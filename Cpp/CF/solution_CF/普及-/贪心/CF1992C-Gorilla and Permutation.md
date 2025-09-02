# Gorilla and Permutation

## 题目描述

Gorilla and Noobish\_Monk found three numbers $ n $ , $ m $ , and $ k $ ( $ m < k $ ). They decided to construct a permutation $ ^{\dagger} $ of length $ n $ .

For the permutation, Noobish\_Monk came up with the following function: $ g(i) $ is the sum of all the numbers in the permutation on a prefix of length $ i $ that are not greater than $ m $ . Similarly, Gorilla came up with the function $ f $ , where $ f(i) $ is the sum of all the numbers in the permutation on a prefix of length $ i $ that are not less than $ k $ . A prefix of length $ i $ is a subarray consisting of the first $ i $ elements of the original array.

For example, if $ n = 5 $ , $ m = 2 $ , $ k = 5 $ , and the permutation is $ [5, 3, 4, 1, 2] $ , then:

- $ f(1) = 5 $ , because $ 5 \ge 5 $ ; $ g(1) = 0 $ , because $ 5 > 2 $ ;
- $ f(2) = 5 $ , because $ 3 < 5 $ ; $ g(2) = 0 $ , because $ 3 > 2 $ ;
- $ f(3) = 5 $ , because $ 4 < 5 $ ; $ g(3) = 0 $ , because $ 4 > 2 $ ;
- $ f(4) = 5 $ , because $ 1 < 5 $ ; $ g(4) = 1 $ , because $ 1 \le 2 $ ;
- $ f(5) = 5 $ , because $ 2 < 5 $ ; $ g(5) = 1 + 2 = 3 $ , because $ 2 \le 2 $ .

