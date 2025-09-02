# Matvey's Birthday

## 题目描述

Today is Matvey's birthday. He never knows what to ask as a present so friends gave him a string $ s $ of length $ n $ . This string consists of only first eight English letters: 'a', 'b', $ ... $ , 'h'.

First question that comes to mind is: who might ever need some string? Matvey is a special boy so he instantly found what to do with this string. He used it to build an undirected graph where vertices correspond to position in the string and there is an edge between distinct positions $ a $ and $ b $ ( $ 1<=a,b<=n $ ) if at least one of the following conditions hold:

1. $ a $ and $ b $ are neighbouring, i.e. $ |a-b|=1 $ .
2. Positions $ a $ and $ b $ contain equal characters, i.e. $ s_{a}=s_{b} $ .

Then Matvey decided to find the diameter of this graph. Diameter is a maximum distance (length of the shortest path) among all pairs of vertices. Also, Matvey wants to find the number of pairs of vertices such that the distance between them is equal to the diameter of the graph. As he is very cool and experienced programmer he managed to solve this problem very fast. Will you do the same?

## 说明/提示

Consider the second sample.

The maximum distance is $ 2 $ . It's obtained for pairs $ (1,4) $ , $ (2,4) $ , $ (4,6) $ and $ (4,7) $ .

## 样例 #1

### 输入

```
3
abc
```

### 输出

```
2 1
```

## 样例 #2

### 输入

```
7
aaabaaa
```

### 输出

```
2 4
```

# 题解

## 作者：Karry5307 (赞：9)

### 题意

给定一个 $n$ 个点的图，每个点有颜色 $S_i$，$i$ 和 $j$ 有边当且仅当 $\vert i-j\vert=1$ 或 $S_i=S_j$。求这个无向图的直径，以及有多少对点的最短距离为直径。

$\texttt{Data Range:}2\leq n\leq 10^5$

### 题解

很有意思的题啊……

一个非常暴力的想法是求出任意点对之间的距离然后再统计，但是这样做无论是时间上还是空间上都是不行的，但是注意到颜色最多只有 $8$ 种，所以通过考虑利用颜色作为中转来得到所需要的。

设 $d_{i,j}$ 表示点 $i$ 到所有颜色为 $j$ 的点的最短路，再设 $g_{i,j}$ 代表所有颜色为 $i$ 的点到颜色为 $j$ 的点的最短路。这两个东西的求法，大概是先 BFS 求出不考虑传送情况下的直线距离，接下来考虑颜色 $i$ 到颜色 $j$ 是否在中转颜色处进行传送求出 $g$，最后反推出 $d$。

于是点 $i$ 到点 $j$ 的最短路很明显可以 $O(1)$ 求，即直接距离和通过中转颜色的距离取 min，但是不能直接枚举这个东西。

考虑数据分治。这里有一个结论：最短路径上一个颜色不可能出现超过 $2$ 次。如果出现 $3$ 次的话可以将第一次出现和最后一次出现的用传送代替，使得比所谓“最短路”要短，于是最短路长度不超过 $15$。

考虑先枚举右端点 $r$，再枚举左端点 $l$，如果 $r-l\leq 15$，那么可以直接暴力，复杂度是能接受的。

否则有一个性质：$g_{S_i,j}\leq d_{i,j}\leq g_{S_i,j}+1$。因为 $i$ 的颜色为 $S_i$，所以左边不等式成立。同时因为肯定存在一个颜色为 $i$ 的点有 $g_{S_i,j}=d_{i,j}$，如果这个点为 $i$ 那么 $g_{S_i,j}=d_{i,j}$，否则从 $i$ 走到这个点再走到 $j$ 有 $d_{i,j}=g_{S_i,j}+1$，右边不等式成立。

也就是说 $d_{i,j}-g_{S_i,j}\in\{0,1\}$，同时因为 $j$ 的范围很小所以可以高高兴兴压位。设 $m_i$ 的第 $j$ 位表示 $d_{i,j}-g_{S_i,j}$，在这种情况下点 $i$ 和点 $j$ 的最短路为
$\min(d_{i,k}+g_{S_j,k}+m_{j,k}+1)$。（因为直接距离大于 $15$ 所以不可能成为最短路）

