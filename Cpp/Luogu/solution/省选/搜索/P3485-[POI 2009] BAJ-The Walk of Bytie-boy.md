# [POI 2009] BAJ-The Walk of Bytie-boy

## 题目背景

[English Edition](/paste/9lmt83m9)

## 题目描述

给出一张 $n$ 个点 $m$ 条边的有向图，每条边上有一个字母，并给出一个整数 $d$ 和一个序列 $s_1, s_2, \dots, s_d$。  

你需要对每一个 $i(1\le i<n)$ 求出一条从 $s_i$ 到 $s_{i+1}$ 的最短路径满足这条路径上的边上的字母连起来后是回文的。  

不保证每个点最多只在 $s$ 中出现一次。

## 说明/提示

对于 $100\%$ 的数据，$2\le n\le 400$，$1\le m\le 6\times10^4$，$1\le x_i,y_i\le n$，$2\le d\le100$，$1\le s_i\le n$。

同时保证不会出现重边与自环。

## 样例 #1

### 输入

```
6 7
1 2 a
1 3 x
1 4 b
2 6 l
3 5 y
4 5 z
6 5 a
3
1 5 3
```

### 输出

```
3 ala
-1
```

# 题解

## 作者：wgyhm (赞：6)

## Description

https://www.luogu.com.cn/problem/P3485

## Solution

序列上怎么做？抛开在图上不太可行的 manacher，考虑区间 dp。

令 $f_{x,y}$ 表示从 $x\to y$ 的最短回文路径。转移枚举 $l\to x,y\to r$，如果经过同样的字母，就 $f_{l,r}\gets\min f_{x,y}+2$。

但是这样复杂度应该是 $O(m^2)$ 的，没有前途。

考虑转移拆成两部分，令 $f_{x,y}$ 还是表示 $x\to y$ 的最短回文路径，$g_{x,y,c}$ 表示 $x\to z\xrightarrow{c} y$ 且 $x\to z$ 是回文路径的最短路径。

有转移：

* $f_{z,y}\gets \min\{ g_{x,y,c}\}+1,z\xrightarrow{c}x$。

* $g_{x,z,c}\gets \min \{f_{x,y}\},y\xrightarrow{c}z$。

用 bfs，且实现的好的话，每个状态只会被转移一次。复杂度 $O(nm+26n^2)$。

