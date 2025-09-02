# [ZJOI2015] 幻想乡 Wi-Fi 搭建计划

## 题目描述

傲娇少女幽香是一个很萌很萌的妹子。随着科技的进步，幻想乡的大家也开始使用手机了。这时幽香发现没人来她的太阳花田玩了，她感到很伤心，于是向别人打听了一下，才知道原来大家都嫌弃这里没有 Wi-Fi，手机上网还需要流量。

怎么办呢？幽香决定赶快搭建几个 Wi-Fi 点，让所有人都能在太阳花田里畅快地上网。

我们可以近似地把太阳花田看成一个 $y$ 轴在 $[0,R]$ 之间，$x$ 坐标在 $(-\infty,+\infty)$（也就是在 $x$ 轴上无限延伸）的无限长方形。

太阳花田里面有 $n$ 个景点，是游客们经常光顾的，幽香认为只要让这些景点尽量被 Wi-Fi 覆盖，那么游客们就肯定心满意足了。

八云紫表示她可以帮幽香架设 Wi-Fi 路由器。现在通用的路由器，每个的覆盖半径正好也是 $R$。八云紫扫视了一遍地图，发现在太阳花田外面，只有 $m$ 个有网络的地点，她只可以在那里架设路由器。如果你在点 $p$ 搭建了路由器，那么位于 $q$ 的地点，只要 $p$ 和 $q$ 的欧几里得距离小于等于 $R$，$q$ 点就会被 Wi-Fi 覆盖。

同时八云紫表示，架设难度随着地点的不同而不同，所以收费也不一样，在第 $i$ 个位置架设需要 $c_i$ 的钱。

现在幽香想要覆盖尽量多的景点，在这个前提下，幽香也想要尽量节省钱。你能帮助她吗？

## 说明/提示

- 对于 $10\%$ 的数据，$n,m\le 20$；
- 对于另 $30\%$ 的数据，$n,m\le 100$，所有网络架设点的 $y$ 坐标都大于 $R$；
- 对于另 $60\%$ 的数据，$n,m\le 100$。

对于全部数据，$1\le R\le 10^8,0\le c\le 10^4$。

## 样例 #1

### 输入

```
10 10 10000
6743 2963
3505 1986
3565 7235
1735 5522
16877 5597
11621 6
3100 8243
1750 6173
5709 7671
7915 3915
14339 -438 3075
4278 15210 8371
13996 19000 6750
17049 -4969 7788
737 16339 2934
904 14023 2322
8982 14759 4311
13102 11458 5554
4135 12183 576
5087 -2459 6787```

### 输出

```
10
10438```

# 题解

## 作者：luogu_gza (赞：8)

非常精妙的一个做法。

简化题意：定义合法区域为 $y \in [0,R]$ 的区域，给定一些在合法区域内的标记点，与一些圆心在合法区域外的，半径为 $R$ 的圆，选择第 $i$ 个圆会产生 $c_i$ 的代价。第一问是最多能覆盖几个标记点；第二问是在保证覆盖标记点最多的情况下，代价的最小值。

首先第一问是非常好做的，明显我们可以选上所有的圆，枚举判断即可，复杂度 $O(nm)$。

第二问一上来就给人一种 NP 问题的感觉啊！但是因为每个圆的半径固定，所以是有做法的。

有一个比较明显的结论：假设所有圆都在合法区域的一侧（代码中将“一侧”钦定为上侧），则将圆按照圆心的 $x$ 从小到大排序，那么假设第 $i$ 个圆无法覆盖某一个点，那么在 $i$ 之后的圆也永远无法覆盖到这个点（一定存在一种代价最小的方案使得这个结论成立）。

这句话其实也点明了去掉无法覆盖点后，排序圆，排序点后，存在匹配关系使得每个圆所覆盖的点都是一段区间。

---

另起思路，定义 $f_{i,j,k}$ 为目前处理到第 $i$ 个点，上一个被匹配的上侧圆为 $j$，上一个被匹配的下侧圆为 $k$ 的最小代价。若 $j=0$ 则表示目前从未匹配过上侧圆，$k=0$ 亦同。

初始化：$f_{0,0,0}=0$。

答案：$\min_{i=0}^{m}\min_{j=0}^{m}f_{n,i,j}$。

转移不难，我们考虑枚举一个可以包含 $i$ 点的圆，然后如果这个圆就是上次被匹配的某侧圆，那么本次转移无代价，否则就加上这个圆的代价。

但是一个圆会有被加代价多次的情况啊！你说得对，但是我们的结论保证永远不会出现这种情况，因为你总会发现一段点匹配一个圆后才会换圆，且永远不会把匹配圆换回来（结论是对称的）。

