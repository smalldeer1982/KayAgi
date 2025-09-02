# [ABC241G] Round Robin

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc241/tasks/abc241_g

$ 1 $ から $ N $ までの番号がついた $ N $ 人が総当たり戦をしています。  
 すなわち、全ての組 $ (i,j)\ (1\leq\ i\ \lt\ j\ \leq\ N) $ について、人 $ i $ と人 $ j $ は $ 1 $ 回試合をするので、試合は合計で $ \frac{N(N-1)}{2} $ 試合行われます。  
 なお、試合は必ず一方が勝者、もう一方が敗者となり、引き分けとなることはありません。

既に $ M $ 試合が終了しており、$ i $ 試合目では人 $ W_i $ が人 $ L_i $ に勝ちました。

総当たり戦が終了したとき、単独優勝をする可能性のある人を列挙してください。  
 ただし単独優勝とは、その人の勝利数が、他のどの人の勝利数よりも多いことを言います。

## 说明/提示

### 制約

- $ 2\leq\ N\ \leq\ 50 $
- $ 0\leq\ M\ \leq\ \frac{N(N-1)}{2} $
- $ 1\leq\ W_i,L_i\leq\ N $
- $ W_i\ \neq\ L_i $
- $ i\neq\ j $ ならば、$ (W_i,L_i)\ \neq\ (W_j,L_j) $
- $ (W_i,L_i)\ \neq\ (L_j,W_j) $
- 入力は全て整数である

### Sample Explanation 1

人 $ 2,4 $ は単独優勝する可能性があり、人 $ 1,3 $ は単独優勝する可能性がありません。 なお、`4 2` などの出力は不正解となることに注意してください。

### Sample Explanation 2

単独優勝する可能性のある人がいないこともあります。

## 样例 #1

### 输入

```
4 2
2 1
2 3```

### 输出

```
2 4```

## 样例 #2

### 输入

```
3 3
1 2
2 3
3 1```

### 输出

```
```

## 样例 #3

### 输入

```
7 9
6 5
1 2
3 4
5 3
6 2
1 5
3 2
6 4
1 4```

### 输出

```
1 3 6 7```

# 题解

## 作者：Federico2903 (赞：4)

## 思路

鄙人写的第一篇网络流题解，有错误请指出 qwq。  
对于每一个选手 $i$，首先我们目前已经知道了 $m$ 场比赛的胜负情况，那么我们可以用贪心的思路让 $i$ 赢得剩下的所有他还没打的比赛，正确性显然，这样不会增加别人的分数。那么 $i$ 赢的条件是其他人的分数都不能比他高，设 $i$ 输了 $x$ 场，则他能得到的分数最大值 $mx_i $ 就是 $ n - 1 - x$。  
这一题的限制很多，如果我们单纯贪心让少的赢肯定是不行的，因为让别人赢会增加另外的人的分数，这时候考虑使用网络流。  
对于源点 $S$，我们把它和每一个比赛连起来，这条边的容量为 $1$，表示这场比赛能够得到一点分数，随后把这场比赛和参加这场比赛的两个队员分别连一条容量为 $1$ 的边，也就是说，这场比赛因为和源点之间的边容量为 $1$，所以他只能得到 $1$ 点分数，而比赛和两个队员间的边的容量为 $1$，表示这场比赛可以为两个队员中的一个提供一点分数，接着我们把所有的队员和汇点 $T$ 连接，除了队员 $i$ 连接 $T$ 的边的容量为 $mx_i$ 以外，其余的队员的边的容量为 $mx_i - 1$，表示其余的队员的分数都不能比 $i$ 高，最后我们从汇点和每个队员之间连接一条边，容量为该队员赢的次数，队员 $i$ 相应边的容量应为 $mx_i$，表示玩家初始的分数。  
建图的步骤就完成了，接下来使用 Dinic 算法计算最大流即可，如果最大流达不到 $n \times (n - 1) / 2$ 即所有比赛的数量，说明有的玩家赢得次数必大于 $i$ 导致流量无法传出，那么 $i$ 就必输，反之可以赢。细节在代码的注释内，可以细看。

**注意：`memcpy`, `memset` 的速度可能不如 `for` 循环。**

## AC 代码