Help them find a permutation for which the value of $ \left(\sum_{i=1}^n f(i) - \sum_{i=1}^n g(i)\right) $ is maximized.

 $ ^{\dagger} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation (as $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation (as $ n=3 $ , but $ 4 $ appears in the array).

## 说明/提示

In the first example, $ \left(\sum_{i=1}^n f(i) - \sum_{i=1}^n g(i)\right) = 5 \cdot 5 - (0 \cdot 3 + 1 + 3) = 25 - 4 = 21 $

## 样例 #1

### 输入

```
3
5 2 5
3 1 3
10 3 8```

### 输出

```
5 3 4 1 2
3 2 1
10 9 8 4 7 5 6 1 2 3```

# 题解

## 作者：Garry_HJR (赞：5)

## 题目大意
给 $3$ 个正整数 $n,m,k$。

设 $f(i)=\sum_{j=1}^i p_j \times [p_j\ge k]$，$g(i)=\sum_{j=1}^i p_j \times [p_j \le m]$。

构造一组排列 $p$，令 $\left(\sum_{i=1}^n f(i) - \sum_{i=1}^n g(i)\right)$ 最大。

## 思路分析

明显 $f,g$ 单调不降。

但是这么说太晦涩也太泛了些，我们不妨用大白话来说说这两个函数共同的性质。

这么说，如果你在第 $i$ 个位置制造了贡献 $p$ ，那么在 $i+1,i+2,\dots,n$ 这些位置里，这个 $p$ 都会被计算进去。

再换句话讲，今天的你，将承载昨天的自己继续生活下去，你无法改变过去，但可以选择创造现在，这之后，明天的你又会承载今天的你，继续走下去。

看看式子 $\left(\sum_{i=1}^n f(i) - \sum_{i=1}^n g(i)\right)$，明显我们要让 $\sum_{i=1}^n f(i)$ 尽可能大，让 $\sum_{i=1}^n g(i)$ 尽可能小。

由于我上面说的这两个函数的性质，我们一定要尽量让 $f$ 的收益创造时间更往前，让 $g$ 的收益创造时间更往后。

我们观察到 $f(i)$ 创造收益需要 $p_i \ge k$，$g(i)$ 创造收益需要 $p_i \le m$。

这样的话用白话讲，我们要让大的尽可能到前面，小的尽可能到后面。

想到这里，直觉让我们从大到小排序，这就是最终答案。

但，真的是这样吗？

不是的。

我们将样例的第一组数据按照直觉排序，你将得到下面的数据。

![数据1](https://cdn.luogu.com.cn/upload/image_hosting/iaq4wrh9.png)

我们再看看，
这里的 $\left(\sum_{i=1}^n f(i) - \sum_{i=1}^n g(i)\right)=20$。

然而样例解释是 $21$，这就告诉我们错了。

再一看，由于我们把 $2$ 放在了 $1$ 前面，因此这个 $2$ 就会被计入两次贡献，不优。

我们应该把 $1$ 放在 $2$ 前面，这样的话 $1$ 会被计入 $2$ 次贡献，$2$ 只会被计入一次贡献，明显更优。

下面的图为我们证明了这点。

![数据2](https://cdn.luogu.com.cn/upload/image_hosting/zxt62zgf.png)

推广一下，我们应该在最后面把 $m,m-1,\dots,1$ 给重排成 $1,2,\dots,m$，减小大数的贡献。

得解。

## 代码展示
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n,m,k;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m>>k;
		for(int i=n;i>m;i--)cout<<i<<' ';
		for(int i=1;i<=m;i++)cout<<i<<' ';
		cout<<endl;
	}
}
```

---

## 作者：MhxMa (赞：3)

### 分析

这个问题是关于构造一个特定的排列，使得两个函数 $f(i)$ 和 $g(i)$ 的差值最大化。

- $f(i)$：在前 $i$ 个元素中，所有不小于 $k$ 的元素的和
- $g(i)$：在前 $i$ 个元素中，所有不超过 $m$ 的元素的和。

题意需要我们最大化下面这个式子：
$$
\sum_{i=1}^n f(i) - \sum_{i=1}^n g(i)
$$

由于 $m<k$，如果一个元素 $x$ 满足 $m<x<k$，那么它既不会增加 $f(i)$ 也不会增加 $g(i)$。

so，我们需要确保 $f(i)$ 的增加速度尽可能快， $g(i)$ 的增加速度尽可能慢，从而最大化两者的差值。排列如下：  

- 影响 $f(i)$，而不影响 $g(i)$ 的数：输出 $k$ 到 $n$ 的数。

- 不影响 $f(i)$，而影响 $g(i)$：从 $m+1$ 开始，输出到 $k-1$。

- 既影响 $f(i)$，也会影响 $g(i)$：输出 $1$ 到 $m$，由于 $f(i)$ 和 $g(i)$ 都会增加相同的量，所以他们的差值不会改变。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int T;
int n, m, k;

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &m, &k);
		for (int i = n; i >= k; --i) // 影响 f(i)，而不影响 g(i) 的数
			cout << i << " ";
		for (int i = m + 1; i <= k - 1; ++i) // 不影响 f(i)，而影响 g(i) 的数
			cout << i << " ";
		for (int i = 1; i <= m; ++i) // 即影响 f(i)，也影响 g(i) 的数
			cout << i << " ";
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：__zyq_666_kpzc__ (赞：2)

### [中文题面](https://vjudge.net.cn/problem/CodeForces-1992C#author=GPT_zh)
### 思路分析
根据题意，我们可以知道：$g$ 与 $f$ 符合前缀和性质。

我们可以把不大于 $m$ 的所有数字放到最后面，最小化 $g$，再把不小于 $k$ 的所有数字放到前面，最大化 $f$，最后把其余数字放在中间，就可以将获得题目要求的最优排列。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k,a[100005],ans=0;
void w(){
    int n,m,k;
    cin>>n>>m>>k;
	for(int i=n;i>=k;i--){
		cout<<i<<" ";
	}
	for(int i=m+1;i<k;i++){
		cout<<i<<" ";
	}
	for(int i=1;i<=m;i++){
		cout<<i<<" ";
	}
	cout<<"\n";
	return;
} 
signed main(){
	ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
  	int T;
	cin>>T;
	while(T--){
		w();
	} 
	return 0;
} 
```

---

## 作者：coding_goat (赞：1)

因为要使 $ \left(\sum_{i=1}^n f(i) - \sum_{i=1}^n g(i)\right) $ 最大，所以要使 $f(i)$ 大的同时使 $g(i)$ 小。我们把区间分成 $[1,m]$，$[m+1,k-1]$，$[k,n]$ 三个区间。因为只有 $[k,n]$ 影响 $f(i)$，所以根据 $f$ 的定义，要使 $f$ 大只有将 $[k,n]$ 放在最前面，且从 $n$ 到 $k$ 输出。同理，我们将 $[1,m]$ 放在最后，从 $1$ 到 $m$ 输出。剩下的 $[m+1,k-1]$ 不会影响两个函数的取值，于是放在中间即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mem(a,b) memset((a),(b),sizeof(a))
#define lb(x) ((x)&-(x))
#define lc(x) ((x)<<1)
#define rc(x) (((x)<<1)|1)
#define pb(G,x) (G).push_back((x))
using namespace std;
inline int read()
{
	int xx=0;int f=1;
	char c = getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-') f = -1;
		c = getchar();
	}
	while(c>='0'&&c<='9')
	{
		xx = (xx<<1)+(xx<<3)+(c^48);
		c = getchar();
	}
	return xx*f;
}
#define maxn 200050

