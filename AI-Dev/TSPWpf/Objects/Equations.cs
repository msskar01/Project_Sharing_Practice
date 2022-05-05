using System;
using System.Collections.Generic;
using System.Text;

namespace TSPWpf.Objects
{
    /// <summary>
    /// Equations object
    /// </summary>
    public class Equations
    {
        /// <summary>
        /// Distance Equation
        /// </summary>
        /// <param name="city1"></param>
        /// <param name="city2"></param>
        /// <returns></returns>
        public double GetDistance(City city1, City city2)
        {
            return Math.Sqrt(Math.Pow((city2.XCoordinate - city1.XCoordinate), 2) + Math.Pow((city2.YCoordinate - city1.YCoordinate), 2));
        }

        /// <summary>
        /// Calculate the distance between point pt and the segment p1 --> p2.
        /// </summary>
        /// <param name="pt"></param>
        /// <param name="p1"></param>
        /// <param name="p2"></param>
        /// <param name="closest"></param>
        /// <returns></returns>
        public double FindDistanceToSegment(
            City pt, City p1, City p2, out City closest)
        {
            double differencex = p2.XCoordinate - p1.XCoordinate;
            double differencey = p2.YCoordinate - p1.YCoordinate;
            if ((differencex == 0) && (differencey == 0))
            {
                // It's a point not a line segment.
                closest = p1;
                differencex = pt.XCoordinate - p1.XCoordinate;
                differencey = pt.YCoordinate - p1.YCoordinate;
                return Math.Sqrt(differencex * differencex + differencey * differencey);
            }

            // Calculate the t that minimizes the distance.
            double t = (((pt.XCoordinate - p1.XCoordinate) * differencex) + ((pt.YCoordinate - p1.YCoordinate) * differencey)) /
                (differencex * differencex + differencey * differencey);

            // See if this represents one of the segment's
            // end points or a point in the middle.
            if (t < 0)
            {
                closest = new City(p1.Name, p1.XCoordinate, p1.YCoordinate, p1.NextCity);
                differencex = pt.XCoordinate - p1.XCoordinate;
                differencey = pt.YCoordinate - p1.YCoordinate;
            }
            else if (t > 1)
            {
                closest = new City(p2.Name, p2.XCoordinate, p2.YCoordinate, p2.NextCity);
                differencex = pt.XCoordinate - p2.XCoordinate;
                differencey = pt.YCoordinate - p2.YCoordinate;
            }
            else
            {
                closest = new City(p1.Name, p1.XCoordinate + t * differencex, p1.YCoordinate + t * differencey, p1.NextCity);
                differencex = pt.YCoordinate - closest.XCoordinate;
                differencey = pt.YCoordinate - closest.YCoordinate;
                closest = new City(p1.Name, p1.XCoordinate, p1.YCoordinate, p1.NextCity);
            }

            return Math.Sqrt(differencex * differencex + differencey * differencey);
        }
    }
}
