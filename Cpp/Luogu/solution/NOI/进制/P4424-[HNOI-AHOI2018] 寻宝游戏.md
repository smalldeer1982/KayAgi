# [HNOI/AHOI2018] 寻宝游戏

## 题目描述

某大学每年都会有一次 Mystery Hunt 的活动，玩家需要根据设置的线索解谜，找到宝藏的位置，前一年获胜的队伍可以获得这一年出题的机会。

作为新生的你，对这个活动非常感兴趣。你每天都要从西向东经过教学楼一条很长的走廊，这条走廊是如此的长，以至于它被人戏称为 infinite corridor。一次，你经过这条走廊时注意到在走廊的墙壁上隐藏着 $n$ 个**等长的**二进制的数字，长度均为 $m$。你从西向东将这些数字记录了下来，形成一个含有 $n$ 个数的二进制数组 $a_1,a_2,...,a_n$。

很快，在最新的一期的 Voo Doo 杂志上，你发现了 $q$ 个长度也为 $m$ 的二进制数 $r_1,r_2,...,r_q$。

聪明的你很快发现了这些数字的含义。

保持数组 $a_1,a_2,...,a_n$ 的元素顺序不变，你可以在它们之间插入 $\land$（按位与运算）或者 $\lor$（按位或运算）。例如：$11011\land 00111=00011$，$11011\lor 00111=11111$。

你需要插入 $n$ 个运算符，相邻两个数之前恰好一个，在**第一个数的左边**还有一个。**如果我们在第一个运算符的左边补入一个 0**，这就形成了一个运算式，我们可以计算它的值。与往常一样，运算顺序是**从左到右**。有趣的是，出题人已经告诉你这个值的可能的集合—— Voo Doo 杂志里的那些二进制数 $r_1,r_2,...,r_q$，而解谜的方法，就是对 $r_1,r_2,...,r_q$ 中的每一个值 $r_i$，分别计算出**有多少种方法填入这 $n$ 个计算符**，使的这个运算式的值是 $r_i$。

然而，infinite corridor 真的很长，这意味着数据范围可能非常大。因此，答案也可能非常大，但是你发现由于谜题的特殊性，你只需要求答案模 $1000000007$ 的值。

## 说明/提示

对于 $10\%$ 的数据，$n \le 20, m \le 30, q = 1$；

对于另外 $20\%$ 的数据，$n \le 1000, m \le 16$；

对于另外 $40\%$ 的数据，$n \le 500, m \le 1000$；

对于全部的数据 $1\leq n\leq 1000,1\leq m\leq 5000,1\leq q\leq 1000$。

## 样例 #1

### 输入

```
5 5 1
01110
11011
10000
01010
00100
00100```

### 输出

```
6```

## 样例 #2

### 输入

```
10 10 3
0100011011
0110100101
1100010100
0111000110
1100011110
0001110100
0001101110
0110100001
1110001010
0010011101
0110011111
1101001010
0010001001```

### 输出

```
69
0
5```

# 题解

## 作者：Kelin (赞：43)

## [题意](https://blog.csdn.net/BeNoble_/article/details/80083151)

给你$n$个长度为$m$的$01$串

你可以在每个串前面加一个运算符$\land$或$\lor,$分别表示$and$和$or$运算

每次询问一个长度为$m$的$01$串$,$问有多少总操作序列能得到这个串

---

## 题解

因为是二进制数$,$所以考虑按位处理($i$表示第$i$个数字$,j$表示第$j$位)

$1.$

>$0\lor1=1,1\lor1=1$

>$0\land0=0,1\land0=0$

也就是说如果第$j$位是$0$且$i$前面的运算符是$\land,$那么不管前面是什么最后的运算结果都确定了是$0$(另外一种情况同理)

$2.$
>$0\lor0=0,1\lor0=1$

>$0\land1=0,1\land1=1$

也就是说如果第$j$位是$0$且$i$前面的运算符是$\lor,$那么不管前面是什么最后的运算结果都不会发生改变(另外一种情况同理)

考虑把操作序列转化成$01$序列$(\lor\to0,\land\to1)$

可以观察到

>如果$i$前面的运算符和第$j$位相同那么运算结果就不会改变

>否则的话运算结果也是可以直接得出的

设最后一位是最高位

把第$j$位的$01$串提出来得到一个长度是$n$的二进制数$x$

因为要使得第$j$位运算结果是$1$则最后一个$\lor1$操作的位置一定要在$\land0$后面

转化一下就是就要求$x\gt$**操作串**

$e.g$

>$ x=1011,op=0011,x\gt op$

>$0\lor 1\lor 0\land 1\land 1=1$

>$ x=1011,op=1011,x\le op$

>$0\land 1\lor 0\land 1\land 1=0$

那么这道题就成功的转化为一个比大小的题目了

每一位按照其二进制数的值排序

判断一下每一位二进制数和$op$的大小关系

