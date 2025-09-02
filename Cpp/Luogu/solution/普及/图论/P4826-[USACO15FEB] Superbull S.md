# [USACO15FEB] Superbull S

## 题目描述

Bessie 和她的朋友们正在一年一度的 Superbull 锦标赛中比赛，Farmer John 负责让比赛尽可能精彩。总共有 $N$ $(1 \leq N \leq 2000)$ 支队伍参加 Superbull。每支队伍都被分配了一个唯一的整数队伍 ID，范围在 $1 \ldots 2^{30}-1$ 之间，用于区分不同队伍。Superbull 是淘汰制比赛——每场比赛后，Farmer John 会选择淘汰其中一支队伍，被淘汰的队伍将不再参与后续比赛。当只剩一支队伍时，Superbull 结束。

Farmer John 发现比赛得分有一个特殊性质：任意一场比赛中，两支队伍的得分总和总是等于两队 ID 的按位异或（XOR）。例如，若队伍 12 和 20 比赛，则该场比赛总得分为 $24$，因为 $01100 \oplus 10100 = 11000$（即 $12 \oplus 20 = 24$）。

Farmer John 认为比赛总得分越高越精彩。因此，他希望安排一系列比赛，使得 Superbull 所有比赛的总得分最大化。请帮助他设计比赛方案。

## 说明/提示

**输出样例解释**：  
一种获得 37 分的方案如下：  
1. Farmer John 让队伍 3 和 9 比赛，选择淘汰 9，此时剩余队伍为 6、9、10  
2. 让队伍 6 和 9 比赛，选择淘汰 9，此时剩余队伍为 6 和 10  
3. 最后让队伍 6 和 10 比赛  
总得分为 $(3 \oplus 9) + (6 \oplus 9) + (6 \oplus 10) = 10 + 15 + 12 = 37$。

**关于按位异或**：  
按位异或运算（记作 $\oplus$）对两个二进制数的每一位进行逻辑异或操作。当且仅当某一位上两个数不同时，结果的该位为 1。例如：  
$10100$（十进制 20）$\oplus$ $01100$（十进制 12）$= 11000$（十进制 24）

## 样例 #1

### 输入

```
4
3
6
9
10```

### 输出

```
37```

# 题解

## 作者：Register (赞：12)

### 题意描述
有$n$头牛比赛，每场比赛都选任意两头牛

每场比赛会影响总得分，总得分会加上选手$x$的$id$和选手$y$的$id$按位异或的值

每局比赛你都要钦定一头牛输掉，输掉的牛不能继续比赛


求总得分的最大值
### 解题思路
- 对于每一头牛，除了最后的赢家，有且仅有一个战胜自己的牛

- 对于每一头牛，可能会战胜大于等于$0$，小于$n$头牛

- 对于最后的赢家，没有人会战胜它（这不废话吗

- 共有$n-1$场比赛

> **以上四点，分别与树的父亲结点、儿子结点、根结点、边的数量对应**

我们可以预处理出每两头牛对局的得分，跑一次最大生成树即可
### 注意事项
- 总得分记得开```long long```

- 边的数组容量多卡点

- $C++$中```^```是异或的意思，不是幂运算

### 代码

```cpp
#include <cstdio>
#include <algorithm>
int n,sum,cnt,ans,a[2001],f[2001];
struct edge{
	int u,v,c;
}e[2000000];
int read(){
    char ch=getchar();int res=0,w=1;
    while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {res=res*10+ch-'0';ch=getchar();}
    return res*w;
}
int Find(int x){
	if(f[x]==x) return x;
	return f[x]=Find(f[x]);
}
inline bool comp(const edge&x,const edge&y){
	return x.c>y.c;
}
int main(){
	n=read();
	for(register int i=1;i<=n;i++) {a[i]=read();f[i]=i;}
	for(register int i=1;i<n;i++)
		for(register int j=i+1;j<=n;j++) {e[++sum].u=i;e[sum].v=j;e[sum].c=a[i]^a[j];}
	std::sort(e+1,e+sum+1,comp);
	for(register int i=1,x1,x2;i<=sum;i++)
	{
		x1=Find(e[i].u);x2=Find(e[i].v);
		if(x1==x2) continue;
		ans+=e[i].c;f[x1]=x2;cnt++;
		if(cnt==n-1) break;
	}
	printf("%d\n",ans);
    return 0;
}
```


---

## 作者：zylll (赞：7)

第一次题解qwq

