# [ARC132F] Takahashi The Strongest

## 题目描述

高桥君、青木君和すぬけ君三个人进行 $k$ 次猜拳游戏。

由 `P`、`R`、`S` 组成的长度为 $k$ 的字符串称为**作战方案**。游戏流程如下：

- 每位参与者各自选择一个作战方案。
- 进行 $k$ 次猜拳。在第 $i$ 次时，每位参与者根据所选作战方案的第 $i$ 个字符出拳。具体来说，`P` 表示出“布”，`R` 表示出“石头”，`S` 表示出“剪刀”。

青木君会从 $n$ 个作战方案 $a_1,\dots,a_n$ 中等概率随机选择一个。すぬけ君会从 $m$ 个作战方案 $b_1,\dots,b_m$ 中等概率随机选择一个。两人的选择是独立的。

如果在 $k$ 次猜拳中，有至少一次只有高桥君获胜，则高桥君会感到高兴。对于所有可能的 $3^k$ 种作战方案，求出当高桥君选择该作战方案时他感到高兴的概率，并输出该概率乘以 $nm$ 后的整数值（可以证明该值一定为整数）。

## 说明/提示

### 注意

当三个人猜拳时，只有高桥君获胜的情况有以下三种：

- 高桥君出“布”，青木君和すぬけ君都出“石头”；
- 高桥君出“石头”，青木君和すぬけ君都出“剪刀”；
- 高桥君出“剪刀”，青木君和すぬけ君都出“布”。

### 约束条件

- $1 \leq k \leq 12$
- $1 \leq n, m \leq 3^k$
- $a_i, b_i$ 是由 `P`、`R`、`S` 组成的长度为 $k$ 的字符串
- $a_1,\dots,a_n$ 互不相同
- $b_1,\dots,b_m$ 互不相同

### 样例解释 1

