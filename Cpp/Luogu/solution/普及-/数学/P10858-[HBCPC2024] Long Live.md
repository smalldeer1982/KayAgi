# [HBCPC2024] Long Live

## 题目描述

在 Minecraft 中，简单世界中有三个维度，其中一个被称为“The End”。在这个维度中，末影龙通常被象征为 Minecraft 的最终 Boss。

现在，我们、你和Steve想要打败这条龙。然而，我们发现这条龙出了一道谜题来困扰我们。在与龙战斗之前，我们必须先解开这个谜题。请站在我们这边，与龙一同战斗。谜题如下：

给定两个正整数 $x$ 和 $y$，请找到两个整数 $a$ 和 $b$，使得

$$\sqrt{\dfrac{\operatorname{lcm}(x,y)}{\gcd(x,y)}}=a\sqrt{b}$$

并使 $a \cdot b$ 最大化。

其中，$\gcd(a, b)$ 表示 $a$ 和 $b$ 的最大公约数，而 $\operatorname{lcm}(a, b)$ 表示 $a$ 和 $b$ 的最小公倍数。

## 说明/提示

亲爱的所有参赛者：

这个问题可能是故事的开篇，但绝不是故事的结尾。请一直相信自己，愿我的歌声伴随你们，“致我们曾一起翻越的高山，与你并肩战斗巨龙的时光，我度过了生命中最美好的时光”。

翻译者：[Immunoglobules](https://www.luogu.com.cn/user/1066251)

## 样例 #1

### 输入

```
2
1 1
4 4```

### 输出

```
1 1
1 1```

# 题解

## 作者：x1489631649 (赞：7)

### [题目链接](https://www.luogu.com.cn/problem/P10858)
### 输入 
多组数据，每组数据两个整数 $x,y(1 \le x,y \le 10^9)$。
### 输出
**最小公倍数**除以**最大公因数**开根号然后找到两个数 $a$ 与 $b$ ，将 $b$ 的开根号在乘 $a$ 等于那个数，且使得 $a \times b$ 的积最大。
### 分析
1. 首先我们将等式两边**同时平方**可得最小公倍数除以最大公因数等于 $a^2 \times b$。
2. 转移使得 $a \times b$ 等于最小公倍数除以最大公因数与 $a$ 的乘积。由于最小公倍数和最大公因数已经确定，所以只需要让 $a$ 尽量小，而 $a$ 的最小值只能是 $1$。
### 实现
我们可以使用系统自带的函数 $\gcd$ 来进行求值然后再用**最小公倍数乘最大公因数等于两个数的积**来求出最小公倍数。
 ### Code
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	unsigned long long t,x,y,flag;
	cin>>t;
	while(t--)
	{
		cin>>x>>y;
		if(x>y)
			swap(x,y);
		cout<<"1 "<<(x*y/__gcd(x,y))/__gcd(x,y)<<endl;
	}
} 
```
### 时间复杂度
时间复杂度为 $O(t\log V)$，其中 $V$ 是值域，显然可以通过。

---

## 作者：luogu_gza (赞：6)

由于 $\operatorname{lcm}$ 总是 $\gcd$ 的倍数，我们钦定 $x=1$，则 $y=\frac{\operatorname{lcm}(x,y)}{\gcd(x,y)}$。

代码不难。

---

## 作者：_Star_Universe_ (赞：4)

## [题目传送门](https://www.luogu.com.cn/problem/P10858)
### 题意
给你两个数 $x,y$，请你求出一组 $(a,b)$ 使得：
$$\sqrt \frac{\operatorname{lcm}(x,y)}{\gcd(x,y)} = a \sqrt b$$
且 $a \times b$ 的值最大。

### 概念
先说明一下 $\gcd(x,y)$ 表示 $x$ 和 $y$ 的最大公因数，$\operatorname{lcm}(x,y)$ 则表示 $x$ 与 $y$ 的最小公倍数。

### 思路
一道简单的数学题。

首先两边同时开平方，得到：
$$\frac{\operatorname{lcm}(x,y)}{\gcd(x,y)} = a^2 \times b$$

两边同除以 $a$，得到：
$$\frac{\operatorname{lcm}(x,y)}{\gcd(x,y)} \div a = a \times b$$

由于我们希望 $a \times b$ 较大，所以 $a$ 为 $1$，将 $a=1$ 代入得 $b$：
$$b = \frac{\operatorname{lcm}(x,y)}{\gcd(x,y)}$$

那我们就可以定义一个变量存 $\gcd(x,y)$，可以使用 C++ 自带的 $\gcd$ 函数求得。那么 $\operatorname{lcm}(x,y)$ 怎么得到呢？这里给出公式：
$$\operatorname{lcm}(x,y)=\frac{x \times y}{\gcd(x,y)}$$

最后注意数据范围 $1 \le x,y \le 10^9$，相乘必定会溢出 `int`，所以要开 `long long`。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int T;
signed main(){
	cin>>T;
	while(T--){
		int x,y;
		cin>>x>>y;
		int g=__gcd(x,y);
		int l=x*y/g;
		cout<<1<<" "<<l/g<<endl;
	}
	return 0;
}
```