暴力处理依旧不可行，注意到颜色不超过 $8$ 种，而 $m_i$ 的取值不超过 $2^8$ 种，所以可以开个桶存一下某个颜色与 $m_i$ 对应的位置数量，暴力统计即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51;
ll n,res,d;
li r;
ll x[MAXN],dist[MAXN][11],dis[11][11],c[11][511],msk[MAXN];
char ch[MAXN];
vector<ll>v[11];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline void upd(ll x,ll c)
{
	x==res?r+=c:1,x>res?res=x,r=c:1;
}
inline void bfs(ll x)
{
	ll top;
	queue<ll>q;
	for(register int i=1;i<=n;i++)
	{
		dist[i][x]=0x3f3f3f3f;
	}
	for(register int i:v[x])
	{
		q.push(i),dist[i][x]=0;
	}
	while(!q.empty())
	{
		top=q.front(),q.pop();
		if(dist[top-1][x]>dist[top][x]+1)
		{
			q.push(top-1),dist[top-1][x]=dist[top][x]+1; 
		}
		if(dist[top+1][x]>dist[top][x]+1)
		{
			q.push(top+1),dist[top+1][x]=dist[top][x]+1; 
		}
	}
}
int main()
{
	n=read(),scanf("%s",ch+1),memset(dis,0x3f,sizeof(dis));
	for(register int i=1;i<=n;i++)
	{
		x[i]=ch[i]&15,v[x[i]].push_back(i); 
	}
	for(register int i=1;i<=8;i++)
	{
		bfs(i),dis[i][i]=0; 
	} 
	for(register int k=1;k<=n;k++)
	{
		for(register int i=1;i<=8;i++)
		{
			for(register int j=1;j<=8;j++)
			{
				dis[i][j]=min(dis[i][j],dist[k][i]+dist[k][j]);
			}
		}
	}
	for(register int k=1;k<=8;k++)
	{
		for(register int i=1;i<=8;i++)
		{
			for(register int j=1;j<=8;j++)
			{
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]+1);
			}
		}
	}
	for(register int k=1;k<=8;k++)
	{
		for(register int i=1;i<=n;i++)
		{
			for(register int j=1;j<=8;j++)
			{
				dist[i][j]=min(dist[i][j],dist[i][k]+dis[k][j]+1);
			}
		}
	}
	for(register int i=1;i<=n;i++)
	{
		for(register int j=1;j<=8;j++)
		{
			msk[i]|=(dist[i][j]-dis[x[i]][j])<<j-1;
		}
	}
	for(register int j=1;j<=n;j++)
	{
		for(register int i=max(1,j-15);i<j;i++)
		{
			d=j-i;
			for(register int k=1;k<=8;k++)
			{
				d=min(d,dist[i][k]+dist[j][k]+1);
			}
			upd(d,1);
		}
	}
	for(register int i=17,j=1;i<=n;i++,j++)
	{
		c[x[j]][msk[j]]++;
		for(register int k=1;k<=8;k++)
		{
			for(register int l=0;l<256;l++)
			{
				if(c[k][l])
				{
					d=2e9;
					for(register int u=1;u<=8;u++)
					{
						d=min(d,dis[k][u]+dist[i][u]+((l>>u-1)&1)+1);
					}
					upd(d,c[k][l]);
				}
			}
		}
	}
	printf("%d %lld\n",res,r);
}
```

---

## 作者：Alex_Wei (赞：8)

> [CF718E Matvey's Birthday](https://www.luogu.com.cn/problem/CF718E)

称经过相同字符之间的边为 “传送”。对于两个不同位置 $x, y$，若 $x$ 与 $y$ 的最短路不包含传送，则它们之间距离为 $|x - y|$，否则设传送的字符为 $c$，则它们之间距离为 $f_{x, c} + f_{y, c} + 1$，其中 $f_{x, c}$ 表示 $x$ 到某个含有字符 $c$ 的位置的最短路。

因此，$dist(x, y)$ 可表示为 $\min(|x - y|, f_{x, c} + f_{y, c} + 1)$。

因为最短路不可能包含三个相同字符的点，所以直径不超过 $2k - 1 = 15$。对于每个位置 $i$ 及其相邻 $15$ 个位置，可直接枚举求出最短路。不妨先假设最小值取到后者，最后处理最小值取到前者的答案。

定义 $dist'(x, y) = \min\limits_{c} f_{x, c} + f_{y, c} + 1$。问题转化为求 $dist'$ 的最大值以及取到最大值的点对数量

进一步地，我们发现 $f_{x, c}$ 不会超过从某个字符为 $a_x$ 的位置 $p$ 到字符为 $c$ 的位置的最短路最小值 $g_{a_x, c}$ 加 $1$，直接从 $x$ 传送到 $p$ 即可。

考虑对所有不相等的颜色对 $x, y$ 求答案。枚举所有 $c$ 并求出 $v = \min g_{x, c} + g_{y, c} + 1$。根据上述结论，任意 $a_p = x$ 且 $a_q = y$ 的 $dist'(p, q)$ 落在 $[v, v + 2]$ 区间内。

考虑 $dist'(p, q) = v$ 的充要条件，可知为存在字符 $c$ 使得 $f_{p, c} = g_{x, c}$，$f_{q, c} = g_{y, c}$ 且 $v = g_{x, c} + g_{y, c} + 1$。为此，对于第一个条件，对每个位置 $p$ 预处理使得 $f_{p, c} = g_{a_p, c}$ 的字符集 $T_p$，对于最后一个条件，预处理满足条件的字符集 $S$。转化后，充要条件可写为 $T_p \cap T_q \cap S \neq \varnothing$。预处理 $h_{c, S}$ 表示使得 $a_p = c$ 且 $T_p = S$ 的 $p$ 的数量，只需求 $h_x$ 和 $h_y$ 做与卷积后与 $S$ 有交的下标的值之和。预处理复杂度可忽略不计，瓶颈在于对每个 $x, y$ 都做一遍与卷积，时间复杂度 $2 ^ kk^ 3$。

类似地，考虑 $dist'(p, q) = v + 1$ 的充要条件，发现限制较多。不妨考虑 $dist'(p, q) = v + 2$ 的充要条件。那么首先 $T_p$，$T_q$ 与 $S$ 不能有交，若有交则 $dist'(p, q)\leq v + 1$。再考虑使得 $v + 1 = g_{x, c} + g_{y, c} + 1$ 的字符集 $S'$，则 $T_p \cap T_q$ 与 $S'$ 不能有交，否则 $dist'(p, q) \leq v + 1$。换句话说，将使得 $dist'(p, q) \leq v + 1$ 的条件取反就得到了 $dist'(p, q) = v + 2$ 的条件，即 $p\to q$ 推出 $\lnot q\to \lnot p$，而 $dist'(p, q) > v + 1$ 则 $dist'(p, q)$ 只能等于 $v + 2$，读者可以从这个角度体会得到充要条件的动机。类似上一部分做与卷积即可。

最后不要忘记枚举相距不超过 $15$ 的点对，检查是否 $|x - y|$ 比 $\min f_{x, c} + f_{y, c} + 1$ 更小。

时间复杂度 $\mathcal{O}(nk ^ 2 + 2 ^ kk ^ 3)$，显然优于标算 $n 2 ^ kk ^ 2$。前半部分可以做到 $2 ^ k k ^ 2$，有时间再来研究。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
#define fi first
#define se second
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
inline int read() {
  int x = 0;
  char s = getchar();
  while(!isdigit(s)) s = getchar();
  while(isdigit(s)) x = x * 10 + s - '0', s = getchar();
  return x;
}
inline void print(int x) {
  if(x < 0) return putchar('-'), print(-x);
  if(x >= 10) print(x / 10);
  putchar(x % 10 + '0');
}
bool Mbe;
constexpr int K = 1 << 8;
constexpr int N = 1e5 + 5;
constexpr int inf = 0x3f3f3f3f;
char s[N];
vector<int> buc[8];
ll ans[18], h[8][K];
int n, col[N], T[N], f[N][8], g[8][8];
void FWT(ll *f, int op) {
  for(int k = 1; k < K; k <<= 1)
    for(int i = 0; i < K; i += k << 1)
      for(int j = 0; j < k; j++)
        f[i | j] += op * f[i | j | k];
}
bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  ios::sync_with_stdio(0);
  cin >> n >> s + 1;
  memset(f, 0x3f, sizeof(f));
  memset(g, 0x3f, sizeof(g));
  for(int i = 1; i <= n; i++) buc[col[i] = s[i] - 'a'].push_back(i);
  for(int c = 0; c < 8; c++) {
    g[c][c] = 0;
    if(buc[c].empty()) continue;
    ans[1] += 1ll * buc[c].size() * (buc[c].size() - 1) / 2;
    queue<int> q;
    for(int it : buc[c]) f[it][c] = 0, q.push(it);
    while(!q.empty()) {
      int t = q.front();
      q.pop();
      if(g[col[t]][c] == inf) {
        g[col[t]][c] = f[t][c];
        for(int it : buc[col[t]]) {
          if(f[it][c] != inf) continue;
          f[it][c] = f[t][c] + 1, q.push(it);
        }
      }
      for(int d : {-1, 1}) {
        if(t + d < 1 || t + d > n) continue;
        if(f[t + d][c] == inf) f[t + d][c] = f[t][c] + 1, q.push(t + d);
      }
    }
  }
  for(int i = 1; i <= n; i++) {
    for(int j = 0; j < 8; j++)
      if(f[i][j] == g[col[i]][j])
        T[i] |= 1 << j;
    h[col[i]][T[i]]++;
  }
  for(int i = 0; i < 8; i++) FWT(h[i], 1);
  for(int x = 0; x < 8; x++)
    for(int y = x + 1; y < 8; y++) {
      if(buc[x].empty() || buc[y].empty()) continue;
      int v = N;
      ll v0 = 0, v1 = 1ll * buc[x].size() * buc[y].size(), v2 = 0;
      for(int c = 0; c < 8; c++) v = min(v, g[x][c] + g[y][c] + 1);
      int S = 0, _S = 0;
      for(int c = 0; c < 8; c++)
        if(g[x][c] + g[y][c] + 1 == v) S |= 1 << c;
        else if(g[x][c] + g[y][c] + 1 == v + 1) _S |= 1 << c;
      static ll a[K], b[K];
      memset(a, 0, sizeof(a));
      for(int i = 0; i < K; i++) a[i] = h[x][i] * h[y][i];
      FWT(a, -1);
      for(int i = 0; i < K; i++) if(i & S) v0 += a[i];
      memset(a, 0, sizeof(a));
      memset(b, 0, sizeof(b));
      for(int it : buc[x]) if(!(T[it] & S)) a[T[it]]++;
      for(int it : buc[y]) if(!(T[it] & S)) b[T[it]]++;
      FWT(a, 1), FWT(b, 1);
      for(int i = 0; i < K; i++) a[i] *= b[i];
      FWT(a, -1);
      for(int i = 0; i < K; i++) if(!(i & _S)) v2 += a[i];
      v1 -= v0 + v2;
      ans[v] += v0;
      ans[v + 1] += v1;
      ans[v + 2] += v2;
    }
  for(int i = 1; i <= n; i++) {
    for(int j = i + 1; j <= min(n, i + 15); j++) {
      int v = N;
      for(int c = 0; c < 8; c++) v = min(v, f[i][c] + f[j][c] + 1);
      if(j - i < v) ans[v]--, ans[j - i]++;
    }
  }
  for(int i = 15; i; i--) if(ans[i]) cout << i << " " << ans[i] << "\n", exit(0);
  cerr << TIME << " ms\n";
  return 0;
}
/*
2022/9/5
author: Alex_Wei
start coding at 20:16
finish debugging at 21:47
*/
```

