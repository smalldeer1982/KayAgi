# 「SWTR-5」Grid

## 题目背景

**赛时提醒：格子可以重复经过，但分数只算一次。**

## 题目描述

小 A 有一个 $n\times m$ 的网格，每个格子上都写着一个数字。为方便描述，令左上角的网格为 $(1,1)$，右下角的网格为 $(n,m)$。

小 A 可以进入最下方第 $n$ 行的任意一个网格，并按照以下规则进行游戏：

- 设小 A **第一次进入第 $i$ 行**的位置为 $(i,r_i)$：  
如果小 A 在 $(i,r_i)$，则他只能向左或向上跳。否则他可以向左，向右或向上跳。
- 小 A 不能跳出网格，除非他在第 $1$ 行，这代表结束整场游戏。

定义一局游戏的得分为所有小 A 经过的格子上的数字之和。小 A 想请你帮他求出得分的最小值。

## 说明/提示

「样例说明」

样例 $1$ 的解释如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/1l4pl5s2.png)

「数据范围与约定」

**本题采用捆绑测试。**

- Subtask 1（3 points）：$a_{i,j}\leq 0$。
- Subtask 2（12 points）：$n,m\leq 5$。
- Subtask 3（15 points）：$n=2$。
- Subtask 4（18 points）：$n,m\leq 90$。
- Subtask 5（22 points）：$n,m\leq 400$。
- Subtask 6（30 points）：无特殊限制。

对于 $100\%$ 的数据：$1\leq n,m\leq 10^3$，$-10^6 \leq a_{i,j}\leq 10^6$。

---

「题目来源」

