/*
 * Improved shortest augmenting path algorithm (an improvement of Edmonds-Karp algorithm)
 * Ref: Network Flows: Theory, Algorithm and Applications 7.4 Shortest augmenting path algorithm
 *
 * Time complexity: O(n^2*m)
 * Verified by poj.org 1273, SPOJ FASTFLOW
 */
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

#define ALL(x) (x).begin(), (x).end()
#define FOR(i, a, b) for (long i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 200, M = 200;

struct Edge {
  long v, c;
  Edge *next, *rev;
} *e[N], pool[M*2], *allo;

void insert(long u, long v, long c)
{
  allo->v = v; allo->c = c; allo->next = e[u]; e[u] = allo++;
  allo->v = u; allo->c = 0; allo->next = e[v]; e[v] = allo++;
  e[u]->rev = e[v];
  e[v]->rev = e[u];
}

long shortest_augmenting_path(long n, long src, long sink)
{
  long flow = 0;
  vector<long> h(n, 0), nh(n+1, 0);
  nh[0] = n;
  vector<Edge> st;
  vector<Edge*> cur(e, e+n);
  while (h[src] < n) {
    Edge y;
    y.v = src;
    y.c = LONG_MAX;
    y.next = cur[src];
    for (st.push_back(y); st.size(); ) {
      Edge& x = st.back();
      for (; x.next; x.next = x.next->next)
        if (x.next->c > 0 && h[x.v] == h[x.next->v]+1)
          break;
      cur[x.v] = x.next;
      if (x.next) {
        Edge y;
        y.v = x.next->v;
        y.c = min(x.c, x.next->c);
        y.next = cur[y.v];
        if (y.v == sink) {
          REP(i, st.size()) {
            st[i].c -= y.c;
            st[i].next->c -= y.c;
            st[i].next->rev->c += y.c;
          }
          flow += y.c;
          while (st.size() && ! st.back().c)
            st.pop_back();
        } else
          st.push_back(y);
      } else {
        long minh = n;
        for (Edge* it = e[x.v]; it; it = it->next)
          if (it->c > 0)
            minh = min(minh, h[it->v]+1);
        if (! --nh[h[x.v]]) goto out;
        nh[h[x.v] = minh]++;
        cur[x.v] = e[x.v];
        st.pop_back();
      }
    }
  }
out:
  return flow;
}

int main()
{
  long n, m, u, v, c;
  while (cin >> m >> n) {
    allo = pool;
    REP(i, n)
      e[i] = NULL;
    while (m--) {
      cin >> u >> v >> c;
      insert(u-1, v-1, c);
    }
    cout << shortest_augmenting_path(n, 0, n-1) << endl;
  }
}
