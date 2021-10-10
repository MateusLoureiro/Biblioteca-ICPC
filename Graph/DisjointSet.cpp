int ds[maxn], sz[maxn];

// LEMBRAR DE BUILDAR O DSU
void dsBuild(int n){
	for(int i = 0; i < n; i++){
		ds[i] = i;
		sz[i] = 1;
	}
}

int dsFind(int i){
	return (ds[i] == i ? i : ds[i] = dsFind(ds[i]));
}

void dsUnion(int a, int b){
	a = dsFind(a), b = dsFind(b);
	if(sz[a] < sz[b])
		swap(a, b);
	if(a != b)
		sz[a] += sz[b];
	ds[b] = a;
}
