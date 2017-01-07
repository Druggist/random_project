#ifndef INSTANCE_H
#define INSTANCE_H

#include "task.h"
#include "maitenance.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>

using std::cerr;
using std::vector;
using std::endl;
using std::fstream;
using std::string;
using std::ofstream;
class Instance{
	int id, tasks_number;
public:
	vector<Task> task_v;
	vector<Maitenance> maitenance_v;
private:
	void clear_task_v();
	void clear_maitenance_v();
public:
	void generate_instance(int, int, int, bool);
	void dump_instance(string);
	void read_instance(string);
	//void set_id(int);
	//void set_task_number(int);
	void clear_all();
	void print_taks_v();
};

#endif // INSTANCE_H
