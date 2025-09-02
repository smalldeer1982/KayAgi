# Ehab the Xorcist

## 题目描述

Given 2 integers $ u $ and $ v $ , find the shortest array such that [bitwise-xor](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of its elements is $ u $ , and the sum of its elements is $ v $ .

## 说明/提示

In the first sample, $ 3\oplus 1 = 2 $ and $ 3 + 1 = 4 $ . There is no valid array of smaller length.

Notice that in the fourth sample the array is empty.

## 样例 #1

### 输入

```
2 4```

### 输出

```
2
3 1```

## 样例 #2

### 输入

```
1 3```

### 输出

```
3
1 1 1```

## 样例 #3

### 输入

```
8 5```

### 输出

```
-1```

## 样例 #4

### 输入

```
0 0```

### 输出

```
0```

# 题解

## 作者：syksykCCC (赞：45)

$\oplus$ 表示异或，$\land$ 表示与。

下面是本文需要用到的几个结论：

> 1. **一个序列的异或和一定小于等于数值和。**
> 
> 证明：异或的本质是二进制下的不进位加法，相比起进位的普通加法，所得的结果当然会较小。当然，在进位不会发生，也就是加数之间没有相同的位（与值为 $0$）时，两者是等价的。
> 
> 2. **一个序列的数值和和异或和奇偶性相同。**
>
> 证明：首先继续分析结论 1，得到一个等式：
>
> $$ a+b = (a \oplus b) + 2(a \land b)$$
> $$ (a+b) - (a \oplus b) = 2(a \land b) $$
> $2(a \land b)$ 是二进制下手动进位（找到相同位，左移一位）。
>
> 因为 $a \land b$ 一定是整数，所以 $(a+b)-(a \oplus b)$ 一定是 $2$ 的倍数（偶数）。当然，这个只是两个数的情况，三个数或更多依次分析即可。

那么，当 $u \not\equiv v \pmod{2}$，或者 $u > v$ 时，答案就是 $-1$ 了。

记 $\Delta = v - u$。

先考虑一些特殊情况，比如 $\Delta = 0$，也就是 $u = v$，那么数列直接设置为 $[u]$ 就好了。当然，如果恰好 $u=v=0$ 的话，$[]$ 是满足条件的更短的数列。

然后，我们考虑把 $\Delta$ 拆开，让它自相残杀掉，剩下的就只剩一个 $u$ 了。

不要忘了 $\Delta \bmod 2 = 0$，所以我们可以把它分为相等的两个部分，也就是 $[\frac{\Delta}{2},\frac{\Delta}{2}]$，两个相等的数字的异或和一定是等于 $0$ 的。所以，$[\frac{\Delta}{2},\frac{\Delta}{2}, u]$ 就是一个可行的解。

会不会有更优的解呢？我们考虑把 $\frac{\Delta}{2}$ 和 $u$ 合并，如果 $\frac{\Delta}{2} \land u = 0$，那么，我们大可以把它们替换为一个数，即构造 $[\frac{\Delta}{2}, \frac{\Delta}{2} \oplus u]$ 即可，因为它们没有相同位，异或起来不会进位，所以对数值和也没有影响。

```cpp
#include <bits/stdc++.h>
typedef long long LL;
using namespace std;
LL u, v;
int main()
{
	ios::sync_with_stdio(false);
	cin >> u >> v;
	LL delta = v - u;
	if(delta < 0 || (delta & 1))
	{
		cout << -1 << endl;
		return 0;
	}
	if(!delta)
	{
		if(!u) cout << 0 << endl;
		else cout << 1 << '\n' << u << endl; 
	}
	else
	{
		LL haf = delta >> 1;
		if((haf & u) == 0) cout << 2 << '\n' << haf << ' ' << (haf ^ u) << endl;
		else cout << 3 << '\n' << haf << ' ' << haf << ' ' << u << endl;
	}
	return 0;
}
```

---

## 作者：wind_cross (赞：14)

考场上最后10分钟搞出这道题，~~然而C我没写出来~~

看到许多大佬对此题进行了严谨的证明，对于像我这样的萌新是不太好理解的，我就分享一下自己的考虑思路。

首先题目给出一个异或和和一个数值和，让我们构造序列。毫无疑问，异或和一定小于数值和，大于直接输出-1即可。

然后我们来思考异或和的性质。对于每一个二进制位，如果数列中该位上的1的个数为奇数，则该位最终异或的结果为1，反之为0。所以，对于异或和的每一位，如果为1，则数列中这一位上的1的个数一定需要为奇数，也就是最小值为1。由此便可得到：
```
  异或和转为二进制后，其有1的位上至少在数列中有一个数该位上也为1，并且最终数量一定为奇数，反之为0的位为偶数
```
所以我们考虑先在每一个二进制异或和位为1的填上一个1，现在问题成了数值和-=异或和后，算出可行的数列。

因为现在已经把异或和1的位填好了，那么之后填每一位就不能改变异或和，也就是说每一位至少填两次。也就很容易得到第二个结论：
```
  如果此时数值和与异或和奇偶性相同，则一定有解，反之无解，因为最低位填两次最少+2，所以奇偶性必须相同
```
如果奇偶性相同，就再将数值和（原先的数值和-异或和）转化，具体看代码。然后需要数的个数，就是二进制位中需要填次数最大的一个

代码：
```cpp
#include<cstdio>
#include<algorithm>
#include<cctype>
using namespace std;
template <class code>inline code read(const code &a)
{
    code x=0;short w=0;char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) {x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return w?-x:x;
}
void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)print(x/10);
	putchar(x%10+48);
}
long long qwq1[1005],qwq2[1005],xs[1005];
long long cc[1005];
int main()
{
	long long v=read(v),u=read(u);
	cc[0]=1;
	int zzu;
	for(zzu=1;zzu<=62;zzu++)cc[zzu]=cc[zzu-1]*2;//预先处理二进制位
	if(v>u){//大于直接输出-1
		puts("-1");
		return 0;
	}
	u-=v;
	long long c=0,c1=0;
	while(u!=0){
		++c;
		u>>=1;
	} 
	while(v!=0){
		xs[c1++]=v&1;//直接填v
		v>>=1;
	}
	if(c<c1)c=c1;//重要！！！需要判断一下最多需要的位数，我因为这个wa了3次
	long long yy=c,flag=0;
	while(yy>=0){
		if(2ll*cc[yy]<=u){//如果该位可以填两次
			xs[yy]+=2;//填
			u-=2ll*cc[yy];//数值改变
		}
		--yy;
	}
	if(u){//假如u还没被分解完
		puts("-1");
		return 0;
	}
	long long maxn=0;
	for(int i=0;i<=c;i++)maxn=max(maxn,xs[i]);//最多需要填的次数
	printf("%lld\n",maxn);
	for(int i=1;i<=maxn;i++){
		long long now=0;
		for(int j=0;j<=c;j++){
			if(xs[j]){//每次填的尽量多
				now+=cc[j];
				xs[j]--;
			}
		}
		printf("%lld ",now);//填一个数便输出
	}
	return 0;
}
```

这题作为D难度是很友好的了，cf比赛思维是很重要的，希望这篇题解对你有所帮助！

---

## 作者：rrrrr (赞：10)

这里不讨论前面的情况，仅证明长度为 2 的构造方法的唯一性。   
令 
$$\Delta=V-U$$    
若$\Delta$为偶数，易得一组解为
$$\left(\dfrac{\Delta}{2},\dfrac{\Delta}{2},U\right)$$


假设存在二个数的解  为  
$$\left(U+x ,\Delta -x \right)$$   
即得 
$$ (U+x) \oplus (\Delta -x)=U \quad  (1)$$  
由异或的性质得
$$ 2*((U+x) \land (\Delta -x))=\Delta$$  
所以
$$ (U+x) \land (\Delta -x)=\dfrac{\Delta}{2}\quad  (2)$$
所以
$$(U+x) \lor (\Delta -x)=\dfrac{\Delta}{2}+U\quad  (3)$$
由$(2)$可得
$$ \Delta -x\geqslant\dfrac{\Delta}{2}$$
$$ x\leqslant\dfrac{\Delta}{2}$$
由$(3)$可得
$$ U +x\geqslant\dfrac{\Delta}{2}+U$$
$$ x\geqslant\dfrac{\Delta}{2}$$
所以
$$x=\dfrac{\Delta}{2}$$
带入$(3)$式
$$(U+\dfrac{\Delta}{2}) \lor \dfrac{\Delta}{2}=\dfrac{\Delta}{2}+U\quad $$
所以
$$(U+\dfrac{\Delta}{2}) \land \dfrac{\Delta}{2}=\dfrac{\Delta}{2} $$
显然
$$U\land\dfrac{\Delta}{2} = 0$$    
若为
$$\left(U-x ,\Delta +x \right)$$
同理可证得 $ x=U-\dfrac{\Delta}{2}$ 
（此处留给读者自行证明）   
证毕

---

## 作者：Falashiro (赞：8)

提供一种与大多数题解不同的方法。

显然 $u>v$ 或 $u$ 与 $v$ 奇偶性不同时无解。

对于有解的情况，以 $u=14$ ，$v=20$ 为例，

先把 $u$ 和 $v$ 变成长度相同的 $2$ 进制串，高位补 $0$ 。

$$u:01110\ \ \ \ \ v:00101$$

接着把答案数组看成 $2$ 进制，把 $v$ 的每一位转化成答案数组中这一位为 $1$ 的数的数量。

忽略其他数，对某一位上的数进行考虑。

若想让 $u$ 的某一位为 $0$ ，则 $v$ 的这一位显然要是偶数；

若想让 $u$ 的某一位为 $1$ ，则 $v$ 的这一位显然要是奇数。

即 $u$ 与 $v$ 的每一位的奇偶性必须相同。

然后从最高位开始循环，若第 $i$ 位 $u$ 与 $v$ 奇偶性不同，则 $v_i--$ ，$v_{i-1}+=2$ ，显然这样不影响 $v$ 的大小。

对以上例子进行这步操作后 $:$

$$u:01110\ \ \ \ \ v:00101$$

$$↓$$ 

$$u:01110\ \ \ \ \ v:00120$$

$$↓$$ 

$$u:01110\ \ \ \ \ v:00310$$

$$↓$$ 

$$u:01110\ \ \ \ \ v:2\text-1310$$

然后发现出现了负数，于是需要让低位向高位借位，类似于减法借位。

这一步从低位开始循环。

若 $v$ 的第 $i$ 位为负数则 $v_i+=2$ ，$v_{i+1}--$ 。

但是这样会改变高位的奇偶性，所以仍需要在第 $i$ 位 $u$ 与 $v$ 奇偶性不同时 $v_i--$ ，$v_{i-1}+=2$ 。

对以上例子进行这步操作后 $:$

$$u:01110\ \ \ \ \ v:2\text-1310$$

$$↓$$ 

$$u:01110\ \ \ \ \ v:21210$$

$$↓$$ 

$$u:01110\ \ \ \ \ v:23110$$

此时保证了 $u$ 与 $v$ 的每一位奇偶性相同且没有负数。

答案数组的第 $i$ 位为 $1$ 的次数是 $v_i$ ，所以答案数组的最小长度即为 $v$ 数字串中最大的数，在以上例子中答案数组的最小长度为 $3$ 。

构造答案数组十分简单，只要满足在 $2$ 进制下答案数组第 $i$ 位为 $1$ 的数的数量等于 $v_i$ 即可。

对于以上例子，答案数组可构造为：

$$ans_1:11110$$

$$ans_2:11000$$

$$ans_3:01000$$

每一位相加就是：

$$23110\text{（即为v数字串）}$$

最后转化为 $10$ 进制输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 64
int n,m,a[N],b[N];
signed main(){
	scanf("%lld%lld",&n,&m);
	if(n>m||((m-n)&1)){
		puts("-1");
		return 0;
	}
	int tot1=0,tot2=0,tot,ans=0,t;
	a[++tot1]=n&1;
	while(n/=2)
		a[++tot1]=n&1;
	b[++tot2]=m&1;
	while(m/=2)
		b[++tot2]=m&1;
	tot=max(tot1,tot2);
	for(int i=tot;i>0;i--)
		if((b[i]-a[i])&1)b[i-1]+=2,b[i]--;
	for(int i=1;i<tot;i++){
		if((b[i]-a[i])&1)b[i-1]+=2,b[i]--;
		if(b[i]<0)b[i]+=2,b[i+1]--;
	}
	for(int i=1;i<=tot;i++)
		ans=max(ans,b[i]);
	printf("%lld\n",ans);
	for(int i=1;i<=ans;i++){
		t=0;
		for(int j=1,k=1;j<=tot;j++,k<<=1)
			if(b[j])t+=k,b[j]--;
		printf("%lld ",t);
	}
    return 0;
}
```

---

## 作者：Limit (赞：3)

# 题目大意

给出 $u$ 和 $v$两个数,需要构造出最短的且异或和为 $u$,和为 $v$ 的序列.

# 分析

(分析均在二进制下)

先考虑不存在的情况,可以发现如果 $u>v$ 显然是不存在的,在考虑每加入一个新的数,如果是奇数,那么异或和最后一位会异或上 $1$,和的最后一位也会异或上 $1$,如果加的偶数则最后后一位不会变化,所以必须 $u$ 和 $v$ 奇偶性相同时才会有答案.

(下面的分析中有一个很重要的结论:$\forall a \in \mathbb{Z}\ \exists\ a \oplus a=0$)

如果 $u$ 为 $0$,如果 $v$ 也是 $0$,则直接输出 $0$,否则 $v$ 一定是偶数,所以可以将它拆成两个 $\frac{v}{2}$.

如果 $u$ 不为 $0$,考虑拆成三个数 $u,\frac{v-u}{2},\frac{v-u}{2}$,三个数的和为 $v$,且三个数为异或和为 $u$,但是这并不意味着一定是三个数,如果 $(u+\frac{v-u}{2})\oplus \frac{v-u}{2}=u$ 时就只要两个数了,其实也就是 $u$ 和 $\frac{v-u}{2}$ 不存在在同一个位置为 $1$.

# 代码

```cpp
#include <bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;i>=last;--i)
using namespace std;
long long u,v;
int main()//代码没什么好说的
{
	scanf("%lld%lld",&u,&v);
	if(u>v||(v-u)&1)
	{
		return 0&printf("-1\n");
	}
	if(!u)
	{
		if(!v)
		{
			return 0&printf("%lld\n",u);
		}
		return 0&printf("2\n%lld %lld\n",v/2,v/2);
	}
	if(u==v)
	{
		return 0&printf("1\n%lld",u);
	}
	if(u&((v-u)/2))
	{
		return 0&printf("3\n%lld %lld %lld",u,(v-u)/2,(v-u)/2);
	}
	return 0&printf("2\n%lld %lld",u+(v-u)/2,(v-u)/2);
}

```

---

## 作者：Create_Random (赞：3)

蒟蒻忘判$u=v$,无奈FST.

思路:

分情况讨论。

------------
$u>v$时:

因为是按位异或，

所以最终结果不会超过$v$.

故$u>v$时不成立，输出$-1$.

------------
$u=v$时:

因为不拆分时即可成立，

直接将$u$或$v$输出即可。

------------
$u<v$时:

可以将和的式子拆成$\begin{matrix}u+\underbrace{1+\cdots+1}\\v-u\end{matrix}$

(将这些数进行异或)

所以当$1$的个数为奇数个时(即$(u-v) \bmod 2=1$时)，

就会剩下一个$1$.

所以最终结果就不等于$u$,输出$-1$.

又因为题目中要求序列长度尽可能小，

所以可将$(v-u)$个$1$合并成$2$个$(v-u)/2$.

现在只有三个数了，

就可暴力分类讨论。

如果$(u+(v-u)/2)$ $xor$ $((v-u)/2)$或者$u$ $xor$ $(v-u)$等于$u$,

即可压缩为两个数。

第一种情况:$(u+(v-u)/2)$ 和 $((v-u)/2)$.

第二种情况:$u$ 和 $(v-u)$.

因为$u<v$,

所以不可能压缩为$1$个数。

------------
别忘了$u$和$v$都为$0$时特判输出$0$!

贴代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long u,v;
int main()
{
	scanf("%lld%lld",&u,&v);
	if(u==0&&v==0)
	{
		printf("0");
		return 0;
	}
	if(u>v)
	{
		printf("-1");
		return 0;
	}
	if(u==v)
	{
		printf("1\n");
		printf("%lld",u);
		return 0;
	}
	if((v-u)%2)
	{
		printf("-1");
		return 0;
	}
	long long cnt=(v-u)/2;
	if(((u+cnt)^cnt)==u)
	{
		printf("2\n");
		printf("%lld %lld",u+cnt,cnt);
		return 0;
	}
	if(((2*cnt)^u)==u)
	{
		printf("2\n");
		printf("%lld %lld",2*cnt,u);
		return 0;
	}
	printf("3\n");
	printf("%lld %lld %lld",u,cnt,cnt);
	return 0;
}
```


---

## 作者：Clever_Jimmy (赞：2)

#### D. Ehab the Xorcist [题目链接](https://codeforces.ml/contest/1325/problem/D)

1.  如果 $u > v$ 或者是 $u, v$ 的奇偶性不同，显然不可能有解，输出 `-1`。

2.  如果 $u = v = 0$，那么应输出 `0` （而不是 `1\n0`）。

3.  否则若 $u = v$，那么 $u$ 一定是一个合法解。

4.  否则：

    如果 $u$ 和 $\dfrac{v - u}{2}$ 没有交集，即 `!(u & (v - u >> 1))`，那么 $(u + \dfrac{v - u}{2}, \dfrac{v - u}{2})$ 一定是一组合法解。

    否则 $(\dfrac{v - u}{2}, \dfrac{v - u}{2}, u)$ 一定是一组合法解。

记得开 `long long`。

[code](https://codeforces.ml/contest/1325/submission/73262792)

---

## 作者：dingcx (赞：1)

考试就栽在这一题上了qwq

## 思路

又是一道构造题，先分情况讨论。

### $-1$

不难想到，异或是**带减法的加法**，也就是说，几个数的**异或**值一定**不大于**几个数的**和**。

于是，如果 $a>b$，那么一定输出 $-1$。

又由于异或与和的**奇偶性相同**，所以如果 $b-a$ 是奇数，一定输出 $-1$。

### $n=3$

如果不是无法构造，而且没有 "正整数" 的条件的话，任何 $a$ 和 $b$ 都可以用 $3$ 个数构造出来。

方法很简单，由于 $b≥a$ 且 $b-a$ 是偶数，那么先取 $a$，让后两个数抵消就可以了。（即 $a$, $(b-a)/2$, $(b-a)/2$）

然而，题目有 "**正整数**" 和 "**最短**" 两个条件，只好继续分情况讨论。

（后面每种情况都有样例，样例输出两行的压到了一行）

### $n=0$

样例：```0 0```，输出 ```0```

必须 $a$ 和 $b$ **都是 $0$** 才可以 $n=0$。

### $n=1$

样例：```5 5```，输出 ```1 5```

需要一个数搞定，那么必须 $a=b$，序列就是一个数 $a$。

### $n=2 -(1)$

样例：```0 6```，输出 ```2 3 3```

这种情况是 $a=0$，序列只需要两个数 $b/2$, $b/2$。

### $n=2-(2)$

样例 1：```2 4```，输出 ```2 3 1```

样例 2：```1 9```，输出 ```2 5 4```

通过~~找规律~~可以发现序列的两个数分别是 $(a+b)/2$ 和 $(b-a)/2$。

这两个数的和一定是 $b$，但是异或不一定是 $a$。

例如 ```1 3``` 就不能输出 ```2 2 1```。

于是我想到一个方法：**直接判断**。

也就是说，如果 $(a+b)/2$ $xor$ $(b-a)/2 = a$，那么 $n=2$，否则 $n=3$。

于是这道题就做完了。

## 代码

下面放 AC 代码（感觉这个代码很像骗分）——

```cpp
#include<cstdio>
#define ll long long //注意 longlong
using namespace std;
ll read(){ //快读
	ll num=0,sign=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')sign=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=num*10+ch-'0';ch=getchar();}
	return num*sign;
}
int main(){ //主函数
	ll a=read(),b=read();
	if(a>b||(b-a)&1ll) printf("-1\n");//无解的情况
	else{ //有解
		if(a==0ll&&b==0ll) printf("0\n");//a=b=0,n=0
		else if(a==b) printf("1\n%lld\n",a);//a=b,n=1
		else if(a==0ll) printf("2\n%lld %lld\n",b/2ll,b/2ll);//a=0,n=2(1)
		else{ //n=2(2)和n=3
			if((((a+b)/2ll)^((b-a)/2ll))==a) //直接判断异或
				printf("2\n%lld %lld\n",(a+b)/2ll,(b-a)/2ll);//n=2(2)
			else //n=3
				printf("3\n%lld %lld %lld\n",a,(b-a)/2ll,(b-a)/2ll);
		}
	}
	return 0;//华丽结束
}
```
看我写了那么多分析，总得点个赞再走呀~

---

## 作者：GGGabc (赞：1)

重要思想：满四进二不影响异或值(比如：4个2^n变成2个2^(n+1)不影响异或值)
```c
#include <stdio.h>
long long num[70]={0};//表示数组中每个数二进制1之和
long long num1[70]={0};//表示v的二进制值
long long change(long long n)
{
    long long i=0;
    while(n)
    {
        num[i++]=n%2;
        n=n/2;
    }
    return 0;
}
int main()
{
    long long n=0,m=0,ans=0,max=0;
    scanf("%lld%lld",&n,&m);
    change(n);
    for(long long i=0;i<=69;i++)//记录v二进制值
    {
        num1[i]=num[i];
    }
    if(m<n||(m-n)%2==1) printf("-1\n");
    else
    {
        if(n==m)//特判,谁能想到我昨天特判想了一个多小时！
        {
            if(n==0) printf("0\n");//0的话不需要输入数组数量！
            else printf("1\n%lld\n",n);//数组中只有一个数的时候需要
        }
        else
        {
            num[0]=num[0]+m-n;
            for(long long i=0;i<=68;i++)//满四进二
            {
                long long xx=(num[i]-num1[i])/4;
                num[i]=num[i]-4*xx;
                num[i+1]=num[i+1]+2*xx;
            }
            for(long long i=0;i<=69;i++)//找出数组数量
            {
                if(num[i]>max) max=num[i];
            }
            printf("%lld\n",max);
            for(long long i=1,j=0,x=0;i<=max;i++)//输出
            {
                for(j=0,x=1,ans=0;j<=69;j++,x=2*x)
                {
                    if(num[j]>=1)
                    {
                        ans=ans+x;
                        num[j]--;
                    }
                }
                if(i==1) printf("%lld",ans);
                else printf(" %lld",ans);
            }
            printf("\n");
        }
    }
    return 0;
}
```


---

## 作者：LJB00131 (赞：0)

题外话:为什么你们的构造都这么神仙啊 /kk

怪不得我昨天比赛的时候写这么慢 /kel

### 正题：

我来说一种和其他神仙不一样的构造方法。

首先考虑构造出一组可行解，顺便判断无解。当$u > v$时显然是无解的，还有无解的情况就是无法完成构造。

注意到我们要做的事情就是把v的二进制拆分一下，然后使得u那些位置上的1的个数是奇数。那么当我们把考虑v的一个高位拆成两个比他第一位的1时，这两个1异或之后对答案没有影响。因此我们可以把u拆掉，一直拆到$2^0$，在拆的过程中，当u在这一位上有1的时候，我们给他分配一个1，然后做到最后，如果能把最后这些剩下来的全部异或光，那么就是一组可行解。

那么显然最后可以异或光的条件是我们拆出来的1的个数是偶数。不是偶数就无解。然后我们要做的就是把剩下来的1合并回去，让他异或后变成0。

然而比赛的时候我漏看了"最短",然后第一次交Wa on 1了。(这是句废话)

考虑先合并成一些二进制数，当这一位能被分出两个的时候就给他分出来。最后再分的这些二进制数中， 两个数能拼在一起的就拼在一起。因为一位上的1加到0里是没有影响的。容易证明这样可以是最短的。

上面的东西真的很难表达，我的语文也不好，还是看代码理解理解吧qwq

```cpp
#include<bits/stdc++.h>

using namespace std;

int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while(!isdigit(c))
	{
		if(c == '-') f = -1;
		c = getchar();
	}
	while(isdigit(c))
	{
		x = (x << 3) + (x << 1) + c - '0';
		c = getchar();
	}
	return x * f;
}

typedef long long ll;

ll u, v, a[100005];

int main()
{
	cin >> u >> v;
	if(u > v)
	{
		cout << -1 << endl;
		return 0;
	}
	ll cnt = 0;
	for(int i = 63; i >= 0; i--)
	{
		if(v & (1ll << i)) cnt++;
		if(u & (1ll << i)) cnt--;
		if(i != 0) cnt <<= 1;
	}
	if(cnt & 1)
	{
		cout << -1 << endl;
		return 0;
	}
	int num = 0;
	for(int i = 63; i >= 0; i--)
	{
		if(u & (1ll << i)) a[++num] = (1ll << i);
	}
	for(int i = 61; i >= 0; i--)
	{
		if((1ll << (i + 1)) & cnt)
		{
			a[++num] = (1ll << i), a[++num] = (1ll << i);
			cnt ^= (1ll << (i + 1));
		}
	}
	int c = num;
	for(int i = 1; i <= num; i++)
	{
		for(int j = i + 1; j <= num; j++)
			if((a[i] & a[j]) == 0) 
			{
				a[j] |= a[i], a[i] = 0, c--;
				break;
			}
	}
	printf("%d\n", c);
	for(int i = 1; i <= num; i++)
		if(a[i]) printf("%lld ", a[i]);
	printf("\n");
	return 0;
}
```

---

