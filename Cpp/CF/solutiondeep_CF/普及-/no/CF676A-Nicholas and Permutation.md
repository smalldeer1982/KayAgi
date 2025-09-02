# 题目信息

# Nicholas and Permutation

## 题目描述

Nicholas has an array $ a $ that contains $ n $ distinct integers from $ 1 $ to $ n $ . In other words, Nicholas has a permutation of size $ n $ .

Nicholas want the minimum element (integer $ 1 $ ) and the maximum element (integer $ n $ ) to be as far as possible from each other. He wants to perform exactly one swap in order to maximize the distance between the minimum and the maximum elements. The distance between two elements is considered to be equal to the absolute difference between their positions.

## 说明/提示

In the first sample, one may obtain the optimal answer by swapping elements $ 1 $ and $ 2 $ .

In the second sample, the minimum and the maximum elements will be located in the opposite ends of the array if we swap $ 7 $ and $ 2 $ .

In the third sample, the distance between the minimum and the maximum elements is already maximum possible, so we just perform some unnecessary swap, for example, one can swap $ 5 $ and $ 2 $ .

## 样例 #1

### 输入

```
5
4 5 1 3 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
7
1 6 5 3 4 7 2
```

### 输出

```
6
```

## 样例 #3

### 输入

```
6
6 5 4 3 2 1
```

### 输出

```
5
```

# AI分析结果

### 题目中文重写
# Nicholas和排列

## 题目描述
Nicholas 有一个数组 $a$，其中包含 $n$ 个从 $1$ 到 $n$ 的不同整数。换句话说，Nicholas 有一个长度为 $n$ 的排列。

Nicholas 希望最小元素（整数 $1$）和最大元素（整数 $n$）之间的距离尽可能远。他想恰好进行一次交换，以使最小元素和最大元素之间的距离最大化。两个元素之间的距离被认为等于它们位置的绝对差值。

## 说明/提示
在第一个样例中，可以通过交换元素 $1$ 和 $2$ 得到最优答案。

在第二个样例中，如果我们交换 $7$ 和 $2$，最小元素和最大元素将位于数组的两端。

在第三个样例中，最小元素和最大元素之间的距离已经是最大可能值，所以我们只需进行一些不必要的交换，例如，可以交换 $5$ 和 $2$。

## 样例 #1
### 输入
```
5
4 5 1 3 2
```
### 输出
```
3
```

## 样例 #2
### 输入
```
7
1 6 5 3 4 7 2
```
### 输出
```
6
```

## 样例 #3
### 输入
```
6
6 5 4 3 2 1
```
### 输出
```
5
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是先找出数组中最大值和最小值的位置，然后通过枚举四种情况（最大值移到最左边、最大值移到最右边、最小值移到最左边、最小值移到最右边）得到的距离，取其中的最大值作为结果。
- **思路**：都是先遍历数组找到最大值和最小值的位置，再对四种交换情况进行分析。
- **算法要点**：准确记录最大值和最小值的位置，然后比较四种情况的距离大小。
- **解决难点**：正确找出四种交换情况并比较它们的距离，以得到最大距离。

### 题解评分
| 作者 | 评分 | 思路清晰度 | 代码可读性 | 优化程度 |
| --- | --- | --- | --- | --- |
| chl123123 | 4星 | 清晰，明确指出比较四种情况 | 较高，变量命名有注释 | 一般，常规做法 |
| Cult_style | 3星 | 较清晰，说明了思路和式子 | 一般，式子需理解 | 一般，常规思路 |
| q779 | 3星 | 清晰，说明了四种情况 | 一般，代码格式较复杂 | 一般，常规做法 |
| hswfwkj_ | 4星 | 清晰，详细列出四种情况 | 较高，代码简洁 | 一般，常规做法 |
| WinterRain208 | 3星 | 清晰，说明了贪心思路和四种情况 | 一般，有自定义宏 | 一般，常规做法 |
| happybob | 3星 | 较清晰，说明了特殊情况和一般情况 | 一般，使用了类 | 一般，常规做法 |
| CZQ_King | 3星 | 较清晰，提到用 `max` 函数 | 一般，使用结构体 | 一般，常规做法 |
| RioBlu | 3星 | 清晰，说明了四种情况 | 一般，变量命名简单 | 一般，常规做法 |

### 所选题解
- chl123123（4星）：思路清晰，明确指出比较四种情况，代码有注释，可读性高。
- hswfwkj_（4星）：详细列出四种情况，代码简洁易懂。

### 重点代码
#### chl123123 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100+10];
int main()
{
    int n,i,min1=999999,max1=-1,z1,z2;
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>a[i];
        if(a[i]<min1)
        {
             min1=a[i];
             z1=i;
        }
        if(a[i]>max1)
        {
             max1=a[i];
             z2=i;
        }
    }
    cout<<max(max(z2-1,n-z2),max(z1-1,n-z1));
    return 0;
}
```
**核心实现思想**：先遍历数组找到最小值和最大值的位置，然后比较四种情况（最大值到最左边、最大值到最右边、最小值到最左边、最小值到最右边）的距离，输出最大值。

#### hswfwkj_ 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,i,a,Max=-1,Min=999999999,position2,position1;
    cin>>n;
    for(i=1;i<=n;i++){
        cin>>a;
        if(Max<a){
            Max=a;position1=i;
        }
        if(Min>a){
            Min=a;position2=i;
        }
    }
    cout<<max(max(position2-1,n-position2),max(position1-1,n-position1));
    return 0;
}
```
**核心实现思想**：同样先遍历数组记录最大值和最小值的位置，再比较四种情况的距离，输出最大距离。

### 最优关键思路或技巧
- 贪心策略：通过分析可知，要使最小元素和最大元素距离最远，只需要考虑将最大值或最小值移到数组的最左边或最右边这四种情况。
- 记录位置：在遍历数组时，同时记录最大值和最小值的位置，方便后续计算距离。

### 拓展思路
同类型题可能会有更多的限制条件，例如交换次数限制、数组元素有重复等。类似算法套路可以应用在需要通过有限操作达到最优结果的问题中，先分析所有可能的操作情况，再通过贪心策略选择最优操作。

### 推荐洛谷题目
- P1007 独木桥
- P1223 排队接水
- P1803 凌乱的yyy / 线段覆盖

### 个人心得
本题题解中没有明显的个人心得（调试/顿悟）内容。 

---
处理用时：37.55秒