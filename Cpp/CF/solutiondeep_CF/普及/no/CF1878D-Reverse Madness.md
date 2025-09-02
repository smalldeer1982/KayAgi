# 题目信息

# Reverse Madness

## 题目描述

You are given a string $ s $ of length $ n $ , containing lowercase Latin letters.

Next you will be given a positive integer $ k $ and two arrays, $ l $ and $ r $ of length $ k $ .

It is guaranteed that the following conditions hold for these 2 arrays:

- $ l_1 = 1 $ ;
- $ r_k = n $ ;
- $ l_i \le r_i $ , for each positive integer $ i $ such that $ 1 \le i \le k $ ;
- $ l_i = r_{i-1}+1 $ , for each positive integer $ i $ such that $ 2 \le i \le k $ ;

Now you will be given a positive integer $ q $ which represents the number of modifications you need to do on $ s $ .

Each modification is defined with one positive integer $ x $ :

- Find an index $ i $ such that $ l_i \le x \le r_i $ (notice that such $ i $ is unique).
- Let $ a=\min(x, r_i+l_i-x) $ and let $ b=\max(x, r_i+l_i-x) $ .
- Reverse the substring of $ s $ from index $ a $ to index $ b $ .

Reversing the substring $ [a, b] $ of a string $ s $ means to make $ s $ equal to $ s_1, s_2, \dots, s_{a-1},\ s_b, s_{b-1}, \dots, s_{a+1}, s_a,\ s_{b+1}, s_{b+2}, \dots, s_{n-1}, s_n $ .

Print $ s $ after the last modification is finished.

## 说明/提示

In the first test case:

The initial string is "abcd". In the first modification, we have $ x=1 $ . Since $ l_1=1\leq x \leq r_1=2 $ , we find the index $ i = 1 $ . We reverse the substring from index $ x=1 $ to $ l_1+r_1-x=1+2-1=2 $ . After this modification, our string is "bacd".

In the second modification (and the last modification), we have $ x=3 $ . Since $ l_2=3\leq x \leq r_2=4 $ , we find the index $ i = 2 $ . We reverse the substring from index $ x=3 $ to $ l_2+r_2-x=3+4-3=4 $ . After this modification, our string is "badc".

In the second test case:

The initial string is "abcde". In the first modification, we have $ x=1 $ . Since $ l_1=1\leq x \leq r_1=1 $ , we find the index $ i = 1 $ . We reverse the substring from index $ x=1 $ to $ l_1+r_1-x=1+1-1=1 $ . After this modification, our string hasn't changed ("abcde").

In the second modification, we have $ x=2 $ . Since $ l_2=2\leq x \leq r_2=2 $ , we find the index $ i = 2 $ . We reverse the substring from index $ x=2 $ to $ l_2+r_2-x=2+2-2=2 $ . After this modification, our string hasn't changed ("abcde").

In the third modification (and the last modification), we have $ x=3 $ . Since $ l_3=3\leq x \leq r_3=5 $ , we find the index $ i = 3 $ . We reverse the substring from index $ x=3 $ to $ l_3+r_3-x=3+5-3=5 $ . After this modification, our string is "abedc".

## 样例 #1

### 输入

```
5
4 2
abcd
1 3
2 4
2
1 3
5 3
abcde
1 2 3
1 2 5
3
1 2 3
3 1
gaf
1
3
2
2 2
10 1
aghcdegdij
1
10
5
1 2 3 4 2
1 1
a
1
1
1
1```

### 输出

```
badc
abedc
gaf
jihgedcdga
a```

# AI分析结果

### 题目重写
#### 题目描述
给定一个长度为 $n$ 的字符串 $s$，包含小写拉丁字母。

