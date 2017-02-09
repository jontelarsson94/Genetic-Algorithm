//
//  main.cpp
//  TravelingSalesman
//
//  Created by Jonathan Larsson on 2017-02-07.
//  Copyright © 2017 Jonathan Larsson. All rights reserved.
//

#include <iostream>
#include "Initializer.cpp"
#include <math.h>
using namespace std;

int travelingSalesman(int **population, int numToFinish);
float calculateDistance(City one, City two);
float calculateFitness(int cityIds[]);
int* mutateIndividual(int individual[]);
bool inArray(int arr[], int holdNum, int num);
int* crossover(int parentOne[], int parentTwo[]);
void setProbability(float* probability, float* fitness);
void pickByProbability(float* probability, int *parentOne, int *parentTwo);
float calculateRouteDistance(int cityIds[]);
void setNewPopulation(int *child, int **population, float *fitness);
int findFittest(float *fitness);

const int mutationProbability = 100;
const int numberOfCities = 52;
const int populationSize = 750;
const int numToFinish = 100000;
City *cities;

int main(int argc, const char * argv[]) {
    
    srand (time(NULL));
    
    Initializer init;
    
    cities = init.readCitiesFromFile("Berlin52.txt", numberOfCities);
    
    int **population = init.initializeIndividuals(numberOfCities, populationSize);
    
    int fittest = travelingSalesman(population, numToFinish);
    
    float routeDistance = calculateRouteDistance(population[fittest]);
    
    cout << "The routelength is: " << routeDistance << endl;
    cout << "Through the cities with id: " << endl;
    
    for(int i = 0; i < numberOfCities; i++) {
        cout << population[fittest][i] << " -> ";
    }
    cout << population[fittest][0] << endl;
    
    return 0;
}

int travelingSalesman(int **population, int numToFinish)
{
    float *fitness = new float[populationSize];
    
    float *probability = new float[populationSize];
    
    int parentOne, parentTwo;
    int loops = 0;
    
    for(int i = 0; i < populationSize; i++) {
        fitness[i] = calculateFitness(population[i]);
    }

    int fittest = findFittest(fitness);
    int gen = 0;
    while(loops < numToFinish) {
        
        setProbability(probability, fitness);
        
        pickByProbability(probability, &parentOne, &parentTwo);
        
        int *child = crossover(population[parentOne], population[parentTwo]);
        
        mutateIndividual(child);
        
        setNewPopulation(child, population, fitness);
        
        int newFittest = findFittest(fitness);
        
        if(fittest == newFittest) {
            loops++;
        } else {
            loops = 0;
            fittest = newFittest;
            cout << calculateRouteDistance(population[fittest]) << endl;
        }
        gen++;
    }
    cout << "Number of generations: " << gen << endl;
    return fittest;
}

int findFittest(float *fitness)
{
    int fittest = 0;
    float fittestFitness = fitness[0];
    for(int i = 1; i < populationSize; i++) {
        if(fitness[i] > fittestFitness){
            fittest = i;
            fittestFitness = fitness[i];
        }
    }
    return fittest;
}

float calculateDistance(City one, City two)
{
    return sqrt((pow (two.x-one.x, 2.0))+(pow(two.y-one.y, 2.0)));
}

float calculateFitness(int cityIds[])
{
    float fitness = 0.0;
    
    for(int i = 0; i < numberOfCities-1; i++) {
        fitness += calculateDistance(cities[cityIds[i]], cities[cityIds[i+1]]);
    }
    
    fitness += calculateDistance(cities[cityIds[numberOfCities-1]], cities[cityIds[0]]);
    
    
    return 1/fitness;
}

float calculateRouteDistance(int cityIds[])
{
    float distance = 0.0;
    
    for(int i = 0; i < numberOfCities-1; i++) {
        distance += calculateDistance(cities[cityIds[i]], cities[cityIds[i+1]]);
    }
    
    distance += calculateDistance(cities[cityIds[numberOfCities-1]], cities[cityIds[0]]);
    
    
    return distance;
}

int* mutateIndividual(int individual[])
{
    
    int willHappen = rand() % 100;
    
    if(willHappen < mutationProbability){
        int pos1 = rand() %  (numberOfCities-1) + 1;
        int pos2 = rand() %  (numberOfCities-1) + 1;
    
        int hold = individual[pos1];
    
        individual[pos1] = individual[pos2];
        individual[pos2] = hold;
    }
    
    return individual;
}

bool inArray(int arr[], int holdNum, int num)
{
    for(int i = 0; i < holdNum; i++) {
        if(arr[i] == num)
            return true;
    }
    return false;
}

int* crossover(int parentOne[], int parentTwo[])
{
    
    int pos2 = rand() %  (numberOfCities-1) + 1;
    int pos1 = rand() %  (numberOfCities-1) + 1;
    if(pos1 > pos2) {
        int hold = pos1;
        pos1 = pos2;
        pos2 = hold;
    }
    int holdNum = pos2-pos1;
    
    int *child = new int[numberOfCities];
    
    int holdArr[holdNum];
    
    for(int i = pos1, j = 0; i < pos2; i++, j++) {
        child[i] = parentOne[i];
        holdArr[j] = parentOne[i];
    }
    
    int current = 0;
    for(int i = 0; i < pos1; i++) {
        if(parentTwo[current]){
            while(inArray(holdArr, holdNum, parentTwo[current])){
                current++;
            }
        }
        child[i] = parentTwo[current];
        current++;
    }
    
    for(int i = pos2; i < numberOfCities; i++) {
        while(inArray(holdArr, holdNum, parentTwo[current])) {
            current++;
        }
        child[i] = parentTwo[current];
        current++;
    }

    return child;
}

void setProbability(float* probability, float* fitness)
{
    float totalFitness = 0.0;
    for(int i = 0; i < populationSize; i++) {
        totalFitness += fitness[i];
    }
    
    for(int i = 0; i < populationSize; i++) {
        probability[i] = fitness[i] / totalFitness;
    }
}

void pickByProbability(float* probability, int *parentOne, int *parentTwo)
{
    
    float first[populationSize];
    float second[populationSize];
    
    float start = 0.0;
    
    for(int i = 0; i < populationSize; i++) {
        first[i] = start;
        second[i] = start+probability[i];
        start += probability[i];
    }
    
    float firstRand = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float secondRand = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    
    for(int i = 0; i < populationSize; i++) {
        int same = false;
        if(firstRand > first[i] && firstRand <= second[i]){
            *parentOne = i;
            same = true;
        }
        if(secondRand > first[i] && secondRand <= second[i]){
            if(!same)
                *parentTwo = i;
            else
                secondRand = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        }
    }
}

void setNewPopulation(int *child, int **population, float *fitness)
{
    int worst = 0;
    float worstFitness = fitness[0];
    float childFitness = calculateFitness(child);
    for(int i = 1; i < populationSize; i++) {
        if(fitness[i] < worstFitness) {
            worstFitness = fitness[i];
            worst = i;
        }
    }
    
    if(childFitness > worstFitness){
        population[worst] = child;
        fitness[worst] = childFitness;
    }
}