欢迎 ctj，记得把 `namespace gza` 改掉。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace gza{
	#define int long long
	#define pb push_back
	#define MT int TTT=R;while(TTT--)
	#define pc putchar
	#define R read()
	#define fo(i,a,b) for(int i=a;i<=b;i++)
	#define rep(i,a,b) for(int i=a;i>=b;i--)
	#define m1(a,b) memset(a,b,sizeof a)
	namespace IO
	{
		inline int read()
		{
		    int x=0;
		    char ch=getchar();
		    bool f=0;
		    while(!isdigit(ch)){if(ch=='-') f=1;ch=getchar();}
		    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
		    if(f) x=-x;
		    return x;    
		}
		template<typename T> inline void write(T x)
		{
		    if(x<0) pc('-'),x=-x;
		    if(x>9) write(x/10);
		    pc(x%10+'0');
		}
	};
	using namespace IO;
	
	#define x first
	#define y second
	const int N=110;
	int n,m,r;
	pair<int,int> a[N];
	bool vis[N];
	struct Node{
		int x,y,c,typ;
		bool operator< (const Node& A)const
		{
			return pair<int,int>({x,y})<pair<int,int>({A.x,A.y});
		}
	}b[N];
	bool check(int i,int j)
	{
		if(j==0) return 1;
		int dx=a[i].x-b[j].x,dy=a[i].y-b[j].y;
		return dx*dx+dy*dy<=r*r;
	}
	int f[N][N][N];
	void main(){
		n=R,m=R,r=R;
		fo(i,1,n) a[i].x=R,a[i].y=R;
		fo(i,1,m) b[i].x=R,b[i].y=R,b[i].c=R;
		fo(i,1,m)
			if(b[i].y>r) b[i].typ=1;
			else b[i].typ=2;
		fo(i,1,n)
		{
			bool flag=0;
			fo(j,1,m) if(check(i,j)) flag=1;
			if(!flag) vis[i]=1;
		}
		int now=0;
		fo(i,1,n) if(!vis[i]) now++,a[now]=a[i];
		sort(a+1,a+now+1);
		write(n=now),puts("");
		m1(f,0x3f),f[0][0][0]=0;
		fo(i,1,n) fo(j,0,m) fo(k,0,m) fo(l,1,m) if(check(i,l))
		{
			if(b[l].typ==1) f[i][l][k]=min(f[i][l][k],f[i-1][j][k]+((j!=l)?b[l].c:0));
			else f[i][j][l]=min(f[i][j][l],f[i-1][j][k]+((k!=l)?b[l].c:0));
		}
		int ans=2e9;
		fo(i,0,m) fo(j,0,m) ans=min(ans,f[n][i][j]);
		write(ans);
	}
}
signed main(){
	gza::main();
}
```

---

## 作者：Fan_sheng (赞：1)

本题解参考 [Lstdo 的 CSDN 博客](https://blog.csdn.net/luositing/article/details/104071263)，有关结论的证明也可以看那里。

---

长得一脸网络流的样子，但是没法建模，因为费用流要求费用与流量相关。考虑其他做法。

首先给出一个神必结论：我们去掉所有没法覆盖到的点，并按 $x$ 从小到大排序。假设所有圆圆心都在 $y=R$ 上方，我们让每个点匹配一个**包含它**的圆，一定存在一种匹配方式（且代价最小），使得每个圆所匹配的点都是一段区间。

这个结论在圆心不保证都在上方或下方时不成立，但是这不重要。

于是列出一个 dp：$dp[i][j][k]$ 表示处理到第 $i$ 个点（已排序），最后一个匹配上方圆的点匹配了圆 $j$，最后一个匹配下方圆的点匹配了圆 $k$，最小代价。

转移就是枚举一个可以匹配 $i$ 的圆，如果它是上方圆且它是 $j$，此次匹配就没有代价；如果它是上方圆且它不是 $j$，相当于新建了一个圆，新增这个圆的代价。

你已经发现了，这样可能重复计算代价，一个圆可能新建了若干次。但是此时我们之前的结论发挥作用：一定存在一种最优解，使得每个圆最多新建一次。同时，重复计算代价的方案显然是不优的。这两点保证了 dp 可以找到最优解。

复杂度 $\mathcal O(n^4)$。

Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,dp[103][103][103],C[103],ans=0x3f3f3f3f;
ll R;
pair<ll,ll>p[103],circ[103];
inline bool check(int i,int j){
	if(!j)return 1;
	ll x=p[i].first-circ[j].first,y=p[i].second-circ[j].second;
	return R*R>=x*x+y*y;
}
inline void init(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)if(check(i,j))goto suc;
		p[i].first=0x3f3f3f3f;
		suc:;
	}sort(p+1,p+n+1);
	while(p[n].first>1e9)n--;
	printf("%d\n",n);
}
int main(){
	scanf("%d%d%lld",&n,&m,&R);
	for(int i=1;i<=n;i++)
	scanf("%lld%lld",&p[i].first,&p[i].second);
	for(int i=1;i<=m;i++)
	scanf("%lld%lld%d",&circ[i].first,&circ[i].second,&C[i]);
	init();
	memset(dp,0x3f,sizeof(dp)),dp[0][0][0]=0;
	for(int i=1;i<=n;i++)
	for(int j=0;j<=m;j++)
	for(int k=0;k<=m;k++)
	for(int t=1;t<=m;t++)if(check(i,t)){
		if(circ[t].second>R)
		dp[i][t][k]=min(dp[i][t][k],dp[i-1][j][k]+(j!=t)*C[t]);
		else dp[i][j][t]=min(dp[i][j][t],dp[i-1][j][k]+(k!=t)*C[t]);
	}
	for(int j=0;j<=m;j++)
	for(int k=0;k<=m;k++)ans=min(ans,dp[n][j][k]);
	printf("%d",ans);return 0;
}
```


---

