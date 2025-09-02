# [NWRRC2024] Longest Common Substring

## 题目描述

Lisa 编写了一个解决最长公共子串问题的程序。她使用该程序对两个由字符 $\tt{0}$ 和 $\tt{1}$ 组成的字符串 $s$ 和 $t$ 进行计算，找到了它们的最长公共子串 $w$。当存在多个相同长度的最长公共子串时，她任意选择其中一个。

值得注意的是，Lisa 找到的 $w$ 长度非常小——最多为 3。

Lisa 记得 $n$（$s$ 的长度）、$m$（$t$ 的长度）和 $w$，但她不记得字符串 $s$ 和 $t$ 本身。现在她想知道有多少对字符串 $(s, t)$ 满足：它们的长度分别为 $n$ 和 $m$，由字符 $\tt{0}$ 和 $\tt{1}$ 组成，并且 $w$ 是它们的最长公共子串之一。

请帮助 Lisa 计算这个对数，结果对 $998\,244\,353$ 取模。注意当 $n = m$ 且 $s \ne t$ 时，$(s, t)$ 和 $(t, s)$ 被视为不同的对。

## 说明/提示

注意，字符串 $a$ 是字符串 $b$ 的子串，当且仅当 $a$ 可以通过从 $b$ 的开头和结尾删除零个或多个字符得到。

在第一个测试用例中，所有满足条件的字符串对为 ($\tt{01}$, $\tt{10}$)、($\tt{01}$, $\tt{11}$)、($\tt{10}$, $\tt{01}$)、($\tt{10}$, $\tt{11}$)、($\tt{11}$, $\tt{01}$) 和 ($\tt{11}$, $\tt{10}$)。

## 样例 #1

### 输入

```
2 2 1
1```

### 输出

```
6```

## 样例 #2

### 输入

```
3 4 2
01```

### 输出

```
28```

## 样例 #3

### 输入

```
7 5 3
110```

### 输出

```
399```

## 样例 #4

### 输入

```
23 42 3
000```

### 输出

```
174497840```

# 题解

## 作者：sunkuangzheng (赞：1)

首先对题面做第一步转化：我们不关心最长公共子串的具体值，只关心它是否大于等于 $k+1$。而公共子串长度有单调性，因此我们只关心是否存在长度为 $k+1$ 的公共子串。因此问题转化为：求有多少 $s,t$ 满足存在公共子串 $w$ 且不存在长度为 $k+1$ 的公共子串。

注意到 $2^{k+1} = 16$ 非常小，我们可以把所有的 $2^{k+1}$ 个子串是否出现过压进状态。一开始我在想对两个串同时进行 dp，但是时空复杂度都爆炸。后来发现两个串的填充是基本独立的，我们只需要保证其最后拥有的 $2^{k+1}$ 子串不交。

那么进行 DP，设 $dp_{n,o,r,b}$ 表示长度为 $n$，串的最后 $k$ 个字符是 $o$，串中是否存在了 $w$ 的状态是 $r=0/1$，串中拥有的所有 $2^{k+1}$ 子串的状态是 $b$ 的方案数，转移直接枚举填什么就行了。

然后最终的问题是，求 $\sum \limits_{i \& j = 0} f_ig_j$，这是套路的，考虑对 $g$ 数组的下标反转（$0111 \to 1000$），这样限制就变成了 $g$ 是 $i$ 的超集，高维前缀和即可。


```cpp
/**
 *    author: sunkuangzheng
 *    created: 19.11.2024 08:47:52
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 5e5+5,mod = 998244353;
using namespace std;
int T,n,M,k,w,dp[105][8][2][1 << 16],m,len; string s;
void ad(int &x,int y){x = (x + y) % mod;}
vector<int> get(int n){
    vector<int> f(len);
    for(int o = 0;o < m;o ++) for(int j = 0;j < len;j ++) ad(f[j],dp[n][o][1][j]);
    return f; 
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n >> M >> k >> s;
    for(char c : s) w = w * 2 + c - '0';
    m = (1 << k),len = (1 << m * 2);
    for(int i = 0;i < m;i ++) dp[k][i][(i == w)][0] = 1;
    for(int i = k;i < max(n,M);i ++) for(int o = 0;o < m;o ++) for(int r : {0,1})
        for(int b = 0;b < len;b ++) for(int j : {0,1}){
            int nw = o * 2 + j;
            // if(dp[i][o][r][b]) debug(i,o,r,b),debug(i+1,nw%m,r|(nw%m==w),b|(1<<nw));
            ad(dp[i+1][nw%m][r|(nw%m==w)][b|(1<<nw)],dp[i][o][r][b]);
        }
    auto f = get(n),g = get(M);
    reverse(g.begin(),g.end());
    for(int i = 0;i < m * 2;i ++) for(int j = len - 1;j >= (1 << i);j --)
        if(j >> i & 1) ad(g[j - (1 << i)],g[j]);
    int ans = 0;
    for(int i = 0;i < len;i ++) ad(ans,1ll * f[i] * g[i] % mod);
    cout << ans << "\n"; 
}
```

---

