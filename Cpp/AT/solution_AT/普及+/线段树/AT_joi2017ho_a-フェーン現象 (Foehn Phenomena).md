# フェーン現象 (Foehn Phenomena)

## 题目描述

### 题目简述

你知道$N+1$个地点的海拔$A_i$,编号为$0 \dots N$,有风从$0$吹向$N$,想让你求出地点$N$的风的温度.

保证$A_0=0$

规则：
- 如果$A_i=A_{i+1}$风的温度不变.
- 如果$A_i>A_{i+1}$由于海拔降低,风的温度会上升$(A_i-A_{i+1})\times T$度
- 如果$A_i<A_{i+1}$由于海拔升高,风的温度会下降$(A_{i+1}-A_i)\times S$度

## 样例 #1

### 输入

```
3 5 1 2
0
4
1
8
1 2 2
1 1 -2
2 3 5
1 2 -1
1 3 5```

### 输出

```
-5
-7
-13
-13
-18```

## 样例 #2

### 输入

```
2 2 5 5
0
6
-1
1 1 4
1 2 8```

### 输出

```
5
-35```

## 样例 #3

### 输入

```
7 8 8 13
0
4
-9
4
-2
3
10
-9
1 4 8
3 5 -2
3 3 9
1 7 4
3 5 -1
5 6 3
4 4 9
6 7 -10```

### 输出

```
277
277
322
290
290
290
290
370```

# 题解

## 作者：yangrunze (赞：25)

要做这个题，首先我们要了解一个概念：**差分**

差分是个啥？好多同学肯定一听这高大上的名字就晕了，其实差分这东西，你也不用想得太神秘，把第二个字去掉，这差分其实就是个“差”

那具体是什么样的“差”呢？就是**数组元素中，每两项之间的差**（特别的，差分数组的第一项原数组的第一项自己）

栗子：
```
原数组：  5 2 0 1 3 1 4
每两项的差： 2-5=-3  0-2=-2  1-0=1  3-1=2  1-3=-2  4-1=3 
差分数组：5 -3 -2 1 2 -2 3
```
话说回来，这题到底跟这差分有啥关系呢？？先说这题的核心操作

> ......接下来的$Q$行中第$j$行$(1\leq j\leq Q)$包括三个被空格隔开的整数$L_j,R_j,X_j$.这表示第$j$天地壳运动使**地点$L_j$ 到地点$R_j$中这些地点的海拔变化了$X_j$**

emmmmm......**区间修改**

>......输出$Q$行,第$j$行的输出代表第$j$天地壳运动后$N$**位置的风的温度**

emmmmm......**查询操作**

