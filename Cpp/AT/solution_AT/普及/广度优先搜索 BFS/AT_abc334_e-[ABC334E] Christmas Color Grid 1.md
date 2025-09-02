# [ABC334E] Christmas Color Grid 1

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc334/tasks/abc334_e

**この問題は問題 G と似た設定です。問題文の相違点を赤字で示します。**

$ H $ 行 $ W $ 列のグリッドがあり、グリッドの各マスは赤色あるいは緑色に塗られています。

グリッドの上から $ i $ 行目、左から $ j $ 列目のマスをマス $ (i,j) $ と表記します。

マス $ (i,j) $ の色は文字 $ S_{i,j} $ で表され、$ S_{i,j}\ = $ `.` のときマス $ (i,j) $ は赤色、$ S_{i,j}\ = $ `#` のときマス $ (i,j) $ は緑色に塗られています。

グリッドにおいて、緑色に塗られたマスを頂点集合、隣り合った $ 2 $ つの緑色のマスを結ぶ辺全体を辺集合としたグラフにおける連結成分の個数を **緑の連結成分数** と呼びます。ただし、$ 2 $ つのマス $ (x,y) $ と $ (x',y') $ が隣り合っているとは、$ |x-x'|\ +\ |y-y'|\ =\ 1 $ であることを指します。

**赤色**に塗られたマスを一様ランダムに $ 1 $ つ選び、**緑色**に塗り替えたとき、塗り替え後のグリッドの緑の連結成分数の期待値を $ \text{mod\ }\ 998244353 $ で出力してください。

  「期待値を $ \text{mod\ }\ 998244353 $ で出力」とは 求める期待値は必ず有理数となることが証明できます。 またこの問題の制約下では、その値を互いに素な $ 2 $ つの整数 $ P $, $ Q $ を用いて $ \frac{P}{Q} $ と表したとき、 $ R\ \times\ Q\ \equiv\ P\pmod{998244353} $ かつ $ 0\ \leq\ R\ \lt\ 998244353 $ を満たす整数 $ R $ がただ $ 1 $ つ存在することが証明できます。この $ R $ を出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ H,W\ \leq\ 1000 $
- $ S_{i,j}\ = $ `.` または $ S_{i,j}\ = $ `#`
- $ S_{i,j}\ = $ `.` なる $ (i,j) $ が存在する。
 
### Sample Explanation 1

マス $ (1,3) $ を緑色に塗り替えたとき、緑の連結成分数は $ 1 $ となります。 マス $ (2,2) $ を緑色に塗り替えたとき、緑の連結成分数は $ 1 $ となります。 マス $ (3,2) $ を緑色に塗り替えたとき、緑の連結成分数は $ 2 $ となります。 マス $ (3,3) $ を緑色に塗り替えたとき、緑の連結成分数は $ 2 $ となります。 よって、赤色に塗られたマスを一様ランダムに $ 1 $ つ選び、緑色に塗り替えた後の緑の連結成分数の期待値は $ (1+1+2+2)/4\ =\ 3/2 $ となります。

## 样例 #1

### 输入

```
3 3
##.
#.#
#..```

### 输出

```
499122178```

## 样例 #2

### 输入

```
4 5
..#..
.###.
#####
..#..```

### 输出

```
598946613```

## 样例 #3

### 输入

```
3 4
#...
.#.#
..##```

### 输出

```
285212675```

# 题解

## 作者：yydfj (赞：4)

这是本蒟蒻第四十五次写的题解，如有错误点请好心指出！

## 问题简述

给你一个 $n \times m$ 的网格，记 ```#``` 为绿色格，```.``` 为红色格，问随机均匀地将一个红色格涂成绿色格之后，新的网格中绿色连通块个数的期望值是多少，并取模 $998244353$。

## 解法综述

考虑先用并查集求出原始网格中的绿色连通块个数 $tot$，再考虑将一个红色格涂成绿色格的情况。

- 如果要涂的格子的相邻格子中没有绿色格，则当前连通块个数为 $tot+1$；
- 如果要涂的格子与一个相同的连通块相邻，则当前连通块个数为 $tot$；
- 如果要涂的格子与两个互不相同的连通块相邻，则当前连通块个数为 $tot-1$；
- 如果要涂的格子与三个互不相同的连通块相邻，则当前连通块个数为 $tot-2$；
- 如果要涂的格子与四个互不相同的连通块相邻，则当前连通块个数为 $tot-3$。

