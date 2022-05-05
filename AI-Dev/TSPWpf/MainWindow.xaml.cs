using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Shapes;

using TSPWpf.Objects;

namespace TSPWpf
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        #region Constants

        private int generationCounter = 0;

        private double population;

        private double crossoverChance;

        private double mutationChance;

        private List<City> cities = new List<City>();

        private Equations equations = new Equations();
        
        private GeneticAlgorithm geneticAlgorithm = new GeneticAlgorithm();

        #endregion

        #region Main Window
        /// <summary>
        /// Initiates Main window
        /// </summary>
        public MainWindow()
        {

            InitializeComponent();

            //Variables
            population = 50;
            double xCoordinate, yCoordinate;
            string line, cityName;
            string[] parsedWords;

            //Pass in a distance of 0 when creating the path object
            TravelPath path = new TravelPath(0, new List<City>());

            //File reader, looks for cities and puts them into cities list. Uses direct file address to find txt file
            System.IO.StreamReader file = new System.IO.StreamReader(@"C:\Users\phoen\source\repos\AI-Dev\TSPWpf\Input-Text\Random222.tsp");
            while ((line = file.ReadLine()) != null)
            {
                if (line == "NODE_COORD_SECTION")
                {
                    while ((line = file.ReadLine()) != null)
                    {
                        parsedWords = line.Split(' ');
                        //Skips over any none valid lines in the txt
                        if (parsedWords.Length != 3)
                        {
                            continue;
                        }
                        cityName = parsedWords[0];
                        xCoordinate = Convert.ToDouble(parsedWords[1]);
                        yCoordinate = Convert.ToDouble(parsedWords[2]);
                        cities.Add(new City(cityName, xCoordinate, yCoordinate, null));
                    }
                }
            }
            file.Close();

            //Stop program if no cities where found
            if (cities == null)
            {
                return;
            }

            MakeCitiesForFittestPath(cities);
        }

        #endregion

        #region Functions

        /// <summary>
        /// Make the cities in the canvas in the main window
        /// </summary>
        /// <param name="cities"></param>
        private void MakeCitiesForFittestPath(List<City> cities)
        {
            foreach(City city in cities)
            {
                Ellipse fittestEllipse = new Ellipse();
                fittestEllipse.Stroke = Brushes.Black;
                fittestEllipse.Fill = Brushes.Black;
                fittestEllipse.Width = 10;
                fittestEllipse.Height = 10;
                Canvas.SetLeft(fittestEllipse, city.XCoordinate * 7);
                Canvas.SetTop(fittestEllipse, city.YCoordinate * 7);
                fittestPathCanvas.Children.Add(fittestEllipse);
            }
        }

        /// <summary>
        /// Draw the path on the canvas
        /// </summary>
        /// <param name="path"></param>
        private void MakeOverallFittestPath(TravelPath path)
        {
            for (int i = fittestPathCanvas.Children.Count - 1; i >= 0; i += -1)
            {
                UIElement Child = fittestPathCanvas.Children[i];
                if (Child is Line)
                    fittestPathCanvas.Children.Remove(Child);
            }
            for (int i = 0; i < path.PathOfCities.Count() - 1; i++)
            {
                Line myLine = new Line();
                myLine.Stroke = Brushes.Black;
                myLine.X1 = path.PathOfCities.ToArray()[i].XCoordinate * 7 + 5;
                myLine.Y1 = path.PathOfCities.ToArray()[i].YCoordinate * 7 + 5;
                myLine.X2 = path.PathOfCities.ToArray()[i+1].XCoordinate * 7 + 5;
                myLine.Y2 = path.PathOfCities.ToArray()[i+1].YCoordinate * 7 + 5;
                fittestPathCanvas.Children.Add(myLine);
            }
        }


        /// <summary>
        /// Updates the data for the path on the right of the main window
        /// </summary>
        /// <param name="currentFittestPath"></param>
        /// <param name="overallFittestPath"></param>
        private void UpdatePathData(TravelPath currentFittestPath, TravelPath overallFittestPath)
        {
            numberOfGenerationsLabel.Content = string.Format("# of generations: {0}", ++generationCounter);
            currentShortestDistanceLabel.Content = string.Format("Current shortest distance: {0}", currentFittestPath.Distance);
            if (overallFittestPath.Distance == currentFittestPath.Distance)
            {
                generationWithFittestPathLabel.Content = string.Format("Generations to achieve shortest-ever path: {0}", generationCounter);
            }
            overallShortestDistanceLabel.Content = string.Format("Shortest distance ever: {0}", overallFittestPath.Distance);
        }

        /// <summary>
        /// Update just distance
        /// </summary>
        /// <param name="currentFittestPath"></param>
        /// <param name="overallFittestPath"></param>
        private void UpdatePathDistance(TravelPath currentFittestPath, TravelPath overallFittestPath)
        {
            currentShortestDistanceLabel.Content = string.Format("Current shortest distance: {0}", currentFittestPath.Distance);
            overallShortestDistanceLabel.Content = string.Format("Shortest distance ever: {0}", overallFittestPath.Distance);
        }       

        /// <summary>
        /// Update population when slider changes
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void PopulationChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (IsLoaded)
            {
                population = PopulationSlider.Value;
                PopulationLabel.Content = population;
            }
        }

        /// <summary>
        /// Update crossover chance when slider changed
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CrossoverChanceChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (IsLoaded)
            {
                crossoverChance = CrossoverChanceSlider.Value;
                CrossoverChanceLabel.Content = crossoverChance;
            }
        }

        /// <summary>
        /// Update mutation chance when slider changed
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MutationChanceChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (IsLoaded)
            {
                mutationChance = MutationChanceSlider.Value;
                MutationChanceLabel.Content = mutationChance;
            }
        }

        /// <summary>
        /// Starts the GA from the GUI when the play button is pressed
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void PlayButtonClick(object sender, RoutedEventArgs e)
        {
            startTime.Content = DateTime.Now.ToString("HH:mm:ss tt");
            int exitCondition = 0;
            List<Edge> edges = new List<Edge>();
            List<TravelPath> generation, crowds = new List<TravelPath>();
            TravelPath currentFittestPath = null, overallFittestPath = null;

            for (int i = 0; i < 10; i++)
            {
                generation = geneticAlgorithm.GenerateGeneration(cities, population);
                overallFittestPath = null;
                exitCondition = 0;
                while (exitCondition < 50)
                {
                    generation = geneticAlgorithm.GeneticAlgorithmMethod(generation, crossoverChance, mutationChance, out currentFittestPath);
                    if (overallFittestPath == null)
                    {
                        overallFittestPath = currentFittestPath;
                        MakeOverallFittestPath(overallFittestPath);
                    }
                    else if (overallFittestPath.Distance > currentFittestPath.Distance)
                    {
                        overallFittestPath = currentFittestPath;
                        MakeOverallFittestPath(overallFittestPath);
                        exitCondition = 0;
                    }
                    else
                    {
                        exitCondition++;
                    }
                    UpdatePathData(currentFittestPath, overallFittestPath);
                }
                while (true)
                {
                    TravelPath newPath = geneticAlgorithm.FixCrossovers(overallFittestPath);
                    if (newPath.Distance != overallFittestPath.Distance)
                    {
                        overallFittestPath.PathOfCities = newPath.PathOfCities;
                        overallFittestPath.Distance = newPath.Distance;
                    }
                    else
                    {
                        break;
                    }
                }
                crowds.Add(overallFittestPath);
            }
            
            //Reset the next cities since they are supposed to be null, but since they are pointers will not automaticly reset
            foreach(City city in cities)
            {
                city.NextCity = null;
            }

            foreach(TravelPath crowd in crowds)
            {
                for(int i = 0; i < crowd.PathOfCities.Count() - 1; i++)
                {
                    Edge edge = new Edge(crowd.PathOfCities[i], crowd.PathOfCities[i+1], equations.GetDistance(crowd.PathOfCities[i], crowd.PathOfCities[i + 1]));
                    
                    if(edges.Any(x => x.City1 == edge.City1 && x.City2 == edge.City2))
                    {
                        int tempIndex = edges.FindIndex(x => x.City1 == edge.City1 && x.City2 == edge.City2);
                        edges[tempIndex].Count++;
                    }
                    else
                    {
                        edges.Add(edge);
                    }
                }
            }
            edges = edges.OrderByDescending(x => x.Count).ThenBy(x => x.Distance).ToList();
            overallFittestPath.PathOfCities.Clear();
            overallFittestPath.Distance = 0;

            foreach (Edge edge in edges)
            {
                if (!overallFittestPath.PathOfCities.Contains(edge.City1))
                {
                    if (overallFittestPath.PathOfCities.Contains(edge.City2))
                    {
                        //Don't add city1 to the path if city2 already has something going to it, otherwise there would be two cities going to the same city
                        foreach(City city in overallFittestPath.PathOfCities)
                        {
                            if(city.NextCity == edge.City2)
                            {
                                //Go to the end of the outter loop to avoid getting cought in this one
                                goto END;
                            }
                        }
                        edge.City1.NextCity = edge.City2;
                        overallFittestPath.PathOfCities.Insert(overallFittestPath.PathOfCities.IndexOf(edge.City2), edge.City1);
                        overallFittestPath.Distance += edge.Distance;
                    }
                    else
                    {
                        edge.City1.NextCity = edge.City2;
                        overallFittestPath.PathOfCities.Add(edge.City1);
                        overallFittestPath.PathOfCities.Add(edge.City2);
                        overallFittestPath.Distance += edge.Distance;
                    }
                }
                else if (overallFittestPath.PathOfCities.Single(x => x.Equals(edge.City1)).NextCity == null)
                {
                    if (overallFittestPath.PathOfCities.Contains(edge.City2))
                    {
                        //Case where the edge includes the end of a subpath for city1 and the beginning of a subpath for city2
                        if (overallFittestPath.PathOfCities[overallFittestPath.PathOfCities.IndexOf(edge.City2)].NextCity != null &&
                            SelectStartOfSubPath(overallFittestPath, edge.City2) == edge.City2)
                        {
                            //Check if the start of the edge is already somewhere in the sub path that contains the end of the edge
                            if(IsInSubPath(edge.City1, SelectStartOfSubPath(overallFittestPath, edge.City2)))
                            {
                                continue;
                            }

                            //Check if edge is already in the list but backwords
                            if(edge.City2.NextCity == edge.City1)
                            {
                                continue;
                            }

                            //grab the subpath that contains city1 and put it right before city2 and its subpath, connect the two by setting the next city
                            overallFittestPath.PathOfCities[overallFittestPath.PathOfCities.IndexOf(edge.City1)].NextCity = overallFittestPath.PathOfCities[overallFittestPath.PathOfCities.IndexOf(edge.City2)];
                            overallFittestPath = MovePathRange(overallFittestPath,
                                                               overallFittestPath.PathOfCities.IndexOf(SelectStartOfSubPath(overallFittestPath, edge.City1)),
                                                               overallFittestPath.PathOfCities.IndexOf(edge.City1),
                                                               edge.City2);
                            overallFittestPath.Distance += edge.Distance;
                        }
                        
                        //The case where both city1 and city2 from the edge are the ends of two different subpaths, reverse the subpath for city2 and then add city1 to it
                        else if(overallFittestPath.PathOfCities[overallFittestPath.PathOfCities.IndexOf(edge.City1)].NextCity == null &&
                                overallFittestPath.PathOfCities[overallFittestPath.PathOfCities.IndexOf(edge.City2)].NextCity == null)
                        {
                            int indexA = overallFittestPath.PathOfCities.IndexOf(SelectStartOfSubPath(overallFittestPath, edge.City2));
                            List<City> temp = overallFittestPath.PathOfCities.GetRange(indexA,
                                                                                       Math.Abs(overallFittestPath.PathOfCities.IndexOf(edge.City2) - indexA) + 1);
                            temp.Reverse();
                            for(int i = 0; i < temp.Count(); i++)
                            {
                                if (i == temp.Count() - 1)
                                {
                                    temp[i].NextCity = null;
                                }
                                else
                                {
                                    temp[i].NextCity = temp[i + 1];
                                }
                            }
                            foreach (City city in temp)
                            {
                                overallFittestPath.PathOfCities[indexA] = city;
                                indexA++;
                            }
                            overallFittestPath.PathOfCities[overallFittestPath.PathOfCities.IndexOf(edge.City1)].NextCity = overallFittestPath.PathOfCities[overallFittestPath.PathOfCities.IndexOf(edge.City2)];
                            overallFittestPath = MovePathRange(overallFittestPath,
                                                               overallFittestPath.PathOfCities.IndexOf(SelectStartOfSubPath(overallFittestPath, edge.City1)),
                                                               overallFittestPath.PathOfCities.IndexOf(edge.City1),
                                                               edge.City2);
                            overallFittestPath.Distance += edge.Distance;
                        }
                    }
                    else
                    {
                        overallFittestPath.PathOfCities.Insert(overallFittestPath.PathOfCities.IndexOf(edge.City1) + 1, edge.City2);
                        overallFittestPath.PathOfCities.Single(x => x.Equals(edge.City1)).NextCity = edge.City2;
                        overallFittestPath.Distance += edge.Distance;
                    }
                }
            END:;   
            }
            overallFittestPath.PathOfCities.Add(overallFittestPath.PathOfCities.First());
            overallFittestPath.Distance += equations.GetDistance(overallFittestPath.PathOfCities.Last(),
                                                                 overallFittestPath.PathOfCities[overallFittestPath.PathOfCities.Count() - 2]);

            while (true)
            {
                TravelPath newPath = geneticAlgorithm.FixCrossovers(overallFittestPath);
                if (newPath.Distance != overallFittestPath.Distance)
                {
                    overallFittestPath.PathOfCities = newPath.PathOfCities;
                    overallFittestPath.Distance = newPath.Distance;
                }
                else
                {
                    break;
                }
            }

            crowds.OrderBy(x => x.Distance);
            currentFittestPath = crowds[0];
            UpdatePathDistance(currentFittestPath, overallFittestPath);
            MakeOverallFittestPath(overallFittestPath);
            endTime.Content = DateTime.Now.ToString("HH:mm:ss tt");
        }

        /// <summary>
        /// Selectes the starting city in a sub path of the main path
        /// </summary>
        /// <param name="travelPath"></param>
        /// <param name="nextCity"></param>
        /// <returns></returns>
        public City SelectStartOfSubPath(TravelPath travelPath, City nextCity)
        {
            foreach(City city in travelPath.PathOfCities)
            {
                if(city.NextCity == nextCity)
                {
                    return SelectStartOfSubPath(travelPath, city);
                }
            }
            return nextCity;
        }

        /// <summary>
        /// Checks to see if a city is in a given path
        /// </summary>
        /// <param name="compare"></param>
        /// <param name="startOfPathOfCities"></param>
        /// <returns></returns>
        public bool IsInSubPath(City compare, City startOfPathOfCities)
        {
            while (true)
            {
                if (startOfPathOfCities.NextCity == compare)
                {
                    return true;
                }
                else if (startOfPathOfCities.NextCity != null)
                {
                    startOfPathOfCities = startOfPathOfCities.NextCity;
                }
                else
                {
                    return false;
                }
            }
        }

        /// <summary>
        /// Moves a range of cities in a path
        /// </summary>
        /// <param name="travelPath"></param>
        /// <param name="startIndex"></param>
        /// <param name="endIndex"></param>
        /// <param name="tagetCity"></param>
        /// <returns></returns>
        public TravelPath MovePathRange(TravelPath travelPath, int startIndex, int endIndex, City tagetCity)
        {
            var pathRange = travelPath.PathOfCities.GetRange(startIndex, Math.Abs(endIndex - startIndex) + 1);
            travelPath.PathOfCities.RemoveRange(startIndex, Math.Abs(endIndex - startIndex) + 1);
            foreach(City city in pathRange)
            {
                travelPath.PathOfCities.Insert(travelPath.PathOfCities.IndexOf(tagetCity), city);
            }
            return travelPath;
        }

        #endregion
    }
}
