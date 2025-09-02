# Non-Palindromic Substring

## 题目描述

A string $ t $ is said to be $ k $ -good if there exists at least one substring $ ^\dagger $ of length $ k $ which is not a palindrome $ ^\ddagger $ . Let $ f(t) $ denote the sum of all values of $ k $ such that the string $ t $ is $ k $ -good.

You are given a string $ s $ of length $ n $ . You will have to answer $ q $ of the following queries:

- Given $ l $ and $ r $ ( $ l < r $ ), find the value of $ f(s_ls_{l + 1}\ldots s_r) $ .

 $ ^\dagger $ A substring of a string $ z $ is a contiguous segment of characters from $ z $ . For example, " $ \mathtt{defor} $ ", " $ \mathtt{code} $ " and " $ \mathtt{o} $ " are all substrings of " $ \mathtt{codeforces} $ " while " $ \mathtt{codes} $ " and " $ \mathtt{aaa} $ " are not.

 $ ^\ddagger $ A palindrome is a string that reads the same backwards as forwards. For example, the strings " $ \texttt{z} $ ", " $ \texttt{aa} $ " and " $ \texttt{tacocat} $ " are palindromes while " $ \texttt{codeforces} $ " and " $ \texttt{ab} $ " are not.

## 说明/提示

In the first query of the first test case, the string is $ \mathtt{aaab} $ . $ \mathtt{aaab} $ , $ \mathtt{aab} $ and $ \mathtt{ab} $ are all substrings that are not palindromes, and they have lengths $ 4 $ , $ 3 $ and $ 2 $ respectively. Thus, the string is $ 2 $ -good, $ 3 $ -good and $ 4 $ -good. Hence, $ f(\mathtt{aaab}) = 2 + 3 + 4 = 9 $ .

In the second query of the first test case, the string is $ \mathtt{aaa} $ . There are no non-palindromic substrings. Hence, $ f(\mathtt{aaa}) = 0 $ .

In the first query of the second test case, the string is $ \mathtt{abc} $ . $ \mathtt{ab} $ , $ \mathtt{bc} $ and $ \mathtt{abc} $ are all substrings that are not palindromes, and they have lengths $ 2 $ , $ 2 $ and $ 3 $ respectively. Thus, the string is $ 2 $ -good and $ 3 $ -good. Hence, $ f(\mathtt{abc}) = 2 + 3 = 5 $ . Note that even though there are $ 2 $ non-palindromic substrings of length $ 2 $ , we count it only once.

## 样例 #1

### 输入

```
5
4 4
aaab
1 4
1 3
3 4
2 4
3 2
abc
1 3
1 2
5 4
pqpcc
1 5
4 5
1 3
2 4
2 1
aa
1 2
12 1
steponnopets
1 12```

### 输出

```
9
0
2
5
5
2
14
0
2
5
0
65```

# 题解

## 作者：wosile (赞：10)

定义 $k$-good 字符串是：**存在**非回文的长度为 $k$ 的子串的字符串。

场上我读成了任意，然后虚空调试 50 分钟。

很明显对于大部分的 $k$ 和字符串 $s$，一个字符串都是 $k$-good 的。那我们就观察一下非 $k$-good 的字符串有什么性质。

首先，所有字符串都不是 $1$-good 的。
如果 $|s|=k$ 并且 $s$ 是回文串，那么 $s$ 不是 $k$-good 的。

若 $s$ 不是 $k$-good 的，并且 $k<|s|$，那么 $s_1s_2s_3\dots s_k$ 和 $s_2s_3s_4\dots s_{k+1}$ 都是回文串。所以 $s_1=s_k=s_3=s_{k-2}=s_5=\dots=s_{2x+1}=s_{k-2y}$。

如果 $k$ 是偶数，就有 $s$ 的所有字符相等，即 $s_i=s_j$。

如果 $k$ 是奇数，就有 $s$ 是由两个字符交替出现构成的，即 $s_{2x+c}=s_{2y+c}$。

我们可以说明以上命题的逆命题也成立。

所以，一个字符串：

- 一定不是 $1$-good 的；
- $k=|s|$ 时，当且仅当这个字符串回文时不是 $|s|$-good 的；
- $k=2x+1<|s|$ 时，当且仅当所有字符都相同时不是 $k$-good 的；
- $k=2x<|s|$ 时，当且仅当是由两个字符交替构成的（即 `abababab` 的形式）时不是 $k$-good 的。

所以，我们需要快速判断一个字符串是否回文，是否所有字符相同，是否交替相同。判断完之后等差数列求和即可。

判断回文可以用 manacher 预处理或者哈希，后两个可以通过统计 $s_i=s_{i-1}$ 和 $s_i=s_{i-2}$ 的位置个数来判断。