[Sweet Round 05](https://www.luogu.com.cn/contest/28195) A。  
idea & solution：[Alex_Wei](https://www.luogu.com.cn/user/123294)。

## 样例 #1

### 输入

```
3 3
-1 -3 2
5 -1 -6
-3 7 -6```

### 输出

```
-17```

## 样例 #2

### 输入

```
3 3
1 2 3
4 5 -6
-7 8 9```

### 输出

```
-2```

## 样例 #3

### 输入

```
4 4
-1 2 -3 3
-7 -8 -9 -10
-7 20 -3 15
-8 7 0 -1```

### 输出

```
-32```

## 样例 #4

### 输入

```
17 17
536854 594409 871941 -388369 465282 -638502 -121382 -481711 -648747 583148 -407200 -756103 225750 685372 -952316 -115958 688880
-248927 927601 -41187 -729045 -902796 -714842 537911 -972691 646275 -968170 811593 -288461 -492905 954416 455549 839671 927565
317945 317920 -182592 -477 239886 747388 -323625 132984 -147642 637483 948110 750134 450272 -689049 862925 -327794 5865
196810 600825 -547716 873435 -389664 882011 -708186 504812 955352 -657431 -963785 -899423 671938 -770932 -428505 204660 -235382
592361 -686010 805643 -168792 871936 -334335 402655 783215 -315411 480760 371553 -87790 -111152 142452 918172 968088 364749
200836 914812 962142 -276470 757612 -369974 955746 -740349 -218873 976129 94337 -853562 69100 -479860 865764 -865684 -782689
-977548 -226536 197351 516125 137800 -391378 -392070 -954935 -399763 284345 -752733 195962 268045 800832 916405 578799 782717
-111876 -384522 785558 -663839 -346670 317823 -902413 -138975 794147 -377010 -370134 925156 333264 -827840 859848 773995 -335011
495949 -158831 446359 962836 -861756 936842 533809 -58318 -462176 561405 -127056 -497496 -636673 -312588 -354065 -489258 926614
603167 -154853 601062 951736 758952 -290610 838384 -455373 -823858 293098 782955 -711867 739231 -835281 -940599 938774 389756
-762794 -788479 -122327 -608246 998569 -70814 -198006 -361373 658973 -811815 -26348 240052 251877 -660298 -390790 558411 -90995
213545 492431 847902 -681087 -721770 -482897 -577178 -400679 712628 -943805 -613025 927604 867612 -753902 -235086 -60571 445511
901422 -769346 -655924 638444 188703 964292 865767 -298677 -245870 643123 -87216 -18374 -115040 -954311 -220506 919822 -183816
-576494 -481376 139875 360147 411997 437956 755645 874372 130352 -770235 -708813 850918 -835413 -426540 62763 722776 767682
-237305 -121638 -273740 518922 -423961 690214 -253799 571892 915095 586784 670083 -764317 14014 -103481 -750401 325979 70672
323842 988625 859616 920791 -749116 -660548 302396 408853 -944605 732263 -38368 223609 -484449 712951 831842 -200066 -965163
-659884 172567 -482821 -666287 42438 -113937 -539200 -57775 -558423 116068 532754 -440321 456398 -216316 293270 771477 583186
```

### 输出

```
-28761600```

# 题解

## 作者：zumgze (赞：8)

算法：动态规划

设小 A 第一次进入第 $i$ 行的位置为 $(i,r_i)$：

如果小 A 在 $(i,r_i)$，则他只能向左或向上跳。否则他可以向左，向右或向上跳。
小 A 不能跳出网格，除非他在第 $1$ 行，这代表结束整场游戏。

可知：当第一次进入某一个位置的时候只能从它的右侧或者下侧进入（若该位置为$(i,r_i)$，则只能从它的下侧进入，否则只能从它的右侧进入）

所以动态规划的递推关系已经得出：即其右侧、下侧格子得分中的小者加上本格的数字
$dp[i][j]=min(dp[i][j+1],dp[i+1][j])+a[i][j];$

下面考虑一种情况，进入某一格$a[i][j]$之后，可以先向左移动若干格，之后再回到$a[i][j]$，如果这若干个格子中的数字之和小于零，那么$dp[i][j]$就应该加上它，得到一个更优的解。

设$b[i][j]$为$a[i][j]$加上左边若干个格子中的数字之后得到的最小值（这里其实直接在 $a$ 数组上修改即可，详情见代码）
$b[i][j]=min(b[i][j-1],0)+a[i][j];$

用得到的 $b$ 数组计算 $dp$ 数组的时候，由于$b[i][j]$的值可能已经包含$b[i][j-1]$的值（即$b[i][j-1]$小于零的情况），所以特殊判断这种情况即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long dp[2000][2000];
long long a[2000][2000];
inline int read()//快速读入
{
    int x=0;
    bool f=false;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        f|=(ch=='-');
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    if(f)return -x;
    else return x;
}
int main ()
{
	//ios::sync_with_stdio(false);
	int n,m;
	n=read();
	m=read();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)a[i][j]=read();		
		dp[i][m+1]=1e10;//初值给一个比较大的数
		for(int j=1;j<=m;j++)//直接改造a数组为加上左边若干个格子中的数字之后得到的最小值
			if(a[i][j-1]<0)a[i][j]+=a[i][j-1];
	}
	for(int i=n;i>=1;i--)//从右下到左上
		for(int j=m;j>=1;j--)
			if(a[i][j]<=0)dp[i][j]=min(dp[i][j+1],dp[i+1][j]+a[i][j]);//可以滚动为dp[i]=min(dp[i],dp[i+1]+a[i][j]);
			else dp[i][j]=min(dp[i][j+1],dp[i+1][j])+a[i][j];//可以滚动为dp[i]=min(dp[i],dp[i+1])+a[i][j];
	long long ans=1e10;
	for(int j=1;j<=m;j++)ans=min(ans,dp[1][j]);//第一行，枚举最优解
	printf("%lld",ans);
    return 0;
}
```


---

## 作者：Wf_yjqd (赞：6)

额么么，某年某市某区区赛搬运了这道题。

时隔一年，回来补题。

------------

一眼动态规划。

考虑设 $f_{i,j}$ 表示从第 $i$ 行，第 $j$ 列进入下一行时的最小代价。

那么如何转移呢？

显然，进入第 $i$ 行时的列数一定是 $\ge j$ 的，这样才能到达第 $j$ 列。

考虑从刚进到第 $i$ 行的点 $k$ 跑到 $j$ 的路径上的点一定是要算代价的，而同时可以再往左跑一段后跑回来。

后者可以预处理一个以 $j$ 为终点的最小子段和，但前者难道要枚举 $k$ 吗？

显然不行，这样此题复杂度就成 $\operatorname{O}(n^3)$ 的了（虽然某区赛可以过）。

我们可以想到再维护一个以 $j$ 为起点的最小子段和，不过我们还需要处理上一行进到 $k$ 时的最小代价和，这个只用把长度为 $1$ 的子段代价加上 $f_{i-1,j}$ 即可。

于是此题复杂度 $\operatorname{O}(n^2)$。

空间上可以滚动数组，不过没必要，总体量级也没变，注释里有。

------------
寄 `long long` 的代码、、

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=1e3+84;
ll n,m,ans=0x7f7f7f7f,val[maxn][maxn],f[maxn][maxn],hzn[maxn],qzn[maxn];
int main(){
    scanf("%lld%lld",&n,&m);
    for(ll i=n;i>=1;i--)
        for(ll j=1;j<=m;j++)
            scanf("%lld",&val[i][j]);
    for(ll i=1;i<=n;i++){
        memset(hzn,0x7f,sizeof(hzn));
        memset(qzn,0x7f,sizeof(qzn));
        for(ll j=1;j<=m;j++)
            qzn[j]=min(qzn[j-1],0ll)+val[i][j];
        for(ll j=m;j>=1;j--)
            hzn[j]=min(hzn[j+1],f[i-1][j])+val[i][j];
            // hzn[j]=min(hzn[j+1],f[j])+val[i][j];滚动数组
        for(ll j=1;j<=m;j++)
            f[i][j]=min(hzn[j]+qzn[j]-val[i][j],hzn[j]);
            // f[j]=min(hzn[j]+qzn[j]-val[i][j],hzn[j]);滚动数组
        //     printf("%lld %lld %lld %lld %lld Sherry\n",i,j,hzn[j],qzn[j],val[i][j]);
        // }
    }
    for(ll i=1;i<=m;i++)
        ans=min(ans,f[n][i]);
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：Miraik (赞：4)

来一发和其他题解略微不同的思路。

把题目转化一下，就变成了：

有 $n$ 行数，每行有 $m$ 个，每一行都取一段长度不为 $0$ 连续的数，但结束位置的下标一定大于等于上一行的结束位置下标，求最终取得的数之和最小是多少。

$DP$ 的过程很显然，与我们熟悉的过河卒差不多，设 $f_{ij}$ 为取到第 $i$ 行，该行以 $j$ 作为结尾下标可获得的最小分数。状态转移方程：

$f_{i,j}=\min(f_{i,j-1}+a_{i,j} , f_{i-1,j}+s_{i,j}-m_{i,j-1})$

初始化 $f_{i,0}=\infty$。

其中 $s_{i,j}$ 表示第从 $a_{i,1}$ 到 $a_{i,j}$ 之和，即第 $i$ 行的前缀和。

$m_{i,j}$ 则表示 $s_{i,1}$ 到 $s_{i,j}$ 中的最大值，因此 $s_{i,j}-m_{i,j-1}$ 即为第 $i$ 行以 $j$ 为结尾下标可获得的最小分值。

$m$ 与 $s$ 可以边做边求。

注意到 $f_{i,j}$ 的值只与 $f_{i,j-1}$ 和 $f_{i-1,j}$ 有关，可以将第一维压掉。

记得开 ```long long``` ！

完整代码（压行勿怪）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;long long sum,res,x,ans=1ll<<60,f[1005]={1ll<<60};
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++,sum=res=0)//sum为前缀和(s[i][j])，res为之前前缀和中的最大值(m[i][j-1])
	    for(int j=1;j<=m;j++)
	    	scanf("%lld",&x),sum+=x,f[j]=min(f[j-1]+x,f[j]+sum-res),res=max(sum,res);
	for(int i=1;i<=m;i++)ans=min(ans,f[i]);//最后不一定取完f[n][n]，所以在f[n][i]中取最小分数 
	return printf("%lld\n",ans),0;
}

```