青木君的作战方案为 `RS`。すぬけ君选择作战方案 `RP` 时，满足条件的高桥君作战方案为 `PP`、`PR`、`PS`。すぬけ君选择作战方案 `RR` 时，满足条件的高桥君作战方案为 `PP`、`PR`、`PS`。すぬけ君选择作战方案 `RS` 时，满足条件的高桥君作战方案为 `PP`、`PR`、`PS`、`RR`、`SR`。综上，当高桥君的作战方案为 `PP`、`PR`、`PS`、`RP`、`RR`、`RS`、`SP`、`SR`、`SS` 时，对应的概率分别为 $1,1,1,0,\frac{1}{3},0,0,\frac{1}{3},0$。输出时请将这些概率乘以 $3$ 后的值输出。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 1 3
RS
RP
RR
RS```

### 输出

```
3
3
3
0
1
0
0
1
0```

## 样例 #2

### 输入

```
3 5 4
RRP
SSS
RSR
PPP
RSS
PPS
SRP
SSP
RRS```

### 输出

```
4
7
7
6
9
10
4
7
8
4
8
7
4
8
8
3
7
7
3
7
6
4
8
8
1
5
5```

# 题解

## 作者：EuphoricStar (赞：4)

没见过这种在新运算下做卷积的题，感觉挺新奇的。

考虑 Takahashi 成为绝对赢家的必要条件，发现前提是 Aoki 和 Snuke 出的要相同。不妨将每种策略映射到一个四进制数（$P \to 1, R \to 2, S \to 3$），定义运算 $x \otimes y = \begin{cases} x & x = y \\ 0 & x \ne y \end{cases}$（这里是 $x,y \le 3$ 的情况，对于一个四进制数就逐位做），设 $a_i, b_i$ 分别为 Aoki 和 Snuke 每种策略的数量，那么实际上我们希望先求：

$$c_i = \sum\limits_{j \otimes k = i} a_j b_k$$

这个东西是可以 FWT 算的。先算 $A_i = \sum\limits_{j \otimes i = i} a_j, B_i = \sum\limits_{j \otimes i = i} b_j$，那么 $C_i = A_i B_i$，最后 $C \to c$ IFWT 回去。定义一种新的集合从属关系 $0 \subset 1, 0 \subset 2, 0 \subset 3$ 且 $1,2,3$ 互不相交，那么 FWT 的过程相当于做一个超集和。

那么得到了 $c_i$ 之后，我们还希望求 $d_i = \sum\limits_{j \otimes i \ne 0} c_j$。正着算不好算，考虑变成求 $d_i = \sum\limits_{j \otimes i = 0} c_j$。考虑设计一个 dp，$f_{k,i}$ 表示考虑了前 $k$ 位，$i$ 表示前 $k$ 位是已经确定的策略，后面的位和 $d_i = \sum\limits_{j \otimes i = 0} c_j$ 中的 $j$ 后面的位相同，这样的方案数。转移枚举在当前位填 $1/2/3$，并且不能与 $j$ 在这个位相同。

这样就做完了，时间复杂度 $O(k 4^k)$。

[code](https://atcoder.jp/contests/arc132/submissions/41660412)

---

## 作者：Argon_Cube (赞：2)

没有 [P12482 [集训队互测 2024] 欧伊昔](https://www.luogu.com.cn/problem/P12482) 魔怔，我不认可。

本题是上面那个题的严格子集。

----

一眼 FWT，先容斥成一次都赢不了的方案数。接下来我们考虑 $a_ib_j$ 对 $c_k$ 的贡献系数。

先拆位，此时 $i,j,k\in [0,3)$，贡献系数是 $1-[i\equiv j\equiv k+1\pmod 3]$。于是 $C_{(k+1)\bmod 3}=(A_0+A_1+A_2)(B_0+B_1+B_2)-A_{k}B_{k}$。

于是用 P12482 的做法直接在 FWT 中维护 $(A_0,A_1,A_2)\to(A_0,A_1,A_2,A_0+A_1+A_2)$ 即可，复杂度 $\Theta(4^n)$。

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <array>

#define rgall(arr)          (arr).begin(),(arr).end()
#define rgo1(arr,cnt)       (arr).begin()+1,(arr).begin()+1+(cnt)
#define rgcnt(arr,cnt)      (arr).begin(),(arr).begin()+(cnt)
#define rgany(arr,rgl,rgr)  (arr).begin()+(rgl),(arr).begin()+(rgr)
#define fori(i,a,b)         for(int i=(a);i<=(b);i++)
#define ford(i,a,b)         for(int i=(a);i>=(b);i--)
#define fori0(i,a,b)        for(int i=(a);i<(b);i++)
#define ford0(i,a,b)        for(int i=(a);i>(b);i--)
#define fr first
#define sc second

using namespace std;

array<long long,1<<24> va,vb;

void FWT(int l,int r,decltype(va)& va)
{
    if(r-l==1)
        return;
    int mid=r-l>>2;
    fori(i,0,2)
        FWT(l+mid*i,l+mid*(i+1),va);
    fori0(i,0,mid)
        fori(j,0,2)
            va[l+i+mid*3]+=va[l+i+mid*j];
}
void IFWT(int l,int r,decltype(va)& va)
{
    if(r-l==1)
        return;
    int mid=r-l>>2;
    fori(i,0,3)
        IFWT(l+mid*i,l+mid*(i+1),va);
    fori0(i,0,mid)
    {
        if(!~va[l+i])
            continue;
        auto& b=va[l+i+mid*3];
        fori(j,0,2)
        {
            auto &a=va[l+i+mid*j];
            a=b-a;
        }
        b=-1;
    }
}

int main(int argc,char* argv[],char* envp[])
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m=1,ca,cb;
    cin>>n>>ca>>cb;
    fori(i,1,n)
        m*=3;
    fori(k,0,1)
        fori(i,1,k?cb:ca)
        {
            int a=0;
            fori(j,1,n)
            {
                char b;
                cin>>b;
                a=a<<2|(b=='S')+(b=='P')*2;
            }
            ++(k?vb:va)[a];
        }
    FWT(0,1<<n+n,va),FWT(0,1<<n+n,vb);
    fori0(i,0,1<<n+n)
        va[i]*=vb[i];
    IFWT(0,1<<n+n,va);
    fori0(i,0,1<<n+n)
        if(va[i]!=-1)
            cout<<1ll*ca*cb-va[i]<<'\n';
    return 0;
}
```

---

## 作者：xujindong_ (赞：1)

首先转为计数不赢的方案数。此时每一维独立，这个问题形如位运算卷积，在每一位上前两个人的 $i,j$ 会贡献给第三个人的 $k$。

此时有一个问题，一个 $(i,j)$ 会贡献给多个 $k$，无法表示成运算。具体地，当前两个人出的不同，第三个人任意出都输，否则第三个人有一种出法赢。我们考虑先中转一下，先将前两个人合并得到第三个人的策略。设三种出法为 $1\sim 3$。第三个人有四种策略，可以表示为运算 $x\circ y=\begin{cases}0&\ x\ne y\\x&\ x=y\end{cases}$。按这个运算进行四进制 FWT，位矩阵是 $\begin{bmatrix}1&1&1&1\\0&1&0&0\\0&0&1&0\\0&0&0&1\end{bmatrix}$。最后再把策略加到具体的出法上，也就是进行位矩阵为 $\begin{bmatrix}0&0&0&0\\1&1&0&1\\1&1&1&0\\1&0&1&1\end{bmatrix}$ 的变换。复杂度 $O(k4^k)$。

