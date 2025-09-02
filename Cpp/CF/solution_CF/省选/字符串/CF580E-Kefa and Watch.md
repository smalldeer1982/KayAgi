# Kefa and Watch

## 题目描述

One day Kefa the parrot was walking down the street as he was on the way home from the restaurant when he saw something glittering by the road. As he came nearer he understood that it was a watch. He decided to take it to the pawnbroker to earn some money.

The pawnbroker said that each watch contains a serial number represented by a string of digits from $ 0 $ to $ 9 $ , and the more quality checks this number passes, the higher is the value of the watch. The check is defined by three positive integers $ l $ , $ r $ and $ d $ . The watches pass a check if a substring of the serial number from $ l $ to $ r $ has period $ d $ . Sometimes the pawnbroker gets distracted and Kefa changes in some substring of the serial number all digits to $ c $ in order to increase profit from the watch.

The seller has a lot of things to do to begin with and with Kefa messing about, he gave you a task: to write a program that determines the value of the watch.

Let us remind you that number $ x $ is called a period of string $ s $ ( $ 1<=x<=|s| $ ), if $ s_{i}=s_{i+x} $ for all $ i $ from 1 to $ |s|-x $ .

## 说明/提示

In the first sample test two checks will be made. In the first one substring "12" is checked on whether or not it has period 1, so the answer is "NO". In the second one substring "88", is checked on whether or not it has period 1, and it has this period, so the answer is "YES".

In the second statement test three checks will be made. The first check processes substring "3493", which doesn't have period 2. Before the second check the string looks as "334334", so the answer to it is "YES". And finally, the third check processes substring "8334", which does not have period 1.

## 样例 #1

### 输入

```
3 1 2
112
2 2 3 1
1 1 3 8
2 1 2 1
```

### 输出

```
NO
YES
```

## 样例 #2

### 输入

```
6 2 3
334934
2 2 5 2
1 4 4 3
2 1 6 3
1 2 3 8
2 3 6 1
```

### 输出

```
NO
YES
NO
```

# 题解

## 作者：引领天下 (赞：39)

这个题目其实很简单啊……看了一下题解基本上都做烦了，一个memcmp的水题，怎么还用到了什么线段树维护哈希？开玩笑。。。

注意到所有数字都在0~9之间，于是可以考虑把放在字符数组里，然后每次更新直接memcpy，查询memcmp。

然后就结束了？

上代码。

```cpp
#include<bits/stdc++.h>
char s[100100];
int main(){
    int n,m,k,l,r,c,i,f;
    scanf("%d%d%d%s",&n,&m,&k,s+1);//读入初始序列：直接转成char
    m+=k;
    for(i=0;i<m;i++){
        scanf("%d%d%d%d",&f,&l,&r,&c);
        if(f==1) memset(s+l,c+'0',r-l+1);//修改
        else puts(memcmp(s+l,s+l+c,r-l-c+1)?"NO":"YES");//查询
        //哪有那么烦？
    }
}
```

---

## 作者：子归 (赞：11)

