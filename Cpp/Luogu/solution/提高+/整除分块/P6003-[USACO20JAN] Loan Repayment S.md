# [USACO20JAN] Loan Repayment S

## 题目描述

Farmer John 欠了 Bessie $N$ 加仑牛奶（$1 \leq N \leq 10^{12}$）。他必须在 $K$ 天内将牛奶给 Bessie。但是，他不想将牛奶太早拿出手。另一方面，他不得不在还债上有所进展，所以他必须每天给 Bessie 至少 $M$ 加仑牛奶（$1 \leq M \leq 10^{12}$）。

以下是 Farmer John 决定偿还 Bessie 的方式。首先他选择一个正整数 $X$。然后他每天都重复以下过程：

1. 假设 Farmer John 已经给了 Bessie $G$ 加仑，计算 $\frac{N-G}{X}$ 向下取整。令这个数为 $Y$。
2. 如果 $Y$ 小于 $M$，令 $Y$ 等于 $M$。
3. 给 Bessie $Y$ 加仑牛奶。

求 $X$ 的最大值，使得 Farmer John 按照上述过程能够在 $K$ 天后给 Bessie 至少 $N$ 加仑牛奶 （$1 \leq K \leq 10^{12}$）。

## 说明/提示

### 样例解释

在这个测试用例中，当 $X=2$ 时 Farmer John 第一天给 Bessie $5$ 加仑，后两天每天给 Bessie $M=3$ 加仑。

### 子任务

- 测试点 $2 \sim 4$ 满足 $K \leq 10^5$。
- 测试点 $5 \sim 11$ 没有额外限制。

## 样例 #1

### 输入

```
10 3 3```

### 输出

```
2```

# 题解

## 作者：Bring (赞：20)

