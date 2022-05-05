using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TSPWpf.Objects
{
    /// <summary>
    /// Edge Object
    /// </summary>
    public class Edge
    {
        /// <summary>
        /// Get and set city1
        /// </summary>
        public City City1 { get; set; }

        /// <summary>
        /// Get and set city2
        /// </summary>
        public City City2 { get; set; }

        /// <summary>
        /// Get and set Distance
        /// </summary>
        public double Distance { get; set; }

        /// <summary>
        /// For wizdom of crowds, keeps count of how many common edges are found
        /// </summary>
        public int Count { get; set; }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="city1"></param>
        /// <param name="city2"></param>
        /// <param name="distance"></param>
        public Edge(City city1, City city2, double distance)
        {
            this.City1 = city1;
            this.City2 = city2;
            this.Distance = distance;
            this.Count = 0;
        }
    }
}
