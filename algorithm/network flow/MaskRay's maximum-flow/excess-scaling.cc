/*
 * Excess scaling algorithm
 * Ref: Network Flows: Theory, Algorithm and Applications 7.9 Excess scaling algorithm
 *
 * Time complexity: O(n*m+n^2*log(U))
 * The first phase 'relabel' is an optimization
 *
 * Verified by poj.org 1273
 */
#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
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

void relabel(long n, long src, long sink, vector<long>& h)
{
  queue<long> q;
  fill(ALL(h), n);
  h[sink] = 0;
  for (q.push(sink); q.size(); ) {
    long u = q.front();
    q.pop();
    for (Edge* it = e[u]; it; it = it->next)
      if (it->rev->c > 0 && h[it->v] == n) {
        h[it->v] = h[u]+1;
        q.push(it->v);
      }
  }
  h[src] = n;
}

long excess_scaling(long n, long src, long sink)
{
  vector<char> vis(n, 0);
  vis[src] = vis[sink] = 1;
  vector<long> ex(n, 0), h(n, 0);
  vector<long> head(2*n-1), succ(n);
  vector<Edge*> cur(n);
  relabel(n, src, sink, h);
  for (Edge* it = e[src]; it; it = it->next)
    if (it->c > 0) {
      ex[it->v] += it->c;
      it->rev->c += it->c;
      it->c = 0;
      if (! vis[it->v]) {
        vis[it->v] = 1;
        succ[it->v] = head[h[it->v]];
        head[h[it->v]] = it->v;
      }
    }
  long d = *max_element(ALL(ex));
  if (! d) return 0;
  for (d = 1L << 63-__builtin_clzl(d); d; d >>= 1) {
    copy(e, e+n, cur.begin());
    fill(ALL(vis), 0);
    vis[src] = vis[sink] = 1;
    fill(ALL(head), -1);
    REP(i, n)
      if (2*ex[i] > d && ! vis[i]) {
        vis[i] = 1;
        succ[i] = head[h[i]];
        head[h[i]] = i;
      }
    for (long level = 0; level < 2*n-1; )
      if (head[level] < 0)
        level++;
      else {
        bool found = false;
        long u = head[level];
        for (Edge*& it = cur[u]; it; it = it->next)
          if (it->c > 0 && level == h[it->v]+1) {
            found = true;
            long t = min(ex[u], it->c);
            if (it->v != src && it->v != sink)
              t = min(t, d-ex[it->v]);
            ex[u] -= t;
            ex[it->v] += t;
            it->c -= t;
            it->rev->c += t;
            if (2*ex[it->v] > d && ! vis[it->v]) {
              vis[it->v] = 1;
              succ[it->v] = head[level-1];
              head[level-1] = it->v;
              level--;
              break;
            }
            if (2*ex[u] <= d) break;
          }
        if (2*ex[u] <= d) {
          vis[u] = 0;
          head[h[u]] = succ[u];
        } else if (! found) {
          head[h[u]] = succ[u];
          h[u] = 2*n-2;
          for (Edge* it = e[u]; it; it = it->next)
            if (it->c > 0)
              h[u] = min(h[u], h[it->v]+1);
          succ[u] = head[h[u]];
          head[h[u]] = u;
          cur[u] = e[u];
        }
      }
  }
  return ex[sink];
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
      if (u != v)
        insert(u-1, v-1, c);
    }
    cout << excess_scaling(n, 0, n-1) << endl;
  }
}
