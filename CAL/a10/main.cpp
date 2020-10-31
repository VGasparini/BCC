#include <bits/stdc++.h>
#define MAX_N 1000000 // um milhão

using namespace std;

void sieve(bool (&prime)[MAX_N + 1])
{
  for (int i = 2; i <= (int)sqrt(MAX_N); i++)
    if (prime[i] == false)
      for (int j = i * i; j <= MAX_N; j += i)
        prime[j] = true;
}

int main()
{

  // GERANDO CRIVO
  bool prime[MAX_N + 1];
  vector<unsigned long long int> primes;

  prime[0] = true;
  prime[1] = true;

  sieve(prime);

  for (int i = 0; i <= MAX_N; i++)
  {
    if (!prime[i])
    {
      primes.push_back(i);
    }
  }

  // GERANDO N
  srand(time(NULL));

  unsigned long long int p = primes[rand() % primes.size()];
  unsigned long long int q;

  do
  {
    q = primes[rand() % primes.size()];
  } while (q == p);

  unsigned long long int n = p * q;

  printf("p e q gerados:\t\t%llu\t%llu\n", p, q);

  // DESCOBRINDO P E Q
  unsigned long long int max_try = n / 2;
  int i, j;
  bool achou;

  for (i = 0; primes[i] <= max_try && i < primes.size(); i++)
  {
    for (j = 0; primes[j] <= max_try && j < primes.size(); j++)
    {
      if ( n == primes[i] * primes[j] )
      {
        achou = true;
        break;
      }
    }
    if (achou)
      break;
  }

  if (achou)
  {
    printf("p e q encontrados:\t%llu\t%llu\n", primes[i], primes[j]);
  }
  else
  {
    printf("p e q não encontrados.\n");
  }
}