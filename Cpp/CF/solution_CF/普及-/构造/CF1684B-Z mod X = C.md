# Z mod X = C

## 题目描述

给定三个整数 $a,b,c$，求三个整数 $x,y,z$，满足

$$x \bmod{y} =a$$
$$y \bmod{z} =b$$
$$z \bmod{x} =c$$

对于给定数据，保证答案存在。

## 说明/提示

$1 \le t \le 10^4$

$1 \le a < b < c \le 10^8$

## 样例 #1

### 输入

```
4
1 3 4
127 234 421
2 7 8
59 94 388```

### 输出

```
12 11 4
1063 234 1484
25 23 8
2221 94 2609```

# 题解

## 作者：Withers (赞：5)

[题目传送门](https://codeforces.com/contest/1684/problem/B)
# 题目大意
给出 $a,b,c$ ($a<b<c$)要求构造一组 $x,y,z$,使得

$$x \bmod{y} =a$$
$$y \bmod{z} =b$$
$$z \bmod{x} =c$$

# 思路
这个构造有很多方法，这里我就说2种，一种是我赛时想到的，还有一种是 @lgvc 大佬想到的

第一种（我自己的） :

$x=a+b+c,y=c+b,z=c$  

~~我也不知道当时怎么想出来的~~，应该就是按照顺序加一下然后构造出来的吧

第二种（@lgvc 大佬的）

$y=b,z=c$ 这时候 $x$ 只需满足 $x>c$ 且 $x=k\times b+a$ ，求出一组解即可

# 代码

这里就只给出第一种的代码了QAQ

```cpp
#include<bits/stdc++.h>
#define Withers using
#define AK namespace
#define IOI std;
Withers AK IOI;
typedef long long ll;
typedef pair<int,int> pii;
bool k=0;
#define infll 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		long long a,b,c;
		scanf("%lld%lld%lld",&a,&b,&c);
		long long z=c,y=c+b,x=a+b+c;
		//long long y=z+b;
		printf("%lld %lld %lld\n",x,y,z);
	}
}
// POWERED BY WITHERS
// THINK ONCE, CODE TWICE
```


---

## 作者：RE_Prince (赞：4)

# CF1684B Z mod X = C 

一道大水题。~~（我才不会告诉你们我想了半个小时才想出来）~~

## Sol

我的想法是直接让 $z=c$，然后其余的 $x$ 和 $y$ 直接根据 $z$ 的大小来决定。

就以样例为例：

```
1 3 4
```

其实样例给的非常有误导性，我们先不看输出，自己算一遍。

1. 固定 $z$ 为 $4$
2. $y\mod z=3$（也就是 $b$），所以最简单的方法就是让 $y=b+z$。
3. 算出来 $y$ 之后，我们来看 $x$。 $x\mod y=1$（也就是 $a$），和上面的思路一样，让 $x=y+a$。 

但注意一个小问题，保险起见，我将数据排了个序，以防不出现 $a\leq b\leq c$ 的情况。

给出AC代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, i, j, k;
int a, b, c, x, y, z;
signed main()
{
	int T;
	cin >> T;
	while (T--)
	{
		cin >> a >> b >> c;
		if (a > b) swap(a, b);//排个序
		if (b > c) swap(b, c);
		if (a > c) swap(a, c);
		z = c;//上面的方法算xyz
		y = c + b;
		x = y + a;
		cout << x << " " << y << " " << z << endl;
	}
	return 0;
}
```



---

## 作者：0xFF (赞：3)

#### 题目大意
 

------------
给定三个整数 $a,b,c$，求三个整数 $x,y,z$，满足

$$\begin{array}{l}
x \bmod y=a \\
y \bmod z=b \\
z \bmod x=c
\end{array}$$

#### 思路分析


------------
一道有趣的思维题。

考虑构造一组满足题设的可行解 $(x,y,z)$。

观察样例可以发现给定的 $a,b,c$ 中总有一个数会出现在答案中，不妨大胆猜测 $x,y,z$ 中必然会出现 $a,b,c$ 中的一数。

假设 $z = c \Rightarrow y = b + c \Rightarrow  x = a + b + c$。

经过证明:
$$ a + b + c \equiv a (\bmod \ b+c)$$

$$ b+c \equiv b (\bmod \ c)$$

$$c \equiv c (\bmod \ a+b+c)$$

这样就构造出了一组可行解。

---

## 作者：seanlsy (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1684B)

**思路**

不妨令 $x \ge y \ge z$，$\because z \equiv c\pmod{x},\therefore z=c$。此时原方程组可转化为

$\begin{cases}x\equiv a\pmod{y}\\y\equiv b\pmod{c}\end{cases}$

显然 $y=bk+c$。

因为题目要求 $x,y,z \le 10^{18}$

所以显然它们越小越好。

所以令 $k=1$，则 $y=b+c$。

此时 $x=yn+a$，令 $n=1$，则 $x=a+b+c$。

所以只要依次输出 $x$，$y$，$z$ 即可。

**MAIN CODE**
```cpp
printf("%d %d %d\n",a+b+c,b+c,c);
```
**一些要注意的地方**

其实本文给出的答案并非唯一解，例如 $\begin{cases}x=a+4b+2c\\y=2b+c\\z=c\end{cases}$ 也是一组可行的解。

总的来说这是一道构造题，但是比较好想。

---

## 作者：ztlh (赞：3)

~~从来都没时间参加CF的我，只会在赛后补题、写题解~~

由于题目要求输出**任意一组解**，限制很宽，意味着各种~~玄学~~解法都可能AC。

假设 $a < b < c$，因为 $x$，$y$，$z$ **不可能每个数都比另外两个大**，所以**必然**有以下三种情况**至少一项**：

- $x = a$

- $y = b$

- $z = c$

如果 $x = a$，会导致 $z \bmod a = c$，但 $a < c$，不可能成立，无解。

于是我们令 $y = b$，$z = c$，此时只要 $x \bmod b = a$ 即可，即 $x = k * b + a$。

考虑 $k$ 需要满足的条件。由于 $z \bmod x = c$，必须满足 $x > c$，于是

$$k * b + a > c$$

$$k > \frac{c - a}{b}$$

正确性显然。最后别忘了将解得的 $x$，$y$，$z$ 按照 $a$，$b$，$c$ 输入的顺序排序。代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct nd{
	int v;
	int ans;
	int id;
}a[3];
bool cmp1(nd x,nd y){
	return x.v<y.v;
}
bool cmp2(nd x,nd y){
	return x.id<y.id;
}
int t;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&a[0].v,&a[1].v,&a[2].v);
		a[0].id=1; a[1].id=2,a[2].id=3;
		sort(a,a+3,cmp1);
		a[1].ans=a[1].v;
		a[2].ans=a[2].v;
		a[0].ans=a[1].v*((int)ceil((a[2].v-a[0].v)/(double)a[1].v)+1)+a[0].v;
		sort(a,a+3,cmp2);
		printf("%d %d %d\n",a[0].ans,a[1].ans,a[2].ans);
	}
	return 0;
}
```

---

## 作者：GlenBzc (赞：3)

### 题意翻译
对于1$\leq$ $a$ $<$ $b$ $<$ $c$ $\leq$ $10^{8}$ , 可以找到 $x$, $y$, $z$  ($1$ $\leq$ $x$, $y$, $z$ $\leq$ $10^{18}$) 有  
* $x$ % $y$ = $a$  

* $y$ % $z$ = $b$  

* $z$ % $x$ = $c$
### 分析  
分析样例，不妨设$z$等于$c$，则$x$ $>$ $c$，又有$y$ % $z$ = $b$，则可令$y$ $=$ $z$ $\times$ $b$ $-$ ($z$ $-$ $b$)，最后$x$ % $y$ = $a$，可推得$x$ $=$ $y$ $+$ $a$  
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define ios ios::sync_with_stdio(false), cin.tie(nullptr);
#define endl '\n';
#define int long long
signed main()
{
	ios;
	int t;cin>>t;
	while(t--)
	{
        int a,b,c;
		cin>>a>>b>>c;
		int x,y,z;
		z=c;
		y=(z*b)-(z-b);
		x=y+a;
		cout<<x<<" "<<y<<" "<<z<<endl;
	}
	return 0;
}
```

---

## 作者：RevolutionBP (赞：3)

### 题目描述：
给定三个整数 $a,b,c$，求三个整数 $x,y,z$，满足

$$x \bmod{y} =a$$

$$y \bmod{z} =b$$

$$z \bmod{x} =c$$

#### 数据范围：
$1\le a<b<c \le 10^6$ $1 \le x,y,z \le 10^{18}$


### 题解
这道题目最开始把数据范围看成 $1\le a,b,c \le 10^{18}$ 了，好半天无从下手，首先考虑到取模操作的一个性质，对于 $a<mod$ 来说，实际上 $a\%b$ 是没有作用的

这样的话我们不妨给 $x,y,z$ 排个序，先暂且让 $x<y<z$ 吧

那么容易发下 $x \bmod y =a$ 也就等价于 $x=a$,同理 $y=b$，那么只需让 $z \bmod x = c$ 即可

这里的 $x=a<c$ 由小学知识可知，余数是不能大于除数的，所以这个做法不行

但是我们可以让 $x,y,z$ 三者之间的关系转变一下，很容易想到让 $y<z<x$ 这样的话 $y=b,z=c$，然后只需让 $x\bmod y = a$ 即可，这里一看就很合理了，因为 $y=b>a$，问题转化为找到一个大于 $c$ 的模 $b$ 等于 $a$ 的数

容易构造 $x=c*b+a$ 满足上述条件，此时 $x\le 10^{18}$，至此，问题得到解决

#### code

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

long long T, a, b, c;
long long x, y, z;
signed main() {
    cin >> T;
    while (T--) {
        cin >> a >> b >> c;
        y = b, z = c;
        x = c * b + a;
        cout << x << " " << y << " " << z << endl;
    }
    return 0;
}
```

---

## 作者：ztrztr (赞：2)

## 题目大意
给出 $a,b,c$，已知：

$
x \bmod y = a
$

$
y \bmod z = b
$

$
z \bmod x = c
$

请你求出 $x,y,z$
## 思路
我们先看 $x$，因为 $x \bmod y =a$，我们知道：$(n+m) \bmod (m)=n$，其中的 $(n+m)$ 可以等于 $a + b + c = x$，$m$ 就等于 $b + c = y$。接着看 $z$，还是 $(n+m) \bmod (m)=n$，这里的 $(n+m)$ 等于 $b+c$，$m$ 等于 $c=z$。我们就得出：

$
x=a+b+c
$

$
y=b+c
$

$
z=c
$

最后，我们把每一个一等式都带进去验证一下：

$
(a+b+c) \bmod (b+c)=a
$

$
(b+c) \bmod c=b
$

$
c \bmod (a+b+c)=c
$

都是正确的。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    cin >> t;
    while (t--) {
        int a, b, c;
        cin >> a >> b >> c;
        int x = a + b + c;
        int y = b + c;
        int z = c;
        /*
        (a + b + c) % (b + c) = a;
        (b + c) % c = b;
        (c) % (a + b + c) = c;
        */
        cout << x << " " << y << " " << z << "\n";
    }
    return 0;
}
```

---

## 作者：GI录像机 (赞：1)

## 思路：

像这种找结论的题，看看数据范围往往会有意想不到的惊喜。

$a<b<c\le10^8$

令 $x=a+b+c$，因为 $b+c>a$，所以 $(a+b+c)\bmod(b+c)=a$。

既然如此，我们令 $y=b+c$，又因为 $c>b$，所以 $(b+c)\bmod c=b$。

于是我们又令 $z=c$，再计算 $z\bmod x$，因为此时 $x>z$，所以 $z\bmod x =z=c$！

现在一切都符合要求，而 $x$ 的值又远远小于上限 $10^{18}$，就可以愉快地打代码啦。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int f = 1, x = 0;
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
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 1e6 + 10;
int t = read();
signed main() {
	while (t--) {
		int a = read(), b = read(), c = read();
		write(a + b + c);
		putchar(' ');
		write(b + c);
		putchar(' ');
		write(c);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：庄nnnn额 (赞：1)

简单的数学题、思考题。

仔细想一想，就能知道 $x=a+b+c\ ,y=b+c\ ,z=c$。

证明：
$$\because b>a,c>0$$

$$\therefore b+c>a$$

$$\therefore a\equiv a\pmod{b+c}$$

$$\therefore a+b+c\equiv a\pmod{b+c}$$

$$\because c>b$$

$$\therefore b\equiv b\pmod{c}$$

$$\therefore b+c\equiv b\pmod{c}$$

$$\because a+b+c>c$$

$$\therefore c\equiv c\pmod{a+b+c}$$

$$\mathtt{QED}$$
代码就不放了，自己打吧。

---

## 作者：CodeMao (赞：0)


简单讲一下**思路**：

- 这道题仅需简单地构造一下即可。
  
- 题目要求构造 $x$，$y$，$z$ 使得 $x \mod y =a$，$y \mod z=b$，$z \mod x = c$，我们很容易想到，$y$ 就是 $x$ 除去 $a$ 以外的部分，$z$ 就是 $y$ 除去 $b$ 以外的部分，所以很容易相处一种构造方案，即：
  
  $$
  \begin{aligned}
  & x=a+b+c \\
  & y=b+c \\
  & z=c
  \end{aligned}
  $$
- 再带入题目中加以验证：
  
  $$
  \begin{aligned}
  & x \mod y = (a+b+c) \mod (b+c) = c \\
  & y \mod z = (b+c) \mod c = b \\
  & z \mod x = c \mod (a+b+c) = c
  \end{aligned}
  
  $$
- 显然符合题意。
  

代码很简短，来康康：

```cpp
#include <cstdio>
#define ll long long
int t;ll a,b,c;
int main(){
    // freopen("G:\\C\\in.in","r",stdin);
    // freopen("G:\\C\\out.out","w",stdout);
    scanf("%d",&t);
    while(t--){
        scanf("%lld%lld%lld",&a,&b,&c);
        printf("%lld %lld %lld\n",a+b+c,b+c,c);
    }
    return 0;
}
```

Do you understand?

---

## 作者：KAqwq (赞：0)

# Updata
2022.9.4：修改了一些语病。

# CF1684B

直接抛下结论，$(a+b+c) \bmod (b+c) = a$ 是合法的构造。 
# 思路

~~这道题只是看起来很离谱~~，所以我们只需要找到一个适用于任何数据的结构，如下：

$$x=a+b+c$$

$$y=b+c$$

$$z=c$$

这样就能满足题目的要求，如样例 $1$：

$$a+b+c=8$$

$$b+c=7$$

$$8 \bmod 7=1$$

$$a=1$$

很明显结论正确。
# Code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,a,b,c;
void slove(){
	scanf("%lld%lld%lld",&a,&b,&c);
	printf("%lld %lld %lld\n",a+b+c,b+c,c);
}
signed main(void){
	scanf("%lld",&T);
	while(T--) slove();
	return 0;
}

```
### ——The End

