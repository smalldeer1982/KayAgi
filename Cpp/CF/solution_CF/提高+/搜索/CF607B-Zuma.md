# Zuma

## 题目描述

$\texttt{Genos}$ 最近在他的手机上下载了祖玛游戏。在祖玛游戏里，存在 $n$ 个一行的宝石，第 $i$ 个宝石的颜色是 $C_i$。这个游戏的目标是尽快的消灭一行中所有的宝石。

在一秒钟，$\texttt{Genos}$ 能很快的挑选出这些有颜色的宝石中的一个回文的、连续的子串，并将这个子串移除。每当一个子串被删除后，剩余的宝石将连接在一起，形成一个新的行列。

你的任务是：求出把整个宝石串都移除的最短时间。

## 说明/提示

在第一个例子中，$\texttt{Genos}$ 可以在一秒钟就把这行珠子全部移走。在第二个例子中，$\texttt{Genos}$ 一次只能移走一个珠子，所以移走三个珠子花费他三秒。在第三个例子中，为了达到 $2$ 秒的最快时间，先移除回文串 $\texttt{4 4}$,再移除回文串 $\texttt{1 2 3 2 1}$。

感谢 @Administrator2004 提供的翻译

## 样例 #1

### 输入

```
3
1 2 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
1 2 3
```

### 输出

```
3
```

## 样例 #3

### 输入

```
7
1 4 4 2 3 2 1
```

### 输出

```
2
```

# 题解

## 作者：QwQcOrZ (赞：165)

区间dp

其它的题解做法比较玄学 ~~至少我是没有看懂~~，或者是用递归实现转移的 ~~于是我决定发篇题解~~

------------

题意：从一个序列中每次取出一个回文串，求最少取几次（取出后两端外的数会相接）

------------

设$dp[i][j]$为在$[i,j]$的闭区间内最少的花费

显然
$\begin{cases}dp[i][i]=1\\dp[i][i+1]=1\quad (a[i]=a[i+1])\\dp[i][i+1]=2\quad (a[i]\ne a[i+1])\end{cases}$

~~原因请读者自行脑补~~

于是可以推出转移方程：

$\begin{cases}dp[i][j]=dp[i+1][j-1]\quad (a[i]=a[j])\\\\dp[i][j]=min_{k=i}^{j-1}dp[i][k]+dp[k+1][j]\end{cases}$

然后就可以愉快的dp辣

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505;
const int inf=233333333;

int n,a[N],dp[N][N];

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=n;i++)
	for (int j=1;j<=n;j++) dp[i][j]=inf;  //开始全赋inf，否则转移取min时就会挂掉
	for (int i=1;i<=n;i++) dp[i][i]=1;  //直接取一个数，花费一个代价
	for (int i=1;i<n;i++) dp[i][i+1]=1+(a[i]!=a[i+1]);  //取两个数的情况，如果相等取一次就好了，否则取两次
	for (int i=3;i<=n;i++)  //注意转移时需要先枚举区间长度
	for (int j=1;i+j-1<=n;j++)
	{
		int l=j,r=i+j-1;  //计算区间左右端点
		if (a[l]==a[r]) dp[l][r]=dp[l+1][r-1];
		for (int k=l;k<r;k++) dp[l][r]=min(dp[l][r],dp[l][k]+dp[k+1][r]);  //转移
	}
	printf("%d",dp[1][n]);

	return 0;
}
```

---

## 作者：installb (赞：31)

区间DP.  

~~看到n=500应该知道复杂度是n三方了吧~~  
$dp[i][j]$表示$[i,j]$区间全部消除最少需要多少步  
对于回文串的处理 其实只要当第$i$和第$j$个珠子颜色相同 那么这两个珠子一定可以在消除$[i+1,j-1]$过程的的最后一步顺便把$i$和$j$也一起消掉  
因为**每一次消除的都是一个回文串 回文串两端同时加上一个相同的字符还是一个回文串**  

如果这两个颜色不相同 枚举断点 答案是消掉左半区间最少步数加上消掉右半边区间最少步数 取最小值 如果能更优那么在上一步已经处理过了  

注意**每一步都要取min** 后者出来的结果可能比前者小  

还有注意处理长度为2的回文串的情况  
dp的预处理也很重要

具体(dp式子)看代码吧  

**code:**  
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

struct node{
	int l,r;
}pal[505];
int n,c[505],cnt = 0;

int dp[505][505] = {0};

int main(){
	memset(dp,0x3f,sizeof(dp)); // 预处理正无穷
	cin >> n;
	for(int i = 1;i <= n;i ++) cin >> c[i];
	for(int i = 1;i <= n;i ++){
		dp[i][i] = 1;
        // 长度为1的本来就是回文串 预处理为1
		dp[i][i - 1] = 1; 
        // 这里通过把长度为0的字符串都赋值为1来应对长度为2的会问串的情况
	}
	for(int l = 1;l <= n;l ++){
		for(int i = 1;i < n;i ++){
			int j = i + l; if(j > n) break;
			if(c[i] == c[j]) dp[i][j] = min(dp[i][j],dp[i + 1][j - 1]);
            // 第一种情况
			for(int k = i;k < j;k ++){
				dp[i][j] = min(dp[i][j],dp[i][k] + dp[k + 1][j]);
			}
            // 第二种情况 枚举断点
            // 每一步取min
		}
	}
	cout << dp[1][n] << endl;
	return 0;
}
```

