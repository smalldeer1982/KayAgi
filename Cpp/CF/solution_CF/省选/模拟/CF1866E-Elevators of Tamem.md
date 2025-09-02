# Elevators of Tamem

## 题目描述

There is a building named Taman Membeku (shortened as Tamem). The building has $ N $ floors numbered from $ 1 $ to $ N $ from bottom to top. The only way to move between floors in the building is to use elevators. There are $ 3 $ elevators available in Tamem, namely elevators $ 1 $ , $ 2 $ , and $ 3 $ .

Pak Chanek works as an elevator operator in Tamem. Pak Chanek will work for $ Q $ days. Initially, each elevator is in floor $ 1 $ and all elevators are on. On each day, exactly one of the following will happen:

- 1 x y – There is a person currently in floor $ x $ who wants to go to floor $ y $ . ( $ 1\leq x,y\leq N $ ; $ x\neq y $ )
- 2 p – Elevator $ p $ changes state at the start of the day. If previously it is on, then it will turn off. If previously it is off, then it will turn on. ( $ 1\leq p\leq3 $ )

For each day, Pak Chanek can control the movement of all elevators as he pleases. However, for each day where there is a person currently in floor $ x $ who wants to go to floor $ y $ , among all elevator movements done by Pak Chanek, the following must happen:

1. One elevator moves to floor $ x $ .
2. The person gets into the elevator.
3. The elevator moves to floor $ y $ .
4. The person gets out of the elevator.

For each day, Pak Chanek can only move the elevators that are currently on. Note that, since a change in state happens at the start of the day, this means that an elevator that turns off on some day starts becoming unusable from that day itself. Conversely, an elevator that turns on on some day starts becoming usable from that day itself.

It is known that the electricity fee for each day is different. More specifically, on the $ j $ -th day, the fee needed to move one elevator up or down by one floor is $ A_j $ .

From the start, Pak Chanek already knows the electricity fees and the sequence of events that will happen on the $ Q $ days, so Pak Chanek can operate the elevators strategically. What is the minimum possible electricity fee to fulfill all needs of the people who want to move between floors in Tamem? Note: in the end, each elevator does not have to go back to floor $ 1 $ .

## 说明/提示

The following is an example of an optimal strategy:

1. On the $ 1 $ -st day: 
  - Elevator $ 2 $ moves to floor $ 3 $ .
  - Elevator $ 3 $ moves to floor $ 2 $ , picks the person up, moves to floor $ 7 $ , then drops the person off.
2. On the $ 2 $ -nd day: 
  - Elevator $ 2 $ picks the person up, moves to floor $ 9 $ , then drops the person off.
3. On the $ 3 $ -rd day: 
  - Elevator $ 2 $ turns off.
4. On the $ 4 $ -th day: 
  - Elevator $ 3 $ moves to floor $ 4 $ , picks the person up, moves to floor $ 5 $ , drops the person off, then moves to floor $ 3 $ .
5. On the $ 5 $ -th day: 
  - Elevator $ 3 $ picks the person up, moves to floor $ 5 $ , then drops the person off.
6. On the $ 6 $ -th day: 
  - Elevator $ 2 $ turns on.
  - Elevator $ 1 $ moves to floor $ 2 $ .
  - Elevator $ 2 $ moves to floor $ 7 $ .
7. On the $ 7 $ -th day: 
  - Elevator $ 2 $ picks the person up, moves to floor $ 3 $ , then drops the person off.
8. On the $ 8 $ -th day: 
  - Elevator $ 1 $ picks the person up, moves to floor $ 1 $ , then drops the person off.

The total electricity fee for each day from the $ 1 $ -st day to the $ 8 $ -th day are $ 24 $ , $ 24 $ , $ 0 $ , $ 18 $ , $ 8 $ , $ 6 $ , $ 28 $ , and $ 6 $ respectively. Therefore, the total electricity fee for the entire $ Q $ days is $ 24+24+0+18+8+6+28+6=114 $ .

It can be obtained that there is no strategy that requires a smaller electricity fee.

## 样例 #1

### 输入

```
9 8
3 4 4 3 4 2 7 6
1 2 7
1 3 9
2 2
1 4 5
1 3 5
2 2
1 7 3
1 2 1```

### 输出

```
114```

# 题解

## 作者：Jordan_Pan (赞：4)

### Preface

大年初一又来水题解了~~~

