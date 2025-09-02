# Bakery

## 题目描述

Masha wants to open her own bakery and bake muffins in one of the $ n $ cities numbered from $ 1 $ to $ n $ . There are $ m $ bidirectional roads, each of whose connects some pair of cities.

To bake muffins in her bakery, Masha needs to establish flour supply from some storage. There are only $ k $ storages, located in different cities numbered $ a_{1},a_{2},...,a_{k} $ .

Unforunately the law of the country Masha lives in prohibits opening bakery in any of the cities which has storage located in it. She can open it only in one of another $ n-k $ cities, and, of course, flour delivery should be paid — for every kilometer of path between storage and bakery Masha should pay $ 1 $ ruble.

Formally, Masha will pay $ x $ roubles, if she will open the bakery in some city $ b $ ( $ a_{i}≠b $ for every $ 1<=i<=k $ ) and choose a storage in some city $ s $ ( $ s=a_{j} $ for some $ 1<=j<=k $ ) and $ b $ and $ s $ are connected by some path of roads of summary length $ x $ (if there are more than one path, Masha is able to choose which of them should be used).

Masha is very thrifty and rational. She is interested in a city, where she can open her bakery (and choose one of $ k $ storages and one of the paths between city with bakery and city with storage) and pay minimum possible amount of rubles for flour delivery. Please help Masha find this amount.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF707B/5363dd57fa93616f4ccd4cae1a9732744eeb0a9c.png)Image illustrates the first sample case. Cities with storage located in and the road representing the answer are darkened.

## 样例 #1

### 输入

```
5 4 2
1 2 5
1 2 3
2 3 4
1 4 10
1 5
```

### 输出

```
3```

## 样例 #2

### 输入

```
3 1 1
1 2 3
3
```

### 输出

```
-1```

# 题解

## 作者：Aisaka_Taiga (赞：2)

给定 $n$ 个点，从其中 $k$ 个点中选一个点，从剩余的点中选一个点，使选出的两点距离最小。

我们思考一下，如果选出的两点要是中间会经过点的话，那么经过的这个点一定是属于两部分其中一部分的，我们可以把相应部分的那个选出来的点，改为中间经过的点，因为没有非正边权，所以这样一定会更优。

所以我们就可以枚举每一跳边，如果两端的点不同，我们就可以取个最小值，直接输出即可。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define N 1000100
using namespace std;
int n,m,k,t[N],u[N],v[N],w[N],ans;
signed main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++)cin>>u[i]>>v[i]>>w[i];
    for(int i=1;i<=k;i++){int x;cin>>x;t[x]=1;}
    ans=INF;
    for(int i=1;i<=m;i++)if(t[u[i]]^t[v[i]])ans=min(ans,w[i]);
    if(ans==INF)cout<<"-1"<<endl;
    else cout<<ans<<endl;
    return 0;
}
```

---

## 作者：xzggzh1 (赞：1)

题意：

有N个城市，M条无向边，其中有K个城市是仓库。

现在要在非仓库的城市中选择一家开面包店，使得其最少与一个仓库联通，且到所有仓库距离的最小值最小。

---

考察你最基本的图论建图能力。

就是对于每一个仓库考虑与它有连边的非仓库的最短距离。

（为什么这么做是对的，因为除了仓库，所有点都是非仓库，那么如果最后选的点和最靠近它的仓库不是相邻的，那么必然可以在这个点与最靠近它的仓库的路径上选一个点使得答案可以更小）

然后把所有的取一个最小值，若所有仓库旁边都没有非仓库，那么输出 $ -1$ 。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int Maxn=1e5+5;
const int inf=1<<30;
inline int R()
{
    char c;int res,sign=1;
    while((c=getchar())>'9'||c<'0') if(c=='-') sign=-1;res=c-'0';
    while((c=getchar())>='0'&&c<='9') res=res*10+c-'0';
    return res*sign;
}
int n,m,k,First[Maxn],to[Maxn*2],We[Maxn*2],Next[Maxn*2],cnt;
bool vis[Maxn];
inline void add(int z,int y,int w)
{
    Next[++cnt]=First[z];
    First[z]=cnt;
    to[cnt]=y;We[cnt]=w;
}
int main()
{
    n=R();m=R();k=R();
    int x,y,w;
    for(int i=1;i<=m;i++)
    {
        x=R();y=R();w=R();
        add(x,y,w);
        add(y,x,w);
    }
    int ans=inf;
    for(int i=1;i<=k;i++)vis[R()]=1;
    for(int i=1;i<=n;i++)
    if(vis[i])
    for(int k=First[i];k;k=Next[k])
    if(!vis[to[k]])ans=min(ans,We[k]);
    if(ans==inf) puts("-1");
    else printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Maysoul (赞：0)

一开始还以为是最短路，想了一圈之后，发现只需要遍历每一条终点不是仓库的边即可。

证明一下：一个点只有仓库和非仓库的情况，如果有一条路径，经过了多个非仓库的点，那么这条路径上一定能找到一个比它更短的路径，通向一个非仓库。

这里我使用链式前向星存边，以仓库为起点，遍历每一条边，对于每一条边，先看终点是不是仓库，如果不是仓库，就更新一下最小值。

代码如下：

```
//2023/5/14
//别着急，先通读一遍题目
//别忘了开long long
//写完先看一遍怎么降复杂度
//要么开全局变量要么给定初值
//想想看，有什么情况需要特判
//看看数组开的够不够大
//std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+10;
const int INF=0x3f3f3f3f;
int num,ans=INF;
int head[10000000];
int vis[10000000];
int escnt;
struct linkstar{
	int from,to,w,next;
}edge[10000000];
void add(int from,int to,int w)//链式前向星存边
{
	edge[++escnt].from=from;
	edge[escnt].to=to;
	edge[escnt].w=w;
	edge[escnt].next=head[from];
	head[from]=escnt;
}
vector<int> vec;
int main()
{
	memset(head,-1,sizeof(head));
	int n,m,k;
	cin>>n>>m>>k;
	for (int i=1;i<=m;i++)
	{
		int x,y,w;
		cin>>x>>y>>w;
		add(x,y,w);
		add(y,x,w); 
	}
	for (int i=1;i<=k;i++)//记录每一个仓库
	{
		int o;
		cin>>o;
		vec.push_back(o);
		vis[o]=1;
	}
	for (int i=0;i<k;i++)//以仓库为起点进行遍历
	{
		int p=vec[i];
		for (int j=head[p];j!=-1;j=edge[j].next)
		{
			if(!vis[edge[j].to])
			{
				ans=min(edge[j].w,ans);
			}
		}
	}
	ans== INF ? cout<<"-1"<<endl : cout<<ans<<endl;
	return 0;
}

