# 题目信息

# Sakurako's Task

## 题目描述

Sakurako has prepared a task for you:

She gives you an array of $ n $ integers and allows you to choose $ i $ and $ j $ such that $ i \neq j $ and $ a_i \ge a_j $ , and then assign $ a_i = a_i - a_j $ or $ a_i = a_i + a_j $ . You can perform this operation any number of times for any $ i $ and $ j $ , as long as they satisfy the conditions.

Sakurako asks you what is the maximum possible value of $ mex_k $ $ ^{\text{∗}} $ of the array after any number of operations.

 $ ^{\text{∗}} $ $ mex_k $ is the $ k $ -th non-negative integer that is absent in the array. For example, $ mex_1(\{1,2,3 \})=0 $ , since $ 0 $ is the first element that is not in the array, and $ mex_2(\{0,2,4 \})=3 $ , since $ 3 $ is the second element that is not in the array.

## 样例 #1

### 输入

```
6
1 3
3
2 10
1 1
3 1
1 2 3
3 2
1 2 4
4 5
2 2 2 16
4 5
2 2 2 3```

### 输出

```
2
11
3
4
8
8```

# AI分析结果

### 题目内容中文重写
# 樱子的任务

## 题目描述
樱子为你准备了一个任务：

她给你一个包含 $n$ 个整数的数组，并允许你选择 $i$ 和 $j$，使得 $i \neq j$ 且 $a_i \geq a_j$，然后将 $a_i$ 赋值为 $a_i - a_j$ 或 $a_i = a_i + a_j$。只要满足条件，你可以对任意的 $i$ 和 $j$ 进行任意次数的此操作。

樱子问你，在进行任意次数的操作后，数组的 $mex_k$ $^{\text{∗}}$ 的最大可能值是多少。

$^{\text{∗}}$ $mex_k$ 是数组中缺失的第 $k$ 个非负整数。例如，$mex_1(\{1,2,3 \}) = 0$，因为 $0$ 是数组中第一个缺失的元素；$mex_2(\{0,2,4 \}) = 3$，因为 $3$ 是数组中第二个缺失的元素。

## 样例 #1
### 输入
```
6
1 3
3
2 10
1 1
3 1
1 2 3
3 2
1 2 4
4 5
2 2 2 16
4 5
2 2 2 3
```

### 输出
```
2
11
3
4
8
8
```

### 题解综合分析与结论
这些题解核心思路一致，都是先处理 $n = 1$ 的特殊情况，对于 $n > 1$，利用裴蜀定理得出数组经过操作后能得到的元素应是数组所有元素最大公约数 $d$ 的倍数或为 $0$，然后构造出最优序列 $b_i=(i - 1) \times d$，最后计算该序列的 $mex_k$。

算法要点：
1. 计算数组所有元素的最大公约数 $d$。
2. 分情况讨论 $n$ 的值和 $d$ 的值，计算 $mex_k$。

解决难点：
1. 发现操作与最大公约数的联系，这需要对裴蜀定理有一定了解。
2. 构造出最优序列以计算 $mex_k$。

### 所选题解
- **作者：eb0ycn（5星）**
    - 关键亮点：思路清晰，代码简洁，对不同情况的处理逻辑明确。
    ```cpp
    #include<cstdio>
    int t,n,k,d,a;
    int gcd(int a,int b){return b?gcd(b,a%b):a;}
    int main(){
        scanf("%d",&t);
        while(t--){
            scanf("%d%d",&n,&k),d=0;
            for(int i=0;i<n;++i)scanf("%d",&a),d=gcd(d,a);
            if(n==1)printf("%d\n",k-(a>=k));
            else if(k>1ll*(n-1)*(d-1))printf("%d\n",k+n-1);
            else a=(k+d-2)/(d-1)-1,printf("%d\n",a+k);
        }
        return 0;
    }
    ```
    核心实现思想：先计算 $t$ 组数据，每组数据输入 $n$ 和 $k$ 后，计算数组元素的最大公约数 $d$。对于 $n = 1$ 的情况直接计算结果，对于 $n > 1$ 的情况，根据 $k$ 与 $(n - 1) \times (d - 1)$ 的大小关系计算结果。

- **作者：Super_Cube（4星）**
    - 关键亮点：代码使用标准库函数，简洁明了，对不同情况的判断清晰。
    ```cpp
    #include<bits/stdc++.h>
    int T,n,m,d;
    int main(){
        scanf("%d",&T);
        while(T--){
            scanf("%d%d",&n,&m);
            d=0;
            for(int i=1,x;i<=n;++i)
                scanf("%d",&x),d=std::__gcd(d,x);
            if(!d||n==1)
                printf("%d\n",m-(m<=d));
            else if(d==1)
                printf("%d\n",n-1+m);
            else
                printf("%d\n",std::min((m-1)/(d-1),n-1)+m);
        }
        return 0;
    }
    ```
    核心实现思想：同样处理 $T$ 组数据，每组输入 $n$ 和 $m$ 后计算最大公约数 $d$，根据 $d$ 的值和 $n$ 的值分情况计算结果。

### 最优关键思路或技巧
- 思维方式：通过观察操作的特点，联想到裴蜀定理，从而将问题转化为求数组元素的最大公约数，进而构造最优序列。
- 代码实现技巧：使用递归函数计算最大公约数，简洁高效。

### 可拓展之处
同类型题可能会改变操作规则或 $mex$ 的定义，但核心思路依然是分析操作对数组元素的影响，找到元素之间的关系，构造最优序列。类似算法套路可用于处理一些涉及数论和序列构造的问题。

### 洛谷相似题目推荐
1. [P1072  Hankson的趣味题](https://www.luogu.com.cn/problem/P1072)：考察最大公约数和最小公倍数的知识。
2. [P2152  消防局的设立](https://www.luogu.com.cn/problem/P2152)：涉及贪心和数论相关知识。
3. [P2568  GCD](https://www.luogu.com.cn/problem/P2568)：主要考察最大公约数的计算和应用。

### 个人心得
题解中未包含个人心得内容。

---
处理用时：29.89秒