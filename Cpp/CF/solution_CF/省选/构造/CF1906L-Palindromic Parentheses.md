# Palindromic Parentheses

## 题目描述

Construct a parentheses sequence consisting of $ N $ characters such that it is balanced and the length of its longest palindromic subsequence (LPS) is exactly $ K $ . Determine whether such a construction is possible. If there are several possible sequences, construct any of them.

A parentheses sequence consists of only character ( and ). A parentheses sequence is balanced if each character ( has a corresponding character ) and the pairs of parentheses are properly nested. For example, (), (()), (())(), and ((())()) are balanced. However, )(, ((), and ()) are not balanced.

A sequence is palindromic if it reads the same backwards as forwards. For example, ((, ), ())(, and (()(( are palindromic. However, (), )(, and (()) are not palindromic.

A subsequence can be derived from another sequence by removing zero or more characters without changing the order of the remaining characters. For example, (, ))), ())(, and (())() are subsequence of (())(). However, )(( and ((())) are not subsequence of (())().

The longest palindromic subsequence (LPS) of a sequence is a subsequence with the maximum number of characters, derived from that sequence and it is palindromic. For example, the LPS of sequence (())() is ())(, which can be obtained by removing the second and sixth characters. Therefore, the length of the LPS of (())() is $ 4 $ .

## 说明/提示

Explanation for the sample input/output #2

The LPS of (()()) is either ((( by removing all ) characters, or ))) by removing all ( characters.

The output ((())) also satisfies the requirements.

Explanation for the sample input/output #3

The only possible balanced parentheses sequences are (()) and ()(). The length of the LPS of (()) and ()() are $ 2 $ and $ 3 $ , respectively.

Explanation for the sample input/output #4

The LPS of ()((())()())() is )())()())(), which can be obtained by removing the first, fourth, and fifth characters.

## 样例 #1

### 输入

```
6 4```

### 输出

```
(())()```

## 样例 #2

### 输入

```
6 3```

### 输出

```
(()())```

## 样例 #3

### 输入

```
4 1```

### 输出

```
-1```

## 样例 #4

### 输入

```
14 11```

### 输出

```
()((())()())()```

# 题解

## 作者：bluewindde (赞：3)

一开始理解错了，误认为“回文”指对称，但是反而受错误的理解启发得到正确做法。

考虑串 `(((...()...)))`，其 LPS 长度为 $\dfrac{n}{2}$。那么若 $k=\dfrac{n}{2}$，输出这个串即可。

接下来考虑串 `()(((...()...)))`，其 LPS 长度为 $\dfrac{n}{2}+1$，写个程序跑一下即可。（求 LPS 即为求它反转后的串与原串的 LCS）

而 $k<\dfrac{n}{2}$ 是无解的，因为一个平衡的括号串里 `(` 的个数有 $\dfrac{n}{2}$ 个，这些 `(` 构成一个回文子序列，因此 $k<\dfrac{n}{2}$ 不会成为 LPS，故无解。

$k=n$ 也是无解的，因为一个平衡的括号串开头一定是 `(`，结尾一定是 `)`，因此不存在长度为 $n$ 的回文序列。

$k>\dfrac{n}{2}$ 的规律可以借助打表程序找。

打表程序代码，输出每个长度为 $n$ 的平衡串的 LPS：

```cpp
#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

int n;
int a[2005];
int b[2005];
int dp[2005][2005];
map<int, set<string>> mp;

static inline void LPS() {
    for (int i = 1; i <= n; ++i) {
        b[n - i + 1] = a[i];
    }
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            dp[i][j] = 0;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            if (a[i] == b[j]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
            }
        }
    }
    string s;
    for (int i = 1; i <= n; ++i) {
        s.push_back(a[i] + '(');
    }
    mp[dp[n][n]].insert(s);
}

static inline void dfs(int x) {
    if (x > n) {
        bool flag = true;
        int cur = 0;
        for (int i = 1; i <= n; ++i) {
            if (a[i] == 0) {
                ++cur;
            } else {
                --cur;
            }
            if (cur < 0) {
                flag = false;
                break;
            }
        }
        if (cur != 0) {
            flag = false;
        }
        if (flag) {
            LPS();
        }
        return;
    }
    a[x] = 0;
    dfs(x + 1);
    a[x] = 1;
    dfs(x + 1);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    dfs(1);
    for (auto [L, s] : mp) {
        cout << L << endl;
        for (auto str : s) {
            cout << "    " << str << endl;
        }
    }
    return 0;
}
```

以 $n=10$ 为例，可以提取出一组特殊的串：

```cpp
((((())))) // k = 5
(((())))() // k = 6
()((()))() // k = 7
()(())()() // k = 8
()()()()() // k = 9
```

发现只需保留一个长度为 $2\cdot(n-k)$ 的形如 `(((...()...)))` 的串，剩余的空位由串 `()` 尽量均匀地填补在两侧即可。

> 注：这个很像我在文章 [LPS](https://www.luogu.com.cn/blog/artbaernydfy/post-lps) 里提到的朴素 LPS 的优化。

总结：构造题就是去尝试的过程，暴力程序可以更好地帮助找规律。

代码

```cpp
#include <iostream>

using namespace std;

int n, k;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k;
    if (k < n / 2 || k == n) {
        cout << -1 << endl;
        return 0;
    }
    int extra = n - 2 * (n - k); // 剩余的空位长度
    int cur = 0;                 // 已经输出的串长度
    for (int i = 1; i <= extra / 4; ++i) {
        cout << "()";
        cur += 2;
    }
    for (int i = 1; i <= n - k; ++i) {
        cout << "(";
        ++cur;
    }
    for (int i = 1; i <= n - k; ++i) {
        cout << ")";
        ++cur;
    }
    while (cur + 2 <= n) {
        cout << "()";
        cur += 2;
    }
    cout << endl;
    return 0;
}
```

打表程序代码比正解长，这或许就是构造题的魅力。

---

## 作者：rizynvu (赞：2)

[我的博客](https://www.cnblogs.com/rizynvu/p/18036863)。

考虑先判定有无解对应的 $k$ 的范围。  

首先若 $k = n$ 一定无解，因为字符串开头是 $\texttt{(}$ 结尾是 $\texttt{)}$ 匹配不上。  
下界因为各有 $\frac{n}{2}$ 个 $\texttt{()}$，所以可以先猜测下界就为 $\frac{n}{2}$。  

考虑构造到这个下界。  
能发现只需要形如 $\texttt{(((...)))}$ 即可。

然后考虑增量法往上一个一个增加。  
发现 $\texttt{()(((...)))}$ 会使左边的小括号组的右括号与右边的大括号组的右括号匹配上，即匹配长度会增加 $2$，且此时左边小括号组的左括号是未匹配的。  
继续增加，$\texttt{()(((...)))()}$，能发现最左边的左括号与右边的括号组的左括号匹配上了，$+2$，且此时右括号组的右括号是未匹配的。  
于是能发现再在左边加上 $\texttt{()}$ 又能 $+2$，然后又是右边加，左边加这样的。

放的数量可以考虑解方程，设最中间各有 $x$ 个 $\texttt{(}$ 和 $\texttt{)}$，左右侧共有 $y$ 个 $\texttt{()}$，有方程 $\begin{cases}2x + 2y = n\\ x + 2y = k\end{cases}$，解得 $\begin{cases}x = n - k \\ y = k - \frac{n}{2}\end{cases}$。  
于是就可以中间放上 $n - k$ 个 $\texttt{(}$ 和 $\texttt{)}$，然后依次在左边和右边来回放共 $k - \frac{n}{2}$ 个 $\texttt{()}$。  

```cpp
#include<bits/stdc++.h>
int main() {
    int n, k; scanf("%d%d", &n, &k);
    int x = n - k, y = k - n / 2;
    if (x <= 0 || y < 0) return puts("-1"), 0;
    for (int i = 1; i <= (y + 1) / 2; i++) printf("()");
    for (int i = 1; i <= x; i++) printf("(");
    for (int i = 1; i <= x; i++) printf(")");
    for (int i = 1; i <= y / 2; i++) printf("()"); 
    return 0;
}
```

---

## 作者：SegTree (赞：1)

$k<\dfrac{n}{2}$ 或 $k\ge n$ 时显然无解。

考虑第一种做法：猜测答案的构造形如 `()...()(((...)))`，那么枚举左侧的 `()` 的长度 $x$，则可以贪心得到最长回文子序列为 $\max(\dfrac{n}{2}-x+2\min(\dfrac{n}{2}-x,x),2x+1)$。

发现这个做法无法做 $k\ge \dfrac{3}{4}n$ 的偶数情况，因为这个时候 $2x+1$ 贡献到了 $\max$ 上，偶数构造不出来。

考虑第二种做法：用若干个 `()...())(...)(` 再在两边加括号。但是这个做法的问题在于你中间构造的长度比较短的时候会将长度与左边括号个数取 $\max$。而这种做法在 $k\ge \dfrac{3}{4}n$ 时不受影响。

做完了。

---

## 作者：RainWetPeopleStart (赞：0)

考虑什么时候无解。

发现 $k=n$ 一定无解，$k<\frac{n}{2}$ 一定无解。

注意到 $k=n-1$ 时有解 `()()()...()()()`，$k=\frac{n}{2}$ 时有解 `(((...)))`，通过观察样例可以考虑把若干 `()` 替换为 `(((...)))`。

通过猜测得知可以替换 $n-k$ 个 `()`，再通过手玩得出剩余的 `()` 可以平均分布在两边，这样构造是对的。

其实从增量的角度想可能也能想出来。

证明可以讨论回文中心的位置，如果中心在 `()` 上一定不优。

在 $k-\frac{n}{2}$（`()` 的对数）为偶数时，最优是把中间的 `(` 全取了，为 $n-k+2(k-\frac{n}{2})=k$。

为奇数时，不妨设左边的 `()` 比右边多一个，最优也是把中间的 `(` 全取了，为 $n-k+2(k-\frac{n}{2})=k$。

由此，得证。

复杂度 $O(n)$。


```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define ll long long
#define ull unsigned long long
#define uint unsigned int
#define bi __int128_t
#define lb(x) ((x)&(-(x)))
#define gp(i,j) (((i)>>(j-1))&1)
#define ppc __builtin_popcount
using namespace std;
const int N=7e5+10,mod=998244353;
void cmx(int &a,int b){if(b>a) a=b;}
void cmn(int &a,int b){if(b<a) a=b;}
void cmx(ll &a,ll b){if(b>a) a=b;}
void cmn(ll &a,ll b){if(b<a) a=b;}
void Add(int &a,int b){a+=b;if(a>=mod) a-=mod;}
void Sub(int &a,int b){a-=b;if(a<0) a+=mod;}
void Mul(int &a,int b){a=1ll*a*b%mod;}
int n,k;
int main(){
    cin>>n>>k;
    if(k>n-1||k<n/2){
        cout<<-1<<endl;
    }else{
        int oth=k-(n/2-1)-1;
        int lp=oth/2,rp=(oth+1)/2,mp=n/2-oth;
        for(int i=1;i<=lp;i++) cout<<"()";
        for(int i=1;i<=mp;i++) cout<<"(";
        for(int i=1;i<=mp;i++) cout<<")";
        for(int i=1;i<=rp;i++) cout<<"()";
    }
    return 0;
}
```

---

