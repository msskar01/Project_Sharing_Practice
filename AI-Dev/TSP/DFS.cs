using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TSP
{
    /// <summary>
    /// Depth First Search object
    /// </summary>
    class DFS
    {
        Equations equations = new Equations();

        /// <summary>
        /// Calculates all possible paths using a depth first search algorithm in the form of recursion.
        /// </summary>
        /// <param name="cities"></param>
        /// <param name="path"></param>
        /// <param name="currentCity"></param>
        /// <returns></returns>
        public Path DepthFirstSearch(List<City> cities, Path path, City currentCity)
        {
            Path finalPath = new Path(path.Distance, new List<City>(path.PathOfCities));
            double originalDistance = path.Distance;
            foreach (City city in currentCity.NextCities)
            {
                if (city == currentCity.NextCities.First())
                {
                    path.Distance += equations.GetDistance(currentCity, city);
                    finalPath = DepthFirstSearch(cities, path, city);
                }
                else
                {
                    path.Distance = originalDistance;
                    path.Distance += equations.GetDistance(currentCity, city);
                    Path temp = DepthFirstSearch(cities, path, city);
                    if (temp.Distance < finalPath.Distance)
                    {
                        finalPath = temp;
                    }
                }
            }
            finalPath.PathOfCities.Insert(0, currentCity);
            return finalPath;
        }
    }
}
