// Range update, range query

int n;

struct LazyContext{
	// Atributes
	bool on;
	LazyContext(){} // Neutral element of update operation
	LazyContext(/* Atributos */){} // Initilization
	void reset(){}  // Reset to neutral element
	//void set(int x, int y) {}	// If prop depends on the range
	void operator += (LazyContext lazy) {} // Lazy to lazy prop
};

struct Node{
	// Atributes
	Node(){} // Neutral element of query operation
	Node(/* Atributos */){} 	// Initialize
	Node(Node l, Node r){} // Merge
	void apply(LazyContext lazy){} // Lazy to seg prop
};


template <class Data, class LazyContext = LazyContext, class Node = Node>
class SegTree{
private:
	vector<Data> ent;
	vector<Node> seg;
	vector<LazyContext> lazy;
public:
	void init(vector<Data> a){
		ent = a;
		seg.resize(4*a.size());
		lazy.resize(4*a.size());
		build();
	}
	
	void build(int pos = 0, int i = 0, int j = n-1){
		int esq = pos+pos+1, dir = pos+pos+2, mid = (i+j)>>1;
		//lazy[pos].set(i, j); // If prop depends on range
		if(i == j){
			seg[pos] = Node(ent[i]);
			return;
		}
		build(esq, i, mid); build(dir, mid+1, j);
		seg[pos] = Node(seg[esq], seg[dir]);
	}

	void apply(int pos, int l, int r){
		if(lazy[pos].on){
			int esq = pos+pos+1, dir = pos+pos+2;
			seg[pos].apply(lazy[pos]);
			if(l != r){
				lazy[esq] += lazy[pos];
				lazy[dir] += lazy[pos];
			}
			lazy[pos].reset();
		}
	}

	void upd(int l, int r, LazyContext val, int pos = 0, int i = 0, int j = n-1){
		int esq = pos+pos+1, dir = pos+pos+2, mid = (i+j)>>1;
		apply(pos, i, j);
		if(j < l || i > r)	return;
		if(l <= i && r >= j){
			lazy[pos] += val;
			apply(pos, i, j);
			return;
		}
		upd(l, r, val, esq, i, mid); upd(l, r, val, dir, mid+1, j);
		seg[pos] = Node(seg[esq], seg[dir]);
	}

	Node qry(int l, int r, int pos = 0, int i = 0, int j = n-1){
		int esq = pos+pos+1, dir = pos+pos+2, mid = (i+j)>>1;
		apply(pos, i, j);
		if(j < l || i > r)	return Node();
		if(l <= i && r >= j)	return seg[pos];
		return Node(qry(l, r, esq, i, mid), qry(l, r, dir, mid+1, j));
	}
};
