# 题目信息

# Comparison String

## 题目描述

You are given a string $ s $ of length $ n $ , where each character is either &lt; or &gt;.

An array $ a $ consisting of $ n+1 $ elements is compatible with the string $ s $ if, for every $ i $ from $ 1 $ to $ n $ , the character $ s_i $ represents the result of comparing $ a_i $ and $ a_{i+1} $ , i. e.:

- $ s_i $ is &lt; if and only if $ a_i < a_{i+1} $ ;
- $ s_i $ is &gt; if and only if $ a_i > a_{i+1} $ .

For example, the array $ [1, 2, 5, 4, 2] $ is compatible with the string &lt;&lt;&gt;&gt;. There are other arrays with are compatible with that string, for example, $ [13, 37, 42, 37, 13] $ .

The cost of the array is the number of different elements in it. For example, the cost of $ [1, 2, 5, 4, 2] $ is $ 4 $ ; the cost of $ [13, 37, 42, 37, 13] $ is $ 3 $ .

You have to calculate the minimum cost among all arrays which are compatible with the given string $ s $ .

## 说明/提示

In the first test case of the example, the array can be $ [13, 37, 42, 37, 13] $ .

In the second test case of the example, the array can be $ [42, 37, 13, 37, 42] $ .

## 样例 #1

### 输入

```
4
4
<<>>
4
>><<
5
>>>>>
7
<><><><
```

### 输出

```
3
3
6
2```

# AI分析结果

### 题目翻译
#### 比较字符串

#### 题目描述
给定一个长度为 $n$ 的字符串 $s$，其中每个字符要么是 `<` 要么是 `>`。

如果一个由 $n + 1$ 个元素组成的数组 $a$ 满足以下条件，则称该数组与字符串 $s$ 兼容：对于从 $1$ 到 $n$ 的每个 $i$，字符 $s_i$ 表示 $a_i$ 和 $a_{i + 1}$ 的比较结果，即：
- 当且仅当 $a_i < a_{i + 1}$ 时，$s_i$ 为 `<`；
- 当且仅当 $a_i > a_{i + 1}$ 时，$s_i$ 为 `>`。

例如，数组 $[1, 2, 5, 4, 2]$ 与字符串 `<<>>` 兼容。还有其他与该字符串兼容的数组，例如 $[13, 37, 42, 37, 13]$。

数组的代价是数组中不同元素的数量。例如，$[1, 2, 5, 4, 2]$ 的代价是 $4$；$[13, 37, 42, 37, 13]$ 的代价是 $3$。

你需要计算所有与给定字符串 $s$ 兼容的数组中的最小代价。

#### 说明/提示
在样例的第一个测试用例中，数组可以是 $[13, 37, 42, 37, 13]$。
在样例的第二个测试用例中，数组可以是 $[42, 37, 13, 37, 42]$。

#### 样例 #1
##### 输入
```
4
4
<<>>
4
>><<
5
>>>>>
7
<><><><
```
##### 输出
```
3
3
6
2
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是通过寻找字符串中最长的连续相同符号子串，其长度加 1 即为与给定字符串兼容的数组的最小代价。不同题解在思路阐述方式和代码实现细节上有所不同，但本质相同。
- **思路**：都通过分析样例或对大小关系进行推理，得出要使数组中不同元素数量最少，关键在于利用连续相同符号的特性，即连续相同符号对应的数组元素需不同，而符号变化时可复用之前的元素。
- **算法要点**：遍历字符串，统计连续相同符号的长度，记录最大值，最后最大值加 1 得到结果。
- **解决难点**：主要是理解如何通过连续相同符号子串的长度来确定最小代价，以及处理字符串遍历过程中连续符号长度的统计和更新。

### 所选题解
- **作者：__Dist__ (赞：2)，4星**
    - **关键亮点**：思路清晰，先对题目进行简洁翻译，再通过分析样例得出结论，代码注释详细，易于理解。
- **作者：YCSluogu (赞：2)，4星**
    - **关键亮点**：通过无根树的方式解释题意，使思路更形象，代码简洁。
- **作者：CheZiHe929 (赞：0)，4星**
    - **关键亮点**：通过多组数据样例分析得出规律，代码注释详细，对特殊情况有处理说明。

### 重点代码
```cpp
// __Dist__ 的代码
int maxn = 0; //储存最长的连续相同符号
int sum = 1; //当前连续符号的长度
char now = s[0]; //判断是否与上个符号相同
for (int i = 1; i < n; i++) {
    if (s[i] == now) sum++;
    else {
        maxn = max(maxn, sum); //取最大值
        sum = 1; //当前长度归1
        now = s[i]; //更新now
    }
}
maxn = max(maxn, sum); //这里还要取一次最大值
cout << maxn + 1 << endl;

// YCSluogu 的代码
int tot = 1;
int ans = 1;
for (int i = 1; i < str.size(); i++) {
    tot = str[i] == str[i - 1] ? tot + 1 : 1;
    ans = std::max(ans, tot);
}
cout << ans + 1 << endl;

// CheZiHe929 的代码
int maxn=0,sum=1;
char now=s[0];
for(int i=1;i<n;i++){
    if(s[i]==now)sum++;
    else {
        maxn=max(maxn,sum);
        sum=1;
        now=s[i];
    }
}
maxn=max(maxn,sum);
cout<<maxn+1<<endl;
```
**核心实现思想**：通过遍历字符串，使用变量记录当前连续相同符号的长度，当符号变化时更新最长连续相同符号的长度，最后输出最长连续相同符号长度加 1 的结果。

### 扩展思路
同类型题可能会改变比较符号的种类或增加其他条件，但核心思路可能还是通过寻找某种连续特征来确定最优解。类似算法套路可应用于其他需要寻找连续子结构的问题，如寻找最长连续递增子序列等。

### 推荐题目
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)

### 个人心得
本题解中未包含个人心得内容。 

---
处理用时：34.30秒