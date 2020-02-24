#include <iostream>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <cassert>

#include "VirtualMachine.h"

using namespace std;

int VirtualMachine::get_clock()
{
    return clock;
}

void VirtualMachine::run(fstream& objectCode, fstream& in, fstream& out)
{
    const int debug = true;
    int opcode, rd, i, rs, constant, addr, j;

    base = 0;
    for (limit = 0; objectCode >> mem[limit]; limit++);
    
    sr = 2;
    sp = msize;
    pc = 0;
    while (pc < limit) {
        ir = mem[pc];
        pc++;
        opcode = (ir&0xf800)>>11;
        rd = (ir&0x600)>>9;
        i = (ir&0x100)>>8;
        rs = (ir&0xc0)>>6;
        addr = ir&0xff;
        constant = addr;
    
        clock++;
    	
	//if(debug) out << "Hello" << endl;
        if (opcode == 0) { /* load loadi */
            if (i) {
                if (constant&0x80) constant |= 0xff00;
                r[rd] = constant;
            } else {
                if (addr >= limit) {
                    out << "Out of bound error. load\n" << limit;
                    return;
                }
                r[rd] = mem[addr];
                clock += 3;
            }

        } else if (opcode == 1) { /* store */
            if (addr >= limit) {
                out << "Out of bound error.\n";
                return;
            }
            mem[addr] = r[rd];
            clock += 3;

        } else if (opcode == 2) { /* add addi */
            int sign1 = (r[rd]&0x8000)>>15;
            int sign2;
            if (i) {
                sign2 = (constant&0x80)>>7;
                // sign extend both operands to perform operation
                if (sign2) constant |= 0xffffff00;
                if (r[rd] & 0x8000) r[rd] |= 0xffff0000;
                r[rd] = r[rd] + constant;
            } else {
                sign2 = (r[rs]&0x8000)>>15;
                int temp = r[rs];
                // sign extend both operands to perform operation
                if (sign2) temp |= 0xffff0000;
                if (r[rd] & 0x8000) r[rd] |= 0xffff0000;
                r[rd] = r[rd] + temp;
            }

            // set CARRY
            if (r[rd]&0x10000) sr |= 0x1;
            else sr &= 0xfffe;

            // set OVERFLOW
            if (sign1 == sign2 and sign1 != (r[rd]&0x8000)>>15)
                sr |= 0x10;
            else
                sr &= 0xffef;

            // keep it at 16 bits
            r[rd] &= 0xffff;

        } else if (opcode == 3) { /* addc addci */
            int sign1 = (r[rd]&0x8000)>>15;
            int sign2;
            if (i) {
                sign2 = (constant&0x80)>>7;
                // sign extend both operands to perform operation
                if (sign2) constant |= 0xffffff00;
                if (r[rd] & 0x8000) r[rd] |= 0xffff0000; 
                r[rd] = r[rd] + constant + sr&0x1;
            } else {
                sign2 = (r[rs]&0x8000)>>15;
                int temp = r[rs];
                // sign extend both operands to perform operation
                if (sign2) temp |= 0xffff0000;
                if (r[rd] & 0x8000) r[rd] |= 0xffff0000;
                r[rd] = r[rd] + temp + sr&0x1;
            }

            // set CARRY
            if (r[rd]&0x10000) sr |= 0x1;
            else sr &= 0xfffe;

            // set OVERFLOW
            if (sign1 == sign2 and sign1 != (r[rd]&0x8000)>>15)
                sr |= 0x10;
            else
                sr &= 0xffef;

            // keep it at 16 bits
            r[rd] &= 0xffff;

        } else if (opcode == 4) { /*sub subi */
            int sign1 = (r[rd]&0x8000)>>15;
            int sign2;
	    int temp = constant;
	    temp = ~temp;  /* Performing the subtracting by 2 complement */
	    temp += 1;    /* Add one */  
            if (i) {
                sign2 = (constant&0x80)>>7;
                // sign extend both operands to perform operation
                if (sign2) constant |= 0xffffff00;
                if (r[rd] & 0x8000) r[rd] |= 0xffff0000; 
                r[rd] = r[rd] + temp;
            } else {
                temp = r[rs];
		temp = ~temp;
		//ASK HERE
		temp += 1;
                sign2 = (r[rs]&0x8000)>>15;
                // sign extend both operands to perform operation
                if (sign2) temp |= 0xffff0000;
                if (r[rd] & 0x8000) r[rd] |= 0xffff0000;
                r[rd] = r[rd] + temp;
            }

            // set CARRY
            if (r[rd]&0x10000) sr |= 0x1;
            else sr &= 0xfffe;

            // set OVERFLOW
            if (sign1 == sign2 and sign1 != (r[rd]&0x8000)>>15)
                sr |= 0x10;
            else
                sr &= 0xffef;

            // keep it at 16 bits
            r[rd] &= 0xffff;

        } else if (opcode == 5) { /* subc subci */
            int sign1 = (r[rd]&0x8000)>>15;
            int sign2;
	    int temp = constant;
	    temp = ~temp;
	    temp += 1;
            if (i) {
                sign2 = (constant&0x80)>>7;
                // sign extend both operands to perform operation
                if (sign2) constant |= 0xffffff00;
                if (r[rd] & 0x8000) r[rd] |= 0xffff0000;
                r[rd] = r[rd] + temp + sr&0x1;
            } else {
                int temp = r[rs];
		temp = ~temp;
		//ASK HERE
		temp += 1;
                sign2 = (r[rs]&0x8000)>>15;
                // sign extend both operands to perform operation
                if (sign2) temp |= 0xffff0000;
                if (r[rd] & 0x8000) r[rd] |= 0xffff0000;
                r[rd] = r[rd] + temp + sr&0x1;
            }

            // set CARRY
            if (r[rd]&0x10000) sr |= 0x1;
            else sr &= 0xfffe;

            // set OVERFLOW
            if (sign1 == sign2 and sign1 != (r[rd]&0x8000)>>15)
                sr |= 0x10;
            else
                sr &= 0xffef;

            // keep it at 16 bits
            r[rd] &= 0xffff;
        
	} else if (opcode == 6) { /* and andi */
            int sign1 = (r[rd]&0x8000)>>15;
            int sign2;
            if (i) {
                sign2 = (constant&0x80)>>7;
                // sign extend both operands to perform operation
                if (sign2) constant |= 0xffffff00;
                if (r[rd] & 0x8000) r[rd] |= 0xffff0000;
                r[rd] = r[rd] & constant;
            } else {
                sign2 = (r[rs]&0x8000)>>15;
                int temp = r[rs];
                // sign extend both operands to perform operation
                if (sign2) temp |= 0xffff0000;
                if (r[rd] & 0x8000) r[rd] |= 0xffff0000;
                r[rd] = r[rd] & temp;
            }

            // keep it at 16 bits
            r[rd] &= 0xffff;

	    
	} else if (opcode == 7) { /* xor xori */
            int sign1 = (r[rd]&0x8000)>>15;
            int sign2;
            if (i) {
                sign2 = (constant&0x80)>>7;
                // sign extend both operands to perform operation
                if (sign2) constant |= 0xffffff00;
                if (r[rd] & 0x8000) r[rd] |= 0xffff0000;
                r[rd] = r[rd] ^ constant;
            } else {
                sign2 = (r[rs]&0x8000)>>15;
                int temp = r[rs];
                // sign extend both operands to perform operation
                if (sign2) temp |= 0xffff0000;
                if (r[rd] & 0x8000) r[rd] |= 0xffff0000;
                r[rd] = r[rd] ^ temp;
            }

            // keep it at 16 bits
            r[rd] &= 0xffff;
	    
	} else if (opcode == 8) { /* compl */
            r[rd] = ~r[rd];
            
            // keep it at 16 bits
            r[rd] &= 0xffff;


        } else if (opcode == 9) { /* shl */
            r[rd] = r[rd]<<1;

            // set CARRY
            if (r[rd]&0x10000) sr |= 0x1;
            else sr &= 0xfffe;

            // keep it at 16 bits
            r[rd] &= 0xffff;

        } else if (opcode == 10) { /* shla */
            // set CARRY
            if (r[rd]&0x8000) sr |= 0x1;
            else sr &= 0xfffe;

            r[rd] = r[rd]<<1;
            if (r[rd]&0x10000) r[rd] |= 0x8000; // 1000 0000 0000 0000
	        else r[rd]& 0x7fff; // 0111 1111 1111 1111

            // keep it at 16 bits
            r[rd] &= 0xffff;

        } else if (opcode == 11) { /* shr */
            // set CARRY
            if (r[rd]&0x1) sr |= 0x1;
            else sr &= 0xfffe;

            r[rd] = r[rd]>>1;

            // keep it at 16 bits
            r[rd] &= 0xffff;

        } else if (opcode == 12) { /* shra */
            // set CARRY
            if (r[rd]&0x8000) sr |= 0x1;
            else sr &= 0xfffe;

            r[rd] = r[rd]<<1;
            if (r[rd]&0x4000) r[rd] |= 0x8000;

            // keep it at 16 bits
            r[rd] &= 0xffff;

	} else if (opcode == 13) { /*compr compri */
	    if(i){
	        if(r[rd] < constant){ // compare and set status register
	            sr |= 0x8;
		    sr &= 0xfff9;
		}
		else if(r[rd] == constant){ // compare and set status register
	            sr |= 0x4;
		    sr &= 0xfff5;
		}
		else if(r[rd] > constant){ // compare and set status register
	            sr |= 0x2;
		    sr &= 0xfff3;
		}
	    }
	    else{
	        if(r[rd] < r[rs]){ // compare and set status register
	            sr |= 0x8;
		    sr &= 0xfff9;
		}
		else if(r[rd] == r[rs]){ // compare and set status register
	            sr |= 0x4;
		    sr &= 0xfff5;
		}
		else if(r[rd] > r[rs]){ // compare and set status register
	            sr |= 0x2;
		    sr &= 0xfff3;
		}
	    }

	} else if (opcode == 14) { /* getstat */
	    r[rd] = sr;
		
	} else if (opcode == 15) { /* putstat */
	    sr = r[rd];

	} else if (opcode == 16) { /* jump */
	    pc = addr;

	} else if (opcode == 17) { /* jumpl */
	    if ( sr &0x8) pc = addr; 
           
	} else if (opcode == 18) { /* jumpe */
        if ( sr &0x4) pc = addr; 
	    
	} else if (opcode == 19) { /* jumpg */
	    if (sr&0x2) pc = addr;    
         
	} else if (opcode == 20) { /* call */ 
        sp --; 	     
        mem[sp] = pc;   // program counter

	    sp --; 
	    mem[sp] = sr;   // status register

	    sp --; 
	    mem[sp] = r[3]; // register 3

	    sp --;
	    mem[sp] = r[2]; // register 2

	    sp --;
	    mem[sp] = r[1]; // register 1

	    sp--; 
	    mem[sp] = r[0]; // register 0

	    pc = addr;	// load new address
	    clock += 3;
	}
    else if (opcode == 21) { /* return */ 
	    r[0] = mem[sp]; // restore register 0
	    sp++;

	    r[1] = mem[sp]; // restore register 1
	    sp++;

	    r[2] = mem[sp]; // restore register 2
	    sp++;

	    r[3] = mem[sp]; // restore register 3
	    sp++;

	    sr = mem[sp]; // restore status register
	    sp++;

	    pc = mem[sp]; // restore program counter
            sp++;
	    clock += 3; 

	} else if (opcode == 22) { /* read */ 
            in >> r[rd];
	    clock += 27; 
	
	} else if (opcode == 23) { /* write */
            if (r[rd] & 0x8000) r[rd] |= 0xffff0000;
	        out << r[rd] << endl;
	    clock += 27;	

	} else if (opcode == 24) { /* halt */
            exit(2);
	
	} else if (opcode ==25) { /* noop */ 
             
        } else {
            cout << "Bad opcode = " << opcode << endl;
            exit(3);
        }

        if (debug) {
            printf("ir=%d op=%d rd=%d i=%d rs=%d const=%d addr=%d\n", ir, opcode, rd, i, rs, constant, addr);
            printf("r[0]=%d r[1]=%d r[2]=%d r[3]=%d pc=%d sr=%d sp=%d clock=%d\n\n", r[0], r[1], r[2], r[3], pc, sr, sp, clock);
            //char c;
            //cin>>c;
        }
    }

    if (debug) {
        for (j=0; j<limit; j++) {
            printf("%8d", mem[j]);
            if ((j%8)==7) printf("\n");
        }
        cout << endl;
    }
} /* main */
