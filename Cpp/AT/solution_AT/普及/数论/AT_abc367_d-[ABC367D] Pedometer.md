# [ABC367D] Pedometer

## 题目描述

一个湖泊周围有 $N$ 个休憩所。这些休憩所按顺时针方向被标记为 $1, 2, \ldots, N$。从休憩所 $i$ 到休憩所 $i+1$（其中休憩所 $N+1$ 指的是休憩所 $1$）顺时针行走需要 $A_i$ 步。已知从某个休憩所 $s$ 到另一个不同的休憩所 $t$ 顺时针行走的最短步数是 $M$ 的倍数。我们需要计算所有可能的 $(s,t)$ 组合的数量。

## 说明/提示

#### 制约条件

- 所有输入数据都是整数。
- $2 \le N \le 2 \times 10^5$
- $1 \le A_i \le 10^9$
- $1 \le M \le 10^6$

#### 示例解释 1

- 从休憩所 $1$ 到休憩所 $2$ 顺时针行走的最短步数是 $2$ 步，这不是 $3$ 的倍数。
- 从休憩所 $1$ 到休憩所 $3$ 顺时针行走的最短步数是 $3$ 步，这是 $3$ 的倍数。
- 从休憩所 $1$ 到休憩所 $4$ 顺时针行走的最短步数是 $7$ 步，这不是 $3$ 的倍数。
- 从休憩所 $2$ 到休憩所 $3$ 顺时针行走的最短步数是 $1$ 歩，这不是 $3$ 的倍数。
- 从休憩所 $2$ 到休憩所 $4$ 顺时针行走的最短步数是 $5$ 步，这不是 $3$ 的倍数。
- 从休憩所 $2$ 回到休憩所 $1$ 顺时针行走的最短步数是 $8$ 步，这不是 $3$ 的倍数。
- 从休憩所 $3$ 到休憩所 $4$ 顺时针行走的最短步数是 $4$ 步，这不是 $3$ 的倍数。
- 从休憩所 $3$ 回到休憩所 $1$ 顺时针行走的最短步数是 $7$ 步，这不是 $3$ 的倍数。
- 从休憩所 $3$ 回到休憩所 $2$ 顺时针行走的最短步数是 $9$ 步，这是 $3$ 的倍数。
- 从休憩所 $4$ 回到休憩所 $1$ 顺时针行走的最短步数是 $3$ 步，这是 $3$ 的倍数。
- 从休憩所 $4$ 回到休憩所 $2$ 顺时针行走的最短步数是 $5$ 步，这不是 $3$ 的倍数。
- 从休憩所 $4$ 回到休憩所 $3$ 顺时针行走的最短步数是 $6$ 步，这是 $3$ 的倍数。

因此，符合条件的 $(s,t)$ 组合数量为 $4$。

## 样例 #1

### 输入

```
4 3
2 1 4 3```

### 输出

```
4```

## 样例 #2

### 输入

```
2 1000000
1 1```

### 输出

```
0```

## 样例 #3

### 输入

```
9 5
9 9 8 2 4 4 3 5 3```

### 输出

```
11```

# 题解

## 作者：小粉兔 (赞：9)

在博客园食用更佳：<https://www.cnblogs.com/PinkRabbit/p/-/ABC367>。

## 题意简述（\*1037）

环上有 $n$ 个关键点，按顺时针以 $1 \sim n$ 编号。

给定正整数 $a_1, \ldots, a_n$。从点 $i$ 顺时针走 $a_i$ 的距离才能到达顺时针方向的下一个点。

给定 $m$，求满足从点 $i$ 顺时针走到点 $j$ 的距离为 $m$ 的倍数的点对 $(i, j)$（要求 $i \ne j$）的数量。

数据范围：$n \le 10^5$，$a_i \le 10^9$，$m \le 10^6$。

## 题解

考虑断环为链，变为 $2 n$ 个点，前 $n$ 个只作辅助用，后 $n$ 个作为关心的终点。记录下这些点的坐标（即从原点出发到达它们需要的距离）。

要问从多少个点出发到达点 $i$ 的距离为 $m$ 的倍数，就是在问从 $i$ 往前数 $n - 1$ 个点（不包含 $i$ 本身），这些点中坐标与 $i$ 的坐标模 $m$ 同余的点的数量。

使用一个值域为 $[0, m)$ 的桶来统计余数，终点每向右移动一次时，就在桶中添加它当前坐标的余数，并删除它在绕一圈前坐标的余数。将桶中与当前相同的余数数量（但要减去 $1$，因为本身不算）累加就得到答案。

时空复杂度为 $\mathcal O(n + m)$。

## 参考 AC 代码

```cpp
#include <iostream>
#include <vector>
using std::cin, std::cout;

#define F2(i, a, b) for(int i = a; i < (b); ++i)

void Solve();
int main() {
    cin.sync_with_stdio(false);
    cin.tie(nullptr);
    Solve();
    return 0;
}

using LL = long long;

void Solve() {
    int n, m;
    cin >> n >> m;
    std::vector<int> a(n);
    F2(i, 0, n)
        cin >> a[i];
    std::vector<int> b(m, 0);
    int s = 0;
    F2(i, 0, n) {
        s = (s + a[i]) % m;
        ++b[s];
    }
    int t = s;
    LL ans = 0;
    F2(i, 0, n) {
        s = (s + a[i]) % m;
        ++b[s];
        --b[(s - t + m) % m];
        ans += b[s] - 1;
    }
    cout << ans << '\n';
}
```

---

## 作者：yszkddzyh (赞：8)

首先需要知道断环为链的小技巧，即将原本长度为 $n$ 的数组变成长度为 $2n-1$ 的数组，且对于每一个 $n < i < 2n$，有 $a_i=a_{i-n}$。比如样例 $1$，$a$ 原来为 ${2,1,4,3}$，我们将其变为 ${2,1,4,3,2,1,4}$，这样，原来在环上的操作，就变成了在后来的数组中对每一个长度为 $n$ 的子区间的操作。

断环为链后，使用类似于前缀和的方法，将 $a_i$ 的含义变成**从 $1$ 到 $i$ 顺时针的距离**，比如样例 $1$，断环为链后，$a={2,1,4,3,2,1,4}$，我们将其变为 ${0,2,3,7,10,12,13}$，其中 $a_1=0$ 表示从 $1$ 到 $1$ 顺时针的距离为 $0$，$a_2=2$ 表示从 $1$ 到 $2$ 的顺时针的距离为 $2$，以此类推，最后 $a_7=13$ 表示从 $1$ 到第二圈的 $3$ 顺时针的距离为 $13$。代码实现就类似于前缀和的求法，待会看代码。

