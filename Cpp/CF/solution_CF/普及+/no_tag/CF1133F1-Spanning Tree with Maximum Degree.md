# Spanning Tree with Maximum Degree

## 题目描述

You are given an undirected unweighted connected graph consisting of $ n $ vertices and $ m $ edges. It is guaranteed that there are no self-loops or multiple edges in the given graph.

Your task is to find any spanning tree of this graph such that the maximum degree over all vertices is maximum possible. Recall that the degree of a vertex is the number of edges incident to it.

## 说明/提示

Picture corresponding to the first example: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1133F1/679cb38fe66138eb41c68a27752c7ba6f50631eb.png)

In this example the number of edges of spanning tree incident to the vertex $ 3 $ is $ 3 $ . It is the maximum degree over all vertices of the spanning tree. It is easy to see that we cannot obtain a better answer.

Picture corresponding to the second example: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1133F1/3901be7d0b3c499456efcd32ad4bf53709c399cf.png)

In this example the number of edges of spanning tree incident to the vertex $ 1 $ is $ 3 $ . It is the maximum degree over all vertices of the spanning tree. It is easy to see that we cannot obtain a better answer.

Picture corresponding to the third example: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1133F1/4fb66d4828c313ca8131754e22e661e238cfd944.png)

In this example the number of edges of spanning tree incident to the vertex $ 2 $ is $ 4 $ . It is the maximum degree over all vertices of the spanning tree. It is easy to see that we cannot obtain a better answer. But because this example is symmetric, we can choose almost the same spanning tree but with vertex $ 5 $ instead of $ 2 $ .

## 样例 #1

### 输入

```
5 5
1 2
2 3
3 5
4 3
1 5
```

### 输出

```
3 5
2 1
3 2
3 4
```

## 样例 #2

### 输入

```
4 6
1 2
1 3
1 4
2 3
2 4
3 4
```

### 输出

```
4 1
1 2
1 3
```

## 样例 #3

### 输入

```
8 9
1 2
2 3
2 5
1 6
3 4
6 5
4 5
2 7
5 8
```

### 输出

```
3 2
2 5
8 5
6 1
2 7
1 2
3 4
```

# 题解

## 作者：lw21144 (赞：2)

## CF1133F1 Spanning Tree with Maximum Degree

