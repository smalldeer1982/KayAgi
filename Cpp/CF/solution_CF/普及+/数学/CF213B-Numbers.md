# Numbers

## 题目描述

Furik loves writing all sorts of problems, especially such that he can't solve himself. You've got one of his problems, the one Furik gave to Rubik. And Rubik asks you to solve it.

There is integer $ n $ and array $ a $ , consisting of ten integers, indexed by numbers from 0 to 9. Your task is to count the number of positive integers with the following properties:

- the number's length does not exceed $ n $ ;
- the number doesn't have leading zeroes;
- digit $ i $ $ (0<=i<=9) $ occurs in the number at least $ a[i] $ times.

## 说明/提示

In the first sample number 9 meets the requirements.

In the second sample number 10 meets the requirements.

In the third sample numbers 10, 110, 210, 120, 103 meet the requirements. There are other suitable numbers, 36 in total.

## 样例 #1

### 输入

```
1
0 0 0 0 0 0 0 0 0 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
1 1 0 0 0 0 0 0 0 0
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3
1 1 0 0 0 0 0 0 0 0
```

### 输出

```
36
```

# 题解

## 作者：湖南省队御用绫厨TM_Sharweek (赞：1)

## 题意简述
给出一个数字 $n$ 和 $10$ 条限制 $a_0,a_1,a_2,\cdots,a_9$。求出有多少个数 $x$ 满足：

- $x<10^n$。
- $\forall i\in[0,9]\cap\N$，$x$ 中数位 $i$ 的出现次数 $\ge a_i$。

## 思路分析
看到奇怪数数题就可以考虑 dp 了。

首先我们有一个比较显然的 dp 状态设计。即用 $f_{i,b_0,b_1,b_2,\cdots,b_9}$ 表示考虑这个数前 $i$ 位，出现数位 $j$ 的次数为 $b_j$ 的方案数。如此设计状态，状态转移方程为 $f_{i,b_0,b_1,b_2,\cdots,b_9}=\sum_{j=0}^9f_{i,b_0,b_1,b_2,\cdots,b_j-1,\cdots,b_9}$。这个状态设计下的转移方程是非常复杂的，并且计算的复杂度也相当高，根本不可能通过此题。

然后我们可以稍微优化一下这个状态设计：用 $f_{i,b_0,b_1,b_2,\cdots,a_j,\cdots,b_9}$ 表示已经满足了数位 $j$ 的状态，删掉 $b_9$ 因为显然它就是 $i-\sum_{i=0}^8b_i$ 等。但一系列优化后，时间复杂度仍然无法接受。必须要设计新的状态。

我们可以考虑这样一个状态：$f_{i,S}$ 表示考虑前 $i$ 位，$S$ 内的数位限制已经满足的情况。怎么让一个数位限制 $a_j$ 一次就满足呢？直接加入不少于 $a_j$ 个 $j$ 不就行了！但是这样会有一个问题，如果我们在一个已经满足了数位限制 $a_j$ 的状态中再插入若干个 $j$，那么很有可能会统计到重复的情况。例如，状态 $f_{i,S_1}$ 是在 $f_{i-k_1,S_2}$ 的基础上插入 $k_1$ 个 $j$ 得到的，那么 $f_{i+k_2,S_1}$ 就会算一遍 $f_{i,S_1}$ 中插入 $k_2$ 个 $j$ 的答案，再算一遍 $f_{i-k_1,S_2}$ 中插入 $k_1+k_2$ 个 $j$ 的答案，而这两种情况实际上是相同的，被重复计算了。为了避免这种情况出现，我们再次修改状态的定义，用 $f_{i,S}$ 表示考虑前 $i$ 位，$S$ 内的数位限制已经满足且**以前没添加不在 $S$ 内的数位，以后不再添加 $S$ 内的数位**的情况。当我们在一个长度为 $i$ 的数中插入 $k$ 个数 $j$ 时，就是要在新形成的长度为 $i+k$ 的数中选择 $k$ 个作为 $j$，剩下的位数和原来的数对应。那么就有 $\binom{i+k}{k}$ 种选择方法。需要注意的是，$0$ 是不能放在首位的。所以当 $j=0$ 时，方案数应该是 $\binom{i+k-1}{k}$。所以转移方程如下：

$$f_{i,S}=\sum_{j\in S \land j\notin S}\sum_{k=0}^{i-a_j}(f_{k,S/\{j\}}\times\binom{i}{i-k})+[0\in S]\times\sum_{k=1}^{i-a_0}(f_{k,S/\{0\}}\times\binom{i-1}{i-k})$$

边界状态为 $f_{0,\varnothing}=1$。

但是如果读者进行了认真的思考的话，会发现这种做法是**错误**的（当然也有可能是在写完代码测试完样例后）。因为重复计数的问题仍然没有解决。先满足限制 $a_i$ 再满足限制 $a_j$ 的情况与先满足 $a_j$ 再满足 $a_i$ 的情况中显然会有一些重复的方案，而转移方程不会考虑这些重复的方案。并且经过一段时间的思考后，我们发现容斥也难以处理这个问题。于是我们不得不再次更换思路。

