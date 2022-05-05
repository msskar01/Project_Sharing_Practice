using System;
using System.Collections.Generic;
using System.Text;

namespace TSPWpf.Objects
{
    /// <summary>
    /// City object
    /// </summary>
    public class City
    {
        /// <summary>
        /// Gets and sets the city name
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// Gets and sets the city x cordinate
        /// </summary>
        public double XCoordinate { get; set; }

        /// <summary>
        /// Gets and sets the city y cordinate
        /// </summary>
        public double YCoordinate { get; set; }

        /// <summary>
        /// Gets and sets the next city
        /// </summary>
        public City NextCity { get; set; }

        /// <summary>
        /// Constructor
        /// </summary>
        public City(string name, double xCoordinate, double yCoordinate, City nextCity)
        {
            this.Name = name;
            this.XCoordinate = xCoordinate;
            this.YCoordinate = yCoordinate;
            this.NextCity = nextCity;
        }
    }
}
