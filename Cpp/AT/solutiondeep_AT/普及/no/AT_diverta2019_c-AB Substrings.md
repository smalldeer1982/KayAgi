# 题目信息

# AB Substrings

## 题目描述

[problemUrl]: https://atcoder.jp/contests/diverta2019/tasks/diverta2019_c

すぬけ君は $ N $ 個の文字列を持っています。$ i $ 番目の文字列は $ s_i $ です。

これらの文字列を好きな順序で並べたあと、連結して $ 1 $ つの文字列を作ることを考えます。 作った文字列に `AB` という部分文字列が含まれる個数としてありうる値のうち、最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{4} $
- $ 2\ \leq\ |s_i|\ \leq\ 10 $
- $ s_i $ は英大文字のみからなる

### Sample Explanation 1

\- 例えば、`ABCA`, `BAD`, `XBAZ` の順で連結して `ABCABADXBAZ` を作ったとき、`AB` という部分文字列は $ 2 $ つ含まれます。

## 样例 #1

### 输入

```
3

ABCA

XBAZ

BAD```

### 输出

```
2```

## 样例 #2

### 输入

```
9

BEWPVCRWH

ZZNQYIJX

BAVREA

PA

HJMYITEOX

BCJHMRMNK

BP

QVFABZ

PRGKSPUNA```

### 输出

```
4```

## 样例 #3

### 输入

```
7

RABYBBE

JOZ

BMHQUVA

BPA

ISU

MCMABAOBHZ

SZMEHMA```

### 输出

```
4```

# AI分析结果



# AB 子串

## 题目描述

### 题目内容

すぬけ君有 $N$ 个字符串，第 $i$ 个字符串为 $s_i$。将这些字符串按任意顺序连接后形成一个大字符串，求其中子串 `AB` 的最大出现次数。

### 输入格式

- 第一行输入整数 $N$
- 接下来 $N$ 行每行输入一个由大写字母组成的字符串

### 输出格式

- 输出可能的最大 `AB` 子串数量

### 样例

#### 样例1
输入：
```
3
ABCA
XBAZ
BAD
```
输出：
```
2
```

#### 样例2
输入：
```
9
BEWPVCRWH
ZZNQYIJX
BAVREA
PA
HJMYITEOX
BCJHMRMNK
BP
QVFABZ
PRGKSPUNA
```
输出：
```
4
```

## 算法分类
贪心、字符串

---

## 题解分析

### 核心思路
1. **内部统计**：每个字符串内部的 `AB` 数量固定，直接累加
2. **连接增益**：通过连接字符串产生额外 `AB`，需分类讨论：
   - 类型①：以 `B` 开头且以 `A` 结尾（B...A）
   - 类型②：仅以 `A` 结尾（...A）
   - 类型③：仅以 `B` 开头（B...）
3. **最优策略**：
   - 优先将类型①首尾相连，形成链式增益
   - 用类型②和类型③包裹类型①链，最大化首尾增益
   - 剩余的类型②与类型③两两配对

### 关键难点
- 类型①的链式拼接产生 `AB` 的数量为 $c-1$（c为类型①数量）
- 当存在类型①时，首尾可各接一个类型②和类型③，额外获得 2 个 `AB`
- 剩余的类型②与类型③按最小值配对，每对贡献 1 个 `AB`

---

## 精选题解

### 题解1（ISTP，4星）
**关键亮点**：
- 清晰的四类划分与条件判断
- 数学式处理各类别组合关系
- 完整覆盖所有边界情况

```cpp
int main() {
    int n, ans = 0, a = 0, b = 0, c = 0;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        string s; cin >> s;
        for(int j = 1; j < s.size(); j++)
            if(s[j-1] == 'A' && s[j] == 'B') ans++;
        if(s.back() == 'A' && s[0] == 'B') c++;
        else if(s.back() == 'A') a++;
        else if(s[0] == 'B') b++;
    }
    if(a && b && c) ans += c + 1 + min(a-1, b-1);
    else if(a && b && !c) ans += min(a, b);
    else ans += c - (!a && !b && c);
    cout << ans;
}
```

### 题解2（Samhu07，4星）
**核心思想**：
- 变量命名直观（x=类型②，y=类型③，z=类型①）
- 条件分支层次清晰

```cpp
if(x && y && z) cout << ans + z + 1 + min(x-1, y-1);
else if(x && y && !z) cout << ans + min(x, y);
else if(x || y) cout << ans + z;
else cout << ans + z-1;
```

---

## 总结技巧
1. **分类量化**：将字符串按首尾特征分类统计
2. **链式增益**：优先处理自闭合类型（类型①），利用其链式结构最大化收益
3. **包裹策略**：用单边类型包裹链式结构创造额外增益
4. **剩余配对**：未使用的类型②与类型③两两配对

---

## 拓展练习
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)（贪心策略）
2. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)（字符串贪心处理）
3. [P4995 跳跳！](https://www.luogu.com.cn/problem/P4995)（极值排列组合）

---
处理用时：54.71秒