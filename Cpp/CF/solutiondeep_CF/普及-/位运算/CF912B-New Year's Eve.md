# 题目信息

# New Year's Eve

## 题目描述

Since Grisha behaved well last year, at New Year's Eve he was visited by Ded Moroz who brought an enormous bag of gifts with him! The bag contains $ n $ sweet candies from the good ol' bakery, each labeled from $ 1 $ to $ n $ corresponding to its tastiness. No two candies have the same tastiness.

The choice of candies has a direct effect on Grisha's happiness. One can assume that he should take the tastiest ones — but no, the holiday magic turns things upside down. It is the xor-sum of tastinesses that matters, not the ordinary sum!

A xor-sum of a sequence of integers $ a_{1},a_{2},...,a_{m} $ is defined as the bitwise XOR of all its elements: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912B/475d3a054d8c211f23a68d652dd85385e5ab9fc9.png), here ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912B/4298d47c0191af3c0a3103f431751061bc7e2362.png) denotes the bitwise XOR operation; more about bitwise XOR can be found [here.](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)

Ded Moroz warned Grisha he has more houses to visit, so Grisha can take no more than $ k $  candies from the bag. Help Grisha determine the largest xor-sum (largest xor-sum means maximum happiness!) he can obtain.

## 说明/提示

In the first sample case, one optimal answer is $ 1 $ , $ 2 $ and $ 4 $ , giving the xor-sum of $ 7 $ .

In the second sample case, one can, for example, take all six candies and obtain the xor-sum of $ 7 $ .

## 样例 #1

### 输入

```
4 3
```

### 输出

```
7
```

## 样例 #2

### 输入

```
6 6
```

### 输出

```
7
```

# AI分析结果

### 题目中文重写
# 新年前夜

## 题目描述
由于格里沙去年表现良好，在新年前夜，圣诞老人拜访了他，并给他带来了一个巨大的礼物袋！袋子里有 $n$ 颗来自老面包店的美味糖果，每颗糖果都从 $1$ 到 $n$ 进行了标记，标记对应着它的美味程度。没有两颗糖果的美味程度是相同的。

糖果的选择直接影响着格里沙的幸福感。人们可能会认为他应该选择最美味的糖果——但事实并非如此，节日的魔力让事情变得不同。重要的是美味程度的异或和，而不是普通的总和！

一个整数序列 $a_{1},a_{2},\cdots,a_{m}$ 的异或和定义为其所有元素的按位异或：$\bigoplus_{i = 1}^{m}a_{i}=a_{1}\oplus a_{2}\oplus\cdots\oplus a_{m}$，这里 $\oplus$ 表示按位异或运算；更多关于按位异或的信息可以在[这里](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)找到。

圣诞老人警告格里沙他还要去更多的房子，所以格里沙从袋子里拿的糖果不能超过 $k$ 颗。帮助格里沙确定他能获得的最大异或和（最大的异或和意味着最大的幸福感！）。

## 说明/提示
在第一个样例中，一个最优的选择是 $1$、$2$ 和 $4$，它们的异或和为 $7$。

在第二个样例中，例如，可以拿走所有六颗糖果，得到异或和为 $7$。

## 样例 #1
### 输入
```
4 3
```
### 输出
```
7
```

## 样例 #2
### 输入
```
6 6
```
### 输出
```
7
```

### 题解综合分析与结论
- **思路对比**：所有题解都先对 $k = 1$ 的情况进行特判，此时答案为 $n$。对于 $k > 1$ 的情况，核心思路都是将 $n$ 转换为二进制，找到其最高位，然后构造一个该最高位及以下所有位都为 $1$ 的数作为答案。
- **算法要点**：主要算法是通过位运算来处理，如右移 `>>` 操作确定 $n$ 的二进制位数，左移 `<<` 操作构造全为 $1$ 的二进制数。
- **解决难点**：难点在于理解为什么当 $k > 1$ 时，最大异或和是 $n$ 二进制最高位及以下全为 $1$ 的数。部分题解给出了证明，利用了异或运算的性质，即对于 $S = 2^b - 1$，任意 $a < S$，有 $a \oplus (S - a) = S$。

### 所选题解
- **作者：BB2655（5星）**
    - **关键亮点**：思路清晰，有详细的文字解释和代码注释，引用的文章证明了核心结论。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long int n,k;
    cin>>n>>k;
    if(k==1)  //特判
    {
        cout<<n;
        return 0;
    }
    long long int b=0;
    for(;n>>b;b++)  //b为(n)2的位数
    cout<<(1LL<<b)-1;  //1LL意为long long的1
    return 0;
}
```
核心实现思想：先特判 $k = 1$ 的情况，对于 $k > 1$，通过右移操作确定 $n$ 的二进制位数 $b$，然后构造 $2^b - 1$ 作为答案。

- **作者：SoyTony（4星）**
    - **关键亮点**：给出了结论的详细证明，代码规范，有自定义的快速读入和快速幂函数。
    - **核心代码**：
```cpp
ll n,k;
inline ll q_pow(ll x,ll p){
    ll ans=1;
    while(p){
        if(p&1){
            ans*=x;
        }
        x*=x;
        p>>=1;
    }
    return ans;
}
int main(){
    n=read(),k=read();
    if(k==1) printf("%lld\n",n);
    else{
        ll cnt=0,num=1;
        while(1){
            num<<=1;
            cnt++;
            if(num>n){
                break;
            }
        }
        printf("%lld\n",q_pow(2,cnt)-1);
    }
    return 0;
}
```
核心实现思想：同样先特判 $k = 1$ 的情况，对于 $k > 1$，通过左移操作找到大于 $n$ 的最小的 $2^cnt$，然后计算 $2^cnt - 1$ 作为答案。

- **作者：Daniel_yao（4星）**
    - **关键亮点**：思路简洁明了，代码简洁易懂，时间复杂度分析清晰。
    - **核心代码**：
```cpp
long long n, k, num = 1;
int main(){
    cin >> n >> k;
    if(k == 1){
        cout << n << endl;
    } else {
        while(n){//分解
            num = num << 1;
            n = n >> 1;
        }
        cout << (num * 1ll) - 1 << endl;//取最大值
    }
    return 0;
}
```
核心实现思想：先特判 $k = 1$ 的情况，对于 $k > 1$，通过右移操作将 $n$ 不断缩小，同时左移 $num$，最后计算 $num - 1$ 作为答案。

### 最优关键思路或技巧
- **位运算**：利用右移 `>>` 确定二进制位数，左移 `<<` 构造全为 $1$ 的二进制数，避免了复杂的数学计算。
- **分类讨论**：先特判 $k = 1$ 的情况，简化问题处理。

### 可拓展之处
同类型题可能会改变选择数字的范围或条件，或者改变运算规则（如改为其他位运算）。类似算法套路是先分析特殊情况，再通过位运算处理二进制相关问题。

### 推荐洛谷题目
- [P1837 连通块](https://www.luogu.com.cn/problem/P1837)：涉及位运算和状态压缩。
- [P2114 [NOI2014]起床困难综合症](https://www.luogu.com.cn/problem/P2114)：需要运用位运算的性质来解决问题。
- [P3811 乘法逆元](https://www.luogu.com.cn/problem/P3811)：虽然主要考察逆元，但部分解法会用到位运算优化。

### 个人心得摘录与总结
无明显个人心得内容。 

---
处理用时：36.99秒