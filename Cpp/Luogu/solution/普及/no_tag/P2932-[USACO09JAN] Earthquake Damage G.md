# [USACO09JAN] Earthquake Damage G

## 题目描述

威斯康星州发生了一场地震，影响了 Farmer John 的农场！地震损坏了一些牧场，使它们无法通行。值得注意的是，没有一条牛道受到损坏。

像往常一样，农场被建模为一组编号为 $1\ldots P$ 的 $P(1 \le P \le 30,000)$ 个牧场，这些牧场通过一组编号为 $1\ldots C$ 的 $C (1 \le C \le 100,000)$ 条无向牛道连接。牛道 $i$ 连接牧场 $a_i$ 和 $b_i (1 \le a_i \le P; 1 \le b_i \le P)$。牛道可能连接 $a_i$ 自己，或者可能多次连接两个牧场。谷仓位于牧场 $1$。

总共有 $N (1 \le N \le P)$ 头牛（在不同的牧场）通过手机依次联系 Farmer John，发送一个整数消息 $report_j (2 \le report_j \le P)$，表示牧场 $report_j$ 未受损，但打电话的牛无法从牧场 $report_j$ 返回谷仓，因为它找不到不经过受损牧场的路径。

在所有牛报告后，确定无法返回谷仓的最小牧场数量（包括那些不可通行的牧场）。

注意：在前 $50$ 次提交中，将提供部分测试数据的反馈。

## 说明/提示

牧场 $2$ 受损，导致牧场 $2, 3, 4$ 的牛无法返回谷仓。（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
4 3 1 
1 2 
2 3 
3 4 
3 
```

### 输出

```
3 
```

# 题解

## 作者：zhy137036 (赞：8)

## 题意简述

- 给你一个无向图，有一些点坏了。
- 已知一些点没有坏，但是无法不经过坏点到达（以下简称为无法到达） $1$ 号点。
- 求最少有多少点无法到达 $1$ 号点。

## 题目分析

### 特殊点

重点在“没有坏，但是无法到达 $1$ 号点”的 $u$ 点上。

这意味着与它相邻的 $v$点，要么是坏点，要么和它处境一样。

如果 $v$ 是坏点，那与 $v$ 相邻的点有可能能到达 $1$ 号点。

如果 $v$ 和 $u$ 处境一样，那与 $v$ 相邻的点也无法到达 $1$ 号点。

所以最好的假设是与 $u$ 相邻的点全都是坏点。（可以认为是一种贪心）

### 搜索

刚才已经标记出了所有坏点，然后从 $1$ 号点开始搜索，得到能到达 $1$ 号点的点的数量。

用总点数减去搜出来的答案，得到无法到达的点的数量

## 代码

```cpp
#include<iostream>
#include<vector>
using namespace std;
int p,c,n,ans;//ans表示搜到的点的数量
bool broken[30010];//需不需要被搜索
vector<int>edge[30010];//边
void dfs(int x){
	ans++;//搜到的点又多了一个
	broken[x]=true;//下次别再搜这个点了
	for(int i=0;i<edge[x].size();i++){
		int y=edge[x][i];//能使代码清晰一点
		if(!broken[y])dfs(y);//不让你搜就别搜
	}
}
int main(){
	cin>>p>>c>>n;
	for(int i=1;i<=c;i++){
		int x,y;cin>>x>>y;
		edge[x].push_back(y);
		edge[y].push_back(x);
	}
	for(int i=1;i<=n;i++){
		int x;cin>>x;
		for(int j=0;j<edge[x].size();j++)
			broken[edge[x][j]]=true;//与之相邻，都不要被搜
	}
	dfs(1);
	cout<<p-ans<<endl;
    return 0;
}
```

## 后记

还有一些问题可以想一想：

- $u$ 点不能被搜到，为什么不标记？
- 如果 $v$ 点也是已知的“没有坏，但是无法不经过坏点到达 $1$ 号点”的点，算法会不会出错？

这些问题插在中间可能会打断思路，所以放在最后。

- 因为相邻的点都被标记了，不可能被搜到。
- 因为我们能确定与 $v$ 相邻的点都不能到达 $1$ 号点，所以 $v$ 与世隔绝，$v$ 被误判成坏点也不重要了。

---

## 作者：ez_lcw (赞：3)

 **这题明显是一道暴力深搜的题目**

大体思路是（可能有更好的）：**深搜找出所有能到的牛棚，再用总牛棚数减去所有能到的牛棚数，就是不能到的牛棚了。**

关键是要掌握题目中" *_N (1 <= N <= P)头在不同牛棚的牛通过手机短信report_j(2 <= report_j <= P)告诉FJ它们的牛棚(report_j)没有损坏,但是它们无法通过路经和没有损坏的牛棚回到到农场_ "获取到信息：*

**既然它们的牛棚没有损坏但又回不去，就说明与这个牛棚连接的所有牛棚都损坏了，也就是没有牛棚供它们顺路回家，所以只用建一个布尔数组来表示第n个牛棚有没有被损坏。**

然后直接深搜就行了。

代码如下：

```
#include<iostream>
#include<cstdio>
#include<queue>
#include<vector>

