# Reflection

## 题目描述

For each positive integer $ n $ consider the integer $ ψ(n) $ which is obtained from $ n $ by replacing every digit $ a $ in the decimal notation of $ n $ with the digit $ (9-a) $ . We say that $ ψ(n) $ is the reflection of $ n $ . For example, reflection of $ 192 $ equals $ 807 $ . Note that leading zeros (if any) should be omitted. So reflection of $ 9 $ equals $ 0 $ , reflection of $ 91 $ equals $ 8 $ .

Let us call the weight of the number the product of the number and its reflection. Thus, the weight of the number $ 10 $ is equal to $ 10·89=890 $ .

Your task is to find the maximum weight of the numbers in the given range $ [l,r] $ (boundaries are included).

## 说明/提示

In the third sample weight of $ 8 $ equals $ 8·1=8 $ , weight of $ 9 $ equals $ 9·0=0 $ , weight of $ 10 $ equals $ 890 $ .

Thus, maximum value of the product is equal to $ 890 $ .

## 样例 #1

### 输入

```
3 7
```

### 输出

```
20```

## 样例 #2

### 输入

```
1 1
```

### 输出

```
8```

## 样例 #3

### 输入

```
8 10
```

### 输出

```
890```

# 题解

## 作者：luojien (赞：11)

## 题目分析
通过观察，我们发现，取正整数 $x$ 权值的通项是 $[(10^{\lceil\log_{10}{x}\rceil} - 1) - x]x$。

首先想到的是暴力枚举，但是—— 数据范围：$1 \leq n \leq 10^9$，所以本题采用 $O(n^2)$ 的算法是肯定 TLE 的。