进一步地，可以将 IFWT 和最后的变换合成一步，位矩阵变成 $\begin{bmatrix}0&0&0&0\\1&0&-1&0\\1&0&0&-1\\1&-1&0&0\end{bmatrix}$。此时我们发现有很好的性质：$f,g,h$ 只在每一位都为 $1,2,3$ 处有值。因此 FWT 时可以对未经变换的部分 $O(3^i)$ 枚举。复杂度 $O(\sum_{i=0}^{k-1}4^i3^{k-i})=O(4^k)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int l,n,m,p3[17],p[17][531441];
long long f[16777216],g[16777216];
string s;
int id(string s){
  int v=0;
  for(int i=0;i<l;i++)v=4*v+(s[i]=='P'?1:s[i]=='R'?2:3);
  return v;
}
int main(){
  ios::sync_with_stdio(0),cin.tie(0),p3[0]=1,cin>>l>>n>>m;
  for(int i=1;i<=l;i++)p3[i]=3ll*p3[i-1];
  for(int i=0;i<=l;i++)for(int j=0;j<p3[i];j++)for(int k=0,t=j;k<i;k++)p[i][j]|=(t%3+1)<<2*k,t/=3;
  for(int i=1;i<=n;i++)cin>>s,f[id(s)]++;
  for(int i=1;i<=m;i++)cin>>s,g[id(s)]++;
  for(int k=0;k<l;k++){
    for(int i=0;i<p3[l-k-1];i++){
      for(int j=0;j<1<<2*k;j++){
        int a=p[l-k-1][i]<<2*(k+1)|j,b=a|1<<2*k,c=a|2<<2*k,d=a|3<<2*k;
        f[a]+=f[b]+f[c]+f[d],g[a]+=g[b]+g[c]+g[d];
      }
    }
  }
  for(int i=0;i<1<<2*l;i++)f[i]*=g[i];
  for(int k=0;k<l;k++){
    for(int i=0;i<1<<2*(l-k-1);i++){
      for(int j=0;j<p3[k];j++){
        int a=i<<2*(k+1)|p[k][j],b=a|1<<2*k,c=a|2<<2*k,d=a|3<<2*k;
        long long w=f[a],x=f[b],y=f[c],z=f[d];
        f[a]=0,f[b]=w-y,f[c]=w-z,f[d]=w-x;
      }
    }
  }
  for(int i=0;i<p3[l];i++)cout<<1ll*n*m-f[p[l][i]]<<'\n';
  return 0;
}
```

更好的做法是直接不中转，写出 $f,g$ 对 $h$ 的贡献，对 $h$ 的 $0,1,2$ 的贡献系数是 $\begin{bmatrix}1&1&1\\1&0&1\\1&1&1\end{bmatrix},\begin{bmatrix}1&1&1\\1&1&1\\1&1&0\end{bmatrix},\begin{bmatrix}0&1&1\\1&1&1\\1&1&1\end{bmatrix}$。考虑直接分治乘法。设 $f$ 当前位为 $0,1,2$ 的子数组分别为 $f_0,f_1,f_2$，$g,h$ 同理，令 $t=(f_0+f_1+f_2)(g_0+g_1+g_2)$，则 $h_0=t-f_1g_1,h_1=t-f_2g_2,h_2=t-f_0g_0$，从而递归到 $4$ 个规模为 $\frac 13$ 的子问题，时间复杂度 $O(4^k)$。对于递归的同一层，$t$ 可以共用一个临时数组，空间复杂度 $O(3^k)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,l,p3[17];
long long f[531441],g[531441],h[531441];
string s;
int id(string s){
  int v=0;
  for(int i=0;i<l;i++)v=3*v+(s[i]=='P'?0:s[i]=='R'?1:2);
  return v;
}
void solve(int n,long long f[],long long g[],long long h[]){
  if(!n){
    h[0]=f[0]*g[0];
    return;
  }
  int l=p3[n-1];
  long long*temp=new long long[l];
  solve(n-1,f,g,h+2*l),solve(n-1,f+l,g+l,h),solve(n-1,f+2*l,g+2*l,h+l);
  for(int i=0;i<l;i++)f[i]+=f[l+i]+f[2*l+i],g[i]+=g[l+i]+g[2*l+i];
  solve(n-1,f,g,temp);
  for(int i=0;i<l;i++)h[i]=temp[i]-h[i],h[l+i]=temp[i]-h[l+i],h[2*l+i]=temp[i]-h[2*l+i],f[i]-=f[l+i]+f[2*l+i],g[i]-=g[l+i]+g[2*l+i];
  delete[]temp;
}
int main(){
  ios::sync_with_stdio(0),cin.tie(0),p3[0]=1,cin>>l>>n>>m;
  for(int i=1;i<=l;i++)p3[i]=3*p3[i-1];
  for(int i=1;i<=n;i++)cin>>s,f[id(s)]++;
  for(int i=1;i<=m;i++)cin>>s,g[id(s)]++;
  solve(l,f,g,h);
  for(int i=0;i<p3[l];i++)cout<<1ll*n*m-h[i]<<'\n';
  return 0;
}
```

