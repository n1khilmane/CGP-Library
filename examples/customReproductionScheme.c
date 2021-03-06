/*
	This file is part of CGP-Library
	Copyright (c) Andrew James Turner 2014 (andrew.turner@york.ac.uk)

    CGP-Library is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    CGP-Library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with CGP-Library.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include "../src/cgp.h"

void mutateEveryParent(struct parameters *params, struct chromosome **parents, struct chromosome **children, int numParents, int numChildren){
	
	int i;
	int selectedParent;

	/* for each child */
	for(i=0; i< numChildren; i++){

		selectedParent = i % numParents;

		/* set child as clone of selected parent */
		copyChromosome(children[i], parents[selectedParent]);

		/* mutate newly cloned child */
		mutateChromosome(params, children[i]);
	}	
}

int main(void){
	
	struct parameters *params = NULL;
	struct dataSet *trainingData = NULL;
	struct chromosome *chromo = NULL;
	
	int numInputs = 1;
	int numNodes = 50;
	int numOutputs = 1;
	int arity = 2;
	
	int mu = 4;
	int lambda = 8;
	
	double targetFitness = 0.1;
	int updateFrequency = 1000;
	int numGens = 10000;
	
	params = initialiseParameters(numInputs, numNodes, numOutputs, arity);
	
	addNodeFunction(params, "add,sub,mul,div,sin");
	
	setTargetFitness(params, targetFitness);

    setUpdateFrequency(params, updateFrequency); 
	
	setCustomReproductionScheme(params, mutateEveryParent, "mutateEveryParent");
	
	setMu(params, mu);
	setLambda(params, lambda);
	
	trainingData = initialiseDataSetFromFile("./dataSets/symbolic.data");
	
	chromo = runCGP(params, trainingData, numGens);
	
	freeChromosome(chromo);
	freeDataSet(trainingData);
	freeParameters(params);
	
	return 0;
}