经过上述的处理，我们即是要找 $(i,j)$ 的个数，满足 $i<j$ 且 $j-i+1\leq n$ 且 $m\mid (a_j-a_i)$，也就是说，$i$ 和 $j$ 在同一个长度为 $n$ 的子区间内（否则 $a_j-a_i$ 就不是从 $i$ 到 $j$ 的最短距离了），并且 $a_j-a_i$ 为 $m$ 的倍数。

这时应该能自然地想到解法：将 $a$ 中每一个数对 $m$ 取模。这样 $a_j-a_i$ 是 $m$ 的倍数就变成了 $a_i=a_j$。比如样例 $1$，经过前缀和处理后 $a={0,2,3,7,10,12,13}$，再对 $m=3$ 取模得到 ${0,2,0,1,1,0,1}$ 然后你就找 $i<j$ 且 $j-i+1\leq n$ 且 $a_i=a_j$ 的个数就行了。具体方法是从后往前扫描，开一个桶动态维护每个数出现的次数，再统计答案。

代码：
```cpp
#include <bits/stdc++.h>
#define int long long//十年OI一场空 
using namespace std;

const int N = 4e5 + 5;//断环为链所以要开两倍 
const int M = 1e6 + 5;
int n, m, ans, a[N], cnt[M];//cnt就是桶 

signed main(){
	
	ios :: sync_with_stdio(false);
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = n + 1; i <= 2 * n - 1; i++) a[i] = a[i - n]; //断环为链 
	for(int i = 1, p = 0, t; i <= n * 2 - 1; i++)
		t = a[i], a[i] = p, p += t;//求类似前缀和的东西，这里t是临时变量，p是这一位的值
	//上面不懂的话可以对照样例手搓一下
	for(int i = 1; i <= n * 2 - 1; i++) a[i] = a[i] % m + 1;//取模 
	for(int i = 2 * n - 1; i > n; i--) cnt[a[i]]++;//这里要先将能n+1到2n-1的数丢进桶里 
	for(int l = n, r; l >= 1; l--){//扫描每一个区间，l,r为左右端点，循环内部统计的是与左端点相等的数量 
		r = l + n - 1;//求出右端点 
		ans += cnt[a[l]];//统计与左端点相等的数量 
		cnt[a[r]]--, cnt[a[l]]++;//动态更新桶，由于右端点下一次循环就不在区间内了，所以要减掉 
	}
	cout << ans;
	
	return 0;
}
```

---

## 作者：nr0728 (赞：7)

考虑一下如果把题目中的环改成序列怎么做。这个很简单，先前缀和，令 $s_i=\sum\limits_{j=1}^i A_j$，然后如果从 $S$ 走到 $T$，那么路程就是 $\sum\limits_{i=S}^{T-1}A_i=s_{T-1}-s_{S-1}$。然后如果这种情况合法，即：

$$
s_{T-1}-s_{S-1}\equiv 0\pmod M\\
s_{T-1}-s_{S-1}=kM\ (k\in\mathbb Z)\\
s_{T-1}-kM=s_{S-1}\ (k\in\mathbb Z)\\
s_{T-1}-k_1M=s_{S-1}-k_2M\ (k_1,k_2\in\mathbb Z)\\
s_{T-1}\equiv s_{S-1}\pmod M
$$

所以我们对于每个 $i$，看第 $i$ 个数前面有没有和它同余的数，存一下就行了：

```cpp
map<int,int> mp;
++mp[0];
int ans=0;
rep(i,1,n)
{
	ans+=mp[s[i]%m];
	++mp[s[i]%m];
}
```

然后再考虑本题的环，因为走的一定是最近路程，比如考虑样例，不可能 $1\rightarrow 2\rightarrow 3\rightarrow 4\rightarrow 1\rightarrow 2$，只能直接走到 $2$。

所以我们把数组复制一份接到原来数组的后面，然后 $N\leftarrow 2N$。我们可以发现，$\forall i\geq \dfrac N 2,j\leq i-\dfrac N 2$，如果路程是 $s_{i}-s_{j}$ 那就不是最短路径。我们一边算一遍减掉不合法的贡献就行了。由于在一个序列上的情况我们在 $i\leq \dfrac N 2$ 的时候已经算过了，所以 $i\geq \dfrac N 2$ 的数就不能贡献。

