//pref[i+1] = maior prefixo que também é sufixo da substring p[0..i]
string p, t; //p = pattern, t = text
int pref[maxn], n, m; //m = p.size(), n = t.size()
vector<int> occur;

void kmpPreprocess(){
	int i = 0, j = -1;
	pref[0] = -1;
	while(i < m){
		while(j >= 0 && p[i] != p[j])
			j = pref[j];
		pref[++i] = ++j;
	}
}

int kmpSearch(){
	int i = 0, j = 0;
	occur.clear();
	while(i < n){
		while(j >= 0 && t[i] != p[j])
			j = pref[j];
		i++, j++;
		if(j == m){
			occur.push_back(i-j);
			j = pref[j];
		}
	}
	return occur.size();
}
