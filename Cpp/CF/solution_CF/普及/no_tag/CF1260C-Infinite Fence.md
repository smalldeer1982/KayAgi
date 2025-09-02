# Infinite Fence

## 题目描述

- 有一个长度为 $10^{100}$ 的栏杆，编号 $1,2,\dots,10^{100}$。
- 你要将编号为 $r$ 的倍数的栏杆染成红色，$b$ 的倍数的栏杆染成蓝色。
- 编号既是 $r$ 也是 $b$ 的栏杆染成蓝色或红色皆可。
- 其它栏杆不染色
- 将所有染色的栏杆按编号从小到大排序。
- 问：是否存在一种染色方法，使得不存在连续 $k$ 个被染色的栏杆，它们染上相同的颜色

## 说明/提示

$1 \leq T \leq 1000$

$1 \leq r,g,k \leq 10^9$

友情提醒：（基本）原题识别自动机：P6476

## 样例 #1

### 输入

```
4
1 1 2
2 10 4
5 2 3
3 2 2
```

### 输出

```
OBEY
REBEL
OBEY
OBEY
```

# 题解

## 作者：yuzhechuan (赞：19)


数学结论题，现场却卡得我基本掉色

难度在于对数学式的敏感度

---

### 题解：

假设r<=b（如果不是就交换）

首先思考r，b互质的情况，发现一定会存在第pos个木板涂蓝色，而第pos+1个木板涂成红色的情况

也就是说$rx-by=1$一定有正整数解存在，这一点可以用裴蜀定理简单的证明

（在[P1082 同余方程](https://www.luogu.com.cn/problem/P1082)的题解里，你也许可以得到更好的证明）

这意味着如果要OBEY，那么区间[pos,pos+b]中的红色木板数量一定要小于k，也就是

$$(k-1)*r+1 \geq b$$

（该式的意思是pos以后的k-1块红木板要能够卡满，甚至超过这个长度为b的区间）

此时又可以发现对于r，b不互质的情况，如果我们只看那些能被gcd(r,b)整除的木板，它们的情况又是与上述情况相同的

换句话说，只要先将r，b都除去gcd(r,b)使两者互质，再套用上述判定式即可

---

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	x=0;char c=getchar();bool f=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return  x;
}
template<class t> inline void write(t x){
	if(x<0){putchar('-'),write(-x);}
	else{if(x>9)write(x/10);putchar('0'+x%10);}
}

#define int long long

int t,r,b,k;

void doit(){
	read(r);read(b);read(k);
	int gcd=__gcd(r,b);
	r/=gcd;
	b/=gcd;
	if(r>b) swap(r,b);
	if((k-1)*r+1>=b) puts("OBEY");
	else puts("REBEL");
}

