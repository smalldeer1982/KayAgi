# [USACO4.1] 麦香牛块Beef McNuggets

## 题目描述

农夫布朗的奶牛们正在进行斗争，因为它们听说麦当劳正在考虑引进一种新产品：麦香牛块。奶牛们正在想尽一切办法让这种可怕的设想泡汤。奶牛们进行斗争的策略之一是“劣质的包装”。“看，”奶牛们说，“如果你只用一次能装 $3$ 块、 $6$ 块或者 $10$ 块的三种包装盒包装麦香牛块，你就不可能满足一次只想买 $1$ 、 $2$ 、 $4$ 、 $5$ 、 $7$ 、 $8$ 、 $11$ 、 $14$ 或者 $17$ 块麦香牛块的顾客了。劣质的包装意味着劣质的产品。”。

你的任务是帮助这些奶牛。给出包装盒的种类数 $N(1 \le N \le 10)$ 和 $N$ 个代表不同种类包装盒容纳麦香牛块个数的正整数 $(1 \le i \le 256)$，输出顾客不能用上述包装盒（每种盒子数量无限）买到麦香牛块的最大块数。如果所有购买方案都能得到满足或者不存在不能买到块数的上限，则输出 $0$。不能买到的最大块数（倘它存在）不超过 $2\times 10^9$。

## 说明/提示

题目翻译来自 NOCOW。

USACO Training Section 4.1


## 样例 #1

### 输入

```
3
3
6
10```

### 输出

```
17```

# 题解

## 作者：_rqy (赞：40)

这题题解竟然一个证明正确的都没有...

> 许多题解考虑类似小凯的疑惑使用 $ab-a-b$ 的结论，然而这个结论只在 $\gcd(a,b)=1$ 时适用。注意到所有数的 $\gcd$ 为 $1$ 不意味着存在两个数互质（比如 $6,10,15$），因此这个结论是不能直接套的。

考虑确定一个最大的不能被表示出来的数（如果存在）的上界。

如果所有的数的 $\gcd$ 不为 $1$，那么显然是不存在最大的不能表示出来的数的（任取一个不被 $\gcd$ 整除的数都不能被凑出来）。

设输入的所有数为 $a_1\dots a_n$，可以发现如果一个数 $k$ 能凑出来，那么 $k+a_1$ 也能凑出来；反过来说如果 $k$ 不能凑出来，那么 $k-a_1$ 也显然不能凑出来。

这样的话，对于任意的 $i=0\dots a_1-1$，一定存在一个数 $f_i$，使得 $f_i \equiv i \pmod{a_1}$，$f_i$ 能被凑出来但是 $f_i-a_1$ 不能（换句话说，$f_i$ 就是 $i, i+a_1, i+2a_1\dots$ 里面第一个能被凑出来的数）。

由于所有数的 $\gcd$ 是 $1$，所以对于任意一个数 $i$ 都能找到一串 $k_1,k_2\dots k_p$ 使得 $a_{k_1}+a_{k_2}+\dots+a_{k_p}\equiv i\pmod{a_1}$，所以一定有 $f_i\leq a_{k_1}+a_{k_2}+\dots+a_{k_p}$。取其中最短的（$p$ 最小的）一串 $a$，我们来证明 $p<a_1$。

如果 $p\geq a_1$，令 $S_j=(a_{k_1}+a_{k_2}+\dots a_{k_j})\bmod a_1$ 即这一串 $a$ 的前缀和，那么 $0\leq S_j<a_1$，因此 $S_j$ 只有 $a_1$ 中取值方式。根据鸽巢原理，$S_0,S_1\dots S_{a_1}$ 中必定有两个相等，记为 $S_l,S_r$，那么将 $a_{l+1},a_{l+2}\dots a_r$ 从这一串 $a$ 中去掉，可以发现剩下的 $a$ 的和仍然 $\equiv i\pmod{a_1}$，与我们选择了最小的 $p$ 不符。

因此 $p<a_1$，$f_i\leq a_{k_1}+\dots+a_{k_p}\leq p\times\max{a}\leq (a_1-1)\times\max{a}$。

如果 $t$ 是某个不能凑出来的数，那么显然 $t\leq f_{t\bmod a_1}-a_1\leq (a_1-1)\times\max{a}-a_1$，于是 $t$ 的上界不超过 $255\times256-256$。

接下来就可以直接背包计算这个上界以下所有的数能不能被凑出来了。代码十分简单，就不贴了qaq。

---

## 作者：HigHwind (赞：25)


> 哇题目看得我又饿了

# 原题

### 题目描述

农夫布朗的奶牛们正在进行斗争，因为它们听说麦当劳正在考虑引进一种新产品：麦香牛块。奶牛们正在想尽一切办法让这种可怕的设想泡汤。奶牛们进行斗争的策略之一是“劣质的包装”。“看，”奶牛们说，“如果你只用一次能装3块、6块或者10块的三种包装盒包装麦香牛块，你就不可能满足一次只想买1、2、4、5、7、8、11、14或者17块麦香牛块的顾客了。劣质的包装意味着劣质的产品。”

你的任务是帮助这些奶牛。给出包装盒的种类数$N(1≤N≤10)$和N个代表不同种类包装盒容纳麦香牛块个数的正整数$(1≤i≤256)$输出顾客不能用上述包装盒(每种盒子数量无限)买到麦香牛块的最大块数。如果所有购买方案都能得到满足或者不存在不能买到块数的上限，则输出0。 不能买到的最大块数（倘它存在）不超过2,000,000,000。

### 输入输出格式

输入格式：

第1行: 包装盒的种类数N

第2行到N+1行: 每个种类包装盒容纳麦香牛块的个数

输出格式：

输出文件只有一行数字：顾客不能用包装盒买到麦香牛块的最大块数或0(如果所有购买方案都能得到满足或者顾客不能买到的块数没有上限)。

### 输入输出样例

#### 输入样例：

```
3
3
6
10
```

#### 输出样例：

```
17
```

## 解答

### 特殊情形：NOIP2017_Day1 T1 小凯的疑惑

