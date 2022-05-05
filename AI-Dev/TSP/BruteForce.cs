using System;
using System.Collections.Generic;
using System.Text;

namespace TSP
{
    /// <summary>
    /// Brute Force object, similar to DFS
    /// </summary>
    class BruteForce
    {
        Equations equations = new Equations();

        /// <summary>
        /// Calculates all possiple paths from a starting city from a list of cities and returns the path with the least distance
        /// </summary>
        /// <param name="startingCity"></param>
        /// <param name="cities"></param>
        /// <param name="path"></param>
        /// <param name="currentCity"></param>
        /// <returns></returns>
        public Path BruteForceMethod(City startingCity, List<City> cities, Path path, City currentCity)
        {
            Path finalPath = new Path(path.Distance, new List<City>());
            double originalDistance = path.Distance;
            City city;
            for (int position = cities.Count - 1; position >= 0; position--)
            {
                city = cities[position];
                if (position == cities.Count - 1)
                {
                    path.Distance += equations.GetDistance(currentCity, city);
                    cities.Remove(city);
                    finalPath = BruteForceMethod(startingCity, cities, path, city);
                    cities.Insert(position, city);
                }
                else
                {
                    path.Distance = originalDistance;
                    path.Distance += equations.GetDistance(currentCity, city);
                    cities.Remove(city);
                    Path temp = BruteForceMethod(startingCity, cities, path, city);
                    if (temp.Distance < finalPath.Distance)
                    {
                        finalPath = temp;
                    }
                    cities.Insert(position, city);
                }
            }
            if(cities.Count == 0)
            {
                finalPath.PathOfCities.Insert(0, currentCity);
                finalPath.Distance += equations.GetDistance(currentCity, startingCity);
                return finalPath;
            }
            finalPath.PathOfCities.Insert(0, currentCity);
            return finalPath;
        }
    }
}