---

## 作者：ghj1222 (赞：7)

我们先预处理一个数组`dis[i][j]`代表位置i到任意一个字母是j的位置(转化为图中即为点j1)需要的时间

先只处理序列上的，把所有字符为j的点作为起点开始bfs即可

然后我们再预处理一个数组`dch[i][j]`代表字符是i的任意位置到字符是j的任意位置需要的时间(转化为图中为点i2到j1的最短路)

显然`dch[i][j]=min(dis[k][i]+dis[k][j])`，枚举k更新即可

我们更新完成后可以再跑一遍floyd，不过是`dch[i][j]=min(dch[i][j],dch[i][k]+1+dch[k][j])`。那个1是因为从任意一个x1到x2都需要1个时间。

然后我们可以用dch数组去更新dis数组了：`dis[i][j]=min(dis[i][j],dis[i][k]+1+dch[k][j])`。

这样我们就能推出任意两个点i,j之间的最短路，设点与点之间的最短路为`d[i][j]`。

那么`d[i][j]=min(|i-j|,dis[i][k]+dis[k][j]+1)`。

本题N是10万，肯定不能暴力枚举啦。我们先枚举右端点，设为i。

由于最多有8个字母，每个字母在最短路上最多出现两次（如果出现多次，这就一定不是最短路），所以最短路最长为15。

