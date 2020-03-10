//maxn > 2*(quantidade de variáveis booleanas)
//No main, para negar a variavel de numero x, basta adicionar ~x
vector<int> adj[maxn];
int idx[maxn], low[maxn], z, comp[maxn], ncomp;
stack<int> st;

int dfs(int u){
	//Se visitado, retorna idx[u] caso o nó ainda não esteja em um SCC
	if(~idx[u]) 
		return idx[u] ? idx[u] : z;
	
	low[u] = idx[u] = z++;
	st.push(u);
	for(int v : adj[u]){
		//Atualiza o low[u] com os idx dos nós daquele SCC
		low[u] = min(low[u], dfs(v));
	}
	
	//Popando a pilha até termos a "raiz" do SCC, onde low[u] == idx[u]
	if(low[u] == idx[u]){
		while(st.top() != u){
			int v = st.top();
			idx[v] = 0;
			low[v] = low[u];
			comp[v] = ncomp;
			st.pop();
		}
		idx[st.top()] = 0;
		st.pop();
		comp[u] = ncomp++;
	}
	
	//Retorna o menor valor alcançado por aquele nó, para atualizar a raiz do SCC
	return low[u];
}

//Lembrar de limpar o grafo em caso de multiplos testes
bool solveSat(int n){
	memset(idx, -1, sizeof idx);
	z = 1;
	ncomp = 0;
	for(int i =0; i < 2*n; i++)
		dfs(i);
	
	for(int i = 0; i < 2*n; i++)
		if(comp[i] == comp[i^1])
			return false;
	return true;
}

//Mapeia os numeros para seus devidos lugares no grafo
int trad(int v) { return v < 0 ? (~v)*2^1 : v*2; }
void add(int a, int b) { adj[trad(a)].push_back(trad(b)); }
void addOr(int a, int b) { add(~a, b); add(~b, a); }
void addImp(int a, int b) { addOr(~a, b); }
void addEqual(int a, int b) { addOr(a, ~b); addOr(~a, b); }
void addDiff(int a, int b) { addEqual(a, ~b); }
// value[i] = comp[trad(i)] < comp[trad(~i)];
