# MKnez's ConstructiveForces Task

## 题目描述

MKnez wants to construct an array $ s_1,s_2, \ldots , s_n $ satisfying the following conditions:

- Each element is an integer number different from $ 0 $ ;
- For each pair of adjacent elements their sum is equal to the sum of the whole array.

More formally, $ s_i \neq 0 $ must hold for each $ 1 \leq i \leq n $ . Moreover, it must hold that $ s_1 + s_2 + \cdots + s_n = s_i + s_{i+1} $ for each $ 1 \leq i < n $ .

Help MKnez to construct an array with these properties or determine that it does not exist.

## 说明/提示

In the first test case, $ [9,5] $ is a valid answer since $ 9+5 $ (the sum of the two adjacent elements $ s_1+s_2 $ ) is equal to $ 9+5 $ (the sum of all elements). Other solutions include $ [6,-9], [-1,-2], [-5000,5000], \ldots $

For the second test case, let us show why some arrays do not satisfy the constraints:

- $ [1,1,1] $ — $ s_1+s_2 = 1+1 = 2 $ and $ s_1+s_2+s_3=1+1+1 = 3 $ differ;
- $ [1,-1,1] $ — $ s_1+s_2=1+(-1)=0 $ and $ s_1+s_2+s_3=1+(-1)+1 = 1 $ differ;
- $ [0,0,0] $ — The array $ s $ cannot contain a $ 0 $ .

This is not a proof, but it can be shown that the answer is "NO".

## 样例 #1

### 输入

```
2
2
3```

### 输出

```
YES
9 5
NO```

# 题解

## 作者：SuperCowHorse (赞：6)

先证明一个东西：

$\because s_1+s_2=\sum s[i]=s_2+s_3$，

$\therefore s_1=s_3$。

同理，$s_1=s_3=s_5=\dots$，$s_2=s_4=s_6=\dots$。

根据题目，很容易想到：当 $n$ 为偶数时，可以构造以下序列：

- $s_1=1,s_2=-1,s_3=1,s4=-1\dots$

如此交错。

那 $n$ 是奇数呢？

设 $s_1=x$，$s_2=y$，根据题目，有：

$\dfrac{n+1}2\times x+\dfrac{n-1}2\times y=x+y$

$\dfrac{n-1}2\times x+\dfrac{n-3}2\times y=0$

$(n-1)x+(n-3)y=0$

$(n-1)x=(3-n)y$

$\dfrac xy=\dfrac{3-n}{n-1}$

又 $\because x\neq0$，$y\neq0$，

$\therefore$ 当 $n=3$ 时，无解。

其余就构造 $x=3-n$，$y=n-1$ 即可。

Code:
``` cpp
//chenye3
#include<bits/stdc++.h>
#define ll long long
#define do double
using namespace std;
const ll inf=0x3f3f3f3f;
int n;
inline void solve(){
	scanf("%d",&n);
	if(n==3){//3特判掉
		printf("NO\n");
		return;
	}
	printf("YES\n");
	if(n&1){//奇数
		for(int i=1;i<=n;++i){
			if(i&1){
				printf("%d%c",3-n," \n"[i==n]);
			}
			else{
				printf("%d%c",n-1," \n"[i==n]);
			}
		}
		return;
	}
	for(int i=1;i<=n;++i){//偶数
		if(i&1){
			printf("%d%c",1," \n"[i==n]);
		}
		else{
			printf("%d%c",-1," \n"[i==n]);
		}
	}
}
signed main(){
	int T=1;
	for(scanf("%d",&T);T;--T) solve();
	return 0;
}
```

---

## 作者：Awsdkl (赞：2)

先证明：  
$\because s_i + s_{i+1} = s_1 + s_2 + ...+ s_n = s_{i+1} + s_{i+2}$，  
$\therefore s_i = s_{i+2}$。  
就可以得到：$s_1 = s_3 = s_5 = ...$，$s_2 = s_4 = s_6 = ...$。  
所以所构造的序列一定是交错相等的。  
当 $n$ 为偶数的时候，不难想到，只要 $s_i + s_{i+1} = 0$ 即可，我们让序列为：  
$s_1 = 1,s_2 = -1,s_3 = 1...$。  
也可以这样表示：$s_i = (i \mod 1) \times 2 - 1$。 

