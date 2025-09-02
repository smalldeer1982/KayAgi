# The Thorny Path

## 题目描述

According to a legend the Hanoi Temple holds a permutation of integers from $ 1 $ to $ n $ . There are $ n $ stones of distinct colors lying in one line in front of the temple. Monks can perform the following operation on stones: choose a position $ i $ ( $ 1 \le i \le n $ ) and cyclically shift stones at positions $ i $ , $ p[i] $ , $ p[p[i]] $ , .... That is, a stone from position $ i $ will move to position $ p[i] $ , a stone from position $ p[i] $ will move to position $ p[p[i]] $ , and so on, a stone from position $ j $ , such that $ p[j] = i $ , will move to position $ i $ .

Each day the monks must obtain a new arrangement of stones using an arbitrary number of these operations. When all possible arrangements will have been obtained, the world will end. You are wondering, what if some elements of the permutation could be swapped just before the beginning? How many days would the world last?

You want to get a permutation that will allow the world to last as long as possible, using the minimum number of exchanges of two elements of the permutation.

Two arrangements of stones are considered different if there exists a position $ i $ such that the colors of the stones on that position are different in these arrangements.

## 说明/提示

Let's label the colors of the stones with letters. Explanations for the first two test cases of the first example:

1. Using the permutation $ [2, 3, 1] $ , we can additionally obtain the arrangements CAB and BCA from ABC. This is already the maximum possible result.
2. Using the permutation $ [2, 1, 3] $ , the only BAC can be obtained from ABC. As we saw in the previous case, two arrangements are not the maximum possible number of distinct arrangements for $ n = 3 $ . To get an optimal permutation, for example, we can swap $ 1 $ and $ 3 $ , so we will get the permutation $ [2, 3, 1] $ .

## 样例 #1

### 输入

```
3
3
2 3 1
3
2 1 3
3
1 2 3```

### 输出

```
3 0
3 1
3 2```

## 样例 #2

### 输入

```
5
4
2 3 4 1
4
2 3 1 4
4
2 1 4 3
4
2 1 3 4
4
1 2 3 4```

### 输出

```
4 0
4 1
4 0
4 1
4 2```

# 题解

## 作者：AsunderSquall (赞：3)

## 题意

给定一个大小为 $n$ 的排列 $P$，你可以任意交换排列中的两个元素若干次，要求在最大化 交换后的排列 的各个置换环的大小的乘积的情况下，最小化交换元素的次数。

## 题解


发现可以用一次操作把一个大小为 $a$ 的置换环变成大小为 $b$ 和 $a-b$ 的两个置换环。也可以用一次操作把大小为 $a$ 和 $b$ 的置换环变成一个大小为 $a+b$ 的置换环。

那么可以直接考虑变成数的问题。即，有 $m$ 个和为 $n$ 的数，一次操作可以把 $a$ 变成 $b$ 和 $a-b$，也可以把 $a$ 和 $b$ 变成 $a+b$，让你最大化所有数的乘积，同时最小化步数。

```cpp
num.clear();
rd(n);for (int i=1;i<=n;i++) rd(a[i]);for (int i=1;i<=n;i++) v[i]=0;
for (int i=1;i<=n;i++){int x=i,len=0;while (!v[x]) v[x]=1,x=a[x],len++;if (len)num.push_back(len);}
```


------------

先考虑所有数的乘积，显然有，分成尽量多的 $3$，如果余下的是 $1$，就把 $3 \times 1$ 变成 $2 \times 2$。

或者说：  
$ans= 3^{n/3} (n \bmod 3 =0),ans=4 \times 3^{\lfloor n/3 \rfloor -1} (n \bmod 3 =1),ans=2 \times 3^{\lfloor n/3 \rfloor}(n \bmod 3=2)$。

-------------

然后考虑最小化步数。  

$n \bmod 3 =0$ 的情况显然，因为最终拆分是固定的（要求 $3$ 尽可能多），只需贪心拆出最多的 $3$，然后将 $1,2$ 尽可能地匹配即可。  

$n \bmod 3 =2$ 的情况只需要先提出一个 $2$ 来，在按照 $n \bmod 3=0$ 的情况做就行了。

