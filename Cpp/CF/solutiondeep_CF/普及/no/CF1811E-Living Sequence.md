# 题目信息

# Living Sequence

## 题目描述

In Japan, the number $ 4 $ reads like death, so Bob decided to build a live sequence. Living sequence $ a $ contains all natural numbers that do not contain the digit $ 4 $ . $ a = [1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 16, \ldots] $ .

For example, the number $ 1235 $ is part of the sequence $ a $ , but the numbers $ 4321 $ , $ 443 $ are not part of the sequence $ a $ .

Bob realized that he does not know how to quickly search for a particular number by the position $ k $ in the sequence, so he asks for your help.

For example, if Bob wants to find the number at position $ k = 4 $ (indexing from $ 1 $ ), you need to answer $ a_k = 5 $ .

## 样例 #1

### 输入

```
7
3
5
22
10
100
12345
827264634912```

### 输出

```
3
6
25
11
121
18937
2932285320890```

# AI分析结果

### 题目内容重写
在日本，数字 $4$ 的发音类似于“死”，因此 Bob 决定构建一个“活着的序列”。活着的序列 $a$ 包含所有不包含数字 $4$ 的自然数。$a = [1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 16, \ldots]$。

例如，数字 $1235$ 是序列 $a$ 的一部分，但数字 $4321$ 和 $443$ 不是序列 $a$ 的一部分。

Bob 意识到他不知道如何快速查找序列中第 $k$ 个位置的数字，因此他请求你的帮助。

例如，如果 Bob 想要查找位置 $k = 4$（从 $1$ 开始索引）的数字，你需要回答 $a_k = 5$。

### 样例 #1
#### 输入
```
7
3
5
22
10
100
12345
827264634912
```
#### 输出
```
3
6
25
11
121
18937
2932285320890
```

### 算法分类
进制

### 题解分析与结论
本题的核心思路是将问题转化为九进制转换，并通过映射处理来避免数字 $4$。大多数题解都采用了这一思路，即将输入的数字 $k$ 转换为九进制，然后将每一位大于等于 $4$ 的数字加 $1$，从而得到不含 $4$ 的结果。

### 高星题解推荐
#### 1. 作者：SunLegend (赞：29)
- **星级**：5星
- **关键亮点**：思路清晰，代码简洁，直接通过九进制转换和映射数组实现，避免了复杂的数位 DP 或二分查找。
- **核心代码**：
```cpp
int m[12]={0,1,2,3,5,6,7,8,9}; // 映射数组
while(n) {
    a[++x]=m[n%9]; 
    n/=9;
}
for(int i=x;i>=1;i--) cout<<a[i];
```
- **个人心得**：作者提到初次读题时可能会想到数位 DP 或二分查找，但通过九进制转换可以大大简化代码实现。

#### 2. 作者：IceKylin (赞：3)
- **星级**：4星
- **关键亮点**：通过双射函数将九进制映射到不含 $4$ 的数字，代码简洁且易于理解。
- **核心代码**：
```cpp
ll phi[10]={0,1,2,3,5,6,7,8,9};
while(n) a[++cnt]=phi[n%9],n/=9;
for(int i=cnt;i;--i) cout<<a[i];
```
- **个人心得**：作者提到本题可以通过简单的进制转换解决，避免了复杂的数位 DP。

#### 3. 作者：Drystynt (赞：3)
- **星级**：4星
- **关键亮点**：通过将九进制中的 $4$ 到 $8$ 映射为 $5$ 到 $9$，实现了不含 $4$ 的序列生成，代码简洁且逻辑清晰。
- **核心代码**：
```cpp
while(n) {
    a[j]=n%9;
    if(a[j]>=4) a[j]++;
    n/=9;
}
for(;j>=0;j--) printf("%d",a[j]);
```
- **个人心得**：作者通过观察样例数据，发现可以通过简单的进制转换和映射解决本题。

### 最优关键思路
将输入的数字 $k$ 转换为九进制，然后将每一位大于等于 $4$ 的数字加 $1$，从而得到不含 $4$ 的结果。这种方法避免了复杂的数位 DP 或二分查找，代码简洁且高效。

### 可拓展之处
类似的问题可以通过进制转换和映射来解决，例如处理不含某些特定数字的序列生成问题。此外，进制转换的思想可以应用于其他需要处理数字位的问题。

### 推荐题目
1. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
2. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)
3. [P1036 选数](https://www.luogu.com.cn/problem/P1036)

这些题目都涉及到数字处理和进制转换的思想，可以帮助进一步巩固相关知识。

---
处理用时：29.27秒