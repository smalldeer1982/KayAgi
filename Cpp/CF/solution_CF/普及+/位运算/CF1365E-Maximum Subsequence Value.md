# Maximum Subsequence Value

## 题目描述

给出一个长度为 $n$ 的数列 $a$，你需要选出一个子序列，使其价值最大，输出最大的价值。  

对于一个长度为 $k$ 的子序列，若在这个子序列中有不少于 $\max(1,k-2)$ 个数的二进制位 $i$ 上是 $1$，则其价值增加 $2^i$。

## 样例 #1

### 输入

```
3
2 1 3```

### 输出

```
3```

## 样例 #2

### 输入

```
3
3 1 4```

### 输出

```
7```

## 样例 #3

### 输入

```
1
1```

### 输出

```
1```

## 样例 #4

### 输入

```
4
7 7 1 1```

### 输出

```
7```

# 题解

## 作者：do_while_true (赞：5)

考虑根据 $n$ 的取值进行讨论。

当 $1\leq n\leq3$ 时，$k$ 最大值为 $3$ ，此时 $max(1,k-2)$ 也仅为 $1$，也就是取全部的数一定是最优的，因为尽可能让每一位都有 $1$ ，并不在于有多少。

当 $n>3$ 时，考虑从 $k=3$ 时每加进一个数对答案的影响，显然 $k$ 每次加 $1$ ，$max(1,k-2)$ 都会 $+1$ ，也就是说每一个二进制位的 $1$ 的个数都要 $+1$ 才能使得答案不小于 $k=3$ 时。每个二进制位最多只是加了一个 $1$ 的个数，而 $max(1,k-2)>1$ ，所以我们不管怎么加都不可能使得 $k=4$ 的答案能比 $k=3$ 更优。

所以当 $n>3$ 时，$\mathcal{n^3}$ 枚举三个数算最大值即可。

---

## 作者：rui_er (赞：3)

思路：

考虑如何使取出的 $k$ 个数价值最大。

对于 $k\in\left\{1,2,3\right\}$，根据定义，若 $k$ 个数中至少有一个数的二进制位 $i$ 上是 $1$，则价值增加 $2^i$，这个定义十分眼熟，发现就是按位或的结果。对于 $k\ge 4$，$k$ 每增加 $1$，就会使 $\max\left(1,k-2\right)$ 增加 $1$，因此每个二进制位的出现次数都需要加 $1$ 才能使答案更优，显然不如 $k=3$ 的情况。

因此对于 $n\in\left\{1,2\right\}$，答案即为这些数的或；对于 $n\ge 3$，答案为数列任取三个数能得到的最大的或。可以花费 $\mathcal{O}(n^3)$ 枚举取的三个数得到答案。

因为懒得特判前者，我选择牺牲了一定的代码常数，将 $i,j,k$ 都从 $1$ 枚举到 $n$，但是对于前者也能得到正确的结果。

---

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define loop while(true)
#define rep(x,y,z) for(ll x=y;x<=z;x++)
#define per(x,y,z) for(ll x=y;x>=z;x--)
#define fil(x,y) memset(x, y, sizeof(x))
#define mulT0 ll T; for(scanf("%lld", &T);T;T--)
#define mulT1 ll T, rnds; for(scanf("%lld", &T),rnds=1;rnds<=T;rnds++)
using namespace std;
typedef long long ll;
const ll N = 505;

ll n, a[N], ans;