时间复杂度 $O(\sum |s|+\sum q)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n,Q;
int p[400005];
char s[400005];
int s1[200005],s2[200005];

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&Q);
		scanf("%s",s+1);
    	for(int i=1;i<=n;i++){
    		s1[i]=s1[i-1]+(s[i]==s[i-1]);
    		if(i>1)s2[i]=s2[i-1]+(s[i]==s[i-2]);
		}
		s[0]='~',s[n+n+2]='}';
		for(int i=n;i>=1;i--)s[i+i]=s[i];
		for(int i=1;i<=n+1;i++)s[i+i-1]='|';
		int r=0,mid=0;
		for(int i=0;i<=n+n+1;i++)p[i]=0;
		for(int i=1;i<=n+n;i++){
	    	if(i<=r)p[i]=min(p[(mid<<1)-i],r-i+1);
	    	while(s[i-p[i]]==s[i+p[i]])p[i]++;
	    	if(p[i]+i>r)r=p[i]+i-1,mid=i;
    	}
		while(Q--){
			int L,R;
			scanf("%d%d",&L,&R);
			int len=(R-L+1);
			long long ans=1LL*len*(len+1)/2-1;
			int le=len-(len&1);
			int lo=len-(1^len&1);
			if(s2[R]-s2[L+1]==len-2)ans-=1LL*(3+lo)*(lo/2)/2;
			else if(len%2==1 && p[L+R]>=len)ans-=lo;
			if(s1[R]-s1[L]==len-1)ans-=1LL*(2+le)*(le/2)/2;
			else if(len%2==0 && p[L+R]>=len)ans-=le;
			printf("%lld\n",ans);
		}
	}
	return 0;
	//quod erat demonstrandum
}
```

---

## 作者：wxzzzz (赞：7)

### 题意

若一个字符串的有至少一个长度为 $k$ 的字串不是回文串，则称其为 $k-\operatorname{good}$ 串。

给定一个字符串 $s$，$q$ 组询问，每次给定 $l,r$，求能使 $s_l\sim s_r$ 为 $k-\operatorname{good}$ 串的所有 $k$ 之和。

### 思路

前置：[回文自动机](https://www.cnblogs.com/wangxuzhou-blog/p/character-string.html#%E5%9B%9E%E6%96%87%E8%87%AA%E5%8A%A8%E6%9C%BA)

若一个串的所有长度为 $k$ 的子串都是回文串，定义其为 $k-\operatorname{bad}$ 串。

手画几组数据就会发现，$k-\operatorname{bad}$ 串其实是有规律的：

1. $k=1$ 显然是。

1. 若 $k$ 为奇数 $k-\operatorname{bad}$ 串必然形如这样：$\tt ababab,aaaaaa$。

1. 若 $k$ 为偶数 $k-\operatorname{bad}$ 串必然形如这样：$\tt aaaaaa$。

所以，若 $s_l\sim s_r$ 全部相同，所有 $k-\operatorname{bad}$ 的 $k$ 之和为 $\displaystyle\sum_{k=1}^n k$。

否则，若 $s_l\sim s_r$ 交错排列，所有 $k-\operatorname{bad}$ 的 $k$ 之和为 $\displaystyle\sum_{k=1}^n k[k\bmod 2=1]$。

另外，若 $s_l\sim s_r$ 以上两点都不满足，还有一种情况：$s_l\sim s_r$ 为回文串，所有 $k-\operatorname{bad}$ 的 $k$ 之和为 $(r-l+1)+1$。

对于判断 $s_l\sim s_r$ 是否为回文串，可以建出 PAM，在后缀链上倍增，判断以 $r$ 为右端点的最大的长度大于等于 $r-l+1$ 的最小回文串长度是否为 $r-l+1$ 即可。

答案就是 $\displaystyle\sum_{k=1}^n k$ 减去所有 $k-\operatorname{bad}$ 的 $k$ 之和。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n, q, idt, last, rt[200005], len[200005], mps[200005], t[200005][26], f[200005][25];
char s[200005];
struct node {
    int l, r, val;
    bool flag;
} ts[2][200005 << 2];
void pushup(int g, int p) {
    if (ts[g][p << 1].val == -1) {
        ts[g][p].val = ts[g][p << 1 | 1].val;
        ts[g][p].flag = ts[g][p << 1 | 1].flag;
    } else if (ts[g][p << 1 | 1].val == -1) {
        ts[g][p].val = ts[g][p << 1].val;
        ts[g][p].flag = ts[g][p << 1].flag;
    } else {
        ts[g][p].flag = (ts[g][p << 1].flag & ts[g][p << 1 | 1].flag);
        ts[g][p].flag &= (ts[g][p << 1].val == ts[g][p << 1 | 1].val);
        ts[g][p].val = ts[g][p << 1].val;
    }
}
void build(int g, int p, int l, int r) {
    ts[g][p].l = l, ts[g][p].r = r;

    if (l == r) {
        ts[g][p].flag = 1;

        if ((l & 1) == g)
            ts[g][p].val = s[l] - 'a';
        else
            ts[g][p].val = -1;

        return;
    }

    int mid = l + r >> 1;
    build(g, p << 1, l, mid);
    build(g, p << 1 | 1, mid + 1, r);
    pushup(g, p);
}
node query(int g, int p, int l, int r) {
    if (ts[g][p].l >= l && ts[g][p].r <= r)
        return ts[g][p];

    int mid = ts[g][p].l + ts[g][p].r >> 1;

    if (l <= mid && mid < r) {
        node ls, rs, ret;
        ls = query(g, p << 1, l, r);
        rs = query(g, p << 1 | 1, l, r);

        if (ls.val == -1)
            return rs;
        else if (rs.val == -1)
            return ls;
        else {
            ret.flag = (ls.flag & rs.flag);
            ret.flag &= (ls.val == rs.val);
            ret.val = ls.val;
        }

        return ret;
    }

    if (l <= mid)
        return query(g, p << 1, l, r);

    if (mid < r)
        return query(g, p << 1 | 1, l, r);
}
int get(int pos, int p) {
    while (s[pos - 1 - len[p]] != s[pos])
        p = mps[p];

    return p;
}
int insert(int pos, int x) {
    int p = get(pos, last);

    if (!t[p][x]) {
        mps[++idt] = t[get(pos, mps[p])][x];
        t[p][x] = idt;
        len[idt] = len[p] + 2;
    }

    last = t[p][x];
    return last;
}
bool check(int l, int r) {
    int p = rt[r];

    for (int i = 20; i >= 0; i--)
        if (len[f[p][i]] >= r - l + 1)
            p = f[p][i];

    return len[p] == r - l + 1;
}
long long calc(int x, int y) {
    return 1ll * (x + y) * (y - x + 1) / 2;
}
int main() {
    cin >> T;

    while (T--) {
        for (int i = 0; i <= idt; i++) {
            len[i] = mps[i] = 0;

            for (int j = 0; j < 26; j++)
                t[i][j] = f[i][j] = 0;
        }

        idt = 1, last = 0;
        mps[0] = 1, len[1] = -1;

        for (int i = 1; i <= n * 4; i++)
            ts[0][i] = ts[1][i] = {0, 0, 0, 0};

        cin >> n >> q;

        scanf("%s", s + 1);

        for (int i = 1; i <= n; i++)
            rt[i] = insert(i, s[i] - 'a');

        for (int i = 1; i <= idt; i++)
            f[i][0] = mps[i];

        for (int j = 1; j <= 20; j++)
            for (int i = 1; i <= idt; i++)
                f[i][j] = f[f[i][j - 1]][j - 1];

        build(0, 1, 1, n);
        build(1, 1, 1, n);

        while (q--) {
            int l, r;
            cin >> l >> r;

            if (l == r) {
                cout << "1\n";
                continue;
            }

            long long cnt = 1;
            if (query(0, 1, l, r).flag && query(1, 1, l, r).flag) {
                if (s[l] == s[l + 1])
                    cnt = calc(1, r - l + 1);
                else if ((r - l + 1) & 1)
                    cnt = 1ll * (r - l + 2) * ((r - l + 2) / 2) / 2;
                else
                    cnt = 1ll * (r - l + 1) * ((r - l + 1) / 2) / 2;
            } else if (check(l, r))
                cnt = r - l + 2;

            cout << calc(1, r - l + 1) - cnt << '\n';
        }
    }

    return 0;
}
```

---

## 作者：AKPC (赞：6)

考虑 $\texttt{k-good}$ 串的性质。

- 不存在 $k=1$ 的 $\texttt{k-good}$ 串，因为单个字符是回文串。
- 对于 $k$ 等于该字符串长度的情况，只要这个串是回文串，那么这个串就不是 $\texttt{k-good}$ 串，因为这个字符串的长度 $k$ 的子串只有本身，反之就是。
- 除去以上情况，把剩余情况分两部分：
	- $k$ 是偶数，只有这个串全部是同一个字符组成才不是 $\texttt{k-good}$ 串。
	- $k$ 是奇数，只有这个串全部同一个字符构成，或者仅两个字符且交替排布的时候，它才不是 $\texttt{k-good}$ 串。

考虑如何解决本题：

- 对于 $k=1$，不要把 $k=1$ 算进去即可。
- 对于 $k$ 等于该字符串长度的情况，考虑给这个字符串算前后缀哈希值，然后根据回文串性质：回文串反过来还是其本身来判断是否回文。建议实现多哈希避免哈希出现误差，特别是打 CF，比如我写的是四哈希；也不建议使用 $64$ 位无符号整型来自然溢出，如果运气比较好可能不会有什么事，反正我会莫名奇妙地被卡在第 $13$ 个点（雾）。
- 对于剩下两种情况，全部同一个字符的判断可以判断区间内字符 ASCLL 码最大、小值是否相等，可以 ST 表，两种字符交替需要对奇、偶位置来开 ST 表。

那么这个题就做完了，对于每个测试点，预处理复杂度 $\Theta(n\log n)$ 的（这主要是因为 ST 表，不过使用分块四毛子可以卡到平均 $\Theta(n)$，最劣 $\Theta(n\sqrt n)$），单次查询 $\Theta(1)$。