这个说起来可能有点绕，结合[代码](https://atcoder.jp/contests/abc367/submissions/56827609)理解。

---

## 作者：LuukLuuk (赞：4)

# 题解：AT_abc367_d [ABC367D] Pedometer

### 题目大意
在环上有 $N$ 个点，相邻两点 $i,i+1$ 之间距离为 $A_i$。设 $d_{i,j}$ 为顺时针从 $i$ 走到 $j$ 的距离，求对于所有的 $d_{i,j},i\neq j$ 中能被 $K$ 整除的数的个数。

数据范围：

- $2 \le N \le 2 \times 10 ^ 5$
- $1 \le A_i \le 10^9$
- $1 \le M \le 10 ^ 6$

### 思路
首先，考虑时间 $\mathcal{O}(N^2)$ 的破环成链加前缀和做法。设前缀和为 $sum$，枚举 $i, j$，则 $d_{i,j} = sum_j - sum_{i - 1}$。

注意 $M$ 的数据范围，刚好可以开数组。由整除性质可知若 $x\equiv y \mod M$，则 $M\mid x - y$，又因为距离的计算为两前缀和的差，则有且仅当两前缀和同余时它们有贡献。

具体地，我们可以设 $vis_x$ 为模 $M$ 余 $x$ 的 $sum$ 值的个数。枚举区间起点的上一个数 $i-1$，统计 $sum_{i}$ 到 $sum_{i + n - 1}$ 中的 $vis$ 数组值。统计时在 $i=0$ 时统计一遍 $sum_1$ 到 $sum_{n-1}$ 的 $sum$ 值，在后来枚举 $i = {1, \dots, n - 1}$ 的循环中每次减去 $sum_{i}$，加上 $sum_{i + n - 1}$。$vis_{i-1}$ 即为当前起点的所有贡献。时间为 $\mathcal{O}(N)$。

### 代码

**注意：要开 `long long`!**

```cpp

#include <cstdio>
#include <cmath>
using namespace std;

#define int long long
int vis[1000010];
int sum[400010];
int a[400010];
int n, m, ans;

signed main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
		a[i + n] = a[i];//破环成链 
	}
	for (int i = 1; i <= 2 * n; ++i) {
		sum[i] = sum[i - 1] + a[i];//前缀和 
		//统计vis（到n时回到自己），所以不算 
		if (i < n)	vis[sum[i] % m] ++;
	}
	ans += vis[0];//先把从一号开始的算进答案 
	for (int i = 1; i < n; ++i) {
		//减去自己的前缀和 
		vis[sum[i] % m] --;
		//加上最新的前缀和 
		vis[sum[i + n - 1] % m] ++;
		//答案即为和当前前缀和同余的 
		ans += vis[sum[i] % m];
	}
	printf("%lld", ans);
	return 0;
}

```

---

## 作者：Redshift_Shine (赞：4)

## 4. Pedometer

就是这道题让我失去了理论 perf 值。

首先，在没有环的情况下，有一个非常显然的模前缀和做法，直接开桶计数即可。

如果有环，就将数组复制两份，在里面做长度为 $n-1$ 的滑动窗口就可以了。注意，一定是 $n-1$，否则起点终点相同的情况会被统计，然后 WA 掉。

时间复杂度 $O(n)$。

```c++
#include <iostream>
#include <map>
using namespace std;
const int N = 2e5 + 10, M = 1e6 + 10;
int n, m, cnt[M];
using ll = long long;
ll a[N << 1], res;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", a + i);
        a[n + i] = a[i];
    }
    for (int i = n * 2; i > n; i--)
    {
        a[i] = (a[i] + a[i + 1]) % m;
        cnt[a[i]]++;
    }
    for (int i = n; i; i--)
    {
        cnt[a[n + i]]--;
        a[i] = (a[i] + a[i + 1]) % m;
        res += cnt[a[i]];
        cnt[a[i]]++;
    }
    // for (int i = 1; i <= 2 * n; i++)
    // {
    //     printf("%lld%c", a[i], " \n"[i == 2 * n]);
    // }
    printf("%lld\n", res);
}
```

---

## 作者：Your_Name (赞：2)

## 题意
给出一个环，顺时针编号，同时给出 $i$ 号点与 $i + 1$ 号点之间的距离，问有多少对 $(s, t)$ 满足从 $s$ 顺时针走到 $t$ 的最短距离为 $M$ 的倍数。
## 思路
看到环形问题，第一步就是破环成链。（这是很经典的思路，不会的可以看看区间 $dp$ 的题目）

然后，我们来考虑怎么样才能达成从 $s$ 顺时针走到 $t$ 的最短距离为 $M$ 的倍数。

我拿样例举例。
![](https://cdn.luogu.com.cn/upload/image_hosting/o1q1bidm.png)

（一）直接暴力枚举左右端点，再暴力计算两点距离，复杂度 $O(n^3)$。

（二）考虑优化。

因为我们是要快速求出两点之间的距离，且两点距离仅为简单相加（如 $1$ 到 $4$ 的距离为 $1$ 到 $3$ 的距离加 $3$ 到 $4$ 的距离），所以想到直接前缀和优化。

记 $Sum_i$ 表示从 $1$ 号点到 $i+1$ 号点的距离。

则转移方程为：$Sum_i = Sum_{i - 1} + a[i]$。

从 $s$ 到 $t$ 的距离为 $Sum_t - Sum_s(s \le t)$。

$Sum$ 数组维护区间即为图中棕色标记。
![](https://cdn.luogu.com.cn/upload/image_hosting/vs5qmwdf.png)

这样，然后再复制一遍数组，枚举起点和终点，复杂度 $O(n^2)$。

（三）再次优化。

根据上文的计算距离公式“$Sum_t - Sum_s$”，我们把他设为 $dis$，可以看出在对答案有贡献的前提下：
* $M \mid dis$（即 $dis$ 一定为 $M$ 的倍数）
* $dis \in \mathbb{Z}$

根据这两个性质，再根据[余数的可减性](https://oi-wiki.org/math/number-theory/basic/#%E5%90%8C%E4%BD%99)，我们可以得出以下结论：
* $Sum_s \equiv Sum_t(\bmod \ M)$（即 $Sum_t \bmod M = Sum_s \bmod M$）

看不懂的话我可以解释一下。

>我们设 $a=Sum_t$，$b=Sum_s$。
>
>我们再设$k_1$，$k_2$ 为最大的，使 $a=k_1 \times M + >C_1$，$b=k_2 \times M + C_2$ 满足的，非负整数。
>
>因为：$(a-b) \bmod M=0$
>
>所以：$(a-b) \bmod M=((k_1-k_2)\times M+C_1-C_2)\bmod M=(C_1-C_2)\bmod M=0$
>
>又因为 $C_1<M$ 且 $C_2< M$
>
>因此：$C_1=C_2$，所以：$a\equiv b(\bmod \ M)$，$Sum_s \equiv Sum_t(\bmod \ M)$。

有了这个，我们可以得出，想要两点之间距离为 $M$ 的倍数，我们只需要找有几个 $(s, t)$ 满足$Sum_s \equiv Sum_t(\bmod \ M)$ 且 $(s < t)$ 即可。

链上的问题解决了，我们来看看环怎么做。

首先还是把数组复制一遍，然后对这个长度为 $2n$ 的序列跑一遍前缀和，然后在统计答案时加上他前面有多少个 $Sum$ 满足条件。

你可以看看这张图（$cnt_i$ 表示前面有多少个 $Sum_j$ 满足 $Sum_j\bmod M=i$）：

![](https://cdn.luogu.com.cn/upload/image_hosting/k52cs6mp.png)

但你写了就会发现，这样是不行的。

以下标为 $7$ 为例，$Sum_7 \bmod M=2$ 按我们之前的说法，他应该加上 $cnt_2$ 但是现在 $cnt_2$ 记录的那个一还是下标为 $1$ 贡献的，可是 $1$ 号点 到 $4$ 号点的最短路径并不是 $1,2,3,4,1,2,3,4$ 所以这段路径本身并不合法，也就不能记录在答案里。

解决方法也很简单，直接把不合法的贡献减掉，在复制段不累计贡献即可。

解释一下：

>1. 当前下标大于等于 $n$ 时，可以发现合法的贡献下标一定小于 $n$，所以只要维护下标小于 $n$ 的贡献即可。
>2. 当前下标大于等于 $n$ 时，可以发现合法的贡献下标一定大于 $i-n$，所以只要维护下标大于 $i-n$ 的贡献即可。

还有，图中下标为 $8$ 的那一列，也就是下标为 $2n$ 的那一列不需要维护，因为没有一个合法路径经过那里。

复杂度 $O(n)$，肯定能过。
## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 4e5 + 10, M = 1e6 + 10;//注意开两倍空间
LL n, m, a[N], sum[N], cnt[M], ans;
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        a[i + n] = a[i];//复制一遍
    }
    cnt[0] = 1;//从0到1的Sum为0，所以当前cnt[0]为1
    for(int i = 1; i < n * 2; i++){//最后一个不考虑
        if(i >= n)cnt[sum[i - n] % m] --;//取消贡献，为什么是i-n上面讲了
        sum[i] = sum[i - 1] + a[i];//前缀和
        ans += cnt[sum[i] % m];//累计答案
        if(i < n)cnt[sum[i] % m] ++;//在复制段的贡献是无效的。
    }
    cout << ans;
    return 0;
}
```
 _完结撒花_ 。

---

## 作者：2c_s (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc367_d)

## 思路

题意：要求找环上**顺时针**区间和为 $M$ 的倍数的区间数。

看到这里，首先我们想到可以将 $N$ 的范围**扩大一倍**来处理环，并且用**前缀和取模**的方式来计算每个点的权。

之后我们发现，当且仅当区间**左右端点的权相同时**，这个区间和才为 $M$ 的倍数。

- 证明：如果一个点 $A$ 的权为 $w_A$，另一个点 $B$ 的权为 $w_B$，设区间 $[A,B]$ 为符合要求的区间，那么$w_A$ 的权再加上 $M$ 的倍数 $k$，则 $w_B=(w_A+k\cdot M)\bmod M=w_A\bmod M+k\cdot M\bmod M=w_A$。所以 $w_B=w_A$，证毕。

知道了这个点后，又发现 $1\le M\le 10^6$，所以我们完全可以把每个权为 $w$ 的位置存在对应的桶中，之后用 ``lower_bound`` 和 ``uppber_bound`` 查找，找到符合要求的区间数，输出。

时间复杂度 $\mathcal{O}(N\log N)$，空间复杂度 $\mathcal{O}(N+M)$。

- 记得开 long long。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll read(){
	ll k=0;bool flag=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')flag=0;c=getchar();}
	while(isdigit(c)){k=(k<<1)+(k<<3)+(c^48);c=getchar();}
	if(flag)return k;return -k;
}
const int N=1e6+10;//数组开够。
ll n,m,a[N],sum[N];
vector<ll>ve[N];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i)a[i]=a[i+n]=read();
	for(int i=1;i<=n<<1;++i){//记得这里要到 n*2。
		sum[i]=(sum[i-1]+a[i])%m;
		ve[sum[i]].push_back(i);
	}
	ll ans=0;
	for(int i=1;i<=n;++i){
		ll pl=lower_bound(ve[sum[i]].begin(),ve[sum[i]].end(),i)-ve[sum[i]].begin();//计算符合要求的左端点的位置。
		ll pr=upper_bound(ve[sum[i]].begin(),ve[sum[i]].end(),i+n-1)-ve[sum[i]].begin()-1;//计算符合要求的右端点的位置，upper_bound 记得 -1。
		ans+=pr-pl;
	}
	cout<<ans;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/173525358)

---

## 作者：zzhbpyy (赞：1)

### [传送门](https://www.luogu.com.cn/problem/AT_abc367_d)
## 思路
对于环上问题，我们容易想到断环成链。由于题目要求求出距离为 $M$ 倍数的数对 $(s,t)$ 数量，对序列求一次前缀和并对 $M$ 取模。容易发现，若前缀和序列中的两个数相等，则说明有一组数对满足条件。但是暴力枚举是 $O(n^2)$ 复杂度的，无法通过本题。我们可以开一个桶进行优化，每次将答案加上这个数出现过的次数。

但是这种做法会计算重复，最后的答案还需要减去前 $n-1$ 个数的答案。复杂度为 $O(n)$。
## 代码
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[400005],cnt[1000005];
signed main(){
	ios::sync_with_stdio(0),cin.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=n+1;i<=2*n;i++)a[i]=a[i-n];
	int ans=0,res=0;
	for(int i=1;i<=n;i++){
		(a[i]+=a[i-1])%=m;
		ans+=cnt[a[i]%m];
		if(i==n-1)res=ans;
		cnt[a[i]%m]++;
	}
	for(int i=n+1;i<=2*n-1;i++){
		(a[i]+=a[i-1])%=m;
		cnt[a[i-n]%m]--;//将i-n处的前缀和从桶中剔除，否则可能会累加转了一圈回来继续走的情况
		ans+=cnt[a[i]%m];
		cnt[a[i]%m]++;
	}cout<<ans-res;
}
```

---

## 作者：__O_v_O__ (赞：1)

我们发现，环上的问题不好处理，于是我们考虑断环为链。

于是，原来的问题转化为了以下问题：给定序列 $a$，求有多少对 $(s,t)$ 满足 $m\mid \sum\limits_{i=s}^t a_i$ 且 $t-s\le n$。

这里有一个区间和，我们用前缀和处理，于是问题又简化为了求满足 $m\mid S_t-S_s$ 且 $t-s\le n$ 的 $(s,t)$ 对数（其中 $S$ 是前缀和）。

现在，答案已经呼之欲出，我们枚举每个元素，用一个桶动态存储每个数前面与它距离 $\le n$ 的数模 $m$ 的余数。处理当前元素时，将答案加上桶中它模 $m$ 的余数项的值即可。

注意：只有当前元素下标大于 $n$ 时才计算答案，否则可能对同一个 $(s,t)$ 计算多次。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a[1000001],s[1000001],an,b[1000001];
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i],a[i+n]=a[i];
	}
	for(int i=2;i<=2*n;i++){
		s[i]=s[i-1]+a[i-1];
	}
	for(int i=1;i<=2*n;i++){
		if(i<=n)b[s[i]%m]++;
		else{
			if(i>n)b[s[i-n]%m]--;
			an+=b[s[i]%m];
			b[s[i]%m]++;
		}
	}
	cout<<an;
	return 0;
}
```

---

## 作者：Guizy (赞：1)

以下为本人赛时思路。

先破环成链，然后我们可以把 $1$ 号休息区看作是从位置 $0$ 走了 $A_1$ 步之后的位置。把每个休息区到 $0$ 的距离模 $M$ 的余数算出来（前缀和），然后每次用一个 $flag$ 数组统计前面（从 $1\sim i-1$）有多少个休息区到 $i$ 的距离是 $M$ 的倍数（显然满足条件当且仅当从 $0$ 到两个休息区分别的距离在模 $M$ 意义下相同）。但是因为是破环成链，所以不能走一圈以上（即 $i$ 不能走到 $i+n-1$ 之后的点），同时要去掉两个点都在 $[i+n,2n]$ 这个区间内合法的点对个数。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,a[1000001],k;
int sum[1000001];
int flag[1000001];

signed main(){
	
	cin>>n>>k;
	for(int i=1;i<=n;i++) 
		cin>>a[i],a[i+n]=a[i];
	
	int ans=0;
	for(int i=1;i<=n*2;i++)
		sum[i]=sum[i-1]+a[i],sum[i]%=k;
	for(int i=1;i<=n*2;i++){
		if(i>=n+1) flag[sum[i-n]]--;//不能走一圈以上
		ans+=flag[sum[i]];
		flag[sum[i]]++;
	}
  
	memset(flag,0,sizeof flag);
	for(int i=n+1;i<=n*2;i++){
		ans-=flag[sum[i]];
  //两个点都在 [i+n,2n] 这个区间内，减去
		flag[sum[i]]++;
	}
	cout<<ans
	return 0;
}
```

