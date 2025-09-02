# An overnight dance in discotheque

## 题目描述

The crowdedness of the discotheque would never stop our friends from having fun, but a bit more spaciousness won't hurt, will it?

The discotheque can be seen as an infinite $ xy $ -plane, in which there are a total of $ n $ dancers. Once someone starts moving around, they will move only inside their own movement range, which is a circular area $ C_{i} $ described by a center $ (x_{i},y_{i}) $ and a radius $ r_{i} $ . No two ranges' borders have more than one common point, that is for every pair $ (i,j) $ ( $ 1<=i&lt;j<=n $ ) either ranges $ C_{i} $ and $ C_{j} $ are disjoint, or one of them is a subset of the other. Note that it's possible that two ranges' borders share a single common point, but no two dancers have exactly the same ranges.

Tsukihi, being one of them, defines the spaciousness to be the area covered by an odd number of movement ranges of dancers who are moving. An example is shown below, with shaded regions representing the spaciousness if everyone moves at the same time.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF814D/5a49565ef74e61d7b40ab12eaa412e67e7b6d97c.png)But no one keeps moving for the whole night after all, so the whole night's time is divided into two halves — before midnight and after midnight. Every dancer moves around in one half, while sitting down with friends in the other. The spaciousness of two halves are calculated separately and their sum should, of course, be as large as possible. The following figure shows an optimal solution to the example above.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF814D/8da25989c38168302d4efff7470ec1e71f4e2366.png)By different plans of who dances in the first half and who does in the other, different sums of spaciousness over two halves are achieved. You are to find the largest achievable value of this sum.

## 说明/提示

The first sample corresponds to the illustrations in the legend.

## 样例 #1

### 输入

```
5
2 1 6
0 4 1
2 -1 3
1 -2 1
4 -1 1
```

### 输出

```
138.23007676
```

## 样例 #2

### 输入

```
8
0 0 1
0 0 2
0 0 3
0 0 4
0 0 5
0 0 6
0 0 7
0 0 8
```

### 输出

```
289.02652413
```

# 题解

## 作者：ljk123 (赞：4)

# An overnight dance in discotheque题解
其实可以看做一道结论题：只将覆盖次数为2的圆放到另一组。

我们可以将结论分解为两部分：

1.将覆盖次数为2的圆放到另一组。

2.不将覆盖次数大于2的圆放到另一组

