# GCD is Greater

## 题目描述

In the evenings during the hike, Kirill and Anton decided to take out an array of integers $ a $ of length $ n $ from their backpack and play a game with it. The rules are as follows:

1. Kirill chooses from $ 2 $ to $ (n-2) $ numbers and encircles them in red.
2. Anton encircles all the remaining numbers in blue.
3. Kirill calculates the greatest common divisor ([GCD](https://en.wikipedia.org/wiki/Greatest_common_divisor)) of all the red numbers.
4. Anton calculates the [bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND) of all the blue numbers and adds the number $ x $ to the result.
5. If the GCD of all the red numbers is strictly greater than the sum of the bitwise AND of all the blue numbers and the number $ x $ , then Kirill wins; otherwise, Anton wins.

Help Kirill to beat Anton or tell if it's impossible.

## 样例 #1

### 输入

```
8
4 1
4 3 1 8
4 1
4 5 8 4
5 0
1 1 1 1 1
5 2
31 63 127 63 31
4 1
1 3 3 3
8 3
4 3 4 1 2 2 5 3
4 2
1 4 3 6
8 48
31 61 37 15 53 26 61 12```

### 输出

```
YES
2 4 8
2 3 1 
YES
2 4 4
2 5 8 
NO
YES
2 63 63
3 31 127 31
YES
2 3 3
2 1 3
YES
2 4 4
6 3 1 2 2 5 3
YES
2 3 6
2 1 4 
YES
2 61 61
6 31 37 15 53 26 12```

# 题解

## 作者：EuphoricStar (赞：10)

感觉是这场唯一比较有趣的题？

首先明确一点：先手只会选 $2$ 个数，因为数多了 $\gcd$ 会变小，而且对方的 $\text{and}$ 会变大。

所以对于某一位，若 $0$ 的个数 $\ge 3$ 那么对方的按位与这一位一定是 $0$。

所以若 $0$ 的个数 $\le 2$，那么可能会选这一位是 $0$ 的，导致对方的按位与这一位是 $1$。把它们加入一个集合 $S$ 中。

对每一位做这一步后 $S$ 的大小为 $O(\log V)$。枚举 $S$ 中的每个元素，再 $O(n)$ 枚举另外一个选什么，$O(\log V)$ check 一下即可（$O(\log V)$ 是因为要算 $\gcd$。还要写一个 ST 表查询区间按位与）。

令 $T = \{1, 2, \ldots, n\} \setminus S$。此时还没有考虑选 $T$ 中的数。但是因为选 $T$ 中的任意两个数，剩下的数的按位与都等于原序列的按位与，所以我们只可能选 $T$ 中两两 $\gcd$ 最大的两个数，设它们为 $a_x, a_y$。特殊考虑一下它们即可。

总时间复杂度 $O(n (\log n + \log^2 V))$。

[code](https://codeforces.com/problemset/submission/1945/252289248)

---

## 作者：dxbt (赞：4)

### Sol
我们通过简单观察，可以得到这么一个性质：选两个数进行 $\gcd$ 是不劣的。原因显然：选得越多，$\gcd$ 越小，其余数的与和越大，差就越小，显然不优。

然后我们考虑遍历整个数组，设这个数之前的数的与和为 $s$：

1. $(s \operatorname{and} a_i) < s$ 那么我们钦定其中一个数是 $a_i$，跑一遍前缀后缀然后枚举另一个数，复杂度 $O(n \log V)$。这部分总共会跑 $O(\log V)$ 遍。

2. 遍历完之后，若还是没有合法方案，就说明选上面遍历的这些数是不可行的，这些数就会被染蓝，那么蓝色的与和也就确定了，因为不存在其他数使得与和比上面这些数小，所以把剩下的数装进桶里，枚举 $\gcd$ 值，判断是否合法即可，复杂度是调和级数，也就是 $O(n\log V)$。

总复杂度 $O(n\log^2 V)$ 常数很小。

### Code

``` cpp
#include<bits/stdc++.h>
#define F(i,l,r) for(int i=(l),i##end=(r);i<=i##end;++i)
#define G(i,l,r) for(int i=(l),i##end=(r);i>=i##end;--i)
#define x first
#define y second
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define ep emplace_back
using namespace std;
int n;int a[400009];bool vis[400009];
int ans[400009];
pii out;int K,MK;
void calc(int x)
{
  	int xx=(1ll<<31)-1;
	F(i,1,n)
	{
	  	ans[i]=xx;
		if(i!=x)xx&=a[i];
	}
	xx=(1ll<<31)-1;
	G(i,n,1)
	{
	  	ans[i]&=xx;
		if(i!=x)xx&=a[i];
	}
	F(i,1,n)
	{
	  	if(i==x) continue;
		if(__gcd(a[i],a[x])>ans[i]+K) out=mp(x,i); 
	}
}
int ton[500009];
void solve()
{
	cin>>n>>K;out=mp(0,0);
	int xx=(1ll<<31)-1;MK=0;
	F(i,1,n){cin>>a[i];MK=max(MK,a[i]);}
	sort(a+1,a+n+1);
	F(i,1,n)
	{
	  	if((xx&a[i])<xx)
		{
		  	calc(i);
			vis[i]=true;
		}
		xx&=a[i];
	}
	if(out!=mp(0,0))
	{
	  	cout<<"Yes\n";
		cout<<2<<' '<<a[out.x]<<" "<<a[out.y]<<'\n';
		cout<<n-2;
		F(i,1,n) if(i!=out.x && i!=out.y) cout<<" "<<a[i];
		cout<<'\n';
		return ;
	}
	else
	{
	  	xx+=K;
		F(i,1,n) if(!vis[i]) ton[a[i]]++;
		F(i,xx+1,MK)
		{
			int cnt=0;
		  	F(j,1,MK/i)
			{
			  	cnt+=ton[i*j];
			}
			if(cnt>=2) 
			{
				F(j,1,n) if(!vis[j] && a[j]%i==0)
				  	if(out.x) out.y=j;
					else out.x=j;
			  	break;
			}
		}
		if(out!=mp(0,0))
		{
			cout<<"Yes\n";
			cout<<2<<' '<<a[out.x]<<" "<<a[out.y]<<'\n';
			cout<<n-2;
			F(i,1,n) if(i!=out.x && i!=out.y) cout<<" "<<a[i];
			cout<<'\n';
			return ;
		}
	}
	cout<<"No"<<'\n';
}
void init()
{
  	F(i,1,n) vis[i]=0;
	F(i,1,MK) ton[i]=0;
}
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);
  	int t;
	cin>>t;
	while(t--)
	{
	  	solve();
		init();
	}
}
```

---

## 作者：MiniLong (赞：2)

注意到只会选 $2$ 个红的。

然后如果有一位有 $3$ 个以上的 $0$，那么咋选这一位都是 $0$。所以在 $0$ 个数小于等于 $2$ 的位置上，把所有这一位是 $0$ 的数拿出来，暴力和其他 $n - 1$ 个数配对判断。

如果都不合法，那么刚刚选出来这些数肯定是蓝色了。于是与和就是所有数与起来（因为没被选的那些位置都必定是 $0$ 了，而被选的那些数又必须是蓝色，所以这些位置也是 $0$，只有所有数都是 $1$ 的位置才有 $1$ 的贡献）。所以设与和为 $sum$，那么 $\gcd$ 要大于 $sum+x$。所以枚举 $\gcd = [sum+x+1,\max{V}]$，如果它的倍数没被一开始选出来的个数大于 $1$，就合法，随便找两个出来就好了。

复杂度 $\Theta(n \log^2 V)$。

---

## 作者：SFlyer (赞：1)

性质+模拟题。首先发现 $A$ 集合一定是有两个数，证明考虑 $\gcd$ 多一个数不会增大，$\And$ 少一个数不会变小。于是就有了一个 trivial 的 $\mathcal{O}(n^2)$ 算法。

考虑按位与的每一个二进制位。发现如果这一位是 $0$ 的个数 $\ge 3$，那么不管怎么选集合，按位与这一位一定是 $0$。否则个数 $\le 2$，设为集合 $S$。有两种情况：$0$ 或者 $1$。如果是 $0$，那么我们 $A$ 集合的两个数不能完全包含 $S$，如果是 $1$，就必须完全包含。发现按位与的结果只和 $S$ 中是不是在 $A$ 有关，因此对于所有 $S$ 中特殊的数，暴力枚举如果他在 $A$ 集合可不可以满足，这个复杂度是 $\mathcal{O}(n\log^2 V)$ 的。

否则所有特殊的数都不在 $A$ 集合中，这个时候按位与的结果就确定了，我们只要最大化 $\gcd$ 即可。这个调和级数枚举 $\gcd$ 判断就可以了。

总复杂度 $\mathcal{O}(n\log^2 V+n \ln V)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 4e5+5;

int n,x,a[N],sp[N][20],msk,sz[20],vis[N];
vector<int> has[N];

bool chk(int p,int d){
	for (int i=1; i<=n; i++){
		if (i!=p){
			int ms=msk;
			for (int j=0; j<19; j++){
				if (!(msk>>j&1)) continue;
				if (sp[i][j]+sp[p][j]!=sz[j]) ms^=1<<j;
			}
			if (__gcd(a[p],a[i])>ms+x){
				cout<<"YES\n";
				cout<<"2 "<<a[i]<<" "<<a[p]<<"\n"<<n-2<<" ";
				for (int j=1; j<=n; j++){
					if (j!=p && j!=i) cout<<a[j]<<" ";
				}
				cout<<"\n";
				return 1;
			}
		}
	}
	return 0;
}

void solve(){
	cin>>n>>x;
	int mx=0;
	for (int i=1; i<=n; i++){
		cin>>a[i];
		vis[i]=0,mx=max(mx,a[i]);
		for (int j=0; j<19; j++) sp[i][j]=0;
	}
	msk=(1<<19)-1;
	vector<pair<int,int> > s; 
	for (int i=0; i<19; i++){
		vector<int> v;
		for (int j=1; j<=n; j++){
			if (!(a[j]>>i&1)) v.push_back(j);
		}
		sz[i]=0;
		if (v.size()>2) msk^=1<<i;
		else{
			if (v.empty()) continue;
			sz[i]=v.size();
			s.push_back({v[0],i}),sp[v[0]][i]=1;
			if (v.size()==2) s.push_back({v[1],i}),sp[v[1]][i]=1;
		}
	}
	for (auto u : s){
		vis[u.first]=1;
		if (chk(u.first,u.second)) return;
	}
	for (int i=0; i<19; i++){
		if (sz[i]) msk^=1<<i;
	}
	int nd=msk+x;
	for (int i=1; i<=n; i++){
		if (!vis[i]) has[a[i]].push_back(i);
	}
	int f=0;
	for (int i=1; i<=mx; i++){
		int cnt=0;
		vector<int> v;
		for (int j=i; j<=mx; j+=i){
			if (has[j].size()){
				cnt+=has[j].size();
				for (auto u : has[j]) v.push_back(u);
			}
		}
		if (cnt>=2 && i>nd){
			f=1;
			cout<<"YES\n";
			cout<<"2 "<<a[v[0]]<<" "<<a[v[1]]<<"\n";
			cout<<n-2<<" ";
			for (int j=1; j<=n; j++){
				if (j!=v[0] && j!=v[1]) cout<<a[j]<<" ";
			}
			cout<<"\n";
			break;
		}
	}
	if (!f) cout<<"NO\n";
	for (int i=1; i<=n; i++){
		if (!vis[i]) has[a[i]].clear();
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t;
	cin>>t;
	while (t--){
		solve();
	}
	return 0;
}
```

---

## 作者：Alear (赞：0)

传送门：[洛谷](https://www.luogu.com.cn/problem/CF1945H)，[CF](https://codeforces.com/contest/1945/problem/H)。

大致浏览了一下题解区，这应该是最暴力做法？

以下假设 $n$ 和值域 $V$ 同阶。$A,B$ 分别表示红色和蓝色圈起来的数构成的集合，与洛谷题意翻译一致。

两个观察：

1. $|A| \leq 2$。否则把 $A$ 中的数移至 $B$ 中，答案显然不劣。
2. 会影响 $B$ 的与和的数只有 $O(\log V)$ 个。对于二进制中的某一位上，有三个数为 $0$ 时，该位始终为 $0$。

基于这两个观察，我们直接枚举大于 $k + x$ 的所有约数，暴力验证每一对倍数是否满足要求。其中 $k$ 为所有数的与和，更小的约数肯定不会成为答案。

当倍数的数量很大时，总能很快找到一对不会使 $B$ 中与和变大的倍数。如果找不到，说明倍数数量很少，也不会消耗多少时间。

复杂度不太会算，有一个很松的界是 $O(n \log^3 n)$，分别由枚举约数和平方枚举倍数对带来，但是明显跑不满，可以通过此题。

甚至完全不用枚举二进制位。

[code](https://codeforces.com/contest/1945/submission/286190066)

---

## 作者：Ghosty_Neutrino (赞：0)

## 分析
首先发现 $\gcd$ 肯定数字越多越小。然后与值数字越多越小。所以结论就是选择两个数字取 $\gcd$，剩下的数字分到另一个集合。那么问题就变成了找出一对数字，它们的 $\gcd$ 和剩下的数字的与做差值最大化。

如果某一位所有数字这一位都为 $1$，我们以下证明不考虑这些位，我们把这些位单独提出来。发现如果数字非常多，与值很有可能等于 $0$。于是我们在二进制位上面考虑问题。现在考虑让与值为 $0$。我们把某一位为 $0$ 的数字个数记下来。

那么如果只有一个这一位为 $0$ 的数字，那么这个数字肯定不能取。（取了那么另一个集合中所有数字这一位就是 $1$ 了）。

如果只有两个这一位为 $0$ 的数字。那么这两个数字不能同时取（同理）。

也就是说最多只会有 $19$ 条限制。那如果不同数字的个数超过了 $20$ 就一定可以使其与值为 $0$。

我们预处理 $al_i$ 表示所有数字中第 $i$ 位为 $0$ 的数字个数。

于是我们枚举最大公约数 $d$，考虑将它的倍数全部提出来，集合为 $bs$，以外的数字集合为 $out$。

我们处理 $in_i$ 表示集合 $bs$ 中第 $i$ 位为 $0$ 的数字个数。

我们通过每一位的 $al-in$ 可以快速求出集合 $out$ 的与值。

然后考虑集合 $in$ 中选择两个数字，分类讨论：

$|bs|$ 小于等于 $20$：

我们暴力枚举两个数字。然后用前缀后缀与快速求出其他数字的与值（记得和 $out$ 的与在做一遍与运算），然后判断是否有解。

$|bs|$ 大于 $20$：

那么与值一定为 $0$，还是一样暴力扫两个值，最劣情况就是都是一个数字的限制，然后我们最后枚举到。（因为限制只有 $20$ 个，所以复杂度是对的）。

## 易错点和细节
有一些位，所有数字这一位都是 $1$，那么将这些位加起来为 $s$，那么最大公约数就从 $s+x+1$ 开始枚举。

本题有重复数字。可以先特判一下选两个重复数字的情况。后面的枚举也要记得考虑这种情况。

对于某一位 $0$ 的个数有为 $1$ 或 $2$ 的限制，可以用变量 $one$ 和 $two$ 状压。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,l,r) for (int i = (l); i <= (r); i++)
#define per(i,r,l) for (int i = (r); i >= (l); i--)
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define maxn(a, b) a = max(a, b)
#define minn(a, b) a = min(a, b)
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
typedef double db;
const ll mod = 998244353;
mt19937 gen(114514);
ll rp(ll a,ll b) {ll res=1%mod;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
const int V = (1<<20)-1;
void solve() {
	int n, c, m = 0;
	scanf("%d%d", &n, &c);
	VI a(n);
	for(auto &x : a) {
		scanf("%d", &x);
		maxn(m, x);
	}
	VI cnt(m+1);
	for(auto x : a) cnt[x]++;
	VI suf(m + 2);
	suf[m+1] = V;
	rep(i,1,m) suf[i] = cnt[i] ? i : V;
	per(i,m,1) suf[i] &= suf[i + 1];
	auto print = [&](const int &x, const int &y) {
		puts("YES");
		printf("2 %d %d\n", x, y);
		cnt[x]--; cnt[y]--;
		printf("%d", n - 2);
		rep(i,1,m) while (cnt[i]--) printf(" %d", i);
		puts("");
	};
	int pre = V;
	rep(i,1,m) {
		if(cnt[i] > 2) pre &= i;
		if(cnt[i] >= 2 && i > (pre & suf[i + 1]) + c) {
			print(i, i);
			return ;
		}
		if(cnt[i]) pre &= i;
	}
	VI al(21);
	int one = 0, two = 0;
	rep(i,1,m) if(cnt[i]) {
		rep(j,0,20) if (~i>>j&1) al[j] += cnt[i];
	}
	int s = 0;
	rep(j,0,20) {
		if (!al[j]) s |= 1 << j;
		else if (al[j] == 1) {
			one |= 1<<j;
		} else if (al[j] == 2) {
			two |= 1<<j;
		}
	}

	rep(d,s + c + 1,m) {
		VI bs, in(21);
		for (int b = d; b <= m; b += d) {
			if (cnt[b]) {
				bs.pb(b);
				rep(i,0,20) if (~b>>i&1) {
					in[i] += cnt[b];
				} 
			}
		}
		int out = 0;
		rep(i,0,20) if (al[i] == in[i]) {
			out |= 1 << i;
		}
		if (SZ(bs) <= 20) {
			suf = bs; suf.pb(V);
			per(i,SZ(bs)-1,0) suf[i] &= suf[i + 1];
			int l = V;
			rep(i,0,SZ(bs)-1) {
				int mid = V;
				if (cnt[bs[i]] > 1) mid &= bs[i];
				rep(j,i+1,SZ(bs)-1) {
					if (cnt[bs[j]] > 1) mid &= bs[j];
					if ((l & mid & suf[j + 1] & out) + c < d) {
						print(bs[i], bs[j]);
						return ;
					}
					mid &= bs[j];
				}
				l &= bs[i];
			}
		} else {
			rep(i,0,SZ(bs)-1) {
				int vi = V^bs[i];
				if (one & vi) break;
				rep(j,i+1,SZ(bs)-1) {
					int vj = V^bs[j];
					if (one & vj) break;
					if (vi & vj & two) break;
					print(bs[i], bs[j]);
					return ;
				}
			}
		}
	}
	puts("NO");
}

int main() {
    //freopen();
    //freopen();
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}

```

---

## 作者：Petit_Souris (赞：0)

首先，$A$ 集合只会选两个数，原因显然。

考虑一个二进制位。如果这位有至少 $3$ 个 $0$，那么 $B$ 集合的 AND 这位一定是 $0$。否则，至少得选择这些 $0$ 中的一个才会导致这位是 $1$。我们称这样的数为关键数，容易发现关键数的个数是 $\mathcal O(\log V)$ 的，那么对于选了至少一个关键数的情况，我们可以 $\mathcal O(n\log V)$ 枚举所有情况并 $\mathcal O(\log V)$ 计算 gcd 和剩下的 AND。

对于没选关键数的情况，发现 AND 只会等于整个序列的 AND，因此要选 $\gcd$ 最大的 pair，可以调和级数求出。

时间复杂度 $\mathcal O(n\log^2V)$。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=1e6+9;
ll T,n,X,a[N],cnt[20],bin[N],tag[N];
ll chk(ll i,ll j){
    ll o=0;
    rep(k,0,18){
        ll rcnt=cnt[k]-((a[i]>>k)&1)-((a[j]>>k)&1);
        if(rcnt==n-2)o+=(1<<k);
    }
    if(__gcd(a[i],a[j])>o+X)return 1;
    return 0;
}
void output(ll i,ll j){
    puts("YES");
    write(2),putchar(' ');
    write(a[i]),putchar(' ');
    write(a[j]),putchar('\n');
    write(n-2),putchar(' ');
    rep(k,1,n){
        if(k!=i&&k!=j)write(a[k]),putchar(' ');
    }
    putchar('\n');
}
void solve(){
    n=read(),X=read();
    rep(i,1,n)a[i]=read(),tag[i]=0;
    memset(cnt,0,sizeof(cnt));
    rep(i,0,18){
        rep(j,1,n)cnt[i]+=((a[j]>>i)&1);
    }
    vector<ll>oo;
    rep(i,0,18){
        if(cnt[i]<n-2)continue;
        rep(j,1,n){
            if((a[j]>>i)&1)continue;
            oo.emplace_back(j);
            tag[j]=1;
        }
    }
    for(ll i:oo){
        rep(j,1,n){
            if(i==j)continue;
            if(chk(i,j)){
                output(i,j);
                return ;
            }
        }
    }
    ll mx=*max_element(a+1,a+n+1);
    rep(i,0,mx)bin[i]=0;
    rep(i,1,n)bin[a[i]]+=(!tag[i]);
    ll o=0;
    per(i,mx,1){
        ll c=0;
        for(ll j=i;j<=mx;j+=i)c+=bin[j];
        if(c>=2){
            o=i;
            break;
        }
    }
    if(o){
        ll p1=0,p2=0;
        rep(i,1,n){
            if(tag[i])continue;
            if(a[i]%o==0){
                if(!p1)p1=i;
                else p2=i;
            }
        }
        if(p1&&p2&&chk(p1,p2)){
            output(p1,p2);
            return ;
        }
    }
    puts("NO");
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    T=read();
    while(T--)solve();
    return 0;
}
```

---

## 作者：Reunite (赞：0)

有趣的题。

一个显然的观察是 $|A|=2$，因为随着 $|A|$ 变大 $\gcd$ 会单调不增，$B$ 中按位与单调不减，一定不优。所以 $A$ 中只考虑有两个数的情况。

因为是按位与，你发现如果二进制第 $d$ 位有 $>2$ 个数为 $0$，那按位与这一位一定为 $0$，因为最多只能选掉两个。剩下几种情况涉及到数的总数只有 $O(\log V)$ 个，我们依次钦定每个数一定被选，暴力找另一个与其匹配的数，总对数是 $n\log V$ 的，这部分用 ST 表预处理区间与可以做到 $n\log^2 V$，还有一个 $\log$ 是 $\gcd$，理论可以预处理然后 $O(1)$ 求，但是常数大不如不用。如果合法就输出。

经过上面的 check 如果还不合法，说明这些不选可能导致某一位为 $0$ 的我们一个都没选，也就是说只有二进制中在所有 $a_i$ 都出现过的位才会有，那么右边的值变成了一个定值，可以直接计算。

剩下就是，我们希望在剩下那去掉 $O(\log V)$ 个数中，选出 $\gcd$ 最大的两个，直接枚举 $\gcd$，然后调和级数判一下倍数的个数就行。

复杂度 $O(n\log n+ n\log^2 V)$。


---

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

int T,n,x;
int a[400005];
int b[400005];
int h[400005];
int lg[400005];
int f[20][400005];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

inline int ask(int l,int r){
	if(l>r) return (1<<30)-1;
	int len=lg[r-l+1];
	return f[len][l]&f[len][r-(1<<len)+1];
}

inline bool check(int p){
	for(int i=1;i<p;i++){
		int l=__gcd(a[p],a[i]);
		int r=x+(ask(1,i-1)&ask(i+1,p-1)&ask(p+1,n));
		if(l>r){
			puts("YES");
			printf("2 %d %d\n",a[i],a[p]);
			printf("%d ",n-2);
			for(int j=1;j<=n;j++)
				if(j!=i&&j!=p) printf("%d ",a[j]);
			puts("");
			return 1;
		}
	}
	for(int i=p+1;i<=n;i++){
		int l=__gcd(a[p],a[i]);
		int r=x+(ask(1,p-1)&ask(p+1,i-1)&ask(i+1,n));
		if(l>r){
			puts("YES");
			printf("2 %d %d\n",a[i],a[p]);
			printf("%d ",n-2);
			for(int j=1;j<=n;j++)
				if(j!=i&&j!=p) printf("%d ",a[j]);
			puts("");
			return 1;
		}
	}
	return 0;
}

int main(){
	in(T);
	while(T--){
		in(n),in(x);
		int mx=0,R=x;
		for(int i=1;i<=n;i++) in(a[i]),mx=max(mx,a[i]),f[0][i]=b[i]=a[i];
		for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1,h[i]=0;
		for(int j=1;j<=lg[n];j++)
			for(int i=1;i+(1<<j)-1<=n;i++)
				f[j][i]=f[j-1][i]&f[j-1][i+(1<<(j-1))];
		for(int i=1;i<=mx;i++) h[i]=0;
		bool ok=0;
		for(int d=0;(1<<d)<=mx;d++){
			int op=0,x=0,y=0;
			for(int i=1;i<=n;i++){
				if((a[i]>>d)&1) continue;
				op++;
				if(!x) x=i;
				else y=i;
			}
			if(op>2) continue;
			if(!op) R+=(1<<d);
			if(x&&check(x)){ok=1;break;}
			if(y&&check(y)){ok=1;break;}
			if(x) b[x]=0;
			if(y) b[y]=0;
		}
		if(ok) continue;
		for(int i=1;i<=n;i++)
			if(b[i]) h[b[i]]++;
		for(int i=R+1;i<=mx;i++){
			int s=0;
			for(int j=i;j<=mx;j+=i) s+=h[j];
			if(s>=2){
				puts("YES");
				int x=0,y=0;
				for(int j=1;j<=n;j++){
					if(b[j]&&b[j]%i==0){
						if(x) y=j;
						else x=j;
					}
				}
				printf("2 %d %d\n",a[x],a[y]);
				printf("%d ",n-2);
				for(int j=1;j<=n;j++)
					if(j!=x&&j!=y) printf("%d ",a[j]);
				puts("");
				ok=1;
				break;
			}
		}
		if(!ok){
			puts("NO");
			continue;
		}
	}

	return 0;
}

```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF1945H)

**题目大意**

> 给定 $a_1\sim a_n$，以及自然数 $x$，把 $a$ 分成两个集合 $A,B$（大小至少为 $2$），使得 $\gcd(A)>\mathrm{AND}(B)+x$。
>
> 数据范围：$n,a_i\le 4\times 10^5$。

**思路分析**

注意到 $|A|$ 越大，$\gcd(A)$ 越小，$\mathrm{AND}(B)$ 越大，因此 $|A|=2$，设 $A=\{a_i,a_j\}$。

考虑 $\mathrm{AND}(B)$ 和 $\mathrm{AND}(a_1\sim a_n)$ 的差 $x$。

如果 $x\ne 0$，那么说明有一些二进制位只在 $a_i,a_j$ 上为 $0$。

如果存在一个二进制位 $k$，使得 $k$ 只在 $a_i$ 上为 $0$，称 $a_i$ 为“不好的”。

如果存在二进制位 $k$ 使得 $k$ 恰在 $a_i,a_j$ 上同时为 $0$，称 $(a_i,a_j)$ 为“不好的”。

那么“不好的”数和数对总共 $\mathcal O(\log V)$ 个。

分类讨论：

- 如果 $x=0$：

  只要求最大的 $\gcd(A)$。

  对于每个 $x$，求出 $x$ 的倍数有多少个是“好的”，设为 $c$。

  再对于所有 $(a_i,a_j)$ 不好，且 $a_i,a_j$ 分别是“好的”，求分别有多少个这样数对使得 $x\mid \gcd(a_i,a_j)$ ，设为 $d$ 个。

  这两部分可以直接 $\mathcal O(V\ln V)$ 调和级数暴力算出。

  那么 $x$ 可以成为 $\gcd(A)$ 当且仅当 $d<\dfrac{c(c-1)}2$。

- 如果 $(a_i,a_j)$ 是“不好的”。

  这样的数对只有 $\mathcal O(\log V)$ 个，直接枚举。

- 如果 $a_i$ 是“不好的”，$(a_i,a_j)$ 是“好的”。

  这样的数对只有 $\mathcal O(n\log V)$ 个，直接枚举。

  时间复杂度 $\mathcal O(n\log^2 V)$

构造简单记录即可。

时间复杂度  $\mathcal O(n\log^2 V)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=4e5+5;
int n,f[MAXN],g[MAXN],a[MAXN],d[MAXN];
vector <int> dg[20],fac[MAXN];
void out(int x,int y) {
	printf("YES\n2 %d %d\n%d ",a[x],a[y],n-2);
	for(int i=1;i<=n;++i) if(i!=x&&i!=y) printf("%d ",a[i]); puts("");
}
void solve() {
	int lim=0,m=0;
	scanf("%d%d",&n,&lim);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),m=max(m,a[i]),d[i]=0;
	for(int i=1;i<=m;++i) f[i]=g[i]=0;
	for(int k=0;k<20;++k) dg[k].clear();
	int A=a[1];
	for(int i=1;i<=n;++i) {
		++f[a[i]],A&=a[i];
		for(int k=0;k<20;++k) if(!(a[i]>>k&1)) dg[k].push_back(i);
	}
	for(int k=0;k<20;++k) if(dg[k].size()==1) d[dg[k][0]]|=1<<k;
	for(int i=1;i<=n;++i) if(d[i]) --f[a[i]];
	map <array<int,2>,int> e;
	for(int k=0;k<20;++k) if(dg[k].size()==2) {
		e[{dg[k][0],dg[k][1]}]|=1<<k;
	}
	for(auto z:e) {
		int x=z.first[0],y=z.first[1];
		if(!d[x]&&!d[y]) ++g[__gcd(a[x],a[y])];
	}
	for(int i=1;i<=m;++i) {
		for(int j=2*i;j<=m;j+=i) f[i]+=f[j],g[i]+=g[j];
	}
	for(int i=m;i>=1;--i) {
		if(g[i]<1ll*f[i]*(f[i]-1)/2&&i>lim+A) {
			vector <int> tmp;
			for(int t=1;t<=n;++t) if(a[t]%i==0&&!d[t]) tmp.push_back(t);
			for(int x=0;x<(int)tmp.size();++x) for(int y=x+1;y<(int)tmp.size();++y) {
				if(!e.count({tmp[x],tmp[y]})) return out(tmp[x],tmp[y]);
			}
		}
	}
	for(auto z:e) {
		int x=z.first[0],y=z.first[1];
		if(__gcd(a[x],a[y])>lim+A+d[x]+d[y]+z.second) {
			return out(x,y);
		}
	}
	for(int i=1;i<=n;++i) if(d[i]) {
		for(int j=1;j<=n;++j) if(i!=j&&!e.count({i,j})) {
			if(__gcd(a[i],a[j])>lim+A+d[i]+d[j]) return out(i,j);
		}
	}
	puts("NO");
}
signed main() {
	for(int i=1;i<MAXN;++i) for(int j=i;j<MAXN;j+=i) fac[j].push_back(i);
	int T; scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：I_am_Accepted (赞：0)

以下认为值域和 $n$ 同阶。

最优策略 $\gcd$ 一定只选两个数。

枚举每个二进制位：

* 如果全是 $1$，那 bitwise and 确定是 $1$。
* 如果只有一个 $0$，如果 $\gcd$ 取到了这个 $0$（$n-1$ 种选法）bitwise and 为 $1$，否则确定是 $0$。
* 如果只有两个 $0$，如果 $\gcd$ 取到了这两个 $0$ 则 bitwise and 为 $1$，否则确定是 $0$。

上述需要特判的位置对至多只有 $O(n\log)$ 对，直接判即可。

剩下的情况 bitwise and 确定。我们需要在被 ban 掉的位置对之外找到 $\gcd$ 最大的一对。

枚举 $\gcd=d$，用调和的复杂度求出元素为 $d$ 的倍数的个数 $x$ 以及被 ban 掉的个数 $y$。如果 $y<\binom{x}{2}$，那我们能做到 $\gcd=d$。

然后暴力找即可（找到及时停止），复杂度 $O(n\log^2)$（如果 $O(1)\, \gcd$ 则复杂度 $O(n\log )$）。

---

