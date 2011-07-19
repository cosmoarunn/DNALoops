/*
 * Entity.h
 *
 *  Created on: Jul 17, 2011
 *      Author: grosner
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "Includes.h"
#include "boost/foreach.hpp"
#include "boost/filesystem.hpp"
#include "boost/format.hpp"
#include <unistd.h>
#include "stdlib.h"						// For system() calls
using namespace boost::filesystem;

class Entity {
public:

	// Construction and destruction
	Entity();
	virtual ~Entity();

	// Setters
	void add_child(Entity *child);
	void set_parent(Entity *parent);
	void set_name(string name);

	// Getters
	vector<Entity*> get_child_vector() const;
	Entity*         get_parent();
	string			get_name() const;

	// Model-Specific getters
	// TODO: Resolve circular imports ???, allow vector<Atom*> ???
	void get_atoms(vector<Entity*> &atoms);
	void get_residues(vector<Entity*> &residues);

	// Statistics
	int n_children() const;
	int n_atoms()    const;

	// Output methods
	friend ostream &operator<<(ostream &out, const Entity &e);

	// To handle default arguments and make things prettier, never call this
	// directly, always use the pure to_pdb() method to generate PDB files!
	void           write_pdb(string filelocation);
	virtual void   as_pdb(int &chain_count, int &residue_count, int &atom_count, ofstream &pdbfile) {};

	// Operator Methods
	// Get i'th child
	//Entity operator[](int i);

	void run_x3dna();

	bool   is_bottom;
	bool   is_top;

private:

	// Integer denoting the ID of the parent, which will be used in the Foreign
	// Key to the parent. Since Loop objects do not have a parent, ensure this
	// is left to zero.
	int pk;

	// Integer ID denoting this Entity for the DB
	int id;

	// A human readable name of the Entity. Defaults to empty string
	string m_name;

	// Vector to hold references to all the child objects to the parent
	vector<Entity*> m_children;

	// The parent reference
	Entity* m_parent;

	// A vector of all the bottom-level atom elements
	vector<Entity*> atom_vector;
};

#endif /* ENTITY_H_ */