---

## 作者：eastcloud (赞：1)

题目看上去就很能容斥，先固定一组小 C 的策略算方案，设小 C 的策略为 $T$ 的答案为 $h(T)$，设 $f(S)$ 和 $g(S)$ 分别表示小 A 的策略和小 B 的策略包含集合 $S$ 的方案数，这里的包含指的是恰好在对应位置选了对应数，我们就能得到 $h(T)=\sum_{S \subset T,s\neq \emptyset} (-1)^{|S|-1}f(S)g(S)$。

先考虑怎么算 $f(S)$ 和 $g(S)$，你会发现这个东西本质上就是一个高维前缀和，把连续两个二进制位压缩表示一个状态，分别是剪刀石头布或者通配符，跟普通的高维前缀和一样做就行。

算出来 $f$ 和 $g$ 之后对应位置作乘法，倒着变换回去也是类似的，记得加上容斥系数。


```cpp

#include<bits/stdc++.h>

#define ll long long
#define pi pair<ll,ll>
#define vi vector<ll>
#define cpy(x,y,s) memcpy(x,y,sizeof(x[0])*(s))
#define mset(x,v,s) memset(x,v,sizeof(x[0])*(s))
#define all(x) begin(x),end(x)
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define ary array

#define N 600005
#define K 14

using namespace std;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0' || ch>'9')f=(ch=='-'?-1:f),ch=getchar();
    while(ch>='0' && ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*f;
}
void write(ll x){
    if(x<0)x=-x,putchar('-');
    if(x/10)write(x/10);
    putchar(x%10+'0');
}

ll n,k,m;

char s[N][K],t[N][K];
ll f[(1<<24)],g[(1<<24)];
ll id(char s){
    return (s=='P'?1:(s=='R'?2:3));
}

ll a[K];

int main(){
    #ifdef EAST_CLOUD
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    #endif

    k=read(),n=read(),m=read();
    for(ll i=1;i<=n;i++)scanf("%s",s[i]+1);
    for(ll i=1;i<=m;i++)scanf("%s",t[i]+1);
    for(ll i=1;i<=n;i++){
        ll w=0;
        for(ll j=1;j<=k;j++){
            ll num=id(s[i][j]);
            w+=(1<<((j-1)*2))*num;
        }
        f[w]++;
    }
    for(ll i=1;i<=m;i++){
        ll w2=0;
        for(ll j=1;j<=k;j++){
            ll num2=id(t[i][j]);
            w2+=(1<<((j-1)*2))*num2;
        }
        g[w2]++;
    }
    for(ll i=1;i<=k;i++){
        ll lim=(1<<(2*k));
        for(ll j=0;j<lim;j++){
            ll w=(j>>(2*(i-1)));w=(w&3);
            if(!w)continue;
            ll A=(1<<(2*(i-1))),B=(1<<(2*(i-1)+1));
            ll goal=j;goal=((goal&A)?(goal^A):goal);goal=((goal&B)?(goal^B):goal);
            f[goal]+=f[j];g[goal]+=g[j];
        }
    }
    for(ll j=0;j<(1<<(2*k));j++){
        f[j]=f[j]*g[j];
        ll cnt=0;
        for(ll l=1;l<=k;l++){
            if((j&(1<<(2*(l-1)))) || (j&(1<<(2*(l-1)+1))))cnt++;
        }
        f[j]=((cnt&1)?f[j]:-f[j]);
    }
    f[0]=0;
    for(ll i=1;i<=k;i++){
        ll lim=(1<<(2*k));
        for(ll j=0;j<lim;j++){
            ll w=(j>>(2*(i-1)));w=(w&3);
            if(!w)continue;
            ll A=(1<<(2*(i-1))),B=(1<<(2*(i-1)+1));
            ll goal=j;goal=((goal&A)?(goal^A):goal);goal=((goal&B)?(goal^B):goal);
            f[j]+=f[goal];
        }
    }
    for(ll i=0;i<(1<<(2*k));i++){
        ll flag=0,w=0;
        for(ll j=1;j<=k;j++){
            if(!(i&(1<<(2*(j-1)))) && !(i&(1<<(2*(j-1)+1)))){flag=1;break;}
            ll it=((i>>(2*(j-1)))&3)+1;it=(it==4?1:it);
            w|=it*(1<<(2*(k-j)));
        }
        if(flag)continue;
        write(f[w]);putchar('\n');
    }
    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc132_f)

**题目大意**

> 给定三个人玩石头剪刀布，进行 $k$ 轮，已知前两个人会选择的策略集合。
>
> 对于第三个人的每种策略，求出前两个人有多少种选择策略的方法使得第三个人至少获胜一轮。
>
> 数据范围：$k\le 12$。

**思路分析**

考虑枚举第 $i$ 轮并钦定第三个人在这一轮获胜。

我们就要计算有多少第一个人和第二个人的策略对，使得他们在第 $i$ 位相等。

回到原问题，进行容斥，钦定第三个人获胜了其中 $x$ 轮，容斥系数 $(-1)^{x-1}$。

我们就要对于 $3^x$ 个可能的决策 $s$，求第一个人和第二个人在这 $x$ 位恰好是 $s$ 的数量，可以四进制 FWT，某一位 $=3$ 说明不钦定这一位取值。

然后做一个类似的过程，把每一位 $=3$ 的值加给这一位 $=0/1/2$ 的值。

时间复杂度 $\mathcal O(k4^k)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,N,Z,X,Y;
ll f[1<<24],g[1<<24];
int read() {
	string o; cin>>o;
	int s=0;
	for(int i=0;i<n;++i) s=s<<2|(o[i]=='P'?0:(o[i]=='R'?1:2));
	return s;
}
void out(int i,int s) {
	if(i==n) return cout<<f[s]<<"\n",void();
	out(i+1,s<<2|1);
	out(i+1,s<<2|2);
	out(i+1,s<<2);
}
signed main() {
	ios::sync_with_stdio(false);
	cin>>n>>X>>Y,N=1<<(n*2);
	for(int i=0;i<n;++i) Z=Z<<2|1;
	for(int i=0;i<X;++i) ++f[read()];
	for(int i=0;i<Y;++i) ++g[read()];
	for(int k=1;k<N;k<<=2) for(int i=0;i<N;i+=k<<2) for(int j=i;j<i+k;++j) {
		f[j+3*k]+=f[j]+f[j+k]+f[j+2*k];
		g[j+3*k]+=g[j]+g[j+k]+g[j+2*k];
	}
	for(int s=0;s<N;++s) {
		f[s]*=g[s];
		if((n&1)^__builtin_parity(s&(s>>1)&Z)^1) f[s]*=-1;
	}
	f[N-1]=0;
	for(int k=1;k<N;k<<=2) for(int i=0;i<N;i+=k<<2) for(int j=i;j<i+k;++j) {
		f[j]+=f[j+3*k],f[j+k]+=f[j+3*k],f[j+2*k]+=f[j+3*k];
	}
	out(0,0);
	return 0;
}
```