## 线段树+Hash
听说这方法比不过暴力？（雾）
### 解题过程
#### 首先考虑第二个问题，如何快速求解一个子串是不是另一个串的循环节。  
此处有一个结论：    
假设 S 为 的长度为 n 。
只要判断 S[1…n-d+1] 和 S[d+1…n] 是否相等即可。  
简单的想，假设当前循环节是$k$，那么就有：  
$a$  
$a*ch+b$  
$a*ch^2+b*ch+c$  
$a*ch^3+b*ch^2+c*ch+d$  
$a*ch^4+b*ch^3+c*ch^2+d*ch+e$  
$a*ch^5+b*ch^4+c*ch^3+d*ch^2+e*ch+f$  
必从$k$个字母循环，假设$k=2$.那么就有:  
$a$  
$a*ch+b$  
$a*ch^2+b*ch+a$  
$a*ch^3+b*ch^2+a*ch+b$  
$a*ch^4+b*ch^3+a*ch^2+b*ch+a$  
$a*ch^5+b*ch^4+a*ch^3+b*ch^2+a*ch+b$  
发现前面两个和后面两个Hash值相等，再通过数学归纳法，可以证明。  
其实也很好想，因为我们要通过Hash[n]-Hash[n-d]相减来判断是不是s[0]-s[d]的多少$ch$倍，必须满足后面几个相等，因为只有是循环节，才能将前面的抵消掉。  
#### 第一个问题，如何处理赋值与Hash值之间的关系
一段的一段的赋值，查找也是一段一段的，很容易可以想到用线段树来维护一个Hash值。  
每个点存当前的Hash值，但是这里就有一个问题，因为是存的从$ch^0$开始的，那么怎么才能转移到父亲节点呢？  
```
kano[x].h=((kano[x<<1].h*Pow[kano[x<<1|1].rkano[x<<1|1].l+1]+kano[x<<1|1].h)%mod+mod)%mod;

```
左儿子里的值和他在父亲节点应当是的值差了什么呢？  
根据Hash函数的定义：$Hash(l,r)=Hash[r]-Hash[l-1]*p^{r-l+1}$
所以说，左儿子里的值就差了乘上一个$ch^{sizeof(rightson)}$  
这个问题解决了，那$pushdown$又该如何呢？  
```
void pushdown(int x){
	if(kano[x].lazy+1){
		kano[x<<1].lazy=kano[x<<1|1].lazy=kano[x].lazy;
		kano[x<<1].h=Pow2[kano[x<<1].r-kano[x<<1].l]*kano[x].lazy%mod;
		kano[x<<1|1].h=Pow2[kano[x<<1|1].r-kano[x<<1|1].l]*kano[x].lazy%mod;
		kano[x].lazy=-1;
	}
	return ;
}
```
$lazy$里存的是将要变成的值，那么如何将这些值赋到儿子中呢？  
可以看，在没有赋值前假设左儿子的值是:
$x*ch^3+y*ch^2+z*ch$，  
那么赋值之后就应该是:$k*ch^3+k*ch^2+k*ch$.
可以发现，就是在$k$的基础上$*$了一个$ch^3+ch^2+ch$,因此就可以同时维护一个$ch^x+xh^{x-1}+ch^{x-2}+……ch$的一个东西，就可以快速地$pushdown$。
#### 注意事项
1.有递归操作时，一定都下传$lazy$。  
2.注意边界。  
3.我每次修改时都将k加了1，防止0，$lazy$为-1，防止0的出现。
#### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int b=17;
const int N=1e5+50;
const int mod=1e9+9;
typedef unsigned long long ULL;
char s[N];
int n,m,opt,k,l,r;
ULL Pow[N],Pow2[N];
struct Kano{
	int l,r,lazy;
	ULL h;
}kano[N*6];
void pushup(int x){
	kano[x].h=((kano[x<<1].h*Pow[kano[x<<1|1].r-kano[x<<1|1].l+1]+kano[x<<1|1].h)%mod+mod)%mod;
}
void pushdown(int x){
	if(kano[x].lazy+1){
		kano[x<<1].lazy=kano[x<<1|1].lazy=kano[x].lazy;
		kano[x<<1].h=Pow2[kano[x<<1].r-kano[x<<1].l]*kano[x].lazy%mod;
		kano[x<<1|1].h=Pow2[kano[x<<1|1].r-kano[x<<1|1].l]*kano[x].lazy%mod;
		kano[x].lazy=-1;
	}
	return ;
}
void build(int x,int l,int r){
	kano[x].l=l;kano[x].r=r;kano[x].lazy=-1;
	if(l==r){
		kano[x].h=s[l]-'0'+1;
		return;
	}
	int mid=(kano[x].l+kano[x].r)>>1;
	build(x<<1,l,mid),build(x<<1|1,mid+1,r);
	pushup(x);
}
void add(int x,int l,int r,int a){
	if(kano[x].l==l&&kano[x].r==r){
		kano[x].lazy=a;
		kano[x].h=Pow2[kano[x].r-kano[x].l]*a%mod;
		return;
	}
	pushdown(x);
	int mid=(kano[x].l+kano[x].r)>>1;
	if(mid>=r) add(x<<1,l,r,a);
	else if(mid<l) add(x<<1|1,l,r,a);
	else add(x<<1,l,mid,a),add(x<<1|1,mid+1,r,a);
	pushup(x);
}
ULL query(int x,int l,int r){
	if(l>r) return 0;
	if(kano[x].l==l&&kano[x].r==r)
		return kano[x].h;
	pushdown(x);
	int mid=(kano[x].l+kano[x].r)>>1;
	if(mid>=r) return query(x<<1,l,r);
	else if(mid<l) return query(x<<1|1,l,r);
	else return (query(x<<1,l,mid)*Pow[r-mid]+query(x<<1|1,mid+1,r))%mod;
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	m+=k;
	scanf("%s",s+1);
	Pow[0]=Pow2[0]=1;
	for(int i=1;i<=n;i++) Pow[i]=Pow[i-1]*b%mod,Pow2[i]=(Pow2[i-1]*b+1)%mod;
	build(1,1,n);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d%d",&opt,&l,&r,&k);
		if(opt==1) add(1,l,r,k+1);
		else printf("%s\n",query(1,l,r-k)==query(1,l+k,r)?"YES":"NO");
	}
}
```

听说这东西打起来很爽，调起来更爽.(雾)

---

## 作者：FriedrichC (赞：7)

[洛谷题面](https://www.luogu.com.cn/problem/CF580E)

[原题链接](https://codeforces.com/problemset/problem/580/E)

蒟蒻太笨看不懂大佬的题解，自己来写一发。

## 题意分析
首先，问题的导向性非常明显，既要判断循环节的存在性，又要支持区间操作，容易想到用**线段树维护哈希值**。

现在问题的关键在于，究竟怎样维护区间的哈希值，以及支持区间覆盖操作。

## 哈希值的处理
### 维护
首先，既然我们要使用线段树，每一个节点当然是维护对应区间的哈希值，

但是，子节点更新父节点信息的方式不再是简单的加和。

让我们来回顾一下字符串哈希的过程：

```cpp
ull hassh(char* s)
{
	ull ans=0;
	for(int i=1;i<=len;++i)
		ans=ans*p+s[i];
	return ans;
}
```

代码大概长这样，其中 $p$ 为某个基数。

我们通常哈希的过程，是**从左往右**哈希，在遍历到每个字符的位置时，先将前缀的哈希值乘上基数，再加上当前字符自身的权值。

如果把某个前缀的哈希值展开来看，大致可以得到这样一个式子：

$p^{i-1}\cdot s[1]+p^{i-2}\cdot s[2]+\dots +s[i]$

可以发现，这个表达式是一个关于 $p$ 的多项式，对于每一个字母，其乘上的 $p$ 的幂的大小，即系数，与其在字符串中的**位置**密切相关。

这启示我们，将两段字符串的哈希值**简单相加**绝**不等于**二者**拼接**而成的字符串的哈希值，

因为在拼接成的新串之中，**原来两串中字母的相对位置的改变，会引起其在新串的哈希值表达式中对应系数的改变**。

那么，若我们要将左右区间的哈希值合并该怎么做呢？

首先，左区间的每一个字符**合并后**对应的系数一定大于右区间的每一个字符，

因为正常的哈希顺序从左往右，越先处理的字母在往后的过程中乘上基数的次数就越多，从先前的表达式中也可以看出这一点。

左右区间合并之后，对于左区间，相当于在其后添加了一个**右区间长度**（记为 $len$）的**后缀**，

那么假如我们从左区间末端开始，继续进行哈希的过程，左区间的字符每次都会多乘一个基数，

不难证明，左区间的每一个字符总共会再**乘上** $p^{len}$，而右区间的字符等效于相对位置**不变**，系数自然不变。

因此，线段树 `pushup` 的操作大概长这样：

```cpp
void pushup(int p)
{
    h(p)=(h(p<<1)*pw[r(p<<1|1)-l(p<<1|1)+1]%mod+h(p<<1|1))%mod;
}
```
### 更新
维护的问题终于解决了，那么我们的覆盖操作呢？

还是再回看哈希的表达式，

$p^{i-1}\cdot s[1]+p^{i-2}\cdot s[2]+\dots +s[i]$

区间覆盖相当于把某部分的所有字符替换为同一字符，即：

$p^{i-1}\cdot ch+p^{i-2}\cdot ch+\dots +ch$

计算和原哈希值的差量来更新显然不现实，但是新的这段哈希值就等于 $ch$ 乘上 $p$ 的**幂的前缀和**，在预处理 $p$ 的幂时顺便处理前缀和即可。

而计算时具体取长度为多少的前缀和显然也与区间长度有关，显然，对于一个长度为 $len$ 的区间，我们要取的前缀和为 $p^{len-1}+p^{len-2}+\dots+1$。

### 查询
在查询每一段哈希值时还要注意一个细节，在线段树的写法上，我们要把查询区间是否把左右节点**单独覆盖**分开讨论，

假如并不是单独覆盖，而是覆盖部分存在**相交**，此时就要相当于要把左右区间的哈希值**合并**了，于是要给左节点的查询结果乘上新的系数。

代码大概长这样：

```cpp
ull ask(int p,int l,int r)
{
    if(l>r)return 0;
    if(l<=l(p)&&r>=r(p))return h(p);
    spread(p);
    int mid=(l(p)+r(p))>>1;
    if(mid>=r)return ask(p<<1,l,r)%mod;
    else if(mid<l)return ask(p<<1|1,l,r)%mod;
    else return (ask(p<<1,l,mid)*pw[r-(mid+1)+1]%mod+ask(p<<1|1,mid+1,r))%mod;
}
```

也可以是这样：

```cpp
ull ask(int p,int l,int r)
{
    if(l>r)return 0;
    if(l<=l(p)&&r>=r(p))return h(p);
    spread(p);
    int mid=(l(p)+r(p))>>1;
    if(l<=mid&&r>mid)return (ask(p<<1,l,mid)*pw[r-(mid+1)+1]%mod+ask(p<<1|1,mid+1,r))%mod;
    else
    {
        if(l<=mid)return ask(p<<1,l,r)%mod;
        else if(r>mid)return ask(p<<1|1,l,r)%mod;
    }
}
```

## 循环节的查询
终于到了最后的问题，如何查询循环节。

许多题解都提到了这样一个结论：

若长度为 $n$ 的字符串 $s$ 存在长为 $k$ 的循环节，则有 $s[1+k,n]=s[1,n-k]$。

现用直观而简单的方法证明这点。

首先，题目中对于存在长度为 $k$ 的循环节的定义是：$\forall i\in [1,n-k],s_i=s_{i+k}$。

（ps：翻译中没有，请看原题面。）

现在我们把两份**相同字符串** $s$ 错开 $k$ 个单位**对齐**，那二者的**交集**就分别为 $s[1+k,n]$ 和 $s[n-k,n]$。

![](https://cdn.luogu.com.cn/upload/image_hosting/bh4o9x50.png)


如图，我们用**下标代替字母**，为了方便说明，记上面的字符串为 $s_1$，下面的为$s_2$，其实本质是**同一个字符串**。

以 $k=2$ $n=8$ 为例，$s_1[3,8]$ 即 $s[1+k,n]$，$s_2[1,6]$ 即 $s[1,n-k]$。

根据循环节的定义，我们有 $s_1[1,2]=s_1[3,4]$，又 $s_1[1,2]=s_2[1,2]$，则 $s_1[3,4]=s_2[1,2]$。

同理，我们可以继续证明 $s_1[5,6]=s_2[3,4]$ ，以此类推，最终会证明 $s[1+k,n]=s[1,n-k]$。

推广到一般的情况，不难发现 $s[1,k]=s[k+1,2k]=s[2k+1,3k]=\dots =s[n-2k+1,n-k]$，


也就是从 $1$ 开始的相邻 $k$ 长段都相等，那么，我们同样只需要将两个 $s$ 错开 $k$ 位对齐，

**由于相邻 $k$ 长段相等，错位之后原先相邻段就变成上下对齐，上下对齐的部分都相等，自然有 $s[1+k,n]=s[1,n-k]$ 成立**。

这个证明思路和 KMP 算法求字符串循环元算法的证明思路基本一致，可以参阅蓝书。

了解了这个结论之后，每次询问操作，我们只要查询区间 $[l,r-d]$ 和 $[l+d,r]$ 是否相等即可。

## 附上代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define maxn 100010
using namespace std;
typedef unsigned long long ull;
const int mod=1e9+9;
const int p=1331;
int n,m,k;
char a[maxn];
ull pw[maxn],pre[maxn];//pw存储p的幂，pre为pw的前缀和
struct seg_tree{
    int l,r,tag;//tag的意义是标记区间覆盖操作的覆盖值
    ull h;
    #define l(x) tree[x].l
    #define r(x) tree[x].r
    #define tag(x) tree[x].tag
    #define h(x) tree[x].h
}tree[maxn<<2];
void pushup(int p)
{
    h(p)=(h(p<<1)*pw[r(p<<1|1)-l(p<<1|1)+1]%mod+h(p<<1|1))%mod;
}
void build(int p,int l,int r)
{
    l(p)=l,r(p)=r,h(p)=0,tag(p)=-1;
    if(l==r){h(p)=a[l]-'0';return;}//记得转成数字大小，因为tag是数字
    int mid=(l+r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    pushup(p);
}
void spread(int p)
{
    if(tag(p)!=-1)
    {
        tag(p<<1)=tag(p<<1|1)=tag(p);
        h(p<<1)=tag(p)*pre[r(p<<1)-l(p<<1)]%mod;
        h(p<<1|1)=tag(p)*pre[r(p<<1|1)-l(p<<1|1)]%mod;
        tag(p)=-1;
    }
}
void change(int p,int l,int r,int d)
{
    if(l<=l(p)&&r>=r(p))
    {
        h(p)=d*pre[r(p)-l(p)]%mod;
        tag(p)=d;
        return;
    }
    spread(p);
    int mid=(l(p)+r(p))>>1;
    if(l<=mid)change(p<<1,l,r,d);
    if(r>mid)change(p<<1|1,l,r,d);
    pushup(p);
}
ull ask(int p,int l,int r)
{
    if(l>r)return 0;
    if(l<=l(p)&&r>=r(p))return h(p);
    spread(p);
    int mid=(l(p)+r(p))>>1;
    if(l<=mid&&r>mid)return (ask(p<<1,l,mid)*pw[r-(mid+1)+1]%mod+ask(p<<1|1,mid+1,r))%mod;
    else
    {
        if(l<=mid)return ask(p<<1,l,r)%mod;
        else if(r>mid)return ask(p<<1|1,l,r)%mod;
    }
}
signed main()
{
    cin>>n>>m>>k>>a+1;
    pw[0]=pre[0]=1;
    for(int i=1;i<=n;++i)
    {
        pw[i]=pw[i-1]*p%mod;
        pre[i]=(pre[i-1]+pw[i])%mod;
    }
    build(1,1,n);
    int t=m+k;
    while(t--)
    {
        int op,l,r,x;
        cin>>op>>l>>r>>x;
        if(op==1)change(1,l,r,x);
        else
        {
            if(ask(1,l,r-x)==ask(1,l+x,r))puts("YES");
            else puts("NO");
        }
    }
	return 0;
}

```

