# Vasya and Triangle

## 题目描述

Vasya has got three integers $ n $ , $ m $ and $ k $ . He'd like to find three integer points $ (x_1, y_1) $ , $ (x_2, y_2) $ , $ (x_3, y_3) $ , such that $ 0 \le x_1, x_2, x_3 \le n $ , $ 0 \le y_1, y_2, y_3 \le m $ and the area of the triangle formed by these points is equal to $ \frac{nm}{k} $ .

Help Vasya! Find such points (if it's possible). If there are multiple solutions, print any of them.

## 说明/提示

In the first example area of the triangle should be equal to $ \frac{nm}{k} = 4 $ . The triangle mentioned in the output is pictured below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1030D/7ee3f0a3ce75449bbc8ed199a32a394763a46df2.png)In the second example there is no triangle with area $ \frac{nm}{k} = \frac{16}{7} $ .

## 样例 #1

### 输入

```
4 3 3
```

### 输出

```
YES
1 0
2 3
4 1
```

## 样例 #2

### 输入

```
4 4 7
```

### 输出

```
NO
```

# 题解

## 作者：da32s1da (赞：8)

首先，有结论：

$$\text{(0,0),(x,0),(0,y)}\ ,1\le x\le n,1\le y\le m \ \text{可表示出}\frac{1}{2}\text{到}\frac{n\times m}{2}\text{之间的所有的}\frac{z}{2}\ ,1\le z\le n\times m$$

证明显然。

令$x=1,y=1...m$，表示$\frac{1}{2}\ .\ .\ .\ \frac{m}{2}$。

令$x=2,y=1...m$，表示$(2\times \frac{1}{2})\ .\ .\ .\ (2\times \frac{m}{2})$。

令$x=3,y=1...m$，表示$(3\times \frac{1}{2})\ .\ .\ .\ (3\times \frac{m}{2})$。

$....$

令$x=n,y=1...m$，表示$(n\times \frac{1}{2})\ .\ .\ .\ (n\times \frac{m}{2})$。

综上。

回到本题。由于是端点三角形，我们知道面积肯定是$\frac{z}{2}\ ,1\le z\le n\times m$。

于是判掉无解。

此时答案是$\frac{x\times y}{2}=\frac{n\times m}{k}=\frac{\frac{2\times n\times m}{k}}{2}$。

故$x\times y=\frac{2\times n\times m}{k}$。

因为$x,y$都是整数，且$1\le x\le n\ ,1\le y\le m$，所以我们令$x=\frac{2n}{\gcd(2n,k)},y=\frac{m}{\frac{k}{\gcd(2n,k)}}$。

但此时$x$可能大于$n$，此时$x$一定是$2$的倍数。我们让$x=\frac{x}{2}\ ,y=2y$。此时一定满足$1\le x\le n\ ,1\le y\le m$，输出即可。

```
#include<cstdio>
typedef long long LL;
LL n,m,k,X,Y;
LL gcd(LL u,LL v){return v?gcd(v,u%v):u;}
int main(){
	scanf("%I64d%I64d%I64d",&n,&m,&k);
	if(k/gcd(n*m,k)>2){//特判无解
		puts("NO");
		return 0;
	}
	puts("YES");
	printf("0 0\n");//原点
	X=(2*n)/gcd(2*n,k);
	if(X>n)X/=2,m*=2;//调整解
	k/=gcd(2*n,k);
	Y=m/k;
	printf("%I64d 0\n",X);
	printf("0 %I64d\n",Y);
}
```

---

## 作者：chen_hx (赞：4)

## 概述

>看了一下题解，好像都是 gcd 或者 $\sqrt n$ 的弄因数出来的算法。然后本人在数学课上胡出了一种 $O(1)$ 的构造，如下

## 过程

>首先可以知道 $k | n \times m \times 2$ ，然后设 $x=\frac{n \times m \times 2} k$ 。  

* >假如 $n \ge x$ ，那么直接令底为 $x$ ，令高为 $1$。