---

## 作者：tzl_Dedicatus545 (赞：0)

简单题。

首先至少赢一次是搞笑的限制，总数减一下变成一次也不能赢。

> 请回忆 FWT 的过程：
> 
> 我们认为 FWT 的过程对于任意位是独立的，不妨令 $c(i,s)$ 是 $f_i$ 对 $\text{FWT}_s$ 的贡献。读者可以自行验证该矩阵 $c$ 对于运算 $\circ$ 应当满足以下限制：
>
> $\forall s,t,i$ 有 $c(s,i)c(t,i)=c(s\circ t,i)$。

对于本题，首先转移类似一个 $\text{R} \circ \text{S} = \{\text{R,S,P}\}$，$\text{R} \circ \text{R} = \{\text{R,S}\}$ 的样子。不妨把四种本质不同的集合压成一个四进制数，$\circ$ 真值表如下：

$$
x \circ y= \begin{cases} 0 & (x\neq y)\\ x &  (x=y)\end{cases}
$$

如此一来，方便的写出转移矩阵 $c$：

$$
\begin{bmatrix}
   1 & 0 & 0 & 0\\
   1 & 1 & 0 & 0\\
   1 & 0 & 1 & 0\\
   1 & 0 & 0 & 1
\end{bmatrix}
$$

最后我们按位做一次高位后缀和状物就行了。

复杂度 $O(k4^k)$。

能让我，赢一次吗？

---

