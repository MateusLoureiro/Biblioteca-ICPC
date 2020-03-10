int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

bool check(int c, int r){
	if(c < 0 || c >= C || r < 0 || r >= R)
		return false;
	return true;
}

int dfs(int c, int r){
	if(!check(c, r))
		return 0;
	grid[r][c] = false; //Qualquer coisa que de falso no check
	int ans = 0;
	for(int i = 0; i < 4; i++)
		ans += dfs(c + dx[i], r + dy[i]);
	return ans;
}
