# Deque

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dp/tasks/dp_l

太郎君と次郎君が次のゲームで勝負します。

最初に、数列 $ a\ =\ (a_1,\ a_2,\ \ldots,\ a_N) $ が与えられます。 $ a $ が空になるまで、二人は次の操作を交互に行います。 先手は太郎君です。

- $ a $ の先頭要素または末尾要素を取り除く。 取り除いた要素を $ x $ とすると、操作を行った人は $ x $ 点を得る。

ゲーム終了時の太郎君の総得点を $ X $、次郎君の総得点を $ Y $ とします。 太郎君は $ X\ -\ Y $ を最大化しようとし、次郎君は $ X\ -\ Y $ を最小化しようとします。

二人が最適に行動すると仮定したとき、$ X\ -\ Y $ を求めてください。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 1\ \leq\ N\ \leq\ 3000 $
- $ 1\ \leq\ a_i\ \leq\ 10^9 $

### Sample Explanation 1

二人が最適に行動すると、次のように操作が行われます。 操作対象の要素を太字で表しています。 - 先手: (10, 80, 90, \*\*30\*\*) → (10, 80, 90) - 後手: (10, 80, \*\*90\*\*) → (10, 80) - 先手: (10, \*\*80\*\*) → (10) - 後手: (\*\*10\*\*) → () このとき、$ X\ =\ 30\ +\ 80\ =\ 110 $, $ Y\ =\ 90\ +\ 10\ =\ 100 $ となります。

### Sample Explanation 2

二人が最適に行動すると、例えば次のように操作が行われます。 - 先手: (\*\*10\*\*, 100, 10) → (100, 10) - 後手: (\*\*100\*\*, 10) → (10) - 先手: (\*\*10\*\*) → () このとき、$ X\ =\ 10\ +\ 10\ =\ 20 $, $ Y\ =\ 100 $ となります。

### Sample Explanation 4

答えは 32-bit 整数型に収まらない場合があります。

### Sample Explanation 5

二人が最適に行動すると、例えば次のように操作が行われます。 - 先手: (4, 2, 9, 7, 1, \*\*5\*\*) → (4, 2, 9, 7, 1) - 後手: (\*\*4\*\*, 2, 9, 7, 1) → (2, 9, 7, 1) - 先手: (2, 9, 7, \*\*1\*\*) → (2, 9, 7) - 後手: (2, 9, \*\*7\*\*) → (2, 9) - 先手: (2, \*\*9\*\*) → (2) - 後手: (\*\*2\*\*) → () このとき、$ X\ =\ 5\ +\ 1\ +\ 9\ =\ 15 $, $ Y\ =\ 4\ +\ 7\ +\ 2\ =\ 13 $ となります。

## 样例 #1

### 输入

```
4
10 80 90 30```

### 输出

```
10```

## 样例 #2

### 输入

```
3
10 100 10```

### 输出

```
-80```

## 样例 #3

### 输入

```
1
10```

### 输出

```
10```

## 样例 #4

### 输入

```
10
1000000000 1 1000000000 1 1000000000 1 1000000000 1 1000000000 1```

### 输出

```
4999999995```

## 样例 #5

### 输入

```
6
4 2 9 7 1 5```

### 输出

```
2```

# 题解

## 作者：猫猬兽 (赞：34)

来一发不一样的思路，并且时空复杂度更优。

考虑数列中存在 $3$ 个连续的数 $a_i,a_{i+1},a_{i+2}$ 满足 $a_i \le a_{i+1}$ 并且 $a_{i+1} \ge a_{i+2}$，此时一方任取两边的数，则另一方取中间的数最优，所以，这 $3$ 个数可以等效合并为 $1$ 个大小为 $a_i+a_{i+2}-a_{i+1}$ 的数。

将数列中满足条件的数等效合并完后，数列一定满足先递减后递增，此时从两端贪心即可。

时空复杂度均为 $O(n)$ ，比动态规划优。

代码如下，采用的是读入一个数立即完成合并操作。

```cpp
#include<iostream>
using namespace std;
long long b,s,t,a[100001],n,i,p,q;
int main()
{
	cin>>n;
	for(i=1;i<=n;i=i+1)
	{
		cin>>s;a[++t]=s;
		while(t>=3&&a[t-1]>=a[t-2]&&a[t-1]>=a[t]){a[t-2]=a[t]+a[t-2]-a[t-1];t=t-2;}
	}
	p=1;q=t;
	for(i=1;i<=t;i=i+1)
	{
		if(a[p]>a[q])b=b+(i%2*2-1)*a[p++];
		else b=b+(i%2*2-1)*a[q--];
	}
	cout<<b;return 0; 
}
```


