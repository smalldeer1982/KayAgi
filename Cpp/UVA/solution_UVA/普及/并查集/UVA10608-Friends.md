# Friends

## 题目描述

某个小镇里有 $N$ 个位公民，其中有些人是朋友关系。

在这个小镇里，“我的朋友的朋友是我的朋友”是一条不变的真理，即如果 $A$ 和 $B$ 是朋友，$B$ 和 $C$ 是朋友，那么 $A$ 和 $C$ 也是朋友。

由于镇里的朋友太多，形成了几个朋友团（在任何一个朋友团里的人都是朋友，而任意两个不相同朋友团的人不是朋友）。你想知道镇里最大的朋友团里有多少位公民。

## 说明/提示

$1 \leq N \leq 3 \times 10^4$，$0 \leq M \leq 5 \times 10^5$。

## 样例 #1

### 输入

```
2
3 2
1 2
2 3
10 12
1 2
3 1
3 4
5 4
3 5
4 6
5 2
2 1
7 1
1 2
9 10
8 9```

### 输出

```
3
7```

# 题解

## 作者：xhhhh36 (赞：3)

# 题意
有 $n$ 个人和 $m$ 组关系，每组关系表示 $A$ 和 $B$ 是朋友。朋友的朋友也是朋友。问人数最多的朋友群有多少人？
# 思路
看到这题的描述马上会想到用**并查集**维护集合。那并查集怎么维护集合呢？首先用一个 $fa$ 数组来存储每个集合的代表元素，最开始有 $n$ 个集合。每遇到一个关系，就将 $A$ 和 $B$ 所在的集合合并，即$fa_{B} \to fa_{A}$。最后再用一个计数数组来计数每个集合中的元素个数。注意：本题有多组数据。[并查集模板题](https://www.luogu.com.cn/problem/P3367)
# AC code
```cpp
#include <bits/stdc++.h>

using namespace std;
int g,n,m,fa[500001],ans[30001],mx=0;
int find(int x)
{
	if (fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void un(int x,int y)
{
	fa[find(x)]=find(y);
}
int main()
{
	cin>>g;
	for (int i=1;i<=g;i++)
	{
		scanf("%d%d",&n,&m);
		memset(ans,0,sizeof(ans));
		for (int j=1;j<=n;j++)
		{
			fa[j]=j;
		}
		for (int j=1;j<=m;j++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			un(x,y);
		}
		for (int j=1;j<=n;j++)
		{
			ans[find(j)]++;
		}
		for (int j=1;j<=n;j++)
		{
			mx=max(mx,ans[j]);
		}
		cout<<mx<<endl;
        mx=0;//不要忘了重置
	}
	return 0;
}
```


---

## 作者：Jorisy (赞：2)

根据题目，可以看出，这道题要我们求元素最多的并查集。  
对于并查集，有两个操作：
- “查”：查找一个集合内的元素的祖先。通常写成一个递归函数：
```cpp
int find(int x)
{
	return f[x]==x?x/*祖先就是自己*/:f[x]=find(f[x])/*路径压缩*/;
}
```
- “并”：将两个元素所在集合变成一个。通常会调用“查”函数：
```cpp
f[find(x)]=find(y);
```
其还有一个 $O(n)$ 的初始化：
```cpp
for(int i=1;i<=n;i++)
{
	f[i]=i;
}
```

---

那理解了并查集之后，就可以解题了。  
首先输入 $t$ 组数据，然后输入关系：
```
int n,m;
cin>>n>>m;
for(int i=1;i<=n;i++)
{
	f[i]=i;
}//初始化
for(int i=1;i<=m;i++)
{
	int x,y;
	cin>>x>>y;
	f[find(x)]=find(y);//“并”
}
```
接下来，我们可以开一个计数数组，来计数每个集合的元素数：
```cpp
for(int i=1;i<=n;i++)
{
	ans[find(i)]++;//元素所在的集合的祖先加一
}
```
最后，我们在 $O(n)$ 打擂一下求最大集合个数即可。  
AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

int f[500005],ans[30005];

int find(int x)//“查”
{
	return f[x]==x?x:f[x]=find(f[x]);
}

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,m;
		cin>>n>>m;
		memset(ans,0,sizeof(ans));//计数数组初始化
		for(int i=1;i<=n;i++)
		{
			f[i]=i;
		}//并查集数组初始化
		for(int i=1;i<=m;i++)
		{
			int x,y;
			cin>>x>>y;
			f[find(x)]=find(y);//“并”
		}
		for(int i=1;i<=n;i++)
		{
			ans[find(i)]++;//计数
		}
		int maxans=INT_MIN;
		for(int i=1;i<=n;i++)
		{
			maxans=max(maxans,ans[i]);
		}//求最大集合个数
		cout<<maxans<<endl;
	}
	return 0;
}
```

---

## 作者：DeepSkyBlue__ (赞：1)

这道题可以用 BFS 来求连通块。主要思想就是利用 BFS 求出每一个连通块，对连通块内的点进行染色，最后看哪个连通块里的点最多。

CODE：

```cpp
#include<bits/stdc++.h>
//#include<tr1/unordered_map> 
using namespace std;
//using namespace std::tr1;
unordered_map<int,vector<int> >adj;
queue<int>q;
bool v[200001];
int color=0;//color代表当前连通块的颜色
int C[200001];//C数组储存每一个点的颜色
int sth[200001];//sth用来存储各个颜色的连通块的大小
void bfs(int s)
{
	q.push(s);//源点入队
	v[s]=true;//这个点走过了
	C[s]=color;
	while(!q.empty())//只要队内还有元素就继续扩展
	{
		int cur=q.front();//对队首元素进行bfs
		q.pop();
		for(int i=0;i<adj[cur].size();i++)
		{
			int next=adj[cur][i];//next代表下一步能到的点
			if(!v[next])//如果这个点没有走过
			{
				v[next]=true;//那么就走这个点
				q.push(next);//这个点入队
				C[next]=color;//这个点染色
			}
		}
	}
}
bool cmp(int x,int y)//手写cmp函数
{
	return x>y;
}
int main()
{
	int n,m;	
	int T;
	cin>>T;	
	while(T--)
	{
		cin>>n>>m;
		memset(v,0,sizeof(v));
		adj.clear();
		color=0;
		memset(C,0,sizeof(C));
		memset(sth,0,sizeof(sth));//多测注意清空
		for(int i=1;i<=m;i++) 
		{
			int x,y;
			cin>>x>>y;
			adj[x].push_back(y);
			adj[y].push_back(x);//无向图2次建边
		}
		for(int i=1;i<=n;i++)
			if(!v[i])//如果没有被走过
			{
				color++;//变到下一种颜色
				bfs(i);//i属于一个新的连通块，以i为起点bfs
			}
		for(int i=1;i<=n;i++)sth[C[i]]++;//统计各个连通块的大小
		sort(sth+1,sth+1+color,cmp);//找出最大的连通块
		cout<<sth[1]<<endl;
	}
	return 0;
}
```


---

## 作者：fuwei123 (赞：0)

并查集板子题。

如果你不会并查集，请出门左转，查看[并查集板子](https://www.luogu.com.cn/problem/P3367)。

那么这道题就很好做了，路径压缩别忘了写，然后从头遍历每个点，让它祖先对应的集合大小加一，更新答案即可。**非常非常**水，建议评橙（并查集板子是橙）。

```cpp
#include<bits/stdc++.h>
using namespace std;

