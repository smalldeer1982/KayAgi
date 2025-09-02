# Pashmak and Graph

## 题目描述

Pashmak's homework is a problem about graphs. Although he always tries to do his homework completely, he can't solve this problem. As you know, he's really weak at graph theory; so try to help him in solving the problem.

You are given a weighted directed graph with $ n $ vertices and $ m $ edges. You need to find a path (perhaps, non-simple) with maximum number of edges, such that the weights of the edges increase along the path. In other words, each edge of the path must have strictly greater weight than the previous edge in the path.

Help Pashmak, print the number of edges in the required path.

## 说明/提示

In the first sample the maximum trail can be any of this trails: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF459E/46950f7ebb1a8fb1042610e7d90ce693216dd148.png).

In the second sample the maximum trail is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF459E/0a8ef1a8d44f73ed1581f13e754f7328cc98bdea.png).

In the third sample the maximum trail is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF459E/077a752077571978dd842d2ca5ed7e4dcecd7b85.png).

## 样例 #1

### 输入

```
3 3
1 2 1
2 3 1
3 1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 3
1 2 1
2 3 2
3 1 3
```

### 输出

```
3
```

## 样例 #3

### 输入

```
6 7
1 2 1
3 2 5
2 4 2
2 5 2
2 6 9
5 4 3
4 3 4
```

### 输出

```
6
```

# 题解

## 作者：Star_Cried (赞：16)

## CF459E-DP

~~趁这题没掉蓝水发题解~~

~~核心代码15行~~

### 思路

观察数据范围，我们~~建m层分层图跑最长路~~想到DP。

DP最大的特点就是无后效性。那么我们这一题哪个条件无后效性呢？

发现**DP值一定从边权小于当前点的位置转移而来**。

这不就无后效性了？我们按边权将所有边排序即可。

然后，枚举边，将DP值记录到点上，每次用起始点的dp值加1更新到达点的dp值。最后输出dp值最大的即可。

然后，您会发现第一个样例过不去。

因为题目要求边权**严格递增**，所以我们需要同时将边权相同的边用上次的dp值更新，即我们需要临时记录一下。

样例非常良心。

### 实现

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#include<cmath>
using namespace std;
inline int read(){
	int w=0,x=0;char c=getchar();
	while(!isdigit(c))w|=c=='-',c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return w?-x:x;
}
namespace star
{
	const int maxn=3e5+10;
	int n,m,f[maxn],g[maxn];
	struct edge{
		int u,v,val;
		inline bool operator < (const edge &zp)const{return val<zp.val;}
	}e[maxn];
	inline void work(){
		n=read();m=read();
		for(int i=1;i<=m;i++)e[i].u=read(),e[i].v=read(),e[i].val=read();
		sort(e+1,e+1+m);
		for(int i=1,j;i<=m;i=j+1){
			j=i;
			while(e[j+1].val==e[i].val)j++;
			for(int k=i;k<=j;k++) g[e[k].u]=f[e[k].u],g[e[k].v]=f[e[k].v];//只有这些dp值要用
			for(int k=i;k<=j;k++) f[e[k].v]=max(f[e[k].v],g[e[k].u]+1);
		} 
		int ans=0;
		for(int i=1;i<=n;i++) ans=max(ans,f[i]);
		printf("%d",ans);
	}
}
signed main(){
	star::work();
	return 0;
}
```

#### postscripts

目前rank1，可能只是因为写的人少。

是一道不错的DP练手题。

---

## 作者：BriMon (赞：7)

更好的阅读体验[戳这里](https://www.cnblogs.com/BriMon/p/9709862.html)

在一条直线上的最长上升子序列我们都会，但是放在图上怎么办。

设$f[i][j]$为到点$i$，上一个经过的点是$j$的最长边数?显然不行，状态量爆炸，数组都开不下。

那既然在图上做不行，我们就把它转化到直线上。

我们必须让我们的转移时间接近线性，必须固定一维，枚举一维。

所以思考20分钟过后...
我们把边按照边权排序，这样往后递推的时候可以不用考虑边权的约束关系。

所以设$f[i]$为以点$i$为结尾的最长的边数。

然后枚举到一个边转移 : $f[v] = max \left(f[v], f[u] + 1 \right)$。

但是会有边权相同的边，那我们就不能用前面相同的边权得到的结果更新这个点，所以另开一个数组$g$存储和这条边相同边权的更新之后的$f$数组，这样就保证了更新是合法的。

记得清空$g$数组，开栈维护更新过的点， 可以把时间复杂度降低到$O(N^2)$；

此题还是很水的，毕竟像我这样的蒟蒻都能想出来..


```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define reg register
#define gc getchar
inline int read() {
	int res = 0;char ch=gc();bool fu=0;
	while(!isdigit(ch))fu|=(ch=='-'), ch=gc();
	while(isdigit(ch))res=(res<<3)+(res<<1)+(ch^48),ch=gc();
	return fu?-res:res;
}
#define N 300005
int n, m;
struct edge {
	int x, y, val;
	inline bool operator < (const edge & a) const {
		return val < a.val;
	}
}ed[N];
int f[N], g[N];
int stack[N], top;
int ans;