> 小凯手中有两种面值的金币，两种面值均为正整数且彼此互素。每种金币小凯都有无数个。在不找零的情况下，仅凭这两种金币，有些物品他是无法准确支付的。现在小凯想知道在无法准确支付的物品中，最贵的价值是多少金币？注意：输入数据保证存在小凯无法准确支付的商品。

若$\gcd(a,b)=1$，求$k_{max}≠ma+nb(k,a,b,m,n\in\Bbb{N_+})$

就是说$a,b$互质，求$a,b$的自然数倍之和所不能表示出来的最大的数。

据说是小学奥赛题……结论很简单

$k_{max}=ab-a-b \space\space\space\space(*)$


这题直接输出就好了。


但是直接证明我不会证……

不过证$ab-a-b$无法被表示还是可以的，用反证法：

不妨假设

$$ab-a-b=ma+nb(a,b,m,n\in\Bbb{N_+})$$

则整理得

$$(b-m-1)a=(n+1)b$$

而据互质条件$\gcd(a,b)=1$得

$$\begin{cases}a=n+1\\b=b-m-1\end{cases}$$

可解得$m=-1\notin\Bbb{N_+}$，故原假设不成立，即$ab-a-b$不能被表示。

### 投机取巧

有了上面的这个结论，我们就可以回到本题来了。（别告诉我你已经忘了题目了-。-）

题中给了一个答案范围$ans_{max}=2*10^9$，不用说，拿这个枚举肯定是Timeout。

那么能不能再缩减一下这个范围呢？

注意题目中我划的高亮数据范围：

> $1≤i≤256$

所以当$i=i_{max}=256$时，用上面的结论($ab-a-b$)可知$ans_{max}=256^2-2*256$

有了这个上限，我们就只用枚举到$ans_{max}$了。

当然，还要注意题目要求输出$0$的时候。

### 程序

之所以`MAXLIM`使用了$256^2-2*256+1$是为了简化下文代码中循环次数的处理。

这个值是可以取的最小值，再往大取是没有问题的，所以我在其他题解里也看到过用$70000$做的，这个值可能是试出来的吧。

本来这个值取的再小一点也不会有太大问题，但是洛谷给的数据太刁钻了……

```
4
252
250
254
256
```

对于这组数据，如果`MAXLIM`取为$256^2-2*256$（仅比理想最小值小1），这组数据就会得到$65023$而不是输出$0$……好伤啊！

```
#include <bits/stdc++.h>

#define LL unsigned long long
#define MAXLIM 65025 // = 256^2-2*256 + 1

using namespace std;
int f[MAXLIM + 1]; //f[i]存储整数i能否被表示
int i, j, n;
int a[11];
int main() 
{
    cin >> n;
    for (i = 1; i <= n; i++)
        cin >> a[i];
    f[0]=1;
    
    // 核心代码，背包处理
    for (i=1;i<=n;i++)
        for (j = a[i]; j <= MAXLIM; j++)
            f[j] = f[j] || f[j - a[i]];


    int ans = 0;                  //存结果用
    for (i = MAXLIM; i >= 0; i--) //找不能被表示的最大的数，倒找比顺找好
        if (f[i] == 0)
        {
            ans = i;
            break;
        }
    if (ans>65024)
        ans = 0;
    cout << ans << endl;
    
    return 0;
}
```



---

## 作者：cabasky (赞：18)

楼下都能证明上界，然后都用类似完全背包的做法。这里我提供一种不同的思路。

题目大意为数组中取数，每个数取任意多次，问不能凑出来的最大数。

容易yy出来，**如果一个数k可以被凑出来，那么对于物品大小为x，k+x，k+2x，k+3x……都可以凑出来。**

那么我们**不妨对所有能凑出来的方案对任意一个物品x取模**，分成0到x-1一共x组。

我们现在要求出每一组方案的最小值。

**然后在每一组方案的最小值里取最大值，减去x，即为答案。**

为什么呢？

假设每一组能凑到的方案的最小值的最大值为t，由于这个t在这一组里是最小值，那么t-x一定不能凑出来。否则t就不是最小值了。

而且由于t在所有的组中是最大值，假设t=ax+b，那么ax+0，ax+1，ax+2………ax+x-1也可以被凑出来，这x个数是其他组别里的方案或者其他组别里的方案加上整数个x得到的。但是，t-x即ax+b-x不能被凑出来（因为t是最小值），而上面的ax+y中，y如果小于b，要么ax+y可以凑出，那么对答案没影响，要么ax+y减去任意个x可以被凑出，但是肯定小于t-x；y如果大于b，那么ax+y-x一定可以凑出，否者ax+y>t，不符合条件，所以也不是最优解。

表述不是很明了，不如探讨样例。

选择3作为x，

除以3余0的方案 最小值是0（什么都不选）

除以3余1的方案 最小值是10 选一个10

除以3余2的方案 最小值是20 选两个10

那0 3 6 9 12 15 18 21……都可以由第一组的0加任意个3凑出；

10 13 16 19 22 25……都可以由第二组的10加任意个3凑出；

20 23 26 29 32 35……都可以由第三组的20加任意个3凑出。

我们发现上面的20，21，22三个数连续了，也就是这个剩余系完整了，那么大于22的数一定全都可以有这三个数加3凑出来。

但是20前面有缺的，即20-3=17，20-2\*3，20-3\*3……一定凑不出来。

对于10和0也同理。

所以这些凑不出来的数里面最大的肯定就是最大的20只减去一个3，也就是17。

那么如何求出每一组的最小值呢？

这里就是本题的精华所在，也就是**最短路**模型的转化。

**我们不妨把0到x-1建立x个点，对于每一个点，我们枚举题目给出的a[i]，从x到(x+a[i])%x连一条边权为a[i]的边，表示(ax+b)%x加上a[i]变成了(ax+b+a[i])%x。**

然后0的距离是0，也就是什么都不取。

从0开始跑单源最短路。

假如跑完以后出现某个点的距离减去x大于题目的上界，那么就输出0；

假如某个点到达不了，那么显然也输出0，**因为这表示这一组的方案一定是凑不出来的**。

