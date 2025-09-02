# 题目信息

# Maximum Balanced Circle

## 题目描述

There are $ n $ people in a row. The height of the $ i $ -th person is $ a_i $ . You can choose any subset of these people and try to arrange them into a balanced circle.

A balanced circle is such an order of people that the difference between heights of any adjacent people is no more than $ 1 $ . For example, let heights of chosen people be $ [a_{i_1}, a_{i_2}, \dots, a_{i_k}] $ , where $ k $ is the number of people you choose. Then the condition $ |a_{i_j} - a_{i_{j + 1}}| \le 1 $ should be satisfied for all $ j $ from $ 1 $ to $ k-1 $ and the condition $ |a_{i_1} - a_{i_k}| \le 1 $ should be also satisfied. $ |x| $ means the absolute value of $ x $ . It is obvious that the circle consisting of one person is balanced.

Your task is to choose the maximum number of people and construct a balanced circle consisting of all chosen people. It is obvious that the circle consisting of one person is balanced so the answer always exists.

## 样例 #1

### 输入

```
7
4 3 5 1 2 2 1
```

### 输出

```
5
2 1 1 2 3
```

## 样例 #2

### 输入

```
5
3 7 5 1 5
```

### 输出

```
2
5 5 
```

## 样例 #3

### 输入

```
3
5 1 4
```

### 输出

```
2
4 5 
```

## 样例 #4

### 输入

```
7
2 2 3 2 1 2 2
```

### 输出

```
7
1 2 2 2 2 3 2 
```

# AI分析结果

### 题目翻译
# 最大平衡圈

## 题目描述
有 $n$ 个人站成一排。第 $i$ 个人的身高是 $a_i$。你可以选择这些人的任意子集，并尝试将他们排列成一个平衡圈。

一个平衡圈是指这样一种人员排列顺序：任意相邻两人的身高差不超过 $1$。例如，设所选人员的身高为 $[a_{i_1}, a_{i_2}, \dots, a_{i_k}]$，其中 $k$ 是你选择的人数。那么对于从 $1$ 到 $k - 1$ 的所有 $j$，都应满足条件 $|a_{i_j} - a_{i_{j + 1}}| \le 1$，并且还应满足条件 $|a_{i_1} - a_{i_k}| \le 1$。$|x|$ 表示 $x$ 的绝对值。显然，由一个人组成的圈是平衡的。

你的任务是选择最多的人，并构造一个由所有所选人员组成的平衡圈。显然，由一个人组成的圈是平衡的，所以答案总是存在的。

## 样例 #1
### 输入
```
7
4 3 5 1 2 2 1
```
### 输出
```
5
2 1 1 2 3
```

## 样例 #2
### 输入
```
5
3 7 5 1 5
```
### 输出
```
2
5 5 
```

## 样例 #3
### 输入
```
3
5 1 4
```
### 输出
```
2
4 5 
```

## 样例 #4
### 输入
```
7
2 2 3 2 1 2 2
```
### 输出
```
7
1 2 2 2 2 3 2 
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是基于平衡圈的性质，即圈上的数必须连续，中间的数至少出现两次，通过不同方式找出满足条件的最大长度的平衡圈并构造出相应的排列。
- **思路对比**：大部分题解是通过统计每个数的出现次数，然后枚举起点，找满足条件的终点；也有使用双指针、二分等方法来确定区间。
- **算法要点**：都需要统计数的出现次数，部分题解使用前缀和辅助计算区间内数的总数；在构造平衡圈时，一般是先上升再下降的顺序。
- **解决难点**：关键在于如何高效地找出满足条件的最大区间，以及处理边界情况和数的出现次数的限制。

### 题解评分
- **shenmadongdong**：4星。思路清晰，代码简洁，直接通过遍历统计每个数的出现次数，然后找出最大的平衡圈区间。
- **ywy_c_asm**：3星。思路详细，但代码相对复杂，使用了自定义的输入函数，增加了代码的复杂度。
- **sieve**：2星。思路有一定的推导过程，但没有给出完整代码，实现细节不明确。
- **ttq012**：3星。使用ST表维护区间信息，时间复杂度较高，代码实现相对复杂。
- **_lgh_**：3星。思路正确，但只给出了部分代码，不完整。
- **XCH_0803**：3星。使用双指针法，思路清晰，但代码中部分变量命名不够清晰。

### 所选题解
- **shenmadongdong**：4星。关键亮点在于思路简洁直接，通过一次遍历统计出现次数，再一次遍历找出最大平衡圈区间，代码实现简单易懂。

### 重点代码
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(register int i=a;i<=b;++i)
#define req(i,a,b) for(register int i=a;i>=b;--i)
using namespace std;
int n,a,num[200010],l,c,m,r,p;
int main()
{
    cin>>n;
    rep(i,1,n) scanf("%d",&a),num[a]++;//统计每个数的出现次数
    rep(i,1,200001)//需要多统计一次，否则2e5开始的区间会炸
    {
        if (l&&num[i]<2) {c+=num[i];if (c>=m) m=c,p=l,r=i;c=0,l=0;}//环的区间的结束
        else if (l&&num[i]>=2) c+=num[i];
        if (!l&&num[i]) l=i,c+=num[i];//环的区间的开始
    }
    printf("%d\n",m);//最大环长度
    rep(i,p,r) rep(j,1,num[i]-1) printf("%d ",i);
    req(i,r,p) if (num[i]) printf("%d ",i);//显而易见的构造，使其先上升再下降
    return 0;
}
```
**核心实现思想**：先统计每个数的出现次数，然后遍历这些数，当遇到出现次数小于2的数时，判断当前统计的区间长度是否为最大，更新最大长度和区间端点；最后按照先上升再下降的顺序构造平衡圈并输出。

### 拓展思路
同类型题可能会有不同的限制条件，如相邻元素的差值范围变化、圈的其他性质要求等。类似算法套路可以是先分析问题的性质，找出关键特征，然后通过枚举、双指针、二分等方法来确定满足条件的区间，最后进行构造。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：考察贪心算法，与本题的贪心选择思路有一定相似性。
2. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：使用二分法解决问题，与本题中部分题解使用二分确定区间有相似之处。
3. [P1886 滑动窗口 /【模板】单调队列](https://www.luogu.com.cn/problem/P1886)：使用队列维护区间信息，与本题中使用数据结构辅助解题的思想类似。

### 个人心得
题解中没有明显的个人心得内容。

---
处理用时：45.06秒