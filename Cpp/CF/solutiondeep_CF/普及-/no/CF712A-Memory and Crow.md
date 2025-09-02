# 题目信息

# Memory and Crow

## 题目描述

There are $ n $ integers $ b_{1},b_{2},...,b_{n} $ written in a row. For all $ i $ from $ 1 $ to $ n $ , values $ a_{i} $ are defined by the crows performing the following procedure:

- The crow sets $ a_{i} $ initially $ 0 $ .
- The crow then adds $ b_{i} $ to $ a_{i} $ , subtracts $ b_{i+1} $ , adds the $ b_{i+2} $ number, and so on until the $ n $ 'th number. Thus, $ a_{i}=b_{i}-b_{i+1}+b_{i+2}-b_{i+3}... $ .

Memory gives you the values $ a_{1},a_{2},...,a_{n} $ , and he now wants you to find the initial numbers $ b_{1},b_{2},...,b_{n} $ written in the row? Can you do it?

## 说明/提示

In the first sample test, the crows report the numbers $ 6 $ , $ -4 $ , $ 8 $ , $ -2 $ , and $ 3 $ when he starts at indices $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ and $ 5 $ respectively. It is easy to check that the sequence $ 2 $ $ 4 $ $ 6 $ $ 1 $ $ 3 $ satisfies the reports. For example, $ 6=2-4+6-1+3 $ , and $ -4=4-6+1-3 $ .

In the second sample test, the sequence $ 1 $ , $ -3 $ , $ 4 $ , $ 11 $ , $ 6 $ satisfies the reports. For example, $ 5=11-6 $ and $ 6=6 $ .

## 样例 #1

### 输入

```
5
6 -4 8 -2 3
```

### 输出

```
2 4 6 1 3 
```

## 样例 #2

### 输入

```
5
3 -2 -1 5 6
```

### 输出

```
1 -3 4 11 6 
```

# AI分析结果

### 题目翻译
# 记忆与乌鸦

## 题目描述
有 $ n $ 个整数 $ b_{1},b_{2},\cdots,b_{n} $ 排成一行。对于从 $ 1 $ 到 $ n $ 的所有 $ i $，乌鸦通过执行以下步骤来定义 $ a_{i} $ 的值：
- 乌鸦先将 $ a_{i} $ 初始化为 $ 0 $。
- 然后乌鸦将 $ b_{i} $ 加到 $ a_{i} $ 上，减去 $ b_{i + 1} $，加上 $ b_{i + 2} $，依此类推，直到第 $ n $ 个数。因此，$ a_{i}=b_{i}-b_{i + 1}+b_{i + 2}-b_{i + 3}\cdots $。

Memory 给了你 $ a_{1},a_{2},\cdots,a_{n} $ 的值，现在他希望你找出最初写在这一行中的数字 $ b_{1},b_{2},\cdots,b_{n} $。你能做到吗？

## 说明/提示
在第一个样例测试中，当乌鸦分别从索引 $ 1 $、$ 2 $、$ 3 $、$ 4 $ 和 $ 5 $ 开始时，报告的数字分别是 $ 6 $、$ -4 $、$ 8 $、$ -2 $ 和 $ 3 $。很容易验证序列 $ 2 $ $ 4 $ $ 6 $ $ 1 $ $ 3 $ 满足这些报告。例如，$ 6 = 2 - 4 + 6 - 1 + 3 $，$ -4 = 4 - 6 + 1 - 3 $。

在第二个样例测试中，序列 $ 1 $、$ -3 $、$ 4 $、$ 11 $、$ 6 $ 满足这些报告。例如，$ 5 = 11 - 6 $ 且 $ 6 = 6 $。

## 样例 #1
### 输入
```
5
6 -4 8 -2 3
```
### 输出
```
2 4 6 1 3 
```

## 样例 #2
### 输入
```
5
3 -2 -1 5 6
```
### 输出
```
1 -3 4 11 6 
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是通过对样例进行分析，找出 $ b[i] $ 与 $ a[i] $ 之间的规律，即 $ b[i]=a[i]+a[i + 1] $（特别地，$ b[n]=a[n] $ ，由于全局变量默认初始化为 $ 0 $，所以 $ a[n]+a[n + 1]=a[n] $ 无需特判）。各题解的算法要点都是根据此规律，通过循环进行计算和输出。解决的难点在于如何从题目给定的条件中推导出这个规律。

### 题解评分与选择
- **k3v1n070828（5星）**：思路清晰，通过详细的样例分析推导出规律，并且对代码中未特判 $ b[n]=a[n] $ 的原因进行了说明，代码简洁易懂。
- **_Felix（4星）**：思路简洁，通过变量更新的方式实现了规律的应用，代码逻辑清晰。
- **lihanyang（4星）**：使用了 `long long` 类型，避免了可能的整数溢出问题，代码结构清晰。

### 重点代码及核心实现思想
#### k3v1n070828
```cpp
#include<cstdio>
using namespace std;
int n,a[100010];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
        printf("%d ",a[i]+a[i+1]);
    return 0;
}
```
核心实现思想：先输入数组长度和数组元素，然后根据规律 $ b[i]=a[i]+a[i + 1] $ 进行输出。

#### _Felix
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    int k=0,x;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        if(i!=1)
            cout<<x+k<<" ";
        k=x;
    }
    cout<<x<<endl;
    return 0;
}
```
核心实现思想：通过变量 $ k $ 记录前一个 $ a $ 值，$ x $ 记录当前 $ a $ 值，根据规律 $ b[i]=a[i]+a[i - 1] $ 进行输出。

#### lihanyang
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    ll a[1000005];
    ll b[1000005];
    ll t;
    cin>>t;
    for(ll i=1;i<=t;i++)
    {
        cin>>a[i]; 
    }
    for(ll i=t;i>=1;i--)
    {
        b[i]=a[i]+a[i+1];
    }
    for(ll i=1;i<=t;i++)
    {
        cout<<b[i]<<" ";
    }
}
```
核心实现思想：先输入数组元素，然后根据规律 $ b[i]=a[i]+a[i + 1] $ 计算 $ b $ 数组，最后输出 $ b $ 数组。

### 最优关键思路或技巧
- 通过对样例进行详细分析，找出数字之间的规律，从而将复杂的问题简化。
- 利用全局变量默认初始化为 $ 0 $ 的特性，避免对 $ b[n]=a[n] $ 进行特判。

### 拓展思路
同类型题可能会给出更复杂的数列关系，需要通过更多的数学推导来找出规律。类似算法套路是先从简单的样例入手，通过列举和计算找出规律，再根据规律进行代码实现。

### 推荐洛谷题目
- P1003 铺地毯
- P1008 三连击
- P1014 Cantor表

### 个人心得摘录与总结
- **k3v1n070828**：提到很多同学可能会奇怪没有判断 $ b[n]=a[n] $，并普及了全局变量默认赋值为 $ 0 $ 的特性，提醒大家在编程时要注意变量的默认值。 

---
处理用时：40.86秒