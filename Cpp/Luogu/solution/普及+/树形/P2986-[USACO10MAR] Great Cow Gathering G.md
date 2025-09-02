# [USACO10MAR] Great Cow Gathering G

## 题目描述

Bessie 正在计划一年一度的奶牛大集会，来自全国各地的奶牛将来参加这一次集会。当然，她会选择最方便的地点来举办这次集会。

每个奶牛居住在 $N$ 个农场中的一个，这些农场由 $N-1$ 条道路连接，并且从任意一个农场都能够到达另外一个农场。道路 $i$ 连接农场 $A_i$ 和 $B_i$，长度为 $L_i$。集会可以在 $N$ 个农场中的任意一个举行。另外，每个牛棚中居住着 $C_i$ 只奶牛。

在选择集会的地点的时候，Bessie 希望最大化方便的程度（也就是最小化不方便程度）。比如选择第 $X$ 个农场作为集会地点，它的不方便程度是其它牛棚中每只奶牛去参加集会所走的路程之和（比如，农场 $i$ 到达农场 $X$ 的距离是 $20$，那么总路程就是 $C_i\times 20$）。帮助 Bessie 找出最方便的地点来举行大集会。

## 说明/提示

$1\leq N\leq 10^5$，$1\leq A_i\leq B_i\leq N$，$0 \leq C_i,L_i \leq 10^3$。

## 样例 #1

### 输入

```
5 
1 
1 
0 
0 
2 
1 3 1 
2 3 2 
3 4 3 
4 5 3 
```

### 输出

```
15 
```

# 题解

## 作者：yybyyb (赞：90)

考虑如果依次枚举每一个点作为集会的地点

使用DFS进行计算

然后再依次比较

时间复杂度O(n^2)

但是n的范围太大，显然会超时。


那么，我们应当如何优化？

先看看样例