```cpp
#define INF 1e12

struct edge{
	int nxt, v;
	ll c;
	//表示 一条连往v的边的容量为c
} e[10 * MAXN];

int cnt = 1, siz, then[MAXN], dis[MAXN];
//cnt, h, e用于链式前向星存边
//dis是Dinic算法分层的结果

queue<int> q;

void _add(int u, int v, ll c){e[++cnt]=(edge){then[u], v, c}; then[u]=cnt;}
void add(int u, int v, ll c){_add(u, v, c); _add(v, u, 0);}
//为了增广的反悔，需要加一条容量为0的反悔边

int S, T, cur[MAXN];
//S是网络的源点，T是网络的汇点，在这里S向所有未完成的比赛连c=1的边
//这里所有未完成的比赛向对应两位选手连c=1的边
//所有选手向汇点连c=INF的边

//Dinic算法通过BFS对原图分层，向层数高的方向增广来加速
bool dinic_bfs(){
	rep(i, 0, siz) dis[i] = -1;
	dis[S] = 0; q.push(S);
	//正常BFS
	while(!q.empty()){
		int t = q.front(); q.pop();
		for(int u = then[t]; u; u = e[u].nxt){
			if(e[u].c > 0 && dis[e[u].v] == -1){
				dis[e[u].v] = dis[t] + 1;
				q.push(e[u].v);
			}
		}
	}
	return dis[T] != -1;
	//如果无法访问T，图已经不连通了
}

ll dinic_dfs(int x, ll flow){
	if(x == T) return flow;
	ll rf = flow;
	for(int u = cur[x]; u; u = e[u].nxt){
		if(rf <= 0) break;
		//cout << e[u].v << " " << e[u].c << endl;
		cur[x] = u; //当前弧优化，Dinic每条边只会用于增广一次
		ll rf_x = e[u].c;
		if(rf_x > 0 && dis[e[u].v] > dis[x]){
			ll transfer = dinic_dfs(e[u].v, min(rf_x, rf));
			rf -= transfer;
			e[u].c -= transfer;
			e[u ^ 1].c += transfer;
			//此处应给反悔边加上transfer，方便撤销操作
			//警钟敲烂！！！cnt必须初始化为1才能这么写
		}
	}
	return flow - rf;
}

ll dinic(){
	ll ans = 0;
	while(dinic_bfs()){
		rep(i, 0, siz) cur[i] = then[i];
		ans += dinic_dfs(S, INF);
	}
	return ans;
}

int n, m, W[MAXN], mx[MAXN];
//W记录胜场数量 mx记录最大可以赢的场次的数量
bitset<60> vis[60];

signed main() {
	read(n, m);
	rep(i, 1, n) mx[i] = n - 1;
	//初始最大都是n-1
	siz = n * n + 2 * n;
	S = 0; T = siz;
	rep(i, 1, m){
		int x, y;
		read(x, y);
		W[x]++; mx[y]--;
		//x胜场+1，y最大7可赢-1（输了一场）
		vis[min(x, y)][max(x, y)] = 1;
		//标记这俩人比赛过了
	}
	rep(x, 1, n){
		int id = n; cnt = 1;
		rep(i, 0, siz) then[i] = 0;
		rep(i, 1, n){
			if(i == x) continue;
			rep(j, i + 1, n){
				if(j != x && (!vis[i][j])){
					id++;
					add(S, id, 1);
					add(id, i, 1);
					add(id, j, 1);//建边
				}
			}
		}
		rep(i, 1, n){
			if(i != x) add(S, i, W[i]);
			else add(S, i, mx[x]);
			if(i != x) add(i, T, max(mx[x] - 1, 0));
			else add(i, T, mx[x]);
		}
		//cout << "de:" << i << " " << mx[i] << endl;
		if(dinic() == n * (n - 1) / 2){
			print(x);
		}
	}
	return 0;
}
```

---

## 作者：kkxacj (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc241_g)

#### 前置知识

网络流。

#### 思路

首先把 $m$ 场已经进行的比赛处理一下，记录每个人 $i$ 最多能赢 $a_i$ 场，$win_i$ 为每个人已经赢了的场数，如果第 $i$ 个人要赢，那么其他的人赢得场数必须比他小。

