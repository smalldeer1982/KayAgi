# 『MGOI』Simple Round I | C. 魔法禁林

## 题目背景

> 战斗的意义是为了生存，在这个竞争激烈的世界里，只有不断变强才能得以生存。——殿堂魔法士 S

## 题目描述

开学的第一天，小 M 迫不及待地计划着前往神秘的禁林。

小 M 拥有两个重要的属性，魔力值和生命值。非常特别的是，初始时，这两个值可以由小 M **任意决定**。

禁林可以看作一张 $n$ 个点 $m$ 条边的无向简单连通图。小 M 将在禁林里面行走，从起点 $s$ 走到 $t$。

每经过一条边，小 M 的**魔力值**都会减去 1。同时，每条边上有一个具有攻击力属性的魔兽，小 M 要与之战斗。若小 M 经过这条边之前的魔力值为 $k$，这条边上魔兽的攻击力为 $w$，那么经过这条边时发生的战斗将会消耗 $\left\lfloor \dfrac{w}{k} \right\rfloor$ 的**生命值**。魔兽不会被打败，因此**多次经过同一条边，每次都会发生战斗**。

**小 M 需要保证，当他的魔力值消耗完时，他的生命值为 0，且此时走到 $t$ 点。**

你需要求出小 M 初始时需要的最小生命值。

## 说明/提示

**【样例 1 解释】**

初始时，小 M 选择魔力值为 $2$，生命值为 $4$。

- $1\rightarrow2$：魔力值剩余 $1$，生命值剩余 $4 - \left\lfloor \frac{2}{2} \right\rfloor=3$。
- $2\rightarrow3$：魔力值剩余 $0$，生命值剩余 $3 - \left\lfloor \frac{3}{1} \right\rfloor=0$。

可以证明 $4$ 为小 M 初始时需要的最小生命值。

**【数据范围】** 

**本题采用 Subtask 捆绑测试。**

对于所有数据，$1 \le n \le 20000$，$1 \le m \le 40000$，$1\le s,t,u,v\le n$，$s\ne t$，图为无向简单连通图，$0\le w\le 100$。

| Subtask | $n$ | $m$ | $w\le$ | 分值 |
| :------------: | :----------: | :----------: | :-----------: | :----------------:|
| $1$ | $5$ | $10$ | $10$ | $11$ |
| $2$ | $2000$ | $4000$ | $10$ | $27$ |
| $3$ | $20000$ | $40000$ | $1$ | $19$ |
| $4$ | $20000$ | $40000$ | $100$ | $43$ |

## 样例 #1

### 输入

```
3 3 1 3
1 2 2
1 3 5
3 2 3```

### 输出

```
4```

## 样例 #2

### 输入

```
5 10 1 5
2 1 3
3 1 7
4 2 4
5 3 9
5 1 7
2 3 2
5 4 6
1 4 10
5 2 5
3 4 10```

### 输出

```
6```

# 题解

## 作者：WsW_ (赞：24)

### 更新：

这是一篇**已通过**的题解。

* $2023.08.06$ 全角空格改半角空格，顺手改了几个标点，完善了一些说明。
* $2023.11.25$ 补上缺失的空格。

感谢指出问题

---
### 总思路
要我们开始就确定一个 $k$ 很难，但根据题目要求，到达终点时 $k=0$。  
而此题中是无向图，因此我们反着跑。一开始 $k=0$，每走一步 $k\gets k+1$，从终点跑去起点即可。  
后面的思路都是直接按反走说的，即后文“终点”为题目“起点”。

--- 
#### 一、直接反跑单源最短路  
套上 dijkstra 板子，发现此题多了一个量 $k$，怎么办？  
在 $dist$ 数组中新增一维，对于 $dist_{i,j}$ 意为：$k=i$，到点 $j$ 时所需的最小生命值。
其他同 dijkstra 板子。

$38$ 分，后两个 subtask 空间炸了。

---
#### 代码与[提交记录](https://www.luogu.com.cn/record/119347691)
```cpp
#include<bits/stdc++.h>
using namespace std;

struct node{
	int val,next,to;
}edg[80005];
int elen;
struct point{
	int ans,cnt,x;
	bool operator < (const point &A)const{
		return ans>A.ans;
	}
};

priority_queue<point> q;

int x,y,z;
int n,m,s,t;
int ans[20003][20003];//此为dist数组
int head[20003];
int fans;

void add(int u,int v,int val){
	elen++;
	edg[elen].to=v;
	edg[elen].val=val;
	edg[elen].next=head[u];
	head[u]=elen;
	
}

signed main(){
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			ans[i][j]=1e9;
		}
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
		add(y,x,z);
	}
	swap(s,t);
	ans[1][s]=0;
	q.push({0,1,s});
	while(!q.empty()){
		point xx=q.top();
		q.pop();
		y=xx.cnt;
		x=xx.x;
		for(int i=head[x];i;i=edg[i].next){
			int to=edg[i].to;
			int cost=edg[i].val;
			if(ans[y+1][to]>ans[y][x]+cost/y){
				ans[y+1][to]=ans[y][x]+cost/y;
				q.push({ans[y+1][to],y+1,to});
			}
		}
	}
	fans=1e9;
	for(int i=1;i<=n;i++)fans=min(fans,ans[i][t]);
	printf("%d",fans);
	return 0;
}
```

---
### 二、剪枝  
由于前面是空间炸了，说明正确性是没问题的，接着优化空间。  
看了下数据范围，发现 $0\le w\le 100$，不禁想起某次模拟赛的第一题的思路：当达到某个状态时，后续无论怎样变化，答案不会改变。  

本题中扣血的方法是：扣 $\left\lfloor\dfrac{w}{k}\right\rfloor$ 的血量，因此当 $k>w$ 时不会扣血。而数据范围 $w\le 100$，所以当 $k>100$ 时，后面无论怎样走都不会扣血。  
题目中保证是连通图，所以 $k>100$ 时我们可以从当前位置无伤走到终点。  
我们记录答案的 $dist$ 数组第一维就只用开到 $100$，当然数组要稍微开大点。  
跑最短路的时候如果 $k>100$，那直接记录答案，跳过后续操作即可。

