# [ABC388G] Simultaneous Kagamimochi 2

## 题目描述

有 $N$ 个饼从小到大依次排列。第 $i$ 个饼（$1 \leq i \leq N$）的大小为 $A_i$。

对于两个饼 $A$ 和 $B$，其大小分别为 $a$ 和 $b$，当且仅当 $a$ 不超过 $b$ 的一半时，可以将饼 $A$ 放在饼 $B$ 上，形成一个镜饼。

给定 $Q$ 个整数对。第 $i$ 个整数对为 $(L_i, R_i)$，请对每个 $i$ 解决以下问题：

> 仅使用第 $L_i$ 到第 $R_i$ 个饼（共 $R_i - L_i + 1$ 个饼），最多可以同时制作多少个镜饼？
>
> 更严格地说，求最大的非负整数 $K$，使得：
>
> - 从第 $L_i$ 到第 $R_i$ 个饼中选出 $2K$ 个饼，将其分成 $K$ 对，每对中一个饼放在另一个饼上，形成 $K$ 个镜饼。

## 说明/提示

- $2 \leq N \leq 2 \times 10^5$
- $1 \leq A_i \leq 10^9$（$1 \leq i \leq N$）
- $A_i \leq A_{i+1}$（$1 \leq i < N$）
- $1 \leq Q \leq 2 \times 10^5$
- $1 \leq L_i < R_i \leq N$（$1 \leq i \leq Q$）
- 输入均为整数

### 样例解释 1

每个问题的答案如下所示。镜饼的制作方式为示例：

- 饼的大小为 $(1,2,3,4)$。可以制作 $(1,3)$ 和 $(2,4)$ 两个镜饼。
- 饼的大小为 $(2,3,4,4,7,10)$。可以制作 $(2,4)$、$(3,7)$ 和 $(4,10)$ 三个镜饼。
- 饼的大小为 $(7,10,11,12,20)$。可以制作 $(10,20)$ 一个镜饼。
- 饼的大小为 $(1,1)$。无法制作任何镜饼。
- 饼的大小为 $(1,1,2,3,4,4,7,10,11,12,20)$。可以制作 $(1,2)$、$(1,3)$、$(4,10)$、$(4,11)$ 和 $(7,20)$ 五个镜饼。

因此，请按顺序输出 `2`、`3`、`1`、`0`、`5`。

## 样例 #1

### 输入

```
11
1 1 2 3 4 4 7 10 11 12 20
5
2 5
3 8
7 11
1 2
1 11```

### 输出

```
2
3
1
0
5```

## 样例 #2

### 输入

```
24
127 148 170 174 258 311 331 414 416 436 517 523 532 587 591 638 660 748 760 776 837 857 972 984
15
7 11
8 9
8 13
12 15
9 23
1 17
8 12
1 5
6 17
3 7
12 19
13 18
7 22
1 12
14 15```

### 输出

```
0
0
0
0
2
6
0
1
1
0
0
0
3
5
0```

# 题解

## 作者：Loser_Syx (赞：15)

首先明确一点，在一段连续的区间内，如果存在一个可能的答案 $k$，那么一定可以是前 $k$ 小和前 $k$ 大的组合，显然。

不妨预处理一个 $to_i$ 表示 $i$ 可以与 $[to_i,n]$ 内的组合。

于是我们可以考虑在 $[0,\frac{r-l+1}{2}]$ 内二分答案，对于某个 $i \in [l,l+k-1]$，我们显然要求 $i$ 与 $r-l+1-k+i$ 进行匹配（小对小，大对大），那么就要求 $to_i \leq r-l+1-k+i$，把 $i$ 移项就是 $to_i-i \leq r-l+1-k$。ST 表简单维护即可。

复杂度 $O(n \log n)$。

---

## 作者：rui_er (赞：7)

鉴于本题解书写时洛谷题面暂无中文翻译，为避免可能的歧义或困惑，先对本题解中的译法进行约定：（顺便吐槽音译怪）

- 英文题面中“mochi”或日文题面中“餅”译为“饼”。
- 英文题面中“kagamimochi”或日文题面中“鏡餅”译为“镜饼”。

鉴于本题是 C 和 E 的加强版，而我懒得去写那两题的题解，这里不加证明地给出那两题的做法：

- C：对于每个饼，双指针求出大小不超过其一半的最后一个饼的位置。
- E：二分答案 $k$，check 是否前 $k$ 个饼可以依次和后 $k$ 个饼组合成镜饼。

