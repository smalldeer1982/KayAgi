# [NAPC-#1] Stage3 - Jump Refreshers

## 题目背景

> ![](https://cdn.luogu.com.cn/upload/image_hosting/wkktxonu.png)

## 题目描述

**注意本题中 kid 的移动方式与 iw 游戏中不同（）。**

kid 面前有一个无穷大的竖直二维平面。坐标系 $x$ 轴正方向为从左到右，$y$ 轴正方向为从下到上。

地图（该平面）内有 $n$ 个**位置互不相同**的**可以无限重复使用**的跳跃球。当 kid 正好位于某跳跃球位置时，他可以让 shift 键按下，然后他会瞬间上升 $d$ 格（此期间不能左右移动）。他每秒往下坠落 $1$ 格，同时每秒 kid 可以选择：向左或向右移动 1 格，或者不移动。当 kid 不在跳跃球上时他不能起跳。

![](https://cdn.luogu.com.cn/upload/image_hosting/1abzjhjs.png)

上图是一个例子，蓝色区域表示 kid 在跳跃球（箭头）处起跳（$d=2$）后可以达到的区域。**kid 每秒时的横纵坐标只能是整数，即：我们认为他不能达到非整点位置。**

现在，kid 把存档放在了第 $c$ 个跳跃球处（即起点是第 $c$ 个跳跃球处；此时可以立即起跳）。定义 kid 的得分为他经过（即在某处起跳：显然起跳之后可以回到原位置）的**不同**跳跃球的个数。kid 想知道他可以最多获得多少得分（**不需要**（但可以）**回到起点**），请你告诉他吧。

再次提醒：**跳跃球可以无限重复使用，即 kid 可以在某个跳跃球上无限起跳。**

## 说明/提示

### 【数据范围】

**本题采用捆绑测试。**
$$
\def\r{\cr\hline}
\def\None{\text{None}}
\def\arraystretch{1.5}
\begin{array}{c|c|c|c}
\textbf{Subtask} & id= & \textbf{Sp. Constraints} & \textbf{Score}\r
\textsf1& 1\sim3,36 & n\leqslant10,T\leqslant10 & 10 \r
\textsf2& 4\sim7 & \sum n\leqslant200 & 15 \r
\textsf3& 8\sim13 & \mathbf A & 25 \r
\textsf4& 14\sim18 & \mathbf B & 10 \r
\textsf5& 19\sim35 & - & 40 \r
\end{array}
$$
其中 $\sum n$ 表示单测试点内所有 $n$ 的总和。

$id=1\sim3,36$ 表示 $id\in\{1,2,3,36\}$。
- 特殊性质 $\mathbf A$：保证对于任意不同跳跃球 $u,v$，如果 kid 理论上能从 $u$ 跳到 $v$（理论上：不考虑 kid 能否从起点到达 $u$ 的问题，下同），那么他理论上**一定不可以**从 $v$ 跳到 $u$。
- 特殊性质 $\mathbf B$：保证对于任意跳跃球 $u,v$，如果 kid 理论上能从 $u$ 跳到 $v$，那么他理论上**一定可以**从 $v$ 跳到 $u$。

注意上面的“从 $u$ 跳到 $v$"不一定非得一跳到位。比如样例 #1-2 中可以从第 $3$ 个跳到第 $5$ 个：$3\to2\to4\to5$。

对于 $100\%$ 的数据，$1\leqslant T\leqslant 1000$，$1\leqslant n\leqslant 3000$，$\sum n\leqslant 3000$，$1\leqslant d\leqslant 10^9$，$1\leqslant c\leqslant n$，$1\leqslant x_i,y_i\leqslant10^6$，$(x_i,y_i)$ 互不相同。

---
#### 【样例解释 #1-1】
![](https://cdn.luogu.com.cn/upload/image_hosting/zpc7sm2i.png)

$d=2$，容易发现离开初始位置就上不去了。所以 kid 要么往左边碰第 $2$ 个跳跃球，得分为 $2$；要么往右边跳，经过第 $3$ 和第 $4$ 个跳跃球，得分为 $3$。
#### 【样例解释 #1-2】
![](https://cdn.luogu.com.cn/upload/image_hosting/q8ks8qb4.png)

$d=3$，kid 可以先往下走一圈（$4\to3\to2\to4$）跳回起点，然后往右去碰第 $5$ 个球。左上角的第 $1$ 个跳跃球是碰不到的。
#### 【样例解释 #1-3】
![](https://cdn.luogu.com.cn/upload/image_hosting/akghkpe9.png)

通过最上面那个球是可以跳到右边的。
#### 【样例解释 #1-4】
![](https://cdn.luogu.com.cn/upload/image_hosting/50smzomm.png)

有 的 人 。

## 样例 #1

### 输入

```
4 0
4 2 1
2 4
1 1
5 2
4 1
5 3 4
1 7
2 4
3 2
4 5
8 2
4 1 2
1 1
1 2
1 3
4 1
4 2 1
1 1
4 1
1 4
4 4```

### 输出

```
3
4
4
1```

# 题解

## 作者：ycy1124 (赞：8)

### 题意
在一个平面中有 $n$ 个互不重叠的点，开始时你在点 $c$ 上。当你在点上时可以向上跳 $d$ 格，当你不在点上时每秒会下降 $1$ 格，同时可以向左或右移动一格，也可以不移动。问你最多可以到达多少个不同的点（相同的点可以重复经过）。
### 思路
不难想到，我们可以按点之间能否到达将题目给出的点连边，然后得到一张有向图，图上每个点的点权为 $1$。对于最终答案的路径，他是会有很多路径被重复经过的，这样会导致暴力的复杂度很高，于是我们可以对其进行缩点，因为缩点后图是没有环的，所以缩点后搜索的复杂度会降低很多，然后再搭配上最优性剪枝就可以通过此题。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>a[3001];
int idx=0,dfn[3001],low[3001],Color=0;
bool bj[3001];
int n,m,color[3001];
int ww[3001];
stack<int>q;
int d,c;
void read(int &x){//快读
	char ch=getchar();
	int f=1;
	x=0;
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			f=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-48;
		ch=getchar();
	}
	x*=f;
}
void dfs(int p){//tarjan内的搜索
	bj[p]=1;
	dfn[p]=low[p]=++idx;
	q.push(p);
	for(auto it:a[p]){
		if(!dfn[it]){
			dfs(it);
			low[p]=min(low[p],low[it]);
		}
		else{
			if(bj[it]){
				low[p]=min(low[p],dfn[it]);
			}
		}
	}
	if(dfn[p]==low[p]){
		Color++;
		while(q.top()!=p){
			bj[q.top()]=0;
			color[q.top()]=Color;
			q.pop();
			ww[Color]++;
		}
		bj[p]=0;
		q.pop();
		color[p]=Color;
		ww[Color]++;//缩点后的点权会改变，ww数组表示的是缩点后的点权
	}
}
void tarjan(){//tarjan缩点
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
			dfs(i);
		}
	}
}
vector<int>t[3001];
int ans[3001];
bool vis[3001];
void Dfs(int p,int www){
	vis[p]=1;
	ans[p]=max(ans[p],www);
	for(auto it:t[p]){
		if(!vis[it]&&www+ww[it]>ans[it]){//最优性剪枝
			Dfs(it,www+ww[it]);
		}
	}
	vis[p]=0;
}
int x[3001],y[3001];
int main(){
	int T,id;
	read(T);
	read(id);
	while(T){
		T--;
		idx=0;//多测清空
		for(int i=1;i<=n;i++){
			dfn[i]=0;
			low[i]=0;
			a[i].clear();
		}
		for(int i=1;i<=Color;i++){
			ans[i]=0;
			t[i].clear();
			ww[i]=0;
		}
		Color=0;
		read(n);
		read(d);
		read(c);
		while(!q.empty()){
			q.pop();
		}
		for(int i=1;i<=n;i++){
			read(x[i]);
			read(y[i]);
		}
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				if(y[i]-y[j]+d-abs(x[i]-x[j])>=0){//连边
					a[i].push_back(j);
				}
				if(y[j]-y[i]+d-abs(x[i]-x[j])>=0){
					a[j].push_back(i);
				}
			}
		}
		tarjan();
		for(int i=1;i<=Color;i++){//缩点
			for(int j=1;j<=n;j++){
				if(color[j]==i){
					for(auto it:a[j]){
						if(color[it]==i){
							continue;
						}
						t[i].push_back(color[it]);
					}
				}
			}
		}
		Dfs(color[c],ww[color[c]]);//跑一遍dfs求答案
		int wwww=0;	
		for(int i=1;i<=Color;i++){//枚举最大答案
			wwww=max(wwww,ans[i]);
		}
		printf("%d\n",wwww);//输出
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/179065547)。

---

## 作者：DevilsFlame (赞：8)

据题目所说，**他每秒往下坠落 $1$ 格，同时每秒 kid 可以选择：向左或向右移动 $1$ 格，或者不移动。** 意为从 $i$ 点至 $j$ 点需满足 $|j_x - i_x| + j_y - i_y \le 0$。   
需注意的是：坐标系 $x$ 轴正方向为**从左到右**，$y$ 轴正方向为**从下到上**。  
在每个跳跃球可以上升 $d$ 个或下坠，所以建有向图，连通条件为 $|j_x - i_x| + j_y - i_y \le d$。  
假使 $u$ 到 $v$ 有条路经可走，$v$ 到 $u$ 也油条路径，就可以缩点（如果缩点还不会就去这里：**[P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)**）。  
缩点后由有向图变为 **DAG**，问题也就简单了。  
每个跳跃球为 $1$ 分，包括初始跳跃球。用一数组来存储，注意 $n$ 数组。缩点后会有重边:
![](https://cdn.luogu.com.cn/upload/image_hosting/x4xp3gek.png)   
$1$，$2$，$3$ 为一集合，$4$，$5$ 为一集合，但有路径 $3-4$、$1-4$、$1-5$，所以就有 $2$ 条冗余的边！所以用双重 ```map``` 来判重  
（多组数据禁忌用 ```memset``` ）。  
具体代码如下：

```cpp
#include<bits/stdc++.h>
#define N 3005//  养成好习惯
using namespace std;
int T,id,n,m,d,a,b,c,ans;
int dfn[N],low[N],tot,stk[N],top;
int col,to[N],s[N],mm[N];
vector <int> e[N],c_e[N];
bool in[N];
struct Node
{
	int x,y;
}v[N];
inline void read(int &x)//  快读
{
	x = 0;
	int f = 1;
	char s = getchar();
	while(s < '0' || s > '9')
	{
		if(s == '-') f = -1;
		s = getchar();
	}
	while(s >= '0' && s <= '9')
	{
		x = x * 10 + s - 48;
		s = getchar();
	}
	x *= f;
	return;
}
inline void write(int x)//  快写
{
	if(x < 0)
	{
		putchar('-');
		x *= -1;
	}
	if(x > 9) write(x / 10);
	putchar(x % 10 + 48);
	return;
}
inline void tarjan(int x)// tarjan 缩点模版
{
	dfn[x] = low[x] = ++ tot;
	in[x] = 1;
	stk[++ top] = x;
	for(int i = 0;i < e[x].size();i ++)
	{
		int v = e[x][i];
		if(!dfn[v])
		{
			tarjan(v);
			low[x] = min(low[x],low[v]);
		}
		else if(in[v]) low[x] = min(low[x],dfn[v]);
	}
	if(dfn[x] == low[x])// 缩点
	{
		col ++;
		while(stk[top] != x)
		{
			in[stk[top]] = 0;
			to[stk[top]] = col;// 染色（加入同一集合
			s[col] ++;
			top --;
		}
		s[col] ++;
		to[x] = col;
		in[x] = 0;
		top --;
	}
	return;
}
inline void build()// 缩点建变
{
	map <int,map <int,bool> > pl;
	for(int i = 1;i <= n;i ++)
	{
		int u = to[i];// 代表点（染色
		for(int j = 0;j < e[i].size();j ++)
		{
			int v = to[e[i][j]];
			if(u == v || pl[u][v]) continue;
			//u == v  是为了防止自环
			//pl  避免重编增加时间复杂度
			pl[u][v] = 1;
			c_e[u].push_back(v);
		}
	}
	return;
}
inline int dfs(int x)// 找答案
{
	if(mm[x]) return mm[x];// 记忆化会吧
	int r = 0;
	for(int i = 0;i < c_e[x].size();i ++)
	    r = max(r,dfs(c_e[x][i]));
	mm[x] = (r + s[x]);
	return mm[x];
}
int main()
{
	read(T),read(id);
	while(T --)
	{
		tot = 0,col = 0,ans = 0;;
		read(n),read(d),read(c);
		for(int i = 1;i <= n;i ++)
		{
			read(v[i].y),read(v[i].x);// x、y 含义要注意,个人习惯x行y列
			s[i] = dfn[i] = low[i] = to[i] = mm[i] = 0;// 清空，不想用memset
		}
		for(int i = 1;i <= n;i ++)
			for(int j = 1;j <= n;j ++)
				if(i != j && abs(v[j].y - v[i].y) + v[j].x - v[i].x - d <= 0)// 建边，x、y为我个人习惯
					e[i].push_back(j);
		tarjan(c);
		build();
		write(dfs(to[c]));
		putchar('\n');
		for(int i = 1;i <= n;i ++) e[i].clear(),c_e[i].clear();// 勿忘清空
	}
	return 0;
}
```

望审核员大大通过

---

## 作者：Svemit (赞：6)

[blog](https://www.cnblogs.com/Svemit/p/17524346.html)

[传送门](https://www.luogu.com.cn/problem/P9431)

~~这个人赛时看错了几次题目导致样例调了 1h。~~
## Sol1: $n \leqslant 10, T \leqslant 10$

乱搞分。

枚举跳跃的顺序，判断可不可行，最后取最大值，复杂度 $O((n - 1 )!)$。

## Sol2: $B$

感觉跟正解没什么关系，先说这个。

- 特殊性质 $\mathbf B$：保证对于任意跳跃球 $u, v$，如果 kid 理论上能从 $u$ 跳到 $v$，那么他理论上**一定可以**从 $v$ 跳到 $u$。

两点一定互相可达，题目求的是能到的最大的点的数量。

并查集维护最大连通块大小即可。

## Sol3: $A$
 
提示正解的部分。

- 特殊性质 $\mathbf A$：保证对于任意不同跳跃球 $u,v$，如果 kid 理论上能从 $u$ 跳到 $v$（理论上：不考虑 kid 能否从起点到达 $u$ 的问题，下同），那么他理论上**一定不可以**从 $v$ 跳到 $u$。

一定没有环，所以建完图后一定是一个 DAG，直接在 DAG 上跑 dp。

## Sol4: 如何建图
如果点 $u$ 能跳到点 $v$ 的话，就连接一条 $u$ 向 $v$ 的边。

每下坠一格时，可以移动一格，所以 $y$ 坐标的差应该小于等于 $x$ 坐标的差。
```cpp
bool check(int a, int b)
{
	int x1 = x[a], x2 = x[b], y1 = y[a] + d, y2 = y[b];
	if(y1 < y2) return false;
	if(abs(x1 - x2) > y1 - y2) return false;
	return true;
}
```

## Sol5:
建完图之后显然不是 DAG，于是想到缩点，缩点完用 Sol3 的方法去 dp。
```cpp
bool check(int a, int b)
{
	int x1 = x[a], x2 = x[b], y1 = y[a] + d, y2 = y[b];
	if(y1 < y2) return false;
	if(abs(x1 - x2) > y1 - y2) return false;
	return true;
}
int h[N], nxt[M], to[M], cnt;
void add(int u, int v)
{
	to[++ cnt] = v, nxt[cnt] = h[u], h[u] = cnt;
}
int dfn[N], low[N], bel[N], tim, scc_cnt;
bool ins[N];
int siz[N], f[N], in_deg[N];
stack<int> s;
void tarjan(int u)
{
	dfn[u] = low[u] = ++ tim;
	ins[u] = true;
	s.push(u);
	for(int i = h[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(!dfn[v])
		{
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if(ins[v]) low[u] = min(low[u], dfn[v]);
	}
	if(low[u] == dfn[u])
	{
		int v;
		scc_cnt ++;
		do
		{
			siz[scc_cnt] ++;
			v = s.top();
			s.pop();
			ins[v] = false;
			bel[v] = scc_cnt;
		} while(v != u);
	}
}
vector<int> adj[N];
int top()
{
	queue<int> q;
	for(int i = 1; i <= scc_cnt; i ++) if(in_deg[i] == 0) q.push(i), f[i] = siz[i];
	while(q.size())
	{
		int u = q.front();
		q.pop();
		for(auto v : adj[u])
		{
			f[v] = max(f[v], f[u] + siz[v]);
			if(-- in_deg[v] == 0) q.push(v);
		}
	}
}
void init()
{
	for(int i = 1; i <= n; i ++) 
	{
		h[i] = 0;
		adj[i].clear();
		in_deg[i] = 0;
		f[i] = 0;
		siz[i] = 0;
		ins[i] = false;
		bel[i] = 0;
		nxt[i] = 0; 
		to[i] = 0;
		dfn[i] = 0;
		low[i] = 0;
	}
	cnt = scc_cnt = tim = 0;
}
void solve()
{
	cin >> n >> d >> c;
	
	for(int i = 1; i <= n; i ++) cin >> x[i] >> y[i];
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++) if(check(i, j) && i != j) add(i, j);
	for(int i = 1; i <= n; i ++) if(!dfn[i]) tarjan(i);
	for(int i = 1; i <= n; i ++)
		for(int j = h[i]; j; j = nxt[j])
			if(bel[i] != bel[to[j]]) adj[bel[to[j]]].push_back(bel[i]), in_deg[bel[i]] ++;
	queue<int> q;
	for(int i = 1; i <= scc_cnt; i ++) if(in_deg[i] == 0) q.push(i), f[i] = siz[i];
	while(q.size())
	{
		int u = q.front();
		q.pop();
		for(auto v : adj[u])
		{
			f[v] = max(f[v], f[u] + siz[v]);
			if(-- in_deg[v] == 0) q.push(v);
		}
	}
	cout << f[bel[c]] << '\n';
}
```

---

## 作者：y_kx_b (赞：4)

## Stage3 - Jump Refreshers

预计难度：\*1900 左右，绿。

前置芝士：有向图缩点。

---

### $\textbf{Sub }{\sf1}\textbf:$ $n\leqslant10$，$T\leqslant10$。

随便乱搞就行了吧/kel

我依然选择状压 dp。

[code。](https://www.luogu.com.cn/paste/s7juf7qw)

复杂度理论可以卡到 $O(n^42^n)$，但是实际中 $n=10$ 的完全图好像也只卡到了 $300\times2^{10}$。

### $\textbf{Sub }{\sf2}\textbf:$ $\sum n\leqslant200$。
唔，$n^3$ 做法，我也不知道咋搞）

### $\textbf{Sub }{\sf4}\textbf:$ $\mathbf B$。

既然跳过去就可以跳回来，那么直接搜索起点能到多少个球就行了呀。

[B code。](https://www.luogu.com.cn/paste/sq535rd2)

### $\textbf{Sub }{\sf3}\textbf:$ $\mathbf A$。

[把上面 $\mathbf B$ 写出来发现 dfs 有股图论的风格，于是考虑建图，当 kid 可以通过第 $i$ 个跳跃球跳到第 $j$ 个时，我们从 $i$ 往 $j$ 建边。]::::

因为 kid 跳过去就没法跳回来了，那么可以直接 dp 统计路径：设 $dp_u$ 为以 $u$ 为起点最多可以跳到的跳跃球的数量，那么显然 $dp_v=\max\limits_{u\to v\land u\not=v} dp_u+1$，其中 $u\to v$ 表示从 $u$ 可以直接跳到 $v$（同时 $v$ 不可能跳到 $u$）。最后输出最大值即可。

[A code。](https://www.luogu.com.cn/paste/vaedqc9z)


### $\textbf{Sub }{\sf5}\textbf:$ 无特殊限制。
考虑建图，当 kid 可以通过第 $i$ 个跳跃球跳到第 $j$ 个时，我们从 $i$ 往 $j$ 建边。$n^2$，非常暴力。

问题完美转化为在图上找以 $c$ 为起点的一条路径，让这条路径经过的不同点的数量最多，输出最多点数。

发现可以缩点，缩点后变成 DAG 就可以像上面 dp 了（只不过每个点带了点权，代表这个 scc 里原来有多少球）。

当然了，这个 dp 也可以换成 spfa 等最短路算法，输出缩点后以 c 点缩点后所在点为起点的最长路长度即可。

呜呜 出完后才发现好像就是[缩点板子](https://www.luogu.com.cn/problem/P3387)（

code：
```cpp
int a[N];
int head[N], to[M], ne[M], idx1 = 0;
void add(int u, int v) {
	to[idx1] = v, ne[idx1] = head[u], head[u] = idx1++;
}
int dfn[N], low[N], timer = 0;
int stk[N], top = 0; bool inst[N];
int bel[N], a2[N], scc_cnt = 0;
void tarjan(int u) {
	dfn[u] = low[u] = ++timer;
	inst[stk[top++] = u] = 1;
	for(int i = head[u]; ~i; i = ne[i]) {
		int v = to[i];
		if(!dfn[v])
			tarjan(v), low[u] = min(low[u], low[v]);
		else if(inst[v]) low[u] = min(low[u], dfn[v]);
	}
	if(dfn[u] == low[u]) {
		scc_cnt++; a2[scc_cnt] = 0;
		int y;
		do {
			y = stk[--top];
			inst[y] = 0;
			bel[y] = scc_cnt;
			a2[scc_cnt] += a[y];
		} while(y != u);
	}
}
int head2[N], to2[M], ne2[M], idx2 = 0;
void add2(int u, int v) {
	to2[idx2] = v, ne2[idx2] = head2[u], head2[u] = idx2++;
}
int dp_val[N];
int dp(int u) {//记搜
	assert(u);
	if(dp_val[u]) return dp_val[u];
	int res = a2[u];
	for(int i = head2[u]; ~i; i = ne2[i]) {
		int v = to2[i];
		res = max(res, a2[u] + dp(v));
	}
	return dp_val[u] = res;
}
int x[N], y[N];
bool major(int Testcase = 1) {
	int n = read(), d = read(), c = read();
	int siz_mem = sizeof(int) * (n + 5);
	memset(head, -1, siz_mem); idx1 = 0;
	for(int i = 1; i <= n; i++) a[i] = 1, x[i] = read(), y[i] = read();
	for(int u = 1; u <= n; u++) for(int v = 1; v <= n; v++)//暴力建图（）
		if(y[u] + d - y[v]/*下落时间*/>= abs(x[u] - x[v])/*横向移动所需时间*/)
			add(u, v);
/**/memset(dfn, 0, siz_mem);//dfn 相当于标记一个点是否被访问过，得清掉
/**/memset(bel, 0, siz_mem);//有些点可能不会被tarjan搜到 但还保存着上一次的 bel 信息
							//然后下面暴力建缩点图的时候就可能出现环（）
	timer = scc_cnt = 0;
	tarjan(c);
	
	memset(head2, -1, siz_mem); idx2 = 0;
	for(int u = 1; u <= n; u++) for(int i = head[u]; ~i; i = ne[i]) {
		int &v = to[i];
		if(bel[u] != bel[v]) add2(bel[u], bel[v]);
	}
	memset(dp_val, 0, siz_mem);
	printf("%d\n", dp(bel[c]));
	return Testcase;
}
int main() {
	int T = read(), id = read(); while(T--) major();
}
```
希望不要放过乱搞做法，我已经尽力把某些点造得奇奇怪怪的了（）qwq。

---

## 作者：Aventurine_stone (赞：2)

## 1. 题目分析
很显然，对于每一个点，我们可以依次枚举其他点，看此点是否能走到其他点，若能走到则连一条有向边，那么我们就可以在图上求解了。故这是一道图论题。
## 2. 题目做法
我们会发现，直接在一个有环的图上跑最长路可能有些困难。  
但是，既然有环的话。我们便可以用 tarjan 算法把图中的环缩成点，记录新图上每个点在原图环上的点数，重建一个图。  
然后我们便得到一个拓扑图，这样我们就可以很轻松地跑最长路了。  
### 注意
跑完 tarjan 建新图时，要判重边，不然很可能会超时。  
跑最长路时，不要用 SPFA。
## 3. 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3010,M=9000010;
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x;
}
int head[N],ne[M],e[M],idx;
inline void add(int x,int y)
{
	ne[++idx]=head[x];
	head[x]=idx;
	e[idx]=y;
}
int h2[N],ne2[M],e2[M],idx2;
inline void add2(int x,int y)
{
	ne2[++idx2]=h2[x];
	h2[x]=idx2;
	e2[idx2]=y;
}
int T,ID,n,d,st;
int dfn[N],low[N],cnt,biao;
int id[N],num[N],cb[N];
stack<int>s;
bool vis[N];
int t;
void tarjan(int x)//缩点 
{
	vis[x]=1;
	s.push(x);
	dfn[x]=low[x]=++biao;
	for(int i=head[x];i;i=ne[i])
	{
		int c=e[i];
		if(!dfn[c])
		{
			tarjan(c);
			low[x]=min(low[x],low[c]);
		}
		else if(vis[c])
			low[x]=min(low[x],dfn[c]);
	}
	if(low[x]==dfn[x])
	{
		cnt++;
		while(1)
		{
			t=s.top();
			s.pop();
			vis[t]=0;
			id[t]=cnt;
			num[cnt]++;//记录点数 
			if(t==x)
				return ;
		}
	}
}
int dist[N];
queue<int>q;
void tp(int x)//跑最长路 
{
	dist[x]=num[x];
	for(int i=cnt;i;i--)
	{
		for(int j=h2[i];j;j=ne2[j])
		{
			int c=e2[j];
			dist[c]=max(dist[c],dist[i]+num[c]); 
		}
	}
}
unordered_map<int,bool> o;
int x[N],y[N],maxx;
int main()
{
	T=read(),ID=read();
	while(T--)
	{
		n=read(),d=read(),st=read();
		idx=0;
		for(int i=1;i<=n;i++)
			head[i]=0,id[i]=0;
		for(int i=1;i<=n;i++)
			x[i]=read(),y[i]=read();
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(i==j)
					continue;
				t=y[i]-y[j]+d-abs(x[i]-x[j]);
				if(t>=0)
					add(i,j);
			}
		}
		cnt=biao=0;
		for(int i=1;i<=n;i++)
			dfn[i]=low[i]=0;
		tarjan(st);
		idx2=0;
		for(int i=1;i<=cnt;i++)
			h2[i]=0;
		for(int i=1;i<=n;i++)
		{
			if(!id[i])
				continue;
			for(int j=head[i];j;j=ne[j])
			{
				int c=e[j];
				if(!id[c])
					continue;
				if(id[i]!=id[c]&&!o[id[i] * 10000 + id[c]])//建新图时判重边 
				{
					add2(id[i],id[c]);
					o[id[i] * 10000 + id[c]]=1;
				}
			}
		}
		o.clear();
		for(int i=1;i<=cnt;i++)
			dist[i]=0;
		tp(id[st]);
		maxx=0;
		for(int i=1;i<=cnt;i++)
			maxx=max(maxx,dist[i]);
		printf("%d\n",maxx);
		for(int i=1;i<=cnt;i++)
			num[i]=0;
	}
	return 0;
}
```

---

## 作者：Melo_DDD (赞：2)

刚学缩点用来练手的，顺便还练了练动规，好题，记录一下。

# 题目大意

跳到一个球上得一分。

多测一定要清空。

# 题目实现

不看标签也能看出来是缩点。

很容易发现其实对答案有贡献的只有那几个球，所以可以把它们拿出来建图，但显然这几个球不可能正好组成一个 DAG，所以咱们把能到达的几个点建**有向边**缩成一个重新建图（每多一个球点权加 $1$）（所以要开两个结构体，我用的链式前向星）。结构体不用清空，因为后面的会覆盖前面的，而没被覆盖的也不会被访问。

```cpp
struct edge {
	int to ,nxt ,frm ;
};
edge e1[N * N] ,e2[N * N] ;
inline void add1 (int u ,int v) {
	e1[++ tot1].frm = u ;
	e1[tot1].nxt = head1[u] ;
	head1[u] = tot1 ;
	e1[tot1].to = v ;
}
inline void add2 (int u ,int v) {
	e2[++ tot2].nxt = head2[u] ;
	head2[u] = tot2 ;
	e2[tot2].to = v ;
}
```

咱们考虑缩点之前怎么建边：很简单，互相能到达的球之间建**有向边**，暴力跳就行。

问题在于如何判断是否可达，注意每下落一次可以向左或者向右动一次，所以水平方向的移动距离一定不大于竖直方向。

```cpp
inline bool judge (int p1 ,int p2) {
	int x1 = x[p1] ,x2 = x[p2] ,y1 = y[p1] ,y2 = y[p2] ;
	if (abs (x1 - x2) > y1 + d - y2) return false ;
	return true ;
}
```

然后是一个普普通通的缩点板子，缩完之后怎么建边？将所有建过的边遍历，只要其起点和终点不在同一连通块就行。

然后就是个简单的 DP 求最长路，或者用迪杰也不是不行。

## 代码

```cpp
#include <bits/stdc++.h>
#define rep(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
using namespace std ;
const int N = 3e3 + 7 ;
int t ,id ,n ,d ,c ,dfn[N] ,low[N] ,num[N] ,val[N] ,head1[N] ,tot1 ,head2[N] ,tot2 ,dcnt ,ccnt ,stk[N] ,stop ,a[N] ,dp[N] ,x[N] ,y[N] ;
bool instk[N] ;
inline int read () {
    char ch = getchar () ,f = 0 ;
	int t = 0 ;
    for( ;ch < '0' or ch > '9' ;ch = getchar ()) {
		if (! (ch ^ 45)) f = 1 ;
	}
    for( ;ch >= '0' and ch <= '9' ;ch = getchar ()){
		t = (t << 1) + (t << 3) + (ch ^ 48) ;
	}
    return f ? - t : t ;
}
struct edge {
	int to ,nxt ,frm ;
};
edge e1[N * N] ,e2[N * N] ;
#define mem(a ,b) memset (a ,b ,sizeof (a)) 
namespace shin {
	inline void init () {
		mem (dfn ,0) ;
		mem (low ,0) ;
		mem (num ,0) ;
		mem (val ,0) ;
		mem (head1 ,0) ;
		tot1 = 0 ;
		mem (head2 ,0) ;
		tot2 = 0 ;
		dcnt = 0 ;
		ccnt = 0 ;
		mem (stk ,0) ;
		mem (instk ,0) ;
		stop = 0 ;
		mem (dp ,0) ;
	}
	inline void add1 (int u ,int v) {
		e1[++ tot1].frm = u ;
		e1[tot1].nxt = head1[u] ;
		head1[u] = tot1 ;
		e1[tot1].to = v ;
	}
	inline void add2 (int u ,int v) {
		e2[++ tot2].nxt = head2[u] ;
		head2[u] = tot2 ;
		e2[tot2].to = v ;
	}
	inline void tarjan (int cur) {
		low[cur] = dfn[cur] = ++ dcnt ;
		stk[++ stop] = cur ;
		instk[cur] = true ;
		for (int i = head1[cur] ;i ;i = e1[i].nxt) {
			int nex = e1[i].to ;
			if (! dfn[nex]) {
				shin :: tarjan (nex) ;
				low[cur] = min (low[cur] ,low[nex]) ;
			}
			else if (instk[nex]) {
				low[cur] = min (low[cur] ,dfn[nex]) ;
			}
		}
		if (low[cur] == dfn[cur]) {
			ccnt ++ ;
			int now ;
			do {
				now = stk[stop --] ;
				instk[now] = false ;
				num[now] = ccnt ;
				val[ccnt] ++ ;
			} while (now != cur) ;
		}
	}
	inline void get_ans (int cur) {
		if (dp[cur]) return ;
		dp[cur] = val[cur] ;
		for (int i = head2[cur] ;i ;i = e2[i].nxt) {
			int nex = e2[i].to ;
			shin :: get_ans (nex) ;
			dp[cur] = max (dp[cur] ,val[cur] + dp[nex]) ;
		}
	}
	inline bool judge (int p1 ,int p2) {
		int x1 = x[p1] ,x2 = x[p2] ,y1 = y[p1] ,y2 = y[p2] ;
		if (abs (x1 - x2) > y1 + d - y2) return false ;
		return true ;
	}
} 
int main () {
	t = read () ;
	id = read () ;
	do {
		shin :: init () ;
		n = read () ;
		d = read () ;
		c = read () ;
		rep (i ,1 ,n ,1) {
			x[i] = read () ;
			y[i] = read () ;
		}
		rep (u ,1 ,n ,1) {
			rep (v ,1 ,n ,1) {
				if (u == v) continue ;
				if (shin :: judge (u ,v)) {
					shin :: add1 (u ,v) ;
				}
			}
		}
		rep (i ,1 ,n ,1) {
			if (! dfn[i]) shin :: tarjan (i) ;
		}
		rep (i ,1 ,tot1 ,1) {
			if (num[e1[i].frm] == num[e1[i].to]) continue ;
			shin :: add2 (num[e1[i].frm] ,num[e1[i].to]) ; 
		}
		shin :: get_ans (num[c]) ;
		cout << dp[num[c]] << '\n' ;
	} while (t -- != 1) ;
	return 0 ;
}
```

###### 你是否承认卡芙卡和狼谷的美貌举世无双？

---

## 作者：tuntunQwQ (赞：1)

我们可以对于每一个跳跃球 $u$，向所有在 $u$ 处起跳时能够到达的跳跃球 $v$ 连一条有向边。因为在一个强连通分量中的点可以互相到达，所以考虑将整张图缩点，缩点后每个点的点权就是原图中该强连通分量中点的个数。记忆化搜索求出从第 $i$ 个点出发可以走到的最长路径，最后取最大值即可。

代码如下，可供参考：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3005,M=N*N;
int n,t,d,c,id,x[N],y[N],h[N],e[M],nxt[M],idx;
int dfn[N],low[N],tmc,stk[N],top,ccb[N],ccb_cnt;bool in_st[N];
pair<int,int> p[M];int m;
int h1[N],w1[N],e1[M],nxt1[M],idx1,f[N];
void add(int a,int b){
	e[++idx]=b,nxt[idx]=h[a],h[a]=idx;
}
void add1(int a,int b){
	e1[++idx1]=b,nxt1[idx1]=h1[a],h1[a]=idx1;
}
void tarjan(int u){
	dfn[u]=low[u]=++tmc;
	stk[++top]=u;
	in_st[u]=1;
	for(int i=h[u];i;i=nxt[i]){
		int v=e[i];
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if(in_st[v])low[u]=min(low[u],low[v]);
	}
	if(dfn[u]==low[u]){
		ccb_cnt++;
		do{
			in_st[stk[top]]=0;
			ccb[stk[top]]=ccb_cnt;
			w1[ccb_cnt]++;
		}while(stk[top--]!=u);
	}
}
int dfs(int u){
	int maxx=0;
	for(int i=h1[u];i;i=nxt1[i]){
		int v=e1[i];
		if(!f[v])maxx=max(maxx,dfs(v));
		else maxx=max(maxx,f[v]);
	}
	f[u]=max(w1[u]+maxx,f[u]);
	return f[u];
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t>>id;
	while(t--){
		idx1=idx=m=0;
		for(int i=1;i<=n;i++){
			dfn[i]=low[i]=h[i]=0;
		}
		for(int i=1;i<=ccb_cnt;i++){
			f[i]=w1[i]=h1[i]=0;
		}
		ccb_cnt=0;
		cin>>n>>d>>c;
		for(int i=1;i<=n;i++)cin>>x[i]>>y[i];
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(i!=j&&y[i]+d-y[j]>=abs(x[i]-x[j]))add(i,j),p[++m]={i,j};
			}
		}
		for(int i=1;i<=n;i++){
			if(!dfn[i])tarjan(i);
		}
		for(int i=1;i<=m;i++){
			if(ccb[p[i].first]!=ccb[p[i].second])add1(ccb[p[i].first],ccb[p[i].second]);
		}
		cout<<dfs(ccb[c])<<'\n';
	}
	return 0;
}
```

---

## 作者：qiuxiangyu (赞：1)

# 前置知识
Tarjan 求强连通分量（不会的同学请左转，[P2863](https://www.luogu.com.cn/problem/P2863)）。

拓扑排序（不会的同学请右转，[B3644](https://www.luogu.com.cn/problem/B3644)）。

# 本题解法

## 建模

读完题意就会发现，能对答案起到贡献的其实只有给定位置的那 $n$ 个点，二维平面内的其他点其实并不会对答案产生任何的贡献。所以我们可以把**这 $n$ 个点从二维平面中单独拿出来**。根据题意，对于任意两个给定位置的点，只会有能到与到不了这两种情况，所以我们可以根据这个进行建图，若 $i$ 在游戏中可以直接到达 $j$，我们便从 $i$ 向 $j$ 连一条边。那什么时候叫做 “可以直接到达” 呢？我们会发现，当 $i$,$j$ 两点之间的**横坐标方向上的距离小于等于**他们**纵坐标方向上的最大距离**时，才可以从 $i$ 直接到达 $j$。也就是当 $y_i+d-{y_j}\ge\mid {x_i-x_j}\mid$ 的时候，才建边（$+d$ 是因为可以**多争取到一些时间来左右移动**）。注意到此时 $i$ 可以到 $j$，但 $j$ 不一定可以到 $i$，所以应该建一条**有向边**。这里需要我们两两枚举端点进行**暴力**连边，时间复杂度为 $O(n^2)$。

## 缩点

### 思路

建完图后，就要思考如何利用我们建的图来解决本题。会发现我们所建的图是一个**有向图**，但是其中可能会存在**环**。而如果存在环，那就意味着环上的点都是**两两可达**的，那么无论我们从哪一个点出发，我们都可以将这环上的点都走一遍，也就是说如果进入了这个环，环上的点都一定会对答案进行贡献，那么我们就可以将每一个环都给看成是一个**整体**，加答案时整体加上**环上点的个数**就行了。这也就是缩点。

### 做法

我们利用 Tarjan 求出每一个点所属的强连通分量（$id_i$）和每一个强连通分量中点的个数（$size_i$）之后，因为我们是要达到**简化环**的目的，所以同一个强连通分量（环）里的点就不用连边了，**不同**强连通分量的点才需要连边。也就是说，对于 $i,j$ 这两个在原图上有边的点，若 $id_i\ne id_j$，这两个点不是同一个强连通分量中的点，我们就将它们在**新图**上建一条**有向边**。时间复杂度为 $O(n+m)$。

### 缩点代码

``` c++
for(int i=1;i<=n;i=-~i){
	for(int j=0;j<g[i].size();j=-~j){
		int y=g[i][j];//原图上的边
		if(id[i]!=id[y]){
			g2[id[i]].push_back(id[y]);//新图建边
		}
	}
}

```
## 拓扑排序 + DP

### 思路

我们会发现，当我们将原图中的环给缩掉之后，新图就一定是一个**有向无环图**，并且每一个点上有一个权值 $size_i$，表示这个点所代表的强连通分量中有几个可以**被一起捆绑的点**。现在我们的问题就转化为，从一个起点 $c$ 出发，沿着新建的图经过一个点时便会获得它对应点权的分数，问能获得的**最大**分数是多少？这个问题其实就是一个拓扑排序问题，我们在拓扑排序的过程中，**顺便更新它相邻的节点，最终一定可以把整个图给遍历完**。由于我们要算从给定起点出发，能经过路径上点的点权和最大为多少，我们就可以将新图建一个**反图**，在反图上跑拓扑排序，**起点就是原来的新图上的终点，终点便自然是原来的新图上的起点即为 $c$ 点所对应的强连通分量的编号**。

### 做法

设状态 $f_i$ 表示从**某一个起点**出发，到当前 $i$ 这个点所能获得的**点权和**的最大值（注意这里的点 $i$ 是缩点之后的编号）。初始值也就是对于**入度**为 $0$ 的点，$f_i=size_i$。对于一条边 $u \rightarrow v$，转移方程便是 $f_v=\max(f_v,f_u+size_y)$，意思就是从走向 $v$ 的点中选取一个值最大的点来继续走下去。答案便是 $f[id[c]]$。时间复杂度为 $O(n+m)$。

## 注意事项
由于本题目是多组数据，请注意**每一组数据都要对数组进行清空！！！**。

~~多测不清空, oier 两行泪。~~

## 全部代码

总的时间复杂度为 $O(n^2)$。

``` c++
#include<bits/stdc++.h>
using namespace std;
const int N=3010;
int f[N],id[N],scc,x[N],y[N],ans,idx,sz[N];
int T,o,n,D,S,dfn[N],low[N],s[N],top,d[N];
bool vis[N],in[N];
vector<int> g[N],g2[N];
queue<int> q;
inline bool cmp(register int i,register int j){//判断从 i 到 j 是否可以有一条有向边
	if(y[i]+D-y[j]>=abs(x[i]-x[j])) return true;
	return false;
}

// Tarjan 求强连通分量模板
inline void tarjan(register int u){
	vis[u]=true;
	dfn[u]=low[u]=++idx;
	s[++top]=u;
	in[u]=true;
	for(int i=0;i<g[u].size();i=-~i){
		int y=g[u][i];
		if(!dfn[y]){
			tarjan(y);
			low[u]=min(low[u],low[y]);
		}else if(in[y]){
			low[u]=min(low[u],dfn[y]);
		}
	}
	if(dfn[u]==low[u]){
		scc++;
		while(1){
			int t=s[top];
			id[t]=scc;
			sz[scc]++;
			in[t]=false;
			top--;
			if(t==u) break;
		}
	}
}
signed main(){
	scanf("%d %d",&T,&o); 
	while(T--){
		scanf("%d %d %d",&n,&D,&S);
		
		//多测要清空
		idx=ans=top=scc=0;
		for(int i=1;i<=n;i=-~i){
			vis[i]=in[i]=false;
			sz[i]=f[i]=s[i]=dfn[i]=low[i]=d[i]=id[i]=0;
			g[i].clear();
			g2[i].clear();
		}
		for(int i=1;i<=n;i=-~i){
			scanf("%d %d",&x[i],&y[i]);
		}
		for(int i=1;i<=n;i=-~i){
			for(int j=1;j<=n;j=-~j){
				if(i==j) continue;//不能建出自环
				if(cmp(i,j)){
					g[i].push_back(j);//暴力 O(n^2) 建模
				}
			}
		}
		
		tarjan(S);//规定了起点,就从起点开始跑
		
		//缩点
		for(int i=1;i<=n;i=-~i){
			for(int j=0;j<g[i].size();j=-~j){
				int y=g[i][j];
				if(id[i]==0||id[y]==0) continue;
				//谨防从起点到不了的点会因为强连通分量的编号为 0 而导致的一些离谱错误
				if(id[i]!=id[y]){
					//建原图缩点后的的反向图
					g2[id[y]].push_back(id[i]);
					d[id[i]]++;
				}
			}
		}
		
		//拓扑排序
		for(int i=1;i<=scc;i=-~i){
			if(d[i]==0){
				f[i]=sz[i];//初始化,任选入度为 0 的起点
				q.push(i);
			}
		}
		while(!q.empty()){
			int t=q.front();
			q.pop();
			for(int i=0;i<g2[t].size();i=-~i){
				int y=g2[t][i];
				// DP 状态转移
				f[y]=max(f[y],f[t]+sz[y]);
				--d[y];
				if(d[y]==0){
					q.push(y);
				}
			}
		}
		
		//答案
		printf("%d\n",f[id[S]]);//注意是起点所对应的编号,而不是 f[S]
	}
	return 0;
}

```
## 巩固提升
有兴趣的同学可以尝试一下这个 [P3387](https://www.luogu.com.cn/problem/P3387)，是差不多的。

---

## 作者：IC0CI (赞：1)

## 题面分析

若设定若能从一个点 $u$ 到达另一个点 $v$，则由 $u$ 向 $v$ 建立一条有向边。

则题目要求从起点 $c$ 开始走一条路径最多能达到多少点。

注意到有些点之间可以互相跳，则这些点可以看做一个点，则容易想到 tarjan 强连通分量缩点。

### 关于具体实现

若能从一个点 $u$ 到达另一个点 $v$，即满足 $|{a_i}_x - {a_j}_x| \le {a_i}_y + d - {a_j}_y$，则由 $u$ 向 $v$ 建立一条有向边。

对这个图进行缩点，新图的点权是强连通分量的大小再将新图遍历求一条路径的最大权值。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long

int rd() //省略快读

const int N = 3e3 + 3;
int T,id;
struct node
{
    int x,y;
}a[N];
vector<int> adj[N];
vector<int> sc[N];

int low[N],dfn[N],scc[N],stk[N],cnt,tim,top,num[N];

void tarjan(int u)
{
    dfn[u] = low[u] = ++tim;
    stk[++top] = u;
    for(auto v : adj[u])
    {
        if(!dfn[v]) tarjan(v),low[u] = min(low[u],low[v]);
        else if(!scc[v]) low[u] = min(low[u],low[v]);
    }
    if(low[u] == dfn[u])
    {
        cnt++;
        int tmp;
        do
        {
            tmp = stk[top--];
            scc[tmp] = cnt;
            num[cnt]++;
        }while(tmp != u);
    }
}

int b[N];

int dfs(int u)
{
    if(b[u]) return b[u];
    int ans = num[u];
    for(auto v : sc[u]) ans = max(ans,num[u] + dfs(v));
    b[u] = ans;
    return ans;
}

signed main()
{
    T = rd(),id = rd();
    while(T--)
    {
        memset(num,0,sizeof num);
        memset(dfn,0,sizeof dfn);
        memset(low,0,sizeof low);
        memset(scc,0,sizeof scc);
        memset(stk,0,sizeof stk);
        memset(b,0,sizeof b);
        tim = top = cnt = 0;
        int n = rd(),d = rd(),c = rd();
        for(int i = 1;i <= n;i++) a[i] = {rd(),rd()},adj[i].clear(),sc[i].clear();
        for(int i = 1;i <= n;i++)
            for(int j = 1;j <= n;j++)
                if(i != j && abs(a[i].x - a[j].x) <= a[i].y + d - a[j].y)
                    adj[i].emplace_back(j);
        for(int i = 1;i <= n;i++) if(!dfn[i]) tarjan(i);
        for(int i = 1;i <= n;i++) for(auto v : adj[i]) if(scc[i] != scc[v]) sc[scc[i]].emplace_back(scc[v]);
        cout << dfs(scc[c]) << '\n';
    }
    return 0;
}
```

---

## 作者：Vct14 (赞：1)

问题可以转化为输出一个图上所有以 $c$ 为起点的路径中，经过的不同点数量的最大值。

直接建图显然无法通过，考虑缩点，形成一个有向无环图，然后 dp 统计路径。

由于出题人大佬已经讲的很详细了，所以这里我来讲讲缩点。

------------

首先要了解几个概念：

- 强连通：在一个有向图里，若有两点 $u$ 和 $v$，由 $u$ 有一条路径可以走到 $v$，由 $v$ 也有一条路径可以走到 $u$，我们就称 $u$ 和 $v$ 强连通。

- 强连通分量：在一个有向图中，若有一个子图中每两个点都强连通，我们就叫这个子图叫做强连通分量。

缩点就是把有向图中的强连通分量缩成一个点，一般用于处理有向图的连通性问题。

那么就有一个问题了：怎样找强连通分量？

我们可以使用 tarjan 算法，一个基于 dfs 的算法，每个强连通分量为搜索树中的一棵子树。搜索时，把当前搜索树中未处理的节点加入一个堆栈，回溯时可以判断栈顶到栈中的节点是否为一个强连通分量。

这里给出伪代码和模板。

```
tarjan(u){
　　DFN[u]=Low[u]=++Index //节点 u 设定次序编号和 Low 初值
　　Stack.push(u)//将节点 u 压入栈中
　　for each (u,v) in E//枚举每一条边
　　　　if(v is not visted)
			tarjan(v)//继续向下找
			Low[u]=min(Low[u], Low[v])
		else if(v in S)//如果节点 u 还在栈内
			Low[u]=min(Low[u], DFN[v])
	if(DFN[u]==Low[u])//如果节点 u 是强连通分量的根
　　	repeat v=S.pop//将 v 退栈，为该强连通分量中一个顶点
　　print v
　　until(u==v)
}
```

模板，可以输出一个图中的所有强连通分量：

```c++
 #include<cstdio>
 #include<algorithm>
 #include<string.h>
 using namespace std;
 struct node {
     int v,next;
 }edge[1001];
  int DFN[1001],LOW[1001];
 int stack[1001],heads[1001],visit[1001],cnt,tot,index;
void add(int x,int y)
{
     edge[++cnt].next=heads[x];
     edge[cnt].v = y;
     heads[x]=cnt;
    return ;
 }
 void tarjan(int x)//代表第几个点在处理。递归的是点。
 {
     DFN[x]=LOW[x]=++tot;// 新进点的初始化。
     stack[++index]=x;//进站
     visit[x]=1;//表示在栈里
    for(int i=heads[x];i!=-1;i=edge[i].next)
     {
         if(!DFN[edge[i].v]) {//如果没访问过
            tarjan(edge[i].v);//往下进行延伸，开始递归
             LOW[x]=min(LOW[x],LOW[edge[i].v]);//递归出来，比较谁是谁的儿子／父亲，就是树的对应关系，涉及到强连通分量子树最小根的事情。
        }
        else if(visit[edge[i].v ]){  //如果访问过，并且还在栈里。
             LOW[x]=min(LOW[x],DFN[edge[i].v]);//比较谁是谁的儿子／父亲。就是链接对应关系
         }
     }
     if(LOW[x]==DFN[x]) //发现是整个强连通分量子树里的最小根。
    {
         do{
            printf("%d ",stack[index]);
             visit[stack[index]]=0;
             index--;
         }while(x!=stack[index+1]);//出栈，并且输出。
         printf("\n");
     }
     return ;
 }
 int main()
 {
     memset(heads,-1,sizeof(heads));
     int n,m;
     scanf("%d%d",&n,&m);
    int x,y;
     for(int i=1;i<=m;i++)
     {
         scanf("%d%d",&x,&y);
        add(x,y);
     }
    for(int i=1;i<=n;i++)
         if(!DFN[i])  tarjan(i);//当这个点没有访问过，就从此点开始。防止图没走完
    return 0;
 }
 ```
 
然后，就要连接缩点后的图了。

先记录一下每条边，然后判断，如果原图一条边上两点属于不同的强连通分量，则两个强连通分量相连，就可以对这两个分量连接。此时我们就可以得到缩点后的图。

```c++
for( int i = 1 ; i <= m ; ++ i ) {
	int a , b ;
	scanf("%d%d", &a , &b );
	G[a].push_back(b);
	way[i].from = a , way[i].to = b ;
}
for( int i = 1 ; i <= m ; ++ i ) {//连接缩点后的图 
	int a = d[way[i].from] ;
	int b = d[way[i].to] ;
	if( a != b )//不属于同一分量
		g[a].push_back(b); 
}
```

### 参考

[wust_cyl](https://blog.csdn.net/wust_cyl?type=blog) 的博客。

---

## 作者：_JF_ (赞：0)

[Link ](https://www.luogu.com.cn/problem/P9431)

现在还有这么经典的题？？当作训练模板的。

我们把每个球看成一个点，如果 $x$ 能到 $y$ ，连一条从 $x$ 到 $y$ 的有向边。

判断是容易的，注意到下落一格的时候能走的范围是上一个的范围各往外扩展 $1$。这样就能求从 $x$ 到 $y$ 的纵坐标时候的覆盖范围。

然后容易发现，对于一个 SCC，我可以在里面随便游走并获得全部点的贡献。并且我们可以选择任意点的出去，所以可以缩点。

然后我们缩完了以后就直接拓扑排序 dp 即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =4001;
vector<int> g[N],G[N];
int n,d,c,in[N],dp[N],SCC,Val[N],tot,dfn[N],low[N],vis[N],id[N],X[N],Y[N];
stack<int> sta;
bool Vus[N]; 
bool Judge(int x,int y){
	int nowx=X[x],nowy=Y[x],nowx1=X[y],nowy1=Y[y];
	int op;
	if(nowy>nowy1)	op=1; else	op=-1;
	int len=d+op*abs(nowy-nowy1);
	if(abs(nowx-nowx1)>len)	return false;
	return true;
}
void Tarjan(int u){
	dfn[u]=low[u]=++tot,vis[u]=1,sta.push(u);
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(!dfn[v])	Tarjan(v),low[u]=min(low[u],low[v]);
		else if(vis[v]==1)	low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		SCC++;
//		if(SCC==2)	cout<<u<<endl;
		while(sta.top()!=u)	vis[sta.top()]=2,id[sta.top()]=SCC,Val[SCC]++,sta.pop();
		vis[u]=2,id[u]=SCC,Val[SCC]++,sta.pop();
	} 
}
void rbuild(){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(i==j)	continue;
			if(Judge(i,j)&&(id[i]!=id[j]))	G[id[i]].push_back(id[j]),in[id[j]]++;
		}
}
void Topo(){
	queue<int> q; 
	int ans=1;
	for(int i=1;i<=SCC;i++)	if(in[i]==0)	q.push(i);
	Vus[id[c]]=true,dp[id[c]]=Val[id[c]],ans=max(ans,dp[id[c]]);
	while(!q.empty()){
		int u=q.front(); q.pop();
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i];
			in[v]--;
			if(Vus[u]==true)	Vus[v]=true,dp[v]=max(dp[v],dp[u]+Val[v]),ans=max(ans,dp[v]);
			if(in[v]==0)	q.push(v);	
		}
	}
	cout<<ans<<endl;
}
void Clear(){
	while(!sta.empty())	sta.pop();
	tot=SCC=0;
	for(int i=1;i<=n;i++)	low[i]=dfn[i]=0,Vus[i]=0,vis[i]=0,id[i]=0,Val[i]=0,in[i]=0,dp[i]=0,G[i].clear(),g[i].clear();
}
int main(){
	int t,Id;
	cin>>t>>Id;
	while(t--){
		cin>>n>>d>>c;
		for(int i=1;i<=n;i++)	cin>>X[i]>>Y[i];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				if(i==j)	continue;
				if(Judge(i,j))	
					g[i].push_back(j);
			}
	//	for(int i=1;i<=n;i++){
	//		cout<<i<<' ';
	//		for(int j=0;j<g[i].size();j++)	cout<<g[i][j]<<' ';
	//		cout<<endl;
	//	}
		for(int i=1;i<=n;i++)	if(!vis[i])	Tarjan(i);
		rbuild(),Topo();
		Clear();
	}
	return 0;
} 
/*
5 3 4
1 7
2 4
3 2
4 5
8 2
*/ 
```

---

## 作者：_H17_ (赞：0)

## 题目分析

是[【模板】缩点](/problem/P3387) 的双倍经验。

考虑缩点加拓扑 DP（当然也可以记搜）。

至于连边，如果两个点下落时间比移动距离大（或者相等）就连到一起。

缩点使用 Tarjan 算法，本质是从根遍历图，形成搜索树。利用返祖边回到前面的点来判断是否在同一个强联通分量中。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int N=3001,M=9000001;
int T,id,n,m,d,c,tot,cnt,tot2,x[N],y[N],head[N],scc[N],dfn[N],low[N],vis[N],head2[N],ind[N],f[N],siz[N];
stack<int>st;
struct Edge{
	int nxt,frm,tar;
	Edge(int nxt=0,int frm=0,int tar=0):nxt(nxt),frm(frm),tar(tar){}
}edge[M];
struct Edge2{
    int nxt,tar;
    Edge2(int nxt=0,int tar=0):nxt(nxt),tar(tar){}
}edge2[M];
bool check(int a,int b){//是否可以连边
    return(abs(x[a]-x[b])<=y[a]-y[b]+d)&&(a^b);
}
void add(int u,int v){
	edge[++tot]=Edge(head[u],u,v),head[u]=tot;
	return;
}
void add2(int u,int v){
	edge2[++tot2]=Edge2(head2[u],v),head2[u]=tot2;
	return;
}
void tarjan(int u){//缩点
	low[u]=dfn[u]=++cnt,vis[u]=1;
	st.push(u);
	for(int i=head[u],v;i;i=edge[i].nxt){
		v=edge[i].tar;
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
	    else if(vis[v])
	    	low[u]=min(low[u],low[v]);
	}
	if(dfn[u]==low[u]){
		int v;
		while(!st.empty()){
		    v=st.top(),scc[v]=u,vis[v]=0,siz[u]++;
            st.pop();
			if(u==v)
				break;
		}
	}
	return;
}
int dfs(int u){//记搜
    if(f[u])
        return f[u];
    f[u]=0;
    for(int i=head2[u],v;i;i=edge2[i].nxt)
        f[u]=max(f[u],dfs(v=edge2[i].tar));
    return(f[u]+=siz[u]);
}
void Main(){
    memset(head,0,sizeof(head)),
    memset(head2,0,sizeof(head2)),
    memset(siz,0,sizeof(siz)),
    memset(dfn,0,sizeof(dfn)),
    memset(f,0,sizeof(f));
    tot=tot2=cnt=0;
	cin>>n>>d>>c;
	for(int i=1;i<=n;i++)
		cin>>x[i]>>y[i];
	for(int i=1;i<=n;i++)
	    for(int j=1;j<=n;j++)
	        if(check(i,j))
	            add(i,j);//建图
	m=tot;//注意：如果你后面有 m，那么务必初始化
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i);//缩点
	for(int i=1,u,v;i<=m;i++){
		u=scc[edge[i].frm],v=scc[edge[i].tar];
		if(u^v)
			add2(u,v);//重建图
	}
	cout<<dfs(scc[c])<<'\n';//输出答案
	return;
}
int main(){
    ios::sync_with_stdio(0);
    for(cin>>T>>id;T;--T)
        Main();
    return 0;
}
```

---

## 作者：lfxxx (赞：0)

对于两个跳跃点 $A,B$ 可以从 $A$ 走到 $B$ 当且仅当 $A_{y} + d - B_{y} \geq \max(A_x,B_x) - \min(A_x,B_x)$，所以不放把满足这个要求的 $A,B$ 连边 $A \to B$ 而原问题被我们转化成选择一条路径最大化经过的不同点数量，考虑 tarjan 缩点，一个强连通分量内的所有点显然可以全部走到，而剩下的问题便是缩点完的 DAG 上的最长路，考虑拓扑排序求解即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e3+114;
int X[maxn],Y[maxn],n,c,d;
vector<int> edge[maxn],E[maxn];
int dfn[maxn],low[maxn],dfncnt,vis[maxn],col[maxn],sz[maxn],cl;
stack<int> st;
void tarjan(int u){
    dfn[u]=low[u]=++dfncnt;
    vis[u]=true;
    st.push(u);
    for(int v:edge[u]){
        if(dfn[v]==0){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(vis[v]==true) low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u]){
        cl++;
        while(st.top()!=u){
            vis[st.top()]=false;
            col[st.top()]=cl;
            sz[cl]++;
            st.pop();
        }
        vis[u]=false;
        col[u]=cl;
        sz[cl]++;
        st.pop();
    }
}
int use[maxn];
void dfs(int u){
    use[u]=true;
    for(int v:E[u]) if(use[v]==false) dfs(v);
}
int In[maxn],dp[maxn];
void build(){
    for(int u=1;u<=n;u++){
        for(int v:edge[u]){
            int U=col[u],V=col[v];
            if(U!=V){
                E[U].push_back(V);
            }
        }
    }
}
void topo(){
    queue<int> q;
    dfs(col[c]);
    for(int u=1;u<=cl;u++){
        for(int v:E[u]){
            if(use[u]==true&&use[v]==true){
                In[v]++;
            }   
        }
    }
    dp[col[c]]=sz[col[c]];
    q.push(col[c]);
    while(q.size()){
        int u=q.front();
        q.pop();
        for(int v:E[u]){
            if(use[v]==false) continue;
            dp[v]=max(dp[v],dp[u]+sz[v]);
            In[v]--;
            if(In[v]==0) q.push(v);
        }
    }
}
void work(){
    cin>>n>>d>>c;
    for(int i=1;i<=cl;i++) E[i].clear(),dp[i]=sz[i]=use[i]=In[i]=0;
    cl=0;
    for(int i=1;i<=n;i++) dfn[i]=low[i]=vis[i]=col[i]=0,edge[i].clear();
    dfncnt=0;
    for(int i=1;i<=n;i++) cin>>X[i]>>Y[i];
    for(int u=1;u<=n;u++){
        for(int v=1;v<=n;v++){
            if(u==v) continue;
            if(Y[u]+d-Y[v]>=abs(X[u]-X[v])){
                edge[u].push_back(v);
            }
        }
    }
    for(int i=1;i<=n;i++) if(dfn[i]==0) tarjan(i);
    build();
    topo();
    int mx=0;
    for(int i=1;i<=cl;i++) mx=max(mx,dp[i]);
    cout<<mx<<"\n";
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T,id;
    cin>>T>>id;
    while(T--) work();
    return 0;
}
```


---

