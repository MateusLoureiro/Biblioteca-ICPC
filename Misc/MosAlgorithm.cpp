// Quicker if q << n) 
ll hilbertOrder(int x, int y, int pow, int rotate) { 
	if (pow == 0)
		return 0;
		
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
	seg = (seg + rotate) & 3;
	
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	
	ll subSquareSize = ll(1) << (2*pow - 2);
	ll ans = seg * subSquareSize;
	ll add = hilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}

const int blockSize = (int)sqrt(n) + 1; // Customize based on problem

struct Query {
	int l, r, idx;
	bool operator < (Query o) const {
		if(l / blockSize != other.l / blockSize)
			return l < o.l;
		return (l / blockSize & 1) ? (r < o.r) : (r > o.r);
	}
	
	/*// If using hilbertOrder
	ll ord;
	void calcOrd(){
		ord = hilbertOrder(l, r, 20, 0); //(2 ^ pow) >= n;
	}
	bool operator < (Query o) const {
		return ord < o.ord;
	}
	*/
};

vector<int> mosAlgorithm(vector<Query> qrs){
	vector<int> ans(qrs.size());
	sort(qrs.begin(), qrs.end());
	
	// TODO: initialize data structure
	
	int cur_l = 0, cur_r = -1;
	for(Query q : qrs){ // Keep data structure range in [cur_l, cur_r]
		while(cur_l > q.l){
			cur_l--; 
			//TODO: add(cur_l)
		}
		while(cur_l < q.l){
			//TODO: remove(cur_l)
			cur_l++;
		}
		while(cur_r < q.r){
			cur_r++;
			//TODO: add(cur_r)
		}
		while(cur_r > q.r){
			//TODO: remove(cur_r)
			cur_r--;
		}
		ans[q.idx] = get_ans();
	}
	return ans;
}
