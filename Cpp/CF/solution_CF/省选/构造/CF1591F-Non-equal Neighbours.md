# Non-equal Neighbours

## 题目描述

You are given an array of $ n $ positive integers $ a_1, a_2, \ldots, a_n $ . Your task is to calculate the number of arrays of $ n $ positive integers $ b_1, b_2, \ldots, b_n $ such that:

- $ 1 \le b_i \le a_i $ for every $ i $ ( $ 1 \le i \le n $ ), and
- $ b_i \neq b_{i+1} $ for every $ i $ ( $ 1 \le i \le n - 1 $ ).

The number of such arrays can be very large, so print it modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case possible arrays are $ [1, 2, 1] $ and $ [2, 1, 2] $ .

In the second test case possible arrays are $ [1, 2] $ , $ [1, 3] $ , $ [2, 1] $ and $ [2, 3] $ .

## 样例 #1

### 输入

```
3
2 2 2```

### 输出

```
2```

## 样例 #2

### 输入

```
2
2 3```

### 输出

```
4```

## 样例 #3

### 输入

```
3
1 1 1```

### 输出

```
0```

# 题解

## 作者：_ztyqwq (赞：12)

考虑容斥。称满足 $ b_i = b_{i + 1} (1 \leqslant i < n) $ 的 $ i $ 为关键点。则题意要求的是有 $ 0 $ 个关键点的 $ \{b_n\} $ 的数量。

容易发现

$$ \text{答案} = \text{至少有 } 0 \text{ 个关键点的答案} - \text{至少有 } 1 \text{ 个关键点的答案} + ... + (-1)^{n - 1} \text{至少有 } n - 1 \text{ 个关键点的答案} $$

观察发现长度为 $ n $，**至少**有 $ k $ 个关键点的一组 $ \{b_n\} $ 其实是将整个数组分成了连续 $ n - k $ 段，**每段的 $ b_i $ 一定相同**，但**相邻的两段的数可相同可不同**，这是容斥思想的核心。

定义 $ f_{i, 0/1} $ 为 $ b_1, ..., b_i $ 这一段排列，分成连续的偶数段 / 奇数段的方案数，其中每段 $ b_j $ 一定相同，相邻两段无要求。

则有

$$ \text{答案} = (-1)^{n}(f_{n, 0} - f_{n, 1}) $$

考虑如何转移。枚举 $ i $ 所在的一段的左端点 $ j $，可以得到

$$ f_{i, 0/1} = \sum_{j = 1}^i f_{j - 1, 1/0} (\min_{k = j}^i a_k) $$

$ \min_{k= j}^i a_k $ 的含义是 $ b_j, ..., b_i $ 这些数只能是同一个数，取值范围自然是这个区间中最小的 $ a_i $。

发现这样转移是 $ O(n^2) $ 的。考虑在 $ \min $ 的单调性上做优化。

维护一个 $ a_i $ 严格递增的单调栈。在做 $ f_{i, 0/1} $ 时，单调栈的栈顶应该是 $ i (a_i) $，设栈顶的下一位元素是 $ x (a_x) $。则有

$$ f_{i, 0/1} = f_{x, 0/1} + a_i \sum_{j = x + 1}^i f_{j - 1, 1/0} $$

解释：因为 $ a_x $ 是 $ i $ 往左走第一个比 $ a_i $ 大的数，所以转移方程中，$ j $ 取 $ 1 $ 到 $ x $ 的任何数，$ \min_{k = j}^i a_k $ 都与 $ \min_{k = j}^x a_k $ 相等。因此这些 $ j $ 对 $ f_{i, 0/1} $ 的贡献之和就等于 $ f_{x, 0/1} $。

而 $ a_{x + 1} $ 到 $ a_{i - 1} $ 的数都小于等于 $ a_i $。因此 $ j $ 取 $ x + 1 $ 到 $ i $ 的任何数，都有 $ \min_{k = j}^i a_k = a_i $。因此这些 $ j $ 对 $ f_{i, 0/1} $ 的贡献之和就是 $ a_i \sum\limits_{j = x + 1}^i f_{j - 1, 1/0} $。显然可以通过维护 $ f_{i, 0/1} $ 的前缀和快速计算。

注意栈中只有一个元素时，$ f_{i, 0/1} = a_i \sum\limits_{j = 1}^i f_{j - 1, 1/0} $。此时 $ a_i $ 大于 $ a_1 $ 到 $ a_{i - 1} $ 的所有数，也就不存在这样的 $ x $。

边界条件为 $ f_{0, 0} = 1, f_{0, 1} = 0 $。时间复杂度 $ \Theta(n) $。

~~看题解也就图一乐 真理解还得看代码~~

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
typedef long long ll;
#define int ll
int a[200010], f[200010][2], s[200010][2];
int stk[200010], cnt = 0;
inline int p1(int x)
{
	return (x & 1) ? mod - 1 : 1;
}
signed main()
{
	int n;
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	f[0][0] = s[0][0] = 1, f[0][1] = s[0][1] = 0;
	stk[0] = 0;
	for(int i = 1; i <= n; i++)
	{
		while(cnt && a[stk[cnt]] >= a[i])
			cnt--;
		stk[++cnt] = i;
		f[i][0] = ((cnt == 1 ? 0 : f[stk[cnt - 1]][0]) + (s[i - 1][1] - (cnt == 1 ? 0 : s[stk[cnt - 1] - 1][1]) + mod) * a[i]) % mod;
		f[i][1] = ((cnt == 1 ? 0 : f[stk[cnt - 1]][1]) + (s[i - 1][0] - (cnt == 1 ? 0 : s[stk[cnt - 1] - 1][0]) + mod) * a[i]) % mod;
		s[i][0] = (s[i - 1][0] + f[i][0]) % mod;
		s[i][1] = (s[i - 1][1] + f[i][1]) % mod;
	}
	printf("%lld\n", (f[n][0] - f[n][1] + mod) * p1(n) % mod);
	return 0;
}

