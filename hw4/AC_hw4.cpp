#include <bits/stdc++.h>
using namespace std;

#define llint long long

const long long INF = 1e18;
int n, m, k, S, T;
vector<vector<pair<long long, int>>> Graph;

int main(){
    // input
    cin >> n >> m >> k >> S >> T;
    S--, T--;
    Graph.resize(2*n);
    for (int i = 0; i < m; i++){
        int u, v, w, d;
        cin >> u >> v >> w >> d;
        u--, v--;
        
        if (d == 0){
            Graph[u].push_back({v, w});
            Graph[v].push_back({u, w});
            Graph[u+n].push_back({v+n, w});
            Graph[v+n].push_back({u+n, w});
        } else {
            Graph[u+n].push_back({v+n, w});
            Graph[v+n].push_back({u+n, w});
        }
    }
    for (int i = 0; i < k; i++){
        int key;
        cin >> key;
        key--;
        Graph[key].push_back({key+n, 0});
    }

    // process
    vector<long long> dis(2*n, INF);
    vector<bool> vis(2*n, false);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    dis[S] = 0;
    pq.push({0, S});

    while (pq.size()){
        long long nowDis = pq.top().first;
        int now = pq.top().second;
        pq.pop();

        if (vis[now]) continue;
        vis[now] = true;

        for (auto [nxt, w]: Graph[now]){
            if (nowDis+w < dis[nxt]){
                dis[nxt] = nowDis+w;
                pq.push({nowDis+w, nxt});
            }
        }
    }

    // output
    long long ans = min(dis[T], dis[T+n]);
    if (ans==INF){
        cout << -1 << "\n";
    }else{
        cout << ans << "\n";
    }

}