---

## 作者：xcxc82 (赞：22)

# CF607B Zuma 题解

## [间隙(原题面)](https://www.luogu.com.cn/problem/CF607B)
- 前排声明:蒟蒻刚学oi没多久,而且是自学的,写的可能会比较累赘,望见谅。

## 前置知识

- 基础区间dp



##  题意

给一个长度为n的串,每次都可以挑选一个回文的连续字串进行消除,删除后，剩余的串将连接在一起，形成一个新的串,求把串全部删除完需要的最小次数


------------


## 分析

![](https://cdn.luogu.com.cn/upload/image_hosting/k3ezz757.png)

可以看出每一个区间的的求解都可以分为更小的两个区间的求解

联想到区间dp


设$dp[l][r]$为左端点为l,右端点为r时的最优解


不难推出~~比较套路的~~状态转移方程

- $dp[l][r]=min(dp[l][r],dp[l][k]+dp[k+1][r]).(l<=k<r)$

同时,这里还有一个区间的回文判断



假设我们把总区间划分为两个区间

$[1,4,5,3,4,1,3,2]$和$[3,2]$

其中$[1,4,5,3,4,1,3,2]$包含一个回文部分

![](https://cdn.luogu.com.cn/upload/image_hosting/teqq2yqh.png)

此时我们只要直接将回文部分删去即可

即$dp[l][r]=dp[l+1][r-1]$

这其实是一个类似于预处理的东西(个人看法,可能有误)

如果一个区间包含回文部分

则先把$dp[l][r]$给预处理成它不进行划分可以产生的最小值


再去和划分成两个区间所产生的最小值进行比较

- 即$if(a[l]==a[r])$
$dp[l[[r]=dp[l+1][r-1]$

贴上丑陋的代码

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;
const int MAXN = 510;
int n,a[MAXN],dp[MAXN][MAXN];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){//预处理长度为1的区间
		dp[i][i]=1;
	}
	for(int len=1;len<n;len++){//枚举长度
		for(int l=1;l<=n&&l+len<=n;l++){//枚举左右断点
		
			int r=l+len;
				dp[l][r]=inf;
			if(a[l]==a[r]){//如果包含回文部分
				if(r==l+1){//注意,这里是区间长度为2的特判
					dp[l][r]=dp[l+1][r-1]=1;
				}
				else dp[l][r]=dp[l+1][r-1];
			}
			for(int k=l;k<r;k++){//枚举断点
				dp[l][r]=min(dp[l][r],dp[l][k]+dp[k+1][r]);
			}
		}
	}
	cout<<dp[1][n];
} 
```
如有错误欢迎大佬们指出QwQ








---

## 作者：Diaоsi (赞：13)

## 题目链接：[传送门](https://www.luogu.com.cn/problem/CF607B)
## 思路：
这是一道比较套路的区间dp。

我们首先设状态为 $f(i,j)$ ，表示将区间 $[i,j]$ 内所有的珠子消除的最小步数。

显然，初始化为 $f(i,i)=1$ ，目标状态为 $f(1,n)$ 。

按照区间dp的做法，我们可以先枚举区间长度，左端点 $i$ 和右端点 $j$ ，不难发现当左端点与右端点的珠子颜色一样时，将区间 $[i,j]$ 内所有的珠子消除的最小步数与将区间 $[i+1,j-1]$ 内所有的珠子消除的最小步数相同，即：

$$f(i,j)=f(i+1,j-1),a_i=a_j$$

当不满足这个条件时，就在区间 $[i,j]$ 内枚举断点 $k$ ，此时将区间 $[i,j]$ 内所有的珠子消除的最小步数为将区间 $[i,k]$ 与 $[k+1,j]$ 内所有的珠子消除的最小步数之和的最小值，即：

$$f(i,j)=\min(f(i,j),f(i,k)+f(k+1,j)),k\in(i,j)$$

此时我们注意到，有可能出现回文串为偶数的情况，对于此种情况，我们只需要在初始化时将长度为 0 的回文串的操作次数初始化为 1 ，这样在遇到一对相邻且相等的 $a_i$ 与 $a_j$ 时就能正确转移状态，即可解决有关偶数长度回文串的问题。

至此，问题得到了解决。

## 代 码 放 送：

既然你能找到这题，我相信你能瞬间做出来的。

$Code:$

```cpp
#include<bits/stdc++.h>
#define Max(x,y) (x>y?x:y)
#define Min(x,y) (x<y?x:y)
using namespace std;
const int N=1010,INF=0x3f3f3f3f;
int n,a[N],f[N][N];
int main(){
	scanf("%d",&n);
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),f[i][i]=f[i][i-1]=1;
	for(int l=1;l<=n;l++) 
		for(int i=1;i<=n-l;i++){
			int j=i+l;
			if(a[i]==a[j])f[i][j]=f[i+1][j-1];
			for(int k=i;k<=j;k++)f[i][j]=Min(f[i][j],f[i][k]+f[k+1][j]);
		}
	printf("%d\n",f[1][n]);
	return 0;
}
```


---

## 作者：king_kb (赞：9)

题意：

给定一个序列，如果其子序列是一个回文字串，那么它可以一次消除。问最少需要多少次才可以将字符串全部消除。

那么题目就很明了了，直接分析第三个样例。

```c++
7
1 4 4 2 3 2 1
```
答案是2，其过程也就是先把44消除，形成的新子序列是12321，刚好是一个回文子序列。第一想法就是模拟，但是涉及到新数组的生成，想想就很头疼再看看$n \leq 500$基本可以断定这就是道dp问题。而且是一个区间dp问题。

那么设计状态$dp[i][j]$表示消除区间$[i,j]$的最小步数，可以很轻松想到$dp[i][j]=min(dp[i][j], dp[i][k]+dp[k][j])$但是这样显然少考虑了一种情况，就是两个子序列合并起来成为子串的情况，由dp的性质可以很轻松的想到，只需要判断$num[i]$和$num[j]$的关系，如果两个相等的话，$dp[i][j]=dp[i+1][j-1]$大致思路就是这样。

但是出初始化的问题也需要考虑。$dp[i][i]=1$这个可以很轻松想到，但是这个题需要注意的是还需初始化区间为长度为2的值，否则会听取wa声一片。这是由于如果$i+1$和$l-1$这个要保证至少相等即区间唯$1$。

下面附上代码

```c++
#include<cstdio>
#include<cstring>
#include<iostream> 
using namespace std;
#define kb 510
inline int read()
{
	int ans=0, w=1;
	char ch=getchar();
	while(ch<'0' || ch>'9')
	{
		if(ch=='-')	w=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
	{
		ans=ans*10+ch-'0';
		ch=getchar();
	}
	return ans*w;
}
int dp[kb][kb], num[kb];
void dfs(int l, int r)
{
	if(dp[l][r]!=0x3f3f3f3f) return ;
	if(num[l]==num[r])
	{
		dfs(l+1, r-1);
		dp[l][r]=dp[l+1][r-1];
	}
	for(int k=l; k<=r; k++)
	{
		dfs(l, k);dfs(k+1, r);
		dp[l][r]=min(dp[l][r], dp[l][k]+dp[k+1][r]);
	}
}
int main()
{
	int n=read();
	for(int i=1; i<=n; i++) num[i]=read();
	memset(dp, 0x3f, sizeof(dp));
	for(int i=1; i<=n; i++)	dp[i][i]=1;
	for(int i=1; i<=n; i++)	if(num[i]==num[i+1]) dp[i][i+1]=1;else dp[i][i+1]=2;
	dfs(1, n);
	printf("%d", dp[1][n]);
	return 0;
}
```

---

## 作者：SSHhh (赞：7)

对于这道题，其实就是用一个简单的区间 dp，再加上回文串的特判就可以AC。

如果不看回文串的话，这道题的 dp 方程是很好推出来的：dp[l][r]表示将 l 到 r 这一段完全消除所用的最小总代价，dp[l][r]=min(dp[l][r],dp[l][k]+dp[k+1][r]) l<=k<=r。但是有回文串的存在，不能直接转移，我们就只能试着推推结论。

不难发现，在消去一个回文串(或者在其中消去一部分后可以成为回文串的区间)的过程中，首先满足一个性质：如果已经是回文串了(或需要消去的部分包含端点)，那么直接将其消去即可；否则，在它的两端一定存在若干个字符相同，并且将他们忽略不会影响答案，这些字符就可以愉快的忽略了。(^_^)

有了这些性质后，我们就可以得出：每一段区间消去两端相同字符后都可以由几个可以被上述方法处理成回文串的区间组成，这也就同时证明了该 dp 方程的正确性。不过，这个 dp 方程因为使用的位置较少，包含从两端忽略字符的操作，所以最好用记忆化搜索去实现，复杂度 n²。

所以 dp 方程就是：

dp[l][r]=dp[l+1][r-1]; (a[l]==a[r])

dp[l][r]=min(dp[l][r],dp[l][k]+dp[k+1][r]);

下面附上代码：
```cpp
#include<iostream>
#define INF 2147483647
using namespace std;
int n,a[505],dp[505][505];
int dfs(int l,int r)
{
	if(dp[l][r]!=INF)	return dp[l][r];
	if(l==r)	return dp[l][r]=1;	//初始化
	else if(l==r-1)	return dp[l][r]=(a[l]==a[r]?1:2);	//初始化
	if(a[l]==a[r])	dp[l][r]=dfs(l+1,r-1);	//左右各忽略一个字符
	for(int k=l;k<=r-1;k++)
		dp[l][r]=min(dp[l][r],dfs(l,k)+dfs(k+1,r));	//转移
	return dp[l][r];
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>a[i];
	for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++)
			dp[i][j]=INF;
	cout<<dfs(1,n);
	return 0;
}
```

---

## 作者：AmamiyaYuuko (赞：5)

题目大意：给出序列，每次可以删去一个序列的一个回文串，求删空子序列的最小次数。

典型的区间 dp...

设 $f(i, j)$ 表示删完区间 $[i, j]$ 的最小花费。初始化 $f = \infty, f(i, i) = 1$。

如果 $a_i = a_j$，那么可以在删除区间 $[i + 1, j - 1]$ 时可以一起把 $i, j$ 也删掉，所以 $f(i, j) = f(i + 1, j - 1)$。

特别地，如果 $j = i + 1$ 并且 $a_i = a_j$，那么这个区间是回文的，可以一次删去。

最后枚举断点，然后计算出将区间分割成两个区间分别删去所需花费的最小值即可。

然后就可以愉快地进行 dp 了。

最后答案即为 $f(1, n)$。

状态转移方程：

 $\begin{cases}f(i, i + 1)=1(a_i = a_{i + 1})\\f(i, j) = f(i + 1, j - 1)(a_i = a_j)\\f(i, j) = \min(f(i, k) + f(k + 1, j))(k \in [i, j ))\end{cases}$ 
 
 代码
 
 ```cpp
 #include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

template <class T>
inline void read(T &x)
{
    x = 0;
    int f = 0;
    char ch = getchar();
    while (!isdigit(ch))    { f |= ch == '-'; ch = getchar(); }
    while (isdigit(ch))     { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
    x = f ? -x : x;
    return;
}

int f[510][510];
int a[510];
int n;

int main()
{
    memset(f, 0x3f3f3f3f, sizeof(f));
    read(n);
    for (int i = 1; i <= n; ++i)    read(a[i]), f[i][i] = 1;
    for (int k = 2; k <= n; ++k) // 枚举区间长度
    {
        for (int i = 1; i + k - 1 <= n && i <= n; ++i) // 枚举左端点
        {
            int j = i + k - 1; // 算出右端点
            if (a[i] == a[j])   
            {
                if (i + 1 == j) f[i][j] = 1;
                else    f[i][j] = f[i + 1][j - 1];
            }
            for (int l = i; l < j; ++l)
                f[i][j] = std::min(f[i][j], f[i][l] + f[l + 1][j]); // 枚举断点，更新答案
        }
    }
    printf("%d\n", f[1][n]);
    return 0;
}
 ```



---

## 作者：__Hacheylight__ (赞：5)

题意:

给出一个全部由数字组成的字符串,

在这个字符串中如果有一个子串是回文串那么就可以移除,

问至少要移除多少次,

才能把这个字符串全部移除


题解:

区间dp,对于区间[i,j],如果a[i]==a[j],那么dp[i][j]==dp[i+1][j-1],

因为区间[i+1,j-1]一定能移除到一定程度与边界2个构成回文串,

但是要注意,如果区间长度等于2时,dp[i][j]应该是等于1

并且有状态转移方程

dp[i][i+len-1]=min(dp[i][i+len-1],dp[i][k]+dp[k+1][i+len-1]) (2<=len<=n,i<=k<i+len-1)

代码：
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define N 1010
int dp[N][N] ;//dp[i][j]表示截了j次，截到i 
int a[N] ;
int n ;
int main(){
	scanf("%d",&n) ;
	for (int i=1;i<=n;i++) scanf("%d",&a[i]) ;
	for (int j=1;j<=n;j++){ //枚举隔断的次数 
		for (int i=1;i<=j;i++){ //枚举左端点 
			dp[i][j]=dp[i][j-1]+1 ;
			for (int k=i;k<j;k++)  
			if (a[j]==a[k]) dp[i][j]=min(dp[i][j],dp[i][k-1]+max(dp[k+1][j-1],1)) ;
		}
	}
	printf("%d\n",dp[1][n]) ;
} 
```

---

## 作者：wtyqwq (赞：2)

- [CF607B Zuma](https://www.luogu.com.cn/problem/CF607B)

- 解题思路：

  考虑区间 $\text{DP}$ 的解法。令 $f(i, j)$ 表示消去 $a_i \sim a_j$ 所需要的最短时间。状态转移方程：
  
  $$f(i, j) = \min\{f(i, j), f(i, k) + f(k + 1, j)\ | \ k\in [i, j - 1], 1\le i < j \le n\}$$
  
  $$f(i, j) = \min\{f(i, j), f(i + 1, j - 1) \ | \ 1\le i < j \le n,a_i = a_j\}$$
  
  注意：在上面转移方程中，第二个式子里 $f(i,j)$ 的初始值，为按照第一个式子已经转移完成后，得到的 $f(i, j)$ 的值，而不应是 $\infty$。可自行造数据理解这句话。
  
  初始状态为：
  
  $$f(i, i) = f(i, i - 1) = 1,i\in [1, n]$$
  
  $$f(i, j) = \infty,1\le i < j \le n$$
  
  目标状态为：$f(1, n)$。
  
------------
```cpp
#include <stdio.h>
#define N 505
#define INF 0x3F3F3F3F
int f[N][N], n, a[N];
int min(int a, int b) { return a < b ? a : b; }
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		f[i][i] = f[i][i - 1] = 1;
	}
	for (int l = 2; l <= n; ++l) {
		for (int i = 1, j; (j = i + l - 1) <= n; ++i) {
			f[i][j] = INF;
			if (a[i] == a[j])
				f[i][j] = f[i + 1][j - 1];
			for (int k = i; k < j; ++k) f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
		}
	}
	printf("%d\n", f[1][n]);
	return 0;
}
```
- 算法标签：区间动态规划。

- 时间复杂度：$O(n^3)$。

- 空间复杂度：$O(n^2)$。

- 期望得分：$100$ 分。[提交记录](https://www.luogu.com.cn/record/33991442)。

---

## 作者：hater (赞：1)

来补一篇题解

很有 **水** 准的一道区间DP

数据 500 加上这句话 

**每当一个子串被删除后，剩余的宝石将连接在一起**

用脚指头想出来是 区间DP n^3 算法

f [ i ] [ j ] 表示 i ~ j 和并所需的最少时间

这段子串的消除可以分为两个子任务

特殊的 如果这个任务前后两个颜色相同

可以直接看做回文 直接转移

min max 函数别打错 枚举区间注意范围

怕出锅的OIER可以先做完 长度为 1 2 的子任务


```cpp
#include <bits/stdc++.h>
#define LL long long 
#define MAXN 505 
#define INF 0x7f7f7f7f 
#define IL inline 
using namespace std;
LL f[MAXN][MAXN] , a[MAXN] , n ;
IL LL min(LL A , LL B)
{
	if(A > B) return B ;
	  return A ;
}
int main()
{
	cin >> n;
	for(int i = 1; i <= n; i ++) 
	  cin >> a[i] ;
	for(int i = 1; i <= n; i++)
	{
		f[i][i] = 1 ;
		if(a[i] == a[i-1]) f[i-1][i] = 1;
		  else f[i-1][i] = 2;
	}
	for(int L = 3; L <= n; L++)
	  for(int i = 1; i + L -1 <= n; i++)
	   {
	   	  int j = i + L -1 ;
	   	  f[i][j] = INF ;
	   	  if(a[i] == a[j]) 
	   	    f[i][j] = f[i+1][j-1]  ;
	   	   for(int k = i ;k < j; k++)  
	   	     f[i][j] = min (f[i][j] , f[i][k] + f[k+1][j]) ;
	   }
	cout << f[1][n] << endl;
	return 0; 
}
```

~~突然发现自己的马蜂开始变化~~

---

## 作者：cirnovsky (赞：1)

## 前言

不知为何我感觉这篇题解的 $\LaTeX$ 容易崩，崩了的话上面去我的洛谷博客查看吧。

## 题意简述

给你一个长度为 $n$ 的序列，每次你可以删除一回文串，问最少多少步能把这个序列删干净。

## 题解

考虑区间dp。

状态定义很显然：$dp_{i,j}$ 表示删除区间 $[i,j]$ 的最少步数。

那么状态的转移也很简单了。

$$
dp_{i,j}=dp_{i+1,j-1},a_{i}=a_{j}
$$

$$
dp_{i,j}=\min_{i\le k\le j}\{dp_{i,j},dp_{i,k}+dp_{k+1,j}\}
$$

边界也很显然。

$$
dp_{i,i}=1
$$

$$
dp_{i,i+1}=1+[a_{i}\neq a_{i+1}]
$$

最终答案就是 $dp_{1,n}$

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int MAXN = 5e2 + 5;
int n, a[MAXN], dp[MAXN][MAXN];

signed main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int i = 1; i <= n; ++i) dp[i][i] = 1;
	for (int i = 1; i < n; ++i) dp[i][i + 1] = 1 + (a[i] != a[i + 1]);
	for (int dis = 3; dis <= n; ++dis) {
		for (int l = 1, r = dis; r <= n; ++l, ++r) {
			dp[l][r] = 0x3f3f3f3f;
			if (a[l] == a[r]) dp[l][r] = dp[l + 1][r - 1];
			for (int k = l; k <= r; ++k) dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r]);
		}
	}
	printf("%d\n", dp[1][n]);
	return 0;
}
```

---

## 作者：xukuan (赞：1)

# 区间dp

令f[l][r]表示左区间为l右区间为r时的最小取次数

毫无疑问，当l==r时，f[l][r]=1;

我们从样例开始分析


#### 样例1：

因为a[1]==a[3]

所以f[1][3]=f[2][2]

由此可得方程1：if(a[l]==a[r]) f[l][r]=f[l+1][r-1]


##### 样例2：

没什么好分析的

### 样例3（最关键的）：

方程2：f[l][r]=f[l][k]+f[k+1][r](l<=k<r)

同时：

方程3：if(l==r-1) f[l][r]=a[l]==a[r]?1:2;


综合一下，就可以上代码了

我用递归实现

```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF 2147483647
using namespace std;