对于`|i-j|<=15`的情况，我们可以暴力处理，复杂度O(N)，即O(能过)。

对于`|i-j|>15`的情况，显然前面的`|i-j|`一定不会有贡献。那么对于一个左端点j，有：

`d[i][j]=min(dis[i][k]+dis[k][j]+1)`。

我们这里有一个性质：`dch[a[i]][k]<=dis[i][k]<=dch[a[i]][k]+1`。你可以这么理解：从i到k中间需要经过一些传送，你可以直接在i点走到了字符为k的点（耗费为`dch[a[i]][k]`)，也可以在i点通过传送到相同字符的位置再走到字符为k的点（耗费为`dch[a[i]][k]+1`）。我们设`mask[i][k]`为`dis[i][k]-dch[a[i]][k]`，显然它不是0就是1。由于最多有8种字符，所以可以把每个位置的`mask[i]`压成一个0到255的数，下面我们称为掩码。那么我们的最短路可以写成：`d[i][j]=min(dis[i][k]+dch[a[j]][k]+mask[j][k]+1)`。这样子我们i和i前面的位置j的最短路与j无关了，**只与j位置的字符和掩码有关**。所以可以**批量处理前面相同字符和掩码的位置**。而字符和掩码组成最多有2048种，在可以处理的数量级内。我们处理一个`cnt[ch][mask]`表示当前[1,i-16]区间内，字符为ch且掩码为mask的位置的数量。每次i向右移动的时候更新一个i-16，然后枚举这2048种状态统计计数即可。

这道题确实不好想，这里还是献上我的丑陋的代码吧。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
char a[100010];
vector<int> points[10];
int dis[100010][10];//点到某字符的距离
int dch[10][10];//字符之间的距离
int cnt[10][300];//字符是c且掩码为Mask的位置有多少个
int mask[100010];//二进制掩码

int ans;
long long ans2;

void update(int x, int tot)
{
	if (x == ans)
		ans2 += tot;
	if (x > ans)
	{
		ans = x;
		ans2 = tot;
	}
}

void bfs(int ch)
{
	queue<int> q;
	for (vector<int>::iterator i = points[ch].begin(); i != points[ch].end(); i++)
		q.push(*i);
	for (int i = 1; i <= n; i++)
		if (a[i] == ch + 96)
			dis[i][ch] = 0;
		else
			dis[i][ch] = 0x3f3f3f3f;
	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		if (dis[x - 1][ch] == 0x3f3f3f3f)
		{
			dis[x - 1][ch] = dis[x][ch] + 1;
			q.push(x - 1);
		}
		if (dis[x + 1][ch] == 0x3f3f3f3f)
		{
			dis[x + 1][ch] = dis[x][ch] + 1;
			q.push(x + 1);
		}
	}
}

