# 题目信息

# The Number Of Good Substrings

## 题目描述

You are given a binary string $ s $ (recall that a string is binary if each character is either $ 0 $ or $ 1 $ ).

Let $ f(t) $ be the decimal representation of integer $ t $ written in binary form (possibly with leading zeroes). For example $ f(011) = 3, f(00101) = 5, f(00001) = 1, f(10) = 2, f(000) = 0 $ and $ f(000100) = 4 $ .

The substring $ s_{l}, s_{l+1}, \dots , s_{r} $ is good if $ r - l + 1 = f(s_l \dots s_r) $ .

For example string $ s = 1011 $ has $ 5 $ good substrings: $ s_1 \dots s_1 = 1 $ , $ s_3 \dots s_3 = 1 $ , $ s_4 \dots s_4 = 1 $ , $ s_1 \dots s_2 = 10 $ and $ s_2 \dots s_4 = 011 $ .

Your task is to calculate the number of good substrings of string $ s $ .

You have to answer $ t $ independent queries.

## 样例 #1

### 输入

```
4
0110
0101
00001000
0001000
```

### 输出

```
4
3
4
3
```

# AI分析结果

### 题目内容重写
给定一个二进制字符串 $s$（即字符串中的每个字符都是 $0$ 或 $1$）。定义 $f(t)$ 为二进制字符串 $t$ 所表示的十进制数（可能包含前导零）。例如，$f(011) = 3$，$f(00101) = 5$，$f(00001) = 1$，$f(10) = 2$，$f(000) = 0$，$f(000100) = 4$。

子串 $s_{l}, s_{l+1}, \dots , s_{r}$ 是“好”的，如果 $r - l + 1 = f(s_l \dots s_r)$。

例如，字符串 $s = 1011$ 有 $5$ 个好子串：$s_1 \dots s_1 = 1$，$s_3 \dots s_3 = 1$，$s_4 \dots s_4 = 1$，$s_1 \dots s_2 = 10$，$s_2 \dots s_4 = 011$。

你的任务是计算字符串 $s$ 中好子串的数量。你需要回答 $t$ 个独立的查询。

### 算法分类
字符串、枚举、剪枝

### 题解分析与结论
所有题解的核心思路都是通过枚举子串的起始位置，然后向后遍历，计算子串的二进制值，并判断是否满足条件。由于二进制值的增长速度较快，题解中普遍采用了剪枝策略，即当二进制值超过字符串长度时，停止继续遍历。

### 所选高星题解

#### 1. 作者：Miracle_1024 (5星)
**关键亮点**：
- 通过预处理数组 `a[i]` 记录从位置 `i` 开始的下一个 `1` 的位置，避免了前导零的无效遍历。
- 时间复杂度为 $O(n \log n)$，代码简洁且高效。

**核心代码**：
```cpp
for(int i=0;i<s.size();i++){
    poww=0;
    for(int j=a[i];j<s.size();j++){
        poww*=2;
        if(s[j]=='1')poww++;
        if(poww>s.size())break;
        if(j-i+1==poww)ans++;
    }
}
```

#### 2. 作者：Dream_poetry (4星)
**关键亮点**：
- 同样通过预处理数组 `a[i]` 记录下一个 `1` 的位置，优化了前导零的处理。
- 代码结构清晰，逻辑明确。

**核心代码**：
```cpp
for(int i=0;i<n;++i){
    int num=0;
    for(int j=a[i];j<n;j++){
        num*=2;
        if(b[j]=='1') num++;
        if(num==j-i+1) ans++;
        if(num>n) break;
    }
}
```

#### 3. 作者：liyp (4星)
**关键亮点**：
- 通过定义数组 `a[i]` 记录下一个 `1` 的位置，并限制遍历的长度为 $18$，进一步优化了时间复杂度。
- 代码实现简洁，逻辑清晰。

**核心代码**：
```cpp
for (int i = 0; i < s.size(); i++) {
    for (int j = a[i]; j < s.size() && j < a[i] + 18; j++) {
        if (ejz(i, j) == j - i + 1) {
            ans++;
        }
    }
}
```

### 最优关键思路或技巧
- **预处理数组**：通过预处理数组记录下一个 `1` 的位置，避免了对前导零的无效遍历，显著提高了效率。
- **剪枝策略**：当二进制值超过字符串长度时，停止继续遍历，减少了不必要的计算。

### 可拓展之处
- 类似的问题可以应用于其他进制，如八进制、十六进制等，只需调整二进制计算的部分。
- 可以进一步优化算法，考虑使用滑动窗口或其他数据结构来减少时间复杂度。

### 推荐相似题目
1. [P1010 二进制数](https://www.luogu.com.cn/problem/P1010)
2. [P1011 二进制加法](https://www.luogu.com.cn/problem/P1011)
3. [P1012 二进制减法](https://www.luogu.com.cn/problem/P1012)

---
处理用时：27.68秒