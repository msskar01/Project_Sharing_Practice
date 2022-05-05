using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using TSPWpf.Objects;

namespace TSPWpf
{
    /// <summary>
    /// Cheapest Insertion Greedy Algorithm
    /// </summary>
    class Greedy
    {
        Equations equations = new Equations();

        /// <summary>
        /// Creates a path using the list of past in cities using Cheapest Insertion by finding the shortest distance from a point to a line segment
        /// </summary>
        /// <param name="path"></param>
        /// <param name="cities"></param>
        /// <returns></returns>
        public TravelPath GreedyAlgorithm(TravelPath path, List<City> cities)
        {
            City startingCity = cities.First();

            List<Edge> edges = new List<Edge>();
            foreach(City city in cities)
            {
                if(city == startingCity)
                {
                    continue;
                }

                double distance = equations.GetDistance(city,
                                                        startingCity);
                edges.Add(new Edge(startingCity,
                                   city,
                                   distance));
            }
            edges = edges.OrderBy(x => x.Distance).ToList();
            path.PathOfCities.Add(startingCity);
            cities.Remove(startingCity);

            path.PathOfCities.Last().NextCity = edges.ToArray()[0].City2;
            path.PathOfCities.Add(edges.ToArray()[0].City2);
            cities.Remove(edges.ToArray()[0].City2);
            path.Distance += edges.ToArray()[0].Distance;

            path.PathOfCities.Last().NextCity = edges.ToArray()[1].City2;
            path.PathOfCities.Add(edges.ToArray()[1].City2);
            cities.Remove(edges.ToArray()[1].City2);
            path.Distance += equations.GetDistance(edges.ToArray()[0].City2,
                                                   edges.ToArray()[1].City2);

            path.PathOfCities.Last().NextCity = startingCity;
            path.PathOfCities.Add(startingCity);
            path.Distance += edges.ToArray()[1].Distance;

            edges.Clear();

            //Everything after the first three nodes
            while(cities.Count != 0)
            {
                City closestCity = new City("", 0, 0, null);
                City tempCity = new City("", 0, 0, null);
                City tempPathCity = new City("", 0, 0, null);
                double record = -1;
                foreach (City city in cities)
                {
                    foreach(City pathCity in path.PathOfCities)
                    {
                        double distance = equations.FindDistanceToSegment(city, pathCity, pathCity.NextCity, out closestCity);
                        if(record == -1)
                        {
                            record = distance;
                            tempCity = city;
                            tempPathCity = closestCity;
                        }
                        else if(distance < record)
                        {
                            record = distance;
                            tempCity = city;
                            tempPathCity = closestCity;
                        }
                    }
                }
                if (cities.Count() == 0)
                {
                    continue;
                }

                tempCity.NextCity = tempPathCity.NextCity;
                tempPathCity.NextCity = tempCity;
                cities.Remove(tempCity);
                var location = path.PathOfCities.FindIndex(x => x.Name == tempPathCity.Name);
                path.PathOfCities[location] = tempPathCity;
                path.PathOfCities.Insert(location + 1, tempCity);
                path.Distance += record;
            }

            return path;
        }
    }
}
