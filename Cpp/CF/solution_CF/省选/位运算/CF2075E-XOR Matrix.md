# XOR Matrix

## 题目描述

对于两个数组 $a = [a_1, a_2, \dots, a_n]$ 和 $b = [b_1, b_2, \dots, b_m]$，我们定义大小为 $n \times m$ 的异或矩阵 $X$，其中对于每对 $(i,j)$（$1 \le i \le n$；$1 \le j \le m$），有 $X_{i,j} = a_i \oplus b_j$。符号 $\oplus$ 表示按位异或运算。

给定四个整数 $n, m, A, B$。请计算满足以下条件的数组对 $(a, b)$ 的数量：
- 数组 $a$ 包含 $n$ 个整数，每个整数的取值范围是 $0$ 到 $A$；
- 数组 $b$ 包含 $m$ 个整数，每个整数的取值范围是 $0$ 到 $B$；
- 由这些数组生成的异或矩阵中，不同值的数量不超过两个。

## 说明/提示

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6
2 2 2 2
2 3 4 5
5 7 4 3
1337 42 1337 42
4 2 13 37
536870902 536370902 536390912 466128231```

### 输出

```
57
864
50360
439988899
112000
732195491```

# 题解

## 作者：cflsfzh (赞：5)

适合入门者看的题解，**通俗易懂，好想好写**！

看到这道题，一开始并没有什么好的想法，就先推导一下吧。

**请注意**：因为 $0$ 也是一个可取的数字，所以我们应当将值域换一种说法为可取数字数，因此 $A$ 和 $B$ 都应 $+1$，笔者后续的 $A$ 和 $B$ 都默认指的是题面中给出的 $A$ 和 $B$ 都 $+1$，同时为了方便采用题面中的说法，即第一种说法而不是第二种，**值域**。

很容易发现当数组 $a$ 和数组 $b$ 中，分别只有一种数字，或者是 $a$ 只有一种数字，$b$ 有两种不同的数字或是 $a$ 有两种不同的数字，$b$ 只有一种数字的三种情况的答案非常好计算。可推出三种情况的答案分别是：
$$
\left\{
\begin{array}{l}
A\times B\\
A\times B\times \left(B-1\right)\div2\times pw\_m\\
A\times \left(A-1\right)\div2\times B\times pw\_n
\end{array}
\right.
$$
其中我们总是定义：
$$
\left\{
\begin{aligned}
pw\_n&=2^n-2\\
pw\_m&=2^m-2
\end{aligned}
\right.
$$
接着不难发现还有一种情况，就是当 $a$ 和 $b$ 都存在两种不同的数字的情况，这种情况是最难的。首先我们可以设 $a$ 中有 $x$ 和 $y$ 这两个不同的数字，$b$ 中有 $c$ 和 $d$ 这两个不同的数字。我们要使得最多只有两个不同的值，即：
$$
\begin{cases}
x \oplus c&=y \oplus d\\
x \oplus d&=y \oplus c
\end{cases}
$$
这是显然的，因为 $x$ 与 $y$ 不能相等，且 $c$ 和 $d$ 不能相等。然后我们可以化简成这个式子：

$$x \oplus y=c \oplus d$$

这也是显然的。用这个式子能干什么呢？接下来，我们需要两个结论。

**引理 1**

对于一组询问 $\left\{n,m,A,B\right\}$，因为已经拆出上述式子，而 $x,y \in a$ 且 $c,d \in b$，所以可以一起考虑 $A$ 和 $B$。于是对于一个值域 $X$，它可以是 $A$，也可以是 $B$，我们不妨设它是 $A$，并设 $x \oplus y=Y$。

值域 $X$ 下的 $Y$ **一定满足**：$Y$ 的值域在 $\left[2^i,2^{i+1}\right)$ 的范围下时，$Y$ 的可能方案数一定是**相等**的。

**证明**

**（请注意，笔者写的位数是在二进制下成立的。）**

可以抽象理解一下，当 $Y$ 的值域在 $\left[2^i,2^{i+1}\right)$ 的范围下时，显然可以换一个说法，$Y$ 的第 $i$ 位一定是 $1$，之前的（即更高位）一定是 $0$，且之后的（即更低位）可以乱取，即既可以取 $0$，也可以取 $1$，这一定能保证 $Y$ 的值满足在值域 $X$ 内。

于是我们发现，我们可以将情况分成两种。

**（请注意，为了不再写冗长的备注，我们定义：在第 $i$ 位前的总是更高位，在第 $i$ 位后的总是更低位。）**

1. 当值域 $X$ 的第 $i$ 位是 $1$。在这种情况下，无论我们高位怎么取（只要是满足值域 $X$ 的情况下取得的），一定都可以保证 $Y$ 接下的每一位（即更低位）可能是 $1$ 或者是 $0$。如果你没有想明白，你可以发现，当 $X$ 的更低位的某位是 $0$，第 $i$ 为了保证异或值为 $1$，所以 $x$ 和 $y$ 必定在第 $i$ 位上是一个取 $1$，一个取 $0$ 的。考虑最极端的情况，总是取到上限，因为若是没取到上限显然接下的每一位可取 $1$ 也可取 $0$，使得 $Y$ 的值可是 $1$ 也可是 $0$，证明是显然的。所以当取到上限时，$x$ 和 $y$ 中那个第 $i$ 位取了 $1$ 的在当前位一定只能取 $0$，但是在第 $i$ 位上取了 $0$ 的可以在当前位取 $1$，这也保证了 $Y$ 在当前位的值既可以是 $1$，也可以是 $0$。至于第 $i$ 位前的，显然总是保证 $x$ 和 $y$ 的取值总是一致的即可，保证 $Y$ 的值在更高位一定是 $0$ 的。
2. 当值域 $X$ 的第 $i$ 位是 $0$。在这种情况下，我们只需在 $X$ 的高位某处值为 $1$ 时 $x$ 和 $y$ 同步取得 $0$ 即可，这样后续位一定可以取 $1$，也可以取 $0$，简单来说就是后续位的上限全是 $1$ 了，于是问题就转化为了情况 $1$。什么？你问如果高位没有 $1$ 了怎么办，显然结果为 $0$，这是不可能有方案数的，所以还是都是相等的，满足引理。 

于是不难发现对于每一个合法的选择方案前缀（即只选在第 $i$ 位前的合法方案）一定能使得 $Y$ 在值域 $\left[2^i,2^{i+1}\right)$ 下的所有情况的方案都 $+1$，这保证了 $Y$ 的可能法案数一定是相等的。

得到了相等的有什么用？我们发现计算最终的答案就是在计算 $A$ 范围下与 $B$ 范围下对于同一个异或值结果的方案数乘积之和。现在通过引理 $1$，我们只需计算这两个范围下对于异或值为 $2$ 的整次幂时的方案数即可。

**引理 2**

在值域 $X$ 下，对于异或结果为 $2^i$ 的方案数为 $(X>>i+1<<i)+((X>>i \& 1)? \text{X 的后 i-1 位} :0)$。

**证明**

**（请注意：因为为了代码实现，我的 $i$ 是从 $0$ 开始循环的，与题解中的第 $i$ 位相比，在代码中实现以及引理 2 中的公式都是做了 $+1$ 处理的）**

也简单说明一下吧。先不考虑后面那坨，即先默认 $X$ 的第 $i$ 位为 $0$。为了保证异或结果为 $2^i$ 即 $Y$ 的第 $i$ 位为 $1$，我们显然可以回看证明引理 1 时的情况二的讲述，需要高位某处上限为 $1$，但是 $x$ 和 $y$ 同时取了 $0$，这样后续的位就没有上限限制了，即想填 $0$ 就填 $0$，想填 $1$ 就填 $1$，于是显然如果设高位我们上限为 $1$，但是取了 $0$ 的位置为 $j$，这会给我们的方案数造成 $2^{j-1}$ 的贡献，而且只有在第 $i$ 位之前的 $1$ 的位置能进行这样的贡献，于是我们先将 $X$ 右移 $i$ 位，在因为造成的贡献是要 $\div 2$ 的，所以在右移 $1$ 位，最后左移 $i$ 位。于是我们就证完了前面那坨。

至于后半段，也很好理解，就是当 $i$ 位为 $1$ 时，显然为了保证异或值为 $2^i$，$x$ 和 $y$ 中必须一个取 $0$，一个取 $1$，在不进行高位上限为 $1$，我们只取 $0$ 的操作下，我们在第 $i$ 位显然是可以取到 $1$ 的，这是合法的方案，但是后续位并不是想填什么就填什么，所以贡献并不是 $2^{i-1}$，而是后续位的上限，即 $X$ 的后 $i-1$ 位。于是第二部分的公式也证完了，相信大家应该理解了，没理解的可以看看代码，结合着一起理解。

**统计答案**

这是最后一步，也是我们通过两个引理可以显然得到的结果。我们先用引理 2 来将值域 $A$ 和 $B$ 分别代入值域 $X$，算出当异或值为 $2^i$ 时两边各自的方案数，我们设这个结果分别为 $ansa$ 和 $ansb$。于是显然因为在保证有两个不同的数字下，这两个数字时可以乱填在数组 $a$ 和 $b$ 中的，于是我们需要将答案 $\times pw\_n\times pw\_m$，开头计算前三种情况的贡献时里面乘的 ```pw_n``` 和 ```pw_m``` 也是这个原理。最后使用引理 1 得知在 $\left[2^i,2^{i+1}\right)$ 范围内的异或值的方案数都是一样的，所以再 $\times 2^i$ 即可。最终公式：

$$ans+=ansa\times ansb\times pw\_n\times pw\_m\times 2^i$$

最终这道题就终于做完啦！
[AC code。](https://codeforces.com/contest/2075/submission/311214897)

**完结撒花！**

---

## 作者：wanggk (赞：4)

upd on 5.12：修改两处笔误。

[cnblogs](https://www.cnblogs.com/wanggk/articles/-/CF2075E)

### 题意

对于数组 $a$ 和 $b$ ，定义 $n \times m$ 的矩阵 $X_{i,j} = a_i \oplus b_j$。

给你 $n, m, A, B$，求出有多少数组对 $(a, b)$ 满足：

- $a$ 长度为 $n$ 且值域为 $[0,A]$。
- $b$ 长度为 $m$ 且值域为 $[0,B]$。
- 生成的矩阵中，不同的值不超过两个。

$2 \le n, m, A, B \le 2^{29} - 1$。

### 题解

可以发现同一个数，异或上不同的两个数，结果一定不同。因此，数组 $a,b$ 均满足：**不同的值的个数不超过 $2$**。

分类讨论，对 $a,b$ 中不同的值的个数为 $1$ 或 $2$ 分别讨论。

### 情况一：$a,b$ 数组均只有一个值

方案数为 $(A+1) \times (B+1)$。

### 情况二：一个数组有两个不同值，另一个只有一个值

- $a$ 数组只有一个值：$(A+1) \times C_{B+1}^2 \times Calc_m$。
- 反过来，$b$ 数组只有一个值：$(B+1) \times C_{A+1}^2 \times Calc_n$。

其中，$Calc_m$ 表示，用两个不同数（每种数都要用），填满数组的 $m$ 个位置的方案数，即 $Calc_m=2^m-2$。

### 情况三：$a,b$ 数组均有两个不同值

设 $a$ 数组的值为 $x,y(x \not = y)$，$b$ 数组的值为 $p,q(p \not = q)$。

矩阵中所有的可能值为 $x \oplus p,x \oplus q,y \oplus p,y \oplus q$，因为 $x \not = y,p \not =q$，所以只可能 $x \oplus p = y \oplus q$，即 $x \oplus y \oplus p \oplus q =0$。

所以这一种情况转化为，统计以下四元组 $(x,y,p,q)$ 的个数（这一统计的答案记作 $sum$）：

- $x,y \in [0,A]$。
- $p,q \in [0,B]$。
- $x \oplus y \oplus p \oplus q =0$。
- $x \not = y,p \not = q$。

显然，当 $x=y,p=q$ 时一定满足第三个条件，所以我们只需要先忽略最后一个条件，再减去 $x=y,p=q$ 时的 $(A+1) \times (B+1)$ 即可。

忽略最后一个条件后就是一个二进制下的数位 DP 了。设 $f_{k,0/1,0/1,0/1,0/1}$ 表示，已经填完了二进制下前 $k$ 位，当前 $x,y,p,q$ 是否达到 $A$ 或 $B$ 的上限，此时的方案数。

刷表法转移，设当前是 $f_{k,S}$（$S$ 为那四个 $01$ 的状压），用 $2^4$ 枚举 $x,y,p,q$ 的这一位分别填 $0$ 还是 $1$，检查是否合法（不超过这一位上界）并更新新的上界 $to$，转移 $f_{k-1,to} \leftarrow f_{k,S}$。

最终**选数**的方案数为：

$$sum= \frac{(\sum_{S} f_{0,S} )-(A+1) \times (B+1)}{2 \times 2}$$

除以 $4$ 是因为要除掉 $x,y$ 的选择顺序和 $p,q$ 的选择顺序。

算上安排位置的方案，情况三的答案就为 $sum \times Calc_m \times Calc_n$。

最后三种情况相加即可。

### 代码

完整代码见[提交记录](https://codeforces.com/contest/2075/submission/311186453)。

写了一部分注释：

```cpp
void solve()
{
    rd(n,m,A,B);
    ans=(A+1ll)*(B+1ll)%mod;//情况一
    qadd(ans,B*(B+1ll)/2ll%mod*(A+1ll)%mod*calc(m)%mod);//情况二
    qadd(ans,A*(A+1ll)/2ll%mod*(B+1ll)%mod*calc(n)%mod);//情况二

    if(m<2 || n<2 || !A || !B){
        write(ans),End;
        return;
    }
    //下面都是情况三
    memset(f,0,sizeof(f));
    For(i,0,29) up[i][0]=up[i][1]=(A>>i)&1,up[i][2]=up[i][3]=(B>>i)&1;//类似数位 DP，获取上界

    f[30][0]=1ll;
    Forr(k,30,1) For(lim,0,15) if(f[k][lim])
        For(val,0,15) if(!ppc[val]) //val 是枚举 x,y,p,q 这一位填什么，因为要异或和为 0，所以每一位的异或（ppc[val]）都要是 0
        {
            int to=lim;
            bool flag=true;//flag=false 即不合法
            For(i,0,3)
                if(!(lim>>i&1)){ //0 表示对最高位有限制，1 表示对当前位无限制（可能和大多数人习惯反过来？）
                    if((val>>i&1)<up[k-1][i]) to|=(1<<i); //这位严格小于上界，那么此后无限制
                    else if((val>>i&1)>up[k-1][i]){
                        flag=false;
                        break;
                    }
                }
            if(flag) qadd(f[k-1][to],f[k][lim]);
        }
    ll sum=0;
    For(lim,0,15) qadd(sum,f[0][lim]);

    ll red=(A+1ll)*(B+1ll)%mod;
    sum=(sum-red+mod)%mod;
    sum=sum*inv2%mod*inv2%mod;
    
    qadd(ans,sum*calc(n)%mod*calc(m)%mod);
    write(ans),End;
}
```

---

## 作者：未来姚班zyl (赞：1)

![](https://cdn.luogu.com.cn/upload/image_hosting/pbhld75i.png)

一看不同的数要小于等于两个，这一定是一道很清新的小分讨题！耶！

首先一个数组内的数的种类不能超过 $3$ 个，否则另一个数组随便选一个位置就会有三个不同的数，所以只有四种情况，是简单分讨推式子题，符合 Div. 2 E！

设 $a$ 数组的数的种类数是 $cta$，$b$ 数组的数的种类数是 $ctb$。

- $cta=ctb=1$

方案数是 $(A+1)(B+1)$。

- $cta=2,ctb=1$

肯定合法。

$b$ 数组的方案数依旧是 $B+1$。$a$ 数组的方案数，相当于先从 $A+1$ 个数选两个数 $x,y$，然后再从 $n$ 个数中分配 $x,y$，然后减去全 $x$ 和全 $y$ 的，方案数是 $C_n^{2}(2^n-2)$。总的就是两个相乘。

- $cta=1,ctb=2$

一样的。

- $cta=ctb=2$

那么设 $a$ 中的两个数为 $a_1,a_2$，$b$ 中的两个数为 $b_1,b_2$。

那么数组中可能出现这四类数：$a_1\oplus b_1,a_1\oplus b_2,a_2\oplus b_1,a_2\oplus b_2$。

由于 $a_1\oplus b_1\neq a_1\oplus b_2,a_1\oplus b_1\neq a_2\oplus b_1$，矩阵又只能有两类不同的数，那就必须有：

$$a_1\oplus b_2=a_2\oplus b_1$$

移个项就是 $a_1\oplus a_2=b_1\oplus b_2$，设其值为 $x$。

我们发现这个计数非常困难~~非常符合 ECR E~~。

因为我们同时要满足 $a_1,a_2\le A$，$b_1,b_2\le B$。

我们考虑这种类似要求 $x\le K$，其中 $K$ 是常数，这类问题的通用方法：枚举 LCP。

从高到低位确定，我们不妨钦定 $a_1>a_2,b_1>b_2$，维护 $(a_1,b_1,x)$ 的状态。

设 $dp_{i,fa,fb,fx}$ 表示确定了第 $i$ 位，$a_1$ 是否已经小于 $A$，$b_1$ 是否已经小于 $B$，$x$ 是否大于 $0$ 的方案数总和。

对于第四维，我们发现 $x$ 一旦有值，就有 $a_1\neq a_2$，$b_1\neq b_2$。所以对于 $x$ 的最高位 $p$，$a_1,b_1$ 的第 $p$ 位也必须是 $1$，这条件充要。

哇我的代码是砖。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R x<<1|1
#define mid ((l+r)>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,nb
#define OK Ll<=l&&r<=Rr
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
inline void pf(int x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N=5e5+5,M=1e6+5,inf=(1LL<<30)-1,mod=998244353;
const ll llf=1e18;
inline void add(int &a,int b){if(b<0)b+=mod;((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){add(b,mod);return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,ll b){if(!b)return 1;int c=qp(a,b>>1LL);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int n,m,A,B,iv2=INV(2),dp[35][2][2][2];
inline bool che(int s,int p){return (s>>p)&1;}
inline void Main(){
	n=read(),m=read(),A=read(),B=read();
	//Case 1: cta=ctb=1
	int ans=mul(A+1,B+1);
	//Case 2: max(cta,ctb)=2,min(cta,ctb)=1
	int KA=mul(mul(A,mul(A+1,iv2)),Red(qp(2,n),2)),KB=mul(mul(B,mul(B+1,iv2)),Red(qp(2,m),2));
	add(ans,Add(mul(KA,B+1),mul(KB,A+1)));
	//Case 3:cta=ctb=2,Xa^Ya=Xb^Yb
	memset(dp,0,sizeof(dp));
	dp[29][0][0][0]=1;
	per(i,28,0){
		int wA=che(A,i),wB=che(B,i),w;
		rep(fa,0,1)rep(fb,0,1)rep(fA,0,1)if(w=dp[i+1][fa][fb][fA]){
			if(fa&&fb&&fA){
				add(dp[i][1][1][1],mul(w,8));
				continue;
			}
			if(fA){
				Mul(w,2);
				if(!fa&&!fb){
					add(dp[i][0][0][1],w);
					if(wA)add(dp[i][1][0][1],w);
					if(wB)add(dp[i][0][1][1],w);
					if(wA&wB)add(dp[i][1][1][1],w);
					continue;
				}
				Mul(w,2);
				if(!fa){
					add(dp[i][0][1][1],w);
					if(wA)add(dp[i][1][1][1],w);
					continue;
				}
				add(dp[i][1][0][1],w);
				if(wB)add(dp[i][1][1][1],w);
				continue;
			}
			if(fa&&fb){
				add(dp[i][1][1][1],w);
				add(dp[i][1][1][0],mul(w,4));
				continue;
			}
			if(!fa&&!fb){
				add(dp[i][0][0][0],w);
				if(wA)add(dp[i][1][0][0],w);
				if(wB)add(dp[i][0][1][0],w);
				if(wA&&wB)add(dp[i][0][0][1],w),add(dp[i][1][1][0],w);
				continue;
			}
			if(!fa){
				add(dp[i][0][1][0],mul(w,2));
				if(wA)add(dp[i][1][1][0],mul(w,2)),add(dp[i][0][1][1],w);
				continue;
			}
			add(dp[i][1][0][0],mul(w,2));
			if(wB)add(dp[i][1][1][0],mul(w,2)),add(dp[i][1][0][1],w);
		}
	}
	int W=0;
	rep(i,0,1)rep(j,0,1)add(W,dp[0][i][j][1]);
	add(ans,mul(W,mul(Red(qp(2,n),2),Red(qp(2,m),2))));
	cout <<ans<<'\n';
}
signed main(){
	int T=read();
	while(T--)Main();
	return 0;
}
```

