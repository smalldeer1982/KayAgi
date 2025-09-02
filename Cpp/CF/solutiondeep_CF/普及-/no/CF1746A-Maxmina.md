# 题目信息

# Maxmina

## 题目描述

You have an array $ a $ of size $ n $ consisting only of zeroes and ones and an integer $ k $ . In one operation you can do one of the following:

- Select $ 2 $ consecutive elements of $ a $ and replace them with their minimum (that is, let $ a := [a_{1}, a_{2}, \ldots, a_{i-1}, \min(a_{i}, a_{i+1}), a_{i+2}, \ldots, a_{n}] $ for some $ 1 \le i \le n-1 $ ). This operation decreases the size of $ a $ by $ 1 $ .
- Select $ k $ consecutive elements of $ a $ and replace them with their maximum (that is, let $ a := [a_{1}, a_{2}, \ldots, a_{i-1}, \max(a_{i}, a_{i+1}, \ldots, a_{i+k-1}), a_{i+k}, \ldots, a_{n}] $ for some $ 1 \le i \le n-k+1 $ ). This operation decreases the size of $ a $ by $ k-1 $ .

Determine if it's possible to turn $ a $ into $ [1] $ after several (possibly zero) operations.

## 说明/提示

In the first test case, you can perform the second type operation on second and third elements so $ a $ becomes $ [0, 1] $ , then you can perform the second type operation on first and second elements, so $ a $ turns to $ [1] $ .

In the fourth test case, it's obvious to see that you can't make any $ 1 $ , no matter what you do.

In the fifth test case, you can first perform a type 2 operation on the first three elements so that $ a $ becomes $ [1, 0, 0, 1] $ , then perform a type 2 operation on the elements in positions two through four, so that $ a $ becomes $ [1, 1] $ , and finally perform the first type operation on the remaining elements, so that $ a $ becomes $ [1] $ .

## 样例 #1

### 输入

```
7
3 2
0 1 0
5 3
1 0 1 1 0
2 2
1 1
4 4
0 0 0 0
6 3
0 0 1 0 0 1
7 5
1 1 1 1 1 1 1
5 3
0 0 1 0 0```

### 输出

```
YES
YES
YES
NO
YES
YES
YES```

# AI分析结果

### 题目内容
# Maxmina

## 题目描述
你有一个大小为 $n$ 的数组 $a$，数组仅由 $0$ 和 $1$ 组成，还有一个整数 $k$ 。在一次操作中，你可以执行以下操作之一：
- 选择 $a$ 中的 $2$ 个连续元素，将它们替换为二者中的最小值（即，对于某个 $1 \leq i \leq n - 1$，令 $a := [a_{1}, a_{2}, \ldots, a_{i - 1}, \min(a_{i}, a_{i + 1}), a_{i + 2}, \ldots, a_{n}]$ ）。此操作会使 $a$ 的大小减 $1$ 。
- 选择 $a$ 中的 $k$ 个连续元素，将它们替换为这 $k$ 个元素中的最大值（即，对于某个 $1 \leq i \leq n - k + 1$，令 $a := [a_{1}, a_{2}, \ldots, a_{i - 1}, \max(a_{i}, a_{i + 1}, \ldots, a_{i + k - 1}), a_{i + k}, \ldots, a_{n}]$ ）。此操作会使 $a$ 的大小减 $k - 1$ 。

判断经过若干次（可能为零次）操作后，是否有可能将数组 $a$ 变为 $[1]$ 。

## 说明/提示
在第一个测试用例中，你可以对第二个和第三个元素执行第二种类型的操作，这样 $a$ 变为 $[0, 1]$ ，然后你可以对第一个和第二个元素执行第二种类型的操作，这样 $a$ 就变为 $[1]$ 。

在第四个测试用例中，很明显可以看出，无论你怎么做，都无法得到 $1$ 。

在第五个测试用例中，你可以首先对前三个元素执行类型 $2$ 的操作，使 $a$ 变为 $[1, 0, 0, 1]$ ，然后对位置二到四的元素执行类型 $2$ 的操作，使 $a$ 变为 $[1, 1]$ ，最后对剩下的元素执行第一种类型的操作，使 $a$ 变为 $[1]$ 。

