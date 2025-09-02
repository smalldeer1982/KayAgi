# [POI 2014] MRO-Ant colony

## 题目背景

[English Edition](/paste/44plylwf)

## 题目描述

正在寻找食物的蚂蚁们来到了一座山。

这座山有 $n$ 个洞穴，并有 $n-1$ 条道路连接这些洞穴。也就是说，所有的洞穴和道路组成了一个树形结构。

对于每个只有一条道路连接的洞穴，都有一个出入口使得该洞穴与外界相连。

在**每个出入口**处，都有 $g$ 群蚂蚁，第 $i$ 群蚂蚁的大小为 $m_i$。

蚂蚁群会一个接一个地进入山中，当且仅当山中没有蚂蚁，下一群蚂蚁才会进入。

进入山后，蚂蚁们会按如下方式行动：

- 如果蚂蚁们进入了一个洞穴，该洞穴有 $d$ 条道路与之相连（不包括它们进入该洞穴经过的道路），则蚂蚁们会分为大小相等的 $d$ 个蚁群，每个蚁群各选择一条道路，使得一个道路恰好有一条蚁群经过，特别地，如果 $d=0$（即蚁群到达了出口），蚂蚁们会从该出口离开山。
- 根据上文，假如这个蚁群有 $x$ 只蚂蚁，则每个蚁群会有 $\left \lfloor \dfrac{x}{d} \right \rfloor$ 只蚂蚁，多余的蚂蚁将会消失（至于怎么消失，这并不重要 :)）。

下面这张图就是一个例子：大小为 $m$ 的蚁群到达了一个洞穴，该洞穴有 $3$ 条道路（除了它们进入该洞穴时经过的道路），则该蚁群分割成了三个大小为 $\left \lfloor \dfrac{m}{3} \right \rfloor$ 的蚁群。

