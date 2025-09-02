# Daleks' Invasion (easy)

## 题目描述

Heidi found out that the Daleks have created a network of bidirectional Time Corridors connecting different destinations (at different times!). She suspects that they are planning another invasion on the entire Space and Time. In order to counter the invasion, she plans to deploy a trap in the Time Vortex, along a carefully chosen Time Corridor. She knows that tinkering with the Time Vortex is dangerous, so she consulted the Doctor on how to proceed. She has learned the following:

- Different Time Corridors require different amounts of energy to keep stable.
- Daleks are unlikely to use all corridors in their invasion. They will pick a set of Corridors that requires the smallest total energy to maintain, yet still makes (time) travel possible between any two destinations (for those in the know: they will use a minimum spanning tree).
- Setting the trap may modify the energy required to keep the Corridor stable.

Heidi decided to carry out a field test and deploy one trap, placing it along the first Corridor. But she needs to know whether the Daleks are going to use this corridor after the deployment of the trap.

She gives you a map of Time Corridors (an undirected graph) with energy requirements for each Corridor.

For a Corridor $ c $ , $ E_{max}(c) $ is the largest $ e \le 10^9 $ such that if we changed the required amount of energy of $ c $ to $ e $ , then the Daleks may still be using $ c $ in their invasion (that is, it belongs to some minimum spanning tree). Your task is to calculate $ E_{max}(c_1) $ for the Corridor $ c_1 $ that Heidi plans to arm with a trap, which is the first edge in the graph.

## 说明/提示

After the trap is set, the new energy requirement for the first Corridor may be either smaller, larger, or equal to the old energy requiremenet.

In the example, if the energy of the first Corridor is set to $ 4 $ or less, then the Daleks may use the set of Corridors $ \{ \{ 1,2 \}, \{ 2,3 \} \} $ (in particular, if it were set to less than $ 4 $ , then this would be the only set of Corridors that they would use). However, if it is larger than $ 4 $ , then they will instead use the set $ \{ \{2,3\}, \{3,1\} \} $ .

## 样例 #1

### 输入

```
3 3
1 2 8
2 3 3
3 1 4
```

### 输出

```
4
```

# 题解

## 作者：water_tomato (赞：5)

