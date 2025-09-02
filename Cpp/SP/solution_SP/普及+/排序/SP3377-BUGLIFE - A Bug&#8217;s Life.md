# BUGLIFE - A Bug&#8217;s Life

## 题目描述

Professor Hopper is researching the sexual behavior of a rare species of bugs. He assumes that they feature two different genders and that they only interact with bugs of the opposite gender. In his experiment, individual bugs and their interactions were easy to identify, because numbers were printed on their backs.  
  
 Given a list of bug interactions, decide whether the experiment supports his assumption of two genders with no homosexual bugs or if it contains some bug interactions that falsify it.

## 样例 #1

### 输入

```
2
3 3
1 2
2 3
1 3
4 2
1 2
3 4```

### 输出

```
Scenario #1:
Suspicious bugs found!
Scenario #2:
No suspicious bugs found!```

# 题解

## 作者：rui_er (赞：7)

很久以前 AC 了这题，现在补一个题解。

题意简述：有若干个虫子，它们之间有一些关♂系，要判断它们之间有没有同性恋。

那么什么情况会出现同性恋呢？题目中有关系的虫子连成一个无向图，如果有长度为奇数的环，那么一定有同性恋；如果不存在长度为奇数的环，那么也不一定存在同性恋。大家可以画个图理解一下。

于是原题转换为：给定一个无向图，求图中是否有长度为奇数的环。

看到其他题解都在写种类并查集，我们来个简单的，新手也可以看懂的方法——**0/1 染色 dfs**。

我们这里将虫子划分为两类：“颜色”（这里代表性别）为 $1$ 或 $2$，用 $0$ 表示还没有搜索到。每一次遍历从当前点 $u$ 为起点的所有的边 $e(u,v)$，如果 $u$ 和 $v$ 颜色相同，意味着有同性恋。如果 $v$ 没有被染色，那么 dfs 到 $v$，颜色取反（$3-col$）。

时间复杂度分析：对于每一组数据，每个点最多被遍历（染色）一次，所以时间复杂度为 $O(n)$；原题有 $T$ 组数据，时间复杂度为 $O(Tn)$，可以通过此题。

代码（有一些注释）：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
using namespace std;
const int N = 2005, M = (int)(1e6+5)<<1;

int T, n, m, ans;
int col[N];

struct Edge { // 前向星建图
	int v, nxt;
	Edge() {}
	Edge(int a, int b) : v(a), nxt(b) {}
}e[M];
int ne, h[N];
void add(int u, int v) {
	e[++ne] = Edge(v, h[u]);
	h[u] = ne;
	e[++ne] = Edge(u, h[v]);
	h[v] = ne;
} 

void dfs(int u, int c) { // 0/1 染色 dfs，两个参数分别是当前点编号和颜色
	col[u] = c;
	for(int i=h[u];i;i=e[i].nxt) {
		int v = e[i].v;
		if(col[v] == col[u]) {
			ans = 0;
			break;
		}
		if(!col[v]) {
			dfs(v, 3-c);
		}
	}
}

