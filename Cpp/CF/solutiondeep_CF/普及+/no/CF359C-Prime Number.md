# 题目信息

# Prime Number

## 题目描述

Simon has a prime number $ x $ and an array of non-negative integers $ a_{1},a_{2},...,a_{n} $ .

Simon loves fractions very much. Today he wrote out number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF359C/30ceed91a13d03a8240cb0eaa60aa832738192a0.png) on a piece of paper. After Simon led all fractions to a common denominator and summed them up, he got a fraction: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF359C/e0810919ce9aff20137654b00c598ccaa33ece8d.png), where number $ t $ equals $ x^{a_{1}+a_{2}+...+a_{n}} $ . Now Simon wants to reduce the resulting fraction.

Help him, find the greatest common divisor of numbers $ s $ and $ t $ . As GCD can be rather large, print it as a remainder after dividing it by number $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

In the first sample ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF359C/a1e2654626975b2109236cae030121c98f55e9d0.png). Thus, the answer to the problem is $ 8 $ .

In the second sample, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF359C/21aa04c7cee2f3b67d81ff94d48ffd8a4add7ce1.png). The answer to the problem is $ 27 $ , as $ 351=13·27 $ , $ 729=27·27 $ .

In the third sample the answer to the problem is $ 1073741824 mod 1000000007=73741817 $ .

In the fourth sample ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF359C/b75d78ae6544e1f3836b40eca1b29ba08f0f671d.png). Thus, the answer to the problem is $ 1 $ .

## 样例 #1

### 输入

```
2 2
2 2
```

### 输出

```
8
```

## 样例 #2

### 输入

```
3 3
1 2 3
```

### 输出

```
27
```

## 样例 #3

### 输入

```
2 2
29 29
```

### 输出

```
73741817
```

## 样例 #4

### 输入

```
4 5
0 0 0 0
```

### 输出

```
1
```

# AI分析结果

### 题目内容
# 质数

## 题目描述
西蒙有一个质数$x$和一个非负整数数组$a_{1},a_{2},\cdots,a_{n}$。

西蒙非常喜欢分数。今天，他在一张纸上写下了数字$\sum_{i = 1}^{n}\frac{1}{x^{a_{i}}}$。在西蒙将所有分数化为同分母并求和后，他得到了一个分数：$\frac{s}{t}$，其中$t = x^{a_{1}+a_{2}+\cdots+a_{n}}$。现在西蒙想化简这个结果分数。

帮助他，找出数字$s$和$t$的最大公约数。由于最大公约数可能相当大，将其对数字$1000000007$（$10^{9}+7$）取余后输出。

## 说明/提示
在第一个样例中，$\sum_{i = 1}^{2}\frac{1}{2^{2}}=\frac{1}{4}+\frac{1}{4}=\frac{2}{4}$，通分求和后为$\frac{2 + 2}{2^{4}}=\frac{4}{16}$。因此，该问题的答案是$8$。

在第二个样例中，$\sum_{i = 1}^{3}\frac{1}{3^{i}}=\frac{1}{3}+\frac{1}{9}+\frac{1}{27}=\frac{9 + 3+1}{27}=\frac{13}{27}$，通分求和后为$\frac{3^{5}+3^{4}+3^{3}}{3^{6}}$。该问题的答案是$27$，因为$351 = 13×27$，$729 = 27×27$。

在第三个样例中，问题的答案是$1073741824\ mod\ 1000000007 = 73741817$。

在第四个样例中，$\sum_{i = 1}^{5}\frac{1}{4^{0}}=\frac{1}{1}+\frac{1}{1}+\frac{1}{1}+\frac{1}{1}+\frac{1}{1}=\frac{5}{1}$，通分求和后为$\frac{5}{4^{0}}$。因此，该问题的答案是$1$。

## 样例 #1
### 输入
```
2 2
2 2
```
### 输出
```
8
```

## 样例 #2
### 输入
```
3 3
1 2 3
```
### 输出
```
27
```

## 样例 #3
### 输入
```
2 2
29 29
```
### 输出
```
73741817
```