排除以上可能后，假如最大距离是0，那么输出0，**因为这表示所有的数都可以凑出来**。

对于这个x的选择，当然是任意的，但是x的大小即为点的个数，所以x不妨选最小的那个（然而x要保证非0）。

这题因此可以用dij写，然而数据不大，所以spfa也可以0ms过掉。

复杂度上界Θ(n\*n\*min(i))

以下是本蒟蒻丑陋无比的代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
#define UPPER 2000000000
typedef long long LL;
LL dis[400],val[10000],a[20],mx=-1,mn=400;
int q[10000],head,tail,used[400],n,point[10000],yest[10000],last[400],total;
void adde(int f,int t,int v){
    //cout<<"add"<<f<<"->"<<t<<" "<<v<<endl;
    point[++total]=t;
    val[total]=v;
    yest[total]=last[f];
    last[f]=total;
}
void spfa(int p){
    memset(dis,-1,sizeof(dis));
    dis[p]=0;
    used[p]=1;
    head=tail=1;
    q[1]=p;
    int f,t,v;
    while(head<=tail){
        f=q[head];
        //cout<<"f="<<f<<endl;
        for(int i=last[f];i;i=yest[i]){
            t=point[i];
            //cout<<f<<"->"<<t<<"   "<<val[i]<<endl;
            if(dis[t]==-1||dis[f]+val[i]<dis[t]){
                dis[t]=dis[f]+val[i];
                if(!used[t]){
                    used[t]=1;
                    q[++tail]=t;
                }
            }
        }
        used[f]=0;
        head++;
    }
}
int main(){
    //freopen("in.txt","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if(mn>a[i]) mn=a[i];
    }
    for(int i=0;i<mn;i++)
        for(int j=1;j<=n;j++)
            adde(i,(i+a[j])%mn,a[j]);
    spfa(0);
    int flag=1;
    for(int i=0;i<mn;i++){
        if(dis[i]==-1||dis[i]-mn>UPPER){
            flag=0;
            break;
        }
        else{
            if(dis[i]>mx) mx=dis[i];
        }
    }
    if(!flag) puts("0");
    else{
        if(mx-mn>=0) printf("%lld\n",mx-mn);
        else puts("0");//这里我也是后来想到的，因为mn最小，那么不可能有任何方案比mn更小，除非这个mx=0，这样才能mx-mn<0
    }
    return 0;
}
```

---

## 作者：shadowice1984 (赞：15)

来一发dp

显然，如果我们令dp[i]表示能否凑出i个牛块。

则满足以下递推式

if(dp[i])dp[i+weight[x]]=true;

然后我们需要的就是确定容量。

然后有这样一个结论，

若p，q互质，则任意大于lcf（p，q）-p-q的数都能被p，q表示

然后dp就好~

```cpp
#include<stdio.h>
using namespace std;
int gcd(int a,int b)
{
    if(b==0)return a;
    else return gcd(b,a%b);
}
int lcf(int a,int b)
{
    return a*b/gcd(a,b);
}
bool dp[80000];
int weight[10];
int n;int cont=0x3f3f3f3f;
int res=0;
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&weight[i]);
    }
    int g=weight[0];
    for(int i=0;i<n;i++)//确定容量
    {
        g=gcd(g,weight[i]);
        if(g==1)break;
    }
    if(g!=1)
    {
        printf("0");return 0;
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<=i;j++)
        {
            int t=lcf(weight[i],weight[j]);
            if(cont>t&&gcd(weight[i],weight[j])==1)cont=t;
        }
    }
    dp[0]=true;
    for(int i=0;i<n;i++)//dp
    {
        for(int j=0;j<cont;j++)//每个物品可以多次使用
        {
            if(dp[j]==true)
            {
                dp[j+weight[i]]=true;
            }
        }
    }
    for(int i=0;i<cont;i++)
    {
        //printf("dp[%d]is%d\n",i,dp[i]);
        if(dp[i]==false)res=i;
    }
    printf("%d",res);
    return 0;//拜拜程序
}
```

---

## 作者：Ken_He (赞：5)

貌似之前的题解都没有讲256^2的枚举范围是怎么来的诶~~

那还是我来吧


# USACO 4.1.1 麦香牛块 Beef McNuggets


## 题目大意


给你$n$个数$a_1, a_2 ... a_n$, 要你求最大的正整数$m$使得方程$a_1 x_1 + a_2 x_2 + ... + a_n x_n = m$无非负整数解. 题目数据满足$a_x$为正整数且不大于$256$, $n \le 10$.


## Solution


先看一个定理: 对于正整数$p$, $q$满足$gcd(p, q) = 1$, 我们有$px + qy = n$无非负整数解的最大正整数$n$为$pq - p - q$. 证明如下:

我们首先利用反证法, 证明$px + qy \ne pq - p - q$: 我们假设存在正整数$x$和$y$使得$px + qy = pq - p - q$, 则有


$$px + qy = pq - p - q $$

$$p(x + 1) + q(y + 1) = pq $$

$$\because gcd(p, q) = 1\ ,\ p | q(y + 1) $$

$$\therefore p | y + 1 $$

同理, $$q | x + 1$$


接着我们令$y + 1 = pj$, $x + 1 = qk$. 则有


$$pqk + qpj = pq $$

$$pq(j + k) = pq$$


注意到$x, y \ge 0$, 我们有$y + 1 \ge 1$且$x + 1 \ge 1$, 因而$j \ge 1$且$k \ge 1$. 因而$j + k \ge 2$, 因而假设不成立.

得证.

再证明当$n \ge pq - p - q + 1$时原方程总有非负整数解:

我们令$n = pq - p - q + k$, 则根据扩展欧几里得定理, 方程$pa + qb = k$有整数解(其中$a$和$b$中必有一个为正, 一个为负). 我们假设$a < 0 < b$, 调整$a$和$b$的值使得$|a| < q$. 令此时的$a$和$b$分别为$A$和$B$. 
回到原方程


$$px + qy = pq - p - q + k $$

$$px + qy = pq - p - q + Ax + By $$

$$p(x + 1 - A) + q(y + 1 - B) = pq$$

根据前面的结论, 我们又有


$$p | y + 1 - B $$

$$q | x + 1 - A$$

$$
因此我们令

$$j = \frac{x + 1 - A} q $$

$$k = \frac{y + 1 - B} p$$

则有
$$pq(i + j) = pq $$

$$i + j = 1$$

不妨设$i = 0$且$j = 1$, 则


$$y + 1 - B= 0 $$

$$x + 1 - A = q$$


因而
$$y = B - 1 $$

$$x = A + q - 1$$

由于$B > 0$, 因而$B - 1 \ge 0$;

根据之前定义, 我们又有$|A| < q$, 因而$A + q - 1 \ge 0$
因而原方程必有非负整数解.


好了, 现在考虑这道题怎么做233

注意到$a$值较小, 我们直接从0开始到$256^2$背包暴力即可.

我们注意到$a$之间并不一定互质, 但这并不影响我们枚举的范围.


```cpp
#include <cstdio>
#include <cctype>

