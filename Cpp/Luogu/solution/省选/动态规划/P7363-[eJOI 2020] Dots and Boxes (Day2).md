# [eJOI 2020] Dots and Boxes (Day2)

## 题目背景

小 T 和小 A 在玩一种点格游戏。

## 题目描述

首先，小 T 拿出了一张拥有 $(N+1) \times (M+1)$ 个格点的方格纸（这些格子从上到下，从左到右可以编号为第 $1 \sim N+1$ 行第 $1 \sim M+1$ 列的格点），每个格点向上下左右的那个格点（如果那个方向有格点的话）连边，不难发现，会形成一个 $N \times M$ 的方格矩阵。但是小 T 拿出的是没有连边的格点方格纸，小 T 和小 A 的目标就是在格点之间连线。

游戏规则是这样的，每一轮玩家可以在两个格点之间连线，如果连完线能连好一个格子，那么这个格子就属于这个玩家了。然后玩家可以继续连线，直到连完线不能获得格子为止，就换到下一个玩家。当所有玩家都不能连线时，游戏结束。

比如下面这张图即为当 $N=2,M=3$ 时两位玩家可能的连线结果：

![](https://cdn.luogu.com.cn/upload/image_hosting/sngf2kqv.png)

其中虚线为这一轮玩家连的线。

小 A 和小 T 已经玩了许久了，你发现他们现在的方格纸满足每一个格子周围的四条边都有 **$0$ 条或 $2$ 条未被连线**，比如下面这张图就满足要求，上面这张图除了第一幅图也都满足要求：

![](https://cdn.luogu.com.cn/upload/image_hosting/gzoveutp.png)

并且刚好轮到小 A 了。

定义小 A 和小 T 的分数 $S_A,S_T$ 为玩家从现在开始得到的分数，那么整个游戏的分数即为 $S_A-S_T$，小 A 要让整个游戏的分数变得越大越好，小 T 则反之，他们都会按照他们的目标做最优策略。

你要求出他们做最优策略下得到的分数。

## 说明/提示

#### 样例 1 解释

下图为其中一种连线方式，红色为小 A 的操作，蓝色为小 T 的操作：

![](https://cdn.luogu.com.cn/upload/image_hosting/cu0mah7j.png)

#### 样例 2 解释

这个样例为题目描述中的第二个图片。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（20 pts）：给出的输入只包含一个连通块。
- Subtask 2（20 pts）：$N \times M \le 12$。
- Subtask 3（20 pts）：给出的输入只包含两个连通块。
- Subtask 4（20 pts）：$N,M \le 7$。
- Subtask 5（20 pts）：无特殊限制。

对于 $100\%$ 的数据，$3 \le N, M \le 20$，**每一个格子周围的四条边都有 $0$ 条或 $2$ 条未被连线**。

其中一个连通块定义为已连上的边与方格纸的边缘围起来的块，比如说下面这个图有 $5$ 个连通块：

![](https://cdn.luogu.com.cn/upload/image_hosting/6g0pk8w2.png)

注意已被玩家占有的方格不属于任意一个连通块。

#### 说明

翻译自 [eJOI 2020 Day2 C Dots and Boxes](https://ejoi2020.ge/static/assets/Day2/Problems/Game.pdf)。

## 样例 #1

### 输入

```
3 3
000
111
011
110
1010
1000
1001```

### 输出

```
-5```

## 样例 #2

### 输入

```
5 5
00100
10100
11010
00100
01000
11100
011111
001011
101011
110111
100111```

### 输出

```
6```

# 题解

## 作者：Danno0v0 (赞：11)

~~是一道棋牌类问题但不是大%拟的问题，太棒了~~

题目中有一句非常重要的话：

>满足每一个格子周围的四条边都有 0 条或 2 条未被连

这说明了什么呢，当然是说明了所有联通起来的（不被黑线隔开的）方块要么组成一条链，要么链首尾拼接组成一个环，不可能是树或者奇奇怪怪的东西。这个性质手推就很容易得到了。

那么我们的预处理就是把每一条链和每一个环的大小预处理出来。接下来为了方便做（原因后讲），我们把不同种类的图丢到两个数组里面。

接下来就是讨论最优策略了。

这里拿链来举例：

假设这里有一条没有被操作过的链：（图上的红边表示原有的边）

![](https://cdn.luogu.com.cn/upload/image_hosting/00lkeyhb.png)

现在轮到先手（蓝色的边）来操作，很明显是一个格子都占不了的，所以只能随意地画一条边：

![](https://cdn.luogu.com.cn/upload/image_hosting/st189aq6.png)

现在轮到后手（绿色的边）了。他就可以高高兴兴地靠着先手的边占掉这条链上所有格子。

![](https://cdn.luogu.com.cn/upload/image_hosting/43g03fvq.png)

然后这条链就算处理完了。接下来到下一条链时，由于后手的 combo 奖励，他这个时候是先对这条链进行操作的，所以——

他现在变成了先手，而之前的先手变成了现在的后手。而依据上面的推导，后手将会占完所有的格子，然后这里的后手就变成了先手，所以，两个人就交替地占着格子。然后注意到后手能得到多少收益取决于先手决定操作哪条链，而先手肯定会选大小最小的链让后手收益最小，所以，答案就是把所有连通块按从小到大排序然后两人交替取就是——

了吗？

我们来看这样一种情况，先手决定操作大小为 $3$ 的链，现在轮到后手了：

![](https://cdn.luogu.com.cn/upload/image_hosting/6sqvhjjy.png)

按照上面的推论，后手现在只能收掉大小为 $3$ 的链而把旁边大小为 $6$ 的链送给先手，所以后手特别不满意，于是他决定操作一下。

问题是操作在哪里呢？操作在大小为 $6$ 的链上是肯定不行的，（相当于下一步操作先手就可以把两条链都占了，抢占 $6$ 没占成，倒把 $3$ 给丢了）于是只能操作在 $3$ 上了（边上的数字表示画边的顺序）：

![](https://cdn.luogu.com.cn/upload/image_hosting/umecn7t3.png)

在画下第二条边的时候后手因为没有占格子所以停止了画边。现在轮到先手了。

1. 先手操作在 $3$ 上—，这个时候先手只好把后手留给他的两个格子占掉，然后面对 $6$ 的链当先手。

2. 先手直接操作在 $6$ 上，等于直接面对 $6$ 的链当先手。

所以此时无论先手怎么搞，都会在面对 $6$ 的时候当先手，这样，后手就能愉快地在 $6$ 的时候当后手啦。

对后手的这种战术做一个总结：也就是放弃两个属于自己的格子（在链上时）给先手，让面对下一条更大的链的时候先手依然是当先手。

（注$^1$：在环上时需要放弃四个格子，就像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/upvqv928.png)

可以证明没有方法在画下 $last$ 的时候只放弃三个或更小的格子，手推即可。 

注$^2$：如果一个链的大小等于 $2$ ，先手可以把线画在链的中心位置让后手不能放弃格子；如果大小等于 $1$ ，请问后手怎么执行放弃两个格子的战术。也就是只有链的大小大于 $2$ ，后手才可以放弃格子换取后手。

）

所以综上，对于每一个连通块：

先手只能操作一条线。

后手可以选择：

- 获取这个连通块内所有格子，然后把后手转让给先手。

- 获取这个连通块内格子数量 $-2$  （链） $-4$ （环） ，剩下的给先手。

这个直接 DP 就可以了。

哦对了，由于对于环和链，后手的第二种策略放弃格子数量是不同的，所以我们分开转移（所以要分开存）。然后因为不管后手怎么操作，后手能获得的格子数还是取决于先手选择的连通块，所以不管先手决定操作哪种连通块，一定都是选最小的。

code：（还是说一下 DP ：$dp_{i,j}$ 表示现在选到了第 $i$ 大的链和第 $j$ 大环时的并且两人采用最优策略的分数，并且现在轮到先手，然后倒推，一些细节放代码里了）

```cpp
#include<bits/stdc++.h>
#define up 1
#define right 2
#define down 4
#define left 8
using namespace std;
int n,m,a[101][101],size_chain[1000001],size_loop[1000001],fi[1000001],nx[1000001],to[1000001],val[1000001],totm,fa[1000001],dp[101][101],num1,num2,cnt,A,T,tot;
bool vis[1000001],check;
bool cmp(int a,int b){
	return a>b;
}
void link(int a,int b){
	nx[++tot]=fi[a];
	fi[a]=tot;
	to[tot]=b;
} 
void dfs(int now,int fath){//丑陋找连通块 
	vis[now]=1;
	cnt++;
	for(int i=fi[now];i;i=nx[i]){
		int v=to[i];
		if(v==fath) continue;
		if(vis[v]) {
			check=1;
			continue;
		}
		dfs(v,now);
	}
}
int main()
{
	char s;
	cin>>n>>m;
	for(int i=0;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>s;
			a[i][j]+=((s-'0')*down);
			a[i+1][j]+=((s-'0')*up);
		} 
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++){
			cin>>s;
			a[i][j]+=((s-'0')*right);
			a[i][j+1]+=((s-'0')*left);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(!(a[i][j]&1)&&i-1>0) link(i*100+j,(i-1)*100+j);
			if(!(a[i][j]&2)&&j+1<=m) link(i*100+j,i*100+(j+1));
			if(!(a[i][j]&4)&&i+1<=n) link(i*100+j,(i+1)*100+j);
			if(!(a[i][j]&8)&&j-1>0) link(i*100+j,i*100+(j-1));
			if(a[i][j]==15) vis[i*100+j]=1;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(!vis[i*100+j]){
				cnt=0,check=0;
				dfs(i*100+j,0);
				if(!check) size_chain[++num1]=cnt;
				else size_loop[++num2]=cnt;
			}
		}
	}
	sort(size_chain+1,size_chain+num1+1,cmp);
	sort(size_loop+1,size_loop+num2+1,cmp);
	for(int i=0;i<=num1;i++){
		for(int j=0;j<=num2;j++){
			dp[i][j]=-0x7ffffff;
			if((!i)&&(!j)){
				dp[i][j]=0;
				continue;
			}
			if(i){
				if(size_chain[i]>=3) dp[i][j]=-max(size_chain[i]+dp[i-1][j],size_chain[i]-4-dp[i-1][j]);
				else dp[i][j]=-size_chain[i]-dp[i-1][j];
				/* 
				第一个问题：为什么是max前是-和转移方程的含义
				这是从经过上一次后手操作后的分数转移的，而后手的收益相当于先手的负收益所以要加-
				第一个转移的含义就是：把没有选这条链时的分数加上选了这条链的收益就是后手收益
				第二个转移的含义就是：这条链的大小减去放弃格子失去的收益再减去没有选这条链时的分数
				——为什么是减去没选时的分数？因为数组里存的是对于先手来说的收益，而进行放弃操作时，在下一个（别忘了我们是倒推）联通块时后手仍然是后手不会进行先后交换，所以下一个连通块时的操作时，需要从下一个连通块时后手分数进行转移，而后手分数就是先手分数的相反数 
				第二个问题：为什么都是-了，用max，不应该用min保证这个人收益最大吗？ 
				后手用的是最优策略啊喂，假如用min，就相当于让后手用最劣策略来保证先手的最优策略啊。 
				第三个问题：对于第二个转移，为什么-4而不是-2？
				你转出两个格子给另一个人，那么你不仅损失了应得的两个格子，还让对手得到了本不应得的两个格子；加起来就是4个。 
				*/ 
			}
			if(j){
				dp[i][j]=max(dp[i][j],-max(size_loop[j]+dp[i][j-1],size_loop[j]-8-dp[i][j-1]));
			}
			/*
			环的转移同理。 
			*/ 
		}
	}
	cout<<dp[num1][num2];
}
```



---

## 作者：Kubic (赞：6)

eJOI 官方题解写的都是什么东西，看都看不懂/px

经过几小时的思考终于肝出来了/kk

补一篇题解来造福一下后人吧qwq。

首先先去感性理解一下这个游戏的过程。

题目限制每个格子边上只能有 $0$ 或 $2$ 个已经选择的边。先考虑令 $w_{i,j}$ 表示 $(i,j)$ 这个格子四周有几条未选的边。显然 $w_{i,j}=0$ 的格子没有任何用。

考虑剩下的 $w_{i,j}=2$ 的格子。

现在去选一条边，则会将 $1$ 个或 $2$ 个 $w_{i,j}$ 变为 $1$。这时候轮到另外一个人了，他可以将这个连通块里的格子选走任意多个之后再选一条边。

这里连通块指不穿过已选的边，按照四联通规则所能走到的所有格子组成的集合。

上面只是感性部分，可以结合样例手玩一下，应该比较容易理解。

如果这个图里只有一个连通块，那么先手选第一条边之后直接就把这个连通块白给了，游戏结束。

连通块只有两种：链和环。先考虑只有链的情况。

如果有两个连通块，假设大小为 $x,y$，不妨 $x\le y$。两个人所要争取的一定是 $y$ 而不是 $x$。所以先手不能直接把 $y$ 白给了，而是一定先白给 $x$。此时就有两种情况了。

- 如果 $x\ge 3$，那么后手可以先连续获取 $x-2$ 个方格并在 $x$ 中选择一条边使得它不与其它边形成方格。这样做会把 $2$ 个格子送给先手但是逼迫先手把 $y$ 白给了。容易证明这一定能做到。

- 如果 $x<3$，那么后手只能获取 $x$ 中所有格子并白给 $y$。

环中的第一种操作与链有差异，它需要 $x\ge 4$，并且要送 $4$ 个格子给对手。

有了这样的基础，我们考虑扩展到多个连通块的情况。

将环和链分开，并分别从小到大排序。每次如果被迫白给一定只会白给链中最小的一个或者环中最小的一个。令 $dp_{i,j}$，表示当前链还剩下 $i$ 及 $i$ 之后，环还剩下 $j$ 及 $j$ 之后的答案。

根据上面的推理，具体转移已经比较容易推出了，如果不懂可以看代码，应该还是比较清晰的。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 25
#define M 405
const int INF=1e9;
int n,m,cnt,st[2][M],dp[M][M];
bool fl,vs[N][N];char a1[N][N],a2[N][N];
void W(int &x,int y) {x=max(x,y);}
void dfs(int x,int y)
{
	if(!x || !y || x>n || y>m) {fl=0;return;}
	if(vs[x][y]) return;bool fl1=0;vs[x][y]=1;
	if(a1[x][y]=='0') fl1=1,dfs(x-1,y);
	if(a1[x+1][y]=='0') fl1=1,dfs(x+1,y);
	if(a2[x][y]=='0') fl1=1,dfs(x,y-1);
	if(a2[x][y+1]=='0') fl1=1,dfs(x,y+1);cnt+=fl1;
}
int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n+1;++i) scanf("%s",a1[i]+1);
	for(int i=1;i<=n;++i) scanf("%s",a2[i]+1);
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j)
	{cnt=0;fl=1;dfs(i,j);if(cnt) st[fl][++st[fl][0]]=cnt;}
	sort(st[0]+1,st[0]+st[0][0]+1);
	sort(st[1]+1,st[1]+st[1][0]+1);
	for(int i=st[0][0]+1,t;i;--i) for(int j=st[1][0]+1;j;--j)
	{
		if(i>st[0][0] && j>st[1][0]) continue;dp[i][j]=-INF;
		if(i<=st[0][0])
		{
			t=-INF;W(t,st[0][i]+dp[i+1][j]);
			if(st[0][i]>2) W(t,st[0][i]-4-dp[i+1][j]);
			W(dp[i][j],-t);
		}
		if(j<=st[1][0])
		{
			t=-INF;W(t,st[1][j]+dp[i][j+1]);
			if(st[1][j]>3) W(t,st[1][j]-8-dp[i][j+1]);
			W(dp[i][j],-t);
		}
	}printf("%d\n",dp[1][1]);return 0;
}
```

---

## 作者：__usingnamespace__ (赞：1)

题意不清楚的可以试着下两把，很快就能搞懂意思了。

先手先开一个连通块，为了损失最小显然从小的开始。后手显然要把先手开的这个连通块处理掉，否则净亏。

把所有连通块分为环和链。搜索记录其长度。显然 1- 链是强制交换先后顺序，对于 2- 链，情况如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/el9m7zwx.png)

显然先手不会这样填

![](https://cdn.luogu.com.cn/upload/image_hosting/33qy7wzu.png)

因为这样相当于把选择权交给后手，所以先手必然选择这样填

![](https://cdn.luogu.com.cn/upload/image_hosting/ig7865r6.png)

因此 2- 链与 1- 链是一样的意义。

对于 n- 链($n\geq 3$)：

![](https://cdn.luogu.com.cn/upload/image_hosting/52zg95de.png)

后手都有两种选择：全部吃完，然后交换先后手权

![](https://cdn.luogu.com.cn/upload/image_hosting/fggpfbyz.png)

留两个，保留先后手权

![](https://cdn.luogu.com.cn/upload/image_hosting/qyulae27.png)

对于环上的情况类似，只不过后手要保留先后手权的代价是 4 个

![](https://cdn.luogu.com.cn/upload/image_hosting/ieqhrkcj.png)

那么就显然可以 DP 求当前的后手如何选择答案最优。

首先处理 1- 链和 2- 链，剩下的设 $dp_{i,j}$ 表示还剩 $i$ 个链 $j$ 个环，那么对于上一个填完的是链的情况，有

$dp_{i,j}=\max (dp_{i,j},\min (dp_{i+1,j}+4,-dp_{i+1,j})-sizel_i)$

对于上一个填完的是环的情况，有

$dp_{i,j}=\max (dp_{i,j},\min (dp_{i,j+1}+8,-dp_{i,j+1})-sizec_j)$

（ $sizel,sizec$ 分别表示环和链大小）

表示从上一状态选择保留先后手还是选择交换先后手。

最后的答案就是前面的 1- 链， 2- 链的结果+目前先手/后手对应 $dp_{1,1}$/$-dp_{1,1}$ 。

**Code**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=30,inf=1000000000;
char s[maxn];
int ditu[maxn][maxn],gpc,nows;
int flag;
bool ban[maxn][maxn][4],vis[maxn][maxn];//上下左右 
const int xx[4]={-1,1,0,0},yy[4]={0,0,-1,1};
int cir[400],lin[400],cirlen,linlen;
int n,m;
int dp[maxn<<1][410];
inline void dfs(int x,int y,int cl,int la)
{
    ditu[x][y]=cl;nows++;
    for(int i=0;i<=3;i++)
    {
        if(i==la)continue;
        if(ban[x][y][i])continue;
        int tox=x+xx[i],toy=y+yy[i];
        if(tox==0||toy==0||tox>n||toy>m){flag=1;continue;}
        if(ditu[tox][toy]==cl)
        {
            flag=-1;
            return;
        }
        dfs(tox,toy,cl,i^1);
    }
    return;
}
inline void check()
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)printf("%2d ",ditu[i][j]);
        cout<<endl;
    }
    for(int i=1;i<=cirlen;i++)cout<<cir[i]<<' ';cout<<endl;
    for(int i=1;i<=linlen;i++)cout<<lin[i]<<' ';cout<<endl;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n+1;i++)
    {
        scanf("%s",s+1);
        for(int j=1;j<=m;j++)
        {
            if(s[j]=='1')
            {
                ban[i-1][j][1]=1;
                ban[i][j][0]=1;
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s+1);
        for(int j=1;j<=m+1;j++)
        {
            if(s[j]=='1')
            {
                ban[i][j-1][3]=1;
                ban[i][j][2]=1;
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(!ditu[i][j])
            {
                if(ban[i][j][0]&ban[i][j][1]&ban[i][j][2]&ban[i][j][3])continue;
                gpc++;flag=0;nows=0;dfs(i,j,gpc,4);if(flag==1)lin[++linlen]=nows;if(flag==-1)cir[++cirlen]=nows;
            }
        }
    }
    int nowf=-1,ans=0,zyw;
    sort(lin+1,lin+linlen+1);
    sort(cir+1,cir+cirlen+1);
    for(zyw=1;zyw<=linlen&&lin[zyw]<=2;zyw++)
    {
        ans+=nowf*lin[zyw];nowf=-nowf;
    }
    for(int i=linlen+1;i>=zyw;i--)
    {
        for(int j=cirlen+1;j;j--)
        {
            if(i>linlen&&j>cirlen)continue;
            dp[i][j]=-inf;
            if(i<=linlen)dp[i][j]=max(dp[i][j],min(dp[i+1][j]+4,-dp[i+1][j])-lin[i]);
            if(j<=cirlen)dp[i][j]=max(dp[i][j],min(dp[i][j+1]+8,-dp[i][j+1])-cir[j]);
        }
    }
    nowf=-nowf;
    printf("%d\n",ans+nowf*dp[zyw][1]);
//    check();
    return 0;
}
```

---

## 作者：dengyaotriangle (赞：1)

考虑这个局面的结构，发现由于每个点的度数为 $0$ 或 $2$，所以可以继续操作的连通块一定构成一些环或者链。

考虑这个游戏的过程，第一步一定是先手在某一个连通块中加一条边，此时后手可以

- 以这条边为中心，不断加边直到占完这个连通块。然后最后选择一个其它的连通块的某条边，也就是转变为了少了一个连通块，自己先手的原问题的情况。

- 以这条边为中心，不断加边，但是在占的格子尽可能多的情况下不占满，逼迫先手继续回到先手的位置。而在后手回合结束后，先手没有任何选择，只能在把那些留下来的格子吃掉之后，自己再新开辟一个连通块。

第一种很好理解，就是尽可能多占当前的格子，而第二种呢？

首先，做第一种操作，注意到做完之后自己转变为了（一个相同子问题的）先手，而先手进行一次操作是得不到格子的，反而是后手拿到了，说明有时是需要避免自己成为先手的。这种时候需要在达到目的的情况下，尽可能占更多格子，也就是第二种策略的目标。

而具体方法，如图，红色为先手选的，后手按照顺序加蓝色的边，注意最后加的那条不会形成新格子，于是在此之后，后手的回合就结束了。

![](https://cdn.luogu.com.cn/upload/image_hosting/zagf424o.png)

而且这种方法是最优的，也就是对于一个环最少剩 $4$ 个格子，一个链最少剩 $2$ 个。

注意到剩下的部分先手继续操作的话一定会形成新格子，所以先手不能在不开辟新连通块的情况下结束自己的回合，只能在下一个连通块还是先手。

注意有一个特殊情况，对于一个长度 $\leq2$ 的链，若先手选择在中间的边，那么后手无法进行第二种策略。这种情况下，先手显然需要避免后手进行第二种策略，因为这样后手的选择严格变少了，不管对于后手哪种策略更优，对先手来说都是阻止掉好。

![](https://cdn.luogu.com.cn/upload/image_hosting/uuljobfw.png)

那么已经得到了一个关于连通块数指数级的算法，就是状压哪些集合被选了，然后先手枚举选哪个连通块，再枚举后手的策略，转移即可。

接下来，观察到，对于两个同种连通块（环/链），先手一定会选择其中更小的那个。

因为这样可以让后手得到的格子尽可能少，且（对于 $\leq 2$ 的链来说）有可能还可以限制后手的选择，所以一举两得，感性理解上显然是更优的。

（至于不同种类的连通块之间，注意到后手的选择一个最少剩 $4$ 个，一个最少剩 $2$ 个，之间的优劣关系不好只由大小判定，所以是分开的）

于是这两种连通块剩下的一定分别是一个后缀，所以可以设计 dp 状态 $dp_{i,j}$ 代表对于最大的 $i$ 个链，最大的 $j$ 个环构成的子局面，先手最大收益。转移即枚举下一波选环还是链即可。

复杂度 $\mathcal{O}(nm(n+m))$，（注意到链的块一定有两个位置与网格边缘相邻，所以不超过 $n+m$ 个，环则是最多 $nm/4$ 个）

```cpp
#include<bits/stdc++.h>
using namespace std;
//dengyaotriangle!

const int maxn=25;
const int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
const int maxm=405;

int n,m;
char _[maxn];
bool a[maxn][maxn][4];
bool vis[maxn][maxn];

int c[maxm],r[maxm],cs,rs;
int dp[maxm][maxm];//c: chain / r: ring

bool ic;
int sz;
void dfs(int x,int y){
    sz++;
    vis[x][y]=1;
    for(int i=0;i<4;i++)if(a[x][y][i]){
        int cx=x+dx[i],cy=y+dy[i];
        if(cx>=1&&cx<=n&&cy>=1&&cy<=m){
            if(!vis[cx][cy])dfs(cx,cy);
        }else ic=1;
    }
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n+1;i++){
        cin>>_;
        for(int j=1;j<=m;j++)if(_[j-1]=='0'){
            a[i-1][j][2]=1;
            a[i][j][3]=1;
        }
    }
    for(int i=1;i<=n;i++){
        cin>>_;
        for(int j=1;j<=m+1;j++)if(_[j-1]=='0'){
            a[i][j-1][0]=1;
            a[i][j][1]=1;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!vis[i][j]){
                ic=0;sz=0;
                dfs(i,j);
                if(ic)c[++cs]=sz;
                else if(sz>1)r[++rs]=sz;
            }
        }
    }
    sort(c+1,c+1+cs,greater<int>());sort(r+1,r+1+rs,greater<int>());
    for(int i=0;i<=cs;i++){
        for(int j=0;j<=rs;j++){
            if(i==0&&j==0){dp[i][j]=0;continue;}
            dp[i][j]=INT_MIN;
            if(i){
                int nw=c[i]+dp[i-1][j];//type1
                if(c[i]>=3){
                    nw=max(nw,c[i]-2-(2+dp[i-1][j]));//type2
                }
                dp[i][j]=max(dp[i][j],-nw);
            }
            if(j){
                int nw=max(r[j]+dp[i][j-1]/*type1*/,r[j]-4-(4+dp[i][j-1])/*type2*/);
                dp[i][j]=max(dp[i][j],-nw);
            }
        }
    }
    cout<<dp[cs][rs];
    return 0;
}
```

---

## 作者：_Cheems (赞：0)

很好的博弈题，出现在模拟赛中将我薄纱。

题意首先别看错了，两人轮流操作，假如一个人将一个格子四面都围起来了，称之为占领，那么就能继续操作。

然后我猜了个结论，假如能占领一个连通块的一个格子，那么就继续把这个连通分量给占满，因为剩下的不要白不要。

乍一看没问题，但是假如现在有个大小两个连通块，若一方直接把小连通块填满，那么就不得不去画大连通块，然后另一方就能把大连通块占领了，该贪心存在后效性。

基于这个例子，可以知道：先填连通块的不优，称之为先手，因为后手就能直接占领这个连通块；但是后手不一定要填满，因为之后就变成了其它连通块的先手，所以可以留下一些格子，不改变先后手。

由题意，连通块只能是链或简单环，先手先划一笔，后手有两种选择，对于链：

1. 直接占领这个链，但是交换先后手。

2. 让出一些格子给先手，不交换先后手。最少肯定是让 $2$ 个，而让多了没有意义，相当于白给先手一些格子、还可能被反制而被迫交换先后手。

对于环同理，只不过要让 $4$ 个格子。

那么现在有很多链（或环），先手应该选哪个？应该选最小的，因为不管咋选都会让给后手这个连通块，那么肯定先让出小的。

不过对于长度为 $1$ 或 $2$ 的链，情况不一样，因为先手占据了主动权，可以强行交换先后手（中间划一笔即可）。先手肯定想改变逆风局势成为更大连通块的后手，故一定先操作这些链（假如对链操作的话），而且肯定先选长度为 $1$ 的，尽量少让出格子。

现在流程清晰了：先手选当前最小的链或环，后手选交不交换先后手顺序，以此类推；假如场上存在长为 $1$ 或 $2$ 的链，先手选链时优先选它们中较小者并交换先后手。

所以记 $f_{i,j}$ 表示场上剩下前 $i$ 大的链、前 $j$ 大的环时，先手得分减去后手得分的最大值。注意到链的数量为 $O(n+m)$ 级别（两端必然在边界上），所以复杂度 $O(nm(n+m))$。
#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define id(x, y) ((x - 1) *  m + y)
#define MAX(a, b) a = max(a, b)
const int H = 25, NL = 45, NC = 405, inf = 1e7;
int n, m, cnt[H][H], sb;
char s[H];
vector<int> to[H * H];
bool vis[H * H], cir;
int siz, nl, l[NL], nc, c[NC], f[NL][NC];

inline bool chk(int x, int y) {return 1 <= x && x <= n && 1 <= y && y <= m;}
inline void add(int x, int y, int _x, int _y){
	if(!chk(x, y) || !chk(_x, _y)) return ;
	to[id(x, y)].push_back(id(_x, _y)), to[id(_x, _y)].push_back(id(x, y));
}
inline void dfs(int u, int from, bool &cir, int &siz){
	vis[u] = true, ++siz; 
	for(auto v : to[u])
		if(v ^ from){
			if(!vis[v]) dfs(v, u, cir, siz);
			else cir |= true;
		}
}
inline bool cmp(int a, int b) {return a > b;}
signed main(){
	cin >> n >> m;
	for(int i = 1; i <= n + 1; ++i){
		scanf("%s", s + 1);
		for(int j = 1; j <= m; ++j)
			if(s[j] == '0') add(i - 1, j, i, j);
			else ++cnt[i][j], ++cnt[i - 1][j];
	}
	for(int i = 1; i <= n; ++i){
		scanf("%s", s + 1);
		for(int j = 1; j <= m + 1; ++j) 
			if(s[j] == '0') add(i, j - 1, i, j);
			else ++cnt[i][j], ++cnt[i][j - 1];
	}

	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			if(!vis[id(i, j)] && cnt[i][j] < 4){
				dfs(id(i, j), 0, cir = 0, siz = 0); 
				if(!cir) l[++nl] = siz;
				else c[++nc] = siz;
			}
			
	sort(l + 1, l + 1 + nl, cmp), sort(c + 1, c + 1 + nc, cmp);
	f[0][0] = 0;
	for(int i = 0; i <= nl; ++i)
		for(int j = (!i ? 1 : 0); j <= nc; ++j){
			f[i][j] = -inf;
			if(i){
				if(l[i] <= 2) MAX(f[i][j], -l[i] - f[i - 1][j]);
				else MAX(f[i][j], min(-l[i] - f[i - 1][j], -l[i] + 4 + f[i - 1][j]));
			}
			if(j) MAX(f[i][j], min(-c[j] - f[i][j - 1], -c[j] + 8 + f[i][j - 1]));
		}
	cout << f[nl][nc];
	return 0;
}
```

---