## 样例 #4
### 输入
```
4 5
0 0 0 0
```
### 输出
```
1
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是围绕求通分后分子$s=\sum_{i = 1}^{n}x^{sum - a_{i}}$（其中$sum=\sum_{i = 1}^{n}a_{i}$）与分母$t = x^{sum}$的最大公约数展开。因为$x$是质数，所以最大公约数必然是$x$的某次方。
 - **思路方面**：多数题解先考虑找出分子中$x$的幂次的最小值，但发现简单取最小值在某些情况下（如$a_i$有重复值时）不正确，还需要进一步处理分子各项合并后可能产生的新的$x$的幂次。
 - **算法要点**：涉及快速幂计算，因为$x$和幂次可能很大，需要用快速幂高效计算$x$的幂对$1000000007$取余的结果；还需要统计$x$的幂次相同的项的个数，并处理这些个数中$x$的因数个数。
 - **解决难点**：难点在于如何全面考虑分子各项合并后$x$的幂次变化。例如在某些情况下，简单取分子中$x$幂次最小值作为最大公约数中$x$的幂次是错误的，需要动态调整。

### 所选的题解
 - **作者：是个汉子 (赞：4) - 4星**
    - **关键亮点**：思路清晰，详细阐述了从错误思路到正确思路的转变过程，即不仅要找$a_i$的最小值，还要考虑指数变为$0$的数字之和是否是$x$的倍数。代码实现中通过排序和循环不断更新最小因子以及处理指数为$0$的情况。
    - **个人心得**：作者分享了自己一开始错误的思路，以及被样例1否定后发现新问题的过程。
    - **核心代码片段**：
```c++
ll fpow(ll a,ll b){
    ll res=1;
    while(b){
        if(b&1) res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}

ll calc(ll x,ll y){
    ll res=0;
    while(x&&(x%y==0)){
        res++;
        x/=y;
    }
    return res;
}

int main(){
    scanf("%lld%lld",&n,&x);
    for(int i=0;i<n;i++){
        scanf("%lld",&a[i]);
        sum+=a[i];
    }
    for(int i=0;i<n;i++)
        num[i]=sum-a[i];
    sort(num,num+n);
    ll tot=1,now=num[0],tmp;
    int pos=0;
    while(233){
        while(pos+1<n&&num[pos+1]-cnt==now) tot++,pos++;
        cnt+=now;
        if((tot%x)||(now==0)){
            tmp=min(sum,cnt);
            ll ans=fpow(x,tmp);
            printf("%lld\n",ans);
            break;
        }
        now=calc(tot,x);
        if(pos+1<n) now=min(now,num[pos+1]-cnt);
        for(int i=1;i<=now;i++) tot/=x;
    }
    return 0;
}
```
核心实现思想：`fpow`函数实现快速幂计算。`calc`函数计算一个数中包含另一个数作为因子的个数。主函数中先计算数组和及各项通分后的幂次，排序后通过循环不断更新最小幂次`now`和相同幂次的个数`tot`，根据`tot`是否为$x$的倍数等条件调整`now`，最终计算出结果。
 - **作者：weihaozhen2010 (赞：1) - 4星**
    - **关键亮点**：先清晰地分析出通分后的分子分母形式，指出最初只取分子幂次最小值的错误，然后给出修正方法，即化简分子后再看能否从化简后的系数中提取出$x$，并注意结果不能超过分母的幂次。
    - **核心代码片段**：
```c++
ll qpow(ll a,ll b, ll p)
{
    ll ans=1,base=a;
    while(b)
    {
        if(b&1) ans=(ans*base)%p;
        base*=base;
        base%=p;
        b>>=1;
    }
    return ans;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>x;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) sum+=a[i];
    for(int i=1;i<=n;i++) f[i]=sum-a[i];
    for(int i=1;i<=n;i++) mn=min(mn,f[i]);
    num=qpow(x,mn,MOD);
    for(int i=1;i<=n;i++)
    {
        if(f[i]>mn) val+=qpow(x,(f[i]-mn),MOD);
        else val++;
    }
    if(val>=x)
    {
        ll p=0;
        while(val%x==0)
        {
            val/=x;
            p++;
        }
        if(mn+p>sum) mn=sum;
        else mn+=p;
    }
    cout<<qpow(x,mn,MOD);
    return 0;
}
```
核心实现思想：`qpow`函数实现快速幂。主函数中先计算数组和及各项通分后的幂次，找到最小幂次`mn`，计算出初步的最大公约数`num`。然后通过循环计算化简分子后的系数`val`，若`val`大于等于$x$，则从`val`中提取$x$，更新`mn`，最后输出结果。
 - **作者：yuhaocheng (赞：0) - 4星**
    - **关键亮点**：从回忆通分过程入手，逐步分析出简单思路的错误，提出用优先队列维护$x$的幂次及其个数，通过不断合并相同幂次项并处理个数中$x$的因数来正确计算最大公约数。
    - **核心代码片段**：
```cpp
struct Number {
    int k; 
    int cnt; 
    bool operator>(const Number &_x) const { 
        return k > _x.k;
    }
};

