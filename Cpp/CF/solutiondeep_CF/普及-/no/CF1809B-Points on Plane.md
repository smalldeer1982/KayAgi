# 题目信息

# Points on Plane

## 题目描述

You are given a two-dimensional plane, and you need to place $ n $ chips on it.

You can place a chip only at a point with integer coordinates. The cost of placing a chip at the point $ (x, y) $ is equal to $ |x| + |y| $ (where $ |a| $ is the absolute value of $ a $ ).

The cost of placing $ n $ chips is equal to the maximum among the costs of each chip.

You need to place $ n $ chips on the plane in such a way that the Euclidean distance between each pair of chips is strictly greater than $ 1 $ , and the cost is the minimum possible.

## 说明/提示

In the first test case, you can place the only chip at point $ (0, 0) $ with total cost equal to $ 0 + 0 = 0 $ .

In the second test case, you can, for example, place chips at points $ (-1, 0) $ , $ (0, 1) $ and $ (1, 0) $ with costs $ |-1| + |0| = 1 $ , $ |0| + |1| = 1 $ and $ |0| + |1| = 1 $ . Distance between each pair of chips is greater than $ 1 $ (for example, distance between $ (-1, 0) $ and $ (0, 1) $ is equal to $ \sqrt{2} $ ). The total cost is equal to $ \max(1, 1, 1) = 1 $ .

In the third test case, you can, for example, place chips at points $ (-1, -1) $ , $ (-1, 1) $ , $ (1, 1) $ , $ (0, 0) $ and $ (0, 2) $ . The total cost is equal to $ \max(2, 2, 2, 0, 2) = 2 $ .

## 样例 #1

### 输入

```
4
1
3
5
975461057789971042```

### 输出

```
0
1
2
987654321```

# AI分析结果

### 题目内容
# 平面上的点

## 题目描述
给定一个二维平面，你需要在上面放置 \(n\) 个筹码。
你只能将筹码放置在整数坐标的点上。将筹码放置在点 \((x, y)\) 的成本等于 \(|x| + |y|\)（其中 \(|a|\) 是 \(a\) 的绝对值）。
放置 \(n\) 个筹码的成本等于每个筹码成本中的最大值。
你需要以这样一种方式在平面上放置 \(n\) 个筹码：每对筹码之间的欧几里得距离严格大于 \(1\)，并且成本尽可能小。

## 说明/提示
在第一个测试用例中，你可以将唯一的筹码放置在点 \((0, 0)\)，总成本等于 \(0 + 0 = 0\)。
在第二个测试用例中，例如，你可以将筹码放置在点 \((-1, 0)\)、\((0, 1)\) 和 \((1, 0)\)，成本分别为 \(|-1| + |0| = 1\)、\(|0| + |1| = 1\) 和 \(|0| + |1| = 1\)。每对筹码之间的距离大于 \(1\)（例如，\((-1, 0)\) 和 \((0, 1)\) 之间的距离等于 \(\sqrt{2}\)）。总成本等于 \(\max(1, 1, 1) = 1\)。
在第三个测试用例中，例如，你可以将筹码放置在点 \((-1, -1)\)、\((-1, 1)\)、\((1, 1)\)、\((0, 0)\) 和 \((0, 2)\)。总成本等于 \(\max(2, 2, 2, 0, 2) = 2\)。

## 样例 #1
### 输入
```
4
1
3
5
975461057789971042
```
### 输出
```
0
1
2
987654321
```

### 算法分类
数学

### 题解综合分析与结论
所有题解核心思路都是通过分析点的放置规律，找到放置 \(n\) 个满足欧几里得距离大于 \(1\) 的点时，成本最小值与 \(n\) 的关系。主要难点在于如何确定不同成本下能放置点的最大数量，以及如何根据 \(n\) 准确计算出最小成本。各题解通过观察点的排列形状（如正方形、菱形等），结合距离条件和成本定义，推导出公式。部分题解考虑到数据范围大，需处理精度问题。

### 所选的题解
- **作者：听取MLE声一片 (5星)**
    - **关键亮点**：思路清晰，从欧几里得距离条件转化为曼哈顿距离思考，通过对 \(|x| + |y|\) 奇偶性分类，严谨推导出每个成本 \(d\) 下最多能放置点的数量为 \((d + 1)^2\)，进而得出答案为 \(\lceil \sqrt{n} \rceil - 1\)。虽未给出代码，但思路极具启发性。
- **作者：jhdrgfj (4星)**
    - **关键亮点**：通过旋转图形直观展示点的放置规律，推出总代价为 \(x\) 时可放置 \((x + 1)^2\) 个点，得出 \(n\) 个点所需代价为 \(\sqrt{n} - 1\)，考虑到数据范围大，手写二分开根保证精度，代码实现完整。
    - **重点代码**：
```cpp
long long int ef(long long int a){    //开根函数
    __int128 l=0,r=a,mid=a/2ll;     //由于 longlong 在判断时会溢出，所以用__int128
    while (l<r){
        if (mid*mid<a){
            l=mid+1;
        }else if (mid*mid>=a){
            r=mid-1;
        }
        mid=(l+r+1)/2;
    }
    long long int c=l;
    if (c*c<a) return c+1;    //由于我们要求的是向上取整的根，所以要防止我的玄学开根返回向下取整的根
    return c;
} 
int main()
{
    long long int t,n;
    cin>>t;
    while (t--){
        cin>>n;
        cout<<ef(n)-1<<endl;    //调用开根函数，然后减 1
    }
}
```
    - **核心实现思想**：通过二分查找的方式，在 \([0, a]\) 的区间内寻找 \(a\) 的平方根，考虑到向上取整的需求，对结果进行特殊处理。
- **作者：Iniaugoty (4星)**
    - **关键亮点**：提供两种解法，解法一通过观察数据猜测公式并验证，解法二从曼哈顿距离角度严谨推导，得出答案为 \(\lceil \sqrt{n} \rceil - 1\)，代码简洁，使用 `sqrtl` 和 `ceil` 函数处理开根和向上取整。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n;
signed main(){
    scanf("%lld",&t);
    while(t--){
        scanf("%lld",&n);
        printf("%lld\n",(long long)ceil((long double)sqrtl(n))-1);
    }
    return 0;
}
```
    - **核心实现思想**：利用 `sqrtl` 函数计算 \(n\) 的平方根，再通过 `ceil` 函数向上取整，最后减 1 得到结果。

### 最优关键思路或技巧
通过观察点的排列规律，结合欧几里得距离和成本的定义，将问题转化为寻找不同成本下能放置点的最大数量，从而建立 \(n\) 与最小成本的关系。在实现时，对于大数据范围要注意处理精度问题，可采用手写二分或合适的高精度函数。

### 拓展
同类型题常涉及在特定几何空间中，依据距离、成本等限制条件放置元素并求最优解。类似算法套路是先通过画图观察元素放置规律，再结合数学知识推导公式。例如在其他几何图形（如三角形网格）中放置元素并满足一定条件求最值。

### 洛谷推荐题目
- [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)：通过对数字生成规律的分析，考察递推和数学思维。
- [P2678 [NOIP2015 普及组] 跳石头](https://www.luogu.com.cn/problem/P2678)：结合二分查找和对题目条件的数学分析解决最优解问题。
- [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：通过数学推导和枚举解决连续自然数求和问题，锻炼数学思维。 

---
处理用时：48.51秒