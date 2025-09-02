# Mike and Fish

## 题目描述

As everyone knows, bears love fish. But Mike is a strange bear; He hates fish! The even more strange thing about him is he has an infinite number of blue and red fish.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF547D/031dc6fdab66492c31079b30a48004c3918930a2.png)He has marked $ n $ distinct points in the plane. $ i $ -th point is point $ (x_{i},y_{i}) $ . He wants to put exactly one fish in each of these points such that the difference between the number of red fish and the blue fish on each horizontal or vertical line is at most 1.

He can't find a way to perform that! Please help him.

## 样例 #1

### 输入

```
4
1 1
1 2
2 1
2 2
```

### 输出

```
brrb
```

## 样例 #2

### 输入

```
3
1 1
1 2
2 1
```

### 输出

```
brr
```

# 题解

## 作者：shadowice1984 (赞：52)

标算是什么数学归纳法+带加删边的欧拉回路……，复杂度是$O(nlogn)$的

这个做法过于硬核了，我们不如来想想亲民一些的乱搞做法(没准是对的？)

(反正这个做法我既不会证也不会叉，欢迎dalao来叉或者来证)

对于x坐标相同的点，我们把这些点**两两配对**,如果剩下点则不管，然后在每一对点之间连一条边

对于y坐标相等的点，我们也把这些点**两两配对**，如果剩下点则不管，然后在每一对点之间连一条边

最后对得到的图进行红蓝染色(其实就是黑白染色)就可以得到我们的方案了

证明也很简单，如果我们红蓝染色成功，那么对于每一个x或者y坐标来讲最多剩下一个红点或者蓝点

~~所以这个算法gg的时候就是我们红蓝染色失败了，也就是说我们连出了奇环……，不知道有没有dalao可以给出一组连出奇环的方案~~

上代码~

```C
#include<cstdio>
#include<algorithm>
using namespace std;const int N=1e6+10;typedef long long ll;
int v[N];int x[N];int ct;int al[N];int col[N];int n;
int lstu[N];int lstv[N];
inline void add(int u,int V){v[++ct]=V;x[ct]=al[u];al[u]=ct;}
inline void dfs(int u,int tw)
{col[u]=tw;for(int i=al[u];i;i=x[i])if(col[v[i]]==-1)dfs(v[i],tw^1);} 
int main()
{
    scanf("%d",&n);for(int i=1;i<=n;i++)col[i]=-1;
    for(int i=1,x,y;i<=n;i++)
    {
        scanf("%d%d",&x,&y);
        if(lstu[x]){add(lstu[x],i),add(i,lstu[x]),lstu[x]=0;}else lstu[x]=i;
        if(lstv[y]){add(lstv[y],i),add(i,lstv[y]),lstv[y]=0;}else lstv[y]=i;
    }for(int i=1;i<=n;i++)if(col[i]==-1)dfs(i,0);
    for(int i=1;i<=n;i++)putchar((col[i])?'r':'b');return 0;
}
```






---

## 作者：StudyingFather (赞：31)

题解区不少神仙都是欧拉回路做法 orz

我的做法和 SI 神仙的做法思路上差不多。这里帮忙补充一些比较严密的证明。

考虑若干个横坐标相等的点，我们随机将它们两两配对后连边（如果有偶数个点，则能全部配对，否则剩下一个单独的点）；对于纵坐标相等的点也作如此处理。

最后得到的图可以证明是一个二分图（证明后附），我们直接对其黑白染色即可得到答案。

接下来是证明时间。

1. 证明得到的图是二分图。

每个点最多只连两条边，且最多一条横向边和最多一条纵向边，即不存在一个点同时与两个横坐标相等的点连边的情况。

这意味着形成的环一定为横向边和纵向边交替的形态，也即不存在奇环，从而得到的图为二分图。

2. 这种构造方案的正确性。

按照上面的建图方式，每个横坐标相同而形成的点对颜色必定相反，纵坐标相同的点对情况同理。

因此横坐标等于 $x$ 的点中，其中配对的点里黑点数必定等于白点数，而没有参加配对的点最多只有一个，符合题目要求。

