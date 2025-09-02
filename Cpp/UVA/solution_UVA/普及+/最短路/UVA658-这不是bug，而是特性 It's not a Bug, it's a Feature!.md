# 这不是bug，而是特性 It's not a Bug, it's a Feature!

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=8&page=show_problem&problem=599

[PDF](https://uva.onlinejudge.org/external/6/p658.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA658/3980280739ce31d9b96acdbe804068ca33cab9fc.png)

## 样例 #1

### 输入

```
3 3
1 000 00-
1 00- 0-+
2 0-- -++
4 1
7 0-0+ ----
0 0```

### 输出

```
Product 1
Fastest sequence takes 8 seconds.

Product 2
Bugs cannot be fixed.

```

# 题解

## 作者：EuphoricStar (赞：5)

## 思路

在任意时刻，每个 bug 可能存在也可能不存在，所以可以用一个 $n$ 位的二进制串表示当前软件的“状态”。

我们可以把状态看成结点，状态转移看成边，这样这道题就转化为最短路问题。但是这题和普通的最短路问题不一样：节点很多，多达 $2^n$ 个，而且很多状态根本遇不到（即不管怎么打补丁，也不可能打成那个状态），所以没有必要先把图储存好。

这道题我们可以使用**隐式图搜索**的方法：当需要得到某个结点 $u$ 出发的所有边时，直接枚举所有 $m$ 个补丁，看看是否能打得上。

其他细节见代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int inf = 0x3f3f3f3f;

struct node {
    int dis, bug;
    bool operator < (const node &u) const {
        return dis > u.dis;
    }
};
priority_queue<node> pq;
int dis[1100000], n, m, t[110], tc;
char bef[110][110], aft[110][110];
bool vis[1100000];

int main() {
    while (1) {
        scanf("%d%d", &n, &m);
        if (!n && !m) {
            break;
        }
        for (int i = 0; i < m; ++i) {
            scanf("%d%s%s", &t[i], bef[i], aft[i]);
        }
        printf("Product %d\n", ++tc);
        bool flag = 0;
        memset(dis, 0x3f, sizeof(dis));
        memset(vis, 0, sizeof(vis));
        while (pq.size()) {
            pq.pop();
        }
        pq.push({0, (1 << n) - 1});
        dis[(1 << n) - 1] = 0;
        while (pq.size()) {
            node u = pq.top();
            pq.pop();
            if (!u.bug) {
                flag = 1;
                printf("Fastest sequence takes %d seconds.\n", u.dis);
                break;
            }
            if (vis[u.bug]) {
                continue;
            }
            vis[u.bug] = 1;
            for (int i = 0; i < m; ++i) {
                bool f = 0;
                for (int j = 0; j < n; ++j) {
                    if (bef[i][j] == '-' && (u.bug & (1 << j))) {
                        f = 1;
                        break;
                    }
                    if (bef[i][j] == '+' && !(u.bug & (1 << j))) {
                        f = 1;
                        break;
                    }
                }
                if (f) {
                    continue;
                }
                node v = u;
                v.dis += t[i];
                for (int j = 0; j < n; ++j) {
                    if (aft[i][j] == '+') {
                        v.bug |= (1 << j);
                    } else if (aft[i][j] == '-') {
                        v.bug &= ~(1 << j);
                    }
                }
                int d = dis[v.bug];
                if (v.dis < d) {
                    dis[v.bug] = v.dis;
                    pq.push(v);
                }
            }
        }
        if (!flag) {
            puts("Bugs cannot be fixed.");
        }
        putchar('\n');
    }
    return 0;
}
```


---

## 作者：xixike (赞：4)

## Description

[Luogu传送门](https://www.luogu.com.cn/problem/UVA658)

## Solution

首先看到 $n \leq 20$，可以想到状压，然后题目要求我们求从全部为 1  的状态到全部为 0 状态的最短时间，不难想到使用最短路或者 $\text{dp}$ 来解决。

对于这道题，我们使用最短路。

把每一种状态当作一个节点，每次处理一个节点时枚举所有的补丁，判断该补丁能否使用，如果可以，直接计算出使用该补丁之后的状态，即为当前点能到达的下一个点。

那么这时还有两个问题：

- 如何判断当前点能否使用。

  把每个补丁必须有的 $\text{bug}$ 存到 $b_1$ 里，必须没有的 $\text{bug}$ 存到 $b_2$ 里，设当前点状态为 $x$，那么 `(x & b1) = b1 && (x & b2) = 0 ` 时，可以转移。

- 如何计算使用补丁之后的状态。

  同样把使用补丁之后会消失的 $\text{bug}$ 存到 $f_1$ 里，会出现的 $\text{bug}$ 存到 $f_2$ 里，那么由于 $f_2$ 都会出现，所以令 `x |= f2`，会消失的 $\text{bug}$ 如何处理呢？也很简单，先令 $x$ 或上 $f_1$，再异或上 $f_1$。

当然这两个都是小问题了，如果还是不理解的话看代码吧。

（另外本题每组数据后面要输出一行空行）

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

namespace IO{
    inline int read(){
        int x = 0;
        char ch = getchar();
        while(!isdigit(ch)) ch = getchar();
        while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
        return x;
    }

    template <typename T> inline void write(T x){
        if(x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace IO;

const int N = 110;
const int inf = 1e9;
int n, m, sta;
struct node{
    int t, b1, b2, f1, f2;
}p[N];
char s[N];
int dis[(1 << 21) + 5];
bool vis[(1 << 21) + 5];

inline void spfa(){
    memset(dis, 0x3f, sizeof(dis));
    queue <int> q;
    q.push(sta = (1 << n) - 1), dis[sta] = 0;
    while(!q.empty()){
        int x = q.front(); q.pop();
        vis[x] = 0;
        for(int i = 1; i <= m; ++i)
            if((x & p[i].b1) == p[i].b1 && !(x & p[i].b2)){
                int y = (x | p[i].f1 | p[i].f2) ^ p[i].f1;
                if(dis[y] > dis[x] + p[i].t){
                    dis[y] = dis[x] + p[i].t;
                    if(!vis[y]) vis[y] = 1, q.push(y);
                }
            }
    }
}

inline void Clear(){
    for(int i = 1; i <= m; ++i) p[i] = (node){0, 0, 0, 0, 0};
}

signed main(){
    int Case = 0;
    while(scanf("%d%d", &n, &m) && n && m){
        for(int i = 1; i <= m; ++i){
            p[i].t = read();
            scanf("%s", s);
            for(int j = 0; j < n; ++j){
                if(s[j] == '+') p[i].b1 |= (1 << j);
                if(s[j] == '-') p[i].b2 |= (1 << j);
            }
            scanf("%s", s);
            for(int j = 0; j < n; ++j){
                if(s[j] == '-') p[i].f1 |= (1 << j);
                if(s[j] == '+') p[i].f2 |= (1 << j);
            }
        }
        spfa(), Clear();
        printf("Product %d\n", ++Case);
        if(dis[0] >= inf) printf("Bugs cannot be fixed.\n\n");
        else printf("Fastest sequence takes %d seconds.\n\n", dis[0]);
    }
    return 0;
}
```



---

## 作者：xzlhxc_ed (赞：3)

[题目链接(洛谷)](https://www.luogu.org/problemnew/show/UVA658)   

这道题初看还是有点迷惑性，毕竟很容易就想到了DFS或者DP的做法。但是，从样例第一组中就可以看出，它的状态转移会回到原来的状态，所以，这道题**不是普通的DAG**，不能简单地DP求解。 

由于本题每一个状态转移都有一个**非负**的权值（时间），因此题目所要求的，就是最短路。由于权值非负，所以可以用$dijkstra$（下文简称dij）来做。

# ①数据存储加工
既然确定了算法，那么我们就自然地能打出一个dij模板（不会dij的请转至[P4779](https://www.luogu.org/problemnew/show/P4779)）   
那么，我们要如何存状态呢？   
一个状态可以看做是一个点，以0代表'-'，以1代表'+'。这样定义，假设n=3，那么dij的起点就是111(+++)，终点就是000(---)。
# ②松弛
既然确定了算法以及数据存储，那么，dij算法怎么实现呢？直接存边吗？  
一个有20个BUG的数据会有$2^{20}(=1048576)$个点，不管是用邻接表还是用邻接矩阵都存不下。事实上，这些状态有很多都是达不到的，又因为m<=100，所以**每一个状态的出边都不会大于100条**，所以我们不用存边，对于每一个点，直接枚举m个补丁就可以了。
```cpp
int m,n;
int start,end;//起点，终点
string patches[100][2];//补丁
int time[100];//存储每个补丁的耗时，即边的权值
priority_queue<step>dui;//dij用的堆优化
int dis[(1<<21)+10];//最短路数组
//dij算法开始！
int dijkstra()
	{
		while(!dui.empty())
		{
			struct step now=dui.top();
			dui.pop();
			if(dis[now.num]!=now.time)continue;//也可以用一个vis数组来储存是否走过 
			for(int i=0;i<m;i++)
			{
				if(can_go(now.num,patches[i][0]))
				{
					int to=change(now.num,patches[i][1]);
					if(dis[now.num]+time[i]<dis[to])
					{
						dis[to]=dis[now.num]+time[i];
						dui.push((step){to,dis[to]});
					}
				}
			}
		}
	    return dis[end]==2139062143?-1:dis[end];
        //2139062143->0x7f，判断是否有解。
	}
```
# ③状态函数
至此，其实核心的代码差不多就写完了，但是上文中，还有2个函数没有实现，一个是判断是否能使用当前补丁的函数```bool can_go(int From,string To)```，一个是状态转换的函数```change(int From,string patch)```。    
既然是状态压缩，在这里，不免要用一些位运算知识。  
**(A>>n-1)&1用于判断二进制数A从右到左第n位是否为1.   
A=A|(1<<n-1)用于把A从右往左第n位设置为1.   
A=A&(~(1<<n-i-1))用于把A从右往左第n为设置为0.**  
至于为什么如此，可以自行手算模拟一下。    

can_go函数比较简单，直接一位一位查询，如果不符合，直接返回0，查询完后没问题返回1.
```cpp
	bool can_go(int a,string b)
    //在这里a即为上文的From,b即为To
	{
		for(int i=n-1;i>=0;i--)
		{
			if(b[i]=='+')
			{
				if(!((a>>n-i-1)&1))return false;
			}
			else if(b[i]=='-')
			{
				if((a>>n-i-1)&1)return false;
			}	 
		}
		return true;
	}
```
而change函数就要用更多的技巧，但总体也简单。
```cpp
int change(int a,string b)
//a即为From，b即为patch
	{
		int A=a;
		for(int i=n-1;i>=0;i--)
		{
			if(b[i]=='+')
			 A=A|(1<<n-i-1);
			if(b[i]=='-')
			 A=A&(~(1<<n-i-1));
		}
		return A;
	}
```
# ④AC
P.S.由于uva的题目很多都是含有多组测试数据，因此将一些函数封装在一个struct中会比较方便。

---

## 作者：Exber (赞：3)

```
It's not a Bug, it's a Feature!
	———— Mojang
```
## 做法

dijkstra+状压。

首先可以用一个二进制数来表示特性的修复情况。例如 `110101` 就表示编号为 `1`、`2`、`4` 和 `6` 的特性没被修复。

那么在输入时可以用 `b1` 数组来存每一个补丁使用时必须存在的特性，用 `b2` 数组来存必须不存在的特性；用 `f1` 数组来存打补丁后会被修复（不存在）的特性，用 `f2` 数组来存打补丁后会加入（存在）的特性。由于可以用二进制来表示修复情况，所以只用一维数组就够了。

那如何判断一个补丁能不能用以及求出用完之后的特性修复状态呢？由于只有当前状态中包含 $b1_i$ 里的所有特性并不包含 $b2_i$ 里的任何特性才能使用补丁 $i$，所以只有当 `(u&b1[i])==b1[i]&&(u&b2[i])==0` 时才能用第 $i$ 个补丁；而由于用完补丁后会修复 $f1_i$ 里的所有特性并会加入 $f2_i$ 里的所有特性，所以用完后的状态就是 `((u|f1[i])|f2[i])^f1[i]`。

很容易发现，每一个状态都只能由其它状态转移而来，但又不一定能转移回去了。所以这道题其实是一个图论题，每种特性的修复状态相当于图节点，而补丁则相当于单向的边。这道题就变为了要求以 `(1<<n)-1` 号节点为源点的单源最短路了。

由于每个补丁花费的时间不是固定的，所以不能用 `BFS`。这里建议用 `dijkstra` 的堆优化而不是 `SFFA`。因为关于 `SPFS`，他死了！

最后注意一下输出格式，每个测试点中间其实有一个空行……

## AC 代码
```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

struct node
{
	int x,cost;
	bool operator<(const node b)const
	{
		return cost>b.cost; // 小根堆 
	}
};

char temp[25];
int n,m,cost[105],b1[105],b2[105],f1[105],f2[105],dis[1<<20],inf;
bool vis[1<<20];

void dijkstra() // 关于 SPFA，他死了！！ 
{
	// 初始化 
	memset(dis,127,sizeof(dis)); 
	memset(vis,0,sizeof(vis));
	inf=dis[0]; // 极大值的赋值 
	priority_queue<node> q;
	q.push((node){
		(1<<n)-1,0
	});
	dis[(1<<n)-1]=0; // 源点距离为 0 
	while(!q.empty())
	{
		node top=q.top();
		q.pop();
		int u=top.x;
		if(u==0)
		{
			break; // 找到答案了！ 
		}
		if(vis[u])
		{
			continue;
		}
		vis[u]=true;
		for(int i=1;i<=m;i++)
		{
			if((u&b1[i])==b1[i]&&(u&b2[i])==0) // 可以用这个补丁吗？ 
			{
				int v=((u|f1[i])|f2[i])^f1[i]; // 用完后的状态 
				if(dis[u]+cost[i]<dis[v]) // 可以更新 
				{
					dis[v]=dis[u]+cost[i]; // 更新 
					q.push((node){ // 加入堆 
						v,dis[v]
					});
				}
			}
		}
	}
}

int main()
{
	int cnt=0;
	while(1)
	{
		scanf("%d%d",&n,&m);
		if(n==0&&m==0)
		{
			break;
		}
		cnt++; 
		// 初始化 
		memset(b1,0,sizeof(b1));
		memset(b2,0,sizeof(b2));
		memset(f1,0,sizeof(f1));
		memset(f2,0,sizeof(f2));
		for(int i=1;i<=m;i++)
		{
			scanf("%d",&cost[i]);
			scanf("%s",temp+1);
			for(int j=1;j<=n;j++)
			{
				if(temp[j]=='+')
				{
					b1[i]|=1<<j-1;
				}
				if(temp[j]=='-')
				{
					b2[i]|=1<<j-1;
				}
			}
			scanf("%s",temp+1);
			for(int j=1;j<=n;j++)
			{
				if(temp[j]=='-')
				{
					f1[i]|=1<<j-1;
				}
				if(temp[j]=='+')
				{
					f2[i]|=1<<j-1;
				}
			}
		}
		dijkstra();
		printf("Product %d\n",cnt);
		if(dis[0]==inf)
		{
			printf("Bugs cannot be fixed.\n");
		}
		else
		{
			printf("Fastest sequence takes %d seconds.\n",dis[0]);
		}
		printf("\n"); // 记得有一个空行！ 
	}
	return 0;
}
```


---

## 作者：reyik (赞：2)

首先，这题是一道图论综合题。

图论图论，有图才能论，那么图上总有顶点和边。

那么在这道题中，顶点是什么，边是什么呢？

我们不难看出，从一个状态通过补丁变为另一个状态，那么这两个状态之间就可以连一条有向边。

但状态怎么用数组来存储呢？

我们如果用二位数组来储存显然是不行的，所以我们不难想到用位运算的方法来储存状态。

接下来我们想，一开始，他的状态时:
```
+++++...n个BUG

```

那么，最后一个状态是：
```
-----一个BUG都没有

```

那么确定了顶点和有向边，起点和终点，那么这道题就是求从有n个BUG 到 一个BUG 都没有的最短路径。

这样思路就清楚了，附上丑陋的代码（~~qwq~~）

```
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int inf=1e9;
int d[(1<<20)+10],vis[(1<<20)+10]; 
int s[2][110], t[2][110];
int n, m, w[110];
string s1, s2;
void spfa() {//标准SPFA 
	int mas = (1<<n) - 1;
	queue <int> q;
	for(int i = 0; i < mas; i++) {
		vis[i] = 0;
		d[i] = inf;
	}
	vis[mas] = 1;
	d[mas] = 0;
	q.push(mas);
	bool flag=false;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = 0;
		for(int i = 0; i < m; i++) {
			if((u | s[1][i]) == u && ((u & s[0][i]) == u)) {
				int v = u;
				v = v | t[1][i];
				v = v & t[0][i];
				if(d[u] + w[i] < d[v]) {
					d[v] = d[u] + w[i];
					if(!vis[v]) {
						q.push(v);
						vis[v] = 1;
					}
				}
			}
		}
	}
	if(d[0] == inf) {//如果当前的目标点仍然为最大值，说明无解 
		printf("Bugs cannot be fixed.\n");
	} else {
		printf("Fastest sequence takes %d seconds.\n", d[0]);
	}
}
int main() {
	int T= 0;
	while(scanf("%d%d", &n, &m) != EOF && n) {
		memset(s, 0, sizeof(s));//用s和t数组分别来表示补丁原来的状态和现在的状态 
		memset(t, 0, sizeof(t));
		for(int i = 0; i < m; i++) {
			cin>>w[i]>>s1>>s2;
			for(int j = 0; j < n; j++) {
				if(s1[j] == '+') s[1][i] += (1<<j);
				if(s1[j] != '-') s[0][i] += (1<<j);
				if(s2[j] == '+') t[1][i] += (1<<j);
				if(s2[j] != '-') t[0][i] += (1<<j);
			}
		}
		printf("Product %d\n", ++T);
		spfa();
		printf("\n");//注意空行。
	}
	return 0;
}


```

---

## 作者：Conan15 (赞：1)

观察到 bug 的数量最多只有 $20$，容易联想到**状压**。\
然后按照题目条件暴力建边，直接 dijkstra 跑**最短路**。\
这样算下来最坏情况边数是 $2^n \times m$，卡得比较紧。\
考虑**时间换空间**，在 dijkstra 的时候直接遍历所有补丁，看是否能使用直接拓展状态。

```cpp
#include <bits/stdc++.h>
#define PII pair<int, int>
using namespace std;
const int N = (1 << 20) + 5, K = 105;
char ch[30];
int n, m, t[K];

int b1[K], b2[K], f1[K], f2[K];

priority_queue< PII > q;
int d[N];
bool st[N];
void dijkstra() {
    while (q.size()) q.pop();
    for (int i = 0; i < (1 << n) - 1; i++) d[i] = 0x3f3f3f3f, st[i] = 0;
    d[(1 << n) - 1] = 0, st[(1 << n) - 1] = 0;
    q.push(make_pair(0, (1 << n) - 1));
    while (q.size()) {
        int S = q.top().second; q.pop();
        if (st[S]) continue;
        st[S] = 1;
        for (int i = 1; i <= m; i++) {
            if ((S & b1[i]) != b1[i]) continue;
            if (S & b2[i]) continue;
            int T = S;
            T = (S ^ (S & f1[i])) | f2[i];
            if (d[T] > d[S] + t[i]) {
                d[T] = d[S] + t[i];
                q.push(make_pair(-d[T], T));
            }
        }
    }
    if (d[0] == 0x3f3f3f3f) puts("Bugs cannot be fixed.\n");
    else printf("Fastest sequence takes %d seconds.\n\n", d[0]);
}

int main() {
    int Tid = 0;
    while (scanf("%d%d", &n, &m) != EOF) {
        if (!n && !m) break;
        Tid++;
        printf("Product %d\n", Tid);
        for (int i = 1; i <= m; i++) b1[i] = b2[i] = f1[i] = f2[i] = 0;
        for (int i = 1; i <= m; i++) {
            scanf("%d", &t[i]);
            scanf("\n %s", ch + 1);
            for (int j = 1; j <= n; j++) {
                if (ch[j] == '+') b1[i] |= (1 << j - 1);
                if (ch[j] == '-') b2[i] |= (1 << j - 1);
            }
            scanf("\n %s", ch + 1);
            for (int j = 1; j <= n; j++) {
                if (ch[j] == '-') f1[i] |= (1 << j - 1);
                if (ch[j] == '+') f2[i] |= (1 << j - 1);
            }
        }
        dijkstra();
    }
    return 0;
}
```

---

## 作者：freeHackerJava (赞：1)

首先读题，得出这是一道与状态有关的题。同时，通过题目的描述，这道题目有一个起始状态和一个终点状态，而且有边权（补丁所需的时间），所以这道题是一道最短路。

首先看怎么建图。发现每一位都有 $2$ 种可能，总共有 $2^n$ 种情况，显然存不下，因为有 $2^n$ 个点，每个点对 $m$ 条关系都可能行得通。况且计算边通往的情况在时间上也需要 $n$ 的常数，如此一来，时间和空间都会爆。仔细分析，发现题目中有很多情况根本不可能遇到，于是就可以考虑一种新方法：在最短路跑到某个点时，再计算从它出发的所有边，假设是 Dijkstra 堆优化，那么根据Dijkstra的思路，每个点**通往的边**只会计算一次，所以不会出现比建图时间上更差的可能。如果是 SPFA 的话，每个点最多会被计算 $\frac{e}{n}$ 次（雾）。不过可以放心用 SPFA，此题不卡 SPFA。

既然有了思路，那么考虑表示状态。首先有一种方法，就是和题面一样使用字符串来作为状态然后最短路。但这样会喜提常数 $n$，看起来 $n$ 很小，但是如果仔细分析，发现时间复杂度最差应该是 $O(((2^n+m) \log m ) \times n)$（假设使用Dijkstra堆优化），经过计算，最坏情况会达到 $10^8$ 以上。发现超过 $10^8$ 的部分并不多，基本只超过一点点，但是就是过不了，毕竟处理边的情况的时候常数也不小。但是只要复杂度除以一个 $n$ 就过了，所以问题出在储存方式。

众所周知，状态压缩是一个专门储存二进制的东西，题目正好每个字符只有两种状态，所以可以使用二进制形式储存，这样时间复杂度就除以了一个 $n$，实际上在计算边通往的状态时还是一样的时间，但是我们使用 Dijkstra 的优先队列储存时，时间就可以除以至少一个 $n$。SPFA 的队列类似。

现在大体知道思路了，来看看详细的应该怎么写。我们假设二进制的每一位 $1$ 表示这个 Bug 存在，那么初始状态应该是 $2^n-1$，即每一位都是 $1$。那么同理，终点状态应该是 $0$，即每一位都是 $0$。

接着，相信大家都会写如何计算这个状态通往的边了，先判断这个状态符不符合打补丁前的状态，再计算打补丁后的状态。然后按照 Dijkstra 或 SPFA 的模板来做即可。

最后，也是最重要的部分，UVa 的输出格式！！！

Talk is cheap, show me your code.

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,dist[1100000],c[110],f[1100000];
//dist表示从起始点到每个点的距离，f表示每个点是否访问过，Dijkstra 的模板
string a[110],b[110];
//a 字符串数组表示补丁的初始状态，b 字符串数组表示补丁修复后的状态，c 数组表示使用补丁所需时间（也即边权）
struct edge{
	int to,w;
	bool operator<(const edge &t)const{
		return w>t.w;
	}
};
priority_queue<edge>q;
int main(){
    //freopen("xx.in","r",stdin);
    //freopen("xx.ans","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    while(cin>>n>>m){
		if(n==0&&m==0){
			return 0;
		}
		for(int i=1;i<=m;i++){
			cin>>c[i]>>a[i]>>b[i];
		}
		memset(dist,0x3f,sizeof(dist));
		memset(f,0,sizeof(f));
		dist[(1<<n)-1]=0;
		q.push({(1<<n)-1,0});
		//初始化 Dijkstra
		while(!q.empty()){
			int p=q.top().to;
			q.pop();
			f[p]=1;
			for(int i=1;i<=m;i++){
				bool flag=1;
				//判断这个补丁是否能使用（开始）
				for(int j=0;j<n;j++){
					if(a[i][j]=='0'){
						continue;
					}
					if(a[i][j]=='+'&&(p&(1<<j))){
						continue;
					}
					if(a[i][j]=='-'&&!(p&(1<<j))){
						continue;
					}
					flag=0;
					break;
				}
				if(!flag){
					continue;
				}
				//判断这个补丁是否能使用（结束）
				//计算这个补丁使用后的状态（开始）
				int t=p;
				for(int j=0;j<n;j++){
					if(b[i][j]=='0'){
						continue;
					}
					if(b[i][j]=='+'){
						t|=(1<<j);
					}
					if(b[i][j]=='-'){
						t&=(~(1<<j));
					}
				}
				//计算这个补丁使用后的状态（结束）
				if(dist[t]>dist[p]+c[i]){
					//更新边权
					dist[t]=dist[p]+c[i];
					if(!f[t]){
						//纳入状态
						q.push({t,dist[t]});
					}
				}
			}
		}
		cout<<"Product "<<++t<<"\n";
		if(dist[0]==0x3f3f3f3f){
			cout<<"Bugs cannot be fixed.\n";
		}else{
			cout<<"Fastest sequence takes "<<dist[0]<<" seconds.\n";
		}
        cout<<"\n";//UVa 输出格式，警钟长鸣！！！
	}
    return 0;
}
```

---

## 作者：Pwtking (赞：1)

考察算法：

**最短路+状态压缩！** 

本篇题解更侧重为大家讲解一下本道题的做题思路，以及以后碰到此类提该如何解题。

首先读完题后先看数据范围，当看到 $n\le20$ 时，我们可以大体知道对这道题该使用什么算法：要么**爆搜**，要么**状压**。

我们可以考虑是否可以用状压解决。

首先先找到状压的对象，我们既然要状压，状压的数据范围肯定要小于 $30$，事实上小于 $25$ 为宜，那么状压**每个 bug 是否被修复**是个不错的选择。

选择完压缩的状态之后，就该考虑用什么算法实现解题了。仔细观察后发现，既然我们要使一个状态转移到另一个状态，何不考虑状压 dp 呢？但是先别急着做，我们再想想后发现，这些需要转移的状态是有后效性的，所以不能直接 dp。

那么我们该怎么办呢？

我们要求修复的时间最短，为何不采用最短路算法呢？

做法：

我们先考虑常规建边，但是把每个状态都建一条边会有 $2 \times 10^7$ 条边，这样跑最短路显然会超时。仔细思考后发现，其实**没必要建边**，**我们在跑最短路的时候直接判断每个状态的转移是否合法就行了**，这一点其他的题解已经讲得很详细了，我就不再赘叙啦 qwq。

解决完这个问题之后，本道题基本就可以切掉啦！

[AC 记录](https://www.luogu.com.cn/record/105026922)

如有不严谨的地方，欢迎及时在评论区艾特我。

END-

---

## 作者：eEfiuys (赞：1)

题目：[UVA658](https://www.luogu.com.cn/problem/UVA658)

~~我怎么觉得这是 Mojang 出的题呢？~~

### 输入：
- 具体格式见[P2761 软件补丁问题](https://www.luogu.com.cn/problem/P2761)。
	- 第 $1$ 行有 $2$ 个正整数 $n$ 和 $m$, $n$ 表示错误总数, $m$ 表示补丁总数, $1 \le n \le 20$, $1 \le m \le 100$。
	- 接下来 $m$ 行给出了 $m$ 个补丁的信息。每行包括一个正整数 $t_i$，表示运行补丁程序 $i$ 所需时间，以及 $2$ 个长度为 $n$ 的字符串，中间用一个空格符隔开。
		- 第 $1$ 个字符串中，如果第 $k$ 个字符为 ‘+’，则表示第 $k$ 个错误属于 $b1_i$，若为 ‘-’，则表示第 $k$ 个错误属于 $b2_i$，若为 ‘0’，则第 $k$ 个错误既不属于 $b1_i$ 也不属于 $b2_i$，即软件中是否包含第 $k$ 个错误并不影响补丁 $i$ 的可用性。
		- 第 $2$ 个字符串中，如果第 $k$ 个字符为 ‘-’，则表示第 $k$ 个错误属于 $f1_i$，若为 ‘+’，则表示第 $k$ 个错误属于 $f2_i$，若为 ‘0’，则第 $k$ 个错误既不属于 $f1_i$ 也不属于 $f2_i$，即软件中是否包含第 $k$ 个错误不会因使用补丁 $i$ 而改变。

### 算法：
- 最短路，**状压+BFS+优先队列**。
	- $now = 18$，即在二进制表示下为 $10010$，表示错误 $1$ 和 $4$ 未被修复。
   - 枚举每个补丁，能使用就更新状态，加到队列里。
   - 优先处理时间短的状态。
   - 如果 $now = 0$，即没有错误，就输出时间并返回。
   - 如果队列空了，但还有错误，就输出无法修复。
- **状压方式之位运算**：
	- 运算符：
		- 按位与```&```：全 $1$ 则 $1$ ，否则为 $0$。
		- 按位或```|```：有 $1$ 则 $1$ ，否则为 $0$。
		- 按位取反```~```：是 $0$ 则 $1$，是 $1$ 则 $0$。
		- 按位异或```^```：不同则 $1$，相同则 $0$。
		- 移位```>>```和```<<```：向右、向左移位。
   - 常用运算：
		- 集合取并：```A|B;```。
		- 集合取交：```A&B;```。
		- 集合相减：```A&~B;```。
		- 集合取反：```^A;```。
		- 置位：```A|=1<<bit;```。
		- 清位：```A&=~(1<<bit);```。
		- 测位：```(A&(1<<bit))!=0;```或```(A>>bit&1)!=0;```。
	- 其它运算：
		- 取最后一个非 $0$ 位：```A&-A;```或```A&~(A-1);```。
		- 统计非 $0$ 位:```For(;A;A-= A &-A)cnt++;```。
		- 取所有子集:```X=A;While(X)X=(X - 1)&A;```。

### 提示：
- 每组数据之间都要多输出一个**换行**。
- 记得**清空**数组和队列。

**hack 数据：**[658|udebug](https://www.udebug.com/UVa/658)

------------

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
char ch;
int t[101],b1[1<<20],b2[1<<20],f1[1<<20],f2[1<<20]; //见上。
bool v[1<<20]; //是否访问过当前状态。
struct node //结构体。
{
	int now,step; //now当前状态错误数量, step当前用时。
	bool operator<(const node &a)const //重载运算符，优先队列按step从小到大排序。
	{  
		return step>a.step;
	} 
}st;
priority_queue<node>q; //优先队列。
void bfs()
{	
	q.push(st);
	while(!q.empty()) //队列非空。
	{
		node k=q.top();
		q.pop();
		if(k.now==0) //当前状态没有错误，输出时间，返回。
		{
			printf("Fastest sequence takes %d seconds.\n\n",k.step);
			return;
		}
		if(v[k.now]) //重复的状态。
			continue;
		v[k.now]=1;
		for(int i=1;i<=m;i++) //枚举各种错误状态。
		{
			if((k.now|b1[i])!=k.now||(k.now&~b2[i])!=k.now) //不能使用该补丁。
				continue;
			node newn=k; //新状态。
			newn.now&=(~f1[i]);
			newn.now|=f2[i];
			newn.step+=t[i]; //增加用时。
			q.push(newn);
		}
	}
	printf("Bugs cannot be fixed.\n\n"); //队列空了还有错误，无法修复。
	return;
}
int main()
{
	cin>>n>>m; //先输入，不然都是0，不会进入多组数据的循环。
	for(int k=1;n!=0&&m!=0;k++) //多组数据。
	{
		memset(v,0,sizeof(v));
		memset(s,0,sizeof(s));
		memset(b1,0,sizeof(b1));
		memset(b2,0,sizeof(b2));
		memset(f1,0,sizeof(f1));
		memset(f2,0,sizeof(f2));
		while(!q.empty())
			q.pop();
		//清空。
		//队列没有clear(),因此逐个弹出未处理的状态。
		printf("Product %d\n",k); //先输出第几组数据。
		for(int i=1;i<=m;i++)
		{
			cin>>t[i];
			for(int j=1;j<=n;j++)
			{
				cin>>ch;
				if(ch=='+')
					b1[i]|=(1<<(j-1));
				else if(ch=='-')
					b2[i]|=(1<<(j-1));
			}
			for(int j=1;j<=n;j++)
			{
				cin>>ch;
				if(ch=='-')
					f1[i]|=(1<<(j-1));
				else if(ch=='+')
					f2[i]|=(1<<(j-1));
			}
		}
		//输入，见上，‘+’和‘-’位运算状压，‘0’不用处理。
		st.now=(1<<n)-1;
		st.step=0;
		//位运算状态压缩，初始化状态。
		bfs(); //广搜。
		cin>>n>>m; //最后输入，方便判断。
	}	
	return 0;
}
```

---

## 作者：hulean (赞：1)

## 【题意】

补丁在修正$BUG$时，有时也会引入新的$BUG$，假定有$n(n<=20)$个潜在$BUG$，和$m(m<=100)$个补丁，每个补丁用两个长度为$n$的字符串表示，其中字符串的每个位置表示一个$BUG$,第一个串表示打补丁之前的状态 **（“-”表示该$BUG$必须不存在，“+”表示该补丁必须存在，0表示无所谓）**，第二串表示打补丁之后的状态 **（"-"表示不存在，"+"表示存在，"0"表示不变）**。每个补丁有一定的执行时间，你的任务是用最小的时间把所有BUG都存在的软件变得没有$BUG$。

## 【算法】

 $\text{隐式图}$$SPFA$

## 【分析】

在任意时刻，每个$BUG$可能存在也可能不存在，所以可以用$n$位二进制串来表示当前软件的**状态**。打完补丁之后，软件的BUG状态会发生改变，对应**状态转移**。是不是很像动态规划？可惜动态规划是**行不通**的，因为状态经过多次转移之后可能会回到以前的状态，即状态图并不是**DAG**。如果**直接**用记忆化搜索，会出现**无限递归**。

**正确的方法**是把状态看成点，状态转移看成边，转化成图论中的**最短路径**问题，然后使用$Dijkstra$或$Bellman-Ford$算法进行求解。不过这道题和普通的最短路径问题不一样:节点很多，有$2^n$个，而且**很多状态根本遇不到**（即不管怎么打补丁，也不可能打成那种状态），所以**没有必要先将原图存储好**。

~~孩子咳嗽老不好，~~ **怎么办呢？**

这里介绍一种 **"隐式图"** 的方法，当需要得到某个点的所有边时，不是去读$G[u]$,而是直接枚举这$m$个补丁是否打的上。不管是$Dijkstra$还是$Bellman-Ford$算法，这个方法都适用。

- 一些本题的其他小技巧

> 得到$x$的二进制右起第$i$位:``x>>(i-1)&1``

> 把$x$二进制的右起第$i$位替换为$a$($a$或$0$或$1$）:``x^=(x&(1<<(i-1)))^(a<<(i-1))``

## 【代码】

思路也说得很清楚了，这里就不写注释了

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=20+10,MAXM=100+10;
int n,m;
struct Node
{
	int t;
	int a[MAXN];
	int b[MAXN];
}patch[MAXM];
int d[2000000];
int T;
inline void init(int k)
{
	cin>>patch[k].t;
	string s;
	cin>>s;
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='-')patch[k].a[i+1]=-1;
		else if(s[i]=='0')patch[k].a[i+1]=0;
		else patch[k].a[i+1]=1;
	}
	cin>>s;
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='-')patch[k].b[i+1]=-1;
		else if(s[i]=='0')patch[k].b[i+1]=0;
		else patch[k].b[i+1]=1;
	}
}
inline bool check(int sum,int k)
{
	for(int i=1;i<=n;i++)
	{
		if(patch[k].a[i]==0)continue;
		if(patch[k].a[i]==-1 && (sum>>(n-i)&1)==0 )continue;
		if(patch[k].a[i]==1 && (sum>>(n-i)&1)==1 )continue;
		return 0;
	}
	return 1;
}
inline int get(int sum,int k)
{
	for(int i=1;i<=n;i++)
	{
		if(patch[k].b[i]==0)continue;
		if(patch[k].b[i]==-1)sum^=(sum&(1<<(n-i)))^(0<<(n-i));
		else sum^=(sum&(1<<(n-i)))^(1<<(n-i));
	}
	return sum;
}
inline void SPFA()
{
	memset(d,0x3f,sizeof(d));
	queue<int>q;
	q.push((1<<n)-1);
	d[(1<<n)-1]=0;
	while(q.size())
	{
		int now=q.front();
		//cout<<now<<endl;
		q.pop();
		for(int i=1;i<=m;i++)
		{
			if(!check(now,i))continue;
			int x=get(now,i);
			//cout<<x<<endl;
			if(d[now]+patch[i].t<d[x])
			{
				d[x]=d[now]+patch[i].t;
				q.push(x);
			}
		}
	}
}
int main()
{
	//ios::sync_with_stdio(false);
	while(cin>>n>>m)
	{
		if(n==0&&m==0)break;
		T++;
		for(int i=1;i<=m;i++)
			init(i);
		//cout<<patch[1].a[1]<<" "<<patch[1].a[2]<<" "<<patch[1].a[3]<<endl;
		SPFA();
			printf("Product %d\n",T);
		if(d[0]==0x3f3f3f3f)
			printf("Bugs cannot be fixed.\n");
		else
			printf("Fastest sequence takes %d seconds.\n",d[0]);
		cout<<endl;
	}
	return 0;
}
```

**刘汝佳大法好！**

---

## 作者：_liet (赞：1)

这里可以把一个二进制数看做状态，1 表示该位置有 bug，0 表示该位置没有 bug。

然后把状态看做顶点，补丁看做边，用 dijkstra 求一下从初状态到末状态的最短路就可以了。

代码如下：
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#define MAXVERTEX 1100000
#define MAXEDGE 110
#define INF 999999999
typedef long long ll;
using namespace std;

int dis[MAXVERTEX], vis[MAXVERTEX];
int len, patches;

struct Patch {
    int t;
    string from, to;

    Patch(int t = 0, string from = "", string to = ""):
    t(t), from(from), to(to) {}

    // 计算打完这个补丁之后的状态
    int fix(int state) const {
        int res = 0;
        for (int i = 0; i < len; i++) {
            if (to[i] == '+')
                res += 1;
            else if (to[i] == '0')
                res += 1 & (state >> (len - i - 1));
            res <<= 1;
        }
        // 因为在 for 循环执行完之后 res 会多左移一位
        // 所以这里需要右移一位
        res >>= 1;
        return res;
    }

    // 判断当前状态是否可以打上这个补丁
    bool canFix(int state) const {
        for (int i = 0; i < len; i++) {
            if (from[i] == '+' && !(1 & (state >> (len - i - 1))))
                return false;
            if (from[i] == '-' && (1 & (state >> (len - i - 1))))
                return false;
        }
        return true;
    }
} patch[MAXEDGE];

int dijkstra(int begin, int end) {
    // 以下为 dijkstra 常规操作
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > heap;
    for (int i = 0; i <= 1 << len; i++) {
        dis[i] = INF;
        vis[i] = 0;
    }
    dis[begin] = 0;
    heap.push(make_pair(0, begin));
    while (!heap.empty()) {
        int u = heap.top().second;
        if (u == end) return dis[end];
        heap.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = 0; i < patches; i++) {
            if (patch[i].canFix(u)) {
                int v = patch[i].fix(u);
                int w = patch[i].t;
                if (!vis[v]) {
                    if (dis[v] > dis[u] + w) {
                        dis[v] = dis[u] + w;
                        heap.push(make_pair(dis[v], v));
                    }
                }
            }
        }
    }
    return dis[end];
}

int main() {
    int counter = 0, t;
    string from, to;

    ios::sync_with_stdio(false);
    while (cin >> len >> patches) {
        if (len == 0 && patches == 0) break;

        for (int i = 0; i < patches; i++) {
            cin >> t >> from >> to;
            patch[i] = Patch(t, from, to);
        }

        // 最开始的状态应该是每一位上都是 1
        int begin = (1 << len) - 1;

        int ans = dijkstra(begin, 0);
        cout << "Product " << ++counter << endl;
        if (ans == INF) { // 如果得出的最短时间是无限长的则表示不可修复
            cout << "Bugs cannot be fixed." << endl;
        } else {
            cout << "Fastest sequence takes " << ans << " seconds." << endl;
        }
        cout << endl; // 注意最后需要输出一行空行
    }

    return 0;
}
```

