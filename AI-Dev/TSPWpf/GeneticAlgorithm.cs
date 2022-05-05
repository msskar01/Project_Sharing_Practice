using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using TSPWpf.Objects;

namespace TSPWpf
{
    class GeneticAlgorithm
    {
        Equations equations = new Equations();
        private Random rand = new Random();

        /// <summary>
        /// The actual Genetic Algorithm
        /// </summary>
        /// <param name="parentGeneration"></param>
        /// <param name="CrossOverChance"></param>
        /// <param name="MutationChance"></param>
        /// <param name="fittestPath"></param>
        /// <returns></returns>
        public List<TravelPath> GeneticAlgorithmMethod(List<TravelPath> parentGeneration, double CrossOverChance, double MutationChance, out TravelPath fittestPath)
        {
            List<TravelPath> childGeneration = new List<TravelPath>();
            TravelPath childPath, secondFittestPath;
            parentGeneration = parentGeneration.OrderBy(x => x.Distance).ToList();
            while(childGeneration.Count() < parentGeneration.Count())
            {
                //crossover
                if ((((double)rand.Next(10) / 10) + CrossOverChance) > 1)
                {
                    fittestPath = parentGeneration.First();
                    secondFittestPath = parentGeneration[1];
                    childPath = CrossOverFunction(fittestPath,
                                                  secondFittestPath);
                    childGeneration.Add(childPath);
                }
                //mutate
                else if(((double)rand.Next(20) / 20) + MutationChance > 1)
                {
                    childGeneration.Add(MutationFunction(parentGeneration[rand.Next(parentGeneration.Count())]));
                }
                //clone
                else
                {
                    childGeneration.Add(parentGeneration[rand.Next(parentGeneration.Count())]);
                }
            }
            childGeneration = childGeneration.OrderBy(x => x.Distance).ToList();
            fittestPath = childGeneration.First();
            return childGeneration;
        }

        /// <summary>
        /// Generates a randomly filled generation with random paths
        /// </summary>
        /// <param name="cities"></param>
        /// <param name="population"></param>
        /// <returns></returns>
        public List<TravelPath> GenerateGeneration(List<City> cities, double population)
        {
            List<TravelPath> generation = new List<TravelPath>();
            for(int i = 0; i < population; i++)
            {
                TravelPath path = new TravelPath(0, new List<City>());

                //Create random paths for the generation
                for(int count = cities.Count(); count > 0; count--)
                {
                    int random = rand.Next(cities.Count());
                    path.PathOfCities.Add(cities[random]);
                    cities.Remove(cities[random]);
                    if(path.PathOfCities.Count() > 1)
                    {
                        path.Distance += equations.GetDistance(path.PathOfCities.Last(),
                                                               path.PathOfCities[path.PathOfCities.Count()- 2]);
                    }
                }

                //Add cities back to list
                foreach (City city in path.PathOfCities)
                {
                    cities.Add(city);
                }

                //Add the first city in the path to make a loop
                path.PathOfCities.Add(path.PathOfCities.First());
                path.Distance += equations.GetDistance(path.PathOfCities.Last(),
                                                       path.PathOfCities[path.PathOfCities.Count() - 2]);
                //Add to generation
                generation.Add(path);
            }
            return generation;
        }

        /// <summary>
        /// Crossover function, takes part of the first path and places it in the childpath, then fills in the rest of the child path with what ever is left over in the second path
        /// </summary>
        /// <param name="fittestPath"></param>
        /// <param name="secondFittestPath"></param>
        /// <returns></returns>
        public TravelPath CrossOverFunction(TravelPath fittestPath, TravelPath secondFittestPath)
        {
            TravelPath childPath = new TravelPath(0, new List<City>());
            int index = rand.Next(fittestPath.PathOfCities.Count() - 1), count = rand.Next(fittestPath.PathOfCities.Count - index - 1);
            foreach (City city in fittestPath.PathOfCities.GetRange(index,
                                                                    count))
            {
                childPath.PathOfCities.Add(city);
                if(childPath.PathOfCities.Count() > 1)
                {
                    childPath.Distance += equations.GetDistance(childPath.PathOfCities.Last(),
                                                                childPath.PathOfCities[childPath.PathOfCities.Count() - 2]);
                }
            }
            foreach(City city in secondFittestPath.PathOfCities)
            {
                if(!childPath.PathOfCities.Contains(city))
                {
                    childPath.PathOfCities.Add(city);
                    if (childPath.PathOfCities.Count() > 1)
                    {
                        childPath.Distance += equations.GetDistance(childPath.PathOfCities.Last(),
                                                                    childPath.PathOfCities[childPath.PathOfCities.Count() - 2]);
                    }
                }
            }
            childPath.PathOfCities.Add(childPath.PathOfCities.First());
            childPath.Distance += equations.GetDistance(childPath.PathOfCities.Last(),
                                                        childPath.PathOfCities[childPath.PathOfCities.Count() - 2]);
            return childPath;
        }

