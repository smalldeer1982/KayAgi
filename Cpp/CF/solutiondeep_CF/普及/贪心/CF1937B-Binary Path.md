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
#### 二进制路径

**题目描述**

给定一个 $2 \times n$ 的网格，网格中填充了0和1。设第 $i$ 行第 $j$ 列的数为 $a_{ij}$。

有一只蚱蜢位于左上角单元格 $(1, 1)$，它只能向右或向下跳跃一个单元格。它想要到达右下角单元格 $(2, n)$。考虑由路径上的单元格中的数字按顺序组成的长度为 $n+1$ 的二进制字符串。

你的目标是：

1. 找到通过选择任何可用路径可以获得的字典序最小的字符串；
2. 找到生成这个字典序最小字符串的路径数量。

**说明/提示**

在第一个测试用例中，字典序最小的字符串是 $\mathtt{000}$。有两条路径可以生成这个字符串：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1937B/28bc26c21acb39dafc863512440b57a82f70d617.png)

在第二个测试用例中，字典序最小的字符串是 $\mathtt{11000}$。只有一条路径可以生成这个字符串：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1937B/f024d427300a33d2f71c9946e45249754a59348c.png)

**样例 #1**

**输入**

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

**输出**

```
000
2
11000
1
001001101
4
```

---

### 题解分析与结论

#### 综合分析
本题的核心在于如何在 $2 \times n$ 的网格中找到字典序最小的路径，并统计生成该路径的数量。由于蚱蜢只能向右或向下移动，因此路径的选择相对有限，但仍需考虑如何高效地找到最小字典序的路径。

#### 题解对比
1. **ZhongYuLin的题解**：使用了可持久化线段树维护哈希值，通过二分比较来找到最小字典序的路径。这种方法虽然高效，但实现复杂，且扩展性较高，适合更复杂的网格问题。
2. **AK_400的题解**：通过贪心策略，优先选择0，并在必要时向下移动。这种方法简洁高效，适合本题的规模。
3. **_299817_的题解**：同样采用贪心策略，通过模拟路径选择过程，找到最小字典序的路径，并统计路径数量。这种方法直观易懂，代码实现也较为简洁。

#### 最优关键思路
- **贪心策略**：优先选择0，并在必要时向下移动，以确保字典序最小。
- **路径统计**：通过模拟路径选择过程，统计生成最小字典序路径的数量。

#### 可拓展之处
- **更复杂的网格**：对于 $m \times n$ 的网格，可以使用类似的贪心策略，但需要考虑更多的路径选择。
- **动态规划**：对于更复杂的路径选择问题，可以使用动态规划来优化路径选择过程。

#### 推荐题目
1. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
2. [P8860 动态图连通性](https://www.luogu.com.cn/problem/P8860)
3. [CF464E The Classic Problem](https://www.luogu.com.cn/problem/CF464E)

---

### 所选高分题解

#### 1. AK_400的题解（4星）
**关键亮点**：
- 使用贪心策略，优先选择0，并在必要时向下移动。
- 通过模拟路径选择过程，找到最小字典序的路径，并统计路径数量。

**核心代码**：
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

#### 2. _299817_的题解（4星）
**关键亮点**：
- 通过模拟路径选择过程，找到最小字典序的路径。
- 统计生成最小字典序路径的数量。

**核心代码**：
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

#### 3. Wf_yjqd的题解（4星）
**关键亮点**：
- 通过贪心策略，优先选择0，并在必要时向下移动。
- 统计生成最小字典序路径的数量。

**核心代码**：
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

---

### 总结
本题的关键在于贪心策略的应用，通过优先选择0来确保字典序最小，并通过模拟路径选择过程来统计路径数量。对于更复杂的网格问题，可以考虑使用动态规划或更高级的数据结构来优化路径选择过程。

---
处理用时：43.86秒