# 题目信息

# Taxes

## 题目描述

Mr. Funt now lives in a country with a very specific tax laws. The total income of mr. Funt during this year is equal to $ n $ ( $ n>=2 $ ) burles and the amount of tax he has to pay is calculated as the maximum divisor of $ n $ (not equal to $ n $ , of course). For example, if $ n=6 $ then Funt has to pay $ 3 $ burles, while for $ n=25 $ he needs to pay $ 5 $ and if $ n=2 $ he pays only $ 1 $ burle.

As mr. Funt is a very opportunistic person he wants to cheat a bit. In particular, he wants to split the initial $ n $ in several parts $ n_{1}+n_{2}+...+n_{k}=n $ (here $ k $ is arbitrary, even $ k=1 $ is allowed) and pay the taxes for each part separately. He can't make some part equal to $ 1 $ because it will reveal him. So, the condition $ n_{i}>=2 $ should hold for all $ i $ from $ 1 $ to $ k $ .

Ostap Bender wonders, how many money Funt has to pay (i.e. minimal) if he chooses and optimal way to split $ n $ in parts.

## 样例 #1

### 输入

```
4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
27
```

### 输出

```
3
```

# AI分析结果

### 题目内容重写

#### 题目描述

Funt先生现在住在一个税收法律非常特殊的国家。Funt先生今年的总收入为$n$（$n \geq 2$） burles，他需要缴纳的税款计算为$n$的最大除数（当然，不包括$n$本身）。例如，如果$n=6$，那么Funt需要支付$3$ burles，而如果$n=25$，他需要支付$5$ burles，如果$n=2$，他只需支付$1$ burle。

由于Funt先生是一个非常投机取巧的人，他想要稍微作弊一下。具体来说，他想要将初始的$n$分成几个部分$n_{1}+n_{2}+...+n_{k}=n$（这里的$k$是任意的，甚至$k=1$也是允许的），并分别对每个部分缴纳税款。他不能将某个部分设为$1$，因为这会导致他被发现。因此，对于所有$i$从$1$到$k$，条件$n_{i} \geq 2$必须成立。

Ostap Bender想知道，如果Funt选择将$n$分成部分的最优方式，他需要支付的最少税款是多少。

#### 样例 #1

##### 输入

```
4
```

##### 输出

```
2
```

#### 样例 #2

##### 输入

```
27
```

##### 输出

```
3
```

### 题解分析与结论

本题的核心在于如何将$n$分成若干部分，使得每部分的税款之和最小。根据题解，大多数解法都基于**哥德巴赫猜想**，即任何大于2的偶数都可以表示为两个质数的和，而任何大于5的奇数都可以表示为三个质数的和。因此，最优解通常为1、2或3。

### 高星题解推荐

#### 题解1：作者：yyyer (赞：38)  
**星级：5星**  
**关键亮点：**  
- 简洁明了地利用了哥德巴赫猜想，将问题分为$n$为质数、偶数、奇数三种情况。
- 代码清晰，逻辑严谨，直接判断$n$是否为质数，以及$n-2$是否为质数，从而得出最优解。

**核心代码：**
```cpp
bool isprime(int n) {
    if(n<2)return false;
    for(int i=2;i*i<=n;i++) if(n%i==0)return false;
    return true;
}
int main() {
    int n;
    cin>>n;
    if(isprime(n)) cout<<"1"<<endl; //n自身为质数
    else if(n%2==0) cout<<"2"<<endl; //n是偶数
    else if(isprime(n-2)) cout<<"2"<<endl; //n-2是质数
    else cout<<"3"<<endl; //都不满足，直接输出3
    return 0;
}
```

#### 题解2：作者：lgnotus (赞：7)  
**星级：4星**  
**关键亮点：**  
- 详细解释了哥德巴赫猜想在本题中的应用，特别是对奇数的处理。
- 代码简洁，逻辑清晰，直接判断$n$是否为质数，以及$n-2$是否为质数。

**核心代码：**
```cpp
bool prime(long long num) {
    for(long long i=2;i*i<=num;i++) {
        if(num%i==0)return 0;
    }
    return 1;
}
int main() {
    cin>>n;
    if(prime(n))cout<<1<<endl;
    else if(n%2==0)cout<<2<<endl;
    else if(prime(n-2))cout<<2<<endl;
    else cout<<3<<endl;
    return 0;
}
```

#### 题解3：作者：ADivT (赞：2)  
**星级：4星**  
**关键亮点：**  
- 详细解释了哥德巴赫猜想在本题中的应用，特别是对奇数的处理。
- 代码简洁，逻辑清晰，直接判断$n$是否为质数，以及$n-2$是否为质数。

**核心代码：**
```cpp
bool prime(int a) {
    for(int i=2; i*i<=a; ++i)
        if(a%i==0) return 0;
    return 1;
}
int main() {
    int n;
    scanf("%d",&n);
    if(prime(n))printf("%d\n",1);
    else if(n%2==0||prime(n-2))printf("%d\n",2);
    else printf("%d\n",3);
    return 0;
}
```

### 最优关键思路与技巧

1. **哥德巴赫猜想的应用**：将问题分为$n$为质数、偶数、奇数三种情况，分别处理。
2. **质数判断优化**：通过循环到$\sqrt{n}$来判断质数，减少计算量。
3. **特殊情况处理**：对于奇数，判断$n-2$是否为质数，以决定最优解。

### 可拓展之处

- **类似算法套路**：可以应用于其他需要分解整数的问题，如最小化某些函数值的问题。
- **同类型题目**：可以考虑其他基于质数分解或整数分解的题目。

### 推荐题目

1. **P1217 [USACO1.5]回文质数**：考察质数判断和回文数的结合。
2. **P1075 质因数分解**：考察质因数分解的基本应用。
3. **P3383 【模板】线性筛素数**：考察素数筛法的应用。

### 个人心得摘录

- **yyyer**：通过哥德巴赫猜想简化问题，直接得出最优解。
- **lgnotus**：详细解释了奇数的处理方式，确保逻辑严谨。
- **ADivT**：通过快速判断质数，优化了代码效率。

---
处理用时：44.41秒