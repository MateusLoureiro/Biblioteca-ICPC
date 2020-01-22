//O range das queries é de (0, n-1), checar necessidade de decrementar o input
//Lembrar de buildar a seg
//Chamada de Merge já vem com os valores, e não com as posições na Seg

const int maxn = 1e5 + 10, inf = 1e9 + 10; //Checar os limites

struct no{
	//Definir no
	int val;
};

vector<int> ent(maxn);
vector<no> seg(4*maxn);

no merge(no esq, no dir){
	no ret;
	//Definir Merge
	ret.val = esq.val * dir.val;
	return ret;
}

void build(int pos, int i, int j){
	
	int esq = 2*pos;
	int dir = esq+1;
	int mid = (i + j) / 2;
	
	if(i == j){
		seg[pos] = {ent[i]}; //Inicializar com valores base ent[i]
		return;
	}
	build(esq, i, mid);
	build(dir, mid+1, j);
	seg[pos] = merge(seg[esq], seg[dir]);
}

void update(int pos, int i, int j, int x, int val){
	
	int esq = 2*pos;
	int dir = esq+1;
	int mid = (i + j) / 2;
	
	if(i == j){
		seg[pos] = {val}; //Inicializar com valores base val
		return;
	}
	if(x <= mid)
		update(esq, i, mid, x, val);
	else
		update(dir, mid+1, j, x, val);
	seg[pos] = merge(seg[esq], seg[dir]);
}	

no query(int pos, int i, int j, int l, int r){
	
	int esq = 2*pos;
	int dir = esq+1;
	int mid = (i+j)/2;
	
	if(r < i || l > j){
		return {1}; //Valor que não atrapalhe
	}
	if(j <= r && i >= l){
		return seg[pos];
	}
	
	return merge(query(esq, i, mid, l, r), query(dir, mid+1, j, l, r));
}