```cpp
// Problem : D. Mike and Fish
// Contest : Codeforces Round #305 (Div. 1)
// URL : https://codeforces.com/contest/547/problem/D
// Author : StudyingFather
// Site : https://studyingfather.com
// Memory Limit : 256 MB
// Time Limit : 3000 ms
// Powered by CP Editor (https://github.com/cpeditor/cp-editor)

#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
int vis[200005],p[200005],q[200005];
vector<int> e[200005];
void dfs(int u,int c)
{
 vis[u]=c;
 for(auto v:e[u])
  if(vis[v]==-1)dfs(v,c^1);
}
int main()
{
 memset(vis,-1,sizeof(vis));
 int n;
 cin>>n;
 for(int i=1;i<=n;i++)
 {
  int x,y;
  cin>>x>>y;
  if(p[x])
  {
   e[i].push_back(p[x]);
   e[p[x]].push_back(i);
   p[x]=0;
  }
  else p[x]=i;
  if(q[y])
  {
   e[i].push_back(q[y]);
   e[q[y]].push_back(i);
   q[y]=0;
  }
  else q[y]=i;
 }
 for(int i=1;i<=n;i++)
  if(vis[i]==-1)dfs(i,0);
 for(int i=1;i<=n;i++)
  cout<<(vis[i]?'r':'b');
 return 0;
}
```

---

## 作者：Kinandra (赞：26)

标签: 图论, 欧拉回路.

我们转化一下问题: 将点看成连接其横坐标和纵坐标的边, 我们为每一条边定向, 使得每一个点的入度与出度的差的绝对值不超过 $1$ .

这个很容易可以转化成一个欧拉回路的问题: 显然度数为偶数的点入度等于出度, 而度数为奇数的点入出度恰好差 $1$ . 我们将度数为奇数的点连一条虚拟边到一个虚拟点, 由于的度数为奇数的点必然是偶数个, 那么虚拟点的度数也为偶数, 我们对新图跑欧拉回路对边定向即可.

时间复杂度 $\mathcal O(n)$.

```cpp
#include <bits/stdc++.h>
using namespace std;
int read();
int n;
int hd[400005], nx[800005], to[800005], cnt;
int deg[800005];
void add(int f, int t) {
    nx[++cnt] = hd[f], hd[f] = cnt, to[cnt] = t, ++deg[f];
}
struct E {
    int u, v;
    void init() { u = read(), v = read() + 200000, add(u, v), add(v, u); }
} p[200005];
bool vis[800005];
int res[200005];

int tcc;
void dfs(int u) {
    for (int &i = hd[u], e; i; i = nx[i])
        if (!vis[e = i >> 1])
            vis[e] = 1, (e <= n ? res[e] = i & 1 : 0), dfs(to[i]);
}

int main() {
    n = read(), cnt = 1;
    for (int i = 1; i <= n; ++i) p[i].init();
    for (int i = 1; i <= 400000; ++i)
        if (deg[i] & 1) add(0, i), add(i, 0);
    for (int i = 1; i <= 400000; ++i) dfs(i);
    for (int i = 1; i <= n; ++i) putchar(res[i] ? 'r' : 'b');
    return 0;
}
const int _SIZE = 1 << 22;
char ibuf[_SIZE], *iS = ibuf, *iT = ibuf;
#define gc                                                         \
    (iS == iT ? iT = ((iS = ibuf) + fread(ibuf, 1, _SIZE, stdin)), \
     (iS == iT ? EOF : *iS++) : *iS++)
int read() {
    int x = 0, f = 1;
    char c = gc;
    while (!isdigit(c)) f = (c == '-') ? -1 : f, c = gc;
    while (isdigit(c)) x = x * 10 + c - '0', c = gc;
    return x * f;
}
```


---

## 作者：zhylj (赞：16)

大家的做法都好神，orz。

先假设所有点都是蓝的。

考虑~~乱搞~~网络流，把行列当作点，第 $x$ 行标号 $x$，第 $y$ 行标号 $y + 2\times 10^5$。

对于点 $(x,y)$，连边 $x\to y+2\times 10^5$，下界为 $0$，上界为 $1$，若这条边有流量则定义这个点被染红。

对于每一行，如果它上面有 $p$ 个点，那么它上面的红点数只能为 $\left\lfloor\dfrac n2\right\rfloor,\left\lceil\dfrac n2\right\rceil$，所以建一条源点到这一行的，下界为 $\left\lfloor\dfrac n2\right\rfloor$，上界为 $\left\lceil\dfrac n2\right\rceil$ 的边。

