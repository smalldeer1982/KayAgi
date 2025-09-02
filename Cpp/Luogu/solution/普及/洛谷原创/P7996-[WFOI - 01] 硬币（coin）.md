# [WFOI - 01] 硬币（coin）

## 题目描述

你面前有一排 $n$ **堆**硬币排成一线，**同一堆硬币**的面值相同，记第 $i$ 堆硬币的面值为 $a_i$。而**每堆硬币**的数量都相同，记为 $x$。

现在你知道每第 $i$ 堆硬币的面值 $a_i$，你需要确定一个**正整数** $x$，使得**每堆硬币的总金额的**方差最接近于一个**正整数** $k$。

两数 **“最接近”** 的定义：两数之差的绝对值最小。

方差定义：方差 $s ^ 2 = \cfrac{(a_1 - \bar x)^2 + (a_2 - \bar x) ^ 2 + \cdots + (a_n - \bar x) ^ 2}{n}$，其中 $\bar x$ 代表 $x$ 的平均值。

## 说明/提示


**【样例 $\#1$ 解释】**

  当 $x=3$ 时，第 $i$ 个堆的硬币金额为 $3\times a_i$，这些硬币堆的金额分别为 $21,6,12,18,9,21,30$，可以计算得这些硬币金额的方差约为 $58.78$，可以证明当 $x=3$ 时方差最接近 $47$。

**【样例 $\#2$ 解释】**

  可以发现，无论 $x$ 的取值，方差都会为 $0$，所以输出 `No answer!`。







**【数据规模】**

**本题采用 Subtask 捆绑测试。**

Subtask 编号 | $n,\forall a_i\le$ | $k\le$ | $\footnotesize\texttt{测试点数目}$ |
:-: | :-: | :-: | :-:
**Subtask #0 $(20\texttt{pts})$** | $10^3$ | $10^9$| $6$ |
**Subtask #1 $(25\texttt{pts})$** | $10^5$ | $10^{12}$| $6$ |
**Subtask #2 $(25\texttt{pts})$** | $10^5$ | $10^{18}$| $6$ |
**Subtask #3 $(30\texttt{pts})$** | $7\times10^6$ | $3\times 10^{18}$| $6$ |

对于 $100\%$ 的数据，$1\le n,\forall a_i\le7\times10^6$，$1\le k\le3\times10^{18}$。记原来 $a$ 数组的方差为 $p$，则数据满足 $p=0$ 或 $p\in[0.25,\ 2^{63}-1]$ 。