```

---

## 作者：Dzhao (赞：12)

呆呆题，提供一种十分呆呆的做法。

我们先暴力 DP，令 $dp_{i,j}$ 表示当前填数到第 $i$ 位，第 $i$ 位填了 $j$ 的方案数，那么转移即为 $dp_{i,j}=\sum\limits_{k\not=j}dp_{i-1,k}(1\le j\le a_i)$，这个转移就相当于是你需要维护一个序列 $b$，每次将 $1\le j\le a_i$ 的 $b_j$ 变为 $sum-b_j$（$sum$ 为 $b$ 序列的和），将 $j\ge a_i$ 的 $b_j$ 变为 $0$，这个就相当于维护区间乘 $-1$ 和 $0$，区间加 $sum$，查询全局和，就是线段树2，然后就做完了，复杂度 $\mathcal{O}(n\log val)$，$val$ 是值域。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, mod = 998244353;
int n, ls[N * 60], rs[N * 60], tr[N * 60], tag1[N * 60], tag2[N * 60], rt, a[N], cnt;
int NewNode() {tag2[++cnt] = 1; return cnt;}
void pd1(int p, int l, int r) {
	if (tag1[p]) {
		int mid = l + r >> 1;
		if (!ls[p]) ls[p] = NewNode();
		if (!rs[p]) rs[p] = NewNode();
		tr[ls[p]] = (tr[ls[p]] + 1ll * tag1[p] * (mid - l + 1)) % mod;
		tr[rs[p]] = (tr[rs[p]] + 1ll * tag1[p] * (r - mid)) % mod;
		tag1[ls[p]] = (tag1[ls[p]] + tag1[p]) % mod;
		tag1[rs[p]] = (tag1[rs[p]] + tag1[p]) % mod;
		tag1[p] = 0;
	}
}
void pd2(int p) {
	if (tag2[p] != 1) {
		if (!ls[p]) ls[p] = NewNode();
		if (!rs[p]) rs[p] = NewNode();
		tr[ls[p]] = 1ll * tr[ls[p]] * tag2[p] % mod;
		tr[rs[p]] = 1ll * tr[rs[p]] * tag2[p] % mod;
		tag2[ls[p]] = 1ll * tag2[ls[p]] * tag2[p] % mod;
		tag2[rs[p]] = 1ll * tag2[rs[p]] * tag2[p] % mod;
		tag1[ls[p]] = 1ll * tag1[ls[p]] * tag2[p] % mod;
		tag1[rs[p]] = 1ll * tag1[rs[p]] * tag2[p] % mod;
		tag2[p] = 1;
	}
}
void push_up(int p) {tr[p] = (tr[ls[p]] + tr[rs[p]]) % mod;}
void modify(int &p, int l, int r, int x, int y, int z, int op) {
	if (x > y) return;
	if (!p) p = NewNode();
	if (l >= x && r <= y) {
		if (op == 1) {
			tr[p] = (tr[p] + 1ll * z * (r - l + 1)) % mod;
			if (l != r) pd2(p), pd1(p, l, r);
			tag1[p] = (tag1[p] + z) % mod;
		} else {
			tr[p] = 1ll * z * tr[p] % mod;
			if (l != r) pd2(p), pd1(p, l, r);
			tag2[p] = 1ll * tag2[p] * z % mod;
		}
		return;
	}
	pd2(p); pd1(p, l, r); int mid = l + r >> 1;
	if (mid >= x) modify(ls[p], l, mid, x, y, z, op);
	if (mid < y) modify(rs[p], mid + 1, r, x, y, z, op);
	push_up(p);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	modify(rt, 1, 1e9, 1, a[1], 1, 1);
	for (int i = 2; i <= n; i++) {
		int sum = tr[rt];
		modify(rt, 1, 1e9, 1, a[i], -1, 2);
		modify(rt, 1, 1e9, 1, a[i], sum, 1);
		modify(rt, 1, 1e9, a[i] + 1, 1e9, 0, 2);
	}
	printf("%d\n", (tr[rt] + mod) % mod);
	return 0;
}
```

---

## 作者：lfxxx (赞：5)

先不管值域，设计状态 $dp_{i,j}$ 表示考虑前 $i$ 个数最后一个数为 $j$ 的方案数，那么有如下转移：

$$dp_{i,j} = dp_{i-1,k} (j \not = k,j \leq a_i)$$

先滚动数组去掉一维状态，然后发现每一次操作对于数组 $dp$ 而言其实是对于 $j \leq a_i$ 的 $dp_{j}$ 变成 $x - dp_j$ 这里 $x$ 代表所有 $dp_i$ 的总和，使得 $j > a_i$ 的 $dp_j$ 变为 $0$。