[code](/paste/vrjuwxl9)，感觉有蓝吧？

---

## 作者：xuyiyang (赞：3)

### Solution
首先看看 $k$-good 串的充要条件。以下记字符串长度为 $l$。

- 没有 $1$-good 串。证明显然。
- $l$-good 串只要满足 $S$ 不为回文串。证明显然。
- $2k+1$-good（$2k+1<l$）串，只要满足 $S$ 不是两个字符交替出现。证明：令 $S=s_1s_2\dots s_qs_{q+1}\dots$，若 $S$ 不是 good 串，则 $s_1s_2\dots s_{2k+1}$，$s_2s_3\dots s_{2k+2}$ 回文，从而推出 $s_1=s_{2k+1}=s_3=s_{2k-1}=\dots$，即得性质。
- $2k$-good（$2k<l$）串，只要满足 $S$ 不是只包含一个字母。证明：同性质 3。

所以只需将总的减去不合法的，即不是 $k$-good 串的个数算出即可。需要判断区间回文，可以 Hash。
对于区间全部相等或交替出现，考虑随机赋权，判断区间和是否等于单个字母即可。对于交替出现，分奇偶考虑，于是就做完了。时空复杂度线性。需要写双 Hash。
### Code
```cpp
const int N = 2e5 + 10;

mt19937 Rand(time(0));
int n, q;
char s[N];
LL w[27];
LL s1[N], s2[N], s3[N];

struct Hash {
	LL mod, P;
	LL h1[N], h2[N], p[N];
	void init() {
		p[0] = 1; for (int i = 1; i <= n; i ++ ) p[i] = p[i - 1] * P % mod;
		for (int i = 1; i <= n; i ++ ) h1[i] = (h1[i - 1] * P + s[i] - 'a' + 1) % mod;
		for (int i = n; i >= 1; i -- ) h2[i] = (h2[i + 1] * P + s[i] - 'a' + 1) % mod;
	}
	bool chk(int l, int r) {
		LL hl = (h1[r] - h1[l - 1] * p[r - l + 1] % mod + mod) % mod;
		LL hr = (h2[l] - h2[r + 1] * p[r - l + 1] % mod + mod) % mod;
		return hl == hr;
	}
} H1, H2;

void solve() {
	scanf("%d%d", &n, &q); scanf("%s", s + 1); H1.mod = 1e9 + 7, H1.P = 10003, H2.mod = 998244353, H2.P = 41; H1.init(), H2.init();
	for (int i = 1; i <= 26; i ++ ) w[i] = Rand();
	for (int i = 1; i <= n; i ++ ) s1[i] = s1[i - 1] + w[s[i] - 'a' + 1];
	for (int i = 1; i <= n; i += 2) s2[i] = s2[i - 2] + w[s[i] - 'a' + 1];
	for (int i = 2; i <= n; i += 2) s3[i] = s3[i - 2] + w[s[i] - 'a' + 1];
	while (q -- ) {
		int l, r; scanf("%d%d", &l, &r); int len = r - l + 1;
		LL res = (LL)len * (len + 1) / 2 - 1;
		if (s1[r] - s1[l - 1] == w[s[l] - 'a' + 1] * len) {
			int t = (len % 2 == 0 ? len : len - 1);
			if (t >= 2) res -= (LL)(2 + t) * t / 4;
		} else if (len % 2 == 0 && H1.chk(l, r) && H2.chk(l, r)) res -= len;
	//	printf("%lld\n", res);
		
		int _l = (l % 2 == 1 ? l : l + 1), _r = (r % 2 == 1 ? r : r - 1);
		bool flg = 1; flg &= ((s2[_r] - s2[_l - 2]) == w[s[_l] - 'a' + 1] * (_r - _l + 2) / 2);
		_l = (l % 2 == 0 ? l : l + 1), _r = (r % 2 == 0 ? r : r - 1);
		flg &= ((s3[_r] - s3[_l - 2]) == w[s[_l] - 'a' + 1] * (_r - _l + 2) / 2);
		if (flg) { 
			int t = (len % 2 == 1 ? len : len - 1);
			if (t >= 3) res -= (LL)(3 + t) * (t - 1) / 4;
		} else if (len % 2 == 1 && H1.chk(l, r) && H2.chk(l, r)) res -= len;
		printf("%lld\n", res);
	} return void();
}
```

---

## 作者：Lu_xZ (赞：1)

