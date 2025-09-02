# [ABC279D] Freefall

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc279/tasks/abc279_d

スーパーマンである高橋くんは、地上で困っている人を助けるため、あるビルの屋上から飛び降りようとしています。 高橋くんがいる星には重力の大きさを表す $ g $ という値が定まっており、 高橋くんが落下を開始してから地面に到達するまでにかかる時間は $ \frac{A}{\sqrt{g}} $ です。

現在の時刻は $ 0 $ であり、$ g\ =\ 1 $ が成り立ちます。 高橋くんは、今から次の操作を好きな回数（$ 0 $ 回でもよい）行います。

- 超能力により $ g $ の値を $ 1 $ 増やす。時間が $ B $ 経過する。
 
その後、高橋くんはビルから飛び降ります。落下を開始した後は $ g $ の値を変えることはできません。 また、操作によって経過する時間と落下にかかる時間以外は考えないものとします。

高橋くんが地面に到達できる最も早い時刻を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ A\ \leq\ 10^{18} $
- $ 1\ \leq\ B\ \leq\ 10^{18} $
- 入力は全て整数
 
### Sample Explanation 1

\- 操作を $ 0 $ 回行うとき、地面に到達する時刻は $ 1\times\ 0+\frac{10}{\sqrt{1}}\ =\ 10 $ です。 - 操作を $ 1 $ 回行うとき、地面に到達する時刻は $ 1\times\ 1+\frac{10}{\sqrt{2}}\ \fallingdotseq\ 8.07 $ です。 - 操作を $ 2 $ 回行うとき、地面に到達する時刻は $ 1\times\ 2+\frac{10}{\sqrt{3}}\ \fallingdotseq\ 7.77 $ です。 - 操作を $ 3 $ 回行うとき、地面に到達する時刻は $ 1\times\ 3+\frac{10}{\sqrt{4}}\ =\ 8 $ です。 操作を $ 4 $ 回以上行っても、地面への到達時刻は遅くなるのみです。 よって、操作を $ 2 $ 回行ってから飛び降りるのが最適で、答えは $ 2+\frac{10}{\sqrt{3}} $ です。

### Sample Explanation 2

操作を $ 1 $ 回も行わないのが最適です。

## 样例 #1

### 输入

```
10 1```

### 输出

```
7.7735026919```

## 样例 #2

### 输入

```
5 10```

### 输出

```
5.0000000000```

## 样例 #3

### 输入

```
1000000000000000000 100```

### 输出

```
8772053214538.5976562500```

# 题解

## 作者：Fido_Puppy (赞：10)

$$\texttt{Preface}$$

来一发 $\Theta(1)$ 的题解。

$$\texttt{Description}$$