int main() {
	scanf("%lld", &n);
	rep(i, 1, n) scanf("%lld", &a[i]);
	rep(i, 1, n) rep(j, 1, n) rep(k, 1, n) ans = max(ans, a[i]|a[j]|a[k]);
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：ShineEternal (赞：1)

[更佳的阅读效果。](https://vipblog.github.io/Q26F2-_0P/)

## description：

![](https://vipblog.github.io/post-images/1591709941589.jpg)

## solution：

这道题目刚开始乍一看并无思路（包括但不限于我太菜），不过仔细分析一下，我们可以**贪心的只选择三个数**。

为什么选择三个数一定是最优的呢？（当然如果 $n=1/2$ 的时候分别选 $1/2$ 个)

我们观察题意，一个十分必要的制约条件是 不少于 $\max\{1,k-2\}$ 个数的某一位相同。

那么当 $k=3$ 时就成了互不干扰的情况，而如果 $k>3$ 就需要保证两个甚至更多的数字某一位相同。

这样的话，比起选择多个数，我们要保障第 $i$ 位的贡献能够得到的同时完全可以选择更少的含有这一位的数。（因为要得到这一位的贡献就需要 $k-2$ 个数凑起来，而如果要凑 $k-2$ 个某一位相同的数完全可以只留下其中一个数。

## code：
```cpp
#include<cstdio>
using namespace std;
long long a[505];
long long max(long long x,long long y)
{
	if(x<y)return y;
	return x;
}
int main()
{
	int n;
	scanf("%d",&n);
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			for(int k=j+1;k<=n;k++)
			{
				ans=max(ans,a[i]|a[j]|a[k]);
			}
		}
	}
	if(n>=3)printf("%lld\n",ans);
	else
	if(n==2)printf("%lld\n",a[1]|a[2]);
	else
	printf("%lld\n",a[1]);
	return 0;
} 
```

---

## 作者：_Delete_ (赞：0)

## 思路

我们可以对于 $n$ 的取值进行讨论。

显然，当子序列长度 $k$ 小于等于 $3$ 时，对于二进制上的每一位只要有，则必定对答案有贡献，所以一定全取。

当我们再次向其中添加数字时，造成贡献的总位数多了一位，而即使新的数字引入了新的一个二进制位，也不会对答案造成更多的贡献，反而可能会因为新数字某些二进制位上的缺失而减少对答案的贡献。

综上可证明最优答案一定有 $k$ 为 $3$ 的方案，我们可以对这三个数字进行枚举，时间复杂度可以通过此题。

## 代码


```cpp
#include<bits/stdc++.h>
#define endl "\n"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
//value 
ll a[1005];


//function 
void solve(){
	
	
	
	return;
}


 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0); 
	
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	ll n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	
	ll ans=0;
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int k=1;k<=n;k++){
				ans=max(ans,a[i]|a[j]|a[k]);
			}
		}
	}
	
	cout<<ans<<endl;	
	
	
	return 0;
}


```

---

## 作者：Michael1234 (赞：0)

本题可以使用数学归纳法：

首先，我们知道当 $k\le 3$，要求的数量为 $1$，以 $k=3$ 为例，此时只要三个数中有一个数在二进制下的第 $i$ 位有 $1$，其就对答案有贡献。

而当 $k=4$，其要求的数量为 $2$，所以新添加的数要想对答案有贡献，就需要有新的一位 $i$ 上有 $1$。但是，只有一个 $1$ 不够，所以其不可能比三个数更优。通过数学归纳法，我们可以证明当 $k>3$，其答案不可能更优。

因此只需枚举三个序列中的数，答案为：

$$\max_{i=1}^{n}{\max_{j=1}^{n}{\max_{k=1}^{n}{a_i \operatorname{or} a_j \operatorname{or} a_k}}}$$

---

## 作者：ttq012 (赞：0)

$\mathscr{\color{purple}{Difficutly: *1900}}$

## $\mathscr{DESCRIPTION}$

略。

## $\mathscr{SOLUTION}$

有趣的诈骗题。

容易发现，当 $n\le 3$ 的时候，不管怎么选每一位都至少需要 $1$ 个数的二进制位是 $1$ 才能有贡献，所以一定全选。

否则（$n>3$），由于多选择一个数，二进制位上就得多加一个 $1$ 才行，所以选了一定不会更优。所以只选择三个数。

于是选择三个数 $i$，$j$，$k$ 满足 $a_i\operatorname{or}a_j\operatorname{or}a_k$ 的值最大即可。

时间复杂度 $O(n^3)$。

## $\mathscr{CODE}$

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
int a[N], s[N];
signed main()
{
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  if (n <= 3)
  {
    int OR = 0;
    for (int i = 1; i <= n; i++)
      OR |= a[i];
    cout << OR << '\n';
  }
  else
  {
    int mx = 0;
    for (int i = 1; i <= n; i++)
      for (int j = i + 1; j <= n; j++)
        for (int k = j + 1; k <= n; k++)
          mx = max(mx, a[i] | a[j] | a[k]);
    cout << mx << '\n';
  }
  return 0;
}
```

## $\mathscr{AC\ RECORD}$

[$\mathscr{LINK}$](https://www.luogu.com.cn/record/105331090)

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 1900}$
---
### 解题思路：

简单的诈骗题。

考虑一个二进制位，在选择的数的个数达到 $3$ 之前如果有 $1$ 就直接能变成 $1$，而在达到 $3$ 之后即使再加入一个 $1$，也不能使得原本的 $0$ 变成 $1$，反而有可能让 $1$ 变成 $0$。

换言之，在已经选择了三个数的情况下，如果再选择一些新的数一定不优。再说得明白些，就是最优的答案一定可以通过直接选取三个数构造出来。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
int n,a[505],ans;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	for(int k=1;k<=n;k++)
	ans=max(ans,a[i]|a[j]|a[k]);
	printf("%lld\n",ans);
	return 0;
}
```


---