![这里写图片描述](http://img.blog.csdn.net/20170720231457332?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMzA5NzQzNjk=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)


通过一次O(n)的计算，很容易得出来

如果选择1号节点，答案就是17

既然O(n^2)的计算无法在时间内求解

那么是否可以递推出来呢？

显然是可以的。

观察如果已经知道1号节点所需的时间

那么，我们可以做如下假设：

① 所有的牛首先到达了1号节点

② 3号节点以及他子树上的节点都需要退回1->3的路径的长度

③ 除了3号节点以及他子树上的节点都需要前进1->3的路径的长度


通过上面的三条东西，我们就可以从任意一个父节点推出子节点的时间


所以，又是一遍O(n)的计算就可以推出最终的答案


```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
#define MAX 200100
#define ll long long
inline ll read()
{
      register ll x=0,t=1;
      register char ch=getchar();
      while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
      if(ch=='-'){t=-1;ch=getchar();}
      while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}
      return x*t;
}

ll dis[MAX],C[MAX],Q[MAX],f[MAX],Sum,Ans=1000000000000000000;

struct Line
{
      ll v,next,w;
}e[MAX];

ll h[MAX],cnt=1,N;

inline void Add(ll u,ll v,ll w)
{
      e[cnt]=(Line){v,h[u],w};
      h[u]=cnt++;
}
//使用两遍DFS
//第一遍以任意点为根节点计算一遍
//dis[i]表示以i为根的子树到根的距离之和 
ll DFS(ll u,ll ff)
{
      ll tot=0;
      for(ll i=h[u];i;i=e[i].next)
      {
               ll v=e[i].v;
               if(v!=ff)
               {
                      ll s=DFS(v,u);//子树上牛的数量 
                      dis[u]+=dis[v]+e[i].w*s;//统计 
                   tot+=s;//牛的个数
               }
      }
      return Q[u]=tot+C[u];
}
//第二遍计算偏移后的值
//先可以假设走到当前节点的父节点
//再让当前自己点所有牛退回来，父节点的所有牛走过去即可 
void DFS2(ll u,ll ff)
{
       for(ll i=h[u];i;i=e[i].next)
       {
                  ll v=e[i].v;
                  if(v!=ff)
                  {
                           ll ss=e[i].w;
                           f[v]=f[u]-Q[v]*ss+(Sum-Q[v])*ss;
                           DFS2(v,u);
                  }
       }
}

int main()
{
      N=read();
      for(ll i=1;i<=N;++i)
        C[i]=read();
      for(ll i=1;i<=N;++i)
        Sum+=C[i];//统计牛的总数 
      for(ll i=1;i<N;++i)
      {
                 ll u=read(),v=read(),w=read();
                 Add(u,v,w);
                 Add(v,u,w);
      }
      
      DFS(1,1);//求出以1为聚集处的结果 
      
      DFS2(1,1);//求出其他的偏移值
      
      for(ll i=1;i<=N;++i)
            Ans=min(Ans,f[i]);
      
        cout<<Ans+dis[1]<<endl;
        
        return 0;
}

```

---

## 作者：Magi_karp (赞：49)

全新做法 （题解很长但是代码就55行……）

#树的重心


##定义

- 树的重心：也叫树的质心。找到一个点,其所有的子树中最大的子树节点数最少,那么这个点就是这棵树的重心,删去重心后，生成的多棵树尽可能平衡。

##性质

- 性质 1 ：树中所有点到重心的距离和是最小的，一棵树最多有两个重心（比如就两个点连个边）。

- 性质 2 ：把两棵树通过加一条边得到一颗新的树，新的树的重心必然在连接原来两棵树重心的路径上。

- 性质 3 ：一棵树添加或者删除一个节点，树的重心最多只移动一条边的位置。


有边权无点权的树的重心怎么求呢？

首先根据dfs序把无根树变成有根树

处理出以点u为根的子书的结点个数为s[u]（包括自己）

那么点u的所有的子树中最大的子树节点数就是

max{max{s[v]}(v是u的子节点）,n-s[u](这是因为是有根树前面没有算上“父节点”，这里考虑进来）}

下面是代码：

（会发现这个重心的位置其实和边权是无关的）

（为什么无关留作思考咯）（当然接受私信 o(=·ω·=)m ）

···
```cpp
void treedp(int fa,int u)
{
    s[u]=1;//自己的一个点
    for (int i=fr[u];i;i=a[i].ne)
        if (a[i].t!=fa)
        {
            treedp(u,a[i].t);
            s[u]+=s[a[i].t];//s[u]是点u为根的子书的结点个数
            maxs[u]=max(maxs[u],s[a[i].t]);//maxs[u]是所有的子树中最大的子树节点数
        }
    maxs[u]=max(maxs[u],n-s[u]);//再考虑一下父节点
}
```
···
当然这个不是这道题啦

这个题是一颗又有边权又有点权的树hhh

怎么办呢

首先从蒙的角度来说

那就把”最大的子树节点数最少“改成“最大点权块最小”呗

那就是把原来的1换成点权咯

emmmm我还是要简单证明一下的

（考试的时候就要用“显然成立法”！）

我们的目的是把这个问题转化成之前那个重心问题

那么就要去掉点权。

也就是先把拥有c[u]头牛的农场u拆成c[u]个牛数为1的农场（就叫拆之后的为”分身农场“好啦）。

再考虑如何建边（逆向思考）：

如果最终选择的农场理应是这个农场，那么我们建的新图里面，它的“分身农场”的距离应该都是0

如果最终选择的农场不是这个农场而是农场A，那么“分身农场”一定都是分身前的农场到A的距离

得出一个本来就显然的结论……：“分身农场”之间是等价的

也就是每当选定农场沿某边（设边长为dis）向远移动时，每个分身农场贡献的不方便值都是dis

那么总共贡献了c[u]\*dis(c[u]是原农场牛数也是分身农场数）

ok，再合并回去了（根本就没建边啊(#`O′)喂！）

下面是这部分代码

···void treedp(int fa,int u)

```cpp
{
    s[u]=c[u];///就改了这里而已
    for (int i=fr[u];i;i=a[i].ne)
        if (a[i].t!=fa)
        {
            treedp(u,a[i].t);
            s[u]+=s[a[i].t];
            maxs[u]=max(maxs[u],s[a[i].t]);
        }
    maxs[u]=max(maxs[u],sum-s[u]);//这里sum是所有农场里面的牛数之和
}
```
···
好啦总代码贴上！

···
```cpp
#include<algorithm>
#include<cstdio>
using namespace std;
struct B
{
    int t,ne,d;
}a[200005];
int n,e,fr[100005],c[100005],s[100005],maxs[100005],sum;
void add(int f,int t,int d)
{
    a[++e].t=t;
    a[e].ne=fr[f];
    fr[f]=e;
    a[e].d=d;
}
void treedp(int fa,int u)
{
    s[u]=c[u];
    for (int i=fr[u];i;i=a[i].ne)
        if (a[i].t!=fa)
        {
            treedp(u,a[i].t);
            s[u]+=s[a[i].t];
            maxs[u]=max(maxs[u],s[a[i].t]);
        }
    maxs[u]=max(maxs[u],sum-s[u]);
}
void dfs(int fa,int u)//求一个最短路而已，因为s到这里已经没用了我就节约一下
{                          //哦对了我没有初始化是因为只有唯一路径，只被搜到一次，不需要取min，直接覆盖原值就行
    for (int i=fr[u];i;i=a[i].ne)
        if (fa!=a[i].t)
        {
            s[a[i].t]=s[u]+a[i].d;
            dfs(u,a[i].t);
        }
}
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%d",&c[i]),sum+=c[i];
    for (int i=1,x,y,z;i<n;i++)
        scanf("%d%d%d",&x,&y,&z),add(x,y,z),add(y,x,z);
    treedp(1,1);
    int an=1;
    for (int i=2;i<=n;i++)
        if (maxs[i]<maxs[an])//求出最大点权块最小的点（这种树的重心）
            an=i;
    s[an]=0;//现在an就是重心，以它为原点跑最短路
    dfs(an,an);//跑最短路
    long long ans=0;
    for (int i=1;i<=n;i++)
        ans+=s[i]*(long long)c[i];//纯模拟每个农场的c[i]头牛跑s[i]的路
    printf("%lld",ans);
}
···
```

---

## 作者：xfydemx (赞：37)

一类经典的树形dp问题。

考虑 f[i] 表达以i为根子树中奶牛到i的距离和。

第一次dfs从下至上递推出各点的 f[i] 和子树奶牛数 siz[i]

画图易知每个点的答案 d[i] 满足的方程 
```cpp
d[v] = d[u] - siz[v]*a[i].w + (cnt - siz[v])*a[i].w;

```
通过第二次dfs推得各点的 d[i] 

显然最小的 d[i] 即为答案 


```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cctype>
#include<cmath>
#define ll long long
using namespace std;
const int N = 1000005;
const ll INF = 1e55;
inline int read() {
    int s = 1, w= 0; char c = getchar();
    for(; !isdigit(c); c=getchar()) if(c=='-') s = -1;
    for(; isdigit(c); c=getchar()) w = 10*w+c-'0';
    return s*w;
}

ll m,n,ans=INF,cnt,inde,head[N],siz[N],c[N],f[N],d[N];

struct Edge{
    ll nxt,to,w;
}a[N];

inline void add(int x,int y,int w){
    a[++inde].to=y;
    a[inde].nxt=head[x];
    a[inde].w=w;
    head[x]=inde;
}

inline void dfs (int u, int fa) {
	siz[u] = c[u];
	for(int i = head[u]; i; i = a[i].nxt) {
		int v = a[i].to;
		if(v == fa) continue;
		dfs(v,u);
		siz[u] += siz[v];
		f[u] = f[u] + f[v] + siz[v] * a[i].w;
	}
}

inline void dp (int u, int fa) {
	for(int i = head[u]; i; i = a[i].nxt) {
		int v = a[i].to;
		if(v == fa) continue;
		d[v] = 1LL*d[u] - siz[v]*a[i].w + (cnt - siz[v])*a[i].w;
		ans = min(ans, d[v]);
		dp(v,u);
	}
}

int main() {
	int u,v,w;
	n = read();
	for(int i=1; i<=n; i++){
		c[i]=read(); 
		cnt += c[i];
	}
	for(int j=1; j<n; j++){
		u = read(); v = read(); w=read();
		add(u,v,w);
		add(v,u,w);
	}
	dfs(1,0);
	d[1]=f[1];
	ans = min(ans, d[1]);
	dp(1,0);
	printf("%lld\n", ans*1LL);
	return 0;
}
```

---

## 作者：James_Brady (赞：29)

考虑树形DP。

我们设$dp[u]$为以$u$为汇合点的所有奶牛的行走距离和。

我们先考虑子树内的情况（设为$dp1$），

当我们把儿子节点$v$向上转移时，儿子节点的子树内的所有节点都要先走到$v$节点再走$e(u,v)$这条边到$u$节点。

所以对$dp1[u]$的贡献为$dp1[v]+siz[v]*e(u,v)$  ($siz[u]$表示$u$子树内的所有节点的奶牛数之和)

再考虑子树外的情况（设为$dp2$），

对于$u$的儿子$v$，$u$子树以外的节点一定要走到$u$再通过$e(u,v)$这条边到达$v$节点，同时$v$的兄弟节点子树的所有节点都要走到$u$再通过$e(u,v)$这条边走到$v$。

所以$u$对$dp2[v]$的贡献为：

$dp2[u]+dp1[u]-(dp1[v]+siz[v]*e(u,v))+(siz[1]-siz[v])*e(u,v)$

时间复杂度$O(n)$

记得开**long long**！

code:

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
struct nod{
	int v;
	ll w;
	int nxt;
}e[200010];
int n,m,h[100010],cnt;
ll dp1[100010],dp2[100010],siz[100010],val[100010],ans=1e18;
void add(int u,int v,ll w)
{
	e[++cnt].v=v;
	e[cnt].w=w;
	e[cnt].nxt=h[u];
	h[u]=cnt;
}
void dfs(int u,int fa)//计算子树内的dp值
{
	siz[u]=val[u];
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;ll w=e[i].w;
		if(v==fa) continue;
		dfs(v,u);
		siz[u]+=siz[v];
		dp1[u]+=dp1[v]+siz[v]*w;
	}
}
void dfs1(int u,int fa)//计算子树外的dp值
{
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;ll w=e[i].w;
		if(v==fa) continue;
		dp2[v]=dp2[u]+dp1[u]-(dp1[v]+siz[v]*w)+(siz[1]-siz[v])*w;
		dfs1(v,u);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%lld",&val[i]);
	for(int i=1;i<n;i++)
	{
		int u,v;ll w;
		scanf("%d%d%lld",&u,&v,&w);
		add(u,v,w);
		add(v,u,w);
	}
	dfs(1,0);
	dfs1(1,0);
	for(int i=1;i<=n;i++)
	ans=min(ans,dp1[i]+dp2[i]);//枚举每个点作为汇合点
	printf("%lld",ans);
}
```


---

## 作者：忘怀星 (赞：10)

> 题解居然满了，然后我的方法好像和别人不一样？管理大大求过qwq（

#### 题意:

本题要求一个点，使得答案最小，需要得到这个最小值。

#### 题解：

其实我的想法大概就是贪心了，我们考虑一条边： $AB$，两边的奶牛数分别为 $a$ ， $b$  。就像这样：

![这里应该有图片？](https://cdn.luogu.com.cn/upload/image_hosting/9fhm09wq.png)

我们考虑这里是 $A$ 处的奶牛走向 $B$ 处更优，还是相反的选择更优。

显然，我们让牛数少的走向牛数多的一边答案更优。

因此，我们发现当一个点的 $c$ （当然不仅仅是读入的 $c$ 啦）大于总牛数 $sum$ 时，这个点显然就是最终集合点的最优解。

现在来讲讲如何来求这个 $c$ 。

我们设 dp[u] 为以 u 为节点树的某一边的所有奶牛走到 u 的最优答案。其中 $c$ 即为这一部分的奶牛总数。是不是很好理解？

不理解我还有图：

![这好像也应该有张图](https://cdn.luogu.com.cn/upload/image_hosting/pnl84abm.png)

其中 c[u] 就**可以**是 1+1+1+2 = 5 了。

当然，按照我这个定义， $c$ 并不是一下子就能够直接确定的，我们需要结合程序来看。

我的方法是拓扑排序（没想到吧hhh），本质是一个从树的叶子向里推的过程，我们在拓排的时候来更新 dp 和 c 。如果发现某一 点 u 有 $c[u] > sum/2 $ 那么 u 即为集合点（u 有且只有一个证明显然），跳过这步并将 u 记为 ans ，最后输出 dp[ans] 即可。

代码：

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define ll long long 
#define re register 
using namespace std;

const int N=1e6+7;
ll read()
{
	ll a = 0,x = 1;
	char ch = getchar();
	while(ch > '9' || ch < '0'){
		if(ch == '-') x = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		a = a*10 + ch - '0';
		ch = getchar();
	}
	return a*x;
}
ll c[N],n;

int head[N],go[N],cnt,nxt[N],du[N];
ll val[N];
void add(int u,int v,ll w)
{
	go[++cnt] = v;
	nxt[cnt] = head[u];
	head[u] = cnt;
	val[cnt] = w;
	du[u] ++;
}
queue<ll>q;
ll ins[N],dp[N],sum;
int main()
{
	n = read();
	for(re int i = 1;i <= n;i ++){
		c[i] = read();
		sum += c[i];
	}
	for(re int i = 1;i < n;i ++){
		int u = (int)read(),v = (int)read();
		ll w = read();
		add(u,v,w);add(v,u,w);
	}
	for(re int i = 1;i <= n;i ++){
		if(du[i] <= 1){
			q.push(i);
			ins[i] = 1;
		}
	}
	ll ans = 0;
	while(!q.empty()){
		ll u = q.front();
		q.pop();
		if(c[u] > sum/2) {ans = u;continue;}
		for(re int e = head[u];e;e = nxt[e]){
			ll v = go[e];
			
			dp[v] += dp[u] + c[u]*val[e];
			c[v] += c[u];
			if(ins[v]) continue;
			du[v] --;
			if(du[v] == 1){
				q.push(v);
				ins[v] = 1;
			}
		}
	}
	printf("%lld",dp[ans]);
	return 0;
}

```

写在最后：

- $c$ 存的应该是两段中较小的值吧
- 复杂度显然 O(n),除非你说 stl 的 queue 不是 O(n) 的
- 代码要是没有高亮不是我的锅qwq
- 图片丑就凑付看，别喷了

---

## 作者：丨Sky灬丨无惧 (赞：8)

### 题解。
 思路：刚开始做，求树的重心加上SPFA，感觉跟[医院设置](https://www.luogu.com.cn/problem/P1364)一样，就是数据范围较大，$N\le100000$，而且边权不为$1$,所以不能像医院设置一样用邻接矩阵了，于是使用链式前向星，几分钟搞完。交上去$90$分（懵逼），然后造了几组数据发现，有边权的树的答案不一定在重心上。
 
 [$90$分](https://www.luogu.com.cn/record/32155017)（很神奇的数据）。
 
 于是经过老师的教导，成功学习到了这题的动态转移方程。
 
 第二次思路：先搜两遍树，都以$1$为根，第一遍求出假如奶牛们都到$1$集会的不方便程度和改良版的子树节点数（改成点权）。即如下：
 
 ```cpp
void tree(int x,int f) {//正常的子树节点。
	d[x]=1;//正常只要1.
	for(int i=b[x]; i; i=a[i].next) {
		int v=a[i].v;
		if(v==f)continue;
		tree(v,x);
		d[x]+=d[v];
	}
}
```
```
void tree(int x,int f) {//此题的子树点权值。
	d[x]=c[u];//c数组为此题中各个点的奶牛数。
	for(int i=b[x]; i; i=a[i].next) {
		int v=a[i].v;
		if(v==f)continue;
		tree(v,x);
		d[x]+=d[v];
	}
	return;
}
```
其中数组含义可以对照待会的完整代码。

第二遍搜索当转移到其他点集会时的不方便程度，此时可举一个例子：[还是医院设置](https://www.luogu.com.cn/problem/P1364)。

![](https://cdn.luogu.com.cn/upload/pic/166.png)

可以看出$1$处的不方便程度为：$4\times1+13\times0+12\times1+20\times2+40\times2=136$。

当转移至$3$处时的不方便程度为：$4\times2+13\times1+12\times0+20\times1+40\times1=81$

我们发现$3$处及其子树的点的路程都少了$1$，而$3$处子树外的点的路程增多了$1$，而且其中每个单项式因为因为边权为$1$的缘故其实少了$\times1$。于是我们可以推出方程：$e(v)=e(u)-d(v)\cdot a(i).w+(s-d(v))\cdot a(i).w$

代入例子即$3$点的不方便程度等于，$1$点的不方便程度减去$3$点的子树点权值乘转移的边的边权，加上$3$点外的子树点权值乘转移的边乘边权。即$136-72\times1+(89-72)\times1=81$

于是就可以开心地写代码了。

【代码】：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,u,v,w,k=0,s=0,ans=1e18,b[1000000],c[1000000],d[1000000];//开了long long，ans的值也要自然改大，否则会60分。
long long e[1000000],f[1000000];//记得要开long long否则会错。
struct sb {
	long long u,v,w,next;
};
sb a[1000000];
void rtt(int u,int v,int w) {
	a[++k].u=u;
	a[k].v=v;
	a[k].w=w;
	a[k].next=b[u];
	b[u]=k;
	return;
}
void tree(int u,int f) {
	d[u]=c[u];//开头已讲。
	for(int i=b[u]; i; i=a[i].next) {
		int v=a[i].v;
		if(v==f)continue;
		tree(v,u);
		d[u]+=d[v];//开头已讲。
		e[u]+=e[v]+a[i].w*d[v];//在第一遍计算出奶牛们到1集会时的不方便程度。
	}
}
void tre(int u,int fa) {
	for(int i=b[u]; i; i=a[i].next) {
		int v=a[i].v;
		if(v==fa)continue;
		e[v]=e[u]-d[v]*a[i].w+(s-d[v])*a[i].w;//计算前往点的不方便程度。
		ans=min(ans,e[v]);//如果更小，就更新答案。
		tre(v,u);
	}
}
int main() {
//	freopen("P2986.txt","r",stdin);
//	freopen("P2986.out","w",stdout);
	cin>>n;
	for(int i=1; i<=n; i++) {
		cin>>c[i];
		s+=c[i];//计算奶牛总数。
	}
	for(int i=1; i<n; i++) {
		scanf("%d%d%d",&u,&v,&w);
		rtt(u,v,w);
		rtt(v,u,w);
	}
	tree(1,0);//第一遍搜索。
	for(int i=2; i<=n; i++)e[i]=1e18;//除了第一点的不方便程度其他点都要重置。
	tre(1,0);//第二遍搜索。
	cout<<ans;
	return 0;
}
```
完结撒花。

---

## 作者：totorato (赞：8)

### 如果我们知道了每一颗子树中有多少头牛，我们还知道总共有多少头牛。现在只要求出在任何一个节点集合的花费，我们就可以O(1)转移到相邻的节点。这一样就可以O(n)得到所有的节点的花费。具体怎么转移呢？

### 到某一个节点集合的花费是由这个节点的所有子树的牛和父亲那边所有牛带来的。对于节点x,如果我们从它的父节点转移过来，那么以这个节点为根的子树中的牛到这个节点比到父节点少走了这条边的路程，而父节点的牛多走了这么多路程，所以只需要一个简单的计算就可以算出从父节点到子节点的花费变化量。

### 于是我们只需要O(1)求出到1号节点的花费，这么转移就可以得到所有节点的花费。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>

#define MX 200002

using namespace std;

int c[MX],u[MX],v[MX],w[MX],lnum;
int n,fst[MX],nxt[MX];
long long f[MX],totc;

void addeg(int nu,int nv,int nw)
{
    nxt[++lnum]=fst[nu],fst[nu]=lnum,u[lnum]=nu,v[lnum]=nv,w[lnum]=nw;
}

void input()
{
    int a,b,l;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&c[i]),totc+=c[i];
    for(int i=1;i<=n-1;i++)scanf("%d%d%d",&a,&b,&l),addeg(a,b,l),addeg(b,a,l);
}

long long num[MX],dis[MX];
void sch1(int x,int fa)
{
    num[x]=c[x];
    for(int i=fst[x];i;i=nxt[i])
    {
        if(v[i]==fa)continue;
        sch1(v[i],x);
        num[x]+=num[v[i]];
        dis[x]+=dis[v[i]]+num[v[i]]*w[i];
    }
}

long long mn=999999999999999;

void sch2(int x,int fa)
{
    mn=min(mn,f[x]);
    for(int i=fst[x];i;i=nxt[i])
    {
        if(v[i]==fa)continue;
        f[v[i]]=f[x]+(totc-num[v[i]])*w[i]-num[v[i]]*w[i];
        sch2(v[i],x);
    }
}

int main()
{
    input();
    sch1(1,0);
    f[1]=dis[1];
    sch2(1,0);
    cout<<mn<<endl;
    return 0;
}
```
### CodeForces219D也可以这么做


---

## 作者：welen (赞：8)

梁老师说写题解能提升自己对算法的理解~

本题解包含复杂度O（N²）复杂度暴力算法及O（N）复杂度dp算法，以及从暴力算法到dp算法的思考过程。

PS：本人在笔记本上写出暴力算法部分题解后，在学校机房写完了剩下的题解，返回笔记本时，网页在洛谷的博客编辑页面是打开的，于是按了一次提交题解（此时笔记本上的题解只包含暴力算法），于是在学校机房上写的完整题解被覆盖了，呜呜呜～～～

看到这道题，首先想到暴力，从每一个点开始dfs，计算当前点为集合点时的不方便程度，取最小的不方便程度为答案。每一次dfs复杂度为N，一共进行N次，总复杂度O(N²)。

在比赛上除非看到一眼就秒杀的题，不然的话，一定先写出暴力。于是我先把这道题的暴力给打出来了。
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int N;
int ora[100005];
int head[100005];
long long ans = 0x3f3f3f3f3f;
struct edge{
    int v,w,next;
};
edge ed[200005];
int top;
void addE(int u,int v,int w){
    ed[++top].v = v;
    ed[top].w = w;
    ed[top].next=head[u];
    head[u]= top;
    ed[++top].v = u;
    ed[top].w = w;
    ed[top].next = head[v];
    head[v] = top;
}
long long coc[100005];
long long dfs(int u,int father){
    coc[u] = ora[u];
    long long res = 0;
    for (int i = head[u]; i != 0; i=ed[i].next) {
        int v = ed[i].v;
        if(v==father){
            continue;
        }
        int w = ed[i].w;
        res += dfs(v,u);
        res += w*coc[v];
        coc[u]+=coc[v];
    }
    return res;
}
int main(){
    scanf("%d",&N);
    for (int i = 1; i <= N; ++i) {
        scanf("%d",&ora[i]);
        coc[i] = ora[i];
    }
    for (int j = 1; j <= N-1; ++j) {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        addE(a,b,c);
    }
    for (int i = 1; i <= N; ++i) {
        ans = min(ans,dfs(i,0));
    }
    printf("%d\n",ans);
    return 0;
}

```
第一次提交AC4个点，WA了第5个点，TLE了5个点。开了long long后还是WA，看了眼错误信息，输出的第二个字符为0，正确答案第二个字符为3。因为对数字有点敏感，所以想到了0x3f3f3f3f的第二个数字是0，猜到了估计是初识化小了，在后面补了1个3f。再次提交，AC前5个点，TLE后5个点，成功拿到到暴力分50分～

接下来继续想，因为老师告诉过这题是很经典的树上dp题，可以O（N）过，所以在往递推那边想:P

一次DFS，只能知道根节点的不方便数。如果想复杂度O（N）的情况下求出答案。看来需要递推。

因为我的暴力写法上记录了每个点及其子节点的总奶牛数（coc数组），所以很快想出了dp写法～

如果第一次dfs让我们知道一个点u的奶牛数coc\[u\]、u点的不方便数cnt，其子节点v的奶牛数coc\[v\]，u点到v的的路径长度w，如何推得v点的不方便数呢？

直接让u点及u点的所有子节点的奶牛走到v点就ok啊！从u点要走到v点的奶牛数为coc\[u\]-coc\[v\]，奶牛总路程为（coc\[u\]-coc\[v\]）*w。同时，来自v点的奶牛是“退回去”的，还需要减去coc\[v\]*w。

因此状态转移方程就是cntv = cnt+(coc\[u\]-coc\[v\])*w-coc\[v\]*w

注意1:因为u点的奶牛都走到v点了，并且v点还需要往下递归，所以需要将coc\[v\]赋值为coc\[u\]

注意2:此题的ans初始值需要比较大。本人提交第1次，80分，将ans的初始值后面加了1个3f后变成了90分，再加了一个3f后才AC。。。

下面附上O（N）复杂度dp代码～

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int N;
int ora[100005];
int head[100005];
long long ans = 0x3f3f3f3f3f3f3f3f;
struct edge{
    int v,w,next;
};
edge ed[200005];
int top;
void addE(int u,int v,int w){
    ed[++top].v = v;
    ed[top].w = w;
    ed[top].next=head[u];
    head[u]= top;
    ed[++top].v = u;
    ed[top].w = w;
    ed[top].next = head[v];
    head[v] = top;
}
long long coc[100005];
long long cnt;
long long dfs1(int u,int father){
    coc[u] = ora[u];
    long long res = 0;
    for (int i = head[u]; i != 0; i=ed[i].next) {
        int v = ed[i].v;
        if(v==father){
            continue;
        }
        int w = ed[i].w;
        res += dfs1(v,u);
        res += w*coc[v];
        coc[u]+=coc[v];
    }
    return res;
}
void dfs2(int u,int father){
//	printf("u :%d %d\n",u,cnt);
	long long tmp = cnt;
	ans = min(ans,tmp);
	for(int i = head[u]; i != 0; i = ed[i].next){
		int v = ed[i].v;
		if(v==father){
			continue;
		}
		int w = ed[i].w;
		cnt += (coc[u]-coc[v])*w;
		cnt -= coc[v]*w;
		int k = coc[v];
		coc[v]=coc[u]; //把奶牛借给下面的点 
		dfs2(v,u);
		coc[v]=k;
		cnt = tmp;
	}
}
int main(){
    scanf("%d",&N);
    for (int i = 1; i <= N; ++i) {
        scanf("%d",&ora[i]);
        coc[i] = ora[i];
    }
    for (int j = 1; j <= N-1; ++j) {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        addE(a,b,c);
    }
	cnt = dfs1(1,0);
	dfs2(1,0);
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：KillerXu (赞：7)

感觉自己思路比较复杂。

我们不妨先考虑只从儿子那边过来的路程之和。这显然可以用树形$dp$来解决。

我们设$f[x]$表示从$x$的所有儿子到$x$结点的路程之和，$size[x]$表示以$x$为根的子树中总共有多少只奶牛，不包括$x$结点。简单思考可以推出：

$$f[x] = \sum_{v \in son}(f[v] + size[v]×dis(x,v))$$

再考虑从父亲那边过来的路程之和，我们简单的推一推：

设$g[x]$表示从$x$的祖先到$x$结点的路程之和。

我们考虑$g[x]$从父亲那里转移，首先要加上以父亲为根、截掉以$x$为根的子树 的子树里所有的结点到父亲那里的路程之和，即$f[fa]-f[x]-(size[x]×dis(fa,x))$，然后肯定要加上父亲的祖先那边的路程之和即$g[fa]$，最后还要加上除以$x$为根的子树外，其他结点的所有奶牛到$x$结点的路程之和。
设$sum=\sum c[i]$即树中所有奶牛，那么可以表示为$(sum - size[x]) × dis(x,fa)$。

最终我们得出：

$$g[x] = f[fa]-f[x]-(size[x]×dis(fa,x))+g[fa]+(sum - size[x]) × dis(x,fa)$$

答案为$min \{f[i]+g[i] \}$

其实看似复杂，自己简单画一画图也就能很好的理解了。

## Code
```cpp
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <algorithm>

#define N 100005
#define ll long long

using namespace std;

ll size[N] , c[N] , f[N] , g[N] , sum = 0 , ans = 100000000000000;
struct Edge{
	int to , next , val;
}edge[N << 1];
int head[N] , tot = 0;
int n;

void add(int u , int v , int d){
	edge[++tot].to = v;
	edge[tot].val = d;
	edge[tot].next = head[u];
	head[u] = tot;
}

void solve1(int x , int fa){
	size[x] = c[x];
	for(int i = head[x]; i; i = edge[i].next){
		int v = edge[i].to;
		if(v == fa) continue;
		solve1(v , x);
		size[x] += size[v];
		f[x] += f[v] + size[v] * edge[i].val;
	}
}

void solve2(int x , int fa){
	for(int i = head[x]; i; i = edge[i].next){
		int v = edge[i].to;
		if(v != fa) continue;
		g[x] = f[v] - f[x] - (size[x] * edge[i].val) + g[v] + (sum - size[x]) * edge[i].val;
	}
	for(int i = head[x]; i; i = edge[i].next){
		if(edge[i].to != fa)
			solve2(edge[i].to , x);
	}
}

int main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		scanf("%lld" , &c[i]);
		sum += c[i];
	}
	for(int i = 1; i < n; i++){
		int u , v , d;
		scanf("%d%d%d" , &u , &v , &d);
		add(u , v , d);
		add(v , u , d);
	}
	
	solve1(1 , 0);
	solve2(1 , 0);
	
	for(int i = 1; i <= n; i++) ans = min(ans , f[i] + g[i]);
	cout << ans;
	return 0;
}
```

---

## 作者：bingliang (赞：7)

距离退役还有  200多小时   唉，高二得我怕是凉了  。

这道题，我们一步一步来想


对于部分分起到引起思考的作用

就是说我们这个题如果暴力的做的话是n^2的那我们是否可以优化呢。

后来我们发现对于   父节点x转移到他的任意一子节点都是01的（前提是预处理出距离，和有多少奶牛）那我们就可以做到on解出

 

再讲点事情解救本题的通过率，一些迷之数据   让我1/10的时间蒸发了

就是我们要找最小值但  由于题目数据较大  开小了会导致过不了

我的程还是   @初中Gunbuster大佬帮调的

ans初值就付1000000000000005ull;就好了

```cpp
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#define  ll long long
const int maxn=1e5+5;
const int maxm=3e5+5;
using namespace std;
ll n,c[maxn];
ll first[maxn],nxt[maxm];
ll a[maxm],b[maxm],l[maxm];
ll vis[maxn];
ll ju[maxn];
ll dp[maxn];
ll son[maxn];
ll sum;
void dfs1(int x){
        vis[x]=1;
    ll k=first[x];
    while(k!=-1){    
       if(!vis[b[k]]){
           ju[b[k]]=ju[x]+l[k] ; 
           dfs1(b[k]);
           son[x]+=son[b[k]];
           }
         k=nxt[k];
    }
    return ;
}
void dfs2(int x){
    vis[x]=1;
        ll k=first[x];
    while(k!=-1){
        if(!vis[b[k]]){
        dp[b[k]]=dp[x]-son[b[k]]*l[k]+(sum-son[b[k]])*l[k];         
        dfs2(b[k]);
         }
        k=nxt[k];
    }
    return;
}
int main(){
    cin>>n;
    for(ll i=1;i<=2*n;i++)
        first[i]=-1;
    for(ll i=1;i<=n;i++){
        cin>>c[i];
        son[i]+=c[i];
        sum+=c[i];
    }
    for(ll i=1;i<=2*(n-1);i++){
       cin>>a[i]>>b[i]>>l[i];
       nxt[i]=first[a[i]];
       first[a[i]]=i;
       i++;
       a[i]=b[i-1];b[i]=a[i-1];l[i]=l[i-1];
       nxt[i]=first[a[i]];
       first[a[i]]=i;
    }
    dfs1(1);
    for(ll i=2;i<=n;i++){
       dp[1]+=ju[i]*c[i];
       vis[i]=0;
    }
    dfs2(1);
    ll ans=1000000000000005ull;
    for(ll i=1;i<=n;i++)
       ans=min(ans,dp[i]);
    cout<<ans;
    return 0;
}
```

---

## 作者：cheeseYang (赞：3)

**看不懂的代码里有详细说明！！！！！！**

树形DP。。。。作为老是搞错链式前向星的我还是在艰难的检查下用链式前向星AC掉了。。。思路就是先假设所有奶牛都到一个点了，然后就可以从这个点推出所有点的状态，O(n)的动态规划，其实就是一维（也可以不用数组），我们记录每个点他的所有儿子节点（包括儿子节点的节点）的奶牛总数son[i]，dp[v]=dp[rt]-son[v]\*a[i].w+(sum-son[v])\*a[i].w;（sum是所有奶牛数总和），预处理的时候我们把所有点到第一个点的距离，接下来就可以愉快的处理出dp[1]了，然后就是一边DFs的动态规划并且每次比较取答案

```cpp
#include<bits/stdc++.h>
#define ri register int
#define For(i,k,j) for(ri i=k;i<=j;++i)
using namespace std;
const int maxn=100005;
long long n,head[maxn],c[maxn],e,dp[maxn],vis[maxn],d[maxn],son[maxn],sum,ans=1000000000000000000;//所以数据都要开long long 
struct node{
    int to,last,w;    
}a[maxn*2];
void add(int x,int y,int z){
    a[++e].last=head[x];    
    a[e].to=y;
    a[e].w=z;
    head[x]=e;
```
}//链式前向星存图，因为是无向的所以要存两遍
```cpp
int r(long long &x){
    char c=getchar();x=0;    
    while(!isdigit(c))c=getchar();
    while(isdigit(c))x=x*10+c-'0',c=getchar();
```
}//读入优化
```cpp
void init(int rt){
    vis[rt]=1;
    for(int i=head[rt];i;i=a[i].last){    
        int v=a[i].to;
        if(!vis[v]){
            vis[v]=1;
            d[v]=d[rt]+a[i].w;
            init(v);
            son[rt]+=son[v];//把他的儿子节点也累加
```
}//第一遍初始化，把每个点到第一个点的距离存到d数组里
```cpp
    }
}
void dfs(int rt){
    vis[rt]=1;
    for(int i=head[rt];i;i=a[i].last){
        int v=a[i].to;
        if(!vis[v]){
            vis[v]=1;
            dp[v]=dp[rt]-son[v]*a[i].w+(sum-son[v])*a[i].w;//状态转移方程，由第一个点递推出其他点，就像楼下的解释那样，sum是所有奶牛的总数，son[v]是他所有的子节点，因为由父亲节点推来，所以要减去son[v]*a[i].w，而其他点要加上(sum-son[v])*a[i].w
            //cout<<dp[v]<<endl;
            ans=min(ans,dp[v]);
            dfs(v);
        }
    }
}
int main(){
    cin>>n;    
    for(ri i=1;i<=n;++i){
        r(c[i]);
        son[i]=c[i];
        sum+=c[i];    //初始化
    }
    for(ri i=1;i<n;++i){
        long long x,y,z;    
        r(x),r(y),r(z);
        add(x,y,z);
        add(y,x,z);
    }
    init(1);
    for(ri i=2;i<=n;++i)
        dp[1]+=c[i]*d[i];//初始化第一个点的值
    memset(vis,0,sizeof(vis));
    dfs(1);
    ans=min(dp[1],ans);//最后还要和dp[1]比较一下
    cout<<ans;
    return 0;
}
```

---

## 作者：米奇 (赞：2)

## Description

有n个点,n-1条边,每个点上有ci个人.要选一个点使所有人到这个点的距离最小

------------

## Solution

这是道树形DP的基础题

我们考虑每一条边的贡献进行转移

我们先钦定1号点为根,通过dfs算一遍选1号点的答案

考虑转移:当前答案+(总结点数-2*转移的点的子树大小)*边权

------------

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=200005;
int n,m,sum,ans,x,y,z,t,a[N],dis[N],size[N],head[N];
struct node{
	int too,next,zh;
}edge[N];
void add(int a,int b,int c)
{
	edge[++t].too=b;edge[t].zh=c;
	edge[t].next=head[a];head[a]=t;
}
void dfs(int u,int fa)
{
	size[u]=a[u];
	for(int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].too;
		if(v==fa)continue;
		dis[v]=dis[u]+edge[i].zh;
		dfs(v,u);
		size[u]+=size[v];
	}
	ans+=dis[u]*a[u];
}
void dfs2(int u,int fa,int k)
{
	ans=min(ans,k);
	for(int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].too;
		if(v==fa)continue;
		dfs2(v,u,k+(sum-2ll*size[v])*edge[i].zh);
	}
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		sum+=a[i];//总人数
	}
	for(int i=1;i<n;i++)
	{
		scanf("%lld%lld%lld",&x,&y,&z);
		add(x,y,z);add(y,x,z);
     //前向星连边
	}
	dfs(1,0);//求选的点为1的答案
	dfs2(1,0,ans);//树形DP
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Prean (赞：2)

这道题让我想到了过去的某一道题“医院设置”啊！那道题我是怎么做的来着？？？我想想。。。。。。是枚举节点然后BFS。

想都不用想，不行的。因为这题的数据范围很大，连儿子表示法都用不了你还想用BFS？？？不存在的！

那么剩下的方法，好像就只有树形DP了吧。。。。。。
然而我在做这道题之前还不知道该咋做。。。怎么办？
~~那就去百度吧！~~自己推呗

首先我们找不到这棵树的根，那我们就设根是1，然后就可以从1开始DFS或BFS得到当1作为聚集点时的“不方便程度”，代码如下：
```cpp
void D1(int fa)
{
	f1[fa]=true;//标记该点以免儿子节点搜回来,当然也可以搜索时加一个变量表示父亲
	for(int i=h[fa];i;i=e[i].nx)if(!f1[e[i].to])
	{
		D1(e[i].to);
		dp[fa]+=a[e[i].to]*e[i].data+dp[e[i].to];//计算距离，其中dp[e[i].to]是子树的大小，a[e[i].to]是子树的权和，因为整个子树到达这个节点都要多走这一段距离，所以需要乘e[i].data
		a[fa]+=a[e[i].to];//计算子树的大小
	}
}
```
然后我们就得到了根节点的“不方便程度”。那么下一步该怎么办呢？我们先假设一下，假如奶牛们不想去根节点了，想去根节点的一个儿子节点，那该怎么办呢？这时这棵树被这条边分成了两部分：根节点的子树和除这课子树之外的根节点的树。根节点的子树本来要多走那条边的距离，现在都不用走了，不方便程度就减少了子树的权和乘那条边的长度。然而以根节点为根的子树本来可以就这样的，但是突然换了一个聚集点，就要多走那条边的长度，就多了子树的大小乘那条边的长度。可是现在的子树大小怎么计算你？既然被分成了两棵子树，那么这棵子树的大小就是总的权和减去子树的大小，也就是a[1]-a[son]。这样，我们得到了状态转移方程：
```
dp[son]=dp[fa]+(a[1]-2*a[son])*e[i].data
```
这一部分的代码如下：
```cpp
void D2(int fa)
{
	f2[fa]=true;
	for(int i=h[fa];i;i=e[i].nx)if(!f2[e[i].to])
	{
		dp[e[i].to]=dp[fa]+(a[1]-2*a[e[i].to])*e[i].data;
		D2(e[i].to);
	}
}
```


然后我们只要再跑一遍dp数组找最小值就行了。完结撒代码：
```cpp
#include<iostream>
using namespace std;
class Edge{public:int to,nx,data;}e[200000];
int n,cnt,h[100005];bool f1[100005],f2[100005];
long long dp[100005],a[100005];
void AddEdge(int x,int y,int data)
{
	e[++cnt].to=y;e[cnt].nx=h[x];e[cnt].data=data;
	h[x]=cnt;
}
void D1(int fa)
{
	f1[fa]=true;
	for(int i=h[fa];i;i=e[i].nx)if(!f1[e[i].to])
	{
		D1(e[i].to);dp[fa]+=a[e[i].to]*e[i].data+dp[e[i].to];
		a[fa]+=a[e[i].to];
	}
}
void D2(int fa)
{
	f2[fa]=true;
	for(int i=h[fa];i;i=e[i].nx)if(!f2[e[i].to])
	{dp[e[i].to]=dp[fa]+(a[1]-2*a[e[i].to])*e[i].data;D2(e[i].to);}
}
int main()
{
	int i;long long mi=0x7fffffffffffffff;
	ios::sync_with_stdio(false);cin>>n;
	for(i=1;i<=n;++i)cin>>a[i];
	for(i=1;i<n;++i)
	{
		int x,y,z;
		cin>>x>>y>>z;
		ddEdge(x,y,z);AddEdge(y,x,z);//一定要记得双向，不然坑死人
	}
	D1(1);D2(1);for(i=1;i<=n;++i)mi=min(mi,dp[i]);cout<<mi;
}
```

---

## 作者：jins3599 (赞：1)

做的时候感觉挺简单的...然后就自己YY出了树的重心的求法...但是挺麻烦的。

首先转移方程是很好推的：

$f(i)=f(v)+w*(\sum c-\sum c_v).$

然后我们初始的状态呢？没有！！！

于是我们尝试$O(n)$先预处理出来$f_1$的状态。

然后我就开始了：

 
- 跑一边树上前缀和快速计算树上距离

- $f_1 = \sum c_i*d_i$

于是最后跑一遍树形dp问题就解决了。

 ```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N =  100010;

int c[N] , n ;
int head[N] , cnt;
struct Edge {
	int to , nxt , w;
}e[N << 1];

void add(int u , int v , int w) {
	e[++ cnt].to = v;
	e[cnt].nxt = head[u];
	e[cnt].w = w;
	head[u] = cnt;
}

int dis[N] , f[N] , sumc[N];
void dfs3(int now , int ff) {
	sumc[now] = c[now];
	for(int i = head[now] ; i ; i = e[i].nxt) {
		int v = e[i].to;
		if(v == ff) continue;
		dis[v] += dis[now] + e[i].w;
		dfs3(v , now);
		sumc[now] += sumc[v];
 	}
}

void dfs4(int now , int ff) {
	for(int i = head[now] ; i ; i = e[i].nxt) {
		int v = e[i].to;
		if(v == ff) continue;
		f[v] = f[now] - sumc[v] * e[i].w + (sumc[1] - sumc[v]) * e[i].w;
		dfs4(v , now); 
	}
}

signed main () {
	scanf("%lld" , &n);
	for(int i = 1 ; i <= n ; i ++) scanf("%lld" , c + i);
	for(int i = 1 ; i <= n - 1 ; i ++) {
		int u , v , w;
		scanf("%lld %lld %lld" , &u, &v, &w);
		add(u , v , w); add(v , u , w);
	}
  
	dfs3(1 , 1);
	int ans = 1e15;
  	for(int i = 2 ; i <= n ; i ++) {f[1] += dis[i] * c[i];}
  	dfs4(1 , 1);
  	for(int i = 1 ; i <= n ; i ++) ans = min(ans , f[i]);
	printf("%lld\n" , ans);
 	return 0;
}
```

---

## 作者：Yuyuanqi (赞：1)

# 题解 P2986 [USACO10MAR]伟大的奶牛聚集

[题目链接](https://www.luogu.org/problem/P2986)

很好的一道树形dp的题目，我们观察每一个点i的答案，发现答案 f[i] 由两部分组成：

A1.i所有子树中的犇集中到i点

A2.除了i的子树中的所有犇集中到i的父亲节点，再走到i点

f[i] = A1 + A2

我们发现i的答案和i的孩子有关，也和i的父亲有关。一般这样的问题用两次dfs就可以解决。（由于选谁是根节点都无所谓，以下以1号节点为根）

第一次dfs我们求出每一个点的 f[i]， 意思是以i为根节点的子树中的牛集中到i点的“不方便值”。显然我们只要统计i点子树中牛的数量 q[i] 然后递推就可以了。

第二次dfs我们要把 f[i] 变成所有牛（而不是子树中的牛）集中到i点的不方便值。设i的父亲是j，i到j的距离是s。ans[i] 就等于 f[j] + (q[1] - q[i]) * s - q[u] * s。 （多想几遍就想通了，要理解上面A1A2的意思）

下面放代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 100005
#define ll long long
using namespace std;
inline int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}
ll ans = 1e15, f[N], c[N], q[N];
//f在两次dfs里含义不一样 c是每个点有多少牛 q是每个点和他的子树总共有多少牛
int tot, head[N], n;

struct edge
{
	int to, next, dis;
	edge() {}
	edge(int x, int y, int z) { to = x, next = y, dis = z; }
}a[2 * N];
//邻接表存图
void add(int from, int to, int dis)
{
	a[++tot] = edge(to, head[from], dis);
	head[from] = tot;
}

void dfs(int x, int fa)
{
	q[x] += c[x];
	for (int i = head[x]; i; i = a[i].next)
	{
		int u = a[i].to, s = a[i].dis;
		if (u != fa)
		{
			dfs(u, x);
			q[x] += q[u];
			f[x] += f[u] + q[u] * s;
		}
	}
}
//第一次dfs 求出A1
void dfs2(int x, int fa)
{
	for (int i = head[x]; i; i = a[i].next)
	{
		int u = a[i].to, s = a[i].dis;
		if (u != fa)
		{
			f[u] = f[x] + (q[1] - q[u]) * s - q[u] * s;
			dfs2(u, x);
		}
	}
}
//第二次dfs 求出每个点的答案
int main()
{
	n = read();
	for (int i = 1; i <= n; i++)
		c[i] = read();
	for (int i = 1; i < n; i++)
	{
		int a1 = read(), a2 = read(), a3 = read();
		add(a1, a2, a3);
		add(a2, a1, a3);
	}
	dfs(1, 1);
	dfs2(1, 1);
	for (int i = 1; i <= n; i++)
		ans = min(ans, f[i]); //在所有点中找到最方便的
	cout << ans << endl;
	return 0;
}
```


---

## 作者：TheShadow (赞：1)

# 闲扯

我做这道题的时候究极脑瘫。。

第一次提交忘开 $long\ long$ ，只有 $50$ 分；

第二次提交输出忘开 $long\ long$ ，只有 $70$ 分。。。

无语至极。。

# 题面

[题面](https://www.luogu.org/problem/P2986)

# Solution

要找出一个点，使得 $\sum\limits_{j!=rt} dis_j\cdot c_j$ 最小。

考虑换根。

先求出以 $1$ 号点为根节点时的答案，同时记录子树里面的奶牛数。对于每一条边，它的贡献为 $val\cdot size_{to}$ 。

然后 $DFS$ 换根。考虑将根节点转至 $u$ 时，只有 $rt$ 连向 $u$ 的边会改变答案。具体的：

1. 对于以 $u$ 为根结点的子树所包含的奶牛，他们要走的路程减少了 $val$ ，对于答案的贡献要减去 $size_u\cdot val$ 。
2. 对于其他的奶牛，他们要走的路程增加了 $val$ ，对于答案的贡献要加上 $(size_1-size_u)\cdot val$ 。（因为 $size_1$ 表示奶牛的总数）

然后最后的答案为 $\min\limits_{i=1}^n ans_i$ 。

# Code

```c++
#include<bits/stdc++.h>
#define del(a,i) memset(a,i,sizeof(a))
#define ll long long
#define inl inline
#define il inl void
#define it inl int
#define ill inl ll
#define re register
#define ri re int
#define rl re ll
#define mid ((l+r)>>1)
#define lowbit(x) (x&(-x))
#define INF 0x3f3f3f3f
using namespace std;
template<class T>il read(T &x){
	int f=1;char k=getchar();x=0;
	for(;k>'9'||k<'0';k=getchar()) if(k=='-') f=-1;
	for(;k>='0'&&k<='9';k=getchar()) x=(x<<3)+(x<<1)+k-'0';
	x*=f;
}
template<class T>il print(T x){
	if(x/10) print(x/10);
	putchar(x%10+'0');
}
ll mul(ll a,ll b,ll mod){long double c=1.;return (a*b-(ll)(c*a*b/mod)*mod)%mod;}
it qpow(int x,int m,int mod){
	int res=1,bas=x%mod;
	while(m){
		if(m&1) res=(res*bas)%mod;
		bas=(bas*bas)%mod,m>>=1;
	}
	return res%mod;
}
const int MAXN = 1e5+5;
int n,c[MAXN],u,v,d,head[MAXN],num_edge,size[MAXN];
ll ans,now;
struct Edge{
	int next,to,dis;
	Edge(){}
	Edge(int next,int to,int dis):next(next),to(to),dis(dis){}
}edge[MAXN<<1];
il add_edge(int u,int v,int dis){
	edge[++num_edge]=Edge(head[u],v,dis),head[u]=num_edge;
	edge[++num_edge]=Edge(head[v],u,dis),head[v]=num_edge;
}
il DFS(int u,int fa){
	size[u]=c[u];
	for(ri i=head[u];i;i=edge[i].next){
		if(edge[i].to==fa) continue;
		DFS(edge[i].to,u),size[u]+=size[edge[i].to];
		ans+=1ll*size[edge[i].to]*edge[i].dis;
	}
}
il DFS1(int u,int fa,ll res){
	ans=min(ans,res);
	for(ri i=head[u];i;i=edge[i].next){
		if(edge[i].to==fa) continue;
		DFS1(edge[i].to,u,res-1ll*edge[i].dis*size[edge[i].to]+1ll*edge[i].dis*(size[1]-size[edge[i].to]));
	}
}
int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n);
	for(ri i=1;i<=n;++i) read(c[i]);
	for(ri i=1;i<n;++i) read(u),read(v),read(d),add_edge(u,v,d);
	DFS(1,0),now=ans;
	for(ri i=head[1];i;i=edge[i].next) DFS1(edge[i].to,1,now-1ll*edge[i].dis*size[edge[i].to]+1ll*edge[i].dis*(size[1]-size[edge[i].to]));
	printf("%lld",ans);
	return 0;
}
```

# 总结

做题一定要算好数据范围，确定好是使用 $int$ 还是用 $long\ long$ ，不然炸了就不好了。

---

## 作者：RikoHere (赞：1)

很显然，我们最终选择的是以某一节点为根，然后其他节点到根节
点的权值和

按照一般树形dp的套路，往往需要先进行一次dfs来获取部分的信息

先默认`1`节点为根方便我们来进行预处理，**假设$f_{i,1}$为$i$节点的子节点到达$i$节点所需要的权值和$f_{i,2}$为其他节点(即非$i$子树中)到达$i$节点所需要的权值和**，答案即为$f_{i,1}+f_{i,2}$的最小值

第一次进行dfs,我们很容易就能处理出全部$f_1$的值，再用$f_1$的值进行递推不难递推出全部$f_2$的值

$$f_{v,2}=f_{u,2}+(f_{u,1}-f_{v,1}-val*size[v])+(T-size[v])*val$$

其中$u$为$e$节点的父亲(以`1`节点为根),$val$为连接$u,v$边的边权，$T$表示整颗树上奶牛的总数量，$size[i]$即以$i$为$i$节点子树上奶牛的总数量，特别的，我们认为$f_{1,2}=0$

只要两遍dfs即可求解，答案在更新$f_2$的同时顺带更新即可

 - **tip**:按照题目的数据范围答案可能会爆$int$

```
//2019/8/5->Riko->AtNCU->luoguP2986
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>

namespace Rikopack {
	bool digit (int ch) { return (ch <= '9' and ch >= '0');}
	inline int in () {
		int x = 0, ch = getchar(), base = 1;
		while (!digit(ch)) {
			if (ch == '-') base = -1;
			ch = getchar();
		}
		while (digit(ch)) x = x*10+ch-'0', ch = getchar();
		return x*base;
	}
	template <class T> inline void smax (T& x, T y) { if (x < y) x = y;}
	template <class T> inline void smin (T& x, T y) { if (x > y) x = y;}
	void print (int x) { printf("debug:%d\n", x);}
	const int MAXINT = 2123456789;
	#define LL long long
	//Believing heart is your power
}
using namespace Rikopack;
using namespace std;

const int N = 101000;
int n, root = 1; LL tot, ans;
LL f_1[N], f_2[N]; int Cows[N], Size[N];
int nxt[N<<1], to[N<<1], val[N<<1], head[N], edgeind;
inline void add (int u, int v, int x) {
	int i = ++edgeind;
	nxt[i] = head[u]; to[i] = v; val[i] = x; head[u] = i;
}

void Predfs (int x, int fa) {
	Size[x] += Cows[x];
	for (int i = head[x]; i; i = nxt[i]) {
		int e = to[i];
		if (e == fa) continue;
		Predfs(e, x);
		Size[x] += Size[e];
		f_1[x] += ((LL)Size[e]*val[i]+f_1[e]);
	}
}
void dfs (int x, int fa) {
	for (int i = head[x]; i; i = nxt[i]) {
		int e = to[i];
		if (e == fa) continue;
		f_2[e] = (f_1[x]-f_1[e]-(LL)val[i]*Size[e])+f_2[x]+(LL)(tot-Size[e])*val[i];
		smin(ans, f_1[e]+f_2[e]);
		dfs(e, x);
	}
}
void work () {
	Predfs(root, 0);
	ans = f_1[root];
	dfs(root, 0);
	printf("%lld", ans);
}
void prepare () {
	n = in();
	for (int i = 1; i <= n; ++i) {
		Cows[i] = in();
		tot += Cows[i];
	}
	for (int i = 1; i < n; ++i) {
		int u = in(), v = in(), x = in();
		add(u, v, x); add(v, u, x);
	}
	work();
}
int main () { prepare();}
```


---

## 作者：eros1on (赞：1)

[博客食用更佳~](https://tle666.github.io/2019/07/22/[USACO10MAR]%20Great%20Cow%20Gathering/)

# **Description**

给一个带边权与点权的树 $T$ （ $N$ 个结点 ），找一个点 $x$ 使 $\sum_{u \in T\ \&\ u \neq x} dis_{u,x} \times c_u$ 取最大值。

对于 $100\%$ 的数据，有 $1 \leq N \leq 100000,\ 1 \leq C_i \leq 1000$ 。

[题目链接戳这里](https://www.luogu.org/problemnew/show/P2986)

# **Solution**

树形 DP 。其实也不能完全算是 DP 。

我们使用调整法。对于点 $1$ ，我们可以 $O(n)$ 地算出 $f_1 = \sum_{u \in T\ \&\ u \neq 1} dis_{u,1} \times C_u$

然后递归考虑 $1$ 的儿子结点 $u$ 。我们比较一下 $f_1$ 和 $f_u$ 。可以将这棵树分为两部分。其中一部分（ $up$ ）与点 $1$ 在点 $u$ 的同一边，而另一部分（ $dn$ ）则与点 $u$ 在点 $1$ 同一边。当我们的注意力从 $1$ 转到 $u$ 上时，我们发现 $f$ 的值发生了一些变化。对于 $up$ 那部分的所有点，它们都被加上了一段路程 $dis_{1,u}$ ；而对于 $dn$ 那部分的所有点，它们都减去了 $dis_{1, u}$ 。

![题目中的样例](https://i.loli.net/2019/07/22/5d35c8f32385195587.png)

举个例子。对于图上的 $3$ ，我们发现 $f_3 = 1\times 1 + 1 \times 2 + 2 \times 6 = 15$ 。把它分成 $up$ 和 $dn$ ， $up = 3,\ dn = 12$ 。同理对于 $4$ ， $up = up_3 + 3 \times (1 + 1) = 9,\ dn = dn_3 - 3 \times 2 = 6$ 。

结果，我们发现 $up$ 和 $dn$ 都与前面有关系，所以只用记变化值就行啦。

**注意开 `long long` 。。**

# **Code**

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 100100;

#define int long long

int n, c[N], f[N], up[N], dn[N], size[N], ans = 1e18;
// f up dn 如上文；size[u] 以 u 为根的子树大小（此处指子树中 c[i] 之和）

struct edge { int v, w; edge *next; } pool[N << 1], *h[N], *cur = pool;

inline void addedge(int u, int v, int w) {
  edge *p = ++cur, *q = ++cur;
  p->v = v, p->w = w, p->next = h[u], h[u] = p;
  q->v = u, q->w = w, q->next = h[v], h[v] = q;
}

inline int calc(int u, int dis, int fa) { // 求 f[1]
  int v, res = c[u] * dis;
  for (edge *p = h[u]; p; p = p->next)
    if ((v = p->v) != fa) {
      res += calc(v, dis + p->w, u);
    }
  return res;
}

inline void pre(int u, int fa) { // 求 size
  int v; size[u] = c[u];
  for (edge *p = h[u]; p; p = p->next)
    if ((v = p->v) != fa) {
      pre(v, u); size[u] += size[v];
    }
}

inline void dfs(int u, int fa) { // 求 f
  int v;
  for (edge *p = h[u]; p; p = p->next)
    if ((v = p->v) != fa) {
      up[v] = (size[1] - size[v]) * p->w;
      dn[v] = -size[v] * p->w;
      f[v] = f[u] + up[v] + dn[v]; // 记得 up 和 dn 只是相对 u 的变化值
      dfs(v, u);
    }
}

signed main() {
  int u, v, w;
  scanf("%lld", &n);
  for (int i = 1; i <= n; i++) scanf("%lld", &c[i]);
  for (int i = 1; i < n; i++) {
    scanf("%lld%lld%lld", &u, &v, &w);
    addedge(u, v, w);
  }
  pre(1, 0); f[1] = calc(1, 0, 0); dfs(1, 0);
  for (int i = 1; i <= n; i++) ans = min(ans, f[i]);
  printf("%lld\n", ans);
  return 0;
}
```



---

## 作者：RetrO (赞：1)

一道树形dp的题主要是用2次dfs中的动归方程，每一次判断点是否相同然后计算到此路径继续进行深搜，然后size是用来做累加个数的,val是用来记录原本个数的，便于反悔，找到更优解。#include<bits/stdc++.h>

    
```cpp
#define ll long long
using namespace std;
struct edge{
    int to,next;ll val;
}G[400010];
ll cost;
int tot; 
int n;
int head[500010];
ll ans=1e18;
int val[400010];
ll size[400010];
ll c[400010];
ll len[400010];
void addedge(int a,int b,ll c)
{
    G[tot].to=b;
    G[tot].next=head[a];
    G[tot].val=c;
    head[a]=tot++;
}
void calc_ans(int x,int fa,ll cost)
{
    for(int i=head[x];~i;i=G[i].next)
        if(G[i].to!=fa)
        {
            ll t=cost-size[G[i].to]*G[i].val+(size[1]-size[G[i].to])*G[i].val;
            ans=min(ans,t);
            calc_ans(G[i].to,x,t);
        }
}
void dfs(int x,int fa)
{
    for(int i=head[x];~i;i=G[i].next)
    if(G[i].to!=fa)
        {
    len[G[i].to]=len[x]+G[i].val;
    cost+=len[G[i].to]*val[G[i].to];
    dfs(G[i].to,x);
    size[x]+=size[G[i].to];        
    }
}
int main()
{
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    scanf("%d",&val[i]),size[i]=val[i];
    for(int i=1;i<n;i++)
    {
        int a,b;ll c;
        scanf("%d %d %lld",&a,&b,&c);
        addedge(a,b,c);
        addedge(b,a,c);
    }
    dfs(1,0);
    ans=min(ans,cost);
    calc_ans(1,0,cost);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：abandentsky (赞：1)

题意：题目的意思很简单，就是求一个点，其他点到在这个点的距离和最小。很容易想到树的重心。（删除这个点，使得其他的连通块中节点最多的一块节点个数最小）。将无根树转化为有根树（随便找一个点最为根dfs一遍就好了）。这个题目也差不多。我们用dp[i]表示已i为根的子树（包括i）到i的花费。这样对于根节点root，dp[i]=dp[1]+dp[2]+.....+dp[n]其中dp[1]...dp[n]为root的子树。但是还得加上1..n这些子树到root的距离。就是leaves[1]...leaves[n]表示每个以i为根包括i的子树的节点个数。加上节点个数*dist就好了。这样dp[root]就表示以root为集合地点的花费，跑n遍树形dp只能得四十分，充分发掘树上信息，可以得到递推：（以样例为例）
ssize[1]=ssize[1]-ssize[3];
mm=dp[1]-dp[3]-ssize[3]*dist;
dp[3]=dp[3]+mm+ssize[1]*dist;
ssize[3]=K;
解释一下各个数组：ssize[i]表示以i为根的子树的节点个数。dp[i]表示以i为根的子树所有节点到i的花费。mm大家可以自己模拟一下。K表示整个树的节点个数。整个过程就是让自己的儿子节点转化为根节点的过程。代码中需要注意第二个dfs回溯过程。一定要记录（看其他大佬直接dfs了，是我菜）。还有最后比较大小，一定要开10000000000000以上，wrong一个点。
```c
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#define MAXN 100005
#define mod 100000000
#define INF 0x3f3f3f3f
using namespace std;

typedef long long  LL;
int n;
LL val[MAXN],dp[MAXN],ssize[MAXN],PP[MAXN],K;
struct Edge
{
    int from,to,dist;;
    Edge(int from=0,int to=0,int dist=0):from(from),to(to),dist(dist){}
};
vector<Edge> edges;
vector<int> G[MAXN];

LL dfs(int u,int fa)
{
    if(G[u].size()==1&&edges[G[u][0]].to==fa)
        return ssize[u]=val[u];
    LL leaves=val[u];
    for(int i=0;i<G[u].size();i++)
    {
        Edge &e=edges[G[u][i]];
        if(e.to==fa)
            continue;
        int v=e.to;
        LL tt=dfs(v,u);
        dp[u]+=tt*e.dist+dp[v];
        leaves+=tt;
    }
    return ssize[u]=leaves;
}

void dfs_2(int root,int fa)
{
    PP[root]=dp[root];
    for(int i=0;i<G[root].size();i++)
    {
        Edge &e=edges[G[root][i]];
        int v=e.to;
        if(v==fa)
            continue;
        int ss_rot=ssize[root];              //记录
        int dp_v=dp[v];                         //记录
        int ss_v=ssize[v];                       //记录
        ssize[root]=ssize[root]-ssize[v];
        LL mm=dp[root]-dp[v]-ssize[v]*e.dist;
        dp[v]=dp[v]+mm+ssize[root]*e.dist;
        ssize[v]=K;
        dfs_2(v,root);
        ssize[root]=ss_rot;                            //回溯
        dp[v]=dp_v;                                       //回溯
        ssize[v]=ss_v;                                    //回溯
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&val[i]);
    int u,v,w;
    for(int i=1;i<n;i++)
    {
        scanf("%d %d %d",&u,&v,&w);
        edges.push_back({u,v,w});
        edges.push_back({v,u,w});
        int mm=edges.size();
        G[u].push_back(mm-2);
        G[v].push_back(mm-1);
    }
    LL minn=10000000000000;  //一定要开大
    memset(dp,0,sizeof(dp));
    K=dfs(1,-1);                            //以1为根建立一个有根树
    dfs_2(1,-1);                             //递推过程
    for(int i=1;i<=n;i++)
        minn=min(minn,PP[i]);
    printf("%lld\n",minn);
    return 0;
}

```




---

## 作者：Caiyy (赞：1)

一道dp，不过这个树上dp算是很简单的了。

然而我调了一上午，最后发现是int和long long相加搞的错QAQ（没注意啊。）

暴力O(n^2)显然过不了，然而这是一棵树啊，我们枚举聚会的节点，可以通过它的父亲转移过去。

把节点1作为根。

第一遍dfs，1、求它本身节点权值以及子树节点权值的和；2、求所有节点到根的不方便值

第二遍dfs（即dp），从根节点开始，转移方程**f[v]=f[u]-size[v]\*e[i].w+(all-size[v])\*e[i].w;**

all表示牛的总数，c[]表示节点i的牛数，size[]表示它本身以及子树所有牛数，un表示不方便度，f[]表示以i为聚会节点的答案


```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 100003
#define ll long long
int cnt=0,all=0,n;
int head[N],c[N];
ll ans=100000000000000;
ll un[N],size[N],f[N];
bool vis[N];
struct edge{
    int to,next,w;
} e[N*2];
void add(int u,int v,int w){
    e[++cnt].to=v;
    e[cnt].w=w;
    e[cnt].next=head[u];
    head[u]=cnt;
}
void dfs(int u){
    vis[u]=true;
    size[u]=(ll)c[u];
    for(int i=head[u];i>-1;i=e[i].next){
        int v=e[i].to,w=e[i].w;
        if(!vis[v]){
            dfs(v);
            size[u]+=size[v];
            un[u]+=un[v]+(ll)size[v]*w;
        }
    }
}
void dp(int u){
    vis[u]=true;
    for(int i=head[u];i>-1;i=e[i].next){
        int v=e[i].to,w=e[i].w;
        if(!vis[v]){
            f[v]=f[u]-(ll)size[v]*w+(ll)(all-size[v])*w;
            dp(v);
        }
    }
}
int main(){
    memset(head,-1,sizeof(head));
    int u,v,w;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",c+i);
        all+=c[i];
    }
    for(int i=1;i<=n-1;i++){
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
        add(v,u,w);
    }
    dfs(1);
    f[1]=un[1];
    memset(vis,0,sizeof(vis));
    dp(1);
    for(int i=1;i<=n;i++)
        ans=min(ans,f[i]);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：安好 (赞：0)

/\*
树形dp+容斥原理

f[i]表示i为关键点答案

dis[i]表示以i为根子树和,第一遍树形dp统计

num[i]表示点权和,tot为总点权和

容斥原理: f[v]=f[now]+(tot-num[v])\*e[i].d-num[v]\*e[i].d; 第二遍树形dp统计

由父亲节点转移到儿子节点 容斥比较难想一些,建议画图比照代码理解

一定明确要求Σ点权\*边权最小，容斥的时候注意计算的是那个点的点权\*哪条边的边权

\*/







```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100007
using namespace std;
int head[N],w[N];
long long f[N],num[N],dis[N],tot;
int n,m,x,y,z,cnt;
struct edge
{
    int u,to,pre,d;
}e[N<<1];
inline void add(int u,int to,int d)
{
    e[++cnt].to=to;e[cnt].d=d;e[cnt].pre=head[u];head[u]=cnt;
}
void tree_dp1(int fa,int now)
{
    num[now]=w[now];
    for(int i=head[now];i;i=e[i].pre)
    {
        if(e[i].to==fa) continue;
        tree_dp1(now,e[i].to);
        num[now]+=num[e[i].to];
        dis[now]+=dis[e[i].to]+num[e[i].to]*e[i].d;
    }
}
long long mn=999999999999999LL;
void tree_dp2(int fa,int now)
{
    mn=min(mn,f[now]);
    for(int i=head[now];i;i=e[i].pre)
    {
        int v=e[i].to;
        if(v==fa) continue;
        f[v]=f[now]+(tot-num[v])*e[i].d-num[v]*e[i].d;
        tree_dp2(now,v);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) 
      scanf("%d",&w[i]),tot+=w[i];
    for(int i=1;i<n;i++)
    {
        scanf("%d%d%d",&x,&y,&z);
        add(x,y,z);add(y,x,z);
    }
    tree_dp1(0,1);
    f[1]=dis[1];
    tree_dp2(0,1);
    printf("%lld\n",mn);
    return 0;
}
```

---

