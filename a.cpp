#include <bits/stdc++.h>
using namespace std;
 
typedef vector <long long> vi;
typedef pair <long long, long long> pii;
#define pb push_back
#define all(c) c.begin(), c.end()
#define For(i, a, b) for (long long i = a; i < b; ++i)
#define Forr(i, a, b) for (long long i = a; i > b; --i)
#define um unordered_map
#define F first
#define S second
#define int long long
#define inf LLONG_MAX
#define min(a,b) (a < b ? a : b)
#define max(a,b) (a > b ? a : b)
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define _CRT_SECURE_NO_WARNINGS
#define endl "\n"
 
template <class X>
void printarr(X arr[], int n) {
	for (int i = 0; i < n; ++i)
		cout << arr[i] << ' ';
	cout << endl;
}
 
int modulo = 1e9 + 7;
 
int fpow(int a, int n) {
	int ans = 1;
	while (n) {
		if (n&1) ans = (ans*a)%modulo;
		a = (a*a)%modulo; n = n >> 1;
	}
	return ans;
}
 
signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int t; cin >> t;
	for (int T = 0 ; T < t ; T++)
	{
		int m,k; cin >> m >> k;
		vector < pair < pii, int > > arr;
		int prefixCost[m+1]; prefixCost[0] = 0;
 
		For(i,0,m)
		{
			int l,r,c; cin >> l >> r >> c;
			arr.pb(make_pair(make_pair(l,r), c));
		}
 
		sort(all(arr));
		For(i,1,m+1) prefixCost[i] = prefixCost[i-1] + (arr[i-1].F.S-arr[i-1].F.F+1)*arr[i-1].S;
 
		int ans = 0;
		for (int i = 0; i < m; ++i)
		{
			int start = arr[i].F.F;
			int end = start + k - 1;
			pair <  pii, int > toFind = make_pair(make_pair(end,inf), inf);
			vector < pair <  pii, int > > :: iterator it = upper_bound(all(arr), toFind);
			if (it == arr.end())
			{
				if (arr[m-1].F.S <= end)
					ans = max(ans, prefixCost[m]-prefixCost[i]);
				else
					ans = max(ans, prefixCost[m-1]-prefixCost[i]+(end-arr[m-1].F.F+1)*arr[m-1].S);
			}
			else
			{
				--it;
				int index = it - arr.begin();
				int curr = prefixCost[index] - prefixCost[i];
				curr += (min(arr[index].F.S,end)-arr[index].F.F+1)*arr[index].S;
				ans = max(ans, curr);
			}
		}
 
		for (int i = 0; i < m; ++i)
		{
			int end = arr[i].F.S;
			int start = max(1ll, end - k + 1);
			pair < pii, int > toFind = (make_pair(make_pair(start,inf), inf));
			vector < pair < pii, int > > :: iterator it = upper_bound(all(arr), toFind);
			if (it == arr.begin())
				ans = max(ans, prefixCost[i+1]);
			else
			{
				--it;
				int index = it - arr.begin();
				int curr = prefixCost[i+1] - prefixCost[index+1];
				int common = max(arr[index].F.S-start+1, 0);
				curr += common*arr[index].S;
				ans = max(ans, curr);
			}
		}
 
		cout << ans << endl;
	}
    return 0;
}
