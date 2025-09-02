# 「HGOI-1」Binary search

## 题目背景

$\text{bh1234666}$ 正在学习[二分查找](https://baike.baidu.com/item/%E4%BA%8C%E5%88%86%E6%9F%A5%E6%89%BE/10628618?fr=aladdin)。

## 题目描述

众所周知二分查找的 $\text{mid}$ 在计算时可以取 $\lfloor\dfrac{l+r}{2}\rfloor$ 或者 $\lceil\dfrac{l+r}{2}\rceil$，于是有选择困难症的 $\text{bh1234666}$ 同学在自己的二分查找代码中加入了随机化，每次随机选取其中的一个作为 $\textit{mid}$。

注意，选取不同的 mid 其他参数也会受到影响，请以代码为准。

现在 $\text{bh1234666}$ 给你了二分查找使用的序列（保证为单调递增）以及他想要寻找的数（保证在序列内），他想知道在运气最好的情况下循环需要进行几次（即代码中 $\textit{cnt}$ 的可能的最终值的最小值）。

循环：
```cpp
int find(int *num,int x,int len)
{
	int l=0,r=len-1,mid,cnt=0,w;
	while(l<r)
	{
		cnt++;
		w=rand()%2;
		mid=(l+r+w)/2;
		if(num[mid]-w<x) l=mid+!w;
		else r=mid-w;
	}
	return mid;
}
```
递归：
```
int cnt;
int get(int *num,int x,int l,int r)
{
	if(l==r) return l;
	cnt++;
	int w=rand()%2;
	int mid=(l+r+w)/2;
	if(num[mid]-w<x) return get(num,x,mid+!w,r);
	else return get(num,x,l,mid-w);
}
int find(int *num,int x,int len)
{
	cnt=0;
	return get(num,x,0,len-1);
}
```
注：以上两代码完全等价。

在此对上述代码中的 $w$ 的作用做进一步阐释。

例如对于区间 $[0,7]$，有 $8$ 个成员。虽然 $mid$ 的取值会因为 $w$ 的取值改变而改变，但是最终确定的区间一定是 $[0,3]$ 或 $[4,7]$，选手可以就上述代码自行模拟。

对于区间 $[0,6]$，有 $7$ 个成员。$\textit{mid}$ 的取值与 $w$ 的取值无关，但是 $l$ 和 $r$ 的取值会受到 $w$ 的影响，最终确定的区间可能是 $[0,2]$，$[3,6]$（$w=1$）或 $[0,3]$，$[4,6]$（$w=0$）。

## 说明/提示

### 样例 1 解释

找 $4$：

取 $[1,5]$。

取 $[1,3]$。

取 $[3,3]$（退出循环）。

### 样例 2 解释

查询 $10$ 的位置。

$$
[1,13] \stackrel{w=0}{\longrightarrow} [1,7]\stackrel{w=0}{\longrightarrow}[5,7] \stackrel{w=1}{\longrightarrow} [5,5]
$$

### 数据范围及约定
本题采用**捆绑测试**，共有 $3$ 个 $\text{subtask}$，最终分数为所有 $\text{subtask}$ 分数之和。

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|}\hline
\textbf{Task} & \textbf{Score} & \text{特殊限制} \cr\hline
1 & 25 & n \le 20 \cr\hline
2 & 35 & n=2^k(k \in \mathbf{N}) \cr\hline
3 & 40 &  \cr\hline
\end{array}
$$

对于 $100\%$ 的数据，保证 $1 \le n \le 2^{20}$，$1 \le q \le 100$，$1 \le num_i \le 10^9$。