## 其他细节
- 由于覆盖操作的覆盖值存在 $0$，所以懒标记初始化为 $-1$。

- 初始化叶节点哈希值时需要将字符转成其数字大小，因为懒标记存储的值是数字而不是字符，否则每次都需要将字符转成数字，十分不便。

- 本人亲测这题确实卡自然溢出，为了保险起见，最好选择一个模数 $mod$。
















---

## 作者：顾z (赞：4)

> ### Description
>
> $n$个数的字符串，$m + k$个操作
>
> `1 l r k`把$l - r$赋值为$k$
>
> `2 l r d`询问$l - r$是否有长度为$d$的循环节
>
> $n \leq 10^5, m + k \leq 10^5, d \leq 10$
>
> ### Input
>
> 第一行为三个整数$n,m,k$
>
> 第二行为一个$n$个数的字符串。
>
> 接下来$m+k$行每行对应一种操作。
>
> ### Output
>
> 对于每一个$2$操作,如果存在,输出一行$YES$，否则输出$NO$

**线段树维护哈希**

~~写起来爽,调起来更爽~~

我们首先**预处理出$po$数组记录$base^i$(这个要用来修改及查询的。)**

**还要预处理出来$val[i][j]$代表长度为$j$的全部为数字$i$的字符串的哈希值。**

