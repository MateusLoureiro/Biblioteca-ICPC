// Point update, range query

int n;

struct Node{
	// Atributos
	Node(){} // Elemento neutro	
	Node(/* Atributos */){} 	// Initialize
	Node(Node l, Node r){} // Merge
};

template <class Data, class Node = Node>
class SegTree {
private:
	vector<Data> ent;
	vector<Node> seg;
public:
	void init(vector<Data> a){
		ent = a;
		seg.resize(4*a.size());
		build();
	}
	
	void build(int pos = 0, int i = 0, int j = n-1){
		int esq = pos+pos+1, dir = pos+pos+2, mid = (i+j)>>1;
		if(i == j){
			seg[pos] = Node(ent[i]);
			return;
		}
		build(esq, i, mid);	build(dir, mid+1, j);
		seg[pos] = Node(seg[esq], seg[dir]);
	}
	
	void upd(int ind, Data val, int pos = 0, int i = 0, int j = n-1){
		int esq = pos+pos+1, dir = pos+pos+2, mid = (i+j)>>1;
		if(i == j){
			ent[ind] = val;
			seg[pos] = Node(val);
			return;
		}
		if(ind <= mid)	upd(ind, val, esq, i, mid);
		else	upd(ind, val, dir, mid+1, j);
		seg[pos] = Node(seg[esq], seg[dir]);
	}
	
	Node qry(int l, int r, int pos = 0, int i = 0, int j = n-1){
		int esq = pos+pos+1, dir = pos+pos+2, mid = (i+j)>>1;
		if(j < l || i > r)	return Node();
		if(l <= i && r >= j)	return seg[pos];
		return Node(qry(l, r, esq, i, mid), qry(l, r, dir, mid+1, j));
	}
};	
