# 题目信息

# Diverse Substring

## 题目描述

You are given a string $ s $ , consisting of $ n $ lowercase Latin letters.

A substring of string $ s $ is a continuous segment of letters from $ s $ . For example, "defor" is a substring of "codeforces" and "fors" is not.

The length of the substring is the number of letters in it.

Let's call some string of length $ n $ diverse if and only if there is no letter to appear strictly more than $ \frac n 2 $ times. For example, strings "abc" and "iltlml" are diverse and strings "aab" and "zz" are not.

Your task is to find any diverse substring of string $ s $ or report that there is none. Note that it is not required to maximize or minimize the length of the resulting substring.

## 说明/提示

The first example has lots of correct answers.

Please, restrain yourself from asking if some specific answer is correct for some specific test or not, these questions always lead to "No comments" answer.

## 样例 #1

### 输入

```
10
codeforces
```

### 输出

```
YES
code
```

## 样例 #2

### 输入

```
5
aaaaa
```

### 输出

```
NO
```

# AI分析结果

### 题目内容重写
# 多样子串

## 题目描述

给定一个由 $n$ 个小写拉丁字母组成的字符串 $s$。

字符串 $s$ 的子串是指从 $s$ 中连续取出的字母段。例如，"defor" 是 "codeforces" 的子串，而 "fors" 不是。

子串的长度是指其中字母的个数。

我们称一个长度为 $n$ 的字符串为“多样”的，当且仅当没有任何一个字母出现的次数严格超过 $\frac{n}{2}$ 次。例如，字符串 "abc" 和 "iltlml" 是多样的，而字符串 "aab" 和 "zz" 不是。

你的任务是找到字符串 $s$ 中的任意一个多样子串，或者报告不存在这样的子串。注意，不需要最大化或最小化结果子串的长度。

## 说明/提示

第一个样例有很多正确答案。

请不要询问某个特定测试的特定答案是否正确，这些问题总是会导致“无可奉告”的回答。

## 样例 #1

### 输入

```
10
codeforces
```

### 输出

```
YES
code
```

## 样例 #2

### 输入

```
5
aaaaa
```

### 输出

```
NO
```

### 题解分析与结论

#### 思路对比
所有题解的核心思路都是寻找相邻且不相同的两个字符，这样的子串长度为2，必然满足“多样”的条件。这种方法的时间复杂度为 $O(n)$，非常高效。

#### 难点
1. **理解题意**：需要明确“多样”子串的定义，即没有任何一个字符的出现次数超过子串长度的一半。
2. **优化思路**：直接寻找长度为2的相邻不同字符，避免复杂的枚举和统计。

#### 最优思路
最优的思路是直接遍历字符串，寻找相邻且不相同的两个字符。这种方法简单高效，且代码实现容易。

#### 可拓展之处
类似的问题可以扩展到寻找满足其他条件的子串，例如字符种类数、字符出现频率等。可以通过调整判断条件来适应不同的需求。

### 推荐题目
1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P3805 【模板】Manacher算法](https://www.luogu.com.cn/problem/P3805)
3. [P3919 【模板】可持久化线段树](https://www.luogu.com.cn/problem/P3919)

### 精选题解

#### 题解1：Annihilation_y
**星级**：★★★★★
**关键亮点**：代码简洁，思路清晰，直接寻找相邻不同字符，时间复杂度低。
**代码核心**：
```cpp
for (int i=2;i<=len;i++)
{
    if(s[i]!=s[i-1])
    {
        printf("YES\n");
        cout<<s[i-1]<<s[i];
        return 0;
    }
}
printf("NO");
```

#### 题解2：liuyz11
**星级**：★★★★
**关键亮点**：思路明确，代码结构清晰，使用了`rep`宏简化代码。
**代码核心**：
```cpp
rep(i, 1, len - 1){
    if(st[i] != ch){
        puts("YES");
        printf("%c%c\n", ch, st[i]);
        return 0;
    }
}
puts("NO");
```

#### 题解3：decoqwq
**星级**：★★★★
**关键亮点**：思路简单直接，代码易读，适合初学者理解。
**代码核心**：
```cpp
for(int i=1;i<n;i++)
{
    if(s[i]!=s[i-1])
    {
        printf("YES\n%c%c",s[i-1],s[i]);
        return 0;
    }
}
cout<<"NO";
```

### 个人心得总结
- **调试经历**：部分题解在边界条件处理上不够严谨，例如从0开始遍历时可能导致数组越界。
- **踩坑教训**：在判断相邻字符时，确保遍历范围正确，避免越界错误。
- **顿悟感想**：通过寻找长度为2的相邻不同字符，可以大大简化问题，避免复杂的统计和枚举。

---
处理用时：30.38秒