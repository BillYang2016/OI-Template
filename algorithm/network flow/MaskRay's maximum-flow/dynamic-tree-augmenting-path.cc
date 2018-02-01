/*
 * Dynamic tree implementation of shortest augmenting path
 * Ref: Network Flows: Theory, Algorithm and Applications 8.5 Dynamic tree implementations
 *
 * The link-cut tree implementation augments each node with two pointers 'l, r' to make a doubly-linked list of siblings, and another pointer 'eldest' to indicate an arbitrary child.
 *
 * Time complexity: O(n*m*log(n))
 * Verified by poj.org 1273
 */
#include <algorithm>
#include <climits>
#include <iostream>
#include <utility>
using namespace std;

#define FOR(i, a, b) for (long i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 200, M = 200;

long h[N];
struct Edge {
  long v, c;
  Edge *next, *pre;
} *e[N], pool[M*2], *allo;

namespace LCT {
extern struct Node null, nodes[];
struct Node {
  Edge* e;
  long dlt;
  Node *c[2], *p, *l, *r, *eldest, *opt;
  void init(Edge* e) {
    this->e = e;
    dlt = 0;
    c[0] = c[1] = p = &null;
    opt = this;
    eldest = NULL;
  }
  void mconcat() {
    // in case of a tie, choose the node closest to the root
    opt = c[0]->opt->e->c <= e->c ? c[0]->opt : this;
    if (c[1]->opt->e->c < e->c)
      opt = c[1]->opt;
  }
  void untag() {
    if (dlt) {
      c[0]->dlt += dlt;
      c[1]->dlt += dlt;
      if (e->c != LONG_MAX) {
        e->c += dlt;
        e->pre->c -= dlt;
      }
      dlt = 0;
    }
  }
  void setc(long d, Node* x) {
    c[d] = x;
    x->p = this;
  }
  void zag(long d) {
    Node *x = c[d], *p = this->p;
    setc(d, x->c[d^1]);
    mconcat();
    x->setc(d^1, this);
    x->p = p;
    if (p->c[0] == this)
      p->c[0] = x;
    else if (p->c[1] == this)
      p->c[1] = x;
  }
  void splay() {
    while (p->c[0] == this || p->c[1] == this) {
      Node *p = this->p, *g = p->p;
      if (g->c[0] == p || g->c[1] == p) {
        g->untag(); p->untag(); untag();
        if (g->c[0] == p) {
          if (p->c[0] == this) g->zag(0), p->zag(0);
          else p->zag(1), g->zag(0);
        } else {
          if (p->c[0] != this) g->zag(1), p->zag(1);
          else p->zag(0), g->zag(1);
        }
      } else {
        p->untag(); untag();
        p->zag(p->c[0] != this);
      }
    }
    untag();
    mconcat();
  }
  void expose() { static int c = 0; ++c;
    Node *x = this, *y = &null;
    for (; x != &null; y = x, x = x->p) {
      x->splay();
      x->c[1] = y; // mconcat in last splay
    }
    splay();
  }
  void link(Node* par, Edge* e) {
    expose();
    this->e = e;
    mconcat();
    p = par;
    if (par->eldest) {
      (l = par->eldest->l)->r = this;
      (r = par->eldest)->l = this;
    } else
      par->eldest = l = r = this;
  }
  void cut(Edge* e) {
    expose();
    this->e = e;
    Node* x = c[0];
    while (x->untag(), x->c[1] != &null)
      x = x->c[1];
    x->splay();
    x->setc(1, &null);
    x->mconcat();
    p = &null;
    if (r == this)
      x->eldest = 0;
    else {
      l->r = r;
      r->l = l;
      if (x->eldest == this)
        x->eldest = r;
    }
  }
  long root() {
    Node* x = this;
    expose();
    while (x->c[0] != &null) {
      x = x->c[0];
      x->untag();
    }
    return x-nodes;
  }
  Node* find_opt() {
    expose();
    Node* r = opt;
    if (r != &null)
      r->splay();
    return r->opt;
  }
  void add(long x) {
    expose();
    dlt += x;
  }
} null, nodes[N];
};

void insert(long u, long v, long c)
{
  allo->v = v; allo->c = c; allo->next = e[u]; e[u] = allo++;
  allo->v = u; allo->c = 0; allo->next = e[v]; e[v] = allo++;
  e[u]->pre = e[v];
  e[v]->pre = e[u];
}

long tree_augmenting_path(long n, long src, long sink)
{
  Edge enull;
  enull.c = LONG_MAX;
  enull.pre = &enull;
  LCT::Node* a = LCT::nodes;
  LCT::null.init(&enull);
  REP(i, n)
    a[i].init(&enull);
  fill_n(h, n, 0);
  long flow = 0, u = src;
  while (h[src] < n) {
    bool retreat = true;
    long minh = n;
    for (Edge* it = e[u]; it; it = it->next)
      if (it->c > 0) {
        if (h[u] == h[it->v]+1) {
          a[u].link(&a[it->v], it);
          u = a[it->v].root();
          retreat = false;
          break;
        }
        minh = min(minh, h[it->v]+1);
      }
    if (retreat) {
      h[u] = minh;
      LCT::Node* eldest = a[u].eldest;
      if (eldest)
        for (LCT::Node* v = eldest; ; v = v->r) {
          v->cut(&enull);
          // v->r is still available
          if (v->r == v) break;
        }
    } else if (u == sink) {
      LCT::Node* v = a[src].find_opt();
      flow += v->e->c;
      a[src].add(- v->e->c);
      do v->cut(&enull), v = a[src].find_opt();
      while (! v->e->c);
    }
    u = a[src].root();
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
    cout << tree_augmenting_path(n, 0, n-1) << endl;
  }
}
