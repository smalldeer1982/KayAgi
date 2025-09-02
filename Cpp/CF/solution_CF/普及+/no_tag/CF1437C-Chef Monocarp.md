# Chef Monocarp

## 题目描述

Chef Monocarp has just put $ n $ dishes into an oven. He knows that the $ i $ -th dish has its optimal cooking time equal to $ t_i $ minutes.

At any positive integer minute $ T $ Monocarp can put no more than one dish out of the oven. If the $ i $ -th dish is put out at some minute $ T $ , then its unpleasant value is $ |T - t_i| $ — the absolute difference between $ T $ and $ t_i $ . Once the dish is out of the oven, it can't go back in.

Monocarp should put all the dishes out of the oven. What is the minimum total unpleasant value Monocarp can obtain?

## 说明/提示

In the first example Monocarp can put out the dishes at minutes $ 3, 1, 5, 4, 6, 2 $ . That way the total unpleasant value will be $ |4 - 3| + |2 - 1| + |4 - 5| + |4 - 4| + |6 - 5| + |2 - 2| = 4 $ .

In the second example Monocarp can put out the dishes at minutes $ 4, 5, 6, 7, 8, 9, 10 $ .

In the third example Monocarp can put out the dish at minute $ 1 $ .

In the fourth example Monocarp can put out the dishes at minutes $ 5, 1, 2, 4, 3 $ .

In the fifth example Monocarp can put out the dishes at minutes $ 1, 3, 4, 5 $ .

## 样例 #1

### 输入

```
6
6
4 2 4 4 5 2
7
7 7 7 7 7 7 7
1
1
5
5 1 2 4 3
4
1 4 4 4
21
21 8 1 4 1 5 21 1 8 21 11 21 11 3 12 8 19 15 9 11 13```

### 输出

```
4
12
0
0
2
21```

# 题解

## 作者：Tony102 (赞：11)

