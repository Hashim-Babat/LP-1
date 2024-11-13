#include<iostream>
using namespace std;

class Process{
    public :
        int id;
        string pname;

        Process():id(0),pname(""){};
};

class Election{
    public:
        Process process[10];
        bool isCrashed[10];
        int num;

        void input(){
            cout<<"Enter number of process :";
            cin>>num;

            for(int i=0;i<num;i++){
                cout<<"Enter process id : ";
                cin>>process[i].id;
                cout<<"Enter process name : ";
                cin>>process[i].pname;
            }
        }

        void crashHighestProcess(){
            int highestIndex = 0;
            for (int i = 1; i < num; i++) {
                if (process[i].id > process[highestIndex].id) {
                    highestIndex = i;
                }
            }
            isCrashed[highestIndex] = true;
            cout<<"The process with id : "<< process[highestIndex].id<<" is Crashed."<<endl;
        }

        void Bully(int initiatorID){
            int maxID = initiatorID;

            for(int i=0;i<num;i++){
                if(process[i].id > initiatorID && !isCrashed[i]){
                    cout<<initiatorID <<" send Election message to "<<process[i].id<<endl;
                    if(maxID < process[i].id){
                        maxID = process[i].id;
                    }
                }
            }

            cout<<"New Coodinator is process id  "<<maxID;
        }


        void Ring(int initiatorId){
            int startPos = -1;
            cout<<"Ring Message [";

            for(int i = 0 ; i < num; i++){
                if (process[i].id == initiatorId){
                    startPos = i;
                    break;
                }
            }

            int maxId = initiatorId;

            for(int i = 0; i < num;i++){
                int index = (startPos + i)%num;
                if(!isCrashed[index])
                {
                    cout<<process[i].id<<" ";
                    if(process[i].id > maxId) maxId = process[i].id;

                }
            }
            cout<<"]\n";

            cout<<"New Coordinator through Ring is : "<<maxId<<endl;
        }

};


int main(){
    Election election;
    election.input();

    election.crashHighestProcess();

    int initiatorId;
    cout << "Enter the ID of the process which detects the crash: ";
    cin >> initiatorId;

    int choice;
    while (true) {
        cout << "\nMenu:\n1. Bully Algorithm\n2. Ring Algorithm\n3. Exit\nChoose: ";
        cin >> choice;

        if (choice == 1) {
            election.Bully(initiatorId);
        } else if (choice == 2) {
            election.Ring(initiatorId);
        } else if (choice == 3) {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}