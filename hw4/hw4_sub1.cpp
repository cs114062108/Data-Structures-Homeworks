#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define llint long long
#define INF 1e18    // should be greater than n * w

vector<vector<pair<llint, int>>> Graph;

int main() {
    // input
    int n, m, k, S, T;  // rooms, roads, key rooms, start room, target room
    cin >> n >> m >> k >> S >> T;
    S--; T--;   // convert 1-based to 0-based
    Graph.resize(n);
    for (int _ = 0; _ < m; _++) {
        int u, v, w, d; // room u, room v, road weight, has door
        cin >> u >> v >> w >> d;
        u--; v--;

        Graph[u].push_back({v, w});
        Graph[v].push_back({u, w});
    }
    for (int _ = 0; _ < k; _++) {
        int key;    // key room
        cin >> key;
        key--;
    }

    // process
    vector<llint> dis(n, INF);
    vector<bool> vis(n, false);
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
    llint ans = dis[T];
    if (ans == INF) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}