[CF1437C](https://www.luogu.com.cn/problem/CF1437C)

[更好的阅读体验My Blog](https://tony102.xyz/index.php/2020/10/28/cf1437c-chef-monocarp/)

### Description

有$n$到菜品被放入了一个烤炉中，每到菜品都有一个最佳取出的时间$t_i$。现在按照一定顺序把菜品从烤炉中取出，每到菜品都有可能因为不在最佳时间被取出而造成不美味，定义这个不美味度为$|T-t_i|$，其中$T$是取出的时刻。求把所有菜品都取出来的最小不美味度。

### Solution

设$f[i][j]$表示在$i$时刻拿出了前$j$个菜品可以获得的最小不美味度

考虑暴力DP

若不选，则$f[i][j] = min\{ f[i-1[j]\}$

如果选的话，那么$f[i][j] = min\{f[i-1][j-1] + |i - t[k]|\}$

按照现在的方式DP,每次都要枚举最后选的那个菜品$k$，考虑怎么优化它

贪心地选，我们肯定希望$t[i]$比较小的物品在比较靠前的时间就被选中了，这样会比较优

如果我们对所有$t[i]$进行排序，那么选出的菜品将会是连续的一段。也就是说，最后一个还未被选中的菜品一定当前要选的

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
 
const int SIZE = 6e2 + 5;
const int inf = 0x7f7f7f7f;
 
int T, n;
int a[SIZE], f[SIZE][SIZE];
 
inline int read()
{
	char ch = getchar();
	int f = 1, x = 0;
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + ch - '0'; ch = getchar(); }
	return x * f;
}
 
int main()
{
    T = read();
    while (T --) {
        n = read();
        for (int i = 1; i <= n; ++ i) a[i] = read();
        std::sort(a + 1, a + n + 1);
        memset(f, inf, sizeof(f));
        int minn = inf;
        f[0][0] = 0;
        for (int i = 1; i <= 2 * n; ++ i) {
            f[i][0] = 0;
            for (int j = 1; j <= std::min(i, n); ++ j) {
                f[i][j] = std::min(f[i][j], f[i - 1][j]);
				f[i][j] = std::min(f[i - 1][j - 1] + abs(i - a[j]), f[i][j]);
            }
            if (i >= n) minn = std::min(minn, f[i][n]);
        }
        printf("%d\n", minn);
    }
    return 0;
}
```



### 

---

## 作者：Yingluosanqian (赞：9)

# 来一个费用流的题解

首先显然对于任意 $n$ ，菜品出炉时间最多不超过 $2n$ 。这样就可以建立 $n$ 个点表示菜品， $2n$ 个点表示出炉时间。

关于建边：源点引一条流量为1费用为0的边连向各个菜品，每个菜品都向所有出炉时间连一条流量为1费用为 $|T_i-t_i|$ 的边，所有出炉时间引一条流量为1费用为0的边指向汇点。

求最大流最小费用即可。

---

## 作者：lytqwq (赞：7)

类似 **[P4331](https://www.luogu.com.cn/problem/P4331)** ，不同的是有了时间的限制（时间必须是正的）

同 **[P4331](https://www.luogu.com.cn/problem/P4331)** ，我们也有$O(nlogn)$的 ~~（碾压其他题解的）~~ 做法。

### 法一：

可并堆/左偏树 ~~（不会，不讲）~~

直接就是论文题，不再赘述，给个论文链接：[https://wenku.baidu.com/view/20e9ff18964bcf84b9d57ba1.html](https://wenku.baidu.com/view/20e9ff18964bcf84b9d57ba1.html)

~~（当然你也可以催我学，然后写）~~

### 法二：

堆

先对菜品按时间排序

时间不能重，就是上升序列，按照套路减下标变为求不下降序列。

建一个大根堆，每次看前面的最大值，并移下来，$ans$就加之间的差。

累加$ans$就完了

需要注意的是，与 **[P4331](https://www.luogu.com.cn/problem/P4331)** 不同，这题时间必须是正的，所以我们要在堆里先加足够多的$0$来保证不出现负时间，加$n$个即可

时间复杂度：$O(nlogn)$~~（所以这题数据完全可以出到$1e6$？）~~

AC情况：[https://www.luogu.com.cn/record/41160617](https://www.luogu.com.cn/record/41160617)

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000010;
int n,a[N];
long long int ans;
priority_queue<int>ovo;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		while(!ovo.empty())ovo.pop();
		ans=0;
	    scanf("%d",&n);
	    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    	sort(a+1,a+n+1);
    	for(int i=1;i<=n;i++)ovo.push(0);
    	for(int i=1;i<=n;i++){
		
	    	a[i]-=i;
	    	ovo.push(a[i]);
	    	if(ovo.top()>a[i]){
                ans+=ovo.top()-a[i];
		    	ovo.pop();ovo.push(a[i]);
	    	}
    	}
    	printf("%lld\n",ans);
	}
}
```




---

## 作者：fisheep (赞：2)

## 想法:
设状态 $dp[i][j] $为前 $i$ 个时刻取出了前 $j$ 物品的花费，显然有转移方程：$dp[i][j]=min(dp[i-1][j],dp[i-1][j-1]+abs(t[j]-i))$ ，

这个方程可以把第一维压掉通过倒序转移（类似与背包），时间最坏情况是从$n$时刻开始拿出物品，最多到 $2 n$ 时刻全部拿完

其实这个题是很像是背包的，背包的容量为 $ n$ ，每个物品体积是 $1$，花费是$abs(t_i-t_{i1})$ ，就可以设 $dp[i]$ 表示容量为$i$ 的时候的最小价值，用背包方程求解 $dp[n]$ 即可。

## Code:
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define int long long
const int inf=0x3f3f3f3f;
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0') {
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}

const int maxn=207;
int a[maxn],dp[maxn];
signed main() {
	int t=read();
	while(t--) {
		int n=read();
		for(int i=1; i<=n; i++) {
			a[i]=read();
		}
		sort(a+1,a+n+1);
		memset(dp,0x3f,sizeof dp);
		dp[0]=0;
		for(int i=1; i<=2*n; i++) {
			for(int j=n; j>=0; j--) {
				dp[j]=min(dp[j],dp[j-1]+abs(a[j]-i));
			}
		}
		printf("%lld\n",dp[n]);
	}
	return 0;
}
```


---

## 作者：LRL65 (赞：2)

这题和 [P4331](https://www.luogu.com.cn/problem/P4331)好像有一亿点点像。



------------
这题很容易想到是**DP**吧。~~毕竟我在考场上都能想到。~~

但是要想DP，**必须得在DP前排一下序**。

那么 $f_{i,j}$ 的意思是选前 $i$ 个菜，在第 $j$ 分钟所需的最小值。

那么**状态转移方程**：$f_{i,j}=\min(f_{i,j},f_{i-1,k}+abs(j-a_i))$ $(k$为前一个选的时间$)$。

时间复杂度为 $O(n^3)$，完全可以过。

初始化我是先全赋最大，然后将 $f_{1,j}$ 全跑一边。最后的答案应为 $f_{n,i}$ 的最小值。



------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a[415],f[415][415],ans;//不开long long 见祖宗
int main() {
	cin>>t;
	while(t--) {
		cin>>n;
		ans=100000000;//ans记得要赋一个大的值
		for(int i=1;i<=n;i++)cin>>a[i];
		sort(a+1,a+n+1);//排序
        memset(f,0x3f,sizeof(f));//先全最大
		for(int j=1;j<=410;j++)
			f[1][j]=abs(a[1]-j);//跑f[1][j]
		for(int i=2;i<=n;i++) 
			for(int j=i;j<=410;j++)
                for(int k=i-1;k<j;k++)
				    f[i][j]=min(f[i][j],f[i-1][k]+abs(j-a[i]));
		for(int i=n;i<=410;i++)
			ans=min(ans,f[n][i]);//最小的f[n][i]
		cout<<ans<<endl;
	}
}
```


------------
对了，感谢 @do_while_true 大神和我一起讨论本题

---

## 作者：zjrdmd (赞：2)

一道简单的dp题，看大家都是$O(n^2)$/fad。

提供一个简单好想的$O(n^3)$做法。

设$dp_{i,k}$表示第$i$时刻选择第$k$个物品的最小代价。

对于每个$i$，我们都可以枚举一个$j$，代表前一个物品选择在第$j$时刻。

那么就有如下$dp$式子，$dp_{i,k}=min(dp_{j,k-1}+|a_k-i|,dp_{i,k})$。

于是就有了如下代码。

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#define ri register int

inline int read() {
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}

const int N=205;
int dp[N<<1][N],a[N],n,ans=1e9+7;

int abs_(int x){
	return ((x<0)?(-x):x);
} 

int main(){
	int T=read();
	while(T--){
		memset(dp,0x3f,sizeof(dp));
		n=read();
		for(ri i=1;i<=n;i++)a[i]=read();
		std::sort(a+1,a+n+1);
		for(ri i=1;i<=(n<<1);i++)dp[i][0]=0;
		for(ri i=1;i<=(n<<1);i++){
			dp[i][1]=abs_(i-a[1]);
			for(ri j=1;j<i;j++){
				for(ri k=1;k<=n;k++){
					if((k-1)<=j)dp[i][k]=std::min(dp[i][k],dp[j][k-1]+abs_(a[k]-i));
				}
			}
		}
		for(ri i=1;i<=(n*2);i++)ans=std::min(ans,dp[i][n]);
		printf("%d\n",ans),ans=1e9+7; 
	} 
	return 0;
}

```

P.s：感谢@orz_MSQ 的提醒，对题解部分内容进行了更正。

---

## 作者：123zbk (赞：1)

$n\le 200 $，直接暴力 dp。

设 $dp[i][j]$ 表示前 $i$ 个菜品，在第 $j$ 分钟的最小不美味度。

$dp[i][j]=\min(dp[i][j],dp[i-1][k]+|j-t[i]|)$，$k$ 枚举前一个 $i$ 的时间。

复杂度 $O(n^3)$。

或者我们只需考虑枚举当前这一分钟取还是不取即可。

$dp[i][j]=\min(dp[i-1][j-1]+|j-t[i]|,dp[i][j-1])$。

复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=405;
int T,n,a[maxn],dp[maxn][maxn],ans;
signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		ans=0x3f3f3f3f;
		memset(dp,0x3f,sizeof(dp));
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&a[i]);
		}
		sort(a+1,a+n+1);
		for(int j=1;j<=maxn;j++)
		{
			dp[1][j]=abs(a[1]-j);
		}
		for(int i=2;i<=n;i++)
		{
			for(int j=i;j<=maxn;j++)//最坏情况是2n时刻 
			{
				for(int k=i-1;k<j;k++) 
				{
					dp[i][j]=min(dp[i][j],dp[i-1][k]+abs(j-a[i]));
				}
			}
		}
		for(int j=n;j<=maxn;j++)
		{
			ans=min(ans,dp[n][j]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：ykzzldz (赞：1)

贪心地想，$t_i$ 小的一定先取，因为若交换两个数的位置，对答案一定是有贡献的（也就是将一个大的放到前面一定不优），那么这题就变得比较简单了。我们用 $dp[i][j]$ 表示在第 $i$ 分钟取出 $j$ 号菜的最小值。那么 $dp[i][j]=\min(dp[i][j],dp[k][j-1]+|t_i-i|)$，其中 $k$ 的范围是 $[1,i)$。下面给出代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a[300],dp[450][300],ans,n;
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		ans=1e9;
		memset(dp,127,sizeof dp);
		for(int i=1;i<=n;i++)cin>>a[i];
		sort(a+1,a+1+n);
		for(int i=1;i<=400;i++){
			dp[i][1]=abs(a[1]-i);
			for(int j=2;j<=n;j++){
				for(int k=1;k<i;k++){
					dp[i][j]=min(dp[i][j],dp[k][j-1]+abs(a[j]-i));
				}
			}
			ans=min(ans,dp[i][n]);
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：1)

upd：受 @wz20201136 之前问我的一道题的启发，我发现了 $O(n^2)$ 做法。

第一次秒掉 `*1800` 的 dp（几乎想都没想的那种），祭。

## 思路

显然的贪心性质是按照 $t_i$ 排个序，把先烤好的先取。

然后我们找不到什么特别好的贪心性质，所以考虑进行 dp。我们假设 $dp_{i,j}$ 表示前 $i$ 个，花费 $j$ 分钟取完的时候，所能得到的最大美味度。

转移自然好想，我们对于每个 $dp_{i,j}$，考虑 $i-1$ 在什么时候取出来。显然因为 $t_{i-1} \leq t_i$，所以 $i-1$ 在 $i$ 之前取出来肯定更优。因此枚举一个 $k \in [1,j-1]$ 更新答案，最后取 $\max$。形式化地：

$$dp_{i,j}=\max\limits_{k=1}^{j-1}dp_{i,k}+|j-t_i|$$

复杂度 $O(n^3)$。

注意，$j$ 这一维要开 $2n$（准确来说应该是 $\left\lceil\dfrac{3}{2}n\right\rceil$） 大小，因为如果输入 $n$ 个 $n$ 的话，最优的安排，$j$ 会超出 $n$。

## New Update：

其实不需要枚举 $k$，只需要决策当前这一分钟取不取。

$$dp_{i,j}=\min(dp_{i-1,j-1}+|a_i-j|,dp_{i,j-1})$$

复杂度 $O(n^2)$。

## 代码

$O(n^3)$：

```cpp
#include <bits/stdc++.h>
using namespace std;
int dp[205][405],a[205];
void solve(){
	memset(dp,0x3f,sizeof(dp));
	int n,ans=1e9; cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n);
	dp[0][0]=0;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=(n<<1);j++)
			for(int k=0;k<j;k++)
				dp[i][j]=min(dp[i][j],dp[i-1][k]+abs(a[i]-j));
	for(int i=1;i<=(n<<1);i++) ans=min(ans,dp[n][i]);
	cout<<ans<<endl;
}
int main(){
	int T; cin>>T;
	while(T--) solve();
	return 0;
}
```

$O(n^2)$：

```cpp
#include <bits/stdc++.h>
using namespace std;
int dp[205][405],a[205];
void solve(){
	memset(dp,0x3f,sizeof(dp));
	int n,ans=1e9; cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n);
	for(int i=0;i<=(n<<1);i++) dp[0][i]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=(n<<1);j++)
			dp[i][j]=min(dp[i][j-1],dp[i-1][j-1]+abs(a[i]-j));
	}
	for(int i=1;i<=(n<<1);i++) ans=min(ans,dp[n][i]);
	cout<<ans<<endl;
}
int main(){
	int T; cin>>T;
	while(T--) solve();
	return 0;
}
```

我再考虑考虑怎么优化成 $O(n \log n)$，感觉可行（

---

## 作者：Hilte (赞：1)

# 一.基本思路
这是一道DP的题。  
$dp_{i,j}$ 表示第 $j$ 分钟，取下第 $i$ 道菜的最小难吃指数
# 二.状态转移方程

初始化： 
$dp_{1,j} = abs(j-a_i)$ 其中 $1 \le j \le 2 \times n$  
因为最坏情况下，最后一道菜可能要 $2 \times n$ 秒后才能取出

状态转移方程：  
$dp_{i,j}=\min({dp_{i,j},dp_{i,k}+abs(j-a_i}))$  
其中$1 \le i \le n,1 \le j \le 2 \times n , 1 \le k \le j-1$

# 三.代码
```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