**【提示】**

  本题读入量较大，请使用合适的读入方式。此处推荐[快速读入模板](https://www.luogu.com.cn/paste/bcfvgxr7)，对于 $\texttt{C/C++}$ 语言，你也可以使用 `scanf` 语句完成读入。
  
  为避免卡精度，建议 `C/C++` 选手使用 $\texttt{double}$ 类型，并不建议使用 `eps`。

## 样例 #1

### 输入

```
7 47
7 2 4 6 3 7 10```

### 输出

```
3```

## 样例 #2

### 输入

```
4 4
4 4 4 4```

### 输出

```
No answer!```

# 题解

## 作者：Elgo87 (赞：11)



出题人题解，[博客食用效果更佳](https://www.luogu.com.cn/blog/393864/post-round-1-a-ying-bi-ti-xie#)。

```
Ask: T1 出的很好，下次不要再出了。

Ans: T1 出的很差，我下次还会再出的。

（以上划掉
```

  
## 前置芝士：

- 【问题引入】

	设一个数列的方差为 $s^2$，那么当数列每个数乘 $x$ 时，方差为多少？

- 【 解 】

  根据平均数的计算公式：
  $$
  \bar x=\frac{a_1+a_2+a_3+...+a_n}{n}
  $$
  得出当数列每个数乘 $x$ 时，平均数为

  $$
  \bar x_2=\frac{x(a_1+a_2+a_3+...+a_n)}{n}=x\times \bar x
  $$   

  即：**数列每个数乘 $x$ 时，平均数也会乘 $x$。**

  所以根据方差的计算公式，当数列乘 $x$ 时，可以得出：

  $$
  s^2_2=\frac{(x\times a_1-x\times \bar x)^2+(x\times a_2-x\times \bar x)^2+...+(x\times a_n-x\times \bar x)^2}{n}
  $$

  提公因式得

  $$
  s^2_2=\frac{x^2\times[(a_1-\bar x)^2+(a_2-\bar x)^2+...+(a_n-\bar x)^2]}{n}=x^2\times s^2
  $$

  即：数列乘 $x$ 时，方差乘 $x^2$。

由此可得出以下两个规律：

- **当数列乘 $x$ 时，方差为 $x^2\times s^2$。**

- **$s^2$ 与 $x^2$ 成正比。**

## 本题题意：

简化题意：

给你一个数列，要你把这个数列的每个数乘 $x$，使得方差最接近于 $k$。要你求出这个 $x$。

## 本题思路

记原来数列的方差为 $s^2$。

这时候可以先假设我们要求的 $x$ 是任意正实数，那么可以求得一个唯一的 $x$，使 $s^2\times x^2=k$。

现对上式进行整理。

由于在计算之前先保证了 $s^2\not=0$，故有 $x^2=k\div s^2$。

由于 $x$ 是正数，故开平方后得 $x=\sqrt{k\div s^2}$。




而题目中所求的 $x$ 是**正整数**。由于 **$x$ 与 $s^2$ 成正比**，所以正解一定是 $\lfloor{x}\rfloor$ 或 $\lceil{x}\rceil{}$。


设 $\lfloor{x}\rfloor=a$，$\lceil{x}\rceil{}=b$，那么求解过程如下：

- 若 $s^2=0$：按题目要求直接输出 $\texttt{No answer!}$。

- 若 $a=0$：这种情况下容易得出 $b=1$，由于题目要求的是**正整数**，所以直接输出 $b$ 即可。

- 否则，比较 $s^2\times a^2$ 和 $s^2\times b^2$ 哪个更接近 $k$。具体地，当 $|s^2\times a^2-k| \le |s^2\times b^2-k|$ 时，输出 $a$，否则输出 $b$。

## 细节

- 注意题目要求答案为**正整数**，所以答案不可能会为 $0$，如果没注意，这会导致您 `WA #10 #13 #23`；
- `No answer!` 有个感叹号，如果您没注意，可能会 `WA #4 #8 #22`；
- 存答案的变量一定记得开 `long long`，否则你可能会 `WA #19`。

## 代码

$\texttt{std: }$

```cpp
#include<bits/stdc++.h>
#define N 10001001
using namespace std;
typedef double db;
typedef long long ll;  //十年 OI 一场空，不开 long long 见祖宗
inline void read(ll &ret)  //注意读入优化，此题用 scanf 读入也可过，但是使用朴素 cin 会 TLE
{
	ret=0;char c=getchar();bool pd=false;
	while(!isdigit(c)){pd|=c=='-';c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c&15);c=getchar();}
	ret=pd?-ret:ret;
	return;
}
ll n,k;
ll a[N];
signed main()
{
	read(n);
	read(k);
	db now=0.0;
	for(int i=1;i<=n;i++)
		read(a[i]),now+=1.0*a[i];
	now/=n;
	db sum=0.0;
	for(int i=1;i<=n;i++)
		sum+=(now-1.0*a[i])*(now-1.0*a[i]);
	sum/=n;   //用 sum 计算方差
	if(fabs(sum)<1e-9)  //第一种情况
	{
		puts("No answer!");
		exit(0);
	}
	ll x=floor(sqrt(k/sum)),y=ceil(sqrt(k/sum));  //此处用 x,y 代表思路中的 a,b
	if(!x)  //第二种情况
	{
		printf("%lld\n",y);
		return 0;
	}
	if(fabs(x*x*1.0*sum-k)<=fabs(y*y*1.0*sum-k))  //第三种情况
		printf("%lld\n",x);
	else
		printf("%lld\n",y);
	return 0;
}

```

---

## 作者：柳下惠 (赞：10)

[原题链接](https://www.luogu.com.cn/problem/P7996)。
### 前置知识：
方差计算公式。
![](https://s4.ax1x.com/2021/12/26/T0QZLT.png)

### 题目大意：

给你一段序列和一个值 $k$，求出一个最小的 $x$ 使这个序列上每个值都乘 $x$
后的序列方差值与 $k$ 相差最小。

### 分析：

根据数学原理，如果一个数 $×a$后，原方差 $s^2$ 就会变为 $s^2×a×a$。

我们可以先求出原序列的方差 $s^2$，所以在最好的情况下 $k=s^2×a×a$，所以 $a=sqrt(k/s^2)$，此时不难证明最优值为 $a$，但因为精度，直接开方出来的 $a$ 不一定是最优值，此时还需在一定范围内进行判断。

### code:

```cpp
#include<bits/stdc++.h>
#define I using
#define her std
#define ll long long
#define Love namespace
#define very_much ;
I Love her very_much//防伪
const int maxn=7*1e6+5;
ll n,m,k;
double p=0,s=0;
double a[maxn];
double minn=1e21;//需赋极大值
ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
int main()
{
	n=read(),k=read();
	for(int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+1+n);//排序进行特判
	if(a[1]==a[n]) //如果最大值等于最小值，显然方差为0
	{
		printf("No answer!");
		return 0;
	}
	for(int i=1;i<=n;i++) p+=a[i];
	p/=n;
	for(int i=1;i<=n;i++) s+=(a[i]-p)*(a[i]-p);
	s/=n;//计算出原方差
	ll ans=sqrt(k/s);//求出可能的最优值
	for(double i=max(1.0,ans-6.0);i<=ans+6.0;i+=1.0)//最优值会在一定范围内波动
	{ 
		if(abs(s*i*i-k)<minn)//如果此时的i会使s更接近k
		{
			minn=abs(s*i*i-k);//进行替换
			ans=i;
		}
	}
	printf("%lld",ans);//输出
}
```

---

## 作者：Mortis_Vampire (赞：2)

月赛第一题，非常毒瘤。

做题心路历程：

方差?这不太好吧。（爆肝 NOIP T3 的我很淦）

感觉这是个单峰函数。

那三分应该没问题。

然后我在写 check 函数的时候发现：数列 $a$ 中的每个数乘以 $x$，得到的数列的方差 $S^2$ 等于原数列 $a$ 的方差 $s^2$ 乘以 $x^2$ （~~显然~~）。

于是得到这样一个想法：

求出 $a$ 的方差，最后的答案就是 $\left \lfloor \sqrt{\dfrac{k}{s^2}} \right \rfloor $ 或 $\left \lfloor \sqrt{\dfrac{k}{s^2}} \right \rfloor +1$判断后离 $k$ 更近的一个。

如何判断其方差是否为 $0$ 呢，我们直接计算。（当然，更简便的做法是判断 $a$ 中的数是否全部相等）

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int n,a[7000005],L,R;
double ans,sum,k,rans;
int main() {
	scanf("%d%lf",&n,&k);
	for(int i=1; i<=n; i++) {
		scanf("%d",a+i);sum+=double(a[i]);
	}
	sum/=double(n);
	for(int i=1;i<=n;i++)
	ans+=(a[i]-sum)*(a[i]-sum);
	ans/=double(n);
	if(ans==0){
		printf("No answer!");
		return 0;
	}
	rans=k/ans;
	rans=(int)sqrt(rans);
	if(fabs(rans*rans*ans-k)<=fabs((rans+1)*(rans+1)*ans-k))
	printf("%d",int(rans));
	else printf("%d",int(rans)+1);
	return 0;
}
```
如果你把这份代码交上去，只有 45pts。

其实这已经非常接近正解了。

接下来就是对一些特殊数据的细节处理了。~~毒瘤~~

题目中说答案不能为 $0$ 也就是说当 $rans = 0$ 时，输出 $1$。~~好苟~~

我这里开 ```long double``` 以防被卡，但开 ```double``` 也没问题。

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int n;
long double ans,sum,k,rans,a[7000010];
long double fbbs(long double a){
	return a<0?-a:a;
}
int main() {
	scanf("%d%llf",&n,&k);
	for(int i=1; i<=n; i++) {
		scanf("%llf",a+i);sum+=a[i];
	}
	sum/=(long double)(n);
	for(int i=1;i<=n;i++)
	ans+=(a[i]-sum)*(a[i]-sum);
	ans/=(long double)(n);
	if(ans==0){
		printf("No answer!");
		return 0;
	}
	rans=k/ans;
	rans=(int)sqrt(rans);
	if(fbbs(rans*rans*ans-k)<=fbbs((rans+1)*(rans+1)*ans-k)&&int(rans)>0)
	printf("%d",int(rans));
	else printf("%d",int(rans)+1);
	return 0;
}
```
然后呢，70pts，#19 WA。

什么问题呢？

开 ```long long```，因为对```rans```的强制转换爆```int```了。

所以这真的是道签到题吗？~~毒瘤~~

奉上最后的 AC 代码。（常数可能有点大）

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int n;
long double ans,sum,k,rans,a[7000010];
long double fbbs(long double a){
	return a<0?-a:a;
}
int main() {
	scanf("%d%llf",&n,&k);
	for(int i=1; i<=n; i++) {
		scanf("%llf",a+i);sum+=a[i];
	}
	sum/=(long double)(n);
	for(int i=1;i<=n;i++)
	ans+=(a[i]-sum)*(a[i]-sum);
	ans/=(long double)(n);
	if(ans==0){
		printf("No answer!");
		return 0;
	}
	rans=k/ans;
	rans=(long long)sqrt(rans);
	if(fbbs(rans*rans*ans-k)<=fbbs((rans+1)*(rans+1)*ans-k)&&(long long)(rans)>0)
	printf("%lld",(long long)(rans));
	else printf("%lld",(long long)(rans)+1);
	return 0;
}
```
偷偷告诉你们，这是道曾经被整活成黑的黄题。

---

## 作者：Eason_AC (赞：2)

## Content
你有 $n$ 堆硬币，其中第 $i$ 堆有 $x$ 块面值为 $a_i$ 的硬币。你需要确定**正整数** $x$，使得使得每堆硬币的总金额的方差最接近于一个正整数 $k$。

**数据范围：$1\leqslant n,\forall a_i\leqslant 7\times 10^6$，$1\leqslant k\leqslant 3\times 10^{18}$。**
## Solution
这题目精度确实挺恶心人~~不然这道题目怎么会一度评为黑题呢~~，但是思路不太难想。

首先我们摆个结论出来。

---

**结论**：设 $p$ 为长度为 $n$ 的 $a$ 数组的方差，则如果 $a$ 数组里面的所有数全部都增加至原来的 $x$ 倍，那么其方差变为 $x^2\cdot p$。

证明：设原来的 $a$ 数组的平均值为 $\bar a$，则由定义得

$$p=\dfrac{\sum\limits_{i=1}^n(a_i-\bar a)}n$$

设 $a_i'=xa_i$，设 $a'$ 数组的平均值为 $\bar{a'}$，则有

$$\begin{aligned}\bar {a'}&=\dfrac{\sum\limits_{i=1}^n a_i'}n\\&=\dfrac {\sum\limits_{i=1}^n(xa_i)}n\\&=\dfrac {nx\sum\limits_{i=1}^na_i}n\\&=x\dfrac{\sum\limits_{i=1}^n a_i}n=x\bar a\end{aligned}$$

设 $p'$ 为 $a'$ 数组的方差，则有

$$\begin{aligned}p'&=\dfrac{\sum\limits_{i=1}^n(a_i'-\bar{a'})^2}n\\&=\dfrac{\sum\limits_{i=1}^n(xa_i-x\bar a)^2}n\\&=\dfrac{nx^2\sum\limits_{i=1}^n(a_i-\bar a)^2}n\\&=x^2\dfrac{\sum\limits_{i=1}^n(a_i-\bar a)^2}n=x^2p\end{aligned}$$

证毕。

---

然后我们发现事情就变得非常简单了，我们首先找到一个最大的**整数** $x_1$ 使得 $p'=x_1^2p\leqslant k$，即 $x_1\leqslant \sqrt{\dfrac kp}$，那么很显然满足要求的最大的**整数** $x_1$ 的值即为 $\lfloor\sqrt{\dfrac kp}\rfloor$。然后即可求出最小使得 $x_2^2p>k$ 的**整数** $x_2$ 的值为 $x_1+1$。

然后我们将这两个数代入，看代入哪个值的方差更小，如果相同的话取 $x_1$ 即可，然后这道伪黑题就做完了……

吗？

注意到我们求的都是**整数**，而题目要求的是**正整数**，因此需要判断 $x_1$ 是否是**正整数**，不是正整数的话就只能够取 $x_2$，否则按照上面的要求去比较求得答案。

关于卡精度这档事……确实挺恶心人，我赛时被这玩意的精度卡了大概 40 分钟，最后用 `long long` + `double` 才卡过去。以下给出一种基于上述做法的可参考的代码。
## Code
```cpp
namespace Solution {
#define int ll //看代码之前留意一下这里
	const int N = 7e6 + 7;
	int n, k, a[N];
	
	iv Main() {
		read(n, k); F(int, i, 1, n) read(a[i]);
		double ave = 0.0, ans = 0.0;
		F(int, i, 1, n) ave += a[i]; ave /= n;
		F(int, i, 1, n) ans += (a[i] - ave) * (a[i] - ave); ans /= n;
		if(ans == 0.0) {puts("No answer!"); return;}
		double t = sqrt(k * 1. / ans); 
		int k1 = (int)t, k2 = k1 + 1;
		if(!k1 || fabs(k1 * k1 * ans - k) > fabs(k2 * k2 * ans - k)) write(k2);
		else write(k1);
		return;
	}
#undef int
}
```

---

## 作者：Galois_Field_1048576 (赞：1)

### 题意简述

求最合适的 $x \in \mathbf{N^+}$ 使得 $|\frac{1}{n} \sum\limits^{n}_{i=1} (xa_i-\frac{\Sigma (xa_i)}{n} )^2 - k|$ 最小。  

看着没什么头绪，是吧。  

### 拆一下柿子：
$|\frac{1}{n} \sum\limits^{n}_{i=1} (xa_i-\frac{\Sigma (xa_i)}{n} )^2 - k|$
明显就乘法分配律

$|\frac{1}{n} \sum\limits^{n}_{i=1} (xa_i-x\frac{\Sigma (a_i)}{n} )^2 - k|$还是乘法分配律

$|\frac{1}{n} \sum\limits^{n}_{i=1} [x(a_i-\frac{\Sigma (a_i)}{n} )]^2 - k|$ 

$|\frac{1}{n} \sum\limits^{n}_{i=1} x^2(a_i-\frac{\Sigma (a_i)}{n} )^2 - k|$

$|x^2\frac{1}{n} \sum\limits^{n}_{i=1} (a_i-x\frac{\Sigma (a_i)}{n} )^2 - k|$

$|x^2\cdot p-k|$  ( $p$ 是常量)  
所以只要预处理出 $p$ 然后二分，结果输出 $+1,-1$ ,不变中最合适的一个即可。  
### 细节
二分边界R是 $\frac{4k}{\min(1,p)}$ ，需要用`unsigned long long`类型。  
$p$ 需要 `double`类型。  
如果答案 $\le 0$ 则输出 $1$。  
$\frac{1}{n} \sum\limits^{n}_{i=1} (a_i-x\frac{\Sigma (a_i)}{n} )^2 = 0 \iff \exists k, \forall i,a_i=k$  
### 代码
```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
const int N = 7e6+5;
long long n, k, a[N];
double avg, p; 
inline long long read(){
	long long now=0,nev=1; char c=getchar();
	while(c<'0' || c>'9') { if(c=='-') nev=-1; c=getchar();}
	while(c>='0' && c<='9') { now=(now<<1)+(now<<3)+(c&15); c=getchar(); }
	return now*nev;
}
int qwq = 7;double val = 1e200; 
bool okk = false;

int main() {
	n = read(); k=read();
	for (int i=1;i<=n;++i) {
		a[i] = read(), avg += 1.0*a[i];
		if(i>1&&a[i-1]!=a[i]) okk=1;
	}
	avg/=n;
	for (int i=1;i<=n;++i) p += (a[i]-avg)*(a[i]-avg); 
	p /= n;
	if (!okk){
		cout << "No answer!" << endl;
		return 0; 
	}
	unsigned long long mid = 0;
	//cout << avg << ' ' << p << endl;
	unsigned long long l=0llu,r=(unsigned long long)(4llu*k/min(p,1.0));
	while (l <= r) {
		mid = (l+r)/2llu;
		if (p*mid*mid > k) r = mid - 1;
		else if (p*mid*mid < k) l = mid + 1;
		else {
			cout<<mid;
			return 0;
		} 
	}
	for (int i=-1;i<=1;++i) 
		if (val > fabs((mid+i)*(mid+i)*p - k)) val = fabs((mid+i)*(mid+i)*p - k), qwq = i;
	if (mid < 2 && (long long)(mid+qwq) <= 0) cout << 1 << endl;  
	else cout << mid+qwq;
	return 0;
}
```

---

## 作者：lnwhl (赞：1)

# P7996 [WFOI - 01] 硬币 题解
## 题目描述
给定一个数列 $a_{i}$。

求正整数 $x$ 使数组**每个数都乘 $x$ 后的方差**与 $k$ 的差最小。

## 分析
### 前置知识
观察方差的公式。

$s^2=\frac{(a_1-\bar x)^2+(a_2-\bar x)^2+...+(a_n-\bar x)^2}{n}$

其中
$\bar x=\frac{a_1+a_2+a_3+...+a_n}{n}$

**易知 $a_{1}$ 到 $a_{n}$ 每个数都乘 $x$，方差乘 $x^2$**。


------------


证明:

$\because$ $a_{1}$ 到 $a_{n}$ 每个数都乘 $x$.

$\therefore$ $\bar x \gets \bar x \times x$

$\therefore$ $a_{i} - \bar x \gets (a_{i} - \bar x) \times x$

$\therefore$ $(a_{i} - \bar x)^2 \gets (a_{i} - \bar x)^2 \times x^2$

$\because$ $s^2=\frac{(a_1-\bar x)^2+(a_2-\bar x)^2+...+(a_n-\bar x)^2}{n}$

$\therefore$ $s^2 \gets s^2 \times x^2$

证毕。

**这里我们也可以知道 $s^2$ 与 $x^2$ 成正比。**

------------

### 本题思路
1. 先判断**无解**的情况。一个数组的方差等于零当且仅当数组所有的数全相等。

1. 再处理**有解**的情况。

	我们可以先算出原数组的方差 ```vari```。我们可以先假设 $x$ 为**正实数**。那么必有 ```vari```$\times x^2=k$。
   
   $\because$ ```vari```$\neq0$，$x>0$。
   
   $\therefore$ $x= \sqrt{\frac{k}{vari}}$。
   
   但题目中 $x$ 为**正整数**，答案就一定是 $\lfloor x \rfloor$ 或 $\lceil x \rceil$ 了。

	代码中用 $\operatorname{sqrt}$ 求出使 ```vari``` $\times x^2$ 恰小于 $k$ 的 $x$ 的值。
之后取 $k-$```vari``` $\times x^2$ 与 ```vari``` $\times (x+1)^2-k$ 的最小值就可以了。

### 但还有以下几点需要注意：
- 如果有不同的答案，输出最小的一个。
- $x$ 不能为 $0$。
- 这题完全没有必要用 ```int128```，```long double``` 也可以通过。

## 代码（不要只看这里啊）
```c
#include <bits/stdc++.h>
using namespace std;
long long n,k,a[7000005],x;
long double xb=0,vari=0;
inline long long read()//快读 
{
    long long now=0,nev=1; char c=getchar();
    while(c<'0' || c>'9') { if(c=='-') nev=-1; c=getchar();}
    while(c>='0' && c<='9') { now=(now<<1)+(now<<3)+(c&15); c=getchar(); }
    return now*nev;
}
inline long double fc()//求方差 
{
    long double now=0;
    for(int i=1;i<=n;i++)
    {
        now+=(xb-a[i])*(xb-a[i]);
    }
    return now/n;
}
int main()
{
    n=read();k=read();
    long long f,ok=1;
    for(int i=1;i<=n;i++)
    {
        a[i]=read();xb+=a[i];//xb先记录总和，之后除n求出平均数
        if(i>1&&f!=a[i])ok=0;//判断是否全相等
        f=a[i];
    }
    if(ok==1){cout<<"No answer!";return 0;}//无解
    xb/=n;//xb代表平均数
    vari=fc();//原数组的方差
    x=sqrt(k/vari);//x^2倍
    if(x==0)cout<<1;//不能为0 
    else
    {
        long double ans1=x*x*vari;//向下取整
        long double ans2=(x+1)*(x+1)*vari;//向上取整
        if(k-ans1<=ans2-k)cout<<x;//可以等于
        else cout<<x+1;
    }
    return 0;
}
```
## 总结
数据真够毒瘤，月赛题目越来越毒瘤了。

---

## 作者：Inkyo (赞：1)

没啥时间打月赛，于是写完 T1 就跑了（（（

## 题意

给你一个长度为 $n$ 的序列 $\{a_1,a_2,a_3,...,a_n\}$，你需要求得一个 $x$，使得长度为 $n$ 的序列 $\{xa_1,xa_2,...,xa_n \}$ 的方差最接近 $k$。

## 题解

我们都知道，方差的定义是：

>对于一个含 $n$ 个数的序列 $\{a_1,a_2,a_3,...,a_n\}$，其所有数的方差为：

>$$
{\frac{1}{n}\displaystyle\sum_{i=1}^{n}(\bar{a}-a_i)^2}
$$

>（其中，$\bar{a}$ 意指序列中所有数的平均值。）

我们同样知道，对于序列  $\{xa_1,xa_2,...,xa_n \}$，其平均值必然是原数列的 $x$ 倍。

那么，如果带入方差公式，我们可以很轻易的就可以得出，序列  $\{xa_1,xa_2,...,xa_n \}$ 的方差即为原序列方差的 $x^2$ 倍。


那么解法就很简单了。我们只需要先求出原序列的方差 $s^2$，按照题意，我们需要使得 $x^2s^2$ 最接近 $k$，那么我们不妨令 $ans = \lfloor \sqrt{k/s^2} \rfloor$。此时，我们可以很容易地得到：

$$ans^2s^2 \le k < (ans+1)^2s^2$$

因为我们需要求得最接近 $k$ 的值，那么，我们只需要比较 $k - ans^2s^2$ 与 $(ans+1)^2s^2 - k$ 的大小即可。如果前者更小，那么 $x=ans$，反之，$x=ans+1$ 。

这样就得到 $x$ 的值了，这种做法大概是不会被卡精度的。

---

另外，如果求得 $s^2=0$，此时无论 $x$ 取什么值方差都为 $0$，需要输出 `No answer!`

再另外，如果我们求得 $ans = 0$，**由于答案必须要是正整数**，所以需要把 $ans+1$。（我在这卡了半天 orz）

## $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define maxn 7000005
using namespace std;

int n;
int a[maxn];
long long k, ans;
double aver, s; //aver:平均数 s:方差 

inline int read()
{
	int now = 0, nev = 1; char c = getchar();
	while(c < '0' || c > '9') { if(c == '-') nev = -1; c = getchar();}
	while(c >= '0' && c <= '9') { now = (now << 1) + (now << 3) + (c & 15); c = getchar(); }
	return now * nev;
}

int main()
{
	scanf("%d%lld", &n, &k);
	for(register int i = 1; i <= n; i ++) //读入，顺带计算平均数
	{
		a[i] = read();
		aver += a[i];
	}
	aver /= n;
	
	for(register int i = 1; i <= n; i ++) //算方差
		s += ((a[i] - aver) * (a[i] - aver));
	s /= n;
	
	if(s == 0) //特判
	{
		printf("No answer!");
		return 0;
	}
	
	ans = sqrt(k / s);
	double x = abs(k - ans * ans * s), y = abs(k - (ans + 1) * (ans + 1) * s);
	if(x > y) ans ++;
	if(ans == 0) ans ++; 
	
	printf("%lld", ans);
	
	return 0;
} 
```


---

## 作者：SunsetSamsara (赞：1)

## 前置知识

数学

## 分析

首先看方差在数组元素扩大 $k$ 倍时会变大多少倍。

由方差定义，
$$s^2=\frac{(a_1-\bar x)^2+(a_2-\bar x)^2+...+(a_n-\bar x)^2}{n}$$

当数组元素扩大 $t$ 倍时，$\bar x$ 扩大 $t$ 倍，$a_i$ 扩大 $t$ 倍，所以 $\left(a_i - \bar x\right)$ 扩大 $t$ 倍，$\left(a_i - \bar x\right)^2$ 扩大 $t^2$ 倍。

因为 $n$ 不变，所以这就相当于方差扩大 $t^2$ 倍。

然后因为要让方差最接近 $k$，所以就只需求出 $\sqrt{\dfrac{k}{s^2}}$ 最接近的整数。

只需要算出原来的方差即可。

最后，因为我这个写法精度低，所以要开 `__int128`

## 代码

```cpp
#include <bits/stdc++.h> 
#define lld long long 
using namespace std;
int n;
__int128 k;
__int128 a[7000010];
inline __int128 read(){
	__int128 now=0,nev=1; char c=getchar();
	while(c<'0' || c>'9') { if(c=='-') nev=-1; c=getchar();}
	while(c>='0' && c<='9') { now=(now<<1)+(now<<3)+(c&15); c=getchar(); }
	return now*nev;
}
int main() {
	n = read();
	k = read();
	for (int i = 1; i <= n; ++ i) a[i] = read();
	__int128 avg = 0;
	for (int i = 1; i <= n; ++ i) avg += a[i]; // 算出平均数 * n
	__int128 ans = 0, d;
	for (int i = 1; i <= n; ++ i) {
		d = avg - a[i] * n;
		ans = ans + d * d;
	} // 算出方差 * n * n
	if (!ans) {
		puts("No answer!");
		return 0;
	}
	double v = (double) k / ans * n * n * n;
	__int128 t = sqrt(v);
	if (t < 2) t = 2;
	double v1 = abs((t - 1) * (t - 1) - v);
	double v2 = abs(t * t - v);
	double v3 = abs((t + 1) * (t + 1) - v);
	if (v1 <= v2 && v1 <= v3) printf("%lld\n", (lld)t - 1);
	else if (v2 <= v1 && v2 <= v3) printf("%lld\n", (lld)t);
	else printf("%lld\n", (lld)t + 1);
    // 找最接近整数
}
```

---

## 作者：Fearliciz (赞：0)

#### 前言：

同机房同学好多用的二分暴力，我不会，在这里写一个 $O(n)$ 的方法。

#### 解题思路：

首先容易想到二分 $x$ 不过看了看数据范围，觉得有点悬，就没写。

考虑找规律。

记数据平均数为 $ave$，方差为 $s^2$，数据个数为 $n$，则数列 $a$ 的方差为：

$$
s^2=\frac{(a_1-ave)^2+(a_2-ave)^2+...+(a_n-ave)^2}{n}
$$

则我们要求出：

$$
{s'}^2=\frac{(xa_1-xave)^2+(xa_2-xave)^2+...+(xa_n-xave)^2}{n}
$$

现在我们拿出其中 $a_1$ 的那组：

$$
(xa_1-xave)^2
$$

$$
= (x(a_1-ave))^2
$$

$$
= x^2(a_1-ave)^2
$$

同理可得：

$$
(xa_i-xave)^2
$$

$$
= x^2(a_i-ave)^2
$$

$$
\therefore {s'}^2=\frac{x^2(a_1-ave)^2+x^2(a_2-ave)^2+...+x^2(a_n-ave)^2}{n}
$$

$$
\therefore {s'}^2=x^2\frac{(a_1-ave)^2+(a_2-ave)^2+...+(a_n-ave)^2}{n}
$$

显然，式子变成了：

$$
{s'}^2=x^2原方差
$$

现在要使 $|{s'}^2-k|$ 最小，即从：

$$\lfloor\sqrt{\frac{k}{原方差}}\rfloor$$

和

$$\lceil\sqrt{\frac{k}{原方差}}\rceil$$

取一个。

#### 注意事项：

+ 在所有数都相同的情况下，输出 `No answer!`。

+ 记得最后判断答案为 $0$ 的情况，我在这个地方挂了好久。

#### 代码实现：

```cpp
#include <bits/stdc++.h>
using namespace std;

long long a[7000007];
long long n, k;
long long sum = 0;
double fc = 0;
bool flag = 0;

inline long long readll()
{
	long long now = 0, nev = 1;
	char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
			nev = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		now = (now << 1) + (now << 3) + (c & 15);
		c = getchar();
	}
	return now * nev;
}

inline int read()
{
	int now = 0, nev = 1;
	char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
			nev = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		now = (now << 1) + (now << 3) + (c & 15);
		c = getchar();
	}
	return now * nev;
}

void FC()
{
	double ave = 1.0 * sum / n;
	for (int i = 1; i <= n; i++)
		fc += (a[i] - ave) * (a[i] - ave);
	fc /= (double)n;
}

int main()
{
	n = readll(); k = readll();
	for (int i = 1; i <= n; i++)
	{
		a[i] = readll();
		sum += a[i];
		if (i != 1 && a[i] != a[i - 1])
			flag = 1;
	}
	if (!flag)
	{
		printf("No answer!");
		return 0;
	}
	FC();
	double c = floor(sqrt(k / fc));
	double b = ceil(sqrt(k / fc));
	if (c == 0)
		printf("%lld", (long long)b);
	else if (b == 0)
		printf("%lld", (long long)c);
	else if (abs(c * c * fc - k) <= abs(b * b * fc - k))
		printf("%lld", (long long)c);
	else
		printf("%lld", (long long)b);
	return 0;
}
```



---

## 作者：qwq___qaq (赞：0)

~~这精度，真的很毒~~

拿到此题，我们先推导式子：设数组中每个数为 $a_i$，一共有 $n$ 个数。

首先，平均数 $\overline{x_1}\gets \frac{\sum_{i=1}^na_i}{n}$；

方差就是 $s_1\gets\frac{\sum_{i-1}^n(a_i-\overline{x})^2}{n}$。


当每个数增长 $x$ 倍时，则平均数 $\overline{x_2}\gets \frac{\sum_{i=1}^na_i\times x}{n}=x\times\frac{\sum_{i=1}^na_i}{n}=x\times\overline{x_1}$，此处用到了乘法分配律；

方差为 $s_2\gets\frac{\sum_{i-1}^n(a_i\times x-\overline{x}\times x)^2}{n}=x^2\times\frac{\sum_{i-1}^n(a_i-\overline{x})^2}{n}=x^2\times s_1$，仍然是乘法分配律。

此时，我们就可以发现当方差为 $0$ 时（即所有数都相同），无论乘多少倍都为 $0$，无解，输出 `No answer!`。

有了这个公式，我们可以直接运用除法，先除 $n$，再开根，最后四舍五入输出即可。

但是，这样只有 75 分，我们考虑一下：

1. 答案不能为 $0$。

此时，我们就必须求出向上取整和向下取整。

2. 当答案有多个时，输出最小的那一个。

对于这个东西，在第一个的基础上，判断哪个与 $k$ 的差值小就行。

3.$n\in[1,7\times 10^6],p\in[\frac{1}{4},2^{63}-1]$

此时，我们可以发现，如果 $p\times n^2$，就会爆掉，所以我们还是直接除为妙。

具体细节见代码：
```cpp
#include<bits/stdc++.h>
#define int long long//答案：不开 long long 见祖宗
using namespace std;
const int maxn=7e6+5;
double ans,sum,w,n,k,a[maxn];//为了保证精度，全部开 double
bool check=1;//判断每个数是否相同
signed main(){
	scanf("%lf%lf",&n,&k);
	for(int i=1;i<=n;++i)
		scanf("%lf",&a[i]),sum+=a[i];
	for(int i=2;i<=n;++i)
		check&=(a[i]==a[i-1]);
	if(check){
		printf("No answer!");
		return 0;
	}//所有数是否相等
	sum/=n;
	for(int i=1;i<=n;++i)
		ans+=(sum-a[i])*(sum-a[i]);
	ans/=n;
	int a1=sqrt(k/ans),a2=ceil(sqrt(k/ans));//上取整与下取整
	if(!a1)
		printf("%lld\n",a2);//下取整答案为 0
	else if(fabs(a1*a1*ans-k)<=fabs(a2*a2*ans-k))//下取整答案更优
		printf("%lld\n",a1);
	else//其它
		printf("%lld\n",a2);
	return 0;
}
```

---

## 作者：crn1 (赞：0)

## 题目大意
给定一个长度为 $n$ 的序列 $a$，要你求出一个正整数 $x$，使得序列 $a$ 的每一项乘 $x$ 后的方差与给定正整数 $k$ 的差的绝对值最小。

## 题解
方差 $s^2=\frac{1}{n}\sum_{i=1}^{n}(\bar{a}-a_i)^2$

如果数列每项乘上 $x$，变化后方差 $s_1^2=\frac{1}{n}\sum_{i=1}^n(\bar{a}x-a_ix)^2=s^2x^2$

记原方差为 $s^2$ ，就是求一个 $x$ 使得 $|s^2x^2-k|$ 最小，要使这个式子最小，$x$ 的取值只有两种可能，$\sqrt{\frac{k}{s^2}}$ 向上取整和向下取整

## 核心代码
```cpp
long long x = sqrt(k / s2), ans = 1;
double tmp = fabs(s2 - k);
for (long long i = std::max(x, 1ll); i <= x + 1; ++i) {
	f64 y = s2 * i * i;
	if (fabs(y - k) < tmp) tmp = fabs(y - k), ans = i;
}
```

---

## 作者：Argon_Cube (赞：0)

* **【题目链接】**

[Link:P7996](https://www.luogu.com.cn/problem/P7996)

* **【解题思路】**

~~这题我是乱搞出来的（~~

好的，现在说一说如何乱搞。

我用的是 Desmos。

首先，我们可以探究一下，当数量 $x$ 取不同的值时，方差 $v$ 会有什么变化？

如果把图画出来，我们可以很清楚的看到，$v(x)$ 是过点 $(0,0)$ 的一个二次函数。其实这确实很显然。

然后，我们再看看题目的数据范围：原数据中 $v=0$ 或 $0.25\leq v\leq 2^{63}-1$。我们再看样例二，原数据方差为零，那么无论怎么取 $x$ 都是零。

那么，我们想到：原数据的方差即 $v(1)$，假如 $v(x)$ 是一个关于 $x$ 的式子乘上 $v(1)$，那么样例二不就说得通了？

好的，让我们算一下 $\dfrac{v(x)}{v(1)}$。结果出奇的简单：$v(x)=x^2v(1)$！也就是说，当 $v(1)=0$ 时，$v(x)$ 无论如何都是 $0$。而当 $v(1)\neq0$ 时，$\dfrac{v(x)}{v(1)}=x^2$！（这就是为什么 $\textsf{\color{red}little\_cindy}$ 问的“$v(x)$ 与 $x$ 有什么关系”会被拒绝回答）当然如果你想要证明的话，你可以自己试着证一证。证明其实很简单。

那么解法不就出来了？

先算出 $v(1)$。假如 $v(1)=0$，则无解；否则：

我们可以算出最大的一个正整数 $x_0$ 使得 $v(x_0)<k$，那么答案显然就在 $x_0$ 与 $x_0+1$ 之间。我们也可以理解为，解出一个 $v(x_1)=k$，则答案在 $\lceil x_1\rceil$ 与 $\lfloor x_1\rfloor$ 之间。不过，这里 $\lfloor x_1\rfloor$ 用 $x_0$ 替换了。当然，当 $x_1$ 为整数时，我们是不会选 $x_0+1$ 的，这个多出来的备选对答案没有影响。（**不过有一个例外！** 我一会再说）

那么怎样确定 $x_0$ 呢？我们可以转化 $v(x_0)<k$：还记得 $v(x)=x^2v(1)$ 吗？

$$
\begin{aligned}
v(x_0)<&k\\
x_0^2v(1)<&k\\
x_0<\sqrt\frac k{v(1)}
\end{aligned}
$$

那么 $x_0=\left\lfloor\sqrt\dfrac k{v(1)}\right\rfloor$。

好的，前面说的例外是这样的：假如 $x_0=0$，而 $x=0$ 比 $x=1$ 更优，选哪个？**是** $1$！题目说了：

>你需要确定一个**正整数** $x$。

为什么正整数要加粗？$0$ 是正整数吗？不是。我们能选它吗？不能。我们只能选 $1$。这就是这题的一大坑点。

好了，到这里就做完了。复杂度 $\operatorname O(n)$。

* **【代码实现】**

```cpp
#include <iostream>
#include <array>
#include <cmath>

using namespace std;

array<int,7000000> arr;

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	double average=0,variance=0;
	long long cnt,target;
	cin>>cnt>>target;
	for(int i=0;i<cnt;i++)
		cin>>arr[i],average+=arr[i];
	average/=cnt;
	for(int i=0;i<cnt;i++)
		variance+=(average-arr[i])*(average-arr[i]);
	variance/=cnt;
	if(variance<0.2)
		return cout<<"No answer!",0;
	long long ans=sqrt(target/variance);
	if(ans==0)
		return cout<<1,0;
	if(fabs(ans*ans*variance-target)<=fabs((ans+1)*(ans+1)*variance-target))//我们当 x 与 x+1 都是最优解时要小的！所以这里是小于等于
		cout<<ans;
	else
		cout<<ans+1;
	return 0;
}

```

---

## 作者：Iam1789 (赞：0)

根据方差和平均数的定义可得：
$$\bar x=\frac{\sum_{i=1}^na_i}{n}$$
$$s^2=\frac{(a_1-\bar x)^2+(a_2-\bar x)^2+...+(a_n-\bar x)^2}{n}$$

将每堆硬币从 $1$ 个变到 $k$ 个试试？
$$\bar x_k=\frac{\sum_{i=1}^n ka_i}{n}=k \bar x$$
$$s_k^2=\frac{(ka_1-\bar x_k)^2+(ka_2-\bar x_k)^2+...+(ka_n-\bar x_k)^2}{n}$$
$$=\frac{(ka_1-k\bar x)^2+(ka_2-k\bar x)^2+...+(ka_n-k\bar x)^2}{n}$$
$$=k^2\frac{(a_1-\bar x)^2+(a_2-\bar x)^2+...+(a_n-\bar x)^2}{n}$$
$$=k^2 s^2$$
$$s_k=ks$$
$$k=\frac{s_k}{s}$$
显然直接求出来的 $k$ 可能不是整数。于是我们把 $k$ 上取整和下取整，找一个里 $s_k$ 最近的就好了。

注意 $k>0$，很坑。

---

## 作者：cancan123456 (赞：0)

我们来推一下式子：第 $i$ 堆硬币的面值之和为 $xa_i$，所以：

$$\overline{a}'=\dfrac{\sum\limits_{i=1}^{n}xa_i}{n}=x\dfrac{\sum\limits_{i=1}^{n}a_i}{n}=x\overline{a}$$

$$\begin{aligned}(s^2)'&=\sum\limits_{i=1}^{n}(a_i'-\overline{a}')^2\\&=\sum\limits_{i=1}^n(xa_i-x\overline{a})^2\\&=\sum\limits_{i=1}^nx^2(a_i-\overline{a})^2\\&=x^2\sum\limits_{i=1}^n(a_i-\overline{a})^2\end{aligned}$$

所以，如果我们把硬币数乘以 $x$，方差就会乘以 $x^2$.

那么，我们先计算出原先序列的方差，记作 $v$，那么 $x$ 就应当接近于 $\sqrt{\dfrac{k}{v}}$，记作 $x'$，我们计算出后，将 $\lceil x'\rceil$ 与 $\lfloor x'\rfloor$ 进行比较，那个更优就选哪个。

一个小细节：如果 $y<1$ 那么应该输出 $1$，因为 $x$ 只能为正整数。

无解判定：如果原序列的方差就是 0，那么无解，原因显然。

---

## 作者：Tx_Lcy (赞：0)

事实上，对于这一题，并没有这么复杂，解答过程如下。

**第一步，求出所有硬币的初始方差**。设原方差为 S ,可得 $S=\sum (a_i-K)^2$ ， 其中 $K=$ $\sum a_i \over n$ 。

**第二步，求出后来的方差**。当序列中的每个数变成原来的 x 倍后，方差会怎么变呢？显然，这个序列的和也变成 x 倍，这个序列的平均值也变成了 x 倍，可以列出当前的方差 S' 为 $S'=$ $\sum (x \times a_i-x \times K) \over n$ $=$ $\sum [x \times (a_i-K)]^2 \over n$ $=$ $\sum x^2 \times (a_i-K)^2 \over n$ $=$ $n \times x^2 \times S \over n$ $=$ $x^2 \times S$

**第三步，总结规律**。所以我们可以知道。 $S'=x^2S$ 。 如果要使 S' 最接近 k ,那么 $x= \sqrt(k/s) $ 。所以我们只需要求出原来的方差就可以一步到位解决问题。

**具体代码如下：**

```cpp
#include<bits/stdc++.h> //懒人专用头文件
using namespace std;
#define int long long//因为我比较懒（你也许已经看出来了），所以我直接写了一个 define 语句
int const N=7*1e6+10;
int a[N]; 
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,k;cin>>n>>k;
    double sum=0;
    for (int i=1;i<=n;i++)cin>>a[i],sum+=a[i];
    sum=sum/(n+0.000);//算平均数
    double ss=0;
    for (int i=1;i<=n;i++) ss+=(a[i]+0.0-sum)*(a[i]+0.0-sum);//算初始的方差
    ss/=n;
    if (ss==0){cout<<"No answer!";return 0;} //特判一下无解的情况
    int l=sqrt(k/ss),af;//直接开方一下
    double an=9e18;
    for (int i=max(l-1,1LL);i<=l+1;i++){
        double ll=(i*i)*ss;
        if (abs(k+0.0-ll)<an){an=abs(k+0.0-ll);af=i;}
    }//注意很可能答案不是 l
    cout<<af<<'\n';//输出
    return 0;
}
```


---

## 作者：_lfxxx_ (赞：0)

### 题意：
给出 $n$ 个数的序列，你可以同时给序列的每个数乘 $x$，问 $x$ 取多少时，方差最接近 $k$（如果有多个数，取最小的数）。

如果无论 $x$ 取什么值方差都为 $0$，输出 `No answer!`。

以上提及的数均为**正整数**。
### 思路：
一道数学题。

考虑 $x$ 的变化对方差的影响。

首先，$a_i$ 和 $\bar x$ 都乘了 $x$，所以此时

$$s^2=\dfrac{\sum_{i=1}^n(x\cdot a_i-x\cdot \bar x)^2}n$$

$$=\dfrac{\sum_{i=1}^n[x(a_i-\bar x)]^2}n$$

$$=\dfrac{\sum_{i=1}^n x^2(a_i-\bar x)^2}n$$

$$=x^2\cdot\dfrac{\sum_{i=1}^n(a_i-\bar x)^2}n$$

所以 $x$ 的意义在于让方差乘 $x^2$。

先求出 $x$ 取到多少与 $k$ 相等，即 $\sqrt{\dfrac{k}{s^2}}$，之后比较它的上下取整求出谁的方差谁更接近 $k$。

**注意：$x$ 为正整数，不能取 $0$（赛时因这个卡了我好久）。**
### 代码：
```cpp
	int main(){
		int n;
		double s(0),avg(0);
		ll k,ans;
		cin>>n>>k;
		for(int i=1;i<=n;++i)
			cin>>a[i],avg+=a[i];
		avg/=n;
		for(int i=1;i<=n;++i)
			s+=(a[i]-avg)*(a[i]-avg);
		s/=n;//s 为方差
		if(!s)
			cout<<"No answer!\n";
		else{
			ans=sqrt(k/s);
			if(!ans)
				cout<<"1\n";
			else
				if(k-ans*ans*s<=(ans+1)*(ans+1)*s-k)
					cout<<ans<<'\n';
				else
					cout<<ans+1<<'\n';
		}
		return 0;
	}
```


---

## 作者：Noby_Glds (赞：0)

这题，很明显暴力是不能过的。

那么，我们来找“方差”的规律。

### 思路：
先把方差公式贴在这里。

![](https://cdn.luogu.com.cn/upload/image_hosting/knveqsbg.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

很明显，当 $a$ 数组中所有数据扩大 $i$ 倍，平均值 $x$ 也会扩大 $i$ 倍。

现在的方差 $s2$ 相较原来的方差 $s$ 就有以下公式：

$s_2=\dfrac{(i \times a_1-i \times x)^2+(i \times a_2-i \times x)^2+...+(i \times a_n-i \times x)^2}{n}$

$s_2=\dfrac{i^2 \times(a_1-x)^2 + i^2 \times(a_2-x)^2 +...+i^2 \times(a_n-x)^2 }{n}$

$s_2=i^2 \times \dfrac{(a_1-x)^2+(a_2-x)^2 +...+(a_n-x)^2}{n}$

$s_2=i^2 \times s$

我们得到这个最终结论后，就向前跨了一大步，可以用 o(1) 的时间求出扩大所有倍数的方差。

有人可能会直接拿着这个公式去枚举倍数找答案，显然会超时，如何一炮命中？

看目标值 $k$ 为多少个原方差的和，再把这个值开平方，得到值 $i$ 便是一个候选答案。

为什么求解过程是这样以及 $i$ 是一个候选答案？我们来简化题意：

**找到一个正整数，使数列 $a$ 的方差乘 $i$ 的平方尽可能等于 $k$。**

我们先找到实数 $i$，使 $s \times i^2=k$。

两边除以 $s$：$i^2=\dfrac{k}{s}$

开平方：$i=\sqrt{\dfrac{k}{s}}$

但由于题目要找的 $i$ 为正整数，而我们得到的 $i$ 很可能是小数。

不妨把 $i$ 转为整数类型，使它向下取整。

那么另一个候选答案大家就应该知道了，为 $i+1$。

以 $i$ 和 $i+1$ 两个数为倍数的方差分别小于等于 $k$ 和大于 $k$。

哪个离 $k$ 最近，哪个就是最终答案。

另外一个问题，何时方差为 $0$？

想让方差为 $0$，$(a_1-x)^2+(a_2-x)^2 +...+(a_n-x)^2$ 的值就得为零，所以每个单项式的值都为 $0$。

所以当 $a_1=a_2=...=a_n=x$ 时，方差就为 $0$，可以输出 $\texttt{No answer!}$ 了。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k;
double x,a[7000010],last,num;
inline long long read(){
	long long now=0,nev=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') nev=-1;c=getchar();}
	while(c>='0'&&c<='9'){now=(now<<1)+(now<<3)+(c&15);c=getchar();}
	return now*nev;
}//€€£给的良心快读。
int main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++) a[i]=read(),x+=a[i];
	x/=n;
	bool fc=true;
	for(int i=1;i<=n-1;i++){
		if(a[i]!=a[i+1]){
			fc=false;
			break;
		}
	}//判断方差是否为0
	if(fc==true&&a[1]==x){
		cout<<"No answer!";
		exit(0);
	} 
	for(int i=1;i<=n;i++) last+=(x-a[i])*(x-a[i]);
	last/=n;
	long long i=sqrt(k/last);//要开long long,因为这个调了好久
	long double last2=last*i*i,num=last*(i+1)*(i+1);
	if(num-k<k-last2) cout<<i+1;
	else cout<<max(i,(long long)1);//题目要求答案为正整数，防止输出0
	return 0;
}
```


---

