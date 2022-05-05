using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;

using SCS.Objects;

namespace SCS
{
    static class Program
    {
        #region Constants

        #endregion

        /// <summary>
        /// Main function, contains wisdom of crowds logic at the bottom
        /// </summary>
        /// <param name="args"></param>
        static void Main(string[] args)
        {
            #region Constants

            BruteForce bruteForce = new BruteForce();

            GeneticAlgorithm geneticAlgorithm = new GeneticAlgorithm();

            Equations equations = new Equations();

            List<Supersequence> generation = new List<Supersequence>(), crowds = new List<Supersequence>();

            List<Path> pathsFromCrowds = new List<Path>();

            List<string> strings = new List<string>();

            Supersequence bestSupersequence = new Supersequence(0, string.Empty, new List<string>(), new List<Path>()),
                          currentSubsequence = new Supersequence(0, string.Empty, new List<string>(), new List<Path>());

            string line;

            int population = 50, exitCondition = 0;

            double crossoverChance = 1, mutationChance = 0.75;

            #endregion

            //File reader, looks for strings and puts them into a list. Uses direct file address to find txt file so has to be changed if in another directory
            System.IO.StreamReader file = new System.IO.StreamReader(@"C:\Users\phoen\source\repos\AI-Dev\SCS\Input-Text\Test200.txt");
            while ((line = file.ReadLine()) != null)
            {
                strings.Add(line);
            }

            //Bruteforce example
            //foreach (string str in strings)
            //{
            //    List<string> temp = new List<string>();
            //    temp.Add(str);
            //    Supersequence newSupersequence = bruteForce.BruteForceMethod(new List<string>(strings), str, new Supersequence(0, string.Empty, temp, new List<Path>()));
            //    if (newSupersequence.Weight > bestSupersequence.Weight)
            //    {
            //        bestSupersequence = newSupersequence;
            //    }
            //    Console.WriteLine(str);
            //}
            //Console.WriteLine(equations.GetSequence(bestSupersequence));
            //Console.WriteLine(bestSupersequence.Weight);

            // Start of GA, runs this 10 times to get all of the crowds for WofC
            for (int i = 0; i < 10; i++)
            {
                generation = geneticAlgorithm.GenerateGeneration(strings, population);
                bestSupersequence = new Supersequence(0, string.Empty, new List<string>(), new List<Path>());
                exitCondition = 0;
                while (exitCondition < 1000)
                {
                    generation = geneticAlgorithm.GeneticAlgorithmMethod(generation, crossoverChance, mutationChance, out currentSubsequence);
                    if (bestSupersequence.OrderOfStrings.Count() == 0)
                    {
                        bestSupersequence = currentSubsequence;
                    }
                    else if (currentSubsequence.Weight > bestSupersequence.Weight)
                    {
                        bestSupersequence = currentSubsequence;
                    }
                    exitCondition++;
                }
                crowds.Add(bestSupersequence);
            }

            // Start of WofC, here it gathers the most commonly agreed paths
            foreach(Supersequence crowd in crowds)
            {
                foreach (Path path in crowd.Paths)
                {
                    if (pathsFromCrowds.Any(x => x.String1 == path.String1 && x.String2 == path.String2))
                    {
                        int tempIndex = pathsFromCrowds.FindIndex(x => x.String1 == path.String1 && x.String2 == path.String2);
                        pathsFromCrowds[tempIndex].Count++;
                    }
                    else
                    {
                        pathsFromCrowds.Add(path);
                    }
                }
            }

            // Orders the paths to find the most agreed apon one
            pathsFromCrowds = pathsFromCrowds.OrderByDescending(x => x.Count).ThenByDescending(x => x.Weight).ToList();
            int uniqueString1Flag = -1, uniqueString2Flag = -1;
            List<Path> outputPaths = new List<Path>();
            List<List<Path>> uniquePaths = new List<List<Path>>();
            bestSupersequence = new Supersequence(0, string.Empty, new List<string>(), new List<Path>());

            // This is a conviluted way to get all of the paths from the list paths into one path in a way so that it has no loops or repeating string values.
            // In short it uses a list as a kind dictionary to keep track of unique paths while making sure that no value in each unique path is repeated in other paths, unless the paths can merge
            // in which case it will just merge the two paths.
            foreach (Path path in pathsFromCrowds)
            {
                if(uniquePaths.Count() == 0)
                {
                    List<Path> newPath = new List<Path>();
                    newPath.Add(path);
                    uniquePaths.Add(newPath);
                    continue;
                }
                else
                {
                    foreach (List<Path> dictionaryPath in uniquePaths)
                    {
                        if (dictionaryPath.Count() == crowds[0].Paths.Count())
                        {
                            // This is an early exit to make it faster, it does not allways happen though because there is no garantee that all the strings will form one unique path
                            outputPaths = dictionaryPath;
                            goto END;
                        }
                        foreach (Path dicPath in dictionaryPath)
                        {
                            if (dicPath.String1 == path.String1 || dicPath.String2 == path.String2)
                            {
                                goto SKIP;
                            }
                        }
                        if(path.String1 == dictionaryPath.Last().String2 && path.String2 == dictionaryPath.First().String1)
                        {
                            goto SKIP;
                        }
                        else if(path.String1 == dictionaryPath.Last().String2)
                        {
                            uniqueString1Flag = uniquePaths.IndexOf(dictionaryPath);
                        }
                        else if(path.String2 == dictionaryPath.First().String1)
                        {
                            uniqueString2Flag = uniquePaths.IndexOf(dictionaryPath);
                        }
                    }
                }

                if(uniqueString1Flag == -1 && uniqueString2Flag == -1)
                {
                    // Make  a new dictionary path
                    List<Path> newPath = new List<Path>();
                    newPath.Add(path);
                    uniquePaths.Add(newPath);
                }
                else if(uniqueString1Flag != -1 && uniqueString2Flag == -1)
                {
                    // Add to the end of the dictionary path that had ending equal to the begining of this one 
                    uniquePaths[uniqueString1Flag].Add(path);
                }
                else if(uniqueString1Flag == -1 && uniqueString2Flag != -1)
                {
                    // Insert to the begining of the dictionary path that had the start equal to the end of the path
                    uniquePaths[uniqueString2Flag].Insert(0, path);
                }
                else if(uniqueString1Flag != -1 && uniqueString2Flag != -1)
                {
                    // Merge the two dictionary paths that had the same end as the begining of the path and the same beginning as the end of the path
                    uniquePaths[uniqueString1Flag].Add(path);
                    uniquePaths[uniqueString1Flag].AddRange(uniquePaths[uniqueString2Flag]);
                    uniquePaths.RemoveAt(uniqueString2Flag);
                }

                SKIP:;
                uniqueString1Flag = -1;
                uniqueString2Flag = -1;
            }
            END:;

            // In case the unique paths made from string to string do not all connect, in the case of something like
            // ABC->BCE->EDF and UOI->IYZ->ZXP, these two unique paths need to be linked up some how, so this outputPaths area does that
            if(outputPaths.Count() == 0)
            {
                foreach(List<Path> listPaths in uniquePaths)
                {
                    if (outputPaths.Count() == 0)
                    {
                        outputPaths.AddRange(listPaths);
                    }
                    else
                    {
                        outputPaths.Add(new Path(outputPaths.Last().String2,
                                                 listPaths.First().String1,
                                                 equations.GetWeight(outputPaths.Last().String2,
                                                                     listPaths.First().String1)));
                        outputPaths.AddRange(listPaths);
                    }
                }
            }

            foreach(string str in strings)
            {
                foreach(Path checkPath in outputPaths)
                {
                    if (checkPath.String1 == str || outputPaths.Last().String2 == str)
                    {
                        goto OK;
                    }
                }
                outputPaths.Add(new Path(outputPaths.Last().String2,
                                         str,
                                         equations.GetWeight(outputPaths.Last().String2,
                                                             str)));
                OK:;
            }

            bestSupersequence.Paths = outputPaths;
            bestSupersequence.Weight = equations.GetSuperWeight(bestSupersequence.Paths);
            crowds = crowds.OrderByDescending(x => x.Weight).ToList();
            double average = crowds.Average(x => x.Weight);
            if (bestSupersequence.Weight < crowds.Max(x => x.Weight))
            {
                Console.WriteLine("Wisdom of Crowds failed to find a better solution");
            }

            bestSupersequence.Sequence = equations.GetSequence(bestSupersequence);
            Console.WriteLine("The algorithms best sequence");
            Console.WriteLine(bestSupersequence.Sequence);
            Console.WriteLine("Compressed the supersequence down by {0} characters", bestSupersequence.Weight);
            Console.WriteLine("Previous max compression was a decrease of {0} characters", crowds[0].Weight);
        }
    }
}