int n, a[205];
//dp[i][j]第j分钟，取下第i到菜的最小难吃指数 WWF758
int dp[205][405] = {{0}};
int main()
{
	int t;
	cin >> t;
	for(int f = 1; f <= t; f++)
	{	
		cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		sort(a + 1, a + n + 1);	
		//初值
		memset(dp, 0x3f3f3f3f, sizeof(dp));
		for (int j = 1; j <= 2 * n; j++)
			dp[1][j] = abs(j - a[1]);
		//递推
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= 2 * n; j++){
				//更新dp[i][j], 根据a[i-1]在第k分钟分类
				for (int k = 1; k < j; k++)
					dp[i][j] = min(dp[i][j], dp[i - 1][k] + abs(j - a[i]));
			}
		//答案
		int ans = 0x3f3f3f3f;
		for (int j = 1; j <= 2 * n; j++)
			ans = min(ans, dp[n][j]);
		cout << ans << endl;
	}
	return 0;
}
```


---

## 作者：aakennes (赞：1)

~~1800的题竟然这么氵~~

## 正文

#### 题目大意：

给定一序列，球一排列与此序列每一项差之和最小

#### 思路：

原序列不好看，先排一遍序

错误的贪心策略：让 $a_i$ 接近最大值

发现贪心只能保证局部最优解不能保证整体最优解

考虑 $DP$

设定 $f_{i,j}$ 表示第 $i$ 盘菜此前最大值是 $j$

转移方程：

$$f_{i,j}=min(f_{i-1,k}+\begin{vmatrix}
 & a_ i-k& \\ 
\end{vmatrix})(k<j)$$

时间复杂度 $O(qn^3)$，常数很小

把暴力一交，发现A了（没看到 $\sum n<=200$）

发现柿子里后面一项与 $k$ 无关，直接前缀维护最小值就可达到 $O(qn^2)$

### 代码：
```
n=read();
		for(register int i=1;i<=n;i++)a[i]=read();
		if(n==1){puts("0");continue;}
		stable_sort(a+1,a+1+n);ans=INF;
		memset(f,0x3f,sizeof(f));memset(sum,0x3f,sizeof(sum));
		for(int i=1;i<=200;i++)f[1][i]=abs(i-a[1]),sum[i]=min(f[1][i],sum[i-1]);
		for(int i=2;i<=n;i++){
			sum[i-2]=INF;
			for(int j=i;j<=400;j++){
				f[i][j]=sum[j-1]+abs(a[i]-j);
				sum[j-1]=min(sum[j-2],f[i][j-1]);
				if(i==n)ans=min(ans,f[i][j]);
			}
			sum[400]=min(sum[400],f[i][400]);
		}
		printf("%d\n",ans);
