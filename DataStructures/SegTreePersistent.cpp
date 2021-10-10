// by tfg50
struct Node{
	int v = 0;
	Node *l = this, *r = this;
};

int CNT = 1, mn, //sz = 2*ms * ((int)log2(ms) + 2) // TODO: number of calls to update * log2(range of seg);
Node buffer[sz], *root[]; // TODO: size of root vector

void pSegInit(int n){ // lembrar de chamar no main
	mn = n;
	CNT = 1;
	root[0] = &buffer[0];
}
 
Node* update(Node *rootAt, int idx, int val, int l = 0, int r = mn){ // [l, r)
	Node *node = &buffer[CNT++];
	*node = *rootAt;
	int mid = l+r >> 1;
	node->v += val;
	if(l+1 != r){
		if(idx < mid) node->l = update(rootAt->l, idx, val, l, mid);
		else node->r = update(rootAt->r, idx, val, mid, r);
	}
	return node;
}
 
int query(Node *node, int l, int r, int tl = 0, int tr = mn){ // [l, r)
	if(l <= tl && tr <= r) return node->v;
	if(tr <= l || tl >= r) return 0;
	int mid = (tl+tr) / 2;
	return query(node->l, l, r, tl, mid) + query(node->r, l, r, mid, tr);
}