int main() {
	scanf("%d", &T);
	for(int _=1;_<=T;_++) {
		memset(e, 0, sizeof(e));
		memset(h, 0, sizeof(h));
		memset(col, 0, sizeof(col));
		ne = 0;
		ans = 1;
		printf("Scenario #%d:\n", _);
		scanf("%d%d", &n, &m);
		for(int i=1;i<=m;i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			add(u, v);
		}
		for(int i=1;i<=n;i++) { // 对于每一个未被染色的点（新连通块），进行 dfs，与 tarjan 算法类似
			if(ans && !col[i]) {
				dfs(i, 1);
			}
		}
		if(ans) {
			puts("No suspicious bugs found!");
		}
		else {
			puts("Suspicious bugs found!");
		}
	}
	return 0;
}
```

---

## 作者：Сontіnuе (赞：6)

# 思路
我使用的方法是**种类并查集**，这样来看这道题相当于弱化版的食物链。

提供一种思路，就是**开两倍空间**，$n$ 以后的表异性。

简单来说就是 $1$ 到 $n$ 是输入的编号，$(n+1)$ 到 $(2*n)$ 是表异性关系的编号，其一一对应着 $1$ 到 $n$ 的编号。

更详细的，**举个例子**：

若有两只虫子 $x$ 和 $y$ 有关系，放在并查集里的体现就是 $x$ **和 $y+n$ 有关系**；从 $y$ 的角度看就是 $y$ **与 $x+n$ 有关系**，因此，请注意，**这里就代表 $x$ 和 $y$ 有异性关系**。

综上，本方法换句话说，就相当于**用一倍空间的代价，省去了异或的麻烦。** 虽然在这里看起来比较无意义，但是在麻烦一点的题（比如[食物链](https://www.luogu.com.cn/problem/P2024)）里，这种方法也是相对容易些的。

其他的看代码比较容易理解。里面有注释。

# 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn=1e6+10;
const int inf=1<<30;

int n,m;

int fa[maxn<<1];

inline int GetFather(int x)
{
	return x==fa[x] ? x : fa[x]=GetFather(fa[x]); //路径压缩
}

inline void Uni(int x,int y) //连接
{
	int f1=GetFather(x);
	int f2=GetFather(y);
	if(f1!=f2)
		fa[f1]=f2;
}

inline bool Judge(int x,int y) //判断是不是一个性别
{
	return GetFather(x)==GetFather(y);
}

int temp;

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		temp++;
		scanf("%d%d",&n,&m);
		memset(fa,0,sizeof(fa));
		int flag=0;
		for(int i=1;i<=2*n;i++)
			fa[i]=i; //因为要用到2*n的空间表异性，所以初始化2倍
		while(m--)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			if((x==y) || (x>n) || (y>n)) //好像没有特别提到自己喜欢自己 和 输入大于种类的情况，但特判一下总没有问题
			{
				printf("Scenario #%d:\nSuspicious bugs found!\n",temp);
				flag=1;
				break;
			}
			if(Judge(x,y)) //如果同一个根，则同性
			{
				printf("Scenario #%d:\nSuspicious bugs found!\n",temp);
				flag=1;
				break;
			}
			Uni(x+n,y);
			Uni(x,y+n); //标记异性关系
		}
		if(!flag) //不是同性就是异性
			printf("Scenario #%d:\nNo suspicious bugs found!\n",temp);
//		printf("\n"); //poj里面要输出空行
	}
	return 0;
}
```

# 鸣谢
特别谢谢 @talaodi 大佬的帮助……！没有他我一辈子都过不了这道题……

---

## 作者：猪龙骨丶丶 (赞：5)

# ****更简单的并查集写法****
一道判定二分图的题，大家都是黑白染色写，~~自我认为~~我用的是比现有题解都简单的**并查集**
 
 find（i）为i的对象所在集合，你喜欢老婆的老公那么你就是同性恋，即find（a）==find（b）时，a和b时同性恋，love【i】为i的对象。代码很短。
 ```cpp
	for(int i=1;i<=m;i++){
			scanf("%d%d",&a,&b);
			if(find(a)==find(b))
				flag=1;
			if(love[a])f[find(b)]=find(love[a]);
			if(love[b])f[find(a)]=find(love[b]);
			love[a]=f[b],love[b]=f[a];
		}
```



---

## 作者：SymphonyOfEuler (赞：2)

#### 题目意思：

给出一系列的关系，询问在这么多有关系的虫子中是否存在“同性恋”。如果有同性恋，输出 “Suspicious bugs found!”；没有则输出 “No suspicious bugs found!”。

#### 思路：

这道题可以用并查集来实现，在并查集的基础上加上一个数组表示点到根的距离，如果距离为 $0$ 表示同性，$1$ 表示异性，每次得到距离模 $2$。

得到一组关系 $x,y$，首先判断是否在一个集合上，若真，则判断是不是异性（距离为1），否则把它们合并。

放一下并查集的代码还有solve()里面的。

```
struct Weighted_Union_Find_Set { //并查集
    int find(int x) {//查找
        if (father[x] == x) return x;
        int fa = father[x];
        father[x] = find(fa);
        dis[x] = (dis[x] + dis[fa]) % 2;
        return father[x];
    }

    void merge(int x, int y) {//合并
        int fx = find(x);
        int fy = find(y);
        father[fx] = fy;
        dis[fx] = (1 + dis[y] - dis[x]) % 2;
    }

    inline void father_init() {//初始化
        for (int i = 1; i <= n; ++i) {
            father[i] = i;
            dis[i] = 0;
        }
    }
} WUFS;
```