为了保证复杂度正确，最好对每条边的起点和边权存终点，减少转移的冗余。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define maxn 405
#define put() putchar('\n')
#define Tp template<typename T>
#define Ts template<typename T,typename... Ar>
using namespace std;
Tp void read(T &x){
    int f=1;x=0;char c=getchar();
    while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
    while (c>='0'&&c<='9') {x=x*10+c-'0';c=getchar();}
    x*=f;
}
namespace Debug{
	Tp void _debug(char* f,T t){cerr<<f<<'='<<t<<endl;}
	Ts void _debug(char* f,T x,Ar... y){while(*f!=',') cerr<<*f++;cerr<<'='<<x<<",";_debug(f+1,y...);}
	#define gdb(...) _debug((char*)#__VA_ARGS__,__VA_ARGS__)
}using namespace Debug;
#define fi first
#define se second
#define mk make_pair
const int mod=1e9+7;
int power(int x,int y=mod-2) {
	int sum=1;
	while (y) {
		if (y&1) sum=sum*x%mod;
		x=x*x%mod;y>>=1;
	}
	return sum;
}
int n,m;
vector<int>to[maxn][27],pre[maxn][27];
int f[maxn][maxn],g[maxn][maxn][27];
pair<int,int> pg[maxn][maxn][27];
struct yyy {
	int l,r,c;
	yyy (int a=0,int b=0,int d=0) {
		l=a;r=b;c=d;
	}
}pf[maxn][maxn];
queue<pair<int,int> >q1;
queue<yyy>q2;
int Ans[100005];
void print(int x,int y) {
	int l=0,r=f[x][y]+1,c,tmp1,tmp2,len=f[x][y],i;
	while (l+1<r) { 
		Ans[++l]=pf[x][y].c;
		tmp1=pf[x][y].l,tmp2=pf[x][y].r;
		c=pf[x][y].c,x=tmp1,y=tmp2;
		if (l+1>=r) break;
		Ans[--r]=c;
		tmp1=pg[x][y][c].fi,tmp2=pg[x][y][c].se;
		x=tmp1,y=tmp2;
	}
	for (i=1;i<=len;i++) putchar(Ans[i]+'a');
} 
signed main(void){
	int i,j,x,y,z,k;char ch;
	memset(f,0x3f,sizeof(f));
	memset(g,0x3f,sizeof(g));
	read(n);read(m);
	for (i=1;i<=n;i++) f[i][i]=0,q1.push(mk(i,i));
	for (i=1;i<=m;i++) {
		read(x);read(y);ch=getchar();
		to[x][ch-'a'].push_back(y);
		pre[y][ch-'a'].push_back(x);
		f[x][y]=1;pf[x][y]=yyy(0,0,ch-'a');
		q1.push(mk(x,y));
	}
	while (!q1.empty()||!q2.empty()) {
		if (!q1.empty()&&(q2.empty()||f[q1.front().fi][q1.front().se]<=g[q2.front().l][q2.front().r][q2.front().c])) {
			x=q1.front().fi,y=q1.front().se;q1.pop();
			for (i=0;i<26;i++) {
				for (auto tmp:to[y][i]) if (g[x][tmp][i]>f[x][y]+1) {
					g[x][tmp][i]=f[x][y]+1;
					pg[x][tmp][i]=mk(x,y);
					q2.push(yyy(x,tmp,i));
				}
			}
		}
		else {
			x=q2.front().l,y=q2.front().r,z=q2.front().c;q2.pop();
			for (auto tmp:pre[x][z]) if (f[tmp][y]>g[x][y][z]+1) {
				f[tmp][y]=g[x][y][z]+1;
				pf[tmp][y]=yyy(x,y,z);
				q1.push(mk(tmp,y));
			} 
		}
	}
	read(k);read(x);k--;
	while (k--) {
		read(y);
		if (f[x][y]<=1e9) printf("%d ",f[x][y]),print(x,y),put();
		else puts("-1"); 
		x=y;
	}
	return 0;
}
//i=begin && g++ $i.cpp -o $i -std=c++14 && ./$i
```



---

## 作者：win114514 (赞：4)

暴力没前途，怎么可能，直接喜提最劣解。

### 思路

考虑一个最基本做法。


设 $f_{i,j}$ 表示 $(i,j)$ 是回文路径的最小长度。

然后对每个二元组广搜。

拓展时暴力搜 $i$ 的所有入边和 $j$ 的所有出边。

这样是 $O(m^2)$ 的。

但是我们会感到奇怪。

明明只有 $n^2$ 个状态，为什么却花了 $O(m^2)$ 的时间。

发现最大的时间损耗在我们的入边有可能和出边匹配过。

这样就有了很多无效的匹配。

怎么办。

使用 bitset！

我们将能匹配的出边用 bitset 存，每个点没有匹配过的点也用 bitset 存。

寻找的时候把两个与一下，找到里面的所有点即可。

时间复杂度降为了：$O(\frac{mn^2}{w})$。

### Code

```cpp
/*
  ! 如果没有天赋，那就一直重复
  ! Created: 2024/06/26 09:26:19
*/
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
// #define int long long
#define mp(x, y) make_pair(x, y)
#define eb(...) emplace_back(__VA_ARGS__)
#define fro(i, x, y) for (int i = (x); i <= (y); i++)
#define pre(i, x, y) for (int i = (x); i >= (y); i--)
inline void JYFILE19();

using i64 = long long;
using u64 = unsigned long long;
using PII = pair<int, int>;

bool ST;
const int N = 410;
const int M = 60010;
const int mod = 998244353;

