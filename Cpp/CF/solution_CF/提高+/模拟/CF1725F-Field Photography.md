# Field Photography

## 题目描述

PC 正在前往马纳多。原来，2019年印度尼西亚国家科学奥林匹克运动会正在举行。OSN 2019的参赛者目前正在一个待拍照的场地排队。该场地的形状类似于一个大小为 $N\times 10^{100}$ 的网格，有$N$行和$10^{100}$列。行从北到南从 $1$ 编号到 $N$ ，列从西到东从 $1$ 编号到 $10^{100}$ 。第 $r$ 行第 $c$ 列的方格坐标为$(r,c)$。

有 $N$ 个省份参加 OSN 2019。最初，代表省 $i$ 的每个参赛者都会站在方格$（i，p）$中，并满足 $L_i\leq p\leq R_i$ 。因此，我们可以看到有 $R_i-L_i+1$ 个参赛者代表省 $i$ 。

PC 的变量 $Z$ 最初等于 $0$ 。在一次操作中，PC 可以选择行 $i$ 和正整数 $k$ 。然后，PC 将执行以下两种操作之一：

- 将第 $i$ 行中的所有参赛者向西移动 $k$ 个方格。换句话说，在 $(i,p)$ 中的选手被移动到 $(i,p-k)$。
- 将第 $i$ 行中的所有参赛者向东移动 $k$ 个方格。换句话说，在 $(i,p)$ 中的选手被移动到 $(i,p+k)$。
每次操作后，$Z$的值将变为$Z~\text{OR}~k$，其中$\text{OR}$是按位或运算. 请注意，PC 可以多次对同一行执行操作。还要注意，PC 不允许将参赛者移出网格。

有 $Q$ 问题。对于第 $j$ 个问题，您将得到一个正整数 $W_j $，PC 必须执行零或更多操作，以便 $Z$ 的最终值正好是 $W_j$ 。将 $M$ 定义为最大的数字，以便在所有操作之后，至少有一列正好包含 $M$ 参赛者。对于每个问题，您必须找到 PC 可以完成的所有操作序列的最大可能 $M$ 。请注意，PC  针对一个问题所做的操作不会延续到其他问题。

## 说明/提示

对于第 $1$ 个问题，PC 可以执行以下操作以获得 $M=2$：

- 将第 $2$ 排中的所有参赛者向东移动 $4$ 块 $Z$ 变为$0~\text{OR}~4=4$。

- 将第 $1$ 排中的所有参赛者向东移动$12$块$Z$变为$4~\text{OR}~12=12$。

现在，每列 $14$ 和 $15$ 正好包含 $2$ 的参赛者。

对于第二个 $2$ 问题，PC可以执行以下操作以获得 $M=3$：

- 将第 $3$ 排中的所有参赛者向东移动 $4$ 块 $Z$ 变为$0~\text{OR}~4=4$。

- 将第 $3$ 排中的所有参赛者向西移动

$1$ 行 $Z$ 变为 $4~\text{OR}~1=5$。

- 将 $1$ 排中的所有参赛者向东移动$5$块$Z$变为$5~\text{OR}~5=5$。

- 将 $1$ 排中的所有参赛者向东移动 $5$ 块 $Z$ 变为 $5~\text {OR}~5=5$。

现在，第 $11$ 列正好包含 $3$ 名参赛者。

下面是第 $2$ 个问题的示例操作说明。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1725F/96c4e396dbeb78690d68d832bbe2a7eb2a224808.png)

## 样例 #1

### 输入

```
3
1 5
10 11
8 8
2
12
5```

### 输出

```
2
3```

# 题解

## 作者：Mariposa (赞：3)

显然答案只与 $W$ 的 lowbit 有关。

由于一条很长，前面的位随便操作，我们总可以操作若干次 lowbit 使之回到初始位置。

而我们也可以通过若干次操作 lowbit 使得模 lowbit 同余的位对齐。

于是问题转化为找到出现次数最多的模 lowbit 同余的位。

这个问题我们把每行的左右端点离散化下来做一遍前缀和就好。

时间复杂度 $O(n\log^2 n)$。

