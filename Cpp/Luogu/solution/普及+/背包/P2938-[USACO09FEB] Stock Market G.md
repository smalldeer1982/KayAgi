# [USACO09FEB] Stock Market G

## 题目描述

尽管奶牛天生谨慎，它们仍然在住房抵押信贷市场中大受打击，现在它们准备在股市上碰碰运气。贝西有内部消息，她知道 $S$ 只股票在今后 $D$ 天内的价格。

假设在一开始，她筹集了 $M$ 元钱，那么她该怎样操作才能赚到最多的钱呢？贝西在每天可以买卖多只股票，也可以多次买卖同一只股票，交易单位必须是整数，数量不限。举一个牛市的例子：

假设贝西有 $10$ 元本金，股票价格如下：

|  股票 | 今天的价格 | 明天的价格 | 后天的价格 |
| :-: | :---: | :---: | :---: |
| $A$ |   $10$  |   $15$  |   $15$  |
| $B$ |   $13$  |   $11$  |   $20$  |

最赚钱的做法是：今天买入 $A$ 股 $1$ 张，到明天把它卖掉并且买入 $B$ 股 $1$ 张，在后天卖掉 $B$ 股，这样贝西就有 $24$ 元了。

## 样例 #1

### 输入

```
2 3 10 
10 15 15 
13 11 20 
```

### 输出

```
24 
```

# 题解

## 作者：ShineEternal (赞：39)

# 题意简述：

给定⼀个$D$天的$S$只股票价格矩阵，以及初始资⾦ $M$；每次买股票只能买某个股票价格的整数倍，可以不花钱，约定获利不超过$500000$。最⼤化你的 总获利。

# 题目分析：

首先我们要知道此题的详细意图：每天都可以用你手中有的钱买入股票，数量不限，也可以卖出你自己的股票，所得的收益或价值已经在$D*S$的矩阵中给出。要求在最后一天结束后得到的钱最多。

# 题解：
其实我们可以发现：对于每一天只要最大化你的收益就可以达成目的。然后问题就转换为求每一天的股票交易情况了。又知道每个股票可以无限量的购买（当然价值和不多于手中的钱），显然，就是一个完全背包。

### 其实题目中的获利不超过500000已经暗中提示了DP等算法的使用，因为给出一个不是由int到long long 的数据范围的改变一定是为数组内存准备的。

接下来就不再赘述了，其他部分会在代码中注明，看

# [代码](https://blog.csdn.net/kkkksc03/article/details/83000551)

PS:尽量最后再看


---

## 作者：傅思维666 (赞：31)

## 题解：

