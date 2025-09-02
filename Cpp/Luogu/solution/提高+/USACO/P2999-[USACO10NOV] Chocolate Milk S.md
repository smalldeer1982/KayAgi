# [USACO10NOV] Chocolate Milk S

## 题目描述

农民约翰的牛奶生产和运输是一个复杂的过程，他用挤奶器给他的那么多头奶牛挤奶，然后流入管道。

每一个管道把一台挤奶器和一个可能连有一台或多台挤奶器的接口连接起来（这样几个管道里的牛奶就汇合了）。然后牛奶流入附加管道（连在各个接口之间的管道）直到流到中央管道，通向储存室。 然后这些牛奶又经历一个逆向的过程通过管道分流到各个牛奶桶，最后被运至市场。

约翰发现对于牛奶来说，最多只有一种方式从一个接口流到另一个接口。并且由于约翰是一个高效率的人，他需要确保每一个管道都有牛奶经过，也就是说，没有多余的管道。

如果我们把每个挤奶机、接口和奶罐都看成一个节点，就共有 $N$ 个节点，输入有序的节点对 $A_{i}$ 和 $B_{i}$ ，代表牛奶从 $A_{i}$ 节点流到 $B_{i}$ 节点，如果没有相对应的父节点，那就说明这是一个挤奶器，同样的如果没有对应的尾节点，则这是一个奶罐。

这几个月巧克力牛奶的需求量激增，所以约翰想要在某一个接口处安装一个巧克力混合器以得到巧克力牛奶，为了节约，约翰只买了一个巧克力混合器。所以他想把这个东西放到一个所有牛奶都能经过的接口，事实上，有这种接口存在。

帮助约翰找到这样的节点（注意：不能把巧克力混合器放在挤奶机里）。
```

           1 ----+
                 |
                 v
           2 --> 4 --> 6 ------------------> 7 --> 8
                       ^                     |
                       |                     |
           3 --> 5 ----+                     + --> 9

```
所有的牛奶都会流经6号或7号节点，所以巧克力混合器可以放在这两个节点上。

## 样例 #1

### 输入

```
9 
1 4 
3 5 
2 4 
5 6 
6 7 
7 8 
4 6 
7 9 
```

### 输出

```
6 
7 
```

# 题解

## 作者：lolte (赞：15)

### 蒟蒻$lolte$的题解

这题不难想到要用到拓扑排序，但我不像其他两位题解一样需要平均分配。

我用拓扑关系来递推每个点到牛奶流量。挤奶机为1，其余为 $from$ 的流量之和。

特别的，当一个点的出度大于1时，这个点后面的点绝不是混合器，即非答案。

当一个点的流量为牛奶总流量时，这个点是答案。