* >假如 $n < x$  ，那么令底为 $n$ ，然后就可以得知高为 $\frac x n$ ，但是这个可能是一个小数，因此就需要用等积变形把它变成一个整数的坐标。现在三角形的底是平行于坐标轴的，如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/zpt3u11t.png)

>然后把 $(0,0)$ 抬高一个点，这样子这个三角形的底边就是倾斜的了，如下

![](https://cdn.luogu.com.cn/upload/image_hosting/9n0mz6p3.png)

>接着右上角的那一个点就可以在灰线上乱滑了，由于斜线的斜率为 $\frac{1}{n}$ ，就意味着这个点每向 $x$ 轴挪一个整点，纵坐标就增加了 $\frac{1}{n}$ 。就这样可以把 $y$ 坐标调整到 $\lceil \frac{x}{n} \rceil$ ，如下

![](https://cdn.luogu.com.cn/upload/image_hosting/yu54nolp.png)

>其中 $t$ 就是向左滑行的量，$t = (\lceil \frac{x}{n} \rceil - \frac{x}{n})\times n $，显然这个 $t$ 是小于 $n$ 的，因为 $\lceil x \rceil - x < 1$ ,然后这个三角形的面积就是 $\frac x 2$ 的，和题目要求一致。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch))f^=ch=='-',ch=getchar();
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return f?x:-x;
}

int n,m,k,s,x,y;
signed main(){
	n=read(),m=read(),k=read();
	s=n*m*2;
	if(s%k)return 0&puts("NO");
	else puts("YES");
	s/=k;
	puts("0 0");
	if(n>s){
		printf("%lld 0\n",s);
		printf("%lld 1\n",s);
		return 0;
	}
	else{
		printf("%lld 1\n",n);
		int tmp=ceil((1.00*s)/(1.00*n));
		y=tmp*n-s;
		printf("%lld %lld\n",y,tmp);
	}
}
```



######  跪求管理大大过审吧

---

## 作者：DJRzjl (赞：2)

# [CF1030D](https://www.luogu.com.cn/problem/CF1030D)  Vasya and Triangle

我们发现，一个整点三角形的面积的两倍一定是一个整数，因此 $k \nmid 2nm$​ ​时就一定无解，否则就有解。

考虑在平面上选取三个点 $A(0,0),B(0,a),C(b,0)$​​​​，它们连线构成直角三角形，于是需要满足 $a \times b =\frac{2nm}k$​，那为什么一定存在这样的 $a\le m,b\le n$​​​​​ 呢？

- 当 $k$​​​​​​​​​​​​​​​​​​​​​​​​ 是偶数。$\large \frac{2nm}k=\frac{nm}{\frac k 2}$​​​​​​​​​​​​​​​​​​​​​​​​，然后枚举 $\frac k 2$​​​​​​​​​ ​​​​​​​​​​​​​​​的质因数，能除到 $n$​​​​​​​​​​​​​​​​​​​​​​​​ 下面的除到 $n$​​​​​​​​​​​​​​​​​​​​​​​​ 下面，其他的就除到 $m$​​​​​​​​​​​​​​​​​​​​​​​​ 下面，最终得到的 $\frac n{k1},\frac m{k2}\small(k1\times k2=\frac k2)$​​​​​​​​​​​​​​​​​​​​​​​​ 就作为 $b,a$​​​​​​​​​​​​​​​​​​​​​​​​。
  证明可行性：由于 $\frac{2nm}k$​​​​​​​​​​​​​​​​​​​ ​​​​​一定是一个整数，所以 $\frac k2$​​​​​​​​​​​​​​​​​​​​​​​​ 一定能分为合法的 $k1,k2$ 除到 $n,m$ 下面。

- 当 $k$​​​​​​​​​​​​​ 是奇数。直接枚举 $k$​​​​​​​​​​​​​ 的质因数，然后同上面的方法将 $k$​ 分为 $k1,k2\small (k1 \times k2=k)$​ 除到 $n,m$ 的下面，处理完后还要处理那个 $2$​​​​​​​​​​​​：

  若此时 $\frac {2n} {k1}\le n$​，则让 $b=\frac{2n}{k1},a=\frac m{k2}$​；否则让 $b=\frac n{k1},a=\frac {2m}{k2}$。​

  证明可行性：由于 $\frac{2nm}k$ 一定是整数，且 $k$ 是奇数，所有 $\frac{nm}k$ 也一定是整数，所以 $k$ 一定可以分为 $k1$ 和 $k2$，然后由于 $k \ge 2$，所以最后 $k1$ 和 $k2$ 之间至少有一个能够 $\ge 2$，所以 $\frac {2n} {k1}\le n$ 和 $\frac {2m}{k2}\le m$ 二者至少满足其一。
  
  
## Code


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int n,m,k;
pair<int,int>res;

pair<int,int> solve(int x,int n,int m){
	int T=sqrt(x);
	for(int i=2;i<=T;i++){
		while(x%i==0){
			if(n%i==0) n/=i;
			else m/=i;
			x/=i;
		}
	}
	if(x>1){
		if(n%x==0) n/=x;
		else m/=x;
	}
	return make_pair(n,m);
}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	if(2ll*n*m%k) return puts("NO")&0;
	puts("YES");
	if(k%2==0) res=solve(k/2,n,m);
	else {
		res=solve(k,n,m);
		if(res.first*2<=n) res.first*=2;
		else res.second*=2;
	}
	printf("0 0\n0 %d\n%d 0\n",res.second,res.first);
	return 0;
}
```


