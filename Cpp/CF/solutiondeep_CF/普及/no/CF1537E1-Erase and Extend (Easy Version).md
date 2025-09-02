# 题目信息

# Erase and Extend (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference is the constraints on $ n $ and $ k $ . You can make hacks only if all versions of the problem are solved.

You have a string $ s $ , and you can do two types of operations on it:

- Delete the last character of the string.
- Duplicate the string: $ s:=s+s $ , where $ + $ denotes concatenation.

You can use each operation any number of times (possibly none).

Your task is to find the lexicographically smallest string of length exactly $ k $ that can be obtained by doing these operations on string $ s $ .

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a\ne b $ ;
- In the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 说明/提示

In the first test, it is optimal to make one duplication: "dbcadabc" $ \to $ "dbcadabcdbcadabc".

In the second test it is optimal to delete the last $ 3 $ characters, then duplicate the string $ 3 $ times, then delete the last $ 3 $ characters to make the string have length $ k $ .

"abcd" $ \to $ "abc" $ \to $ "ab" $ \to $ "a" $ \to $ "aa" $ \to $ "aaaa" $ \to $ "aaaaaaaa" $ \to $ "aaaaaaa" $ \to $ "aaaaaa" $ \to $ "aaaaa".

## 样例 #1

### 输入

```
8 16
dbcadabc```

### 输出

```
dbcadabcdbcadabc```

## 样例 #2

### 输入

```
4 5
abcd```

### 输出

```
aaaaa```

# AI分析结果

### 题目内容重写
# 删除与扩展（简单版）

## 题目描述

这是该问题的简单版，唯一的区别是对 $n$ 和 $k$ 的限制。只有当所有版本的问题都被解决时，你才能进行 hack。

你有一个字符串 $s$，你可以对它进行两种操作：

- 删除字符串的最后一个字符。
- 复制字符串：$s:=s+s$，其中 $+$ 表示字符串连接。

你可以使用每种操作任意次数（也可以不使用）。

你的任务是通过对字符串 $s$ 进行这些操作，找到长度为 $k$ 的字典序最小的字符串。

字符串 $a$ 的字典序小于字符串 $b$ 当且仅当以下条件之一成立：

- $a$ 是 $b$ 的前缀，但 $a \ne b$；
- 在 $a$ 和 $b$ 第一个不同的位置，$a$ 中的字母在字母表中比 $b$ 中对应的字母更靠前。

## 说明/提示

在第一个测试中，最优操作是进行一次复制："dbcadabc" $\to$ "dbcadabcdbcadabc"。

在第二个测试中，最优操作是删除最后 $3$ 个字符，然后复制字符串 $3$ 次，最后删除最后 $3$ 个字符以使字符串长度为 $k$。

"abcd" $\to$ "abc" $\to$ "ab" $\to$ "a" $\to$ "aa" $\to$ "aaaa" $\to$ "aaaaaaaa" $\to$ "aaaaaaa" $\to$ "aaaaaa" $\to$ "aaaaa"。

## 样例 #1

### 输入

```
8 16
dbcadabc```

### 输出

```
dbcadabcdbcadabc```

## 样例 #2

### 输入

```
4 5
abcd```

### 输出

```
aaaaa```

### 算法分类
字符串、贪心

### 题解分析与结论
本题的核心思想是通过删除和复制操作，找到字符串 $s$ 的一个前缀，然后通过复制该前缀来构造长度为 $k$ 的字典序最小的字符串。所有题解都采用了暴力枚举前缀的方法，通过比较不同前缀生成的字符串的字典序来找到最优解。

### 精选题解
1. **作者：NightmareAlita**  
   **星级：4**  
   **关键亮点：** 该题解通过逆向思维，从前往后扫描字符串，找到最优前缀的长度 $l$，然后通过 $i \bmod l$ 来构造最终字符串。这种方法避免了不必要的复制操作，提高了效率。  
   **代码核心思想：**  
   ```cpp
   for (int i = 0; i < n; ++i) {
       if (s[i] < s[i % l]) { l = i + 1; }
       else if (s[i] > s[i % l]) { break; }
   }
   for (int i = 0; i < k; ++i) {
       cout << s[i % l];
   }
   ```
   **个人心得：** 通过逆向思维，从前往后扫描字符串，可以更高效地找到最优前缀。

2. **作者：xxxr_2024**  
   **星级：4**  
   **关键亮点：** 该题解通过遍历字符串，找到最优前缀的长度 $l$，然后通过 $i \bmod l$ 来构造最终字符串。思路清晰，代码简洁。  
   **代码核心思想：**  
   ```cpp
   for(int i=0;i<n;i++) {
       if(s[i]>s[i%l]) break;
       else if(s[i]<s[i%l]) l=i+1;
   }
   for(int i=0;i<k;i++) cout<<s[i%l];
   ```
   **个人心得：** 通过遍历字符串，可以快速找到最优前缀，避免了不必要的复制操作。

3. **作者：zhang_kevin**  
   **星级：4**  
   **关键亮点：** 该题解通过遍历字符串的前缀，找到最优前缀，然后通过复制该前缀来构造最终字符串。思路清晰，代码简洁。  
   **代码核心思想：**  
   ```cpp
   string get(string s, int k){
       while(s.length() < k) s = s + s;
       while(s.length() > k) s.pop_back();
       return s;
   }
   for(int i = 1; i < n; i++){
       if(s[i] > s[0]) break;
       str += s[i];
       Min = min(Min, get(str, k));
   }
   ```
   **个人心得：** 通过遍历字符串的前缀，可以快速找到最优解，避免了不必要的复制操作。

### 最优关键思路
通过遍历字符串的前缀，找到最优前缀，然后通过复制该前缀来构造最终字符串。这种方法避免了不必要的复制操作，提高了效率。

### 拓展思路
类似的问题可以通过遍历字符串的前缀，找到最优解。例如，可以通过遍历字符串的前缀，找到字典序最小的子串。

### 推荐题目
1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P3805 【模板】manacher算法](https://www.luogu.com.cn/problem/P3805)
3. [P3834 【模板】可持久化线段树 1](https://www.luogu.com.cn/problem/P3834)

---
处理用时：34.86秒