ll f[510][510],a[510],n;

void dfs(ll l,ll r){
	if(f[l][r]!=INF) return;
	if(l==r){
		f[l][r]=1;//初始化
		return;
	}
	if(l==r-1){
		f[l][r]=a[l]==a[r]?1:2;//方程3
		return;
	}
	if(a[l]==a[r]){
		dfs(l+1,r-1);
		f[l][r]=f[l+1][r-1];//方程1
	}
	for(ll k=l; k<r; k++){
		dfs(l,k);
		dfs(k+1,r);
		f[l][r]=min(f[l][r],f[l][k]+f[k+1][r]);//方程2
	}
}

int main(){
	scanf("%lld",&n);
	for(ll i=1; i<=n; i++) scanf("%lld",&a[i]);
	for(ll i=0; i<=n; i++){
		for(ll j=0; j<=n; j++)
			f[i][j]=INF;
	}
	dfs(1,n);
	printf("%lld",f[1][n]);
	return 0;
}
```

---

## 作者：Azuree (赞：0)

题目大意：

从一个序列中每次取出一个回文串，剩余部分拼起来形成一个新的序列，问取几次能把这个序列取完。

---

这道题我们可以用区间DP的方法去解决。

若$a[1,n]$为题目给出的序列，用$f[i][j]$表示将区间$[i,j]$中的数取完需要的最少的次数，那么显然$f[i][i]=1$，且当$a[i]=a[j]$时$f[i][i+1]=1$，当$a[i] \neq a[i+1]$时$f[i][i+1]=2$。有用我们再后续进行动态规划时更新的最短的区间长度为$3$，所以$f[i][i]$和$f[i][i+1]$两种情况需要特殊处理。

在更新$f[i][j]$时，最简单的思路就是把$f[i][j]$分成$f[i][k]$和$f[k+1][j]$两部分进行处理（其中$k \in [i,j)$），即

$$f[i][j]=\min (f[i][j],f[i][k]+f[k+1][j]),k \in [i,j)$$

而对于$a[i]=a[j]$的情况，当区间$[i+1,j-1]$还剩最后一个可以一次取出的序列$b$时（显然$b$是回文的），我们可以将$a[i]$、$a[j]$和$b$组成一个新的回文串同时取出（即组成$a[i]\ b\ a[j]$），从而我们可知当$a[i]=a[j]$时，

$$f[i][j]=\min (f[i][j],f[i+1][j-1])$$

然后根据上述两式DP即可。

code:

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define ll long long
#define INF 1000000009
#define qwq printf("qwq\n");

using namespace std;

int read() {
    register int x = 0,f = 1;register char ch;
    ch = getchar();
    while(ch > '9' || ch < '0'){if(ch == '-') f = -f;ch = getchar();}
    while(ch <= '9' && ch >= '0'){x = x * 10 + ch - 48;ch = getchar();}
    return x * f;
}

int n,a[505],f[505][505];

int main() {
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) 
			f[i][j] = INF;
	for(int i = 1; i <= n; i++) f[i][i] = 1, f[i][i + 1] = 1;
	for(int i = 1; i < n; i++) if(a[i] != a[i + 1]) f[i][i + 1]++;
	for(int i = 3; i <= n; i++)
		for(int j = 1; j <= n - i + 1; j++) {
			int l = j, r = j + i - 1;
			if(a[l] == a[r]) f[l][r] = f[l + 1][r - 1];
			for(int k = l; k < r; k++) f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r]);
		}
	printf("%d\n", f[1][n]);
    return 0;
}
```