因此考虑用线段树维护 $dp$ 数组即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 2e5+114;
const int top = 1e9+7;
const int mod = 998244353;
struct Node{
	int sum,tag1,tag2,ls,rs,lt,rt;
}tr[maxn*40];
int tot,rt;
void pushup(int cur){
	tr[cur].sum=(tr[tr[cur].ls].sum+tr[tr[cur].rs].sum)%mod;
}
void pushdown1(int cur){
	if(tr[cur].tag1!=0){
		int mid=(tr[cur].lt+tr[cur].rt)>>1;
		if(tr[cur].ls==0) tr[cur].ls=++tot,tr[tr[cur].ls].tag2=1,tr[tr[cur].ls].lt=tr[cur].lt,tr[tr[cur].ls].rt=mid;
		if(tr[cur].rs==0) tr[cur].rs=++tot,tr[tr[cur].rs].tag2=1,tr[tr[cur].rs].lt=mid+1,tr[tr[cur].rs].rt=tr[cur].rt;
		tr[tr[cur].ls].sum=(tr[tr[cur].ls].sum+tr[cur].tag1*(mid-tr[cur].lt+1))%mod;
		tr[tr[cur].rs].sum=(tr[tr[cur].rs].sum+tr[cur].tag1*(tr[cur].rt-mid))%mod;
		tr[tr[cur].ls].tag1=(tr[tr[cur].ls].tag1+tr[cur].tag1)%mod;
		tr[tr[cur].rs].tag1=(tr[tr[cur].rs].tag1+tr[cur].tag1)%mod;
		tr[cur].tag1=0;
	}
}
void pushdown2(int cur){
	if(tr[cur].tag2!=1){
		int mid=(tr[cur].lt+tr[cur].rt)>>1;
		if(tr[cur].ls==0) tr[cur].ls=++tot,tr[tr[cur].ls].tag2=1,tr[tr[cur].ls].lt=tr[cur].lt,tr[tr[cur].ls].rt=mid;
		if(tr[cur].rs==0) tr[cur].rs=++tot,tr[tr[cur].rs].tag2=1,tr[tr[cur].rs].lt=mid+1,tr[tr[cur].rs].rt=tr[cur].rt;
		tr[tr[cur].ls].sum=(tr[tr[cur].ls].sum*tr[cur].tag2)%mod;
		tr[tr[cur].rs].sum=(tr[tr[cur].rs].sum*tr[cur].tag2)%mod;
		tr[tr[cur].ls].tag1=(tr[tr[cur].ls].tag1*tr[cur].tag2)%mod;
		tr[tr[cur].rs].tag1=(tr[tr[cur].rs].tag1*tr[cur].tag2)%mod;
		tr[tr[cur].ls].tag2=(tr[tr[cur].ls].tag2*tr[cur].tag2)%mod;
		tr[tr[cur].rs].tag2=(tr[tr[cur].rs].tag2*tr[cur].tag2)%mod;
		tr[cur].tag2=1;
	}
}
void pushdown(int cur){
	pushdown2(cur);
	pushdown1(cur);
}
void update1(int &cur,int lt,int rt,int l,int r,int v){
	if(lt>r||rt<l) return ;
	if(cur==0){
		cur=++tot;
		tr[cur].lt=lt,tr[cur].rt=rt,tr[cur].tag2=1,tr[cur].tag1=0;		
	}
	if(l<=lt&&rt<=r){
		tr[cur].sum+=((v%mod)*(rt-lt+1)%mod);
		tr[cur].sum%=mod;
		tr[cur].tag1+=v;
		tr[cur].tag1%=mod;
		return ;
	}	
	pushdown(cur);
	int mid=(lt+rt)>>1;
	update1(tr[cur].ls,lt,mid,l,r,v);
	update1(tr[cur].rs,mid+1,rt,l,r,v);
	pushup(cur);
}
void update2(int &cur,int lt,int rt,int l,int r,int v){
	if(lt>r||rt<l) return ;
	if(cur==0){
		cur=++tot;
		tr[cur].lt=lt,tr[cur].rt=rt,tr[cur].tag2=1,tr[cur].tag1=0;	
	}
	if(l<=lt&&rt<=r){
		tr[cur].sum*=v;
		tr[cur].sum%=mod;
		tr[cur].tag2*=v;
		tr[cur].tag2%=mod;
		tr[cur].tag1*=v;
		tr[cur].tag1%=mod;
		return ;
	}	
	pushdown(cur);
	int mid=(lt+rt)>>1;
	update2(tr[cur].ls,lt,mid,l,r,v);
	update2(tr[cur].rs,mid+1,rt,l,r,v);
	pushup(cur);
}
int a[maxn],n;
signed main(){
cin>>n;
for(int i=1;i<=n;i++) cin>>a[i];
update1(rt,1,top,1,a[1],1);
for(int i=2;i<=n;i++){
	int sum=tr[rt].sum%mod;
	update2(rt,1,top,1,a[i],-1);
	update1(rt,1,top,1,a[i],sum);
	update2(rt,1,top,a[i]+1,top,0);
} 
cout<<(tr[rt].sum+mod)%mod;
return 0;
}
```


---

## 作者：I_am_Accepted (赞：4)

[AtCoder相同题目（除范围）](https://atcoder.jp/contests/arc115/tasks/arc115_e)~~双倍经验~~

### Analysis

设 $f_n$ 表示前 $n$ 个数满足条件的方案数。

由容斥原理得（规定 $f_0=1$）：

$$f_n=\sum\limits_{i=0}^{n-1}(-1)^{n-i+1}f_i\min\limits_{j=i+1}^{n}a_j$$

其中 $f_i\min\limits_{j=i+1}^{n}a_j$ 表示 $b_y=b_{y+1}(x<y<i)$ 且 $b_y\not=b_{y+1}(y\leqslant x)$ 的方案数。

发现这不是一般的 DP 优化方法……

找到最大的 $k$ 使得 $0<k<n \land a_k\leqslant a_n$，特判 $k$ 不存在的情况，那么转移时当 $i\leqslant k-1$：

$$\min\limits_{j=i+1}^{n}a_j=\min\limits_{j=i+1}^{k}a_j$$

即：

$$\begin{aligned}
f_n &= a_n\sum\limits_{i=k}^{n-1}(-1)^{n-i+1}f_i+\sum\limits_{i=0}^{k-1}(-1)^{n-i+1}f_i\min\limits_{j=i+1}^{k}a_j
\\
&= a_n\sum\limits_{i=k}^{n-1}(-1)^{n-i+1}f_i+(-1)^{n-k}\sum\limits_{i=0}^{k-1}(-1)^{k-i+1}f_i\min\limits_{j=i+1}^{k}a_j
\\
&= a_n\sum\limits_{i=k}^{n-1}(-1)^{n-i+1}f_i+(-1)^{n-k}f_k
\end{aligned}$$

每一个位置的 $k$ 可以在 $O(N)$ 内用单调栈求出。

过程中求 $\{f\}$ 的正负交替的前缀和，即可 $O(1)$ 求出每一个 $\sum\limits_{i=k}^{n-1}(-1)^{n-i+1}f_i$，总时间 $O(N)$。

### Code

[Link](https://codeforces.com/contest/1591/submission/139476338)

---

## 作者：樱雪喵 (赞：2)

CF1585F & 1591F，两个一样的题但一边题解全是线段树，另外一边全是容斥，好离谱。

直接 dp 是 $O(nV)$ 的，考虑容斥。钦定有 $i$ 对相邻数相同，发现这个东西要考虑好几对数连成一段的情况，还是不好求。  
但上面的问题给我们一个启发，有 $i$ 对数相同等价于把序列拆成不多于 $n-i$ 段。  
那设 $f_{i,j}$ 表示前 $i$ 个数分成 $j$ 段，有朴素 dp：
$$
f_{i,j}=\sum_{k=0}^{i-1} f_{k,j-1}\times \min\{a_{k+1},\dots,a_i\}
$$
最后统计答案就是
$$ans=\sum_{j=1}^n (-1)^{j+n} f_{n,j}$$

状态还要优化，发现我们只关心 $j$ 的奇偶性而不关心具体是什么。设 $f_{i,j}$ 表示前 $i$ 个，钦定分成奇数还是偶数段的方案数。方程改成
$$
f_{i,j}=\sum_{k=0}^{i-1} f_{k,j\oplus 1}\times \min\{a_{k+1},\dots,a_i\}
$$

再优化转移复杂度，考虑后面 $\min$ 的值。设第一个比 $a_i$ 小的位置在 $lst_i$。那么小于 $lst_i$ 的 $k$ 可以直接从 $f_{lst_i,j}$ 转移过来。  
求 $lst$ 用单调栈。那么式子是
$$f_{i,j}=f_{lst_i,j}+\sum_{k=lst_i}^{i-1} f_{k,j\oplus 1}\times a_i$$
把 $a_i$ 拆出去，$\sum f_{k,j\oplus 1}$ 用前缀和优化，时间复杂度 $O(n)$。

```cpp
#define int long long
const int N=2e5+5,mod=998244353;
int n,a[N];
int f[N][2],sum[N][2],lst[N];
stack<int> q;
signed main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=n;i++)
    {
        while(!q.empty()&&a[q.top()]>=a[i]) q.pop();
        lst[i]=q.empty()?0:q.top(); q.push(i);
    }
    f[0][0]=sum[0][0]=1;
    for(int i=1;i<=n;i++)
        for(int j=0;j<=1;j++)
        {
            f[i][j]=(lst[i]?f[lst[i]][j]:0)+a[i]*(sum[i-1][j^1]-(lst[i]?sum[lst[i]-1][j^1]:0))%mod;
            f[i][j]=(f[i][j]%mod+mod)%mod;
            sum[i][j]=(f[i][j]+sum[i-1][j])%mod;
        }
    if(n&1) printf("%lld\n",(f[n][1]-f[n][0]+mod)%mod);
    else printf("%lld\n",(f[n][0]-f[n][1]+mod)%mod);
    return 0;
}
```

---

## 作者：xiezheyuan (赞：2)

## 简要题意

有 $n$ 个空，第 $i$ 个空要填 $1\sim b_i$ 的一个数。且相邻两个空不能填相同的数。问有多少种填数方案，对 $998244353$ 取模。

$1 \leq n \leq 5 \times 10^5,1 \leq b_i \leq 10^9$。

## 思路

如果有条件建议大家直接看 [英文题解](https://codeforces.com/blog/entry/97845)。个人认为讲得最清晰。

首先考虑正难则反的原则。如果直接对相邻不同的方案计数比较麻烦，不如直接对相邻相同的方案计数。最后再用总方案数减去它。

设 $f(i,j)$ 表示前 $i$ 个数有 $j$ 个相邻的数相同。不如通过容斥思想换一种说法，将 $[1:i]$ 部分划分成 $i-j+1$ 段，每一段的空填的都是一样的。注意到我们这里其实隐含了 **至少** $i-j+1$ 段这个条件。

于是我们干脆换一个说法。直接设 $f(i,j)$ 表示前 $i$ 个数可以分成 $j+1$ 段（至于为什么是 $j+1$ 段，这是我做题时的历史遗留问题），每一段的数都是相同的。

然后枚举断点就可以得到状态转移方程：

$$
f(i,j)=\sum_{k=1}^{i}f(k-1,j-1)\times \min_{s=k}^{i}a_s
$$

时间复杂度 $O(n^3)$，空间复杂度 $O(n^2)$。均难以接受。

先来优化空间，不难发现我们其实可以按照 $j$ 的奇偶性压掉 $j$ 这一维。

然后考虑优化时间复杂度。用 ST 表优化掉 $\min$ 的复杂度只能做到 $O(n^2)$。我们需要更强力的方法。

先维护 $f$ 的前缀和 $g$。然后考虑带 $\min$ 的那一个系数。

我们发现可以找到左侧第一个小于 $a_i$ 的数 $a_s$。那么这一段的系数都是相同的，直接用前缀和去乘上 $a_i$ 即可。

最后还有前面的部分。我在这一部分想了很久。后来发现其实就是：

$$
\sum_{k=1}^{s}f(k-1,j-1)\times\min_{t=k}^{s} a_t
$$

这不就是 $f(s,j)$ 吗？

于是我们就可以 $O(n)$ 解决这个 dp。

最后答案应该是：

$$
f(n,n)-f(n,n-1)
$$


## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
using namespace std;

const int mod = 998244353;
const int N = 2e5+5;
int f[N][2],g[N][2];
int n,a[N],stk[N],top;

int M(int x){
	return (x%mod+mod)%mod;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	f[0][0]=1;f[0][1]=0;
	g[0][0]=1;g[0][1]=0;
	for(int i=1;i<=n;i++){
		while(top && a[stk[top]] >= a[i]) top--;
		int cur = top?stk[top]:0;
		stk[++top]=i;
		if(!cur){
			f[i][0]=M(g[i-1][1]*a[i]);
			f[i][1]=M(g[i-1][0]*a[i]);
		}
		else{
			f[i][0]=M(f[cur][0]+M(M(M(g[i-1][1]-g[cur-1][1]))*a[i]));
			f[i][1]=M(f[cur][1]+M(M(M(g[i-1][0]-g[cur-1][0]))*a[i]));
		}
		g[i][0] = M(g[i-1][0] + f[i][0]);
		g[i][1] = M(g[i-1][1] + f[i][1]);
//		for(int j=1;j<=i;j++){
//			int ret=INT_MAX;
//			for(int k=j;k<=i;k++){
//				ret = min(ret, a[k]);
//			}
//			f[i][0] += f[j-1][1] * ret % mod;
//			f[i][0] %= mod;
//			f[i][1] += f[j-1][0] * ret;
//			f[i][1] % mod;
//		}
	}
	if(n&1) cout<<(M(f[n][1]-f[n][0]))<<'\n';
	else cout<<(M(f[n][0]-f[n][1]))<<'\n';
	return 0;
}
```


