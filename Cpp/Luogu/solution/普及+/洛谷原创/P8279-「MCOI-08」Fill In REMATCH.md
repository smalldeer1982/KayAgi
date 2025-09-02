# 「MCOI-08」Fill In REMATCH

## 题目描述

Dream 有一个长度为 $n$（$1\le n\le 10^5$）的整数数组 $a_1,a_2,\dots,a_n$，其中对于 $i=1,2,\dots,n$，满足 $0\le a_i<2^{60}$。

他计算了前缀异或数组 $p_i=a_1\oplus a_2\oplus\dots\oplus a_i$ 以及后缀异或数组 $s_i=a_i\oplus a_{i+1}\oplus\dots\oplus a_n$。

现在 Tommy **一共**将 $p$ 和 $s$ 的 $n$ 个元素换成 $-1$。给定当前的 $p$ 与 $s$ 数组，请恢复任意一组可能为原数组的 $a_1,a_2,\dots,a_n$。

保证存在一组合法解。

## 说明/提示

对于 $100\%$ 的数据，$1\le n,\sum n\le 10^5$，$\sum [p_i=-1]+\sum [s_i=-1]=n$，**保证有合法解。**

 - Subtask 1（10 pts）：$n\le 4$，$p_i,s_i<2$；
 - Subtask 2（10 pts）：$n\le 100$；
 - Subtask 3（20 pts）：$p_i,s_i<2$；
 - Subtask 4（60 pts）：无特殊限制。


## 样例 #1

### 输入

```
1
4
-1 34 367 -1
3178 -1 -1 3333```

### 输出

```
3 33 333 3333```

# 题解

## 作者：Anxiomgh (赞：7)

###### 蒟蒻的第一篇题解，请大家多多指教。 

# Sol 

首先给出异或运算的三个性质： 
1. 归零律：$a \oplus a = 0$
1. 恒等律：$a \oplus 0 = a$
1. 结合律：$a \oplus b \oplus c = a \oplus (b \oplus c) = (a \oplus b) \oplus c$ 

由题意得：  
$p$ 是 $a$ 的前缀异或数组，满足 $p_i = \bigoplus_{j=1}^ia_j$  

$s$ 是 $a$ 的后缀异或数组，满足 $s_i = \bigoplus_{j=i}^na_j$

根据 性质 1 和 性质 3，易得 引理 1: 

$$a_i = p_i \oplus p_{i-1} = s_i \oplus s_{i+1}$$

也就是说，只要能还原出 $p$ 或 $s$ 数组中的每一个被换成 -1 的数的一个合法解，一定可以还原出数组 $a$ 的一个合法解。

如何还原呢？再观察一下数组 $p$ 和 $s$，根据 性质 2，不妨把 $p_0$ 和 $s_{n+1}$ 设为 0，设 $sum = \bigoplus_{i=1}^na_i$，根据 性质 3，易得 引理 2：  

$$p_i \oplus s_{i+1} = sum(0 \leq i \leq n)$$ 

不难发现，如果用 引理 2 还原 $p$ 数组或 $s$ 数组，必定要先用 引理 2 求得 $sum$。因为根据题意，有条件 $\textstyle\sum[p_i = -1] + \textstyle\sum[s_i = -1] = n$($1 \leq i \leq n$)，所以可得 引理 3：

$$\exists i \in N(0 \leq i \leq n),p_i \neq -1,s_{i+1} \neq -1$$

证明如下:  

假设 $\forall i \in N(0 \leq i \leq n)$，$p_i$ 或 $s_{i+1}$ 中有一个值为 $-1$.

$\because$ $p_0 = s_{n+1} = 0$.

$\therefore$ 有 $\textstyle\sum[p_i = -1] + \textstyle\sum[s_i = -1] = n + 1(1 \leq i \leq n)$，与条件矛盾.

$\therefore$ 假设不成立.

引理 3 得证.

于是根据 引理 3 和 引理 2，$O(n)$ 遍历一遍两个数组可以求得 $sum$，再根据 引理   2，$O(n)$ 遍历一遍两个数组就可以还原两个数组的一组合法解。还原过程如下：  
对于任意一对 $p_i$，$s_{i+1}$，分三种情况讨论:
1. $p_i$ 和 $s_{i+1}$ 都不为 $-1$，不做处理。
1. $p_i$ 和 $s_{i+1}$ 中有一个为 $-1$，用 $sum$ 异或另一个元素即可获得为 $-1$ 元素的值。
1. $p_i$ 和 $s_{i+1}$ 都为 $-1$，那么它们就没有确定的值。通过性质2可以发现，当把 $a_i$ 赋值为 $0$ 时，最易处理并且不违反任何条件。此时，$p_i = p_{i-1} \oplus 0 = p_{i-1}$，赋值完 $p_i$ 后，就变成了第2种情况，即可求得 $s_{i+1}$ 的值。

最后，根据 引理 1，遍历一遍 $p$ 数组或 $s$ 数组即可求得原数组的值。 