using namespace std;
 
int p,c,n,report,ans;

bool vis[100005];//true为走过，false为未走过

vector<int>a[100005];//存路径，也可以用邻接矩阵
 
void dfs(int u){
    ans++;
    vis[u]=true;
    for(int i=0;i<a[u].size();i++){
        if(!vis[a[u][i]]){//判断是否走过
            dfs(a[u][i]);
        }
    }
}
 
int main(){
    scanf("%d%d%d",&p,&c,&n);
    for(int i=1;i<=c;i++){
    	int ai,bi;
        scanf("%d%d",&ai,&bi);
        a[ai].push_back(bi);//存储与牛棚ai相连的牛棚bi
        a[bi].push_back(ai);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&report);
        vis[report]=true;
        for(int i=0;i<a[report].size();i++){
            vis[a[report][i]]=true;//将所有与report相连的牛棚设为true；
        }
    }
    dfs(1);
    printf("%d\n",p-ans);//求出答案
    return 0;   
}
```

---

## 作者：hypot (赞：3)

把每个无法到达的点搜一遍，类似noip2014寻找道路，最后统计答案就好

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int M=30005;
int n,m,k,x,y,ans,t;
bool vis[M];
int head[M];
struct edge{
    int to,next;
}e[M*7];
void add(int i,int j){
    e[t].to=j;
    e[t].next=head[i];
    head[i]=t++;
}//存图
void del(int x){
    for(int i=head[x];i!=-1;i=e[i].next)
    vis[e[i].to]=1;//x联通的点也无法到达1（设x联通的点为y,若y可以到达1，则x也可以，反之亦然）
}
void dfs(int x){
    vis[x]=1;ans--;
    for(int i=head[x];i!=-1;i=e[i].next)
    if(!vis[e[i].to]) dfs(e[i].to);//统计vis[i]没有被设为1的点，即可行点
}
void init()
{
    memset(head,-1,sizeof(head));
    cin>>n>>m>>k;
    ans=n;//要求输出不可行点数，用n-可行点
    for(int i=1;i<=m;i++){
        scanf("%d%d",&x,&y);
        add(x,y),add(y,x);//建图
    }
    for(int i=1;i<=k;i++){
        scanf("%d",&x);
        del(x);//x为无法到达1的点
    }
}
void work()
{
    dfs(1);
    printf("%d\n",ans);
}
int main()
{
    init();
    work();
    return 0;
} 
//详细注释在代码里

```

---

## 作者：wunaidedanjuan (赞：2)

### **简化题意**

一个有 $n$ 个点，$m$ 条道路的无向图中，有一些点坏了无法通过；有 $c$ 个点没有损坏，却无法到达 $1$ 号点。求最少有几个点不经过损坏点无法达到 $1$ 号点。

### **思路分析**

- 求最少几个点不经过损坏点无法达到 $1$ 号点，可以转化成求从 $1$ 号点最多能不经过损坏的点到达几个点。

- 一个点没有损坏却无法回到 $1$ 号点，说明它周围的道路通向无法到达 $1$ 号点的点或者可以达到却损坏了的点。所以可以将这个点以及它通向的所有点都看作损坏的点并标记。

### **思路总结**
- 建一个无向图；

- 标记无法到达 $1$ 号点却未损坏的点及其连通的点；

- 搜索 $1$ 号点可以到达的为被标记的点。

