# Odd Grasshopper

## 题目描述

The grasshopper is located on the numeric axis at the point with coordinate $ x_0 $ .

Having nothing else to do he starts jumping between integer points on the axis. Making a jump from a point with coordinate $ x $ with a distance $ d $ to the left moves the grasshopper to a point with a coordinate $ x - d $ , while jumping to the right moves him to a point with a coordinate $ x + d $ .

The grasshopper is very fond of positive integers, so for each integer $ i $ starting with $ 1 $ the following holds: exactly $ i $ minutes after the start he makes a jump with a distance of exactly $ i $ . So, in the first minutes he jumps by $ 1 $ , then by $ 2 $ , and so on.

The direction of a jump is determined as follows: if the point where the grasshopper was before the jump has an even coordinate, the grasshopper jumps to the left, otherwise he jumps to the right.

For example, if after $ 18 $ consecutive jumps he arrives at the point with a coordinate $ 7 $ , he will jump by a distance of $ 19 $ to the right, since $ 7 $ is an odd number, and will end up at a point $ 7 + 19 = 26 $ . Since $ 26 $ is an even number, the next jump the grasshopper will make to the left by a distance of $ 20 $ , and it will move him to the point $ 26 - 20 = 6 $ .

Find exactly which point the grasshopper will be at after exactly $ n $ jumps.

## 说明/提示

The first two test cases in the example correspond to the first two jumps from the point $ x_0 = 0 $ .

Since $ 0 $ is an even number, the first jump of length $ 1 $ is made to the left, and the grasshopper ends up at the point $ 0 - 1 = -1 $ .

Then, since $ -1 $ is an odd number, a jump of length $ 2 $ is made to the right, bringing the grasshopper to the point with coordinate $ -1 + 2 = 1 $ .

## 样例 #1

### 输入

```
9
0 1
0 2
10 10
10 99
177 13
10000000000 987654321
-433494437 87178291199
1 0
-1 1```

### 输出

```
-1
1
11
110
190
9012345679
-87611785637
1
0```

# 题解

## 作者：言琢დ (赞：6)

看数据范围便知是 $O(1)$ 单次询问的找规律题。

考虑从 $x_0=0$ 开始遍历：

$$0\rightarrow -1\rightarrow 2\rightarrow 4\rightarrow 0$$

这就构成了一个循环节。

由此可以推断，假如 $x_0$ 是偶数：

$$x_0\rightarrow x_0-1\rightarrow x_0+2\rightarrow x_0+4\rightarrow x_0$$

假如 $x_0$ 是奇数：

$$x_0\rightarrow x_0+1\rightarrow x_0-2\rightarrow x_0-4\rightarrow x_0$$

无论怎样循环节都是 $4$，那么打表输出即可：

```cpp
#include<cstdio>
#define int long long
int init(){
	char c = getchar();
	int x = 0, f = 1;
	for (; c < '0' || c > '9'; c = getchar())
		if (c == '-') f = -1;
	for (; c >= '0' && c <= '9'; c = getchar())
		x = (x << 1) + (x << 3) + (c ^ 48);
	return x * f;
}
void print(int x){
	if (x < 0) x = -x, putchar('-');
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
int maps(int i, int x){
    if (i == 0) return 0;
    if (i == 1) return x;
    if (i == 2) return -1;
    return -x - 1;
}
signed main(){
    int t = init();
    while (t--) {
        int x0 = init(), n = init();
        int d = maps(n % 4, n);
        if (x0 % 2 == 0) print(x0 - d), putchar('\n');
        else print(x0 + d), putchar('\n');
    }
}
```

上面的代码中通过奇偶性分类讨论，分别给出了 $x_0\pm d$ 的答案：

其中 $d$ 代表以 $0$ 为起点时移动 $n$ 步的答案，`maps` 就是用来计算 $d$ 值的函数。

实际上整个遍历过程由于奇偶性的关系，本质上 $0$ 和其他偶数只有一开始有偏移的关系，和其他奇数也只是把所有操作的正负号倒过来而已。

---

## 作者：remmymilkyway (赞：3)

# 题目分析

## 1. 找到规律

如果 $x_0=0$ ，那么蟋蟀处在的位置分别为 $0,-1,1,4,0,-5,1,8,0,\dots$ 。

如果 $x_0=1$ ，那么蟋蟀处在的位置分别为 $1,2,0,-3,1,6,0,-7,1,\dots$ 。

如果 $x_0=2$ ，那么蟋蟀处在的位置分别为 $2,1,3,6,2,-3,3,10,2,\dots$ 。

