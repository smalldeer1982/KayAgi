# 题目信息

# Strange Function

## 题目描述

Let $ f(i) $ denote the minimum positive integer $ x $ such that $ x $ is not a divisor of $ i $ .

Compute $ \sum_{i=1}^n f(i) $ modulo $ 10^9+7 $ . In other words, compute $ f(1)+f(2)+\dots+f(n) $ modulo $ 10^9+7 $ .

## 说明/提示

In the fourth test case $ n=4 $ , so $ ans=f(1)+f(2)+f(3)+f(4) $ .

- $ 1 $ is a divisor of $ 1 $ but $ 2 $ isn't, so $ 2 $ is the minimum positive integer that isn't a divisor of $ 1 $ . Thus, $ f(1)=2 $ .
- $ 1 $ and $ 2 $ are divisors of $ 2 $ but $ 3 $ isn't, so $ 3 $ is the minimum positive integer that isn't a divisor of $ 2 $ . Thus, $ f(2)=3 $ .
- $ 1 $ is a divisor of $ 3 $ but $ 2 $ isn't, so $ 2 $ is the minimum positive integer that isn't a divisor of $ 3 $ . Thus, $ f(3)=2 $ .
- $ 1 $ and $ 2 $ are divisors of $ 4 $ but $ 3 $ isn't, so $ 3 $ is the minimum positive integer that isn't a divisor of $ 4 $ . Thus, $ f(4)=3 $ .

Therefore, $ ans=f(1)+f(2)+f(3)+f(4)=2+3+2+3=10 $ .

## 样例 #1

### 输入

```
6
1
2
3
4
10
10000000000000000```

### 输出

```
2
5
7
10
26
366580019```

# AI分析结果

### 题目内容重写

#### 题目描述

设 $f(i)$ 表示最小的正整数 $x$，使得 $x$ 不是 $i$ 的除数。

计算 $\sum_{i=1}^n f(i)$ 对 $10^9+7$ 取模的结果。换句话说，计算 $f(1)+f(2)+\dots+f(n)$ 对 $10^9+7$ 取模的结果。

#### 说明/提示

在第四个测试用例中，$n=4$，所以 $ans=f(1)+f(2)+f(3)+f(4)$。

- $1$ 是 $1$ 的除数，但 $2$ 不是，所以 $2$ 是 $1$ 的最小非除数。因此，$f(1)=2$。
- $1$ 和 $2$ 是 $2$ 的除数，但 $3$ 不是，所以 $3$ 是 $2$ 的最小非除数。因此，$f(2)=3$。
- $1$ 是 $3$ 的除数，但 $2$ 不是，所以 $2$ 是 $3$ 的最小非除数。因此，$f(3)=2$。
- $1$ 和 $2$ 是 $4$ 的除数，但 $3$ 不是，所以 $3$ 是 $4$ 的最小非除数。因此，$f(4)=3$。

因此，$ans=f(1)+f(2)+f(3)+f(4)=2+3+2+3=10$。

#### 样例 #1

##### 输入

```
6
1
2
3
4
10
10000000000000000
```

##### 输出

```
2
5
7
10
26
366580019
```

### 算法分类

数学

### 题解分析与结论

本题的核心在于理解 $f(i)$ 的定义，并通过数学方法高效计算 $\sum_{i=1}^n f(i)$。大多数题解都利用了 $f(i)$ 的性质，即 $f(i) = k$ 当且仅当 $\operatorname{lcm}(1,2,\dots,k-1)$ 整除 $i$，但 $k$ 不整除 $i$。通过预处理 $\operatorname{lcm}(1,2,\dots,k)$，可以快速计算每个 $k$ 对应的 $i$ 的数量，从而求出总和。

### 精选题解

#### 题解1：云浅知处 (5星)

**关键亮点**：
- 通过预处理 $\operatorname{lcm}(1,2,\dots,k)$，将问题转化为对每个 $k$ 计算满足条件的 $i$ 的数量。
- 使用容斥原理，通过 $\left\lfloor\frac{n}{\operatorname{lcm}(1,2,\dots,k-1)}\right\rfloor - \left\lfloor\frac{n}{\operatorname{lcm}(1,2,\dots,k)}\right\rfloor$ 计算满足条件的 $i$ 的数量。
- 代码清晰，预处理部分简洁高效。

**核心代码**：
```cpp
void init(){
    f[0]=f[1]=1;
    for(int i=2;i<=100;i++)f[i]=lcm(f[i-1],i);
}

int t,n;

signed main(void){
    init();
    cin>>t;
    while(t--){
        cin>>n;
        int ans=0;
        for(int i=1;f[i]<=n;i++)ans=(ans+(i+1)*(((n/f[i])-(n/f[i+1]))))%mod;
        cout<<ans<<endl;
    }
    return 0;
}
```

#### 题解2：VinstaG173 (4星)

**关键亮点**：
- 同样利用 $\operatorname{lcm}(1,2,\dots,k)$ 的性质，通过容斥原理计算满足条件的 $i$ 的数量。
- 代码简洁，直接计算每个 $k$ 的贡献。

**核心代码**：
```cpp
int main(){
    scanf(" %d",&t);
    lcm[1]=1;
    while(t--){
        scanf(" %lld",&n);res=0;
        for(i=2;;++i){
            lcm[i]=i/gcd(lcm[i-1],i)*lcm[i-1];
            res=(res+i*(n/lcm[i-1]-n/lcm[i]))%ntf;
            if(lcm[i]>n)break;
        }
        printf("%lld\n",res);
    }
    return 0;
}
```

#### 题解3：ZCETHAN (4星)

**关键亮点**：
- 通过打表计算每个 $f(i)$ 的周期，利用最小公倍数性质快速计算贡献。
- 代码结构清晰，预处理部分高效。

**核心代码**：
```cpp
void solve(){
    ll n;
    scanf("%lld",&n);
    ll ans=n*2%MOD;
    ans=(ans+n/2)%MOD;
    for(int i=4;top[i]<=n;i++){
        ans=(ans+n/top[i])%MOD;
    }
    printf("%lld\n",ans);
}
```

### 最优关键思路

通过预处理 $\operatorname{lcm}(1,2,\dots,k)$，利用容斥原理快速计算每个 $k$ 对应的 $i$ 的数量，从而高效求出 $\sum_{i=1}^n f(i)$。这种方法将问题转化为数学计算，避免了直接枚举 $i$ 的低效性。

### 拓展思路

类似的问题可以通过预处理和数学性质来优化计算，特别是在涉及数论和组合数学的题目中。例如，计算某个函数的前缀和时，可以利用函数的周期性或数学性质来减少计算量。

### 推荐题目

1. [P2261 [CQOI2007]余数求和](https://www.luogu.com.cn/problem/P2261)
2. [P1447 [NOI2010]能量采集](https://www.luogu.com.cn/problem/P1447)
3. [P2158 [SDOI2008]仪仗队](https://www.luogu.com.cn/problem/P2158)

---
处理用时：35.18秒