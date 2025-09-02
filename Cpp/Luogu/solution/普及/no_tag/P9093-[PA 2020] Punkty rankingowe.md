# [PA 2020] Punkty rankingowe

## 题目描述

**题目译自 [PA 2020](https://sio2.mimuw.edu.pl/c/pa-2020-1/dashboard/) Runda 1 [Punkty rankingowe](https://sio2.mimuw.edu.pl/c/pa-2020-1/p/ran/)。**

Bytie 决定认真准备今年的 PA。为了训练，他创建了一个 BitForces 账号，BitForces 是一个定期举办编程竞赛的平台。

Bytie 知道这个平台使用一种积分系统（也称为 rating），这个系统会让他知道自己的进步，也可以将自己的成绩与其他选手比较。选手的 rating 是一个整数（可能为负数）。在账号创建后，Bytie 的 rating 是 $0$，参加每场比赛后，他的 rating 都会加或减某一个整数。此外，在每场比赛后的 rating 变化历史是可以在平台上看到的。兴奋的 Bytie 开始分析这些数据。他在纸上写下了 $n$ 个连续的数字：

- 在一场比赛之后的最大 rating 上升；
- 在连续两场比赛之后的 rating 上升之和的最大值；
- 在连续三场比赛之后的 rating 上升之和的最大值；
- 以此类推，直到他写到在连续 $n$ 场比赛之后的 rating 上升之和的最大值；

几天后 Bytie 想要回想起 rating 变化的序列。然而，此时 BitForces 正出现技术问题。请帮助 Bytie 还原一个合法的 rating 变化序列，使其长度至少为 $n$ 并且符合写在纸上的数据。

## 说明/提示

#### 样例 1 解释

以下是一、二、三、四次连续比赛中名次增加最多的区间。

![](https://cdn.luogu.com.cn/upload/image_hosting/uvrbz3bh.png)

------------

#### 数据范围

**本题采用捆绑测试**

对于 $100\%$ 的数据，保证 $1\le n\le 300$，$-10^6\le a_i\le 10^6$，$n\le k\le 10^5$，$-10^{13}\le b_k\le 10^{13}$。

## 样例 #1

### 输入

```
4
3 4 5 -1
```

### 输出

```
TAK
9
2 2 -7 0 3 -7 3 -1 3```

## 样例 #2

### 输入

```
10
3 1 4 1 5 9 2 6 5 3```

### 输出

```
NIE```

# 题解

## 作者：Autream (赞：3)

#### 题意简述

给定一个长度为 $n$ 的序列 $a$，其中 $a_i$ 表示一个序列中连续 $i$ 个元素的最大值，求这个序列，可能有多种解。如果有解，输出任意一种；否则输出 `NIE`。

---

#### 题目分析

看到这种有 `Special Judge` 的题目首先就得想到构造。

我们假设所有情况都是有解的，那么对于一个序列 $b$，我们可以假设 $b$ 的前 $i$ 项的和就是连续 $i$ 项的最大值，也就是题目所给的 $a_i$，那么这个构造柿子就显而易见了。

因为 $b$ 的前 $i$ 项的和是 $a_i$，并且此时 $b$ 中只有 $i$ 个数，所以对于连续 $i+1$ 个数的最大值，我们只能添加一个数，使得前 $i+1$ 项的和为 $a_{i+1}$，这个数显然就是 $a_{i+1}-\sum\limits_{j=1}^{i}b_j$。也就是 $b_i=a_i-a_{i-1}$。

接下来我们再来考虑不合法的情况。

因为我们表示的 $\sum\limits_{j=1}^{i}b_j$ 是连续 $i$ 项的和，那么如果在更新到第 $i+1$ 项的时候，在这 $i+1$ 项中有连续的 $j \in [1,i]$ 项的最大值大于了 $a_i$ 那么就不合法。例如下面这组数据：

```
5
3 1 4 1 5
```

当我们按照上面的构造柿子构造到最后一项时，$b$ 数组为：

```3 -2 3 -3 4```

可以发现最后四项的和为 $2$，大于题目给的 $a_4=1$，故不符合条件。

区间和用前缀和统计即可。

---

#### AC Code

```cpp
#include<bits/stdc++.h>
#define arrout(a,n) rep(i,1,n)std::cout<<a[i]<<" "
#define arrin(a,n) rep(i,1,n)std::cin>>a[i]
#define rep(i,x,n) for(int i=x;i<=n;i++)
#define dep(i,x,n) for(int i=x;i>=n;i--)
#define erg(i,x) for(int i=head[x];i;i=e[i].nex)
#define dbg(x) std::cout<<#x<<":"<<x<<" "
#define mem(a,x) memset(a,x,sizeof a)
#define all(x) x.begin(),x.end()
#define arrall(a,n) a+1,a+1+n
#define PII std::pair<int,int>
#define m_p std::make_pair
#define u_b upper_bound
#define l_b lower_bound
#define p_b push_back
#define CD const double
#define CI const int
#define int long long
#define il inline
#define ss second
#define ff first
#define itn int
CI N=1e5+5;
int n,a[N],b[N],s[N];
signed main() {
    std::cin>>n;
    arrin(a,n);
    rep(i,1,n){
        b[i]=a[i]-a[i-1];
        s[i]=s[i-1]+b[i];
        rep(len,1,i){
            rep(l,1,i-len+1){
                int r=l+len-1;
                if(s[r]-s[l-1]>a[len]){
                    puts("NIE");
                    exit(0);
                }
            }
        }
    }
    puts("TAK");
    std::cout<<n<<"\n";
    arrout(b,n);
    return 0;
}
```

---

## 作者：Tomwsc (赞：2)

# P9093 [PA 2020] Punkty rankingowe 题解

## 思路

看完题面，发现还有 ```Special Judge```，第一眼想到的便是构造。

对于这类构造的题目，最重要的是想清楚构造的方法，这点一般都是最为困难的一个部分。

接下来，我会讲一下是怎样想出构造方法的：

首先，发现题目给出了 $n\le 300$，于是容易想到用立方级别的算法，考虑判无解时可以暴力加前缀和 $n^2$，于是构造便只能在 $O(n)$ 的时间内完成。

接着，可以发现，题目给出的 $b$ 数组中的第 $i$ 位就是说构造的序列中连续的 $i$ 个数的最大值为 $b_i$。这其实很容易让人联想到与之类似的都是连续的 $i$ 个数的和的前缀和。于是便可以尝试令构造数组的前 $m$ 项满足 $b_m$，也就是和前缀和相像，在这个基础上可以进行二重循环判断构造出来的数组是否满足 $b$ 数组，如果不满足，便可以直接判无解。显然，这个尝试是正确的。

分析完构造方法，就很好写代码了。这种题目还是需要把思维发散，然后思考方法。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf (1ll << 62)
using namespace std;
const int MAXN = 305;
int n;
int a[MAXN];
int s[MAXN] , b[MAXN];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(register int i = 1;i <= n;i ++)
		cin >> a[i];
	for(register int i = 1;i <= n;i ++) {
		b[i] = a[i] - s[i - 1];
		s[i] = s[i - 1] + b[i];
		for(register int j = 1;j <= n;j ++)
			for(register int k = 1;k <= i - j + 1;k ++)
				if(s[k + j - 1] - s[k - 1] > a[j]) {
					cout << "NIE" << '\n';
					return 0;
				}
	}
	cout << "TAK" << '\n';
	cout << n << '\n';
	for(register int i = 1;i <= n;i ++)
		cout << b[i] << " ";
	return 0;
}
```

---

## 作者：ProzacPainkiller (赞：2)

首先，我们可以知道，当对于一个整数 $i\ (1\le i\le n)$ 有一个整数 $j\ (1\le j\le n)$ 使得 $a_i>a_j+a_{i-j}$ 时，绝对是无解的。（对于一个合法序列，两个区间和最大值相加一定大于等于长度等于它们两个长度之和的区间的和最大值）

接着，在剩下的情况中，我们来构造 $\{b_k\}$。

应用贪心的思想，我们直接来使得 $b_i=a_i-a_{i-1}$，我们用数学归纳法的思想证明这种策略行得通。

首先假设 $b$ 前 $i-1$ 项可以满足 $a$ 的条件，接下来就是要推出下一项也可以满足条件，也就是说，我们对于每一个整数 $j\ (2\le j\le i)$ 要证明 $\sum_{p=j}^{i}b_p\le a_{i-j+1}$（构造方法已经保证 $j=1$ 的情况合法）。我们可以知道，$\sum_{p=1}^{i}b_p=a_i$ 并且 $\sum_{p=1}^{j-1}b_p=a_{j-1}$。由于已经排除了 $a_i>a_{j-1}+a_{i-j+1}$ 的情况，那么$\sum_{p=j}^{i}b_p=a_i-a_{j-1}\le a_{i-j+1}$，即合法。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=302;
int n,ans[N],a[N];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		ans[i]=a[i]-a[i-1];
		for(int j=1;j<=i>>1;j++)
			if(a[j]+a[i-j]<a[i])
			{
				cout<<"NIE";
				return 0;
			}
	}
	cout<<"TAK\n"<<n<<'\n';
	for(int i=1;i<=n;i++)	cout<<ans[i]<<' ';
	return 0;
}
```

---

## 作者：r1sing (赞：1)

## 形式化题意
给定一个 $n$ 和 $n$ 个整数 $a_1,a_2,a_3,\cdots,a_n$，让你构造一个序列使它的长度为 $i$ 的最大子段和等于 $a_i$。
## 构造
首先我们让第一个数等于 $a_1$, 第一个数加第二个数等于 $a_1$……就得到了类似下图的序列
![](https://cdn.luogu.com.cn/upload/image_hosting/2zxf7nu9.png)
可是这样的构造方法的时间复杂度是 $O(n^2)$ 的，稍微有点高（也能过）而且代码不是特别好写。
### 优化
我们可以发现并不需要插一个 -inf 可以构造一个长度为 $n$ 的序列使前 $i$ 个的和为 $a_i$。
### 判断合法性
比如说样例2的数据
```markdown
9
3 1 4 1 5 9 2 6 5 3
```
构造出的序列为
```markdown
9
3 -2 3 -3 4 4 -7 4 -1 -2
```
我们可以发现 $4 + 4\ne1$ 所以这个序列不合法。
所以我们可以对这个序列做个前缀和，求长度为 $i$ 的最大子段和是否等于 $a_i$。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
ll a[303];
ll b[303];
ll s[303];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);     cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	ll sum = 0;
	for(int i = 1; i <= n; i++)
	{
		b[i] = a[i] - sum;
		sum += b[i];
	}
	for(int i = 1; i <= n; i++)
		s[i] = s[i - 1] + b[i];
	for(int i = 1; i <= n; i++)
	{
		for(int j = i; j <= n; j++)
		{
			if(s[j] - s[j - i] > a[i])
			{
				cout << "NIE";
				return 0;
			}
		}
	}
	cout << "TAK\n";
	cout << n << "\n";
	for(int i = 1; i <= n; i++)
		cout << b[i] << " ";
	return 0;
}
```

---

