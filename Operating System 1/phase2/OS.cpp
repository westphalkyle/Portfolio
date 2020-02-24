#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

#include "Assembler.h"
#include "VirtualMachine.h"
#include "OS.h"

using namespace std;


OS::OS() {

    //Assembler as;
    //VirtualMachine vm;
    
    string line;
    fstream assembly, objectCode;
    fstream in, out, stack;
    int base=0, limit = 0;
    
    
    system("ls *.s > progs");

    fstream program;
    program.open("progs", ios::in);
    if (!program.is_open()) {
	cout << "Couldn't open progs" << endl;
	exit(1);
    }
    
    getline(program, line);
    while (!program.eof()) {
         objectCode.close();
         in.close();
         out.close();
         stack.close();
         
	 limit = 0;

         string assemblyFile = line;
         int pos = assemblyFile.find(".");
         if (pos > assemblyFile.length() || assemblyFile.substr(pos) != ".s") {
             cout << "No .s suffix.\n";
             exit(2);
         }
     
         string name = assemblyFile.substr(0, pos);
         string objectFile = name + ".o";
     
         assembly.open(assemblyFile.c_str(), ios::in);
         objectCode.open(objectFile.c_str(), ios::out);
         if (!assembly.is_open() or !objectCode.is_open()) {
             cout << "Couldn't open " << assemblyFile << " and/or " << objectFile << endl;
             exit(3);
         }
         PCB * p = new PCB(name, base, limit);
     
         if (as.assemble(assembly, objectCode)) {
             cout << "Assembler Error\n";
             assembly.close();
             objectCode.close();
             exit(4);
         }
     
         assembly.close();
         objectCode.close();
     
         objectCode.open(objectFile.c_str(), ios::in);
         if (!objectCode.is_open()) {
             cout << "Couldn't open " << objectFile << endl;
             exit(5);
         }
    

         string inFile = name + ".in";
         string outFile = name + ".out";
         string stFile = name + ".st";
         system(string("touch " + stFile).c_str());
         p->in.open(inFile.c_str(), ios::in);
         p->out.open(outFile.c_str(), ios::out);
         p->stack.open(stFile.c_str(), ios::in | ios::out);
         if (!p->in.is_open() or !p->out.is_open()) {
            cout << "Couldn't open " << inFile << " and/or " << outFile << endl;
             exit(6);
         }
         for (p->limit; objectCode >> vm.mem[p->limit + p->base]; p->limit++);
         base += p->limit + 1;
         jobs.push_back(p);
     
         getline(program, line);
    }

	list<PCB *>::iterator it = jobs.begin();
	while (it != jobs.end()) {
            readyQ.push(*it);
	    it++;
	}
}

OS::~OS() {
    cout << "Clock = " << sys_time << endl;
    PCB *temp;
    while(!jobs.empty()) {
        temp = jobs.front();
	delete temp;
	jobs.pop_front();
    }
    delete running;
}

void OS::run(/*int argc, char *argv[]*/)
{
    while (true) {
        if(readyQ.empty() && waitQ.empty()) break;
        contextSwitch();
	
	if(running) {
            loadState();
            vm.run(running->in, running->out, TIME_SLICE);
	    saveState();
	}
    }

} // run

void OS::loadState() {
    vm.pc = running->pc;
    for (int i = 0; i < 4; i++)
        vm.r[i] = running->r[i];
    vm.ir = running->ir;
    vm.sr = running->sr;
    vm.base = running->base;
    vm.limit = running->limit;
    vm.sp = running->sp;
    running->stack.seekg(0, ios::beg);
    for (int i = vm.sp; i < vm.msize and not running->stack.fail(); i++)
        running->stack >> vm.mem[i];
}

void OS::saveState() {
    running->pc = vm.pc;
    for (int i = 0; i < 4; i++)
        running->r[i] = vm.r[i];
    running->ir = vm.ir;
    running->sr = vm.sr;
    running->base = vm.base;
    running->limit = vm.limit;
    running->sp = vm.sp;
    running->stack.seekp(0, ios::beg);
    for (int i = vm.sp; i < vm.msize; i++)
        running->stack << vm.mem[i] << endl;
}

void OS::contextSwitch() {
    if(running) { 
        sys_time += vm.get_clock();
	running->cpu_time += vm.get_clock();
    }	
    while(true) {
        if(!waitQ.empty()) {
	    if(waitQ.front()->io_completion <= sys_time) {
                readyQ.push(waitQ.front());
                waitQ.pop();
            }
	}
	break;
    }

    int VMReturnStatus = (vm.sr&0xe0)>>5;
    if (VMReturnStatus == 0) { /* Time Slice */
        readyQ.push(running);    
    }
    if (VMReturnStatus == 1) { /* Halt Instruction */
    }
    if (VMReturnStatus == 2) { /* Out-of-bound Reference */
        }
    if (VMReturnStatus == 3) { /* Stack Overflow */
        }
    if (VMReturnStatus == 4) { /* Stack Underflow */
        }
    if (VMReturnStatus == 5) { /* Invalid Opcode */
        }
    if (VMReturnStatus == 6) { /* Read Operation */
        running->io_completion = running->cpu_time + 27;
	waitQ.push(running);    
    }
    if (VMReturnStatus == 7) { /* Write Operation */
        running->io_completion = running->cpu_time + 27;
        waitQ.push(running);    
    }
    running = NULL;
    vm.sr = 0;
    if (!readyQ.empty()) {
        running = readyQ.front();
        readyQ.pop();
    }
    sys_time += 5; // time for context switch
}
