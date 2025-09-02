# [USACO08OCT] Building A Fence G

## 题目背景

勤奋的 Farmer John 想要建造一个由四面围成的栅栏来关住那些奶牛。他现在有一块长度为$N$（$4 \leq N \leq 2,500$）的长木板，他需要把这块长木板切成边长均为正整数的四块，使得他能建造一个栅栏。 

## 题目描述

请问他有多少种不同的切割方式能使切割出来的木板围成一个四面的栅栏。 

注意： 

1. 不要考虑对称性的问题，不需要去除对称的方案和类似的复杂问题；
2. 栅栏围成的面积必须大于 0；
3. 结果可以用 32 位整数存储。

## 说明/提示

Farmer John 有 10 种方法将木板分成四块：
- (1, 1, 1 ,3);
- (1, 1, 2, 2); 
- (1, 1, 3, 1); 
- (1, 2, 1, 2); 
- (1, 2, 2, 1); 
- (1, 3, 1, 1); 
- (2, 1, 1, 2); 
- (2, 1, 2, 1); 
- (2, 2, 1, 1);
- (3, 1, 1, 1)。

其中有四种情况是不能围成一个四边形的：
- (1, 1, 1, 3),
- (1, 1, 3, 1),
- (1, 3, 1, 1),
- (3, 1, 1, 1)。

## 样例 #1

### 输入

```
6```

### 输出

```
6```

# 题解

## 作者：BqtMtsZDnlpsT (赞：8)

