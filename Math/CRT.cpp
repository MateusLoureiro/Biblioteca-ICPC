//by tfg

ll modinverse(ll a, ll b, ll s0 = 1, ll s1 = 0){
	return b == 0 ? s0 : modinverse(b, a % b, s1, s0 - s1 * (a/b));
}

ll gcd(ll a, ll b) {
	return b == 0 ? a : gcd(b, a % b);
}

ll mul(ll a, ll b, ll m){
	ll q = (ld)a * (ld)b / (ld)m;
	ll r = a*b - q*m;
	return (r+m) % m;
}

struct Equation {
	
	Equation(ll a, ll m){
		mod = m, ans = a, valid = true;
	}
	
	Equation(){
		valid = false;
	}
	
	Equation(Equation a, Equation b){
		if(!a.valid || !b.valid){
			valid = false;
			return;
		}
		
		ll g = gcd(a.mod, b.mod);
		if((a.ans - b.ans) % g != 0){
			valid = false;
			return;
		}
		
		valid = true;
		mod = a.mod * (b.mod / g);
		ans = a.ans + mul( mul(a.mod, modinverse(a.mod, b.mod), mod), (b.ans - a.ans) / g, mod);
		ans = (ans % mod + mod) % mod;
	}
	
	ll mod, ans;
	bool valid;
};
