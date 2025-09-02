# [POI 2011] INS-Inspection

## 题目描述

Byteotian Railways（BR）的铁路网络由双向轨道组成，这些轨道连接某些车站对。每对车站最多由一段轨道连接。此外，从每个车站到每个其他车站都有唯一的路线。（该路线可能由几段轨道组成，但不能经过任何车站多于一次。）Byteasar 是 BR 的一名卧底检查员。他的任务是选择一个车站（记为 $S$）作为他的行动中心，并前往所有其他车站。他的旅程应如下进行：Byteasar 从车站 $S$ 出发。接下来，他选择一个尚未检查的车站，沿最短路径（当然是乘火车）前往该车站，检查车站，然后返回 $S$。BR 的腐败员工互相警告 Byteasar 的到来。为了欺骗他们，Byteasar 选择下一个要检查的车站，使得他从车站 $S$ 出发的方向与上次不同，即沿着从 $S$ 出发的不同轨道段。每个车站（除了 $S$）恰好被检查一次。在检查完最后一个车站后，Byteasar 不返回 $S$。沿每段轨道的旅行时间相同：一小时。Byteasar 打算将所有车站都考虑为初始车站 $S$。对于每个车站，他想知道检查剩余车站的顺序，以最小化总旅行时间，前提是对于该特定 $S$ 这是可能的。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
9
3 6
2 4
2 6
2 5
1 7
2 7
8 9
7 8```

### 输出

```
-1
23
-1
-1
-1
-1
-1
-1
-1```

# 题解

## 作者：Fading (赞：15)

思维定式？

这是我们今天考试的题目...

大家都搞什么换根$dp$求最长链，有必要吗？？？

如果一个点不是重心，那么答案一定是$-1$。

否则，就是深度和$-$最长链。

注意，如果重心子树最大值为$\frac n2$，那么最长链只能在这个子树里选。

由于一棵树重心最多只有两个，我们暴力做就好了。

代码就不贴了，很好写...

---

## 作者：子谦。 (赞：5)


这道题的题面有点问题，如果按照题面做，应该是A不了的，下面引用一下评论里@[REM_001](https://www.luogu.org/space/show?uid=87316)的翻译

>一棵n个节点的树，行动中心S从1->N。从S出发前往任意一个未标记到的点(沿树上两点的唯一路径走)，标记该节点，然后返回S。相邻两次行动所经过的道路不允许有重复，最后一次标记后不需要返回，求路程总和的最小值。
>
>第i行输出行动中心为i时的答案，如果不可能则输出-1

这种翻译好像跟题面没什么区别啊。

别着急，下面就知道区别在哪里了。

题面要求，相邻两次到达的点不能有公共边，说白了就是以 $S$ 为根的树每次取的点不能来自同一颗 $S$ 的子节点的子树。那么再简化一下，就是 $S$ 的子节点的子树节点数最大不能超过$n/2$。为什么呢？如果超过一半了，肯定会出现相邻啊。

那么这里就出现了一个临界值。$n-1$个点排成的队列，如果$n$是偶数，比如说是$4$。那么最大的子节点的子树大小最大就是$2$这个时候，队列的最后一个点就被确定一定是这个大小为$2$的子树上的点。意识到什么不对的地方了吗？

如果按照题面翻译的那样，我们是不需要考虑这种情况的，但是正确的题面可是要考虑这个临界值的啊。这也就是有的人怎么改都A不了的原因了。题面都是错的，怎么可能写对嘛。

上面我们讲了怎么判定，那么怎么求最大的子节点的子树大小呢？设 $s[u]$ 表示以$u$为根的子树大小，我们先随便选一个点为根节点，然后dfs一遍求出$s[u]$，此时的$s[u]$表示的是以$u$的父节点为根节点时，以$u$为根的子树大小。当以$u$的子节点为根节点时，以$u$为根的子树大小为$n-s[u]+1$，这里很好理解，就不说为什么了。

能够判定了，我们还需要求距离和，还有最大距离。

我们定义$w[u][0]$表示以$u$为根节点的子树上的点到$u$的距离和，$w[u][1]$表示不在以$u$为根节点的子树上的点到$u$的距离和，跑两遍dfs就可以求出。然后就是求距离，这个很简单，我们在下面的程序里说

下放程序

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cctype>
#define ll long long
#define gc getchar
#define maxn 1000005
using namespace std;

inline ll read(){
    ll a=0;int f=0;char p=gc();
    while(!isdigit(p)){f|=p=='-';p=gc();}
    while(isdigit(p)){a=(a<<3)+(a<<1)+(p^48);p=gc();}
    return f?-a:a;
}int n;ll ans;

struct ahaha{
    int to,next;
}e[maxn<<1];int tot,head[maxn];
inline void add(int u,int v){
    e[tot].to=v,e[tot].next=head[u];head[u]=tot++;
}

int f[maxn],l[maxn],s[maxn];ll w[maxn][2];  //f记录父子关系，l记录最远距离，s记录子树大小，w[0]表示下方的点的距离和，w[1]表示上方的点的距离和
int p[maxn],d1[maxn],d[maxn][2];  //p表示下方距离的最大值经过哪一个子节点，d1表示下方距离次大值，d[0]表示下方距离最大值，d[1]表示上方距离最大值
void dfs(int u,int fa){s[u]=1;
    for(int i=head[u];~i;i=e[i].next){
        int v=e[i].to;if(v==fa)continue;
        dfs(v,u);f[v]=u;s[u]+=s[v];  //先递归，再处理 s的处理也很常见
        w[u][0]+=w[v][0]+s[v];  //加上s[v]是加上uv相连的这条边的贡献
        if(d[v][0]+1<=d1[u])continue; //如果v下方最大值+1还不如u下方次大值大，我们就可以直接走了
        if(d[v][0]+1>=d[u][0]){  //如果大于等于最大值，更新次大值，更新最大值，更新最大值来源。为什么等于也可以大家可以自己想一想，很简单
            d1[u]=d[u][0];
            d[u][0]=d[v][0]+1,p[u]=v;
            continue;
        }
        d1[u]=d[v][0]+1;  //剩下的情况就是 d1[u]<d[v][0]+1<d[u][0] 所以更新次大值
    }
}
void dfs1(int u,int fa){
    for(int i=head[u];~i;i=e[i].next){
        int v=e[i].to;if(v==fa)continue;
        if(v==p[u])d[v][1]=max(d1[u],d[u][1])+1;  //如果是父节点的最大值来源，那么用次大值更新
        else d[v][1]=max(d[u][0],d[u][1])+1;  //反之，用最大值更新
        w[v][1]=(ll)n-s[v]+w[u][1]+w[u][0]-w[v][0]-s[v];  //n-s[v]表示uv相连的边的贡献，w[u][0]-w[v][0]-s[v]表示父节点的其他子节点的贡献
        dfs1(v,u);  //先处理，再递归
    }
}

int main(){memset(head,-1,sizeof head);
    n=read();
    if(n==1){  //对于只有一个节点的树我们直接特判
    	puts("0");
    	return 0;
    }	
    for(int i=1;i<n;++i){  //读入所有边
        int u=read(),v=read();
        add(u,v);add(v,u);
    }
    dfs(1,-1);dfs1(1,-1);  //第一遍dfs自下而上处理，第二遍自上而下
    for(int u=1;u<=n;++u){
        int maxa=0,a,k;
        for(int i=head[u];~i;i=e[i].next){  //求出以当前节点为根，最大的子节点的子树大小，并记录是哪个子节点
            int v=e[i].to;k=f[v]==u?s[v]:n-s[u];
            if(k>maxa)maxa=k,a=v;
        }
        if((maxa<<1)>n){  //如果超过一半，必定会相邻，输出-1
            puts("-1");
            continue;
        }
        l[u]=(maxa<<1)==n?(f[a]==u?d[a][0]+1:(max(p[a]==u?d1[a]:d[a][0],d[a][1])+1)):max(d[u][0],d[u][1]);  //这一行的意思是如果不是前面提到的临界值，那么直接找最大距离即可；但是如果是临界情况，并且这个子节点依然是子节点，那么就是子节点下面的最远距离+1，如果子节点之前是父节点，那么找子节点没有经过u的最长距离+1
        printf("%lld\n",(w[u][0]+w[u][1]<<1)-l[u]); //最后输出答案即可
    }
    return 0;
}
```

