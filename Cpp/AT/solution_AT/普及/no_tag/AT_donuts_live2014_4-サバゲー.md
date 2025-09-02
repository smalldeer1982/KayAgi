# サバゲー

## 题目描述

[problemUrl]: https://atcoder.jp/contests/donuts-live2014/tasks/donuts_live2014_4

パンチくんが運営している会社では、サバイバルゲームが大流行りです。

通常のサバイバルゲームはチームが $ 2 $ つですが、パンチくんは普通のゲームに飽きてしまったため、多くのチームで対戦することにしました。

参加人数と、チームの数が与えられるので、チームの分け方が何パターンあるか求めて下さい。

ただし、各参加者は必ずどれか $ 1 $ つだけのチームに所属するものとし、また $ 0 $ 人のチームがあってはならないものとします。

## 说明/提示

### 部分点

$ M\ =\ 2 $ を満たすテストケースに正解した場合、部分点として $ 40 $ 点が与えられる。

### Sample Explanation 1

$ 2 $ 人を $ 2 $ チームに分ける分け方は、 $ 1 $ 通りしかありません。

### Sample Explanation 2

$ 3 $ 人を $ 2 $ チームに分ける分け方は、 - { $ A,\ B $ }, { $ C $ } - { $ A,\ C $ }, { $ B $ } - { $ A $ }, { $ B,\ C $ } の $ 3 $ 通りです。 参加者は互いに区別がつきますが、チームは区別がつかないことに注意して下さい。 { $ A,\ B $ }, { $ C $ }と、{ $ C $ }, { $ A,\ B $ } は同じものとしてカウントします。

## 样例 #1

### 输入

```
2 2```

### 输出

```
1```

## 样例 #2

### 输入

```
3 2```

### 输出

```
3```

## 样例 #3

### 输入

```
500 2```

### 输出

```
695241506```

## 样例 #4

### 输入

```
20 10```

### 输出

```
584923236```

# 题解

## 作者：违规用户名Jx9)zIu (赞：2)

# [题目传送门](https://www.luogu.com.cn/problem/AT_donuts_live2014_4)

  容易想到组合数，但是 dp 好像更好做，就用 dp 做了。

  （一道淼 dp 我做了俩小时）。
  
  状态转移方程式如下：
  
  $dp _{1,1} =1$ , $dp_{i,j}=dp _{i-1,j-1}+dp_{i-1,j} \cdot j$ 

  $dp_{1,1}$ 一定要等于一，否则等于零结果会完全不同。

  最后的最后，只要把 $dp_{n,m}\bmod MOD$就行了。 
  时间复杂度： $O(nm)$ 。

# CODE:

```
#include<bits/stdc++.h>
using namespace std;
const long long MOD=1000000007;
long long dp[1005][1005];
void read(int &x){//快读，习惯但不必要 
	x=0; 
	int w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			w=-1;	
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-48;
		ch=getchar();
	}
	x*=w; 
}
int main(){
	int n,m;
	read(n),read(m);
	dp[1][1]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(!(i==1&&j==1)){
				dp[i][j]=(dp[i-1][j-1]+dp[i-1][j]*j)%MOD;
			}
		}
	}
	cout<<dp[n][m]%MOD<<endl;
	return 0;
}
```
血与泪的教训：十年 OI 一场空，不开 long long 见祖宗。

---


upd:修改格式，补充对解法的进一步说明。

# END

---

## 作者：_hxh (赞：2)

### 前言

~~刚开始打了一个莫名其妙的组合数模板，后面发现自己不知道在干什么~~

### 分析

题意非常简洁：有 $n$ 个人，现在要把他们划分为 $m$ 组，求不同的划分方案模 $10^9 + 7$，**人与人之间互不相同。**

刚开始你肯定会觉得这就是一道组合数的淼题，但是你突然看到：

$$2 \le M \le N \le 1000$$

噫，那行吧。组合数学肯定是不行了。那我们只能用 $\dots$ 动态规划？

尝试设计动态规划。先给出转移方程：

$$
\large dp_{i,j} \gets {\color{red} dp_{i - 1,j} \times j} + {\color{blue} dp_{i - 1,j - 1}}
$$

其中 $dp_{i,j}$ 表示把 $i$ 个人划分为 $j$ 组的方案数，则有两种情况：

1. 仍旧以原先的组数进行分配，体现为红色部分。
2. 多开一组进行分配，体现为蓝色部分。