朴素写法 E 的 check 是 $O(n)$ 的，我们只要将其优化到 $O(1)$，就可以直接套用过来通过本题。

这时候 C 就给了我们启发。我们预处理出 C 的位置数组 $pos$，并定义下标差数组 $dis_i=i-pos_i$。容易发现，二分的答案为 $k$ 时，E 的 check 等价于判断 $\max\limits_{i=r-k+1}^{r}\{dis_i\}\le (r-k+1)-l$ 是否成立。使用 ST 表维护 $dis$ 的区间最值即可。

时间复杂度 $O((n+m)\log n)$。

```cpp
// Problem: G - Simultaneous Kagamimochi 2
// Contest: AtCoder - HHKBプログラミングコンテスト2025(AtCoder Beginner Contest 388)
// URL: https://atcoder.jp/contests/abc388/tasks/abc388_g
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x, y, z) for(int x = (y); x <= (z); ++x)
#define per(x, y, z) for(int x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(y < x) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

template<int mod>
inline unsigned int down(unsigned int x) {
	return x >= mod ? x - mod : x;
}

template<int mod>
struct Modint {
	unsigned int x;
	Modint() = default;
	Modint(unsigned int x) : x(x) {}
	friend istream& operator>>(istream& in, Modint& a) {return in >> a.x;}
	friend ostream& operator<<(ostream& out, Modint a) {return out << a.x;}
	friend Modint operator+(Modint a, Modint b) {return down<mod>(a.x + b.x);}
	friend Modint operator-(Modint a, Modint b) {return down<mod>(a.x - b.x + mod);}
	friend Modint operator*(Modint a, Modint b) {return 1ULL * a.x * b.x % mod;}
	friend Modint operator/(Modint a, Modint b) {return a * ~b;}
	friend Modint operator^(Modint a, int b) {Modint ans = 1; for(; b; b >>= 1, a *= a) if(b & 1) ans *= a; return ans;}
	friend Modint operator~(Modint a) {return a ^ (mod - 2);}
	friend Modint operator-(Modint a) {return down<mod>(mod - a.x);}
	friend Modint& operator+=(Modint& a, Modint b) {return a = a + b;}
	friend Modint& operator-=(Modint& a, Modint b) {return a = a - b;}
	friend Modint& operator*=(Modint& a, Modint b) {return a = a * b;}
	friend Modint& operator/=(Modint& a, Modint b) {return a = a / b;}
	friend Modint& operator^=(Modint& a, int b) {return a = a ^ b;}
	friend Modint& operator++(Modint& a) {return a += 1;}
	friend Modint operator++(Modint& a, int) {Modint x = a; a += 1; return x;}
	friend Modint& operator--(Modint& a) {return a -= 1;}
	friend Modint operator--(Modint& a, int) {Modint x = a; a -= 1; return x;}
	friend bool operator==(Modint a, Modint b) {return a.x == b.x;}
	friend bool operator!=(Modint a, Modint b) {return !(a == b);}
};

const int N = 5e5 + 5;

int n, a[N], m, dis[N];

struct SparseTable {
    int mx[18][N];
    void init(int* a, int n) {
        rep(i, 1, n) mx[0][i] = a[i];
        rep(j, 1, 17) rep(i, 1, n - (1 << j) + 1) mx[j][i] = max(mx[j - 1][i], mx[j - 1][i + (1 << (j - 1))]);
    }
    int ask(int l, int r) {
        if(l > r) return -2e9;
        int k = __lg(r - l + 1);
        return max(mx[k][l], mx[k][r - (1 << k) + 1]);
    }
}st;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    cin >> m;
    int ptr = 0;
    rep(i, 1, n) {
        while(ptr < n && a[ptr + 1] * 2 <= a[i]) ++ptr;
        dis[i] = i - ptr;
        // cout << dis[i] << " \n"[i == n];
    }
    st.init(dis, n);
    rep(i, 1, m) {
        int ql, qr;
        cin >> ql >> qr;
        int l = 0, r = (qr - ql + 1) / 2 + 1;
        while(l < r) {
            int mid = (l + r) >> 1;
            if(st.ask(qr - mid + 1, qr) <= (qr - mid + 1) - ql) l = mid + 1;
            else r = mid;
        }
        cout << l - 1 << endl;
    }
    return 0;
}
```

---

## 作者：Genius_Star (赞：6)

### 思路：

不想多说了，之前写了一个详细点的，结果正好碰上 lg 崩了，一点保存瞬间 504，都没时间备份。