```

---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1437C)
## 思路
基础 $\verb!DP!$ 题，直接暴力。

设 $f_{i,j}$ 表示前 $i$ 个菜肴，其中第 $i$ 个菜肴选在 $j$ 时刻制作的最小不美味度。

转移 $f_{i,j}=min(f_{i-1,k}+|t[i]-j|)$，我们发现这个方程非常有意思，其中 $i$ 这一维可以压掉，而取 $\min$ 的操作可以一个前缀 $\min$ 优化到 $O(nm)$，但是由于这只是一道基础的 $\verb!DP!$ 题，我选择不加优化，直接暴力转移。

时间复杂度 $O(nm^2)$，这里不妨设 $m$ 是一个较大的数，例如我就设为 $2000$，答案就是 $\min f_{n,j}$。
## 代码
```cpp
//A tree without skin will surely die. 
//A man without face is invincible.
#include<bits/stdc++.h>
#define int long long
#define rint register int
using namespace std;
int const N=2e2+10;
int const M=2e3+10;
int f[N][M],t[N];
signed main(){
    ios::sync_with_stdio(false);
    cout.tie(0),cout.tie(0);
    int T;cin>>T;
    while (T--){
        int n,m=2000,ans=9e18;cin>>n;
        for (int i=1;i<=n;++i) cin>>t[i];
        sort(t+1,t+n+1);
        memset(f,0x3f,sizeof(f));
        for (int j=1;j<=m;++j) f[1][j]=abs(t[1]-j),ans=min(ans,f[n][j]);
        for (int i=2;i<=n;++i)
            for (int j=1;j<=m;++j){
                for (int k=1;k<j;++k)
                    f[i][j]=min(f[i][j],f[i-1][k]+abs(t[i]-j));
                ans=min(ans,f[n][j]);
            }
        cout<<ans<<'\n';
    }
    return 0;
}
```

虽然跑到了最优解最后一名，但是这个 $\verb!DP!$ 仍然有非常大优化的空间，这就留给各位读者完成了。

---

## 作者：zztqwq (赞：0)

## Solution

将 $\{t_i\}$ 排序，令 $f(i,j)$ 表示前 $i$ 个菜品在前 $j$ 个时刻的最小代价，则容易得出 $f(i,j)=\min\{f(i-1,j-1)+\vert j-t_i\vert,f(i,j-1)\}$，分别决策第 $j$ 秒选或者不选菜品 $i$。注意 $j$ 的循环范围是 $1\sim 2n$ 而不是 $1\sim n$，因为在 $n$ 秒之后还有可能放菜品。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
const int N=200;
int dp[N+10][2*N+10],a[N+10];
//   选了 i 个菜品，前j秒 
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		sort(a+1,a+n+1);
		memset(dp,0x3f,sizeof(dp));
		for(int i=0;i<=2*n;i++) dp[0][i]=0;
		
		for(int i=1;i<=n;i++)
			for(int j=1;j<=2*n;j++)
				dp[i][j]=min(dp[i][j-1],dp[i-1][j-1]+abs(j-a[i]));
		printf("%d\n",dp[n][n*2]);
	}
	return 0;
}
```