---

## 作者：mcyqwq (赞：29)

考虑模拟博弈过程。

显然游戏过程中剩下的数必然是连续的一段。设 $f_{i,j}$ 表示剩下下标为 $[i,j]$ 的数时，先手（并非当前的先手而是开始时的先手，下同）能取得的最大分数差。

分两种情况讨论：

- 已经取走的数为偶数个，此时先手取，$f_{i,j}=\max(f_{i+1,j}+a_i,f_{i,j-1}+a_j)$。

- 已经取走的数为奇数个，此时后手取，$f_{i,j}=\min(f_{i+1,j}-a_i,f_{i,j-1}-a_j)$。

dp 流程与普通的区间 dp 类似，只是少了枚举区间断点的操作。时间复杂度 $O(n^2)$。

代码：

```cpp
//NOIP2021 rp++
#include <cstdio>

#define ll long long
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int N = 3005;

int n;
ll a[N], f[N][N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", a + i);
	for(int len = 1; len <= n; len++) {
		for(int i = 1; i + len - 1 <= n; i++) {
			int j = i + len - 1;
			if((n - len) & 1) f[i][j] = min(f[i + 1][j] - a[i], f[i][j - 1] - a[j]);
			else f[i][j] = max(f[i + 1][j] + a[i], f[i][j - 1] + a[j]);
		}
	}
	printf("%lld", f[1][n]);
	return 0;
}
```

---

## 作者：xvl_ (赞：11)

[题目传送门](https://www.luogu.com.cn/problem/AT_dp_l)

一道区间 $dp$ 题。

在 $dp$ 之前，我们需要明确以下几个东西：

**状态的表示**，**状态转移方程**，**边界条件**跟**答案的表示**。

### 状态的表示
定义 $sum(l,r) = \sum_{i=l}^ra_i$ 

$dp[l][r]$ 表示目前剩下的数为 $a[l] \thicksim a[r]$ 时，当前取数的人取数所能获得的最大数字和。

### 状态转移方程

$$dp[l][r]=\max\begin{cases}sum(l,r)-dp[l+1][r]\\
sum(l,r)-dp[l][r-1]\end{cases}$$

### 边界条件

$$dp[i][i] = a[i]\space (1\le i\le n)$$

### 答案的表示

$$dp[1][n]-(sum(1,n)-dp[1][n])$$

#### 最后贴上代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, ans, sum[3005], a[3005], dp[3005][3005];
signed main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0); // 优化
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i]; // 注意要用前缀和，否则会 TLE
    }
    for (int i = 1; i <= n; i++) dp[i][i] = a[i];
    for (int len = 2; len <= n; len++) {
        for (int l = 1, r = l + len - 1; r <= n; l++, r++) {
            dp[l][r] = max(sum[r] - sum[l - 1] - dp[l + 1][r], sum[r] - sum[l - 1] - dp[l][r - 1]); // 进行 dp
        }
    }
    cout << dp[1][n] - (sum[n] - dp[1][n]);
    return 0;
}
```


---

## 作者：syzxzqy (赞：8)

## [原题传送门](https://www.luogu.com.cn/problem/AT_dp_l)  
题目的意思是两人在一列数两头取数，都要取最大的和，求先者的分数-后者的分数（后面称作分数差）。  
我们知道在取数中剩下的一定是连续的，我们可以逆向思维，用区间 DP，从数列中间做起。  
一般的区间 DP 都是一个人或一个事物，这道题却有两个人，我们可以把后者的值当为负数，也就是减去这个数。  
$f_{i,j}$  表示取了第 $i$ 个到第 $j$ 个的分数差。
我们分两种讨论：  
如果当前取数的是前者，  
那么，$f_{i,j}
=\max_{(f_{i+1,j}+a_{i},f_{i,j-1}+a_{j})}$；  
后者就是 $f_{i,j}=\min_{(f_{i+1,j}-a_{i},f_{i,j-1}-a_{j})}$。   
因为前者分数不变，后者分数变大，分数差变小，也要求最小。  
时间复杂度：$O(n^2)$。  
###### 上代码
```cpp
#include<bits/stdc++.h>
#define int long long//数据爆int 
using namespace std;
int n,i,j,len,a[3001],f[3001][3001];//定义 
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(i=1;i<=n;i++)
		cin>>a[i];//输入 
	for(len=1;len<=n;len++)//枚举选的长度 
		for(i=1,j=len;j<=n;i++,j++){//枚举开头结尾 
			if((n-len)%2==0)//先者取数 
				f[i][j]=max(f[i+1][j]+a[i],f[i][j-1]+a[j]);
			else//后者取数 
				f[i][j]=min(f[i+1][j]-a[i],f[i][j-1]-a[j]);
		}
	cout<<f[1][n];//输出 
}
```

---

## 作者：Ginger_he (赞：3)

## 题目描述

给定一个队列，双方轮流按最优策略取数，每次只能从队头或队尾取出。设先手取出数的和为 $x$，后手取出数的和为 $y$，求 $x-y$。

## 题解

做完之后看到题解区里写的都是 dp，来发一个记忆化搜索的做法。

这是一道经典的 $\min-\max$ 搜索，因为求的是 $x-y$，所以还剩下奇数个数时我们要算的是 $y-x$ 的最小值，剩下偶数个数时算的是 $x-y$ 的最大值，最后用 $f_{l,r}$ 记一下答案即可。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 3005
int n;
ll a[N],f[N][N];
ll dfs(int l,int r)
{
	if(l>r) return 0;
	if(~f[l][r]) return f[l][r];
	ll res=0,u=dfs(l+1,r),v=dfs(l,r-1);
	if(n-r+l-1&1) res=min(u-a[l],v-a[r]);
	else res=max(u+a[l],v+a[r]);
	return f[l][r]=res;
}
int main()
{
	memset(f,-1,sizeof(f));
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	printf("%lld\n",dfs(1,n));
	return 0;
}
```