[博客食用口味更佳](https://www.cnblogs.com/fusiwei/p/11609733.html)

一道怪异的背包问题。

首先，我们能明确一点，就是DP的决策：

在第$i$天，有这么几种决策方式：

第一种：不买。

第二种：买完第二天卖。

第三种：买完在手中存几天后再卖。

但是第三种决策完全可以转化成第二种决策，原理是这样的：

对于一只股票，我们在第$i$天买第$j$天卖，其效果可以被看为在第$i$天买，第$k$天卖（$i\le k\le j$），当天再买回来，第$j$天卖。

这样的话，我们的第三种决策就可以变成：买完第二天卖，第二天再买回来。这就解决了DP的无后效性的问题。我们就可以开始设计DP过程了。

根据上面的分析，我们发现买股票变成了相邻两天的事情。那么，每一天对于每种物品只有两种选择：买还是不买。

诶？好像完全背包欸！

那么，对于每一天，我们都做一次完全背包：这个背包的体积就是当前的资金，每个物品的体积是当天的价值，价值为当天的价值减去前一天的价值。

所以我们可以跑$d-1$次完全背包，选出答案最大的一次。



代码如下：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int s,d,m,maxx;
int map[60][20],dp[500001];
int main()
{
	scanf("%d%d%d",&s,&d,&m);
	for(int i=1;i<=s;i++)
		for(int j=1;j<=d;j++)
			scanf("%d",&map[i][j]);
	for(int i=2;i<=d;i++)
	{
		maxx=-1;
		memset(dp,0,sizeof(dp));
		for(int j=1;j<=s;j++)
			for(int k=map[j][i-1];k<=m;k++)
			{
				dp[k]=max(dp[k],dp[k-map[j][i-1]]+map[j][i]-map[j][i-1]);
				maxx=max(maxx,dp[k]);
			}
		m+=maxx;
	}
	printf("%d",m);
	return 0;
}
```



---

## 作者：A_Đark_Horcrux (赞：9)

update on 2019.11.26：变量名写反，fixed

update on 2019.11.20：更好的代码注释

~~论一个CSP-J选手在洛谷看到了考试题的心情~~

[P5662 纪念品](https://www.luogu.org/problem/P5662)

咳咳，进入正题。

买东西：考虑背包；

每天可以进行无数次操作：考虑完全背包。

~~你这些都想到了考场上怎么就不会写呢XD~~

在同一天，对于一种股票，有买和不买两种选择；买又分为买完一天后卖，两天后卖……

但其实我们不用把每一天的情况算过去。对于买完后x天卖出，__相当于在中间的x-1天里，买下任意量的某种股票再全部卖掉__，至于要不要买，可以在DP过程中判断。这样 __买股票就变成了相邻两天间的事情__ 只要我们一天一天DP过去，就可以解决这个问题。

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int max(int x,int y) {return x>y?x:y;}
int t,n,m,maxx=-1,i,j,k,a[101][51],f[1000010];//分别问天数，股票种类数，钱数，统计用的maxx，循环用的变量，记录股票数据的数组，dp用的数组
int main()
{
	
	scanf("%d %d %d",&n,&t,&m);
	for(i=1;i<=n;i++)
		for(j=1;j<=t;j++)
			scanf("%d",&a[i][j]);//输入
	for(k=2;k<=t;k++)//对于每一种股票
	{
		maxx=-1;//T天能获得的最大价值
		for(i=1;i<=n;i++)//完全背包的套路，i从1~t，在传统的背包问题里代表物品数
			for(j=a[i][k-1];j<=m;j++)//j从a[i][k-1]，也就是前一天的股票交易价格，到m，在传统的背包问题中代表体力或容量
			{
				f[j]=max(f[j],f[j-a[i][k-1]]+a[i][k]-a[i][k-1]);//f[j]表示不买，f[j-a[i][k-1]]+a[i][k]-a[i][k-1]表示买，等于昨天如果没买所剩下的钱，减去昨天买入用的钱，再加上今天买入用的钱
				maxx=max(f[j],maxx);//一边算一边取max
			}
		m+=maxx; memset(f,0,sizeof(f));//加上maxx，f数组清0
	}
	printf("%d",m);//输出m
	return 0;
}//结束awa
```

---

## 作者：fy0123 (赞：8)

假设每天买完第二天就卖掉，如果第二天不卖掉可以看成是第二天卖掉再买入。这样就把问题转化成了完全背包问题。一天一天DP即可。

另外，几个注意点，一是数组大小不要开错，二是此题卡常，建议到**大牛分站**提交。

放一下大牛分站AC代码：

```cpp
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
using namespace std;

const int N = 15, M = 55, MAX = 500010;
int n, m, limit;
int a[M][N], f[MAX];

inline int read()
{
    char ch = getchar(); int x = 0, flag = 0;
    while (!isdigit(ch)){ if (ch == '-') flag = 1; ch = getchar(); }
    while (isdigit(ch)){ x = x * 10 + ch - '0'; ch = getchar(); }
    return flag ? -x : x;
}

int main()
{
    n = read(), m = read(), limit = read();
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= m; j ++) a[i][j] = read();
    for (int i = 2; i <= m; i ++){
        int Max = 0;
        memset(f, 0, sizeof f);
        for (int j = 1; j <= n; j ++)
            for (int k = a[j][i-1]; k <= limit; k ++){
                f[k] = max(f[k], f[k-a[j][i-1]]+a[j][i]-a[j][i-1]);
                Max = max(Max, f[k]);
            }
        limit += Max;
    }
    printf("%d\n", limit);
    return 0;
}
```

---

## 作者：asdfghjkl123 (赞：7)

如果看透了，算是比较友好的完全背包吧……每天买了再卖出。

我觉得我时间已经比较优秀了……然而还是没有A,加了O2以后A了……如果有朋友有兴趣加一下快读什么的优化的话欢迎粘代码回去……

dp存的是第i天的利润，然后每天结束时更新当前自己有的成本。输出最后一天的成本，因为最后一天不会入手股票。

贴代码：
```
#include<bits/stdc++.h>
using namespace std;
int s,d,m,maps[60][20],dp[1000100],mmx,val;
int maxx(int a,int b)
{
	return a<b?b:a;
}
int main()
{
//	freopen("testdata(1).in","r",stdin);
	scanf("%d%d%d",&s,&d,&m);
	for(int i=1;i<=s;i++)
		for(int j=1;j<=d;j++)
			scanf("%d",&maps[i][j]);
	for(int day=1;day<d;day++)
	{
		mmx=-1;
		memset(dp,0,sizeof(dp));
		for(int sor=1;sor<=s;sor++)
		{
			val=maps[sor][day+1]-maps[sor][day];
			if(val<=0)continue;
			for(int k=maps[sor][day];k<=m;k++)
			{
				dp[k]=maxx(dp[k],dp[k-maps[sor][day]]+val);
//				mmx=maxx(mmx,dp[k]);
			}
		}
		for(int k=0;k<=m;k++)mmx=maxx(mmx,dp[k]);
		m+=mmx;
	}
	printf("%d",m);
	return 0;
}
```

由于代码在O2AC后多次再版，可能代码中会出现少许纰漏，~~正好作为放抄袭标志……~~希望包涵。

---

## 作者：inoichi_lim (赞：5)

### 这题是[这题](https://www.luogu.com.cn/problem/P5662)的加强版。
- 但是，这题和上题却有细节上的不同：输入格式不同。P5662 是**先$t$后$n$**，而此题正好相反。
- 注：$t,n,m$等变量以 P5662 为准。
### 然后，我们发现，我们假设$f_{k}$为有$k$个金币的
$\color{red}\texttt{最大利润}$。
- 然后……就是一个完全背包啦qwq
- 可是方程似乎还是不好确定。
### 所以，我们简化操作：从
```
持有一个物品
卖一个物品
买一个物品
（共3个）
```
### 变成
```
先卖后买=持有一个物品
卖一个物品
买一个物品
（共2个）
```
### 那么，我们设第$i$天第$j$个物品的重量为$a_{j,i-1}$（注意不要搞反），价值为$a_{j,i}$。
所以，就可以对每天**分别**做完全背包了。

$code:$
```cpp
#include<bits/stdc++.h>
#define ns "-1"
#define fs(i,x,y,z) for(ll i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(ll i=x;i>=y;i+=z)
#define ll long long
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
using namespace std;
const int N=1000001,inf=0x7f7f7f7f;
int n,a[N][101],f[N],m,t;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);
    cin>>n>>t>>m;
    if(t==1){
    	cout<<m;
    	return 0;
	}
	fs(i,1,n,1){
		fs(j,1,t,1){
			cin>>a[i][j];
		}
	}
	fs(i,2,t,1){
		ms(f,0);//因为每天是独立的，所以在这里要清空f
		int maxx=-1;//用max会CE
		fs(j,1,n,1){
			fs(k,a[j][i-1],m,1){//完全背包
				f[k]=max(f[k],f[k-a[j][i-1]]+a[j][i]-a[j][i-1]);
           //难点：完全背包的转移
           //f[k-a[j][i-1]]就是目前可用重量-目前物品重量
           //+a[j][i]就是加上目前物品利润
				maxx=max(maxx,f[k]);
           //更新max值（最大利润）
			}
		}
		m+=maxx;//加上利润
	}
	cout<<m;
	return 0;
}
```
- 最后要说一句：#4测试点**不开O2`2.2s`，开了O2`0.034s`……**

---

## 作者：hater (赞：5)

应该算是最暴力的解法了 

考场上倒数三分钟调了出来 （大汗）

（因为是考场解法 不喜勿喷）

枚举两个交易的时间 再用完全背包做

看到题解才发现有 n^3 的解法 

不过这个 n^3*max(钱数）的解法吸口氧还是过了

没有吸氧 85分 

Th[i] 存储的是i天所能得到最大的钱数 

其他没什么问题了 这个思路没有太大的难度 

```cpp
#include <bits/stdc++.h> 
#define MAX 1005
#define R register
using namespace std ;
int S , D , M , Map[MAX][MAX] ; 
int f[500005] , V[MAX] , W[MAX] , Ans , Tot , len ; 
int Th[MAX] ; 
int main() 
{
	cin >> S >> D >> M ;
	Th[1] = Th[0] = M ;
	for(R int i=1; i<=S; i++)
	  for(R int j=1; j<=D; j++)
	    cin >> Map[i][j] ; 
	for(R int St=1; St<D; St++)
	 for(R int En=St+1; En<=D; En++)
	  {
	  	memset( f , 0 , sizeof(f) ) ;
	  	memset( V , 0 , sizeof(V) ) ;
	  	memset( W , 0 , sizeof(W) ) ;
	  	Ans = len = 0;
	  	for(R int i=1; i<=S; i++)
	  	if( Map[i][St] < Map[i][En] ) 
	  	{
	  		W[++len] = Map[i][St] ;
	  		V[len] = Map[i][En] ;
		}
		for(R int i=1; i<=len; i++)
		 for(R int j=0; j<=Th[St]; j++)
		  if( j-W[i] >= 0 ) f[j] = max( f[j] , f[j-W[i]]+V[i] ) ;
		for(R int i=0; i<=Th[St]; i++)
		 Ans = max( Ans , f[i]+Th[St]-i ) ;
		Th[En] = max( Th[En] , Ans ) ;
		Tot = max( Tot , Ans ) ;
	  }
	cout << Tot << endl; 
	return 0 ;
} 
```



---

## 作者：Warriors_Cat (赞：3)

$CSP-J$的一道原题……

我们先来分析一下题目。

比如，我们看第一天和第二天，对于一种股票$X$，他第一天要么买，要么不买；如果买的话，第二天他要么卖，要么不卖。如果不卖的话，我们可以把它当作第一和第二天之间卖掉，第二天和第三天又买进来，这样子就可以处理第三天的买卖情况了。

因为每个股票可以买无穷多个，于是这道题就变成了一个完全背包问题：

有一个背包，容量为$V$。有$n$个物品，每个物品的容积为$p[k][i]$，价值为$p[k + 1][i]-p[k][i]$，问价值最大是多少？

做$D-1$次完全背包即可

于是就上$Code$啦：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int p[110][110], t, n, m, dp[500010];
int dfs(int k, int V){
	if(k == t) return V;
	memset(dp, 0, sizeof(dp));
	for(int i = 1; i <= n; ++i){
		for(int j = p[k][i]; j <= V; ++j){
			dp[j] = max(dp[j], dp[j - p[k][i]] + p[k + 1][i] - p[k][i]);//完全背包模板
		}
	}
	return dfs(k + 1, V + dp[V]);
}
int main(){
	scanf("%d%d%d", &n, &t, &m);
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= t; ++j){
			scanf("%d", &p[j][i]);
		}
	}
	printf("%d", dfs(1, m));
	return 0;
}
```

~~今年真的比去年水了好几倍QAQ~~

$CSP2019$已经过去了，祝大家$CSP2020.rp++$.

## End

---

## 作者：年华当诗酒 (赞：3)

### 虽说2019CSP已永远离我们远去，但我们仍能得到新知识


~~写的太迟了，见谅~~。

如果你认真的读完题，我相信你会发现，这道题似曾相识。

~[见本题](https://www.luogu.com.cn/problem/P2938)

**没错，这是2019CSP入门的第3题，一模一样。**

[ Double Experience ！](https://www.luogu.com.cn/problem/P5662)

~~略有不同，在输入部分（逃~~

好，你现在应该知道这题是一道完全背包题，那为什么呢?

**首先，题目直接给出了背包容量，即小伟手上有的钱，当然在小伟不断买卖的过程中，它是会变的，并且，小伟当天能无限制的买入，卖出，这也就说明它是完全背包。**

完全背包大家应该都学过，这里不进行赘述。

阶段，就是完全背包的，即小伟手上有的钱数，那来看决策吧。

```
	for (int i = 1; i <= m; i ++)
	   	for (int j = w[i]; j <= t; j ++)
			f[j] = max(f[j], f[j - w[i]] + c[i]);
