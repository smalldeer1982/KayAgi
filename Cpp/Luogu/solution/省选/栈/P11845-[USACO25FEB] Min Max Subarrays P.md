# [USACO25FEB] Min Max Subarrays P

## 题目描述

**注意：本题的时间限制为 3 秒，通常限制的 1.5 倍。**

给定一个长为 $N$ 的整数数组 $a_1,a_2,\dots,a_N$（$2\le N \le 10^6$，$1\le a_i\le N$)。输出所有 $N(N+1)/2$ 个 $a$ 的连续子数组的以下子问题的答案之和。

给定一个非空整数列表，交替执行以下操作（从第一个操作开始）直到列表大小恰好为一。

1. 将列表内的两个相邻整数替换为它们的较小值。
1. 将列表内的两个相邻整数替换为它们的较大值。

求最终余下的整数的最大可能值。

例如，

$[4, 10, 3] \to [4, 3] \to [4]$

$[3, 4, 10] \to [3, 10] \to [10]$

在第一个数组中，$(10, 3)$ 被替换为 $\min(10, 3)=3$，随后 $(4, 3)$ 被替换为 $\max(4, 3)=4$。


## 说明/提示

样例 1 解释：

对于 $[2]$ 答案为 $2$，对于 $[1]$ 答案为 $1$，对于 $[2, 1]$ 答案为 $1$。

因此，我们的输出应当为 $2+1+1 = 4$。

样例 3 解释：

考虑子数组 $[2, 4, 1, 3]$。


1. 在 $(1, 3)$ 上应用第一次操作，我们的新数组是 $[2, 4, 1]$。
1. 在 $(4, 1)$ 上应用第二次操作，我们的新数组是 $[2, 4]$。
1. 在 $(2, 4)$ 上应用第三次操作，我们最终的数是 $2$。

可以证明 $2$ 是最终的数的最大可能值。

- 测试点 $4\sim 5$：$N\le 100$。
- 测试点 $6\sim 7$：$N\le 5000$。
- 测试点 $8\sim 9$：$\max(a)\le 10$。
- 测试点 $10\sim 13$：没有额外限制。

## 样例 #1

### 输入

```
2
2 1```

### 输出

```
4```

## 样例 #2

### 输入

```
3
3 1 3```

### 输出

```
12```

## 样例 #3

### 输入

```
4
2 4 1 3```

### 输出

```
22```

# 题解

## 作者：xxxxxzy (赞：5)

模拟赛考了这个题，被硬控 2h，最后没调出来，问候搬题人母亲。

考虑对于一个长度等于奇数的序列，在上面进行一轮操作，手玩发现很大概率都是得到最大值。

继续手玩发现 $n=3$ 的部分情况并不满足，这种情况是最大值在中间，而对于 $n>3$ 都是成立的。

考试时对于这个的一种解释：只有 $n=3$ 且最大值在中间时第一次必然会对周围两个数取 $\min$，所以只能取到次大值，而更大 $n$ 的则可以避免第一次对最大值取 $\min$。

考虑区间长度为偶数，发现很多情况都是取到次大值。

反例手玩就会发现，只会存在于 $4,6$ 中，设 $X,Y$ 为最大，次大值，形如：

+ $n=4:$ ```X..Y```,```X.Y.```,```.X.Y```。
+ $n=6:$ ```.X.Y..```,```..X.Y.```,```.X..Y.```。

考虑证明，因为 $X,Y$ 必须都留到最后然后再取 $\min$，然后考虑类似上面 $n=3$ 一样分析，就可以感性证明。

这样只需要维护所有长度为奇数的区间的最大值和所有长度为偶数的区间的次大值。

这个好（？）维护，直接分治，每次拿个双指针扫就做完了。

真难写，/tuu /tuu /tuu，果然我还是不适合做数据结构，时间 $O(n \log n)$。

