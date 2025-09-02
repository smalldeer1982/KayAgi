# The Maximum Subtree

## 题目描述

定义一个大小为   $n$ 的树是好的，为存在一种给每一个节点   $i$ 赋两个值   $l_i,r_i$ 分别代表线段的左端点和右端点的方案，使得两个点   $u,v$ 在树上有边当且仅当   $u,v$ 所代表的线段有交集。

现在给定一棵大小为   $n$ 的树，让你求出最大的好的子树的大小。多组数据。

本题中“子树”指树上的一个连通子图。

## 样例 #1

### 输入

```
1
10
1 2
1 3
1 4
2 5
2 6
3 7
3 8
4 9
4 10
```

### 输出

```
8
```

# 题解

## 作者：nofind (赞：4)

题意:https://www.luogu.org/problem/CF1238F

考虑一颗树的线段会长什么样子:

![](https://cdn.luogu.com.cn/upload/image_hosting/o9xtmjfe.png)

发现这是一个毛毛虫:https://www.luogu.org/problem/P3174

于是用上面那道题的方法做即可

考虑毛毛虫的主链为$a_1,a_2...a_k$,一个点的出度为$val[i]$

那么这条毛毛虫的点数为:$(\sum\limits_{i=1}^{k}val[a_i])-(k-2)$,其中$-(k-2)$是因为除了两个链首,链上的每个点都被多算了一次

推一下式子就变成:$ans=(\sum\limits_{i=1}^{k}{val[i]-1})+2$

之后跑带权直径即可

code:
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=3*1e5+10;
int T,n,cnt,st,ed,ans;
int head[maxn],val[maxn];
struct edge
{
	int to,nxt;
}e[maxn<<1];
inline void add(int u,int v)
{
	e[++cnt].nxt=head[u];
	head[u]=cnt;
	e[cnt].to=v;
	val[u]++;
}
void dfs(int x,int fa,int dis)
{
	if(dis>ans)ans=dis,st=x;
	for(int i=head[x];i;i=e[i].nxt)
	{
		int y=e[i].to;
		if(y==fa)continue;
		dfs(y,x,dis+val[y]);
	}
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)head[i]=0,val[i]=-1;
		cnt=0;
		for(int i=1;i<n;i++)
		{
			int u,v;scanf("%d%d",&u,&v);
			add(u,v);add(v,u);
		}
		ans=-1;dfs(1,0,val[1]);ans=-1;dfs(st,0,val[st]);
		printf("%d\n",ans+2);
	}
	return 0;
}
```


---

## 作者：RuntimeErr (赞：1)

考虑按照样例模拟出以某个点为线段中心时什么样的子树（联通子图）可以选。

显然**包含**于线段中的部分只能塞它的子节点而不能塞子节点的子树（不然重叠就不满足条件了），只有线段**两端**除了塞子节点还可以再塞多级子节点。不难发现，这就是一个**毛毛虫**。~~于是把 P3174 放过来就好了（~~

```cpp
const int N=3e5+10;

int n,ans=0;
vector<int>e[N];
int f[N],a[N];//f[u]:以u为腰的毛毛虫大小(边数);a[u]:u的度数

void dfs(int u,int fa){
	f[u]=a[u];
	for(int v:e[u]){
		if(v==fa)continue;
		dfs(v,u);
		ans=max(ans,f[u]+f[v]-1);//合并两条毛毛虫链
		f[u]=max(f[u],a[u]+f[v]-1);
	}
}

void solve(){
    read(n);ans=0;
    for(int i=1;i<=n;++i)e[i].clear(),f[i]=a[i]=0;
    for(int i=1;i<n;++i){
        int u,v;read(u),read(v);
        e[u].push_back(v),e[v].push_back(u);
        ++a[u],++a[v];
    }
    dfs(1,0);
    printf("%d\n",ans+1);
}

int main(){
    int t;read(t);
    while(t--)solve();
    return 0;
}
```

---

## 作者：lgswdn_SA (赞：1)

这种很复杂的描述其实能够识别出来是强行加戏……

考虑什么样的树是好的。对于一个线段 $[l,r]$ 作为子树的根，假设和它重叠的有 $1,2,3,...,p$ 号节点，那么这些节点中最多有两个节点是可以继续有儿子节点的。为什么呢？因为这两个可以继续有儿子节点的一定处于 $[l,r]$ 的两端，又因为 $1,2,...,p$ 互不重叠，所以最多存在两个。

![image.png](https://i.loli.net/2020/09/14/apC5NtHYnALZTmz.png)

这就是[毛毛虫](https://www.luogu.com.cn/problem/P3174)的定义。于是我们相当于找树上最大毛毛虫即可。

~~结果写着写着毛毛虫的细节错了一大堆~~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+9;

struct edge {int to,nxt;}e[N*2]; int hd[N],tot;
void add(int u,int v) {e[++tot]=(edge){v,hd[u]};hd[u]=tot;}

int n,g[N],h[N][2],ans;

void clear() {
	ans=0;
	for(int i=1;i<=n;i++) h[i][0]=h[i][1]=g[i]=0, hd[i]=0;
	for(int i=1;i<=tot;i++) e[i]=(edge){0,0};
	tot=0;
}

void dfs(int u,int fa) {
	int num=0;
	for(int i=hd[u],v;i;i=e[i].nxt) {
		num++;
		if((v=e[i].to)==fa) continue;
		dfs(v,u);
		if(g[v]>h[u][1]) h[u][1]=g[v];
		if(h[u][0]<h[u][1]) swap(h[u][0],h[u][1]);
	}
	num--;
	g[u]=1+h[u][0]+max(0,num-1);
	ans=max(ans,h[u][0]+h[u][1]+1+max(0,num-1));
}

int main() {
	int T; scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		clear();
		for(int i=1,u,v;i<n;i++)
			scanf("%d%d",&u,&v), add(u,v), add(v,u);
		dfs(1,0);
		printf("%d\n",ans);
	}
	return 0;
} 
```

