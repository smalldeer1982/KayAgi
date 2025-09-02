# [USACO04OPEN] Turning in Homework G

## 题目描述

贝茜有 $ C $ ( $ 1 \leq C \leq 1000 $ )门科目的作业要上交，之后她要去坐巴士和奶牛同学回家。

每门科目的老师所在的教室排列在一条长为 $ H $ ( $ 1 \leq H \leq 1000 $ )的走廊上，他们只在课后接收作业，交作业不需要时间。贝茜现在在位置0，她会告诉你每个教室所在的位置，以及走廊出口的位置。她每走1个单位的路程，就要用1秒。她希望你计算最快多久以后她能交完作业并到达出口。

## 说明/提示

走到坐标 8 处，第 9 分钟交一本作业，等到第 12 分钟时，交另一本作业。再走到坐标 4 处交作业，最后走到坐标 3 处，交最后一本作业，此地就是车站所在位置，共用时 22 分钟


## 样例 #1

### 输入

```
4 10 3
8 9
4 21
3 16
8 12
```

### 输出

```
22```

# 题解

## 作者：dzz1537568241 (赞：22)

其实就是一道很裸的区间dp + 贪心，我们分成两部分考虑


# 一：贪心

最佳策略应该是由下面两种状态转移过来的

 1.  向左或向右移动到 下一个教室 交作业

1. 从一个端点移动到另一个端点

如果**先去中间某个教室**，**之后必然还要走到i教室和j教室**，那么**不如先去i教室或者j教室**，之后去另一端的教室时必然会经过中间的教室交作业。

# 二：区间dp

先把教室按照x轴上的坐标排序
```cpp
struct node{
	int x, t;
	bool operator < (const node &b)const{
		return x < b.x;
	}
}a[maxc];
int main(){
	cin>>C>>H>>B;
	for(int i = 1; i <= C; i++){
		cin>>a[i].x>>a[i].t;
	}
	sort(a + 1, a + 1 + C);
}
```



所有数轴上的dp题目基本都是f[maxn][maxn][2]这样的数组，

- 用f[ i ][ j ][ 0 ]来表示 当前人 在区间[ i , j ] 的左端点

- 用f[ i ][ j ][ 1 ]来表示 当前人 在区间[ i , j ] 的右端点

在这道题目里要稍微懂得灵活变通一点，

- 用f[ i ][ j ][ 0 ]来表示 当前人 在区间[ i , j ] 的左端点, 且区间[i + 1, j]的教室没有交作业

- 用f[ i ][ j ][ 1 ]来表示 当前人 在区间[ i , j ] 的右端点，且区间[i, j - 1]的教室还没有交作业

这样就能写出状态转移方程式：

```cpp
f[i][j][0] = min(f[i][j][0], max(f[i - 1][j][0] + a[i].x - a[i - 1].x, a[i].t) );
f[i][j][0] = min(f[i][j][0], max(f[i][j + 1][1] + a[j + 1].x - a[i].x, a[i].t) );
f[i][j][1] = min(f[i][j][1], max(f[i][j + 1][1] + a[j + 1].x - a[j].x, a[j].t) );
f[i][j][1] = min(f[i][j][1], max(f[i - 1][j][0] + a[j].x - a[i - 1].x, a[j].t) );
```
每次枚举的是最后停留的点，f[i][i]就是**最后停留到i点时的最小耗时**，注意**这里j需要倒序枚举**

```cpp
	for(int i = 1; i <= C; i++){
		for(int j = C; j >= i; j--){
			f[i][j][0] = min(f[i][j][0], max(f[i - 1][j][0] + a[i].x - a[i - 1].x, a[i].t) );
			f[i][j][0] = min(f[i][j][0], max(f[i][j + 1][1] + a[j + 1].x - a[i].x, a[i].t) );
			f[i][j][1] = min(f[i][j][1], max(f[i][j + 1][1] + a[j + 1].x - a[j].x, a[j].t) );
			f[i][j][1] = min(f[i][j][1], max(f[i - 1][j][0] + a[j].x - a[i - 1].x, a[j].t) );
		}
	}
```
最后给出全部代码：
```cpp
#include <iostream>
#include <cstdio>
#define INF 0x3f3f3f
#include <cstring>
#include <algorithm>
using namespace std;
int C,H,B;
const int maxc = 1050, maxh = 1050; 
int f[maxc][maxc][2];
struct node{
	int x, t;
	bool operator < (const node &b)const{
		return x < b.x;
	}
}a[maxc];
int main(){
	cin>>C>>H>>B;
	for(int i = 1; i <= C; i++){
		cin>>a[i].x>>a[i].t;
	}
	sort(a + 1, a + 1 + C);
	memset(f, INF,sizeof(f));
	f[1][C][0] = max(a[1].x,a[1].t);
	f[1][C][1] = max(a[C].x,a[C].t);
	for(int i = 1; i <= C; i++){
		for(int j = C; j >= i; j--){
			f[i][j][0] = min(f[i][j][0], max(f[i - 1][j][0] + a[i].x - a[i - 1].x, a[i].t) );
			f[i][j][0] = min(f[i][j][0], max(f[i][j + 1][1] + a[j + 1].x - a[i].x, a[i].t) );
			f[i][j][1] = min(f[i][j][1], max(f[i][j + 1][1] + a[j + 1].x - a[j].x, a[j].t) );
			f[i][j][1] = min(f[i][j][1], max(f[i - 1][j][0] + a[j].x - a[i - 1].x, a[j].t) );
		}
	}
	int ans = INF;
	for(int i=1;i<=C;i++)
    {
        ans = min(ans,min(f[i][i][0]+abs(a[i].x - B), f[i][i][1] + abs(a[i].x-B)));
    }
    cout<<ans;
}
```


---

## 作者：ZBHRuaRua (赞：14)

# 洛谷P2339 turning in homework

这道题首先我们看题面，会感觉很像一道区间dp，但是状态方程没有那么好想，那么我们进行分步，先想有没有可以帮助我们的贪心策略。

这道题的贪心其实就是，先将每个办公室按照离原点的距离从小到大进行排序，然后我们一定要先走到左区间端点或右区间端点，因为即使你先走里面，最终你还是要走出来的，时间上不会有节约，明显不优。

