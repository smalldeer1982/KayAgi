# 题目信息

# Absolute Beauty

## 题目描述

Kirill has two integer arrays $a_1,a_2,…,a_n$ and $b_1,b_2,…,b_n$ of length $n$. He defines the _absolute beauty_ of the array $b$ as
$$
\sum_{i=1}^n|a_i-b_i|
$$
Here, $|x|$ denotes the absolute value of $x$.

Kirill can perform the following operation **at most once**:

- select two indices $i$ and $j$ ($1≤i<j≤n$) and swap the values of $b_i$ and $b_j$.

Help him find the maximum possible absolute beauty of the array $b$ after performing **at most one** swap.

## 说明/提示

In the first test case, each of the possible swaps does not change the array $ b $ .

In the second test case, the absolute beauty of the array $ b $ without performing the swap is $ |1-1| + |2-2| = 0 $ . After swapping the first and the second element in the array $ b $ , the absolute beauty becomes $ |1-2| + |2-1| = 2 $ . These are all the possible outcomes, hence the answer is $ 2 $ .

In the third test case, it is optimal for Kirill to not perform the swap. Similarly to the previous test case, the answer is $ 2 $ .

In the fourth test case, no matter what Kirill does, the absolute beauty of $ b $ remains equal to $ 16 $ .

## 样例 #1

### 输入

```
6
3
1 3 5
3 3 3
2
1 2
1 2
2
1 2
2 1
4
1 2 3 4
5 6 7 8
10
1 8 2 5 3 5 3 1 1 3
2 9 2 4 8 2 3 5 3 1
3
47326 6958 358653
3587 35863 59474```

### 输出

```
4
2
2
16
31
419045```

# AI分析结果

### 题目内容重写
**绝对美丽**

**题目描述**

Kirill有两个长度为$n$的整数数组$a_1,a_2,…,a_n$和$b_1,b_2,…,b_n$。他定义数组$b$的_绝对美丽_为
$$
\sum_{i=1}^n|a_i-b_i|
$$
其中，$|x|$表示$x$的绝对值。

Kirill最多可以执行一次以下操作：

- 选择两个索引$i$和$j$（$1≤i<j≤n$），并交换$b_i$和$b_j$的值。

帮助他在执行**最多一次**交换后，找到数组$b$的最大可能绝对美丽。

**说明/提示**

在第一个测试用例中，每个可能的交换都不会改变数组$b$。

在第二个测试用例中，不执行交换时数组$b$的绝对美丽为$|1-1| + |2-2| = 0$。交换数组$b$中的第一个和第二个元素后，绝对美丽变为$|1-2| + |2-1| = 2$。这些是所有可能的结果，因此答案是$2$。

在第三个测试用例中，Kirill不执行交换是最优的。与上一个测试用例类似，答案是$2$。

在第四个测试用例中，无论Kirill做什么，数组$b$的绝对美丽都保持为$16$。

**样例 #1**

**输入**

```
6
3
1 3 5
3 3 3
2
1 2
1 2
2
1 2
2 1
4
1 2 3 4
5 6 7 8
10
1 8 2 5 3 5 3 1 1 3
2 9 2 4 8 2 3 5 3 1
3
47326 6958 358653
3587 35863 59474
```

**输出**

```
4
2
2
16
31
419045
```

### 算法分类
贪心

### 题解分析与结论
题目要求通过最多一次交换操作，最大化数组$b$的绝对美丽。题解中普遍采用了将问题转化为线段长度的方法，通过分类讨论线段的相交情况，确定交换操作对绝对美丽的影响。最终，通过贪心策略找到最优的交换对，使得绝对美丽最大化。

### 评分较高的题解
#### 1. 作者：mountain_climber (赞：8)
**星级：5星**
**关键亮点：**
- 将绝对值问题转化为线段长度，清晰直观。
- 通过分类讨论线段的相交情况，明确了交换操作的影响。
- 代码简洁高效，时间复杂度为$O(n)$。

**核心代码：**
```cpp
int l=inf,r=0,ans=0;
for(int i=1;i<=n;i++) ans+=abs(a[i]-b[i]); 
for(int i=1;i<=n;i++){
    l=min(l,max(a[i],b[i]));
    r=max(r,min(a[i],b[i]));
}
printf("%lld\n",ans+(2*(r-l)>0?2*(r-l):0));
```
**实现思想：** 首先计算不交换时的绝对美丽，然后通过遍历找到最优的交换对，计算交换后的绝对美丽。

#### 2. 作者：LittleAcbg (赞：8)
**星级：5星**
**关键亮点：**
- 通过数轴上的线段长度分析问题，思路清晰。
- 贪心策略明确，找到最大左端点和最小右端点。
- 代码简洁，时间复杂度为$O(n)$。

**核心代码：**
```cpp
int minn = 1e+9,maxx = 0,sum = 0;
for (int i = 1; i <= n; ++i)
{
    minn = min(minn, max(a[i], b[i]));
    maxx = max(maxx, min(a[i], b[i]));
    sum += abs(a[i] - b[i]);
}
cout << sum + max(0LL, (maxx - minn) * 2) << endl;
```
**实现思想：** 计算不交换时的绝对美丽，然后通过遍历找到最优的交换对，计算交换后的绝对美丽。

#### 3. 作者：_ZML_ (赞：2)
**星级：4星**
**关键亮点：**
- 通过数轴上的线段长度分析问题，思路清晰。
- 贪心策略明确，找到最大左端点和最小右端点。
- 代码简洁，时间复杂度为$O(n)$。

**核心代码：**
```cpp
int mx=-1e9, mn=1e9, ans=0;
for(int i=1;i<=n;i++) {
    ans+=abs(b[i]-a[i]);
    mx=max(mx,a[i]); mn=min(mn,b[i]);
}
if(mx>mn) ans+=2*(mx-mn);
cout<<ans<<"\n";
```
**实现思想：** 计算不交换时的绝对美丽，然后通过遍历找到最优的交换对，计算交换后的绝对美丽。

### 最优关键思路或技巧
1. **线段长度转化**：将绝对值问题转化为数轴上的线段长度，便于分析和计算。
2. **贪心策略**：通过找到最大左端点和最小右端点，确定最优的交换对。
3. **分类讨论**：通过分类讨论线段的相交情况，明确交换操作对绝对美丽的影响。

### 可拓展之处
类似的问题可以通过将绝对值转化为线段长度，结合贪心策略进行优化。例如，在最大化或最小化某些与绝对值相关的目标函数时，可以采用类似的思路。

### 推荐题目
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

### 个人心得摘录
- **mountain_climber**：通过将绝对值问题转化为线段长度，思路更加清晰，代码实现也更加简洁。
- **LittleAcbg**：贪心策略的明确性使得问题解决更加高效，代码实现也非常简洁。
- **_ZML_**：通过数轴上的线段长度分析问题，思路清晰，代码实现简洁高效。

---
处理用时：49.03秒