---

## 作者：heaven_soar (赞：0)

#### 题目简介：
每一盘菜都有最佳取出时间 $t_i$，而每一时间节点只能取出一盘菜，而第 $i$ 盘菜的不美味值为 $|t-t_i|$，$t$ 为实际取出时间。求菜的不美味值和最小。

#### 思路：
考虑数据范围为100，可以想到用dp完成，同时最佳取出时间小的必定在大的之前取出，进行排序后就可以将其转化为类似背包的问题：

设 $\large f_{i,j}$ 为选到前 $i$ 盘菜，最后第 $i$ 盘的选取时间为 $j$ ，能得到的最小不美味值。再枚举上一盘菜的选取时间 $k$，就有转移方程：
$$
\Large f_{i,j}=\min(f_{i-1,k})+|j-t_i|,k\in[i-1,j)
$$
递推求解。

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define re register
using namespace std;
inline int qread(){///快读
	int x=0;
	char c=getchar(),o=' ';
	while(c<'0'||c>'9') o=c,c=getchar();
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	if(o=='-') x=-x;
	return x;
}
int f[201][401],a[201];
int Min(int x,int y){
	return x<y?x:y;
}
int Max(int x,int y){
	return x>y?x:y;
}
int Abs(int x){
	return x>0?x:~x+1;
}
int main(){
	int t=qread();
	while(t--){
		memset(a,0,sizeof a);
		int n=qread(),mx=0;
		for(re int i=1;i<=n;++i)
			a[i]=qread();
		mx=n*2;//最大的最佳取出时间不超过n，而最多有n个数，为了防止超出边界，选取时间最大值开到2*n
		sort(a+1,a+1+n);
		for(re int i=0;i<=n;++i)
			for(re int j=0;j<=mx;++j)
				f[i][j]=0x3fffffff;
		for(re int i=0;i<=mx;++i) f[0][i]=0;
		for(re int i=1;i<=n;++i){
			for(re int j=i;j<=mx;++j){//注意之前至少前i-1的时间内都取出过菜了
				for(re int k=i-1;k<j;++k){
					f[i][j]=Min(f[i][j],f[i-1][k]);
				}
				f[i][j]+=Abs(j-a[i]);
			}
		}
		int ans=0x3fffffff;
		for(re int i=n;i<=mx;++i) ans=Min(ans,f[n][i]);
		cout<<ans<<'\n';
	}
	return 0;
}
```


---

## 作者：yu__xuan (赞：0)

### 题目

[CF1437C Chef Monocarp](https://www.luogu.com.cn/problem/CF1437C)

### 思路

$f_{i,j}$ 表示前 $i$ 个时间点拿出了 $j$ 个物品的最小贡献。

状态转移方程为 $f_{i,j}=\min(f_{i,j},f_{i-1,j-1}+|i-t_j|)$。

发现转移有点像 $01$ 背包，倒序枚举 $j$，可以优化成一维。

$f_j$ 表示拿出了前 $j$ 个的最小贡献。

状态转移方程为 $f_j=\min(f_j,f_{j-1}+|i-t_j|)$。

### Code

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#define M 201

int min(int a, int b) { return a < b ? a : b; }

int t, n, a[M], f[M];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        std::sort(a + 1, a + n + 1);
        memset(f, 0x3f, sizeof f);
        f[0] = 0;
        for (int i = 1; i <= 2 * n; ++i) {
            for (int j = n; j >= 1; --j) {
                f[j] = min(f[j], f[j - 1] + abs(a[j] - i));
            }
        }
        printf("%d\n", f[n]);
    }
    return 0;
}
```

