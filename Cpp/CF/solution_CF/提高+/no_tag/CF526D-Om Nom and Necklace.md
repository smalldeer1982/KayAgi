# Om Nom and Necklace

## 题目描述

One day Om Nom found a thread with $ n $ beads of different colors. He decided to cut the first several beads from this thread to make a bead necklace and present it to his girlfriend Om Nelly.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF526D/76315fd43cfbe5e147469d75b9c643c18f6f5673.png)Om Nom knows that his girlfriend loves beautiful patterns. That's why he wants the beads on the necklace to form a regular pattern. A sequence of beads $ S $ is regular if it can be represented as $ S=A+B+A+B+A+...+A+B+A $ , where $ A $ and $ B $ are some bead sequences, " $ + $ " is the concatenation of sequences, there are exactly $ 2k+1 $ summands in this sum, among which there are $ k+1 $ " $ A $ " summands and $ k $ " $ B $ " summands that follow in alternating order. Om Nelly knows that her friend is an eager mathematician, so she doesn't mind if $ A $ or $ B $ is an empty sequence.

Help Om Nom determine in which ways he can cut off the first several beads from the found thread (at least one; probably, all) so that they form a regular pattern. When Om Nom cuts off the beads, he doesn't change their order.

## 说明/提示

In the first sample test a regular sequence is both a sequence of the first 6 beads (we can take $ A= $ "", $ B= $ "bca"), and a sequence of the first 7 beads (we can take $ A= $ "b", $ B= $ "ca").

In the second sample test, for example, a sequence of the first 13 beads is regular, if we take $ A= $ "aba", $ B= $ "ba".

## 样例 #1

### 输入

```
7 2
bcabcab
```

### 输出

```
0000011```

## 样例 #2

### 输入

```
21 2
ababaababaababaababaa
```

### 输出

```
000110000111111000011```

# 题解

## 作者：qwqszxc45rtnhy678ikj (赞：20)