然后每次区间合并的时候.

$$len=tr[rs].r-tr[rs].l+1$$

$$tr[o].va=(tr[ls].va\times po[len] \% mod +tr[rs].va) \% mod$$

这个应该不是很难理解吧。(就类似于你$hash$匹配的做法。)

修改时候,我们直接赋值$tr[o].va=val[k][len]$即可。

需要**注意**的有两点：

1. $lazy$标记初值要为$1$,因为会存在赋值为$0$的情况
2. 查询操作中,当前区间分别在左右两侧的时候$tr[ls].va \times po[r-mid]$！！

因此直接码代码就好了

还有一个**神仙结论**是做题的根据。

> **如果询问为$(l,r,d)$,则只需要判断$(l+d,r)$和$(l,r-d)$即可。**

证明的话,我不太会.但是这是正确的。

如果这题卡单$hash$的话可以写双$hash$。稍作修改即可。不多$BB$了.

``代码``

```c++
#include<cstdio>
#include<algorithm>
#include<iostream>
#define lo long long
#define base 31
#define mod 20020303
#define R register

using namespace std;

const int gz=1e5+8;

inline void in(R int &x)
{
    int f=1;x=0;char s=getchar();
    while(!isdigit(s)){if(s=='-')f=-1;s=getchar();}
    while(isdigit(s)){x=x*10+s-'0';s=getchar();}
    x*=f;
}

int n,m,K,po[gz]={1},val[10][gz];

char s[gz];

struct wc
{
    int l,r,tg;
    lo va;
}tr[gz<<2];

inline void pre()
{
    for(R int i=1;i<gz;i++)
        po[i]=po[i-1]*base%mod;
    for(R int i=0;i<10;i++)
        for(R int j=1;j<gz;j++)
            val[i][j]=(val[i][j-1]*base%mod+i)%mod;
}

#define ls o<<1
#define rs o<<1|1

inline void up(R int o)
{
    tr[o].va=(tr[ls].va*po[tr[rs].r-tr[rs].l+1]%mod+tr[rs].va%mod)%mod;
}

void build(R int o,R int l,R int r)
{
    tr[o].l=l,tr[o].r=r;tr[o].tg=-1;
    if(l==r)
    {
        tr[o].va=s[l]-'0';
        return;
    }
    R int mid=(l+r)>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    up(o);
}

inline void down(R int o)
{
    if(tr[o].tg==-1)return;
    R int k=tr[o].tg;
    tr[ls].va=val[k][tr[ls].r-tr[ls].l+1];
    tr[rs].va=val[k][tr[rs].r-tr[rs].l+1];
    tr[ls].tg=tr[rs].tg=k;
    tr[o].tg=-1;
}

void change(R int o,R int l,R int r,R int k)
{
    if(tr[o].l==l and tr[o].r==r)
    {
        tr[o].tg=k;
        tr[o].va=val[k][tr[o].r-tr[o].l+1];
        return ;
    }
    down(o);
    R int mid=(tr[o].l+tr[o].r)>>1;
    if(r<=mid)change(ls,l,r,k);
    else if(l>mid)change(rs,l,r,k);
    else change(ls,l,mid,k),change(rs,mid+1,r,k);
    up(o);
}

lo query(R int o,R int l,R int r)
{
    if(tr[o].l==l and tr[o].r==r)return tr[o].va;
    down(o);
    R int mid=(tr[o].l+tr[o].r)>>1;
    if(r<=mid)return query(ls,l,r);
    else if(l>mid) return query(rs,l,r);
    else
        return ((query(ls,l,mid)%mod)*po[r-mid]%mod+query(rs,mid+1,r)%mod)%mod;//注意这里！！
}

int main()
{
    pre();
    in(n),in(m),in(K);
    R int tt=m+K;
    scanf("%s",s+1);
    build(1,1,n);
    for(R int opt,l,r,k;tt;tt--)
    {
        in(opt),in(l),in(r),in(k);
        switch(opt)
        {
            case 1:change(1,l,r,k);break;
            case 2:
            {
                if(r-l+1==k)
                {
                    puts("YES");
                    continue;
                }
                puts(query(1,l,r-k)==query(1,l+k,r) ? "YES":"NO");
                break;
            }
        }
    }
}
```



