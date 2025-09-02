# Lucky Permutation

## 题目描述

Petya loves lucky numbers. Everybody knows that lucky numbers are positive integers whose decimal representation contains only the lucky digits 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

One day Petya dreamt of a lexicographically $ k $ -th permutation of integers from $ 1 $ to $ n $ . Determine how many lucky numbers in the permutation are located on the positions whose indexes are also lucky numbers.

## 说明/提示

A permutation is an ordered set of $ n $ elements, where each integer from $ 1 $ to $ n $ occurs exactly once. The element of permutation in position with index $ i $ is denoted as $ a_{i} $ ( $ 1<=i<=n $ ). Permutation $ a $ is lexicographically smaller that permutation $ b $ if there is such a $ i $ ( $ 1<=i<=n $ ), that $ a_{i}&lt;b_{i} $ , and for any $ j $ ( $ 1<=j&lt;i $ ) $ a_{j}=b_{j} $ . Let's make a list of all possible permutations of $ n $ elements and sort it in the order of lexicographical increasing. Then the lexicographically $ k $ -th permutation is the $ k $ -th element of this list of permutations.

In the first sample the permutation looks like that:

1 2 3 4 6 7 5

The only suitable position is 4.

In the second sample the permutation looks like that:

2 1 3 4

The only suitable position is 4.

## 样例 #1

### 输入

```
7 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 7
```

### 输出

```
1
```

# 题解

## 作者：wxzzzz (赞：3)

### 思路

