# [ABC185E] Sequence Matching

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc185/tasks/abc185_e

長さ $ N $ の整数列 $ A $ と、長さ $ M $ の整数列 $ B $ があります。  
 高橋君は $ A $ から、いくつかの要素を取り除き、残った要素をそのままの順番で繋げることで新たな数列 $ A' $ を作ります。(一つも取り除かなくても、全部取り除いても構いません。)  
 $ B $ についても同様に、いくつかの要素を取り除き、残った要素をそのままの順番で繋げることで新たな数列 $ B' $ を作ります。(一つも取り除かなくても、全部取り除いても構いません。)  
 このとき、$ |A'|\ =\ |B'| $ となるような取り除き方をします。(数列 $ s $ について $ |s| $ は $ s $ の長さを表します。)  
 $ A,\ B $ から取り除いた合計要素数を $ x $ とし、$ 1\ \le\ i\ \le\ |A'| $ かつ $ {A'}_i\ \neq\ {B'}_i $ を満たす整数 $ i $ の数を $ y $ とするとき、$ x\ +\ y $ として考えられる最小の値を求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ N,\ M\ \le\ 1000 $
- $ 1\ \le\ A_i,\ B_i\ \le\ 10^9 $
- 入力は全て整数

### Sample Explanation 1

$ A $ から $ A_4 $ を削除して $ A' $ を作り、$ B $ からは何も削除せず $ B' $ を作ることにすると、$ x\ =\ 1 $ となります。 また、このとき $ 1\ \le\ i\ \le\ |A'| $ かつ $ {A'}_i\ \neq\ {B'}_i $ を満たす整数 $ i $ は $ 2 $ の一つのみなので $ y\ =\ 1 $ となります。そして $ x\ +\ y $ は $ 2 $ となり、これが最小です。

### Sample Explanation 2

$ A $ からは何も取り除かず、$ B $ からは $ B_4,\ B_6 $ の $ 2 $ 要素を削除すると $ x\ =\ 2,\ y\ =\ 1 $ となり、 $ x\ +\ y $ は $ 3 $ で、これが最小です。

### Sample Explanation 3

$ A $ からも $ B $ からも何も取り除かないことも許されます。

## 样例 #1

### 输入

```
4 3
1 2 1 3
1 3 1```

### 输出

```
2```

## 样例 #2

### 输入

```
4 6
1 3 2 4
1 5 2 6 4 3```

### 输出

```
3```

## 样例 #3

### 输入

```
5 5
1 1 1 1 1
2 2 2 2 2```

### 输出

```
5```

# 题解

## 作者：crzcqh (赞：3)

思路：

观察数据范围，$O(n^2)$ 可过，很明显是一个 $n^2$ 的 dp。设 $f_{i,j}$ 表示 $A_1\sim A_i$ 和 $B_1\sim B_j$ 的最小代价，下面是分类讨论：

1. 如果 $A_i=B_j$，则最小代价和 $f_{i-1,j-1}$ 是一样的。

2. 如果不相等，只能是 $f_{i-1,j},f_{i,j-1},f_{i-1,j-1}$ 中取最小然后再加上修改或删除或插入的 $1$ 代价。

状态转移方程：

$$f_{i,j}=\min(f_{i-1,j}+1,f_{i,j-1}+1,f_{i-1,j-1}+[A_i≠ A_j])$$

初始化：

$$f_{0,i}=f_{i,0}=i$$

Code:

```cpp
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++){
			if(a[i]==b[j])
				dp[i][j]=dp[i-1][j-1];
			else
				dp[i][j]=min(dp[i][j-1],
				min(dp[i-1][j-1],dp[i-1][j]))+1;
			//cout<<i<<' '<<j<<' '<<dp[i][j]<<endl;
		}
```

---

## 作者：loser_seele (赞：2)

这题是 [P2758](https://www.luogu.com.cn/problem/P2758) 的原题，如果不懂的可以去找那题的题解。

至于这两题为什么等价，观察到删除和插入操作是等价的，而修改操作对应这题的不同位置个数，所以是一样的。

考虑类似 LCS 的 dp 方法，显然有：

$ dp_{i,0}=i,dp_{0,j}=j $，是平凡的，代表修改为空串的代价。

$ dp_{i,j}=\min\{ dp_{i-1,j}+1,dp_{i,j-1}+1,dp_{i-1,j-1}+![a_i = b_j] \} $，表示 $ dp_{i,j} $ 从后面的三种情况转移而来。

于是可以在 $ \mathcal{O}(n^2) $ 的时间复杂度内解决本题。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[2020],b[2020];
int f[2020][2020];
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++)
		cin>>a[i];
	for(int i=0;i<m;i++)
		cin>>b[i];
	for(int i=1;i<=n;i++)
		f[i][0]=i;
	for(int j=1;j<=m;j++)
		f[0][j]=j;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			f[i][j]=min(min(f[i-1][j]+1,f[i][j-1]+1),f[i-1][j-1]+(a[i-1]!=b[j-1]));
	cout<<f[n][m];
}
```


---

## 作者：Acheron_RBM (赞：1)

这题很显然的动态规划。

转移方程有二：

- 遍历 $A$，$B$。如果 $A_i$ 等于 $B_i$ 那么 $dp_{i,j}$ 等于 $dp_{i-1,j-1}$。

- 否则状态转移方程是 $dp_{i,j}=\min(dp_{i,j-1},\min(dp_{i-1,j-1},dp_{i-1,j}))+1$。

```cpp
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++) 
	{
		cin>>a[i];
	}
	for(int i=0;i<m;i++)
	{
		cin>>b[i];
	}
	for(int i=1;i<=n;i++) 
	{
		dp[i][0]=i;//初始化 
	}
	for(int i=1;i<=m;i++) 
	{
		dp[0][i]=i;//初始化 
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[i-1]==b[j-1])
			{
				dp[i][j]=dp[i-1][j-1];
			}
			else
			{
				dp[i][j]=min(dp[i][j-1],min(dp[i-1][j-1],dp[i-1][j]))+1;
			}
		}
	}
	cout<<dp[n][m];
} 
```

---

## 作者：_liuyi_ (赞：1)

## 题意分析
给定两个序列 $A$,$B$ ,可以删除、修改、插入。
## 思路
非常明显的一道动规题目。

遍历 $A$ , $B$。

如果 $A_i$ 等于 $B_j$ 。

那么最大值就是前面的值,$f_{ij}=f_{i-1,j-1}$。

否则删除、修改、插入三个行为去最小值加一。 
$f_{ij}=\min(f_{ij-1},\min(f_{i-1j-1},f_{i-1j}))+1$。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,f[2001][2001],a[2001],b[2001];
int main(){
	scanf("%d%d",&n,&m); 
	for(int i=0;i<n;i++) scanf("%d",&a[i]);
	for(int i=0;i<m;i++) scanf("%d",&b[i]);
	for(int i=1;i<=n;i++) f[i][0]=i;//预处理空串
	for(int i=1;i<=m;i++) f[0][i]=i;//同上
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i-1]==b[j-1]){
				f[i][j]=f[i-1][j-1];
			}
			else{
				f[i][j]=min(f[i][j-1],min(f[i-1][j-1],f[i-1][j]))+1;
			}
		}
	}
	printf("%d",f[n][m]);
} 
```