priority_queue<Number, vector<Number>, greater<Number>> q;

int count(int a, int &b) { 
    int res = 0;
    while (b && b % a == 0) { 
        res++; 
        b /= a; 
    }
    return res;
}

signed main() {
    faster_io(); 
    cin >> n >> x;
    for (int i = 1; i <= n; i++) { 
        cin >> a[i];
    }
    int sum = 0;
    for (int i = 1; i <= n; i++) { 
        sum += a[i];
    }
    for (int i = 1; i <= n; i++) { 
        b[i] = sum - a[i];
    }
    { 
        int tmp = 1;
        b[0] = -1;
        for (int i = n - 1; i >= 0; i--) { 
            if (b[i]!= b[i + 1]) {
                q.push({b[i + 1], tmp});
                tmp = 0; 
            }
            tmp++; 
        }
    }
    int ans = 0;
    { 
        while (!q.empty()) {
            Number f = q.top(); 
            q.pop();
            while (!q.empty() && q.top().k == f.k) { 
                f.cnt += q.top().cnt; 
                q.pop();
            }
            ans = f.k; 
            int tmp = count(x, f.cnt); 
            if (tmp) {
                q.push({f.k + tmp, f.cnt});
            } else {
                break;
            }
        }
    }
    ans = min(ans, sum); 
    cout << qpow(x, ans, MOD) << endl;
}
```
核心实现思想：定义`Number`结构体表示$x$的幂次及其个数，`count`函数计算一个数中包含另一个数作为因子的个数。主函数中先计算数组和及各项通分后的幂次，统计相同幂次的个数并放入优先队列。通过循环取出最小幂次项，合并相同幂次项，处理个数中的$x$因子，更新答案，最后取答案与分母幂次的最小值并输出。

### 最优关键思路或技巧
利用$x$是质数这一特性，将求最大公约数问题转化为求$x$的幂次问题。通过统计分子中$x$的相同幂次项的个数，并处理这些个数中$x$的因数，动态调整最大公约数中$x$的幂次。在实现过程中，快速幂算法用于高效计算$x$的幂对大数取余的结果。

### 可拓展之处
同类型题通常围绕分数化简、数论中最大公约数与质数相关性质展开。类似算法套路是遇到求含质数底数的幂运算结果的最大公约数问题，优先考虑幂次的分析与处理，结合快速幂优化计算。

### 推荐题目
 - [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)：通过枚举因数，结合最大公约数和最小公倍数的关系求解，涉及数论基础和枚举技巧。
 - [P2613 【模板】有理数取余](https://www.luogu.com.cn/problem/P2613)：与本题类似，涉及分数运算及取余，需要运用数论知识如逆元来解决。
 - [P1572 计算分数](https://www.luogu.com.cn/problem/P1572)：同样是分数运算问题，通过模拟分数的加、减、乘、除运算，加深对分数运算和数论知识的理解。

### 个人心得摘录与总结
 - **作者：是个汉子**：分享了自己从错误思路（简单找$a_i$最小值来确定最大公约数中$x$的幂次）到发现问题（样例1不通过，意识到指数为$0$的数字之和可能是$x$的倍数）并修正思路的过程，强调了样例对调试和发现问题的重要性。 

---
处理用时：121.31秒