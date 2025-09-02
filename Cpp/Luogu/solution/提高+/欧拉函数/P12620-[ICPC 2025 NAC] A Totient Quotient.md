# [ICPC 2025 NAC] A Totient Quotient

## 题目描述

对于一个正整数 $k$，欧拉函数 $\phi(k)$ 定义为小于等于 $k$ 且与 $k$ 互质的正整数的个数。例如，$\phi(9) = 6$，$\phi(24) = 8$，$\phi(1) = 1$。（提醒一下，两个正整数 $a$ 和 $b$ 的最大公约数（gcd）是能同时整除 $a$ 和 $b$ 的最大正整数。如果两个正整数的 gcd 为 $1$，则它们互质。）

欧拉乘积公式通过 $k$ 的质因数分解给出了 $\phi(k)$ 的值。对于一个质数 $p$，令 $\nu_p(k)$ 表示 $p$ 的最高幂次，使得 $p^{\nu_p(k)}$ 能整除 $k$（例如，$\nu_2(48) = 4$，$\nu_3(48)=1$，$\nu_5(48)=0$）。如果 $k$ 是若干质数的幂次的乘积，即 $k = \prod_{i=1}^j p_i^{\nu_{p_i}(k)}$（其中乘积仅包含满足 $\nu_{p_i}(k) > 0$ 的质数 $p_i$），那么：
$$ \phi(k) = \prod_{i=1}^j \left[(p_i - 1)\left(p_i^{\nu_{p_i}(k)-1}\right)\right].$$

《美国数学月刊》（Li 等人，《形如 $\phi(m^2)/\phi(n^2)$ 的正有理数》，128(2)，2021 年）最近的一期证明了以下关于欧拉商的事实：对于任意一对正整数 $a$、$b$，存在唯一的一对正整数 $m$、$n$ 满足：
1. $\frac{a}{b} = \frac{\phi(m^2)}{\phi(n^2)}$；
2. 如果一个质数 $p$ 整除乘积 $mn$，则 $\nu_p(m) \neq \nu_{p}(n)$；
3. $\gcd(m,n)$ 是无平方因子的：即对于每个质数 $p$，$\gcd(m,n)$ 不被 $p^2$ 整除。

条件 2 和 3 保证了 $m$ 和 $n$ 是满足条件 1 的唯一最小正整数对。

你希望通过数值验证这一结论。编写一个程序，输入两个整数 $a$ 和 $b$，输出对应的 $m$ 和 $n$。

## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
9 13```

### 输出

```
18 13```

## 样例 #2

### 输入

```
19 47```

### 输出

```
13110 18612```

# 题解

## 作者：gcx12012 (赞：1)

### 前言
这种题也能想很久，彻底没救了。
### Solution
由于不同质数之间都是相互独立的，我们可以先考虑一个质数的情况。

设 $m=p^k$，当其变成 $p^{k+1}$ 时，$\phi(m^2)$ 会发生什么变化。

我们发现，若 $k=0$，则 $\phi(m)$ 乘上 $p(p-1)$；否则它会乘上 $p^2$。

  然后我们考虑将 $a,b$ 做质数拆分，然后从大到小考虑质数。设 $a$ 有 $k_1$ 个质因子 $p$，$b$ 有 $k_2$ 个质因子 $p$，那么我们按照 $|k_1-k_2|$ 的奇偶性讨论，如果为偶数则小的一边答案乘上 $p$，大的一边答案乘上 $p^{\frac{|k_1-k_2|}{2}+1}$；否则让大的一边答案乘上 $p^{\frac{|k_1-k_2|-1}{2}+1}$，然后把 $p-1$ 的质数拆分贡献到小的一边，一直这样做下去就做完了。
```
const ll V=10000;
ll cnt[N],cnt2[N];
ll a,b,m=1,n=1;

ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}


int main()
{
    //freopen("gcx.in","r",stdin);
    //freopen("gcx.out","w",stdout);
    a=read(),b=read();
    For(i,2,sqrt(a)){
        while(a%i==0) cnt[i]++,a/=i;
    }
    if(a>1) cnt[a]++;
    For(i,2,sqrt(b)){
        while(b%i==0) cnt2[i]++,b/=i;
    }
    if(b>1) cnt2[b]++;
    Rof(i,V,2){
        ll now=min(cnt[i],cnt2[i]);
        cnt[i]-=now,cnt2[i]-=now;
        if(cnt[i]){
            if(cnt[i]&1){
                For(j,1,cnt[i]/2+1) m*=i;
                ll now=i-1;
                For(j,2,sqrt(now)){
                    while(now%j==0) cnt2[j]++,now/=j;
                }
                if(now>1) cnt2[now]++;
            }else{
                m*=i,n*=i;
                For(j,1,cnt[i]/2) m*=i;
            }
        }
        if(cnt2[i]){
            if(cnt2[i]&1){
                For(j,1,cnt2[i]/2+1) n*=i;
                ll now=i-1;
                For(j,2,sqrt(now)){
                    while(now%j==0) cnt[j]++,now/=j;
                }
                if(now>1) cnt[now]++;
            }else{
                m*=i,n*=i;
                For(j,1,cnt2[i]/2) n*=i;
            }
        }
    }
    cout<<m<<' '<<n<<endl;
   	return 0;
}
```

---