时间复杂度 $O(\textstyle\sum n)$，即可通过本题。
# 代码
```cpp
#include<iostream>

using namespace std;
#define ll long long //不要忘记开 ll 

ll p[100010];
ll s[100010];

ll find(int n) //查找 
{
	for (int i = 0; i <= n; i++)
		if (p[i] != -1 && s[i + 1] != -1)
			return p[i] ^ s[i + 1];
}

void update(ll val, int n) //还原 
{
	for (int i = 0; i <= n; i++)
	{
		if (p[i] != -1 && s[i + 1] == -1) 
			s[i + 1] = val ^ p[i];
		else if (p[i] == -1 && s[i + 1] != -1) 
			p[i] = val ^ s[i + 1];
		else if (p[i] == -1 && s[i + 1] == -1)
		{
			p[i] = p[i - 1];
			s[i + 1] = val ^ p[i];
		}
	}
}

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> p[i];
		for (int i = 1; i <= n; i++) cin >> s[i];
		
		ll sum = find(n); //查找所有数异或的结果，记为 sum 
		
		update(sum, n); //还原 p 数组和 s 数组 

		for (int i = 1; i <= n; i++)
			cout << (p[i] ^ p[i - 1]) << " "; //用 p 数组求原数组的值，也可以用 s 数组 
		cout << endl;
	}
	return 0;
}
```

---

## 作者：我是逍逍 (赞：3)

几个简单的性质：  
1. $a \oplus a = 0$  
2. $a \oplus 0 = a$  
3. $a \oplus b \oplus c = a \oplus (b \oplus c)$ 
4. $a \oplus b \oplus c = d \Leftrightarrow a \oplus b = d \oplus c$

由题意得：   
$p_i = \bigoplus_{j = 1}^i a_j$ , $s_i = \bigoplus_{j = i}^n a_j$  
结合上述性质，设 $E = \bigoplus_{i = 1}^n a_i$，可以推出：$p_i \oplus s_{i+1} = E \ , \ p_i \oplus s_i = E \oplus a_i$ 变形可得 $p_i = E \oplus a_i \oplus s_i$ 即 $a_i, p_i, s_i$ 知二求三。  
因此，我们可以根据上述性质尽可能推出已经被唯一确定的 $p_i, s_i, a_i$ 此步骤保证求出的 $p_i, s_i, a_i$ 不与输入数据冲突。  
对于剩下的未知量，是可以随便填的，证明很简单：假设只有唯一解，设为 $a_1, a_2$ （简化问题），那么，可以推出 $a_1 \oplus k, a2 \oplus k$ 同样是一组合法解，因为 $a_1 \oplus k \oplus a_2 \oplus k = a_1 \oplus a_2$ 。该填法对后续没有区别，不影响其他数据的填入，证毕。（当然，如果只有唯一解，那么也不会存在 SpecialJudge）。   
代码中为了方便起见，未知量填入 $1$ ，但亲测填入 $rand()$ 也能过。  
```cpp
#include <stdio.h>
  
const int Max = 100005;
long long t, n, p[Max], s[Max], a[Max], E;

int main() {
	scanf("%lld", &t);
	
	while (t--) {
		scanf("%lld", &n);
		
		for (int i = 1; i <= n; i++) 
			scanf("%lld", &p[i]);
		for (int i = 1; i <= n; i++) 
			scanf("%lld", &s[i]);
		
		for (int i = 0; i <= n; i++) 
			if (p[i] != -1 && s[i + 1] != -1) {
				E = p[i] ^ s[i + 1];
				break;
			}
		
		for (int i = 0; i <= n; i++) {
			if (p[i] == -1 && s[i + 1] != -1)
				p[i] = E ^ s[i + 1];
			else if (p[i] != -1 && s[i + 1] == -1) 
				s[i + 1] = E ^ p[i];
			else if (p[i] == -1 && s[i + 1] == -1) 
				p[i] = 1;
			if (i)
				printf("%lld ", p[i] ^ p[i - 1]);
		}
		puts("");
	}
}
```


---

## 作者：stntn (赞：3)

## 简要题意

有一个数列，给你它的前缀异或和数组 $p$ 和后缀异或和数组 $s$ 的部分数据，求还原任一满足的数列。

## 分析

关键在于 $\sum \left [ p_i=-1 \right ] + \sum \left [ s_i=-1 \right ]=n$，即 $-1$ 的数量不超过 $n$ 个。

易发现，若知道任意一组 $p_i$ 和 $s_{i+1}$ 我们便可以求出整个数组的异或和。

反之，如果知道任意 $p_i$ 或 $s_i$ 和异或和 $sum$ 便可对应求出 $s_{i+1}$ 或 $p_{i-1}$。

而对应原数组 $a$，由前缀的性质可得 $a_i=p_i \oplus p_{i-1}=s_{i+1} \oplus s_i$。 

于是我们可以：

