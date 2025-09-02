# 题目信息

# Obtaining the String

## 题目描述

You are given two strings $ s $ and $ t $ . Both strings have length $ n $ and consist of lowercase Latin letters. The characters in the strings are numbered from $ 1 $ to $ n $ .

You can successively perform the following move any number of times (possibly, zero):

- swap any two adjacent (neighboring) characters of $ s $ (i.e. for any $ i = \{1, 2, \dots, n - 1\} $ you can swap $ s_i $ and $ s_{i + 1}) $ .

You can't apply a move to the string $ t $ . The moves are applied to the string $ s $ one after another.

Your task is to obtain the string $ t $ from the string $ s $ . Find any way to do it with at most $ 10^4 $ such moves.

You do not have to minimize the number of moves, just find any sequence of moves of length $ 10^4 $ or less to transform $ s $ into $ t $ .

## 说明/提示

In the first example the string $ s $ changes as follows: "abcdef" $ \rightarrow $ "abdcef" $ \rightarrow $ "abdcfe" $ \rightarrow $ "abdfce" $ \rightarrow $ "abdfec".

In the second example there is no way to transform the string $ s $ into the string $ t $ through any allowed moves.

## 样例 #1

### 输入

```
6
abcdef
abdfec
```

### 输出

```
4
3 5 4 5 
```

## 样例 #2

### 输入

```
4
abcd
accd
```

### 输出

```
-1
```

# AI分析结果

### 题目内容重写（中文）

给定两个字符串 $s$ 和 $t$，两个字符串的长度均为 $n$，且由小写拉丁字母组成。字符串中的字符编号从 $1$ 到 $n$。

你可以多次（包括零次）执行以下操作：

- 交换 $s$ 中任意两个相邻的字符（即对于任意 $i = \{1, 2, \dots, n - 1\}$，你可以交换 $s_i$ 和 $s_{i + 1}$）。

你不能对字符串 $t$ 进行任何操作。所有操作都依次应用于字符串 $s$。

你的任务是通过最多 $10^4$ 次操作将字符串 $s$ 转换为字符串 $t$。你不需要最小化操作次数，只需找到一种操作序列，使得操作次数不超过 $10^4$ 次即可。

### 说明/提示

在第一个样例中，字符串 $s$ 的变化如下：  
"abcdef" $ \rightarrow $ "abdcef" $ \rightarrow $ "abdcfe" $ \rightarrow $ "abdfce" $ \rightarrow $ "abdfec"。

在第二个样例中，无法通过任何允许的操作将字符串 $s$ 转换为字符串 $t$。

### 样例 #1

#### 输入

```
6
abcdef
abdfec
```

#### 输出

```
4
3 5 4 5 
```

### 样例 #2

#### 输入

```
4
abcd
accd
```

#### 输出

```
-1
```

---

### 题解分析与结论

#### 综合分析与结论

本题的核心目标是通过交换相邻字符将字符串 $s$ 转换为 $t$。由于题目不要求最小化操作次数，因此可以采用较为简单的贪心或冒泡排序的思路来解决。难点在于如何高效地找到合法的交换序列，并确保操作次数不超过 $10^4$。

大多数题解的思路是：
1. 首先检查 $s$ 和 $t$ 的字符是否相同，若不同则直接输出 `-1`。
2. 对于有解的情况，通过贪心或冒泡排序的方式，逐步将 $s$ 中的字符交换到 $t$ 中的对应位置。

#### 最优关键思路或技巧

1. **字符匹配检查**：通过统计 $s$ 和 $t$ 中每个字符的出现次数，确保两者字符完全相同，否则直接输出 `-1`。
2. **贪心交换**：从左到右遍历 $t$，对于每个字符，在 $s$ 中找到对应的字符，并通过相邻交换将其移动到正确位置。
3. **冒泡排序思想**：将 $s$ 中的字符按照 $t$ 的顺序进行排序，记录每次交换的位置。

#### 可拓展之处

- 类似问题可以扩展到更复杂的字符串操作，如允许交换不相邻的字符，或允许插入、删除操作。
- 类似算法可以应用于其他排序问题，如通过交换相邻元素将数组排序。

#### 推荐题目

1. [P1177 【模板】快速排序](https://www.luogu.com.cn/problem/P1177)  
2. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)  
3. [P1068 分数线划定](https://www.luogu.com.cn/problem/P1068)

---

### 精选题解

#### 题解1：作者：SUNCHAOYI (赞：6)  
**评分：4.5星**  
**关键亮点**：  
- 通过字符统计快速判断无解情况，代码简洁高效。  
- 使用冒泡排序的思想，逐步将 $s$ 中的字符交换到 $t$ 中的对应位置，思路清晰。  
- 代码结构清晰，注释详细，易于理解。

**核心代码**：
```cpp
for(int i = 0;i < n;i++)
{
    for(int j = 0;j < n;j++)
    {
        if(a[j] == b[i] && in[j] == 0)
        {
            in[j] = i;
            break;
        }
    }
}
for(int i = 1;i <= n;i++)
{
    for(int j = 0;j < n - 1;j++)
    {
        if(in[j] > in[j + 1])
        {
            ans[++k] = j + 1;
            swap(in[j],in[j + 1]);
        }
    }
}
```

#### 题解2：作者：EightSixSun (赞：2)  
**评分：4星**  
**关键亮点**：  
- 使用队列记录交换过程，代码实现简洁。  
- 通过贪心思想，逐步将 $s$ 中的字符交换到 $t$ 中的对应位置，思路清晰。  
- 代码结构清晰，易于理解。

**核心代码**：
```cpp
For(i,1,n)
{
    For(j,1,n-1)
    {
        if(sd[j] > sd[j+1])
        {
            ans.push(j);
            swap(sd[j],sd[j+1]);
        }
    }
}
```

#### 题解3：作者：CQ_Bab (赞：1)  
**评分：4星**  
**关键亮点**：  
- 通过贪心思想，逐步将 $s$ 中的字符交换到 $t$ 中的对应位置，思路清晰。  
- 代码实现简洁，注释详细，易于理解。  
- 使用 `vector` 记录交换过程，代码结构清晰。

**核心代码**：
```cpp
while(!check()) {
    rep(i,1,n) {
        if(s[i] != t[i]) {
            int stop = false;
            rep(j,i+1,n) {
                if(t[i] == s[j]) {
                    stop = j;
                    break;
                }
            }
            rep1(j,stop,i+1) {
                ans.pb(j-1);
                swap(s[j-1],s[j]);
            }
            break;
        }
    }
}
```

---
处理用时：39.56秒