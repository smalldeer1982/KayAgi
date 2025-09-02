# Tweetuzki 爱等差数列

## 题目描述

Tweetuzki 特别喜欢等差数列。尤其是公差为 $1$ 且全为正整数的等差数列。

显然，对于每一个数 $s$，都能找到一个对应的公差为 $1$ 且全为正整数的等差数列各项之和为 $s$。这时，Tweetuzki 想知道，满足这样条件的等差数列，最小的首项是多少。

由于 Tweetuzki 的数学非常差，尤其是因式分解，所以请你告诉他结果。

## 说明/提示

**样例解释 1**

$2 + 3 + 4 = 9$

**样例解释 2**

$16 = 16$

## 数据范围

对于 $10\%$ 的数据，$s \le 10^6$。  
对于 $100\%$ 的数据，$1 \le s \le 10^{12}$。

## 提示

若有一个数列 $a$，每一项 $a_i$ 都满足 $a_i \in \mathbb{N_{+}}$ 且 $a_i - a_{i - 1} = a_{i + 1} - a_i = 1$，则称这个数列为一个公差为 $1$ 且全为正整数的等差数列。

## 样例 #1

### 输入

```
9```

### 输出

```
2 4```

## 样例 #2

### 输入

```
16```

### 输出

```
16 16```

## 样例 #3

### 输入

```
1000000007```

### 输出

```
500000003 500000004```

# 题解

## 作者：公主殿下MIKU (赞：7)

解释有点小毛病，已修正，谢谢指出