前置：[数位DP](https://www.cnblogs.com/wangxuzhou-blog/p/advanced-dynamic-programming.html#%E6%95%B0%E4%BD%8DDP)、[逆康托展开](https://www.cnblogs.com/wangxuzhou-blog/p/preliminary-number-theory.html#%E9%80%86%E5%BA%B7%E6%89%98%E5%B1%95%E5%BC%80)

发现 $n$ 很大，有 $10^9$，但 $k$ 的规模也只有 $10^9$，远远小于 $n$ 的全排列数。

因此，在 $n$ 很大时，$a_1\sim a_{pos}$ 的值都和位置相同。经计算，在 $n\le10^9$ 时，$n-pos\le 12$。

考虑对 $a_{pos+1}\sim a_n$ 暴力逆康托展开求幸运数的个数，对 $a_1\sim a_{pos}$ 数位 DP 求 $1\sim pos$ 中的幸运数个数。

设 $f_{i,j}$ 表示所有位数为 $i$，最高位为 $j$ 的幸运数个数，有：

$$f_{i,j}=\begin{cases}
1\ (i=1,j=4,7)\\
f_{i-1,4}+f_{i-1,7}\ (i>1,j=4,7)
\end{cases}$$

分位讨论答案即可，数位 DP 板子。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, t, ans, pos, c[15], p[15], f[15][15];
vector<int> s, v;
inline bool limit() {
    for (int i = 1; i <= n; i++)
        if (p[i] >= m)
            return 1;

    return 0;
}
inline bool check(int x) {
    while (x) {
        if (x % 10 != 4 && x % 10 != 7)
            return 0;

        x /= 10;
    }

    return 1;
}
int main() {
    p[0] = 1;

    for (int i = 1; i <= 13; i++)
        p[i] = p[i - 1] * i;

    cin >> n >> m;

    if (!limit()) {
        cout << "-1";
        return 0;
    }

    m--;

    for (int i = 1; i <= 13; i++) {
        pos = n - i;

        if (p[i] > m)
            break;
    }

    for (int i = pos + 1; i <= n; i++) {
        v.push_back(i);
        s.push_back(m / p[n - i]), m %= p[n - i];
    }

    int now = pos;

    for (auto i : s) {
        int val = v[i];
        v.erase(lower_bound(v.begin(), v.end(), val));

        if (check(++now) && check(val))
            ans++;
    }

    int dig = 0, sum = 0, d[15];
    f[1][4] = f[1][7] = 1;

    for (int i = 2; i <= 10; i++) {
        f[i][4] = f[i - 1][4] + f[i - 1][7];
        f[i][7] = f[i - 1][4] + f[i - 1][7];
    }

    pos++;

    while (pos) {
        d[++dig] = pos % 10;
        pos /= 10;
    }

    for (int i = 1; i < dig; i++)
        for (int j = 0; j <= 9; j++)
            sum += f[i][j];

    for (int i = dig; i >= 1; i--) {
        for (int j = 0; j < d[i]; j++)
            sum += f[i][j];

        if (d[i] != 4 && d[i] != 7)
            break;
    }

    ans += sum;
    cout << ans;
    return 0;
}
```

---

## 作者：Yuby (赞：2)

#### 题意：

定义：幸运数字是指只含 4 和 7 的数字。

求在 1 到 $n$ 的第 $k$ 个全排列中有多少元素的下标和值都是幸运数。

$1 \leq n,k\leq 10^9$

#### 分析：

注意到 $n$ 和 $k$ 的范围很大，肯定是没办法强算的。

这个时候我们要返回全排列的定义和性质。一个长度为 $n$ 的序列有 $n!$ 种排列。以下分析都是按照一个长度为 $n$ 的序列。

这个 $n!$ 是由 $n*(n-1)!$ 得到的，也就是说对于每一个第一位都有 $(n-1)!$ 种方案。第一位每增加 1 相当于排列方案增加 $(n-1)!$ 换句话说就是如果当前是第 $x$ 种方案那么当首位增加 1 时变成了第 $x+(n-1)!$ 种方案。

运用这个性质发现会变的只有序列的最后十几个数。因为十几的阶乘就已经超过了 $10^9$。不妨把他们单独处理。运用上面的结论即可 $O(m^2 \log m)$ 计算第 $k$ 小的字典序。$m$ 为会改变的数列部分的总长度，最多十几个。

#### 代码：

```cpp
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a));
#define pc putchar
#define fast_iostream ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef double db;
const ld EPS=1e-8;
const ll INF=ll(1e9+7);
const ll LLINF=ll(1e18+7);
const ld LDEPS=1e-18;
inline ll max(ll x,ll y){return x>y?x:y;}
inline ll min(ll x,ll y){return x<y?x:y;}
inline ld dmax(ld x,ld y){return x>y?x:y;}
inline ld dmin(ld x,ld y){return x<y?x:y;}
inline ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
inline ll lcm(ll a,ll b){return a*b/gcd(a,b);}
inline ll lowbit(ll x){return x&(-x);}
inline ll read(){ll read_result=0,is_below_0=0;char now_ch=0;while(!isdigit(now_ch)){is_below_0|=now_ch=='-';now_ch=getchar();}while(isdigit(now_ch)){read_result=(read_result<<3)+(read_result<<1)+(now_ch^48);now_ch=getchar();}return is_below_0?-read_result:read_result;}
inline ld dread(){ld x=0,d=0.1;char f=0,ch=getchar();while(!isdigit(ch))f|=(ch=='-'),ch=getchar();while(isdigit(ch)) x=x*10+ch-48,ch=getchar();if(ch=='.'){ch=getchar();while(isdigit(ch))x+=d*(ch^48),d*=0.1,ch=getchar();}return f?-x:x;}
inline void write(ll x){if(x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x%10+'0');}
const ll MAXN=1e9+7;
ll n,k,bas[1200],a[100007],b[100007];
vector<ll>luck;
void dfs(ll x)
{
	if(x>MAXN)return ;
	if(x)luck.push_back(x);
	dfs(x*10+4),dfs(x*10+7);
}
bool check(ll x)
{
	while(x>0)
	{
		if(x%10!=4&&x%10!=7)return 0;
		x/=10;
	}
	return 1;
}
int main()
{
	dfs(0);
	bas[0]=1;
	for(ll i=1;i<=15;i++)bas[i]=bas[i-1]*i;
	n=read(),k=read();
	ll pos=0;
	for(ll i=1;i<=min(15,n);i++)
		if(bas[i]>=k)
		{
			pos=i;
			break;
		}
	if(bas[pos]<k)
	{
		puts("-1");
		return 0;
	}
	ll ans=0;
	for(ll i=0;i<luck.size();i++)if(luck[i]<n-pos+1)ans++;//处理不会变的数的贡献
	for(ll i=1;i<=pos;i++)a[i]=n-i+1;//h
	sort(a+1,a+pos+1);k--;
	for(ll i=1;i<=pos;i++)
	{
		if(k<=0)break;
		if(k<bas[pos-i])continue;
		ll p=k/bas[pos-i];
		swap(a[i],a[i+p]);
		k%=bas[pos-i];
		sort(a+i+1,a+pos+1);
	}
	for(ll i=1;i<=pos;i++)
		if(check(i+n-pos)&&check(a[i]))ans++;
	write(ans);
	return 0;
}
```

---

## 作者：lfxxx (赞：1)

不难发现由于 $k$ 相对阶乘而言很小，所以这个排列一定是前面一段 $p_i = i$ 的部分后面一个不大于 $13$ 的段可以用预处理阶乘加上逆康托展开暴力处理，前面的部分下标等于数，直接数位 dp 即可。细节看代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k;
int fac[14];
int pre;//[1,pre] 表示 [1,pre] 中 a[i] = i
bool check(int x){
	while(x>0){
		if(x%10!=4&&x%10!=7) return false;
		x/=10;
	}
	return true;
} 
int dp[30][2][2];//考虑到第 i 位 是否有前导 0 是否到上界
vector<int> dight;
int dfs(int pos,bool flag,bool f){
	if(pos==-1){
		return 1;
	}	
	if(dp[pos][flag][f]!=-1) return dp[pos][flag][f];
	int res=0;
	for(int i=0;i<10;i++){
		if(i!=4&&i!=7&&i!=0) continue;
		if(f==false&&i==0) continue;//可以有前导 0 中间没有  
		if(flag==true&&i>dight[pos]) continue;
		res+=dfs(pos-1,flag&(i==dight[pos]),(i==0)&f);
	}
	return dp[pos][flag][f]=res;
}
vector<int> D,f,a;
signed main(){
	cin>>n>>k;
	k--;
	fac[0]=1;
	for(int i=1;i<=13;i++) fac[i]=fac[i-1]*i;
	for(int i=1;i<=13;i++){
		pre=n-i;
		if(fac[i]>k) break;
	}
	if(n<=13&&k>=fac[n]){
		cout<<"-1\n";
		return 0;
	}
	for(int i=pre+1;i<=n;i++) D.push_back(i),f.push_back(k/fac[n-i]),k%=fac[n-i];
	for(int x:f){
		a.push_back(D[x]);
		D.erase(find(D.begin(),D.end(),a.back()));
	}
	int tot=pre;
	while(pre>0) dight.push_back(pre%10),pre/=10;
	memset(dp,-1,sizeof(dp));
	int ans=(tot!=0?dfs(dight.size()-1,true,true)-1:0);
	for(int x:a) tot++,ans+=(check(tot)&check(x));
	cout<<ans<<'\n';
	return 0;
}
```