[更好的阅读体验请点这里](https://www.cnblogs.com/BrianPeng/p/12284076.html)

## 在这里解释一下二分内judge()的操作方式

首先一定是二分$x$，不必多说

但是如果真的一天天扫过去，每次judge()是$O(k)$的，明显超时

所以在judge()时会使用类似**除法分块**的方法

假设现在剩下了$r$的欠债，还剩$t$天

循环退出条件：$r\leqslant0||t==0$，这时直接通过$r\leqslant0$的成立与否判断$x$的成立与否

那么$y=\lfloor\frac{r}{x}\rfloor$

如果$y<=m$，那么直接就以$m$为每天的还债量，于是$r-=tm,t=0$

否则就计算一下会有连续多少天的每日还债量是$y$，假设这种情况持续$a$天，那么可以知道在$a-1$天之后的还债量$=y$，而$a$天之后的还债量$<y$

于是有方程$\lfloor\frac{r-(a-1)y}{x}\rfloor=y,\lfloor\frac{r-ay}{x}\rfloor<y$

改为不等式：$\frac{r-(a-1)y}{x}\geqslant y,\frac{r-ay}{x}<y$

变形：$a\leqslant\frac r y-x+1,a>\frac r y-x$

因为$a$是正整数，所以$a=\lfloor\frac r y-x+1\rfloor$

于是在之后的连续$a$天，花费都是$y$

那么就可以快速把答案“跳”出来了

**Time complexity: $O(n^\frac{1}{2}\log n)$**（后面有证明）

**Memory complexity: $O(1)$**

细节请见代码（代码中用$rm$代替$r$）

```cpp
//This program is written by Brian Peng.
#pragma GCC optimize("Ofast","inline","no-stack-protector")
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define Rd(a) (a=read())
#define Gc(a) (a=getchar())
#define Pc(a) putchar(a)
int read(){
	register int x;register char c(getchar());register bool k;
	while(!isdigit(c)&&c^'-')if(Gc(c)==EOF)exit(0);
	if(c^'-')k=1,x=c&15;else k=x=0;
	while(isdigit(Gc(c)))x=(x<<1)+(x<<3)+(c&15);
	return k?x:-x;
}
void wr(register int a){
	if(a<0)Pc('-'),a=-a;
	if(a<=9)Pc(a|'0');
	else wr(a/10),Pc((a%10)|'0');
}
signed const INF(0x3f3f3f3f),NINF(0xc3c3c3c3);
long long const LINF(0x3f3f3f3f3f3f3f3fLL),LNINF(0xc3c3c3c3c3c3c3c3LL);
#define Ps Pc(' ')
#define Pe Pc('\n')
#define Frn0(i,a,b) for(register int i(a);i<(b);++i)
#define Frn1(i,a,b) for(register int i(a);i<=(b);++i)
#define Frn_(i,a,b) for(register int i(a);i>=(b);--i)
#define Mst(a,b) memset(a,b,sizeof(a))
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
int n,k,m,l(1),r,md;
bool jdg(int x);
signed main(){
	r=Rd(n),Rd(k),Rd(m);
	while(l<=r)jdg(md=(l+r)>>1)?l=md+1:r=md-1;
	wr(l-1),exit(0);
}
bool jdg(int x){
	int y,a,rm(n),t(k);
	while(t&&rm>0){
		y=rm/x;
		if(y>m)a=min(rm/y-x+1,t),rm-=a*y,t-=a;
		else rm-=t*m,t=0;
	}
	return rm<=0;
}
```

---

## 现在是复杂度证明

每次judge()的时间消耗就是不同$y$值的数量，假设是$d$

那么最坏情况就是不同的$y$值分别是$1,2,\cdots,d$，而且每个只出现一次

那么就有$\sum_{i=1}^d i\geqslant n$，此时使$d$最小

利用等差数列求和公式：$\frac{d(d+1)}{2}\geqslant n$

当$d=\lceil (2n)^\frac{1}{2}\rceil$时就满足不等式

所以$d=O(n^\frac{1}{2})$

于是最终时间复杂度$O(d\log n)=O(n^\frac{1}{2}\log n)$，可以AC

---

## 作者：AC_Automation (赞：12)

很明显，可以通过二分$x$的方式将极值问题转化为判定性问题。  
暴力的方法是直接模拟每一天还的牛奶量，复杂度$O(k\log n)$，能过四个点。  
考虑优化二分的判定函数。我们将还的过程分为两部分。前一部分每次还的牛奶量都大于$M$，后一部分则等于$M$。  
容易发现，在前一部分的某些情况下，会有连续几天还同样的牛奶量。考虑从这个方向去优化复杂度。  
设$r$为未还的奶量，这种情况下连续$p$天还$q$加仑。根据题意，$q=\dfrac{r}{x}$  
推式子：
$$\begin{cases}\left\lfloor\dfrac{r-(p-1)\cdot q}{x}\right\rfloor=q\\\\\left\lfloor\dfrac{r-p\cdot q}{x}\right\rfloor<q\end{cases}$$
去掉下取整
$$\begin{cases}\dfrac{r-(p-1)\cdot q}{x}\geq q\\\\\dfrac{r-p\cdot q}{x}<q\end{cases}$$
整理
$$\begin{cases}r-p\cdot q+q\geq q\cdot x\\\\r-p\cdot q<q\cdot x\end{cases}$$

$$\begin{cases}\dfrac{r}{q}-p+1\geq x\\\\\dfrac{r}{q}-p< x\end{cases}$$

$$\dfrac{r}{q}-x<p\leq\dfrac{r}{q}-x+1$$

因为$p$是一个整数，所以$p=\left\lfloor\dfrac{r}{q}-x+1\right\rfloor$

这样的话，我们就可以一次性算出很多天的还奶量了。后半部分的计算非常简单，直接除一下即可。

复杂度$O(\sqrt n\log n)$  
代码（所有变量的定义与前文相同）
```cpp
#include<iostream>
#define int long long
using namespace std;
int n,k,m;
bool judge(int x){
	int r=n,d=k;//d是剩余的天数
	while(1){
		int p,q;
		q=r/x;
		if(q<=m){
			return m*d>=r;//处理第二部分
		}
		p=r/q-x+1;
		if(p>d)p=d;//注意天数要在范围之内
		r-=p*q;
		d-=p;
		if(r<=0)return 1;
		if(d==0)return 0;
	} 
}
signed main(){
	cin>>n>>k>>m;
	int l=1,r=n,mid;
	while(l<r){
		mid=(l+r+1)>>1;//这里的二分边界要注意一下
		if(judge(mid))
			l=mid;
		else r=mid-1;
	}
	cout<<l;
	return 0;
}

```

---

## 作者：Talanton_Cerydra (赞：9)

## 这种题目还是需要用二分,才能逐步求出x最大值

首先回顾下二分的模板:

```cpp
void erfen()//二分模板
{
//使用left和right作为边界
    while(left<right)//只要left不越界
    {
        mid=(left+right+1)/2;//求出中间值
        if(judge())//这里的judge是一个判断函数,对于不同的题目需要多次编写
        {
            left=mid;//符合judge,left更新为mid
        }
        else 
        {
            right=mid-1;//不符合judge,right更新为mid-1
        }
        //就这样逐渐夹逼,最终得出结果
    }
}
```

至于这个judge,对于这道题是要判断x

所以可以这样写:

```cpp
bool judge()
{
    long long int kk=k,gq=0;//把k保存在另一个变量,以防变动
    //gq即已还的牛奶数
    while(gq<n&&kk>0)//逐渐判断
    {
        long long int ss=(n-gq)/mid;//ss指的就是题目中的y
        if(ss<m) //如果y小于m
        {
            long long int o=(n-gq+m-1)/m;//
            return o<=kk;
        }
        long long int ch=n-mid*ss;
        long long int d=(ch-gq)/ss+1;//天数
        d=min(d,kk);//如果d小于kk就让d等于kk
        gq+=ss*d;//还了y*d牛奶
        kk-=d;//过了d天
    }
    return gq>=n;//如果能按时还清就返回true,否则返回false
}
int main() 
{
    scanf("%lld%lld%lld",&n,&k,&m);//输入n,k和m
    erfen();//二分法
    printf("%lld",left);//输出最小值也就是输出left
    return 0;//结束
}
```

### 综上,给出完整代码:

```
#include <cstdio>
#include <algorithm>//不用万能头是防止left变量名带来的混乱,试一下就知道怎么回事了
using namespace std;//不解释
long long int n,k,m,left=1,right=1000000000000,mid;//把它们都定为全局变量,让所有函数都能用到
//注意数据范围,要开long long
bool judge()//二分的判断函数
{
    long long int kk=k,gq=0;//把k保存在另一个变量,以防变动
    //gq即已还的牛奶数
    while(gq<n&&kk>0)//逐渐判断
    {
        long long int ss=(n-gq)/mid;//ss指的就是题目中的y
        if(ss<m) //如果y小于m
        {
            long long int o=(n-gq+m-1)/m;//
            return o<=kk;
        }
        long long int ch=n-mid*ss;
        long long int d=(ch-gq)/ss+1;//天数
        d=min(d,kk);//如果d小于kk就让d等于kk
        gq+=ss*d;//还了y*d牛奶
        kk-=d;//过了d天
    }
    return gq>=n;//如果能按时还清就返回true,否则返回false
}
void erfen()//二分
{
//使用left和right作为边界
    while(left<right)//只要left不越界
    {
        mid=(left+right+1)/2;//求出中间值
        if(judge())//看前面的说明
        {
            left=mid;//符合judge,left更新为mid
        }
        else 
        {
            right=mid-1;//不符合judge,right更新为mid-1
        }
        //就这样逐渐夹逼,最终得出结果
    }
}
int main() //相比前两个函数而言,主函数显得十分短小
{
    scanf("%lld%lld%lld",&n,&k,&m);//输入n,k和m
    erfen();//二分法
    printf("%lld",left);//输出最小值也就是输出left
    return 0;//结束
}
```

# Farmer John ,你的牛奶还清了么?

---

## 作者：KaisuoShutong (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/P6003)

# 题目大意

给定三个整数 $N,K,M$，要求出最大的 $X$ 使得初始 $G=0$ 的一个表达式 $G+=max(\frac{N-G}{X},M)$ 累加 $K$ 次后大于 $N$。  
~~感觉把题目讲复杂了T_T~~

# 题目分析


首先看到“至少”“最大”等字眼，会想到二分答案。

那我们就胡出一个暴力算法了（~~好吧，写了忘记存了~~）。  
但是肯定过不了。

考虑优化二分瓶颈：check。  
用除法分块优化它。

推一个简单的柿子。

设当前的增加量为 $A=\frac{N-G}{X}$。  
如果共有 $K+1$ 个增加量全部都是 $A$ ，就得到：
$$\frac{(N-G)-K\times A}{X}\geq A$$
$${(N-G)-K\times A}\geq X\times A$$
$$K\times A\leq (N-G)-X\times A$$
$$K\leq\frac{(N-G)-X\times A}{A}$$
$$K\leq\frac{(N-G)}{A}-X$$
故有上式+1个增加量为 $A$。

然而这道题有一个对 $M$ 取 $max$ 的限制，所以我们考虑算出 $A$ 后先特判这次的增加量是否大于 $M$。如果不大于，那说明后面的全都是 $M$ 了，$O(1)$ 计算即可。

~~自认为非常漂亮的掐头去尾代码~~

```cpp
signed main()
{
	n=read(),k=read(),m=read();
	int l=1,r=n,mid,ans,cnt;
	while(l<=r)
	{
		mid=l+r>>1,cnt=0;
		for(int i=1;i<=k;i++)
		{
			int add=(n-cnt)/mid;
			if(add<=m) {cnt+=(k-i+1)*m;break;}
			int now=(n-cnt)/add-mid+1;now=min(now,n-i+1);
			cnt+=now*add,i+=now-1;
			if(cnt>=n) break;
		}
		if(cnt>=n) ans=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：PersistentLife (赞：5)

### Update：

2020-4-14 更改的变量的大小写，加了一些注释。

### Level $1$：暴力

从大到小枚举 $X$，然后判断是否满足条件。

代码是这样的，其中 $check$ 函数是判断当 $X$ 等于某一个值时是否符合题意。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,m,x;
bool check()
{
	int cnt=0;
	for(int i=1;i<=k;i++)
	{
		cnt+=max((n-cnt)/x,m);
		if(cnt>=n) return 1;
	}
	return 0;
}
signed main()
{
	cin>>n>>k>>m;
	for(int i=n;i>=1;i--)
	{
		x=i;
		if(check())
		{
			cout<<x;
			return 0;
		}
	}
	return 0;
}
```
然后，只有 $9$ 分，全部 TLE 。

### Level $2$：$check$ 函数优化

我们发现，$check$ 函数可以不通过暴力的方法去判断，最快的方法是计算，详见代码。

```cpp
bool check()
{
	int cnt=0;//统计目前已经归还的多少牛奶
	int i=k;
	while(i>0&&cnt<n)
	{
		int y=(n-cnt)/x;//算出 y
		if(y<m)//此时每天只有还m牛奶，所以可以直接下结论判断 
		{
			if((n-cnt+m-1)/m<=i) return true;
			else return false;
		}
		int c2=n-x*y;//通过计算判断出未来几天所还的牛奶
		int day=min((c2-cnt)/y+1,i);//还能还几天
		cnt+=y*day;//加上还的牛奶
		i-=day;//减去天数
		if(cnt>=n) return true;//此时已经归还了足够的牛奶，所以可以返回 true
	}
	return false;//如果无法满足条件就返回 false
}
```
然后，还是只有 $9$ 分。

但是，我们怎么能轻言放弃呢？于是，就有了 Level $3$ 。

### Level $3$：二分答案

我们先来看一下前两份代码的时间复杂度：

Level $1$：$\Theta(N \times K)$

Level $2$：$\Theta(N^{\frac1 2} \times \log N \times K)$

关于 Level $2$ 时间复杂度证明详见 Bring 大佬的题解 ~~（因为本蒟蒻不会）~~ 。

那么我们对 $X$ 的二分区间是多少呢？答案是 $1$ 至 $10^{12}$，因为 $\frac{N-G}{X}$ 一定小于 $N$ ，而 $X$ 是分母，根据~~小学~~数学知识，“分母越大商越小”，可以得出结论，$X \le N$。

那么时间复杂度为 $\Theta(N^{\frac1 2} \times \log N \times \log 10^{12})$ 。

此处 $\log 10^{12}$ 的值不超过 $50$，所以不用担心。

那么这个复杂度是可以通过的，上代码！

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int l,r,x,n,k,m;
bool check()
{
	int cnt=0;//统计目前已经归还的多少牛奶
	int i=k;
	while(i>0&&cnt<n)
	{
		int y=(n-cnt)/x;//算出 y
		if(y<m)//此时每天只有还m牛奶，所以可以直接下结论判断 
		{
			if((n-cnt+m-1)/m<=i) return true;
			else return false;
		}
		int c2=n-x*y;//通过计算判断出未来几天所还的牛奶
		int day=min((c2-cnt)/y+1,i);//还能还几天
		cnt+=y*day;//加上还的牛奶
		i-=day;//减去天数 
		if(cnt>=n) return true;//此时已经归还了足够的牛奶，所以可以返回 true
	}
	return false;//如果无法满足条件就返回 false
}
signed main()
{
	cin>>n>>k>>m;
    l=1;r=12;
	while(l<r-1)
	{
		x=(l+r+1)/2;
		if(check()) l=x;
		else r=x;
	}
	cout<<l;
	return 0;
}
```

~~FarmerJohn,did you pay back all the milk?~~

---

## 作者：Yesod (赞：3)

# 方法

我们可以先找一下规律：假设 $n=1000,x=100$ 时：

$$y=10,9,9,9,9,9,\cdots$$

可以发现 $n=1000$ 时 $y=10$，$n=990\sim900$ 时 $y=9$。

这样我们就可以快速写出代码：

# 代码
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,k,m,y,g,l,r,x,ans;
int main(){
	scanf("%lld%lld%lld",&n,&k,&m);
	l=1,r=n;
	while(l<=r){//二分
		x=(l+r)/2;
		g=y=0;
		for(ll i=1;i<=k;){
			y=(n-g)/x;
			if(y<=m)
			{
				g+=m*(k-i+1);
				break;
			}
			ll s=(n-g-y*x)/y+1;//快速算出区间
			g+=s*y;
			i+=s;
		}
		if(g>=n) l=x+1,ans=x;
		else r=x-1;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：信守天下 (赞：3)

## [洛谷传送门](https://www.luogu.com.cn/problem/P6003)
## 思路：二分
很难直接对 $X$ 进⾏求解，但是如果知道 $X$ ，模拟⼀下就能求出 $G$ 。

$X$ 的取值范围很⼤，⽆法逐个枚举。

但不难发现，$G$ 的增⻓是先快后慢，当⾜够慢时再变成匀速的。

其中 $X$ 越⼩，增⻓越快，所以 $G$ 关于 $X$ 单调。

可以⽤⼆分答案的⽅式求解 $X$ 。

然⽽当 $X$ 很⼤时，$G$ 每次的增⻓量很⼩。

这会导致模拟效率低下，需要进⾏优化。

仔细观察每次的增量，可以发现同样的增量会连续出现很多次。

只有当 ( $N$ - $G$ ) 时，下次操作才会导致增量变化。

所以我们可以直接计算出增量保持不变的次数，然后统⼀进⾏计算。
## $code$
~~~cpp
#include <cstdio>
#include <iostream>

using namespace std;
using LL = long long;

LL n, k, m, l, r;

bool C(LL x) {                      // 校验x是否可行
  LL g = 0;                         // 初始化已还数量
  for (LL i = 0; i < k;) {          // 按天数还牛奶
    LL y = (n - g) / x;             // 应该还的数量
    if (y <= m) {                   // 之后每天都还m
      return g + (k - i) * m >= n;  // 直接验证可行性
    }
    LL t = min(k - i, (n - g) % x / y + 1);  // 连续还y的天数
    g += t * y;                              // 累加还的数量
    i += t;                                  // 累加天数
  }
  return g >= n;
}

int main() {
  cin >> n >> k >> m;
  for (l = 1, r = n; l <= r;) {  // 二分答案
    LL mid = (l + r) >> 1;
    if (C(mid)) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  cout << l - 1;
  return 0;
}
~~~

---

## 作者：accomplishment (赞：2)

这题要求 $X_\text{max}$，只要二分一下 $X$ 就行了，关键是怎么写判断。

设 $G$ 是现在已经还给的牛奶加仑数，今天要还的牛奶加仑数就是：

$$Y = \frac{N - G}{X}$$

假设持续先连续还 $d$ 天，每天都还这么多，最后一天也剩 $Y$，那么有：

$$\left\lfloor \frac{N-G-Yd}{X} \right\rfloor = Y$$

去掉取整符号，变成：

$$\frac{N-G-Yd}{X} \geq Y$$

我们一步一步把它变成关于 $d$ 的不等式：

$$N-G-Yd \geq XY$$
$$Yd \leq N-G-XY$$
$$d \leq \frac{N-G-XY}{Y}$$

那么 $d_\text{max} = \left\lfloor \frac{N-G-XY}{Y} \right\rfloor$。

现在我们就可以来做整除分块，对于每个 $X$ 判断最后的牛奶数量是否大于等于 $N$ 二分就行。

$\text{Time Complexity: }O(\sqrt{n} \log n)$。

$\text{AC Code: }$

```cpp
#include <iostream>
#include <fstream>

using namespace std;

long long _maxi = 0;
long long _dayNum = 0;
long long _limit = 0;
long long _res = 1;

bool Check (long long num) {
	
	long long back = 0; // G
	long long need = 0; // Y
	long long cur = 1; // d
	
	while (cur < _dayNum + 1) {
		need = (_maxi - back) / num; // i-th day milk need to return
		
		// return milk < M, get it out of the loop
		if (need < _limit) {
			break;
		}
		
		long long day = (_maxi - back - num * need) / need + 1; // (N-G-XY)/Y, because last day isn't in there, +1 
		
		// the day that be past > K
		if (day + cur > _dayNum) {
			day = _dayNum - cur + 1;
		}
		
		cur += day;
		back += need * day;
		
		// G >= N
		if (back > _maxi - 1) {
			return true;
		}
	}
	
	// last day return M everyday
	return (_dayNum - cur + 1) * _limit + back > _maxi - 1;
	
}

int main () {
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	cin >> _maxi >> _dayNum >> _limit;
    
    // binary search 
    
	long long left = 1;
	long long right = _maxi / _limit;
	
	while (left < right + 1) {
		long long mid = (left + right) >> 1;
		
		if (Check(mid)) {
			left = mid + 1;
			_res = mid;
		} 
		
		else {
			right = mid - 1;
		}
	}
   
	cout << _res << '\n';
   
	return 0;
	
} 
```

> P.S. 这题为什么评黄啊，整除分块模板题都是蓝题，这题紫左右吧（

---

## 作者：AgrumeStly (赞：2)



模拟赛第一题（

### 9pts

考虑暴力。

枚举 $x$，对于每个 $x$，模拟 $k$ 天，判断其是否合法，找出最大的 $x$。

时间复杂度：$O(n^2)$

### 36pts

考虑优化先前暴力算法。

我们不难发现当 $x$ 合法时，必然有合法 $x_1$，当且仅当 $x_1 < x$。  
故 $x$ 具有单调性，考虑二分答案。

对于 $x$，我们进行二分答案，对于每一个 $x$，我们对其进行判断是否合法。  
其中判断合法我们每一天逐一枚举，时间复杂度 $O(k)$。若合法，我们便再去寻找更大的合法 $x$。

时间复杂度：$O(n \log n)$

```cpp
bool check(int x) {
    int num = 0;
    for (int i = 1; i <= k; i++) {
        int y = (n - num) / x;
        if (y < m) y = m;
        num += y;
    }
    if (num >= n) return true;
    return false;
}

signed main() {
    n = read(), k = read(), m = read();
    int l = 1, r = n;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}
```

### 100pts

我们发现先前算法中，`check()` 函数效率为 $O(k)$，是显然超时的，我们考虑优化 `check()`。

对于每个 $y$，我们发现，当其中的 $x$ 固定时，存在 $z$ 使得 $y = \lfloor \dfrac{z}{x} \rfloor = \lfloor \dfrac{z + 1}{x} \rfloor = \dots = \lfloor \dfrac{z + a}{x} \rfloor$

故我们可以算出其中的 $a$，一次将 $a$ 个相同的 $y$ 算出。

我们假设当前欠了 $r$ 加仑，还有 $t$ 天的时间去还。  
那么我们对于 $r$，每次算出 $a$，判断其是否能在 $k$ 天中还完。  
我们知道若存在 $a$，则 $\lfloor \dfrac{z + (a - 1)}{x} \rfloor$ 依然等于 $\lfloor \dfrac{z + a}{x} \rfloor$，而 $a$ 天之后必然有 $\lfloor \dfrac{z + a}{x} \rfloor \le \lfloor \dfrac{z + a - 1}{x} \rfloor$。  
通过计算得出 $a = \lfloor \dfrac{r}{y} - x + 1 \rfloor$  
因为均为 `int`，故对于正整数 $a$ 直接 $a = \dfrac{r}{y} - x + 1$

当此时 $y <= m$ 时，因为题面说明 $y = m$，故可以直接算出剩余天数能还的量。

容易看出，当 $r \le 0$ 或者 $t == 0$ 时，就不需要进行计算。  
当 $t == 0$ 时，若 $r \le 0$，说明对于当前 $x$，能在规定时间内还完，故合法。

时间复杂度：$O(\sqrt{n} \log n)$

```cpp
#define int long long
int n, k, m, ans;

bool check(int x) {
    int r = n, t = k;
    while (r > 0 && t) {
        int y = r / x;
        if (y <= m) r -= t * m, t = 0;
        else {
            int a = min(r / y - x + 1, t);
            r -= y * a;
            t -= a;
        }
    }
    return r <= 0;
}

int erfen(int l, int r) {
    int num = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) num = mid, l = mid + 1;
        else r = mid - 1;
    }
    return num;
}

