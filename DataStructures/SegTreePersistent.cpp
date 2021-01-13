// by tfg

struct Node{
	int v = 0;
	Node *l = this, *r = this;
};

int CNT = 1;
Node buffer[ms * 20];
 
Node* update(Node *root, int idx, int val, int l = 0, int r = mn){
	Node *node = &buffer[CNT++];
	*node = *root;
	int mid = (l + r) / 2;
	node->v += val;
	if(l+1 != r){
		if(idx < mid) node->l = update(root->l, idx, val, l, mid);
		else node->r = update(root->r, idx, val, mid, r);
	}
	return node;
}
 
int query(Node *node, int l, int r, int tl = 0, int tr = mn){
	if(l <= tl && tr <= r) return node->v;
	if(tr <= l || tl >= r) return 0;
	int mid = (tl+tr) / 2;
	return query(node->l, l, r, tl, mid) + query(node->r, l, r, mid, tr);
}