如果有解最后可以得到$x\le op\lt y,$那么方案数就是$y-x$

```
#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define go(u) for(register int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
const int N=5005,P=1e9+7;
typedef int arr[N];
int n,m,q,c[2];arr a,b,s,t,Mi;char p[N];
inline int pls(int a,int b){return a+=b,a<P?a:a-P;}
inline int sub(int a,int b){return a-=b,a<0?a+P:a;}
int main(){
    #ifndef ONLINE_JUDGE
        file("s");
    #endif
    scanf("%d%d%d\n",&n,&m,&q);
    Mi[1]=1;fp(i,2,n+1)Mi[i]=(Mi[i-1]<<1)%P;
    fp(i,1,m)a[i]=i;
    fp(i,1,n){
        gets(p+1);c[0]=0,c[1]=m;
        fp(j,1,m)p[j]=='1'?s[j]=pls(s[j],Mi[i]):++c[0];
        fd(j,m,1)b[c[p[a[j]]-48]--]=a[j];swap(a,b);
    }
    fp(i,1,m)t[i]=s[a[i]];
    register int up,dw;t[m+1]=Mi[n+1];
    while(q--){
        gets(p+1);up=m+1,dw=0;
        fd(i,m,1)if(p[a[i]]=='0'){dw=i;break;}
        fp(i,1,m)if(p[a[i]]=='1'){up=i;break;}
        printf("%d\n",up<dw?0:sub(t[up],t[dw]));
    }
return 0;
}
```

---

## 作者：Soulist (赞：18)

寻宝游戏

题意：

给定$n$个长度为$m$的$01$串

现在允许你在对$0$依次“按位与”或者“按位或”上这些$01$串

$q$组询问，每次询问有多少种方法填入“按位与”或者“按位或”使得最终结果为询问的$01$串

$Sol:$

$1.$

$$0~|~1~=~1~,\quad 1~|~1~=~1$$

$$0~\&~0=~0,\quad 1~\&~0~=~0$$

于是有对于一个$1$如果其前面填入的为$~|~$，那么无论如何答案都是$1$

对于一个$0$如果其前面填入的为$\&$，那么无论如何答案都是$0$


$2.$

$$1~|~0~=~1~,\quad 0~|~0~=~0$$

$$1~\&~1=~1,\quad 0~\&~1~=~0$$

于是有对于一个$1$如果其前面为$\&$那么答案不会改变

对于一个$0$如果其前面为$~|~$那么答案也不会改变

$3.$

我们先考虑最基础的问题，假设所有的$0/1$串都只有$1$位

我们从后往前考虑所有的$0/1$，可以将其变成一个序列

由于两两之间也有一个操作，于是把操作单独提出来也是一个序列

规定它为操作序列，我们尝试把操作序列转成一个$0/1$序列

令$~|~$为 $0$，$\&$ 为 $1$

于是对于一个$0/1$序列$10010$等，其运算结果为$1$当且仅当其$>$操作序列，否则其为$0$

这是因为对于操作序列，如果偏高位与$0/1$序列全部相等，则为情况$2$运算结果不变，否则如果存在一个$1$且操作序列对应位为$0$则为情况$1$，运算结果为$1$

于是对于一位的情况，我们成功将这道题转化成了一道比大小的题目了$qwq$

对于每个$0/1$串若其有$m$位我们就对其每一位单独考虑

若结果要求当且位为$1$则表明操作序列$<$当且位，否则表示操作序列$\ge$当前位

于是我们将所有的$0/1$串提前排个序，问题就只需要取$0$中最大值$x$和$1$中最小值$y$，$y-x$即方案数

**一点细节**

注意到我们最后要反向，还要对每一位单独处理

于是好像有我们读入的就是待排序的最低位，次低位...最高位

于是好像可以边读入边基排...

