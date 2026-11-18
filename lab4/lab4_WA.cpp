// 14062 - RedCapeFlyingCat Escapes the Maze Again 
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define llint long long
#define INF 1e18

vector<vector<tuple<int, int>>> Graph;

int main() {
    int n, m, k, S, T, type;
    cin >> n >> m >> k >> S >> T >> type;
    S--; T--;
    Graph.resize(2*n);
    vector<bool> is_door(n, false);
    for (int _ = 0; _ < m; _++) {
        int u, v, w, d;
        cin >> u >> v >> w >> d;
        u--; v--;
        
        if (d == 0) {
            Graph[u].push_back({v, w});
            Graph[v].push_back({u, w});
            Graph[u+n].push_back({v+n, w});
            Graph[v+n].push_back({u+n, w});
        } else {
            Graph[u+n].push_back({v+n, w});
            Graph[v+n].push_back({u+n, w});
        }
    }
    vector<bool> is_key(n, false);
    for (int _ = 0; _ < k; _++) {
        int key;
        cin >> key;
        key--;
        Graph[key].push_back({key+n, 0});
        is_key[key] = true;
    }

    vector<vector<int>> portals;
    vector<int> port_q;
    vector<int> room_portals(n, -1);
    int P;
    cin >> P;
    portals.resize(P);
    port_q.resize(P);
    for (int i = 0; i < P; i++) {
        int c, q;
        cin >> c >> q;
        port_q[i] = q;
        for (int _ = 0; _ < c; _++) {
            int p_i;
            cin >> p_i;
            portals[i].push_back(p_i);
            room_portals[p_i] = i;
        }
    }

    // process
    vector<llint> dis(2*n, INF);
    vector<bool> vis(2*n, false);
    priority_queue<pair<llint, int>, vector<pair<llint, int>>, greater<pair<llint, int>>> pq;
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

        // Check Portal
        int p = room_portals[now];
        if (p != -1) {
            int q = port_q[p];
            for (int room: portals[p]) {
                if (nowDis+q < dis[room]) {
                    //dis[room] = nowDis+q;
                    //pq.push({nowDis+q, room});
                }
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