---

## 作者：attack (赞：4)

首先有个神仙结论：若询问区间为$(l, r, d)$，则只需判断$(l + d, r)$和$(l, r - d )$是否相同

证明可以用归纳法。

然后线段树维护一下字符串hash值，维护一个区间覆盖的标记就好了

注意赋值的时候有$0$的情况，因此开始的标记不能为$0$

```cpp
#include<cstdio>
#include<algorithm>
#define int long long 
#define LL long long 
#define ull long long 
using namespace std;
const int MAXN = 1e6 + 10;
const double eps = 1e-9;
inline int read() {
    char c = getchar(); int x = 0, f = 1;
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
int N, M, K;
char s[MAXN];
struct Segment {
	ull sum[MAXN], po[MAXN], seed, mod;
	#define ls k << 1
	#define rs k << 1 | 1
	struct Node {
		int l, r, siz;
		ull ha, f;
	}T[MAXN];
	void update(int k) {
		T[k].ha = (T[ls].ha % mod + po[T[ls].siz] * T[rs].ha % mod) % mod;
	}
	void ps(int k, int son) {
		T[son].f = T[k].f;
		T[son].ha = sum[T[son].siz - 1] * T[son].f % mod;
	}
	void pushdown(int k) {
		if(T[k].f == -1) return ;
		ps(k, ls); ps(k, rs);
		T[k].f = -1;
	}
	void Build(int k, int ll, int rr) {
		T[k] = (Node) {ll, rr, rr - ll + 1, 0, -1};
		if(ll == rr) {
			T[k].ha = s[ll] - '0'; 
			return ;
		}
		int mid = T[k].l + T[k].r >> 1;
		Build(ls, ll, mid); Build(rs, mid + 1, rr);
		update(k);
	}
	void IntervalChange(int k, int ll, int rr, ull val) {
		if(ll <= T[k].l && T[k].r <= rr) {
			T[k].f = val % mod; 
			T[k].ha = sum[T[k].siz - 1] * val % mod;
			return ;
		}
		pushdown(k);
		int mid = T[k].l + T[k].r >> 1;
		if(ll <= mid) IntervalChange(ls, ll, rr, val);
		if(rr >  mid) IntervalChange(rs, ll, rr, val);
		update(k);
	}
	ull IntervalQuery(int k, int ll, int rr) {
		if(ll > rr) return 0;
		if(ll <= T[k].l && T[k].r <= rr) return T[k].ha % mod;
		pushdown(k);
		int mid = T[k].l + T[k].r >> 1;
		if(ll > mid) return IntervalQuery(rs, ll, rr) % mod;
		else if(rr <= mid) return IntervalQuery(ls, ll, rr) % mod;
		else return (IntervalQuery(ls, ll, rr) % mod + po[mid - max(T[k].l, ll) + 1] * IntervalQuery(rs, ll, rr) % mod) % mod;
	}
	void work() {
		po[0] = 1; sum[0] = 1;
		for(int i = 1; i <= N; i++) po[i] = po[i - 1] * seed % mod, sum[i] = (sum[i - 1] + po[i]) % mod;	
		Build(1, 1, N);
	}
	int Query(int l, int r, int k) {
		return IntervalQuery(1, l, r - k) == IntervalQuery(1, l + k, r);
	}
}Se[2];

main() {
	Se[0].seed = 27; Se[0].mod = 1e9 + 7;
	Se[1].seed = 233; Se[1].mod = 1e9 + 9;
	N = read(); M = read(); K = read();
	scanf("%s", s + 1);
	Se[0].work(); Se[1].work();
	for(int i = 1; i <= M + K; i++) {
		int opt = read(), l = read(), r  = read(), k = read();
		if(opt == 1) Se[0].IntervalChange(1, l, r, k), Se[1].IntervalChange(1, l, r, k);
		else {
			if((r - l + 1) == k) {
				puts("YES"); 
				continue;
			}
			puts((Se[0].Query(l, r, k) && Se[1].Query(l, r, k))? "YES" : "NO");
		}
	}
	return 0;
}

```