---

## 作者：SUNCHAOYI (赞：1)

注意到一个数组内的数的种类不可能大于 $2$，于是大力分类讨论。

- $a,b$ 数组内的数均只有一种，此时生成的异或矩阵只有一种取值，满足题目条件，方案数为 $(A + 1)(B + 1)$。

- $a$ 数组内的数有两种，$b$ 中只有一种。此时生成的异或矩阵有两种取值，仍然满足题目条件。可以给 $a$ 数组内的数任意选择两种，并枚举其中一种数的个数。用二项式定理进一步化简，最终可得到方案数为

$$
(B + 1) \times \binom {A + 1}{2} \sum \limits_{i = 1}^{n - 1} \binom {n}{i} \\
=\dfrac{1}{2}{(B + 1)(A + 1)A}\sum \limits_{i = 1}^{n - 1} \binom {n}{i} \\
=\dfrac{1}{2}{(B + 1)(A + 1)A}(2^n - 2)
$$

- $b$ 数组内的数有两种，$a$ 中只有一种。同理可得方案数为

$$
\dfrac{1}{2}{(A + 1)(B + 1)B}(2^m - 2)
$$

- $a,b$ 数组内的数均有两种。设 $a$ 中存在 $x_1,x_2\ (x_1 \neq x_2)$，$b$ 中存在 $y_1,y_2\ (y_1 \neq y_2)$，则只有 $x_1 \oplus y_2 = x_2 \oplus y_1$ 时满足题意。交换一下可得 $x_1 \oplus x_2 = y_1 \oplus y_2$。由于每一位相互独立，所以设 $dp_{i,0/1,0/1,0/1,0/1}$ 表示考虑到第 $i$ 位时，$x_1,x_2,y_1,y_2$ 是否已经达到上界时的方案数，直接大力数位 dp 即可。需要注意的时，最后还需要枚举某一个数的个数，也就是乘上