```
void solve() { //解决
    int t, ccase = 0;
    cin >> t;
    while (t--) {
        ccase++;
        bool flag = false;
        cin >> n >> m;
        WUFS.father_init();
        for (int i = 0; i < m; ++i) {
            int x, y;
            cin >> x >> y;
            if (WUFS.find(x) == WUFS.find(y)) {//判断
                if (abs(dis[x] - dis[y] + 2) % 2 == 0) flag = true;//距离为1
            } else WUFS.merge(x, y);//否则合并
        }
        cout << "Scenario #" << ccase << ":\n";
        if (flag) {
            cout << "Suspicious bugs found!\n";
            continue;
        }
        cout << "No suspicious bugs found!\n";
    }
}
```


---

## 作者：EuphoricStar (赞：1)

## 思路

我们把虫子的性别看做黑色或白色，把关系看做边，那么这道题就转换成了二分图判定问题。

因此只需要对每个连通块做一次 DFS 染色，如果发现颜色矛盾就立刻退出搜索。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, head[2020], len, c[2020], t;
struct edge {
    int to, next;
} edges[2000100];

void add_edge(int u, int v) {
    edges[++len] = (edge){v, head[u]};
    head[u] = len;
}

bool check(int u) {
    for (int i = head[u]; i; i = edges[i].next) {
        int v = edges[i].to;
        if (c[u] == c[v]) {
            return 0;
        }
        if (!c[v]) {
            c[v] = 3 - c[u];
            if (!check(v)) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    scanf("%d", &t);
    for (int _ = 1; _ <= t; ++_) {
        scanf("%d%d", &n, &m);
        memset(head, 0, sizeof(head));
        memset(edges, 0, sizeof(edges));
        memset(c, 0, sizeof(c));
        len = 0;
        while (m--) {
            int u, v;
            scanf("%d%d", &u, &v);
            add_edge(u, v);
            add_edge(v, u);
        }
        printf("Scenario #%d:\n", _);
        bool flag = 1;
        for (int i = 1; i <= n; ++i) {
            if (!c[i]) {
                c[i] = 1;
                if (!check(i)) {
                    flag = 0;
                    break;
                }
            }
        }
        puts(flag ? "No suspicious bugs found!" : "Suspicious bugs found!");
    }
    return 0;
}
```


---

## 作者：HDWR (赞：1)

本文同步发布于[Handwer's Blog](https://blog.handwer-std.top/) 

# 题目描述

见题面。

# 解题思路

显然这是一个并查集，但并不是一个裸的并查集

我们要多维护一个数组`rel[]`，其中`rel[i]`表示`i`和它的祖先的关系（relative）。我们定义`rel[i]`表示两种性别，当根节点相同且`rel[]`相同时，它们就是同性恋

`rel[]`的更新方式：

```
(in Find(x))
rel[x] = (rel[x] + rel[U[x]]) % 2;
```
```
(in Union(x, y))
int fx = Find(x), fy = Find(y);
...
rel[fx] = (rel[x] + rel[y] + 1) % 2;
```

`rel[]`的判断方式：
```
(in Union(x, y))
if (fx == fy) {
	if (rel[x] == rel[y]) suspiciousFound = true;
    return;
}
```

剩下的照常写就行

注意路径压缩要分开写，先创建一个变量存它的祖先节点再更新 

~~按秩合并没写过不知道~~

# 代码实现

~~你们最喜欢的~~代码实现：
```
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXM = 1000000 + 10;

int n, m;
int U[MAXM], rel[MAXM];

bool flag;

int Find(int x) {
    if (x != U[x]) {
    	// 把路径压缩撑开写
        int fux = Find(U[x]);
        rel[x] = (rel[x] + rel[U[x]]) % 2; // 更新rel数组
        // 1 1 -> 0
        // 1 0 / 0 1 -> 1
        // 0 0 -> 0
        // 其实是一个异或的过程
        U[x] = fux； // qwq
    }
    return U[x];
}

void Union(int x, int y) {
    int fx = Find(x), fy = Find(y);
    if (fx == fy) {
        if (rel[x] == rel[y]) flag = true; // 判断是否同性
        return;
    }
    U[fx] = fy;
    rel[fx] = (rel[x] + rel[y] + 1) % 2; // 更新rel数组
}

int main(int argc, char *const argv[]) {
    int t;
    scanf("%d", &t);
    int _t = 0;
    while (t --> 0) {
        memset(U, 0, sizeof(U));
        memset(rel, 0, sizeof(rel));
        n = 0, m = 0, flag = false;
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; ++i) U[i] = i;
        for (int i = 1; i <= m; ++i) {
            int x, y;
            scanf("%d %d", &x, &y);
            Union(x, y);
        }
        printf("Scenario #%d:\n", ++_t);
        if (flag) printf("Suspicious bugs found!\n");
        else printf("No suspicious bugs found!\n");
    }
    return 3; // qwq
}

```



---

## 作者：Little09 (赞：1)

二分图判定模板题（不知道为什么蓝）。

如果没有同性恋，那么很显然是一张二分图，否则不是。那么只要判定这张图是不是二分图即可。

一个图是二分图，当且仅当图中没有奇环。所以黑白染色即可。

多测记得清空。

```cpp
#include<bits/stdc++.h>
using namespace std; 
int T,n,m;
int h[2000001],t[2000001],nxt[2000001],cnt;
int col[2000001];
bool flag;
void add(int x,int y)
{
	t[++cnt]=y;
	nxt[cnt]=h[x];
	h[x]=cnt;
}
void dfs(int x,int coler)
{
	col[x]=coler;
	for (int i=h[x];i;i=nxt[i])
	{
		if (col[t[i]]!=-1)
		{
			if (col[t[i]]!=3-coler) flag=1;
		}
		else dfs(t[i],3-coler);
	}
}
int main()
{
	cin >> T;
	for (int _=1;_<=T;_++)
	{
		cin >> n >> m;
		flag=0;
		for (int i=1;i<=n;i++) h[i]=0,col[i]=-1;
		for (int i=1;i<=m;i++)
		{
			int x,y;
			cin >> x >> y;
			add(x,y),add(y,x);
		}
		for (int i=1;i<=n;i++)
		{
			if (col[i]==-1) dfs(i,1);
			if (flag)
			{
				printf("Scenario #%d:\nSuspicious bugs found!\n",_);
				goto no;
			}
		}
		printf("Scenario #%d:\nNo suspicious bugs found!\n",_);
		no:; 
	}
	return 0;
}
```


---

## 作者：RainAir (赞：1)

## 题目描述

题目询问在这么多有关系的虫子中是否存在“同性恋”。
也就是说你给他们分配性别，问是否无论怎么分配都会存在“同性恋”。

## 解题报告

我们不妨把这些虫子看成 $n$ 个点，每个关系看成一条无向边。我们把男性看成白色，女性看成黑色，那么我们考虑存在题目描述的情况的时候图的形态。

1. 形成非环结构：这样一定不会存在这种情况，你可以对其进行一次类似拓扑排序的操作来分配性别。

2. 形成偶环结构：这样自己画一下发现也是有分配方案的

3. 形成奇环结构：这样是不能找出一种性别分配方案的

于是题目转化为：判断一个无向图是否存在奇环。

判断奇环的一种方法是对其进行二分图染色，如果存在合法的染色方案就不存在同性恋情况，否则存在。

当然这个题目可以用带权并查集直接维护子节点和父节点的关系来判断即可，这里不再详细阐述（为了给后面的人留坑 qwq）

## 代码
```c++
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2000 + 5;
const int MAXM = 1000000 + 5;

namespace fastIO{ 
    #define BUF_SIZE 100000 
    #define OUT_SIZE 100000 
    #define ll long long 
    bool IOerror=0; 
    inline char nc(){ 
        static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE; 
        if (p1==pend){ 
            p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin); 
            if (pend==p1){IOerror=1;return -1;} 
        } 
        return *p1++; 
    } 
    inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';} 
    inline void read(int &x){ 
        bool sign=0; char ch=nc(); x=0; 
        for (;blank(ch);ch=nc()); 
        if (IOerror)return; 
        if (ch=='-')sign=1,ch=nc(); 
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0'; 
        if (sign)x=-x; 
    } 
    inline void read(ll &x){ 
        bool sign=0; char ch=nc(); x=0; 
        for (;blank(ch);ch=nc()); 
        if (IOerror)return; 
        if (ch=='-')sign=1,ch=nc(); 
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0'; 
        if (sign)x=-x; 
    } 
    #undef ll 
    #undef OUT_SIZE 
    #undef BUF_SIZE 
}; 
using namespace fastIO;

