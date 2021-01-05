int len[ms*2], link[ms*2], aut[ms*2][sigma];
int sz, last;

void buildAut(string &s) {
  
  len[0] = 0; link[0] = -1;
  sz = 1; last = 0;
  memset(aut[0], -1, sizeof aut[0]);
  
  for(char ch : s) {  
    int c = ch-'a', cur = sz++;	// TODO: take care if letters are uppercase
    len[cur] = len[last]+1;
    memset(aut[cur], -1, sizeof aut[cur]);
    int p = last;
    
    while(p != -1 && aut[p][c] == -1) {
      aut[p][c] = cur;
      p = link[p];
		}
    if(p == -1)
      link[cur] = 0;
   	else {
      int q = aut[p][c];
      if(len[p] + 1 == len[q])
        link[cur] = q;
     	else {
        len[sz] = len[p]+1;
        link[sz] = link[q];
        memcpy(aut[sz], aut[q], sizeof aut[q]);
        
        while (p != -1 && aut[p][c] == q){
          aut[p][c] = sz; 
          p = link[p];
        }
        link[q] = link[cur] = sz++;
      }
    }
    
    last = cur;
  }
}
