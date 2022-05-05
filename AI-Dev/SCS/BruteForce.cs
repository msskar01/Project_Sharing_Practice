using System;
using System.Collections.Generic;
using System.Text;

using SCS.Objects;

namespace SCS
{
    public class BruteForce
    {
        public Equations equations = new Equations();

        public Supersequence BruteForceMethod(List<string> strings, string start, Supersequence supersequence)
        {
            Supersequence finalSupersequence = new Supersequence(supersequence.Weight, supersequence.Sequence, new List<string>(supersequence.OrderOfStrings), new List<Path>(supersequence.Paths));
            List<Path> originalPaths = new List<Path>(supersequence.Paths);
            strings.Remove(start);
            for (int position = strings.Count - 1; position >= 0; position--)
            {
                string str = strings[position];
                if (position == strings.Count - 1)
                {
                    supersequence.Paths.Add(new Path(start, str, equations.GetWeight(start, strings[position])));
                    strings.Remove(str);
                    supersequence.OrderOfStrings.Add(str);
                    finalSupersequence = BruteForceMethod(strings, str, supersequence);
                    supersequence.OrderOfStrings.Remove(str);
                    finalSupersequence.Weight = equations.GetSuperWeight(supersequence.Paths);
                    strings.Insert(position, str);
                }
                else
                {
                    supersequence.Paths = new List<Path>(originalPaths);
                    supersequence.Paths.Add(new Path(start, str, equations.GetWeight(start, strings[position])));
                    strings.Remove(str);
                    supersequence.OrderOfStrings.Add(str);
                    Supersequence tempSupersequence = BruteForceMethod(strings, str, supersequence);
                    supersequence.OrderOfStrings.Remove(str);
                    if (tempSupersequence.Weight > finalSupersequence.Weight)
                    {
                        finalSupersequence.Weight = tempSupersequence.Weight;
                        finalSupersequence.Sequence = tempSupersequence.Sequence;
                        finalSupersequence.OrderOfStrings = new List<string>(tempSupersequence.OrderOfStrings);
                        finalSupersequence.Paths = new List<Path>(tempSupersequence.Paths);
                    }
                    strings.Insert(position, str);
                }
            }
            return finalSupersequence;
        }
    }
}