考虑枚举赢家 $i$ ，每次建立一个源点 $s$ 和汇点 $t$，由 $s$ 所有没有进行的比赛且不是和第 $i$ 个人对决的比赛连一条边，然后它再和比赛的两个人连一个边，流量均为 $1$，表示一场比赛可以让其中一人的获胜次数加 $1$，然后对所有不是第 $i$ 个人向 $t$ 连一条边 $a_i - 1$ 的边，$s$ 向 $i$ 连一条流量为 $win_i$ 的边，表示每个人最多赢 $a_i - 1$ 场，如果 $a_i = 0$ 那第 $i$ 个人一定赢不了直接跳过。

跑完网络流，如果流量大小恰好为 $(n - 1) \times x - a_i$，那么说明每场比赛都在满足条件的情况下进行了，那就可行，直接输出答案即可。

代码用的 `Dinic`。

**code** 
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO
{
	template<typename T>
	void Read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void Read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],top,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++top]=48+x%10;while(top) pc(stk[top--]);}
}
using namespace IO;
struct w
{
	int to,nxt,z;
}a[20010];
int n,m,x,y,s,t,cnt,ma[60],b[60][60],now[10010],head[10010],dep[10010],win[60],tot,ans;
inline void add(int x,int y,int z)
{
	a[++cnt].to = y; a[cnt].z = z;
	a[cnt].nxt = head[x]; 
	head[x] = cnt;
	a[++cnt].to = x; a[cnt].z = 0;
	a[cnt].nxt = head[y]; 
	head[y] = cnt;
}
inline bool bfs()
{
	for(int i = s;i <= t;i++) dep[i] = 1e9;
	queue<int>q;
	q.push(s);
	dep[s] = 0,now[s] = head[s];
	while(!q.empty())
	{
		x = q.front();
		q.pop();
		for(int i = head[x];i;i = a[i].nxt)
		{
			y = a[i].to;
			if(a[i].z == 0 || dep[y] != 1e9) continue;
			now[y] = head[y];
			dep[y] = dep[x] + 1;
			q.push(y);
			if(y == t) return 1;
		}
	}
	return 0;
}
int dfs(int x,int sum)
{
	if(x == t || sum == 0) return sum;
	int res = 0;
	for(int i = now[x];i;i = a[i].nxt)
	{
		now[x] = i;
		if(a[i].z > 0 && dep[a[i].to] == dep[x] + 1)
		{
			int k = dfs(a[i].to,min(sum,a[i].z));
			if(k == 0) dep[a[i].to] = 1e9;
			a[i].z -= k,a[i ^ 1].z += k;
			sum -= k,res += k;
		}
	}
	return res;
} 
signed main()
{
	Read(n),Read(m); s = 0,t = n * n + n * 2;
	for(int i = 1;i <= n;i++) ma[i] = n - 1;//每个人初始最多赢n - 1次 
	for(int i = 1;i <= m;i++)
	{
		Read(x),Read(y);
		win[x]++; ma[y]--;
		b[x][y] = b[y][x] = 1;
	}
	for(int i = 1;i <= n;i++)
	{
		cnt = 1,tot = n;
		if(ma[i] == 0) continue;
		for(int j = s;j <= t;j++) head[j] = 0;
		for(int j = 1;j <= n;j++)
		{
			if(j == i) continue; //i要尽量多赢，所以有关他的比赛全部跳过 
			for(int z = j + 1;z <= n;z++)
			{
				if(b[j][z] || z == i) continue;
				add(s,++tot,1);
				add(tot,j,1); add(tot,z,1);
			}
		}
		for(int j = 1;j <= n;j++)
			if(j != i) add(s,j,win[j]),add(j,t,ma[i] - 1);
		ans = 0;
		while(bfs()) ans += dfs(s,1e9);
		if(ans == (n - 1) * n / 2 - ma[i]) print(i),pc(' ');
	}
	flush();
	return 0;
}
```

---

## 作者：DaydreamWarrior (赞：3)

[阅读体验可爱捏](https://rainlycoris.github.io/#/post/28)

## 分析

枚举第一名，假设以后的比赛该名玩家都获胜，然后判定是否合法。

数据范围很网络流，考虑最大流，流量代表得分，然后是建图：
- 源点和每场比赛连容量为 $1$ 的边
- 比赛如果有胜负就向胜者连边，否则就向参与比赛的两个人连边
- 设第一名的得分为 $w$，第一名向汇点连容量为 $w$ 的边，其余的人得分不能超过第一名，所以其余的人向汇点连容量为 $w-1$ 的边

由于总场次为 $\frac{n(n+1)}{2}$，如果最大流为 $\frac{n(n+1)}{2}$ 就说明每场比赛都分出了胜负，这种情况合法。

## 代码

```cpp
const int N = 3000,M = 10000;
int h[N],ne[M],e[M],w[M],idx;
int win[N][N];
int n,m,S,T;