复杂度$O(nm+qm)$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define drep( i, s, t ) for( register int i = t; i >= s; -- i )
#define int long long
#define re register
int read() {
	char cc = getchar(); int cn = 0, flus = 1;
	while(cc < '0' || cc > '9') {  if( cc == '-' ) flus = -flus;  cc = getchar();  }
	while(cc >= '0' && cc <= '9')  cn = cn * 10 + cc - '0', cc = getchar();
	return cn * flus;
}
const int P = 1000000007 ; 
const int N = 1000 + 5 ;
const int M = 5000 + 5 ; 
int n, m, q, lk[M], rk[M], b[M][N], a[M], Ans[M] ; 
char s[M] ;
int Get( int x, int y ) {
	return ( Ans[y] - Ans[x] + P ) % P ; 
}
signed main()
{
	n = read(), m = read(), q = read() ; 
	rep( i, 1, m ) rk[i] = i ; 
	rep( i, 1, n ) {
		scanf("%s", s + 1 ) ; int rs = 0 ; 
		rep( j, 1, m ) a[j] = s[j] - '0', b[j][i] = a[j] ; 
		rep( j, 1, m ) if( a[rk[j]] == 0 ) lk[++ rs] = rk[j] ;
		rep( j, 1, m ) if( a[rk[j]] == 1 ) lk[++ rs] = rk[j] ;
		rep( j, 1, m ) rk[j] = lk[j] ; 
	}
	rep( j, 1, m ) drep( i, 1, n ) Ans[j] = ( Ans[j] * 2ll + b[j][i] ) % P ;
	rep( j, 1, n ) Ans[m + 1] = ( Ans[m + 1] * 2ll + 1 ) % P ; 
	rk[m + 1] = m + 1 ; Ans[m + 1] += 1 ; 
	while( q -- ) {
		scanf("%s", s + 1 ) ; int Lk = 0, Rk = m + 1 ; 
		rep( j, 1, m ) if( s[rk[j]] == '1' ) { Rk = j ; break ; }
		drep( j, 1, m ) if( s[rk[j]] == '0' ) { Lk = j ; break ; } 
		printf("%lld\n", ( Rk < Lk ) ? 0 : Get( rk[Lk], rk[Rk] ) ) ;
	} 
	return 0;
}
```

---

## 作者：ztzshiwo001219 (赞：16)

官方题解 [myy的题解](http://matthew99.blog.uoj.ac/blog/3488)

首先注意到0|1=1|1=1,0&0=1&0=0,也就是说不管前面是什么只要遇到|1和&0后面的结果都是确定的.而&1和|0则不会改变结果

那么对于某一位来说最终结果是1的充要条件就是最后一个&0后面至少要有一个|1.也就是最后一个|1的位置要在最后一个&0后面.

我们可以把操作转化一下,对于第i个操作,如果是|就设为0,&就设为1.这样就转化成了一个长度为n的01串.我们可以观察如果要让某一位为1,这个01串需要满足什么条件.我们从后往前看,如果当前为0,操作串也为0,|0没有任何影响,都为1同理.如果遇到一位不同,操作串为1(&),数字为0则一定非法(因为后面没有|1),反之一定合法.

考虑这个过程我们发现:这实际上就是在比较二进制数的大小!如果后面为高位,那么第i位操作后为1,当且仅当操作串的字典序小于第i位01串.那么满足这一位为1的操作的个数就是这一位01串形成的二进制数.

通过这个结论我们可以很明显的得到算法.
对于每一位形成的01串从大到小进行排序,
对于每一个询问检查是否合法(按照排序后的顺序时候所有0在1后面,为1则小于当前数,为0则大于当前数),直接输出答案(最小的结果为1的01串-最大的结果为0的01串)

代码:
```cpp
#include<bits/stdc++.h>
#include<tr1/unordered_map>
#define  For(i,a,b) for(int i=a,i##E=b;i<=i##E;++i)
#define	rFor(i,a,b) for(int i=a,i##E=b;i>=i##E;--i)
#define pb push_back
#define pii pair<int,int>
#define ft first
#define sd second
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long LL;
const int N=5010;
const int inf=0x3f3f3f3f;
const int mod=1e9+7;
template<typename T>inline bool chkmax(T&A,const T&B){return A<B?1,A=B:0;}
template<typename T>inline bool chkmin(T&A,const T&B){return A>B?1,A=B:0;}
template<typename T>inline void read(T&x)
{
    x=0;int f=0;char ch=getchar();
    while(!isdigit(ch))f|=(ch=='0'),ch=getchar();
    while( isdigit(ch))x=x*10+ch-'0',ch=getchar();
    x=f?-x:x;
}
inline void file()
{
    freopen("hunt.in","r",stdin);
    freopen("hunt.out","w",stdout);
}
int n,m,Q,len;
int a[N];
int num[N],p[N];
char str[N][N],q[N];
inline void Add(int&x,const int&y){x=x+y<mod?x+y:x+y-mod;}
inline LL qpow(LL a,LL b)
{
	LL ret=1;
	for(;b;b>>=1,a=a*a%mod)
		if(b&1)ret=ret*a%mod;
	return ret;
}
struct node{int x[N/30+1],id,ans;}s[N];
inline bool operator<(const node&A,const node&B)
{
	rFor(i,len,0)if(A.x[i]!=B.x[i])return A.x[i]>B.x[i];
	return 0;
}
int main()
{
    file();
    read(n),read(m),read(Q);
	For(i,1,n)scanf("%s",str[i]+1);
	For(i,1,m)
	{
		rFor(j,n,1)
		{
			s[i].x[j/30]=(s[i].x[j/30]<<1)|(str[j][i]-'0');
			Add(s[i].ans,s[i].ans+(str[j][i]-'0'));
		}
		s[i].id=i;
	}
	len=n/30;
	sort(s+1,s+m+1);
	For(i,1,m)num[s[i].id]=i;
	s[0].ans=qpow(2,n);
	while(Q--)
	{
		scanf("%s",q+1);
		For(i,1,m)p[num[i]]=q[i]-'0';
		int pos1=0,pos0=0;
		rFor(i,m,1)if(p[i]){pos1=i;break;}
		For(i,1,m)if(!p[i]){pos0=i;break;}
		if(pos0&&pos1&&pos0<pos1)puts("0");
		else printf("%d\n",(s[pos1].ans+mod-s[pos1+1].ans)%mod);
	}
    return 0;
}

