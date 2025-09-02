# [ICPC 2017 WF] Mission Improbable

## 题目描述

这是一个春天的晴天，你即将见到 Patrick，他是你的密友和前犯罪伙伴。Patrick 因为在编程比赛中赌博而损失了大部分的钱，所以他需要再干一票。为此，他需要你的帮助，尽管你已经从犯罪生活中退休。你起初很不情愿，因为你不想回到过去的犯罪生活，但你觉得听听他的计划也无妨。

附近的一个仓库里有一批昂贵的消费品，Patrick 打算尽可能多地偷走这些物品。这需要找到进入建筑物的方法，制服保安，通过各种激光束——你知道的，通常的抢劫技巧。然而，仓库的核心部分配备了一个 Patrick 无法禁用的安全系统。这就是他需要你帮助的地方。

货物存放在大型立方体箱子中，所有箱子的尺寸相同。箱子整齐地堆叠在一起，形成一个三维网格。安全系统每小时使用三个摄像头拍摄这些堆叠：一个前置摄像头，一个侧面摄像头和一个顶部摄像头。前置摄像头的图像显示每列中最高堆叠的高度，侧面摄像头的图像显示每行中最高堆叠的高度，顶部摄像头的图像显示每个堆叠是否为空。如果安全系统检测到任何图像的变化，它就会发出警报。

一旦 Patrick 进入，他将确定堆叠的高度并发送给你。图 C.1 显示了网格的可能布局和每个摄像头的视图。