Tips：有大神告诉我，不用分类讨论，直接记搜搜出来 $\le 10$ 就行了。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pii pair<ll, ll>
#define mp make_pair
#define pb push_back
#define ld lower_bound
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define drep(i, a, b) for (int i = (a); i >= (b); i--)
#define ud upper_bound
#define mem(s, k) memset(s, k, sizeof(s))
#define cpy(s, t) memcpy(s, t, sizeof(s))
#define fi first
#define se second
#define ull unsigned long long
#define vi vector<int>
#define fv inline void
#define fn inline static
using u16 = unsigned short;
using u32 = unsigned;
using u64 = unsigned ll;
using u128 = __uint128_t;
using i16 = short;
using i32 = ll;
using i64 = ll;
using i128 = __int128_t;
using db = double;
using namespace std;
const int N = 1e6 + 5;
i32 ans = 0;
struct info {
    i32 mx, se;
    info() { mx = se = 0; }
    fv ins(i32 x) {
        if (mx < x)
            se = mx, mx = x;
        else if (se < x)
            se = x;
    }
    friend info operator+(info x, info y) {
        x.ins(y.mx), x.ins(y.se);
        return x;
    }
};
i32 n, m, a[N];
info p[N], q[N];
fv calc(i32 n, i32 m) {
    i32 pos = 0, t[2] = {};
    rep(i, 1, m) {
        while (pos < n && p[pos + 1].mx <= q[i].se) t[(++pos) & 1]++;
        ans += t[i & 1] * q[i].se;
    }
    pos = t[0] = t[1] = 0;
    rep(i, 1, n) {
        while (pos < m && q[pos + 1].mx <= p[i].se) t[(++pos) & 1]++;
        ans += t[i & 1] * p[i].se;
    }
    pos = t[0] = t[1] = 0;
    rep(i, 1, m) {
        while (pos < n && p[pos + 1].mx <= q[i].mx) t[(++pos) & 1] += p[pos].mx;
        ans += t[i & 1];
    }
    pos = t[0] = t[1] = 0;
    rep(i, 1, m) {
        while (pos < n && p[pos + 1].mx <= q[i].se) t[(++pos) & 1] += p[pos].mx;
        ans -= t[i & 1];
    }
    pos = t[0] = t[1] = 0;
    rep(i, 1, n) {
        while (pos < m && q[pos + 1].mx < p[i].mx) t[(++pos) & 1] += q[pos].mx;
        ans += t[i & 1];
    }
    pos = t[0] = t[1] = 0;
    rep(i, 1, n) {
        while (pos < m && q[pos + 1].mx <= p[i].se) t[(++pos) & 1] += q[pos].mx;

        ans -= t[i & 1];
    }
}
fv solve(i32 l, i32 r) {
    if (l == r)
        return;
    i32 mid = (l + r) >> 1;
    solve(l, mid), solve(mid + 1, r);
    i32 n = mid - l + 1, m = r - mid;
    p[0] = q[0] = info();
    rep(i, 1, n) p[i] = p[i - 1], p[i].ins(a[mid - i + 1]);
    rep(i, 1, m) q[i] = q[i - 1], q[i].ins(a[mid + i]);
    calc(n, m);
}
i32 L[N], R[N], stk[N], tp;
int main() {
    IOS;
    freopen("minmax.in", "r", stdin);
    freopen("minmax.out", "w", stdout);
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n) {
        i32 mxp = -1, secp = -1, mx = -1e9, sec = -1e9, thd = -1e9;
        rep(j, i, n) {
            if (a[j] > mx)
                secp = mxp, mxp = j, thd = sec, sec = mx, mx = a[j];
            else if (a[j] > sec)
                secp = j, thd = sec, sec = a[j];
            else if (a[j] > thd)
                thd = a[j];
            if (j - i + 1 == 3) {
                if (mx == a[i + 1])
                    ans += max(a[i], a[j]);
                else
                    ans += mx;
            } else if (j - i + 1 == 4) {
                if (a[i] == mx && a[i + 2] == sec || a[i + 2] == mx && a[i] == sec)
                    ans += max(a[i + 1], a[i + 3]);
                else if (a[i + 1] == mx && a[i + 3] == sec || a[i + 1] == sec && a[i + 3] == mx)
                    ans += max(a[i], a[i + 2]);
                else if (a[i + 1] == mx && a[i + 2] == sec || a[i + 1] == sec && a[i + 2] == mx)
                    ans += max(a[i], a[i + 3]);
                else
                    ans += sec;
            } else if (j - i + 1 == 6) {
                if (abs(secp - mxp) == 2 && secp != i && mxp != i && secp != j && mxp != j)
                    ans += thd;
                else if (abs(secp - mxp) == 3 && secp != i && mxp != i && secp != j && mxp != j)
                    ans += thd;
                else
                    ans += sec;
            } else {
                if ((j - i + 1) & 1)
                    ans += mx;
                else
                    ans += sec;
            }
            ans -= ((j - i + 1) & 1 ? mx : sec);
            if (j - i + 1 >= 6)
                break;
        }
    }
    solve(1, n);
    rep(i, 1, n) {
        while (tp && a[stk[tp]] < a[i]) --tp;
        L[i] = stk[tp] + 1, stk[++tp] = i;
    }
    tp = 0;
    drep(i, n, 1) {
        while (tp && a[stk[tp]] <= a[i]) --tp;
        R[i] = tp ? stk[tp] - 1 : n, stk[++tp] = i;
        i32 vl = i - L[i], vr = R[i] - i;
        i32 p0 = (vl + 2) >> 1, p1 = vl + 1 - p0;
        i32 q0 = (vr + 2) >> 1, q1 = vr + 1 - q0;
        ans += p0 * q0 * a[i] + q1 * p1 * a[i];
    }
    cout << ans;
}
```

---

## 作者：Purslane (赞：5)

# Solution

赛时被这题肘击了，花了一个半小时才过。

---------

先考虑咋做 $01$。也就是你需要判断，能否把一段 $01$ 串用给定的操作变为 $1$。

显然全是 $0$ 不行。

如果有 $\ge 3$ 个 $1$，我们可以不断操作使得两个 $1$ 相邻，这样无论怎么操作都可以保证有至少一个 $1$ 了。

如果有 $1$ 个 $1$，分类讨论发现，最后有 $1$ 等价于有偶数个 $0$，但是 $010$ 除外。

如果有 $2$ 个 $1$，发现只有 $|S|=4$ 或 $6$ 的时候有 $O(1)$ 种情况不能变为 $1$。

~~证明略，毕竟你在打比赛。~~

所以我们得出了计算过程：如果区间长度是奇数返回最大值，否则返回次大值。对于所有长度 $\le 6$ 的区间重新暴力计算即可。

--------

所以我们只需要求出：所有区间长度为奇数的区间最大值和，以及区间长度为偶数的次大值和。

对于前者，只需要维护两侧比他大的第一个数（方便起见，对元素进行双关键字排序）；对于后者，维护两侧比他大的两个数即可。

这一部分只有无聊的分类讨论，略过。

复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e6+10;
int n,a[MAXN],ans,v[MAXN];
set<int> st;
vector<int> rev[MAXN];
int check(int l,int r,int *a) {
	int cnt=0;
	ffor(j,l,r) cnt+=a[j];
	if(cnt>=3) return 1;
	if(cnt==0) return 0;
	if(cnt==1) {
		if((r-l+1)%2==0) return 0;
		if(r-l+1==3&&a[l+1]==1) return 0;
		return 1;
	}
	if(cnt==2) {
		if((r-l+1)==4&&(a[l]==a[l+2]||a[l+1]==a[l+2]&&a[l+1]==1)) return 0;
		if((r-l+1)==6&&(a[l+1]&&a[l+3]||a[l+2]&&a[l+4]||a[l+1]&&a[l+4])) return 0;
		return 1;	
	}
}
int calc(int l,int r) {
	if(l==r) return 0;
	int mx=0;
	vector<int> vc;
	ffor(i,l,r) vc.push_back(a[i]);	
	sort(vc.begin(),vc.end(),[](int A,int B) {return A>B;});
	for(auto id:vc) {
		ffor(i,l,r) v[i]=(a[i]>=id);
		if(check(l,r,v)) return -((r-l+1)%2==0?vc[1]:vc[0])+id;	
	}
}
pair<int,int> ccalc(int l,int r) {
	int c0=0,c1=0;
	c0=r/2,c1=r-r/2;
	c0-=(l-1)/2,c1-=l-1-(l-1)/2;
	return {c0,c1};	
}
int solve1(int a1,int b1,int a2,int b2) {
	auto pr1=ccalc(a1,b1),pr2=ccalc(a2,b2);
	return pr1.first*pr2.first+pr1.second*pr2.second;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>a[i],rev[a[i]].push_back(i);
	roff(i,n,1) for(auto id:rev[i]) {
		int l1=0,l2=0,r1=n+1,r2=n+1;
		auto it=st.lower_bound(id);
		if(it!=st.end()) {
			r1=*it;
			++it;
			if(it!=st.end()) r2=*it;	
		}
		it=st.lower_bound(id);
		if(it!=st.begin()) {
			--it;
			l1=*it;
			if(it!=st.begin()) --it,l2=*it;	
		}
		ans+=i*solve1(1,id-l1,1,r1-id);
		ans+=((l1-l2)*(r1-id)-solve1(id-l1+1,id-l2,1,r1-id)+(r2-r1)*(id-l1)-solve1(r1-id+1,r2-id,1,id-l1))*i;
		st.insert(id);
	}
	ffor(l,1,n) ffor(r,l,min(n,l+5)) ans+=calc(l,r);
	cout<<ans;
	return 0;
}
```