[[ABC279D] Freefall](https://www.luogu.com.cn/problem/AT_abc279_d)

$$\texttt{Solution}$$

题目要求 $\min\limits_{g = 1}^{\infty} \{ b \times (g - 1) + \dfrac{a}{\sqrt g} \}$，明显 $a, b$ 一定的时候，最小的 $g$ 是固定的。

所以开始大力推式子，设：

$$f(x) = bx - b + \dfrac{a}{\sqrt x}$$

$$f(x) = ax ^ {-\frac12} + bx - b$$

求个导数，由于这个是单峰函数，所以当取到极小值时导数为 $0$：

$$f'(x) = -\frac12 ax ^ {-\frac32} + b = 0$$

$$x^{-\frac32} = \dfrac{2b}{a}$$

$$x = \left( \frac{2b}{a} \right)^{-\frac23}$$

然后这里要求 $x \in \mathbb{Z}$，所以向下取整和向上取整都算一下就可以了。

代码实现很简单，就不放了。

$$\texttt{Thanks for watching!}$$

---

## 作者：RE_Prince (赞：5)

# AT_abc279_d


[link](https://www.luogu.com.cn/problem/AT_abc279_d)


## Sol


乍一看这道题：$a,b\le10^{18}$，就出现两个想法：要不是 $\mathcal O(1)$ 出结论，要不是 $\log$ 的复杂度。


分析下样例，可以发现 $g$ 增大，答案的变化是从大到小到大。很显然是一个单谷函数，要求它的最低值。容易想到三分法。


先推荐大家去做[【模板】三分法](https://www.luogu.com.cn/problem/P3382)这道题，了解三分法之后再回来做这道。


三分，和二分有点相似，就是取出 $mid$，再比较 $mid+1,mid-1$ 的大小（通过一个题目要求的 $check$ 函数），判断取哪段比较好（看是单峰还是单谷函数）。

那我们可以写出一个返回题目要求的函数：

```cpp
inline double f(int erw)
{
	return (double)(a*erw+b*1.000/sqrtl((1+erw)*1.000));
}
```


注：$erw$ 是题目中的 $g$。


那么主函数也很好写啦，就是一个简单的二分变形：（我直接上整个代码了）

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
double b,a;
double ret=1e18;
inline double f(int erw)
{
	return (double)(a*erw+b*1.000/sqrtl((1+erw)*1.000));
}
signed main()
{
	scanf("%Lf%Lf",&b,&a);//注意输入
	int l=0,r=1e18;
	while(l<=r)//三分法
	{
		int mid=(l+r)>>1;
		if(f(mid+1)>=f(mid)) r=mid,ret=f(mid);
		if(f(mid)>=f(mid-1)) r=mid-1,ret=f(mid);//这个仿佛没啥用
		else l=mid+1;
	}
	printf("%.10Lf",ret);
	return 0;
}
```

---

## 作者：MoyunAllgorithm (赞：2)

### 或为目前题解区唯一不包含求导和三分的题解！！！

**题意**

你将要从 $A$ 米高空进行自由落体。有一个值 $G=1$ 。在自由落体前，你可以使用无限次超能力（可以不做）：花费 $B$ 时间，可以让 $G \leftarrow G+1$。

进行这些操作后，你开始了自由落体。落到地上需要 $\dfrac{A}{\sqrt{G}}$ 的时间。现在请问最小的总时间。

**分析**

想到三分！

~~但不会啊那就别做了(bushi~~

既然不会三分，就硬搞二分！

首先思考这个问题：**我如何知道进行一次超能力值不值呢？**

非常简单：在这次超能力之前，我的落地总时间是

$$t_1= \dfrac{A}{\sqrt{G}}+(G-1)B$$

当我使用了这次超能力，我的落地总时间是

$$t_2= \dfrac{A}{\sqrt{G+1}} + GB$$

也就是说，如果 $t1>t2$，使用超能力。

也就是

$$\dfrac{A}{\sqrt{G}} +(G-1)B > \dfrac{A}{\sqrt{G+1}}+GB$$

$$\dfrac{A}{\sqrt{G}} -B > \dfrac{A}{\sqrt{G+1}}$$

有一个数学上的规律：随着正整数 $x$ 的增大， $\sqrt{x+1}-\sqrt{x}$ 会越来越趋近于 $0$。我们看上面的式子：式子中，随着 $G$ 的增大，$\dfrac{A}{\sqrt{G}}-\dfrac{A}{\sqrt{G+1}}$ **单调递减**趋近于 $0$。

这就引出了我们的二分策略：二分 $G$，找到最大的满足$\dfrac{A}{\sqrt{G}} -B > \dfrac{A}{\sqrt{G+1}}$ 的 $G$。

最后提醒：**输出答案时不要忘记给 $G-1$ 乘上 $B$！！！**~~我不会告诉你因为忘记这个我浪费了三十分钟导致第五题没时间写的~~

**AC CODE**

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
long long A,B;
int Check(int x)
{
	double v=(double)sqrt(x);
	double nv=(double)sqrt(x+1);
	double lv=(double)sqrt(x-1);
	if((double)A/v-(double)B>(double)A/nv) return 1;//小了
	if((double)A/lv-(double)B>(double)A/v) return 2;//恰好是最大的合法
	return 3;//大了
}
signed main()
{
	scanf("%lld %lld",&A,&B);
	int l=1,r=A;
	int ans;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(Check(mid)==1) 
		{
			l=mid+1;
		}
		else if(Check(mid)==3) r=mid-1;
		else 
		{
			ans=mid;
			break;
		}
	}
	printf("%.10lf\n",(double)B*(double)ans-B+(double)A/sqrt(ans));//浮点数输出，不要忘记乘以B！！！！！！！！！！！！！！！！！
}
```



---

## 作者：shinzanmono (赞：1)

# Solution:
这题可以用数学方法来 AC：

我们可知用时 $T$ 与 重力加速度 $g$ 存在以下函数关系：
$$ T=f(g)=\frac{A}{\sqrt g}+B(g-1) \ \ \ g\geq1 \ \text{且} \ g \in \mathbb{N^+} $$
我们画出函数图像（[绘图软件](https://www.geogebra.org/geometry)），可以发现当 $g \geq1$ 时，必有 $T\geq0$，且当 $g\geq0$ 时呈对钩状，所以在 $[0,+\infty)$ 必有一个最小值，我们需判断最小值是否满足 $g\geq1$。且当最小值为小数时，我们需要判断与它相邻的整数中，哪一个的函数值更小。

我们把目光转移到求最小值上，我们在函数图像上可以发现，再求的最小值时，函数的斜率为 $0$。我们考虑对原函数求导，在求使导函数为 $0$ 的 $g$，即：
$$
\begin{aligned}
& f'(g)=-\frac12A\cdot g^{-\frac32}+B \\
\therefore & -\frac12A\cdot g^{-\frac32}+B=0\\
\therefore & \ g=\left(\frac{A}{2B}\right)^\frac23
\end{aligned}
$$

然后进行分类讨论：

$$
ans =
\begin{cases}
f(1) & g<1 \\
f(g) & g\in(\mathbb{N^+}\cap[1,+\infty))\\
\min(f(\lfloor g\rfloor),f(\lceil g\rceil)) & \text{otherwise}
\end{cases}
$$
即可得出答案。

# Code:
```cpp
#include<iostream>
#include<cmath>
typedef long long ll;
ll a, b;
double f(double g){
    return a / sqrt(g) + b * (g - 1);
}
int main(){
    std::cin >> a >> b;
    double g = std::pow(1. * a / b / 2, 2. / 3.);
    if (g < 1) g = 1;
    else g = f(std::floor(g)) - f(std::ceil(g)) < 0 ? std::floor(g) : std::ceil(g);
    printf("%.6lf",f(g));
    return 0;
}

```

---

## 作者：半只蒟蒻 (赞：1)

[Luogu 题目传送门](https://www.luogu.com.cn/problem/AT_abc279_d)

[Atcoder 题目传送门](https://atcoder.jp/contests/abc279/tasks/abc279_d)

### 抽象版题意

试找到一个自然数 $k$ 使得 $f(k)=k \times B+\frac{A}{\sqrt{k+1}}$ 有最小值，并求出这个最小值。

### 思路

首先证明 $f(k)=k \times B+\frac{A}{\sqrt{k+1}}$ 是一个凸函数。

因为 $g(k)=k \times B$ 是一个一次函数，显然是凸函数。

而 $h(k)=\frac{A}{\sqrt{k+1}}$ 可以看作是 $p(n)=\frac{A}{n} (n=\sqrt{k+1})$ 的形式，是一个反比例函数，也是凸函数。

根据“凸函数加凸函数等于凸函数”的定理，$f(k)=g(k)+h(k)$ 也是一个凸函数

---

那么问题变成求这个凸函数的谷。

假设我们已经算出 $k=x$ 时的 $f(x)=x \times B + \frac{A}{\sqrt{x+1}}$ ，考虑将 $k$ 增加 $1$ 得到 $f(x+1)=(x+1) \times B + \frac{A}{\sqrt{x+2}}$ ，将 $f(x+1)$ 和 $f(x)$ 做差得到 $d(x)=f(x+1)-f(x)=B-\frac{A \times (\sqrt{x+1} - \sqrt{x+2})}{\sqrt{(x+1)(x+2)}}$ ，根据凸函数的性质，第一个使 $d(x)<0$ 的 $x$ 就是原问题的答案。

---

考虑用倍增思想解决这个问题，设置一个步长 $step$ ，每次计算下一个取值 $x' \gets x+step$ ，如果 $d(x')<0$ 那么 $step \gets step/2$ ，开始下一轮迭代；否则 $x \gets x'$ ，同时 $step \gets step/2$ 

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ld eps=1e-7;
ld A,B;ll delta,i,nxt;
ld ans,cur,cur1;


int main(){
	
	cin>>A>>B;
	
	ans=A;
	
	i=0;	
	delta=(1LL<<31)*(1LL<<31);   //步长
	
	while(delta>0){
		nxt=i+delta;
		if(B*sqrt(nxt)*sqrt(nxt+1)-A*(sqrt(nxt+1)-sqrt(nxt))>eps)delta>>=1;
		else i=nxt,delta>>=1;
	}
	
	i++;
	
	ld ans1,ans2,ans3;
	
    //由于误差，最后答案可能出现在 [i-1,i+1] 这个范围内，所以需要比较一下
	if(i>0)ans1=(i-1)*B+A/sqrt(i);
	ans2=i*B+A/sqrt(i+1);
	ans3=(i+1)*B+A/sqrt(i+2);
	
	ans=min(ans1,min(min(ans2,ans3),ans));
	
	printf("%.8LF\n",ans);
	
	return 0;
}

```

求过

---

## 作者：_dijkstra_ (赞：1)

D 题，稍微有点困难。

## 思路

发现分母上有 $\sqrt{g}$。容易猜到，答案是一个单峰函数：从大变小，再从小变大。

题目就是问这个单峰函数的极值。

所以我们直接三分即可。注意精度开大一点。

## 代码

省去了缺省源。

```cpp
//ll 是 long long
//ldb 是 long double，不过开 double 应该也可以过
ll a, b;
ldb calc(ll g) {return (ldb)b * (g - 1) + (ldb)a / sqrt(g);}
ldb FIND(ll l, ll r)
{
    while (r - l > 1000) //个人喜欢的写法，可以避免答案差一点点
    {
        ll mid = (l + r) >> 1;
        if (calc(mid - 1) > calc(mid + 1)) l = mid - 1;
        else r = mid + 1;
    }
    ldb ans = 0; bool flag = true;
    for (ll g = l; g <= r; g++) //暴力检验区间内的所有数字，哪个是极值
    {
        ldb t = calc(g);
        if (t < ans || flag) ans = t, flag = false;
    }
    return ans;
}
void solve()
{
    cin >> a >> b;
    printf("%.10Lf\n", FIND(1, 1e18));
}
```

---

## 作者：yuheng_wang080904 (赞：0)

## 题意

给定两个数 $a,b(1\le a,b\le10^{18})$，求出 $min_{g=1}^{\infty}b\times (g-1)+\frac{a}{\sqrt{g}}$。精度误差不超过 $10^{-6}$。

## 思路

我们令$f(x)=b\times (x-1)+\frac{a}{\sqrt{x}}$，由题意要求 $f(x)$ 的最小值，我们便可以知道这是一个下凸函数，即为 `U` 形，那么这可以用二分来做。

我们可以二分 $g$ 的值 $mid$，可以利用做差法计算 $x=mid$ 与 $x=mid-1$ 时函数的大小关系，易得 $f(x-1)-f(x)=\frac{a}{\sqrt{x-1}}-\frac{a}{\sqrt{x}}-b$。如果该式结果大于 0，那么就说明当 $x=mid-1$ 时函数值更大，因此我们选择的是一个单调递减的区间，答案至少为此时的 $mid$，因此我们可以让 `l=mid+1`，否则就说明我们选择的是一个单调递增的区间，答案不可能大于此时的 $mid$，因此我们可以让 `r=mid-1`。

这种思路总体就是二分法，可以完美解决此题。

## 代码

注意开 `long long` !
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll a,b;
bool check(ll x){
	double p=a*1.0/sqrt(x+1)-a*1.0/sqrt(x+2)-b;
	if(p>0)return 1;
	return 0;
}
int main(){
    cin>>a>>b;
	ll l=0,r=1e18,ans=0;
	while(l<=r){
		ll mid=(l+r)/2;
		if(check(mid)){
		    ans=mid;
		    l=mid+1;
		}
		else r=mid-1;
	}
	cout<<fixed<<setprecision(10)<<min(a*1.0/sqrt(ans+2)+b*ans+b,a*1.0)<<endl;
    return 0;
}
```

## 另解

如果有一定的数学基础的话，我们可以用均值不等式解决本题，此处就简略说说。

同样令$f(x)=b\times (x-1)+\frac{a}{\sqrt{x}}=b\times x+\frac{a}{\sqrt{x}}-b$，我们发现这里 $b$ 为一常数，与 $f(x)$ 的最小值无关，因此我们可以令 $F(x)=b\times x+\frac{a}{\sqrt{x}}$，则利用均值不等式有 $F(x)=bx+\frac{a}{2\sqrt{x}}+\frac{a}{2\sqrt{x}}\ge3\sqrt[3]{bx\times\frac{a}{2\sqrt{x}}\times\frac{a}{2\sqrt{x}}}=3\sqrt[3]{a^2b}$，可知 $F(x)$ 的最小值不会小于 $3\sqrt[3]{a^2b}$，根据均值不等式的取等条件 $bx=\frac{a}{2\sqrt{x}}$，解得 $x=(\frac{a}{2b})^{\frac{2}{3}}$。我们只要在这个 $x$ 值附近进行枚举，以确保取得最小值即可，基本上时间复杂度为 $O(1)$。

代码就留给读者思考了。


---

## 作者：FReQuenter (赞：0)

## 思路

根据题意，我们设 Takahashi 动用了 $x$ 次超能力，则能得出这样一个式子：

$$f(x)=Bx+\frac{A}{\sqrt{x+1}}$$

不难发现，这个函数的曲线是单谷的，所以我们可以三分法求解。我们三分 $x$，最终答案就是 $f(x)$。为了防止一些波动，答案可以取 $\min\{f(\max\{x-1,0\}),f(x),f(x+1)\}$。注意一下精度，同时 $Bx$ 可能会爆 `long long`，可以用 `__int128` 存一下。保险起见，$f$ 函数的返回值应使用 `long double`。

三分法可以参考：[【模板】三分法](https://www.luogu.com.cn/problem/P3382)。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Fastio{
struct Reader{
    template<typename T>inline Reader&operator>>(T&x){
        char c=getchar();short f=1;
        while(c<'0'||c>'9'){if(c=='-')f*=-1;c=getchar();}
        x=0;while(c>='0'&&c<='9'){
            x=(x<<1)+(x<<3)+(c^48);
            c=getchar();
        }x*=f;return *this;
    }
}cin;
const char endl='\n';
struct Writer{
const int Setprecision=6;
typedef int mxdouble;
    template<typename T>inline Writer&operator<<(T x){
        if(x==0)return putchar('0'),*this;
        if(x<0)putchar('-'),x=-x;
        static int sta[45];int top=0;
        while(x)sta[++top]=x%10,x/=10;
        while(top)putchar(sta[top]+'0'),--top;
        return*this;
    }
}cout;
}
#define cin Fastio::cin
#define endl Fastio::endl
#define int __int128
//自己要写一下__int128的输入输出
#define double long double
int a,b,l,r,lmid,rmid,ans;
double f(int x){
	x=max(__int128(0),x);
	return b*x+a/sqrtl(x+1);
}
//f函数
signed main(){
	cin>>a>>b;
	r=1e18;//右边界
	while(l<=r){
		lmid=(2*l+r)/3;
	    rmid=(l+2*r)/3;
	    if(f(lmid)>f(rmid)) l=lmid+1,ans=lmid;
	    else r=rmid-1;
	}
	cout<<fixed<<setprecision(10)<<min(f(ans),min(f(ans-__int128(1)),f(ans+__int128(1))));//波动
}
```

---