void add(int a,int b,int c){
    w[idx] = c,e[idx] = b,ne[idx] = h[a],h[a] = idx++;
    w[idx] = 0,e[idx] = a,ne[idx] = h[b],h[b] = idx++;
}

namespace Dinic{
    int q[N],d[N],cur[N];

    bool bfs(){
        int hh = 0,tt = -1;
        memset(d,-1,sizeof(d));
        d[S] = 0,cur[S] = h[S];
        q[++tt] = S;
        while(hh<=tt){
            int u = q[hh++];
            for(int k=h[u];~k;k=ne[k]){
                int v = e[k];
                if(d[v]==-1&&w[k]){
                    d[v] = d[u]+1;
                    cur[v] = h[v];
                    if(v==T)
                        return true;
                    q[++tt] = v;
                }
            }
        }
        return false;
    }

    int find(int u,int lim){
        if(u==T)
            return lim;
        int flow = 0;
        for(int k=cur[u];~k&&flow<lim;k=ne[k]){
            cur[u] = k;
            int v = e[k];
            if(d[v]==d[u]+1&&w[k]){
                int t = find(v,min(w[k],lim-flow));
                if(!t)
                    d[v] = -1;
                w[k] -= t;
                w[k^1] += t;
                flow += t;
            }
        }
        return flow;
    }

    int dinic(){
        int r = 0,flow;
        while(bfs())
            if((flow=find(S,1e9)))
                r += flow;
        return r;
    }
}

signed main(){
    n = in(),m = in();
    for(int k=1;k<=m;k++){
        int a = in(),b = in();
        win[a][b] = 1;
        win[b][a] = 2;
    }
    S = 0,T = n+n*(n-1)/2+1;
    for(int k=1;k<=n;k++){
        memset(h,-1,sizeof(h));
        idx = 0;
        int cnt = n,wnt = 0;
        for(int j=1;j<=n;j++)
            for(int i=j+1;i<=n;i++){
                add(S,++cnt,1);
                if(win[i][j]){
                    if(win[j][i]==1){
                        if(j==k)
                            wnt++;
                        add(S,j,1);
                    }
                    else{
                        if(i==k)
                            wnt++;
                        add(S,i,1);
                    }
                }
                else{
                    if(j==k||i==k){
                        add(cnt,k,1);
                        wnt++;
                    }
                    else{
                        add(cnt,j,1);
                        add(cnt,i,1);
                    }
                }
            }
        for(int j=1;j<=n;j++)
            if(j==k)
                add(j,T,wnt);
            else
                add(j,T,wnt-1);
        if(Dinic::dinic()==n*(n-1)/2)
            out(k,' ');
    }
    return 0;
}
```

---

## 作者：NOI_Winner (赞：2)

解法：最大流。

先预处理每个人已经进行的比赛数和已经获胜的比赛数，分别设为 $a_i$ 和 $b_i$。

由于数据范围较小，我们考虑依次枚举每一个人，判断是否可能获胜。设当前的人为 $A$，我们直接假定剩余的与 $A$ 相关的比赛全部是 $A$ 赢，则 $A$ 赢的比赛数量为 $b_i+n-1-a_i$，则其他人最多赢的数量为 $b_i+n-2-a_i$。我们可以根据这个限制条件考虑如何建图。

建立源点与汇点，对于所有**未进行的且与 $A$ 无关的比赛**建立节点，同时对除 $A$ 以外的所有人建立节点。由源点向这些比赛的节点连一条容量为 $1$ 的边，由这些比赛的节点向比赛双方代表的节点分别连一条容量为 $1$ 的边，再由所有其他人代表的节点向汇点连一条容量为 $b_i+n-2-a_i$ 的边。求出最大流，若流量为这些比赛的数量，则说明所有比赛都可以合法进行，$A$ 可能成为赢家。

参考代码：
```cpp
#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

