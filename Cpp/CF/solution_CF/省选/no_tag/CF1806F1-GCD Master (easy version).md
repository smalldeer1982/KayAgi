# GCD Master (easy version)

## 题目描述

This is the easy version of the problem. The only difference between the two versions is the constraint on $ m $ . You can make hacks only if both versions of the problem are solved.

You are given an array $ a $ of length $ n $ and two integers $ m $ and $ k $ . Each element in $ a $ satisfies $ 1\le a_i \le m $ .

In one operation, you choose two indices $ i $ and $ j $ such that $ 1 \le i < j \le |a| $ , then append $ \gcd(a_i,a_j) $ to the back of the array and delete $ a_i $ and $ a_j $ from the array. Note that the length of the array decreases by one after this operation.

Find the maximum possible sum of the array after performing exactly $ k $ operations.

## 说明/提示

In the first test case, the best way is to choose $ i=1 $ , $ j=3 $ in the first operation. The final sequence is $ [7,4] $ .

## 样例 #1

### 输入

```
3
3 8 1
4 7 8
5 114 2
7 2 4 1 6
3 514 2
2 3 3```

### 输出

```
11
14
1```

# 题解

## 作者：DeaphetS (赞：2)

题目大意：给定 $n,m,k(1\le k\lt n \le 10^6,1\le m\le 10^{6})$ 以及一个长度为 $n$ 的序列 ${a_i}(1\le a_i\le m)$。每次操作可以选取两个数 $x,y$ 从序列中删去，并将 $\gcd(x,y)$ 加入序列中。求进行恰好 $k$ 次操作后 $\sum a_i$ 的最大值。

### 分析题目性质

显然如果序列中存在相同的两个元素，那么可以通过对这两个相同元素进行操作，把他们合并成一个元素并消耗一次操作次数，于是我们先假设所有元素都互不相同，思考如何解题。

考虑这么一件事情，如果一开始选了两个数 $x,y$ 并将其合并为 $\gcd(x,y)$ 加到了序列中，之后我们再把这个 $\gcd$ 拿出来去和另一个数字 $z$ 合并。那么这一系列操作就相当于把 $x,y,z$ 三个数字从序列中删去，并在序列中加入新数字 $\gcd(x,y,z)$。于是我们可以把操作分成若干组，每组操作就相当于选取 $t$ 个数字从序列中删去，然后把这 $t$ 个数字的 $\gcd$ 加入到序列中，一组操作所花费的操作次数就是 $t-1$ 次。

可以很自然地想到，若划分的组数越多，被波及的数字个数就越多，于是就会有一个猜想：是否一次性选取 $k+1$ 个数字把他们合并就是最优的。我们来证明这个猜想。

#### 猜想 1：一次性选取 $k+1$ 个元素进行合并是最优策略

考虑反证法，如果操作的组数有多组，那么考虑其中两组操作。不妨设第一组操作涉及到的数字集合为 $S$，各个数字的 $\gcd$ 为 $x$；第二组操作涉及的数字集合为 $T$，$\gcd$ 为 $y$，且有 $x\ge y$。那么这两组操作带来的贡献就是 $x+y-\sum_{i\in S}{i}-\sum_{j\in T}{j}$。

接下来观察把这两组操作进行合并对贡献造成的影响。选取 $S$ 中最大的数字 $mx$，由于不可重集 $S$ 中的 $\gcd$ 为 $x$ 且 $|S|\ge 2$，所以有 $mx\ge 2x$。考虑将 $mx$ 从 $S$ 中删除（即不对该数字进行操作），并对 $S,T$ 各自合并后的结果 $x,y$ 进行一次操作，那么在操作次数不变的情况下，其贡献为 $\gcd(x,y)-\sum_{i\in S}{i}-\sum_{j\in T}{j}+mx$。

对比两种操作的贡献，去除掉相同的部分有 $mx+\gcd(x,y)\gt 2x\ge x+y$，得出后者更优。于是最优方案下的操作组数只会有一组，即得证。

#### 题意转换

猜想得到证明后，我们就能将题意转化为：选 $k+1$ 个数字将他们合并成这些数字的 $\gcd$，求代价最少的方案。当然，这里有个前提是序列中的元素各不相同。

考虑有相同元素怎么办。实际上如果有相同的元素出现在同一组操作中，可以看做先把相同的元素合并成一个元素，剩下的是互不相同的元素一起操作。那么每次把两个相同元素合并的代价就是对应元素的值。

于是可以把重复的数字拎出来并排序，令 $b_i$ 表示删去 $i$ 个重复元素的最小花费。枚举 $i$ 的值，计算一次性选 $k-i+1$ 个数字合并的最小花费就能得到最终的答案。

在这一系列转换过后，我们要解决的问题就变成了：对每个 $i\le k+1$，求选择 $i$ 个数字合并成他们的 $\gcd$ 的最小花费。