[题目传送门](https://www.luogu.com.cn/problem/CF1133F1)

考虑到整个图中没有自环和重边，并且生成树只考虑最大度数尽可能大，因此我们可以先找出度数最大的点 $num$，然后选出和 $num$ 相连的所有点，再通过 bfs 搜到所有的点即可。时间复杂度 $O(m)$

具体细节见代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf=1145141919810<<20; //inf=1e18
const char FILE_IN[]="*.in",FILE_OUT[]="*.out";
int n,m,tot,s[200005],vis[200005],head[200005],to[400005],nxt[400005];
inline void Fre_open(){
	freopen(FILE_IN,"r",stdin);
	freopen(FILE_OUT,"w",stdout);
}
queue<int>q;
namespace Fast_Read_and_Write{
	inline int read(){ // 快读快写
		int cnt=1,h=0; char ch=getchar();
		while(ch<'0'||ch>'9') cnt=(ch=='-')?-1:1,ch=getchar();
		while(ch>='0'&&ch<='9') h=h*10+(ch^48),ch=getchar();
		return h*cnt;
	}
	inline void write(int x){
		if(x<0) putchar('-'),x=-x;
		x>9?write(x/10),putchar((x%10)^48):putchar((x%10)^48);
	}
}
using namespace Fast_Read_and_Write;
inline void print(int u,int v){ // 输出一条边
	write(u),putchar(32),write(v),putchar('\n');
}
inline void add(int u,int v){ // 链式前向星连边
	to[++tot]=v,nxt[tot]=head[u],head[u]=tot;
}
signed main(){
	// Fre_open();
	n=read(),m=read();
	memset(head,-1,sizeof(head));
	for(int i=1,x,y;i<=m;i++){ // 读入边并记录
		x=read(),y=read(),add(x,y),add(y,x),s[x]++,s[y]++;
	}
	int num=0,maxd=0;
	for(int i=1;i<=n;i++){ // 找图中度数最大的点 
		if(maxd<s[i]) maxd=s[i],num=i;
	}
	vis[num]=1,q.push(num);
	while(!q.empty()){ // bfs 搜索
		register int u=q.front(); q.pop();
		for(register int i=head[u];i!=-1;i=nxt[i]){
			register int v=to[i]; if(vis[v]) continue;
			print(u,v),vis[v]=1,q.push(v); //继续拓展节点
		}
	}
	return 0;
} 
```

通过记录[点这里](https://www.luogu.com.cn/record/122386364)，最大耗时点 $358$ ms。

---

## 作者：Li_Yichen (赞：1)

简单题。寻找连通图和生成树之间的关系，要求求的是生成树中最大度数里最大，我们只需在输入的过程中统计度数，选择最大的点，然后以这个点为根节点。考虑维护并查集，根据贪心的思想，先输出和这个点所连接的边，把左右端点合并，但这样不能保证所有点的连通性。因此枚举每一条边，只要左右端点不连通，输出这条边，把两个点合并即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int u[200005],v[200005];
int d[200005];
int pos,maxn=-1e9;
int father[200005];
void init(){
    for(int i=1;i<=n;i++){
        father[i] = i;
    }
}
int find(int x){
    if(father[x] == x) return x;
    return father[x] = find(father[x]);
}
int merge(int x,int y){
    int u = find(x);
    int v = find(y);
    if(u != v) father[u] = v;
}
int main(){
    cin >> n >> m;
    init();
    for(int i=1;i<=m;i++){
        cin >> u[i] >> v[i];
        d[u[i]] ++;
        d[v[i]] ++;
    }
    for(int i=1;i<=n;i++){
        if(maxn < d[i]){
            maxn = d[i];
            pos = i;
        }
    }
    for(int i=1;i<=m;i++){
        if(u[i] == pos || v[i] == pos){
            cout << u[i] << " " << v[i] << endl;
            merge(u[i],v[i]);
        }
    }
    for(int i=1;i<=m;i++){
        if(find(u[i]) != find(v[i])){
            cout << u[i] << " " << v[i] << endl;
            merge(u[i],v[i]);
        }
    }
    return 0;
}
```

---

## 作者：OIerZhang (赞：0)

# [CF1133F1 Spanning Tree with Maximum Degree](https://www.luogu.com.cn/problem/CF1133F1)

题外话：~~居然有这么水的绿题~~

## 思路

要使得树中度数最大的顶点的度数尽可能大，最大的最大，一眼定贪心。

要问度数最大的顶点，那么肯定是和其他顶点无关的。所以第一步就是把度数最大的顶点挑出来。

这样度数最大的顶点的度数就最大了（这话有点拗口），我们只需要把和这个顶点相连的边加入生成树就 OK 了。

至于剩下的，就挑一些加入进去就行了，前提是不能有环。

至于如何判环，看楼上犇犇用 BFS，所以我用了更好用的并查集的方法。通过并查集判断两个顶点 $u_i,v_i$ 是否在一个集合，如果是，那么它们将会形成一个环，反之则不会。

## 代码

并查集经典模板：

```cpp
int fa[200005];

int find(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = find(fa[x]); // 路径压缩
}

void merge(int x,int y)
{
    int u = find(x);
    int v = find(y);
    if(u != v)
        fa[u] = v;
}

void init()
{
    for (int i = 1; i <= n; i++)
        fa[i] = i;
}
```

核心代码：
```cpp
for (int i = 1; i <= m; i++)
{
    cin >> u[i] >> v[i];
    d[u[i]]++;
    d[v[i]]++;
}
for (int i = 1; i <= n; i++)
    if (mx < d[i])
        mx = d[i], pos = i; // 挑度数最大的顶点
for (int i = 1; i <= m; i++)
{
    if (u[i] == pos || v[i] == pos) // 把和这个顶点相连的边加入生成树
    {
        cout << u[i] << ' ' << v[i] << endl;
        merge(u[i], v[i]);
    }
}
for (int i = 1; i <= m; i++)
{
    if (find(u[i]) != find(v[i])) // 并查集判环
    {
        cout << u[i] << ' ' << v[i] << endl; // 保证没有环的情况下任选边加入生成树
        merge(u[i], v[i]);
    }
}
```

~~再给完整代码就没意思了，请各位自行脑补~~

> 珍爱账号，远离抄袭。

---

## 作者：Frozen_Ladybug (赞：0)

先解释一下题：本题所求的是使最大的度数尽可能大的生成树，从已给的边中选边和点。

我们可以使用并查集，再用贪心维护。我们取原图中度数最大的节点和它的所有边；在保证是树的情况下任意加边。判定是否为树可以用并查集维护。

我们要求的是度数最大值最大，而不是度数之和最大。可以取原图中度数最大的点（在所有生成树中一定最大），在把它所有的邻边都加入生成树，保证无环的情况下任选边即可（多个点任选其一，因为有特判）。

这样我们就不需要把整个图建出来，代码如下。

```c
#include<bits/stdc++.h>
using namespace std;
int n,m,u[200005],v[200005],c[200005],fa[200005],rt;
//全程不建图,任意可行的解都判定为对
int findfa(int x){
    if(fa[x]==x) return x;
    return fa[x]=findfa(fa[x]);
}//找祖先
void unite(int x,int y){
    int fax=findfa(x),fay=findfa(y);
    if(fax!=fay) fa[fax]=fay;
}//合并节点
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u[i],&v[i]);
        c[u[i]]++,c[v[i]]++;
    }//输入,c数组记录每个点的出度
    for(int i=1;i<=n;i++) if(c[i]>c[rt]) rt=i;
    //我们取所有出度中最大的点作为树根,往下搜索
    for(int i=1;i<=n;i++) fa[i]=i;//每个点的祖先初始化为自己
    for(int i=1;i<=m;i++)//再依次搜索每一条边
        if(u[i]==rt||v[i]==rt){
            printf("%d %d\n",u[i],v[i]);
            unite(u[i],v[i]);
        }//如果入度或出度与根节点连接,就输出并合并
    for(int i=1;i<=m;i++)
        if(findfa(u[i])!=findfa(v[i])){
            printf("%d %d\n",u[i],v[i]);
            unite(u[i],v[i]);
        }//如果两个点的祖先不一样,就输出,并(贪心思维)合并
    return 0;
}
```


---

## 作者：nynkqh_yzp (赞：0)

因为图中没有自环或重边，所以如果一个点的度是最大的，那么肯定会把与它相关的边全部选上。

所以直接枚举。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,f[200001],l[200001],r[200001],an,ans;
int zbb(int x){
	if(f[x]==x)
		return x;
	f[x]=zbb(f[x]);
	return f[x];
}
vector<int>a[200001];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d %d",&l[i],&r[i]);
		a[l[i]].push_back(r[i]);
		a[r[i]].push_back(l[i]);
	}
	an=a[1].size();
	ans=1;
	for(int i=2;i<=n;i++){
		f[i]=i;
		if(a[i].size()>an){
			an=a[i].size();
			ans=i;
		}
	}
	for(int i=0;i<a[ans].size();i++){
		f[zbb(a[ans][i])]=zbb(ans);
		printf("%d %d\n",a[ans][i],ans);
	}
	for(int i=1;i<=m;i++)
		if(l[i]!=ans&&r[i]!=ans&&zbb(r[i])!=zbb(l[i])){
			printf("%d %d\n",l[i],r[i]);
			f[zbb(l[i])]=zbb(r[i]);
		}
    return 0;
}
```


---

## 作者：⚡current⚡ (赞：0)

很水的一道题，只要读清题意就很简单

题目要求的是度数最大值最大的生成树，并不是度数之和要最大，那么显而易见，在原图中度数最大的点，在所有的生成树中也一定是最大的，因为一张图的生成树是它的子集，所以生成树中每个点的度数一定小于等于原图中对应点的度数。那么只要将原图中度数最大点的所有邻边都加入生成树中(因为保证没有自环或重边)，剩下的边任选就可以了，如果有多个点的度数都最大，那么任选一个即可。

**下面提供两种方法：**

**法一：**像**Kruskal**一样用并查集维护一下两个点是否在一棵树中，按上面的步骤加边，如果一个点的两个端点已经在一个集合里了，那就不用加了。

代码$\downarrow$

```c++
#include<stdio.h>