通过这层贪心，我们可以得到一个基本的状态方程式

## F[ i ][ j ][ 0/1 ]表示区间i~j还未提交作业，下一步将提交i或j点的作业所需的最短时间

那么我们就可以很轻松地得到状态转移啦，用大区间推小区间即可。

Code：
```cpp
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int C,H,B;
struct node{
	int d,t;
}a[1050];
int F[1050][1050][2];
bool cmp(node a,node b)
{
	return a.d<b.d;
}
int ans=99999999;
int main()
{
//	freopen("7.in","r",stdin);
//	freopen("7.out","w",stdout);
	cin>>C>>H>>B;
	for(int i=1;i<=C;i++)
	{
		cin>>a[i].d>>a[i].t;
	}
	sort(a+1,a+1+C,cmp);
	memset(F,63,sizeof(F));
	F[1][C][0]=max(a[1].d,a[1].t);F[1][C][1]=max(a[C].d,a[C].t);//初始化
	for(int i=1;i<=C;i++)
	{
		for(int j=C;j>=1;j--)//状态转移，应该不难理解
		{
			F[i][j][0]=min(F[i][j][0],max(a[i].t,F[i-1][j][0]+a[i].d-a[i-1].d));
			F[i][j][0]=min(F[i][j][0],max(a[i].t,F[i][j+1][1]+a[j+1].d-a[i].d));
			F[i][j][1]=min(F[i][j][1],max(a[j].t,F[i][j+1][1]+a[j+1].d-a[j].d));
			F[i][j][1]=min(F[i][j][1],max(a[j].t,F[i-1][j][0]+a[j].d-a[i-1].d));
		}
	}
	for(int i=1;i<=C;i++)
	{
		ans=min(ans,min(F[i][i][0]+abs(a[i].d-B),F[i][i][1]+abs(a[i].d-B)));
	}
	cout<<ans<<endl;
}
```


---

## 作者：namelessgugugu (赞：12)

### 题面

贝茜需要从长为 $H$ 的数轴（范围为 $[0, H]$）原点经过 $C$ 个开放着的办公室后到达位于 $B$ 的车站，速度为 $1$。第 $i$ 个办公室位于 $x_i$，在第 $T_i$ 时刻后开放。

$1 \leqslant H, C \leqslant 1000, 0 \leqslant T_i \leqslant 10^4$。

### 分析

读完题会发现不对劲，按理说我们应该尽可能快地跑过去交作业，但是这题中办公室要特定时间后开放，如果先跑到了反而要等，这非常反直觉。

要是办公室是特定时间后关闭该多好？这样我们就不用纠结决策了，直接跑到最近的办公室就行。

考虑到终点是固定的，我们可以时光倒流，让贝茜从终点跑回起点，这样办公室就是在固定时间后关闭而不是开启了。

但是如果事先不知道答案的话也不容易计算每个办公室的关闭时间，由于答案有单调性，可以套一层二分答案。

于是只需要解决这样一个问题：

贝茜从数轴 $B$ 处出发，要在开放时经过所有办公室，最后在 $k$ 时刻内到达原点，办公室在 $T_i'$ 时刻后关闭。

接下来的问题很简单。先把 $x$ 数组排序。令 $f(i, j, 0/1)$ 表示已经走过了 $[i, j]$ 范围内的办公室，贝茜在左 / 右端点的最短时间（为 $+\infty$ 即为不可能），最后看 $f(1, C, 0)$ 是否不超过 $k$ 即可。

转移方程比较简单，具体看代码就行。

复杂度 $O(n^2 \log n)$。

### 代码

与上文不同的是，在代码中我令原点和车站也是办公室，它们的 $T = 0$，这样只需要判断 $f(1, c, 0)$ 是否为 $+\infty$ 了。

```cpp
/*
有些变量名在代码中与上文不一致，这里列出来。
上文 -> 代码
C -> n
H -> w
B -> st
x_i, t_i -> x[i].first(同时也是pos[i]), x[i].second
t_i' -> lim[i]
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long ll;
typedef unsigned long long ull;
const int N = 1005, inf = 0x3f3f3f3f;
int n, m, st;
std::pair<int, int> x[N];
int pos[N], lim[N];
int f[N][N][2];
inline bool check(int k)
{
    for (int i = 1; i <= n;++i)
    {
        pos[i] = x[i].first;
        lim[i] = k - x[i].second;
        if(lim[i] < 0)
            return 0;
    }
    memset(f, 0x3f, sizeof(f));
    f[st][st][0] = f[st][st][1] = 0;
    for (int l = 2; l <= n;++l)
        for (int i = 1; i + l - 1 <= n;++i)
        {
            int j = i + l - 1;
            //转移f[i][j][0]
            {
                if(pos[i + 1] - pos[i] + f[i + 1][j][0] <= lim[i])
                    f[i][j][0] = std::min(f[i][j][0], pos[i + 1] - pos[i] + f[i + 1][j][0]);
                if(pos[j] - pos[i] + f[i + 1][j][1] <= lim[i])
                    f[i][j][0] = std::min(f[i][j][0], pos[j] - pos[i] + f[i + 1][j][1]);
            }
            //转移f[i][j][1]
            {
                if(pos[j] - pos[j - 1] + f[i][j - 1][1] <= lim[j])
                    f[i][j][1] = std::min(f[i][j][1], pos[j] - pos[j - 1] + f[i][j - 1][1]);
                if(pos[j] - pos[i] + f[i][j - 1][0] <= lim[j])
                    f[i][j][1] = std::min(f[i][j][1], pos[j] - pos[i] + f[i][j - 1][0]);
            }
        }
    return f[1][n][0] != inf;
}
inline int bs(void)
{
    int l = 0, r = 20000, res = -1;
    //此处的二分上界大概为 max{T} + 2H，取一个足够大的数就行
    while(l <= r)
    {
        int mid = (l + r) >> 1;
        if(check(mid))
            res = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    return res;
}
int main(void)
{
    scanf("%d%d%d", &n, &m, &st);
    for (int i = 1; i <= n;++i)
        scanf("%d%d", &x[i].first, &x[i].second);
    x[++n] = {0, 0}, x[++n] = {st, 0};
    std::sort(x + 1, x + 1 + n);
    for (int i = 1; i <= n;++i)
        if(x[i].first == st && x[i].second == 0)
        {
            st = i;
            break;
        }
    printf("%d\n", bs());
    return 0;
}
```

