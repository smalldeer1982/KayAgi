# 题目信息

# Reberland Linguistics

## 题目描述

First-rate specialists graduate from Berland State Institute of Peace and Friendship. You are one of the most talented students in this university. The education is not easy because you need to have fundamental knowledge in different areas, which sometimes are not related to each other.

For example, you should know linguistics very well. You learn a structure of Reberland language as foreign language. In this language words are constructed according to the following rules. First you need to choose the "root" of the word — some string which has more than $ 4 $ letters. Then several strings with the length $ 2 $ or $ 3 $ symbols are appended to this word. The only restriction —  it is not allowed to append the same string twice in a row. All these strings are considered to be suffixes of the word (this time we use word "suffix" to describe a morpheme but not the few last characters of the string as you may used to).

Here is one exercise that you have found in your task list. You are given the word $ s $ . Find all distinct strings with the length $ 2 $ or $ 3 $ , which can be suffixes of this word according to the word constructing rules in Reberland language.

Two strings are considered distinct if they have different length or there is a position in which corresponding characters do not match.

Let's look at the example: the word $ abacabaca $ is given. This word can be obtained in the following ways: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF666A/db0a6930c8ac7df2b263a19be9a4e03f20d4a6b4.png), where the root of the word is overlined, and suffixes are marked by "corners". Thus, the set of possible suffixes for this word is $ {aca,ba,ca} $ .

## 说明/提示

The first test was analysed in the problem statement.

In the second example the length of the string equals $ 5 $ . The length of the root equals 5, so no string can be used as a suffix.

## 样例 #1

### 输入

```
abacabaca
```

### 输出

```
3
aca
ba
ca
```

## 样例 #2

### 输入

```
abaca
```

### 输出

```
0
```

# AI分析结果



# 题目中文翻译

# Reberland语言学

## 题目描述

一流专家毕业于Berland国立和平友谊学院。你是这所大学最有天赋的学生之一。这里的教育并不轻松，因为你需要在不同领域（有时互不相关）拥有扎实的基础知识。

例如，你必须精通语言学。作为外语，你正在学习Reberland语言的结构。这种语言的单词构造遵循以下规则：首先选择一个长度超过4个字母的"词根"，然后在其后追加多个长度为2或3的后缀字符串。唯一限制是——不允许连续追加相同的字符串。这些追加的字符串都被视为单词的后缀（这里的"后缀"指语素概念，而非通常理解的字符串末尾字符）。

你任务列表中有这样一道练习题：给定单词$ s $，找出所有可能作为合法后缀的互异长度为2或3的字符串集合。两个字符串被认为是不同的当且仅当长度不同或存在至少一个位置的字符不同。

例如给定单词$ abacabaca $，可能的构造方式如右图所示，其中词根下划线标注，后缀用尖角符号标记。此时合法的后缀集合是$ {aca,ba,ca} $。

# 算法分类
动态规划

# 题解分析与结论

## 核心思路
两篇题解均采用逆向动态规划解法：
1. **状态设计**：`dp[i][0/1]`表示从位置i开始取2/3长度的子串是否合法
2. **转移方程**：
   - 末尾情况直接合法
   - 后续接不同长度的后缀直接转移
   - 后续接相同长度的后缀需比较子串差异
3. **结果收集**：使用集合去重统计所有合法子串

## 最优题解

### 题解作者：Froggy（★★★★☆）
**关键亮点**：
1. 清晰的状态转移分类处理
2. 高效实现子串比较逻辑
3. 使用集合自动处理重复项

**核心代码解析**：
```cpp
for(int i=len-1;i>=5;i--){
    // 处理长度为2的后缀
    if(i+2<len){
        if(dp[i+2][1]) dp[i][0]=1; // 接3长度后缀
        // 接2长度后缀需比较子串差异
        if(dp[i+2][0] && (s[i+1]!=s[i+3] || s[i]!=s[i+2])) 
            dp[i][0]=1;
    }
    // 处理长度为3的后缀（逻辑类似）
}
```

# 关键技巧总结
1. **逆向DP设计**：从字符串末尾向前推导，便于处理后缀限制条件
2. **复合状态转移**：通过`0/1`状态区分不同长度后缀的合法性
3. **剪枝优化**：在转移时直接比较子串差异，避免无效状态扩展
4. **自动去重**：利用集合特性简化结果处理

# 类似题目推荐
1. [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147) - 子串分解问题
2. [P2679 子串](https://www.luogu.com.cn/problem/P2679) - 复合状态动态规划
3. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040) - 区间划分的动态规划

# 题解心得摘录
作者在题解中提到："相邻两个永远不会相同"的判断需要特别注意子串比较的范围。通过`(s[i+1]!=s[i+3] || s[i]!=s[i+2])`的条件，巧妙避免了存储完整子串，直接通过字符位置比较实现高效判断，这一实现方式体现了对问题本质的深刻理解。

---
处理用时：71.31秒