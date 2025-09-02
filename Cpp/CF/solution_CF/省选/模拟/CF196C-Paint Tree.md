# Paint Tree

## 题目描述

给你一棵$n$个点的树和$n$个平面直角坐标系上的点，现在要把树上的$n$个点映射到坐标系中的$n$个点上。要求是除了在顶点处不能有线段相交。

## 样例 #1

### 输入

```
3
1 3
2 3
0 0
1 1
2 0
```

### 输出

```
1 3 2
```

## 样例 #2

### 输入

```
4
1 2
2 3
1 4
-1 -2
3 5
-3 3
2 0
```

### 输出

```
4 2 1 3
```

# 题解

## 作者：shiroi (赞：4)


### Description

给定一棵 $n$ 个点的无根树和平面上的 $n$ 个点，求出任意一个映射使得这些点能够一一对应，同时除了在顶点处不允许线段交叉。

题目保证不存在三点共线。

### Solution

观察题目发现，如果需要让平面上的连边不相交，那么无根树上一棵子树对应的坐标区间都不能与其他子树对应的坐标区间相交，可以考虑转化为对于每棵子树分配合法的点来满足条件。

由于不存在三点共线，我们可以考虑利用极角排序的性质分治解决问题。

每次分治到一个子树对应的坐标区间，把区间范围内左下角的点作为子树的根对应的点，以此为基准对剩下的点极角排序。对于一个点的儿子，则在区间内划分一段大小为其子树大小的子区间进行递归，对于每一棵子树直接分配其子树大小个点。

题目保证不存在三点共线，因此解一定存在。总的时间复杂度为 $O(n^2 \log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
    int x=0,f=1,c=getchar();
    while(c<48) c=='-'&&(f=-1),c=getchar();
    while(c>47) x=x*10+c-'0',c=getchar();
    return x*f;
}

typedef long long ll;
const int MAXN = 2005;
struct Point {ll x,y,id;} p[MAXN],tmp;
std::vector<int> G[MAXN];
ll size[MAXN],ans[MAXN];
ll n;

inline void addedge(int u,int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}

inline bool cmp(Point a,Point b)
{
    ll ax=a.x-tmp.x,ay=a.y-tmp.y;
    ll bx=b.x-tmp.x,by=b.y-tmp.y;
    if(ax>=0 && bx<=0) return 1;
    if(ax<=0 && bx>=0) return 0;
    return ax*by>ay*bx;
}

void dfs(int x,int fa)
{
    size[x]=1;
    for(int &y : G[x])
    {
        if(y==fa) continue;
        dfs(y,x); size[x]+=size[y];
    }
}

void sol(ll l,ll r,ll x,ll fa)
{
    ll cur=l;
    for(ll i=l+1; i<=r; i++)
        if(p[i].x<p[cur].x||
                (p[i].x==p[cur].x&&p[i].y<p[cur].y))cur=i;
    swap(p[l],p[cur]);
    tmp=p[l]; ans[p[l].id]=x;
    sort(p+l+1,p+r+1,cmp);
    ll now=l+1;
    for(int &y : G[x])
    {
        if(y==fa) continue;
        sol(now,now+size[y]-1,y,x);
        now+=size[y];
    }
}

int main(int argc, char const *argv[])
{
    n=read();
    for(int i=1; i<n; ++i)
        addedge(read(),read());
    ll x,y,w;
    for(int i=1; i<=n; ++i)
    {
        x=read(); y=read();
        p[i]=(Point) {x,y,i};
    }
    dfs(1,0); sol(1,n,1,0);
    for(ll i=1; i<=n; i++)
        printf("%lld%c",ans[i]," \n"[i==n]);
    return 0;
}
```





---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2200}$
---
学了极坐标系之后或许会更容易想到？

---
### 解题思路：

首先处理一下给出的树，任选一个点作为根节点，然后进行一个 $\text{DFS}$，计算出以某一个点为根的子树大小。

然后考虑分治，将一些点划分给树上的一个子树进行分配。找出最左边的一个点作为根节点，然后将区间内的所有点按照极角排序。按照顺序依次划分给各个子树递归下去即可。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
const int MAXN=3005;
struct str{
	int x,y,id;
}p[MAXN],tmp;
int n,head[MAXN],nxt[MAXN],num[MAXN],tot,u,v,size[MAXN],cur,ans[MAXN];
bool cmd(str a,str b){
	int ax=a.x-tmp.x;
	int ay=a.y-tmp.y;
	
	int bx=b.x-tmp.x;
	int by=b.y-tmp.y;
	
	return ax*by>ay*bx;
}
void add(int x,int y){
	nxt[++tot]=head[x];
	head[x]=tot;
	num[tot]=y;
}
void dfs(int now,int fa){
	for(int i=head[now];i;i=nxt[i]){
		if(num[i]!=fa){
			dfs(num[i],now);
			size[now]+=size[num[i]];
		}
	}
	size[now]++;
	return;
}
void work(int now,int l,int r,int fa){
	cur=l;
	for(int i=l+1;i<=r;i++){
		if(p[i].x<p[cur].x)
		swap(p[i],p[cur]);
		else 
		if(p[i].y<p[cur].y&&p[i].x==p[cur].x)swap(p[i],p[cur]);
	}
	tmp=p[cur];
	sort(p+l+1,p+r+1,cmd);
	ans[p[cur].id]=now;
	int x=cur+1;
	for(int i=head[now];i;i=nxt[i]){
		if(num[i]==fa)continue;
		work(num[i],x,x+size[num[i]]-1,now);
		x+=size[num[i]];
	}
}
signed main(){
	scanf("%I64d",&n);
	for(int i=1;i<n;i++){
		scanf("%I64d%I64d",&u,&v);
		add(u,v);add(v,u);
	}
	for(int i=1;i<=n;i++){
		scanf("%I64d%I64d",&p[i].x,&p[i].y);
		p[i].id=i;
	}
	dfs(1,1);
	work(1,1,n,1);
	for(int i=1;i<=n;i++)
	printf("%I64d ",ans[i]);
	printf("\n");
	return 0;
}
```


---