---

## 作者：the_xin (赞：0)

据群友们说此题是dp 于是咱来个大炮轰蚊子（最小费用最大流）

根据题意我们知道有n到菜品被放入了一个烤炉中，每到菜品都有一个最佳取出的时间ti。现在按照一定顺序把菜品从烤炉中取出，每到菜品都有可能因为不在最佳时间被取出而造成不美味，定义这个不美味度为|T-ti|，其中T是取出的时刻。求把所有菜品都取出来的最小不美味度。
所以我们可以将每个菜品看作左边的点 每一天看做右边的点根据贪心我们知道 最多n*3/2 天 这就是一个二分图 
跑一边费用流即可

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int N=650,M=(200*300+N+20)<<1,INF=1e9+10;
struct Edge
{
    int v,next,w,c;
}edge[M];
int head[N],tot=1,n,m,S,T,d[N],incf[N],pre[N];
void add(int u,int v,int w,int c){
    edge[++tot]={v,head[u],w,c};
    head[u]=tot;
    edge[++tot]={u,head[v],0,-c};
    head[v]=tot;
}
void init(){
    memset(head,0,sizeof(head));
    tot=1;
}
bool vis[N];
int spfa(){
    memset(d,0x3f,sizeof(d));
    memset(incf,0,sizeof (incf));
    queue<int>q;
    d[S]=0;
    incf[S]=INF;
    q.push(S);
    while(q.size()){
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(int i=head[u];i;i=edge[i].next){
            int v=edge[i].v;
            int w=edge[i].w;
            int c=edge[i].c;
            if(w&&d[v]>d[u]+c){
                d[v]=d[u]+c;
                pre[v]=i;
                incf[v]=min(w,incf[u]);
                if(!vis[v]){
                        q.push(v);
                        vis[v]=1;
                   }
            }
        }
    }

    return incf[T]>0;

}
int ek(){
    int cost=0;
    while(spfa()){
        int u=T;
        while(u!=S){
            int i=pre[u];
            edge[i].w-=incf[T];
            edge[i^1].w+=incf[T];
            u=edge[i^1].v;
        }
        cost+=d[T]*incf[T];
    }
    return cost;
}
int main(){
    int __;
    scanf("%d",&__);
    while(__--){
        init();
        scanf("%d",&n);
        S=n*3+10,T=S+1;
        for(int i=1;i<=n;i++){
            int x;
            scanf("%d",&x);
            add(S,i,1,0);
            for(int j=1;j<=(n*3+1)/2;j++){
                add(i,j+n,1,abs(x-j));
            }

        }
        for(int j=1;j<=(n*3+1)/2;j++){
                add(j+n,T,1,0);
            }
        printf("%d\n",ek());

    }
}

```


---

