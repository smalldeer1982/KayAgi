# 题目信息

# WOW Factor

## 题目描述

Recall that string $ a $ is a subsequence of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly zero or all) characters. For example, for the string $ a $ ="wowwo", the following strings are subsequences: "wowwo", "wowo", "oo", "wow", "", and others, but the following are not subsequences: "owoo", "owwwo", "ooo".

The wow factor of a string is the number of its subsequences equal to the word "wow". Bob wants to write a string that has a large wow factor. However, the "w" key on his keyboard is broken, so he types two "v"s instead.

Little did he realise that he may have introduced more "w"s than he thought. Consider for instance the string "ww". Bob would type it as "vvvv", but this string actually contains three occurrences of "w":

- "vvvv"
- "vvvv"
- "vvvv"

For example, the wow factor of the word "vvvovvv" equals to four because there are four wows:

- "vvvovvv"
- "vvvovvv"
- "vvvovvv"
- "vvvovvv"

Note that the subsequence "vvvovvv" does not count towards the wow factor, as the "v"s have to be consecutive.

For a given string $ s $ , compute and output its wow factor. Note that it is not guaranteed that it is possible to get $ s $ from another string replacing "w" with "vv". For example, $ s $ can be equal to "vov".

## 说明/提示

The first example is explained in the legend.

## 样例 #1

### 输入

```
vvvovvv
```

### 输出

```
4
```

## 样例 #2

### 输入

```
vvovooovovvovoovoovvvvovovvvov
```

### 输出

```
100
```

# AI分析结果

### 题目重写
# WOW因子

## 题目描述

回忆一下，字符串 $a$ 是字符串 $b$ 的子序列，如果 $a$ 可以通过删除 $b$ 中的若干（可能为零或全部）字符得到。例如，对于字符串 $a$ ="wowwo"，以下字符串是子序列："wowwo", "wowo", "oo", "wow", "", 以及其他，但以下不是子序列："owoo", "owwwo", "ooo"。

字符串的 WOW 因子是其子序列中等于 "wow" 的数量。Bob 想写一个具有高 WOW 因子的字符串。然而，他键盘上的 "w" 键坏了，所以他用两个 "v" 代替。

他没有意识到，他可能引入了比想象中更多的 "w"。例如，字符串 "ww"。Bob 会将其输入为 "vvvv"，但这个字符串实际上包含三个 "w" 的出现：

- "vvvv"
- "vvvv"
- "vvvv"

例如，单词 "vvvovvv" 的 WOW 因子等于四，因为有四个 "wow"：

- "vvvovvv"
- "vvvovvv"
- "vvvovvv"
- "vvvovvv"

注意，子序列 "vvvovvv" 不计入 WOW 因子，因为 "v" 必须连续。

对于给定的字符串 $s$，计算并输出其 WOW 因子。注意，不能保证 $s$ 可以通过将 "w" 替换为 "vv" 从另一个字符串得到。例如，$s$ 可以等于 "vov"。

## 说明/提示

第一个例子在题目描述中解释。

## 样例 #1

### 输入

```
vvvovvv
```

### 输出

```
4
```

## 样例 #2

### 输入

```
vvovooovovvovoovoovvvvovovvvov
```

### 输出

```
100
```

### 算法分类
前缀和

### 题解分析与结论
该题的核心思路是通过前缀和和后缀和来计算每个 `o` 左右两侧的 `vv` 对数，然后利用乘法原理计算总的 `wow` 子序列数。大多数题解都采用了类似的方法，区别在于具体实现细节和优化程度。

### 高星题解推荐
1. **作者：jijidawang (5星)**
   - **关键亮点**：详细解释了前缀和和后缀和的计算方法，并给出了清晰的代码实现。通过 Iverson Bracket 优化了计算过程，时间复杂度为 $O(n)$。
   - **代码核心**：
     ```cpp
     for (int i=1; i<n; i++) pre[i] = pre[i-1] + ((s[i] == 'v') && (s[i+1] == 'v'));
     for (int i=n-1; i>=1; i--) suf[i] = suf[i+1] + ((s[i] == 'v') && (s[i+1] == 'v'));
     for (int i=1; i<n; i++)
         if (s[i] == 'o') ans += 1ll * pre[i-1] * suf[i];
     ```

2. **作者：灵茶山艾府 (4星)**
   - **关键亮点**：提供了两种解法，一种是前后缀分解，另一种是状态机 DP。状态机 DP 的解法虽然复杂度相同，但思路新颖，适合扩展思维。
   - **代码核心**：
     ```go
     for i := 1; i < n; i++ {
         if s[i] == 'o' {
             f1 += f0
         } else if s[i-1] == 'v' {
             f2 += f1
             f0++
         }
     }
     ```

3. **作者：K_Madoka (4星)**
   - **关键亮点**：简洁明了地实现了前缀和和后缀和的计算，代码可读性强，适合初学者理解。
   - **代码核心**：
     ```cpp
     for(int i=1;i<n;i++){
         if(s[i]=='v'&&s[i-1]=='v') a[i]=a[i-1]+1;
         else a[i]=a[i-1];
     }
     for(int i=n-1;i>=1;i--){
         if(s[i]=='v'&&s[i+1]=='v') b[i]=b[i+1]+1;
         else b[i]=b[i+1];
     }
     ```

### 最优关键思路
1. **前缀和与后缀和**：通过预处理每个 `o` 左右两侧的 `vv` 对数，利用乘法原理计算总的 `wow` 子序列数。
2. **Iverson Bracket 优化**：通过布尔表达式简化计算，减少不必要的条件判断。
3. **状态机 DP**：通过状态转移方程动态计算 `wow` 子序列数，适合扩展思维。

### 拓展思路
类似的问题可以扩展到其他子序列计数问题，例如计算特定模式的子序列数。可以尝试使用动态规划或前缀和等方法来优化计算。

### 推荐题目
1. [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)
2. [P1045 最大子段和](https://www.luogu.com.cn/problem/P1045)
3. [P1216 数字三角形](https://www.luogu.com.cn/problem/P1216)

---
处理用时：36.08秒