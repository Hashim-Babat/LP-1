// Arrival Time: Time at which the process arrives in the ready queue.
// Completion Time: Time at which process completes its execution.
// Burst Time: Time required by a process for CPU execution.
// Turn Around Time: Time Difference between completion time and arrival time.
// Turn Around Time = Completion Time  –  Arrival Time
// Waiting Time(W.T): Time Difference between turn around time and burst time.
// Waiting Time = Turn Around Time  –  Burst Time
#include<bits/stdc++.h>
using namespace std;
void FCFS(vector<vector<int>>& process) {
    int n = process.size();
    int currentTime = 0;
    // Sort processes by arrival time
    sort(process.begin(), process.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];  // Sort by arrival time
    });
    // Initialize the first process
    if (currentTime < process[0][0]) {
        currentTime = process[0][0];  // Move time to the arrival time of the first process if idle
    }
    process[0][2] = currentTime + process[0][1];  // Completion time
    process[0][3] = process[0][2] - process[0][0];  // Turn-Around Time (CT - AT)
    process[0][4] = process[0][3] - process[0][1];  // Waiting Time (TAT - BT)
    currentTime = process[0][2];
    double avgTA = process[0][3];
    double avgW = process[0][4];
    // Iterate over the remaining processes
    for (int i = 1; i < n; i++) {
        if (currentTime < process[i][0]) {
            currentTime = process[i][0];  // Move time to the next process's arrival time if idle
        }
        process[i][2] = currentTime + process[i][1];  // Completion time
        process[i][3] = process[i][2] - process[i][0];  // Turn-Around Time (CT - AT)
        process[i][4] = process[i][3] - process[i][1];  // Waiting Time (TAT - BT)
        currentTime = process[i][2];  // Update current time after process execution

        avgW += process[i][4];
        avgTA += process[i][3];
    }
    cout << "\nProcess Name\tArrival Time\tBurst Time\tCompletion Time\tTurn-Around Time\tWaiting Time";
    for (int i = 0; i < n; i++) {
        cout << "\nP[" << i << "] : \t\t" << process[i][0] << "\t\t" << process[i][1] << "\t\t" << process[i][2] << "\t\t" << process[i][3] << "\t\t\t" << process[i][4];
    }
    cout << "\nAverage Turn-Around Time: " << avgTA / n;
    cout << "\nAverage Waiting Time: " << avgW / n;
}
bool compareByPriority(const vector<int>& a, const vector<int>& b) {
    return a[5] < b[5];  // Compare by priority (lower value means higher priority)
}
void Priority(vector<vector<int>>& process) {
    int n = process.size();
    vector<bool> completed(n, false);
    int currentTime = 0;
    int completedProcesses = 0;
    for (int i = 0; i < n; i++) {
        cout << "\nEnter the priority for process -> P[" << i << "] : ";
        int priority;
        cin >> priority;
        process[i][5] = priority;  // Set the priority for each process
    }
    while (completedProcesses < n) {
        int minPriorityIndex = -1;
        for (int i = 0; i < n; i++) {
            if (!completed[i] && process[i][0] <= currentTime) {
                if (minPriorityIndex == -1 || process[i][5] < process[minPriorityIndex][5]) {
                    minPriorityIndex = i;
                }
            }
        }
        if (minPriorityIndex == -1) {
            currentTime++;
            continue;
        }
        int i = minPriorityIndex;
        completed[i] = true;
        completedProcesses++;
        if (currentTime < process[i][0]) {
            currentTime = process[i][0];
        }
        process[i][2] = currentTime + process[i][1];  // Completion time
        process[i][3] = process[i][2] - process[i][0];  // Turn-Around Time (CT - AT)
        process[i][4] = process[i][3] - process[i][1];  // Waiting Time (TAT - BT)
        currentTime = process[i][2];

        cout << "\nExecuting process P[" << i << "] at time " << currentTime;
    }
    double avgTA = 0;
    double avgW = 0;
    for (int i = 0; i < n; i++) {
        avgTA += process[i][3];
        avgW += process[i][4];
    }
    cout << "\n\nProcess Name\tArrival Time\tBurst Time\tCompletion Time\tTurn-Around Time\tWaiting Time\tPriority";
    for (int i = 0; i < n; i++) {
        cout << "\nP[" << i << "] : \t\t" << process[i][0] << "\t\t" << process[i][1] << "\t\t" << process[i][2] << "\t\t" << process[i][3] << "\t\t\t" << process[i][4] << "\t\t\t" << process[i][5];
    }
    cout << "\nAverage Turn-Around Time: " << avgTA / n;
    cout << "\nAverage Waiting Time: " << avgW / n;
}
bool comparebyBurst(vector<int>& a,vector<int>& b){
    return a[1] < b[1];
}
void SJF(vector<vector<int>>& process){
    int n = process.size();
    vector<int> arrivalTime(n), burstTime(n), remainingTime(n);
    vector<int> completionTime(n), turnaroundTime(n), waitingTime(n);
    for (int i = 0; i < n; i++){
        arrivalTime[i] = process[i][0];
        burstTime[i] = process[i][1];
        remainingTime[i] = burstTime[i];
    }
    int completed = 0, currentTime = 0, minIndex = -1;
    int minBurstTime = INT_MAX;
    bool check = false;
    while (completed != n) {
        for (int i = 0; i < n; i++){
            if (arrivalTime[i] <= currentTime && remainingTime[i] < minBurstTime && remainingTime[i] > 0){
                minBurstTime = remainingTime[i];
                minIndex = i;
                check = true;
            }
        }
        if (!check){
            currentTime++;
            continue;
        }
        remainingTime[minIndex]--;
        minBurstTime = remainingTime[minIndex];
        if (minBurstTime == 0){
            minBurstTime = INT_MAX;
        }
        if (remainingTime[minIndex] == 0){
            completed++;
            check = false;
            completionTime[minIndex] = currentTime + 1;
            turnaroundTime[minIndex] = completionTime[minIndex] - arrivalTime[minIndex];
            waitingTime[minIndex] = turnaroundTime[minIndex] - burstTime[minIndex];
        }
        currentTime++;
    }
    int totalTat = 0;
    int totalWt = 0;
    cout<<"\nProcess Name\tArrival Time\tBurst Time\tCompletion Time\tTurn-Around Time\tWaiting Time";
    for(int i=0;i<n;i++){
        totalTat += turnaroundTime[i];
        totalWt += waitingTime[i];
        cout<<"\nP["<<i<<"] : \t\t"<<arrivalTime[i]<<"\t\t"<<burstTime[i]<<"\t\t"<<completionTime[i]<<"\t\t"<<turnaroundTime[i]<<"\t\t\t"<<waitingTime[i];
    }
    cout << "\nAverage TurnAround Time = " << (float)totalTat / n;
    cout << "\nAverage Waiting Time = " << (float)totalWt / n;
}
int find(vector<int>& v,int val){
    for(int i=0;i<v.size();i++){
        if(v[i]==val) return i;
    }
    return -1;
}
void roundRobin(vector<vector<int>>& process) {
    int n = process.size();
    cout << "\nEnter the Time Quantum: ";
    int timeQuantum, currTime = 0;
    cin >> timeQuantum;

    vector<int> completionTime(n, 0);
    queue<vector<int>> readyQueue;

    for (int i = 0; i < n; i++) {
        process[i][5] = process[i][1];
        vector<int> temp = process[i];
        temp[2] = i;
        readyQueue.push(temp);
    }

    while (!readyQueue.empty()) {
        vector<int> currentProcess = readyQueue.front();
        readyQueue.pop();
        int processNumber = currentProcess[2];
        int arrivalTime = currentProcess[0];
        int remainingBurst = currentProcess[5];

        if (arrivalTime <= currTime) {
            cout << "\nSlot: " << currTime << " - ";
            if (remainingBurst <= timeQuantum) {
                currTime += remainingBurst;
                cout << currTime << " Process [" << processNumber << "] completed";
                currentProcess[5] = 0;
                completionTime[processNumber] = currTime;
            } else {
                currTime += timeQuantum;
                cout << currTime << " Process [" << processNumber << "]";
                currentProcess[5] -= timeQuantum;
                readyQueue.push(currentProcess);
            }
        } else {
            readyQueue.push(currentProcess);
            if (readyQueue.front()[0] > currTime) {
                currTime = readyQueue.front()[0];
            }
        }
    }
    double avgTurnaroundTime = 0, avgWaitingTime = 0;
    for (int i = 0; i < n; i++) {
        process[i][2] = completionTime[i];
        process[i][3] = process[i][2] - process[i][0];
        process[i][4] = process[i][3] - process[i][1];
        avgTurnaroundTime += process[i][3];
        avgWaitingTime += process[i][4];
    }
    cout << "\n\nProcess Name\tArrival Time\tBurst Time\tCompletion Time\tTurn-Around Time\tWaiting Time";
    for (int i = 0; i < n; i++) {
        cout << "\nP[" << i << "] : \t\t" << process[i][0] << "\t\t" << process[i][1] << "\t\t" << process[i][2] << "\t\t" << process[i][3] << "\t\t\t" << process[i][4];
    }
    cout << "\nAverage Turn-Around Time: " << avgTurnaroundTime / n;
    cout << "\nAverage Waiting Time: " << avgWaitingTime / n;
}
int main(){
    int n;
    cout<<"\nEnter the number of process : ";
    cin>>n;
    int avgTA=0;
    int avgW=0;
    // Arrival  Burst  Completion  Turn-Arund  Waiting Priority
    vector<vector<int>> process(n,vector<int>(6));
    for(int i=0;i<n;i++){
        cout<<"\nEnter the arrival time & Burst Time for process -> P["<<i<<"] : ";
        int a,b;
        cin>>a>>b;
        process[i][0] = a;
        process[i][1] = b;
    }
    int ch;
    char c = 'y';
    while(c == 'y'){
        cout<<"\n1.FIRST COME FIRST SERVE";
        cout<<"\n2.SHORTEST JOB FIRST";
        cout<<"\n3.PRIORITY BASED";
        cout<<"\n4.ROUND ROBIN";
        cout<<"\nEnter your choice : ";
        cin>>ch;
        if(ch==1){
            FCFS(process);
        }
        else if(ch==2){
            SJF(process);
        }
        else if(ch==3){
            Priority(process);
        }
        else if(ch==4){
            roundRobin(process);
        }
        else{
            cout<<"\nINVALID INPUT";
        }
        cout<<"\nDo you want to continue (y/n) : ";
        cin>>c;
    } 
}