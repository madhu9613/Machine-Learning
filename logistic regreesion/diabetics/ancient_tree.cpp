cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int t, n, k;
vector<int> tree[MAXN];
int weight[MAXN], color[MAXN], final_color[MAXN];
long long total_cost;

// Map to store the count of colors in each subtree
map<int, int>* dfs(int u, int p) {
    map<int, int>* my_map = new map<int, int>();

    for (int v : tree[u]) {
        if (v == p) continue;
        map<int, int>* child_map = dfs(v, u);

        // Small to large merging
        if (my_map->size() < child_map->size()) swap(my_map, child_map);
        for (auto &[col, cnt] : *child_map)
            (*my_map)[col] += cnt;

        delete child_map;
    }

    int col = color[u];
    if (col == 0) {
        // Choose a color that does not cause parent to become cutie
        for (int c = 1; c <= k; c++) {
            if ((*my_map)[c] <= 1) {
                col = c;
                break;
            }
        }
        color[u] = col;
    }

    (*my_map)[col]++;

    // Check if this node becomes cutie
    for (auto &[c, cnt] : *my_map) {
        if (cnt >= 2 && c != color[u]) {
            total_cost += weight[u];
            break;
        }
    }

    final_color[u] = color[u];
    return my_map;
}

void reset(int n) {
    for (int i = 1; i <= n; ++i) {
        tree[i].clear();
        final_color[i] = 0;
    }
    total_cost = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> t;
    while (t--) {
        cin >> n >> k;
        reset(n);

        for (int i = 1; i <= n; ++i)
            cin >> weight[i];

        for (int i = 1; i <= n; ++i)
            cin >> color[i];

        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            tree[u].push_back(v);
            tree[v].push_back(u);
        }

        dfs(1, 0);
        cout << total_cost << "\n";
        for (int i = 1; i <= n; ++i)
            cout << final_color[i] << " ";
        cout << "\n";
    }

    return 0;
}
