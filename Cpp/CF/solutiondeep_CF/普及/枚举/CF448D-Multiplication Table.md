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
冠军比宗（Bizon）不仅迷人，而且非常聪明。

当我们中的一些人在学习乘法表时，冠军比宗却以自己的方式享受着乐趣。冠军比宗绘制了一个 $n×m$ 的乘法表，其中第 $i$ 行和第 $j$ 列交叉处的元素等于 $i·j$（表的行和列从 1 开始编号）。然后有人问他：表中第 $k$ 大的数字是多少？冠军比宗总是能正确且立即给出答案。你能重复他的成功吗？

考虑给定的乘法表。如果你将表中的所有 $n·m$ 个数字按非递减顺序写出，那么你写出的第 $k$ 个数字就称为第 $k$ 大的数字。

## 说明/提示
一个 $2×3$ 的乘法表如下所示：

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
这些题解的核心思路都是使用二分查找来找到乘法表中第 $k$ 大的数。不同题解在具体实现细节上有所差异：
- **Mxfg**：通过二分答案，在 `check` 函数中计算每行小于等于当前二分中间值的元素个数总和，判断是否大于等于 $k$ 来缩小二分区间。
- **yu__xuan**：同样二分答案，在 `check` 函数中分别计算小于当前二分中间值的元素个数和等于该值的元素个数，根据这两个数量与 $k$ 的关系判断是否为答案。
- **iiawaKL**：二分答案，`check` 函数计算每行小于等于当前二分中间值的元素个数总和，判断是否小于 $k$ 来缩小二分区间。
- **pengrui**：使用二分答案和双指针算法，通过双指针遍历乘法表，计算小于当前二分中间值的元素个数，判断是否大于等于 $k$ 来缩小二分区间。

### 题解选择
- **Mxfg（5星）**：
    - **关键亮点**：思路清晰，代码简洁，直接计算小于等于中间值的元素个数，避免了复杂的判断，易于理解和实现。
    - **个人心得**：无
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
核心实现思想：遍历乘法表的每一行，对于每一行 $i$，计算 $\min(m, x/i)$ 表示该行中小于等于 $x$ 的元素个数，将所有行的个数相加，若总和大于等于 $k$，则说明 $x$ 可能是第 $k$ 大的数。

- **yu__xuan（4星）**：
    - **关键亮点**：详细说明了如何计算小于和等于中间值的元素个数，逻辑严谨。
    - **个人心得**：无
```cpp
for(int i=1;i<=n;++i){
    sum+=min((mid-1)/i,m);
    if(mid%i==0&&mid/i<=m) tmp++;
}
if(sum<=k-1&&sum+tmp>=k){
    write(mid);
    return 0;
}
```
核心实现思想：遍历乘法表的每一行，计算小于中间值的元素个数总和 `sum` 以及等于中间值的元素个数 `tmp`，若 `sum` 小于等于 $k - 1$ 且 `sum + tmp` 大于等于 $k$，则中间值即为第 $k$ 大的数。

- **iiawaKL（4星）**：
    - **关键亮点**：代码简洁，思路直接，通过判断小于中间值的元素个数是否小于 $k$ 来缩小二分区间。
    - **个人心得**：无
```cpp
bool check(long long x){
    ll sum=0;
    for(int i=1;i<=n;i++)sum+=min(m,x/i);
    return sum<k;
}
```
核心实现思想：遍历乘法表的每一行，计算小于等于中间值的元素个数总和，若总和小于 $k$，则说明中间值太小，需要增大二分区间的左边界。

### 最优关键思路或技巧
- **二分查找**：利用乘法表元素的单调性，通过二分查找在 $[1, n*m]$ 区间内快速定位第 $k$ 大的数。
- **计算小于等于某值的元素个数**：对于乘法表的每一行 $i$，小于等于 $x$ 的元素个数为 $\min(m, x/i)$，通过累加每行的个数可以快速得到整个乘法表中小于等于 $x$ 的元素总数。

### 拓展思路
同类型题目通常涉及在有序数据集合中查找满足特定条件的元素，可使用二分查找来优化时间复杂度。类似算法套路还有二分查找结合其他算法（如双指针）来解决复杂问题。

### 推荐题目
- [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)
- [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)

### 个人心得摘录与总结
- **iiawaKL**：提到根据数据很大想到用二分思路，体现了根据数据规模选择合适算法的重要性。
- **pengrui**：无明显个人心得。 

---
处理用时：28.38秒