```
#include<bits/stdc++.h>
using namespace std;
#define inf 1e9
const int maxn=2e5+10;
const int mod=1e9+7;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int n,m,L[maxn],R[maxn],Ans[maxn],S[maxn],a[maxn];
int main(){
	n=read();
	for(int i=1;i<=n;i++)
		L[i]=read(),R[i]=read();
	for(int k=0;k<=30;k++){
		int tag=0,len=(1<<k),top=0;
		for(int i=1;i<=n;i++)a[++top]=L[i]%len,a[++top]=R[i]%len+1;
		sort(a+1,a+1+top);
		top=unique(a+1,a+1+top)-a-1;
		for(int i=0;i<=top;i++)S[i]=0;
		for(int i=1;i<=n;i++){
			int l=L[i]%len,r=R[i]%len;
			if(R[i]-L[i]>=len){++tag;continue;}
			if(l>r)++tag;
			l=lower_bound(a+1,a+1+top,l)-a;
			r=lower_bound(a+1,a+1+top,r+1)-a;
			++S[l],--S[r];
		}int Mx=0;
		for(int i=1;i<=top;i++)S[i]+=S[i-1];
		for(int i=0;i<=top;i++)Mx=max(Mx,S[i]);
		Ans[k]=Mx+tag;
	}m=read();
	for(int i=1,x;i<=m;i++){
		x=read();
		printf("%d\n",Ans[__lg(x&(-x))]);
	}
    return 0;
}
```

还是蛮搞笑的，但我也只有说 2100 搞笑的水平了。

---

## 作者：cosf (赞：0)

## [CF1725F](https://www.luogu.com.cn/problem/CF1725F)

性质题。

可以发现，答案只和 $W$ 的最低位有关。假设 $W$ 的最低位是 $2^d$，则显然每一次移动的距离一定 $2^d$ 的倍数，所以你完全可以把所有的移动都变成若干次 $2^d$ 的移动，最后再随便挑一个省往右移 $W$ 再移回来即可。

因此，我们只需要处理每一个 $2^d$ 的答案，最后就可以 $O(1) / \text{query}$ 了。

---

即然都是移 $2^d$ 的距离，不难想到在模 $2^d$ 的意义下进行。

考虑（某一个省的）区间 $[l, r]$。

如果 $r - l + 1 \ge 2^d$，则每一个余数都能去到。

否则，如果 $l \bmod 2^d \lt r \bmod 2^d$，则只有余数在 $[l \bmod 2^d, r \bmod 2^d]$ 能够取到。

否则就是 $[0, l\bmod 2^d] \cup [r\bmod 2^d, 2^d - 1]$ 能去到了。

最后再把所有区间求并，看看哪一个点的覆盖次数最多即刻。

---

离散化即可。复杂度 $O(n\log n + q)$（如果把预处理的 $30$ 倍时间看作常数的话）。

---

```cpp
#include <algorithm>
#include <iostream>
using namespace std;

#define MAXN 100005
#define MAXL 31
#define ctz __builtin_ctz

inline int read(int &x);

int n;

struct Sec
{
    int l, r;
} a[MAXN], b[MAXN << 2];
int idx = 0;

int res[MAXL];

void calc(int k) // 1 << k
{
    int m = 1 << k, ad = 0;
    b[idx = 1] = {m, 0};
    for (int i = 1; i <= n; i++)
    {
        if (a[i].r - a[i].l + 1 >= m)
        {
            ad++;
        }
        else if (a[i].r % m >= a[i].l % m)
        {
            b[++idx] = {a[i].l % m, 1};
            b[++idx] = {a[i].r % m + 1, -1};
        }
        else
        {
            b[++idx] = {0, 1};
            b[++idx] = {a[i].r % m + 1, -1};
            b[++idx] = {a[i].l % m, 1};
        }
    }
    sort(b + 1, b + idx + 1, [](Sec a, Sec b)
         { return a.l < b.l; });
    int r = res[k] = ad;
    for (int i = 1; i < idx; i++)
    {
        r += b[i].r;
        if (b[i].l != b[i + 1].l)
        {
            res[k] = max(res[k], r);
        }
    }
}

int main()
{
    read(n);
    for (int i = 1; i <= n; i++)
    {
        read(a[i].l);
        read(a[i].r);
    }
    for (int i = 0; i < MAXL; i++)
    {
        calc(i);
    }
    int q;
    read(q);
    while (q--)
    {
        int w;
        read(w);
        printf("%d\n", res[ctz((unsigned)w)]);
    }
    return 0;
}

```

---

## 作者：huangrenheluogu (赞：0)

这个 *2100 很下饭，我的代码还是很下饭。

考虑一下这个 $10^{100}$ 的含义，就是右边可以无限延伸。

其实这个移动就是 $\operatorname{lowbit}W$ 而已，其中 $\operatorname{lowbit}x$ 表示 $x$ 表示为二进制后最右边的 $1$ 代表的数。比如 $(10101010)_2=(10)_2,(10000)_2=(10000)_2$。

因为或起来是 $W$ 的只能是一堆数，而这个最小的 $\operatorname{lowbit}W$ 就可以整除可能可以移动的所有整数。

然后，我就使用了 $O(NQ)$ 的方法开写，很是下饭。

