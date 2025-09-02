# [BalticOI 2015] Tug of War

## 题目描述

拔河（*Tug of War*）在 Byteland 是十分受欢迎的运动。规则十分简单：两队以相反方向拉绳子。一年一度的 Byteland 拔河比赛将要进行，并且许多选手都报名参加了。作为公平竞赛专员，你的工作是把选手们划分为两个队伍，使得这个比赛能够进行很长时间。

由于一共 $2n$ 名选手报名参赛，所以一个队有 $n$ 名队员。一根绳上左右两边各有 $n$ 个点。Byteland 的拔河精英们都很挑剔，每个参赛选手在左右两边都有一个他们想要站的位置。此外，你知道每一个参赛选手的力量值。

组织者现在问你如下的问题：给定一个整数 $k$，能否分出两个队，这两个队各有 $n$ 名选手，并且他们站在他们想站的位置（当然不能有两名或以上选手站在同一位置），双方力量和之差不超过 $k$？

## 说明/提示

### 样例解释 1

第一个样例中我们可以安排 $1,3,6,7$ 号选手站在左边（这个队伍力量值为 $1+8+2+1=12$），并安排 $2,4,5,8$ 号选手站在右边（这个队伍力量值为 $2+2+5+2=11$）。力量值的差为 $1$。

### 样例解释 2

第二个样例中两位力量值为 $4$ 的选手不得不在一个队中，因此两队最小的力量值之差为 $6$。

### 子任务

以下子任务与评测无关，仅供参考。

本题采用子任务式测评，只有一个子任务内所有测试点均正确才可获得此子任务的分数。

对于全部子任务，$k\le 20n,1\le l_i,r_i\le n,1\le s_i\le 20$。

对于每个子任务满足的条件如下：

| 子任务 |           条件            | 分数 |
| :----: | :-----------------------: | :--: |
|  $1$   |         $n\le 10$         | $18$ |
|  $2$   |    $n\le 2\times 10^3$    | $30$ |
|  $3$   | $n\le 3\times 10^4,s_i=1$ | $23$ |
|  $4$   |    $n\le 3\times 10^4$    | $29$ |

~~注：实际上，拔河并不取决于力量而取决于双方体重。原题的选手力量值应正比于选手体重值。~~

### 附注