const int N = 10, LIM = 256;
int a[N], f[LIM * LIM << 2];
int main()
{
    int n; scanf("%d", &n);
    for(int i = 0; i < n; ++ i) scanf("%d", a + i);
    f[0] = 1;
    for(int i = 1; i < LIM * LIM << 2; ++ i) for(int j = 0; j < n; ++ j) if(i - a[j] >= 0 && f[i - a[j]])  f[i] = 1;
    int ans = 0;
    for(int i = 1; i < LIM * LIM << 2; ++ i) if(! f[i]) ans = i;
    printf("%d\n", ans > LIM * LIM ? 0 : ans);
}

```

---

## 作者：文艺平衡树 (赞：3)

### 裴蜀定理：
方程$\sum_{i=1}^{n}k_ix_i=b$有整数解当且仅当$gcd(k_1,k_2,...,k_n)|b$

不知道的同学可以做一下这题：[【模板】裴蜀定理](https://www.luogu.com.cn/problem/P4549)

### 证明：
#### 必要性
设 $gcd(k_1,k_2,...,k_n)=g$（后面也用g表示），则 $g|k1,g|k2....$，又$b=\sum_{i=1}^{n}k_ix_i$，所以$g|b$。

#### 充分性
先证方程$\sum_{i=1}^{n}k_ix_i=g$有解，当$n=2$时根据扩展欧几里得算法显然成立，利用数学归纳法，假设$n=k$时方程有解，那么$n=k+1$时：

$k_1x_1+k_2x_2+....+k_nx_n+k_{n+1}x_{n+1}=gcd(k_{n+1},g)$，就要证存在$x_{n+1}$ 使 $k_{n+1}x_{n+1}+\lambda g=gcd(k_{n+1},g)$

解释一下$\lambda g$，这是说因为 $k=n$ 时方程有解，所以我们将解中的每一个$x$变为原来的 $\lambda$ 倍，就使得$\sum_{i=1}^{n}k_ix_i=\lambda g$，其中 $\lambda$ 是任意整数。

那么，改写一下 $k=n+1$时的方程 ：$ax+by=gcd(a,b)$，肯定有解。

所以方程$\sum_{i=1}^{n}k_ix_i=g$有解，又因为$g|b$，所以我们将方程$\sum_{i=1}^{n}k_ix_i=g$ 的解变为原来的$\frac{b}{g}$倍就可以了。

综上，裴蜀定理得证。

### 解决问题
分析一下，这道题就是要找一个最大的$b$，使得方程 $\sum_{i=1}^{n}k_ix_i=b$ 无**自然数解**。

根据裴蜀定理，如果$g>1$，可以找到一个任意大的$b$（$g\nmid b$），使该方程没有整数解，自然更没有自然数解了，输出"0"。

如果$g=1$，方程一定存在整数解，且$b$足够大时，一定能通过解的调整使各个$x$都变为自然数，所以满足题意的 $b$ 是有上界的。

我们关心的是这个上界是多少。~~我太弱了不会证~~，那就开个1e6的数组试试吧，接下来跑DP就完事了。

然后，过了。。。
## 代码
```
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
int dp[1000000],a[11];
int gcd(int x,int y){
    if(x<y) swap(x,y);
    if(!y) return x;
    return gcd(y,x%y);
}
int main(){
    int n,i,j,ans=0,g=0;
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        scanf("%d",&a[i]);
        g=gcd(g,a[i]);
    }
    dp[0]=1;
    for(i=1;i<=1000000;i++){
        for(j=1;j<=n;j++){
            if(i>=a[j])
                dp[i]|=dp[i-a[j]];
        }
        if(!dp[i]) ans=i;
    }
    if(g==1) printf("%d",ans);
    else printf("0");
    system("pause");
    return 0;
}
```


---

## 作者：dolphin (赞：3)

楼上的题解很精妙……但是我一开始没看懂……所以还是说一下另一个做法

其实是有这样一个结论：若p，q为自然数，且gcd(p,q)=1，那么px+qy不能表示的最大数为pq-p-q

那么本题中p，q均取决于最大的两个数，不妨取256，那么上界为256^2-256\*2

之后就是简单的完全背包

如果数据中有1，或者最大不能取到的数大于上界，就是0

···cpp

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=256,m=65536;
int n,f[m+10],a[15];
int main(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    if (a[1]==1){
        printf("0");
        return 0;
    }
    f[0]=1;
    for (int i=1;i<=n;i++)
        for (int j=a[i];j<=m;j++)
            if (f[j-a[i]]) f[j]=1;
    int x=0;
    for (int i=m;i>=1;i--)
        if (!f[i]){
            x=i;
            break;
        }
    if (x>m-N*2) x=0;
    printf("%d",x);
    return 0;
}
···
```

---

## 作者：学而思李老师 (赞：3)

### 题意简述

给你 $n$ 个正整数 $a_1, a_2, \cdots, a_n$，求不能用 $p_1a_1+p_2a_2+\cdots+p_na_n (p_1, p_2, \cdots, p_n\geq 0\text{且}p_1, p_2, \cdots, p_n\text{均为整数})$ 表示的最大整数。

