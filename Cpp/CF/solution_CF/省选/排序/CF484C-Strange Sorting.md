# Strange Sorting

## 题目描述

How many specific orders do you know? Ascending order, descending order, order of ascending length, order of ascending polar angle... Let's have a look at another specific order:  $ d $ -sorting. This sorting is applied to the strings of length at least $ d $ , where $ d $ is some positive integer. The characters of the string are sorted in following manner: first come all the 0-th characters of the initial string, then the 1-st ones, then the 2-nd ones and so on, in the end go all the $ (d-1) $ -th characters of the initial string. By the $ i $ -th characters we mean all the character whose positions are exactly $ i $ modulo $ d $ . If two characters stand on the positions with the same remainder of integer division by $ d $ , their relative order after the sorting shouldn't be changed. The string is zero-indexed. For example, for string 'qwerty':

Its 1-sorting is the string 'qwerty' (all characters stand on 0 positions),

Its 2-sorting is the string 'qetwry' (characters 'q', 'e' and 't' stand on 0 positions and characters 'w', 'r' and 'y' are on 1 positions),

Its 3-sorting is the string 'qrwtey' (characters 'q' and 'r' stand on 0 positions, characters 'w' and 't' stand on 1 positions and characters 'e' and 'y' stand on 2 positions),

Its 4-sorting is the string 'qtwyer',

Its 5-sorting is the string 'qywert'.

You are given string $ S $ of length $ n $ and $ m $ shuffling operations of this string. Each shuffling operation accepts two integer arguments $ k $ and $ d $ and transforms string $ S $ as follows. For each $ i $ from $ 0 $ to $ n-k $ in the increasing order we apply the operation of $ d $ -sorting to the substring $ S\[i..i+k-1\] $ . Here $ S\[a..b\] $ represents a substring that consists of characters on positions from $ a $ to $ b $ inclusive.

After each shuffling operation you need to print string $ S $ .

## 说明/提示

Here is detailed explanation of the sample. The first modification is executed with arguments $ k=4 $ , $ d=2 $ . That means that you need to apply 2-sorting for each substring of length 4 one by one moving from the left to the right. The string will transform in the following manner:

qwerty $ → $ qewrty $ → $ qerwty $ → $ qertwy

Thus, string $ S $ equals 'qertwy' at the end of first query.

The second modification is executed with arguments $ k=6 $ , $ d=3 $ . As a result of this operation the whole string $ S $ is replaced by its 3-sorting:

qertwy $ → $ qtewry

The third modification is executed with arguments $ k=5 $ , $ d=2 $ .

qtewry $ → $ qertwy $ → $ qetyrw

## 样例 #1

### 输入

```
qwerty
3
4 2
6 3
5 2
```

### 输出

```
qertwy
qtewry
qetyrw
```

# 题解

## 作者：Lynkcat (赞：11)

这里提供一种 $O(nm)$ 的做法。

首先考虑一个 $0$ ~ $k-1$ 的排列：

以 $k=5,d=3$ 为例，

$a=[0,1,2,3,4]$

置换后为 $a'=[0,3,1,4,2]$

这时候我们将 $a$ 中的元素一一映射到 $a'$ 中