int n,m,k;

void work()
{
	n=read(),m=read(),k=read();
	for(int i=n;i>=k;i--) cout<<i<<' ';
	for(int i=m+1;i<k;i++) cout<<i<<' ';
	for(int i=1;i<=m;i++) cout<<i<<' ';
	puts("");
}

signed main()
{
	int _=read();
	while(_--) work();
	return 0;
}
```

---

## 作者：dutianchen1 (赞：1)

# CF1992C
#### 题意翻译
本题是要求我们对一个 $[1,n]$ 的排列进行构造。其中令 $f(i)$ 为前 $i$ 个数中不大于 $m$ 的数的和，$g(i)$ 为前 $i$ 个数中不小于 $k$ 的数的和。

我们的目标是要对原来 $[1,n]$ 的排列构造，使得 $ {\textstyle \sum_{i=1}^{n}}f(i)-{\textstyle \sum_{i=1}^{n}}g(i)$ 最小。

#### 思路
简单来说，我们构造的思路主要就是使得 ${\textstyle \sum_{i=1}^{n}}f(i)$ 更大，同时让 ${\textstyle \sum_{i=1}^{n}}g(i)$ 更小。

那么我们就需要让大的数尽量往前放，小的数往后放。

而所谓“大的数”与“小的数”的界定标准与 $m$ 有关。比 $m$ 大的数就构造在排列的前面，反之则放在后面。

在此基础上，我们为了使得 ${\textstyle \sum_{i=1}^{n}}f(i)$ 更大，就需要让比 $m$ 大的数按照降序排列，使得其中较大的数可以被多次计算。同理，比 $m$ 小的数就需要升序排列，使得其中较大的数减少计算次数。

------------
代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6+5;
inline ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
ll num[N];
ll n,T;
int main()
{
	cin.tie(0);cout.tie(0);
	T=read();
	while(T--)
	{
		n=read();
		ll m,k;
		m=read();k=read();
		for(int i=n;i>m;i--)cout<<i<<' ';
		for(int i=1;i<=m;i++)cout<<i<<' ';
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Malkin_Moonlight (赞：1)

## 题解：CF1992C Gorilla and Permutation

## 思路

为了解决这个问题，我们需要构造一个长度为 $ n $ 的排列，使得差值 $ \sum_{i=1}^n f(i) - \sum_{i=1}^n g(i) $ 最大。

为了最大化差值 $ \sum_{i=1}^n f(i) - \sum_{i=1}^n g(i) $：

1. 在贡献 $ f(i) $ 最多的位置（即元素至少为 $ k $ 的位置）尽可能放置较大的数。
2. 在贡献 $ g(i) $ 较少的位置（即元素最多为 $ m $ 的位置）尽可能放置较小的数。

这种方法确保我们最大化了差值，因为：

- $ f(i) $ 会累积较大的值，因为我们在贡献 $ f(i) $ 的位置放置了较大的数。

- $ g(i) $ 会累积较小的值，因为我们在贡献 $ g(i) $ 的位置放置了较小的数。

---

## 作者：Pursuewind (赞：1)

很抽象的一道题。

# 题意简述

给定 $n,m,k$（$m<k$）。

对于一个长度为 $n$ 的排列 $a$，定义：

$g(i)=\sum\limits_{i=1}^i (a_i \le m) \times a_i$。

$f(i)=\sum\limits_{i=1}^i (a_i \ge k) \times a_i$。

构造一个排列 $a$ 使得：

$$\sum\limits_{i=1}^n f(i)-\sum\limits_{i=1}^n g(i)$$

最大，输出排列。

# 做法

显然，$f$ 与 $g$ 函数是单调不降的。

显然，我们要最大化 $f$，同时最小化 $g$。

注意到 $m<k$，所以说 $f$ 与 $g$ 没有交集。或者说没有一个整数 $x$ 既满足 $x \le m$，又满足 $x \ge k$。

于是我们可以将 $1 \sim n$ 的所有数 $x$ 分为 $3$ 类：

- $x \ge k$，这一部分对 $f$ 有贡献。
- $x \le m$，这一部分对 $g$ 有贡献。
- $x \in (m,k)$，这一部分没有任何贡献。

我们来分析一个整数 $x$ 放在第 $i$ 位会产生怎样的影响。

- $x \ge k$，贡献 $x(n-i+1)$，应当让其最大化。
- $x \le m$，贡献 $-x(n-i+1)$，应当让其最大化，也就是让 $x(n-i+1)$ 最小化。
- $x \in (m,k)$，贡献为 $0$。

看到这里，聪明的你一定看出了，对于 $x \ge k$ 的数，要将更大的 $x$ 放在更靠前的位置；对于 $x \le m$ 的数，要将更小的 $x$ 放在更靠前的位置。

于是这样构造：

${\color{red}n,n-1,\dots,k+1,k},{\color{green}k-1,\dots,m+1},{\color{blue}1,2,\dots,m-1,m}$

$3$ 中颜色对应 $3$ 种不同的 $x$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;
int a[N], b[N];
int n, m, k;
void solve()
{
	cin >> n >> m >> k;
	for (int i = n; i > m; i --){
		cout << i << " ";
	}
	for (int i = 1; i <= m; i ++){
		cout << i << " ";
	}
	cout << "\n";
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while (t --) solve();
	return 0;
}
```

