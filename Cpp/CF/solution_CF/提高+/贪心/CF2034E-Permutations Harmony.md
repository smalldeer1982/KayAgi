# Permutations Harmony

## 题目描述

Rayan wants to present a gift to Reyhaneh to win her heart. However, Reyhaneh is particular and will only accept a k-harmonic set of permutations.

We define a k-harmonic set of permutations as a set of $ k $ pairwise distinct permutations $ p_1, p_2, \ldots, p_k $ of size $ n $ such that for every pair of indices $ i $ and $ j $ (where $ 1 \leq i, j \leq n $ ), the following condition holds:

 $ $$$ p_1[i] + p_2[i] + \ldots + p_k[i] = p_1[j] + p_2[j] + \ldots + p_k[j]  $ $ </p><p>Your task is to help Rayan by either providing a valid <span class="tex-font-style-it">k-harmonic set of permutations</span> for given values of  $ n $  and  $ k $  or by determining that such a set does not exist.</p><p>We call a sequence of length  $ n $  a permutation if it contains every integer from  $ 1 $  to  $ n$$$ exactly once.

## 说明/提示

In example 1, we have $ p_1 = [1, 2, 3] $ , $ p_2 = [2, 3, 1] $ , and $ p_3 = [3, 1, 2] $ . It's easy to see that $ p_1[1] + p_2[1] + p_3[1] = p_1[2] + p_2[2] + p_3[2] = p_1[3] + p_2[3] + p_3[3] = 6 $ .

In example 2, we have $ p_1 = [1, 2, 3, 4] $ and $ p_2 = [4, 3, 2, 1] $ . It's easy to see that $ p_1[1] + p_2[1] = p_1[2] + p_2[2] = p_1[3] + p_2[3] = p_1[4] + p_2[4] = 5 $ .

In example 3, as there are five distinct elements in $ p_1 $ , it's obvious that the answer is "No".

## 样例 #1

### 输入

```
4
3 3
4 2
5 1
3 2```

### 输出

```
YES
1 2 3
2 3 1
3 1 2
YES
1 2 3 4
4 3 2 1
NO
YES
1 2 3
3 2 1```

# 题解

## 作者：littlebug (赞：3)

省流：本文将教你如何正确处理三角恋。

感觉没有那么难呀，几乎一眼秒了，大概 \*1700 的样子。

虽然 CD 因为某些原因没过，导致 E 没看就是了。

## Solution

首先，如果 $k$ 为偶数，那直接两两配对即可，即每个 $a$ 和 $n+1-a$ 配对，在 $n!$ 个排列中刚好每个排列都有另一半。~~连排列都有另一半了，你呢？~~

主要讲讲 $k$ 为奇数应该怎么搞，我们发现，无论怎么搞都需要有一组个数 $\ge 3$ 的排列互相配对（~~三角恋~~），于是考虑如何把这三个排列搞出来。我们可以手动模拟一下解决，根据每个位置的三个数相加和必须为 $3(n+1)$，多试几次就可以，于是我们得到了这个表（设 $x$ 为 $\lfloor \frac n 2 \rfloor$）：

| $1$ | $2$ | $3$ | $4$ | $5$ | $\ldots$ | $2x-1$ | $2x$ | $2x+1$ |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| $x+1$ | $2x+1$ | $x$ | $2x$ | $x-1$ | $\ldots$ | $2$ | $x+2$ | $1$ |
| $2x+1$ | $x$ | $2x$ | $x-1$ | $2x-1$ | $\ldots$ | $x+2$ | $1$ | $x+1$ |

~~懒得敲了，直接把官方题解的搬过来了。~~

那么我们就把三角恋的情况搞定了，剩下的和偶数情况一样，两两配对就可以了。

不过还要注意判无解，共有 $4$ 种情况：

