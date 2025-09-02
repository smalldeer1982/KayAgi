# 题目信息

# Weakened Common Divisor

## 题目描述

与  $GCD$  （最大公约数）类似，我们引进  $WCD$ （弱公约数）的概念， $ WCD$  的定义如下：

给出几对数 $\left( a_1,b_1 \right) ,\left( a_2,b_2 \right) ,\cdots ,\left( a_n,b_n \right)$ ，它们的  $WCD$  满足大于  $1 $ ，且能整除每个数对中至少一个数。  $WCD$  在一些情况下，可能不存在。

例如，给出这几对数 $\left[ \left( \text{12,}15 \right) ,\left( \text{25,}18 \right) ,\left( \text{10,}24 \right) \right]$  ，它们的   $WCD$  可以是 $ 2,3,5,6$  （这些数都满足严格大于  $1$  ，且能整除每个数对中至少一个数）

现在给你几对数，求他们的   $WCD$  。

## 样例 #1

### 输入

```
3
17 18
15 24
12 15
```

### 输出

```
6```

## 样例 #2

### 输入

```
2
10 16
7 17
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5
90 108
45 105
75 40
165 175
33 30
```

### 输出

```
5
```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是围绕着找出满足条件的弱公约数（WCD），主要方法有两种：一是先求出每对数的最小公倍数（lcm），再求所有 lcm 的最大公约数（gcd），最后找出 gcd 的一个质因数；二是先分解第一对数的质因数，然后逐个检查这些质因数是否能整除后续每对数中的至少一个数。

- **思路对比**：
    - 计算 lcm 和 gcd 的方法相对巧妙，但可能存在时间复杂度较高的问题，尤其是直接计算 lcm 会增加计算量。
    - 分解质因数的方法较为直接，通过筛选出满足条件的质因数来得到结果。
- **算法要点**：
    - 计算 lcm 和 gcd 时，利用了 gcd 的结合律和质因数分解的性质。
    - 分解质因数时，需要注意对每个数的质因数进行完整分解，包括可能存在的大于根号的质因数。
- **解决难点**：
    - 质因数分解的时间复杂度较高，部分题解采用了优化方法，如判断选 $a_1$ 还是 $b_1$ 与 gcd 取最大公约数来减小要分解的数的大小。
    - 对于较大的数，直接 $O(\sqrt{n})$ 分解质因数可能会超时，部分题解提到了使用 Pollard-rho 算法来优化。

### 所选题解
- **作者：zhaotiensn (赞：7) - 4星**
    - **关键亮点**：思路清晰，通过计算 lcm 和 gcd 简化问题，代码实现简洁明了。
    - **个人心得**：作者提到分解质因数觉得太麻烦，且担心根号级的复杂度会超时，所以采用了这种投机取巧的方法。
```cpp
inline ll gcd(ll x,ll y){
    return x%y?gcd(y,x%y):y;
}
inline ll calc(ll x){//求一个质因子
    for(int i=2;i<=sqrt(x);i++){
        if(x%i==0){
            return i;
        }
    }
    return x;
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n;
    n--;
    cin>>a>>b;
    ans=a*b/gcd(a,b);
    while(n--){
        cin>>a>>b;
        ans=gcd(ans,a*b/gcd(a,b));//对于所有的lcm求gcd
    }
    if(ans==1){//如果gcd为1，那么就没有wcd
        cout<<-1<<endl;
    }else{
        if(gcd(ans,a)>1){//要求的因子一定在a中或b中
            cout<<calc(gcd(ans,a))<<endl;
        }else{
            cout<<calc(gcd(ans,b))<<endl;
        }
    }
    return 0;
}
```
核心实现思想：先计算第一对数的 lcm，然后依次与后续每对数的 lcm 求 gcd，最后根据 gcd 的结果判断是否存在 WCD，并找出一个质因数输出。

- **作者：Dreamunk (赞：1) - 4星**
    - **关键亮点**：直接分解第一对数的质因数，然后逐个检查，时间复杂度较低，代码简洁。
```cpp
int n,a,b,p[20],fl[20],t[20],k;
int main(){
    int f;
    n=read();
    a=read();b=read();
    for(int i=2;i*i<=a;i++){
        f=0;
        for(;a%i==0;)a/=i,f=1;
        if(f)p[++k]=i;
    }if(a>1)p[++k]=a;
    for(int i=2;i*i<=b;i++){
        f=0;
        for(;b%i==0;)b/=i,f=1;
        if(f)p[++k]=i;
    }if(b>1)p[++k]=b;
    for(;--n;){
        a=read();b=read();
        for(int j=1;j<=k;j++)
            if(a%p[j]&&b%p[j])fl[j]=1;
    }
    for(int i=1;i<=k;i++)if(!fl[i])
        return 0*printf("%d",p[i]);
    return 0*puts("-1");
}
```
核心实现思想：先分解第一对数的质因数，存储在数组中，然后遍历后续每对数，标记不满足条件的质因数，最后输出满足条件的质因数。

- **作者：Eleveslaine (赞：0) - 4星**
    - **关键亮点**：对结论进行了详细的证明，思路严谨，通过引理证明了答案与 lcm 和 gcd 的关系。
```cpp
// factor(x) 返回 x 最小的质因数
n=read<int>();
for(int i=1;i<=n;++i)
{
    a=read<ll>(),b=read<ll>();
    ans=gcd(ans,lcm(a,b));
}
if(ans==1)
{
    puts("-1");
    return 0;
}
else
{
    if(gcd(ans,a)!=1)
        printf("%lld\n",factor(gcd(ans,a)));
    else
        printf("%lld\n",factor(gcd(ans,b)));
}
```
核心实现思想：通过循环计算所有数对的 lcm 的 gcd，根据 gcd 的结果判断是否存在 WCD，若存在则找出一个质因数输出。

### 最优关键思路或技巧
- 利用 gcd 的结合律和质因数分解的性质，将问题转化为计算 lcm 和 gcd 的问题。
- 分解质因数时，注意对每个数的质因数进行完整分解，包括可能存在的大于根号的质因数。
- 对于较大的数，可通过判断选 $a_1$ 还是 $b_1$ 与 gcd 取最大公约数来减小要分解的数的大小。

### 可拓展之处
同类型题或类似算法套路：
- 求多个数的最大公约数或最小公倍数的相关问题。
- 质因数分解在数论问题中的应用，如判断一个数是否为质数、求一个数的所有因数等。

### 推荐题目
- [P1072  Hankson的趣味题](https://www.luogu.com.cn/problem/P1072)
- [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
- [P2152 SDOI2009 SuperGCD](https://www.luogu.com.cn/problem/P2152)

### 个人心得总结
- zhaotiensn 提到分解质因数觉得太麻烦，且担心根号级的复杂度会超时，所以采用了计算 lcm 和 gcd 的方法。这提醒我们在解题时可以尝试不同的思路，避免陷入固定的思维模式。
- Jasper08 提到一开始想预处理 $2\times 10^8$ 内所有质数，结果 MLE 了。这告诉我们在处理大规模数据时，要注意空间复杂度，避免内存溢出。

---
处理用时：53.60秒