### 算法思路分析

#### 考场上不会像其他题解一样推式子怎么办？

因为每一个数使用的次数没有限制，可以选择任何一个非负整数个，所以可以使用完全背包解决。具体完全背包算法请见 [P2722 [USACO3.1]总分 Score Inflation](https://www.luogu.com.cn/problem/P2722)，这是一道模板题。

我们可以发现，这题也和装箱问题很像，都是“能不能凑出”的问题，所以可以把上述两道题的算法融合一下，暂且称之为“布尔型完全背包”。

但是，我们看到数据范围，最大可以到 $2\times 10^9$，背包问题的复杂度是 $O(nm)$，肯定超时，数组也开不下。如果你数学很差，在考场上看到这么大的数据范围怎么办呢？

我们知道，计算机大约在一秒内可以完成 $10^8$ 次运算，也就是不考虑常数的话，循环最多只能有 $10^8$ 次。我们这题中，$1\leq n \leq 10$，背包问题的 $m$ 最多就到 $\dfrac{10^8}{10}=10^7$，因此我们可以得出：如果此题完全背包是正解，那么开 $10^7$ 的数组肯定能AC~~结果我的 $10^7$ 数组的代码交上去真的AC了~~。

所以，在数据范围非常大的时候，我们可以利用计算时间复杂度的方法算出到底需要多少数组。比如回文质数那题，$10^8$ 在 $1s$ 内很难跑完，那么不用数论知识分析，也可以猜到那题开 $10^7$ 的数组也能过。

当然，此题其实是运气好，正解就是完全背包。那么其它题解中的式子是怎么推出来的呢？

#### 小奥推式子

首先要判断什么情况下答案是$0$。也就是说，永远都有空隙。小奥告诉我们，只有当 $\gcd(a_1, a_2, a_3, \cdots, a_n)=1$时，才能有最大的不能被表示出的数。所以，读入完直接处理这种情况。

根据之前做过的一道数论题小凯的疑惑，可以知道两个数 $x, y$ 不能用 $ax+by$ 表示出来的最大整数的公式是 $xy-x-y$ 具体证明那题题解里已经有了，非常详细。

这篇题解主要讲解了在考场上因为各种原因导致没有推出来公式的情况下应该如何利用数据范围降低难度。虽然感觉有点无赖，但是确实这招还是挺好用的。

核心代码：
```cpp
for(int i = 2; i <= 255; i ++)
	{
		bool flg = true;
		for(int j = 1; j <= n; j ++)
			if(w[j] % i != 0)
			{
				flg = false;
				break;
			}
		if(flg)
		{
			printf("0");
			return 0;
		}
	}
		
	dp[0] = true;
	for(int i = 1; i <= n; i ++)
		for(int j = w[i]; j <= MR; j ++)
			dp[j] |= dp[j - w[i]];
			
	for(int i = MR - 5; i >= 0; i --)
		if(!dp[i])
		{
			printf("%d", i);
			return 0;
		}
```


---

## 作者：pmt2018 (赞：2)

# 题解

这里给出一种不依赖$ pq-p-q $ 的方法

令数列最小值为$a_0$

显然，若在某时已有连续$a_0$个数能被表示出来，那么剩下所有的数都能够被表示。

所以，我们在dp的同时维护一个当前能被连续表示的数$t$，若$t=a_0$则跳出循环。

那么，如果没有最大不能被表示的数呢？

可以证明，若有两个数互质，则一定有最大不能被表示的数。

所以，预先统计所有数的最大公因数$gcd$

如果$gcd\neq 1$那么一定有最大不能被表示的数。

代码如下：

~~~cpp
#include<bits/stdc++.h>
#define mp make_pair
#define pb push_back
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int > vi;
typedef pair<int ,int > pii;
typedef vector<pii> vii;
const int inf=0x3f3f3f3f, maxn=100007, mod=1e9+7;
const ll linf=0x3f3f3f3f3f3f3f3fLL;
const ll P=19260817;
int n;
int a[259];
bool dp[100007];
int rt,ans;
int gcd=1;
bool one=true;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    gcd=a[1];
    for(int i=2;i<=n;i++)
		gcd=__gcd(a[i],gcd),a[i]==1?one=1:one&=1;

    if(gcd!=1||!one){
        printf("%d\n",0); 
        return 0;
    }
    dp[0]=true; 
    for(int i=1;;i++){
        for(int j=1;j<=n;j++){
            if(i<a[j])break;
            dp[i]|=dp[i-a[j]];
        }
        if(!dp[i]){
            ans=i;
            rt=0;
        }else{
            rt++;
        }
        if(rt==a[1])break;
    }
    printf("%d\n",ans);
    return 0;
}
~~~


---

## 作者：「QQ红包」 (赞：2)

完全背包

```cpp
/*
ID: ylx14271
PROG: nuggets
LANG: C++     
*/
#include<set>  
#include<map>  
#include<list>  
#include<queue>  
#include<stack>  
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>  
#include<stdlib.h>  
#include<string.h>  
#include<algorithm> 
#define LL unsigned long long   
using namespace std;
int f[70001];//f[i]表示是否能构成i
int i,j,n;
int a[11]; 
int main() 
{
    freopen("nuggets.in","r",stdin);
    freopen("nuggets.out","w",stdout); 
    scanf("%d",&n);
    for (i=1;i<=n;i++)//读入 
        scanf("%d",&a[i]);
    f[0]=1;
    for (i=1;i<=n;i++) 
        for (j=a[i];j<=70000;j++)//不一定是7万，一个较大的数就好 
        f[j]=f[j]||f[j-a[i]];
    int x=0;//存结果用 
    for (i=70000;i>=0;i--)//找不能被表示的最大的数 
    if (f[i]==0)
    {
        x=i;
        break;
    }
    if (x>65024) x=0;
    cout<<x<<endl;//输出 
    return 0;
}//完全背包 

```

---

## 作者：MilkyCoffee (赞：1)

### $All\ in\ all...$

布尔型完全背包，选的是某个能否被拼出来。

本篇主要是面向新手。

### $dp's\ equation$