---

## 作者：yeshubo_qwq (赞：3)

## Solution

操作 $1$ 使用 memset 函数，很简单。

操作 $2$ 有一个结论：比较 $s_{l...r-d}$ 和 $s_{l+d,r}$ 即可。

易证，此处略。

可以使用 memcmp 函数。

memcmp 函数原型：

```cpp
int memcmp(const void *str1, const void *str2, size_t n);
```

功能：用于比较 $str1$ 的前 $n$ 位和 $str2$ 的前 $n$ 位。

返回值：若前者小，返回值 $<0$；若两者相等，返回值 $=0$；若前者大，返回值 $>0$。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,Q1,Q2,op,l,r,x;
char c,s[100005];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>Q1>>Q2>>s+1;
	for (int T=Q1+Q2; T--;){
		cin>>op>>l>>r;
		if (op==1) cin>>c,memset(s+l,c,r-l+1);
		else cin>>x,cout<<(memcmp(s+l,s+l+x,(r-l+1)-x)?"NO\n":"YES\n");
	}
	return 0;
}
```

---

## 作者：MrPython (赞：2)

一道紫色的大水题。

正解线段树维护哈希值，但是对于不会的人来说，暴力也可行！

具体地，STL 大法。使用 `vector<char>` 存储原数组（`string` 也可以）。对于操作 `1`，直接用 `std::fill` 进行区间赋值；对于操作 `2`，用 `std::equal` 判断 $2$ 个区间是否相等。

操作 `1`，`2` 都是 $O(n)$ 的，时间复杂度如此炸裂，为什么还能通过呢？

在古老的 C 语言中有一些库函数，专门处理内存的相关操作，例如 `memset`、`memcpy`、`memcmp` 等。它们都在汇编层面进行过优化，虽然时间复杂度还是 $O(n)$，但是常数被优化到极小。在 C++ 中，它们被对迭代器更友好的相关函数替代，但是在许多情况下仍会被编译器优化。因此，这些 STL 函数的常数较小，再加上数据较水，可以通过本题。
```cpp
#include<bits/extc++.h>
using namespace std;
namespace pbds=__gnu_pbds;
using ui=unsigned int;
using uli=unsigned long long int;
using li=long long int;
int main(void){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    size_t n,m,k;
    cin>>n>>m>>k;
    vector<char> s(n);
    for (char& i:s) cin>>i;
    for (size_t i=0;i<m+k;++i){
        char op;size_t l,r;
        cin>>op>>l>>r;--l;
        if (op=='1'){
            char c;
            cin>>c;
            fill(s.begin()+l,s.begin()+r,c);
        }else{
            size_t d;
            cin>>d;
            cout<<(equal(s.begin()+l,s.begin()+r-d,s.begin()+l+d)?"YES\n":"NO\n");
        }
    }
    return 0;
}
```

---

## 作者：Mars_Dingdang (赞：2)

写了好久线段树+哈希，结果发现还不如暴力？

## 题目大意
给定一个长度为 $n$ 的字符串，每个元素均为数字，然后有 $m+k$ 次操作，支持将区间 $[l, r]$ 整体赋值，以及查询区间 $[l, r]$ 是否有长度为 $d$ 的循环节。

## 大体思路
很容易想到字符串哈希 + 线段树。

设哈希的进制数为 $base$，模数为 $M$，则前缀哈希值
$H_i=H_{i-1}\times base+s_i\pmod M$。接下来作为哈希基本功，预处理出 $p_i=base^i$。这样区间 $[l, r]$ 的哈希值可以通过前缀哈希值用以下方法求出：
$$Hash(l, r)=H_r-H_{l-1}\times p_{r-l+1}$$

由于整体赋值时将区间 $[l,r]$ 赋值为 $v$ 相当于这一段的哈希值变为
$$\sum_{i=0}^{r-l}v\times base^i=v\times \sum_{i=0}^{r-l}p_i$$
考虑预处理出数组 $sp_i=\sum_{j=0}^{i-1}base^j=sp_{i-1}+p_{i-1}$ 用以记录上式中 $\Sigma$ 的部分，这样区间修改可以由懒标记完成。

下面给出一份有关上述实现的代码，但代码中使用 `ull` 代替模数的方式会被卡，因此实际提交时需要修改。

```cpp
	struct node {
		int ls, rs, l, r, len, tag; // 左右儿子，维护区间及长度，懒标记
		ull h1, h2; // 双哈希，偷懒用ull做模数，但会被卡
		#define ls(u) tr[u].ls
		#define rs(u) tr[u].rs
		#define L(u) tr[u].l
		#define R(u) tr[u].r
	} tr[maxn * 2];
	inline void init() {
		tr[1] = {0, 0, 1, n, n, 0, 0, 0};
		sp[0] = 0, p[0] = p2[0] = 1ull;
		rep(i, 1, n) p[i] = p[i - 1] * base, p2[i] = p2[i - 1] * base2;
		rep(i, 1, n) sp[i] = sp[i - 1] + p[i - 1], sp2[i] = sp2[i - 1] + p2[i - 1];
	}
	inline void pushup(int u) { // 有子树计算父节点
		tr[u].h1 = tr[rs(u)].h1 + tr[ls(u)].h1 * p[tr[rs(u)].len];
		tr[u].h2 = tr[rs(u)].h2 + tr[ls(u)].h2 * p2[tr[rs(u)].len];
	}
	inline void Upd(int u, int v) { // 修改
		tr[u].tag = v;
		tr[u].h1 = v * sp[tr[u].len];
		tr[u].h2 = v * sp2[tr[u].len];
	}
	inline void pushdown(int u) { // 标记下放
		if(tr[u].tag == 0) return;
		Upd(ls(u), tr[u].tag);
		Upd(rs(u), tr[u].tag);
		tr[u].tag = 0;
	}
	inline void build(int u, int l, int r) { // 建树
		if(l == r) {
			tr[u] = {0, 0, l, r, 1, 0, (ull)(a[l] ^ 48), (ull)(a[l] ^ 48)};
			return;
		}
		tr[u] = {0, 0, l, r, r - l + 1, 0, 0, 0};
		ls(u) = ++nSeg; rs(u) = ++nSeg;
		int mid = (l + r) >> 1;
		build(ls(u), l, mid);
		build(rs(u), mid + 1, r);
		pushup(u);
	}
	inline ull H1(int u, int l, int r) { // 哈希1
		if(l > R(u) || r < L(u)) return 0;
		pushdown(u);
		if(l <= L(u) && r >= R(u))	
			return tr[u].h1 * p[r - R(u)]; // 根据位值原理求出这一段哈希值对整体的贡献
		return H1(ls(u), l, r) + H1(rs(u), l, r);
	}
	inline ull H2(int u, int l, int r) { // 哈希2
		if(l > R(u) || r < L(u)) return 0;
		pushdown(u);
		if(l <= L(u) && r >= R(u))	
			return tr[u].h2 * p2[r- R(u)];
		return H2(ls(u), l, r) + H2(rs(u), l, r);
	}
	inline void change(int u, int l, int r, int v) {
		if(l > R(u) || r < L(u)) return;
		if(l <= L(u) && r >= R(u)) {
			Upd(u, v);
			return;
		}
		pushdown(u);
		change(ls(u), l, r, v);
		change(rs(u), l, r, v);
		pushup(u);
	}