### 代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch<='9'&&ch>='0') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
const int maxn=100010;
int n,id[maxn],od[maxn],to[maxn],q[maxn],liu[maxn],l=1,r=0,tot=0;
bool ji[maxn];
int main(){
	memset(id,0,sizeof(id));
	memset(od,0,sizeof(od));
	n=read();
	for (int i=1;i<n;++i) {
		int a,b;
		a=read();
		b=read();
		to[a]=b;
		++od[a];//出度+1 
		++id[b];//入度+1 
	}
	for (int i=1;i<=n;++i) {
		if (!id[i]) {
			q[++r]=i;//加入队列 
			liu[i]=1;//挤奶器流量为1 
			++tot;//统计牛奶总流量 
			ji[i]=1;//标记为挤奶器 
		}
	}
	while (l<=r) {
		//拓扑流程 
		int u=q[l];
		if (od[u]>1) {
			//入度>1，后面直接不管 
			liu[to[u]]=0;
			++l;
			continue;
		}
		liu[to[u]]+=liu[u];//累加流量 
		--id[to[u]];
		if (!id[to[u]]) {//加点 
			q[++r]=to[u];
		}
		++l;
	}
	r=0;
	for (int i=1;i<=n;++i) {
		if (ji[i]) continue;//挤奶器不管 
		if (liu[i]==tot) q[++r]=i;//统计答案 
	}
	for (int i=1;i<=r;++i) printf("%d\n",q[i]);
}
```

_ (:з」∠) ---

---

## 作者：我和鱼过不去 (赞：10)

这题应该使用拓扑排序。

### 思路
给定每个挤奶器牛奶流量 $1$， 并用数组 $milk $ 记录每个节点可以流经来自多少个不同挤奶器的牛奶，子接口可以流经来自父接口的所有牛奶。  
进行拓扑排序，若某节点的流量为挤奶器的数量，则该节点可以放置巧克力混合器。  

>对于牛奶来说，最多只有一种方式从一个接口流到另一个接口。  

因此**不会有牛奶分流后再重新聚集到一点**，即除了入度为 $0$ 的节点外，一个出度大于 $1$ 的节点的子节点都不能放置巧克力混合器。  
其余的细节参考代码及注释。

------------
 
```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=100005;
vector<int>G[N];
queue<int>q;
int ind[N],f[N],milk[N];
bool ism[N];
int n,m,sum;
void topo()
{
    for(int i=1;i<=n;i++)
    {
        if(!ind[i])
        {
            q.push(i);
            ism[i] = true;   //标记挤奶器 
            milk[i] = 1;     //记录每个接口可以流经来自多少个挤奶器的牛奶
            sum++;           //一共有多少个挤奶器
        }
    }
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        if(G[u].size()>1)    //牛奶不会在分流后聚集到一点 
        {
            continue;
        }
        for(int i=0;i<G[u].size();i++)
        {
            int v = G[u][i];
            ind[v]--;
            milk[v]+=milk[u];   //上一个接口的牛奶可以流向该接口 
            if(!ind[v]) q.push(v);
        }
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)  //一共有n-1条管道
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        ind[v]++;    //记录出度 
    }
    topo();
    for(int i=1;i<=n;i++)
    {
        if(!ism[i]&&milk[i]==sum)   //如果不是挤奶器，并且来自所有挤奶器的牛奶都可以流经该接口 
        {
            printf("%d\n",i);
        }
    }
    return 0;
}
```


---

## 作者：小手冰凉 (赞：6)

把一份牛奶平均分到所有的挤奶机中，每次运输都平均分成连出去的边数份到接下来的管道中


维护一下每个点能有多少牛奶流入


以拓扑序遍历，时间复杂度O（n）


最后节点中牛奶量为1（QAQ  注意挤奶机不能取，贡献1WA  QAQ)（QAQ   注意精度误差，再贡献1WA   QAQ）的就能取



```cpp
#include<bits/stdc++.h>
using namespace std;
const double eps=1e-9;
const int N=100005;
int in[N],out[N];
int head[N],nxt[N],tail[N];
double x[N];
bool b[N];
int q[N],t,n;
void addto(int x,int y)
{
    t++;
    in[y]++;
    out[x]++;
    nxt[t]=head[x];
    head[x]=t;
    tail[t]=y;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        addto(x,y);
    }
    int l=1;
    int r=0;
    for(int i=1;i<=n;i++){
        if(in[i]==0)r++,q[r]=i,b[i]=true;
    }
    for(int i=1;i<=r;i++)
        x[q[i]]=1.0/r;//平均分配
    while(l<=r){
        int xx=q[l];
        for(int k=head[xx];k;k=nxt[k]){
            x[tail[k]]+=x[xx]/out[xx];//平均分配
            in[tail[k]]--;
            if(in[tail[k]]==0)q[++r]=tail[k];
        }
        l++;
    }
    for(int i=1;i<=n;i++)
        if(!b[i]&&fabs(1-x[i])<=eps)printf("%d\n",i);
    return 0;
}
```

---

## 作者：Lyz09 (赞：3)

# 思路

这道题的方法题目已经很明显了：**拓扑排序** 。

由题意可得知水管只会从一边流向另一边（单向），因此可以判断每个挤奶器能流到哪些点，只要一个点所有挤奶器都能流过，就可以输出，但是题目说混合机不能放在挤奶器的位置（入度为 $0$ 的节点），所以需要用数组记录特判。

>对于牛奶来说，最多只有一种方式从一个接口流到另一个接口。

**所以分叉后的节点（出度大于 $1$ 的子节点）只装一个混合机是无法将所有的牛奶混合的，只能装在分叉之前。**

------------

我知道有些人就是来看这个的，你们喜欢的来了。

# 代码

```cpp
#include<iostream>
#include<vector>
#include<cstdio>
#include<queue>
using namespace std;
vector<int> v[100001];
queue<int> q;
int n,m,u,vl,l,a[100001],b[100001],c[100001];
void topo() //拓扑排序。
{
	for(int i=1;i<=n;i++)
	if(!a[i]) //判断挤奶器。
	{
		b[i]=c[i]=1;
		q.push(i);
		l++;
	}
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		if(v[u].size()==1) //出度为零是储存室，出度大于一即为分叉，只有1出度才能继续往下搜（可以用另一种写法：continue）。
		{
			int vl=v[u][0];
			b[vl]+=b[u];
			a[vl]--;
			if(!a[vl])
			 q.push(vl);
		}
	}
}
int main()
{
	cin>>n;
	m=n-1;
	for(int i=1;i<=m;i++) //建边。
	{
		scanf("%d%d",&u,&vl);
		v[u].push_back(vl);
		a[vl]++;
	}
	topo();
	for(int i=1;i<=n;i++)
	if(!c[i]&&b[i]==l) //判断输出，c数组判断是否是挤奶器，b数组判断有几个挤奶器的奶能经过这个点。
	 printf("%d\n",i);
}
```

题解求管理大大通过。

---

## 作者：lichenghan (赞：3)

# P2999 题解

**[传送门](https://www.luogu.com.cn/problem/P2999)**

~~考场上莫名其妙的想到的一个奇葩做法~~

首先，建一个**反图**（若原图中有一条 $u$ 到 $v$ 的边,则在此图中有 $v$ 到 $u$ 的边）。

然后，**dfs** 求出对于每个点，原图中能到达此点的挤奶器的数量（也就是反图中能到达的挤奶器的数量），**需要记忆化保证$O(n)$时间复杂度**

最后，统计能到达的挤奶器的数量等于挤奶器总数的点，输出结果。

**小细节：**

1. 挤奶器不能装混合器！
2. 牛奶分流后不会再聚合，dfs 时要注意！

### Code
```cpp
#include <iostream>
#include <cstdio>
#include<vector>
using namespace std;
int n;
vector<int> g[100001];
int in[100001];
int out[100001];
int s;
int mem[100001];
int dfs(int x){ //记搜
    if(mem[x]){
        if(in[x]<=1) return mem[x];
        else return -1; //排除分流
    }
    for(int i=0;i<g[x].size();i++){
        mem[x]+=dfs(g[x][i]);
    }
    if(in[x]>1) return -1; //排除分流
    return mem[x];
}
int main(){
    scanf("%d",&n);
    int u,v;
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        g[v].push_back(u);//反图
        out[v]++;
        in[u]++;
    }
    for(int i=1;i<=n;i++){
        if(out[i]==0) s++,mem[i]=1;
    }
    for(int i=1;i<=n;i++){
        if(!mem[i]) dfs(i);
    }
    for(int i=1;i<=n;i++){
        if(out[i]/*挤奶器不算*/&&mem[i]==s){
            printf("%d\n",i);
        }
    }
}
```

---

## 作者：依依 (赞：2)

我的错误做法，网络流建边，然后看哪一条边的流是满流。WA 9 RE 1

这样做的问题是流量设定没有限制，所以不可行



正解：把一份牛奶平均分到所有挤奶机中，

然后拓扑排序遍历整张图，每次 经过边u->v  

v从u得到的牛奶量为 (u的牛奶量/u的出度)

对于一个点，如果最终他的牛奶量+eps>=1(会有精度误差)

那么就可以在那里放置机器

--注意挤奶机处不可以放置机器  
[这个世界由你决定](http://www.cnblogs.com/adelalove/p/8666016.html)

---

## 作者：mango09 (赞：1)

[题目链接](https://www.luogu.com.cn/problem/P2999)

[博客链接](https://www.luogu.com.cn/blog/305532/post-ti-xie-p2999-post)

**思路：拓扑排序**

> 对于牛奶来说，最多只有一种方式从一个接口流到另一个接口。

则不会有牛奶分开又聚到一起，故有一个性质：除非节点的入度 $=0$，否则任何出度 $>1$ 的节点的子节点都不能放置混合器。

然后跑拓扑排序即可。

**代码**

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#define int long long
using namespace std;

const int MAXN = 1e5 + 5;

int n, cnt;
int head[MAXN], in[MAXN], out[MAXN], milk[MAXN];
bool ismilk[MAXN];
queue<int> q;

struct edge
{
	int to, nxt;
}e[MAXN];

inline void add(int u, int v)
{
	e[++cnt] = edge{v, head[u]};
	head[u] = cnt;
}

inline void topo()
{
	cnt = 0; 
	for (int i = 1; i <= n; i++)
	{
		if (!in[i])
		{
			q.push(i);
			ismilk[i] = true; //挤奶器
			milk[i] = 1; //有多少个挤奶器的牛奶流过这里
			cnt++; //统计挤奶器的数量
		}
	}
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		if (out[u] > 1) //出度>1不用管
		{
			continue;
		}
		for (int i = head[u]; i; i = e[i].nxt)
		{
			int v = e[i].to;
			in[v]--;
			milk[v] += milk[u]; //加上父节点的值
			if (!in[v]) //父节点全部处理完
			{
				q.push(v);
			}
		}
	}
}

signed main()
{
	scanf("%lld", &n);
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%lld%lld", &u, &v);
		add(u, v);
		out[u]++;
		in[v]++;
	}
	topo();
	for (int i = 1; i <= n; i++)
	{
		if (!ismilk[i] && milk[i] == cnt) //不是挤奶器并且所有挤奶器的牛奶流过这里
		{
			printf("%lld\n", i);
		}
	}
	return 0;
}
```