[传送门](https://www.luogu.com.cn/problem/P6184)

- 本题思路：~~暴 力 出 奇 迹~~。
	1. 首先设四条边长分别为 $a , b , c , d$ 且 $a \ge b \ge c \ge d$。

	1. 由初二所学内容可以发现 $a$ 的取值范围为是 $ \left \lceil \frac{N}{4}\right \rceil\le a < \left \lceil \frac{N}{2}\right \rceil $(下面一些题解上好像写 $a < \left \lfloor \frac{N}{2}\right \rfloor$，但是仔细一想就会发现，当 $a$ 为奇数时后者是错的)
    
    1. $\because\left\{\begin{matrix}b+c+d=N-a\\b \ge c\ge d\\ b \le a\end{matrix}\right.\; \therefore \left\lceil\frac{N-a}{3}\right \rceil \le b \le a$
    
    1. 同理，得 $\left\lceil\frac{N-a-b}{2}\right \rceil \le c \le b$。
    
    1. 所以，若求出 $a,b,c$，就可以得到 $d=N-a-b-c$。
    
- 所以，3重循环枚举 $a,b,c$，再根据 $a,b,c$ 算出 $d$。
- 由于要考虑顺序，~~手动枚举~~可以发现：

 
	| 情况 | 种数 |
	| :----------: | :----------: | :----------: |
	| $a=b=c=d$ | $1$ |
	| $a=b=c$ 或 $b=c=d$ | $4$ |
	| $a=b$ 且 $c=d$ | $6$ |
	| $a=b$ 或 $b=c$ 或 $c=d$ | $12$ |
	| $a>b>c>d$ | $24$ |

- 几个注意点

	1. 循环过程中 $d$ 的值计算出来可能小于等于 $0$，此时可以直接退出循环（因为 $c$ 的值还在变大）。
    1. $d$ 的值计算出来可能大于 $c$，不符合定义，此时不能退出循环（因为 $c$ 的值变大后 $d$ 会变小）。
- 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int n,s;
int S(int a,int b,int c,int d)//计算情况数
{
	if(a==b&&a==c&&a==d)return 1;
	if((a==b&&a==c)||(b==c&&c==d))return 4;
	if(a==b&&c==d)return 6;
	if(a==b||b==c||c==d)return 12;
	return 24;
}
int main()
{
	scanf("%d",&n);
	for(int i=(n+3)/4;i<(n+1)/2;i++)//i对应a
		for(int j=(n-i+2)/3;j<=i;j++)//j对应b
			for(int k=(n-i-j+1)/2;k<=j;k++)//k对应c
			{
				int l=n-i-j-k;//计算d
				if(l<=0)break;
				if(l>k)continue;
				s+=S(i,j,k,l);
			}
	printf("%d",s);
}
```
- [AC记录](https://www.luogu.com.cn/record/46655207)

---

## 作者：神眷之樱花 (赞：6)

### 解析
因为切好后的木板要拼成一个四边形，所以最长的那条边不能超过总长度的一半向下取整，而且这道题不需要考虑对称性的问题，所以自然地我们很容易想到dp,而且这道题数据范围很小，一般的dp就能过，都不用优化。
### 状态转移方程
```cpp
dp[i][j] += dp[i - 1][j - k];
//设dp[i][j]表示已经切了i块木板，总长度为j的方案数
//自然dp[0][0] = 1
//dp[i][j] = dp[i - 1][j - k](1 <= k <= min(j,(n - 1) / 2)
//k的边界值是为了保证能拼成四边形
```

### 代码如下
```cpp
#include<cstdio>
#include<algorithm>
int dp[5][2505],n;
int main() {
	scanf("%d",&n);
	dp[0][0] = 1;
	for(int i = 1; i <= 4; i++)
		for(int j = 1; j <= n; j++)
			for(int k = 1; k <= std::min(j,(n - 1) / 2); k++)
				dp[i][j] += dp[i - 1][j - k];
	printf("%d",dp[4][n]);
	return 0;
} 
```


---

## 作者：YangHHao (赞：6)

### 题意简述

给正整数 $n$，求边长为整数且和为 $n$ 的四边形总数

看了一圈居然没有用数学公式的，不是 dp 就是暴力枚举。其实只要稍微推一下公式就可以 $\large O(1)$ 稳过

### 题解

纯组合推导，无需 OI 知识（误）

首先，我们分出 4 个数和为 $n$ 共有 $\large C_{n-1}^{3}$ 种分法，用小学学的插板法易证

考虑减去不合法方案数

因为上面分法中一个方案不合法当且仅当 4 个数中存在一个 $x$，使得$n-x \le x$，即 $x \ge \left \lceil \dfrac{n}{2} \right \rceil $

而当存在两个这样的 $x$ 时，总和大于 $n$，矛盾！

故只存在一个这样的 $x$

不妨设第一个为 $x$，则剩下的总和为 $n-x$，再次利用插板法，得此时方案数为 $\large C_{n-x-1}^{2}$

故答案为 $\large C_{n-1}^{3} - 4\sum\limits_{i=2}^{\left \lfloor  \frac{n}{2} \right \rfloor -1 } C_{i}^{2}$

带入平方和求和公式和等差数列求和公式即可

代码只有 6 行

### 代码实现
```cpp
#include<iostream>
int n;
signed main(){
	std::cin>>n;
	std::cout<<(n-1)*(n-2)*(n-3)/6-(n/2-1)*(n/2)*(n/2*2-1)/3+2+(n/2+1)*(n/2-2)<<'\n';
}

```


---

## 作者：Otue (赞：4)

本蒟蒻完全看不懂大家的数学推导，于是我慢慢献出 $O(4n)$ 的超快 dp 做法。

## 引理
**引理：构成四边形条件：任意一边长度小于周长除二。**   

**证明：** 设四边为 $a,b,c,d$，周长为 $S$，因为有 $a < b+c+d$，所以 $2\times a < a+b+c+d = S$，所以 $a<\dfrac{S}{2}$。
## 动规设计
设 $f_{i,j}$ 表示切割出了 $i$ 块木板，这 $i$ 块木板总长为 $j$ 的方案数。

显然可得方程：$f_{i,j}=∑f_{i-1,j-k}$。

代码如下：
```c++
len = (n + 1) / 2 - 1;
for (int i = 1; i <= 4; i++)
    for (int j = 1; j <= n; j++)
        for (int k = 1; k <= min(len, j); k++) f[i][j] += f[i - 1][j - k];
```
但是这个时间复杂度 $O(4n^2)$，虽然勉强能过，但是太慢了，于是考虑前缀和优化：

设 $sum_{i,j}=∑f_{i,k}$，则有如下代码：

```c++
#include <bits/stdc++.h> 
using namespace std;

#define int long long
const int N = 1e5 + 5;
int n, dp[5][N], sum[5][N];

// 若还不清楚，请看如下推导
//sum[i][j]=f[i][1]+...+f[i][j]
//f[i-1][j-k]+f[i-1][j-k+1]+…+f[i-1][j-1]=sum[i-1][j-1]-sum[i-1][j-k-1]，其中k=min(j,(n+1)/2-1);

signed main() {
	cin >> n;
	dp[0][0] = 1;
	for (int i = 0; i <= n; i++) sum[0][i] = 1;
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= n; j++) {
			if (j - (n + 1) / 2 < 0) dp[i][j] = sum[i - 1][j - 1];
			else dp[i][j] = sum[i - 1][j - 1] - sum[i - 1][j - (n + 1) / 2];  
			sum[i][j] = sum[i][j - 1] + dp[i][j];
		}
	}
	cout << dp[4][n] << endl;
}
```

---

## 作者：Ciaxin_ (赞：4)

# 方法是找规律
在经过三重循环暴力枚举后，
发现了在每个数据之间极其微妙的关系：

当 $n=4$ 和 $n=5$ 时，两者相差为 $3$。

当 $n=5$ 和 $n=6$ 时，两者相差为 $2$。

当 $n=6$ 和 $n=7$ 时，两者相差为 $10$。

当 $n=7$ 和 $n=8$ 时，两者相差为 $3$。

当 $n=8$ 和 $n=9$ 时，两者相差为 $21$。

当 $n=9$ 和 $n=10$ 时，两者相差为 $4$。

………………

当然如果这样还是看不出来，

那我们就换一种方法看看
```
    	//假设3前面有1,那么
    3	//1*(1*2+1)=3