---

## 作者：zhenjianuo2025 (赞：2)

可以发现，对于一个长度 $\ge 7$ 的区间，若区间长度为奇数，实际上可以取到最大值；若区间长度为偶数，由于最后一步是取 min 操作，所以最多只能留下次大值，并且次大值也可以取到。

先按照上面的方法算出所有子区间的答案之和，再把长度 $\le 6$ 的区间单独处理。你当然可以人脑分讨。但是可以离散化成 $1,\ldots,6$ 的排列，提前把所有长度不超过 $6$ 的排列提前爆搜出来直接查表。

考虑如何计算子区间中奇数长度的最大值和偶数长度的次大值之和。第一问是经典的，可以处理出 $i$ 左边第一个大于 $a_i$ 的位置 $l_i$ 和 $i$ 右边第一个大于 $a_i$ 的位置 $r_i$。第二问只需要再找到 $r_i$ 后面的第一个大于 $a_i$ 的位置 $r'_i$ 和 $l_i$ 左边的第一个大于 $a_i$ 的位置 $l'_i$。那么左端点在 $[l'_i+1,l_i]$，右端点在 $[i,r_i-1]$ 中的区间的次大值都是 $a_i$。另一边也是对称的。从大到小扫描 $a_i$，同时分别维护一个向前和一个向后的并查集，时间复杂度 $O(n\alpha(n))$。

---

## 作者：donaldqian (赞：2)

### 1. 闲话
其实这题有点像 [CF2084G1](https://codeforces.com/problemset/problem/2084/G1) 的。

简述一下那道题的题意：给你一个序列，两个人要在这上面做博弈论。先手每次可以将列表内的两个相邻整数替换为它们的较小值（**即本题 $1$ 操作**），且他希望最后剩下的数最大。后手每次可以做**本题 $2$ 操作**，且他希望最后剩下的数最小。那道题的结论是什么呢？对于一段序列 $a_{1\dots n}$，若 $n$ 是奇数，剩下的数就是 $\max(a_1, a_n)$；若 $n$ 是偶数，剩下的数就是 $\min(a_1, a_n)$。

### 2. 思路
那么这道题相当于：先后手都希望剩下的数最大。我们容易发现：当 $n$ 较大且是奇数时，一定能取到序列最大值；当 $n$ 较大且是偶数时，一定能取到序列次大值（因为最后一次是取 $\min$ 所以一定取不到最大值）。稍微手玩一下就能发现 $n\ge 7$ 时都满足这个东西。

然后就好做了，我们用 DS（包括但不限于线段树、从大到小加数然后 set）维护出每个数左右两边 $\ge$ 自己的第一、二个位置，然后分奇偶算一下这个数的贡献即可（这里需要注意细节，因为可能有重复的数，所以可能要钦定最大值/次大值取最左边之类的，防止重复计算）。然后区间长度 $\le 6$ 的大力分讨即可。

---

## 作者：sunkuangzheng (赞：1)

挺有意思的题。

首先考虑怎么求单个序列的答案，不难想到二分答案 $mid$ 转化为 $01$ 问题。两种操作只有在 $(0,1)$ 时有区别：此时一个是删掉 $0$ 一个是删掉 $1$。

> 观察 $1$：含有至少三个 $1$ 的串一定有解。
> 
> 总可以通过若干操作将串化为 $01$ 相间的情况，经过暴力验证所有只包含 $3$ 个 $1$ 的 $01$ 相间的 $01$ 串都有解。

于是我们只需要判定答案是第 $1,2$ 还是第 $3$ 大。

> 观察 $2$：串长大于等于 $4$ 时，只含有 $1$ 个 $1$ 的 $01$ 串有解条件是串长是奇数。
>
> 注意到如果 $1$ 的左右都有偶数个 $0$ 那就显然有解；当串长为奇数且至少为 $5$ 时，如果两侧都是奇数个 $0$ 那可以各操作一次，全都变成偶数。当然这步操作在两侧都只有恰好 $1$ 个 $1$ 时无法进行，因此要求串长至少是 $5$。

对于长度 $\le 4$ 的串可以暴力解决，现在我们剩下的串是长度大于 $4$ 且长度为偶数的串。

> 观察 $3$：串长大于等于 $8$ 时，只包含 $2$ 个 $1$ 的长度为偶数的 $01$ 串一定有解。
>
> 此时 $0$ 的数量是偶数，且形成 $3$ 个连续段。类似的，如果所有段长度都是偶数那就直接有解，否则一定是一个偶数两个奇数。类似的，如果奇数段有长度不为 $1$ 的，那就可以两次操作把这两个都变成偶数。否则，如果偶数段的长度至少为 $4$，就可以用 $4$ 次操作消除奇数段，同时使得偶数段长度减少 $2$。因此长度至少为 $8$ 时必然有解。

我们暴力计算长度小于等于 $8$ 的区间答案，对于更大的区间，如果其长度是奇数则贡献最大值，否则是次大值。我们拆开来求：

- 求所有长度是奇数的区间的最大值的和。
- 求所有长度是偶数的区间的次大值的和。

对于第一个问题，我们直接枚举最大值是谁，单调栈求出其作为最大值的区间 $[l,r]$，则 $[l,r]$ 的任意子区间的最大值都是 $a_i$，容易计算贡献。

对于第二个问题，类似的枚举次大值是谁，求其作为次大值的贡献区间。考虑求出 $i$ 左右两侧前两个大于 $a_i$ 的位置 $l_2,l_1,r_1,r_2$，那么贡献区间有两类：$L \in (l_2,l_1],R \in [i,r_1)$ 和 $L \in (l_1,i],R \in [r_1,r_2)$，贡献也容易计算。

复杂度瓶颈在找 $l_1,l_2,r_1,r_2$，我直接写了线段树二分，复杂度单 $\log$。

---

## 作者：Genius_Star (赞：0)

### 思路：

注意到若区间长度为奇数时，最后一步是取 $\max$ 操作，考虑最大值所处的位置 $Max$，奇数次操作时操作 $Max$ 最右/左边的两个，偶数次操作时操作 $Max$ 和 $Max$ 左边的。

容易证明，当 $len > 6$，$Max$ 最后一定会先跑到某一个边界上去，此时到最后一步操作前都操作另外一边，最后一步即可与 $Max$ 取较大值。

故当 $len > 6$ 时，且 $len$ 为奇数，贡献是区间最大值。

那么当 $len$ 是偶数时，最后一步是取 $\min$ 操作，我们需要使得最后这两个值最小值尽量大，考虑最大值和次大值的位置 $x, y$，设 $x < y$。

每次奇数操作时，取 $(x, y)$ 或 $(y, n]$ 或 $[1, x)$ 的两个数进行；每次偶数操作时，取 $(x \pm 1, x)$ 或 $(y \pm 1, y)$（注意 $x, y$ 之间不要进行操作）。

不难证明，当 $len > 6$ 时，最后肯定只剩下了 $x, y$，故取 $\min(x, y)$。

所以当 $len > 6$ 且 $len$ 为偶数时，贡献是区间次大值。

那么对于 $len \le 6$ 的区间怎么办呢，考虑提前预处理 $len!$ 即所有排列的答案即可。

好的，现在我们的问题是求所有奇数长度区间的最大值贡献之和与偶数长度区间次大值之和。

这是经典的问题，考虑求一个位置的贡献之和，预处理出 $pre_i$ 与 $suf_i$ 表示左右两侧第一个 $>(a_i, i)$ 的位置（注意这里要使用双关键字，因为可能有重复的数）。

次大值的话，也考虑一个位置的贡献，维护左右两侧第一个大于和第二个大于的数的位置即可。

时间复杂度为 $O(N \log N)$。

---