![](https://cdn.luogu.com.cn/upload/image_hosting/4lbj63c1.png)

图 C.1：高度网格和相应的摄像头视图。

![](https://cdn.luogu.com.cn/upload/image_hosting/pcswms8b.png)

图 C.2：抢劫后的可能高度网格

Patrick 想要尽可能多地偷走箱子。由于他无法禁用安全系统，他计划通过将剩余的箱子重新排列成堆叠，使得下一组摄像头图像保持不变。在上述示例中，可以偷走九个箱子。图 C.2 显示了一个可能的抢劫后配置，看起来与安全系统相同。

Patrick 请求你帮助他确定在不被检测到的情况下可以偷走的最大箱子数量。你会帮助他完成这最后一票吗？

## 说明/提示

时间限制：1 秒，内存限制：512 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5 5
1 4 0 5 2
2 1 2 0 1
0 2 3 4 4
0 3 0 3 1
1 2 2 1 1
```

### 输出

```
9
```

## 样例 #2

### 输入

```
2 3
50 20 3
20 10 3
```

### 输出

```
30
```

# 题解

## 作者：CSPAK_Zhangxiuqi0011 (赞：19)

## 题目简述
给定一个由边长为 $1$ 的正方体组成的立体图形，长，宽分别为 $r,c$。求最多取掉多少个小正方体，使得这个立体图形的三视图不变。
## 思路
题目中要我们取掉最多的小正方体，很容易转化成放最少的小正方体。  
首先，我们考虑俯视图。  
俯视图很简单，其实就是在**之前有小正方体**的地方放一个箱子。于是假设 $(i,j)$ 处原来有小正方体，则这个位置取走了 $a_{i,j}-1$ 个小正方体。这个我们在输入的时候就可以解决。  
接下来考虑正视图和侧视图。  
不难发现，每行/列的正/侧视图取决于这行/列中最高的那一个位置。那么，很容易想到，我们可以偷一点懒，假设这行/列最高的位置放了 $x$ 个小正方体，那么在这行/列只选一个位置放 $x$ 个小正方体不就行了吗？  
于是，对于每一行/列，我们又放回去了 $x-1$ 个小正方体。需要注意的问题是：**如果这一行这一列根本没有小正方体，那么直接跳过，否则会出错**。  
这道题就做完了吗？并没有。  
很容易发现一种情况，举个例子说明：假如这个立体图形就是一个高度为 $4$ 的长方体呢？  
按照刚才我们的做法，先取掉了 $3$ 个小正方体，然后第 $1$ 行和第 $1$ 列最高的都是 $4$，各放回去 $3$ 个小正方体，最后取走了 $-3$ 个小正方体。这个答案很明显是不对的。  
那么，问题出在哪了呢？  
很容易想到，当某一行和某一列的最高高度相等的时候（假设是 $y$），在这一行这一列的交点直接放 $y$ 个小正方体肯定比各在其他位置放 $y$ 个小正方体更优。于是遇到这种情况，直接在两列的交点放置即可，在上面基础上又少了 $y-1$ 个小正方体。  
这道题做完了吗？还是没有。  
我们再看一种情况：
```
3 3 3
3 3 3
3 3 3
```
按照刚才的做法，发现每行每列的最大高度都相同。于是，我们在每个交点处都放置 $3$ 个小正方体。放置之后的图和原图一样。  
但是我们很容易发现，有一种方式是更优的：
```
3 1 1
1 3 1
1 1 3
```
也就是说，有些交点是根本没有必要放置的。  
现在我们要解决的问题，就变成了：如何找到正确的交点？  
观察上面的那个例子，可以发现，在我选了对角线三个点放 $3$ 个小正方体后，其他行/列都已经不用再放了。也就是说，每一行/列最好只有一个交点放小正方体。为什么是最好呢？很容易理解：
```
1 3 1
1 1 1
1 3 1
```
如图，很明显第 $1,3$ 行和第 $2$ 列最大值相等。我们在上面那个交点放了 $3$ 个小正方体后，虽然第 $2$ 列已经放好了，但是第 $3$ 行的高度 $3$ 只能放在第 $2$ 列。我们先把这个问题放在一边。  
提到**交点**，可以想到**二分图**：  
将每一行作为左部点，每一列作为右部点，如果某行和某列最大值相等，就把对应点连边。做二分图最大匹配，如果这一行匹配上了，令这一行的最大值为 $z$，则节省了 $z-1$ 个方块。  
看到这里，我们会发现刚才上面丢下的问题也被解决了：在上面的例子中，第 $1$ 行和第 $2$ 列匹配上了，但是第 $3$ 行失配了，正好第 $2$ 列在上面放了一个 $3$，相当于第 $2$ 列放过了，第 $3$ 行只能老老实实放 $3$ 个方块，不能像上面的交点一样从原来的 $6$ 个方块节省到 $3$ 个方块（可以自己理解一下）。  
那么有的同学就会问了（~~为啥会问~~）：每行匹配上的贡献不一定一样，为什么不用做带权最大匹配呢？  
我们仔细想一想：我们刚才连边的条件是啥？是**一行和一列最大值一样**！所以若左部点（对应的行） $i$ 和 $j$ 最大值不同的时候，不管怎么匹配，都不会发生冲突（因为它们不可能联通）。如果最大值相同呢？那么不管哪个点匹配上了，只要数量相同，都是一样的。  
这道题做完了吗？仍然没有。  
我们再看一种情况：  
```
5 0
0 3
3 0
```
可以发现，图中第 $3$ 行和第 $2$ 列最大值相等，直接在交点处放 $3$ 个小正方体更省事。但是原来第 $3$ 行第 $2$ 列这个位置并没有小正方体啊！如果放置了，则会导致俯视图改变，这里我们只能老老实实的在原本的位置放。所以，我们在连边之前一定要加一个判断条件：**该行该列的交点处原本有小正方体**（上面第 $1$ 行多加个 $5$ 是为了避免第 $2$ 行和第 $1$ 列最大值相等的情况，方便叙述，可以不看第一行）。  
剩下的就是二分图板子啦！  
## Code
温馨提示：学习是给自己学的，请不要抄袭他人代码。  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a[105][105],x[105],y[105],vis[105],used[105];
vector<int>ve[105];
int find(int now){//匈牙利算法板子 
	int l;
	l = ve[now].size();
	for(int i = 0;i<l;i++){
		if(vis[ve[now][i]]){
			continue;
		}
		vis[ve[now][i]] = 1;
		if(!used[ve[now][i]] || find(used[ve[now][i]])){
			used[ve[now][i]] = now;
			return 1;
		}
	}
	return 0;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	int ans;
	ans = 0;
	for(int i = 1;i<=n;i++){
		for(int j = 1;j<=m;j++){
			cin>>a[i][j];
			if(a[i][j]){
				ans = ans+a[i][j]-1;//处理俯视图情况（即只留1个小正方体） 
				x[i] = max(x[i],a[i][j]);
				y[j] = max(y[j],a[i][j]);//计算行和列最大值 
			}
		}
	}
	for(int i = 1;i<=n;i++){
		if(!x[i]){//如果这一行没有小正方体，直接跳过，要不然走到下面去的话ans值会减一 
			continue;
		}
		ans = ans-x[i]+1;
	}
	for(int i = 1;i<=m;i++){
		if(!y[i]){//同理 
			continue;
		}
		ans = ans-y[i]+1;
	}
	for(int i = 1;i<=n;i++){
		for(int j = 1;j<=m;j++){
			if(x[i] == y[j] && a[i][j]){//一定要判断这个交点处是否有小正方体！ 
				ve[i].push_back(j);
			}
		}
	}
	for(int i = 1;i<=n;i++){
		memset(vis,0,sizeof(vis));
		if(find(i)){//是否能匹配上 
			ans = ans+x[i]-1;//在交点处放置，可以节省一些小正方体 
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：myyes (赞：5)

二分图最大匹配好题，相当的规范。

由于三视图不变，每个有箱子的位置都必须留一个数，且取完箱子后每行每列的最大值都必须不变。

于是我们先把所有箱子都取走，再在一些格子上放回去，使得放回去的箱子子最少。显然如果在一个格子上放箱子同时满足了一行一列的最大值会省去一些箱子。

考虑将行看成左边 $n$ 个点，列看成右边 $n$ 个点，第 $i$ 行 $j$ 列的最大值相等就连边 $i,j$，这样就转化成了一个二分图匹配问题。跑匈牙利即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int cnt=1,head[1000010],last[2000010],go[2000010],seat[1000010],use[1000010],a[110][110],n,m,L[1000010],R[1000010];
long long ans;
void add(int a,int b){
  go[++cnt]=b;
 last[cnt]=head[a];
  head[a]=cnt;
   }
bool sit(int a,int bian)
  {
  	if(use[a]==bian)return 0;
  	use[a]=bian;
   for(int i=head[a];i;i=last[i]){
   	int v=go[i];
  if(!seat[v]||sit(seat[v],bian)){
  	seat[v]=a;
  	return 1;
  }
   }
return 0;
  }
int main()
 {
   scanf("%d%d",&n,&m);
 for(int i=1;i<=n;i++) 
  {for(int j=1;j<=m;j++)
 {
  scanf("%d",&a[i][j]);
 if(a[i][j]){ans+=a[i][j]-1;
}
  L[i]=max(L[i],a[i][j]);
   R[j]=max(R[j],a[i][j]) ;
    }
  }
 for(int i=1;i<=n;i++)
  {
 if(L[i]) ans-=L[i]-1;
   }
    for(int i=1;i<=m;i++)
     {if(R[i])ans-=R[i]-1;}
    for(int i=1;i<=n;i++)
 {
 	for(int j=1;j<=m;j++)
 	 {
 	   if(L[i]==R[j]&&a[i][j]){add(i,j) ;}
 	  }
 }
  for(int i=1;i<=n;i++)
  {if(sit(i,i))ans+=L[i]- 1;}
  cout<<ans<<endl;
}
```


---

## 作者：ZHR100102 (赞：2)

还不错的二分图建模题，和士兵占领那题挺相似的。

# 简要题意

给你一个立体图形的三视图，你需要求出总方块数减去摆出这个立体图形的最少方块数的值。

# 转化

首先考虑最简单的俯视图，只要当前这个位置不为 $0$ 就必须强制放一个方块。因此我们可以把非 $0$ 的方块高度全部减 $1$ 来先处理掉这个情况。

接下来考虑如何处理左视图和主视图。观察后不难发现，这两个视角给答案的限制就是要求每一行或者每一列都有一个方格的高度达到某个值，其他的方格都可以不要。

我们先采取最劣的贪心策略，每一行每一列都先选不同的方格以满足答案的要求，后面再来调整，答案就是每行每列高度之和。

那么这样的贪心能不能进一步对方案优化呢？显然，当存在某一行和某一列所需高度相等，且**该行该列相交的格子原高度不为 $0$ 时**，我们可以将这一行和这一列所选的方格并成一个方格，这样代价就更小了。

同时不难发现，每一行最多与一列相匹配，每一列同理，不然一定是不优的。这就符合了二分图的性质，左部点就是代表行的点，右部点就是代表列的点，原高度不为 $0$ 的方格就充当二分图上的边，跑二分图匹配就是尽可能将行列所用的方格合并到一块，以减少花费。


跑二分图最大匹配即可。注意这里可以不跑最大权匹配，因为不同高度的行和列根本不会在一个连通块中，所以相当于只要每个连通块内做权值都相同的普通二分图最大匹配即可。

跑完最大匹配，让之前选的方块数减掉最大匹配数就是最小需要使用的方块数。

我使用了网络流来实现，时间复杂度为 EK 或 Dinic 的复杂度，或者写匈牙利也是可以的。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int K=105,N=1005,M=100005;
const ll inf=0x3f3f3f3f3f3f3f3f;
int n,m,hx[K],hy[K],a[K][K],s,t;
ll smans=0,sma=0;
int h[N],cur[N],idx=1;
struct Edge{
	int v,ne;
	ll c;
}e[M];
void add(int u,int v,ll c)
{
	e[++idx]={v,h[u],c};
	h[u]=idx;
}
void addeg(int u,int v,ll c)
{
	add(u,v,c);
	add(v,u,0);
}
int getid(int id,int tp)
{
	return (id+tp*n);
}
ll d[N];
bool BFS()
{
	memset(d,0,sizeof(d));
	d[s]=1;
	queue<int>q;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=h[u];i;i=e[i].ne)
		{
			int v=e[i].v;ll c=e[i].c;
			if(d[v]==0&&c)
			{
				d[v]=d[u]+1;
				q.push(v);
				if(v==t)return 1;
			}
		}
	}
	return 0;	
}
ll dfs(int u,ll mf)
{
	if(u==t)return mf;
	ll sm=0;
	for(int i=cur[u];i;i=e[i].ne)
	{
		int v=e[i].v;ll c=e[i].c;
		cur[u]=i;
		if(d[v]==d[u]+1&&c)
		{
			ll res=dfs(v,min(c,mf));
			e[i].c-=res;
			e[i^1].c+=res;
			mf-=res;
			sm+=res;
			if(mf==0)break;
		}
	}
	if(sm==0)d[u]=0;
	return sm;
}
ll dinic()
{
	ll flow=0;
	while(BFS())
	{
		memcpy(cur,h,sizeof(h));
		flow+=dfs(s,inf);
	}
	return flow;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	s=n+m+1,t=n+m+2;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
			hx[i]=max(hx[i],a[i][j]);
			hy[j]=max(hy[j],a[i][j]);
			smans+=(a[i][j]>0);sma+=a[i][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]>0&&hx[i]==hy[j])addeg(getid(i,0),getid(j,1),1);
		}
	}
	for(int i=1;i<=n;i++)addeg(s,getid(i,0),1);
	for(int i=1;i<=m;i++)addeg(getid(i,1),t,1);
	ll flow=dinic();
	for(int i=h[s];i;i=e[i].ne)
	{
		int v=e[i].v;ll c=e[i].c;
		if(c&&hx[v])smans+=hx[v]-1;
	}
	for(int i=1;i<=m;i++)if(hy[i])smans+=hy[i]-1;
	cout<<sma-smans;
	return 0;
}
```

# 总结

这题就是根据贪心，尽可能多选行和列共用的方格，然后其他行和列自己单独选一个格子就行，同时还运用到了一个二分图性质。还是很不错的一道题的。

---

## 作者：Betrayer_of_love (赞：1)

## 思路：

可以简化一下问题，假设 Patrick 把箱子都拿走但是原来有箱子的位置留下一个，现在要放箱子使得每行每列最大值都满足，最少放多少个。

设第 $i$ 行的最大值是 $H(i)$，第列的是 $W(i)$。没有箱子的行可以不用去管，假设每行每列都有一个地方放 $\frac{H(i)}{W(i)}$，现在如果有一个 $H(i)=W(j)$，而且原来 $(i,j)$ 位置上有箱子，那么就可以在 $(i,j)$ 位置上放 $H(i)$ 个箱子同时满足第 $i$ 行与第 $j$ 列，获得 $H(i)-1$ 的收益。

按照以上思路，这题就做完了，统一答案随便搞一下即可。

## 代码：


```cpp
#include<bits/stdc++.h>
#define il inline
#define vd void
using namespace std;
typedef long long ll;
il int gi() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) {
		if (ch == '-')f = -1;
		ch = getchar();
	}
	while (isdigit(ch))x = x * 10 + ch - '0', ch = getchar();
	return x * f;
}
ll A[101][101], H[101], W[101];
int S, T, fir[210], dis[30010], nxt[30010], w[30010], id = 1;
ll cost[30010];
il vd link(int a, int b, ll d) {
	nxt[++id] = fir[a], fir[a] = id, dis[id] = b, w[id] = 1, cost[id] = d;
	nxt[++id] = fir[b], fir[b] = id, dis[id] = a, w[id] = 0, cost[id] = -d;
}
il bool Mincost(ll&total) {
	static ll dist[210];
	static int que[210], hd, tl, lst[210];
	static bool inq[210];
	memset(dist, 63, sizeof dist);
	dist[S] = 0;
	hd = tl = 0;
	que[tl++] = S;
	inq[S] = 1;
	lst[T] = 0;
	while (hd ^ tl) {
		int x = que[hd];
		for (int i = fir[x]; i; i = nxt[i])
			if (w[i] && dist[dis[i]] > dist[x] + cost[i]) {
				dist[dis[i]] = dist[x] + cost[i], lst[dis[i]] = i;
				if (!inq[dis[i]])inq[dis[i]] = 1, que[tl++] = dis[i], tl %= 210;
			}
		inq[x] = 0, ++hd, hd %= 210;
	}
	for (int i = lst[T]; i; i = lst[dis[i ^ 1]])w[i] = 0, w[i ^ 1] = 1, total -= cost[i];
	return lst[T];
}
int main() {
	int n = gi(), m = gi();
	ll ans = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			A[i][j] = gi();
			if (A[i][j])ans += A[i][j] - 1;
			H[i] = std::max(H[i], A[i][j]);
			W[j] = std::max(W[j], A[i][j]);
		}
	for (int i = 1; i <= n; ++i)if (H[i])ans -= H[i] - 1;
	for (int i = 1; i <= m; ++i)if (W[i])ans -= W[i] - 1;
	S = 0, T = n + m + 1;
	for (int i = 1; i <= n; ++i)link(S, i, 0);
	for (int i = 1; i <= m; ++i)link(i + n, T, 0);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if (A[i][j] && H[i] == W[j] && H[i])link(i, n + j, -H[i] + 1);
	while (Mincost(ans));
	printf("%lld\n", ans);
	return 0;
}