![1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF814D/5a49565ef74e61d7b40ab12eaa412e67e7b6d97c.png)
![2](https://cdn.luogu.com.cn/upload/vjudge_pic/CF814D/8da25989c38168302d4efff7470ec1e71f4e2366.png)

在图中我们可以看到，覆盖次数为2的圆c3被放到另一空间，

此操作增加的面积为2(S圆c3-(S圆c4+S圆c5)[即S阴影<原来的>])=2S空<原来的>

覆盖次数为2的圆，S圆肯定大于等于S阴影<原来的>，S空<原来的>一定大于等于0，

就算里面的圆也有一些放放到另一组，S圆也一定定大于等于S阴影，故一定放。

将覆盖次数为2的圆放到另外一空间后，

原来覆盖次数大于2的圆，我们对任意互相包含的一组进行讨论。

若每组最外围的圆原先覆盖次数为奇数，即为阴影，则

放到另一空间，阴影变成空，空变成阴影，变化后的S阴影仍然小与S在外围的圆=S阴+S空（现在的）
减小的量为S空（现在的），S阴之前的。

而原先被这一组包括，却没有放到另一空间的，

若最外围为阴影，不变。

否则，增量<=S最外围的圆<=S阴（放到另一空间的之前的）(即减少量)，故不放。

若每组最外围的圆原先覆盖次数为偶数，即为空，

现在的空就是之前的空，不变，则第一空间的增量<=S最外围的圆，另一空间的减少量等于S最外围的圆，故也不放。
得证

没有画图工具，口胡说得很绕，敬请理解。

~~大家还是感性理解一下算了。~~

贴一下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1006;
int n,cnt=0,f[N],rr[N],head[N];
struct edge{int nxt,to;}e[N];
struct circle{long long x,y,r;}o[N];
double ans=0.00,pai=3.1415926535898;
inline void add(int u,int v){e[++cnt].nxt=head[u],e[cnt].to=v,head[u]=cnt;}
inline int read(){
   int T=0,F=1; char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-') F=-1; ch=getchar();}
   while(ch>='0'&&ch<='9') T=(T<<3)+(T<<1)+(ch-48),ch=getchar();
   return F*T;
}
bool check(int u,int v){
     double t=sqrt((o[u].x-o[v].x)*(o[u].x-o[v].x)+(o[u].y-o[v].y)*(o[u].y-o[v].y));
     return (1.0000*o[v].r>=t+o[u].r);
}
void dfs(int u,int d,long long v){
     if(d==2) v*=-1;
     ans+=v*pai*o[u].r*o[u].r;
     for(int i=head[u];i;i=e[i].nxt) dfs(e[i].to,d+1,-v); 
}
bool cmp(circle u,circle v){return u.r>v.r;}
int main(){
    n=read();
    for(int i=1;i<=n;++i) f[i]=n+1,rr[i]=1e7,o[i].x=read(),o[i].y=read(),o[i].r=read();
    sort(o+1,o+n+1,cmp);
    for(int i=1;i<=n;++i)
        for(int j=1;j<i;++j)
            if(check(i,j)&&o[j].r<rr[i]) f[i]=j,rr[i]=o[j].r;
    for(int i=1;i<=n;++i) add(f[i],i);
    dfs(n+1,0,-1),printf("%.9lf",ans);
    return 0;
} 
```


---

## 作者：皎月半洒花 (赞：4)

恶意评分成了一道黑题……本来应该是蓝色的啊$\rm{qaq}$

首先是奇怪的贪心，不过好像很合理的样子。大概就是一定要分成两堆的话，另一堆一定要放这一堆会冲突的圆。那么只需要记录覆盖层数的奇偶性，贪心地取就好了……

不过我是不敢在罚时的比赛里面随便交贪心，于是考虑一个$DP$。我们将之写作一个森林的形式，其中每棵树从上至下保持着半径的小根堆性质，且儿子一定会被父亲包含。那么在某棵树上，就一定有奇数层的贡献为$-1$,偶数层的贡献为$1$。

考虑用$dp[u][0/1][0/1]$表示以点$u$为根的子树里面，分成两堆之后，两堆分别的高度为偶数/奇数时的最优值。转移的时候从下向上$DP$，分类讨论一下就完了。

此处笔者选用的是官方题解里面比较优美的转移版本并且很闲地写了两个$sol$……

```cpp
#define MAXN 3050

using namespace std ;
const double Pi = acos(-1.0) ;
struct C{
	double x, y, r ;
}base[MAXN] ;
double Ans ;
int i, j, k ;
long long dp[MAXN][2][2] ;
int N, mark[MAXN], fa[MAXN] ; 

inline double dist(C A, C B){
	return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y)) ;
}
inline double get_S(C A){ return Pi * A.r * A.r ; }
inline bool check_in(C A, C B){ return A.r + B.r > dist(A, B) ; }
namespace DP{
	#define to(k) E[k].to
	struct Edge{
		int next, to ;
	}E[MAXN << 1] ;
	int head[MAXN], cnt ;
	inline void Add(int u, int v){
    	E[++ cnt].to = v, E[cnt].next = head[u], head[u] = cnt ;
    	E[++ cnt].to = u, E[cnt].next = head[v], head[v] = cnt ;
	}
	void do_dp(int u, int faa){
		long long f[2][2] ; memset(f, 0, sizeof(f)) ;
		for (int k = head[u] ; k ; k = E[k].next){
			if (to(k) == faa) continue ;
			do_dp(to(k), u) ;
			for (int ii = 0 ; ii <= 1 ; ++ ii)
				for (int jj = 0 ; jj <= 1 ; ++ jj)
					f[ii][jj] += dp[to(k)][ii][jj] ; 
		}
		for (int ii = 0 ; ii <= 1 ; ++ ii)
			for (int jj = 0 ; jj <= 1 ; ++ jj)
				dp[u][ii][jj] = max(f[ii ^ 1][jj] + (1ll * (ii ? -1 : 1) * base[u].r * base[u].r), 
									f[ii][jj ^ 1] + (1ll * (jj ? -1 : 1) * base[u].r * base[u].r)) ;
	}
	inline bool Comp(C A, C B){ 
		return A.r > B.r ; }
	void solve1(){
		sort(base + 1, base + N + 1, Comp) ;
		for (i = 1 ; i <= N ; ++ i) 
			for(j = i + 1 ; j <= N ; ++ j)
				if (check_in(base[i], base[j])) 
					if (!fa[j] || base[fa[j]].r > base[i].r) fa[j] = i ;
		for (i = 1 ; i <= N ; ++ i) if (fa[i]) Add(i, fa[i]) ;	
		for (i = 1 ; i <= N ; ++ i)	if (!fa[i]) do_dp(i, 0), Ans += dp[i][0][0] ;
		printf("%.8lf", Ans * Pi) ;  	
	}
}
namespace Greedy{
	inline bool Comp(C A, C B){ return A.r > B.r ; }
	void solve2(){
		sort(base + 1, base + N + 1, Comp) ;
		for (i = 1 ; i <= N ; ++ i) 
			for(j = i + 1 ; j <= N ; ++ j)
				if (check_in(base[i], base[j])) ++ mark[j] ;
		for (i = 1 ; i <= N ; ++ i) 
			if (!mark[i] || (mark[i] & 1)) Ans += get_S(base[i]) ; else Ans -= get_S(base[i]) ;
		printf("%.8lf", Ans) ;  	
	}
}
int main(){
	cin >> N ;
	for (i = 1 ; i <= N ; ++ i) 
		scanf("%lf%lf%lf", &base[i].x, &base[i].y, &base[i].r) ;
	if (N >= 500) DP :: solve1() ; else Greedy :: solve2() ; return 0 ; 
}
```

---

## 作者：ncwzdlsd (赞：1)

题中说的是圆，可以考虑把圆的关系转成树上边的关系。

显然，在图中，被覆盖次数为奇数的圆对答案的贡献为正，被覆盖次数为偶数的圆对答案的贡献为负。我们将每一个圆的面积按照从大到小排序，然后考虑圆的覆盖关系，如果圆 $i$ 覆盖了圆 $j$，那么我们就连边 $(i,j)$，同时记录这一组中面积最大的圆。

经过这样的操作之后，我们就把这一堆圆转化成了森林。考虑贪心策略，选面积大的圆一定更优，证明也很简单，对于一个圆的面积 $S_i$，选它的贡献是 $S_i$，不选它的贡献是 $-S_i$，该圆子树中正贡献面积与负贡献面积的差一定小于等于 $S_i$，所以对于一个圆，如果不选该圆，那么该圆（含子树）的整体贡献一定是负的，显然这是不如选择这个圆优的。由于这种贪心策略，所以我们把所有树的节点放入一个组，子节点放入一个组。

于是乎对于每一个圆的子树，累计奇数层的正贡献和偶数层的负贡献，即可得到答案。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=1005;
const double pi=acos(-1.0);
int head[maxn],nxt[maxn],to[maxn],cnt,pre[maxn];
double ans;

struct node{double x,y,r,S;}gg[maxn];

bool cmp(node a,node b){return a.r<b.r;}

void add(int x,int y)
{
	to[++cnt]=y;
	nxt[cnt]=head[x];
	head[x]=cnt;
}

double dis(int i,int j)
{return sqrt((gg[i].x-gg[j].x)*(gg[i].x-gg[j].x)+(gg[i].y-gg[j].y)*(gg[i].y-gg[j].y));}

void dfs(int x,int dep)
{
	for(int i=head[x];i;i=nxt[i])
	{
		if(dep%2==0) ans+=gg[to[i]].S;
		else ans-=gg[to[i]].S;
		dfs(to[i],dep^1);
	}
}

int main()
{
	int n;cin>>n;
	for(int i=1;i<=n;i++) cin>>gg[i].x>>gg[i].y>>gg[i].r,gg[i].S=pi*gg[i].r*gg[i].r;
	sort(gg+1,gg+n+1,cmp);
	for(int i=1;i<=n;i++)
		for(int j=1;j<i;j++)
			//连边操作：如果圆u覆盖圆v，连边(u,v)
			if(!pre[j]&&dis(i,j)<gg[i].r+gg[j].r) add(i,j),pre[j]=i;
	for(int i=1;i<=n;i++) if(!pre[i]) ans+=gg[i].S,dfs(i,0);
	printf("%.8lf",ans);
	return 0;
}
```

