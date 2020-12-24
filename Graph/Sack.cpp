// src: Arpa -https://codeforces.com/blog/entry/44351- with some modifications
int cnt[maxn], sz[maxn];
int in[maxn], out[maxn], nodeIn[maxn], z = 0; // if add/rmv based on the in/out time of nodes in dfs 

void prepSack(int v, int p){
	sz[v] = 1;
	in[v] = z, nodeIn[z++] = v; // if add/rmv based on the in/out time of nodes in dfs
	for(auto u : adj[v]){
		if(u == p) continue;
		prepSack(u, v);
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
    
  cnt[col[v]]++;	// TODO: add this node in structure
    
  for(auto u : adj[v])
		if(u != p && u != big)	
    	for(int s = in[u]; s < out[u]; s++)
				cnt[col[nodeIn[s]]]++; // TODO: add small children to structure
	
	// TODO: answer queries of subtree of v here
	
	if(keep == 0)	
	  for(int s = in[v]; s < out[v]; s++)
			cnt[col[nodeIn[s]]]--;	// TODO: remove small children from structure
}
