# 题目信息

# Multiplication Table

## 题目描述

Bizon the Champion isn't just charming, he also is very smart.

While some of us were learning the multiplication table, Bizon the Champion had fun in his own manner. Bizon the Champion painted an $ n×m $ multiplication table, where the element on the intersection of the $ i $ -th row and $ j $ -th column equals $ i·j $ (the rows and columns of the table are numbered starting from 1). Then he was asked: what number in the table is the $ k $ -th largest number? Bizon the Champion always answered correctly and immediately. Can you repeat his success?

Consider the given multiplication table. If you write out all $ n·m $ numbers from the table in the non-decreasing order, then the $ k $ -th number you write out is called the $ k $ -th largest number.

## 说明/提示

A $ 2×3 $ multiplication table looks like this:

`<br></br>1 2 3<br></br>2 4 6<br></br><br></br>`

## 样例 #1

### 输入

```
2 2 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 3 4
```

### 输出

```
3
```

## 样例 #3

### 输入

```
1 10 5
```

### 输出

```
5
```

# AI分析结果

### 题目翻译
# 乘法表

## 题目描述
冠军比松不仅迷人，而且非常聪明。

当我们中的一些人在学习乘法表时，冠军比松却以自己的方式享受乐趣。冠军比松绘制了一个 $ n×m $ 的乘法表，其中第 $ i $ 行和第 $ j $ 列交叉处的元素等于 $ i·j $（表的行和列从 1 开始编号）。然后有人问他：表中第 $ k $ 大的数字是多少？冠军比松总是能正确并立即给出答案。你能复制他的成功吗？

考虑给定的乘法表。如果你将表中的所有 $ n·m $ 个数字按非递减顺序写出，那么你写出的第 $ k $ 个数字就称为第 $ k $ 大的数字。

## 说明/提示
一个 $ 2×3 $ 的乘法表如下所示：

`<br></br>1 2 3<br></br>2 4 6<br></br><br></br>`

## 样例 #1
### 输入
```
2 2 2
```
### 输出
```
2
```

## 样例 #2
### 输入
```
2 3 4
```
### 输出
```
3
```

## 样例 #3
### 输入
```
1 10 5
```
### 输出
```
5
```

### 综合分析与结论
这些题解都采用了二分答案的思路来解决问题，核心在于通过二分查找合适的数，并利用检查函数判断该数是否满足第 $ k $ 大的条件。不同题解的主要差异在于检查函数的实现方式。
- **Mxfg题解**：通过遍历每一行，计算每行中小于等于当前二分答案的元素个数，将其累加后与 $ k $ 比较。
- **yu__xuan题解**：分别计算小于当前二分答案的元素个数和等于该答案的元素个数，根据这两个数量与 $ k $ 的关系判断是否为答案。
- **iiawaKL题解**：思路与Mxfg题解类似，检查函数判断累加的小于等于当前二分答案的元素个数是否小于 $ k $。
- **pengrui题解**：使用双指针算法辅助检查，通过移动指针计算小于当前二分答案的元素个数。

### 题解选择
- **Mxfg题解（5星）**
    - **关键亮点**：思路清晰，代码简洁易懂，直接通过二分答案和简单的检查函数解决问题。
    - **核心代码**：
```cpp
bool check(long long x)
{
    long long sum=0;
    for(int i=1;i<=n;i++){
        sum+=min(m,x/i);
    }
    return sum>=k;
}
```
核心思想是遍历乘法表的每一行，对于每行 $ i $，计算 $ x/i $ 并取其与 $ m $ 的最小值，累加得到小于等于 $ x $ 的元素个数，最后判断该个数是否大于等于 $ k $。

- **yu__xuan题解（4星）**
    - **关键亮点**：详细说明了计算小于和等于二分答案的元素个数的方法，逻辑严谨。
    - **核心代码**：
```cpp
while(l<=r){
    ll mid=(l+r)>>1,sum=0,tmp=0;
    for(int i=1;i<=n;++i){
        sum+=min((mid-1)/i,m);
        if(mid%i==0&&mid/i<=m) tmp++;
    }
    if(sum<=k-1&&sum+tmp>=k){
        write(mid);
        return 0;
    }
    if(sum+tmp<=k-1) l=mid+1;
    else r=mid-1;
}
```
核心思想是二分查找答案，在每次二分过程中，计算小于 $ mid $ 的元素个数 $ sum $ 和等于 $ mid $ 的元素个数 $ tmp $，根据这两个数量与 $ k $ 的关系调整二分区间。

- **iiawaKL题解（4星）**
    - **关键亮点**：代码简洁，思路直接，通过二分和检查函数快速求解。
    - **核心代码**：
```cpp
bool check(long long x){
    ll sum=0;
    for(int i=1;i<=n;i++)sum+=min(m,x/i);
    return sum<k;
}
```
核心思想与Mxfg题解类似，检查小于等于 $ x $ 的元素个数是否小于 $ k $，以此来调整二分区间。

### 最优关键思路或技巧
- **二分答案**：利用乘法表元素的单调性，通过二分查找缩小答案范围，将时间复杂度从暴力枚举的 $ O(nm) $ 降低到 $ O(log(nm)) $。
- **检查函数优化**：通过遍历行并利用 $ x/i $ 计算每行中小于等于 $ x $ 的元素个数，避免了对整个乘法表的遍历。

### 拓展思路
同类型题或类似算法套路：
- 对于具有单调性的二维矩阵中查找第 $ k $ 大/小元素的问题，都可以考虑使用二分答案的方法。
- 二分答案结合检查函数的思路可以应用于许多需要在一个有序区间内查找满足特定条件的元素的问题。

### 推荐题目
1. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)
2. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)
3. [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)

### 个人心得摘录与总结
- **Mxfg**：提到第一次发题解，指出可以用暴力但拿不到全分，考虑到乘法表的性质，发现满足单调性，从而使用二分答案求解。总结为初次解题时要思考更优算法，利用题目特性简化问题。
- **iiawaKL**：表示第一次写题解，因数据大想到二分思路，还请大佬指教。总结为遇到大数据问题可优先考虑二分等高效算法，同时保持谦虚学习的态度。 

---
处理用时：33.88秒