```

---

## 作者：StudyingFather (赞：5)

是 myy 的题呢 orz

我们先考虑 $m=1$ 的情况。

容易发现位运算存在这样的规律：

1. $\vee 1$ 和 $\wedge 0$ 会直接影响运算结果，前者使得值变为 $1$，后者使得值变为 $0$；
2. $\vee 0$ 和 $\wedge 1$ 对结果没有影响。

由上面两个结论可以知道，运算最后结果为 $1$，当且仅当存在至少一个 $\vee 1$ 操作，且最后一个 $\vee 1$ 操作在 $\wedge 0$ 操作之前。

看起来似乎还是不太好办？我们转化一下。

设操作序列中 $\vee=0$，$\wedge=1$。

同时我们设数字序列从下往上看得到的数为 $x$，操作序列从下往上看得到的数为 $y$，

这样我们可以转化条件：运算最后结果为 $1$，当且仅当 $x \gt y$。

感性理解一下，从高位向低位相同的位都不影响结果，而对于第一个不同的位，$x$ 对应的位为 $1$，$y$ 对应的位为 $0$ 时，意味着我们在这个位上执行了一次 $\vee 1$ 操作，根据前面的性质，易知这种情况下运算结果为 $1$，反之同理。

最后解集一定是这两个不等式之一：$x \gt y$（该位是 $1$） 或者是 $x \leq y$（该位是 $0$）。

这样我们就解决了 $m=1$ 的情况。

对于多个位的情况，我们需要将各个位的结果合并。

说白了就是解这样一个不等式组：

$$
\begin{cases}
 x \gt a_1\\
 x \leq a_2\\
 x \leq a_3\\
 x \gt a_4\\
 \vdots
\end{cases}
$$

```cpp
// Problem : P4424 [HNOI/AHOI2018]寻宝游戏
// Contest : Luogu
// URL : https://www.luogu.com.cn/problem/P4424
// Author : StudyingFather
// Site : https://studyingfather.com
// Memory Limit : 500 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <iostream>
#include <string>
#include <algorithm>
#define MOD 1000000007
using namespace std;
struct node
{
 string s;
 int id;
 bool operator<(const node&a)const
 {
  return s>a.s||(s==a.s&&id<a.id);
 }
}p[5005];
string a[1005];
long long res[5005];
int main()
{
 ios::sync_with_stdio(false);
 int n,m,q;
 cin>>n>>m>>q;
 for(int i=1;i<=n;i++)
  cin>>a[i];
 for(int i=0;i<m;i++)
 {
  p[i].id=i;
  for(int j=n;j;j--)
  {
   a[j][i]-='0';
   res[i]=(res[i]*2+a[j][i])%MOD;
   p[i].s.push_back(a[j][i]);
  }
 }
 p[m].id=m;
 p[m+1].id=m+1;
 for(int j=n;j;j--)
 {
  res[m]=(res[m]*2+1)%MOD;
  p[m].s.push_back(1);
 }
 res[m]++;
 sort(p,p+m+1);
 while(q--)
 {
  string str;
  cin>>str;
  int l=0,r=m+1;
  for(int i=m;i;i--)
   if(str[p[i].id]=='1')
   {
    l=i;
    break;
   }
  for(int i=0;i<=m;i++)
   if(str[p[i].id]=='0')
   {
    r=i;
    break;
   }
  cout<<(l>r?0:(res[p[l].id]-res[p[r].id]+MOD)%MOD)<<endl;
 }
 return 0;
}
```


---

## 作者：TheLostWeak (赞：5)

[在博客查看](https://www.cnblogs.com/chenxiaoran666/p/Luogu4424.html)

**大致题意：** 给你$n$个$m$位二进制数。每组询问给你一个$m$位二进制数，要求你从$0$开始，依次对于这$n$个数进行$and$或$or$操作，问有多少种方案能够得到给你的这个二进制数。

### 找规律

不难想到去对每一位分别讨论。

则根据位运算法则可得：

- 当你把某一位的数$and\ 0$，就相当于把这一位数赋值为$0$。
- 当你把某一位的数$or\ 1$，就相当于把这一位数赋值为$1$。
- 当你把某一位的数$and\ 1$或者$or\ 0$时，这一位的值均不变。

则可以得出一个结论：

- 若给定数这一位为$0$，则对于这一位的运算中最后一次$and\ 0$要出现在最后一次$or\ 1$之后（或者两者都未出现）。
- 若给定数这一位为$1$，则对于这一位的运算中最后一次$or\ 1$要出现在最后一次$and\ 0$之后（注意$or\ 1$必须有，$and\ 0$可有可无）。

但这样依然不太好操作，所以我们要进行进一步转化。

### 转化

考虑把操作序列转化为一个二进制数，$or$为$0$，$and$为$1$，且较后操作处于较高位。

然后把题目中给出的$n$个长度为$m$的数变为$m$个长度为$n$的数，第$i$个数由初始的$n$个数的第$i$位组成，且编号较大的数处于较高位。

这样一来操作与数就可以一一对应了。

然后考虑如果对应位相等，表示该操作无影响。

而不相等那一位，若操作序列中的值为$0$，数中的值为$1$，即操作序列中这一位小于该数中的这一位，说明是赋值为$1$，反之是赋值为$0$。

由于二进制下比大小看不相等的最高位，所以我们可以得出结论：

- 若操作序列所表示的二进制数小于该数，则最终结果中该数所对应位上为$1$（不能等于是因为一定要有$or\ 1$操作）。
- 若操作序列所表示的二进制数大于等于该数，则最终结果中该数所对应位上为$0$。

也就是说，一个符合条件的操作序列所表示的二进制数，要满足其小于所有应得位为$1$的数，大于等于所有应得位为$0$的数。

而这也就是要小于所有应得位为$1$的数的最小值，大于等于所有应得数为$0$的数的最大值。

则可以先将所有数排序，然后求出所有数取模后的值，然后对于询问从小到大找最大值，从大到小找最小值即可。

具体实现详见代码。

### 代码

```cpp
#include<bits/stdc++.h>
#define Tp template<typename Ty>
#define Ts template<typename Ty,typename... Ar>
#define Reg register
#define RI Reg int
#define Con const
#define CI Con int&
#define I inline
#define W while
#define N 1000
#define M 5000
#define X 1000000007
#define Inc(x,y) ((x+=(y))>=X&&(x-=X))
using namespace std;
int n,m,v[M+5],pw[M+5];
struct data
{
	int p;string s;
	I bool operator < (Con data& o) Con {return s<o.s;}
}s[M+5];
I int XSub(CI x,CI y) {return x<y?x-y+X:x-y;}
int main()
{
	RI Qt,i,j,l,r;string st;for(scanf("%d%d%d",&n,&m,&Qt),i=1;i<=m;++i) s[i].p=i;//初始化
	for(i=1;i<=n;++i) for(cin>>st,j=1;j<=m;++j) s[j].s=st[j-1]+s[j].s;//初始化出字符串
	for(pw[0]=i=1;i<=n;++i) (pw[i]=pw[i-1]<<1)>=X&&(pw[i]-=X);v[m+1]=pw[n];//预处理2的幂
	for(sort(s+1,s+m+1),i=1;i<=m;++i) {for(j=0;j^n;++j) s[i].s[j]^48&&Inc(v[i],pw[n-j-1]);}//排序，预处理出每个数的值
	W(Qt--)
	{
		for(cin>>st,l=0,i=m;i;--i) if(st[s[i].p-1]^'1') {l=i;break;}//找最小值
		for(r=m+1,i=1;i<=m;++i) if(st[s[i].p-1]^'0') {r=i;break;}//找最大值
		printf("%d\n",l<=r?XSub(v[r],v[l]):0);//计算答案
	}return 0;
}
```

---

## 作者：rehtam (赞：3)

对每一位考虑是从哪个位置贡献来的，可以得到 $nm$ 个后缀。

后缀总长度为 $n^2m$，无法存储。考虑对于所有后缀建 trie，空间就只有 $nm$ 级别了。

若 trie 上一个结点到根的 $cnt$ 总和是 $m$ 则以这个点结尾时合法的，方案数为 $2$ 的幂次。此时可以知道它对应的 $01$ 串，哈希记录。

---

## 作者：lhm_ (赞：1)

不难发现 $\vee 1$ 和 $\wedge 0$ 是会影响到最终结果的，相当于赋值操作，而 $\wedge 1$ 和 $\vee 0$ 是无法对结果产生影响的。当某一位最终的结果是 $1$ 时，最后一个能产生影响的操作必须是 $\vee 1$，当最终的结果是 $0$ 时，最后一个能产生影响的操作必须是 $\wedge 0$。

$n$ 个二进制串，对每一位分别来进行考虑，得到 $m$ 个长度为 $n$ 的二进制串，每一位都对应一个二进制串。把 $\vee\wedge$ 的运算序列也看作一个二进制串，$\vee$ 看作 $0$，$\wedge$ 看作 $1$，根据刚才的性质得，若第 $i$ 位的最终结果为 $1$，则第 $i$ 位对应的二进制串要大于运算序列对应的二进制串，若第 $i$ 位的最终结果为 $0$，则第 $i$ 位对应的二进制串要小于等于运算序列对应的二进制串。

因此先将 $m$ 个二进制串排序后，并处理出其对应的权值。对于每个询问串，通过每一位的限制得出运算序列的取值范围，作差即可求解。

同时还需在边界上加上极大值和极小值，因为两个限制分别是大于和小于等于，所以极大值还需特殊处理，让其权值再加上 $1$。

```cpp
#include<bits/stdc++.h>
#define maxn 5010
#define p 1000000007
using namespace std;
typedef long long ll;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,m,q;
int rnk[maxn];
ll pw[maxn],val[maxn];
char str[maxn];
struct node
{
    int s[maxn];
    int id;
}t[maxn];
bool cmp(const node &a,const node &b)
{
    for(int i=n;i;--i)
        if(a.s[i]!=b.s[i])
            return a.s[i]<b.s[i];
    return 0;
}
int main()
{
    read(n),read(m),read(q),pw[0]=1;
    for(int i=1;i<=n;++i) pw[i]=pw[i-1]*2%p;
    for(int i=1;i<=n;++i)
    {
        scanf("%s",str+1);
        for(int j=1;j<=m;++j) t[j].s[i]=str[j]-'0';
    }
    for(int i=1;i<=n;++i) t[m+1].s[i]=1;
    for(int i=1;i<=m+1;++i) t[i].id=i;
    sort(t+1,t+m+1,cmp),val[m+1]=1;
    for(int i=1;i<=m+1;++i)
    {
        rnk[t[i].id]=i;
        for(int j=1;j<=n;++j)
            val[i]=(val[i]+pw[j-1]*t[i].s[j])%p;
    }
    while(q--)
    {
        int l=0,r=m+1;
        scanf("%s",str+1);
        for(int i=1;i<=m;++i)
        {
            if(str[i]-'0') r=min(r,rnk[i]);
            else l=max(l,rnk[i]);
        }
        printf("%lld\n",l>r?0:(val[r]-val[l]+p)%p);
    }
    return 0;
}
```

---

## 作者：81179332_ (赞：1)

我们按位考虑，容易发现，$\text{and}\ 1$ 和 $\text{or}\ 0$ 对答案无影响

若最后一个出现的是 $\text{and}\ 0$，则答案为 $0$；若最后一个出现的是 $\text{or}\ 1$，则答案为 $1$

我们将操作序列中的 $\text{and}$ 看成 $1$，将 $\text{or}$ 看成 $0$

如果令操作序列的最后一位为最高位，设 $n$ 个字符串的第 $j$ 位组成的二进制数为 $x$（第 $n$ 个字符串的第 $j$ 位为最高位）

那么我们可以发现，如果答案为 $0$，则 $x\le op$（如果相等的话就都是对答案无影响的情况，答案为最开始的 $0$）；如果答案为 $1$，则 $x > op$

那么我们将 $m$ 个二进制数排个序，每次询问合并一下不等式组，就得出了答案范围了

不要用 `scanf("%1d",)`，慢死了

```cpp
//timeuse:30min
const int N = 5010;
int n,m,q;
char p[N];ll _2[N],s[N],res[N];
int t[2],a[N],b[N];
int main()
{
	freopen("random.in","r",stdin);
	freopen("sol.out","w",stdout);
	n = read(),m = read(),q = read();
	_2[0] = 1;for(int i = 1;i <= n;i++) _2[i] = Mod(_2[i - 1] + _2[i - 1]);
	for(int i = 1;i <= m;i++) a[i] = i;
	for(int i = 1;i <= n;i++)
	{
		scanf("%s",p + 1),t[0] = t[1] = 0;
		for(int j = 1;j <= m;j++) 
			p[j] -= '0',s[j] = Mod(s[j] + _2[i - 1] * p[j]),t[0] += !p[j],t[1]++;
		for(int j = m;j;j--) b[t[p[a[j]]]--] = a[j];swap(a,b);
	}
	for(int i = 1;i <= m;i++) res[i] = s[a[i]];
	res[m + 1] = _2[n];
	while(q--)
	{
		scanf("%s",p + 1);for(int i = 1;i <= m;i++) p[i] -= '0';
		int up = m + 1,down = 0;
		for(int i = m;i;i--) if(!p[a[i]]) { down = i;break; }
		for(int i = 1;i <= m;i++) if(p[a[i]]) { up = i;break; }
		fprint(up > down ? Mod(res[up] - res[down] + mod) : 0);
	}
	return 0;
}

