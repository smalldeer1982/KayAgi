# 题目信息

# Accounting

## 题目描述

A long time ago in some far country lived king Copa. After the recent king's reform, he got so large powers that started to keep the books by himself.

The total income $ A $ of his kingdom during $ 0 $ -th year is known, as well as the total income $ B $ during $ n $ -th year (these numbers can be negative — it means that there was a loss in the correspondent year).

King wants to show financial stability. To do this, he needs to find common coefficient $ X $ — the coefficient of income growth during one year. This coefficient should satisfy the equation:

 $ A·X^{n}=B. $ Surely, the king is not going to do this job by himself, and demands you to find such number $ X $ .

It is necessary to point out that the fractional numbers are not used in kingdom's economy. That's why all input numbers as well as coefficient $ X $ must be integers. The number $ X $ may be zero or negative.

## 样例 #1

### 输入

```
2 18 2
```

### 输出

```
3```

## 样例 #2

### 输入

```
-1 8 3
```

### 输出

```
-2```

## 样例 #3

### 输入

```
0 0 10
```

### 输出

```
5```

## 样例 #4

### 输入

```
1 16 5
```

### 输出

```
No solution```

# AI分析结果

### 题目内容
# 记账

## 题目描述
很久很久以前，在某个遥远的国度，住着国王科帕。在最近的国王改革之后，他获得了极大的权力，以至于开始亲自记账。

已知他的王国在第0年的总收入为A，在第n年的总收入为B（这些数字可能为负，表示相应年份出现了亏损）。

国王想要展示财政稳定性。为此，他需要找到一个共同系数X——即一年的收入增长系数。这个系数应满足方程：$A·X^{n}=B$ 。当然，国王不会亲自做这项工作，而是要求你找出这样的数字X。

需要指出的是，在这个王国的经济中不使用分数。因此，所有输入数字以及系数X都必须是整数。数字X可以为零或负数。

## 样例 #1
### 输入
```
2 18 2
```
### 输出
```
3
```

## 样例 #2
### 输入
```
-1 8 3
```
### 输出
```
-2
```

## 样例 #3
### 输入
```
0 0 10
```
### 输出
```
5
```

## 样例 #4
### 输入
```
1 16 5
```
### 输出
```
No solution
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路均是利用题目中\(a\)、\(b\)绝对值范围较小（\(\vert a\vert,\vert b\vert\leq1000\)）的条件，通过枚举\(x\)在\(-\vert b\vert\)到\(\vert b\vert\)范围内的所有整数值，代入方程\(a\times x^n = b\)进行验证，找到满足方程的\(x\)值。其中一些题解还提到了特殊情况的处理，如\(a = 0\)且\(b = 0\)时\(x\)可取任意值（题解中多取1）；\(a = 0\)且\(b\neq0\)时无解；\(a\neq0\)且\(b = 0\)时\(x\)只能取0 。各题解思路相近，主要区别在于对特殊情况的处理以及代码实现细节。

### 所选的题解
 - **作者：tryrtj (5星)**
    - **关键亮点**：详细分析了题目中的坑点，对\(a\)、\(b\)不同取值组合的特殊情况进行了全面讨论，并在代码中准确实现，代码可读性较高。
    - **个人心得**：提交9次才通过，强调了0这个值在题目中的多种特殊情况容易出错，如\(a = 0\)，\(b = 0\)；\(a = 0\)，\(b≠0\)；\(a≠0\)，\(b = 0\) 这几种情况。
 - **作者：qzhwmjb (4星)**
    - **关键亮点**：指出题目中需要注意\(a\)、\(b\)的绝对值处理，以及多个解输出任意一个的要点，并介绍了解题过程中使用的\(abs\)和\(pow\)函数。
 - **作者：long_long (4星)**
    - **关键亮点**：简洁明了地阐述了题目大意和思路，对特殊情况的判断和处理在代码中体现清晰。

### 重点代码
 - **作者：tryrtj**
核心实现思想：先对\(a = 0\)且\(b = 0\) 以及\(a≠0\)且\(b = 0\) 的特殊情况直接输出结果并结束程序。对于其他情况，在\(-\vert b\vert\)到\(\vert b\vert\)范围内枚举\(x\)，通过循环计算\(x^n\)的值并与\(a\)相乘判断是否等于\(b\) 。
```cpp
#include<iostream>
#include<cmath>
using namespace std;
int main(){
    int a,b,n;
    cin>>a>>b>>n;
    if(a==0&&b==0){//第一种（此处省略第二种，因为通过枚举可以排除这种情况）
        cout<<1;
        return 0;
    }
    if(a!=0&&b==0){//第三种
        cout<<0;
        return 0;
    }
    for(int i=-abs(b);i<=abs(b);i++){
        if(i!=0){//记得加上i≠0，不信的话试试1 1 1这组数据
        int r=1;//初始为1，也是上面要求≠0的原因
        for(int j=0;j<n;j++){
            r*=i;//求积
        }
        if(r*a==b){//判断
            cout<<i<<endl;
            return 0;//直接结束
        }
        }
    }
    cout<<"No solution"<<endl;//输出否定
    return 0;
}
```
 - **作者：qzhwmjb**
核心实现思想：在\(-\vert b\vert\)到\(\vert b\vert\)范围内枚举\(x\)，利用\(pow\)函数计算\(x^n\)，判断\(a\times x^n\)是否等于\(b\) 。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,n,i;
int main() {
    cin>>a>>b>>n;
    for(i=-abs(b);i<=abs(b);i++){
        if(a*pow(i,n)==b){
            cout<<i<<endl;
            return 0;
        }
    }
    cout<<"No solution"<<endl;
    return 0;
}
```
 - **作者：long_long**
核心实现思想：与qzhwmjb类似，同样是先判断特殊情况，再在\(-\vert b\vert\)到\(\vert b\vert\)范围内枚举\(x\)，使用\(pow\)函数判断\(a\times x^n\)是否等于\(b\) 。
```cpp
#include<cstdio>
#include<cmath>
int main(){
    int a,b,n;
    scanf("%d%d%d",&a,&b,&n);
    if(a==0&&b==0){ printf("1\n");return 0;}
    if(a!=0&&b==0){ printf("0\n");return 0;}
    for(int i=-abs(b);i<=abs(b);i++) if(a*pow(i,n)==b){ printf("%d\n",i);return 0;}
    printf("No solution\n");
    return 0;
}
```

### 最优关键思路或技巧
利用题目给定的\(a\)、\(b\)取值范围限制，采用枚举法遍历可能的解空间。同时，对\(a\)、\(b\)为0的特殊情况进行单独处理，避免在枚举过程中出现错误结果，提高代码的准确性和鲁棒性。

### 拓展思路
同类型题目通常会给出一个方程，方程中含有一个或多个未知数，同时会对未知数及其他参数的取值范围有所限制，可利用这些限制条件通过枚举法求解。类似套路如在一些简单的数论问题中，给定关于整数的等式关系，结合整数范围进行枚举尝试。

### 洛谷推荐题目
 - [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：通过枚举菜品组合解决点菜问题，与本题枚举思路类似。
 - [P1469 找筷子](https://www.luogu.com.cn/problem/P1469)：在一定范围内枚举寻找满足条件的筷子数量，考察枚举思想。
 - [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：通过枚举不同包装铅笔的购买数量来找到最优方案，涉及枚举与简单的数学计算。 

---
处理用时：67.41秒