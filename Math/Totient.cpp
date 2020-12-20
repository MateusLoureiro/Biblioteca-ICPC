//phi[p] = quantidade de números menores que p que são primos com p
//pot[i] = menor potencia do primeiro cara
bool notPrime[maxn];
int primes[maxn], phi[maxn], pot[maxn], qnt;

void totient(int lim){
	phi[1] = 1;
	pot[1] = 1;
	qnt = 0;
	for(int i = 2; i < lim; i++){
		if(!notPrime[i]){ //Se for primo calcular phi(i)
			primes[qnt++] = i;
			phi[i] = i-1;
			pot[i] = i;
		}
		for(int j = 0; j < qnt && i*primes[j] < lim; j++){
			notPrime[i*primes[j]] = true;
			if(i % primes[j] != 0){ //Se o menor primo (primes[j]) for elevado a 1
				pot[i*primes[j]] = primes[j];
				phi[i*primes[j]] = phi[primes[j]] * phi[i];
			}
			else{ //Se o menor primo (primes[j]) for elevado a mais que 1
				pot[i*primes[j]] = pot[i] * primes[j];
				phi[i*primes[j]] = primes[j] * phi[pot[i]] * phi[i/pot[i]];
				break;
			}
		}
	}
}
