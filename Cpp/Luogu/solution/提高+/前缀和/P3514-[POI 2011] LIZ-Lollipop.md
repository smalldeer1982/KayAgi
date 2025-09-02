# [POI 2011] LIZ-Lollipop

## 题目描述

给一个只有 $1$ 和 $2$ 的序列，每次询问有没有一个子串的和为 $x$。

## 样例 #1

### 输入

```
5 3
TWTWT
5
1
7```

### 输出

```
1 3
2 2
NIE```

# 题解

## 作者：LightningUZ (赞：30)

很巧妙的思维题。

题意是这样的，给你一个串，只有 T 和 W。令 T=2，W=1，将其变成数字串。然后每次给一个 $k$,问是否存在一个子段和为 $k$。

## 判断是否有解

**重要结论1**：如果 $k(k>2)$ 可以，$k-2$ 也可以。

> 证：假设 $[l,r]$ 区间的和是 $k$。   
  如果这个区间的两边 （$a[l]$，$a[r]$） 中有一个是 $2$，那么把这个去掉 （变成 $l,r-1$ 或 $l+1,r$），那就有 $k-2$了   
  否则它两边就都是 $1$。把两边都去掉，那就有 $k-2$ 了。
  综上，我们一定有 $k-2$。  
  **证毕**

然后就好做了：找到最大的奇数，最大的偶数；对于奇数，判断它是否小于最大的奇数，偶数同理。

如何找到最大的奇数/偶数？

设 $S$ 表示总和，$M_{0/1}$ 表示最大的偶数/奇数。

显然 $M_{S\%2}=S$

**重要结论2**：只要枚举左边/右边删连续的就行。

> 证： 假设我们非要删掉两边才能使答案最优   
  如果两边中有一边是偶数，那偶数这边不删，肯定更优   
  否则，两边都是奇数。两边都不删，肯定更优   
  注：“更优”表示的是，模 $2$ 余数不变，并且和更大   
  **证毕**

## 输出解

设 $[l_k,r_k]$ 表示和为 $k$ 的区间。

首先，$l_S=1,r_S=n$

然后，我们在枚举删前后，求出 $M_{0/1}$ 的时候，可以顺便把区间记下来，这样就有了 $k=M_{0/1}$ 时的答案区间了。

对于答案区间 $[l_k,r_k]$，可以像 “判断是否有解” 一章中，**重要结论1** 的证明里面一样，枚举它左边/右边是 $2$，或者两边都是 $1$，推出 $l_{k-2},r_{k-2}$

然后就显然可以推出所有的答案区间了。

## simple 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Flandre_Scarlet
{
    #define N 4000006
    #define F(i,l,r) for(int i=l;i<=r;++i)
    #define D(i,r,l) for(int i=r;i>=l;--i)
    #define Fs(i,l,r,c) for(int i=l;i<=r;c)
    #define Ds(i,r,l,c) for(int i=r;i>=l;c)
    #define MEM(x,a) memset(x,a,sizeof(x))
    #define FK(x) MEM(x,0)
    #define Tra(i,u) for(int i=G.Start(u),v=G.To(i);~i;i=G.Next(i),v=G.To(i))
    #define p_b push_back
    #define sz(a) ((int)a.size())
    #define all(a) a.begin(),a.end()
    #define iter(a,p) (a.begin()+p)
    int I() {char c=getchar(); int x=0; int f=1; while(c<'0' or c>'9') f=(c=='-')?-1:1,c=getchar(); while(c>='0' and c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar(); return (x=(f==1)?x:-x);}
    void Rd(int cnt,...) {va_list args;va_start(args,cnt); F(i,1,cnt) {int* x=va_arg(args,int*);(*x)=I();} va_end(args);}
    void RA(int *a,int n) {int *p=(a+1); F(i,1,n) {(*p)=I();++p;}}
    int n,m;
    char ss[N]; int a[N];
    void Input()
    {
        Rd(2,&n,&m); scanf("%s",ss+1);
        F(i,1,n) a[i]=(ss[i]=='T')?2:1;
    }
    int s[N];
    int Max[2]; int l[N],r[N];
    void up(int a,int ll,int rr)
    {
        if (a>Max[a%2]) {Max[a%2]=a; l[a]=ll; r[a]=rr; }
    } 
    void get(int &l,int &r,int pl,int pr)
    {
        if (pl==0 and pr==0) return;
        l=pl,r=pr;
        if (a[pl]==2) ++l;
        else if (a[pr]==2) --r;
        else ++l,--r;
    }
    void Soviet()
    {
        F(i,1,n) s[i]=s[i-1]+a[i];
        F(i,1,n-1) {up(s[n]-s[i],i+1,n); up(s[i],1,i);} up(s[n],1,n);
        // 枚举删左边/右边，以及全选
        D(i,2*n,1) get(l[i],r[i],l[i+2],r[i+2]);
        // 继承
        F(i,1,m)
        {
            int k=I();
            if (k>Max[k%2]) puts("NIE");
            else printf("%d %d\n",l[k],r[k]);
        }
    }
    void IsMyWife()
    {
        Input();
        Soviet();
    }
}
#undef int //long long
int main()
{
    Flandre_Scarlet::IsMyWife();
    getchar();
    return 0;
}
```

---

## 作者：George1123 (赞：10)

# [POI2011]LIZ-Lollipop

**[博客中阅读](https://www.cnblogs.com/Wendigo/p/12493641.html)**

**前置知识：**
> 破脑术开脑洞。

---

> [\[POI2011\]LIZ-Lollipop](https://www.luogu.com.cn/problem/P3514)

> 给定一个长度为 $n$ 的序列 $a\{n\}(a_i\in{1,2})$，$m$ 次询问求 $k$ 是否可以表示成连续某段序列 $a_L\sim a_R$ 的和。如果可以，输出 $L$ 和 $R$。否则，输出 $\texttt{NIE}$。（注：读入序列用字符串，$\texttt{T}$ 表示 $2$，$\texttt{W}$ 表示 $1$）。

> 数据范围：$1\le n,m\le 10^6$，$1\le k\le 2\times 10^6$。

---

如果不是思维难度的原因，这题是橙色的吧。

---

首先想到区间和就要先把前缀和算出来。

用**逆推**做。**如果有一个区间 $[L,R]$ 的和为 $x$，那么如何得出和为 $x-2$ 的区间呢**：

1. 满足 $a_L=2$ 或 $a_R=2$，所以和为 $x-2$ 的区间是 $[a_L+1,a_R]$ 或 $[a_L,a_R-1]$。

2. 否则肯定 $a_L=a_R=1$，那么和为 $x-2$ 的区间就是 $[a_l+1,a_R-1]$。

所以只需要找出最大的奇数区间和 $x$ 和最大的偶数区间和 $x$ 即可。

然后逆推别的，可以循环或者递归，至于找最大奇偶数区间和，就不必多说了。

---

$\texttt{code}$

```cpp
#include <bits/stdc++.h>
using namespace std;

//&Start
#define lng long long
#define lit long double
#define re register
#define kk(i,n) " \n"[i==n]
const int inf=0x3f3f3f3f;
const lng Inf=0x3f3f3f3f3f3f3f3f;

//&Data
const int N=1e6;
int n,m,a[N+10],mo=-1,me=-1;
int l[(N<<1)+10],r[(N<<1)+10],sum[N+10];
//l[i] 表示区间和为 i 的区间左端点，r[i] 表示右端点（不开双倍空间也能得不少分吧）
char c[N+10];

//&Solve
void solve(int x){ //循环实现逆推
	if(x<=2) return;
	if(a[l[x]]==2) l[x-2]=l[x]+1,r[x-2]=r[x];
	else if(a[r[x]]==2) l[x-2]=l[x],r[x-2]=r[x]-1;
	else l[x-2]=l[x]+1,r[x-2]=r[x]-1;
	solve(x-2);
}

//&Main
int main(){
	memset(l,-1,sizeof l);
	memset(r,-1,sizeof r);
	scanf("%d%d%s",&n,&m,c+1);
	//-----------------魔芋分割线---------------------------
	for(int i=1;i<=n;i++) a[i]=(c[i]=='T'?2:1);
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i]; //求前缀和
	//-----------------魔芋分割线---------------------------
	if(sum[n]&1) mo=sum[n],l[mo]=1,r[mo]=n;
	else me=sum[n],l[me]=1,r[me]=n; //因为所有数的和肯定是该奇偶性下最大的
	// printf("varque %d %d\n",mo,me);
	//-----------------魔芋分割线---------------------------
	int lf=-1,ri=-1;
	for(int i=1;i<=n;i++)if(a[i]==1){lf=i;break;}
	for(int i=n;i>=1;i--)if(a[i]==1){ri=i;break;}//找1，得出另外奇偶性下最大的区间和
	//-----------------魔芋分割线---------------------------
	int tmp=-1,lt=-1,rt=-1;
	if(lf!=-1&&sum[n]-sum[lf]>tmp)
		tmp=sum[n]-sum[lf],lt=lf+1,rt=n;
	if(ri!=-1&&sum[ri-1]>tmp)
		tmp=sum[ri-1],lt=1,rt=ri-1;
	//-----------------魔芋分割线---------------------------
	if(sum[n]&1) me=tmp,l[me]=lt,r[me]=rt;
	else mo=tmp,l[mo]=lt,r[mo]=rt;
	// printf("varque %d %d\n",mo,me);
	//-----------------魔芋分割线---------------------------
	solve(mo); //逆推
	solve(me);
	//-----------------魔芋分割线---------------------------
	for(int i=1,x;i<=m;i++){
		scanf("%d",&x);
		if(l[x]==-1&&r[x]==-1) puts("NIE"); //没有方案
		else printf("%d %d\n",l[x],r[x]); //输出
	}
	return 0;
}

