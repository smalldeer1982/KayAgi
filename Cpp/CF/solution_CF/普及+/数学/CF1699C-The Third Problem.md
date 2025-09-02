# The Third Problem

## 题目描述

You are given a permutation $ a_1,a_2,\ldots,a_n $ of integers from $ 0 $ to $ n - 1 $ . Your task is to find how many permutations $ b_1,b_2,\ldots,b_n $ are similar to permutation $ a $ .

Two permutations $ a $ and $ b $ of size $ n $ are considered similar if for all intervals $ [l,r] $ ( $ 1 \le l \le r \le n $ ), the following condition is satisfied: $ $$$\operatorname{MEX}([a_l,a_{l+1},\ldots,a_r])=\operatorname{MEX}([b_l,b_{l+1},\ldots,b_r]), $ $  where the  $ \\operatorname{MEX} $  of a collection of integers  $ c\_1,c\_2,\\ldots,c\_k $  is defined as the smallest non-negative integer  $ x $  which does not occur in collection  $ c $ . For example,  $ \\operatorname{MEX}(\[1,2,3,4,5\])=0 $ , and  $ \\operatorname{MEX}(\[0,1,2,4,5\])=3 $ .</p><p>Since the total number of such permutations can be very large, you will have to print its remainder modulo  $ 10^9+7 $ .</p><p>In this problem, a permutation of size  $ n $  is an array consisting of  $ n $  distinct integers from  $ 0 $  to  $ n-1 $  in arbitrary order. For example,  $ \[1,0,2,4,3\] $  is a permutation, while  $ \[0,1,1\] $  is not, since  $ 1 $  appears twice in the array.  $ \[0,1,3\] $  is also not a permutation, since  $ n=3 $  and there is a  $ 3$$$ in the array.

## 说明/提示

For the first test case, the only permutations similar to $ a=[4,0,3,2,1] $ are $ [4,0,3,2,1] $ and $ [4,0,2,3,1] $ .

For the second and third test cases, the given permutations are only similar to themselves.

For the fourth test case, there are $ 4 $ permutations similar to $ a=[1,2,4,0,5,3] $ :

- $ [1,2,4,0,5,3] $ ;
- $ [1,2,5,0,4,3] $ ;
- $ [1,4,2,0,5,3] $ ;
- $ [1,5,2,0,4,3] $ .

## 样例 #1

### 输入

```
5
5
4 0 3 2 1
1
0
4
0 1 2 3
6
1 2 4 0 5 3
8
1 3 7 2 5 0 6 4```

### 输出

```
2
1
1
4
72```

# 题解

## 作者：tzyt (赞：16)