signed main(){
	read(t);
	while(t--) doit();
}
```

---

## 作者：inoichi_lim (赞：2)

$10^{100}$太大了，所以我们把它当做无穷大。

开题，我想：这不就是GCD吗？

后来：`GCD?GCD!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!`

这里定义$p1=r,p2=b$。

我们这里假设$p1\le p2$（因为只要判断有没有解，$k$是针对红蓝双色的，所以交换一下没问题）。

这里考虑$\gcd(p1,p2)=1$的情况即可，因为木板无限长，所以除掉一个$\gcd$不影响$p1$和$p2$的关系。

如果无解，那么$k$段红色（其实红色蓝色都一样，凭个人喜好）的长度为$p1(k-1)+1$，这里的$p1$为一段红色的长度，$k-1$指**除了$0$**意外其他段的长度，$+1$则代表$0$（也要算进去）。

那好，为了在这一段红色中没有蓝色，我们要$p1(k-1)+1<p2$（这里只能是小于，要不然若左边的东西等于右边的，那么第$k$个块可以填蓝色，就不无聊了）。

所以，如果$p1(k-1)+1\ge p2$，那么输出`OBEY`；否则，输出`REBEL`。

代码：
```cpp
#include<bits/stdc++.h>
#define ns "-1"
#define fs(i,x,y,z) for(ll i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(ll i=x;i>=y;i+=z)
#define ll long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=100001,inf=0x3f3f3f3f;
inline ll read(){//常数优化多小才算够~
	ll date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
ll gcd(ll a,ll b){
    if(b) return gcd(b,a%b);
    return a;
}
ll t,p1,p2,k;//不开long long见________
int main(){
	t=read();
	//cout<<t;
	while(t--){
		p1=read(),p2=read(),k=read();
		ll kgcd=gcd(p1,p2);
		p1/=kgcd;
		p2/=kgcd;
		//这里把他们搞成互质 
		if(p1>p2) swap(p1,p2);
		if((k-1)*p1+1>=p2){
			puts("OBEY");//puts自带一个\n
		}else{
			puts("REBEL");
		};
	}
	return 0;
}

```

---

## 作者：xht (赞：2)

首先除以 $gcd$，不妨 $a \le b > 2$，然后可以发现由于 $a,b$ 互质，因此一定存在 $ka \equiv 1 \pmod b$ 的 $k$，即 $a$ 的逆元，因此贪心的判定即可。

```cpp
inline void solve() {
	ll a, b, k;
	rd(a), rd(b), rd(k);
	if (a > b) swap(a, b);
	ll d = __gcd(a, b);
	a /= d, b /= d;
	prints(b > 2 && (b - 2) / a + 1 >= k ? "REBEL" : "OBEY");
}

int main() {
	int T;
	rd(T);
	while (T--) solve();
	return 0;
}
```

---

## 作者：Kizuna_AI (赞：2)

我的博客：https://likecoding.tech

这道题目明显的一道数学找规律题 不用数学做法的都被hack掉了（我一个人就hack了9个人）
![hack人](https://cdn.luogu.com.cn/upload/image_hosting/oozjg5bl.png)

提供一组我hack时的数据
```
1
999999929 999999937 2
```
正确答案是$rebel$然而用暴力做法就会输出$obey$


------------

讲解一下我做这道题目的思路吧：  
首先，我们先定义$r \leq b$，若不满足条件，就进行$swap$操作。  
很明显，$r$和$b$是$10^9$的范围，那么使用暴力肯定会超时。   
也就必定存在着一种**规律**来满足条件，使其可以在O(1)会类似短时间中来获取答案  
查看到样例，样例3和样例4值得探讨一下（只需考虑到$lcm(r,b)$ 自行想想为什么）

如果为$r$的倍数用${\color{red}\text{红色}}$表示，$b$的倍数用${\color{blue}\text{蓝色}}$表示，同时为$r$和$b$的倍数用${\color{black}\text{黑色}}$表示

样例三：$\color{red}\text{2 4 }\color{blue}\text{5 }\color{red}\text{6 8 }\color{black}\text{10} $发现是满足条件的，所以是$obey$。  
样例四：$\color{red}\text{2 }\color{blue}\text{3 }\color{black}\text{6}$所以也是$obey$

于是我的第一反应就是，这不是很简单的嘛 若$b/r<k$，就是$obey$，否则就是$rebel$

准备提交时，我让自己再测试一组自编数据，查看是不是真的就是这个公式，会不会有错误。

果不其然，我找到了一组可以推翻这个公式的测试数据：
```
25 39 2
```
做出来是这样的$\color{red}\text{25 }\color{blue}\text{39 }\color{red}\text{50 75 }\color{blue}\text{78 }\color{black}\text{100}$
这组数据答案应该是$rebel$，而前面的那个公式则会输出$obey$。

![那咋整啊](https://img12.360buyimg.com/uba/jfs/t1/74767/23/16703/18544/5ddfcd62Eb8191ba9/e15f3ee8905e59cc.jpg)

我自己有找了很多规律，在这里也稍微举一些  

数据（$3,b,2$） | r和b的倍数 | 答案 |
:-: | :-: | :-: |
$\text{3 3 2}$ 即$b=4$时| $\color{black}\text{3}$ | $obey$ |
$\text{3 4 2}$ 即$b=4$时| $\color{red}\text{3 }\color{blue}\text{4 }\color{red}\text{6 }\color{blue}\text{8 }\color{red}\text{9 }\color{blue}\text{10 }\color{black}\text{12 }$ | $obey$ |
$\text{3 5 2}$ 即$b=5$时 | $\color{red}\text{3 }\color{blue}\text{5 }\color{red}\text{6 }\color{red}\text{9 }\color{blue}\text{10 }\color{red}\text{12 }\color{black}\text{15 }$ | $rebel$ |

 
 
数据（$5,b,3$） | $r$或$b$的倍数（从$r$到$lcm(r,b)$） | 答案 |
:-: | :-: | :-: |
$\text{5 9 3}$ 即$b=9$时| $\color{red}\text{5 }\color{blue}\text{9 }\color{red}\text{10 15 }\color{blue}\text{18 }\color{red}\text{20 25 }\color{blue}\text{27 }\color{red}\text{30 35 }\color{blue}\text{36 }\color{red}\text{40 }\color{black}\text{45 }$ | $obey$ |
$\text{5 10 3}$ 即$b=10$时 | $\color{red}\text{5 }\color{black}\text{10 }$ | $obey$ |
$\text{5 11 3}$ 即$b=11$时 | $\color{red}\text{5 10 }\color{blue}\text{11 }\color{red}\text{15 20 }\color{blue}\text{22 }\color{red}\text{25 30 }\color{blue}\text{33 }\color{red}\text{35 40 }\color{blue}\text{44 }\color{red}\text{45 50 }\color{black}\text{55 }$ | $obey$ |
$\text{5 12 3}$ 即$b=12$时 | $\color{red}\text{5 10 }\color{blue}\text{12 }\color{red}\text{15 20  }\color{blue}\text{24 }\color{red}\text{25 30 35 }\color{blue}\text{36 }\color{red}\text{40 45  }\color{blue}\text{48 }\color{red}\text{50 55  }\color{black}\text{60 }$ | $rebel$ |

根据以上的结论，我们就可以推出公式$b*(k-1)+1>=r$。提交一发，却WA了，为什么呢？

很容易发现$\text{2 3 2}$是$obey$ 同时$\text{20 30 2}$也是$obey$  

那我们只需加上 `b/=__gcd(b,r);r/=__gcd(b,r);` 就可以解决了。

关于证明正确性嘛，本人数学较弱，不会证明

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,tot=0;
long long r,b,k,g;
map<long long,int> m;
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%I64d%I64d%I64d",&r,&b,&k);
		if(b>r) swap(b,r); //使得始终r>=b 
		g=__gcd(b,r);
		b/=g;r/=g;
		if(b*(k-1)+1>=r) cout<<"OBEY\n";
		else cout<<"REBEL\n";
	}
	return 0;
}
```

实际上 如果不能验证公式的正确性，完全可以使用**对拍**来判断

---

## 作者：hkr04 (赞：1)

### 题意简述
有两个数$a\le b$，给出$k$，问是否存在$mb<na<(n+1)a<\cdots (n+k-1)<(m+1)b,(m+1)b\le10^{100},m,n\in N,n\ge 1$。存在输出“NO”，不存在输出“YES”（由于转换了求的东西所以存在和不存在与原题输出相反）。  

### 题解
先说一下为什么这么化简题意。原题中的$r,b$这里用$a,b$表示。不妨设$a\le b$，则染色的情况必定为$a\cdots aba\cdots aba\cdots$的情形。可以发现，相当于是$b$在截断$a$的连续染色。而为了实现原题中**不超过k个连续的愿望**，$lcm(a,b)$显然要染成$b$去防止$a$的延伸。接下来只需要看是否在$10^{100}$的范围内，每个$b$之间间隔的$a$的数量都**小于k**。   

接下来讲一下我的解题思路。一开始是想至少搞一个下界出来，即：假设每个$b$之间夹的$a$的数量最多为$c$，则$c\ge \lfloor\frac{b-1}{a}\rfloor$，也就是一开始$0\thicksim b$中存在的$a$的数量。仔细想想，由于$b-1=\lfloor\frac{b-1}{a}\rfloor\times a+r,0\le r < a$，如果想在两个$b$地倍数之间的a开头往前或结尾往后扎扎实实地再塞进一个$a$是不可能的，想要再添加只有可能是存在一个数$\lambda,mb<\lambda< mb+r$。这样好像讲的有点乱,看图明白一点：
![1.jpg](https://i.loli.net/2020/05/01/fXtCOUqdPwvsN8l.jpg)   
![2.jpg](https://i.loli.net/2020/05/01/Y3ESHv6gBlVfzjT.jpg)  

截取线段和什么类似？取模！若$\lambda$存在，则不可避免的**最多颜色连续数**为$\lfloor\frac{b-1}{a}\rfloor+1$，不然，则为$\lfloor\frac{b-1}{a}\rfloor$。即为判定$ax\equiv t(mod\ b)(0\le t<r)$是否有解。进一步的，判定$ax+by=t$是否有解。又由**裴蜀定理**知，该方程有解的充要条件为$\gcd(a, b)|t$。且$r$可以取遍$0\thicksim r-1$的整数，所以只需判断$r$和$\gcd(a, b)$的大小关系。如此一来，只需将**最多颜色连续数**和$k$进行比较，若$k$比较大则有解，否则无解。本题就得到了解决。特殊地，当$a|b$时$r=0$，此时是可以不让$b$染成$a$的，代入发现同样可以通过比较$r$与$\gcd(a,b)$的大小关系获得正确答案。  

等等，我们还有个范围问题！怎么确定如此找到的$(m+1)b$是否小于等于$10^{100}$呢？设$d=\gcd(a,b)$，由于$ax+by=t$的解集与$\frac{a}{d}x+\frac{b}{d}y=\frac{t}{d}$相同，不妨先设$a\bot b$。  
先证明一个引理：当$a\bot b$时，$\{0,a,2a,\cdots,(b-1)a\}$构成$b$的完全剩余系。  
首先，$\{0,a,2a,\cdots,(b-1)a\}$和$\{0,1,2,\cdots,b-1\}$在元素个数上相同。下用反证法证明原集合中元素对$b$取模结果两两不同即可。  
若$ax\equiv ay(mod\ b)(0\le x,y <p,x\neq y)$，且$a\bot b$，则$x\equiv y(mod\ b)$。进一步的，由于$0\le x,y <p$，则$x=y$，得出矛盾。  
证毕。  

这一步是想说明，只要有解，解的范围就在$[0,b/d-1]$中。而$mb<ax+t\le a(b-1)+a=ab,(m+1)b<ab+b\le 10^{18}+10^9<10^{100}$。  
这回是真的结束了。  

代码：
```cpp
#include <cstdio>
#include <cctype>
char ans[2][10]={"REBEL\n", "OBEY\n"};

int gcd(int a,int b) {return b?gcd(b, a%b):a;}
int read()
{
	int res=0;
	char ch=getchar();
	while(!isdigit(ch))	
		ch=getchar();
	while(isdigit(ch))
		res=res*10+ch-'0',ch=getchar();
	return res;
}
int main()
{
	int T=read();
	while(T--)
	{
		int a=read(),b=read(),k=read();
		if (a>b)
			a^=b^=a^=b;
		int d=gcd(a, b),r=b%a;
		int s=(b-1)/a+(r>d);
		printf("%s",ans[s<k]);
	}
	return 0;
}
```

---

## 作者：Rainbow_qwq (赞：1)

[CF1260C Infinite Fence](https://www.luogu.com.cn/problem/CF1260C)

# 思路

如果输入的$a>b$就交换$a,b$

如果$\gcd(a,b)==1(a\leq b)$，那肯定能找到一个点$p$，使$p\ \text{mod}\  b=0$且$(p+1)\ \text{mod}\  a=0$ (裴蜀定理)

此时是最劣情况，从$p+1$开始一直向后必须涂$a$色，直到$p+b$为止。

那此时连在一起有$\dfrac{b-2}{a}+1$个颜色都为a的块。

若$\dfrac{b-2}{a}+1<k$就可以，若$\dfrac{b-2}{a}+1\geq k$就不行，直接判断即可。

那$\gcd(a,b)>1$呢？只要把两个数都除以$\gcd(a,b)$，就互质了，可以当做$\gcd(a,b)==1$的情况。

code:
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
#define int long long//开long long
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
int gcd(int n,int m){
	if(m==0)return n;
	return gcd(m,n%m);
}
bool work()
{
	int a=read(),b=read(),k=read();
	if(a>b)swap(a,b);
	int gc=gcd(a,b);
	a/=gc,b/=gc;
	return (b-2)/a+1<k;
}
signed main()
{
	int n=read();
	while(n--)
    	if(work())puts("OBEY");
        else puts("REBEL");
    return 0;
}
```

---

## 作者：紊莫 (赞：0)

# 题意

~~看翻译。~~  

重题：[P6476 [NOI Online #2 提高组] 涂色游戏](https://www.luogu.com.cn/problem/P6476)  
~~话说 CCF 经典重题。~~  

# 分析

只需要一个循环节即可。  

其实就是看 $(x+1)b-1-(x b+1)=b-2$ 个格子中全部是 $r$ 倍数（红色）的情况行不行，当然前提是两者互质且 $b>r$。  

只需要考虑这一个循环是因为这题具有周期性（两者的最小公倍数）。  
题目中的 $10^{100}$ 纯纯唬人。

# 代码  

```cpp
int main()
{
   int T=read();
	while(T--)
	{
		int r=read(),b=read(),k=read();
		if(k==1) puts("REBEL");
		else if(r==b) puts("OBEY");//特判，相当于随便放。
		else{
			int g=__gcd(r,b);r=r/g,b/=g;//使两者互质
			if(b<r) swap(r,b);
			if((b-2)/r+1>=k) puts("REBEL");
			else puts("OBEY");
		}
		
	}
    return 0;
}
```

解释一下算出来的个数为什么加一。  

因为两者互质，所以不是整除，严格来说是 $\left \lceil \frac{b-2}{r}  \right \rceil $。

---

## 作者：SisconHL (赞：0)

P6476 题解满了就爬到这里来了（bushi）

$r=g$ 时显然只有 $k=1$ 时不可行，否则间隔染色，怎么都行。

介于若 $k=1$ 怎么都不可行，特判掉就完了。

不妨设 $r<g$

下面举个 $r=6,g=15$ 的例子，重叠部分用紫色：

![image.png](https://i.loli.net/2020/10/22/uLmeHXhd7B4vcyK.png)

首先显然可以有一个循环节，$10^{100}$ 太大了。

其次紫色部分染什么呢？显然是蓝色。因为它右边最近的显然是红色，左边同理，这样就隔开了（甚至如果 $k>1$ 都不用管这里的颜色了）

考虑把相邻两个红色之间塞尽量多的蓝色，最主要的问题就是左边红色空出多少才有一个蓝色。

考虑使 $r,g$ 互质，即都除以它们的 $\gcd$，则 $r=2,g=5$：

![image.png](https://i.loli.net/2020/10/22/oUiHIKR5uTe4nYa.png)

观察得可以做到一个都不空地衔接，下面形式化这一点：

$$\forall a,b:a\perp b,a<b,\exists x,y,s.t.:by-ax=1$$

 ~~这不就是 $B\acute ezout$ 定理么=w=~~
 
把每一个红色看成如下的形状：

![image.png](https://i.loli.net/2020/10/22/9Pwb5gCBGhxRYey.png)

用两个蓝色空出来空间除以上图的长度，向上取整。

所以就可以塞 $\lceil\dfrac{b-1}a\rceil$ 个进去，和 $k$ 比较就行了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int gcd(int a,int b){return a?gcd(b%a,a):b;}
void work(){
	int a,b,c;scanf("%d%d%d",&a,&b,&c);
	if(a>b)swap(a,b);int t=gcd(a,b);a/=t;b/=t;
	printf("%s\n",c==1?"No":(ceil((b-1)/(double)a)<c?"OBEY":"REBEL"));
}
int main(){
	int T;scanf("%d",&T);while(T--)work();
	return 0;
}
```

---

## 作者：qwq___qaq (赞：0)

首先，$k=1$ 时显然无解。

然后，使 $r\le b$（颜色不影响答案）。

我们可以知道：无论怎样染色，染色的位置都是 $\gcd(r,b)$ 的倍数。

所以，染完一个 $b$ 后，下次染 $r$ 最前方的位置最优就是 $\gcd(r,b)$。

假设无解，最优地，我们可以选择 $k-1$ 个，他们每个和第一个相差 $r$，所以总共的距离就是 $(k-1)\times r+\gcd(r,b)$。算上第一个，一共正好 $k$ 个。

而在这中间，只要任意插入一个 $b$，就满足条件，所以 $(k-1)\times r+\gcd(r,b)<b$ 时有解，反之无解。

注意乘法爆 `long long`，时间复杂度 $O(T\log(r+b))$。

这里给出关键代码：
```cpp
k==1||1ll*(k-1)*min(r,b)<max(r,b)-__gcd(r,b)?puts("REBEL"):puts("OBEY");
```

---

