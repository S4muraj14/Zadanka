class Solution {
public:
    //O(n log n)
    //const int max_n = 307; // w teorii moze byc nawet 10^6
    unordered_map<int,pair<int,int>> m; //first - xor, second - {suma dlugosci, ile jest}
    int pref_xor[307];
    int countTriplets(vector<int>& arr) {
        int n = arr.size();
        for(int i = 0; i < n; i++){
            if(i == 0) pref_xor[i] = arr[i];
            else pref_xor[i] = pref_xor[i-1]^arr[i];
            m[pref_xor[i]].first += i+1; //ewentualnie +1
            m[pref_xor[i]].second++;
        }
        int ans = 0;
        for(int i = 0; i < n-1; i++){
            m[pref_xor[i]].first -= i+1; //ewentualnie +1
            m[pref_xor[i]].second--;
            int akt = arr[i]^pref_xor[i];
            int dl = m[akt].first;
            dl -= (i+1)*m[akt].second;
            ans += dl;
        }
        return ans;
    }
};