代码：  
```cpp
if (n%3==0)
{
    ans=ksm(3,n/3);
    for (int x:num) res+=(x-1)/3,cnt[x%3]++;
    res+=min(cnt[1],cnt[2]);
    if (cnt[2]>cnt[1]) res+=(cnt[2]-cnt[1]);
    if (cnt[1]>cnt[2]) res+=(cnt[1]-cnt[2])/3*2;
}
if (n%3==2)
{
    ans=ksm(3,n/3)*2%mod;
    for (int x:num) res+=(x-1)/3,cnt[x%3]++;
    if (cnt[2]) cnt[2]--;else cnt[1]-=2,res++;
    res+=min(cnt[1],cnt[2]);
    if (cnt[2]>cnt[1]) res+=(cnt[2]-cnt[1]);
    if (cnt[1]>cnt[2]) res+=(cnt[1]-cnt[2])/3*2;
}
```

------------

重点是 $n \bmod 3 =1$，因为这个时候并不是拆出越多 $3$ 越好。  

而且也不一定是拆成若干个 $3$ 和两个 $2$，因为拆出一个 $4$ 和两个 $2$ 是等效果的。  

不过拆出一个 $4$ 的情况我们可以先处理掉，枚举在哪个数中拆出了 $4$，统计答案是 $O(1)$ 的。

还有一个可能是拆出了一个 $3$ 和一个 $1$ 合并成一个 $4$，我们也可以处理掉。

最后是有两个 $2$ 的情况，我们可以想到，一定是由现成的 $1$ 和 $2$ 拼出了两个 $2$，这样也可以处理掉。

这样就做完了，注意判断一下现成的 $1$ 和 $2$ 是否足以拼成两个 $2$。

```cpp
if (n%3==1) 
{
    ans=ksm(3,n/3-1)*4%mod;
    bool flag=0;
    for (int x:num) res+=(x-1)/3,cnt[x%3]++;
    int Res=res;
    res=inf;
    tmp=Res;
    int c[3];c[1]=cnt[1];c[2]=cnt[2];
    if (c[2]>=2) {c[2]-=2;}else {int x=2-c[2];c[2]=0;c[1]-=2*x;tmp+=x;}
    tmp+=min(c[1],c[2]);
    if (c[2]>c[1]) tmp+=(c[2]-c[1]);
    if (c[1]>c[2]) tmp+=(c[1]-c[2])/3*2;
    if (c[1]>=0 && c[2]>=0) res=min(res,tmp);
    for (int x:num) if (x>=4)
    {
        tmp=Res-(x%3!=0);
        cnt[x%3]--;cnt[(x-4)%3]++;
        tmp+=min(cnt[1],cnt[2]);
        if (cnt[2]>cnt[1]) tmp+=(cnt[2]-cnt[1]);
        if (cnt[1]>cnt[2]) tmp+=(cnt[1]-cnt[2])/3*2;
        res=min(res,tmp);
        cnt[(x-4)%3]--;cnt[x%3]++;
    }
    if (cnt[0] && cnt[1]) 
    {
        tmp=Res+1;
        cnt[1]--;
        tmp+=min(cnt[1],cnt[2]);
        if (cnt[2]>cnt[1]) tmp+=(cnt[2]-cnt[1]);
        if (cnt[1]>cnt[2]) tmp+=(cnt[1]-cnt[2])/3*2;
        res=min(res,tmp);
    }
}
```