![](https://cdn.luogu.com.cn/upload/image_hosting/c8qrtdpo.png)

容易发现排列的置换构成了若干个环。

但依照题意，区间向右移一位，最后的置换应变为 $a'=[3,1,4,2,5]$

映射如下图

![](https://cdn.luogu.com.cn/upload/image_hosting/0mpsojgx.png)

容易发现，除了 $0$ 和 $k-1$ 以外，每个点都有一个入边和一个出边。那么我们容易得出，图上一定是一条 $k-1$ 走到 $0$ 的链与若干个环。

那么事情就变得非常简单了：我们可以计算第 $i$ 个位置最终的位置在哪儿

* $0 \leq i<k$ 

	若 $i$ 在环上，则它参与排序的次数为 $n-k+1$ ，即最终位置它在环上走 $n-k+1$ 步后的位置。
	若 $i$ 在链上，则需要分类讨论，若设 $i$ 走到链尾步数为 $step$ 那么它的最终位置在 $\min(n-k+1,step)+$ 链尾第 $step-\min(n-k+1,step)$ 个点的标号。
    
* $k \leq i$ 

	我们知道这个点会在第 $i-k+2$ 次成为排序区间的末尾，即 $k-1$ 的位置上也就是说这种情况和 $i=k-1$ 时大致相同，不再赘述。
    
code:

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for (int i=(a);i<=(b);i++)
#define R(i,a,b) for (int i=(a);i<(b);i++)
#define D(i,a,b) for (int i=(a);i>=(b);i--)
#define go(i,x) for (int i=head[x];i;i=e[i].nx)
#define mp make_pair
#define pb push_back
#define pa pair < int,int >
#define fi first
#define se second
#define re register
#define be begin()
#define en end()
#define sqr(x) ((x)*(x))
#define ret return puts("-1"),0;
#define put putchar('\n')
#define inf 1000000005
#define mod 998244353
//#define int ll
#define N 2000005
using namespace std;
inline char gc(){static char buf[100000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;}
//#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int n,m,k,d,p;
int to[N],f[N],now,ans[N],P[N],lans[N],b[N],PP[N],cnt,PPP[N];
bool vis[N];
		char lst1[N/2];
char st[N/2];
vector<int>G[N];
int pd(int x,int y)
{
	int p=k-1,l=n-1;
	p=max(p,x);
	l=min(l,x+k-1);
	return l-p+1;
}
signed main()
{
	scanf("%s",st);
	m=read();
	n=strlen(st);
	for (int i=0;i<n;i++) lans[i]=i;
	memset(f,-1,sizeof(f));
	while (m--)
	{
		k=read(),d=read();
		p=0;
		for (int i=0;i<d;i++)
			for (int j=i;j<k;j+=d)
			{
				f[p+k-1]=j+k;
				p++;
			}
		
		now=k-1;p=0;
		b[0]=-1;
		while (~now)
		{
			now=f[now];
			if (now==-1) break;
			vis[now]=1;
			p++;
			P[now-k]=p;
			b[p]=now-k;
		}
		for (int i=k;i<k+k;i++)
			if (!vis[i])
			{
				now=i;p=0;
				++cnt;
				do
				{
					vis[now]=1;
					PP[now-k]=p;
					PPP[now-k]=cnt;
					G[cnt].push_back(now-k);
					p++;
					now=f[now];
				}while (now!=i);
			}
		for (int i=0;i<k;i++)
		{
			int rnd=min(n-k+1,P[i]);
			if (!P[i]) 
			{
				rnd=n-k+1;
				ans[rnd-2+max(1,i-k+1)+G[PPP[i]][(PP[i]-rnd%G[PPP[i]].size()+G[PPP[i]].size())%G[PPP[i]].size()]+1]=i;
			}
			else
			{
				ans[rnd+b[P[i]-rnd]]=i;
			}
		}
		
		for (int i=k;i<n;i++)
		{
			int rnd=min(n-i,P[k-1]);
			if (!P[k-1]) ans[n-k+i+1]=i;
			else
			{
				ans[rnd+max(1,i-k+2)+b[P[k-1]-rnd]-1]=i;
			}
		}
		for (int i=0;i<n;i++)  lst1[i]=st[ans[i]];
		printf("%s\n",lst1);
		for (int i=0;i<n;i++) st[i]=lst1[i];
		for (int i=1;i<=cnt;i++) G[i].clear();cnt=0;
		for (int i=0;i<=k+k;i++)P[i]=b[i]=vis[i]=PP[i]=PPP[i]=0,f[i]=-1;
	}
}
/*
*/


---

## 作者：onglu (赞：7)

### 题意  
定义一种区间排序。  
排序的方式是将区间内下标$i\equiv x(mod\ d)$的放在一块，块的顺序按照块内第一个数的下标排序。  
比如$0,1,2,3,4,5,6$当$d=3$时排序后变成$0,3,6,1,4,2,5$。  
给定一个字符串，和$m$个操作。  
每次操作给定区间长度$k$和$d$。  
从左到右给每一个长度为$k$的序列以此排序。  
每一个操作之后输出现在的字符串。  
  
### 分析  
乍一看无从下手，但是发现每次操作的时候，区间内的数字变化是一定的。  
也就是说，我们只要用一个$p$数组表示一次操作数字的位置变化，就能很轻松地对每一个区间进行递推。  
时间复杂度为$O(mn^2)$，显然是无法通过所有的数据的。  
  
我们考虑优化这个递推过程。  
我们可以把排序区间移动看成是数组整体左移，这样子我们只要变更一下$p$数组，在用$p$数组递推的同时考虑数组左移，就只要不停地对第一个区间进行排序即可。  
比如$k=4,d=2$，原数组为$0,1,2,3,4,5$的时候。  
我们原来的$p$数组应该是$0,2,1,3,4,5$。  
现在我们只要把$p$数组变成$2,1,3,4,5,0$就可以考虑整体左移了。  
  
我们可以利用矩阵乘法的思想优化这个递推过程。  
定义数组乘法为按照数组递推一次。
我们发现对字符串的递推与对$p$数组自乘是一样的。  
那么我们快速幂计算$p$数组递推$n-k+1$次的数组，再用它去乘字符串，就可以把$O(n)$的递推优化到$O(logn)$的递推了。  
注意我们用$p$数组递推的时候原字符串发生了左移，在结束一次操作后一定要把它右移回来。  
### 代码  
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define ll long long
#define file "sorting"
using namespace std;
const int Maxn=1000009;
int read(){
	char c;int num,f=1;
	while(c=getchar(),!isdigit(c))if(c=='-')f=-1;num=c-'0';
	while(c=getchar(), isdigit(c))num=num*10+c-'0';
	return f*num;
}
int n,m,k,d;
char c[Maxn],w[Maxn];
int cnt[Maxn],ans[Maxn];
int p[Maxn],tmp[Maxn],l[Maxn];
void multi(int *a,int *b){
	for(int i=0;i<n;i++)
		tmp[i]=a[b[i]];
	for(int i=0;i<n;i++)
		a[i]=tmp[i];
}
void Pow(int *a,int p){
	for(int i=0;i<n;i++)ans[i]=i;
	for(;p;p>>=1,multi(a,a))
		if(p&1)multi(ans,a);
	for(int i=0;i<n;i++)a[i]=ans[i];	
}
void work(){
	k=read();d=read();
	memset(cnt,0,d*4);
	for(int i=0;i<k;i++)
		cnt[i%d]++;
	for(int i=0;i<d;i++)
		cnt[i]+=cnt[i-1];
	for(int i=k-1;i>=0;i--)
		p[(cnt[i%d]--)-1]=i;
	for(int i=k;i<n;i++)
		p[i]=i;
	multi(p,l);
	//for(int i=0;i<n;i++)printf("%d ",p[i]);
	//printf("\n");
	int t=n-k+1;
	Pow(p,t);
	for(int i=0;i<n;i++)
		w[i]=c[p[i>=t?i-t:i+n-t]];
	puts(w);
	for(int i=0;i<n;i++)
		c[i]=w[i];
}
int main()
{
	while((c[n]=getchar())!='\n')n++;
	m=read();
	for(int i=0;i<n;i++)l[i]=i+1;
	l[n-1]=0;
	while(m--)work();
	return 0;
}
/* p为置换矩阵
 * l为左移矩阵  
 */ 


```

---

## 作者：XL4453 (赞：2)

### $\text{Difficulty : 2600}$
---
### 解题思路：

首先很容易发现这个的变化和字符串本身没啥特别大的联系，只要字符串的长度和变化的参数 $d,k$ 给定，就能给出一个固定的置换，将这个置换对应到原始的字符串上就行。

问题就是如何求这个置换，暴力求解复杂度为 $O(n^2m)$，不能接受。

---
进一步研究这个置换是如何产生的，发现直接用题目中给出的形式并不好描述，每一步操作进行的置换都是不同的。但是另一方面，可以发现所有的置换都似乎满足一些特殊的形式，考虑用一些基本的轮换和给出的那个针对前 $k$ 个元素的 $\text{d-sorting}$ 表示出所有的用到的置换。

具体地，设针对前 $k$ 个元素的 $\text{d-sorting}$ 的置换为 $P_0$，考虑第 $i$ 次行动 $P_i$ 作出的置换与 $P_0$ 的关系。



容易发现，$\begin{bmatrix}1,2,3\dots n\\2,3\dots n,1\end{bmatrix}^{i-1} P_0 \begin{bmatrix}1,2,3\dots n\\n,1,2\dots n-1\end{bmatrix}^{i-1}=P_i$。而 $Ans=P_1P_2...P_{n-k+1}$，直接代入就得到了一个非常简洁的形式，这里不妨设置换 $C=\begin{bmatrix}1,2,3\dots n\\2,3\dots n,1\end{bmatrix}^{i-1}$，则 $Ans=(P_0C)^{n-k+1}\begin{bmatrix}1,2,3\dots n\\n,1,2\dots n-1\end{bmatrix}^{n-k+1}$。

根据置换的结合律，这个东西可以直接快速幂求解。这样做的复杂度为 $O(nm\log n)$，可以接受但是不优。

一种明显而且优秀的做法是直接求出这个 $P_0C$ 置换的循环长度，直接环上找点。复杂度 $O(nm)$。

---
因为第二种做法非常优秀，所以我选择第一种。

注意每一次操作之后影响保留。

---
### 代码：

```cpp
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
using namespace std;
int T,m,k,p,n,cnt,P[1000006],C[1000006],ANS[1000006],c[1000006];
char s[1000006],tmp[1000006];
void work(int *a,int *b){
	for(int i=0;i<n;i++)
	c[i]=a[b[i]];
	for(int i=0;i<n;i++)
	a[i]=c[i];
}
void pow(int *s,int p){
	for(int i=0;i<n;i++)ANS[i]=s[i];
	p--;
	while(p){
		if(p&1)work(ANS,s);
		work(s,s);
		p>>=1;
	}
}
int main(){
	while((s[n]=getchar())!='\n')n++;
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&k,&p);
		cnt=-1;
		for(int i=0;i<p;i++){
			for(int j=i;j<k;j+=p)
			P[++cnt]=j;
		}
		for(int i=k;i<n;i++)P[i]=i;
		for(int i=0;i<n-1;i++)C[i]=i+1;C[n-1]=0;
		work(P,C);
		pow(P,n-k+1);
		for(int i=0;i<n;i++)
		tmp[i]=s[ANS[i>=(n-k+1)?i-(n-k+1):i+n-(n-k+1)]];
		for(int i=0;i<n;i++)
		putchar(tmp[i]),s[i]=tmp[i];
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：Inui_Sana (赞：0)

省选后第一道随机题。

考虑确定 $k,d$ 之后，对于每一个 $k$ 的区间，里面的数位置移动就是固定的，换句话说，可以直接用一个置换表示题目所说的排序，记进行一次排序后 $i$ 去到了 $a_i$，则 $a_i=\left\lfloor\dfrac{i-1}{d}\right\rfloor+((i-1)\bmod d)\times \left\lfloor\dfrac{k}{d}\right\rfloor+\min((i-1)\bmod d,k\bmod d)$。

但是这个置换是针对每一个长为 $k$ 的区间的，所以考虑能不能构造出一种置换，使得其可以直接表示每个位置的数的移动。

考虑记录最后在 $i$ 位置的数，进行 $j$ 次我们构造的置换 $p$ 前在哪里。对于 $p$ 的构造，可以考虑固定操作的区间是最后 $k$ 个位置，每次先对最后 $k$ 个位置做一次排序，然后整个序列向后循环位移一位。经过 $n-k+1$ 次置换，就可以根据限制所在的位置，得出在原序列中对应的起始位置，这一部分建议手玩，结合代码理解。

然后倍增优化一下就做完了，时间复杂度 $O(nm\log n)$。

总之，就是构造+手玩，做完了。/cf

code：

```cpp
int n,m,a[23][N];
char s[N],t[N];
void Yorushika(){
	scanf("%s%d",s+1,&m),n=strlen(s+1);
	while(m--){
		int k,d;scanf("%d%d",&k,&d);
		rep(u,1,k){
			int v=(u-1)/d+(u-1)%d*(k/d)+min((u-1)%d,k%d)+1;
			if(u==k)a[0][n-k+v]=1;
			else a[0][n-k+v]=n-k+u+1;
		}
		rep(i,1,n-k)a[0][i]=i+1;
		rep(j,1,20)rep(i,1,n)a[j][i]=a[j-1][a[j-1][i]];
		rep(i,1,n){
			int tmp=n-k+1,p=i;
			drep(j,20,0)if((1<<j)<=tmp)tmp-=1<<j,p=a[j][p];
			if(p<=n-k+1)t[i]=s[k+p-1];
			else t[i]=s[p-n+k-1];
			pc(t[i]);
		}
		puts("");
		rep(i,1,n)s[i]=t[i];
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：Piwry (赞：0)

## 解析

我在写 “排列乘法” 时不小心被坑到了X

粗略来说，可以通过的解法应该都是设 $p[i]$ 表示 “下一步将 $a[p[i]]$ 放到 $i$ 位置”，而当时我设 $p[i]$ 表示 “下一步将 $a[i]$ 放到 $p[i]$ 位置”，于是就 WA 个不停...

因此这里主要分析下社论中提到的 “multiplication of permutations” 部分，其他部分会稍微略过

### Part 0

首先我们可以把原本的操作看成：对字符串的前 $k$ 位进行一次排序，将字符串左移一位... 如此重复 $n-k+1$ 次，再将字符串右移 $n-k+1$ 位

定义 “排列变换” 为任意调换序列中元素的顺序，那么我们所重复的两个操作都可以看做是一次 “排列变换”

### Part 1

考虑用矩阵乘法定义排列变换

设向量 $v=\begin{bmatrix} a_0 \\ \vdots \\ a_{n-1} \end{bmatrix}$ 表示原序列，那么一次排列变换就可以视为一个 $n\cdot n$ 的 $01$ 矩阵。设矩阵 $P$ 表示排列变换，矩阵 $C$ 表示左移变换，那么答案就为 $(P\cdot C)^{n-k+1}\cdot v$，最后再右移 $n-k+1$ 位

为了简化运算，我们可以设 $p[i]$ 表示矩阵的第 $i$ 行第 $j$ 列为 $1$；这样两个变换矩阵的乘法实际上就能看做对右矩阵对应的 $p[.]$ 做左矩阵对应的变换

（同时这也解释了为什么我在最上面提到的，设 $p[i]$ 表示 “下一步将 $a[i]$ 放到 $p[i]$ 位置” 会出现错误...）

这样就已经可以用矩阵快速幂在可接受的复杂度内解决这个问题了

### Part 2

设 $A=P\cdot C$，我们实际上只是对 $v$ 一直在做 $A$ 变换。当次数足够多时，排列中某个数的位置变化一定是循环的；于是可以考虑求出这个 “环”，将变换次数模掉环长后就可以 $O(1)$ 确定变换后某个元素的位置了

具体实现见代码吧

## 代码

```cpp
#include <cstdio>
#include <vector>
using std::vector;

const int MAXN =1e6+20;

/* ------------------------------ IO ------------------------------ */

namespace IO_base{
	const int MAXB =1<<10;
	char gbuf[MAXB], *ps =gbuf, *pt =gbuf;
	char pbuf[MAXB+1], *pp =pbuf;
	struct Flusher{
		~Flusher(){
			fwrite(pbuf, 1, pp-pbuf, stdout);
		}
	}flusher;
	
	inline char Getchar(){
		if(ps == pt){
			ps =gbuf;
			pt =gbuf+fread(gbuf, 1, MAXB, stdin);
		}
		return (ps == pt) ? EOF : *ps++;
	}
	inline void Putchar(const char &ch){
		if(pp == pbuf+MAXB){
			pp =pbuf;
			fwrite(pbuf, 1, MAXB, stdout);
		}
		*pp++ =ch;
	}
}
#define getchar IO_base::Getchar
#define putchar IO_base::Putchar

namespace IO_number{
	int read(){
		int x =0; char c =getchar(); bool f =0;
		while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
		while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
		return (f) ? -x : x;
	}
	
	void write(const int &x){
		if(x < 0){
			putchar('-');
			write(-x);
		}
		else{
			if(x/10)
				write(x/10);
			putchar('0'+x%10);
		}
	}
}
using namespace IO_number;

namespace IO_string{
	void Puts(const char *s){
		#define CHECK_P (\
			(*p >= '0' && *p <= '9') ||\
			(*p >= 'a' && *p <= 'z') ||\
			(*p >= 'A' && *p <= 'Z') ||\
			(*p == ' ') ||\
			(*p == '\n') ||\
			(*p == '-')\
		)
		for(const char *p =s; CHECK_P; ++p)
			putchar(*p);
		putchar('\n');
		#undef CHECK_P
	}
	
	struct string{
		char data[MAXN];
		int len;
		
		int size() const{
			return len;
		}
		
		char & operator [] (const int &index){
			return data[index];
		}
		char operator [] (const int &index) const{
			return data[index];
		}
		
		void read(){
			#define CHECK (\
				(ch >= '0' && ch <= '9') ||\
				(ch >= 'a' && ch <= 'z') ||\
				(ch >= 'A' && ch <= 'Z') ||\
				(ch == '-')\
			)
			char ch =getchar();
			while(!CHECK)
				ch =getchar();
			len =0;
			while(CHECK)
				data[len++] =ch, ch =getchar();
			#undef CHECK
		}
	};
}
#define puts IO_string::Puts
using namespace IO_string;

/* ------------------------------ Main ------------------------------ */

int p[MAXN]; /* p[i] 放到 i */

void work(const int &k, const int &d, const int &n){
	static int _p[MAXN], _tmp[MAXN];
	static bool vis[MAXN];
	
	for(int s =0, j =0; s < d; ++s)
		for(int i =s; i < k; i +=d)
			_p[j++] =i;
	for(int i =k; i < n; ++i)
		_p[i] =i;
	for(int i =0; i < n; ++i)
		_tmp[(i-1+n)%n] =_p[i];
	for(int i =0; i < n; ++i)
		_p[i] =_tmp[i];
	
	const int step =n-k+1;
	for(int i =0; i < n; ++i)
		vis[i] =0;
	for(int i =0; i < n; ++i)
		if(!vis[i]){
			vector<int> circle;
			for(int j =i; !vis[j]; vis[j] =1, j =_p[j])
				circle.push_back(j);
			for(int _i =0; _i < (int)circle.size(); ++_i)
				_tmp[_i] =circle[(_i+step+(int)circle.size())%(int)circle.size()];
			for(int j =i, _i =0; _i < (int)circle.size(); j =_p[j], ++_i)
				p[j] =_tmp[_i];
		}
	
	for(int i =0; i < n; ++i) // mov_r
		_tmp[(i+step)%n] =p[i];
	for(int i =0; i < n; ++i)
		p[i] =_tmp[i];
}

int main(){
	static char _tmp[MAXN];
	static string s;
	s.read();
	const int n =s.size();
	for(int _t =0, T =read(); _t < T; ++_t){
		const int k =read(), d =read();
		work(k, d, n);
		for(int i =0; i < s.size(); ++i)
			_tmp[i] =s[p[i]];
		for(int i =0; i < s.size(); ++i)
			s[i] =_tmp[i];
		puts(s.data);
	}
}
```

---