---

## 作者：出言不逊王子 (赞：0)

在智推里看到了这道题，来写一发。

首先我们看到了题目给出了一堆圆，然后我们发现这些圆不存在相交的情况。

也就是说，圆的包含关系正好可以构成一棵树，每个点的权值就是圆的半径的平方！

那么我们按照半径，从小到大给这些圆排个序，然后依次遍历每个圆。

对于每个圆，遍历半径比他大的其他圆，找到**第一个**包含他的圆，那么这个圆就是他的父亲了。

然后我们有了一堆树结构，也就是一个森林。容易发现不同树之间答案相互独立，所以我们对于每棵树分别求答案。

首先我们发现，最大的圆和第二大的圆一定是放在两个不同的组里的。

接下来我们发现，对于一个大圆，他的面积一定比他内部所有小圆的面积总和都大。

所以考虑分奇偶讨论，对于每棵树，我们把深度为奇数的点放在一个组，深度为偶数的点放在一个组，这样的话似乎可以把损失降低到最小。

然后我们写出了代码，过了第一个样例，但是第二个样例，我们会发现标准的输出是 $92\pi$，但是我们的输出只有 $72\pi$。

这是为什么呢？

因为我们把半径为 $6$ 这么大一个圆的位置给挖掉了，足足损失了 $(6^2-4^2)\times \pi=20\pi$ 的面积。如果把他放到另一个组去，就只会损失 $(6^2-5^2)\times \pi=11\pi$ 的面积。