        /// <summary>
        /// Mutation function designed to swap two cities in a path and reuturn the resulted child path
        /// </summary>
        /// <param name="travelPath"></param>
        /// <returns></returns>
        public TravelPath MutationFunction(TravelPath travelPath)
        {
            TravelPath newPath = FixCrossovers(travelPath);
            if (newPath.Distance != travelPath.Distance)
            {
                travelPath.PathOfCities = newPath.PathOfCities;
                travelPath.Distance = newPath.Distance;
            }
            return travelPath;
        }

        public TravelPath FixCrossovers(TravelPath travelPath)
        {
            var list = new List<City>();
            foreach (City city in travelPath.PathOfCities)
            {
                list.Add(city);
            }
            var derefPath = new TravelPath(0, list);
            derefPath.PathOfCities.RemoveAt(derefPath.PathOfCities.Count() - 1);
            for (int city1 = 0; city1 < derefPath.PathOfCities.Count() - 1; city1++)
            {
                for (int city2 = 0; city2 < derefPath.PathOfCities.Count() - 1; city2++)
                {
                    if (city1 == city2 || city1 + 1 == city2 || city2 + 1 == city1)
                    {
                        continue;
                    }

                    if (CheckIntersection(derefPath.PathOfCities[city1], derefPath.PathOfCities[city1 + 1], derefPath.PathOfCities[city2], derefPath.PathOfCities[city2 + 1]))
                    {
                        derefPath.PathOfCities = derefPath.ReverseCities(derefPath.PathOfCities,
                                                                         city1 + 1,
                                                                         city2);
                    }
                }
            }
            derefPath.PathOfCities.Add(derefPath.PathOfCities.First());
            derefPath.Distance = derefPath.CalculatePathDistance(derefPath);
            return derefPath;
        }

        public bool CheckIntersection(City LineACity1, City LineACity2, City LineBCity1, City LineBCity2)
        {
            int oBCity1 = orientation(LineACity1, LineACity2, LineBCity1);
            int oBCity2 = orientation(LineACity1, LineACity2, LineBCity2);
            int oACity1 = orientation(LineBCity1, LineBCity2, LineACity1);
            int oACity2 = orientation(LineBCity1, LineBCity2, LineACity2);

            // General case 
            if (oBCity1 != oBCity2 && oACity1 != oACity2)
            {
                return true;
            }

            // Special Cases 
            // p1, q1 and p2 are colinear and p2 lies on segment p1q1 
            if (oBCity1 == 0 && onSegment(LineACity1, LineBCity1, LineACity2))
            {
                return true;
            }

            // p1, q1 and q2 are colinear and q2 lies on segment p1q1 
            if (oBCity2 == 0 && onSegment(LineACity1, LineBCity2, LineACity2))
            {
                return true;
            }

            // p2, q2 and p1 are colinear and p1 lies on segment p2q2 
            if (oACity1 == 0 && onSegment(LineBCity1, LineACity1, LineBCity2))
            {
                return true;
            }

            // p2, q2 and q1 are colinear and q1 lies on segment p2q2 
            if (oACity2 == 0 && onSegment(LineBCity1, LineACity2, LineBCity2))
            {
                return true;
            }

            return false; // Doesn't fall in any of the above cases 
        }

        // Given three colinear points p, q, r, the function checks if 
        // point q lies on line segment 'pr' 
        static Boolean onSegment(City p, City q, City r)
        {
            if (q.XCoordinate <= Math.Max(p.XCoordinate, r.XCoordinate) && q.XCoordinate >= Math.Min(p.XCoordinate, r.XCoordinate) &&
                q.YCoordinate <= Math.Max(p.YCoordinate, r.YCoordinate) && q.YCoordinate >= Math.Min(p.YCoordinate, r.YCoordinate))
            {
                return true;
            }
            return false;
        }

        // To find orientation of ordered triplet (p, q, r). 
        // The function returns following values 
        // 0 --> p, q and r are colinear 
        // 1 --> Clockwise 
        // 2 --> Counterclockwise 
        static int orientation(City p, City q, City r)
        {
            double val = ((q.YCoordinate - p.YCoordinate) * (r.XCoordinate - q.XCoordinate)) -
                      ((q.XCoordinate - p.XCoordinate) * (r.YCoordinate - q.YCoordinate));

            if (val == 0)
            {
                return 0; // colinear 
            }

            return (val > 0) ? 1 : 2; // clock or counterclock wise 
        }


        //public TravelPath MutationFunction(TravelPath travelPath)
        //{
        //    travelPath.PathOfCities.Remove(travelPath.PathOfCities.Last());
        //    travelPath.PathOfCities = travelPath.SwapCities(travelPath.PathOfC ities,
        //                                                     rand.Next(travelPath.PathOfCities.Count() - 1),
        //                                                     rand.Next(travelPath.PathOfCities.Count() - 2));
        //    travelPath.PathOfCities.Add(travelPath.PathOfCities.First());
        //    travelPath.Distance = travelPath.CalculatePathDistance(travelPath);
        //    return travelPath;
        //}
    }
}