---

## 作者：Lates (赞：3)

区间dp。

其实就是【NOI1995】石子合并的简化版。

设 $f[i][j]$ 为区间 $[i,j]$ 的答案。

那么 

$$f[i][j]=\max\{\ f[i][k]+f[k+1][j]+\sum_{l=i}^{j}a_{i}\  \}\ (k\in[i,j))$$

$k$ 是枚举中断点。后面的和用前缀和维护。

时间复杂度 $O(n^3)$。

---

## 作者：freoepn (赞：2)

区间 dp。

设 $dp_{i,j}$ 表示只能取区间 $i$ 到 $j$ 中的数时先手能获得的最大分数。
 
$dp_{i,j}$ 等于区间中所有数的总和减去之前得到的分数。
 
之前的分数有两种不同的情况，分别为取最左边和最右边的数。
 
两种情况之前的分数分别为 $dp_{i+1,j}$ 和 $dp_{i,j-1}$。
 
因为要求答案最大，肯定要从中取最小值。

这个做法时间复杂度为 $O(N^3)$，肯定会超时。
 
我们可以先花 $O(N^2)$ 的时间预处理出每个区间中所有数字的和。
 
这样时间复杂度就变成 $O(N^2)$ 了。
 
代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, a[3005], dp[3005][3005], sum[3005][3005];
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    sum[i][i] = a[i];
    for (int j = i + 1; j <= n; j++) {
      sum[i][j] = sum[i][j - 1] + a[j];//统计区间
    }
  }
  for (int i = 1; i <= n; i++) {
    dp[i][i] = a[i];//直接选这一个数
  }
  for (int l = 1; l < n; l++) {
    for (int i = 1; i <= n - l; i++) {
      dp[i][i + l] = sum[i][i + l] - min(dp[i][i + l - 1], dp[i + 1][i + l]);//进行转移
    }
  }
  cout << dp[1][n]-(sum[1][n] - dp[1][n])<< endl;//因为题目要求的是差，所以还要把后手取的值算出来
  return 0; 
}
```


---

## 作者：scp020 (赞：1)

### 题意

给定一个长度为 $n$ 的数列，两个人可以从数列的两端取数，每个人都选取最优解，第一个人取到的数的和为 $x$，第二个人取到的数的和为 $y$，求 $x-y$。

### 解决

本题和 [这题](https://www.luogu.com.cn/problem/AT680) 有些像，区间动态规划，时间复杂度 $O(n^2)$。

$\mathit{f}_{i,j}$ 表示在从 $i$ 到 $j$ 的区间里第一个人能取到的数的和的最大值。

同时要维护一个 $sum$ 数组，$\mathit{sum}_{i,j}$ 表示在从 $i$ 到 $j$ 的区间里的数的和。

初始化过程如下：

$\mathit{f}_{i,i}=a_i$，$\mathit{sum}_{i,i}=a_i$

动态规划过程如下：

循环枚举长度 $i$，循环枚举起始位置 $j$。

$\mathit{f}_{j,i+j}=\mathit{sum}_{j,i+j}-\min(\mathit{f}_{j,i+j-1},\mathit{f}_{j+1,i+j})$

因为第一个人取到 $x=\mathit{f}_{1,n}$，而所有书的和为 $\mathit{sum}_{1,n}$，所以第二个人取到的数和为 $y=\mathit{sum}_{1,n}-\mathit{f}_{1,n}$，所以结果 $x-y=\mathit{f}_{1,n}\times 2 - \mathit{sum}_{1,n}$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[3010],f[3010][3010],sum[3010][3010];
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],sum[i][i]=a[i],f[i][i]=a[i];
	for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) sum[i][j]=sum[i][j-1]+a[j];
	for(int i=1;i<n;i++) for(int j=1;i+j<=n;j++)f[j][i+j]=sum[j][i+j]-min(f[j][i+j-1],f[j+1][i+j]);
	cout<<f[1][n]*2-sum[1][n];
	return 0;
}
```


