# [ICPC 2022 Xi'an R] Find Maximum

## 题目描述

定义在所有非负整数 $x$ 上的函数 $f(x)$ 如下：

$$
f(x) =
\begin{cases}
1 & (x = 0) \\
f(\frac{x}{3}) + 1 & (x > 0\land x\bmod3 = 0) \\
f(x - 1) + 1  & (x > 0\land x\bmod 3\neq 0)
\end{cases}
$$

计算 $\max_{x = l} ^ r f(x)$。

共有 $T$ 组数据。

$1\leq T\leq 10 ^ 4$，$1\leq l\leq r\leq 10 ^ {18}$。

## 样例 #1

### 输入

```
10
1 2
1 3
1 4
1 5
2 3
2 4
2 5
3 4
3 5
4 5
```

### 输出

```
3
3
4
5
3
4
5
4
5
5
```

# 题解

## 作者：chenzhixing_ (赞：3)

# P9362 \[ICPC 2022 Xi'an R] Find Maximum 题解

[题目链接](https://www.luogu.com.cn/problem/P9362)

---

## 题意理解

这道题目的第一个难点就是如何理解题意。

仅凭“注意到” 三个字，就得出三进制下的性质，显然是不负责任的。

所以我们来说明一下我是如何得出原式的规律的。

$$
f(x) =
\begin{cases}
1 & (x = 0) \\
f(\frac{x}{3}) + 1 & (x > 0\land x\bmod3 = 0) \\
f(x - 1) + 1 & (x > 0\land x\bmod 3\neq 0)
\end{cases}
$$

观察原式，发现第一个条件对整个式子的影响其实不大：它只是整个递推式的初始值。而第二、三个条件只涉及递增，不涉及倍乘，所以第一个限定条件我们可以忽略。

那么看第二、三个限定条件分别限定了什么。

第二个式子的意思是：当函数自变量翻三倍的时候，函数值增加一；

第三个式子的意思是：当函数自变量增加一的时候，如果没有被三的倍数占用，函数值加一。

我们以加一为右儿子，乘三为左儿子建树，画出来看一下，大概就长这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/op5ynfg9.png)

其中节点的深度就代表着以这个点编号为自变量对应的函数值。

因为每个节点最多只有两种向外扩展的方式：加一，或者乘以三，所以这棵树一定是一颗二叉树。

同时，因为我们的规定，以三的倍数为编号的节点一定是左儿子，所以右儿子所构成的链条长度一定都等于三，并且以三的倍数起头。

这个时候需要一点注意力，不过也就是绿题的水平：既然这道题与三有这么大的关系，不妨用三进制想一想。

在三进制中，乘以三就是左移一位，不冲突三的倍数的加一，就是在末位不进位的加一。

所以，在不进位的情况下加一，就代表着末位的数码加一；乘以三，就代表位数加一。因此，**函数值刚好就是三进制下位数加各位上数码之和**。

## 算法设计

问题转为了在 $[L,R]$ 的区间里找到三进制上位数加上各个数码的和的最大值。

因为直接枚举复杂度是 $\operatorname O(n \times T)$ 的，显然不能通过。所以我们考虑效率更高的做法：数位 DP。

这里采用记忆化搜索的写法，以下是一般模板。

```cpp
int f[MAXN][MAXSIT];
bool st[MAXN][MAXSIT];

int lower_range[MAXN], upper_range[MAXN];

int dfs(int len, int op, bool zero, bool lower, bool upper) // 参数分别代表当前处理的从低到高的位数，只考虑到上一位的答案，是否仍然存在前导零，之前的位是否压着下界，之前的位是否压着上界
{
  if (!zero && !upper && !lower && st[len][op]) // 因为不同的条件下可能对答案产生很大的影响，所以要确保储存的条件一致，这里就只储存无前导零，不压界的情况。当然这些条件也可以都写进记忆化，不过代码过于冗长。
    return f[len][op]; // 记忆化剪枝
  if (!len) // 如果之前已经处理完所有位
    return op; //返回处理完上一位的答案
  int l = lower ? lower_range[len] : 一般最小边界;
  int r = upper ? upper_range[len] : 一般最大边界;
  int ans = 初始值;
  for (int i = l; i <= r; ++i)
    update(ans, dfs(len - 1, f(op), zero && !i, lower && i == l, upper && i == r));
  if (!zero && !upper && !lower) st[len][op] = 1, f[len][op] = ans;
  return ans;
}
```

