# Wind-Speed-Data-Representation
This is a program that generates a computer simulation of windspeed for a flight simulator. Assume that the wind speed for a particular region can be modeled by using an average value and a gust value that is added to the average. For example, the wind speed might be 10 miles per hour, with added noise (which represents gusts) of 5 miles per hour, the wind speed would be a value between 5 and 15 (10 ± 5).

The wind speed simulation must include storm simulation. Assuming that the possibility of encountering a storm at each time step is Pstorm, the program must add a storm magnitude (a random number between the minimum and maximum storm amplitude values) to the simulated wind speed for a duration T (a random number between the minimum and maximum storm duration).Same logic would apply to Microburst wind speeds. 

For the SimulationConfiguration.txt, the values in the txt file are represented as: 
- Avg Wind Speed, Gust Value, Simulation duration, Step size
- Storm Probability(Pstorm), min and max storm amplitude, max and min storm duration
- Microburst probability (Pburst), min and max microburst ampltide, max and min microburst duration. 

