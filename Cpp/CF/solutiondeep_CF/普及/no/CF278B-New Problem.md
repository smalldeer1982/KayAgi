# 题目信息

# New Problem

## 题目描述

Coming up with a new problem isn't as easy as many people think. Sometimes it is hard enough to name it. We'll consider a title original if it doesn't occur as a substring in any titles of recent Codeforces problems.

You've got the titles of $ n $ last problems — the strings, consisting of lowercase English letters. Your task is to find the shortest original title for the new problem. If there are multiple such titles, choose the lexicographically minimum one. Note, that title of the problem can't be an empty string.

A substring $ s[l...\ r] $ $ (1<=l<=r<=|s|) $ of string $ s=s_{1}s_{2}...\ s_{|s|} $ (where $ |s| $ is the length of string $ s $ ) is string $ s_{l}s_{l+1}...\ s_{r} $ .

String $ x=x_{1}x_{2}...\ x_{p} $ is lexicographically smaller than string $ y=y_{1}y_{2}...\ y_{q} $ , if either $ p&lt;q $ and $ x_{1}=y_{1},x_{2}=y_{2},...\ ,x_{p}=y_{p} $ , or there exists such number $ r $ $ (r&lt;p,r&lt;q) $ , that $ x_{1}=y_{1},x_{2}=y_{2},...\ ,x_{r}=y_{r} $ and $ x_{r+1}&lt;y_{r+1} $ . The string characters are compared by their ASCII codes.

## 说明/提示

In the first sample the first 9 letters of the English alphabet (a, b, c, d, e, f, g, h, i) occur in the problem titles, so the answer is letter j.

In the second sample the titles contain 26 English letters, so the shortest original title cannot have length 1. Title aa occurs as a substring in the first title.

## 样例 #1

### 输入

```
5
threehorses
goodsubstrings
secret
primematrix
beautifulyear
```

### 输出

```
j
```

## 样例 #2

### 输入

```
4
aa
bdefghijklmn
opqrstuvwxyz
c
```

### 输出

```
ab
```

# AI分析结果



# 题目重写

## 题目描述

设计新的题目并不像很多人想象的那么简单。有时候连命名都困难。我们将认为一个标题是原创的，当且仅当它没有作为子串出现在最近任何Codeforces题目的标题中。

你获得了最近 $n$ 道题目的标题（由小写英文字母组成的字符串）。你的任务是找出新问题的最短原创标题。如果有多个最短标题，选择字典序最小的。注意，标题不能是空字符串。

子串 $s[l...r]$ $(1 \leq l \leq r \leq |s|)$ 的定义是字符串 $s$ 中从第 $l$ 到第 $r$ 个字符组成的连续字符序列。

字典序比较规则：字符串 $x$ 比 $y$ 小当且仅当 $x$ 是 $y$ 的前缀且更短，或存在某个位置 $r$ 使得前 $r$ 个字符相同且 $x_{r+1} < y_{r+1}$。

## 输入样例 #1

5  
threehorses  
goodsubstrings  
secret  
primematrix  
beautifulyear  

## 输出样例 #1

j  

## 输入样例 #2

4  
aa  
bdefghijklmn  
opqrstuvwxyz  
c  

## 输出样例 #2

ab  

---

**算法分类**  
搜索（BFS/DFS）

---

**题解分析与结论**

### 核心思路
1. **长度优先搜索**：答案的最短性要求优先检查长度更小的字符串，通过 BFS 或迭代加深 DFS 保证按层级扩展。
2. **字典序生成**：按字母顺序生成候选字符串（'a'到'z'），确保找到的第一个解即为字典序最小。
3. **子串检查优化**：直接使用字符串的 `find` 方法验证候选字符串是否存在于输入字符串的任意子串。

### 最优题解亮点

#### 题解作者：opzc35（BFS）  ★★★★☆
**核心思路**：  
- 使用 BFS 从空字符串开始逐层扩展，保证最短解优先被找到。
- 按字母顺序生成子节点，确保字典序最小。
- 直接利用 `string::find` 方法进行子串存在性检查。

**关键代码**：
```cpp
void bfs() {
    queue<string> q;
    q.push("");
    while (!q.empty()) {
        string top = q.front();
        q.pop();
        if (!check(top) && top != "") {
            cout << top;
            return;
        }
        for (char x = 'a'; x <= 'z'; x++) {
            q.push(top + x);
        }
    }
}
```

#### 题解作者：Paracelestia（迭代加深）  ★★★★☆
**核心思路**：  
- 通过迭代加深控制搜索深度，逐层增加字符串长度。
- 深度优先生成所有可能字符串，利用递归的天然顺序保证字典序。
- 通过 `exit(0)` 直接终止搜索，避免冗余计算。

**关键代码**：
```cpp
void dfs(string t) {
    if (t.size() > dep) return;
    bool f = false;
    for (int i = 1; i <= n; ++i) 
        if (s[i].find(t) != -1) {
            f = true;
            break;
        }
    if (!f && !t.empty()) {
        cout << t << endl;
        exit(0);
    }
    for (char ch = 'a'; ch <= 'z'; ++ch)
        dfs(t + ch);
}

// 调用方式
for (dep = 1; dep <= 20; ++dep) dfs("");
```

#### 题解作者：lizhixun（长度枚举）  ★★★★☆
**核心思路**：  
- 显式枚举字符串长度，从 1 开始逐步增加。
- 对每个长度进行全排列 DFS，按字母顺序生成候选解。
- 找到第一个有效解立即终止程序。

**关键代码**：
```cpp
void dfs(int step, int sz, string ss) {
    if (step == sz + 1) {
        if (!check(ss)) {
            cout << ss;
            exit(0);
        }
        return;
    }
    for (char c = 'a'; c <= 'z'; c++)
        dfs(step + 1, sz, ss + c);
}

// 主调用
for (int i = 1; i <= max_len + 1; i++)
    dfs(1, i, "");
```

---

**关键技巧总结**  
- **层级扩展机制**：BFS 或迭代加深确保最短解优先。
- **字典序生成顺序**：按字母顺序生成候选字符串（'a'→'z'）。
- **高效子串检查**：直接调用 `string::find` 避免预处理开销。

---

**同类题目推荐**  
1. [P1039 侦探推理](https://www.luogu.com.cn/problem/P1039) - 字符串模式匹配与逻辑推理
2. [P1706 全排列问题](https://www.luogu.com.cn/problem/P1706) - 字典序生成训练
3. [CF1536B Prinzessin der Verurteilung](https://codeforces.com/problemset/problem/1536/B) - 同类最短未出现子串问题

---
处理用时：192.48秒