[Link](https://codeforces.com/contest/1944/problem/D)

场上思路出的最快的一题，~~但没调出来~~。

反着考虑全为回文串需满足哪些情况。

若 $k = 1$，没有限制条件。

若 $k = 2$，对于任意三个位置 $\_$ $\_$ $\_$，先填 $x$ $x$ $\_$，然后二三也要回文，第三位只能是 $x$，最终整段区间全部相同。

若 $k = 3$，全部相同的情况肯定满足，考虑出现不同元素：
+ $\_$ $\_$ $\_$ $\_$
+ $x$ $\_$ $x$ $\_$
+ $x$ $y$ $x$ $\_$

此时二到四段也要回文，最终 $x$ $y$ $x$ $y$ 交替出现。

以此类推 $k > 3$ 的情况，得到结论：

**奇数需间隔排列或全相等，偶数只能全相等**。

此处有一特殊情况，若 $k = r - l + 1$，那么只要整段不回文，就有 $r - l + 1$ 的贡献。

#### 如何快速判断区间全部相等？

只需维护 $lst_i$ 表示前一个与 $s_i$ 不同的元素的位置，最后判断 $lst_r < l$。

具体实现：

```cpp
	vector<int> lst(n, -1);
	for(int i = 1; i < n; ++ i) {
		if(s[i] != s[i - 1]) lst[i] = i - 1;
		else lst[i] = lst[i - 1];
	}
```

#### 如何快速判断元素交替出现？
维护 $f(i, pre)$ 表示从 $i$ 起，前一位的值是 $pre$ 的交替段向左延伸的最大长度。

这里再维护一个 $L_i = i - f(i, s_{i - 1}) + 1$ 得到区间左端点，判断 $L_r \le l$。

```cpp
	vector<vector<int>> f(n, vector<int>(128, 1));
	vector<int> L(n, 0);
	for(int i = 1; i < n; ++ i) {
		f[i][s[i - 1]] = 1 + f[i - 1][s[i]];
		L[i] = i - f[i][s[i - 1]] + 1;
	}
```

#### 如何判断区间是否回文？

可以 $manacher$，但我不会，这里用字符串哈希解决。

代码：
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
#define per(i, a, b) for(int i = (a); i >= (b); -- i)
using namespace std;
using ll = unsigned long long;
constexpr int N = 2e5 + 5, B = 131, P = 1e9 + 7;

ll pre[N], pw[N] = {1};
ll h[N], t[N];
ll H(int l, int r) {return (h[r] - (h[l - 1] * pw[r - l + 1]) % P + P) % P;}
ll T(int l, int r) {return (t[r] - (t[l - 1] * pw[r - l + 1]) % P + P) % P;}

void init(ll *a, string &s) {
	a[0] = s[0];
	for(int i = 1; i < s.length(); ++ i) {
		a[i] = (a[i - 1] * B + s[i]) % P; 
	}
}

void solve() {
	int n, m; cin >> n >> m;
	string s; cin >> s;
	string _ = s;
	reverse(_.begin(), _.end());
	init(h, s);
	init(t, _);
	
	vector<int> lst(n, -1);
	for(int i = 1; i < n; ++ i) {
		if(s[i] != s[i - 1]) lst[i] = i - 1;
		else lst[i] = lst[i - 1];
	}
	
	vector<vector<int>> f(n, vector<int>(128, 1));
	vector<int> L(n, 0);
	for(int i = 1; i < n; ++ i) {
		f[i][s[i - 1]] = 1 + f[i - 1][s[i]];
		L[i] = i - f[i][s[i - 1]] + 1;
	}
	
	for(int i = 0; i < m; ++ i) {
		int l, r; cin >> l >> r;
		-- l, -- r;
		if(lst[r] < l) cout << 0 << '\n';
		else {
			ll len = r - l + 1;
			ll ans = (len - 1) * len / 2;
			ans --;
			if(L[r] <= l) {
				ans -= pre[len - 1];
			}
			if(H(l, r) != T(n - r - 1, n - l - 1)) ans += len;
			cout << ans << '\n';
		}
	}
}

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	for(int i = 3; i <= 2e5; ++ i) pre[i] = pre[i - 1] + (i & 1) * i;
	for(int i = 1; i <= 2e5; ++ i) pw[i] = pw[i - 1] * B % P;
	int T = 1;
	cin >> T;
	while(T --) solve();
	return 0;
}
```

---

## 作者：Alex_Wei (赞：1)

### [CF1943B Non-Palindromic Substring](https://www.luogu.com.cn/problem/CF1943B)

考虑非 $k$-好串的性质，即所有 $k$-子串都是回文串。

- 对于 $k$ 为奇数且 $k\neq 1$ 且 $k\neq |t|$，如果 $t$ 不是 $k$-好的，则考虑 $t_{1\sim k}$ 和 $t_{2\sim k + 1}$。设 $m = \frac {k + 1} 2$。对于 $t_{1\sim k}$，要求 $t_{m - i} = t_{m + i}$。对于 $t_{2\sim k + 1}$，要求 $t_{m + 1 - i} = t_{m + 1 + i}$，于是有 $t_m = t_{m + 2} = t_{m - 2} = t_{m + 4} = \cdots$ 以及 $t_{m + 1} = t_{m - 1} = t_{m + 3} = t_{m - 3} = \cdots$，即 $t$ 有长度为 $2$ 的循环节（不一定是整循环）。

  对每个位置 $i$ 记录最小的 $j$ 使得 $s_j = s_{j + 2} = \cdots = s_i$ 以回答询问。

- 对于 $k$ 为偶数且 $k\neq |t|$，如果 $t$ 不是 $k$-好的，则考虑 $t_{1\sim k}$ 和 $t_{2\sim k + 1}$。设 $m = \frac k 2$，若 $m$ 是偶数，则
  $$
  t_1 = t_k = t_3 = t_{k - 2} = t_5 = \cdots = t_{m - 1} = t_{m + 2} = t_{m + 1} = t_m = t_{m + 3} = \cdots = t_2 = t_{k + 1}
  $$
  $m$ 是奇数的情况类似。本质是连边形成了螺旋结构。于是 $t$ 的所有字符全部相等。

- 对于 $k = 1$，$t$ 不是 $1$-好的。

- 对于 $k = |t|$，$t$ 不是 $k$-好的当且仅当 $t$ 是回文串。使用 Manacher 或哈希判断回文。

时间复杂度 $\mathcal{O}(n + q)$。[代码](https://codeforces.com/contest/1943/submission/251717454)。

---

## 作者：Shunpower (赞：1)

我草，青青草原题。~~你们这些 coach 天天 hack 别人哈希干嘛啊。~~

-------

讲个赛时做法：

下面我们称 $len$ 为（查询的）字符串长度。

考虑这个 $k$-good 的条件其实很容易就满足了，所以我们考虑如何才能不 $k$-good。

显然对于任何串而言 $k=1$ 一定不行，$k=len$ 的情况可以直接使用马拉车或者哈希判定本身是不是回文。

考虑平凡的 $k$。可以发现，取出每一个 $k$ 长子串的过程类似一个滑动窗口，而我们每移动一格就把相等的字符位连在一起（因为不 $k$-good 一定是每一个 $k$ 长子串都回文）。手玩一下可以发现这东西非常漂亮：

对于 $k$ 是偶数，可以发现，只要能够移动一次（所以要先排除掉 $k=len$ 的情况），那么整个串都会连通在一起。换句话说，对于 $k$ 是偶数，**不** $k$-good 当且仅当整个串全部由一种字符构成。下面画了 $k=4$ 的滑动窗口式的连法：

![](https://cdn.luogu.com.cn/upload/image_hosting/ch3spj8e.png)

对于 $k$ 是奇数，可以发现，只要能够移动一次，那么整个串的奇数位和偶数位就会分别连通在一起。换句话说，对于 $k$ 是奇数，**不** $k$-good 当且仅当整个串的奇数位都是相同字符，整个串的偶数位都是相同字符。下面画了 $k=5$ 的滑动窗口式的连法：

![](https://cdn.luogu.com.cn/upload/image_hosting/8voq4y5y.png)

那么现在我们就知道该怎么做了：显然 $k=1$ 不 $k$-good。先检验 $k=len$ 是不是 $k$-good 的，然后检验整个串是不是完全由同种字符构成，如果是则所有偶数都**不** $k$-good；再检验整个串的奇数位和偶数位是否分别由同种字符构成，如果是则所有奇数都**不** $k$-good。

考虑解决询问，检验 $k=len$ 前面已经说过可以马拉车或者哈希。

检验奇偶 $k$ 可以垒三类前缀和实现：某个字符在 $i$ 及其之前在所有位、偶数位、奇数位上出现的次数。

判定 $[l,r]$ 是否由同种字符构成，就相当于判定是否存在一个字符在 $[l,r]$ 的所有位上都出现，很容易用第一个前缀和数组完成。而判定奇数偶数位上是否分别为同种字符，我们可以考虑把所有字符在 $[l,r]$ 中奇数位、偶数位的出现次数全部塞进一个可重集，只要这个集合里面在 $len$ 为偶数时有两个 $\frac{len}{2}$，在奇数是各有一个 $\frac{len-1}{2},\frac{len+1}{2}$。很容易可以证明这个判定是充要的，且这个判定很容易用后两个前缀和数组完成。

这个“塞进可重集”操作不需要用 `map`，直接用数组最后在清空一遍就行了。

于是总时间复杂度 $\mathcal O(n\Sigma)$，相当好写，我赛时一发过了。

特别注意用哈希判定回文的时候可能会被各种卡哈希，据 StayAlone 声称判断 $\text{hash}(l,r)=\text{hash}(r,l)$ 更难卡，为了保险还是写多哈希或者马拉车的好。

[代码](https://codeforces.com/contest/1944/submission/251855634)（不是赛时的，赛时写抽了带 $\log$ 而且常数很大）

---

## 作者：Priestess_SLG (赞：0)

还是想介绍一下我的巨大哈希做法。

题目本身是比较简单的，就是直接分类讨论：

+ $k=1$，此时任何串都是回文的，一定不是 good。
+ $k=r-l+1$，此时若整串回文，则不是 good，否则是 good。可以用三哈希处理。
+ $2\mid k$，此时若字符串内所有字符全都相同，则所有偶数长度均非 good，否则均为 good。
+ $2\nmid k$，此时若字符串内所有奇数位置和偶数位置的字符分别全都相同，则所有奇数长度均非 good，否则均为 good。

对于 $k=r-l+1$ 的情况，可以写 $6$ 个哈希，其中三个为正哈希，三个为反哈希，来判断串是否回文。对于 $2\mid k$ 的情况，可以使用前缀和处理然后暴力统计区间内出现了多少个字符，时间复杂度为 $O(\omega)$ 其中 $\omega$ 取字符集大小即 $26$。对于 $2\nmid k$ 的情况，考虑对原串分别维护奇数位置的哈希和偶数位置的哈希，然后再维护 $26$ 个哈希分别表示长度为 $i$ 字符全为 $j$ 的串的哈希值。查询的时候直接 $O(\omega)$ 暴力判断答案是否可行即可。

写起来十分痛苦。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 200010;
int n, q;
char s[N], s1[N], s2[N];
const int base1 = 131, base2 = 1331, base3 = 13331;
const int mod1 = 998244353, mod2 = 1e9 + 7, mod3 = 218105633;
int b1[N], b2[N], b3[N], h1[N], h2[N], h3[N], h4[N], h5[N], h6[N], pre[N][26];
int h7[N], h8[N], h9[N], h10[N], h11[N], h12[N];
int h13[N][26], h14[N][26], h15[N][26];
int get(int *h, int *b, int m, int l, int r) {
    return (h[r] - h[l - 1] * b[r - l + 1] % m + m) % m;
}
int chk(int l, int r) {
    return get(h1, b1, mod1, l, r) == get(h4, b1, mod1, n - r + 1, n - l + 1) &&
           get(h2, b2, mod2, l, r) == get(h5, b2, mod2, n - r + 1, n - l + 1) &&
           get(h3, b3, mod3, l, r) == get(h6, b3, mod3, n - r + 1, n - l + 1);
}
signed main() {
    cout << fixed << setprecision(15);
    // cin.tie(0)->sync_with_stdio(false);
    int T, tc;
    cin >> T;
    tc = T;
    int ca = 1;
    b1[0] = b2[0] = b3[0] = 1;
    for (int i = 1; i < N; ++i) {
        b1[i] = b1[i - 1] * base1 % mod1;
        b2[i] = b2[i - 1] * base2 % mod2;
        b3[i] = b3[i - 1] * base3 % mod3;
    }
    for (int i = 0; i < 26; ++i)
        for (int j = 1; j < N; ++j) {
            h13[j][i] = (h13[j - 1][i] * base1 + (i + 'a')) % mod1;
            h14[j][i] = (h14[j - 1][i] * base2 + (i + 'a')) % mod2;
            h15[j][i] = (h15[j - 1][i] * base3 + (i + 'a')) % mod3;
        }
    while (T--) {
        cin >> n >> q;
        scanf("%s", s + 1);
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < 26; ++j) pre[i][j] = pre[i - 1][j];
            ++pre[i][s[i] - 'a'];
        }
        for (int i = 1; i <= n; ++i) {
            h1[i] = (h1[i - 1] * base1 % mod1 + s[i]) % mod1;
            h2[i] = (h2[i - 1] * base2 % mod2 + s[i]) % mod2;
            h3[i] = (h3[i - 1] * base3 % mod3 + s[i]) % mod3;
        }
        for (int i = 1; i <= n; ++i) {
            h4[i] = (h4[i - 1] * base1 % mod1 + s[n-i+1]) % mod1;
            h5[i] = (h5[i - 1] * base2 % mod2 + s[n-i+1]) % mod2;
            h6[i] = (h6[i - 1] * base3 % mod3 + s[n-i+1]) % mod3;
        }
        int i1 = 0, i2 = 0;
        for (int i = 1; i <= n; ++i) {
            if (i & 1) {
                s1[++i1] = s[i];
            } else {
                s2[++i2] = s[i];
            }
        }
        for (int i = 1; i <= i1; ++i) {
            h7[i] = (h7[i - 1] * base1 % mod1 + s1[i]) % mod1;
            h8[i] = (h8[i - 1] * base2 % mod2 + s1[i]) % mod2;
            h9[i] = (h9[i - 1] * base3 % mod3 + s1[i]) % mod3;
        }
        for (int i = 1; i <= i2; ++i) {
            h10[i] = (h10[i - 1] * base1 % mod1 + s2[i]) % mod1;
            h11[i] = (h11[i - 1] * base2 % mod2 + s2[i]) % mod2;
            h12[i] = (h12[i - 1] * base3 % mod3 + s2[i]) % mod3;
        }
        while (q--) {
            int l, r;
            cin >> l >> r;
            if (l == r) cout << "0\n";
            else {
                int len = r - l + 1;
                if (chk(l, r)) {
                    int cnt = 0;
                    for (int i = 0; i < 26; ++i)
                        if (pre[r][i] != pre[l - 1][i]) ++cnt;
                    if (cnt == 1) cout << "0\n";
                    else if (cnt == 2) {
                        int ok1 = 0, ok2 = 0;
                        int lp = l / 2 + 1, rp = (r + 1) / 2;
                        int _len = rp - lp + 1;
                        for (int i = 0; i < 26; ++i) {
                            if (h13[_len][i] == get(h7, b1, mod1, lp, rp) && h14[_len][i] == get(h8, b2, mod2, lp, rp) && h15[_len][i] == get(h9, b3, mod3, lp, rp)) {
                                ok1 = 1;
                                break;
                            }
                        }
                        lp = (l + 1) / 2, rp = r / 2;
                        _len = rp - lp + 1;
                        for (int i = 0; i < 26; ++i) {
                            if (h13[_len][i] == get(h10, b1, mod1, lp, rp) && h14[_len][i] == get(h11, b2, mod2, lp, rp) && h15[_len][i] == get(h12, b3, mod3, lp, rp)) {
                                ok2 = 1;
                                break;
                            }
                        }
                        int ok = ok1 && ok2;
                        if (!ok) {
                            cout << (len - 1) * len / 2 - 1 << '\n';
                            continue;
                        }
                        int tlen = len / 2;
                        int res = (1 + tlen) * tlen;
                        if (len % 2 == 0) res -= len;
                        cout << res << '\n';
                    } else cout << (len - 1) * len / 2 - 1 << '\n';
                } else {
                    int cnt = 0;
                    for (int i = 0; i < 26; ++i)
                        if (pre[r][i] != pre[l - 1][i]) ++cnt;
                    if (cnt == 1) cout << "0\n";
                    else if (cnt == 2) {
                        int ok1 = 0, ok2 = 0;
                        int lp = l / 2 + 1, rp = (r + 1) / 2;
                        int _len = rp - lp + 1;
                        for (int i = 0; i < 26; ++i) {
                            if (h13[_len][i] == get(h7, b1, mod1, lp, rp) && h14[_len][i] == get(h8, b2, mod2, lp, rp) && h15[_len][i] == get(h9, b3, mod3, lp, rp)) {
                                ok1 = 1;
                                break;
                            }
                        }
                        lp = (l + 1) / 2, rp = r / 2;
                        _len = rp - lp + 1;
                        for (int i = 0; i < 26; ++i) {
                            if (h13[_len][i] == get(h10, b1, mod1, lp, rp) && h14[_len][i] == get(h11, b2, mod2, lp, rp) && h15[_len][i] == get(h12, b3, mod3, lp, rp)) {
                                ok2 = 1;
                                break;
                            }
                        }
                        int ok = ok1 && ok2;
                        if (!ok) {
                            cout << (len + 1) * len / 2 - 1 << '\n';
                            continue;
                        }
                        int tlen = len / 2;
                        cout << (1 + tlen) * tlen << '\n';
                    } else cout << (len + 1) * len / 2 - 1 << '\n';
                }
            }
        }
    }
    return 0;
}
```

