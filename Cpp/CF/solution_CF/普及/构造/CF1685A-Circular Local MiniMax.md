# Circular Local MiniMax

## 题目描述

给你 $n$ 个整数 $ a_1, a_2, \ldots, a_n $ 。 问有没有可能将它们排列在一个圆上，使每个数字严格地大于其相邻的两个数字或严格地小于其相邻的两个数字？

换句话说，检查是否存在 $ b_1, b_2, \ldots, b_n $ 的整数 $ a_1, a_2, \ldots, a_n $ 的重新排列，使得 $ i $ 从 $ 1 $ 到 $ n $ 中至少有一个以下条件成立。

- $ b_{i-1} < b_i > b_{i+1} $
- $ b_{i-1} > b_i < b_{i+1} $

为了使前面的公式对 $ i=1 $ 和 $ i=n $ 有意义，我们应定义 $ b_0=b_n $ 和 $ b_{n+1}=b_1 $。

## 样例 #1

### 输入

```
4
3
1 1 2
4
1 9 8 4
4
2 0 2 2
6
1 1 1 11 111 1111```

### 输出

```
NO
YES
1 8 4 9 
NO
YES
1 11 1 111 1 1111```

# 题解

## 作者：Patricky (赞：4)

~~你谷写文章包含 emoji 就变成一陀问号，非常难绷~~

UPD: 类似题目推荐 

<https://www.luogu.com.cn/problem/CF1419D2>
<https://www.luogu.com.cn/problem/CF1339B>

~~双倍经验~~ ~~三倍经验~~

## 题意

试重新安排数组各元素，
使得新数组首尾相接之后每个元素要么是局部最大值，
要么是局部最小值（均严格）。

或报告不可能。

## 解答

即是说，使数组单调性形如 `\/\/\/...\/\/\/`，
从该图案中不难发现，如果有解，
则元素个数 **必为偶数**（证明奇数必对应至少一组矛盾也是容易的）。

该如何尽可能安排好该数组呢？
下面是我的思考过程：考虑特殊情况：长度为 $n$ 的排列。
你也许很容易构造一些解（因为是环形，你也许给出了其 `rotate` 们）：

$$
\color{red}{1}  {}_{/} 
\color{blue}{3} {}_{\backslash}
\color{red}{2}  {}_{/}
\color{blue}{5} {}_{\backslash}
\color{red}{4}  {}_{/}
\color{blue}{6} {}_{\backslash}
\color{gray}{1}
$$

$$
\color{red}{1}  {}_{/} 
\color{blue}{4} {}_{\backslash}
\color{red}{2}  {}_{/}
\color{blue}{5} {}_{\backslash}
\color{red}{3}  {}_{/}
\color{blue}{6} {}_{\backslash}
\color{gray}{1}
$$

$$
\color{red}{1}  {}_{/} 
\color{blue}{6} {}_{\backslash}
\color{red}{2}  {}_{/}
\color{blue}{5} {}_{\backslash}
\color{red}{3}  {}_{/}
\color{blue}{4} {}_{\backslash}
\color{gray}{1}
$$

容易发现对于不重的数组，这样的条件是很容易满足的。
接下来考虑有重复元素的数组。

**至多** 可容忍多少重复元素？借助鸽巢原理，若放入 $\dfrac{n}{2}$ 个重复元素，则无论如何安排序列都必有相邻重复元素，这与题意相违。

以如此最坏情形考虑，**排序** 之后总尝试 $a_i \leftrightarrow a_{i + n / 2}$ 配对。✔

$$
[a_1, a_2, a_3, a_4, \cdots, a_{n - 1}, a_n]_{\rm sorted}

\Rightarrow

[a_1, a_{n / 2 + 1}, a_2, a_{n / 2 + 2}, \cdots, a_{n / 2}, a_{n}]
$$

## 参考代码

 + 需要注意 `std::ranges` 是 $C$++ $20$ 及以上标准引入的。

我的做法是选完之后再 $\mathcal O(n)$ 检查这样的方案是否合理。
不过实际上还未造出 $b$ 数组时就可以给出能否了。

```cpp
int solve() {
  int n;
  cin >> n;
  vector<int> a(n);
 
  for (int &i : a) {
    cin >> i;
  }
 
  if (n & 1) {
    return cout << "NO\n", int{};
  }
 
  ranges::sort(a);
  vector<int> b(n);
 
  for (int i = 0; i < n; ++i) {
    b[i] = a[i / 2 + (i & 1 ? n / 2 : 0)];
  }
 
  b.push_back(b.front());
  for (int i = 1; i < n; i += 2) {
    if (b[i - 1] >= b[i] || b[i] <= b[i + 1]) {
      return cout << "NO\n", int{};     
    }
  }
 
  cout << "YES\n";
  for (int i = 0; i < n; ++i) {
    cout << b[i] << " \n"[i + 1 == n];
  }
  
  return {};
}
```

---

## 作者：Lijunzhuo (赞：0)

题意：给定一个长 $n$ 的序列，请输出一种可能的数列，使得该数列整体呈“波浪形”，且把它整体右挪任意位也是如此。

这道题我们可以分类讨论：
1. 若 $n$ 为奇数，则一定构造不出答案数列。证明它我们要先定义一个东西——局部极值：对于每一个数 $a_i$，若大于其左右两个邻居，则它是局部极大值，否则为局部极小值。显然，每一个局部极大值必须有一个对应的极小值。因此，无法使得所有 $n$ 个元素都满足局部极大值或局部极小值的条件，证毕。
2. 若 $n$ 为偶数，我们可以想出如下可能得构造方案：先排序，后把较小的一半依次放在排列的奇数位置（即局部极小值的位置），然后在把较大的一半依次放在排列的偶数位置（即局部极大值的位置）。但是这样还是不行，如样例的第三个测试案例，$n$ 为偶数却无法构造，因为这组数据中有重复的元素，排序放置后无法确定局部极大值与局部极小值，所以我们要再判断一下，我们所构造的数列是否符合条件。

分类讨论完毕，我们可以写出代码了：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int T,n,A[N],ans[N];
bool check()
{
	for(int i=2;i<=n;i++)
		if(ans[i]==ans[i-1])
			return false;
	return true;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&A[i]);
		if(n&1)//无解情况1 
		{
			printf("NO\n");
			continue;
		}
		sort(A+1,A+1+n);
		for(int i=1;i<=(n>>1);i++)
			ans[(i<<1)-1]=A[i];
		for(int i=(n>>1)+1;i<=n;i++)
			ans[(i-(n>>1))<<1]=A[i];
		if(!check())//无解情况2 
		{
			printf("NO\n");
			continue;
		}
		printf("YES\n");//有解
		for(int i=1;i<=n;i++)
			printf("%d ",ans[i]);
		putchar('\n');
	}
	return 0;
}
```
因为洛谷现在不能用 `RemoteJudge` 了，所以没有洛谷里的提交记录，提交记录在[这里](https://codeforces.com/contest/1685/submission/278374030)。

---