这两个词一出现，大家有没有条件反射般地想到什么东西呢？也许做过[树状数组2](https://www.luogu.com.cn/problem/P3368)的同志们可能已经晓得了：**我们当初用树状数组进行区间修改和单点查询操作的时候，存在树状数组里的值的就是数组元素之间的差分！**

~~（说句闲话，我一开始想到这里本来想用树状数组做来着，结果怎么写也写不出来，后来才发现这题更简单——压根用不着树状数组！）~~

那用差分进行区间修改操作的时候，好处都有啥？咱这就讲：

（如果你已经AC了树状数组2或已经了解过这部分内容，你就可以跳过啦！）

咱还是从一个栗子开始：

将数组5 2 0 1 3 1 4，将2~5区间内的每个数加上6

加上之后，求出差分，和原数组对比一下：

|  |  |
| :----------: | :----------: |
|原数组  |5 2 0 1 3 1 4  |
|修改后的数组|5 **8** **6** **7** **9** 1 4|
|原差分数组  | 5 -3 -2 1 2 -2 3|
|修改后的差分数组|5 **3** -2 1 2 **-8** 3|

简直“没有对比就没有伤害”啊，如果直接在原数组上动工，那就要修改好多好多个，而**修改差分数组**，只需要修改**两个**就行啦！

为什么呢？这一切的功劳就在于我们数学课本里**等式的性质**：**如果两个数加上或减去一个数，等式仍然成立**

如果$a=b$，那么$a \pm c=b \pm c$

所以如果当两个数$a$,$b$同时加上一个数$c$的时候，**他们的差是不变的**，差分只会在头尾两端改变（这就不用推导了吧）

现在明白差分为啥有这么神奇的威力了吧！并且，经过大量的举例和推导，我们可以得到差分变化的规律是这样的：
```cpp
	a[l]+=k;
	a[r+1]-=k;
```
不仅如此题目中**温度的变化也跟海拔差有关**，所以差分当然是这个题的最好选择啦！

那这样的话，这个题的思路就有啦！废话不多说，先上代码！

等会，在放代码之前，咱先来介绍一下这个函数（逃）：
```cpp
int read(){
	char c=getchar();
	int f=1,x=0;
	while(c<'0'||c>'9'){
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+(c^'0');
		c=getchar();
	}
	return x*f;
}
```
没错这就是大名鼎鼎的**读入优化**！（俗称“快读”）

因为刚学会嘛，所以顺便在这篇题解里给大家讲讲这玩意怎么写（会快读的可以跳过啦）：

大家都知道，scanf比cin快得可不是一点半点，（亲测：cin
TLE了五六个点，scanf全A）那有比scanf更快的吗？

当然有喽！就是大名鼎鼎的**getchar()**

所以这个读入优化的原理就是每次**把数据以字符的形式读进去再转化成int类型**!

明白了这一点，就可以知道怎么搞这个东西了：

```cpp
int read(){
	char c=getchar(); //先读入一个字符
 	int f=1,x=0;//f是这个数的符号（正负），x是这个数
	while(c<'0'||c>'9'){  //如果不是数字的话（就是负号呗）
		if(c=='-')
			f=-1;  //这个数是负数了
		c=getchar();
	}
	while(c>='0'&&c<='9'){ //是数字就接着往下读
		x=(x<<1)+(x<<3)+(c^'0'); 
//其实就相当于x*10+c-'0'，x<<n是指x*2的n次方，x*2+x*8不就是x*10嘛，至于c^0，实际上就是c-'0'，用二进制位运算可以加快速度
		c=getchar(); 
	}
	return x*f; //返回读入的x*数的符号f
}
```

这样的话我们就可以安心写代码啦！

```
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;  //十年OI一场空，不开 long long见祖宗
ll a[4000005];//差分数组
ll n,q,s,t;//不解释
inline ll read(){  
//快读！（代码里的inline和下文for循环里的“register”一样，只是优化用的，完全可以去掉）
	char c=getchar();
	int f=1;
	ll x=0;
	while(c<'0'||c>'9'){
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+(c^'0');
		c=getchar();
	}
	return x*f;
}
ll temp(ll x){//这个函数是来求变化温度的，根据题意模拟即可
	if(x>=0)
	return -x*s;
	else return -x*t;  //因为海拔方向和温度方向相反，所以要加个负号
}
int main(){
	n=read();q=read();s=read();t=read(); //快读，实在不会的可以用scanf代替
	ll last=0; //last用来存储上一个数（不理解？看下面）
	for(register int i=0;i<=n;i++){//注意这题是从0开始存
		ll k=read();  //读入当前数据
		a[i]=k-last;  //数组中存储两个元素的差（差分）
		last=k;		//更新last
	}
	for(register int i=1;i<=q;i++){ 
		ll l=read(),r=read(),k=read();//没啥好说的
		a[l]+=k;  //根据前面得到的结论进行差分数组的修改
		a[r+1]-=k;
		ll ans=0;  //记录最后输出的答案
		for(register int j=0;j<=n;j++)
			ans+=temp(a[j]);  //对每个海拔的变化值（差分）求温度，加起来，输出，perfect!
		printf("%lld\n",ans);
	}
	return 0;
}
```
交上去一看......葡萄美酒夜光杯，T了一堆又一堆

为啥呢？我分析了一下：每一次修改时，都要遍历整个数组，太慢！

那咋办呢？？后来我（~~通过看题解~~）发现，反正每次修改就需要改两个数，所以我们只需要**把变化的高度求出来更新在ans变量里**就好啦！

嗯，这思路不错嘛，还有一点要注意的：**当r=n的时候，我们不需要更新差分数组的值**，记住了这几点，我们把代码修改成这样

```
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
ll a[4000005];
ll n,q,s,t;
ll ans=0;
inline ll read(){
	char c=getchar();
	int f=1;
	ll x=0;
	while(c<'0'||c>'9'){
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+(c^'0');
		c=getchar();
	}
	return x*f;
}
ll temp(ll x){
	if(x>=0)
	return -x*s;
	else return -x*t;
}
int main(){
	n=read();q=read();s=read();t=read();
	ll last=0;
	for(register int i=0;i<=n;i++){
		ll k=read();
		a[i]=k-last;
		last=k;//到这里和前面都一样
		ans+=temp(a[i]);//注意第一次输入就可以顺道把没有经过地壳运动的初始ans记录下来哦！
	}
	for(register int i=1;i<=q;i++){
		ll l=read(),r=read(),k=read();
 //在修改差分数组的时候，顺便进行ans的更新		
  		ans-=temp(a[l]); //旧的不去，新的不来！
		a[l]+=k;
		ans+=temp(a[l]);//更新后的值再加到ANS里面
		if(r<n){ //特判r要小于n
			ans-=temp(a[r+1]);//对右端点也如法炮制
			a[r+1]-=k;
			ans+=temp(a[r+1]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```
于是就愉快的AC了

好了总结一下：这次我们学了一个新技能，叫**差分**，它是**数组里每两个元素之间的差**，在**区间修改**里可以起到大作用！最后还要注意**时间的优化**哦！

The End!!!

---

## 作者：顾z (赞：15)

# [顾](https://www.luogu.org/blog/RPdreamer/#)[z](https://www.cnblogs.com/-guz/)

~~你没有发现两个字里的blog都不一样嘛~~ qwq

原题为「JOI 2017 Final」焚风现象

题解的话如果你们看得懂日文就去看看 -->[https://www.ioi-jp.org/joi/2016/2017-ho/2017-ho-t1-review.pdf](https://www.ioi-jp.org/joi/2016/2017-ho/2017-ho-t1-review.pdf)

### 分析

首先,这是一个**差分模板题**,不过应该不是很容易看出来.

涉及到了**区间修改与单点查询**.(我相信有人会写数据结构的.

但是这里的单点查询就是一个固定的点$n$。

#### 首先考虑为什么可以差分去做?

　~~题目中的描述就暗示着我们进行差分啊.~~

首先我们发现了题目中的这一句话

> 风的温度随海拔升降而变化。

而,每个地点的海拔已知,所以我们可以在输入的时候求出每个位置的海拔差.

#### 做法

根据海拔差,我们又可以求出每个位置的温度.由于$n$位置不会变,且一直为最后一个位置.

所以我们可以累加$ans$.(因为最后一个位置$n$永远不会变。

而且考虑到某一段区间的海拔变化,相对位置不会变,我们只需要考虑从起始位置$l$的温度变化,后面到达$r$的温度就随之变化.

这里需要注意的位置就是当$r==n$的时候,是不需要变化$r+1$位置的海拔与温度的.

即我们的$ans$是不需要改变的.而改变的话,需要考虑相对高度的变化.我相信大家能懂的 qwq.

### 代码

```c++
#include<cstdio>
#include<cstring>
#include<cctype>
#define N 200005
#define R register
using namespace std;
long long n,q,s,t;
long long A[N],last,ans;
inline void in(long long &x)
{
	int f=1;x=0;char s=getchar();
	while(!isdigit(s)){if(s=='-')f=-1;s=getchar();}
	while(isdigit(s)){x=x*10+s-'0';s=getchar();}
	x*=f;
}
inline long long get(long long x)
{
	return  x > 0 ? -(x*s) : -(x*t) ; 
}
int main()
{
	//freopen("cure.in","r",stdin);
 	//freopen("cure.out","w",stdout);
	in(n),in(q),in(s),in(t);
	in(last);
	for(R int i=1;i<=n;i++)
	{
		R long long x;
		in(x);
		A[i]=x-last;
		last=x;
		ans+=get(A[i]);
	}
	for(R long long x,y,z;q;q--)
	{
		in(x),in(y),in(z);
		ans-=get(A[x]);
		A[x]+=z;
		ans+=get(A[x]);
		if(y!=n) ans-=get(A[y+1]),A[y+1]-=z,ans+=get(A[y+1]);
		printf("%lld\n",ans);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
```

还有标程~~很神奇~~

```c++
#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;
ll s1,s2;
ll dif[300001];
ll get(ll t)
{
	if(t>0)return -s1*t;
	else return -s2*t;
}
int main()
{
	int num,query;
	scanf("%d%d%lld%lld",&num,&query,&s1,&s2);
	vector<int>v;
	for(int i=0;i<=num;i++)
	{
		int z;
		scanf("%d",&z);
		v.push_back(z);
	}
	ll ans=0;
	for(int i=0;i<num;i++)
	{
		dif[i]=v[i+1]-v[i];
		ans+=get(dif[i]);
	}
	for(int i=0;i<query;i++)
	{
		int za,zb,zc;
		scanf("%d%d%d",&za,&zb,&zc);
		ans-=get(dif[za-1]);
		dif[za-1]+=zc;
		ans+=get(dif[za-1]);
		if(zb!=num)
		{
			ans-=get(dif[zb]);
			dif[zb]-=zc;
			ans+=get(dif[zb]);
		}
		printf("%lld\n",ans);
	}
}

```

---

## 作者：Viktley (赞：4)

**Ps:**
窝本想写树状数组的，但~~还是菜~~

---

**思路:**

数据是比较大的，那么暴力求解显然不可能。

我们考虑用差分优化。

将每一次的 Q 看成是区间修改，即（$p_l+x,p_{r+1}-x$）。

最后我们将 ($0-n$) 的区间按上升降温，

下降升温的题目要求加一个总，最后就是答案 。

```cpp
for(register int i=1;i<=q;i++){ 
        scanf("%lld%lld%lld", &l, &r, &k);
        a[l]+=k;
        a[r+1]-=k;
        ll ans=0;
        for(int j=0;j<=n;j++)ans+=solve(a[j]);  //solve()即依题意处理函数（上升降温，下降升温）
        printf("%lld\n",ans);
    }
```
但是这交上去还是会TLE。

考虑对ans进行差分处理。

我回顾的以前的题，发现有一个好东西。

差分例题中最后有一个区间求和的问题。

于是大家考虑把ans看成是一个区间和 （0~n） ,

再以solve()的值为修改值，进行差分。

形象理解一下ans为一个有 n + 1 个数的区间。

==最后提醒一下，long long卡死了我所有的点==

```cpp
#include <cstdio>
#include <iostream>
#define ll long long
using namespace std;
const ll N = 2e5 + 10;
ll n, q, s, t, x, y, z, ans, a[N], p[N];
ll solve(ll x)
{
	if(x >= 0) return x * s;
	return x * t;
}
int main()
{
	scanf("%lld%lld%lld%lld", &n, &q, &s, &t);
	for(ll i = 0; i <= n; i++)
		scanf("%lld", &a[i]), p[i] = a[i] - a[i - 1], ans -= solve(p[i]);
	while(q--)
	{
		scanf("%lld%lld%lld", &x, &y, &z);
		ans += solve(p[x]), p[x]+= z, ans -= solve(p[x]);
		if(y < n) ans += solve(p[y + 1]), p[y + 1]  -= z, ans -= solve(p[y + 1]);
		printf("%lld\n", ans); 
	}
	return 0;
}
```


---

## 作者：KEBrantily (赞：3)

差分 + 纯特判过题。

~~看了一下大概没人像我这么 zz 吧。~~

## Description

给定一个序列 $a_{1\dots n }$，每次取一段区间对其中所有的数加减一个同样的值，然后按题目所给的条件进行计算。

修改若干次，前面的修改对于后面的计算会造成影响，求出每一次修改后的答案。

## Solution

看到区间修改，发现 $l_i,r_i\le n\le 200,000$，暴力修改不可行。可以考虑差分。

差分后，发现 $q\le 200,000$，无法进行 $\Theta(nq)$ 的操作。其中 $q$ 次循环是不能省的，所以考虑换个方法统计区间的答案。

结合题目的条件，每个对答案的贡献都是基于 $a_i$ 与 $a_{i+1}$ 的差值大小。而 $a_{i+1}-a_i$ 又是我们已经处理完的差分数组中的元素。

假设差分后的数组为 $c$，则初始序列的答案为 

$$\sum_{i=1}^{n} [-c_i\times T(c_i<0)]-\sum_{i=1}^n [c_i\times S(c_i>0)]$$

而对于每一次操作 $(l,r,k)$，可以发现，修改之后对答案有影响的位置只有 $l$ 和 $r$ 两个位置，而其他的值还是不变的。

所以对于每次操作 $(l,r,k)$，我们只需要在上一次的答案基础上修改 $l,r$ 两个位置的贡献即可。

修改 $l,r$ 处的贡献，就是比较修改前后 $c_{l},c_{r}$ 与 $0$ 的大小关系，然后按题目所给规则计算即可。具体修改方式不好阐述，但是比较简单，见代码即可。

时间复杂度 $\Theta(n)$。

## Code

```cpp
#include<queue>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define rr register 
#define maxn 20000010
#define INF 0x3f3f3f3f
#define LL long long
#define Mod 19260817
#define int long long
using namespace std;

int n,q,s,t,now,ans1,ans2;
int a[maxn],c[maxn];

inline int read(){
    rr int s=0,w=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=(s<<1)+(s<<3)+ch-'0',ch=getchar();
    return s*w;
}

signed main(){
    n=read();q=read();
    s=read();t=read();a[0]=read();
    for(int i=1;i<=n;i++){
        c[i]=((a[i]=read())-a[i-1]);
        if(c[i]>0)ans1+=c[i];if(c[i]<0)ans2+=c[i];
    }
    ans1*=-s;ans2*=-t;
    //ans1 统计升温，ans2 统计降温，则答案为 ans1 + ans2; 
    for(int i=1,fr,to,val;i<=q;i++){
        fr=read();to=read();val=read();
        c[fr]+=val;c[to+1]-=val;//差分，则差分前的两个数分别是 c[fr] - val 和 c[to + 1] + val; 
        if(c[fr]-val==0){
            if(c[fr]>0) ans1-=val*s;
            if(c[fr]<0) ans2-=val*t;
        }
        if(c[fr]-val>0){
            if(c[fr]>=0) ans1-=val*s;
            else if(c[fr]<0){
                ans1+=(c[fr]-val)*s;
                ans2-=c[fr]*t;
            }
        }
        if(c[fr]-val<0){
            if(c[fr]<=0) ans2-=val*t;
            else if(c[fr]>0){
                ans2+=(c[fr]-val)*t;
                ans1-=c[fr]*s;
            }
        }
        
        if(to+1<=n){//差分减的时候可能会超出 n 的范围，此时不用计算它的贡献; 
        //下面的判断和上面是一样的 
            if(c[to+1]+val==0){
                if(c[to+1]>0) ans1+=val*s;
                if(c[to+1]<0) ans2+=val*t;
            }
            
            if(c[to+1]+val>0){
                if(c[to+1]>=0) ans1+=val*s;
                else if(c[to+1]<0){
                    ans1+=(c[to+1]+val)*s;
                    ans2-=c[to+1]*t;
                }
            }
            if(c[to+1]+val<0){
                if(c[to+1]<=0) ans2+=val*t;
                else if(c[to+1]>0){
                    ans2+=(c[to+1]+val)*t;
                    ans1-=c[to+1]*s;
                }
            }
        }
        printf("%lld\n",ans2+ans1);
    }
    return 0;
}
```


---

## 作者：白鲟 (赞：3)

## 前言
发篇题解庆祝一下 AC 这道在我任务计划里躺了一年的题。若显示出现问题请到[博客](https://www.luogu.com.cn/blog/bzlz-zdx/solution-at2442)食用。  
## 题意简述
（吐槽一下题目难以简述的事实）  

给出一个序列 $a_i$ 与函数 $f(x)$，进行多次区间修改，并在每次修改后求出 $\sum_{i=1}^{n}f(i)$ 的值。  

其中函数 $f(x)$ 满足如下形式：
$$
f(x)=
\begin{cases} 
-s(a_x-a_{x-1}) & a_x > a_{x-1}\\
0 & a_x=a_{x-1}\\
-t(a_x-a_{x-1}) & a_x < a_{x-1}
\end{cases}
$$  

（好像简述之后又变复杂了）
## 题目分析
观察函数形式，我们可以发现 $f(x)$ 的值只与 $a_x-a_{x-1}$ 的值有关。因此，很容易想到保存相邻两项的差值序列，记作 $delta_i$。这也就是原序列的差分序列。而原函数则可以简记如下：
$$
f(x)=
\begin{cases} 
-s \cdot delta_x & delta_x>0\\
0 & delta_x=0\\
-t \cdot delta_x & delta_x<0
\end{cases}
$$  
我们知道，运用差分思想，区间修改的时间复杂度仅为 $\operatorname{O}(1)$。问题的关键是求出每次修改所有后 $f(i)$ 的和。由于实际上在差分序列中每次修改仅改动两项，我们可以想到在上一次的答案的基础上略作修改便可以得到这一次的答案。  

接下来就到了愉快（并不）的推式子时间。对于在差分序列上进行的每一次修改，我们需要用较小的时间复杂度统计出它对答案的贡献。对于修改点 $i$，若修改后的 $delta_i'<0$，则可能是两种情况： 修改前 $delta_i<0$ 或修改前的 $delta_i \ge 0$。对于第一种情况，容易得知对答案的贡献为 $t(delta_i-delta_i')$；而第二种情况则要麻烦一些，对于 $delta_i-delta_i'$ 间的部分需要分成两段进行统计，因为大于 $0$ 的部分贡献每段是 $s$，但小于 $0$ 的是 $t$，合起来应该是 $-t \cdot delta_i'+s \cdot delta_i$。同理可推出 $delta_i' \ge 0$ 的情况。  

整理推出的式子可以得到每一次修改后的 $ans'$ 与修改前 $ans$ 的关系（为什么我整理得这么复杂啊）：
$$
ans'=ans+
\begin{cases} 
s \cdot (\max(delta_x,0)-delta_x')+t \cdot \min(delta_x,0) & delta_x' \ge 0\\
t \cdot (\min(delta_x,0)-delta_x')+s \cdot \max(delta_x,0) & delta_x'<0
\end{cases}
$$
## 代码
注意开`long long`；注意输入的坐标有 $n+1$ 个；注意如果修改的右端点为 $n$ 则对差分序列的第 $n+1$ 项修改时不会对答案产生贡献。
```cpp
#include<algorithm>
#include<cstdio>
using namespace std;
long long n,q,s,t,l,r,x,sum,a[200002],delta[200002];
inline long long f(long long x,long long y)
{
	return y>0ll?((max(x,0ll)-y)*s+min(x,0ll)*t):((min(x,0ll)-y)*t+max(x,0ll)*s);
}
signed main()
{
	scanf("%lld%lld%lld%lld%*lld",&n,&q,&s,&t);
	for(long long i=1;i<=n;++i)
	{
		scanf("%lld",&a[i]);
		delta[i]=a[i]-a[i-1];
		sum-=delta[i]>0ll?delta[i]*s:delta[i]*t;
	}
	while(q--)
	{
		scanf("%lld%lld%lld",&l,&r,&x);
		long long t1=delta[l],t2=delta[r+1];
		delta[l]+=x;
		delta[r+1]-=x;
		sum+=f(t1,delta[l])+(n!=r)*f(t2,delta[r+1]);
		printf("%lld\n",sum);
	}
	return 0;
}
```

---

## 作者：tcswuzb (赞：2)

~~这道题目貌似可以使用裸差分来做~~

## 题意分析

这道题其实就是

每一次都把一座山峰升高或者降低 

然后问你经过的温度到达最后是什么样子

![dslsdkf](https://i.loli.net/2018/10/09/5bbc22df51969.png)

大概就是这样

首先 我们就可以发现

区间内的山峰意一起增长的话 区间内相对高度不变

只有区间边界上相对高度发生变化

所以使用树状数组维护差分 

不才用了两个树状数组 

一个维护高度 一个维护温度

注意相对高度变化时 由于存在s以及t

所以有四种变化情况 分开讨论

![sdf](https://i.loli.net/2018/10/09/5bbc2581867cd.png)

1.原先比其低后来比其高

2.原先比起低后来还是比其低

3.原先比其高后来还是比其高

4.原先比其高后来比其低

# CODE:

```cpp
#pragma GCC optimize(3)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#include<stack>
#include<list>
#include<set>
#include<deque>
#include<vector>
#include<ctime>
#define int long long
#define M 2000008
#define inf 0x7fffffff
#define IL inline
#define D double
#define R register
using namespace std;
template<typename T>void read(T &a)
{
    T x=0,f=1;char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-')f=0;ch=getchar();
    }
    while(isdigit(ch))
    {
        x=(x<<1)+(x<<3)+ch-'0';ch=getchar();
    }
    a=f?x:-x;
}
int n,q,s,t;
int tre1[M],num[M],tre2[M];
IL void add(int *tre,int ak,int x)
{
    for(;x<=n+1;x+=(x&-x)) tre[x]+=ak;
}
IL int qury(int *tre,int x)
{
    int sum=0;
    for(;x;x-=(x&-x)) sum+=tre[x];
    return sum;
}
signed main()
{
//	freopen("cure.in","r",stdin);
//	freopen("cure.out","w",stdout);		
    read(n);read(q);read(s);read(t);
    for(R int i=1;i<=n+1;++i) read(num[i]);
    for(R int i=1;i<=n+1;++i)
    {
        add(tre1,num[i]-num[i-1],i);
        if(num[i-1]<num[i]) add(tre2,-abs(num[i]-num[i-1])*s,i);
        else add(tre2,abs(num[i]-num[i-1])*t,i);
    }
//	printf("hi %lld\n",qury(tre1,n+1));
//	printf("ti %lld\n",qury(tre2,n+1));
    while(q--)
    {
        int le,ri,x;
        read(le);read(ri);read(x);
        ++le;++ri;
        int hx,hy,hi,hj;
        hx=qury(tre1,le-1);
        hy=qury(tre1,le);
        hi=qury(tre1,ri);
        hj=qury(tre1,ri+1);
        add(tre1,x,le);add(tre1,-x,ri+1);
        if(hx<=hy && hx<=hy+x)
        {
            add(tre2,abs(hx-hy)*s,le);
            add(tre2,-abs(hy+x-hx)*s,le);
        }
        else if(hx>=hy && hx>=hy+x)
        {
            add(tre2,-abs(hx-hy)*t,le);
            add(tre2,abs(hy+x-hx)*t,le);
        }
        else if(hx>=hy && hx<=hy+x)
        {
            add(tre2,-abs(hx-hy)*t,le);
            add(tre2,-abs(hy+x-hx)*s,le);
        }
        else if(hx<=hy && hx>=hy+x)
        {
            add(tre2,abs(hx-hy)*s,le);
            add(tre2,abs(hy+x-hx)*t,le);
        }
        
        if(hi<=hj && hi+x<=hj)
        {
            add(tre2,abs(hj-hi)*s,ri+1);
            add(tre2,-abs(hi+x-hj)*s,ri+1);	
        }
        else if(hi>=hj && hi+x>=hj)
        {
            add(tre2,-abs(hi-hj)*t,ri+1);
            add(tre2,abs(hi+x-hj)*t,ri+1);		
        }
        else if(hi<=hj && hi+x>=hj)
        {
            add(tre2,abs(hj-hi)*s,ri+1);
            add(tre2,abs(hi+x-hj)*t,ri+1);			
        }
        else if(hi>=hj && hi+x<=hj)
        {
            add(tre2,-abs(hi-hj)*t,ri+1);
            add(tre2,-abs(hi+x-hj)*s,ri+1);		
        }
        
        printf("%lld\n",qury(tre2,n+1));
    }
    return (2333==233333);
}


```

# _NOIP 2018 RP++_

---

## 作者：漠寒 (赞：0)

## 分析

这是一道典型的差分题。差分指的就是两项之间的差，即 $b_i=a_i-a_{i-1}$，而题目中影响温度变化的正是这一值。

所以我们就可以直接用 $b$ 数组来直接判断三个规则来做这道题，那修改呢？这就是差分最重要的一个性质，修改一个片段只会影响差分数组内的两个值，其它修改的位置，它和它前面都修改了同样一个值，所以数值不变，因此每次修改单独将变化的两值拿出来更改答案即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline void read(int &res){
	res=0;
	int f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')res=(res<<1)+(res<<3)+c-48,c=getchar();
	res*=f;
}
int n,m;
int s,t;
int ans;
int l,r,x;
int a[200005],b[200005];
signed main()
{
	read(n);read(m);read(s);read(t);
	read(a[0]);
	for(int i=1;i<=n;i++){
		read(a[i]);
		b[i]=a[i]-a[i-1];
		if(b[i]>0)ans-=b[i]*s;//规则3
		else ans+=-b[i]*t;//规则2 
	}
	for(int i=1;i<=m;i++){
		read(l);read(r);read(x);
		if(b[l]>0)ans+=b[l]*s;
		else ans-=-b[l]*t;//先将历史答案改掉 
		b[l]+=x;//a[l]加了，比l-1在原来基础上更多了x 
		if(b[l]>0)ans-=b[l]*s;
		else ans+=-b[l]*t;
		if(r==n){//特判，因为风吹到n+1和JOI先生并没有关系 
			printf("%lld\n",ans);
			continue;
		}
		if(b[r+1]>0)ans+=b[r+1]*s;
		else ans-=-b[r+1]*t;
		b[r+1]-=x;//a[r]加了，a[r+1]就比a[r]在原来基础上更少了x 
		if(b[r+1]>0)ans-=b[r+1]*s;
		else ans+=-b[r+1]*t;
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：Vermouth_1412 (赞：0)

### 裸的差分？
### 我感觉是裸的线段树
#### 海拔的上升与下降就区间修改呗
#### 至于答案吗,单点查询一下就行了，这不就是线段树模板1
#### ~~是不是特别的呆啊~~，其实就是这样，常数呢，问题不大，只要不是老爷机都能过


代码如下：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rint register int
#define ll long long
#define lson rec<<1,l,mid
#define rson rec<<1|1,mid+1,r
using namespace std;
const int mx=200005;
int n,m,x,y,nt;
ll ans,s,t;
ll h[mx],ad[mx<<2];
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48;ch=getchar();}
    return x*f;
}
inline void pushdown(int rec)
{
    if(ad[rec]){
        ad[rec<<1]+=ad[rec];ad[rec<<1|1]+=ad[rec];ad[rec]=0;
    }
}
void modify(int rec,int l,int r)
{
    if(x<=l&&y>=r){
        ad[rec]+=nt;return;
    }
    int mid=(l+r)>>1;pushdown(rec);
    if(x<=mid) modify(lson);
    if(y>mid) modify(rson);
}
ll query(int rec,int l,int r)
{
    if(l==r) return ad[rec]+h[l];
    int mid=(l+r)>>1;pushdown(rec);
    if(x<=mid) return query(lson);
    return query(rson);
}
inline void js(ll h1,ll h2)
{
    if(h2>h1) ans+=(h2-h1)*t;
    else ans-=(h1-h2)*s;	
}
inline void aj(ll h1,ll h2)
{
    if(h2>h1) ans-=(h2-h1)*t;
    else ans+=(h1-h2)*s;		
}
int main()
{
	freopen("qaq.in","r",stdin);
    n=read()+1;m=read();t=read();s=read();
    h[1]=read();for(rint i=2;i<=n;++i){
        h[i]=read();
        if(h[i]>h[i-1]) ans-=(h[i]-h[i-1])*t;
        else ans+=(h[i-1]-h[i])*s;
    }//printf("ans=%lld\n",ans);
    ll h1,h2,zz;
    for(rint i=1;i<=m;++i){
        x=read()+1;y=read()+1;nt=read();
        h2=query(1,1,n);--x;h1=query(1,1,n);++x;js(h1,h2);
        if(y!=n){
            zz=x;x=y;h1=query(1,1,n);++x;h2=query(1,1,n);x=zz;js(h1,h2);
        }
        modify(1,1,n);
        h2=query(1,1,n);--x;h1=query(1,1,n);++x;aj(h1,h2);
        if(y!=n){
            zz=x;x=y;h1=query(1,1,n);++x;h2=query(1,1,n);aj(h1,h2);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

