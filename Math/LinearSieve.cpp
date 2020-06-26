bool notPrime[maxn];
int primes[maxn], qnt;

void linearSieve(int lim){
	qnt = 0;
	//primes[qnt++] = 1; //Depende se o 1 é válido ou não
	for(int i = 2; i < lim; i++){
		if(!notPrime[i])
			primes[qnt++] = i;
		for(int j = 0; j < qnt && i*primes[j] < lim; j++){ //int j = 1 se primes[0] = 11
			notPrime[i*prime[j]] = true;
			if(i % primes[j] == 0)
				break;
		}
	}
}
