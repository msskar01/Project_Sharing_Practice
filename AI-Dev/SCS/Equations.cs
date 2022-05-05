using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
using System.Windows;

using SCS.Objects;

namespace SCS
{
    public class Equations
    {
        /// <summary>
        /// Gets the weight of just the current path of string1 to string2
        /// </summary>
        /// <param name="string1"></param>
        /// <param name="string2"></param>
        /// <returns></returns>
        public int GetWeight(string string1, string string2)
        {
            int weight = 0, maxWeight = 0;
            for (int i = string1.Length - 1; i > 0; i--)
            {
                if(string1[i] == string2[0])
                {
                    if(weight > 0)
                    {
                        maxWeight = weight;
                        weight = 0;
                    }
                    for(int s1 = i, s2 = 0; s1 < string1.Length && s2 < string2.Length; s1++, s2++)
                    {
                        if(string1[s1] == string2[s2])
                        {
                            weight++;
                        }
                        else
                        {
                            weight = 0;
                            break;
                        }
                    }
                }
            }
            if(maxWeight > weight)
            {
                weight = maxWeight;
            }
            return weight;
        }

        /// <summary>
        /// Gets the weight of the whole supersequince
        /// </summary>
        /// <param name="paths"></param>
        /// <returns></returns>
        public int GetSuperWeight(List<Path> paths)
        {
            int weight = 0;
            foreach (Path path in paths)
            {
                weight += path.Weight;
            }
            return weight;
        }

        /// <summary>
        /// Gets the sequence from the list of paths
        /// </summary>
        /// <param name="supersequence"></param>
        /// <returns></returns>
        public string GetSequence(Supersequence supersequence)
        {
            foreach (Path path in supersequence.Paths)
            {
                string tempString2 = path.String2;
                if (supersequence.Sequence == string.Empty)
                {
                    supersequence.Sequence += path.String1;
                }
                for (int i = path.Weight; i > 0; i--)
                {
                    tempString2 = tempString2.Remove(0, 1);
                }
                supersequence.Sequence += tempString2;
            }
            return supersequence.Sequence;
        }
    }
}