---

## 作者：xfrvq (赞：1)

[原题链接](https://www.luogu.com.cn/problem/P2999)

[博客使用](https://www.luogu.com.cn/blog/368107/solution-p2999)

---

思路：**拓扑排序**

---

$ind$ 数组表示到达节点 $i$ 的边共有几条，在做拓扑排序的时候去减去。

$milk$ 数组表示节点 $i$ 所可能来自多少个挤奶器。

$ismilk$ 表示这个节点是不是一个奶罐（其实就是判断 $ind$ 是不是 $0$ ，但 $ind$ 会在拓扑排序过程中改变）。

main 函数中在跑完一遍拓扑排序，就遍历 $1 \to n$ 如果 $ismilk_i$ 并且 由这个点可以到达任意一个挤奶器，也就是 $milk_i = $ 挤奶器总数，这个点就是一个可行的接口。

---

代码：

```cpp
#include<stdio.h>
#include<queue>
std::vector<int> G[100005];
int ind[100005],n,cnt = 0;
bool ismilk[100005];
int milk[100005];
void topo(){
	std::queue<int> q;
	for(int i = 1;i <= n;++i){
		if(ind[i] == 0){
			q.push(i);
			ismilk[i] = true;
			milk[i] = 1;
			++cnt;
		}
	}
	while(!q.empty()){
		int u = q.front();
		q.pop();
		if(G[u].size() <= 1){
			for(int i = 0;i < G[u].size();++i){
				int v = G[u][i];
				milk[v] += milk[u];
				--ind[v];
				if(ind[v] == 0) q.push(v);
			}
		} 
	}
} 
int main(){
	scanf("%d",&n);
	for(int i = 1;i < n;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		++ind[v];
	}
	topo();
	for(int i = 1;i <= n;++i) if(ismilk[i] == false && milk[i] == cnt) printf("%d\n",i);
	return 0;
}
```

---

~~你以为题解到此就结束了吗？？哦NONONO~~

接下来是 dfs 题解。

此思路 by [lichenghan](https://www.luogu.com.cn/user/238300)

首先考虑暴力。

对于每一个节点，dfs 两遍，先 dfs 儿子，判断是否由它可以到达每一个奶罐。再 dfs 父亲，判断是否可以由它到达每一个挤奶器。

代码：

```cpp
#include<stdio.h>
#include<vector>
std::vector<int> son[100001];
std::vector<int> fa[100001];
int n,ans,ans2;
void dfs(int u){
	if(son[u].size() == 0){
		++ans;
		return;
	}
	for(int i = 0;i < son[u].size();++i) dfs(son[u][i]);
}
void dfs2(int u){
	if(fa[u].size() == 0){
		++ans2;
		return;
	}
	for(int i = 0;i < fa[u].size();++i) dfs2(fa[u][i]);
}
int main(){
	scanf("%d",&n);
	for(int i = 1;i < n;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		son[u].push_back(v);
		fa[v].push_back(u);
	}
	int ss = 0,sf = 0;
	for(int i = 1;i <= n;++i) 
		if(son[i].size() == 0) ++ss;
		else if(fa[i].size() == 0) ++sf;
	for(int i = 1;i <= n;++i) if(fa[i].size()){
		ans = 0;
		dfs(i);
		if(ans == ss){
			ans2 = 0;
			dfs2(i);
			if(ans2 == sf) printf("%d\n",i);
		}
	}
	printf("\n");
	return 0;
}
```

TLE 快乐！

既然 DFS 会 TLE，那么我们就用记忆化搜索！！

代码：

```cpp
#include<stdio.h>
#include<vector>
std::vector<int> son[100001];
std::vector<int> fa[100001];
int n;
int dp1[100001],dp2[100001]; // dp数组以记忆化
int dfs1(int u){
	if(dp1[u]) return dp1[u]; // 如果曾经算过就不用再算了
	if(son[u].size() == 0) return 1;
	int ret = 0;
	for(int i = 0;i < son[u].size();++i) ret += dfs1(son[u][i]);
	return dp1[u] = ret; // 更新
}
int dfs2(int u){
	if(dp2[u]) return dp2[u]; // 如果曾经算过就不用再算了
	if(fa[u].size() == 0) return 1;
	int ret = 0;
	for(int i = 0;i < fa[u].size();++i) ret += dfs2(fa[u][i]);
	return dp2[u] = ret; // 更新
}
int main(){
	scanf("%d",&n);
	for(int i = 1;i < n;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		son[u].push_back(v);
		fa[v].push_back(u);
	}
	int ss = 0,sf = 0;
	for(int i = 1;i <= n;++i) 
		if(son[i].size() == 0) ++ss;
		else if(fa[i].size() == 0) ++sf;
	for(int i = 1;i <= n;++i) if(fa[i].size())
		if(dfs1(i) == ss)
			if(dfs2(i) == sf) printf("%d\n",i);
	return 0;
}
```

---

## 作者：pldzy (赞：1)


## **前置知识 --> 拓扑排序**

 这道题为什么要用拓扑排序呢？因据题意，每一个点奶的流量都有先后顺序，且顺序不得改动。
 
 重点在于本题入度，出度，队列等的运用。
 

**思路**
------------
挤奶器：入度为 0，且可以最早入队列（因为它不受先后顺序的限制）；

混合器：混合器要放在每一个奶流都会经过的点，则该点的奶流量 = 总奶流量；

 while 入队出队操作：当队头的出度为 1 时，可以将之前记录下来的他的“子节点”操作之后，入队；

答案统计：在将挤奶器入队时，统计总奶量，每一个挤奶器的奶量为 1， 并用 tot 统计，最后比较该点的奶流量是否与总奶量相等，若相等，则记录。


------------
##  _**Code**_ 
```cpp
#include<bits/stdc++.h>
using namespace std; 

const int maxn = 100010;
int n;
int to[maxn], ans[maxn];
int rd[maxn], cd[maxn];
int liu[maxn], ji[maxn];//挤奶器 
int tot;

queue <int> q;

int main()
{
	scanf ("%d", &n);
	for (int i = 1; i < n; i++)
	{
		int a, b;
		scanf ("%d %d", &a, &b);
		to[a] = b;
		cd[a]++;
		rd[b]++;
	}
	
	for (int i = 1; i <= n; i++)//寻找挤奶器 
	{
		if (!rd[i])
		{
			liu[i] = 1;
			tot += 1;
			q.push (i);
			ji[i] = 1;
		}
	}
	
	while (!q.empty())
	{
		int x = q.front ();
		q.pop ();
		if (cd[x] > 1) continue;
		//拓扑
		liu[to[x]] += liu[x];
		rd[to[x]] --;
		if (!rd[to[x]]) q.push (to[x]); 
	}
	
	int tmp = 1;
	for (int i = 1; i <= n; i++)
	{
		if (ji[i]) continue;//挤奶器
		if (tot == liu[i]) 
		{
			ans[tmp] = i;
			tmp ++;
		}
	}
	for (int i = 1; i < tmp; i++) printf ("%d\n", ans[i]);
	return 0;
}
```


---

## 作者：⊱⋛赫宇⋚⊰ (赞：1)

## 题目大意

让我们求一个所有入度为0的点都等达到的点

---------

## 对于50%的数据
我们可以想到O(n*n)的解决思路。

在输入的时候，先预处理出每个点的入度和出度，再一重判断枚举每个点,如果是挤奶器，那么就遍历这个点，再是一重循环枚举管道和奶罐，如果这个点可以被所有的挤奶器流到，那么继续遍历这个点，看看这个点能不能到达所有的奶罐如果可以那么就可以在这个地方设立巧克力混合器，注意也可以在奶罐处设立巧克力混合器

```cpp
#include<bits/stdc++.h>
#define maxn 100100
using namespace std;
inline int read()
{
	int res=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch)){res=(res<<1)+(res<<3)+(ch&15);ch=getchar();}
	return res*f;
}
int n,head[maxn],tot;
struct ad{
	int ne;
	int to;
}edge[maxn];
inline void add(int x,int y)
{
	edge[++tot].to=y;
	edge[tot].ne=head[x];
	head[x]=tot;
}
int rdu[maxn],cdu[maxn],li[maxn],ans[maxn],num;
int vis[maxn],p[maxn],q[maxn];
inline void dfs(int x)//找挤奶器可以通向的地方
{
	vis[x]=1;
	for(int i=head[x];i;i=edge[i].ne)
	if(!vis[edge[i].to])q[edge[i].to]++,dfs(edge[i].to);
}
int sum;
inline void dfs2(int x)//遍历是不是可以流到奶罐
{

	vis[x]=1;if(p[x]==2)sum++;
	for(int i=head[x];i;i=edge[i].ne)
	if(!vis[edge[i].to])dfs2(edge[i].to);	
	
} 
int ni,g;
int main()
{
	n=read();
	for(int i=1;i<n;i++)
	{
		int x,y;x=read();y=read();
        cdu[x]++;rdu[y]++;
        add(x,y);
	}
	for(int i=1;i<=n;i++)
	if(rdu[i]==0)p[i]=1,ni++;
	else if(cdu[i]==0)p[i]=2,g++;
	else p[i]=3;
	for(int i=1;i<=n;i++){if(p[i]==1){memset(vis,0,sizeof(vis));dfs(i);}}
    for(int i=1;i<=n;i++)
	{
    	if(p[i]!=1&&q[i]==ni)
    	{
    		sum=0;
    		memset(vis,0,sizeof(vis));
    		
			dfs2(i);
    		
    		if(sum==g)printf("%d\n",i);
			
		}
	}
	return 0;
}

```
## 对于100%的数据

我们O(n)解决（拓扑排序）
在输入的时候，预处理出每个点的出度和入度，然后一重循环枚举出挤奶处，把他压入队列,对于每个点如果它的出度>1，那么他所连的边就不可能成为巧克力混合器，因为这是一棵树。如果就只有一的出度，那么所指向的点加上这个点的奶流量，将那个点的入度–，如果入度等于0了，那么就可以入队了，最后只需要判断一下能不能流满就好

```cpp
#include<bits/stdc++.h>
#define maxn 1000100
using namespace std;
inline int read()
{
	int res=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch)){res=(res<<1)+(res<<3)+(ch&15);ch=getchar();}
	return res*f;
}
int rdu[maxn],cdu[maxn],n;
int to[maxn],milk[maxn];
int vis[maxn];
int q[maxn];
int l=1,r;
int milkn;
int main()
{
	n=read();
	for(int i=1;i<n;i++)
	{
		int x,y;x=read();y=read();
		cdu[x]++;
		rdu[y]++;
		to[x]=y;
	}
	for(int i=1;i<=n;i++)
	if(!rdu[i]){vis[i]=1;q[++r]=i;milk[i]=1;milkn++;}//把初始的挤奶点入队
	
	while(l<=r)
	{
		int u=q[l];
	    if(cdu[u]>1)
	    {
	    	milk[to[u]]=0;l++;
	    	continue;
		}
	    milk[to[u]]+=milk[u];//可以流到
	    l++;
	    rdu[to[u]]--;
	    if(!rdu[to[u]])q[++r]=to[u];//入队
	}
	for(int i=1;i<=n;i++)
	if(!vis[i]&&milk[i]==milkn)printf("%d\n",i);
	return 0;
}

```


---

## 作者：JoaoFelix (赞：1)

一道妙题，首先我们会发现这是一棵树，然后我们发现树的性质或许不是特别有提示性。

而且我们发现涉及到有关于出度入度的大部分都和DAG相关，但是其实树就是一个DAG。

我们把这题转化成DAG理解可能更好，最好地处理DAG的办法就是拓扑排序。

我们看这道题怎么拓扑排序，我们发现拓扑排序的结果是可并的，但是也是会有重复的，因此我们这题考虑用什么办法去重。

如果是类似于bitset的这样的可以做一下，但是复杂度不能接受。

我们发现如果我们把它看成类似于网络流的模型，定义一个流量，然后让它平均分配，在里面流，容易发现，如果一个点所有的都从这里流，那么就是满足条件的，因此我们拓扑排序模拟这个流的过程就好了。

这道题的启示是，这题感觉挺奇特的，看上去这个平均分配和这个题目没有一点关系，但是我们往往也能这么做，一种类似于求所有的是否经过，或者判断是否关键点的我们都可以利用平均分配解决。

代码：
```cpp
#include<bits/stdc++.h>
#define LL long long
#define db double
using namespace std;
const int N=1e5+5;
struct Edge{int to,nxt;}e[N];
int n,fst[N],tote,in[N],out[N],tot,ans;db vl[N];bool fl[N];
void adde(int u,int v){e[++tote]=(Edge){v,fst[u]};fst[u]=tote;}
queue<int>q;
int main(){
	scanf("%d",&n);
	for(int i=1,u,v;i<n;i++)scanf("%d%d",&u,&v),adde(u,v),in[v]++,out[u]++;
	for(int i=1;i<=n;i++)if(!in[i])tot++,fl[i]=true;
	for(int i=1;i<=n;i++)if(!in[i])q.push(i),vl[i]=1.0/(db)tot;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=fst[u],v;i;i=e[i].nxt){
			in[v=e[i].to]--;vl[v]+=vl[u]/(db)out[u];
			if(!in[v])q.push(v);
		}
	}
	for(int i=1;i<=n;i++)if(!fl[i]&&fabs(vl[i]-1)<1e-8)printf("%d\n",i);
	return 0;
}

```


---

## 作者：920106970144yxz (赞：1)

~~看到楼下的大佬们都在用拓扑和网络流算每个节点的流量，本蒟蒻表示并看不懂。~~

呃，言归正传。

本题乍一看要算每个节点的流量，但如果暴力算，时间是O(n²)，直接TLE。

这时我们注意到这张图只有n-1条边，说明这是一棵“树”。

你可能会说：
## 这咋会是树呢，一个节点能有好几个父亲啊。

我们来看张示意图~~（灵魂画风警告）~~
![样例](https://s2.ax1x.com/2019/02/05/kYKy1x.png)

由于FJ保证一定有解，所以一定存在一个点，是所有挤奶机都能通往的（本图中为⑥），也一定存在一个点，是通往所有罐头的（本图中为⑦）。

这两个节点分别是两棵树的根，答案就是这两个节点之间的所有点（包括端点）。

另外，因为没有环所以哪些点必然是一条链。

所以我们从任意一个
挤奶机开始，找到一个出度不为1（决不能是≤1，会死循环）的点,再立刻反向搜，找到一个入度大于1（决不能是不为1，会把挤奶机误判）的点，记录下中途出现的点，排序后输出，时间是O(n)。

上代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int const maxn=1000000+10;
int H[maxn],N[maxn],V[maxn],tot=0,deg[maxn],out[maxn],beg;
int aH[maxn],aN[maxn],aV[maxn],atot=0,cnt=0,col[maxn];
void add(int u,int v){
	V[++tot]=v;N[tot]=H[u];H[u]=tot;
}
/*
 *建图
 */ 
void antiadd(int u,int v){
	aV[++atot]=v;aN[atot]=aH[u];aH[u]=atot;
}
/*
 *建反图
 */ 
void bfs1(int u){
	while(out[u]==1){
		u=V[H[u]];
	}
	beg=u;
	return;
}
/*
 *寻找通往所有罐头的点 
 */ 
void bfs2(int u){
	while(deg[u]==1){
		col[++cnt]=u;
		u=aV[aH[u]];
	}
	if(deg[u]!=0)
	col[++cnt]=u;
	return;
}
/*
 *寻找通往所有挤奶机的点 
 */ 
int main(){
	int i,u,v,cow,n;
	scanf("%d",&n);
	for(i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		add(u,v);
		antiadd(v,u);
		deg[v]++;
		out[u]++;
	}
	for(i=1;i<=n;i++){
		if(deg[i]==0){
			cow=i;break;
		}
	}
	bfs1(cow);
	bfs2(beg);
	sort(col+1,col+1+cnt);
	/*
	 *排序
	 */ 
	for(i=1;i<=cnt;i++){
		printf("%d\n",col[i]);
	}
	return 0;
}
//这是我从FTB上学来的注释风格（大雾 
```

---

## 作者：Flandre_495 (赞：1)

### 我来发一篇最简单的题解。 



#### 由题目得这是一棵树；

#### 你只需要知道点的入度与出度，用to数组指向下一个点；

#### 对于指向多个点的点，它的to可以随意更新（因为根本用不到，下面会提到）；

#### 你要找所有奶都经过的点；

#### 设每个挤奶机贡献一份奶流量，奶流量最大的点就是所有奶经过的点；

#### 用most更新最大流量；

#### 来一遍拓扑，每一个点的流量是指向它的点流量的总和，用每个点更新它指向点的流量；

#### 当一个点出度大于一时，它指向的点中不可能再有所有奶经过的点；

此时拓扑结束；

#### 最后就从小到大枚举点，哪个点流量为most（且不为挤奶机）就可以安装插件；

还是看代码吧；


```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
const int qwq=501010;
int n;
int x,y;
int most;     //最大奶流量； 
int ru[qwq],chu[qwq];//入度与出度； 
int l[qwq];   //此点奶流量； 
int to[qwq];  //下一个点； 
bool vis[qwq]; 
bool kou[qwq];//是否为挤奶机； 
void DFS(int u)
{
	most=max(most,l[u]);//此点奶流量已被上一点更新； 
	if(chu[u]>1)return ;//若在此分流，则不可能再有点为插件； 
	vis[u]=1;
	ru[ to[u] ]--;       
	l [ to[u] ]+=l[u];  //更新下一点入度与流量； 
	if(ru[ to[u] ]==0)  //继续遍历； 
	DFS(to[u]);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)//树n-1条边；
	{
		scanf("%d%d",&x,&y);
		ru[y]++;
		chu[x]++;
		to[x]=y;
		//若x下一个点不止一个，那么就不用再遍历下面的点；
		//这个点下一个点没有意义；
   		//to数组只对出度为一的点有用； 
	}
	for(int i=1;i<=n;i++)
	{
		if(ru[i]==0)
		{
			l[i]=1;  //奶流量源； 
			kou[i]=1;//入度为一的点为挤奶机； 
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(!vis[i]&&ru[i]==0)
		DFS(i);  //拓扑（从挤奶机开始）；
	}
	for(int i=1;i<=n;i++)
	{
		if(l[i]==most&&!kou[i])//如果此点奶流量最大且不为挤奶机； 
		cout<<i<<endl;         //安装插件； 
	}
	return 0;
}
```


---

## 作者：orz_z (赞：0)

[传送门](https://www.luogu.com.cn/problem/P2999)

# 拓扑排序

关于拓扑排序，这里不叙述太多，可参考本人[CSDN](https://blog.csdn.net/qq_46258139/article/details/113623693)。

值得注意的是，这不是一棵树吗？

> FJ 发现对于牛奶来说有一种最多的方式从一个接口流到另一个接口。并且由于 FJ 是一个高效率的人，他需要确保每一个管道都有牛奶经过，也就是说，没有多余的管道。

所以，对于牛奶来说，最多只有一种方式从一个接口流到另一个接口。则不会有牛奶分开又聚到一起。

故有一个性质：除非节点的入度等于 $0$，否则任何出度大于 $1$ 的节点的子节点都不能放置混合器。

$ans_i$ 表示如果在 $i$ 结点造一个巧克力混合器，最多能经过的牛奶数（每个点初始为 $1$）。

用拓扑排序遍历整棵树，顺便计算 $ans$。

 1. 只需要找到入度为 $0$ 的结点，标记并放入队列。
 

```cpp
for (int i = 1; i <= n; i++)
		if (!ind[i]) q.push(i), ans[i] = check[i] = 1, cnt++;
```

 2. 每次找孩子只需要找出度为 $1$ 的结点。
 


> 对于每个点如果它的出度大于 $1$，那么他所连的边就不可能成为巧克力混合器。


 3. 对于每个结点 $x$ ，若 $ans_x$ 值等于总边数，且入度不为 $0$，就输出。

# AC CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 99;

int n, m, t, tot, cnt;
int head[maxn], out[maxn], ind[maxn];
int ans[maxn];
bool check[maxn];

struct Edge
{
    int to, next;
} e[maxn];

void add(int a, int b)
{
    e[++tot].to = b;
    e[tot].next = head[a];
    head[a] = tot;
}

void topo()
{
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (!ind[i])
            q.push(i), ans[i] = check[i] = 1, cnt++;
    while (!q.empty())
    {
        int tmp = q.front();
        q.pop();
        if (out[tmp] == 1)
        {
            int j = head[tmp];
            ans[e[j].to] += ans[tmp];
            if (--ind[e[j].to] == 0)
                q.push(e[j].to);
        }
    }
}

signed main()
{
    cin >> n;
    for (int i = 1, a, b; i < n; i++)
    {
        cin >> a >> b;
        add(a, b);
        out[a]++;
        ind[b]++;
    }
    topo();
    for (int i = 1; i <= n; i++)
    {
        if (ans[i] == cnt && !check[i])
        {
            cout << i << endl;
        }
    }
}
```

---

## 作者：wtyqwq (赞：0)

- [P2999 Chocolate Milk](https://www.luogu.com.cn/problem/P2999)

- 解题思路：

  - 根据题意，运输系统一定是个有向无环图。

  - 容易发现一个性质：假设有 $k$ 个挤奶机（入度为 $0$ 的点），从每个挤奶机出发遍历这个有向无环图，每个最终成为答案的点必定被访问了 $k$ 次。
  
  - 根据上面的性质，我们就有了一个 $O(n^2)$ 的做法，即从每个挤奶机出发遍历这个有向无环图，统计每个点被访问的次数 $\text{vis}_i$，若 $\text{vis}_i=k$，输出这个点即可。
  
  - 需要注意的是：
  
      - 无需统计挤奶机被遍历的次数，因为题目中说“巧克力插件不能安装在一个挤奶机上”。
    
      - 遍历的过程中，若发现当前点的出度 $>1$ 或当前点的出度 $=0$，则无需继续遍历。
      
  - 这个做法的时间复杂度看上去还是 $O(n^2)$ 的，不知道有没有构造的数据可以卡掉？（评测已经通过）。或者证明是以下代码复杂度低于 $O(n^2)$ 也可以？

- 代码实现：
 
------------
```cpp
#include <stdio.h>
#define N 100005
int head[N], ver[N], nex[N];
int In[N], Out[N], vis[N], x, y, k, n, m, tot;
void Add(int x, int y) {
	ver[++tot] = y;
	nex[tot] = head[x];
	head[x] = tot;
}
void Depth_Search(int x) {
	if (Out[x] == 1) {
		++vis[ver[head[x]]];
		Depth_Search(ver[head[x]]);
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; ++i) {
		scanf("%d %d", &x, &y);
		Add(x, y), ++In[y], ++Out[x];
	}
	for (int i = 1; i <= n; ++i)
		if (In[i] == 0)
			Depth_Search(i), ++k;
	for (int i = 1; i <= n; ++i)
		if (vis[i] == k)
			printf("%d\n", i);
	return 0;
}
```
- 算法标签：深度优先搜索 $\text{DFS}$。[提交记录](https://www.luogu.com.cn/record/39205535)。

---