---

## 作者：Happy_mouse (赞：0)

# [Sequence Matching](https://www.luogu.com.cn/problem/AT_abc185_e) 题解
[AC证明](https://www.luogu.com.cn/record/173632370)
## 分析与解答
题目转化：
# 编辑距离

## 题目描述

$a$ 和 $b$ 是两个数组。用最少的操作次数，将数组 $a$ 转换为数组 $b$。操作共有三种：

1. 删除一个数；（求子序列嘛，其中删掉一些数）
2. 插入一个数；（等效于从另一数组删一个数）
3. 将一个数改为另一个数。（即不相等情况）

呃，这题我好像在哪做过。

又看了看，呀，原来是 [P2758](https://www.luogu.com.cn/problem/P2758)，双倍经验啊。

DP 一道。开二维数组，$f_{i,j}$ 表示在 $a$ 数组取前 $i$，$b$ 数组取前 $j$ 时保持相等所需操作的最小值。

如果 $a_i=b_j$ ，则其 $f_{i-1,j-1}$ 是一样的（不用改）。

如果不相等，只能是 $f_{i-1,j}$（操作 1 之前），$f_{i,j-1}$（操作 2 之前），$f_{i-1,j-1}$（操作 3 之前）中取最小然后再加上修改或删除或插入的代价。

状态转移方程：
$$
f_{i,j}=\min(f_{i-1,j}+1,f_{i,j-1}+1,f_{i-1,j-1}+[a_i \ne b_j])
$$
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[1005],b[1005];
int f[2005][2005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++) cin>>b[i];
	for(int i=0;i<=n;i++) f[i][0]=i;
	for(int i=0;i<=m;i++) f[0][i]=i;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			f[i][j]=min(f[i][j-1],min(f[i-1][j],f[i-1][j-1]))+1;//删除，修改，添加三选一
			if(a[i]==b[j]) f[i][j]=min(f[i][j],f[i-1][j-1]);//继承
		}
	}
	cout<<f[n][m];
	return 0;
}
```

---

## 作者：Flyingsnow (赞：0)

## 思路

这种题不用看直接想 dp。

首先遍历 $a$ 与 $b$，若有相等转移方程即为 $dp_{i,j}=dp{i-1, j-1}$，如果不等转移方程即为 $dp_{i,j} = \min(dp_{i,j-1},\min(dp_{i-1,j-1},dp_{i-1,j})) + 1$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 7;

int a[N], b[N];

int dp[N][N];

int n, m;

signed main() {
    scanf("%d%d", &n, &m);
    
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);
        
    for (int i = 0; i < m; ++i)
        scanf("%d", &b[i]);
        
    for (int i = 1; i <= n; ++i)
        dp[i][0] = i; 
        
    for (int i = 1; i <= m; ++i)
        dp[0][i] = i; 
        
    for (int i = 1; i <= n; ++i) 
        for (int j = 1; j <= m; ++j) 
            (a[i - 1] == b[j - 1]) ? dp[i][j] = dp[i - 1][j - 1] : dp[i][j] = min(dp[i][j - 1], min(dp[i - 1][j - 1], dp[i - 1][j])) + 1;
        
    printf("%d", dp[n][m]);
    return 0;
}

```



