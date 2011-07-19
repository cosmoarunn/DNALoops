/*
 * StepParameter.h
 *
 *  Created on: Jul 16, 2011
 *      Author: grosner
 */

#ifndef STEPPARAMETER_H_
#define STEPPARAMETER_H_

#include "Includes.h"
#include "BioModels/Entity.h"

class StepParameterEntity : public Entity, public StepParameters {
public:
	StepParameterEntity();
	virtual ~StepParameterEntity();

	void   as_pdb(int &chain_count, int &residue_count, int &atom_count, ofstream &pdbfile) {};
};

#endif /* STEPPARAMETER_H_ */
