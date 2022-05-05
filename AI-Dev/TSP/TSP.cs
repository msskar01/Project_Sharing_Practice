using System;
using System.Collections.Generic;
using System.Linq;

namespace TSP
{
    /// <summary>
    /// Traveling Sales Person object
    /// </summary>
    class TSP
    {
        static void Main(string[] args)
        {   
            //Variables
            Equations equations = new Equations();
            double xCoordinate, yCoordinate;
            string line, cityName;
            string[] parsedWords;
            List<City> cities = new List<City>();
            
            //Pass in a distance of 0 when creating the path object
            Path path = new Path(0, new List<City>());

            //File reader, looks for cities and puts them into cities list. Uses direct file address to find txt file
            System.IO.StreamReader file = new System.IO.StreamReader(@"C:\Users\phoen\source\repos\AI-Dev\TSP\Input-Text\11PointDFSBFS.tsp");
            while((line = file.ReadLine()) != null)
            {
                if(line == "NODE_COORD_SECTION")
                {
                    while((line = file.ReadLine()) != null)
                    {
                        parsedWords = line.Split(' ');
                        //Skips over any none valid lines in the txt
                        if(parsedWords.Length != 3)
                        {
                            continue;
                        }
                        cityName = parsedWords[0];
                        xCoordinate = Convert.ToDouble(parsedWords[1]);
                        yCoordinate = Convert.ToDouble(parsedWords[2]);
                        cities.Add(new City(cityName, xCoordinate, yCoordinate, new List<City>()));
                    }
                }
            }
            file.Close();

            //Stop program if no cities where found
            if (cities == null)
            {
                return;
            }

            //Hardcoded edges
            for (int count = 0; count < cities.Count(); count++)
            {
                City city = cities[count];
                cities[count] = city.HardCodePath(city, cities);
            }

            ////DFS algorithm call
            //DFS dfs = new DFS();
            //path = dfs.DepthFirstSearch(cities, path, cities.First());

            //BFS algorithm call
            BFS bfs = new BFS();
            path = bfs.BreadthFirstSearch(path, cities.First(), cities.Last());

            Console.WriteLine(path.Distance);
            foreach (City city in path.PathOfCities)
            {
                Console.WriteLine(city.Name);
            }
        }
    }
}