最后加起来即可。记得初始情况 $dp_{1,1} \gets 1$。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
const long long mod = 1000000007;
int n,m;
long long f[N][N];
int main()
{
	cin >> n >> m;
	f[1][1] = 1;
	for (int i = 1;i <= n;i++)
		for (int j = 1;j <= m;j++)
			if (!(i == 1 && j == 1))
				f[i][j] = (f[i - 1][j - 1] + f[i - 1][j] * j) % mod;
	cout << f[n][m] << endl;
	return 0;
}
```

---

## 作者：lzh_juruo (赞：1)

# AT_donuts_live2014_4 サバゲー 题解

~~上来一眼想到组合数，然后调了半天才发现人与人之间互不相同。~~

考虑 dp 。设 $f_{i,j}$ 表示分了 $i$ 组和 $j$ 个人的情况总数。

如何转移：（1）这个人可以新分一个组，从 $f_{i-1,j-1}$ 转移而来。（2）这个人可以加入之前 $i$ 个组的其中之一，从 $f_{i,j-1}$ 转移而来，注意乘上 $i$。

状态转移方程 $f_{i,j}=f_{i-1,j-1}+f_{i,j-1} \times i$，边界 $f_{0,0}=1$。

AC 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
int n,m,f[1002][1002];
signed main(){
	cin>>n>>m;
	f[0][0]=1;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			f[i][j]=(f[i-1][j-1]+f[i][j-1]*i)%mod;
		}
	}
	cout<<f[m][n];
	return 0;
}
```

---

## 作者：Elairin176 (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT_donuts_live2014_4)     
淼 dp。    
## 题意
有 $n$ 个人，现在要把他们划分为 $m$ 组，求不同的划分方案模上 $10^9+7$，人与人之间互不相同。   
## 解法  
我们发现这是一道计数题。   
计数题一般可以用组合数学或 dp 解决。   
本题应该使用 dp。因为发现组合数学难以求解状态如此复杂的问题。     
那么我们设 $f_{i,j}$ 为现在有 $n$ 个人，划分为 $j$ 组的方案数。    
我们可以枚举 $i,j$ 来求它。   
有以下几种状态可以转移到这个状态：     
- 这一轮新加了一组。结果为 $f_{i-1,j-1}$。因为只增加了一组，所以我们不需要对其作任何变动。    
- 这一轮没有新加组。结果为 $f_{i-1,j}\times j$。显然这一个新加的人可以进入任何一组，根据乘法原理即可推得。     

那么总的 dp 式子就是这两项加起来。    
时间复杂度 $O(nm)$，可以通过。    
[CODE](https://atcoder.jp/contests/donuts-live2014/submissions/44687672)

---

## 作者：topcsa (赞：0)

## 题型分析

看到“划分”首先想到是组合数，但是转念一想，这题组合数明显做不了，因为人与人是不一样的，只能用 dp 来做。

## 思路

我们把 $dp_{i,j}$ 设为前 $i$ 个人分成 $j$ 组的方案数。

那么：

如果多开一组，不会有太多影响，所以是 $dp_{i-1,j-1}$。

如果加入一个人，则按照加乘原理，从上一个状态转移过来，因为一个人可以从 $j$ 个组中任选一组，所以有 $dp_{i-1,j}\times j$ 种情况。

然后将这两种情况加和，即：
$$
dp_{i,j}=dp_{i-1,j-1}+dp_{i-1,j}\times j
$$
dp 数组的初始值 $dp_{1,1}=1$，因为一个人一个组只有一种情况。

**注意：要取模一定，要开 long long，~~十年 OI 一场空，不开 long long 见祖宗~~**。

代入程序即可。

## 代码

下面是带注释的 AC 代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod = 1e9 + 7;
int dp[1010][1010];
signed main()
{
	int n, m;
	cin >> n >> m;
	dp[1][1] = 1; 
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (i != 1 || j != 1) dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j] * j) % Mod;
		}
	}
	cout << dp[n][m] % Mod;
	return 0;
}

```

## 注意

注意一下取模和 long long 的问题就可以了，我在 long long 这里卡了一会儿。

---

## 作者：_Sky_Dream_ (赞：0)

# [传送门](https://www.luogu.com.cn/problem/AT_donuts_live2014_4)

一眼 dp 题。

首先，假设 $dp_{i,j}$ 表示有 $i$ 个人在 $j$ 组中的分配情况总数。

那么，该如何推出表达式呢？

首先，可以由 $dp_{i-1,j-1}$ 直接推导过来，因为加了一人和一组。

其次，由 $dp_{i-1,j}$ 推导过来的时候，这个数要乘上 $j$，因为这个人可以加到前面 $j$ 组。

那么，完整的表达式为：$dp_{i,j}=dp_{i-1,j-1}+dp_{i-1,j}\times j$。

AC Code：

```cpp
//#pragma GCC optimize(1)
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define int long long
#define rep(i,x,y) for(register int i=x;i<=y;++i)
#define rp(i,x,y) for(register int i=x;i>=y;--i)
#define N 100005
#define MAX 1145141919810
#define mod 1000000007
using namespace std;
int n,m;
int dp[1005][1005];
inline void Enchanted(){
	srand(time(0));
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n>>m;
	dp[1][1]=1;
	rep(i,1,n)
		rep(j,1,m)
			if(i!=1||j!=1)
				dp[i][j]=(dp[i-1][j-1]+dp[i-1][j]*j)%mod;
	cout<<dp[n][m];
}
signed main(){Enchanted();return 0;}




```

---

