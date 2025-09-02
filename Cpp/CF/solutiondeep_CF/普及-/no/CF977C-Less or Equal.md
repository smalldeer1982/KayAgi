# 题目信息

# Less or Equal

## 题目描述

You are given a sequence of integers of length $ n $ and integer number $ k $ . You should print any integer number $ x $ in the range of $ [1; 10^9] $ (i.e. $ 1 \le x \le 10^9 $ ) such that exactly $ k $ elements of given sequence are less than or equal to $ x $ .

Note that the sequence can contain equal elements.

If there is no such $ x $ , print "-1" (without quotes).

## 说明/提示

In the first example $ 5 $ is also a valid answer because the elements with indices $ [1, 3, 4, 6] $ is less than or equal to $ 5 $ and obviously less than or equal to $ 6 $ .

In the second example you cannot choose any number that only $ 2 $ elements of the given sequence will be less than or equal to this number because $ 3 $ elements of the given sequence will be also less than or equal to this number.

## 样例 #1

### 输入

```
7 4
3 7 5 1 10 3 20
```

### 输出

```
6```

## 样例 #2

### 输入

```
7 2
3 7 5 1 10 3 20
```

### 输出

```
-1
```

# AI分析结果

### 题目中文重写
# 小于或等于

## 题目描述
给定一个长度为 $n$ 的整数序列和整数 $k$，你需要打印出任意一个在 $[1; 10^9]$ 范围内（即 $1 \le x \le 10^9$）的整数 $x$，使得给定序列中恰好有 $k$ 个元素小于或等于 $x$。

注意，该序列中可能包含相等的元素。

如果不存在这样的 $x$，则打印 “-1”（不包含引号）。

## 说明/提示
在第一个样例中，5 也是一个有效的答案，因为索引为 $[1, 3, 4, 6]$ 的元素小于或等于 5，并且显然也小于或等于 6。

在第二个样例中，你无法选择任何一个数，使得给定序列中只有 2 个元素小于或等于这个数，因为给定序列中会有 3 个元素也小于或等于这个数。

## 样例 #1
### 输入
```
7 4
3 7 5 1 10 3 20
```
### 输出
```
6
```

## 样例 #2
### 输入
```
7 2
3 7 5 1 10 3 20
```
### 输出
```
-1
```

### 算法分类
排序

### 综合分析与结论
这些题解的核心思路都是先对给定的整数序列进行排序，然后根据 $k$ 的值和序列的特点进行分类讨论，判断是否存在满足条件的 $x$。
- **思路**：排序后，根据 $k$ 的不同取值情况进行分析。当 $k = 0$ 时，需要判断序列中最小的数是否为 1，若为 1 则无解，否则可输出 1 或最小数减 1；当 $k > 0$ 时，需要判断第 $k$ 个数和第 $k + 1$ 个数是否相等，若相等则无解，否则输出第 $k$ 个数。
- **算法要点**：主要是排序操作，使用 `sort` 函数对数组进行排序，然后通过条件判断来确定是否有解以及解的值。
- **解决难点**：主要难点在于对特殊情况的处理，如 $k = 0$ 时的边界条件判断，以及 $k > 0$ 时第 $k$ 个数和第 $k + 1$ 个数相等的情况。

### 所选题解
- **lichenzhen（4星）**
    - **关键亮点**：思路清晰，对无解情况的分析详细，代码简洁明了。
    - **个人心得**：无
- **xhz0311（4星）**
    - **关键亮点**：详细记录了自己的思考过程和调试经历，对各种错误情况的分析很有价值。
    - **个人心得**：在洛谷上一直 UKE，去 codeforces 交就 AC 了，估计是 CF 新年彩蛋惹的祸。
- **Eason_AC（4星）**
    - **关键亮点**：代码简洁，使用三目运算符进行条件判断，逻辑清晰。
    - **个人心得**：无

### 重点代码
#### lichenzhen 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000001];
int main()
{
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    if(k==0) 
    {
        if(a[1]==1){
            cout<<-1;
            return 0;
        }
        else {
            cout<<a[1]-1;//也可以输出1 
            return 0;
        }
    }
    if(a[k]==a[k+1]){
        cout<<-1;
        return 0;
    }
    cout<<a[k];
}
```
**核心实现思想**：先读取输入的 $n$ 和 $k$ 以及数组元素，然后对数组进行排序。对于 $k = 0$ 的情况，判断最小元素是否为 1，若为 1 则无解，否则输出最小元素减 1；对于 $k > 0$ 的情况，判断第 $k$ 个元素和第 $k + 1$ 个元素是否相等，若相等则无解，否则输出第 $k$ 个元素。

#### xhz0311 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n,k;
    cin>>n>>k;
    int a[n+1];
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    sort(a+1,a+n+1);
    if(k==0 && a[1]==1) //若k=0且a[1]=1，则无解
    {
        cout<<-1;
    }
    else if(k==0)//若k=0且a[1]≠1，则x=1必定满足题意
    {
        cout<<"1";
    }
    else if(a[k]==a[k+1])//如果a[k]=a[k+1]，则一定无解
    {
        cout<<"-1";
    }
    else
    {
        cout<<a[k];//特判结束，放心输出a[k]
    }
    return 0;
}
```
**核心实现思想**：同样先读取输入并排序，然后通过多个条件判断来确定是否有解以及解的值，对 $k = 0$ 和 $k > 0$ 的情况分别进行处理。

#### Eason_AC 的代码
```cpp
int n, k, a[200007], ans;

int main() {
    getint(n), getint(k);
    _for(i, 1, n) getint(a[i]);
    sort(a + 1, a + n + 1);
    ans = (!k ? (a[1] > 1 ? a[1] - 1 : -1) : (a[k] == a[k + 1] ? -1 : a[k]));
    writeint(ans);
    return 0;
}
```
**核心实现思想**：读取输入并排序后，使用三目运算符根据 $k$ 的值和数组元素的关系来确定 $ans$ 的值，最后输出 $ans$。

### 最优关键思路或技巧
- 先对序列进行排序，这样可以方便地找到第 $k$ 大的数。
- 对 $k = 0$ 和 $k > 0$ 的情况分别进行特判，处理边界条件。
- 注意判断第 $k$ 个数和第 $k + 1$ 个数是否相等，避免出现错误。

### 拓展思路
同类型题可能会改变数据范围、增加约束条件或改变问题的描述方式，但核心思路仍然是排序和分类讨论。例如，可能会要求找到满足条件的最小或最大的 $x$，或者要求找到所有满足条件的 $x$ 等。

### 推荐洛谷题目
- P1177 【模板】排序
- P1093 奖学金
- P1271 【深基9.例1】选举学生会

---
处理用时：45.73秒