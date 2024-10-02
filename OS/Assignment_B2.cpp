#include<bits/stdc++.h>
using namespace std;
void FCFS(vector<vector<int>>& process){
    int n = process.size();
    process[0][4]=0;
    process[0][2]=process[0][1];
    process[0][3]=process[0][2]-process[0][0];
    double avgTA= process[0][3];
    double avgW=process[0][4];
    for(int i=1;i<n;i++){
        process[i][2] = process[i-1][2] + process[i][1];
        process[i][3] = process[i][2] - process[i][0];
        process[i][4] = process[i][3] - process[i][1];
        avgW += process[i][4];
        avgTA += process[i][3];
    }
    cout<<"\nProcess Name\tArrival Time\tBurst Time\tCompletion Time\tTurn-Around Time\tWaiting Time";
    for(int i=0;i<n;i++){
        cout<<"\nP["<<i<<"] : \t\t"<<process[i][0]<<"\t\t"<<process[i][1]<<"\t\t"<<process[i][2]<<"\t\t"<<process[i][3]<<"\t\t\t"<<process[i][4];
    }
    cout<<"\nAverage Turn-Around Time : "<<avgTA/n;
    cout<<"\nAverage Waiting Time : "<<avgW/n;
}
bool comparebypriority(vector<int>& a,vector<int>& b){
    return a[5] < b[5] ;
}
void Priority(vector<vector<int>>& process){
    int n = process.size();
    for(int i=0;i<n;i++){
        cout<<"\nEnter the priority for process -> P["<<i<<"] : ";
        int c;
        cin>>c;
        process[i][5] = c;
    }
    sort(process.begin(),process.end(),comparebypriority);
    process[0][4]=0;
    process[0][2]=process[0][1];
    process[0][3]=process[0][2]-process[0][0];
    double avgTA= process[0][3];
    double avgW=process[0][4];
    for(int i=1;i<n;i++){
        process[i][2] = process[i-1][2] + process[i][1];
        process[i][3] = process[i][2] - process[i][0];
        process[i][4] = process[i][3] - process[i][1];
        avgW += process[i][4];
        avgTA += process[i][3];
    }
    cout<<"\nProcess Name\tArrival Time\tBurst Time\tCompletion Time\tTurn-Around Time\tWaiting Time\tPriority";
    for(int i=0;i<n;i++){
        cout<<"\nP["<<i<<"] : \t\t"<<process[i][0]<<"\t\t"<<process[i][1]<<"\t\t"<<process[i][2]<<"\t\t"<<process[i][3]<<"\t\t\t"<<process[i][4]<<"\t\t\t"<<process[i][5];
    }
    cout<<"\nAverage Turn-Around Time : "<<avgTA/n;
    cout<<"\nAverage Waiting Time : "<<avgW/n;
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
void roundRobin(vector<vector<int>>& process){
    int n = process.size();
    cout<<"\nEnter the Time Quantum : ";
    int s,currTime=0;
    cin>>s;
    vector<int> p(n,0);
    for(int i=0;i<n;i++){
        p[i] = process[i][1];
    }
    queue<vector<int>> q;
    for(int i=0;i<n;i++){
        process[i][5] = process[i][1];
        vector<int> v = process[i];
        q.push(v);
    }
    while(!q.empty()){
        vector<int> v1 = q.front();
        q.pop();
        int actual = v1[1];
        int no = find(p,actual);
        cout<<"\nSlot : "<<currTime <<" - "<<currTime+s<<" Process ["<<no<<"] ";
        int burst = v1[5];
        if(burst < s){
            v1[5] = 0;
            p[no] = currTime + s;
        }
        else if(burst==s){
            v1[5] = 0;
            p[no] = currTime + s;
        }
        else if(burst > s){
            v1[5] = v1[5]-s;
            q.push(v1);
        }
        currTime += s;
    }
    for(int i=0;i<n;i++){
        process[i][2] = p[i] ;
    }
    double avgTA = 0;
    double avgW = 0;
    for(int i=0;i<n;i++){
        process[i][3] = process[i][2] - process[i][0];
        process[i][4] = process[i][3] - process[i][1];
        avgW += process[i][4];
        avgTA += process[i][3];
    }
    cout<<"\nProcess Name\tArrival Time\tBurst Time\tCompletion Time\tTurn-Around Time\tWaiting Time";
    for(int i=0;i<n;i++){
        cout<<"\nP["<<i<<"] : \t\t"<<process[i][0]<<"\t\t"<<process[i][1]<<"\t\t"<<process[i][2]<<"\t\t"<<process[i][3]<<"\t\t\t"<<process[i][4];
    }
    cout<<"\nAverage Turn-Around Time : "<<avgTA/n;
    cout<<"\nAverage Waiting Time : "<<avgW/n;
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