1. 求出 $sum$。
1. 尽量还原 $s$ 和 $p$。
1. 尽量还原 $a$。

回到最开始的那个条件，可以发现，无论哪一组数据，均可以求出 $sum$ （即一定会有一组已知 $p_i$ 和 $s_{i+1}$ 相邻）。具体地，从 $1$ 到 $n$ 扫描一遍，若出现 $p_i$ 和 $s_{i+1}$ 都不为 $-1$，就可以求出 $sum=p_i \oplus s_{i+1}$。

```cpp
rep(i,1,n+1) if(~s[i]&&~p[i-1]) p[n]=s[1]=s[i]^p[i-1];
```
然后求出 $s$ 和 $p$，$a_i=p_i \oplus p_{i-1}=s_{i+1} \oplus s_i$。

```cpp
rep(i,1,n+1)
{
	if(~p[i-1]) s[i]=s[1]^p[i-1];
	if(~s[i]) p[i-1]=s[1]^s[i];
}
rep(i,1,n)
{
	if(~p[i]&&~p[i-1]) a[i]=p[i]^p[i-1];
	if(~s[i+1]&&~s[i]) a[i]=s[i+1]^s[i];
}
```
最后，对于无法求出的一些数位，~~乱搞即可~~根据个人喜好即可，我这里维护当前前缀和 $P$，若遇见有条件限制的 $p_i$，$a_i=P \oplus p_i$ 否则 $a_i=0$。

## CODE

```cpp
#include<bits/stdc++.h> 
#define N 100010
#define int long long
#define DB double
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define INF 0x3f3f3f3f
using namespace std;
template <typename T> inline void read(T &a)
{
	a=0;T w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=(a<<3)+(a<<1)+(ch^48);ch=getchar();}
	a*=w;
}
template <typename T,typename ...Args> void read(T &x,Args &...args){read(x);read(args...);}
int T,n,p[N],s[N],a[N],sum;
signed main()
{
	read(T);
	while(T--)
	{
		read(n);sum=0;
		rep(i,1,n) a[i]=-1;
		rep(i,1,n) read(p[i]);p[0]=0;
		rep(i,1,n) read(s[i]);s[n+1]=0;
		rep(i,1,n+1) if(~s[i]&&~p[i-1]) p[n]=s[1]=s[i]^p[i-1];
		rep(i,1,n+1)
		{
			if(~p[i-1]) s[i]=s[1]^p[i-1];
			if(~s[i]) p[i-1]=s[1]^s[i];
		}
		rep(i,1,n)
		{
			if(~p[i]&&~p[i-1]) a[i]=p[i]^p[i-1];
			if(~s[i+1]&&~s[i]) a[i]=s[i+1]^s[i];
		}
		rep(i,1,n)
		{
			if(~a[i]){printf("%lld ",a[i]);sum^=a[i];}
			else if(~p[i]) printf("%lld ",sum^=p[i]);
			else {printf("%lld ",sum);sum=0;}
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：GI录像机 (赞：3)

## 题意简述：

给出一个前缀异或和数组和一个后缀异或和数组，求任一满足条件的原数组。其中异或和数组值为 $−1$ 的无需考虑，**且输入中不为 $-1$ 的数的总数为原数组的长度**。

## 大体思路：
我们先想只有前缀异或和的情况。

因为任何数异或 $0$ 等于本身，所以我们可以把 $-1$ 的位置都填成 $0$。又因为异或运算满足结合律和交换律，再把有值的位置填成这个值与上一个非 $-1$ 的值的异或。（补充：异或运算有一个神奇的特性：若 $A\oplus B=C$，则 $B\oplus C=A$，哪怕不知道也很容易推出来）

那有后缀时呢？

我们考虑将后缀转化为前缀，因为 $A\oplus A=0$，所以我们只需将后缀异或上数组全部值的异或和，就能得到前缀。数据还贴心地将后缀的顺序倒过来。这样我们的后缀就能通过全部值的异或和转化为下标减一的前缀。

那又有问题来了，若前缀和数组最后一个值为 $-1$，后缀和数组第一个值为 $-1$，如何求出全部值的异或和呢？

我们看题目，发现有两个加粗的字：**一共**。接着看，有 $n$ 个 $-1$。也就是说，**有 $n$ 个有值的前缀或后缀**！据此我们可以推出，若前缀数组为 $x$，后缀数组为 $y$，且 $x_n\neq -1$，$y_1\neq -1$，存在一个 $i\in [1,n]$，使得 $x_i\neq -1$ 且 $y_{i+1}\neq -1$ 成立。

学过加法的你肯定知道，对于一个长度为 $n$ 的数组，它的元素总和为前 $i$ 个数的和与后 $n-i$ 个数的和之和。异或运算也是这样，它的元素异或和为前 $i$ 个数的异或和与后 $n-i$ 个数的异或和的异或和，因为它满足交换律和结合律。

我们用前缀异或和与后缀异或和求出总的异或和后，就能求出全部值的异或和啦！

## 参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define GICamera return 0;
long long read() {
	long long f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(long long x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 1e5 + 10;
long long p1[N], p2[N];
int main() {
	long long t = read();
	while (t--) {
		long long n = read();
		for (int i = 1; i <= n; i++)p1[i] = read();
		//找到全部值的异或和
		for (int i = 1; i <= n; i++) {
			p2[i] = read();
			if (p2[i] != -1 && p1[i - 1] != -1)p1[n] = p2[i] ^ p1[i - 1];
		}
		//把后缀转化为前缀
		for (int i = 1; i <= n; i++) {
			if (p2[i] == -1)continue;
			p1[i - 1] = p2[i] ^ p1[n];
		}
		//构造答案
		long long id = 0;
		for (int i = 1; i <= n; i++) {
			if (p1[i] == -1) {
				putchar('0');
				putchar(' ');
			} else {
				write(p1[i]^p1[id]);
				putchar(' ');
				id = i;
			}
		}
		putchar('\n');
	}
	GICamera
}
```