---

## 作者：ssfx2019s005 (赞：2)

思路：动态规划

我们可以发现，当不需要考虑向右走时，这道题就与[数字三角形](https://www.luogu.com.cn/problem/P1216)就是一样的。因此，可以得出只向左或向上走的转移方程：
$$
f[i][j]=\min(f[i][j+1],f[i+1][j])+g[i][j]
$$
再进一步考虑。首先假设小A首次进入第 $i$ 行在 $(i,r_i)$ 的位置上，那么该点左边所有点以及该点本身都是可达的。如果存在这样一个点使得从 $(i,r_i)$ 到这个点之间所有格子上的数和为负数，那么就可以让答案更小。

因此，在输入 $g[i][j]$ 之后，我们可以通过类似前缀和的方式改变 $g[i][j]$ 的含义，让它代表从 $(i,j)$ 向左走再返回来能让答案减少的值（如果不能向左走不能减少则值不变）。

这样，在矩阵中先向左走在折返这样的操作就可以转化成向左走。

code：
```
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
int n,m;
const int N=1015;
int g[N][N];
int f[N][N];
int qz[N][N];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>g[i][j];    
		}
		f[i][m+1]=f[i][0]=1e18;
	} 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(g[i][j-1]<0)
				g[i][j]+=g[i][j-1];
	for(int i=n;i;i--){
		for(int j=m;j;j--){
			if(g[i][j]>0){
				f[i][j]=min(f[i][j+1],f[i+1][j])+g[i][j];
			}
			else{
				f[i][j]=min(f[i][j+1],f[i+1][j]+g[i][j]);
			}
		}
	}
	int minn=1e18+7;
	for(int j=1;j<=m;j++)
		minn=min(minn,f[1][j]);
	cout<<minn<<endl;
	return 0;
}
```

---

## 作者：do_while_true (赞：2)

提供一个 $\mathcal{O}(nm\log m)$ 的做法。

题目转换一下，可以理解为从 $(1,1)$ 走到 $(n,m)$ ，每次走到一行的时候可以在前面多取一段连着的和的最小值。

把原矩阵全部取反就是最大值。

这样子转化问题就很明显了，就是一个经典问题：

求一个矩阵，只能向右向下走，求第一行走到最后一行的最大值，也就是设 $f[i][j]$ 为走到 $(i,j)$ 的最大值。

为 $f[i][j]=\max\{f[i][j-1]+a[i][j],f[i-1][j]+a[i][j]\}$ 加上了一个可以在前面多选一个以 $j$ 为结尾的区间和的问题。

从 $f[i][j-1]$ 转移过来就不需要再找前面一个在第 $i$ 行以 $j-1$ 为结尾的最大区间和了，因为 $f[i][j-1]$ 已经计算了以 $j-1$ 为结尾的最大区间和。

而对于从 $(i-1,j)$ 转移而来，需要求一个在第 $i$ 行以 $j$ 为结尾的最大区间和，可以利用前缀和，把前 $j-1$ 所有前缀和放进小根堆里面，取堆顶即可。因为区间和 $sum[j]-sum[k-1]$ 最大，需要 $sum[k-1]$ 最小（$sum[j]$ 代表第 $i$ 行以 $j$ 为结尾的前缀和，已经确定了）。

对以上两种情况分类取最大值即可。

PS: 可能人傻描述麻烦，可以理解为那个经典问题带一个可以加上一个区间和的转移，求这个值用堆贪心即可。

因为有个堆，时间复杂度 $\mathcal{O}(nm\log m)$（貌似被其他更优做法吊打了）

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#define ll long long
const int N = 1010;
inline ll Max(ll x, ll y) { return x > y ? x : y; }
inline ll Min(ll x, ll y) { return x < y ? x : y; }
inline ll read() {
	ll r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') w = 1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		r = (r << 3) + (r << 1) + (ch ^ 48);
		ch = getchar();
	}
	return w ? ~r + 1 : r;
}
int n, m;
ll a[N][N], f[N][N], sum, ans = -0x7fffffffffffffff;
std::priority_queue<ll>q;
int main() {
	n = read(); m = read();
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			a[i][j] = -read();
	for(int i = 1; i <= m; ++i) f[1][i] = Max(f[1][i - 1] + a[1][i], a[1][i]);
	for(int i = 2; i <= n; ++i) {
		while(!q.empty()) q.pop();
		q.push(- (sum = a[i][1]));
		q.push(0);
		f[i][1] = f[i - 1][1] + a[i][1];
		for(int j = 2; j <= m; ++j) {
			sum += a[i][j];
			f[i][j] = Max(f[i][j - 1] + a[i][j], f[i - 1][j] + sum + q.top());
			q.push(-sum);
		}
	}
	for(int i = 1; i <= m; ++i) ans = Max(ans, f[n][i]);
	printf("%lld\n", -ans);
	return 0;
}
```

---

## 作者：yewanxingkong (赞：2)

观前提示：不开 $long long$ 见祖宗。
# **题目分析**
题目看起来花里胡哨的，很麻烦。

但是你仔细分析一下就会发现这其实和一个图你只能向上或向左走一样，不过你要再加一个 $dp$ 来判断这个点往左走再回来会不会值更小。

# **代码细节**
一开始在记录数据的时候开一个数组记录这个点在可以往左走的情况下的最小值。

转移方程是 $d[i][j]=min(a[i][j],a[i][j]+d[i][j-1])$

然后就是判断这个点可以从右到还是从下到的转移方程。因为要加上之前那个 $dp$ 的值，所以转移方程我用了两个数组，一个记录最终值，一个记录不加那个 $dp$ 的值。

转移方程是

$b[i][j]=min(c[i+1][j],b[i][j+1])+a[i][j]$
$c[i][j]=b[i][j]+min((long long)0,d[i][j-1])$

下面是代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
using namespace std;
long long n,m,a[2010][2010],b[2010][2010],c[2010][2010],chu=1e10,d[2010][2010];
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
int main(){
	n=read();
	m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			a[i][j]=read();
		for(int j=1;j<=m;j++)
			d[i][j]=min(a[i][j],a[i][j]+d[i][j-1]);
	}
	for(int i=1;i<=n;i++)
		b[i][m+1]=1e10;
	for(int i=n;i>=1;i--)
		for(int j=m;j>=1;j--){
			b[i][j]=min(c[i+1][j],b[i][j+1])+a[i][j];
			c[i][j]=b[i][j]+min((long long)0,d[i][j-1]);
		}
	for(int i=1;i<=m;i++)
		chu=min(chu,c[1][i]);
	cout<<chu;
	return 0;
}
```


