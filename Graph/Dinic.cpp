//By: Amigos do Beto
//Grafo é uma lista de arestas
//adj[u]: índice na lista da primeira aresta com origem em u
//ant[u]: índice da proxima aresta a ser visitada na lista de u (-1 caso ela não exista)
const int maxv = 1e3; // Quantidade maxima de vertices
const int maxe = 1e5; // Quantidade maxima de arestas

int adj[maxv], to[maxe], ant[maxe], wt[maxe], z, n;
int copy_adj[maxv], fila[maxv], level[maxv];

void flowinit() { // Lembrar de chamar no main
  memset(adj, -1, sizeof adj);
  z = 0;
}

//Adiciona aresta (u, v) com capacidade k e outra (v, u) com flow 0;
//Aresta "complementar" a aresta z tem ind (z^1);
void add(int u, int v, int k) {
  to[z] = v;
  ant[z] = adj[u];
  wt[z] = k;
  adj[u] = z++;
  swap(u, v);
  to[z] = v;
  ant[z] = adj[u];
  wt[z] = 0; // Lembrar de colocar = 0
  adj[u] = z++;
}

//Constrói o grafo de levels enquanto o sink é alcançável
int bfs(int source, int sink) {
  memset(level, -1, sizeof level);
  level[source] = 0;
  int front = 0, size = 0, u;
  fila[size++] = source;
  while(front < size) {
    u = fila[front++];
    for(int i = adj[u]; i != -1; i = ant[i]) {
      if(wt[i] && level[to[i]] == -1) {
        level[to[i]] = level[u] + 1;
        fila[size++] = to[i];
      }
    }
  }
  return level[sink] != -1;
}

//Busca o bottleneck de cada augmenting path
int dfs(int v, int sink, int flow) {
  if(v == sink) return flow;
  int f;
  for(int &i = copy_adj[v]; i != -1; i = ant[i]) {
    if(wt[i] && level[to[i]] == level[v] + 1 && 
      (f = dfs(to[i], sink, min(flow, wt[i])))) {
      wt[i] -= f;
      wt[i ^ 1] += f;
      return f;
    }
  }
  return 0;
}

int maxflow(int source, int sink) {
  int ret = 0, flow;
  while(bfs(source, sink)) {
    memcpy(copy_adj, adj, sizeof adj);
    while((flow = dfs(source, sink, 1 << 30))) { //Tem que ter dois parenteses
      ret += flow;
    }
  }
  return ret;
}