接下来给定一个正整数 $k$ 和两个长度为 $k$ 的数组 $l$ 和 $r$。保证以下条件成立：
- $l_1 = 1$；
- $r_k = n$；
- 对于每个正整数 $i$，$1 \le i \le k$，有 $l_i \le r_i$；
- 对于每个正整数 $i$，$2 \le i \le k$，有 $l_i = r_{i-1}+1$。

然后给定一个正整数 $q$，表示需要对 $s$ 进行 $q$ 次修改。每次修改由一个正整数 $x$ 定义：
- 找到唯一的索引 $i$，使得 $l_i \le x \le r_i$；
- 设 $a=\min(x, r_i+l_i-x)$，$b=\max(x, r_i+l_i-x)$；
- 反转 $s$ 中从索引 $a$ 到索引 $b$ 的子串。

反转子串 $[a, b]$ 意味着将 $s$ 变为 $s_1, s_2, \dots, s_{a-1},\ s_b, s_{b-1}, \dots, s_{a+1}, s_a,\ s_{b+1}, s_{b+2}, \dots, s_{n-1}, s_n$。

输出所有修改完成后的字符串 $s$。

### 算法分类
差分

### 题解分析与结论
本题的核心在于如何高效处理多次区间翻转操作。大多数题解采用了差分数组或前缀和的方法来统计每个位置被翻转的次数，从而避免直接模拟翻转操作带来的高时间复杂度。差分数组的使用使得每次翻转操作的时间复杂度降为 $O(1)$，最终通过遍历字符串并根据翻转次数的奇偶性来决定是否交换字符。

### 评分较高的题解
#### 1. 作者：Kedit2007 (赞：22)
**星级：5星**
**关键亮点：**
- 使用差分数组统计每个位置被翻转的次数，避免直接模拟翻转操作。
- 通过前缀和优化，最终时间复杂度为 $O(n + q)$，效率高。
- 代码简洁，思路清晰，易于理解。

**核心代码：**
```cpp
for (int i = 0; i < m; i++) {
    int lb = l[i], rb = r[i];
    for (int j = lb - 1, k = rb - 1; j < k; j++, k--) {
        int cnt = arr[j + 1] - arr[lb - 1] + arr[rb] - arr[k];
        if (cnt % 2 == 1) {
            swap(s[j], s[k]);
        }
    }
}
```

#### 2. 作者：Bh_hurter (赞：4)
**星级：4星**
**关键亮点：**
- 使用差分数组记录翻转次数，思路清晰。
- 通过对称性优化，减少不必要的交换操作。
- 代码实现简洁，易于理解。

**核心代码：**
```cpp
for (int i = 1; i <= n; i++) {
    sum += c[j];
    if (sum % 2 != 0) {
        ans[j-1] = s[l[i]+r[i]-j-1];
    }
}
```

#### 3. 作者：BHDwuyulun (赞：0)
**星级：4星**
**关键亮点：**
- 使用差分数组记录翻转次数，避免直接模拟翻转操作。
- 通过映射优化查找区间，减少时间复杂度。
- 代码简洁，思路清晰。

**核心代码：**
```cpp
d[min(x,l[mp[x]]+r[mp[x]]-x)]++;
d[max(x,l[mp[x]]+r[mp[x]]-x)+1]--;
```

### 最优关键思路
1. **差分数组**：通过差分数组记录每个位置被翻转的次数，避免直接模拟翻转操作，时间复杂度从 $O(n \times q)$ 降为 $O(n + q)$。
2. **对称性优化**：利用翻转区间的对称性，减少不必要的交换操作，进一步优化性能。

### 可拓展之处
- 类似的问题可以应用差分数组或前缀和来优化区间操作，如区间加、区间减等。
- 在处理字符串翻转问题时，可以考虑使用平衡树等数据结构来进一步优化。

### 推荐题目
1. [P3391 文艺平衡树](https://www.luogu.com.cn/problem/P3391)
2. [P3368 树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P3372 线段树 1](https://www.luogu.com.cn/problem/P3372)

---
处理用时：30.02秒