$100$ 分。  

---
### 代码与[提交记录](https://www.luogu.com.cn/record/119366774)
```cpp
#include<bits/stdc++.h>
using namespace std;

struct node{
	int val,next,to;
}edg[80005];
int elen;
struct point{
	int cnt,x;
};
queue<point> q;

int x,y,z;
int n,m,s,t;
bool vis[103][20003];
int ans[103][20003];//此为dist数组
int head[20003];
int fans=1e9;

void add(int u,int v,int val){
	elen++;
	edg[elen].to=v;
	edg[elen].val=val;
	edg[elen].next=head[u];
	head[u]=elen;
	
}

signed main(){
 	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
 	cin>>n>>m>>s>>t;
	for(int i=1;i<=101;i++){
		for(int j=1;j<=n;j++){
			ans[i][j]=1e9;
		}
	}
	for(int i=1;i<=m;i++){
		cin>>x>>y>>z;
		add(x,y,z);
		add(y,x,z);
	}
	swap(s,t);
	ans[1][s]=0;
	q.push({1,s});
	while(!q.empty()){
		point xx=q.front();
		q.pop();
		y=xx.cnt;
		x=xx.x;
		vis[y][x]=0;
		if(y>100){
			fans=min(fans,ans[y][x]);
			continue;
		}
		for(int i=head[x];i;i=edg[i].next){
			int to=edg[i].to;
			int cost=edg[i].val;
			if(ans[y+1][to]>ans[y][x]+cost/y){
				ans[y+1][to]=ans[y][x]+cost/y;
				if(!vis[y+1][to]){
					q.push({y+1,to});
					vis[y+1][to]=1;
				}
			}
		}
	}
	for(int i=1;i<=101;i++)fans=min(fans,ans[i][t]);
	cout<<fans;
	return 0;
}
```

---

## 作者：信息向阳花木 (赞：19)

（这是一篇已经过了的题解，改动了一下代码）

赛时第一眼看，是个无向图，求一个点到另外一个点的最小值，诶，这不裸的最短路嘛，然后兴高采烈地倒着跑了个 `dijkstra`，喜提 $30$ 分。仔细一看，$w \le 100$，发现当 $k > 100$ 时，生命就是永恒的，于是加了个剪枝，就过啦。

具体地，正常的最短路量有一个，本题有两个。于是我们定义 $dist_{i,j}$ 表示当前魔力值为 $i$ 走到 $j$ 的最小生命值。每倒着走一条边，$k$ 就多了 $1$。当 $k > 100$ 时，往后无论怎么走，生命值都不会减少，$k$ 就不用加了，直接跳过这个状态即可。其他和裸最短路没啥区别。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define PII pair<int, pair<int, int> >
#define x first
#define y second

const int N = 20010, M = 80010;

inline void in(int &x)
{
    x = 0; bool f = 0; char c = getchar();
    while(c < '0' || c > '9')
    {
        if(c == '-') f = 1;
        c = getchar();
    }
    while(c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c & 15);
        c = getchar();
    }
    x = f ? -x : x;
}

inline void out(int x)
{
    if(x < 0) putchar('-'), x = -x;
    if(x / 10) out(x / 10);
    putchar((x % 10) | 48);
}

int n, m, s, t, ans = 0x3f3f3f3f;
int h[N], e[M], ne[M], w[M], idx;
int dist[210][N], res[N];
bool st[210][N];
priority_queue<PII, vector<PII>, greater<PII> > q;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
    return;
}

void dijkstra()
{
    memset(dist, 0x3f, sizeof dist);
    dist[0][s] =0;
    q.push({0, {0, s}});

    while (!q.empty())
    {
        PII p = q.top();
        q.pop();

        int id = p.second.second, k = p.second.first;
        //对于一个  PII，first 表示最小生命值，second.first 表示当前魔法值，second.second 表示当前结点编号 
        if(st[k][id]) continue;
        st[k][id] = 1;

        if(k > 100) { ans = p.first; continue; } //剪枝，注意这里要记录一下答案（改动的地方，不然会被 hack）

        for (int i = h[id]; ~i; i = ne[i])
        {
            int j = e[i];
            if(dist[k + 1][j] > dist[k][id] + w[i] / (k + 1))
            {
                dist[k + 1][j] = dist[k][id] + w[i] / (k + 1);
                q.push({dist[k + 1][j], {k + 1, j}});
            } //更新状态 
        }
    }
    return;
}

int main()
{
    memset(h, -1, sizeof h);

    in(n); in(m); in(t); in(s); //倒着做 
    while (m -- )
    {
        int x, y, z;
        in(x); in(y); in(z);
        add(x, y, z); add(y, x, z);
    }

    dijkstra();

    for(int i = 0; i <= 101; i ++ ) ans = min(ans, dist[i][t]);
    printf("%d\n", ans);

    return 0;
}

```

---

## 作者：Register_int (赞：17)

绷不住了。

题面给出了 $w\le100$ 的限制，就说明，只要我们起始状态的魔力值 $\ge 100$ 都无法影响到生命值。考虑倒着从 $t$ 走到 $s$，那么步数在 $100$ 以上的都是白走。

考虑 $dp$。设 $dp_{u,k}$ 表示走到 $u$ 点用 $k$ 步生命值的最小值，那么有：

$$dp_{u,k}=\min_{(u,v,w)\in E}dp_{v,k-1}+\left\lfloor\dfrac wk\right\rfloor$$

大力就做完了。复杂度 $O((\max w)(n+m))$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e4 + 10;

vector<pair<int, int>> g[MAXN];

int n, m, s, t; ll dp[2][MAXN], ans;

int main() {
	scanf("%d%d%d%d", &n, &m, &s, &t);
	memset(dp[0], 0x3f, sizeof dp[0]);
	for (int i = 1, u, v, w; i <= m; i++) {
		scanf("%d%d%d", &u, &v, &w);
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	}
	dp[0][t] = 0, ans = LLONG_MAX; 
	for (int i = 1; i <= 100; i++) {
		memset(dp[i & 1], 0x3f, sizeof dp[i & 1]);
		for (int u = 1; u <= n; u++) {
			for (auto x : g[u]) {
				int v = x.first, w = x.second;
				dp[i & 1][u] = min(dp[i & 1][u], dp[~i & 1][v] + w / i);
			}
		}
		ans = min(ans, dp[i & 1][s]);
	}
	printf("%lld", ans);
}
```