![](https://cdn.luogu.com.cn/upload/pic/6972.png)

在其中一条道路上，有一只食蚁兽，当经过该道路的蚁群大小恰好为 $k$ 时，它会把这个蚁群的蚂蚁全部吃掉。

现在请你求出食蚁兽一共吃掉多少只蚂蚁。

## 说明/提示

对于 $100\%$ 的数据，$2\le n,g\le10^6$，$1\le k,m_i\le10^9$，$1\le a_i,b_i\le n$。

## 样例 #1

### 输入

```
7 5 3
3 4 1 9 11
1 2
1 4
4 3
4 5
4 6
6 7
```

### 输出

```
21
```

# 题解

## 作者：liuyz11 (赞：9)

首先对于指定的那条边，可以把它拆成两棵树或者建一个0的点与这两点相连.

会想到计算每个叶子节点的每组蚂蚁到指定边后还剩多少蚂蚁，显然会超时.

我们倒过来考虑，从指定的边开始计算.

假设第 $i$ 个节点存在数量大于等于 $dp1_i$ 的蚂蚁，且小于等于 $dp2_i$的蚂蚁最终到达指定边会被吃掉(即恰好 $k$ 只).

容易得到转移方程:

$dp1_v = dp1_u \cdot (c_u - 1)$

$dp2_v = (dp2_u + 1) \cdot (c_u - 1) - 1$

其中 $c_u$ 表示点 $u$ 的度


一开始 $dp1_0$ 与 $dp2_0$都为k.

最后对于每一个叶子结点 $i$，在 $m$ 数组中二分查找大于等于 $dp1_i$ 且小于等于 $dp2_i$ 的数量.

参考代码

```cpp
#include <bits/stdc++.h>
#define rep(x, l, r) for(int x = l; x <= r; x++)
using namespace std;
typedef long long ll;

const ll INF = 1 << 30;
const int MAXN = 1e7 + 5;

int n, m, k, cnt, root1, root2;
int head[MAXN], nxt[MAXN << 1], to[MAXN << 1];
int a[MAXN];
ll dp1[MAXN], dp2[MAXN], c[MAXN];

void addedge(int u, int v){
	cnt++;
	nxt[cnt] = head[u];
	head[u] = cnt;
	to[cnt] = v;
}

void add(int u, int v){
	addedge(u, v);
	addedge(v, u);
	c[u]++; c[v]++;
}

void dfs(int u, int fa){
	for(int e = head[u]; e; e = nxt[e]){
		int v = to[e];
		if(v == fa) continue;
		dp1[v] = min(INF, dp1[u] * (c[u] - 1));//防止炸longlong
		dp2[v] = min(INF, (dp2[u] + 1) * (c[u] - 1) - 1); 
		dfs(v, u);
	}
}

int main(){
	scanf("%d%d%d", &n, &m, &k);
	rep(i, 1, m) scanf("%d", &a[i]);
	sort(a + 1, a + m + 1);
	scanf("%d%d", &root1, &root2);
	add(0, root1);//建一个0点与两个根节点连边
	add(0, root2);
	rep(i, 1, n - 2){
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	dp1[0] = dp2[0] = k;
	dfs(0, -1);
	ll ans = 0;
	rep(i, 1, n)
		if(c[i] == 1){
			ans += upper_bound(a + 1, a + m + 1, dp2[i]) - lower_bound(a + 1, a + m + 1, dp1[i]);
		}
	printf("%lld\n", ans * k);//最后记得要乘上k
	return 0;
}
```

---

## 作者：沧澜 (赞：7)

- 这个题从叶子节点去算的话显然很困难，所以我们可以从食蚁兽所在的两个点开始倒着搞。

minn和maxn记录每个节点最多和最少有多少个蚂蚁才能让食蚁兽恰好吃到k只。

- 然后，分别以这两个点为根节点，dfs一下求出所有的minn和maxn。

- 接着，二分答案，求一下对于每个节点,g群蚂蚁中符合条件的蚂蚁的群数。

- 最后，群数\*k即为所求。

**别忘了开long long(╯‵□′)╯︵┻━┻**

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define MAXN 1000001
using namespace std;
int n,g,K;
int s,t,tot;
long long ans;
int outo[MAXN],dad[MAXN];
int to[MAXN],net[MAXN],head[MAXN];
long long m[MAXN],minn[MAXN],maxn[MAXN];
void add(int u,int v){
    to[++tot]=v;net[tot]=head[u];head[u]=tot;
    to[++tot]=u;net[tot]=head[v];head[v]=tot;
}
void dfs(int now){
    for(int i=head[now];i;i=net[i])
        if(dad[now]!=to[i]){
            dad[to[i]]=now;
            outo[now]++;
        }
    for(int i=head[now];i;i=net[i])
        if(dad[now]!=to[i]){
            minn[to[i]]=minn[now]*outo[now];
            maxn[to[i]]=(maxn[now]+1)*outo[now]-1;
            maxn[to[i]]=min(maxn[to[i]],m[g]);
            if(minn[to[i]]<=m[g])
                dfs(to[i]);
        }
}
long long cal(long long  x){
    int l=1,r=g,bns=0;
    while(l<=r){
        int mid=(l+r)/2;
        if(m[mid]<x){
            bns=max(bns,mid);
            l=mid+1;
        }
        else r=mid-1;
    }
    return bns;
}
int main(){
    scanf("%d%d%d",&n,&g,&K);
    for(int i=1;i<=g;i++)    scanf("%d",&m[i]);
    sort(m+1,m+1+g);
    scanf("%d%d",&s,&t);
    for(int i=2;i<n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y);
    }
    minn[s]=maxn[s]=minn[t]=maxn[t]=K;
    dfs(s);
    dfs(t);
    for(int i=1;i<=n;i++)
        if(!outo[i])
            ans+=cal(maxn[i]+1)-cal(minn[i]);
    cout<<ans*K;
}
```

---

## 作者：ywy_c_asm (赞：6)

这题我是用除法的向下取整做的。

首先暴力的想法就是，我们对于树上的每个叶子，都O(ng)模拟蚁群的走法，然后像题目那样说的在分叉处向下取整一下然后接着走直到走到关键边为止。

然后我们发现，对于每个叶子的g个数中的任意一个，我们仅仅只是需要判断这玩意走啊走啊经过若干次向下取整的除法然后走到了关键边是不是就到了k，我们干脆就把这玩意优化成一条链，就是把这个关键边的一个非叶子节点钦定为根（当然，如果n=2的时候咱们特判一下就行了），然后每个叶子节点就真的成为了叶子节点，我们关心的就是他到根（或者是他到关键边的另一个端点如果后者是他的祖先的话）的一段路径，那么也就是说每向上跳一个祖先都会除以这个点的度数-1，然后向下取整，然后做这么多次这样的操作。

由此我们能想到什么呢？

$\lfloor\frac{\lfloor\frac{n}{a}\rfloor}{b}\rfloor=\lfloor\frac{n}{ab}\rfloor$

（这个公式相信很多人都知道，如果不知道的可以列式子推一下还是不难推出来的）

于是我们发现可以把他到根（或者关键边的另一个端点）的连乘积求出来，这东西可能很大，不过要是特别大的话做个除法肯定也不会除到k，我们把它跟inf取min就行了。

那么现在问题就转化为，对每个叶子节点，我要知道在这g个数里，有多少数除以连乘积向下取整之后的结果是k（把这玩意最后乘个k就是答案了）。

容易发现把数排完序之后对应的数是一段连续的区间（如果存在的话），那么就可以二分了。

上代码~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
inline int get(){
	int n=0;char c;while((c=getchar())||23333){
		if(c>='0'&&c<='9')break;if(c=='-')goto s;
	}n=c-'0';while((c=getchar())||23333){
		if(c>='0'&&c<='9')n=n*10+c-'0';else return(n);
	}s:while((c=getchar())||23333){
		if(c>='0'&&c<='9')n=n*10-c+'0';else return(n);
	}
}
int ints[1000001];int deg[1000001];
typedef struct _b{
	int dest;int nxt;
}bian;bian memchi[2000001];int gn=1;int heads[1000001];ll dp[1000001]；
inline void add(int s,int t){
	deg[t]++;memchi[gn].dest=t;memchi[gn].nxt=heads[s];heads[s]=gn;gn++;
}int root,taizi;//root是根，taizi（为啥要起这名字请自行体会……)是根的一个儿子，他们都是关键边的端点 
void dfs(int pt,int baba){//dfs从上到下递推出连乘积 
	if(pt!=root){
		if(pt==taizi)dp[pt]=max(1,deg[pt]-1);
		else dp[pt]=min(1234567890ll,dp[baba]*max(1,deg[pt]-1));//注意要和inf取min不然会爆掉 
	}for(register int i=heads[pt];i;i=memchi[i].nxt){
		if(memchi[i].dest==baba)continue;dfs(memchi[i].dest,pt);
	}
}
int main(){
	int n=get(),g=get(),k=get();for(register int i=1;i<=g;i++)ints[i]=get();sort(ints+1,ints+1+g);
	int rs,rt;for(register int i=1;i<n;i++){
		int s=get(),t=get();add(s,t);add(t,s);if(i==1)rs=s,rt=t;
	}if(deg[rs]!=1)root=rs,taizi=rt;else root=rt,taizi=rs;dp[root]=max(1,deg[root]-1);//别忘了判断只有一条边的情况 
	ll tot=0;dfs(root,0);
	for(register int i=1;i<=n;i++){
		if(deg[i]==1){
			if(ints[g]/dp[i]<k)continue;if(ints[1]/dp[i]>k)continue;
			int ans=-1,l=1,r=g;while(l<=r){//二分出答案区间 
				int mid=(l+r)>>1;if(ints[mid]/dp[i]>=k)ans=mid,r=mid-1;else l=mid+1;
			}if(ans!=-1){
				if(ints[ans]/dp[i]!=k)continue;int rl=ans;l=1,r=g;while(l<=r){
					int mid=(l+r)>>1;if(ints[mid]/dp[i]<=k)ans=mid,l=mid+1;else r=mid-1;
				}tot+=(ans-rl+1);
			}
		}
	}tot*=k;cout<<tot<<endl;
	return(0);
}
```