```

---

**祝大家学习愉快！**

---

## 作者：fy0123 (赞：9)

思维题。

我们想办法从大到小构造解，比如一个序列是TTWTWWTW，那么2+2+1+2+1+1+2+1=12，12肯定合法并且方案为[1,n]。那么我们观察一下发现[2,n]就是10，进一步可以发现所有和12奇偶性相同的都可以构造出来，具体的，可以按如下方案构造：（记Sum[l,r]为[l,r]的权值和，s[x]为第x位的字符）

- 若当前区间Sum[l,r]=x，那么若`s[l]=='W'&&s[r]=='W'`，可推出Sum[l+1,r-1]=x-2

- 否则若`s[l]=='T'`，可推出Sum[l+1,r]=x-2

- 否则可推出Sum[l,r-1]=x-2

那么事情就变得简单了，我们只要求出能表示出来的最大奇/偶数即可，然后从最大数往下推，就可以处理出所有答案了。至于怎么求能表示出来的最大奇/偶数，显然一个是Sum[1,n]，另一个是找到从左往右（或从右往左）第一个`'W'`的位置i，把[1,i]（或[i,n]）删去后的子段和。

代码如下：

```cpp
#include<bits/stdc++.h>
#define rep(i,x,y) for (int i=(x);i<=(y);i++)
using namespace std;
const int N=2e6+100;
int n,m,sum1,sum2,l1,r1,l2,r2,l[N],r[N]; char str[N];
int main(){
	scanf("%d%d%s",&n,&m,str+1);
	rep (i,1,n) sum1+=1+(str[i]=='T'); l1=1,r1=n;
	sum2=0;
	rep (i,1,n) if (str[i]=='W'){sum2=max(sum2,sum1-i*2+1); l2=i+1,r2=n; break;}
	for (int i=n;i;i--) if (str[i]=='W'){if (sum1-(n-i)*2-1>sum2) sum2=sum1-(n-i)*2-1,l2=1,r2=i-1; break;}
	if (!(sum1&1)) swap(sum1,sum2),swap(l1,l2),swap(r1,r2);
	for (int i=sum1;i>=1;i-=2){
		l[i]=l1,r[i]=r1;
		if (str[l1]=='W'&&str[r1]=='W') l1++,r1--;
		else if (str[l1]=='T') l1++; else r1--;
	}
	for (int i=sum2;i>=1;i-=2){
		l[i]=l2,r[i]=r2;
		if (str[l2]=='W'&&str[r2]=='W') l2++,r2--;
		else if (str[l2]=='T') l2++; else r2--;
	}
	while (m--){
		int x; scanf("%d",&x);
		if ((x&1)&&x>sum1||!(x&1)&&x>sum2) puts("NIE"); else printf("%d %d\n",l[x],r[x]);
	}
	return 0;
}
```

---

## 作者：Biscuit46 (赞：7)

**先挂一个自己博客的链接:[Anderson](https://www.cnblogs.com/cjgjh)**

**在原博客使用效果更佳!**

## 原题
[题面](https://www.luogu.org/problemnew/show/P3514)

## Solution
~~我是不会告诉你我一开始写了一个二分答案+rand的算法的。。。~~
这样子你可以获得80分的好成绩！！！
```cpp
#pragma GCC diagnostic error "-std=c++11"
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<iostream>
#include<queue>
#define ll long long
#define file(a) freopen(a".in","r",stdin)//;freopen(a".out","w",stdout)
using namespace std;
inline int gi(){
    int sum=0,f=1;char ch=getchar();
    while(ch>'9' || ch<'0'){if(ch=='-')f=-f;ch=getchar();}
    while(ch>='0' && ch<='9'){sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
    return f*sum;
}
inline ll gl(){
    ll sum=0,f=1;char ch=getchar();
    while(ch>'9' || ch<'0'){if(ch=='-')f=-f;ch=getchar();}
    while(ch>='0' && ch<='9'){sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
    return f*sum;
}
int a[2000010],sum[2000010];
struct node{
    int id,val;
    bool operator<(const node b)const{
        return val<b.val;
    }
}d[2000010];
int main(){
    srand(time(NULL));
#ifndef ONLINE_JUDGE
    file("example");
#endif
    int i,j,n,m,k;
    n=gi();m=gi();
    for(i=1;i<=n;i++){
        char ch=getchar();
        a[i]=ch=='W'?1:2;
    }
    for(i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];
    for(i=1;i<=n;i++){
        d[i]=(node){i,rand()};
    }
    sort(d+1,d+n+1);
    while(m--){
        k=gi();int flag=0;
        for(int x=1;x<=n;x++){
            i=d[x].id;
            int l=i,r=n,ans=0;
            while(l<=r){
                int mid=(l+r)>>1;
                if(sum[mid]-sum[i-1]>k)r=mid-1;
                else if(sum[mid]-sum[i-1]<k)l=mid+1;
                else{ans=mid;break;}
            }
            if(ans){
                printf("%d %d\n",i,ans);flag=1;
                break;
            }
        }
        if(!flag)puts("NIE");
    }
    return 0;
}
```

这是一道比较有思维难度的题目，我们考虑一下如果一段区间有1，那么显然都可以完成对吧。
这里给一个比较简单的证明:
$Sum$表示前i个数的和,$sum_i$表示i往后有多少个T.我们考虑当前这个数如果是T(2),那么有如下两种情况
- i向后延续的长度>1向后延续的长度,则有:
$Sum-1=a_{sum_1+2}+a_{sum_1+3}+...+a_{sum_1+i}$

这个可以这么想,我们把它差分一下,变成:
$a_1+a_2+...+a_{sum_1+i}-a_1-a_2-...-a_{sum_1+1}$
因为$1~sum_1$都是2,所以前面的数都是2.
然后我们考虑第一个式子$a_1+a_2+a_3+...+a_{sum_1+i}$
因为i向后延续的长度>1向后延续的长度,所以我们考虑把这i个数往前移,然后把1往后延续的长度放到后面,就有
原式=$a_1+a_2+...+a_{sum_1+i}-a_1-a_2-a_{sum_1+1}=Sum-1$

---
- 如果i延续的长度不能够到n,则有:
$Sum-1=a_{sum_i+1}+a_{sum_i+2}+...+a_{sum_i+i}$

同理可证

----

那么就可以写出下面这段代码了.


```cpp
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<iostream>
#include<queue>
#define ll long long
#define file(a) freopen(a".in","r",stdin)//;freopen(a".out","w",stdout)
using namespace std;
inline int gi(){
    int sum=0,f=1;char ch=getchar();
    while(ch>'9' || ch<'0'){if(ch=='-')f=-f;ch=getchar();}
    while(ch>='0' && ch<='9'){sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
    return f*sum;
}
inline ll gl(){
    ll sum=0,f=1;char ch=getchar();
    while(ch>'9' || ch<'0'){if(ch=='-')f=-f;ch=getchar();}
    while(ch>='0' && ch<='9'){sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
    return f*sum;
}
int a[2000010],sum[2000010],Sum,l[2000010],r[2000010];
int main(){
#ifndef ONLINE_JUDGE
    file("example");
#endif
    int i,j,n,m,k;
    n=gi();m=gi();
    for(i=1;i<=n;i++){
        char ch=getchar();
        if(ch=='T')a[i]=2;
        else a[i]=1;
    }
    for(i=n;i;i--)sum[i]=a[i]==2?(sum[i+1]+1):0;
    int Sum=0;
    for(i=1;i<=n;i++){
        Sum+=a[i];
        l[Sum]=1;r[Sum]=i;
        if(a[i]==2)
            if(sum[i]>sum[1])l[Sum-1]=sum[1]+2,r[Sum-1]=sum[1]+i;
            else if(sum[i]!=n-i+1)l[Sum-1]=sum[i]+1,r[Sum-1]=sum[i]+i;
    }
    while(m--){
        k=gi();
        if(l[k])printf("%d %d\n",l[k],r[k]);
        else puts("NIE");
    }
    return 0;
}
```

---

## 作者：Alex_Wei (赞：3)

> **[P3514 [POI2011]LIZ-Lollipop](https://www.luogu.com.cn/problem/P3514)*
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/poi.html)。

元素权值仅有 $1$ 和 $2$ 一定是非常重要的限制。考虑固定左端点 $l$，右端点 $r$ 从 $l\to n$ 的过程。设 $[l, r]$ 之和为 $v_{l, r}$，容易证明若 $1 \leq k < s$ 且 $k$ 不能被表示为以 $l$ 开头的某个子串和，则 $k + 1$ 一定可以被表出。否则至少存在一个元素权值不小于 $3$。

因此，考虑找到最长的后缀 $[l, n]$ 使得 $s_l = \tt W$（即找到最小的 $l$ 使得 $s_l = \tt W$），则根据上述性质，$1\sim v_{l, n}$ 一定全部能被表示出来，因为若 $2\leq k < v_{l, n}$ 不能被以 $l$ 开头的某个子串和表出，则 $k + 1$ 一定能被以 $l$ 开头的某个子串和表出，所以 $k$ 一定能被以 $l + 1$ 开头的某个子串和表出。同理，最长的前缀 $[1, r]$ 同样满足该性质。

因此，求出开头和末尾的连续的 $2$ 的个数 $be, ed$。若 $be \leq ed$，说明 $[l, n]$ 之和大于 $[1, r]$ 之和，用后缀来做。否则用前缀来做。可以通过翻转序列避免分类讨论，因此不妨设 $[l, n]$ 之和更大。

设 $buc_k$ 表示 $[l, buc_k]$ 之和等于 $k$。注意 $buc_k$ 可能不存在，但此时根据上述性质，$buc_{k + 1}$ 存在。

- 若询问的 $k \leq v_{l, n}$，则若 $buc_k$ 存在，输出 $l, buc_k$。否则输出 $l + 1, buc_{k + 1}$。
- 否则，若 $k \leq v_{1, n}$ 且 $k$ 与 $v_{l, n}$ 的奇偶性相同（因为接下来只能让 $l$ 往左移，每次添加 $2$），则输出 $l - \frac{k - v_{l, n}} 2, n$。
- 否则无解。

时间复杂度线性。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read() {
	int x = 0; char s = getchar();
	while(!isdigit(s)) s = getchar();
	while(isdigit(s)) x = x * 10 + s - '0', s = getchar();
	return x;
}
inline void print(int x) {
	if(x >= 10) print(x / 10);
	putchar(x % 10 + '0');
}

const int N = 1e6 + 5;
int n, m, sum, p, be, ed, buc[N];
char s[N];
int main() {
	scanf("%d %d %s", &n, &m, s + 1);
	for(int i = 1; i <= n && s[i] == 'T'; i++) be++;
	for(int i = n; i && s[i] == 'T'; i--) ed++;
	if(be > ed) reverse(s + 1, s + n + 1);
	for(int i = 1; i <= n && !sum; i++)
		if(s[i] == 'W') {
			buc[sum = 1] = p = i;
			for(int j = i + 1; j <= n; j++) buc[sum += s[j] == 'W' ? 1 : 2] = j;
		}
	for(int i = 1; i <= m; i++) {
		int k = read(), l = -1, r = -1;
		if(k <= sum) buc[k] ? (l = p, r = buc[k]) : (l = p + 1, r = buc[k + 1]);
		else if((k - sum >> 1) < p && !(k - sum & 1)) l = p - (k - sum >> 1), r = n;
		if(l == -1) puts("NIE");
		else {
			if(be > ed) swap(l, r), l = n + 1 - l, r = n + 1 - r;
			print(l), putchar(' '), print(r), putchar('\n');
		}
	}
	return 0;
}
```

---

## 作者：Durancer (赞：2)

### 前置知识

- 钻脑机，开发脑洞

- 瞪眼法，寻找性质

- 人工手，会打代码

### 思路

看着几乎都没有人打暴力的啊=_=，为了把原始的思考过程呈现出来还是一步一步讲吧。

- $60 \text{pts}$

如果是在线的话有点太难办了，直接离线下来做，或者询问之前预处理：

我们考虑用双指针，$r$ 指针不断向右移动， $l$ 指针每次 $r$ 指针都移动之后重置一遍，保证可以遍历到每一个区间。


时间复杂度为 $O(\sum_{i=1}^n\sum_{j=1}^ij)$。

如果有什么牛逼优化貌似可以拿到 $80\text{pts}$ 的好成绩，但是想部分分有时候比正解还难想，这里不再赘述。

- $100 \text{pts}$

在线处理显然是很难的，需要优化 $O(nq)$ 的时间复杂度，我们思考一下有没有 $O(n)$ 的算法来通过预处理解决。

**可以发现一个很重要的性质：**

如果有一个子区间的值为 $val$，($val\ge2$ )，那么一定可以通过把区间右端点左移一个位置，或者左端点右移一个位置，或者左右各缩小一个位置来得到，因为左右两边的值肯定是 $1\ \text{or}\ 0$。

首先预处理出所有 $[1,i],[i+1,n]$ 以及 $[1,n]$ 的区间值，然后判断一下区间的值在奇数和偶数的时候的最大值，防止出现区间更新变成负数的情况。

然后就可以愉快的 $O(n)$ 预处理，$O(1)$ 询问啦！

### 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int N=1e6+9;
const int M=2e6+9;
int L[M],R[M];
int a[N],s[N];
int n,Q;
int Max[2];//0 - > 偶数 ， 1 - > 奇数 
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar();}
	return f*x;
} 
void update(int l,int r)
{
	int val=s[r]-s[l-1];
	Max[val%2]=max(val,Max[val%2]);
	L[val]=l;
	R[val]=r;
}
void get(int &la,int &lb,int l,int r)
{
	la=l; lb=r;
	if(a[la]==2)
		la++;
	else if(a[lb]==2)
		lb--;
	else 
	{
		la++;
		lb--; 
	}
}
int main()
{
	n=read(); Q=read();
	for(int i=1;i<=n;i++)
	{
		char s;
		scanf("%c",&s);
		if(s=='T')
			a[i]=2;
		else a[i]=1;
	}
	for(int i=1;i<=n;i++)
		s[i]=s[i-1]+a[i];
	for(int i=1;i<n;i++)
	{
		update(1,i);
		update(i+1,n);	
	} 
	update(1,n);
	for(int i=2*n-2;i>=1;i--)
		if(Max[i%2]>=i+2)
			get(L[i],R[i],L[i+2],R[i+2]);	
	for(int i=1;i<=Q;i++)
	{
		int x=read();
		if(Max[x%2]>=x)
			printf("%d %d\n",L[x],R[x]);
		else printf("NIE\n");
	}
	return 0;
}
```




---

## 作者：Fading (赞：2)

这个题我做了快$1$个半小时，想了差不多$1$个小时。真是一道好题，容纳了贪心+构造+思维以及奇偶性的性质 ~~，为出题人点赞~~！

结果发现我奇偶考虑的能力还是很菜很菜，愣是没想到。

题解区的做法太神仙了，这里给出我的辣鸡解法。

一开始我的思路是把$1,2$变成$0,1$，枚举长度，结果搞了$30$分钟还是不会，谁可以教教我？

后来思考离线，然后发现还是不会，反过来考虑还是不会，但是突然意识到总和的变化量只能是$1,2$，那么，如果加上一个$1$，两两拼凑，那么$[1,\text{总和}+1]$的答案全部可以表示。于是我就把这个思维题做出来了，真是脑洞大开，希望以后打比赛的时候有今天这么大的脑洞。


------------


具体的，如果有$1$，设最后一次加上$1$后的位置为$R$，$[1,R]$的总和为$\text{bound}$，那么$[1,\text{bound}]$直接可以表示出来。本题还有丧心病狂的输出答案，这时候我们只需要把$R-1,R$的所有后缀拉出来就可以得到答案了。

然后考虑$[\text{bound}+1,\text{Sum}]$的答案，$\text{Sum}$是总和。

注意到$[R+1,n]$全是$2$，那么奇偶性不变：

如果询问的$x\equiv \text{bound}\pmod2$，直接输出$1$和$(\frac{x-\text{bound}}2)+R$，显然右端点$\leq n$。

如果询问的$x\not\equiv \text{bound}\pmod2$，我们找到一个最小的$L$满足$\sum_{i=1}^La_i\not\equiv \text{bound}$，直接输出$L$和$(\frac{x+\sum_{i=1}^La_i-\text{bound}}2)+R$，注意右端点不一定$\leq n$。

如果没有$L$或者计算得到的右端点越界，输出$\text{NIE}$。

思考细节很多，这个题解容纳了我一开始没考虑清楚的很多情况。

时间复杂度$O(n)$。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
#define gc getchar
inline ll read(){
    register ll x=0,f=1;char ch=gc();
    while (!isdigit(ch)){if(ch=='-')f=-1;ch=gc();}
    while (isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=gc();}
    return (f==1)?x:-x;
}
int bound,n,Q,a[1010101],ans[1010101][2],ALL,L,boundL;
bool vis[1010101];
signed main(){
	n=read(),Q=read();
	for (int i=1;i<=n;i++){
		char ch=gc();
		while (!isalpha(ch)) ch=gc();
		a[i]=(ch=='T'?2:1);
	}
	int R=0;
	for (int i=1,MAX=0;i<=n;i++){
		if (a[i]==1){
			bound=MAX+1;R=i;
		}
		MAX+=a[i],ALL+=a[i]; 
	}
	for (int i=R,MAX=0;i>0;i--){
		MAX+=a[i];
		ans[MAX][1]=R,ans[MAX][0]=i;
	}
	for (int i=R-1,MAX=0;i>0;i--){
		MAX+=a[i];
		ans[MAX][1]=R-1,ans[MAX][0]=i;
	}
	for (int i=1,MAX=0;i<=R;i++){
		if (bound%2!=(bound-MAX)%2){
			L=i;boundL=bound-MAX;break;
		}
		MAX+=a[i];
	}
	while (Q--){
		int x=read();
		if (x>ALL) puts("NIE");
		else if (x<=bound) printf("%d %d\n",ans[x][0],ans[x][1]);
		else if ((x-bound)%2==0){
			printf("%d %d\n",1,(x-bound)/2+R); 
		}else if (L&&(x-boundL)/2+R<=n){
			printf("%d %d\n",L,(x-boundL)/2+R); 
		}else puts("NIE");
	}
    return 0;
}

```

另一个做法给出了一个更加直观，更加优美的性质：

由于这个序列只有$1,2$，如果一个区间可以表示出$x$，那么与$x$奇偶性相同的区间全部可以得到。

这个题和以前做过的某 CF 题有异曲同工之妙。总之如果序列的值域很奇怪，绞尽脑汁去想性质~~就好了~~。

---

## 作者：hsaht2426 (赞：1)

方法一：

我们发现找到一个为 $x$ 的区间是**困难的**。

但 $\le x$ 是 $=x$ 的必要条件，于是考虑放缩。

找到一个 $\le x$ 的区间是**平凡的**，可以直接二分。

假设左端点为 $1$。

若二分出为 $x$，即答案。

若二分出为 $x-1$，如何构造出 $x$ 还是不容易，于是**考虑何时无解**。

然后考虑更新 $l$，不可能直接计算，考虑**递推/构成**。

由题得未选到的第一个数是 $2$，那么分类讨论。

如果第一个位置为 $1$，这时可以直接去 $1$ 添 $2$。

否则，我们发现这样的区间可以直接搬运，即 $l,r$ 同时加 $1$。

我们发现第二个过程其实可以**优化**，预处理随便跳即可。

这样就是 $O(m \log n)$ 的，可以通过。

预处理代替二分即可 $O(n)$。

方法二：

注意到 $\omega$ **很小**，我们可以从此入手讨论。

- 考虑初始时全为一的情况。

这样子区间集合等价于从一开始的区间集合。很好做，直接判断大小。

考虑加一个 $2$，发现不是很好做。（有佬会做请教教我）

但是我们可以**考虑另一种简单情形**：（这步挺神仙的，不是很常见）

-  考虑初始时全为二的情况。

显然发现奇数无解，偶数判断大小。

-  考虑加入一个 $1$，分讨一下：

若不经过 $1$，则同原来一样。

若经过 $1$，我们发现**奇偶性**改变了，这样就可以产生与原来不交的一个集合的答案。且依然是从一开始的。

然而构造不太好整了，于是仍然考虑**放缩**，但只是考虑判断无解，即分析答案集合。

- 考虑加入两个 $1$，分讨一下：

同样的考虑奇偶性与分讨：

考虑奇数与前者无异，取 $\max$ 即可，而偶数就会新产生结果，单独分析答案集合。

我们希望它可以满足前者的一些**性质**，此题中为连续性。

手摸一下似乎是满足的（省略）。

容易证明（手摸几组后就很显然了）：

我们发现，左端点在第一个 $1$ 左边，右端点在第二个 $1$ 右边的区间产生的数的集合，与左端点在第一个 $1$ 右边，右端点在第二个 $1$ 左边的区间产生的数的集合，刚好可以拼成一个从 $2$ 开始的连续区间。

所以这样偶数的区间还是从最小值到最大值。

-  由此我们可以猜想：

我们只需求出奇偶最大值即可判断无解。

这仍然不是很好求的，至少不能用之前的思路了。

我们考虑**极限**，若全选，必然为奇偶最大值中的一个。

考虑借此**递推**另一者，由于只有 $1$ 能改变奇偶，所以我们找到最靠前的与最靠后的，减去前/后缀即可。

最后考虑原问题，根据前面的推导，显然是分奇偶递推。

考虑从 $x$ 递推至 $x-2$ 是的情况：（注意这个递推其实也是一种 $\text{dp}$，所以要考虑后效性）

首先对于任何一个 $x$ 递推至 $x-2$ 是否有后效性呢？（即是否所有 $x-2$ 在构造同奇偶答案上等价）

考虑前面的结论，答案是连续的，所以对于任意一个 $x-2$ 均有方案。

然后考虑转移：

两边至少有一个 $2$，我们考虑删去任意一个即可。

两边至少没有 $2$，必然全为 $1$，我们考虑全部删去即可。

于是我们对整个序列的奇偶最大值的区间做一遍，我们就用预处理做完了这道题。

---

## 作者：Unnamed114514 (赞：1)

放在最前面：暴力求叉或证明时间复杂度的正确性。

***

提供一种在线的很简单的不费脑子的~~但是不知道正确性的~~方法。（仅供参考）

首先，既然是在线的，我们容易想到对于每个 $k$，进行一次尺取法，那么显然，我们对于 $[l,r]$ 的指针，在无解的情况下可以移动 $O(n)$ 次，所以最坏复杂度 $O(nm)$。

考虑优化。

***

优化 $1$：当 $k$ 比较大的时候，直接从左往右移动 $r$ 的时间复杂度开销比较大，所以可以考虑在尺取前记录一个数组 $S$ 表示价格的前缀和。因为 $S$ 具有单调性，那么我们就可以直接二分找到 $l=1$ 时对应的左端点。

此时最坏的时间复杂度仍然是 $O(nm)$。

***

优化 $2$：发现此时 $r$ 的移动优化了，我们可以考虑直接优化 $l$ 的移动或者直接移动 $[l,r]$ 这个整体。

记 $c_i$ 表示 $i$ 及 $i$ 后共 $c_i$ 个元素与 $i$ 相同，$s_i$ 为第 $i$ 个字符所对应的值。

此时仍然是 $l=1$ 时求出 $r$，但是 $r$ 应该要保证 $S_r-S_{l-1}<k$ 且 $S_{r+1}-S_{l-1}\ge k$。

此时我们对不同的情况进行分类讨论：

第一种情况：只移动 $r$。

由于 $S_{r+1}-S_{l-1}\ge k$ 且 $s_i$ 的价格一定是有值的，于是 $S_{r+2}-S_{l-1}>k$，所以我们扩展右端点时最多扩展一个元素。如果 $S_{r+1}-S_{l-1}$ 即 $[l,r+1]$ 的和为 $k$，那么此时 $[l,r+1]$ 显然为可行解。

此时我们只移动 $r$ 是显然不可能的了，因为 $S_r-S_{l-1}<k$。并且此时能保证 $S_r-S_{l-1}=k-1$。因为 $S_r-S_{l-1}$ 只能为 $k-1$ 或 $k-2$，但是当 $S_r-S_{l-1}=k-2$ 时，若 $s_{r+1}=1$，那么 $r$ 可以继续向右移动，若 $s_{r+1}=2$，那么此时我们就在只移动右端点的情况下特判掉了。同时，当 $S_r-S_{l-1}=k-1$ 时，若 $s_{r+1}=1$，那么也会被特判掉，于是 $s_{r+1}=2$。此时，若只移动 $l$，那么 $S_{r}-S_{l}\ge2$，是可以取 $s_{r+1}$ 的，所以我们不能只移动 $l$。于是，我们考虑移动 $[l,r]$ 这个整体。

因为 $s_{r+1}$ 已经确定了，所以可以对 $s_l$ 进行分类讨论。

第二种情况：$s_l=2$。

因为同时移动 $l,r$ 会使 $[l,r]$ 的和不变，容易发现为了保证 $S_r-S_{l-1}=k-1$ 的特殊性质，我们只能将 $[l,r]$ 移动相同的数。

此时，我们移动 $\min\{c_l,c_{r+1}\}$ 次后，才暂时不会出现这种情况，所以我们此时可以直接 $val=\min\{c_l,c_{r+1}\},l\gets l+val,r\gets r+val$。

第三种情况：$s_l=1$。

此时注意到 $S_r-S_{l-1}=k-1$，由于 $s_{r+1}=s_l+1$，所以 $S_{r+1}-S_l=k$，那么此时 $[l+1,r+1]$ 就是一组可行解。

时间复杂度？

最坏的话个人认为是 $O(nm)$，但是实际上远远跑不满，~~清纯少女~~ tzl 认为这个东西的时间复杂度是 $O(m)$ 乘上一个大常数，这个意见保留。时间复杂度姑且记作 $O(km)$ （$k$ 是大常数），暂时不知道最坏能不能卡到 $O(nm)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int n,m,k,c[maxn],mp[26],S[maxn];
string s;
inline void work(int x){
	int l=1,r=lower_bound(S+1,S+n+1,x)-S-1;
	while(r<n){
		if(S[r+1]-S[l-1]==x){
			printf("%d %d\n",l,r+1);
			return;
		}
		if(s[l]==s[r+1]){
			int val=min(c[l],c[r+1]);
			l+=val,r+=val;
		} else{
			if(s[l]=='T'){
				int val=min(c[l],c[r+1]/2);
				l+=val,r+=val*2;
			} else{
				printf("%d %d\n",l+1,r+1);
				return;
			}
		}
	}
	puts("NIE");
}
int main(){
	mp['T'-'A']=2,mp['W'-'A']=1;
	scanf("%d%d",&n,&m);
	cin>>s;
	s=' '+s;
	c[n]=1;
	for(int i=1;i<=n;++i)
		S[i]=S[i-1]+mp[s[i]-'A'];
	for(int i=n-1;i;--i)
		if(s[i]==s[i+1])
			c[i]=c[i+1]+1;
		else
			c[i]=1;
	while(m--){
		scanf("%d",&k);
		work(k);
	}
	return 0;
}
```

---

## 作者：Sol1 (赞：1)

给一个相对不是很难想的做法。

一个序列 $211221121$，其前缀和为 $2,3,4,6,8,9,10,12,13$，缺少的是 $1,5,7,11$。

然后对序列以 $2$ 为开头进行分段：$211/2/211/21$，第一段前缀和是 $[2,4]$，第二段是 $[6,6]$，第三段是 $[8,10]$，第四段是 $[12,13]$。从这个分段看出，不会有两个相邻的数都不在前缀和内出现。

这提示我们什么？

如果再在序列前面加一个 $1$，那么每一个不在前缀和中的数都能被前面一个在前缀和内的数补上。

也就是说形如 $111\cdots 112\texttt{-}\texttt{-}\texttt{-}\cdots\texttt{-}$ 的序列一定可以表示出 $[1,S]$ 内所有的数。其中 $\texttt{-}$ 表示这一位可以是任意数，$S$ 表示序列的和。

然后对于所有情况，就是在 $111\cdots 112\texttt{-}\texttt{-}\texttt{-}\cdots\texttt{-}$ 前面再添加若干个 $2$（可以是 $0$ 个）以及后面会写到的两种特殊情况。

设原序列为 $A$，$A$ 去掉前缀 $2$ 后为 $A_{[i,n]}$，$A_{[i,n]}$ 再去掉前缀 $1$ 后为 $A_{[j,n]}$。

先做一遍 $A_{[j,n]}$ 的前缀和，将 $\sum_{x=j}^kA_x$ 的答案记录为 $[j,k]$。

然后从 $2$ 到 $\sum_{k=i}^nA_k$ 枚举和 $s$，如果 $s$ 已经有答案则不需要记录，否则将 $s-1$ 的答案的左端点向左扩展 $1$ 得到 $s$ 的答案，并将 $1$ 的答案记为 $[i,i]$。

再对 $A_{[i,n]}$ 做前缀和，设 $S(i,r)=\sum_{k=i}^rA_k$，则记 $b_{S(i,r)}=r$。

然后预处理 $p_k$ 代表对于 $k$，补最少的 $2$ 使得补到一个 $b$ 中有值的位置会补到哪。如果 $b_i$ 有值，则 $p_i=i$。否则 $p_i=p_{i-2}$。

这样对于一次查询 $k$，如果 $k$ 已经记录有答案区间 $[l,r]$，直接输出答案区间，否则设 $x=p_k$。如果 $i\leq \dfrac{k-x}{2}$，则需要补的 $2$ 超过前缀 $2$ 的个数，输出 `NIE`；否则就补这么多个 $2$ 就可以了。

然后是两种特殊情况：

1. 整个序列全是 $2$，随便做。
2. 序列是一段 $2$ 接一段 $1$，数一下后面有多少个 $1$ 然后对于 $1$ 不够的查询就往前补 $2$。

时空复杂度 $O(n+m)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[(1<<21)+5], *p1 = buf, *p2 = buf;

inline int qread() {
	char c = getchar();
	int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}

int n, q, a[1000005], sum[1000005], ansl[2000005], ansr[2000005], sumidx[2000005], pre[2000005];

inline char readchar() {
	char c = getchar();
	while (c < 'A' || c > 'Z') c = getchar();
	return c;
}

inline void Read() {
	n = qread(); q = qread();
	for (int i = 1;i <= n;i++) {
		if (readchar() == 'T') a[i] = 2;
		else a[i] = 1;
	}
}

inline void Solve() {
	int idx1 = n + 1, idx2 = n + 1;
	for (int i = 1;i <= n;i++) {
		if (a[i] == 1) {
			idx1 = i;
			break;
		}
	}
	if (idx1 == n + 1) {
		for (int i = 1;i <= q;i++) {
			int k = qread();
			if (k & 1) puts("NIE");
			else printf("1 %d\n", k >> 1);
		}
		return;
	}
	for (int i = idx1;i <= n;i++) {
		if (a[i] == 2) {
			idx2 = i;
			break;
		}
	}
	if (idx2 == n + 1) {
		ansl[1] = ansr[1] = idx1;
		for (int i = 2;;i++) {
			if (ansr[i - 1] == n) break;
			ansr[i] = ansr[i - 1] + 1;
		}
	} else {
		int sum = 0;
		for (int i = idx2;i <= n;i++) {
			sum += a[i];
			ansl[sum] = idx2; ansr[sum] = i;
		}
		for (int i = idx1;i < idx2;i++) sum += a[i];
		ansl[1] = ansr[1] = idx1;
		for (int i = 2;i <= sum;i++) {
			if (!ansl[i]) {
				ansl[i] = ansl[i - 1] - 1;
				ansr[i] = ansr[i - 1];
			}
		}
		sum = 0;
		for (int i = idx1;i <= n;i++) {
			sum += a[i];
			sumidx[sum] = i;
		}
		for (int i = 3;i <= 2 * n;i++) {
			if (sumidx[i]) pre[i] = i;
			else pre[i] = pre[i - 2];
		}
	}
	while (q--) {
		int k = qread();
		if (ansl[k]) printf("%d %d\n", ansl[k], ansr[k]);
		else {
			int p = pre[k], len = (k - p) / 2;
			if (len >= idx1 || !p) puts("NIE");
			else printf("%d %d\n", idx1 - len, sumidx[p]);
		}
	}
}

int main() {
	Read();
	Solve();
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

这个题好多人貌似都是用前缀的性质去做的，不过我用的不是那种方法。

首先就有一个显然的暴力思路：每次处理询问的时候，从1~n扫一遍，找他的前缀和是否和前面的某个前缀和差值为x，复杂度是$O(nm)$的，如果加上离线排序处理和链表优化什么的可能会快一些~~反正我拿这个水了80分……~~

这样显然是过不去的，于是我们就只有一条路可走：研究只有1、2序列的特殊性质。

研究了半天后，我们可以发现，这个东西可以进行奇偶性的讨论——如果一个数x的答案是区间$[l,r]$，那么比不大于他的的和他奇偶性相同的数都有解，且存在包含于$[l,r]$的答案。

为什么呢？我们不妨这样想，如果把l或r往里移动一位的话，就有三种情况：

1.$a[l]=2$，那么把l右移一位就会使区间和减2

2.$a[r]=2$，那么把r左移一位就会使区间和减2

3.$a[l]=a[r]=1$，那么把l左移一位，把r右移一位就会使区间和减2

所以$x-2$的答案是包含在这个区间中的，归纳可得不超过x的奇偶性相同的数的答案都包含在这个区间中。

于是我们就有了个做法：离线处理，把奇偶性不同的分开处理，（假如我们正在处理偶数，处理奇数的步骤完全相同~~我直接复制的代码~~的）然后从大到小排个序，先找到最大的有解的偶数，$O(n)$找到他的解，然后开始左右端点指针往里移动找后面比他小的偶数的答案就行了。由于指针是单向移动的，所以复杂度为$O(n)$。

然后我们一交，发现TLE了，分跟$O(nm)$暴力一样。

为什么呢？注意我刚才说的“先找到最大的有解的数”，每次查找都是$O(n)$的，如果无解的数特别多的话会被卡成$O(nm)$的。

然后考虑他的优化，上面说了，如果这个数有解，那么比他小的就一定有解，所以这个东西是满足单调性的，可以二分答案。于是我们就二分出最大的有解的数然后再用上述方法处理就行了。总复杂度$O(nlogn)$。

~~还有就是复制代码的时候一定要复制全……我处理奇数的代码直接复制的偶数的，然后没复制全……WA了半天……~~

上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
inline int get(){
	int y;scanf("%d",&y);return(y);
	int n;char c;while((c=getchar())||1)if(c>='0'&&c<='9')break;
	n=c-'0';while((c=getchar())||1){
		if(c>='0'&&c<='9')n=n*10+c-'0';
		else return(n);
	}
}
unsigned char ints[1000001];int sum[1000001],pos[5000001];//pos为前缀和的出现位置
typedef struct _n{
	int data;int index;
	friend bool operator <(const _n &a,const _n &b){
		return(a.data>b.data);
	}
}node;int n;
int ref[200];
char str[1000002];
inline void uget(){
	cin>>str+1;
	for(register int i=1;i<=n;i++){
		ints[i]=ref[str[i]];sum[i]=ints[i]+sum[i-1];pos[sum[i]]=i;
	}
}
int ansl[1000001],ansr[1000001];
node ou[1000001],ji[1000001];
int main(){memset(pos,0x7f,sizeof(pos));ref['W']=1;ref['T']=2;
	n=get();int m=get();uget();
	int ptrji=0,ptrou=0;pos[0]=0;bool bswitch=1;
	for(register int i=1;i<=m;i++){
		int a=get();
		if(a&1){
			ji[ptrji].data=a;ji[ptrji].index=i;ptrji++;
		}else{
			ou[ptrou].data=a;ou[ptrou].index=i;ptrou++;
		}//分离奇偶
	}sort(ou,ou+ptrou);sort(ji,ji+ptrji);
	int l=0,r=ptrou-1;int ans=-1;
	while(l<=r){//二分最大的有解的数
		int mid=(l+r)>>1;
		for(register int i=1;i<=n;i++){
			if(sum[i]>=ou[mid].data){
				if(pos[sum[i]-ou[mid].data]!=0x7f7f7f7f){
					ansl[ou[mid].index]=pos[sum[i]-ou[mid].data]+1,ansr[ou[mid].index]=i;
					r=mid-1;ans=mid;goto s;
				}
			}
		}
		l=mid+1;
		s:;
	}
	if(ans!=-1){
		l=ansl[ou[ans].index],r=ansr[ou[ans].index];int lst=ou[ans].data;
		for(register int i=ans+1;i<ptrou;i++){
			int tmp=lst;
			while(tmp!=ou[i].data){//内向指针处理
				tmp-=2;
				if(ints[l]==1&&ints[r]==1){
					l++;r--;
				}else{
					if(ints[l]==2)l++;
					else r--;
				}
			}ansl[ou[i].index]=l;ansr[ou[i].index]=r;lst=ou[i].data;
		}
	}
	l=0,r=ptrji-1;ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		for(register int i=1;i<=n;i++){
			if(sum[i]>=ji[mid].data){
				if(pos[sum[i]-ji[mid].data]!=0x7f7f7f7f){
					ansl[ji[mid].index]=pos[sum[i]-ji[mid].data]+1,ansr[ji[mid].index]=i;
					r=mid-1;ans=mid;goto s1;
				}
			}
		}
		l=mid+1;
		s1:;
	}
	if(ans!=-1){
		l=ansl[ji[ans].index],r=ansr[ji[ans].index];int lst=ji[ans].data;
		for(register int i=ans+1;i<ptrji;i++){
			int tmp=lst;
			while(tmp!=ji[i].data){
				tmp-=2;
				if(ints[l]==1&&ints[r]==1){
					l++;r--;
				}else{
					if(ints[l]==2)l++;
					else r--;
				}
			}ansl[ji[i].index]=l;ansr[ji[i].index]=r;lst=ji[i].data;
		}
	}
	for(register int i=1;i<=m;i++){
		if(!ansl[i]){
			printf("NIE\n");
		}else{
			printf("%d %d\n",ansl[i],ansr[i]);
		}
	}
	return(0);
}
```

---

## 作者：zc_li (赞：1)

#### 这是一道好玩的思维题
##### 我用了一个清奇的思路
对于一个只有1和2的序列，如果这个序列头是1，则从1到这个序列的总合的值（1到sum[n]间一个值），总有一个数k可以使得a[1]到a[k]的和或a[2]到a[k]的和为这个值。

### 证明如下：
#### 因为1<=a[k]<=2,则sum[k+1]<=sum[k]+2

#### 因为a[1]=1,则sum[k+1]-a[1]<=sum[k]+1

#### 得到
#### sum[k]+1>=sum[k+1]-a[1]
#### sum[k+1]-a[1]+1=sum[k+1]

#### 得到连续序列，证毕。
则如果有一a[i]=1,k<=sum[n]-sum[i-1],总有一以a[i]为头的序列和为k,这种情况只需从这个i最小的a[i]=1,开始二分序列尾,然后输出.
##### 容易得到这个sum[i-1]越小越好，则每次只需寻找第一个i（a[i]=1)
##### 若sum[i-1]>sum[n]-sum[j]（j为最后一个i所在位置),则翻转序列

如果这个i不满足a[i]=1,k<=sum[n]-sum[i-1]，则求a[r,n]（r<i)和为k,因为在第一个1前所有数都为2,所以我们可以直接求出r.

## 代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,a[1000005],qzh[1000005],ywz[1000005],kz=1e9,jl,pd,xk,ppd;

int main() {
	cin>>n>>m;
	for(int i=1; i<=n; i++) {
		char q;
		cin>>q;
		if(q=='T') a[i]=2;
		else a[i]=1;
		qzh[i]=qzh[i-1]+a[i];
	}
	for(int i=n; i>=1; i--) {
		if(kz==1e9) jl=i;
		if(a[i]==1) kz=i,ppd=1;
		ywz[i]=kz;
	}
	if(qzh[ywz[1]]>qzh[n]-qzh[jl-1]) {
		pd=1;
		for(int i=1; i<=n/2; i++) {
			swap(a[i],a[n-i+1]);
		}
	}
	kz=1e9;
	for(int i=n; i>=1; i--) {
		if(a[i]==1) kz=i;
		ywz[i]=kz;
	}
	for(int i=1;i<=n;i++) qzh[i]=qzh[i-1]+a[i];
	xk=qzh[n]-qzh[ywz[1]-1];
	for(int i=1; i<=m; i++) {
		int q;
		cin>>q;
		if(q>qzh[n]||(q>xk&&(q-xk)%2==1)) {
			cout<<"NIE"<<"\n";
			continue;
		}
		if(q<=xk) {
			int l=ywz[1]+1,r=n,mid;
			while(l<=r) {
				mid=(l+r)>>1;
				if(qzh[mid]-qzh[ywz[1]]>q) r=mid-1;
				else l=mid+1;
			}
			if(qzh[r]-qzh[ywz[1]]==q) {
				if(!pd) cout<<ywz[1]+1<<" "<<r<<"\n";
				else cout<<n-r+1<<" "<<n-(ywz[1]+1)+1<<"\n";
				continue;
			}else{
				if(!pd) cout<<ywz[1]<<" "<<r<<"\n";
				else cout<<n-r+1<<" "<<n-(ywz[1])+1<<"\n";
				continue;
			}
		}else{
			q-=xk;
			q/=2;
			if(!pd) cout<<ywz[1]-q<<" "<<n<<"\n";
			else cout<<1<<" "<<n-(ywz[1]-q)+1<<"\n";
		}
	}
	return 0;
}//Rin is a big fAKer.
```


---

## 作者：Lates (赞：0)

1. 发现存在 $k$，必然存在 $k-2$。两边存在 $2$，直接删掉 $2$。两边都是 $1$，都删。于是按照奇偶分类。如果询问不超过对于奇偶性能到达的最大值就有解。

2. 对于区间 $[1,n]$ 的和为 $x$，那么 $x$ 的奇偶性那个最大值是 $x$。考虑找奇偶性相反的最大值。那么有一个结论，就是可以找一段后缀或者前缀当做这个最大值。 

要满足和最大，和的奇偶性不变。两边都是 $1$，则都不删。两边存在一个 $2$，也不必删。于是只需要删一对 $1,2$ 中的 $1$。

然后分别模拟这个过程即可。

```cpp
pair<int,int>b[MAX];
int n,m,pre[MAX],mx[2];
int a[MAX],x,xx;char s;
signed main(){
	n=read(),m=read();
	for(register int i=1;i<=n;++i) {cin>>s;if(s == 'T') a[i] = 2 ; else a[i] = 1;pre[i] = pre[i-1] + a[i];}
	x = pre[n];mx[pre[n] & 1] = pre[n];
	int l = 1,r = n; b[x] = mp(1,n);
	while(l<=r){
		x-=2;if(a[l] == a[r] && a[l] == 1)++l,--r,b[x] = mp(l,r);
		else if(a[l] == 2)++l,b[x] = mp(l,r);
		else if(a[r] == 2)--r,b[x] = mp(l,r);
	}
	x = 0; l = r = -1;
	for(register int i=1;i<=n;++i) if((pre[i] & 1 ) ^ (pre[n] & 1))if(pre[i] > x)x = pre[i],l=1,r=i;
	for(register int i=n;i;--i) if((pre[n] - pre[i-1] & 1) ^ (pre[n] & 1))if(pre[n] - pre[i-1] > x)x = pre[n] - pre[i-1],l = i, r = n;
	if(l!=-1 && r!=-1){
		mx[x&1] = x, b[x] = mp(l,r);
		while(l<=r){
			x-=2;if(a[l] == a[r] && a[l] == 1)++l,--r,b[x] = mp(l,r);
			else if(a[l] == 2)++l,b[x] = mp(l,r);
			else if(a[r] == 2)--r,b[x] = mp(l,r);
		}		
	}
	while(m--){int t =read();if(t<=mx[t&1]) printf("%d %d\n",b[t].first,b[t].second);else puts("NIE");}
	return 0;
}
```

---

## 作者：lytqwq (赞：0)

序列只有 $1$ 和 $2$ 。

假如现在有个子串是 $22222...22$ ，

那么 $k$ 可以是 $2,4,6,8,...$ 。

如果这个子串旁边有个 $1$ ，

如 $122222222...22$ 或是 $22222222...221$ ，

那么现在 $k$ 可以取 $[1,sum]$ 所有数 。

------------

现在给了我们一个序列 $a$ ， 明显 $k$ **可以** 是 $sum$ ， 但是如果最外面都是一堆 $2$ 我们就不能取到 $sum-1$ 。

我们发现如果有一个距离边缘最近的 $1$ 我们把这个 $1$ 到边界的所有的 $2$ 全删掉后，就可以改变 $k$ 的奇偶性了。

假设需要删 $p$ 个 $2$ ，那么 $k$ 可以取 

$ [1,sum-2p] | \{sum-2p,sum-2(p-1),sum-2(p-2),...,sum\} $

按照这个思路把方案写出来即可

代码如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2000010;
int n,m;
int near,sum1[N];
char chr[N];
int l[N],r[N];
int main(){
	scanf("%d%d",&n,&m);
	scanf("%s",chr+1);
	for(int i=1;i<=n;i++){
		if(chr[i]=='W'){
			near=i;
			break;
		}
	}
	for(int i=n;i>=1;i--){
		if(chr[i]=='W'){
			if((n-i)<(near-1)){
				near=i;
			}
			break;
		}
	}
	for(int i=1;i<=n;i++){
		sum1[i]=sum1[i-1];
		if(chr[i]=='W')sum1[i]+=1;
		else sum1[i]+=2;
	}
	int len=min(n-near,near-1);
	if(len==n-near){
		for(int i=n;i>=near;i--){
			l[sum1[i]]=1;r[sum1[i]]=i;
		}
		for(int i=1;i<=near-1;i++){
			l[sum1[near-1]-sum1[i-1]]=i;
			r[sum1[near-1]-sum1[i-1]]=near-1;
		}
		for(int i=1;i<=near;i++){
			l[sum1[near]-sum1[i-1]]=i;
			r[sum1[near]-sum1[i-1]]=near;
		}
	}
	else{
		for(int i=1;i<=near;i++){
			l[sum1[n]-sum1[i-1]]=i;
			r[sum1[n]-sum1[i-1]]=n;
		}
		for(int i=n;i>=near;i--){
			l[sum1[i]-sum1[near-1]]=near;
			r[sum1[i]-sum1[near-1]]=i;
		}
		for(int i=n;i>=near+1;i--){
			l[sum1[i]-sum1[near]]=near+1;
			r[sum1[i]-sum1[near]]=i;
		}
	}
	for(int i=1;i<=m;i++){
		int k;
		scanf("%d",&k);
		if(l[k]!=0&&r[k]!=0){
			printf("%d %d\n",l[k],r[k]);
		}
		else{
			printf("NIE\n");
		}
	}
}
```





---

## 作者：derta (赞：0)

[[POI2011]LIZ-Lollipop](https://www.luogu.com.cn/problem/P3514)

### 题意简述

给出一个长度为 $n$ 的序列 $a$，有 $a_i \in \{1,2\}$，$m$ 次询问，每次询问给定 $k$，求 $l,r$ 使得 $k=\sum_{i=l}^{r}a_i$，若不存在，输出 `NIE`，有 Special Judge（读入时 $a$ 为字符串，`W` 代表 $1$，`T` 代表 $2$）

$n,m \leqslant 10^6$，$1 \leqslant k \leqslant2 \times 10^6$

### 思路
观察到 $k$ 较小，考虑从这里入手

设 $l_k,r_k$ 满足 $k=\sum_{i=l_k}^{r_k}a_i$，考虑从 $k$ 转移到 $k-2$

- $l_k=2$，$l_{k-2}=l_k+1$，$r_{k-2}=r_k$
- $r_k=2$，$l_{k-2}=l_k$，$r_{k-2}=r_k-1$
- 否则，有 $l_k=1$ 且 $r_k=1$，$l_{k-2}=l_k+1$，$r_{k-2}=r_k-1$

先算出 $a$ 数组的总和，再算出与总和奇偶性不同的最大区间和，分别向下递推即可

代码很好写，不给了

---

## 作者：MC_Launcher (赞：0)

### 蒟蒻题解奉上

#### ~~经过了n小时的努力~~才AC



------------
题目思路


------------
$"给定一个长度为n的只包含{1,2}序列，T=2，W=1，给定m组数$
$据，分别询问序列中是否有一段区间和为k。如果有，输出区间$
$的左标和右标，否则输出NIE。"$

对于这道题，我们用逆推的做法

已知一个区间$[l,r]$的和为$x$，那么我们可以很容易地求出$x-2$的值

若$aL$为$1$且$aR$为$1$

那么$[l+1,r-1]$区间和为$x-2$

否则若$aL$为2

那么$[l+1,r]$区间和为$x-2$

反之亦然

逆推代码献上

```cpp
int l[2000001]={},r[2000001]={};
l[kkk]=1;
r[kkk]=n;
for(int i=kkk-2;i>0;i-=2)
{
	if(a[l[i+2]]==1&&a[r[i+2]]==1)
	{
		l[i]=l[i+2]+1;
		r[i]=r[i+2]-1;
	}
	else
	{
		if(a[r[i+2]]==2)
		{
			r[i]=r[i+2]-1;
			l[i]=l[i+2];
		}
		else
		{
			r[i]=r[i+2];
			l[i]=l[i+2]+1;
		}
	}
}
```

这里的$kkk$表示整个序列的和

到这一步，我们已经求出了序列的一半

于是乎，我们需要找到一个$W$，即$1$，这样才能改变奇偶性，同时，又需要使去掉$1$剩下的序列最大

判断代码献上

```cpp
int ms=-1,mz;
for(int i=n;i>=0;i--)
{
	if(a[i]==1)
	{
		ms=i;
		break;
	}
}
if(ms!=-1)
{
	for(int i=1;i<=n;i++)
	{
		if(a[i]==1)
		{
			mz=i;
			break;
		}
	}
	if(b[ms-1]>b[n]-b[ms])
	{
		if(b[ms-1]>b[mz-1])
		{
			if(b[ms-1]>b[n]-b[mz])
			{
				kkk=b[ms-1]; 
				l[b[ms-1]]=1;
				r[b[ms-1]]=ms-1;
			}
			else
			{
				kkk=b[n]-b[mz];
				l[b[n]-b[mz]]=mz+1;
				r[b[n]-b[mz]]=n;
			}
		}
		else
		{
			if(b[mz-1]>b[n]-b[mz])
			{
				kkk=b[mz-1];
				l[b[mz-1]]=1;
				r[b[mz-1]]=mz-1;
			}
			else
			{
				kkk=b[n]-b[mz];
				l[b[n]-b[mz]]=mz+1;
				r[b[n]-b[mz]]=n;
			}
		}
	}
	else
	{
		if(b[n]-b[ms]>b[mz-1])
		{
			if(b[n]-b[ms]>b[n]-b[mz])
			{
				kkk=b[n]-b[ms];
				l[b[n]-b[ms]]=ms+1;
				r[b[n]-b[ms]]=n;
			}
			else
			{
				kkk=b[n]-b[mz];
				l[b[n]-b[mz]]=mz+1;
				r[b[n]-b[mz]]=n;
			}
		}
		else
		{
			if(b[mz-1]>b[n]-b[mz])
			{
				kkk=b[mz-1];
				l[b[mz-1]]=1;
				r[b[mz-1]]=mz-1;
			}
			else
			{
				kkk=b[n]-b[mz];
				l[b[n]-b[mz]]=mz+1;
				r[b[n]-b[mz]]=n;
			}
		}
	}
}
```
手动判断，大佬勿喷，如果有更好的方法请指导一下

因为序列中可能没有$1$，所以循环一次后判断一下，$b$数组为前缀和，$b[i]$记录$a$数组$1$~$i$的和，这样就能更容易地比较每一段区间和，而$kkk$用来记录最大的那段区间和，并将左标$l$和右标$r$记录

接着和上面除了奇偶性不同都相同，代码也一样

最后读入数据判断一下有没有记录左标和右标，有，输出；没有，输出NIE即可

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m;
	cin>>n>>m; 
	int a[n+1]={},kkk=0;
	char x;
	int b[n+1]={};
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		if(x=='T')a[i]=2;
		else a[i]=1;
		kkk+=a[i];
		b[i]=b[i-1]+a[i];
	}
	//一道华丽的分割线 
	int l[2000001]={},r[2000001]={};
	l[kkk]=1;
	r[kkk]=n;
	for(int i=kkk-2;i>0;i-=2)
	{
		if(a[l[i+2]]==1&&a[r[i+2]]==1)
		{
			l[i]=l[i+2]+1;
			r[i]=r[i+2]-1;
		}
		else
		{
			if(a[r[i+2]]==2)
			{
				r[i]=r[i+2]-1;
				l[i]=l[i+2];
			}
			else
			{
				r[i]=r[i+2];
				l[i]=l[i+2]+1;
			}
		}
	}
	//又是一道华丽的分割线 
	int ms=-1,mz;
	for(int i=n;i>=0;i--)
	{
		if(a[i]==1)
		{
			ms=i;
			break;
		}
	}
	if(ms!=-1)
	{
		for(int i=1;i<=n;i++)
		{
			if(a[i]==1)
			{
				mz=i;
				break;
			}
		}
		if(b[ms-1]>b[n]-b[ms])
		{
			if(b[ms-1]>b[mz-1])
			{
				if(b[ms-1]>b[n]-b[mz])
				{
					kkk=b[ms-1]; 
					l[b[ms-1]]=1;
					r[b[ms-1]]=ms-1;
				}
				else
				{
					kkk=b[n]-b[mz];
					l[b[n]-b[mz]]=mz+1;
					r[b[n]-b[mz]]=n;
				}
			}
			else
			{
				if(b[mz-1]>b[n]-b[mz])
				{
					kkk=b[mz-1];
					l[b[mz-1]]=1;
					r[b[mz-1]]=mz-1;
				}
				else
				{
					kkk=b[n]-b[mz];
					l[b[n]-b[mz]]=mz+1;
					r[b[n]-b[mz]]=n;
				}
			}
		}
		else
		{
			if(b[n]-b[ms]>b[mz-1])
			{
				if(b[n]-b[ms]>b[n]-b[mz])
				{
					kkk=b[n]-b[ms];
					l[b[n]-b[ms]]=ms+1;
					r[b[n]-b[ms]]=n;
				}
				else
				{
					kkk=b[n]-b[mz];
					l[b[n]-b[mz]]=mz+1;
					r[b[n]-b[mz]]=n;
				}
			}
			else
			{
				if(b[mz-1]>b[n]-b[mz])
				{
					kkk=b[mz-1];
					l[b[mz-1]]=1;
					r[b[mz-1]]=mz-1;
				}
				else
				{
					kkk=b[n]-b[mz];
					l[b[n]-b[mz]]=mz+1;
					r[b[n]-b[mz]]=n;
				}
			}
		}
	}
	//又双一道华丽的分割线 
	for(int i=kkk-2;i>0;i-=2)
	{
		if(a[l[i+2]]==1&&a[r[i+2]]==1)
		{
			l[i]=l[i+2]+1;
			r[i]=r[i+2]-1;
		}
		else
		{
			if(a[r[i+2]]==2)
			{
				r[i]=r[i+2]-1;
				l[i]=l[i+2];
			}
			else
			{
				r[i]=r[i+2];
				l[i]=l[i+2]+1;
			}
		}
	}
	//又双叒一道华丽的分割线 
	int yyy;
	for(int i=1;i<=m;i++)
	{
		cin>>yyy;
		if(l[yyy]!=0)
		{
			cout<<l[yyy]<<" "<<r[yyy]<<endl;
		}
		else cout<<"NIE"<<endl;
	}
}
```

很长......肯定没人抄我题解

P.S 对不起kkksc03了

---