---

## 作者：zhlzt (赞：0)

假设 $len = j - i + 1$，$s_{i\sim j}$ 和 $s_{i+1\sim j+1}$ 都是回文串。

那么有 $s_i = s_j$，$s_j = s_{i + 2}$，$s_{i + 2} = s_{j - 2}$，$s_{j - 2} = s_{i + 4}$，以此类推，可以发现此时一定满足 $s_i = s_{i + 2} = s_{i + 4} = \cdots$ ，同理可得 $s_{i + 1} = s_{i + 3} = s_{i + 5}=\cdots$ 。

此外，如果 $len$ 是偶数，那么 $i$ 和 $j$ 的奇偶性就不同，但是 $s_i = s_j$ 意味着所有字符必须相等。

但是当 $len=1$ 或 $len=n$ 时的边界情况不满足以上结论，他们的特殊性很好说明。

因此，字符串为 $k$-good 的条件可以写成如下 ： 
- $k = 1$ : 不可能；

- $1 < k < len \land k\equiv 1\pmod 2$：不是交替串；

- $1 < k < len \land k\equiv 0\pmod 2$：不是由相同字母构成串；

- $k = len$ ：非回文串。

现在开始子串查询。第二种和第三种情况很容易处理，可以将满足 $s_i \ne s_{i + 2}$ 和 $s_i \ne s_{i + 1}$ 的位置分别存储在 `std::set` 中。检查子串是否为回文串的标准方法有很多，如字符串 Hash 和 Manacher 算法。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=2e5+10;
char str[maxn],st[maxn<<1];
int dp[maxn<<1];
void manacher(int n){
	int m=0; st[m++]='$';
	for(int i=0;i<n;i++){
		st[m++]='#'; st[m++]=str[i];
	}
	st[m++]='#'; st[m++]='&';
	int posr=0,mid=0;
	for(int i=0;i<m;i++) dp[i]=0;
	for(int i=1;i<m-1;i++){
		if(i>posr) dp[i]=0;
		else dp[i]=min(dp[(mid<<1)-i],posr-i);
		while(st[i+dp[i]+1]==st[i-dp[i]-1]) dp[i]++;
		if(dp[i]+i>posr) posr=dp[i]+i,mid=i;
	}
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n,q;scanf("%d%d",&n,&q);
		scanf("%s",str); manacher(n);
		set<int>pos1,pos2;
		for(int i=0;i<n;i++){
			if(i+1<n and str[i]!=str[i+1]) pos1.insert(i+1);
			if(i+2<n and str[i]!=str[i+2]) pos2.insert(i+1);
		}
		while(q--){
			int l,r;scanf("%d%d",&l,&r);
			if(l==r){puts("0");continue;}
			int len=r-l+1; ll ans=0;
			auto it1=pos1.lower_bound(l);
			auto it2=pos2.lower_bound(l);
			if(it1!=pos1.end() and (*it1)+1<=r){
				if(it2!=pos2.end() and (*it2)+2<=r){
					ans=1ll*(1+len-1)*(len-1)/2-1;
				} else {
					ans=1ll*((len-1)/2+1)*((len-1)/2)/2*2;
				}
			}
			if(dp[l+r]<len) ans=ans+1ll*len;
			printf("%lld\n",ans);
		}
	}
	return 0;
}
```

---

## 作者：Wf_yjqd (赞：0)

因为输出不开 long long 本地能过卡了很久。

------------

考虑正难则反，用总长度减去存在回文串的所有长度 $k$。

对于 $k=1$，显然都是回文。

对于 $k=r-l+1$，转换为判断回文串。

因为一点串串算法都不会，硬写了个三模哈希好在没卡。

对于 $k$ 剩下的情况我们奇偶考虑。

若 $k$ 为偶，那就要求所有字符都相同，可以简单地前缀维护。

若 $k$ 为奇，发现回文意味着奇数位相同且偶数位相同，也能前缀维护。

全部统计起来即可，复杂度线性。

------------

最终式子代码里有。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=2e5+26,mx=2e5,base[3]={23,8414141,31},mod[3]={998244353,564611849,1000000007};
ll T,n,q,l,r,lst[maxn],lst2[maxn];
ll qz[3][maxn],hz[3][maxn],pw[3][maxn];
char s[maxn];
inline bool check(ll l,ll r){
    if((hz[0][l]-hz[0][r]*pw[0][r-l]%mod[0]+mod[0])%mod[0]!=(qz[0][r]-qz[0][l]*pw[0][r-l]%mod[0]+mod[0])%mod[0])
        return 0;
    if((hz[1][l]-hz[1][r]*pw[1][r-l]%mod[1]+mod[1])%mod[1]!=(qz[1][r]-qz[1][l]*pw[1][r-l]%mod[1]+mod[1])%mod[1])
        return 0;
    if((hz[2][l]-hz[2][r]*pw[2][r-l]%mod[2]+mod[2])%mod[2]!=(qz[2][r]-qz[2][l]*pw[2][r-l]%mod[2]+mod[2])%mod[2])
        return 0;
    return 1;
}
int main(){
    scanf("%lld",&T);
    pw[0][0]=pw[1][0]=pw[2][0]=1;
    for(ll i=1;i<=mx;i++){
        pw[0][i]=pw[0][i-1]*base[0]%mod[0];
        pw[1][i]=pw[1][i-1]*base[1]%mod[1];
        pw[2][i]=pw[2][i-1]*base[2]%mod[2];
    }
    while(T--){
        scanf("%lld%lld%s",&n,&q,s+1);
        for(ll i=1;i<=n;i++){
            qz[0][i]=(qz[0][i-1]*base[0]+s[i])%mod[0];
            qz[1][i]=(qz[1][i-1]*base[1]+s[i])%mod[1];
            qz[2][i]=(qz[2][i-1]*base[2]+s[i])%mod[2];
        }
        hz[0][n+1]=hz[1][n+1]=hz[2][n+1]=0;
        for(ll i=n;i>=1;i--){
            hz[0][i]=(hz[0][i+1]*base[0]+s[i])%mod[0];
            hz[1][i]=(hz[1][i+1]*base[1]+s[i])%mod[1];
            hz[2][i]=(hz[2][i+1]*base[2]+s[i])%mod[2];
        }
        for(ll i=1;i<=n;i++)
            lst[i]=(s[i]==s[i-1]?lst[i-1]:i-1);
        for(ll i=2;i<=n;i++)
            lst2[i]=(s[i]==s[i-2]?lst2[i-2]:i-2);
        while(q--){
            scanf("%lld%lld",&l,&r);
            if((r-l)&1)
                printf("%lld\n",(r-l+2)*(r-l+1)/2-1-(lst[r]<l)*(r-l+1)*((r-l)/2)/2-(lst2[r]<l&&lst2[r-1]<l&&r-l>=3)*(r-l+3)*((r-l)/2)/2-check(l,r)*(r-l+1));
            else
                printf("%lld\n",(r-l+2)*(r-l+1)/2-1-(lst[r]<l)*(r-l+2)*((r-l)/2)/2-(lst2[r]<l&&lst2[r-1]<l&&r-l>=3)*(r-l+2)*((r-l-1)/2)/2-check(l,r)*(r-l+1));
        }
    }
    return 0;
}
```