[题目传送门](https://www.luogu.com.cn/problem/CF526D)

这道题就纯属水紫好吧，顶多是个绿……

话不多说，进入正题。

这道题我们可以利用 KMP 的性质来做，我们直接上推算过程：

首先我们可以把 $AB$ 分为名为 $C$ 的一组，那么字符串可以变成 $CC……CA$，其中 $C$ 有 $k$ 个，且 $A$ 是 $C$ 的前缀（由定义而知）。

![](https://cdn.luogu.com.cn/upload/image_hosting/05fi2xmh.png?x-oss-process=image/resize,m_lfit,h_600,w_600)

接着，我们进行求 $next$ 数组来扫一遍。首先，在第一个 $C$ 内，所指向的 $next$ 都是最开始的地方。第一个 $C$ 结束的地方为临界点。

![](https://cdn.luogu.com.cn/upload/image_hosting/bfn2gm0t.png?x-oss-process=image/resize,m_lfit,h_600,w_600)

开始扫后面的值，当扫到第二个 $C$ 的时候，所指向的 $next$ 刚好是第一个 $C$ 里的相同位置。第二个 $C$ 扫描结束后，所指向的 $next$ 刚好扫完第一个 $C$。

![](https://cdn.luogu.com.cn/upload/image_hosting/l1u2v0kk.png?x-oss-process=image/resize,m_lfit,h_600,w_600)

以此类推，后面每次扫到的都是上一个 $C$ 内的相同位置。扫到最后一个点，也就是最后的 $A$ 结束时，它指向了最后一个 $C$ 内的同一位置。

![](https://cdn.luogu.com.cn/upload/image_hosting/6b1xp30r.png?x-oss-process=image/resize,m_lfit,h_600,w_600)

我们可以通过最后一个点和它的 $next$ 指向的地方相减得到 $C$ 的长度，再通过总长和 $C$ 的长度确定 $C$ 的个数和 $A$ 的长度，只要段数是 $k$ 且 $A$ 的长度在 $C$ 以内就可以了。

**但是！**

我们举个例子：

    9 2
    ababababa

我们的段数是大于 $k$ 的，本来是有解，我们的程序把它判定为无解了。怎么办呢？

我们可以先把它原本多少段先求出来，然后看看究竟是 $C$ 的数量除以 $k$ 大，还是膜 $k$ 大，就可以判断了（对应“只要段数是 $k$ 且 $A$ 的长度在 $C$ 以内就可以了”）。

有些坑点和详细细节写代码里的：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,p,h,i=0,j=-1,nxt[1000010]={-1};
char c[1000010];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>c[i];
	while(i<n){ //求next不用说了
		if(j==-1||c[i+1]==c[j+1]){
			i++,j++;
			nxt[i]=j;
		}else j=nxt[j];
	}
	for(int i=1;i<=n;i++){
		p=i-nxt[i]; //C的长度
		h=i/p; //C的个数
		if(i%p)cout<<((h/m-h%m)>0); //如果不为空，大于就行了
		else cout<<((h/m-h%m)>=0); //当A为空的时候，个数除以k（代码里是m）是要大于等于才行的
	}
	return 0;
}
```



------------

### 更正信息

- 感谢 @岂非 的提醒，已经更正，今后题解将更加注意。
- 上次修改未改正完全，现已彻底修改

---

## 作者：MikukuOvO (赞：12)

提供一种简便做法。

首先我们考虑将原串写成$SSSSA$这种形式或者$SSSS$这种形式。

我们考虑$nxt$数组的性质，常识告诉我们$nxt$数组可以求最小循环节，那么我们考虑分类讨论：

我们定义$len=n/(n-nxt[n])$

如果是$SSSSA$这种形式，那么就不能表示为$n-nxt[n]$的循环，这样我们考虑剩余部分就是$A$，长度为$len$%$k$，$B$的长度为$len/k-len$%$k$，我们只要判断$B$的长度是否$>0$。

如果另一种形式同理，判断大于等于$0$即可。

```cpp
const int N=1e6+5;

int n,k;
int nxt[N],ans[N];
char s[N];

int main()
{
    fio();
    gi(n,k);
    scanf("%s",s+1);
    for(int i=2,j=0;i<=n;++i)
    {
	while(j&&s[i]!=s[j+1]) j=nxt[j];
	if(s[i]==s[j+1]) ++j;
	nxt[i]=j;
    }
    for(int i=1;i<=n;++i)
    {
	int cur=i-nxt[i],d=i/cur;
	if(i%cur) ans[i]=((d/k-d%k)>0);
	else ans[i]=((d/k-d%k)>=0);
    }
    for(int i=1;i<=n;++i) print(ans[i]);
    end();
}
```

---

## 作者：fisheep (赞：8)

## 想法：
本来是想复习一下$KMP$，但是看到题解区我却十分的失望。只有一篇是关于$KMP$的(还是我学长并且本蒟蒻还看不懂)。所以自己想了一想打算再写一篇。

首先不得不说这题的思路还是挺巧妙的。

#### 题目思路: KMP 找循环节 + 数学推导

首先想要答案存在，将 $S = A + B$。这个$S$肯定是这个前缀的一段循环节。

我们知道最小循环节为: $min_{cir}=n-nxt[n]$

设$S=q * min_{cir}$

$n=k * |S|+|A|=k * (q * min_{cir})+|A|$

我们知道：

$0 \leq |A| \leq |S|=k * (q * min_{cir})+[0,q * min_{cir}]=[k*(q * min_{cir}),(k+1) * (q* min_{cir})]$

由于$n$是定值，那么就是求是是否存在一个正整数:

$[\dfrac{n}{ (k+1) * min_{cir}},\dfrac{n}{k * min_{cir}}]$


所以接下来就判断区间中是否包含正整数，可以将左端点的值$L$向上取值，右端点的值$R$向下取值，判断 $L <= R$.


```cpp

#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=1e6+7;
#define int long long
inline int read(){
  int x=0,f=1;
  char ch=getchar();
while(ch>'9'||ch<'0'){
if(ch=='-') f=-1;
  ch=getchar();
}
while(ch>='0'&&ch<='9'){
  x=(x<<1)+(x<<3)+(ch^48);
  ch=getchar();
}
return x*f;
}

int f[maxn], n, k;
char s[maxn];
void getfail() {
    f[0] = f[1] = 0;
    for (int i = 1; i < n; ++i) {
        int j = f[i];
        while (j && s[i] != s[j])  j = f[j];
        f[i+1] = s[i];
        if(f[i+1]==s[j]) f[i+1]= j+1 ;
        else f[i+1]=0;
    }
}
bool check(int l, int cir) {
    int upp = l / k, down = l / (k+1) + 1;
    upp = upp / cir, down = (down+cir-1) / cir;//向上取整可以用ceil，但是本蒟蒻不会。
    return upp >= down || (l % (k+1) == 0 && (l / (k+1)) % cir == 0);
}
signed main() {
    n=read(),k=read();
        scanf("%s", s);
        getfail();
        for (int i = 1; i <= n; ++i) {
            int mincir = i - f[i], cir = mincir;
            printf("%d", check(i, cir));
        }
        printf("\n");
    return 0;
}
```

---

## 作者：岂非 (赞：7)

[题目传送门~](https://www.luogu.com.cn/problem/CF526D)

**纯 KMP 做法详解**

现有的 KMP 题解有些太难懂了……蒟蒻看了整整一天才学明白，于是决定自己写一篇。

## 题意简述

给定一个长度为 $n$ 的字符串，判断其每个前缀是否形如 $\texttt{ABABA...BA}$。

## 浅析

看到这样反复循环再多出一个 $\texttt{A}$ 的形式，自然的可以想到用 KMP 求解。

因为显然如果该前缀符合要求，如下图，图中第二行与第三行一定是第一行原串的 border 之一。

![](https://cdn.luogu.com.cn/upload/image_hosting/ftgs52lr.png#pic_center)

# 正题

### 以下过程均假设该前缀是合法串

定义当前前缀为 $C$,$C$ 的长度为 $i$, 

$C$ 中最小循环节为 $S$，**注意这里的 $S$ 并不代指 $\texttt{AB}$**，

那么一个合法的串一定形如 $SSSSST$ 或 $SSSSSS$，**注意这里的 $T$ 也不是指 $\texttt{A}$**。

由上面的定义，显然 $\texttt{AB}$ 是由若干个 $S$ 拼成的，而 $T$ 则是 $S$ 的一个不为 $S$ 本身的前缀。

### 证明

&emsp;&emsp; 1. 由于原串是由 $\texttt{AB}$ 反复拼成的，所以 $\texttt{AB}$ 是一个原串的较大循环节，必由若干最小循环节 $S$ 拼出

&emsp;&emsp; 2. 原串形如 $\texttt{ABAB...A}$，$\texttt{AB}$ 为若干 $S$ 的形式，当 $\texttt{A}$ 不为空串时，一定是若干个连续的 $S$ 加一个 $S$ 的前缀 $T$，而 $\texttt{B}$ 此时的形式为 $T$ 所对应的一个后缀 $S-T$ 加若干个 $S$。

不妨画图表示一下现在串的形式，下图是一个对应的特例：

![一个特例可能是长这样](https://cdn.luogu.com.cn/upload/image_hosting/ck2wjwhv.png "一个特例可能是长这样")

接下来定义几个**重要**的东西：

$nxt[i]$ 为 KMP 中求出的最长公共前后缀

$l$ 为 $S$ 串的长度

$m$ 为 $S$ 串出现的个数

$a$ 为 $\texttt{A}$ 中完整 $S$ 串的个数

$d$ 为 $\texttt{AB}$ 中 $S$ 的个数。

显然 $l=i-nxt[i]$，$m= \lfloor \frac{i}{l} \rfloor $，$a=m \bmod k$，$d= \lfloor \frac{m}{k} \rfloor $ 

在上面那个例子里就是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/aamgn8jc.png)

没明白的同学可以停下来想一想。

### 考虑对于一个普通的字符串如何判断它是一个合法串

Case1: 当 $i \bmod l > 0$ 时，串形如 $SSSSSST$。

&emsp;&emsp;&emsp;&emsp; 显然此时无论是 $\texttt{A}$ 还是 $\texttt{B}$，都不能为空串

&emsp;&emsp;&emsp;&emsp; $\texttt{A}$ 显然是有长度的，所以判一下 $\texttt{B}$ 是否为空就可以乐

&emsp;&emsp;&emsp;&emsp; 判这个的方式就是看一下 $d-a$ 是否为正，大概如下图，判的是 $\texttt{B}$ 是否至少占据 $(S-T)$

![](https://cdn.luogu.com.cn/upload/image_hosting/od0jh2pi.png)

&emsp;&emsp;&emsp;&emsp; 颜色代表的含义与上一张图相同，新的绿色是得到的 $\texttt{B}$ 中有多少个 $S$（上取整）

Case2: 当 $i \bmod l = 0$ 时，串形如 $SSSSSS$。按照前面的定义与 KMP 中 $nxt$ 数组的性质，求出的 $T=S$

&emsp;&emsp;&emsp;&emsp;这个情况要考虑的好像就有点多了：

&emsp;&emsp;&emsp;&emsp;1. $\texttt{A}$ 和 $\texttt{B}$ 都不是空串

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; 此时把最后一个串 $S$ 看作 $T$，就可以当作 Case1 正常处理。

&emsp;&emsp;&emsp;&emsp;2. $\texttt{B}$ 是空串

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; 此时 $\texttt{A}$ 占据的是完整的一段 $S$。

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; 由于 $\texttt{B}$ 可以是空串，所以 $d-a =0$。

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; 大概是下图这样

![](https://cdn.luogu.com.cn/upload/image_hosting/ihorzw9v.png "一个特例")

&emsp;&emsp;&emsp;&emsp;3. $\texttt{A}$ 是空串

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; 此时 $\texttt{B}$ 占据的是完整的一段 $S$，$a=0$。

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; 显然，要保证 $b$ 不为空串，$d-a > 0$ 即可。

&emsp;&emsp;&emsp;&emsp;**综上所述，**

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; **在 Case1 下，只要 $d-a > 0$，该串为合法串**

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; **在 Case2 下，只要 $d-a \geq 0$，该串为合法串**

## 代码

代码变量名写的很清楚，不需要解释。

```cpp
#include <cstdio>
using namespace std;
int n,k,nxt[1000010],lenth_of_blocks,number_of_blocks,blocks_of_a;
char s[1000010];
int main(){
    scanf("%d%d",&n,&k);
    scanf("%s",s+1);
    for(int i=2,j=0;i<=n;i++){
        while(j&&s[i]!=s[j+1]) j=nxt[j];
        if(s[i]==s[j+1]) j++;
        nxt[i]=j;
    }
    for(int i=1;i<=n;i++){
        lenth_of_blocks=i-nxt[i];
        number_of_blocks=i/lenth_of_blocks;
        blocks_of_a=number_of_blocks%k;
        if(i%lenth_of_blocks!=0){
            if(number_of_blocks/k-blocks_of_a>0){
                putchar('1');
            }
            else{
                putchar('0');
            }
        }
        else{
            if(number_of_blocks/k-blocks_of_a>=0){
                putchar('1');
            }
            else{
                putchar('0');
            }
        }
    }
    return 0;
}
```

---

## 作者：KingPowers (赞：6)

## 前言

[题目链接](https://www.luogu.com.cn/problem/CF526D)

虽然题解区中已经有了 KMP 的解法，但个人认为大部分已有的 KMP 题解说的都不太明白，有的甚至还不太严谨，因此写了篇自认为明白一点的。

## 正文

常识级别的结论：长度为 $n$ 的字符串其最小循环节长度为 $n-nxt_n$，若 $n\bmod{(n-nxt_n)}$ 不为 $0$ 则不存在循环节。

考虑将 $AB$ 作为一个整体看待，形如 $ABABA$ 的字符串一定也可以表示成 $SSSST$ 的形式，如果令 $B$ 为空的话还可以直接表示成 $SSSSS$ 的形式，其中 $T$ 是 $S$ 的一个前缀。

记 $d=n/(n-nxt_n)$，因为一共出现了 $k$ 次 $AB$，所以每一个 $AB$ 都出现了 $d/k$ 次 $S$，而 $A$ 就是去掉 $k$ 次 $AB$ 后剩下的 $d\bmod k$ 那一部分，因此 $B$ 中就出现了 $d/k-d\bmod k$ 个 $S$。

如果说原串存在循环节，此时 $B$ 是可以为空的，因此只需要 $d/k-d\bmod k\ge0$ 即可；否则 $B$ 是不可以为空的，需要满足 $d/k-d\bmod k>0$。

## 代码

```cpp
#include<bits/stdc++.h>
//#define int long long
#define fi first
#define se second
#define Mp make_pair
#define pb emplace_back
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rof(i,a,b) for(int i=a;i>=b;i--)
#define clr(a,x) memset(a,x,sizeof(a))
using namespace std;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
const int N=4e6+5;
const int mod=1e9+7;
const int inf=1e9;
int n,k,ans[N],nxt[N];
char s[N];
void Main(){
	scanf("%d%d",&n,&k);
	scanf("%s",s+1);
	for(int i=2,j=0;i<=n;i++){
		while(j&&s[i]!=s[j+1]) j=nxt[j];
		if(s[i]==s[j+1]) j++;
		nxt[i]=j;
	}
	For(i,1,n){
		int len=i-nxt[i],d=i/len;
		if(i%len) ans[i]=(d/k-d%k)>0;
		else ans[i]=(d/k-d%k)>=0;
	}
	For(i,1,n) printf("%d",ans[i]);
}
signed main(){
	int T=1;
	while(T--) Main();
	return 0;
}
```

---

## 作者：chenxia25 (赞：6)

呵呵，先贴一张图：（这就是我CodeForces的头像（至少现在是））

![](https://s2.ax1x.com/2019/12/04/Q1I4Zq.jpg)

>### [洛谷题目页面传送门](https://www.luogu.org/problem/CF526D) & [CodeForces题目页面传送门](https://codeforces.com/contest/526/problem/D)

>给定字符串$a$，求它的每一个前缀，是否能被表示成$m+1$个字符串$A$和$m$个字符串$B$交错相连的形式，即求$\forall i\in[1,|a|],\left[\exists A,\exists B,a_{1\sim i}=\underbrace{A+B+A+\cdots+A+B+A}_{m+1\text{个}A,m\text{个}B}\right]$。

>$|a|\in\left[1,10^6\right]$。

考虑把$A+B$看作一个整体，这样问题就转化为了求$a$的每一个前缀是否能被表示成$m$个字符串$S$相连再连上一个$S$的前缀（可以$=\varnothing$，也可以$=S$）。

我们先考虑怎么在短时间内知道一个$a$的前缀是否可以被表示为$m$个$S$相连，如果可以就再往后扩展。这是一个非常经典的问题。设要求的是$a$的前缀$a_{1\sim i}$。首先，得满足$m|i$，于是我们可以枚举$\dfrac im$，即$|S|$。然后如果$a_{1\sim i-\frac im}=a_{1+\frac im\sim i}$，那么$a_{1\sim i}$可以被表示为$m$个$S$相连（这个很好证吧，错位相等）。我们可以拿$a_{1+\frac im\sim i}$去匹配$a_{1\sim i-\frac im}$，这个显然可以哈希，而在枚举$|S|$时$a_{1\sim i-\frac im}$永远是$a$的前缀，所以也可以Z算法（如果聪明的读者还不知道Z算法是什么，please点击[这个](https://www.cnblogs.com/ycx-akioi/p/Z-algorithm.html)）。

接下来要考虑如何往后拓展。这个比较简单，往后拓展的那段子串长度一定$\in[0,|S|]$，并且要与$a$的前缀匹配。这不正是Z算法的专长吗？$\min(|S|,z_{a,m|S|+1})$不就是能往后拓展的最长长度吗？这个最长长度也可以哈希+二分，但那复杂度就带$\log$了。对了，能往后拓展最长$z_{a,m|S|+1}$个，就意味着$\forall i\in[m|S|,m|S|+z_{a,m|S|+1}]$，$a_{1\sim i}$都能被表示成$m+1$个字符串$A$和$m$个字符串$B$交错相连的形式，这是个区间答案赋成$1$的操作，可以用线段树或树状数组维护，但更简单的有差分。最后被赋成$1$的次数若$>0$，则答案为$1$，否则为$0$。

感觉说的不太清楚。。。具体看代码吧~~（也不一定能看懂啊）~~：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000000;
int n/*|a|*/,m/*要被表示成m+1个A与m个B交错相连的形式*/;
char a[N+5];//字符串 
int z[N+1];//z数组 
void z_init(){//Z算法 
	z[1]=n;
	int zl=0,zr=0; 
	for(int i=2;i<=n;i++)
		if(zr<i){
			while(i+z[i]<=n&&a[i+z[i]]==a[1+z[i]])z[i]++;
			if(z[i])zl=i,zr=i+z[i]-1;
		}
		else if(i+z[i-zl+1]<=zr)z[i]=z[i-zl+1];
		else{
			z[i]=zr-i+1;
			while(i+z[i]<=n&&a[i+z[i]]==a[1+z[i]])z[i]++;
			zl=i;zr=i+z[i]-1;
		}
}
int d[N+1];//差分数组 
int main(){
	cin>>n>>m>>a+1;
	z_init();
	for(int i=1;i*m<=n;i++)//枚举|S| 
		if(z[i+1]>=i*(m-1)){//a[1~i*m]可以被表示为m个S相连 
//			cout<<i<<" "<<i*m+min(i,z[i*m+1])<<"\n";
			d[i*m]++;//往后拓展的左端点差分数组++ 
			if(i*m+min(i,z[i*m+1])+1<=n)d[i*m+min(i,z[i*m+1])+1]--;//往后拓展的右端点的下一个差分数组-- 
		}
	int now=0;
	for(int i=1;i<=n;i++){
		now+=d[i];//现在now为i的答案被赋成1的次数 
		cout<<!!now;//转为bool值 
	}
	return 0;
}
```

---

## 作者：Alex_Wei (赞：2)

> *II. [CF526D Om Nom and Necklace](https://www.luogu.com.cn/problem/CF526D)
>
> [常见字符串算法](https://www.cnblogs.com/alex-wei/p/Common_String_Theory_Theory.html) Part 4. Z Algorithm 例题 II.

重新表述题意：若 $S$ 能被表示成 $AAA\cdots AB$，其中 $A$ 出现了 $k$ 次且 $B$ 是 $A$ 的前缀，则 $S$ 符合要求。考虑在 $k\times A$ 处统计答案。根据 border 的性质 2：若 $S$ 有长为 $|S|-p$ 的 border 说明 $S$ 有周期 $p$，我们 KMP 求出 $S$ 的 $nxt$ 数组。若 $i - nxt_i \left | \dfrac i k \right.$ 说明 $S[1,i]$ 由 $k$ 个相同字符串拼接而成，即 $|A|=\dfrac i k$。

此时仅需考虑可能的 $B$ 的最长长度 $r$，即 $\min(|A|,|\mathrm{lcp}(S[i+1, n],S)|)$，后者可以用 Z 算法求得。这说明 $S[1,i\sim i + r]$ 都可以成为答案，用差分维护即可，时间复杂度线性。 

```cpp
const int N = 1e6 + 5;
int n, k, nxt[N], z[N], pre[N];
char s[N];
int main() {
	scanf("%d %d %s", &n, &k, s + 1);
	for(int i = 2, p = 0, l = 0, r = 0; i <= n; i++) {
		while(p && s[p + 1] != s[i]) p = nxt[p];
		nxt[i] = p += s[p + 1] == s[i];
		if(i <= r) z[i] = min(r - i + 1, z[i - l + 1]);
		while(s[1 + z[i]] == s[i + z[i]]) z[i]++;
		if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1; 
	} for(int i = k; i <= n; i += k) {
		int period = i - nxt[i];
		if(i / k % period == 0) pre[i]++, pre[i + min(i / k, z[i + 1]) + 1]--;
	} for(int i = 1; i <= n; i++) cout << ((pre[i] += pre[i - 1]) > 0);
	return 0;
}
```

---

## 作者：世末OIer (赞：2)

哈哈，看到楼下没有Z-function的题解，我来发一发

```cpp

#include<bits/stdc++.h>
using namespace std;
const int N = (int)1e6 + 100;
int n;
char s[N];
int z[N];
int a[N];
char ans[N];
int k;

inline void calc_z(){                               //处理出所有的Z的值
	int l=0,r=0;
	for(int i=1;i<n;i++){
		if(i<=r)
			z[i]=min(r-i,z[i-l]);
		while(i+z[i]<n && s[z[i]]==s[i+z[i]])
			z[i]++;
		if(i+z[i]>r){
			l=i;
			r=i+z[i];
		}
	}
	return;
}

int main(){
	scanf("%d %d %s",&n,&k,s);
	calc_z();                                       //预处理
	ans[n]=(char)(0);
	if(k==1){                                       //特判
		for(int i=0;i<n;i++) ans[i]='1';
		printf("%s\n",ans);
		return 0;
	}
	for(int d=1;d*k<=n;d++){                        //枚举长度
		if(z[d]<d*(k-1)) continue;                  //当然不行，跳过
		int l=d*k;                                  //判断
		int r=min(d+z[d],d*(k+1))+1;                //同上
		a[l]++;                                     //更改
		a[r]--;                                     //同上
	}
	int bal=0;
	for(int i=1;i<=n;i++){                          //计算
		bal+=a[i];
		if(bal>0) ans[i-1]='1';
		else ans[i-1]='0';
	}
	printf("%s\n",ans);                             //输出
	return 0;
}
```

---

## 作者：ncwzdlsd (赞：2)

看了其他大佬的题解有用到 Z 函数做的，其实不需要扩展 KMP，朴素的 KMP 即可。

前置芝士：KMP 算法（这个大家应该都会，要不也不会来薄纱字符串紫题 qwq）

首先介绍一下 KMP 中的 `nxt` 数组在求最小循环节时的应用：如果 `n%(n-nxt[n])==0`，那么最小循环节为 `n-nxt[n]`；否则不存在最小循环节。

我们考虑把这个字符串从 $\texttt{ABABAB…ABA}$ 转化为 $\texttt{SSS…SA}$ 的形式，由于 $A$ 可以为空，所以还可以把它转化为 $\texttt{SSS…S}$ 的形式。对于第一种形式（即 $A$ 不为空），我们可以知道此时它不存在最小循环节，所以我们的 $A$ 的长度就是 `tim%k`（`tim` 表示对于当前字符串它最小循环节出现的次数），$B$ 的长度就是 `tim/k-tim%k`，只要 $B$ 的长度大于 $0$ 即满足题意；对于第二种形式，我们只要 $B$ 的长度大于等于 $0$ 即可。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=1e6+5;
char s[maxn];
int nxt[maxn],out[maxn];

int main()
{
	int n,k;cin>>n>>k;
	scanf("%s",s+1);
	for(int i=1,j=0;i<=n;i++)
	{
		while(j&&s[i+1]!=s[j+1]) j=nxt[j];
		if(s[i+1]==s[j+1]) j++;
		nxt[i+1]=j;
	}
	for(int i=1;i<=n;i++)
	{
		int now=i-nxt[i],tim=i/now;
		if(i%now) out[i]=((tim/k-tim%k)>0);
		else out[i]=((tim/k-tim%k)>=0);
	}
	for(int i=1;i<=n;i++) cout<<out[i];
	return 0;
}
```

---

## 作者：EuphoricStar (赞：1)

## 思路

题意相当于将 $S$ 表示成 $A^kB$（$A^x = A^{x-1}A$，$A^0$ 为空串），其中 $B$ 为 $A$ 的前缀。

考虑枚举 $|A^k|$，设 $|A^k| = len\ (k\ |\ len)$，在 $[1,len]$ 中寻找长度为 $\dfrac{len}{k}$ 的循环节。看到循环节就想到 KMP，预处理出 $fail_i$，那么 $[1,len]$ 的最短的循环节长度为 $len - fail_{len}$。当 $len - fail_{len} \nmid len$ 或者 $len < 2 \cdot (len - fail_{len})$（即循环次数 $< 2$；注意当 $m=1$ 时这个条件可以不满足），则 $[1,len]$ 不存在循环节。现在已经知道了最短的循环节长度为 $len - fail_{len}$，若 $[1,len]$ 存在长度为 $\dfrac{len}{k}$ 的循环节，那么必须满足 $(len - fail_{len})\ |\ \dfrac{len}{k}$。

现在要求最长的满足 $B$ 为 $A$ 前缀的 $B$ 的长度。先求出原串的 $\mathbf{Z}$ 函数数组 $z$。显然 $B$ 也必须是整个串的前缀，所以 $|B| \le z_{len + 1}$。又因为 $|B| \le |A| = \dfrac{len}{k}$，所以 $|B|_{\max} = \min(z_{len+1},\dfrac{len}{k})$。知道了 $|B|$ 的范围，也就知道了满足条件的整个串的前缀的范围。开一个数组 $d_i$，若 $d_i > 0$ 则原串前缀 $[1,i]$ 满足条件，否则不满足，在 $d$ 数组上将 $[i,i+|B|_{\max}]$ 整体加一。实现时差分即可。

时空复杂度均为 $O(n)$。

## 代码

[code](https://codeforces.com/contest/526/submission/161434231)

---

## 作者：He_Ren (赞：1)

# z算法

要找形如$ABABABABA$的串

这个很难下手

**找出不变的量，转化问题**

考虑设$S=AB$

那么问题就转化为求$\underbrace{S\cdots S}_\text{k个S}\ T$

其中，T是S的一个前缀

由前缀想到z算法

先枚举S的长度，再判断其余的$k-1$个位置的$z_i$是否$\leq |S|$

复杂度好像是$O(n^2)$的，这也是部分人不敢写的原因

**正确计算复杂度，并敢写代码，也是解题中重要的部分**

观察发现，复杂度实际上是$O(\frac{n}{k} \times k)$，就是$O(n)$

$T$的长度，在$0$到$|S|$见任意取即可

也就是说，这段区间的答案都是1

可以用差分维护

总复杂度$O(n^2)$

```cpp
#include<cstdio>
const int MAXN = 1e6 + 5;

inline int min(int a,int b){ return a<b? a: b;}

int n;
char s[MAXN];
int z[MAXN];

inline void calc_z(void)
{
	int l=0, r=0;
	for(int i=1; i<n; ++i)
	{
		z[i]=0;
		if(i<r) z[i] = min(r-i, z[i-l]);
		while(i+z[i]<n && s[z[i]] == s[i+z[i]]) ++z[i];
		if(i+z[i] > r) l=i, r=i+z[i];
	}
}

int ans[MAXN];

int main(void)
{
	int k;
	scanf("%d%d%s",&n,&k,s);
	
	z[0]=n;
	calc_z();
	
	for(int l=1; l<=n/k; ++l)
	{
		bool flag=1;
		for(int i=1; i<k; ++i)
			if(z[l*i]<l)
			{
				flag=0;
				break;
			}
		if(flag)
		{
			++ans[l*k];
			--ans[l*k + min(l,z[l*k]) + 1];
		}
	}
	for(int i=1, cnt=0; i<=n; ++i)
	{
		cnt+=ans[i];
		if(cnt>0) putchar('1');
		else putchar('0');
	}
	return 0;
}
```

# 哈希

上面的部分相似，不再赘述

提供另一种计算$T$的方法

考虑哈希



如果暴力枚举，总复杂度就变成$O(n^2)$，显然太慢

发现答案有单调性，于是二分$T$的长度（$0 \leq |T| \leq \min(|S|,n - k \times |S|)$）

总复杂度$O(n\log n)$，对于$n \leq 10^6$来说跑得有些满

**发现程序过的风险较大，应及时考虑卡常**

我在写的时候，对这点意识就不强，导致T了好几次，应多加注意

```cpp
#include<cstdio>
#include<cstdlib>
#include<ctime>
typedef long long ll;
const int MAXN = 1e6 + 5;

inline int min(int a,int b){ return a<b? a: b;}

char s[MAXN];
struct Hash_map
{
	int mod,base,pb[MAXN];
	int h[MAXN];
	
	inline void init(int n)
	{
		pb[0]=1;
		for(int i=1; i<=n; ++i)
		{
			pb[i] = ((ll)pb[i-1] * base) %mod;
			h[i] = ((ll)h[i-1]*base + s[i]) %mod;
		}
	}
	
	inline int val(int l,int r)
	{
		int res = (h[r] - (ll)h[l-1]*pb[r-l+1]) %mod; 
		return res<0? res+mod: res;
	}
	
	inline bool check(int l2,int len){ return h[len] == val(l2,l2+len-1);}
}m1,m2;

int ans[MAXN];

int main(void)
{
	srand(time(0));
	int n,p;
	scanf("%d%d%s",&n,&p,s+1);
	
	m1.mod=19260817; m1.base = rand()%233 + 321; m1.init(n);
	m2.mod=19491001; m2.base = rand()%321 + 233; m2.init(n);
	
	int maxl = n/p;
	for(int l=1; l<=maxl; ++l)
	{
		int v1 = m1.h[l], v2 = m2.h[l];
		bool flag=1;
		for(int i=1; i<p; ++i)
			if(v1 != m1.val(i*l+1, (i+1)*l) || v2 != m2.val(i*l+1, (i+1)*l))
			{
				flag=0;
				break;
			}
		if(!flag) continue;
		
		int L=0, R=min(l,n-p*l);
		int pl = p*l + 1;
		while(L<R)
		{
			int mid = (L+R+1)>>1;
			if(m1.check(pl, mid) && m2.check(pl, mid)) L = mid;
			else R = mid-1;
		}
		
		++ans[pl-1];
		--ans[pl+L];
	}
	
	int cnt=0;
	for(int i=1; i<=n; ++i)
	{
		cnt+=ans[i];
		if(cnt>0) putchar('1');
		else putchar('0');
	}
	return 0;
}
```


---

## 作者：Aiopr_2378 (赞：0)

Solution of CF526D Om Nom and Necklace

标签：KMP

## 解题思路

关于周期字符串，想到 KMP，因为在 $nxt$ 数组中，前后缀是相等的。对于一段字符串，构成形如题目中形如 $\texttt{ABAB...ABA}$ 的最短循环节 $\texttt{AB}$ 长度就是 $n-nxt[n]$。

> 例子 &emsp; 在字符串 $\texttt{abaabaabaab}$ 中，$n=11,nxt[n]=8$，最短循环节长度为 $3$。 

这样，通过计算 $nxt$ 数组就可以得到每个前缀字符串的最短循环节长度。

怎样求是否能拆分成 $k+1$ 个 $\texttt{A}$ 和 $k$ 个 $\texttt{B}$ 呢？不难发现，抛去最后一个 $\texttt{A}$，前面的 $k$ 对 $\texttt{AB}$ 正好构成一个**循环节**，但不一定是最短的（通过模拟样例即可理解）。

设$len=n-nxt[i]$ 表示前 $i$ 个字符构成的前缀中，最小循环节的长度；$p=\lfloor \frac{i}{len}\rfloor$ 表示以最小循环节为单位，构成 $p$ 个完整的循环节，分类讨论：

- 若 $len\nmid i$，也就是说后面会跟上一点不完整的循环节，例如最小循环节长度为 $3$ 的字符串 $\texttt{abbabbab}$。此时，$\texttt{B}$ 串占循环节次数为 $\lfloor p/k\rfloor$，为补全向下取整的部分， $\texttt{A}$ 占据 $p\bmod k$ 的长度。满足题目要求，即要满足：$\lfloor p/k\rfloor-p \bmod k>0$。
- 若 $len\mid i$，也就是说没有不完整的循环节，例如最小循环节长度为 $3$ 的字符串 $\texttt{abbabb}$。与上面相似地，$\texttt{B}$ 串占据循环节次数 $\lfloor p/k\rfloor$，$\texttt{A}$ 串占据 $p\bmod k$。因为没有多余的不完整循环节，两个串可以有一个为空串，则要满足：$\lfloor p/k\rfloor-p\bmod k\ge 0$。

前面的 KMP 还是很好想的，后面计数注意一下细节就好啦~

## 参考代码

```cpp
#include<iostream>
using namespace std;
#define MAXN 1000005
int n,k,nxt[MAXN];
char s[MAXN];
int main(){
    cin>>n>>k>>(s+1);
    for(int i=2,j=0;i<=n;i++){
        while(j&&s[i]!=s[j+1]) j=nxt[j];
        if(s[i]==s[j+1]) j++;
        nxt[i]=j;
    }
    for(int i=1;i<=n;i++){
        int len=i-nxt[i];
        int p=i/len;
        if(i%len) cout<<(p/k-p%k>0);
        else cout<<(p/k-p%k>=0);
    }
    return 0;
}
```

---

## 作者：pengyule (赞：0)

做法比较麻烦，口述一下。

你对任何一个 `BABA..BAB` 串都可以根据 KMP 得到 `BA`，`BABA..BAB` 模 `BA` 余下的是 `B`，从而 `A`。（`A`, `B`都可以为空串）

首先判一下得到的 `A`、`B` 最基本的合不合法。接下来考虑：

设 $P=$`BABAB..AB` 的长度为 $num$（注意不是 $i$），这个是 $|A|,|B|$ 都最短的时候，那么考虑，能否变成满足 $k$ 的形式，那就是 $(2u+1)k+(2v+1)(k+1)=num$（$2u+1,2v+1$ 是 $A',B'$ 包含 $P$ 中的几个字符，显然必须都是奇数），解这个不定方程即可。

易错点：当 $A,B$ 中有一为空时，假如当前方案方程无解，还是可以有 alternative 的，就是交换 $A,B$ 然后 $num\gets num-2$ 这样。

[submission](https://codeforces.ml/contest/526/submission/152552204)

---

## 作者：封禁用户 (赞：0)

某些大佬使用了Z-BOX过了此题

本蒟蒻不会，只能用哈希（前缀和）+二分+差分

hash???

由题意得，第一个A的位置为开始，我们枚举第二个A的开始位置，也就是A+B的长度，然后二分能拖多长，也就是往后有几个相等的，在k*i到k*i+ans（二分的结果）都是可以的

总时间复杂度为（nlogn）

具体细节见代码：

```cpp
#define MOD 1000000007ll
#define x 25625462
#define y 46835134
using namespace std;
const int N=1000005;
char s[N];
long long powx[N],powy[N];
long long hashx[N],hashy[N];
int a[N];
string ans;
bool check(int p,int q,int d)
{
	long long hashp=hashx[p+d]-hashx[p];
	if(hashp<0)
		hashp+=MOD;
	hashp=hashp*powx[q-p]%MOD;
	long long hashq=hashx[q+d]-hashx[q];
	if(hashq<0)
		hashq+=MOD;
	if(hashp!=hashq)
		return false;
	hashp=hashy[p+d]-hashy[p];
	if(hashp<0)
		hashp+=MOD;
	hashp=hashp*powy[q-p]%MOD;
	hashq=hashy[q+d]-hashy[q];
	if(hashq<0)
		hashq+=MOD;
	if(hashp!=hashq)
		return false;
	return true;
}
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	scanf("%s",s);
	powx[0]=1;
	for(int i=0;i<n;i++)
		powx[i+1]=powx[i]*x%MOD;
	powy[0]=1;
	for(int i=0;i<n;i++)
		powy[i+1]=powy[i]*y%MOD;
	for(int i=0;i<n;i++)
		hashx[i+1]=(hashx[i]+(long long)(s[i]-'a')*powx[i])%MOD;
	for(int i=0;i<n;i++)
		hashy[i+1]=(hashy[i]+(long long)(s[i]-'a')*powy[i])%MOD;
	for(int i=0;i<n/k+1;i++)
	{
		int lb=0,ub=n+1;
		while(ub-lb>1)
		{
			int mid=(lb+ub)>>1;
			if(i+mid<=n&&check(0,i,mid))
				lb=mid;
			else
				ub=mid;
		}
		int l=k*i;
		int r=min(l+i,i+lb);
		if(l<=r)
		{
			a[l]++;
			a[r+1]--;
		} 
	}
	for(int i=0;i<n;i++)
		a[i+1]+=a[i];
	for(int i=0;i<n;i++)
		ans+=(a[i+1]>0)?'1':'0';
	printf("%s\n",ans.c_str());
	return 0;
}

```

---

## 作者：__Hacheylight__ (赞：0)

【题意】



给出一个字符串s，判断其各个前缀是否是 ABABA…ABA的形式（A和B都可以为空，且A有Q+1个，B有Q个，Q给定）。



【分析】



此题出题人比较友好，居然放二分+哈希过了



我们首先枚举第一对A+B的长度i，



由于答案的A+B需要2k+1个，那么一对A+B最长只有N/K那么长，最短为1，可以节省一些枚举资源



由于我们发现如果A的长度x都不满足，比x还大的A肯定不满足



所以我们可以二分A的长度mid，判断其是否合法



我们发现最后一个A的长度的左边位置L是k*i,右边是L+i和i+l（二分的得到的l）中的最小值



之后维护一个查分数组，在L上++，R+1上--



最后扫一遍++，然后看一下该位是否>0即为可以



于是就搞完了




【代码】

```cpp
#include <bits/stdc++.h>
using namespace std ;

#define rep(i, a, b) for (int (i) = (a); (i) <= (b); (i)++)
#define Rep(i, a, b) for (int (i) = (a) - 1; (i) < (b); (i)++)
#define REP(i, a, b) for (int (i) = (a); (i) >= (b); (i)--)
#define clr(a) memset(a, 0, sizeof(a))
#define Sort(a, len, cmp) sort(a + 1, a + len + 1, cmp)
#define ass(a, sum) memset(a, sum, sizeof(a))

#define ls ((rt) << 1)
#define rs ((rt) << 1 | 1)
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define endl '\n'
#define ENDL cout << endl
#define SZ(x) ((int)x.size())

typedef long long ll ;
typedef unsigned long long ull ;
typedef vector <int> vi ;
typedef pair <int, int> pii ;
typedef pair <ll, ll> pll ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
typedef map <ll, ll> mll ;

const int N = 1000010 ;
const double eps = 1e-8 ;
const int iinf = INT_MAX ;
const ll linf = 2e18 ;
const double dinf = 1e30 ;
const int MOD = 1000000007 ;
const int x = 25625462 ;
const int y = 46835134 ;

inline int read(){
    int X = 0, w = 0 ;
	char ch = 0 ;
    while (!isdigit(ch)) { w |= ch == '-' ; ch = getchar() ; }
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar() ;
    return w ? - X : X ;
}

void write(int x){
     if (x < 0) putchar('-'), x = - x ;
     if (x > 9) write(x / 10) ;
     putchar(x % 10 + '0') ;
}

void print(int x) {
	cout << x << endl ;
	exit(0) ;
}

void PRINT(string x) {
	cout << x << endl ;
	exit(0) ;
}

void douout(double x){
	 printf("%lf\n", x + 0.0000000001) ;
}

string ans ;
char s[N] ;
ll hashx[N], hashy[N], powx[N], powy[N], a[N] ;
int n, k ;

bool check(int p, int q, int d)  { // yes, double hash
	ll hashp = hashx[p + d] - hashx[p] ;
	if (hashp < 0) hashp += MOD ;
	hashp = hashp * powx[q - p] % MOD ;
	ll hashq = hashx[q + d] - hashx[q] ;
	if (hashq < 0) hashq += MOD ;
	if (hashp != hashq) return false ;
	
	hashp = hashy[p + d] - hashy[p] ;
	if (hashp < 0) hashp += MOD ;
	hashp = hashp * powy[q - p] % MOD ;
	hashq = hashy[q + d] - hashy[q] ;
	if (hashq < 0) hashq += MOD ;
	if (hashp != hashq) return false ;
	return true ;
}

signed main(){
	scanf("%d%d", &n, &k) ;
	scanf("%s", s) ;
	powx[0] = 1 ;
	for (int i = 0; i < n; i++) powx[i + 1] = powx[i] * x % MOD ;
	for (int i = 0; i < n; i++) hashx[i + 1] = (hashx[i] + (ll) (s[i] - 'a') * powx[i]) % MOD ;
	powy[0] = 1 ;
	for (int i = 0; i < n; i++) powy[i + 1] = powy[i] * y % MOD ;
	for (int i = 0; i < n; i++) hashy[i + 1] = (hashy[i] + (ll) (s[i] - 'a') * powy[i]) % MOD ;
	for (int i = 0; i <= n / k; i++) { // 下一个a的起点
		int low = 0, high = n + 1 ;
		while (low + 1 < high) {
			int mid = (low + high) >> 1 ;
			if (i + mid <= n && check(0, i, mid)) low = mid ;
			else high = mid ;
		}
		int L = k * i ; int R = min(L + i, i + low) ;
		if (L <= R) {
			a[L]++ ;
			a[R + 1]-- ;
		}
	}
	for (int i = 0; i < n; i++) a[i + 1] += a[i] ;
	for (int i = 0; i < n; i++) ans += ((a[i + 1] > 0) ? '1' : '0') ;
	cout << ans << endl ;
}
```

---