### **代码呈现**
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<ctime>
#include<queue>
#include<map> 
#include<vector>
#include<string>
#include<bitset>
#include<cctype>
#include<cstdlib>
#include<functional>
#include<istream>
#include<sstream>
#define int long long 
using namespace std;
const int N=200000,inf=0x3f3f3f3f3f3f3f3f,mod=10007;
int ans=0;
vector<int>a[N];
bool b[N];
void dfs(int x)
{
	b[x]=true;//标记搜过
	ans++;
	for(vector<int>::iterator i=a[x].begin();i!=a[x].end();i++)
		if(b[*i]==false)
			dfs(*i);
}
signed main()
{
	memset(b,0,sizeof(b));//初始没有点损坏 
	int n,m,c,x,y;
	scanf("%lld%lld%lld",&n,&m,&c);
	for(int i=1;i<=m;i++)
	{
		scanf("%lld%lld",&x,&y);
		a[x].push_back(y);//无向图，双向建边 
		a[y].push_back(x);
	}
	for(int i=1;i<=c;i++)
	{
		scanf("%lld",&x);
		b[x]=true;//标记损坏点及其周围点
		for(vector<int>::iterator j=a[x].begin();j!=a[x].end();j++)
			b[*j]=true; 
	}
	dfs(1);
	printf("%lld",n-ans);
	return 0;
}
```

---

## 作者：_szs9601 (赞：1)

#### 思路
通过搜索求出能到达农场的牛棚数量，用总数量减去能到达的牛棚数量，就是最终答案。

有个问题，即有 $N$ 个点，虽然它们没有坏，但是不能通过其他路径到达农场。我们设这个点为 $a$，与它联通的点为 $b$，如果 $b$ 能到达农场，那么 $a$ 同样也能通过 $b$ 到达农场，所以与 $a$ 相连的点都不能到达农场。

~~这题我用宽搜来练练手，不喜勿喷。~~
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,x,y,i,j,ans,f[30100];
vector<int>a[30100];
queue<int>q;
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		a[x].push_back(y);
		a[y].push_back(x);
	}//存图
	for(i=1;i<=k;i++){
		scanf("%d",&x);
		for(j=0;j<a[x].size();j++) f[a[x][j]]=1;
	}//去边
	q.push(1);f[1]=1;ans=1;
	while(!q.empty()){
		x=q.front();
		for(i=0;i<a[x].size();i++)
			if(f[a[x][i]]==0){
				q.push(a[x][i]);f[a[x][i]]=1;ans++;
			}
		q.pop();
	}//搜索
	printf("%d\n",n-ans);
	return 0;
}
```

---

## 作者：flysnow (赞：1)

## P2932 [USACO09JAN]Earthquake Damage G

#### - 首先

我们理解一下题目大意，有 $P$ 个点， $C$ 条无向边，有部分的点遭到损坏（即无法到达这个点），现给出 $N$ 个没被损坏但无法到达 $1$ 的点，求最少有多少点无法到达 $1$ 号点。

为什么这 $N$ 个点到达不了 $1$ 呢？
是因为与它相邻的点是它通向 $1$ 的唯一路径；

那么无非就两种情况：

要么就是与其相邻的点被损坏，要么就是与其相邻的点无法到达 $1$。

所以我们只要把与这 $N$ 个点有边直接相邻的所有点打上标记，最后再从 $1$ 进行遍历。

$AC$ $Code$ 

```cpp
#include <bits/stdc++.h>

const int N = 3e4 + 5, M = 1e5 + 5;

using namespace std;

struct node {
	int to, next;
}e[M << 1 | 1];

int n, m, cnt, q, a, b, ans;//n, m, q 即为上文的 P, C, N

int head[N];
bool vis[N];

inline void add(int u, int v) {
	e[++ cnt].to = v;
	e[cnt].next = head[u];
	head[u] = cnt;
}

void Dfs(int u) {
	for (int i = head[u]; i; i = e[i].next)
		vis[e[i].to] = 1;
}

void dfs(int u) {
	ans ++;
	vis[u] = 1;
	for (int i = head[u], v; i; i = e[i].next) 
		if (!vis[v = e[i].to]) dfs(v);
}

int main() {
	scanf("%d%d%d", &n, &m, &q);
	
	for (int i = 1; i <= m; i ++) {
		scanf("%d%d", &a, &b);
		add(a, b);
		add(b, a);
	}
	
	for (int i = 1; i <= q; i ++) {
		scanf("%d", &a);
		Dfs(a);
	}
	dfs(1);
	printf("%d\n", n - ans);
	return 0;
}
```


