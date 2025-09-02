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

### 题目内容中文重写
# 新年前夜

## 题目描述
由于格里沙（Grisha）去年表现良好，在新年前夜，圣诞老人（Ded Moroz）拜访了他，并给他带来了一个巨大的礼物袋！袋子里装有来自老面包店的 $n$ 颗美味糖果，每颗糖果都从 $1$ 到 $n$ 进行了标记，标记对应着它的美味程度。没有两颗糖果的美味程度是相同的。

糖果的选择直接影响着格里沙的幸福感。人们可能会认为他应该选择最美味的糖果——但事实并非如此，节日的魔法让事情变得不同。重要的不是普通的总和，而是美味程度的异或和！

一个整数序列 $a_{1},a_{2},\cdots,a_{m}$ 的异或和定义为其所有元素的按位异或：$a_{1}\oplus a_{2}\oplus\cdots\oplus a_{m}$，这里 $\oplus$ 表示按位异或运算；更多关于按位异或的信息可以在[这里](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)找到。

圣诞老人警告格里沙，他还有更多的房子要去拜访，所以格里沙最多只能从袋子里拿 $k$ 颗糖果。帮助格里沙确定他能获得的最大异或和（最大的异或和意味着最大的幸福感！）。

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

### 综合分析与结论
这些题解的核心思路都是先特判 $k = 1$ 的情况，此时答案就是 $n$；当 $k > 1$ 时，要尽量凑出二进制位全为 1 的数，这个数就是答案。

- **思路对比**：大部分题解思路一致，都是通过位运算来找到 $n$ 的最高位，然后构造出二进制全为 1 的数。部分题解给出了详细的证明，如 SoyTony 的题解。
- **算法要点**：主要运用了位运算，通过右移操作找到 $n$ 的最高位，再通过左移操作构造出所需的数。
- **解决难点**：关键在于理解当 $k > 1$ 时，为什么可以凑出二进制全为 1 的数作为最大异或和。

### 所选题解
- **作者：BB2655 (赞：6)  4星**
    - **关键亮点**：思路清晰，有详细的文字解释和代码实现，还给出了相关的数学原理。
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
核心实现思想：先特判 $k = 1$ 的情况，直接输出 $n$。对于 $k > 1$ 的情况，通过右移操作找到 $n$ 的最高位 $b$，然后计算 $2^b - 1$ 作为答案。

- **作者：SoyTony (赞：2)  4星**
    - **关键亮点**：给出了结论的详细证明，逻辑严谨。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef double db;
inline ll read(){
    ll x=0,w=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
    while(c<='9'&&c>='0'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}
    return x*w;
}
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
核心实现思想：先特判 $k = 1$ 的情况，直接输出 $n$。对于 $k > 1$ 的情况，通过不断左移找到大于 $n$ 的最小的 $2^cnt$，然后计算 $2^{cnt} - 1$ 作为答案。

- **作者：fisheep (赞：2)  4星**
    - **关键亮点**：代码简洁，通过找规律得出结论。
    - **核心代码**：
```cpp
#include<cstdio>
#include<cstring>  
using namespace std; 
inline long long read() {
    long long x=0,f=1;
    char ch=getchar();
    while(ch>'9'||ch<'0') {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
 
long long n,k,ans=1;  
int main(){  
    n=read(),k=read();
    if(k==1){
        printf("%lld\n",n);
    }else{
        while(n>>=1) ans<<=1;
        printf("%lld\n",(ans<<1)-1);  
    }
    return 0;  
}
```
核心实现思想：先特判 $k = 1$ 的情况，直接输出 $n$。对于 $k > 1$ 的情况，通过右移操作找到 $n$ 的最高位，然后计算 $2^{最高位 + 1} - 1$ 作为答案。

### 最优关键思路或技巧
- **特判思想**：对于 $k = 1$ 的特殊情况单独处理，简化逻辑。
- **位运算技巧**：利用右移操作找到 $n$ 的最高位，左移操作构造出二进制全为 1 的数。

### 可拓展之处
同类型题可能会改变选取数字的规则，或者改变运算方式（如改为其他位运算）。类似算法套路可以先分析特殊情况，再寻找一般规律，利用位运算的特性来解决问题。

### 推荐洛谷题目
- [P1888 三角函数](https://www.luogu.com.cn/problem/P1888)
- [P1009 阶乘之和](https://www.luogu.com.cn/problem/P1009)
- [P1017 进制转换](https://www.luogu.com.cn/problem/P1017)

### 个人心得摘录与总结
题解中未包含个人心得内容。

---
处理用时：44.92秒