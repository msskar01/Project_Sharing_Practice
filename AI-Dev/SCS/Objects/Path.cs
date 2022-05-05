using System;
using System.Collections.Generic;
using System.Text;

namespace SCS.Objects
{
    public class Path
    {
        /// <summary>
        /// Left String
        /// </summary>
        public string String1 { get; set; }

        /// <summary>
        /// Right String
        /// </summary>
        public string String2 { get; set; }

        /// <summary>
        /// The amount of characters that can be removed traveling from string1 to string2
        /// </summary>
        public int Weight { get; set; }

        /// <summary>
        /// Popularity count
        /// </summary>
        public int Count { get; set; }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="string1"></param>
        /// <param name="string2"></param>
        /// <param name="weight"></param>
        public Path(string string1, string string2, int weight)
        {
            this.String1 = string1;
            this.String2 = string2;
            this.Weight = weight;
            this.Count = 0;
        }
    }
}
