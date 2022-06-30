#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

class Vertex {
public:
    int idx; // порядковый номер в самом графе
    int counter = 0;
    bool visited = false;

    vector<int> edge_to;
    vector<int> edge_from;
    void add_from(int v) {
        if (edge_from.size() == 0) {
            counter = 1;
        }
        edge_from.push_back(v);
    }

    void add_to(int v) {
        edge_to.push_back(v);
    }
};

bool comp(Vertex l, Vertex r) {
    if (l.counter < r.counter) {
        return true;
    }
    else if (l.counter == r.counter) {
        if (l.idx < r.idx) {
            return true;
        }
    }
    return false;
}

//template<typename T>
//void MergeSort(T* arr, size_t l, size_t r, bool (*comp)(T l, T r));
//
//template<typename T>
//void MergeSort(vector <T>& arr, size_t l, size_t r, bool (*comp)(T l, T r))
//{
//    if (l >= r)
//        return;
//
//    size_t mid = (l + r) >> 1;
//    MergeSort(arr, l, mid, comp);
//    MergeSort(arr, mid + 1, r, comp);
//    merge(arr, l, r, mid, comp);
//}
//
//template<typename T>
//void merge(T* arr, size_t l, size_t r, size_t m, bool (*comp)(T l, T r));
//
//template<typename T>
//void merge(vector<T>& arr, size_t l, size_t r, size_t m, bool (*comp)(T l, T r)) {
//    if (l >= r || m < l || m > r)
//        return;
//    if (r == l + 1 && comp(arr[r], arr[l])) {
//        swap(arr[l], arr[r]);
//        return;
//    }
//
//    vector<T> tmp(&arr[l], &arr[r] + 1);
//
//    for (size_t i = l, j = 0, k = m - l + 1; i <= r; ++i) {
//        if (j > m - l) {
//            arr[i] = tmp[k++];
//        }
//        else if (k > r - l) {
//            arr[i] = tmp[j++];
//        }
//        else {
//            arr[i] = (comp(tmp[j], tmp[k])) ? tmp[j++] : tmp[k++];
//        }
//    }
//}
//
//void DFS(vector<Vertex>& graph, int parent) {
//    /*if (graph[parent].visited) {
//        return;
//    }*/
//    graph[parent].visited = true;
//    for (int i = 0; i < graph[parent].edge_to.size(); i++) {
//        int child = graph[parent].edge_to[i];
//        if (!graph[i].visited && graph[parent].edge_to[i] && i != parent) {
//            graph[child].counter = max(graph[child].counter, graph[parent].counter + 1);
//            DFS(graph, child);
//        }
//    }
//    return;
//}

vector<int> TopologicalSort(vector<vector<int>>& graph, vector<int>& child) {
    vector<int> ans;
    set<int> vert, nextVert;

    for (int i = 0; i < child.size(); i++) {
        if (child[i] == 0) {
            vert.insert(i);
        }
    }

    while (!vert.empty()) {
        int vert_begin = *vert.begin();
        vert.erase(vert.begin());
        ans.push_back(vert_begin);

        for (int next_V : graph[vert_begin]) {
            child[next_V]--;
            if (child[next_V] == 0) {
                nextVert.insert(next_V);
            }
        }

        if (vert.empty()) {
            copy(nextVert.begin(),
                nextVert.end(),
                inserter(vert, vert.begin()));
            nextVert.clear();
        } // update new level
    }
    return ans;
}

int main() {
    ifstream f1("input.txt");
    ofstream f2("output.txt");

    int n, m;
    f1 >> n >> m;

    vector<vector<int>> graph(n);
    vector<int> child(n);

    for (int i = 0; i < m; i++) {
        int v_from, v_to;
        f1 >> v_from >> v_to;
        graph[--v_from].push_back(--v_to); //исчисление с 0
        child[v_to]++; // счетчик ребер
    }

    vector<int> ans = TopologicalSort(graph, child);

    for (int i : ans) {
        f2 << i + 1 << " ";
    }

    return 0;
}