//O range das queries é de (0, n-1), checar necessidade de decrementar o input
//Lembrar de buildar a seg
//Chamada de Merge já vem com os valores, e não com as posições na Seg

const int maxn = 1e5 + 10, inf = 1e9 + 10; //Checar os limites

struct no{
	//Definir no
	int zeros, ones, twos;
};

vector<int> ent(maxn), lazy(4*maxn);
vector<no> seg(4*maxn);

no merge(no esq, no dir){
	no ret;
	//Definir Merge
	return ret;
}

void build(int pos, int i, int j){
	
	int esq = 2*pos;
	int dir = esq+1;
	int mid = (i + j) / 2;
	
	lazy[pos] = 0;
	
	if(i == j){
		seg[pos] = {ent[i]}; //Inicializar com valores base ent[i]
		return;
	}
	build(esq, i, mid);
	build(dir, mid+1, j);
	seg[pos] = merge(seg[esq], seg[dir]);
}

void apply(int pos, int l, int r){
	if(lazy[pos]){
		int esq = 2*pos;
		int dir = esq+1;
		
		seg[pos].num = lazy[pos] * (r-l+1); //Definir Propagação da lazy na Seg
		
		if(l != r){ //Definir propagação da lazy na lazy
			lazy[esq] += lazy[pos];
			lazy[dir] += lazy[pos];
		}
		lazy[pos] = 0;
	}
	
}

no query(int pos, int i, int j, int l, int r){
	
	int esq = 2*pos;
	int dir = esq+1;
	int mid = (i+j)/2;
	
	apply(pos, i, j);
	
	if(r < i || l > j){
		return {0, 0, 0}; //Valor que não atrapalhe
	}
	if(j <= r && i >= l){
		return seg[pos];
	}
	
	return merge(query(esq, i, mid, l, r), query(dir, mid+1, j, l, r));
}

void update(int pos, int i, int j, int l, int r, int val){
	
	int esq = 2*pos;
	int dir = esq+1;
	int mid = (i+j)/2;
	
	apply(pos, i, j);
	
	if(r < i || l > j){
		return;
	}
	if(j <= r && i >= l){
		lazy[pos] = val;
		apply(pos, i, j);
		return;
	}
	
	update(esq, i, mid, l, r, val); 
	update(dir, mid+1, j, l, r, val);
	seg[pos] = merge(seg[esq], seg[dir]);
}