```


**完结撒花，谢谢Thanks♪(･ω･)ﾉ**

---

## 作者：yizhiming (赞：1)

被诈骗了。

补充一下另外一篇题解没有涉及的一些细节。

### 题目大意

给定一个 $n\times m$ 的矩形 $a$，表示俯视图下每个位置有几个小方块，要求从中拿走 $k$ 个小方块，并重新排列剩余的小方块，使得改变后的左视图、正视图、俯视图不变，求最大的 $k$。

$1\leq n,m \leq 100,0\leq a_{i,j} \leq 10^9$。

### 题目分析

首先想视图的性质，我们至少要先钦定每个原本有小方块的位置至少有一个，所以先将全体有值的都减去 $1$，再考虑后面的操作。

此时若想满足视图，只需要对应行列的最大值和之前相同即可，所以我们先求出行列最大值，我们称第 $i$ 行的最大值为 $mx1_i$，第 $j$ 列最大值为 $mx2_j$。

首先此时对于每一行每一列分别填上一个对应最大值的小方块柱即可，但是此时有什么问题呢？如果只求 $mx1,mx2$ 的和作为所需要的方块，那么既有可能比原本的方块数多，也有可能存在更优做法。

这种情况出现是因为存在一个坐标 $(i,j)$ 使得他既是 $mx1_i$ 又是 $mx2_j$，所以算重了，显然可以将这种情况的两柱合并起来变得更优。

什么时候可以合并呢？首先第 $i$ 行第 $j$ 列的最大值要相同，其次 $(i,j)$ 这个位置要有值，才能够匹配，此时问题就变成了满足条件的行列能够匹配，问匹配的最大值，因为行只会连列，所以就是一个二分图，直接求二分图最大匹配即可，使用网络流解决。

虽然每个行只能匹配一列，但是由于流量相同，所以一定会满流，也就是坐不点唯一对应一个右部点。

跑出来的最大流就是多算的方块个数。

### Code

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#define int long long
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 1e4+5;
int mp[105][105],n,m;
int S,T,inf = 1e18;
int head[N],tote=1;
struct aa{
	int nxt,to,val;
}edge[N*20]; 
void link(int u,int v,int w){
	edge[++tote] = (aa){head[u],v,w};head[u] = tote;
	edge[++tote] = (aa){head[v],u,0};head[v] = tote;
}
int dep[N];
queue<int>q;
bool bfs(){
	q.push(S);
	memset(dep,0,sizeof(dep));
	dep[S] = 1;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(int i=head[u];i;i=edge[i].nxt){
			int now = edge[i].to;
			if(!dep[now]&&edge[i].val){
				dep[now] = dep[u]+1;
				q.push(now);
			}
		}
	}
	return dep[T];
}
int dfs(int u,int f){
	if(u==T){
		return f;	
	} 
	int used = 0;
	for(int i=head[u];i&&f;i=edge[i].nxt){
		int now = edge[i].to;
		if(dep[now]==dep[u]+1&&edge[i].val){
			int w = dfs(now,min(f,edge[i].val));
			f-=w;used+=w;
			edge[i].val-=w;edge[i^1].val+=w;
		}
	}
	if(!used){
		dep[u] = 0;
	}
	return used;
}
int flow;
void dinic(){
	flow = 0;
	while(bfs()){
		flow+=dfs(S,inf);
	}
}
int mx1[N],mx2[N];
signed main(){
	n = read();m = read();
	int res = 0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			mp[i][j] = read();
			res+=max(0ll,mp[i][j]-1);
			mx1[i] = max(mx1[i],mp[i][j]-1);
			mx2[j] = max(mx2[j],mp[i][j]-1);
		}
	}
	S = 0;T = n+m+1;
	for(int i=1;i<=n;i++){
		res-=mx1[i];
		link(S,i,mx1[i]);
	}
	for(int i=1;i<=m;i++){
		res-=mx2[i];
		link(i+n,T,mx2[i]);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mx1[i]==mx2[j]&&mp[i][j]){
				link(i,j+n,inf);
			}
		}
	}
	dinic();
	cout<<res+flow<<"\n";
	return 0;
}

```


