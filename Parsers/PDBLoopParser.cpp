/*
 * PDBLoopParser.cpp
 *
 *  Created on: Jul 16, 2011
 *      Author: Michael Grosner*/

#include "PDBLoopParser.h"

PDBLoopParser::PDBLoopParser(string model_directory) : m_directory(model_directory) {
	m_loop.set_name(m_directory.stem());
}

PDBLoopParser::PDBLoopParser(char*  model_directory) : m_directory(model_directory) {
	m_loop.set_name(m_directory.stem());
}

PDBLoopParser::PDBLoopParser(path   model_directory) : m_directory(model_directory) {
	m_loop.set_name(m_directory.stem());
}

PDBLoopParser::~PDBLoopParser() {
	// TODO Auto-generated destructor stub
}

Loop PDBLoopParser::parse() {

	directory_iterator end_itr;

	// TODO: Raise an exception
	//if (!exists(p)) return false;

	for (directory_iterator itr(m_directory); itr != end_itr; itr++) {
		// If this is a file,
		if (is_regular_file(itr->path()) && itr->path().extension() == ".pdb") {
			// m_filepaths is unneeded
			m_filepaths.push_back(itr->path());
			parse_single_pdb_file(itr->path().string());
		}
	}

	return m_loop;

}

void PDBLoopParser::parse_single_pdb_file(string pdb_filename) {

	// Open the file stream
	ifstream ifs;
	ifs.open(pdb_filename.c_str());
	string line;

	// Since some of the PDB files may have multiple Structures inside (i.e.
	// two HUs) seperated by a TER line, need to return multiple Structures
	Structure *s = new Structure(pdb_filename);
	Chain     *c = new Chain();
	Residue   *r = new Residue();
	Atom      *a = new Atom();

	// Save the previous Residue and Chain PDB IDs to compare and decide whether
	// or not a new one needs to be made.
	int    r_id_prev = 0;
	string c_id_prev = "";
	bool   make_new  = false;

	string atom("ATOM");
	string ter("TER");

	while( getline(ifs, line) ) {

		if (line.empty()) continue;

		if (make_new) {
			s = new Structure(pdb_filename);
			make_new = false;
		}

		if (line.compare(0, atom.length(), atom) == 0) {

			// Information in PDB files follow strict column sizes. This may
			// not be very robust, but works fine with my PDB files.
			//int a_id      = atoi(line.substr(6,5).c_str());
			string a_name = line.substr(13,3);
			string r_name = boost::trim_copy(line.substr(17,3));
			string c_id   = line.substr(21,1);
			int r_id      = atoi(line.substr(23,3).c_str());

			double x = atof(line.substr(31,7).c_str());
			double y = atof(line.substr(38,7).c_str());
			double z = atof(line.substr(46,7).c_str());

			// If an Entity has a different ID than the one before,
			if (c_id_prev.compare(c_id) != 0) {
				c = new Chain(c_id);		// Create a new chain with new ID
				s->add_child(c);			// Attach to parent Entity
				c_id_prev = c_id;			// Keep track of new ID
			}
			if (r_id_prev != r_id) {
				r = new Residue(r_name, r_id);
				c->add_child(r);
				r_id_prev = r_id;
			}

			// Every line should contain a new atom, then attach it to a residue
			a = new Atom(a_name, x, y, z);
			r->add_child(a);

		}

		/* If a TER comes in the file, denoting multiple structures in the PDB,
		   add the previously parsed structure to the vector which will be
		   loaded into the loop, then start a new structure. If the TER is before
		   the EOF, an empty Structure will be created
		   TODO: Ensure that the empty structure does not get committed to DB */
		else if (line.compare(0, ter.length(), ter) == 0) {
			if (DEBUG) {
				cout << "Pushing back " << *s << endl;
			}
			m_loop.add_child(s);
			make_new = true;
		}
	}

	// If no TER at the EOF, add the structure
	if ( (s->get_child_vector().size() != 0) && !make_new ) {
		if (DEBUG) {cout << "Pushing back " << *s << endl;}
		m_loop.add_child(s);
	}

}
