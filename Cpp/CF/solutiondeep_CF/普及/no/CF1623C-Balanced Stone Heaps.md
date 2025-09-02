# 题目信息

# Balanced Stone Heaps

## 题目描述

There are $ n $ heaps of stone. The $ i $ -th heap has $ h_i $ stones. You want to change the number of stones in the heap by performing the following process once:

- You go through the heaps from the $ 3 $ -rd heap to the $ n $ -th heap, in this order.
- Let $ i $ be the number of the current heap.
- You can choose a number $ d $ ( $ 0 \le 3 \cdot d \le h_i $ ), move $ d $ stones from the $ i $ -th heap to the $ (i - 1) $ -th heap, and $ 2 \cdot d $ stones from the $ i $ -th heap to the $ (i - 2) $ -th heap.
- So after that $ h_i $ is decreased by $ 3 \cdot d $ , $ h_{i - 1} $ is increased by $ d $ , and $ h_{i - 2} $ is increased by $ 2 \cdot d $ .
- You can choose different or same $ d $ for different operations. Some heaps may become empty, but they still count as heaps.

What is the maximum number of stones in the smallest heap after the process?

## 说明/提示

In the first test case, the initial heap sizes are $ [1, 2, 10, 100] $ . We can move the stones as follows.

- move $ 3 $ stones and $ 6 $ from the $ 3 $ -rd heap to the $ 2 $ -nd and $ 1 $ heap respectively. The heap sizes will be $ [7, 5, 1, 100] $ ;
- move $ 6 $ stones and $ 12 $ stones from the last heap to the $ 3 $ -rd and $ 2 $ -nd heap respectively. The heap sizes will be $ [7, 17, 7, 82] $ .

In the second test case, the last heap is $ 1 $ , and we can not increase its size.

In the third test case, it is better not to move any stones.

In the last test case, the final achievable configuration of the heaps can be $ [3, 5, 3, 4, 3, 3] $ .

## 样例 #1

### 输入

```
4
4
1 2 10 100
4
100 100 100 1
5
5 1 1 1 8
6
1 2 3 4 5 6```

### 输出

```
7
1
1
3```

# AI分析结果

### 题目内容重写
#### 平衡石子堆

**题目描述**

有 $n$ 堆石子，第 $i$ 堆有 $h_i$ 个石子。你可以通过以下操作改变每堆石子的数量：

- 从第 $3$ 堆开始，依次处理到第 $n$ 堆。
- 对于当前处理的第 $i$ 堆，选择一个数 $d$（$0 \le 3 \cdot d \le h_i$），将 $d$ 个石子从第 $i$ 堆移动到第 $(i - 1)$ 堆，并将 $2 \cdot d$ 个石子从第 $i$ 堆移动到第 $(i - 2)$ 堆。
- 操作后，第 $i$ 堆的石子数减少 $3 \cdot d$，第 $(i - 1)$ 堆的石子数增加 $d$，第 $(i - 2)$ 堆的石子数增加 $2 \cdot d$。
- 你可以为不同的操作选择不同的 $d$。某些堆可能会变为空，但它们仍然被视为堆。

问：经过操作后，最小的堆中最多可以有多少个石子？

**说明/提示**

在第一个测试用例中，初始堆的大小为 $[1, 2, 10, 100]$。我们可以进行如下操作：

- 从第 $3$ 堆移动 $3$ 个石子和 $6$ 个石子到第 $2$ 堆和第 $1$ 堆。堆的大小变为 $[7, 5, 1, 100]$；
- 从最后一堆移动 $6$ 个石子和 $12$ 个石子到第 $3$ 堆和第 $2$ 堆。堆的大小变为 $[7, 17, 7, 82]$。

在第二个测试用例中，最后一堆只有 $1$ 个石子，无法增加其大小。

在第三个测试用例中，最好不要移动任何石子。

在最后一个测试用例中，最终可以达到的堆大小为 $[3, 5, 3, 4, 3, 3]$。

**样例 #1**

**输入**