constexpr int maxn = 100, maxn2 = maxn * maxn, maxm2 = 6 * maxn2, inf = 0x3f3f3f3f;
int head[maxn2 + 5], vert[maxm2 + 5], nxt[maxm2 + 5], edge[maxm2 + 5], tot;
int d[maxn2 + 5], now[maxn2 + 5], c1[maxn + 5], c2[maxn + 5];
bool g[maxn + 5][maxn + 5];

struct match_t
{
	int x, y;
} a[maxn2 + 5];

inline void add_edge(int x, int y, int z)
{
	vert[++tot] = y;
	edge[tot] = z;
	nxt[tot] = head[x];
	head[x] = tot;
}

inline void add(int x, int y, int z)
{ add_edge(x, y, z); add_edge(y, x, 0); }

bool bfs()
{
	memset(d, 0, sizeof(d));
	queue<int> q; q.push(0);
	d[0] = 1; now[0] = head[0];
	
	while (q.size())
	{
		int x = q.front(); q.pop();
		for (int i = head[x]; i; i = nxt[i])
		{
			int y = vert[i], z = edge[i];
			if (z && !d[y])
			{
				d[y] = d[x] + 1;
				now[y] = head[y];
				q.push(y);
			}
		}
	}
	return d[1];
}

int dinic(int x, int flow)
{
	if (1 == x || !flow)
		return flow;
	
	int rest = flow;
	for (int& i = now[x]; i && rest; i = nxt[i])
	{
		int y = vert[i], z = edge[i];
		if (z && d[y] == d[x] + 1)
		{
			int k = dinic(y, min(z, rest));
			if (!k) continue;
			edge[i] -= k; edge[i ^ 1] += k;
			rest -= k;
		}
	}
	return flow - rest;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, m; cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		cin >> a[i].x >> a[i].y;
		g[a[i].x][a[i].y] = g[a[i].y][a[i].x] = true;
	}
	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			if (i == a[j].x || i == a[j].y)
				c1[i]++;
			if (i == a[j].x)
				c2[i]++;
		}
	
	for (int i = 1; i <= n; i++)
	{
		memset(head, 0, sizeof(head));
		tot = 1;
		
		int tot = n + 1;
		for (int j = 1; j <= n; j++)
			for (int k = j + 1; k <= n; k++)
				if (!g[j][k] && j != i && k != i)
				{
					add(0, ++tot, 1);
					add(tot, j + 1, 1);
					add(tot, k + 1, 1);
				}
		int lim = c2[i] + n - 2 - c1[i];
		bool flag = true;
		for (int j = 1; j <= n; j++)
			if (j != i)
			{
				if (lim - c2[j] < 0)
				{ flag = false; break; }
				add(j + 1, 1, lim - c2[j]);
			}
		
		if (!flag)
			continue;
		
		int maxflow = 0, flow;
		while (bfs())
			while ((flow = dinic(0, inf)))
				maxflow += flow;
		if (maxflow == tot - n - 1)
			cout << i << " ";
	}
	cout << endl;
	
	return 0;
}
```

---

## 作者：CodingOIer (赞：1)

## [ABC241G] Round Robin 题解

### 思路分析

一道很经典的网络流建模问题。

显然的，我们可以想到向每一个比赛创建一个容量为 $1$ 的边，这个比赛再向双方选手连容量为 $1$ 的边，再从每个选手向汇点连一条容量为 $mx - 1$ 的边，其中的 $mx$ 表示当前的选手最多的胜利场数。（不是那么严谨，仅供参考）

我猜你就没听懂……下面是更「形象化」且完整的表达：

赛委会 $S$ 向每局比赛 $C_i$ 分配了 $1$ 的分值，而每局比赛可以自由地将分数分给参加它的 $2$ 个选手之一。现在赛委会 $S$ 想要 $x$ 赢，但以前的比赛无法重来，便确定 $x$ 的接下来的比赛都会赢且最多的得分为 $mx_x$。所以只有剩下的选手 $P_1, P_2, P_3, \dots , P_{x - 1}, P_{x + 1}, \dots , P_{n - 1}, P_n$ 需要比赛，不需要建立关于 $x$ 的比赛。同时对于已经有了结果的比赛，赛委会 $S$ 直接将分值给到选手 $P_i$。而为了使 $x$ 是**非并列**冠军，所以每个选手在向记分员 $T$ 汇报时必须报出 $k_i < mx - 1$ 的分数。而新闻台在报道时会检查报来的总分 $\sum_{i=1}^{n}k_i + mx$ 是否等于应有的总分 $\frac{n \times (n - 1)}{2}$，如果相同则表示有方法让 $x$ 稳拿冠军，反之不行。 

赛委会时真的黑啊……

### 代码实现

这个题的细节挺多的。

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <utility>
#include <vector>
constexpr int MaxN = 5e3 + 5;
int idx;
int n, m, s, t;
int id[MaxN];
int cnt[MaxN];
int rev[MaxN][MaxN];
int last[MaxN];
int beat[MaxN];
int was_beat[MaxN];
std::queue<int> queue;
std::vector<int> use[MaxN];
std::vector<int> max[MaxN];
std::vector<int> link[MaxN];
std::map<std::pair<int, int>, bool> map;
inline void init()
{
    idx = 0;
    for (int i = 0; i < MaxN; i++)
    {
        use[i].clear();
        max[i].clear();
        link[i].clear();
    }
}
inline void add(int u, int v, int m, int k)
{
    use[u].push_back(k);
    max[u].push_back(m);
    link[u].push_back(v);
    rev[v][u] = link[u].size() - 1;
}
inline void add(int u, int v, int m)
{
    add(u, v, m, 0);
    add(v, u, m, m);
}
inline int new_node()
{
    idx++;
    return idx;
}
void bfs()
{
    queue.push(s);
    cnt[s] = 1;
    for (; !queue.empty();)
    {
        int u = queue.front();
        queue.pop();
        for (int i = 0; i < int(link[u].size()); i++)
        {
            int v = link[u][i];
            if (cnt[v] == 0 && max[u][i] - use[u][i] > 0)
            {
                cnt[v] = cnt[u] + 1;
                queue.push(v);
            }
        }
    }
}
int dfs(int u, int f)
{
    if (u == t || f == 0)
    {
        return f;
    }
    for (int i = last[u]; i < int(link[u].size()); i++)
    {
        last[u] = i;
        int v = link[u][i];
        if (cnt[u] + 1 == cnt[v])
        {
            int push = std::min(f, max[u][i] - use[u][i]);
            push = dfs(v, push);
            if (push > 0)
            {
                use[u][i] += push;
                use[v][rev[u][v]] -= push;
                return push;
            }
        }
    }
    return 0;
}
inline int Dinic()
{
    int res = 0;
    for (;;)
    {
        memset(cnt, 0, sizeof(cnt));
        bfs();
        if (cnt[t] == 0)
        {
            break;
        }
        memset(last, 0, sizeof(last));
        res += dfs(s, 1e9);
    }
    return res;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        beat[u]++;
        was_beat[v]++;
        map[{u, v}] = true;
        map[{v, u}] = true;
    }
    for (int x = 1; x <= n; x++)
    {
        init();
        s = new_node();
        t = new_node();
        int mx = (n - 1) - was_beat[x];
        for (int i = 1; i <= n; i++)
        {
            id[i] = new_node();
            if (i == x)
            {
                continue;
            }
            for (int j = i + 1; j <= n; j++)
            {
                if (j != x && !map[{i, j}])
                {
                    int contest = new_node();
                    add(s, contest, 1);
                    add(contest, id[i], 1);
                    add(contest, id[j], 1);
                }
            }
        }
        for (int i = 1; i <= n; i++)
        {
            if (i == x)
            {
                continue;
            }
            add(s, id[i], beat[i]);
            add(id[i], t, mx - 1);
        }
        if (Dinic() + mx == n * (n - 1) / 2)
        {
            printf("%d ", x);
        }
    }
    return 0;
}
```