---

## 作者：TernaryTree (赞：1)

来点没有脑子的做法。

$f_{i,j}$ 表示前 $i$ 个数的序列，最后一个是 $j$ 的方案数。

那么有

$$
f_{i,j}=
\begin{cases}
(\sum\limits_{k=1}^{a_{i-1}}f_{i-1,k})-f_{i-1,j}&(j\le a_i) \\
0&(j\gt a_i)
\end{cases}
$$

注意到，一次 $f_{i-1,j}$ 到 $f_{i,j}$ 的转移是取相反数后加上上一个版本的 $f$ 和，$\gt a_i$ 的要特别赋值为 $0$。

取相反数看成区间 $\times (-1)$，赋值为 $0$ 看成区间 $\times 0$，所以维护一个【模板】线段树 2 即可。

值域太大，无脑改成动态开点即可。

代码轻微卡常。

[Code](https://www.luogu.com.cn/paste/t4cubmha)

---

## 作者：_Wind_Leaves_ShaDow_ (赞：1)

神仙 Ds 优化 dp 啊。

碰见这种题先想朴素 dp。设 $dp_{i,j}$ 表示前 $i$ 个数，最后一个取 $j$ 的方案数。

转移显然。枚举一个 $k$ 转移。$dp_{i,j}=\sum_{k=1}^{k\le a_{i-1}}dp_{i-1,k}\times(k\ne j)$。

记值域为 $a_i$，复杂度 $O(n\times a_i\times a_i)$。~~你不爆谁爆。~~

那么把转移方程抽象看。观察状态是如何从 $i-1$ 层转化到 $i$ 层的。

对于当前的 $j$，我们会加上左边的 $[1,j-1]$ 段和右边的 $[j+1,a_{i-1}]$ 段。发现有一点线段树的样子了。但是这么转仍然是 $O(n\times a_i\times\log a_i)$，~~一眼炸~~。于是继续优化。

根据状态方程的意义我们知道当 $j>a_{i-1}$ 时，$dp_{i-1,j}=0$。显然加上 $0$ 结果仍然不变，于是转移可以变成加上左边 $[1,j-1]$ 段和右边 $[j+1,10^9]$ 段。也就是 $[1,10^9]$ 段减去单独的 $j$ 段。

于是得出结论：每一次转移时，$dp_{i,j}=\sum_{k=1}^{k\le 10^9}dp_{i-1,k}-dp_{i-1,j}$。前面的可以直接线段树搞出来。但是仍然没有去掉 $j$ 维的优化。

还能怎么优化？

就是说我们要统一进行操作。把上面的式子小小变一下：

$dp_{i,j}=-dp_{i-1,j}+\sum_{k=1}^{k\le 10^9}dp_{i-1,k}$

看出什么了？

我们处理出整段的和，然后对整个 $dp$ 数组乘上 $-1$，再区间加上预先处理的和。注意一下我们要保证 $dp_{a_i}$ 之后的点为 $0$，所以再区间乘 $0$。也就是我们要维护 **区间加和区间乘**。用 [线段树](https://www.luogu.com.cn/problem/P3373) 解决。这里不对线段树进行过多阐述。

那么我们可以开心线段树解决了。

复杂度 $O(n \log a_i)$。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long 
#define pb(x) push_back(x)
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

using namespace std;
typedef double db;
const int N=2e5+10,M=1e9,mod=998244353,INF=1e16;

int n,a[N],id=0;

struct SegT{
	int sm,tgs,tgm,ls,rs;
}sg[N*60];

inline int build(){//动态开点（1e9开普通线段树也需要胆量的）
	id++;
	sg[id].tgm=1;
	sg[id].ls=sg[id].rs=sg[id].tgs=sg[id].sm=0;
	return id;
}

inline void tgd(int p,int l,int r){//懒标记下放
	if(!sg[p].ls)sg[p].ls=build();
	if(!sg[p].rs)sg[p].rs=build();
	int mid=((l+r)>>1),sl=sg[p].ls,sr=sg[p].rs;
	sg[sl].sm=(sg[sl].sm*sg[p].tgm%mod+sg[p].tgs*(mid-l+1)%mod)%mod;
	sg[sr].sm=(sg[sr].sm*sg[p].tgm%mod+sg[p].tgs*(r-mid)%mod)%mod;
	sg[sl].tgs=(sg[sl].tgs*sg[p].tgm%mod+sg[p].tgs)%mod;
	sg[sr].tgs=(sg[sr].tgs*sg[p].tgm%mod+sg[p].tgs)%mod;
	sg[sl].tgm=(sg[sl].tgm*sg[p].tgm)%mod;
	sg[sr].tgm=(sg[sr].tgm*sg[p].tgm)%mod;
	sg[p].tgs=0;
	sg[p].tgm=1;
	return;
}

inline void add(int ql,int qr,int l,int r,int p,int K){//区间加
	if(ql<=l&&r<=qr){
		sg[p].tgs=(sg[p].tgs+K)%mod;
		sg[p].sm=(sg[p].sm+K*(r-l+1))%mod;
		return;
	}
	if(!sg[p].ls)sg[p].ls=build();
	if(!sg[p].rs)sg[p].rs=build();
	int mid=((l+r)>>1),sl=sg[p].ls,sr=sg[p].rs;
	tgd(p,l,r);
	if(ql<=mid)add(ql,qr,l,mid,sl,K);
	if(qr>mid)add(ql,qr,mid+1,r,sr,K);
	sg[p].sm=(sg[sl].sm+sg[sr].sm)%mod;
	return;
}

inline void mul(int ql,int qr,int l,int r,int p,int K){//区间乘
	if(ql<=l&&r<=qr){
		sg[p].tgs=(sg[p].tgs*K)%mod;
		sg[p].tgm=(sg[p].tgm*K)%mod;
		sg[p].sm=(sg[p].sm*K)%mod;
		return; 
	}
	if(!sg[p].ls)sg[p].ls=build();
	if(!sg[p].rs)sg[p].rs=build();
	int mid=((l+r)>>1),sl=sg[p].ls,sr=sg[p].rs;
	tgd(p,l,r);
	if(ql<=mid)mul(ql,qr,l,mid,sl,K);
	if(qr>mid)mul(ql,qr,mid+1,r,sr,K);
	sg[p].sm=(sg[sl].sm+sg[sr].sm)%mod;
	return; 
}

signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	build();
	add(1,M,1,M,1,1);//这里其实只要开到max(a[i])，但是本人懒。
	mul(a[1]+1,M,1,M,1,0);//预处理 i=1
	for(int i=2;i<=n;i++){
		int sum=sg[1].sm;
		mul(1,M,1,M,1,-1);
		add(1,M,1,M,1,sum);
		mul(a[i]+1,M,1,M,1,0);
	}
	cout<<(sg[1].sm+mod)%mod;//注意取模操作
	return 0;
} 
```

---

## 作者：orz_z (赞：0)

容斥，记 $g_i$ 表示 $[1,i]$ 的答案。

$$
g_i=\sum_{j=1}^{i-1}g_j\times \min_{k=j+1}^{i}a_k\times(-1)^{i-j-1}
$$

记 $f_i$ 表示 $g_i\times(-1)^i$，记 $s$ 为 $f$ 的前缀和。

然后单调栈维护点 $i$ 左边第一个小于等于它的数位置 $k$，则转移方程为：$f_i=f_k-a_i\times (s_{i-1}-s_{k-1})$。

时间复杂度 $\mathcal O(n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define ha putchar(' ')
#define he putchar('\n')

inline int read()
{
	int x = 0;
	char c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x;
}

inline void write(int x)
{
	if(x > 9)
		write(x / 10);
	putchar(x % 10 + 48);
}

const int _ = 5e5 + 10, mod = 998244353;

int n, a[_], t, sk[_];

ll f[_], s[_];

signed main()
{
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	f[1] = s[1] = -a[1], sk[++t] = 1;
	for(int i = 2; i <= n; ++i)
	{
		while(t && a[sk[t]] > a[i]) t--;
		if(t == 0) f[i] = -a[i] * (s[i - 1] + 1) % mod;
		else f[i] = (f[sk[t]] - a[i] * (s[i - 1] - s[sk[t] - 1])) % mod;
		s[i] = (s[i - 1] + f[i]) % mod;
		sk[++t] = i;
	}
	write(((n & 1 ? -1 : 1) * f[n] % mod + mod) % mod), he;
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

## 思路

首先考虑最暴力的 $dp_{i,j}$，看到第 $i$ 位选了 $b_i=j$ ，暴力转移 $dp_{i,j}=\sum_{k\not=j}dp_{i-1,k}$，复杂度 $O(n\times \max\{a_i\})$。

考虑优化，首先使用离散化将 $a_i$ 分成若干个区间，容易发现区间内 $dp$ 值完全相等，故可以改变定义为选了 $a_i=l_j\sim r_j$，其中 $l_j,r_j$ 为区间左右端点，此时复杂度为 $O(n^2)$。

继续优化，考虑上面的式子本质上转移可以区间统一加上所有 $dp$ 的和，区间对当前 $dp$ 值乘上 $-1$，再将区间和全部加上即可。遇到大于 $a_i$ 的区间乘 $0$。很显然，我们可以把线段树 $2$ 的板子搬过来使用。复杂度降低为了 $O(n\log n)$，即可通过本题。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
const int p=998244353; 
struct vert{
	int num,mul,plu,size,tg;
};
int a[200005],b[200005];
struct sgt{
	vert f[2000005];
	void pushup(int now){
		f[now].num=(f[now*2].num+f[now*2+1].num)%p;
		f[now].size=f[now*2].size+f[now*2+1].size; 
	}
	void pushdown(int now){
		f[now*2].num=(f[now*2].num*f[now].mul+f[now].plu*f[now*2].size)%p;
		f[now*2+1].num=(f[now*2+1].num*f[now].mul+f[now].plu*f[now*2+1].size)%p;
		f[now*2].mul=(f[now*2].mul*f[now].mul)%p;
		f[now*2+1].mul=(f[now*2+1].mul*f[now].mul)%p;
		f[now*2].plu=(f[now*2].plu*f[now].mul+f[now].plu)%p;
		f[now*2+1].plu=(f[now*2+1].plu*f[now].mul+f[now].plu)%p;
		f[now].mul=1;
		f[now].plu=0;
	}
	void init(int now,int id){
		f[now].mul=1;
		f[now].plu=0;
		f[now].num=0;
		f[now].size=b[id];
	}
	void build(int now,int l,int r){
		if(l==r){
			init(now,l);
			return ; 
		}
		int mid=(l+r)>>1;
		f[now].mul=1;
		build(now*2,l,mid);
		build(now*2+1,mid+1,r);
		pushup(now);
	}
	void modify1(int now,int l,int r,int ql,int qr,int mul1){
		if(ql<=l&&qr>=r){
			f[now].mul=(f[now].mul*mul1)%p;
			f[now].plu=(f[now].plu*mul1)%p;
			f[now].num=(f[now].num*mul1)%p;
			return ;
		}
		if(ql>r||qr<l) return ;
		pushdown(now);
		int mid=(l+r)>>1;
		modify1(now*2,l,mid,ql,qr,mul1);
		modify1(now*2+1,mid+1,r,ql,qr,mul1);
		pushup(now);
	}
	void modify2(int now,int l,int r,int ql,int qr,int plu1){
		if(ql<=l&&qr>=r){
			f[now].plu=(f[now].plu+plu1)%p;
			f[now].num=(f[now].num+plu1*f[now].size)%p;
			return ;
		}
		if(ql>r||qr<l) return ;
		pushdown(now);
		int mid=(l+r)>>1;
		modify2(now*2,l,mid,ql,qr,plu1);
		modify2(now*2+1,mid+1,r,ql,qr,plu1);
		pushup(now);
	}
	int qry(int now,int l,int r,int ql,int qr){
		if(ql<=l&&qr>=r) return f[now].num;
		if(ql>r||qr<l) return 0;
		pushdown(now);
		int mid=(l+r)>>1;
		return (qry(now*2,l,mid,ql,qr)+qry(now*2+1,mid+1,r,ql,qr))%p;
	}
}tree;
int t[200005];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) t[i]=a[i];
	sort(t+1,t+n+1);
	t[0]=0;
	t[n+1]=t[n]+1;
	for(int i=1;i<=n+1;i++) b[i]=t[i]-t[i-1];
	for(int i=1;i<=n;i++) a[i]=lower_bound(t+1,t+n+1,a[i])-t;
	n++;
	tree.build(1,1,n);
	tree.modify2(1,1,n,n,n,1);
	for(int i=1;i<n;i++){
//		cout<<tree.qry(1,1,n,1,n)<<" "; 
		int sum=tree.qry(1,1,n,1,n);
		tree.modify1(1,1,n,1,a[i],p-1);
		tree.modify1(1,1,n,a[i]+1,n,0);
		tree.modify2(1,1,n,1,a[i],sum);
	}
	cout<<tree.qry(1,1,n,1,n);
	return 0;
}
```

---

## 作者：SS80194 (赞：0)

退役选手打了打 CF 玩，发现脑子不灵了。

考虑一个暴力 DP ，设 $f_{i,j}$ 表示处理到第 $i$ 个， $b_i = j$ 的方案数，则转移方程为：
$$
f_{i,j}=
\left\{
    \begin{aligned}
    \sum_{j'=1}^{b_{i-1}}f_{i-1,j'}-f_{i-1,j} (j \leq b_i)  \\
    0 (j > b_i)
    \end{aligned}
\right.
$$

首先有一个关键结论：把 $a$ 数组排序，在 $(a_i,a_{i+1}]$ 区间的答案全部是相同的。因此，有用的 $j$ 其实只有 $O(n)$ 个。可以把 $j$ 的一维搬到线段树上，具体来说，以 $j$ 为下标 $f_{i,j}$ 为权值开一棵线段树。从 $i$ 转移到 $i+1$ 直接在线段树上修改。

注意对于同一个 $i$ 的所有 $j$ 来说， $\sum_{j'=1}^{b_{i-1}}f_{i-1,j'}$ 都是一个定值，于是这个线段树只用支持三种操作：
- 区间取相反数
- 区间赋 $0$
- 区间加

看着不太好维护。注意到区间取相反数本质上是区间 $\times -1$ ，区间赋 $0$ 本质上是区间 $\times 0$ ，直接写一个类似 P3373 的区间乘，区间加的线段树即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long lld;
const lld mdx=998244353;
const int maxn=2e5+900;
const int maxT=1e6+800;
int n,m,a[maxn],b[maxn],ind[maxn],nx=0;
int tl[maxT],tr[maxT];lld val[maxT],mul[maxT],add[maxT];
int getid(int x){return lower_bound(ind+1,ind+m+1,x)-ind;}
int ls(int x){return (tl[x]==tr[x]?0:2*x);}
int rs(int x){return (tl[x]==tr[x]?0:2*x+1);}
int len(int x){return tr[x]-tl[x]+1;}
lld srl(lld x,lld y){return (ind[y]-ind[x-1])%mdx;}
void pushup(int p)
{
	val[p]=((ls(p)?val[ls(p)]:0)+(rs(p)?val[rs(p)]:0))%mdx;
}
void pushdown(int p)
{
	lld pm=mul[p],pa=add[p];mul[p]=1,add[p]=0;
	if(ls(p))
	{
		val[ls(p)]=(val[ls(p)]*pm+1ll*pa*srl(tl[ls(p)],tr[ls(p)]))%mdx;
		add[ls(p)]=(add[ls(p)]*pm+pa)%mdx;
		mul[ls(p)]*=pm;mul[ls(p)]%=mdx;
	}
	if(rs(p))
	{
		val[rs(p)]=(val[rs(p)]*pm+1ll*pa*srl(tl[rs(p)],tr[rs(p)]))%mdx;
		add[rs(p)]=(add[rs(p)]*pm+pa)%mdx;
		mul[rs(p)]*=pm;mul[rs(p)]%=mdx;
	} 
}
void build(int p,int l,int r)
{
	tl[p]=l;tr[p]=r;mul[p]=1;add[p]=0;
	if(l==r){val[p]=((l<=a[1]?1ll:0ll)*srl(l,l))%mdx;return ;}
	int mid=(tl[p]+tr[p])/2;
	if(l<=mid) build(2*p,l,mid);
	if(mid<r) build(2*p+1,mid+1,r);
	pushup(p);
}
void upd1(int p,int l,int r,int k)
{
    if(l>r) return ;
	if(l<=tl[p]&&tr[p]<=r)
	{
		val[p]*=k;val[p]%=mdx;
		mul[p]*=k;mul[p]%=mdx;
		add[p]*=k;add[p]%=mdx;
		return ;
	}
	pushdown(p);int mid=(tl[p]+tr[p])/2;
	if(l<=mid) upd1(ls(p),l,r,k);
	if(mid<r) upd1(rs(p),l,r,k);
	pushup(p);
}
void upd2(int p,int l,int r,int k)
{
    if(l>r) return ;
	if(l<=tl[p]&&tr[p]<=r)
	{
		val[p]+=1ll*(k*srl(l,r))%mdx;
		val[p]%=mdx;
		add[p]+=k;val[p]%=mdx;
		return ;
	}
	pushdown(p);int mid=(tl[p]+tr[p])/2;
	if(l<=mid&&ls(p)) upd2(ls(p),l,r,k);
	if(mid<r&&rs(p)) upd2(rs(p),l,r,k);
	pushup(p);
}
lld query(int p,int l,int r)
{
	if(l<=tl[p]&&tr[p]<=r)
	{
		return val[p];
	}
	pushdown(p);lld ans=0;int mid=(tl[p]+tr[p])/2;
	if(l<=mid&&ls(p)) ans+=query(ls(p),l,r);
	if(mid<r&&rs(p)) ans+=query(rs(p),l,r);
	return ans%mdx;
}
int main()
{
    freopen("1591F.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) ind[i]=a[i];
	sort(ind+1,ind+n+1);m=unique(ind+1,ind+n+1)-ind-1;
	for(int i=1;i<=n;i++) a[i]=getid(a[i]);
    build(1,1,m);
    for(int i=2;i<=n;i++)
    {
        lld dlt=query(1,1,m);
        upd1(1,1,m,-1);upd2(1,1,m,dlt);
        upd1(1,a[i]+1,m,0);
    }
    lld A=query(1,1,m);A%=mdx;A=(A+mdx)%mdx;
    printf("%lld\n",A);
    return 0;
}
```

---