---

## 作者：Luzhuoyuan (赞：0)

闲话：打 Div 2，再次实现赛后 10min 切题，绷不住了。下大分。

Links: [[Codeforces]](https://codeforces.com/problemset/problem/1943/B) [[Luogu]](https://www.luogu.com.cn/problem/CF1943B)

### 题意

定义一个字符串是 $k$-good 的，当且仅当该字符串存在长为 $k$ 的非回文子串。对于字符串 $t$，定义 $f(t)$ 为满足 $t$ 是 $k$-good 的正整数 $k$ 的总和。对于给定的一个长为 $n$ 的字符串 $s$，你需要回答 $q$ 个询问，每次询问给出两个正整数 $l,r$，求 $f(s_ls_{l+1}\dots s_r)$ 的值。每个测试点 $t$ 组测试用例。

$$1\le t\le 2\cdot 10^4;1\le n,q,\sum n,\sum q\le 2\cdot 10^5;1\le l<r\le n$$

### 思路

先考虑怎样计算 $f(t_1t_2\dots t_m)$。我们对于 $k$ 的值进行分讨：

- 当 $k=1$ 时，贡献显然为 $0$。
- 当 $k=m$ 时，若整个串为回文，则贡献为 $0$，否则为 $m$。
- 当 $1<k<m$，$k$ 为奇数时，**不**产生贡献的条件是：字符串隔位相等，即 $t_1=t_3=\dots,t_2=t_4=\dots$。证明考虑反向思考，判断是否所有长为 $k$ 的子串均为回文串（$k$-bad （雾）。若只考虑位于 $[1,k]$ 的子串，那么肯定呈现为：$t_1t_2\dots t_{\frac{k+1}{2}}t_{\frac{k+1}{2}-1}\dots t_1$。由于 $[2,k+1]$ 的子串也是回文串，可以得到 $t_1=t_3,t_2=t_4,t_3=t_5\dots t_{\frac{k+1}{2}-2}=t_{\frac{k+1}{2}}$，继续往后也同理。所以当隔位相等时贡献为 $0$，否则贡献为 $\displaystyle\sum_{i=1}^{\lfloor\frac m 2\rfloor-1}(2i+1)=\lfloor\dfrac m 2\rfloor^2-1$。
- 当 $1<k<m$，$k$ 为偶数时，**不**产生贡献的条件是：字符串每位均相等，即 $t_1=t_2=\dots=t_m$。证明与上面类似，只考虑 $[1,k]$ 呈现 $t_1t_2\dots t_{\frac k 2}t_{\frac k 2}t_{\frac k 2 -1}\dots t_1$，再考虑 $[2,k+1]$ 就得到 $t_1=t_3,t_2=t_4,\dots,t_{\frac k 2 -2}=t_{\frac k 2},t_{\frac k 2}=t_{\frac k 2 -1}$，即 $t_1=t_2=\dots=t_{\frac k 2}$，继续往后也同理。故满足全部相等时贡献为 $0$，否则贡献为 $\displaystyle\sum_{i=1}^{\lfloor\frac{m-1}{2}\rfloor}2i=\lfloor\dfrac{m-1}{2}\rfloor(\lfloor\dfrac{m-1}{2}\rfloor+1)$。

现在问题就是对于 $s_ls_{l+1}\dots s_r$ 快速判断上面的东西。

每个相等和隔位相等可以对于每个 $i$ 预处理 $f_i,g_i$ 分别表示最靠左的位置满足 $s_{f_i}=s_{f_i+1}=\dots=s_i,s_{g_i}=s_{g_i+2}=\dots=s_i$；某个子串是否是回文可以用哈希或者 Manacher 线性预处理。然后简单判断一下就行啦。复杂度 $O(n+q)$。

### 代码

代码中用了哈希。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,mod=998244353;
mt19937 rnd(time(0));
int T,n,m,f[N],g[N],a[N],b[N],bs[N],d[30];
bool fl[N];
char s[N];
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
signed main(){
	T=read();
	bs[0]=1;for(int i=1;i<=2e5;i++)bs[i]=bs[i-1]*13331%mod;
	for(int i=1;i<=26;i++){do d[i]=rnd()&8191;while(fl[d[i]]);fl[d[i]]=true;}//随机映射
	while(T--){
		n=read(),m=read();scanf("%s",s+1);
		for(int i=1;i<=n;i++)f[i]=(s[i]==s[i-1]?f[i-1]:i);
		g[1]=1;for(int i=2;i<=n;i++)g[i]=(s[i]==s[i-2]?g[i-2]:i);
		a[0]=1;for(int i=1;i<=n;i++)a[i]=(a[i-1]*13331+d[s[i]^96])%mod;
		b[n+1]=1;for(int i=n;i;i--)b[i]=(b[i+1]*13331+d[s[i]^96])%mod;
		while(m--){
			int l=read(),r=read();
			int c=((a[r]-a[l-1]*bs[r-l+1]%mod+mod)%mod==(b[l]-b[r+1]*bs[r-l+1]%mod+mod)%mod);
			printf("%lld\n",((r-l)/2)*((r-l)/2+1)*(f[r]>l)
				+(((r-l+1)/2)*((r-l+1)/2)-1)*(g[r]>l+1||g[r-1]>l+1)+!c*(r-l+1));
		}
	}
	return 0;
}
```

（逃

---

## 作者：aeiouaoeiu (赞：0)

考虑一个子串 $s(l,r)$ 不是 $k$ 好时需要满足的条件。

此时 $s(l,r)$ 中所有长度为 $k$ 的子串均为回文串，有 $s_l=s_{l+k-1},s_{l+1}=s_{l+k-2},\cdots,s_{l+1}=s_{l+k},s_{l+2}=s_{l+k-1}\cdots$。将几个等号合并，发现对于奇偶性相同的 $i,j$，都有 $s_i=s_j$，且当 $k$ 为偶数时对于所有 $i,j$ 都有 $s_i=s_j$。

那么求出每个字母在所有下标/奇数下标/偶数下标出现次数的前缀和，可以 $\mathcal O(V)$ 判断一个子串是否是 $k(2\le k<n)$ 好的，其中 $V=26$。

注意上面的判断需要满足至少能有两个长度为 $k$ 的子串，所以要特判 $k=n$，这里我用了哈希。同时还要特判 $k=0$。

时间复杂度：$\mathcal O((n+q)V)$。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define pob pop_back
#define mp make_pair
using namespace std;
typedef long long ll;
typedef double db;
const ll maxn=200007,ee=1000000000000000007ll,P1=142857133,P2=999999151,B1=11451,B2=191981;
ll n,q,hs1[maxn],hs2[maxn],pw1[maxn],pw2[maxn],hs1r[maxn],hs2r[maxn],sumo[30][maxn],sume[30][maxn],suma[30][maxn];
string s;
void init(void){
	pw1[0]=pw2[0]=1;
	for(int i=1;i<maxn;i++) pw1[i]=pw1[i-1]*B1%P1,pw2[i]=pw2[i-1]*B2%P2;
}
pair<ll,ll> hsg(ll l,ll r){return mp((hs1[r]-hs1[l-1]*pw1[r-l+1]%P1+P1)%P1,(hs2[r]-hs2[l-1]*pw2[r-l+1]%P2+P2)%P2);}
pair<ll,ll> hsgr(ll l,ll r){return mp((hs1r[l]-hs1r[r+1]*pw1[r-l+1]%P1+P1)%P1,(hs2r[l]-hs2r[r+1]*pw2[r-l+1]%P2+P2)%P2);}
ll solve(ll l,ll r){
	ll flg1=0,flg2=0,flg3=0,res=(hsg(l,r)==hsgr(l,r)?0:(r-l+1));
	for(int i=0;i<26;i++){
		if(sumo[i][r]-sumo[i][l-1]!=0) flg1++;
		if(sume[i][r]-sume[i][l-1]!=0) flg2++;
		if(suma[i][r]-suma[i][l-1]!=0) flg3++;
	}
	//cout<<flg1<<" "<<flg2<<" "<<flg3<<"\n";
	//pair<ll,ll> r1=hsg(l,r),r2=hsgr(l,r);
	//cout<<r1.first<<" "<<r1.second<<"\n",cout<<r2.first<<" "<<r2.second<<"\n";
	if(flg1!=1||flg2!=1) res+=(r-l)*(r-l+1)/2-1;
	else if(flg3!=1) res+=((r-l)/2)*((r-l)/2+1);
	return res;
}
int main(void){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll Tccs=1; init();
	cin>>Tccs;
	for(int tcs=1;tcs<=Tccs;tcs++){
		cin>>n>>q>>s,s=" "+s; hs1r[n+1]=hs2r[n+1]=0;
		for(int i=1;i<=n;i++) hs1[i]=(hs1[i-1]*B1%P1+(s[i]-'a'))%P1,hs2[i]=(hs2[i-1]*B2%P2+(s[i]-'a'))%P2;
		for(int i=n;i>=1;i--) hs1r[i]=(hs1r[i+1]*B1%P1+(s[i]-'a'))%P1,hs2r[i]=(hs2r[i+1]*B2%P2+(s[i]-'a'))%P2;
		//for(int i=1;i<=n;i++) cout<<hs1[i]<<" "; cout<<"\n";
		//for(int i=1;i<=n;i++) cout<<hs1r[i]<<" "; cout<<"\n";
		//for(int i=1;i<=n;i++) cout<<pw1[i]<<" "; cout<<"\n";
		for(int j=0;j<26;j++){
			for(int i=1;i<=n;i++) sumo[j][i]=sumo[j][i-1]+(((i&1)&&s[i]-'a'==j)?1:0);
			for(int i=1;i<=n;i++) sume[j][i]=sume[j][i-1]+((!(i&1)&&s[i]-'a'==j)?1:0);
			for(int i=1;i<=n;i++) suma[j][i]=suma[j][i-1]+((s[i]-'a'==j)?1:0);
		}
		for(int i=1,l,r;i<=q;i++){
			cin>>l>>r;
			cout<<solve(l,r)<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：Diaоsi (赞：0)

[Non-Palindromic Substring](https://www.luogu.com.cn/problem/CF1943B)

直接计算答案比较困难，假设所有的 $k$ 都对答案产生贡献，则答案为 $\dfrac{1}{2}s(s+1)$，$s$ 为区间长。考虑哪些情况对答案不会产生贡献，然后再从答案中减去即可。

当 $k=1$ 时一定对答案没有贡献，$k$ 为偶数时能对答案没贡献当且仅当询问区间的字符完全相同，$k$ 为奇数时对答案没贡献当且仅当询问区间的字符交替相同。

还有一种特殊的情况是 $k$ 等于询问区间长，此时若该区间为回文串也不会对答案产生贡献。

- 若区间中字符全部相同，则答案为 $0$。

- 若区间中字符交替相同，则答案为符合条件的偶数 $k$ 之和，可以用等差数列求和公式处理。

- 然后就是判断询问区间是否为回文串，若是则答案减去区间长度。

于是只需要开桶维护前缀中每个位置字符出现的次数，前缀中奇数位置字符出现的次数和偶数位置字符出现的个数。判断回文可以使用哈希，实测双哈希不会被卡。也可以使用 Manacher 算法。

时间复杂度 $\mathcal{O}\left(\left|\Sigma\right|(n+q)\right)$。

Code:
```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
using namespace std;
const ll N=200010,M=2000010,lpw=998244407;
inline ll max(ll x,ll y){return x>y?x:y;}
inline ll min(ll x,ll y){return x<y?x:y;}
inline void swap(ll &x,ll &y){x^=y^=x^=y;}
int T,n,m,t[N][27][3];
ull h1[N],p1[N],h2[N],p2[N];
ull h3[N],h4[N];
char s[N],c[N];
ull hash1(ll l,ll r){
	return h1[r]-h1[l-1]*p1[r-l+1];
}
ull hash2(ll l,ll r){
	return (h2[r]-h2[l-1]*p2[r-l+1]%lpw+lpw)%lpw;
}
ull hash3(ll l,ll r){
	return h3[r]-h3[l-1]*p1[r-l+1];
}
ull hash4(ll l,ll r){
	return (h4[r]-h4[l-1]*p2[r-l+1]%lpw+lpw)%lpw;
}
bool chk(ll l,ll r){
	int l1=n-l+1,r1=n-r+1;
	if(l1>r1)swap(l1,r1);
	return hash1(l,r)==hash3(l1,r1)&&hash2(l,r)==hash4(l1,r1);
}
void solve(){
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	p1[0]=p2[0]=1;
	for(ll i=1;i<=n;i++){
		c[i]=s[n-i+1];
		h1[i]=h1[i-1]*131+s[i]-'a'+1;
		p1[i]=p1[i-1]*131;
		h2[i]=(h2[i-1]*13331+s[i]-'a'+1)%lpw;
		p2[i]=p2[i-1]*13331%lpw;
	}
	for(ll i=1;i<=n;i++){
		h3[i]=h3[i-1]*131+c[i]-'a'+1;
		h4[i]=(h4[i-1]*13331+c[i]-'a'+1)%lpw;
	}
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=26;j++)
			t[i][j][0]=t[i][j][1]=t[i][j][2]=0;
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=26;j++){
			t[i][j][0]+=t[i-1][j][0];
			t[i][j][1]+=t[i-1][j][1];
			t[i][j][2]+=t[i-1][j][2];
		}
		t[i][s[i]-'a'+1][0]++;
		if(i&1)t[i][s[i]-'a'+1][1]++;
		else t[i][s[i]-'a'+1][2]++;
	}
	while(m--){
		ll l,r,len,ans=0;
		scanf("%lld%lld",&l,&r);
		len=r-l+1;
		if(l==r){
			puts("0");
			continue;
		}
		ll res=0,ql=0,qr=0,flg=1;
		for(ll j=1;j<=26;j++)
			res+=(t[r][j][0]-t[l-1][j][0]>0);
		if(res==1){
			puts("0");
			continue;
		}
		else if(res==2){
			for(ll j=1;j<=26;j++)
				ql+=(t[r][j][1]-t[l-1][j][1]>0);
			for(ll j=1;j<=26;j++)
				qr+=(t[r][j][2]-t[l-1][j][2]>0);
			if(ql==1&&qr==1){
				if(len&1)len--;
				len>>=1;
				ans=len*(len+1);
				flg=0;
			}
		}
		if(flg)ans=len*(len+1)/2-1;
		if(flg&&chk(l,r))ans-=(r-l+1);
		printf("%lld\n",ans);
	}
}
int main(){
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