[题目](https://www.luogu.com.cn/problem/CF1866E)[传送门](https://codeforces.com.cn/problemset/problem/1866/E)

题目大意：一栋大楼有 $N$ 层楼，三座电梯，在 $Q$ 天里每一天 $i$ 都有一个一座电梯运行一层楼的花费 $A_i$ 并发生以下两个事件之一：  
1.一个人从楼层 $x$ 到楼层 $y$，也就是说，要有一座电梯在这一天（或之前）运行到楼层 $x$，再运行到楼层 $y$。  
2.一座电梯改变运行状态，如果它之前可运行，那么从这一天开始变得不可运行，否则从这一天开始变得可运行。  
你需要求出满足所有乘客要求情况下使用的最小花费。

数据范围：$2\leq N\leq 10^5$，$1\leq Q\leq 300$，$1\leq A_i\leq 10^5$。

### Analysis

我们发现 $N$ 很大 $Q$ 很小，不必记录每座电梯具体的位置，只需要记录它上一次载客是在哪一次。

考虑 dp。设 $f_{i,j,k}$ 表示三座电梯最后一次载客分别是第 $i,j,k$ 次需要的最小花费。

我们发现，考虑第 $d$ 次载客时，必然有一座电梯在第 $d-1$ 次载客。枚举其它两座电梯最后一次载客的时间。

比如现在要算 $f_{d,j,k}$，如果第 $d-1$ 次载客的电梯是第一座，从 $f_{d-1,j,k}$转移过来；否则第二座和第三座里一定有一座是上次载客的，比如它是第三座，从 $f_{k,j,d-1}$ 转移过来。（这里的变量 $k$ 枚举的是第一座电梯上次载客的时间）

接下来考虑如何转移。如果没有操作 $2$，我们要找到两次载客的间歇时间中花费最少的那一天转移，再加上从楼层 $x$ 到楼层 $y$ 的花费（这里我脑残预处理用了 ST 表）。加上操作二后，只需要在不可运行的时间里把这座电梯的花费设为无穷大。

时间复杂度 $O(Q^3)$，可以通过此题。

于是我们就做完了，只不过细节挺多的。

### Code

```cpp
#include<bits/stdc++.h>
#define inf (long long)1<<45
#define int long long
using namespace std;
const int _=305;
int n,q[_],d,a[4][25][_],lg[_];
void ST(int w){
	for(int i=1;(1<<i)<=q[0];i++)
		for(int j=0;j+(1<<i)-1<=q[0];j++)
			a[w][i][j]=min(a[w][i-1][j],a[w][i-1][j+(1<<i-1)]);
}
int Min(int w,int l,int r){
	int g=lg[r-l+1];
	return min(a[w][g][l],a[w][g][r-(1<<g)+1]);
}
int x[_],y[_],mp[_];
int f[_][_][_],ans;
bool f1=0,f2=0,f3=0;
变量名清晰易懂
signed main(){
	scanf("%lld%lld",&n,&q[0]);
	for(int i=0;i<4;i++)
		for(int j=0;j<25;j++)
			for(int k=0;k<_;k++)
				a[i][j][k]=inf;
	for(int i=1;i<=q[0];i++)
		scanf("%lld",&a[0][0][i]);
	for(int i=1;i<=q[0];i++){
		scanf("%lld",&q[i]);
		if(q[i]==1){
			d++;mp[d]=i;
			scanf("%lld%lld",&x[d],&y[d]);
		}
		else{
			int x;
			scanf("%lld",&x);
			if(x==1)f1^=1;
			if(x==2)f2^=1;
			if(x==3)f3^=1;
		}
		if(!f1)a[1][0][i]=a[0][0][i];
		if(!f2)a[2][0][i]=a[0][0][i];
		if(!f3)a[3][0][i]=a[0][0][i];
	}
	if(!d){
		printf("0\n");
		return 0;
	}
	lg[1]=0;
	for(int i=2;i<=q[0];i++)
		lg[i]=lg[i>>1]+1;
	mp[0]=0;y[0]=1;
	ST(1);ST(2);ST(3);
	for(int i=0;i<=d;i++)
		for(int j=0;j<=d;j++)
			for(int k=0;k<=d;k++)
				f[i][j][k]=inf;
	f[0][0][0]=0;d=0;
	for(int i=1;i<=q[0];i++){
		if(q[i]==2)continue;
		d++;
		int Cost1,Cost2,Cost3,cost1,cost2,cost3,c1ost,c2ost,c3ost;
		cost1=a[1][0][mp[d]]*abs(x[d]-y[d]);
		c1ost=Min(1,mp[d-1],mp[d])*abs(x[d]-y[d-1]);
		cost2=a[2][0][mp[d]]*abs(x[d]-y[d]);
		c2ost=Min(2,mp[d-1],mp[d])*abs(x[d]-y[d-1]);
		cost3=a[3][0][mp[d]]*abs(x[d]-y[d]);
		c3ost=Min(3,mp[d-1],mp[d])*abs(x[d]-y[d-1]);
		for(int j=0;j<d;j++)
			for(int k=0;k<d;k++){
				f[d][j][k]=min(f[d][j][k],f[d-1][j][k]+c1ost+cost1);
				f[j][d][k]=min(f[j][d][k],f[j][d-1][k]+c2ost+cost2);
				f[j][k][d]=min(f[j][k][d],f[j][k][d-1]+c3ost+cost3);
				if(j==d-1)continue;
				Cost1=Min(1,mp[k],mp[d])*abs(x[d]-y[k]);
				Cost2=Min(2,mp[k],mp[d])*abs(x[d]-y[k]);
				Cost3=Min(3,mp[k],mp[d])*abs(x[d]-y[k]);
				f[d][d-1][j]=min(f[d][d-1][j],f[k][d-1][j]+Cost1+cost1);
				f[d][j][d-1]=min(f[d][j][d-1],f[k][j][d-1]+Cost1+cost1);
				f[d-1][d][j]=min(f[d-1][d][j],f[d-1][k][j]+Cost2+cost2);
				f[j][d][d-1]=min(f[j][d][d-1],f[j][k][d-1]+Cost2+cost2);
				f[d-1][j][d]=min(f[d-1][j][d],f[d-1][j][k]+Cost3+cost3);
				f[j][d-1][d]=min(f[j][d-1][d],f[j][d-1][k]+Cost3+cost3);
			}
	}
	ans=inf;
	for(int j=0;j<d;j++)
		for(int k=0;k<d;k++){
			ans=min(ans,f[d][j][k]);
			ans=min(ans,f[j][d][k]);
			ans=min(ans,f[j][k][d]);
		}
	printf("%lld\n",ans);
	return 0;
}码风严谨
```

### Postscribe

调了两年，怒了，不写注释了，让代码自己猜。

在新的一年里，祝大家心想事成，万事如意~~~

---

## 作者：larsr (赞：3)

~~来水一篇题解~~

首先我们分析一下事件 1，事件 1 要求在这一天有一个电梯经过 $x$ 和 $y$ 两个地点。我们可以把每次的事件 1 的工作安排给**三个电梯之一**的一个电梯，有 $3^Q$ 种情况。

为下面叙述，我们把事件 1 称作**任务**。

对于一个电梯，上次任务在第 $i$ 天，下次任务在第 $j$ 天（保证第 $i$ 天到第 $j$ 天除了这两天没有任务），我们需要在这些天里让这个电梯从 $y_i$ 到 $x_j$。很明显，要让代价最小，可以让这个电梯在这些天中**单位代价最小**的日子完成该移动。我们可以预处理这些东西，不过要注意事件 2 会让一些某些天的某些电梯不能动。 $m_{i,a,b}$ 表示第 $i$ 台电梯从第 $a$ 天到第 $b$ 天中单位代价的最小值。

从 $x_i$ 移动到 $y_i$ 的代价是**固定**的，可以预处理。现在要算其他移动的代价，我们从第一天往后 dp，$dp_{i,a,b,c}$ 代表第 $i$ 天时，1 号电梯上次的任务在第 $a$ 天，2 号电梯上次的任务在第 $b$ 天，3 号电梯上次的任务在第 $c$ 天，的**最小代价**。$dp_{i, a, b, c}$ 对下一天的贡献（还要判断电梯今天能不能运行）如下：

$$
dp_{i, a, b, c} + m_{1,a,i+1} \times |y_a - x_{i+1}|\to dp_{i + 1, i, b, c} \\
dp_{i, a, b, c} + m_{2,b,i+1} \times |y_b - x_{i+1}|\to dp_{i + 1, a, i, c} \\
dp_{i, a, b, c} + m_{3,c,i+1} \times |y_c - x_{i+1}|\to dp_{i + 1, a, b, i}
$$

如果通过刚刚转移方程，复杂度是 $O(Q^4)$。但是实际上到不了，因为当经过第 $i$ 天，三个电梯中必定有一个完成了该天的人任务，当天的状态数是 $O(Q^2)$。例如，当第 $i$ 天有任务时，状态只能是 $dp_{i,i,x,y}$ 和 $dp_{i,x,i,y}$ 和 $dp_{i,x,y,i}$，其中 $x$ 和 $y$ 是可变的。

可以用队列维护当天的状态有哪些，时间复杂度是 $O(Q^3)$，刚好可以过。

贴一份代码
```cpp
#include<cstdio>
#include<cmath>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 305
#define inf 0x3f3f3f3f3f3f3f3f
#define ll long long
using namespace std;
int n, q;
ll a[N];
int ka[N], kb[N], kc[N];
int flag[N][4], go[N];
ll gom[N][N][4];
ll dp[2][N][N][N];
ll ans = 0;
struct node
{
	int a, b, c;
};
queue<node>p[2];
int main()
{
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= q; i++)scanf("%d", a + i);
	flag[0][1] = flag[0][2] = flag[0][3] = 1;
	for(int i = 1; i <= q; i++)
	{
		flag[i][1] = flag[i - 1][1];
		flag[i][2] = flag[i - 1][2];
		flag[i][3] = flag[i - 1][3];
		scanf("%d", ka + i);
		if(ka[i] == 1)scanf("%d%d", kb + i, kc + i), go[i] = kc[i], ans += a[i] * abs(kb[i] - kc[i]);
		else scanf("%d", kb + i), flag[i][kb[i]] ^= 1;
	}
	go[0] = 1;
	memset(gom, 0x3f, sizeof gom);
	for(int i = 1; i <= q; i++)
		for(int j = 1; j <= i; j++)
			for(int s = 1; s <= 3; s++)
			{
				gom[j][i][s] = gom[j][i - 1][s];
				if(flag[i][s])gom[j][i][s] = min(gom[j][i][s], a[i]);
			}
	for(int j = 1; j <= q; j++)
		for(int s = 1; s <= 3; s++)
			gom[0][j][s] = gom[1][j][s];
	memset(dp, 0x3f, sizeof dp);
	dp[0][0][0][0] = 0;
	node xxx = {0, 0, 0};
	p[0].push(xxx);
	int now = 0;
	for(int i = 1; i <= q; i++)
	{
		int las = now;
		now ^= 1;
		if(ka[i] == 2)
		{
			while(!p[las].empty())
			{
				node w = p[las].front();
				p[las].pop();
				dp[now][w.a][w.b][w.c] = dp[las][w.a][w.b][w.c];
				p[now].push(w);
				dp[las][w.a][w.b][w.c] = inf;
			}
		}
		else
		{
			while(!p[las].empty())
			{
				node w = p[las].front();
				p[las].pop();
				if(flag[i][1] && gom[w.a][i][1] != inf)
				{
					node m = w;
					m.a = i;
					if(dp[now][m.a][m.b][m.c] == inf)p[now].push(m);
					dp[now][m.a][m.b][m.c] = min(dp[now][m.a][m.b][m.c], dp[las][w.a][w.b][w.c] + gom[w.a][m.a][1] * abs(go[w.a] - kb[m.a]));
				}
				if(flag[i][2] && gom[w.b][i][2] != inf)
				{
					node m = w;
					m.b = i;
					if(dp[now][m.a][m.b][m.c] == inf)p[now].push(m);
					dp[now][m.a][m.b][m.c] = min(dp[now][m.a][m.b][m.c], dp[las][w.a][w.b][w.c] + gom[w.b][m.b][2] * abs(go[w.b] - kb[m.b]));
				}
				if(flag[i][3] && gom[w.c][i][3] != inf)
				{
					node m = w;
					m.c = i;
					if(dp[now][m.a][m.b][m.c] == inf)p[now].push(m);
					dp[now][m.a][m.b][m.c] = min(dp[now][m.a][m.b][m.c], dp[las][w.a][w.b][w.c] + gom[w.c][m.c][3] * abs(go[w.c] - kb[m.c]));
				}
				dp[las][w.a][w.b][w.c] = inf;
			}
		}
	}
	ll minn = 1e18;
	while(!p[now].empty())
	{
		node w = p[now].front();
		p[now].pop();
		minn = min(minn, dp[now][w.a][w.b][w.c]);
	}
	printf("%lld\n", ans + minn);
	return 0;
}
```

---

## 作者：_maze (赞：3)

一开始没看到 $Q$ 的范围，寄麻了。但用脑子想想也知道 $N$ 是个没用的条件啊。

发现  $Q$ 太小了，考虑枚举每个电梯上一个待的位置。如果一个电梯想要接这个乘客，它会停在上一个它搭过的乘客的终点。然后在这一段区间里选择一个电费最小的点移动到这个乘客的起点。由于 $Q$ 只有 $300$，这部分显然可以 $O(n^2)$ 暴力预处理。

于是我们设 $f_{i,j,k}$ 表示当前三辆电梯上一个搭人的位置。显然当前为第 $d$ 个人的转移必定会有一个变量为 $d-1$，我们只要枚举剩下两个变量就好。总共的时间复杂度为 $O(Q^3)$。

题目里还有对电梯状态的限制，但是难不倒我们，我们把整个天数复制三遍作为每个电梯的电费，然后把电梯不能用的时段的电费设为无限大即可。最终输出即为一架电梯载了最后一个人中合法状态最小值

```cpp
/*
slow is fast
*/
#include<bits/stdc++.h>
#define pre(i,a,b) for(int i=a;i<=b;++i)
#define suf(i,a,b) for(int i=a;i>=b;--i)
#define ll long long
#define pii pair<int,int>
using namespace std;
const int N=305,p=1e9+7;
namespace Y {
int n,Q,a[N];
ll f[N][N][N],mn[3][N][N];
struct node { int opt,x,y; }w[N];
inline void chkmin(ll &a,ll b) { if(a>b) a=b; }
inline void chkmax(ll &a,ll b) { if(a<b) a=b; }
void MAIN() {
  cin>>n>>Q;
  pre(i,1,Q) cin>>a[i];
  pre(i,1,Q) {
    cin>>w[i].opt>>w[i].x;
    if(w[i].opt==1) cin>>w[i].y;
    else w[i].x--;
  }
  int chk[3]={0};
  pre(i,1,Q) {
    if(w[i].opt==2) chk[w[i].x]=1^chk[w[i].x];
    mn[0][i][i]=chk[0]?2e13:a[i];
    mn[1][i][i]=chk[1]?2e13:a[i];
    mn[2][i][i]=chk[2]?2e13:a[i];
  }
  pre(i,1,Q) pre(j,i+1,Q) {
    mn[0][i][j]=min(mn[0][i][j-1],mn[0][j][j]);
    mn[1][i][j]=min(mn[1][i][j-1],mn[1][j][j]);
    mn[2][i][j]=min(mn[2][i][j-1],mn[2][j][j]);
  }
  pre(i,1,Q) {
    mn[0][0][i]=mn[0][1][i];
    mn[1][0][i]=mn[1][1][i];
    mn[2][0][i]=mn[2][1][i];
  }
  memset(f,0x3f,sizeof f);
  f[0][0][0]=0;
  int las=0;
  vector<int> peo;
  w[0].y=1;
  pre(i,1,Q) {
    if(w[i].opt==2) continue;
    peo.push_back(i);
    pre(j,0,i-1) {
      pre(k,0,i-1) {
        chkmin(f[i][j][k],f[las][j][k]+(abs(w[las].y-w[i].x)*mn[0][las][i])+(abs(w[i].y-w[i].x)*mn[0][i][i]));
        chkmin(f[las][i][k],f[las][j][k]+(abs(w[j].y-w[i].x)*mn[1][j][i])+(abs(w[i].y-w[i].x)*mn[1][i][i]));
        chkmin(f[las][j][i],f[las][j][k]+(abs(w[k].y-w[i].x)*mn[2][k][i])+(abs(w[i].y-w[i].x)*mn[2][i][i]));

        chkmin(f[i][las][k],f[j][las][k]+(abs(w[j].y-w[i].x)*mn[0][j][i])+(abs(w[i].y-w[i].x)*mn[0][i][i]));
        chkmin(f[j][i][k],f[j][las][k]+(abs(w[las].y-w[i].x)*mn[1][las][i])+(abs(w[i].y-w[i].x)*mn[1][i][i]));
        chkmin(f[j][las][i],f[j][las][k]+(abs(w[k].y-w[i].x)*mn[2][k][i])+(abs(w[i].y-w[i].x)*mn[2][i][i]));
        
        chkmin(f[i][k][las],f[j][k][las]+(abs(w[j].y-w[i].x)*mn[0][j][i])+(abs(w[i].y-w[i].x)*mn[0][i][i]));
        chkmin(f[j][i][las],f[j][k][las]+(abs(w[k].y-w[i].x)*mn[1][k][i])+(abs(w[i].y-w[i].x)*mn[1][i][i]));
        chkmin(f[j][k][i],f[j][k][las]+(abs(w[las].y-w[i].x)*mn[2][las][i])+(abs(w[i].y-w[i].x)*mn[2][i][i]));
      }
    }
    las=i;
  }
  reverse(peo.begin(),peo.end());
  ll ans=2e13;
  pre(i,0,las-1) pre(j,0,las-1) {
    if(i==j&&j!=0) continue;
    chkmin(ans,f[las][i][j]);
  }
  pre(i,0,las-1) pre(j,0,las-1) {
    if(i==j&&j!=0) continue;
    chkmin(ans,f[i][las][j]);
  }
  pre(i,0,las-1) pre(j,0,las-1) {
    if(i==j&&j!=0) continue;
    chkmin(ans,f[i][j][las]);
  }
  if(peo.size()==0) {
    cout<<0<<endl;
    return ;
  } 
  cout<<ans<<endl;
}
};//namespace Y
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int T=1;
	while(T--) Y::MAIN();
	return 0;
}
```


---

## 作者：Ace_FutureDream (赞：1)

偶遇神秘溢出，硬调 $4$ 小时无法战胜。

首先 $n$ 是没用的，因为上一次电梯的位置只跟上次在哪个询问载客有关，你不可能在不载客的时候去走到一个没用的位置，除非是让电梯移动到下一次载客的位置。

所以设 $f_{i,j,k}$ 表示三个电梯上一次载客分别在 $i,j,k$ 时候，已经解决了 $1\sim\max\{i,j,k\}$ 天载客的最小代价。

考虑转移，第一种是直接从上一次载客的位置过来：

$$f_{i-1,j,k}+val_{i,0}+\operatorname{cost}(i-1,i,0)\times |y_{i-1}-x_i|\to f_{i,j,k}$$

$$f_{j,i-1,k}+val_{i,0}+\operatorname{cost}(i-1,i,1)\times |y_{i-1}-x_i|\to f_{j,i,k}$$

$$f_{j,k,i-1}+val_{i,2}+\operatorname{cost}(i-1,i,2)\times |y_{i-1}-x_i|\to f_{j,k,i}$$

其中 $val_{i,j}$ 表示第 $i$ 天的第 $j$ 部电梯从 $x_i$ 到 $y_i$ 载客的代价，$\operatorname{cost}(l,r,j)$ 表示第 $j$ 部电梯在第 $l$ 天到第 $r$ 天电梯移动的最小代价。

第二种是从其他位置过来，与上面的转移同理。

但是要注意，如果我们把不能移动的电梯花费设为 $inf$，那么这个 $inf$ 不能太大也不能太小，太大会爆 `long long`，太小会导致让一些不能转移的电梯转移了，让最终结果错误。

所以可以将 $inf$ 直接设为 $10^{18}$，然后开 `__int128`，这样不会爆 `long long` 答案也正确。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const ll N=310;
const __int128 D=1;
ll val[N][4];
ll a[N];
ll cant[4];
__int128 f[N][N][N];
ll l[N],r[N],g[3][N][N],id[N];
inline void mi(__int128 &x,__int128 y){
	x=(x<y?x:y);
}
inline ll qry(ll op,ll l,ll r){
	l=id[l];r=id[r];
	l=max(l,1ll);
	return g[op][l][r];
}
inline ll mb(ll x){
	return (x>0?x:-x);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	ll n,q;
	cin>>n>>q;
	for(ll i=1;i<=q;i++)
		cin>>a[i];
	ll cnt=0;
	for(ll i=1;i<=q;i++){
		ll op,x,y;
		cin>>op>>x;
		if(op==1){
			cnt++;
			id[cnt]=i;
			cin>>y;
			l[cnt]=x,r[cnt]=y;
		}else{
			x--;
			cant[x]^=1;
		}
		for(ll j=0;j<=2;j++){
			if(cant[j])
				val[i][j]=1e18;
			else 
				val[i][j]=a[i];
		}
	}
	for(ll op=0;op<=2;op++){
		for(ll i=1;i<=q;i++){
			g[op][i][i]=val[i][op];
			for(ll j=i+1;j<=q;j++){
				g[op][i][j]=min(g[op][i][j-1],val[j][op]);
			}
		}
	}
	for(ll i=0;i<=cnt;i++)
		for(ll j=0;j<=cnt;j++)
			for(ll k=0;k<=cnt;k++)
				f[i][j][k]=1e18;
	f[0][0][0]=0;
	r[0]=1;
	__int128 ans=1e18;
	for(ll i=1;i<=cnt;i++){
		ll w=r[i]-l[i];w=mb(w);
		__int128 c1=D*val[id[i]][0]*w;
		__int128 c2=D*val[id[i]][1]*w;
		__int128 c3=D*val[id[i]][2]*w;
		for(ll j=0;j<i;j++){
			for(ll k=0;k<i;k++){
				ll p=i-1;
				//part1
				mi(f[i][j][k],f[p][j][k]+c1+D*qry(0,p,i)*mb(r[p]-l[i]));
				mi(f[j][i][k],f[j][p][k]+c2+D*qry(1,p,i)*mb(r[p]-l[i]));
				mi(f[j][k][i],f[j][k][p]+c3+D*qry(2,p,i)*mb(r[p]-l[i]));
				//part2
				mi(f[i][p][j],f[k][p][j]+c1+D*qry(0,k,i)*mb(r[k]-l[i]));
				mi(f[i][j][p],f[k][j][p]+c1+D*qry(0,k,i)*mb(r[k]-l[i]));
				mi(f[p][i][j],f[p][k][j]+c2+D*qry(1,k,i)*mb(r[k]-l[i]));
				mi(f[j][i][p],f[j][k][p]+c2+D*qry(1,k,i)*mb(r[k]-l[i]));
				mi(f[p][j][i],f[p][j][k]+c3+D*qry(2,k,i)*mb(r[k]-l[i]));
				mi(f[j][p][i],f[j][p][k]+c3+D*qry(2,k,i)*mb(r[k]-l[i]));
			}
		}
		if(i==cnt){
			for(ll j=0;j<i;j++){
				for(ll k=0;k<i;k++){
					mi(ans,f[i][j][k]);
					mi(ans,f[j][i][k]);
					mi(ans,f[j][k][i]);
				}
			}
		}
	}
	if(ans==1e18)ans=0;
	cout<<(ll)ans<<'\n';
	return 0;
} 

```

---

## 作者：DengDuck (赞：1)

得到了 JoeyJ 老师の肯定，表示代码很优雅，所以我就来写一发题解吧。

发现状态肯定得表示三个电梯的位置，但是真用位置来表示非常没有前途，所以我们考虑设 $F_{T,i,j,k}$ 表示三个电梯上一次完成的任务分别是 $i,j,k$，当前处理到了第 $T$ 个任务。

但是四维很不可做，所以我们考虑改变，发现如果只考虑任务 $1$，将任务 $2$ 的结果改存为某一时刻电梯的状态，这样比较有前途，因为如果只考虑任务 $1$，显然有 $T=\max(i,j,k)$，所以就减掉了一维，同理我们可以通过预处理找出下一个任务 $1$ 来转移。

转移时注意我们可以提前到那个位置，我们肯定希望选最便宜一天去移动，但是我们在第 $i$ 天可以转移的前提是电梯开放，我们考虑对于每个电梯都 $\mathcal O(n^3)$ 预处理出每个区间电梯开发时最便宜的一天的价格，用这个来转移。

同时也要注意在任务当天一定要可以走，不然我们就没办法把人送走，太失败了，唉。

然后刷表法转移即可，时间复杂度 $\mathcal O(n^3)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=305;
const LL Inf=1e15;
int n,Q,Can[N][3],X[N],Y[N],Op[N];
LL F[N][N][N],A[N],MnA[N][N],MnB[N][N],MnC[N][N],LST,Nxt[N];
void Min(LL &x,LL y){if(x>y)x=y;}
int main()
{
	freopen("elevator.in","r",stdin);
	freopen("elevator.out","w",stdout);
	scanf("%d%d",&n,&Q);
	for(int i=1;i<=Q;i++)
	{
		scanf("%lld",&A[i]);
	}
	Can[0][0]=Can[0][1]=Can[0][2]=1;
	for(int i=1;i<=Q;i++)
	{
		for(int j=0;j<3;j++)Can[i][j]=Can[i-1][j];
		scanf("%d",&Op[i]);
		if(Op[i]==1)
		{
			scanf("%d%d",&X[i],&Y[i]);
		//	cout<<LST<<"->"<<i<<endl;
			Nxt[LST]=i,LST=i;
		}
		else
		{
			int X;
			scanf("%d",&X);
			Can[i][X-1]^=1;
		}
	}
	memset(F,127,sizeof(F));
	A[0]=Inf;
	for(int i=0;i<=Q;i++)
	for(int j=i;j<=Q;j++)
	{
		LL MA=Inf,MB=Inf,MC=Inf;
		for(int k=i;k<=j;k++)
		{
			if(Can[k][0])Min(MA,A[k]);
			if(Can[k][1])Min(MB,A[k]);
			if(Can[k][2])Min(MC,A[k]);
		}
		MnA[i][j]=MA,MnB[i][j]=MB,MnC[i][j]=MC;
	}
	Y[0]=1;
	F[0][0][0]=0;
	LL Ans=Inf;
	for(int i=0;i<=LST;i++)
	for(int j=0;j<=LST;j++)
	for(int k=0;k<=LST;k++)
	{
		if((i==j&&i&&j)||(j==k&&j&&k)||(i==k&&i&&k))continue;
		if(Op[i]==2||Op[j]==2||Op[k]==2)continue;
		int t=Nxt[max({i,j,k})];
	//	if(F[i][j][k]!=F[0][0][Q+1])cout<<i<<' '<<j<<' '<<k<<' '<<F[i][j][k]<<endl;
		if(MnA[i][t]!=Inf&&Can[t][0])Min(F[t][j][k],F[i][j][k]+MnA[i][t]*abs(Y[i]-X[t])+abs(Y[t]-X[t])*A[t]);
		if(MnB[j][t]!=Inf&&Can[t][1])Min(F[i][t][k],F[i][j][k]+MnB[j][t]*abs(Y[j]-X[t])+abs(Y[t]-X[t])*A[t]);
		if(MnC[k][t]!=Inf&&Can[t][2])Min(F[i][j][t],F[i][j][k]+MnC[k][t]*abs(Y[k]-X[t])+abs(Y[t]-X[t])*A[t]);
		if(max({i,j,k})==LST)Min(Ans,F[i][j][k]);
	}
	printf("%lld\n",Ans);
}
```

---

## 作者：鲤鱼江 (赞：0)

模拟赛搬的题，来写一篇题解。

首先发现 $Q$ 很小但是 $N$ 很大，于是猜测复杂度与 $N$ 无关。

我们考虑每次移动电梯必然是一步到位（既不可能出现电梯在不载人的情况下分两天移动），于是只需要考虑这个电梯上一次送人是在什么时候，送到了哪里。

DP 式子呼之欲出：我们设 $dp_{i,j,k}$ 表示三辆电梯分别在第 $i$ 天，第 $j$ 天，第 $k$ 天运过人，DP 时枚举两维状态（因为上一次要运人的时候肯定运了人），再枚举上一次是哪一个电梯运人和这一次是哪个电梯运人，大力转移，时间复杂度 $O(n^3)$。

具体转移时需要用到 RMQ，发现 $Q\leq 300$，于是选择 $O(Q^2)$ 预处理，$O(1)$ 查询 ~~（有个朋友用了 SGT 喜提暴力分）~~。

为了实现简洁选择了封装。

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace Fread {
	const int SIZE=1<<21;char buf[SIZE],*S,*T;
	inline char getchar() {if(S==T){T=(S=buf)+fread(buf,1,SIZE,stdin);if(S==T)return '\n';}return *S++;}
}
namespace Fwrite {
	const int SIZE=1<<21;char buf[SIZE],*S=buf,*T=buf+SIZE;
	inline void flush(){fwrite(buf,1,S-buf,stdout);S=buf;}
	inline void putchar(char c){*S++=c;if(S==T)flush();}
	struct POPOSSIBLE{~POPOSSIBLE(){flush();}}ztr;
}
#define getchar Fread :: getchar
#define putchar Fwrite :: putchar
namespace Fastio{
	struct Reader{
	    template<typename T>
    	Reader& operator >> (T& x) {
        	char c=getchar();T f=1;while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}x=0;
        	while(c>='0'&&c<='9'){x=x*10+(c-'0');c=getchar();}x*=f;return *this;
    	}
	    Reader(){}
	}cin;
	struct Writer{
	    template<typename T>
	    Writer& operator << (T x) {
	        if(x==0){putchar('0');return *this;}if(x<0){putchar('-');x=-x;}static int sta[45];int top=0;
	        while(x){sta[++top]=x%10;x/=10;}while(top){putchar(sta[top]+'0');--top;}return *this;
    	}
    	Writer& operator << (char c) {putchar(c);return *this;}
    	Writer(){}
	}cout;
}