对于每一列同理连向汇点。

大力跑有源汇上下界可行流即可，时间复杂度 $\mathcal O($能过$)$.

```cpp
const int kM = 2e6 + 5, kN = 4e5 + 15, kX = 2e5 + 5, kInf = 0x3f3f3f3f;

namespace Net {

	struct Edge {
		int v, nxt, c, idx;
	} E[kM];
	int head[kN], w[kN], S, T, s, t, cnt;
	void Init(int ns, int nt) {
		memset(head, 0xff, sizeof(head));
		s = ns; t = nt; cnt = 0;
	}
	void TAdd(int u, int v, int c, int idx) {
		E[cnt] = (Edge) { v, head[u], c, idx }; head[u] = cnt++;
		E[cnt] = (Edge) { u, head[v], 0, idx }; head[v] = cnt++;
	}
	void Add(int u, int v, int low, int upp, int idx = 0) {
		if(low != upp) TAdd(u, v, upp - low, idx);
		w[u] -= low; w[v] += low;
	}
	int tot = 0;
	void Build() {
		Add(t, s, 0, kInf);
		S = t + 1; T = t + 2;
		for(int i = 1; i <= t; ++i) {
			if(w[i] > 0) TAdd(S, i, w[i], 0), tot += w[i];
			if(w[i] < 0) TAdd(i, T, -w[i], 0);
		}
	}
	int lev[kN], cur[kN];
	std::queue <int> que;
	int GetLev(int ss, int tt) {
		memcpy(cur, head, sizeof(cur));
		memset(lev, 0, sizeof(lev));
		lev[ss] = 1; que.push(ss);
		while(!que.empty()) {
			int u = que.front(); que.pop();
			for(int i = head[u]; ~i; i = E[i].nxt) {
				int c = E[i].c, v = E[i].v;
				if(c && !lev[v]) {
					lev[v] = lev[u] + 1;
					que.push(v);
				}
			}
		}
		return lev[tt];
	}
	int Incr(int u, int res_f, int tt) {
		if(u == tt) return res_f;
		int ret = 0, dlt;
		for(int &i = cur[u]; ~i; i = E[i].nxt) {
			int c = E[i].c, v = E[i].v;
			if(c && lev[v] > lev[u] && (dlt = Incr(v, std::min(res_f, c), tt))) {
				E[i].c -= dlt; E[i ^ 1].c += dlt;
				ret += dlt; res_f -= dlt;
				if(!res_f) break;
			}
		}
		return ret;
	}
	int Dinic(int ss, int tt) {
		int max_f = 0;
		while(GetLev(ss, tt)) {
			max_f += Incr(ss, kInf, tt);
		}
		return max_f;
	}
	int col[kN];
	void Construct() {
		for(int i = 1; i <= kX; ++i) {
			for(int j = head[i]; ~j; j = E[j].nxt) {
				int v = E[j].v, idx = E[j].idx;
				if(idx) col[idx] = E[j].c;
			}
		}
	}

}

int n, p[kN];
int main() { 
	int T = 1; //rd(T);
	while(T--) {
		rd(n); Net::Init(kX * 2, kX * 2 + 1);
		for(int i = 1; i <= n; ++i) {
			int x, y; rd(x, y);
			Net::Add(x, y + kX, 0, 1, i);
			++p[y + kX]; ++p[x];
		}
		for(int i = 1; i <= kX; ++i) {
			if(p[i] > 0) Net::Add(Net::s, i, p[i] / 2, (p[i] + 1) / 2);
			if(p[i + kX] > 0) Net::Add(i + kX, Net::t, p[i + kX] / 2, (p[i + kX] + 1) / 2);
		}
		Net::Build();
		Net::Dinic(Net::S, Net::T);
		Net::Construct();
		for(int i = 1; i <= n; ++i) {
			printf("%c", Net::col[i] ? 'b' : 'r');
		}
		printf("\n");
	} return 0;
}
```

---

## 作者：xht (赞：11)

