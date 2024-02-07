#ifndef _HISTORY_HPP_
#define _HISTORY_HPP_

#include <iomanip>
#include <iostream>
#include <string>

#include "Transaction.hpp"

class History {
public:
	// Constructor
	//
	History();

	// Destructor.
	//
	~History();

	// Insert transaction into linked list.
	//
	void insert(Transaction *p_new_trans);

	// Read the transaction history from file.
	//
	void read_history();

	// Print the transaction history.
	//
	void print();
	
	// Sort using insertion sort.
	//
	void sort_by_date();

	// Update the acb members in the linked list.
	//
	void update_acb_cgl();

	// Compute the ACB, and CGL.
	//
	double compute_cgl(unsigned int year);

	Transaction *get_p_head();

private:
	Transaction *p_head;
};

#endif
