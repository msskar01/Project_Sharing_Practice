using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using SCS.Objects;

namespace SCS
{
    class GeneticAlgorithm
    {
        #region Constants

        Equations equations = new Equations();
        private Random rand = new Random();

        #endregion

        /// <summary>
        /// Generic Algorithm method, will create new generations spawned from crossover of the parent generation
        /// </summary>
        /// <param name="parentGeneration"></param>
        /// <param name="CrossOverChance"></param>
        /// <param name="MutationChance"></param>
        /// <param name="fittestSequence"></param>
        /// <returns></returns>
        public List<Supersequence> GeneticAlgorithmMethod(List<Supersequence> parentGeneration, double CrossOverChance, double MutationChance, out Supersequence fittestSequence)
        {
            List<Supersequence> childGeneration = new List<Supersequence>();
            Supersequence childSupersequence, secondFittestSequence;
            parentGeneration = parentGeneration.OrderByDescending(x => x.Weight).ToList();
            fittestSequence = Tournament(new List<Supersequence>(parentGeneration));
            parentGeneration.Remove(fittestSequence);
            secondFittestSequence = Tournament(new List<Supersequence>(parentGeneration));
            parentGeneration.Add(fittestSequence);
            while (childGeneration.Count() < parentGeneration.Count())
            {
                //crossover
                if ((((double)rand.Next(20) / 20) + CrossOverChance) > 1)
                {
                    childSupersequence = CrossOverFunction(fittestSequence,
                                                           secondFittestSequence);
                    //mutate
                    if (((double)rand.Next(20) / 20) + MutationChance > 1)
                    {
                        childGeneration.Add(MutationFunction(childSupersequence));
                    }
                    else
                    {
                        childSupersequence.Weight = equations.GetSuperWeight(childSupersequence.Paths);
                        childGeneration.Add(childSupersequence);
                    }
                }
                //clone
                else
                {
                    childGeneration.Add(parentGeneration[rand.Next(parentGeneration.Count())]);
                }
            }
            childGeneration = childGeneration.OrderByDescending(x => x.Weight).ToList();
            fittestSequence = childGeneration.First();
            return childGeneration;
        }

        /// <summary>
        /// Tournament to deside the fittest paths
        /// </summary>
        /// <param name="generation"></param>
        /// <returns></returns>
        public Supersequence Tournament(List<Supersequence> generation)
        {
            while(generation.Count() != 1)
            {
                int randomPostion1 = rand.Next(generation.Count() - 1), randomPostion2 = rand.Next(generation.Count() - 2);
                Supersequence supersequence1 = generation[randomPostion1];
                generation.Remove(supersequence1);
                Supersequence supersequence2 = generation[randomPostion2];
                if(supersequence1.Weight > supersequence2.Weight)
                {
                    generation.Add(supersequence1);
                    generation.Remove(supersequence2);
                }
            }
            return generation.First();
        }

        /// <summary>
        /// Crossover just takes a random sample from the fittest and then filles in the rest of the genomes using the second fittest
        /// </summary>
        /// <param name="fittestSequence"></param>
        /// <param name="secondFittestSequence"></param>
        /// <returns></returns>
        public Supersequence CrossOverFunction(Supersequence fittestSequence, Supersequence secondFittestSequence)
        {
            string[] stringArray = new string[fittestSequence.OrderOfStrings.Count()];
            Path[] pathArray = new Path[fittestSequence.Paths.Count()];
            Supersequence childSupersequence = new Supersequence(0, string.Empty, new List<string>(), new List<Path>());
            int range = rand.Next(fittestSequence.OrderOfStrings.Count() - 2), count = rand.Next(2, fittestSequence.OrderOfStrings.Count - range - 1), index = range;
            foreach (string str in fittestSequence.OrderOfStrings.GetRange(range,
                                                                           count))
            {
                stringArray[index] = str;
                if(index != range)
                {
                    pathArray[index - 1] = new Path(stringArray[index - 1],
                                                    stringArray[index],
                                                    equations.GetWeight(stringArray[index - 1],
                                                                        stringArray[index]));
                }
                index++;
            }
            index = 0;
            foreach (string str in secondFittestSequence.OrderOfStrings)
            {
                if (!stringArray.Contains(str))
                {
                    while(stringArray[index] != null)
                    {
                        if(index == 0)
                        {
                            index++;
                        }
                        else if(pathArray[index - 1] == null)
                        {
                            pathArray[index - 1] = new Path(stringArray[index - 1],
                                                        stringArray[index],
                                                        equations.GetWeight(stringArray[index - 1],
                                                                            stringArray[index]));
                            index++;
                        }
                        else
                        {
                            index++;
                        }
                    }
                    stringArray[index] = str;
                    if (index != 0)
                    {
                        pathArray[index - 1] = new Path(stringArray[index - 1],
                                                        stringArray[index],
                                                        equations.GetWeight(stringArray[index - 1],
                                                                            stringArray[index]));
                    }
                    index++;
                    if(index == secondFittestSequence.OrderOfStrings.Count())
                    {
                        index = 0;
                    }
                }
            }
            childSupersequence.OrderOfStrings = stringArray.ToList();
            childSupersequence.Paths = pathArray.ToList();
            return childSupersequence;
        }

