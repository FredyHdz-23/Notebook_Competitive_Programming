#include <template.h>

const int N=5005; 
int dp[N][N];

int lcs(string&a,string&b){
    int n=sz(a),m=sz(b);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) dp[i][j]= (a[i-1]==b[j-1]?dp[i-1][j-1]+1:max(dp[i-1][j],dp[i][j-1]));
    }
    return dp[n][m];
}

string rec(string&a,string&b){
    string s;int i=sz(a),j=sz(b);
    while(i&&j){
        if(a[i-1]==b[j-1])s+=a[i-1],i--,j--;
        else if(dp[i-1][j]>=dp[i][j-1])i--;
        else j--;
    }
    reverse(all(s));return s;
}