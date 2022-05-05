using System;
using System.Collections.Generic;
using System.Text;

namespace TSP
{
    /// <summary>
    /// Path object
    /// </summary>
    class Path
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
        public Path(double distance, List<City> pathOfCities)
        {
            this.Distance = distance;
            this.PathOfCities = pathOfCities;
        }
    }
}
