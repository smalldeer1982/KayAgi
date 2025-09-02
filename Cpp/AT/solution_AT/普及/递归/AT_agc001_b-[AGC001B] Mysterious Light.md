# [AGC001B] Mysterious Light

## 题目描述

高桥くん有一个边长为 $N$ 的三枚镜子构成的正三角形, 顶点为 $A, B, C$。他有一个超级步枪，放在 $AB$ 段的 $P$ 点上，使得 $AP=X$。这个步枪将会沿着平行于 $BC$ 的方向发射一道光。

光以直线传播，以镜子的形式反射，但是有一个特殊的地方：它会被自己的轨迹反射，当光回到步枪的时候，光被吸收。
下面的图显示了当 $N=5, x=2$ 时的光轨迹。

![avatar](https://cdn.luogu.org/upload/vjudge_pic/AT1980/82d4f7f391403506ac5ef0aff8934e6a17530f07.png)

给定 $N$ 和 $x$，求出光线的总长度。

## 说明/提示

对于所有数据，$2≤N≤10^{12}$，$1≤x≤N-1$，保证 $N, x$ 是整数。

另外，有 $300$ 分的部分分保证 $N \le 1000$。

## 样例 #1

### 输入

```
5 2```

### 输出

```
12```

# 题解

## 作者：ztntonny (赞：23)

# **数学解法**
刚看到图脑子一团乱，自己画了一个，就发现每一条线段的长度变化特别像小奥~~噩梦~~辗转相除法，具体就是拿现有第二小的减现有第一小的，再重复直到得出 $0$ 。而其目的就是找到最大公约数，考虑几何意义，主要是平移![](https://cdn.luogu.com.cn/upload/image_hosting/v20ffmb9.png)转换成几何就是![](https://cdn.luogu.com.cn/upload/image_hosting/h2hwdbs6.png)可得式子 $3 × ( n - \gcd ( n , x ) )$，下面就是快乐代码时间：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
	ll x , n;
	cin >> n >> x;
	cout << 3 * ( n - __gcd ( n , x ) );
	return 0;
}
```
谢谢！

---

## 作者：Acerkaio (赞：15)

# 题意：
高桥 くん 有一个边长为 N 的三枚镜子构成的正三角形 , 顶点为 a, b, c. 他有一个超级步枪 ， 放在 AB 段的P点上，使得 AP=X 。 并沿着平行于 BC 的方向发射一道光 。
![AT1980](https://cdn.luogu.org/upload/vjudge_pic/AT1980/82d4f7f391403506ac5ef0aff8934e6a17530f07.png)

光以直线传播 ， 以镜子的形式反射 ， 但是有一个特殊的地方 ： 它会被自己的轨迹反射 ， 当光回到步枪的时候 ， 光被吸收 。  下面的图显示了当 n=5 ，x=2 时的光轨迹 。 求出光线的总长度 。
# 题解：
### 本体采用递归求解
图中射出的第一条线加上第二条线就等于线段 ab :
![1 + 2 = ab](https://cdn.luogu.com.cn/upload/image_hosting/rqbnkrao.png)

所以递归是可以不把第一条线和第二条线计算上。

新增加的为 $ 2\times (x-x\bmod y) $ 用一个计数变量计入可 ;

当到最后一步 $ 2-x \bmod y $ ，就增加了 $ 2 \times x-y $


# CODE:

```
#include <bits/stdc++.h>
using namespace std;
long long ans;
void gx( long long n, long long x )
{
	if ( n % x == 0 )
	{
		ans += n * 2 - x;
		return;
	}else  {
		ans += (n - n % x) * 2;
		gx( x, n % x );
	}
}


int main()
{
	long long n, x;
	cin >> n >> x;
	ans	= n;
	n	-= x;
	gx( max( n, x ), min( n, x ) );
	cout << ans;
	return(0);
}
```



---

## 作者：ImmortalWatcher (赞：9)

tips：

- 发现问题的本质，可以考虑看看是否能递归或者分治解决同样的子问题。

**solution 1**

射出两条射线之后，问题就变成了从一个平行四边形中不断射来射去，可以递归解决子问题。

也就是探究射线在一个固定长度的平行四边形中射两下会移动多少距离，这个可以手玩得出。

**solution 2**

这个解法更加巧妙和精简。

手玩可以发现，光的路径一定能拆成若干个等边三角形，不然就回不到 P 点了。

所以最后的答案一定可以平移为一个大的等边三角形。

我们考虑计算这个大等边三角形的边长。

考虑在光移动的时候，当等边三角形封闭的时候计算它的贡献。

观察下图边长的关系：

![](https://cdn.luogu.com.cn/upload/image_hosting/gkju1yu1.png)

~~画的有点丑，不要介意~~

黄色为光的路径，红色为拆分的等边三角形，每条边的边长已经标好，不放心的可以倒角自己算一下。

然后我们就可以发现边长的变化是 $n-x$ 与 $x$ 在做差得到的（大减小），虽然好像图画的太简单还是不太容易看出来，可以画一个更大的更复杂的规律会更明显。

实际上这就是 $n-x$ 和 $x$ 再做更相减损。

考虑更相减损术的几何表示方法。

![](https://cdn.luogu.com.cn/upload/image_hosting/o49c6hf4.png)

发现红色路径就是我们要求的东西，最后剩下的那一小块边长根据更相减损术的意义就是 $\gcd(n-x,x)=\gcd(n,x)$，平移一下就可以得到红色路径的长度就是 $n-\gcd(n,x)$，所以最后的答案就是 $3(n-\gcd(n,x))$，时间复杂度是 $O(\log{n})$。

```cpp
#include<cstdio>
using namespace std;
long long n,x;
long long gcd(long long x,long long y){return !y?x:gcd(y,x%y);}
int main()
{
	scanf("%lld%lld",&n,&x);
	printf("%lld",3*(n-gcd(n,x)));
	return 0;
}
```


---

## 作者：klii (赞：5)

[$\Huge\textbf{题面}$](https://www.luogu.com.cn/problem/AT1980)

![](https://cdn.luogu.org/upload/vjudge_pic/AT1980/82d4f7f391403506ac5ef0aff8934e6a17530f07.png)

直觉告诉我们路径应该会有“循环节”的。

观察上图，可以发现图中有很多等边三角形，但是很难下手。

注意到路径的所有线段都是与 $\triangle{abc}$ 的三边平行的，可以从中提取一个“循环节”$\text{--------}$ 平行四边形。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/po1j4iqm.png)

~~好丑~~

平行四边形 $ABCD,ABEF,AHGF$都是类似的，由此可以递归求解。

怎么求？

假设我们已经知道平行四边形的较短边为 $x$，较长边为 $n$，记该问题为 $(n, x)$， 观察上图，可以分两种情况：

$\bullet$ 如平行四边形 $ABCD$：

可以分为子问题 $ABEF$ 以及 $CF,EF$ 的长度和。

由于题目给定的是等边三角形，可以证明 $CF,EF$ 这一类的边都是相等的。

观察这种边的数量，可以得到边数为 $2*\left\lfloor\frac n x\right\rfloor$ 。

$BE = n \%x,EF = x$， 子问题即为 $(x, n \% x)$。 ~~( $\gcd$！~~

$\bullet$ 如平行四边形 $AHGF$：

若出发点为 $A$，则跑完该问题后光已经回到了起点，被吸收。因此并不需要继续求子问题。

这种情况的充要条件是 $n \%x == 0$ 。

观察所走的边数，发现与之前不一样，少走了一条边（想想之前的最后一条边有什么作用就明白了），于是边数为 $2 * \left\lfloor\frac n x\right\rfloor - 1$ 。

于是就做完了。

代码：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
long long ans;
void solve(long long n, long long x) {
	if (n % x == 0) {
		ans += (2 * (n / x) - 1) * x;
		return;
	}
	ans += 2 * (n / x) * x;
	solve(x, n % x);
}
int main() {
	long long n, x;
	scanf("%lld%lld", &n, &x);
	ans = n;
	solve(n - x, x);
	printf("%lld", ans);
	return 0;
}
```


---

## 作者：wheneveright (赞：4)

[AT1980 [AGC001B] Mysterious Light](https://www.luogu.com.cn/problem/AT1980)

## 分析

注意到在两次反射之后就一直是在一个一个平行四边形中反射，考虑递归解决。

先考虑前两次反射的长度，随便画个图就知道是 $n$。

接下来定义 $f (n, m)$ 表示平行四边形两边分别为 $n, m$ 的答案。

发现在这次反射没到边界上时就是 $m$，到了的话就进入下一层递归。

那么在一个四边形中没触碰边界是反射几次？手推一下就知道是 $2 \times \lfloor \frac n m \rfloor$。

下一层递归的四边形是什么？首先因为上面已经出现过除法了，这里肯定是有一股 $n \mod m$ 另外一个边显然是 $m$。

注意最后把最后一次的 $n$ 减掉，因为已经碰到激光枪了不需要再反射一次。

## 代码

复杂度参考 `gcd`，根本不用像别人写那么长嘛。

```cpp
# include <bits/stdc++.h>
using namespace std;

long long f (long long m, long long n) {
	return m == 0 ? -n : n / m * m * 2 + f (n % m, m);
}

int main () {
	long long n, x;
	cin >> n >> x;
	cout << n + f (n - x, x);
	return 0;
}
```

---

## 作者：miaokehao (赞：4)

这道题观察样例的图形，可以看出这道题本质上是一个可以分治的问题，其基本图形为平行四边形，假设长的边为a，短的边为b，那么如果a%b==0,ans+=(a<<1)-b,否则可以递归成子问题;
```
#include <bits/stdc++.h>
#define res register ll
#define ll long long
using namespace std;
ll n,x,ans;
inline ll read()
{
  ll X=0,w=0;
  char ch=0;
  while(!isdigit(ch))
  {
    w|=ch=='-';
    ch=getchar();
  }
  while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
  return w?-X:X;
}
inline void dfs(res l,res s)
{
  if(l%s==0)
  {
    ans+=(l<<1)-s;
    return;
  }
  ans+=l/s*s*2;
  dfs(s,l%s);
}
int main()
{
  n=read(),x=read();
  ans=n;
  if(x>=n-x)
    dfs(x,n-x);
  else
    dfs(n-x,x);
  printf("%lld\n",ans);
  return 0;
}
```

---

## 作者：judgejudge (赞：3)

# 递归子程序
这道题本质就是递归。只是有点难分辨罢了。

我们可以看回原来的图片。

![](https://cdn.luogu.com.cn/upload/image_hosting/06tu2eal.png)


我们先除去第一条和第二条光线（因为**由等边三角形可以得到光线1+光线2等于ab**)，剩下的很明显看出是递归啦。

那么怎么个递归法呢？？

我们由图看到这需要递归的两条边都是在不断地缩小，**而且满足x和y，递归后是y,x%y的关系。** 新增加的边数等于**2乘以(x-x%y)** 的关系。（因为不能整除，所以要先减去多出来的部分。再乘以2）

最后一步时，即x%y==0时，我们观察一下，由等边三角形的规律，我们发现，增加的边数等于**2*x-y**(因为y前面已经算入)。

AC代码：
```cpp
#include <iostream>
using namespace std;
typedef long long ll;
ll n,m;
ll ans;
inline void dfs(ll x,ll y){
	if(x%y==0){//如果到最后一步
		ans+=x*2-y;//根据观察得到的规律
		return ;
	}
	else{
		ans+=(x-x%y)*2;//注意减去多出来的部分
		dfs(y,x%y);//递归，较短的部分和多出来的部分
	}
}
main(){
	cin>>n>>m;
	ans=n;//初始值由n开始
	n-=m;
	dfs(max(n,m),min(n,m));//递归
	cout<<ans<<endl; 
	return 0;
}
```


---

## 作者：听取MLE声一片 (赞：2)

简单递归题。

容易发现原题可以化为求边长分别为为 $x,y$ 的平行四边形一个顶点到达对角顶点的长度。我们用 $f(x,y)$ 表示上述计算。

不难看出开始的两段由于等边三角形长度之和一定为大等边三角形边长，所以答案为 $N+f(X,N-X)$。

我们来看如何求 $f(x,y)$。光经过反射会又形成一个边长分别为 $y,x\mod y$ 的平行四边形，这个进行递归。这部分光会有 $k=\lfloor \frac{x}{y} \rfloor$ 段，每段长度均为 $2\times y$。所以 $f(x,y)=2\times k\times y+f(y,x\mod y)$。

我们发现形式类似于辗转相除。当最后的 $y$ 等于 $0$ 的时候，需要返回 $-x$ 来抵消上一步多走的一部分。

代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,x;
int solve(int x,int y){
	if(y==0)
		return -x;
	int k=(x/y);
	return k*2*y+solve(y,x%y);
}
signed main()
{
	n=read(),x=read();
	cout<<n+solve(x,n-x);
	return 0;
}
```



---

## 作者：int32 (赞：1)

新年快乐！

## $\sf Sol$

这些反射不断构成平行四边形，于是考虑递归求解。

设 $s(a,b)$ 表示长边为 $a$，短边为 $b$ 的情况。

由图可得，最开始是 $s(n-x,x)$，然后是 $s(x,(n-x)\bmod x)$（即 ，直到 $a\bmod b=0$ 即结束。每次增加的边长度为 $\lfloor\dfrac{a}{b}\rfloor\times2b$。

所以只要模仿 $\gcd$ 的算法模拟即可。

## $\sf Code$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, x;
int fun(int a, int b){
    if(b==0) return -a;
    return fun(b,a%b)+(a/b)*b*2;
}
signed main(){
    cin>>n>>x;
    cout<<fun(x,n-x)+n;
    return 0;
}
```

---

## 作者：MattL (赞：1)

[洛谷链接](https://www.luogu.com.cn/problem/AT1980)

[原题链接](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/1980)

------------
**分析：**

这是一道藏得较深的递归题。

---
**思考：**

看原图：

![](https://cdn.luogu.org/upload/vjudge_pic/AT1980/82d4f7f391403506ac5ef0aff8934e6a17530f07.png)

留下有用部分：

![](https://cdn.luogu.com.cn/upload/image_hosting/vv1p8ea3.png)

可以看到，有用部分是一个平行四边形。

如何递归呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/v8lesczh.png)

看，去掉指向左上和右边的光柱（箭头），有用部分又是一个平行四边形。

![](https://cdn.luogu.com.cn/upload/image_hosting/6q72vh0v.png)

再去掉指向左上和右上的光柱（箭头），有用部分还是一个平行四边形。

---

**解题：**

设 $f_{q,w}$ （~~别问我为啥要用 q,w~~ ）为每个状态下的平行四边形， $q$ 代表长边边长， $w$ 代表短边边长。

开始状态：（假设 $n-x>x$ 但其实你看了递归式子后就知道无所谓了） $f_{n-x,x}$ 。

去掉两条长为 $x$ 的边，状态转移成了 $f_{x,n-2\times x}$ ，把他改成模的形式，记作 $f_{x,(n-x)\bmod x}$。

又去边时，发现大的数是小的数的倍数，就不用继续递归了，直接去 3 条边就行了。

综上所述，得出递归式：

$$qp(q,w)\begin{cases} ans+=(2\times(q\div w)-1)\times w &q \bmod w= 0\\ans+=2\times(q\div w)\times w  ,qp(w,q\bmod w ) &q\bmod w\neq 0 \end{cases}$$

---
**上代码：**

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,x,ans;
void qp(long long q,long long w)
{
	if(q%w==0)
		ans+=(2*(q/w)-1)*w;
	else
	{
		ans+=2*(q/w)*w;
		qp(w,q%w);
	}
}
int main()
{
	cin>>n>>x;
	ans=n;
	qp(n-x,x);
	cout<<ans<<endl;
}
```


---

