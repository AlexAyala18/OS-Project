#include <iostream>
#include <string>
#include <vector>

//set these process states as absolute, will return error for any other values
enum ProcessState { NEW, READY, RUNNING, WAITING, TERMINATED };

//sets system memory to 200, and sets initial available memory to system memory
const int SYSTEM_MEMORY = 200;
int available_memory = SYSTEM_MEMORY;

class Process {

//private data members
private:
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    ProcessState state;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int memory_required;
    bool io_operations;

public:
    // Constructor to initialize process attributes 
    Process(int pid, int arrival_time, int burst_time, int priority, int memory_required, bool io_operations)
        : pid(pid), arrival_time(arrival_time), burst_time(burst_time), priority(priority), state(NEW),
        remaining_time(burst_time), waiting_time(0), turnaround_time(0), memory_required(memory_required), io_operations(io_operations) {
    }

    // Updates the state of the process
    void updateState(ProcessState new_state) {
        state = new_state;
    }

    // Executes the process by decrementing remaining execution time
    void execute() {
        if (state == NEW) {//in case the user does not set it.
            state = READY;
            displayProcessInfo();
        }
        //if there is enough memory, the process can run
        if (state == READY && memory_required <= available_memory) {
            displayProcessInfo();
            available_memory -= memory_required; 
            state = RUNNING;
        }
        //decrements the process if remaining time is greater then 0
        if (state == RUNNING || state == READY) {
            if (remaining_time > 0) {
                remaining_time--;
                if (remaining_time == 0) {
                    state = TERMINATED;
                    available_memory = available_memory + memory_required;  // Release memory when process terminates
                    calculateTurnaroundTime();//only called when the process is finished. 
                }
            }

        }
        else if (memory_required > available_memory && state == READY) {
            std::cout << "Not enough memory for Process " << pid << std::endl;
        }

    }

    // Increments waiting time when the process is in the READY state
    void incrementWaitingTime() {
        if (state == READY) {
            waiting_time++;
        }
    }

    // Calculates turnaround time as the sum of waiting time and burst time
    void calculateTurnaroundTime() {//calculated when the process is terminated
        turnaround_time = waiting_time + burst_time;
    }

    // Displays process information
    void displayProcessInfo() const {
        std::cout << "Process " << pid << " | State: " << stateToString(state)//return the string value of the state. 
            << " | Remaining Time: " << remaining_time
            << " | Waiting Time: " << waiting_time
            << " | Turnaround Time: " << turnaround_time
            << " | Available Memory: " << available_memory << std::endl;
    }

    // Converts process state to a string
    static std::string stateToString(ProcessState state) {
        switch (state) {
        case NEW: return "NEW";//for when state is not clarified
        case READY: return "READY";
        case RUNNING: return "RUNNING";
        case WAITING: return "WAITING";
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
    p1.updateState(READY);//There is 2 because 2 processes were opened.
    p2.updateState(READY);//always update the state before executing.

    // Simulating execution of process p1 
    for (int i = 0; i < 8; i++) {
        p1.execute();
        p1.displayProcessInfo();
    }

    // Simulating execution of process p2
    for (int i = 0; i < 6; i++) {
        p2.execute();
        p2.displayProcessInfo();
    }

    return 0;
}
