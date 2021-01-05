// src: tfg50
template <class T> // One-indexed array
class BIT {
public:
	void init(int _n) {
		this->n = _n;
		bit.assign(n + 1, 0);
	}

	T qry(int x) {
		x = std::min(x, n);
		T ans = 0;
		for(; x > 0; x -= x & -x) {
			ans += bit[x];
		}
		return ans;
	}
	
	T qry(int l, int r){	// Impossible in min BIT;
		return qry(r) - qry(l-1);
	}

	void upd(int x, T v) {	// in min BIT, v has to be always <= bit[x];
		if(x <= 0) return;
		for(; x <= n; x += x & -x) {
			bit[x] += v;
		}
	}
	
private:
	int n;
	std::vector<T> bit;
};
