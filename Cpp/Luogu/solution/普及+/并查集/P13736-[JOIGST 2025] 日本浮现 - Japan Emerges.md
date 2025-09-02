# [JOIGST 2025] 日本浮现 / Japan Emerges

## 题目描述

日本列岛的地壳运动十分激烈。

日本列岛的水域可以视为一个在南北方向上有 $H$ 行、在东西方向上有 $W$ 列的网格，从北到南第 $i$ 行、从西到东第 $j$ 列记为 $(i,j)$。

初始时有恰好 $N$ 个格子是**陆地**，其他格子均为**海洋**。这 $N$ 块陆地分别位于格子 $(R_1,C_1),(R_2,C_2),\ldots,(R_N,C_N)$。

日本列岛每天中午都会发生地壳运动。第 $t(t\ge 1)$ 日中午的地壳运动可以描述为如下的过程：

- 若一个格子 $(r,c)$ 满足 $1\le r\le H-1$，$1\le c\le W$ 且 $(r,c)$ 在早上（即地壳运动发生之前）为陆地、$(r+1,c)$ 在早上为海洋，那么在地壳运动发生之后，$(r+1,c)$ 也将成为陆地。

如果从任何一个为陆地的格子出发，都能通过“反复移动到东、西、南、北相邻的陆地格子”到达任何一个其他的为陆地的格子，那么称日本列岛是“连通的”。随着不断的地壳运动，日本列岛可能会在某个时候变成连通的。

判断日本列岛是否会通过若干次地壳运动变为连通的。如果可以，试求出至少需要经过几天才可以变为连通的。

## 说明/提示

#### 【样例解释 #1】

下图展示了初始时日本列岛的形态（深绿色为陆地，白色为海洋）：