---

## 作者：attack (赞：1)

由于阶乘的数量增长非常迅速，而$k$又非常小，那么显然最后的序列只有最后几位会发生改变，前面的位置都是$i = a[i]$。那么前面的可以直接数位dp/爆搜，后面的部分是经典问题，可以用逆康托展开计算。
```cpp
/*
*/
#include<bits/stdc++.h> 
#define Pair pair<int, int>
#define MP(x, y) make_pair(x, y)
#define fi first
#define se second
#define int long long 
#define LL long long 
#define Fin(x) {freopen(#x".in","r",stdin);}
#define Fout(x) {freopen(#x".out","w",stdout);}
using namespace std;
const int MAXN = 1e6 + 1, mod = 1e9 + 7, INF = 1e9 + 10;
const double eps = 1e-9;
template <typename A, typename B> inline bool chmin(A &a, B b){if(a > b) {a = b; return 1;} return 0;}
template <typename A, typename B> inline bool chmax(A &a, B b){if(a < b) {a = b; return 1;} return 0;}
template <typename A, typename B> inline LL add(A x, B y) {if(x + y < 0) return x + y + mod; return x + y >= mod ? x + y - mod : x + y;}
template <typename A, typename B> inline void add2(A &x, B y) {if(x + y < 0) x = x + y + mod; else x = (x + y >= mod ? x + y - mod : x + y);}
template <typename A, typename B> inline LL mul(A x, B y) {return 1ll * x * y % mod;}
template <typename A, typename B> inline void mul2(A &x, B y) {x = (1ll * x * y % mod + mod) % mod;}
template <typename A> inline void debug(A a){cout << a << '\n';}
template <typename A> inline LL sqr(A x){return 1ll * x * x;}
inline int read() {
    char c = getchar(); int x = 0, f = 1;
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
int N, K, fac[MAXN];
vector<int> res;
int find(int x) {
	sort(res.begin(), res.end());
	int t = res[x];
	res.erase(res.begin() + x);
	return t;
}
bool check(int x) {
	while(x) {
		if((x % 10) != 4 && (x % 10) != 7) return 0;
		x /= 10;
	}
	return 1;
}
int ans;
void dfs(int x, int Lim) {//计算1 - lim中只包含4 7的数量 
	if(x > Lim) return ;
	if(x != 0) ans++;
	dfs(x * 10 + 4, Lim);
	dfs(x * 10 + 7, Lim);
}
signed main() {
	N = read(); K = read() - 1;
	int T = -1; fac[0] = 1;
	for(int i = 1; i <= N;i++) {
		fac[i] = i * fac[i - 1];
		res.push_back(N - i + 1);
		if(fac[i] > K) {T = i; break;}
	}
	if(T == -1) {puts("-1"); return 0;}
    dfs(0, N - T);
    for(int i = T; i >= 1; i--) {
 	   	int t = find(K / fac[i - 1]), pos = N - i + 1;
    	if(check(pos) && check(t)) ans++;
    	K = K % fac[i - 1];
	}
	cout << ans;
	return 0;
}
/*

*/
```

---