int fa[30005], n, m, T, ans[30005];
int find(int x){
	if(fa[x] == x)return x;
	return fa[x] = find(fa[x]);
}
void merge(int x, int y){
	fa[find(x)] = find(y);
}
int main(){
	ios::sync_with_stdio(0);
	cin >> T;
	while(T--){
		cin >> n >> m;
		for(int i = 1;i <= n;i++){
			fa[i] = i;
			ans[i] = 0;
		}
		int a, b;
		for(int i = 1;i <= m;i++){
			cin >> a >> b;
			merge(a, b);
		}
		for(int i = 1;i <= n;i++){
			ans[find(i)]++;
		}
		int maxn = -1145141919;
		for(int i = 1;i <= n;i++){
			maxn = max(maxn, ans[i]);
		}
		cout << maxn << "\n";
	}
	return 0;
}
```


---

## 作者：oddy (赞：0)

## 题意解释

有 $n$ 个人和 $m$ 组朋友关系，朋友的朋友也是朋友。求人数最多的朋友圈有多少个人。

## 解题思路

考虑使用并查集。这个题目等价于给定若干次合并操作，最后求最大的集合的元素个数。所以我们在并查集的基础上再加一个 $g_i$ 表示以 $i$ 为根节点的集合的元素个数。

Tip：合并集合前必须判断两个结点是否不属于同一个集合，否则会因为把元素个数加了两遍而导致答案错误。

```cpp
#include <cstdio>
#include <algorithm>