注意上次我们的思路之所以错误，是因为满足 $a_i$ 限制与满足 $a_j$ 限制的先后会导致方案被重复计算。如何避免这个重复计算呢？容易想到给限制的满足规定一个严格的先后顺序可以规避掉这个问题。但这样会不会导致部分方案漏记呢？其实是不会的。因为我们每次转移是在原来的数上插入 $k$ 个 $j$，先插入和后插入显然是没有什么区别的。所以我们可以要求限制的满足必须符合某个顺序。如果从 $0$ 往大逐个满足，会发现最开始加入的就是 $0$，没有前导零这个限制完成起来非常麻烦。所以我们选择从 $9$ 往小逐个满足（当然你也可以自己选择一个你喜欢的不先满足 $0$ 的顺序）。基于上述思路，我们如此设计状态：$f_{i,j}$ 表示考虑到前 $i$ 位数，已经满足了 $a_j$ 至 $a_9$，此后不会再添加数位 $j$ 至 $9$，没有添加 $0$ 至 $j-1$ 的方案数，并用 $f_{i,10}$ 表示什么都没有加入或满足的方案数。在上一种做法中，我们已经很详尽地讨论了转移需要用到的组合数，现在可以直接用了。转移方程为：$f_{i,j}=\sum_{k=0}^{i-a_j}f_{k,j+1}\times\binom{i}{i-k}(j\neq 0),f_{i,0}=\sum_{k=0}^{i-a_0}f_{k,1}\times\binom{i-1}{i-k}$。边界条件为 $f_{0,10}=1$。答案为 $\sum_{i=1}^nf_{i,0}$。时间复杂度为 $\Theta(|\Sigma|n^2)$，其中 $|\Sigma|=10$，可以通过。

需要注意一些细节：$f_{i,j}$ 可能从 $f_{i,j+1}$ 转移（当且仅当 $a_j=0$ 时出现这种情况），所以第二维需要从大到小计算。

## 代码

以下是我的 C++ 代码

```cpp
/*********************************************************************
    程序名:
    版权:
    作者: TM_Sharweek
    日期: 2024-12-22 13:51
    说明:恭喜《戏游九州》打破中术最速传说记录！
*********************************************************************/
#include <bits/stdc++.h>

#define p_b push_back
#define m_p make_pair
#define sec second
#define fst first
#define p_q priority_queue
#define u_m unordered_map

using namespace std;

using ll = long long;
using ull = unsigned long long;
using i128 = __int114514;

const int N = 150;
const ll P = 998244353;//1e9+7

ll f[N][15];
ll c[N][N];
int a[15];

long long main() {
	freopen("cf213b.in","r",stdin);
	freopen("cf213b.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	c[0][0] = 1;
	int n;
	cin >> n;
	for (int i = 0; i < 10; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++) {
		c[0][i] = 1;
		for (int j = 1; j <= i; j++) {
			c[j][i] = (c[j - 1][i - 1] + c[j][i - 1]) % P;
		}
	}
	f[0][10] = 1;
	for (int i = 0; i <= n; i++) {
		for (int j = 9; j >= 1; j--) {
			for (int k = 0; k <= i-a[j]; k++) {
				f[i][j] = (f[i][j] + f[k][j + 1] * c[i-k][i] % P) % P;
			}
		}
		for (int k = 0; k <= i-a[0]; k++) {
			f[i][0] = (f[i][0] + f[k][1] * c[i-k][i - 1] % P) % P;
		}
	}
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		ans = (ans + f[i][0]) % P;
	}
	cout << ans << endl;

	return 1007120412;
}

``````

---

## 作者：HBWH_zzz (赞：0)

# [CF213B Numbers](https://codeforces.com/problemset/problem/213/B)

>给定 $n$ 和 $a_0\sim a_9$，求方案数使得最多有 $n$ 位的无前导零数中含有至少 $a_i$ 个 $i$ 的数的个数对 $10^9+7$ 取模。$n\leq 100$。

本文思路来自抽象的官方题解。

设 $f_{i,j}$ 表示只用 $j\sim 9$ 的数填满 $i$ 位（不能有前导零）。则有：

$$f_{i,9}=[i\geq a_9]$$

这个好理解，只有一种填法 $99\dotsc99$ 。

$$f_{i,j}=\sum_{a_j\leq k\leq i} f_{i-k,j+1}\times \binom{i}{k}$$

其中 $j\in(0,9)$ ，理解方法就是在已经有 $j+1\sim 9$ 的基础上插入 $j$ ，一共有 $i$ 个位置，要选 $k$ 个空位作为 $j$ 的位置，所以乘上组合数 $\binom{i}{k}$。

$$f_{i,0}=\sum_{a_0\leq k\leq i}f_{i-k,1}\times \binom{i-1}{k}$$

由于 $0$ 不能出现在最前面，所以组合数需要变成 $\binom{i-1}{k}$。

最后答案就是 $\sum_{1\leq i\leq n} f_{i,0}$。然后这个转移是 $O(n^2\times 10)$ 的，可过。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007
#define ll long long
int n;
int a[10];
ll C[105][105];
ll f[105][10];

ll dp(int i,int j){
	if(j==9)
		return (i>=a[9]);
	if(f[i][j]!=-1)
		return f[i][j];
	if(j!=0){
		ll ret=0;
		for(int k=a[j];k<=i;++k){
			ret=(ret+dp(i-k,j+1)*C[i][k])%mod;
		}
		return f[i][j]=ret;
	}
	ll ret=0;
	for(int k=a[0];k<=i;++k){
		ret=(ret+dp(i-k,1)*C[i-1][k])%mod;
	}
	return f[i][j]=ret;
	
}


int main(){
	memset(f,-1,sizeof f);
	scanf("%d",&n);
	for(int i=0;i<=9;++i)
		scanf("%d",&a[i]);
	for(int i=0;i<=n;++i){
		C[i][0]=1;
		for(int j=1;j<=i;++j)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	ll ans=0;
	for(int i=1;i<=n;++i){
		ans=(dp(i,0)+ans)%mod;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