---

## 作者：EricWan (赞：1)

开一个桶，记录 $1$ 走到每个点的距离模 $m$ 的值，新来一个点，计算它前面有几个点与它有合法关系，如果向后绕一圈，它前面有几个点与它有合法关系。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, suma, sum, ans, box[10000005], a[10000005], sur[10000005], pre[10000005];
signed main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		suma += a[i];
		pre[i] = pre[i - 1] + a[i];
	}
	for (int i = n; i >= 1; i--) {
		sur[i] = sur[i + 1] + a[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		sum += a[i];
		sum %= m;
		ans += box[sum];
		ans += box[(m - sur[i + 1] % m) % m];
		box[sum]++;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：under_the_time (赞：1)

## 题意

> 给定一个环，从第 $i$ 个位置顺时针方向走到第 $i+1$（若 $i+1>n$ 那么就是走到 $1$）个位置需要 $a_i$ 步。给定 $m$，求 $(s,t)$ 的对数，满足 $s\ne t$ 且从 $s$ 顺时针走到 $t$ 的步数为 $m$ 的倍数。
>
> $n\le 2\times 10^5$，$m\le 10^6$，$a_i\le 10^9$。

## 解法

路径可以分为走 $n\to 1$ 和不走 $n\to1$，分别对应 $s>t$ 和 $s<t$。先考虑后者。我们从 $1$ 到 $n$ 求出一个前缀和 $s$，$s_i$ 表示从 $1$ 到 $i$ 所需的步数，那么答案即为
$$
\sum_{i=1}^n\sum_{j=i+1}^n[s_j-s_i\equiv0\pmod m]=\sum^n_{i=1}\sum^n_{j=i+1}[s_i\equiv s_j\pmod m]
$$
我们提前将所有 $s_i$ 对 $m$ 取模后，此时的问题就转化为：对于每个 $i$，求在 $[i+1,n]$ 中与 $s_i$ 相等的元素个数，然后求和。倒着扫一遍用个桶记录一下，先求再插入即可。

然后考虑 $s>t$ 的情况。我们破环成链，将 $s$ 继续向 $[n+1,2n]$ 处延申；那么答案即为：对于每个 $i\in[1,n]$，求在 $[n+1,i-1]$ 中与 $s_i$ 相等的元素个数，然后求和。与上一个情况同理。然后就做完了。

## 代码

```cpp
// Problem: D - Pedometer
// Contest: AtCoder - AtCoder Beginner Contest 367
// URL: https://atcoder.jp/contests/abc367/tasks/abc367_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Good luck to the code >w<
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
int a[maxn], n, m; 
#define ll long long
const int maxm = 1e6 + 5;
int t[maxm], s[maxn << 1];
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i ++)
		scanf("%d", &a[i]), a[i] %= m;
	// c1
	for (int i = 1; i <= n; i ++)
		s[i] = (1ll * s[i - 1] + 1ll * a[i - 1]) % m;
	ll ans = 0;
	for (int i = n; i >= 1; i --) {
		ans += t[s[i]], t[s[i]] ++;
		// cout << ans << '\n';
	}
	// c2
	memset(t, 0, sizeof(t)); 
	s[n + 1] = (1ll * s[n] + 1ll * a[n]) % m;
	for (int i = n + 2; i <= 2 * n; i ++)
		s[i] = (1ll * s[i - 1] + 1ll * a[i - n - 1]) % m;
	for (int i = n * 2; i > n; i --) {
		ans += t[s[i]], t[s[i - n]] ++;
		// cout << ans << '\n';
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：_wsq_ (赞：1)

直接做是 $O(n^2)$ 的，肯定不行。

显然可以先把从 $1$ 开始的答案都预处理出来。考虑转移到从 $2$ 开始的答案时，出现了哪些变化。

1. 所有答案要减去从 $1$ 到 $2$ 的距离
2. 要加入 $2$ 到 $1$ 的贡献
3. 要把 $1$ 到 $2$ 的贡献减掉

$2$ 和 $3$ 是很好维护的，开几个变量就行。对于 $1$，显然直接减是很麻烦的，考虑预处理出从 $1$ 开始每一个余数都有多少。

![](https://cdn.luogu.com.cn/upload/image_hosting/w6w7d81l.png)

因此，可以记录一下 $1$ 到当前点的距离模 $m$ 的余数，然后找出对应的答案即可。

代码（$c$ 数组用于记录当前从 $1$ 开始的答案）
```cpp
#include <iostream>
using namespace std;
#define maxn 200005
#define maxm 1000005
#define int long long
int n,m,a[maxn],c[maxm],sum1,sum2,ans,cnt;
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<n;i++){
        sum2+=a[i];
        sum2%=m;
        c[sum2]++;
    }
    ans+=c[0];
    for(int i=2;i<=n;i++){
        sum2+=a[(i+n-2)%n?(i+n-2)%n:n];
        sum2%=m;
        c[sum2]++;
        sum1+=a[i-1];
        sum1%=m;
        c[sum1]--;
        cnt+=a[i-1];
        cnt%=m;
        ans+=c[cnt];
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：__Allen_123__ (赞：0)

### 题意简述

给定圆上 $n$ 个点，其中如果从第 $i$ 个点沿顺时针方向在圆上走，走 $a_i$ 步可以到达第 $i+1$ 个点（第 $n+1$ 个点即第 $1$ 个点）。求出满足以下条件的点对 $(a,b)$ 的数量：

- 从第 $a$ 个点开始在圆上沿顺时针方向走到第 $b$ 个点的距离是 $m$ 的倍数。

### 题目分析

此题中，我们可以使用前缀和思想，记从第 $1$ 个点到第 $i$ 个点的距离对 $m$ 取模的值为 $s_i$。那么，如果 $s_x=s_y$，则在点 $x$ 和点 $y$ 之间行走的距离就为 $m$ 的倍数，使用一个桶维护满足 $s_i=0\sim (n-1)$ 的对应的数量，枚举到每一个点时把桶内对应值加入答案，再修改桶的值（使对应桶的大小 $+1$）即可。

但是此题是圆上问题，我们考虑破环为链。我们可以复制一次原序列放在原序列末尾，并在复制后的序列上进行枚举。此时桶的值也要进行相应的修改，由于 $(a,b)$ 和 $(a+n,b+n)(1\le a,b\le n)$ 所对应的是相同的点对，所以我们只需要在枚举前 $n$ 个点时把 $s_i$ 加入桶即可。同时多绕一圈（如点对 $(a,b)(1\le a\le n,a+n\le b\le 2n)$）也是不可行的，所以使用一个队列维护当前可以走到这个点的所有点，一个点移出队列时对应的桶 $-1$ 即可。

[AC 记录](https://atcoder.jp/contests/abc367/submissions/56798054)。

---

## 作者：postpone (赞：0)

假设以 $\text{pre}_i$ 表示 $i$ 点的前缀和，容易想到，从 $l$ 走到 $r + 1$ 符合题意，当且仅当 $\text{pre}_r - \text{pre}_{l - 1}\equiv0\pmod M$。转换一下得 $
\text{pre}_r \equiv \text{pre}_{l - 1}\pmod M $。

先预处理出所有前缀和对 $M$ 的模。接着从 $1$ 到 $N$，枚举每一个点 $i$ 在前 $i$ 个点中的贡献，分为 $i$ 作起点和终点两种情况，这样加起来即为结果（可用归纳法证明）。

如何分类讨论：如第一段所示，作为终点时，只需要找前 $i$ 个点中（预处理后的）前缀和与当前 $\text{pre}_{i - 1}$ 相同的个数；作为起点，则仅需考虑它直接走到底再回到第一个点走过来的情况（因为只考虑前 $i$ 个点，不考虑 $(i, N]$ 中的点）。

复杂度 $O(N)$，代码如下。

`pre` 数组表示前缀和，下标从 $1$ 到 $N$。遍历时从 $0$ 到 $N - 1$，实质上就是从 $1$ 到 $N$ 的点的情况，因为题意中 $A_i$ 表示从 $i$ 走到 $i + 1$ 的代价。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] %= m;
    }

    vector<int> pre(n + 1);
    for (int i = 0; i < n; i++) {
        pre[i + 1] = (pre[i] + a[i]) % m;
    }

    vector<int> cnt(m);
    ll ans = 0;
    
    for (int i = 0; i < n; i++) {
        ans += cnt[(pre[i] - pre.back() + m) % m];
        ans += cnt[pre[i]];
        cnt[pre[i]]++;
    }

    cout << ans << endl;

    return 0;
}
```

---

## 作者：吴思诚 (赞：0)

> 闲话：赛时切 D 花了 78min，差点比赛结束前都没写完，鉴定为思路对应的代码太难写，输麻了，虽然 rank 3000+ 只掉了 39。

切入正题：首先如果只是求从 $1$ 出发，就是求路径的前缀和，然后看为 $0$ 的个数。（不算 $1$ 本身，共 $n-1$ 个）

**以下计算均在模意义下。**

但是他要求的是从 $1\sim n$ 每个点出发的答案，如果都这样做就 $O(n^2)$。

可以发现从 $1$ 到 $2$，$2\sim n$ 的距离都变近了相同的值（记为 $\Delta$），可以考虑集体减少记录在 $\Delta$ 中，所以不变；而 $2$ 对应的前缀和被删去了，加入了 $1$（可直接计算，一整圈的长度减去，由于有集体减少，它需要增加 $\Delta$ 的距离）

于是我们只需要记录绕一整圈的距离、一个 $\Delta$，处理到 $i$ 时，先去除 $i$ 对应的前缀和，新增一个 $i-1$ 的距离到统计数组中，每次统计 $cnt_{\Delta}$ 即可。

代码链接：https://atcoder.jp/contests/abc367/submissions/56857599

---

## 作者：ma_niu_bi (赞：0)

### 题意

一个湖周围有 $N$ 个休息区。  

从休息区 $i$ 顺时针走到休息区 $i+1$ 需要 $A_i$ 步，其中休息区 $N+1$ 指的是休息区 $1$。

从休息区 $s$ 顺时针走到休息区 $t(s \ne t)$ 所需的最小步数是 $M$ 的倍数。

求 $(s,t)$ 的可能对数。

### 思路

容易想到把原序列复制一遍破环成链。

把原 $A$ 数组做一遍前缀和，得到 $S$。

$s$ 到 $t$ 的距离为 $S_t-S_s$，其中 $s < t < s + n$。

若 $t \ge s + n$ 相当于绕了整个湖一圈，不符合题意。

原问题转化为了有多少对 $(i,j)$ 满足 $(i<j<i+n)$ 且 $S_j-S_i \equiv 0\pmod{M}$。

转化一下即 $S_j \equiv S_i \pmod{M}$。

使用一个桶维护 $S_i$ 对 $M$ 取余的结果。

倒序枚举 $i$，把 $S_{i+n}$ 从桶中删除，在桶里查询有多少个 $j$ 满足条件，并把 $S_i$ 加入桶中。

预处理时把 $S_{n+1}$ 到 $S_{2n}$ 都加入桶中。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
int n, m, a[N], c[N];
ll ans;
void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i ++) 
        cin >> a[i + 1], a[i + n + 1] = a[i + 1],
        a[i + 1] %= m, a[i + n + 1] %= m;
    for (int i = 1; i <= 2 * n; i ++) a[i] += a[i - 1], a[i] %= m;
    for (int i = n + 1; i <= 2 * n; i ++) c[a[i]] ++;
    for (int i = n; i >= 1; i --) {
        c[a[i + n]] --;
        ans += c[a[i]];
        c[a[i]] ++;
    }
    cout << ans << "\n";
}
signed main() {
    int T = 1;
    // cin >> T;
    while (T --) solve();
    return 0;
}
```

