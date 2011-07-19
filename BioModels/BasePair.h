/*
 * BasePair.h
 *
 *  Created on: Jul 16, 2011
 *      Author: grosner
 */

#ifndef BASEPAIR_H_
#define BASEPAIR_H_

#include "Includes.h"
#include "BioModels/Entity.h"
#include "BioModels/Loop.h"
#include <assert.h>

class BasePairEntity: public Entity, public BasePair {
public:

	// BasePairEntitys should not be called by the blank constructor. Instead,
	// They should use the crazy constructor below to load the BasePair super
	// class method beforehand to take advantage of the DNASim libary's methods.
	BasePairEntity();
	virtual ~BasePairEntity();

	BasePairEntity(const vector<int>& pairing, const int& position, const string& bp1,
			const string& bp2, const CoordinateSystem& coords, Loop& l);

	void as_pdb(int &chain_count, int &residue_count, int &atom_count,
			ofstream &pdbfile) {}

	// Output methods
	friend ostream &operator<<(ostream &out, const BasePairEntity &bp);

private:
	int strand_position;

	string base1;
	string base2;

};

#endif /* BASEPAIR_H_ */
