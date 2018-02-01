/*
 * Capacity scaling algorithm
 * Ref: Network Flows: Theory, Algorithm and Applications 8.5 Dynamic tree implementations
 *
 * Time complexity: O(m^2*log(U))
 * Verified by poj.org 1273
 */
#include <algorithm>
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
} *e[N], *pre[N], pool[M*2], *allo;

void insert(long u, long v, long c)
{
  allo->v = v; allo->c = c; allo->next = e[u]; e[u] = allo++;
  allo->v = u; allo->c = 0; allo->next = e[v]; e[v] = allo++;
  e[u]->rev = e[v];
  e[v]->rev = e[u];
}

long capacity_scaling(long n, long src, long sink, long cap)
{
  long flow = 0;
  vector<long> st;
  for (long d = 63-__builtin_clzl(cap); d; d >>= 1) {
    st.clear();
    for(;;) {
      fill_n(pre, n, (Edge*)0);
      pre[src] = (Edge*)1;
      for (st.push_back(src); st.size(); ) {
        long v = st.back();
        st.pop_back();
        for (Edge* it = e[v]; it; it = it->next)
          if (it->c >= d && ! pre[it->v]) {
            pre[it->v] = it;
            if (it->v == sink) {
              st.clear();
              break;
            }
            st.push_back(it->v);
          }
      }
      if (! pre[sink]) break;
      for (long v = sink; v != src; v = pre[v]->rev->v) {
        pre[v]->c -= d;
        pre[v]->rev->c += d;
      }
      flow += d;
    }
  }
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
    cout << capacity_scaling(n, 0, n-1, 10000000) << endl;
  }
}
