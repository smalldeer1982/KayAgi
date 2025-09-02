# Genius Acm

## 题目描述

Advanced CPU Manufacturer (ACM) is one of the best CPU manufacturers in the world. 每天，该公司生产 $n$ 台 CPU 并销售到世界各地。

ACM 公司的质检部门会对生产出的 CPU 进行成组测试，对一组（若干个）CPU 进行测试的方法如下：

1. 随机从该组 CPU 中选取 $m$ 对（即 $2m$ 台），若总数不足 $2m$ 台，则选取尽量多对。

2. 对于每一对 CPU，测量它们之间的 Relative Performance Difference (RPD)，并把第 $i$ 对的 RPD 记为 $D_i$。RPD 的计算方法在后面给出。

3. 该组 CPU 的 Sqared Performance Difference (SPD） 由以下公式给出：

$SPD=\sum _i D^2_i$


4. 该组 CPU 通过质检，当且仅当 $SPD \le k,$ 其中 $k$ 是给定常数。

ACM 公司生产的 CPU 性能很好，而质检部门制定的标准更是过于严格。通常他们把 $n$ 台 CPU 作为一整组进行测试，这导致一些性能良好的 CPU 无法通过测试，生产部门对此颇有微词。作为质检部门的领导，小 S 在不更改质检测试流程的前提下，想出了这样一个主意：如果能够把 $n$ 台 CPU 恰当地分成连续的若干段，使得每段 CPU 都能够通过成组测试，就可以解决当下的问题。

现在，小 S 已经知道了 $n$ 台各自的性能表现 $P_1,\cdots ,P_n$，两台 CPU 的 RPD 被定义为它们性能表现的差的绝对值。请你帮忙计算一下，至少把这些 CPU 分成多少段，才能使得每一段都能通过成组测试。

## 说明/提示

对于 $20 \%$ 的数据，$1 \leq n \leq 10^2$ 。  
对于 $40 \%$ 的数据， $1 \leq n \leq 10^3$ 。  
对于另外 $10 \%$ 的数据，$k=0$ 。  
对于另外 $10 \%$ 的数据，$0 \leq k \leq 1$ 。  
对于另外 $10 \%$ 的数据， $m=1$ 。  
对于另外 $10 \%$ 的数据，$1 \leq m \leq 2$ 。  
对于 $90 \%$ 的数据，$0 \leq k \leq 10^{12}$ 。  
对于 $100 \%$ 的数据，$T \leq 12,1 \leq n, m \leq 5 \cdot 10^5, 0 \leq k \leq 10^{18}, 0 \leq P_i \leq 2^{20}$ 。  

## 样例 #1

### 输入

```
2
5 1 49
8 2 1 7 9
5 1 64
8 2 1 7 9```

### 输出

```
2
1```

# 题解

## 作者：DDD_et (赞：11)

# P10455 Solution

**做法：贪心，倍增，归并思想**

## 题意

给定 $n$ 台 CPU 的性能 $P_1\dots P_n$，问至少要分成几组，才能使在每组里抽取 $\min \{m,\frac{n}{2}\}$ 台 CPU 时使得其 SPD 最大不超过 $k$。

设一组 CPU 的性能为 $d_1 \dots d_n$，则这组 CPU 的 SPD 定义为 $(d_1-d_2)^2+(d_3-d_4)^2+\dots+(d_{n-1}-d_n)^2$。

## 思路

### Part 1. 贪心

第一眼我们知道测试用的 CPU 既然是随机抽，那么我们要使得最大的 SPD 都不超过 $k$，SPD 的最大值当然不能枚举，所以考虑贪心策略。

设有四数 $a,b,c,d$，且它们满足 $a<b<c<d$。

则有两种取数方式：

- $a$ 与 $d$ 一组，剩下的另一组。
- $a$ 与 $c$ 一组，剩下的另一组。

则第一种方式的 SPD 为 $(d-a)^2+(c-b)^2$，第二种方式的 SPD 为 $(c-a)^2+(d-b)^2$。

两式相减，得：

$$
\begin{aligned}
(d-a)^2+(c-b)^2-(c-a)^2-(d-b)^2 &= (d-a)(d-a)+(c-b)(c-b)-(c-a)(c-a)-(d-b)(d-b) \\
&=(d^2-2ad-a^2)+(c^2-2bc-b^2)-(c^2-2ac-a^2)-(d^2-2bd-b^2) \\
&=2ac+2bd-2ad-2bc \\
&=2(d-c)(b-a)
\end{aligned}
$$

由于 $d>c,b>a$，所以 $d-c$ 和 $b-a$ 均大于 $0$。

即我们要使题目中最大的 $D_i$ 与最小的 $D_i$ 配对，使第二大的 $D_i$ 与第二小的 $D_i$ 配对，以此类推。

### Part 2. 倍增

根据题目数据，肯定是不能二分的，因为最坏情况下需要进行 $n$ 次二分，会使时间复杂度变为 $\mathcal{O}(n^2 \log^2 n)$。

那么可以用倍增平替掉（[什么是倍增？](https://oi-wiki.org/basic/binary-lifting/)）。朴素思想就是倍增模版，用变量 $\text{stt}$ 记录当前的位置，$\text{add}$ 记录平移的元素数，当排序后求出来的 SPD 小于等于 $k$ 时 并将 $\text{add}$ 乘上 $2$，否则 $\text{add}$ 除以 $2$，注意一般采用左闭右开区间。

时间复杂度 $\mathcal{O}(n \log^2n)$。

### Part 3. 归并思想优化

~~归并立大功。~~

发现在求 SPD 的函数中，每次都要将当前数组排一遍序，时间开销较大，所以考虑使用归并排序的思想。

增加一个变量 $\text{end}$ 记录上次结束时的位置作为中心点，我们既然在上次倍增时已经对 $[\text{stt},\text{end})$ 这个区间排了序，那么这次只要排序 $[\text{end},\text{end}+\text{add})$，并用归并排序的思想将这两个数组合并再求 SPD 即可。

记得在符合条件后更新用来排序的数组并且不管怎样都要更新 $\text{stt}$ 为 $\text{end}$。

时间复杂度 $\mathcal{O}(n \log n)$，可以通过。

## 代码

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 10;
int n, m, k, t, p[N], m1[N], m2[N];

int RPD (int a, int b) { return a - b; }

bool check (int s, int mid, int e)
{
	for (int i = mid; i < e; i ++) m1[i] = p[i];
	sort (m1 + mid, m1 + e); //只排序[mid,e)
	
	int lp = s, rp = mid, idx = 0, res = 0;
	while (lp < mid && rp < e) //归并
	{
		if (m1[lp] <= m1[rp]) m2[idx ++] = m1[lp ++];
		else m2[idx ++] = m1[rp ++];
	}
	while (lp < mid) m2[idx ++] = m1[lp ++];
	while (rp < e) m2[idx ++] = m1[rp ++];
	
	for (int i = 0; i < m && i < idx; i ++, idx --)
		res += pow (RPD (m2[i], m2[idx - 1]), 2); //贪心求 SPD
	return res <= k;
}

signed main ()
{
    scanf ("%lld", &t);
	while (t --)
	{
		scanf ("%lld%lld%lld", &n, &m, &k);
		for (int i = 0; i < n; i ++) scanf ("%lld", p + i);
		int stt = 0, end = 0, cnt = 0;
		while (end < n)
		{
			int add = 1;
			while (add > 0)
			{
				if (end + add <= n && check (stt, end, end + add))
				{
					end += add, add <<= 1;
					if (end >= n) break;
					for (int i = stt; i < end + add; i ++)
						m1[i] = m2[i - stt]; //更新用来排序的数组
				}
				else add >>= 1;
			}
			cnt ++, stt = end; //更新起始位置
		}
		printf ("%lld\n", cnt);
	}
	return 0;
}
```

### 写在最后

~~还是那句话，归并立大功。~~

**谢谢观看！**

---

## 作者：Shadow_Soldier (赞：8)

# 题意概述
给定正整数 $n$，$m$，$k$，与非负整数 $P_1,P_2,\cdots,P_n$，问最少要将序列 $P_1,P_2,\cdots,P_n$ 划分成多少个连续的子段，使每一段的 SPD 值小于等于 $k$。  
每段的 SPD 值的计算方式为：选 $\min(\lfloor \frac{n}{2} \rfloor, m)$ 对数，每对的两个数的差的平方的和的最大值。  
想看题目就点这里：[P10455 Genius Acm](https://www.luogu.com.cn/problem/P10455)。
# SPD 值的求法
比如，给定正整数 $n$，$m$ 与整数 $a_1,a_2,\cdots,a_n$，求 $a$ 序列的 SPD 值。  
最暴力的方法当然是枚举每种选择数对的方式并求出每种选择方式的结果，最后求一个最大值。当然，这样的时间复杂度太高，难以接受。所以我们想到，如何选择数对它的结果就会最大呢？  
当然，结果用贪心很容易想到，就是第 $1$ 小的数匹配第 $1$ 大的数、第 $2$ 小的数匹配第 $2$ 大的数、$\cdots$、第 $\min(\lfloor \frac{n}{2} \rfloor, m)$ 小的数匹配第 $\min(\lfloor \frac{n}{2} \rfloor, m)$ 大的数。那么为什么呢？能否证明这一点呢？下面给出一个证明：

证明：  
不妨 $a_1 \le a_2 \le \cdots \le a_n$，令 $K = \min(\lfloor \frac{n}{2} \rfloor, m)$，并假设所选的 $K$ 对数分别为 $(x_1, y_1),(x_2,y_2),\cdots,(x_K,y_K)$。即要最大化 $S = \sum_{i = 1}^K (x_i - y_i)^2$。  
固定所选的 $2K$ 个元素，且不妨 $x_i < y_i$，则若存在正整数 $s, t(1 \le s, t \le K)$，使 $x_s \le x_t$ 且 $y_s < y_t$。  
令正整数 $y'_1,y'_2,\cdots,y'_K$ 为交换 $y_s$ 与 $y_t$ 后的 $y_1,y_2,\cdots,y_K$，即（$i$ 为正整数，且 $i \le K$）：  
$$
y'_i = 
\begin{cases}
  y_t & i = s \\
  y_s & i = t \\
  y_i & i \ne s \text{ 且 } i \ne t
\end{cases}
$$
则原来配对方案 $(x_1,y_1),(x_2,y_2),\cdots,(x_K,y_K)$ 每对数的差的平方的和 $S$ 减去交换 $y_s$ 与 $y_t$ 后的配对方案 $(x_1,y'_1),(x_2,y'_2),\cdots,(x_K,y'_K)$ 的差的平方的和 $S'$ 的结果如下：
$$
\begin{aligned}
S - S' &= \sum_{i=1}^K (x_i - y_i)^2 - \sum_{i=1}^K (x_i - y'_i)^2 \\
  &= \sum_{i=1}^K ({x_i}^2 + {y_i}^2 - 2x_iy_i) - \sum_{i=1}^K ({x_i}^2 + {y'_i}^2 - 2x_iy'_i) \\
  &= (\sum_{i=1}^K {x_i}^2 + \sum_{i=1}^K {y_i}^2 - 2\sum_{i=1}^K x_iy_i) - (\sum_{i=1}^K {x_i}^2 + \sum_{i=1}^K {y'_i}^2 - 2\sum_{i=1}^K x_iy'_i) \\
  &= 2(\sum_{i=1}^K x_iy'_i - \sum_{i=1}^K x_iy_i) \\
  &= 2((x_sy_t+x_ty_s) - (x_sy_s + x_ty_t)) \\
  &= 2(x_s - x_t)(y_t - y_s) \\
  &\le 0
\end{aligned}
$$
$\therefore S' \ge S$  
即，若存在正整数 $s, t(1 \le s, t \le K)$，使 $x_s \le x_t$ 且 $y_s < y_t$，则交换 $y_s$ 与 $y_t$ 后每对数的差的平方的和不会更小。  
所以，给 $x_1,x_2,\cdots,x_K$ 定序，令 $x_1 \le x_2 \le \cdots \le x_K$，则最优解一定满足 $y_1 \ge y_2 \ge \cdots \ge y_K$。即：满足 $x_1 \le x_2 \le \cdots \le x_K \le y_K \le y_{K-1} \le \cdots \le y_1$ 的一定是一组最优解。也就是在固定的 $2K$ 的数中，最优配对方式为第 $1$ 小的数匹配第 $1$ 大的数、第 $2$ 小的数匹配第 $2$ 大的数、$\cdots$、第 $K$ 小的数匹配第 $K$ 大的数。  
接下来考虑在全部的 $n$ 个数中如何选 $2K$ 个数（若 $K=0$，则不需要选任何数）。  
当 $K=1$ 时，显然选择 $a_1$ 与 $a_n$，因为 $a_1 = \min\{a_1,a_2,\cdots,a_n\}$，$a_n = \max\{a_1,a_2,\cdots,a_n\}$，显然 $(a_n - a_1)^2$ 最大。  
当 $K=i$（$i$ 为正整数，$i > 1$） 时，显然在前 $i - 1$ 个最优的情况下选择剩下的最大值与最小值，即在前 $i - 1$ 个的基础上在选取 $a_i$ 与 $a_{n - i + 1}$。  
所以，应选取 $a_1,a_2,\cdots,a_K,a_{n - K + 1},a_{n - K + 2},\cdots,a_n$，作为 $2K$ 个元素。也就是第 $1$ 小的数匹配第 $1$ 大的数、第 $2$ 小的数匹配第 $2$ 大的数、$\cdots$、第 $K$ 小的数匹配第 $K$ 大的数。

得到了上面的结论，$a_1,a_2,\cdots,a_n$ 的 SPD 值就好求了。  
首先，对 $a_1,a_2,\cdots,a_n$ 进行排序，然后依次匹配并求出每对数的差的平方的和。  
排序的时间复杂度为 $\Omicron(n \log_2 n)$，匹配的时间复杂度为 $\Omicron(n)$，所以总的时间复杂度就是 $\Omicron(n \log_2 n)$。
# 原题思路
## 一、暴力
既然题目要求分段，那就暴力进行分段，将计数器赋值为 $0$，外循环枚举左端点，内循环从左端点开始枚举右端点，每次再按照上面方法计算 SPD 值（不能用原数组排序），如果大于 $k$，就把左端点到右端点减一的部分作为一段并将左端点赋值为此时的右端点，计数器加一。循环完后，再将计数器加一（最后一段），答案就是最后计数器中的值。  
那么，时间复杂度呢？首先，外面的两层循环的时间复杂度是 $\Omicron(n)$ 的；里面的操作（求 SPD 值）是 $\Omicron(n \log_2 n)$ 级的。所以，最终的时间复杂度为 $\Omicron(n^2 \log_2 n)$，过不了。  
但是我们发现，每次会重复对一段进行排序，所以如果每次该用插入排序，在有序的序列中插入一个数的话，时间复杂度可以优化成 $\Omicron(n^2)$，仍然过不了。
## 二、二分
注意到固定左端点后，右端点（区间长度）具有单调性。所以，每次可以尝试使用二分右端点（区间长度），而不是直接枚举，可是最坏情况下，可能执行 $n$ 次二分，每次二分最多执行 $\log_2 n$ 次判断函数，每个判断函数的时间复杂度是 $\Omicron(n \log_2 n)$ 级的。  
注意到：
$$
\begin{aligned}
\sum_{i=0}^{\log_2 n} (\frac{n}{2^i} \log_2 \frac{n}{2^i}) &\le \sum_{i=0}^{\log_2 n} (\frac{n}{2^i} \log_2 n) \\
  &\le (\log_2 n) \cdot \sum_{i=0}^{\log_2 n} \frac{n}{2^i} \\
  &\le (\log_2 n) \cdot 2n \\
  &= 2 \cdot (n \log_2 n)\tag{1}
\end{aligned}
$$
所以每次二分的时间复杂度是 $\Omicron(n \log_2 n)$ 级的，然后可以推断出总的时间复杂度是 $\Omicron(n^2 \log_2 n)$，和朴素版暴力一样，还没有优化版暴力好。那该如何优化呢？  
在这里说句题外话：虽然优化之后反倒没有原来的时间复杂度好了，但是也是一种思路，有的时候就是这种看似没用思路优化后成为了时间复杂度更优的算法。
## 三、倍增
我们发现，二分之所以慢，是因为它的枚举方向，所以可以用倍增替代掉二分。我们发现，可以将二分右端点的部分改成：先从小往大尝试将后面二的幂个元素加入备选序列，直到原序列中元素不足这么多个或者加入备选序列后的 SPD 值大于 $k$。然后再从最后的加入备选序列的数量开始从大往小尝试将后面二的幂个元素加入备选序列，每次尝试时，如果加入后的备选序列的 SPD 值不大于 $k$，则加入备选序列；否则，即加入后的备选序列的 SPD 值大于 $k$，则不加入备选序列。其它的就跟二分的过程差不多了。  
时间复杂度：外层一样的 $\Omicron(n)$，内层每次倍增最多排序 $2 \log_2 n$ 次（常数忽略不计）。由 $(1)$，时间复杂度为 $\Omicron(n^2 \log_2 n)$，与二分一样。
## 四、倍增 + 归并
在上面倍增的思路中，我们发现每次倍增中进行的排序的序列左端点都是重合的，只是右边延伸了一段。所以可以想到，将原来直接排序的部分修改成：先将加入备选序列的部分排好序（当然不能存在原数组中），然后用归并（双指针）的方式将两个有序序列合并成一个大的有序序列。  
时间复杂度：外层还是 $\Omicron(n)$，内层每次倍增最多归并 $2 \log_2 n$ 次（常数忽略不计）。那每次倍增的复杂度是 $\Omicron(n \log_2 n)$，总的时间复杂度是否还是 $\Omicron(n^2 \log_2 n)$ 呢？不是。我们发现，每一段只会被排一次序。所以，总的排序操作的时间复杂度的和应该不超过 $\Omicron(n \log_2 n)$。而归并的时间复杂度的和也不超过 $\Omicron(n \log_2 n)$。所以总的时间复杂度就是 $\Omicron(n \log_2 n)$。通过！  
不过，归并完后的时候可以将结果复制回原数组（如果结果的 SPD 值不大于 $k$ 的话）。
# 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
template <typename T>
inline void read(T& r) {
	r=0;bool w=0; char ch=getchar();
	while(ch<'0'||ch>'9') w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9') r=r*10+(ch^48), ch=getchar();
	r=w?-r:r;
}
int T, n, m, k, ii, ans, p[500010], a[500010], b[500010];
bool check(int l, int r, int rr) {
    if(rr > n) return false;
	int p1 = l, p2 = r + 1, p3 = l, s = 0;
    for(int i = l; i <= rr; i ++) {
        a[i] = p[i];
    }
	sort(a + r + 1, a + rr + 1);
	while(p1 <= r && p2 <= rr) {
		if(a[p1] < a[p2]) b[p3++] = a[p1++];
		else b[p3++] = a[p2++];
	}
	while(p1 <= r) b[p3++] = a[p1++];
	while(p2 <= rr) b[p3++] = a[p2++];
	for(int i = l, j = rr, o = 1; i < j && o <= m; i ++, j --, o ++) {
		s += ((b[j] - b[i]) * (b[j] - b[i]));
        if(s > k) return false;
	}
    for(int i = l; i <= rr; i ++) {
        p[i] = b[i];
    }
	return true;
}
signed main()
{
	read(T);
	while(T --) {
		read(n);read(m);read(k);
		for(int i = 1; i <= n; i ++) {
			read(p[i]);
		}
		ans = 0;
		for(int l = 1, r = 0; l <= n; ++ans) {
			for(ii = 1; check(l, r, r + ii); ii <<= 1) {
				r += ii;
			}
			ii >>= 1;
			for(; ii; ii >>= 1) {
                if(check(l, r, r + ii)) {
    				r += ii;
                }
			}
			l = r + 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}
``````
# 提交记录
[我的提交记录](https://www.luogu.com.cn/record/204928105)
# 最后说的话
本题的代码虽然略微有一点儿长，但是还是要自己手打，千万不可以抄代码。  
最后祝愿大家 AC！

---

## 作者：forever_nope (赞：8)

曾经写的倍增笔记里面有这道题，详细看：<https://www.cnblogs.com/RainPPR/p/18208160>。

UPD 20240805：更新了上面的链接。

下面是题解，从上面我的笔记里面抄过来的（

## 天才 ACM

考虑到，一个集合的校验值，一定是最大对最小，次大对次小。

随便举个例子，若 $a<b<c<d$，则

$$
(d-a)^2+(c-b)^2=a^2+b^2+c^2+d^2-2(ad+bc)\\
(b-a)^2+(d-c)^2=a^2+b^2+c^2+d^2-2(ab+cd)
$$

上式减下式，

$$
ab+cd-ad-bc=a(b-d)+c(d-b)=(c-a)(d-b)
$$

乘积为正数，即上式大于下式，即贪心可行且正确。

回归问题，容易总结出来：

对于左端点，找到最右的点，使得校验值小于限制的值。

考虑到计算校验值是 $\mathcal O(n\log n)$ 的，因此这里需要优化。

注意到和上面的题形式类似，可以倍增处理，

因为倍增的复杂度是 $\mathcal O(\log n)$ 的，因此整体复杂度为，

$$
\mathcal O(n\log^2n)
$$

不太可过，但是注意到每次右端点增加的时候，可以类似归并排序的合并。

于是复杂度降为，

$$
\mathcal O(n\log n)
$$

但是细节很多，本人采用了闭区间的写法，

```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

using ll = long long;
constexpr int N = 1e6 + 10;

int n, m;
ll t;
int a[N], b[N];
int q[N];

bool getchk(int l, int r, int ad) {
	int lt = r - ad + 1;
    for (int i = lt; i <= r; ++i) b[i] = a[i];
    sort(b + lt, b + r + 1);
    int tot = 0, u = l, v = lt;
	while (u < lt && v <= r) {
		if (b[u] < b[v]) q[tot++] = b[u++];
		else q[tot++] = b[v++];
	}
	while (u < lt) q[tot++] = b[u++];
	while (v <= r) q[tot++] = b[v++];
	ll chk = 0;
	for (int i = 0, j = tot - 1, k = 1; k <= m && i < j; ++i, --j, ++k)
	chk += 1ll * (q[j] - q[i]) * (q[j] - q[i]);
	return chk <= t;
}

int getpos(int l) {
	int p = 1, k = l - 1;
	while (p) {
		if (k + p <= n && getchk(l, k + p, p)) {
			k = k + p, p <<= 1;
			for (int i = l; i <= k + p; ++i) b[i] = q[i - l];
		} else p >>= 1;
	} return k;
}

void solev() {
	cin >> n >> m >> t;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	int l = 1, ans = 0;
	while (l <= n) l = getpos(l) + 1, ++ans;
	cout << ans << endl;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int T; cin >> T;
	while (T--) solev();
	return 0;
}
```

---

## 作者：Jerrycyx (赞：6)

## 更易于理解的题面

> 给定一个整数 $M$ ，对于任意一个整数集合 $S$，定义“校验值”如下:
> 
> 从集合 $S$ 中取出 $M$ 对数（即 $2M$ 个数，不能重复使用集合中的数，如果 $S$ 中的整数不够 $M$ 对，则取到不能取为止)，使得“每对数的差的平方之和”最大，这个最大值就称为集合 $S$ 的“校验值”。
> 
> 现在给定一个长度为 $N$ 的数列 $A$ 以及一个整数 $K$。
> 
> 我们要把 $A$ 分成若干段，使得每一段的“校验值”都不超过 $K$。
> 
> 求最少需要分成几段。

## “校验值”

考虑贪心，**将第 $k$ 大的值与第 $k$ 小的值组合** _（这个 $k$ 不是题面中的那个 $k$，下同）_  即可使“每对数的差的平方之和”最大。

可以将数组排序后双指针求出，求一次“校验值”的时间复杂度为 $O(N \log N)$。

对于一组已经排好序的数列 $a_1,a_2,a_3,...,a_n$ 当一个新的数 $x$ 加入这个数列的时候，最大值只能被更大的 $x$ 更新，所以最大值不会减小，而只会增大或不变。

同理，$a_k$（第 $k$ 大的数）只能被大于 $a_k$ 的数更新，$a_{n-k+1}$（第 $k$ 小的数）只能被小于 $a_{n-k+1}$ 的数更新。所以 $a_k$ 不会减小，$a_{n-k+1}$ 不会增大。故 $a_k-a_{n-k+1}$ 不会减小，即 $(a_k-a_{n-k+1})^2$ 不会减小。

因此，**当一个新的数加入数列的时候，“校验值”不会减小，即“校验值”具有非严格单调性。**

## $80\ \rm{Pts}$ 暴力

在“校验值”不超过 $K$ 的情况下，不断扩大数列长度，当无法再扩大的时候，开启下一个数列。

具体地说，设当前区间为 $[l,r]$，将 $r$ 不断右移，如果此时“校验值”大于 $K$，则令 `l=r,ans++`，即开启新区间。

在每一次 $r$ 增加的时候，将 $a[l,r]$ 提出并排序，双指针扫描前后端并累加差的平方，即可得到校验值。

计算校验值的时间复杂度为 $O(N \log N)$，一共需计算 $N$ 次，所以暴力的时间复杂度为 $O(N^2 \log N)$。

时间复杂度上可以通过 $40\%$ 的数据，另有 $40\%$ 的数据有特殊性质可以大量减少判断次数和判断时间，所以一共可得 $80\ \rm{Pts}$ ~~暴力碾标算~~。

参考代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

inline int read()
{
	int x=0;bool w=true;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=false;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^'0');ch=getchar();}
	return w?x:-x;
}

const int N=5e5+5,M=5e5+5;
int T,n,m,k,p[N],tmp[N];

inline bool check(const int L,const int R)
{
	for(int i=L;i<=R;i++)
		tmp[i]=p[i];
	sort(tmp+L,tmp+R+1);
	int sum=0,l=L,r=R,cnt=0;
	while(l<r && sum<=k && cnt<m)
	{
		sum+=(tmp[r]-tmp[l])*(tmp[r]-tmp[l]);
		l++,r--, cnt++;
	}
	return sum<=k;
}

int main()
{
	T=read();
	while(T--)
	{
		memset(p,0,sizeof(p));
		n=read(),m=read(),k=read();
		for(int i=1;i<=n;i++)
			p[i]=read();
		int l=1,ans=0;
		for(int r=1;r<=n;r++)
			if(!check(l,r)) l=r,ans++;
		printf("%d\n",ans+1);
	}
	return 0;
}
```

## $90\ \rm{Pts}$ 倍增

因为“校验值”具有单调性，所以我们可以倍增 $r$，每次检验区间 $[l,r+2^{bin}-1]$ 是否合法，若合法则令 $r=r+2^{bin}-1$ 并将 $bin+1$，否则 $bin-1$（避免多余检测过大区间而增加程序运行时间）。

时间复杂度 $O(N \log^2 N)$ ~~（试图卡常卡成满分的人就是我）~~

参考代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

inline int read()
{
	int x=0;bool w=true;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=false;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^'0');ch=getchar();}
	return w?x:-x;
}

