# FreeDiv

## 题目描述

Vasya plays FreeDiv. In this game he manages a huge state, which has $ n $ cities and $ m $ two-way roads between them. Unfortunately, not from every city you can reach any other one moving along these roads. Therefore Vasya decided to divide the state into provinces so that in every province, one could reach from every city all the cities of the province, but there are no roads between provinces.

Unlike other turn-based strategies, in FreeDiv a player has the opportunity to build tunnels between cities. The tunnels are two-way roads along which one can move armies undetected by the enemy. However, no more than one tunnel can be connected to each city. As for Vasya, he wants to build a network of tunnels so that any pair of cities in his state were reachable by some path consisting of roads and a tunnels. But at that no more than $ k $ tunnels are connected to each province (otherwise, the province will be difficult to keep in case other provinces are captured by enemy armies).

Vasya discovered that maybe he will not be able to build such a network for the current condition of the state. Maybe he'll have first to build several roads between cities in different provinces to merge the provinces. Your task is to determine the minimum number of roads Vasya needs to build so that it was possible to build the required network of tunnels in the resulting state.

## 说明/提示

In the first example only one province exists, so it is not necessary to build any tunnels or roads.

In the second example two provinces exist. It is possible to merge the provinces by building a tunnel between cities 1 and 3.

In the third example at least one additional road is necessary. For example it is possible to build additional road between cities 1 and 2 and build two tunnels between cities 1 and 3, 2 and 4 after that.

## 样例 #1

### 输入

```
3 3 2
1 2
2 3
3 1
```

### 输出

```
0```

## 样例 #2

### 输入

```
4 2 2
1 2
3 4
```

### 输出

```
0```

## 样例 #3

### 输入

```
4 0 2
```

### 输出

```
1```

# 题解

## 作者：pythoner713 (赞：10)

假设我们在第一步中已经随便连了一些边，那么怎么判断是否可以通过操作二使图联通呢？

经过操作一后，设当前图中的联通块大小分别是 $a_1,a_2,\dots,a_d$。注意到操作二可以等价于以下表述：对于第 $i$ 个连通块，最多向外连出 $\min(a_i,k)$ 条边。而要想令这 $d$ 个连通块联通，至少还需要 $d-1$ 条边。因此操作二能使当前图联通，当且仅当：

$$\sum_{i=1}^d\min(a_i,k)\ge 2(d-1)$$

乘以 $2$ 是因为一条边会被统计两次。

那么现在正解就呼之欲出了，第一步的连边无非是为了合并原图连通块，达到减小 $d$ 的目的，但是合并后出的新连通块大小要尽量不超过 $k$，不然会让不等式左侧减小。因此我们可以用小根堆维护当前所有连通块大小，每次选取最小的两个连通块合并，直到上述不等式成立即可。

---

```cpp
#include<bits/stdc++.h>
#define nb 1000010
using namespace std;

int ans, d, n, m, k, E, fa[nb], size[nb];
priority_queue<int, vector<int>, greater<int>> q;

int find(int x){
	while(x != fa[x])
		x = fa[x] = fa[fa[x]];
	return x;
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++) fa[i] = i;
	for(int i = 0, u, v; i < m; i++)
		cin >> u >> v, fa[find(u)] = find(v);
	for(int i = 1; i <= n; i++) size[find(i)]++;
	for(int i = 1; i <= n; i++){
		if(find(i) == i) q.push(size[i]), d++;
		E += min(k, size[i]);
	}
	while(1){
		if(E >= 2 * d - 2){
			cout << ans;
			return 0;
		}
		ans++;
		int u, v;
		u = q.top(), q.pop();
		v = q.top(), q.pop();
		d--, E -= min(u, k) + min(v, k);
		E += min(k, u + v);
		q.push(u + v);
		// E 即为不等式左侧的值
		// 每次贪心地取两个最小的连通块合并
		// 一旦有 E >= 2(d - 1) 说明可以进入操作二, 输出答案
	}
	return 0;
}
```


---

## 作者：small_john (赞：3)

## 思路

首先，需要明白，如果在操作一后，有 $x$ 个联通块，则整张图还需要 $x-1$ 条无向边才能联通。

而，设第 $i$ 个联通块的大小是 $siz_i$，由于每个点只能连一条边，则最多能向外连到 $siz_i$ 个点，等价于可以向外连 $siz_i$ 个联通块（即每个点都在不同的联通块）。