int main()
{
	n = read(), m = read();
	for (reg int i = 1 ; i <= m ; i ++)
		ed[i] = (edge){read(), read(), read()};
	sort(ed + 1, ed + 1 + m);
	for (reg int i = 1 ; i <= m ; i ++)
	{
		int j = i + 1;
		while(ed[i].val == ed[j].val) j ++;
		for (reg int k = i ; k < j ; k ++)
		{
			g[ed[k].y] = max(g[ed[k].y], f[ed[k].x] + 1);
			stack[++top] = ed[k].y;
		}
		while(top)
		{
			f[stack[top]] = max(f[stack[top]], g[stack[top]]);
			g[stack[top]] = 0;
			top--;
		}
		i = j - 1;
	}
	for (reg int i = 1 ; i <= n ; i ++) ans = max(ans, f[i]);
	cout << ans << endl;
	return 0;
}
```

---

## 作者：xy0313 (赞：6)

刚才标题太长了。。。



#### [更优质的阅读体验](https://xy0313.wordpress.com/2020/11/18/cf459e-pashmak-and-graph/)

### 我们可以将其转化为最长上升子序列

这时候我们可以按边权排序来更新每一个点

~~这样你就能拿到35分的好成绩~~

## 仅仅按边权排序是不行的


看下图

![](https://ftp.bmp.ovh/imgs/2020/11/53722a9849714a8e.png)

链接 6 和 5 的边如果先遍历到了，那么 6 的答案就会是2

而如果先遍历 3 和 5 这条边， 6 的答案就是 4

所以

### 在相同的边中，一定是起点答案大的优先遍历

因为小答案更新完可能需要被大答案重新更新

#### 而先更新大答案就能保证更新的点一定不会被第二次更新

这样就行了吗

~~这样你就还是能拿到35分的好成绩~~

还需要调整一个东西

![](https://ftp.bmp.ovh/imgs/2020/11/6823d3b646a68d0d.png)

在上图中，如果先遍历了 1 和 2 这条边， 3 就不能被 f [ 2 ] + 1 更新

也就是说，对于一些点

虽然不能用 f [ y ] = f [ x ] + 1 来更新，

### 但是可以用更新前的 x 点来更新

也就是 f [ y ] = f [ x ]

这样就可以 A 掉这道题了

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <queue>

using namespace std;

const int N = 3e5 + 4;

struct stu{
	int x,y,z;
}e[N];

struct fuck{
	int x;
	int w;
	bool operator <(const fuck &x)const {
		return w > x.w;
	}
};
//让起点中答案的放在前面，就是关于答案的大根堆

int n,m;
int f[N];
int cnt[N];

priority_queue <fuck> que;

bool cmp(stu x,stu y)
{
	return x.z < y.z;
}

int read()
{
    int x=0,f=1;
    char ch;
    while(ch<'0'||ch>'9')  {if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return f*x;
}
//加点优化吧

void bfs()
{
	while(que.size())
	{
		int u = que.top().x;
		que.pop();
		int x = e[u].x;
		int y = e[u].y;
		int w = e[u].z;
		if(f[x] + 1 > f[y])
		{
			if(!cnt[x] || cnt[x] < w)
			{
				f[y] = f[x] + 1;
				cnt[y] = w;
			}
			else if(f[x] > f[y])
			{
				f[y] = f[x];
				cnt[y] = w;
			}
        		// cnt 记录了更新这个点的上一个边权
                	//当前边比 cnt 大才能转移
                    	//防止相同边来搞事情
		}
	}
}

int main()
{
	n = read();
	m = read();
	for(int i = 1;i <= m;i ++) e[i].x = read(),e[i].y = read(),e[i].z = read();
	
	sort(e + 1,e + 1 + m,cmp);
	
	e[0].z = -1;
	e[m + 1].z = -1;
	for(int i = 1;i <= m + 1;i ++)
	{
		if(e[i].z != e[i - 1].z) bfs();
        	//相同边到此结束，遍历一下更新答案
     
		que.push((fuck){i,f[e[i].x]});
        	//相同的边开始了
	}
	int ans = 0;
	for(int i = 1;i <= n;i ++)
		ans = max(ans,f[i]);
	cout << ans;
	return 0;
}
```