首先注意到对于询问的 $[l, r]$ 肯定是钦定前面一段放上面，后面一段放下面。

于是考虑二分答案 $mid$。

故我们需要对于 $i \in [l, l + mid - 1]$，都满足 $2a_i \le a_{r - l - mid + i + 1}$，此时必然存在答案。

这样看起来很难判断啊，但是由于不带修，直接维护第一个满足 $2a_i \le a_{nxt_i}$ 的 $nxt_i$。

则判断就变为了 $nxt_i \le r - l - mid + i + 1$，移项得 $nxt_i - i \le r - l - mid + 1$。

故我们使用维护 ST 表维护 $nxt_i - i$ 的最大值即可。

时间复杂度为 $O(N \log N)$。

---

## 作者：2huk (赞：5)

显然二分。考虑 check $k$ 是否合法。

根据 E 的思路，显然要把 $[l, l+k-1]$ 这些积木按顺序依次摞到 $[r-k+1,r]$ 上面。我们要判断是否合法。

注意到如果第 $i$ 块积木将要摞在上面，那么它下面的积木应该是 $r-l+1-k+i$。也就是说，$k$ 合法等价于对于所有 $i \in [l, l+k-1]$ 都满足 $2a_i \le a_{r-l+1-k+i}$。

预处理 $p_i$ 表示 $[i+1,n]$ 中第一个 $\ge 2a_i$ 的位置，不存在为无穷大。那么上面那个条件可以等价地写成 $p_i \le r-l+1-k+i$，即 $p_i-i \le r-l+1-k$。

判断「对于所有 $i \in [l, l+k-1]$ 是否都满足 $p_i-i \le r-l+1-k$」，可以求区间 $[l,l+k-1]$ 的 $p_i-i$ 的最大值。静态 RMQ 用 ST 表即可解决。

```cpp
int n, a[N], p[N];
int st[N][20];

int query(int l, int r) {
	int k = log2(r - l + 1);
	return max(st[l][k], st[r - (1 << k) + 1][k]);
}

bool chk(int l, int r, int k) {
	return query(l, l + k - 1) <= r - l + 1 - k;
}

void Luogu_UID_748509() {
	cin >> n;
	
	for (int i = 1; i <= n; ++ i ) {
		cin >> a[i];
	}
	
	for (int i = 1; i <= n; ++ i ) {
		p[i] = lower_bound(a + i + 1, a + n + 1, a[i] * 2) - a;
		if (p[i] == n + 1) p[i] = 1e9;
		// cout << i << " : " << p[i] << '\n';
		p[i] -= i;
		st[i][0] = p[i];
	}
	
	for (int j = 1; j < 20; ++ j )
		for (int i = 1; i + (1 << j - 1) <= n; ++ i )
			st[i][j] = max(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
	
	int q;
	cin >> q;
	while (q -- ) {
		int l, r;
		cin >> l >> r;
		
		int lo = 1, hi = (r - l + 1) / 2, res = 0;
		while (lo <= hi) {
			int mid = lo + hi >> 1;
			if (chk(l, r, mid)) res = mid, lo = mid + 1;
			else hi = mid - 1;
		}
		
		cout << res << '\n';
	}
}
```

---

## 作者：lhz2022 (赞：2)

考虑二分。

我们设 $b_i$ 代表最后一个可以放到 $a_i$ 上面的麻糬的下标与 $a_i$ 的差。

容易发现，$b$ 数组可以 $O(n)$ 计算。

