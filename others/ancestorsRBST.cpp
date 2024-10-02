#include<bits/stdc++.h>
using namespace std;
void print(vector<int>& v){
    for(int i=0;i<v.size();i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
}
void stringify(string s,vector<int>& v){
    int n = s.size(),i=0,c=1;
    while(i<n){
        if(c==1){
            int a = int(s[i]-48);
            c=0;
            i++;
            v.push_back(a);
        }
        else{
            int b = int(s[i]-48);
            i++;
            if(i<n){
                int z = int(s[i]-48);
                i++;
                b=b*10+z;
            }
            c=1;
            v.push_back(b);
        }
    }
}
void helper(vector<int>& v,vector<int>& ans,int s,int e,int i){
    if(s>e) return;
    if(i>ans.size()) return;
    int mid;
    if(s!=e) mid = ((s+e)/2)+1;
    else mid = s;
    if(i<ans.size()) ans[i]=v[mid];
    helper(v,ans,s,mid-1,2*i+1);
    helper(v,ans,mid+1,e,2*i+2);
}
void ancestors(string s,int x){
    vector<int> v;
    stringify(s,v);
    print(v);
    sort(v.begin(),v.end());
    reverse(v.begin(),v.end());
    print(v);
    vector<int> ans(v.size()*2,0);
    helper(v,ans,0,v.size()-1,0);
    print(ans);
    int j=-1;
    for(int i=0;i<ans.size();i++){
        if(ans[i]==x){
            j=i;
            break;
        }
    }
    if(j>=0){
        while(true){
            j/=2;
            cout<<ans[j]<<" ";
            if(j==0) break;
        }
    }
    else{
        cout<<x<<" does not exists!!!"<<endl;
    }
    
}
int main(){
    string s="12345678";
    int x = 56;
    ancestors(s,x);
}