$dp[j] = dp[j]\ ||\ dp[j-w[i]];$ $->$ 如果减去一个包装能拼出来，那么 $dp[j]$ 也能拼出来。

### $initialization$

$dp[0] = true;$ $->$ 如果要买0块的话，肯定是可以的

如果公约数非 $1$（如$2$、$4$、$6$、$8$），就肯定不存在上限。

### $time\ complexity$

$O(nm)$

一秒钟计算机能做约为$10^8$量级的运算。

复杂度$10^8$，用$10^7$拿部分分保险（拿 $80pt$ 总比数据溢出好）。而且本题的数据远远小于$10^7$（这一点由于本人的数学功底不够无法证明希望后补/其他神犇帮个忙QAQ）。

### $code$

```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

const int NR = 10;
const int MR = 1e7;

int w[NR + 5];
bool dp[MR + 5];

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
	    cin >> w[i];
	}
	// ------- 没有最大上限
    // 这里我用的是最没用的试除，不过能过就行（
	
	for (int x = 2; x <= 255; x++) {
	    bool flag = true;
	    for (int i = 1; i <= n; i++) {
	        if (w[i] % x != 0) {
            	// 只要找到一个不是x的倍数，就说明x非1~n的公约数
	            flag = false;
	            break;
	        }
	    }
	    if (flag == true) { // 如果x是公倍数，就肯定没有最大上限了
	        cout << 0 << endl;
    	    return 0;
	    }
	}
    // ------- 没有最大上限
    
    // 正文
	dp[0] = 1;
	for (int i = 1; i <= n; i++) {
	    for (int j = w[i]; j <= MR; j++) {
	        dp[j] |= dp[j-w[i]]; 
            // 看不懂异或的看下面
	        // if (dp[j] || dp[j-w[i]]) dp[j] = 1;
	    }
	}
	for (int j = MR; j >= 1; j--) {
	    if (!dp[j]) {
	        // 找出最大
	        cout << j << endl;
            // 如果dp[j]从后面找的话，找到了就是最大的，然后我们输出j，结束程序
	        return 0;
	    }
	}
	cout << 0 << endl;
    // 如果跑完了还没找到不能组装的，就输出0
    return 0;
}
```

### $If\ you\ have\ finished\ reading\ this\ blog,\ please...$

管理求过QAQ

路过人求赞！

---

## 作者：不存在之人 (赞：1)

例$p=4$，$q=5$的情形(最大不能表示的数是$11$)