再根据[本场比赛 E 题](https://www.luogu.com.cn/problem/AT_abc388_e)，我们发现，操作的本质就是使找出最大的 $k$ 使得对于任意的 $0\leq i \leq k$ 都有 $a_{l+i}\times 2\leq a_{r-k+i}$。

换句话说，就是区间前 $i$ 个和后 $i$ 个一一队员满足题目中要求的 $2$ 倍关系。

那么这种对应关系就可以转化为 $l+\max_{i=r-k+1}^r b_i \leq r-k+1$。

那么一个很显然的做法就是使用某种数据结构维护 $b$ 的区间最大值。我们可以用 st 表维护，并二分计算 $k$ 的值。

预处理时间复杂度：$O(n \log n)$，单次询问时间复杂度：$O(\log n)$，总复杂度 $O((n+q) \log n)$。

[代码](https://atcoder.jp/contests/abc388/submissions/61643819)

---

## 作者：I_will_AKIOI (赞：2)

感谢巨佬 @[what_can_I_do](/user/658973) 的指点，让我理解并通过了这题。

发现 E 题属于 G 题，所以先考虑 E 题，当然也可以先阅读 E 题的[题解](https://www.luogu.com.cn/problem/solution/AT_abc388_e)。

发现如果答案 $x$ 满足要求，那么 $x-1$ 也可以，所以考虑二分。接着考虑怎么匹配是最优的，由于数组是有序的，所以相邻更远的两个数差值期望是越大的。因此就可以把最小的 $x$ 个数和最大的 $x$ 个数进行比较，也就是把 $a_1\dots a_x$ 和 $a_{n-x+1}\dots a_n$ 依次进行比较，如果不能满足两倍关系，就是不合法的。

接着发现这 $q$ 次询问，二分的复杂度是可以接受的，但是 check 函数复杂度过高，需要优化。

发现在 check 的过程中，匹配的两个数的距离是相同的，不妨先对于每个 $i$ 预处理出最小的 $j$ 使得 $a_j\ge 2a_i$，那么 $i$ 匹配下一个数字至少需要往后跳 $j-i$ 步，把这个数记作 $b_i$，那么二分 $mid$ 的时候，$a_{l+x}$ 需要和 $a_r$ 至少隔 $\max_{i=l}^{l+mid-1} b_i$ 个数字，否则数字就塞不下了，不合法。

对于区间 $\max$ 的问题，由于不带修，直接上一个 ST 表维护就行，码量小还跑得飞快。

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("O3")
#define N 200005
using namespace std;
int n,q,l,r,a[N],f[19][N],Log[N];
int query(int l,int r)
{
	int k=Log[r-l+1];
	return max(f[k][l],f[k][r-(1<<k)+1]);
}
bool check(int mid)
{
	int x=query(l,l+mid-1);
	return l+mid-1+x<=r;
}
int main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=2;i<=n;i++) Log[i]=Log[i>>1]+1;
	for(int i=1;i<=n;i++)
	{
		int j=lower_bound(a+1,a+n+1,a[i]*2)-a;
		f[0][i]=j-i;
	}
	for(int j=1;(1<<j)<=n;j++) for(int i=1;i+(1<<j)<n;i++) f[j][i]=max(f[j-1][i],f[j-1][i+(1<<j-1)]);
	cin>>q;
	while(q--)
	{
		cin>>l>>r;
		int L=0,R=(r-l+1)/2,mid;
		while(L<R)
		{
			mid=L+R+1>>1;
			if(check(mid)) L=mid;
			else R=mid-1;
		}
		cout<<L<<"\n";
	}
	return 0;
}
```

---

## 作者：DengStar (赞：1)

> 约定：称一个区间的“匹配”为从区间挑出若干个互不相交的二元组，使得二元组的第一个元素不超过第二个元素的一半。一个匹配中二元组的数量，称为匹配的大小。

区间询问，不强制在线，我们可以尝试用莫队来解决。

首先考虑怎么扩展和删除端点。这里要用到一个关键结论：如果存在一个大小为 $x$ 的匹配，那它一定可以表示为一个长为 $x$ 的前缀和一个长为 $x$ 的后缀匹配（即第 $i$ 个元素匹配第 $(n - x + 1)$ 个元素）。这个结论比较容易猜，但我不会严格证明。

有了这个结论，我们就能在端点扩展之后，快速更新最大匹配的大小。下面不妨考虑右端点扩展，左端点扩展的情况类似。显然，端点扩展一次，最大匹配的大小最多增加 $1$，因此只需判断最大匹配会不会增加 $1$。

假设扩展之前，区间为 $[L, R]$，最大匹配为 $cnt$。如果扩展后 $cnt$ 增加 $1$，那么根据结论，一定是 $A_{L+cnt}$ 和 $A_{R+1}$ 匹配，直接判断大小关系即可。注意有一个 corner case：当 $cnt$ 的大于区间长度的一半就不用尝试更新 $cnt$ 了，因为此时 $cnt$ 不会变大。

现在已经知道如何 $O(1)$ 扩展，那删除呢？我们发现，要判断删除一个端点后 $cnt$ 会不会 $-1$，等价于判断：对于区间内长度为 $cnt$ 的前缀和等长的后缀，前缀和后缀内的第 $i$ 个数能否一一匹配，这似乎不太好维护。（实际上这可以转化为一个 RMQ 问题，见[这篇题解](https://www.luogu.com.cn/article/1td3rz29)。但能想到这个做法的话就不用莫队了）

但是我们还是能用莫队来做！对于这种扩展容易、删除困难的问题，可以用一种叫做“回滚莫队”的改版莫队来解决。这种算法可以在不能删除的情况下解决问题，并且时间复杂度和莫队一样都是 $O(n \sqrt n)$（假设询问次数 $q$ 和序列长度 $n$ 同阶，下同。）

还是把序列分成 $B$ 块。**对于每个询问，如果其左右端点在同一块，我们就暴力扩展处理**，这样对于单个询问，时间复杂度是 $O(n / B)$ （由于其左右端点在同一块，所以区间长度不超过 $n / B$。）**否则，把询问按左端点所在的块分类，对于左端点在同一块的询问，我们一起处理。**

具体而言，对于左端点在同一块内的询问，先按右端点大小从小到大排序。然后，还是用 $L,R$ 和 $cnt$ 表示当前处理的区间左右端点，和区间内最大匹配的大小。对于左端点在第 $i$ 块的询问，初始化 $L, R$ 为第 $i$ 块的右端点，然后不断令 $R$ 向右扩展。扩展到 $R = j$ 时，如果有某个询问的左端点在第 $i$ 块，而右端点为 $j$，我们就处理这个询问。此时，$R$ 已经到位了，但左端点还在原位，那么我们让左端点向左扩展，直到其到位为止。由于一开始 $L$ 在第 $i$ 块的右端点，所以 $L$ 一直往左移动就能到位。但移动之后，对于之后的询问，$L$ 可能就在它的左端点的左边了，而我们又不能删除，那怎么办呢？这里就是回滚莫队的精髓了：在 $L$ 移动之前，我们先记录下移动前的 $cnt$。移动之后，直接把 $L$ 和 $cnt$ 修改为原来的值，就可以 $O(1)$ 地回到移动前的状态，这就是“回滚”。于是，**对于每个询问，我们都能保证 $L$ 在其左端点的右边，这就规避了删除操作。**

时间复杂度分析：处理左端点在一个块内的询问时，$R$ 是单调增的，最多移动 $n$ 次；对于每个询问，$L$ 最多移动 $n / B$ 次。因此处理左右端点不同块的询问，时间复杂度为 $O(nB + \dfrac{n^2}{B})$，取 $B = \sqrt{n}$ 最优，时间复杂度为 $O(n \sqrt n)$。而处理左右端点同块元素的时间复杂度是相同的，因此这就是回滚莫队的时间复杂度。

[参考代码](https://atcoder.jp/contests/abc388/submissions/61599450)

---

## 作者：dayz_break404 (赞：1)

考虑二分答案 $mid$，可以预先对于每一个位置的数字将第一个大于等于它的两倍的数字位置找出来记为 $a_i$。与 E 的二分思路类似，答案如果合法应该满足 $a_i\le l+len-mid+(i-l)$，转换一下式子得到 $a_i-i\le len-mid$。其中 $len=r-l+1$，即区间长度。维护区间 $a_i-i$ 的最大值即可。

---

## 作者：ztlh (赞：1)

题外话：昨晚的 ABC，由于想开摆，于是开了 unrated，谁知道 G 这么水/ll

## Solution

注意到：

- 对每个 $A_i$ 来说，比它大的可与它组成合法二元组的 $A_j$ 是单调的（即存在 $k$ 使得 $j \geq k$ 时 $A_j \geq A_i \times 2$，$j < k$ 时 $A_j < A_i \times 2$）。此时我们记 $B_i = k - i$
- 若有 $i < j < k < l$ 满足 $(A_i,A_j)$ 与 $(A_k,A_l)$ 合法，则 $(A_i,A_k)$ 与 $(A_j,A_l)$ 也合法

于是，在二元组总数 $K$ 一定时，我们可以贪心地选取区间内最左侧 $K$ 个元素作为 $K$ 个二元组中的较小值，选取区间内最右侧 $K$ 个元素作为 $K$ 个二元组中的较大值，且从左到右一一对应。由上面两条性质容易证明这一定最优。

二分答案，比较 $\max_{L_i \leq j \leq R_i} B_j$（st 表维护即可）与 $R_i - L_i + 1 - K$（即左侧最小值与右侧最小值的距离）即可。时间复杂度 $\mathcal{O} (Q\log N)$。

## Code


```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int n,q,ql,qr;
int a[N];
int b[N];
int st[N][25];
int qlg[N];
inline int query(int l_,int r_){
	int k=qlg[r_-l_+1];
	return max(st[l_][k],st[r_-(1<<k)+1][k]);
}
inline bool check(int m){
	if(!m) return 1;
	return query(ql,ql+m-1)<=qr-ql+1-m;
}
int main(){
	scanf("%d",&n);
	qlg[1]=0;
	for(int i=2;i<=n;i++) qlg[i]=qlg[i/2]+1;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	int t=2;
	for(int i=1;i<=n;i++){
		while(t<=n&&a[i]*2>a[t]) t++;
		if(t>n) b[i]=n+5;
		else b[i]=t-i;
	}
	for(int i=1;i<=n;i++) st[i][0]=b[i];
	for(int j=1;j<=20;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	scanf("%d",&q);
	int ml,mr,mid;
	while(q--){
		scanf("%d%d",&ql,&qr);
		ml=0; mr=(qr-ql+1)>>1;
		while(ml<mr){
			mid=(ml+mr+1)>>1;
			if(check(mid)) ml=mid;
			else mr=mid-1;
		}
		printf("%d\n",ml);
	}
	return 0;
}
```

---

## 作者：HasNoName (赞：1)

### 思路
考虑将每一个位置最近一个大于等于它两倍的数和它之间的距离记录下来。

因为如果一个从 $x$ 到 $x+k-1$ 的字段中，距离最大的距离小于等于 $y-(x+k-1)$，则一定有方法可以使得有 $k$ 组配对。

用 ST 表维护即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005,L=20;
int st[N][L+5],a[N];
int get(int l,int r)//得到l~r中的最长长度
{
    int t=log2(r-l+1);
    return max(st[l][t],st[r-(1<<t)+1][t]);
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,T;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    a[n+1]=2e9;
    int r=1;
    for(int i=1;i<=n;i++)
    {
        while(a[r]<a[i]*2)r++;
        st[i][0]=r-i;//长度
    }
    for(int j=1;j<=L;j++)
        for(int i=1;i+(1<<j)-1<=n;i++)
            st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);//计算ST表
    cin>>T;
    while(T--)
    {
        int x,y,l,r,mid;
        cin>>x>>y;
        l=0;r=(y-x+1)/2;//二分
        while(l<r)
        {
            mid=(l+r+1)>>1;
            if(get(x,x+mid-1)<=y-(x+mid-1))l=mid;
            else r=mid-1;
        }
        cout<<l<<'\n';
    }
    return 0;
}
```

---

## 作者：Redshift_Shine (赞：0)

## 闲话

还好我根据观察排行榜得出了 G 比 F 简单的结论，要不然就要卡死了。

赛后惊喜地发现我对做法和两篇日文题解都不太一样，所以来写一篇题解。

## 题解

由于 Kagamimochi = 镜饼，接下来我会用镜饼来解释我的做法。

我们将组成镜饼的两张饼称为“左饼”和“右饼”。其中，左饼的大小不大于右饼的一半。

由于给出的序列 $A$ 单调不降，对于序列中的每一张饼，将其作为“左饼”时，为了使一个区间内能匹配的镜饼更多，我们总是选择下标最小的可以与其匹配的“右饼”进行匹配。为了实现这一点，我们可以以从后往前的顺序枚举左饼，并使用双指针和并查集查找可以匹配的下标最小的右饼。**注意，这里的右饼不能重复，也就是说每张饼只能被作为右饼使用一次**。

找到最优匹配后，将查询按左端点降序排序，同时将对应的最优匹配位置拍到树状数组上做前缀求和即可。然而有时候会发现查询结果大于答案，这个时候只需要将查询结果与理论最大配对数取最小值即可，因为在这种情况下，只需要取前半部分作为左饼，后半部分作为右饼，即可保证构法成立。

时间复杂度 $O((n+q)\log n)$，但是由于树状数组常数较小，其实际表现可能优于线段树或 ST 表。

## 代码
```cpp
// #define Redshift_Debug
#ifdef Redshift_Debug
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <tuple>
using namespace std;
const int N = 2e5 + 10;
int n, a[N], tr[N], q, f[N], res[N];
using t3i = tuple<int, int, int>;
inline void update(int x, int v)
{
	while (x <= n)
		tr[x] += v, x += (x & -x);
}
inline int query(int x)
{
	int res = 0;
	while (x)
	{
		res += tr[x];
		x -= (x & -x);
	}
	return res;
}
inline int find(int x)
{
	return x == f[x] ? x : f[x] = find(f[x]);
}
inline void merge(int x, int y)
{
	f[find(x)] = find(y);
}
t3i qry[N];
void run()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		f[i] = i;
		scanf("%d", a + i);
	}
	f[n + 1] = n + 1;
	scanf("%d", &q);
	for (int i = 1; i <= q; i++)
	{
		auto &[l, r, id] = qry[i];
		scanf("%d%d", &l, &r);
		l = -l;
		id = i;
	}
	sort(qry + 1, qry + q + 1);
	for (int i = 1, rp = n + 1, rn = n; i <= q; i++)
	{
		auto &[l, r, id] = qry[i];
		l = -l;
		while (rn >= l)
		{
			while (a[rp - 1] >= a[rn] * 2)
				rp--;
			update(find(rp), 1);
			rn--;
			if (find(rp) > n)
				continue;
			merge(rp, find(rp) + 1);
		}
		res[id] = min((r - l + 1) / 2, query(r));
	}
	for (int i = 1; i <= q; i++)
		printf("%d\n", res[i]);
}
int main()
{
#ifdef Redshift_Debug
	auto st = chrono::high_resolution_clock::now();
#endif
	run();
#ifdef Redshift_Debug
	auto ed = chrono::high_resolution_clock::now();
	fprintf(stderr, "%.9lf\n", (ed - st).count() / 1e9);
#endif
}
```

---

## 作者：CatnipQwQ (赞：0)

发现这题是 E 的加强版，所以想到了使用二分，尝试将区间中的前 $mid$ 个 mochi 和后 $mid$ 个 mochi 按顺序两两分成一组，如果不能匹配就肯定不合法。但是这样 check 需要将区间遍历一遍，是不可行的。于是我们就要加速这个过程。联想到这场比赛的 C 题，可以发现如果某个 mochi 可以放在第 $i$ 个 mochi 的上面，那么它必定可以放在第 $j>i$ 个 mochi 的上面。于是记 $r_i$ 为第 $i$ 个 mochi 至少要放在第 $r_i$ 个 mochi 上面（如果它不能放在任何 mochi 上则 $r_i=n+1$），那么它可以用二分在 $O(n\log n)$ 的时间复杂度内得到。对于第 $i$ 个 mochi，若它在询问的区间 $l\sim r$ 中的前 $mid$ 个，那么它会放在第 $r-mid+(i-l+1)$ 个 mochi 上。于是需要满足条件 $r-mid+(i-l+1)\geq r_i$。把左边和 $i$ 有关的部分移到右边，则可以得到 $r-l+1-mid\geq r_i-i$。由于左边的部分和 $i$ 无关，所以右边的部分越大越不容易满足条件。所以我们只需要用 ST 表求出 $l\sim l+mid-1$ 中的 $r_i-i$ 的最小值就可以在 $O(1)$ 的时间复杂度内 check 啦 awa。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005], r[200005], maxx[20][200005], lg[200005];
int query(int l, int r)
{
	int len=lg[r-l+1];
	return max(maxx[len][l], maxx[len][r - (1<<len) + 1]);
}
int main()
{
	int n;
	scanf("%d", &n);
	for(int i=1; i<=n; i++)
		scanf("%d", &a[i]);
	for(int i=n; i>=1; i--)
		r[i]=lower_bound(a+1, a+n+1, a[i]*2) - a;
	lg[0]=-1;
	for(int i=1; i<=n; i++)
	{
		lg[i]=lg[i/2]+1;
		maxx[0][i]=r[i]-i;
	}
	for(int i=1; (1<<i)<=n; i++)
	{
		for(int j=1; j+(1<<i)-1<=n; j++)
			maxx[i][j]=max(maxx[i-1][j], maxx[i-1][j + (1 << (i-1))]);
	}
	int q;
	scanf("%d", &q);
	for(int i=1; i<=q; i++)
	{
		int l,r;
		scanf("%d%d", &l, &r);
		int len=r-l+1, lb=1, rb=len/2;
		while(lb<=rb)
		{
			int mid=(lb+rb) / 2;
			if(query(l,l+mid-1)<=len-mid)
				lb=mid+1;
			else
				rb=mid-1;
		}
		printf("%d\n", lb-1);
	}
	return 0;
}
```

---

## 作者：ZLCT (赞：0)

# [ABC388G] Simultaneous Kagamimochi 2
~~数据结构学傻的做法。~~\
\
看到离线多个区间询问，第一想法是莫队，但是发现不容易 $O(1)$ 维护收缩时答案的变化。\
然后发现每个点都只能向前选择点进行配对，所以我们可以考虑扫描线。\
\
我们将询问挂在右端点的坐标上，从左到右扫，我们思考对于 $a_i$ 会如何产生贡献，显然它可以与所有 $a_j\times 2\le a_i$ 的点进行配对。\
\
那么我们一个直观的思路就是用线段树维护 $f_i$ 表示能与 $i$ 配对的点的个数，那么每扫描到一个点就是一个前缀加，每扫描到一个询问就查询 $[l,i]$ 的 $f$ 最大值并与 $\lfloor{\frac{i-l+1}{2}}\rfloor$，当然由于 $f$ 数组是单调不降的，所以可以认为查询 $f_l$。\
这是为什么呢？\
我们分两种情况讨论：
- 第一种，$f_l\ge\lfloor{\frac{i-l+1}{2}}\rfloor$。这代表我们肯定可以从中间分开按照 C 题的逻辑一个一个一次匹配。
- 第二种，$f_l<\lfloor{\frac{i-l+1}{2}}\rfloor$。那么我们就按照这 $f_l$ 种配对方法进行配对即可。

但是这样显然会有问题，比如下面的例子：$[2,6,6,6]$。\
扫描到最后一个数时我们 $f_1$ 是 $3$，所以按照我们的逻辑答案应该是 $2$，但是显然只能凑成一对。\
\
我们错误的原因是忽略了题目中每个点只能选择一次的条件，于是我们可以开一个 `set` 去存还没被选择配对的位置，那么我们每次配对就选最大的可配对且还未配对位置进行配对。\
这是因为我们扫描线保证了之后的 $r$ 都 $\ge i$，于是我们其实不在乎究竟是哪一个位置与 $j$ 所匹配。\
复杂度常数较大的 $O(n\log n)$。\
[code](https://atcoder.jp/contests/abc388/submissions/61598811)

---

## 作者：Double_Light (赞：0)

考虑 E 题的做法，二分答案 $x$，然后贪心地判断第 $l-1+i$ 个饼是否能够叠在第 $r-x+i$ 个饼上面，其中 $i\in[1,x]$，如果全都可以，那么就能够做出 $x$ 个双层饼。总时间复杂度 $O(n^2\log n)$。

考虑优化。对于每一个饼 $i$，都存在一个 $b_i$，满足饼 $1\sim b_i$ 可以叠到 $i$ 的上面做成双层饼，但是 $b_i+1\sim n$ 号饼不能。由于 $b$ 单调不降，容易用指针从左向右扫求出 $b$ 数组。

考虑二分合法的判断。本质上可以转化为对于每一个 $i\in[1,x]$，$b_{r-x+i}$ 是否都 $\geq l-1+i$，也就是 $(r-x+i)-b_{r-x+i}$ 是否都 $\leq (r-x+i)-(l-1+i)=r-l+1-x$。

发现最后这个式子和 $i$ 没有关系，所以可以预处理出来，求出 $r-x+i-b_{r-x+i}$ 的最大值，与 $r-l+1-x$ 比较即可，只需要线段树维护 $i-b_i$ 的最大值。

总时间复杂度 $O(n\log^2n)$。

```cpp
#include<iostream>
#define mid ((l+r)/2)
#define int long long
using namespace std;
int n;
int a[500005];
int b[500005];
int now=1;
int q;
int tr[2000005];
void pushup(int x){
	tr[x]=max(tr[2*x],tr[2*x+1]);
}
void update(int x,int l,int r,int k,int v){
	if(l==k&&l==r){
		tr[x]=v;
		return ;
	}
	if(k<=mid)update(2*x,l,mid,k,v);
	if(k>mid)update(2*x+1,mid+1,r,k,v);
	pushup(x);
}
int query(int x,int l,int r,int from,int to){
	if(from<=l&&r<=to){
		return tr[x];
	}
	int ans=0;
	if(from<=mid)ans=max(ans,query(2*x,l,mid,from,to));
	if(to>mid)ans=max(ans,query(2*x+1,mid+1,r,from,to));
	return ans;
}
bool check(int x,int l,int r){
	if(query(1,1,n,r-x+1,r)<=r-l+1-x)return 1;
	return 0;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		while(a[now]<=a[i]/2)now++;
		b[i]=now-1;
	}
	for(int i=1;i<=n;i++){
		update(1,1,n,i,i-b[i]);
	}
	cin>>q;
	while(q--){
		int ll,rr,ans=0;
		cin>>ll>>rr;
		int l=0,r=(rr-ll+1)/2;
		while(l<=r){
			if(check(mid,ll,rr)){
				ans=mid;
				l=mid+1;
			}
			else r=mid-1;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