1. 若 $k=1$ 且 $n \ne 1$，则显然无解。
1. 若 $k > n!$，由于排列数最多只能有 $n!$ 个，所以无解。
1. 根据上面那个表可得 $n$ 必须为奇数，所以若 $k$ 为奇数但是 $n$ 为偶数则无解。
1. 当 $k$ 为奇数时，我们发现，在上面那个表中，已经用掉了 $3$ 个两两不配对的排列，所以在所有 $n!$ 个排列中，就出现了 $3$ 个没法配对的排列，于是最多能有 $n!-3$ 个排列被使用，所以 $k> n!-3$ 时无解。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<vector>

#define int long long
#define il inline
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define rpe(i,a,b) for(int i=(a);i>=(b);--i)
#define pb emplace_back

using namespace std;

template <typename T> il void clr(T &x) {T().swap(x);}

const int fac[20]={1,1,2,6,24,120,720,5040,40320,362880,3628800};
int n,k;
vector < vector <int> > a;
vector <int> p,b1,b2,b3,c1,c2,c3;

il void solve(int __Ti)
{
    clr(a),clr(b1),clr(b2),clr(b3),clr(c1),clr(c2),clr(c3),clr(p);
    cin>>n>>k;

    if(k==1) return n==1 ? cout<<"YES\n1\n" : cout<<"NO\n",void(); // 无解情况 1

    if(n<=10 && k>fac[n]) return cout<<"NO\n",void(); // 无解情况 2

    if(k&1)
    {
        if(!(n&1)) return cout<<"NO\n",void(); // 无解情况 3
        if(n<=10 && k>fac[n]-3) return cout<<"NO\n",void(); // 无解情况 4

        int x=n>>1; // 三角恋！
        rep(i,1,n) b1.pb(i);
        b2.resize(n),b3.resize(n);
        for(int i=1,j=x+1;i<=n;i+=2,--j) b2[i-1]=b3[((i-1)?:n)-1]=j;
        for(int i=2,j=2*x+1;i<=n;i+=2,--j) b2[i-1]=b3[i-1-1]=j;

        a.pb(b1),a.pb(b2),a.pb(b3);
        
        rep(i,0,n-1) c1.pb(n+1-b1[i]),c2.pb(n+1-b2[i]),c3.pb(n+1-b3[i]);

        k-=3;
    }

    rep(i,1,n) p.pb(i);
    do // 两两配对
    {
        if(p==b1 || p==b2 || p==b3 || p==c1 || p==c2 || p==c3) continue;

        a.pb(p);
        a.pb(vector<int>());
        for(auto i:p) a.back().pb(n+1-i);

        k-=2;
    } while(k>0 && next_permutation(p.begin(),p.end()));

    cout<<"YES\n";
    for(auto j:a) {for(auto i:j) cout<<i<<' '; cout<<'\n';}
}

