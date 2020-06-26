//src: Amigos do Beto
//mlg = floor(log2(maxn))

const int ms = 1e5 + 10, mlg = log2(ms)+10; // Checar limites
int par[ms][mlg+1], lvl[ms];
vector<int> adj[ms]; // Modificar para grafos com peso

void dfs(int v, int p, int l = 0) { // Chamar como dfs(root, root)
  lvl[v] = l;
  par[v][0] = p;
  for(int k = 1; k <= mlg; k++) {
    par[v][k] = par[par[v][k-1]][k-1];
  }
  for(int u : adj[v]) { // Modificar para grafos com peso
    if(u != p) dfs(u, v, l + 1);
  }
}

/*
// Para grafos com peso, ja pega as distancias até o nó 0
const int inf = 1e18; // Checar infinito
int dist[ms];
void dfs(int v, int p, int l = 0, int d = 0) { // chamar como dfs(root, root)
  lvl[v] = l;
  dist[v] = d;
  par[v][0] = p;
  for(int k = 1; k <= mlg; k++) {
    par[v][k] = par[par[v][k-1]][k-1];
  }
  int u;
  for(ii it : adj[v]) { //Modificar para grafos com peso
    u = it.first;
    if(u != p) 
			dfs(u, v, l + 1, d + it.second);
  }
}
*/

int lca(int a, int b) {
  if(lvl[b] > lvl[a]) swap(a, b);
  for(int i = mlg; i >= 0; i--) {
    if(lvl[a] - (1 << i) >= lvl[b]) a = par[a][i];
  }
  if(a == b) return a;
  for(int i = mlg; i >= 0; i--) {
    if(par[a][i] != par[b][i]) a = par[a][i], b = par[b][i];
  }
  return par[a][0];
}