```
4
4
1 2 10 100
4
100 100 100 1
5
5 1 1 1 8
6
1 2 3 4 5 6
```

**输出**

```
7
1
1
3
```

### 算法分类
二分

### 题解综合分析
本题的核心思路是通过二分答案来确定最小的堆中最多可以有多少个石子。大多数题解都采用了二分法，并通过从后向前遍历堆来验证当前二分答案是否可行。难点在于如何正确计算每个堆可以移动的石子数，并确保移动后所有堆的石子数都满足条件。

### 精选题解
#### 题解1：作者：ycy1124 (赞：19)
**星级：5星**
**关键亮点：**
- 使用二分答案法，思路清晰。
- 通过从后向前遍历堆，确保每个堆在移动石子后仍然满足条件。
- 代码实现简洁，逻辑严密。

**代码核心实现：**
```cpp
bool bj=0;
for(int i=1;i<=n-2;i++){
    if(a[i]+tmp1[max(0,i-1)]+tmp2[max(0,i-2)]<mid){
        bj=1;
    }
    tmp1[i]=min(int(floor(1.00*max(a[i]+tmp1[max(0,i-1)]+tmp2[max(0,i-2)]-mid,0)/3)),a[i]/3);
    tmp2[i]=min(int(floor(1.00*max(a[i]+tmp1[max(0,i-1)]+tmp2[max(0,i-2)]-mid,0)/3)),a[i]/3)*2;
}
```
**核心思想：** 通过从后向前遍历堆，计算每个堆可以移动的石子数，并确保移动后所有堆的石子数都满足条件。

#### 题解2：作者：yeshubo_qwq (赞：8)
**星级：4星**
**关键亮点：**
- 使用二分答案法，思路清晰。
- 通过从后向前遍历堆，确保每个堆在移动石子后仍然满足条件。
- 代码实现简洁，逻辑严密。

**代码核心实现：**
```cpp
bool check(int x){
    int d;
    for(int i=n;i>=3;i--){
        if(a[i]<x)return 0;
        d=min(a[i]-x,b[i])/3;
        a[i-2]+=2*d;a[i-1]+=d;a[i]-=d*3;
    }
    return a[1]>=x&&a[2]>=x;
}
```
**核心思想：** 通过从后向前遍历堆，计算每个堆可以移动的石子数，并确保移动后所有堆的石子数都满足条件。

#### 题解3：作者：vvauted (赞：2)
**星级：4星**
**关键亮点：**
- 使用二分答案法，思路清晰。
- 通过从后向前遍历堆，确保每个堆在移动石子后仍然满足条件。
- 代码实现简洁，逻辑严密。

**代码核心实现：**
```cpp
bool check(int x) {
    for(int i = 1; i <= n; ++ i) b[i] = a[i], c[i] = 0;
    for(int i = n, p; i > 2; -- i) {
        p = max(min(b[i], c[i] + b[i] - x), 0) / 3;
        b[i] -= p * 3;
        c[i - 1] += p;
        c[i - 2] += p * 2;
    }
    for(int i = 1; i <= n; ++ i) if(b[i] + c[i] < x) return 0;
    return 1;
}
```
**核心思想：** 通过从后向前遍历堆，计算每个堆可以移动的石子数，并确保移动后所有堆的石子数都满足条件。

### 最优关键思路
- **二分答案**：通过二分法确定最小的堆中最多可以有多少个石子。
- **从后向前遍历**：从后向前遍历堆，确保每个堆在移动石子后仍然满足条件。
- **计算移动石子数**：计算每个堆可以移动的石子数，并确保移动后所有堆的石子数都满足条件。

### 可拓展之处
- **类似题目**：可以通过二分答案法解决其他类似的最小值最大化问题。
- **优化思路**：可以考虑优化计算移动石子数的过程，减少时间复杂度。

### 推荐题目
1. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)
2. [P1281 书的复制](https://www.luogu.com.cn/problem/P1281)
3. [P1316 丢瓶盖](https://www.luogu.com.cn/problem/P1316)

---
处理用时：43.65秒