        /// <summary>
        /// Mutation randomly swaps two genomes
        /// </summary>
        /// <param name="supersequence"></param>
        /// <returns></returns>
        public Supersequence MutationFunction(Supersequence supersequence)
        {
            int random1 = rand.Next(supersequence.OrderOfStrings.Count() - 2), random2 = rand.Next(supersequence.OrderOfStrings.Count() - 2);
            supersequence.OrderOfStrings = SwapStrings(supersequence.OrderOfStrings,
                                                       random1,
                                                       random2);
            if(random1 + 1 == random2)
            {
                supersequence.Paths[random1] = new Path(supersequence.Paths[random2].String1,
                                                        supersequence.Paths[random1].String1,
                                                        equations.GetWeight(supersequence.Paths[random2].String1,
                                                                            supersequence.Paths[random1].String1));
            }
            else
            {
                string tempString1 = supersequence.Paths[random1].String1;
                supersequence.Paths[random1] = new Path(supersequence.Paths[random2].String1,
                                                        supersequence.Paths[random1].String2,
                                                        equations.GetWeight(supersequence.Paths[random2].String1,
                                                                            supersequence.Paths[random1].String2));
                supersequence.Paths[random2] = new Path(tempString1,
                                                        supersequence.Paths[random2].String2,
                                                        equations.GetWeight(tempString1,
                                                                            supersequence.Paths[random2].String2));
            }

            supersequence.Weight = equations.GetSuperWeight(supersequence.Paths);
            return supersequence;
        }

        /// <summary>
        /// Swap function for mutaion
        /// </summary>
        /// <param name="strings"></param>
        /// <param name="indexA"></param>
        /// <param name="indexB"></param>
        /// <returns></returns>
        public List<string> SwapStrings(List<string> strings, int indexA, int indexB)
        {
            string tmp = strings[indexA];
            strings[indexA] = strings[indexB];
            strings[indexB] = tmp;
            return strings;
        }

        /// <summary>
        /// Funtion to randomly generate and populate a new generation
        /// </summary>
        /// <param name="strings"></param>
        /// <param name="population"></param>
        /// <returns></returns>
        public List<Supersequence> GenerateGeneration(List<string> strings, double population)
        {
            List<Supersequence> generation = new List<Supersequence>();
            for (int i = 0; i < population; i++)
            {
                Supersequence supersequence = new Supersequence(0, string.Empty, new List<string>(), new List<Path>());

                // Create random paths for the generation
                for (int count = strings.Count(); count > 0; count--)
                {
                    int random = rand.Next(strings.Count());
                    supersequence.OrderOfStrings.Add(strings[random]);
                    strings.Remove(strings[random]);
                    if(supersequence.OrderOfStrings.Count() > 1)
                    {
                        supersequence.Paths.Add(new Path(supersequence.OrderOfStrings[supersequence.OrderOfStrings.IndexOf(supersequence.OrderOfStrings.Last()) - 1],
                                                supersequence.OrderOfStrings[supersequence.OrderOfStrings.IndexOf(supersequence.OrderOfStrings.Last())],
                                                equations.GetWeight(supersequence.OrderOfStrings[supersequence.OrderOfStrings.IndexOf(supersequence.OrderOfStrings.Last()) - 1],
                                                                    supersequence.OrderOfStrings[supersequence.OrderOfStrings.IndexOf(supersequence.OrderOfStrings.Last())])));
                    }
                }

                // Add the strings back to strings
                foreach (string str in supersequence.OrderOfStrings)
                {
                    strings.Add(str);
                }

                //Add to generation
                generation.Add(supersequence);
            }
            return generation;
        }
    }
}