---

## 作者：Eason_cyx (赞：1)

比较复杂的图上深搜。

题目描述比较神，所以这里给出容易理解的题意：

- FJ 的农庄有很多牛棚，$1$ 号牛棚表示农庄。

- 由于当地发生了地震，有一些牛棚损坏了。

- 他一共有 $P$ 间牛棚，用 $C$ 条道路连接。

- 有 $N$ 个牛棚的牛给他发来信息，称它们无法回到农庄。

- 请你求出最多能有多少牛能回到农庄。

首先我们分析：为什么这些牛无法回到农庄？

回农庄肯定是要经过道路，既然回不去，说明有道路损坏了。

题目中说：

> 最多能有多少牛能回到农庄

那么我们考虑贪心。

如何贪心呢？问一个问题，你就会了：假设 `FJ` 有两个农庄，`A` 农庄所有道路都坏掉了，`B` 农庄只有一条道路坏了，导致一个牛棚中的奶牛回不去。如果要你选择哪一个农庄回到 `1` 号点的奶牛多一些，你会选择哪个？

没错，肯定是 `B`。所以我们使用一个小贪心：如果一个牛棚坏了，就将它周围的牛棚都看做坏了。

本题考察的主要算法是 `DFS`。我们搜索可以按照以下步骤：

1. 从 $1$ 号点开始搜索，统计能到达的点个数，记为 $ans$。

2. 答案就是 $P - ans$。

接下来是代码实现。

本题我们存图如果使用邻接表，空间会炸；所以我们使用 `vector` 进行存储，$a_{i,j}$ 表示与第 $i$ 个点相连的第 $j$ 个点。

分析到这里，思路已经比较清晰了，有不完善之处请看下面代码注释：
```cpp
#include <iostream>
#include <vector>
using namespace std;
vector<int> a[10005];
bool vis[10005]; //vis[i] = true表示第i个点走过，如果坏掉了是不能走的，直接赋值为true，如果为false表示没走过，能走
int p,c,n,ans;
void dfs(int step) {
	ans++;
	vis[step] = true;
	for(int i = 0;i < a[step].size();i++) {
		if(!vis[a[step][i]]) {
           dfs(a[step][i]);
        }
    }
}
int main() {
	cin >> p >> c >> n;
	for(int i = 1;i <= c;i++) {
		int ai,bi; cin >> ai >> bi;
		a[ai].push_back(bi);
		a[bi].push_back(ai);
                //连接边
	}
	for(int i = 1;i <= n;i++) {
		int report; cin >> report;
		vis[report] = true;
		for(int j = 0;j < a[report].size();j++) {
		    vis[a[report][j]] = true;//将这些点设置为坏的
		}
	}
	dfs(1);
	cout << p - ans << endl;
	return 0;
}
```

---

## 作者：zhujiangyuan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P2932)

修了一下题面，顺便来写篇题解。

问题是求出最小的不可能回到农庄的牛棚数目，但不易直接求出答案。正难则反，考虑求出**最多能回到农庄的牛棚数目**。

对于一个点 $u$，如果它没有坏，且无法通过没有损坏的牛棚回到农庄，就说明所有与 $u$ 直接有边相连的点 $v$ 都到不了农庄。原因：如果 $v$ 能到达农庄，那么 $u$ 也能到达农庄，与已知条件不符。故若 $u$ 无法到达农庄，$v$ 就无法到达农庄。

