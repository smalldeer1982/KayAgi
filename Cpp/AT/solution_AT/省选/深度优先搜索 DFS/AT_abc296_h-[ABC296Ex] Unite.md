# [ABC296Ex] Unite

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc296/tasks/abc296_h

$ N $ 行 $ M $ 列のマス目があり、各マスは黒または白で塗られています。 ここで、少なくとも $ 1 $ つのマスが黒く塗られています。  
 最初のマス目の状態は $ N $ 個の長さ $ M $ の文字列 $ S_1,S_2,\ldots,S_N $ で与えられます。  
 マス目の上から $ i $ 行目 $ (1\leq\ i\leq\ N) $ かつ左から $ j $ 列目 $ (1\leq\ j\leq\ M) $ のマスは、 $ S_i $ の $ j $ 文字目が `#` であるとき黒く、`.` であるとき白く塗られています。

高橋君の目標は白く塗られたいくつかのマス ($ 0 $ 個でもよい ) を新しく黒く塗ることによって、黒く塗られたマス全体が **連結** になるようにすることです。 高橋君が目標を達成するために**新しく塗る必要のある**マスの個数としてあり得る最小値を求めてください。

ただし、黒く塗られたマス全体が **連結** であるとは、黒く塗られたどの $ 2 $ つのマスの組 $ (S,T) $ についても、 正整数 $ K $ と長さ $ K $ の黒く塗られたマスの列 $ X=(x_1,x_2,\ldots,x_K) $ であって、$ x_1=S $, $ x_K=T $ かつ任意の $ 1\leq\ i\leq\ K-1 $ について $ x_i $ と $ x_{i+1} $ が辺を共有しているようなものが存在することをいいます。  
 なお、問題の制約下でつねに、高橋君が目標を達成するような塗り方が存在することが証明できます。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ 1\leq\ M\ \leq\ 7 $
- $ N,M $ は整数
- $ S_i $ は `#` と `.` のみからなる長さ $ M $ の文字列
- 与えられるマス目において、黒く塗られたマスが $ 1 $ つ以上存在する。
 
### Sample Explanation 1