signed main() {
    n = read(), k = read(), m = read();
    int l = 1, r = n;
    ans = erfen(l, r);
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：神眷之樱花 (赞：1)

### 题外话
无语，提交了8次，只因为看错了 $k$ 和 $m$ 的输入顺序，唉，还是我太菜了。
### 正题
此题题意很容易理解，读完题应该就能想到二分答案的方法。

二分的耗时和判断的设计是有很大联系的，很显然如果只是普通的模拟的话，遇到特殊设计的数据或者大数据是肯定过不了的。所以我们必须要优化判断的方法。
### 二分边界的设计
基本的二分写法有以下两种，要想跑出正确的答案，必然要用严谨的写法。
```cpp
l=mid+1||r=mid,mid=(l+r)>>1
//或者是
l=mid||r=mid-1,mid=(l+r+1)>>1
```
第二种写法在其它题中能用来处理无解的情况，这里就不展开了。
### 判断的设计
第一种情况：

当某一天要还的牛奶不足 $m$ 时，那以后的每一天要还的牛奶一定都不足 $m$，出现这种情况时，我们就直接判断在剩下的天数内，每天还 $m$ 是否能还完就行了。

第二种情况：

当某一天要还的牛奶超过 $m$ 时，因为是向下取整的机制，所以我们不难发现会有连续几天还的牛奶是一样多的。这样我们就又能用乘法代替加法，减少循环次数，再一次剩下时间。因为本人还不太会用 $Markdown$ ,所以证明去参见别的大佬的吧。
### 代码
```cpp
#include<bits/stdc++.h>
#define QAQ while(1)
#define ll long long
using namespace std;
ll n,m,k;
bool judge(ll x)
{
	ll rest=n,day=k;
	QAQ
	{
		ll QWQ,y;
		y=rest/x;
		if(y<=m) return m*day>=rest;
		QWQ=rest/y-x+1;
		QWQ=min(QWQ,day);
		rest-=QWQ*y;
		day-=QWQ;
		if(rest<=0)return true;
		if(day==0)return false;
	}
}
int main()
{
	cin>>n>>k>>m;
	ll l=1,r=n,mid;
	while(l<r)
	{
		mid=(l+r+1)>>1;
		if(judge(mid)) l=mid;
		else r=mid-1;
	}
	cout<<l;
	return 0;
}
```


---

## 作者：zzw4257 (赞：1)

> 求最大的$X$使得重复这个过程$K$次使得$ans\geqslant N$
>
> ```cpp
> dlt=max(res/X,m),res-=dlt,ans+=dlt
> ```

考虑二分答案$X$

对于判定其实有两个**阶段**

- 第一个阶段$dlt>m$考虑整除分块(分子版本的)，我们观察需要$res$减多少次$div=\lfloor\frac{res}{X}\rfloor$,$\lfloor\frac{res'}{X}\rfloor$才会变化

  对$\lfloor\frac{res}{X}\rfloor$可以找到最小的$tim$使得$\lfloor\frac{res-tim\lfloor\frac{res}{X}\rfloor}{X}\rfloor=\lfloor\frac{res}{X}\rfloor-1$

  可以轻易知道答案是$tim=\lfloor\frac{\frac{res}{X}}{X}\rfloor-X+1$

  证明可以列不等式证明，或者感性理解

- 第二个阶段$dlt=m$可以直接算出次数

```cpp
inline char Check(ll x){
	ll div,t,now=n,cnt=k;
	while(cnt&&now>0)(div=now/x>m)?t=min(now/div-x+1,cnt),now-=t*div,cnt-=t:now-=cnt*m,cnt=0;
	return now<=0;
}
```

---

## 作者：伟大的王夫子 (赞：1)

很明显，我们这道题要二分这个$X$

但是，如果就二分的时候暴力加，那么显然会超时。所以，按照数论分块的思想，我们考虑当现在时$\lfloor \frac{N-G}{X}\rfloor (=m)$ 假设加上这次最多还会有$y$次满足Bessie给的牛奶的数量还是这个值，那么$\lfloor \frac{N -G - my}{X} \rfloor = m $

$(m + 1)X >N - G - my \ge mX$

$N-G-mX \ge my > N - G - (m + 1)X$

所以$y_{max}=\lfloor \frac{N - G - mX}{m} \rfloor$

然后另答案加上$(y + 1) \times m$

即可。

还得特判一下天数超过$K$的情况

二分下界为$1$,上界为$\lfloor \frac{N}{M} \rfloor$

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, t, m;
bool valid(ll x) {
	ll g = 0, s = t;
	while (s > 0) {
		ll k = (n - g) / x;
		if (k <= m) {
			g += s * m;
			return g >= n;
		}
		ll y = (n - g - x * k) / k;//计算相同天数
		if (y + 1 <= s) {
			s -= y + 1;
			g += (y + 1) * k;
		} else {
			g += s * k;
			break;//特判
		}
		if (g >= n) return 1;
	}
	return 0;
}
int main() {
	cin >> n >> t >> m;
	ll l = 1, r = n / m, ans;
	while (l <= r) {
		ll mid = (l + r) >> 1;
		if (valid(mid)) ans = mid, l = mid + 1;
		else r = mid - 1;
	}
	cout << ans;
}
```

注意：一定一定要开long long

---

## 作者：small_john (赞：0)

## 分析

二分+分块。

普通的二分 TLE 就在 ok 函数中。

```cpp
bool ok(long long x)
{
	long long sum = 0;
	for(long long i = 1;i<=k;i++)
	{
		int s = (n-sum)/x;
		if(s<=m)
		{
			sum+=m*(k-i+1);
			break;
		}
		sum+=s;
	}
	return sum>=n;
}
```

所以就可以用分块来优化。

我们知道，一定有一段时间还了 $y$ 加仑，不妨把这个天数直接求出来。

设现在还的牛奶有 $sum$ 加仑，那么对于每个合法的 $sum$，有 $y=\dfrac{n-sum} {x}$，而直到 $x\times y$ 的 $sum$，都会还 $y$ 加仑，所以共还 $\dfrac {n-sum-x\times y}{y+1}$ 天。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,k,m,l,r,ans;
bool ok(ll x)
{
	ll sum = 0;
	for(ll i = 0;i<k;)
	{
		ll y = (n-sum)/x;
		if(y<=m)
			return (sum+(k-i)*m)>=n;
		ll add = (n-sum-x*y)/y+1;
		sum+=y*add;
		i+=add;
 	}
	return sum>=n;
}
int main()
{
	cin>>n>>k>>m;
	l = 1,r = n;
	while(l<=r)
	{
		ll mid = (l+r)/2;
		if(ok(mid))
			ans = mid,l = mid+1;
		else r = mid-1;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：_szs9601 (赞：0)

#### 思路
很明显，这是一道二分题。但如果我们直接用暴力判断，肯定是会超时的。但是我们发现，当 $X$ 很大时，会有多天要还的牛奶是相等的。所以我们将这些天要还的牛奶算在一起，用乘法代替加法，减少循环次数，进行优化。
#### 代码
```cpp
#include<bits/stdc++.h>
#define LL long long//记得开long long
using namespace std;
LL n,k,m,t,w,mid,ans;
bool pd(LL x){
	LL s=n,y,t;
	for(LL i=1;i<=k;){
		y=s/x;
		if(y<=m) return s-(k-i+1)*m<=0;//如果应该还的数量<=m,则之后每天都还m
		t=min(k-i+1,s%x/y+1);//t为要还相同牛奶天数
		s-=y*t;//乘法代替加法
		i+=t;//直接跳过t天
		if(s<=0) return 1;//牛奶还完了
	}
	return 0;
}
int main(){
	scanf("%lld%lld%lld",&n,&k,&m);
	t=1;w=1e13;
	while(t<=w){
		mid=(t+w)>>1;
		if(pd(mid)) ans=mid,t=mid+1;
		else w=mid-1;
	}//二分
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Ezis (赞：0)

首先我们想到的肯定是一个**超时**的暴力算法。

但发现题目要求查找 $x$ 的最大值，所以可以想到用**二分**去优化。

每次判断当前 $mid$ 是否符合题目要求。

#### 二分模板：
```cpp
while(l<r){
   mid=(l+r+1)/2;
   if(check(mid))
      l=mid;
   else
      r=mid-1;
}
```


这里只需要将 $check$ 函数改一下即可。

在 $check$ 函数中，我们需要统计当前需要求的 $mid$ 是否能满足在 $k$ 天内还到 $n$ 加仑牛奶。

最后的答案为查找到的 $l$ 。

**具体代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
int n,k,m,l,r,mid;
bool check(int mid){
	int cnt=0;
	int i=k;
	while(i>0&&cnt<n){
		int y=(n-cnt)/mid;
		if(y<m){
			if((n-cnt+m-1)/m<=i)
				return true;
			else	
				return false;
		}
		int c2=n-mid*y;
		int day=min((c2-cnt)/y+1,i);
		cnt+=y*day;
		i-=day;	
	}
	if(cnt>=n)
		return true;
	return false;
}
signed main(){
	scanf("%lld%lld%lld",&n,&k,&m);
	l=1;
	r=1000000000000;
	while(l<r){
		mid=(l+r+1)/2;
		if(check(mid))
			l=mid;
		else
			r=mid-1;
	}
	printf("%lld",l);
	return 0;
}
```



---