int t, n, m, x, y, f[30005], g[30005];

int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

int main() {
    for(scanf("%d", &t); t; --t) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; i++) f[i] = i, g[i] = 1;
        while(m--) {
            scanf("%d%d", &x, &y), x = find(x), y = find(y);
            if(x != y) // 按照集合内的元素个数合并
                if(g[x] > g[y]) g[x] += g[y], f[y] = f[x];
                else g[y] += g[x], f[x] = f[y];
        }
        printf("%d\n", *std::max_element(g+1, g+n+1));
    }

    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

[UVA10608 Friends](https://www.luogu.com.cn/problem/UVA10608)

### 题意

有 $N$ 个人，其中有 $M$ 对朋友，且满足朋友的朋友也是朋友，求最多有多少人相互都是朋友？（也就是最大的朋友圈）

注意有多组数据。

### 做法

根据“朋友的朋友也是朋友”这句话，可以得知此题中的朋友关系具有传递性。

每一对朋友之间可以抽象成一条边，所有人之间的关系看作一个无向图，则最大的一个朋友圈便是图中的最大连通块。

于是我们可以考虑用并查集求解。

每次添加关系时将两个人的信息合并到一起，即将其中一人的“祖先”设为另一人的“祖先”。合并完后对所有“祖先”的人数进行累加，再判断最大值。

注意每个人一开始的“祖先”要初始化为自己。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define re register
#define N 114514
#define M 1919180
ll t,n,m;
ll x,y;
ll f[N],ans[N],total;
ll find(ll x){
	return x==f[x]?x:find(f[x]);  //查找祖先 
}
void hebing(ll x,ll y){
	f[find(x)]=find(y);    //合并操作 
}
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		total=-114514;  //答案因为要取max，所以要初始化为负数 
		for(int i=1;i<=n;i++) ans[i]=0,f[i]=i; //ans数组清空，每个人祖先初始化为自己 
		for(int i=1;i<=m;i++){
			cin>>x>>y;
			hebing(x,y);
		}
		for(int i=1;i<=n;i++) ans[find(i)]++;
		for(int i=1;i<=n;i++) total=max(total,ans[i]);
		cout<<total<<endl;
	}
	return 0;
} 
```


---

## 作者：rai1gun (赞：0)

### 1.题目思路

本题的大致意思是给你 $n$ 个集合，合并完元素最多的那个集合中有多少个数。

不难想到使用并查集维护。

并查集是一个以森林来维护的集合，如果同时做了路径压缩和按秩合并复杂度可以降到 $O(\alpha(n))$，当然，一般题只需要使用路径压缩即可。

### 2.题目代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
int fa[N],h[N],T;
inline int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int main(){
	cin>>T;
	while(T--){
		int n,m;
		cin>>n>>m;
		memset(h,0,sizeof(h));
		for(int i=1;i<=n;i++) fa[i]=i;
		while(m--){
			int x,y;
			cin>>x>>y;
			fa[find(x)]=find(y);
		}
		for(int i=1;i<=n;i++)h[find(i)]++;
		int ans=-1;
		for(int i=1;i<=n;i++) ans=max(ans,h[i]);
		cout<<ans<<endl;
	}
	return 0;
}

```

---

## 作者：charleshe (赞：0)

把每位公民看作点，朋友关系为边，题目意思便被我们转化成了：

有一个 $N$ 个点 $M$ 条边的无向图，求其中最大连通块中点的数量。

可以直接考虑并查集。

并查集，顾名思义，它需要实现并和查的功能。

并，指的是将两个点所在的连通块合并，而查，指的是判断两点是否在一个连通块里。对于这题，我们只需要实现并的功能。

为了方便查找，并查集均用父亲节点存储法，每个节点指向它所连边的上一个节点。

