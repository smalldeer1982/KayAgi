# 题目信息

# Binary Path

## 题目描述

You are given a $ 2 \times n $ grid filled with zeros and ones. Let the number at the intersection of the $ i $ -th row and the $ j $ -th column be $ a_{ij} $ .

There is a grasshopper at the top-left cell $ (1, 1) $ that can only jump one cell right or downwards. It wants to reach the bottom-right cell $ (2, n) $ . Consider the binary string of length $ n+1 $ consisting of numbers written in cells of the path without changing their order.

Your goal is to:

1. Find the lexicographically smallest $ ^\dagger $ string you can attain by choosing any available path;
2. Find the number of paths that yield this lexicographically smallest string.

 $ ^\dagger $ If two strings $ s $ and $ t $ have the same length, then $ s $ is lexicographically smaller than $ t $ if and only if in the first position where $ s $ and $ t $ differ, the string $ s $ has a smaller element than the corresponding element in $ t $ .

## 说明/提示

In the first test case, the lexicographically smallest string is $ \mathtt{000} $ . There are two paths that yield this string:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1937B/28bc26c21acb39dafc863512440b57a82f70d617.png)In the second test case, the lexicographically smallest string is $ \mathtt{11000} $ . There is only one path that yields this string:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1937B/f024d427300a33d2f71c9946e45249754a59348c.png)

## 样例 #1

### 输入

```
3
2
00
00
4
1101
1100
8
00100111
11101101```

### 输出

```
000
2
11000
1
001001101
4```

# AI分析结果

### 题目内容重写

#### 题目描述

给定一个 $2 \times n$ 的网格，网格中每个格子填有 `0` 或 `1`。设第 $i$ 行第 $j$ 列的数为 $a_{ij}$。

有一只蚱蜢位于左上角格子 $(1, 1)$，它只能向右或向下移动一格。蚱蜢想要到达右下角格子 $(2, n)$。考虑路径上经过的格子中的数字按顺序组成的长度为 $n+1$ 的二进制字符串。

你的目标是：

1. 找到通过选择任意可用路径可以得到的最小字典序字符串；
2. 找到产生这个最小字典序字符串的路径数量。

#### 说明/提示

在第一个测试用例中，最小字典序字符串是 `000`，有两条路径可以产生这个字符串。

在第二个测试用例中，最小字典序字符串是 `11000`，只有一条路径可以产生这个字符串。

#### 样例 #1

##### 输入

```
3
2
00
00
4
1101
1100
8
00100111
11101101
```

##### 输出

```
000
2
11000
1
001001101
4
```

### 题解综合分析与结论

本题的核心问题是在一个 $2 \times n$ 的网格中，找到从左上角到右下角的最小字典序路径，并统计产生该路径的数量。由于网格只有两行，蚱蜢只能向右或向下移动，因此路径的选择空间相对有限，可以通过贪心策略或动态规划来解决。

### 评分较高的题解

#### 题解1：作者：AK_400 (赞：10)

**星级：5星**

**关键亮点：**
- 通过贪心策略，优先选择 `0`，并且在相等时优先向右走。
- 使用 `l` 和 `r` 来记录向下走的最早和最晚位置，简化了路径的选择和统计。
- 代码简洁高效，时间复杂度为 $O(n)$。

**核心代码：**
```cpp
int l=0,r=n-1;
for(int i=n-1;i>0;i--){
    if(a[0][i]=='1'&&a[1][i-1]=='0')r=i-1;
}
for(int i=0;i<=r;i++){
    if(a[0][i+1]=='0'&&a[1][i]=='1')l=i+1;
}
for(int i=0;i<=r;i++){
    cout<<a[0][i];
}
for(int i=r;i<n;i++){
    cout<<a[1][i];
}
cout<<endl<<r-l+1<<endl;
```

**实现思想：**
- 通过遍历网格，确定向下走的最早和最晚位置，从而得到最小字典序路径。
- 统计路径数量时，利用 `r-l+1` 计算符合条件的路径数。

#### 题解2：作者：_299817_ (赞：2)

**星级：4星**

**关键亮点：**
- 通过贪心策略，优先选择 `0`，并且在相等时优先向右走。
- 使用 `flag` 来标记是否已经向下走，简化了路径的选择和统计。
- 代码清晰，易于理解。

**核心代码：**
```cpp
int flag = 1;
int cnt = 0;
int num;
rep(i, 1, n){
    if(a[1][i + 1] > a[2][i] && flag == 1){
        flag++;
        num = i;
        ans[++cnt] = a[1][i], ans[++cnt] = a[2][i];
    }else{
        ans[++cnt] = a[flag][i];
    }
}
if(flag == 1){
    ans[++cnt] = a[2][n];
    num = n;
}
rep(i, 1, cnt) cout << ans[i];
cout << endl;
int aans = 1;
per(i, num, 2){
    if(a[1][i] == a[2][i - 1]) aans++;
    else break;
}
cout << aans << endl;
```

**实现思想：**
- 通过遍历网格，优先选择 `0`，并且在相等时优先向右走。
- 统计路径数量时，从向下走的位置向左搜索，统计符合条件的路径数。

#### 题解3：作者：Wf_yjqd (赞：1)

**星级：4星**

**关键亮点：**
- 通过贪心策略，优先选择 `0`，并且在相等时优先向右走。
- 使用 `i` 和 `j` 来记录路径的选择，简化了路径的生成和统计。
- 代码简洁高效，时间复杂度为 $O(n)$。

**核心代码：**
```cpp
for(int i=1,j;i<=n;i++){
    printf("%d",a[0][i]);
    if(a[1][i]<a[0][i+1]||i==n){
        for(j=i;j<=n;j++)
            printf("%d",a[1][j]);
        puts("");
        for(j=i-1;j>=1;j--)
            if(a[1][j]!=a[0][j+1])
                break;
        printf("%d\n",i-j);
        break;
    }
}
```

**实现思想：**
- 通过遍历网格，优先选择 `0`，并且在相等时优先向右走。
- 统计路径数量时，从向下走的位置向左搜索，统计符合条件的路径数。

### 最优关键思路或技巧

1. **贪心策略**：优先选择 `0`，并且在相等时优先向右走，确保路径的字典序最小。
2. **路径统计**：通过记录向下走的最早和最晚位置，利用 `r-l+1` 计算符合条件的路径数。
3. **简化路径选择**：利用 `flag` 或 `i` 和 `j` 来标记路径的选择，简化代码实现。

### 可拓展之处

- **网格扩展**：如果网格扩展到 $m \times n$，可以使用动态规划或广度优先搜索（BFS）来解决问题。
- **多路径统计**：如果需要统计所有最小字典序路径的数量，可以使用动态规划结合哈希表来记录路径。

### 推荐题目

1. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
2. [P8860 动态图连通性](https://www.luogu.com.cn/problem/P8860)
3. [CF464E The Classic Problem](https://www.luogu.com.cn/problem/CF464E)

---
处理用时：45.36秒