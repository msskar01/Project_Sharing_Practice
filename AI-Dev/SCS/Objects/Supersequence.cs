using System;
using System.Collections.Generic;
using System.Text;

namespace SCS.Objects
{
    public class Supersequence
    {
        /// <summary>
        /// Number of total characters that can be removed in the supersequence
        /// </summary>
        public int Weight { get; set; }

        /// <summary>
        /// The actuall supersequence
        /// </summary>
        public string Sequence { get; set; }

        /// <summary>
        /// The strings in order that made up the supersequence
        /// </summary>
        public List<string> OrderOfStrings { get; set; }

        /// <summary>
        /// The paths made from string to string to form supersequence
        /// </summary>
        public List<Path> Paths { get; set; }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="weight"></param>
        /// <param name="sequence"></param>
        /// <param name="orderOfStrings"></param>
        /// <param name="paths"></param>
        public Supersequence(int weight, string sequence, List<string> orderOfStrings, List<Path> paths)
        {
            this.Weight = weight;
            this.Sequence = sequence;
            this.OrderOfStrings = orderOfStrings;
            this.Paths = paths;
        }
    }
}