因为我们需要的是最大值，所以记忆化数组记录最大值，`update` 自然也是使用最大值，同时使用 `int` 类型的标记数组，通过比对标记的时间是否与当前询问的时间一致来判断是否已经被记忆化剪去。

接下来的问题是记搜函数的参数：首先肯定要传入**当前处理的位数**；为了控制上下界以及前导零，我们在记忆化搜索函数中额外传入**是否有前导零**、**之前的位数是否抵住上界**，**之前的位数是否抵住下界**。最后在传入一个参数表示**这位之前的答案**即可。

记忆化只要是**不抵上下界**并且**无前导零**的条件下就可以。

处理 `lower_range` 和 `upper_range` 只需要将输入的 `l`，`r` 变为三进制即可。

最后是转移，分别维护上下边界、前导零以及当前位答案，最后统计返回的最大值作为答案返回即可。

最终实现大概是这样：

```cpp
int a[M], b[M], n;
int f[M][K], st[M][K], tot = 1;

int dfs(int len, int op, bool zero, bool lower, bool upper)
{
    if (st[len][op] == tot && !lower && !upper && !zero) return f[len][op];
    if (!len) return zero ? 1 : op; // 因为 0 对应的答案是 1
    int l = lower ? a[len] : 0, r = upper ? b[len] : 2, ans = 0;
    for (int i = l; i <= r; ++i)
        ans = max(ans, dfs(len - 1, op + (!zero || i) + i, zero && !i, lower && i == l, upper && i == r));
    if (!zero && !upper && !lower) return st[len][op] = tot, f[len][op] = ans;
    return ans;
}

int calc1(int x, int a[]) // 三进制拆分
{
    memset(a, 0, sizeof(int) * M); // 一定要清零
    int len = 0;
    while (x)
    {
        a[++ len] = x % 3;
        x /= 3;
    }
    return len;
}
```

## 总结

这道题是一道基础的 数位DP 好题，除了最开始的注意到以外没有什么特别难的思维点，不过 数位DP 的具体实现是比较细节也比较容易出错的。

---

## 作者：pikiuk (赞：3)

在三进制下考察 $f$ 函数，不难发现其含义为 $n$ 在三进制下的数位个数和数码和。

这个东西显然是可以贪心解决的，具体的，对于每一位，可以顶格填写，或者少填 $1$，后面全部填三，动态维护最大值即可。

```
#include<bits/stdc++.h>
#define int long long
#define Li 38
using namespace std;
int T, l, r, B[47], L[47], R[47], ans, sum, now, flag;
void solve(){
	cin >> l >> r; now = sum = flag = ans = 0;
	for(int i = Li - 1; ~i; i --){
		L[i] = l % B[i + 1] / B[i];
		R[i] = r % B[i + 1] / B[i];
	}
	for(int i = Li - 1; ~i; i --){
		if(R[i]) flag = 1;
		if(! flag) continue;
		if(R[i] and now + 1ll * R[i] * B[i] - 1 >= l){
			if(R[i] > 1 or sum) ans = max(ans, sum + R[i] + 1ll * 3 * i);
			else ans = max(ans, sum + 1ll * 3 * i);
		}
		sum = sum + R[i] + 1; now = now + 1ll * R[i] * B[i];
	} return cout << max(ans, sum) << "\n", void();
}
signed main(){
	B[0] = 1; for(int i = 1; i <= Li; i ++) B[i] = 1ll * B[i - 1] * 3;
	cin >> T; while(T --) solve(); 
}
```