安利一波自己的博客qwq[https://beyondlimits.site/](https://beyondlimits.site/)

看到第一篇题解是关于Kruskal的，我就写个Prim版的吧。

这道题看到以后显然就是最大生成树。

思路就是把每一条边都与其他边连上，建图，故会很稠密，所以显然更适合Prim算法。

代码非常简单，接近于一个模板。
```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;
int n,a[2005],key[2005];
long long ans;bool vis[2005];
void Prim(){
    for(int i=1,x=0;i<=n;i++,x=0){
        for(int j=1;j<=n;j++)if(!vis[j])
            if(key[j]>=key[x])x=j;
        vis[x]=true;
        for(int y=1;y<=n;y++)
            if(!vis[y])key[y]=max(key[y],a[x]^a[y]);
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    Prim();
    for(int i=1;i<=n;i++)ans+=(long long)key[i];
    printf("%lld",ans);
}
```

---

## 作者：Del_Your_Heart (赞：5)

## 题目大意：
### 给你 $n$ 头牛，要求你安排 $n-1$ 场比赛，每次比赛的得分为两头牛的编号的异或和，求出最大的比赛总得分。

------------
## 思路剖析：
（这是我们今天模拟赛的一道题。~~我花20min就切掉了。~~）

最开始看到这题时，我毫无思绪，但当我看到 
>在每场比赛之后，$FJ$选择淘汰其中一支球队，而被淘汰的球队再也无法参加任何比赛了。当只剩下一支球队时，比赛就结束了。

之后，我想：**每次比赛淘汰一头牛，最后只剩下一头牛，那就打了$n-1$场比赛**。而任意两头牛之间都珂以安排比赛，得分为两头牛的编号异或和，这不就是**在一个$n$个顶点的完全图上跑最大生成树**吗?

### 问题到这里就迎刃而解了。

------------

## 具体做法：
#### 在每两头牛之间建一条权值为两头牛编号的异或值的无向边，然后再用$prim$或$kruskal$跑最大生成树即可。
#### 这里推荐用$prim$，因为$prim$时间复杂度为$O(n^2)$，$kruskal$时间复杂度为$O(m\log{m})$，在类似于完全图的这种稠密图当中$prim$会快一点。
#### ~~可我还是用了$kruskal$，只是为了在考场上抢$First$ $Blood$。。。（逃~~


------------

## 代码实现：
```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch)){
		f|=ch=='-';
		ch=getchar();
	}
	while(isdigit(ch)){
		x=x*10+(ch^48);
		ch=getchar();
	}
	return f?-x:x;
}
int n,tot=0,f[2005],a[2005];
struct node{
	int u,v,w;
	bool operator< (const node& a) const{
		return w>a.w;
	}
}e[5000005];
inline void add(int u,int v,int w){
	e[++tot].v=v;
	e[tot].u=u;
	e[tot].w=w;
}
inline int find(int x){
	if(f[x]==x)
		return x;
	else return f[x]=find(f[x]);
}
inline int kruskal(){
	int ans=0,cnt=0;
	for(register int i=1;i<=tot;++i){
		int f1=find(e[i].u),f2=find(e[i].v);
		if(f1!=f2){
			f[f1]=f2;
			ans+=e[i].w;
			if(++cnt==n-1)
				break;
		}
	}
	return ans;
}
signed main(){
	n=read();
	for(register int i=1;i<=n;++i)
		f[i]=i,a[i]=read();
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<=n;++j)
			if(i!=j)
				add(i,j,a[i]^a[j]);
	sort(e+1,e+tot+1);
	cout<<kruskal();
    return 0；
}
```

---

## 作者：andysk (赞：4)

[Link]( https://www.luogu.org/problem/P4826 )

[Blog](https://tony102.xyz/index.php/2019/10/16/luogu4826-usaco15febsuperbull-%e8%b6%85%e7%ba%a7%e7%89%9b/)食用效果明显更佳

### 题意

有 $n$ 头牛, 要求在它们中间安排 $n-1$ 场决斗, 其中每场的收益是这两头牛权值的异或和, 使总的异或和最大



### 题解

这题确实比较简单

首先由题可知, 每头牛之间都可以有决斗,抽象成一张图,这是一张完全图,要求你在这张完全图中选出 $n -1$ 条边, 使得边权总和最大.

很明确就是处理每头牛之间的权值异或和建图跑一个最大生成树.

觉得难度评分明显过高.



### Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int SIZE = 2000 + 5;
const int SIZE_EDGE = 2000 * 2000 + 5;

#define int long long

int n, num;
int id[SIZE], fa[SIZE];

struct node {
    int from, to, v;
} edge[SIZE_EDGE];

inline int read()
{
    char ch = getchar();
    int f = 1, x = 0;
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + ch - '0'; ch = getchar(); }
    return x * f;
}

inline void Addedge(int x, int y, int z)
{
    edge[++num].from = x;
    edge[num].to = y;
    edge[num].v = z;
}

inline int Find(int x) { return fa[x] == x ? x : fa[x] = Find(fa[x]); }

inline void Unite(int x, int y)
{
    int fx = Find(x), fy = Find(y);
    if (fx != fy) fa[fx] = fy;
} 

inline int CMP(node a, node b) { return a.v > b.v; }

inline void Kruskal()
{
    int sum = 0, cnt = 0;
    for (int i = 1; i <= num; i++) {
        int u = edge[i].from, v = edge[i].to;
        if (Find(u) != Find(v)) {
            Unite(u, v);
            sum += edge[i].v, cnt++;
        }
        if (cnt == n - 1) break;
    }
    std::cout << sum;
} 

signed main()
{
    n = read();
    for (int i = 1; i <= n; i++) id[i] = read();
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            // if (i == j) continue;
            Addedge(i, j, id[i] ^ id[j]);
            // printf("%d %d %d\n", i, j, id[i] ^ id[j]);
        }
    }
    std::sort(edge + 1, edge + num + 1, CMP);
    for (int i = 1; i <= n; i++) fa[i] = i;
    Kruskal();
    return 0;
}
```


---

## 作者：installb (赞：3)

题目中说到每打一场比赛淘汰一队 并且最后剩下一队 那么就是一共会有$n-1$场比赛  

我们可以先把它转化成一个完全图 一支球队代表一个点 一场比赛代表一条边(边连接的两个点代表比赛双方) 边权为这场比赛的得分(根据题目定义求得)  
一开始时不知道应该怎么选取比赛 所以先所有边都连上  

$n$个点 $n-1$条边  
结合上面条件和题目条件应该可以看出来是求这张图的**最大生成树** 了  

- 每一队可以击败$0$到$n-1$支球队  
- 除了一支球队以外 每一对都会被一支球队击败  

这些条件对应  

- 树上每一个节点都有$0$到$n-1$个子节点  
- 除了根节点外 每一个点都有且仅有一个父节点  

相当于一个节点会淘汰它所有的儿子节点  

如果出现环就会有问题 并且出现环后为了保证边数图会不连通 然后就不止一个获胜者  

**唯一的可能是一棵树 树的情况下最优解是最大生成树**  

~~此题完结 上代码~~  
写了Prim  

**code:**  
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

LL n;
LL a[2005] = {0};
LL dis[2005] = {0};
LL vis[2005] = {0};
LL sum = 0;

int main(){
	scanf("%lld",&n);
	for(LL i = 1;i <= n;i ++) scanf("%lld",&a[i]);
	dis[1] = 0; vis[1] = 1;
	for(LL i = 1;i <= n;i ++) dis[i] = a[1] ^ a[i];
    // 先把第一个点加进去  
    // 这里直接在跑MST的过程中计算边权而没有预处理
	for(LL i = 1;i <= n;i ++){
		LL mxs = 0,id;
		for(LL j = 1;j <= n;j ++){
			if(vis[j]) continue;
			if(dis[j] > mxs){
				mxs = dis[j];
				id = j;
			}
		}
		sum += mxs; vis[id] = 1; dis[id] = 0;
		for(LL j = 1;j <= n;j ++){
			dis[j] = max(dis[j],a[id] ^ a[j]);
		}
	}
    // 上面是模板
	cout << sum << endl;
	return 0;
}
```