2  10	//2*(2*2+1)=10
3  21	//3*(3*2+1)=21
4  36	//4*(4*2+1)=36
…………
```
通过这种方法可以求出差值，
那么用前一个数加上这两个数的差值就珂以得出这个数啦
### 上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m[100010];// n  存放差值 
long long sm[100010];// 存放每个的方案数 
long long cnt=2;	//计数器 
long long tot=1; 	//计数器 
int main()
{
	scanf("%lld",&n);
	for(long long i=4;i<=n;i++,tot++)
	{
		m[++cnt]=tot; 
		m[++cnt]=tot*(tot*2+1);//计算差值
	}
	sm[4]=1;//当n=4时方案数为 1 
	for(long long i=5;i<=n;i++)
	{
		sm[i]=sm[i-1]+m[i-1];//计算方案数
	}
	printf("%lld",sm[n]);
	return 0;
}
```

---

## 作者：wuyonghuming (赞：4)

## 思路：
这道题可以用暴力循环拿到部分的分数。
## 过程：
枚举每一个可能的长度，如果可以形成一个矩形，答案加一。
## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n,ans=0;
    cin>>n;
    for(int i=1;i<=n;i++)
		for(int j=1;j<=n-i;j++)
			for(int k=1;k<=n-i-j;k++)
				for(int l=1;l<=n-i-j-k;l++)
					if(max(max(max(i,j),k),l)<n-max(max(max(i,j),k),l)&&i+j+k+l==n)//判断，当方形最长的一条边的长度小于另外三条，答案加一
						ans++;
	cout<<ans;
	return 0;
} 
```
当然，会**时间超限**。

接着可以把一部分的答案输出来。

现在我把我的答案显示在这里，我先用$s$来表示答案。
### $s_1=0,s_2=0,s_3=0,s_4=1,s_5=4$
### $s_6=6,s_7=16,s_8=19,s_9=40,s_{10}=44$
### $s_{11}=80,s_{12}=85,s_{13}=140,s_{14}=146$
接着我再用$s$,来表示和上一项的差。
### $s_1=0,s_2=0,s_3=0,s_4=1,s_5=3$
### $s_6=2,s_7=10,s_8=3,s_9=21,s_{10}=4$
### $s_{11}=36,s_{12}=5,s_{13}=55,s_{14}=6$
如果没有发现规律，可以用下面代码来看一看答案。

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int hanshu(int n)
{
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n-i;j++)
			for(int k=1;k<=n-i-j;k++)
				for(int l=1;l<=n-i-j-k;l++)
					if(max(max(max(i,j),k),l)<n-max(max(max(i,j),k),l)&&i+j+k+l==n)
						ans++;
	return ans;
}
int main()
{
    for(int n=1;n<=100;n++)
    {
		cout<<setw(10)<<hanshu(n);
		if(n%10==0)
		{
			cout<<endl;
		}
	}
	for(int n=1;n<=100;n++)
    {
		cout<<setw(10)<<hanshu(n)-hanshu(n-1);
		if(n%10==0)
		{
			cout<<endl;
		}
	}
	return 0;
} 
```
现在，我们发现了**规律**：

当$i$为**偶数**时：

$s_i=s_{i-1}+(i/2-1)$

当$i$为**奇数**时，我先用$c$来表示它和上一项的差：

$c_i=c_{i-1}+(i/2-1)×4-1$

$s_i=s_{i-1}+c_i$

