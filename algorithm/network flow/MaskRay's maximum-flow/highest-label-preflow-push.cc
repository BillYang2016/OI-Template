/*
 * Highest-label preflow-push algorithm
 * Ref: Network Flows: Theory, Algorithm and Applications 7.8 Highest-label preflow-push algorithm
 *
 * Time complexity: O(n^2*m^0.5)
 * The first phase 'relabel' is an optimization
 *
 * Verified by poj.org 1273, SPOJ FASTFLOW
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

long highest_label_preflow_push(long n, long src, long sink)
{
  vector<char> vis(n, 0);
  vis[src] = vis[sink] = 1;
  vector<long> ex(n, 0), h(n, 0);
  vector<long> head(2*n-1, -1), succ(n);
  vector<Edge*> cur(e, e+n);
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
  for (long level = n-1; ; ) {
    while (level >= 0 && head[level] < 0) level--;
    if (level < 0) break;
    long u = head[level];
    head[level] = succ[u];
    for (Edge*& it = cur[u]; it; it = it->next)
      if (it->c > 0 && level == h[it->v]+1) {
        long t = min(ex[u], it->c);
        ex[u] -= t;
        ex[it->v] += t;
        it->c -= t;
        it->rev->c += t;
        if (! vis[it->v]) {
          vis[it->v] = 1;
          succ[it->v] = head[level-1];
          head[level-1] = it->v;
        }
        if (! ex[u]) break;
      }
    if (! ex[u])
      vis[u] = 0;
    else {
      level = 2*n-2;
      for (Edge* it = e[u]; it; it = it->next)
        if (it->c > 0)
          level = min(level, h[it->v]+1);
      h[u] = level;
      succ[u] = head[level];
      head[level] = u;
      cur[u] = e[u];
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
    cout << highest_label_preflow_push(n, 0, n-1) << endl;
  }
}