---

## 作者：Acc_Robin (赞：8)

# P2339Turning in Homework 题解

[P2339](https://www.luogu.com.cn/problem/P2339)链接在此

本题使用的大致思想有**贪心**和**动态规划**。

使用的模型是**区间DP**。更加细致地，是在区间两端的DP。

$~$

## 贪心：
首先应当明确的是，我们的路线应该是酱紫的：

![](https://accrobin.github.io/assets/image/Arti3.jpg)

原因：
1.我们不可能一直朝着一个方向走，走走停停，那样显然是不优的。
2.那为什么我们的圈子越兜越小了呢？（想一想，为什么？）$^1$

继续，我们考虑，$\exist ~i,j ~s.t.~x_i \le x_j \land T_i \le T_j$这样的两间教室。通俗点讲，就是$i$教室在$j$教室前面，而且$i$教室先下课。那么我们就可以在前往$j$教室的路上顺便前往$i$教室。如果$T_i \ge T_j$，那么我们可以在从$j$返回的路上顺便前往$i$教室。

所以我们应当将每件教室按照位置进行排序（贪心的体现）。

$~$

## 动态规划之区间DP

$~$

### 变量的选取
既然我们兜的圈子是精心规划过的，那么就应当以圈子的范围为突破口。也就是说，将**圈子的范围**作为转移方程的变量，以此来进行转移。我们先将圈子的左右端点记下来，记作$l$和$r$。之后，我们将圈子更严谨地成为“**区间**”。

不过，只有范围还是很粗糙的，我们要进一步精致化。

考虑：我们现在处在一个区间的端点上，接下来要如何走？等等，突然发现似乎我们并不清楚现在**究竟处在这个区间的哪一个端点上**。

因为**处在不同的端点就有不同的转向策略**，所以，必要地，我们应当把现在所处区间的端点也作为一个变量。区间只有两个端点，那么我们记$0$作为左端点，记$1$作为右端点。

$~$

### 动态转移方程
为了简洁和易于理解，将两点$i,j$之间的距离记作$dis(i,j)$，而在具体实现中我们应使用$|x_i-x_j|$，即`abs(a[i].x-a[j].x)`。

请读者**再次阅读题目**，**明确各个变量的含义**。

接下来就是写出动态转移方程的时候了：

我们设$f[l][r][0]$表示当前处在区间$[l,r]$的左端点时$^2$，已经花费的最小时间。

$~$

一、考虑当我们处在区间$[l,r]$的左端点上时，上一步可能是从哪里转移过来的：

　　1）如果是第$l-1$个教室，我们花费的时间至少是$f[l-1][r][0]+dis(l-1,l)$，（已经花费的时间+将花费的时间）。又因为受到了时间$T$的限制，故我们这个步骤的结果就是$\max(f[l-1][r][0]+dis(l-1,l),T_{l})$。

　　2）如果是第$r+1$个教室，我们花费是时间至少是$f[l][r+1][1]+dis(l,r+1)$，同样受到时间限制，这个步骤的结果是$\max(f[l][r+1][1]+dis(l,r+1),T_{l})$。

　　我们要从这两种情况中选择时间更小的那个，所以：

$$
f[l][r][0]=\min \begin{Bmatrix}
\max(f[l-1][r][0]+dis(l-1,l),T_{l})
 \\
\max(f[l][r+1][1]+dis(l,r+1),T_{l})
\end{Bmatrix} 
$$

$~$

二、考虑当我们处在区间$[l,r]$的右端点上时，上一步可能是从哪个教室转移来：

　　1）如果是第$l-1$个教室，结果就是$\max(f[l-1][r][0]+dis(l-1,r),T_{r})$。

　　2）如果是第$r+1$个教室，结果就是$\max(f[l][r+1][1]+dis(r,r+1),T_{r})$。

　　结合这两种情况，可得：

$$f[l][r][1]=\min \begin{Bmatrix}
\max(f[l-1][r][0]+dis(l-1,r),T_{r})
 \\
\max(f[l][r+1][1]+dis(r,r+1),T_{r})
\end{Bmatrix} $$

**综上所述**，我们可以得到：

$$
f[l][r][0]=\min \begin{Bmatrix}
\max(f[l-1][r][0]+dis(l-1,l),T_{l})
 \\
\max(f[l][r+1][1]+dis(l,r+1),T_{l})
\end{Bmatrix}\\
f[l][r][1]=\min \begin{Bmatrix}
\max(f[l-1][r][0]+dis(l-1,r),T_{r})
 \\
\max(f[l][r+1][1]+dis(r,r+1),T_{r})
\end{Bmatrix}
$$

然后照着抄，实现在代码上就OK了~

你以为这就OK了？不！还有很多细节：

$~$

## 实现的细节
### 初始化$f$数组
$f$数组的初始化应该赋值为$\infty$，但是还应当把$f[1][n][0]$和$f[1][n][1]$用转移方程来预处理出来。

$~$

### 答案的选择
我们在做完这些步骤之后，得到的是最小的区间$[i,i]$，而区间$f[i][i][0/1]$还要加上$dis(i,d)$才是最终答案。我们还要再$O(n)$跑一遍得出最小值。

代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>

#define max std::max
#define min std::min

typedef struct Res
{
	int x, t;
	bool operator < (const Res &b) const
	{
		if(x<b.x)
			return 1;
		return 0;
	}
}Res;
Res a[1005];
int dp[1005][1005][2];
int main(void)
{
	int n, len, E, i, j, ans;
	scanf("%d%d%d", &n, &len, &E);
	for(i=1;i<=n;i++)
		scanf("%d%d", &a[i].x, &a[i].t);
	sort(a+1, a+n+1);
	memset(dp, 62, sizeof(dp));
	dp[1][n][0] = max(a[1].x, a[1].t);
	dp[1][n][1] = max(a[n].x, a[n].t);
	for(i=1;i<=n;i++)
	{
		for(j=n;j>=1;j--)
		{
			if(i==1 && j==n) continue;
			dp[i][j][0]=min(max(dp[i-1][j][0]+a[i].x-a[i-1].x,a[i].t),max(dp[i][j+1][1]+a[j+1].x-a[i].x, a[i].t));
			dp[i][j][1]=min(max(dp[i-1][j][0]+a[j].x-a[i-1].x,a[j].t),max(dp[i][j+1][1]+a[j+1].x-a[j].x,a[j].t));
		}
	}
	ans = 2147483647;
	for(i=1;i<=n;i++)
		ans = min(ans, min(dp[i][i][1], dp[i][i][0])+abs(E-s[i].x));
	printf("%d\n", ans);
	return 0;
}
```

1:反证

分两种情况：

1）假设我们的圈子大小一直不变，在圈子边界上就会出现时间的浪费，不优。

2）假设我们的圈子越兜越大，在圈子中心就会出现越来越多的空闲教室，也就是说，我们花费的大量不必要的时间在路上。

更加**感性**地，我们这样考虑：圈子越来越小，意味着我们尽可能地将**路上**花费的时间减小了，是更优秀的。

$~$

2:贪心

此时除了这个区间以外的所有教室的作业都已经收好了，不用去理会。注意，$l$和$r$是已经收好作业的。

---

## 作者：Lates (赞：5)

题解里没有说明为啥用区间dp的。

对于三个要交作业的点 $A,B,C$，现在在 $A$.

![image.png](https://i.loli.net/2020/06/24/k3cDvnwpJoLQyRV.png)

我们发现肯定是要在访问 $C$ 的途中把 $B$ 的作业给交了，不然 $BC$ 这段就会重复走。

类似的我们可以想到，最终交作业的过程必然是从大区间推倒到小区间的。

![image.png](https://i.loli.net/2020/06/24/k9KAvfBp5ly8NWd.png)

于是满足区间dp 的性质了。

设 $f[i][j][0/1]$ 为区间 $[i,j]$ 内没有交作业，其余交完作业，此时要交 $i/j$ 作业的最小答案。

然后用 $f[i-1][j][0/1],f[i][j+1][0/1]$ 更新 $f[i][j]$ 即可。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read(){
	register int x=0,f=0,ch=getchar();
	while('0'>ch||ch>'9')f^=ch=='-',ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar();
	return f?-x:x;
}
const int MAX=1005;
int n,m,k;
struct E{
	int x,t;
}e[MAX]; 
inline bool cmp(E a,E b){
	return a.x<b.x;
}
int ans;
int f[MAX][MAX][2];
signed main(){
	n=read(),m=read(),k=read();
	for(register int i=1;i<=n;++i){
		e[i]=(E){read(),read()}	;
	}
	sort(e+1,e+n+1,cmp);
	memset(f,0x3f,sizeof(f));
	f[1][n][0]=max(e[1].t,e[1].x);
	f[1][n][1]=max(e[n].t,e[n].x);
	for(register int i=1;i<=n;++i){
		for(register int j=n;j>=i;--j){
			f[i][j][0]=min(f[i][j][0],min(
				max(f[i-1][j][0]+e[i].x-e[i-1].x,e[i].t),
				max(f[i][j+1][1]+e[j+1].x-e[i].x,e[i].t)
			));
			f[i][j][1]=min(f[i][j][1],min(
				max(f[i-1][j][0]+e[j].x-e[i-1].x,e[j].t),
				max(f[i][j+1][1]+e[j+1].x-e[j].x,e[j].t)
			));
		}
	}
	ans=1e9;
	for(register int i=1;i<=n;++i){
		ans=min(ans,min(f[i][i][0],f[i][i][1])+(e[i].x>k?e[i].x-k:k-e[i].x));
	}
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：cff_0102 (赞：4)

本题可以用区间 dp 解决。设 $dp_{i,j,0/1}$ 为还剩 $[i,j]$ 的作业没交，且接下来去交左边或右边的作业时需要的最少时间。那么转移就很清楚了，也是按照传统的区间 dp 套路做就可以了。

不过本题的重点显然是为什么剩下没交的作业可以用区间来表示。正常来说，如果我们按最优方案交作业，那么在每一时刻剩下没交的作业的位置都不一定是连续的。

实际上可以这样考虑：因为最后没交的作业范围总是要缩到一个点上，那么在范围缩小的过程中，每个在这个范围内的作业一定有一个时刻处于 dp 的区间的左端点或者右端点。那么接下来选择把这个作业交了，和在先前就把这个作业交了是没有区别的。

或者换个说法，在交中间的一个作业之后，还是要在这个区间里跑来跑去，还会很多次经过这个可以交作业的地方，那么在最后一次经过的时候再交这个作业，最终的总时间也是一样的。因此本题状态才可以用一个个区间表示。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1020;
using pii=pair<int,int>;
pii a[N];
int dp[N][N][2];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n,l,b;cin>>n>>l>>b;
	for(int i=1;i<=n;i++)cin>>a[i].first>>a[i].second;
	sort(a+1,a+1+n);
	memset(dp,0x3f,sizeof dp);
	dp[1][n][0]=max(a[1].first,a[1].second);dp[1][n][1]=max(a[n].first,a[n].second);
	for(int l=n-1;l>=1;l--){
		for(int i=1;i+l-1<=n;i++){
			int j=i+l-1;
			dp[i][j][0]=min({dp[i][j][0],max(dp[i-1][j][0]+a[i].first-a[i-1].first,a[i].second),max(dp[i][j+1][1]+a[j+1].first-a[i].first,a[i].second)});
			dp[i][j][1]=min({dp[i][j][1],max(dp[i-1][j][0]+a[j].first-a[i-1].first,a[j].second),max(dp[i][j+1][1]+a[j+1].first-a[j].first,a[j].second)});
		}
	}
	int ans=dp[0][0][0];
	for(int i=1;i<=n;i++){
		ans=min(ans,min(dp[i][i][0],dp[i][i][1])+abs(b-a[i].first));
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：xiaoshumiao (赞：4)

首先发现此题有一个性质：如果要交一个区间的作业，那么肯定要先交区间的左端点或右端点。因为先交中间的话肯定还会再绕回去交两个端点的，所以肯定会更慢。

考虑区间 DP。设 $dp_{i,j,0/1}$ 表示交完所有除了区间 $[i,j]$ 的作业的最小耗时，那么：

$dp_{i,j,0}=\min\begin{cases}
  \max(dp_{i-1,j,0}+x_i-x_{i-1},t_i)\\
  \max(dp_{i,j+1.1}+x_{j+1}-x_i,t_i)
\end{cases}$

$dp_{i,j,1}=\min\begin{cases}
  \max(dp_{i-1,j,0}+x_j-x_{i-1},t_j)\\
  \max(dp_{i,j+1.1}+x_{j+1}-x_j,t_j)
\end{cases}$

最终答案为 $\min\{\min(dp_{i,i,0},dp_{i,i,1})+|x_i-b|\}$。

代码：
```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1010; int dp[N][N][2];
struct P { int x,t; }a[N];
int main() {
  int n,h,b; scanf("%d %d %d",&n,&h,&b);
  for(int i=1;i<=n;i++) scanf("%d %d",&a[i].x,&a[i].t);
  sort(a+1,a+n+1,[](P a,P b) { return a.x<b.x; });
  memset(dp,0x3f,sizeof(dp)),dp[1][n][0]=max(a[1].x,a[1].t),dp[1][n][1]=max(a[n].x,a[n].t);
  for(int i=1;i<=n;i++)
    for(int j=n;j>=i;j--)
      if(i!=1||j!=n)
        dp[i][j][0]=min(max(dp[i-1][j][0]+a[i].x-a[i-1].x,a[i].t),max(dp[i][j+1][1]+a[j+1].x-a[i].x,a[i].t)),
        dp[i][j][1]=min(max(dp[i-1][j][0]+a[j].x-a[i-1].x,a[j].t),max(dp[i][j+1][1]+a[j+1].x-a[j].x,a[j].t));
  int ans=0x3f3f3f3f;
  for(int i=1;i<=n;i++) ans=min(ans,min(dp[i][i][0],dp[i][i][1])+abs(a[i].x-b));
  printf("%d",ans);
  return 0;
}
```

---

## 作者：米奇奇米 (赞：4)

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
struct node{
    int x,y;
};//结构体排序
node a[N];
int n,m,k,f[N][N][2];
bool cmp(node a,node b)
{return a.x<b.x;}//写一个函数，让快排等会从大到小排序
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++) 
    scanf("%d%d",&a[i].x,&a[i].y);//读入
    sort(a+1,a+n+1,cmp);
    memset(f,127,sizeof(f));//进行初始化
    f[1][n][0]=max(a[1].x,a[1].y);
    f[1][n][1]=max(a[n].x,a[n].y);
    for(int i=1;i<=n;i++)
        for(int j=n;j>=i;j--)
        {
            f[i][j][0]=min(f[i][j][0],max(f[i][j+1][1]+a[j+1].x-a[i].x,a[i].y));
            f[i][j][0]=min(f[i][j][0],max(f[i-1][j][0]+a[i].x-a[i-1].x,a[i].y));
            f[i][j][1]=min(f[i][j][1],max(f[i][j+1][1]+a[j+1].x-a[j].x,a[j].y));
            f[i][j][1]=min(f[i][j][1],max(f[i-1][j][0]+a[j].x-a[i-1].x,a[j].y));
        }
    int ans=1e9;
    for(int i=1;i<=n;i++) 
    ans=min(ans,min(f[i][i][0],f[i][i][1])+abs(a[i].x-k));
    cout<<ans;	
}
  这是一题区间dp：
容易想到用f[i][j][k]表示完成了i−−j这段区间的作业，容易想到用f[i][j][k]表示完成了i−−j这段区间的作业。 
然后走到了i(0)或j(1)办公室的最优解然后走到了i(0)或j(1)办公室的最优解。
为了解决这个问题：使用大区间推导小区间！
依据结论：当有一段时间[l,r]未交作业时，位置在l或r最优为了解决这个问题，使用大区间推导小区间。
f[i][j][0]表示i−−j未完成交作业，只交了i(0)或j(1)作业的最优解，转移显然f[i][j][0]表示i−−j未完成交作业，只交了i(0)或j(1)作业的最优解。
转移显然在结束后min(f[i][i][0],f[i][i][1])就表示结束位置为i的最少时间，再加上到车站距离结束后min(f[i][i][0],f[i][i][1])就表示结束位置为i的最少时间，再加上到车站距离。
因为推的顺序相反，需要初始化f[1][C][0]和f[1][C][1]，注意外层i从小到大，内层j从大到小。
具体的看上面的代码！！！！
```

---

## 作者：YksKuusiTAlv (赞：3)

一份简明扼要的题解。

先给出一个结论：当场面上有若干份作业没交，我们交的第一份作业一定是所有没交的作业中最靠左的或者最靠右的。

证明：我们先交一份在中间的作业，当且仅当他出现比左右端点都早，否则一定不优。 既然他比左右端点都早，那么交完左端点往右走的时候 或者 交完右端点往左走的时候，一定可以顺便交掉他，也就是先交它不会使答案变优。

所以我们可以写出一个 $2^n$ 暴力，枚举下一次交左端点还是右端点，使用区间 Dp 优化这个暴力即可。

具体的，由于我们的性质，没交的作业肯定是中间的一段区间，当前我们肯定处于交完这个区间左端点的作业或者右端点的作业的状态。

设 $f_{l,r,0/1}$ 代表还剩 $[l,r]$ 的作业没交，当前在左端点右端点的最小时间，转移枚举下一次跑到左端点还是右端点缩小区间即可。

---

## 作者：PineappleSummer (赞：1)

[P2339 [USACO04OPEN] Turning in Homework G](https://www.luogu.com.cn/problem/P2339)

因为交作业不需要时间，所以交一个区间的作业的时候，一定是先交左端点或者先交右端点。

设 $dp_{l,r,0/1}$ 为还有 $[l,r]$ 的作业没交，当前在 $l/r$ 时的答案。

初始：$dp_{1,n,0}=\max(x_1,t_1)$，$dp_{1,n,1}=\max(x_n,t_n)$。

转移：从相邻区间的两个状态转移而来。

$$dp_{i,j,0}=\max(t_i,\min(dp_{i-1,j,0}+x_i-x_{i-1},dp_{i,j+1,1}+x_{j+1}-x_i))$$

$$dp_{i,j,1}=\max(t_j,\min(dp_{i-1,j,0}+x_j-x_{i-1},dp_{i,j+1,1}+x_{j+1}-x_j))$$

答案为 $\min\limits_{i=1}^n\{|b-x_i|+\min(dp_{i,i,0},dp_{i,i,1})\}$。

时间复杂度 $\mathcal O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1010;
int n, h, b;
int dp[N][N][2], ans = 1e9;
struct Node {
    int x, t;
} a[N];
bool operator < (Node a, Node b) {
    return a.x < b.x;
}
signed main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);
    
    cin >> n >> h >> b;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].t;
    }
    sort (a + 1, a + n + 1);
    memset (dp, 0x3f, sizeof (dp));
    dp[1][n][0] = max (a[1].x, a[1].t);
    dp[1][n][1] = max (a[n].x, a[n].t);
    for (int i = 1; i <= n; ++i)
        for (int j = n; j >= i; j--) {
            if (i == 1 && j == n) continue;
            dp[i][j][0] = max (a[i].t, min (dp[i - 1][j][0] + a[i].x - a[i - 1].x, dp[i][j + 1][1] + a[j + 1].x - a[i].x));
            dp[i][j][1] = max (a[j].t, min (dp[i - 1][j][0] + a[j].x - a[i - 1].x, dp[i][j + 1][1] + a[j + 1].x - a[j].x));
        }
    for (int i = 1; i <= n; i++)
        ans = min (ans, min (dp[i][i][0], dp[i][i][1]) + abs (b - a[i].x));
    cout << ans;
    return 0;
}
```

---

## 作者：quarmer (赞：1)

这题一看就感觉和[关路灯](https://luogu.com.cn/problem/P1220)那题很像，只不过加了一个最早提交时间。再通过~~看标签~~思考，初步确定了是区间dp。

既然是区间 dp，先设计出状态 $f_{i,j}$ 表示交完区间 $[i , j]$ 作业的最小时间，然后发现不太好转移。通过思考，发现这题有一个贪心：**对于每一个区间，交完作业时间的最优解一定是先交区间的一个端点**，因为如果先去区间中间交作业，最后一定会去到两端点，那么这还不如先去一个端点，再去另一个端点的时候一起把中间的一交，不然中间的路就会再走一遍，显然不是最优的

有了这个贪心，我们就可以设出新的状态：设 $f_{i,j,0/1}$ 表示除了区间 $[i, j]$ 的作业全都交完，现在交了 $i/j$ 时的最小时间。

这个区间 dp 就有点特殊，它是从大区间推到小区间。

根据定义，不难写出方程：

$f_{l,r,1}=\min \begin{cases}
\max(f_{l-1,r,0}+d(l-1,r),t_{r})
 \\
\max(f_{l,r+1,1}+d(r,r+1),t_{r})
\end{cases}$

$f_{l,r,0}=\min \begin{cases}
\max(f_{l-1,r,0}+d(l,l - 1),t_{l})
 \\
\max(f_{l,r+1,1}+d(l,r+1),t_{l})
\end{cases}$ 

其中 $d(i, j)$ 为第 $i$ 个交作业的地方到第 $j$ 个的距离。$t_{i}$ 是第 $i$ 个地方的下课时间。因为下课后才能教，所以要取 $\max$。

初始化显然：

$f_{1,n,0} = \max(x_{1}, t_{1})$

$f_{1,n,1} = \max(x_{n}, t_{n})$

注意这里也要 $\max$，原因同上，我就因为没取 $\max$ 错了两次。

最后放上代码，就没有注释了，该说的都说了。

```cpp
#include <algorithm>
#include <iostream>
//#include <cmath>
#include <cstdio>
#include <cstring>
#include <stack>
#include <queue>
#include <vector>
#include <list>
#include <map>
using namespace std ;
#define int long long
#define ll long long 
int n, h, b ;
struct node {
	int x, t ;
}a[1005] ;
bool cmp(node x, node y) {
	return x.x < y.x ;
}
int f[1005][1005][2] ;
int read(){
	char ch ;int s = 0 ;int w = 1;
	while((ch = getchar()) >'9' || ch < '0' )if(ch == '-')w = -1 ;
	while(ch >= '0' && ch <= '9')s = (s << 1) + (s << 3) + (ch ^ 48) , ch = getchar() ;
	return s * w ;
}
signed main() {
	n = read(), h = read(), b = read() ;
	for(int i = 1 ; i <= n ; i++) a[i].x = read(), a[i].t = read() ;
	sort(a + 1, a + n + 1, cmp) ;
	memset(f, 0x3f, sizeof(f)) ;
	f[1][n][0] = max(a[1].x, a[1].t), f[1][n][1] = max(a[n].x, a[n].t) ;
	for(int len = n - 1 ; len ; len--) {
		for(int l = 1, r = l + len - 1 ; r <= n ; l++, r++) {
			f[l][r][0] = min(f[l][r][0], max(f[l - 1][r][0] + a[l].x - a[l - 1].x, a[l].t)) ;
			f[l][r][0] = min(f[l][r][0], max(f[l][r + 1][1] + a[r + 1].x - a[l].x, a[l].t)) ;
			f[l][r][1] = min(f[l][r][1], max(f[l][r + 1][1] + a[r + 1].x - a[r].x, a[r].t)) ;
			f[l][r][1] = min(f[l][r][1], max(f[l - 1][r][0] + a[r].x - a[l - 1].x, a[r].t)) ;
		}
	}
	int ans = 0x3f3f3f3f3f3f3f ;
	for(int i = 1 ; i <= n ; i++) ans = min(ans, min(f[i][i][1], f[i][i][0]) + abs(a[i].x - b)) ;
	cout << ans ;
	return 0 ;
}
```

---

## 作者：Plozia (赞：1)

宣传博客 $\to$ [link](https://www.cnblogs.com/Plozia/p/16485040.html)

首先注意到对于还没交作业的区间 $[l,r]$，一定是先交端点再交中间更优，因为你交端点同时可以顺便把中间交了，但是如果先交中间则还要去端点交。

据此先将输入按 $x$ 升序排序，设 $f_{i,j,0/1}$ 表示 $[i,j]$ 没交作业，剩下的都交了，当前正在交 $i/j$ 的最小时间（注意交好了），初始化 INF，$f_{1,C,0}=\max\{a_1.x,a_1.t\},f_{1,C,1}=\max\{a_C.x,a_C.t\}$。

则有如下转移方程：

$$f_{i,j,0}=\min\{\max\{f_{i,j+1,1}+a_{j+1}.x-a_i.x,a_i.t\},\max\{f_{i-1,j,0}+a_i.x-a_{i-1}.x,a_i.t\}\}$$

$$f_{i,j,1}=\min\{\max\{f_{i,j+1,1}+a_{j+1}.x-a_j.x,a_j.t\},\max\{f_{i-1,j,0}+a_j.x-a_{i-1}.x,a_j.t\}\}$$

注意转移的时候不要算上初始状态 $f_{1,C,0},f_{1,C,1}$。

最后答案就是 $\min_{i \in [1,n]}\{\min\{f_{i,i,0},f_{i,i,1}\}+|b-a_i.x|\}$，$b$ 是门的位置。

GitHub：[CodeBase of Plozia](https://github.com/Plozia/CodeBase-of-Plozia/blob/main/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%20DP/%E5%8C%BA%E9%97%B4%20DP/P2339%20%5BUSACO04OPEN%5DTurning%20in%20Homework%20G.cpp)

Code：

```cpp
/*
========= Plozia =========
	Author:Plozia
	Problem:P2339 [USACO04OPEN]Turning in Homework G
	Date:2022/7/17
========= Plozia =========
*/

