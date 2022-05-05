using System;
using System.Collections.Generic;
using System.Text;

namespace TSP
{
    /// <summary>
    /// City object
    /// </summary>
    class City
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
        /// Gets and sets the city that it is connected to the current city
        /// </summary>
        public List<City> NextCities { get; set; }

        /// <summary>
        /// Constructor
        /// </summary>
        public City(string name, double xCoordinate, double yCoordinate, List<City> nextCities)
        {
            this.Name = name;
            this.XCoordinate = xCoordinate;
            this.YCoordinate = yCoordinate;
            this.NextCities = nextCities;
        }

        /// <summary>
        /// Hard codes predetermined paths for the city, this is for project 2 which only has one test case with 11 cities
        /// </summary>
        /// <param name="city"></param>
        /// <param name="cities"></param>
        /// <returns></returns>
        public City HardCodePath(City city, List<City> cities)
        {
            switch (city.Name)
            {
                case "1":
                    city.NextCities.Add(cities[1]);
                    city.NextCities.Add(cities[2]);
                    city.NextCities.Add(cities[3]);
                    break;
                case "2":
                    city.NextCities.Add(cities[2]);
                    break;
                case "3":
                    city.NextCities.Add(cities[3]);
                    city.NextCities.Add(cities[4]);
                    break;
                case "4":
                    city.NextCities.Add(cities[4]);
                    city.NextCities.Add(cities[5]);
                    city.NextCities.Add(cities[6]);
                    break;
                case "5":
                    city.NextCities.Add(cities[6]);
                    city.NextCities.Add(cities[7]);
                    break;
                case "6":
                    city.NextCities.Add(cities[7]);
                    break;
                case "7":
                    city.NextCities.Add(cities[8]);
                    city.NextCities.Add(cities[9]);
                    break;
                case "8":
                    city.NextCities.Add(cities[8]);
                    city.NextCities.Add(cities[9]);
                    city.NextCities.Add(cities[10]);
                    break;
                case "9":
                    city.NextCities.Add(cities[10]);
                    break;
                case "10":
                    city.NextCities.Add(cities[10]);
                    break;
                case "11":
                    break;
                default:
                    break;
            }
            return city;
        }
    }
}