![](https://cdn.luogu.com.cn/upload/image_hosting/bhooygf4.png)

第 $1$ 天之后，$(2,1),(2,3),(4,2),(4,3)$ 形成新的陆地。此时日本列岛并不连通（$(1,1)$ 无法通过反复向四个方向移动到达 $(4,4)$）。下图展示了第 $1$ 天之后日本列岛的形态（深绿色为初始时的陆地，浅绿色为新形成的陆地，白色为海洋）：

![](https://cdn.luogu.com.cn/upload/image_hosting/62bylxrx.png)

第 $2$ 天之后，$(3,1)$ 形成新的陆地。此时日本列岛连通了。下图展示了第 $2$ 天之后日本列岛的形态：

![](https://cdn.luogu.com.cn/upload/image_hosting/mhyugk4d.png)

日本列岛在 $2$ 次地壳运动后变为连通的。

该样例满足子任务 $3,4,5,6,7$ 的限制。

#### 【样例解释 #2】

日本列岛无法通过地壳运动变为连通的。

该样例满足子任务 $2,3,4,5,6,7$ 的限制。

#### 【样例解释 #3】

日本列岛在所有地壳运动之前就是连通的。

该样例满足子任务 $2,3,4,5,6,7$ 的限制。

#### 【数据范围】

- $1 \le H,W \le 2\times 10^5$；
- $2 \le N \le \min(H \times W,\ 2\times 10^5)$；
- $1 \le R_i \le H(1\le i\le N)$；
- $1 \le C_i \le W(1\le i\le N)$；
- $(R_i, C_i) \neq (R_j, C_j) (1\le i<j\le N)$。

#### 【子任务】

1. （$5$ 分）$W = 1$；
2. （$9$ 分）$N = 2$；
3. （$8$ 分）$H,W,N \le 500$；
4. （$28$ 分）$N \le 2000$；
5. （$13$ 分）$H \times W \le 2\times 10^5$；
6. （$13$ 分）$H \times N \le 2\times 10^5$；
7. （$24$ 分）无附加限制。

## 样例 #1

### 输入

```
4 4 5
1 1
1 3
3 2
3 3
4 4```

### 输出

```
2```

## 样例 #2

### 输入

```
3 3 2
1 1
3 3```

### 输出

```
-1```

## 样例 #3

### 输入

```
2 2 2
1 1
1 2```

### 输出

```
0```

# 题解

## 作者：_qhbd_ (赞：0)

# 思路
对于点 $(x,y)$：
- 若有 $(x',y)$ 满足 $x'>x$，那么经过 $x'-x-1$ 天后，它们连通。
- 若有 $(x',y-1)$ 满足 $x'>x$，那么经过 $x'-x$ 天后，它们连通。
- 若有 $(x',y+1)$ 满足 $x'>x$，那么经过 $x'-x$ 天后，它们连通。

考虑建图，点 $u$ 与点 $v$ 经过 $w$ 天连通，则有边 $u,v$ 边权为 $w$。然后求最大边权最小的生成树即可（其实就是求最小生成树）。

总边数是不会超过 $3\times N$。考虑点 $(x,y),(x_1,y),(x_2,y)$ 有 $x<x_1<x_2$，那么只需要 $(x,y)$ 向 $(x_1,y)$ 连边，$(x_1,y)$ 向 $(x_2,y)$ 连边即可。其他两种情况同理，第 $y$ 列的点最多分别向 $y,y-1,y+1$ 三列的某点各连一边。

有无解在于最小生成树能否成功构建。

建边要二分查找，需要最小生成树，时间复杂度 $O(n\log n)$
# code
```cpp
#include<bits/stdc++.h>
#define F first
#define S second
using namespace std;
const int N=2e5+5;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while('0'>ch||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
pair<int,int>tmp;
vector<pair<int,int>>W[N];
int h,w,n,x[N],y[N],fa[N],ans,num;
priority_queue<pair<int,pair<int,int>>>q;
inline int findfa(int x){return x==fa[x]?x:fa[x]=findfa(fa[x]);}
inline bool merge(int x,int y){
	x=findfa(x);
	y=findfa(y);
	if(x!=y){
		fa[x]=y;
		num++;
		return true;
	}
	return false;
}
int main(){
	h=read();
	w=read();
	n=read();
	for(int i=1;i<=n;i++){
		fa[i]=i;
		x[i]=read();
		y[i]=read();
		W[y[i]].emplace_back(x[i],i);
	}
	for(int i=1;i<=w;i++)sort(W[i].begin(),W[i].end());
	for(int i=1;i<=n;i++){
		auto it=lower_bound(W[y[i]].begin(),W[y[i]].end(),pair<int,int>{x[i]+1,0});
		if(it!=W[y[i]].end())	
			q.push({-(it->F-x[i]-1),{i,it->S}});
		it=lower_bound(W[y[i]-1].begin(),W[y[i]-1].end(),pair<int,int>{x[i],0});
		if(it!=W[y[i]-1].end())
			q.push({-(it->F-x[i]),{i,it->S}});
		it=lower_bound(W[y[i]+1].begin(),W[y[i]+1].end(),pair<int,int>{x[i],0});
		if(it!=W[y[i]+1].end())
			q.push({-(it->F-x[i]),{i,it->S}});
	}
	while(!q.empty()&&num<n-1){
		if(merge(q.top().S.F,q.top().S.S))
			ans=q.top().F;
		q.pop();
	}
	printf("%d\n",num<n-1?-1:-ans);
	return 0;
}
```

---

## 作者：reinforest (赞：0)

思维难度：中位黄。

细节难度：上位绿。

二分+双指针+并查集。

首先二分答案都好说。因为如果答案 $d$ 满足条件则 $d+1$ 就一定满足条件。

设二分到的答案是 $d$。

我们需要把点按照纵坐标分组，分完组后按照横坐标排序。我们首先对纵坐标相同的点考虑，如果有两个点 $(a,b)$ 和 $(c,b)$，不妨设 $a<c$，它们满足 $a+d+1 \geq b$ 就连通，这是简单的。

然后考虑纵坐标相邻的点，设这两个纵坐标是 $i$ 和 $i+1$。考虑双指针维护，分别设指针为 $j$ 和 $k$。实际上是如果 $j$ 所对应的区间与 $k$ 所对应的区间有交则连边。

双指针的时候，当我们枚举到一个 $j$ 的时候，我们需要找到第一个与这个区间相交的 $k$，连通性的更新必须从这里开始。

然后贪心地考虑，我们不妨一直累加到最大的 $k$，满足其所对应的区间与 $j$ 所对应的区间相交。然后**令 $k$ 不动**，往后累加 $j$。这样的 $k$ 一定是不劣的。
因为这样的 $k$ 可以尽可能的往后与更多的区间相交，且不会舍弃掉 $j$ 累加以后可能的区间。 

然后就做完了。这道题细节比较多，尤其是双指针。

这里给出一组样例：

```
input:
7 2 3
1 1
3 2
5 1

output:
2
```

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr ll maxn=2e5+5,inf=1e18;
vector<ll> c[maxn];//第 c 列中的点
struct poi{
	ll x,y;
}arr[maxn];
bool cmp(ll a,ll b){
	return arr[a].x<arr[b].x;
}
ll h,w,n;
struct DSU{
	ll fa[maxn];
	void init(){
		for(int i=1;i<=n;i++)fa[i]=i;
	}
	ll fid(ll x){
		if(fa[x]==x)return x;
		else return fa[x]=fid(fa[x]);
	}
	void merg(ll x,ll y){
		ll fx=fid(x),fy=fid(y);
		fa[fx]=fy;
	}
	void update(){
		for(int i=1;i<=n;i++)fa[i]=fid(i);
	}
	bool connect(){
		update();
		for(int i=1;i<n;i++){
			if(fa[i]!=fa[i+1])return false;
		}
		return true;
	}
}T;
bool check(ll md){
	T.init();
	for(int i=1;i<=w;i++){
		for(int j=1;j<c[i].size();j++){
			if(arr[c[i][j-1]].x+md+1>=arr[c[i][j]].x){
				T.merg(c[i][j-1],c[i][j]);
			}
		}
	}
	for(int i=1;i<w;i++){
		for(int j=0,k=0;j<c[i].size();j++){
			while(k<c[i+1].size() && arr[c[i+1][k]].x+md<arr[c[i][j]].x)k++;
			bool flg=false;
			while(k<c[i+1].size() && arr[c[i+1][k]].x<=arr[c[i][j]].x+md){
				flg=true;
				T.merg(c[i+1][k],c[i][j]);
				k++;
			}
			if(flg)k--;
		}
	}
	return T.connect();
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0); 
	cin>>h>>w>>n;
	for(int i=1;i<=n;i++){
		cin>>arr[i].x>>arr[i].y;
		c[arr[i].y].push_back(i);
	}
	for(int i=1;i<=w;i++){
		sort(c[i].begin(),c[i].end(),cmp);
	}
	ll l=0,r=2*h,ans=inf,md;
	while(l<=r){
		md=(l+r)>>1;
		if(check(md)){
			r=md-1;
			ans=md;
		}else{
			l=md+1;
		}
	}
	if(ans>=inf)cout<<-1<<"\n";
	else cout<<ans<<"\n";
	return 0;
}
```

---

