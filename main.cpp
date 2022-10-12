/*----------------------------------------------------------------------------------------*/
/* Name: Aditya Pandhare, Student Number: N17706593 */
/* Date: October 18, 2021. */
/* Program: Assignment 2 - Flight Simulator Wind Speed.cpp */
/* Description: This program computes Wind Speeds, Storm Speeds and Burst Speeds. */
/*----------------------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

//These are all of the function prototypes. The arrays are all generated from the simulationConfiguration.txt file. They don't have a const on them as there aren't any operations on the elements in these arrays, thus they aren't subject to change. They are mainly used for logical expressions for other operations.
void loadConfiguration();
void generateWindSpeedData(double wind[], int size);
void generateStormData(double wind[], int size, double storm[], int size2);
void generateBurstData(double wind[], int size, double burst[], int size3);
void saveToFile(double wind[], int size);

int main() {
    cout << "Welcome to Wind Speed Simulator!" << endl;
    loadConfiguration(); //This calls the loadConfiguration function.
    
    cout << "\n";
    cout << "Wind Simulation completed!" << endl;
    cout << "Please open WindSimulation.txt in your directory to view your data!" << endl;
    cout << "\n";
    
    return(0);
}

//The purpose of the function below is to read all of the configurations from the simulationConfiguration.txt file and store them into respective arrays. These arrays can then be passed to the desired function which is much more convenient that passing multiple variables through the other functions.
void loadConfiguration() {
    
    ifstream config;
    config.open("simulationConfiguration.txt", ios::in); //Creates an ifstream and reads in data from simulationConfiguration.txt.
    
    if (config.fail()) {
        cout << "simulationConfiguration File could not be opened." << endl;
        exit (1);
    }
    
    //These are all the variables which will initialized from the data in simulationConfiguration.txt and then they will be set into their respective arrays as shown in lines 48-50.
    double avg_wind_speed, gust_value, wind_dur, step_size;
    double storm_prob, s_min_amp, s_max_amp, s_min_dur, s_max_dur;
    double burst_prob, b_min_amp, b_max_amp, b_min_dur, b_max_dur;
    
    int windsize(4), sbsize(5); //windsize is the size of WindSpeedData array and sbsize (storm, burst size) is the size of the Storm and Burst Data arrays. Both of them are already initialized to their respective sizes.
    
    config >> avg_wind_speed >> gust_value >> wind_dur >> step_size;
    config >> storm_prob >> s_min_amp >> s_max_amp >> s_min_dur >> s_max_dur;
    config >> burst_prob >> b_min_amp >> b_max_amp >> b_min_dur >> b_max_dur;
    
    double WindSpeedData[4] = {avg_wind_speed, gust_value, wind_dur, step_size};
    double StormData[5] = {storm_prob, s_min_amp, s_max_amp, s_min_dur, s_max_dur};
    double BurstData[5] = {burst_prob, b_min_amp, b_max_amp, b_min_dur, b_max_dur};
    
    generateWindSpeedData(WindSpeedData, windsize); //This calls the generateWindSpeedData function with the WindSpeedData array and its size which is 4.
    generateStormData(WindSpeedData, windsize, StormData, sbsize);//This calls the generateStormData function with the StormData array and its size which is 5.
    generateBurstData(WindSpeedData, windsize, BurstData, sbsize);//This calls the generateBurstData function with the BurstData array and its size which is 4.
    saveToFile(WindSpeedData, windsize); //This calls the saveToFile function with the WindSpeedData array and its size which is 4.
    
    config.close();
}

//The purpose of this function is to generate WindSpeedData. We have parameters from the WindSpeedData array and its size as we will need the configurations from this array to execute this function.
void generateWindSpeedData(double wind[], int size) {
    
    ofstream windspeeddata;
    windspeeddata.open("WindSpeedData.txt", ios::out); //We create a file known as WindSpeedData.txt and we set it to out so we can read all of the windspeed data onto this file.
    
    if (windspeeddata.fail()) {
        cout << "WindSpeedData File could not be opened." << endl;
        exit (1);
    }
    
    double a, b;
    
    a = wind[0] - wind[1]; //This is the minimum windspeed value.
    b = wind[0] + wind[1]; //This is the max windspeed value.
    
    srand((unsigned int)time(NULL));
    
    //This is a for loop which sets a counter, while this counter is less than total duration of the windspeed, it will write on WindSpeedData.txt, the time and a randomly generated number between the min and max windspeed values (between a and b). Then it will increment i based on the step size.
    for (int i = 0; i <= wind[2]; i += wind[3]) {
        windspeeddata << setw(10) << left << i << "  " << setw(10) << left << ((double)rand()/RAND_MAX)*(b-a)+a << endl;
    }
    
    windspeeddata.close();
}

//The purpose of this function is to generate StormData. We have parameters from the WindSpeedData array and its size as well as the StormData array and its size as we will need the configurations from this array to execute this function.
void generateStormData(double wind[], int size, double storm[], int size2) {
    
    ofstream stormdata;
    stormdata.open("StormData.txt", ios::out); //We create a file known as StormData.txt and we set it to out so we can read all of the storm data onto this file.
    
    if (stormdata.fail()) {
        cout << "StormData File could not be opened." << endl;
        exit (1);
    }
    
    double amp, dur, prob; //We have 3 new variables, amp which is the randomly generated storm ampltiude, dur which is the randomly genereated storm duration, prob which is the probability of a storm occuring.
    srand((unsigned int)time(NULL));
 
    //This for loop generates a random number between 0-100 for prob and a random number between the min and max storm duration values into dur at each time step. It also checks that is the randomly generated number in prob is between the storm probability value from the configuration, it will execute another loop.
    for(int i=0; i <= wind[2]; i+= wind[3]) {
        prob = ((double)rand()/RAND_MAX)*(101);
        dur = (((double)rand()/RAND_MAX)*(storm[4] - storm[3]))+storm[3];
        
        if(prob > storm[0]) { //If the randomly generated prob is not within the storm probability, there will be no storm, thus the storm speed will be written out as 0 on StormData.txt.
            stormdata << setw(10) << left << i << "  " << setw(10) << left << 0 << endl;
        }
        
        else if(prob >= 0 && prob <= storm[0]) { //Otherwise if the randomly generated prob is within the storm proability, it generates random numbers for the storm amplitude (between the min and max storm ampltiude values from the configuration) at each time step for the duration dur.
            int k = i;
            
            while(i <= k + dur && i <= wind[2]){
                amp = ((double)rand()/RAND_MAX)*(storm[2] - storm[1])+storm[1];
                stormdata << setw(10) << left << i << "  " << setw(10) << left << amp << endl;
                i += wind[3];
            }
        }
    }
    
    stormdata.close();
}

//The purpose of this function is to generate BurstData. We have parameters from the WindSpeedData array and its size as well as the BurstData array and its size as we will need the configurations from this array to execute this function.
void generateBurstData(double wind[], int size, double burst[], int size3) {
    
    ifstream stormdata;
    stormdata.open("StormData.txt", ios::in); //We create a file known as StormData.txt and we set it to out so we can read all of the storm data onto this file.
    
    if (stormdata.fail()) {
        cout << "StormData File could not be opened." << endl;
        exit (1);
    }
    
    ofstream burstdata;
    burstdata.open("BurstData.txt", ios::out); //We create a file known as BurstData.txt and we set it to out so we can read all of the burst data onto this file.
    
    if (burstdata.fail()) {
        cout << "BurstData File could not be opened." << endl;
        exit (1);
    }
    
    double amp, dur, prob;
    double t, storminfo;
    srand((unsigned int)time(NULL));
 
    // This is essentially the same code as generateStormData() but applied to Burst Data configurations.
    for(int i=0; i <= wind[2]; i+= wind[3]) {
        stormdata >> t >> storminfo;
        
        if(storminfo == 0){ //This reads storm data and checks whether it is active. If it isn't a microburst won't occur. If there is it will.
            burstdata << setw(10) << left << i << "  " << setw(10) << left << 0 << endl;
        }
        
        else if(storminfo > 0){
            prob = ((double)rand()/RAND_MAX)*(101);
            dur = ((double)rand()/RAND_MAX)*(burst[4] - burst[3])+burst[3];
        
            if(prob > burst[0]) {
                burstdata << setw(10) << left << i << "  " << setw(10) << left << 0 << endl;
            }

            else if(prob >= 0 && prob <= burst[0]) {
                int k = i;
            
                while(i <= k + dur && i <= wind[2]){
                    amp = ((double)rand()/RAND_MAX)*(burst[2] - burst[1])+burst[1];
                    burstdata << setw(10) << left << i << "  " << setw(10) << left << amp << endl;
                    i += wind[3];
            }
        }
        }
    }
   
    burstdata.close();
}

//The purpose of this function is to read all of the data from the WindSpeedData.txt, StormData.txt and BurstData.txt files, add them up together and write them all into a newly generated file known as WindSimulation.txt.
//For this function, we also need the parameters from the WindSpeedData array and its size for logical expressions while executing loops.
void saveToFile(double wind[], int size) {
    
    ifstream winddata;
    winddata.open("WindSpeedData.txt", ios::in); //Reads in data from WindSpeedData.txt.
    
    if(winddata.fail()) {
        cout << "WindSpeedData File failed to open" << endl;
        exit(1);
    }
    
    ifstream stormdata;
    stormdata.open("StormData.txt", ios::in); //Reads in data from StormData.txt.
    
    if(stormdata.fail()) {
        cout << "StormData File failed to open" << endl;
        exit(1);
    }
    
    ifstream burstdata;
    burstdata.open("BurstData.txt", ios::in); //Reads in data from BurstData.txt.
    
    if(burstdata.fail()) {
        cout << "BurstData File failed to open" << endl;
        exit(1);
    }
    
    ofstream windsimulation;
    windsimulation.open("WindSimulation.txt", ios::out); //Writes on new data to a new generated file WindSimulation.txt.
    
    if(windsimulation.fail()) {
        cout << "WindSimulation File failed to open" << endl;
        exit(1);
    }

    double time, windinfo, storminfo, burstinfo;
    
    //Here we read data from all 3 files and add them up (overlap the data) and this is written onto the new file WindSimulation.txt. This loop ensures that we do this until it reaches the duration of the whole dataset, while incrementing it via the step size.
    for(int i=0; i <= wind[2]; i+= wind[3]) {
        winddata >> time >> windinfo;
        stormdata >> time >> storminfo;
        burstdata >> time >> burstinfo;
        
        //This if statement tells us that there is no storm or burst since the combined wind information is less than the max average wind speed. Thus, we print out the time and wind information as well as a 0 to indicate there is no storm/burst.
        if(windinfo+storminfo+burstinfo <= (wind[0]+wind[1])) {
            windsimulation << setw(10) << left << i << "  " << setw(10) << left << (windinfo+storminfo+burstinfo) << setw(10) << left << 0 << endl;
        }
        
        //This else if statement tells us that there is a storm or burst since the combined wind information is greater than the max average wind speed. Thus, we print out the time and wind information as well as a 1 to indicate there is a storm/burst.
        else if(windinfo+storminfo+burstinfo > (wind[0]+wind[1])) {
            windsimulation << setw(10) << left << i << "  " << setw(10) << left << (windinfo+storminfo+burstinfo) << setw(10) << left << 1 << endl;
        }
    }
    winddata.close();
    stormdata.close();
    burstdata.close();
    windsimulation.close();
}
