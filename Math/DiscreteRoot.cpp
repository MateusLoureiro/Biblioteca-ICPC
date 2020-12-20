//By: Amigos do Beto
//x^k = a % mod
//Acho que tem que conferir se realmente há resposta
ll discreteRoot(ll k, ll a, ll mod) {
  ll g = primitiveRoot(mod);
  ll y = discreteLog(fexp(g, k, mod), a, mod);
  if (y == -1) {
    return y;
  }
  return fexp(g, y, mod);
}
