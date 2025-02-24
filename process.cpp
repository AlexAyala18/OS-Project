#include <iostream>
#include <string>
#include <vector>

enum ProcessState { NEW, READY, RUNNING, WAITING, TERMINATED };

const int SYSTEM_MEMORY = 200;
int available_memory = SYSTEM_MEMORY;

class Process {
private:
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    ProcessState state;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int memory_required;//we can add a memory counter and simulate a need for memory I created it but its not really used its just there
    bool io_operations;//i'm not even gonna bother with having a seperate process be updated but we can if decided. its here if we do. 

public:
    // Constructor to initialize process attributes this was made with google i never learned how to make proper constructors. 
    Process(int pid, int arrival_time, int burst_time, int priority, int memory_required, bool io_operations)
        : pid(pid), arrival_time(arrival_time), burst_time(burst_time), priority(priority), state(NEW),
        remaining_time(burst_time), waiting_time(0), turnaround_time(0), memory_required(memory_required), io_operations(io_operations) {
    }

    // Updates the state of the process
    void updateState(ProcessState new_state) {//this allows us to set the new state to anything. 
        state = new_state;
    }

    // Executes the process by decrementing remaining execution time
    void execute() {
        if (state == READY && memory_required <= available_memory) {
            available_memory -= memory_required;  // Nvm I figured out how to make it easy. 
            //state = RUNNING;
        }

        if (state == RUNNING||state == READY) {

            if (remaining_time > 0) {
                state = RUNNING;
                remaining_time--;
                if (remaining_time == 0) {
                    state = TERMINATED;
                    available_memory = available_memory + memory_required;  // Release memory when process terminates
                    calculateTurnaroundTime();//only called when the process is finished. 
                }
            }
            //state == RUNNING;
        }
        else if (memory_required > available_memory && state == READY) {
            std::cout << "Not enough memory for Process " << pid << std::endl;//will fix want process to end auto
        }
        
    }

    // Increments waiting time when the process is in the READY state
    void incrementWaitingTime() {//I made it but since we dont require looking into anything it won't be called this is for when io operations is true
        if (state == READY) {
            waiting_time++;
        }
    }

    // Calculates turnaround time as the sum of waiting time and burst time
    void calculateTurnaroundTime() {//calculated when the process is terminated. this could be wrong math need to verify
        turnaround_time = waiting_time + burst_time;
    }

    // Displays process information including state, remaining time, waiting time, and turnaround time aka the menu or gui
    void displayProcessInfo() const {//we can change it this was a first draft its not good. 
        std::cout << "Process " << pid << " | State: " << stateToString(state)//this will return the string value of the state. 
            << " | Remaining Time: " << remaining_time
            << " | Waiting Time: " << waiting_time
            << " | Turnaround Time: " << turnaround_time
            << " | Available Memory: " << available_memory << std::endl;
    }

    // Converts process state to a string
    static std::string stateToString(ProcessState state) {//it does not read at sec == begining it skips the ready phase. 
        switch (state) {
        case NEW: return "NEW";//just for when state is not clarified
        case READY: return "READY";//i'll add it. 
        case RUNNING: return "RUNNING";
        case WAITING: return "WAITING";//its here if we need to implement but its currently not operational
        case TERMINATED: return "TERMINATED";
        default: return "UNKNOWN";
        }
    }
};

int main() {
    // Creating two process 
    Process p1(1, 0, 8, 1, 124, false);//pid, arrival time, burst time, priority, memory required, io operations. 
    Process p2(2, 1, 6, 2, 169, true);

    // Updating process states to READY
    p1.updateState(READY);//There is 2 because 2 processes were opened. //if not put first will not work.
    p2.updateState(READY);//always update the state before executing.
    p1.displayProcessInfo();

    // Simulating execution of process p1 you can change the time to anything. 
    for (int i = 0; i < 8; i++) {
        p1.execute();
        p1.displayProcessInfo();
    }
    p2.displayProcessInfo();//

    // Simulating execution of process p2
    for (int i = 0; i < 6; i++) {
        p2.execute();
        p2.displayProcessInfo();
    }

    return 0;
}



//Memory is operational 
//IDK what PID does
//state is being used 
//remaining waiting and turnaround done. 
//IDK how to do the IO operations one for the waiting time. 
//arrival priority and burst times(except for turnaround) are not being used I'm using a countdown.  