当 $n$ 是奇数时,则有：  
$\dfrac{n+1}{2} \times s_1 + \dfrac{n-1}{2} \times s_2 = s_1 + s_2$  
$\therefore (n+1)\times s_1 + (n-1) \times s_2 = 2\times s_1 + 2\times s_2$  
而当 $s_1 + s_2 = 1$，即 $s_1 = 1 - s_2$ 时，我们将其带入式子，则 $(n+1)\times (1 - s_2) + (n-1) \times s_2 = 2\times (1 - s_2) + 2\times s_2$，  
$\therefore n - 2 \times s_2 + 1 = 2$，  
$\therefore s_2 = \dfrac{n-1}{2}$，$s_1 = \dfrac{3-n}{2}$。  
而对于无解的情况，即 $s_1 = 0$ 或 $s_2 = 0$ ，我们发现，符合题意的只有 $n = 3$ （即 $s_1 = 0$）。  
所以只要交错输出 $\dfrac{n-1}{2}$ 和 $\dfrac{3-n}{2}$ 即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int t;
int n;

int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		if(n & 1) //当n为奇数时
		{
			if(n <= 3)
			{
				printf("NO\n");
				continue;
			}
			printf("YES\n");
			for(int i = 1;i <= n;i++)
			{
				if(i & 1) printf("%d ",(3-n)/2);
				else printf("%d ",(n-1)/2);
			}
			puts("");
			continue;
		}
		//n为偶数
		printf("YES\n");
		for(int i = 1;i <= n;i++)
		{
			printf("%d ",(i & 1) * 2 - 1);
		}
		puts("");
	}
	
	
	return 0;
}
```

---

## 作者：loser_seele (赞：1)

来个不一样的构造。

题目已经给出了 $ n \leq 3 $ 的构造，接下来只考虑 $ n \geq 4 $ 的情况。

首先 $ a_1+a_2=a_2+a_3=\sum a_i $，不难有 $ a_1=a_3 $，同理有 $ a_1=a_3=a_5=...,a_2=a_4=a_6=... $。

当 $ n $ 为偶数的时候直接填入 $ 1,-1 $ 即可，显然每两个数的和与总和相等为 $ 0 $。

否则，设 $ a_1=a,a_2=b,d=\lfloor \frac{n}{2} \rfloor $，则不难有 $ \sum a_i=d \times (a+b)+a=a+b $，接下来将 $ a $ 视为变量解方程。

$ d \times (a+b)+a=a+b \rightarrow d(a+b)=b \rightarrow da=(1-d)b  $

这个方程的一组特解为 $ a=1-d,b=d $，这是显然的。

因为 $ a,b $ 均不为 $ 0 $，而 $ 1-d=0 $ 或 $ d=0 $ 当且仅当 $ d=0,1 $，对应的 $ n $ 为 $ n \leq 3 $，已经排除，所以满足题意。

时间复杂度 $ \mathcal{O}(\sum n) $，可以通过。这个构造方法的值域相对比第一篇题解的小一点。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int a[2000020],ans=0;
void gen(int n)
{
int f[2000020];
for(int i=1;i<=n;i++)
f[i]=i;
do
{
if(0)//add something here.
ans++;
}while(next_permutation(f+1,f+n+1));
}
#define Y cout<<"Yes"<<'\n'
#define N cout<<"No"<<'\n'
signed main()
{
	int T=1;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		if(n%2==0)
		{
			cout<<"YES\n";
			for(int i=1;i<=n;i+=2)
				cout<<"1 -1 ";
			cout<<'\n';
		}
		else if(n==3)
			cout<<"NO\n";
		else
		{
			int d=n/2-1;
			cout<<"YES\n";
			for(int i=1;i<=n-2;i+=2)
				cout<<-d<<' '<<d+1<<' ';
			cout<<-d<<'\n';
		}
	}
}
```


---

## 作者：cjh20090318 (赞：1)

大家好，我是 CQ-C2024 蒟蒻 CJH。

## 题意

**本题有多组数据。**

给定一个正整数 $n$，请你构造一个有 $n$ 个非零整数的序列，满足任意相邻的两个数等于序列中所有数的总和且序列中的每一个数的绝对值不超过 $5000$。

试判断是否存在这样一个序列，如果可以输出 `YES` 并输出任意一个满足条件的序列，否则输出 `NO`。

## 分析

由题可得，将每一种情况移项：

$$\begin{cases}s_3+s_4+\dots+s_n=0\\s_1+s_4+\dots+s_n=0\\\dots\\s_1+s_2+\dots+s_{n-2}=0\end{cases}$$

根据加减消元法，可以发现：奇偶性相同的所有数相等。

