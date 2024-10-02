#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Block {
    int size;
    bool allocated;
};

void firstFit(vector<Block>& memory, int requestSize) {
    for (int i = 0; i < memory.size(); ++i) {
        if (!memory[i].allocated && memory[i].size >= requestSize) {
            memory[i].allocated = true;
            cout << "First Fit: Allocated " << requestSize << " units at memory block " << i << endl;
            return;
        }
    }
    cout << "First Fit: Memory allocation failed for size " << requestSize << endl;
}

int nextFit(vector<Block>& memory, int requestSize, int& lastIndex) {
    for (int i = lastIndex; i < memory.size(); ++i) {
        if (!memory[i].allocated && memory[i].size >= requestSize) {
            memory[i].allocated = true;
            lastIndex = i; // Update lastIndex for next fit
            cout << "Next Fit: Allocated " << requestSize << " units at memory block " << i << endl;
            return i;
        }
    }
    for (int i = 0; i < lastIndex; ++i) {
        if (!memory[i].allocated && memory[i].size >= requestSize) {
            memory[i].allocated = true;
            lastIndex = i; // Update lastIndex for next fit
            cout << "Next Fit: Allocated " << requestSize << " units at memory block " << i << endl;
            return i;
        }
    }
    cout << "Next Fit: Memory allocation failed for size " << requestSize << endl;
    return -1;
}

void bestFit(vector<Block>& memory, int requestSize) {
    int bestFitIndex = -1;
    int minFragmentation = INT_MAX;

    for (int i = 0; i < memory.size(); ++i) {
        if (!memory[i].allocated && memory[i].size >= requestSize) {
            int fragmentation = memory[i].size - requestSize;
            if (fragmentation < minFragmentation) {
                minFragmentation = fragmentation;
                bestFitIndex = i;
            }
        }
    }

    if (bestFitIndex != -1) {
        memory[bestFitIndex].allocated = true;
        cout << "Best Fit: Allocated " << requestSize << " units at memory block " << bestFitIndex << endl;
    } else {
        cout << "Best Fit: Memory allocation failed for size " << requestSize << endl;
    }
}

void worstFit(vector<Block>& memory, int requestSize) {
    int worstFitIndex = -1;
    int maxFragmentation = -1;

    for (int i = 0; i < memory.size(); ++i) {
        if (!memory[i].allocated && memory[i].size >= requestSize) {
            int fragmentation = memory[i].size - requestSize;
            if (fragmentation > maxFragmentation) {
                maxFragmentation = fragmentation;
                worstFitIndex = i;
            }
        }
    }

    if (worstFitIndex != -1) {
        memory[worstFitIndex].allocated = true;
        cout << "Worst Fit: Allocated " << requestSize << " units at memory block " << worstFitIndex << endl;
    } else {
        cout << "Worst Fit: Memory allocation failed for size " << requestSize << endl;
    }
}

int main() {
    int numBlocks;
    cout << "Enter number of memory blocks: ";
    cin >> numBlocks;

    vector<Block> memory(numBlocks);

    // Input sizes for each block
    cout << "Enter size of each memory block:" << endl;
    for (int i = 0; i < numBlocks; ++i) {
        cout << "Block " << i << ": ";
        cin >> memory[i].size;
        memory[i].allocated = false;
    }

    int requestSize;
    cout << "Enter size to allocate: ";
    cin >> requestSize;

    int lastIndex = 0;

    firstFit(memory, requestSize);
    lastIndex = nextFit(memory, requestSize, lastIndex);
    bestFit(memory, requestSize);
    worstFit(memory, requestSize);

    return 0;
}