![](https://i.loli.net/2018/12/04/5c0678d4b70c2.jpg)

------------
1.

假设可以表示为$pq-q-p$

那么

$px+qy=pq-q-p$

$p(x+1)+q(y+1)=pq$

$p|y+1,q|x+1$ //整除

又$p(x+1),q(y+1)<=pq$

有$x+1=kq$且$y+1=(1-k)q$或$x+1=(1-k)p$,且$y+1=kp$,$k$是正整数

但是$x,y>=0$故$pq-q-p$,就无法表示成$px+qy$

------------
2.

$(p-1)(q-1)=pq-p-q+1$

对于$n>pq-q-p$即$n>=(q-1)(p-1)$

$gcd(p,q)=1$

对于$z<min(p,q)$存在$a$,$b$使得$ap+bq=z$

不妨设$a>0>b$,显然$a>0$

那么如果$a>q$,取$a1=a-q,b1=b+p$

那么有$a1*p+b1*q=z$

如果$a1>q$,可以继续得到

$Ap+Bq=z$,且$0<|A|<q,0<|B|<p$

$pq-p-q=(p-1)q-q=(q-1)p-p$

对于$n>pq-q-p$

$n=pq-q-p+k*min(p,q)+r$

$r<z<min(p,q)$

那么取$A$,$B$

$Ap+Bq=r$,且$0<|A|<q,0<|B|<p$

不妨设$A>0$

$n=pq-q-p+k*min(p,q)+r$

$=(q-1)p-p+k*min(p,q)+Ap+Bq$

$=(A-1)p+(B+q-1)p+k*min(p,q)$

其中$(A-1),(B+q-1)>=0$

那么无论$min(p,q)$是$p$还是$q$

对于$n>pq-q-p$,都可以表示成$px+qy$

------------
请问：能不能表示成$5x+3y$($x$,$y$为非负整数)的最大整数是？

答案是$7$

显然在$1~10$中，符合题意的最大数为$7$，对于更大的数，显然不能是$3$或$5$的倍数，而任意的数模$3$ $mod$ $1$ 或 $2$，余$1$的，可以将$3×3+1$换成$5*2$，余$24$的，可以将$3+2$换成$5$，通过这种变换可以将十以上的数都变成$5x+3y$这种形式，所以满足题意的数是$7$

于是最大数都只有$625*625$

一个背包型$dp$就好了：
```cpp
#include<cstdio>
#define For(i,a,b) for(i=a;i<=b;i++)
#define rep(i,a,b) for(i=a;i>=b;i--)
using namespace std;
const int maxn=100010;
int dp[maxn];
int a[maxn];
int main()
{
	int i,j,n;
	scanf("%d",&n);
	For(i,1,n)
	{
		scanf("%d",&a[i]);
		dp[a[i]]=1;
	}
	For(i,1,n)
	{
		For(j,a[i],100000)
		{
			dp[j]=(dp[j]||dp[j-a[i]]);
		}
	}
	rep(i,100000,1)
	if(!dp[i])
	{
		if(i<70000) printf("%d\n",i);
		else printf("0\n");return 0;
	}
	printf("0\n");
	return 0;
}
```

---

## 作者：L2_sheep (赞：1)

利用取模运算，可以降低时间和空间复杂度。设数组a为可装牛块数量，把数组a的最小值赋给k。

当且仅当k等于1时，所有购买方案都能得到满足，输出0。

设数组b为组合得到的最小数量（对k取模对应其数组下标），设boolean数组f为对k取模的得数是否能通过组合得到。

接下来，进行完全背包。最后，统计f数组，若不全为true，则不存在不能买到块数的上限，输出0。

若全为true，找出数组b的最大数，减去k，就是答案。


    
    
```cpp
#include <stdio.h>
#include <algorithm>
using namespace std;
int main() 
{
    int n, a[11], b[256] = {0}, t, x, y, i, j, m = 0, k;
    bool f[256] = {1};
    scanf("%d", &n);
    for(i = 0; i < n; i ++) scanf("%d", a + i);
    sort(a, a + n);
    if(a[0] == 1){
        puts("0");
        return 0;
    }
    k = a[0];
    for(i = 1; i < n; i ++){
        t = a[i] % k;
        for(j = 0; j < k; j ++){
            x = j + t;
            if(x >= k) x -= k;
            if(f[j]){
                y = b[j] + a[i];
                if(!f[x]) b[x] = y, f[x] = true;
                else if(y < b[x]) b[x] = y; 
            }
        }
    }
    for(i = 0; i < k && f[i]; i ++);
    if(i < k) puts("0");
    else{
        for(i = 0; i < k; i ++){
            if(b[i] > m) m = b[i];
        }
        printf("%d\n", m - k);
    }
    return 0;
}
```

---

## 作者：cszhpdx (赞：1)

题目传送门：[P2737 \[USACO4.1\]麦香牛块Beef McNuggets](https://www.luogu.com.cn/problem/P2737)

简化题意：其实就是给你 $n$ 个数，$a_1$ 到 $a_n$ ，对于每个数取任意个，把它们的和放到集合 $S$ 中，找出在集合 $S$ 中最大的正整数 $x$ ，使得 $x \not \in S $

这题大概思路就是确定两个范围，设有两数 $m,\ r$，它们满足：

所有的测试点里的答案 $\le m$

如果凑出来的数有上限，那么 $\{x \mid x \in [r,m],x \in N+\} \subseteq S$ 

反之 $\{x \mid x \in [r,m],x \in N+\} \not\subseteq S$

我们先假设 $m\ r$ 存在，那么我们要确定的就是在 $[r,m]$ 范围内的每一个正整数能否被凑出来

这怎么求呢，很明显这是一个布尔型完全背包模板

代码：

```cpp
f[0]=true;
for(int i=1;i<=n;i++)
	for(int j=a[i];j<=M;j++)//即前文中的m
		f[j]|=f[j-a[i]];
```

没看懂的话建议百度完全背包

# 前方高能
确定 $m\ r$，**我们发现前面的背包时间复杂度是 $O(nm)$ 如果这个算法能过的话，应该满足 $nm \le 10^8$ 其中 $n \le 10$，那么 $m \le 10^7$ 时 $m$ 一定满足上述条件，于是我们设 $m=10^7$** ,那么如何确定 $r$ 呢？这个数不好靠分析时间复杂度的方式来算，于是我干脆蒙了一个数 $r=5 \times 10^6$ ，然后对了！
献上代码:
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int NR=15, MR=1e7, LYGXMD=5e6;
//LYGXMD代表R, MR代表M
int n, a[NR], f[MR+10];
int main()
{
	//输入
	scanf("%d", &n);
	for(int i=1;i<=n;i++)
		scanf("%d", a+i);
	//背包
	f[0]=true;
	for(int i=1;i<=n;i++)
		for(int j=a[i];j<=MR;j++)
			f[j]|=f[j-a[i]];
	//找到没有上限的情况
	for(int i=LYGXMD;i<=MR;i++)
		if(!f[i])
		{
			printf("0");
			return 0;
		}
	//算出答案
	int ans=MR;
	while(ans>0 && f[ans])ans--;
   //如果有答案的话那么输出答案
	printf("%d", ans);
	return 0;
}
```
当然我的用时间复杂度分析的方法不是正解，但却是比赛中很实用的技巧，至于 $m\ r$正解的算法可以看看别的题解， dalao 们解释的都很清楚

---

## 作者：Celebrate (赞：1)

这一道题背包是一个不错的解法，但是需要加一个判断0的优化，不然很难确定

我们把背包的容量设置为尽可能大，并且不能超时，我就设了12000000

代码如下：

```cpp
#include <bits/stdc++.h>
#define MAXN 12000000
using namespace std;
int gcd(int a,int b)//最大公因数 
{
    if(b==0)return a;
    else return gcd(b,a%b);
}
int f[MAXN]; //f[i]存储整数i能否被表示
int a[11];
int main() 
{
	int n,i,j;
    scanf("%d",&n);
    for(i=1;i<=n;i++) scanf("%d",&a[i]);//输入 
    int t=a[1];
    for(i=2;i<=n;i++){t=gcd(t,a[i]);if(t==1) break;}//如果最大公因数为1，就退出查找 
    if(t!=1)//如果他们n个数的最大公因数不是1，就可以组成无限大的数 
    {
    	printf("0\n");
    	return 0;
    }
    f[0]=1;
    //核心代码，背包处理
    for(i=1;i<=n;i++)//背包 
        for(j=a[i];j<=MAXN;j++)
            if(f[j-a[i]]==1)
            	f[j]=1;
    int ans=0;                  //存结果用
    for(i=MAXN;i>=0;i--) //找不能被表示的最大的数，倒找比顺找好
        if(f[i]==0)
        {
            ans=i;
            break;
        }
    if(ans>=MAXN-1)ans=0;
    printf("%d",ans);
    return 0;
}
```

---

## 作者：wxy_god (赞：0)

状态：设$f[i]$表示能否装$i$块牛块（$bool$类型）  
转移：$f[i] |=f[i - a[j]]$  
然而，$2000000000$的数往下枚举一定会$TLE$，数论$0$分的我只能一个一个试。最后瞎碰碰出来了$65536$。  
最后输出的时候从$2*65536$往下枚举，如果$f[i]$是$true$，那么可以装出来，直接跳过。当找到一个是$false$时候，如果$i$大于$65536$，超出上限，输出零。否则，直接输出$i$，$return\ 0$。  
当然$USACO$的题一如既往有坑点。如果用上面的代码提交，会$WA$一个点。因为其有一个特殊数据，不会有输出（忘了是啥了），所以在最后还要输出$0$。

```
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>

const int N = 65536;
int n;
int a[11];
bool f[N << 1];

int main () {
	
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++ ) scanf("%d", a + i);
    f[0] = true;
    
    for(int i = 1; i <= n; i ++ )
	    for(int j = a[i]; j <= N << 1; j ++ )
	    	f[j] |= f[j - a[i]];
	
	for(int i = N << 1; i >= 0; i -- ) {
		if(f[i]) continue;
		if(i > N) printf("0");
		else printf("%d", i);
		return 0;
	}
	
	printf("0");
	
	return 0;
} 
```

---

## 作者：沉辰 (赞：0)

发一份有点歪的，不知道可不可以通过

实际来看测试数据范围并没有像题面里所说的那样大，所以可以从当前状态向外送

即-->f[v]=1表示v这个体积可以构成，那么f[v+a[i]]=1必定是合法的

所以 if(f[v]) for(int i=1;i<=n;i++) f[v+a[i]]=1;

可以推知所有合法体积，ans自然也就知道了

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<map>
#include<queue>
#define mod 1000000007 
#define inf 336860180
#define PI 3.1415926
#define ll long long
using namespace std;
int n,a[19],f[20000000],ans;
int max(int a,int b)
{
    return a>b ? a:b;
}
int main()
{  
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    f[0]=1;
    for(int v=0;v<=2000000;v++)
     if(f[v])
        for(int i=1;i<=n;i++) f[v+a[i]]=1;    
     else ans=v;//统计一下答案
     if(ans>=199999) cout<<0;
     else cout<<ans;
    return 0;
}
```

---

## 作者：Sky1231 (赞：0)

```cpp
//没有Pascal所以补上
//出解范围256^2=65536--因为题目中的数据都是小于等于256的，所以如果有最大无法表示的数，必然小于256^2
//可以采用构造法
//对于无限解:
//  (1)输入数据中有1
//  (2)某个大于256^2的数不能被合成且这个数字一定小于等256^2+256=65792。
var
  n,i,j,maxb:longint;
  a:array[0..65792] of longint;
  b:array[1..10] of longint;
begin
  readln(n);
  maxb:=0;
  for i:=1 to n do
  begin
    readln(b[i]);
    if b[i]>maxb then
      maxb:=b[i];
    if b[i]=1 then
    begin
      writeln(0);
      exit;
    end;
  end;
  fillchar(a,sizeof(a),0);
  a[0]:=1;
  for i:=1 to n do
    for j:=b[i] to 65792 do
      if a[j-b[i]]=1 then
        a[j]:=1;
  for i:=65537 to 65792 do
    if a[i]=0 then
    begin
      writeln(0);
      exit;
    end;
  for i:=65536 downto 1 do
    if a[i]=0 then
    begin
      writeln(i);
      exit;
    end;
end.
```

---

## 作者：i207M (赞：0)

## 题目总结

给定N个数，求不能由这些数组成的最大的数；

## 数据范围

$1<=N<=10,1<=i<=256$

## 解题思路

根据NOIP2017小凯的疑惑，我们知道，有两个数不能组成的大数最大不超过$ab-a-b$，所以此题答案不超过256×256-2×256+5=65029

然后暴力背包DP，倒序找出最大的不符合要求的数；

## 易错误区

我竟然忘记了背包DP这件事……

## 代码展示

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<stack>
#include<bitset>
#include<deque>
using namespace std;
#define ll long long
#define inf 0x3f3f3f3f
#define ri register int
#define il inline
#define fi first
#define se second
#define mp make_pair
#define pi pair<int,int>
#define mem0(x) memset((x),0,sizeof (x))
#define mem1(x) memset((x),0x3f,sizeof (x))
il char gc() {
    static const int BS = 1 << 22;
    static unsigned char buf[BS], *st, *ed;
    if (st == ed) ed = buf + fread(st = buf, 1, BS, stdin);
    return st == ed ? EOF : *st++;
}
#define gc getchar
template<class T>void in(T &x)
{
    x = 0; bool f = 0; char c = gc();
    while (c < '0' || c > '9') {if (c == '-') f = 1; c = gc();}
    while ('0' <= c && c <= '9') {x = (x << 3) + (x << 1) + (c ^ 48); c = gc();}
    if (f) x = -x;
}
#undef gc
void out(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) out(x / 10);
    putchar(x % 10 + '0');
}
#define N 256*256-2*256+1 // 65029
int n, a[12];
char f[N + 5];
signed main() {
    in(n);
    for (ri i = 1; i <= n; ++i) in(a[i]);
    sort(a + 1, a + 1 + n);
    f[0] = 1;
    for (ri i = 1; i <= n; ++i) {
        for (ri j = a[i]; j <= N; ++j) {
            f[j] |= f[j - a[i]];
            //cout << (int)f[i][j];
        }
    }
    f[0] = 0;
    for (ri i = N; i >= 0; --i) {
        if (!f[i]) {
            printf("%d", i == N ? 0 : i);
            return 0;
        }
    }
    return 0;
}
/*
int f[N];
int find(int x){
    return x==f[x]?x:f[x]=find(f[x]);
}
bool cmpy(int x,int y){
    int fx=find(x),fy=find(y);
    if(fx==fy) return 0;
    if(fy>fx) f[fy]=fx;
    else f[fx]=fy;
    return 1;
}
*/
/*
int v[M], u[M], w[M], nx[M];
int cnt, head[N];
il void add(int uu, int vv, int ww) {
    u[++cnt] = uu, v[cnt] = vv, w[cnt] = ww, nx[cnt] = head[uu];
    head[uu] = cnt;
}
*/
/*
struct Edge {
    int u,v,w,nx;
    Edge() {}
    Edge(int uu,int vv,int ww,int nxt) {
        u=uu,v=vv,w=ww,nx=nxt;
    }
    friend bool operator<(const Edge& a,const Edge& b) {
        return a.w<b.w;
    }
} edge[M];
int cnt,head[M];
il void add(int u,int v,int w) {
    edge[++cnt]=Edge(u,v,w,head[u]);
    head[u]=cnt;
}
*/

```

---

