// src: Arpa -https://codeforces.com/blog/entry/44351- with some modifications
int cnt[maxn], sz[maxn];
int in[maxn], out[maxn], nodeIn[maxn], z = 0; // if add/rmv based on the in/out time of nodes in dfs 

void getSz(int v, int p){
	sz[v] = 1;
	in[v] = z, nodeIn[z++] = v; // if add/rmv based on the in/out time of nodes in dfs
	for(auto u : adj[v]){
		if(u == p) continue;
		getSz(u, v);
		sz[v] += sz[u];
	}
	out[v] = z;
}

void dfs(int v, int p, bool keep){
  int big = -1;
  for(auto u : adj[v]){
		if(u == p)	continue;
		if(big == -1 || sz[u] > sz[big])
			big = u;
	}
			
  for(auto u : adj[v])
    if(u != p && u != big)
      dfs(u, v, 0);
  
  if(big != -1)
    dfs(big, v, 1);
    
  cnt[col[v]]++;	// TODO: add property of this nodeIn in data structure
    
  for(auto u : adj[v])
		if(u != p && u != big)	
    	for(int s = in[u]; s < out[u]; s++)
				cnt[col[nodeIn[s]]]++; // TODO: add property of small children of this nodeIn to data structure
	
	// TODO: answer queries in respect to subtree of v here
	
	if(keep == 0)	
	  for(int s = in[v]; s < out[v]; s++)
			cnt[col[nodeIn[s]]]--;	// TODO: remove property of small children of this nodeIn in the data structure
}