int n, m, d, ct, tt, tp, st[M], f[N][N], head[N], fead[N];
pair<PII, int> nt[N][N];
vector<int> res;
template<int T> struct Bitset {
  u64 v[T / 64 + 10], n, all;
  Bitset() { n = T / 64 + 1, all = -1; }
  inline void clr() { memset(v, 0, sizeof v); }
  inline void get() {
    res.clear();
    fro(i, 0, n) {
      if (v[i]) {
        auto x = v[i], lg = 1ull;
        while (x) lg = __lg(x), res.eb(lg + i * 64), x -= (1ull << lg);
      }
    }
  }
  inline void set(int x) { v[x>>6] ^= 1ull<<(x&63); }
  inline void operator&=(const Bitset<T> &tmp) { fro(i, 0, n) v[i] &= tmp.v[i]; }
};
Bitset<401> w, g[27], vs[401];

struct edge {
  int to, nxt, val;
} e[M << 1], p[M << 1];

inline void add(int x, int y, int z) {
  e[++ct] = {y, head[x], z}, head[x] = ct;
  p[++tt] = {x, fead[y], z}, fead[y] = ct;
}
inline void sol(int l, int r) {
  int L, R;
  tie(L, R) = nt[l][r].x;
  st[++tp] = nt[l][r].y;
  if (L == l && r == R) return;
  sol(L, R);
}

signed main() {
  JYFILE19();
  cin >> n >> m;
  fro(i, 1, m) {
    int x, y; char c;
    cin >> x >> y >> c;
    add(x, y, c - 'a');
  }
  queue<PII> q;
  fro(i, 1, n) fro(j, 1, n) if (i != j) vs[i].set(j);
  fro(i, 1, n) {
    for (int j = head[i]; j; j = e[j].nxt) {
      if (f[i][e[j].to] == 0) {
        f[i][e[j].to] = 1;
        nt[i][e[j].to] = {{i, e[j].to}, e[j].val};
        vs[i].set(e[j].to);
        q.emplace(i, e[j].to);
      }
    }
  }
  fro(i, 1, n) {
    for (int j = head[i]; j; j = e[j].nxt)
      for (int k = head[e[j].to]; k; k = e[k].nxt) {
        if (f[i][e[k].to] == 0 && e[j].val == e[k].val) {
          f[i][e[k].to] = 2;
          nt[i][e[k].to] = {{i, e[k].to}, e[k].val};
          vs[i].set(e[k].to);
          q.emplace(i, e[k].to);
        }
      }
  }
  while (q.empty() == 0) {
    int l, r;
    tie(l, r) = q.front(), q.pop();
    fro(i, 0, 25) g[i].clr();
    for (int i = head[r]; i; i = e[i].nxt) {
      g[e[i].val].set(e[i].to);
    }
    for (int i = fead[l]; i; i = p[i].nxt) {
      w = vs[p[i].to], w &= g[p[i].val], w.get();
      for (auto j : res) {
        f[p[i].to][j] = f[l][r] + 2;
        nt[p[i].to][j] = {{l, r}, p[i].val};
        vs[p[i].to].set(j);
        q.emplace(p[i].to, j);
      }
    }
  }
  cin >> d;
  for (int i = 1, las = 0; i <= d; i++) {
    int x; cin >> x;
    if (i > 1) {
      if (f[las][x]) {
        cout << f[las][x] << " ", tp = 0, sol(las, x);
        fro(i, 1, tp) cout << (char)(st[i] + 'a');
        if (f[las][x] % 2 == 0) cout << (char)(st[tp] + 'a');
        pre(i, tp, 2) cout << (char)(st[i - 1] + 'a');
        cout << "\n";
      } else {
        cout << -1 << "\n";
      }
    }
    las = x;
  }
  return 0;
}