由于简单版本的值域只有 $10^6$，那么就有一个经典的做法就是枚举 $\gcd$ 的值，之后判断 $\gcd$ 的每个倍数是否存在并计算即可。计算答案部分的时间复杂度为 $O(m\log m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1000010
int T,n,m,k,x,cnt,c[N];
long long sum,ans,b[N];
void init()
{
	cnt=sum=ans=0;
	scanf("%d%d%d",&n,&m,&k);
	k++;
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		c[x]++;
		sum+=x;
		if(c[x]>1)b[++cnt]=x;
	}
	sort(b+1,b+cnt+1);
	for(int i=1;i<=cnt;i++)b[i]+=b[i-1];
	if(cnt>=k-1)ans=max(ans,sum-b[k-1]);
	for(int i=1;i<=m;i++){
		long long res=i;
		for(int j=i,num=0;j<=m && num<k;j+=i)if(c[j]){
			res-=j,num++;
			if(cnt>=k-num)ans=max(ans,sum+res-b[k-num]);
		}
	}
	for(int i=1;i<=m;i++)c[i]=0;
	printf("%lld\n",ans);
}
int main()
{
	scanf("%d",&T);
	while(T--)init();
}
```


---

## 作者：mazihang2022 (赞：2)

考虑 F1：

首先，假设 $a$ 中元素互不相同。

改写一下问题：将序列分成 $n-k$ 组，最大化每组的 $\gcd$ 之和。我们设 $S_i$ 表示一个组的元素。

> 定理 $1$：当 $k>0$ 时，原序列的最小元素所属的组满足 $|S_a|>1$。

证明：

如果 $|S_a|=1$，我们可以找到一个组 $S_x$ 使得 $|S_x|>1$。可以证明，用原序列的最小元素替换 $S_x$ 的最大元素一定更优。

设 $a$ 为原序列的最小值，$b$ 为 $S_x$ 的最大值。

- 原始答案是 $a+\gcd(S_x)$。
- 用最小元素替换 $S_x$ 的最大元素，答案是 $b+\gcd(S_x \setminus \{b\}\cup\{a\}) >b$。



因为 $\gcd(S_x) \le \max{S_x} - \min S_x = b-\min S_x < b-a$，所以 $a+\gcd(S_x)< a+b-a=b<b+\gcd(S_x \setminus \{b\}\cup\{a\})$。Q.E.D.

注意，当 $\max S_x = \min S_x$ 时，$\gcd(S_x) \not\le \max{S_x} - \min S_x$，这就是为什么需要 $a$ 中元素互不相同。



> 定理 $2$：当 $k>0$ 时，只有一个 $S_x$ 满足 $|S_x| >1$。

证明：

设 $S_a$ 为包含最小元素的组。

根据定理 $1$，我们知道 $|S_a| >1$。我们可以从序列中删除 $S_a$ 包含的所有元素，将 $\gcd({S_a})$ 添加到序列中，并让 $k$ 减去 $|S_a|-1$。很明显 $\gcd(S_a)$ 是新的序列中的最小元素。我们可以继续这个过程直到 $k=0$，这告诉我们只有 $|S_a|=k+1>1$。Q.E.D.

我们可以枚举 $\gcd(S_a)$，做到 $O(n+m\ln m)$ 的复杂度。

如何处理重复的元素呢？

我们可以发现，对于重复的元素，最好的策略是将它们与相同的数合并，所以它和之前的部分是独立的。枚举对重复元素执行的操作次数即可。



---

考虑 F2：

仍然假设 $a$ 中元素互不相同。假设 $a$ 已经排好序了。

> 定理 $3$：当 $k>0$ 时，我们将选择前 $k$ 个元素，然后从剩下的元素当中再选择一个。

也就是说，$S=\{a_1,a_2,\ldots,a_k,a_x\}$，其中 $k < x \le n$，是唯一一个包含多个元素的组。

证明：

假设 $T=\{a_1,a_2,\ldots, a_{p}, a_{c_1}, a_{c_2}, \ldots, a_{c_t}\}$，其中 $p+1<c_1<c_2<\cdots<c_t$，$t\ge 2$，$p+t=k+1$。那么我们可以证明 $T'=\{a_1,a_2,\ldots, a_{p},a_{p+1}, a_{c_1}, a_{c_2}, \ldots, a_{c_{t-1 }}\}$ 一定更优。

设 $g=\gcd(T)$，$g'=\gcd(T')$。我们有 $a_{c_t}-a_{p+1}> a_{c_t}-a_{c_{t-1}}\ge g$。

$\Delta=ans(T')-ans(T)=a_{c_t}-a_{p+1}+g'-g> g'>0$。

重复这个过程，最后我们就能得到 $S=\{a_1,a_2,\ldots,a_k,a_x\}$，其中 $k < x \le n$。Q.E.D.



当有重复元素时，我们在去重后的序列中分别求出取 $1\sim k$ 个数的答案。前缀 $\gcd$ 只有 $O(\log m)$ 种不同的值，所以我们可以做到 $O(n \log^2 m)$（另一个 $O(\log m)$ 是计算 $\gcd$ 的复杂度）。设 $g_i$ 为前缀 $\gcd$。当我们在剩下的数中寻找最优的元素时，我们需要计算 $\gcd(g_i,a_j)$，导致时间复杂度成为 $O(n \log^2 m)$。我们可以发现，$g_i\mid g_{i-1}$，所以 $\gcd(g_i,a_j)=\gcd(g_i,\gcd(g_{i-1},a_j))$。$\gcd$ 是不降的，所以总复杂度可以做到 $O(n \log m)$（可以理解成对 $\gcd$ 势能分析）。

---

## 作者：chroneZ (赞：0)

容易得知操作顺序和最终结果是无关的，考虑对序列从小到大排序后逐个操作。

我们发现，如果我们不考虑序列中最小的元素，而是去合并序列后方更大的元素，我们一定希望后面元素有较大的 $\gcd$。但是稍作考虑后发现，其 $\gcd$ 值的上界仅为被合并的元素中最小的值，而这些元素的总和对答案造成的减量是非常之大的。

考虑 $k = 1$。对于序列中的最小值 $a_1$ 以及任意两非最小值 $a_i, a_j(i < j)$，如果选择合并 $a_i, a_j$，答案的减量（后文称之为“代价”）为 $a_i + a_j - \gcd(a_i, a_j)$，最优情况下这个值为 $a_j$，**这要求序列可重**；如果序列不可重，$\gcd(a_i, a_j) \leq \min(a_i, a_j - a_i)$，这意味着最优的代价为 $a_i + a_j - \min(a_i, a_j - a_i)$。

然而，如果我们转而合并 $a_1, a_i$，代价为 $a_1 + a_i - \gcd(a_1, a_i)$，最劣情况下这个值为 $a_1 + a_i - 1$。

**钦定序列是不可重的**，二者作差得到选择 $a_1$ 时至少可以减少的代价为 $a_j - a_1 - \min(a_i, a_j - a_i) + 1$。分别讨论 $a_j$ 在 $a_1, \frac{a_j}{2}$ 之间及 $\frac{a_j}{2}, a_j$ 之间，可证该值恒大于 $1$，此处略。至此我们发现，对于任意无重复元素的序列，**与最小值合并一定是最优的选择**。

考虑 $k > 1$。由于 $\gcd(a_1, a_i) \leq a_1$，因此与最小值合并后得到的新元素 $\gcd(a_1, a_i)$ 一定会成为序列中新的最小值。依此归纳下去，每次我们都会选择一个数与最小值合并，并将它们的 $\gcd$ 作为新的最小值，直到达到操作次数。因此所有的被操作数应被合并于一起，换言之，我们只需选定 $k + 1$ 个数一次性合并，最大化剩余元素与这 $k + 1$ 个数的 $\gcd$ 的总和。

至此已经足够解决 F1 了。需要注意的是关于重复元素的问题，在上文有提到：当序列可重时，如果选择合并 $a_i, a_j(a_i = a_j)$，代价为 $a_j$，是更优于与最小值合并的（e.g. 对于序列 $\{2, 5, 5\}$，合并成 $\{2, 5\}$ 显然优于合并成 $\{1, 5\}$）。但是这种最优的情况仅限相同元素之间，因此它独立于不可重的情形，我们可以将原序列去重，并单独考虑出现次数 $> 1$ 的元素。具体地，记 $b_i$ 表示共合并 $i$ 个相同元素的最小代价，$c_x$ 为 $x$ 在 $a$ 中的出现次数，记 $a'$ 为将 $a$ 中所有元素出现次数减一后的可重序列（即 $a$ 中的元素 $x$ 在 $a'$ 中的出现次数）。仍然对 $a'$ 从小到大排序，则 $b_i \gets a_i + b_{i - 1}$ 即得。

由于值域只有 $10^6$，枚举 $\gcd$ 的值为 $g$（即最小元素的因数），每次从小到大加入 $g$ 的倍数，记当前加入的元素集为 $T$，$sum = \sum \limits_{i = 1} ^ n a_i$，若 $k + 1 - |T| \in [0, |b|]$，令 $Ans \gets \max(Ans, sum - \sum \limits_{x \in T} x + g - b_{k + 1 - |T|})$。

```cpp
void solve(){
	i64 n, m, k; cin >> n >> m >> k;
	vector<i64> a(n), b, e(m + 1, 0);
	i64 sum = 0, ans = 0;
	for(int i = 0; i < n; i++)
		cin >> a[i];
	sort(a.begin(), a.end());
	for(int i = 0; i < n; i++){
		if(e[a[i]]) b.push_back(a[i]);
		e[a[i]] = 1; sum += a[i];
	}
	b.push_back(0); sort(b.begin(), b.end());
	for(int i = 1; i < b.size(); i++)
		b[i] += b[i - 1];
	int L = b.size() - 1;

	if(L >= k) ans = max(ans, sum - b[k]);
	for(int g = 1; g <= m; g++){
		if(a[0] % g) continue;
		int t = 0; i64 s = 0;
		for(int i = g; i <= m; i += g){
			if(!e[i]) continue;
			t++; s += i;
			if(0 <= k + 1 - t && k + 1 - t <= L)
				ans = max(ans, sum - s + g - b[k + 1 - t]);
		}
	}
	cout << ans << "\n";
}
```


---