最后就是

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n,ans,s=0;
    cin>>n;
    for(int i=4;i<=n;i++)
	{
		if(i%2==0)
		{
			ans=ans+(i/2-1);//只要上一项的所以用一个变量就行了
		}
		else
		{
			s+=(i/2-1)*4-1;//只要上一项的所以用一个变量就行了
			ans=ans+s;//只要上一项的所以用一个变量就行了
		}
	}
	cout<<ans;
	return 0;
} 
```

谢谢观看，希望大家能看懂。

---

## 作者：DP王子 (赞：2)

这题居然没有一篇 dp 题解，唯一的题解居然是找规律。所以我来水一发。

首先理解题意，要摆出四边形，只需满足最大的木棒长度小于 $\lfloor\dfrac{n}{2} \rfloor$。

我们可以令 $dp[i][j]$ 表示用 $i$ 根木棒，总长度为 $j$。枚举 $k$ 为这一次拿的木棒长度。那么很容易推出转移方程：

$$dp[i][j]=\sum_{k=1}^{min(j,\lfloor\frac{n}{2} \rfloor)}dp[i-1][j-k]$$

所以我们就通过了本题。附上代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int dp[5][3000];
int main()
{
	cin >> n;
	dp[0][0]=1;
	for (int i=1;i<=4;i++)
	{
		for (int j=1;j<=n;j++)
		{
			for (int k=1;k<=min(j,(n-1)/2);k++)
			{
				dp[i][j]+=dp[i-1][j-k];
			}
		}	
	}
	cout << dp[4][n];
	return 0;
}
```

但是我们依旧可以考虑优化。注意到这个方程只与 $i$ 上一位有关，因此很显然可以滚动掉。虽然没有什么作用。

我们继续考虑。既然只与上一位有关，并且要求的是一个和的形式，那么我们考虑前缀和优化。维护 $dp$ 数组的前缀和即可。给一下代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int dp[2505],sum[2505];
int main()
{
	cin >> n;
	for (int i=0;i<=n;i++) sum[i]=1;
	for (int i=1;i<=4;i++)
	{
		for (int j=1;j<=n;j++) 
		{
			if (j-1-min(j,(n-1)/2)>=0)dp[j]=sum[j-1]-sum[j-1-min(j,(n-1)/2)];//这个if的目的是为了不访问到下标为1的地方
			else dp[j]=sum[j-1];
		}
		sum[0]=0;
		for (int j=1;j<=n;j++) sum[j]=sum[j-1]+dp[j];
	}
	cout << dp[n];
	return 0;
}
```


---

## 作者：漠寒 (赞：0)

## 分析

题意就是将给定的 $N$ 分为四块作为一个四边形的四条边长，因此可以得到一个信息，最大的一条边长最大必须小于 $n$ 的一半（类比于三角形两边之和大于第三边），此前提下才能保证四条边能形成四边形。

想到 $dp$，对于现在连接第 $i$ 条边时，先枚举连出这条边后的总长度 $j$，再去枚举本次我们要连接一条多长的边，令为 $k$，因此新连上这条边后，$dp(i,j)$ 就要加上上一条边连接后拥有的方案数，即加上 $dp(i-1,j-k)$，至此此题得解，注意方案数仅有加计算，将 $dp(0,0)$ 初始赋值为1即可。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
int n,f[5][2555];
inline int min(int x,int y){
	return x<y?x:y;
}
int main()
{
	cin>>n;
	f[0][0]=1;//初始化 
	for(int i=1;i<=4;i++){
		for(int j=1;j<=n;j++){
			for(int k=1;k<=min(j,(n-1/2));k++)//取最小，保证新加的边不会大于等于总长度的一半 
				f[i][j]+=f[i-1][j-k];//累计 
		}
	}
	cout<<f[4][n]<<endl;
	return 0;
}
```


---

## 作者：_Imaginary_ (赞：0)

PS：可能题解长度会极其短。

首先，让我们考虑一下什么时候能构成四边形。

设周长为S，四条边长顺次为 $a,b,c,d$ ,并且 $a$ 最长。

那么：
$$a<b+c+d,\ \ \ 2a<a+b+c+d=S
$$
所以 $a<\lfloor\frac{S}{2}\rfloor$ 。

接下来让我们看看数据范围.

$n\le2500$，容易想到 $O(n)$ 或 $O(n^2)$ 。

所以，依旧是根据 _不会的题都用_ **dp** _的神奇理论_ ，这道题也用dp。

令 $dp[i][j]$ 表示已经取了i根，最长的为j中的情况数，

$$
dp[i][j]=\sum\limits_{now=1}^{\min\{\lfloor \frac{tot\_length}{2}\rfloor,j\}}dp[i-1][j-now]
$$

那么答案要求的就是 $\min\limits_{\lfloor \frac{n}{4}\rfloor\le i\le\frac{n}{2}}\{dp[4][i]\}$。

~~完结撒花~~

---