这道题留给我们一个教训，就是不要过分相信翻译，毕竟谁都可以递交翻译

不喜勿喷



---

## 作者：Crazyouth (赞：3)

## 分析

看到标签里写的 dp，想了想可能是换根，但我不会，怎么办呢？

考虑什么时候会是 $-1$。观察样例发现，只有行动中心为 $2$ 的时候才不是 $-1$，而 $2$ 恰好是树的重心，那么猜想只有重心才不是 $-1$，接下来证明它。

如果一个点不是重心，那么说明至少存在其中一个子树 $T'$ 大小大于 $\frac{n}{2}$，那么剩下的子树大小之和一定小于 $\frac{n}{2}-1$，则我们每次访问完  $T'$ 中的一个节点后，要保证相邻两次不走重复道路，就需要访问一个 $T'$ 外的节点，如此到最后，会发现除了 $T'$ 中的 $2$ 个点以外其它点都访问完了，这时但凡再去访问一个点，剩下那个点就访问不到了，因此不是重心的点都是 $-1$。

做到这一步了，下一步就开始想对于重心应该输出什么。这时候，如果恰有子树 $T'$ 的节点树为 $\frac{n}{2}$，那么我们必须先访问 $T'$ 中的一个点，否则就会最后剩下 $2$ 个 $T'$ 中的点没访问，又无解了。既然需要先访问 $T'$ 中的点，那么最后必定也会剩下 $T'$ 中的点，我们想让最后这条路径尽量长（否则它要被计算两次），所以就选择 $T'$ 中深度最大的点。综上，如果重心 $c$ 存在一个子树 $T'$ 的节点个数为 $\frac{n}{2}$，答案为 $2\times\displaystyle\sum_x\operatorname{dist}(c,x)-\max_x(\operatorname{dist(c,x)}\times\{x\in T'\})$，其中 $\operatorname{dist}(i,j)$ 表示 $i,j$ 的距离，$\{x\in T'\}$ 表示 $\begin{cases}
   1 &\text{if } x\in T' \\
   0 &\text{if } x\not \in T'
\end{cases}$。

如果不存在这样的子树 $T'$，那么对选择没有要求，又因为 $c$ 是重心，必然存在合法解，那么最优肯定是选择深度最大的结尾，因此此时答案为 $2\times\displaystyle\sum_x\operatorname{dist}(c,x)-\max_x(\operatorname{dist(c,x)})$。

由于重心最多 $2$ 个，所以复杂度 $O(n)$。

两篇做法相同的题解都没放代码，我就放一个吧。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int maxx[N],is[N],sz[N],n,dep[N],rt,son[N],tag[N];
vector<int> G[N];
void dfs(int u,int fa)
{
	sz[u]=1;
	maxx[u]=0;
	for(auto v:G[u])
	{
		if(v==fa) continue;
		dfs(v,u);
		sz[u]+=sz[v];
		maxx[u]=max(maxx[u],sz[v]);
		if(maxx[u]==n/2&&!son[u]) son[u]=v;
	}
	maxx[u]=max(maxx[u],n-sz[u]);
	if(maxx[u]==n/2&&!son[u]) son[u]=fa;
	if(maxx[u]<=(n>>1)) is[u]=1;
}
void dfs2(int u,int fa)
{
	tag[u]=(u==son[rt])|tag[fa];
	if(fa==rt) dep[u]=1;
	for(auto v:G[u])
	{
		if(v==fa) continue;
		dep[v]=dep[u]+1;
		dfs2(v,u);
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)
	{
		if(!is[i]) cout<<-1<<endl;
		else
		{
			memset(dep,0,sizeof dep);
			memset(tag,0,sizeof tag);
			rt=i;
			dfs2(i,0);
			int ans=0,maxd=0;
			for(int i=1;i<=n;i++) ans+=dep[i];
			if(!son[i])
			for(int i=1;i<=n;i++) maxd=max(maxd,dep[i]);
			else
			for(int i=1;i<=n;i++) maxd=max(maxd,dep[i]*tag[i]);
			cout<<ans*2-maxd<<endl;
		}
	}
	return 0;
}

---

## 作者：Kketchup (赞：0)

### [[POI2011] INS-Inspection](https://www.luogu.com.cn/problem/P3525)

- 树的重心

**Sol:** 题目要求不能连续走相同的边，而每次都是从 $S$ 出发的，那也就是不能两次走相同的 $S$ 的子树。进一步地，$S$ 一定不能有点数大于 $\frac{n}{2}$ 的子树。反证一下，假设有点数大于 $\frac{n}{2}$ 的子树（至多一个），每次都会访问一个最大子树中的点，再访问一个其他子树的点，而最大子树最后会剩下至少 $2$ 个点，就无解了。所以我们得到重要结论：**只有重心有解**。

接下来考虑怎么计算答案。因为最后不用返回，所以最后走到最远的点是最优的。所以答案为 $2\times \sum_xdis(S,x)-\max_xdis(S,x)$。因为一个树的重心最多 $2$ 个，所以时间复杂度 $O(n)$。

还有一个特殊的部分要注意：如果最大子树大小正好是 $\frac{n}{2}$，那么第一个和最后一个都应该是这个子树内的点，这种情况特判找这个子树里的最远点。

**Trick:** 发现只有重心有答案后保证复杂度，不发现这个性质只能换根，比较麻烦。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
#define F(i,x,y) for(int i=(x);i<=(y);++i)
#define Fo(i,x,y) for(int i=(x);i>=(y);--i)
const int N=1e6+10;
int n,p;
bool z[N],tag[N];
int son[N],siz[N],dep[N],mx[N];
vector<int> e[N];
void dfs(int u,int fa){
    siz[u]=1;
    for(int v:e[u]){
        if(v==fa) continue;
        dfs(v,u);
        siz[u]+=siz[v];
        mx[u]=max(mx[u],siz[v]);
        if(siz[v]==n/2&&!son[u]) son[u]=v;
    }
    mx[u]=max(mx[u],n-siz[u]);
    if(mx[u]==n/2&&!son[u]) son[u]=fa;
    if(mx[u]<=(n/2)) z[u]=1;
}
void dfs2(int u,int fa){
    tag[u]=(u==son[p])|tag[fa];
    for(int v:e[u]){
        if(v==fa) continue;
        dep[v]=dep[u]+1;
        dfs2(v,u);
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=1,x,y;i<n;++i){
        cin>>x>>y;
        e[x].emplace_back(y);
        e[y].emplace_back(x);
    }dfs(1,0);
    for(int i=1;i<=n;++i){
        if(!z[i]) cout<<-1<<endl;
        else{
            memset(dep,0,(n+1)*sizeof(int));
            memset(tag,0,(n+1)*sizeof(bool));
            p=i;dep[i]=0;
            dfs2(i,0);
            int maxx=0,ans=0;
            for(int i=1;i<=n;++i) ans+=dep[i];
            if(son[i]){for(int j=1;j<=n;++j) if(tag[j]) maxx=max(maxx,dep[j]);}
            else for(int j=1;j<=n;++j) maxx=max(maxx,dep[j]);
            cout<<2*ans-maxx<<endl;
        }
    }
    return 0;
}
```

---

## 作者：Gorenstein (赞：0)

对于任意一点 $S$，令其为根。根据题意，$S$ 相邻两次不能往同一棵子树走，否则必会产生重合。因此两次去往同一子树至少相隔一次该子树外的标记。

设某一子树的大小为 $a$，总点数为 $n$。根据上述讨论结果，除去 $S$ 本身，若余下的 $n-1$ 个点中 $a-1>n-1-a$ 即该子树的大小减一大于了其余点的个数，则无论如何必然会有两次去往该子树，无法满足题设。从而需使 $2a\leqslant n$，即该子树的点不能超过总点数的一半。

为使路径总和最小，当使最后一次标记的点（假设为 $x$）距 $S$ 最远。这是因为根据题意，最后一次标记不需要返回，从而减少了 $\operatorname{dis}(S,x)$ 的距离。

当 $S$ 的某个子节点 $y$ 的子树点数达到 $n$ 的一半时，若第一次不走 $y$ 的子树，那么除去 $S$ 本身，其余部分就只剩下 $\frac{n}{2}-2$，此时无论如何均不能再满足题设。因此当 $S$ 的某个子节点 $y$ 的子树点数达到总点数的一半时，最后一次必然会标记该子树的点。因此需要从该子树中寻找深度最大的点。

综上所述，我们得到如下解法：
- 找到树的所有重心。
- 对于每个重心 $p$，令其为根，分类讨论：
   - 若 $p$ 有一个子树 $E$ 的节点数量达到 $n$ 的一半，则答案为 $2\big(\sum _x\operatorname{dis}(p,x)\big)-\max\limits_{y\in E}\operatorname{dis}(p,y)$。
   - 若不存在这样的子树，则答案为 $2\big(\sum _x\operatorname{dis}(p,x)\big)-\max\operatorname{dis}(p,x)$。

一棵树最多只有两个重心。而对于非重心的点，根据本题解开始时讨论出的结论，必然不可能存在一种标记点的方法使之满足题设，故均为 `-1`。

该解法时间复杂度为 $O(n)$。

---

## 作者：lgswdn_SA (赞：0)

一个比较简单的题目。把题目中的

假设这棵树的根节点为 $u$，那么两个节点 $v_1,v_2$ 到 $u$ 的路径不经过重复边的充要条件是 $v_1,v_2$ 不在一个同一个子树中（一个过于明显的性质），所以我们只需要保证相邻两次行动中，选择的点不在同一个子树中。

我们贪心地去构造这个顺序。考虑 $u$ 的最大子树中的节点，它们可以间隔地放。如果最大子树的数量超过 $\frac{n-1}{2}$上取整，那么显然是放不下了，意味着无论怎么放都一定会有两次相邻的经过重复的边。

最大子树大小和题目中要求的距离之和以及最大距离都可以通过换根 dp 求，不会的可以参考 [UM的日报队列中的文章](https://sflsrick.blog.luogu.org/note-how-to-change-root)。代码中变量有点乱，建议自己写换根dp。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+9;

struct edge {int to,nxt;}e[N*2]; int hd[N],tot;
void add(int u,int v) {e[++tot]=(edge){v,hd[u]};hd[u]=tot;}
int n;

int d[N],sd[N],md[N][3],mdx[N],sz[N],msz[N],son[N];
//深度，距离总和，最长链，最长链儿子，子树的大小，最大子树大小，重儿子 
void dfs1(int u,int fa) {
	sz[u]=1;
	for(int i=hd[u],v;i;i=e[i].nxt) {
		if((v=e[i].to)==fa) continue;
		d[v]=d[u]+1;
		dfs1(v,u);
		sd[u]+=(sd[v]+sz[v]), sz[u]+=sz[v];
		md[u][2]=max(md[u][2],md[v][1]+1);
		if(md[u][2]>md[u][1]) swap(md[u][1],md[u][2]), mdx[u]=v;
		msz[u]=max(msz[u],sz[v]);
	}
}

int sdg[N],mdg[N];
void dfs2(int u,int fa) {
	for(int i=hd[u],v;i;i=e[i].nxt) {
		if((v=e[i].to)==fa) continue;
		sdg[v]=sdg[u]+sd[u]+n-2*sz[v]-sd[v];
		if(v==mdx[u]) mdg[v]=max(mdg[u]+1,md[u][2]+1);
		else mdg[v]=max(mdg[u]+1,md[u][1]+1);
		msz[v]=max(msz[v],n-sz[v]);
		dfs2(v,u);
	}
	/* 
}


signed main() {
	scanf("%lld",&n);
	for(int i=1,u,v;i<n;i++)
		scanf("%lld%lld",&u,&v), add(u,v), add(v,u);
	dfs1(1,0), dfs2(1,0);
	for(int i=1;i<=n;i++) {
		if(msz[i]>n/2) puts("-1");
		else printf("%lld\n",(sdg[i]+sd[i])*2-max(md[i][1],mdg[i]));
	}
	return 0;
}
```

如果按照普通题面写你会发现只有40分，原因很简单，题面错了。根据对的题面，如果重子树大小是 $\frac{n}{2}$，那么最后减去的“这里面的最长距离”一定是重儿子中的点到 $u$ 的最长距离。（具体为什么楼上解释的比较清楚了）。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+9;

struct edge {int to,nxt;}e[N*2]; int hd[N],tot;
void add(int u,int v) {e[++tot]=(edge){v,hd[u]};hd[u]=tot;}
int n;

int d[N],sd[N],md[N][3],mdx[N],sz[N],msz[N],son[N],faa[N];
//深度，距离总和，最长链，最长链儿子，子树的大小，最大子树大小，重儿子，父节点 
void dfs1(int u,int fa) {
	sz[u]=1; faa[u]=fa;
	for(int i=hd[u],v;i;i=e[i].nxt) {
		if((v=e[i].to)==fa) continue;
		d[v]=d[u]+1;
		dfs1(v,u);
		sd[u]+=(sd[v]+sz[v]), sz[u]+=sz[v];
		md[u][2]=max(md[u][2],md[v][1]+1);
		if(md[u][2]>md[u][1]) swap(md[u][1],md[u][2]), mdx[u]=v;
		if(sz[v]>msz[v]) son[u]=v;
		msz[u]=max(msz[u],sz[v]);
	}
}

int sdg[N],mdg[N];
void dfs2(int u,int fa) {
	for(int i=hd[u],v;i;i=e[i].nxt) {
		if((v=e[i].to)==fa) continue;
		sdg[v]=sdg[u]+sd[u]+n-2*sz[v]-sd[v];
		if(v==mdx[u]) mdg[v]=max(mdg[u]+1,md[u][2]+1);
		else mdg[v]=max(mdg[u]+1,md[u][1]+1);
		if(n-sz[v]>msz[v]) son[v]=u;
		msz[v]=max(msz[v],n-sz[v]);
		dfs2(v,u);
	}
}


signed main() {
	scanf("%lld",&n);
	for(int i=1,u,v;i<n;i++)
		scanf("%lld%lld",&u,&v), add(u,v), add(v,u);
	dfs1(1,0), dfs2(1,0);
	for(int i=1;i<=n;i++) {
		if(msz[i]>n/2) puts("-1");
		else {
			if(msz[i]<(n+1)/2)
				printf("%lld\n",(sdg[i]+sd[i])*2-max(md[i][1],mdg[i]));
			else if(son[i]!=faa[i])
				printf("%lld\n",(sdg[i]+sd[i])*2-md[son[i]][1]-1);
			else
				printf("%lld\n",(sdg[i]+sd[i])*2-mdg[i]);
		}
	}
	return 0;
}
```

---