```

这是普通的完全背包的决策，

但很显然，题目没有直接给出，第i个物品的体积和价值。

**仔细读题，不难发现，当前物品的体积是上一天的价格，而其价值是两天，不一定是相邻两天的价格。**

~~没有中间商赚差价（逃~~

**说实话，动态转移方程已经明了，**

	f[j] = max(f[j], f[j - a[k][i]] + a[k + 1][i] - a[k][i]);
    
a[k][i] 数组用来表示第 k 天，第 i 件物品的价值，

但事实上，输入的却是，第 k 件物品，第 i 天的价值，

所以，这就要求我们，输入时注意一下。



------------
# 附上完整代码

```
#include<bits/stdc++.h>
using namespace std;
int const N=150;
int const M=500050;
int t, n, m;
int a[N][N];
int f[M];

int main()
{
	cin >> n >> t >> m;
	for (int i = 1;i <= n;i ++)
		for ( int j = 1;j <= t;j ++)
			cin >> a[j][i];
	for (int k = 1; k <= t;k ++)
	{
		memset(f, 0, sizeof(f));
		for (int i = 1;i <= n;i ++)
			for (int j = a[k][i];j <= m ;j ++)
				f[j] = max(f[j], f[j - a[k][i]] + a[k + 1][i] - a[k][i]);
		m = max(f[m] + m, m);
	}	
	cout << m;
	return 0;
}
```
## 注意细节：

**cin 部分，**

**memset 的意义不用过多赘述，**

**之前的叙述里已经提到过了，我们的背包容量不是一成不变的，所以，你懂得。**


~~话说一模一样的题难度是不一样的，有点小奇怪（逃~~

---

## 作者：0x3F (赞：2)

其实和[纪念品](https://www.luogu.com.cn/problem/P5662)是一样的，我的代码是复制过来的。

首先是一个思想：你想第一天就买进，等到最后一天就卖出，相当于你第一天买了，第二天立即卖出，然后再买回来，第三天再立即卖出，以此类推，等到最后一天再买回来，再卖出。

所以每一天可以独立决策。

那每一天都要做哪些决策呢？

买进任意一只股票任意张，然后明天必须卖掉并赚取差价。

用完全背包即可。

DP 方程如下。

$$dp_{i, j, k} = \max\{dp_{i, j-1, k-price_{i, j}}+price_{i+1,j}-price_{i, j} \}$$

其中表示第 $i$ 天，考虑到第 $j$ 个物品，手中持有 $k$ 元现金时明天最多可以得到的钱。

要把 $i$ 和 $j$ 两个维度压掉，只保留 $k$ 这一个维度，即手持的现金数量。

最后注意了：本题和[纪念品](https://www.luogu.com.cn/problem/P5662)的区别有：

1. 数据范围不同。

2. 输入顺序不同。

3. 没了！！！

上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int T, N, M;
int ans;
int dp[500010], p[15][55];

int main() {
	cin >> N >> T >> M;
	for (int j = 1; j <= N; j++) {
		for (int i = 1; i <= T; i++) {
			cin >> p[i][j];
		}
	}
	for (int i = 1; i <= T; i++) {
		memset(dp, 0, sizeof(dp));
		ans = 0;
		dp[M] = M;
		for (int j = 1; j <= N; j++) {
			for (int k = M; k >= p[i][j]; k--) {
				dp[k - p[i][j]] = max(dp[k - p[i][j]], dp[k] + p[i + 1][j] - p[i][j]);
			}
		}
		for (int k = 0; k <= M; k++) ans = max(ans, dp[k]);
		M = ans;
	}
	cout << M << endl;
	return 0;
}

```

