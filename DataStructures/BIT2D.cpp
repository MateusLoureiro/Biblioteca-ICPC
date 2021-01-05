//Código não testado!!!!

template <class T> // One-indexed array
class BIT {
public:

	void init(int _r, int _c) {
		this->R = _r;
		this->C = _c;
		bit.assign(R+1, vector<T>(C+1, 0));
	}
	
	T qry(int x, int y) {
		x = std::min(x, R);
		y = std::min(y, C);
		T ans = 0;
		while(x > 0) {
			int yTemp = y;
		  while(y > 0) {
		    ans += bit[x][yTemp];
		    yTemp -= yTemp&-yTemp;   
		  }
		  x -= x&-x;
		}
		return ans;
	}
	
	T qry(int x1, int y1, int x2, int y2){
		return qry(x2, y2) - qry(x2, y1-1) - qry(x1-1, y2) + qry(x1-1, y1-1);
	}
	
	void upd(int x, int y, T v) {
		while(x <= R) {
		  int yTemp = y;
		  while(yTemp <= C) {
		    bit[x][yTemp] += v;
		    yTemp += yTemp&-yTemp;
		  }
		  x += x&-x;
		}
	}
	
private:
	int R, C;
	std::vector<vector<T>> bit;
};