```


---

## 作者：Keroshi (赞：0)

# 题目分析
题目要求仓库前往面包店的最小耗时。  
如果一个仓库要送面包到面包店，那么一定会经过一条连接仓库和面包店的边，否则无法送达。    
那么最短路径一定是连接仓库和面包店的，就可以 $O(m)$ 枚举每一条边，选择最短的即可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,k,t[N],l[N],r[N],w[N],ans;
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++) scanf("%d%d%d",&l[i],&r[i],&w[i]);
    for(int i=1;i<=k;i++) {int x;scanf("%d",&x);t[x]=1;}
    ans=2e9;
    for(int i=1;i<=m;i++)
        if(t[l[i]]^t[r[i]]) 
        ans=min(ans,w[i]);
    printf("%d",ans<2e9-1?ans:-1);
    return 0;
}
```

---

## 作者：_Revenge_ (赞：0)

### 题目简化和分析：   

~~这题看着玄胡很水实际。~~    

**我们需要做什么？**   

- 只需对每个工厂周围的面包店遍历一遍打擂台取最小
- 注意只对面包店遍历，所以对工厂设标记     
- 如果打完擂台发现 $ans=inf$ 则说明全是工厂   

### Solution:   

```cpp
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N=1e5+50;

int n,m,k;

struct edge{
	int to,dis,next;
}e[N<<1];

int head[N<<1],a[N],cnt;

void add_edge(int u,int v,int w){
	++cnt;
	e[cnt].to=v;
	e[cnt].dis=w;
	e[cnt].next=head[u];
	head[u]=cnt;
}
bool vis[N];
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;++i){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	for(int i=1;i<=k;++i){
		scanf("%d",&a[i]);
		vis[a[i]]=1;
	}
	int ans=INT_MAX;
	for(int i=1;i<=k;++i){
		for(int j=head[a[i]];j;j=e[j].next){
			int y=e[j].to;
			if(vis[y]) continue;
			ans=min(ans,e[j].dis);
		}
	}
	printf("%d\n",ans==INT_MAX?-1:ans);
}
```


---

## 作者：SqrtSecond (赞：0)

## 题意

给定一张 $n$ 个节点， $m$ 条边的带权无向图，有 $k$ 个指定的点可以建仓库，其余的点可以建面包店（总共只能建一个），问从仓库到面包店的最小距离。

$n,m\le10^5,0\le k\le n$

## 思路1

枚举仓库和面包店，预处理最短路，时间复杂度 $O(n^3)$ ，空间复杂度 $O(n^2)$ ，显然要炸。

## 思路2

我们发现，每个节点都不是建仓库就是建面包店。

由于**边权为正**，我们可以证明最优方案在走的过程中**至多只走一条边。**

为什么呢？

假设你从一个仓库 $u$ 走到了一个面包店 $v$ ，最短路径走过了至少两条边。

那么，你中间至少经过了一个节点 $x$ 。

如果这个节点可以建仓库，由于这是最短路径，且边权为正，显然从 $x$ 走到 $v$ 的方案更优。

反之，则从 $u$ 走到 $x$ 更优。

所以，我们只需要判定两个节点之间有没有边即可。

如果枚举两个顶点，时间复杂度就能降为 $O(n^2)$ 。

## 思路3

如果我们直接枚举边呢？

开个结构体（数组也行）存边。

如果这条边的两边都建仓库或都建面包店就不考虑，否则就更新答案。

时间复杂度 $O(m)$ ，空间复杂度 $O(m)$ ，可以通过本题。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=2e9;
inline int read()
{
	char ch=getchar();int x=0,r=1;
	while(ch<'0'||ch>'9'){if(ch=='-')r=0;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return r?x:-x;
}//快读
int n,m,k,ans=inf;
struct edge
{
	int u,v,w;
}e[200100];//存边
bool b[100100];//能否建仓库 
signed main()
{
	n=read();m=read();k=read();
	for(int i=1;i<=m;++i)
	{
		e[i].u=read();e[i].v=read();e[i].w=read();
	}
	while(k--)b[read()]=true;//维护可否建仓库
	for(int i=1;i<=m;++i)
	{
		if(b[e[i].u]==b[e[i].v])continue;//状态相同的不考虑 
		ans=min(ans,e[i].w);//更新答案 
	}
	printf("%d",ans==inf?-1:ans);//记得判-1 
	return 0;//养成好习惯
}
```

---