```

---

## 作者：ylsoi (赞：1)

感觉MYY出的题就是不一样。

位数很多，所以应该要想到对于每一位单独考虑。

对于单独每一位，考虑每一个运算符这一位上的影响，不难发现总共有四种情况：$\land 1, \land 0, \lor 1, \lor 0$，其中$\land 1,\lor 0$对最后的结果不会产生影响，于是我们发现$\land 0$会使目前的结果为0，$\lor 1$会使目前的结果为1，并且每一次的运算独立，和之前的结果并没有任何关系。

于是可以进一步得到，如果最后的结果要为1，那么最后一个有效的运算应该是$\lor 1$，如果是0，则最后一个有效的运算应该是$\land 0$。

于是我们把操作序列的$\land$看作1，$\lor$看作0，并反转。然后将每一位的序列给从后往前提出来，不难发现当这一位的序列$>$opt的时候，这一位的结果为1，反之则为0。

于是我们只要对每一位的操作序列排序就好了。

如果看不懂的话看一下[代码](https://blog.csdn.net/ylsoi/article/details/84841770)可以帮助理解

---

## 作者：tommymio (赞：0)

不是很像 $\text{CN}$ 省选的题，个人感觉更像是 $\text{JOI}$ 那类风格的题（？

对于这种位运算题，一上来肯定先想到拆位并找寻位运算的规律。

- 对于 $\vee$ 而言，任何一位的二进制数 $\vee 0$ 都为其自身，$\vee 1$ 都为 $1$。

- 对于 $\wedge$ 而言，任何一位的二进制数 $\wedge 1$ 都为其自身，$\wedge 0$ 都为 $0$。

**这提醒我们，对于每一位而言，只有 $\wedge 0,\vee 1$ 能够改变这一位上的状态。**

考虑 $m=1$ 的情况。若最终运算结果为 $1$，最后一个 $\vee 1$ 必然在 $\wedge 0$ 之后（也可以不存在 $\wedge 0$，但一定有 $\vee 1$）；若最终运算结果为 $0$，最后一个 $\vee 1$ 必然在 $\wedge 0$ 之前（也可以不存在 $\vee 1$ 和 $\wedge 0$，因为初始时为 $0$）。

但这样还是很难考虑，对模型进行转换。我们发现，插入的每个符号，都对应一个二进制位上的数，除了初始的 $0$ 没有符号与之对应。不妨将 $n$ 个符号也压缩成一个二进制数，并设 $\vee\to 0,\wedge\to 1$。这样设有一个很巧妙的点：当 $\vee 0$ 或 $\wedge 1$ 时，按位比较这两个二进制数是一样的，而 $\vee 1$ 或 $\wedge 0$ 这些对结果有实质影响的操作，体现在这两个二进制数上就有大小之分。

根据之前的结论，最终运算结果为 $1$ 时，最后一个 $\vee 1$ 必在 $\wedge 0$ 之后（或者不存在 $\wedge 0$，只存在 $\vee 1$）。我们发现将给出的 $n$ 个 $1$ 位二进制数按 $n\sim 1$ 从高到低位压缩成一个 $n$ 位二进制数 $x$。记 $w$ 为操作序列压缩成的二进制数，若 $w<x$，那么这一位结果为 $1$；否则，若 $w\geq x$，这一位结果为 $0$。

上述结论的证明如下：
- 对于 $w\neq x$ 的情况，根据二进制比较的定义，设 $w$ 与 $x$ 的 $i\sim n$ 位相等，而在第 $i-1$ 位不相等，相等的部分对结果没有影响，只考虑不相等。不相等只存在两种情况，$w$ 的第 $i-1$ 位为 $0$，而 $x$ 的第 $i-1$ 位为 $1$，或 $w$ 的第 $i-1$ 位为 $1$，而 $x$ 的第 $i-1$ 为 $0$。第一种情况对应了 $\vee 1$ 晚于 $\wedge 0$ 的情况，而第二种情况对应了 $\wedge 0$ 晚于 $\vee 1$ 的情况。
- 对于第一种情况，$w<x$，最终结果为 $1$；对于第二种情况，$w > x$，最终结果为 $0$。
- 对于 $w=x$ 的情况，相等的部分对结果没有影响，因此最终结果为初始的 $0$。

得到上述结论后，对于 $m\geq 2$ 的点也非常好想，直接将每一个二进制数拆位，对于每一位得到一个关于 $w$ 的不等式，解这个不等式组即可。最终得到 $L \leq w < R$，答案即为 $R-L$，注意对于答案处理边界。

代码写的非常娱乐，对于二进制数排序部分的处理，没有用 $\text{trie}$ 也没有用基排，暴力写了个 $\text{cmp}$ 直接套用 $\text{sort}$，跑的慢死了，看看就好（

```cpp
#include<cstdio>
#include<algorithm>
typedef long long ll;
const ll mod=1e9+7;
int n;
struct BN {
	int id,a[5005];
}input[1005],c[5005];
char s[5005]; int rev[5005];
inline int min(const int &x,const int &y) {return x<y? x:y;}
inline int max(const int &x,const int &y) {return x>y? x:y;} 
inline bool cmp(const BN &x,const BN &y) {for(register int i=n;i>=1;--i) {if(x.a[i]<y.a[i]) return 1; if(x.a[i]>y.a[i]) return 0;} return 0;}
signed main() {
	int m,q; scanf("%d%d%d",&n,&m,&q);
	for(register int i=1;i<=n;++i) {
		scanf("%s",s+1);
		for(register int j=1;j<=m;++j) input[i].a[j]=s[m-j+1]-'0'; 
	}
	for(register int i=1;i<=m;++i) {
		for(register int j=n;j>=1;--j) {
			c[i].a[j]=input[j].a[i];
		}
		c[i].id=i;
	}
	std::sort(c+1,c+1+m,cmp);
	for(register int i=1;i<=n;++i) c[m+1].a[i]=1;
	for(register int i=1;i<=m;++i) rev[c[i].id]=i;
	for(register int t=1;t<=q;++t) {
		scanf("%s",s+1); int st=0,ed=m+1;
		for(register int i=1;i<=m;++i) {
			if(s[i]=='1') {ed=min(ed,rev[m-i+1]);}
			else {st=max(st,rev[m-i+1]);}
		}
		if(!cmp(c[st],c[ed])) {printf("0\n");}
		else {
			ll L=0,R=0;
			for(register int i=n;i>=1;--i) L=((L<<1)|(c[st].a[i]))%mod;
			for(register int i=n;i>=1;--i) R=((R<<1)|(c[ed].a[i]))%mod;
			printf("%lld\n",((R+(ed==m+1)-L)%mod+mod)%mod);
		}
	}
	return 0;
}
```

---

## 作者：⚡️行云流水 (赞：0)

首先我们对每一位单独考虑，再将m
位的一起考虑。我们将操作序列也定义为一个01
串。如果是and操作，则为1，否则为0。我们发现：
x and 0=0x or 1=1也就是说 and 0
和 or 1本质上是赋值操作。然后x and 1=xx or 0=x也就是说 and 1
和 or 0
后上值不变。然后考虑第j
位，如果它应该为1
，则最后一个赋值操作后第j
位变成了1
。然后我们观察操作序列和第j
列的01
串之间的关系。赋值操作的时候对应位置上的数不同。所以，我们以n
为最高位，设第j
列的数字为sj
,操作序列的数字为R
，则R>sj
。反之，则R≤sj
。
所以我们将m
列数字排序过后找到上下界就行了。













```cpp
#include <bits/stdc++.h>
#define il inline
const int maxn = 1e3 + 10;
const int maxm = 5e3 + 10;
const int P = 1000000007;
typedef long long ll;
using namespace std;
template<class T> il void rd(T& res) {
    res = 0;char c;bool sign = 0;
    for(c = getchar();!isdigit(c);c = getchar()) sign |= c == '-';
    for(;isdigit(c);c = getchar()) res = (res << 1) + (res << 3) + (c ^ 48);
    (sign) && (res = -res);
    return;
}
template<class T> il void rd(T& a,T& b,T& c) {
    rd(a);rd(b);rd(c);
    return;
}
template<class T> il void Chkmin(T& x,T y) {
    if(x > y) x = y;
}
template<class T> il void Chkmax(T& x,T y) {
    if(x < y) x = y;
}
int n,m,i,j,k,ans,q;  
int rnk[maxn];         
ll _2[maxn],sum[maxn];
bool b[maxn];
struct Node {
    bool val[maxn];int id;
}a[maxm];
il bool cmp(Node a,Node b) {
    for(int i = 1;i <= n;i++) {
        if(a.val[i] < b.val[i]) return 1;
        if(a.val[i] > b.val[i]) return 0;
    }
    return 0;
}
il void add(ll& x,ll y) {
    x = (x + y) % P;
    return;
}
int main() {
    rd(n,m,q);
    _2[0] = 1;
    for(int i = 1;i <= n;i++) _2[i] = (_2[i - 1] << 1) % P;
    for(int i = 1;i <= n;i++) {
        char c;do {c = getchar();}while(!isdigit(c));  
        int cnt = 0;
        while(isdigit(c)) a[++cnt].val[n - i + 1] = c - 48,c = getchar();    
    }
    for(int i = 1;i <= m;i++) a[i].id = i;sort(a + 1,a + m + 1,cmp);   
    for(int i = 1;i <= m;i++) rnk[a[i].id] = i;
    for(int i = 1;i <= n;i++) a[m + 1].val[i] = 1;
    for(int i = 1;i <= m + 1;i++) {
        for(int j = 1;j <= n;j++) {
            if(a[i].val[j]) add(sum[i],_2[n - j]);
        }
    }
    sum[m + 1]++;
    while(q--) {
        int cnt = 0,l = 0,r = m + 1;char c;
        do {c = getchar();}while(!isdigit(c));
        while(isdigit(c)) b[++cnt] = c - 48,c = getchar();
        for(int i = 1;i <= m;i++) {
            if(b[i]) Chkmin(r,rnk[i]);
            else Chkmax(l,rnk[i]);
        }
        if(l > r) puts("0");
        else printf("%lld\n",(sum[r] - sum[l] + P) % P);
    }
    return 0;
}
```


---