---

## 作者：yanbinmu (赞：1)

# 分析
很显然一道 dp 题。

**分两种情况**：
1. 格子的数小于 0，那么就考虑是从下方还是右侧过来
1. 格子的数大于 0，那么考虑走或不走

**因此可得两种状态转移方程：**

1. $a_{i, j} > 0$ $f_{i, j} = \min(f_{i + 1, j}, f_{i, j + 1} + a_{i, j})$
2. $a_{i, j} < 0$ $f_{i,j} = \min(f_{i + 1, j} + a_{i, j}, f_{i, j + 1})$

# AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long f[1005][1005], a[1005][1005], c[1005][1005];
int main()
{	
	long long n,m;
	cin >> n >> m;
	for(int i = 1;i <= n;i ++ ){
		f[i][m+1] = 1e10+1;//处理数据
	}
	for(int i = 1;i <= n;i ++ ){
		for(int j = 1;j <= m;j ++ ){
			cin >> a[i][j];
			a[i][j] = min(a[i][j], a[i][j] + a[i][j - 1]);//处理输入的数据，可以减少dp循环次数，把左侧的加上（判断取加或不加的小值）
		}
	}	
	
	for(int i = n;i >= 1;i -- ){
		for(int j = m;j >= 1;j -- ){
			if(a[i][j] > 0) f[i][j] = min(f[i + 1][j],f[i][j + 1]) + a[i][j];//判断格子对应的数
			else f[i][j] = min(f[i + 1][j] + a[i][j],f[i][j + 1]);
		}
	}
	long long ans = 1e10 + 1;
	for(int i = 1;i <= m;i ++ ){
		ans = min(ans, f[1][i]);//过一遍数组，找到最小值
	}
	cout << ans;
	return 0;
}
```
****
### **提示：一定开 long long，不开见祖宗。**

---

## 作者：_Only_this (赞：1)


### P6649 「SWTR-05」Grid

------------


给你一个矩阵，从最后一行开始走，到了每一行第一个到的点时只能向左或者向上走，否则就可以向左向右向上走，最终走到第一行结束，求经过所有格子的最小值。

题意很好理解，一眼动归。

动态规划题最重要的一步就是设置状态，

设置 $f_{i,j}$ 为从第 $i$ 行，第 $j$ 列进入下一行时的最小值。

接下来考虑转移，

显然，第 $i$ 行 $j$ 列一定是由上一行列数为 $\geq j$ 的位置转移而来的，

所以我们要再枚举一个 $k$，$j\leq k\leq m$，用于转移。

至于如何处理往左跑一段后又跑回来的这种情况，

可以用一个最小字段和的结构来处理。

但是，

这样写的时间复杂度为 $O(n^3)$，实在是满足不了我们时限1s的要求。

因此，

可以再用一个最小字段和来处理转移时枚举 $k$ 的过程

这样就成功优化掉了一个 $n$，时间复杂度为 $O(n^2)$，符合时限。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn = 1e3+5;
const ll inf = 3e18;
ll n,m,ans=inf;
ll a[maxn][maxn],dp[maxn][maxn],qz[maxn],hz[maxn];
int main(){
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++)
			scanf("%lld",&a[i][j]);
	for(ll i=n;i>=1;i--){
		memset(qz,0x3f,sizeof qz);
		memset(hz,0x3f,sizeof hz);
		for(ll j=1;j<=m;j++)
			qz[j]=min(0ll,qz[j-1])+a[i][j];
		for(ll j=m;j>=1;j--)
			hz[j]=min(hz[j+1],dp[i+1][j])+a[i][j];
		for(ll j=1;j<=m;j++)
			dp[i][j]=min(qz[j]+hz[j]-a[i][j],hz[j]);
	}
	for(ll i=1;i<=m;i++)
		ans=min(ans,dp[1][i]);
	printf("%lld",ans);
	return 0;
}
```

