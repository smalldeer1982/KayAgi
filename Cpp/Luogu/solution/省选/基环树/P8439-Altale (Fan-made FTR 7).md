# Altale (Fan-made FTR 7)

## 题目背景

[![](https://cdn.luogu.com.cn/upload/image_hosting/inglwsjz.png)](https://music.163.com/#/program?id=2067229684)

为什么评级 7？

Powerless：Equilibrium FTR 9.

## 题目描述

小机器人又在钓星星了。

星星在天空中形成了若干个星座，每个星座有一个“中心点”，如果星星脱离了与中心点的直接或间接的联系，那么星星就会从星座中脱离，掉落到地面上。

经过小机器人日日夜夜的观测，他发现了这些星座的性质：每一个星座内部都是联通的，星星的联系的数量总与星座中星星的数量相等。

另外，不同的星座之间星星没有联系，同一个星座中的星星都有间接或直接的联系。

他通过观测天体运动给星星编了号，他发现每个星座的中心点都是星座中编号最小的星星。

可惜的是，小机器人只能通过随（diao）缘（yu）的方式获得取消这些联系的钥匙。

小机器人非常贪心，想要用尽量少的时间获得尽量多的星星。

他想要 $k$ 颗星星，你能告诉他他至少需要钓上几把钥匙吗？

如果你解决了这个问题，说不定小机器人会送给你几颗星星哦~

**[简化题意](https://www.luogu.com.cn/paste/5nhqqjzm)**

## 说明/提示

**本题采用捆绑测试。**

设星座共有 $l$ 个。

对于 $100\%$ 的数据，保证 $1\le n\le 10^6,1\le k\le n-l$。

Subtask 1：对于 $20\%$ 的数据，保证 $n\le 1000$。

Subtask 2：对于 $10\%$ 的数据，保证 $l\le 5$。

Subtask 3：对于 $20\%$ 的数据，保证 $l\le 15$。

Subtask 4：无特殊限制。

----

样例解释 $1$：

![](https://cdn.luogu.com.cn/upload/image_hosting/ov9db62k.png)

消除 $(1,4)$ 间联系即可。

样例解释 $2$：

![](https://cdn.luogu.com.cn/upload/image_hosting/wh22obzj.png)

消除 $(8,14),(8,10),(8,16)$ 三条联系即可。

可以证明没有消除联系更少的方法。

可能有别的方法也仅需要消除 $3$ 条联系。

## 样例 #1

### 输入

```
4 1
1 2
2 3
3 1
1 4```

### 输出

```
1```

## 样例 #2

### 输入

```
17 9
1 2
1 6
1 3
3 4
4 5
5 6
6 7
8 10
10 9
10 11
11 12
11 13
13 14
14 8
15 13
8 16
16 17```

### 输出

```
3```

# 题解

## 作者：Shanganze (赞：11)

####  首先简化题意：
 
 每一棵基环树上以其编号最小的点作为根，求要使至少 $k$ 个点不与任意一个根联通最少需要删几条边。
 
 首先考虑如果是一棵正常的树，最优方案就是删除根节点和它儿子的边，那么该儿子所在子树所有节点都与根节点不连通。可以看为一个费用为 $1$ 的物品，价值为该子树大小。
 
 那么转移到基环树上来看，基环树就是比普通树多一条边。
 
####  分类讨论：

1. 这条边所连接的两点在两个子树内，如果要获取其中一个子树的价值，就必须把这两个子树的与根的链接都断开。也就是把两个费用 $1$ 物品合并成一个费用 $2$ 物品，价值为两子树大小和。

2. 这条边所连接的两点在同一个子树内，显然不影响正常的答案（这是 $A$ 了之后才想到的）。
 
但是看下面这张图
 
 ![](https://cdn.luogu.com.cn/upload/image_hosting/wl0hhjum.png)
 
 如果 $k=7$ 时，按上面的考虑断开 $1-9$ $ $ $1-10$ $ $ $1-5$ 的三条边，但是显然可以断开 $1-10$ $ $ $5-2$ 的两条边。
 
 由此我们考虑到可以，我们还有一种选择：断开这个环上的一点向外的链接（不能是根），费用为 $1$，价值为相连那一点的子树大小。而且可以看出一个环上，最多只会断开一次对外的链接（如果断开两次，那么价值显然不如直接断开和根的链接）。所以我们只需要找出这个环上断开一条向外链接最大的价值。
 
 我们再考虑统计答案。通过上面的分析，我们已经将转化为一个子问题，有若干个费用为 $1$ 的物品，还有若干费用为 $2$ 的物品，每一个费用 $2$ 物品与一个费用 $1$ 物品相对应（也就是这两个物品中只能选一个）。
 
考虑贪心。

若单独费用为 $1$ 的物品选了 $x$ 个，一定是前 $x$ 大，这个很简单。

记绑定的物品费用 $1$ 的价值为 $a$，费用 $2$ 的价值为 $b$，分以下两类情况。

$2a \gt b$，这部分可以把费用 $2$ 价值 $b$ 的物品拆成费用 $1$ 价值 $b-a$ 的物品，然后和单独费用 $1$ 的物品放一起简单贪心，不赘述了。

$2a \le b$，把所有 $2a \le b$ 的分成一组，可以断言最多只会选一个费用 $1$ 的物品。

证明很简单，假设选了 $a_1,a_2$，不妨设 $a_1\le a_2$，那么 $a_1,a_2$ 替换为 $b_2$ 更优，因为 $b_2 \ge 2a_2 \ge a_1+a_2$。

这一组按 $b$ 降序排序后只有三种情况。选了一个前缀的费用 $2$，或者前缀里面刨去了一个 $b-a$ 最小的选费用 $1$，或者后缀里面选了一个 $a$ 最大的费用 $1$，总之可以枚举前缀，然后二分查找前面贪心的部分即可。

总复杂度 $O(n\log n)$。

贪心部分鸣谢 [Rosaya](https://www.luogu.com.cn/user/191748#main)

```c
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+10;
int n,m,v[N],z[N],siz[N],ans1[N],cnt1,cnt2,ans=1e9,cnt3;
struct a3{
	int a,b,c;
}ans2[N],ans3[N];
bool a33(a3 a,a3 b){return a.b>b.b;}
struct a1{int nex,to;}x[N<<1];
int head[N],p,k,f[N],t[N],maxx[N];
bool a2(int a,int b){return a>b;}
int find(int a){
	if(f[a]==a)return a;
	return f[a]=find(f[a]);
}
void add(int a,int b){
	x[++p].to=b;
	x[p].nex=head[a];
	head[a]=p;
}
void dfs(int a,int fa,int p){
	v[a]=1;siz[a]=1;
	for(int q=head[a];q;q=x[q].nex){
		int o=x[q].to;
		if(o!=fa){
			dfs(o,a,p);
			z[a]^=z[o];siz[a]+=siz[o];//想一下为什么用异或
		}
	}
	if(a==p)return;
	for(int q=head[a];q;q=x[q].nex){
		int o=x[q].to;
		if(o!=fa){
			if(z[o]==0){
				t[z[a]]=max(t[z[a]],siz[o]);
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for(int q=1;q<=n;q++)f[q]=q;
	for(int q=1;q<=n;q++){
		int a,b;
		cin>>a>>b;
		if(find(a)==find(b)){
			z[a]=z[b]=++cnt2;
			continue;
		}
		add(a,b);add(b,a);
		f[find(a)]=f[find(b)];
	}	
	for(int q=1;q<=n;q++){
		if(v[q]==0){
			dfs(q,q,q);
			for(int i=head[q];i;i=x[i].nex){
				int o=x[i].to;
				if(z[o]==0)ans1[++cnt1]=siz[o];
				else ans2[z[o]].b+=siz[o],ans2[z[o]].a=t[z[o]];
			}
		}
	}
	for(int q=1;q<=cnt2;q++){
		if(ans2[q].a*2>=ans2[q].b){
			ans1[++cnt1]=ans2[q].a;
			ans1[++cnt1]=ans2[q].b-ans2[q].a;
		}
		else{
			ans3[++cnt3]=ans2[q];
		}
	}
	sort(ans1+1,ans1+1+cnt1,a2);sort(ans3+1,ans3+1+cnt3,a33);
	for(int q=1;q<=cnt1;q++)ans1[q]+=ans1[q-1];
	for(int q=cnt3;q>=1;q--){ans3[q].c=max(ans3[q+1].c,ans3[q].a);}
	for(int q=1;q<=cnt3;q++){ans3[q].a=ans3[q].b-ans3[q].a;ans3[q].b+=ans3[q-1].b;}
	int o=1e9;
	for(int q=0;q<=cnt3;q++){
		o=min(ans3[q].a,o);
		int p=ans3[q].b,u=q*2;
		if(p>=k){
			ans=min(u,ans);continue;
		}
		if(ans1[cnt1]<k-p-ans3[q+1].a)continue;
		int w=lower_bound(ans1+1,ans1+1+cnt1,k-p-ans3[q+1].a)-ans1+1;ans=min(ans,u+w+1);
		if(ans1[cnt1]<k-p)continue;
		int i=lower_bound(ans1+1,ans1+1+cnt1,k-p)-ans1+1;ans=min(ans,u+i);
		if(ans1[cnt1]<k-p+o)continue;
		int j=lower_bound(ans1+1,ans1+1+cnt1,k-p+o)-ans1+1;ans=min(ans,u-1+j);	
	}
	cout<<ans;
	return 0;
}
```
代码不懂可以私信我。

  
  
 


---

## 作者：zsq147258369 (赞：11)

贪心。

题目叫你求最少要割几边才能有 $k$ 个点被隔离。

对于每一个基环树，我们讨论以下几种情况：

* 中心点在环外：

显然只能割断中心点周围的边。

* 中心点在环上：

如果把中心点的子树抛开，只有两种情况。

割一条边：若割环上的，那没有用，那就割其他点的儿子。此时最大隔离数为其他点中某个儿子的子树节点数的最大数。

割两条边：就割中心点两边的边，把环上其他点隔离，共隔离 $sum_i-siz_{ro_i}$（$sum_i$ 是基环树上节点总数，$ro_i$ 是基环树的根）。

显然割大于两条边没用。中心点的子树与上面的情况一起单独处理。

现在对于中心点在环上的树，我们定义它的权值 $val_{i,1/2}$ 表示割 1/2 条边的隔离数。

另外定义 $a$ 为割中心点周围的边的隔离数。以上的所有跑次拓扑及几次 dfs 即可（基环树基操）。

现在可以推出以下 6 种选择：

* 选一个没割过的树 $i$，割掉一条边，贡献是 $val_{i,1}$。

* 选一个割过一条边的树 $i$，再割掉一条边，贡献是 $val_{i,2}-val_{i,1}$。

* 选 $a$ 中的一条边割掉，贡献是 $a_i$。

* 选一个已经割掉一条边的树 $j$ 以及没割边的树 $i$，把割 $j$ 的边反悔掉，再割 $i$ 两条边，贡献是 $val_{i,2}-val_{j,1}$。

* 选一个已经割掉两条边的树 $j$ 以及没割边的树 $i$，把割 $j$ 的第二条边反悔掉，再割 $i$ 两条边，贡献是 $val_{i,2}-val_{j,2}+val_{j,1}$。

* 选一个被割过的 $a_j$，把其反悔掉，再割两条树 $i$ 的边，贡献是 $val_{i,2}-a_j$。

最后就是模拟以上过程，把贡献加起来，当贡献大于 $k$ 时退出即可。

还有就是注意把元素及时加到堆里，以及只有中心点周围可以的割的边。

~~[简化版？](https://www.luogu.com.cn/problem/CF436E)~~
~~别问我为什么蓝题会变紫题的简化。~~
# $code$
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+50,inf=1919810;

struct node
{
	int u,v,nxt;
}e[N];

struct wty
{
	int id,val;
	
	friend bool operator<(wty a,wty b)
	{
		return a.val<b.val;
	}
};

int out[N],cnt,head[N],siz[N],vis[N],ans,ro[N],Mi[N],tot,n,k,val[N][3];
queue<int>q;priority_queue<wty>q1,q2,q3,q4,q5,q6,q7;
/*
未选的,a[i]
未选的,b[i]
已选一次的,b[i]-a[i]
已选一次的,-a[i]
已选二次的,a[i]-b[i]
*/

void add(int u,int v)
{
	e[++cnt]=(node){u,v,head[u]};head[u]=cnt;++out[u];
	e[++cnt]=(node){v,u,head[v]};head[v]=cnt;++out[v];
}

void tp()
{
	while(!q.empty())
	{
		int x=q.front();q.pop();
		for(int i=head[x];i;i=e[i].nxt)
		{
			int v=e[i].v;
			--out[v];
			if(out[v]==1)q.push(v);
		}
	}
}

void dfs(int x,int fa)
{
	Mi[x]=x;siz[x]=1;
	for(int i=head[x];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa||out[v]>=2)continue;
		dfs(v,x);Mi[x]=min(Mi[v],Mi[x]);
		siz[x]+=siz[v];
	}
}

void dfs2(int x)
{
	ro[tot]=min(ro[tot],Mi[x]);vis[x]=1;
	val[tot][2]+=siz[x];
	for(int i=head[x];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(out[v]>=2)
		{
			if(!vis[v])
			dfs2(v);
		}
	}
}

void dfs3(int x,int no)
{
	vis[x]=1;
	for(int i=head[x];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(x!=ro[no]&&out[v]<2)val[no][1]=max(val[no][1],siz[v]);
		if(out[v]>=2)
		{
			if(!vis[v])
			dfs3(v,no);
		}
	}
}

void pre()
{
	while(q1.size()&&vis[q1.top().id]!=0)q1.pop();
	while(q2.size()&&vis[q2.top().id]!=0)q2.pop();
	while(q3.size()&&vis[q3.top().id]!=1)q3.pop();
	while(q4.size()&&vis[q4.top().id]!=1)q4.pop();
	while(q5.size()&&vis[q5.top().id]!=2)q5.pop();
}

main()
{
	std::ios::sync_with_stdio(false);
    std::cin.tie(0);
	memset(ro,127,sizeof ro);
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		int u,v;
		cin>>u>>v;
		add(u,v);
	}
	for(int i=1;i<=n;i++)if(out[i]==1)q.push(i);
	tp();for(int i=1;i<=n;i++)if(out[i]>=2)dfs(i,0);
	for(int i=1;i<=n;i++)if(out[i]>=2&&vis[i]==0)++tot,dfs2(i);
	memset(vis,0,sizeof vis);
	for(int i=1;i<=tot;i++)
	{
		int x=ro[i];
		for(int j=head[x];j;j=e[j].nxt)
		{
			int v=e[j].v;
			if(siz[v]>siz[x]||out[v]>=2)continue;
			q6.push((wty){i,siz[v]});
		}
		if(out[ro[i]]<2)//root 非环
		{
			q6.push((wty){i,val[i][2]-siz[x]});
			continue;
		}
		dfs3(ro[i],i);val[i][2]-=siz[ro[i]];
		q1.push((wty){i,val[i][1]});
		q2.push((wty){i,val[i][2]});
	}
	memset(vis,0,sizeof vis);
	while(1)
	{
		if(k<=0)break;
		++ans;
		int val1,val2,val3,val4,val5,val6;
		val1=val2=val3=val4=val5=val6=-inf;
		pre();
		if(!q1.empty())val1=q1.top().val;
		if(!q3.empty())val2=q3.top().val;
		if(!q2.empty()&&!q4.empty())val3=q2.top().val+q4.top().val;
		if(!q2.empty()&&!q5.empty())val4=q2.top().val+q5.top().val;
		if(!q6.empty())val5=q6.top().val;
		if(!q2.empty()&&!q7.empty())val6=q7.top().val+q2.top().val;
		if(val6>=val1&&val6>=val2&&val6>=val3&&val6>=val4&&val6>=val5)
		{
			k-=val6;
			q6.push((wty){q7.top().id,-q7.top().val});
			q7.pop();int x=q2.top().id;q2.pop();
			vis[x]=2;
			q5.push((wty){x,val[x][1]-val[x][2]});
			continue;
		}
		if(val5>val1&&val5>val2&&val5>val3&&val5>val4)
		{
			k-=val5;
			q7.push((wty){q6.top().id,-q6.top().val});q6.pop();
			continue;
		}
		if(val1>=val2&&val1>=val3&&val1>=val4)
		{
			k-=val1;int x=q1.top().id;q1.pop();
			vis[x]=1;
			q3.push((wty){x,val[x][2]-val[x][1]});
			q4.push((wty){x,-val[x][1]});
			continue;
		}
		if(val2>=val1&&val2>=val3&&val2>=val4)
		{
			k-=val2;int x=q3.top().id;q3.pop();
			vis[x]=2;
			q5.push((wty){x,val[x][1]-val[x][2]});
			continue;
		}
		if(val3>=val4)
		{
			k-=val3;int x=q2.top().id,y=q4.top().id;q2.pop(),q4.pop();
			vis[x]=2,vis[y]=0;
			q5.push((wty){x,val[x][1]-val[x][2]});
			q1.push((wty){y,val[y][1]});
			q2.push((wty){y,val[y][2]});
			continue;
		}
		k-=val4;int x=q2.top().id,y=q5.top().id;q2.pop(),q5.pop();
		vis[x]=2;vis[y]=1;
		q5.push((wty){x,val[x][1]-val[x][2]});
		q3.push((wty){y,val[y][2]-val[y][1]});
		q4.push((wty){y,-val[y][1]});
	}
	cout<<ans;
}
```

~~话说这首歌还挺好听~~

---

## 作者：dspt (赞：5)

## 题外话

我写这题的时候，这题有两篇题解，当时第一篇代码被我粘下来对拍了，结果被我 [Hack](https://www.luogu.com.cn/discuss/841054) 了。于是我只好去看第二篇，结果第二篇的代码有 93 行，一看就不可读，于是我带来一篇代码简短可读的题解。

鉴于 [CF436E **Cardboard Box**](https://www.luogu.com.cn/problem/CF436E) 比本题弱，被评为了紫题（CF 2600），所以强烈建议本题评紫。

&nbsp;

## 基环树

题目明说了，给定若干棵基环树，相信你已经会 BFS 找出基环树的环了。

接下来我们需要分类讨论，因为根是否在环上显然是两种不同的情况。

### 根不在环上

![](https://cdn.luogu.com.cn/upload/image_hosting/dsj56efq.png)

 如图，红色的三条边是可能被删掉的三条边，显然直接删与根相连的边最优，这三条边会使不与根联通边分别增加 1 个、3 个、2 个。

### 根在环上

![](https://cdn.luogu.com.cn/upload/image_hosting/op4b59f0.png)

显然红色的边并没有被影响。但除此之外我们有两种决策：

+ 删环上其它点子树里的边，如黄色的边
+ 删掉根在环上的其它两条边，如蓝色的边

我们仔细分析蓝色的情况，它具有一下性质：删一条边不会带来任何贡献，删两条边可以贡献所有不在根子树内的点的数量（图中的 $2,3,7,8,9,10$）。然而黄色的边删若干次总是删不完不在根子树内的其它点，因为环上的点删不掉，但是删一条边可以贡献根子树之外的某棵子树大小。

于是我们可以得到结论：如果基环树内（除了根子树内的红边）只删一条边：删除根子树之外的最大子树；删两条边：删除与根相连的两条环边；不会出现删更多边的情况。或者说，对于黄边和蓝边，要么只删两条蓝边，要么只删一条黄边。

&nbsp;

## 堆

分别维护三种颜色的边，删最少的边，考虑**贪心**。我们可以开三个堆分别维护红边、蓝边、黄边带来的贡献。

但是黄边和蓝边之间存在一些特殊的关系：不能同时选。于是我们需要特殊处理一下，我们并不是直接把蓝边和黄边的贡献开个堆记录。

对于任意存在黄边的基环树子树，设最大的根子树之外的贡献为 $g$（黄边贡献），基环树大小减去根子树大小为 $h$（蓝边贡献）。如果 $g\geqslant h-g$，我们可以直接把贡献看作 $g,h-g$ 两个独立的贡献。由于我们是在贪心的做，不难发现 $g$ 一定在 $h-g$ 之前被选到，如果只选 $g$ 那就是黄边贡献；如果两个都选了那就是蓝边贡献。 不会出现只选 $h-g$ 的情况，所以这样拆是正确的。如果 $g<h-g$，我们把 $h$ 放入蓝边的堆中，$g$ 放入黄边的堆中。

>  观察：黄边的堆中最多只选出一条边删。
>
> 证明：设选出了两条黄边，分别来自基环树 $i,j$，贡献分别是 $g_i,g_j$，令 $g_i\leqslant g_j$。但 $h_j>2g_j\geqslant g_i+g_j$，所以选基环树 $j$ 的蓝边更优。

不妨把贡献减到 $k$ 上，当 $k\leqslant0$ 就代表找到了答案，设当前在删第 $i$ 条边，流程如下：

1. 如果 $k$ 不超过红边堆中的贡献最大值或者黄边堆中的贡献最大值，说明删一条红边 / 黄边即可，答案为 $i$。
2. 如果 $k$ 不超过蓝边堆中的贡献最大值，说明删两条蓝边即可，答案为 $i+1$。
3. 如果蓝边堆中有边：如果红边堆中只有一条边 / 红边堆中贡献最大的两条边的贡献和小于等于蓝边堆中的贡献最大值，说明删两条蓝边更优，删除贡献最大的那两条蓝边，并且 $k$ 减去那两条边的贡献，$i\leftarrow i+2$ 。
4. 否则删红遍最优，删除贡献最大的红遍，并且 $k$ 减去那条边的贡献，$i\leftarrow i+1$ 。

注意到当删除蓝边堆中某棵基环树对应的蓝边贡献，我们要在黄边堆中删去那棵基环树的黄边贡献，可以在维护蓝边堆的时候每个节点额外维护对应基环树的黄边贡献即可。

堆需要支持随机删除、取最大值，可以手写基于 `priority_queue`的堆，但是我懒，直接用了 `multiset`。

&nbsp;

## 代码

[代码](https://www.luogu.com.cn/paste/4dt25u9i)比较短，良心的解释了变量和函数！还附带了 python 的代码生成器！

---