完结撒花~

---

## 作者：YellowBean_Elsa (赞：5)

这题考思维能力。

首先我们想到最后这是一个图上最长上升序列，

故考虑把序列上求最长上升子序列的方法搬运过来，

$\operatorname{DP}$，设 $f$ 数组表示每个点结尾的序列最大长度。

然后按理要枚举上一条边进行转移。

但是这样有**后效性**，即不论怎么樣的 dp 顺序, 都会出现后面的状态影响前面的（考虑环）

怎么办？~~缩点，显然不行啊，每个 scc 内部怎么做呢。。。~~

经过一番思考，我们发现可以**按照边权从小到大枚举**！

（枚举大边时，根据题意小边不能用来转移）

但是注意到要求**严格递增**，所以我们必须把相同边权的边一起 dp 掉，又为了防止他们互相影响，开一个 $g$ 数组保存临时的转移结果。记得清空 $g$ 哦~~

时间复杂度 $O(M)$

```cpp
//coder: Feliks*GM-YB
#include<bits/stdc++.h>
#define fu(i,a,b) for(register int i = a, I = (b) + 1; i < I; i++)
#define fd(i,a,b) for(register int i = a, I = (b) - 1; i > I; i--)
typedef long long ll;
using namespace std;
const int N=4e5;
inline int Max(int x,int y){
	if(x>=y)return x;
	return y;
}inline int read(){
    int x=0;char ch=getchar();
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
    return x;
}int n,m;
struct edge{
	int x,y,w;
	bool operator < (const edge &A)const{
		return w<A.w;
	}
}e[N];
int f[N],g[N],ans;
int used[N],cnt;//用于记录相同边权的边的终点
int main(){
	n=read(),m=read();
	fu(i,1,m)
		e[i].x=read(),e[i].y=read(),e[i].w=read();
	sort(e+1,e+m+1);
	fu(i,1,m){
		int j=i-1;
		//枚举所有相同边权的边，注意最后 j 是第一个更大边权的边
		while(e[++j].w==e[i].w){ 
			used[++cnt]=e[j].y;
			g[e[j].y]=Max(g[e[j].y],f[e[j].x]+1);//先用临时数组转移 
		}while(cnt){
			//把临时数组合并到 f 中，并清空 
			f[used[cnt]]=Max(g[used[cnt]],f[used[cnt]]);
			g[used[cnt]]=0;cnt--;
		}i=j-1;//注意 for 循环会再做一步 i++，刚好把 i 变成 j 
	}fu(i,1,n)ans=Max(f[i],ans);
	printf("%d\n",ans);
	return 0;
}
```




---

## 作者：violetctl39 (赞：2)

# CF459E Pashmak and Graph 题解

by ctldragon

简化题意：给你一个有向图，求出最长的边权严格递增的路径长度。

设 $f_u$ 为从 $u$ 开始的最长边权严格递增的路径长度，发现每次转移都是从边权更大的边转移过来。

所以对边权从大到小排序后可以直接 DP，而没有后效性。
$$
f_u=\max_{v\in e[u]}f_v+1
$$
由于题目要求严格递增，所以转移时要避免出现 $v$ 已经被边权为 $w$ 的边更新后又用同样边权的边更新 $u$。所以要记一下 $g_v$，代表边权严格大于 $f_v$ 的转移边权的最长路径。这里可以记 $vis_v=w$ 来标记当前 $f_v$ 是否已经被边权为 $w$ 的边更新过。



本做法代码量题解区较小，最易实现。时间复杂度瓶颈在于排序 $O(m\log m)$，DP 复杂度为严格 $O(m)$。

代码：