其实应该是预处理出每个可能的 $\operatorname{lowbit}W$ 然后再 $O(\log W)$ 回答询问。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5, inf = 1e9;
int n, Q, W, aa[N << 2], tot, b[N << 2], kk, idx, x, ans[N];
struct Interval{
	int l, r;
}a[N], upd[N << 1];
inline int gethash(int x){
	return lower_bound(aa + 1, aa + tot + 1, x) - aa;
}
inline int Unique(){
	for(int i = 1; i <= tot; i++) b[i] = 0;
	tot = 0;
	for(int i = 1; i <= idx; i++){
		aa[++tot] = upd[i].l;
		aa[++tot] = upd[i].r + 1;
//		if(W == 8) printf("%d %d\n", upd[i].l, upd[i].r);
	}
	sort(aa + 1, aa + tot + 1);
	tot = unique(aa + 1, aa + tot + 1) - aa - 1;
	for(int i = 1; i <= idx; i++){
		x = gethash(upd[i].l);
		b[x]++;
		x = gethash(upd[i].r + 1);
		b[x]--;
	}
	int ans = 0;
	for(int i = 1; i <= tot; i++){
		b[i] += b[i - 1];
		ans = max(ans, b[i]);
	}
	return ans;
}
int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].l, &a[i].r);
	for(int i = 0, j = 1; j <= inf; j *= 2, i++){
		W = j;
		idx = 0;
		for(int i = 1; i <= n; i++){
			if(a[i].r / W >= a[i].l / W + 2){
				idx++;
				upd[idx].l = 0, upd[idx].r = W - 1;
				continue ;
			}
			if(a[i].r / W == a[i].l / W + 1){
				if(a[i].l % W <= a[i].r % W + 1){
					idx++;
					upd[idx].l = 0, upd[idx].r = W - 1;
				}
				else{
					idx++;
					upd[idx].l = a[i].l % W, upd[idx].r = W - 1;
					idx++;
					upd[idx].l = 0;
					upd[idx].r = a[i].r % W;
				}
			}
			else{
				idx++;
				upd[idx].l = a[i].l % W;
				upd[idx].r = a[i].r % W;
			}
		}
		ans[i] = Unique();
	}
	scanf("%d", &Q);
	while(Q--){
		scanf("%d", &W);
		x = 0;
		while(!(W & 1)) x++, W >>= 1;
		printf("%d\n", ans[x]);
	}
	return 0;
}
```

---

## 作者：TernaryTree (赞：0)

卡 `map` 放离散化题。/oh

考虑 $W$ 为奇数的情况。显然我们可以随便移 $W$ 二进制上为 $1$ 的位，然后最后通过最低位上的 $1$ 一步一步挪，把每个线段都集中到一个地方，从而 $M=n$。

扩展一下，如果 $W$ 的二进制是 $\dots10$ 呢？显然这时高位上的 $1$ 随便挪，然后剩下最小的只能两步两步挪。如果是 $\dots100$ 呢？就是四步四步挪了。所以，答案是只和 $\operatorname{lowbit}(W)$ 有关的，而 $\operatorname{lowbit}(W)$ 只有 $\log W$ 中，考虑暴力算。

枚举 $len=2^d$。对每一个线段左端点与右端点都对 $len$ 取模，然后就是环状的区间加，最后查询全局最大值。差分实现之即可。注意到 $len\le 10^9$，需要 `map`/离散化。

这题的恶心之处在于 `map` 的大常数会被卡 TLE #5，而均摊 $\Theta(1)$ 的 `__gnu_pb_ds::gp_hash_table` 与 `__gnu_pb_ds::cc_hash_table` 均无序，直接替换 map 会 WA #3，而换成有序写起来可能还不如离散化好写。

核心代码：

```cpp
for (int d = 0; d < maxd; d++) {
	int m = 1ll << d, tot = 0;
	cnt = 0;
	for (int i = 1; i <= n; i++) b[++cnt] = l[i] % m, b[++cnt] = r[i] % m;
	sort(b + 1, b + 1 + cnt);
	cnt = unique(b + 1, b + 1 + cnt) - b - 1;
	for (int i = 1; i <= cnt + 1; i++) s[i] = 0;
	for (int i = 1; i <= n; i++) {
		if (r[i] - l[i] + 1 >= m) {
			++tot;
			continue;
		}
		int ql = l[i] % m, qr = r[i] % m;
		ql = lower_bound(b + 1, b + 1 + cnt, ql) - b;
		qr = lower_bound(b + 1, b + 1 + cnt, qr) - b;
		if (ql > qr) ++tot;
		s[ql]++, s[qr + 1]--;
	}
	int mx = 0;
	for (int i = 1; i <= cnt + 1; i++) {
		s[i] += s[i - 1];
		mx = max(mx, s[i]);
	}
	ans[d] = tot + mx;
}
```

---