---

## 作者：SnapYust (赞：0)

### 更好的阅读体验

[这里](https://www.cnblogs.com/snapyust/p/18300198)

### 题目传送门

[Gorilla and Permutation](https://www.luogu.com.cn/problem/CF1992C)

### 题意

给定正整数 $n,m,k$，假设有一个关于 $n$ 的排列 $\{a_n\}$，那么 $f(i)=\sum_{j=1}^i a_i|a_i\ge k,g(i)=\sum_{j=1}^i a_i|a_i\le m$。

需要求一个 $n$ 的排列，最大化 $\sum_{i=1}^n f(i)-\sum_{i=1}^n g(i)$。

### 思路

**贪心**。

在求两个正整数的最大差时，有一种思路就是在最大化被减数的同时最小化减数，这道题就可以用这种思路。

首先考虑如何**最大化** $\sum_{i=1}^n f(i)$。易得我们只需要在排列前端把 $k$ 到 $n$ 从大到小排序即可。

**因为越大的数越靠前，那么其产生的价值就越大。**

举个例子：

$\{a_n\}=[a,b,10,c,d]$

$\{a_n\}=[10,a,b,c,d]$

当 $10$ 放在第三个位置时，其产生的贡献永远比 $10$ 放在第一个位置时产生的贡献少！

其次考虑如何**最小化** $\sum_{i=1}^n g(i)$。易得我们只需要在排列末端把 $1$ 到 $m$ 从小到大排序即可。

证明同上。

注意到 $k>m$，所以这两个操作并不交叉。至于那些大于 $m$ 又小于 $k$ 的数，随便放就行了。

直白地，对于给定的 $n,m,k$，我们给出的排列应当是：

$$n,n-1,\cdots,k+1,k,\cdots,1,2,\cdots,m-1,m$$

### 代码

```
#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--){
        int n,m,k;cin>>n>>m>>k;
        for(int i=n;i>m;i--)cout<<i<<' ';
        for(int i=1;i<=m;i++)cout<<i<<' ';
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：__DayLight__ (赞：0)

## 前言


[原题机翻。](https://www.luogu.com.cn/discuss/855295)
## 思路


上过小学的都知道：

>被减数 - 减数 = 差

而要让差尽量的**大**，就要让被减数尽量的**大**，减数要尽量的**小**。

所以要让 $ \left(\sum_{i=1}^n f(i) - \sum_{i=1}^n g(i)\right) $ 最大，就要让 $\sum_{i=1}^n f(i)$ 最大化，让 $\sum_{i=1}^n g(i)$ 最小化。

具体怎么操作呢？

1. 降序输出比 $m$ 大的数，这样下来，$g(i)$ 能一直保持为 $0$，也能使 $f(i)$ 保证取到序列中未取数的最大数，让差最大。

1. 升序输出剩下的数，原理类似于上一步，让 $g(i)$ 保证取到序列中未取数的最小数，让差最大。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,k;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>m>>k;
		//希望后来有 dalao 能找到这个 k 的用处。 
		for(int i=n; i>m; i--)
			cout<<i<<' ';
		for(int i=1; i<=m; i++)
			cout<<i<<' ';
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：_H17_ (赞：0)

## 题目分析

注意到 $f,g$ 都是前缀和性质的，所以前面的数权重大。

于是 $[k,n]$ 从大到小放最前面，用来最大化 $g$；$(m,k)$ 乱放；$[1,m]$ 从小到大放最后，用来最小化 $f$。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int T,n,m,k;
signed main(){
	for(cin>>T;T;--T){
		cin>>n>>m>>k;
		for(int i=n;i>=k;i--)
			cout<<i<<' ';
		for(int i=k-1;i>m;i--)
            cout<<i<<' ';
        for(int i=1;i<=m;i++)
            cout<<i<<" \n"[i==m];
	}
	return 0;
}
```

---

## 作者：ArcNick (赞：0)

这里提供一种~~投机取巧~~打表找规律的做法。

首先我们要看看符合答案要求的排列长什么样子。不难得到从官方第三组样例 `10 9 8 4 7 5 6 1 2 3` 得到的具体数值为 $235$。那么我们就把等于 $235$ 的所有排列都列出来，代码如下：
```cpp
void solve() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        a[i] = i;
    }
    do {
        int tf = 0, tg = 0, f = 0, g = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] >= k) tf += a[i];
            if (a[i] <= m) tg += a[i];
            f += tf;
            g += tg;
        }
        if (f - g == 235) {
            for (int i = 1; i <= n; i++) {
                cout << a[i] << ' ';
            }
            cout << endl;
        }
    } while (next_permutation(a + 1, a + 1 + n));
}
```
然后可以得到 $24$ 组数据，这里只列一部分：
```
10 9 8 4 5 6 7 1 2 3 
10 9 8 4 5 7 6 1 2 3 
10 9 8 4 6 5 7 1 2 3
10 9 8 4 6 7 5 1 2 3
```
发现答案为前面一部分从 $n$ 到 $k$ 降序排，后面一部分从 $1$ 到 $m$ 升序排，中间剩下的随便填就好，并且发现前两个官方样例也满足这个做法！

参考代码：
```cpp
void solve() {
    cin >> n >> m >> k;
    for (int i = n; i >= k; i--) cout << i << ' ';
    for (int i = m + 1; i < k; i++) cout << i << ' ';
    for (int i = 1; i <= m; i++) cout << i << ' ';
    cout << '\n';
}
```

---

## 作者：wangzc2012 (赞：0)

# CF1992C Gorilla and Permutation
## 思路分析
根据题意，我们要使 $ \left(\sum_{i=1}^n f(i) - \sum_{i=1}^n g(i)\right) $ 尽可能大。因此，我们需要将被减数尽可能增大，减数尽可能减小。    
所以，我们将所有不小于 $k$ 的数字按降序排列，并放置于开头，使 $\sum_{i=1}^n f(i)$ 最大；再将所有不大于 $m$ 的数按升序排列，并放置于末尾，使 $\sum_{i=1}^n g(i)$ 最小。至于其他的数，直接将其穿插进中间，随便放置即可。
## AC Code
~~因为本人是一只蒟蒻，所以代码有点丑，请谅解。~~
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,k;
int main(){
    cin>>t;
    while (t--){
        cin>>n>>m>>k;
        for (int i=n;i>m;i--) cout<<i<<' ';
        for (int i=1;i<=m;i++) cout<<i<<' ';
        cout<<'\n';
    }
    return 0;
}
```

---

## 作者：tzzl3035 (赞：0)

# CF1992C 题解
### 题目大意
有 $t$ 组数据，每组给出三个整数 $n$，$m$ 和 $k$。刚开始有一个长度为 $n$ 的序列 $1,2 \dots n-1,n$。定义 $g(i)$ 为前 $i$ 项不大于 $m$ 的所有数字之和，$f(i)$ 为前 $i$ 项不小于 $k$ 的所有数字之和。请你重新排列这个序列后，使 $\sum_{i=1}^{n} f(i) - \sum_{i=1}^{n} g(i)$ 最大。
### 思路
想要让两者的差尽量大，需要让被减数尽量大，减数尽量小。通过研究样例，可以发现，想要让 $\sum_{i=1}^{n} f(i)$ 尽量大，需要将所有不小于 $k$ 的数字放在序列最开头，且按降序排列；想要让 $\sum_{i=1}^{n} g(i)$ 尽量小，需要让不大于 $m$ 的所有数字放在序列最末尾，且按升序排列。而剩下的数字，放中间随便排即可。
### 代码
``` c++
#include <bits/stdc++.h> // 万能头
using namespace std;
using i64 = long long;
 
void solve() {
	int n, m, k;
	cin >> n >> m >> k; // 输入
	// 按结论输出
	for(int i = n; i > m; i--) {
		cout << i << ' ';
	}
	for(int i = 1; i <= m; i++) {
		cout << i << ' ';
	}
	cout << '\n';
}
 
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
 
	int t;
	cin >> t;
	// 挨组处理
	while(t--) {
		solve();
	}
	
	return 0;
}
```
### [RESULT](https://codeforces.com/contest/1992/submission/270571155)

---

## 作者：Fish_redflying (赞：0)

一道构造题。

考虑贪心。我们可以尝试将这个排列变成一个下降排列。

因为题目给的函数 $f(i)$ 是从**前缀**操作的，且阐明是求前缀大于等于 $k$ 的数之和。由于下降排列可以使每一次前缀都取到**最大**的值，就是**越前越大**，故此考虑。

参考样例，得出：`5 4 3 2 1`。

容易发现，$f(i)$ 没什么问题，但 $g(i)$ 取出的值与事实不符。

显然，是因为先取了 $2$ ，而不是 $1$ 。导致了 $(2)+(2+1)=5$。

从贪心的角度来说，我们需让 $g(i)$ 取到的值尽量减小。

所以，考虑上升排列，这样的排列可以使前缀**最小**。

这种排列的性质和下降排列相反，效果也相反，所以我们可以在
$g(i)$ 的影响的范围内操作，也就是 $n-m+1$ 至 $n$ 。

具体看代码。~~马蜂清奇，不要见怪。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,k;
int main()
{
	scanf("%d",&t);
	while(t--) {
		scanf("%d%d%d",&n,&m,&k);
		for(int i=n;i>m;i--)  printf("%d ",i);
		for(int i=1;i<=m;i++) printf("%d ",i);
		printf("\n");
	}
}
```

---