const int MAXN = 400000 + 121;
int v[MAXN], u[MAXN], dgree[MAXN], fa[MAXN], cnt, maxn, maxd, fau, fav;

inline int read()
{
    int x=0; char c=getchar();
    while(c<'0' || c>'9') c=getchar();
    while (c>='0' && c<='9') {x=x*10+c-'0'; c=getchar();}
    return x;
}
int find(int x)
{
    if(fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}
inline void add_into_gragh(int x, int y)//读入的时候建图加边用的
{
    u[++cnt] = x;
    v[cnt] = y;
    ++dgree[x];
    ++dgree[y];
    if(dgree[x] > maxd) {maxd = dgree[x]; maxn = x;}//顺便找一下度数最大的点
    if(dgree[y] > maxd) {maxd = dgree[y]; maxn = y;}
}
inline void add_into_tree(int x)//尝试把某条边加入生成树
{
    fau = find(u[x]), fav = find(v[x]);
    if(fau == fav) return;//如果一个点的两个端点已经在一个集合里了，那就不用加了
    printf("%d %d\n", u[x], v[x]);
    fa[find(fau)] = fav;
}
int main()
{
    int n, m;
    n = read(); m = read();
    for(int i = 1; i <= n; ++i) fa[i] = i;
    for(int i = 1; i <= m; ++i) add_into_gragh(read(), read());
    for(int i = 1; i <= m; ++i) if(u[i] == maxn || v[i] == maxn) add_into_tree(i);//先加度数最大点的邻边
    for(int i = 1; i <= m; ++i) add_into_tree(i);
    return 0;
}
```

**法二：**以度数最大点为起点BFS一下，BFS树就是一个符合要求的生成树，这个代码非常简单，我就不贴了。

---