### 当 $n$ 为偶数时

可以代入化简为：$s_1+s_2=0$。

所以就用最简单的 $s_1=1,s_2=-1$ 即可。

### 当 $n$ 为奇数时

可以带入化简为：$\lfloor\dfrac{n}{2}\rfloor  s_1+(\lfloor\dfrac{n}{2}\rfloor -1) s_2=0$。

所以直接令 $s_1=\lfloor\dfrac{n}{2}\rfloor -1,s_2=-\lfloor\dfrac{n}{2}\rfloor$。

剩下的根据相等关系处理即可。

## 注意

当 $n=3$ 时，根据上面的式子可得 $1\times s_1+0 \times s_2=0$，解得 $s_1=0$。

因为是非零整数，所以不满足条件，应该输出 `NO`。

易证其他的情况均有解。

## 代码

```cpp
//the code is from chenjh
#include<bits/stdc++.h>
using namespace std;
void solve(){
	int n;scanf("%d",&n);
	if(n==3){puts("NO");return;}//特判 n=3 时。
	puts("YES");//不等于 3 必定有解。
	if(n&1){//按照分析，分类讨论。
		int a=n>>1,b=a-1;//处理 s_1,s_2 的系数。
		for(int i=1;i<n;i+=2) printf("%d %d ",b,-a);
		printf("%d\n",b);
	}
	else{
		for(int i=1;i<=n;i+=2) printf("1 -1 ");
		putchar('\n');
	}
}
int main(){
	int t;scanf("%d",&t);
	while(t--) solve();
	return 0;
}

```

---

## 作者：____someone____ (赞：1)

## Description:

[$\text{\color{red}题目地址}$](https://www.luogu.com.cn/problem/CF1779B)

[$\text{\color{Brown}在他的博客查看该文章}$](https://www.luogu.com.cn/blog/666someonebk999/solution-cf1779b)

题意：

请你构造一个长度为 $n$ 的序列，使得序列中每一个元素都不为 $0$，且每两个相邻的元素之和等于序列中所有元素之和，如果能够造的出来就输出 `YES`，并输出构造的序列；如果不能，就输出 `NO`。

## Solution:

首先，我们由题意我们很容易知道 $s_{i-1}+s_{i}=s_{i}+s_{i+1}$，于是便得到一个式子 $s_{i-1}=s_{i+1}$。

所以，该序列中的某个元素一定等于与它不相邻的两个元素，所以该序列中只有两种元素，我们不妨设相邻的两个数为 $a$ 和 $b$。

- 当 $n$ 为偶数时，很容易想到可以使得 $a+b=0$，那么整个序列的和就为 $\dfrac{a\cdot n}{2}+\dfrac{b\cdot n}{2}$，所以序列的和就为 $0$，符合题意，所以当 $n$ 为偶数时，该序列一定能构造出，而且 $a$ 和 $b$ 互为相反数，即 $a=-b$。

- 当 $n$ 为奇数时，我们可以令 $a+b=1$（令 $a+b$ 等于其他数也行），假设 $a$ 为第一个元素，那么 $b$ 为第二个元素，因为 $n$ 为奇数，所以序列中元素值等于 $a$ 的元素有 $\dfrac{n+1}{2}$ 个；序列中元素值等于 $b$ 的元素有 $\dfrac{n-1}{2}$ 个。那么整个序列的和就为 $\dfrac{a\cdot(n+1)}{2}+\dfrac{b\cdot(n-1)}{2}=a+b=1$，所以 $a\cdot(n+1)+b\cdot(n-1)=2$，于是我们便可以联立一个关于 $a$ 和 $b$ 的方程组:
$$\begin{cases}a+b=1\\a\cdot(n+1)+b\cdot(n-1)=2\end{cases}$$

很容易我们就能解得
$$\begin{cases}a=\dfrac{3-n}{2}\\b=\dfrac{n-1}{2}\end{cases}$$

但是，不要高兴的太早，我们要注意题目有一个要求，就是序列里的元素都不能为 $0$，所以 $a\ne0$ 且 $b\ne$0，即 $n\ne1$ 且 $n\ne3$，所以当 $n=1$ 或者 $n=3$ 时这个序列是构造不出来的。

好了，分析完了，代码也就很好写了。

## AC Code（杜绝抄袭）:
```cpp
#include<bits/stdc++.h>
using namespace std;

int t,n;

int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		if(n%2==0)  //n是偶数的情况
		{
			cout<<"YES"<<endl;
			for(int i=1;i<=n;i++)
				if(i%2==0)cout<<1<<" ";   
				else cout<<-1<<" ";  //输出的相邻的两个数互为相反数
			cout<<endl;
		}
		else if(n!=3&&n!=1)
		{
			cout<<"YES"<<endl;
			int a=(3-n)/2,b=(n-1)/2;   //直接套用公式
			for(int i=1;i<=n;i++)
				if(i%2==0)cout<<b<<" ";
				else cout<<a<<" ";    //按照分析输出
			cout<<endl;
		}
		else cout<<"NO"<<endl;    //当n=1或n=3的情况
	}
	return 0;
}
```


---

## 作者：Convergent_Series (赞：0)

对于所有的 $i(1\le i<n-1)$ , 满足:
$$s_i+s_{i+1}=\sum_{i=1}^{n} s_i=s_{i+1}+s_{i+2},s_i=s_{i+2}$$

符合题意的序列一定是 $a,b,a,b \dots$ 形式的。

---

当 $n \bmod 2=0$ 时：

$\begin{aligned}
\frac{n(a+b)}{2}&=a+b\\
n(a+b)&=2(a+b)\\
\end{aligned}$

若 $a+b\ne 0$ ,则 $n=2$ ，与条件不符，舍去。  
当 $a+b=0$ 时， $\frac{0}{2}=0$ ，符合条件，$a=-b$ 。

---
当 $n \bmod 2=1$ 时：

$\begin{aligned}
\frac{(a+b)(n-1)}{2}+a&=a+b\\
(a+b)(n-1)&=2b\\
(a+b)(n-1)-2b&=0\\
a(n-1)+b(n-3)&=0\\
b(n-3)&=a(1-n)\\
\text{当}n\ne 3\text{时，}\frac{a}{b}&=\frac{1-n}{n-3} ;\\
\text{当}n= 3\text{时，}n-3&=0\text{ ，无解。}\\
\end{aligned}$

---

根据上面的式子就可以写出代码了：
```cpp
#include<bits/stdc++.h> 
#define int long long
using namespace std;
int n,t; 
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		if(n==3) cout<<"NO\n";//无解
		if(n>3&&n%2==1){//奇数
			cout<<"YES\n";
			for(int i=1;i<=n/2;i++) cout<<n-3<<" "<<1-n<<" ";
			cout<<n-3<<"\n";
		}
		if(n%2==0){//偶数
			cout<<"YES\n";
			for(int i=1;i<=n/2;i++) cout<<"1 -1 ";
			cout<<"\n";
		}
	}
	return 0;
} 
```

---

## 作者：cyrxdzj (赞：0)

### 一、思路

首先，当 $n$ 为偶数时，可以交替输出 $1$ 和 $-1$。这样，无论是数列的总和还是相邻两数和都为 $0$。

当 $n$ 为奇数时，需要更多考虑。

我们发现，$s_{i-1}+s_i=s_i+s_{i+1}$，因此 $s_{i-1}=s_{i+1}$。

换句话说，数列的奇数号数字相等，偶数号数字相等。

再换句话说，间隔一个数字的那两个数字相等。

我们再推一下当 $n=5$ 和 $n=7$ 时的答案（中的一种）：

```
n=5:
1 -2 1 -2 1
n=7:
2 -3 2 -3 2 -3 2
```

可以发现，两种数是有规律的。多出现的数（编号为奇数的数）为 $\frac{n-3}{2}$，少出现的数为 $\frac{1-n}{2}$。

证明：我们可以发现，多出现的数，数量为 $\frac{n+1}{2}$，少出现的数，数量为 $\frac{n-1}{2}$。数列相邻两数和为 $\frac{n-3}{2}+\frac{1-n}{2}=-1$，数列总和请读者自行计算，也是 $-1$。

当然，$n$ 不能等于 $3$，因为~~样例已经告诉我们了~~此时多出现的数会算出 $0$，这不合题意。

### 二、代码

```cpp
// Problem: MKnez's ConstructiveForces Task
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1779B
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<cstdio>
using namespace std;
int t;
int n;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		if(n==3)
		{
			printf("NO\n");
		}
		else if(n&1)
		{
			printf("YES\n");
			for(int i=1;i<=n/2;i++)
			{
				printf("%d %d ",(n-3)/2,(1-n)/2);
			}
			printf("%d\n",(n-3)/2);
		}
		else
		{
			printf("YES\n");
			for(int i=1;i<=n/2;i++)
			{
				printf("1 -1 ");
			}
			printf("\n");
		}
	}
	return 0;
}
```

---

## 作者：快乐的大童 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1779B)

## 题意简述
构造一个长度为 $n$ 的整数序列，使得这个序列相邻两个数的和等于整个序列所有数的和。你还需要保证序列没有等于 $0$ 的数，且值域在 $[-5000,5000]$ 之间。
## 思路
分两种情况讨论。

### 当 $n$ 为偶数时
显然奇数位填 $1$，偶数填 $-1$ 即可。

当然填其他数，或者奇偶位互换都可以。
### 当 $n$ 为奇数时

根据题意我们可以得到：$a_1+a_2=a_1+a_2+a_3+\cdots+a_n$。

化简得 $a_3+a_4+a_5+\cdots+a_n=0$，我们称之为结论 $1$。

根据题意我们还可以得到：$a_2+a_3=a_1+a_2+a_3+\cdots+a_n$。

化简得 $a_1+a_4+a_5+\cdots+a_n=0$，我们称之为结论 $2$。

我们可以根据结论 $1,2$ 得到 $a_1=a_3$。

根据题意我们还可以得到：$a_3+a_4=a_1+a_2+a_3+\cdots+a_n$。

化简得 $a_1+a_2+a_5+\cdots+a_n=0$，我们称之为结论 $3$。

根据结论 $2,3$ 可以得到 $a_2=a_4$。

以此类推，我们可以得到 $a_1=a_3=\cdots=a_{2k+1}=\cdots=a_n$ 且 $a_2=a_4=\cdots=a_{2k}=\cdots=a_{n-1}$，我们称之为结论 $4$。

为了表述方便，设所有奇数位的数都等于 $A$，所有偶数位的数都等于 $B$。

我们再尝试推一下：

先引用一下结论 $1$：$a_3+a_4+a_5+\cdots+a_n=0$。

根据结论 $4$，我们可以得到 $\dfrac{n-1}{2}\times A+\dfrac{n-3}{2}\times B=0$。

移项得 $\dfrac{n-1}{2}\times A=-\dfrac{n-3}{2}\times B$

两边同乘 $2$ 得 $(n-1)\times A=-(n-3)\times B$。

两边同除 $n-1$ 得 $A=-\dfrac{n-3}{n-1}\times B$。

显然当 $n=3$ 时无论 $B$ 取何值 $A$ 永远等于 $0$，故 $n=3$ 时无解。

由于 $n\ge 2$，故不存在 $n=1$ 的情况。

对于其他情况，由于我们需要保证 $A,B$ 都为整数，所以 $B$ 最好取 $n-1$，此时 $A=3-n$。

当然你可以取任何值，只要在值域范围内。
## 代码
仅给出主要部分。

```cpp
/*R()为快读函数，writesp()为快输函数+再输出一个空格*/
#define rep(a,b,c) for(int a=b;a<=c;a++)
void solve(){
	n=R();
	if(n==3) puts("NO");
	else{
		puts("YES");
		if(n&1){
			rep(i,1,n){
				if(i&1) writesp(3-n);
				else writesp(n-1);
			}
		}else{
			rep(i,1,n){
				if(i&1) writesp(1);
				else writesp(-1);
			}
		}
		puts("");
	}
}
```


---

## 作者：fengxiaoyi (赞：0)

### 思路

**找规律**

其实这题找规律即可，可以发现，当 $n\bmod2=0$ 时，$b$ 数组是 $n\div$ 个 $1$ 和 $n\div$ 个 $-1$ 交错形成的。换言之，当 $n\bmod2=0$ 时，$b$ 数组形如 $1,-1,1,-1,\cdots$，且长度为 $n$。

若 $n$ 为奇数，既 $n\bmod2=1$，$b$ 数组形如 $(n-3)\div2,-((n-3)\div2+1),(n-3)\div2,-((n-3)\div2+1),\cdots$，且长度为 $n$。

有了这个规律，程序就~~太水了~~很好写出来了。

### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		if(n==3) printf("NO\n");
		else if(n&1){
			printf("YES\n");
			for(int i=1;i<n;i+=2)
				printf("%d %d ",(n-3)/2,-((n-3)/2+1));
			printf("%d\n",(n-3)/2);
		}
		else{
			printf("YES\n");
			for(int i=1;i<=n;i+=2)
				printf("-1 1 ");
			putchar('\n');
		}
	}
	return 0;
}
```


---

