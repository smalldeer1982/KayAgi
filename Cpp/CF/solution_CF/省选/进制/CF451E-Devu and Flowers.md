# Devu and Flowers

## 题目描述

Devu wants to decorate his garden with flowers. He has purchased $ n $ boxes, where the $ i $ -th box contains $ f_{i} $ flowers. All flowers in a single box are of the same color (hence they are indistinguishable). Also, no two boxes have flowers of the same color.

Now Devu wants to select exactly $ s $ flowers from the boxes to decorate his garden. Devu would like to know, in how many different ways can he select the flowers from each box? Since this number may be very large, he asks you to find the number modulo $ (10^{9}+7) $ .

Devu considers two ways different if there is at least one box from which different number of flowers are selected in these two ways.

## 说明/提示

Sample 1. There are two ways of selecting $ 3 $ flowers: $ {1,2} $ and $ {0,3} $ .

Sample 2. There is only one way of selecting $ 4 $ flowers: $ {2,2} $ .

Sample 3. There are three ways of selecting $ 5 $ flowers: $ {1,2,2} $ , $ {0,3,2} $ , and $ {1,3,1} $ .

## 样例 #1

### 输入

```
2 3
1 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 4
2 2
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3 5
1 3 2
```

### 输出

```
3
```

# 题解

## 作者：HenryYang (赞：59)