---

## 作者：LJ07 (赞：2)

## 题目描述

[题目传送门](https://www.luogu.com.cn/problem/P8279)

## 前言

本篇题解未考虑到 $\sum[p_i=-1]+\sum[s_i=-1]=n$ 的条件，与目前题解区的主流做法不同。

目前是Accepted，如有谬误请在讨论区指出，不胜感激。

## 思路简述

令 $S_i=\oplus _{i=1}^na_i=S_{i-1}\oplus a_i$，则有 $S_0=0$。

则有 $p_i=S_i\oplus S_0$, $s_i=S_n\oplus S_{i-1}$。

然后很容易的想到对于每一个 $S_i$ 建点，根据上述关系式进行连边，直接从 $S_0$ 搜索求出所有能求解的 $S_i$。

对于每一个没有遍历到的 $S_i$，随便赋值即可。

最后即可通过 $S_i$ 求解出 $a_i$。

时间复杂度为 $O(\sum n)$。

**注意不要偷懒使用```memset```清空数组，否则会TLE第一个点**。

## 丑陋の代码

[click here](https://www.luogu.com.cn/paste/dicjwp5g)

---

## 作者：Otomachi_Una_ (赞：2)

## 解题思路

~~这道题考场上想了30min，太菜了~~

有一个显然的结论：

$$a_i=p_i\bigoplus p_{i-1}=s_i\bigoplus s_{i+1}$$

轻轻地挪一下项变成：

$$p_i\bigoplus s_{i+1}=p_{i-1}\bigoplus s_i$$

那么因为题目中提到 

> 现在 Tommy 一共将 $p$ 和 $s$ 的 $n$ 个元素换成 $−1$。

也就是说我们必然能找到一个 $i\in[0,n]$ 使得 $p_i\not= -1,s_{i+1}\not = -1$ 记 $t=p_i\bigoplus s_{i+1}$。

然后只要找出这个值，其他有一半的构造另一半，两边都没有的一边设为 $0$ 一边设为 $t$ 即可。

最后 $a_i=p_i\bigoplus p_{i-1}$。

## 参考代码
```cpp
#include<iostream>
using namespace std;
#define ll long long
const int MAXN=1e5+5;
int T;
int n;ll s[MAXN],t[MAXN];
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>s[i];
		for(int i=1;i<=n;i++) cin>>t[i];
		ll xx=-1;
		for(int i=0;i<=n;i++) if(s[i]!=-1&&t[i+1]!=-1) xx=s[i]^t[i+1];
		if(xx==-1) xx=0;
		for(int i=0;i<=n;i++)
			if(s[i]!=-1) t[i+1]=xx^s[i];
			else if(t[i+1]!=-1) s[i]=xx^t[i+1];
			else s[i]=0,t[i+1]=xx;
		for(int i=1;i<=n;i++)
			cout<<(s[i]^s[i-1])<<" ";
		cout<<endl;
	}
}
```


---

## 作者：IvanZhang2009 (赞：1)

首先根据题意我们可以知道

$p_i\oplus s_{i+1}$

$=(a_1\oplus a_2\oplus\dots\oplus a_i)\oplus(a_{i+1}\oplus a_{i+2}\oplus\dots\oplus a_n)$

$=a_1\oplus a_2\oplus\dots\oplus a_n$

设上述结果为 $x$。如果我们知道了 $x$ 的值和 $p_i$ 的值，那么由 

$a\oplus b=c \Rightarrow a=b\oplus c$ 或 $b=a\oplus c$

就可以推导出 $s_{i+1}=x\oplus p_i$。

同理如果知道了 $x$ 的值和 $s_{i+1}$ 的值也可以推出 $p_i=x\oplus s_{i+1}$。

那么我们最想要知道的就是 $x$ 的值。

很显然，$x=p_{n}=s_1$，那么如果两个数中有任意一个已经知道了，那么就相当于我们得知了 $x$ 的值。

那如果 $p_{n}=s_1=-1$，那么剩下 （$2\cdot n-2$） 个数里只有 （$n-2$） 个数我们不知道。那么就必然可以找到正整数 $i$ 使得 $p_i\neq-1$ 且 $s_{i+1}\neq-1$，那么可以得到 $x=p_i\oplus s_{i+1}$。

于是我们得到了 $x$。

还记得我们求 $x$ 的目的吗？

这个时候我们跑一遍 $p$ 和 $s$，看看如果哪一个数我们是得知的，就可以相应地推出它对应的数。即根据 $p_i$ 推出 $s_{i+1}$，根据 $s_i$ 推出 $p_{i-1}$。这样我们尽可能多地还原了数组 $p$ 和 $s$。

~~好的我们应该已经得知了两个数组里的所有数了吧我们写个代码就成功了~~

等等，我说**尽可能多**，那么数组里还有一些数我们不知道，也就是仍然存在 $i$ 使得 $p_i=s_{i+1}=-1$。

这个时候这个数它已经不重要了，我们只需要令 $p_i=0$，$s_{i+1}=x$ 就行了。这个时候我们的任意赋值不会影响到两个数组中其它的数字，所以这样我们就可以将两个数组中所有的 -1 还原。

然后就快乐地输出啦！

~~等等，好像输出我也不会~~

因为 $p_i=a_1\oplus a_2\oplus\dots\oplus a_i$，所以 $a_i=p_{i}\oplus p_{i-1}$（$i>1$)，而 $a_1=p_1$。

所以直接输出就好了!

## 代码
```cpp
#define REP(i,b,e)  for(int i=(b);i<(e);++i)
int n;
int a[100005],b[100005];//a,b是题目中的p,s数组
int c[100005];//c是原数组
void Main() {
	cin>>n;
	REP(i,0,n)cin>>a[i];
	REP(i,0,n)cin>>b[i];
	if(n==1){
		if(a[0]==-1)cout<<b[0]<<endl;
		else cout<<a[0]<<endl;
		return;
	}
	if(a[n-1]!=-1)b[0]=a[n-1];   //推导x,代码里直接将x表示成b[0]或a[n-1]
	else if(b[0]!=-1)a[n-1]=b[0];
	else{
		REP(i,0,n-1){
			if(a[i]!=-1&&b[i+1]!=-1){
				b[0]=a[n-1]=a[i]^b[i+1];
				break;
			}
		}
	}
	REP(i,0,n-1)
	if(a[i]==-1&&b[i+1]==-1)a[i]=0,b[i+1]=b[0];
	else if(a[i]==-1)a[i]=b[0]^b[i+1];
	else if(b[i+1]==-1)b[i+1]=b[0]^a[i];
	REP(i,0,n)if(a[i]!=-1&&b[i]!=-1&&c[i]==-1)c[i]=a[i]^b[i]^a[n-1];
	REP(i,1,n)
	c[i]=a[i]^a[i-1];
	c[0]=a[0];
	REP(i,0,n)cout<<c[i]<<' ';
	cout<<endl;
}
```

---

## 作者：3a51_ (赞：1)

首先，对于 $p_i$ 与 $s_{i+1}$，可以得到 $\forall i\;p_i\oplus s_i=p_n=s_1$。因为隐藏的个数最多 $n$ 个，而相等的对数总共 $n+1$ 个，所以一定能得到这个结果，记为 $ans$。接下来可以将那些不是均为 $-1$ 的对数填满。剩余的都是 $-1$ 的呢？可以随便填。证明如下：

因为影响到 $p_i$ 与 $s_{i+1}$ 的因素只有 $ans$，所以可以保证每一组 $p_i$ 与 $s_{i+1}$ 独立。这样考虑这一组的时候就不用考虑别的组了。

`code`:
```cpp
#include<bits/stdc++.h>
#define int long long
#define Tothetime_tolife using
#define AK namespace
#define IOI std
Tothetime_tolife AK IOI;
const int Mod1=998244353;
const int Mod2=1000000007;
int gcd(int a,int b){return __gcd(a,b);}
int lcm(int a,int b){return a*b/gcd(a,b);}
void read(int &x){x=0;char ch=' ';while(ch>'9' || ch<'0'){ch=getchar();}while(ch>='0' && ch<='9'){x=x*10+ch-'0';ch=getchar();}return;}
void write(int x){if(x>9){write(x/10);}putchar(x%10+'0');return;}
const int N=100005;
int t,n,p[N],s[N],a[N],ans;
signed main()
{
	read(t);
	while(t--){
		ans=-114514;
		read(n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&p[i]);
		}
		for(int i=1;i<=n;i++){
			scanf("%lld",&s[i]);
		}
		for(int i=1;i<n;i++){
			if(p[i]!=-1 && s[i+1]!=-1){
				ans=p[i]^s[i+1];
				break;
			}
		}
		if(ans==-114514){
			if(p[n]!=-1) ans=p[n];
			else ans=s[1];
		}
		s[1]=ans;p[n]=ans;
		for(int i=1;i<n;i++){
			if(p[i]==-1 && s[i+1]!=-1){
				p[i]=ans^s[i+1];
			}else if(p[i]!=-1 && s[i+1]==-1){
				s[i+1]=ans^p[i];
			}
		}
		for(int i=1;i<n;i++){
			if(p[i]==-1 && s[i+1]==-1){
				p[i]=ans/2;s[i+1]=ans^p[i];
			}
		}
		for(int i=1;i<=n;i++){
			a[i]=p[i]^p[i-1];
			printf("%lld ",a[i]);
		}
		printf("\n");
	}
	return 0;
}

```

---

## 作者：wwz1428572008 (赞：0)

## 做题思路
由题意可知，每组数据有 $n$ 个不是 $-1$ 的元素。设 $xsum=a_1\oplus a_2\oplus\dots\oplus a_n$。所以：
1. $p_n\ne -1$，此时 $xsum=p_n$。
2. $s_1\ne -1$，此时 $xsum=s_1$。
3. $p_n=-1$ 且 $s_1=-1$，此时将其余元素分为 $n-1$ 组，第 $i$ 组为 $p_i$ 与 $s_{i+1}$。那么，在这 $n-1$ 个组中有 $n$ 个不为 $-1$。所以，必定有一组中两个元素都不是 $-1$，设它是第 $i$ 组。则 $xsum=p_i\oplus s_{i+1}$。

这时，我们就可以利用 $xsum$ 将一些 $p_i$ 通过 $s_{i+1}$ 推算出来。然后就和第一题的方法类似了，只是把加法换成异或。
注意要用 `long long`。
### 代码
```cpp
#include<iostream>
using namespace std;
long long p[100002],s[100002];
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>p[i];
		for(int i=1;i<=n;i++)
			cin>>s[i];
		long long tot=0;
		if(p[n]!=-1)
			tot=p[n];
		else if(s[1]!=-1)
			tot=s[1];
		else
		{
			for(int i=1;i<n;i++)
				if(p[i]!=-1 && s[i+1]!=-1)	tot=p[i]^s[i+1];
		}
		for(int i=1;i<n;i++)
			if(p[i]==-1 && s[i+1]!=-1)	p[i]=tot^s[i+1]; 
		if(p[n]==-1)	p[n]=tot;
		long long len=0,cur=0;
		for(int i=1;i<=n;i++)
		{
			if(p[i]!=-1)
			{
				if(p[i-1]!=-1)
					cout<<(p[i]^p[i-1])<<' ';
				else
				{
					for(int i=1;i<=len;i++)
						cout<<0<<' ';
					cout<<(p[i]^cur)<<' ';
				}	
			}
			else
			{
				if(p[i-1]!=-1)
					cur=p[i-1],len=1;
				else
					len++;
			}
		}
	}
	return 0;
}
```

---

## 作者：qscisQJing (赞：0)

本蒟蒻第一篇~~水题~~题解 如有错误欢迎指正~



------------
# [P8279](https://www.luogu.com.cn/problem/P8279)
很显然，我们有这个式子
$p_i \bigoplus p_{i+1}= a_{i+1}$

和这个式子$s_{i+1} \bigoplus s_{i+2}= a_{i+1}$

也就是说$p_i \bigoplus p_{i+1} =s_{i+1} \bigoplus s_{i+2}$

移一下项后 $p_i \bigoplus s_{i+1}= p_{i+1} \bigoplus s_{i+2}$

不难发现，$p$的下标和$s$的下标分别加了$1$

所以 $p_1 \bigoplus s_2= p_2 \bigoplus s_3 = \dots=p_{n-1} \bigoplus s_n$

这是个很有用的式子，结合"现在 Tommy 一共将 $p$和$s$的$n$个元素换成$-1$"我们可以知道必然有组$p_i,p_{i+1}$或$s_i,s_{i+1}$或$p_i,s_{i+1}$是已知的

接着直接还原就可以了


如果$p_i,p_{i+1},s_i,s_{i+1}$中有已知的，直接和已知的值异或就可以了

如果全部都是$-1$就随便设一个 ~~反正是spj~~

（完）

---

## 作者：Qiaoqia (赞：0)

来一种不需要依赖 -1 个数是 $n$ 的做法。

先把后缀异或转换成若干段异或和（即非 -1 位置之间的段），然后从头往后做，如果如果有前缀的限制就填满足前缀限制的，有中间一段限制就填中间一段限制的。  
但这样有一个问题，虽然填一个数字一定可以满足一个限制，但如果一个位置同时有两个限制就不行了，在这种情况下，可以把一段的限制异或上和它结尾重合的那个前缀限制，这样就转换成了另一个前缀限制，因为保证有解，所以一定不会再和前面产生冲突了。

这样转换完毕后有限制就填满足限制的数，否则填 $0$ 即可。

```cpp
void solve() {
    int n;

    std::cin >> n;
    
    std::vector<long long> p(n + 2), s(n + 2), a(n + 2);
    std::vector<long long> pre(n + 2), lim(n + 2);
    
    for (int i = n, lst = n + 1; i >= 1; i--) {
        if (s[i] == -1) continue;
        pre[lst - 1] = i - 1, lim[lst - 1] = s[i] ^ s[lst];
        if (p[i - 1] != -1) p[lst - 1] = p[i - 1] ^ lim[lst - 1];
        if (p[lst - 1] != -1) p[i - 1] = p[lst - 1] ^ lim[lst - 1];
        lst = i;
    }
    
    for (int i = 1; i <= n; i++) 
        if (p[i] != -1) a[i] = p[i] ^ p[i - 1];
        else if (pre[i]) {
            a[i] = lim[i] ^ p[i - 1] ^ p[pre[i]];
            p[i] = p[i - 1] ^ a[i];
        }
        else p[i] = p[i - 1];
        
    for (int i = 1; i <= n; i++) std::cout << a[i] << ' ';
    std::cout << '\n';
}
```

---

## 作者：_lmh_ (赞：0)

### 题目大意
给定一个长度为 $n$ 数组 $\{a_i\}$ 的前缀异或数组 $\{p_i\}$ 及后缀异或数组 $\{s_i\}$，将这 $2n$ 个数中的 $n$ 个替换为 $-1$，还原这个数组。

### 解法
将这 $2n$ 个数分为 $n+1$ 组，分别为 $\{q_1\},\{p_1,q_2\},\{p_2,q_3\},\cdots,\{p_{n-1},q_n\},\{p_n\}$，易得其中每个有两个数的组的两个数异或后的值或其余两组中的数的值都是相等的，且都是原数组全部元素异或后的值。

但是，一共只去掉了 $n$ 个数，所以必定有一组所有数全部已知，所以可以求出原数组全部元素异或后的值。

之后，看中间有两个数的 $n-1$ 组，如果其中有一个数已知，就把另一个数也推出来，最后，$n-1$ 组中要么两个数全部未知，要么全部已知。

之后，注意到 $0 \leq a_i < 2^{60}$，所以要开 long long，且可以将部分数取零。

所以，如果 $p_i$ 已知，$a_i$ 就取 $p_i$ 与上一个已求的 $p$ 中的元素；否则，$a_i$ 就取零。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,p[100007],q[100007],T,t;
long long read() {
  long long x=0,w=1;
  char ch=0;
  while (ch<'0'||ch>'9') {
    if (ch=='-') w=-1;      
    ch=getchar();             
  }
  while (ch>='0'&&ch<='9') {
    x=(x<<3)+(x<<1)+(ch-'0');
    ch=getchar();
  }
  return x*w;
}
int main(){
	T=read();
	while(T--){
		n=read();
		for (register int i=1;i<=n;++i) p[i]=read();
		for (register int i=1;i<=n;++i) q[i]=read();
		if (q[1]>=0) p[n]=q[1];if (p[n]>=0) q[1]=p[n];
		if (!(p[n]>=0&&q[1]>=0)) for (register int i=1;i<=n;++i){
			if (p[i]>=0&&q[i+1]>=0) {
				p[n]=p[i]^q[i+1];break;
			}
		}
		for (register int i=1;i<=n;++i){
			if (q[i+1]>=0) p[i]=q[i+1]^p[n];
		}
		t=0;
		for (register int i=1;i<=n;++i){
			if (p[i]>=0){
			    printf("%lld ",p[i]^p[t]);t=i;
			}
			else {putchar('0');putchar(' ');}
		} 
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：FoxT (赞：0)

### 题目大意

给出一个数组 $a$ 的前缀异或数组 $p$ 和后缀异或数组 $s$ ，其中有若干个未知元素，输出一个符合条件的原数组，数据保证有解。

### 题目思路

首先根据前缀数组和后缀数组的定义，可得：

$\forall 1 < i < n,p_i \oplus s_{i+1} = a_1 \oplus a_2 \oplus ... \oplus a_n = p_n = s_1$

于是我们可以根据 $s_1$ 或 $p_n$ 的取值来确定任意一组 $p_i \oplus s_{i+1}$ 的取值。

注意：若 $s_1$ 和 $p_n$ 均未给出，可对其赋任意值。

进而可以根据 $p_i$ 得到 $s_{i+1}$ ，反之同理。

注意：若此组 $p_i$ 和 $s_{i+1}$ 的值均未给出，可对其中之一赋任意值再同上计算 

从而我们可以得到整个数组 $s$ 和 $p$ ，于是很容易可以得到一个符合条件的原数组 $a$


### 代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
#define MAX_N 100010
#define int long long
int t,p[MAX_N],s[MAX_N];
signed main(){
	// ios::sync_with_stdio(false);
	scanf("%lld",&t);
	while(t--){
		int n;
		scanf("%lld",&n);
		for(int i = 1;i <= n;i++)scanf("%lld",&p[i]);
		for(int i = 1;i <= n;i++)scanf("%lld",&s[i]);
		int a = -1;
		if(p[n] != -1)a = p[n];
		else if(s[1] != -1)a = s[1];
		else{
			for(int i = 1;i < n;i++){
				if(p[i] != -1 && s[i + 1] != -1)
					a = p[i] ^ s[i + 1];
			}
		}
		if(a == -1)
			a = 1;
		p[n] = a;
		s[1] = a;
		for(int i = 1;i < n;i++){
			if(p[i] == -1 && s[i + 1] == -1){
				p[i] = 1;
				s[i + 1] = a ^ p[i];
			}
			else if(p[i] == -1)
				p[i] = a ^ s[i + 1];
			else
				s[i + 1] = a ^ p[i];
		}
		printf("%lld ",p[1]);
		for(int i = 2;i <= n;i++)
		    printf("%lld ",(p[i] ^ p[i - 1]));
		putchar('\n');
	}
	return 0;
}
```


### 后记

Updata 2022.4.13. 完成题解

---

## 作者：西湖水妖 (赞：0)

### 题目描述

+ 有一个长度为 $n$ 的整数数组 $a$。
+ $p,s$ 分别为这个数组的前缀、后缀异或和，即 $\forall i\in\mathbf{Z}\wedge1\le i\le n,p_i=a_1\oplus a_2\oplus\cdots\oplus a_i,s_i=a_i\oplus a_{i+1}\oplus\cdots\oplus a_n$。
+ 有一些前缀、后缀异或和未知，用 $-1$ 表示。刚好有 $n$ 个前缀、后缀异或和已知。
+ $1\le n\le10^5,\forall i\in\mathbf{Z}\wedge1\le i\le n,0\le a_i<2^{60}.$
+ 你只需要其中一个答案即可，保证至少有一个解。

### 题目分析

异或的性质大家都清楚吧，不清楚建议先查一下。

首先考虑没有后缀和的情况，和 A 题类似，输入的时候记录上一个异或和的值，当前的数字 $=-1\Rightarrow$ 直接输出 $0$，否则输出当前数字异或上一个异或和的值即可。

现在加入后缀和，我们只需要想办法把所有后缀和都转成前缀和就行了。发现只要求出整个数组的异或和，然后把它分别异或上每个后缀和的情况就可以得到它对应的前缀和。

怎么求总和呢？我们发现，$p_n$ 已经给出 $\vee s_n$ 已经给出 $\Rightarrow$ 整个数组的和可以轻松得出。$p_i$ 已经给出 $\wedge$ $s_{i+1}$ 已经给出 $\Rightarrow$ 总和也能得出，为 $p_i\oplus s_{i+1}$。

总和一定可以通过这种方式得出吗？答案是肯定的。为了方便描述，下面把 $s$ 数组左移一位，变成 $s_0,s_1\cdots s_{n-1}$。于是上面的算法就可以进一步简化。

我们可以得出，总和可以求出 $\Leftrightarrow\exists i\in\mathbf{Z}\wedge0\le i\le n,p_i$ 已经给出 $\wedge s_i$ 已经给出。考虑 $p_0,s_n$ 的实际意义，它们都是 $0$，所以已经给出。

接着会使用到[鸽巢原理](https://mp.weixin.qq.com/s?__biz=MzU3NTg3MTYyMQ==&mid=100006133&idx=6&sn=ef5ab6480b0a78ca09599402d233586c&scene=19#wechat_redirect)。小学数学书上有，忘了可以点击链接学习（其实不学也行）。我们根据上面的结论，发现一共有 $0\sim n$ 这 $n+1$ 种对应的关系，满足其中一条就可以得到总和。因为输入给出了 $n$ 个已知条件，我们又制造了两个已知条件（$p_0,s_n$），所以一共有 $n+2$ 个已知条件，至少会有两个已知条件对应，因此总和一定可以通过这种方式得出。

具体实现可以看代码

```cpp
//这里已经按照上面讲的左移过的顺序进行读入。
for(auto i = p.begin(), j = s.begin(); i != p.begin() + n + 1; ++ i, ++ j)
    if(*i != - 1 && *j != - 1)
    {
        sum = *i ^ *j; //如果两个都给出了，算出总和。
        break;
    }
last = 0;
for(auto i = p.begin() + 1, j = s.begin() + 1; i != p.begin() + n + 1; ++ i, ++ j)
{
    if(*j != - 1)
        *i = sum ^ *j;
    ++ cnt; //因为后面用了前置的递减，所以这里必须先加一下，同时也方便没有给出的情况。
    if(*i == - 1) //如果没有给出，那么增加一下计数器，方便之后输出 0。
        continue;
    while(-- cnt) //没有给出的全部输出 0。
        cout << "0 ";
    cout << (*i ^ last) << " "; //输出当前的答案。
    last = *i;
}
```


---

