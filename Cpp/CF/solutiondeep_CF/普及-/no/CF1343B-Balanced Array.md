# 题目信息

# Balanced Array

## 题目描述

You are given a positive integer $ n $ , it is guaranteed that $ n $ is even (i.e. divisible by $ 2 $ ).

You want to construct the array $ a $ of length $ n $ such that:

- The first $ \frac{n}{2} $ elements of $ a $ are even (divisible by $ 2 $ );
- the second $ \frac{n}{2} $ elements of $ a $ are odd (not divisible by $ 2 $ );
- all elements of $ a $ are distinct and positive;
- the sum of the first half equals to the sum of the second half ( $ \sum\limits_{i=1}^{\frac{n}{2}} a_i =         \sum\limits_{i=\frac{n}{2} + 1}^{n} a_i $ ).

If there are multiple answers, you can print any. It is not guaranteed that the answer exists.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
5
2
4
6
8
10```

### 输出

```
NO
YES
2 4 1 5
NO
YES
2 4 6 8 1 3 5 11
NO```

# AI分析结果

### 题目内容
# 平衡数组

## 题目描述
给定一个正整数 $n$，保证 $n$ 是偶数（即可被 2 整除）。

你想要构造一个长度为 $n$ 的数组 $a$，使得：
- $a$ 的前 $\frac{n}{2}$ 个元素是偶数（可被 2 整除）；
- $a$ 的后 $\frac{n}{2}$ 个元素是奇数（不可被 2 整除）；
- $a$ 的所有元素都不同且为正数；
- 前半部分的和等于后半部分的和（$\sum\limits_{i=1}^{\frac{n}{2}} a_i = \sum\limits_{i=\frac{n}{2} + 1}^{n} a_i$）。

如果有多个答案，你可以输出任何一个。不保证答案一定存在。

你必须回答 $t$ 个独立的测试用例。

## 样例 #1
### 输入
```
5
2
4
6
8
10
```
### 输出
```
NO
YES
2 4 1 5
NO
YES
2 4 6 8 1 3 5 11
NO
```
### 算法分类
数学

### 题解综合分析与结论
所有题解思路核心一致，均先判断无解情况，再构造满足条件的数组。
 - **无解判断**：多数题解指出当 $n\%4!=0$ （等价于 $\frac{n}{2}\%2 = 1$ ）时无解，原因是此时左右两边元素个数为奇数，左边偶数和为偶数，右边奇数和为奇数，两者不可能相等。
 - **数组构造**：当有解时（$n\%4 == 0$ ），前 $\frac{n}{2}$ 个元素构造为连续偶数 $2, 4, 6, \cdots, n$ ，后 $\frac{n}{2} - 1$ 个元素构造为连续奇数 $1, 3, 5, \cdots, n - 3$ ，最后一个奇数通过前半部分偶数和与后半部分前 $\frac{n}{2} - 1$ 个奇数和的差值来确定，以保证两部分和相等。

### 所选的题解
 - **作者：PersistentLife (5星)**
    - **关键亮点**：思路清晰，对无解情况给出两种证明方法，代码注释详细。
    - **个人心得**：无
    - **核心代码**：
```cpp
int n;
cin>>n;
if((n/2)%2==1)
{
    cout<<"NO"<<endl;
    continue;
}
cout<<"YES"<<endl;
for(int i=2,j=1;j<=n/2;j++,i+=2) cout<<i<<" ";
for(int i=1,j=1;j<=n/2;j++,i+=2)
{
    if(j==n/2) i+=(n/2);
    cout<<i<<" "; 
}
cout<<endl;
```
    - **代码简述**：先判断 $n/2$ 是否为奇数，若是则输出 `NO` ；否则输出 `YES` ，然后分别按规律输出前半部分偶数和后半部分奇数，最后一个奇数加上 $n/2$ 以平衡和。
 - **作者：zhzzhzzzz (4星)**
    - **关键亮点**：简洁明了，直接通过观察样例得出 $n\%4!=0$ 时无解，代码简洁。
    - **个人心得**：CF的AB题常可通过看样例找规律。
    - **核心代码**：
```cpp
int T;
scanf("%d", &T);
while (~--T)
{
    int n;
    scanf("%d", &n);
    if (n % 4!= 0)
    {
        puts("NO");
        continue;
    }
    else
    {
        puts("YES");
        for (int i = 1, x = 2; i <= n / 2; i++, x += 2)
            printf("%d ", x);
        for (int i = 1, x = 1; i <= n / 2 - 1; i++, x += 2)
            printf("%d ", x);
        printf("%d\n", n - 1 + n / 2);
    }
}
```
    - **代码简述**：循环读入 $n$ ，判断 $n\%4$ 是否为0 ，不为0输出 `NO` ，否则输出 `YES` ，并按规律输出前半部分偶数和后半部分奇数，最后一个奇数为 $n - 1 + n / 2$ 。
 - **作者：_jimmywang_ (4星)**
    - **关键亮点**：逻辑清晰，先说明无解情况及原因，再阐述有解时的构造思路，代码规范。
    - **个人心得**：无
    - **核心代码**：
```cpp
t=d;
while(t--){
    ll n=d;
    if(n%4!=0)cout<<"NO\n";
    else {
        ll sum=0;
        cout<<"YES\n";
        f(i,1,n/2)cout<<i*2<<" ";
        f(i,1,n/2-1)cout<<i*2-1<<" ";
        cout<<n-1+n/2<<endl;
    }
}
```
    - **代码简述**：读入 $t$ 个 $n$ ，判断 $n\%4$ ，若不为0输出 `NO` ，否则输出 `YES` ，分别输出前半部分偶数和后半部分奇数，最后一个奇数为 $n - 1 + n / 2$ 。

### 最优关键思路或技巧
通过数学分析得出无解的条件，利用等差数列的性质构造满足和相等的数组。在构造过程中，先分别构建前半部分偶数序列和后半部分大部分奇数序列，最后通过计算差值确定最后一个奇数，从而满足数组和相等的条件。

### 可拓展思路
同类型题通常围绕数论和数组构造，常见套路是先通过数学分析找出解存在的条件，再根据条件进行针对性构造。例如，改变奇偶性要求、和的条件或者数组元素的其他限制等。

### 洛谷相似题目推荐
 - [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)：涉及数论相关知识，对给定数进行质因数分解，与本题类似在于都需要对数字进行数学性质的分析。
 - [P1009 阶乘之和](https://www.luogu.com.cn/problem/P1009)：考查数学运算和高精度计算，和本题一样需要对数字进行特定规则下的运算处理。
 - [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：通过数学分析找出满足连续自然数和为给定值的情况，同样是利用数学原理解决数组或序列相关问题。 

---
处理用时：58.36秒