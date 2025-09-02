# Conveyor

## 题目描述

有一个 $120$ 行，$120$ 列的棋盘，行列编号均为 $0,1,\cdots,119$，$i$ 行 $j$ 列的格子的坐标为 $(i,j)$，左上角的格子坐标为 $(0,0)$。每一个格子上都有一个传送带，初始方向为右。

一开始，有一个史莱姆在 $(0,0)$，其他格子都什么也没有，每一秒传送带的方向都会如下变化：

- 所有的史莱姆随着传送带的方向移动一格。如果传送带的方向没有格子，史莱姆就会离开棋盘；如果两个史莱姆到了同一个格子上，就会合并为一个史莱姆。
- 所有**上一秒**有史莱姆的传送带的方向都会改变，向右的会变成向下的，向下的会变成向右的。
- $(0,0)$ 处会出现一个史莱姆。

给定 $q$ 个询问，问在第 $t$ 秒，$(x,y)$ 格是否有史莱姆。

## 说明/提示

$ t = 0 $ 时的棋盘如图。红色箭头表示每个传送带的方向，蓝色图案表示史莱姆。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1733E/9a5ad38e6ba3be11b681addc62e40c385d86286e.png)

$ t = 1 $ 时的棋盘如图。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1733E/615f3226ab73df7a7b42b7235acfce44b1cc8ee4.png)

$ t = 2 $ 时的棋盘如图。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1733E/adf4a0692493dda978e85c03fc1c2ec678092cc0.png)

## 样例 #1

### 输入

```
6
1 1 0
5 1 3
0 0 0
2 4 5
2 0 2
1547748756 100 111```

### 输出

```
NO
YES
YES
NO
YES
YES```

# 题解

## 作者：Silviasylvia (赞：11)

写篇题解记录一下 cf 场上几乎秒了 `*2700` 题 /cy。

首先，每一个不同的时刻出生的史莱姆走的路程都不一样，所以显然不可能会有两只史莱姆会相遇（给这个条件完全是在迷惑选手）。然后分析这个数据范围，想着大概是 $Tt\log n$ 或者是 $Tn^2$ 的复杂度（$n$ 是地图大小，此处为 $120$），发现前者完全没啥可行的方法，于是去想后者。

我们发现直接做很麻烦，于是我们做一个差分，考虑求方案数。设 $f_t$ 表示前 $t$ 时刻有多少个史莱姆经过了 $(x,y)$，我们只需要判断 $f_t-f_{t-1}$ 是否为 $0$ 即可。我们发现这个东西特别好处理。如果有 $t$ 只史莱姆经过了 $(a,b)$，那么则有 $\frac{t+1}{2}$ 去了 $(a,b+1)$，$\frac t2$ 去了 $(a,b)$（默认取整）。这个东西直接 $n^2$ dp 就可以了。

注意初始化 $dp_{0,0}=t-x-y+1$ 而不是 $t$，因为走的步数不足 $x+y$ 的无法造成贡献。