---

## 作者：FinderHT (赞：2)

### 题意简述

给定正整数 $x,y$，找到正整数 $a,b$，使得 $\sqrt{\frac{\operatorname{lcm}(x,y)}{\gcd(x,y)}}=a\sqrt{b}$，且的值 $a\cdot b$ 最大。 

### 题解

注意到 $a\cdot b=\frac{a^2b}{a}=\frac{(a\sqrt{b})^2}{a}$，结合式子 $\sqrt{\frac{\operatorname{lcm}(x,y)}{\gcd(x,y)}}=a\sqrt{b}$ 可知 $a\cdot b=\frac{\operatorname{lcm}(x,y)}{\gcd(x,y)\cdot a}$，显然 $a=1$ 时 $a\cdot b$ 最大，带入上式得 $b=\frac{\operatorname{lcm}(x,y)}{\gcd(x,y)}$，就做完了。

### 代码

[Code](https://www.luogu.com.cn/paste/n8jfybby)

---

## 作者：_Deer_Peach_ (赞：2)

简单数学题：

题意：

给出两个数 $x$ 和 $y$，求一组 $(a,b)$ 使得 $\sqrt{\frac{\operatorname{lcm}(x,y)}{\gcd(x,y)}} = a \times \sqrt{b}$ 且 $a \times b$ 最大。

思路：

首先化简式子，两边平方得到 $\frac{\operatorname{lcm}(x,y)}{\gcd(x,y)} = a^2 \times b$。

为了得出 $a \times b$，两边同时除以 $a$，因为要使 $a \times b$ 的值最大，且 $\frac{\operatorname{lcm}(x,y)}{\gcd(x,y)}$ 是定值，所以 $a$ 要尽可能小，所以 $a$ 就是 $1$，$b=\frac{\operatorname{lcm}(x,y)}{\gcd(x,y)}$。

那我们就可以先算出来 $x$ 和 $y$ 的最大公因数和最小公倍数，然后算出 $a$ 和 $b$。

代码：
```
#include<bits/stdc++.h>
#define int long long//养成好习惯
using namespace std;
int t;signed main(){
	cin>>t;while(t--){
		int x,y;cin>>x>>y;
		int gcd=__gcd(x,y);//最大公因数
		int lcm=x*y/gcd;//最小公倍数
		cout<<1<<" "<<lcm/gcd<<endl;//a和b
	}return 0;
}
```

---

## 作者：xingshuyan000 (赞：2)

[题目传送门：洛谷 P10858](https://www.luogu.com.cn/problem/P10858)

# 题目大意

~~（前两段是废话，可以直接忽略）~~

给定两个正整数 $x$ 和 $y$，请找到两个整数 $a$ 和 $b$，使得

$$\sqrt{\dfrac{\operatorname{lcm}(x,y)}{\gcd(x,y)}}=a\sqrt{b}$$

并且最大化 $a \cdot b$。请你输出当 $a \cdot b$ 最大时 $a,b$ 的值分别是多少，这里的 $a,b$ 都是整数。

# 题目分析

这是一道比较简单的数学题。

这里的 $\gcd(a, b)$ 表示 $a$ 和 $b$ 的最大公约数，$\operatorname{lcm}(a, b)$ 表示 $a$ 和 $b$ 的最小公倍数。数学符号应该不用我做过多解释吧。

### 第一步，理解公式
根据数学知识，我们可以得到 
$$\gcd(x,y) \cdot \operatorname{lcm}(x,y)=x\cdot y$$

### 第二步，通过数学推导简化公式
经过简单的数学变换，我们可以得到
$$\operatorname{lcm}(x,y)=\frac{xy}{\gcd(x,y)}$$

等号两边同时除以 $\gcd(x,y)$ 并开根号得

$$\sqrt{\dfrac{\operatorname{lcm}(x,y)}{\gcd(x,y)}}=\frac{\sqrt{xy}}{\gcd(x,y)}$$

这样，我们可以得到

$$\frac{\sqrt{xy}}{\gcd(x,y)}=a\sqrt{b}$$

然后为了方便一些，我再把等号两边同时平方了，得到
$$\frac{xy}{\gcd^2(x,y)}=a^2b$$

这样，等号左边就变成了 $\frac{x}{\gcd(x,y)}\cdot\frac{y}{\gcd(x,y)}$，而 $\gcd(x,y)$ 一定是 $x$ 和 $y$ 的因数，所以两个分式都能整除。

为了方便表示，我设 $n=\frac{x}{\gcd(x,y)},m=\frac{y}{\gcd(x,y)}$ ，这样，上面得到的式子就变成了
$$n\cdot m=a^2\cdot b$$

### 第三步，确定 $a,b$ 的值

因为等号左边的 $n \cdot m$ 是一个定值，所以 $a^2 \cdot b$ 一定也是一个定值，而我们要保证 $a \cdot b$ 最大，而 $a \cdot b=\frac{a^2 \cdot b}{a}$，也就是说我们要找一个整数 $a$ 的最小值。

这里我们注意一下，**因为在最开始的式子中，$b$ 是在根号内部的，所以 $b$ 必须是一个正数**。我只是为了方便计算，让等号两边同时平方了，其实这不是一个等价变形，只是这样做等号仍成立，但数据的范围其实是扩大了，不过不影响分析。

因为 $b>0$，等号左边 $n \cdot m>0$，所以 $a \in \mathbb{N}^*$，而又要保证 $a$ 的值最小，所以 $a=1$，此时 $b=n \cdot m$。

综上所述，$a=1,b=\frac{xy}{\gcd^2(x,y)}$。

### 第四步，编程实现

分析完了，编程实现应该就很简单了吧。

我这里提一下用 C++ 求两个数的最大公约数和最小公倍数的方法。（我直接上代码，具体分析可以自己去查）

**最大公约数**

可以用辗转相除法（也就是欧几里得算法）求两个数的最大公约数（实现方法如下代码），或者也可以用 STL 的内置函数 `__gcd()` 来求，这个函数包含在头文件 `<algorithm>` 里面。


```cpp
int gcd(int x,int y)
{
	while(y)
	{
		int temp = x % y;
		x = y;
		y = temp;
	}
	return x;
}
```

**最小公倍数**

根据上文我提到的式子：
$$\gcd(x,y) \cdot \operatorname{lcm}(x,y)=x\cdot y$$

我们可以得到，两个数的最小公倍数就是它们的乘积除以它们的最大公约数的商，那么这样最小公倍数也很好求了。以下是编程实现（此题用不到）：


```cpp
int lcm(int x,int y)
{
	int g=gcd(x,y);
	int l=(x*y)/g;
	return l;
}
```
最后提醒一下：**不开 `long long` 见祖宗**。

# Code

分析完了，展示一下我的代码吧。

```cpp
#include<iostream>
using namespace std;
#define LL long long
LL gcd(LL x,LL y)
{
	while(y)
	{
		LL temp=x%y;
		x=y;
		y=temp;
	}
	return x;
}
int main()
{
	ios::sync_with_stdio(0);
	int T;
	cin>>T;
	while(T--)
	{
		LL x,y;
		cin>>x>>y;
		LL g=gcd(x,y);
		LL n=x/g,m=y/g;
		LL b=n*m;
		cout<<"1 "<<b<<"\n";
	}
	return 0;
}

---

## 作者：Vct14 (赞：1)

本场第二道签到题。

首先，对于一个二次根式 $\sqrt x$，如果存在 $p^2\mid x$，设 $x=p^2\times s$，那么将 $p$ 提出根式，得到 $\sqrt x=p\sqrt s$，而 $ps<p^2s=x$，因此不提出更优。所以我们需要尽量使得 $a=1$，也就是求出左式结果后不进行化简，即 $a=1,b=\dfrac{\operatorname{lcm}(x,y)}{\gcd(x,y)}$。

又有性质 $\operatorname{lcm}(x,y)\times\gcd(x,y)=xy$，可以得到 $b=\dfrac{xy}{\gcd(x,y)^2}$。

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	int t;cin>>t;
	while(t--){
		int x,y;cin>>x>>y;
		int g=__gcd(x,y);
		cout<<"1 "<<(x/g)*(y/g)<<"\n";
	} 
	return 0;
}
```

如何证明性质 $\operatorname{lcm}(a,b)\times\gcd(a,b)=ab$？设 $\gcd(a,b)=g,a=gx,b=gy,\gcd(x,y)=1$。那么 $\operatorname{lcm}(a,b)=gxy$，则 $ab=g^2xy=\operatorname{lcm}(a,b)\times\gcd(a,b)$。

---

## 作者：joker_opof_qaq (赞：1)

模拟题目，按照题意模拟

[题目传送门](https://www.luogu.com.cn/problem/P10858)

### 题意简述

给你 $x$ 和 $y$，求出 $a$ 和 $b$ 使 $\sqrt{\dfrac{\operatorname{lcm}(x,y)}{\gcd(x,y)}}=a\sqrt{b}$。

### 思路来源

因为要使 $a \times b$ 最大，而如果使 $a$ 变大 $k$ 倍，那么 $b$ 就要变小 $k^2$ 倍，而 $k \in N$ 所以 $a$ 要取最小的数，即 $1$，剩下的数全都当 $b$ 的因数就行了。

最后打印 $1$ 和 $x \times y \div \gcd(x,y)^2$ 就可以了！

### AC CODE && 提交记录

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<iomanip>
#include<string>
#include<cmath>
#include<queue>
#include<map>
#include<list>
#include<stack>
#include<cctype>
#include<cstdlib>
#define int long long
#define gcd __gcd
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
	return x*f;
}
inline void write(int x) {
	if (x<0)x=-x,putchar('-');
	if (x>9)write(x/10);
	putchar(x%10+'0');
}
int lcm(int a,int b){
	return a/__gcd(a,b)*b;
}
signed main(){
	int t=read();
	while(t--){
		int x=read(),y=read();
	    int ans=x*y/gcd(x,y)/gcd(x,y);
		cout<<1<<' '<<ans<<endl;
	}
    return 0;
}
```

[link](https://www.luogu.com.cn/record/171967395)

---

## 作者：_Weslie_ (赞：1)

签到题，但是不如 E。

## 题意简述

给定 $x$ 和 $y$。求一组 $(a,b)$ 使 $\sqrt{\dfrac{\operatorname{lcm}(x,y)}{\gcd(x,y)}}=a\sqrt{b}$ 且 $a\times b$ 最大。

## 思路

两边平方，得 $\dfrac{\operatorname{lcm}(x,y)}{\gcd(x,y)}=a^2b$。

两边同时除以 $a$，得 $\dfrac{\frac{\operatorname{lcm}(x,y)}{\gcd(x,y)}}{a}=ab$。

$\dfrac{\operatorname{lcm}(x,y)}{\gcd(x,y)}$ 是定值，所以我们要 $a$ 最小。

$a$ 最小显然是 $1$，则 $b$ 是 $\dfrac{\operatorname{lcm}(x,y)}{\gcd(x,y)}$，于是输出即可。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
void solve(long long a,long long b){
	long long g=(a*b/__gcd(a,b))/__gcd(a,b);
	printf("1 %lld\n",g);
}
int T;
long long a,b;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%lld%lld",&a,&b);
		solve(a,b);
	}
	return 0;
}
```

---

## 作者：Milkshakefairytale (赞：0)

作者应该是一个 MC 玩家，图片运用了我们可爱的末影龙。

## 大致题意

### 题意

在 Minecraft 中，简单世界有三个维度，其中一个被称为“末地”。在这个维度上，末影龙通常被象征为《我的世界》的最终 boss。

现在我们、你和史蒂夫想打败龙。然而，我们发现龙在讲一个谜题。我们必须先解决这个问题，然后再与龙作战。请站在我们这边与龙作战。谜题如下。

给定两个正整数 $ x $ 和 $ y $ ，请找到两个整数 $ a $ 和 $ b $ ，使得这个式子成立，并且使 $ a ⋅ b $ 最大化：

$$  \sqrt{\frac{\operatorname{lcm}(x,y)}{\gcd (x,y) } }  $$ = a$$ \sqrt{b}$$（$ \operatorname{lcm}$是最小公倍数，$\gcd$是最大公约数）

### 输入格式

第一行输入一个 $ T $ ，表示有 $ T $ 组数据。

接下来 $ T $ 行，每行输入 $ x ,y $ 。

### 输出格式

输出满足题意的 $ a , b $ 。

### 数据范围

$$ 1 \le T \le 1 \times 10^4 $$

$$ 1 \le x,y \le 1 \times 10^9 $$

## 题目分析

相信大家都会求出最小公倍数和最大公约数，但是怎么求出a和b是一个很大的问题。

对于这个式子：$$  \sqrt{\frac{\operatorname{lcm}(x,y)}{\gcd(x,y)}}  $$ = a$$ \sqrt{b}$$ 我们可以进行一次两边平方的操作。

式子就会变为$$ \frac{\operatorname{lcm}(x,y)}{\gcd(x,y)} $$ = $a^ {2}\times b$ ，看起来比原来好一点了。

对于这个式子我们不难分析出，对于每组数据来说$$ \frac{\operatorname{lcm}(x,y)}{\gcd(x,y)} $$ 都是一个定值，那么如果要使 $ a \times b $ 最大，$ a $ 一定要最小，所以说 $ a $ 一定是 $ 1 $ ，而 $ b $ 是$$ \frac{\operatorname{lcm}(x,y)}{\gcd(x,y)} $$。

## 代码
```cmp
#include<bits/stdc++.h>
using namespace std;
inline int read() {//快读函数 
    int s = 0, f = 1;
    char ch = getchar();
    while ('0' > ch || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
    while ('0' <= ch && ch <= '9') {s = (s << 3) + (s << 1) + ch - 48; ch = getchar();}
    return s * f;
}
inline void write(int x)//快写函数 
{
    if(x<0){
    	putchar('-');
		x=-x;
	}
    if(x>9)
		write(x/10);
    putchar(x%10+'0');
}
int t;
long long x,y,a,b;//不开long long等着WA吧 
int main()
{
	t=read();
	while(t--)
	{
		cin>>x>>y;
		a=1;
		long long lcm=x*y/__gcd(x,y);//最小公倍数，__gcd()代表最大公因数 
		b=lcm/__gcd(x,y);
		cout<<a<<" "<<b<<endl;
	}
	return 0;
}
```

---

## 作者：Your_Name (赞：0)

## 思路

首先发现左边的那个数是一个定值，且把式子化简一下可以得到：

* $$\dfrac{\operatorname{lcm}(x,y)}{\gcd(x,y)}=a^2b=ab \times a$$

为了最大化 $ab$ 我们直接让 $a = 1$ 即可。

至于左边的数，我们可以化简得到：

* $$\dfrac{\operatorname{lcm}(x,y)}{\gcd(x,y)}=\dfrac{x \times y}{\gcd(x,y) ^ 2}

不难发现结果一定为整数（因为 $x$ 和 $y$ 里都有一个 $\gcd(x,y)$）,所以直接用库函数求就行，具体看代码。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t, x, y;
int main(){
    cin >> t;
    while(t --){
        cin >> x >> y;
        long long k = 1ll * (x * y) / (1ll *(1ll * __gcd(x, y) * 1ll * __gcd(x, y)));//不开long long见祖宗！
        cout << "1 " << k << endl;
    }
    return 0;
}
```
 _完结撒花_

---

## 作者：_QWQ__QWQ_ (赞：0)

给你两个数 $x,y$ 让你找到一组 $a,b$，使 $\sqrt{\frac{\operatorname{lcm}(x,y)}{\gcd(x,y)}}=a\sqrt{b}$，且 $a\cdot b$ 最大。


由最小公倍数和最大公约数的性质，我们知道：
$$ \operatorname{lcm}(x, y) \cdot \gcd(x, y) = x \cdot y $$

代入原式得：
$$ \sqrt{\frac{\operatorname{lcm}(x, y)}{\gcd(x, y)}} = \sqrt{\frac{x \cdot y}{\gcd(x, y)^2}} $$

设 $k = \frac{x \cdot y}{\gcd(x, y)^2}$，则原式变为：
$$ \sqrt{k} $$

为了将 $\sqrt{k}$ 分解为 $a \sqrt{b}$ 的形式，我们需要找到 $k$ 的最大整数平方因子 $m^2$（即 $m$ 是 $k$ 的因子且 $m^2$ 尽可能大）。

所以得出结论：$a=1$，$b=\frac{\operatorname{lcm}(x,y)}{\gcd(x,y)}$。

考时代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
const int maxn=1e6+5;
int t;
int n,x,a,b;
signed main(){
	cin>>t;
	while(t--){
		cin>>a>>b;
		cout<<'1'<<' '<<(a*b/__gcd(a,b))/__gcd(a,b)<<endl;
	}
	return 0;
}
```

~~因为写反了还吃了一发罚时~~

---

## 作者：SecuritySetting (赞：0)

题意：

给出两个数 $x$ 和 $y$，求出满足 $\sqrt{\frac{\operatorname{lcm}(x,y)}{\gcd(x,y)}} = a \times \sqrt{b}$ 的两个数 $a$ 和 $b$ 并使 $a$ 和 $b$ 的乘积最大。

思路：

直接硬推式子，两边乘以平方可以得到 $\frac{\operatorname{lcm}(x,y)}{\gcd(x,y)} = a^2 \times b$。那么一眼可以看出 $a \times b = \frac{\frac{\operatorname{lcm}(x,y)}{\gcd(x,y)}}{a}$。既然要使 $a$ 和 $b$ 的乘积最大，那么 $\frac{\frac{\operatorname{lcm}(x,y)}{\gcd(x,y)}}{a}$ 的值也要大，那么 $a$ 要尽可能小，$a$ 最小为 $1$，所以 $a$ 就是 $1$，$b$ 就是 $\frac{\operatorname{lcm}(x,y)}{\gcd(x,y)}$。

代码：
```
#include <bits/stdc++.h>
using namespace std;
int t;
int main() {
	cin >> t;
	while ( t --) {
		long long x, y;
		cin >> x >> y;
		long long g = __gcd(x, y);//最大公因数 
		long long l = x * y / g;//最大公因数乘以最小公倍数等于这两个数的乘积
		long long a = 1, b = l / g; 
		cout << a << " " << b << endl;
	}return 0;
}
```

---

## 作者：xinxin2022 (赞：0)

## 题意

给定  $x,y$，求一组 $a,b$ 满足：

$$\sqrt{\frac{\operatorname{lcm}(x,y)}{\gcd(x,y)}}=a \sqrt{b}$$ 

且 $ab$ 的值尽可能大。

## 思路

首先有公式：

$$\operatorname{lcm}(x,y) = \frac{ab}{\gcd(a,b)}$$

这个公式可以这样求出：

首先 $ab$ 必然是 $a,b$ 两数的公倍数。

然后设 $x$ 为 $ab$，如果 $a$ 和 $b$ 有相同因数，则 $x$ 在除掉这个因数的时候仍然既是 $a$ 的倍数又是 $b$ 的倍数。

而 $\gcd(a,b)$ 可求出 $a,b$ 两数的最大公因数，那 $x$ 除以 $\gcd(a,b)$ 后便可得到两数的最小公倍数。

因此式子可以简化为：

$$\sqrt{\frac{xy}{\gcd(x,y)^2}} = a \sqrt{b}$$

显然 $gcd(x,y)$ 可以使用辗转相除法在 $\log x$ 的时间复杂度以内求出，因此我们要做的就是继续简化这个式子，让它能用非枚举的方式求出。

首先因为 $a,b$ 都是整数，所以 

$$\frac{xy}{\gcd(x,y)^2}$$

也必然是整数。

而既然两侧都有根号出现，而且两侧的数在没有根号的情况下都是整数，又因为 $b$ 在等式里带根号，在 $ab$ 尽可能大的条件下显然要让 $a$ 尽可能小，所以 $a$ 可以等于 $1$。

等式简化为：

$$ \sqrt{\frac{xy}{\gcd(x,y)^2}} = \sqrt{b}$$

而

$$\sqrt{\frac{xy}{\gcd(x,y)^2}} = \sqrt{b}$$

$$(\sqrt{\frac{xy}{\gcd(x,y)^2}})^2 = (\sqrt{b})^2$$

$$\frac{xy}{\gcd(x,y)^2} = b$$

所以现在只需要求

$$\frac{xy}{\gcd(x,y)}$$

即可。

代码如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
long long a,b;
int main(){
    cin>>t;
    for(int i=1;i<=t;i++){
        cin>>a>>b;
        cout<<"1 "<<a*b/__gcd(a,b)/__gcd(a,b)<<'\n';
        //此处使用库函数__gcd()求a和b的最大公因数
    }
    return 0;
}
```

以下是时间复杂度的分析：

辗转相除法求 $\gcd(a,b)$ 所用的时间为 $\log a$，因此程序的时间复杂度为：

$$O(\sum_{i=1}^{T} \log x_i)$$

以下是资料：

[辗转相除法的证明](https://www.cnblogs.com/kentle/p/13553261.html)

[辗转相除法的理论学习与证明](http://www.shadafang.com/a/202302/5176111.html)

---

