# 题目信息

# [ARC113C] String Invasion

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc113/tasks/arc113_c

長さ $ N $ の文字列 $ S $ が与えられます。$ S $ の $ i $ 文字目を $ s_i $ で表します。以下の操作を繰り返せる回数の最大値を求めてください。

- 連続する $ 3 $ 文字 $ s_i,s_{i+1},s_{i+2}\quad\ (1\leq\ i\leq\ |S|-2) $ であって、$ s_i=s_{i+1}\neq\ s_{i+2} $ であるものを選ぶ。$ s_{i+2} $ を $ s_i $ で置き換える。

## 说明/提示

### 制約

- $ 3\ \leq\ |S|\ \leq\ 2\times\ 10^5 $
- $ S $ は英小文字からなる

### Sample Explanation 1

以下のように $ 3 $ 回の操作を行うことができます。 - $ i=2 $ に対して操作を行う。操作後の文字列は `acccpt` になる。 - $ i=3 $ に対して操作を行う。操作後の文字列は `acccct` になる。 - $ i=4 $ に対して操作を行う。操作後の文字列は `accccc` になる。

## 样例 #1

### 输入

```
accept```

### 输出

```
3```

## 样例 #2

### 输入

```
atcoder```

### 输出

```
0```

## 样例 #3

### 输入

```
anerroroccurred```

### 输出

```
16```

# AI分析结果



# [ARC113C] String Invasion

## 题目描述

给定长度为 $N$ 的字符串 $S$，每次操作选择满足 $s_i=s_{i+1}\neq s_{i+2}$ 的连续三字符，将 $s_{i+2}$ 替换为 $s_i$。求最多可执行的操作次数。

### 样例解释
样例1：`accept` → 3次操作后全变为`c`  
样例2：`atcoder` → 无合法操作  
样例3：`anerroroccurred` → 16次操作

## 算法分类
贪心

## 题解分析

各题解核心思路均为**从后往前贪心**，维护字符出现次数数组。当发现连续两个相同字符时，计算可替换的字符数（总长度 - 当前下标 - 已有该字符数），清空统计数组并记录当前字符覆盖后续所有位置。

### 优质题解推荐

1. **Binary_Lee（4.5星）**  
   **亮点**：清晰的变量命名与逻辑分层  
   **关键思路**：  
   ```cpp
   sum[s[s.size()-1]]++;  // 初始化最后两个字符计数
   sum[s[s.size()-2]]++;
   for(int i=s.size()-3;i>=0;i--) {
       sum[s[i]]++;
       if(s[i]==s[i+1] && s[i+1]!=s[i+2]) {
           ans += s.size()-i - sum[s[i]];  // 计算可操作次数
           memset(sum,0,sizeof(sum));      // 清空统计数组
           sum[s[i]] = s.size()-i;         // 设置当前字符覆盖后续
       }
   }
   ```

2. **So_noSlack（4星）**  
   **亮点**：详细的样例推导与注释  
   **代码片段**：  
   ```cpp
   num[str[n-1]-'a']++;  // 初始化后两位
   num[str[n-2]-'a']++;
   for(int i=n-3;i>=0;i--) {
       num[str[i]-'a']++;
       if(str[i]==str[i+1] && str[i+1]!=str[i+2]) {
           ans += n-i - num[str[i]-'a'];  // 有效替换次数
           memset(num,0,sizeof(num));     // 重置统计
           num[str[i]-'a'] = n-i;         // 更新覆盖情况
       }
   }
   ```

3. **zimujum（4星）**  
   **个人心得**：通过暴力解法推导出优化思路  
   **核心实现**：  
   ```cpp
   if(s[i]==s[i+1]) {
       sum += ans - v[s[i]-'a'+1];  // 减去已有相同字符
       memset(v,0,sizeof(v));       // 清空统计
       v[s[i]-'a'+1] = ans;         // 设置覆盖后的计数
   }
   ```

## 关键技巧
- **逆向贪心**：从后往前处理可避免覆盖后续操作机会  
- **字符统计数组**：动态维护已存在的字符数量，避免重复计算  
- **覆盖重置机制**：每次操作后清空统计，重新记录覆盖后的字符分布

## 拓展应用
类似需要最大化操作次数的字符串修改问题（如CF1625C、ABC290E），均可尝试逆向贪心+状态覆盖的思路。

## 相似题目推荐
1. [P1071 潜伏者](https://www.luogu.com.cn/problem/P1071)  
2. [CF1107B Digital root](https://www.luogu.com.cn/problem/CF1107B)  
3. [ABC259D Circumferences](https://www.luogu.com.cn/problem/ABC259D)

---
处理用时：61.39秒