```
然后，我们能在单次 $O(\log n)$ 的复杂度内实现区间赋值、区间查询操作。对于判断 $[l, r]$ 是否存在长度为 $d$ 的循环节，考虑学习 KMP 时对于将 $n-p_n$ 作为最短循环节的证明方式，这里只需判断 $[l+d, r]$ 与 $[l, r-d]$ 是否相等即可。若这两段错位相等，则可归纳证明长度为 $d$ 的循环节存在。判断相等可利用哈希，复杂度 $O(\log n)$。

```cpp
	if(op == 1) change(1, l, r, d);
	else{
		if(d == r - l + 1) puts("YES");
		else (H1(1, l + d, r) == H1(1, l, r - d) && H2(1, l + d, r) == H2(1, l, r - d) ? puts("YES") : puts("NO"));
	} 
```

其实，本题还有一种更为直接暴力且吊打线段树的方法。利用字符串函数 `memset` 和 `memcmp` 的极高效率，可以直接实现区间赋值和区间查询。

```cpp
	if(op == 1) memset(s + l, d + '0', r - l + 1);
	else puts(memcmp(s + l, s + l + d, r - l + 1 - d) ? "NO" : "YES");
```

---

## 作者：QianianXY (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF580E)

## 前置知识
- 线段树
- 哈希

## 题目分析

线段树维护哈希经典题，其实也只是换汤不换药的线段树基本操作罢了。

定义 $v_k$ 表示区间 $k$ 的哈希值，$len_k$ 表示区间 $k$ 的长度。

定义基数为 $bas$，先预处理 $pw_i$ 为 $bas^i$。

题目中操作二为区间统一赋值。

对于线段树中区间 $k$，端点为 $l,r$，暴力修改哈希值，实现如下，复杂度为线性：

```cpp
for (rei i = l; i <= r; i++)
	v[k] = (v[k] * bas + num) % mod;
```

而我们预处理 $pw2_i$ 为 $bas^i$ 在 $bas$ 进制中每一位都为 $1$ 的值。

则显然修改可优化为 $O(1)$：

```cpp
v[k] = pw2[r - l] * num % mod;
```

那已知左右儿子（$ls,rs$）的哈希值，又如何转换为父亲的哈希值呢（上传操作）？这里给出公式：

$$ v_k=v_{ls}\times pw_{len_{rs}}+v_{rs} $$

意义为在 $bas$ 进制下，$v_{ls}$ 向左移动 $len_{rs}$ 位，再加上 $v_{rs}$。

下传就很简单了，使用上述的 $O(1)$ 修改方法即可。

建议用结构体捆绑 $v,len$，但不要捆绑 $l,r$，方便调试。

最后有一个显然的结论：若 $v_{i...j-d}=v_{i+d...j}$，则 $l-r$ 有长度为 $d$ 的循环节。

数学归纳法易证。

给出一个需要转化，但本质相同的题：[CF452F](https://www.luogu.com.cn/problem/CF452F)
## code

截止发文时，在为数不多的提交中位居最优解第一页~~QwQ~~。

```cpp
#include <bits/stdc++.h>
#define rei register int
#define N 200010
#define ls k<<1
#define rs k<<1|1
using namespace std;
typedef long long ll;
const ll bas = 23, mod = 1e9 + 7;

template <typename T> inline void read(T &x)
{
	x = 0; T f = 1; char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -f; ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + ch - 48; ch = getchar();}
	x *= f;
}

struct Tree {ll v, len;} T[N << 2];
ll n, m1, m2, pw[N], len[N], v[N], f[N], pw2[N], str[N];