---

## 作者：chenpengjin (赞：1)

1. 题意：

   小明希望尽可能大，小方希望尽可能小，换句话说，就相当于是他们两个都希望自己得到的分数尽可能的多。
***
2. 思路：

	首先考虑区间 dp。
    
    在这里我们设 $dp_{i,j}$ 表示区间 i 到 j 能够取得 $X - Y$ 或 $Y - X$ 的最大值。
    
    因为每次取的人都希望上一次取的那个人得到的分更小。
    
    因此，每次在进行状态转移时，我们在转移时的答案都选择减法而不是加法，就得到了状态转移方程式：
    
	> $dp_{i,j} = max(a_{i} - dp_{i + 1,j}, a_{j} - dp_{i,j - 1})$
*** 
3. 代码：

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 3e3 + 5;
int n;
long long dp[MAXN][MAXN], sum, a[MAXN];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		sum += a[i];
	}
	for (int i = 1; i <= n; i++) {
		dp[i][i] = a[i];
	}
	for (int l = 2; l <= n; l++) {
		for (int i = 1; i <= n - l + 1; i++) {
			int j = i + l - 1;
				dp[i][j] = max(a[i] - dp[i + 1][j], a[j] - dp[i][j - 1]);
		}
	}
	printf("%lld", dp[1][n]);
	return 0;
}
```



---

## 作者：_JF_ (赞：1)

## **AT4533 Deque**

前来补一篇题解。

这道题还是典型的**区间dp**。

首先它没有后效性，每个数只可以取一次。并且是从前边后者后边取的。

设 $dp[i][j]$ 表示从 $i$ 到 $j$ 的区间先手可以获得分值的最大值。

用全部的和减去先手的值，就是后手的值了。

1 $dp[i][i] =i$ (一个数的时候就只能取自身。）

2 $dp[j][i+j]=sum[j][i+j]-min(dp[j+1][i+j],dp[j][i+j-1]);$

这个方程表示当前一段的最值就是这一段总和减去头或者尾的值。$min$ 因该都会吧，就是一个数，减去的值越小，剩下就越大。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =8000;
long long a[N],sum[N][N];
long long dp[N][N];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
  	for(int i=1;i<=n;i++) 
	{
    	sum[i][i]=a[i];
    	dp[i][i]=a[i];
    	for (int j=i+1;j<=n;j++) 
      		sum[i][j]=sum[i][j-1] + a[j];
  	}
	for(int i=1;i<n;i++)
	{
		for(int j=1;j<=n-i;j++)
		{
			dp[j][i+j]=sum[j][i+j]-min(dp[j+1][i+j],dp[j][i+j-1]);
		}
	}
	cout<<dp[1][n]-(sum[1][n]-dp[1][n]);
}
```


---

## 作者：kdy20100729 (赞：1)

考虑 $A$、$B$ 两人博弈。  
设 $dp_{x,y}$ 表示只拿 $x \sim y$ 的这些数字，表示 $A-B$ 的最大得分。  
如果现在只剩最后一个数字，现在出手的人只能拿这一个数字。  
如果现在出手的人是 $A$，那么 $dp_{i,i}=a_i$。如果现在出手的人是 $B$，那么 $dp_{i,i}=-a_i$。  
如果现在有两个数字可以拿，那么现在先出手的人肯定要去判断剩一个数字的情况下是拿最左边的数字还是最右边的数字哪个好。  
假设现在是 $A$ 要拿：
> $dp_{1,2}= \max (dp_{1,1}+a_2, dp_{2,2}+a_1)$