---

## 作者：sqzyz (赞：3)

[原题传送门](https://www.luogu.com.cn/problem/P3576)

## 题意

一棵树，在每个叶子结点都会有 $g $ 个蚁群**依次**进入，即每个时刻树上只有一个蚁群。

蚁群在某个节点时，若该节点连有 $d$ 条道路，则蚁群会分散成 $d$ 组向前行进（**向下取整**）。

在第一条路径上有一只食蚁兽，假如在这条路径上有 $k$ 只蚂蚁经过，这些蚂蚁会被吃掉，求最终食蚁兽能吃掉几只蚂蚁


## 思路

如果暴力模拟 $g$ 群蚂蚁行进的过程，显然会 T 飞,但是似乎无法在暴力的基础上优化

正难则反，我们考虑**倒推**，从食蚁兽所在的边开始推

对于每个节点记录两个值 

$dpl_u$ 表示想让食蚁兽吃掉蚂蚁，该节点上**最少**有几只蚂蚁

$dph_u$ 表示想让食蚁兽吃掉蚂蚁，该节点上**最多**有几只蚂蚁

得到转移方程

$dpl_v=dpl_u\cdot d$

$dph_v=(dph_u+1)\cdot d-1$

其中 $d$ 表示节点 $u$ 的儿子个数

我们通过 BFS 得到所有点的两个 dp 值，并提前将 $m$ 数组排序（方便后边的二分）

然后对于每个叶子节点，用  upper_bound  分别查找到 $dph$ 和 $dpl$ 的位置并作差，即可求得在所有蚁群中有多少满足条件，即可以让食蚁兽吃掉，再乘上 $k$ 求得最终的答案

**注意：**

因为~~食蚁兽比较能吃~~数据范围比较大，**要开 long long**

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,g,k;
int rt1,rt2;
int a[1000005];
vector<int>e[1000005];
long long dp_l[1000005],dp_h[1000005];
long long ans;
void dfs(int u,int pa){
	int d=e[u].size();
	d--;//减去与父亲的连边 
	for(int i=0;i<e[u].size();i++){
		int v=e[u][i];
		if(v==pa)continue;
		dp_l[v]=dp_l[u]*d;
		dp_h[v]=(dp_h[u]+1)*d-1;
		//状态转移 
		dfs(v,u);
	}
	if(d==0){
		ans+=(upper_bound(a+1,a+g+1,dp_h[u])-lower_bound(a+1,a+g+1,dp_l[u]))*k;//统计答案 
	}
	return;
}
int main(){
	scanf("%d%d%d",&n,&g,&k);
	for(int i=1;i<=g;i++)scanf("%d",&a[i]);
	sort(a+1,a+1+g);//排序，以便二分 
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		if(i==1){
			rt1=u,rt2=v;
			e[0].push_back(rt1);
			e[rt1].push_back(0);
			e[0].push_back(rt2);
			e[rt2].push_back(0);
			//将食蚁兽所在边与0点相连，方便后续的处理 
			continue;
		}
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dp_l[0]=k;
	dp_h[0]=k;
	dfs(0,-1);
	printf("%lld",ans);
	return 0;
	//下班~~ 
}
```

---

## 作者：Night_sea_64 (赞：3)

这题挺新颖的，能锻炼思维能力。

相信不少人跟我一样，第一次看到题都以为直接模拟，找到每个出入口，然后模拟每群蚂蚁的行动就好了。但是我们可以看到数据范围，$1\le n,g\le10^6$。真要这么做的话，时间复杂度 $O(n^2g)$，世界末日都跑不完。。。

因为蚁群最多可以有 $(n-1)\times g$ 群（即有 $n-1$ 个点连向同一个点），不可能一一枚举，但是食蚁兽所在的边（可以看作蚂蚁要去的终点，以下简称终点边）只有一条。所以我们可以考虑从终点边倒着往回推，这样只需要遍历整个树一次就行了！

搜索每个点当然是更方便的，所以我们从终点边连接的两个点分别算一次。每个点维护两个量 $l_i,r_i$，分别为从 $i$ 点走到终点边的方向（注意不是走到终点边，而是走向终点边的方向）的蚂蚁最少和最多有多少。设 $x$ 为当前的点，$y$ 为 $x$ 要转移去的一个点，$size_x$ 为 $x$ 连的边数，则有如下的转移式：

$$l_y=l_x\times(size_x-1)$$

$$r_y=r_x\times(size_x-1)+size_x-2$$

意思就是，$l_y$ 个蚂蚁在全部没有消失（即被 $size_x-1$ 整除）的情况下平均分为 $size_x-1$ 份，变为了 $l_x$ 个蚂蚁，则倒推回去就是 $l_x\times (size_x-1)$；$r_y$ 个蚂蚁在消失地尽可能多（即消失了 $size_x-1-1$ 个）的情况下平均分为 $size_x-1$ 份，变为了 $r_x$ 个蚂蚁，倒推回去就是 $r_x\times(size_x-1)+size_x-2$。显然这样算的一定是 $y$ 点的最小值和最大值。

最后，在每个出入口 $i$ 处，要找到有几群蚂蚁大小在 $l_i\sim r_i$ 之间。这可以通过先把蚂蚁大小排序，再使用二分查找（STL 的 lower_bound 或 upper_bound）得到。算出有几群蚂蚁之后 $\times k$（因为每个大小满足要求的蚂蚁群里面都有 $k$ 只被吃了）。

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#define int long long
#define lb lower_bound
#define ub upper_bound
using namespace std;
int n,m,k,p1,p2,ans;
int a[1000010],l[1000010],r[1000010];
vector<int>v[1000010];
void dfs(int x,int last)
{
    for(auto y:v[x])
        if(y!=last)
        {
            l[y]=l[x]*(v[x].size()-1);
            r[y]=r[x]*(v[x].size()-1)+v[x].size()-2;
            dfs(y,x);
        }
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++)cin>>a[i];
    sort(a+1,a+m+1);
    for(int i=1;i<n;i++)
    {
        int x,y;
        cin>>x>>y;
        if(i==1)p1=x,p2=y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    l[p1]=r[p1]=l[p2]=r[p2]=k;
    dfs(p1,p2);
    dfs(p2,p1);
    for(int i=1;i<=n;i++)
        if(v[i].size()==1)
            ans+=(ub(a+1,a+m+1,r[i])-lb(a+1,a+m+1,l[i]));
    cout<<ans*k<<endl;
    return 0;
}
```

---

## 作者：QwQ_operator (赞：3)

来自我的博客：[http://www.cnblogs.com/z360/p/7523150.html](http://www.cnblogs.com/z360/p/7523150.html)

树形dp


Ｏ(≧口≦)Ｏ做了一晚上、、、


我们会发现一个很严肃的问题，如果我们从子节点开始做的话会非常难处理（反正蒟蒻表示我不会、、、）


既然正着不会，我们就倒着搞吧、、其次他说的是通过一条边的数量为k，这k只蚂蚁都会被吃掉。然而我们如果直接用边来进行运算的话，既然这样我们直接将边改为这条边的两个节点，然后以这两个节点为根节点，将原来的树处理成两棵树。然后就可以在这两棵树上乱搞了


如图所示：在1~2这条边上如果有k只蚂蚁经过的时候这k只蚂蚁会被吃掉


我们将上面的两棵树抽离成两颗一颗以1为根节点，一棵以2为根节点。


对于每一颗树我们从根节点开始往下进行搜索，更新每一个节点的父亲节点，如果这个点的父亲节点与他相连出去的节点不相同，那么将与他相连节点的父亲节点为当前节点。


我们看上面的图，如果要是蚂蚁经过1~2这条边上的时候蚂蚁的数量达到k时1号节点·与2好节点处的蚂蚁数量也就要为k。


然后我们在从这个各节点倒着计算他下面的节点蚂蚁的数量


我们知道进入蚂蚁的节点一定是子节点，然后每一个子节点往其他的分支那平分蚂蚁，他评分出来的蚂蚁一定是有一波要进入他的父亲节点。这样的话我们可以直接根据他的父亲节点的蚂蚁数目推出当前节点的蚂蚁数目，我们这个地方是不可能求出准确值的，因为他在平分的时候是下取整的。所以我们只能求出一个子节点的蚂蚁数目的范围。


子节点的蚂蚁的数目等于它的父节点的；连出去的边的条数\*父节点的蚂蚁个数。


看这个图，你可以发现一个规律它的父节点连出去的边的条数正好等于它的父节点的入读。我们可以在进行dfs的时候处理处每一个点的父亲节点以及该点的入读、


蚂蚁平分，子节点最少的蚂蚁的个数为他父亲节点的蚂蚁的数量\*父亲节点的入读，也就是说没有蚂蚁被消灭。最多的蚂蚁的数量为还差一个蚂蚁就可以让每一个分支在多分一只蚂蚁了，极为maxn[t]=(sum[now]+1)\*out[now]-1


然后dfs结束的条件的为他已经搜索到最后一层子节点了。当minn[to[i]]<=m[g]是说明还没有到达根节点。


然后我们可以处理处到达叶子节点的时候的蚂蚁的最多数量跟最少数量，然后在判断有多少组蚂蚁满足要求。


最后的可以吃到的蚂蚁的数量为k\*满足条件的蚂蚁的组数



```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define N 1100000
#define ll long long
using namespace std;
int n,g,k,x,y,sx,sy,tot;
int fa[N],in[N],head[N];
ll s[N],maxn[N],minn[N],ans;
int read()
{
    int x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1; ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0'; ch=getchar();}
    return x*f;
}
struct Edge
{
    int to,from,next;
}edge[N<<1];
int add(int x,int y)
{
    tot++;
    edge[tot].to=y;
    edge[tot].next=head[x];
    head[x]=tot;
}
int dfs(int now)
{
    for(int i=head[now];i;i=edge[i].next)
    {
        int t=edge[i].to;
        if(fa[now]!=t)
        {
            fa[t]=now;
            in[now]++;
         } 
    }
    for(int i=head[now];i;i=edge[i].next)
    {
        int t=edge[i].to;
        if(fa[now]!=t)
        {
            minn[t]=minn[now]*in[now];
            maxn[t]=(maxn[now]+1)*in[now]-1;
            maxn[t]=min(maxn[t],s[g]);
            if(minn[t]<=s[g]) dfs(t);
        }
    }
}
ll erfen(ll x)
{
    int l=1,r=g,ans1=0;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(s[mid]<x)
        {
            ans1=mid;
            l=mid+1;
        }
        else r=mid-1;
    }
    return ans1;
}
int main()
{
    n=read(),g=read(),k=read();
    for(int i=1;i<=g;i++) scanf("%lld",&s[i]);
    sort(s+1,s+1+g);
    sx=read(),sy=read();
    for(int i=2;i<n;i++)
    {
        x=read(),y=read();
        add(x,y),add(y,x);
    }
    minn[sx]=minn[sy]=maxn[sx]=maxn[sy]=k;
    dfs(sx),dfs(sy);
    for(int i=1;i<=n;i++)
     if(!in[i])
      ans+=erfen(maxn[i]+1)-erfen(minn[i]);
    printf("%lld",ans*k);
    return 0;
}
```

---

## 作者：Max_QAQ (赞：1)

**思路：**

对于给出的这一棵树，每个叶子节点上都有 $g$ 个蚁群，然后树的节点范围 $\leq 1e6$ ，那我们肯定不可能都跑一遍，考虑怎么优化。

很明显对于任意的数都满足，先除以一个数（下取整）再除以另一个数（下取整），和除以这两个数的乘积（下取整）的结果都是一样的。

可以根据这个来对这道题求解。

一个蚁群只是经过同一条边一次，也就是说如果他经过了食蚁兽所在的边没有被吃掉，他就不可能再被吃掉了，所以我们考虑将整个树根据食蚁兽所在的边的两个点，将整棵树一分为二，以那两个节点分别为根对那半棵树进行处理。

树上两点的路径是唯一的，一个蚁群经过一个点肯定会分成这个点的度数 $-1$ 组蚂蚁，而我们只需要考虑走到食蚁兽所在的边的那一群，所以可以从那半棵树的根开始，依次向他的儿子去下放标记，表示这群蚂蚁最后会分成几组。


**设：** $f_i$ 表示第 $i$ 个点的标记， $deg_i$ 表示第 $i$ 个点的度数。

那转移就长这样 $f_{son}=f_{fa}\times (deg_{fa}-1)$ 。

那么当标记打到了度数为 $1$ 的点也就是叶子节点时，我们就需要对这 $g$ 群蚂蚁进行处理，既然是下取整，那么肯定会有很多数下取整分成 $k$ ，我们可以预先对这写蚁群进行排序，然后再进行二分查询，查询的范围就是 $l : f_x \times k\ \ \ r : f_x\times (k+1)-1$ ，那么查询到的范围就是满足条件的蚁群数量，两个相减得到答案就行。

**注意：**

可以插入两个哨兵防止二分炸掉，但哨兵的大小一定要够大才行！！！

贴个代码。
```cpp
#include<bits/stdc++.h>
#define int long long
#define chkmax(x,y) (x)=(x>y)?(x):(y)
#define chkmin(x,y) (x)=(x<y)?(x):(y)
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
inline void write(int x){
	static int sta[42];int top=0;
	if(x<0) putchar('-'),x=-x;
	do{sta[++top]=x%10,x/=10;}while(x);
	while(top) putchar(sta[top--]+'0');
	return ;
}
int n,g,k,as,ae,ans;
int head[2000010],ver[4000010],to[4000010],tot;
int f[2000010],ant[2000010],deg[2000010];
inline void add(int x,int y){
	ver[++tot]=y;
	to[tot]=head[x];
	head[x]=tot;
}
inline int searchl(int val){
	int l=0,r=g+1,res;
	while(l<=r){
		int mid=(l+r)>>1;
		if(val<=ant[mid]) res=mid,r=mid-1;
		else l=mid+1;
	}
	return res;
}
inline int searchr(int val){
	int l=0,r=g+1,res;
	while(l<=r){
		int mid=(l+r)>>1;
		if(val<ant[mid]) res=mid,r=mid-1;
		else l=mid+1;
	}
	return res;
}
void dfs(int x,int fa){
	int cnt=0,l,r;
	if(deg[x]==1){
		l=searchl(f[x]*k);//我用的手写二分，当然也可以用自带的lowerbound和uppperbound
		r=searchr(f[x]*(k+1)-1);
		ans+=(r-l);
		return ;
	}
	for(int i=head[x];i;i=to[i]){
		int y=ver[i];
		if(y==fa||y==as||y==ae) continue;
		f[y]=f[x]*(deg[x]-1);
		dfs(y,x);
	}
}
signed main(){
	n=read(),g=read(),k=read();
	for(int i=1;i<=g;i++) ant[i]=read();sort(ant+1,ant+1+g);ant[0]=-0x7fffffffffffffff,ant[g+1]=0x7fffffffffffffff;//排序加哨兵
	for(int i=1,x,y;i<n;i++){
		x=read(),y=read();
		deg[x]++,deg[y]++;
		if(i==1) as=x,ae=y;//找出食蚁兽的点
		add(x,y),add(y,x);
	}
	f[as]=f[ae]=1;
	dfs(as,0),dfs(ae,0);//分别dfs处理
	write(ans*k);//前面找的是几个满足要求的，所以最后要乘 k
	return 0;
}
``






---

## 作者：huhangqi (赞：0)

一个比较简单的思路，不需要二分。

考虑逆向操作，从路径两端开始处理数值范围，将蚂蚁群大小视为一次查询。

由于树的两点之间的简单路径只有一条，所以每个点的范围是唯一的。

处理时和 $10^9$ 取最小值，因为此时已经超过了蚁群最大数量，再继续可能会把 long long 爆了。

之后我们再把叶子节点的范围找出来，做一个类似差分的操作即可，具体可以看代码。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,g,k,m[1000005],d[1000005],l[1000005],r[1000005],cnt,cnt2,ans;
vector<int> e[1000005];
struct P{
	int op,v;
}a[3000005];
bool cmp(P a,P b){
	if(a.v!=b.v)return a.v<b.v;
	return a.op<b.op;
}
void dfs(int p,int f){
	for(int i:e[p]){
		if(i==f)continue;
		if(d[i]==1){
			l[i]=l[p],r[i]=r[p];
		}
		else {
			l[i]=l[p]*(d[i]-1);
			r[i]=r[p]*(d[i]-1)+d[i]-2;
		}
		dfs(i,p);
	}
}
signed main(){
	cin>>n>>g>>k;
	for(int i=1;i<=g;i++)scanf("%d",&m[i]);
	int x,y;
	cin>>x>>y;
	e[x].push_back(y);
	e[y].push_back(x);
	d[y]++,d[x]++;
	for(int i=2,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
		d[u]++,d[v]++;
	}
	if(d[x]==1)l[x]=r[x]=k;
	else l[x]=r[x]=k*(d[x]-1);
	if(d[y]==1)l[y]=r[y]=k;
	else l[y]=r[y]=k*(d[y]-1);
	dfs(x,y);
	dfs(y,x);
	for(int i=1;i<=n;i++)if(d[i]==1)a[++cnt2]={1,l[i]},a[++cnt2]={3,r[i]};
	for(int i=1;i<=n;i++)a[++cnt2]={2,m[i]};
	sort(a+1,a+cnt2+1,cmp);
	for(int i=1,s=0;i<=cnt2;i++){
		if(a[i].op==2)ans+=s;
		else if(a[i].op==1)s++;
		else s--;
	}
	cout<<ans*k;
	return 0;
}


``````

---

## 作者：forgotmyhandle (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P3576)

## 分析
首先根据下取整除法的性质：$\lfloor \frac{\lfloor \frac{a}{x} \rfloor}{y} \rfloor = \lfloor \frac{a}{xy} \rfloor$。所以只需要对每个点求出结束时乘的所有东西的乘积即可。从关键边的两个端点开始 dfs，dfs 的过程中求出到每个点的乘积，然后对于每个点，设这个乘积为 $a$，则如果从这个点以 $[ak, a(k + 1) - 1]$ 之间的数量出发，就会到关键边被吃掉。所以可以直接二分，然后就可以直接求出有多少群从这个点出发的蚂蚁会被吃到。

## 代码
```cpp
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
const int lim = 1000000621;
int n, g, k;
int head[1000005], nxt[2000005], to[2000005], ecnt;
void add(int u, int v) { to[++ecnt] = v, nxt[ecnt] = head[u], head[u] = ecnt; }
int p, q;
int a[1000005];
int deg[1000005];
int mul[1000005][2], dist[1000005][2];
void dfs(int x, int fa, int s) {
    for (int i = head[x]; i; i = nxt[i]) {
        int v = to[i];
        if (v != fa) {
            mul[v][s] = min(lim, mul[x][s] * (deg[x] - 1));
            dist[v][s] = dist[x][s] + 1;
            dfs(v, x, s);
        }
    }
}
int Search1(int k) {
    int l = 1, r = g, mid, ans = g + 1;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (a[mid] >= k) 
            ans = mid, r = mid - 1;
        else 
            l = mid + 1;
    }
    return ans;
}
int Search2(int k) {
    int l = 1, r = g, mid, ans = 0;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (a[mid] <= k) 
            ans = mid, l = mid + 1;
        else 
            r = mid - 1;
    }
    return ans;
}
signed main() {
    cin >> n >> g >> k;
    for (int i = 1; i <= g; i++) cin >> a[i];
    sort(a + 1, a + g + 1);
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        add(u, v);
        add(v, u);
        deg[u]++, deg[v]++;
        if (i == 1) 
            p = u, q = v;
    }
    mul[p][0] = 1, mul[q][1] = 1;
    dfs(p, 0, 0);
    dfs(q, 0, 1);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (deg[i] != 1) 
            continue;
        int K = mul[i][dist[i][0] > dist[i][1]];
        int L = Search1(K * k), R = Search2(K * (k + 1) - 1);
        ans += (R - L + 1);
    }
    cout << ans * k << "\n";
    return 0;
}
```

---

## 作者：xuantianhao (赞：0)

# [MRO-Ant colony](https://www.luogu.com.cn/problem/P3576)

根据下取整除法的性质 $(\left\lfloor\dfrac{\left\lfloor\dfrac{x}{y}\right\rfloor}{z}\right\rfloor=\left\lfloor\dfrac{x}{yz}\right\rfloor)$，我们可以反向考虑，即从特殊边开始，计算出从每个叶子到特殊边的路径上，要除以的那个分母是什么。

这个可以直接一遍 dfs 就出来了（可以把它当成 DP）。注意，当一段路径的分母已经爆 $10^9$ 时就可以直接退出了，因为这样子不会有蚂蚁到得了特殊边。

然后，对于一个分母 $d$，所有 $\in\Big[dk,d(k+1)\Big)$ 的蚁群数量都是合法的；故我们直接对蚁群数量排序然后二分再差分即可。

时间复杂度 $O(n\log n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF=1e9;
const int N=1e6+100;
int n,m,k,U,V,a[N];
LL d[N],res;
vector<int> v[N],u;
void dfs(int x,int fa,int lam){
    if(v[x].size()==1){u.push_back(lam);return;}
    if(1ll*lam*(v[x].size()-1)>INF) return;
    lam*=(v[x].size()-1);
    for(auto y:v[x]) if(y!=fa) dfs(y,x,lam);
}
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++) scanf("%d",&a[i]);
    scanf("%d%d",&U,&V);
	v[U].push_back(V);
	v[V].push_back(U);
    for(int i=1,x,y;i+1<n;i++){
		scanf("%d%d",&x,&y);
		v[x].push_back(y);
		v[y].push_back(x);
	}
    dfs(U,V,1);
	dfs(V,U,1);
    sort(a+1,a+m+1);
    for(auto i:u){
        LL l=1ll*k*i,r=1ll*(k+1)*i;
        if(l>INF) continue;
        d[lower_bound(a+1,a+m+1,l)-a]++;
        d[lower_bound(a+1,a+m+1,r)-a]--;
    }
    for(int i=1;i<=m;i++)d[i]+=d[i-1],res+=d[i]; 
    printf("%lld\n",res*k);
    return 0;
}
```

