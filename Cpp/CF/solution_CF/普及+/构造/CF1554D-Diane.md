# Diane

## 题目描述

### 题意简述

要求您构造一个长度为 $n$ 的由小写字母构成的字符串，使得字符串内每个字串出现奇数次。

## 说明/提示

在第一组数据里， $\texttt{abc}$  的每个子串都恰好只出现一次。

在第三组数据里，$\texttt{bbcaabbba}$ 的每个子串出现奇数次，其中 $\texttt{b}$ 出现 $5$ 次，$\texttt{a}$ 和 $\texttt{bb}$ 各出现 $3$ 次，其它子串各出现 $1$ 次。


对于 $100\%$ 的数据，$1\le t\le 500$，$1\le n \le 10^5$，$1\le \sum n\le 3\times 10^5$。

## 样例 #1

### 输入

```
4
3
5
9
19```

### 输出

```
abc
diane
bbcaabbba
youarethecutestuwuu```

# 题解

## 作者：遮云壑 (赞：16)

## Description
要求构造一个长度为 $n$ 的由小写字母构成的字符串，使得字符串内每个字串出现奇数次。
## Solution
结论+构造

这题有一个很重要的结论，玩出来基本就切了。

先上一张图

![](https://cdn.luogu.com.cn/upload/image_hosting/tfwg64rq.png)


~~我猜你开始拍大腿了~~

没错，说简单一点就是我们小学学过的那个，奇数+偶数=奇数。有由于12345奇偶交错排列，所以我们只要错位相加就行了。

分两类，$n$ 为奇数，中间插一个 $bc$ 使得前后 $a$ 的数量为相邻的一奇一偶。$n$ 为偶数，中间插一个 $b$ 同样使得前后 $a$ 的数量为相邻的一奇一偶。

## code
[出门右转](https://codeforces.com/contest/1554/submission/133930522)

---

## 作者：Jerrlee✅ (赞：10)

## 题意：
造一个长为 $n$ 的字符串（只有小写字母），要求字符串内每个字串出现奇数次。
## 解法：
用 $abc$ 三个字母组就行了，插入在字符串 $s$ 中。

具体分两类， $n \bmod 2==0$ 的和 $n \bmod 2==1$ 的。

1. $n$ 为偶数，字符串左边 $n/2$ 一半放 `a`，插个 `b`，再放 `a`。

2. $n$ 为奇数，字符串左边 $n/2$ 一半放 `a`，插 `bc`，再放 `a`。（注意：要比上面少放一个 `a` ！)

## 优化：

- 优化1：如果是 `1~26` 个字母直接打印 `a` 到那个字母就行了。

得出以下优化的部分代码。
```cpp
if(n<=26){
	for(int i=0;i<n;i++) s+='a'+i;
	cout<<s<<endl;
	continue;
} //优化1
```

- 优化2：当然如果字母数是 26 的奇数倍，直接打印 `a~z`  $n/26$ 遍也行！

## 注意：
样例是对的，但并不是唯一解！比如5个字母时，答案为 `diane`，当然也可以用 `abcde` 和 `aabca` 。
## 总代码：
```cpp
#include<iostream>
using namespace std;
int main(){ //比赛开始前为了速度可以先打好这几行
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		string s;
		if(n<=26){
			for(int i=0;i<n;i++) s+='a'+i; //从 0 开始 s 加的是 ASCII 码（不会的百度）
			cout<<s<<endl;
			continue;
		} //用的优化1
		if(n%2==0){
			for(int i=1;i<n/2;i++) s+='a';
			s+='b';
			for(int i=n/2+1;i<=n;i++) s+='a';
		} //偶数情况
		if(n%2!=0){
			for(int i=1;i<n/2;i++) s+='a';
			s+='b',s+='c'; //用逗号可以缩成一行（我代码追求简洁）
			for(int i=n/2+1;i<=n-1;i++) s+='a'; //n一定要 -1 ，与偶数情况区分开！
		} //奇数情况
		cout<<s<<endl;
	}
	return 0; //好习惯
}
```

[AC记录（洛谷）](https://www.luogu.com.cn/record/54613843)

[AC记录（CF）](https://codeforces.com/contest/1554/submission/124212768)

---

## 作者：Blunt_Feeling (赞：10)

## CF1554D Diane 题解

题意是构造一个长度为 $n$ 的字符串 $s$，使得 $s$ 的每个非空子字符串在 $s$ 中出现奇数次。

不妨将长度分为奇数和偶数讨论。

若长度为偶数，假设 $s$ 全部为`a`，先考虑只把其中一个`a`换成`b`，比如`aabaaaaa`，易得`b`左右两边的两个子串长度为一奇一偶。设这两个`a`串中，较短的长度为 $x$，较长的长度为 $y$，则如果 $y-x$ 的值为 $3$ 或以上（比如上例），则长度为 $y-1$ 的子串必出现 $2$ 次。所以，$x$ 与 $y$ 必是相邻自然数。

$$\begin{cases} x=\left\lfloor\frac{n-1}{2}\right\rfloor \\ y=\left\lfloor\frac{n-1}{2}\right\rfloor+1 \end{cases}$$

------------

若长度为奇数，同样设 $s$ 全部为`a`，先考虑只把其中一个`a`换成`b`，但是这时`b`左右两边的两个子串长度为两奇或两偶。这样就不太妙了，因为较短的那个`a`串必在 $s$ 中出现偶数次。

所以考虑换掉两个字母。只能把一个`a`换成`b`，再挑一个`a`换成`c`。此时 $s$ 中的`a`被拆成了三段，设这三个`a`串长度为 $x,y,z$，奇偶情况为三奇或一奇二偶。

- 如果为三奇，那坏事了，`aa`必出现偶数次。有人说`abaca`不是可以？这个可以，但另外的不行。

- 如果为一奇二偶，不妨设 $x$ 是奇数，$y$ 和 $z$ 都是偶数。首先 $y\ne z$，那既然这样，假设 $y<z$，长度为 $z-1$ 的子串岂不是要出现 $2$ 次了？所以 $x=z-1$。这里有一个绝妙的构造方法：

$$\begin{cases} x=\left\lfloor\frac{n-2}{2}\right\rfloor \\ y=0 \\ z=\left\lfloor\frac{n-2}{2}\right\rfloor+1 \end{cases}$$

---

## 作者：louhao088 (赞：6)

一道巧妙的构造题。

如果想到了就很简单，主要就是想不到。~~其实也挺好想的~~

我们考虑一个全是同一字母的串。如果长度为奇数，那么它的各个奇数长度的子串出现次数为奇数个，偶数长度为偶数个。如果长度为偶数则刚好相反，奇数长度子串出现偶数次，偶数长度出现奇数次。

发现这个的话，之后就很简单了，就是把奇数串，偶数串都放入传中，中间加一个串防止两边影响。很容易证明这样就是对的。

注意要特判 $n=1$ 情况，不然可能会挂。

```cpp
#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define re register
const int maxn=1e5+5;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
void print(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) print(x/10);
    putchar(x%10+'0');
}
int n,m,T,h,y,z,x;
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	T=read();
	while(T--)
	{
		n=read();if(n==1)
		{
			putchar('a');puts("");continue;
		}
		m=n/2;
		for(int i=1;i<=m;i++)putchar('a');putchar('b');
		if(m%2==1)
		{
			x=n-m-1;
			if(x%2==1)
				putchar('c'),x--;
		}
		else 
		{
			x=n-m-1;if(x%2==0)putchar('c'),x--;
		}
		for(int i=1;i<=x;i++)putchar('a');puts("");
	}
 	return 0;
}

```


---

## 作者：npqenqpve (赞：2)

### 题意：

构造一个字符串使得其每个子串都出现奇数次。

### 思路：

考虑极为形式化的构造，摆一堆相同的字符上去，可以发现

- 如果长度为偶数，那么他长度为奇数的子串有偶数个，长度为偶数的子串有奇数个；
- 反之如果长度为奇数，那么长度为奇数的子串奇数个，长度为偶数的子串偶数个。

那么我们可以想到把让相同的子串拼起来，使得偶数变成奇数，那么我们需要一个长度为 $l$ 的字符串和一个长度为 $l-1$ 的字符串达到目标，但是我们需要保证这两个串是相互独立的，只需要在中间添加无关的字符。

简而言之，就是在前面摆 $\frac{n}{2}$ 个某一种字符，在最后摆 $\frac{n}{2}-1$ 个相同种类的字符 ，中间缺失的部分至多只有 $2$ 个，放上无关字符即可，容易证明无关字符不对答案产生影响。



---

## 作者：Demoe (赞：2)

### [题目传送门](https://www.luogu.com.cn/problem/CF1554D)

## $\text{Description}$

- 要求您构造一个长度为 $n$ 的由小写字母构成的字符串，使得字符串内每个字串出现奇数次。

## $\text{Solution}$

我们考虑一个长度为 $n$ 的由一个字符构成的字符串。

它每个长度为 $i$ 的子串出现次数为 $n-i+1$。

拓展到两个字符串即为 $n_1-i+1+n_2-i+1$

即为 $n_1+n_2+2(-i+1)$，发现奇偶性只与 $n_1+n_2$ 有关。

下结论只需要两个**长度奇偶性不同**的同样字符构成的字符串，就可以平衡奇偶性让所有子串出现奇数次。

然而只需要长度奇偶性不同吗？（

这显然不行，因为长的字符串有可能会自己产生出现次数为偶数的子串而此时短的字符串贡献为 $0$（$n-i+1\le 0$ 时）。

那么让两个字符串长度差恰好为 $1$ 即可。

中间只要拿另外的字符当分隔符就行了，易证包含分隔符的子串只会出现一遍。

- $n=1$ 时，$ans= \texttt{a}$。

- $2\mid n$ 时，$ans=\texttt{aa...aba...aa}$。

- $2\nmid n(n\ge 3)$ 时，$ans=\texttt{aa...abca...aa}$。

其中左右两边 $\texttt{a}$ 的个数之差为 $1$。

这样构造即可。

## $\text{Code}$

```cpp
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	rd(T);
	while(T--){
		rd(n);
		if(n==1){puts("a");}
		else if(n&1){
			for(re i=1;i<=n/2-1;++i) putchar('a');
			putchar('b');putchar('c');
			for(re i=1;i<=n/2;++i) putchar('a');
			puts("");
		}
		else{
			for(re i=1;i<=n/2-1;++i) putchar('a');
			putchar('b');
			for(re i=1;i<=n/2;++i) putchar('a');
			puts("");
		}
	}
	return 0;
}
```

---

## 作者：Joshua_He (赞：2)

# 很显然，这是一道贪心题（~~智商题~~）
[题目链接我放着了](https://codeforces.com/contest/1554/problem/D)  
在[我的博客](https://www.cnblogs.com/joshuahxz210/p/15079351.html)食用更佳哦（有翻译）  

晚上实在没空打 CF，第二天早上补题目，看到 D 题的样例输出瞬间懵了，但是感觉不是这样的。  
后来想了半天看了 tags，上面写着 greedy（贪心）。我才想到，只用 $\texttt abc$ 三个字母也可以实现这个题目。

### 有关这道题的基本想法  
左边放 $\displaystyle\frac{1}{2}\cdot n$（向下取整）个 $a$。  
如果是**偶数**个，那中间放个 $b$，**奇数**个就放 $bc$。  
然后再放$\displaystyle\frac{1}{2}\cdot(n-1)$（向下取整）个 $a$ 拿去补剩下的字符。  
这样就可以保证 $a$、$b$、$c$ 都是奇数个，且有关 $a$ 的子字符串也是奇数个。  

## 代码实现
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);//加速
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		if(n%2){//如果是奇数
			if(n=1) cout<<"a\n";//（雷区）这里防止出现 bc 而变成三位字符
			else{
				string s=string(n/2,'a')+"bc"+string(n/2-1,'a');
				cout<<s<<"\n";
			}
		}
		else{
			string s=string(n/2,'a')+"b"+string(n/2-1,'a');
			cout<<s<<"\n";
		}
	}
	return 0;
}//完结撒花
```



---

## 作者：lgmulti (赞：1)

因为这是一道构造题，所以需要首先探索这题的一些性质。这题要求字符串中每个子串重复奇数次，所以就要看一看什么性质可以使得字符串中每个字串出现奇数次。

首先如果某个字母只出现一次，那么这个字母出现的次数必定为奇数次，任意个数的只出现一次的字母组合成的子串也必定只出现一次。

比较难解决的就是出现多次的字母，这时候就要简化问题，首先考虑当这些字母连续时各种子串的出现次数，可以发现若字符串为 $c$ 个连续的相同的字母时，子串“$a$ 个连续的该字母” 的出现次数为 $c-a+1$。若某个 $a$ 满足 $c-a+1$ 为奇数，则 $c-(a-1)+1$ 和 $c-(a+1)+1$ 必为偶数，所以不能只使用连续出现多次的字母作为目标字符串。

若出现多段分割开的连续的相同字母，设共有 $m$ 段，第 $i$ 段有 $c_i$ 个连续的相同的字母，且 $a<\min c_i$，则子串“$a$ 个连续的该字母” 的出现次数为
$$
\sum\limits_{i=1}^m (c_i-a+1)=\sum\limits_{i=1}^m c_i-m(a-1)
$$
当 $\sum_{i=1}^m c_i$ 为偶数时，则若需要满足题目条件，$m(a-1)$ 必须为奇数。而若存在 $a$ 使得 $m(a-1)$ 为奇数，则 $m\left[(a+1)-1\right]$ 和 $m\left[(a-1)-1\right]$ 必为偶数。

而当 $\sum_{i=1}^m c_i$ 为奇数时，$m(a-1)$ 必须为偶数，只要令 $m$ 为偶数，即可满足条件。

为了使得写代码的过程更加简单，令 $m=2$，则要使 $c_1+c_2$ 为奇数，则他们必定一个为奇数、一个为偶数。

此时就有许多种构造方法了，一种简单的方法为令重复的字母为 `a`，$c_1=1$，即在开头先输出一个字母 `a`，然后输出另一个字母作为两段之间的分隔符，然后若 $n$ 为偶数，则输出 $n-2$ 个 `a`，若 $n$ 为奇数，则输出 $n-1$ 个 `a` 和另一个字母，且这个字母不与分隔符相等。

但是我使用的构造方法是在 $n\geq 3$ 时，字符串为
$$
(\lfloor\frac{n}{2}\rfloor-1)\texttt{a} + \texttt{b}+\lfloor\frac{n}{2}\rfloor\texttt{a}+c
$$

代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;

long long t,n;

int main(){	
	long long i,j;
	cin>>t;
	while(t--){
		cin>>n;
		if(n==1)
			cout<<"a\n";
		else if(n==2)
			cout<<"ab\n";
		else{
			for(i=0;i<n/2-1;i++)
				cout<<'a';
			cout<<'b';
			for(i=0;i<n/2;i++)
				cout<<'a';
			if(n&1)
				cout<<'c';
			cout<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Light_Pursuer (赞：0)

# [Diane - 洛谷](https://www.luogu.com.cn/problem/CF1554D) 1800

## Soltion

贪心构造做法。

当 $n=1$ 时，直接输出一个字符 $a$ 即可。

分类讨论 $n$ 的奇偶性情况：

    当 $n$ 为偶数时：

        先输出 $\frac{n}{2}$ 个 字符 $a$，再输出一个字符 $b$，最后输出 $\frac{n}{2}-1$ 个字符 $a$ 即可。

        例如当 $n$ 为 `6` 时，输出：`a a a b a a`。

    当 $n$ 为奇数时：

        先输出 $\frac{n-1}{2}$ 个字符 $a$，再输出一个字符 $b$，接着输出 $\frac{n-1}{2}-1$ 个字符 $a$，最后输出一个字符 $c$。

        例如当 $n$ 为 `7`时，输出：`a a a b a a c`。

code.

```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int ret=0,f=1;char c=getchar();
	while(!(c>='0'&&c<='9'))
	{
		if(c=='-') f=1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		ret=ret*10+c-'0';
		c=getchar();
	}
	return f*ret;
}
int main()
{
	int t;t=read();
	while(t--)
	{
		int n;n=read();
		if(n==1)
		{
			cout<<'a'<<endl;
		}
		else 
		{
			if(n%2==0)
			{
				int x=n/2,y=n/2-1;
				for(int i=1;i<=x;i++)
				{
					cout<<'a';
				}
				cout<<'b';
				for(int i=1;i<=y;i++)
				{
					cout<<'a';
				}
				cout<<endl;
			}
			if(n%2==1)
			{
				int x=(n-1)/2,y=x-1;
				for(int i=1;i<=x;i++)
				{
					cout<<'a';
				}
				cout<<'b';
				for(int i=1;i<=y;i++)
				{
					cout<<'a';
				}
				cout<<"c\n";
			}
		}
	}
	return 0;
}
```

---

## 作者：_Winham_ (赞：0)

思路：

使得构造的一个字符串中每个字串出现奇数次。

挺简单的一道构造体，我们可以输出三个部分，分别为 $\frac{n}{2}$ 长度的 $a$，与一个奇偶次的判断（这一个稍后讲），及最后一个 $\frac{n}{2}-1$长度的 $a$。

这个思路主要就是构造三个部分，能使最优的运算构造这个字符串。

而这个奇偶次的判断:

- 如果 $n$ 为奇数，就输出 $bc$
- 否则，就输出 $b$

这个思路很简单，就是要区分奇偶的区别

```cpp
#include<iostream>
#include<string>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<iomanip>
#include<cstdio>
#include<queue>
#include<stack>
#include<deque>
using namespace std;
#define int long long
const int N = 1e6+10;
const int INF = 0x3f3f3f3f;
int T,n; 
signed main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n/2;i++)cout<<"a";
		if(n>1)cout<<"b";
		if(n&1)cout<<"c";
		for(int i=1;i<n/2;i++)cout<<"a";
		cout<<endl;
	} 
	return 0;//
}
```

---

## 作者：_xxxxx_ (赞：0)

### 题意

$T$ 组数据，每组数据给出一个正整数 $n$，要求构造出一个长为 $n$ 且每个字串出现奇数次的小写字母组成的字符串。

### 分析

首先看到题，第一想法肯定是输出 $n$ 个不同的字母，这样绝对字串出现奇数次。但是小写字母只有 $26$ 个，填不满 $n$。

然后可以想到：我一个字母用多次不就行了吗。

但是，可能单个字母会出现偶数次，不符合条件。但是我们也有别的字母可以用，所以将他补成奇数次就行。

又会出现问题，问题是可能会有长度不为 $1$ 的子串出现在这个连续的字母中。也发现了，发生这个问题的原因是因为连续的字母只有 $1$ 条。所以我们将其分为两段，前面一段，后面一段。

前面一段奇数，后面一段偶数，可以满足要求。

最后处理一下 $n$ 为偶数的情况就行了。

### 代码

```
#include <bits/stdc++.h>
const int N = 1e5 +10;
using namespace std;
int T;
signed main()
{
	cin >> T;
	while(T--)
	{
		int n;
		cin >> n;
		if(n == 1)//特判 
		{
			cout << "a\n";
			continue;
		}
		if(n == 2)//特判 
		{
			cout << "bc\n";
			continue;
		}
		for(int i = 1; i<= (n / 2 - 1); i++)//奇数个 
		{
			cout << "a";
		}
		cout << "bc";//补上 
		if(!(n & 1))
		{
			cout << "d";
			n-=4;//相当于让后面循环少执行2次、
			//2次：d和多了的一个a 
			//n为偶数时，后面a会多一个 
		}
		for(int i = 1; i <= (n / 2); i++)//偶数个 
		{
			cout << "a";
		}
		puts("");//记得换行  
	}
	return 0;
}
```

---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
要求构造一个长度为 $n$ 的由小写字母构成的字符串，使得字符串内每个字串出现奇数次.  
$n\leq 10^5$

## $\text{Solution}$
注意到，一个长度为奇数的字符相同的串中的长度为奇数的子串有奇数个，长度为偶数的子串有偶数个.  
类似的，一个长度为偶数的字符相同的串中的长度为奇数的子串有偶数个，长度为偶数的子串有奇数个.  
所以，我们只需要用两个**长度相差一**的全是 $\text{a}$ 的串填满绝大部分，两者衔接处随便填填  $\text{bcd}$ 什么的就行了.  
~~好奇本题的spj怎么写的.~~
## $\text{code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=2e5+100;
const int mod=51061;
const double eps=1e-9;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}


int n,m;


int main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  int T=read();
  while(T--){
    n=read();
    if(n<=26){
      for(int i=1;i<=n;i++) putchar('a'+i-1);
      putchar('\n');
    }
    else{
      int x=(n-3)/2,y=x+1;
      for(int i=1;i<=x;i++) putchar('a');
      for(int i=1;i<=n-x-y;i++) putchar('a'+i);
      for(int i=1;i<=y;i++) putchar('a');
      putchar('\n');
    }
  }
  return 0;
}

```


---

## 作者：Leasier (赞：0)

这道题显然要让我们把若干单个字符组合起来。

显然，单个字符的组合中长度为奇数的字符出现次数的奇偶性与总长度相同，否则相异。

为了让总出现次数为奇数，我们可以让长度为一奇一偶的字符串组合起来啊！

于是我们令 $m = \lfloor \frac{n}{2} \rfloor$，首先构造 $m$ 个 a，然后根据 $n$ 的奇偶性构造 b 或 bc，最后构造 $m - 1$ 个 a 即可。

代码：
```cpp
#include <stdio.h>

int main(){
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++){
		int n;
		scanf("%d", &n);
		if (n == 1){
			printf("a\n");
		} else {
			int m = n / 2;
			for (int j = 1; j < m; j++){
				printf("a");
			}
			printf("b");
			if (n % 2 == 1) printf("c");
			for (int j = 1; j <= m; j++){
				printf("a");
			}
			printf("\n");
		}
	}
	return 0;
}
```

---