---

## 作者：unputdownable (赞：2)

对于任意的格点三角形，由[皮克定理](https://baike.baidu.com/item/%E7%9A%AE%E5%85%8B%E5%AE%9A%E7%90%86)可知，它的面积一定是 $\frac 1 2$ 的倍数。

那么首先判掉 $2 \times \frac {n \times m} k$ 不是整数的情况，即 $k$ 不整除 $2 \times n \times m$ 的情况。

那么容易想到构造一个直角顶点在 $(0,0)$ 的三角形，设剩余的两个顶点为 $(a,0)$ 和 $(0,b)$，

这个三角形的面积就是 $\frac {a \times b} 2$，与长方形的面积比是 $\frac 1 2 \times \frac a n \times \frac b m$，这个要等于 $\frac 1 k$。

若 $2|k$，则 $\frac k 2 | (n \times m)$，令 $a$ 等于 $\gcd(n,\frac k 2)$，此时推出来的 $b$ 必然小于等于 $m$。

否则，有 $k | (n \times m)$，考虑将 $k$ 乘 $2$ 后再构造，构造出来一组 $(a',b')$，我们需要将其面积乘 $2$。

此时有 $\frac n {a'},\frac m {b'}$ 是正整数，且乘积为 $k$（有 $k>1$）。

容易发现两数中至少有一个 $\geq 3$。

不妨设 $\frac n {a'} \geq 3$，令 $(a,b)=(2a',b')$，此时有 $a\leq \frac2 3 n$。

另一边同理。

**Code**（与上面说的有些出入，大致同理）。

```
int n,m,k;
signed main() {
    n=read(); m=read(); k=read();
    if(n*m*2%k!=0) {
        puts("NO");
        return 0;
    }
    int g=__gcd(n,k);
    int j=k/g;
    int l=2*m/j;
    int c=n/g;
    if(l>m) {
        l/=2;
        c*=2;
    }
    puts("YES");
    puts("0 0");
    printf("0 %d\n",l);
    printf("%d 0\n",c);
	return 0;
}
```

---

## 作者：wjyyy (赞：2)

[在我的blog里看](http://www.wjyyy.top/1770.html)

## 题意：
在$n\times m$的矩形中找出一个格点三角形，使得$S_\triangle=\frac{nm}k,k\ge 2$。

## 题解：

   首先这个题要求出在$n\times m$的矩形中，是否存在一个**格点三角形**，使得这个格点三角形的面积为$\frac{nm}k$。

   如果我们直接构造，可能需要枚举的东西太多了，$n,m,k$都达到了$10^9$的数量级。但是我们可以发现题目中$k$一定$\ge 2$，那么如果能构造，就一定可以被装在这个$n\times m$的矩形中。因为$n\times m$的矩形最大可以装下$\frac{nm}2$的三角形。此时问题转化为能否构造出一个$\frac{nm}k$的格点三角形，注意这个题还需要**输出顶点方案**。

   样例给出了一个合法的数据和一个不合法的数据，一开始感觉上下互质可能会出问题，但是这个题和质数貌似没有关系。但是和约分肯定有关，因此猜想：格点三角形的面积一定是$\frac 12$的倍数。也就是说，$\frac {nm}k$约分后，分母不是$1$就是$2$。

   既然是三角形，由于初中老师教过割补法求平面直角坐标系中三角形的面积，那我们就证一下这个猜想。我们构造一个任意的格点三角形，那么这个格点三角形的面积可以表示为一个边与坐标轴平行的矩形，减去三个直角三角形，这三个直角三角形都满足直角边与坐标轴平行。

![](http://www.wjyyy.top/wp-content/uploads/2018/09/201809251512.png)

   这个矩形的面积是一个整数，则三角形的面积为$S_\triangle=\frac{ab}2$。又因为在格点三角形中，$ab$是整数，所以$S_\triangle$一定是$\frac 12$的倍数。

   证完这个东西，我们发现三角形就是可构造的了。设要求的三角形面积为$S=\frac t2,t\in \mathbb N^*$，那么我们只需要在这个$n\times m$的三角形中找出$a\le n,b\le m$使得$ab=2S=t$即可，此时$t$并不会爆`long long`。那么一定存在这样一组整数对$(a,b)$吗？答案是肯定的。

   要证存在整数对$(a,b)\ \mathrm{St.}\ ab=\frac{2nm}{k},a\le n,b\le m$，且$\gcd(2nm,k)=k,k\ge 2$。那么由于$\gcd(2nm,k)=k$，除出来的结果是整数，不考虑分子上的$2$，则这个整数应该只含$n,m$的质因子，且$ab\le nm$。

### 单独讨论分子上的$2$

* 如果满足$k|2$，则这个整数满足“只含$n,m$的质因子”，并且$ab\le nm$；

* 如果$k\not|2$，则$k\ge 3$，但是满足$\gcd(2nm,k)=k$，可知$\frac{2nm}k<nm$，同时$k|nm$，让$ab=\frac 2k\cdot nm$，约掉之后就可以使$n$或$m$中至少一个减小。比方说$k=p_1p_2$，则$ab=2\cdot \frac {n}{p_1}\cdot \frac{m}{p_2}$，则$ab\le nm$。又因为$p_1\ge 2$或$p_2\ge 2$，且$ \frac {n}{p_1},\frac{m}{p_2}$都是整数，因此$p_1,p_2$中至少有一个满足$\frac{2n}{p_1}\le n$或$\frac {2m}{p_2}\le m$。虽然不一定满足“只含$n,m$的质因子”，但是多出来的只是一个$2$，它可以被$\frac 2k$中的$k$约掉，从而达到上一句话的情况，就可以用$a,b$来表示了。


  最后需要得出答案，构造出一个**直角三角形**，直角边分别为$a,b$，如何枚举$(a,b)$呢？作为$S'=\frac{2nm}k$的约数，它的枚举复杂度为$\sqrt{S'}$，数量级是$10^9$，从$1$开始容易$TLE$，事实上良心的pretest10也卡掉了我的前两次提交。因为$a\le n,b\le m$，所以枚举起点应该在$\lfloor \frac{S'}{\max(n,m)}\rfloor$，以避免枚举“另一条边超过$\max(n,m)$”的情况。不过最后还是要稍微检验一下（防止写快了弄混……

  其实只要推出来面积一定是$\frac 12$的倍数，和最后一段的上下界优化就可以做题了。但是为了严谨~~和题解需要~~我还是证明了一下存在性……

## Code：

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
long long n,m,k;
long long gcd(long long a,long long b)
{
    if(!b)
        return a;
    return gcd(b,a%b);
}
int main()
{
    scanf("%I64d%I64d%I64d",&n,&m,&k);
    long long tt=n>m?n:m;
    int flag=(n>=m);
    k=k;
    long long t=n>m?n:m;
    n=n*m;
    long long tmp=gcd(n,k);
    n/=tmp;
    k/=tmp;
    if(k>2)
    {
        puts("NO");
        return 0;
    }
    if(k==1)
        n*=2;
    long long up=sqrt(n)+1;
    for(int i=(n/tt)?(n/tt):1;i<=up;++i)
        if(n%i==0)
            if(n/i<=t)
            {
                n=n/i;
                m=i;
                break;
            }
    puts("YES");
    puts("0 0");
    if(flag)
    {
        printf("%I64d 0\n",n);
        printf("0 %I64d\n",m);
    }
    else
    {
        printf("%I64d 0\n",m);
        printf("0 %I64d\n",n);
    }
    return 0;
}
```

---

## 作者：我打 (赞：1)

[博客链接](https://www.cnblogs.com/Laoli-2020/p/15757636.html)

题目翻译：给定$n,m,k$，让你求出三个整点$A(x1,y1),B(x2,y2),C(x3,y3)$，其中$0 \le x1,x2,x3 \le n$，$0 \le y1,y2,y3 \le m$，$S_{\triangle ABC}=\frac{nm}k$。
数据范围：$1 \le n,m \le 10^9$，$2 \le k \le 10^9$。

我们发现，一个整点三角形的面积的两倍一定是一个整数，因此 $k \nmid 2nm$ 时就一定无解，否则就有解。

我们考虑在平面上选取三个点 $A(0,0),B(0,a),C(b,0)$，那么 $a \times b =\frac{2nm}k$。

 - 当$k$是个偶数的时候， $\large \frac{2nm}k=\frac{nm}{\frac k 2}$，然后枚举 $\frac k 2$ 的质因数，能除到$n$下面的除到$n$，否则就除到$m$下面，最终得到的 $n,m$ 就作为 $b,a$ 输出。
证明可行性：由于 $\frac{2nm}k$ 一定是一个整数，所以 $\frac k 2$ 一定能分到 $n$ 和 $m$ 下。

 - 当 $k$ 是个奇数的时候，直接枚举$k$的质因数，然后按照上面的方法分别除到 $n$ 和 $m$ 的下面，处理完$k$后还要处理那个2，如果此时的 $n$ 乘 $2$ 不超过限制就使得 $n$ 变成 $n \times 2$，否则就给 $m$ 乘 $2$，输出同上。
证明可行性：由于 $\frac{2nm}k$ 一定是一个整数，且$k$是个奇数，所有 $\frac{nm}k$ 也一定是一个整数，所以 $k$ 一定能分下去，然后由于 $k \ge 2$，所以最后 $n$ 和 $m$ 之间必定有一个能够乘 $2$ 的。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	int N=n,M=m;
	if(2ll*n*m%k!=0)
		return puts("NO")&0;
	puts("YES");
	int ok=1;
	if(k%2==0)
		k/=2,ok=0;
	long long S=2ll*n*m/k;
	for(int i=2;i*i<=k;i++)
		while(k%i==0)
		{
			if(n%i==0)
				n/=i;
			else
				m/=i;
			k/=i;
		}
	if(n%k==0)
		n/=k;
	else
		m/=k;
	if(ok)
	{
		if(n*2<=N)
			n*=2;
		else
			m*=2;
	}
	printf("0 0\n0 %d\n%d 0\n",m,n);
	
	return 0;
}
```

---

## 作者：IMIDAZOLE (赞：1)

# 思路
这是一道数论题

首先，有一个结论：**整点三角形面积的两倍必定为整数**

~~证明：无……~~

只要不符合这个结论的情况就是无解，直接输出即可

其次，我们设 $A(0,0)$ , $B(a,0)$ , $C(0,b)$ , ~~简单粗暴……~~

#### $ab = \frac{2nm}{k}$

直接枚举 $k$ 的质因子（因为 $n = q_1q_2...q_k$ 其中 $q$ 为质数），这样方便把枚举出来的质因子整除到 $n$ 或 $m$ 中，这样操作 $n$ 和 $m$ 中肯定有一个可以接纳，~~原因只可意会，不可言说……~~，其实仔细想想也能明白的哦

最后 $k$ 只剩个“光棍”，剩下的 $2$ 乘到 $n$ 和 $m$ 中任意一个，只要乘后的值不大于原来的 $n$ 或 $m$ 即可，最后处理完的 $n$ 作为 $a$ , $m$ 作为 $b$ , 直接输出答案就解决了
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL n,m,k,a,b;
int read() {
	int x = 0,f = 1;
	char c = getchar();
	while(c < '0' || c > '9') {
		if(c == '-')	f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9') {
		x = (x << 1) + (x << 3) + (c ^ 48);
		c = getchar();
	}
	return x * f;
}
int main() {
	a = n = read(),b = m = read(),k = read();
	if((2 * n * m) % k)	{printf("NO\n");return 0;}// 整点三角形面积的两倍必定为整数
	// 直接设 A（0，0），B（a，0），C（0，b） 
	// 要注意 a <= n && b <= m
	for(int i = 2;i <= k;i ++)
		while(!(k % i)) {
			if(!(a % i))	a /= i;
			else if(!(b % i))	b /= i;
			k /= i;
		}
	if((a << 1) <= n)	a <<= 1;
	else	b <<= 1;
	printf("YES\n");
	printf("0 0\n");
	printf("%lld 0\n",a);
	printf("0 %lld\n",b);
	return 0;
}

---

## 作者：船酱魔王 (赞：0)

## 题意回顾

有 $ n \times m $ 长宽的网格，构造一个格点三角形使其面积为 $ \frac{nm}{k} $。

## 分析

* 首先，格点三角形面积的两倍必然是整数，否则一定无解。原因：对于一个格点三角形，我们可以将其表示为一个矩形的面积减去边缘上若干个三角形的面积，显然是 $ \frac{k}{2}(k \in \mathbb{Z}) $ 的形式。
* 然后，我们找到 $ (0,0),(x,0),(0,y) $ 使得 $ xy=\frac{2nm}{k} $。
* 若 $ k \mid nm $，情况很简单，最后因为必然有一条轴上长度被扣去了至少一半，所以在那条轴上长度翻倍即可。
* 若 $ k \mid nm $ 不成立，将 $ k \leftarrow \frac{k}{2} $ 即可，然后省去轴长翻倍的步骤：本质上相当于 $ k $ 和分子的 $ 2 $ 相抵消。
* 怎么去找 $ xy=\frac{nm}{k'} $ 的问题实现方法为找到 $ k_n=\gcd\{n,k'\} $，然后 $ k_m=\frac{k}{k_n} $。取 $ x=\frac{n}{k_n} $，$ y=\frac{m}{k_m} $ 即可。
 
## 参考实现

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;
int n, m, k;
int gcd(int x, int y) {
    return (y == 0) ? x : gcd(y, x % y);
}
int main() {
    cin >> n >> m >> k;
    if(((ll)n * m * 2) % k != 0) puts("NO");
    else {
        int tk = 1;
        if(k % 2 != 0) tk = 0;
        else k /= 2;
        int tn = gcd(n, k);
        int tm = k / tn;
        n = n / tn, m = m / tm;
        if(!tk) {
            if(tn > 1) n *= 2;
            else m *= 2;
        }
        puts("YES");
        printf("0 0\n%d 0\n0 %d\n", n, m);
    }
    return 0;
}
```

---