我们发现，现在的答案变成了 $82\pi$，距离标准答案又近了一步。

有了刚才的经验，我们决定把半径为 $4$ 的圆也放过去。答案变成了 $90\pi$。

难道这样做是对的？说着，我们把半径为 $2$ 的圆放到了另一边。答案变成了 $92\pi$！我们成功了！

也就是说，对于一棵树，我们把根节点放在一个组，其他的点放在一个组，这样能保证最终的答案最大。

其实也很好证明：

- 假设 A 组当前的最小半径的圆的半径是 $r_A$，另一个组（姑且叫他 B 组）当前最小半径是 $r_B$。
- 假设最大的圆放入了 A 组，第二大的圆放入了 B 组，则 $r_A>r_B$。
- 现在我们放第三大的圆（假设半径是 $r_3$），会发现放两边是一样的，所以我们假设放 B 组。
- 现在我们放第四大的圆。如果放 A 组会造成损失，放 B 组能增加面积，那肯定放 B 组。
- 现在我们放第五大的圆，我们发现如果我们放 A 组，那么本来可以拿来填 B 组空洞的得调过来填 A 组导致 B 组的损失更大，所以放 B 组。
- 以此类推，直到放完最后一个球。

代码：
```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define int long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=1001,inf=0x3f3f3f3f;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
struct circle{
	int x,y,r,val;
}p[N];
int n;
bool cmp(circle x,circle y){return x.r<y.r;}
struct edge{
	int v,nx;
}e[N<<1];
int hd[N],totm,vis[N],dep[N],dep1[N],dep2[N],dep1tot,dep2tot,res0,res1,fa[N];//dep1存的是奇数的点，dep2存的是偶数的点 
bool cmp1(int x,int y){return dep[x]<dep[y];}
void add(int u,int v){e[++totm].v=v;e[totm].nx=hd[u];hd[u]=totm;}
bool able(int x,int y){return bool((p[x].x-p[y].x)*(p[x].x-p[y].x)+(p[x].y-p[y].y)*(p[x].y-p[y].y)<=p[y].r*p[y].r);}//x能不能在y里边 
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	if(dep[u]==1) dep1[++dep1tot]=u;
	else dep2[++dep2tot]=u;
	for(int i=hd[u];i;i=e[i].nx){
		int v=e[i].v;if(v==fa) continue;
		dfs(v,u);
	}
} 
void dfs0(int now,int fa){
	printf("%lld s fa is %lld\n",now,fa);
	for(int i=hd[now];i;i=e[i].nx){
		int v=e[i].v;if(v==fa) continue;
		dfs0(v,now);
	}
}
signed main(){
	n=read();
	fs(i,1,n,1) p[i].x=read(),p[i].y=read(),p[i].r=read(),p[i].val=p[i].r*p[i].r;
	//不难发现，只有r小的才可能被r大的包裹，并且每个点肯定是被能覆盖并且第一个的 
	sort(p+1,p+n+1,cmp); 
//	fs(i,1,n,1) printf("%d %d %d\n",p[i].x,p[i].y,p[i].r);
	fs(i,1,n,1){
		//if(!hd[i]){
			fs(j,i+1,n,1){
				if(able(i,j)){
					fa[i]=j;
					add(i,j);add(j,i);
					break;
				}
			}
		//}
	}
//	dfs0(1,0);
//	fs(i,1,n,1) printf("%d ",fa[i]);
//	puts("");
	fs(i,1,n,1){
		if(!fa[i]){
			ms(dep1,0);ms(dep2,0);dep1tot=dep2tot=0;
			int cur=0;
			dfs(i,0);
			sort(dep1+1,dep1+dep1tot+1,cmp1);
			sort(dep2+1,dep2+dep2tot+1,cmp1);
		//	fs(j,1,dep1tot,1) printf("%d %d\n",dep1[j],dep[dep1[j]]);//puts("");
		//	fs(j,1,dep2tot,1) printf("%d %d\n",dep2[j],dep[dep2[j]]);
			fs(j,1,dep1tot,1){
				if(j&1) res1+=p[dep1[j]].val;
				else res1-=p[dep1[j]].val; 
			}
			fs(j,1,dep2tot,1){
				if(dep[dep2[j]]!=dep[dep2[j-1]]) cur^=1;
				if(cur&1) res0+=p[dep2[j]].val;
				else res0-=p[dep2[j]].val; 
			}
		}
	} 
	printf("%.12lf",acos(-1.0)*db(res0+res1));//,res0,res1);
	return 0;
}
//本质：选还是不选，选的话怎样，不选的话怎样
//我们现在有了一个森林
//考虑DP
//f[i]表示以i为根的最大价值
//f[i][j]表示i放j阵营的最大价值 
//感觉不对啊，我们是不是可以直接对于每棵树进行分类？ 
//也就是说，对于每个点黑白染色
//没有上司的舞会？
//因为f父亲>sigma儿子
//也就是说我们奇数层A一阵营，偶数层A一阵营？
//好，没了 
//好，炸了 
//我们发现这个6是纯纯的出生，搁那碍事了不少，考虑把他调走 
//现在的\sum r2是82，距离92还有10
//把4也挪走？ans变成了90（更大了） 
//最后一步，挪走2？？？？？
//64+28=92
//也就是说，最大的给一个，其他的放一块？？？？？？？？？？？
//考虑样例1，好像对了 
//好，WA On 6
//凹个森林？ 
//哦草，同等深度的不能直接j&1
```