根据上述情况，可以总结出若要涂的格子与 $ss$ 种连通块相邻，则当前连通块个数为 $tot-ss+1$。

记 $kk$ 为要涂的格子数，用 $ans$ 将每种情况的连通块个数求和，则答案为 $\dfrac{ans}{kk}$。

## 代码描述

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353,dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
ll n,m,f[1000005],a[1005][1005],cnt,tot,kk,ans;
unordered_map<ll,bool> mp;
bool bz[1000005];
string s[1005];
ll find(ll x){return f[x]==x?x:f[x]=find(f[x]);}
ll ksm(ll x,ll y)
{
	ll res=1;
	while(y)
	{
		if(y&1) res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
int main()
{
	cin>>n>>m;
	for(int i=0;i<n;i++) cin>>s[i];
	for(int i=0;i<n;i++)
	for(int j=0;j<m;j++)
	{
		a[i][j]=++cnt;
		f[cnt]=cnt;
	}
	for(int i=0;i<n;i++)
	for(int j=0;j<m;j++)
	if(s[i][j]=='#')
	for(int k=0;k<4;k++)
	{
		ll xx=i+dx[k],yy=j+dy[k];
		if(xx<0||yy<0||xx>=n||yy>=m||s[xx][yy]=='.') continue;
		ll fx=find(a[xx][yy]),fy=find(a[i][j]);
		if(fx!=fy) f[fx]=fy;
	}
	for(int i=0;i<n;i++)
	for(int j=0;j<m;j++)
	if(s[i][j]=='#'&&!bz[find(a[i][j])]) bz[find(a[i][j])]=1,tot++;//用并查集求出原始网格中的绿色连通块个数tot
	for(int i=0;i<n;i++)
	for(int j=0;j<m;j++)
	if(s[i][j]=='.')
	{
		kk=(kk+1)%mod;
		mp.clear();
		ll ss=0;
		for(int k=0;k<4;k++)
		{
			ll xx=i+dx[k],yy=j+dy[k];
			if(xx<0||yy<0||xx>=n||yy>=m||s[xx][yy]=='.') continue;
			if(!mp.count(find(a[xx][yy]))) ss++,mp[find(a[xx][yy])]=1;
		}
		ans=(ans+tot-ss+1)%mod;//若要涂的格子与ss种连通块相邻，则当前连通块个数为tot-ss+1
	}
	cout<<ans*ksm(kk,mod-2)%mod;
	return 0;
}
```

---

## 作者：rui_er (赞：3)

先求出初始时绿连通块数量。

枚举每个红色格子，将其染成绿色本应增加一个绿连通块，但是它每与一个绿连通块相邻，就又会减少一个绿连通块。根据上述规则可以求出每个红色格子染绿后的绿连通块数量，求平均值即可。

时间复杂度 $O(nm)$。

```cpp
// Problem: E - Christmas Color Grid 1
// Contest: AtCoder - UNIQUE VISION Programming Contest 2023 Christmas (AtCoder Beginner Contest 334)
// URL: https://atcoder.jp/contests/abc334/tasks/abc334_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x, y, z) for(int x = (y); x <= (z); ++x)
#define per(x, y, z) for(int x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

template<int mod>
inline unsigned int down(unsigned int x) {
	return x >= mod ? x - mod : x;
}

template<int mod>
struct Modint {
	unsigned int x;
	Modint() = default;
	Modint(unsigned int x) : x(x) {}
	friend istream& operator>>(istream& in, Modint& a) {return in >> a.x;}
	friend ostream& operator<<(ostream& out, Modint a) {return out << a.x;}
	friend Modint operator+(Modint a, Modint b) {return down<mod>(a.x + b.x);}
	friend Modint operator-(Modint a, Modint b) {return down<mod>(a.x - b.x + mod);}
	friend Modint operator*(Modint a, Modint b) {return 1ULL * a.x * b.x % mod;}
	friend Modint operator/(Modint a, Modint b) {return a * ~b;}
	friend Modint operator^(Modint a, int b) {Modint ans = 1; for(; b; b >>= 1, a *= a) if(b & 1) ans *= a; return ans;}
	friend Modint operator~(Modint a) {return a ^ (mod - 2);}
	friend Modint operator-(Modint a) {return down<mod>(mod - a.x);}
	friend Modint& operator+=(Modint& a, Modint b) {return a = a + b;}
	friend Modint& operator-=(Modint& a, Modint b) {return a = a - b;}
	friend Modint& operator*=(Modint& a, Modint b) {return a = a * b;}
	friend Modint& operator/=(Modint& a, Modint b) {return a = a / b;}
	friend Modint& operator^=(Modint& a, int b) {return a = a ^ b;}
	friend Modint& operator++(Modint& a) {return a += 1;}
	friend Modint operator++(Modint& a, int) {Modint x = a; a += 1; return x;}
	friend Modint& operator--(Modint& a) {return a -= 1;}
	friend Modint operator--(Modint& a, int) {Modint x = a; a -= 1; return x;}
	friend bool operator==(Modint a, Modint b) {return a.x == b.x;}
	friend bool operator!=(Modint a, Modint b) {return !(a == b);}
};

typedef Modint<998244353> mint;

const int N = 1e3 + 5;
const int nxt[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

int n, m, k, vis[N][N];
string s[N];
mint cnt, ans;

void dfs(int x, int y, int u) {
    vis[x][y] = u;
    rep(d, 0, 3) {
        int nx = x + nxt[d][0], ny = y + nxt[d][1];
        if(s[nx][ny] == '#' && !vis[nx][ny]) dfs(nx, ny, u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    s[0] = s[n + 1] = string(m + 2, ' ');
    rep(i, 1, n) {
        cin >> s[i];
        s[i] = ' ' + s[i] + ' ';
    }
    rep(i, 1, n) rep(j, 1, m) if(s[i][j] == '#' && !vis[i][j]) dfs(i, j, ++k);
    rep(i, 1, n) {
        rep(j, 1, m) {
            if(s[i][j] == '.') {
                ++cnt;
                set<int> st;
                rep(d, 0, 3) {
                    int nx = i + nxt[d][0], ny = j + nxt[d][1];
                    if(s[nx][ny] == '#') st.insert(vis[nx][ny]);
                }
                ans += k - (int)st.size() + 1;
            }
        }
    }
    cout << ans / cnt << endl;
    return 0;
}
```

---

## 作者：harmis_yz (赞：1)

## 分析

一眼题，为什么会有人觉得 T3 难，难的不是 T2 和 T6 嘛。

考虑并查集。对于一个连通块，看做一个并查集。如果将某个红点变成绿点，只需要考虑它四周的绿点所在并查集合成一个并查集之后连通块变化的数量即可。由于题目范围很小，判断某个并查集是否出现过可以开 map 乱搞。

求期望连通块个数就是 $\frac{P}{Q}$，$P$ 表示所有情况的连通块个数和，$Q$ 表示红点数量（情况数）。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define PII pair<int,int>
#define x first
#define y second

const int N=2005,p=998244353;
int n,m;
char ch[N][N];
int fa[N*N];
int dx[10]={0,0,1,-1},dy[10]={1,-1,0,0};
map<int,bool> vk;

il int get(int x,int y){
	return (x-1)*m+y;
}
il int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
il int qmi(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=ans*a%p;
		a=a*a%p;b>>=1;
	}
	return ans;
}

il void solve(){
	cin>>n>>m;int cnt=0,P=0,Q=0;
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=m;++j)
		cin>>ch[i][j];
	for(re int i=1;i<=n*m;++i) fa[i]=i;
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=m;++j)
		if(ch[i][j]=='#'){
			for(re int k=0;k<4;++k){
				int nowx=i+dx[k],nowy=j+dy[k];
				if(ch[nowx][nowy]=='#') fa[find(get(i,j))]=find(get(nowx,nowy));
			}
		}
		else ++Q;
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=m;++j)
		if(ch[i][j]=='#'&&find(get(i,j))==get(i,j)) ++cnt;
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=m;++j)
		if(ch[i][j]=='.'){
			vk.clear();int dt=0;
			for(re int k=0;k<4;++k){
				int nowx=i+dx[k],nowy=j+dy[k];
				if(ch[nowx][nowy]!='#') continue;
				int s=find(get(nowx,nowy));
				if(!vk[s]) vk[s]=1,++dt;
			}
			P=(P+cnt-dt+1)%p;
		}
	cout<<P*qmi(Q,p-2)%p;
	return ;
}

signed main(){
	solve();
	return 0;
}
```


---

## 作者：Milthm (赞：1)

~~这个 E 说难不算难，说简单也没那么简单，但是没有 C 难就对了。~~

你会发现这个期望根本没什么意义，你根本不需要推式子，你只要枚举每个红色的位置算出答案就可以了。

暴力是 $O(n^2m^2)$ 的，考虑优化。我们可以先算出连通块的个数 $cnt$，然后我们判断，你当前枚举的这个位置，它四周的所有绿色位置属于几个连通块。设这个值为 $k$，而我们刚才已经求出了块的数量 $cnt$。然后我们发现，你填上这里，会使这 $k$ 个连通块合并为一个，从而减少 $k-1$ 个，所以该次的答案为 $cnt-(k-1)=cnt-k+1$ 个。

然后你只需要把所有答案累加起来，乘上红色位置数量的逆元即可。

### AC code


```cpp
#include<bits/stdc++.h>
#define int long long
#define N 2005
const int mod=998244353;
using namespace std;
int n,m,f[N][N],cnt,w[4][2]={{0,1},{1,0},{-1,0},{0,-1}},qwq,p;
set<int>s;
char a[N][N];
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;y>>=1;
	}
	return ans;
}
void dfs(int x,int y,int k){
	f[x][y]=k;
	for(int i=0;i<4;++i){
		int px=x+w[i][0],py=y+w[i][1];
		if(px>=1&&px<=n&&py>=1&&py<=m&&a[px][py]=='#'&&f[px][py]==0){
			dfs(px,py,k);
		}
	}
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j)cin>>a[i][j];
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(!f[i][j]&&a[i][j]=='#'){
				dfs(i,j,i*10000+j);++cnt;
			}
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(a[i][j]=='#')continue;
			s.clear();++p;
			for(int k=0;k<4;++k){
				int x=i+w[k][0],y=j+w[k][1];
				if(x>=1&&x<=n&&y>=1&&y<=m&&f[x][y])s.insert(f[x][y]);
			}
			qwq+=cnt-s.size()+1;
		} 
	}
	cout<<qwq%mod*qpow(p,mod-2)%mod;
	return 0;
}

```


---

## 作者：incra (赞：1)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc334_e)
### 题解
水题。

考虑用并查集维护每一个绿色连通块，那么对于每一个红色节点，改成绿色节点后的答案 $=$ 不修改的答案就减去了周围不同绿色连通块的数目 $- 1$。

如果周围没有绿色连通块，那么相对于不修改的答案 $+1$。
### 代码
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <ctime>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#define x first
#define y second
#define pb push_back
#define desktop "C:\\Users\\incra\\Desktop\\"
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = cin.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = cin.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = cin.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
const int N = 1010,M = N * N,MOD = 998244353;
int n,m;
char s[N][N];
int p[M];
int get_pos (int x,int y) {
	return (x - 1) * m + y;
}
int find (int x) {
	if (p[x] != x) p[x] = find (p[x]);
	return p[x];
}
int main () {
	scanf ("%d%d",&n,&m);
	for (int i = 1;i <= n;i++) scanf ("%s",s[i] + 1);
	for (int i = 1;i <= n * m;i++) p[i] = i;
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= m;j++) {
			if (i + 1 <= n && s[i][j] == '#' && s[i + 1][j] == '#') p[find (get_pos (i,j))] = find (get_pos (i + 1,j));
			if (j + 1 <= m && s[i][j] == '#' && s[i][j + 1] == '#') p[find (get_pos (i,j))] = find (get_pos (i,j + 1));
		}
	}
	int ans = 0;
	for (int i = 1;i <= n * m;i++) ans += find (i) == i && s[(i - 1) / m + 1][(i - 1) % m + 1] == '#';
	LL a = 0,b = 0;
	set <int> vis;
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= m;j++) {
			if (s[i][j] == '#') continue;
			vis.clear ();
			for (int d = 0;d < 4;d++) {
				int ni = i + dx[d],nj = j + dy[d];
				if (ni < 1 || ni > n || nj < 1 || nj > m || s[ni][nj] == '.') continue;
				vis.insert (find (get_pos (ni,nj)));
			}
			a = (a + ans - (vis.size () - 1)) % MOD,b++;
		}
	}
	printf ("%lld\n",a * power (b,MOD - 2,MOD) % MOD);
	return 0;
}
```

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc334_e)

一道 dfs 题。

先统计出绿连通块数量，然后对于每个红色方块统计涂成绿色方块后会变成多少个连通块。正常涂成绿色后应该会增加一个大小为 $1$ 的绿连通块，但若是有不同的绿连通块与其相邻，答案又会减少 $1$。

### Code

```cpp
#include <bits/stdc++.h>

const long long IMX = 1ll << 30;
const long long LMX = 1ll << 60;
const long long MOD = 998244353;

using ll = long long;
using i128 = __int128;
using ld = long double;
using f128 = __float128;

namespace xvl_ { 
	#define SP(n, x) std :: setprecision(n) << std :: fixed << x
	#define REP(i, l, r) for (auto i = (l); i <= (r); i++)
	#define PER(i, r, l) for (auto i = (r); i >= (l); i--)
	#define DEBUG(x) std :: cerr << #x << " = " << x << '\n'
	#define SZ(x) (x.size())
	#define fst first
	#define snd second
	template <typename T> T Max(T a, T b) { return a > b ? a : b; } template <typename T, typename... Args> T Max(T a, Args... args) { return a > Max(args...) ? a : Max(args...); }
	template <typename T> T Min(T a, T b) { return a < b ? a : b; } template <typename T, typename... Args> T Min(T a, Args... args) { return a < Min(args...) ? a : Min(args...); }
}
using namespace std;
using namespace xvl_;
ll h, w, cnt, sum, ans;
ll dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}, id[1005][1005];
char c[1005][1005];
void dfs(int x, int y) {
    REP(i, 0, 3) {
        ll sx = dir[i][0] + x, sy = dir[i][1] + y;
        if (sx >= 1 and sy >= 1 and sx <= h and sy <= w and c[sx][sy] == '#' and !id[sx][sy]) {
			id[sx][sy] = cnt;
			dfs(sx, sy);
		}
    }
}
ll qpow(ll n, ll m, int p) { 
	ll res = 1;
	while (m) {
		if (m & 1) res = res % p * n % p;
		n = n % p * n % p;
		m >>= 1;
	}
	return res; 
}
int main() {
	// freopen("InName.in", "r", stdin);
	// freopen("OutName.out", "w", stdout);
	ios :: sync_with_stdio(0);
	cin.tie(nullptr);
	cin >> h >> w;
	REP(i, 1, h) { REP(j, 1, w) cin >> c[i][j]; }
	REP(i, 1, h) {
		REP(j, 1, w) {
			if (!id[i][j] and c[i][j] == '#') {
				cnt++;
				id[i][j] = cnt;
				dfs(i, j);
			}
		}
	}
	REP(i, 1, h) {
		REP(j, 1, w) {
			if (c[i][j] == '.') {
				sum++;
				set <int> S;
				REP(k, 0, 3) {
					ll sx = dir[k][0] + i, sy = dir[k][1] + j;
					if (sx >= 1 and sy >= 1 and sx <= h and sy <= w and c[sx][sy] == '#') S.insert(id[sx][sy]);
				}
				ans += cnt - S.size() + 1; // 原先的连通块数量 + 1 再减去相邻的不同的连通块
			}
		}
	}
	cout << ans % MOD * qpow(sum, MOD - 2, MOD) % MOD;
	return 0;
}
```

---

## 作者：FReQuenter (赞：0)

考虑直接硬推期望。只需要计算出对于每一个红点，填成绿色后会多出多少联通块。

那么先计算出原图中每个点所属的联通块。之后只要查询对于单个红点，有几个绿色联通块与它相邻即可。

给出一个并查集的实现。bfs，dfs 等均可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int h,w;
int get(int x,int y){
	return (x-1)*w+y;
}
int p[1000005];
int find(int x){
	if(x!=p[x]) p[x]=find(p[x]);
	return p[x];
}
char g[1005][1005];
int X[]={0,0,0,1,-1},Y[]={0,1,-1,0,0};
int qpow(int a,int n){
	int ans=1;
	while(n){
		if(n&1) ans*=a,ans%=mod;
		a*=a,a%=mod,n>>=1;
	}
	return ans;
}
signed main(){
	cin>>h>>w;
	for(int i=1;i<=h;i++) for(int j=1;j<=w;j++) cin>>g[i][j],p[get(i,j)]=get(i,j);
	int sum=0;
	for(int i=1;i<=h;i++) for(int j=1;j<=w;j++) for(int k=1;k<=4;k++){
		int nx=i+X[k],ny=j+Y[k];
		if(nx<1||ny<1||nx>h||ny>w) continue;
		if(g[nx][ny]=='#'&&g[i][j]=='#') if(find(get(i,j))!=find(get(nx,ny))) p[find(get(i,j))]=find(get(nx,ny));
	}
	for(int i=1;i<=h;i++) for(int j=1;j<=w;j++) if(find(get(i,j))==get(i,j)&&g[i][j]=='#') sum++;
//	cout<<sum<<endl;
	int ans=0,cnt=0;
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			if(g[i][j]=='#') continue;
			else{
				cnt++;
				map<int,int> mp;
				for(int k=1;k<=4;k++){
					int nx=i+X[k],ny=j+Y[k];
					if(nx<1||ny<1||nx>h||ny>w||g[nx][ny]!='#') continue;
					mp[find(get(nx,ny))]++;
				}
				ans+=sum-mp.size()+1;
			}
			ans%=mod;
		}
	}
//	cout<<ans<<' '<<cnt<<endl;
	cout<<ans*qpow(cnt,mod-2)%mod;
}
```

