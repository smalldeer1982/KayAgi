# 题目信息

# Ehab Is an Odd Person

## 题目描述

You're given an array $ a $ of length $ n $ . You can perform the following operation on it as many times as you want:

- Pick two integers $ i $ and $ j $ $ (1 \le i,j \le n) $ such that  $ a_i+a_j $ is odd, then swap $ a_i $ and $ a_j $ .

What is lexicographically the smallest array you can obtain?

An array $ x $ is [lexicographically smaller](https://en.wikipedia.org/wiki/Lexicographical_order) than an array $ y $ if there exists an index $ i $ such that $ x_i<y_i $ , and $ x_j=y_j $ for all $ 1 \le j < i $ . Less formally, at the first index $ i $ in which they differ, $ x_i<y_i $

## 说明/提示

In the first example, we can swap $ 1 $ and $ 4 $ since $ 1+4=5 $ , which is odd.

## 样例 #1

### 输入

```
3
4 1 7
```

### 输出

```
1 4 7 ```

## 样例 #2

### 输入

```
2
1 1
```

### 输出

```
1 1 ```

# AI分析结果

### 题目内容
# Ehab 是个奇怪的人

## 题目描述
给定一个长度为 $n$ 的数组 $a$ 。你可以对其进行任意多次以下操作：
- 选择两个整数 $i$ 和 $j$ （$1 \le i,j \le n$），使得 $a_i + a_j$ 为奇数，然后交换 $a_i$ 和 $a_j$ 。
你能得到的字典序最小的数组是什么？
如果存在一个索引 $i$ ，使得 $x_i < y_i$ ，并且对于所有 $1 \le j < i$ 都有 $x_j = y_j$ ，那么数组 $x$ 的字典序小于数组 $y$ 。更通俗地说，在它们首次不同的索引 $i$ 处，$x_i < y_i$ 。

## 说明/提示
在第一个示例中，我们可以交换 $1$ 和 $4$ ，因为 $1 + 4 = 5$ ，是奇数。

## 样例 #1
### 输入
```
3
4 1 7
```
### 输出
```
1 4 7 
```

## 样例 #2
### 输入
```
2
1 1
```
### 输出
```
1 1 
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是基于数组元素的奇偶性来决定最终的输出。若数组中所有元素奇偶性相同，由于无法进行交换操作，所以直接输出原数组；若数组中同时存在奇数和偶数，即存在和为奇数的数对可进行交换，通过证明可得出能对任意两个数进行交换，进而对数组排序得到字典序最小的数组。各题解的算法要点相似，均是先判断数组中奇数和偶数的存在情况，再据此进行输出或排序输出。解决难点在于理解当数组中同时存在奇数和偶数时，如何通过给定的交换规则实现任意两个数的交换，进而能够对数组进行排序。

### 所选的题解
 - **作者：宁_缺 (赞：7) - 5星**
    - **关键亮点**：思路清晰简洁，代码简短高效，直接点明做法，没有过多冗余表述。
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    int n,a[100001];
    int main(){
        bool o=0,j=0;cin>>n;
        for(int i=1;i<=n;++i)
            cin>>a[i],((a[i]&1)?j:o)=1;
        if(o&&j)sort(a+1,a+n+1);
        for(int i=1;i<=n;++i)printf("%d ",a[i]);
        return 0;
    }
    ```
    **核心实现思想**：通过遍历数组标记是否存在奇数和偶数，若两者都存在则对数组排序，最后输出数组。
 - **作者：CircleOO (赞：6) - 5星**
    - **关键亮点**：对特殊情况进行详细分析，并给出了“当数组中同时存在奇数和偶数时可对任意两个数进行交换”这一结论的证明过程，逻辑严谨。
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int MAXN=1e5+10;
    int n;
    int arr[MAXN];
    bool hasOdd=false,hasEven=false;
    int main(){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>arr[i];
            if(arr[i]%2==0)hasEven=true;
            else hasOdd=true;
        }
        if(hasOdd^hasEven){
            for(int i=1;i<=n;i++){
                cout<<arr[i]<<" ";
            }
        }else{
            sort(arr+1,arr+n+1);
            for(int i=1;i<=n;i++){
                cout<<arr[i]<<" "; 
            }
        }
        return 0;
    }
    ```
    **核心实现思想**：遍历数组判断奇数和偶数的存在情况，根据异或结果决定是直接输出原数组还是排序后输出。
 - **作者：清清老大 (赞：0) - 4星**
    - **关键亮点**：思路阐述清晰，先点明两数相加为奇数的条件，再分别讨论数组全为奇数或偶数以及同时存在奇数和偶数的情况。
    ```cpp
    #include<bits/stdc++.h>

    using namespace std;

    int n,a[110101];

    int main()
    {
        bool odd = 0,even = 0;
        cin >> n;
        for(int i = 0;i < n;i ++)
        {
            scanf("%d",&a[i]);
            if(a[i] % 2)
            {
                odd = 1;
            }
            else
            {
                even = 1;
            }
        }
        if(odd && even)
        {
            sort(a,a + n);
        }
        for(int i = 0;i < n;i ++)
        {
            printf("%d ",a[i]);
        }
        return 0;
    }
    ```
    **核心实现思想**：遍历数组标记奇数和偶数的存在情况，若两者都有则排序数组，最后输出数组。

### 最优关键思路或技巧
通过对数组元素奇偶性的判断来决定是否可以对数组进行排序以得到字典序最小的数组。当数组中同时存在奇数和偶数时，利用给定的交换规则证明可以实现任意两个数的交换，从而将问题转化为简单的排序问题。

### 拓展
同类型题或类似算法套路：此类题目通常会给出一些特殊的操作规则，需要深入分析这些规则对数据的影响，找到关键性质（如本题中通过奇偶性判断能否任意交换元素），进而将复杂问题简化为常见的算法问题（如排序）。

### 洛谷相似题目
 - [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：通过分析不同购买方案的性价比，选择最优方案，考察对条件的分析和简单的数学计算。
 - [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：根据给定的条件判断并计算满足条件的结果，涉及对条件的理解和简单的逻辑判断。
 - [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)：通过枚举不同数字组合，结合火柴棒使用规则来求解等式，考察枚举思想和对规则的应用。

### 个人心得摘录与总结
 - **作者：CircleOO**：提到本题题面具有迷惑性，有一定思维难度，但想清楚后代码难度不高，认为做此类题目多猜想是不错的方法，例如思考能否把数换到任意位置。总结为面对此类具有迷惑性的题目，要大胆猜想并深入分析规则背后的本质。 

---
处理用时：56.97秒