struct Node{
    struct Edge *firstEdge;
    int opt;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next;
}pool[MAXM<<1],*frog = pool;

Edge *New(Node *s,Node *t){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;
    ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v){
    node[u].firstEdge = New(&node[u],&node[v]);
    node[v].firstEdge = New(&node[v],&node[u]);
}

bool dfs(Node *v){
    for(Edge *e = v->firstEdge;e;e = e->next){
        if(e->t->opt == v->opt) return false;
        if(!e->t->opt){
            e->t->opt = 3 - v->opt;
            if(!dfs(e->t)) return false;
        }
    }
    return true;
}

int cnt,N,M;
bool flag = true;

inline void Solve(){
    printf("Scenario #%d:\n",++cnt);
    frog = pool;flag = true;CLR(node,0);
    read(N);read(M);
    FOR(i,1,N) node[i].opt = 0;
    FOR(i,1,M){
        int u,v;
        read(u);read(v);
        add(u,v);
    }
    FOR(i,1,N)
        if(!node[i].opt) node[i].opt = 1,flag &= dfs(&node[i]);
    printf("%s\n",flag ? "No suspicious bugs found!" : "Suspicious bugs found!");
}

int main(){
    int T;read(T);
    while(T--) Solve();
    return 0;
}
```

---

## 作者：_Revenge_ (赞：0)

### 题目简化和分析：   

前言：~~这题目背景真奇怪。~~   

我们可以将每种关系，看成一条边，如果出现**奇数边**环就不满足。  
例如：$a,b$ 异性 $a,c$ 异性 $b,c$异性 这种情况是不满足的。    
相当与一个**奇数边**环。   

所以我们就的考虑如何判断环，我们可以使用**二分图染色**。  
如果一条边的两个端点的颜色一致，则是**奇数边**环。    

注意：多组数据应该清空数组啊！（（我被坑了     

### Solution:   

```cpp
#include<bits/stdc++.h>