---

## 作者：LionBlaze (赞：0)

这题居然还能交题解。

显然，通过“最短时间”想到 Dijkstra，状态可以使用 `array<bool, 20>` 表示，但是我们可以使用 `bitset` 的策略——状压。

考虑二进制，每一位对应一个 bug，如果是 $1$ 则表示有这个 bug，如果是 $0$ 则表示没有这个 bug。

考虑时间复杂度。对于每一种状态，打完补丁后的状态都是唯一确定的（可能不存在），最多有 $m2^n$ 条边，显然有 $2^n$ 个点，优先队列（二叉堆）优化的时间复杂度是 $\mathcal O(nm2^n)$，理论上可能不行，实际上可以通过。

但是可能这题实际上并不会有这么多边，有时间搞个严谨证明或者 hack。

斐波那契堆优化的时间复杂度是正确的。

---

## 作者：lihongqian__int128 (赞：0)

看到 $n\le20$，考虑状压。把当前状态设成 $s$，若二进制下从左到右第 $i$ 为是 $1$，表示第 $i$ 个问题仍存在，否则表示第 $i$ 个问题不存在。

判断是否包含必须包含的错误：把必须包含的错误看作一个二进制数 $B_1$（意义同上），若当前状态为 $s$，则当 $s\operatorname{and}B_1=B_1$ 时包含必须包含的错误。其余条件的判断的同理。