---

## 作者：Avocadooo (赞：0)

考虑枚举每一个玩家判断是否可能满足获胜。

假设现在我们试图使得玩家 $ x $ 最终获胜，那么对于剩下的有 $ x $ 参与的比赛，我们可以贪心让 $ x $ 全部获胜，因为 $ x $ 获得这些比赛的胜利不会使得其他玩家分数增加。

考虑在已经知晓结果的 $ M $ 场比赛中 $ x $ 有 $ cnt $ 场落败。那么最后 $ x $ 的得分应为 $ n-1-cnt $，而其他人的得分应小于 $ n-1-cnt $。

限制条件很多，考虑使用网络流，每个流量表示一个得分。由源点向每个点连前 $ M $ 场比赛的得分数的容量的边。

同时对每一场未得到结果的比赛构建虚点，由源点向其连流量为 $ 1 $ 的边，向比赛双方 $ i,j $ 各连一条流量为 $ 1 $ 的边，即该比赛可以给 $ i $ 或 $ j $ 一个得分的贡献。由每个玩家向汇点连边，表示玩家的最大得分限制。

因为每个流量对应一个得分，而总共有 $ \frac{N(N-1)}{2} $ 场比赛。所以最大流应也为 $ \frac{N(N-1)}{2} $。若最大流小于该值，说明若使 $ x $ 最终胜利的方案不存在。