---

## 作者：wzy2021 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/P3576)

我们来看一下这道题：

树上问题，容易想到树形 $dp$

设 $dp_{i}$ 表示指定边到第 $i$ 条边要分叉多少？

容易得到 

$$dp_v = dp_u \times (num_u - 1)$$

其中 $num_i$ 为节点 $i$ 的度。

但这样在算结果时会超时。

有没有更好的方法呢？~~没有~~

显然，会被吃一定是有范围的，

那么不妨设 $dp_{i,0/1}$ 表示从 $i$ 节点走到指定边会被吃的上界 $/$ 下界，

即从 $i$ 出发 $p$ 个蚂蚁，

若 $dp_{i, 0} \leq p \leq dp_{i, 1}$，则到指定边时会有 $k$ 只蚂蚁，

若不在这个范围内，则不会被吃。

容易得到：

$$dp_{v, 0} = dp_{u, 0} \times (num_u - 1)$$

$$dp_{v, 1} = (dp_{v, 0} + 1) \times (num_u - 1) - 1 $$

既然已经得到了每个点的上下界，那出入口的上下界也得到了，~~废话~~ ！

最终就可以二分查找得出结果

复杂度 $O (n log (g))$

我们可以把指定边 $(x, y)$ 拆分成 $(0, x)$ 与 $(0, y)$，$0$ 号节点当作树的根节点，且上文的指定边到 $i$ 号节点就是 $0$ 号节点到 $i$ 号节点。