跑个最短路即可。

时间复杂度：$\Theta(mn)$。

注意本题的输出格式……

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1<<20,M=105;
int n,m,ti[M],b1[M],b2[M],f1[M],f2[M],dis[N];
bool vis[N];
struct node{
	int p,v;
	bool operator<(const node&_)const{return v>_.v;}
};
void dij(){
	priority_queue<node>q;
	int s=(1<<n)-1;
	q.push({s,0});dis[s]=0;
	while(!q.empty()){
		int t=q.top().p;q.pop();
		if(vis[t])continue;
		vis[t]=1;
		for(int i=1;i<=m;i++){
			int g=t;
			if((g&b1[i])!=b1[i])continue;
			if((g&b2[i])!=0)continue;
			g^=(g&f1[i]);
			g|=f2[i];
			if(dis[g]<=dis[t]+ti[i])continue;
			dis[g]=dis[t]+ti[i];
			q.push({g,dis[g]});
		}
	}
}
int cnt;
int _main(){
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	for(int i=1;i<=m;i++){
		cin>>ti[i];
		char c;
		b1[i]=b2[i]=f1[i]=f2[i]=0;
		for(int j=0;j<n;j++){
			cin>>c;
			if(c=='+')b1[i]|=(1<<j);
			if(c=='-')b2[i]|=(1<<j);
		}
		for(int j=0;j<n;j++){
			cin>>c;
			if(c=='+')f2[i]|=(1<<j);
			if(c=='-')f1[i]|=(1<<j);
		}
	}
	dij();
	cnt++;
	cout<<"Product "<<cnt<<'\n';
	if(dis[0]==0x3f3f3f3f)cout<<"Bugs cannot be fixed.\n";
	else cout<<"Fastest sequence takes "<<dis[0]<<" seconds.\n";
	cout<<'\n';
	return 0;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	while(cin>>n>>m&&n&&m)_main();
	return 0;
}
```

---

## 作者：LionBlaze (赞：0)

update：增加时间复杂度分析。

这道题拿到手一看就能发现是一道最短路题。显然，所有 Bug 的状态是图中的节点，而补丁就是边。

但是这道题比较特殊的地方，就是：如何表达一种状态，比如“有第 $1, 3, 4$ 个 Bug，没有第 $2, 5$ 个 Bug”呢？

我们可以显而易见地想到一种方法：用一个字符串表达，字符串中的字符就表示一个 Bug 是否存在。比如上面所说的状态就可以表示为 $\texttt{YNYYN}$。

但是，我们的节点可是要直接当做下标来用的，这时怎么办？难不成直接一个 `arr["YNYYN"]`？虽然 C++ 里有 $\Theta(\log n)$ 的自动排序的基于红黑树的 `map` 或者 $\Theta(1)$ 的不会自动排序的基于哈希表的 `unordered_map`，可以做到这一点。但这莫非也太费空间了一点，并且常数很大。

但是，我们注意到数据范围 $n \le 20$，我们就可以使用一个数字来存储一个状态，比如前面说的状态就可以使用 $10110$ 来表达。

但是这样似乎更不行了，因为这里的数字最大需要是 $11,111,111,111,111,111,111$（别数了，有 $20$ 个 $1$），数组都开不下。

但是，我们看到一长串的 $0$ 和 $1$，发现：

**这不完全是二进制吗？**

于是我们就可以用一个二进制数来存储。最大值是 $(11,111,111,111,111,111,111)_2$，也就是 $2^{20} - 1 = 1048575$，完全可以开的下。

所以，我们的问题就完全转化为了一个正权图上的最短路问题，可以使用堆优化的 Dijkstra 算法解决。

最终代码（只放关键部分）：
```cpp
class patch //补丁
{
public:
	int dist; //打补丁的时间
	string before, after; //打补丁的条件以及修复的 Bug
} patches[105];

