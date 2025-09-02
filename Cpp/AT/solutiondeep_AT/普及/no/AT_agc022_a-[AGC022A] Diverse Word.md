# 题目信息

# [AGC022A] Diverse Word

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc022/tasks/agc022_a

ゴトウは辞書をもらいました。ところが、その辞書は知らない言語で書かれていました。 分析した結果、その辞書にはありうるすべての **多彩** な単語が辞書順に載っていることがわかりました。

単語は、それが英小文字からなる空でない文字列であって、単語内の文字がすべて異なる場合、そしてその場合に限って **多彩** であると呼ばれます。例えば、`atcoder`、`zscoder`、`agc` は多彩な単語ですが、`gotou`、`connect` は多彩な単語ではありません。

多彩な単語 $ S $ が与えられるので、この辞書で $ S $ の次に載っている単語、すなわち、$ S $ より辞書順で大きいような、辞書順で最小の多彩な単語を求めてください。あるいは、そのような単語は存在しないと判定してください。

なお、$ X\ =\ x_{1}x_{2}...x_{n} $、$ Y\ =\ y_{1}y_{2}...y_{m} $ を二つの異なる文字列とするとき、$ Y $ が $ X $ の接頭辞であるか、$ j $ を $ x_{j}\ \neq\ y_{j} $ であるような最小の整数として $ x_{j}\ >\ y_{j} $ である場合、そしてその場合に限って $ X $ は $ Y $ より辞書順で大きいといいます。

## 说明/提示

### 制約

- $ 1\ \leq\ |S|\ \leq\ 26 $
- $ S $ は多彩な単語である。

### Sample Explanation 1

`atcoder` より辞書順で大きいような、辞書順で最小の多彩な単語は `atcoderb` です。`atcoderb` は `b` より辞書順で小さいことに注意してください。

### Sample Explanation 3

これが辞書順で最も大きい多彩な単語なので、答えは `-1` です。

## 样例 #1

### 输入

```
atcoder```

### 输出

```
atcoderb```

## 样例 #2

### 输入

```
abc```

### 输出

```
abcd```

## 样例 #3

### 输入

```
zyxwvutsrqponmlkjihgfedcba```

### 输出

```
-1```

## 样例 #4

### 输入

```
abcdefghijklmnopqrstuvwzyx```

### 输出

```
abcdefghijklmnopqrstuvx```

# AI分析结果



# [AGC022A] Diverse Word

## 题目描述

给定一个仅包含互不相同小写字母的字符串 $S$（称为"多彩单词"），求字典序比 $S$ 大的最小多彩单词。若不存在则输出 -1。

### 输入格式
输入仅一行字符串 $S$（长度在 1 到 26 之间）

### 输出格式
输出所求字符串或 -1

### 说明/提示
- 字典序比较规则：按首个不同字符的 ASCII 值比较
- 当 $S$ 是字母表逆序时无解（如 zyxwvutsrqponmlkjihgfedcba）

## 算法分类
贪心、构造

## 题解综合分析

### 核心思路对比
各题解均采用分类讨论策略：
1. **长度 <26**：追加最小未出现字符（PR_CYJ、So_noSlack 等）
2. **长度=26**：从后向前找可替换位置，替换为后方最小更大字符并截断（火车司机、Ezio__Auditore 等）

### 关键难点
- 长度=26 时的最优替换位置判定
- 处理全逆序的特殊情况
- 字典序比较与字符替换的协调

## 优质题解推荐

### 1. 火车司机（5星）
**亮点**：
- 使用逆向遍历寻找替换点，逻辑清晰
- 维护最大值数组优化比较
- 代码简洁高效，可读性强

核心代码：
```cpp
for(int i = n; i; --i) {
    if(s[i] < mx) {
        for(int j = 1; j < i; ++j) putchar(s[j]);
        for(int j = s[i]-'a'; j<26; ++j) 
            if(v[j]) { putchar(j+'a'); return 0; }
    }
    mx = max(mx, s[i]), v[s[i]-'a'] = 1;
}
```

### 2. PR_CYJ（4星）
**亮点**：
- 利用 STL 的 next_permutation 简化排列生成
- 特判全逆序情况处理直接

核心代码：
```cpp
if(s == "zyxwvutsrqponmlkjihgfedcba") cout << -1;
else {
    next_permutation(s.begin(), s.end());
    for(int i=0; i<s.size(); i++) {
        cout << s[i];
        if(s[i] != t[i]) break;
    }
}
```

### 3. Ezio__Auditore（4星）
**亮点**：
- 使用双指针维护后缀最大值
- 逻辑分层明确，便于调试

核心代码：
```cpp
int max_suf = -1;
for(int i = n; i >=1; i--) {
    if(max_suf > s[i]-'a') {
        for(int j=1; j<i; j++) putchar(s[j]);
        for(int j=s[i]-'a'+1; j<26; j++)
            if(vis[j]) { putchar(j+'a'); break; }
        return 0;
    }
    max_suf = max(max_suf, s[i]-'a');
    vis[s[i]-'a'] = 1;
}
```

## 最优技巧总结
1. **分治策略**：根据长度分情况处理，避免冗余判断
2. **逆向扫描**：从后往前寻找首个可替换点，确保最小增量
3. **贪心选择**：替换时取右侧最小更大字符，保证字典序最小性
4. **STL 优化**：next_permutation 快速生成下一个排列

## 拓展思考
类似问题可考虑：
1. 带限制条件的全排列问题（如 LeetCode 31. 下一个排列）
2. 存在禁用字符的字典序构造（如 Codeforces 上相关构造题）
3. 多约束条件的字符串生成（如同时要求字符出现次数限制）

## 相似题目推荐
1. [P2525 Uim的情人节礼物·其之壱](https://www.luogu.com.cn/problem/P2525)（全排列问题）
2. [P1088 火星人](https://www.luogu.com.cn/problem/P1088)（第k小排列）
3. [CF1768C Elemental Decompress](https://www.luogu.com.cn/problem/CF1768C)（双序列构造）

---
处理用时：57.25秒