[考场提交](https://codeforces.com/contest/1733/submission/172722581)。

---

## 作者：z_z_b_ (赞：10)

## CF1733E Conveyor

（古早以前的每周讲题报的题目，结果不讲了，想起来交个题解。）

一道很有意思的人类智慧题。

因为 $t$ 很大，直接求 $(x,y)$ 有没有史莱姆是不现实的。

传送带每经过一只史莱姆就转一次方向，可以发现传送带是“右下右下……” 这样来的。

所以假设经过 $(x,y)$ 的史莱姆有 $z$ 只，那就有 $\lceil\frac{z}{2}\rceil$ 只向右走，$\lfloor\frac{z}{2}\rfloor$ 只向下走（第一只史莱姆向右走）。

可以设 $f_{t,x,y}$ 为 $t$ 时刻之内经过 $(x,y)$ 的史莱姆数量。

那么当 $f_{t,x,y}-f_{t-1,x,y}$ 为正数时，$t$ 时刻一定有史莱姆经过。

$f$ 可以从 $(0,0)$ 递推，只需要知道一共有多少只史莱姆经过 $(0,0)$ 且能到达 $(x,y)$ 就行了。

告诉了总时间，那史莱姆数量可以算出来，只需要注意一下新出生的史莱姆在给定的时间内能不能走到询问的位置了。

单次询问复杂度 $O(n^2)$。

史莱姆，可爱捏。

```cpp
void solve()
{
	memset(f1,0,sizeof f1),memset(f2,0,sizeof f2);
	t=read(),x=read(),y=read();
	f1[0][0]=t-x-y+1,f2[0][0]=t-x-y;//t-x-y+1 时刻起，新出生的史莱姆 t 秒走不到 (x,y)。t-x-y 同理 
	for(int i=0;i<=x;i++)
		for(int j=0;j<=y;j++)
		{
			if(i) f1[i][j]+=f1[i-1][j]/2,f2[i][j]+=f2[i-1][j]/2;//从上面转移 
			if(j) f1[i][j]+=(f1[i][j-1]+1)/2,f2[i][j]+=(f2[i][j-1]+1)/2;//从左边转移
		}
	puts(f1[x][y]>f2[x][y]?"YES":"NO");
}
```

---

## 作者：Miraik (赞：7)

看上去好像一脸不可做，我们分析分析性质。

我们发现题面里这个“当两只史莱姆到了同一个位置时会合并“没有任何用处，因为我们每只史莱姆都不在同一个时刻出生，且每秒都向右或向下移动一格，显然不可能相遇。

但是似乎好像还是一脸不可做？正难则反。

根据上面这个性质，我们发现求出 $t$ 时刻之内所有经过 $(x,y)$ 的史莱姆的个数是不难算的。因为传送带是 右下右下右下右... 这样变化的，容易发现经过 $(a,b)$ 的史莱姆（记为 $c$）中，必然是 $\lceil \frac{c}{2} \rceil$ 只去了 $(a,b+1)$，$\lfloor \frac{c}{2} \rfloor$ 只去了 $(a+1,b)$。

这个过程显然可以递推，但注意初始化是 $f_{0,0}=t-x-y+1$，因为从 $t-x-y+1$ 时刻起，新出生的史莱姆们是对答案没有贡献的（它们走不了 $x+y$ 步，不可能到达 $(x,y)$ ）

于是我们只需要判断 $t-1$ 时刻内经过 $(x,y)$ 的史莱姆数是否等于 $t$ 时刻内即可。显然若相等，说明 $t$ 时刻 $(x,y)$ 没有史莱姆，反之亦然。

时间复杂度 $O(qn^2)$。

[code](https://codeforces.com/contest/1733/submission/172773190)

---

## 作者：_Extroversion (赞：3)

## 题目分析

刚读完题思路迷茫，可以先观察数据范围，$t$ 很大，而 $n,m$ 很小，因此时间复杂度大概率只与 $n,m$ 有关，~~应该都不会去想带 $\log(t)$ 的做法吧。~~

在此之后，不难发现每一时刻史莱姆只能向下或向右移动一格，从起点移动 $(x+y)$ 格才有可能移动到 $(x,y)$。因为任意两只史莱姆距起点的曼哈顿距离均不同，所以永远不会有合并。那能只考虑 $(t-x-y+1)$ 时刻产生的史莱姆吗？大抵难以实现，因为我们不知道此时传送带的状态。

进一步观察，从前 $t$ 时刻的角度，若有 $s$ 只史莱姆经过 $(x,y)$，则有 $\frac{s+1}{2}$ 只往右走，$\frac{s}{2}$ 只往下走。这不就是经典的二维 DP 吗？可以用 $O(nm)$ 的复杂度求出前 $t$ 时刻经过 $(x,y)$ 的数量。
对于第 $t$ 时刻，运用差分的思想，判断前 $t$ 时刻和前 $(t-1)$ 时刻经过的史莱姆数量是否相等即可，注意初始值保证对 $f_{x,y}$ 能产生贡献。

## 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
int Q,x,y;
long long t,f[121][121],f2[121][121];
int main(){
	scanf("%d",&Q);
	while(Q--){
		scanf("%lld%d%d",&t,&x,&y);
		memset(f,0,sizeof(f));
		memset(f2,0,sizeof(f2));
		f[0][0]=t-x-y+1;//注意初始值
		for(int i=0;i<=x;i++){
			for(int j=0;j<=y;j++){
				if(i>0)f[i][j]+=f[i-1][j]/2;
				if(j>0)f[i][j]+=(f[i][j-1]+1)/2;
			}
		}
		f2[0][0]=t-x-y;
		for(int i=0;i<=x;i++){
			for(int j=0;j<=y;j++){
				if(i>0)f2[i][j]+=f2[i-1][j]/2;
				if(j>0)f2[i][j]+=(f2[i][j-1]+1)/2;
			}
		}
		if(f[x][y]==f2[x][y])printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
```


---

## 作者：CQ_Bob (赞：1)

题解摘自 [CSP2024 前做题情况](https://www.luogu.com.cn/article/9zpicw3e)。

## 分析

注意力极强。

会发现，$t$ 时刻是否有点在 $(x,y)$ 相当于判断 $t$ 时刻前经过 $(x,y)$ 的点的数量是否比 $t-1$ 时刻前经过 $(x,y)$ 的点的数量多。因为如果有多的，那么多出来的显然只会在 $t$ 时刻经过。

那么问题就转化为求有多少个点在 $t$ 时刻前经过了 $(x,y)$。发现每个点产生的时刻不同，即对于每个时刻 $t$，每个点走过的路径长度 $p_i$ 互不相同。又因为只会向下或者向右走，所以不可能存在合并的情况。那么，我们就可以将所有的点全部放在 $(0,0)$，然后让它们一起走，看有多少个点经过了 $(x,y)$。记 $f_{i,j}$ 为经过 $(i,j)$ 的点的数量。那么对于第奇数次经过，那些点会跑到 $(i,j+1)$，其它的点会跑到 $(i+1,j)$。即有 $\lceil \frac{f_{i,j}}{2} \rceil$ 的点会到 $(i,j+1)$，$\lfloor \frac{f_{i,j}}{2} \rfloor$ 的点会到 $(i+1,j)$。那么就可以 $O(n^2)$ 转移了。

对于初始的点的数量，只有 $p_i \ge x+y$ 的点才可能经过，所以 $p_i <x+y$ 的点没有任何作用，即 $t$ 时刻有用的点数为 $t-x-y+1$。时间复杂度 $O(tn^2)$。

## 代码

```cpp
il int work(int s,int x,int y){
	for(re int i=0;i<=n;++i)
	for(re int j=0;j<=n;++j) f[i][j]=0;
	f[0][0]=s;
	for(re int i=0;i<=n;++i)
	for(re int j=0;j<=n;++j){
		f[i][j+1]+=(f[i][j]+1)/2;
		f[i+1][j]+=f[i][j]/2;
	}
	return f[x][y];
}
il void solve(){
	int t=rd,x=rd,y=rd;
	if(work(max(0ll,t-x-y+1),x,y)==work(max(0ll,t-1-x-y+1),x,y)) printf("NO\n");
	else printf("YES\n");
	return ;
}
```

---

## 作者：周子衡 (赞：1)

首先注意到以下事实：

**观察** 第 $i$ 个出发的球第 $j$ 秒的坐标 $(x,y)$ 一定满足 $x+y=i+j-1$。

这意味着：

1. 不可能有两个球相撞。
2. 对于每个询问 $(t,x,y)$，只可能是第 $x+y-t+1$ 个出发的球在时刻 $t$ 经过了 $(x,y)$，我们只需要关心这个球即可。

问题转化为求解某个球的运动轨迹。直接模拟时间复杂度不能承受。我们考虑这样一个问题：

- 给定整数 $a$，试问前 $a$ 个球总共有多少个经过了格子 $(x,y)$？

设上面问题的答案为 $c_{a,x,y}$。通过对比 $c_{a-1,x,y}$ 和 $c_{a,x,y}$，我们就可以知道 $a$ 球有没有到达格子 $(x,y)$ 了。

怎么求解 $c$ 呢？我们考虑递推。注意到，如果有 $b$ 个球经过了 $(x,y)$，那么不论这些球分别是从什么方向、以什么顺序来的，一定有 $\lceil\dfrac{b}{2}\rceil$ 个球是从右边离开的，$\lfloor\dfrac{b}{2}\rfloor$ 个球是从下面离开的。这意味着：

$$
c_{a,x,y}=\lfloor\dfrac{c_{a,x-1,y}}{2}\rfloor+\lceil\dfrac{c_{a,x,y-1}}{2}\rceil
$$

边界条件为 $c_{a,0,0}=a$。直接递推即可以总时间复杂度 $O(qn^2)$ 通过此题。

---

## 作者：Wu_Qi_Tengteng (赞：0)

容易发现，一个人每移动一次 $x$ 或 $y$ 就会增加 $1$。

所以说任意时刻一个位置上至多有一个人、在 $a$ 
后面出发的人必定不会出现在他之后会到达的位置上。

并且，如果一个人在 $t$ 时刻到达了 $(x,y)$ ，那么他必然是在 $t-(x+y)$ 时出发的。

那么我们就想要求出 $t-x-y$ 时出发的人的路线。

一个人的路线取决于一个位置在之前被经过了多少次。那么我们只需要考虑 $[0,t-x-y-1]$ 时出发的队伍把每个位置各经过了多少遍。

发现如果一个位置 $(x,y)$ 有 $n$ 个人经过，那么会有 $\lceil\frac{n}{2}\rceil$ 个人到 $(x,y+1)$ ，$\lfloor\frac{n}{2}\rfloor$ 个人到 $(x+1,y)$ 。
这样我们可以 $dp$ 模拟。 $dp_{0,0}=t-x-y$ ，$dp_{i,j+1}=dp_{i,j+1}+
\lceil\frac{dp_{i,j}}{2}\rceil$ ，$dp_{i+1,j}=dp_{i+1,j}+\lfloor\frac{dp_{i,j}}{2}\rfloor$。

时间复杂度 $\mathcal{O(qn^2)}$ 。

```c++
#include<bits/stdc++.h>
using namespace std;
#define R register 
#define int long long
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
const int N=125;
int q,t,x,y; 
int dp[N][N];
signed main(){
	q=read();
	while(q--){
		t=read();x=read();y=read();
		if(t-x-y<0){
			printf("NO\n");
			continue;
		}
		memset(dp,0,sizeof dp);
		dp[0][0]=t-x-y;
		for(R int i=0;i<=x;++i){
			for(R int j=0;j<=y;++j){
				dp[i][j+1]+=(dp[i][j]+1)>>1;
				dp[i+1][j]+=dp[i][j]>>1;
			}
		} 
		int tx=0,ty=0;
		for(R int i=1;i<=x+y;++i){
			if(dp[tx][ty]&1){
				tx++;
			}else ty++;
		}
		if(tx==x&&ty==y){
			printf("YES\n");
		}else printf("NO\n");
	}
	return 0;
}
```

---

## 作者：zdd6310 (赞：0)

# CF1733E Conveyor

发现每一次史莱姆的坐标之和一定会增加，所以史莱姆是不可能重合的。

这是一个很重要的结论。

题目中是按照时间轴移动史莱姆的，但是之后的史莱姆一定不会走到先前的史莱姆前面，所以可以按照史莱姆来移动。

**原来的移动方式可以改变为将第一个史莱姆移动知道移动出棋盘，再将第二个史莱姆移动出棋盘，以此类推，对于答案是完全没有影响的。**

这就是为什么可以求出每一个史莱姆移动结束的状态，在进行差分的原因。这才是关键。

对于一个棋盘，能够影响史莱姆移动状态的只有传送带的方向。

如果我们求第 $p$ 个史莱姆是否经过 $(x,y)$ 格，只需要求出第 $(p-1)$ 个史莱姆走完后传送带的方向，和 $x$ 走完后的方向。如果 $(x,y)$ 的方向一致，说明没有经过 $(x,y)$，不然就是经过了 $(x,y)$。

---

考虑如何求出传送带的方向。我们将传送带的方向转为经过 $(x,y)$ 的次数。如果次数是偶数，那么就会向右，不然就是向下。

这个东西可以递推求出。

1. 知道坐标 $(0,0)$ 被经过了 $x$ 次。
2. 每一个坐标 $(x,y)$，如果被经过了 $k$ 次，那么一共会有 $\lceil \frac{k}{2} \rceil $ 个史莱姆向右，$\lfloor\frac{k}{2} \rfloor $ 个史莱姆向下。

类似数学归纳法，直接可以 $O(xy)$ 求出每一个格子的出现次数。

---

如何求出是第几个史莱姆呢？因为每一个史莱姆每次走坐标之和都会增加 1，所以一定是第 $(t-x-y)$  个史莱姆才有可能在第 $t$ 秒走过 $(x,y)$。

## code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e2+5;
int t,n,m;
int a[MAXN][MAXN],b[MAXN][MAXN];
inline void solve(){
	cin>>t>>n>>m;
	int del=t-n-m;
	for(int i=0;i<=n;i++)for(int j=0;j<=m;j++)
		a[i][j]=b[i][j]=0;
	a[0][0]=del,b[0][0]=del+1;
	for(int i=0;i<=n;i++)for(int j=0;j<=m;j++){
		a[i][j+1]+=(a[i][j]+1)/2;
		a[i+1][j]+=a[i][j]/2;
		b[i][j+1]+=(b[i][j]+1)/2;
		b[i+1][j]+=b[i][j]/2;
	}
	if(a[n][m]!=b[n][m]){
		cout<<"YES\n";
	}else{
		cout<<"NO\n";
	}
}
#define Fopen(file) freopen(file".in","r",stdin),freopen(file".out","w",stdout)
signed main(){
    Fopen("nothingness");
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);
	int T;cin>>T;while(T--)solve();
}
```

---

## 作者：shinkuu (赞：0)

模拟赛题，虚高，场上几乎秒了。

首先考虑在 $t$ 时刻经过 $(x,y)$，那么它一定是在 $t-x-y$ 时刻从 $(0,0)$ 出发。于是问题就变成了这个时刻出发，是否会经过 $(x,y)$。

第一想法肯定是看每个时刻开始的移动是否有规律。打表出来发现没有什么规律。于是换个思路，看每个位置被经过了多少次。

类似 pkusc2024 D2T1 地，发现对于 $(x,y)$ 这个点，每经过两次 $(x-1,y)$ 就会经过一次 $(x,y)$，$(x,y-1)$ 同理。于是先令一个点走完（走到 $x>100$ 或 $y>100$）后下一个点再出发，设 $dp_{i,j}$ 为 $(i,j)$ 累计被经过的次数，则有 $dp_{0,0}=t+1,dp_{i,j}=\left\lfloor \frac{dp_{i-1,j}}{2}\right\rfloor+\left\lceil \frac{dp_{i-1,j}}{2}\right\rceil$。

于是我们就可以在 $O(xy)$ 的时间复杂度内求出 $dp_{x,y}$。这有什么用呢？想到差分。只要知道 $t-x-y$ 时刻的 $dp_{x,y}$ 和 $t-x-y-1$ 时刻的，那么就可以知道 $t-x-y$ 时刻出发的这个点是否经过 $(x,y)$ 了！

$O(qxy)$ 解决。

code：

```cpp
int n,m;
ll dp[N][N];
ll solve(ll t,int x,int y){
	if(t<0){
		return 0;
	}
	dp[0][0]=t+1;
	rep(i,0,x){
		rep(j,0,y){
			if(!i&&!j){
				continue;
			}
			dp[i][j]=0;
			if(i){
				dp[i][j]+=dp[i-1][j]/2;
			}
			if(j){
				dp[i][j]+=(dp[i][j-1]+1)/2;
			}
		}
	}
	return dp[x][y];
}
void Yorushika(){
	read(m);
	while(m--){
		ll t,x,y;read(t,x,y);
		if(!t){
			if(!x&&!y){
				puts("YES");
			}else{
				puts("NO");
			}
			continue;
		}
		if(t-x-y<0){
			puts("NO");
			continue;
		}
		puts(solve(t-x-y,x,y)-solve(t-x-y-1,x,y)?"YES":"NO");
	}
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：CNS_5t0_0r2 (赞：0)

性质题。

首先，不同时刻出生的史莱姆到原点的曼哈顿距离不同，因此史莱姆是不会重合的。

计算每个史莱姆在第 $t$ 个时刻的位置是很困难的，可以转化为比较前 $t$ 个时刻和前 $t - 1$ 个时刻**经过** $(x,y)$ 的史莱姆数量是否相等，相等就说明在 $t$ 时刻 $(x,y)$ 没有史莱姆，否则就一定有。

考虑每个史莱姆经过 $(i,j)$ 后会去哪。

由题意，第 $1$ 个经过 $(i,j)$ 的史莱姆会去 $(i,j + 1)$，第 $2$ 个经过 $(i,j)$ 的史莱姆会去 $(i + 1,j)$，第 $3$ 个经过 $(i,j)$ 的史莱姆又会去 $(i,j + 1)$ $\cdots$ 不难得出，对于前 $k$ 个经过 $(i,j)$ 的史莱姆，有 $\lfloor \frac{k + 1}{2} \rfloor$ 个去 $(i,j + 1)$，有 $\lfloor \frac{k}{2} \rfloor$ 个去 $(i + 1,j)$，这个显然是可以递推的。

设 $dp_t(i,j)$ 代表前 $t$ 个时刻经过 $(i,j)$ 的史莱姆数量，不难得出转移方程：

$$dp_t(i,j) = \lfloor \frac{dp_t(i - 1,j)}{2} \rfloor + \lfloor \frac{dp_t(i,j - 1)}{2} \rfloor$$

可以特盘 $i$ 或 $j$ 为 $0$ 的情况，也可以平移。

边界就是 $dp_t(0,0) = t - (x + y - 1)$（最后 $x +y - 1$ 个史莱姆不可能经过 $(x,y)$，需要去除）。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 129;
int q;
long long t;int x,y;
long long dp1[N][N],dp2[N][N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> q;
	while(q--){
		memset(dp1,0,sizeof dp1);
		memset(dp2,0,sizeof dp2);
		cin >> t >> x >> y;
		dp1[0][0] = max(t - x - y + 1,0ll);
		for(int i = 0;i <= x;i++)
			for(int j = 0;j <= y;j++){
				if(i > 0)
					dp1[i][j] += dp1[i - 1][j] >> 1;
				if(j > 0)
					dp1[i][j] += (dp1[i][j - 1] + 1) >> 1;
			}
		dp2[0][0] = max(t - x - y,0ll);
		for(int i = 0;i <= x;i++)
			for(int j = 0;j <= y;j++){
				if(i > 0)
					dp2[i][j] += dp2[i - 1][j] >> 1;
				if(j > 0)
					dp2[i][j] += (dp2[i][j - 1] + 1) >> 1;
			}
		if(dp1[x][y] == dp2[x][y])
			cout << "NO\n";
		else
			cout << "YES\n";
	}
	return 0;
}
```

---