为了使能回到农庄的牛棚数目更多，就把与 $u$ 直接相连的点 $v$ 全部标记为"坏点"，即不能走的点。然后从 $1$ 号点开始 dfs 一遍求出所有能到达的点，再拿 $P$ 减去能到达的点的数目就是答案。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=3e4+10;
int p,c,n,ans;
vector<int>G[N];
bool v[N];
void dfs(int x)//dfs求出能到达的点的数目
{
	v[x]=1;ans++;
	for(auto i:G[x])
	{
		if(!v[i]) dfs(i);
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>p>>c>>n;
	for(int i=1;i<=c;i++)
	{
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		for(int j=0;j<G[x].size();j++)
			v[G[x][j]]=1; //标记为坏点
	}
	dfs(1);
	cout<<p-ans;
	return 0;
}
```

---

## 作者：SilverLi (赞：0)

[Earthquake Damage G](https://www.luogu.com.cn/problem/P2932)

先贪心，将一个 $report_j$ 及其周围的点都标记为“坏点”。

再从 $1$ 号点 DFS（因为 $1$ 号点是农场的位置），遍历每一个不是“坏点”的点。

最后用总的牛棚数 $p$ 减去不是“坏点”的点的个数。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define DeepFirstSerch DFS
const int N=30005;
int p,c,n,ans;
int u,v,vis[N];
vector<int> g[N];
void DFS(int ch) {
	++ans,vis[ch]=1;// DFS 求有多少个“好点”
	for(int i:g[ch])
		if(!vis[i])	DFS(i);
}
signed main() {
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>p>>c>>n;
	while(c--) {
		cin>>u>>v;
		g[u].push_back(v),
		g[v].push_back(u);
	}
	while(n--) {
		cin>>u;// 贪心，将一个“坏点”及其周围的点都标记为“坏点”
		vis[u]=1;
		for(int i:g[u])	vis[i]=1;
	}
	DeepFirstSerch(1);
	cout<<p-ans;
	return 0;
}
```

---

## 作者：haotian1234 (赞：0)

## 题意暗示
- 给你了一个图，有一些点是无法走到的。
- 现在告诉你几个通向 1 号点的路上全是坏的点的点（本身没有坏）
- 让你求有几个点无法到达 1 号点（其实就是求有几个点能到 1 号点）
## 题目分析
1. 你要存一个图，本人建议用 vector，没有别的就因为方便。
1. 对于已经无法到 1 号点的点，旁边的点要做好标记，因为他们要么坏了要么也无法到一号点（否则当前这个点就可以从这个点到一号点了）。
1. 上述预处理做完后，从 1 号点开始搜索如果搜到的这个点没有被标记，说明能到 1 号点，将能到 1 号点的点的个数记为 $ans$ （包括 1 号点自己），此时 $ans + +$。
1. 最后输出 $p - ans$ 
## 题目坑点
- vector 枚举从 0 开始

下面就上大家最最最关心的东西——代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int p,c,n,ans,i,f[30010],j,x,y;
vector<int> a[30010];
void sc(int x){
	ans++;f[x]=1;
	for(int i=0;i<a[x].size();i++){
		int y=a[x][i];
		if(!f[y])sc(y);
	}
}//搜索
int main(){
	scanf("%d%d%d",&p,&c,&n);
	for(i=1;i<=c;i++){
		scanf("%d%d",&x,&y);
		a[x].push_back(y);
		a[y].push_back(x);
	}//存图
	for(i=1;i<=n;i++){
		scanf("%d",&x);
		for(j=0;j<a[x].size();j++)//vector 枚举从0开始
			f[a[x][j]]=1;
	}//标记
	sc(1);
	printf("%d\n",p-ans);
    return 0;
}
```


---

## 作者：xy_xw_for_2024 (赞：0)

题目还是很容易懂的

而且很容易可以得出如果一个牛棚不能到，那么和TA相邻的都不能到

因为如果相邻的都可以到的话，那TA肯定可以到

要最少的话就把TA周围的全部变成破坏的就好

以下是代码：
```cpp
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
inline void read(int &x) {
    x=0;
    int f=1;
    char s=getchar();
    while(s<'0'||s>'9') {
        if(s=='-')
            f=-1;
        s=getchar();
    }
    while(s>='0'&&s<='9') {
        x=x*10+s-48;
        s=getchar();
    }
    x*=f;
}
inline void pr(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9)
        pr(x/10);
    putchar(x%10+48);
}//快读快输不解释
vector<int>G[30005];
int flag[30005]={0,1},a,b,p,n,c,i,j,k,ans;
inline void bfs(int x) {//广搜，最后搜一遍看那些可以达到
    queue<int>q;
    q.push(x);
    while(!q.empty()) {
        int t=q.front();
        q.pop();
        int l=G[t].size();
        for(i=0;i<l;i++)
            if(flag[G[t][i]]==0) {//flag=-1时表示当前牛棚被破坏
                q.push(G[t][i]);
                flag[G[t][i]]=1;
            }
    }
}
int main() {
    read(p),read(c),read(n);
    for(i=1;i<=c;i++) {
        read(a),read(b);
        G[a].push_back(b);
        G[b].push_back(a);//无向图
    }
    for(i=1;i<=n;i++) {
        read(a);
        int l=G[a].size();
        flag[a]=-1;//一定要标记一下，当前点是不能到的
        for(j=0;j<l;j++)
            flag[G[a][j]]=-1;//相连的都被破坏
    }
    bfs(1);
    for(i=1;i<=p;i++)
        if(flag[i]==0||flag[i]==-1)//搜不到||被破坏
            ans++;
    pr(ans);
}
```
[我的博客链接](https://blog.csdn.net/qq_43890190/article/details/86144757)

---

## 作者：piuke (赞：0)

# 题目描述
[~可爱的小网址~](https://www.luogu.org/problemnew/show/P2932)
# 题意描述&语文分析
话说这是一道语文题……
不是我说，真的是一道语文题，考的不是编程素养，是语文。
真的严重考验阅读能力……

首先，勾关键
>N头在不同牛棚的牛通过手机短信$report_j$告诉FJ它们的牛棚($report_j$)没有损坏，但是它们无法通过路经和没有损坏的牛棚回到到农场。

既然它们的牛棚没有损坏，但是他们还是回不去，就说明与这个牛棚连接的所有牛棚都损坏了，意思就是说相邻的点要么损坏，要么和它情况一样。也就是说，相邻的点，也没有用，也回不到1号牛棚。

诶？好像有什么不对？

既然都要回到点1，这样，去掉那些未损坏但不可以回去的点的相邻边，遍历一下，没遍历到的点数，不就是答案吗？

如何删除已经加入的边？vector有一个函数，叫做clear，可以清掉整个vector……

邻接表快切……
# 来得及其快的代码
```cpp
#include<map>
#include<set>
#include<list>
#include<queue>
#include<deque>
#include<stack>
#include<ctime>
#include<cmath>
#include<vector>
#include<bitset>
#include<cstdio>
#include<cctype>
#include<string>
#include<cstdlib>
#include<cstring>
#include<climits>
#include<iomanip>
#include<iostream>
#include<algorithm>
using namespace std;
#define reg register
inline bool OpenFile() {
    freopen("earthquake.in","r",stdin);
    freopen("earthquake.out","w",stdout);
    return 1;
}
//bool _Open=OpenFile();
template <typename T>
inline T read() {
    T a=0; char c=getchar(),f=1;
    while(c<'0'||c>'9') {
        if(c=='-') f=-f;
        if(c==-1) return c;
        c=getchar();
    }
    while(c>='0'&&c<='9') a=(a<<1)+(a<<3)+(c^48),c=getchar();
    return a*f;
}
template <class T>
inline int write(T x) {
    if(x<0) x=(~x)+1, putchar('-');
    if(x/10) write(x/10);
    return putchar(x%10|48);
}
template <class T>
inline int write(T x,char c) {
    return write(x)&&putchar(c);
}
template <class T>
inline T Max(T a,T b) { return a>b?a:b; }
template <class T>
inline T Min(T a,T b) { return a<b?a:b; }
template <class T>
inline T Abs(T a) { return a<0?-a:a; }
int p=read<int>(),c=read<int>(),n=read<int>();
vector<int>G[30001];
char OK[30001];
int k;
int ans;
inline void dfs(int x) {
    OK[x]=1;
    for(reg int i=0;i<(int)G[x].size();i++)
        if(!OK[G[x][i]]) dfs(G[x][i]);
}
int main() {
    for(reg int i=1;i<=c;i++) {
        int u=read<int>(),v=read<int>();
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for(reg int i=1;i<=n;i++) {
        int u=read<int>();
        for(reg int i=0;i<(int)G[u].size();i++)
            OK[G[u][i]]=-1;
        G[u].clear();
    }
    dfs(1);
    for(reg int i=1;i<=p;i++)
        if(OK[i]!=1)
            ans++;
    write(ans);
}
```

---