代码写得太狗屎了，完整代码可以去 [CF](https://codeforces.com/contest/1411/submission/129158559)
 上查看。

---

## 作者：紊莫 (赞：0)

意义不明的题目，完全不值 ``*3000``。

---

首先乘积最大一定是若干个 $2$ 和 $3$，并且至多两个 $2$，因为三个 $2$ 不如两个 $3$，根据交换元素对置换环的影响，我们可以任意合并和分裂，也就和排列没有关系了。

我的做法也是讨论 $n$ 模 $3$ 的值，如果只分出至多 $1$ 个 $2$，那么直接将所有元素分到 $\le 3$，然后直接贪心匹配，此处略。

主要是 $n$ 模 $3$ 为 $2$ 的情况，可能的麻烦是 $2\times 2 = 4$，也就是有时候会保留（合并出） $4$，而不是两个 $2$。

那么我的做法和上面一样，首先将所有元素分到 $\le 4$。

考虑这个 $4$ 怎么被我得到，得到了之后也是贪心匹配。

1. 直接一个 $4$，不花费代价。
2. 两个 $1$ 和一个 $2$，花费 $1$ 的代价。
3. 一个 $1$ 和一个 $3$，花费 $1$ 的代价。
4. 两个 $2$，不花费代价。
5. 四个 $1$，花费 $2$ 的代价。

可能还有我没考虑到的情况，但是这样五种情况已经可以通过原题，若有 hack，请告知我。

然而这些操作多个同时可行，顺序是会影响后面的答案的。

方便起见，我直接将这五个条件枚举全排列，然后取答案最小值即可。

[提交记录。](https://codeforces.com/contest/1411/submission/326120404)

---

## 作者：Shapy_UI_Tools (赞：0)

## 前言
要理解置换环的特性：
1. 交换一个环的两个点，环被以这两个点为界拆成两份。
2. 交换两个环的两个点，两个环被合并。
3. 两个小环的大小之和为大环的大小。

## 简化题意
（原题是 $n$ 个点，我们设一共有 $m$ 个环。）

给定 $m$ 个数，可以把 $x1+x2$ 拆成 $x1$ 和 $x2$，也可以把 $x1$ 和 $x2$ 合并成 $x1+x2$。求所有数乘积的最大值。
## 解法
### 性质探究
首先，可以发现我们可以把所有数全拆成一堆 $1$，然后再把这些 $1$ 任意合并。所以，对于一个固定的 $n$，其最大乘积是固定的。而对于任意两个数 $x$、$y$，如果 $|x-y| \ge 2$，则根据基本不等式，$xy<(\frac{x+y}{2})^2$，而我们要使乘积最大，所以 $x=y$ 或 $|x-y|=1$。所以，答案的组成一定是 $x$ 个 $\lfloor \frac{n}{x} \rfloor$ 与 $1$ 个 $n \bmod \lfloor \frac{n}{x} \rfloor$。当然，如果 $n \bmod \lfloor \frac{n}{x} \rfloor=0$，就没有那 $1$ 个 $n \bmod \lfloor \frac{n}{x} \rfloor$ 了。通俗来讲，就是把 $n$ 平均分成 $x$ 份。

现在，我们就要求出这个 $x$ 究竟在取多少的时候可以使 $(\frac{n}{x})^x$ 最大。
$$
f(x)=(\frac{n}{x})^x=e^{x \ln \frac{n}{x}}
$$
设
$$
\begin{aligned}
g(x)&=x \ln \frac{x}{n} \\
g'(x)&=\ln\frac{x}{n}+x\ln'\frac{x}{n} \\
&=\ln\frac{x}{n}+x(\frac{1}{\frac{1}{n}x} \times \frac{1}{n}) \\
&=\ln\frac{x}{n}+1
\end{aligned}
$$
则
$$
\begin{aligned}
f(x)&=e^{-g(x)} \\
f'(x)&=-e^{-g(x)}g'(x) \\
&=-e^{x \ln\frac{n}{x}}(\ln\frac{x}{n}+1) \\
&=-(\frac{n}{x})^x(\ln\frac{x}{n}+1)
\end{aligned}
$$
我们希望找到 $f(x)$ 的最大值，即
$$
\begin{aligned}
&f'(x)=-(\frac{n}{x})^x(\ln\frac{x}{n}+1)=0 \\
\because\;&(\frac{n}{x})^x \ne 0 \\
\therefore\;&\ln\frac{x}{n}+1=0 \\
\therefore\;&\ln x=\ln n-1 \\
\therefore\;&x=\frac{n}{e}
\end{aligned}
$$
所以，把 $n$ 分成 $\frac{n}{e}$ 份可以使乘积最大。所以每份的大小就是 $e$。$3$ 要比 $2$ 更接近 $e$，所以每份大小为 $3$ 可以使乘积最大。
### 思路
我们设 $b$ 为一个存储所有环的大小的数组。比如数据是 `2 3 4 1 5`，则 $b$ 数组为 `4 1`，分别代表环 `2 3 4 1` 和环 `5` 的大小。
1. 对于 $\forall b_i \bmod 3=0$，把 $b_i$ 等分成 $\frac{b_i}{3}$ 个 $3$ 即可。**我们称由这种方式得到的 $3$ 为“天然 $3$”。**
2. 如果有 $b_i \bmod 3=1$ 且有 $b_j \bmod 3=2$，就将这两个数合并，因为一定有 $(b_i+b_j) \bmod 3=0$，所以再将 $b_i+b_j$ 等分成 $\frac{b_i+b_j}{3}$ 个 $3$。**我们称由这种方式得到的 $3$ 为“合成 $3$”。** 当一个数比较小的时候是很难处理的，而一个数比较大的时候是很好处理的，于是我们要对模 $3$ 余数的每个类别的数分别从小到大排序
- 此时，判断如果所有数全部进行了前两步之一，直接输出答案。
3. 若尚有一些数没有进行任何操作，那剩下的数要么满足 $\forall b_i \bmod 3=1$，要么满足 $\forall b_i \bmod 3=2$，否则它们之间会进行 2 操作。无论 $\forall b_i \bmod 3=1$ 还是 $\forall b_i \bmod 3=2$，均有 $\forall b_i+b_j+b_k \bmod 3=0$，所以我们先尽量地进行三合一，也就是将 $b_i$、$b_j$、$b_k$ 加起来后，再等分成 $\frac{b_i+b_j+b_k}{3}$ 个 $3$。**这种方式得到的 $3$ 却并不能算作“合成 $3$”，因为合成它的数模 $3$ 的余数是相等的。**
- 为什么对于模 $3$ 余数不等于 $3$ 的数，这么合并后分离就一定最优呢？因为我们通过这种方式进行的操作与数的大小是成正比的，我们会进行固定次数的合并操作然后进行 $\frac{x}{3}-1$ 次的分裂；但如果我们先进行分裂再合并，有可能遇到分出来的碎块不能直接拼出 $3$，还需要再次分裂，所以一定不会更优。
4. 之后还要处理三合一之后仍然没有操作完毕的数，也就是剩下的数已经不足三个以供合并了。先考虑 $\forall b_i \bmod 3=1$，此时如果这个数不是 $1$，我们就直接从里面分出来 $3$，直到剩下了 $4$。比如，当前的数是 $10$，我们就分离出来两个 $3$，剩下 $4$。如果这个数是 $1$，我们就先扔那不管。因为 $1$ 和 $4$ 的功能略有差别，如果盲目把 $4$ 也都拆到 $1$，就可能存在本来可以提供 $4$ 的贡献，结果因为拆分只能提供 $1 \times 3=3$ 的贡献了。但 $1$ 又需要闲置，这样才能在之后有需要时拿出来用。
5. 然后考虑 $\forall b_i \bmod 3=2$，此时只要不断从里面分离出 $3$，剩下 $2$ 就好了。$5$ 必然更劣，因为我们可以将其拆解为 $2$ 和 $3$，产生 $2 \times 3=6$ 的贡献。所以，就只有这一种处理方法。
6. 接下来，场上还剩下一些 $1$ 闲置没有处理。但是，$1$ 的数量一定最多有 $2$ 个，因为一旦有 $3$ 个，就会在 3 操作中被进行三合一。我们考虑把 $1$ 跟别的数合并。场上存在的数一定是 $1$、$3$、$4$，不可能会存在 $2$，否则会在操作 2 中进行二合一。我们先考虑场上只有 $1$ 个 $1$，则如果跟 $3$ 合并可以产生 $\frac{3+1}{3}=\frac{4}{3}$ 的贡献，如果跟 $4$ 合并成 $5$ 后又给 $5$ 拆了可以产生 $\frac{2 \times 3}{4}=\frac{3}{2}$ 的贡献，显然与 $4$ 合并的贡献给更大，所以优先考虑和 $4$ 合并，一合一拆总共两步操作。如果没有 $4$，就先考虑和“合成$3$”合并，再考虑和“天然 $3$”合并。这两种合并方式带来的贡献是相等的，但是与“天然 $3$”合并需要一步，而与“合成 $3$”合并可以视为撤销那次合成操作，然后把其中模 $3$ 余数等于 $1$ 的数跟 $1$ 合并，与模 $3$ 余数等于 $2$ 的数乘积产生贡献 $2 \times 2=4$，这种方式相当于返回一次操作同时加了一次操作，也就是操作次数为 $0$。
7. 然后考虑场上有两个 $1$，此时应该将两个 $1$ 合并成 $2$，产生贡献 $\frac{1+1}{1}=2$。我们不可能把它们合并给 $4$，因为根本就不可能有 $4$，否则 $2$ 个 $1$ 和 $1$ 个 $4$，它们模 $3$ 的余数相等，会在操作 3 中进行三合一。我们也不应该把它们合并给 $3$，因为产生的贡献是 $(\frac{4}{3})^2=\frac{16}{9}$，贡献太低。
8. 考虑场上存在的 $4$ 的数量如果为 $1$ 个，则要么不管它，要么在操作 6 中跟 $1$ 合并。同 7 中所述，此时不可能有两个 $1$ 存在。如果有 $2$ 个 $4$，应该将其合并后拆解为 $2$ 个 $3$ 和 $1$ 个 $2$，需要 $3$ 步操作，产生贡献 $\frac{3 \times 3 \times 2}{4 \times 4}=\frac{9}{8}$。同 7 中所述，此时不可能有 $1$。

至此，所有情况就都讨论完了。
### 实现
首先要把输入数据转换成环的大小，`vis` 数组存储一个点是否已经加环了，跟着数组的数走，一边走一边给环的大小加，如果碰到了访问过的点就把环的大小记下来然后继续找新环。

然后要根据模 $3$ 的余数分类存储所有数并从小到大排序。

需要开四个变量分别存储当前场上 $b_i \in [1,4]$ 的数量，并额外开一个变量存储“合成 $3$”的数量。

按照上述思路进行大分类讨论，并按照操作统计步数。

## 代码
[提交记录](https://codeforces.com/contest/1411/submission/227491054)
```cpp
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#define int long long
using namespace std;

const int N = 1e6 + 10, MOD = 1e9 + 7;

int T;

int n;
int a[N];
bool vis[N];
int b[N], m;
vector<int> v[3];
int cnt1, cnt2, cnt3, _cnt3, cnt4;
int ans = 0;

void clear() {
	memset(vis, 0, sizeof(vis));
	memset(b, 0, sizeof(b));
	m = 0;
	cnt1 = cnt2 = cnt3 = _cnt3 = cnt4 = 0;
	ans = 0;
	v[0].clear();
	v[1].clear();
	v[2].clear();
}

int ksm(int x, int y) {
	if (y == 0) return 1;
	int res = ksm(x, y >> 1);
	res = res * res % MOD;
	if (y & 1) res = res * x % MOD;
	return res;
}

void print() {
	printf("%lld %lld\n", ksm(2, cnt2) * ksm(3, cnt3) % MOD * ksm(4, cnt4) % MOD, ans);
}

signed main() {
	scanf("%lld", &T);
	while (T--) {
		clear();
		scanf("%lld", &n);
		for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		for (int i = 1; i <= n; i++) {
			if (vis[i]) continue;
			m++;
			for (int j = i; !vis[j]; j = a[j]) {
				b[m]++;
				vis[j] = true;
			}
		}
		for (int i = 1; i <= m; i++) v[b[i] % 3].push_back(b[i]);
		for (int i = 0; i < 3; i++) sort(v[i].begin(), v[i].end());
		for (int i = 0; i < v[0].size(); i++) {
			cnt3 += v[0][i] / 3;
			ans += v[0][i] / 3 - 1;
		}
		int pos = 0;
		while (pos < v[1].size() && pos < v[2].size()) {
			cnt3 += (v[1][pos] + v[2][pos]) / 3;
			_cnt3 += (v[1][pos] + v[2][pos]) / 3;
			ans += 1;
			ans += (v[1][pos] + v[2][pos]) / 3 - 1;
			pos++;
		}
		if (pos == v[1].size() && pos == v[2].size()) {
			print();
			continue;
		}
		if (pos < v[1].size()) {
			while (pos + 2 < v[1].size()) {
				cnt3 += (v[1][pos] + v[1][pos + 1] + v[1][pos + 2]) / 3;
				_cnt3 += (v[1][pos] + v[1][pos + 1] + v[1][pos + 2]) / 3;
				ans += 2;
				ans += (v[1][pos] + v[1][pos + 1] + v[1][pos + 2]) / 3 - 1;
				pos += 3;
			}
			for (int i = v[1].size() - 1; i >= pos; i--) {
				if (v[1][i] != 1) {
					cnt3 += v[1][i] / 3 - 1;
					ans += v[1][i] / 3 - 1;
					cnt4++;
				}
				else {
					cnt1++;
				}
			}
		}
		else {
			while (pos + 2 < v[2].size()) {
				cnt3 += (v[2][pos] + v[2][pos + 1] + v[2][pos + 2]) / 3;
				_cnt3 += (v[2][pos] + v[2][pos + 1] + v[2][pos + 2]) / 3;
				ans += 2;
				ans += (v[2][pos] + v[2][pos + 1] + v[2][pos + 2]) / 3 - 1;
				pos += 3;
			}
			for (int i = v[2].size() - 1; i >= pos; i--) {
				cnt3 += v[2][i] / 3;
				ans += v[2][i] / 3;
				cnt2++;
			}
		}
		if (cnt1 == 1) {
			if (cnt4 != 0) {
				cnt4--;
				cnt3++;
				cnt2++;
				ans += 2;
			}
			else if (_cnt3 != 0) {
				cnt1--;
				cnt3--;
				cnt2 += 2;
			}
			else if (cnt3 != 0) {
				cnt1--;
				cnt3--;
				cnt4++;
				ans++;
			}
		}
		else if (cnt1 == 2) {
			cnt1 -= 2;
			cnt2++;
			ans++;
		}
		if (cnt4 == 2) {
			cnt4 -= 2;
			cnt3 += 2;
			cnt2++;
			ans += 3;
		}
		print();
	}
};
```

---