如何将两个点所在的连通块合并呢？按照我们的理解，是不是给出两个点，在这两个点中间连一条线，就能合并了呢？当然不。当你直接连边时，你连的两个边的父亲级别的节点均不会认为存在加边，而且加边后也不好处理两个边的父亲节点数组。

根据第一个出现的问题，可以发现我们要用没有父节点的点来进行连边。因此，可以发现另一种选择：对两个点的最老祖宗节点进行连边。

那么，我们就需要实现寻找最老祖宗节点和连边的程序。

求最老祖宗节点：

```cpp
int find(int x){//寻找点x的祖先
	if(x==f[x]) return x;//如果点x的祖先是自己，说明x就是最老祖宗节点，返回x。
	return f[x]=find(f[x]);//否则，递归其父亲节点
}
```
连边：

```cpp
void add(int x,int y){//连边
	f[find(x)]=find(y);//对两个点的最老祖宗进行连边。此处默认把y的祖先连到x上。
}
```
并的问题解决了，对于其他部分，设一个数组，把一个连通块的所有点的数量存在其最老祖宗节点在数组中的对应位置，再求最大值，本题便做完了。

注意事项：

- 本题是**多组数据**！不要用单个数据的做法来做本题。

- 初始时要将每个点的父亲节点设为自己，这代表一个点的父亲节点仍是自己，即途中没有边。之后再根据输入逐个加边。

- 对于每一个数据，存连通块点数量的数组都要归零，以免出现奇怪的 WA。

考虑了这些，代码就好写了。

```cpp
#include <iostream>
using namespace std;
int f[30003],fr[30003];
int n,m,t,a,b;
int find(int x){//查找祖先
	if(x==f[x]) return x;
	return f[x]=find(f[x]);
}
void add(int x,int y){//连边
	f[find(x)]=find(y);
}
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			f[i]=i;
			fr[i]=0;//这里是初始化。
		}
		for(int i=1;i<=m;i++){
			cin>>a>>b;
			add(a,b);
		}
		for(int i=1;i<=n;i++){
			fr[find(i)]++;//存节点数量
		}
		int maxnum=-1;
		for(int i=1;i<=n;i++){
			if(maxnum<fr[i]){
				maxnum=fr[i];//找节点最多的连通块的节点数量
			}
		}
		cout<<maxnum<<endl;
	}
	return 0;
}
```
附录：

这是一道并查集题目，对并查集感兴趣的同学可以再去做一下下面几题：

[P1551 亲戚](https://www.luogu.com.cn/problem/P1551)；

[P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)；

[UVA10583 Ubiquitous Religions](https://www.luogu.com.cn/problem/UVA10583)。

都是比较基础的并查集题目，但都要涉及到查的功能，可以翻看一下题解，里面有较详细的对并查集的讲解。

---

## 作者：Unnamed114514 (赞：0)

## 前置知识
[并查集](https://blog.csdn.net/qq_31965925/article/details/106265355)，是用一个森林来维护的集合，其特点为合并速度极快，查询效率较高，空间消耗比较小。
## 题意
求最大联通块的节点数。
## 分析
想到联通，我们可以使用并查集，每次多一条边的时候就合并两个集合，最后求那个节点的人数最多即可。简单好打，时间复杂度 $O(tm)$，空间 $O(n)$。虽然比 bfs 慢，但还是可以过。
## AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e4+5;
inline int read(){
	int res=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
		ch=getchar();
	while(ch>='0'&&ch<='9'){
		res=(res<<1)+(res<<3)+(ch^'0');
		ch=getchar();
	}
	return res;
}
int father[maxn],rk[maxn],n,m,t=read(),ans;//rk维护人数
inline int findSet(int x){
	return father[x]=(father[x]==x?x:findSet(father[x]));
}
inline void unionSet(int a,int b){
	father[a]=b;
	rk[b]+=rk[a];
}//合并
int main(){
	for(int j=1;j<=t;++j){//多测
		ans=0;
		n=read(),m=read();
		for(int i=1;i<=n;++i)
			father[i]=i,rk[i]=1;
		for(int i=1;i<=m;++i){
			int x=findSet(read()),y=findSet(read());
			if(x!=y)
				unionSet(x,y);
		}
		for(int i=1;i<=n;++i)
			ans=max(ans,rk[i]);	
		printf("%d\n",ans);
	}
	return 0;
} 
```

---