bool ED;
inline void JYFILE19() {
  // freopen("", "r", stdin);
  // freopen("", "w", stdout);
  srand(random_device{}());
  ios::sync_with_stdio(0), cin.tie(0);
  double MIB = fabs((&ED - &ST) / 1048576.), LIM = 32;
  cerr << "MEMORY: " << MIB << endl, assert(MIB <= LIM);
}
```

---

## 作者：small_john (赞：1)

## 前言

Upd：修改了一处笔误，往管理通过。

模拟赛遇到了这道题，写篇题解纪念一下。

## 思路

先讲暴力。

设 $f_{i,j}$ 表示从 $i$ 到 $j$ 的最短回文路径。很明显，如果存在一对 $x\to i$ 的边和 $j\to y$ 的边满足边上的字母相同，$f_{x,y}$ 就可以从 $f_{i,j}$ 转移过来。这样暴力做的时间复杂度是 $O(n^2+m^2)$，显然不能通过。

考虑优化上述暴力，设 $g_{i,j,k}$ 表示从 $i$ 到 $j$ 的路径除了最后一条字母为 $k$ 的边是回文路径的最短路径长度。如果存在一条 $y\to j$ 且字母为 $k$ 的边，$g_{i,j,k}$ 就可以从 $f_{i,y}$ 转移过来。而如果存在一条 $x\to i$ 且字母为 $k$ 的边，$g_{i,j,k}$ 就可以转移到 $f_{x,j}$。

至于输出回文串，对于每一个状态记录一个前驱即可。

用广搜实现上述过程，先处理出当前这一层的 $g$，再处理出这一层的 $f$。时间复杂度就做到了 $O(n^2+nm)$，大约带 26 倍的常数。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3+5;
int n,m;
vector<int> g[N][26],_g[N][26];
int dis[N][N],d[N][N][26],p[N][N][26],val[N][N];
pair<int,int> pre[N][N];
void bfs()
{
	queue<pair<int,int> > q;
	queue<pair<int,pair<int,int>>> _q; 
	for(int i = 1;i<=n;i++)
		for(int j = 1;j<=n;j++)
		{
			dis[i][j] = -1;
			for(int k = 0;k<26;k++) d[i][j][k] = -1;
		}
	for(int i = 1;i<=n;i++) dis[i][i] = 0,q.push({i,i});
	for(int i = 1;i<=n;i++)	for(int j = 0;j<26;j++) for(auto k:g[i][j]) q.push({i,k}),dis[i][k] = 1,val[i][k] = j;
	while(!q.empty())
	{
		while(!q.empty())
		{
			int u1 = q.front().first,u2 = q.front().second;q.pop();
			for(int i = 0;i<26;i++)	
				for(auto v:g[u2][i])
					if(d[u1][v][i]==-1) d[u1][v][i] = dis[u1][u2]+1,p[u1][v][i] = u2,_q.push({i,{u1,v}});
		}
		while(!_q.empty())
		{
			int c = _q.front().first,u1 = _q.front().second.first,u2 = _q.front().second.second;_q.pop();
			for(auto v:_g[u1][c]) 
				if(dis[v][u2]==-1) dis[v][u2] = d[u1][u2][c]+1,pre[v][u2] = {u1,p[u1][u2][c]},val[v][u2] = c,q.push({v,u2});
		}
	}
}
int qq[N];
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	char ch;
	for(int i = 1,u,v;i<=m;i++)
		cin>>u>>v>>ch,g[u][ch-'a'].push_back(v),_g[v][ch-'a'].push_back(u);
	bfs();
	int q;cin>>q;
	for(int i = 1;i<=q;i++) cin>>qq[i];
    for(int i = 1;i<q;i++)
    {
        int x = qq[i],y = qq[i+1],_x,_y;
        _x = x,_y = y;
        cout<<dis[x][y]<<' ';
        if(dis[x][y]!=-1)
        {
            string s = "";
            char c;
            while(x&&y)
            {
                if(x==y) break;
                if(dis[x][y]==1)
                {
                    c = 'a'+val[x][y];
                    break;
                }
                auto p = pre[x][y];
                s+='a'+val[x][y];
                x = p.first,y = p.second;
            }
            cout<<s;
            if(dis[_x][_y]&1) cout<<c;
            reverse(s.begin(),s.end());
            cout<<s;
        }
        cout<<'\n';
    }
	return 0;
}
```

---

## 作者：未来姚班zyl (赞：1)

## 题目大意

给定一个边带权的有向图，边权为字母，多次询问 $s$ 到 $t$ 的最短回文路径长度，并要求给出方案。

## 题目分析

考虑一个超级显然的暴力，设 $dp_{i,j}$ 表示 $s=i$，$t=j$ 的答案。

转移只需要对于每种颜色枚举 $i$ 的入边和 $j$ 的出边，使用 bfs 转移即可，复杂度 $O(n^4V)$，$V=26$。