超链接：[数学合集](https://blog.csdn.net/HenryYang2018/article/details/89399986)

---


打完这篇文章的数学公式真的要吐血身亡了……

---

模板题：[CF451E](https://www.luogu.org/problemnew/show/CF451E)

---
模板题还可以长这样：
设$S=\{n_1*a_1,n_2*a_2,\cdots,n_k*a_k\}$是由$n_1$个$a_1$，$a_2$个$a_2$，$\cdots$，$n_k$个$s_k$组成的多重集。设$n=\sum_{i=1}^{k}n_i$，对于任意整数$r\leq n$，从S种去除r个元素组成一个多重集（不考虑顺序），求产生的不同多重集的数量

---
上面说的都是同一个问题，我用人话来描述一遍，现在有k堆珠子，每堆珠子颜色不同，第i堆珠子有$n_i$颗，现在我们从所有的珠子中取出r颗，问你这r颗珠子有多少种搭配？（与顺序无关）

---

咱们正式开始：

这道题太难了，我们先来解决一个简单一点的问题：**我们不管$n_i$这个条件，也就是说每种珠子都有无穷多颗，那么取r颗能有多少中选择捏？**

解决这个问题，我们使用一种非常优美的算法——**隔板法**

比如r=8,k=3

想法很简单：先画好r颗珠子

![](https://cdn.luogu.com.cn/upload/image_hosting/2erv2nrc.png)

然后在它们中间随便插入k-1块板子：

![](https://cdn.luogu.com.cn/upload/image_hosting/ki4cr6sz.png)

那么从左到右每一块板子之间就对应一种颜色：

![](https://cdn.luogu.com.cn/upload/image_hosting/ddt3kvhw.png)

那么这就是一种情况了

这就说明，每一种插板方案都对应了一种珠子颜色的情况，那么问题就变成**我们有多少种插板方案？**

注意几个细节：插在最左边是允许的，就表示没有珠子是第一种颜色，两块板插在同一个间隙也是被允许的，就表示没有珠子是这两块板之间所表示的那个颜色

那么插板方案数怎么计算呢，我们来看上面那个例子：
第一块板在插的时候有(r+1)种选法：

![](https://cdn.luogu.com.cn/upload/image_hosting/tcu27jgk.png)

当我把第一块板插进去后，第二块板就多了一种选择，有(r+2)种选法了：

![](https://cdn.luogu.com.cn/upload/image_hosting/xa2uhq6l.png)

然而两块板交换位置是同一种情况，So，最后除个二得到最终答案

总结一下：
我们要在r个珠子中插入(k-1)块板

第一块板有(r+1)种选择，第二块板有(r+2)种选择，第三块板有(r+3)种选择……第(k-1)块板有(r+k-1)种选择，所以根据乘法原理算出当前的答案：$(r+1)*(r+2)*\cdots*(r+k-1)=\frac{(r+k-1)!}{r!}$

但是板的顺序是没有关系滴，So，我们还要出去(k-1)块板的全排列总数，于是我们得到了最终答案：
$$\frac{(r+k-1)!}{r!(k-1)!}=C_{k+r-1}^r=C_{k+r-1}^{k-1}$$

---
好的，不过现在我们还是不能解决最上面的那个东西，我们还需要学习一个东西：**容斥原理**

我来简单（真的很简单）地来讲一下：

现在我们有三个集合：A，B，C，它们的**韦恩图**（你不用知道这是什么，往下看就行了）长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/srj61xsp.png)

现在我们要求$\left|A\cup B\cup C\right|$

那么我们就先$\left|A\right|+\left|B\right|+\left|C\right|$，但是中间的部分的周围3块（黄色，粉色，深蓝色）我们连续算了两次，我们就再减掉$\left|A\cap B\right|,\left|A\cap C\right|,\left|B\cap C\right|$

中间的紫色部分开始时被我们加了3次，然后又被我们减掉3次，So，我们还要把它加回去

于是乎，我们就得到了最终答案：
$$\left|A\cup B\cup C\right|=\left|A\right|+\left|B\right|+\left|C\right|-\left|A\cap B\right|-\left|A\cap C\right|-\left|B\cap C\right|+\left|A\cap B\cap C\right|$$

如果我们把这个式子稍稍扩展一下的话，就得到了容斥原理：

设$s_1,s_2\cdots s_n$为有限合集，$\left|s\right|$表示集合s的大小 ，则：
$$\left|\bigcup^{n}_{i=1}s_i\right|=\sum^n_{i=1}\left|s_i\right|-\sum_{1\leq i< j\leq n}\left|s_i \cap s_j \right|+\sum_{1\leq i< j< k\leq n}\left|s_i \cap s_j \cap s_k\right| +\cdots+(-1)^{n+1}\left|s_1\cap\cdots\cap s_n\right|$$


---
终于我们可以正式开始解决开始的那个问题了！

为了防止大家忘记它，我把它写在下面：

**现在有k堆珠子，每堆珠子颜色不同，第i堆珠子有$n_i$颗，现在我们从所有的珠子中取出r颗，问你这r颗珠子有多少种搭配？（与顺序无关）**

现在，如果我们不考虑$n_i$，就是我们上面解决的那个问题，答案就是$C_{k+r-1}^{k-1}$

现在我们来考虑$n_i$的限制，显然上面的那些情况中有很多情况是不能满足的，那把它们减去就好了

那么不符合条件的情况是那些捏？

我们设集合$s_i$表示至少取了$n_i+1$个颜色为i的珠子的所有情况，也就是$s_i$集合中i这个颜色的珠子个数一定超了$n_i$这个限制（其他的颜色情况我们不管），那么这个$s_i$一定都是要被我们舍弃的情况

然后有没有发现所有要被我们舍去的情况有这么多：$\left|\bigcup^{n}_{i=1}s_i\right|$

所以**最终答案**就是：$C_{k+r-1}^{k-1}-\left|\bigcup^{n}_{i=1}s_i\right|$

**我们先来看一下，对于每一个$\left|s_i\right|$怎么求？**

（注意一下，每个$s_i$里的情况都是不合法的情况，我们在算这个$\left|s_i\right|$的时候都是没有$n_i$限制的）

首先我们要从所有的珠子中取出$n_i+1$颗颜色i的珠子，这样的话，无论剩下的珠子怎么选都可以保证我们取出来的情况是在集合$s_i$里面的


取完了$n_i+1$颗颜色i的珠子后，我们还要拿$r-n_i-1$颗，那么这个有多少种情况捏？

这是没有$n_i$限制的，有没有发现这就是上面我们已经讨论过的问题，我们的结论是：$C_{k+r-1}^{k-1}$

只不过现在的r是$r-n_i-1$，代入以后我们得到了$\left|s_i\right|=C_{k+r-n_i-2}^{k-1}$

**那么我们试着再来求一求：$\left|s_i \cap s_j \right|$**

也就是我们要先取出$n_i+1$颗颜色i的珠子，$n_j+1$颗颜色j的珠子，这样剩下的珠子就可以随便取了，那么我们还要取几颗呢？$(r-n_i-n_j-2)$颗，带回我们上面的那个结论，我们就得到了：$\left|s_i \cap s_j \right|=C_{k+r-n_i-n_j-3}^{k-1}$

相信大家一定发现了其中的规律，后面的情况我就不多说了，然后我们就可以使用**容斥原理**了！

然后我们就得到了（好好理解一下↓）：
$$\left|\bigcup^k_{i=1}s_i\right|=\sum^k_{i=1}C_{k+r-n_i-2}^{k-1}-\sum_{1\leq i< j\leq n}C_{k+r-n_i-n_j-3}^{k-1}+\cdots+(-1)^{k+1}C_{k+r-\sum_{i=1}^kn_i-(k+1)}^{k-1}$$

So，最终答案：

$C_{k+r-1}^{k-1}-\sum^k_{i=1}C_{k+r-n_i-2}^{k-1}+\sum_{1\leq i< j\leq n}C_{k+r-n_i-n_j-3}^{k-1}-\cdots+(-1)^kC_{k+r-\sum_{i=1}^kn_i-(k+1)}^{k-1}$

---

打代码时要注意：

 - 我们可以枚举x从0到$2^k-1$，我们把x换成二进制后，假设有num位是1，分别是第$i_1,i_2,\cdots,i_{num}$，我们就表示：
 
$(-1)^{num}C_{k+r-n_{i_1}-n_{i_2}-\cdots -n_{i_p}-(num+1)}^{k-1} $

这样就可以保证我们扫到每一种情况了
 - 我们要算$C_b^a$的话，就得用$P_b^a$乘上a!的逆元（逆元是什么？[戳](https://blog.csdn.net/HenryYang2018/article/details/89372739)），别忘了一边乘，一边模


---

c++代码（CF451E）：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int ll p=1000000007;

int k;
ll r,n[25],inv[25];

ll pow(ll a,ll b,ll p){
    ll ans=1;
    while(b){
        if (b%2) ans=(ans*a)%p;
        b/=2;
        a=(a*a)%p;
    }
    return ans;
}

void get_inv(ll n,ll p){
    inv[1]=1;
    for (ll i=2;i<=n;i++){
        inv[i]=inv[p%i]*(p-p/i)%p;
    }
}

int C(ll y,ll x){
    if (y<0||x<0||y<x) return 0;
    y%=p;
    if (y==0 || x==0) return 1;
    ll ans=1;
    for (int i=0;i<x;i++){
        ans=1ll*ans*(y-i)%p;
    }
    for (int i=1;i<=x;i++){
        ans=1ll*ans*inv[i]%p;
    }
    return ans;
}

int main(){
    get_inv(20,p);
    scanf("%d%lld",&k,&r);
    ll ans=C(k+r-1,k-1);
    for (int i=1;i<=k;i++){
        scanf("%lld",&n[i]);
    }
    for (int x=1;x<1<<k;x++){
        ll t=k+r,num=0;
        for (int i=0;i<k;i++){
            if (x>>i & 1) num++,t-=n[i+1];
        }
        t-=num+1;
        if (num%2==1) ans=(ans-C(t,k-1))%p;
        else ans=(ans+C(t,k-1))%p;
    }
    printf("%lld",(ans+p)%p);
    return 0;
}
```

参考：
《算法竞赛进阶指南》 李煜东 著


---

## 作者：niiick (赞：22)

证明因为比较详细，所以略长，于博客内食用更佳
###[多重集下的组合数](https://blog.csdn.net/niiick/article/details/81745698)
####**多重集定义**

多重集是指**包含重复元素**的广义集合
例如$S=\{n_1\cdot a_1,n_2\cdot a_2,...,n_k\cdot a_k\}$就是由$n_1$个$a_1$，$n_2$个$a_2$，...，$n_k$个$a_k$组成的多重集
****************
####**多重集的排列数**

给定一个多重集$S=\{n_1\cdot a_1,n_2\cdot a_2,...,n_k\cdot a_k\}$
其排列数为
$$A=\frac{N!}{n_1!n_2!...n_k!}(N=\sum_{i=1}^kn_i)$$
***********************
####**多重集的组合数**

**（Q1）**
给定一个多重集$S=\{n_1\cdot a_1,n_2\cdot a_2,...,n_k\cdot a_k\}$
以及一个整数$m$，且有$m<=n_i(\forall i\in[1,k])$，
求从S中取出任意m个元素可以产生的**不同多重集**数量

**（A1）**
$ans=C_{k+m-1}^{k-1}$
#####**证明**

题目所求就是满足$\sum_{i=1}^kx_i=m$的多重集$\{x_1\cdot a_1,x_2\cdot a_2,...,x_k\cdot a_k\}$的数量

换句话说，
就是就是要给每个$x_i$赋值$[0,m]$中的任意整数，且所有$x_i$的和为m，
(这里因为有$m<=n_i(\forall i\in[1,k])$，所以不用考虑$x_i>n_i$的情况)

若我们用**0的个数表示每个**$x_i$**的值**

那么我们可以转化原问题为
**用**$k-1$**个**$1$**将**$m$**个**$0$**分为**$k$**组的方案数**

也就是**多重集**$\{m\cdot 0,(k-1)\cdot 1\}$的**排列数**，
故得
$$ans=\frac{(m+k-1)!}{m!(k-1)!}=C_{k+m-1}^{m}=C_{k+m-1}^{k-1}$$
***********************
**（Q2）**
给定一个多重集$S=\{n_1\cdot a_1,n_2\cdot a_2,...,n_k\cdot a_k\}$
以及一个整数$m(m<=\sum_{i=1}^kn_i$)，
求从S中取出任意m个元素可以产生的**不同多重集**数量
**（A2）**
$$ans=C_{k+m-1}^{k-1}-\sum_{i=1}^kC_{k+m-n_i-2}^{k-1}+\sum_{1<=i,j<=k,i!=j}C_{k+m-n_i-n_j-3}^{k-1}-...+(-1)^kC_{k+m-\sum_{i=1}^{k}n_i-(k+1)}^{k-1}$$
#####**证明**

上面的式子显然用到了**容斥定理**，
怎么理解呢

先不考虑$n_i$得限制，
那么从其中取m个元素的方案数为$C_{k+m-1}^{k-1}$

这里的方案数显然包含了$x_i>n_i$的不合法方案

设$S_i$表示**至少包含**$n_i+1$**个**$a_i$**的多重集**(也就是$a_i$个数不合法的多重集)，
我们需要从上述总方案数中减去$S_i$的数量

怎么求$S_i$的数量呢，
我们先**从**$S$**中取出**$n_i+1$**个**$a_i$，
再在$S$**任选**$m-n_i-1$**个元素**，
即构成了$S_i$，
根据Q1证明可得其数量为$C_{k+m-n_i-2}^{k-1}$

减去了所有只考虑$x_i>n_i$的不合法方案后，
会发现我们还多减去了$S_i\bigcap S_j$的数量
(也就是同时包含了至少$n_i+1$个$a_i$和至少$n_j+1$个$a_j$的多重集)，
我们再把这部分数量加回来$\sum_{1<=i,j<=k,i!=j}C_{k+m-n_i-n_j-3}^{k-1}$

反复容斥下去即可得到上述式子
$$ans=C_{k+m-1}^{k-1}-\sum_{i=1}^kC_{k+m-n_i-2}^{k-1}+\sum_{1<=i,j<=k,i!=j}C_{k+m-n_i-n_j-3}^{k-1}-...+(-1)^kC_{k+m-\sum_{i=1}^{k}n_i-(k+1)}^{k-1}$$
*******************
那么该题要如何应用上述式子呢

观察到n的范围很小，所以从n入手

我们枚举$x=0$~$2^n-1$，
对于每一个x，设其二进制表示下**共有p位为1**，
分别为$i_1,i_2,...,i_p$

于是可以用这个x表示上式中的一项$(-1)^pC_{n+m-f_{i_1}-f_{i_2}-...-f_{i_p}-(p+1)}^{n-1}$

那么每个$x=0$~$2^n-1$就可以用来**唯一**的描述上式中的**一项**，
这点从二进制角度证明很显然

再考虑每一项的组合数$C_{x}^{y}$，
由于x可能很大，所以稍作变换

以$C_{n+m-1}^{n-1}$为例
$C_{n+m-1}^{n-1}=A_{n+m-1}^{n-1}/(n-1)!=\frac{(n+m-1)!}{[(n+m-1)-(n-1)]!}*\prod_{i=1}^{n-1}inv[i]=\prod_{i=m+1}^{n+m-1}i*\prod_{i=1}^{n-1}inv[i]$
这样就限制组合数单次计算复杂度可以以O(n)记
******************

```
//niiick
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>
#include<cstdio>
using namespace std;
typedef long long lt;

lt read()
{
    lt f=1,x=0;
    char ss=getchar();
    while(ss<'0'||ss>'9'){if(ss=='-')f=-1;ss=getchar();}
    while(ss>='0'&&ss<='9'){x=x*10+ss-'0';ss=getchar();}
    return f*x;
}

const lt mod=1e9+7;
const int maxn=50;
lt a[maxn],inv[maxn];
lt ans;

lt C(lt n,lt m)
{
    if(n<0||m<0||n<m)return 0;
    if(n%mod==0||m==0)return 1;
    lt res=1;
    for(lt i=n-m+1;i<=n;++i)
    res*=(i%mod),res%=mod;
    for(int i=1;i<=m;++i)
    res*=inv[i],res%=mod;
    return res;
}

lt qpow(lt b,lt k)
{
    lt res=1;
    while(k>0)
    {
        if(k&1)res=(res*b)%mod;
        b=(b*b)%mod;
        k>>=1;
    }
    return res;
}

int main()
{
    lt n=read(),m=read();
    for(int i=1;i<=n;++i)a[i]=read();
    for(int i=1;i<=20;++i)inv[i]=qpow(i,mod-2);
    
    ans=C(n+m-1,n-1)%mod;
    for(int i=1;i<=(1<<n)-1;++i)
    {
        lt k=n+m,p=0;
        for(int j=0;j<n;++j)
        if((1<<j)&i)p++,k-=a[j+1];
        k-=p+1;
        if(p&1) ans-=C(k,n-1),ans%=mod;
        else ans+=C(k,n-1),ans%=mod;
    }
    printf("%lld",(ans+mod)%mod);
    return 0;
}
```





---

## 作者：dreagonm (赞：14)

# 一种母函数的做法

题目等价于求这样的一个问题

给出n个变量$x_1,x_2,\dots,x_n$，求方程$x_1+x_2+x_3+\dots+x_n=S$的整数解方案数且要满足$x_1\le f_1.x_2\le f_2,\dots,x_n\le f_n$

乍一看不是很好做，那怎么办？

看到$n\le20$，状压？其实生成函数也可以做

写出整个的生成函数
$$
G(x)=(1+x+x^2+\dots+x^{f_1})(1+x+x^2+\dots+x^{f_2})\dots(1+x+x^2+\dots+x^{f_n})
$$


通过等比数列求和公式，可以化成这样
$$
G(x)=\frac{(1-x^{f_1+1})(1-x^{f_2+1})\dots (1-x^{f_n+1})}{(1-x)^n}
$$
答案就是第s项系数

然后通过生成函数的公式

$$
G(x)= (1-x^{f_1+1})(1-x^{f_2+1})\dots (1-x^{f_n+1})\sum_{i=0}^{\infty}\left(\begin{matrix}n+i-1\\n-1\end{matrix}\right)x^i
$$

后面的暴力展开，最多有$2^n$项且系数只会有1或-1

考虑前面的项怎么做

假设现在求出了第k项，我们需要在后面的式子的第s-k项系数（如果k>s，忽略即可）

第s-k项的系数就是$\left(\begin{matrix}n+s-k-1\\n-1\end{matrix}\right)$，但是s有$10^{14}$，我们还需要变形一下
$$
\left(\begin{matrix}n+s-k-1\\n-1\end{matrix}\right) 
$$
$$
=\frac{(n+s-k-1)!}{(n-1)!(s-k)!}
$$
$$
=\frac{\prod_{i=s-k+1}^{n+s-k-1}i}{(n-1)!}
$$
然后就相当可做了

~~推出来的式子好像和直接状压没啥区别~~

## 代码
```
#include <set>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define int long long
const int MOD = 1000000007;
using namespace std;
int jcn_1=1,inv_jcn_1,n,f[100],s,ans=0;
int pow(int a,int b){
    int ans=1;
    a%=MOD;
    while(b){
        if(b&1)
            ans=(ans*a)%MOD;
        a=(a*a)%MOD;
        b>>=1;
    }
    return ans;
}
int C(int k){//k
    int ans=1;
    for(int i=s-k+1;i<=n+s-k-1;i++)
        ans=(ans*(i%MOD))%MOD;
    return ans*inv_jcn_1%MOD;
}//return c(x,n-1)
void dfs(int pos,int opt,int x){
    if(pos==n){
        if(x>s)
            return;
        ans=((ans+opt*C(x))%MOD+MOD)%MOD;
        return;
    }
    dfs(pos+1,opt,x);
    dfs(pos+1,-opt,x+f[pos+1]+1);
}
signed main(){
    scanf("%I64d %I64d",&n,&s);
    for(int i=1;i<n;i++)
        jcn_1*=i;
    inv_jcn_1=pow(jcn_1,MOD-2);
    for(int i=1;i<=n;i++)
        scanf("%I64d",&f[i]);
    dfs(0,1,0);
    printf("%I64d\n",ans);
    return 0;
}
```
### 小广告
[我的博客](https://www.cnblogs.com/dreagonm/)

---

## 作者：An_Account (赞：12)

首先，一句话题意：

有$s$个球，$n$个盒子，第$i$个盒子最多能放$f[i]$个球，也可以不放，问放球的方法总数模$10^9+7$的模数。

---

如果盒子没有容纳限制，那么这个题就是一道经典的组合数学题，答案直接$C^{n-1}_ {s+n-1}$，但这道题有$f$的限制，比较讨厌。

下面介绍两种方法。

## 1.母函数

这题的母函数很容易表示出来，为

$f(x)=(1+x^1+x^2\dots+x^{f[1]})(1+x^1+x^2\dots+x^{f[2]})\dots(1+x^1+x^2\dots+x^{f[n]})$

答案则为$x^s$项的系数，可惜此题中$f[i]$很大，因此不能使用母函数。

**我着重介绍以下的方法**

## 2.状压+组合数+容斥原理+Lucas定理

注意到除了$n$以外的数都特别大，而$n$特别小，只有$n<=20$。这让我们联想到了状态压缩，$2^{20}$的状态大小可以承受。

因此，我们枚举状态$k$。第$i$位表示第$i$个盒子是否放了超过其容量的球。考虑**逆向求解**，则答案为方案总数-不合法方案总数

方案总数比较简单，为$C^{n-1}_ {s+n-1}$。如果第$i$个盒子放的球数超过了其容量，那么显然，它至少放了$f[i]+1$个球。

我们将所有多放的球从总数中剔除出去，则剩下$m=s-\sum_{i\in k}{(f[i]+1)}$个球，且此时已经满足所有属于$k$的$i$号盒子都超过了其容量。如果有$s<m$，则跳过这种情况，否则共有$C^{n-1}_ {s-m+n-1}$种情况。

```cpp
for (int i=0;i<(1<<n);i++) {
	LL cnt=s;
	for (int j=1;j<=n;j++)
		if (i&(1<<(j-1))) 
			cnt-=f[j]+1;
	if (cnt<0) continue;
	res=(res+C(cnt+n-1,n-1))%mod;
}
```

但注意，这并不是最终的答案，因为假如我们计算出了一个放满了$l$个盒子的解，其实这个解的含义是“至少放满了$l$个盒子”，也就是说，它包含放满$l,l+1,l+2\dots n$个盒子的答案，明显有重复。

所以我们使用容斥原理，若状态中有奇数个盒子超出了范围，那么就在$res$中减，否则就加。

```cpp
for (int i=0;i<(1<<n);i++) {
	LL cnt=s;int del=1;
	for (int j=1;j<=n;j++)
		if (i&(1<<(j-1))) 
			cnt-=f[j]+1,del=-del;
	if (cnt<0) continue;
	res=(res+C(cnt+n-1,n-1)*(LL)del)%mod;
}
```

最后说一下Lucas定理：解决大组合数取模。注意此题中组合数的第一项是一个可能为$10^{14}$的数，不能使用常规方法。

```cpp
LL Lucas(LL a,LL b) {
	if (a<=mod&&b<=mod) return C(a,b);
	return C(a%mod,b%mod)*Lucas(a/mod,b/mod)%mod;//Lucas
}
```

附上AC代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define LL long long
const LL mod=1e9+7;
LL Pow(LL x,LL y) {
	LL res=1;
	while (y) {
		if (y&1) res=res*x%mod;
		x=x*x%mod,y>>=1;
	}
	return res;
}
LL C(int n,int r) {
	if (n<r) return 0;
	r=min(r,n-r);
	LL res=1,a=1,b=1;
	for (int i=1;i<=r;i++)
		a=a*(n-i+1)%mod,b=b*i%mod;
	res=res*a%mod*Pow(b,mod-2)%mod;
	return res;
}
LL Lucas(LL a,LL b) {
	if (a<=mod&&b<=mod) return C(a,b);
	return C(a%mod,b%mod)*Lucas(a/mod,b/mod)%mod;
}
LL f[21];
LL solve(int n,LL s) {
	LL res=0;
	for (int i=0;i<(1<<n);i++) {
		LL cnt=s;int del=1;
		for (int j=1;j<=n;j++)
			if (i&(1<<(j-1))) 
				cnt-=f[j]+1,del=-del;
		if (cnt<0) continue;
		res=(res+Lucas(cnt+n-1,n-1)*(LL)del)%mod;
	}
	return (res+mod)%mod;
}
int main() {
	int n;LL s;
	while (~scanf("%d%lld",&n,&s)) {
		for (int i=1;i<=n;i++) scanf("%lld",&f[i]);
		printf("%lld\n",solve(n,s));
	}
}
```

---

## 作者：whiteqwq (赞：9)

[CF451E Devu and Flowers](https://www.luogu.com.cn/problem/CF451E)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1729522)

## 题意
题意：$n$种颜色，每种颜色$f_i$朵花，需要选择$m$朵花，求有多少种选择方案（两个方案不同当且仅当存在某一种颜色的花数量不同），对$1000000007$取模。
数据范围：$1\leqslant n\leqslant 20,0\leqslant m\leqslant 10^{14}$。

## 分析
这是一道求多重集合组合数的题目，比较好地考察了容斥原理和组合数计算。

可以抽象出模型：求在一个存在$n$个元素，每个元素有$f_i$个的可重集取出$m$个元素的方案数。

我们令$s_i$为满足第$i$个元素选择的数量在$f_i$以内，且取出了$m$个元素的方案形成的集合，那么我们的答案便是$|\bigcap_{i=1}^n s_i|$。

因为$s_i$是求至多选多少个，所以不是很好求，那么先容斥一波，
$$|\bigcap_{i=1}^n s_i|=|U|-|\bigcup_{i=1}^n\bar{s_i}|$$

全集就是$n$种元素取出$m$个元素的方案数（某个元素可以选出$0$个），直接套公式：$|U|=C_{n+m-1}^{n-1}$（具体可以考虑一种特殊的隔板法，加入$n-1$个球，选择$n-1$个球间隔出$n$个区间，这些区间可以为$0$）

考虑如何求并集，还是不好求，所以继续容斥：
$$|\bigcup_{i=1}^n \bar{s_i}|=\sum_{k=1}^n(-1)^{k-1}\sum_{a_1<a_2<\cdots<a_k}|\bar{s_{a_1}}\cap \bar{s_{a_2}}\cap\cdots\cap \bar{s_{a_k}}|$$

因为$n$很小，所以可以考虑二进制枚举每一种情况，然后问题转移成怎么求某一种元素$i$选的次数要超过$f_i$并取出$m$个元素的方案数。

因为起码要选$f_i+1$个这种元素，所以可以把选出的$m$减去$f_i+1$，这样就转化为全集那里讲的公式了。

然后直接套公式，套在容斥原理里面，就ok了。

最后，因为$m$很大，所以可以吧组合数$C_n^m=\frac{n!}{m!\cdot(n-m)!}$拆开，变为$n\cdot(n-1)\cdot\cdots\cdot(n-m+1)\cdot\frac{1}{m!}$，然后预处理一下就可以了。

## 代码
```
#include<stdio.h>
const long long maxn=25,mod=1000000007;
long long i,j,k,m,n,mul=1,ans;
long long finv[maxn],a[maxn];
long long ksm(long long a,long long b){
	long long res=1;
	while(b){
		if(b&1)
			res=res*a%mod;
		a=a*a%mod,b>>=1;
	}
	return res;
}
long long c(long long n,long long m){
	if(n<0||m<0||m>n)
		return 0;
	n%=mod,m%=mod;
	long long res=1;
	for(long long i=n-m+1;i<=n;i++)
		res=res*i%mod;
	res=res*finv[m]%mod;
	return res;
}
int main(){
	scanf("%lld%lld",&n,&m);
	for(i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	for(i=1;i<=n;i++)
		mul=mul*i%mod;
	finv[n]=ksm(mul,mod-2);
	for(i=n;i>=1;i--)
		finv[i-1]=finv[i]*i%mod;
	ans=c(n+m-1,n-1);
	for(k=1;k<(1<<n);k++){
		long long cnt=0,res=n+m-1;
		for(i=1;i<=n;i++)
			if((k>>(i-1))&1)
				cnt++,res-=a[i]+1;
		ans=(ans-(cnt%2==0? -1:1)*c(res,n-1))%mod;
	}
	printf("%lld\n",(ans+mod)%mod);
	return 0;
}
```

---

## 作者：MyukiyoMekya (赞：7)

观察到 $s,f_i$ 很大，$n$ 很小，自然会考虑到容斥。

发现计算第 $i$ 个只能放 $\le f_i$ 个的似乎不太好处理，如果是计算第 $i$ 个必须放 $>f_i$ 个的方案数就好多了。

记 $P_i$ 表示当前计算的方案是否满足第 $i$ 个必须放 $>f_i$ 个的限制，

$|P_1\cup P_2\cup \cdots \cup P_k|$ 表示满足 $P_1$ 或 $P_2$ 或 ... $P_k$ 的方案数，$|P_1\cap \cdots \cap P_k|$ 表示 $P_{1\cdots k}$ 都满足的方案数，某个 $P_j$ 不出现说明随意选。 

根据隔板法和 `合法方案=总方案-不合法方案`，答案显然等于 $C_{s+n-1}^{n-1}-|P_1\cup P_2\cup \cdots P_n|$，$C$ 是组合数。

然后发现 $|\bigcup_{i=1}^m P_{c_i}|$ 不好算，$|\bigcap_{i=1}^m P_{c_i}|$ 显然等于 $C_{s-(m+\sum_{i=1}^m f_{c_i})+n-1}^{n-1}$，那么直接上容斥
$$
\bigcup_{i=1}^n=\sum_{S}{(-1)^{|S|}|\bigcap_{i\in S}P_i|}
$$
发现组合数上标很大，下标很小所以可以通过 $\mathcal O(m)$ 计算 $C_n^m$ 的方法和卢卡斯定理来搞。总复杂度 $\mathcal O(2^n(n+n\log p))$。

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define int long long
#define ln std::puts("")
const int p=1e9+7;
const int S=1e5;
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
int buf[21],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');return;}
inline int fpow(int a,int b)
{
	reg int res=1;
	for(;b;b>>=1,a=a*a%p)
		if(b&1)
			res=res*a%p;
	return res;
}
inline int C(int n,int m)
{
	if(n<m)return 0;
	m=std::min(m,n-m);
	reg int ans=1;
	for(int i=0;i<m;++i)
		(ans*=(n-i)*fpow(i+1,p-2)%p)%=p;
	return ans;
}
inline int lucas(int n,int m)
{
	if(n<m)return 0;
	if(!m)return 1;
	return lucas(n/p,m/p)*C(n%p,m%p)%p;
}
int a[20];
signed main(void)
{
	int n,s;read(n,s);
	for(int i=0;i<n;++i)read(a[i]);
	reg int ans=0;
	for(int m=0;m<(1<<n);++m)
	{
		reg int Sum=0,cnt=0;
		for(int i=0;i<n;++i)if(m&(1<<i))Sum+=a[i],++cnt;
		(ans+=lucas(s-Sum-cnt+n-1,n-1)*((cnt&1)?(p-1):1)%p)%=p;
	}
	write(ans),ln;
	return 0;
}
```



---

## 作者：Leap_Frog (赞：3)

### P.S.
还挺清新的吧，感觉不需要像一楼的高妙 `多重集的组合数`  
直接来个反演，啪地一下做完了，很快啊 ![](//xn--9zr.tk/xia)  

### Description.
有 $n$ 种球，每种有 $\{a_i\}$ 个，求无序选出 $s$ 个球的方案数。  

### Solution.
首先这个 $n\le20$ 范围很假，考虑在 $n$ 做文章。  
我们设 $G(S)$ 表示 $S$ 集合不满足限制，而 $\forall x\not\in S$ 第 $x$ 位满足限制的方案数。  
设 $F(S)$ 表示集合 $S$ 集合不满足限制，其他任意的方案数。  
那么显然有 $F(S)=\sum_{S\subseteq T}G(T)$  
子集反演一下就有 $G(S)=\sum_{S\subseteq T}(-1)^{|T|-|S|}F(T)$  
我们要求 $G(\varnothing)=\sum_{T}(-1)^{|T|}F(T)$  
所以我们只要 $O(n)$、$O(1)$ 知道这个 $F(T)$ 怎么求就可以通过此题。  
首先，我们把所有不满足限制的给 $a_i$ 加一个，因为这边仅考虑那些满足限制的方案数。  
对于剩下的，我们可以不满足也可以满足，所以就相当于是球无限。  
转换一下模型就变成了 $|T|$ 个不同盒子有 $s-\sum_{x\not\in T}(a_x+1)$ 个相同的球盒子可以空的放球问题。  
直接插板法就是个组合数 $\dbinom{|T|-1}{s-\sum_{x\not\in T}(a_x+1)+|T|-1}$  
注意组合数下标大于模数，可以用 Lucas 不过这题 $|T|$ 很小可以直接按定义暴拆。  
然后这题就做完了，复杂度 $O(2^n\times n)$  

### Coding.
```cpp
//是啊……你就是那只鬼了……所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}/*}}}*/
const int P=1e9+7;int n;ll s,a[21],iv[21];
inline int C(ll n,int m)
{//组合数
	if(n<0||m<0||n<m) return 0;else if(!m||n%P==0) return 1;
	int r=1;for(ll i=n-m+1;i<=n;i++) r=i%P*r%P;
	for(int i=1;i<=m;i++) r=1ll*iv[i]*r%P;
	return r;
}
int main()
{
	read(n),read(s);for(int i=1;i<=n;i++) read(a[i]);
	iv[1]=1;for(int i=2;i<=n;i++) iv[i]=1ll*iv[P%i]*(P-P/i)%P;
	int rs=0;for(int S=0;S<(1<<n);S++)
	{//反演
		char cn=0;ll lim=s;
		for(int i=0;i<n;i++) if((S>>i)&1) cn^=1,lim-=a[i+1]+1;
		if(cn) rs=(rs+P-C(lim+n-1,n-1))%P;else rs=(rs+C(lim+n-1,n-1))%P;
	}
	return printf("%d\n",rs),0;
}
```

---

## 作者：JustinRochester (赞：2)

[洛谷传送门](https://www.luogu.com.cn/problem/CF451E)

[cf传送门](https://codeforces.com/problemset/problem/451/E)

贡献一个只用到基础组合数学+容斥的做法

---

假设每种花都是无穷多的。那么，方案数显然相当于 $s$ 个小球，分 $k$ 组，每组至少 $0$ 个的方案数。

考虑初始加入 $n$ 个小球，按每组至少 $1$ 个进行插空分配，之后再抽走。方案数显然为 $\dbinom{s+n-1}{n-1}$ 。

当然，这个分法显然有问题，因为每种花并不是无穷多的，这种分法可能导致一些花比限制条件更多。

现考虑某集合 $S$ ，集合中的每种花都**严格多于**限制条件。则对于集合中的某种花 $i$ ，选择第 $i$ 种花的数量 $>f_i$ ，即 $\geq f_i+1$ 。

因此，不妨设 $\displaystyle f_S=\sum_{i\in S}(f_i+1)$ 。

考虑集合 $S$ 中每种花都**严格多于**限制条件的方案数，等价于先将 $s$ 个小球中选出 $f_S$ 个，剩余的部分分 $k$ 组，每组至少 $0$ 个。分配后，再将 $f_S$ 个按需分配回去。因此，方案数为 $\dbinom{s-f_S+n-1}{n-1}$ 。

最后求每种花都不多于限制条件的方案数，则进行容斥：

有 $0$ 个超限的 $-$ 有 $1$ 个超限的 $+$ 有 $2$ 个超限的 $\cdots $

$\displaystyle ans=\sum_{S}(-1)^{|S|}\dbinom{s-f_S+n-1}{n-1}$

由于 $n-1\leq 19$ ，直接暴力展开组合数即可，复杂度为 $O(n\cdot 2^n)$

---

**【代码】**
---

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=1e9+7;
inline ll fpow(ll a,ll x) { ll ans=1; for(a%=MOD;x;x>>=1,a=a*a%MOD) if(x&1) ans=ans*a%MOD; return ans; }
inline ll inv(ll a) { return fpow(a,MOD-2); }
//快速幂 & 逆元
ll n,s,f[1<<20],invn;//invn 为 (n-1)! 的逆元
inline ll C(ll n,ll m){
     if(m<0||m>n) return 0;
     ll ans=1;
     for(int i=1;i<=m;i++)
          ans=(n-i+1)%MOD*ans%MOD;
     return ans*invn%MOD;
}
inline ll calc(ll S){
     if(S&(S-1)) f[S]=f[S^(S&(-S))]+f[S&(-S)];
     return C(s-f[S]+n-1,n-1);
}
int main(){
     ios::sync_with_stdio(0);
     cin.tie(0); cout.tie(0);
     cin>>n>>s;
     invn=1;
     for(int i=1;i<=n-1;i++) invn=invn*i%MOD;
     invn=inv(invn);
     for(int i=1,s=1;i<=n;i++,s<<=1) cin>>f[s],++f[s];
     ll Ans=0;
     for(int i=0;!(i>>n);i++)
          Ans=( Ans+calc(i)*((__builtin_popcount(i>>10)+__builtin_popcount(i&1023)&1)?-1:1) )%MOD;
     //__builtin_popcount(i) 可以直接算出 i 二进制中 1 的个数，但要 i 相对较小的时候
     Ans=(Ans%MOD+MOD)%MOD;
     cout<<Ans;
     cout.flush();
     return 0;
}
```

---

## 作者：傅思维666 (赞：2)

## 题解：

排列组合这个地方的确比较难理解，来给大家用大白话讲一下。

多重集排列组合。

不妨反着来：对于有$N$种元素的多重集$S$，选$K$个元素，注意是个不是种，的可行方案数。可以变成：现在有$N$个篮子，把$K$个元素扔进这些篮子里的方案数。

注意，这种是特殊情况，也就是说，每种元素无限多个可供挑选。

这样的话，用隔板法解决问题。

容易得出，答案也就是$C_{N+K-1}^{N-1}$。

解释一下，现在有$K$个元素，分成$N$堆，也就是要往里插入$N-1$块板。按理讲应该是$C_{K+1}^{N-1}$，但是因为允许有空集，也就是不插，那么就相当于每块板子插进去之后又产生了新元素，所以是这个答案。

那么，根据多重集的限制，现在每种元素有一个数量上限，怎么办呢？

很简单，采用容斥原理。关于容斥原理，请见：

[浅谈容斥原理](https://www.cnblogs.com/fusiwei/p/13995045.html)

上限是“至多放$f[i]$个”，那么如果我往这个里面放$f[i]+1$个，是不是就不合法了？

把不合法的减去即可。

因为这道题N只有20，所以考虑状压，表示当前这个集合超没超。

最后根据容斥，如果当前状态1的个数是奇数，就要减去，是偶数，就要加上。

代码：

```cpp
#include<cstdio>
#define ll long long
using namespace std;
const int maxn=25;
const int mod=1e9+7;
int n;
ll s;
ll f[maxn],inv[maxn];
ll calc(ll n,ll m)
{
	if(n<0||m<0||n<m)
		return 0;
	n%=mod;
	if(n==0||m==0)
		return 1;
	ll ret=1;
	for(int i=0;i<m;i++)
		ret=(ret*(n-i))%mod;
	for(int i=1;i<=m;i++)
		ret=(ret*inv[i])%mod;
	return ret;
}//n中选m的组合数
ll qpow(ll a,ll b)
{
	ll ret=1;
	while(b)
	{
		if(b&1)
			ret=(ret*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return ret;
}
int main()
{
	scanf("%d%lld",&n,&s);
	for(int i=1;i<=n;i++)
		scanf("%lld",&f[i]);
	for(int i=1;i<=20;i++)
		inv[i]=qpow(i,mod-2);
	ll ans=calc(n+s-1,n-1)%mod;
	for(int i=1;i<(1<<n);i++)
	{
		ll tot=n+s;
		int p=0;
		for(int j=0;j<n;j++)
			if(i>>j&1)
			{
				p++;
				tot-=(f[j+1]+1);
			}
		tot--;
		if(p&1)
			ans=(ans-calc(tot,n-1))%mod;
		else
			ans=(ans+calc(tot,n-1))%mod;
	}
	printf("%lld\n",(ans+mod)%mod);
	return 0;
}
```



---

## 作者：子归 (赞：2)

## 经典容斥
题意就不说了.  
### 解法
#### 理想情况
理想每一组中可以取无限朵花，那么我们就需要达到$x_1+x_2+x_3+……+x_n=M$。
此时$x_i>=0$，那么令$y_i=x_i+1$，则$y_1+y_2+y_3+……+y_n=M+N$。
因为$y_i>=1$，所以可以用隔板法,在$M+N-1$个空隙中插入$N-1$个板,答案为$C_{M+N-1}^{N-1}$。
#### 实际
在实际中有$x_1<=A_1,x_2<=A_2,x_3<=A_3……x_n<=A_n$等条件，此时就需要同时满足这N个条件。
那么正难则反，考虑求补集，也就是至少不满足其中一个条件的方案。就可以用总方案减去这些方案就可以得出答案。
设不满足$i$的方案为$s_i$，  
那么答案就是$C_{M+N-1}^{N-1}-|s_1\bigcup s_2\bigcup s_3……\bigcup s_n|$。  
将其展开就是：
$C_{M+N-1}^{N-1}-|s_1|-|s_2|-……|s_3|+|s_1\bigcap s_2|+……-|s_1\bigcap s_2\bigcap s_3|-……$。  
就是一个容斥原理的展开。
考虑$s_i$怎么求。以$s_1$举例，假如要求$s_1$，就代表我们必须从第一组里取出至少$A_1+1$朵花，那么此时还剩$M-(A_1+1)$朵花。剩下的就是隔板，  
那么此时方案就是$C_{M+N-1-(A_1+1)}^{N-1}$。
那么$|s_1\bigcap s_2|$同上，方案就是$C_{M+N-1-(A_1+1)-(A_2+1)}^{N-1}$。  
整理一下，就得到 $res=C_{M+N-1}^{N-1}-\sum\limits_{i=1} C_{M+N-1-(A_i+1)}^{N-1}+\sum\limits_{i<j} C_{M+N-1-(A_i+1)-(A_j+1)}^{N-1}-……$。
总所周知，容斥复杂度$O(2^n)$，那么可以从$0枚举到2^{n-1}$。
然后把每一个条件看成一个二进制位,如果是$1$或$0$就代表遵守或不遵守这个条件，奇数个就减，偶数个就加。
那么怎么去算组合数，可以发现虽然$M$非常大，但是我们的$N$很小，所以只需按着定义去算，大概是$N$的复杂度。所以总的复杂度就是$O(2^N*N)$。
## 参考代码
```cpp
/*
    容斥+组合数计算.
*/
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
typedef long long ll;
const int N=25;
ll n,m;
int res;
ll a[N];
int down=1;
int ksm(int a,int b) {
	int res=1;
	while(b) {
		if(b&1) res=1ll*res*a%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}
	return res;
}
int C(ll a,ll b) {
	if(a<b) return 0;
	int up=1;
	for(ll i=a; i>a-b; --i) up=i%mod*up%mod;
	return 1ll*up*down%mod;
}
int main() {
	scanf("%lld%lld",&n,&m);
	for(int i=0; i<n; ++i) scanf("%lld",&a[i]);
	for(int i=1; i<=n-1; ++i) down=1ll*i*down%mod;
	down=ksm(down,mod-2);
	for(int i=0; i<(1<<n); ++i) {
		ll d=m+n-1,up=n-1;
		int sign=1;
		for(int j=0; j<n; ++j) {
			if((i>>j)&1) {
				sign*=-1;
				d-=a[j]+1;
			}
		}
		res=(res+C(d,up)*sign)%mod;
	}
	printf("%d\n",(res+mod)%mod);
	return 0;
}
```


---

## 作者：kouylan (赞：1)

这道题就是求一个可重集的本质不同子集数量。

当 $m\leq a_i$ 时，采用隔板法，答案是 $\dbinom{m+n-1}{n-1}$。

当 $m>a_i$ 时，正面计算困难，我们考虑计算不合法的情况。

总情况依然是$\dbinom{m+n}{n-1}$。不合法的情况就是存在一个元素它的个数至少是 $a_i+1$。

所以我们可以设 $L_i$ 表示第 $i$ 种元素的个数至少是 $a_i+1$ 的子集个数，那么就是在 $m-a_i-1$ 个元素中做隔板。$L_i$ 就等于 $\dbinom{m-a_i-1+n}{n-1}$。

但这样求完之后，我们发现如果有多个元素都不合法，这就被我们多算了一遍，所以我们要容斥。

稍微优化一下状态，$L_s$ 表示在 $s$ 状态下的元素均不合法的方案数，其中 $s$ 是一个二进制数，其中有 $k$ 个 $1$。那么 $L_s=\dbinom{m-\sum_{i\in s}a_i-k+n-k}{n-1}$。根据 $k$ 的奇偶确定容斥系数的正负即可。

最后一件事，就是此时 $m,a_i$ 较大，所以要推一下组合数的计算。

$\dbinom{n}{m}=\dfrac{n!}{m!(n-m)!}=\prod_{n-m+1}^{n}i\times\prod_{i=1}^{m}inv_i$，$n$ 较大 $m$ 较小时就用这种方法。

下面是 AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int M = 1e9+7ll;

int n,m,a[25],ans,inv[25];

int ksm(int x,int w)
{
	int s=1;
	while(w)
	{
		if(w&1)
			s = s*x%M;
		x = x*x%M;
		w >>= 1;
	}
	return s;
}

int c_(int n,int m)
{
	if(n<0 || m<0 || n<m)
		return 0;
	int res=1;
	for(int i=n-m+1;i<=n;i++)
		res = res*(i%M)%M;
	for(int i=1;i<=m;i++)
		res = res*inv[i]%M;
	return res;
}

signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;cin>>a[i++]);
	for(int i=0;i<=n+2;i++)
		inv[i] = ksm(i,M-2);
	for(int s=0;s<=(1<<n)-1;s++)
	{
		int sum=0,k=0,fl=1;
		for(int i=1;i<=n;i++)
			if(s>>i-1&1)
			{
				if(a[i]>=m)
					fl = 0;
				k++, sum += a[i];
			}
		if(fl==0)
			continue;
//		cout<<s<<endl;
		if(k%2==0)
			ans = (ans+c_(m-sum-k+n-1,n-1))%M;
		else
			ans = (ans-c_(m-sum-k+n-1,n-1)+M)%M;
	}
	cout<<ans<<endl;
	
	return 0;
}
```

祝大家 AC 愉快！

---

## 作者：wtyqwq (赞：0)

[CF451E Devu and Flowers](https://www.luogu.com.cn/problem/CF451E)

注：本文全文均出自李煜东的《算法竞赛进阶指南》，讲解清晰易懂，表达规范准确，希望能帮助到大家。

  多重集的排列数：多重集是指包含重复元素的广义集合。设 $S=\{n_1\cdot a_1,n_2\cdot a_2,\cdots,n_k\cdot a_k\}$ 是由 $n_1$ 个 $a_1$，$n_2$ 个 $a_2\cdots n_k$ 个 $a_k$ 组成的多重集。$S$ 的全排列数为；
  $$\frac{n!}{n_1!\times n_2!\times \cdots \times n_k !}$$
  
  多重集的组合数：设 $S=\{n_1\cdot a_1,n_2\cdot a_2,\cdots,n_k\cdot a_k\}$ 是由 $n_1$ 个 $a_1$，$n_2$ 个 $a_2\cdots n_k$ 个 $a_k$ 组成的多重集，设整数 $r\le n_i(\forall i \in [1,k])$。从 $S$ 中取出 $r$ 个元素组成一个多重集（不考虑元素的顺序），产生的不同多重集的数量为：
  $$C_{k+r-1}^{k-1}$$

  证明：原问题等价于统计下列集合的数量：$\{x_1\cdot a_1,x_2\cdot a_2,\cdots ,x_k\cdot a_k\}$，其中 $\sum_{i=1}^k x_i = r$ 并且 $x_i\le n_i$。因为 $r\le n_i$，所以必定有 $x_i\le n_i$，所以只需考虑 $\sum_{i=1}^k x_i = r$ 这一个条件。故原问题等价于 $r$ 个 $0$，$k-1$ 个 $1$ 构成的全排列数。$k-1$ 个 $1$ 把 $r$ 个 $0$ 分成 $k$ 组，每组的 $0$ 的数量对应 $x_i$。而多重集 $\{r\cdot 0,(k-1)\cdot 1\}$ 的全排列数为：
  
  $$\frac{(r+k-1)!}{r!\times (k-1)!}=C_{k+r-1}^r=C_{k+r-1}^{k-1}$$
  
  容斥原理：设 $S_1,S_2,\cdots,S_n$ 为有限集合，$|S|$ 表示集合 $S$ 的大小，则：
  
  $$\left|\bigcup_{i=1}^n S_i\right|=\sum_{i=1}^n|S_i|-\sum_{1\le i < j \le n}|S_i\cap S_j|+\sum_{1\le i<j<k\le n} |S_i\cap S_j \cap S_k|+\cdots+(-1)^{n+1}S_1\cap \cdots \cap S_n|$$
  
  多重集的组合数：设 $S=\{n_1\cdot a_1,n_2\cdot a_2,\cdots,n_k\cdot a_k\}$ 是由 $n_1$ 个 $a_1$，$n_2$ 个 $a_2\cdots n_k$ 个 $a_k$ 组成的多重集，设整数 $n=\sum_{i=1}^k n_i$。对于任意整数 $r\le n$，从 $S$ 中取出 $r$ 个元素组成一个多重集（不考虑元素的顺序），产生的不同多重集的数量为：
  
  $$C_{k+r-1}^{k-1}-\sum_{i=1}^k C_{k+r-n_i-2}^{k-1}+\sum_{1\le i<j\le k} C_{k+r-n_i-n_j-3}^{k-1}-\cdots+(-1)^k C_{k+r-\sum_{i=1}^k n_i - (k+1)}^{k-1}$$
  
  证明：若不考虑 $n_i$ 的限制，从 $S$ 中任选 $r$ 个元素，方案数为 $C_{k+r-1}^{k-1}$。设 $S_i(1\le i\le k)$ 表示至少包含 $n_i+1$ 个 $a_i$ 的多重集。我们先从 $S$ 中取出 $n_i+1$ 个 $a_i$，然后再任选 $r-n_i-1$ 个元素，即可构成 $S_i$。与上面同理，可构成的不同 $S_i$ 的数量为 $C_{k+r-n_i-2}^{k-1}$。
  
  进一步地，先从 $S$ 中取出 $n_i+1$ 个 $a_i$ 和 $n_j+1$ 个 $a_j$，然后再任选 $r-n_i-n_j-2$ 个元素，即可构成 $S_i\cap S_j$，方法数为：
  
  $$C_{k+r-n_i-n_j-3}^{k-1}$$
  
  根据容斥原理，至少有一种 $a_i$ 选取数量超过 $n_i$ 限制的多重集共有：
  
  $$\left|\bigcup_{i=1}^n S_i\right|=\sum_{i=1}^k C_{k+r-n_i-2}^{k-1}-\sum_{1\le i<j\le k} C_{k+r-n_i-n_j-3}^{k-1}+\cdots +(-1)^kC_{k+r-\sum_{i=1}^k n_i - (k+1)}^{k-1}$$
  
  故满足所有限制的合法多重集共有 $C_{k+r-1}^{k-1}-|\bigcup_{i=1}^kS_i|$ 个。
  
  回到本题，我们设第 $i$ 个盒子中花颜色为 $B_i$，则本题等价于从多重集 $S=\{A_1\cdot B_1,A_2\cdot B_2,\cdots,A_n\cdot B_n\}$ 中选出 $M$ 个元素能够产生的不同多重集的数量。根据多重集组合数的结论，本题的答案为：
  
  $$C_{N+M-1}^{N-1}-\sum_{i=1}^N C_{N+M-A_i-2}^{N-1}+\sum_{1\le i<j\le N}C_{N+M-A_i - A_j-3}^{N-1}-\cdots+(-1)^N C_{N+M-\sum_{i=1}^NA_i -(N+1)}^{N-1}$$
  
  在具体实现时，我们可以枚举 $x=0\sim 2^N-1$，若 $x$ 在二进制表示下共有 $p$ 位为 $1$，分别是第 $i_1,i_2,\cdots,i_p$ 位，则这个 $x$ 就代表上式中的一项：
  
  $$(-1)^p C_{N+M-A_{i_1}-A_{i_2}-\cdots -A_{i_p}-(p+1)}^{N-1}$$
  
  特别地，$x=0$ 代表 $C_{N+M-1}^N$。这样我们可以得到容斥原理计算多重集组合数的公式的每一项。
  
  对于每一项组合数，$N$ 的范围很小，但 $M$ 的范围很大。我们以 $C_{N+M-1}^{N-1}$ 为例，因为 $C_{N+M-1}^{N-1}=\large \frac{P_{N+M-1}^{N-1}}{(N-1)!}$，所以可以先计算排列数 $P_{N+M-1}^{N-1}=\large \frac{(N+M-1)!}{M!}$，也就是 $(N+M-1)\times (N+M-2)\times \cdots \times(M+1)$，然后再乘上 $(N-1)!$ 的乘法逆元。 我们还可以应用 $\text{Lucas}$ 定理，先把 $N+M-1$ 对 $10^9+7$ 取模，再计算组合数，避免乘法结果溢出 $64$ 位整数的表示范围。

---