对于操作 $2$，一个联通块就只能向外连 $k$ 条边，所以就只能联通 $\min(siz_i,k)$ 个块。

所以，操作二在满足 $\displaystyle\sum_{i=1}^{x} \min(siz_i,k)\ge 2\times(x-1)$ 才能使图联通，注意连接两个联通块必须两个都有可以向外连的边时才行，所以右边要乘 $2$。

那么就可以用贪心的思想从小到大合并联通块。证明如下：

如果两个联通块 $x,y$，不妨设 $siz_x<siz_y$，满足 $siz_x\le k,siz_y\le k,siz_x+siz_y>k$，且存在另一个联通块 $z$ 使得 $siz_x+siz_z\le k$，易得 $siz_z<siz_y$。这样，第一种方法的贡献是 $k+siz_z$，而第二种就是 $siz_x+siz_y+siz_z$，因为 $siz_x+siz_y>k$，所以第二种一定比第一种优。

综上，先选小的比先选大的更优。

这个东西用堆维护就行了，时间复杂度 $O(n\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
int n,m,k,f[N],siz[N],ans,now;
priority_queue<int> q;
int find(int x)
{
	if(f[x]==x) return x;
	return f[x] = find(f[x]);
}
void add(int x,int y)//维护联通块
{
	int fx = find(x),fy = find(y);
	if(fx==fy) return;
	siz[fx]+=siz[fy],siz[fy] = 0,f[fy] = fx;
}
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	for(int i = 1;i<=n;i++) f[i] = i,siz[i] = 1;
	for(int i = 1,x,y;i<=m;i++)
		cin>>x>>y,add(x,y);
	for(int i = 1;i<=n;i++)
		if(f[i]==i)
			q.push(-siz[i])/*大根堆维护最小值转负数*/,now+=min(siz[i],k);
	while(1)
	{
		if(now>=2*q.size()-2)//满足条件
			return cout<<ans,0;
		ans++;
		int u = -q.top();q.pop();
		int v = -q.top();q.pop();
		now+=min(k,u+v)-min(k,u)-min(k,v);
		q.push(-u-v);
	}
	return 0;
}
```

---

## 作者：No21 (赞：1)

### 解题思路

我们发现第一步没什么有用的已知信息，而且要求解的地方也在第一步，因此我们很自然的想到从第二步入手。

第二步中我们明显需要的而且未知的量只有一个，即经过第一步处理后的新图的联通块数。因此，我们设新图中有 $tot$ 个联通块，那么我们在第二步里最少需要连 $tot-1$ 条边，那么我们在第二步中总共最多能连多少条边呢？由于第二步中连边数量对点数和联通块的限制，因此对于第 $i$ 个连通块，我们可以连出 $\min(size_i,k)$ 条**单向边**（一出一进就是双向边，而且每个点只连了一条边，如果每个点连一条双向边，就变成每个点连了两条边（自己发出一条和从别的点来的一条））。因此，我们只需要令以下不等式成立，就可以满足条件 $(tot>0)$。

$$\sum\limits_{i=1}^{tot}{\min(size_i,k)} \ge 2 \times (tot-1)$$

我们考虑，初始的图有一个 $tot$（初始联通块个数），因此我们考虑去不断缩小 $tot$ 使不等式成立（一定会有成立的时候，因为不等式左边永远是正数，而右边最小是 $0$，其实从不等式的意义上考虑也很容易得出）。在缩小右边的同时，我们要保证左边尽可能大，不难发现，左边的大小由 $tot$ 和 $size_i$ 共同决定，而 $size_i$ 是有上界的，因此我们尽可能的让每个被合并的 $i$ 的 $size_i$ 尽可能小，这一定是更优的，证明如下。

我们设 $size$ 最小的两个联通块为 $i$ 和 $j$，然后随便取出两个随机块 $x$ 和 $y$。

有一个显而易见的式子：

$$\sum\limits_{i=1}^{tot}{\min(size_i,k)} \le \sum\limits_{i=1}^{tot}{size_i}$$

无论怎么合并，如果合并前两个联通块的 $size$ 的和小于 $2 \times k$，那么总价值不变。反之，我们的总价值**减少**了 $size_x+size_y-2 \times k$，因为 $size_x+size_y \ge size_i+size_j$，所以 $size_x+size_y-2 \times k \ge size_i+size_j-2 \times k$ 因此无论如何，选 $size$ 最小的两个联通块一定不会更劣。

```
#include<bits/stdc++.h>
using namespace std;
namespace TO
{
    const int N=1e6+21;
    int n,m,k,uu,vv,sum,ans,tot;
    priority_queue <pair <int,int>,vector <pair <int,int> >,greater <pair <int,int> > > q;
    int fa[N],size[N];
    int find(int x)
    {
        if(x==fa[x])
            return x;
        return fa[x]=find(fa[x]);
    }
    int mian()
    {
        cin>>n>>m>>k;
        for(int i=1;i<=n;i++)
        {
            fa[i]=i;
            size[i]=1;
        }
        for(int i=1;i<=m;i++)
        {
            cin>>uu>>vv;
            int x=find(uu),y=find(vv);
            if(x!=y)
            {
                size[x]+=size[y];
                fa[y]=x;
            }
        }
        for(int i=1;i<=n;i++)
        {
            if(fa[i]==i)
            {
                sum+=min(size[i],k);
                q.emplace(size[i],i);
                tot++;
            }
        }
        while(1)
        {
            if(sum>=2*(tot-1))
                break;
            auto x=q.top();
            q.pop();
            auto y=q.top();
            q.pop();
            sum-=min(x.first,k);
            sum-=min(y.first,k);
            fa[x.second]=y.second;
            sum+=min(x.first+y.first,k);
            q.emplace(x.first+y.first,y.second);
            tot--;
            ans++;
        }
        cout<<ans<<'\n';
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

## 作者：HowToCarry (赞：1)

[FreeDiv](https://www.luogu.com.cn/problem/CF73D)
### 分析
我们先只考虑第二步，设第一步后图中有 $cnt$ 个连通块，那么显然我们使其联通就需要连 $cnt-1$ 条边，对于连通块 $i$，设其点个数为 $sz_i$，那么这个连通块最多可以向外连 $\min(sz_i,k)$ 条边，那么我们就可以推出若想让整张图联通需满足:
$$
\sum^{cnt} _ {i=1}\min(k,sz_i)\geq 2\times (cnt-1)
$$
这里 $cnt-1$ 乘 $2$ 的原因是连边次数的限制是相对的，比如说第二步 $i$ 向 $j$ 连了一条边，$i$ 不能再连边的同时 $j$ 也不能再连边了。然后我们观察这个式子发现，一个连通块最多连 $k$ 条边，但如果联通块大小越小，那么块就越多，就会使左式变小而右式变大，所以我们第一步的操作的意义就是减少联通块数量并增大连通块大小，但如果块大小超过了 $k$ 的话就相当于浪费了次数，所以我们优先合并块大小最小的块，那么我们直接用小根堆每次将最小的连通块合并直到满足上式要求即可。
### Code
```cpp
#include<bits/stdc++.h>
#define il inline
#define ll long long
#define Angry 0
using namespace std;
const int N=1000005;
int n,m,k,ans,cnt,sum;
int fa[N],sz[N];
priority_queue<int,vector<int>,greater<int> >q;
int find(int u){
	return fa[u]==u?u:fa[u]=find(fa[u]);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		fa[i]=i;
		sz[i]=1;
	}
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		u=find(u);
		v=find(v);
		if(u!=v){
			fa[u]=v;
			sz[v]+=sz[u];
		}
	}
	for(int i=1;i<=n;i++){
		if(fa[i]^i) continue;
		q.push(sz[i]);
		sum+=min(k,sz[i]);
		cnt++;
	}
	int u,v;
	while(sum<((cnt-1)<<1)){
		ans++;
		cnt--;
		u=q.top();
		q.pop();
		v=q.top();
		q.pop();
		sum-=min(u,k)+min(v,k);
		sum+=min(k,u+v);
		q.push(u+v);
	}
	cout<<ans;
	return Angry;
}


```


---

## 作者：翼德天尊 (赞：1)

因为只需要维护连通性，所以不妨以连通块为单位，对于一个大小为 $g$ 的连通块，在第二步中可以向外连 $\min(k,g)$ 条边。

不难发现当 $k=1$ 时，设连通块个数为 $g$，则答案为 $g-2$（注意特判初始连通的情况）。下面考虑 $k>1$ 的情况。

故贪心地讲，我们不会在第一步将大小之和大于 $k+1$ 的两个连通块相连，否则反而会在第二步当中起到副作用。

考虑第二步中我们会将所有连通块连成一棵树的形状，其中单点只能作为叶子节点，剩下的连通块可以作为非叶节点，设所有连通块的最大度数之和为 $d$，则当 $d\ge 2(g-1)$ 时有解。

考虑在第一步中一次加边的作用，若所加的两个连通块大小之和小于等于 $k$，则加边的贡献为 $g\leftarrow g-1$，即使得差值减 $2$；若等于 $k+1$，则贡献为 $g\leftarrow g-1$，$d\leftarrow d-1$，差值减 $1$。

故现在问题就来到了如何做第一步。发现在正常的这样的问题中，直接贪心做，每次取最小的两个连通块合并是不对的，但是又很难用其它方法做。

但其实只要把所有单点合并成非单点，就一定有解了，所以我们每次取最小的两个连通块合并一定可以在所选连通块大小之和 $>k+1$ 之前使不等式 $d\ge 2(g-1)$ 成立。

故当 $d\ge 2(g-1)$ 时，答案为 $0$，否则为 $\left\lceil\frac{2(g-1)-d}{2}\right\rceil$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5;
int n,m,k,d[N],fa[N],cnt,siz[N];
// struct Edge{
//     int to[N<<1],next[N<<1],head[N],tot;
//     void adde(int u,int v){
//         to[++tot]=v,next[tot]=head[u],head[u]=tot;
//     }
// }S;
int read(){
    int w=0,f=1;
    char ch=getchar();
    while (ch>'9'||ch<'0') {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9') {
        w=(w<<3)+(w<<1)+(ch^48);
        ch=getchar();
    }
    return w*f;
}
int find(int x){
    if (fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    // freopen("out.out","w",stdout);
#endif
    n=read(),m=read(),k=read();
    for (int i=1;i<=n;i++) fa[i]=i,siz[i]=1;
    cnt=n;
    for (int i=1;i<=m;i++){
        int u=read(),v=read();
        int x=find(u),y=find(v);
        if (x==y) continue;
        fa[x]=y,siz[y]+=siz[x],--cnt;
    }
    if (k==1){
        cout<<max(0,cnt-2)<<"\n";
        return 0;
    }
    int d=0;
    for (int i=1;i<=n;i++){
        if (fa[i]==i) d+=min(siz[i],k);
    }
    d=2*(cnt-1)-d;
    if (d<=0) puts("0");
    else cout<<(d+1)/2<<"\n";
    return 0;
}
```

---

## 作者：mango2011 (赞：0)

好题！

首先，我们明确一下怎样的情形可以满足题目条件：设当前有 $cnt$ 个连通块，大小分别为 $sz_1,sz_2,sz_3,\dots,sz_{cnt}$。那么，第 $i$ 个连通块最多连出 $\min(sz_i,k)$ 条边，总的度数最多为 $tot=\displaystyle\sum_{i=1}^{k}\min(sz_i,k)$，容易发现当且仅当 $tot\ge2(cnt-1)$ 时这些连通块可以通过操作二组成一个连通图。

而操作一的意义就是：选择两个不同的连通块 $i,j$，合并 $i,j$。对于 $tot$ 而言得到了 $\min(sz_i+sz_j,k)$ 的贡献，丢失了 $\min(sz_i,k)+\min(sz_j,k)$ 的贡献；对于 $cnt$，它的值减少了 $1$。容易发现，我们每一次选取当前最小的 $sz_i,sz_j$ 就可以得到一定是最优的。

有了上面的分析，我们可以开一个优先队列（小根堆），维护当前最小的连通块大小，并且判断 $tot$ 是否大于等于 $cnt$ 即可。

总的复杂度就是 $O(n\log n)$，可以通过。

[评测记录](https://codeforces.com/contest/73/submission/276994022)

---

## 作者：PDAST (赞：0)

## 题意
中文翻译说得很清楚了，我就不赘述了。
## 思路
先将第二步的边全部连上，统计连通块，尽量修免费的路，令第 $i$ 个连通块内有 $s_{i}$ 个点，每个连通块可以连的免费的路的条数为 $\min{s_{i},k}$ 条，把每个块的可连边数放入优先队列，每次取最小的两个，当两个连通块连上后，把一个的可连边数并到另一个点，并把可连边数减二，直到需连边数小于等于可连边数为止，每次答案加上一。最后输出答案即可。
## 代码
~~~cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int f[1000011],s[1000011],sum,cnt,ans;
int Find(int x){
	return f[x]=(f[x]==x?x:Find(f[x]));
}
signed main(){
	int n,m,k;
	priority_queue<int,vector<int>,greater<int>>q;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) f[i]=i;
	while(m--){
		int x,y;
		cin>>x>>y;
		f[Find(x)]=Find(y);
	}
	for(int i=1;i<=n;i++)s[Find(i)]++;
	for(int i=1;i<=n;i++){
		if(s[i])q.push(s[i]);
		if(s[i]>0)cnt++;
		sum+=min(k,s[i]);
	}
	while((cnt-1)*2>sum){
		int x=q.top();
		q.pop();
		int y=q.top();
		q.pop();
		cnt--;
		sum+=min(k,x+y)-min(k,x)-min(k,y);
		q.push(x+y);
		ans++;
	}
	cout<<ans;
}
~~~

---

## 作者：xxx2022 (赞：0)

首先将题意转化一下，假设我们在第一步中将原图划分成了 $p$ 个连通块，计第 $i$ 连通块大小为 $siz_i$，那么每个连通块可以向外连 $\min{(k,a_i)}$ 条边。而使原图联通显然至少需要 $p-1$ 条边，形式话的来讲，我们能在第二步使图联通这个条件等价于 $\sum{\min {(siz_i,k)}} \ge 2(p-1)$。

这样的话我们再来考虑第一步，我们需要最大化左边，最小化右边。此时由于这个式子只与各个联通块的大小和连通块的数量有关，我们可以用并查集求出初始图的连通块信息，将加边操作转化为联通块的合并，联通块合并使用优先队列维护即可，时间复杂度 $O(m+n\log{n})$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
inline int read(){
	int f=1,w=0;
 	char c=getchar();
 	while(c<'0'||c>'9'){
 		if(c=='-')	f=-1;
 		c=getchar();
	}
	while(c>='0'&&c<='9'){
	 	w=(w<<1)+(w<<3)+(c^48);
	 	c=getchar();
	}
	return f*w;
}
int fa[N];
int find(int x){
	if(fa[x]==x)	return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	x=find(x);
	y=find(y);
	if(x==y)	return;
	fa[x]=y;
}
int a[N];
int n,m,k;
priority_queue <int, vector<int> , greater <int> > q;
int main(){
	n=read();
	m=read();
	k=read();
	for(int i=1;i<=n;i++)	fa[i]=i;
	for(int i=1;i<=m;i++){
		int x,y;
		x=read();
		y=read();
		merge(x,y);
	}
	for(int i=1;i<=n;i++){
		a[find(i)]++;
	}
	int cnt=0;
	int ans=0;
	for(int i=1;i<=n;i++){
		if(a[i]){
			q.push(a[i]);
			cnt++;
			ans+=min(a[i],k);
		}
	}
	if(ans>=2*(cnt-1)){
		printf("0\n");
		return 0;
	}
	int res=0;
	while(q.size()>=2){
		int x=q.top();
		q.pop();
		int y=q.top();
		q.pop();
		cnt--;
		ans-=min(x,k);
		ans-=min(y,k);
		ans+=min(x+y,k);
		res++;
		if(ans>=2*(cnt-1)){
			break;
		}
		q.push(x+y);
	}
	cout<<res<<endl;
	return 0;
}
```

---

## 作者：Composite_Function (赞：0)

首先由树的性质可以知道，如果一个图有 $n$ 个连通块，那么再连 $n - 1$ 条边就可以使图联通。

那么可以列出式子，如果有 $n$ 个连通块，每个连通块的大小为 $a _ i$ 那么需要满足：

$$\sum ^ n _ {i = 1} \min(a_i, k) \ge 2(n-1)$$

移个项：

$$S = \sum ^ n _ {i = 1} \min(a_i, k) - 2(n-1) \ge 0$$

然后观察到要使这个式子成立，如果把两个大小为 $a_1,a_2$ 的连通块合并，设新的式子为 $S_0$ 那么：

$$S_0 - S = \min(a_1 + a_2, k) - \min(a_1, k) - \min(a_2, k) + 2$$

然后发现要使 $S_0-S$ 更大，那么 $a_1,a_2$ 要最小。

然后用个数据结构存就行了。

---