const int N=5e5+5;
int T,n,m;
long long k;
int p[N],tmp[N],lg2[N];

inline bool check(const int L,const int R)
{
	if(R>n) return false;
	for(int i=L;i<=R;i++)
		tmp[i]=p[i];
	long long sum=0;
	sort(tmp+L,tmp+R+1);
	int l=L,r=R,cnt=0;
	while(l<r && sum<=k && ++cnt<=m)
	{
		sum+=(long long)(tmp[r]-tmp[l])*(tmp[r]-tmp[l]);
		l++,r--;
	}
	return sum<=k;
}

int main()
{
	for(int i=2;i<=5e5;i++)
		lg2[i]=lg2[i>>1]+1;
	T=read();
	while(T--)
	{
		n=read(),m=read(); scanf("%lld",&k);
		for(int i=1;i<=n;i++)
			p[i]=read();
		int ans=0;
		int l=1,r=l,bin=1;
		while(r<=n)
		{
			if(!bin)
			{
				ans++;
				l=r+1,r=l;
			}
			if(check(l,r+(1<<bin)-1))
			{
				r=r+(1<<bin)-1;
				bin++;
			}
			else bin--;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

## $100\ \rm{Pts}$ 倍增+归并排序

在 `check` 的时候，尤其是 `bin++` 的阶段，**其所排序的数列前半段已经是有序的，无需重新将整个数列排序一遍**。当数列一半有序的时候，可以考虑采用**类似归并排序的合并方式**。

利用 `C++ STL` 自带的 `merge` 函数可以方便地合并两个有序数列为一个有序数列，无需手动再写一个 `merge` 函数（为什么这么多人都喜欢手写 `merge`，是因为不知道有这个函数吗，各位 Dalao 可以解释一下吗？）

用法：`merge(原数列 A 开头, 原数列 A 结尾, 原数列 B 开头, 原数列 B 结尾, 目标数列 C 开头)`，注意“开头”“结尾”是指针，且不包括结尾元素（左闭右开），类似 `sort` 的参数传入。

另外一半的排序直接 `sort` 就好了，不会超时。

时间复杂度 $O(N \log N)$

参考代码：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

inline int read()
{
	int x=0;bool w=true;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=false;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^'0');ch=getchar();}
	return w?x:-x;
}

const int N=5e5+5;
int T,n,m;
long long k;
int p[N],st[N],mg[N],lg2[N];

inline bool check(const int L,const int MID,const int R)
{
	if(R>n) return false;
	for(register int i=MID;i<=R;i++)
		st[i]=p[i];
	sort(st+MID,st+R+1);
	merge(st+L,st+MID, st+MID,st+R+1, mg+L);
	long long sum=0;
	int l=L,r=R,cnt=0;
	while(l<r && sum<=k && ++cnt<=m)
	{
		sum+=(long long)(mg[r]-mg[l])*(mg[r]-mg[l]);
		l++,r--;
	}
	if(sum<=k)
	{
		for(int i=L;i<=R;i++)
		st[i]=mg[i];
	}
	return sum<=k;
}

int main()
{
	for(register int i=2;i<=5e5;i++)
		lg2[i]=lg2[i>>1]+1;
	T=read();
	while(T--)
	{
		n=read(),m=read(); scanf("%lld",&k);
		for(register int i=1;i<=n;i++)
			p[i]=read();
		int ans=0;
		int l=1,r=l,bin=1;
		st[l]=p[l];
		while(r<=n)
		{
			if(!bin)
			{
				ans++;
				l=r+1,r=l;
			}
			if(check(l,r+1,r+(1<<bin)-1))
			{
				r=r+(1<<bin)-1;
				bin++;
			}
			else bin--;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

注意 $k$ 和 $sum$ 要开 `long long`。

----------

$2025.8.12$ 更新：修正一处笔误和错别字。

---

## 作者：Aurora_Borealis_ (赞：6)

显然有贪心思路：对于一个点作为一段的左端点，我们找到最远的右端点，然后以该右端点的下一个点作为新左端点继续找。

考虑对于一段区间 $[l,r]$，其最大的 $val$ 为最大值和最小值配对，次大和次小配对，以此类推，证明可以考虑将该方案与其他方案拆括号后做差，差可证明大于 $0$。但是暴力一项一项找肯定是不行的，这样每次都要重新排序，如何减少排序量呢？考虑倍增。这样复杂度优化成了 $O(n \log ^ 2 n)$，仍然不够优秀。考虑改变倍增的顺序，设确定的左边界为 $l$，当前求出的右边界为 $r$，当前倍增区间长度为 $p$，初始 $p=1，r=l-1$，若当前倍增的区间合法，则 $r=r+p，p=p \times 2$，否则将区间回缩，$p= \dfrac{p}{2}$。这样每次倍增新增加一个区间时，可以仅仅将新增的区间排序，因为前面的区间已经确定一定会取了，已经排过序了，归并排序即可。考虑一个点最多被归并 $\log$ 次，所以总复杂度就是 $O(n\log n)$。

---

## 作者：cqbzpyl (赞：5)

## 天才 Acm 

一眼倍增。

我们可以定义一个左端点 $l=1$ 和右端点 $r=l$，然后二分一个 $p$，初始值为 $1$，如果 $[l,r+p] \text{这个区间的校验值} \le T$ 那么 $r$ 就加 $p$,否则 $p$ 除以二，直到 $p=0$ 为止，就找到了从 $l$ 开始校验值不超过 $T$ 最长能到达的 $r$，这样就可以将 $ans$ 累加，将 $l$ 重新设为 $r$。
如:
```cpp
void merge(int l, int mid, int r) {
	int i = l, j = mid + 1;
	for (int k = l; k <= r; k++) {
		if (j > r || i <= mid && a[i] <= a[j])
			b[k] = a[i++];
		else
			b[k] = a[j++];
	}
}
```

```cpp
while (r <= n) {
      if (!p) {
          ans++;
          l = ++r;
          a[l] = rec[l];
          p = 1;
      }
}
```

重复以上过程，直到将整个数组分割完成为止。

而我们可以写一个 check 来判断 $[l,mid-1]$ 和 $[mid,r]$ 合并之后的校验值是否小于等于 $T$，而这两个区间很明显是有序的，我们只需要合并这两个区间，在判断是否合法即可。

### code
```cpp
#include <bits/stdc++.h>
#define sq(a) (a)*(a)
using namespace std;
const int N = 5e5 + 5;
typedef long long ll;
int n, m, ans, cas;//a是保存排序后的数组，b是merge后的数组，rec是保存原序列 
ll t, rec[N], a[N], b[N];
void merge(int l, int mid, int r) {
	int i = l, j = mid + 1;
	for (int k = l; k <= r; k++) {
		if (j > r || i <= mid && a[i] <= a[j])
			b[k] = a[i++];
		else
			b[k] = a[j++];
	}
}
bool check(int l, int mid, int r) {
	//[l, mid - 1]是前一段 
	for (int k = mid; k <= r; k++) a[k] = rec[k];
	sort(a + mid, a + r + 1);
	merge(l, mid - 1, r);
	ll sum = 0;
	for (int k = 1; k <= ((r - l + 1) >> 1) && k <= m; k++) 
		sum += sq(b[r - k + 1] - b[l + k - 1]);
	if (sum <= t) {
		for (int k = l; k <= r; k++) a[k] = b[k];
		return 1;
	}
	else
		return 0;
}
void solve() {
	int p = 1, l = 1, r = 1;
	a[l] = rec[l];
	while (r <= n) {
		if (!p) {
			ans++;
			l = ++r;
			a[l] = rec[l];
			p = 1;
		}
		else if (r + p <= n && check(l, r + 1, r + p)) {
			r = r + p;
			p <<= 1;
		}
		else
			p >>= 1;
	}
}
int main() {
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d%lld", &n, &m, &t); 
		for (int i = 1; i <= n; i++) scanf("%d", rec + i);
		ans = 0;
		solve();
		printf("%lld\n", ans);
	}
	return 0;
} 
```

---

## 作者：gdz0214_and_zxb0214 (赞：3)

# 题意
将 CPU 分成若干段，在每一段满足质检条件的情况下让段数**尽可能的少**。

质检条件：从每段中随机取出 $\min(m,\frac{n}{2})$ 对 CPU，每对的质检值则为**此对 CPU 性能的差的绝对值的平方**，要求所有质检值的和小于等于 $k$。
# 思路
## 朴素思路
既然题目要求区间，容易想到枚举左端点和右端点。

然而分段的问题往往知道左端点，这题仍然如此，遂想到枚举右端点。

再看想质检条件，它要求无论怎样随机取都能满足条件，自然，抽取的答案中的最大值也要满足条件。

明显，要求出最大值就要让每对 CPU 性能的差的绝对值最大。

那么我们就让数组中差的绝对值最大的两个数做一对，再把剩下的数中差的绝对值最大的两个数做一对，以此类推。

于是就可以把数组排序，让两个指针 $i$ 和 $j$ 分别枚举两边的端点，它们便作为一对。

那么质检条件明显具有单调性，若选的元素越多通过的可能性越小。

于是想到二分右端点。
## 优化
然而上面的思路超时了，原来是排序长度过多而超时。

不难想到可以使用**倍增**来减少排序长度。

可能有人想问了，为啥呢？

其实，倍增的排序长度是从小到大，而二分的排序长度则是从大到小。

若右端点位置较为正常，倍增的时间复杂度会远小于二分。

因此，倍增可以代替二分。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,a[500010],b[500010],c[500010],n,m,o;
bool check(int l,int r,int rr){
	for(int i=r+1;i<=rr;i++){
		c[i]=a[i];
	}
	sort(c+r+1,c+rr+1);
	int p1=l,p2=r+1,p3=l;//归并，极限省时间
	while(p1<=r&&p2<=rr){
		if(a[p1]<=c[p2]){
			b[p3++]=a[p1++];
		}else{
			b[p3++]=c[p2++];
		} 
	} 
	while(p1<=r){
		b[p3++]=a[p1++];
	}
	while(p2<=rr){
		b[p3++]=c[p2++];
	}
	int s=0;
	for(int i=l,j=rr,k=1;k<=m&&i<j;i++,j--,k++){//两个指针
		s+=(b[i]-b[j])*(b[i]-b[j]);
		if(s>o){
			return 0;
		}
	}
	return 1;
}
 main(){
	scanf("%lld",&t);
	while(t--){
		int ans=0;
		scanf("%lld%lld%lld",&n,&m,&o);
		for(int i=1;i<=n;i++){
			scanf("%lld",a+i);
		}
		int l=1,r=1;
		while(l<=n){
			int p=1;
			while(r+p<=n&&check(l,r,r+p)){//第一阶段：增加长度不断增加
				r+=p;
				p<<=1;
				for(int i=l;i<=r;i++){//保证有序
					a[i]=b[i];
				}
			}
			p>>=1;//目前已不能满足
			while(p){
				if(r+p<=n&&check(l,r,r+p)){//第一阶段：增加长度不断减小
					r+=p;
					for(int i=l;i<=r;i++){//同理
						a[i]=b[i];
					}
				}
				p>>=1;
			}
			++ans;
			l=r+1;//再次固定左端点
			r=l;//从左端点开始倍增
		}
		printf("%lld\n",ans);
	}
}
```

---

## 作者：Sarakiel_k (赞：2)

## P0455 Genius ACM
### solution
**关键词：贪心，倍增，二路合并（归并）**

题意：简单来说就是，对于一个区间 S，算出区间内最大的 SPD，保证符合要求 $SPD <= k$。从头开始取连续数个这样的区间 S 使得每一段区间都符合要求的情况下取尽量少的数量直至序列结尾。

从头开始，我们让每一个区间都尽量长就好了，这样能分尽量少的段。对于一个区间 S，我们如何获取他的最大 SPD 呢？想法是头尾配对，这样差值最大。来证明一下：

若 $0 < a < b < c < d$，有两种可能最大的结果，$a -c , b - d$ 和 $a - d, b - c$。做一个减法：

$(a - c)^2 + (b - d)^2 - (a - d)^2 - (b - c )^2 = a^2 + c^2 - 2ac + b^2 + d^2 - 2bd - a^2 - d^2 + 2ad - b^2 - c^2 + 2bc = 2bc + 2ad - 2bd - 2ac = 2b(c-d)+2a(d-c) = 2(c-d)(b-a)$，显然，由于 $c - d < 0$，所以后者更大。

好的那么问题就变成了，对于讨论到的左端点 $L$ 我们不断扩大他的右端点，并计算目前 $[L, R]$ 区间内的最大 SPD ，直到区间最大 SPD 超出 $k$ 为止（因为这个 SPD 显然是单调的，因为方差是非负数，数越多 SPD 会越大）。哎，提到这个单调的解空间，那我问你，我们是不是要用二分？哦不，但是让我们仔细想一下，如果这个 SPD 上限非常小，我们每次都让 $R$ 从全局一点点减少，那岂不是浪费时间？在最坏的情况下，要二分 $n$ 次，二分都有最多 $O(\log n)$ 的复杂度，而且每次计算 SPD 的值还要排序，那复杂度将爆炸为 $O(n^2\log^2n)$。这个复杂度显然有些高了。那么我们可以考虑选择和选择的区间本身长度更相关的**倍增**。

对于倍增，我们每一次检验一个区间的 SPD 值，都需要排序再配对，排序复杂度为 $O(n\log n)$。这样总复杂度相比二分降低为 $O(n\log^2n)$。实际上，我们每次排序求 SPD 时，不用把整个区间都重新排序的，已经倍增确定下来的部分已经排过序，也就是说，我们可以通过类似归并排序的方式，先将新区间排序，再将新区间与本身就有序的老区间合并看看是否合规，若合规，将新区间变成“新的”老区间；否则，再“倍减”地试别的新区间。这样可以将排序的复杂度降低，进一步使总体复杂度降低到 $O(n\log n)$。

最后附上一个点警示后人（汗）：不开 long long 会见祖宗。

好的！完结撒花！我把代码做了比较详细的注释，希望各位看的开心～不介意点个赞再走吧～


附上AC代码
```cpp
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;
const int N = 5e5 + 5;
int n, m, ans, group;
ll t, a[N], b[N], temp[N]; //t和SGD不开longlong会见祖宗。

bool check(int l, int r, int newr){ //检查函数，检查将r延伸至r+row（newr）是否符合要求
    for (int i = r + 1; i <= newr; i++) b[i] = a[i]; //复制一份出来
    sort (b + r + 1, b + newr + 1); //将无序区间排序
    
    for (int i = l, j = r + 1, k = l; k <= newr; k++){ //归并排序，合并两半有序区间
        if(i <= r && b[i] <= b[j] || j > newr) temp[k] = b[i++];
        else temp[k]= b[j++]; 
    }

    int num = min(m, (newr - l + 1) / 2); //num是选取的组数，这里取可以取到的最大组。即m和区间长度的小者
    ll SGD = 0; //记得开longlong
    for (int i = l, j = newr, k = 1; k <= num; k++){
        SGD += 1ll * (temp[i] - temp[j]) * (temp[i] - temp[j]);
        i ++, j --; //两头取
    }
    if (SGD <= t){ //若符合要求，则将临时序列temp复制回副本序列b。
        for (int i = l; i <= newr; i++)
            b[i] = temp[i];
        return 1; //return true
    }
    else return 0;
}

void solve(){
    ans = 0; //记得初始化
    int l = 1, r = 0, p = 1; //初始化l为1，r为0。原因有二：1.r若不为0，则在l=r=1时无法将序列第一个a[1]正确加入序列  2.倍增一般初始化是将sum初始化为0，再倍增叠加。
    while(r < n){
        p = 1; //p（意为power，2的p次方）
        r = l - 1; //r为一段序列中0号位置
        while(p > 0){ //p = 0时结束循环
            if(r + p <= n && check(l, r, r + p)) r += p, p *= 2; //若可以加则倍增的向前延伸
            else p /= 2; //若不可以，则“减缓脚步”，逐渐逼近解
        }
        ans ++; //ans统计分段数
        l = r + 1;
    }
    cout << ans << endl;
}

int main(){
    cin >> group;
    while(group--){
        cin >> n >> m >> t;
        for (int i = 1; i <= n; i++) cin >> a[i]; //输入
        solve();
    }

    return 0;
}
```

---

## 作者：MoonCake2011 (赞：2)

此片题解只会简要提及方法，其他的都是卡常。

先贪心，每次选取最远的边界。

寻找校验值时，为了通过测试，所有我们让 SPD 最大。

又发现校验值具有单调性。

于是每对次找边界分组，尝试二分。

然后因为每次都需要去重新计算，所以时间复杂度 $O(n^2\log^2n)$。

woc，这哪过得了啊！

想一想，貌似没有可优化的了啊！

但是，我们可以将二分换为倍增。

因为倍增只会答案有多少，增多少，所以每次寻找时间为 $(r-l+1)\log^2(r-l+1)$。

而不是二分的 $n\log n$，因为二分从 $n$ 开始分的。

每次只需要重新排序计算，所以时间复杂度 $O(n\log^2 n)$。

过不了。

将排序换成基数排序，$O(n\log n)$。

但这是 $90$ 分。

所以，卡常呗！

发现 `sort` 在 $10^3$ 以内跑的比基排优秀一些。

所以分类讨论排序。

加个 `register`。

过了。

[记录](https://www.luogu.com.cn/record/173829095)。

代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define RE register
#define int long long
inline long long read(){
	RE long long x=0,f=1;RE char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,m,t;
int a[500010],p[500010];
int buc[256],b[500010];
inline void radix_sort(int a[],int l,int r){
	int radix=0;
	for(RE int i=1;i<=4;i++){
		memset(buc,0,sizeof buc);
		for(RE int j=l;j<=r;j++) buc[(a[j]>>radix)&255]++;
		for(RE int j=0;j<256;j++) buc[j]+=buc[j-1];
		for(RE int j=r;j>=l;j--) b[l+(buc[(a[j]>>radix)&255]--)-1]=a[j];
		for(RE int j=l;j<=r;j++) a[j]=b[j];
		radix+=8;
	}
}
inline int get(int l,int r){
	for(RE int i=l;i<=r;i++) p[i]=a[i];
	if(r-l+1<=1e3) sort(p+l,p+r+1);
	else radix_sort(p,l,r);
	RE int ans=0,mid=r-l+1>>1;
	for(RE int i=0;i<m && i<mid;i++) ans+=(p[l+i]-p[r-i])*(p[l+i]-p[r-i]);
	return ans;
}
inline void solve(){
	cin>>n>>m>>t;
	for(RE int i=1;i<=n;i++) a[i]=read();
	RE int l=1,r=1,ans=0;
	while(r<=n){
		RE int len=1;
		while(len)
			if(r+len<=n && get(l,r+len)<=t) r+=len,len*=2;
			else len/=2;
		l=++r,ans++;
	}
	printf("%lld\n",ans);
}
signed main() {
	RE int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：lyas145 (赞：1)

题目在[这里](https://www.luogu.com.cn/problem/P10455)。

~~我再不写题解我就要掉成绿名了，所以我就来写题解了。~~

## 解题思路

首先我们需要判断一个数字集合怎样才能符合标准，因为是随机选，并且 SPD 必须小于或等于 $k$，所以只要求出这个集合**最大的 SPD** 与 $k$ 比较即可。

But 最大的 SPD 怎么求？

根据直觉，最大的数与最小的数凑成一对，次大的数与次小的数凑成一对，以此类推下去，就能求出最大的 SPD。

但是直觉不一定每次都准，所以我们还是来证明一下吧。

给定 $a$,$b$,$c$,$d$ 四个数，且 $0 < a < b < c < d$。

根据直觉的话最大的 SPD 为 $(a - d)^2 + (b - c)^2$。

再来一个可能最大的 SPD：$(a - c)^2 + (b - d)^2$。

众所周知，可以通过两个数的差的正负来判断这两个数的大小。所以上面两式相减得：

$
\hspace{0.37cm} ((a - d)^2 + (b - c)^2) - ((a - c)^2 + (b - d)^2)\\
= (a - d)^2 + (b - c)^2 - (a - c)^2 - (b - d)^2\\
= a^2 - 2 \cdot a \cdot d + d^2 + b^2 - 2 \cdot c \cdot d + c^2 - (a^2 - 2 \cdot a \cdot c + c^2) - (b^2 - 2 \cdot b \cdot d + d^2)\\
= a^2 - 2 \cdot a \cdot d + d^2 + b^2 - 2 \cdot c \cdot d + c^2 - a^2 + 2 \cdot a \cdot c - c^2 - b^2 + 2 \cdot b \cdot d - d^2\\
= - 2 \cdot a \cdot d - 2 \cdot c \cdot d + 2 \cdot a \cdot c + 2 \cdot b \cdot d\\
= - 2 \cdot a \cdot d + 2 \cdot a \cdot c - 2 \cdot c \cdot d + 2 \cdot b \cdot d\\
= - 2 \cdot a \cdot (d + c) - 2 \cdot d \cdot (c + b)
$

最后的结果一看就是负数，所以我们的直觉是正确的！

再来想题目怎么做。我们可以从**当前这一段的开头**开始，向 $n$ 不断**扩展**，当我们扩展到第 $i$ 个数时，最大的 SPD **第一次超过了 $k$**，直接把第 $i$ 个数作为新的一段的开头即可，并累计答案。为啥这是对的？因为如果继续扩展的话最大的 SPD 是**不可能下降的**。为啥不可能下降？可以这样想：我们保持 $i$ 之前的数配对方式不变，$i$ 之后扩展的数不管怎么组合，SPD 都**只会是非负整数**，一个大于 $k$ 的数加一个非负整数一定是大于 $k$ 的。

但是似乎还有点问题：求最大的 SPD 需要**排序**！首先 $\mathrm{O}(n^2)$ 的暴力你们肯定都会，直接插入排序就行了，但是这样肯定过不了，我们必须对此做法进行**优化**。

一个一个的扩展太慢了，我们能不能一下扩展好几步呢？答案是能的，于是今天的主角来了！

**倍增**！

我们可以令 $l$ 为这一段的开头，$lt$ 为**将要扩展**的的第一个数的位置（即当前这一段**已确定的部分**末尾的下一个位置），$add$ 为扩展的步数，并且 $add$ 是**先增大、后减小**的，这样做时间复杂度会比较优秀。如果直接把 $[l,lt + add - 1]$ 这一段每次都直接排序的话，时间复杂度是 $\mathrm{O}(n \log^2 n)$ 的，过不去，需要进一步优化。由于 $[l,lt - 1]$ 这一段是已经确定了的，所以这一段的数的原本的位置就**不重要**了，直接用上次排好序的数组覆盖掉就行了，但是 $[lt,lt + add - 1]$ 这一段的数的原本的位置就很**重要**了（原因很简单，留给你们自己思考），我们得把这一段数复制一遍，然后排个序，再把 $[l,lt - 1]$ 与 $[lt,lt + add - 1]$ 合并（类似于归并排序的一次合并），也就是**二路归并**，得到一个排好序的 $[l,lt + add - 1]$ 这么一段。求出这一段的最大的 SPD 后，判断最大的 SPD 是否小于或等于 $k$，如果是，把排好序的这一段覆盖掉原序列的对应位置，方便下次合并时使用。这样做时间复杂度为 $\mathrm{O}(n \log n)$，可以过。

## 码儿

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;   //不开祖宗见 long long。
const int N=5e5+5;
int T,n,m,ans;
ll k;
ll a[N],b[N],c[N];
//以下是各个数组的作用：
//a：原数组，即题目中的 p。
//b：[lt,lt+add-1] 这一段排序时复制 a 用的。
//c：二路归并时的辅助数组。
inline ll read() {           //快读，没啥好看的。
	ll x=0,f=1;
	char c=getchar();
	while (!isdigit(c)) {f=(c=='-'?-1:1);c=getchar();}
	while (isdigit(c)) {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x;
}
ll sqr(ll x) {return x*x;}   //求 x^2 用的。
bool merge(int l,int r,int k) {
	for (int i=k;i<=r;i++) {b[i]=a[i];}    //把 [lt,lt+add-1] 这一段复制下来。
	sort(b+k,b+1+r);         //给 [lt,lt+add-1] 这一段排序。
	int i=l,j=k,cnt=0;       //二路归并。
	while (i<k && j<=r) {
		if (a[i]<=b[j]) {c[++cnt]=a[i++];}
		else {c[++cnt]=b[j++];}
	}
	while (i<k) {c[++cnt]=a[i++];}
	while (j<=r) {c[++cnt]=b[j++];}
	ll res=0;                //计算最大的 SPD。
	for (int i=1,j=cnt;i<j && i<=m;i++,j--) {
		res+=sqr(c[i]-c[j]);
	}
	if (res<=::k) {         //如果最大的 SPD 小于或等于 k。
		for (int i=1;i<=cnt;i++) {a[i+l-1]=c[i];}
		//把排好序的 [l,lt+add-1] 这一段覆盖掉原序列的对应位置的数，以备下次二路归并时使用。
		//[lt,lt+add-1] 已经确定加入这一段了，每个数原本的位置不重要了。
		return 1;            //可以扩展到 lt+add-1，返回 true。
	}
	return 0;      //不能扩展到 lt+add-1，返回 false。
}
int get(int l) {   //返回以 l 为开头的这一段的末尾的下一个位置。
	int lt=l,add=1;
	while (lt+add-1<=n && merge(l,lt+add-1,lt)) {lt+=add;add<<=1;}
	//add 先增大，如果 lt+add-1 大于 n 或 [l,lt+add-1] 这一段的最大 SPD 已超过 k，
	//就不可能再往后扩展了（至于原因自己想，前文对于后者有一定讲解）。
	while (add) {
	//add 开始减小，并且不会再增大，
	//因为每一个自然数都可以分解成若干个 2 的非负整数次幂的形式，且不重复。
		if (lt+add-1<=n && merge(l,lt+add-1,lt)) {lt+=add;}    //可以扩展就扩展。
		add>>=1;
	}
	return lt;
}
int main() {
	T=read();
	while (T--) {
		ans=0;     //ans 初始化。
		n=read();m=read();k=read();
		for (int i=1;i<=n;i++) {a[i]=read();}
		for (int i=1;i<=n;i=get(i)) {ans++;/*累计答案*/}   //i 相当于每一段的开头。
		printf("%d\n",ans);
	}
	return 0;
}
```

Thanks for reading！

---

## 作者：time_keeper (赞：1)

# P10455 Genius Acm

## 贪心部分

显然，对于一个序列 $A$，其 $\text{SPD}$ 值等于前 $m$ 组首尾差。

**举例**

参考 [RainPPR](https://www.luogu.com.cn/article/uh70pgk9)。

若 $a < b < c < d$，则最大的 $\text{SPD}$ 值等于：

$$(d-a)^2+(c-b)^2=d^2-2da+a^2+c^2-2cb+b^2$$

若顺次相减：

$$(b-a)^2+(d-c)^2=b^2-2ba+a^2+d^2-2dc+c^2$$

两式整理得：

$$a^2+b^2+c^2+d^2-2(da+cb)$$
$$a^2+b^2+c^2+d^2-2(ba+dc)$$

作差得：

$$-2(da+cb)+2(ba+dc)$$
$$ = 2(ba+dc-da-cb)$$
$$=2(c-a)(d-b)$$

由 $a < b < c < d$ 易得上式 $>0$。

## 朴素做法

一个想法是从上次满足条件的右端点 $+1$ 开始，找到最长的满足条件的右端点，这样找的次数就是分的段数。

我们每次需要二分右端点，复杂度 $O(\log n)$。

计算 $\text{SPD}$ 值需要 $O(len \log len)$。

复杂度 $O(n^2 \log^2 n)$。

考虑优化。

## 朴素倍增

发现计算 $\text{SPD}$ 值类似于计算最大的 $k$ 满足：

$$\sum_{i=1}^{k}a_i \le T$$

所以可以倍增。

每次从左端点 $last_r + 1$ 开始倍增。

检验区间 $[l,r + 2^p - 1]$ 的 $\text{SPD}$ 值是否合法。

如果合法，则区间长度可以扩展。尝试 $[l,(r + 2^p - 1) + 2^{p-1}-1]$，即 $r=r+2^p-1,p=p-1$。

如果不合法，那么 $p=p+1$。

每次检验的时候排序，然后按上面的方法计算。

复杂度 $O(\log n \times n \log n) = O(n \log^2 n)$。

[提交记录](https://www.luogu.com.cn/record/177330443)

## 归并排序优化

在每次 $r = r + 2^p-1,p=p-1$ 时。

$[l,r+2^p-1]$ 是有序的，所以只需要排序 $[r + 2^p-1,(r + 2^p-1)+2^{p-1}-1]$ 即可。

然后用归并排序的方法合并有序区间。

这样复杂度变成了 $O(n \log n)$

[Jerrycyx](https://www.luogu.com.cn/article/xwxizza8)的文章里提到了 `merge` 函数，确实不知道，但是只和并区间确实好用。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
int a[N];
int n,m;
long long k;
int tmp[N];
int b[N];
bool check(int l,int r,int mid){
	if(r > n) return false;
	for(int i = mid;i <= r;i++) tmp[i] = a[i];
	sort(tmp + mid,tmp + r + 1);
	merge(tmp + l,tmp + mid,tmp + mid,tmp + r + 1,b + l);
	long long sum = 0;
	int cnt = 0;
	for(int L = l,R = r;L < R && ++cnt <= m;L++,R--)
		sum += 1ll * (b[L] - b[R]) * (b[L] - b[R]);
	if(sum > k) return false;
	else{
		for(int i = l;i <= r;i++) tmp[i] = b[i];
		return true;
	}
}
void solve(){
	cin >> n >> m >> k;
	for(int i = 1;i <= n;i++)
		cin >> a[i];
	int l = 1,r = 1;
	int ans = 0,base = 1;
	tmp[1] = a[1];
	while(r <= n){
		if(!base) ans++,l = r + 1,r = l;
		if(check(l,r + (1 << base) - 1,r + 1))
			r = r + (1 << base) - 1,base++;
		else base--;
	}
	cout << ans << '\n';
	for(int i = 1;i <= n;i++) tmp[i] = a[i] = 0;
	n = m = k = 0;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin >> T;
	while(T--){
		solve();
	}
}
```

[提交记录](https://www.luogu.com.cn/record/177331589)

---

## 作者：CommandSR (赞：1)

## 基本思路

首先，根据贪心思想，显然，如果要随意抽，就要让相差最大的 CPU 两两配对，这样能够保证通过成组测试。

我们考虑固定左端点，将右端点从左往右移动，一直到得到的结果大于 $k$ 为止，左端点等于右端点，新开一段，最后输出段数。

显然，我们需要一个 check 函数判断这个区间能否通过测试。

check 函数暴力写法很好写，排序，两端相减，平方，判断是否小于等于 $k$ 即可。

```cpp
bool check(int l, int r, int sub)
{
	tn = 0;
	for (int i = l; i <= r; i++)
	{
		tmp[++tn] = a[i];
	}
	sort(tmp + 1, tmp + 1 + tn);
	int sum = 0, cc = 0;
	for (int i = 1; ++cc <= m && i <= tn/2; i++)
	{
		sum += pow(tmp[i] - tmp[tn+1-i], 2);
	}
	return sum <= k;
```

时间复杂度 $O(n^2 \log^2{n})$ 考虑优化。

### 倍增优化主函数

在主函数右端点右移的过程中使用倍增，用一个变量 $t$ 表示区间长度，若当前区间可行，将其乘 2 否则除以 2。

此时时间复杂度 $O(n \log^2{n})$。

### 归并思想优化 check 函数

建立一个变量 $sub$ 表示上一步结束时的位置。在上一步已经将 $[l, sub)$ 排好了序，现在只需要排序 $(sub, r]$ 即可。

子区间全部排好序之后，只需要将区间归并，使得整个区间有序，在使用之前提到的贪心思想计算即可。

时间复杂度 $$O(n \log{n})$$ 可以通过本题。

具体代码可以看下面。

## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 500010;
int T, n, m, k, a[N];
int tmp[N], b[N];
bool check(int l, int r, int sub)
{	
	// 归并排序优化 nlogn
	
	for (int i = sub; i < r; i++) tmp[i] = a[i];
	sort(tmp + sub, tmp + r);
	
	// 合并区间
	
	int p = l, q = sub, bn = 0;
	while (p < sub && q < r) 
	{
		if (tmp[p] <= tmp[q]) b[bn++] = tmp[p++];
		else b[bn++] = tmp[q++];
	}
	while (p < sub) b[bn++] = tmp[p++];
	while (q < r) b[bn++] = tmp[q++];
	
	int sum = 0;
	for (int i = 0; i < bn && i < m; i++, bn--)
		sum += pow(b[i] - b[bn-1], 2);
	return sum <= k;
}
signed main() 
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> T;
	while (T--)
	{
		cin >> n >> m >> k;
		for (int i = 0; i < n; i++) 
			cin >> a[i];
		
		int l = 0, r = 0, ans = 0;
		while (r < n)
		{
			int t = 1;
			while (t > 0)
			{
				if (r + t <= n && check(l, r + t, r))
				{
					r += t;
					t <<= 1;
					if (r >= n) break;
					for (int i = l; i < r + t; i++)
						tmp[i] = b[i - l];
				}
				else t >>= 1;
			}
			l = r, ans ++;
		}
		cout << ans << '\n';
	}
	return 0;
}
```

拒绝抄袭！

---

## 作者：Noob_Oler (赞：0)

# 题解：P10455 Genius Acm
### [题目](https://www.luogu.com.cn/problem/P10455)

定义 $x$ 为：从集合 $S$ 中取出 $m$ 对数，使得“每对数的差的平方”之和最大。

将集合内最大的 $m$ 个数和最小的 $m$ 个数配对，最大配最小，次大配次小……

在校验值满足条件的前提下，让区间内的元素尽量多。
因为序列已知，所以从左至右考虑每一段的范围时，左端点固定，让右端点尽量大即可。

显然，右端点放置的位置有明显的单调性，可以考虑二分。
即，对于当前左端点，通过二分找到合法的最大的右端点。

检验长度为 $n$ 的区间。

最坏情况下，每次的可行区间的长度较短，二分时会从长到短对若干区间进行校验值计算。

此时，每轮二分检验的区间长度之和，规模为 $n$。

不难发现，二分时，若可行区间长度太短，会进行额外的无效排序。

此时可考虑用倍增替代二分，具体步骤为：

$1.$ 初始化区间长度 $p = 1$，右端点 $r = l$。

$2.$ 求出区间 $l\sim r + p$ 的校验值，若合法，则`r += p`且`p *= 2`，否则`p /= 2`。

$3.$ 重复步骤 $2$ 直到 $p$ 变为 $0$，此时的 $r$ 为所求。

进一步优化。

首先，我们对 $a$ 区间排序。若可行，则继续对 $a + b$ 区间排序。

但由于区间 $a$ 已经有序，可以直接对区间 $b$ 进行排序，再将两个区间归并即可。

这样，需要排序的无序序列，其总长度规模为 $n$。

---

