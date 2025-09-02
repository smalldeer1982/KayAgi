# 题目信息

# Odd-Even Subsequence

## 题目描述

Ashish has an array $ a $ of size $ n $ .

A subsequence of $ a $ is defined as a sequence that can be obtained from $ a $ by deleting some elements (possibly none), without changing the order of the remaining elements.

Consider a subsequence $ s $ of $ a $ . He defines the cost of $ s $ as the minimum between:

- The maximum among all elements at odd indices of $ s $ .
- The maximum among all elements at even indices of $ s $ .

Note that the index of an element is its index in $ s $ , rather than its index in $ a $ . The positions are numbered from $ 1 $ . So, the cost of $ s $ is equal to $ min(max(s_1, s_3,       s_5, \ldots), max(s_2, s_4, s_6, \ldots)) $ .

For example, the cost of $ \{7, 5, 6\} $ is $ min( max(7, 6),       max(5) ) = min(7, 5) = 5 $ .

Help him find the minimum cost of a subsequence of size $ k $ .

## 说明/提示

In the first test, consider the subsequence $ s $ = $ \{1,       3\} $ . Here the cost is equal to $ min(max(1), max(3)) = 1 $ .

In the second test, consider the subsequence $ s $ = $ \{1, 2,       4\} $ . Here the cost is equal to $ min(max(1, 4), max(2)) = 2 $ .

In the fourth test, consider the subsequence $ s $ = $ \{3,       50, 2, 4\} $ . Here the cost is equal to $ min(max(3, 2), max(50,       4)) = 3 $ .

## 样例 #1

### 输入

```
4 2
1 2 3 4```

### 输出

```
1```

## 样例 #2

### 输入

```
4 3
1 2 3 4```

### 输出

```
2```

## 样例 #3

### 输入

```
5 3
5 3 4 2 6```

### 输出

```
2```

## 样例 #4

### 输入

```
6 4
5 3 50 2 4 5```

### 输出

```
3```

# AI分析结果

### 题目翻译
#### 奇偶子序列

#### 题目描述
Ashish 有一个长度为 $n$ 的数组 $a$。

数组 $a$ 的一个子序列被定义为一个可以通过删除 $a$ 中的一些元素（可能不删除），且不改变剩余元素顺序而得到的序列。

考虑数组 $a$ 的一个子序列 $s$。他将 $s$ 的代价定义为以下两者中的最小值：
- 子序列 $s$ 中所有奇数位置元素的最大值。
- 子序列 $s$ 中所有偶数位置元素的最大值。

请注意，元素的位置是指其在子序列 $s$ 中的位置，而不是在数组 $a$ 中的位置。位置编号从 $1$ 开始。因此，子序列 $s$ 的代价等于 $min(max(s_1, s_3, s_5, \ldots), max(s_2, s_4, s_6, \ldots))$。

例如，子序列 $\{7, 5, 6\}$ 的代价为 $min( max(7, 6), max(5) ) = min(7, 5) = 5$。

请帮助他找到长度为 $k$ 的子序列的最小代价。

#### 说明/提示
在第一个测试用例中，考虑子序列 $s$ = $\{1, 3\}$。这里的代价等于 $min(max(1), max(3)) = 1$。

在第二个测试用例中，考虑子序列 $s$ = $\{1, 2, 4\}$。这里的代价等于 $min(max(1, 4), max(2)) = 2$。

在第四个测试用例中，考虑子序列 $s$ = $\{3, 50, 2, 4\}$。这里的代价等于 $min(max(3, 2), max(50, 4)) = 3$。

#### 样例 #1
##### 输入
```
4 2
1 2 3 4
```
##### 输出
```
1
```

#### 样例 #2
##### 输入
```
4 3
1 2 3 4
```
##### 输出
```
2
```

#### 样例 #3
##### 输入
```
5 3
5 3 4 2 6
```
##### 输出
```
2
```

#### 样例 #4
##### 输入
```
6 4
5 3 50 2 4 5
```
##### 输出
```
3
```

### 算法分类
二分