完结，散花(～￣▽￣)～ 


---

## 作者：Kalium (赞：1)

# P6649 「SWTR-05」Grid题解

## 题意：

在矩阵中，到了每一行第一个到的点时只能向左或者向上走，否则可以向右向左向上走，求经过所有格子的最小值。

## 思路：

这一眼看上去就很 dp 好吧。

我们可以使用前缀和，将第 i 行中，前 j 个数小于零时加上当前这个数，记作       $sum_{i,j}$。

然后在 dp 时，可以判断，当当前这个格子，若在该行前面的所有数的和小于零，便可以向左转且移加上这行的数的和，或者直接向上走。

否则边可以选择向左走且加上这行数字的价值，或者直接向上走。

方程：

$dp_{i, j} = \min(dp_{i + 1,j}, dp_{i, j + 1}) + sum_{i, j} (sum_{i, j} > 0)$。

$dp_{i, j} = \min(dp_{i + 1, j} + sum_{i, j}, dp_{i, j + 1}) (sum_{i, j} < 0)$。

## 细节：

注意开 long long。

## 代码：

```cpp
#include <iostream>
#include <cstdio>

#define inf 1e18
#define ll long long

const int N = 1e3 + 7;

using namespace std;

int n, m;

ll a[N][N];

ll sum[N][N];

ll dp[N][N];

ll ans = inf;

inline ll mina(ll a, ll b) {
	if (a < b)
		return a;
	return b;
}

int main() {
	scanf("%d %d", &n, &m);
	
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) 
			scanf("%lld", &a[i][j]);
	}
	
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++)
			sum[i][j] = mina(sum[i][j - 1], 0) + a[i][j];
	}
	
	for (int i = 1; i <= n; i ++) dp[i][m + 1] = inf;
	
	for (int i = n; i >= 1; i --) {
		for (int j = m; j >= 1; j --) {
			if (sum[i][j] > 0)
				dp[i][j] = mina(dp[i + 1][j], dp[i][j + 1]) + sum[i][j];
			else
				dp[i][j] = mina(dp[i + 1][j] + sum[i][j], dp[i][j + 1]);
		}
	}
	
	for (int i = 1; i <= m; i ++)
		ans = mina(dp[1][i], ans);
	
	printf("%lld\n", ans);
	
	return 0;
}
```

