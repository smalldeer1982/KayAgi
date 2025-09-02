# 题目信息

# Mahmoud and Ehab and the xor

## 题目描述

Mahmoud and Ehab are on the third stage of their adventures now. As you know, Dr. Evil likes sets. This time he won't show them any set from his large collection, but will ask them to create a new set to replenish his beautiful collection of sets.

Dr. Evil has his favorite evil integer $ x $ . He asks Mahmoud and Ehab to find a set of $ n $ distinct non-negative integers such the bitwise-xor sum of the integers in it is exactly $ x $ . Dr. Evil doesn't like big numbers, so any number in the set shouldn't be greater than $ 10^{6} $ .

## 说明/提示

You can read more about the bitwise-xor operation here: [https://en.wikipedia.org/wiki/Bitwise\_operation#XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)

For the first sample ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF862C/180bb5f2e74c80f6ed89e63195bfe3b6f1ffefbe.png).

For the second sample ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF862C/f06e00f5587f7a7d8f6a75ce9483c045f97c5f8a.png).

## 样例 #1

### 输入

```
5 5
```

### 输出

```
YES
1 2 4 5 7```

## 样例 #2

### 输入

```
3 6
```

### 输出

```
YES
1 2 5```

# AI分析结果

### 题目内容
# Mahmoud和Ehab与异或运算

## 题目描述
Mahmoud和Ehab现在处于他们冒险的第三阶段。如你所知，邪恶博士喜欢集合。这次，他不会向他们展示他大量收藏中的任何集合，而是会要求他们创建一个新集合，以充实他那精美的集合收藏。

邪恶博士有他最喜欢的邪恶整数$x$。他要求Mahmoud和Ehab找到一个由$n$个不同的非负整数组成的集合，使得该集合中整数的按位异或和恰好为$x$。邪恶博士不喜欢大数字，所以集合中的任何数字都不应大于$10^{6}$。

## 说明/提示
你可以在此处阅读更多关于按位异或运算的内容：[https://en.wikipedia.org/wiki/Bitwise_operation#XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)

对于第一个样例：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF862C/180bb5f2e74c80f6ed89e63195bfe3b6f1ffefbe.png)

对于第二个样例：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF862C/f06e00f5587f7a7d8f6a75ce9483c045f97c5f8a.png)

## 样例 #1
### 输入
```
5 5
```
### 输出
```
YES
1 2 4 5 7
```
## 样例 #2
### 输入
```
3 6
```
### 输出
```
YES
1 2 5
```
### 算法分类
构造
### 综合分析与结论
这些题解的共同目标是构造出满足条件的$n$个互不相等且不大于$10^6$的非负整数，使它们的异或和为$x$。不同题解的构造思路各有特点：
 - **Error_Eric**：先考虑输出$1$到$n - 2$或$1$到$n - 3$的数，通过异或性质列出方程求解剩下的数。难点在于处理可能出现的数字相等情况，通过分情况讨论解决。
 - **Luzhuoyuan**：利用$(4i)\oplus(4i + 1)\oplus(4i + 2)\oplus(4i + 3)=0$以及$1\oplus 2\oplus 3 = 0$的性质，根据$n\bmod 4$的不同情况进行构造，同样要注意特殊情况如$x = 0,n\bmod 4 = 2$ 。
 - **wmrqwq**：先处理$n = 1$和$n = 2$的情况，之后通过随机化构造数字，最后根据异或和条件确定最后一个数字，利用CF的评测机制应对可能出现的重复数字问题。
 - **copper_ingot**：用$1$到$n - 3$的整数构造前面部分，设其异或和为$ans$，通过特定取值$k = 2 ^ {17}$，$j = 2 ^ {18}$构造后三个数使异或和满足要求，同时处理$n = 2$的特殊情况。
 - **xiaoming_king**：先按顺序添加数字构造数组，计算异或和，再根据与$x$的异或结果调整数组元素，处理可能出现的重复问题。

整体来看，各题解都围绕异或运算性质进行构造，区别在于构造的方式和对特殊情况的处理。

### 所选的题解
 - **Error_Eric（4星）**
    - **关键亮点**：基于异或运算性质进行逐步推导构造，思路清晰，对特殊情况（$sum = x$时数字相等）有明确的处理方法。
    - **个人心得**：发现最初构造会WA，是因为$sum = x$时$a = b$非法，从而修改构造方式。
    - **核心代码**：
