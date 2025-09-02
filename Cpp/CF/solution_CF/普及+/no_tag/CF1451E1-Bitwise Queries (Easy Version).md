# Bitwise Queries (Easy Version)

## 题目描述

The only difference between the easy and hard versions is the constraints on the number of queries.

This is an interactive problem.

Ridbit has a hidden array $ a $ of $ n $ integers which he wants Ashish to guess. Note that $ n $ is a power of two. Ashish is allowed to ask three different types of queries. They are of the form

- AND $ i $ $ j $ : ask for the [bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND) of elements $ a_i $ and $ a_j $ $ (1 \leq i, j \le n $ , $ i \neq j) $
- OR $ i $ $ j $ : ask for the [bitwise OR](https://en.wikipedia.org/wiki/Bitwise_operation#OR) of elements $ a_i $ and $ a_j $ $ (1 \leq i, j \le n $ , $ i \neq j) $
- XOR $ i $ $ j $ : ask for the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of elements $ a_i $ and $ a_j $ $ (1 \leq i, j \le n $ , $ i \neq j) $

Can you help Ashish guess the elements of the array?

In this version, each element takes a value in the range $ [0, n-1] $ (inclusive) and Ashish can ask no more than $ n+2 $ queries.

## 说明/提示

The array $ a $ in the example is $ [0, 0, 2, 3] $ .

## 样例 #1

### 输入

```
4

0

2

3```

### 输出

```
OR 1 2

OR 2 3

XOR 2 4

! 0 0 2 3```

# 题解

## 作者：henrytb (赞：4)

这题真滴好玩。

首先，根据 $\oplus$ 的一个性质：$(a\oplus b)\oplus(b\oplus c)=a\oplus c$，我们可以耗费 $n-1$ 次询问来求所有的 $a_i\oplus a_{i+1}$。然后我们只需要求出 $a_1$ 就可以推出所有的 $a$ 了。

推推式子可以发现两个好玩的结论：

$$a\& b+a\oplus b=a|b$$

$$a\& b+a|b=a+b$$

于是，我们可以再询问 $a_1|a_2$、$a_2|a_3$、$a_1|a_3$。

然后就可以推推式子，求出 $a_1$ 了。

代码：

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int n,xors[100005],a12,a23,a13;
int main(){
    scanf("%d",&n);
    rep(i,1,n-1) {
        printf("XOR %d %d\n",i,i+1);
        fflush(stdout);
        scanf("%d",&xors[i]);
    }
    printf("OR 1 2\n");
    fflush(stdout);
    scanf("%d",&a12);
    printf("OR 2 3\n");
    fflush(stdout);
    scanf("%d",&a23);
    printf("OR 1 3\n");
    fflush(stdout);
    scanf("%d",&a13);
    int sum12=a12+a12-xors[1];
    int sum23=a23+a23-xors[2];
    int sum13=a13+a13-(xors[1]^xors[2]);
    int summ=sum12+sum23+sum13;summ/=2;
    int now=summ-sum23;
    printf("! %d ",now);
    rep(i,1,n-1) {
        now^=xors[i];
        printf("%d ",now);
    }
    puts("");
    return 0;
}
```

---

## 作者：EnofTaiPeople (赞：3)

此题本质与 CF1556D 相同，只是多了一个异或的询问。大家可以先看一下 [这篇文章](https://www.luogu.com.cn/blog/lwxde/solution-cf1556d)。

相比起来，多了一个异或的查询，看到只能问 $n+1$ 次，不难想到只有对每个 $2\le i\le n$ 询问 XOR 1 i，这时，我们只剩下 2 次询问次数，需要将 $a_1$ 求出来。不同的是，这题的值域是确定的，我们可以有目的地去询问。

先考虑非特殊情况，即前 n-1 次询问的结果都在 $[1,n-1]$ 之间，且没有重复，虽然没有与 $a_1$ 完全相等的数，但我们可以寻找与 $a_1$ 大部分相近或大部分相反的数进行询问。1 是很容易想到的，如果 $a_i\operatorname{xor}a_1=1$，这表示 $a_1$ 和 $a_i$ 在二进制下只有最后一位不相等，这时我们耗费一次询问，求他们的与，结果就是出去最后一位的 $a_1$。如何求 $a_1$ 的最后一位？考虑与 $a_1$ 只有最后一位相等的数字，即 $a_i\operatorname{xor}a_1=n-2$ 在询问他们的与，结果就是 $a_1$ 的最后一位。

既然有非特殊情况，那么就一定有特殊情况了。

- 若存在 $i$，使得 $a_i\operatorname{xor}a_1=0$，这时有 $a_i=a_1$，询问他们的与，结果就是 $a_1$；
- 若存在 $x,y,x\neq y$ 使得 $a_x\operatorname{xor}a_1=a_y\operatorname{xor}a_1$，这时有 $a_x=a_y$，询问 $a_x \& a_y$，得到 $a_x$，进而得到 $a_1$。

求出 $a_1$ 之后，由异或运算的自反律，可以轻易得到 $a_2$~$a_n$。

代码如下：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
int Xor[100005],i,n,Map[100005],a1,x;
bool flag=true;
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	for(i=2,cin>>n;i<=n;++i){
		cout<<"XOR 1 "<<i<<endl;cout.flush();cin>>Xor[i];
		if(flag)
			if(Map[Xor[i]]){
				cout<<"AND "<<Map[Xor[i]]<<" "<<i<<endl;
				cout.flush();cin>>x;a1=x^Xor[i];flag=false;
			}else if(Xor[i]==0){
				cout<<"AND 1 "<<i<<endl;cout.flush();
				cin>>a1;flag=false;
			}
		Map[Xor[i]]=i;
	}
	if(flag){
		for(i=2;i<=n;++i)
			if(Xor[i]==1){
				cout<<"AND 1 "<<i<<endl;cout.flush();
				cin>>x;a1|=x;
			}else if(Xor[i]==n-2){
				cout<<"AND 1 "<<i<<endl;cout.flush();
				cin>>x;a1|=x;
			}
	}
	for(i=2,cout<<"! "<<a1;i<=n;++i)
		cout<<" "<<(a1^Xor[i]);
	cout<<endl;
	return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

两个关于位运算的结论：$(a\ | \ b)-(a\ \&\ b)=a\oplus b,(a\ | \ b)+(a\ \&\ b)=a+b$。

先询问 $a_1\ |\ a_2,a_2\ |\ a_3,a_1\ |\ a_3,a_1\oplus a_2,a_2\oplus a_3$，可以求出 $a_1+a_2,a_2+a_3,a_1+a_3$，于是 $a_2=\dfrac{(a_1+a_2)+(a_2+a_3)-(a_1+a_3)}{2}$。

都知道序列中的一个数了，剩下的就很好办了，利用相邻元素的异或值还原出整个序列即可。

刚好 $n+2$ 次操作。

# Code
```cpp
#include<bits/stdc++.h>
int ans[65537];
int n,a,b,c,d,e;
int main(){
	scanf("%d",&n);
	puts("OR 1 2");fflush(stdout);
	scanf("%d",&a);
	puts("OR 2 3");fflush(stdout);
	scanf("%d",&b);
	puts("OR 1 3");fflush(stdout);
	scanf("%d",&c);
	puts("XOR 1 2");fflush(stdout);
	scanf("%d",&d);
	puts("XOR 2 3");fflush(stdout);
	scanf("%d",&e);
	ans[2]=(((a<<1)-d)+((b<<1)-e)-((c<<1)-(d^e))>>1);
	ans[1]=((a<<1)-d)-ans[2];
	ans[3]=((b<<1)-e)-ans[2];
	for(int i=4;i<=n;++i){
		printf("XOR %d %d\n",i-1,i);fflush(stdout);
		scanf("%d",&a);ans[i]=ans[i-1]^a;
	}
	putchar('!');
	for(int i=1;i<=n;++i)
		printf(" %d",ans[i]);
	fflush(stdout);
	return 0;
}
/*
(a|b)-(a&b)=(a^b),(a|b)+(a&b)=a+b
a+b=2(a|b)-(a^b)
*/
```

---

## 作者：wmy_goes_to_thu (赞：1)

水题。

首先，与，或，异或哪个功能最强大？肯定是异或。所以先得到 $a_1 \oplus a_i$ 的值，这样花费了 $n-1$ 步。

因为 $a_i \in [0,n-1]$，根据鸽巢原理，所以只分为两种情况，一种是 $\exists \ i,j, \ s.t. \ a_i=a_j$，另一种是 $\forall \ i,j \ , a_i \ !=a_j$。

对于第一种情况，很容易找出一组 $i,j$，我们可以得到它们的 AND 值，这样就可以求出 $a_1$，即可求出 $a_i$，一共是 $n$ 步。

对于第二种情况，肯定有 $t_1,t_2$，使得 $a_1 \oplus a_{t_1}=1,a_1 \oplus a_{t_2}=n-1$。我们只需要得到 $a_1 \ or \ a_{t_1}$ 和 $a_{t_1} \ and \ a_{t_2}$，就可以了。具体怎么做呢：

根据 $a_1 \ or \ a_{t_1}$，可以求出 $a_{t_1}$ 的前面若干位（不包括最后一位），通过 $a_{t_1} \ and \ a_{t_2}$ 可以求出最后一位，合在一起就是 $a_{t_1}$ 的值，即可求出 $a_1$，一共是 $n+1$ 步。

最后放代码（这个代码是赛场写的，有点冗长）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int x[1000005],y[1000005];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<n;i++)
	{
		printf("XOR %d %d\n",i,i+1);
		fflush(stdout);
		int aa;
		cin>>aa;
		x[i+1]=x[i]^aa;
	}
	for(int i=1;i<=n;i++)y[i]=x[i];
	sort(y+1,y+n+1);
	int ls=0,t1=0,t2=0;
	for(int i=1;i<n;i++)if(y[i]==y[i+1])ls=i;
	if(!ls)
	{
		int tt1=0,tt2=0;
		for(int i=1;i<=n;i++)
		{
			if(x[i]==1)tt1=i;
			else if(x[i]+1==n)tt2=i;
		}
		printf("OR %d %d\n",1,tt1);
		fflush(stdout);
		int a1;
		cin>>a1;
		printf("AND %d %d\n",tt1,tt2);
		fflush(stdout);
		int a2;
		cin>>a2;
		int xx1=x[tt1]^((a1-a1%2)+a2);
		printf("!");
		for(int i=1;i<=n;i++)printf(" %d",xx1^x[i]);
		printf("\n");
		fflush(stdout);
		return 0;
	}
	ls=y[ls];
	for(int i=1;i<=n;i++)if(x[i]==ls)
	{
		if(t1)t2=i;
		else t1=i;
	}
	printf("AND %d %d\n",t1,t2);
	fflush(stdout);
	int yu,xxx=0;
	cin>>yu;
	for(int i=15;i>=0;i--)xxx|=(1ll<<i)*(((yu>>i)&1)^((x[t1]>>i)&1));
	printf("!");
	for(int i=1;i<=n;i++)printf(" %d",xxx^x[i]);
	printf("\n");
	fflush(stdout);
	return 0;
}
```

---

## 作者：H6_6Q (赞：1)

## [1451E1 - Bitwise Queries (Easy Version)](https://codeforces.com/contest/1451/problem/E1)

### 题目大意

有一个 $n$ 个数的序列，每次可以询问任意两个数的 与 或 异或 的值，最多可以询问 $n+2$ 次，将这个序列还原出来。

### 解题思路

如果知道了其中一个数的值，那么其他所有数都可以通过询问与它的异或得出，所以关键在于怎么求出一个确定的值。

假设有三个数 $a,b,c$，那么可以感性理解：

$a \land b$ , $b \land c$ , $a \land c$ 就是二进制下两个数同是 $1$ 的部分。

$a \otimes b$ , $a \otimes c$ 就是两个数二进制下两个数不同的部分。

$(a \land b) \lor (a \land c)$ 就是 $a$ 与 $b$ 或 $c$ 共有部分，且肯定包含在 $a$ 的二进制中。

$(a \otimes b) \lor (a \otimes c)$ 就是 $a$ 与 $b$ 和 $c$ 不同部分的并，显然它也可以表示为 $b \land c$ 和 $a$ 中 $b,c$ 都没有的部分 的并。

$((a \otimes b) \lor (a \otimes c)) \otimes (b \land c)$ 就是 $a$ 中 $b,c$ 都没有的部分。

$((a \land b) \lor (a \land c)) \lor (((a \otimes b) \lor (a \otimes c)) \otimes (b \land c))$ 就是 $a$ 与 $b$ 或 $c$ 的共有部分 和 $a$ 中 $b,c$ 都没有的部分的并，也就是 $a$。

这样只要查询 $a \land b$ , $b \land c$ , $a \land c$ , $a \otimes b$ , $a \otimes c$ 共 $5$ 次就能知道其中的一个数，又知道这个数与另外两个数的异或，所以也能知道另外两个数，即知道了 $3$ 个数。

那么剩下的 $n-3$ 个数只要查询 $n-3$ 次与 $a$ 的异或就能求出来。

共 $5+n-3=n+2$ 次查询。

### Code
```cpp
const int N=1e5+5;
int n,a[N];

signed main()
{
	n=read();
	printf("AND 1 2\n");fflush(stdout);
	int p1=read();
	printf("AND 1 3\n");fflush(stdout);
	int p2=read();
	printf("XOR 1 2\n");fflush(stdout);
	int p3=read();
	printf("XOR 1 3\n");fflush(stdout);
	int p4=read();
	printf("AND 2 3\n");fflush(stdout);
	int p5=read();
	a[1]=((p1|p2)|((p3&p4)^p5));
	a[2]=(a[1]^p3);
	a[3]=(a[1]^p4);
	for(int i=4;i<=n;++i)
	{
		printf("XOR 1 %lld\n",i);fflush(stdout);
		int tmp=read();
		a[i]=(a[1]^tmp);
	}
	fflush(stdout);
	printf("! ");
	for(int i=1;i<=n;++i)
	{
		printf("%lld",a[i]);
		if(i!=n) printf(" ");
	}
	return 0;
}
```

---

## 作者：dead_X (赞：1)

## 前言
我用两种完全不同的方法切了 E1 和 E2，因此题解也会同时介绍两种方法。
## 思路
显然，已知 $a$ 和 $a\oplus b$ 是可以推出 $b$ 的。所以如果我们求出了一个数，剩下的数也能水落石出。

然后我们想一下如何求出某一个数。

在两个数上比较显然不现实，因为每一位在哪个数上都不能确定。

举个例子：$(10\blue{0}1,10\blue{1}0)$ 和 $(10\red{1}1,10\red{0}0)$ 的三种位运算完全相同。

因此我们要**三个数**，即数列的前三项，记为 $a,b,c$。

至于三个数，我们就可以乱来了。一种可行的方法是求出 $a\&b,a\oplus b,b\&c,b\oplus c,a|b$ 。

不妨记作 $A,X,B,Y,F$，再记 $X\oplus Y=Z$，我们来一波推理。

下面均根据这五个数的某一位考虑，即每个数只能是 $1$ 和 $0$。

### Case 1: $Z=1$

即 $a,c$ 中一个是 $1$，我们考虑 $b$。

如果 $X=1$，$a,b$ 都是 $1$，$c$ 是 $0$。

如果 $Y=1$，$b,c$ 都是 $1$，$a$ 是 $0$。

如果 $X=0,\ Y=0$，那么 $b$ 必然是 $0$，如果 $A=1$ 则 $a$ 是 $1$，如果 $B=1$ 则 $b$ 是 $1$。
### Case 2: $Z=0$

那么 $a,c$ 要么全是 $1$，要么全是 $0$。

如果 $F$，$a,c$ 都是 $1$，不然都是 $0$。

如果 $a,c$ 都是 $1$，看看 $X$ 就知道 $c$ 是几了。

如果 $a,c$ 都是 $0$，看看 $X$ 也知道 $c$ 是几了。

至此，我们已经知道了 $a,b,c$，剩下的数只要求出与 $a$ 的异或再异或上 $a$ 就是它自己了。

该算法共用了 $5+(n-3)=n+2$ 次查询。
## 代码
```
#include<bits/stdc++.h>
#define mp make_pair
#define pi pair<int,int>
#define pb push_back
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int a[1000003];
int main()
{
	int n=read();
	puts("XOR 1 2");
	fflush(stdout);
	int x=read();
	puts("XOR 2 3");
	fflush(stdout);
	int y=read();
	puts("OR 1 3");
	fflush(stdout);
	int z=read(),w=x^y; 
	puts("AND 1 2");
	fflush(stdout);
	int qwq=read();	
	puts("AND 2 3");
	fflush(stdout);
	int awa=read();	
	for(int i=1; i<n; i<<=1)
	{//0551050
		if(z&i)//OR是1，至少有一个是1
		{
			if(w&i)//一个0，一个1
			{
				if(y&i)//a2的xor是1，说明a2a3一个1一个0 
				{
					if(qwq&i) a[1]+=i,a[2]+=i;
					else a[3]+=i;
				}
				else 
				{
					if(awa&i) a[2]+=i,a[3]+=i;
					else a[1]+=i;
				}
			 } 
			else//都是1 
			{
				a[1]+=i,a[3]+=i;
				if(!(x&i)) a[2]+=i;
			}
		 } 
		 else
		 {
		 	if(x&i) a[2]+=i;
		 }
	}
	for(int i=4; i<=n; i++)
	{
		printf("XOR 1 %d\n",i);
		fflush(stdout);
		a[i]=read()^a[1];
	}
	printf("! ");
	for(int i=1; i<=n; i++) printf("%d ",a[i]);
	puts("");
	fflush(stdout);
	return 0;
}
```

---

## 作者：Scintilla (赞：1)

首先一个基本的思路是：我们可以先确定几个数，再把确定的数和其他的 $\text{XOR}$，就可以知道所有的数了。

我们知道，三个数可以通过询问两两的 $\text{AND}$ 和 $\text{XOR}$ 来知道（其中 $\text{XOR}$ 只用询问两次，因为其具有结合律）这样五次，总共就是 $n + 2$ 次，可以通过 E1。

为什么不三次询问出两个数呢，因为不能知道它们的顺序。

我们考虑对此方法进行优化。

发现还有一个重要的条件没用，那就是 $n = 2^k$ 及 $a_i \in [0, n - 1]$。不难发现，如果没有重复的话，那 $a$ 就必定是 $[0, n - 1]$ 的一个排列。

所以我们可以把 $\text{XOR}$ 操作提前，用 $n - 1$ 次询问 $a_1$ 和其他数的 $\text{XOR}$ 值，判断有没有重复的（即判断 $\text{XOR}$ 值中是否存在相同的数或 $0$）。

如果有的话，那就询问这两个数的 $\text{OR}$ 值，其答案就是这两个数。那么就知道了 $a_1$，进而就可以知道所有的数了。总询问次数为 $n$。

反之，这 $n - 1$ 个 $\text{XOR}$ 值肯定是 $[1, n - 1]$ 的排列。那么我们可以先找到与 $a_1$ $\text{XOR}$ 值为 $1$ 的数，询问它们的 $\text{OR}$ 值，确定 $a_1$ 二进制下除了最低一位以外的位数，再找到与 $a_1$ $\text{XOR}$ 值为 $2$ 的数，询问它们的 $\text{OR}$ 值，确定 $a_1$ 二进制下最低一位，那么就知道 $a_1$ 了，进而知道所有数。总询问次数为 $n + 1$。其实这里没必要指定，但是我认为指定后更容易理解。

代码太丑陋了，就不放了。

---

## 作者：LTb_ (赞：0)

[更好的阅读体验](http://lycltb.top/post/solution-1451e1/)

首先，可以通过 $n-1$ 次异或询问（具体实现是询问 $a_2 \sim a_n$ 与 $a_1$ 异或后的结果）来求出整个序列两两之间的异或关系，并且在求出一个位置的具体数值之后直接得到整个序列，于是还剩下 $3$ 次询问。

考虑任意的三个数 $a,b,c$（代码中取 $a_1,a_2,a_3$），我们已经通过之前的 $n-1$ 次询问知道了它们两两之间异或的结果。考虑这三个数的第 $i$ 位，分别记为 $x,y,z$ ( $x,y,z \in [0,1]$ )，有 $4$ 种可能情况：$x=y=z$，$x=y\not = z$，$x=z\not = y$，$y=z\not =x$。对于每一种情况，只要知道两个相等的位（如第二种情况中的 $x$ 和 $y$）$\operatorname{AND}$ 的值就可以求出 $x,y,z$。

于是，分别询问 $a \operatorname{AND} b$，$b \operatorname{AND} c$，$a \operatorname{AND} c$ 即可在 $n+2$ 次操作内得到序列。

```cpp
// 2020.11.21
// Code by LTb
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN=2<<17;
int n;
int a[MAXN];

signed main()

{
	cin>>n;
	for (int i=2;i<=n;i++){
		cout<<"XOR 1 "<<i<<endl;
		cin>>a[i];
	}

	int x,y,z;
	cout<<"AND 1 2"<<endl;
	cin>>x;
	cout<<"AND 1 3"<<endl;
	cin>>y;
	cout<<"AND 2 3"<<endl;
	cin>>z;

	int qwq=a[2]^a[3],ans=0;
	for (int i=15;i>=0;i--){
		int tmp1=(x>>i)&1,tmp2=(y>>i)&1,tmp3=(z>>i)&1;
		int tmp4=(a[2]>>i)&1,tmp5=(a[3]>>i)&1,tmp6=(qwq>>i)&1;
		if ((!tmp4) && (!tmp5) && (!tmp6)){
			ans|=tmp1<<i;
		}
		else{
			if (!tmp4) ans|=tmp1<<i;
			else if (!tmp5) ans|=tmp2<<i;
			else ans|=(!tmp3)<<i;
		}
	}

	cout<<"! "<<ans;
	for (int i=2;i<=n;i++)
		cout<<' '<<(ans^a[i]);
	cout<<endl;
	return 0;
}
```



---

## 作者：pomelo_nene (赞：0)

这是一个没有用到任何性质的题解。

首先给出一个式子：

$$
a \operatorname{xor} b + 2 \times (a \operatorname{and} b) = a+b
$$

考虑证明：$a \operatorname{xor} b$ 部分等于 $a,b$ 不相同的位减去 $a,b$ 都是 $1$ 的位。所以需要两个 $+a \operatorname{and} b$ 去调整得到 $a+b$。

对前面三个查询 $5$ 次，分别是 $a_1 \operatorname{xor} a_2,a_1 \operatorname{xor} a_3,a_1 \operatorname{and} a_2,a_1 \operatorname{and} a_3,a_2 \operatorname{and} a_3$（$a_2 \operatorname{xor} a_3$ 可以通过前两次查询结果异或得出），这样就能知道 $a_1+a_2,a_1+a_3,a_2+a_3$。

联立解方程可以得出 $a_1,a_2,a_3$。然后再根据异或的性质，知道一个数，两个数异或的结果，得到另一个数。每次查询一遍即可。查询次数 $5+n-3=n+2$。

注意不要把数组开小了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans[(1<<16)+5];
int main(){
	//a=1^2 b=1&2 c=1^3 d=1&3 e=2^3 f=2&3
	scanf("%d",&n);
	puts("XOR 1 2");
	fflush(stdout);
	int a;
	scanf("%d",&a);
	puts("XOR 1 3");
	fflush(stdout);
	int b;
	scanf("%d",&b);
	int c=a^b;
	puts("AND 1 2");
	fflush(stdout);
	int e;
	scanf("%d",&e);
	puts("AND 1 3");
	fflush(stdout);
	int f;
	scanf("%d",&f);
	puts("AND 2 3");
	fflush(stdout);
	int g;
	scanf("%d",&g);
	int x=a+2*e,y=b+2*f,z=c+2*g;
	int fuck=(x+y+z)/2;
	ans[1]=fuck-z,ans[2]=fuck-y,ans[3]=fuck-x;
	for(int i=4;i<=n;++i)
	{
		printf("XOR 1 %d\n",i);
		fflush(stdout);
		int p;
		scanf("%d",&p);
		ans[i]=ans[1]^p;
	}
	putchar('!');
	for(int i=1;i<=n;++i)	printf(" %d",ans[i]);
	puts("");
	fflush(stdout);
	return 0;
}
```

---