int step[1 << 21]; //最短路径长度

bool can(int num, string str) //现在状态为 num，可不可以打条件为 str 的补丁
{
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '0') continue;
		if (str[i] == '-' &&  (num & (1 << i))) return false;
		if (str[i] == '+' && !(num & (1 << i))) return false;
	}
	return true;
}

int go(int num, string str) //现在状态为 num，打了修复 str 表示的 Bug 之后的状态
{
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '0') continue;
		if (str[i] == '+') num |=  (1 << i);
		if (str[i] == '-') num &= ~(1 << i);
	}
	return num;
}

int Dijkstra(int s, int t, int m) //Dijkstra 算法
{
	memset(step, 0x3f, sizeof step); //初始化为正无穷大
	step[s] = 0;
	class node
	{
	public:
		int id, dist;
		bool operator<(const node& y) const { return dist > y.dist; } //重载小于号，因为要用 priority_queue
	};
	priority_queue<node> pq;
	pq.push({ s, 0 });
	while (!pq.empty())
	{
		node u = pq.top();
		pq.pop();
		if (u.dist > step[u.id]) continue;
		for (int i = 1; i <= m; i++)
		{
			if (!can(u.id, patches[i].before)) continue; //如果不能打补丁，直接跳过
			int v = go(u.id, patches[i].after); //打完补丁之后的状态
			if (u.dist + patches[i].dist < step[v]) //松弛
			{
				step[v] = u.dist + patches[i].dist;
				pq.push({ v, step[v] });
			}
		}
	}
	return step[t];
}
```
时间复杂度：

Dijkstra 是 $\Theta(m \log n)$，其中 $m$ 在极端情况下，每个补丁都可以从任何一个节点到其他节点（也就是所有补丁都是 `x 000 xxx`，所有状态都可以使用），则一共有 $100n$ 条边，时间复杂度也就是 $\Theta(n \log n)$（虽然常数有点大）。

而每次松弛都要判断是否可以使用，时间复杂度 $\Theta(n)$。

总时间复杂度 $\Theta(n^2 \log n)$，对于此题的 $n \le 20$ 可以通过。

---

## 作者：zhenjianuo2025 (赞：0)

## 描述

有 $n$ 个错误，$m$ 个补丁程序。

每一个补丁程序都有其特定的适用环境，某个补丁只有在软件中**包含某些错误**而同时又**不包含另一些错误**时才可以使用。一个补丁在**修复某些错误**的同时，也会**加入另一些错误**。运行每个补丁也会耗费一定的时间。

试求出修复所有错误的情况下，最小的总耗时。

## 思路

状压，设当前状态为二进制数 $S$，$S$ 即每个错误的修复情况。该位为 $0$ 表示该错误尚未被修复，$1$ 表示改错误已经被修复。

对于当前状态，枚举使用哪个补丁，按照最短路模式进行转移即可。

## 代码

```cpp
#include <cmath>
#include <queue>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
int n, m, tim[110], hav[110], dha[110], del[110], add[110], dis[1 << 21]; 
bool vis[1 << 21];
signed main() {
	int cas = 0;
	while (1) {
		cin >> n >> m;
		if (n == 0 && m == 0) return 0;
		for (int i = 1; i <= m; i++) {
			cin >> tim[i];
			hav[i] = 0, dha[i] = 0, del[i] = (1 << n) - 1, add[i] = 0;
			for (int j = 1; j <= n; j++) {
				char c;
				cin >> c;
				if (c == '+') hav[i] |= (1 << (j - 1));
				else if (c == '-') dha[i] |= (1 << (j - 1));
			}
			for (int j = 1; j <= n; j++) {
				char c;
				cin >> c;
				if (c == '-') del[i] -= (1 << (j - 1));
				else if (c == '+') add[i] |= (1 << (j - 1));
			}
		}
		for (int i = 0; i < (1 << n); i++) dis[i] = 1e9;
		dis[(1 << n) - 1] = 0;
		queue<int> q;
		q.push((1 << n) - 1);
		while (!q.empty()) {
			int top = q.front(); q.pop();
			vis[top] = 0;
			for (int i = 1; i <= m; i++) {
				if ((top | hav[i]) == top && (top & dha[i]) == 0) {
					int nxt = top & del[i] | add[i];
					if (dis[nxt] > dis[top] + tim[i]) {
						dis[nxt] = dis[top] + tim[i];
						if (!vis[nxt]) {
							vis[nxt] = 1;
							q.push(nxt);
						}
					}
				} 
			}
		}
		++cas;
		cout << "Product " << cas << "\n";
		if (dis[0] == 1e9) cout << "Bugs cannot be fixed.\n";
		else cout << "Fastest sequence takes " << (dis[0] == 1e9 ? 0 : dis[0]) << " seconds.\n";
		cout << "\n";
	}
	return 0;
}
```


---

## 作者：_Ad_Astra_ (赞：0)

一道有趣的最短路题。

这道题其实跟[P2761 软件补丁问题](https://www.luogu.com.cn/problem/P2761)除了多组数据几乎一样，可以算是双倍经验。

观察 bug 只有两种状态：有或没有。而且 $n \le 20$，很容易想到状压，当前这位是 $1$ 表示有这个 bug，$0$ 表示没有，那么总共就有 $2^n$ 种状态，初始时为 $2^n-1$，结束时为 $0$。然后就可以把这些状态当成点，然后建边跑最短路。

但是由于点数最多会达到 $2^{20} \approx 10^6$，跑 Dijkstra 肯定会TLE。其实有很多状态都是达不到的，我们可以优化掉这些点。我们可以先处理出 $b1,b2,f1,f2$ 四个数组，$b1_i$ 记录运行这个补丁需要的 bug，它的第 $j$ 位表示运行这个补丁需要第 $j$ 个 bug，同理 $b2_i$ 记录运行这个补丁不能有的 bug，$f1_i$ 记录运行这个补丁后新增的 bug，$f2_i$ 记录运行这个补丁后修复的 bug。那么我们可以先预处理出来，然后 Dijkstra 里原来找节点 $u$ 到的节点的部分就可以替换成枚举使用的补丁 $i$ ，判断 $u$ 是否包含 $b1_i$ 里的所有 bug 且不包含 $b2_i$ 里的所有 bug 即可，那么转移到的 $v$ 节点即是 $u$ 加上 $f1_i$ 的所有 bug，减去 $f2_i$ 的所有 bug。

判断的过程使用了一点位运算技巧，把 bug 进行状态压缩的好处就在这里：因为 $u$ 必须包含 $b1_i$ 的所有 $1$，那么 $u\ \& \ b1_i$ 必须等于 $b1_i$，同时 $u$ 还不能包含 $b2_i$ 的任何 $0$，那只要判断 $u \ \& \ b2_i = 0$ 即可。

求转移到的 $v$ 也可以用位运算。首先要包含 $f1_i$ 的所有 bug，那就是 $u\ | \ f1_i$ ；同时还要去除 $f2_i$ 的所有 bug，那就还要再 $| \ f2_i \ \oplus \ f2_i$，也就是 $v = u\ | \ f1_i \ | \ f2_i \ \oplus \ f2_i$ 。

code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int inf=0x3f3f3f3f3f3f3f3f;
int n,m,a[110],b1[110],b2[110],f1[110],f2[110];
const int maxn=1<<25;
int vis[maxn],dis[maxn];
int k;
struct node
{
    int v,d;
    node(){}
    node(int _v,int _d)
    {
        v=_v,d=_d;
    }
    bool operator <(const node &b)const
    {
        return d>b.d;
    }
};
priority_queue<node>pq;
void dij(int s)
{
    memset(vis,0,sizeof(vis));
    while(!pq.empty())pq.pop();
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    pq.push(node(s,dis[s]));
    while(!pq.empty())
    {
        node t=pq.top();pq.pop();
        int u=t.v;
        if(vis[u])continue;
        vis[u]=1;
        for(int i=1;i<=m;i++)
        	if((u&b1[i])==b1[i]&&!(u&b2[i]))//判断能否使用补丁
        	{
        		int v=((u|f1[i])^f1[i])|f2[i];//计算v
        		if(dis[u]+a[i]<dis[v])
        		{
        			dis[v]=dis[u]+a[i];
        			if(!vis[v])pq.push(node(v,dis[v]));
				}
			}
    }
} 
void solve(int id)
{
	k=(1<<n);
	memset(b1,0,sizeof(b1));
	memset(b2,0,sizeof(b2));
    memset(f1,0,sizeof(f1));
    memset(f2,0,sizeof(f2));
	for(int i=1;i<=m;i++)
	{
		string x,y;
		cin>>a[i]>>x>>y;
		for(int j=0;j<n;j++)
			if(x[j]=='+')b1[i]|=(1<<(n-j-1));
			else if(x[j]=='-')b2[i]|=(1<<(n-j-1));
		for(int j=0;j<n;j++)
			if(y[j]=='-')f1[i]|=(1<<(n-j-1));
			else if(y[j]=='+')f2[i]|=(1<<(n-j-1));
	}//预处理b1，b2，f1和f2
	dij(k-1);
	cout<<"Product "<<id<<endl;
	if(dis[0]<inf)cout<<"Fastest sequence takes "<<dis[0]<<" seconds.";
	else cout<<"Bugs cannot be fixed.";
	cout<<endl<<endl;
}
signed main()
{
	int t=0;
	while(cin>>n>>m&&n+m!=0)solve(++t);
	return 0; 
}
```

---

