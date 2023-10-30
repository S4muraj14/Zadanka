#include <bits/stdc++.h>

using namespace std;

const int max_n = 1007;
int arr[max_n];
int ile[max_n];

vector<int> ans;

int find_mex(int n){
    for(int i = 0 ; i<= n; i++) if(!ile[i]) return i;
    return -1;
}

int main(){

    int t;
    cin >> t;

    while(t--){

        int n;
        cin >> n;

        int ile_pop = 0;
        for(int i = 0; i < n; i++){
            cin >> arr[i];
            if(arr[i] == i) ile_pop++;
            ile[arr[i]]++;
        }

        int k = 0;
        while(ile_pop != n){
            k++;

            int m = find_mex(n);
    
            if(m == n){
                for(int i = 0; i < n; i++){
                    if(arr[i] != i){
                        ans.push_back(i);
                        ile[arr[i]]--;
                        ile[n]++;
                        arr[i] = n;
                        break;
                    }
                }
            }

            else{
                ile_pop++;
                ans.push_back(m);
                ile[arr[m]]--;
                ile[m]++;
                arr[m] = m;
            }
        }

        cout << k << '\n';
        for(auto x: ans) cout << x+1 << ' ';
        cout << '\n';

        ans.clear();
        for(int i = 0 ; i <= n;i++) ile[i] = 0;
        

    }


    return 0;
}