#include <bits/stdc++.h>
typedef long long LL;

const int MAXN = 1e3 + 5;
int n, h, b, f[MAXN][MAXN][2];
struct node { int x, t; bool operator <(const node &fir)const { return (x < fir.x); } } a[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
int Abs(int x) { return (x < 0) ? -x : x; }

int main()
{
	n = Read(), h = Read(), b = Read();
	for (int i = 1; i <= n; ++i) a[i].x = Read(), a[i].t = Read();
	std::sort(a + 1, a + n + 1); memset(f, 0x3f, sizeof(f));
	f[1][n][0] = Max(a[1].x, a[1].t); f[1][n][1] = Max(a[n].x, a[n].t);
	for (int i = 1; i <= n; ++i)
		for (int j = n; j >= i; --j)
		{
			f[i][j][0] = Min(f[i][j][0], Min(Max(f[i][j + 1][1] + a[j + 1].x - a[i].x, a[i].t), Max(f[i - 1][j][0] + a[i].x - a[i - 1].x, a[i].t)));
			f[i][j][1] = Min(f[i][j][1], Min(Max(f[i][j + 1][1] + a[j + 1].x - a[j].x, a[j].t), Max(f[i - 1][j][0] + a[j].x - a[i - 1].x, a[j].t)));
		}
	int ans = 0x7f7f7f7f;
	for (int i = 1; i <= n; ++i) ans = Min(ans, Min(f[i][i][0], f[i][i][1]) + Abs(b - a[i].x));
	printf("%d\n", ans); return 0;
}
```

---

## 作者：木xx木大 (赞：1)

[P2339 [USACO04OPEN]Turning in Homework](https://www.luogu.com.cn/problem/P2339)

* 贪心：先将每个办公室按照离原点的距离从小到大进行排序，然后我们一定要先走到左区间端点或右区间端点，因为即使你先走里面，最终你还是要走出来的，时间上不会有节约，明显不优。最终交作业的过程必然是从大区间推倒到小区间的。所以我们用区间dp做这道题。

* 区间dp

  用 $f[i][j][0]$ 来表示当前人在区间 $[i ,j]$ 的左端点, 且区间 $[i + 1,j]$ 的教室没有交作业

  用 $f[i][j][1]$ 来表示当前人在区间 $[i ,j]$ 的右端点，且区间 $[i, j - 1]$ 的教室还没有交作业

  每次枚举的是最后停留的点，$f[i][i]$ 就是最后停留到 $i$ 点时的最小耗时，注意这里 $j$ 需要倒序枚举。具体转移见代码
  
```cpp
#include<bits/stdc++.h>
using namespace std;
int c,h,b;
int x[1010],t[1010],f[1010][1010][2];
struct poit{
	int x,t;
}a[1010];
bool cmp(poit u,poit v)
{
	return u.x<v.x;
}
int main()
{
	scanf("%d%d%d",&c,&h,&b);
	for(int i=1;i<=c;i++)
		scanf("%d%d",&a[i].x,&a[i].t);
	sort(a+1,a+c+1,cmp);
	memset(f,0x3f3f3f3f,sizeof(f));
	f[1][c][0]=max(a[1].x,a[1].t);
	f[1][c][1]=max(a[c].x,a[c].t);
	for(int i=1;i<=c;i++)
		for(int j=c;j>=1;j--)
		{
			f[i][j][0]=min(f[i][j][0],max(f[i-1][j][0]+a[i].x-a[i-1].x,a[i].t));
			f[i][j][0]=min(f[i][j][0],max(f[i][j+1][1]+a[j+1].x-a[i].x,a[i].t));
			f[i][j][1]=min(f[i][j][1],max(f[i-1][j][0]+a[j].x-a[i-1].x,a[j].t));
			f[i][j][1]=min(f[i][j][1],max(f[i][j+1][1]+a[j+1].x-a[j].x,a[j].t));
		}
	int ans=0x3f3f3f3f;
	for(int i=1;i<=c;i++)
		ans=min(ans,min(f[i][i][0]+abs(b-a[i].x),f[i][i][1]+abs(b-a[i].x)));
	printf("%d",ans);
	return 0;
 } 
```

---

## 作者：JPGOJCZX (赞：0)

首先我们考虑如何处理到达给定时间后才能交作业这一限制。其实在生活中，我们一般只会考虑什么时候交作业截止 ~~（除了某些卷王）~~，这样我们只用考虑如何在最大结束时间之前交作业，而不是在所有作业都没开始交之前考虑如何转悠（前者明显比后者简单），这样我们可以先二分答案贝茜交齐所有作业的总时间，再来判断能否在这时间内从原来的终点交齐作业并最终来到原来的起点。

现在考虑如何判断是否可以在给定条件下交齐所有作业。可以知道如果有三份要交的作业 $A, B, C$，他们距离当前点的距离 $x_A < x_B < x_C$，由图：

![](https://cdn.luogu.com.cn/upload/image_hosting/va81elxa.png)


可得从起始点先到 $A$ 再到 $B$ 最后到 $C$ 一定优于从 先从起点到 $B$ 再到 $A$ 最后到 $C$，因此，如果贝茜要在这条走廊上来回交作业，那么她每次改变方向后所走的区间长度总小于上一次，而不是先走一个大区间，再走一个小区间，然后又走一个大区间。反过来，这就是一个从小区间推到大区间的过程，可以用区间 DP 做了。

考虑设 $dp_{l, r, 0/1}$ 表示交完 $l$ 到 $r$ 区间内的作业，最后停留在左端点 $l$ 的最小时间为 $dp_{l, r, 0}$，停留在右端点 $r$ 的最小时间为 $dp_{l, r, 1}$，下面分四种情况讨论：

- 现在在某个区间的左端点，要往左继续交作业。

- 现在在某个区间的右端点，要往左继续交作业。

- 现在在某个区间的左端点，要往右继续交作业。

- 现在在某个区间的右端点，要往右继续交作业。

每种情况只用考虑到达时交作业是否截止，如果没有截止就可以更新答案，因此 DP 方程为：

$$
dp_{l, r, 0} = 
\begin{cases}
dp_{l + 1, r, 0} + dis_{l + 1} - dis_l & & dp_{l + 1, r, 0} + dis_{l + 1} - dis_l \leq time_l\\
dp_{l + 1, r, 1} + dis_r - dis_l & & dp_{l + 1, r, 1} + dis_r - dis_l \leq time_l
\end{cases}
$$

$$
dp_{l, r, 1} = 
\begin{cases}
dp_{l, r - 1, 1} + dis_r - dis_{r - 1} & & dp_{l, r - 1, 1} + dis_r - dis_{r - 1} \leq time_r\\
dp_{l, r - 1, 0} + dis_r - dis_l & & dp_{l, r - 1, 0} + dis_r - dis_l \leq time_r
\end{cases}
$$

**注意：** 

1. 将时间倒序后，记得将交作业截止时间更新为总时间减去原先开始交作业的时间。

2. 记得将出发点与结束点也存为一个办公室，方便统计答案。

完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 9;
struct Homework{
	int x, t;
} h[N];
bool cmp(Homework a, Homework b){
	if(a.x == b.x)
		return a.t < b.t;
	return a.x < b.x;
}
int C, H, B;
int tmp[N];
int dp[N][N][2];
bool chk(int tim){
	for(int i = 1; i <= C; i++){
		tmp[i] = tim - h[i].t;
		if(h[i].t > tim)
			return 0;
	}
	memset(dp, 0x3f, sizeof(dp));
	dp[B][B][0] = dp[B][B][1] = 0;
	for(int len = 2; len <= C; len++)
		for(int l = 1; l + len - 1 <= C; l++){
			int r = l + len - 1;
			if(dp[l + 1][r][0] + h[l + 1].x - h[l].x <= tmp[l])
				dp[l][r][0] = min(dp[l][r][0], dp[l + 1][r][0] + h[l + 1].x - h[l].x);
			if(dp[l + 1][r][1] + h[r].x - h[l].x <= tmp[l])
				dp[l][r][0] = min(dp[l][r][0], dp[l + 1][r][1] + h[r].x - h[l].x);
			if(dp[l][r - 1][1] + h[r].x - h[r - 1].x <= tmp[r])
				dp[l][r][1] = min(dp[l][r][1], dp[l][r - 1][1] + h[r].x - h[r - 1].x);
			if(dp[l][r - 1][0] + h[r].x - h[l].x <= tmp[r])
				dp[l][r][1] = min(dp[l][r][1], dp[l][r - 1][0] + h[r].x - h[l].x);
		}
	if(dp[1][C][0] != 0x3f3f3f3f)
		return 1;
	else
		return 0;
}
int main(){
	scanf("%d%d%d", &C, &H, &B);
	for(int i = 1; i <= C; i++)
		scanf("%d%d", &h[i].x, &h[i].t);
	h[++C] = Homework{B, 0};
	++C;
	sort(h + 1, h + C + 1, cmp);
	for(int i = 1; i <= C; i++)
		if(h[i].x == B && h[i].t == 0){
			B = i;
			break;
		}
	int l = 1, r = N * N;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(chk(mid))
			r = mid - 1;
		else
			l = mid + 1;
	}
	printf("%d", r + 1);
	return 0;
}
```

---

## 作者：zhanghao233 (赞：0)

# 题目大意
数轴上有 $C$ 个点，你要在 $t \ge t_i$ 的时候，经过所有的点并且最后要回到 $B$ ，求最小消耗时间。

# 思路
显然的，我们在兜圈子。如果我们要去 $j$ ，途径 $i(i < j)$ ，要么经过的时候把 $i$ 的作业交了，要么兜圈子，回来交。

也就是我们可以用数轴上的区间 dp ，来做这道题。

很多这种 dp 都是 $f_{i,j,0/1}$ ，但是这道题要细致一点。

$f_{i,j,0/1}$ 表示 $[i,j]$ 还没有交作业，我要交 $i(0)$ 或 $j(1)$ 的作业的情况。$i,j$ 不只是表示区间，而且表示还没有交作业。

显而易见，转移方程是：

```cpp
f[i][j][0]=min(f[i][j][0],max(f[i-1][j][0]+a[i].x-a[i-1].x,a[i].t));
f[i][j][0]=min(f[i][j][0],max(f[i][j+1][1]+a[j+1].x-a[i].x,a[i].t));
f[i][j][1]=min(f[i][j][1],max(f[i][j+1][1]+a[j+1].x-a[j].x,a[j].t));
f[i][j][1]=min(f[i][j][1],max(f[i-1][j][0]+a[j].x-a[i-1].x,a[j].t)); 
```

而答案也就是**全部点都走过了消耗+到门的距离**：
```cpp
for(re int i=1;i<=n;i++)
	ans=min(ans,max(f[i][i][0],f[i][i][1])+abs(a[i].x-b));
```


注意：
- 设置边界，也就是：
$f_{1,n,0}=max(x_1,t_1),f_{1,n,1}=max(x_n,t_n)$。

- $j$ 要从大到小枚举。

---

