# Carousel of Combinations

## 题目描述

You are given an integer $ n $ . The function $ C(i,k) $ represents the number of distinct ways you can select $ k $ distinct numbers from the set { $ 1, 2, \ldots, i $ } and arrange them in a circle $ ^\dagger $ .

Find the value of 
$$
\sum\limits_{i=1}^n \sum\limits_{j=1}^i \left( C(i,j) \bmod j \right)
$$
Here, the operation  $ x \\bmod y $  denotes the remainder from dividing  $ x $  by  $ y $ .</p><p>Since this value can be very large, find it modulo  $ 10^9+7 $ .</p><p> $ ^\\dagger $  In a circular arrangement, sequences are considered identical if one can be rotated to match the other. For instance,  $ \[1, 2, 3\] $  and  $ \[2, 3, 1\]$$$ are equivalent in a circle.

## 说明/提示

In the first test case, $ C(1,1) \bmod 1 = 0 $ .

In the second test case:

- $ C(1,1)=1 $ (the arrangements are: $ [1] $ );
- $ C(2,1)=2 $ (the arrangements are: $ [1] $ , $ [2] $ );
- $ C(2,2)=1 $ (the arrangements are: $ [1, 2] $ );
- $ C(3,1)=3 $ (the arrangements are: $ [1] $ , $ [2] $ , $ [3] $ );
- $ C(3,2)=3 $ (the arrangements are: $ [1, 2] $ , $ [2, 3] $ , $ [3, 1] $ );
- $ C(3,3)=2 $ (the arrangements are: $ [1, 2, 3] $ , $ [1, 3, 2] $ ).

 In total, $ \left(C(1,1) \bmod 1\right) + \left(C(2,1) \bmod 1\right) + \left(C(2,2) \bmod 2\right) + \left(C(3,1) \bmod 1\right) + \left(C(3,2) \bmod 2\right) + \left(C(3,3) \bmod 3\right) = 4 $ .

## 样例 #1

### 输入

```
4
1
3
6
314159```

### 输出

```
0
4
24
78926217```

# 题解

## 作者：William2022 (赞：7)

# CF1957E 题解

## 题目大意
要求直接计算
$$
\sum\limits_{i=1}^n \sum\limits_{j=1}^i \left( C(i,j) \bmod j \right)
$$
其中 $C(i,j)$ 表示从 $i$ 个数当中选 $j$ 个的不同圆排列数。  
拥有 $T$ 组测试样例 $T \leq 10^5$，$n \leq 10^6$。

## 前置知识提示
1. 威尔逊定理  
1. 卢卡斯定理  

## 分析C函数
因为这里的 $C(i,j)$ 是指圆排列数，先选择 $j$ 个数字，方案为 $\binom{i}{j}$。我们尝试将选择的数中的第一个固定，剩下 $j-1$ 个数字的排列方式数为 $(j-1)!$。

所以圆排列数的计算公式为：
$$
C(i,j) = \binom{i}{j} \times (j-1)! 
$$

## 入手  
1. 尝试快速预处理出所有的 $a[i] =\sum\limits_{j=1}^i \left( C(i,j) \bmod j \right)$ 然后对于每组输入数据直接输出前缀和 $\sum\limits_{i=1}^n a[i]$ 即可
2. 展开组合数得
  
$$
\begin{aligned}
C(i,j) &= \binom{i}{j} \times (j-1)! \\
&= \frac{i!}{j!(i-j)!} \times (j-1)! \\
&= \frac{i!}{j(i-j)!}
\end{aligned}

$$

因为 $i>j$ 所以可以从 $i!$ 找到至少一个 $j$ 与分母的 $j$ 抵消
$$
\frac{i!}{(i-j)!} = i \times (i-1) \times \cdots \times (i-j+1)
$$
当 $j$ 是合数时可以证明这其中的质因数可以组成另一个 $j$。  
然后因为结果要模 $j$ 所以我们会得到 $0$。

### 重要 corner  
当 $j=4$ 时，我们上述的可以得到的两个 $j$，也就是一个 $j$ 与两个 $2$ 其中的一个 $2$ 与那个 $j$ 重合，导致结果无法被 $4$ 整除，因此 $4$ 也能造成有效贡献。

至此，我们后面只要考虑 $j$ 为质数的情况了，$4$ 的情况直接加上去。

## 公式推导  
$$
C(i,j) \equiv \binom{i}{j} \times (j-1)! \pmod{j}
$$
根据卢卡斯定理
$$ C(i,j)  \equiv \binom{i \bmod j}{j \bmod j} \times \frac{\lfloor \frac{i}{j} \rfloor}{\lfloor \frac{j}{j} \rfloor} \times (j-1)! \pmod{j}$$
$$
C(i,j) \equiv \lfloor \frac{i}{j} \rfloor \times (j-1)! \pmod{j}
$$
根据威尔逊定理
$$
C(i,j) \equiv -\lfloor \frac{i}{j} \rfloor \pmod{j}
$$
把题目要我们求的结果只考虑质数并用 $C(i,j)$ 替换
$$
\sum\limits_{i=1}^n \sum\limits_{\substack{j为质数 \\ j \leq i}} \left( C(i,j) \bmod j \right) = \sum\limits_{i=1}^n \sum\limits_{\substack{j为质数 \\ j \leq i}} \left( -\left\lfloor \frac{i}{j} \right\rfloor \bmod j \right)
$$
因为括号里有一个 $\bmod j$ 所以考虑交换两个求和顺序  
$$
\sum\limits_{i=1}^n \sum\limits_{\substack{j为质数 \\ j \leq i}} \left( -\left\lfloor \frac{i}{j} \right\rfloor \bmod j \right) = \sum\limits_{j为质数}\sum\limits_{i=j}^n \left( -\left\lfloor \frac{i}{j} \right\rfloor \bmod j \right)
$$
所以我们枚举每一个质数 $j$，并快速求出其对每一个 $a[i]$ 的贡献。

## 递推求解
当我们枚举到 $j$ 的时候，因为 $\left\lfloor \frac{i}{j} \right\rfloor$ 是每连续 $j$ 个数字都是一样的，所以我们从 $i$ 开始，对每 $j$ 个合法的数字加上 $-\left\lfloor \frac{i}{j} \right\rfloor$ 的贡献，区间增加，静态查询，直接差分就行了。  
$j=4$ 时，$(j-1) \equiv 3! \equiv 2\pmod{4}$ ，展开计算 $C(x,4)=\frac{i(i-1)(i-2)(i-3)}{4} \bmod 4$ 发现如果 $2\mid \lfloor \frac{i}{8} \rfloor $ 结果就是 $2$ 否则是 $0$
## 复杂度
$\frac{n}{2} + \frac{n}{3} + \frac{n}{5} + \frac{n}{7} +\ldots+ \frac{n}{4} \approx O(nloglogn) $
## 代码
基本与公式相同，码量很少

```cpp
const int N=1e6;
ll a[MXN];//差分数组，静态做区间修改

void add(int l,int r,int add){//区间修改
    r=Min(r,N);
    (a[l]+=add)%=M;
    (a[r+1]-=add)%=M;
}

void solve(int p){
    for(int i=p;i<=N;i+=p){
        add(i,i+p-1,(i/p*(p-1))%p);
        //-1 ≡ p-1 (mod p)
    }
}
void solve4(){
    for(int i=4;i<=N;i+=4){
        add(i,i+4-1,(i/4*2)%4);
    }
}

signed main() {
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    
    euler();
    for(int i=1;i<=tot;i++)solve(prime[i]);
    solve4();
    
    for(int i=1;i<=N;i++)(a[i]+=a[i-1])%=M;//差分->原数组
    for(int i=1;i<=N;i++)(a[i]+=a[i-1])%=M;//原数组->前缀和
    
    int T;
    std::cin>>T;
    while(T--){
        int x;
        std::cin>>x;
        std::cout<<a[x]<<"\n";
    }
}
```

