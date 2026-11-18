// 15068 - RedCapeFlyingCat Escapes the Maze 
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define llint long long
#define INF 1e18    // should be greater than n * w

vector<vector<pair<int, int>>> Graph;   // {room, weight}

int main() {
    // input
    int n, m, k, S, T;  // rooms, roads, key rooms, start room, target room
    cin >> n >> m >> k >> S >> T;
    S--; T--;   // convert 1-based to 0-based
    Graph.resize(2*n);  // two layers
    for (int _ = 0; _ < m; _++) {
        int u, v, w, d; // room u, room v, road weight, has door
        cin >> u >> v >> w >> d;
        u--; v--;

        if (d == 0) {
            // layer without door
            Graph[u].push_back({v, w});
            Graph[v].push_back({u, w});
        }
        // layer with door
        Graph[u+n].push_back({v+n, w});
        Graph[v+n].push_back({u+n, w});
    }
    for (int _ = 0; _ < k; _++) {
        int key;    // key room
        cin >> key;
        key--;
        Graph[key].push_back({key+n, 0});   // link from door-less layer to door layer, at key room
    }

    // process
    vector<llint> dis(2*n, INF);
    vector<bool> vis(2*n, false);
    priority_queue<pair<llint, int>, vector<pair<llint, int>>, greater<pair<llint, int>>> pq;   // min heap {dis, room}
    dis[S] = 0;
    pq.push({0, S});

    while (pq.size()) {
        llint nowDis = pq.top().first;
        int now = pq.top().second;
        pq.pop();

        if (vis[now]) continue;
        vis[now] = true;

        for (auto [nxt, w]: Graph[now]) {
            if (nowDis+w < dis[nxt]) {
                dis[nxt] = nowDis+w;
                pq.push({nowDis+w, nxt});
            }
        }
    }

    // output
    llint ans = min(dis[T], dis[T+n]);
    if (ans == INF) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}