---

## 作者：Push_Y (赞：0)

由于我是在官方题单里按顺序~~水~~的题目，区间dp题单里的前一题[P4170 [CQOI2007]涂色](https://www.luogu.com.cn/problem/P4170)给我这一题了一些启发（说白了就是几乎一道题），大家可以去做做那道题。


------------

按照动态规划的基本策略

### 表示所求值

用$f[i][j]$表示区间$[i,j]$的最小花费

那么所求值就是$f[1][n]$

### 状态转移方程

- $c[i]==c[j]$，那么就可以两端往里缩一位

	即$f[i][j]=f[i+1][j-1]$

- 另外，在区间$[i,j)$枚举$k$

	$f[i][j]=min(f[i][j],f[i][k]+f[k+1][j])$
    
### 预处理

~~虽然不知道预处理的定义是什么~~

显然$f[i][i]=1$

再把区间长度为2的也初始化掉

- 如果$c[i]==c[i+1]$，那么$f[i][i+1]=1$

- 否则，$f[i][i+1]=2$

按照有位大佬的题解里的写法，可以简写成
```cpp
for(int i=1;i<n;i++)f[i][i+1]=1+(c[i]!=c[i+1]);
```


------------

### CODE

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int gin(){//快读
	char c=getchar();
	int s=0,f=1;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		s=(s<<3)+(s<<1)+(c^48);
		c=getchar();
	}
	return s*f;
}