void add(int pos)
{
	cnt[a[pos] - 96][mask[pos]]++;
}

int main()
{
	//input
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf(" %c", &a[i]);
		points[a[i] - 96].push_back(i);
	}
	
	//bfs，求出每个点到某种字符的距离（先求直接的）
	for (int ch = 1; ch <= 8; ch++)
		bfs(ch);
	
	//求每种字符之间的距离
	//先初始化
	memset(dch, 0x3f, sizeof(dch));
	for (int i = 1; i <= 8; i++)
		dch[i][i] = 0;
	//枚举经过的位置和初始字符（考虑floyd）
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++)
				dch[i][j] = min(dch[i][j], dis[k][i] + dis[k][j]);
	
	//类似floyd
	for (int k = 1; k <= 8; k++)
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++)
				dch[i][j] = min(dch[i][j], dch[i][k] + dch[k][j] + 1);
	
	//再去更新点到字符的距离
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= 8; j++)
			for (int ch = 1; ch <= 8; ch++)
				dis[i][ch] = min(dis[i][ch], dis[i][j] + dch[j][ch] + 1);
	
	//求出掩码mask(或者叫做mark)
	for (int i = 1; i <= n; i++)
		for (int ch = 1; ch <= 8; ch++)
			mask[i] |= (dis[i][ch] - dch[a[i] - 96][ch]) << (ch - 1);
	
	//先暴力做区间长度小于等于15的情况
	for (int r = 1; r <= n; r++)
		for (int l = max(1, r - 15); l < r; l++)
		{
			int minf = r - l;
			for (int ch = 1; ch <= 8; ch++)
				minf = min(minf, dis[l][ch] + dis[r][ch] + 1);
			update(minf, 1);
		}
	
	//然后是大于15的情况,i是右端点
	for (int i = 17, j = 1; i <= n; i++, j++)
	{
		//j是i左边距离为15的那个点
		add(j);
		//枚举字符和掩码
		for (int ch = 1; ch <= 8; ch++)
			for (int st = 0; st <= 255; st++)
			{
				if (cnt[ch][st])
				{
					int fuck = 0x3f3f3f3f;//枚举中转字符
					for (int sb = 1; sb <= 8; sb++)
						fuck = min(fuck, dch[ch][sb] + dis[i][sb] + (((st)>>(sb-1))&1) + 1);
					update(fuck, cnt[ch][st]);
				}
			}
		
	}
	printf("%d %lld\n", ans, ans2);
	return 0;
}
```



---

## 作者：Arghariza (赞：5)

不难发现答案 $\le 15$，极限的情况大概就是 $aabbcc\cdots gghh$，此时跳一步和走一步等效。

这启示我们固定点 $i$，统计 $d(i,j)=D,j<i$ 的 $j$ 的个数，拆成 $i-j\le 15$ 的贡献和 $i-j>15$ 的贡献。

为了方便，以下称从 $i$ 到 $i+1$ 或 $i-1$ 为「走」，在相同颜色的点之间移动为「跳」。对于既可能拥有「走」操作有可能拥有「跳」操作的移动过程，称之为「跑」。

#### $i-j\le 15$ 的贡献

一种情况是 $j$ 直接走到 $i$，步数为 $i-j$。

另一种情况是 $j$ 先跑到一个点 $k$，然后 $k$ 再跳到和它相同颜色的点 $l$，再由 $l$ 跑到 $i$，即 $j\to k\to l\to i$。

为了方便，预处理出 $f_{i,c}$ 表示 $i$ 跑到任意一个颜色为 $c$ 的点的最短距离，$g_{c_1,c_2}$ 为任意两个颜色分别为 $c_1,c_2$ 的点之间，$c_1$ 跑到 $c_2$ 的最短距离。由于边权相同，可以 bfs 求出。

于是 $j\to k\to l\to i$ 的最小步数为 $\min\limits_{c}\{f_{j,c}+f_{i,c}+1\}$。

两种情况取 $\min$ 即可算出 $j\to i$ 的最短距离。枚举 $i$，枚举前 $15$ 个数即可，复杂度 $O(kn)$，$k=15$。

#### $i-j>15$ 的贡献

只有可能是 $\min\limits_c\{f_{j,c}+f_{i,c}+1\}$。但是无法枚举所有的 $j$ 取 $\min$。

发现 $f_{i,c}$ 要么是 $g_{a_i,c}$ 要么是 $g_{a_i,c}+1$，而颜色数很少，考虑状态压缩。把每个点压成二元组 $(a_i,\text{st})$，$\text{st}$ 为 $8$ 位二进制数，第 $c$ 位 $\text{st}(c)$ 表示 $f_{i,c}$ 为 $g_{a_i,c}$ 或者 $g_{a_i,c}+1$。

对于相同的二元组 $(x,\text{st})$，映射到不同的点。但是这些点到 $i$ 的距离都是相同的，为 $\min\limits_c\{f_{i,c}+1+g_{x,c}+\text{st}(c)\}$，可以一起统计进答案里面。复杂度降为 $O(p^22^pn)$，$p=8$，稍微剪枝就过了。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

namespace vbzIO {
	char ibuf[(1 << 20) + 1], *iS, *iT;
//	#if ONLINE_JUDGE
//	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
//	#else
	#define gh() getchar()
//	#endif
	#define rd read
	#define wr write
	#define pc putchar
	#define pi pair<int, ll>
	#define mp make_pair
	#define fi first
	#define se second
	#define pb push_back
	#define ins insert
	#define era erase
	inline int read () {
		char ch = gh();
		int x = 0;
		bool t = 0;
		while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? ~(x - 1) : x;
	}
	inline void write(ll x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}
using vbzIO::read;
using vbzIO::write;

const int N = 1e5 + 100;
const int T = (1 << 8) + 100;
const int inf = 0x3f3f3f3f;
int n, a[N], vs[N], vc[10], f[N][10], g[10][10], ct[10][T];
char s[N];
vector<int> c[N];
pi ans;

void chk(pi &x, pi y) {
	if (y.fi > x.fi) x = y;
	else if (y.fi == x.fi) x.se += y.se;
}

void init() {
	memset(f, inf, sizeof(f));
	memset(g, inf, sizeof(g));
	for (int i = 0; i <= 7; i++) {
		queue<int> q;
		for (int j = 0; j <= 7; j++) vc[j] = 0;
		for (int j = 1; j <= n; j++) vs[j] = 0;
		for (int j : c[i]) 
			q.push(j), f[j][i] = 0, vs[j] = 1;
		g[i][i] = 0, vc[i] = 1;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			if (u > 1) { 
				int v = u - 1;
				if (!vs[v]) 
					f[v][i] = f[u][i] + 1, vs[v] = 1, q.push(v);
			}
			if (u < n) {
				int v = u + 1;
				if (!vs[v]) 
					f[v][i] = f[u][i] + 1, vs[v] = 1, q.push(v);
			}
			if (vc[a[u]]) continue;
			vc[a[u]] = 1, g[a[u]][i] = f[u][i];
			for (int v : c[a[u]]) 
				if (!vs[v]) 
					f[v][i] = f[u][i] + 1, vs[v] = 1, q.push(v);
		}
	}
}

int st(int x) {
	int res = 0;
	for (int i = 0; i <= 7; i++) 
		if (f[x][i] == g[a[x]][i] + 1) res |= (1 << i);
	return res;
}

int main() {
	n = rd(), scanf("%s", s + 1);
	for (int i = 1; i <= n; i++) 
		a[i] = s[i] - 'a', c[a[i]].pb(i);
	init();
	for (int i = 2; i <= n; i++) {
		for (int j = max(1, i - 15); j <= i - 1; j++) {
			int tp = i - j;
			for (int k = 0; k <= 7; k++) tp = min(tp, f[i][k] + f[j][k] + 1);
			chk(ans, mp(tp, 1));
		}
	}
	for (int i = 17; i <= n; i++) {
		ct[a[i - 16]][st(i - 16)]++;
		for (int j = 0; j <= 7; j++) {
			for (int k = 0; k <= (1 << 8) - 1; k++) {
				if (!ct[j][k]) continue;
				int w = n + 1;
				for (int l = 0; l <= 7; l++) 
					w = min(w, f[i][l] + g[j][l] + ((k >> l) & 1) + 1);
				chk(ans, mp(w, ct[j][k]));
			}
		} 
	}
	wr(ans.fi), pc(' '), wr(ans.se);
	return 0;
}
```