---

## 作者：zhangboju (赞：2)

[传送门：P4826 [USACO15FEB]Superbull 超级牛。](https://www.luogu.com.cn/problem/P4826)

[blog效果更佳.](https://www.luogu.com.cn/blog/zhangboju/solution-p4826)

让我们 ~~无耻地~~ 打开题目算法标签：

【图的建立，建图】【生成树】。

首先，是【图的建立，建图】。

这么多牛，两两对决，那么我们直接两两建边，组成一个完全图，不就完事了吗？

那么，节点就是牛，边权就是两头牛两两对战的值（即团队 ID 的异或值）。

然后，将样例带进来，结合样例说明，我们选择了其中的牛，即选中了边（为绿色）：


![](https://cdn.luogu.com.cn/upload/image_hosting/9jjqhjpx.png)

好的，我们已经用掉一个信息了，那还剩下：【生成树】。

教练说过：

>一个 $n$ 个点的树有 $n-1$ 条边。

我们再审一遍题，发现这些牛刚好决斗 $n-1$ 次！！！

再将样例说明那张图旋转，简化：

![](https://cdn.luogu.com.cn/upload/image_hosting/fbnsfg5n.png)

这不就是一棵树吗？

所以，这是要求最大生成树！

于是，【生成树】的性质也出来了！


教练还说过：

>所谓最大生成树，就是在一个图中选出一个树，是树的边权和最大。

我们想到了 Kruskal 算法

Kruskal 的基本思路：

1. 将所有边按边权大小排序；

2. 循环所有边 $e_1\sim e_m$，取出其端点，边权；

3. 看端点 $a$ 和 $b$ 是否在同一集合中，如不是，答案加上边权，将其放入同一集合，计数器自加；

4. 看计数器是否达到 $n-1$，即已有 $n-1$ 条边，退出。

可以看出，这个算法的时间复杂度为 $O(mlogm)$。

其中，$m$ 表示边的数量。


于是，这题没了！


```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int v,u,w;
}e[4000005];
int head[2005],k=1;
inline void add(int u,int v,int w)
{
	e[k].v=v;
	e[k].w=w;
	e[k].u=u;
	k++;
}//前向星存图
bool operator < (const node & a,const node & b)
{
	return a.w>b.w;
}//重载运算符
int a[2005];
int fa[2005];
inline int find(int x)
{
	if(fa[x]!=x) fa[x]=find(fa[x]);
	return fa[x];
}//并查集
int main()
{
	int n;
	cin>>n;
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		for(int j=1;j<i;j++)
		{
			add(i,j,a[i]^a[j]);//建边
			cnt++;
		}
	}
	sort(e+1,e+cnt+1);
	int tot=0,ans=0;
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=cnt;i++)
	{
		int a=find(e[i].u),b=find(e[i].v),w=e[i].w;
		if(a!=b)
		{
			fa[a]=b;
			tot++;
			ans+=w;
		}
		if(tot==n-1) break;
	}//Kruskal
	cout<<ans;
}
```
然后你发现你只对了一个点！~~（不要问我为什么知道）~~

然后你发现：

> “十年OI一场空，不开long long见祖宗！

AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
struct node{
	ll v,u,w;
}e[4000005];
int head[2005],k=1;
inline void add(int u,int v,ll w)
{
	e[k].v=v;
	e[k].w=w;
	e[k].u=u;
	k++;
}
bool operator < (const node & a,const node & b)
{
	return a.w>b.w;
}
ll a[2005];
int fa[2005];
inline int find(int x)
{
	if(fa[x]!=x) fa[x]=find(fa[x]);
	return fa[x];
}
int main()
{
	int n;
	cin>>n;
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		for(int j=1;j<i;j++)
		{
			add(i,j,a[i]^a[j]);
			cnt++;
		}
	}
	sort(e+1,e+cnt+1);
	ll tot=0,ans=0;
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=cnt;i++)
	{
		ll a=find(e[i].u),b=find(e[i].v),w=e[i].w;
		if(a!=b)
		{
			fa[a]=b;
			tot++;
			ans+=w;
		}
		if(tot==n-1) break;
	}
	cout<<ans;
}
```

AC证明：

![](https://cdn.luogu.com.cn/upload/image_hosting/cjn2hhux.png)

看一眼时间：3.32 s​！！！

因为时间复杂度是 $O(mlogm)$ 级别的，而 $m$ 是 $n^2$ 级别的！

所以，我们在超时的边缘疯狂试探。

这时，Prim 来拯救我们！

>所谓 Prim，在稠密图一方。

Prim 的算法思想：和 Dijsktra 相似,只不过是把最后一步 $dis$ 数组的含义改为了到已选中的点中距离最长的长度。

如果你不知道 Dijsktra，请转至：

- [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)


注意此题是最大生成树，细节问题要区分。

根据 Dijsktra 的复杂度，Prim 的复杂度，显然为: $O(n^2)$

而n<=2000，足以通过此题。

那么，Prim 的板子改一改，就可以了！


AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll g[2005][2005];
ll dis[2005],a[2005];
bool vis[2005]; 
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		for(int j=1;j<i;j++)
		{
			g[i][j]=g[j][i]=(a[i]^a[j]);
		}
	}//临接矩阵存图
	ll res=0;
	for(int i=0;i<n;i++)
	{
		int t=-1;
		for(int j=1;j<=n;j++)
		{
			if(!vis[j]&&(t==-1||dis[j]>dis[t])) t=j;
		}
		if(i) res+=dis[t];
		vis[t]=true; 
		for(int j=1;j<=n;j++)
		{
			dis[j]=max(dis[j],g[t][j]);
		}
	}//Prim
	cout<<res;
}

```

![](https://cdn.luogu.com.cn/upload/image_hosting/j3c7lyx9.png)
              

可以看到，完虐 Kruskal!
              
妈妈再也不会担心会 TLE 了！
              

### Conclusion：

> 稠密图跑 Prim！

> 稀疏图跑 Kruskal！

---

## 作者：xiaozeyu (赞：1)

这道题难度其实~~不是太大~~

可以用最短路来算，简单易懂
```
#include<bits/stdc++.h>
using namespace std;
long long n,dis[2500],a[2500];
long long res,k,sum,Max;
bool vis[2500];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);//输入
	for(int i=2;i<=n;i++)
		dis[i]=a[i]^a[1];//把每个先与1异或
	vis[1]=1;
	for(int i=2;i<=n;i++)
	{
		Max=k=0;//重置
		for(int j=1;j<=n;j++)
			if(!vis[j]&&dis[j]>Max)
				Max=dis[j],k=j;//选出最优的
		vis[k]=1;//标记
		sum+=Max;//加上这次的最大值
		for(int j=1;j<=n;j++)
			if(!vis[j])
				dis[j]=max(dis[j],a[j]^a[k]);//重置dis，dis=max(原先的，这次的与每个的异或)
	}
	cout<<sum;//漂亮输出
}
```


---

## 作者：zengxr (赞：1)

比赛的得分为两个队伍的xor值。初看，这个题目似乎要用dp求解，因为你要考虑一支球队与另一支球队是赢是输所获得的不同收益值。但是，因为只要求得最大收益值。就假设每两支队伍都要进行一场比赛。

## 然后跑一遍最大生成树就好了




## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
  int x,y;
  long long dis;
}a[4000010];
int father[2002];
long long arr[2002];
int n,tot;
int find(int x)
{
  if(x!=father[x])
    father[x]=find(father[x]);
  return father[x];
}
void unionn(int x,int y)
{
  x=find(x),y=find(y);
  if(x!=y)
    father[x]=y;
}
bool cmp(node xx,node yy)
{
  return xx.dis>yy.dis;
}
int main()
{
  scanf("%d",&n);
  for(int i=1;i<=n;i++)
  {
    scanf("%lld",&arr[i]);
  }
  for(int i=1;i<=n;i++)
    father[i]=i;
  for(int i=1;i<=n;i++)
  {
    for(int j=i+1;j<=n;j++)
    {
      a[++tot].x=i;
      a[tot].y=j;
      a[tot].dis=(long long)arr[i]^arr[j];
    }
  }
  sort(a+1,a+1+tot,cmp);
  int k=0;
  long long ans=0;
  for(int i=1;i<=tot;i++)
  {
    if(find(a[i].x)!=find(a[i].y))
    {
      unionn(a[i].x,a[i].y);
      ans+=(long long)a[i].dis;
      k++;
    }
    if(k==n-1)
    break;
  }
  printf("%lld\n",ans);
}
```
## 记得开longlong


---

## 作者：novax (赞：0)

#### 题意
有 $N$ 支队伍参加比赛，每支队伍有一个队伍ID。

任意两支队伍进行比赛会得到两支队伍ID按位异或的分数，每场比赛淘汰一支队伍。

要进行比赛直到剩下一支队伍。

#### 做法
既然要比到只剩一支队伍，那就要进行 $N-1$ 场比赛。每两支队伍进行比赛得到的分数是确定的，所以题目相当于：进行 $N-1$ 次比赛，使得每一支队伍都参加比赛并使得到的总分最大化。可以将所有队伍之间的比赛关系看作一张完全图，两点间的边权即为两点ID的按位异或值。本题就变成了在这个完全图中找到一颗生成树，使其边权之和最大，也就是图上的**最大生成树**。

用Kruscal算法可以很方便的求最小生成树，求最大生成树的原理和最小生成树一致，只是在排序时将边按照权值从大到小排序就可以了。

#### 代码
```cpp
#include <cstdio>
#include <algorithm>
struct edge
{
	int fr,to,val;
};
edge a[2000100];
int cnt;
void add(int u,int v,int w)
{
	a[++cnt].fr=u;
	a[cnt].to=v;
	a[cnt].val=w;
}
bool cmp(edge x,edge y)
{
	return x.val>y.val;
}
int c[2010];
int f[2010];
int find(int x)
{
	if(x!=f[x])
		f[x]=find(f[x]);
	return f[x];
}
int N; 
int main()
{
	scanf("%d",&N);
	int i,j;
	for(i=1;i<=N;i++)
		scanf("%d",&c[i]);
	for(i=1;i<=N;i++)
		for(j=i+1;j<=N;j++)
			add(i,j,c[i]^c[j]);
	std::sort(a+1,a+cnt+1,cmp);
	for(i=1;i<=2005;i++)
		f[i]=i;
	int f1,f2,d;
	long long ans;
	d=0;ans=0;
	for(i=1;i<=cnt;i++)
	{
		f1=find(a[i].fr);
		f2=find(a[i].to);
		if(f1==f2)
			continue;
		f[f1]=f2;
		ans+=a[i].val;
		d++;
		if(d==N-1)
			break;
	}
	printf("%lld\n",ans);
}
```


---

## 作者：lxgw (赞：0)

#### [题目传送门](https://www.luogu.com.cn/problem/P4826)

### 题意
有 $n$ 支球队，每支队伍都有一个编号。现在进行淘汰赛制，即每场会淘汰掉一支球队，直到剩最后一支球队；每场比赛的得分为这两支球队的编号的按位异或，求最后分数和最大是多少。

### 思路
这题是个最大生成树。

先任意选两个点来建边其边权为这两个编号的按位异或，把全部边建完之后把边权从大到小排序，在用 kruskal 跑一遍最大生成树就好了。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct edge {
	int x,y,z;
} e[10001000];
int f[10001000],n,m,a[10001000];
inline bool cmp(edge a,edge b) {
	return a.z>b.z;
};//把边按边权从大到小排序。
inline int find(int x) {//并查集，用做判断两个点是否联通
	if(x==f[x])return x;
	return f[x]=find(f[x]);
}
inline void kru() {//kruskal算法
	int cnt=0/*已建的边数*/,ans=0/*最终的和*/;
	for(int i=1; i<=m; ++i) {//从小到大枚举边。
		int fx=find(e[i].x),fy=find(e[i].y);
		if(fx!=fy) ++cnt,ans+=e[i].z,f[fx]=fy;//如果两个点没联通就建边。
		if(cnt==n-1)break;//已经有n-1条边了（已经全部联通）就退出。
	}
	cout<<ans;
}
signed main() {
	cin>>n;
	for(int i=1; i<=n; ++i) f[i]=i/*初始化f数组*/,cin>>a[i];
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			++m,e[m].x=i,e[m].y=j,e[m].z=a[i]^a[j];//n方的建边。
	sort(e+1,e+m+1,cmp);//排序。
	kru();//跑一遍 kruskal 。
	return 0;
}

```

完结撒花~

谢谢 qwq 。




---

## 作者：_Scaley (赞：0)

## 题意简化

1. 有 $N$ 个队伍互相比赛。

2. 每次比赛分数为两支队伍的 ID 的 XOR。

3. 每次输掉的队伍不能再次参加比赛。

4. 问比赛分数的最大值是多少。

## 题目分析

首先，从题意中的第 3 条和第 2 条可以知道，每个队伍只能被一个队伍打败，但可以打败多个队伍。

这时候可以建一个被打败关系的图（口胡）：

* 每个队伍是一个点，拥有自己的 ID 。

* 每两个点只能直接或者间接的相连，且两个点之间只能有一条路 。

* 直接相连的两个点之间的边权为两点 ID 的 XOR 值 。

现在有没有觉得这张（口胡的）图很熟悉 —— 树 。

所以问题就简化成了：**求一棵树，使这棵树的总边权最大。**

又由于每个点都有可能成为这棵树的一部分，所以可以建一个每两个点之间都有一条边的图。

那么这就是一个求最大生成树的问题了。

## 注意

**1. 开 long long 。**

**2. 祖先数组要初始化 。**

**3. 存完全图时加优化 。**

**4. 如果用的是 printf 用 lld 。**

-------

## 代码实现
```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#define MAXN 2001
#define LL long long
//------------定义变量---------------
int js = 0;
int n;
int anc[MAXN], id[MAXN]; // anc 存点祖先，id 存团队ID 。
//------------定义结构体-------------
struct Node{
	int u, v, w;
}e[4000001 << 1]; // 存完全图
//------------声明函数---------------
int read(); // 快读
void add(int, int, int); // 存边
int max(int, int); // 比大小
void swap(int, int); // 没用到
bool comp(Node, Node); // sort 结构体排序
int find(int); // 找祖先
void Heb(int, int); // 合并祖先
LL kls(); // 克鲁斯卡尔求最大生成树
//------------主函数-----------------
int main() {
	n = read();
	for (int i = 1; i <= n; ++i) id[i] = read(), anc[i] = i; // 记得 anc 要初始化
	for (int i = 1; i <= n; ++i){
		for (int j = i + 1; j <= n; ++j) // j 从 i + 1 开始
			add(i, j, id[i] ^ id[j]);
	}
	printf("%lld", kls());
	return 0;
}
//------------定义函数---------------
int read() {
	int x = 0, f = 0; char ch = getchar();
	while (!isdigit(ch)) {f |= (ch == '-'); ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + (ch ^ 48); ch = getchar();}
	return f ? -x : x;
}
void add(int u, int v, int w) {e[++js].u = u; e[js].v = v; e[js].w = w;}
int max(int x, int y) {return x > y ? x : y;}
void swap(int &x, int &y) {x ^= y ^= x ^= y;}
bool comp(Node x, Node y) {return x.w > y.w;}
int find(int x) {if (x != anc[x]) return anc[x] = find(anc[x]); return anc[x];}
void Heb(int x, int y) {int a = find(x), b = find(y); if (a != b) anc[b] = a;}
LL kls() {
	int cnt = 0, f = 0; LL ans = 0; std :: sort(e + 1, e + 1 + js, comp);
	for (int i = 1, u, v, w; i <= js; ++i) {
		u = e[i].u; v = e[i].v; w = e[i].w;
		if (find(u) != find(v)) {Heb(u, v); ++cnt; ans += w;}
		if (cnt == n - 1) {f = 1; break;}
	}
	if (f == 0) ans = -1;
	return ans;
}
```
码丑勿喷

---

## 作者：KEBrantily (赞：0)

**总的来说，**
**这道题只考查了单纯的建图和最大生成树**

但这却是蓝题（问号

------------

## 题意
题意的理解比较麻烦

简单说就是 n 支队伍比赛，i 号队伍和 j 号队伍比赛可获得 i ^ j 的分数，然后其中一支队伍会输，退出比赛，问当场上只有一支队伍的时候分数最大是多少



------------

## 分析

**这么看似乎比较麻烦，那我们转化一下：**

- i 号队伍和 j 号队伍比赛可以看做从 i 向 j 连了一条边，边权就是 i ^ j
- 其中一支队伍会输，退出比赛，也就是不能出现环
- 求最大分数也就是在剩下的无环图中找出最大的 n - 1 条边的权值和

### 证明：
如果可以出现环，那么输掉的球队就可以再次进行比赛，也就是说没有输掉的球队了，而且这样得分也会重复累加

**这样我们就可以看出这就是求一个最大生成树的树边和**


------------

最后

**记得开 long long**


```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#define maxn 5005000

using namespace std;

long long n,m,u[maxn],tot,edge_tot,a,b[maxn],cnt;
long long dfn[maxn],low[maxn],sum,ans,head[maxn],fa[maxn];

struct edge{
	long long fr,to,nxt,dis;
}e[maxn*2];

inline void add(long long fr,long long to,long long dis){
	e[++edge_tot].to=to;
	e[edge_tot].dis=dis;
	e[edge_tot].fr=fr;
	e[edge_tot].nxt=head[fr];
	head[fr]=edge_tot;
}

inline long long Get_Father(long long x){
	if(fa[x]==x) return x;
	return fa[x]=Get_Father(fa[x]);
}

inline void ys(long long x,long long y){
	x=Get_Father(x);
	y=Get_Father(y);
	if(x!=y);
	fa[y]=x;
}

inline bool pd(long long x,long long y){
	if(Get_Father(x)==Get_Father(y)) return true;
    else return false;
}

inline long long cp(edge a,edge b){
	return a.dis>b.dis; 
}

int main(){
	scanf("%d",&n);
	for(long long i=1;i<=n;i++){
		scanf("%d",&u[i]);
		b[i]=i;
		fa[i]=i;
	}
	for(long long i=1;i<n;i++){
		for(long long j=i+1;j<=n;j++){
			long long c=u[i]^u[j];
			add(i,j,c);
			sum++;
		}
	}
	
	sort(e+1,e+sum+1,cp);
	
	for(long long i=1;i<=sum;i++){
//		cout<<e[i].fr<<" "<<e[i].to<<" "<<e[i].dis<<" "<<ans<<endl;
		if(!pd(e[i].fr,e[i].to)){
			ys(e[i].fr,e[i].to);
			ans+=e[i].dis;
			cnt++;
		}
		if(cnt==n-1) break;
	}
	cout<<ans;
	return 0;
}
```

制作不易，不喜勿喷

---

## 作者：Bronya18C (赞：0)

# 最小生成树Kruskal（克鲁斯卡尔）

---

## 这道题是一道裸模版，最主要的是两个知识点：
### xor(异或)

也就是把两个数转化成二进制先，再按下面的规则改变：

1 xor 1=0

0 xor 1=1

1 xor 0=1

0 xor 0=0

(即一样为1，不一样为0)

比如，

10=1010

13=1101

10 xor 13 =0111=7

---
### kruskal

就是说我们把每条边的两个点存入边的结构体数组，顺便把边的权值存进去。

然后我们按权值从小到大排序。

我们把目前最小的边来检查一下，它的两个点是否已经连了。

是：继续下一条边（因为再连会有环，树是无环的无向图）

否：利用并查集连起来，然后答案加上边的权值。

[详见我的另一篇题解](https://www.luogu.org/blog/HarryPoter/solution-p1194)

---
# 附上代码：
```
#include<bits/stdc++.h>

using namespace std;
long long N,n[20005],g,f[20005],ans;
struct road
{
	long long x,y,value;
}G[10000005];
bool cmp(road a,road b)
{
	return a.value>b.value;
}
long long getfather(long long F)
{
	if(f[F]==F)return F;
	f[F]=getfather(f[F]);
	return f[F];
}
int main()
{
	cin>>N;
	for(int i=1;i<=N;i++)
	{
		cin>>n[i];
		for(int j=1;j<i;j++)
		{
			G[++g].x=i;
			G[g].y=j;
			G[g].value=n[i] xor n[j];
		}
		f[i]=i;
	}
	sort(G+1,G+1+g,cmp);
	for(int i=1;i<=g;i++)
	{
		if(N==1)break;
		long long f1=getfather(G[i].x);
		long long f2=getfather(G[i].y);
		if(f1!=f2)
		{
			f[f1]=f2;
			ans+=G[i].value;
			N--;
		}
	}
	cout<<ans<<endl;
	return 0;
} 
```
[安利一下自己的博客](https://www.luogu.org/blog/HarryPoter/)

---

## 作者：曹老师 (赞：0)

## Sol ##

[blog食用](http://www.caolaoshi.men/index.php/archives/usaco15feb-super.html)

克鲁斯卡尔，最大生成树。

可以在两点之间连一条路径，权值就是$num[i]$^$num[j]$，然后跑一遍最大生成树就行。因为通过题目很容易知道有$n$个点$n-1$条边，考虑树，最后的答案，两点间只有一条路径，而且题目中给定的是一个图，再考虑生成树。答案要求最大值，因此就是最大生成树，我打的克鲁斯卡尔的。

## Code ##

```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

struct Road {
	int from , to , len;
	bool operator < (const Road &a) const {
		return len > a.len;
	}
};
Road seg[2005*2005];
int n , top , fa[2005] , cnt;
long long sum , num[2005];

int find(int x) {
	if(fa[x] != x)
		fa[x] = find(fa[x]);
	return fa[x];
}

int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
		scanf("%lld",&num[i]);
	for(int i=1; i<=n; i++)
		for(int j=i+1; j<=n; j++) {
			top++;
			seg[top].from = i;
			seg[top].to = j;
			seg[top].len = num[i] ^ num[j];
		}
	sort(seg+1 , seg+top+1);
	for(int i=1; i<=n; i++)
		fa[i] = i;
	for(int i=1; i<=top; i++) {
		int t1 = find(seg[i].from) , t2 = find(seg[i].to);
		if(t1 != t2) {
			sum += seg[i].len;
			fa[t2] = t1;
			cnt++;
		}
		if(cnt == n-1)
			break;
	}
	printf("%lld",sum);
	return 0;
}
```


  [1]: https://www.luogu.org/problemnew/show/P4826

---