```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;
int n,x,sum=0,u=(1<<18);
int main(){
    scanf("%d%d",&n,&x);
    if(n==2 and x==0)return puts("NO"),0;
    puts("YES");
    switch(n){
        case 1:printf("%d\n",x);break;
        case 2:printf("%d 0\n",x);break;
        default:
            for(int i=1;i<=n-3;i++)printf("%d ",i),sum=sum ^ i;
            if(x==sum)printf("%d %d %d\n",u,u<<1,u+(u<<1));
            else printf("%d %d %d\n",0,u,u ^ x ^ sum);
            break;
    }
    return 0;
}
```
核心实现思想：先特判$n = 1$和$n = 2$的情况。对于其他情况，先输出$1$到$n - 3$的数并计算其异或和$sum$，根据$sum$与$x$是否相等，分别输出不同的三个数，使整体异或和为$x$。
 - **Luzhuoyuan（4星）**
    - **关键亮点**：利用$(4i)\oplus(4i + 1)\oplus(4i + 2)\oplus(4i + 3)=0$等性质，根据$n\bmod 4$分类构造，逻辑严谨，对特殊情况考虑全面。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)((x).size())
using namespace std;
const int N=1e6+5;
int n,x,fl[N];
inline void w(int x){fl[x]=true,cout<<x<<' ',n--;}
signed main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>n>>x;if(n==2&&x==0)cout<<"NO\n",exit(0);
    cout<<"YES\n";
    if(x==0&&(n&3)==2)w(1),w(2),w(3),w(4),w(8),w(12);
    else{
        if((n&3)==0)w(1<<18),w(2<<18),w(3<<18),w(x);
        if((n&3)==1)w(x);
        if((n&3)==2)w(x|(1<<18)),w(1<<18);
        if((n&3)==3)w(x|(1<<18)),w(x|(2<<18)),w(x|(3<<18));
    }
    for(int i=0;n;i+=4)
        if(!fl[i]&&!fl[i+1]&&!fl[i+2]&&!fl[i+3])
            n-=4,cout<<i<<' '<<i+1<<' '<<i+2<<' '<<i+3<<' ';
    cout<<'\n';
}
```
核心实现思想：先处理$n = 2$且$x = 0$的无解情况。然后根据$n\bmod 4$的不同值，先构造部分数字，再通过循环补充剩余数字，保证所有数字不同且异或和为$x$。
 - **copper_ingot（4星）**
    - **关键亮点**：通过特定取值$k$和$j$，巧妙构造后三个数满足异或和要求，整体构造简洁明了，对$n = 2$的特殊情况处理得当。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, x, ans = 0;
int main(){
    scanf("%d%d", &n, &x);
    if (n == 2 &&!x){puts("NO"); return 0;}
    puts("YES");
    if (n == 1) printf("%d", x);
    else if (n == 2) printf("0 %d", x);
    else{
        for (int i = 1; i <= n - 3; i++){printf("%d ", i); ans ^= i;}
        int k = 131072, j = 262144;
        printf("%d %d %d", x ^ k, k ^ j, j ^ ans);
    }
    return 0;
}
```
核心实现思想：先特判$n = 1$和$n = 2$的情况。对于其他情况，先输出$1$到$n - 3$的数并计算其异或和$ans$，通过特定的$k$和$j$值构造后三个数，使得这$n$个数的异或和为$x$。

### 最优关键思路或技巧
利用异或运算的交换律、结合律等性质进行构造是核心思路。如通过先确定部分数字的异或和，再根据目标异或和$x$来计算剩余数字；或者利用一些固定数字组合的异或和特性（如$(4i)\oplus(4i + 1)\oplus(4i + 2)\oplus(4i + 3)=0$），结合对特殊情况（如$n = 2$且$x = 0$）的处理，实现满足条件的构造。

### 同类型题或类似算法套路拓展
此类题目通常围绕特定运算（如本题的异或运算）的性质进行构造。常见套路是先分析运算性质，找到一些固定的运算结果组合，再根据题目给定的条件（如数字个数、取值范围、目标运算结果等）进行分类讨论和构造。

### 洛谷相似题目推荐
 - [P1100 高低位交换](https://www.luogu.com.cn/problem/P1100)：考察位运算操作，与本题对异或运算的运用类似，需掌握位运算基本性质。
 - [P1514 引水入城](https://www.luogu.com.cn/problem/P1514)：涉及到构造满足一定条件的方案，与本题构造满足异或和条件的数字集合思路类似，都需要根据题目条件进行合理构造。
 - [P2678 [NOIP2015 提高组] 跳石头](https://www.luogu.com.cn/problem/P2678)：虽然主要是二分查找，但也需要构造满足条件的方案，与本题在构造思路上有相通之处，都要考虑如何满足题目给定的限制条件。 

---
处理用时：78.70秒