---

## 作者：Pengzt (赞：3)

# Matvey's Birthday

[题目链接](https://www.luogu.com.cn/problem/CF718E)。[cnblogs](https://www.cnblogs.com/Pengzt/p/18665654)。

### Problem

给定一个仅包含 `a`~`h` 的字符串（八个字符）。

有一个 $n$ 个结点的无向图，编号为 $0$ 到 $n−1$。结点 $i$ 与结点 $j$ 间有边相连当且仅当 $|i-j|=1$ 或 $S_i=S_j$。

求这个无向图的直径和有多少对点间的最短距离与直径相同。

数据范围：$2 \le n \le 10^5$。

### Sol

不难发现，直径一定不会超过 $15$。因为我可以通过传送后走一步来切换字符。然后这个东西不是很好贪心，$n$ 又特别小，不难想到 DP。

不妨定义 $f_{i, j}$ 表示点 $i$ 走到第 $j$ 个颜色的最短距离。这个东西是很好处理的，用类似于 BFS 的东西即可得到。

现在讨论直径，由于直径是 $\max\limits_{i, j \in [1, n] \cap \mathbb Z}\min(|i - j|, \min\limits_c f_{i, c} + f_{j, c} + 1)$。经过我们的转化，时间复杂度由 $\mathcal{O}(n^2)$ 变为了 $\mathcal{O}(n^2)$！。

里面的 $\min$ 是很不好的，由于答案一定不会超过 $15$，可以把 $|i - j| \le 15$ 的二元组 $(i, j)$ 单独拉出来跑。然后现在就只需要求 $\max\limits_{i, j \in [1, n] \cap \mathbb Z} \min\limits_c f_{i, c} + f_{j, c} + 1$ 了。这个东西乍一看并不好做，但是发现传送只对颜色有要求，所以对于 $a_i$ 相同的点，$f_{i, c}$ 至多只会有两个值，因为如果不行的话，一定可以传送一次到达。如果记 $g_{i, j}$ 表示颜色 $i$ 走到颜色 $j$ 的最小距离（$g$ 可以在求 $f$ 时一起得到），则显然有 $g_{a_i, j} \le f_{i,j} \le g_{a_i, j} + 1$。里面的 $\min$ 不好拆掉，于是考虑枚举 $i$ 算 $j$ 的答案。然后不妨令 $h_{i, j} = g_{a_i, j} - f_{i, j}$。然后由于 $h$ 的值域很小，可以把后面一维压起来，变为 $h_{i}$。发现相同的 $(a_i, h_i)$ 的答案，无论 $c, j$ 是多少，答案一定是一样的。于是可以枚举 $a_i, h_i, c, j$ 来进行统计。$h_i$ 的值有 $\mathcal{O}(2^c)$ 种，所以时间复杂度为 $\mathcal{O}(nc^22^c)$。空间 $\mathcal{O}(nc + c2^c)$，这是因为我需要知道之前 $(a_i, h_i)$ 出现了多少次，这需要开一个桶。

### Code

[评测记录](https://codeforces.com/contest/718/submission/300475008)。

---

## 作者：born_to_sun (赞：3)

下文中 $k$ 指字母种类数，颜色代指字母。

怎么题解都是跟 $2^k$ 有关的复杂度，来个 bitset。

直接从每个点开始跑最短路，复杂度 $O(n^2)$，不能接受。

我们有一个这样的思路：
+ 枚举颜色 $i$。
+ 设颜色为 $i$ 的点组成的集合为 $S$，将 $S$ 中的点初始距离设为 $1$，跑一遍最短路。
+ 枚举一个颜色为 $i$ 的点 $u$，将它的初始距离改为 $0$，并且快速更新它对答案的影响。

如果我们能做到上述这些步骤，就只用跑 $k$ 次最短路。

设点 $v$ 的最短路为 $dis_v$。

考虑点 $u$ 的初始距离从 $1$ 变为 $0$，那么所有 $dis_v$ 至多减少 $1$。并且我们发现 $dis_v$ 减少 $1$ 当且仅当在最短路 DAG 上 $u$ 可以到达 $v$。

两点可达性问题可以用 bitset 解决，处理出每个点和 $S$ 中的点的可达性。

设 $mx=\max{\{dis_v\}}$，如果所有 $dis_v=mx$ 的点都能够到达所有 $S$ 中的点，说明最长的最短路为 $mx-1$，统计出所有 $dis_v=mx$ 的点数量，以及满足 $dis_v=mx-1$ 的每个 $v$ 与 $S$ 中的多少点不可达，即可求出答案。

否则，最长的最短路为 $mx$，统计 $dis_v=mx$ 的每个 $v$ 与 $S$ 中的多少点不可达。

由于空间开不下，需要对 bitset 分块处理，分 $7$ 块即可。

复杂度为 $O({n^2\over w}+nk)$，能够解决更大的 $k$，部分优于其他题解复杂度。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
const int N=1e5+500;
const int inf=1e18;
const int B=N/64/6;
int n;
char a[N];
int dis[N];
vector<int> c[N];
int head[N],len;
struct E{
	int to,next,w,u;
}e[N*10];
void add(int u,int v,int w){e[++len]=E{v,head[u],w,u};head[u]=len;}
int vis[N];
int mx,ans;
int sk[N],top,to[N];
int bfs(char x){
	memset(vis,0,sizeof(vis));
	memset(dis,63,sizeof(dis));
	deque<int> q;
	for(int i=1;i<=n;i++){
		if(a[i]==x) dis[i]=1,q.push_front(i);
	}
	if(!q.size()) return 0;
	while(q.size()){
		int u=q.front();q.pop_front();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].next){
			int v=e[i].to,w=e[i].w;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				if(w) q.push_back(v);
				else q.push_front(v);
			}
		}
	}return 1;
}
ull f[N][B];
void cal(int now,int res){
	if(mx<now) mx=now,ans=res;
	else if(mx==now) ans+=res;
}
void get(int &F,int &res,int bs,int x){
	int top=n+150;
	for(int T=0;;T++){
		int L=T*B,R=min(((int)c[x].size()-1)>>6,(T+1)*B-1);
		if(L>R) break;
		int up=R-L+1;
		int now=0;
		for(int i=1;i<=n+150;i++){
			for(int j=0;j<up;j++) f[i][j]=0;
		}
		for(int i=L<<6;i<min((int)c[x].size(),(R+1)<<6);i++){
			now++;
			int u=c[x][i];
			int x=i-(L<<6);
			f[u][x>>6]|=1ull<<(x&63);
		}
		for(int i=1;i<=top;i++){
			int u=sk[i];
			if(dis[u]>inf) continue;
			for(int i=head[u];i;i=e[i].next){
				int v=e[i].to,w=e[i].w;
				if(dis[v]==dis[u]+w){
					for(int k=0;k<up;k++) f[v][k]|=f[u][k];
				}
			}
		}
		for(int i=1;i<=n;i++){
			if(dis[i]==bs){
				int sum=0;
				for(int k=0;k<up;k++){
					sum+=__builtin_popcountll(f[i][k]);
				}
				if(sum!=now) F=0,res+=now-sum;
			}
		}
	}
}
bool cmp(int x,int y){
	return dis[x]==dis[y]? x>y: dis[x]<dis[y];
}
void solve(char x){
	if(!bfs(x)) return;
	for(int i=1;i<=n+150;i++) sk[i]=i;
	sort(sk+1,sk+1+n+150,cmp);
	int mx=0;
	for(int i=1;i<=n;i++) mx=max(mx,dis[i]);
	
	int F=1,res=0,cnt=0;
	get(F,res,mx,x);
	for(int i=1;i<=n;i++){
		if(dis[i]==mx) cnt++;
	}
	if(!F) cal(mx,res);
	else{
		res+=cnt*(int)c[x].size();
		get(F,res,mx-1,x);
		cal(mx-1,res);
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>(a+1);
	for(int i=1;i<=n;i++) c[a[i]].push_back(i);
	for(int i=1;i<=n;i++){
		if(i!=1) add(i,i-1,1);add(i-1,i,1);
		add(i,n+a[i],1);
		add(n+a[i],i,0);
	}
	for(int i=0;i<18;i++){
		solve(i+'a');
	}
	cout<<mx<<' '<<ans/2;
	return 0;
}
```

---

## 作者：happybob (赞：1)

题意：

给定一个仅包含 `a` 到 `h` 的字符串，下标从 $0$ 开始。

有一个 $n$ 个结点的无向图，点的编号为 $0$ 到 $n-1$，边权都为 $1$。结点 $i$ 与结点 $j$ 间有边相连当且仅当 $|i-j|=1$ 或 $S_i=S_j$。

求这个无向图的直径和有多少对点间的最短距离与直径相同。

直径定义为任意两点之间最短路的最大值。

$2 \leq n \leq 10^5$，时限 $2$ 秒，空间限制 $256$ MB。

解法：

很好的性质观察题，完全无法独立思考。

我们不妨先考虑两点之间的最短路怎么刻画。对于点 $i$ 与 $j$，我们希望求出 $i$ 到 $j$ 的最短路。不难发现如果将最短路的点对应字符写下，不可能出现某种字符出现次数大于等于 $3$ 次，否则这就不是最短路了。更进一步，最短路不超过 $15$。

我们首先求出 $f_{i,j}$ 表示从 $i$ 号点出发，到达某个字符为 $j$ 的点的最短距离。这个可以对每种字符做多起点 BFS，这部分复杂度 $O(n \left| \Sigma \right|^2)$。然后我们考虑处理出 $g_{i,j}$ 表示某个字符为 $i$ 的点到某个字符为 $j$ 的点的最短路最小值。这个直接通过 $f$ 就可求出。

现在我们其实已经可以求出点 $i$ 到 $j$ 的最短路了。$\operatorname{dis}(i,j)=\min(|i-j|,\min \limits_{k=1}^8 f_{i,k}+f_{j,k}+1)$。两部分分别表示只经过相邻两点的边，或者从某个字符中转。

这样我们得到了一个 $O(n^2|\Sigma|)$ 的做法，直接枚举 $i,j$ 即可。这个做法复杂度瓶颈在于两点之间最短路和其 $f$ 值有关，不容易直接处理。

做到这里有些困难了，比较考察注意力。注意到对于 $i,j$，必有 $g_{a_i,j} \leq f_{i,j} \leq g_{a_i,j}+1$。然后对于一个 $i$，所有 $(a_j,S)$ 相同的 $j$ 一起计算，$S$ 为一个长度为 $8$ 的二进制数，表示 $f_{j,x}$ 的每个取值是 $g_{a_j,x}$ 还是 $g_{a_j,x}+1$。对于 $|i-j| \leq 15$ 的 $j$ 重新计算。这样复杂度为 $O(n|\Sigma|^22^{|\Sigma|})$，事实上状态完全跑不满，可以轻松通过。

[Submission Link.](https://codeforces.com/contest/718/submission/290246983)

---

