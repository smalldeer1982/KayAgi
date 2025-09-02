# 题目信息

# Beautiful Divisors

## 题目描述

Recently Luba learned about a special kind of numbers that she calls beautiful numbers. The number is called beautiful iff its binary representation consists of $ k+1 $ consecutive ones, and then $ k $ consecutive zeroes.

Some examples of beautiful numbers:

- $ 1_{2} $ ( $ 1_{10} $ );
- $ 110_{2} $ ( $ 6_{10} $ );
- $ 1111000_{2} $ ( $ 120_{10} $ );
- $ 111110000_{2} $ ( $ 496_{10} $ ).

More formally, the number is beautiful iff there exists some positive integer $ k $ such that the number is equal to $ (2^{k}-1)*(2^{k-1}) $ .

Luba has got an integer number $ n $ , and she wants to find its greatest beautiful divisor. Help her to find it!

## 样例 #1

### 输入

```
3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
992
```

### 输出

```
496
```

# AI分析结果

### 题目翻译
## 美丽的因数

### 题目描述
最近，卢巴了解到一种她称之为美丽数字的特殊数字。当一个数字的二进制表示由 $k + 1$ 个连续的 $1$ ，紧接着 $k$ 个连续的 $0$ 组成时，这个数字就是美丽的。

一些美丽数字的例子：
- $1_{2}$（十进制为 $1_{10}$ ）；
- $110_{2}$（十进制为 $6_{10}$ ）；
- $1111000_{2}$（十进制为 $120_{10}$ ）；
- $111110000_{2}$（十进制为 $496_{10}$ ）。

更正式地说，如果存在某个正整数 $k$ ，使得该数字等于 $(2^{k}-1)\times(2^{k - 1})$ ，那么这个数字就是美丽的。

卢巴得到了一个整数 $n$ ，她想找到 $n$ 的最大美丽因数。请帮助她找到这个因数！

### 样例 #1
#### 输入
```
3
```
#### 输出
```
1
```

### 样例 #2
#### 输入
```
992
```
#### 输出
```
496
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是围绕找出满足 $(2^{k}-1)\times(2^{k - 1})$ 形式的数，并判断其是否为 $n$ 的因数，从中找出最大的。各题解的差异主要体现在实现方式上，有的通过直接计算，有的通过打表，还有的使用位运算或递推。

### 所选题解
- **Yizhixiaoyun（4星）**
    - **关键亮点**：思路清晰，直接枚举所有满足条件的数并判断是否为因数，代码简洁易懂。
    - **核心代码**：
```cpp
#include<iostream>
#include<cmath>
using namespace std;
int n,s,k=1;
int ans;
int main(){
    cin>>n;
    while((pow(2,k)-1)*(pow(2,k-1))<=n){
        s=(pow(2,k)-1)*(pow(2,k-1));
        if(n%s==0) ans=(pow(2,k)-1)*(pow(2,k-1));
        k++; 
    }
    cout<<ans;
}
```
核心实现思想：通过循环不断计算满足 $(2^{k}-1)\times(2^{k - 1})$ 形式的数，判断其是否小于等于 $n$ 且为 $n$ 的因数，若是则更新答案。

- **_QrSn_（4星）**
    - **关键亮点**：利用数据范围较小的特点，直接打表存储满足条件的数，从大到小枚举，保证找到的是最大因数，代码简洁高效。
    - **核心代码**：
```cpp
#include<iostream>
using namespace std;
int a[9]={1,6,28,120,496,2016,8128,32640};
int n;
int main() {
    cin>>n;
    for(int i=8-1;i>=0;i--){
        if(n%a[i]==0){
            cout<<a[i];
            break;
        }
    }
    return 0;
}
```
核心实现思想：将满足条件的数存储在数组中，从数组末尾开始遍历，若该数是 $n$ 的因数，则输出并退出循环。

- **_caiji_（4星）**
    - **关键亮点**：采用递推的方式构造满足条件的数，避免了重复计算，代码简洁且具有创新性。
    - **核心代码**：
```cpp
#include <cstdio>
using namespace std;
int n,ans;
int main(){
    scanf("%d",&n);
    for(int i=1,j=1;i<=n;j++){
        if(n%i==0&&i>ans) ans=i;
        i=(i<<2)|(1<<j);
    }
    printf("%d",ans);
    return 0;
}
```
核心实现思想：通过递推公式 $a_i=\begin{cases}1&i = 1\\a_{i - 1}<<2|(1<<(i - 1))&i > 1\end{cases}$ 构造满足条件的数，同时判断其是否为 $n$ 的因数并更新最大答案。

### 最优关键思路或技巧
- 利用数据范围较小的特点，打表存储满足条件的数，从大到小枚举，可快速找到最大因数。
- 使用位运算代替幂运算，提高计算效率，如 `1<<k` 表示 $2^k$ 。
- 递推构造满足条件的数，避免重复计算。

### 拓展思路
同类型题可能会改变数据范围或美丽数字的定义，可根据具体情况调整算法。类似算法套路可用于解决其他因数相关问题，如找出满足特定条件的最小因数、因数个数等。

### 推荐题目
- [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
- [P1072 Hankson的趣味题](https://www.luogu.com.cn/problem/P1072)
- [P2613 有理数取余](https://www.luogu.com.cn/problem/P2613)

### 个人心得摘录与总结
- **yzy041616**：提到位运算符号优先级比加减乘除高，写代码时要注意加括号，避免出错。总结：在使用位运算时，一定要注意运算符的优先级，必要时添加括号保证运算顺序正确。 

---
处理用时：37.73秒