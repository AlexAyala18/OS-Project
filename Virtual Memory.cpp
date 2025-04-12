#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

// Constants
const int PAGE_SIZE = 4096; // 4KB
const int VIRTUAL_MEM_SIZE = PAGE_SIZE * 8;  // 8 pages virtual memory
const int PHYSICAL_MEM_SIZE = PAGE_SIZE * 4; // 4 pages physical memory

struct PageTableEntry {
    bool valid;
    int frameNumber;
    bool dirty;
};

class VirtualMemorySimulator {
private:
    vector<PageTableEntry> pageTable;
    queue<int> pageQueue;  // For FIFO
    unordered_map<int, int> frameToPage;

    int numFrames;

public:
    VirtualMemorySimulator() {
        pageTable.resize(VIRTUAL_MEM_SIZE / PAGE_SIZE);
        numFrames = PHYSICAL_MEM_SIZE / PAGE_SIZE;
    }

    int translate(int virtualAddress) {
        int pageNumber = virtualAddress / PAGE_SIZE;
        int offset = virtualAddress % PAGE_SIZE;

        if (!pageTable[pageNumber].valid) {
            handlePageFault(pageNumber);
        }

        int frameNumber = pageTable[pageNumber].frameNumber;
        return (frameNumber * PAGE_SIZE) + offset;
    }

    void handlePageFault(int pageNumber) {
        cout << "Page fault occurred for page: " << pageNumber << endl;

        if (pageQueue.size() >= numFrames) {
            int oldPage = pageQueue.front();
            pageQueue.pop();
            pageTable[oldPage].valid = false;
            cout << "Evicting page: " << oldPage << endl;
        }

        int frameNumber = pageQueue.size();
        pageQueue.push(pageNumber);

        pageTable[pageNumber].valid = true;
        pageTable[pageNumber].frameNumber = frameNumber;
        pageTable[pageNumber].dirty = false;
    }
};

int main() {
    VirtualMemorySimulator vms;

    vector<int> virtualAddresses = { 0, 4096, 8192, 12288, 16384, 0, 20480, 4096 };

    for (int addr : virtualAddresses) {
        int physAddr = vms.translate(addr);
        cout << "Virtual Address: " << addr << " --> Physical Address: " << physAddr << endl;
    }

    return 0;
}
