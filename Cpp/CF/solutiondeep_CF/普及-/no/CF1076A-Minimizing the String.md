# 题目信息

# Minimizing the String

## 题目描述

You are given a string $ s $ consisting of $ n $ lowercase Latin letters.

You have to remove at most one (i.e. zero or one) character of this string in such a way that the string you obtain will be lexicographically smallest among all strings that can be obtained using this operation.

String $ s = s_1 s_2 \dots s_n $ is lexicographically smaller than string $ t = t_1 t_2 \dots t_m $ if $ n < m $ and $ s_1 = t_1, s_2 = t_2, \dots, s_n = t_n $ or there exists a number $ p $ such that $ p \le n $ and $ s_1 = t_1, s_2 = t_2, \dots, s_{p-1} = t_{p-1} $ and $ s_p < t_p $ .

For example, "aaa" is smaller than "aaaa", "abb" is smaller than "abc", "pqr" is smaller than "z".

## 说明/提示

In the first example you can remove any character of $ s $ to obtain the string "aa".

In the second example "abca" < "abcd" < "abcda" < "abda" < "acda" < "bcda".

## 样例 #1

### 输入

```
3
aaa
```

### 输出

```
aa
```

## 样例 #2

### 输入

```
5
abcda
```

### 输出

```
abca
```

# AI分析结果



【中文重写题目】

# 最小化字符串

## 题目描述

给定一个由 $n$ 个小写拉丁字母组成的字符串 $s$。

你需要删除最多一个（即零个或一个）字符，使得通过此操作获得的所有可能字符串中字典序最小的那个。

关于字典序的定义：字符串 $s = s_1 s_2 \dots s_n$ 比字符串 $t = t_1 t_2 \dots t_m$ 字典序更小，当且仅当满足以下任一条件：
1. $n < m$ 且 $s_1 = t_1, s_2 = t_2, \dots, s_n = t_n$
2. 存在某个位置 $p$，使得对于所有 $1 \le i < p$ 有 $s_i = t_i$，且 $s_p < t_p$

例如："aaa" < "aaaa"，"abb" < "abc"，"pqr" < "z"。

## 说明/提示

在第一个样例中，删除任意字符均可得到 "aa"。

第二个样例的排序结果为："abca" < "abcd" < "abcda" < "abda" < "acda" < "bcda"。

---

**算法分类**：贪心

---

### 题解综合分析

所有题解均采用贪心策略，核心思路为：
1. 从左到右扫描，找到第一个满足 `s[i] > s[i+1]` 的位置，删除 `s[i]`
2. 若全序列非递减，则删除最后一个字符

该策略的正确性基于字典序的特性：越靠前的字符对字典序影响越大。删除第一个可优化的位置能最大化降低整体字典序。

---

### 精选题解列表

#### 1. 作者：hank0402（★★★★☆）
**核心亮点**：
- 代码简洁，直接遍历寻找第一个递减点
- 处理边界条件清晰（直接取子串）
```cpp
int main() {
    cin >> n >> s;
    int x = 0;
    for(int i = 0; i < n; i++) 
        if(s[i+1] < s[i]) { x = i; break; }
    // 输出时跳过x位置字符
}
```

#### 2. 作者：StudyingFather（★★★★☆）
**实现技巧**：
- 双循环结构避免字符串操作
- 提前返回优化执行效率
```cpp
for(int i=0;i<n-1;i++)
    if(s[i]>s[i+1]) {
        for(int j=0;j<n;j++) // 直接输出跳过i
        return 0; // 提前退出
    }
// 处理全递增情况
```

#### 3. 作者：alex_liu（★★★☆☆）
**优化点**：
- 使用字符串截取操作简化代码
- 变量命名清晰易理解
```cpp
if(res == -1) res = n-1; // 处理全递增
for(int i=0;i<n;i++) 
    if(i != res) cout<<s[i];
```

---

### 关键思路总结
**贪心选择策略**：在扫描过程中，第一个满足 `s[i] > s[i+1]` 的 `i` 是最优删除点。若全序列非递减，末位字符是唯一可优化点。

**实现技巧**：
- 遍历时使用单次循环及时跳出
- 直接操作输出而非修改原字符串
- 使用 `s.substr()` 或跳过式输出避免容器操作

---

### 拓展建议
类似问题可参考：
1. 删除k个字符使字典序最小（贪心+单调栈）：洛谷P1106
2. 拼接最小字典序（贪心比较器）：洛谷P1012
3. 字典序最小子序列（单调栈应用）：洛谷P1090

---

### 题解心得摘录
> "当字符串全递增时，删末尾优于其他位置" —— DreamBuilder  
> "越靠前的优化对字典序影响越大，找到第一个递减点即可停止" —— Otue  
> "直接操作输出流比修改容器效率更高" —— StudyingFather

---

### 核心代码模板
```cpp
#include <iostream>
using namespace std;

int main() {
    int n; string s;
    cin >> n >> s;
    int del = -1;
    for(int i=0; i<s.size()-1; ++i) {
        if(s[i] > s[i+1]) {
            del = i;
            break;
        }
    }
    if(del == -1) del = s.size()-1;
    cout << s.substr(0, del) + s.substr(del+1);
}
```

---
处理用时：42.98秒