最初、マス目の状態は次のようになっています。ここで、上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,j) $ で表しています。 !\[\](https://img.atcoder.jp/abc296/d5b5d945798a02840b8add26271fe2a5.png) ここで、例えば、高橋君が $ (2,3),(2,4),(3,4) $ の $ 3 $ つのマス(下図の赤いマス)を新しく黒く塗ったとします。 !\[\](https://img.atcoder.jp/abc296/d2d0f1745af0dc309341f96dbd83e717.png) このとき、最初から黒く塗られていたマスと新しく黒く塗られたマスは合わせて次のようになり、黒く塗られたマス全体は連結となります。 !\[\](https://img.atcoder.jp/abc296/76bebc05c2d7c5240151b534ba30f29b.png) $ 2 $ つ以下のマスを新しく黒く塗ることで黒く塗られたマス全体を連結にすることはできないため、$ 3 $ が答えとなります。 白く塗られたマス全体を連結にする必要はないことに注意してください。

### Sample Explanation 2

最初から全てのマスが黒く塗られている可能性もあります。

## 样例 #1

### 输入

```
3 5
...#.
.#...
....#```

### 输出

```
3```

## 样例 #2

### 输入

```
3 3
###
###
###```

### 输出

```
0```

## 样例 #3

### 输入

```
10 1
.
#
.
.
.
.
.
.
#
.```

### 输出

```
6```

# 题解

## 作者：Phartial (赞：2)

考虑状压 dp。

设 $f_{i,j,s}$ 表示当前正在决策坐标为 $(i,j)$ 的格子，且列状态为 $s$。其中列状态维护了当前轮廓线上的连通块，我们可以使用最小表示法来简单维护。

（为什么不用广义括号序列？因为其涉及到 $5$ 个可选值，由于 $m\le 7$，所以这两个都需要用到八进制，而最小表示法显然要好写很多。）

如果我们选择将当前格子变成黑色，那么相当于合并了当前格上面和左边的两个连通块。

如果我们保持当前格子为白色，那么啥都不变，但要注意，这可能会导致某个连通块被孤立导致错解。

直接统计答案即可。

```cpp
#include <iostream>
#include <map>

using namespace std;

const int kN = 101, kM = 7;
const int kL = 1 << 3 * kM;

int n, m, o, l, li, ans = 1e9, gc[kL], gt[kL][kM], ct[kL][8];
char a[kN][kM];
map<int, int> f[2];

int G(int s, int i) { return i < 0 ? 0 : (s >> i * 3 & 7); }
int S(int s, int i, int v) { return s ^ (G(s, i) << i * 3) ^ (v << i * 3); }
void U(int i, int v) {
  auto p = f[o].find(i);
  if (p != f[o].end()) {
    p->second = min(p->second, v);
  } else {
    f[o][i] = v;
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  l = 1 << 3 * m;
  for (int i = 0; i < l; ++i) {
    for (int j = 0; j < m; ++j) {
      ++ct[i][G(i, j)];
    }
    for (int j = 1; j <= m; ++j) {
      if (!ct[i][j]) {
        gc[i] = j;
        break;
      }
    }
    for (int j = 1; j < m; ++j) {
      int vl = G(i, j - 1), vu = G(i, j);
      gt[i][j] = i;
      for (int k = 0; k < m; ++k) {
        if (G(gt[i][j], k) == vu) {
          gt[i][j] = S(gt[i][j], k, vl);
        }
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> a[i][j];
    }
  }
  for (int i = n; i >= 1; --i) {
    for (int j = m - 1; j >= 0; --j) {
      if (a[i][j] == '#') {
        li = i;
        break;
      }
    }
    if (li) {
      break;
    }
  }
  f[o][0] = 0;
  for (int i = 1; i <= li; ++i) {
    for (int j = 0; j < m; ++j) {
      o ^= 1;
      f[o].clear();
      for (auto k : f[!o]) {
        int s = k.first, fv = k.second;
        int vl = G(s, j - 1), vu = G(s, j), v = (a[i][j] == '.');
        if (!vl && !vu) {  // 新开一个连通块
          U(S(s, j, gc[s]), fv + v);
        } else if (vl && !vu) {  // 接上左边的连通块
          U(S(s, j, vl), fv + v);
        } else if (!vl && vu) {  // 接上上面的连通块
          U(s, fv + v);
        } else {  // 将左边和上面的连通块接起来
          U(gt[s][j], fv + v);
        }
        if (a[i][j] == '.') {  // 不涂黑
          int vu = G(s, j);
          if (!vu || ct[s][vu] > 1) {  // 不能孤立某个连通块
            U(S(s, j, 0), fv);
          }
        }
      }
    }
  }
  for (auto p : f[o]) {
    int i = p.first, fv = p.second;
    int g = 0;
    for (int j = 0; j < m; ++j) {
      int v = G(i, j);
      if (!g) {
        g = v;
      } else if (v && v != g) {
        g = -1;
        break;
      }
    }
    if (~g) {
      ans = min(ans, fv);
    }
  }
  cout << ans;
  return 0;
}
```


---

## 作者：do_while_true (赞：1)

考虑一行一行往下 dp，一个状态需要记录每个格子是否是黑色，对于黑色还有记录其并查集。爆搜跑一下本质不同状态数不是很多，dp 就行了。

这里爆搜并查集的方法是，让一个连通块根是最小的那个点，然后把每个点所在连通块中的根字符串哈希起来。

$m=7$ 的时候状态数只有 $324$．

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<assert.h>
#include<map>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n';
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n';
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pil>vpil;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
const int mod=998244353;
inline void cadd(int &x,int y){x=(x+y>=mod)?(x+y-mod):(x+y);}
inline void cdel(int &x,int y){x=(x-y<0)?(x-y+mod):(x-y);}
inline int add(int x,int y){return (x+y>=mod)?(x+y-mod):(x+y);}
inline int del(int x,int y){return (x-y<0)?(x-y+mod):(x-y);}
int qpow(int x,int y){
	int s=1;
	while(y){
		if(y&1)s=1ll*s*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return s;
}
const int N=110;
const int inf=0x3f3f3f3f;
int n,m;
char ch[N][11];
int s[N][11];
struct ST{
	int ok[8],p[8];
	ull has;
	void rhas(){
		has=0;
		for(int i=0;i<m;i++)has=has*233+ok[i]+1;
		for(int i=0;i<m;i++)has=has*233+p[i]+1;
	}
	void mem(){
		for(int i=0;i<8;i++)ok[i]=0;
		for(int i=0;i<8;i++)p[i]=i;
	}
	int getfa(int x){return p[x]==x?x:p[x]=getfa(p[x]);}
	void merge(int x,int y){
		int fx=getfa(x),fy=getfa(y);
		if(fx>fy)
			swap(fx,fy);
		p[fy]=fx;
		for(int i=0;i<m;i++)getfa(i);
	}
	void init(){
		for(int i=1;i<m;i++)
			if(ok[i]&&ok[i-1])
				merge(i-1,i);
	}
	bool check(){
		int c=0;
		for(int i=0;i<m;i++)
			if(ok[i])
				c+=p[i]==i;
		return c<=1;
	}
};
int tot;
map<ull,int>vis;
ST st[510];
int dfs(ST a){
	a.rhas();
	if(vis[a.has])return vis[a.has];
	int ed=vis[a.has]=++tot;
	st[tot]=a;
	for(int i=0;i<m;i++)
		for(int j=i+1;j<m;j++)
			if(a.ok[i] && a.ok[j] && a.p[i]!=a.p[j]){
				ST b=a;
				b.merge(i,j);
				dfs(b);
			}
	return ed;
}
int dp[110][510];
int pos[220];
signed main(){
	#ifdef do_while_true
//		assert(freopen("data.in","r",stdin));
//		assert(freopen("data.out","w",stdout));
	#endif
	read(n);read(m);
	for(int i=1;i<=n;i++){
		scanf("%s",ch[i]);
		for(int j=0;j<m;j++)
			s[i][j]=ch[i][j]=='#'?1:0;
	}
	for(int i=0;i<(1<<m);i++){
		ST a;a.mem();
		for(int j=0;j<m;j++)
			if((1<<j)&i)
				a.ok[j]=1;
		a.init();
		pos[i]=dfs(a);
	}
	int l=1,r=n;
	for(int i=1;i<=n;i++){
		bool fl=0;
		for(int j=0;j<m;j++)
			if(s[i][j])
				fl=1;
		if(fl){
			l=i;
			break;
		}
	}
	for(int i=n;i>=1;i--){
		bool fl=0;
		for(int j=0;j<m;j++)
			if(s[i][j])
				fl=1;
		if(fl){
			r=i;
			break;
		}
	}
	memset(dp,0x3f,sizeof(dp));
	{
		int S=0;
		for(int j=0;j<m;j++)
			S|=s[l][j]<<j;
		for(int i=0;i<(1<<m);i++)
			if((i&S)==S)
				dp[l][pos[i]]=__builtin_popcount(i^S);
	}
	for(int i=l;i<r;i++){
		int S=0;
		for(int j=0;j<m;j++)
			S|=s[i+1][j]<<j;
		for(int c=1;c<=tot;c++)
			if(dp[i][c]!=inf){
				ST a=st[c];
				int T=((1<<m)-1)^S;
				for(int O=T;;O=(O-1)&T){
					int tS=((1<<m)-1)^O;
					ST b=a;
					ST d=st[pos[tS]];
					vi hav(m);
					for(int j=0;j<m;j++)
						if(((1<<j)&tS) && b.ok[j])
							hav[b.p[j]]=1;
					bool fl=0;
					for(int j=0;j<m;j++)
						if(b.ok[j] && b.p[j]==j)
							if(!hav[j])
								fl=1;
					if(fl)continue;
					for(int j=0;j<m;j++)
						for(int k=j+1;k<m;k++)
							if(b.p[j]==b.p[k] && d.ok[j] && d.ok[k] && b.ok[j] && b.ok[k])
								d.merge(j,k);
					d.rhas();
					cmin(dp[i+1][vis[d.has]],dp[i][c]+__builtin_popcount(tS^S));
					if(O==0)break;
				}
			}
	}
	int ans=inf;
	for(int i=1;i<=tot;i++)
		if(st[i].check())
			cmin(ans,dp[r][i]);
	cout << ans << '\n';
    #ifdef do_while_true
		cerr<<'\n'<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
	#endif
	return 0;
}
```

---

