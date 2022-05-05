using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TSPWpf.Objects
{
    /// <summary>
    /// Path object
    /// </summary>
    public class TravelPath
    {
        /// <summary>
        /// Get and set the path distance
        /// </summary>
        public double Distance { get; set; }

        /// <summary>
        /// Get and set the path taken from the starting city
        /// </summary>
        public List<City> PathOfCities { get; set; }

        /// <summary>
        /// Constructor
        /// </summary>
        public TravelPath(double distance, List<City> pathOfCities)
        {
            this.Distance = distance;
            this.PathOfCities = pathOfCities;
        }

        /// <summary>
        /// Swaps two cities in a path
        /// </summary>
        /// <param name="cities"></param>
        /// <param name="indexA"></param>
        /// <param name="indexB"></param>
        /// <returns></returns>
        public List<City> SwapCities(List<City> cities, int indexA, int indexB)
        {
            City tmp = cities[indexA];
            cities[indexA] = cities[indexB];
            cities[indexB] = tmp;
            return cities;
        }

        /// <summary>
        /// Reverse the order of cities in a path, starting at indexA to indexB
        /// </summary>
        /// <param name="cities"></param>
        /// <param name="indexA"></param>
        /// <param name="indexB"></param>
        /// <returns></returns>
        public List<City> ReverseCities(List<City> cities, int indexA, int indexB)
        {
            if(indexA > indexB)
            {
                int ind = indexB;
                indexB = indexA;
                indexA = ind;
            }
            List<City> temp = cities.GetRange(indexA, Math.Abs(indexB - indexA) + 1);
            temp.Reverse();
            foreach(City city in temp)
            {
                cities[indexA] = city;
                indexA++;
            }
            return cities;
        }

        /// <summary>
        /// Calculates the distance for a full path of cities
        /// </summary>
        /// <param name="travelPath"></param>
        /// <returns></returns>
        public double CalculatePathDistance(TravelPath travelPath)
        {
            Equations equations = new Equations();
            List<City> pathOfCities = new List<City>();
            travelPath.Distance = 0;
            foreach(City city in travelPath.PathOfCities)
            {
                pathOfCities.Add(city);
                if(pathOfCities.Count() > 1)
                {
                    travelPath.Distance += equations.GetDistance(pathOfCities[pathOfCities.Count() - 2],
                                                                 pathOfCities.Last());
                }
            }
            return travelPath.Distance;
        }
    }
}