## 样例 #1
### 输入
```
7
3 2
0 1 0
5 3
1 0 1 1 0
2 2
1 1
4 4
0 0 0 0
6 3
0 0 1 0 0 1
7 5
1 1 1 1 1 1 1
5 3
0 0 1 0 0
```
### 输出
```
YES
YES
YES
NO
YES
YES
YES
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路较为统一，都发现了只要数组中存在 $1$ ，利用第二种操作（取 $k$ 个连续元素的最大值）就能将数组变为 $[1]$ ，若数组全为 $0$ 则无法达成目标。各题解在实现上略有不同，有的通过按位或判断是否有 $1$ ，有的通过计数或遍历判断。解决难点在于理解两种操作对数组元素的影响，并从中找出关键条件，即数组中是否存在 $1$ 。

### 所选的题解
- **作者：cjh20090318（5星）**
  - **关键亮点**：思路清晰，代码简洁高效，利用按位或操作简洁地判断数组中是否存在 $1$ ，时间复杂度为 $O(tn)$ 。
  - **个人心得**：无
  - **重点代码**：
```cpp
#include<iostream>
#include<cstdio>
int main(){
    int t,n,k;scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&k);
        bool a,b=0;
        for(int i=0;i<n;i++)  std::cin>>a,b|=a;
        //输入 0 或 1 后按位或。
        puts(b?"YES":"NO");
    }
    return 0;
}
```
  - **核心实现思想**：通过循环读入每个数字，并与变量 $b$ 进行按位或操作，若数组中有 $1$ ，最终 $b$ 为真，输出 `YES`，否则输出 `NO`。
- **作者：Awsdkl（4星）**
  - **关键亮点**：逻辑清晰，通过计数分别统计 $1$ 和 $0$ 的个数，进而判断数组中是否存在 $1$ 。
  - **个人心得**：无
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

int t;
int n,k;
int a;

int main()
{
    scanf("%d",&t);
    while(t--)
    {
        int len1 = 0,len0 = 0;
        scanf("%d%d",&n,&k);
        for(int i = 1;i <= n;i++)
        {
            scanf("%d",&a);
            if(a) len1++;
            else len0++;
        }
        if(len1 >= 1)
        {
            printf("YES\n");
        }
        else printf("NO\n");
    }

    return 0;
}
```
  - **核心实现思想**：遍历数组，对读入的数字进行判断，是 $1$ 则 $len1$ 加 $1$ ，是 $0$ 则 $len0$ 加 $1$ ，最后根据 $len1$ 是否大于等于 $1$ 输出结果。
- **作者：Rnfcr（4星）**
  - **关键亮点**：代码简洁，使用布尔变量 `one` 标记数组中是否存在 $1$ ，通过一次遍历完成判断。
  - **个人心得**：无
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,T,num,k;
int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        bool one=false;//判定有没有1
        for(int i=1;i<=n;i++){
            cin>>num;
            if(num) one=true;
        }
        if(one) cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}
```
  - **核心实现思想**：初始化布尔变量 `one` 为 `false` ，遍历数组，若读入数字为 $1$ 则将 `one` 置为 `true` ，最后根据 `one` 的值输出结果。

### 最优关键思路或技巧
通过分析两种操作对由 $0$ 和 $1$ 组成的数组的影响，发现数组中是否存在 $1$ 是决定能否通过操作得到 $[1]$ 的关键条件，从而简化问题，直接判断数组中是否有 $1$ 即可。

### 拓展
同类型题通常围绕对数组元素的特定操作以及判断能否达到某种目标状态展开。类似算法套路是深入分析操作对数据的影响，找出决定结果的关键因素，进而简化问题求解。

### 洛谷推荐题目
- [P1088 火星人](https://www.luogu.com.cn/problem/P1088)：涉及对数组元素的操作以及状态判断，与本题思路有相似之处。
- [P1241 括号序列](https://www.luogu.com.cn/problem/P1241)：通过对字符串（类似数组）的操作判断是否满足某种条件，锻炼分析操作影响的能力。
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：根据不同购买方案（类似本题操作）选择最优解，考察贪心策略的应用。 

---
处理用时：49.70秒