本题翻译搬运自 [LibreOJ](https://loj.ac/problem/2707)，译者为 HeRaNO，在此对原翻译者表示感谢。

## 样例 #1

### 输入

```
4 1
1 1 1
2 1 2
2 2 8
1 2 2
3 3 5
3 3 2
4 4 1
4 4 2```

### 输出

```
YES```

## 样例 #2

### 输入

```
2 5
1 1 1
1 2 4
2 2 1
2 1 4```

### 输出

```
NO```

# 题解

## 作者：Ephemeroptera (赞：7)

### Solution:

这题楼上已经讲得很清楚了，就是考虑将人看成边去连接两个点，将点分配给边获得相应的权值。有解当且仅当连出来的图是一个基环树森林。  

而基环树森林是方便将点分配给边的。因为对于树的部分，方案已经确定。对于环的部分，分配分成顺时针和逆时针两种情况。而在这一道题中，因为一条边肯定连接的是左边和右边，得到的是一个偶环，也就是说，顺时针分配得到的权值和逆时针分配得到的权值是相反数。

因为要求得两边的权值差在 $k$ 内是否有解，这个问题结合上这个基环树森林可以用背包解决。可以先假定都取顺时针顺序，然后用逆时针顺序减去顺时针顺序作为权值去做，但复杂度为 $O(\frac {n^2a}{w})$ 。另外一篇题解好像是用这个不正确的复杂度通过的。 

注意到做的是背包，并且总权值是 $na$ 的，可以得知不同的个数在 $\sqrt{na}$ 内，做多重背包就好了。单调队列没法 bitset 优化，所以使用二进制分组。但是需要注意的是，二进制分组在这里的复杂度是 $O(\frac{na\sqrt{na}}{w})$ 的而非楼上题解所写的是 $O(\frac{na\sqrt{na}log(\sqrt{na})}{w})$。

因为这里的 $log$ 并不能简单的写成 $log(na)$，复杂度应该写成 $\frac{na\sum_i^{cnt}log(b_i)}{w}$ ，其中 $cnt$ 是不同权值的个数，$b_i$ 是第 $i$ 个权值的个数。其中满足 $\sum_i^{cnt}b_i*val_i \le na$。这个东西实际上是可以被证明是常数。

code: 
```
#include <bits/stdc++.h>



using namespace std;
const int N = 2e5 + 10;
int n, k, m, bas;
int c[N];
int first[N], nex[N << 1], v[N << 1], w[N << 1], num = 1;
int vis[N], cir[N], sav[N], stu[N], top = 0; 
int val[N], len[N], cnt = 0;
struct node {
	int val, cnt;
}a[N];
int edg = 0, ver = 0;
bitset<N * 20> dp;
inline void add(int x, int y, int z) {
	v[++num] = y;
	w[num] = z;
	nex[num] = first[x];
	first[x] = num;
}
inline void Find_cir(int u, int fa) {
	if (vis[u]) {
		for (int i = top; i >= 1; i--) {
			cir[stu[i]] = true;
			sav[++len[cnt]] = stu[i];
			if (stu[i] == u) break;
		}
		return ;
	}
	stu[++top] = u;
	ver++;
	vis[u] = true;
	for (int i = first[u]; i != -1; i = nex[i]) {
		int to = v[i];
		if ((i ^ fa) != 1 && !cir[to]) {
			edg++;
			Find_cir(to, i);	
		}
	}
	top--;
}
inline void DFS(int u, int fa) {
	for (int i = first[u]; i != -1; i = nex[i]) {
		int to = v[i];
		if (!cir[to] && fa != to) {
			m += (to > n ? -w[i] : w[i]);
			DFS(to, u);
		}
	}
}
inline void dfs(int Rot, int u, int fa) {
	for (int i = first[u]; i != -1; i = nex[i]) {
		int to = v[i];
		if ((fa ^ i) != 1 && cir[to]) {
			val[cnt] += (u > n ? -w[i] : w[i]);
			if (Rot != to) dfs(Rot, to, i);
		}
	}
}
inline void sol() {
	for (int i = 1; i <= len[cnt]; i++) DFS(sav[i], 0);
	for (int i = first[sav[1]]; i != -1; i = nex[i]) {
		int to = v[i];
		if (cir[to]) {
			val[cnt] += (sav[1] > n ? -w[i] * 2 : w[i] * 2);
			dfs(sav[1], to, 0);
			break;
		} 
	}
	m += -val[cnt];
	val[cnt] = 2 * val[cnt];
}
int main() {
	memset(first, -1, sizeof first);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> k;
	for (int i = 1; i <= n * 2; i++) {
		int x, y;
		cin >> x >> y >> c[i];
		add(x, y + n, c[i]);
		add(y + n, x, c[i]);
	}
	for (int i = 1; i <= n * 2; i++) {
		if (!vis[i])  {
			ver = 0, edg = 0;
			++cnt;
			Find_cir(i, 0);
			if (ver != edg) {
				cout << "NO\n";
				return 0;
			}
			sol();
		}
	}
	sort(val + 1, val + cnt + 1);
	int tem = cnt; cnt = 0; 
	val[0] = -2e9;
	for (int i = 1; i <= tem; i++) {
		if (val[i] != val[i - 1]) {
			a[++cnt].val = val[i];
			a[cnt].cnt = 1;
		} else a[cnt].cnt++;
	}
	bas = n * 20;
	dp[bas] = 1;
	for (int i = 1; i <= cnt; i++) {
		for (int j = 1; a[i].cnt; j = min(j * 2, a[i].cnt -= j)) {
			if (a[i].val < 0) dp = (dp | (dp >> (-a[i].val * j)));
			else dp = (dp | (dp << (a[i].val * j)));
		}
	} 
	bool ans = 0;
	for (int i = -k; i <= k; i++) ans |= dp[i + bas - m];
	if (ans) cout << "YES\n";
	else cout << "NO\n";
	return 0;
}
```

---

## 作者：Celebrimbor (赞：6)

退役前水一发题解，保佑我安度晚年。

### 分析

我们构造一个二分图，左右各 $2n$ 个点，左边表示选手，右边表示位置，可行的位置连边。如 $l1 = 2$，$r1 = 3$，则连边 $(1,2)$、$(1,3+n)$。

之前校内膜你赛里也出现过长成这样的二分图，记忆犹新。左侧每个点度都为 $2$，这样的二分图有很好的性质：形如若干环上长出若干条链。

如何说明？若图右侧有孤点则无解，若右侧某点度为 $1$ 则该位置的方案确定，可以顺着删去一条链。故令右侧点度均 $\geq 2$，而左侧点度均为 $2$，且左右点度数和相等，可知剩下的图为若干个偶环的集合。

那么对于每个偶环，只要确定一名选手的归属就能确定这些点对两支队伍的总贡献。那么就有两种情况。先默认一种情况，预处理换方案的贡献，做01背包记录某种力量差能否取到即可。再用bitset优化一下，复杂度 $O(\frac{n\times k}{w})$。

取 $n=3e4$、$k=6e5$、$w=64$，算一下大概是 $3e8$，似乎很悬。

看到时限有足足两秒，这摆明了想放 $O(n^2)$ 级的解法过啊。

那么吸个氧，喜提22s最劣解。

### 代码

删链的时候注意判断点到底在不在链上。可以用拓扑排序做，但我写的很丑就是了。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <bitset>

using namespace std;

const int MAXN = 60005, MAXK = 20*MAXN;
int n, k, d[MAXN], ch[MAXN][2], a[MAXN], val[2], base[2], v[MAXN], t;
bool vis[MAXN], vis_[MAXN];
bitset<MAXK*2+100> f;
vector<int> ed[MAXN];

void proc_line(int x) {
	d[x]--;
	if (d[x] >= 2) return;
	for (int u : ed[x]) {
		if (!vis_[u]) {
			vis_[u] = 1;
			if (x <= n) val[0] += a[u];
			else val[1] += a[u];
			vis[x] = 1;
			if (ch[u][0] != x && !vis[ch[u][0]]) proc_line(ch[u][0]);
			else if (ch[u][1] != x && !vis[ch[u][1]]) proc_line(ch[u][1]);
			break;
		}
	}
}

void proc_circle(int x) {
	vis[x] = 1;
	for (int u : ed[x]) {
		if (!vis_[u]) {
			vis_[u] = 1;
			if (x <= n) val[0] += a[u];
			else val[1] += a[u];
			if (ch[u][0] != x && !vis[ch[u][0]]) proc_circle(ch[u][0]);
			else if (ch[u][1] != x && !vis[ch[u][1]]) proc_circle(ch[u][1]);
			break;
		}
	}
}

int main() {
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= 2*n; i++) {
		scanf("%d %d %d", &ch[i][0], &ch[i][1], a+i);
		ch[i][1] += n;
		d[ch[i][0]]++;
		d[ch[i][1]]++;
		ed[ch[i][0]].push_back(i);
		ed[ch[i][1]].push_back(i);
	}
	for (int i = 1; i <= 2*n; i++) {
		if (d[i] == 0) {
			printf("NO\n");
			return 0;
		}
	}
	for (int i = 1; i <= 2*n; i++) {
		if (d[i] == 1) {
			val[0] = val[1] = 0;
			proc_line(i);
			base[0] += val[0];
			base[1] += val[1];
		}
	}
	for (int i = 1; i <= 2*n; i++) {
		if (!vis[i]) {
			val[0] = val[1] = 0;
			proc_circle(i);
			base[0] += val[0];
			base[1] += val[1];
			v[++t] = 2*val[1]-2*val[0];
		}
	}
	f[base[0]-base[1]+MAXK] = 1;
	for (int i = 1; i <= t; i++) {
		if (v[i] > 0) {
			f |= f<<v[i];
		}
		else f |= f>>(-v[i]);
	}
	bool ans = 0;
	for (int i = -k; i <= k; i++)
		ans |= f[i+MAXK];
	printf(ans?"YES\n":"NO\n");
	return 0;
}
```


---

## 作者：封禁用户 (赞：3)

### 前言

偶然看见一道黑题，花了好久才切了。

从 94 到 97 再到 100，花了不少时间。

[题目传送门](https://www.luogu.com.cn/problem/P4733)

### 分析

若干参赛选手，每个选手都有两个喜欢的位置，要求给每个选手匹配一个位置。

这题的重点是，如何把它转化成一个恰当的图论模型。

其实如果大胆地假设，把选手转化成边，连通块的边数刚好等于点数，就是一个基环内向森林。

简单地说，就是有一堆基环内向树，基环内向树就是一个环每个点都是一颗树的根节点的特殊的图。

由于其重要性质“连通块的边数刚好等于点数”，我们此时要做的不是“点——点”匹配而是“边——点”匹配。

所以如果出现有连通块的点数不等于边数时，要判不合法。

对于树的部分，直接让每个点和连向父亲的边匹配。

对于环的部分，有两个匹配方向，可以进行背包。

此时对背包进行 bitset 优化，时间复杂度 $O(\dfrac{nk}{w})$。

### 优化

发现权值和的范围比较小，所以不同的权值应该不多。

通过计算，不同的权值数量是根号级别的。

然后就修改之前的操作，环默认一个方向匹配，另一个方向进行背包。合并相同的权值，就是一个多重背包。

对多重背包进行二进制优化，再用 bitset，时间复杂度为 $O(\dfrac{k^{\frac{2}{3}} \times \log({k})}{w})$，可以接受。

### 代码

本代码已通过目前讨论区的所有 Hack 数据。

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	register T p = 1;
	x = 0;
	char c = getchar();
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -p;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		x = (x<<3)+(x<<1)+(c^48);
		c = getchar();
	}
	x *= p;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10);
	putchar(x%10+48);
}
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define ll long long
#define pii pair<int,int>
#define N 60010 
int head[N],nxt[N<<1],to[N<<1],val[N<<1],deg[N],cnt = 1;
inline void add(int u,int v,int w)
{
	++deg[u];
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = v;
	val[cnt] = w;
}
int f[N],sum[N*40],sumnode[N],sumedge[N],n,k,now = 0;
queue<int> q;
bitset<N> mark;
bitset<N*40> dp;
int find(int u)
{
	if(u == f[u]) return u;
	return f[u] = find(f[u]);
}
int main()
{
//	freopen("tug.in","r",stdin);
//	freopen("tug.out","w",stdout);
	read(n),read(k);
	F(i,1,n<<1) f[i] = i;
	F(i,1,n<<1)
	{
		int u,v,w;
		read(u),read(v),read(w);
		add(u,v+n,w);
		add(v+n,u,w); 
		f[find(u)] = find(v+n);
	}
	F(i,1,n<<1) ++sumnode[find(i)];
	F(u,1,n)
		for(register int i = head[u];i;i = nxt[i])
			++sumedge[find(u)];
	F(i,1,n<<1) 
		if(sumnode[i] != sumedge[i])
		{
			puts("NO");
			return 0;
		}
	F(i,1,n<<1)
		if(deg[i] == 1)
			q.push(i),mark[i] = 1;
	while(q.size())
	{
		int u = q.front();
		q.pop();
		for(register int i = head[u];i;i = nxt[i])
		{
			int v = to[i],w = val[i];
			if(mark[v]) continue;
			if(u <= n) now += w;
			else now -= w;
			if(--deg[v] == 1)
			{
				q.push(v);
				mark[v] = 1;
			}
		}
	}
	F(u,1,n<<1)
	{
		if(mark[u]) continue;
		int ret = 0,x = u;
		int lst = head[x]; 
		while(!mark[x])
		{
			mark[x] = 1;
			for(register int i = head[x];i;i = nxt[i])
			{
				if(i == lst||i == (lst^1)) continue;
				int v = to[i],w = val[i];
				if(mark[v]&&v != u) continue;
				if(x <= n) ret += w;
				else ret -= w;
				lst = i;
				x = v;
				break;
			}
		}
		now -= abs(ret);
		++sum[abs(ret)<<1];
	}
	if(abs(now) <= k)
	{
		puts("YES");
		return 0;	
	} 
	if(now > 0)
	{
		puts("NO");
		return 0;
	}
	dp[0] = 1;
	F(i,1,n*2*40)
	{
		if(!sum[i]) continue;
		int num = sum[i];
		for(register int j = 1;j <= num;j <<= 1)
		{
			num -= j;
			dp |= (dp<<(i*j));
		}
		if(num) dp |= (dp<<(i*num));
	}
	F(i,-k-now,k-now)
		if(dp[i])
		{
			puts("YES");
			return 0;
		}
	puts("NO");
	return 0;
}
```

