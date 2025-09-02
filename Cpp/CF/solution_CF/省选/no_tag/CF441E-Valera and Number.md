# Valera and Number

## 题目描述

Valera is a coder. Recently he wrote a funny program. The pseudo code for this program is given below:

```plain
//input: integers x, k, p
a = x;
for(step = 1; step <= k; step = step + 1){
    rnd = [random integer from 1 to 100];
    if(rnd <= p)
        a = a * 2;
    else
        a = a + 1;
}

s = 0;

while(remainder after dividing a by 2 equals 0){
    a = a / 2;
    s = s + 1;
}
```

Now Valera wonders: given the values $ x $ , $ k $ and $ p $ , what is the expected value of the resulting number $ s $ ?

## 说明/提示

If the concept of expected value is new to you, you can read about it by the link:

http://en.wikipedia.org/wiki/Expected\_value

## 样例 #1

### 输入

```
1 1 50
```

### 输出

```
1.0000000000000
```

## 样例 #2

### 输入

```
5 3 0
```

### 输出

```
3.0000000000000
```

## 样例 #3

### 输入

```
5 3 25
```

### 输出

```
1.9218750000000
```

# 题解

## 作者：do_while_true (赞：18)

感觉是 dp 好题啊！

这里令 $n$ 作为原题面中的 $k$．

**方法一**：我认为的通过常规思路想出来的做法。

正常思路是设 $f_{i,x}$ 表示操作了 $i$ 步得到 $x$ 的概率。但是由于 $x$ 是 $10^9$ 级别，复杂度过于大。

如果 $\times 2$ 将其看作从后面填一个 $0$，那么 $+1$ 操作对一个数产生的影响至多是 $+n$．

所以如果我们对后 $p$ 位作个截断，并保证 $2^p>n$，只记录后 $p$ 个二进制位的值，那么 $+1$ 操作至多会进位一次。

如果进位的话，还要求出进位之后得到了末尾有几个零，所以要记录 $p$ 位以上连续了几个 $1$．

但是这样的 $f$ 转移出去如果产生进位，后面有 $j$ 个 $0$，我们不能将这个 $j$ 也记录到 $f$ 的状态里去。所以另设 dp $g_{i,j}$ 表示经过了 $i$ 次操作，末尾 $j$ 个 $0$ 的方案数，并且要求 $j\geq p+1$（是进位进出来的）。

这样就做完了，$f_{i,j,k}$ 表示进行了 $i$ 次操作，$p+1$ 位及以上有连续的 $j$ 个 $1$，对最低的 $p$ 个二进制位作截断得到的数是 $k$，概率为多少，并且要求 $j$ 和 $k$ 不能同时为 $0$，$j$ 和 $k$ 同时为 $0$ 的方案要在 $g$ 中算。

$g_{i,j}$ 表示进行了 $i$ 次操作，最低位有 $j$ 个 $0$ 的概率，要求 $j\geq p+1$．

时间复杂度 $\mathcal{O}(n^3)$．

---

**方法二**：orz 机房大佬的妙法。

这种 $\times 2$ 和 $+1$ 的操作想到的是看二进制位，但是不断 $+1$ 产生进位会破坏掉很多美好的性质。能不能不让 $+1$ 操作产生一些不好的影响？于是想到了从后往前**倒着操作**，例如在一个 $\times 2$ 操作之前的 $+1$，对于后面的影响就变成了 $+2$，进而不会影响后面的最低位的值。

设 $f_{i,j,k}$ 后面 $i$ 个操作，给 $x$ 的影响是 $+j$，一共有 $k$ 次 $\times 2$ （也就是通过 $\times 2$ 获得的末尾的 $0$ 有 $k$ 个）的概率。

$j$ 的大小因为 $\times 2$ 的存在依然可能会很大？由于 $\times 2$ 相当于对最后一位作了一个截断，使得最后一位不会被前面的操作所影响，所以可以设 $f_{i,j,k}$ 表示后面 $i$ 个操作截断掉后面 $k$ 个位给 $x$ 的影响是 $+j$，这样前面接了一个 $+1$ 则转移到 $j+1$；接了一个 $\times 2$，若 $j$ 是偶数则转移到 $j/2$，否则最后这一位 1 再也不会动了，将概率乘上其末尾零的个数贡献给答案。如果操作都处理完了，把最初的那个 $x$ 看做 $x$ 个 $+1$ 直接算贡献即可。