> [CF547D Mike and Fish](https://codeforc.es/contest/547/problem/D)

## 题意

- 给定 $n$ 个整点。
- 你要给每个点染成红色或蓝色。
- 要求同一水平线或垂直线上两种颜色的数量最多相差 $1$。
- $n,x_i, y_i \le 2 \times 10^5$。

## 题解

对于每个点，将横纵坐标之间连一条边。

那么题意转化为对每条边定向使得每个点的入度和出度最多相差 $1$。

由于奇点一定只有偶数个，不妨将其全都连向 $0$。

然后跑一遍欧拉回路即可，时间复杂度 $\mathcal O(n)$。

## 代码

```cpp
const int N = 2e5 + 7;
int n, v[N<<1], d[N<<1], h[N<<1], e[N<<2], t[N<<2], c = 1;

inline void add(int x, int y, int z = 1) {
	e[++c] = y, t[c] = h[x], h[x] = c;
	if (z) add(y, x, 0);
}

void dfs(int x) {
	for (int &i = h[x]; i; i = t[i])
		if (!v[i>>1]) v[i>>1] = 1 + (x < N), dfs(e[i]);
}

int main() {
	rd(n);
	for (int i = 1, x, y; i <= n; i++)
		rd(x), rd(y), add(x, y + N), ++d[x], ++d[y+N];
	for (int i = 1; i < N << 1; i++)
		if (d[i] & 1) add(0, i);
	for (int i = 1; i < N; i++) dfs(i);
	for (int i = 1; i <= n; i++) putchar("br"[v[i]-1]);
	return 0;
}
```

---

## 作者：frankchenfu (赞：5)

  这是一道图论题。
  
  考虑将横纵坐标之间连一条边。
  
  容易发现，如果把每个点的横纵坐标连一条边，那么就会有一个二分图（$x$坐标和$y$坐标）。接下来，我们每一条边就表示一个点。那么怎么判断是红还是蓝呢？

  其实不难。既然是二分图，我们就对它跑一遍欧拉回路定向，入边为蓝，出边为红即可。因为每条边连接都是x坐标和y坐标之间的，所以对边定向就确定了一个点的颜色。
  
  代码：
  ```cpp
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;  
const int MAXN=500010;  

vector<int>p[MAXN];  
int vis[MAXN],ans[MAXN][2];  

void dfs(int x,int y)
{  
    if(vis[x])
    	return;
    else
    	vis[x]=y;
    int sz=p[x].size();
    for(int i=0;i<sz;i++)
        dfs(p[x][i],1^y);
}
int main()
{
    int n,x,y;
    scanf("%d",&n);  
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&x,&y);
        if(ans[x][0])
        {
            p[i].push_back(ans[x][0]);
            p[ans[x][0]].push_back(i);
            ans[x][0]=0;
        }
        else
            ans[x][0]=i;
            
        if(ans[y][1])
        {
            p[i].push_back(ans[y][1]);
            p[ans[y][1]].push_back(i);
            ans[y][1]=0;
        }
        else
            ans[y][1]=i;
    }  
    for(int i=1;i<=n;i++)
    {
        dfs(i,0);
        if(vis[i])
            putchar('r'); 
        else
            putchar('b');
    }
    return 0; 
}  
```

---

## 作者：tzc_wk (赞：4)

安利个人 blog：https://www.cnblogs.com/ET2006/

[Codeforces 题目传送门](https://codeforces.com/contest/547/problem/D) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF547D)

首先考虑将题目中的条件转化为图论的语言。看到“行”“列”，我们很自然地想到二分图中行、列转点，点转边的套路，对于每一行 $x$ 新建一个点 $R(x)$，对于每一列 $x$ 也新建一个点 $C(y)$。考虑对于点 $(x_i,y_i)$，若其被染上红色，就连边 $R(x_i)\to C(y_i)$，否则连边 $C(y_i)\to R(x_i)$。那么显然对于每一行而言，其红色格子的个数就是该行所对应的点的**出度**，其蓝色格子的个数就是该行所对应的点的**入度**；对于每一列而言，其红色格子的个数就是该行所对应的点的入度，其蓝色格子的个数就是该行所对应的点的出度。

因此我们可将题目转化为：给定一张二分图，要求给每条边定向，使每个点入度与出度之差的绝对值不超过 $1$。

我们不妨先考虑原题的一个弱化版本。假设原图中所有点度数都是偶数，那么我们要求一个无向图，使得每个点的入度等于出度。这显然可以用欧拉回路解决，由于每个点度数都是偶数，因此图的每个连通块的导出子图都存在欧拉回路，那么我们对于每个连通块跑一遍欧拉回路，假设为 $v_1\to v_2\to v_3\to\dots\to v_k\to v_1$，那么我们只需对于 $\forall i\in [1,k]$ 将 $v_i$ 与 $v_{i+1}$ 之间的边定向为 $v_i\to v_{i+1}$ 即可，因为 $\forall i\in [1,k]$，显然 $v_{i-1}\to v_i$ 的边会为 $v_i$ 的入度产生 $1$ 的贡献，$v_{i}\to v_{i+1}$ 的边会为 $v_i$ 的出度产生 $1$ 的贡献，因此 $v_i$ 的入度永远等于出度，符合题目要求。

最后考虑原题，本题一个巧妙之处就在于奇点怎么处理。显然对于一个奇点而言，我们要求它的出度与入度之差为 $\pm 1$，而我们希望它的出度与入度之差为 $0$，这样就能归约到弱化版了。因此我们考虑建立一个虚点，将所有奇点与该虚点之间连边，显然对于原图一个合法的定向方式，我们总能控制这些奇点与虚点连边的方向使得每个奇点的入度都等于出度。又根据有向图 $\sum indeg_i=\sum outdeg_i$ 可知该虚点的入度也等于出度，故我们在新图上跑欧拉回路即可。

时间复杂度线性。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int DELTA=2e5+2;
int n,deg[DELTA*2+5],hd[DELTA*2+5],to[DELTA*6+5],nxt[DELTA*6+5],ec=1;
void adde(int u,int v){to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
int vis[DELTA*3+5];
void dfs(int x){
	for(int &e=hd[x];e;e=nxt[e])
		if(!vis[e>>1]) vis[e>>1]=1+(x<=DELTA),dfs(to[e]);
}
int main(){
	scanf("%d",&n);
	for(int i=1,x,y;i<=n;i++){
		scanf("%d%d",&x,&y);++deg[x];++deg[y+DELTA];
		adde(x,y+DELTA);adde(y+DELTA,x);
	}
	for(int i=1;i<=DELTA*2;i++)
		if(deg[i]&1) adde(0,i),adde(i,0);
	for(int i=1;i<=DELTA;i++) dfs(i);
	for(int i=1;i<=n;i++) putchar((vis[i]==1)?'r':'b');
	return 0;
}
```



---

## 作者：lhm_ (赞：3)

考虑将每个点的横纵坐标看作点，将原先在坐标系上的点看作边，那么题目的要求即为将新图中的每条边定向后，每个点的入度出度的差的绝对值不大于 $1$。

因为度数为奇数的点的个数一定为偶数，所以可以将度数为奇数的点两两配对，在两点之间连一条边。这样每个点度数就都为偶数了，然后可以用欧拉回路来给每条边定向。每条边的方向就对应着原先在坐标系上的点的颜色。

和 [Points and Segments](https://www.luogu.com.cn/problem/CF429E) 很像。

```cpp
#include<bits/stdc++.h>
#define maxn 800010
#define d 200010
using namespace std;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,tot,las;
int p[maxn],deg[maxn],bel[maxn];
bool vis[maxn],tag[maxn],used[maxn];
struct edge
{
    int to,nxt;
}e[maxn];
int head[maxn],edge_cnt=1;
void add(int from,int to)
{
    e[++edge_cnt]={to,head[from]},head[from]=edge_cnt;
}
void dfs(int x)
{
    tag[x]=true;
    for(int &i=head[x];i;i=e[i].nxt)
    {
        int y=e[i].to;
        if(vis[i]) continue;
        used[i]=vis[i]=vis[i^1]=true,dfs(y);
    }
}
int main()
{
    read(n);
    for(int i=1;i<=n;++i)
    {
        int x,y;
        read(x),read(y),y+=d;
        add(x,y),bel[i]=edge_cnt^1,add(y,x);
        deg[x]++,deg[y]++,p[++tot]=x,p[++tot]=y;
    }
    sort(p+1,p+tot+1),tot=unique(p+1,p+tot+1)-p-1;
    for(int i=1;i<=tot;++i)
    {
        int x=p[i];
        if(deg[x]&1)
        {
            if(las) add(las,x),add(x,las),las=0;
            else las=x;
        }
    }
    for(int i=1;i<=tot;++i)
        if(!tag[p[i]])
            dfs(p[i]);
    for(int i=1;i<=n;++i) putchar(used[bel[i]]?'b':'r');
    return 0;
}
```

---