using namespace std;

int n,m;

const int N=1e6+50;

struct edge{
	int to,next;
}e[N<<1];
int head[N<<1],cnt,col[N<<1];
void add_edge(int u,int v){
	++cnt;
	e[cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}


void work()
{
	memset(col,0,sizeof(col));
	memset(head,0,sizeof(head));
	cnt=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	bool flag=0;
	queue<int>q;
	int ans=0;
	for(int i=1;i<=n&&!flag;++i){
		if(col[i]) continue;
		q.push(i);
		col[i]=1;
		while(!q.empty()){
			int x=q.front();
			q.pop();
			for(int j=head[x];j;j=e[j].next){
				int y=e[j].to;
				if(col[y]){
					if(col[y]==col[x]){
						flag=1;
						break;
					}
				}else{
					col[y]=3-col[x];
					q.push(y);
				}
			}
		}
	}
	if(flag){
		printf("Suspicious bugs found!\n");
	}else{
		printf("No suspicious bugs found!\n");
	}
}

int main()
{
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;++i){
		printf("Scenario #%d:\n",i);
		work();
	}
	return 0;
}
```

---

## 作者：COUPDETAT (赞：0)

# 种类并查集
用异或和来确定两个虫子是否为一个集合

同一个集合记为0 不是一个集合记为1

比较两个数的异或和

#### 异或例子

0 0 →0

1 0 →1

1 1 → 0

下面是老师的代码

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int n,m,fa[100100],dis[100100];

int find(int x)
{
	if (fa[x] == x)     return x;
	find(fa[x]);
	dis[x] = dis[x] ^ dis[fa[x]];//统计异或和
   	fa[x] = fa[fa[x]];  
	return fa[x];
}

int main()
{
	int T = 0;
	cin >> T;
	for (int t = 1;t <= T;t++)
		{
			printf("Scenario #%d:\n",t);
			cin >> n >> m;
			for (int i = 1;i <= n;i++)     fa[i] = i,dis[i] = 0;
			int x,y;   bool yes = 0;
			for (int i = 1;i <= m;i++)
				{
					scanf("%d %d",&x,&y);
					int r1 = find(x),r2 = find(y);
					int v = dis[x] ^ dis[y];
					if (r1 == r2  && v == 0 && yes == 0)    {printf("Suspicious bugs found!\n");yes = 1;}
					if (r1 != r2)   {
						fa[r1] = r2;     dis[r1] = dis[x] ^ dis[y] ^ 1;
					}
				}
			if (yes == 0)    printf("No suspicious bugs found!\n");
			printf("\n");
		}
}
```



---

