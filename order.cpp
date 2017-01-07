#include "order.h"

Order::Order(){

}
Order::Order(vector<Task_t> task_m1_v, vector<Task_t> task_m2_v, vector<Maitenance> maitenance_v){
	machine1.set_id(1);
	machine1.set_start(0);
	machine1.set_stop(0);
	machine2.set_id(2);
	int n = 0;
	unsigned int size = (task_m1_v.size() >= task_m2_v.size())?(task_m1_v.size()):(task_m2_v.size());

	for(unsigned int i = 0; i < size; i++){
		if (task_m1_v.size() < i){
			while(!machine1.add(task_m1_v[i+n], maitenance_v)){
				task_m1_v.push_back(task_m1_v[i+n]);
				n++;
			}
			n = 0;
		}

		if (task_m2_v.size() < i){
			if( i == 0 ){
				machine2.set_start(machine1.get_sop());
				machine2.set_stop(machine1.get_sop());
			}

			if(machine1.get_sop() <= machine2.get_sop()) machine2.add(task_m2_v[i], maitenance_v);
			else machine2.addt(machine1.get_sop(), task_m2_v[i]);
		}
	}

	this->exec_t = machine2.get_sop();
}

void Order::initialization(vector<int> O, vector<Task> task_v, vector<Maitenance> maitenance_v){
	machine1.set_id(1);
	machine1.set_start(0);
	machine1.set_stop(0);
	machine2.set_id(2);
	cout<<"machines initialization\n";
	int n, tmp;
	for (unsigned int i = 0; i < O.size(); i++){
		//Machine 1
		n = 1;
		while(!machine1.add(O[i], task_v, maitenance_v)){
			tmp = O[i];
			O[i] = O[i + n];
			O[i + n] = tmp;
			n++;
		}
		// Machine 2
		if( i == 0 ){
			machine2.set_start(machine1.get_sop());
			machine2.set_stop(machine1.get_sop());
		}
		if(machine1.get_sop() <= machine2.get_sop()){
			machine2.add(O[i], task_v, maitenance_v);
		}else{
			machine2.addt(machine1.get_sop(), O[i], task_v);
		}
	}

	this->exec_t = machine2.get_sop();
}

vector<Task_t> Order::get_tasks(int machine_id){
	if (machine_id == 1){
		cout << "Tasks: "<<machine1.get_sop() <<" : "<< machine1.mtasks_v.size() << "\n";
		return machine1.mtasks_v;
	} else {
		cout << "Tasks: "<< machine2.mtasks_v.size() << "\n";
		return machine2.mtasks_v;
	}
}

int Order::get_exectime(){
  return exec_t;
}