题目链接[（CF](https://codeforces.com/problemset/problem/1699/C)，[洛谷）](https://www.luogu.com.cn/problem/CF1699C) | 强烈推荐[博客](https://ttzytt.com/2022/07/CF1699C/)中观看。


这题是真的难想，我 cf 的题解看了好久才搞明白（我太菜了）。

# 题意：
给你一个长度为 $n$ 的排列 $a$，请你找出有多少个相同长度的排列 $b$ 和 $a$ 相似。

如果对于所有区间 $[l, r] (1 \le l \le r \le n)$，下面的条件满足：

$$
\operatorname{MEX}(a_l, a_{l + 1}, \ldots , a_r) = \operatorname{MEX}(b_l, b_{l + 1}, \ldots , b_r)
$$

我们就称排列 $a$ 和 $b$ 是相似的。

其中 $\operatorname{MEX}$ 对于数组 $c$ 的定义是：最小的，没有出现在 $c$ 中的非负整数 $x$。

例如 $\operatorname{MEX}([1,2,3,4,5]) = 0 \ \operatorname{MEX}([0,1,2,4,5]) = 3$。 

由于答案可能会很大，所以输出时需要打印答案模 $10^9 + 7$ 的结果。

# 思路
直接想答案可能比较难，可以先模拟一下给出的样例，尝试构造出一些 $b$。

$a = [1, 3, 7, 2, 5, 0, 6, 4]$

我们从 $0$ 这个数字开始考虑样例。可以发现在 $b$ 中，$0$ 的位置一定和 $a$ 中的 $0$ 的位置相等。

为什么呢？我们定义**在 $a$ 中**数字 $i$ 出现的位置为 $\text{pos}_i$，比如 $\text{pos}_0 = 6$ （下标从 $1$ 开始）。

这时，选择 $[\text{pos}_0, \text{pos}_0]$ 的区间对比 $a$ 和 $b$ 的 $\operatorname{MEX}$ 是否相等，首先，在 $a$ 中，因为 $a[\text{pos}_0] = 0$，$a$ 的 $\operatorname{MEX}([\text{pos}_0])$ 一定等于 $1$。

如果 $b$ 的 $0$ 的位置被改变了，那么在 $b$ 中，因为 $a[\text{pos}_0] > 0$，$\operatorname{MEX}([\text{pos}_0])$，就一定等于 $0$ 了。

所以我们可以推断出 $0$ 的位置是不能变的。

我们还能推出，$1$ 的位置也是不能改变的。

可以考虑中 $[\text{pos}_1(1), \text{pos}_0(6)] (1\ 3\ 7\ 2\ 5\ 0)$ 和 $[\text{pos}_1 + 1, \text{pos}_0](3\ 7\ 2\ 5\ 0)$ 这两个区间的 $\operatorname{MEX}$ 值。

因为 $1$ 的存在， $\operatorname{MEX}([\text{pos}_1, \text{pos}_0])$ 一定大于 $1$，而因为有 $0$ 并且没有 $1$ $\operatorname{MEX}([\text{pos}_1 + 1, \text{pos}_0])$ 一定等于 $1$。

架设我们在 $b$ 中改变了 $1$ 的位置，比如改到了 $2$，那么在 $b$ 中， $\operatorname{MEX}([\text{pos}_1 + 1, \text{pos}_0](1\ 7\ 2\ 5\ 0))$ 就大于 $1$ 了，不符合 $a$ 中等于 $1$ 的情况。

---

现在考虑能合法放置 $2$ 的位置。我们可以推断出，如果在 $a$ 中 $2 \in (\text{pos}_1, \text{pos}_0)$，那么在 $b$ 中， $2$ 就可以被放在 $(\text{pos}_1, \text{pos}_0)$ 这个区间的任意位置。

为啥呢？我们设区间 $[l, r]$ 在 $a$ 中包含 $0$ 和 $1$，也就是 $l \le \text{pos}_1, \text{pos}_0 \le r$。

那因为在 $a$ 中 $2 \in (\text{pos}_1, \text{pos}_0)$，a 中所有 $[l, r]$ 的 $\operatorname{MEX}$ 一定大于 $2$ （也就是说，在 $a$ 中，一个区间如果同时包含 $0$ 和 $1$，就一定会包含 $2$）。

同时，在 $a$ 中，不符合 $l \le \text{pos}_1, \text{pos}_0 \le r$ 的其他所有区间的 $\operatorname{MEX}$ 最大只有 $1$，（这样的区间最多包含一个 $0$，那么 $\operatorname{MEX}$ 就是 $1$ 了）。

那么在 $b$ 中，只要 $2 \in (\text{pos}_1, \text{pos}_0)$，就能符合 $\operatorname{MEX}([l, r]) > 2$。并且符合在不动其他数字的位置的情况下 $a$ 和 $b$ 相似。

符合这样的位置一共有 $(\text{pos}_0 - \text{pos}_1 + 1) - 2$ 个（$-2$ 是因为 $0$ 和 $1$ 占用了区间内的两个位置）。

---

那么如果在 $a$ 中，$2 \notin (\text{pos}_1, \text{pos}_0)$ 呢？

比如 $a = [1, 3, 7, 6, 0, 5, 2, 4]$

我们可以推断出，和前面讲的 $0$ 和 $1$ 一样，这种情况下，我们需要在 $b$ 中把 $2$ 放到相同的位置上。

考虑 $[\text{pos}_1, \text{pos}_2]$ 这个区间，其 $\operatorname{MEX}$ 一定大于 $2$。而 $[\text{pos}_1, \text{pos}_2 - 1]$ 这个区间的 $\operatorname{MEX}$ 就一定等于 $2$（包含 $0$，$1$）。

假设我们把 $2$ 放到 $\text{pos}_2 - 1$ 上，那么 $[\text{pos}_1, \text{pos}_2 - 1]$ 的 $\operatorname{MEX}$ 就大于 $2$ 了。

在 $a = [1, 3, 7, 6, 5, 0, 2, 4]$ 的情况下。


我们可以把 $3$ 放在 $(\text{pos}_1, \text{pos}_2)$ 的区间内。因为只有这样，才能满足所有的 $\operatorname{MEX}{[l, r]} > 3$，其中，$l \le\text{pos}_0, \text{pos}_1, \text{pos}_2 \le r$，并且除 $[l, r]$ 之外的所有区间，$\operatorname{MEX}$ 都小于 $3$。

也就是说，在 $a$ 中，如果一个区间包含了所有比 $3$ 小的数，就一定会包含 $3$。或者说，在 $a$ 中，不可能会有一个区间的 $\operatorname{MEX}$ 等于 $3$，而为了满足这一点，我们需要让 $3 \in (\text{pos}_1, \text{pos}_2)$。

我们设 $x$ 为 $\min{[\text{pos}_0 \ldots \text{pos}_3]}$, $y$ 为 $\max{[\text{pos}_0 \ldots \text{pos}_3]}$。符合上面 $3 \in (\text{pos}_1, \text{pos}_2)$ 条件的位置就有 $(y - x + 1) - 3$ 个（$-3$ 是因为区间中已经有 $0 \sim 2$ 了）。

---

现在我们可以从刚刚的观察中推广一下。我们刚刚发现如果在 $a$ 中，一个数在所有比他小的数的中间，那这个数就有很多位置可以放，相反，如果在所有比他小的数的外面，那就只能放在一个位置。

我们设正在考虑的数为 $k$，$x$ 为 $\min{[\text{pos}_0 \ldots \text{pos}_k]}$，$y$ 为 $\max{[\text{pos}_0 \ldots \text{pos}_k]}$，如果 $k$ 在 $[x, y]$ 这个区间外面，那么 $k$ 就只能放在 $\text{pos}_k$ 上，否则，可以选择 $[x, y]$ 中任意一个没被占用的地方放置。

我们设每个数能选的位置的数量为 $d_i$，那么最终的答案就是所有的 $d$ 乘起来，也就是 $\prod_{i = 0}^{n - 1}$
# 代码
在具体实现的时候，可以从 $0$ 开始~~一个一个~~的考虑，这样可以很方便的确定前面提到的 $x$ 和 $y$，以及 $[x,y]$ 区间内，被占用的位置的数量。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
// keywords:
const int MOD = 1e9 + 7;
int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        int a[n + 1];
        int pos[n + 1];
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            pos[a[i]] = i;
        }
        ll l = pos[0], r = pos[0];
        ll ans = 1;
        for (int i = 1; i < n; i++) {
            // l 和 r 就是之前讲的 x, y
            if (pos[i] < l)
                l = pos[i];
            else if (pos[i] > r)
                r = pos[i];
                //如果在 x, y 的外面
            else
                ans = ans * (r - l + 1 - i) % MOD;
        }
        cout << ans << endl;
    }
}
```

最后，希望这篇题解对你有帮助，如果有问题可以通过评论区或者私信联系我。

---

## 作者：断清秋 (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/CF1699C)

2C 卡半天，小丑竟是我自己。

首先这题有明显的暴力 DS 做法，可以 AC。

然后考虑正常做法。

随便观察一下，会发现原序列 $0$ 和 $1$ 的位置动不了，易证。

然后考虑继续往这个序列里放数，发现假如原序列中 $2$ 夹在 $0$ 和 $1$ 中间，那么放在中间任何位置都可以，证明直观。

如果不在 $0$ 和 $1$ 中间，那就只能放在原序列 $2$ 的位置，证明方法跟证 $0$ 和 $1$ 是一样的，只需将区间 $[0,1]$ 抽象为原来的点 $0$，此时的点 $2$ 就是原来的点 $1$，即可证明。

通过这种抽象区间的方式，可以发现假如前 $i-1$ 个点都被抽象为原来的点 $0$，那么第 $i$ 个点如果在区间内部则可以随便放，否则只能按原序列放。

然后考虑这个区间是啥。记 $pos_i$ 表示 $i$ 在原序列中的位置，而对于当前数 $i$，只要两边都有一个数比它小就可以了，那么对于点 $i$，这个区间就是 $[\min(pos_0,pos_1,...,pos_{i-1}),\max(pos_0,pos_1,...,pos_{i-1})]$，记录这个区间为 $[l_i,r_i]$，如果 $pos_i$ 在这个区间里，那它可放的位置就是这个区间减去前 $i-1$ 个已经放过的数，所以就是 $r_i-l_i+1-(i-1)$。

线性求一下 $l_i,r_i$，枚举每个 $i$ 求答案就做完了。

时间复杂度 $O(n)$。

---

## 作者：cjlak1o1 (赞：6)

好久没有打 cf 了，写篇题解。  

求过，改了好多遍。蒟蒻题解写的少，很多格式还掌握不透彻，望管理员原谅。

#### 题目大意:

给定一个初始序列，包含 $0\sim n-1$ 这 $n$ 个数字，寻找它的**相似序列**(同样包含 $0\sim n-1$ 这 $n$ 个数字)，定义两个相似序列满足**任意相同区间**的**补集**中的**最小非负整数**相同，即：  
$$\operatorname{mex}\{a_l,a_{l+1}\cdots a_r\}=\operatorname{mex}\{b_l,b_{l+1}\cdots b_r\}$$  
~~详情见 [OI_Wiki博弈论](https://oi-wiki.org/math/game-theory/impartial-game/)~~。  

求初始序列的相似序列的方案数。

遇到题目，先想算法，再想特殊性质。这里没有明显算法，所以我们考虑性质。  

**性质：**

- 当一个序列的区间 $\begin{bmatrix}l,r\end{bmatrix}$ 中含 $0\sim k$ 的所有数字时，另一个序列的区间 $\begin{bmatrix}l,r\end{bmatrix}$ 也**必须**含有 $0\sim k$ 的所有数字。

证明：

当一个序列的区间 $\begin{bmatrix}l,r\end{bmatrix}$ 中含 $0\sim k$ 的所有数字时（以 $a$ 数组暂且表示这个序列），$\operatorname{mex}\{a_l,a_{l+1}\dots a_r\}=k+1$，要使另一个序列相同区间 $\operatorname{mex}$ 值相同，必须也含有 $0$ 到 $k$ 的所有数字。  

根据这个性质，我们继续往下推。  

我们通过构造相似序列求方案数，维护相似序列一个区间的两个端点 $l$ 和 $r$，这个区间包含 $0\sim k$ 且两端为 $0\sim k$ 中的数字。  

我们找到初始序列的 $k+1$ 的位置： 

- 其位置若在区间内，那么其相似序列的 $k+1$ 也在此区间内，且填的位置的方案数为区间长度减去已经填的数字个数 $((r-l+1)-(k+1))$。
- 其位置若不在区间内，那么两个序列的 $k+1$ 位置相同，并扩大维护的区间到 $k+1$ 的位置。

第一个就是我们的性质，第二个小证一下，若两个位置不同，我们同时按照上述方式扩大两个序列的区间，必有一个区间相较较小，那么小区间与对应的另一个序列相同的区间不满足**性质**，故不可存在。 

所以我们 $O(n)$ 扫一遍，每次乘以第一种情况的方案数，即为答案。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+1e10;
const int mod=1e9+7;
 
inline int read()
{
	int res=0,f=1;char c;
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) res=(res<<1)+(res<<3)+(c^48);
	return res*f;
}
 
int T,n;
 
signed main()
{
	T=read();
	while(T--)
	{
		n=read();
		int a[100010],ans=1;
		for(int i=1;i<=n;i++)
		{
			int x=read();
			a[x]=i;//记录每个数字位置
		}
		int l=min(a[0],a[1]),r=max(a[1],a[0]);
		for(int i=2;i<n-1;i++)
		{
            //分情况讨论
			if(l<a[i]&&a[i]<r) ans=(ans*(r-l+1-i))%mod;
			else r=max(r,a[i]),l=min(l,a[i]);
			//cout<<l<<r<<ans<<endl;
		}
		printf("%d\n",ans);
	}
	return 0;
}

```
**蒟蒻拙见，请指教。**