我们充分发扬暴力精神，使用 bitset 维护还未加入的状态，复杂度 $O(\frac{n^4V}{w})$，**常数极小**，通过此题。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(int x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N=4e2+5,M=1e5+5,inf=(1LL<<31)-1;
int n,m,type,h[N],to[M],nxt[M],cnt,w[M];
struct edg{
	int y,w;
};
vector<edg>p[N];
bitset<401>v[401][27],V[401][27],d[401],f,g;
inline void add_(int a,int b,int c){
	if(v[a][c][b])return;
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt,w[cnt]=c;
	p[b].pb({a,c}),v[a][c][b]=V[b][c][a]=1;
}
inline int id(int x,int y){
	return (x-1)*n+y;
}
int dist1[N*N],pr1[N*N],col1[N*N];
inline void bfs1(){
	repn(i)repn(j)d[i][j]=1;
	rep(i,1,n*n)dist1[i]=inf;
	queue<Pi>q;
	repn(x)q.push({x,x}),dist1[id(x,x)]=0,d[x][x]=0;
	while(!q.empty()){
		int x=q.front().first,y=q.front().second;
		q.pop();
		rep(col,1,26){
			int nx=V[x][col]._Find_first();
			while(nx<=n){
				f=d[nx]&v[y][col];
				int ny=f._Find_first();
				while(ny<=n){
					d[nx][ny]=0;
					dist1[id(nx,ny)]=dist1[id(x,y)]+2,pr1[id(nx,ny)]=id(x,y),col1[id(nx,ny)]=col;
					q.push({nx,ny});
					ny=f._Find_next(ny);
				}
				nx=V[x][col]._Find_next(nx);
			}
		}
	}
}
int dist2[N*N],pr2[N*N],col2[N*N];
inline void bfs2(){
	repn(i)repn(j)d[i][j]=1;
	rep(i,1,n*n)dist2[i]=inf;
	queue<Pi>q;
	repn(x)e(x)q.push({x,y}),dist2[id(x,y)]=1,d[x][y]=0;
	while(!q.empty()){
		int x=q.front().first,y=q.front().second;
		q.pop();
		rep(col,1,26){
			int nx=V[x][col]._Find_first();
			while(nx<=n){
				f=d[nx]&v[y][col];
				int ny=f._Find_first();
				while(ny<=n){
					d[nx][ny]=0;
					dist2[id(nx,ny)]=dist2[id(x,y)]+2,pr2[id(nx,ny)]=id(x,y),col2[id(nx,ny)]=col;
					q.push({nx,ny});
					ny=f._Find_next(ny);
				}
				nx=V[x][col]._Find_next(nx);
			}
		}
	}
}
int st[N*N],tp,a[N];
inline void Main(){
	n=read(),m=read();
	while(m--){
		int x=read(),y=read();char c;cin>>c;
		add_(x,y,c-'a'+1);
	}
	bfs1(),bfs2();
	int q=read();
	rep(i,1,q)a[i]=read();
	rep(i,1,q-1){
		int s=a[i],t=a[i+1];
		int len=min(dist1[id(s,t)],dist2[id(s,t)]);
		if(len==inf)puts("-1");
		else {
			cout <<len<<' ';
				int T=len/2;tp=0;
				if(len==dist1[id(s,t)]){
					while(T--){
						st[++tp]=col1[id(s,t)];
						int nx=pr1[id(s,t)];
						s=(nx-1)/n+1,t=(nx-1)%n+1;
					}
					rep(i,1,tp)putchar('a'+st[i]-1);
					per(i,tp,1)putchar('a'+st[i]-1);
				}else {
					while(T--){
						st[++tp]=col2[id(s,t)];
						int nx=pr2[id(s,t)];
						s=(nx-1)/n+1,t=(nx-1)%n+1;
					}
					rep(i,1,tp)putchar('a'+st[i]-1);
					rep(c,1,26)if(v[s][c][t]){
						putchar('a'+c-1);
						break;
					}
					per(i,tp,1)putchar('a'+st[i]-1);
				}
			puts("");
		}
	}
}
signed main(){
	int T=1;
	while(T--)Main();
	return 0;
}	
```

---