---

## 作者：哈哈人生 (赞：14)

## 题外话
**谁说这题 dfs 过不了的？我偏要写一篇 dfs 题解（出题人别打我）。**
## [题目传送门](https://www.luogu.com.cn/problem/P9504)

## 思路
这道题的题意其实可以转化成这样（就是我们倒过来想）：从 $t$ 点往 $s$ 点走，初始状态下魔法值和生命值都为 $0$。每走一格魔法值加一；生命值加 $\left\lfloor \dfrac{w}{k} \right\rfloor$，其中 $k$ 为当前魔法值加一，$w$ 为这一步到下一步的边上的魔兽的攻击力。这样我们 dfs 搜索，用链接表记录图，搜到 $s$ 时用打表记录最小值，代码如下。
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int p,w;
	node(int x,int y){p=x,w=y;}
};
vector<node> v[20005];
int n,m,s,e,x,y,w,book[20005],minn=1e9;
void dfs(int p,int mf,int sm){
	if(sm>=minn)return;//小小剪纸
	if(p==s){
		minn=min(sm,minn);//打表
		return;
	}
	for(int i=0;i<v[p].size();i++){
		if(book[v[p][i].p]==0){
			book[v[p][i].p]=1;//标记走过
			dfs(v[p][i].p,mf+1,sm+floor(v[p][i].w/(mf+1)));
			book[v[p][i].p]=0;
		}
	}
}
signed main(){
	cin>>n>>m>>s>>e;
	for(int i=1;i<=m;i++){
		cin>>x>>y>>w;
	    v[x].push_back(node(y,w));//链接表记录
	    v[y].push_back(node(x,w));
	}
	dfs(e,0,0);
	cout<<minn;
	return 0;
}
```
能有这种思路很不错，那么恭喜你拿到了[三十分](https://www.luogu.com.cn/record/119320864)！（~~君子怎能苟居三十分~~）。

可是我们的目标是一百分，所以还得接着努力。我们发现这种思路好是好，但会有错误答案，为什么呢？因为有一种特别~~恶心~~神奇的情况，那就是：我们可以反复走一格一条边，使步数 $k$ 越来越大，直到比所有的 $w$ 都大，导致 $\left\lfloor \dfrac{w}{k} \right\rfloor=0$，那样我们就可以畅通无阻，随便走生命值都不会接着增加。这种情况我们的 dfs 是遍历不到的，因为它有 $book$ 数组标记，不能重复走一个点，所以当这种情况出现是最小值时，记录的最小值就错了。可是删了 $book$ 数组程序好像就会陷入死循环，然后爆零两行泪，所以到底怎么办呢？

~~是时候展现真正的技术了：~~ 我们其实真的可以把 $book$ 数组删了，只要判断上面所说的这种情况是否是当前情况下的最小值。如果是，就更新最小值然后回溯。不是，就接着遍历普通情况。因为普通情况中的死循环情况其实就是我们上面所说的这种情况（不断走同一条边）。如果出现死循环情况，我们上面所说的这种情况会先判断到并且回溯，根本不给它死循环的机会。这就是把普通情况的死循环判断改成了特殊情况，一举两得，妙！

代码如下，这就能开心的过了吧？
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int type;
inline type read(){
	type x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
inline void write(type x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x / 10);
	putchar(x%10+'0');
}
struct node{
	int p,w;
	node(int x,int y){p=x,w=y;}
};
vector<node> v[20005];
int n,m,s,e,x,y,w,minn=1e9,maxw=-1;
void dfs(int p,int mf,int sm){
	if(sm>=minn)return;
	if(p==s){
		minn=min(sm,minn);
		return;
	}
	for(int i=0;i<v[p].size();i++){
			if(v[p][i].w/(mf+1)==0)minn=min(sm,minn);
			else minn=min(minn,sm+(v[p][i].w-(mf+1)+1)*v[p][i].w/(mf+1));
			if(sm>=minn)return;//如果是最小值回溯
			dfs(v[p][i].p,mf+1,sm+v[p][i].w/(mf+1));//往下就说明不是最小值，代码接着跑
	}
}
signed main(){
	n=read(),m=read(),s=read(),e=read();
	for(int i=1;i<=m;i++){
		x=read(),y=read(),w=read();
		maxw=max(maxw,w);
	    v[x].push_back(node(y,w));
	    v[y].push_back(node(x,w));
	}
	dfs(e,0,0);
	write(minn);
	return 0;
}
```
如果你提交了这个代码，那么又恭喜你：[五十七分](https://www.luogu.com.cn/record/119352419)！（~~给你个眼神自己体会~~）。

我们可以发现，我们成功的把错误答案变成了超时（感谢良心的出题人）。要放弃了吗？不！我们要坚持，才能胜利。于是我们开始常数优化，另外再把链接表改成链式前向星。代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int type;
inline type read(){
	type x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
inline void write(type x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x / 10);
	putchar(x%10+'0');
}
struct node{
	int p,ne,w;
}eg[500005];
int h[200005],tot=0;
int n,m,s,e,x,y,w,minn=205,maxw=-1;
void dfs(int p,int mf,int sm){
	if(sm>=minn)return;
	if(p==s){
		minn=min(sm,minn);
		return;
	}
	for(int i=h[p];i;i=eg[i].ne){
		if(eg[i].w/(mf+1)==0)minn=min(sm,minn);
		else minn=min(minn,sm+(eg[i].w-(mf+1)+1)*eg[i].w/(mf+1));
		if(sm>=minn)return;
		dfs(eg[i].p,mf+1,sm+eg[i].w/(mf+1));
	}
}
void add(int a,int b,int c){
	eg[++tot]=node{b,h[a],c};
	h[a]=tot;
}
signed main(){
	n=read(),m=read(),s=read(),e=read();
	for(int i=1;i<=m;i++){
		x=read(),y=read(),w=read();
	    add(x,y,w);
	    add(y,x,w);
	}
	dfs(e,0,0);
	write(minn);
	return 0;
}
```
一百分！哦（此处省略激动的话语）。终于过了，感谢出题人提供的这样一道好题。

## 结语
虽然这个方法没有标准解法跑的快，但简单易懂（~~主要是适合本蒟蒻写~~）。最后也希望大家坚持不懈，能够题题通过！
### 请读者诚信粘贴题解，遵守洛谷社区规则，另外，点个赞呗。

---

## 作者：CSP_Sept (赞：12)

这是下派验题人题解。前往 [T4 题解](https://www.luogu.com.cn/blog/supervise/solution-lgr148-d)。

## 题意

给定一张 $n$ 个结点，$m$ 条边的无向连通图，现在要求从 $s$ 点走到 $t$ 点。

初始有两个参数 $k,l$，每经过一条边权为 $w$ 的边，$k$ 会减去 $1$，$l$ 会减去 $\left\lfloor\dfrac wk\right\rfloor$（这里是经过该边前的 $k$）。一条边重复经过多次依然如此。

求出一条路径，使得满足**最后 $\boldsymbol{k,l}$ 均为 $\boldsymbol{0}$** 的最小 $l$ 初始值。

$1\le n\le 2\times 10^4$，$1\le m\le 4\times 10^4$，$0\le w\le 100$。

## 解法

当时 xht 给这道题时没有给范围（「先没给数据范围，想看看你能搞出什么复杂度的做法」），所以手捏了个 $O(nw)$ 的做法。下面是初始一边想一边反馈的思路，应该挺值得借鉴的。

首先，考虑到由于 $k$ 初始值与选择的路径直接相关而并不确定，正着做显然不太优，所以从 $t$ 向 $s$ 考虑。

这样我们只需让 $k$ 初始为 $1$，便可以不用改变题目的前提，每次经过一条边时让 $k$ 加上 $1$ 即可。而不需关心其他问题。

下面考虑到到达某边时，该边对 $l$ 的贡献，**仅与 $\boldsymbol{k}$ 与选择的边的 $\boldsymbol{w}$ 有关**。这一看就很 dp 啊！

于是考虑设计状态，这个状态得把当前处在的结点与此时的 $k$ 扔进去。

所以设一下 $dp_{u,i}$ 表示到达点 $u$ 时已经经过了 $i$ 条边。这里 $i$ 相当于是 $k-1$。

转移是显然的！

$$
dp_{v,i+1}=\min\limits_{\operatorname{exist}(u\to v)}\left\{dp_{u,i}+\dfrac{w_{u\to v}}{i+1}\right\},
$$

这样转移一下就行了。

但是，这样复杂度还不是最优的，因为这时我们可能会面临**一条边经过无限次**的危险。

考虑优化，注意到下面的性质。

性质：如果经过一条边时，对 $l$ 的贡献已经可以为 $0$，则经过剩下的所有边贡献都是 $0$。

这是因为，当我们经过某边贡献为 $0$ 时，再次经过该边返回贡献同样为 $0$。于是可以经过该边无限次使得 $k$ 变为【无限】，则贡献函数 $\Delta(w,k)$ 自然为 $0$。

这里【无限】其实只要是 $w_{\max}+1$ 就行了，大家发现了吗？

那么加上这个优化后，状态数只有 $O(nw)$ 了。可以开始写了。

## 代码示范

我们先熟练地写了一个 dfs。

```cpp
void dfs(int x, int num) {
	if (x == s || num > wm) {
		ans = min(ans, dp[x][num]);
		return;
	}
	int len = e[x].size();
	for (int i = 0 ; i < len ; i++) {
		int nxt = e[x][i].to, w = e[x][i].w;
		dp[nxt][num + 1] = min(dp[nxt][num + 1], dp[x][num] + (w / (num + 1)));
		dfs(nxt, num + 1);
	}
	return;
}
```

但它 TLE 了。这是因为在 dfs 深度搜索的时候，有很多状态是重复的，一个状态 $(v,i)$ 可能对应着很多条路径，特别是 $i$ 比较大的时候。

所以我们先更新完某一层 $i$ 的所有 $v$，再去更新 $i+1$ 层。就可以避免状态的重复。

这不就是 bfs 吗！我们下面给出代码，这个代码复杂度是严格 $O(nw)$ 的。

```cpp
void bfs(int num) {
	for (int x = 1 ; x <= n ; x++) {
		if (dp[x][num] == inf)
			continue;
		if (num > wm || x == s)
			ans = min(ans, dp[x][num]);
		int len = e[x].size();
		for (int i = 0 ; i < len ; i++) {
			int nxt = e[x][i].to, w = e[x][i].w;
			dp[nxt][num + 1] = min(dp[nxt][num + 1], dp[x][num] + (w / (num + 1)));
		}
	}
	if (num > wm)
		return;
	bfs(num + 1);
}
```

我并没有 AC 记录，因为并不是我提交的。但是大家肯定能相信它可以 AC 吧，因为这篇题解很深刻。

---

## 作者：Walter_Fang (赞：8)

[原题](https://www.luogu.com.cn/problem/P9504)

## 思路/解析

笔者的思路不是很正经，但可以通过此题。思路为：宽搜+卡常。

我们使用链式前向星存储这张图，用二维数组 $f$ 保存当前步数，然后根据题意进行宽搜，这样可以通过 `Substack 1&2`。

对于 `Substack 3`：

注意到 $w\le 1$，因此答案只有可能是 $0$ 或 $1$。因此当权值 $z$ 只包含 $0$ 或 $1$ 时，我们只需要特判，当权值全为 $1$ 时，输出 $1$，否则输出 $0$。

对于 `Substack 4`：

使用快读+`register int`通过本 `Substack`。

至此，本题已 AC。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e4+10;
int n,m,st,ed,head[N],f[N][510],u,v,sx,sy,sz,fx,fy,fz,cnt,x,y,z,ma=INT_MIN,mi=INT_MAX;
struct Node{int x,y;};
queue<Node>q;
struct Edge{int to,nxt,val;}E[N<<1];
void add(int x,int y,int z){E[++cnt]={y,head[x],z};head[x]=cnt;}
namespace FastIO {
	char *p1, *p2, buf[1 << 14];
	#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, (1 << 14), stdin), p1 == p2) ? EOF : *p1++)

	template <typename T>
	inline void read(T& x) {
    	x = 0;
    	register int t = 1;
    	register char ch = getchar();
    	while (ch < '0' || ch > '9') {
        	if (ch == '-')
            	t = -1;
        	ch = getchar();
    	}
    	while (ch >= '0' && ch <= '9'){
        	x = (x << 1) + (x << 3) + (ch ^ 48);
        	ch = getchar();
    	}
    	x *= t;
	}

	template <typename T>
	void write(T x) {
    	if (x < 0) {
        	putchar('-');
        	x = -x;
    	}
    	if (x > 9) write(x / 10);
    	putchar(x % 10 ^ 48);
	}
	template <typename T>
	inline void writeln(T x, char sep = '\n') {
		write(x);
		putchar(sep);
	}
}
using namespace FastIO;
int main(){
	read(n);read(m);read(st);read(ed);
	for(register int i=1;i<=m;++i){
		read(x),read(y),read(z);
		add(x,y,z),add(y,x,z),ma=(z>ma)?z:ma;
	}
	if(ma<=1){
		for(register int i=head[ed];i;i=E[i].nxt)if(!E[i].val)return cout<<0,0;
		return cout<<1,0;
	}
	q.push({ed,1});
	while(!q.empty()){
	register int u=q.front().x,fy=q.front().y,fz=f[u][fy-1];q.pop();
		if(fy>=482)break;
		for(register int i=head[u];i;i=E[i].nxt){
			register int v=E[i].to,sx=fz+E[i].val/fy,sy=fy+1;
			if(f[v][fy]<=sx&&f[v][fy])continue;
			q.push({v,sy});f[v][fy]=sx;
		}
	}
	for(register int i=0;i<=482;++i)if(f[st][i])mi=(f[st][i]<mi)?f[st][i]:mi;
	cout<<mi;
}
```

---

## 作者：船酱魔王 (赞：6)

# P9504 『MGOI』Simple Round I | C. 魔法禁林

## 题意回顾

一个人有魔法值 $ g $ 和生命值 $ l $，每走完一条边（设边权为 $ w $），$ l \leftarrow l-\lfloor \frac{w}{g} \rfloor $，然后 $ g \leftarrow g-1 $，要求**最后一次**到达终点时 $ g $ 和 $ l $ 正好为 $ 0 $。

求最小初始生命值。

图无向连通，$ n \le 20000 $，$ m \le 40000 $，$ w \le 100 $。

## 分析

考虑魔法值大于 $ 100 $ 的时候，显然生命值一定不掉，而我们要关心的状态只有点号和魔法值，生命值是要求的数。因此我们设计状态 $ dp_{u,i} $ 表示 $ u $ 点 $ i $ 魔法值之后，到达终点至少需要多少生命值的消耗。因此对于每条边（$ u $ 和 $ v $ 连接，边权 $ w $）设计状态转移方程（注意转移两次，$ u, v $ 互相分别转移，这里给出了其中一次的方程，另一次只需把 $ u,v $ 倒过来即可）：

$$ dp_{u,i}\leftarrow \min\{dp_{u,i},dp_{v,i-1}+\lfloor \frac{w}{i} \rfloor\} $$

因为转移方程是倒序的，因此初始状态为 $ dp_{t,0} $。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 2e4 + 5;
const int M = 4e4 + 5;
int n, m, s, t;
int u[M], v[M], w[M];
int dp[N][105];
int main() {
	cin >> n >> m >> s >> t;
	for(int i = 1; i <= m; i++) {
		cin >> u[i] >> v[i] >> w[i];
	} 
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j <= 100; j++) {
			dp[i][j] = 1e6 + 5;
		}
	}
	dp[t][0] = 0;
	for(int j = 1; j <= 100; j++) {
		for(int i = 1; i <= m; i++) {
			dp[v[i]][j] = min(dp[v[i]][j], dp[u[i]][j - 1] + w[i] / j);
			dp[u[i]][j] = min(dp[u[i]][j], dp[v[i]][j - 1] + w[i] / j);
		}
	}
	int ans = 1e6 + 5;
	for(int i = 1; i <= n; i++) {
		ans = min(ans, dp[i][100]);
	}
	for(int i = 1; i <= 100; i++) {
		ans = min(ans, dp[s][i]);
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：LiJoQiao (赞：3)

[题目链接](https://www.luogu.com.cn/problem/P9504) [评测记录](https://www.luogu.com.cn/record/119372267)  
分享一个分层图的做法。  

由题意可知本题的所需生命值在路径中是单调不减的，题目本质是一个最短路。

从起点开始跑的话由于不知道魔力值和生命值，不好搞，但是最后到达终点时的魔力值和生命值一定为 $0$，因此可以反跑最短路。

但只当做一个 $n$ 个点 $m$ 条边的无向简单连通图来做会发现边权 $w$ 的影响是会随着魔力值 $k$ 变化的，此时一般的 Dijkstra 的做法无法保证。  

如果我们将魔力和所需生命值同时记录并松弛连接的节点，该题最短路做法就是正确的。  
于是我们可以想到分层图，来记录每层的魔力值。

由于边权的范围比较小，可以考虑以此为层数建分层图。  

当然分层图建多了也没有关系，因为这也符合题意，所需的血量在一条路径上是单调不减的。  
可以尝试下建最大的 $\max_{i=1}^{m} \{w\}$ 层图，我懒狗直接多建了点。  

最后直接遍历每层的 $s$ 点所需生命值即可。

注意数据范围。  

代码如下。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=2e4+10,MAXM=4e4+10,INF=0x3f3f3f3f,MAXW=100+5;
struct EDGE
{
    int v,w,nxt;
}edge[(MAXM<<1)*MAXW];
struct node
{
    int u,dis;
    bool operator<(const node a)const
    {
        return dis>a.dis;
    }
};
priority_queue<node> q;
int n,m,cnt,moli[MAXN*MAXW],head[MAXN*MAXW],dis[MAXN*MAXW]/*dis表示生命值*/;
bool vis[MAXN*MAXW];
inline int read()
{
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
void add(int u,int v,int w)
{
    ++cnt;
    edge[cnt].v=v;
    edge[cnt].w=w;
    edge[cnt].nxt=head[u];
    head[u]=cnt;
}
void dijkstra(int s)
{
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    q.push((node){s,dis[s]});
    while(!q.empty())
    {
        node a=q.top();q.pop();
        int u=a.u;
        if(vis[u])continue;
        vis[u]=1;
        int tmoli=moli[u]+1;
        for(int i=head[u];i;i=edge[i].nxt)
        {
            int v=edge[i].v,w=edge[i].w;
            int adis=w/tmoli,tdis=adis+dis[u];
            if(tdis<dis[v])
            {
                dis[v]=tdis;
                moli[v]=tmoli;
                q.push((node){v,dis[v]});
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int s,t;
    n=read();m=read();s=read();t=read();
    for(int i=1;i<=m;i++)
    {
        int u=read(),v=read(),w=read();
        for(int j=1;j<MAXW;j++)
        {
            add(u+(j-1)*n,v+n*j,w);
            add(v+(j-1)*n,u+n*j,w);
        }
    }
    dijkstra(t);
    int ans=INF;
    for(int i=0;i<MAXW;i++)
    {
        ans=min(ans,dis[s+i*n]);
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Night_sea_64 (赞：1)

看到这道题，我的想法就是：魔法值怎么确定呢？这题让我们先选一个魔法值，然后走一条边就减 $1$，最后需要跟生命值同时耗尽。这怎么能保证呢？

有句话叫做正难则反。这是一个**无向图**，所以正着走跟反着走没有区别，我们**从 $t$ 走到 $s$** 就可以了。这样一开始的生命值和魔法值都是 $0$。很显然在起点的魔法值就是走过的边数，而我们按照题目中的规则增加生命值就可以了。

但是这个无向图可能有环。而且思考一下，为了让生命值小，不一定不能走环。比如环上的 $w$ 都是 $0$，你就可以一直走环把魔法值耗到很大而不增加生命值。这样后面用 $w$ 除以魔法值就可以得到非常小的值。

看一眼数据范围，$0\le w\le100$！！！这说明什么？这说明了**最多走 $100$ 条边之后，生命值就永远也不会增加了**。很显然因为走 $100$ 条边之后魔法值会到 $100$，之后 $\left\lfloor\dfrac{w}{k}\right\rfloor$ 就永远是 $0$。

于是我们得出一个分层图的做法。状态记录两维，分别表示点的编号和走过的边数。在这个分层图上跑一遍 Dijkstra 即可。

```cpp
#include<iostream>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;
int n,m,s,t,ans=1e9;
bool sub3=1;
struct edge{int x,w;};
vector<edge>v[20010];
struct node{int x,cnt,dis;};
int d[20010][110];
bool flag[20010][110];
bool operator<(const node &x,const node &y){
    return x.dis>y.dis;
}
priority_queue<node>q;
void dij()
{
    q.push({t,1,0});
    memset(d,999999,sizeof(d));
    d[t][1]=0;
    while(!q.empty())
    {
        int x=q.top().x,cnt=q.top().cnt;
        if(cnt>100||x==s)
        {
            ans=min(ans,q.top().dis);
            return;
        }
        q.pop();
        if(flag[x][cnt])continue;
        flag[x][cnt]=1;
        for(auto e:v[x])
            if(d[x][cnt]+e.w/cnt<d[e.x][cnt+1])
            {
                d[e.x][cnt+1]=d[x][cnt]+e.w/cnt;
                q.push({e.x,cnt+1,d[e.x][cnt+1]});
            }
    }
}
int main()
{
    cin>>n>>m>>s>>t;
    for(int i=1;i<=m;i++)
    {
        int x,y,w;
        cin>>x>>y>>w;
        v[x].push_back({y,w});
        v[y].push_back({x,w});
        if(w>1)sub3=0;
    }
    if(sub3)
    {
        for(auto e:v[t])
            ans=min(ans,e.w);
        cout<<ans<<endl;
        return 0;
    }
    else
    {
        dij();
        cout<<ans<<endl;
    }
    return 0;
}
```

注：我用小号打的比赛，这是我小号 @A_Legendary_Coder 交的代码。其中特判了 Subtask 3。

---

## 作者：AK_CSP_SZAuQH (赞：1)

这道题题目的题意就不用再多解释一遍了，但再**数据范围**的地方说明了 $w \le 100$，有了这一个范围限制，就也告诉了我们，当我们定义的初始需要的最小生命值的时候，如果初始最小的生命值 $k>100$ 的时侯，与魔兽战斗的时候就不会减少生命值。

所以我们考虑动态规划，设状态 $f_{i,j}$ 表示的是到达 $i$ 节点魔力值为 $j$ 时用了最少生命值，$nt$ 为当前枚举的魔力值 ${}+1$，因为走完当前这条边需要的魔力值比原来多 $1$，$u$ 为当前去到的节点，$j$ 是现在要去到的节点，则

$$f_{j,nt}=\begin{cases}\min(f_{j,nt},f_{u,nt}+edge[i].w \div nt) &ti \le 100 \\ \min(f_{j,nt},f_{u,nt}) &ti > 100 \end{cases}$$

## CODE

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	return x*f;
}
const int N=2e4+5,inf=0x3f3f3f3f;
struct Edge{
	int v,ne,w;
}edge[N<<2];
int h[N],idx=1,n,m,s,t,f[N][105],x,y,z,u,ti,res=inf;
queue<int> a,b; 
void connec(int x,int y,int z){
	edge[idx].v=y;
	edge[idx].ne=h[x];
	edge[idx].w=z;
	h[x]=idx++;
}//链式前向星存图 
void init(){
	memset(f,inf,sizeof f);//初始化成无限大 
	f[t][0]=0;
	a.push(t),b.push(0);
}
signed main(){
	n=read(),m=read(),s=read(),t=read();
	init();
	while(m--){
		x=read(),y=read(),z=read();
		connec(x,y,z);
		connec(y,x,z);
	}
	while(!a.empty()){
		u=a.front(),ti=b.front();
		a.pop(),b.pop();
		if(ti<100){
			for(int i=h[u];i;i=edge[i].ne){
				int j=edge[i].v,nt=ti+1,w=edge[i].w/nt;
				if(f[j][nt]>f[u][ti]+w) f[j][nt]=f[u][ti]+w,a.push(j),b.push(nt);
			}
		}
		else{
			for(int i=h[u];i;i=edge[i].ne){
				int j=edge[i].v;
				if(f[j][ti]>f[u][ti]) f[j][ti]=f[u][ti],a.push(j),b.push(ti);//这里不用再加东西的原因是，大于 100 魔力值对答案的贡献为 0 
			}
		}
	}
	for(int i=1;i<=101;i++)
		res=min(res,f[s][i]);
	printf("%lld",res);
	return 0;
}
```


---

## 作者：yonghu_848119 (赞：1)

### 题意分析：
在一个无向图内，每条边上有边权 $w$，有一个值 $k$，每走过一条边 $k-1$，有一个生命值，每经过一条边，生命值减 $\left\lfloor \dfrac{w}{k}\right\rfloor$。求从点 $s$ 到点 $t$ 需要的最小生命值。

### 思路：
由于 $k$ 是自己决定的，是很难确定的，因为图是无向图，所以考虑反向跑图，刚开始时 $k$ 为 $0$，从终点到起点后，$k$ 就被求出了。

推荐使用迪杰斯特拉跑图，让花费的生命值成为边权，用迪杰斯特拉反向跑图。设       $dist_{i,j}$ 为 魔法值为 $i$ 时，到了点 $j$ 的最小生命值。

**优化：** 由于 $w\le100$，所以当魔法值 $k>100$ 时，伤害为 $0$，因为是反向跑图，之后的 $k$ 一定更大，所以不需要再跑下去了，直接记录起值即可。

### 喜闻乐见的代码环节
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e4+10;
int dist[105][N],n,m,s,t,INF,cnt,ans=1e9;
struct Node{
	int v,nxt,w;
	Node(){nxt=w=0;}
	Node(int x,int y,int z){
		v=x,w=y,nxt=z;	
	}
}adj[N<<2];
struct xxx{
	int s,num;
};
int h[N],idx,f[N],st[N][N],vis[N];
void insert(int x,int y,int z){
	adj[++idx]=Node(y,z,h[x]);
	h[x]=idx;
}
void dij(){
	memset(dist,0x3f3f3f3f,sizeof(dist));
	queue<xxx> heap;
	dist[1][t]=0;
	heap.push({1,t});
	while(heap.size()){
		xxx k=heap.front();
		heap.pop();
		int ver=k.num,x=k.s;
		if(st[ver][x])continue;
		st[ver][x]=1;
		if(x>100){
			ans=min(ans,dist[x][ver]);//当魔法值大于等于100，直接记录并不继续向下处理
			continue;
		}
		for(int i=h[ver];i!=0;i=adj[i].nxt){
			int j=adj[i].v;
			if(dist[x+1][j]>dist[x][ver]+adj[i].w/x){
				dist[x+1][j]=dist[x][ver]+adj[i].w/x;//更新dist的值
				heap.push({x+1,j});
			}
		}
	}
}
int main(){
	cin>>n>>m>>s>>t;
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		insert(u,v,w);
		insert(v,u,w);
	}
	dij();
	for(int i=1;i<=101;i++) ans=min(ans,dist[i][s]);//找最小值
	cout<<ans;
	return 0;
}
```
## 完结撒花！

---

## 作者：AgrumeStly (赞：0)

[Link](https://www.luogu.com.cn/problem/P9504)

这题我们发现如果直接去枚举生命和法力值显然是不行的，又看到说最小的生命值，不禁想到最短路，但是怎么跑？

我们令经过一条边之前魔力值为 $k$，那么该边的边权为 $\lfloor\dfrac{w}{k}\rfloor$，于是我们讲题目转化为了边权为 $\lfloor\dfrac{w}{k}\rfloor$ 时 $s$ 到 $t$ 的最短路径。

我们不知道最短路径一共要经过多少条边，也就无法知道初始魔力值究竟有多少。那我们不妨反着想，考虑从 $t$ 到 $s$ 的最短路径，这时我们就不用知道初始魔力值是多少，而是每经过一个边，就将 $k\leftarrow k+1$。

但是此时仍无法直接跑最短路，因为每一次不同时刻经过一条边，他的边权都是不一样的。此时数据范围 $w\leq 100$ 很好的提示了我们。

妈妈，我会拆点分层图！

我们将原本的一个点拆成 $100$ 个点，因为 $w$ 最大为 $100$，若经过的边数（即魔力值）$k>100$，那么他的边权 $w$ 就必然为 $0$，我们就不需要考虑了，因为不会对我们的答案产生影响。

于是对于点 $x$，我们将其拆成 $100$ 个点 $x\times 100+i(1\leq i\leq 100)$，其中的 $i$ 表示在 $x\times 100+i$ 这个点时的魔力值为 $i$，于是显然的对于两个点 $u,v$，其边权为 $w$，若其在原始图上有边相连，那么我们就在分层图上将 $u\times 100 +i(1\leq i < 100)$ 与 $v\times 100 +i+1$ 相连，其边权为 $\lfloor\dfrac{w}{i}\rfloor$。

最后也就很简单了，我们在新的分层图上跑一遍 $t$（新图上为 $t\times 100 +1$） 到 $s$ 的最短路，最后在 $s$ 点的所有层里面找最小值即为最终答案。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=3e6;
const int MX=2e4;
int n,m,s,t;
vector<int>e[NR],g[NR];
void add(int u,int v,int w){
    e[u].push_back(v),g[u].push_back(w);
}
bool vis[NR];
int dis[NR],ans;
queue<int>q;
void spfa(int _s){
    memset(vis,false,sizeof(vis));
    memset(dis,0x3f3f3f3f,sizeof(dis));
    ans=dis[0];
    q.push(_s),vis[_s]=true,dis[_s]=0;
    while(!q.empty()){
        int u=q.front();q.pop();
        vis[u]=false;
        for(int i=0;i<e[u].size();++i){
            int v=e[u][i],w=g[u][i];
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                if(!vis[v])q.push(v),vis[v]=true;
            }
        }
    }
}
int main(){
    cin>>n>>m>>s>>t;
    for(int i=1,u,v,w;i<=m;++i){
        cin>>u>>v>>w;
        for(int j=1;j<100;++j){
            add(u*100+j,v*100+j+1,w/j);
            add(v*100+j,u*100+j+1,w/j);
        }
    }
    spfa(t*100+1);
    for(int i=s*100+1;i<=s*100+100;++i)
        ans=min(ans,dis[i]);
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Daidly (赞：0)

假设最优情况下的路径是 $x_1(s)\to x_2
\to\cdots\to x_m(t)$，其中 $x_i\to x_{i+1}$ 的魔兽攻击力为 $w_i$，则生命值为 $\sum_{i=1}^{k-1} \lfloor\frac{w_i}{k-i}\rfloor$.

我们换一下顺序，令上述路径为 $x_1(t)\to x_2
\to\cdots\to x_m(s)$，则生命值为 $\sum_{i=1}^{k-1} \lfloor\frac{w_i}{i}\rfloor$.

我们可以用二元组 $(num,dis)$ 来表示一个点的所有状态，用  $\lfloor\frac{w_i}{num+1}\rfloor$ 作为新边权，即到目前点走了 $num$ 步，距离最小为 $dis$。答案就是 $s$ 的所有 $num$ 中 $dis$ 的最小值。

但是你发现 $num$ 是 $O(n)$ 级别的，跑不过去。

发现 $w$ 很小，有结论：一百步内对生命值有贡献。

考虑 $(num\leq 100,dis)$ 即可，即对每一个点拆分成 $101$ 个点表示经历了 $0\sim 100$ 步，连边只在 $0\sim 99$ 中进行，跑 dijkstra 即可。

答案为到每个点的第 $101$ 个点的距离与到 $s$ 的任意步数距离取最小值。

复杂度 $O(mw\log mw)$，虽然[能过](https://www.luogu.com.cn/record/119374524)，但是勉强。

然后你发现虽然这个东西类似分层图最短路，但是步数只能增不能减，你按步数从小到大分层遍历一遍或是直接 BFS 都行，复杂度 $O(w(n+m))$.



---

## 作者：User_Unauthorized (赞：0)

观察到数据范围 $w \le 100$ 再结合经过一条边对生命值的影响为 $\left\lfloor \dfrac{w}{k} \right\rfloor$ 可以发现当 $k > 100$ 时经过任意边均不扣除生命值。所以我们直接从终点 $T$ 开始进行大力 $BFS$，处理出每个点到终点 $T$ 的长度为 $k$ 的最短路径（边权为扣除生命值）。注意一点，在此基础上我们还需要考虑 $S \rightarrow T$ 存在长度小于 $100$ 的路径且边权和更优的情况。

## Code
```cpp
//C
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;
typedef std::vector<bool> bitset;
typedef std::pair<valueType, valueType> Edge;
typedef std::list<Edge> EdgeList;
typedef std::vector<EdgeList> EdgeSet;

constexpr valueType MAX = INT_MAX >> 2, W = 120;

struct Status {
    valueType node;
    valueType dist;

    Status(valueType node, valueType dist) : node(node), dist(dist) {}
};

typedef std::queue<Status> StatusQueue;

int main() {
    valueType N, M, S, T;

    std::cin >> N >> M >> S >> T;

    EdgeSet edges(N + 10);

    for (valueType i = 0; i < M; ++i) {
        valueType u, v, w;

        std::cin >> u >> v >> w;

        edges[u].emplace_back(v, w);
        edges[v].emplace_back(u, w);
    }

    StatusQueue nowQueue, nextQueue;

    nowQueue.emplace(T, 0);
    ValueMatrix dist(W + 10, ValueVector(N + 10, MAX));

    for (valueType k = 1; k <= W; ++k) {
        while (!nowQueue.empty()) {
            Status status = nowQueue.front();
            nowQueue.pop();

            if (dist[k][status.node] < status.dist) {
                continue;
            }

            dist[k][status.node] = status.dist;

            for (Edge edge: edges[status.node]) {
                if (dist[k + 1][edge.first] <= status.dist + edge.second / k) {
                    continue;
                }

                nextQueue.emplace(edge.first, status.dist + edge.second / k);
                dist[k + 1][edge.first] = status.dist + edge.second / k;
            }
        }

        nowQueue.swap(nextQueue);
    }

    valueType ans = MAX;
    bitset visited(N + 10, false);

    typedef std::function<void(valueType)> DfsFunction;

    DfsFunction dfs = [&](valueType x) {
        visited[x] = true;

        ans = std::min(ans, dist[W][x]);

        for (Edge edge: edges[x])
            if (!visited[edge.first])
                dfs(edge.first);
    };

    dfs(S);

    for (valueType k = 0; k <= W; ++k)
        ans = std::min(ans, dist[k][S]);

    std::cout << ans << std::endl;

    return 0;
}
```

---