本题有 [extra sub](https://www.luogu.com.cn/problem/P8487)。

## 样例 #1

### 输入

```
10
1 2 4 6 7 8 10 13 15 17
3
4
10
15```

### 输出

```
3
3
3```

## 样例 #2

### 输入

```
13
1 2 4 6 10 12 19 23 45 99 101 123 134
5
1
2
10
19
123
```

### 输出

```
3
4
3
3
4```

# 题解

## 作者：bh1234666 (赞：14)

看到这题第一反应可能是贪心，二分时每次使区间最小，但是这样做是不正确的。因为直接贪心时靠前的操作权值$^*$小，靠后的操作权值大，靠前的决策会影响靠后的决策，即权值小的决策影响权值大的决策，显然不正确。

$^*$ 此处权值定义较复杂，可以简单理解为对后续长度产生影响（缩短 $1$）的概率。

例如对于 $n=13$,查询序列的第 $5$ 个（下标为 $4$，接下来的位置均指下标）。直接贪心过程为：
$$
[0,12] \stackrel{w=1}{\longrightarrow}  [0,5] \stackrel{w=0}{\longrightarrow} [3,5] \stackrel{w=1}{\longrightarrow} [4,5] \stackrel{w=0}{\longrightarrow} [4,4]
$$

但实际上有更优解法：

$$
[0,12] \stackrel{w=0}{\longrightarrow} [0,6]\stackrel{w=0}{\longrightarrow}[4,6] \stackrel{w=1}{\longrightarrow} [4,4]
$$

第一步贪心看似比最优解短了 $1$ ,贪心的下一步使得查找的值出现在了中部，导致 $ [3,5] \stackrel{w=1}{\longrightarrow} [4,5]$ 这一步无法使得长度折半。而贪心前面短的那一步最优解在下一步除二时除掉了，而在更靠后的 $[4,6] \stackrel{w=1}{\longrightarrow} [4,4]$ 比贪心短了 $1$。

对于 $\text{sub2}$ ，发现每次 $w$ 的值不会影响答案，直接输出 $\log_2 n$ 即可。

发现询问次数只有 $100$ 次，直接暴力。为便于实现，可以采用递归实现的二分，每次递归时分两类递归取最小即可。

由于递归层数为 $\log_2 n$ 层，每层分两种情况，最终复杂度为 $O(nq)$，可以通过此题。


核心代码：

```
int find(int k,int f,int l)
{
	if(f==l) return 0;
	int mid=(f+l)>>1,ret=32;
	if(mid<k) ret=find(k,mid+1,l);
	else ret=find(k,f,mid);
	mid=(f+l+1)>>1;
	if(mid<=k) ret=min(ret,find(k,mid,l));
	else ret=min(ret,find(k,f,mid-1));
	return ret+1;
}
int main()
{
	int i,n,q,k;
	scanf("%d",&n);
	for(i=0;i<n;i++)
		scanf("%d",num+i); 
	scanf("%d",&q);
	while(q--)
	{
		scanf("%d",&k);
		for(i=0;i<n;i++)
			if(num[i]==k) break;
		printf("%d\n",find(i,0,n-1));
	}
	return 0;
}
```


---

## 作者：见贤思齐_Seakies (赞：5)

### [题目链接](https://www.luogu.com.cn/problem/P8481)

------------
### 题意概述

按照题目中的代码进行二分查找（详见题目链接），求最小的可能查找次数。

------------
### 题目分析

第一次看题，想到贪心，每次查找使剩余的查找区间尽可能小。

其实，这样连样例也过不了，是有后效性的，可以自己模拟题目样例。

后来，仔细读了一遍题中给出的两段代码，看了一下数据范围，发现 $n≤2 
^{20}$，平均查找次数是 20 次，完全可以用爆搜过掉此题。

以题中给出的递归代码为基础，爆搜时，分 `w = 0` 和 `w = 1` 两种情况进行搜索，取两者的最小值即可。

详见代码。

------------
### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e7 + 9;
int n, q;
int a[MAXN];
int ans = 1e9;
inline int read() {
	int X = 0; bool flag = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') flag = 0; ch = getchar();}
	while (ch >= '0' && ch <= '9') {X = (X << 1) + (X << 3) + ch - '0'; ch = getchar();}
	if (flag) return X;
	return ~(X - 1);
}
inline void write(int X) {
	if (X < 0) {X = ~(X - 1); putchar('-');}
	if (X > 9) write(X / 10);
	putchar(X % 10 + '0');
}
inline void get(int *num, int x, int l, int r, int cnt) {
	int w, mid;
	if (l == r) {
		ans = min(cnt, ans); // 搜索到边界了，更新答案，取最小值
		return;
	}
        // 题目给出的原代码为 w = rand() % 2，说明 w 只能为 1 或 0
	w = 0, mid = (l + r + w) / 2; // w = 0 的情况
	if (num[mid] - w < x) get(num, x, mid + !w, r, cnt + 1);
	else get(num, x, l, mid - w, cnt + 1);
	w = 1, mid = (l + r + w) / 2; // w = 1 的情况
	if (num[mid] - w < x) get(num, x, mid + !w, r, cnt + 1);
	else get(num, x, l, mid - w, cnt + 1);
    // 这里直接用原代码即可
}
inline int find(int *num, int x, int len) {
	ans = 1e9;
	get(num, x, 1, len, 0);
	return ans;
}
int main() {
	n = read();
	for (int i = 1; i <= n; i++) {
		a[i] = read();
	}
	q = read();
	while (q--) {
		int x;
		x = read();
		write(find(a, x, n)); puts("");
	}
	return 0;
} 
```
------------

### 题目推荐
<https://www.luogu.com.cn/problem/P8444>

<https://www.luogu.com.cn/problem/P8467>

<https://www.luogu.com.cn/problem/P1182>

<https://www.luogu.com.cn/problem/P2249>

都是比较简单的题，仅供参考


---

## 作者：JackMerryYoung (赞：3)

# 前言

月赛 T2, 纯暴力可还行。

# 正文

第一眼我们想到的应该是贪心，每次尽可能使得区间最小，但是手模几组数据就发现是错的。可是为什么错了？

因为你前面的决策缩小长度的可能小于后面的决策缩小长度的可能，而前面的决策影响后面的决策，显然不正确。

那么再回头看看题面。看一眼数据范围发现 $\mathcal{O}(NQ)$ 做法竟然能过，于是直接上 DFS 暴搜：

先抄出题人的板子，然后直接枚举 $w$, 把题目里面的 $w$ 设置为 $0, 1$, 都分别去跑一遍二分。

这样递归下去，当二分查找到要求的数时，结束，将递归层数取个最小值。

最终的最小值就是我们的答案了。注意第一层 DFS 的层数是 $0$ 啊！

理论上是 $\mathcal{O}(NQ)$ 的，应该可以通过（可见你谷评测机有多强）。

# 代码

伪代码：

``` python
Func binary_search(num[], x, l, r, step):
	If(l == r):
        ans = min(ans, step)
        Ret None
        
    mid = (l + r) / 2;
    If(num[mid] < x):
        binary_search(num[], x, mid + 1, r, step + 1)
    Else:
        binary_search(num[], x, l, mid, step + 1)
        
    mid = (l + r + 1) / 2;
    If(num[mid] - 1 < x):
        binary_search(num[], x, mid, r, step + 1)
    Else:
        binary_search(num[], x, l, mid - 1, step + 1)
        
... <- Input

For Each Query:
    x = read()
    ans = INF
    binary_search(arr[], x, 0, N - 1, 0)
    Write(ans)
```

# 后言

这种题目就先交个暴力试试，实在不行再考虑正解。

---

## 作者：Sktic (赞：2)

[P8481 Binary search](https://www.luogu.com.cn/problem/P8481) & [P8487 Binary search Ex ](https://www.luogu.com.cn/problem/P8487)

注：因为许多人比较习惯于采用 $[1,n]$ 的数组形式，所以本篇题解中默认区间编号为 $[1,n]$ 而不是题目中的 $[0,n-1]$ ，不过不影响理解题意。



题目大意：对于一个离散化后的区间 $[1,n]$ ，二分查找其中的一个位置 $x$，设每次查找的区间为 $[l,r]$ ，每次查找时当区间长度为偶数时下一次查找的区间为 $[l,\frac{r-l+1}{2}]$ 或 $[\frac{r-l+1}{2}+1,r]$ ，当区间长度为奇数时下一次查找的区间为 $[l,\lfloor\frac{r-l+1}{2}\rfloor-1]$ ， $[\lfloor\frac{r-l+1}{2}\rfloor,r]$ ， $[l,\lfloor\frac{r-l+1}{2}\rfloor]$ ， $[\lfloor\frac{r-l+1}{2}\rfloor+1,r]$ ，求最少的查找次数使最终的区间为 $[x,x]$ 。多组样例。



原题目中的数据范围为 $1\le n \le 2^{20},1\le q\le10^2,1\le num\le 10^9$ ，可以考虑采用 $\text{map}$ 离散化后进行暴力 $\text{dfs}$ 查找（因为 $q$ 最多只有 $100$ ）。



注意此题的贪心不可行，因为样例 $2$ 中查询 $10$ 的位置时直接贪心的选取小的区间 $[1,6]$ 会使后来 $10$ 出现在区间中央，使得解法不是最优，于是考虑对每种情况都进行一遍 $dfs$ 取最小值。时间复杂度 $O(nq)$ ，可以通过此题。

AC Code:

```C++
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int a[maxn];
map<int,int>mp;
int dfs(int x,int l,int r)
{
	if(l==r)
		return 0;
	int len=r-l+1,mid=l+r>>1;
	if(len%2==0)
	{
		if(x<=mid)
			return dfs(x,l,mid)+1;
		else
			return dfs(x,mid+1,r)+1;
	}
	else
	{
		if(x<mid)
			return min(dfs(x,l,mid-1),dfs(x,l,mid))+1;
		else if(x>mid)
			return min(dfs(x,mid+1,r),dfs(x,mid,r))+1;
		else
			return dfs(x,l,mid)+1;
	}
	return 10086;
}
int main()
{
	ios::sync_with_stdio(false);
	int n,q,k;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>k;
		mp[k]=i;
	}
	cin>>q;
	for(int i=1;i<=q;i++)
	{
		int x;
		cin>>x;
		x=mp[x];
		cout<<dfs(x,1,n)<<endl;
	}
	return 0;
}
```



对于本题的 $\text{extra sub}$ ，由于数据范围达到了 $1\le n \le2^{60},1\le sumq\le 2^{20}$ ，我们要考虑更优的做法。



由于二分查找，所以答案只能为 $\lfloor\log_2n\rfloor$ ， $\lfloor\log_2n\rfloor+1$ 。考虑寻找其中规律。



通过~~打 表~~观察分析可得，设 $n$ 的二进制开头连续的 $1$ 的个数为 $s$ ，结尾连续的 $0$ 的个数为 $t$ ，当 $2|n$ 时区间长度确定，不会影响下一步操作，故设循环节长 $len=2^t$ ，当 $x$ 对 $len$ 取膜后位于 $len$ 的左右两部分，长度 $\le 2^s-2$ 时此时的答案由奇偶性决定，而在中间部分时（即对于两端的距离均 $>2^s-2$ ）时答案固定为 $\lfloor\log_2n\rfloor$ 。



时间复杂度 $O(q)$ ，可以通过~~80分~~。



因为本题中的 $x$ 过大，取模时速度较慢，由于模数不一定与 $10$ 互质，无法使用蒙哥马利，只能考虑采用 $\text{barrett}$ 加快取模速度。预处理一个常量 $mu=\frac{2^{2\times k}}{len}$ （要求取模的数 $x$ 的位数 $\le2\times k$ 且模数位数 $\le k$ ），则 $mu\times \frac{n}{2^{2\times k}}$ 就等于 $2$ 的近似值，当 $2\times k$ 足够大时，近似值可以~~胡萝卜鸡~~忽略不计，由 $n \bmod p=n-\lfloor\frac{n}{p}\rfloor\times p$ 可得 $n \bmod len=n-len\times mu\times \frac{n}{2^{2\times k}}$ ，若得到的值 $\ge len$ 则减去 $len$ 即可得到正确结果。

于是采用此优化后代码运行速率大大加快，可以通过此题。注意计算时由于数字过大导致溢出 $\text{unsigned long long}$ 的情况。

AC Code（由于修改了 $114514$ 次所以比较丑）:

```C++
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
typedef __uint128_t L;
typedef unsigned long long ull;
ull sd = 111111111111111111ull, sd2, k = 1;
ull qu, n;
ull ans;
inline ull get_q(int i)
{
	sd = (sd2 ^ (sd2 >> 3)) + 998244353;
	return ((sd2 = sd ^ (sd << 37)) & k) + ((i & 1) ? 0 : (n - k - 1));
}
struct FastMod
{
    ull b,m;
    FastMod(ull b):b(b),m(ull((L(1)<<56)/b)){}
    ull reduce(ull a)
    {
        ull q=(ull)((L(m)*a)>>56);
        ull r=a-q*b;
        return r>=b?r-b:r;
    }
};
FastMod F(2);
inline ull log2(ull x)
{
	return 63-__builtin_clzll(x);
} 
ull q, q2;
ull logn,len,t=0,s=0;
ull getzero(ull x)
{
	ull ans=0;
	while((x&1)==0)
	{
		x>>=1;
		ans++;
	}
	return ans;
}
ull getone(ull x)
{
	ull ans=0;
	while(x)
	{
		if(x%2)
			ans++;
		else
			ans=0;
		x>>=1;
	}
	return ans;
}
void init()
{
	t=getzero(n);
	s=getone(n);
	logn=log2(n);
	len=n>>t;
	F=FastMod(len);
}
inline ull get_ans(ull x)
{
	if(n==1)
		return logn;
	x=F.reduce(x);
//	cout<<len<<" "<<x<<endl;
	if(x>len>>1)
		x=len-x-1;
	return (x<((ull)1<<s)-2&&x&1)?logn+(ull)1:logn; 
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> n;
	sd2 = n;
	while((k << 1) <= n + 1) k <<= 1;
	k -= 1;
	cin >> q >> q2;
	init();
	for(int i = 1; i <= q; i++)
	{
		cin >> qu;
		ans += get_ans(qu) * i;
	}
	for(int i = 1; i <= q2; i++)
	{
		qu = get_q(i);
		ans += get_ans(qu) * (i + q);
	}
	cout << ans << endl;
	return 0;
}
```



---

## 作者：Joker_1212 (赞：2)

# P8481 题解

[原题传送门](/problem/P8481)

[更好的阅读体验](/blog/Joker-1212/p8481-cpp)

## 题意理解

原题面已经很简洁，此处不再细说，只想强调一下 $w$ 的作用。

官方给出了如下的解释：

> 在此对上述代码中的 $w$ 的作用做进一步阐释。

> 例如对于区间 $[0,7]$，有 $8$ 个成员。虽然 $mid$ 的取值会因为 $w$ 的取值改变而改变，但是最终确定的区间一定是 $[0,3]$ 或 $[4,7]$，选手可以就上述代码自行模拟。

> 对于区间 $[0,6]$，有 $7$ 个成员。$mid$ 的取值与 $w$ 的取值无关，但是 $l$ 和 $r$ 的取值会受到 $w$ 的影响，最终确定的区间可能是 $[0,2]$，$[3,6]$（$w=1$）或 $[0,3]$，$[4,6]$（$w=0$）。

所以可以得出一个结论：当区间长度为偶数时，最终确定的区间只有一个，否则有两个。

数据范围：

- $1\le n\le 2^{20}$
- $1\le q\le 100$
- $1\le num_i\le 10^9$

## 题目分析

由于每一次的操作都会影响后面的操作，所以这道题并不能用贪心算法求解，尝试暴力求解。

由于每次都会把序列一分为二，所以一个数至多需要 $\lceil\log_2 n\rceil$ 次就能找到（此处为二分性质），而每一次分隔至多产生 $2$ 个区间待查询，所以所有的状态总数最多为 $2^{\log_2 n} = n$。又有 $q$ 次询问，每次都要遍历 $n$ 个状态，时间复杂度为 $\mathcal O(nq)$，对付这道题绰绰有余，因此可以用 DFS 进行求解。

DFS 具体做法：当待分割区间长度为偶数时，选择 $w = 0$，否则将两种 $w$ 值都试一遍，选取最终答案最小的即可。

## 代码实现

```cpp
int ans;

inline void dfs(int *a, int l, int r, int x, int cnt)
{
    if (l == r)
    {
        ans = min(ans, cnt);
        return;
    }
    ++cnt;
    int w = 0;
    int mid = (l + r + w) >> 1;
    if (a[mid] - w < x)
        dfs(a, mid + !w, r, x, cnt);
    else
        dfs(a, l, mid - w, x, cnt);
    if ((r - l + 1) & 1)
    {
        w = 1;
        mid = (l + r + w) >> 1;
        if (a[mid] - w < x)
            dfs(a, mid + !w, r, x, cnt);
        else
            dfs(a, l, mid - w, x, cnt);
    }
}

int main()
{
#ifdef LOCAL
    freopen("./in.in", "rb", stdin);
    freopen("./out.out", "wb", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    ll n;
    read(n);
    int *a = new int[n];
    for (int i = 0; i < n; ++i)
        read(a[i]);
    int q;
    read(q);
    while (q--)
    {
        int x;
        read(x);
        ll l = 0, r = n - 1;
        ans = INT_MAX;
        dfs(a, l, r, x, 0);
        write(ans, 10);
    }
    return 0;
}
```

---