---

## 作者：ifffer_2137 (赞：0)

小清新，感觉现在只会做这种思维步骤少的题了/kk
### 题意
定义一个大小为 $n$ 的树是好的，为存在一种给每一个节点 $i$ 赋两个值 $l_i,r_i$ 分别代表线段的左端点和右端点的方案，使得两个点 $u$，$v$ 在树上有边当且仅当 $u$，$v$ 所代表的线段有交集。

现在给定一棵大小为 $n$ 的树，让你求出最大的好的子树的大小,本题中“子树”指树上的一个连通子图。
### 分析
先考虑好树的性质，画图理解一下，会发现如果把线段画成一棵有根树的形状，当一条线段被其父亲完全包含时，它不能再含有自己的儿子，也就是叶子，否则它的父亲和它的儿子间就会有边，不合题意。

所以一条线段最多有两个非叶子儿子（因为必须跨过它的一个端点而不被它包含），又因为它的父亲会占据一边，所以它只能有一个非叶子儿子，特别的，根节点可以有两个。

这个时候题目就比较清晰了，考虑先钦定这个根，跑树形 DP。令 $dp_u$ 表示选定 $u$ 为非叶子节点时，$u$ 子树内的最大合法子树大小，则有：
$$dp_u=cnt_u+\max_{v\in son(u)}dp_v$$
其中 $cnt_u$ 为 $u$ 儿子数量，减去一个最大的儿子再加上 $u$ 本身，抵消了。然后如果是根节点就再求一个次大值，把另一个叶子换掉即可。

但这样是 $O(n^2)$ 的，我们可以考虑换根。

在第二次遍历时，维护 $u$ 子树外的答案 $k$，用来更新 $u$ 的子树 DP 最大和次大值，然后正常算答案。遍历儿子时，只需用除当前儿子外的子树 DP 最大值去转移，算出该儿子子树外的答案。

时间复杂度 $O(n)$，具体实现有一些细节建议阅读代码，~~换根感觉很难口述清楚~~。
### 代码
```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=3e5+5;
int T;
int n,ans;
vector<int> tr[maxn];
int mx[maxn],se[maxn],dp[maxn];
bool cmp(int a,int b){return a>b;}
void dfs1(int u,int f){
	dp[u]=1;
	for(int v:tr[u]){
		if(v==f) continue;
		dfs1(v,u);
		if(dp[v]>=mx[u]) se[u]=mx[u],mx[u]=dp[v];
		else if(dp[v]>se[u]) se[u]=dp[v];
	}
	if(!f){
		int cnt=tr[u].size();
		if(mx[u]) cnt--;if(se[u]) cnt--;
		dp[u]+=mx[u]+se[u]+cnt;
	}else{
		int cnt=tr[u].size()-1;
		if(mx[u]) cnt--;
		dp[u]+=mx[u]+cnt;
	}
}
void dfs2(int u,int f,int k){
	if(k>=mx[u]) se[u]=mx[u],mx[u]=k;
	else if(k>se[u]) se[u]=k;
	if(f){
		dp[u]=1;
		int cnt=tr[u].size();
		if(mx[u]) cnt--;if(se[u]) cnt--;
		dp[u]+=mx[u]+se[u]+cnt;
		ans=max(ans,dp[u]);
	}
	for(int v:tr[u]){
		if(v==f) continue;
		int p; if(dp[v]==mx[u]) p=se[u]; else p=mx[u];
		int cnt=tr[u].size()-1;
		if(p) cnt--;
		dfs2(v,u,1+p+cnt);
	}
}
signed main(){
	cin.tie(0),cout.tie(0);
	T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++) tr[i].clear(),dp[i]=mx[i]=se[i]=0;
		for(int i=1;i<n;i++){
			int u=read(),v=read();
			tr[u].eb(v),tr[v].eb(u);
		}
		dfs1(1,0);
		ans=dp[1];
		dfs2(1,0,0);
		cout<<ans<<endl;
	}
	return 0;
}
```

---