#define endl '\n'
#define int long long
#define F for(int id=0;id<3;++id)
#define cin Fastio :: cin
#define cout Fastio :: cout

const int N=310;
int a[N],minn[3][N][N],fg[N],opt[N],X[N],Y[N],dp[N][N][N],n,q,las;
inline int dis(const int x,const int y,const int v){return (x>=y)?((x-y)*v):((y-x)*v);}
inline void Min(int &x,const int y){x=(x>=y)?y:x;}
void DP(int x,int y,int z,int day){
	int v=dis(X[day],Y[day],a[day]);
	if(!fg[0]) Min(dp[day][y][z],dp[x][y][z]+dis(Y[x],X[day],minn[0][x][day])+v);
	if(!fg[1]) Min(dp[x][day][z],dp[x][y][z]+dis(Y[y],X[day],minn[1][y][day])+v);
	if(!fg[2]) Min(dp[x][y][day],dp[x][y][z]+dis(Y[z],X[day],minn[2][z][day])+v);
}

signed main(){
	cin>>n>>q;
	for(int i=1;i<=q;++i) cin>>a[i];
	F minn[id][0][0]=1e14;
	for(int i=1;i<=q;++i){
		cin>>opt[i]>>X[i];
		if(opt[i]==2) --X[i];
		if(opt[i]==1) cin>>Y[i];
		else fg[X[i]]^=1;
		F minn[id][i][i]=fg[id]?1e14:a[i];
		for(int j=i-1;~j;--j) F minn[id][j][i]=min(minn[id][j][i-1],minn[id][i][i]);
	}
	F fg[id]=0;memset(dp,127/3,sizeof(dp));dp[0][0][0]=0;X[0]=1;Y[0]=1;
	for(int i=1;i<=q;++i){
		if(opt[i]==1){
			for(int j=0;j<i;++j) for(int k=0;k<i;++k){
				if(opt[j]==2||opt[k]==2) continue;
				DP(las,j,k,i);DP(j,las,k,i);DP(j,k,las,i);
			}
			las=i;
		}else fg[X[i]]^=1;
	}
	int ans=1e18;
	for(int i=0;i<=q;++i) for(int j=0;j<=q;++j){Min(ans,dp[las][i][j]);Min(ans,dp[i][las][j]);Min(ans,dp[i][j][las]);}
	cout<<ans<<endl;
	return 0;
}
```

---