## 题意
见[题干](https://www.luogu.com.cn/problem/CF1184E1)，easy version 中要求的是将第一条边最大修改为多少能够使其存在在最小生成树中。
## 解析
题目与最小生成树相关，又要值尽可能大，很容易想到 kruskal 算法，因为该算法是先将权值小的边加入到最小生成树中的，因此，我们希望第一条边能够**尽可能晚**的加入到最小生成树中，这样才能使其权值最大。

考虑到要使其尽可能晚加入而且不能不加入，因此我们希望在第一条边的两点联通之前连接尽可能多的边，如果一条边连接后，第一条边的两点被联通了，显然第一条边就无法加入到最小生成树中了，因此我们需要在这个**刚好被联通**的临界点加入第一条边，即将第一条边的权值修改为临界边的权值（题目要求**可能**出现，因此可以等于临界边的权值，即直接赋值）。

我们又考虑到，可能存在第一条边为**割边**，即第一条边如果不加入到最小生成树中，其他边就无法构成最小生成树的情况，也就是在第一条边不遍历的情况下， $cnt$ 无法等于 $n-1$ ，此时将第一条边的值赋为最大,即题面所述的 $10^9$ 即可。

而我们将该思想进行代码实现时，只需要忽略第一条边，让其他边正常跑 kruskal 即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 1000005
using namespace std;
int n,m,fa[N],cnt;
struct edge{
	int u,v,val;
}e[N];
inline int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
inline bool cmp(edge i,edge j){
	return i.val<j.val;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].val);
	}
	for(int i=1;i<=n;i++)
		fa[i]=i;
	sort(e+2,e+1+m,cmp);//忽略第一条边跑 kruskal 
	for(int i=2;i<=m&&cnt<n-1;i++){
		int u=e[i].u,v=e[i].v;
		if(find(u)==find(v)) continue;
		fa[find(u)]=find(v);
		cnt++;
		if(find(e[1].u)==find(e[1].v)){
			printf("%d\n",e[i].val);
			return 0;
		}	
	}
	if(cnt<n-1){//如果是割边 
		cout<<(int)1e9;
	}
	return 0;
}
```


---

## 作者：优秀的渣渣禹 (赞：1)

题目大意：

给出$n$个点$m$条边的无向图，你可以修改第一条边的权值，使得他可能会处于一棵最小生成树中，问你第一条的权值最大（不超过1e9)可以改为多少。

这个题我们不去使用第一条边去跑最小生成树，然后在跑的过程中，有一条边连接的两个联通分量与第一条连接是一样的，那么答案就是这条边的权值

如果最后没办法联通，说明第一条边是割边，答案是1e9。

```cpp
#define B cout << "BreakPoint" << endl;
#define O(x) cout << #x << " " << x << endl;
#define O_(x) cout << #x << " " << x << " ";
#define Msz(x) cout << "Sizeof " << #x << " " << sizeof(x)/1024/1024 << " MB" << endl;
#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<set>
#define fi first
#define se second
#define LL long long
const int inf = 1e9 + 9;
const int N = 2e6 + 5;
using namespace std;
inline int read() {
	int s = 0,w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-')
			w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * w;
}
int fa[N];
int find(int x){
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
vector<pair<int,pair<int,int> > > e(N);
int main(){
    int n = read(),m = read();
    for(int i = 0;i < m;i++){
        e[i].se.fi = read();
		e[i].se.se = read();
		e[i].fi = read();
    }  
    sort(e.begin() + 1,e.end());
    for(int i = 1;i <= n + 5;i++) fa[i] = i;
    for(int i = 1;i < e.size();i++){
        int u = find(e[i].se.fi),v = find(e[i].se.se);
        if(u != v){
            int x = find(e[0].se.fi),y = find(e[0].se.se);
            if(x == u && y == v) printf("%d\n",e[i].fi),exit(0);
            if(x == v && y == u) printf("%d\n",e[i].fi),exit(0);
            fa[u] = v;
        }
    }
    printf("%d\n",(int)1e9);
}
```

---

## 作者：No21 (赞：0)

### 解题思路

很不错的一道题，有助于理解求最小生成树的过程和 Kruscal 算法的本质。

我们考虑 Kruscal 求最小生成树的过程，首先将边从小到大处理，对于每条边，如果它连接的两个集合是不连通的，那么就以这条边连通它。那么我们考虑，第一条边能进入最小生成树，当且仅当没有任何比它边权更小的边可以连接它连接的两个集合，那么我们只需要在求最小生成树的同时，找到除了第一条边外，连接第一条边连接的两个集合的权值最小的边，然后将第一条边的边权设为找到的这条边的边权即可（可以结合上面的结论验证一下，因为比较显然，这里就不证明了）。

特别的，如果除了第一条边，没有任何一条边可以连接第一条边连接的两个集合（即第一条边是割边），那么代表第一条边的取值可以是任意的。

```
#include<bits/stdc++.h>
using namespace std;
namespace TO
{
    const int N=1e5+21,M=1e6+21;
    int n,m;
    int fa[N];
    struct edge
    {
        int to,from,val;
    }e[M];
    bool cmp(edge x,edge y)
    {
        return x.val<y.val;
    }
    int find(int x)
    {
        if(x==fa[x])
            return x;
        return fa[x]=find(fa[x]);
    }
    void krus()
    {
        for(int i=2;i<=m;i++)
        {
            int x=find(e[i].from),y=find(e[i].to);
            if(x!=y)
            {
                fa[x]=y;
                if(find(e[1].from)==find(e[1].to))
                {
                    cout<<e[i].val<<'\n';
                    exit(0);
                }
            }
        }
    }
    int mian()
    {
        cin>>n>>m;
        for(int i=1;i<=n;i++)
            fa[i]=i;
        for(int i=1;i<=m;i++)
            cin>>e[i].from>>e[i].to>>e[i].val;
        sort(e+2,e+1+m,cmp);
        krus();
        cout<<(int)1e9<<'\n';
        return 0;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    return TO::mian();
}
```

---

## 作者：封禁用户 (赞：0)

观察 $\text{Kruskal}$ 算法。

- 一条边的作用在于合并每两个森林，直到整张图形成一棵树。假设 $1$ 号边为非树边，那么存在一条树边在构成树中的作用等价，但是树边的权值较小，我们只需要让 $1$ 号边的权值与这条树边一样大。

- 树是连通的，如果一条边是割边，那么必须选择它，也就是说，这条边无论权值多大都可以。显然，当 $1$ 号边为割边时，一定是树边。

做法是：

去掉 $1$ 号边，跑 $\text{Kruskal}$ 算法，对于加边的每一时刻，检查 $1$ 号边所连接的两侧森林情况，如果被合并为一颗森林，输出刚加的那条边的边权，原因上面解释过了。

对于 $1$ 号边为割边的情况，去掉它的图没有生成树，特判即可。

---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1184E1)

比较有趣的思维题。

题目要求最小生成树**可能**包含第一条边 $(u,v)$ 时，第一条边的最大长度。

考虑 Kruskal 算法的实现流程是不断添加最小的边，那么最小生成树中包含第一条边的充要条件就是第一条边的长度 $\le$ 最小生成树中最长边的长度。

但是考虑如果连边的时候把 $(u,v)$ 连通了，那第一条边就没有意义了。所以当 $(u,v)$ 联通时，第一条边应该更新成当前生成树中的最长边。

所以实现就是抛开第一条边，对剩下的边跑 Kruskal，当 $(u,v)$ 联通时输出此时生成树中最长边的长度。

额外地，如果抛开第一条边后无法构成生成树，那么第一条边长度为最大值 $10^9$。

时间复杂度 $O(m log m)$。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define back return
#define ri register int
using namespace std;
ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	back x*f;
}
ll n,m,cnt,maxx=-1,fa[100005];
struct node
{
	ll x,y,w;
}a[1000005];
ll find(ll x)
{
	if(fa[x]==x)
		back x;
	back fa[x]=find(fa[x]);
}
bool cmp(node a,node b)
{
	back a.w<b.w;
}
int main()
{
	n=read(),m=read();
	for(ri i=1;i<=n;i++)
		fa[i]=i;
	for(ri i=1;i<=m;i++)
		a[i].x=read(),a[i].y=read(),a[i].w=read();
	sort(a+2,a+m+1,cmp);
	for(ri i=2;i<=m;i++)
	{
		if(find(a[i].x)==find(a[i].y))
			continue;
		else
		{
			fa[find(a[i].x)]=find(a[i].y);
			cnt++;
			maxx=max(maxx,a[i].w);
			if(find(a[1].x)==find(a[1].y))
			{
				cout<<maxx<<"\n";
				back 0;
			}

		}
	}
	if(cnt<n-1)
		cout<<1000000000<<"\n";
	back 0;
}
```

---

## 作者：mot1ve (赞：0)

二分极限卡过。

我们可以二分第一条边的值，时间复杂度 $O(mlogmlogn)$ ，此题时限6s，刚好卡过。

然后此题思维难度就为0了，值得一提的是，由于最小生成树中可能会出现一条和第一条边相等的边，所以我们需要在排序的时候让第一条边优先出现于其他和他相等的值的边。这样才能保证最优。

```
#include<bits/stdc++.h>
using namespace std;
int n,m,l,r,mid,ans,idx;
int fa[1000010],vis[1000010],temp[1000010];
struct node{
	int u,v,w,id;
}edge[1000010],edge2[1000010];
bool cmp(node a,node b)
{
	if(a.w!=b.w) return a.w<b.w;
	return a.id<b.id;//让1先出现 
}
int find(int x)
{
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]); 
}
bool check(int x)//nlogn
{
	for(int i=1;i<=n;i++)
	{
		fa[i]=i;
	}
	for(int i=1;i<=idx;i++)
	{
		edge2[i].id=edge[i].id;
		edge2[i].u=edge[i].u;
		edge2[i].v=edge[i].v;
		edge2[i].w=edge[i].w;
	}
	edge2[1].w=x;
	sort(edge2+1,edge2+1+idx,cmp);
	for(int i=1;i<=idx;i++)
	{
		int f1=find(edge2[i].u);
		int f2=find(edge2[i].v);
		if(f1==f2)
		continue;
		fa[f2]=f1;
		vis[edge2[i].id]=1;
	}
	if(vis[1]==1) return 1;
	else return 0;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		edge[++idx].u=u;
		edge[idx].v=v;
		edge[idx].w=w;
		edge[idx].id=i;//第几条边 
	}
	l=0,r=1e9;
	while(l<=r)
	{
		vis[1]=0;
		int mid=(l+r)>>1;
		if(check(mid))
		{
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	cout<<ans<<endl;
	return 0;
}

---

## 作者：rouxQ (赞：0)

kruskal 好题
## 题意
给一个无向图，希望修改第一条边的边权，使得第一条边可以包含在该图的最小生成树中，最大化该边权。
## $\operatorname{Sol}$
我们考虑 kruskal 的实现过程，若什么时候不需要将第一条边加入最小生成树了，则第一条边连接的两点必定已经联通。换言之，假设第一条边为 $(u_1,v_1,w_1)$，在加入边 $(u_i,v_i,w_i)$ 后 $u_1$ 和 $v_1$ 已经联通，则连接边 $(u_1,v_1,w_1)$ **必须抢在连接边 $(u_i,v_i,w_i)$ 前进行。** 

那么我们便有了一个简单的做法：先忽略第一条边跑 kruskal，在跑的过程中每连接一条边，便判断第一条边连接的两个点是否联通，若联通，则答案即为最后连接的边的边权。特别地，若算法结束后还未联通（即第一条边为割边），将其赋为无穷大即可（本题中为 $10^9$）。

## $\operatorname{Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5, M = 1e6 + 5;
struct edge{int u, v, w;}e[M];
bool cmp(edge x, edge y){return x.w < y.w;}
int fa[N];
int find(int k){return k == fa[k] ? k : fa[k] = find(fa[k]);}
int main (){
    int n, m;
    scanf("%d%d", &n, &m);
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);//事先把第一条边拎出来
    for (int i = 1; i < m; i++)scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
    sort(e + 1, e + m, cmp);
    for (int i = 1; i <= n; i++)fa[i] = i;
    int sum = 0, ans = 1e9;
    for (int i = 1; i < m; i++){
        int uf = find(e[i].u), vf = find(e[i].v);
        if (uf != vf){
            fa[uf] = vf;
            sum++;
            if (find(a) == find(b)){//若连接了一条边后发现
                ans = e[i].w;//       第一条边连接的两个点已联通
                break;
            }
            if (sum == n - 1)break;
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