```cpp
#include<bits/stdc++.h>
#define pc(x) putchar(x)
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){f=ch=='-'?-1:f;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
void write(int x)
{
	if(x<0){x=-x;putchar('-');}
	if(x>9)write(x/10);
	putchar(x%10+48);
}
int n,m,ans;
struct edge
{
	int u,v,w;
	friend bool operator <(edge x,edge y)
	{return x.w>y.w;}
}e[300005];
int f[300005],g[300005],vis[300005];
int main()
{
	n=read(),m=read();
	for(int i=1;i<=m;++i)
		e[i]={read(),read(),read()};
	sort(e+1,e+m+1);
	for(int i=1;i<=m;++i)
	{
		int u=e[i].u,v=e[i].v,w=e[i].w;
		int upt=vis[v]==w?g[v]+1:f[v]+1;
		if(f[u]>=upt)continue;
		if(vis[u]!=w)g[u]=f[u];//更新
		f[u]=upt;vis[u]=w;
	}for(int i=1;i<=n;++i)ans=max(ans,f[i]);
	write(ans),pc('\n');
	return 0;
}
```



---

## 作者：CRTL_xzh2009 (赞：1)

DP题。

首先对边按权值排序，令 $d_i$ 为以点 $i$ 为结尾的最长路径长度。

设边 $E=(a,b,c)$，显然 $d_b=\max\{d_b,d_a+1\}$，因为边权排过序，显然可以这样转移。但是有边权相等的情况，这时候如果出现例如 $1 \rightarrow 3,3\rightarrow4$ 的边权相等，那么进行 $d_3=d_1+1,d_4=d_3+1$ 时，$d_4$ 就会错误。

一种方法是将边权相同的边取出来，将 $d_3=d_1+1,d_4=d_3+1$ 改为 $dd_3=d_1+1,dd_4=d_3+1$，即将 $d$ 转移到 $dd$ 上，这样就是让相同边权的边无序同时转移，最后再将这些点的 $dd$ 复制回 $d$ 上即可。

```cpp
#include<bits/stdc++.h>//
using namespace std;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0')
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
int x[300005],y[300005],f[300005],f2[300005],cnt=0,n,m,ans=0;
struct Node
{
	int x,y,w;
}a[300005];
bool cmp(Node x,Node y)
{
	return x.w<y.w;
}
int main() 
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		a[i].x=read(),a[i].y=read(),a[i].w=read();
	sort(a+1,a+1+m,cmp);
	for(int i=1;i<=m;i++)
	{
		int j=i;
		while(j<m&&a[j].w==a[j+1].w)
			j++;
		for(int k=i;k<=j;k++)
		{
			f2[a[k].x]=f[a[k].x];
			f2[a[k].y]=f[a[k].y];
		}
		for(int k=i;k<=j;k++)
			f[a[k].y]=max(f[a[k].y],f2[a[k].x]+1);
		i=j;
	} 
	for(int i=1;i<=n;i++)
		ans=max(ans,f[i]);
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：封禁用户 (赞：1)

递增关系怎么可能构成环，直接 dp。

先对边排序，对于每个同颜色段有向转移。是不是很像洪水蔓延？

$f_v$ 表示节点 $v$ 为终点的最长递增路径长度。方程 $f_v = \max(f_v,f_u+1)$。

看张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/bfthja7w.png)

**严格递增**哦。显然这个是会互相影响的。因为我们默认转移后继边一定严格递增，在同颜色段下会出错，这是因为有些转移的终点相同。但很明显，它们只需要在同一时刻转移就能正确性。开辅助数组转移。

```cpp
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#include <immintrin.h>
#include <emmintrin.h>
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 3e5 + 5;
int n,m,ans;
struct edge{
	int u,v,w;
	bool operator < (const edge &b) const {
		return w < b.w;
	}
}e[maxn];
int tmp[maxn];
int f[maxn];
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i = 1;i<=m;i++) {
		cin>>e[i].u>>e[i].v>>e[i].w;
	}
	sort(e + 1,e + 1 + m);
	int i,j;
	for(i = 1;i<=m;i = j) {
		for(j = i; j<=m && e[i].w == e[j].w;j++) {
			int u = e[j].u;
			int v = e[j].v;
			tmp[u] = f[u];
		}
		for(j = i; j<=m && e[i].w == e[j].w;j++) {
			int u = e[j].u;
			int v = e[j].v;
			f[v] = max(f[v],tmp[u] + 1);
		}
	}
	for(int i = 1;i<=n;i++) {
		ans = max(ans,f[i]);
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：WZKQWQ (赞：1)

又是一道 1900* 的紫，只能说你谷古早 CF 评分属实逆天。

首先弱化一下，假如没有相同权值边怎么做？那直接设 $f_x$ 是当前图从点 $x$ 出发能走的最远距离，然后从大到小加边，假设被加的边是从 $s\rightarrow t$ 的，那么 $f_s = \max(f_s,f_t+1)$。

然后有相同权值边直接做比较麻烦，我们考虑开个队列存一下转移，相同权值的一起转移就行，这个做法本质就是分层图增量法。

复杂度 $O(n + m)$，代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 300005;
struct Edge{
	int x,y,z;
}e[N];
queue<pair<int,int> >q;
int n,m,f[N];
bool cmp(Edge x,Edge y){return x.z > y.z;}
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;++i) scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].z);
	sort(e + 1,e + m + 1,cmp);
	//for(int i = 1;i <= n;++i) f[i] = 1;
	for(int i = 1;i <= m + 1;++i){
		if(e[i].z != e[i - 1].z){
			while(!q.empty()){
				pair<int,int> tmp = q.front();
				f[tmp.first] = max(f[tmp.first],tmp.second);
				q.pop();
			}
		}
		if(i <= m) q.push({e[i].x,f[e[i].y] + 1});
	}
	int ans = 0;
	for(int i = 1;i <= n;++i) ans = max(ans,f[i]);
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：violin_wyl (赞：1)