$$
\sum \limits_{i = 1}^{n - 1} \binom {n}{i} \times \sum \limits_{i = 1}^{m - 1} \binom {m}{i} \\
= (2^n - 2)(2^m - 2)
$$

最终代码如下：

```cpp
#include <bits/stdc++.h>
#define init(x) memset (x,-1,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define pii pair <int,int>
using namespace std;
const int MAX = 1e5 + 5;
const int MOD = 998244353;
inline int read ();
int t,a[35],b[35];ll n,m,A,B,ans,inv_2 = 499122177,dp[35][2][2][2][2]; 
ll qpow (ll x,ll y)
{
	ll res = 1;
	while (y)
	{
		if (y & 1) res = res * x % MOD;
		x = x * x % MOD;
		y >>= 1;
	}
	return res;
}
int dfs (int x,bool lead,bool p1,bool p2,bool p3,bool p4)
{
	if (x >= 30) return !lead;//不能均为 0 
	if (~dp[x][p1][p2][p3][p4]) return dp[x][p1][p2][p3][p4];
	ll sum = 0;
	for (int d1 = 0;d1 <= (p1 ? a[x] : 1);++d1)
		for (int d2 = 0;d2 <= (p2 ? d1 : 1);++d2)
			for (int d3 = 0;d3 <= (p3 ? b[x] : 1);++d3)
				for (int d4 = 0;d4 <= (p4 ? d3 : 1);++d4)
					if ((d1 ^ d2) == (d3 ^ d4))
						sum += dfs (x + 1,lead && !(d1 ^ d2),p1 && (d1 == a[x]),p2 && (d2 == d1),p3 && (d3 == b[x]),p4 && (d4 == d3)),sum %= MOD;
	return dp[x][p1][p2][p3][p4] = sum;
}
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	t = read ();
	while (t--)
	{
		n = read ();m = read ();A = read ();B = read ();
		ans = (A + 1) * (B + 1) % MOD;
		ans += (A + 1) * (B + 1) % MOD * B % MOD * inv_2 % MOD * (qpow (2,m) - 2 + MOD) % MOD;ans %= MOD;
		ans += (B + 1) * (A + 1) % MOD * A % MOD * inv_2 % MOD * (qpow (2,n) - 2 + MOD);ans %= MOD;
		for (int i = 0;i < 30;++i,A >>= 1) a[29 - i] = A & 1;
		for (int i = 0;i < 30;++i,B >>= 1) b[29 - i] = B & 1;
		init (dp);
		ans += dfs (0,1,1,1,1,1) * (qpow (2,m) - 2 + MOD) % MOD * (qpow (2,n) - 2 + MOD) % MOD;ans %= MOD;
		printf ("%lld\n",ans);
	}
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

## 作者：aeiouaoeiu (赞：0)

看完题目可以认识到，$a,b$ 中数的种类数都分别不超过 $2$。如果超过 $2$，那么选三种数和另一个数组中的某一个数异或起来，显然会产生三种不同的值，不符合题意。

设 $a$ 中两种数为 $a_1,a_2$，$b$ 中两种数为 $b_1,b_2$，若 $a_1\neq a_2,b_1\neq b_2$，那么 $a_1\oplus b_1\neq a_1\oplus b_2$，所以需要满足 $a_1\oplus b_1=a_2\oplus b_2$。显然 $a_1=a_2$ 且 $b_1=b_2$ 时上式仍然成立，而若只有一对相等，上式一定不成立。

于是需要求出满足 $0\le a_1,a_2\le A,0\le b_1,b_2\le B,a_1\oplus b_1=a_2\oplus b_2$ 的四元组 $(a_1,a_2,b_1,b_2)$ 的个数。异或对于每一位独立，不难想到可以按位考虑，进行数位 dp。

设 $f_{i,0/1,0/1,0/1,0/1}$ 表示考虑到从小到大第 $i$ 位，$a_1,a_2,b_1,b_2$ 分别不贴/贴上界，此时合法的 $(a_1,a_2,b_1,b_2)$ 个数。枚举这四个 $0/1$ 维为 $(ta_1,ta_2,tb_1,tb_2)$。

现在考虑 $a_1$ 如何转移。若 $ta_1=0$，则 $a_1$ 在这一位取值随意，由 $ta_1'=0$ 转移过来；若 $ta_1=1$，需要进一步分类讨论，设 $A$ 在这一位的值为 $ca$，枚举 $a_1$ 在这一位的值为 $c$。

- $c=1,ca=1$：此时 $a_1$ 贴着上界，前一位不能随便取，由 $ta_1'=1$ 转移过来。
- $c=0,ca=1$：此时 $a_1$ 不贴上界，前一位随便取，由 $ta_1'=0$ 转移过来。
- $c=1,ca=0$：超出上界，不存在该情况。
- $c=0,ca=0$：此时 $a_1$ 贴着上界，前一位不能随便取，由 $ta_1'=1$ 转移过来。

归纳一下可以得到一个相对简洁的形式：$a_1,ta_1,ca$ 确定，由 $ta_1'=ta_1\&(a_1\oplus ca\oplus 1)$ 转移过来。其他三个形式一致，于是可以进行转移。

最终得到合法四元组个数 $f_{30,1,1,1,1}$。发现 $a_1=a_2=b_1=b_2$ 时计数会算重，于是先剔掉这一部分。$(a_1,a_2),(b_1,b_2)$ 组内交换的情况也会被算重，也要剔掉，也就是除以 $4$。

令 $d=\frac{f_{30,1,1,1,1}-(A+1)(B+1)}{4}$。只是用这些情况计算不会算重。那么对于 $a$ 的每一位，都只有填上 $a_1,a_2$ 两种可能，去掉全填 $a_1,a_2$ 的方案，$b$ 同理，方案数为 $d(2^n-2)(2^m-2)$。

如果 $a,b$ 中有任意一个只填一种数，而另一个种类不超过 $2$，这个方案显然一定合法。需要分成：都只由一种数组成，一个填一种另一个填两种，这两种情况讨论。都只有一种数组成时，方案数显然是 $(A+1)(B+1)$；一个填一种另一个填两种时，假设 $a$ 填了两种，那么去掉全填其中一种的方案，有 $\frac{A(A-1)}{2}B(2^n-2)$，再 $b$ 同理。最终得到式子 $(A+1)(B+1)+\frac{A(A-1)}{2}B(2^n-2)+\frac{B(B-1)}{2}A(2^m-2)$。

两个部分加一起即可。单组数据时间复杂度 $\mathcal{O}(\log \max(A,B)2^V)$，其中 $V=8$。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define mp make_pair 
#define pob pop_back
using namespace std;
typedef long long ll;
const ll maxn=207,ee=1e18,p=998244353;
ll n,m,A,B,f[2][2][2][2],g[2][2][2][2],ans;
ll qpow(ll a,ll b){ll E=1; for(;b;b>>=1,a=a*a%p)if(b&1) E=E*a%p; return E;}
void ups(ll &a,ll b){a=(a+b>=p)?a+b-p:a+b;}
int main(void){
    //freopen("data.in","r",stdin); 
    //freopen("data.out","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0);
    ll T=1; cin>>T;
    for(;T--;){
    	cin>>n>>m>>A>>B; memset(f,0,sizeof(f)),memset(g,0,sizeof(g));
    	for(ll ta1=0;ta1<=1;ta1++)for(ll ta2=0;ta2<=1;ta2++){
    		for(ll tb1=0;tb1<=1;tb1++)for(ll tb2=0;tb2<=1;tb2++) f[ta1][ta2][tb1][tb2]=1;
    	}
    	for(ll i=0,ca,cb,sa1,sa2,sb1,sb2;i<=30;i++){
    		ca=A>>i&1,cb=B>>i&1;
    		memcpy(g,f,sizeof(f)),memset(f,0,sizeof(f));
    		for(ll ta1=0;ta1<=1;ta1++)for(ll ta2=0;ta2<=1;ta2++)for(ll a1=0;a1<=1;a1++)for(ll a2=0;a2<=1;a2++){
    			if((ta1==1&&a1>ca)||(ta2==1&&a2>ca)) continue;
    			for(ll tb1=0;tb1<=1;tb1++)for(ll tb2=0;tb2<=1;tb2++)for(ll b1=0;b1<=1;b1++)for(ll b2=0;b2<=1;b2++){
    				if((tb1==1&&b1>cb)||(tb2==1&&b2>cb)) continue;
    				if((a1^a2)!=(b1^b2)) continue;
    				sa1=ta1&(a1^ca^1),sa2=ta2&(a2^ca^1),sb1=tb1&(b1^cb^1),sb2=tb2&(b2^cb^1);
    				ups(f[ta1][ta2][tb1][tb2],g[sa1][sa2][sb1][sb2]);
    			}
    		}
    	}
    	ans=(f[1][1][1][1]-(A+1)*(B+1)%p+p)%p;
    	ans=ans*qpow(4,p-2)%p,A++,B++;
        cout<<(A*B%p+B*(B-1)/2%p*A%p*(qpow(2,m)-2+p)%p+A*(A-1)/2%p*B%p*(qpow(2,n)-2+p)%p+ans*(qpow(2,n)-2+p)%p*(qpow(2,m)-2+p)%p)%p<<"\n";
    }
    return 0;
}
```

---

