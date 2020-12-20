// src: tfg (with some modifications made by me) 
class HLD {
public:

	vector<int> in, out, p, rin, sz, head, h;
  vector<vector<int>> edges;
  int t;

  void init(int n) {	// this doesn't delete edges!
    sz.resize(n);			// size of subtree
    in.resize(n);			// time of entering node in dfs
    out.resize(n);		// time of leaving the node in dfs
    rin.resize(n);		// inverse of array in
    p.resize(n);			// parent node
    edges.resize(n);	// adjacency list
    head.resize(n);		// head (ancestor) of heavy block
    h.resize(n);			// height of node
  }

  void addEdge(int u, int v) {
    edges[u].push_back(v);
    edges[v].push_back(u);
  }

  void setRoot(int n) {
    t = 0;
    p[n] = n;
    h[n] = 0;
    prep(n, n);
    head[n] = n;
    hld(n);
  }

  int getLCA(int u, int v) {
    while(!inSubtree(head[u], v))
      u = p[head[u]];
    while(!inSubtree(head[v], u))
      v = p[head[v]];
    return in[u] < in[v] ? u : v;
  }
	
	// is v in the subtree of u?
  bool inSubtree(int u, int v) {	
    return in[u] <= in[v] && in[v] < out[u];
  }
	
	// returns ranges [l, r) of the path (if(inc) -> path includes the ancestor)
  vector<pair<int, int>> getPathtoAncestor(int u, int anc, bool inc = 1) {	
    vector<pair<int, int>> ans;
   	while(head[u] != head[anc]) {	//assert(inSubtree(anc, u));
      ans.emplace_back(in[head[u]], in[u] + 1);
      u = p[head[u]];
    }
    ans.emplace_back(in[anc] + !inc, in[u] + 1);
    return ans;
  }
  
  void prep(int on, int par) {
    sz[on] = 1;
    p[on] = par;
    for(int i = 0; i < (int) edges[on].size(); i++) {
      int &u = edges[on][i];
      if(u == par) {
        swap(u, edges[on].back());
        edges[on].pop_back();
        i--;
      } else {
        h[u] = 1 + h[on];
        prep(u, on);
        sz[on] += sz[u];
        if(sz[u] > sz[edges[on][0]]) {
          swap(edges[on][0], u);
        }
      }
    }
  }

  void hld(int on) {
    in[on] = t++;
    rin[in[on]] = on;
    for(auto u : edges[on]) {
      head[u] = (u == edges[on][0] ? head[on] : u);
      hld(u);
    }
    out[on] = t;
  }
};