### 综合分析与结论
这些题解的核心思路都是利用二分答案来解决问题。由于题目要求的是子序列奇数位和偶数位最大值中的最小值最小，符合二分答案的特征。通过二分一个可能的最大值，然后使用贪心策略来检查是否能构造出长度为 $k$ 的子序列满足条件。
- **思路**：二分答案，每次二分出一个可能的最大值 $p$，然后分别检查奇数位置和偶数位置能否选取到满足条件（元素值小于等于 $p$）的长度为 $k$ 的子序列。
- **算法要点**：二分查找的实现，以及检查函数的编写，检查时需要遍历原数组，根据奇偶位置的不同和元素值与 $p$ 的大小关系来决定是否选取该元素。
- **解决难点**：理解子序列的定义，以及如何通过贪心策略在给定最大值的情况下构造出满足条件的子序列。

### 所选题解
- **作者：LeavingZzz (赞：11)，4星**
  - **关键亮点**：思路清晰，步骤梳理明确，代码注释详细，易于理解。
  - **个人心得**：作者提到赛时就差一点做出来，提醒大家比赛时不要慌张。
- **作者：promise_ (赞：4)，4星**
  - **关键亮点**：代码简洁，对二分答案和贪心策略的解释清晰。
- **作者：IceKylin (赞：2)，4星**
  - **关键亮点**：对二分答案的思路和单调性分析详细，还提到了理论上的优化方法。

### 重点代码
#### LeavingZzz 的代码
```cpp
bool check(int p)
{
    int cnt=0;
    for(int i=1;i<=N;i++)//检查奇数位置 
    {
        if((cnt&1))
        {
            if(A[i]<=p)
                cnt++;//奇数位置要满足不能超出限制 
        }
        else cnt++;//偶数位置无所谓qwq 
    }
    if(cnt>=K) return true;//奇数位置满足条件直接返回
    //不满足条件我们还有一次机会
    cnt=0;
    for(int i=1;i<=N;i++)//检查偶数位置 
    {
        if(!(cnt&1))
        {
            if(A[i]<=p)
                cnt++;
        }
        else cnt++;
    }
    if(cnt>=K) return true;//偶数位置满足条件 
    return false;//都不行 
}
```
**核心实现思想**：通过两次遍历原数组，分别检查奇数位置和偶数位置能否选取到满足元素值小于等于 $p$ 的长度为 $K$ 的子序列。

#### promise_ 的代码
```cpp
bool chk1(int x,int y){
    int now=1,len=n;//now表示当前是奇数位置还是偶数位置，len表示剩余的元素个数。
    for(int i=1;i<=n;i++){
        if(now==y&&a[i]>x)//当当前位置i的元素大于x且需要选择的位置与当前位置的奇偶性相同
        now=!now,len--;
        now=!now;
    }
    return len>=k;
}
bool chk2(int x){
    return chk1(x,1)|chk1(x,0);//判断给定的now的情况下，是否存在一个长度至少为k的子序列
}
```
**核心实现思想**：`chk1` 函数用于检查在给定奇偶位置和最大值 $x$ 的情况下，能否构造出长度至少为 $k$ 的子序列。`chk2` 函数则通过调用 `chk1` 函数分别检查奇数和偶数位置。

#### IceKylin 的代码
```cpp
il bool check(int x){
    int odd=0,even=0; 
    for(int i=1;i<=n;++i){
        odd+=!(odd&1)||a[i]<=x;
        even+=(even&1)||a[i]<=x;
    }
    return max(odd,even)>=k;
}
```
**核心实现思想**：在一次遍历中同时统计奇数位置和偶数位置满足条件的元素个数，最后取两者的最大值与 $k$ 比较。

### 关键思路或技巧
- **二分答案**：当题目出现“最大值最小”或“最小值最大”的特征时，可以考虑使用二分答案将问题转化为判定性问题。
- **贪心策略**：在检查函数中，根据奇偶位置和元素值的大小关系来决定是否选取该元素，从而构造出满足条件的子序列。

### 拓展思路
同类型题或类似算法套路：当遇到求某个最值且该最值具有单调性时，可以尝试使用二分答案，再结合贪心、动态规划等算法来解决判定问题。

### 推荐题目
- [P1873 砍树](https://www.luogu.com.cn/problem/P1873)
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)
- [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)

### 个人心得总结
LeavingZzz 提醒大家比赛时不要慌张，避免像他一样因为慌张而与做出题目失之交臂。45dinо 分享了自己一开始没理解“子序列”的意义，误把它当成“子段”，调了 40 分钟单调队列的经历，强调了理解题目概念的重要性。 

---
处理用时：53.11秒