---

## 作者：Piwry (赞：2)

## 解析

考虑将每个人看成一条边；具体来说，这条边的边权为 $s_i$，连接 $l_i$ 和 $n+r_i$ 这两个结点

如果我们要确定一个人的队伍，就相当于将他对应的边 $(u, v)$ 删掉，并决定是将权给予 $u$ 还是 $v$；并且一个结点必须被给予一次且仅一次权。可以发现，当我们删掉一条边后，该边所在的联通块的所有点的权都能被推断出来

观察最后形成的图。不难发现，若单个联通块中有超过一个的环，那么事实上是找不到方案满足每个人的要求的；因为无论我们删哪条边，最后的推断关系都存在环。此外，如果图中存在树的连通块，不难发现这一定会导致其它联通块存在超过一个的环。于是最后，当且仅当图为基环树森林时才能满足每个人的要求

考虑一颗基环树的权确定情况。首先我们只能选择环上的边（不然无法推断出合法的方案）；接着能发现基环树上最终的方案实际上只有两种，即沿着环顺时针分配权或逆时针分配权（至于不属于环的 “树边” 的权的分配方向则是确定的）

于是题目就被转化为：给定 $C$ 个物品（其中 $C$ 实际上就是图的连通块个数；即基环树个数），要为每个物品从两个权值中选择一个，要求使得最终权的和的绝对值小于等于 $k$

事实上可以对每个连通块先默认选择一个权，然后将其权重新设为原先两个权的差，这样最终题目就被转化为了背包问题

直接朴素地 01 背包的话，复杂度是 $\Theta(C\sum s_i)$，即 $\Theta(n^2a)$（其中 $a$ 即值域，这里最大是 $40$）的。即使用 bitset 优化也难以承受

但可以发现，不同的权值数事实上最大是 $\sqrt {\sum s_i}$ 级别的（只需考虑对于权值 $w$，至少需要 $\frac w a$ 个元素相加）。于是我们可以考虑对不同的权值做多重背包（单调队列优化），复杂度为 $O((\sum s_i)^{\frac 3 2})$，即 $O((na)^{\frac 3 2})$

但这样没法用 bitset；于是可以想到用二进制分组做多重背包，这样最后的复杂度就为 $O(\frac {(\sum s_i)^{\frac 3 2})\log_2 {\sqrt {\sum s_i}}} w)$，即 $O(\frac {((na)^{\frac 3 2})\log {\sqrt {na}}} w)$

## CODE

写得比较急，讲不太清楚的地方可以参考代码qaq

