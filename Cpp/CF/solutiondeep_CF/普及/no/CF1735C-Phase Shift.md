# 题目信息

# Phase Shift

## 题目描述

There was a string $ s $ which was supposed to be encrypted. For this reason, all $ 26 $ lowercase English letters were arranged in a circle in some order, afterwards, each letter in $ s $ was replaced with the one that follows in clockwise order, in that way the string $ t $ was obtained.

You are given a string $ t $ . Determine the lexicographically smallest string $ s $ that could be a prototype of the given string $ t $ .

A string $ a $ is lexicographically smaller than a string $ b $ of the same length if and only if:

- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter, that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 说明/提示

In the first test case, we couldn't have the string "a", since the letter a would transit to itself. Lexicographically the second string "b" is suitable as an answer.

In the second test case, the string "aa" is not suitable, since a would transit to itself. "ab" is not suitable, since the circle would be closed with $ 2 $ letters, but it must contain all $ 26 $ . The next string "ac" is suitable.

Below you can see the schemes for the first three test cases. The non-involved letters are skipped, they can be arbitrary placed in the gaps.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1735C/40f1e4167acecb5e201b23a56898bccbc525d101.png)

## 样例 #1

### 输入

```
5
1
a
2
ba
10
codeforces
26
abcdefghijklmnopqrstuvwxyz
26
abcdefghijklmnopqrstuvwxzy```

### 输出

```
b
ac
abcdebfadg
bcdefghijklmnopqrstuvwxyza
bcdefghijklmnopqrstuvwxyaz```

# AI分析结果

### 题目内容重写

#### 题目描述

有一个字符串 $s$ 需要被加密。为此，所有 $26$ 个小写英文字母被排列成一个环，顺序未知。然后，$s$ 中的每个字母被替换为环中顺时针方向的下一个字母，从而得到字符串 $t$。

给定字符串 $t$，请确定字典序最小的字符串 $s$，它可能是 $t$ 的原型。

字符串 $a$ 的字典序小于字符串 $b$ 当且仅当：

- 在 $a$ 和 $b$ 第一个不同的位置上，$a$ 中的字母在字母表中比 $b$ 中的字母更靠前。

#### 说明/提示

在第一个测试用例中，我们不能得到字符串 "a"，因为字母 a 会映射到它自己。字典序第二小的字符串 "b" 是合适的答案。

在第二个测试用例中，字符串 "aa" 不合适，因为 a 会映射到它自己。"ab" 也不合适，因为环只包含 $2$ 个字母，但它必须包含所有 $26$ 个字母。下一个字符串 "ac" 是合适的。

### 算法分类
贪心、构造

### 题解分析与结论

1. **minecraft_herobrine 的题解**：
   - **思路**：贪心地为每个字符找到字典序最小的映射，同时避免形成小于 $26$ 的环。
   - **难点**：如何高效地检查映射是否会导致环的形成。
   - **实现**：使用 `check` 函数遍历映射表，判断是否形成环。
   - **评分**：4星
   - **亮点**：通过贪心策略和环检测，确保字典序最小且映射合法。

2. **EclipSilvia 的题解**：
   - **思路**：使用并查集维护字母的连通性，确保映射不会形成小于 $26$ 的环。
   - **难点**：如何利用并查集高效地管理字母的映射关系。
   - **实现**：通过 `calc` 函数为每个字母找到合适的前驱，并更新并查集。
   - **评分**：4星
   - **亮点**：利用并查集优化环检测，代码结构清晰。

3. **ScottSuperb 的题解**：
   - **思路**：贪心地为每个字符选择字典序最小的源，同时避免形成小于 $26$ 的环。
   - **难点**：如何高效地检查候选源是否会导致环的形成。
   - **实现**：使用 `check` 函数遍历映射表，判断是否形成环。
   - **评分**：3星
   - **亮点**：思路清晰，但代码实现略显冗长。

### 最优关键思路

- **贪心策略**：从字典序最小的字母开始，为每个字符选择最小的合法映射。
- **环检测**：通过遍历映射表或使用并查集，确保映射不会形成小于 $26$ 的环。
- **并查集优化**：利用并查集管理字母的连通性，提高环检测的效率。

### 可拓展之处

- **类似题目**：可以考虑更复杂的映射规则，如多个字母的映射关系或非环形的映射结构。
- **算法套路**：贪心结合并查集或深度优先搜索（DFS）进行环检测，适用于需要构造合法映射的题目。

### 推荐题目

1. [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
2. [P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)
3. [P3388 【模板】割点（割顶）](https://www.luogu.com.cn/problem/P3388)

### 个人心得摘录

- **minecraft_herobrine**：通过贪心策略和环检测，确保字典序最小且映射合法，代码实现较为简洁。
- **EclipSilvia**：利用并查集优化环检测，代码结构清晰，思路明确。

### 核心代码片段

```cpp
// minecraft_herobrine 的 check 函数
bool check(char a, char b) {
    int i;
    memset(v, false, sizeof(v));
    v[a] = true;
    for (i = 1;; i++) {
        if (!b) return false;
        if (v[b]) break;
        v[b] = true;
        b = mp[b];
    }
    return i < 26;
}

// EclipSilvia 的 calc 函数
void calc(int x) {
    for (int i = 1; i <= 26; i++) {
        if (i == x) continue;
        if (!nxt[i]) {
            if (cnt != 25 && find(i) == find(x)) continue;
            ++cnt;
            nxt[i] = x;
            pre[x] = i;
            f[find(i)] = find(x);
            break;
        }
    }
}
```

---
处理用时：34.40秒