---

## 作者：Yansuan_HCl (赞：0)

容易发现圆的包含关系形成一棵树。则可以想到树形 dp.

答案和每个圆**被选的次数的奇偶性**有关。可以设 $f_u[0/1][0/1][0/1]$ 代表：

- $u$ 节点设为红色还是蓝色；
- $u$ 最下面一层红色节点的**总被选次数**的奇偶性；
- $u$ 最下面一层蓝色节点的**总被选次数**的奇偶性。

若 $u$ 的总被选次数为奇数，答案就会加上 $S_u$；总被选次数为偶数，则需在**它的祖先处**（奇）减去 $S_u$，则答案会加上 $-S_u$。

具体转移、初始条件可参考代码。

```cpp
const int N = 1005;
typedef double ld;
template <typename T>
using BS = basic_string<T>;

struct Circ { ll x, y, r; } crc[N];
ll S[N];
int n;
BS<int> g[N]; int deg[N];
ll f[N][2][2][2];

void dp(int u) {
    f[u][0][1][0] = f[u][1][0][1] = S[u];
    f[u][0][0][0] = f[u][1][0][0] = -S[u];
    if (g[u].empty()) return;
    f[u][0][0][1] = f[u][1][1][0] = -S[u];
    f[u][0][1][1] = f[u][1][1][1] = S[u];

    for (int v : g[u]) {
        dp(v);
        U (i, 0, 1) {
            f[u][0][1][i] += max(f[v][1][0][i], f[v][0][0][i]);
            f[u][0][0][i] += max(f[v][1][1][i], f[v][0][1][i]);
            f[u][1][i][0] += max(f[v][1][i][1], f[v][0][i][1]);
            f[u][1][i][1] += max(f[v][1][i][0], f[v][0][i][0]);
        }
    }
}

int main() {
    rd(n);
    U (i, 1, n) 
        rd(crc[i].x, crc[i].y, crc[i].r);
    
    sort(crc + 1, crc + n + 1, [](const Circ &l, const Circ &r) { return l.r < r.r; });
    U (i, 1, n) S[i] = crc[i].r * crc[i].r; // 提取 pi, 减小常数
    
    U (i, 2, n) U (j, 1, i - 1) 
        if ((crc[i].x - crc[j].x) * (crc[i].x - crc[j].x) + (crc[i].y - crc[j].y) * (crc[i].y - crc[j].y) <= crc[i].r * crc[i].r && !deg[j]) {
            g[i] += j; ++deg[j]; } // 建树，注意一个节点只能被它的直接父亲连边

    ld ans = 0;
    U (i, 1, n) if (!deg[i]) {
        dp(i);
        ans += max(max(f[i][0][1][0], f[i][1][0][1]), max(f[i][0][1][1], f[i][1][1][1])); // 根一定是奇数
    }

    printf("%.8lf", acos(-1) * ans);
}
```

---

