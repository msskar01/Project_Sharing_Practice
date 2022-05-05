using System;
using System.Collections.Generic;
using System.Text;

namespace TSP
{
    /// <summary>
    /// Equations object
    /// </summary>
    class Equations
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

    }
}
