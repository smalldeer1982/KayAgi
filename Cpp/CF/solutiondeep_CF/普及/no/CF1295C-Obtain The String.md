# 题目信息

# Obtain The String

## 题目描述

You are given two strings $ s $ and $ t $ consisting of lowercase Latin letters. Also you have a string $ z $ which is initially empty. You want string $ z $ to be equal to string $ t $ . You can perform the following operation to achieve this: append any subsequence of $ s $ at the end of string $ z $ . A subsequence is a sequence that can be derived from the given sequence by deleting zero or more elements without changing the order of the remaining elements. For example, if $ z = ac $ , $ s = abcde $ , you may turn $ z $ into following strings in one operation:

1. $ z = acace $ (if we choose subsequence $ ace $ );
2. $ z = acbcd $ (if we choose subsequence $ bcd $ );
3. $ z = acbce $ (if we choose subsequence $ bce $ ).

Note that after this operation string $ s $ doesn't change.

Calculate the minimum number of such operations to turn string $ z $ into string $ t $ .

## 样例 #1

### 输入

```
3
aabce
ace
abacaba
aax
ty
yyt```

### 输出

```
1
-1
3```

# AI分析结果

【题目内容重写】
# 获取字符串

## 题目描述

给定两个由小写拉丁字母组成的字符串 $s$ 和 $t$。另外，你有一个初始为空的字符串 $z$。你希望将字符串 $z$ 变成字符串 $t$。你可以通过以下操作来实现：将 $s$ 的任意子序列追加到字符串 $z$ 的末尾。子序列是指通过删除零个或多个元素而不改变剩余元素的顺序从给定序列中派生的序列。例如，如果 $z = ac$，$s = abcde$，你可以通过一次操作将 $z$ 变成以下字符串：

1. $z = acace$（如果选择子序列 $ace$）；
2. $z = acbcd$（如果选择子序列 $bcd$）；
3. $z = acbce$（如果选择子序列 $bce$）。

注意，此操作后字符串 $s$ 不会改变。

计算将字符串 $z$ 变成字符串 $t$ 所需的最少操作次数。

## 样例 #1

### 输入

```
3
aabce
ace
abacaba
aax
ty
yyt```

### 输出

```
1
-1
3```

【算法分类】
贪心

【题解分析与结论】
本题的核心思路是通过贪心算法，尽可能在每次操作中选择最长的子序列来减少操作次数。难点在于如何高效地找到 $t$ 中每个字符在 $s$ 中的位置，并判断是否需要开始新的操作。以下是各题解的要点对比：

1. **xiaomuyun**：使用 `vector` 存储每个字符在 $s$ 中的位置，通过二分查找来快速定位字符。思路清晰，代码可读性好，优化程度较高。
2. **yeaDonaby**：同样使用 `vector` 存储字符位置，通过 `upper_bound` 进行二分查找。代码简洁，逻辑清晰，但初始化部分略显冗余。
3. **ix35**：使用子序列自动机的方法，通过构建 `nx` 数组和 `fir` 数组来快速查找字符位置。思路新颖，但代码复杂度较高。
4. **Deft_t**：与 xiaomuyun 和 yeaDonaby 的思路类似，使用 `vector` 存储字符位置，通过二分查找来定位字符。代码简洁，逻辑清晰。
5. **YLWang**：使用 `vector` 存储字符位置，通过二分查找来定位字符。代码简洁，逻辑清晰，但初始化部分略显冗余。
6. **E1_de5truct0r**：使用 `vector` 存储字符位置，通过二分查找来定位字符。代码简洁，逻辑清晰，但初始化部分略显冗余。

【评分较高的题解】
1. **xiaomuyun**（5星）
   - 关键亮点：使用 `vector` 存储字符位置，通过二分查找来快速定位字符，代码可读性好，优化程度较高。
   - 核心代码：
     ```cpp
     for(int i=1;i<=m;++i){
         int it=upper_bound(v[t[i]].begin(),v[t[i]].end(),lst)-v[t[i]].begin();
         if(it>=v[t[i]].size()) lst=v[t[i]][0],++cnt;
         else lst=v[t[i]][it];
     }
     ```

2. **yeaDonaby**（4星）
   - 关键亮点：使用 `vector` 存储字符位置，通过 `upper_bound` 进行二分查找，代码简洁，逻辑清晰。
   - 核心代码：
     ```cpp
     for(R int i=0; i<t.length(); i++){
         int v=t[i]-'a';
         if(k[v].back()<=pop){
             ans++;
             pop=k[v].front();
         }
         else{
             pop=k[v][upper_bound(k[v].begin(),k[v].end(),pop)-k[v].begin()];
         }
     }
     ```

3. **Deft_t**（4星）
   - 关键亮点：使用 `vector` 存储字符位置，通过二分查找来定位字符，代码简洁，逻辑清晰。
   - 核心代码：
     ```cpp
     for(int i = 0;i < t.length();i++){
         int pos = upper_bound(v[t[i]].begin(),v[t[i]].end(),lst)-v[t[i]].begin();
         if(pos < v[t[i]].size()){
             lst = v[t[i]][pos];
         }
         else{
             lst = v[t[i]][0];
             ans++;
         }
     }
     ```

【最优关键思路或技巧】
- 使用 `vector` 存储每个字符在 $s$ 中的位置，通过二分查找来快速定位字符，从而减少操作次数。
- 贪心策略：每次操作尽可能选择最长的子序列，以减少操作次数。

【可拓展之处】
- 类似问题：在字符串匹配或子序列匹配问题中，可以使用类似的数据结构和算法来优化查找效率。
- 同类型题：P3375 【模板】KMP字符串匹配、P3805 【模板】Manacher算法、P3370 【模板】字符串哈希。

【推荐题目】
1. P3375 【模板】KMP字符串匹配
2. P3805 【模板】Manacher算法
3. P3370 【模板】字符串哈希

---
处理用时：34.44秒