考虑观察函数图像（图中为 $1 \leq r \leq 9$ 的情况）：
![](https://cdn.luogu.com.cn/upload/image_hosting/srisyk80.png)

显而易见的，抛物线顶点时的权值最大。根据 $l, r$ 取值，最大权值有以下三种可能：

设 $n = 10^{\lceil\log_{10}{r}\rceil} - 1$

若 $l \in [1, \lfloor\frac{n}{2}\rfloor]$ 且 $r \in [\lfloor\frac{n}{2}\rfloor, n]$：则 $\max {x}=\lfloor\frac{n}{2}\rfloor\times\lceil\frac{n}{2}\rceil$。

若 $l, r \in [1, \lfloor\frac{n}{2}\rfloor)$：则 $\max {x}=(n - r) \times r$。

若 $l, r \in (\lfloor\frac{n}{2}\rfloor, n]$：则 $\max {x}=(n - l) \times l$。

## 代码


```cpp
#include <iostream>
#include <cmath>
#define int long long
using namespace std;
signed main()
{
	int l, r;
	cin >> l >> r;
	int n9 = pow(10, ceil(log10(r + 1))) - 1;
	//cout << n9 << endl;
	if (l <= n9 / 2 && r >= n9 / 2)
	{
		cout << (n9 / 2) * (n9 / 2 + 1) << endl;
	}
	else if (r < n9 / 2)
	{
		cout << (n9 - r) * r << endl;
	}
	else
	{
		cout << (n9 - l) * l << endl;
	}
	return 0; 
}
```
## 注意事项

- 本题数据范围较大（$10^9$），在相乘时会爆 int 所以需要开 long long。

---

## 作者：DiDi123 (赞：6)

# 一、大意
请你求出 $x\in [l,r]$ 中 $f(x)$ 最大是多少。若 $x$ 有 $n$ 位，$f(x)=x\cdot(9\dots9-x) $ （$n$ 个 $9$）。

# 二、分析
首先要解决的就是位数的问题，用几何画板绘图可得下图：
![图片](https://cdn.luogu.com.cn/upload/image_hosting/zziixvoq.png)

我们可以发现其实 $x\cdot(9-x)$ 和 $x\cdot(99-x)$ 还是差别很大的，所以当 $99\geq x>9$ 时 $f(x)$ 肯定比 $x\leq 9$ 时任意一个值都大。

所以我们就得到了一个结论，即所选用的 $9$ 的个数就应该是 $r$ 的位数，因为这样才可以最大。

我么以 $r$ 是两位数为例，现在当 $99\geq x>9$ 时 $f(x)=(99-x)\cdot x$，这是一个二次函数，对称轴为 $x=\frac{99}{2}$，我们可以分三种情况讨论：$l>\frac{99}{2},r<\frac{99}{2}$ 以及 $l<\frac{99}{2}<r$。前两种情况很显然 $f(x)$ 最大值分别是 $f(l)$ 和 $f(r)$ ，最后一种情况就是需要对 $\frac{99}{2}$ 取个整然后再代入 $f(x)$ 就好了。

# 三、代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long l,r,rr,t,xx;
double x;
int main()
{
	cin>>l>>r;
	rr=r;
	while(rr)
		rr/=10,t=t*10+9;
	x=t*0.5,xx=x;
	if(l>x) cout<<t*l-l*l;
	else if(x>r) cout<<t*r-r*r;
	else cout<<t*xx-xx*xx;
}
```


---

## 作者：naroto2022 (赞：4)

# CF86A 题解

### 题意

求 $ \max\limits_{x=l}^{r} f(x),f(x)=(\underbrace{99\cdots9}_ {\log_{10}x+1\text{个}9}-x)\times x
$。

### 思路

看了看题目，用我们聪明的大脑一想，$f(x)=(10^{\log_{10}x+1}-1-x)\times x=-x^2-x+x\times10^{\log_{10}x+1}$，仔细一想这不就是一个开口向下的二次函数吗？于是，题目就是二次函数最值问题。

设 $cnt=10^{\log_{10}x+1}-1$

所以，函数对称轴就为 $\frac{cnt}{2}$。

因为函数开口向下，所以：
- 当 $x\in(-\infty,\frac{cnt}{2}]$，函数单调递增。
- 当 $x\in[\frac{cnt}{2},+\infty)$，函数单调递减。
- 当 $x=\frac{cnt}{2}$ 时，函数有最大值。

于是，求函数图像就可以分为以下三种情况：

1. 当 $l\leqslant r<\frac{cnt}{2}$，则对于任意 $x$，有 $f(x)$ 单调递增，所以有当 $x=r$ 时，有函数最大值 $f(r)$。
2. 当 $\frac{cnt}{2}<l\leqslant r$，则对于任意 $x$，有 $f(x)$ 单调递减，所以有当 $x=l$ 时，有函数最大值 $f(l)$。
3. 当 $l\leqslant\frac{cnt}{2}\leqslant r$，则当 $x=\frac{cnt}{2}$ 时，函数有最大值。

于是，这题就做出来了。

### 总结

1. 二次函数最值问题。
2. 单调性。
3. 分类讨论。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
long long l,r,wr,cnt;
int main(){
    scanf("%lld %lld",&l,&r);
    wr=log10(r);
    cnt=pow(10,wr+1)-1; 
    if(l>=cnt/2) printf("%lld",l*(cnt-l));//f(l)处值最大 
    else if(r<cnt/2) printf("%lld",r*(cnt-r));//f(r)处值最大 
    else printf("%lld",cnt/2*(cnt-cnt/2));//对称轴处f(x)最大，输出对称轴f(x)的值 
    return 0;
}
```


---

## 作者：qczrz6v4nhp6u (赞：3)

~~看见水题来水一发，没想到顺手打了个最优解~~
## 题意
求 $\max\limits_{x=l}^{r}f(x)$ ，其中 $f(x)=(c-x)\times x$，$c$ 表示 $9999...$ （ $9$ 的个数与 $x$ 的位数相同）
## 思路
设 $s(x)=\lfloor\log_{10}x\rfloor+1$ （即 $x$ 的位数）

首先考虑  $s(l)=s(r)$ 的情况。  
根据~~小学奥数~~可以发现 $f(x)$ 在 $x=\dfrac{c}{2}$ 时最大，且向两边单调递减  
那么我们计算 $[l,r]$ 中最靠近 $\dfrac{c}{2}$ 的数即可。具体地：

若 $l>\dfrac{c}{2}$ ，则输出 $f(l)$

若 $r<\dfrac{c}{2}$ ，则输出 $f(r)$

其他情况（也就是 $l\le\dfrac{c}{2}\le r$ ），输出 $f(\big\lfloor\dfrac{c}{2}\big\rfloor)$ 即可

对于 $s(l)<s(r)$ 的情况，可以发现 $s(x)$ 越大， $f(x)$ 越大  
于是乎，我们便可以只考虑 $[10^{s(x)-1},r]$ 的情况  
按照 $s(l)=s(r)$ 的情况考虑即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll l,r;
int main(){
    scanf("%I64d%I64d",&l,&r);
    ll lg1=log10(l),lg2=log10(r);
    ll pw=pow(10,lg2+1)-1ll;
    if(l>=pw/2)
        printf("%I64d",l*(pw-l));
    else if(r<pw/2)
        printf("%I64d",r*(pw-r));
    else
        printf("%I64d",pw/2*(pw-pw/2));
}
```


---

## 作者：OIerJiang_1017 (赞：2)

## [CF86A 题目传送门](https://www.luogu.com.cn/problem/CF86A)

### 题目大意

把十进制表示下的正整数 $n$ 的每一位数字 $a$ 替换 $9−a$ 得到的整数 $N$ 称为反转数，需要去掉前导零。例如，$192$ 的反转数是 $807$，$9$ 的反转数是 $0$，$91$ 的反转数是 $8$。将一个整数 $k$ 的权重定义为该整数与其反转数的乘积。因此，$10$ 的权重等于 $10\times89=890$。你的任务是找出区间 $l-r$ 内权重最大的整数。

### 解决方法

分类讨论：设 $z = 10^{\lceil\log_{10}{r}\rceil} - 1$。
- 如果区间 $[1, \lfloor\frac{z}{2}\rfloor]$ 包含 $l$ 且区间 $[\lfloor\frac{z}{2}\rfloor, z]$ 包含 $r$：则 $\max {a} = \lfloor\frac{z}{2}\rfloor\times\lfloor\frac{z}{2}\rfloor$。
- 如果区间 $[1,\lfloor\frac{z}{2}\rfloor)$ 包含 $l,r$：则 $\max{a} = (z - r) \times r$。
- 如果区间 $(\lfloor\frac{z}{2}\rfloor, z]$ 包含 $l,r$：则 $\max{a} = (z - l) \times l$。

注：$\log_{10}r$ 表示以 $10$ 为底的对数，如：$\log_{10}{100} = 2$，因为 $10^2 = 100$。

### 注意事项

$1 \leq l,r \leq 10^9$，需要开 `long long`。

### 代码展示

```cpp
#include <bits/stdc++.h>//万能头
#define ll long long
//十年OI一场空，不开long long见祖宗
using namespace std;

int main()
{
	ll l, r;//建议scanf,更快
	scanf("%lld%lld", &l, &r);
	ll x = pow(10, ceil(log10(r + 1))) - 1;
	//log10(x)表示10为底的对数
	//如：log10(100)=2,因为10^2=100
	if(l <= x / 2 && r >= x / 2) printf("%lld\n", (x / 2) * (x / 2 + 1)); //分类讨论
	else if (r < x / 2) printf("%lld\n", (x - r) * r);
	else printf("%lld\n", (x - l) * l);//建议printf,更快
	return 0; 
}
```

---

## 作者：Transparent (赞：1)

### 分析
- 若一个数 $x$ 有 $k$ 位，
那么进行一次求 Reflecion number 的操作，
就相当于用 $999…999$ （ $k-1$ 个 $9$ ）减去 $x$ 。

- 这样的话，对于相同位数的两数，
因为 这两数与它们的Reflecion number的和不变，
所以两数的乘积那个大，
就取决于这两个数与它们的Reflecion number的差的大小，
差越小，乘积越大。

- 因此 $n$ 位数中，
Weight 最大的数就是 $\lfloor$ $999…999$ （ $n$ 个 $9$ ）$\div$ $2 \rfloor$ 和 ($\lfloor$$999…999$ （ $n$ 个 $9$ ）$\div 2 \rfloor +1$)。

- 若这个数不在范围中，
则范围中最接近这个数的数 Weight 最大。

- 若左端点和右端点的位数不同，
那一定取位数更大的。

------------

### 代码：
**（C++17）**
```cpp
#include<bits/stdc++.h>
using namespace std;
long long l,r,ans,maxl,maxr,midl,midr;
int ll,rl;
int main()
{
	scanf("%I64d%I64d",&l,&r);//输入输出不能用 %lld （题面有说明） 
	long long L=l,R=r;
	while(L>0)//处理左端点位数 
	{
		L/=10;
		ll++;
	}
	while(R>0)//处理右端点位数 
	{
		R/=10;
		rl++;
	}
	maxl=pow(10,ll)-1;//与左端点位数相同的最大数 
	maxr=pow(10,rl)-1;//与友端点位数相同的最大数
	midl=maxl/2;//与左端点位数相同的Weight值最大数 
	midr=maxr/2;//与右端点位数相同的Weight值最大数 
	if(ll<rl)//左端点位数小于右端点位数 
	{
		if(r>=midr)//可以达到最大值 
		{
			printf("%I64d\n",midr*(midr+1));
			return 0;
		}
		else//不能达到就去最接近的值 
		{
			printf("%I64d\n",r*(maxr-r));
			return 0;
		}
	}
	else//只可能是l,r位数相同，因为l<=r 
	{
		if(r>=midr&&l<=midl)//可以达到最大值 
		{
			printf("%I64d\n",midr*(midr+1));
			return 0;
		}
		if(r>midr&&l>midl)//比Weight最大的数的值更大，就尽量接近 
		{
			printf("%I64d\n",l*(maxl-l));
			return 0;
		}
		if(r<=midr)//比Weight最大的数的值更小，也尽量接近
		{
			printf("%I64d\n",r*(maxr-r));
			return 0;
		}
	}
	return 0;
}
```
注：代码玄学问题，自动识别语言会WA

---

## 作者：qusia_MC (赞：0)

二次函数求最值。

## 题意

以下令 $k=99999...$（一共 $\lceil \log_{10} r\rceil$ 个 $9$）。

答案等于 $\max\limits_{i=l}^r (k-i)i$。

## 思路

一眼盯真肯定求最值。

首先你们要明白一个定理：

当 $a+b$ 的值不变的情况下，$a,b$ 越接近，则乘积越大。

不难证明。设和为 $k$，令 $l=k\div 2$，则 $a=l-x,b=l+x,ab=(l-x)(l+x)=l^2-x^2$。不难发现，当 $x=0$ 也就是 $a,b=l$ 时乘积最大。

那么这个题迎刃而解：

令两个数分别为 $x,(k-x)$，此时和是确定的，那么只需要让这两个数尽量接近（也就是 $k$ 两边平分）。注意到题说是整数那么就向下取整即可。

那么我们令 $k\div 2=s$。

- 若 $s<l$ 则答案就是当 $x=l$ 时的答案。（越小越好）

- 若 $s>r$ 则答案就是 $x=r$ 时的答案（越大越好）

- 否则答案就是当 $x=s$ 时的答案。

## 代码

```
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int l, r, k = 0, s;
    cin >> l >> r;
    int r2 = r;
    while (r2)
    {
        r2 /= 10;
        k = k * 10 + 9;//求k
    }
    s = k / 2;
    if (s < l) cout << (k - l) * l;
    else if (s > r) cout << (k - r) * r;
    else cout << (k - s) * s;//分情况讨论
    return 0;
}
```

因为 CF 不能用所以无法测试，但是样例是都过的。

---

## 作者：卷王 (赞：0)

这是一道数学题。

数学题就要找规律，那么怎么找呢？

可以使用程序进行暴力打表，比如我们输出 $10$ 到 $99$ 的结果，可以发现，在 $49,50$ 的时候，答案最大。直观上也是很好理解，我们要让 $x \times (99-x)$ 尽可能大，显然要让 $x$ 和 $99-x$ 离的越近越好。

**更严谨的想法**：

这里借用一下 @DiDi123 的图。

![](https://cdn.luogu.com.cn/upload/image_hosting/zziixvoq.png)


于是我们可以拿一个例子举例。

如图所示的抛物线 $y=x \times (99-x)(10\leq x\leq 99)$，观察图像，我们肯定要取对称轴与函数交点的位置（即抛物线的最高点），就是左边红点和右边红点的中间位置。


------------

那么我们只需要求出那个中间值即可，$mid$ 为 $(10^{ cntr} - 1) \div 2$，$cntr$ 为 $r$ 的位数。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int l, r, cntl, cntr;
signed main() {
	cin >> l >> r;
	int t = r;
	while(t > 0) cntr++, t /= 10;
	int tmp = (int)pow(10, cntr) - 1;
	int mid = tmp / 2;
	if(l > mid) cout << (tmp - l) * l;
	else if(r < mid) cout << (tmp - r) * r;
	else cout << (tmp - mid) * mid;
	return 0;
}
```
* 感谢 @DiDi123 提供的图片。

---

## 作者：Ryan_Adam (赞：0)

# CF86A Reflection 题解
## 题目描述

题面翻译说的很清楚了。

## 分析
思维题。

首先观察，一个 $n$ 位数 $x$ 和它的 `Reflecion number` 的和为 $n$ 个 $9$，这是显然的。所以在同位数内，和是一定的。小学奥数告诉我们，“和一定，差小积大”，所以说理想状态下 `Weight` 的最大值就是 $\dfrac{99...9}{2}$，也就是 $5 \times 10^{n-1}$。

但考虑一组数据可能不会包含 $5 \times 10^{n-1}$，比如说 $l = 11,r = 34$ 时，并不包含 $50$。这时候最大值就是最接近 $5 \times 10^{n-1}$ 的数，显然肯定是 $l$ 或 $r$,所以实际做的时候取三种情况的 $\max$ 即可。

最后，记得开 long long。

## 示例代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
namespace Raiden
{
    int w(int x)//求Weight函数
    {
        int res=x,num=0;
        int s=0;
        while(res)
        {
            res/=10;
            num=num*10+9;
        }
        return (num-x)*x;
    }
    signed work()
    {
        int l, r;
        cin >> l >> r;
        int ans=max(w(l),w(r));
        int ll = l, rr = r;
        int ls = 0, rs = 0;//统计位数
        while (ll)ls++, ll/=10;
        while (rr)rs++, rr/=10;
        for(int i=ls;i<=rs;i++)
        {
            int num=5*pow(10,i-1);
            if(l<=num&&num<=r)
            {
                ans=max(ans,w(num));
            }
        }
        cout<<ans<<endl;
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Raiden::work();
}
```

---

## 作者：Dreamerly (赞：0)

## 题目：[CF86A](https://www.luogu.com.cn/problem/CF86A)
## 题意：
已知 $x\in\left[l,r\right]$，$f(x)=x\times\left(C-x\right)$，其中 $C=9999...$，($9$ 的个数与 $x$ 的位数相同)。求 $f(x)$ 的最大值。
## 思路：
首先，暴力枚举肯定过不了，优化枚举又复杂。然后看到函数最大值，不妨直接数学思维。

**先考虑 $l$ 和 $r$ 位数相同：**

通过函数绘图或手模可以得出，当 $x=\frac{C}{2}$ 时，$f(x)$ 有最大值，且两边呈单调递减。![详见函数绘图](https://cdn.luogu.com.cn/upload/image_hosting/yxvgxvuj.png)
因此我们只需看 $x\in\left[l,r\right]$ 时，谁更接近 $\frac{C}{2}$，输出 $f(x)$ 即可。

**再考虑 $l$ 和 $r$ 位数不同：**

这里举个例子。若 $l=100,r=2000$。我们知道，对于三位数(即 $l$ 的位数)，$x=\frac{999}{2}$ 时有最大值，取整为 $499$ 或 $500$；但对于四位数(即 $r$ 的位数)，$x=\frac{1000}{2}$，取整为 $500$，与三位数的最大值一样。其他情况皆是如此，由此得到结论 **$x$ 的位数越大，$f(x)$ 越大**。

因此我们将这种情况看成 $x\in\left[10^{len(r)-1},r\right]$，同上解决即可。
## 代码：
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int read(){ 
	int num=0,sign=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') sign=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		num=(num<<3)+(num<<1)+(ch^48);
		ch=getchar(); 
	}
	return num*sign;
} 
void write(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
	return;
}
int get_len(int x){
	int len=0;
	while(x) len++,x/=10;
	return len;
}
int fpow(int base,int power){
	int res=1;
	while(power>0){
		if(power&1) res=res*base;
		base*=base;
		power>>=1;
	}
	return res;
}
signed main(){
	int l=read(),r=read();
	int lenl=get_len(l);
	int lenr=get_len(r);
	int C=fpow(10,lenr)-1;
	int mid=C>>1; 
	
	if(l>=mid) write(l*(C-l));
	else if(r<mid) write(r*(C-r));
	else write(mid*(C-mid));
	return 0;
}
```


---