![](https://ss1.baidu.com/6ONXsjip0QIZ8tyhnq/it/u=2838679063,299287394&fm=58)

由等差数列求和公式易得：
![](https://cdn.luogu.com.cn/upload/pic/46318.png)，
而a1为正整数，因此2s>n(n-1),因此2s>(n-1)(n-1),所以n-1一定小于![](https://cdn.luogu.com.cn/upload/pic/45793.png)，即n一定小于![](https://cdn.luogu.com.cn/upload/pic/46319.png)，我们只需倒着枚举n，
找到第一个满足使a1为正整数的n就可以，因为我们是倒着枚举的，所以第一个肯定满足使a1最小，a1+n-1就是末项
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#define ll long long
using namespace std;
ll k;
ll read()
{
    ll f=1,x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
        f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=(x<<3)+(x<<1)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void write(ll x)
{
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
ll ans;
ll a;
int main()
{
    k=read();
    ll num=2*k;
    ll maxx=sqrt(num)+1;
    for(ll i=maxx;i>=1;i--)
    {
        if((num-i*i+i)%(2*i)==0&&(num-i*i+i)>0)//枚举n
        {
            ans=i;
            break;
        }
    }
    a=(num-ans*ans+ans)/(2*ans);
    write(a);
    putchar(' ');
    write(a+ans-1);
    return 0;
}
```

---

## 作者：zhanghzqwq (赞：6)

## c++党的来啊

这道题当黄题还是很水的。只需要从大到小去枚举它的长度，第一个合法的答案，就是最小的答案。当然，这道题对数学要求也比较高的，被小学奥数整晕的误入。

我做题的时候就是按照以下这个几个步骤来的，跟大家推荐一下。

### 1.确定长度范围

显而易见，长度是从大到小枚举快，然而长度最大是多少呢？让我们来看一看等差数列的求和公式吧。其中s是和，a为首项，b为末项，len等于项数。

$s = ( a + b ) \times len \div 2$

$\because a + b > len$

$\therefore len < \sqrt{2s}$

这样我们循环长度就从$\sqrt{2s}$开始,一直循环到1。知道长度范围又该怎么求首项和末项呢？

### 2.求首项和末项

我们还是从等差数列求和公式来看。s是和，a为首项，b为末项，d是公差也就是1，len等于项数。

$s=(a+b)\times len \div 2$

$\therefore (a+b)=s \times 2 \div len$

$\because d = 1$

$\therefore b = a + len - 1$

$\therefore 2a + len - 1 = s \times 2 \div len$

$a = ( s \times 2 \div len - len + 1) \div 2$

$b = a + len - 1$

所谓判合法，就是要判断一下，要除的时候能不能除尽。

最后一点 算取余运算的时候，一定要是同类型的，不能一个用$int$一个用$longlong$了，我一开始就是在这里卡了80分。

代码很短，只有20行，时间复杂度为$\mathcal O(\sqrt n)$，$s<=10^{12}$不会超时。

上AC代码：

```cpp
#include<cmath>
#include<iostream>
using namespace std;
int main(){
	long long s;
	cin>>s;
	for(long long len=sqrt(2*s);len>=1;len--){//len要用long long
		if(s*2%len!=0){//判合法
			continue;
		}
		if((s*2/len-len+1)%2!=0){//再次判合法
			continue;
		}
		long long a=(s*2/len-len+1)/2;//算首项
		long long b=a+len-1;//算末项
		cout<<a<<" "<<b<<endl;//输出a肯定是最小值
		break;//不算了
	} 
	return 0;//完结撒花
}
```


---

## 作者：D2T1 (赞：5)

[$\color{blue}{\text {pwp }~{\to\textbf{My blog}\gets}}~\text{qwq}$](https://www.luogu.com.cn/blog/390770/blogcenter)

## 前置知识

$\sum\limits_{i=1}^n i = \dfrac{n(n+1)}{2}$（$n$ 为正整数）

## 题解

设最终答案为 $l+1$ 与 $r$，则

$$s=\sum\limits_{i=l+1}^r i = \sum\limits_{i=1}^r i-\sum\limits_{i=1}^l i$$

利用公式，得

$$s=\dfrac{r(r+1)}{2}-\dfrac{l(l+1)}{2}$$

$$\therefore 2s=r(r+1)-l(l+1)$$

$$2s=(r+l+1)(r-l)$$

所以我们可以暴力枚举 $2s$ 的因数，求出 $r+l+1$ 和 $r-l$ 的值，进而算出答案。

复杂度 $O(\sqrt{s})$。

## 代码

```cpp
//P5077
#include <cstdio>
typedef long long ll;

int main(){
	ll s,l=0x3f3f3f3f3f3f3f3f,r;
	scanf("%lld",&s); s<<=1;//最后分解质因数的是 2s
	for(ll i=1; i*i<=s; ++i)
		if(s%i==0){
			ll j=s/i;
			if((i&1)^(j&1))//因为 r+l+1 与 r-l 奇偶性不同，所以可以在这进行判断
				if(l>j-i-1)//解二元一次方程组，取 l 的最小值
					l=(j-i-1)/2,r=(j+i-1)/2;
		}
	printf("%lld %lld",l+1,r);//记得答案是 l+1 和 r
	return 0;
}
```

## 补充

可以发现，当 $2s$ 分解出的两个因数的差越小时，$l+1$ 就越小，所以可以在循环时从大到小循环，只要求出一组答案直接结束循环，可以快 21ms。

```cpp
//P5077
#include <cstdio>
#include <cmath>
typedef long long ll;

int main(){
	ll s,l=0x3f3f3f3f3f3f3f3f,r;
	scanf("%lld",&s); s<<=1;
	for(ll i=sqrt(s); i; --i)
		if(s%i==0){
			ll j=s/i;
			if((i&1)^(j&1)){
			    printf("%lld %lld",(j-i+1)/2,(j+i-1)/2);
			    return 0;
			}
		}
}
```

---

## 作者：Leasier (赞：3)

首先抛出一个等差数列求和公式：$$\displaystyle\sum_{i = a}^b i = \dfrac{1}{2}(a + b)(b - a + 1)$$

所以本题就是求出满足 $s = \dfrac{1}{2}(a + b)(b - a + 1)$ 的 $(a, b)$ 的对数。

我们先把上面那个式子变一下形：$2s = (a + b)(b - a + 1)$。

因为 $a + b$ 和 $b - a$ 的奇偶性相同，所以 $a + b$ 和 $b - a + 1$ 的奇偶性相反。

所以本题只需要从 $\lfloor \sqrt{2s} \rfloor$ 到 $1$ 枚举 $2s$ 的因数，判断后求出 $a$ 和 $b$ 的值即可。

$a$ 和 $b$ 的具体求法：

令当前找到的符合条件的因子为 $i$，则我们可以得到以下两个式子：

$$\begin{cases}
i = b - a + 1 \\
\frac{2s}{i} = a + b
\end{cases}$$

将两式相减可得：$\dfrac{2s}{i} - i = 2a - 1$。

移项并整理后可得：$a = \dfrac{-i^2 + i + 2s}{2i}$。

最后，利用 $b = i - a$ 求出 $b$ 的值即可。

代码：
```cpp
#include <stdio.h>
#include <math.h>

typedef long long ll;

int main(){
    ll s, k, t;
    scanf("%lld", &s);
    k = 2 * s;
    t = sqrt(k);
    for (ll i = t; i >= 1; i--){
        if (k % i == 0 && i % 2 != (k / i) % 2){
            ll a = (-i * i + i + k) / (2 * i), b = k / i - a;
            printf("%lld %lld", a, b);
            return 0;
        }
    }
    return 0;
}
```

---

## 作者：一扶苏一 (赞：3)


## Solution

考虑前 $10\%$ 的点，暴力枚举首项，枚举完首项就可以 $O(1)$ 判断是否合法了。期望得分 10 pts

考虑剩下的部分：

一个等差数列的长度只有为奇数和偶数两种可能，下面对这两种可能分类讨论：

对于长度为奇数的情况，设这个等差数列共有 $2x~+~1$ 项，其中中项（最中间）为 $a_k$

因为 $a_{k-i}~+~a_{k+i}~=~2~\times~a_k$，所以 $\sum~a_i~=~(2x~+~1)~a_k~=~s$

同理，对于长度为偶数的情况，设共有 $2x$ 项，其中中间两项为 $a_k~,~a_{k+1}$，因为公差为$1$，所以即为 $a_k~,~a_k~+~1$

于是 $\sum~a_i~=~x(a_k+a_k~+~1)~=~x~(2a_k~+~1)~=~s$

由此我们得到了两种情况的关系式

$$s~=~\begin{cases}(2x~+~1)~a_k \\x~(2a_k~+~1)  \end{cases}$$

其中第一种情况长度为奇数，第二种情况长度为偶数。

注意到这两个式子都是 $s$ 的因数分解，于是考虑直接枚举 $x$ 的因数。

在第一种情况下，因为 $a_k$ 是它的因数，我们考虑枚举 $a_k$，只要枚举到第一个合法的 $a_k$ 即可停止，

第二种情况下，因为 $x$ 是它的因数，我们考虑枚举 $x$，计算所有合法的 $a_k$

另外记得特判一个数是由自己做等差数列的情况

## Code

```cpp
#include <cmath>
#include <cstdio>
#include <algorithm>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#define putchar(o) \
puts("I am a cheater!")
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;

namespace IPT {
	const int L = 1000000;
	char buf[L], *front=buf, *end=buf;
	char GetChar() {
		if (front == end) {
			end = buf + fread(front = buf, 1, L, stdin);
			if (front == end) return -1;
		}
		return *(front++);
	}
}

template <typename T>
inline void qr(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
	if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch = IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = x * 10 + (ch ^ 48), ch = IPT::GetChar();
	if (ch == '.') {
		ch = IPT::GetChar();
		double base = 1;
		while ((ch >= '0') && (ch <= '9')) x += (ch ^ 48) * ((base *= 0.1)), ch = IPT::GetChar();
	}
	if (lst == '-') x = -x;
}

namespace OPT {
	char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
	if (x < 0) {x = -x, putchar('-');}
	rg int top=0;
	do {OPT::buf[++top] = x % 10 + '0';} while (x /= 10);
	while (top) putchar(OPT::buf[top--]);
	if (pt) putchar(aft);
}

ll s, ans = 1000000000000ll, ss;

int main() {
	freopen("1.in", "r", stdin);
	qr(s);
	for (rg ll i = 2; (i * i) <= s; ++i) if(!(s % i)) {		//枚举中项 
		ll k = s / i;
		if (k & 1) {
			ll x = k >> 1;
			if ((i - x) > 0) {
				ans = i - x;
				ss = k;
				break;
			}
		}
	}
	for (rg ll i = 1;  (i * i) <= s; ++i) if (!(s % i)) {	//枚举x 
		ll k = s / i;
		if (k & 1) {
			ll a = k >> 1;
			if ((a - i) > 0) {
				if (ans > a - i) ans = a - i + 1, ss = i << 1;
			}
		}
	}
	if (ans == 1000000000000ll) printf("%lld %lld\n", s, s);
	else {
		qw(ans, ' ', true);
		qw(ans + ss - 1, '\n', true);
	}
	return 0;
}
```



---

## 作者：Aw顿顿 (赞：1)

## $1.0$ 题意概述

一个等差数列 $a$ 满足：

$$a_1+a_2+a_3+\cdots+a_n=s$$

且：

$$a_2-a_1=a_3-a_2=a_4-a_5=\cdots=1$$

求可能存在的最小 $a_1$。

## $2.0$ 解题思路

利用小学奥数，计算一下式子就可以了。

对于每一个项数为 $n$ 的数列 $a$，一定满足：

$$\dfrac{(a_1+a_n)\cdot n}{2}=s$$

$$(a_1+a_n)\cdot n=2s$$

$$a_1+a_n=\dfrac{2s}{n}$$

因为公差为 $1$，所以可以得到：

$$a_1+n-1=a_n$$

据此，我们对于每一个长度 $n$，都可以得到：

$$a_1+a_1+n-1=\dfrac{2s}{n}$$

$$2a_1=\dfrac{2s}{n}-n+1$$

$$a_1=\dfrac{s}{n}-\dfrac{n-1}{2}$$

$$a_1=\dfrac{2s-(n^2-n)}{2n}$$

$$a_1=\dfrac{2s-n^2+n}{2n}$$

此时暴力枚举所有的 $n$ 即可。

对于每一个可能的 $n$，都可以求出其对应 $a_1$ 和 $a_n$，分别判断输出即可。

## $3.0$ 代码实现

此题较简单，代码不附上，欢迎读者自行思考。

在题解区也有不同的思想，可以比较复杂度并思考优化方法。

有问题欢迎私信，感谢阅读。

---

## 作者：SSerxhs (赞：1)

枚举长度，由等差数列求和公式可知，n<=10^12时长度<=2*10^6，复杂度可以接受。

分开奇偶两类情况讨论，若长度为奇数则中间一项为n/i(此时条件为n%i==0)，若长度为偶数则中间两项的平均值为n/i(此时条件为n%i!=0且n*2%i==0），每次更新答案即可。当然也可以倒过来枚举，只要有可行解就输出

```cpp
// luogu-judger-enable-o2
#include <stdio.h>
#include <math.h>
typedef long long ll;
ll n,i,j,l,ans1=9e18,ans2=9e18;
int main()
{
    scanf("%lld",&n);
    l=2e6;
    for (i=1;i<=l;i++) if (n%i==0)
    {
        if ((i&1)&&(ans1>n/i-(i>>1))&&(n/i-(i>>1)>0))
        {
            ans1=n/i-(i>>1);
            ans2=n/i+(i>>1);
        }
    }
    for (i=1;i<=l;i++) if (((n<<1)%i==0)&&(n%i))
    {
        if ((n/i-i/2+1<ans1)&&(n/i-i/2+1>0))
        {
            ans1=n/i-i/2+1;
            ans2=n/i+i/2;
        }
    }
    printf("%lld %lld",ans1,ans2);
}
```

---

## 作者：Ian_Shi (赞：0)

#  _**Idea**_ ：

题目写的很清楚：

这是一道数学题！



#  _**Deduction**_ ：

设最后求的数分别为 $l$ 和 $r$ 且 $l < r$ ；


则有： 

$s = \frac{ (l+r) \times (r-l+1) }{2}$

所以只要枚举 $l+r$ 就能求出 $r-l+1$  ；


之后就进行简单推导，求出 $l$ 和 $r$ ：


$l=\frac{(2 \times s -(l+r)+1)}{2}$

$r=(l+r)-1+\frac{(2 \times s -(l+r)+1)}{2}$

最后输出就行啦！

#   _**AC code：**_ 

```cpp
#include<bits/stdc++.h>
using namespace std;
long long s,d;

int main(){
	scanf("%ld",&n=s);
	d = n * 2;//简单移项
	for(int i = sqrt(d); i >= 1; i--){
		if(d % i == 0 && (d / i - i + 1) % 2 == 0){ //如果l+r不是d公因数，或l不是整数，则不能选
		cout << (d / i - i + 1) / 2 << ' ' << (d / i - i + 1) / 2 + i - 1; //输出了l，r的值
			return 0;
		}
	}
	return 0;
} 
```


---

## 作者：FanYongchen (赞：0)

我们可以设 $(a+b)*(b-a+1)=2*n\  (b>=a)$

所以，这里我们可以枚举 $(b-a+1)$，然后 $(a+b)=2*n/(b-a+1)$（前提是除得尽的情况下）。

为了方便表示，我们令 $i=(b-a+1),j=(a+b)$

然后利用初中学的解二元一次方程，可得

$\begin{cases}b=\dfrac{1}{2}(i+j-1)\\a=j-b\end{cases}$

这是还要判断一下$b$是不是为整数。

最后取个最小值就行了。

复杂度$\sqrt{N}$，过这道题妥妥的。

代码如下：
```cpp
#include <iostream>
#include <cmath>
using namespace std;
#define ll long long
int main()
{
    ll n;
    cin>>n;
    ll minn=n;
    ll ansa=n,ansb=n;//答案为n的情况
    for(ll i=sqrt(2*n);i>=1;i--)
    {
        if(2*n%i!=0) continue;//去掉不符合的
        ll j=2*n/i;
        if((i+j-1)&1) continue;//去掉不符合的
        ll b=(i+j-1)/2,a=j-b;//求出a,b
        if(a<minn) ansa=a,ansb=b,minn=a;//取最小值
    }
    cout<<ansa<<" "<<ansb;//最后愉快的输出
    return 0;
}
```

#### 感谢观看！！！

---

## 作者：Origin0107 (赞：0)

# Problem
Tweetuzki 特别喜欢等差数列。尤其是公差为 $1$ 且全为正整数的等差数列。

显然，对于每一个数 $s$，都能找到一个对应的公差为 $1$ 且全为正整数的等差数列各项之和为 $s$。这时，Tweetuzki 想知道，满足这样条件的等差数列，最小的首项是多少。

由于 Tweetuzki 的数学非常差，尤其是因式分解，所以请你告诉他结果。

简单来说：找到一个首项最大的公差为 $1$ 的等差数列，使得等差数列之和为 $s$ 。
# Solution
首先，枚举首项大小肯定是不可行的，时间复杂度不能接受，我们考虑枚举长度。

设这个长度为 $x$ ，则有一个等差数列 $a+(a+1)+......+(a+x-1)=s$。

根据等差数列求和公式可得 $s=\frac {(a+a+x-1)*x} {2}$ ，又因为 $a$ 为正整数，所以可以得到 $a+a+x-1>x$ ，即 $s=\frac {(a+a+x-1)*x} {2}>\frac {x^2}{2}$ ，所以 $x<=\sqrt{2s}$ ，只需要从 $\sqrt{2s}+1$ 开始倒序枚举就可以了（倒序枚举保证首项最小）。

上述式子可以化简为 $a*x+\frac {x*(x-1)} {2}$ ，所以当 $s-\frac {x*(x-1)} {2} \bmod x=0$ 的时候，$\frac {s-\frac {x*(x-1)} {2}} {x}$ 即为首项的值。

还有一点，所有变量都要开 $long long$ 否则会被卡50pts。
# Code
```
#include<bits/stdc++.h>
using namespace std;
bool flag;
int main()
{
    flag=0;
    long long n;
    cin>>n;
    long long x=sqrt(2*n);
    for(long long i=x+1;i>=2;i--)
    {
        if(n-((i+1)*i/2)<0) continue;
        if((n-((i+1)*i/2))%i==0)
        {
            long long ans=(n-((i+1)*i/2))/i;
            cout<<ans+1<<" "<<ans+i<<endl;
            flag=1;
            break;
        }
    }
    if(!flag) cout<<n<<" "<<n<<endl;
    return 0;
}
```



---