这样已经能做到 $\mathcal{O}(n^3)$ 了，能不能更再给力一点！不难发现这个 $k$ 仅是在统计答案的时候算一个贡献用，由于期望具有线性性，所以**费用提前计算**一下，在 $\times 2$ 的时候直接乘上概率贡献给答案即可。这样就不需要在 dp 中记录 $k$ 了。

时间复杂度 $\mathcal{O}(k^2)$．

另一个理解角度是将末尾的若干个操作看作 $j$ 个 $+1$ 后面跟着 $k$ 个 $\times 2$：

- 如果来了一个 $+1$ 则将 $j\gets j+1$；
- 如果来了一个 $\times 2$：
  - 若 $j$ 为偶数，则可以视作 $j/2$ 个 $+1$，而后面 $\times 2$ 多了一个。
  - 若 $j$ 为奇数，则这个最低的 $1$ 就确定不会改变了，概率乘上 $k$ 贡献给答案。

这个思考方向也很有趣，实际上这两个解释是一个等价的 dp，只不过后一个巧妙地利用了转化意义做到一个简易的理解方式。

---

**方法三**：洛谷题解中的做法，并不知道怎么想到的？？？

此处 $p$ 即为原题面中的 $p\%$．

设 $f_{i,j}$ 表示操作了 $i$ 次之后的 $x$，再加上 $j$ 之后末尾 $0$ 的个数的期望。

先不管 $j$ 的范围，直接把转移写出来：

考虑当且这个 $x$ 上一步是 $\times 2$ 还是 $+1$：

- 上一步是 $\times 2$，那么新的 $x$ 是偶数，如果 $j$ 是奇数的话末尾零个数就是 $0$ 了；如果 $j$ 是偶数，那么可以视作 $\frac{x}{2}+\frac{j}{2}$ 的期望再 $+1$，即为 $f_{i-1,\frac{j}{2}}+1$，再乘上其概率 $p$．
- 上一步是 $+1$，那么 $i$ 步后的 $x$ 再加上 $j$ 的期望，即为 $(i-1)$ 步后的 $x$ 再加上 $j+1$ 的期望（从 $j$那里拿过来一个 $1$ 放到 $x$ 上）即为 $f_{i-1,j+1}$，再乘上概率 $(1-p)$．

为了更进一步观察这个转移的性质，将其写成刷表的形式：

- $f_{i+1,j\times 2}\gets (f_{i,j}+1)\times p$；

- $f_{i+1,j-1}\gets f_{i,j}\times (1-p)$．

最终答案为 $f_{n,0}$．考虑 dp 中一条对答案产生贡献的路径的 $j$，一操作会将 $j$ 乘二，但二操作只会将 $j$ 减一。所以产生贡献的一条路径经过的 $j$ 一定不会超过 $n$，如果走到某个 $f_{i,j}$ 其 $j>n$，那么就算后面都走第二类转移，也不会到达最终状态 $f_{n,0}$．所以第二维仅记 $[0,n]$ 范围内的即可。

时间复杂度 $\mathcal{O}(n^2)$．

（希望大概是这么理解的吧？）

第一种做法是常规思路通过找到性质来优化 dp 的值域范围。

第二种做法是通过转化问题（正着操作转成倒着操作）来优化 dp，还有一步费用提前计算的思想。

套路，都是套路。

