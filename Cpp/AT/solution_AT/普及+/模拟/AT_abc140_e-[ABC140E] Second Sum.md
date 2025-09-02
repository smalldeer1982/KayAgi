# [ABC140E] Second Sum

## 题目描述

### 题面描述

给出一个 $1 \sim n$ 的排列（即 $1 \sim n$ 每个数只出现一次）$P$。

给出一对 $[L, R]$，设 $X_{L, R}$ 是 $P_L \sim P_R$ 中的次大值（第二大值）。

求 $\sum_{L = 1}^{N - 1} \sum_{R = L + 1}^{N} X_{L, R}$。

注：即求所有 $[L, R]$ 区间的次大值之和。

## 说明/提示

#### 样例 1 解释

$X_{1, 2} = 2, X_{1, 3} = 2, X_{2, 3} = 1$，次大值和为 $2 + 2 + 1 = 5$。

#### 数据约束

对于 $100\%$ 的数据，保证：
- $2 \le N \le 10^5$
- $1 \le P_i \le N$
- $P_i \ne P_j (i \ne j)$
- $1 \le L < R \le N$
- 所有输入均为整数。

---

署名：[George222](https://www.luogu.com.cn/user/848194)

## 样例 #1

### 输入

```
3
2 3 1```

### 输出

```
5```

## 样例 #2

### 输入

```
5
1 2 3 4 5```

### 输出

```
30```

## 样例 #3

### 输入

```
8
8 2 7 3 4 5 6 1```

### 输出

```
136```

# 题解

## 作者：Acfboy (赞：18)

提供两种做法，一种是依赖于单调栈和 ST 表的 $\mathcal O(n \lg n)$ 做法，思维难度较低；还有一个绝妙的做法，根本想不到，但不需要任何现成的 算法/数据结构， 时间复杂度 $\mathcal O(n)$。

### 做法一

分别考虑每一个数在多少个区间内成为了次大值。

最大值在前面时，能当最大值的只有离当前这一个（位置记为 $r$）最近的比他大的，当取到这个最大值（位置记为 $l$）时，区间的最大和次大已确定，只需要把区间 $[l, r]$ 取进去，$l$ 左边和 $r$ 右边比他俩都小的去不去都无所谓。设 $l$ 左边第一个比 $a_r$ 大的为 $l'$, $r$ 右边第一个比 $a_r$ 大的是 $r'$, 则 $a_r$ 对答案的贡献是 $(l - l') \times (r' - r)$ 。

实际做的时候还要再跑一遍最大值在后面的。

用单调栈可以方便地维护 $l$ ，那么如何维护 $l'$ 呢？ 可以使用 ST 表实现，类似倍增求 LCA 那样能跳的救跳，即若这一段最大值还是小于 $a_r$ 就跳。

代码：

```cpp
#include <cstdio>
#include <stack>
#include <algorithm>
#define int long long
const int N = 100005;
int n, pre[N], suc[N], stL[N][20], stR[N][20], a[N], ans;
std::stack<int> st;
int findL(int now, int m) {
	for(int i =  17; i >= 0; i--) 
		if(stL[now][i] < m && now - (1 << i) >= 1) now = now - (1 << i);
	return now;
}
int findR(int now, int m) {
	for(int i =  17; i >= 0; i--) 
		if(stR[now][i] < m && now + (1 << i) <= n) now = now + (1 << i);
	return now;
}
signed main() {	
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++) stL[i][0] = a[i-1], stR[i][0] = a[i+1];
	for(int j = 1; j <= 17; j++)
		for(int i = 1; i <= n; i++)
			if(i - (1 << j) >= 1) stL[i][j] = std::max(stL[i][j-1], stL[i - (1 << (j-1))][j-1]);
	for(int j = 1; j <= 17; j++)
		for(int i = n; i >= 1; i--)
			if(i + (1 << j) <= n) stR[i][j] = std::max(stR[i][j-1], stR[i + (1 << (j-1))][j-1]);
	a[0] = n+1, a[n+1] = n+1;
	st.push(0);
	for(int i = 1; i <= n+1; i++) {
		while(!st.empty() && a[st.top()] < a[i]) {
			suc[st.top()] = i;
			st.pop();
		} 
		pre[i] = st.top();
		st.push(i);
	}
	for(int i = 1; i <= n; i++) {
		int lBer = pre[i], rBer = suc[i];
		int tmpl = findL(lBer, a[i]), tmpr = findR(rBer, a[i]);
		if(lBer >= 1) ans += (lBer - tmpl + 1) * (rBer - i) * a[i];
		if(rBer <= n) ans += (tmpr - rBer + 1) * (i - lBer) * a[i];
	}
	printf("%lld", ans);
	return 0;
}
```

[提交记录链接](https://www.luogu.com.cn/record/47982443)

### 做法二

来考虑如何优化做法一，或者你不会单调栈，也不会 ST 表怎么办？

做法一看上去似乎没有可以优化的地方了，但实际上线性的做法特别的简洁，让人体会到算法竞赛的魅力：

**换一种求解的顺序**

在原来的做法里，我们先统计第一个对答案的贡献，再统计第二个对答案的贡献，没有什么是现成的，一切都需要重新求解。

但如果我们从 $a_i$ 等于 $1$ 的位置开始求解呢？

这时候，其它所有的显然都比它大，不需要求解，而后面再求解的数显然都比这个要大，所以遇到这一个直接跳过就好了。


细品一下这一段话，我们其实是利用了原先求解的结果，去掉了不必要的求解。因为原先做法中，用 ST 表就是为了跳过所有比当前这个小的，但用从小到大的求解顺序，只需要把原来求到过的都跳过就行了，不需要重新求解，所以降低了时间复杂度。

每次更新时，比当前更小的都被跳过了，直接调用没跳过的就是大于当前的，所以这样是对的。

具体的实现使用双向链表 $L_i$ 表示这个去掉所有跳过的左边是什么，$R_i$ 表示去掉跳过的 $i$ 的右边是什么。最后更新一下，跳过当前这一个就可以了。

代码：

```cpp
#include <cstdio>
#define int long long
const int N = 100005;
int L[N], R[N], x, map[N], n;
signed main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &x);
        map[x] = i;
        L[i] = i - 1, R[i] = i + 1;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int l = L[map[i]], r = R[map[i]];
        if (l >= 1) ans += i * (l - L[l]) * (r - map[i]);
        if (r <= n) ans += i * (R[r] - r) * (map[i] - l);
        L[r] = l, R[l] = r;
    }
    printf("%lld", ans);
    return 0;
}
```

仅 $20$ 行，从各个方面吊打原来的 $60$ 行做法，妙不妙？



---

## 作者：SunsetVoice (赞：5)

请注意，严格来说下文复杂度为 $O(n^2)$ 不是正解，但复杂度绝对跑不满，再加上此题数据只有 $10^5$，从而保证了可过。

[通过记录](https://atcoder.jp/contests/abc140/submissions/56964482)，可以看到最高只有 26ms，再加上可以使用分块对其优化至 $O(n\sqrt n)$，该做法可过。

笔者的老师将其出到了模拟赛里，于是笔者只能被迫营业。

考虑每一个 $a_i$ 的贡献 $g_i$。

打一个表，可以发现一个位置能成为次大，当且仅当其所在区间内有恰好一个数比其大。

则找到在其左边出现的第一个比其大的数（记做 $l_i$），其右边出现的第一个比其大的数（记做 $r_i$）。这两步可以使用单调栈 $O(n)$ 解决（头做一遍尾做一遍）。注意边界时需要特判。

接下来，需要统计超出 $l_i,r_i$ 的部分。这部分要求找到比 $a_i$ 大的第二个字符。（左右都要）。

有一个暴力，即直接从 $l_i,r_i$ 向边界跑，遇到第一个大的就返回，但问题在于这样理论上能卡到 $n^2$，因此需要优化。

使用分块记录每个区间的最大值，如果最大值还比 $a_i$ 小就没必要搜了。

这样，记 $4$ 个值分别为 $ll_i,lr_i,rl_i,rr_i$，$g_i=(rr-rl)\times (i-lr)+(lr-ll)\times (rl-i)$。

考场上没来得及写分块，但是跑的仍然飞快。

复杂度能做到 $O(n\sqrt n)$，但 $n^2$ 过了，因此不写分块代码了，有能实现的记得撅我。

---

## 作者：George222 (赞：5)

思路：双向链表+组合数学（不过你要用单调栈也没人拦着你）

我们现在先抛开题面，先换个思路。

我们现在求：这个数**能做多少个区间的次大值**。

我们现在设 $l1, l2, r1, r2$ 分别为左边第一个比这个数大的 id，第二个比这个数大的 id，右边第一个比这个数大的 id，第二个比这个数大的 id。竟然是次大值，所以我们左边和右边能且仅能包含一个比这个数大的。

我们现在求区间数即为：
- 左边取一个比他大的数的个数 $\times$ 右边取不比他大的数的个数。
- 右边取一个比他大的数的个数 $\times$ 左边取不比他大的数的个数。

即为：
- `(l1 - l2) * (r1 - a[i].id)`
- `(r2 - r1) * (a[i].id - l1)`

那么**如何获得 $l1, l2, r1, r2$ 呢**？

如果我能直接从当前这个数找到这四个数是最好的，就是说像这样的一个链表：

![](https://cdn.luogu.com.cn/upload/image_hosting/pvdbjg2k.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

要实现这样我们可以存好 id 后排序，从小到大处理，根据链表的删除机制，到某个数时，一定会成为类似上图的样子。

代码：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll n;
struct Node
{
    ll x;
    ll id;
} a[100005];
ll pre[100005], nxt[100005];
ll ans = 0;
bool cmp(Node a, Node b) {
	return a.x < b.x;
}
void del(ll id)
{
	nxt[pre[id]] = nxt[id];
	pre[nxt[id]] = pre[id];
	return ;
}

int main()
{
    cin >> n;
    for (ll i = 1; i <= n; i++)
    {
    	cin >> a[i].x;
    	a[i].id = i;
    	pre[i] = i - 1;
    	nxt[i] = i + 1;
	}
	nxt[0] = 1;
	pre[n + 1] = n;
	sort(a + 1, a + n + 1, cmp);
	for (ll i = 1; i <= n; i++)
	{
		ll l1, l2, r1, r2;
		// left
		l1 = pre[a[i].id];
		if (l1) l2 = pre[l1];
		else l2 = -1;
		// right
		r1 = nxt[a[i].id];
		if (r1 != n + 1) r2 = nxt[r1];
		else r2 = -1;
		// solve
		if (!(l2 == -1))
			ans += (l1 - l2) * (r1 - a[i].id) * a[i].x;
		if (!(r2 == -1))
			ans += (r2 - r1) * (a[i].id - l1) * a[i].x;
		del(a[i].id);
	}
	cout << ans << "\n";
	return 0;
}
```

---

## 作者：PineappleSummer (赞：4)

upd 2024-07-11：感谢 [endswitch](https://www.luogu.com.cn/user/773915) 指出一处笔误，已经修改。

**强烈推荐笔者的文章[浅谈 ST 表与二分的结合](https://www.luogu.com.cn/article/ubzp0klq)，这道题是里面的例题！**

题意：给定一个长度为 $n$ 的排列，对于 $l<r$，定义 $f(l,r)$ 为区间 $[l,r]$ 中的第二大数，求 $\displaystyle\ \sum_{l=1}^{n-1}\ \sum_{r=l+1}^{n}f(l,r)$。

考虑一个数 $a_x (l\le x\le r)$ 在区间 $[l,r]$ 中是第二大数有两种可能：
- $a_x$ 在区间 $[l,x]$ 中是第一大数，在区间 $[x,r]$ 中是第二大数。
- $a_x$ 在区间 $[l,x]$ 中是第二大数，在区间 $[x,r]$ 中是第一大数。

那就分两种情况统计，再累加贡献。

具体地，对于数 $a_i$，可以找到最大的区间 $[l,r]$ 使得 $a_i$ 是 $[l,r]$ 区间中最大的数。再找出最大的区间 $[L,i]$ 使得 $a_i$ 是该区间中第二大的数，和最大的区间 $[i,R]$ 使得 $a_i$ 是该区间中第二大的数。

那么 $a_i$ 对于答案的贡献即为 $a_i\times(l-L)\times (r-i+1)+a_i\times (i-l+1)\times (R-r)$。

那么难点在于如何找到 $l,r,L,R$。

首先 $[l,r]$ 可以简单地从 $i$ 往两边二分找到，可以参照 AGC005B 的方法。根据定义，$a_{l-1} > a_i$，所以 $L$ 可以通过在 $[1,l-2]$ 上二分得到。具体地，需要找到 $[1,l-2]$ 这个区间中从右边数第一个大于 $a_i$ 的数。设 $ask(x,y)$ 为 $[x,y]$ 这个区间的最大值（$x\le y$），考虑从 $l-2$ 往左边二分查找。如果 $ask(mid,l-2)<a_i$，就让 $r=mid$，否则让 $l=mid+1$。

$R$ 是同理的。

区间最大值由 ST 表维护即可，时间复杂度 $O(n\log n)$。

代码中细节还是挺多的，调不过的可以对比一下。
```cpp
// 为了看着方便，在每一次二分后空了一行
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long LL;
const int N = 1e6 + 10;
int n, f[N][22], ans;
int ask (int l, int r) {
	int s = __lg (r - l + 1);
	return max (f[l][s], f[r - (1 << s) + 1][s]);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> f[i][0];
	for (int j = 1; j <= 19; j++)
		for (int i = 1; i + (1 << j) - 1 <= n; i++)
			f[i][j] = max (f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
	for (int i = 1; i <= n; i++) {
		int l = 1, r = i, L, R, l1, r1;
		
		while (l < r) {
			int mid = (l + r) >> 1;
			if (ask (mid, i) == f[i][0]) r = mid;
			else l = mid + 1;
		}
		l1 = l;
		
		l = 1, r = max (1ll, l1 - 2);
		while (l < r) {
			int mid = (l + r) >> 1;
			if (ask (mid, max (mid, l1 - 2)) < f[i][0]) r = mid;
			else l = mid + 1;
		}
		if (f[r][0] > f[i][0] && f[r + 1][0] > f[i][0]) L = r + 1;
		else L = r;
		
		l = i, r = n;
		while (l < r) {
			int mid = (l + r + 1) >> 1;
			if (ask (i, mid) == f[i][0]) l = mid;
			else r = mid - 1;
		}
		r1 = l;
		R = l;
		ans += f[i][0] * (l1 - L) * (R - i + 1);
      // 左边第二大，右边第一大
     
		l = min (n, r1 + 2), r = n;
		while (l < r) {
			int mid = (l + r + 1) >> 1;
			if (ask (min (mid, r1 + 2), mid) < f[i][0]) l = mid;
			else r = mid - 1;
		}
		if (f[l][0] > f[i][0] && f[l - 1][0] > f[i][0]) R = l - 1;
		else R = l;
		ans += f[i][0] * (i - l1 + 1) * (R - r1);
      // 左边第一大，右边第二大
	}
	cout << ans;
	return 0;
}
```

再次推荐：[浅谈 ST 表与二分的结合](https://www.luogu.com.cn/article/ubzp0klq)，有好的建议欢迎提出，谢谢！

---

## 作者：TH911 (赞：2)

声明：这并不是一篇算法独特的题解，相关方法[此篇题解](https://www.luogu.com.cn/article/rr5wubeo)已有，但**绝对更为详细**。
***
[**广告：个人Blog同步链接。**](https://cfyy.us.kg/2024/11/16/2/)

## 题意分析

当 $a_i$ 对答案产生贡献时，当且仅当存在区间 $[l,r]$ 满足 $i\in[l,r]$ 且 $a_i$ 是 $[l,r]$ 的次大值。

由此我们开始做题。

### 计算合法区间数

显然，**当且仅当**区间中**有且仅有**一个数大于 $a_i$ 时，答案会增加 $a_i$。

那么我们考虑算出，对于每一个 $a_i$，会造成多少个 $a_i$ 的贡献。

如果我们找出了 $a_i$ 左右两边第一个、第二个大于 $a_i$ 的数，**从左至右**分别记作 $a_{dl_i},a_{l_i},a_{r_i},a_{dr_i}$（满足 $dl_i<l_i<i<r_i<dr_i$ 且 $ a_{dl_i},a_{l_i},a_{r_i},a_{dr_i}>a_i$），那么这四个数中肯定只能有**一个**和 $a_i$ 处于同一个区间（**否则 $a_i$ 不为次大值**）。

那么**我们所需要的会对答案造成贡献的区间就不会包含 $a_{dl_i}$ 和 $a_{dr_i}$**（因为一旦包含 $a_{dl_i}$，就一定会包含 $d_{l_i}$，$r_i,dr_i$ 同理）。

既然如此，令合法区间为 $[L,R]$，合法情况就只有两种：

* $L\in[dl_i+1,l_i],R\in[i,r_i-1]$，区间包含了 $l_i$，记作 $[L_1,R_1]$。
* $L\in[l_i+1,i],R\in[r_i,dr_i-1]$，区间包含了 $r_i$，记作 $[L_2,R_2]$。

图示：

![](https://cdn.luogu.com.cn/upload/image_hosting/ktoi611a.png)

当 $L\in[dl_i+1,l_i],R\in[i,r_i-1]$ 时，则合法区间数为 $\left(l_i-\left(dl_i+1\right)+1\right)\left(\left(r_i-1\right)-i+1\right)=(l_i-dl_i)(r_i-i)$。

同样地，当 $L\in[l_i+1,i],R\in[r_i,dr_i-1]$ 时，合法区间数为 $\left(i-l_i\right)\left(dr_i-r_i\right)$。

那么 $a_i$ 对答案的总贡献就是 $a_i\times\left[\left(l_i-dl_i\right)\left(r_i-i\right)+\left(i-l_i\right)\left(dr_i-r_i\right)\right]$，可以 $\mathcal O\left(1\right)$ 求解。

则最终答案为 $\large \sum\limits_{i=1}^n{a_i\times\left[\left(l_i-dl_i\right)\left(r_i-i\right)+\left(i-l_i\right)\left(dr_i-r_i\right)\right]}$（下标从 $1$ 开始）。

但这时我们需要注意的是，这四个数**都有可能不会存在**，那么初值就变得十分重要，甚至会**影响最终答案的正确性**。~~当然，你不嫌麻烦你特判也行。~~

* 如果你的下标从 $1$ 开始：

  ```cpp
  for(int i=1;i<=n;i++){
      l[i]=dl[i]=0;
      r[i]=dr[i]=n+1;
  }
  ```

* 如果你的下标从 $0$ 开始：

  ```cpp
  for(int i=0;i<n;i++){
      l[i]=dl[i]=-1;
      r[i]=dr[i]=n;
  }
  ```

（其实就是类似于“值域两端”）

解释一下为什么：（下标从 $1$ 开始，从 $0$ 开始和从 $1$ 开始差不多，不能理解可以手推或参见上图）

以 $l_i,dl_i$ 为例，$r_i,dr_i$ 同理可得。

首先，$l_i=dl_i=0$ 的好处就是选取区间时 $l_i+1=dl_i+1=1$（不存在的话）。

如果 $l_i$ 不存在，那么 $dl_i$ **绝对**不存在：$l_i=dl_i=1,l_i-dl_i=0$，上文中 $[L_1,R_1]$ 的区间因为要选取 $l_i$ 自然不存在，正确；对于 $[L_2,R_2]$，已经在右边选取了 $r_i$，$l_i$ 自然不会选取到，不影响答案。

如果 $l_i$ 存在，$dl_i$ 不存在：$[L_1,R_1]$ 选取了 $l_i$，则 $1\sim l_i$ 都可以选取，此时 $l_i-dl_i=l_i-0=l_i$，正确；对于 $[L_2,R_2]$，同样与 $l_i,dl_i$ 无关，不影响答案。

这样，我们便可以 $\mathcal O\left(n\right)$ 求出最终答案。

#### 如何计算四个数的位置

[如果你不知道 `set`](https://oi-wiki.org/lang/csl/associative-container/#set)

说了这么多，我们还是不知道如何求出 $dl_i,l_i,r_i,dr_i$。

事实上，我们仅仅需要**从大至小**向 `set` 中加入 $a_i$，然后利用前驱、后继节点来判断大小关系即可。

令 $p_i$ 表示 $a_i$ 的下标，那么按照 $a_i$ 值排序，使得 $\large a_{p_1}>a_{p_2}>a_{p_3}>\cdots>a_{p_n}$。

这时我们用 $i$ 遍历 $[1,n]$，每次在 `set` 中执行 `lower_bound(p[i])`（或者 `upper_bound(p[i])` 也行，因为 $p_i$ 不重复），找到第一个大于 $p_i$ 的下标 $p_x$。

那么 $p_x$ 在 $p_i$ 之前插入 `set`，代表 $a_{p_x}>a_{p_i}$，又有 $p_x>p_i$ 且 $p_x$ 最小，则 $p_x=r_{p_i}$。

而 $dr_{p_i}$ 也很简单，当 $p_x$ 不为 `set` 的最后一个元素（不然越界）时，找到 $p_x$ 的**后继节点**即可。由 `set` 的有序特性且 $p_i$ 不重复，$p_x$ 的后继节点就是**最小的大于 $p_x$ 的元素 $p_{x'}$**，$dr_{p_i}=p_{x'}$。

对于 $l_{p_i}$，其实就是 $p_{x}$ 的**前驱节点** $p_y$。**因为 `set` 内 $p_i$ 不重复、$p_x$ 最小且 $p_y<p_x,p_x>p_i$，有 $p_y<p_i$ 且 $p_y$ 最大。**

那么就有 $l_{p_i}=p_y$。和 $dr_{p_i}$ 同理，$dl_{p_i}$ 为 $p_y$ 的前驱节点 $p_{y'}$。

**注意判定越界**。

最后记得将 $p_i$ 插入 `set` 即可。

~~不会有人不会算前驱后继节点吧。~~

使用 `next()` 和 `prev()` 即可。

虽然说对迭代器进行自减运算、自加运算，或者进行数学运算后强制类型转换也行，但是确实没有这两个简单。

### 注意事项

* $dl_i,l_i,r_i,dr_i$ 的初始值。
* 开 `long long`。

## AC代码

```cpp
//#include<bits/stdc++.h>
#include<algorithm> 
#include<iostream>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<string>
#include<vector>
#include<cmath>
#include<ctime>
#include<deque>
#include<queue>
#include<stack>
#include<list>
#include<set> 
using namespace std;
typedef long long ll;
const int N=2e5;
ll n,a[N+1],p[N+1],l[N+1],dl[N+1],r[N+1],dr[N+1];
bool cmp(ll x,ll y){
	if(a[x]!=a[y])return a[x]>a[y];
	return x<y;
}
int main(){
	/*freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);*/
	
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++)scanf("%lld",a+i);
	for(ll i=1;i<=n;i++){
		p[i]=i;
		l[i]=dl[i]=0;
		r[i]=dr[i]=n+1;
	}sort(p+1,p+n+1,cmp);
	set<ll>s;
	for(ll i=1;i<=n;i++){
		auto pl=s.lower_bound(p[i]);
		if(pl!=s.end()){
			r[p[i]]=*pl;
			if(next(pl)!=s.end())dr[p[i]]=*next(pl);
		}if(pl!=s.begin()){
			pl--;
			l[p[i]]=*pl;
			if(pl!=s.begin())dl[p[i]]=*prev(pl);
		}s.insert(p[i]);
	}ll ans=0;
	for(ll i=1;i<=n;i++)ans+=a[i]*((l[i]-dl[i])*(r[i]-i)+(i-l[i])*(dr[i]-r[i]));
	printf("%lld\n",ans);
	
	/*fclose(stdin);
	fclose(stdout);*/
	return 0;
}
```

---

## 作者：cosf (赞：2)

看到这种类型的题，果断想到，我们可以枚举这个次大值。

具体而言，我们可以给下标 $p_i$ 排个序，满足 $a_{p_1} \gt a_{p_2} \gt \dots \gt a_{p_n}$。

那么，我们可以维护一个 `set`，在加 $a_{p_i}$ 的时候，我们可以找到比他大的数中，左边、右边第一个、第二个比它大的数，记为 $l_1, r_1, l_2, r_2$，那么，以 $a_{p_i}$ 为次大值的区间只有两种情况：

- 左端点在 $(l_2, l_1]$ 之间，右端点在 $[p_i, r_1)$ 之间。方案数为 $(l_1 - l_2)(r_1 - p_i)$。
- 左端点在 $(l_1, p_i]$ 之间，右端点在 $[r_1, r_2)$ 之间。方案数为 $(p_i - l_1)(r_2 - r_1)$。

这东西特别好算。时间复杂度 $O(n\log n)$。

```cpp
#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

using ll = long long;
using si = set<int>::iterator;

#define MAXN 100005

int n;

int a[MAXN], b[MAXN];

set<int> s;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        b[i] = i;
    }
    sort(b + 1, b + n + 1, [](int x, int y)
         { return a[x] > a[y]; });
    s.emplace(0);
    s.emplace(n + 1);
    ll res = 0;
    for (int i = 1; i <= n; i++)
    {
        si it = s.lower_bound(b[i]);
        if (it != --s.end())
        {
            res += 1ll * a[b[i]] * (b[i] - *(--si(it))) * (*(++si(it)) - *it);
        }
        it--;
        if (it != s.begin())
        {
            res += 1ll * a[b[i]] * (*it - *(--si(it))) * (*(++si(it)) - b[i]);
        }
        s.insert(b[i]);
    }
    cout << res << endl;
    return 0;
}
```

---

## 作者：wmrqwq (赞：1)

哎哎，太毒瘤，哎哎，太深刻。

# 题目链接

[AT_abc140_e [ABC140E] Second Sum](https://www.luogu.com.cn/problem/AT_abc140_e)

# 解题思路

考虑有以下基本性质：

在 $1 \sim n$ 的数列上，包含 $i (1 \le i \le n)$ 点的区间（端点为整数）个数为 $i \times (n - i + 1)$ 个。

因此此题我们可以使用拆贡献来计算。

具体的，设 $maxl$ 表示 $a_i$ 左边的第一个比 $a_i$ 大的数字编号，$maxll$ 表示 $a_{maxl}$ 左边的第一个比 $a_{maxl}$ 大的数字编号，$maxr$ 表示 $a_i$ 右边的第一个比 $a_i$ 大的数字编号，$maxrr$ 表示 $a_{maxr}$ 右边的第一个比 $a_{maxr}$ 大的数字编号，

以上定义均有若没有这样的数字则编号为 $-1$ 的性质。

然后有以下分讨：

- 若 $maxl = maxr = -1$，则方案数为 $0$。

- 若 $maxl = maxrr = -1, maxr \neq -1$，则方案数为 $(n-maxr+1) \times i$。

- 若 $maxl = -1, maxrr \neq -1$，则方案数为 $(maxrr-maxr) \times i$。

- 若 $maxr = maxll = -1, maxl \neq -1$，则方案数为 $(n-i+1) \times maxl$。

- 若 $maxr = -1, maxll \neq -1$，则方案数为 $(n-i+1) \times (maxl-maxll)$。

- 若 $maxll = maxrr = -1, maxl \neq -1, maxr \neq -1$，则方案数为 $maxl \times (maxr-i)+(n-maxr+1) \times (i-maxl)$。

- 若 $maxll = -1, maxrr \neq -1, maxl \neq -1$，则方案数为 $maxl \times (maxr-i) + (maxrr-maxr) \times (i-maxl)$。

- 若 $maxrr = -1, maxll \neq -1, maxr \neq -1$，则方案数为 $(n-maxr+1) \times (i-maxl) + (maxl-maxll) \times (maxr-i)$。

- 若 $maxrr \neq -1, maxll \neq -1$，则方案数为 $(maxl-maxll) \times (maxr-i) + (maxrr-maxr) \times (i-maxl)$。

然后这题就做完了，有一车细节，为啥只评绿啊？

# 参考代码

代码太长了，所以贴个[提交记录](https://atcoder.jp/contests/abc140/submissions/60680782)。

---

## 作者：Kobe_BeanBryant (赞：1)

## 题目大意：
在一个 $ N $ 的排列 $ P $，对于区间 $ [l,r] $，其中 $ l<r $，求所有区间 $ [l,r] $ 中第二大的数的和。
## 方法：
对于本题目，可以用双向链表来实现本题目的要求（本蒟蒻能想到的最优方法），我们应该利用原先求解所得出的结果，以此减少时长。
## 实现：
1. 当我们用从小到大的顺序来求解时，把原来求过的都直接跳过，不用再进行重新求解，以此来降低时间的复杂度。

2. 在我们每次更新时，比当前小的数都已经被跳过了，所以可以直接调用没跳过的数（大于当前的数）。

3. 更新，跳过当前这个。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long int n,sum=0;//sum统计
long long vis[1000005],L[1000005],R[1000005];//双向链表L
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d",&x);
		vis[x]=i,L[i]=i-1,R[i]=i+1;//将数组赋值，以便后面求sum的值
	}
	for(int i=1;i<=n;i++){
		int l=L[vis[i]],r=R[vis[i]];
		if(1<=l){
			sum+=i*(l-L[l])*(r-vis[i]);
		}
		if(r<=n){
			sum+=i*(vis[i]-l)*(R[r]-r);
		}
		L[r]=l,R[l]=r;//赋原值
	}
	printf("%lld",sum);//输出
	return 0;//结束
}
```

---

## 作者：_Kenma_ (赞：0)

# abc140_e 解题报告

## 前言

板。

## 思路分析

首先考虑换成最大值怎么求。

发现可以枚举每个数作为最大值，计算每个数的贡献。

将 $a_i$ 左边的第一个大于它的数的下标记为 $l_i$，右边记为 $r_i$，那么 $a_i$ 的贡献区间为 $[L,R],L\in[1,l_i],R \in[r_i,n]$。

求 $l_i,r_i$ 可以用单调栈。

然后考虑怎样推广到次大值。

类似地，将 $a_i$ 左边第一个大于它的数的下标 $l_1$，第二个下标记为 $l_2$。同样地右边第一个记为 $r_1$，右边第二个记为 $r_2$。

然后不难发现 $a_i$ 的贡献区间为 $[L,R],L\in(l_2,l_1],R\in[i,r_1]$ 和 $[L,R],L \in[l_1,i],R\in[r_1,r_2)$ 两段。

瓶颈在于怎么快速求出 $l_1,l_2,r_1,r_2$。

方法有很多，我使用了 set。

具体地，可以将每个数按 $a_i$ 大小排序，然后依次插入下标 $i$，直接在 set 中查找前驱后继就行。

复杂度 $O(n\log n)$。

## 代码实现

注意 set 查找前驱后继时的边界，容易 RE。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans;
int a[100005],b[100005];
set<int> s;
bool cmp(int x,int y){
	return a[x]>a[y];
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0); 
	cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=i;
    }
    sort(b+1,b+1+n,cmp);
    s.emplace(0);
    s.emplace(n+1);
    for(int i=1;i<=n;i++){
        set<int>::iterator it=s.lower_bound(b[i]);
        if(next(it)!=s.end()){
            ans+=a[b[i]]*(b[i]-*(prev(it)))*(*(next(it))-*it);
        }
        it--;
        if(it!=s.begin()){
		    ans+=a[b[i]]*(*it-*(prev(it)))*(*(next(it))-b[i]);
        }
        s.insert(b[i]);
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：_Flame_ (赞：0)

### solution

直接推一类的做法对我们来说太难了，真得粗暴一点。

次大值怎么求呢？

我们考虑把 $a_i$ 为其中次大值的区间 $[l,r]$ 从 $i$ 处分成两段，发现只有两种情况：

- $a_i$ 在 $[l,i]$ 中最大，$[i,r]$ 中次大。
- $a_i$ 在 $[i,r]$ 中最大，$[l,i]$ 中次大。

然后考虑知道 $a_i$ 为次大值的左右两边最大区间为 $[l1,i]$ 和 $[i,r1]$ 时 $a_i$ 的贡献，可以发现若此时 $a_i$ 在区间 $[l,r]$ 内最大，此时在区间 $[l1,r]$ 和区间 $[l,r1]$ 中 $a_i$ 为次大，取区间 $[L,R]$ 使得依旧满足条件当且仅当 $L\in [l1,l),R\in [i,r]$ 或者 $L\in [l,i],R\in (r,r1]$，直接按乘法原理就可以计算出 $a_i$ 对答案产生贡献的区间个数。

于是我们考虑如何找到这些边界，以找到 $l$ 和 $l1$ 为例，我们可以先二分出一个最小的断点 $l$ 使得 $a_i$ 在 $i$ 和 $l$ 间最大，再在 $1$ 到 $l$ 间二分处 $l1$ 使得 $l$ 到 $l1$ 中的最大值比 $a_i$ 大，右端点 $r$ 和 $r1$ 同理。

ST 表平时不太常用到，对我来说太难了，于是用线段树维护区间最大值，复杂度劣一点，但没关系。

### code

```cpp
int n;

int a[maxn];

struct seg{
	int mx;
}tree[maxn<<1];

void pushup(int o){
	tree[o].mx=max(tree[o<<1].mx,tree[o<<1|1].mx);
}

void build(int o,int l,int r){
	if(l==r){
		tree[o].mx=a[l];
		return ;
	}
	int mid=l+r>>1;
	build(o<<1,l,mid);
	build(o<<1|1,mid+1,r);
	pushup(o);
}

int query(int o,int l,int r,int ll,int rr){
	if(ll<=l&&rr>=r){
		return tree[o].mx;
	}
	int mid=l+r>>1,res=0;
	if(ll<=mid){
		res=max(res,query(o<<1,l,mid,ll,rr));
	}
	if(rr>mid){
		res=max(res,query(o<<1|1,mid+1,r,ll,rr));
	}
	return res;
}

void solve(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	build(1,1,n);
	int ans=0;
	for(int i=1;i<=n;i++){
		int l=1,r=i,l1=1,res=i;
		while(l<=r){
			int mid=l+r>>1;
			if(query(1,1,n,mid,i)==a[i]){
				res=mid;
				r=mid-1;
			}
			else{
				l=mid+1;
			}
		}
		l1=res;
		int l2=1;
		l=1,r=max(1ll,l1-2);
		res=r;
		while(l<=r){
			int mid=l+r>>1;
			if(query(1,1,n,mid,max(mid,l1-2))<a[i]){
				res=mid;
				r=mid-1;
			}
			else{
				l=mid+1;
			}
		}
		if(a[res]>a[i]&&a[res+1]>a[i]){
			l2=res+1;
		}
		else{
			l2=res;
		}
		int r1=0,r2=0;
		l=i,r=n;
		res=l;
		while(l<=r){
			int mid=l+r>>1;
			if(query(1,1,n,i,mid)==a[i]){
				res=mid;
				l=mid+1;
			}
			else{
				r=mid-1;
			}
		}
		r1=res;
		r2=res;
		ans+=a[i]*(l1-l2)*(r2-i+1);
		l=min(n,r1+2),r=n;
		res=l;
		while(l<=r){
			int mid=l+r>>1;
			if(query(1,1,n,min(mid,r1+2),mid)<a[i]){
				res=mid;
				l=mid+1;
			}
			else{
				r=mid-1;
			}
		}
		if(a[res]>a[i]&&a[res-1]>a[i]){
			r2=res-1;
		}
		else{
			r2=res;
		}
		ans+=a[i]*(i-l1+1)*(r2-r1);
	}
	write(ans);
	puts("");
	return ;
}
  ```

---

## 作者：small_john (赞：0)

## 思路

比较难想的一道题。

我们可以把数从小到大遍历，每次就找数比 $i$ 小的最大和次大，左边的下标记录为 $l_1,l_2$，右边的记录为 $r_1,r_2$，当前记录为 $now$。那么对答案的贡献就是 $((l_1-l_2)\times(r_1-now)+(r_2-r_1)\times(now-l_1))\times i$。

那如何快速找到 $l_1,l_2,r_1,r_2$ 呢？用双向链表维护，时间复杂度 $O(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n,p[N],vis[N],l[N],r[N],ans;
signed main()
{
	cin>>n;
	for(int i = 1;i<=n;i++)
		cin>>p[i],vis[p[i]] = i,l[i] = i-1,r[i] = i+1;//建立链表
	for(int i = 1;i<n;i++)
	{
		int lt = l[vis[i]],rt = r[vis[i]];
		if(lt>0) ans+=i*(lt-l[lt])*(rt-vis[i]);//左边有值
		if(rt<=n) ans+=i*(r[rt]-rt)*(vis[i]-lt);//右边有值
		l[rt] = lt,r[lt] = rt;//删除此元素
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

考虑通过以贡献找数量。

枚举第二大值的位置，则有 $2$ 种可能的区间：

1. $left_{i,2}+1 \le l \le left_{i,1}$ 且 $i \le r \le right_{i,1}-1$。
2. $left_{i,1}+1 \le l \le i$ 且 $right_{i,1} \le r \le right_{i,2}-1$。

其中 $left_{i,j}$ 表示 $a_i$ 左边第 $j$ 个大于 $a_i$ 的位置。$right$ 同理。上面 $2$ 种区间都会且只会包含一个比 $a_i$ 大的数，所以第二大值只会是 $a_i$。把所有的这 $2$ 种区间的方案数求出来即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline

const int N=1e5+10;
int n,a[N];
int lnxt[N],lnxt2[N];
int rnxt[N],rnxt2[N];
int tr[N];
vector<int> l[N],r[N];
int ans;

il void add1(int x,int y){
	while(x) tr[x]=max(tr[x],y),x-=x&(-x);
}
il int query1(int x){
	int Max=0;
	while(x<=n) Max=max(Max,tr[x]),x+=x&(-x);
	return Max;
}
il void add2(int x,int y){
	while(x) tr[x]=min(tr[x],y),x-=x&(-x);
}
il int query2(int x){
	int Min=n+1;
	while(x<=n) Min=min(Min,tr[x]),x+=x&(-x);
	return Min;
}

il void solve(){
	cin>>n;
	for(re int i=1;i<=n;++i) cin>>a[i];
	memset(tr,0,sizeof(tr));
	for(re int i=1;i<=n;++i) lnxt[i]=query1(a[i]+1),add1(a[i],i),l[lnxt[i]].push_back(i);
	memset(tr,0x3f,sizeof(tr));
	for(re int i=n;i>=1;--i) rnxt[i]=query2(a[i]+1),add2(a[i],i),r[rnxt[i]].push_back(i);
	rnxt[n+1]=n+1,lnxt[0]=0;
	memset(tr,0,sizeof(tr));
	for(re int i=0;i<=n;++i){
		for(re int j=0;j<l[i].size();++j) lnxt2[l[i][j]]=query1(a[l[i][j]]+1);
		if(i>=1) add1(a[i],i);	
	}
	memset(tr,0x3f,sizeof(tr));
	for(re int i=n+1;i>=1;--i){
		for(re int j=0;j<r[i].size();++j) rnxt2[r[i][j]]=query2(a[r[i][j]]+1);
		if(i<=n) add2(a[i],i);	
	}
	rnxt2[n+1]=n+1,lnxt2[0]=0;
	
	for(re int i=1;i<=n;++i){
		int cnt=0;
		cnt+=(i-lnxt[i])*(rnxt2[i]-rnxt[i]);
		cnt+=(rnxt[i]-i)*(lnxt[i]-lnxt2[i]);
		
		ans+=cnt*a[i];
	}
	cout<<ans;
	return ;
}

signed main(){
	solve();
	return 0;
}

```


---