```cpp
#include <cstdio>
#include <vector>
#include <bitset>
#include <map>
using std::vector;
using std::bitset;
using std::pair;
using std::map;
typedef pair<int, int> pad;

const int MAXN =3e4+20, MAXV =20;

/*------------------------------IO------------------------------*/

int read(){
	int x =0; char c =getchar(); bool f =0;
	while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
	while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(c^48), c =getchar();
	return (f) ? -x : x;
}

void write(const int &x){
	if(x < 0){
		putchar('-');
		write(-x);
	}
	else{
		if(x/10)
			write(x/10);
		putchar('0'+x%10);
	}
}

/*------------------------------Map------------------------------*/

int first[MAXN<<1], tote;
struct edge{
	int to, nxt, w;
}e[MAXN<<2];

inline void addedge(const int &u, const int &v, const int &w){
	++tote;
	e[tote].to =v, e[tote].nxt =first[u], first[u] =tote;
	e[tote].w =w;
	++tote;
	e[tote].to =u, e[tote].nxt =first[v], first[v] =tote;
	e[tote].w =w;
}

/*------------------------------Dfs------------------------------*/

namespace Check_Illegal{
	bool vis[MAXN<<1];
	
	pad dfs(const int &u){
		vis[u] =1;
		pad ret(1, 0);
		for(int l =first[u]; l; l =e[l].nxt){
			if(!vis[e[l].to]){
				pad tmp =dfs(e[l].to);
				ret.first +=tmp.first, ret.second +=tmp.second;
			}
			++ret.second;
		}
		return ret;
	}
}

namespace Find_Circle{
	bool vis[MAXN<<1];
	
	int stk_id[MAXN<<1], stk_val[MAXN<<1], top;
	vector<int> Circle;
	int sum_circle[2];
	
	void init(){
		Circle.reserve(MAXN<<1);
		
		top =0;
		Circle.clear();
		sum_circle[0] =sum_circle[1] =0;
	}
	
	void dfs(const int &u, const int &eid_from =0){
		stk_id[top] =u, stk_val[top] =(eid_from == 0) ? 0 : e[eid_from].w, ++top;
		vis[u] =1;
		for(int l =first[u]; l; l =e[l].nxt){
			if(!vis[e[l].to])
				dfs(e[l].to, ((l-1)^1)+1);
			else if(l != eid_from && Circle.empty()){
				int pos =top, cur =1;
				/* 环应当存在 */
				while(stk_id[pos-1] != e[l].to){
					Circle.push_back(stk_id[pos-1]);
					sum_circle[cur ^=1] +=stk_val[pos-1];
					--pos;
				}
				Circle.push_back(e[l].to);
				sum_circle[cur ^=1] +=e[l].w;
			}
		}
		--top;
	}
}
using Find_Circle::Circle;
using Find_Circle::sum_circle;

namespace QAQ{
	bool vis[MAXN<<1];
	
	int sum[2];
	
	void init(){
		sum[0] =sum[1] =0;
	}
	
	void dfs(const int &u, const int &N, const int &eid_from_twin =0){
		vis[u] =1;
		if(eid_from_twin)
			sum[(u > N)] +=e[eid_from_twin].w;
		for(int l =first[u]; l; l =e[l].nxt)
			if(!vis[e[l].to])
				dfs(e[l].to, N, l);
	}
}
using QAQ::sum;

/*------------------------------Main------------------------------*/

int main(){
	int n =read(), k =read();
	for(int i =0; i < 2*n; ++i){
		int l =read(), r =read(), s =read();
		addedge(l, n+r, s);
	}
	// init done. //
	
	map<int, int> Map;
	int Sum =0;
	for(int i =1; i <= 2*n; ++i)
		if(!QAQ::vis[i]){
			pad tmp =Check_Illegal::dfs(i);
			/* 存在非基环树连通块 */
			if(tmp.first != tmp.second/2){
				puts("NO");
				return 0;
			}
			
			Find_Circle::init();
			Find_Circle::dfs(i);
			
			QAQ::init();
			for(int ii =0; ii < (int)Circle.size(); ++ii)
				QAQ::vis[Circle[ii]] =1;
			for(int ii =0; ii < (int)Circle.size(); ++ii)
				QAQ::dfs(Circle[ii], n);
			
			Sum +=sum[0]-sum[1]+(sum_circle[1]-sum_circle[0]);
			/* 环上可以有两个方向确定权值 */
			int new_elm =
				(sum[0]-sum[1]+(sum_circle[0]-sum_circle[1]))
				-
				(sum[0]-sum[1]+(sum_circle[1]-sum_circle[0]))
			;
			if(Map.count(new_elm))
				++Map.find(new_elm)->second;
			else
				Map.insert(pad(new_elm, 1));
		}
	
	bitset<MAXN*MAXV*2+1> dp;
	const int DELTA =MAXN*MAXV;
	dp[Sum+DELTA] =1;
	auto Dp =[&](const int &val){
		if(val >= 0)
			dp |=dp<<val;
		else
			dp |=dp>>(-val);
	};
	for(pad elm:Map){
		/* 这里能保证 elm.second >= 0 */
		int p =1;
		for(int i =0; i < 21 && ((p<<1)-1) <= elm.second; ++i, p <<=1)
			Dp(elm.first*p);
		p >>=1;
		Dp(elm.first*(elm.second-((p<<1)-1)));
	}
	
	bool OK =0;
	for(int i =-k; i <= k; ++i)
		if(dp[DELTA+i]){
			OK =1;
			break;
		}
	if(OK)
		putchar('Y'), putchar('E'), putchar('S');
	else
		putchar('N'), putchar('O');
}
```

---

## 作者：Erica_N_Contina (赞：1)

绝对是笔者写过最长的题解了 qwq。
## 思路

### **PART O 模型转化**

我们考虑一种类似二分图的模型。我们构建一个二分图 $E$，我们把选手和选手想要站的位置分别看成点，为了方便我们把选手编号为 $2n+1\sim 4n$，这些点有一个属性 $w_i$ 为力量。把选手想要站的位置编号为 $1\sim 2n$，$1\sim 2n$ 这些点有一个属性 $id_i$ 为队伍编号，可能是 $1$ 或者 $0$。我们把点分成两组，$1\sim 2n$ 放左边，$2n+1\sim 4n$ 放右边。

我们在选手和选手想要站的位置之间连边，这里我们假定从选手连向位置，那么显然每个位置会有 $2$ 的入度，每个选手会有 $2$ 的出度。现在的问题就变成了我们在 $4n$ 条边中选择 $2n$ 条边，保证左右两边每个点都有一条边相连，让 $id=1$ 的点连着的点的 $w_i$ 之和与 $id=0$ 的点连着的点的 $w_i$ 之和尽可能接近。

下图是 $E$ 的一种可能形态。