---

## 作者：jiangjiangQwQ (赞：0)

### 题目大意
有 $n$ 个小镇，第 $i$ 个小镇到第 $i+1$ 个小镇的距离为 $a_i$，当然 $a_n$ 表示的是第 $n$ 个小镇到第 $1$ 个小镇的距离，现在要你求满足两个城镇之间的**距离是 $m$ 的倍数**的数量，即令 $x$ 和 $y$ 之间的之间距离为 $dist$，要求 $m\mid dist$，答案就是这样的 $x$ 和 $y$ 的数量。
### Part 1
观察样例我们可以发现这 $n$ 个小镇构成一个简单环，我们先考虑满足条件下 $x\leq y$ 的数量，即 $m \mid s_x-s_{y-1}$，然后我们就可以维护一个前缀和数组，同时记录每一个前缀和模 $m$ 的个数，查询时累加当前前缀和对应的计数器中的值就好了，那么这是什么个原理呢？因为根据原式可知 $s_x \equiv s_{y-1} \pmod m$，所以对每个前缀和模 $m$ 的个数各自维护一个计数器。
### Part 2
继续思考可以发现答案中还有可能包括经过 $n$ 再到达在自己前面的小镇的距离也是满足条件的，根据正难则反，发现这样的距离相当于绕一圈的距离减去起点和终点之间的直线距离，令绕一圈的距离为 $res$，根据条件式又可得 $m \mid res-(s_x-s_{y-1})$，像上文所述统计一下满足条件的前缀数量就行了。
### 代码
```cpp
cin >> n >> m;
for (int i = 1; i <= n; i++) cin >> a[i], sum[i] = sum[i - 1] + a[i - 1];
int dist = 0;
for (int i = 1; i <= n; i++) dist += a[i];
dist %= m;
for (int i = 1; i <= n; i++) {
	ans += cnt[sum[i] % m] + cnt[((sum[i] % m - dist) % m + m) % m];
	cnt[sum[i] % m]++;
}
```