inline Tree merge(Tree l, Tree r)
{
	Tree ret;
	ret.v = (l.v * pw[r.len] % mod + r.v) % mod;
	ret.len = l.len + r.len;
	return ret;
}

inline void Pushup(ll k) {T[k] = merge(T[ls], T[rs]);}

inline void Pushdown(ll k)
{
	if (f[k] == -1) return;
	T[ls].v = pw2[T[ls].len - 1] * f[k] % mod;
	T[rs].v = pw2[T[rs].len - 1] * f[k] % mod;
	f[ls] = f[rs] = f[k];
	f[k] = -1;
}
 
inline void Build(ll k, ll l, ll r)
{
	T[k].len = r - l + 1; T[k].v = 0;
	if (l == r) 
	{
		T[k].v = str[l] % mod;
		return;
	}
	ll mid = l + r >> 1;
	Build(ls, l, mid);
	Build(rs, mid + 1, r);
	Pushup(k);
}

inline void Update(ll k, ll l, ll r, ll x, ll y, ll d)
{
	if (x <= l && r <= y)
	{
		f[k] = d;
		T[k].v = pw2[r - l] * d % mod;
		return;
	}
	Pushdown(k); ll mid = l + r >> 1;
	if (x <= mid) Update(ls, l, mid, x, y, d);
	if (mid < y) Update(rs, mid + 1, r, x, y, d);
	Pushup(k);
}

inline Tree Query(ll k, ll l, ll r, ll x, ll y)
{
	if (x <= l && r <= y) return T[k];
	Pushdown(k); ll mid = l + r >> 1;
	if (x <= mid && mid < y) return merge(Query(ls, l, mid, x, y), Query(rs, mid + 1, r, x, y));
	if (x <= mid) return Query(ls, l, mid, x, y);
	if (mid < y) return Query(rs, mid + 1, r, x, y);
}

int main()
{
	read(n); read(m1); read(m2);
	for (rei i = 1; i <= n; i++)
	{
		char c; scanf("%c", &c);
		str[i] = c - '0';
	}
	pw[0] = pw2[0] = 1;
	for (rei i = 1; i <= 2e5; i++) pw[i] = pw[i - 1] * bas % mod, pw2[i] = (pw2[i - 1] * bas % mod + 1) % mod;
	Build(1, 1, n); memset(f, -1, sizeof(f));
	for (rei i = 1; i <= m1 + m2; i++)
	{
		ll opt, x, y, d; read(opt); read(x); read(y); read(d);
		if (opt == 1) Update(1, 1, n, x, y, d);
		else 
		{
			if (d >= y - x + 1) printf("YES\n");
			else printf("%s\n", Query(1, 1, n, x, y - d).v == Query(1, 1, n, x + d, y).v ? "YES" : "NO");
		}
	}
	return 0;
}
```


---

## 作者：IOI_AK_LHY (赞：0)

## 前言

[题目传送门](https://www.luogu.com.cn/problem/CF580E)。

[在博客内食用效果更佳](https://www.luogu.com.cn/blog/lihangyu-749988/solution-cf580e)！

## 题目分析

蒟蒻看到大佬们的线段树+哈希，完全看不懂……但是回头再看一眼题面，我惊喜地发现，完全不用那么复杂！这里我将给你讲解题目中的两种操作如何实现。

### 第一种操作

一看到“赋值”两个字，我就想起了C++中的自带函数--- `memset` 。

`memset` 介绍 :

这个函数可以将一个值赋值给数组或字符串中一部分连续的变量。

这个函数在头文件 `#include<cstring>` 里面。

使用方法与格式如下：

`memset(` 开头 `，` 结尾 `，` 要赋的值 `)`

示例代码：

```cpp
int a[105];
memset(a,a+100,1);
```

这段代码将 `a[0],a[1],`……`,a[99]` 赋值为了1。

### 第二种操作

题目要求找到字符串中的循环节，于是我们知道肯定要将两个字符串进行对比，才能得到结果。

这时候， C++ 帮了我们一个大忙。 C++ 中有一个自带函数--- `memcmp` 。

`memcmp` 介绍：

这个函数是用来对比两个字符串的前几位的大小的，能够帮助我们很快地实现一些看似很复杂的问题。

这个函数也在头文件 `#include<cstring>` 里面。

使用方法与格式如下：

`memcmp(` 第一个字符串 `,` 第二个字符串 `,` 一个长度 `)`

返回值：若前一个字符串的前 `n` 位小于后一个字符串的前 `n` 位，则返回值 $<0$ ，若两段字符串相等，返回 $0$ ，若前一个字符串的前 `n` 位大于后一个字符串的前 `n` 位，则返回值 $>0$ 。

示例代码：

```cpp
string s1="I love luogu";
string s2="I love c++";
cout<<memcmp(s1,s2,8);
```

这段代码将两个字符串的前 $8$ 位进行了大小比较，即比较了 `I love l` 和`I love c` 两个子字符串。返回值 $>0$ 。

按照这样的思路，整个代码很快就可以写出来。

## 代码实现

```cpp
#include<iostream>
#include<string.h>
using namespace std;
const int N=114514;
int n,m,k,l,r,c,flag;
char ch[N];
int main(){
    cin>>n>>m>>k>>ch+1;
    for(int i=1;i<=m+k;i++){
        cin>>flag>>l>>r>>c;
        if(flag==1)
			memset(ch+l,c+48,r-l+1);
        else
        	if(memcmp(ch+l,ch+l+c,r-l-c+1))
        		cout<<"NO"<<endl;
        	else
        		cout<<"YES"<<endl;
    }
    return 0;
}
```

题解制作不易，希望能够帮助到大家！

---

