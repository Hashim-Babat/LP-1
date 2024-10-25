#include<bits/stdc++.h>
using namespace std;

struct Block {
    int size;
    int process;
    bool allocated;
};
void display(vector<Block>& memory){
    int n = memory.size();
    cout<<"\nSize of memory blocks : ";
    for(int i=0;i<n;i++){
        cout<<memory[i].size<<" ";
    }
    cout<<endl;
    cout<<"\nAvailable memory blocks : ";
    for(int i=0;i<n;i++){
        cout<<memory[i].process<<" ";
    }
    cout<<endl;
}
void firstFit(vector<Block>& memory, int requestSize) {
    for (int i = 0; i < memory.size(); ++i) {
        if (!memory[i].allocated && memory[i].size >= requestSize) {
            memory[i].allocated = true;
            memory[i].process = requestSize;
            cout << "First Fit : Allocated " << requestSize << " units at memory block " << i << endl;
            return;
        }
    }
    cout << "First Fit: Memory allocation failed for size " << requestSize << endl;
}

int nextFit(vector<Block>& memory, int requestSize, int& lastIndex) {
    for (int i = lastIndex; i < memory.size(); ++i) {
        if (!memory[i].allocated && memory[i].size >= requestSize) {
            memory[i].allocated = true;
            memory[i].process = requestSize;
            lastIndex = i; // Update lastIndex for next fit
            cout << "Next Fit : Allocated " << requestSize << " units at memory block " << i << endl;
            return i;
        }
    }
    for (int i = 0; i < lastIndex; ++i) {
        if (!memory[i].allocated && memory[i].size >= requestSize) {
            memory[i].allocated = true;
            memory[i].process = requestSize;
            lastIndex = i; // Update lastIndex for next fit
            cout << "Next Fit : Allocated " << requestSize << " units at memory block " << i << endl;
            return i;
        }
    }
    cout << "Next Fit : Memory allocation failed for size " << requestSize << endl;
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
        memory[bestFitIndex].process = requestSize;
        cout << "Best Fit : Allocated " << requestSize << " units at memory block " << bestFitIndex << endl;
    } else {
        cout << "Best Fit : Memory allocation failed for size " << requestSize << endl;
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
        memory[worstFitIndex].process = requestSize;
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

    int lastIndex = 0,ch;
    char c = 'y';
    while(c=='y'){
        cout<<"\n==================== MENU ====================";
        cout<<"\n1. FIRST FIT";
        cout<<"\n2. NEXT FIT";
        cout<<"\n3. BEST FIT";
        cout<<"\n4. WORST FIT";
        cout<<"\n5. EXIT";
        cout<<"\n==============================================";
        cout<<"\nEnter your choice from the MENU : ";
        cin>>ch;
        if(ch==1){
            int requestSize;
            cout << "Enter size to allocate : ";
            cin >> requestSize;
            firstFit(memory, requestSize);
            display(memory);
        }
        else if(ch==2){
            int requestSize;
            cout << "Enter size to allocate : ";
            cin >> requestSize;
            lastIndex = nextFit(memory, requestSize, lastIndex);
            display(memory);
        }
        else if(ch==3){
            int requestSize;
            cout << "Enter size to allocate : ";
            cin >> requestSize;
            bestFit(memory, requestSize);
            display(memory);
        }
        else if(ch==4){
            int requestSize;
            cout << "Enter size to allocate : ";
            cin >> requestSize;
            worstFit(memory, requestSize);
            display(memory);
        }
        else if(ch==5){
            cout<<"\nEXITING..........";
            break;
        }
        else{
            cout<<"\nINVALID INPUT !!";
        }
        cout<<"\nDo you want to continue (y/n) : ";
        cin>>c;
    }
    return 0;
}