---

## 作者：caohan (赞：0)

# 思路

本题动规特征过于明显。

设有一动规数组为 $f_{n,m}$ 且原地图为 $a_{n,m}$ 时：

可以发现，此时若将答案寄存于 $f_{1,1}$ 的话，即是 $f_{i,j}$ 为从第 $n$ 行出发，到达 $(i,j)$ 的最小和，答案定然与起点的状态有关，这不符合动规的基本原则。

所以更改定义，终点不行起点行，即是 $f_{i,j}$ 为从第 $(i,j)$ 出发，到达 $(1,1)$ 的最小和。这就没有了不确定性问题。

此时考虑有多少种状态：
第一种带上当前方格的 $a_{i,j}$ 直接向左，加入 $f_{i,j-1}$.

而第二种则是在向左行走了一些格（可以不走）后，再尽力后退到第一次来的地方，再加入 $f_{i-1,j}$.

比较这两种方法的优劣即可。

但是有个小问题，就是如果此时第二种情况认为不论向左走多少，都是不优的，不要忘了给这种小情况加上初始值。

# 注意：

- 本题的数据量奇大，打开快读，使用 long long 进行存储。

# 代码


```cpp
#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
#define ll long long
ll n,m;
ll val[1005][1005];
ll f[1005][1005];//以i，j为起点，向第一行走，能够得到的最小值；
ll s[1005][1005];
ll smax[1005][1005];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>val[i][j];
			s[i][j]=s[i][j-1]+val[i][j];
			smax[i][j]=max(smax[i][j-1],s[i][j]);
		}
	}
	for(int i=1;i<=n;i++)
	{
		f[i][0]=INT64_MAX-(ll)1e12;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			f[i][j]=min(f[i][j-1]+val[i][j],f[i-1][j]+s[i][j-1]-smax[i][j-1]+val[i][j]);
		}
	}
	ll ans=INT64_MAX;
	for(int j=1;j<=m;j++)
	{
		ans=min(ans,f[n][j]);
	}
	cout<<ans;
	/*cout<<"\n\n\n\n\n\n\n\n";
	for(int i=1;i<=n;i++)
	{6
		for(int j=1;j<=m;j++)
		{
			cout<<f[i][j]<<" ";
		}
		cout<<"\n";
	}*/
	return 0;
}
```




---