假设现在是 $B$ 要拿：
> $dp_{1,2}= \min (dp_{1,1}-a_2, dp_{2,2}-a_1)$

这样我们就可以递推出现在有 $x \sim y$ 这些数字可以拿的情况。  
假设现在是 $A$ 要拿：
> $dp_{x,y}= \max (dp_{x+1,y}+a_x, dp_{x,y-1}+a_y)$

假设现在是 $B$ 要拿：
> $dp_{x,y}= \min (dp_{x+1,y}-a_x, dp_{x,y-1}-a_y)$

### Code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[3005],dp[3005][3005];
signed main()
{
    cin >> n;
    for(int i=1; i<=n; i++)
        cin >> a[i];
    for(int len=1; len<=n; len++)
    {
        for(int l=1; l+len-1<=n; l++)
        {
            int x=l,y=l+len-1;
            if ((n-len)%2==1)
                dp[x][y]=min(dp[x+1][y]-a[x],dp[x][y-1]-a[y]);
            else
                dp[x][y]=max(dp[x+1][y]+a[x],dp[x][y-1]+a[y]);
        }
    }
    cout << dp[1][n];
    return 0;
}
```

---

## 作者：云浅知处 (赞：0)

设 $F(i,j)$ 为：先手面对一段区间 $[i,j]$ 时所能获得的最大分数。

先讨论先手取了左边的情况：此时留给后手的区间是 $[i+1,j]$。

由状态定义知后手能获得的分数就是 $F(i+1,j)$，因此留给先手的分数就是这段区间的和减去 $F(i+1,j)$。

因此在这种情况下，先手获得的分数就是 $\sum_{k=i}^{j}a_k-F(i+1,j)$。

对于右边，只是将 $F(i+1,j)$ 改成了 $F(i,j-1)$，并没有什么变化。转移方程即为：

$$
F(i,j)=\sum_{k=i}^ja_k-\min\big(F(i,j-1),F(i+1,j)\big)
$$

维护一下 $a$ 前缀和，然后 $O(1)$ 转移即可。

算法的时间复杂度为 $O(n^2)$。

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>

#define int long long
const int MN=3005; 

using namespace std;

inline int read(){
    int x=0,f=1;char c=getchar();
    for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
    for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
    return x*f;
}

int T,n;
int a[MN],f[MN][MN],sum[MN];

signed main(void){
		
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),f[i][i]=a[i],sum[i]=sum[i-1]+a[i];
	
	for(int len=2;len<=n;len++){
		for(int l=1,r=len;r<=n;l++,r++){
            f[l][r]=max(sum[r]-sum[l-1]-f[l+1][r],sum[r]-sum[l-1]-f[l][r-1]);
		}
	}
	
	cout<<2*f[1][n]-sum[n]<<'\n';

    return 0;
}
```

---

## 作者：A_Đark_Horcrux (赞：0)

区间DP

设 $f_{i,j}$ 表示先手在 $i$ 到 $j$ 的区间里能得到的最大分数

$f_{i,j}$ 等于$i$ 到 $j$ 的数的总和，减去已经求过的分数（即$f_{i+1,j}$ 或 $f_{i,j-1}$），再加上新取到的那个数。因为要让 $f_{i,j}$ 最大，所以要取 $f_{i+1,j}$ 和 $f_{i,j-1}$ 最小值，

因此 $f_{i,j}= $  $i$ 到 $j$ 的数之和  $ -min(f_{i+1,j},f_{i,j-1})$ 

求和用一个前缀和即可。

最终得到 $f_{1,n}$ 为先手能得到的最大分数，则全部数的和减去 $f_{1,n}$ 为后手的分数，两者相减即为答案。

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=5010;
int n,p,i,j; long long a[N],f[N][N],s[N]; 
int main() 
{
    scanf("%d",&n);
    for (i=1;i<=n;i++)
        scanf("%lld",&a[i]),s[i]=s[i-1]+a[i];
    for(i=1;i<=n;i++) f[i][i]=a[i];
    for(p=1;p<n;p++)
        for(i=1;i+p<=n;i++)
        {
            j=i+p;
            f[i][j]=s[j]-s[i-1]-min(f[i+1][j],f[i][j-1]);
        }
    printf("%lld\n",2*f[1][n]-s[n]);
    return 0;
}
```


双倍经验：[P2734 USACO3.3 游戏 A Game](https://www.luogu.com.cn/problem/P2734)

---