---

## 作者：封禁用户 (赞：0)

思维题。

题目中我们知道：

$$\begin{matrix}
x \mod y = a \\
y \mod z = b \\
z \mod x = c 
\end{matrix}$$

数学课上我们知道：

$$\begin{matrix}
\because y \mod  z = b \\
\therefore (y +z) \mod z = b
\end{matrix}$$

于是你需要思考一段时间去寻找 $x,y,z$ 与 $a,b,c$ 之间的关系，所以可以关掉此页面先去做题。

我直接把关系写在下面：

$$\begin{matrix}
x=a+b+c,\\
y=b+c,\\
z=c.
\end{matrix}$$

将上方关系式代入你会发现完全符合。

然后我们可以开始写代码，这里插一句嘴，我们没必要建立一个名为 $z$ 的变量，可以用 $c$ 代替~~因为我是懒癌晚期患者哦~~。

代码时刻：

```cpp
#include <bits/stdc++.h>
using namespace std;

int t;
int a, b, c;
int x, y; // 懒 癌 晚 期

int main(){
    scanf("%d", &t);
    while (t --){
        scanf("%d %d %d", &a, &b, &c);
        x = a + b + c, y = b + c; // 就是这么简单，推柿子
        printf("%d %d %d\n", x, y, c);
    }
    return 0; // owo
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 视频题解

$2$ 分 $38$ 秒开始。

![](bilibili:BV15U4y127QD)

### 2 思路

我们发现 $a<b<c$。

那么，可以证明，$x=a+b+c$，$y=b+c$，$z=c$ 必定成立。

很明显：

$$x\bmod y=(a+b+c)\bmod(b+c)=a\bmod(b+c)=a$$

$$y\bmod z=(b+c)\bmod c=b\bmod c=b$$

$$z\bmod x=c\bmod(a+b+c)=c$$

### 3 代码与记录

```cpp
#include<cstdio>
using namespace std;
int t;
long long a,b,c;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1684B_1.in","r",stdin);
	freopen("CF1684B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%lld%lld%lld",&a,&b,&c);
		printf("%lld %lld %lld\n",a+b+c,b+c,c);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/76116133)

By **dengziyue**

---

## 作者：JerryLiujiarui (赞：0)

### 题意
给定三个整数 $a$，$b$，$c$，求三个整数 $x$，$y$，$z$ 满足： 

$x$ 除以 $y$ 余 $a$，$y$ 除以 $z$ 余 $b$，$z$ 除以 $x$ 余 $c$ 。
### 方法
经过尝试，我发现 $x$ 的值就是 $a+b+c$，$y$ 的值就是 $b+c$，$z$ 的值就是 $c$。

 那么，这道题一下子就简洁了，对应输出就行了。
## AC 代码
```cpp
    #include<bits/stdc++.h>
    using namespace std;

    int main(){
        int t;
        cin>>t;
        while(t--){
            int a,b,c;
            cin>>a>>b>>c;
            cout<<a+b+c<<" "<<b+c<<" "<<c<<endl;
	}
	return 0;
    }
```


 

---

