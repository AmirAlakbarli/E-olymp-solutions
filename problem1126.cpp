#include <iostream>
#include <cmath>
#include <vector>

#define ll long long

using namespace std;

vector<int> findPrimes(int n)
{
    vector<int> primes;
    bool *isPrime = new bool[n + 1];
    fill(isPrime, isPrime + n + 1, true);
    if (n >= 0)
        isPrime[0] = false;
    if (n >= 1)
        isPrime[1] = false;

    for (int i = 2; i * i <= n; i++)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j <= n; j += i)
                isPrime[j] = false;
        }
    }

    for (int i = 2; i <= n; i++)
        if (isPrime[i])
            primes.push_back(i);

    delete[] isPrime;
    return primes;
}

int segmentedSieve(ll l, ll r)
{

    if (l < 2)
        l = 2;

    int limit = (int)floor(sqrt(r)) + 1, cnt = 0;

    vector<int> primes = findPrimes(limit - 1);

    ll low = l;
    ll high = l + limit;
    r++;

    if (l > r)
        return 0;

    while (low < r)
    {
        if (high > r)
            high = r;

        bool *mark = new bool[high - low];
        fill(mark, mark + high - low, true);

        for (int &p : primes)
        {
            ll loLim = low / p * p;
            if (loLim < low)
                loLim += p;

            if (loLim == p)
                loLim *= p;

            for (ll i = loLim; i < high; i += p)
            {
                if (mark[i - low])
                {
                    mark[i - low] = false;
                    cnt++;
                }
            }
        }
        low += limit;
        high += limit;
        delete[] mark;
    }
    return r - l - cnt;
}

int main()
{
    ll l, r;
    cin >> l >> r;
    cout << segmentedSieve(l, r);
}