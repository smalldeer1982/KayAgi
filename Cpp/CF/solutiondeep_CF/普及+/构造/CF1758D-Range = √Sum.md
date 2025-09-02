# 题目信息

# Range = √Sum

## 题目描述

You are given an integer $ n $ . Find a sequence of $ n $ distinct integers $ a_1, a_2, \dots, a_n $ such that $ 1 \leq a_i \leq 10^9 $ for all $ i $ and $ $$$\max(a_1, a_2, \dots, a_n) - \min(a_1, a_2, \dots, a_n)= \sqrt{a_1 + a_2 + \dots + a_n}. $ $$$

It can be proven that there exists a sequence of distinct integers that satisfies all the conditions above.

## 说明/提示

In the first test case, the maximum is $ 3 $ , the minimum is $ 1 $ , the sum is $ 4 $ , and $ 3 - 1 = \sqrt{4} $ .

In the second test case, the maximum is $ 29 $ , the minimum is $ 18 $ , the sum is $ 121 $ , and $ 29-18 = \sqrt{121} $ .

For each test case, the integers are all distinct.

## 样例 #1

### 输入

```
3
2
5
4```

### 输出

```
3 1
20 29 18 26 28
25 21 23 31```

# AI分析结果

### 题目中文重写
## 题目描述
给定一个整数 $n$。找出一个由 $n$ 个不同整数 $a_1, a_2, \dots, a_n$ 组成的序列，使得对于所有的 $i$ 都有 $1 \leq a_i \leq 10^9$，并且满足：
$$\max(a_1, a_2, \dots, a_n) - \min(a_1, a_2, \dots, a_n)= \sqrt{a_1 + a_2 + \dots + a_n}$$

可以证明，存在满足上述所有条件的不同整数序列。

## 说明/提示
在第一个测试用例中，最大值是 $3$，最小值是 $1$，总和是 $4$，并且 $3 - 1 = \sqrt{4}$。

在第二个测试用例中，最大值是 $29$，最小值是 $18$，总和是 $121$，并且 $29 - 18 = \sqrt{121}$。

对于每个测试用例，这些整数都是不同的。

## 样例 #1
### 输入
```
3
2
5
4
```

### 输出
```
3 1
20 29 18 26 28
25 21 23 31
```

### 综合分析与结论
这些题解的核心目标都是构造一个长度为 $n$ 的不同整数序列，使其满足最大值与最小值的差等于序列元素和的平方根。不同题解的思路和构造方法各有特色：
- **钦定和值构造**：如 nullqtr_pwp 和 Skykguj 的题解，钦定序列和为 $4n^2$，差值为 $2n$，通过初始序列和整体加值的方式逼近目标和，再调整剩余差值。
- **分奇偶构造**：Binary_Lee、_Fancy_、Exschawasion、EBeason、huangrenheluogu、Siteyava_145 等题解，根据 $n$ 的奇偶性分别构造不同的等差数列来满足条件。
- **基于奇数数列构造**：yeshubo_qwq 基于前 $n$ 个奇数数列进行调整；lsj2009 对奇数数列变换后通过调整首尾元素来构造。
- **二分查找构造**：cats142857 固定最大值为 $10^9$，二分查找最小值，再微调其他项使等式成立。

### 评分较高的题解
- **nullqtr_pwp（5星）**
    - **关键亮点**：思路清晰，通过钦定和值和差值，利用整体加值和调整剩余差值的方法，构造过程逻辑连贯，代码简洁易懂。
    - **核心代码**：
```cpp
#define F(i,a,b) for(int i=a;i<=(b);i++)
void solve(){
    int n=read();
    int sum=n*n*4,tot=0;
    F(i,1,n-1) a[i]=i;
    a[n]=1+2*n;
    F(i,1,n) tot+=a[i];
    int add=(sum-tot)/n;
    a[n-1]+=sum-tot-add*n;
    F(i,1,n) printf("%lld ",a[i]+add);
    printf("\n");
}
```
    - **核心实现思想**：先钦定序列和为 $4n^2$，差值为 $2n$，构造初始序列 $1,2,\cdots,n - 1,2n + 1$，计算其和与目标和的差值，通过整体加值逼近目标和，最后将剩余差值加到第 $n - 1$ 个数上。
- **Binary_Lee（4星）**
    - **关键亮点**：通过手算较小样例得出构造方法，并进行了详细的证明，逻辑严谨，代码简洁明了。
    - **核心代码**：
```cpp
void solve(){
    cin>>n;
    if(n&1){
        for(int i=n/2+2;i<=n;i++) cout<<i<<' ';
        for(int i=n+3;i<=n+n/2+3;i++) cout<<i<<' ';
        cout<<endl;
    }
    else{
        for(int i=n/2;i<n;i++) cout<<i<<' ';
        for(int i=n+1;i<=n+n/2;i++) cout<<i<<' ';
        cout<<endl;
    }
}
```
    - **核心实现思想**：根据 $n$ 的奇偶性分别构造不同的等差数列，奇数时构造 $\frac {n-1} 2+2,\frac {n-1} 2+3,\cdots,n,n+3,n+4,\cdots,n+\frac {n-1} 2+3$；偶数时构造 $\frac n 2,\frac n 2+1,\cdots,n-1,n+1,n+2,\cdots,n+\frac n 2$。
- **lsj2009（4星）**
    - **关键亮点**：思路巧妙，利用前 $n$ 个奇数之和的性质，通过对 $n$ 进行变换和调整首尾元素来构造满足条件的序列。
    - **核心代码**：
```cpp
// 构造
a_1=3n;
a_i=3n+2i-1(i!=1,n);
a_n=5n;
```
    - **核心实现思想**：注意到前 $n$ 个奇数之和为 $n^2$，将 $n$ 改为 $2n$ 后调整和值，再通过调整首尾元素使等式成立。

### 最优关键思路或技巧
- **钦定和值与差值**：通过钦定序列的和与差值，将问题转化为如何构造一个满足和值要求的序列，降低了构造的难度。
- **分奇偶讨论**：根据 $n$ 的奇偶性分别构造不同的等差数列，利用等差数列的性质方便计算和值与差值。
- **利用已有数列性质**：如利用前 $n$ 个奇数之和的性质，在此基础上进行调整和变换，简化构造过程。

### 可拓展之处
同类型题可能会有不同的等式约束条件，如最大值与最小值的某种函数关系等于序列元素的另一种函数关系。类似算法套路可以是先分析简单情况，找到规律后进行构造，或者钦定一些关键值，再通过调整其他元素来满足条件。

### 洛谷相似题目推荐
- [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：涉及连续自然数序列的构造和求和问题。
- [P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031)：需要对序列进行调整以满足特定条件，与本题的构造和调整思路有相似之处。
- [P1216 [USACO1.5][IOI1994]数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：在构造路径的过程中需要考虑元素之间的关系和总和的计算。

### 个人心得摘录与总结
- **liangbowen**：最初尝试 $x + 1, x + 2, \cdots, x + n$ 的填法无法完美填充，改为 $x, x + 2, x + 3, \cdots, x + n$ 的填法增加容错。在 $n$ 为奇数时发现答案差 $1$ 且无法填补，通过将数组元素翻倍并整体补值的方式解决。总结：在构造过程中可以尝试不同的填法增加容错，遇到问题时可以对数据进行变换来解决。
- **huangrenheluogu**：从 $n^2$ 开始构造连续 $n$ 个数的序列，发现偶数情况好处理，奇数情况需要不断调整最大最小值和总和。总结：对于构造问题，可以先从简单情况入手，逐步分析复杂情况，通过不断调整来满足条件。 

---
处理用时：39.50秒