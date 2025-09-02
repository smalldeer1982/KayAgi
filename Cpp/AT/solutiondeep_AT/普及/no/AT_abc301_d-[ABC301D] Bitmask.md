# 题目信息

# [ABC301D] Bitmask

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc301/tasks/abc301_d

`0`, `1`, `?` からなる文字列 $ S $ および整数 $ N $ が与えられます。 $ S $ に含まれる `?` をそれぞれ `0` または `1` に置き換えて $ 2 $ 進整数とみなしたときに得られる値の集合を $ T $ とします。 たとえば、$ S= $ `?0?` のとき、 $ T=\lbrace\ 000_{(2)},001_{(2)},100_{(2)},101_{(2)}\rbrace=\lbrace\ 0,1,4,5\rbrace $ です。

$ T $ に含まれる $ N $ 以下の値のうち最大のものを ($ 10 $ 進整数として) 出力してください。 $ N $ 以下の値が $ T $ に含まれない場合は、代わりに `-1` を出力してください。

## 说明/提示

### 制約

- $ S $ は `0`, `1`, `?` からなる文字列
- $ S $ の長さは $ 1 $ 以上 $ 60 $ 以下
- $ 1\leq\ N\ \leq\ 10^{18} $
- $ N $ は整数

### Sample Explanation 1

問題文中で例示したとおり、$ T=\lbrace\ 0,1,4,5\rbrace $ です。 $ T $ に含まれる $ N $ 以下の値は $ 0 $ と $ 1 $ なので、そのうちの最大である $ 1 $ を出力します。

### Sample Explanation 2

$ T=\lbrace\ 5\rbrace $ であるため、$ N $ 以下の値は $ T $ に含まれません。

## 样例 #1

### 输入

```
?0?
2```

### 输出

```
1```

## 样例 #2

### 输入

```
101
4```

### 输出

```
-1```

## 样例 #3

### 输入

```
?0?
1000000000000000000```

### 输出

```
5```

# AI分析结果



### 题目中文翻译
#### [ABC301D] 位掩码

**题目描述**  
给定由 `0`、`1`、`?` 组成的字符串 $S$ 和整数 $N$。将 $S$ 中的 `?` 替换为 `0` 或 `1` 后得到的二进制数集合为 $T$。求 $T$ 中小于等于 $N$ 的最大值，若无解则输出 `-1`。

**样例解释**  
例如，$S =$ `?0?` 时，$T = \{0,1,4,5\}$。若 $N=2$，最大值为 $1$。

### 算法分类  
**贪心**

---

### 题解对比与结论

#### 核心思路  
1. **贪心策略**：从高位到低位遍历，优先在 `?` 位置填 `1`，同时确保后续位填 `0` 时总和仍不超过 $N$。
2. **预处理**：先计算所有确定位（`0`/`1`）的值，若已超过 $N$ 则无解。
3. **动态调整**：对每个 `?` 尝试填 `1`，若可行则保留，否则填 `0`。

---

### 精选题解（评分≥4星）

#### 1. Coffee_zzz 的题解（⭐⭐⭐⭐⭐）
**亮点**  
- 预处理二进制权值数组，逻辑清晰。
- 从高位到低位贪心填 `1`，代码简洁高效。
```cpp
#include <bits/stdc++.h>
using namespace std;
long long con[65];
int main() {
    string s; long long n;
    cin >> s >> n;
    long long cnt = 1, num = 0;
    // 预处理权值（从右到左）
    for (int i = s.size()-1; i >= 0; i--) {
        con[i] = cnt;
        cnt *= 2;
    }
    // 计算确定位的值
    for (int i = 0; i < s.size(); i++)
        if (s[i] == '1') num += con[i];
    if (num > n) { cout << -1; return 0; }
    // 贪心填高位
    for (int i = 0; i < s.size(); i++)
        if (s[i] == '?' && num + con[i] <= n)
            num += con[i];
    cout << num;
}
```

#### 2. _Ad_Astra_ 的题解（⭐⭐⭐⭐）
**亮点**  
- 反转字符串处理，避免显式权值计算。
- 从高位到低位遍历，确保贪心顺序正确。
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    string s; long long n, x = 0;
    cin >> s >> n;
    reverse(s.begin(), s.end());
    // 处理确定位
    for (int i = 0; i < s.size(); i++)
        if (s[i] == '1') x |= (1LL << i);
    if (x > n) { cout << -1; return 0; }
    // 贪心填高位
    x = 0;
    for (int i = s.size()-1; i >= 0; i--) {
        if (s[i] != '?') { x |= (s[i]-'0') * (1LL << i); continue; }
        long long t = x | (1LL << i);
        for (int j = i-1; j >= 0; j--)
            if (s[j] == '1') t |= (1LL << j);
        if (t <= n) x |= (1LL << i);
    }
    cout << x;
}
```

#### 3. DengDuck 的题解（⭐⭐⭐⭐）
**亮点**  
- 预处理后续最小值，优化判断逻辑。
- 高效验证当前位填 `1` 的可行性。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, ans, f[1005];
int main() {
    string s; cin >> s >> n;
    int len = s.size();
    // 预处理后续最小值
    for (int i = len-1; i >= 0; i--) {
        if (s[i] == '1') f[i] += (1LL << (len-1 - i));
        f[i] += f[i+1];
    }
    for (int i = 0; i < len; i++) {
        if (s[i] == '?') {
            long long tmp = ans + (1LL << (len-1 - i)) + f[i+1];
            if (tmp <= n) ans += (1LL << (len-1 - i));
        }
    }
    cout << (ans > n ? -1 : ans);
}
```

---

### 关键思路总结  
1. **高位优先**：二进制高位填 `1` 对数值贡献最大，优先处理。
2. **可行性验证**：填 `1` 后需确保后续位填 `0` 仍不超过 $N$。
3. **预处理优化**：通过预处理确定位或后续最小值，减少重复计算。

---

### 拓展与同类题目  
1. **[P2114 [NOI2014] 起床困难综合症](https://www.luogu.com.cn/problem/P2114)**  
   **相似点**：位运算贪心，按位确定最优值。
2. **[P5657 格雷码](https://www.luogu.com.cn/problem/P5657)**  
   **相似点**：二进制构造问题，需处理位间关系。
3. **[P1582 倒水](https://www.luogu.com.cn/problem/P1582)**  
   **相似点**：利用二进制特性求解最优策略。

---
处理用时：217.00秒