[方法一的代码](https://codeforces.com/contest/441/submission/176220245)

[方法二的代码](https://codeforces.com/contest/441/submission/176226295)

[方法三的代码](https://codeforces.com/contest/441/submission/176226626)

---

## 作者：zac2010 (赞：5)

这道题一个朴素的思路就是：维护 $f_{i,j}$ 表示第 $i$ 轮后 $x=j$ 的方案数。时间复杂度 $O(k\times 2^k)$。显然过不了。

我们尝试寻找一个能抛开 $x$ 的值域的做法。不妨重新设 $f_{i,j}$ 表示第 $i$ 轮结束时的 $x$，增加 $j$ 之后期望的末尾 $0$ 个数是多少。发现这可以通过枚举第 $i$ 轮的两种转移方式得到：

1. 第 $i$ 轮的操作是加 $1$

   $$
   f_{i,j}\leftarrow f_{i-1,j+1}
   $$

2. 第 $i$ 轮的操作是乘以 $2$

   $$
   f_{i,2j}\leftarrow f_{i-1,j}
   $$

注意这里和常见的 $\text{DP}$ 略有不同，它这里是通过枚举第 $i$ 轮的操作来把一种状态转移到另一种等价的状态。

最终答案即为 $f_{k,0}$。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); i++)
#define FR(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 210;
int x, k; double p, f[N][N];
int main(){
	scanf("%d%d%lf", &x, &k, &p), p /= 100;
	FL(i, 0, k) f[0][i] = __builtin_ctz(x + i);
	FL(i, 1, k) FL(j, 0, k){
		f[i][j] = f[i - 1][j + 1] * (1 - p);
		if(!(j & 1)) f[i][j] += (f[i - 1][j >> 1] + 1) * p;
	}
	printf("%.12lf", f[k][0]);
	return 0;
}
```



---

## 作者：Trimsteanima (赞：4)

### Description
一共执行$k$次，每次有$p\%$把$x * 2$，有$(100 - p)\%$把$x + 1$。问二进制下$x$末尾期望$0$的个数。

### Solution
设$f[i][j]$为执行第$i$次后$x + j$末尾期望$0$的个数

加一：$f[i + 1][j - 1] = f[i + 1][j - 1] + (100 - p)\% * f[i][j]; $

乘二：$f[i + 1][j * 2] = f[i + 1][j * 2] +  p\% * (f[i][j] + 1);$

```cpp
#include<bits/stdc++.h>
using namespace std;
int x, k;
double p, p1;
double f[300][300];
int main() {
    scanf("%d%d%lf", &x, &k, &p);
    p /= 100, p1 = 1.0 - p;
    for (int i = 0; i <= k; i ++) 
        for (int j = x + i; j % 2 == 0; j /= 2)
            f[0][i] ++;
    for (int i = 0; i < k; i ++)
        for (int j = 0; j <= k; j ++) {
            if (j)
                f[i + 1][j - 1] += p1 * f[i][j]; // + 1
            if (j * 2 <= k)
                f[i + 1][j * 2] += p * (f[i][j] + 1); // * 2 
        }
    printf("%.10f\n", f[k][0]);
    return 0;
}
```


---

## 作者：Krimson (赞：3)

首先%[xtw](https://www.luogu.com.cn/user/44805)，从她那边得到了一个非常巧妙的思路。  
首先不难发现，因为最多进行 $200$ 次操作，所以转成二进制之后前 $8$ 位的数字是不会影响后面的位数的，因为每次 $\times2$ 相当于是整体左移一位，相对距离没有影响，而 $+1$ 能够变化的值不会超过 $256$。  

设 $g_{i,s}$ 表示操作 $i$ 次前八位为 $s$ 的期望是多少，可以很轻松的维护出答案。  

~~然后它就假了~~  

如果这样写，会发现它 Wa 5 ~~原因是前面四个点都很水~~。  

考虑一下，会发现是漏掉了 $000000000.....00000$ 的情况，即这八位之外还有 $0$ 的情况。

很好解决，只需要多开一个数组 $f_{i,s}$ 表示操作 $i$ 次得到 $s$ 的期望后缀 $0$ 长度就好了，前面转移完全一致，只是 $s=0$ 的时候需要特判。  

~~然后它还是假了~~  

再思考一下，会发现还是漏了一种情况， $111111111111.....11111111$，这种情况下再 $+1$ 会出现一大串的后缀 $0$ ，而前面那个dp并不能把这个统计进去。

~~没关系，再开一个数组！~~  
设 $h_{i,j,s}$ 表示操作 $i$ 次去掉前八位之后后缀 $1$ 的个数为 $j$，前八位为 $s$ 的期望是多少。比如 $(1100001000)_2$ 对应的 $j$ 就是 $2$ ，对应的 $s$ 就是 $(00001000)_2$ 。  

会发现这一部分的转移还是和 $f,g$ 的差不多，实际上只需要稍微改一下判断就好了。

实际上这一个部分可以和上面的 $f,g$ 一样开两个数组来实现 $O(k^2)$ 的时空复杂度。~~但是我懒~~  

有人或许会提出疑问：这样子不是还是会有一些情况没法判断吗？比如 $111110\ 11111111$ ，这样再 $+1$ 不就无法统计上前面新链接上的后缀 $1$ 吗？  

这个确实无法统计，但是可以发现，如果要连接上前面的这一串后缀 $1$ ，意味着需要再进行 $255$ 次 $+1$ 操作，因此这种情况并不会被统计，贡献为 $0$，不需要考虑。

~~无论是理解上还是代码长度上均被另一种方法吊打~~  

实现的精细一些是可以做到空间 $O(k)$，时间 $O(k^2)$ 的，本人写的是 $O(k^3)$。  

至于dp具体转移懒得敲公式了，就没在上面说，可以参考下面的代码。


_Code_
------------

```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
#define ui unsigned int
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il ll max(const ll &a,const ll &b){return a>b?a:b;}
il ll min(const ll &a,const ll &b){return a<b?a:b;}
#define double long double
double f[2][256],g[2][256],h[2][235][256],p;
int count(int x){
    int ans=0;
    for(;x&&!(x&1);x>>=1) ++ans;
    return ans;
}
int ccount(int x){
    int ans=0;
    for(;x&1;x>>=1) ++ans;
    return ans;
}
int cnt[256],cntc[256],x,n;
#define B 255
int main(){
    cnt[0]=1,cntc[1]=1;
    for(ri i=2;i<256;i+=2) cnt[i]=cnt[i>>1]+1;
    for(ri i=3;i<256;i+=2) cntc[i]=cntc[i>>1]+1;
    x=read(),n=read(),p=1.0*read()/100;
    f[0][x&B]=count(x),g[0][x&B]=1;
    h[0][ccount(x>>8)][x&B]=1;
    for(ri i=1,o=1;i<=n;++i,o^=1){
        memset(h[o],0,sizeof(h[o]));
        for(ri j=0;j<232;++j){
            for(ri s=0;s<=255;++s){
                if(s&128)  h[o][j+1][(s<<1)&B]+=h[o^1][j][s]*p;
                else h[o][0][(s<<1)&B]+=h[o^1][j][s]*p;
                if(s==255){
                    if(j) h[o][0][0]+=h[o^1][j][s]*(1-p);
                    else h[o][1][0]+=h[o^1][j][s]*(1-p);
                }
                else h[o][j][s+1]+=h[o^1][j][s]*(1-p);
            }
        }
        double res=0;
        for(ri j=0;j<232;++j) res+=h[o^1][j][B]*(8+j);
        f[o][0]=(f[o^1][0]+g[o^1][0]+f[o^1][128]+g[o^1][128])*p+res*(1-p);
        g[o][0]=(g[o^1][0]+g[o^1][128])*p+g[o^1][B]*(1-p);
        for(ri j=1;j<=255;++j){
            g[o][j]=g[o^1][j-1]*(1-p);
            if(!(j&1)) g[o][j]+=(g[o^1][j>>1]+g[o^1][j>>1|128])*p;
            f[o][j]=g[o][j]*cnt[j];
        }
    }
    double ans=0;
    for(ri i=0;i<256;++i) ans+=f[n&1][i];
    printf("%.9Lf",ans);
    return 0;
}
/*
224314221 19 51
1.590075252
*/
```

---

## 作者：lzqy_ (赞：1)

来个逆天做法（

直接存 $x$ 是不允许的。但由于只能通过 $+1$ 进位，所以较靠后的位可以忽略。

具体地，我们只需要保留这样的一段后缀：

- 长度 $>8$。

- 存在至少一个 $1$（保证末尾的 $0$ 都在这段后缀里）。

- 后缀的第一个位置不是 $1$（连续一段 $1$ 可以一次全部进位）。

可以发现这个状态数是收敛的且不会很多（大概是 $10^5$ 级别），于是我们得到了一个 $O(nS)$ 的做法。

但这个 $S$ 还是太大了。既然这个求的不是精确值，那么把概率 $<10^{-15}$ 的状态全部丢掉就可以了。这能让状态数的范围缩小大约 $20$ 倍。

然后就能过了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=250;
const int maxs=100010;
const int MOD=1e7+3;
const int mod=998244353;
const double eps=1e-15;
struct node{
    int a[maxn];
    int hd,tl;
    int val(int sum=0){
        for(int i=hd;i<=tl;i++)
            if((sum=(sum<<1|a[i]))>=mod)
                sum-=mod;
        return sum;
    }
    bool operator ==(node x)const{
        if(tl-hd+1!=x.tl-x.hd+1) return 0;
        for(int i=1;i<=tl-hd+1;i++)
            if(a[hd+i-1]!=x.a[x.hd+i-1])
                return 0;
        return 1;
    }
};
struct edge{
    node v;
    int to;
}e[maxs];
int head[MOD],ecnt;
int Find(node v){
    int val=v.val()%MOD;
    for(int i=head[val];i;i=e[i].to)
        if(e[i].v==v) return i;
    e[++ecnt].v=v,e[ecnt].to=head[val],head[val]=ecnt;
    return ecnt;
}
double f[maxn][maxs],p;
int n,BEG,P;
void renew(node &t){
    for(int i=t.tl,fl=0;i>=t.hd;i--){
        fl|=t.a[i];
        if(t.tl-i>8&&fl&&!t.a[i]){t.hd=i;break;}
    }
}
int main(){
    scanf("%d%d%d",&BEG,&n,&P),p=P/100.0;
    node t; t.hd=1,t.tl=0;
    while(BEG) t.a[++t.tl]=BEG&1,BEG>>=1;
    for(int i=1;i<=8;i++) t.a[++t.tl]=0;
    for(int i=t.hd;i<=t.tl;i++)
        if(i<t.tl+t.hd-i) 
            swap(t.a[i],t.a[t.tl+t.hd-i]);
    renew(t);
    f[0][Find(t)]=1;
    for(int i=0;i<n;i++){
        printf("!!!%d\n",ecnt);
        for(int j=1,k;j<=ecnt;j++){
            if(fabs(f[i][j])<eps) continue;
            ////
            t=e[j].v,t.a[++t.tl]=0;
            renew(t),f[i+1][Find(t)]+=p*f[i][j];
            ////+1
            t=e[j].v;
            for(k=t.tl;t.a[k];k--) t.a[k]=0; t.a[k]=1;
            renew(t),f[i+1][Find(t)]+=f[i][j]*(1-p);
        }
    }
    double ans=0;
    for(int j=1;j<=ecnt;j++){
        int tot=0; t=e[j].v;

        while(t.tl>=t.hd&&!t.a[t.tl]) t.tl--,tot++;
        ans+=f[n][j]*tot;
    }
    // printf("!!!%d\n",ecnt);
    printf("%.10lf\n",ans);

    return 0;
}

```

---

## 作者：Leeb (赞：0)

### 题意简述

给定一个数 $x$，对它进行 $k$ 次操作，每次操作有 $p\%$ 的概率对它乘以 $2$，有 $(1-p\%)$ 的概率对它加上 $1$，求操作完成后该数最终二进制下最大连续 $0$ 个数的期望值。

### 解题思路

首先，加操作使得末尾的 $0$ 变成 $1$，$1$ 变成 $0$，乘 $2$ 操作使得末尾加一个 $0$，但是有个问题，加操作会产生进位。

稍加思考，我们可以发现：当 $n$ 次乘 $2$ 操作后，加 $1$ 操作至少要进行 $2^n$ 次才可能产生影响，进而得出，加 $1$ 操作最多只能产生加 $k$ 的影响。

我们令 $f_{i,j}$ 表示 $x+k$ 的二进制位数，那么我们就可以将加 $1$ 操作取缔，转移为 $f_{i+1,j-1}=f_{i+1,j-1}+(1-p)\times f_{i,j}$，$f_{i+1,\min(j\times 2,k+1)}=f_{i+1,\min(j\times 2,k+1)}+p\times (f_{i,j}+1)$。

### 参考代码

```cpp
// -- More and More vegetales, what should I do?
// -- AFO! AFO YYDS!
// Code Author : Leeb
// #include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 205
#define inf 0x3f3f3f3f
#define endl '\n'
#define elif else if
// #define int long long 
#define ll long long
#define mem(a, x) memset(a, x, sizeof(a))
using namespace std;
int x, k, val; double p, f[N][N];
inline int in() {
    int a = 0; bool f = 0; char ch = getchar();
    while (ch < '0' || ch > '9')
        {if (ch == '-') f = 1; ch = getchar();}
    while (ch >= '0' && ch <= '9')
        a = (a << 1) + (a << 3) + (ch ^ 48), ch = getchar();
    if (f) return ~a + 1;   
    return a;
}
inline void init() {
    x = in(), k = in(), val = in();
    p = val / 100.0;
    for (int i = 0; i <= k; ++i)
        for (int j = x + i; !(j & 1); j >>= 1) f[0][i]++;
}
inline void work() {
    for (int i = 0; i < k; ++i)
        for (int j = 0; j <= k; ++j) {
            f[i + 1][j - 1] += (1 - p) * f[i][j];
            f[i + 1][min(k + 1, j << 1)] += p * (f[i][j] + 1);
        }
    printf("%.7lf\n", f[k][0]);
}
signed main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int t = 1;
    while (t--) {
        init();
        work();
    }
    return 0;
}
```



---

