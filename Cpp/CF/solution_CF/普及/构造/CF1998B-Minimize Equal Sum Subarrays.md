# Minimize Equal Sum Subarrays

## 题目描述

# 最小化相等和子数组


已知 [农夫约翰喜欢排列](https://usaco.org/index.php?page=viewproblem2&cpid=1421)，我也喜欢它们！

给定一个长度为 $ n $ 的排列 $ p $。

找到一个长度为 $ n $ 的排列 $ q $，使得以下条件下的对数最小化：对所有 $ 1 \leq i \leq j \leq n $，使得 $ p_i + p_{i+1} + \ldots + p_j = q_i + q_{i+1} + \ldots + q_j $。

**注**：一个长度为 $ n $ 的排列是一个包含 $ 1 $ 到 $ n $ 的 $ n $ 个不同整数的数组。例如，\[2, 3, 1, 5, 4\] 是一个排列，但 \[1, 2, 2\] 不是一个排列（数字 2 在数组中出现了两次），而 \[1, 3, 4\] 也不是一个排列（$ n=3 $，但数组中有 4）。

## 说明/提示

对于第一个测试用例，存在唯一一对 $ (i, j) $ ($ 1 \leq i \leq j \leq n $) 使得 $ p_i + p_{i+1} + \ldots + p_j = q_i + q_{i+1} + \ldots + q_j $，即 $ (1, 2) $。可以证明，没有这样的 $ q $ 使得不存在满足条件的对。

## 样例 #1

### 输入

```
3
2
1 2
5
1 2 3 4 5
7
4 7 5 1 2 6 3```

### 输出

```
2 1
3 5 4 2 1
6 2 1 4 7 3 5```

# 题解

## 作者：GLr137 (赞：1)

这题的意思十分简单明了，就是给你一个排列 $ p $，你需要求出一个排列 $ q $ ，使得两个数列中每一个头尾位置相同的区间中所有数之和相等的区间数量尽可能少（不是太好懂，好好琢磨一下）。

那么，该怎么求出这样的数列呢？别急，慢慢来。

首先，我们需要知道，$ q $ 肯定是由 $ p $ 进行位置移动得到的，所以说我们可以考虑一下最简单的方法：把每个数向左（或向右）移动一位。

那么这种办法是否可行呢？我们用一张表格来证明。

|p|1|2|3|4|5|
|:-:|:-:|:-:|:-:|:-:|:-:|
|q|2|3|4|5|1|

不难发现，如果左移了一位，长度为 $ 1 $ 的区间中的数都不同，如果长度 $ \gt 1 $ ，那么每一个长度为 $ m $ 的相同区间内都有$ m - 1 $ 个同样的数字，而各自多出来的那个数字，因为排列中没有相同的数字，所以肯定不同，那么也就能证明为什么这样做最好了。

代码：

``` cpp

# include <bits/stdc++.h>
using namespace std;
int main (){
    int t, n, sz[200005];
    cin >> t;
    for (int i = 1; i <= t; i++){
        cin >> n;
        for (int i = 1; i <= n; i++){
            cin >> sz[i];
        }
        for (int i = 2; i <= n; i++){
            cout << sz[i] << " ";
        }
        cout << sz[1] << "\n";
    }
    return 0;
}

```

最后祝大家 [AC](https://codeforces.com/contest/1998/submission/279790835)  愉快！（洛谷交不了，CF 的提交记录）

---

## 作者：Even_If (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1998B)

# Description 
~~赛时脑子抽了，浪费 40min 才切掉~~\
~~很精妙的~~构造题。\
题意就是：给你一个长度为 $n$ 且由 $1$ 到 $n$ 构成的序列 $p$，要构造出一个也由 $1$ 到 $n$ 组成的长度为 $n$ 的序列 $q$，我们设 $sump_{i,j}$ 为从 $p_i$ 到 $p_j$ 的和，$sumq_{i,j}$ 为从 $q_i$ 到 $q_j$ 的和，要使满足 $sump_{i,j}=sumq_{i,j}$ 的 $(i,j)$ 最少。

# Solution
最开始，序列 $q$ 和序列 $p$ 是相同的，而这时，所有的 $sump_{i,j}$ 和 $sumq_{i,j}$ 一一对应。我们只需要让 $sump$ 和 $sumq$ 错位即可，所以，我们可以将 $q$ 中的最后一个元素移到最前面，其他所有的元素向后移一位，这样原来的 $sumq_{i,j}$ 就变成了 $sumq_{i+1,j+1}$，正好错开 $sump{i,j}$。

时间复杂度：$O(Tn)$。

附上代码：
```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

int t;

const int N = 2e5 + 10;
int a[N];

signed main(void) {
	cin >> t;
	
	while (t --) {
		int n;
		cin >> n;
		
		for (int i = 1; i <= n; i ++) {
			cin >> a[i];
		}
		
		cout << a[n] << ' ';//将最后一个元素移到首位
		
		for (int i = 1; i < n; i ++) cout << a[i] << ' ';//将其他所有元素后移
		
		cout << endl;
	}
	
	return 0;//好习惯
}
```

---

## 作者：joe_zxq (赞：1)

模拟样例易得需要最小化的数量就是 $1$，后面会给出证明。

千万不要相信这道题的样例！我们可以自力更生写一个暴力，计算小数据的所有构造方案。易发现，直接将数列错开一位即可。例如样例的序列 $\{1,2,3,4,5\}$ 可以更改为 $\{5,1,2,3,4\}$。

可以发现，除了整个序列之外的其他区间中，都有一个数不同，其他数均相同，显然和就都不一样。于是最小值就是 $1$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll tc, n, a[200024];

void solve() {
	scanf("%lld", &n);
	for (ll i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
	}
	printf("%lld ", a[n]);
	for (ll i = 1; i < n; i++) {
		printf("%lld ", a[i]);
	}
	printf("\n");
}

int main() {

	scanf("%lld", &tc);
	while (tc--) {
		solve();
	}	

	return 0;
}
```

---

## 作者：Cyx20110930 (赞：0)

# 题意简述

给定 $n$，$1$ 到 $n$ 的排列 $p$，试构造出另一个 $1$ 到 $n$ 的排列 $q$ 使得满足 $\sum_{k=i}^j p_k=\sum_{k=i}^j q_k$ 且 $(1\le i\le j\le n)$ 的 $(i,j)$ 数量最少。

# Sol

大水题一个。首先 $(1,n)$ 必然满足要求，所以答案不小于 $1$。

那么尝试找到构造的通解，有一个显而易见的性质：$p$ 中任意两个元素互不相同。

那么，可以这么构造 $q$：$q_i=p_{(i\bmod n) + 1}$，只有 $(1,n)$ 满足要求。

证明：若 $(i,j)$ 满足要求且 $(1\le i\le j\le n)$ ，则 $\sum_{k=i}^j p_k=\sum_{k=i}^j q_k=\sum_{k=(i\bmod n)+1}^{(j\bmod n)+1} p_k$，即 $p_{(j \bmod n) + 1}=p_i$，当且仅当 $i=1,j=n$ 时成立。证毕！

# Code

```
#include <bits/stdc++.h>
using namespace std;
int n,a[200024];
void solve() {
	cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)cout<<a[i%n+1]<<' ';
	cout<<endl;
}

int main() {
    int t;cin>>t;
	while(t--)
		solve();
}
```

---

## 作者：_Mortis_ (赞：0)

## 题意

找到一个排列 $ q $，使得在给定的排列 $ p $ 中，满足 $( p_i + p_{i+1} + \ldots + p_j = q_i + q_{i+1} + \ldots + q_j ) $ 的子数组对 $ (i, j) $ 的数量最少。

## 思路

请不要被样例迷惑！！！

$ p $ 和 $ q $ 都是排列，数字各不相同，那么，我们只要把第一个数放到最后就能最小化答案。

比如：$\left \{ 4,3,5,1,2 \right \} $ 改成 $\left \{ 3,5,1,2,4 \right \} $。

我们发现，对于任意的 $ p_i + p_{i+1} + \ldots + p_j $ 和 $ q_i + q_{i+1} + \ldots + q_j $（$ i = 1,j = n $ 的情况除外），都有 $ p_{i+1} + \ldots + p_j = q_i + q_{i+1} + \ldots + q_{j-1} $，而 $ p_i $ 一定不等于 $ q_j $（$ p_i = q_{i-1},q_{i-1} \ne q_j $），所以当且仅当 $ i = 1,j = n $ 时式子才成立，答案为 $ 1 $ 不能再小。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[200005];
int R(){
	int res=0;char c=getchar();
	while(!(c>='0'&&c<='9'))c=getchar();
	while(c>='0'&&c<='9')res=(res<<3)+(res<<1)+(c^48),c=getchar();
	return res;
}
void W(int x){
	if(x>9)W(x/10);
	putchar(x%10^48);
}
int main(){
	for(T=R();T--;){
		n=R();
		for(int i=1;i<=n;i++)a[i]=R();
		for(int i=2;i<=n;i++)W(a[i]),putchar(' ');
		W(a[1]);
		puts("");
	}
	return 0;
}
```

AC 记录暂无，CF 交不了。

---

## 作者：DesignDigits (赞：0)

样例 `1 2` 启发我们猜想一种方案：使 $q_i=p_i+1, $ 若 $p_i=n$ 则 $q_i=1.$

由于 $l=1, r=n$ 不管排列 $q$ 是什么样都一定符合题意，最小的 $(l, r)$ 组数至少为 $1.$

那么
$q_i-p_i = \begin{cases}
1\quad (p_i\neq n)\\
1-n \quad(p_i=n)
\end{cases}$

题目的条件是 $\sum_{i=l}^r (q_i-p_i)=0$，

我们知道如果这个条件成立，这 $r-l+1$ 项不可能全是 $1$，不然加起来怎么会是 $0$ 呢。所以至少有一个 $1-n$。

一旦有一个 $1-n$，剩下 $r-l$ 项的和就必须是 $-(1-n)=n-1$ 了。然而 $r-l\leq n-1$，所以必须 $l=1, r=n$ 才可能。我们知道这时一定是符合题意的。所以这种构造方案的 $(l, r)$ 组数就是 $1$，我们证明了它是最优的。

---