## CodeForces459E



#### 解析

###### 题目大意：

有一个 $n$ 个点 $m$ 条边带权有向图，求最长上升路径长度

###### 思路

直接dp明显不行，既然要求路径上的边权单调递增，那就把边权排序不就好了？

这里给一张图
![0](https://cdn.luogu.com.cn/upload/image_hosting/zt00ro65.png)


我们按照边权从小到大加入新的图

![1](https://cdn.luogu.com.cn/upload/image_hosting/q6ps2yxm.png)
![2](https://cdn.luogu.com.cn/upload/image_hosting/j0wkk19k.png)
![3](https://cdn.luogu.com.cn/upload/image_hosting/cgb8iusw.png)

看到这基本都会了吧，设 $f_i$ 表示以 $i$ 结尾的递增路径的最大长度，我们每次把相同权值的边加入，并通过 $f[u]$ 更新 $f[v]$，那转移方程方程则为 $f_v=min(f_v, f_u+1)$
~~这题绿差不多吧~~

----------------------------------------------------

### code

```c++
#include<bits/stdc++.h>
#define int long long
const int N = 3e5 + 10;
const int mods = 1e9 + 7;
const int INF = INT_MAX;
using namespace std;
inline int read ( )
{
	int x = 0, f = 1;
	char ch = getchar ( );
	while (ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar ( );}
	while (ch >= '0' && ch <= '9') {x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar ( );}
	return x * f;
}
struct node{
	int u, v, w;
	bool operator < (const node &A) const{
		return w < A.w;
	}
}e[N];
int dp[N], dp2[N];
int ans;
stack <int> st;
signed main()
{
	int n, m;
	n = read ( ), m = read ( );
	for (int i = 1; i <= m; i++) e[i].u = read ( ), e[i].v = read ( ), e[i].w = read ( );
	sort (e + 1, e + m + 1);
	for (int i = 1; i <= m; )
	{
		int j = i;
		while (e[i].w == e[j].w) j++;
		for (int k = i; k < j; k++)
		{
			dp2[e[k].v] = max (dp2[e[k].v], dp[e[k].u] + 1);
			st.push (e[k].v);
		}
		while (!st.empty ( ))
		{
			dp[st.top ()] = max (dp[st.top ( )], dp2[st.top ( )]);
			st.pop ( );
		}
		i = j;
	}
	for(int i = 1; i <= n; i++) ans = max (ans, dp[i]);
	printf("%d\n", ans);
	return 0;
} //The Dark Emperor
```



---

## 作者：xuezhiyu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF459E)

# 分析题目

要保证这个路径的边权严格递增，那么对于一个节点 $i$ 来说，就可以被用其它有指向它的边的从权值更小的边转移过来。所以说一条边肯定不能经过两次，有了无后效性的保证，我们就可以考虑动态规划了。

状态很好想到：定义 $f_i$ 表示以 $i$ 为最后一个节点的最长路径所包含的边数，所有都初始化为 $0$。

首先肯定得从边权比较小的开始转移，所以要先把所有边按权值从小到大排个序。对于一条边 $(u,v,w)$，之前进行更新 $u$ 的边的权值肯定小于当前这条边的权值 $w$，所以从 $f_u$ 来更新 $f_v$ 肯定是合法的，那么就可以写出状态转移方程：$f_v = \max(f_v, f_u+1)$。

但是就像第一个样例那样，边权可能重复，所以按照顺序就可能从一条边更新到一条和它权值相等的边，所以我们还需要一个数组 $l$ 来存下相同权值的边所更新的 $u$ 所对应的 $f_u$，这样就保证了边权值按更新顺序的单调递增性。

# 代码时间

```cpp
#include <algorithm> // sort 要用
#include <iostream>

using namespace std;

struct edge { // 存储边权的结构体
	int u, v, w;
};

const int N = 3e5 + 10;
int n, m;
int f[N]; // 动态规划的状态数组
int lst[N]; // 题解里面的 l 数组
int ans;
edge graph[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) cin >> graph[i].u >> graph[i].v >> graph[i].w;
	sort(graph + 1, graph + m + 1, [](edge a, edge b) {return a.w < b.w;}); // 按边权的大小从小到大排序
	for (int l = 1; l <= m;) {
		int r = l;
		while (graph[r].w == graph[l].w) r++; r--; // 寻找权值相同的边区间
		for (int i = l; i <= r; i++) lst[graph[i].u] = f[graph[i].u]; // 备份一下，保证路径上边权的单调递增
		for (int i = l; i <= r; i++) f[graph[i].v] = max(f[graph[i].v], lst[graph[i].u] + 1); // 转移方程（注意 lst 不能写成 f）
		l = r + 1;
	}
	for (int i = 1; i <= n; i++) ans = max(ans, f[i]); // 最长的路径以那个节点结尾都有可能
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Zhl2010 (赞：0)

首先读完题我们一定会想到用暴力，每次遍历点并记录下当前点的最大值。

当敲完[错误代码](https://www.luogu.com.cn/paste/8dvw6ouw)时，你会发现你连最后一个样例都过不了了。

为什么？通过观察最后一个样例和程序的过程，我们发现了一个很严重的问题：每次更新了最大值，当下一次遍历这个点时，会因为自身的值太小而退出。

所以正解是什么？

我们先将边从大到小排序（因为从大的边一定能往小的边走，这样方便遍历），然后每次加一条边，用队列存起来，遍历每条边，更新 $f$ 数组，也就是动态规划数组，表达式为 $f_v=\max (f_v,f_t+1)$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x,y,z;
}e[300010];
queue<pair<int,int> >q;
int n,m,f[300010];
bool cmp(node x,node y){
	return x.z>y.z;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++) scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].z);
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=m+1;i++){//第 m+1 次是最后算出答案的一次
		if(e[i].z!=e[i-1].z){
			while(!q.empty()){
				pair<int,int> t=q.front();
				f[t.first]=max(f[t.first],t.second);
				q.pop();
			}
		}
		if(i<=m) q.push({e[i].x,f[e[i].y]+1});//最后一次不用加边
	}
	int ans=0;
	for(int i=1;i<=n;++i) ans=max(ans,f[i]);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：_JF_ (赞：0)

[Link](https://www.luogu.com.cn/problem/CF459E)

军训七天，一题没训。

但是独立切了。

考虑如果原图是个 DAG，那问题很简单，直接拍个 dp 上去就下班了。但是环好像比较难处理。

显然不能进行缩点，我们换一种思考方式，发现按照 DAG 的更新方式被边权限制了，考虑我们边权从小到大进行一个更新。

这样就可以解决掉边权的限制。

考虑 $dp_{i,j}$ 表示以 $i$ 为末尾，最大值为 $j$ 的最长长度。

假设当前边是从 $u$ 到 $v$，边权为 $w$，我们只要把当前以前，以 $u$ 为入度的所有边的 dp 用来更新即可。

所以我们要剔除掉以 $u$ 为入度且边权为 $w$ 的情况。

具体做法就是维护两个数组，分别记录当前边和上一条权值不同的边的权值即可。

然后我们还需要维护一个前缀的 dp 最大值来进行转移。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =4e5+10;
#define int long long
struct node{
	int u,v,w;
}a[N];
int n,m,lst[N],Now[N];
bool cmp(node a,node b){
	return a.w<b.w;
}
map<int,int>  g[N],dp[N];
inline long long read()
{
    register long long x=0,f=0;
    register char t=getchar();
    while(t<'0'||t>'9')f^=(t=='-'),t=getchar();
    while(t>='0'&&t<='9')x=(x<<3)+(x<<1)+(t^48),t=getchar();
    return f?-x:x;
}
inline void write(int x){
  	static int sta[35];int top=0;
  	do{sta[top++]=x%10,x/=10;}while (x);
  	while(top)putchar(sta[--top]+48);
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=m;i++)	a[i].u=read(),a[i].v=read(),a[i].w=read();
	sort(a+1,a+m+1,cmp);
	for(int i=1,u,v,w;i<=m;i++){
		u=a[i].u,v=a[i].v,w=a[i].w;
		if(w!=Now[u])	dp[v][w]=max(dp[v][w],g[u][Now[u]]+1);
		else	dp[v][w]=max(dp[v][w],g[u][lst[u]]+1);
		if(Now[v]!=w)	lst[v]=Now[v],Now[v]=w,g[v][w]=max(g[v][lst[v]],dp[v][w]);
		else	g[v][w]=max(g[v][lst[v]],dp[v][w]);
//		if(lst[v]!=w)	g[v][w]=max(g[v][w],max(dp[v][lst[v]],g[v][lst[v]])),lst[v]=w;
	}
	int ans=1;
//	cout<<dp[3][2]<<endl;
	for(int i=1;i<=m;i++)	ans=max(ans,dp[a[i].v][a[i].w]);
	write(ans),putchar(10);
	return 0;
}

```

---

## 作者：conprour (赞：0)

# 分析
作为一个紫题，真的很水...

首先对于题目所说的边权严格递增，不难想到按照边权排序，这样就不用考虑图上的
操作，直接按照顺序考虑每一条边即可。

这样的话 dp 也好想：设 $dp_i$ 表示以 $i$ 为结尾的包含最多的边数，那么转移也很显然： $dp_i=max\{dp_j+1,dp_i\}$ 。

但是还有一个问题：题目要求**严格**递增，那么如果有相等的值该怎么办？

要避开相等的情况来转移 dp ，但是又不能额外开二维 dp ，所以只能用**滚动数组**了！

不过这里的滚动数组算是一个活用。开两个数组 $f_i,dp_i$ ，其中 $f_i$ 作为滚动数组， $dp_i$ 作为答案数组。

枚举的时候每次找到边权相同的区间 $[i,j]$ ，先转移 $dp_i=max\{f_j+1,dp_i\}$ ，再把 $f_i$ 用 $dp_i$ 覆盖，为下一次转移做准备。

还有不懂的，就直接看代码吧！

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int INF = 0x3f3f3f3f,N = 3e5+10;
inline ll read()
{
	ll ret=0;char ch=' ',c=getchar();
	while(!(c>='0'&&c<='9')) ch=c,c=getchar();
	while(c>='0'&&c<='9') ret=(ret<<1)+(ret<<3)+c-'0',c=getchar();
	return ch=='-'?-ret:ret;
}
int n,m;
struct edge
{
	int x,y,w;
	bool operator <(const edge &oth) const
	{
		return w<oth.w;
	}
}a[N];
int dp[N],f[N];
int cnt[N];
int main()
{
	n=read(),m=read();
	for(int i=1;i<=m;i++) 
		a[i].x=read(),a[i].y=read(),a[i].w=read();
	sort(a+1,a+m+1);
	for(int i=1;i<=m;i++)
	{
		int j=i;
		while(a[i].w==a[j].w) j++;
		for(int k=i;k<j;k++) dp[a[k].y]=max(dp[a[k].y],f[a[k].x]+1);
		for(int k=i;k<j;k++) f[a[k].y]=max(f[a[k].y],dp[a[k].y]);
		i=j-1;  
	}
	int ans=0;
	for(int i=1;i<=n;i++) ans=max(ans,dp[i]);
	printf("%d\n",ans);
	return 0;
}

```


---