---

## 作者：Alcl000000 (赞：0)

题意：给你一个环，求有多少对点 $(u,v)$ 满足从 $u$ 顺时针到 $v$ 的距离为 $m$ 的倍数。

为方便描述，记 $dis_{u,v}$ 表示从 $u$ 顺时针到 $u$ 的距离，$f_u$ 表示从 $u$ 顺时针到 $1$ 的距离，$g_u$ 表示从 $1$ 顺时针到 $u$ 的距离。

我们考虑当确定 $i$ 时，有多少个 $j$ 使得 $dis_{j,i} \bmod m =0$ , 当 $j\in[1,i)$ 时，$dis_{j,i}=g_j-g_i$。当 $j\in(i,n]$ 时，$dis_{j,i}=g_i+f_j$，所以我们可以枚举 $i$，对于 $j\in[1,i)$ 开一个桶，对于 $j\in(i,n]$ 开一个桶，每当 $i+1$ 时，对于桶中对应位置更改即可。时间复杂度 $O(n)$，空间复杂度 $O(m)$。

[AC 记录 / 代码](https://atcoder.jp/contests/abc367/submissions/56817538)

---

## 作者：Lotus_Land (赞：0)

### 题意

一个湖周围有 $N$ 个休息区。

这些休息区按顺时针顺序编号为 $1$、$2$、......、$N$。

从休息区 $i$ 顺时针走到休息区 $i+1$ 需要 $A_i$ 步（其中休息区 $N+1$ 指的是休息区 $1$）。

从休息区 $s$ 顺时针走到休息区 $t$（$s \neq t$）所需的最小步数是 $M$ 的倍数。

求 $(s,t)$ 的可能对数。

### 分析

P3131 的加强版。

先考虑如果 $1$ 到 $N$ 是按一条链排列的话要怎么做。从 $l$ 走到 $r$（$1\leq l<r\leq N$）的最小花费为 $\sum\limits_{i=l}^{r-1}A_i$。这个可以用前缀和优化。设 $S_i=\sum\limits_{j=1}^{i}A_j$，则上述花费为 $S_{r-1}-S_{l-1}$。（注意这一题与 P3131 不同的是 $A_i$ 表示的是从 $i$ 走到 $i+1$ 的步数，所以花费不是 $\sum\limits_{i=l}^{r}A_i$。）

要使花费为 $M$ 的倍数，即 $S_{r-1}-S_{l-1}\equiv 0\pmod{M}$，要保证 $S_{r-1}\bmod M=S_{l-1}\bmod M$。那么就先把每个 $S_i\bmod M$ 都算出来，把值相同的下标都用 vector 存在一起，枚举 $r-1$，二分找到满足条件的 $l-1$ 的个数再全部加起来就行了。时间复杂度 $O(N\log N)$。注意枚举的边界条件：$r-1\in[1,N-1],l-1\in[0,r-1]$。

题目中有环，考虑断环为链。此时 $(s,t)$ 有两种情况：$s<t$ 和 $s>t$。$s<t$ 参照 $1$ 到 $N$ 为一条链的情况进行处理。$s>t$ 则考虑在断开的链上按照 $(s,t+n)$ 处理。

剩下的还是注意边界条件：$(s,t)$ 满足 $1\leq s,t\leq N$，且路径必定不到一圈，处理 $(s,t+n)$ 时枚举的 $r-1$ 和 $l-1$ 要满足 $r-1 \in[N,2\times N-1],l-1\in[r-N,N-1]$，避免 $s<t$ 的情况重复计算。

```cpp
#include<bits/stdc++.h>
#define lc(p) ((p)*2)
#define rc(p) ((p)*2+1)
#define mkpr make_pair
#define LL long long
#define N 500005
using namespace std;
inline LL read() {
	char ch=getchar();
	LL x=0;
	bool t=0;
	while(ch<'0'||ch>'9')   t|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
	return t?-x:x;
}
int n;
LL ans,m,a[N],sum[N];
vector<int>G[1000006];
int main() {
	cin>>n>>m;
	for(int i=1; i<=n; i++)cin>>a[i],a[i+n]=a[i];
	for(int i=0;i<m;i++)G[i].push_back(-1);
	G[0].push_back(0);
	for(int i=1; i<=n*2; i++) {
		sum[i]=sum[i-1]+a[i];
		sum[i]%=m;
	//	cout<<sum[i]<<' ';
		G[sum[i]].push_back(i);
	}
	cout<<endl;
	int p,q;
	for(int i=1; i<=n*2-1; i++) {
		if(i<n) {
			p=upper_bound(G[sum[i]].begin(),G[sum[i]].end(),i-1)-G[sum[i]].begin()-1;
		//	cout<<p<<endl;
			ans+=p;
		} else {
			p=upper_bound(G[sum[i]].begin(),G[sum[i]].end(),n-1)-G[sum[i]].begin()-1;
			q=lower_bound(G[sum[i]].begin(),G[sum[i]].end(),i-n+1)-G[sum[i]].begin();
		//	cout<<p<<' '<<q<<endl;
			ans+=p-q+1;
		//	cout<<p-q+1<<endl;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：PineappleSummer (赞：0)

[[ABC367D] Pedometer](https://www.luogu.com.cn/problem/AT_abc367_d)

赛时第一眼题目看错，寄完了。

我们知道，如果前缀和 $sum_r$ 与前缀和 $sum_{l-1}$ 对于 $m$ 同余，则 $\sum\limits_{i=l}^ra_i$ 是 $m$ 的倍数。

考虑破环为链，将数组的 $n+1\sim 2n$ 设为原数组的 $1\sim n$ 项。

对数组 $1\sim 2n$ 做一遍前缀和，然后将第 $2\sim n$ 项的前缀和对 $m$ 取模后加到统计数组里。

从 $n+1\sim 2n$ 循环 $i$，当前统计数组中存的是 $sum_{i-n+1}\sim sum_{i-1}$。统计数组中 $sum_i\bmod m$ 的个数，并调整数组中存的前缀和的区间。

时间复杂度 $\mathcal O(n)$。

```cpp
cin >> n >> m;
for (int i = 1; i <= n; i++) cin >> a[i], a[i + n] = a[i];
for (int i = 1; i <= n * 2; i++) sum[i] = sum[i - 1] + a[i];
for (int i = 2; i <= n; i++) cnt[sum[i] % m] ++;
for (int i = n + 1; i <= n * 2; i++) {
   res += cnt[sum[i] % m];
   cnt[sum[i - n + 1] % m] --;
   cnt[sum[i] % m] ++;
}
cout << res;
```

---

## 作者：liruixiong0101 (赞：0)

# D - Pedometer
## 题意：
现有一个圆环，圆环上有 $n$（$2\le n\le 2\times 10^5$） 个点，第 $i$ 个点到第 $i+1$ 个点的距离为 $a_i$（我们视第 $n+1$ 个点是第 $1$ 个点），请求出有序数对 $(s,t)$ 满足以下要求的个数：
- 从第 $s$ 个点顺时针走到 $t$ 的距离为 $m$（$1\le m\le 10^6$） 的倍数。
- $s\neq t$。

## 思路：
设 $S_i = \sum_{j=1}^{i - 1} a_j$，那么从 $s$ 顺时针走到 $t$（$s<t$） 的距离为 $S_t-S_s$，那么从 $t$ 顺时针走到 $s$ 的距离为 $S_{n+1}-(S_t-S_s)$。

考虑前者：
$$
S_t-S_s\equiv 0 \pmod m \\
S_t\equiv S_s \pmod m
$$
我们可以把 $S_i\bmod m$（$1\le i\le n$）存入桶中，然后用组合数计算相同 $S$ 的数量。

考虑后者：
$$
S_{n+1}-(S_t-S_s)\equiv 0 \pmod m \\
S_t\equiv S_{n+1}+S_t \pmod m
$$
我们同样可以把 $S_i\bmod m$（$1\le i\le n$）存入桶中，但是在这里我们需要钦定 $s<t$ 否则 $S_t-S_s$ 就会小于 $0$，所以我们可以在遍历 $S_i$ 的同时计算数量，然后再将 $S_i\bmod m$ 存入桶中。

## 代码：
<https://atcoder.jp/contests/abc367/submissions/56809383>

---

## 作者：JXR_Kalcium (赞：0)

## 题目大意

给定 $N$ 个点，第 $i$ 个点到第 $i+1$ 点有一条有向边，权值为 $A_i$，特别地，点 $N$ 和点 $1$ 有一条权值为 $A_N$ 的有向边。现在对于每个 $1\le s,t\le N~(s\neq t)$，求出满足它们的最短距离为 $M$ 的倍数的 $(s,t)$ 对数。

## 解题思路

首先暴力的方法不难想到，因为这是一个环，先把 $A_{1\sim N}$ 复制一份到 $A_{N+1\sim N\times 2}$，此时 $(s,t)$ 的最短距离应为

$$
dis_{(s,t)}=\left\{\begin{aligned}&\sum_{i=s}^{t-1} A_i~(s<t)\\&\sum_{i=s}^{t+N-1} A_i~(s>t)\end{aligned}\right.
$$

然后暴力累加最短距离即可，时间复杂度 $O(n^2)$。其实正解非常简单，首先用**前缀和**处理上面累加的部分，$sum_i$ 表示 $\sum_{k=1}^{i} A_k$，于是最短距离是 $M$ 的倍数也就意味着

$$
(sum_{t-1}-sum_{s-1})\bmod M=0~(1\le s<t\le N\times 2,s\le n,t-s<n)
$$

拆括号得

$$
sum_{s-1}\equiv sum_{t-1}~(\bmod~M)
$$

为了方便，把减一去掉

$$
sum_s\equiv sum_t~(\bmod~M,0\le s<t<N\times 2,s<n,t-s<n)
$$

所以我们只需要对每个前缀和都去 $\bmod~M$，然后用一个桶 $P$ 记录个数，$P_{sum_i}$ 就表示在 $i<j\le i+N-1$ 这个范围内有多少 $sum_j=sum_i$。先预处理 $s=0$ 的情况（就是对每个 $1\le i<N$ 都去让 $P_{sum_i}+1$），接下来每当一个数 $1\le i<N$ 加进来，就把 $P_{sum_i}-1$（因为统计个数的时候不能把自己加进去），并且 $P_{sum_{i+N-1}}+1$（就类似于**滑动窗口**），然后让答案累加 $P_{sum_i}$ 就可以了。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
using namespace std;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x, endl;
#endif

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    static ll sta[41]; ll top=0;
    if(x<0) putchar('-'), x=-x;
    do sta[top++]=x%10, x/=10; while(x);
    while(top) putchar(sta[--top]+48);
}

ll n,m,a[400001],sum[400001],bz[1000001],ans;

int main()
{
    n=read(); m=read();
    for(int i=1; i<=n; ++i) a[i]=read(), a[n+i]=a[i];
    for(int i=1; i<n<<1; ++i) sum[i]=(sum[i-1]+a[i])%m;

    for(int i=1; i<n; ++i)
    {
        ++bz[sum[i]];
        if(sum[0]==sum[i]) ++ans;
    }

    for(int i=1; i<n; ++i)
    {
        --bz[sum[i]]; ++bz[sum[i+n-1]];
        ans+=bz[sum[i]];
    }

    write(ans);
    return 0;
}
```

---

