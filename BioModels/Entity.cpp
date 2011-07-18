/*
 * Entity.cpp
 *
 *  Created on: Jul 17, 2011
 *      Author: grosner
 */

#include "Entity.h"

// Construction and destruction
Entity::Entity() {
	pk = 0;
	m_name = "NO NAME";
	is_bottom = false;
	is_top = false;
}

Entity::~Entity() {
	// TODO Auto-generated destructor stub
}

// Setters
void Entity::add_child(Entity *child) {
	m_children.push_back(child);
}
;

void Entity::set_parent(Entity *parent) {
	m_parent = parent;
}
;

void Entity::set_name(string name) {
	m_name = name;
}

// Getters
vector<Entity*> Entity::get_child_vector() {
	return m_children;
}

Entity* Entity::get_parent() {
	return m_parent;
}

string Entity::get_name() const {
	return m_name;
}

// Model-Specific getters
vector<Entity*> Entity::get_atoms() {
	foreach(Entity *e, get_child_vector())
				{
					if (e->is_bottom) {
						atom_vector.push_back(e);
					} else {
						e->get_atoms();
					}
				}
	return atom_vector;
}

// Statistics
int Entity::n_children() const {
	return m_children.size();
}

int Entity::n_atoms() const {
	return 1;//get_atoms().size();
}

// Output methods
// Use the subclass to handle output
ostream& operator<<(ostream &out, const Entity &e) {
	out << e.n_atoms() << " in " << e;
	return out;
}
