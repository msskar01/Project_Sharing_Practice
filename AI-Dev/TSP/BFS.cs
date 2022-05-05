using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TSP
{
    /// <summary>
    /// Bredth First Search object
    /// </summary>
    class BFS
    {
        Equations equations = new Equations();

        /// <summary>
        /// Calculates all possible paths using a bredth first search algorithm in the form of using queues to keep track of which level the algortihm is on.
        /// </summary>
        /// <param name="startPath"></param>
        /// <param name="startCity"></param>
        /// <param name="targetCity"></param>
        /// <returns></returns>
        public Path BreadthFirstSearch(Path startPath, City startCity, City targetCity)
        {
            List<Path> listOfPaths = new List<Path>();
            Queue<City> cityQueue = new Queue<City>();
            Queue<Path> pathQueue = new Queue<Path>();
            startPath.PathOfCities.Add(startCity);
            cityQueue.Enqueue(startCity);
            pathQueue.Enqueue(startPath);

            while (cityQueue.Count > 0)
            {
                City city = cityQueue.Dequeue();
                Path path = pathQueue.Dequeue();
                if (city == targetCity)
                {
                    listOfPaths.Add(path);
                }
                foreach (City nextCity in city.NextCities)
                {
                    Path newPath = new Path(path.Distance, new List<City>(path.PathOfCities));
                    newPath.Distance += equations.GetDistance(city, nextCity);
                    newPath.PathOfCities.Add(nextCity);
                    cityQueue.Enqueue(nextCity);
                    pathQueue.Enqueue(newPath);
                }
            }

            Path finalPath = listOfPaths.OrderBy(x => x.Distance).First();

            return finalPath;
        }
    }
}