int n,f[505][505],c[505];

int main(){
	n=gin();
	memset(f,127,sizeof(f));//初始值赋大
	for(int i=1;i<=n;i++)c[i]=gin(),f[i][i]=1;
	for(int i=1;i<n;i++)f[i][i+1]=1+(c[i]!=c[i+1]);
	for(int t=2;t<n;t++)
		for(int i=1;i+t<=n;i++){
			int j=i+t;
			if(c[i]==c[j])f[i][j]=f[i+1][j-1];
			for(int k=i;k<j;k++)
				f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]);
		}
	printf("%d\n",f[1][n]);
	return 0;
}

```


------------

 _给管理：这道题思路比较确定，所以本题解的解法可能与其他题解类似。但这篇题解我写得比较详细，个人认为很容易理解，望过审核。_ 

---

## 作者：Suoh_Mikoto (赞：0)

### F[i][j]:表示i-j区间最短时间

### 状态转移方程

## **F[i][j]=min(F[i][k]+F[k+1][j]);**
## **if(a[i] == a[j])|F[i][j]=F[i+1][j-1]**

```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#define IL inline
using namespace std;
const int MAXN=600;
const int inf=0x3f3f3f3f;
IL int read(){
    int x=0,f=1;char c=getchar();
    while(c>'9' || c<'0')	{if(c=='-') f=-1;c=getchar();}
    while(c>='0' && c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
    return x*f;
}
int f[MAXN][MAXN],n;
int a[MAXN];
int dp(int l, int r){
    if(l==r)	return f[l][r]=1;
    if(f[l][r]!=inf)	return f[l][r];
    if(a[l]==a[r])	f[l][r]=r-l==1 ? 1:dp(l+1,r-1);
    for(int k=l;k<r;k++)
        f[l][r]=min(f[l][r],dp(l,k)+dp(k+1,r));
    return f[l][r];
}
int main(){
    n=read();
    memset(f,0x3f,sizeof(f));
    for(int i=1;i<=n;i++)	a[i]=read();
    printf("%d\n",dp(1,n));
    return 0;
}
```

---