我们发现，在执行完 $4$ 的倍数次操作时，蟋蟀会返回到 $x_0$ 。

## 2. 证明

设现在的坐标为 $x$ ，现在在执行完第 $a$ 且 $4|a$ 。

若 $x$ 为奇数，则四步之后，蟋蟀在位置在 $x+(a+1)-(a+2)-(a+3)+(a+4)$ （根据数的奇偶性就可推出），简化过后这一长串式子变为 $x$ 。

若 $x$ 为偶数，则四步时候，蟋蟀的位置在 $x-(a+1)+(a+2)+(a+3)-(a+4)$ （根据数的奇偶性又可推出），简化过后这一长串式子又变为 $x$ 。

$x$ 要么是奇数，要么是偶数，所以找到的规律成立。

## 3. 实现

只需要考虑第 $4\times\lfloor \frac{n}{4}\rfloor$ 步到第 $n$ 步就行了。贴一段C++的代码吧。（我写的，只供参考）

# 代码

```c++
#include <iostream>
using namespace std;
int t;
long long x0, n, res;
void solve() {
	cin >> x0 >> n;
	res = x0;
	for (long long i = n / 4LL * 4LL + 1; i <= n; i++) {
		if (res % 2) res += i;
		else res -= i;
	}
	cout << res << endl;
}
int main() {
	cin >> t;
	while (t--) solve();
	return 0;
}
```

---

## 作者：Bezime (赞：2)

刚看到这题我就手推了一下。

于是，没了。

假设起始于奇数（红色），对应位置的数字 $i$ 表示在此位置走第 $i$ 步。