signed main()
{
    ios::sync_with_stdio(0); ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    int __T; cin>>__T; rep(__Ti,1,__T) solve(__Ti);
    return 0;
}
```

这样，我们就成功处理了三角恋！

看来 Rayan 给 Reyhaneh 送礼物的时候很危险呢，还要提防三角恋破坏他的礼物哦！

---

## 作者：Zrnstnsr (赞：0)

为了方便表述，下称排列 $[a_1,a_2,\dots,a_n]$ 和 $[n+1-a_1,n+1-a_2,\dots,n+1-a_n]$ 为互补排列。

几个非常平凡的结论（~~由非常显然到不太平凡~~）：

1. $k>n!$ 时无解，$k=n!$ 时有解，解为全排列的集合。
2. $n\ge 2$ 且 $k=1$ 时仅 $n=1$ 时有解。相应的，也可以推出 $k=n!-1$ 时无解。
3. $k$ 为偶数时有解，解为任意 $\frac{k}{2}$ 个排列及其补排列。
4. $k$ 为奇数，$n$ 为偶数时无解。这是因为每个下标的和都应该为 $\frac{k(n+1)}{2}$，而此时这个数不是整数，所以无解。

考虑 $n$ 和 $k$ 均为奇数的情形。我们考虑首先构造 $k=3$ 时的特解，然后往上面填充互补排列。由于特解只存在三个不互补的排列（显然特解不会存在互补排列），所以可以一直填充到 $k=n!-3$ 个，正好覆盖了 $k$ 为奇数的所有情形。

为了方便表述，令 $n=2m-1$。通过 _打表_ 可以得到如下所示的特解：

- $p_1=[1,2,\dots,m,m+1,m+2,\dots,2m-1]$
- $p_2=[m,m+1,\dots,2m-1,1,2,\dots,m-1]$
- $p_3=[2m-1,2m-3,\dots,1,2m-2,2m-4,\dots,2]$

然后填充互补排列即可。在我的实现中，我用 `L` 代表一个排列，`R` 代表另一个排列，枚举时则分别使用 `next_permutation` 和 `prev_permutation`。

代码：[294078450](https://codeforces.com/contest/2034/submission/294078450)。

---

## 作者：1234567890sjx (赞：0)

大分类讨论。

+ $n=1$。此时若 $k=1$ 则需构造排列 $\lbrace 1\rbrace$。否则无解。
+ $n\neq 1$ 且 $k=1$。此时显然无解。
+ $2\mid k$。先考虑 $k=2$ 的特殊情况。显然可以构造 $\lbrace 1,2,3,\ldots,n\rbrace$ 和 $\lbrace n,n-1,n-2,\ldots,1\rbrace$。同样的若 $2\mid k$ 则可以构造 $1\sim n$ 组成的排列中字典序前 $\frac{k}{2}$ 小的排列和字典序前 $\frac{k}{2}$ 的排列。特殊点，若 $n!<k$ 则无解。
+ $k-1\mid n-1$。此时令 $d=\frac{n-1}{d-1}$，可以构造 $k$ 个排列。其中第 $i$ 个排列（$i<k$）为 $\lbrace 1+(d-1)i,2+(d-1)i,\ldots,n,1,2,\ldots,(d-1)i\rbrace$。最后一个排列直接让每一个位置所对应元素的和相等即可。
+ $2\nmid n$。此时考虑到 $k\ge 3$ 且 $2\nmid k$，所以考虑先用上面的方法构造 $k=3$ 的排列，对于另外 $n-3$ 个排列用偶数的构造方法。特殊的，若 $n!+3<k$ 则无解。
+ 其余情况无解。

时间复杂度为 $O(nk)$，可以通过。

```cpp
int sjh[N], p1[N], p2[N], n, k;
void run() {
    int T = read(), ca = 1;
    while (T--) {
        n = read(), k = read();
        if (n == 1) {
            if (k == 1) {
                cout << "YES\n";
                for (int i = 1; i <= k; ++i) cout << "1\n";
            } else {
                cout << "NO\n";
            }
        } else if (k == 1) cout << "NO\n";
        else if (~k & 1) {
            int fac = 1;
            if (n > 12) fac = LLONG_MAX;
            else {
                for (int i = 1; i <= n; ++i)
                    fac = fac * i;
            }
            if (fac < k) cout << "NO\n";
            else {
                cout << "YES\n";
                iota(a + 1, a + n + 1, 1ll);
                for (int i = 0; i < k / 2; ++i) {
                    for (int j = 0; j < n; ++j) cout << a[j + 1] << ' ';
                    cout << '\n'; 
                    next_permutation(a + 1, a + n + 1);
                }
                iota(a + 1, a + n + 1, 1ll);
                reverse(a + 1, a + n + 1);
                for (int i = 0; i < k / 2; ++i) {
                    for (int j = 0; j < n; ++j) cout << a[j + 1] << ' ';
                    cout << '\n'; 
                    prev_permutation(a + 1, a + n + 1);
                }
            }
        } else {
            if (n == k) {
                cout << "YES\n";
                for (int i = 1; i <= n; ++i, cout << '\n') {
                    int j = i;
                    for (int x = 1; x <= n; ++x) {
                        cout << j << ' ';
                        ++j;
                        if (j > n) j = 1;
                    }
                }
            } else {
                if ((n - 1) % (k - 1) == 0) {
                    cout << "YES\n";
                    for (int i = 0; i < n; ++i) sjh[i] = 0;
                    int dt = (n - 1) / (k - 1), st = 1;
                    while (k--) {
                        if (k) {
                            int x = st;
                            for (int i = 0; i < n; ++i) {
                                cout << x << ' ';
                                sjh[i] += x;
                                ++x;
                                if (x > n) x = 1;
                            }
                            cout << '\n';
                        } else {
                            int all = st + sjh[0];
                            for (int i = 0; i < n; ++i)
                                cout << all - sjh[i] << ' ';
                            cout << '\n';
                        }
                        st += dt;
                    }
                } else {
                    int fac = 1;
                    if (n > 12) fac = LLONG_MAX;
                    else {
                        for (int i = 1; i <= n; ++i)
                            fac = fac * i;
                    }
                    fac -= 3;
                    if (fac < k) cout << "NO\n";
                    else if (n % 2 == 1) {
                        cout << "YES\n";
                        vector<vector<int>> p; p.resize(3);
                        for (int i = 0; i < 3; ++i) p[i].resize(n);
                        fill(sjh, sjh + n, 0ll);
                        for (int i = 0; i < n; ++i) p[0][i] = i + 1, sjh[i] = i + 1;
                        int st = n / 2 + 1; for (int i = 0; i < n; ++i) {
                            p[1][i] = st; ++st; if (st > n) st = 1;
                            sjh[i] += p[1][i];
                        }
                        int all = n + sjh[0];
                        for (int i = 0; i < n; ++i) p[2][i] = all - sjh[i];
                        iota(p1 + 1, p1 + n + 1, 1ll);
                        iota(p2 + 1, p2 + n + 1, 1ll);
                        reverse(p2 + 1, p2 + n + 1);
                        k -= 3; k /= 2;
                        for (int i = 0; i < 3; ++i, cout << '\n')
                            for (int j = 0; j < n; ++j) cout << p[i][j] << ' ';
                        while (k--) {
                            int o[6] = {1, 1, 1, 1, 1, 1};
                            for (int i = 1; i <= n; ++i) if (p1[i] != p[0][i - 1]) o[0] = 0;
                            for (int i = 1; i <= n; ++i) if (p1[i] != p[1][i - 1]) o[1] = 0;
                            for (int i = 1; i <= n; ++i) if (p1[i] != p[2][i - 1]) o[2] = 0;
                            for (int i = 1; i <= n; ++i) if (p2[i] != p[0][i - 1]) o[3] = 0;
                            for (int i = 1; i <= n; ++i) if (p2[i] != p[1][i - 1]) o[4] = 0;
                            for (int i = 1; i <= n; ++i) if (p2[i] != p[2][i - 1]) o[5] = 0;
                            if (count(o, o + 6, 1ll) == 0) {
                                for (int i = 1; i <= n; ++i) cout << p1[i] << ' '; cout << '\n';
                                for (int i = 1; i <= n; ++i) cout << p2[i] << ' '; cout << '\n';
                            } else ++k;
                            next_permutation(p1 + 1, p1 + n + 1);
                            prev_permutation(p2 + 1, p2 + n + 1);
                        }
                    } else {
                        cout << "NO\n";
                    }
                }
            }
        }
    }
}
```

---

## 作者：wxzzzz (赞：0)

有人场上不认识 distinct 这个单词。

![](https://cdn.luogu.com.cn/upload/image_hosting/5khgi58r.png)

### 思路

如果没有 distinct 是好做的，先考虑这一部分。

发现最终每一列的和是确定的，即 $\frac{\frac{n(n+1)}{2}\cdot m}{n}=\frac{(n+1)m}{2}$。因为是整数，所以必须有 $n$ 为奇数或 $m$ 为偶数，否则无解。

1. $m=1$：有解当且仅当 $n=1$。
2. $m$ 为偶数：直接 $a=\{1,2,\cdots,n\}/\{n,n-1,\cdots,1\}$ 交替即可。
3. $m$ 为奇数且 $m\ge 3$。（此时 $n$ 为奇数）

   考虑构造一个 $m=3$ 的答案。
   
   暴搜出来一种方案：$p1_i=i,p2=\{\frac{n+1}{2},\frac{n+1}{2}+1,\cdots,n,1,2,\cdots,\frac{n-1}{2}\},p3_i=\frac{3(n+1)}{2}-p1_i-p2_i$。

   剩下部分即 $m$ 为偶数的做法。

想到这里基本就做出来了，只要你英语不是 $83.5$。

加上 distinct 后只需要把 $m$ 为偶数的部分改为一个个使用全排列，哈希去掉用过的排列就做完了。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
int hs(int *a) {
    long long ret = 0;
    for (int i = 1; i <= n; i++)
        ret = (ret * 131 + a[i]) % 998244353;
    return ret;
}
void upd(int *a, int *b) {
    for (int i = 1; i <= n; i++)
        b[i] = n - a[i] + 1;
}
int a[100005], b[100005], p1[100005], p2[100005], p3[100005];
unordered_map<int, bool> vis;
bool check() {
    for (int i = 1; i <= n; i++)
        a[i] = i;
    int t = 0;
    while (t < m) {
        upd(a, b);
        if (vis[hs(a)] || vis[hs(b)]) {
            if (!next_permutation(a + 1, a + n + 1))
                break;
            continue;
        }
        vis[hs(a)] = vis[hs(b)] = 1;
        t += 2;
    }
    return t >= m;
}
void solve() {
    cin >> n >> m;
    if (n == 1 && m == 1) {
        puts("YES\n1");
        return;
    }
    if (n == 1 || m == 1) {
        puts("NO");
        return;
    }
    if (m & 1 ^ 1) {
        vis.clear();
        if (!check()) {
            puts("NO");
            return;
        }
        vis.clear();
        for (int i = 1; i <= n; i++)
            a[i] = i;
        puts("YES");
        for (int i = 1; i <= m / 2; i++) {
            upd(a, b);
            if (vis[hs(a)] || vis[hs(b)]) {
                i--;
                next_permutation(a + 1, a + n + 1);
                continue;
            }
            vis[hs(a)] = vis[hs(b)] = 1;
            for (int j = 1; j <= n; j++)
                cout << a[j] << ' ';
            cout << '\n';
            for (int j = 1; j <= n; j++)
                cout << b[j] << ' ';
            cout << '\n';
        }
        return;
    }
    if (n & 1 ^ 1) {
        puts("NO");
        return;
    }
    for (int i = 1; i <= n; i++)
        p1[i] = i;
    int idx = 0;
    for (int i = (n + 1) / 2; i <= n; i++)
        p2[++idx] = i;
    for (int i = 1; i <= n / 2; i++)
        p2[++idx] = i;
    for (int i = 1; i <= n; i++)
        p3[i] = (n + 1) * 3 / 2 - p1[i] - p2[i];
    vis.clear();
    vis[hs(p1)] = vis[hs(p2)] = vis[hs(p3)] = 1;
    m -= 3;
    if (!check()) {
        puts("NO");
        return;
    }
    m += 3;
    vis.clear();
    vis[hs(p1)] = vis[hs(p2)] = vis[hs(p3)] = 1;
    puts("YES");
    for (int i = 1; i <= n; i++)
        cout << p1[i] << ' ';
    cout << '\n';
    for (int i = 1; i <= n; i++)
        cout << p2[i] << ' ';
    cout << '\n';
    for (int i = 1; i <= n; i++)
        cout << p3[i] << ' ';
    cout << '\n';
    for (int i = 1; i <= n; i++)
        a[i] = i;
    for (int i = 1; i <= (m - 3) / 2; i++) {
        upd(a, b);
        if (vis[hs(a)] || vis[hs(b)]) {
            i--;
            next_permutation(a + 1, a + n + 1);
            continue;
        }
        vis[hs(a)] = vis[hs(b)] = 1;
        for (int j = 1; j <= n; j++)
            cout << a[j] << ' ';
        cout << '\n';
        for (int j = 1; j <= n; j++)
            cout << b[j] << ' ';
        cout << '\n';
    }
}
int main() {
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}

---