## 致谢
非常感谢 [C20220403](https://www.luogu.com.cn/user/499128) 大佬在今天春游时为我提供了此题的部分灵感。  

## 更改  
$2025.5.1$ 修正了入手板块的公式

---

## 作者：沉石鱼惊旋 (赞：5)

# 前言

赛时一直在做这题但是没推出来呜呜，下次还是不能懒，多打表。一些东西也不要随便化简，可能化简之后反而看不出结论了。

感谢 ciuim 和 NaCly_Fish 等大神在 LA 群教会我做这题。

# 题目翻译

给定 $n$，求 $(\sum\limits_{j=1}^n\sum \limits_{i=j}^n(C(i,j)\bmod j))\bmod p$。

其中 $p=10^9+7$。

$C(i,j)$ 表示圆排列，即 $\binom{i}{j}(j-1)!$。

$n!$ 表示阶乘，即 $n\times (n-1)\times (n-2)\times \dots\times 1$。

$t$ 组询问。

$1\leq t\leq 5\times 10^5,1\leq n\leq 10^6$。**与大部分 CF 类型题不一样的是，本题没有对 $\sum n$ 的约束**。

# 题目思路

首先先把题目这个鬼式子打开来。即为 $(\sum\limits_{j=1}^n\sum \limits_{i=j}^n(\dfrac{i!(j-1)!}{j!(i-j)!}\bmod j))\bmod p$。

这时容易发现，对于每个 $j$ 分开处理比较好，因为都带一个 $\bmod j$。

然后看到这个时间限制，不难猜测是不劣于 $\mathcal O(n\log n)$ 的解法。

当然虽然没有保证 $\sum n$ 但是我们可以提前把 $[1,10^6]$ 的答案都算出来然后 $\mathcal O(1)$ 回答。

那么我们大概猜测这样一个东西：对于任意 $j$ 在**均摊**不劣于 $\mathcal O(\log n)$ 时间求出 $(\sum\limits_{i=j}^n(\dfrac{i!(j-1)!}{j!(i-j)!}\bmod j))\bmod p$。

考虑到这个 $\bmod j$ 的循环节什么的，很容易往调和级数上去想。事实上我赛时也推到了这一步。

这个时候集中注意力观察。考虑到这个式子是一个二项式系数乘上一个 $(j-1)!$。那么 $(j-1)! \equiv 0\pmod j$ 是上式为 $0$ 的**充分**条件。

接下来把注意力再次放大，发现不满足 $j=4\operatorname{or}j\text{ is prime}$ 的 $j$ 贡献都是 $0$。

不满足 $j\text{ is prime}$ 的 $j$ 贡献都是 $0$，这个结论如何证明？

首先 $j=1$ 显然任何数 $\equiv 0\pmod 1$。

然而当 $j$ 是合数且 $j\neq 4$ 的时候，$(j-1)!\equiv 0\pmod j$ 的证明如下。

考虑合数书写是 $a\times b$ 满足 $a\neq 1\operatorname{and} b\neq 1$，那么朴素情况下即 $a\neq b$，显然 $a$ 与 $b$ 分别作为一个因子在 $(j-1)!$ 中出现了。

极端一点，$a=b$，且 $a,b$ 均为质数，这是最不好处理的。

然而，由于对于 $a\gt2$ 的情况，一定可以被证明成 $2a$ 与 $b$ 也分别作为一个因子在 $(j-1)!$ 中出现了。

$a=b=2$ 是最特殊的情况，因此 $4$ 不被包括在这类合数中。 

---

这里有个问题我想了很久，感觉是熬夜打 CF 然后熬夜补题导致的脑子生锈。我们并不是说满足 $(j-1)! \equiv 0\pmod j$ 的才可以满足上式为 $0$。只是说满足 $(j-1)! \equiv 0\pmod j$ 一定满足上式为 $0$，而且可以筛去大部分无用的数。操作起来很方便。

---

接下来有了这个结论就很好做了。

之后的推导需要『威尔逊定理』和『卢卡斯定理』作为前置知识。

威尔逊定理：对于任意质数 $p$ 满足 $(p-1)!\equiv p-1 \pmod p$。

卢卡斯定理：对于任意质数 $p$ 满足 $ \binom n m\bmod p=\binom{\lfloor n/p\rfloor}{\lfloor m/p\rfloor}\times \binom{n\bmod p}{m\bmod p}\bmod p$。

$j=4$ 部分很简单，直接按上式算就可以，$\mathcal O(n)$ 解决。乘法过程会炸 long long，可以使用 __int128 解决。

$j\text { is prime}$ 部分，把上面两个定理组合起来，得到 $\binom ij(j-1)!\equiv \binom ij(j-1)\equiv -\binom i j\equiv-\lfloor\frac i j\rfloor\pmod j$。

因此，$[kj,(k+1)j-1]$ 之间产生的贡献是一样的，都是 $-\lfloor\frac i j\rfloor=-k$。

所以我们直接枚举这个 $k$ 即可。区间加法可以使用差分解决。

复杂度是一个类似调和级数的东西。当然，这里只有质数，所以复杂度等同埃筛即 $\mathcal O(n\log \log n)$。

注意做完之后需要再做一次前缀和才能 $\mathcal O(1)$ 回答。

# 部分代码

[https://codeforces.com/contest/1957/submission/257645847](https://codeforces.com/contest/1957/submission/257645847)

省略了 modint 部分。

> 注意做完之后需要再做一次前缀和才能 $\mathcal O(1)$ 回答。

所以代码最后出现了 2 次前缀和。第一次是差分操作，第二次是前缀和。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int P = 1e9 + 7;
using Z = mod_int<P>;
typedef long long ll;
typedef __int128 LL;
const int N = 1e6;
int p[1000020];
bool np[1000020];
Z ans[1000020];
void add(int l, int r, Z w)
{
    ans[l] += w, ans[min(r, N) + 1] -= w;
}
void solve()
{
    int n;
    cin >> n;
    cout << ans[n] << '\n';
}
int main()
{
    np[1] = 1;
    for (int i = 2; i <= N; i++)
    {
        if (!np[i])
            p[++p[0]] = i;
        for (int j = 1; j <= p[0] && i * p[j] <= N; j++)
        {
            np[i * p[j]] = 1;
            if (i % p[j] == 0)
                break;
        }
    }
    for (int j = 1; j <= N; j++)
    {
        if (np[j])
        {
            if (j == 4)
            {
                for (LL k = 4; k <= N; k++)
                    add(k, k, k * (k - 1) * (k - 2) * (k - 3) / 4 / 3 / 2 / 1 * 3 * 2 * 1 % 4);
            }
            continue;
        }
        for (int k = 1; k * j <= N; k++)
            add(k * j, (k + 1) * j - 1, (-k % j + j) % j);
    }
    for (int i = 1; i <= N; i++)
        ans[i] += ans[i - 1];
    for (int i = 1; i <= N; i++)
        ans[i] += ans[i - 1];
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
```

---

## 作者：Starrykiller (赞：3)

推了半天没看出来复杂度正确也是挺难绷的。

约定：下文中，$\mathbb{P}$ 代表素数集。

注意到 $\displaystyle C(i,j)\bmod j={i\choose j}(j-1)!\bmod j$。（解释：选出 $j$ 个元素后圆排列，$n$ 个元素的圆排列方案数是 $(n-1)!$ 种，因为每个圆排列对应 $n$ 个排列。）

注意到当且仅当 $j=4$ 或 $j\in \mathbb{P}$ 的时候，$C(i,j)\bmod j\neq 0$。

我们分类讨论。

### $j\in \mathbb{P}$

当 $j\in \mathbb{P}$ 的时候，由 Wilson 定理和 Lucas 定理知道

$${i\choose j}(j-1)!\equiv -{i\choose j}\equiv -\left\lfloor\frac{i}{j}\right\rfloor\pmod j$$

（关于 Lucas 定理：我们利用了

$${i\choose j}\equiv {\lfloor\frac{i}{j}\rfloor\choose \lfloor\frac{j}{j}\rfloor}{i\bmod j\choose j\bmod j}={\lfloor\frac{i}{j}\rfloor\choose \lfloor\frac{j}{j}\rfloor}={\lfloor\frac{i}{j}\rfloor\choose 1}=\left\lfloor\frac{i}{j}\right\rfloor \pmod j$$

）

所以 $\displaystyle C(i,j)\bmod j=\left(j-\left\lfloor\frac{i}{j}\right\rfloor\bmod j\right)\bmod j$，我们将它记为 $f(i,j)$。

答案式子的**一部分**为

$$\sum_{i=1}^n \sum_{j\in\mathbb{P}} f(i,j)$$

（此处已经利用 $j\gt i$ 的时候，$f(i,j)=0$）

我们交换求和号，得到

$$\sum_{j\in \mathbb{P}}\sum_{i\ge j}^n f(i,j)$$

我们发现对于素数 $p$，$[kp,kp+p)$ 的每一个 $f(i,p)$ 值都相同。因此这一部分我们可以利用前缀和来把贡献加到每一个区间 $[kp,kp+p)$ 里面，这样是 $\Theta(n\log \log n)$ 的（和 Erathosthenes 筛的分析是一样的，虽然我不会）。

### $j=4$

别忘记了 $4$ 的贡献。

注意到当 $k\equiv 1\pmod 2$ 的时候，$\forall i\in [4k, 4k+4)$，$f(i,4)=2$；当 $k\equiv 1\pmod 0$ 的时候，$\forall i\in [4k, 4k+4)$，$f(i,4)=0$。

所以累加一下就好了。

综上，我们以 $\Theta(n\log \log n)$ 预处理的代价做到了 $\Theta(1)$ 回答每个询问。

[My implementation](https://codeforces.com/contest/1957/submission/257741411).

---

## 作者：yshpdyt (赞：3)

## 题意
求：
$$\sum\limits_{i=1}^n\sum\limits_{j=1}^i\left(C(i,j)\bmod j\right)$$

其中 $C(i,j)$ 表示从 $i$ 个数当中选 $j$ 个的不同圆排列数。

最终答案对 $10^9+7$ 取模。 

注意区分题目中的两个取模的位置。
## Sol
$C(i,j)$  是很好表示的，就是组合数乘圆排列数，即：
$$\tbinom{i}{j}(i-1)!$$
然后这个东西要对 $j$ 取模，这里使用两个定理，~~如果不知道可以尝试打表找规律~~。

把左右两个式子分开考虑。

左边的组合数注意到模数每次不同且模数较小，考虑**卢卡斯定理**，~~前几天刚学就用上了~~，这个定理的形式如下：

$$ \tbinom{n}{m} \equiv \tbinom{\lfloor n/p \rfloor}{\lfloor m/p \rfloor}\tbinom{n\bmod p}{m\bmod p} \pmod p $$

代入本题就变成很简单的式子了：
$$ \tbinom{i}{j} \equiv \left\lfloor \frac{i}{j} \right\rfloor  \pmod p $$


右边的式子使用**威尔逊定理**，~~长得就很像这个形式~~，形式如下：

如果 $p$ 是质数，有：
$$(p-1)!\equiv p-1\pmod p$$

如果 $p$ 是 $4$，有：
$$(p-1)!\equiv 2\pmod p$$

如果 $p$ 是非 $4$ 的非质数，有：
$$(p-1)!\equiv 0\pmod p$$

所以本题中大部分情况贡献都是 $0$，只需要考虑质数和 $4$ 的影响，完整的式子如下：
$$C(i,4)\equiv 2\left\lfloor \frac{i}{4} \right\rfloor \pmod 4$$

$$C(i,j)\equiv \left\lfloor \frac{i}{j} \right\rfloor (i-1)\pmod j$$

但是直接枚举不太行。注意到不同的 $i$ 之间贡献独立，考虑分开计算最后求前缀和。

由于向下取整，对于 $i\in[kj,(k+1)j-1]$ 的贡献相同，所以对于每个质数枚举其倍数，然后实现区间增加 $k(j-1)$ 。

但是还得取模，然后每个质数的模数又不一样，考虑加的时候就进行取模.

$4$ 的情况比较特殊，但是很好分析，$i$ 如果是 $8$ 的倍数贡献没有贡献，原因显然。

区间增加用差分数组即可。

##
```
#include<bits/stdc++.h>
#define ll long long
#define N 1000005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
ll T;
vector<ll> p;
bool vis[N*3];
ll f[N*3];
ll add[N*3],n;
void sol(){
    cin>>n;
    cout<<f[n]<<endl;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    for(int i=2;i<=N;i++){
		if(!vis[i])p.push_back(i);
		for(auto j:p){
			if(i*j>N)break;
			vis[i*j]=1;
			if(i%j==0)break;
		}
	}
    ll val=0;
    for(auto y:p){
        val=y-1;
        for(int i=1;i*y<=N;i++){
            add[i*y]=(add[i*y]+val)%mod;
            add[i*y+y]=(add[i*y+y]-val+mod)%mod;
            if(val==0)val=y;
            val--;
        }
    }
    val=2;
    for(int i=1;i*4<=N;i++){
        add[i*4]=(add[i*4]+val)%mod;
        add[i*4+4]=(add[i*4+4]-val+mod)%mod;
        if(val==0)val=4;
        val-=2;
    }
    for(int i=1;i<=N;i++){
        add[i]=(add[i-1]+add[i]+mod)%mod;
        f[i]=(f[i-1]+add[i]+mod)%mod;
    }
    ll ttt;
    cin>>ttt;
    while(ttt--)sol();
    return 0;
}
```

---

## 作者：appear_hope (赞：2)

考虑预处理答案。

首先 $C(i, j) = \frac{A(i, j)}{j}$，可以理解为固定圆的第一个位置为 $1$，那么第一个位置会从 $j$ 种选择变到 $1$ 种选择。

拆式子：$C(i, j) = \frac{(i - j + 1) \times (i - j + 2) \times \dots \times i}{j}$。

你会发现 $i - j + 1, i - j + 2, \dots i$ 中必有 $j$ 的倍数。

证明：设 $i - j + 1$ 除以 $j$ 的余数为 $x$，那么从 $i - j + 1$ 开始第一个是 $j$ 的倍数的位置是 $j - x$ 除以 $j$ 的余数，显然这个余数 $< j$，所以 $i - j + 1, i - j + 2, \dots i$ 中必有 $j$ 的倍数。

那么 $C(i, j) = \lfloor \frac{i}{j} \rfloor \times (j - 1)!$。

根据威尔逊定理：若 $j$ 是质数，则 $(j - 1)! \equiv j - 1 \pmod j$。

对于 $j$ 是和数：

若 $j$ 是 $4$，则 $(j - 1)! \equiv 2 \pmod j$。

否则，$(j - 1)! \equiv 0 \pmod j$。

我们可以枚举 $j$，统一处理 $\lfloor \frac{i}{j} \rfloor$ 相等的 $i$，会发现符合这个要求的 $i$ 一定是一段区间，用差分维护。

那么我们现在算出了对于每一个 $i$，其中 $\sum \limits_{j = 1}^{i} C(i, j)$ 的值，对这个值维护一个前缀和即可，接着询问的时候输出答案即可。

---

## 作者：2022dyx (赞：1)

注意：此题定义的 $C$ 并不是传统的组合数，而是圆排列数。这是把排列放到圆上的方案数，因为一个圆有 $j$ 个等价类，因此有：
$$C_i^j=\binom{i}{j}\times (j-1)!$$
题目里最显眼的肯定是那个模 $j$ 了，这个东西提醒我们把 $j$ 相同的一起考虑。只看这个式子并没有什么东西，所以我们可以尝试把组合数拆开，有：
$$C_i^j=\binom{i}{j}(j-1)!=\frac{i^{\underline j}}{j!}\times (j-1)!=\frac{i^{\underline j}}{j}$$
上面的部分是 $j$ 个连续正整数，其中必然有一个是 $j$ 的倍数，可表示为 $\lfloor\frac{i}{j}\rfloor$，其余 $j-1$ 个在模 $j$ 意义下为 $1$ 到 $j-1$，因此原式可化为：
$$C_i^j\equiv(j-1)!\times\lfloor\frac{i}{j}\rfloor\pmod{j}$$
对于 $(j-1)!$ 来说，我们有定理：
$$$
(j-1)!\equiv
\begin{cases}
j-1,&j\in\mathbb{P}\\
2,&j=4\\
0,&otherwise
\end{cases}
\pmod{j}
$$$
先只考虑质数，其实 $4$ 也同理，设答案为 $f_n$，则 $j$ 导致其相比于 $f_{n-1}$ 的增量即为 $\sum_{i=j}^n-\lfloor\frac{i}{j}\rfloor$，显然对于任何 $k$，$j$ 对 $kj$ 到 $(k+1)j-1$ 的贡献均相等，因此我们可以用差分来维护贡献，最后再用前缀和回复。此时 $k$ 的上界为 $O(\frac{n}{j})$，因此总复杂度为 $O(n\log n)$。

代码如下：
```
#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define file(x) freopen(#x ".in", "r", stdin); freopen(#x ".out", "w", stdout);
using namespace std;
constexpr int N = 1e6 + 5;
constexpr int mod = 1e9 + 7;
int t, n, dlt[N], pre[N], ans[N];
bool vis[N];
vector <int> pri;
void check(int x, int y) {
    dlt[x] = (dlt[x] + (x - 1) / y % y) % mod;
    dlt[x] = (dlt[x] - x / y % y + mod) % mod;
}
signed main() {
    cin.tie(0) -> sync_with_stdio(false);
    for (int i = 2; i < N; ++i) {
        if (!vis[i]) pri.pb(i);
        for (auto j : pri) {
            if (i * j >= N) break;
            vis[i * j] = true;
            if (i % j == 0) break;
        }
    }
    for (int i : pri) {
        for (int j = 0; j <= N / i; ++j) {
            int l = i * j, r = i * (j + 1);
            dlt[l] = (dlt[l] + (i - 1) * j % i) % mod;
            if (j != N / i) dlt[r] = (dlt[r] - (i - 1) * j % i + mod) % mod;
        }
    }
    for (int j = 0; j <= N / 4; ++j) {
        int l = 4 * j, r = 4 * (j + 1);
        dlt[l] = (dlt[l] + 2 * j % 4) % mod;
        if (j != N / 4) dlt[r] = (dlt[r] - 2 * j % 4 + mod) % mod;
    }
    for (int i = 1; i < N; ++i) pre[i] = (pre[i - 1] + dlt[i]) % mod, ans[i] = (ans[i - 1] + pre[i]) % mod;
    cin >> t;
    while(t--) {
        cin >> n;
        cout << ans[n] << '\n';
    }
    
}
```

---

## 作者：Pengzt (赞：1)

# Carousel of Combinations

[题目链接](https://www.luogu.com.cn/problem/CF1957E)。[cnblogs](https://www.cnblogs.com/Pengzt/p/18668385)。

### Problem

求：$\sum\limits_{i=1}^n\sum\limits_{j=1}^i\left(F(i,j)\bmod j\right)$。

其中 $F(i,j)$ 表示从 $i$ 个数当中选 $j$ 个的不同圆排列数。

最终答案对 $10^9+7$ 取模。 

注意区分题目中的两个取模的位置。

数据范围：$t \le 10^5$，$n \le 10^6$。

### Sol

首先 $F(i, j) = \frac{i!}{(i - j)!j} = \binom ij (j - 1)!$。然后 $(j - 1)! \bmod j$ 只有在 $j$ 是素数或者 $j=4$ 的时候值不为 $0$。$j = 4$ 的时候可以单独算。当 $j \in \text{prime}$ 的时候，$F(i, j) = -\binom ij \bmod j = -\binom{\lfloor i/j \rfloor}{j/j}\times \binom{i \bmod j}{j \bmod j} = -\lfloor \frac ij \rfloor$。现在要求 $\sum\limits_{p \in \text{prime}} ((\sum\limits_{i = 1}^{n} \lfloor \frac{i}{p} \rfloor) \bmod p)$。这个东西直接做是会 T 的，但是 $\lfloor \frac ip \rfloor$ 的总的断点个数是 $\mathcal{O}(n \ln \ln n)$ 的。考虑对这个东西直接线性筛，枚举质数 $p$，然后就是做 $\lfloor \frac np \rfloor$ 段区间加。这里可以直接差分，最后跑一遍前缀和即可。

### Code

 ```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define fi first
#define se second
const int mod = 1e9 + 7;
int vis[1000005], prC, pri[1000005];
ll ans[1000005];
void Init(int n = 1e6) {
	for (int i = 2; i <= n; ++i) {
		if (!vis[i]) pri[++prC] = i;
		for (int j = 1; j <= prC && i * pri[j] <= n; ++j) {
			vis[i * pri[j]] = 1;
			if (i % pri[j] == 0) break;
		}
	}
	vis[4] = 0;
	for (int i = 2; i <= n; ++i) {
		if (vis[i]) continue;
		ll t = i == 4 ? 2 : i - 1;
		for (int j = 1, k = i; k <= n; ++j, k += i) {
			ll w = j * t % i;
			(ans[k] += w) %= mod;
			if (k + i <= n) (ans[k + i] -= w) %= mod;
		}
	}
	for (int i = 1; i <= n; ++i) (ans[i] += ans[i - 1] + mod) %= mod;
	for (int i = 1; i <= n; ++i) (ans[i] += ans[i - 1] + mod) %= mod;
}
int n;
void Solve() {
	scanf("%d", &n);
	printf("%lld\n", ans[n]);
}
int main() {
	Init();
	int T;
	scanf("%d", &T);
	while (T--)
		Solve();
	return 0;
}
 ```

---

## 作者：yyz1005 (赞：1)

定义 $P$ 是素数集。

注意到：

$$\sum\limits_{i=1}^n\sum\limits_{j=1}^i\left(C(i,j)\bmod j\right) = \sum\limits_{i=1}^n\sum\limits_{j=1}^i\left(C_i^{j}\cdot (j-1)!\bmod j\right)$$

由威尔逊定理：$(p-1)! \bmod p = -1 \Leftrightarrow p \in P$。

若 $p=4,(p-1)! \bmod p = 2$。

若 $p \not\in P \cap p \not= 4$，设 $p = p_0 \cdot d$。

$p_0$ 为 $p$ 的最小素因子，$p_0=d \Leftrightarrow p = p_0^2$。

若 $p_0=d$，设 $p = q^2$ 则 $q \in P,q \not=2$。

那么有 $q,2q < p$，故 $p = q^2 \mid q \times 2q,q \times 2q \mid  (p-1)!$，得 $p\mid (p-1)!$。

否则 $p = q_0 \cdot d \mid q_0 \times d,q_0 \times d \mid (p-1)!$，得 $p|\mid (p-1)!$。

综上，记 $f(p) = (p-1)! \bmod p = \begin{cases}-1&p \in P\\2 & p = 4\\0 & \text{otherwise}\end{cases}$。

不妨交换原式求和顺序。

定义 $dp[i] = \sum\limits_{j=1}^i\left(C_i^j\cdot (j-1)!\bmod j\right)$。

只需求 $\sum dp[i]$。

不妨枚举 $j$，$j$ 将对 $dp[j \le i \le n]$ 做 $f(j) \cdot C_i^j \bmod j$ 的贡献。

注意到 $j \in P \Rightarrow C_i^j \bmod j= C_{i \bmod j}^{j \bmod j} \cdot C_{\left[\frac{i}{j}\right]}^{\left[\frac{j}{j}\right]} = \left[\frac{i}{j}\right]$。

考虑到枚举素数 $j$ 再枚举其倍数做差分，大约 $O(n \ln n)$。

[Code](https://codeforces.com/contest/1957/submission/259706601)。

---

## 作者：diqiuyi (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1957E)。

显然题目所求即位 $\sum_{i=1}^n\sum_{j=1}^i (C_i^j(j-1)!\bmod j)$。

就是要求 $s(i)=\sum_{j=1}^i (C_i^j(j-1)!\bmod j)$ 的前缀和。由威尔逊定理可知，只有当 $j$ 是质数或者 $j$ 是 $4$ 的时候，后面那个东西才不为 $0$。我们知道当 $j$ 是质数的时候，$(j-1)! \equiv -1(\bmod\ j)$。所以 $s(i)=\sum_{j\ is\ prime} (-C_i^j\bmod j)+2C_i^4$。

根据卢卡斯定理，$C_i^j \bmod j=C_{\lfloor{\frac{i}{j}}\rfloor}^1C_{i \bmod j}^0=\lfloor{\frac{i}{j}}\rfloor$。

所以 $s(i)=\sum_{j\ is\ prime} (-\lfloor{\frac{i}{j}}\rfloor\bmod j)+2C_i^4$。

这个可以整除分块处理，实现的优秀的话应该是 $O(n\sqrt{n/\log n})$ 的，但是实测过不了。

但是我们可以考虑每个对每个质数 $p$ 进行一个类似分块的操作。即把所有数 $x$ 按照 $\lfloor{\frac{x}{p}}\rfloor$ 分组。然后 $p$ 每个组的 $s$ 的贡献是相同的，相当于进行一个区间加的操作，用差分维护即可。

时间复杂度为 $O(n\log\log n+T)$。

**CODE**
```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define ll long long
#define ull unsigned long long
using namespace std;
const int maxn=1e6,mod=1e9+7;
int t,n,prime[maxn>>1],cnt;
bitset<maxn+5> vis;
ll s[maxn+5];
const __int128 bas=2;
int cn4(int x){
	return bas*x*(x-1)*(x-2)*(x-3)/24%4;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	for(int i=2;i<=maxn;i++){
		if(!vis[i]) prime[++cnt]=i;
		for(int j=1;j<=cnt&&prime[j]*i<=maxn;j++){
			vis[i*prime[j]]=1;
			if(!(i%prime[j])) break;
		}
	}
	for(int i=1;i<=cnt;i++)
		for(int j=1;j*prime[i]<=maxn;j++){
			int l=prime[i]*j,r=min(maxn,l+prime[i]-1);
			s[l]+=(prime[i]-j%prime[i])%prime[i],s[r+1]-=(prime[i]-j%prime[i])%prime[i];
		}
	for(int i=1;i<=maxn;i++)
		s[i]+=s[i-1],s[i]%=mod;
	for(int i=4;i<=maxn;i++)
		s[i]+=cn4(i);
	for(int i=1;i<=maxn;i++)
		s[i]+=s[i-1],s[i]%=mod;
	cin>>t;
	while(t--)
		cin>>n,cout<<(s[n]+mod)%mod<<'\n';
	return 0;
}

---

## 作者：lfxxx (赞：0)

式子就是 $\sum_{i=1}^n \sum_{j=1}^n {i \choose j} (j-1)! \bmod j$，显然 $i < j$ 时里面的式子会是 $0$，所以式子其实是 $\sum_{i=1}^n \sum_{j=1}^i {i \choose j} (j-1)! \bmod j$，第二维脱离了 $n$ 的限制，结合这里没有 $\sum n$ 的限制，可能需要对于每个 $i$ 求出 $\sum_{j=1}^i {i \choose j} (j-1)! \bmod j$ 再去滚前缀和。

$(j-1)! \bmod j$ 使你想起来威尔逊定理的形式，你知道 $j$ 是质数时其是 $j-1$，其他情况下你通过打表发现其大概率是 $0$，我们来说明下这是为什么。

$j = \prod_{i=1}^k p_i^{q_i}$，当 $k>1$ 时你发现所有 $p_i^{q_i}$ 均小于 $j$，因此 $(j-1)! \bmod j = 0$，当 $k = 1$ 时假若 $q_i > 2$，那么 $[1,p_i^{q_i - 1})$ 中一定包含了 $p_i$，而 $p_i \times p_i^{q_i - 1} = p_i^{q_i}$ 故模数也是 $0$，当 $q_i = 2$ 时你发现假若 $(p_i,p_i^2)$ 中存在一个 $p_i$ 的倍数模数也是 $0$，在这个范围中有 $p_i^2 - p_i - 1$ 个数，当 $p_i^2 - p_i - 1 \geq p_i$ 时根据抽屉原理其中必有 $p_i$ 的倍数，当 $p_i^2 - p_i - 1 < p_i$ 时你发现整理得 $(p_i - 1)^2 < 2$，所以 $p_i$ 只能等于 $2$，也就是 $j = 4$。

所以有意义的 $j$ 要么是质数要么是 $4$。

对于质数 $j$ 而言，其对一个 $i$ 的贡献是 $-{i \choose j} \bmod j$，组合数对质数取模直接卢卡斯拆开得到 ${i \bmod j \choose 0} \times {\left\lfloor \frac{i}{j} \right\rfloor \choose 1} = \left\lfloor \frac{i}{j} \right\rfloor \bmod j$，你发现 $\left\lfloor \frac{i}{j} \right\rfloor$ 的取值构成关于 $i$ 的若干连续段，且连续段数量总和等价于埃筛的复杂度也就是 $O(n \log \log n)$，于是考虑对于每个连续段用差分维护即可。

对于 $j = 4$ 而言，直接暴力做即可。

时间复杂度 $O(n \log \log n + t)$。

[代码](https://codeforces.com/contest/1957/submission/293641458)

---

## 作者：arrow_king (赞：0)

第一次独立想出 *2400，发篇题解记录一下。

# 题意

记 $C(n,m)$ 表示从 $n$ 个元素中选出 $m$ 个排成一个圆环的本质不同方案数。给定 $n,m$，求
$$
\sum_{i=1}^n\sum_{j=1}^iC(i,j)\bmod j
$$
在模 $10^9+7$ 意义下的值。多测，$T\le10^5$，$n\le10^6$。

-----

基础数论大合集。

首先我们先将处于“黑箱”状态的 $C$ 拆开成好操作的形式。因为是圆排列，所以我们考虑将环断开成链，有 $m$ 种断开的方式，不能重复计数。因此总方案数就是
$$
C(n,m)\bmod m=\dfrac{A_n^m}{m}=\dbinom nm(m-1)!\bmod m
$$
看到 $(m-1)!\bmod m$ 的式子，自然想到**威尔逊定理**，它可以很快地求出上式的值。
$$
(n-1)!\bmod n=
\begin{cases}
-1,&n\in\mathbb P\\
2,&n=4\\
0,&\text{otherwise.}
\end{cases}
$$
而根据**卢卡斯定理**，$\dbinom nm\bmod m$ 也有很好的形式：
$$
\dbinom nm\equiv\dbinom{\lfloor n/m\rfloor}{\lfloor m/m\rfloor}\cdot\dbinom{n\bmod m}{m\bmod m}\equiv\bigg\lfloor\dfrac nm\bigg\rfloor\pmod m
$$
接下来就是求答案了。记 $c_i=(i-1)!\bmod i$。由于内部式子关系到对 $j$ 取模，因此我们将 $i,j$ 交换枚举顺序。由上面的分析知道 $j$ 取非 $4$ 合数时没有贡献。我们设 $g_i=\sum\limits_{j=1}^i\big\lfloor\frac ij\big\rfloor c_j\bmod j$，那么最后的答案自然是 $\sum\limits_{i=1}^ng_i$。

$g$ 的求值可以采用调和级数枚举倍数的方式求值。我们枚举 $j\in\mathbb P\cup\{4\}$。在 $j=4$ 的时候我们暴力计算，在 $j\neq 4$ 的时候我们发现 $i/j$ 的贡献是一段一段的，所以可以差分维护。复杂度看似是 $O(n\ln n)$，但是这里只枚举了质数，所以复杂度似乎是埃筛的 $O(n\log\log n)$ 的？

# 代码

暴力组合数需要开 `__int128`。

```cpp
il ll calc(ll n) {
	__int128 ans=n*(n-1);
	ans*=n-2;ans*=n-3;ans/=4;
	return ans%4;
}
il void sieve() {
	for(int i=2;i<=n;i++) {
		if(!f[i]) p[++cnt]=i;
		for(int j=1;j<=cnt&&i*p[j]<=n;j++) {
			f[i*p[j]]=1;
			if(i%p[j]==0) break;
		}
	}
	for(int i=1;i<=n;i++) g[i]=(g[i]+calc(i))%mod,g[i+1]=(g[i+1]-calc(i)+mod)%mod;
	for(int j=1;j<=cnt;j++) {
		for(int i=1;p[j]*i<=n;i++) {
			g[p[j]*i]=(g[p[j]*i]+i*(p[j]-1)%p[j])%mod;
			g[p[j]*i+p[j]]=(g[p[j]*i+p[j]]-i*(p[j]-1)%p[j]+mod)%mod;
		}
	}
	for(int i=1;i<=n;i++) g[i]=(g[i-1]+g[i])%mod;
	for(int i=1;i<=n;i++) g[i]=(g[i-1]+g[i])%mod;
}
```

---

## 作者：zzzYheng (赞：0)

#### 题意：

给定 $n$，求：
$$
\sum_{i=1}^{n}\sum_{j=1}^{i} (C(i,j) \bmod j)
$$
其中 $C(i,j)$ 为在 $i$ 个有标号球中选 $j$ 个并排成一个环的方案数。

数据范围：$n \le 10^6$。多组询问，每组数据不超过 $10^5$ 次询问。

#### 思路：

显然 $C(i,j)=\dbinom{i}{j}\cdot (j-1)!$，因此原式等于：
$$
\sum_{i=1}^{n}\sum_{j=1}^{i} [\dbinom{i}{j}\cdot (j-1)! \bmod j]
$$
注意到 $(j-1)!$ 中会包含很多不同因子，因此在大部分情况下 $\dbinom{i}{j}\cdot (j-1)!\bmod j=0$。

具体的，当 $j=4$ 或 $j$ 为质数时贡献不为 $0$。

$j=4$ 的贡献打个表可以发现贡献存在明显的规律，这里略去。

当 $j$ 为质数时，发现 $\dbinom{i}{j}\bmod j$ 和 $(j-1)!\bmod j$  都可以化简，具体的：

- 根据卢卡斯定理，$\dbinom{i}{j}\bmod j=\dbinom{\lfloor i/j\rfloor}{1}\cdot \dbinom{i\bmod j}{0}=\lfloor \dfrac{i}{j} \rfloor$。
- 根据威尔逊定理，$(j-1)!\bmod j=j-1$。

所以原式等于：
$$
\sum_{i=1}^{n}\sum_{j\in P}^{i} (\lfloor\dfrac{i}{j}\rfloor\cdot (j-1) \bmod j)
$$
考虑把 $1\sim 10^6$ 的所有 $n$ 的答案全部求出来，明显这里面存在重复计算，因此我们差分一下，计算 $n-1$ 到 $n$ 答案的增量，为：
$$
\Delta(n)=\sum_{i\in P}^{n}\lfloor\dfrac{n}{i}\rfloor\cdot (i-1)\bmod i
$$
注意到 $\Delta(n-1)$ 和 $\Delta(n)$ 的式子中有不少 $\lfloor\dfrac{n}{i}\rfloor\cdot (i-1)\bmod i$ 的贡献是相同的，只有 $n$ 为 $i$ 的倍数时贡献不同。

因此再差分，去计算 $\Delta(n)$ 的增量 $\delta(n)$，有：
$$
\delta(n)=\sum_{i \in P,i|n} \lfloor\dfrac{n}{i}\rfloor\cdot (i-1)\bmod i-\lfloor\dfrac{n-1}{i}\rfloor\cdot (i-1)\bmod i
$$
因此可以对于每个质数 $i$，枚举其的倍数 $n$，计算 $i$ 对 $\delta(n)$ 的贡献，可以做到时间复杂度 $\Theta(n\log\log n)$。

#### 总结：

这是一道很基础的数学题，需要熟练掌握威尔逊定理和卢卡斯定理，并且要能够熟练运用差分（增量）法来减少重复运算。

---

## 作者：WaterSun (赞：0)

[更好的阅读体验](https://watersun.top/%5B%E9%A2%98%E8%A7%A3%5DCF1957E%20Carousel%20of%20Combinations)

# 思路

首先先把原式中的 $C(i,k)$ 化出来：

$$
C(i,j) \bmod j = \frac{A^i_j}{j} \bmod j = \frac{i(i - 1)\cdots(i - j + 1)}{j} \bmod j = ((j - 1)! \times \lfloor \frac{i}{j} \rfloor) \bmod j
$$

由威尔逊定理，当 $p$ 为质数时：

$$
(p - 1)! \bmod p = p - 1
$$

其次当 $p$ 为非质数时，$p = 4$ 结果为 $2$；其余情况为 $0$。

定义 $dp_i = \sum_{j = 1}^{i}{((j - 1)! \times \lfloor \frac{i}{j} \rfloor \bmod j)}$。最后结果就是 $\sum_{i = 1}^{n}{dp_n}$。

考虑类似埃筛的处理，考虑每一个 $j$ 对于每一个 $dp_i$ 的贡献。发现在 $i \in [k \times j,(k + 1) \times j)$ 时，会为每一个 $dp_i$ 贡献同一个值：$(j - 1)! \times \lfloor \frac{i}{j} \rfloor \bmod j$。

然后区间修改，直接差分维护即可。

**注意特判 $4$。**

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long
#define Add(a,b) (((a) % mod + (b) % mod) % mod)
#define Sub(a,b) ((((a) % mod - (b) % mod) % mod + mod) % mod)

using namespace std;

const int N = 1e6 + 10,mod = 1e9 + 7;
int dp[N];
bool vis[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void init(){
    for (re int i = 2;i <= 1e6;i++){
        if (!vis[i] || i == 4){
            for (re int j = i;j <= 1e6;j += i){
                vis[j] = true;
                int val = j / i;
                if (i == 4) val *= 2;
                else val *= (i - 1);
                val %= i;
                dp[j] = Add(dp[j],val);
                if (i + j <= 1e6) dp[i + j] = Sub(dp[i + j],val);
            }
        }
    }
    for (re int i = 1;i <= 1e6;i++) dp[i] = Add(dp[i - 1],dp[i]);
    for (re int i = 1;i <= 1e6;i++) dp[i] = Add(dp[i - 1],dp[i]);
}

signed main(){
    init();
    int T; T = read();
    while (T--) printf("%lld\n",dp[read()]);
    return 0;
}
```

---

## 作者：Lu_xZ (赞：0)

[Link](https://www.cnblogs.com/Luxinze/p/18162677#e-carousel-of-combinations)

题意：求 $\sum\limits_{i = 1}^n \sum\limits_{j = 1}^i \begin{pmatrix}i\\j \end{pmatrix}(j - 1)! \bmod j$。

$$
\sum\limits_{j = 1}^i \begin{pmatrix}i\\j \end{pmatrix}(j - 1)! \bmod j = \sum\limits_{j = 1}^i \dfrac{i^{\underline{j}}}{j} \bmod j
$$

$j$ 个连续数相乘，$\lfloor\dfrac{i}{j}\rfloor \cdot j$ 一定被 $j$ 整除，剩余数在模 $j$ 意义下依次为 $1, 2\dots ,j - 1$。

所以原式可以写成 $\sum\limits_{j = 1}^i \lfloor\dfrac{i}{j}\rfloor (j - 1)! \bmod j$。

  ---
  
### 威尔逊定理

当 $p$ 为质数时，有
$$
(p - 1) ! \equiv -1 \pmod p
$$

#### 证明

当 $p = 2$ 时，$(2 - 1)! \equiv -1 \pmod 2$。


当 $p > 2$ 时，即证 $\prod\limits_{i = 2}^{p - 2} \equiv 1 \pmod p$。

方程 $x^2 \equiv 1 \pmod p$ 成立当且仅当 $x \equiv 1$ 或 $x \equiv p - 1$。


所以 $\forall x \in [2, p - 2]$，$x^{-1} \in [2, p - 2]$ 且 $x^{-1} \ne x$。

也就是 $\dfrac{n - 3}{2}$ 对数两两匹配互为逆元。

#### 推广


$$
(n - 1)!\equiv
\begin{cases}
-1 \,&n = p_i\\
4 \,& n = 4\\
0 \,&n > 4, \ n \ne p_i \\
\end{cases}
\pmod n
$$

合数 $n = p_1^{\alpha_1}\dots p_k^{\alpha_k}$。


当  $n$ 不为完全平方数时，$p_1 \ne \dfrac{n}{p_1}$ 且 $p_1, \ \dfrac{n}{p_1} < n$，所以 $n \mid (n - 1)!$。


当 $n = p^2$ 时：

如果 $2p < n$，$2p^2 \mid (n - 1)!$。

否则 $n = 4$，$(4 - 1)! \equiv 2 \pmod 4$。

---
  
回到题目。

令 $w_j = (j - 1)! \bmod j$，$f_i = \sum\limits_{j = 1}^i \lfloor\dfrac{i}{j}\rfloor w_j \bmod j$。

枚举 $j = 4$ 或 $j$ 为质数：

枚举 $k$，对于 $i \in [k\cdot j, k\cdot j + j)$，$j$ 对 $f_i$ 有 $k \cdot w_j$ 的贡献，差分实现。

[submission](https://codeforces.com/contest/1957/submission/258382495)

---

## 作者：piggy123 (赞：0)

Lyrically 在学校问我的，那当然要写题解啦！

这是一道多合一题。显然，$C(i,j)=\binom{i}{j}(j-1)!$，我们考虑 $\binom{i}{j}(j-1)!\bmod j$ 的结果是什么。这里可以打个表，得到结论会快很多（我在草稿纸上画了 $n\leq 7$ 的情况）。我们下面通过严谨推导的方式一步步得出结论。

第一部分：$(j-1)!\bmod j$。由威尔逊定理的拓展易得当 $j$ 为质数时，$(j-1)!\equiv j-1\pmod j$；当 $j=4$ 时特判，否则当 $j$ 为其他数时 $(j-1)!\equiv 0\pmod j$。

所以除了特判 $j=4$，我们只需要在意 $j$ 为质数的取值。此时由卢卡斯定理知 $\binom{m}{n}\equiv \binom{1}{\lfloor\frac{n}{m}\rfloor}\times \binom{0}{n\bmod m}\pmod m$。即当 $j$ 为质数时，$C(i,j)\bmod j=((j-1)\lfloor\frac{i}{j}\rfloor)\bmod j$。

之后按题意算贡献即可。注意这个直接做整除分块是根号的，跑不过去，但是如果对于每个质数算贡献就能除以一个 $\log n$，就可以过了。

AC Code:
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll prm[1000005],ans[1000005],sm[1000005],cnt[1000005];
const ll mod=1000000007;

int main() {
	prm[1]=1;
	for (ll i=2; i<=1000000; i++) {
		if (!prm[i]) {
			for (ll j=i*i; j<=1000000; j+=i) {
				prm[j]=1;
			}
		}
	}
	for (ll i=1; i<=1000000; i++) {
		sm[i]=sm[i-1]+(!prm[i]?i:0);
		if (!prm[i]) {
			for (ll j=i; j<=1000000; j+=i) {
				ans[j]+=j/i;
				if (j+i<=1000000)
					ans[j+i]-=j/i;
			}
		}
	}
	for (ll i=1; i<=1000000; i++) {
		ans[i]+=ans[i-1],ans[i]+=mod,ans[i]%=mod;
	}
	for (ll i=1; i<=1000000; i++) {
		if (!prm[i]) {
			for (ll j=i*i; j<=1000000; j++) {
				ans[j]-=(j/i/i)%mod*i%mod;
				ans[j]+=i*(j/i%i==0);
				ans[j]+=mod;
				ans[j]%=mod;
			}
		}
	}
	ll t;
	cin >> t;
	for (ll n=1; n<=1000000; n++) {
		ans[n]=mod-ans[n];
		ans[n]+=sm[n];
		ans[n]%=mod;
		ans[n]+=ans[n-1];
		ans[n]%=mod;
		sm[n]=(n%8>=4&&n%8<=7)*2;
		sm[n]+=sm[n-1];
	}
	while (t--) {
		ll n;
		cin >> n;
		cout<< (ans[n]+sm[n])%mod<<"\n";
	}
	return 0;
}
```

---

## 作者：Shunpower (赞：0)

纯纯小丑题。

## Statement

求 

$$
\sum\limits_{i=1}^n\sum\limits_{j=1}^i (C(i,j)\bmod j)
$$ 

对 $10^9+7$ 取模的值。$C(i,j)$ 表示从 $1\sim i$ 的整数中选出 $j$ 个的圆排列数量。

多组数据。

数据范围：$1\leq T\leq 10^5,1\leq n\leq 10^6$。

## Solution

这 $C(i,j)$ 的皮套的不好，显然 $C(i,j)={i\choose j}(j-1)!$，当然接下来我们在 $\bmod\ j$ 意义下考虑这个事。

后面那个 $(j-1)!\bmod j$ 自然想到威尔逊定理。由于这里 $j$ 不只有质数，我们还要把扩展部分拿出来：

- 对于 $j\in \mathbb P$（$\mathbb P$ 表示质数集），$(j-1)!\equiv j-1\pmod j$。
- 对于 $j\notin \mathbb P$：
	- $j=4$ 时，$(j-1)!\equiv 2\pmod j$。。
   - 其他情况，$(j-1)!\equiv 0\pmod j$。
   
对于一般的威尔逊定理，[OI-wiki 上有证明](https://oi-wiki.org/math/number-theory/wilson/)。

模数非质数的部分是易证的：

> 证明：  
> 若 $j$ 不是质数，则 $j$ 存在至少一对非平凡因子，且都小于 $j$。所以若 $j$ 的某对非平凡因子不相等，则这对因子必然包含在 $(j-1)!$ 中，所以 $(j-1)!$ 可以被 $j$ 整除。  
> 若 $j$ 的所有对非平凡因子都相等，此时 $j$ 是质数的完全平方数，容易发现，对于质数大于 $2$ 的情况，在 $(j-1)!$ 中都至少有两个数为该质数的倍数，所以此时 $(j-1)!$ 也能被 $j$ 整除。  
> 易得 $j=4$ 时，$(j-1)!\equiv 2\pmod j$。  

这样我们就毙掉了所有合数。然后我们考虑把 $4$ 的贡献拆出去，把式子化为：

$$
\begin{aligned}
&\sum\limits_{i=1}^n\sum\limits_{j=1}^i (C(i,j)\bmod j)\\
=&\sum\limits_{i=1}^n(2{i\choose 4}\bmod 4)+\sum\limits_{1\leq j\leq i\land j\in \mathbb P} ({i\choose j}(j-1)\bmod j)
\end{aligned}
$$ 

此时左边已经可以使用前缀和预处理，假设前缀和为 $pre_i$，右边显然观察到一个 Lucas 定理的形式，继续换：

$$
\begin{aligned}
=&\sum\limits_{i=1}^n(2{i\choose 4}\bmod 4)+\sum\limits_{1\leq j\leq i\land j\in \mathbb P} ({i\choose j}(j-1)\bmod j)\\
=&pre_i+\sum\limits_{i=1}^n\sum\limits_{1\leq j\leq i\land j\in \mathbb P} ({i\bmod j\choose j\bmod j}{\left\lfloor\frac{i}{j}\right\rfloor\choose \left\lfloor\frac{j}{j}\right\rfloor}(j-1)\bmod j)\\
=&pre_i+\sum\limits_{i=1}^n\sum\limits_{1\leq j\leq i\land j\in \mathbb P}(\left\lfloor\frac{i}{j}\right\rfloor(j-1)\bmod j)\\
=&pre_i+\sum\limits_{i=1}^n\sum\limits_{1\leq j\leq i\land j\in \mathbb P}(-\left\lfloor\frac{i}{j}\right\rfloor\bmod j)
\end{aligned}
$$ 

接下来我们考虑怎么算后面这个和式。很容易想到枚举 $i,j,\left\lfloor\frac{i}{j}\right\rfloor$ 三者其二来统计。

由于 $n\leq 10^6$，枚举 $i$ 之后再枚举剩下的东西复杂度不太现实，~~我一开始写的根号分治预处理跑了五秒~~，所以我们直接考虑枚举 $j,\left\lfloor\frac{i}{j}\right\rfloor$，枚举过程中保证它们相乘不超过 $n$ 就行。这样枚举的复杂度等价于埃氏筛，也就是 $\mathcal O(n\log\log n)$ 的。

对于一组 $j,k=\left\lfloor\frac{i}{j}\right\rfloor$，可以发现它们的贡献区间是连续的：所有 $[jk,\min(j(k+1)-1,n)]$ 都会枚举到这个 $j$ 并下取整除得这个 $k$。所以我们直接对区间进行区间加，加上这一对的贡献 $j-k \bmod j$ 即可（注意负号建立在 $\bmod\ j$ 意义下，所以要用 $j-k$）。

使用差分维护区间加，最后做一次前缀和就可以得到右边那个和式在每个 $i$ 处的值，再做一次前缀和就可以得到 $n$ 项之和。

区间加和前缀和时注意对 $10^9+7$ 取模。

现在倒回去看怎么算 $pre_i$。$2{i\choose 4}\bmod 4$ 这玩意显然只关心 ${i\choose 4}$ 是奇数还是偶数，如果是奇数就贡献 $2$，是偶数就贡献 $0$。容易发现 ${i\choose 4}=\frac{i(i-1)(i-2)(i-3)}{24}$ 中，上面必然有一个偶数但非 $4$ 的倍数和一个 $4$ 的倍数，下面只有 $3$ 个 $2$ 要除掉，所以我们考虑那个 $4$ 的倍数。如果它除以 $4$ 后为奇数，则 ${i\choose 4}$ 为奇数，否则 ${i\choose 4}$ 为偶数。

容易发现那个 $4$ 的倍数除以 $4$ 就等于 $\left\lfloor\frac{i}{4}\right\rfloor$，所以我们最后 $pre$ 的转移就是这样的：

$$
pre_i\gets pre_{i-1}+2(\left\lfloor\frac{i}{4}\right\rfloor\bmod 2)
$$

我们直接把全部都预处理到 $n=10^6$。答案直接把 $pre_n$ 和差分数组的二次前缀和的第 $n$ 项加一起就完事了。

## Code

talk is cheap.

其实写得有点丑。

```cpp
int tc,n;
ll mod=1e9+7;
int lim;
vector <int> prime;
bool vis[N];
ll pre[N];
ll ans[N];
void sieve(int n=1000000){
    vis[1]=1;
    fr1(i,2,n){
        if(vis[i]) continue;
        prime.pb(i);
        for(ll j=1ll*i*i;j<=n;j+=i) vis[j]=1;
    }
    fr1(i,1,n) pre[i]=pre[i-1]+(i/4%2==1?2:0);
    for(auto i:prime){
        fr1(j,1,n/i){
            int l=i*j,r=min(i*(j+1),n+1);
            ans[l]+=((i-j)%i+i)%i;
            ans[r]-=((i-j)%i+i)%i;
        }
    }
    fr1(i,1,n) (ans[i]+=ans[i-1])%=mod;
    fr1(i,1,n) (ans[i]+=ans[i-1])%=mod;
}
void solve(){
    cin>>n;
    cout<<(pre[n]+ans[n]%mod+mod)%mod<<'\n';
}
int main(){
#ifdef Rain
    freopen("hack.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);
    sieve();
    cin>>tc;
    while(tc--) solve();
    ET;
}
//ETERNAL LOVE FOR Zhang Junhao, Mu Zhicheng and Zuo Hang.
//ALL FOR Zhang Junhao.
```

---

## 作者：_LSA_ (赞：0)

# CF1957E Carousel of Combinations 题解

显然，题目中 
$$C(n,m) = \tbinom{n}{m}\times (m-1)!$$
即 $n$ 个数中选出 $m$ 个数再乘上 $m$ 个数的圆排列。

题目要求的即为
$$\sum_{i=1}^n\sum_{j=1}^i \Big(\tbinom{i}{j}\times (j-1)! \mod j \Big)$$

考虑每一个 $j$ 对答案的贡献，根据威尔逊定理，当 $j$ 为不为质数时，除了 $4$ 以外 $j \mid(j-1)!$ ，即 $j \neq4$ 且 $j \notin Prime$时对答案的贡献为 $0$ 。

对于 $j=4$ 的情况，即 
$$\sum_{i=4}^n\Big(\tbinom{i}{4}\times 3! \mod 4 \Big)$$

对其展开，得到

$$\sum_{i=4}^n\Big(\frac{i \times (i-1) \times (i-2) \times (i-3)}{4} \mod 4 \Big)$$

直接计算每一项然后前缀和即可。注意直接乘可能爆 $\text{long long}$ ，可以分别计算 $\frac{i(i-1)}{2}$ 和 $\frac{(i-2)(i-3)}{2}$ 分别模 $4$ 再相乘。

现在我们来考虑 $j$ 为质数的时候怎么做。

根据威尔逊定理和卢卡斯定理
$$\tbinom{i}{j}\times (j-1)! \equiv \tbinom{\lfloor \frac{i}{j}\rfloor }{\lfloor \frac{j}{j}\rfloor }\times \tbinom{i\mod j}{j \mod j}\times(-1)\equiv-\lfloor \frac{i}{j}\rfloor \pmod j$$

则原式变为
$$\sum_{i=1}^n\sum_{j \in Prime}^i \Big(-\lfloor \frac{i}{j}\rfloor \mod j\Big)$$
我们还是考虑每个 $i$ 的贡献，再前缀和。

考虑递推，开个桶维护每个质数当前的 $\lfloor \frac{i}{j}\rfloor$ 以及它们的和，发现每个 $i$ 相对 $i-1$ 只有 $i$ 的质因数的 $\lfloor \frac{i}{j}\rfloor$ 发生改变。我们只需对这些数的贡献进行修改即可。

预处理完上述过程，对于每一个询问，$O(1)$ 输出即可。

总时间复杂度 $O(n\sqrt n+T)$，瓶颈在分解质因数，但跑不满，实测可以通过。

## 部分代码
```cpp
const int mod = 1e9+7;
const int N = 1e6+10;
int pr[N],tot;
bool vis[N]; 
ll f[N],g[N],cnt[N],sum;
inline void divide(int x){
	for(int i=1;i<=tot&&pr[i]*pr[i]<=x;i++){
		if(x % pr[i] == 0){
			sum -= cnt[pr[i]];
			cnt[pr[i]]--;
			if(cnt[pr[i]] < 0) cnt[pr[i]] += pr[i];
			sum += cnt[pr[i]];
			while(x % pr[i] == 0) x /= pr[i];
		} 
	}
	if(x > 1){
		sum -= cnt[x];
		cnt[x]--;
		if(cnt[x] < 0) cnt[x] += x;
		sum += cnt[x];
	}
	sum = (sum%mod+mod)%mod;
}
inline void init(int M = 1e6){
	for(int i=2;i<=M;i++){
		if(!vis[i]) pr[++tot] = i;
		for(int j=1;j<=tot&&i*pr[j]<=M;j++){
			vis[i*pr[j]] = true;
			if(i % pr[j] == 0) break;
		} 
	}
	for(int i=2;i<=M;i++){
		divide(i);
		f[i] = (f[i-1]+sum)%mod;
	}//质数的贡献
	for(ll i=4;i<=M;i++){
		ll x = i*(i-1)/2%4,y = (i-2)*(i-3)/2%4;
		x = x*y%4;
		g[i] = (g[i-1]+x)%mod;
	}//4的贡献
}
```

---

## 作者：未来姚班zyl (赞：0)

很好的一道题，让我差 9 min AK。

## 题目大意

设 $f(i,j)$ 为从 $i$ 个数中选 $j$ 个数组成圆排列的个数，多次给定 $n$，求下列式子的值，对 $10^9+7$ 取模：

$$\sum\limits_{i=1}^n\sum\limits_{j=1}^i(f(i,j)\bmod j)$$

## 题目分析

作为一个像我一样数论学得**一坨**的选手，如何在赛时**秒掉**这道题捏？

观察式子，有一个非常突出的地方：$\mod j$。这暗示我们从 $j$ 的角度分析。

回来看 $f(i,j)$ 的意义，相当于 $\frac{A_{i}^{j}}{j}=\frac{(i-j+1)(i-j+2)\dots(i-1)i}{j}$。

看分子上那一串，是 $j$ 个连续的数相乘，显然有且仅有一个数是 $j$ 的倍数。我们只需要求在模 $j$ 意义下的取值。则让那个 $j$ 的倍数除以 $j$，剩下 $j-1$ 个数显然在模 $k$ 意义下同余于 $(j-1)!$，这是一个定值！所以 $f(i,j) \bmod j$ 只与那个 $j$ 的倍数有关，这分成了 $\frac{n}{j}$ 个值相等的区间，暴力枚举并用线段树维护即可 $O(n\log^2n)$ 预处理，并且每次单 $\log$ 查询答案。

问题就只剩下 $(j-1)!\bmod j$ 了。直觉告诉我们这个式子等于 $0$ 的概率很大，具体问题具体分析。

- 如果 $j$ 是一个合数，且不是一个质数的平方，那么 $j$ 最小的非 $1$ 的因数和最大的非 $j$ 的因数都会出现一次，乘起来就消成 $0$ 了。

- 如果 $j$ 是一个质数的平方，设这个质数为 $p$，则 $p$ 和 $2p$ 就都会出现，式子消为 $0$，除了 $4=2\times 2$，这时式子的取值为 $2$。

- 如果 $j$ 是一个质数，手玩一下小的质数发现式子的值总是 $j-1$。然后打表发现对于 $10^3$ 以内的质数，式子的值都是 $j-1$。在赛时，直接猜想所有质数都成立，结果就过了，复杂度 $O(n\log^2 n+T\log n)$。但抱着学习的心态，我们可以上网查阅发现这是一个早已存在的定理：[威尔逊定理](https://oi-wiki.org/math/number-theory/wilson/)。

所以这题似乎只会排列组合就可以过了 awa。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R L|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,N-5
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N =1e6+5,M=4e6+5,inf=(1LL<<31)-1,mod=1e9+7;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,int b){if(!b)return 1;int c=qp(a,b>>1);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
struct seg{
	int w,laz;
}xd[N<<2];
inline void insert(int x,int l,int r,int k){
	add(xd[x].w,mul(r-l+1,k)),add(xd[x].laz,k);
}
inline void getup(int x){
	xd[x].w=Add(xd[L].w,xd[R].w);
}
inline void pushdown(int x,int l,int r){
	insert(lc,xd[x].laz),insert(rc,xd[x].laz);xd[x].laz=0;
}
inline void modify(int x,int l,int r,int Ll,int Rr,int k){
	if(OK)return insert(x,l,r,k),void();
	pushdown(x,l,r);
	if(Ll<=mid)modify(lc,Ll,Rr,k);
	if(Rr>mid)modify(rc,Ll,Rr,k);
	getup(x);
}
inline int query(int x,int l,int r,int Ll,int Rr){
	if(OK)return xd[x].w;
	pushdown(x,l,r);
	if(Rr<=mid)return query(lc,Ll,Rr);
	if(Ll>mid)return query(rc,Ll,Rr);
	return Add(query(lc,Ll,Rr),query(rc,Ll,Rr));
}
bool vis[N];
int p[N],cnt;
inline void prep(){
	rep(i,2,N-5){
		if(!vis[i])p[++cnt]=i;
		for(int j=1;j<=cnt&&p[j]*i<=N-5;j++){
			vis[p[j]*i]=1;
			if(i%p[j]==0)break;
		}
	}
	rep(j,1,N-5){
		int W;
		if(!vis[j])W=j-1;
		else if(j==4)W=2;
		else continue;
		for(int s=j,c=1;s<=N-5;s+=j,c++){
			modify(Root,s,min(N-5,s+j-1),W*c%j);
		}
	}
}
inline void Main(){
	cout <<query(Root,1,read())<<'\n';
}
signed main(){
	prep();
	int T=read();
	while(T--)Main(); 
	return 0;
}
```

补充一下，只用二维差分我们就可以将复杂度降为 $O(n\log n+T)$。补充代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R L|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,N-5
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N =1e6+5,M=4e6+5,inf=(1LL<<31)-1,mod=1e9+7;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,int b){if(!b)return 1;int c=qp(a,b>>1);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int a[N],p[N],cnt;
bool vis[N];
inline void prep(){
	rep(i,2,N-5){
		if(!vis[i])p[++cnt]=i;
		for(int j=1;j<=cnt&&p[j]*i<=N-5;j++){
			vis[p[j]*i]=1;
			if(i%p[j]==0)break;
		}
	}
	rep(j,1,N-5){
		int W;
		if(!vis[j])W=j-1;
		else if(j==4)W=2;
		else continue;
		for(int s=j,c=1;s<=N-5;s+=j,c++)add(a[s],W*c%j),red(a[min(N-5,s+j-1)+1],W*c%j);
	}
	rep(i,1,N-5)add(a[i],a[i-1]);
	rep(i,1,N-5)add(a[i],a[i-1]);
}
inline void Main(){
	cout <<a[read()]<<'\n';
}
signed main(){
	prep();
	int T=read();
	while(T--)Main(); 
	return 0;
}
```

---

## 作者：__int128__CoCo (赞：0)

原题解少打了个 “$\cdots$” 符号，担心误导。重发了……

难得的 $E$ 位置简单题，国内学生应该都会吧？

## 题意

计算 $\sum_{i = 1}^{n} \sum_{j = 1}^{i} C(i, j) \bmod j$ 。

## 题解

其中 $C(i, j)$ 是将 $j$ 个数循环排列的方案数（注意不是组合数）。

《组合数学》原书第五版（就是威斯康星的那本黑皮书）的第二章有这个例题，结论为 $C(i, j) = \frac{P_{i}^{j}}{j} = \frac{i!}{j(i - j)！}$ 。

组合证明很简单。如果对群论了解的话，可以看这里的群论证明（主要是用群论证明，这个公式会很好记）。

**证明：** 

每个线性排列显然属于一个置换群（你可以认为任意排列如果经过旋转能变成一样，则这些排列的集合构成一个置换群）。

每个置换群的大小是显然的 $j$ （这很显然）。

于是循环排列的个数为 $\frac{i
!}{j(i - j)!}$ 。

$\square$

说大白话就是出题人打算要我们计算 $\sum_{i = 1}^{n} \sum_{j = 1}^{i} \frac{i!}{j(i - j)!} \bmod j$ 。

这个公式不好看，把它展开：$\sum_{i = 1}^{n} \sum_{j = 1}^{i} \frac{i \times (i - 1) \times (i - 2) \times \cdots \times (i - j + 1) }{j}$ 。

根据上面的组合意义，分子 $j$ 一定是分母 $i \times (i - 1) \times (i - 2) \times \cdots \times  (i - j + 1)$ 的约数。

实际上只需观察三点：

1. 连续 $j$ 个数在 $\bmod j$ 意义下构成 $j$ 的一个剩余系（即这连续 $j$ 个数 $\bmod j$ 后取遍 $0 \sim j - 1$）。

2. 由 $1$ ，分母仅有一个数 $j$ 的倍数。

3. 不大于 $i$ 的 $j$ 的最大倍数为 $\lfloor \frac{i}{j} \rfloor j$ 。

于是我们要求的是 $\sum_{i = 1}^{n} \sum_{j = 1}^{i} (j - 1)! \lfloor \frac{i}{j} \rfloor \bmod j$ 。

$(j - 1)! \bmod j$ 是 Wilsons 定理，结论是：

1. 若 $j$ 是质数， $(j - 1)! \bmod j = -1$ 。

2. 若 $j = 4$ ， $(j - 1)! \bmod j = 2$ 。

3. 若 $j$ 是其他， $(j - 1)! \bmod j = 0$ 。

**证明：**

1. 若 $j$ 是合数
	1. 若 $j = 1$ 。显然 $0! \bmod 1 = 0$ 。 
    2. 若 $j = 4$ 。显然 $(j - 1)! \bmod j = 2$ 。
    3. 若 $j > 4$ 且 $j$ 是完全平方数。设 $j = a^{2}$ ，显然有 $a < 2a < a^{2}$ 。则 $(j - 1)! = (j - 1) \times \cdots \times 2a \times \cdots \times a \times \cdots \times 1 \Rightarrow j \mid (j - 1)!$ 。于是 $(j - 1)! \bmod j = 0$ 。
    4. 若 $j$ 是非完全平方数。设 $j = ab\ s.t.\ 1 < a < b < j$。则 $(j - 1)! = (j - 1) \times \cdots \times b \times \cdots a \times \cdots 1 \Rightarrow j \mid (j - 1)!$ 。于是 $(j - 1)! \bmod j = 0$ 。
2. 若 $j$ 是质数
	1. 若 $j = 2$ ，显然 $1! \bmod 2 = 1$ 。
    2. 若 $j$ 是奇质数，由 $gcd(j - 1, j) = 1$ 则 $j$ 存在逆元。
    	1. 考虑逆元是自己的情况，$x^{2} \equiv 1 (\bmod j) \Rightarrow (x + 1)(x - 1) \equiv 1 (\bmod j) \Rightarrow x = \pm 1$ 。
        2. 这意味着 $2 \sim j - 2$ 的逆元不是自己。因为模意义下的**逆元存在且唯一**（为什么模意义下的逆元存在且唯一……这里就不证了，写不下）。与 $i$ 是 $2 \sim j - 1$ 可以分为 $\frac{j - 3}{2}$ 组，每组的乘积为 $1$ ，于是 $(j - 2)! \bmod j = 1$ ，两边乘以 $j - 1$ ，即得到 $(j - 1)! \bmod j = - 1$ （$j - 1$ 在 $\bmod j$ 意义下也是 $-1$ ）。

$\square$

先设 $w(j) = (j - 1)! \bmod j$ 。

再设 $f(n) = \sum_{i = 1}^{n} \sum_{j = 1}^{i} \lfloor \frac{i}{j} \rfloor w(j) \bmod j$ 。

显然有递推式 $f(n) = f(n - 1) + \sum_{j = 1}^{n} \lfloor \frac{i}{j} \rfloor w(j) \bmod j$ 。

再设 $g(n) = \sum_{j = 1}^{n} \lfloor \frac{i}{j} \rfloor w(j) \bmod j$ 。

于是有递推关系 $f(i) = f(i - 1) + g(i)$ 。

于是只需要快速求出 $g(i)$ ，便可以线性递推出 $f(n)$ 。

考虑 $g(i)$ 如何求？

由 Wilsons 定理，对 $g$ 数组**有贡献的数字**仅有“质数”和 $4$ 。现在将所有 $\leq n$ 的质数和 $4$ 加入集合 $\mathbb{S}$ 。

单独考虑任意一个 $x$ 满足 $x \in \mathbb{S}$ ，对 $g(i)$ 的贡献为 $\lfloor \frac{i}{x} \rfloor w(x) \bmod x$ 。

看这个东西 $\sum \lfloor \frac{C}{x} \rfloor$ 或者这个东西 $\sum \lfloor \frac{x}{C} \rfloor$ ，这些是啥啊？很常见的答案会形成连续的分段。

$w(x)$ 可以看成常数，那是不是说 $x$ 对 $g$ 数组的贡献是分段连续的？

举个例子：


对 $i \in [1, n]$ ，只看前面的系数 $\lfloor \frac{1}{x} \rfloor, \lfloor \frac{2}{x} \rfloor, \lfloor \frac{3}{x} \rfloor, \cdots, \lfloor \frac{n}{x} \rfloor$ 。

显然结果是分段的，是连续的 $0, 1, 2, \cdots, \lfloor \frac{n}{x} \rfloor$ 。

更具体的：

1. $\lfloor \frac{1}{x} \rfloor \sim \lfloor \frac{x - 1}{x} \rfloor$ 的结果为 $0$ 。

2. $\lfloor \frac{x}{x} \rfloor \sim \lfloor \frac{2x - 1}{x} \rfloor$ 的结果为 $1$ 。

3. $\lfloor \frac{2x}{x} \rfloor \sim \lfloor \frac{3x - 1}{x} \rfloor$ 的结果为 $2$ 。

4. ...

5. $\lfloor \frac{\lfloor \frac{n}{x} \rfloor n}{x} \rfloor \sim \lfloor \frac{n}{x} \rfloor$ 的结果为 $\lfloor \frac{n}{x} \rfloor$ 。

实际上，虽然我们只观察了系数，但我们不打算关心具体结果，我们只关心 $x$ 对 $g$ 的贡献是分段连续的。即对于某个 $x$ ，$kx \sim (k + 1)x - 1$ 具有相同贡献。

我们可以利用差分计算贡献，比如写出类似如下的**伪代码**（因为我不保证这段代码可以编译）算出 $g$ 的差分数组的贡献。

```
for i in range(x, n + 1, x) :
	g[i] += calc(i / x)
    g[i + x] -= clac(i / x)
```

遍历 $\mathbb{S}$ 的每个元素，具体复杂度不太会算，但：

首先是显然应该是低于 $\sum_{i = 1}^{n} \frac{n}{i} = O(n \log n)$ 的。

其次，这和埃氏筛的做法几乎一致，大可以猜测复杂度为 $O(n \log \log n)$ 。

最后我们对 $g$ 的差分数组求和，就得到了 $g$ 数组。至此，本题完全被解决。

## 代码
```
#include <bits/stdc++.h>

typedef long long ll;

// ~~ SEG STARST

// ~~ SEG END
const int MOD = 1E9 + 7;
const int N = 1E6 + 10;
int g[2 * N], f[2 * N];
int p[N], pr[N / 10], tot;
struct EulerSeive {
    EulerSeive() {
        tot = 0;
        for (int i = 0; i < N; i++) p[i] = 0;
        for (int i = 2; i < N; i++) {
            if (!p[i]) p[i] = i, pr[++tot] = i;
            for (int j = 1; j <= tot && i * pr[j] < N; j++) {
                p[i * pr[j]] = pr[j];
                if (p[i] == pr[j]) break;
            }
        }
    }
};

void solve() {
    int n; std::cin >> n;
    std::cout << f[n] << "\n";
}
signed main() {
#ifndef ONLINE_JUDGE
freopen("IO/in", "r", stdin); freopen("IO/out", "w", stdout);
#endif 
    std::cin.tie(0); std::ios::sync_with_stdio(false);
    EulerSeive __init_EulerSeive;
    
    std::vector<int> S;
    S.push_back(4);
    for (int i = 1; i <= tot; i++) S.push_back(pr[i]);

    for (auto x : S) {
        int pc = x;
        auto calc = [&](int v) -> int {
            if (x == 4) return 2 * v % 4;
            else return (-v % x + x) % x;
        };
        for (int i = pc; i < N; i += pc) {
            int tmp = calc(i / pc);
            g[i] = (g[i] + tmp) % MOD;
            g[i + pc] = ((g[i + pc] - tmp) % MOD + MOD) % MOD;
        }
    }

    for (int i = 1; i < N; i++) {
        g[i] = (g[i] + g[i - 1]) % MOD;
    }
	for (int i = 1; i < N; i++) {
        f[i] = (f[i - 1] + g[i]) % MOD;
    }
    
    int _ = 1; std::cin >> _;
    while (_--) { solve(); }
	return 0;
}
```

---

## 作者：DerrickLo (赞：0)

记 $f(x)=\displaystyle{\sum_{i=1}^{x}\sum_{j=1}^{i}C(i,j)\bmod j}$，$g(x)=\displaystyle{\sum_{j=1}^{x}C(x,j)\bmod j}$。那么很显然 $f(x)=\displaystyle{\sum_{i=1}^{x}g(i)}$，那么我们如果需要求出 $f(n)$ 只需要求出 $g(1)$ 到 $g(n)$。

很显然的一点是 $C(i,j)=\dbinom{i}{j}\times (j-1)!$，那么我们考虑对于 $j$ 为合数且 $j\neq 4$ 的情况，$(j-1)!\bmod j$ 必然等于 $0$，即 $C(i,j)\bmod j=0$。

那么我们只需要考虑 $j$ 为质数或 $j=4$ 的情况。首先考虑 $j$ 为质数，由威尔逊定理可以得到 $(j-1)!\equiv -1(\bmod \space j)$，那么 $C(i,j)\equiv -\dbinom{i}{j}(\bmod\space j)$，而又由卢卡斯定理得：

$$\dbinom{i}{j}\equiv\dbinom{i/j}{j/j}\dbinom{i\bmod j}{j\bmod j}\equiv\dbinom{i/j}{1}\equiv\lfloor\frac{i}{j}\rfloor(\bmod\space j)$$

考虑枚举所有质数 $j$，对于任何 $i\ge j$，$g(i)\leftarrow g(i)+(-\lfloor\frac{i}{j}\rfloor\bmod j)$，我们发现后面这个式子对于 $i\in [k\times j,(k+1)\times j)$ 是相同的，那么我们只需要枚举 $k$，然后对区间 $[k\times j,(k+1)\times j)$ 加上相同的数，这可以使用差分维护。

而 $j=4$ 的情况，可以直接特判。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
int t,n,isp[1000005],pr[1000005],cnt,f[1000005],cha[1000005];
signed main(){
	cin>>t;
	for(int i=2;i<=1000000;i++)isp[i]=1;
	for(int i=2;i<=1000000;i++){
		if(isp[i]){
			pr[++cnt]=i;
			for(int j=i*i;j<=1000000;j+=i)isp[j]=0;
		}
	}
	for(int i=1;i<=cnt;i++){
		for(int j=pr[i];j<=1000000;j+=pr[i]){
			int kk=(j/pr[i])%pr[i]*(pr[i]-1)%pr[i];
			cha[j]+=kk,cha[j]%=mod;
			if(j+pr[i]<=1000000)cha[j+pr[i]]-=kk,cha[j+pr[i]]%=mod;
		}
	}
	for(int i=1;i<=1000000;i++)f[i]=(f[i-1]+cha[i])%mod+mod,f[i]%=mod;
	for(int i=4;i<=1000000;i++)if(i*(i-1)%16*(i-2)%16*(i-3)%16!=0)f[i]+=2;
	for(int i=1;i<=1000000;i++)f[i]+=f[i-1],f[i]%=mod;
	while(t--)cin>>n,cout<<f[n]<<"\n";
}
```

---