---

## 作者：FReQuenter (赞：0)

考虑三视图相同：

上：每个有箱子的位置至少有一个。

其他两个面：最大值和原来相同。

一个缩减的方式是把所有原来有箱子的地方全部变成一个箱子，每行和每列保证有一竖列箱子高为原来这一行（列）的最大值。

然后发现有的地方 $(i,j)$ 可以同时作为 $i$ 行和 $j$ 列的最大值，即 $i$ 行和 $j$ 列的最大值相同。

那么可以在这种点 $i$ 向 $j$ 连边，会构成一个二分图。如果当前的 $i$ 可以匹配，那么它就可以同时占 $i$ 行和 $j$ 列的最大值（再减少最大值的箱子数减一）。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[255][255],ga[255][255],vis[255],mat[255],mc[255],mr[255];
bool sp(int x){
    for(int i=1;i<=m;i++){
        if(ga[x][i]&&!vis[i]){
            vis[i]=1;
            if(!mat[i]||sp(mat[i])){
                mat[i]=x;
                return 1;
            }
        }
    }
    return 0;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>a[i][j];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) mc[i]=max(mc[i],a[i][j]);
	}
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;i++) mr[j]=max(mr[j],a[i][j]);
	}
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){
		if(a[i][j]&&mc[i]==mr[j]){
			ga[i][j]=1;
		}
	}
	int lft=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) lft+=(a[i][j]>0);
	}
	for(int i=1;i<=n;i++) if(mc[i]) lft+=mc[i]-1;
	for(int i=1;i<=m;i++) if(mr[i]) lft+=mr[i]-1;
	for(int i=1;i<=n;i++){
		if(!mc[i]) continue;
		for(int j=1;j<=m;j++) vis[j]=0;
		if(sp(i)) lft-=mc[i]-1;
	}
	int sum=0;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) sum+=a[i][j];
	cout<<sum-lft;
}
```

---