---

## 作者：0x282e202e2029 (赞：3)

# P9362 [ICPC2022 Xi'an R] Find Maximum 题解

[题目传送门](https://www.luogu.com.cn/problem/P9362)

## 题意

给定边界 $L$ 和 $R$，求满足 $L  \leqslant x  \leqslant R$ 的所有 $x$ 对应的 $f(x)$ 的最大值。

其中，$f(x)$ 满足：

$$f(x) = \begin{cases}
   1 &\text{if } x = 0 \\
   f(\frac{x}{3}) + 1 &\text{if } x > 0 \wedge x \equiv 0 \pmod 3 \\
   f(x - 1) + 1 &\text{otherwise} \\
\end{cases}$$

## 思路

初看似乎没有思路，于是打表找规律。

观察表达式，似乎与 $3$ 进制有关，但说不出具体关联。

![](https://cdn.luogu.com.cn/upload/image_hosting/xe6bg0ac.png)

(表格显示炸了，所以用图片）

我们发现，真的有关系！

$f(x)$ 等于 **$x$ 的三进制表达中有效位数与数码和之和**。

于是问题转化为在 $[L, R]$ 区间中的所有数的三进制表达中有效位数与数码和之和的最大值。

那么分类讨论，用 $len(x)$ 表示 $x$ 的三进制表达中的有效位数。

情况 $1$：

$len(L) < len(R)$，那么 $x$ 可能是 $({\underbrace{22\cdots2}_{\text{len(R) - 1 个 2}}})_3$，或者在 $[({\underbrace{100\cdots0}_{\text{len(R) - 1 个 0}}})_3, R]$ 之间选择。

情况 $2$：

$len(L) = len(R)$，直接在 $[L, R]$ 之间选择即可。

## AC 代码

```cpp
#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;
int res;
vector<int> getTernary(long long k)
{
    vector<int> v;
    if(!k)
	{
		v.push_back(0);
	}
    while(k)
    {
        v.push_back(k % 3);
        k /= 3;
    }
    reverse(v.begin(), v.end());
    return v;
}//计算一个数的三进制
void cal(vector<int> l, vector<int> r, int pos, int sum, int limitr)
{
    if(limitr)
    {
        int ans = sum + (r.size() - pos) * 2 + r.size();
        res = max(res, ans);
        return ;
    }
    if(pos == r.size())
    {
        int ans = sum + r.size();
        res = max(res, ans);
        return ;
    }
    int limit = r[pos];
    cal(l, r, pos + 1, sum + limit, 0);
    if(limit - 1 >= l[pos])
	{
		cal(l, r, pos + 1, sum + limit - 1, 1);
	}
}//计算结果
vector<int> L, R;
int T;
long long l, r;
int main()
{
    scanf("%d", &T);
    while(T--)
    {
    	res = 0;
    	scanf("%lld%lld", &l, &r);//用了long long，但是写了一次%d%d（苦笑）
    	L = getTernary(l), R = getTernary(r);
    	if(L.size() < R.size())
    	{
        	res = (R.size() - 1) * 2 + R.size() - 1;
        	vector<int> backup;
        	backup.push_back(1);
        	for(int i = 1; i < R.size(); i++) 
			{
				backup.push_back(0);
			}
        	cal(backup, R, 0, 0, 0);
    	}
    	else
    	{
        	cal(L, R, 0, 0, 0);
    	}//分类讨论
    	printf("%d\n", res);
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/112378694)

## 结尾多说几句

本题的坑点：

+ 俗话说得好，

> 十年 OI 一场空，不开 `long long` 见祖宗。

$10^{18}$ 的数据范围，一定要开 `long long`！一定要开 `long long`！一定要开 `long long`！

+ 开了 `long long` 后 `scanf` 要用 `%lld`！开了 `long long` 后 `scanf` 要用 `%lld`！开了 `long long` 后 `scanf` 要用 `%lld`！

---