---

## 作者：Zhou_Wingay (赞：0)

思路：我们把每相邻两天看成一个完全背包，那么：

 1. 现在拥有的钱为背包容量。
 2. 今天的价格为价格。
 3. 明天的价格为价值。

所以，我们只需进行$d-1$次完全背包即可。

最后就是代码了：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
int a[105][105],dp[500005];
int main(){
	int i,j,k;
	cin>>n>>t>>m;
	for(i=1;i<=n;i++){
		for(j=1;j<=t;j++){
			cin>>a[i][j];//输入每天的价格
		}
	}
	for(i=1;i<t;i++){
		memset(dp,0,sizeof(dp));
		for(j=1;j<=n;j++){
			for(k=a[j][i];k<=m;k++){
				dp[k]=max(dp[k],dp[k-a[j][i]]+a[j][i+1]-a[j][i]);
			}
		}//完全背包模板
		m+=dp[m];//下一次拥有的钱为今天剩余的钱
	}
	cout<<m;
	return 0;
}
```


---

## 作者：SegTre (赞：0)

## 解题思路

由题意可知，我们在接下来的D天要每天在S只股票中做出买或不买，卖或不卖的抉择，使盈利最大化。

**我们需要明白：**

- 当天不卖出股票 = 当天卖出股票再买进股票，于是我们简化掉了“卖与不卖”这一抉择——可以当做每天先抛掉所有股票，再考虑要不要买。

- 于是我们可以每天更新一下初始状态，即手里的资金数量（通过把前一天的股票都卖掉）

- 要使得最后利益最大化，就要在当天作出让第二天初始资金最多的抉择。

- 只考虑相邻两天：问题转化为用最小花费获得最大价值

![](https://cdn.luogu.com.cn/upload/image_hosting/q3ii9teh.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

“贝西在每天可以买卖多只股票，也可以多次买卖同一只股票”

**——多重背包了解一下**

**股票种类——物品种类**

**股票价格——物品体积**

**股票对于前一天的盈利——物品价值**

只需要作出 D - 1 次这样的抉择，问题迎刃而解。

## 上代码
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
inline int read()
{
	int res;
	char c;
	while((c=getchar())<'0'||c>'9');
	res=c^48;
	while((c=getchar())>='0'&&c<='9')
	res=(res<<3)+(res<<1)+(c^48);
	return res;
}
int w[105][105],c[105][105],dp[500005];
int main()
{
	int n=read(),t=read(),m=read(),coin=0;
	for(int j=1;j<=n;++j)
	for(int i=1;i<=t;++i)
	w[i][j]=read();
	for(int j=1;j<=n;++j)
	for(int i=1;i<t;++i)
	c[i][j]=w[i+1][j]-w[i][j];
	for(int k=1;k<t;++k)//D-1次抉择
	{
		memset(dp,0,sizeof(dp));
		coin=0;
		for(int i=1;i<=n;++i)
		for(int j=w[k][i];j<=m;++j)
		dp[j]=max(dp[j],dp[j-w[k][i]]+c[k][i]);
		for(int i=m;i==dp[m];--i)
		coin++;
		m+=dp[m]+coin;//记得加上没用完的资金
	}
	printf("%d",m);
	return 0;
}
```


---

## 作者：ql12345 (赞：0)

# 细节好评！

pj的题都做不了满分（第一次提交）/kk

做法：贪心+完全背包，别的题解都已经说的很清楚了（大概，毕竟我也没看）

说一下让我觉得很好的一个细节：

先看我一开始的代码：

```cpp
m=f[m];
```
发现过不了样例，对着样例可以发现问题：**第二天用不完所有的钱**

于是改了之后成为下面这个：

```cpp
int ans=m;
while(f[ans-1]==f[m])--ans;
m=f[ans]+m-ans;
```

发现84tps，没有样例了，看代码~~~ 看着这个while循环怎么这么假~~FAke~~？

于是想，ans如果继续--，如果减得很多，而f[ans]减得比较少呢？

于是就有了下面的AC代码：

```cpp
int ans=m;
for(re int j=1;j<=m;++j)ans=max(ans,f[j]+m-j);
m=ans;
```

祝大家 ~~看完题解~~ 一遍AC！

---