---

## 作者：WilliamFranklin (赞：0)

一道很水的 E。

### 主要思路

其实很简单，首先将每一个绿色连通块都标上序号，原图总连通块的数量为 $cnt$，然后考虑枚举每一个红点，分类讨论一下：如果这个红点四周都是红点，那么连通块数加 $1$；否则，我们用一个 `set` 来维护一下这个红点周围都有多少个不同的连通块，因为一旦这个红点变成了绿点，那么它周围的连通块就会变成一个。如果这个红点周围共 $x$ 个不同的连通块的话，将这个红点变成绿色后，此时的连通块总数量就应该是 $cnt - x + 1$ 个。然后我们按连通块数量来统计个数，直接求期望值即可。

注意：我们这里是可能达到 $cnt + 1$ 个连通块的！

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
const int N = 1005, mod = 998244353;
int a[N][N];
int b[N][N];
bool vis[N][N];
long long cnt1[N * N];
int sum;
int n, m;
int cnt = 0;
int d[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
bool init(int x, int y) {
	return (x > n || x < 0 || y > m || y < 0 || a[x][y] == 0 || vis[x][y]);
}
void dfs(int x, int y) {
	b[x][y] = cnt;
	vis[x][y] = 1;
	For(i, 0, 3) {
		int tx = x + d[i][0], ty = y + d[i][1];
		if (!init(tx, ty)) dfs(tx, ty);
	}
}
long long quickpow(long long a, long long b, long long mod) {
	long long res = 1;
	while (b) {
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> m;
	For(i, 1, n) {
		string s;
		cin >> s;
		For(j, 0, m -1) {
			if (s[j] == '.') a[i][j + 1] = 0, sum++;
			else a[i][j + 1] = 1;
		}
	}
	For(i, 1, n) {
		For(j, 1, m) {
			if (a[i][j] == 0 || vis[i][j]) continue;
			cnt++;
			dfs(i, j);
		}
	}
	For(i, 1, n) {
		For(j, 1, m) {
			if (a[i][j] == 0) {
				set<int> st;
				st.insert(0);
				st.insert(b[i - 1][j]);
				st.insert(b[i + 1][j]);
				st.insert(b[i][j - 1]);
				st.insert(b[i][j + 1]);
				int sz = st.size() - 1;
				sz--;
				if (sz == -1) {
					cnt1[cnt + 1]++;
					continue;
				}
				cnt1[cnt - sz]++;
				
			}
		}
	}
	long long ans = 0;
	For(i, 0, cnt + 1) {
		ans = (ans + i * cnt1[i] % mod * quickpow(sum, mod - 2, mod) % mod) % mod;
	}
	cout << ans;
	return 0;
}
```

### 谢谢观看

---

## 作者：xz001 (赞：0)

- 首先我们先预处理出每个联通块，并标记每个绿点为哪个连通块。
- 然后我们从枚举每一个红点，看看它四个方向上有多少个不同的连通块，很明显，若将它设为绿点，这些连通块都将变成一个连通块，会减少的连通块数量为其周围不同的连通块数量减一。
- 然后我们统计出每个红点设为绿点后的连通块数量之和后，将其除以总共的红点数量即为期望的绿色连通块数量。
- 代码如下：

```cpp
/*
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
*/
#include<bits/stdc++.h>

using namespace std;

#define re			register
#define int			long long
#define fi			first
#define se			second
#define swap(a, b) 	a ^= b, b ^= a, a ^= b
#define pb 			push_back
#define all(x)		x.begin(), x.end()
#define max(a, b)	(a > b ? a : b)
#define min(a, b)	(a < b ? a : b)
#define il			inline
#define abs(x)		((x ^ (x >> 63)) - (x >> 63))

typedef pair<int, int> PII;

const int N = 1e6 + 10;
const int M = 1e6 + 10;
const int INF = 1e18, mod = 998244353;
const double eps = 1e-6;

il int  read() { re int x = 0; re bool f = true; re char c = getchar(); while (c < 48 || c > 57) { if (c == '-') f = false; c = getchar(); } while (c >= 48 && c <= 57) x = (x << 3) + (x << 1) + c - 48, c = getchar(); return f ? x : -x; }
il void write(int x) { if (x < 0) putchar('-'), x = -x; if (x > 9) write(x / 10); putchar(x % 10 + 48); }
il void wel(int x) { write(x), putchar('\n'); }
il void wsp(int x) { write(x), putchar(' '); }

int ksm (int a, int n) {
	int ans = 1;
	while (n) {
		if (n & 1) ans = ans * a % mod;
		a = a * a % mod;
		n >>= 1;
	}
	return ans;
}

int h, w, t[1005][1005], cnt, b[1005][1005], sum;

char s[1005][1005];

void dfs (int i, int j, int d) {
	if (i < 1 || j < 1 || i > h || j > w || s[i][j] != '#' || t[i][j]) return;
	t[i][j] = d;
	dfs (i + 1, j, d);
	dfs (i, j + 1, d);
	dfs (i - 1, j, d);
	dfs (i, j - 1, d);
	return;
}

signed main() {
    scanf("%lld%lld", &h, &w);
    for (int i = 1; i <= h; ++ i) scanf("%s", s[i] + 1);
    for (int i = 1; i <= h; ++ i) 
    	for (int j = 1; j <= w; ++ j) 
    		if (s[i][j] == '#' && !t[i][j]) {
    			++ cnt;
    			dfs (i, j, cnt);
			}
	sum = cnt;
	cnt = 0;
	for (int i = 1; i <= h; ++ i) 
		for (int j = 1; j <= w; ++ j) 
			if (s[i][j] != '#') {
				++ cnt;
				set <int> e; 
				if (t[i - 1][j]) e.insert(t[i - 1][j]);
				if (t[i + 1][j]) e.insert(t[i + 1][j]);
				if (t[i][j - 1]) e.insert(t[i][j - 1]);
				if (t[i][j + 1]) e.insert(t[i][j + 1]);
				b[i][j] = (int)e.size() - 1;
			}
		
	int ans = 0;
	for (int i = 1; i <= h; ++ i)
	    for (int j = 1; j <= w; ++ j)
	        if (s[i][j] != '#') {
	            ans += sum - b[i][j];	
			}
			
	printf("%lld", ans % mod * ksm (cnt, mod - 2) % mod);
    return 0;
}


```

---

## 作者：无钩七不改名 (赞：0)

先用 DFS/BFS/DSU 预处理出连通块的个数 $cnt$。

设与红点 $(i,j)$ 相邻的有 $x$ 个不同的连通块，则将 $(i,j)$ 染绿后，这 $x$ 个连通块会变成 $1$ 个与 $(i,j)$ 相连的连通块。统计答案为 $cnt-x+1$。累加答案并计算期望值即可。

---

## 作者：ant2010 (赞：0)

考虑对于一个红点 $(i,j)$，如果要把这个点变为绿点，分为两种情况：

* 如果这个点周围的点都是红点，那么这个点将成为一个独立的四连通块。

* 否则，设它周围的 $4$ 个（如果在边缘就是 $3$ 个或是 $2$ 个）点属于不同的 $x$ 个四连通块，那么这 $x$ 个点双连通块将会变为 $1$ 个，减少了 $x-1$ 个。

而对于处理每一个四连通块，跑洪水填充算法即可。

那我们枚举所有的红点，然后考虑改变这个点颜色对全局的影响，时间复杂度 $O(n^2)$。

我写的代码里面把那两种情况合并了，因为如果周围都是红点的话，$x$ 就是 $0$，那么减少了 $0-1=-1$ 个就相当于是增加了 $1$ 个。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int const maxn=1e3+5,M=998244353;
char s[maxn][maxn];
int mp[maxn][maxn],tot,n,m;
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
int check(int x,int y){
    if(x==0||x>n||y==0||y>m)return 1;
    return 0;
}
void dfs(int x,int y){
    mp[x][y]=tot;
    for(int i=0;i<4;i++){
        int nx=x+dx[i],ny=y+dy[i];
        if(check(nx,ny)||s[nx][ny]=='.'||mp[nx][ny])continue;
        dfs(nx,ny);
    }
}
vector<int>v;
ll qpow(ll x,int y){
    ll res=1;
    while(y){
        if(y&1)res=res*x%M;
        x=x*x%M,y>>=1;
    }
    return res;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s[i][j]=='.'||mp[i][j])continue;
            tot++,dfs(i,j);
        }
    }
    int cnt=0,sum=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s[i][j]=='#')continue;
            cnt++;
            v.clear();
            for(int k=0;k<4;k++){
                int nx=i+dx[k],ny=j+dy[k];
                if(check(nx,ny)||s[nx][ny]=='.')continue;
                v.push_back(mp[nx][ny]);
            }
            sort(v.begin(),v.end());
            int k=unique(v.begin(),v.end())-v.begin()-1;
            sum+=k;
        }
    }
    printf("%d",(tot-sum*qpow(cnt,M-2)%M+M)%M);
}
```

---

## 作者：MMXIandCCXXII (赞：0)

## 题目大意
一个 $N \times M$ 的字符阵，`.` 表示红色，`#` 表示绿色，要求出随机将一个红色点染成绿色后绿色连通块的数量的期望值，对 $998244353$ 取模。
## 思路
这道题算是我见过最不需要思考的 E 了。首先要想到将一个红点染绿，只会对周围四个点中是绿色的点有影响，它会把周围的不同连通块合并为一个，但是还得注意，周围的点可能属于同一个连通块，用一个 `set` 去一下重，剩下的个数就是周围连通块的数量，算出连通块数量的变化，加上总连通块的数量（深搜或广搜 `Flood Fill`），乘上总红点数量的逆元（快速幂）即可。
## code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int mod = 998244353;

int n, m;
char c[1010][1010];
int cnt, id[1010][1010];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void dfs(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		int nx = dx[i] + x, ny = dy[i] + y;
		if (nx && ny && nx <= n && ny <= m && !id[nx][ny] && c[nx][ny] != '.')
		{
			id[nx][ny] = cnt;
			dfs (nx, ny);
		}
	}
}

int ksm(int a, int b, int p)
{
	int t = 1;
	while (b)
	{
		if (b & 1) t = t * a % p;
		a = a * a % p, b /= 2;
	}
	return t;
}

signed main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    	for (int j = 1; j <= m; j++)
    		cin >> c[i][j];
    		
    for (int i = 1; i <= n; i++)
    	for (int j = 1; j <= m; j++)
    	{
    		if (id[i][j] || c[i][j] == '.') continue;
    		id[i][j] = ++cnt;
			dfs (i, j);
		}
	
//	for (int i = 1; i <= n; i++)
//	{
//		for (int j = 1; j <= m; j++)
//			cout << id[i][j] << " ";
//		cout << endl;
//	}
	
	int cntred = 0, ans = 0;
	for (int x = 1; x <= n; x++)
		for (int y = 1; y <= m; y++)
			if (c[x][y] == '.')
			{
				cntred++;
				set <int> b;
				for (int i = 0; i < 4; i++)
				{
					int nx = dx[i] + x, ny = dy[i] + y;
					if (nx && ny && nx <= n && ny <= m && c[nx][ny] == '#') b.insert (id[nx][ny]);
				}
//				cout << b.size () << endl;
				ans += cnt - (b.size () - 1);
			}
//	cout << ans << " " << cntred << endl;
	int gcd = __gcd (ans, cntred);
	ans /= gcd, cntred /= gcd;
//	cout << ans << " " << cntred << endl;
	cout << ans % mod * ksm (cntred, mod - 2, mod) % mod << endl;
    return 0;
}

```

---

