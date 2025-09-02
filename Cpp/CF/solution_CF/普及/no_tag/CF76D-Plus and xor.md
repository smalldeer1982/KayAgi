# Plus and xor

## 题目描述

Bitwise exclusive OR (or bitwise addition modulo two) is a binary operation which is equivalent to applying logical exclusive OR to every pair of bits located on the same positions in binary notation of operands. In other words, a binary digit of the result is equal to 1 if and only if bits on the respective positions in the operands are different.

For example, if $ X=109_{10}=1101101_{2} $ , $ Y=41_{10}=101001_{2} $ , then:

 $ X $ xor $ Y = 68_{10} = 1000100_{2} $ . Write a program, which takes two non-negative integers $ A $ and $ B $ as an input and finds two non-negative integers $ X $ and $ Y $ , which satisfy the following conditions:

- $ A=X+Y $
- $ B = X $ xor $ Y $ , where xor is bitwise exclusive or.
- $ X $ is the smallest number among all numbers for which the first two conditions are true.

## 样例 #1

### 输入

```
142
76
```

### 输出

```
33 109
```

# 题解

## 作者：正负君 (赞：7)


# CF76D Plus and xor 题解

# 简化题意
~~一道大水题……~~

给出两个正整数 $A,B$，使 $X,Y$ 满足以下条件：
$$ \left\{
\begin{aligned}
X+Y=A\\
X\oplus Y=B \\
\end{aligned}
\right.
$$
- 且要求 $X$ 是所有满足前两个条件中最小的，如果无解，输出 $-1$，否则，输出 $X,Y$。
- $\oplus$ 代表异或。

# 分析
[这里](https://baike.baidu.com/item/%E5%BC%82%E6%88%96/10993677?fr=aladdin)  
先科普一下异或（$\oplus$），也叫半加运算，就是加法竖式不进位一样。  
举个“栗”子：  $729+534$ 和 $729 \oplus 534$  

$$729_{10}=1011011001_2$$
$$534_{10}=1000010110_2$$  
先看 $729+534$：
![](https://cdn.luogu.com.cn/upload/image_hosting/zxwry24q.png)
$$
\begin{aligned}
& 729_{10}+534_{10} \\
=& 1011011001_2+1000010110_2 \\
=& 10011101111_2 \\
=& 1263_{10}
\end{aligned}
$$

让我们再看看 $729 \oplus 534$：  
![](https://cdn.luogu.com.cn/upload/image_hosting/bwk381p0.png)
$$
\begin{aligned}
& 729_{10}\oplus534_{10} \\
=& 1011011001_2\oplus 1000010110_2 \\
=& 11001111_2 \\
=& 207_{10}
\end{aligned}
$$

我们再把这两个结果对比一下：  
![](https://cdn.luogu.com.cn/upload/image_hosting/6baqtxqt.png)

我们发现加法所得的结果只会比异或的结果多一些二进制下的 $1$！  
异或是不进位的加法，因此 $A-B$ 表示的就是 $X+Y$ 的进位情况。  
由于加法得到的进位情况会是异或的 $2$ 倍。所有 $(A-B)\div2$ 是 $X$ 和 $Y$ 的共同都有的部分。所有 $X$ 可以认为是 $(A-B)\div2$。  

# 代码
接下来附上~~你们最爱的~~完整代码：  
```cpp
#include<iostream>
using namespace std;
unsigned long long int A,B,X,Y;
//坑点，2^64-1,需要unsigned long long int!
int main()
{
  cin>>A>>B;//输入
  if(A<B||A-B&1)
  {         //无解
    cout<<-1<<endl;
  }
  else
  { 
    X=A-B>>1;
    Y=A-X;
    cout<<X<<' '<<Y<<endl;
  }
  return 0; //养成好习惯~
}
```
管理大大审核辛苦啦！

---

## 作者：badFlamesへ (赞：4)

# 题解 CF76D
这是一道不错的位运算性质题。

我们先来了解几个柿子（可以下去自己推推看）：

（此处$\operatorname{and}$为按位与，$\operatorname{or}$为按位或，$\operatorname{xor}$为按位异或）

------------

$a\operatorname{and}b+a\operatorname{xor}b=a\operatorname{or}b$ （1）

$a+b=a\operatorname{or}b+a\operatorname{and}b=a\operatorname{xor}b+2\times (a\operatorname{and}b)$ （2）

------------

我们发现，题目中告诉了我们 $x+y$ 和 $x\operatorname{xor}y$ 的值

那么自然而然地， $x\operatorname{and}y$ 的值就是可求并且是固定的了

考虑在 $x+y$ 中，要使 $x$ 的值最小，就让 $x$ 在 $x\operatorname{and}y$ 中的“贡献”尽量少

对于 $x\operatorname{and}y$ 的每一位，若当前位位 $1$ ，则 $x,y$ 的对应位上的值都必须为 $1$ ，否则就让 $x$ 的为 $0$ ， $y$ 的为 $1$（因为$x$要尽量小）。

所以 $\min x=x\operatorname{and}y$

那么 $y=x+y-(x\operatorname{and}y)$

那什么时候无解呢？

考虑公式（2），因为 $a\operatorname{and}b$ 的值为正整数，所以如果 $A-B$ 为奇数则无解

同样，$A<B$ 时也无解

$\text{\color{Red}注意数据范围！！！！！}$

### 代码奉上

```cpp
unsigned long long a, b, d;
signed main() {
   cin >> a >> b;
   d = a - b;
   if(d < 0 || d & 1) puts("-1");
   else {
       cout << d / 2 << ' ' << a - (d / 2);
   }
   return 0;
}
```


---

## 作者：rui_er (赞：4)

本文是我的 CF 思维题集锦的第一期，[点我返回索引](https://www.luogu.com.cn/blog/ak-ioi/codeforces-0)。

原题链接：[76D Plus and xor](https://codeforces.com/problemset/problem/76/D) (dp, greedy, math, \*1700)

**题意简述**

给定两个数 $A,B$，你需要构造出两个数 $X,Y$，使得 $X+Y=A$ 且 $X\operatorname{xor}Y=B$ 的同时，$X$ 尽量小。

**解法分析**

一道很 CF 的构造题。

首先，根据异或不进位加法的性质，两个数的异或和不超过它们的和，因此当 $A\lt B$ 时无解。

同样根据不进位加法的性质，我们知道 $A$ 与 $B$ 的奇偶性必定相同，即 $A-B$ 必定为偶数，否则无解，剩余情况均有解。

我们考虑如何构造符合条件的 $X,Y$ 同时 $X$ 尽量小：

如果 $X$ 和 $Y$ 有一位二进制位同为 $1$，则加法后为 $10$，异或后为 $0$，将两者的差右移 $1$，得到 $01$。我们可以通过这种办法得到 $X,Y$ 中均为 $1$ 的位。因此 $\frac{A-B}{2}$ 的结果就是两数中均为 $1$ 的位。

同时，根据加法和异或的性质，两数同一位上的 $0$ 和 $1$ 可以互换。为了让 $X$ 尽量小，我们令 $X=\frac{A-B}{2}$ 即可，可以用 $A-X$ 求出 $Y$。

注意数据范围，需要使用 unsigned long long。

**代码**

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define loop while(true)
#define rep(x,y,z) for(ll x=y;x<=z;x++)
#define per(x,y,z) for(ll x=y;x>=z;x--)
#define fil(x,y) memset(x, y, sizeof(x))
using namespace std;
typedef unsigned long long ll;
 
ll a, b, x, y;
 
int main() {
    scanf("%llu%llu", &a, &b);
    if(a < b || (a - b) & 1) return puts("-1"), 0;
    x = (a - b) / 2; y = a - x;
    printf("%llu %llu\n", x, y);
    return 0;
}
```

---

## 作者：基地A_I (赞：4)

这题对于我来说~~有点神仙~~

------------

## 题意：

给出两整数A,B，要求找到X,Y满足以下两个个条件：

1.A=X+Y

2.B=X xor Y 其中xor表示异或运算

且要求 X 是所有满足前两个条件中最小的

如果无解，输出-1

否则，输出 X,Y

------------

## 题解

这题先从整体来看：

两个数 X，Y，如果有一位同为1（就是两个1），那么加法运算后 就是 10（当然不管前面的二进制数），xor运算后就是 0，将前者除以 2，变成01，就是两位全是 1 的这一位。其他情况 xor运算与加法运算结果相同，所以 $\frac{A-B}{2}$ 就是求出哪些位 X,Y均为 1 ，我们要让 X 值最小，就让X是公共部分，其余贡献就是 Y

------------

Code

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cmath>
#define int unsigned long long
using namespace std;
inline int read() {
	int x=0,f=1; char ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') { x=(x<<3)+(x<<1)+(ch^48); ch=getchar(); }
	return x * f;
}
int A,B,c;
signed main()
{
	A = read(), B = read();
	c = A-B;
	if(c<0 || c&1) puts("-1");
	else {
		cout<<(A-B)/2<<" "<<A-((A-B)/2)<<endl;
	}
	return 0;
}
/*
142
76

33 109
*/
```

如果不懂最好不要拿数据去模拟，否则会越来越糊涂。（~~我就是这样的~~）

---

## 作者：lanretE (赞：1)

题目主要与加、异或两种运算有关，那么我们就先把两种运算的计算方法列出来。

|  | 1,1 | 1,0 | 0,1 | 0,0 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| 加 | 0（进一位） | 1 | 1 | 0 |
| 异或 | 0 | 1 | 1 | 0 |

可以发现只有在两数当前位均为一时，加法进一位，异或不进位，其他时候两种运算计算方法是相同的。

所以，由于题目中说 $A$ 为两数和，$B$ 为两数异或的结果，那么 $(A-B)$ 就是由进位产生的。因此若 $(A-B)$ 的二进制表示中第 $k$ 位是 $1$，那就意味着原来的 $X$ 与 $Y$ 的第 $k-1$ 位均为 $1$。

对于 $X$，我们希望它最小，现在对 $X$ 的限制只有上述的两数均为 $1$ 的情况，又因为当 $B$ 的某一位为 $1$ 时，让 $X$ 此位为 $0$，$Y$ 此位为 $1$ 即可。所以 $X$ 的最小值为 $(A-B)$ 左移一位，即 $\frac{A-B}{2}$，而 $Y$ 就是 $A-X$ 了。

那么什么时候无解呢？由于输出格式中讲到 $X$ 与 $Y$ 均为正整数，所以当 $A<B$ 或 $(A-B)$ 为奇数时没有符合要求的答案，输出 $-1$ 即可。

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int main(){
	unsigned long long int a,b;//坑点
	cin>>a>>b;
	if(a>=b && (a-b)%2==0) cout<<(a-b)/2<<' '<<a-(a-b)/2;
	else cout<<-1;
}
```


---

## 作者：_edge_ (赞：1)

题解区里面好像没有 $O(\log n)$ 的构造，看来只有我这个蒟蒻才会使用 $\log$ 级别的构造了吧。

我们考虑对于一位来讲，它要么就是 `1 0` 或 `0 1` 要么 `1 1` 或 `0 0` ，这一点我们可以通过异或的值来进行判断。异或就是两个相同的为 $0$ 不同的为 $1$。

然后分情况讨论一下是否要进一，对于 `1 0` `0 1` 的决策要使得 $x$ 最小，必定 $x$ 分到的是 $0$。

最后再判断一下是否合法即可。

总时间复杂度 $O(\log n)$。

注：会爆 long long ，建议使用 unsigned long long 。

```cpp
#include <iostream>
#include <cstdio>
#define int unsigned long long
using namespace std;
const int INF=105;
int a,b,xx;
int aa[INF],bb[INF],tota,totb;
bool fl;
signed main()
{
        cin>>a>>b;
        for (int i=a; i; i>>=1ull) aa[++tota]=i%2;
        while (aa[tota]==0 && tota>1) tota--;
        for (int i=b; i; i>>=1ull) bb[++totb]=i%2;
        while (bb[totb]==0 && totb>1) totb--;
        int totmax=(tota>totb ? tota : totb);
        int l=totmax,r=totmax;
        while (l>=1 && r>=1) {
                if (aa[l]==1 && bb[r]==1) {
                        xx<<=1ull;
                        if (fl) {cout<<"-1\n"; return 0;}
                }
                if (aa[l]==0 && bb[r]==0) {
                        if (fl) xx++,xx<<=1ull,fl=false;
                        else xx<<=1ull;
                }
                if (aa[l]==1 && bb[r]==0) {
                        if (fl) xx++,xx<<=1ull;
                        else xx<<=1ull;
                        fl=true;
                }
                if (aa[l]==0 && bb[r]==1) {
                        xx<<=1ull;
                        fl=true;
                }
                l--; r--;
        } xx>>=1;
        if ((xx^(a-xx))!=b) cout<<"-1\n";
        else cout<<xx<<" "<<a-xx<<"\n";
        return 0;
}

```


---

## 作者：流绪 (赞：1)

跟楼上大佬方法一样,我这里补充一下如何特判 -1。

异或在两个数的某一位上不都等于 1 时和加法是一样，但是如果都等于 1，他相当于不进位，所以 X+Y>=X^Y，即 A>=B 才行。

若 A=B，有 (A-B)%2==0。

若 A>B，那 X,Y 在二进制下有某几位都是 1，那么考虑这几位在异或下对 B 的贡献是 0，在加法下对 A 的贡献是 2 。这样子每次有一位 X,Y 都是 1 的话，A-B 就会增大 2，有 (A-B)%2==0。

故 (A-B)%2==0 恒成立。


------------
更新！

感谢 @hdgfgs 的hack！

在按上述方法求出 x,y 后还要判断一下他们的异或值是否等于 b 防止特殊情况的出现。

------------


下面是 AC 代码。

```cpp
#include<bits/stdc++.h>
#define ll unsigned long long
using namespace std;
int main()
{
    ll a,b;
	cin >> a >> b;
	if(b > a||(a-b)%2)
	{
		cout << -1;
		return 0; 
	} 
	ll x= a-b>>1;
	ll y= a-x;
	if((x^y) !=b)
		cout << -1;
	else
		cout << x << " " << y;
}
```




---

## 作者：kirky_wang (赞：0)

# 分析

[首先了解什么是异或](https://zhidao.baidu.com/question/331324406767909525.html)

异或表示为 $xor$ 

接下来就是找规律，在二进制下模拟 $+$ 和 $xor$ 有何区别：

$+\begin{cases} 0+1=1\\1+1=10\\10+1=11\end{cases}$

$xor\begin{cases} 0xor1=1\\1xor1=0\\10xor1=11\end{cases}$

这是什么规律？我一开始有点懵，然后我找以上唯一一个结果不一样的列了一个简单的竖式:

![](https://cdn.luogu.com.cn/upload/image_hosting/40xrl4q8.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

![](https://cdn.luogu.com.cn/upload/image_hosting/kqt0c03s.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

仔细看就能发现， $xor$ 就是不进位的加法或者说只有二进制位刚好都为1是，异或值和加法值才能不一样。这个值差了 $2$ 的次方倍，其他情况下，加法和异或值都相等。我们很容易算出加法和异或结果的差，也就是 $a-b$ 

那么怎么求 $X$ 和 $Y$ 呢？我们要求最小的 $X$ ，最小的 $X$ 一定是二进制均为1的最高位。

## 什么时候无解？

1.  $a-b>0$ 或者说 $a>b$
1.  $a-b/2$ 必须为偶数，否则无解

# 你们最爱的代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a,b;
    cin>>a>>b;
    if((a-b)||a-b<0)
    	cout<<-1;//无解
    else
    	cout<<((a-b)>>1)<<" "<<(a-((a-b)>>1));
    return 0;
}
```


[结果就ac了](https://www.luogu.com.cn/record/58694237)

---

## 作者：Unordered_OIer (赞：0)

# CF76D 题解
数学题，~~我喜欢~~

## 题意
给定正整数 $a,b$，求两个正整数 $x,y$ 满足：

$$\begin{cases}x+y=a\\x \oplus y=b\end{cases}$$

- 其中 $\oplus$ 代表异或。

## 题解
我们首先来模拟一下 $33,109$ 的加法和异或的过程：

首先转为二进制：

$$33=(100001)_2$$

$$109=(1101101)_2$$

则 $33+109$ 与 $33 \oplus 109$ 的过程为：

```
      1 0 0 0 0 1
+   1 1 0 1 1 0 1
= 1 0 0 0 1 1 1 0


      1 0 0 0 0 1
^   1 1 0 1 1 0 1
=   1 0 0 1 1 0 0
```

把这两个结果比对一下：

```

  1 0 0 0 1 1 1 0
  0 1 0 0 1 1 0 0

```

我们发现**加法所得的结果只会比异或的结果多一些二进制下的** $1$！  
所以一旦发现 $a<b$ 或 $\dfrac{a-b}{2} \notin \mathbb{N^+}$ 就无解了，反之，我们把这个**差量**等分给 $x,y$ 即可。

于是答案就可以表示为：

$$\begin{cases}x=\dfrac{a-b}{2}\\y=a-\dfrac{a-b}{2}\end{cases}$$

写代码即可，复杂度为 $\mathcal O(1)$。

---

## 作者：傅思维666 (赞：0)

## 题解：

挺有含金量的？我觉得可以评绿。

但是其实推推性质也没啥。

可以看出，^就是不进位加法。

那么它和加法之间会有很多地方相像。具体地，按位来讲，如果两个都是0或者一1一0，加法和异或都是一样的。如果两个都是1的话，那么就会出现加法进位异或变0的情况。

如果这一位为第p位，那么加法就比异或多了$2^{p+1}$这么多的数。

所以要求最小的x，其实只需要满足这些都是1的位都是1，其他都是0即可。

其解即为$(A-B)/2$。

注意特判无解情况和开unsigned longlong

代码：

```cpp
#include<cstdio>
#define ull unsigned long long
using namespace std;
ull a,b;
ull ansx,ansy;
int main()
{
	scanf("%llu%llu",&a,&b);
	if(a<b)
	{
		puts("-1");
		return 0;
	}
	if((a-b)&1)
	{
		puts("-1");
		return 0;
	}
	ansx=(a-b)>>1ull;
	ansy=a-ansx;
	printf("%llu %llu\n",ansx,ansy);
	return 0;
}
```



---

## 作者：king_xbz (赞：0)

CF的思维题，本蒟蒻做了很久，题解没一个看懂的，好不容易A了，自己发一篇吧

这种题肯定要搞二进制吧。

假设我们分别模拟二进制下的加法和乘法。

$0+0=0,0xor0=0$

$0+1=1,0xor1=1$

$1+1=10,1xor1=0$

也就是说，只有二进制位刚好都为1是，异或值和加法值才能不一样。

这个值差了$2$的次方倍，其他情况下，加法和异或值都相等。

我们很容易算出加法和异或结果的差，也就是$A-B$。

也就是说，假如有$k$位二进制位均为1，那么$A-B=2^k$

这一差值是由多个相同位置二进制均为1的数对贡献的。

那么怎么求X和Y的值呢？这就是下一个问题了。

**我们不如先去考虑什么时候无解吧**

接下来考虑什么时候不成立吧。

很显然，我们的差值需要由$A-B$贡献，那$A-B$必须大于0。

由于$2^k=A-B$，所以$A-B$必须整除$2$

**回到刚才的问题**

我们可以推导一下，我们要求最小的X，最小的X一定是二进制均为1的最高位。举个例子：

$1111011xor0011011$,那么我们能取的就是二者二进制均为$1$的最高位，也就是公共位即$11011$，此时剩下的位数就可以放在Y的位置。$A-B$显然是二的倍数，表示为2进制就是$100...00$(k个0).而最高位公共$1$位只有$01,11$这样的情况才能通过异或贡献出二的倍数，此时最小的公共部分肯定是左移一位的结果，即$a-b>>1$

代码：

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
signed main()
{
    int a,b;
    cin>>a>>b;
    if((a-b)&1ull||a-b<0)
    puts("-1");
    else
    cout<<((a-b)>>1ull)<<" "<<(a-((a-b)>>1ull));
    return 0;
}
```



---

## 作者：BotDand (赞：0)

思路几位大佬讲的很清楚了，这里科普一下xor：<https://baike.baidu.com/item/%E5%BC%82%E6%88%96/10993677?fromtitle=xor&fromid=64178&fr=aladdin>

具体是怎么做的呢？

举个例子：$3$ $xor$ $5$。

* $3$转换成二进制数是$11$

* $5$转换成二进制数是$101$

| 第三位 | 第二位 | 第一位 |
| :----------: | :----------: | :----------: |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 0 |

转换成整数就是$6$。

总之$xor$只用记住一句话：相同为$0$，不同为$1$。

于是不难推出：$a$ $xor$ $b=0$ $(a=b)$

科普就到这了，望管理员求过qwq。

---

## 作者：long_long (赞：0)

楼上大佬和我的方法差不多。
# 题目大意：

给出两整数A,B，要求找到X,Y满足以下两个个条件：

1.A=X+Y

2.B=X xor Y 其中xor表示异或运算

且要求 X 是所有满足前两个条件中最小的

如果无解，输出-1

否则，输出 X,Y

# 思路：

根据他的这个xor模拟就行了。代码很短，可以自己推出。

需要满足这几个条件：

1.A=X+Y

2.B=X xor Y 其中xor表示异或运算

且要求 X 是所有满足前两个条件中最小的

程序里首先判断一下**不成立**的数。如果b>a或者(a-b)%2==1，那么直接输出-1。

否则输出(a-b/2)，和a-(a-b/2)就行了。

# 见代码：

```
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
typedef unsigned long long ll;//十年OI一场空，不开long long 见祖宗。
int main() {
    ll a,b,x,y;
    cin>>a>>b;//输入
    if(b>a||(a-b)%2==1) cout<<-1<<endl;//第一个判断
    else cout<<(a-b/2)<<" "<<a-(a-b/2)<<endl;//否则
    return 0;//华丽结束
}
```

# 提醒：

### 十年OI一场空，不开longlong见祖宗。

大佬们应该知道啥意思


---