![1](https://cdn.luogu.com.cn/upload/image_hosting/adab1kwz.png)

我们发现每走 $4$ 步会回到初始点。

假设起始于偶数（蓝色）。

![2](https://cdn.luogu.com.cn/upload/image_hosting/t6jajy47.png)

同样每走 $4$ 步会回到初始点。

于是，我们就可以暴力求最后 $n$ $\bmod$ $4$ 步，并求得结果。

AC代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxn 10002
using namespace std;
ll T,x,n,m;
inline void rd(ll &x){x=0;short f=1;char c=getchar();while((c<'0'||c>'9')&&c!='-') c=getchar();if(c=='-') f=-1,c=getchar();while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();x*=f;}
inline void pt(ll x){if(x<0) putchar('-'),x=-x;if(x>9) pt(x/10);putchar(x%10+'0');}
//快读快写
int main(){
	rd(T);
	while(T--){
		rd(x),rd(n);
		m=n%4;
		for(ll i=n-m+1;i<=n;i++)
			x=x&1?x+i:x-i;
		pt(x),puts("");
	}
}
```



---

## 作者：QZY2008 (赞：0)

考场上规律的一题了。

首先注意到每4次跳跃就会回到原点

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/89uggj4t.png)

所以跳跃次数除4（下取整）再乘4，剩下只需跳跃至多4次，模拟即可。

下附代码:

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1e5+1;
ll num[N];
ll t;
ll n,m;
inline ll read(){
	ll x=0,f=1;
	char ch=getchar();
	for (;!isdigit(ch);ch=getchar())
		if (ch=='-')f=-1;
	for (;isdigit(ch);ch=getchar())
		x=(x<<1)+(x<<3)+(ch^48);
	return x*f;
}
inline void init(){
	n=read(),m=read();
}
inline void work(){
    ll x=m/4*4;//处理回原点情况
    while (x<m){
      	if (n%2==0)
        	n-=x+1; 
	  	else
        	n+=x+1;
      	x++;
    }//直接模拟
    printf("%lld\n",n);
}
int main(){
	t=read();
	while (t--){
		init();
		work();
	}
}
```

---

## 作者：Kris_hukr (赞：0)

### 分析

我们不妨假设某一次移动的距离为 $k$。

将移动的距离表示出来：
$$
(k + 0) - (k + 1) - (k + 2) + (k + 3) = 0
$$
容易发现无论 $x$ 的奇偶性都存在这一特点。因此我们只需要模拟 $0\dots3$ 的情况即可。

最后记得开 long long。

### 代码

```cpp
#include <cstdio>
#include <iostream>

typedef long long ll;

template <typename T>
T read();

int main() {
    int T = read<int>();
    while (T--) {
        ll x = read<ll>(), n = read<ll>();
        for (ll i = n - (n % 4) + 1; i <= n; i++) {
            if (x & 1) {
                x += i;
            } else {
                x -= i;
            }
        }
        std::cout << x << '\n';
    }
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}
```

---

## 作者：hyman00 (赞：0)

## 001 题意

一条无限长的数轴上有一个点，一开始在 $x_0$ 处，它会移动 $n$ 次，第 $i$ 次它会按照以下规则移动：

* 如果它当前所处的位置上的数 $x$ 是奇数，则它会移动到 $x+i$ 。
* 否则它会移动到 $x-i$ 。
求移动 $n$ 次后该点所处的位置上的数。

## 002 数据范围
$$
|x_0|\le 10^{14},n\le10^{14}
$$

## 003 题解

看到 $10^{14}$，一定是找规律:

### $x_0$ 是偶数

|n|x|
|:-:|:-:|
|0|0|
|1|-1(-1)|
|2|1(+2)|
|3|4(+3)|
|4|0(+4)|

### $x_0$ 是奇数

|n|x|
|:-:|:-:|
|0|1|
|1|2(+1)|
|2|0(-2)|
|3|-3(-3)|
|4|1(+4)|

发现每操作 $4$ 次就会回到原来的位置！
$$
x+a-(a+1)-(a+2)+(a+3)=x
$$
$$
x-a+(a+1)+(a+2)-(a+3)=x
$$

这下就可以直接模拟 $n\%4$ 次就可以了。

## 004 代码

头文件略

```c++
void run(){
	int n,m;
	cin>>n>>m;
	rept(i,m/4*4+1,m+1){//从m-m%4+1到m模拟
		if(abs(n)%2==0)n-=i;
		else n+=i;
	}
	cout<<n<<"\n";
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int tc=1;
	cin>>tc;
	while(tc--)
		run();
	return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/61625847)

---

## 作者：ttq012 (赞：0)

**题解**

由于 $n$ 的范围很大，暴力枚举肯定不可行。所以这一道题一定是一道思维题。

我们现在定义初始位置为 $5$。

第 $1$ 次移动：$6$。

第 $2$ 次移动：$4$。

第 $3$ 次移动：$1$。

第 $4$ 次移动：$5$。

第 $5$ 次移动：$10$。

第 $6$ 次移动：$4$。

第 $7$ 次移动：$-3$。

第 $8$ 次移动：$5$。

第 $9$ 次移动：$14$。

第 $10$ 次移动：$4$。

第 $11$ 次移动：$-7$。

第 $12$ 次移动：$5$。

以此类推。

我们可以发现：每移动 $4$ 次，就会回到初始的原点。

那么我们只用枚举当前循环的 $4$ 次，就可以求出答案了。


```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int T;
    cin >> T;
    while (T --)
    {
        long long x0, n;
        scanf ("%lld%lld", &x0, &n);
        long long a = n / 4 * 4; // 求出现在已经移动过的次数，由于C++是向下取整的，所以我们可以使用这一种方式来求值。
        long long now = x0; // 当前的位置
        a ++; // 移动了一步
        while (a <= n) // 时间复杂度 O(1)
        {
            long long dist = a; // 向右移动 dist 步
            // 其中向右移动 -1 步就代表向左移动 1 步，向右移动 -2 步就代表向左移动 2 步
            if ((now & 1LL) == 0)
                dist = -dist;
            now += dist;
            a ++;
        }
        printf ("%lld\n", now);
    }
    return 0;
}

```


---

## 作者：一只大龙猫 (赞：0)

这是一篇 **Python** 题解。

我们可以先打一下从走第 $1$ 步到第 $16$ 步后，蟋蟀所在的位置相对于起点的偏移量的表，寻找规律：

[打表程序与数据](https://www.luogu.com.cn/paste/38x0shw6)

此时不难发现，无论起点的位置是奇数还是偶数，偏移量都是以 $4$ 个数为一个周期的。

设 $f_1(x)$ 为当起点为奇数时，蟋蟀走完第 $x$ 步后所在的位置相对于起点的偏移量，$f_0(x)$ 为当起点为奇数时，蟋蟀走完第 $x$ 步后所在的位置相对于起点的偏移量，则根据上面的数据，不难发现以下规律：

$$
    f_1(x)= \left\{
        \begin{array}{ll}
            0 & x \bmod 4 = 0\\
            x & x \bmod 4 = 1\\
            -1 & x \bmod 4 = 2\\
            -x-1 & x \bmod 4 = 3
        \end{array}
    \right.
$$

$$f_0(x)=-f_1(x)$$

了解规律之后，写出代码就不难了：

```python
def f1(x):
    if x%4==0:
        return 0
    elif x%4==1:
        return x
    elif x%4==2:
        return -1
    else:
        return -x-1
n=int(input())
for i in range(n):
    a,b=map(int,input().split()) #输入a和b
    if a%2==1: #见下文
        pyl=f1(b)
    else:
        pyl=-f1(b)
    print(a+pyl)
```

注：

由于数据较大，C 与 C++ 选手应注意变量类型应使用`long long`。Python 选手则无需为此担心（因为 Python 自带高精度）。

在 Python 中，负奇数对 $2$ 取模仍为 $1$，但是在 C/C++ 中，负奇数对 $2$ 取余得到的是 $-1$，需要注意。（具体原因可以看[这个](https://www.luogu.com.cn/discuss/376304?page=1)贴）

---

## 作者：Madefaker (赞：0)

##### B. Odd Grasshopper

题目大意：

对于多组测试数据 $(1 \leq t \leq 10^4)$ 有一只草蜢在数轴上运动。给出一个草蜢的起始点（一定是整数） $x_0(-10^{14} \leq x_0 \leq 10^{14})$ 和运动次数 $n(0 \leq n \leq 10^{14})$，求草蜢停留的位置。草蜢的运动方式如下：（当前运动次数是 $i(1 \leq i \leq n)$）

1. 如果草蜢所在位置是偶数，那么向左移动 $i$ 格。
2. 如果草蜢所在位置是奇数，那么向右移动 $i$ 格。

------

思路：

考虑分别模拟一开始是奇数和偶数两种情况。（同种情况内，由于草蜢的运动方式只和奇偶性相关，与大小无关，因此是类似的）这里为了方便取 $x_0=0$ 和 $1$。

$x_0=0$ 时，它的位置是偶数，向左移动 $1$ 格到 $-1$；$-1$ 是奇数，向右移动 $2$ 格到 $1$；$1$ 是奇数，向右移动三格到 $4$。接下来 $n=4 \sim 8$ 的情况下草蜢分别在 $0,-5,1,8,0$。

$x_0=1$ 时，$n=1\sim 8$ 的情况下草蜢分别在 $2, 0, -3, 1, 6, 0, -7, 1$。

可以看出，草蜢的位置变化规律以 $4$ 为周期，公式为：

$x_0$ 是偶数时：
$$
x_n=
\left\{
\begin{aligned}
x_0 && (n \% 4 == 0) \\
x_0-i && (n \% 4 == 1) \\
x_0+1 && (n \% 4 == 2) \\
x_0+i+1 && (n \% 4 == 3)
\end{aligned}
\right.
$$
$x_0$ 是奇数时：
$$
x_n=
\left\{
\begin{aligned}
x_0 && (n \% 4 == 0) \\
x_0+i && (n \% 4 == 1) \\
x_0-1 && (n \% 4 == 2) \\
x_0-i-1 && (n \% 4 == 3)
\end{aligned}
\right.
$$

------

实现：

直接套公式即可。不要忘记开 long long。

时间复杂度 $O(1)$。

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(NULL);
	cout.tie(NULL);
	int t;
	cin >>t;
	while(t--) {
		ll x0, x1, n;
		cin >> x0 >> n;
		if(x0 < 0) x1 = -x0;
		else x1 = x0;
		if(x1 % 2ll == 1ll) {
			if(n % 4ll == 0ll) cout << x0;
			else if(n % 4ll == 1ll) cout << x0 + n;
			else if(n % 4ll == 2ll) cout << x0 - 1ll;
			else cout <<x0 - n - 1ll;
		}
		else {
			if(n % 4ll == 0ll) cout << x0;
			else if(n % 4ll == 1ll) cout << x0 - n;
			else if(n % 4ll == 2ll) cout << x0 + 1ll;
			else cout <<x0 + n + 1;			
		}
		cout << endl;		
	}
	return 0;
}

```



---

## 作者：引领天下 (赞：0)

简单结论题。

$n\le10^{14}$ 的范围明摆着告诉大家要找规律了，那我们就来手搓几个小一点的 $n$ 试一下：

| 执行完第 $n$ 次操作后的 $x$ | $n$ |
| :----------: | :----------: |
| 0 | 0 |
| -1 | 1 |
| 1 | 2 |
| 4 | 3 |
| 0 | 4 |

我们换 $x_0=1$，仍然会发现 $4$ 次操作后回到了 $1$。

那么规律就很明显了，每$4$次操作回到 $x_0$。

于是我们将 $n\%4$ 后直接模拟即可。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,x,n;
signed main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        cin>>x>>n;
        int m=n-n%4+1;//注意：最后剩下来的若干次操作，以n-n%4+1为开始。
        while(m<=n){
            if(x&1)x+=m;
            else x-=m;
            m++;//直接模拟
        }
        cout<<x<<endl;
    }
    return 0;
}
```

---