具体请见代码：

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
#define int long long // 要开 long long

const int maxn = 1e6 + 10;
struct node {
    int to, nxt;
} edge[maxn >> 1];
int cnt, head[maxn]; // 链式前向星
int n, m, k, ans = 0, a[maxn], num[maxn], dp[maxn][2];

void add (int u, int v) {
    cnt ++;
    edge[cnt].to = v;
    edge[cnt].nxt = head[u];
    head[u] = cnt;
} // 加边

void add_edge (int u, int v) {
    add (u, v); add (v, u);
    num[u] ++; num[v] ++;
} // 别忘了更新 num

void dfs (int u, int fa) {
    dp[u][0] = dp[fa][0] * (num[fa] - 1);
    dp[u][1] = (dp[fa][1] + 1) * (num[fa] - 1) - 1;
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (v == fa) continue;
        dfs (v, u);
    }
} // 树形 dp

signed main() {
    scanf ("%lld%lld%lld", &n, &m, &k);
    for (int i = 1; i <= m; ++i) {
        scanf ("%lld", &a[i]);
    }
    sort (a + 1, a + m + 1); // 不要忘记排序哦！
    
    int x, y; scanf ("%lld%lld", &x, &y); x ++; y ++;
    add_edge (1, x); add_edge (1, y);
    for (int i = 2; i < n; ++i) {
        int u, v; scanf ("%lld%lld", &u, &v); u ++; v ++;
        add_edge (u, v);
    }
    dp[1][0] = dp[1][1] = k;
    dfs (x, 1); dfs (y, 1);
    
    for (int i = 2; i <= n + 1; ++i) {
        if (num[i] == 1) {
            ans += upper_bound (a + 1, a + m + 1, dp[i][1]) - lower_bound (a + 1, a + m + 1, dp[i][0]); // 上界查找与下界查找
        }
    }
    printf ("%lld", ans * k); // 乘 k 别忘了
    return 0;
}
```


---

## 作者：hzoi_zxb (赞：0)

本题首先观察性质，对于一群蚂蚁，其走过的路不会在走，也就是说路径唯一，这样每一个叶子到食蚁兽所在边路径唯一。

我们结合除法向下取整的性质：

$$\left \lfloor \frac{\left \lfloor\frac{m}{a}\right \rfloor}{b} \right\rfloor=\left \lfloor \frac{m}{ab}\right \rfloor$$

所以我们每一个叶子得到的除数我们可以知道，那么对应的食蚁兽区间是 $num\times (k+1)-1$ 到 $num\times k$。

总体来说根据第一个边把树分两部分，分别以两个端点对两边进行 DFS，然后到叶子就就二分出对应的蚁群，二分可以采用 lower_bound 和 upper_bound 来解决。

复杂度 $\mathcal O(nlogm)$。

code

```cpp
#include<bits/stdc++.h>
#define N 1000005
using namespace std;
int n,g,k;
int du[N],head[N],root1,root2,sum,tot,ji;long long ant[N],ans;
struct ddd
{int to,nxt;}bian[N<<1];
namespace AYX
{   inline void add(int u,int v)
    {   bian[++tot].to=v;
        bian[tot].nxt=head[u];
        head[u]=tot;
    }
    inline void dfs(int x,int fa,long long val)
    {   if(du[x]==1)
        {   int l=lower_bound(ant+1,ant+1+g+2,val*k)-ant;
            int r=upper_bound(ant+1,ant+1+g+2,val*(k+1)-1)-ant;
            ans+=(r-l)>0?(r-l):0;
            return;
        }
        for(int i=head[x];i;i=bian[i].nxt)
        {   int v=bian[i].to;
            if(v==fa)continue;
            dfs(v,x,val*(du[x]-1));
        }
    }
    inline short main()
    {   scanf("%d%d%d",&n,&g,&k);
        ant[1]=-9999999999999999;ant[g+2]=9999999999999999;
        for(int i=2;i<=g+1;++i)scanf("%lld",&ant[i]);
        for(int i=1;i<n;++i)
        {   int a,b;
            scanf("%d%d",&a,&b);
            if(i==1)root1=a,root2=b;
            add(a,b);add(b,a);
            du[a]++;du[b]++;
        }
        sort(ant+1,ant+1+g+2);
        dfs(root1,root2,1);
        dfs(root2,root1,1);
        printf("%lld\n",ans*k);
        return 0;
    }
}
signed main()
{   return AYX::main();
}
```


---

## 作者：renhao (赞：0)

最后到达的只有一条边。

很显然，这条边把整个树切成两块。

由于每个节点在一个时刻只有一群蚂蚁，所以每个叶子节点是独立的。

分别考虑每个叶子节点到这条路径，可以发现这个叶子节点到达那条路径使剩下蚂蚁为k的初始蚂蚁量是一个连续的区间(因为向下取整的特点)

所以只要反向推出每个叶子节点的区间边界就可以了。

$L[x]$ 表示 $x$ 最少取 $L[x]$ 使到那条路径剩下蚂蚁为 $k$

$R[x]$ 表示 $x$ 最多取 $R[x]$ 使到那条路径剩下蚂蚁为 $k$

这样分别转移一下就可以了

```cpp
void dfs(int x,int f){
	for(int i=0;i<E[x].size();i++){
		int V=E[x][i];
		if(V==f) continue;
		L[V]=L[x]*(E[x].size()-1);
		R[V]=R[x]*(E[x].size()-1)+(E[x].size()-1)-1;
		if(L[V]>2e9) L[V]=2e9;
		if(R[V]>2e9) R[V]=2e9;
		dfs(V,x);
	}
}
```
然后再原序列里面二分，或者把边界排序后直接两个指针扫过去就可以了。
复杂度都是 $\Theta( n * \log n) $的。

代码很丑,那个双指针写的很臭。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const int N=1e6+10;
int n,g,k,m[N];
vector<int>E[N],q1,q2;
ll L[N],R[N];
void addedge(int u,int v){
	E[u].pb(v);
	E[v].pb(u);
}
void dfs(int x,int f){
	for(int i=0;i<E[x].size();i++){
		int V=E[x][i];
		if(V==f) continue;
		L[V]=L[x]*(E[x].size()-1);
		R[V]=R[x]*(E[x].size()-1)+(E[x].size()-1)-1;
		if(L[V]>2e9) L[V]=2e9;
		if(R[V]>2e9) R[V]=2e9;
		dfs(V,x);
	}
}
int main(){
	scanf("%d %d %d",&n,&g,&k);
	for(int i=1;i<=g;i++) scanf("%d",&m[i]);
	sort(m+1,m+g+1);
	int s=0,t=0;
	for(int i=2;i<=n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		addedge(u,v);
		if(i==2) s=u,t=v;
	}
	L[t]=R[t]=L[s]=R[s]=k;
	dfs(s,t);
	dfs(t,s);
	for(int i=1;i<=n;i++){
		if(E[i].size()==1){
			q1.pb(L[i]);
			q2.pb(R[i]);
		}
	}
	sort(q1.begin(),q1.end());
	sort(q2.begin(),q2.end());
	int r1=0,r2=0;
	ll ans=0;
	for(int i=1;i<=g;i++){
		while(r1<q1.size()&&q1[r1]<=m[i]){
			ans-=i-1;
			r1++;
		}
		while(r2<q2.size()&&q2[r2]<m[i]){
			ans+=i-1;
			r2++;
		}
	}
	while(r1<q1.size()){
		ans-=g;
		r1++;
	}
	while(r2<q2.size()){
		ans+=g;
		r2++;	
	}
	printf("%lld\n",ans*k);
	return 0;
}
```




---