---

## 作者：shaozhehan (赞：0)

[原题链接](https://www.luogu.com.cn/problem/AT_abc185_e)

[AtCoder 链接](https://atcoder.jp/contests/abc185/tasks/abc185_e)

题目大意：

在序列 $a$ 和 $b$ 中删除 $x$ 和 $y$ 个数得到子序列 $a'$ 和 $b'$，且 $a'$ 和 $b'$ 的长度相等。问你 $x+y$ 与 $a'$ 和 $b'$ 在对应位置上元素不相等的下标个数的和的最小值。

思路：

这道题可以使用 dp。定义 $dp_{i,j}$ 代表 $a$ 的前 $i$ 个元素和 $b$ 的前 $j$ 个元素带入题目中的 $a$ 和 $b$ 时的答案。

首先，$dp_{i,0}$ 和 $dp_{0,i}$ 都为 $i$，因为只能在前面或后面的序列删除 $i$ 个元素，对应位置不同元素个数为 $0$。

如果 $i\not=0$ 且 $j\not =0$，那么我们可以分情况讨论：

- 如果 $a_i=b_j$，那么这个时候不用动，$dp_{i,j}=dp_{i-1,j-1}$。
- 如果 $a_i\not=b_j$：
  - 如果此时删除 $a_i$，那么 $dp_{i,j}=dp_{i,j-1}+1$。
  - 如果此时删除 $b_i$，那么 $dp_{i,j}=dp_{i-1,j}+1$。
  - 如果此时不变，那么 $dp_{i,j}=dp_{i-1,j-1}$。

那么，我们可以得到 $dp$ 数组的转移方程：$dp_{i,j}=\begin{cases}dp_{i-1,j-1},&a_i=b_j\\\min\{dp_{i,j-1},dp_{i-1,j},dp_{i-1,j-1}\},&a_i\not=b_j\end{cases}$。

坑点：
- 初始化 $dp_{0,i}$ 和 $dp_{i,0}$ 不能忘！
- 需要判断 $a_i$ 是否等于 $b_j$，不能一概而论！
- $a_i\not=b_j$ 时，千万不能把 $dp_{i-1,j-1}$ 落下！

上代码：

```cpp
#include <iostream>
using namespace std;

int a[1001], b[1001], dp[1002][1002];

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++){
        cin >> b[i];
    }
    for (int i = 1; i <= n; i++){
        dp[i][0] = i;
    }
    for (int i = 1; i <= m; i++){
        dp[0][i] = i;
    }
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            if (a[i] == b[j]){
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min(dp[i][j - 1], min(dp[i - 1][j - 1], dp[i - 1][j])) + 1;
            }
        }
    }
    cout << dp[n][m] << "\n";
    return 0;
}
```

---

## 作者：zhanghao233 (赞：0)

一模一样 [P2758 编辑距离](https://www.luogu.com.cn/problem/P2758)

# 题目大意

* 删除一个字符；

* 插入一个字符；

* 将一个字符改为另一个字符。

# 思路

有点像 **最长上升子序列** ，但不是 ~~所以一眼~~ $DP$

$ DP_{i,j} $ 表示 上字符串 1 到 $i$ 和 下字符串 1 到 $j$ 的最短消耗

~~显然，~~ 我们可以将题只有4种操作转化为转移方程

* **删** ：$ DP_{i,j} = DP_{i-1,j}+1 $ 。 

* **插** ：$ DP_{i,j} = DP_{i,j-1}+1 $ 。

* **变** ：$ DP_{i,j} = DP_{i-1,j-1}+1 $ 。

* **不变** ：$ DP_{i,j} = DP_{i-1,j-1} $


```cpp
#include<iostream>
#include<cstdio>
using namespace std;

int n,m;
int a[2000],b[2000];
int f[2000][2000];
signed main(){
	cin>>n>>m;
	for(int i=0;i<n;i++){
	    cin>>a[i];
	    f[i+1][0]=i+1;
	}
	for(int i=0;i<m;i++){
	    cin>>b[i];
	    f[0][i+1]=i+1;
	}
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i-1]==b[j-1])
            	f[i][j]=f[i-1][j-1];
			else
				f[i][j]=min(min(f[i-1][j]+1,f[i][j-1]+1),f[i-1][j-1]+1);
	
	cout<<f[n][m]<<"\n";
	return 0;
}

```


---