![](https://cdn.luogu.com.cn/upload/image_hosting/8kfxk6pv.png)
### **PART I 不合法情况**

首先我们可以处理到一部分选手，就是那些位置已经被确定的选手。为什么有一些选手的位置已经被确定了呢？我们回到上面构建的二分图 $E$。左边的点的入度可能是 $0,1,2,\dots$。

那么对于入度为 $0$ 的点，就代表着这个位置没有选手想要站，于是这个位置就会空出来。而我们又知道，最终每个点都应该有选手站，否则就会有选手没有位置站、有一些位置空余。所以如果出现一个左边的点没有入度，那么直接输出 NO。

对于入度为 $1$ 的点 $u$，那么只有一个选手 $p$ 想要站这个位置。为了让我们尽可能可以分出这两个队，即让每个选手都有位置站，那么我们就让 $p$ 站 $u$ 这个位置。因此 $p$ 的位置就已经被确定了。

### **PART II 建立新图**

完成上面的部分，我们就已经确定了一些选手的位置。我们把这些选手和位置代表的点从二分图中剔除（后面解释）出来，原二分图就变成了一副新二分图 $G$。

剔除时，我们把那些已经确定位置的选手想要站的位置（$2$ 个）对应的点的入度 $-1$（也就是说在删掉选手代表的点的时候把其连出去的边也删掉），把选手代表的点删掉，把选手确定要站的位置代表的点也删掉，这样我们就保证图中的边数始终等于点数，并且左边的点数=右边的点数。

对于这个二分图，我们有一个重要的性质：左边的点都各种有 $2$ 的入度，右边的点都各自有 $2$ 的出度。为什么？因为首先我们保证图中边数 $=2\times $ 右边的点数。那么假设左边有入度为 $3$ 的点，就一定存在入度 $<2$ 的点。这么说吧，就是左边的点的入度之和也一定等于 $2\times $ 左边的点数。

### **PART III 搭建 dp 模型**

在构建新二分图 $G$ 的流程如下。

我们在剔除位置固定的选手时，标记他们。然后在建新图时，枚举，每个选手。如果有标记就跳过。如果没有，则代表着这个选手连出去的两条边都在新图中。我们设这个选手连出去的两条边指向的点为 $u1,u2$（回顾一下：在图 $E,G$ 中选手是右边的点，位置是左边的点，边是从右边指向左边的）我们在第 $3$ 幅图 $V$ 中连接 $u1,u2$。那么想一想，最后图 $V$ 中是不是会出现几个独立的简单环？并且 $V$ 只由这几个简单环构成，点数为 $2n$，即图 $G$ 中左边的点。

下图是图 $G$ 的一种可能形态。

![](https://cdn.luogu.com.cn/upload/image_hosting/llibea9p.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/ntd9tn06.png)

右边的图是由左边的图构建出来的图 $V$。真实情况中可能是由多个并列的环构成的。

我们构建图 $G$ 的反向图 $G'$，那么我们在图 $V$ 中重叠上图 $G'$。

![](https://cdn.luogu.com.cn/upload/image_hosting/d6nwlgos.png)

我们可以发现每个环，我们假设这个环中有 $k$ 个点（左边的点，即红点），那么这些点会连向的右边的点也是 $k$ 个。

我们把红点编号为 $a1,a2,\dots,ak$，把右边的点编号为 $b1,b2,\dots,bk$（没有对应关系，但是一定是按顺序的），那么我们会发现 $a(j)$ 对应的点是 $b(i),b(i+1)$，$a(j+1)$ 对应的点是 $b(i+1),b(i+2)\dots$。举个例子，假设我们点 $a1$ 我们选择 $b(i)$ 给他匹配，那么 $a 2$ 我们就只能选 $b(i+1)$，$a3$ 只能选 $b(i+2)$。如果 $a1$ 选 $b(i+1)$，那么 $a2$ 我们就只能选 $b(i+2)$，$a3$ 只能选 $b(i+3)$。事实上，我们点 $a1$ 也只有两种情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/44tmdwyp.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/l146vchv.png)

我们就拿一个环来举例。那么每一个环上的点（也就是 $G$ 中的左边的点）选择一个右边的点，那么就会产生贡献——别忘了，右边的点有一个属性 $w_i$ 为力量，左边的点有一个属性 $id_i$ 为队伍编号——那么我们对两个队伍分别记录一个力量和 $sum$，贡献就是把 $sum_{id_i}$ 加上 $w_i$。上面我们说一个环只有两种情况，那么我们把这两种情况计算出来。我们把每个环看出一个物品，每个物品有可能产生 $2$ 种贡献。所以现在我们就要判断每一种物品选择哪个贡献，让 $sum_1$ 和 $sum_0$ 尽可能平均。

### **PART IV 构建背包 dp 模型**

用来上面的说明，我们已经可以摸清楚一点点 dp 的模型了。为了让“尽可能平均”这个抽象条件变具体，我们可以把它变成 $sum_1-sum_0$ 的绝对值尽可能小。我们可以简单写一个 dp。

定义状态：$dp_{i,j}$ 为考虑前 $i$ 个环，是否可以产生差值 $j$（这里的 $j$ 可能是负数）。但是这样的 dp 的时间复杂度是 $O(n\sum s_i)$ 的，明显不行。

我们换一个思路——我们先假设所有的环（假设有 $t$ 个环）都选择第一种情况，产生的差值为 $c_1,\dots,c_t$，我们把它们相加，再加上之前已经确定的选手的位置规划对两个队伍产生的贡献的差值，就得到了两个队伍的 $w$ 值的差值，即为 $ans_{pre}$。然后我们设所有环选择第二种情况产生的差值为 $d_1,\dots,d_t$，我们计算出 $q_i=d_i-c_i$。那么我们就把 $q_1,\dots,q_t$ 看成一个个物品。如果我们选择了物品 $i$，那么就相当于我们第 $i$ 个环选择了情况二，我们把 $ans_{pre}$ 加上 $q_i$，就相当于计算出了上述情况下两个队伍 $w $ 值的差值。我们要让差值尽可能小，就是要让若干物品的和（即选出的 $q_i$）加起来尽可能靠近 $-ans_{pre}$。

所以这就是一个 01 背包的模型。

### PART V 优化背包 dp

01 背包还是会超时啊，所以我们还可以怎么样优化呢？我们考虑到 $q_i$ 的值有很多是重复的（这里就不再说明了，请看他人博客吧，笔者不想写了 TT），所以我们可以把这些重复的 $q_i$ 合并，也可以理解成建一个桶。所以现在这个 dp 变成了一个多重背包。对于多重背包，我们可以使用二进制分解优化。而我们记录的又是当前差值是否可以取到，所以状态只有 $0$ 或者 $1$，这里我们可以用 bitset 优化。

### PART VI 代码

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mp make_pair

#define rd read()
inline int rd
{
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}


// void solve(){

//     cerr<<"\nintrr[][]=";
//     for(int i=1;i<=n;i++)cerr<<t[i].l<<' '<<t[i].r<<endl;
// }

const int M=1e5+5,N=6e5+5;
int n,k,top,w1,cnt,c;
int p1[M],p2[M],x1[M],x2[M],w[M],du[M],stk[M],v[2][M];
bool used[M];
bitset<N*2> f[2];
vector<int> g[M],e,r;

int find(int m){
	for(int i=0;i<(int)g[m].size();i++)
	    if(!used[g[m][i]]) return g[m][i];
}
int anothe(int m,int i){
	return (p1[m]*n+x1[m]==i)?p2[m]*n+x2[m]:p1[m]*n+x1[m];
}
void dfs(int q,int m){
	int p=(q?p2[m]*n+x2[m]:p1[m]*n+x1[m]);
	du[p]--,stk[++top]=p,cnt+=q;
	while(top)	{
		int u=stk[top--],g=find(u),h=anothe(g,u);
		r.push_back(g),e.push_back(u);
		if(u<=n) v[q][cnt]+=w[g],du[h]--,used[g]=1;
		else v[q][cnt]-=w[g],du[h]--,used[g]=1;
		if(du[h]==1) stk[++top]=h;
	}
	while(!r.empty())	{
		if(q) used[r.back()]=0,du[e.back()]=2;
		r.pop_back(),e.pop_back();
	}
}
signed main(){
	//freopen("boat.in","r",stdin)
	//freopen("boat.out","w",stdout);
    n=rd,k=rd;
    for(int i=1;i<=(n<<1);i++) {
		p1[i]=0,x1[i]=rd,p2[i]=1,x2[i]=rd,w[i]=rd;
        du[p1[i]*n+x1[i]]++;
		du[p2[i]*n+x2[i]]++;
        g[p1[i]*n+x1[i]].push_back(i);
		g[p2[i]*n+x2[i]].push_back(i);
    }
    for(int i=1;i<=(n<<1);i++){
		if(!du[i]) {
			puts("NO");
			return 0;
		}
		else if(du[i]==1) stk[++top]=i;
	}
	while(top){
		int u=stk[top--],g=find(u),h=anothe(g,u);
		if(u<=n) w1+=w[g];
		else w1-=w[g];
		du[h]--,used[g]=1;
		if(!du[h]) {
			puts("NO");
			return 0;
		}
		else if(du[h]==1) stk[++top]=h;
	}
	for(int i=1;i<=(n<<1);i++){
	    while(!g[i].empty()) g[i].pop_back();
	}
	for(int i=1;i<=(n<<1);i++){
	    if(!used[i]) {
			g[p1[i]*n+x1[i]].push_back(i);
			g[p2[i]*n+x2[i]].push_back(i);
		}
	}
    for(int i=1;i<=(n<<1);i++){
        if(!used[i]) {
			dfs(1,i);
			dfs(0,i);
			w1+=v[0][cnt];
			v[1][cnt]-=v[0][cnt];
		}
	}
    sort(v[1]+1,v[1]+cnt+1);
	
	f[1][N+w1]=1,c=1,v[1][cnt+1]=N<<2;
    for(int i=1;i<=cnt;i++,c++){
        if(v[1][i]!=v[1][i+1]){
			int k=1;
			while(c>k) stk[++top]=v[1][i]*k,c-=k,k<<=1;
		    stk[++top]=v[1][i]*c,c=0;
		}
	}
    for(int i=0;i<top;i++,c=!c){
        if(stk[i+1]>0) f[!c]=f[c]|(f[c]<<stk[i+1]);
        else f[!c]=f[c]|(f[c]>>-stk[i+1]);
	}
    for(int i=0;i<=k;i++){
        if(f[c][N+i]||f[c][N-i]) {
			puts("YES");
			return 0;
		}
	}
    puts("NO");	
	return 0;
}

/*
2 5
0 1 1 1 1
0 1 1 2 4
0 2 1 2 1
0 2 1 1 4
*/

```

特别感谢 [luogu.com.cn/user/753534](https://www.luogu.com.cn/user/753534) 的帮助。





---

## 作者：0xyz (赞：1)

差 1.5h 就场切了（代码能力太差了）。这份代码可以通过讨论区所有 hack 数据。

我们首先看到数据范围，$\sum s_i\le 6\times 10^5$，实在是很小，所以时间复杂度可能跟这个东西有关。

首先，如果选手之间可以穿模怎么做（也就是去掉“一个位置只能安排一个人”这个条件）？我们可以维护一个 `bitset` $f$，$f_i$ 代表左侧减右侧的差值能否恰为 $i+\Delta$，然后转移就是 `f=f<<s[i]|f>>s[i]`。

 时间复杂度 $O(\frac{n\sum s_i}{\omega})$，可以通过。

接下来，出题人修复了穿模的 bug，那么我们怎么做？我一开始想到的是把选手和位置放在两边，然后做“二分图绝对值最小权完美匹配”这种抽象的东西。

但是我们可以换换思路，因为选手的度数恒为 $2$，那么我们可以把选手当成边，位置当成点。问题转化为考虑给一个 $2n$ 条边，$2n$ 个点的无向图上的边安排方向，使得每个点的入度恰为 $1$。

原来这个无向图有若干连通块，我们分开考虑。首先，如果存在一个环，它一定可以自产自销，从而一个端点是这个环上的点，却不在环上的边一定是外向的。从而，如果一个连通块中同时存在两个环，这两个环的外向边汇合时一定会产生冲突。所以，要成功安排，每个连通块中至多一个环，进而每个连通块的边数 $E$ 和点数 $V$ 满足 $V-1\le E\le V$。但是又会有 $\sum E=2n=\sum V$，所以所有连通块的最终定向都必须是外向基环树，进而所有连通块不在环上的所有边的定向方式唯一，然后环上的边有顺时针和逆时针两个方向，所以整个联通块只有 $2$ 种安排方法，假设它们对于左边重量之和减去右边重量之和的贡献分别是 $a_i,b_i$（可能不是正数）。

注意在处理的时候特判大小为 $2$ 的环，因为无向图双向连边之后会有重边。

于是我们就转化成了一开始提到的那个问题，只是改成了把每个连通块扔进 `bitset` 里。也就是令 `f=f>>a[i]|f>>b[i]`。时间复杂度依然是 $O(\frac{n\sum s_i}{\omega})$。

我居然写了 1h,调了 2.5h，我太逆天了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int _=2e5+5;
bitset<1200001>f;
int n,k,ans=-1,cnt=1,A,B,C,D,E,F,V,u[_],v[_],o[_],nxt[_],h[_],t[_],w[_];
vector<int>z;
void add(int x,int y,int z){
	nxt[++cnt]=h[x];h[x]=cnt;t[cnt]=y;w[cnt]=(y>n?-1:1)*z;
	nxt[++cnt]=h[y];h[y]=cnt;t[cnt]=x;w[cnt]=(x>n?-1:1)*z;
}
void dfs1(int x,int fr,int rt){
	V++;v[x]=1;
	for(int i=h[x];i;i=nxt[i],E++)
		if(!v[t[i]])dfs1(t[i],i,rt);
		else if(fr!=(i^1))C=x;
}
void dfs2(int x,int fr){
	z.push_back(x);o[x]=1;
	for(int i=h[x];i;i=nxt[i]){
		if(F)return;
		if(fr!=(i^1)&&t[i]!=C)dfs2(t[i],i);
		else if(fr!=(i^1))F=1;
	}
	if(!F)z.pop_back(),o[x]=0;
}
void dfs3(int x,int fr){
	for(int i=h[x];i;i=nxt[i])
		if(!o[t[i]]&&(i^1)!=fr)D+=w[i],dfs3(t[i],i);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>k;f[600000]=1;
	for(int i=1,x,y,w;i<=2*n;i++)cin>>x>>y>>w,add(x,n+y,w);
	for(int i=1;i<=2*n;i++)
		if(!v[i]){
			dfs1(i,0,i);
			if(E!=2*V)cout<<"NO\n",exit(0);
			dfs2(C,C);
			for(auto j:z)dfs3(j,0);
			if(z.size()==2){
				int ee;
				for(int j=h[z[0]];j;j=nxt[j])
					if(t[j]==z[1]){A+=w[j];B+=w[j^1];ee=j;break;}
				for(int j=h[z[1]];j;j=nxt[j])
					if(t[j]==z[0]&&j!=(ee^1))A+=w[j],B+=w[j^1];
			}else{
				z.push_back(C);
				for(int j=0;j+1<z.size();j++)
					for(int p=h[z[j]];p;p=nxt[p])
						if(t[p]==z[j+1])A+=w[p],B+=w[p^1];
			}
			A+=D;B+=D;
			if(A>0&&B>0)f=f>>A|f>>B;
			if(A<=0&&B<=0)f=f<<(-A)|f<<(-B);
			if(A>0&&B<=0)f=f>>A|f<<(-B);
			if(A<=0&&B>0)f=f<<(-A)|f>>B;
			A=B=C=D=E=F=V=0;z.clear();
		}
	for(int i=0;i<=min(600000,k);i++)
		if(f[600000-i]|f[600000+i]){ans=i;break;}
	if(~ans)cout<<"YES\n";
	else cout<<"NO\n";
	return 0;
}
```

---

## 作者：Aftglw (赞：1)

如果将每个人看作边，边权设为力量值；

将左右的位置看作点，那么我们将每个人对应的两个位置连接起来，就能得到一个二分图

现在我们要做的就是将边上的权值分配给左右部，使得左右部权值之和相差不超过 $K$

判断是否存在一种分配方案

假设分配给左部造成的贡献为正，右部为负，此时只需所有贡献之和的绝对值不超过 $K$

首先，这张二分图一共有 $2n$ 个点，$2n$ 条边，因此，这张二分图其实是个基环树森林，设共有 $cnt$ 棵基环树，$cnt \le n$

对于森林中每棵树，去环部分的分配是已经确定的了，即只能将每条边的权值分配给儿子（以环为根）

而对于环，我们只能按顺时针或逆时针进行分配，并且这两种不同的分配方案带来的总贡献互为相反数

如果设第 $i$ 个环，按顺时针分配的总权值为 $a_i$，那么按逆时针分配的方案为 $-a_i$

而对于 $cnt$ 个环，先假设全部都按一个方向分配，此时答案为 $ans$

如果已满足 $|ans| \le K$，则现在已经可以直接输出 $\text{YES}$ 了

否则，我们需要将某些环调转方向，显然调转第 $i$ 个环对 $ans$ 造成的贡献为 $-2a_i$

于是现在的问题便转化为：

有 $cnt$ 个物品，第 $i$ 个物品的价值为 $-2a_i$，当前有的价值为 $ans$，你需要选择一些物品，使得最后的总价值 $\le K$ 

直接 `bitset` 优化做 01 背包对吧，时间复杂度 $O(\frac{2cnt\sum a_i}w)$

而 $\sum a_i \le 2n \times 20, cnt \le n$，所以时间复杂度为 $O(\frac {80n^2}{w})$

这么多 $a_i$，应该会有一些值相同吧，而对于这些值相同的，可以当成多重背包做，这样就可以二进制优化了呢！ /hanx

但万一出题人造的数据各个 $a_i$ 互不相同呢？这不就卡掉了吗?

那么出题人最坏会将 $a$ 构造为一个以 $1$ 为首项，公差为 $1$ 的等差数列（这样项数 $cnt$ 最多）

而此时 $\sum a_i = \frac {(1 + cnt)cnt}{2} \le 2n \times 20$，解得 $cnt^2 + cnt \le 80n$

出题人再毒瘤一点，$cnt$ 取到上限 $n$（即全是二元环的情况），则解得 $cnt = n \le 79$，所以最多只会有 $79$ 种不同的 $a_i$

所以就可以愉快地用二进制优化了！

时间复杂度约为 $O(\frac {79 \times 6.3 \times 2 \sum \log{a_i}}{w})$，($\log 79 \approx 6.3$)

然而并 $a_i \le 2n \times 20,n \le 3e4$，于是乎 $a_i \le 1.2e6, \log a_i \le 20.2$

所以时间复杂度约为 $O(\frac {79 \times 6.3 \times 2 \times 79 \times 6.3 \times 20.2} {w})$，即 $O(\frac {10007294}w)$，显然可过 /hanx

```cpp
#include <bits/stdc++.h>
using namespace std;
#define re register
// #define int long long
// #define pair pair<int, int>
// #define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout);
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread (buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;
inline int read()
{
    re int x = 0, f = 0;
    re char c = getchar();
    while (!isdigit(c)) {if (c == '-') f = 1;c = getchar();}
    while (isdigit(c)) {x = (x << 3) + (x << 1) + c - 48;c = getchar();}
    return f ? -x : x;
}
inline string getstr()
{
    string res = "";
    re char ch = getchar();
    while (isspace(ch)) ch = getchar();
    while (!isspace(ch)) res.push_back(ch), ch = getchar();
    return res;
}
const int N = 6e4 + 5, inf = 0x7fffffff, P = 998244353;
int n, nn, K, ans;
int first[N], nex[N << 1], to[N << 1], w[N << 1], num = 1;
inline void Add(int u, int v, int val)
{
    nex[++num] = first[u];
    first[u] = num;
    to[num] = v;
    w[num] = val;
}
int deg[N];
queue<int> q;
inline void update(int u)
{
    for (re int i = first[u]; i; i = nex[i])
    {
        int v = to[i];
        if (deg[v] == 1) continue;
        ans += (u > n ? -1 : 1) * w[i];
        if (--deg[v] == 1) q.push(v);
    }
}
int a[N], cnt;
bool vis[N];
inline void dfs(int u, int ban, int rt)
{
    vis[u] = 1;
    for (re int i = first[u]; i; i = nex[i])
    {
        int v = to[i];
        if (i == ban) continue;
        if (v == rt)
        {
            ans += (u > n ? -1 : 1) * w[i];
            a[cnt] += (u > n ? -1 : 1) * w[i];
            return;
        }
        if (vis[v]) continue;
        ans += (u > n ? -1 : 1) * w[i];
        a[cnt] += (u > n ? -1 : 1) * w[i];
        return dfs(v, i ^ 1, rt);
    }
}
int b[500], t[N * 22]; // 79 * log(79) < 500
bitset<N * 29> f; // 这里应本来开 N * 40 的（因为有负数），但看数据仿佛 N * 29 足矣
signed main()
{
    n = read(), K = read(); nn = n << 1;
    for (re int i = 1; i <= nn; ++i)
    {
        int u = read(), v = read(), val = read();
        ++deg[u], ++deg[v + n];
        Add(u, v + n, val), Add(v + n, u, val);
    }
    for (re int i = 1; i <= nn; ++i)
    {
        if (deg[i] == 1) q.push(i);
        else if (!deg[i]) return puts("NO"), 0;
    }
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        vis[u] = 1, update(u);
    }
    const int base = nn * 20;
    for (re int i = 1; i <= nn; ++i)
    {
        if (vis[i]) continue;
        ++cnt;
        dfs(i, 0, i);
        a[cnt] = -a[cnt], a[cnt] <<= 1;
        ++t[a[cnt] + base];
    }
    sort(a + 1, a + cnt + 1);
    cnt = unique(a + 1, a + cnt + 1) - a - 1;
    int tot = 0;
    for (re int i = 1; i <= cnt; ++i)
    {
        int now = 1;
        while (t[a[i] + base] >= now) b[++tot] = a[i] * now, t[a[i] + base] -= now, now <<= 1;
        if (t[a[i] + base]) b[++tot] = a[i] * t[a[i] + base];
    }
    f.set(ans + base);
    for (re int i = 1; i <= tot; ++i)
        if (b[i] > 0) f |= f << b[i];
        else f |= f >> (-b[i]);
    for (re int i = -K + base, up = K + base; i <= up; ++i)
        if (f[i]) return puts("YES"), 0;
    puts("NO");
    return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

今早模拟赛的题。竟然快速场切了。感动。

不过模拟赛那道题可以让每个人喜欢站的位置可以在同一边。好像改动不大。我们直接说一说加强版的做法。

考虑把一个人喜欢的两个位置连边。那么转化为一个 $n$ 个点 $n$ 条边的图是否存在完美匹配。这个没有那么玄乎。直接检查每个连通块是否是基环树即可。

因为如果这个连通块的边数大于点数，那么就是人多资源少，必定有人无法站到想要的位置（就像每年有 50 块 Au，但是有 Au 实力的人如果比 50 人多那么必定有人成为时代的眼泪）。这种情况就只能是每个连通块都是基环树。

然后考虑给基环树上的每条边定一个方向，使得所有点的入度恰好为 $1$。这个正好符合外向基环树的性质。也就是不在环上的边的方向（也就是这个人选哪个位置）都是向外的。因此我们已经提前知道左边或者右边必定有多少的重量了。

然而环这一个整体是顺时针还是逆时针是不确定的。因此它能给船的左边（我们只用管左边，因为总重量是恒定的）带来的贡献有两种可能。我们关心一共能拼接处多少种情况。

那么直接用 bitset 加速即可。复杂度 $O(\frac{n \sum s}{\omega})$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=60000+10,MAXM=600000+10;
int n,k,fa[MAXN],vis[MAXN],sze[MAXN],w[MAXN],ed[MAXN],id1[MAXN],id2[MAXN],cnt0,cnt1;
bitset<MAXM> bit;
vector<pair<int,int>> G[MAXN];
int find(int k) {return (fa[k]==k)?k:(fa[k]=find(fa[k]));}
void merge(int u,int v) {return fa[find(v)]=find(u),void();}
int checkw(void) {
	ffor(i,2,n+n) if(w[i]!=w[1]) return 0;
	return 1;	
}
int anc[MAXN],idd[MAXN];
vector<int> cir,gid;
void dfs(int u,int id) {
	vis[u]=1;
	for(auto pr:G[u]) {
		int v=pr.first,nm=pr.second;
		if(nm==id) continue;
		if(vis[v]) if(cir.size()==0) {
			int U=u;
			while(U!=v) gid.push_back(idd[U]),cir.push_back(U),U=anc[U];
			gid.push_back(nm),cir.push_back(v);
		}
		if(vis[v]==0) idd[v]=nm,anc[v]=u,dfs(v,nm);
	}
	return ;
}
void add(int u,int ban1,int ban2) {
	for(auto pr:G[u]) {
		int v=pr.first,id=pr.second;
		if(v==ban1||v==ban2) continue;
		add(v,u,0);
		if(v<=n) cnt0+=w[id];
		else cnt1+=w[id];
	}
	return ;
}
void solve(int u) {
	int cnt1=0,cnt2=0;
	gid.clear(),cir.clear(),dfs(u,0);
	ffor(i,0,(int)cir.size()-1) {
		if(cir[i]<=n) cnt1+=w[gid[i]];
		if(cir[(i+1)%cir.size()]<=n) cnt2+=w[gid[i]]; 
	}
	bit=(bit<<cnt1)|(bit<<cnt2);
	ffor(i,0,(int)cir.size()-1) {
		int u=cir[i],lst=cir[(i+1)%cir.size()],nxt=cir[(i-1+cir.size())%cir.size()];
		add(u,lst,nxt);
	}
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k; ffor(i,1,n+n) fa[i]=i; bit[0]=1;
	ffor(i,1,n+n) {
		int p1,x1,p2,x2; cin>>x1>>x2>>w[i];
		p1=0,p2=1;
		id1[i]=p1*n+x1,id2[i]=p2*n+x2;
		merge(id1[i],id2[i]);
	}
	ffor(i,1,n+n) ed[find(id1[i])]++,sze[find(i)]++;
	ffor(i,1,n+n) if(find(i)==i) if(ed[i]!=sze[i]) return cout<<"NO",0;
	if(checkw()) return cout<<"YES",0;
	ffor(i,1,n+n) G[id1[i]].push_back({id2[i],i}),G[id2[i]].push_back({id1[i],i});
	ffor(i,1,n+n) if(vis[i]==0) solve(i);
	int wtot=0;
	ffor(i,1,n+n) wtot+=w[i];
	int dt=INT_MAX;
	ffor(i,0,wtot) if(bit[i]) dt=min(dt,abs(cnt0+i-(wtot-(cnt0+i))));
	if(dt<=k) cout<<"YES";
	else cout<<"NO";
	return 0;
}
```

---

## 作者：KingPowers (赞：0)

[题目链接](https://www.luogu.com.cn/problem/P4733)

~~为了迎合拔河应与体重而非力量相关这一事实~~，下文中记 $w_i$ 为题面中的 $s_i$，$m=\sum w_i$。

考虑将原题转化为图论问题，我们不妨将每个位置看作一个点，将每位选手看作一条边，将他想站的两个位置连起来，边权就是他对应的 $w_i$。那么，给每个位置找匹配的选手，就相当于给每个点在它的连边中找一条匹配的边。

因为对于每个点都有且仅有一条边和它匹配，因此对于每个连通块，我们都要求它的点数和边数相同，否则就直接报告无解。也就是说，我们首先要求所有的连通块都是一棵基环树，这个可以使用并查集简单判断。

对于每一棵基环树而言，环外面接出来的链上的点答案都是可以确定的，因为每个点能和它匹配的边显然只有它父亲到它自己这一条。而对于每一个环，匹配的方式显然也只有逆时针匹配和顺时针匹配这两种，它们对应的权值和也都可以用一遍 dfs 简单求出。

不难发现这么一件事：如果我们知道了某种方案左边选手的权值和为 $a$，那么该方案右边选手的权值和一定是 $m-a$，也就是说我们只要能够维护出来一边选手的权值和就行了。

因此我们考虑直接用一个背包来记录左边的权值和可能是多少，将每个环的两种匹配方式对左边权值和的贡献当作一个物品，每次扔进背包里更新即可，统计答案时同样也只需要枚举左边的权值和。

直接背包复杂度 $O(nm)$ 肯定是过不去的，但是我们只需要判定是否可行，可以直接使用 bitset 优化背包，时间复杂度 $O(\frac{nm}{\omega})$。

实测完全能过，并不需要其他优化（我最慢的点跑了 600ms 左右）。

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=(a);i<=(b);i++)
#define Rof(i,a,b) for(int i=(a);i>=(b);i--)
#define eb emplace_back
using namespace std;
typedef pair<int,int> pii;
const int N=5e5+5;
struct edge{int nxt,to,val;}e[N];
int n,k,cnt=1,head[N],deg[N];
bool vis[N];
bitset<N>dp;
void add_edge(int u,int v,int w){
	deg[u]++;deg[v]++;
	e[++cnt]={head[u],v,w};head[u]=cnt;
	e[++cnt]={head[v],u,w};head[v]=cnt;
}
struct DSU{  //并查集用于判基环树
	int fa[N],v[N],e[N];
	void init(){For(i,1,2*n) fa[i]=i,v[i]=1,e[i]=0;}
	int find(int x){
		if(x==fa[x]) return x;
		return fa[x]=find(fa[x]);
	}
	void merge(int x,int y){
		x=find(x);y=find(y);
		if(x==y) return ++e[y],void();
		if(v[x]>v[y]) swap(x,y);
		fa[x]=y;v[y]+=v[x];e[y]+=e[x]+1;
	}
}dsu;
int sum,sum1,sum2,ans=1e9;
void dfs(int now,int fe){  //计算环上两种匹配方式的贡献
	if(vis[now]) return;
	vis[now]=1;
	for(int i=head[now];i;i=e[i].nxt){
		int to=e[i].to,w=e[i].val;
		if(deg[to]!=2||(i^1)==fe) continue;
		if(now<=n) sum1+=w;
		if(to<=n) sum2+=w;
		dfs(to,i);break;
	}
}
void Main(){
	cin>>n>>k;
	dsu.init();
	For(i,1,2*n){
		int u,v,w;
		cin>>u>>v>>w;v+=n;
		add_edge(u,v,w);sum+=w;
		dsu.merge(u,v);
	}
	queue<int>q;
	For(i,1,2*n){
		if(dsu.v[dsu.find(i)]!=dsu.e[dsu.find(i)])  //该连通块不是基环树
			return cout<<"NO\n",void();
		if(deg[i]==1) q.push(i);
	}
	int ts=0;
	while(!q.empty()){
		int now=q.front();q.pop();
		vis[now]=1;
		for(int i=head[now];i;i=e[i].nxt){
			int to=e[i].to,w=e[i].val;
			if(vis[to]) continue;
			if(now<=n) ts+=w;  //先计算出接在环外边的链的贡献
			if(deg[to]==2) q.push(to);
			deg[to]--;
		}
	}
	dp[ts]=1;
	For(i,1,2*n){
		if(vis[i]||deg[i]!=2) continue;
		sum1=sum2=0;dfs(i,0);
		dp=(dp<<sum1)|(dp<<sum2);	
	}
	For(i,0,sum) if(dp[i]) ans=min(ans,llabs(sum-i-i));  //枚举左边的和
	if(ans<=k) cout<<"YES\n";
	else cout<<"NO\n";
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T=1;//cin>>T;
	while(T--) Main();
	return 0;
}


```

---