---

## 作者：Miraik (赞：3)

发现一个数不是固定的，当且仅当其左右两边都存在比它小的数。

进一步的，记 $i$ 的位置为 $pos_i$，那么 $i$ 可能移动到的位置为 $\min⁡\{pos_1,\cdots,pos_{i−1}\}+1$ 到 $\max⁡\{pos_1,\cdots,pos_{i−1}\}-1$ 中所有不固定的位置，记为 $d_i$。

然后发现第 $1$ 个不固定的数可以放在 $d_i$ 个位置上，第 $2$ 个可以放在 $d_i$ 个位置上（容易发现这个位置是包含关系，因此易证），等等。

因此答案即为 $\prod_{i=1}^{m}d_i-(i-1)$，$m$ 为不固定的数的个数。

[code](https://codeforces.com/contest/1699/submission/162778049)

---

## 作者：linyuhuai (赞：3)

[长文~~真心~~建议前往 blog 使用](https://by505244.github.io/oi_blogs/2022/07/07/CF1699C题解)

### 题意

你现在有一个序列 $a_1,a_2\ldots a_n$，每个序列的值均为 $0$ 到 $n-1$（不重不漏）。
我们要找到一共有多少个序列 $b_1,b_2\ldots b_n$ （$b$ 序列数值范围与 $a$ 一致）与 $a$ 序列相似。

相似的定义：

令 $\text{MEX}$ 为其中没有出现过的最小非负整数（如 $\text{MEX}([1,2,3,4,5]=0,\text{MEX}([0,1,2,4,5])=3)$），则对于任意一个 $l,r(1\le l\le r\le n)$ 满足：

$$\text{MEX}([{a_l,a_{l+1}\cdots,a_r}])=\text{MEX}([b_l,b_{l+1}\cdots,b_r]) $$

则称 $a$ 与 $b$ 相似。

对答案进行 $10^9+7$ 取模。

### 思路

题目说白了就是求将 $a$ 交换一定个数使得交换后与交换前的序列相似（因为数字都一样）。

设 $path_x$ 为 $x$ 在 $a_i$ 数组中的位置。

（如 $a=\{1,3,2\}$，$path_1=1,path_2=3,path_3=2$）

令 $lp=\min_{i=0}^{x-1}path_i,rp=\max_{i=0}^{x-1}path_i$ 

若
$$
1\le l\le lp\le path_2\le rp\le r\le n
$$
因为 $l$ 到 $r$ 经过 $0$ 到 $x$ （前面的定义和假设！），所以：
$$
\text{MEX}([a_l,a_{l+1}\cdots,a_r])\ge x+1
$$
~~然后就没了~~

---

特别的，若 $l>lp$ 或 $r<rp$，则因为 $l$ 到 $r$ 这条线段一定未覆盖到 $0$ 到 $x-1$ 中其中一个数 （因为 $lp,rp$ 定义摆在那），所以 $\text{MEX}([a_l,a_{l+1}\cdots a_r])\le x$，导致 $x$ 的位置可以自由移动而不影响 $\text{MEX}$ 的取值（当然是在 $l>lp$ 或 $r<rp$ 的情况下的）。所以我们重点讨论 $1\le l\le lp\le rp\le r\le n$ 的情况。即接下来 $l$ 与 $r$ 的范围无特殊说明，默认是 $1\le l\le lq\le rq\le r\le n$。

---

设 $path_x$ 移动后的所到达的位置为 $p$。（$path_x$ 为移动前的位置）

##### 当 $lp\le path_x\le rp$ 时：

~~这种应该是要放在中间讲的，但作为关键步骤提前了。~~

结合上开头的讨论。可以推导出如果 $lp\le p\le rp$，那么移动后的序列一定与移动前的序列相似。

反之，$p<lp$ 或 $p>rp$，交换后的 $\text{MEX}([a_{lp},a_{lp+1}\cdots a_{rp}])$ 一定不等于交换前的。

因为 $lp$ 到 $rp$ 覆盖到了 $0$ 到 $x-1$，$x$ 移走了一定会使得 $\text{MEX}$ 值变为 $x$，而原来开头给出的结论移走前 $\text{MEX}([a_{lp},a_{lp+1}\cdots a_{rp}])\ge x+1$ 不符。

所以对于每个在 $lp$ 到 $rp$ 之间的数一共有 $rp-lp+1-x$ 种交换方案，因为在 $lp$ 到 $rp$ 之间已经有 $x$ 个其他数了，而这些其他数也占了一个空间，所以减去。

所以答案再乘 $rp-lp+1-x$ 就结束啦！

##### 当 $path_x<lp$ 时：

任何向左向右的移动都是不被允许的，因为那样会改变 $\text{MEX}$ 的取值。

则 $\text{MEX}([path_x,path_x+1\cdots n])$ 会在 $p<path_x$ 时改变。（即左移，$x$ 左移走了最小非负整数自然也就减少了）

 $\text{MEX}([path_x+1,path_x+2\cdots n])$ 会在 $p>path_x$ 时改变。（即右移，原来里面没有 $x$，移进来了，~~就有了 x~~，再加上里面本来就有 $0$ 到 $x-1$，最小非负整数就增加了）

如表 两行分别代表左移和右移，其中 $x=2$。~~表仅作结合上文理解，由于篇幅所限（更多是懒）不再详细解释。~~

|      状态      |      |      |      |      |      |      | $\text{MEX}([path_x,path_x+1\cdots n])$ | $\text{MEX}([path_x+1,path_x+2\cdots n])$ |
| :------------: | :--: | :--: | :--: | :--: | :--: | :--: | :-------------------------------------: | :---------------------------------------: |
|      先前      | $5$  | $2$  | $3$  | $1$  | $0$  | $4$  |                   $4$                   |                    $2$                    |
| 移动后（左移） | $2$  | $5$  | $3$  | $1$  | $0$  | $4$  |                   $2$                   |                    $2$                    |
| 移动后（右移） | $5$  | $4$  | $3$  | $1$  | $0$  | $2$  |                   $4$                   |                    $4$                    |



##### 当 $path_x>rp$ 时：

类似于 $path_x<lp$，任何向左移右移都是不被允许的。~~（跟上面推导过程很像应该不用写了吧）~~

### 代码

~~简洁明了，与前面格格不入~~

```cpp
#define DEBUG puts("sto shs orz")//突然发现这挺对称（不是 
const int mod = 1e9+7;
void solve(){
	int n;
	read(n);
	for(int i=1;i<=n;i++){
		int x;
		read(x);
		past[x]=i;
	}
	ll ans=1;
	int l=0x7fffffff,r=-1;
	for(int i=0;i<n;i++){
		if(past[i]>l&past[i]<r)ans=ans*(r-l+1-i)%mod;
		l=min(l,past[i]),r=max(r,past[i]);
	}
	printf("%lld\n",ans);
}
```

$\text{finish}$

---

## 作者：UperFicial (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1699C)。

同步发表于我的 [$\text{cnblogs}$](https://www.cnblogs.com/UperFicial/p/16716496.html)。

~~全程手玩即可。~~

观察样例，或者手玩一下会发现，显然 $0$ 和 $1$ 的位置是固定的。

考虑 $2$ 可放入的位置，如果在序列 $a$ 中 $2$ 位于 $0$ 和 $1$ 之间，那么 $2$ 是可以随便移动的，否则 $2$ 的位置会被固定。这个手玩即可。

这个显然是可以推广到 $k$ 个数的。 

考虑第 $k$ 个数，以及我们已经加入过得数 $0,\cdots,(k-1)$，设它们在原序列的位置分别为 $c_0,c_1,\cdots,c_{k-1}$，如果 $k$ 在原序列位置 $p\in[\min_{0\le i<k} \{c_i\},\max_{0\le i<k} \{c_i\}]$，那么 $k$ 是可以随便移动的，如果在外面的话，$k$ 的位置就被固定了。

这个证明显然，如果 $k$ 在外面的话，若 $k$ 移动到 $\left(\max_{0\le i<k} \{c_i\}+1\right)$ 这个位置，那么 $[\min_{0\le i<k} \{c_i\},\max_{0\le i<k} \{c_i\}+1]$ 这个区间的 $\operatorname{mex}$ 为 $(k+1)$，实际上应该是 $k$。

代码实现也很简单，我们只需要记录一下填过的数的最左端位置 $l$，以及最右端位置 $r$，如果目前填的数 $i$ 满足 $l<i<r$，那么 $i$ 在这个区间可以随意移动，但是其中有我们填过的 $(i-1)$ 是不能移动的，所以方案数为 $(r-l-i+1)$。

时间复杂度 $\Theta(n)$。

[代码](https://codeforces.com/contest/1699/submission/172923386)。


---

## 作者：Prophesy_One (赞：0)

似乎没有题解写过这种做法。

首先对于排列，我们有一个性质：$\text{mex}_{i=1}^x p_i=\min_{i=x+1}^n p_i$。

考虑这个性质有什么用，发现它可以锁定所有前缀最小值 $pre_i$，后缀最小值 $suc_i$，即问题转化为：给定所有 $pre_i,suc_i$，求有多少个合法的排列。

显然我们一定可以锁定一些位置的值：如果 $pre_i \neq pre_{i-1}$，那么一定有 $p_i=pre_i$；如果 $suc_i \neq suc_{i+1}$，那么一定有 $p_i=suc_i$。

对于剩下的不能确定值的位置，它应该满足 $p_i>\max(pre_i,suc_i)$，考虑把所有这样的 $\max(pre_i,suc_i)$ 拎出来从大到小排序，乘法原理计算方案数即可。

时间复杂度 $\text{O}(n \log n)$，瓶颈在排序。

[link](https://codeforces.com/contest/1699/submission/293220591)

---

## 作者：bmatrix (赞：0)

前排提醒：这是本题最烂的做法，代码长达 91 行。

由于题里提到了 $\operatorname{MEX}$，所以考虑该怎么求 $\operatorname{MEX}$。

我们使用[主席树](https://oi-wiki.org/ds/persistent-seg/)。由于主席树难以直接处理下标为 $0$ 的情况，所以给数组中的每个值都加上一个偏移量 $1$，同时下文提到的 $\operatorname{MEX}$ 也都是题目里定义的 $\operatorname{MEX}+1$。

主席树记下区间内元素出现的次数后，在树上对值域二分。如果左儿子中各元素出现的次数小于左儿子代表的值域区间的长度，则说明左边至少有一个元素没有出现，因此 $\operatorname{MEX}$ 一定在左儿子的区间，向左递归查找，否则向右递归查找。

值得注意的是，一个长为 $len$ 的区间 $\operatorname{MEX}$ 可能为 $len+1$ ，需要进行特判。

这是主席树部分的代码：
```cpp
struct node {
    int l, r, cnt, ls, rs;
    int mid() { return (l + r) / 2; }
    int len() { return r - l + 1;}
}nd[N * 24];//N是数据范围
int rt[N], tot;
int build(int l, int r) {
    int p = ++tot;
    nd[p].l = l, nd[p].r = r;
    if(l == r) return p;
    int mid = (l + r) / 2;
    nd[p].ls = build(l, mid);
    nd[p].rs = build(mid + 1, r);
    return p;
}
void insert(int& p, int ori, int loc) {
    p = ++tot;
    nd[p] = nd[ori];
    nd[p].cnt++;
    if(nd[p].l == nd[p].r) return;
    if(loc <= nd[p].mid()) insert(nd[p].ls, nd[ori].ls, loc);
    else insert(nd[p].rs, nd[ori].rs, loc);
}
int mex(int lp, int rp) {
    if(nd[lp].l == nd[lp].r) {
        if(nd[rp].cnt - nd[lp].cnt) return nd[lp].l + 1;
        else return nd[lp].l;
    }
    if(nd[nd[rp].ls].cnt - nd[nd[lp].ls].cnt < nd[nd[lp].ls].len()) 
        return mex(nd[lp].ls, nd[rp].ls);
    else 
        return mex(nd[lp].rs, nd[rp].rs);
}
```
这样，通过调用 `mex(rt[l-1],rt[r])` 就可以求出 $\operatorname{MEX}([a_l,a_{l+1}\ldots a_{r-1},a_r])$ 辣！

接下来进入核心做法部分：

首先 $1$ 所在位置一定不变，否则 $b$ 中长为 $1$ 的区间的 $\operatorname{MEX}$ 会和原排列不完全相同。

对于 $a$ 中任意一个区间 $[l,r]$，小于其 $\operatorname{MEX}$ 值的所有数字都只能在该区间内随意排列。否则得到的新区间的 $\operatorname{MEX}$ 会比原区间小，不符合题意。

我们锁定一个区间，设当前区间为 $[l,r]$，并且只能在当前区间内排列的数字所贡献的方案数都已经计算完。

设当前区间的 $\operatorname{MEX}$ 值为 $m$，寻找 $m$ 在 $a$ 中的位置 $p$，若 $p<l$ 则将区间 $[l,r]$ 扩张到 $[p,r]$，否则扩张到 $[l,p]$。设新区间是 $[l',r']$。

对于扩张的新区间，设它的 $\operatorname{MEX}$ 值为 $m'$，那么小于 $m'$ 的所有数字都只能在这个区间内排列。区间长为 $r'-l'+1$，其中原区间 $[l,r]$ 已经确定了 $m-1$ 个数字的位置，又因为数字 $m$ 的位置不能改变，则对答案有贡献的数字共有 $m'-m-1$ 个，这些数字可以随意排列的空位共有 $r'-l'+1-m$ 个，因此这些数字对答案的贡献为 $P_{r'-l'+1-m}^{m'-m-1}$，乘到答案上即可。

区间扩张为整个排列后就不能再继续了，因此这是迭代出口。

正确性可以这样理解：如果选择其他区间，很难得出关于数字位置的信息，也就难以计算。因此选择上述扩张区间的方式，可以找到所有能够确定一些数字的位置的区间，进而进行计算。

时间复杂度 $O(n\log n)$。

核心代码：
```cpp
//P(m,n)的作用是求出m!/(m-n)!，即排列数
//loc[i]代表元素i在原数组中的位置
//mod就是题里给的模数1e9+7
//oldmex即上文的m，newmex即上文的m'
ll ans = 1;
int l = loc[1], r = loc[1], oldmex = 2;
while(r - l + 1 < n) {
    if(loc[oldmex] < l) l = loc[oldmex];
    else r = loc[oldmex];
    int newmex = mex(rt[l - 1], rt[r]);
    ans = ans * P(r - l + 1 - oldmex, newmex - oldmex - 1) % mod;
    oldmex = newmex;
}
cout << ans << endl;
```

谢谢大家能耐心看完我的烂做法，以下是完整代码：（$91$ 行）
```cpp
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
constexpr int N = 1e5 + 5;
constexpr ll mod = 1e9 + 7;
int n, loc[N], rt[N], tot;
ll fact[N];
ll qp(ll a, ll b) { // 快速幂
    ll ans = 1;
    for(; b; b >>= 1, a = a * a % mod)
        if(b & 1) ans = ans * a % mod;
    return ans;
}
ll P(ll m, ll n) { // 排列数，fact[i]即i!
    return fact[m] * qp(fact[m - n], mod - 2) % mod;
}
struct node {
    int l, r, cnt, ls, rs;
    int mid() { return (l + r) / 2; }
    int len() { return r - l + 1;}
}nd[N * 24];
int build(int l, int r) {
    int p = ++tot;
    nd[p].l = l, nd[p].r = r;
    if(l == r) return p;
    int mid = (l + r) / 2;
    nd[p].ls = build(l, mid);
    nd[p].rs = build(mid + 1, r);
    return p;
}
void insert(int& p, int ori, int loc) {
    p = ++tot;
    nd[p] = nd[ori];
    nd[p].cnt++;
    if(nd[p].l == nd[p].r) return;
    if(loc <= nd[p].mid()) insert(nd[p].ls, nd[ori].ls, loc);
    else insert(nd[p].rs, nd[ori].rs, loc);
}
int mex(int lp, int rp) {
    if(nd[lp].l == nd[lp].r) {
        if(nd[rp].cnt - nd[lp].cnt) return nd[lp].l + 1;
        else return nd[lp].l;
    }
    if(nd[nd[rp].ls].cnt - nd[nd[lp].ls].cnt < nd[nd[lp].ls].len()) 
        return mex(nd[lp].ls, nd[rp].ls);
    else 
        return mex(nd[lp].rs, nd[rp].rs);
}
void solve() {
    cin >> n;
    rt[0] = build(1, n);
    for(int i = 1; i <= n; ++i) {
        int x; cin >> x;
        loc[x + 1] = i;
        insert(rt[i], rt[i - 1], x + 1);
    }
    if(n == 1) {
        cout << 1 << endl;
        return;
    }
    ll ans = 1;
    int l = loc[1], r = loc[1], oldmex = 2;
    while(r - l + 1 < n) {
        if(loc[oldmex] < l) l = loc[oldmex];
        else r = loc[oldmex];
        int newmex = mex(rt[l - 1], rt[r]);
        ans = ans * P(r - l + 1 - oldmex, newmex - oldmex - 1) % mod;
        oldmex = newmex;
    }
    cout << ans << endl;
}
void clear() { // 多测不清空，爆零两行泪
    memset(loc + 1, 0, n * sizeof(int));
    memset(rt, 0, (n + 1) * sizeof(int));
    memset(nd + 1, 0, tot * sizeof(node));
    tot = 0;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    fact[0] = 1;
    for(int i = 1; i < N; ++i)
        fact[i] = fact[i - 1] * i % mod;
    int t; cin >> t;
    while(t--) {
        solve();
        clear();
    }
    return 0;
}
```

---