其它细节参考代码：

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N=1000005;
const int M=4000005;
namespace Chain_F{
	int h[N],cnt=1;
	struct Edge{int next,to;ll v;}e[M];
	void cr(int c,int d,ll w){e[++cnt]=(Edge){h[c],d,w};h[c]=cnt;}
	void AddEdge(int c,int d,ll w){cr(c,d,w),cr(d,c,0);}
	void ress(int s){cnt=1; for(int i=0;i<=s;i++) h[i]=0;}
}
using namespace Chain_F;
namespace Dinic{
	ll dis[N];
	int siz,s,t,cur[N];
	queue<int> q;
	void reset(int sz,int S,int T){siz=sz,s=S,t=T;}
	void bfs()
	{
		for(int i=0;i<=siz;i++) dis[i]=-1;
		dis[s]=0; q.push(s);
		while(!q.empty())
		{
			int r=q.front(); q.pop();
			for(int i=h[r];i;i=e[i].next)
			{
				int y=e[i].to;
				if(e[i].v==0 || dis[y]!=-1) continue;
				dis[y]=dis[r]+1;
				q.push(y);
	 		}
		}
	}
	ll dfs(int r,ll minn)
	{
		if(r==t) return minn;
		for(int i=cur[r];i;cur[r]=i,i=e[i].next)
		{
			int y=e[i].to;
			ll flow=e[i].v;
			if(flow==0 || dis[y]<=dis[r]) continue;
			ll d=dfs(y,min(flow,minn));
			if(d>0)
			{
				e[i].v-=d,e[i^1].v+=d;
				return d;
			}
		}
		return 0;
	}
	ll maxflow()
	{
		ll Ans=0,upd;
		while(bfs(),true)
		{
			if(dis[t]==-1) return Ans;
			for(int i=0;i<=siz;i++) cur[i]=h[i];
			while((upd=dfs(s,LLONG_MAX))>0) Ans+=upd;
		}
	}
}
int n,m,sign,maxx[N],w[N];
map<pair<int,int>,bool> p;
void ck(int x)
{
	sign=n;
	ress(Dinic::siz);
	int s=0,t=n*n+n+n;
	for(int i=1;i<=n;i++)
	{
		if(i==x) continue;
		for(int j=i+1;j<=n;j++)
		{
			if(j==x) continue;
			if(p[make_pair(i,j)]) continue;
			++sign;
			AddEdge(s,sign,1);
			AddEdge(sign,i,1),AddEdge(sign,j,1);
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(i!=x) AddEdge(s,i,w[i]);
		else AddEdge(s,i,maxx[x]);
		if(i!=x) AddEdge(i,t,max(0,maxx[x]-1));
		else AddEdge(i,t,maxx[x]);
	}
	Dinic::reset(t,s,t);
	if(Dinic::maxflow()==n*(n-1)/2) printf("%d ",x);
}
int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++) maxx[i]=n-1;
	for(int i=1,x,y;i<=m;i++) scanf("%d %d",&x,&y),w[x]++,maxx[y]--,p[make_pair(min(x,y),max(x,y))]=true;
	for(int i=1;i<=n;i++) ck(i);
}
```

---

