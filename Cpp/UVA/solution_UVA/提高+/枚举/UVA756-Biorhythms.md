# Biorhythms

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=9&page=show_problem&problem=697

[PDF](https://uva.onlinejudge.org/external/7/p756.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA756/329b737b4282ecf0453655ef99a6ed722e0b36b8.png)

## 样例 #1

### 输入

```
0 0 0 0
0 0 0 100
5 20 34 325
4 5 6 7
283 102 23 320
203 301 203 40
-1 -1 -1 -1```

### 输出

```
Case 1: the next triple peak occurs in 21252 days.
Case 2: the next triple peak occurs in 21152 days.
Case 3: the next triple peak occurs in 19575 days.
Case 4: the next triple peak occurs in 16994 days.
Case 5: the next triple peak occurs in 8910 days.
Case 6: the next triple peak occurs in 10789 days.```

# 题解

## 作者：C_Cong (赞：18)

[博客传送门](https://dgsyrc.github.io/2020/04/05/洛谷题解%20UVA756%20【Biorhythms】/#more)

### 题目大意

一个人体力、情感、智力出现峰值的周期分别为23、28、33天，现在给出三者上一次出现峰值的日期$p,e,i$和现在的日期$d$，问经过几天三个峰值会出现在同一天。

### 思路

首先这一看就是中国剩余定理的模板题，

如果不知道中国剩余定理建议先学习再做本题，这样就会发现这题是非常简单的。

由题意和中国剩余定理可得以下方程组：

$$  \begin{cases} x≡p(mod\ 23)  \   (1) \\ x≡e(mod\ 28)  \   (2)\\ x≡i(mod\ 33)  \   (3)\end{cases} $$

其中，该方程组可以化为以下形式：

$$(1)  \begin{cases} x_1≡1(mod\ 23) \\ x_1≡0(mod\ 28) \\ x_1≡0(mod\ 33) \end{cases} $$

$$(2)  \begin{cases} x_2≡0(mod\ 23) \\ x_2≡1(mod\ 28) \\ x_2≡0(mod\ 33) \end{cases} $$

$$(3)  \begin{cases} x_3≡0(mod\ 23) \\ x_3≡0(mod\ 28) \\ x_3≡1(mod\ 33) \end{cases} $$

解以上方程组，有：

$$ \begin{cases} x_1=5544 \\ x_2=14421 \\ x_3=1288 \end{cases} $$

由中国剩余定理有：

$lcm(23,28,33)=21252$

$ans+d≡p*x_1+e*x_2+i*x_3(mod\ 21252)$

化简得：

$ans=(p*x_1+e*x_2+i*x_3-d+21252)\ mod\ 21252$

即：

$ans=(p*5544+e*14421+i*1288-d+21252)\ mod\ 21252$

这样我们就得到了本题的通解。

但是有个特殊情况，当$ans=0$时要输出$21252$，因为你要求的是下一次三者同一天。

Q：为什么通解中要$+21252$

A：因为题目中不能保证$d$一定小于$p$、$e$、$i$，所以为了避免$ans$变成负数，所以要先$+21252$再取模

### 代码实现

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=21252;//lcm(23,28,33)
int p,e,i,d,cot;

int main()
{
	scanf("%d%d%d%d",&p,&e,&i,&d);
	while(p+e+i+d!=-4)
	{
		cot++;
		int ans=(5544*p+14421*e+1288*i-d+maxn)%maxn;//通解
		if(ans==0)//特判
		{
			ans=maxn;
		}
		printf("Case %d: the next triple peak occurs in %d days.\n",cot,ans);
		scanf("%d%d%d%d",&p,&e,&i,&d);
	}
	return 0;
}
```

有帮助的话点个赞顶上去才能让更多人看到哦！

---

## 作者：Nanchtiy (赞：11)

### 思路

几乎是裸的**中国剩余定理**模板题

但是需要注意的是此题并**不是求最小正整数解**

而是**求大于d的解**

因此对于ans我们需要分类讨论

- 当ans<=d时 ans=M-(d-ans)
- 当ans>d时 输出ans即可

### 代码
这里给出较为标准的中国剩余定理解法
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int d,M=23*28*33,ans,t;
int m[4]={0,23,28,33};//存mod数 
int a[4];
void exgcd(int a,int b,int &d,int &x,int &y)
{
    if(!b)
    {
        x=1;
        y=0;
        d=a;
    }
    else
    {
        exgcd(b,a%b,d,x,y);
        int t=x;
        x=y;
        y=t-a/b*y;
    }
}
int intchina(int n)//中国剩余定理 
{
    ans=0;//注意初始化 
    int Mi,x,y,g;
    for(int i=1;i<=n;i++)
    {
        Mi=M/m[i];
        exgcd(Mi,m[i],g,x,y);
        ans=(ans+Mi*x*a[i])%M;
    }
    if(ans<=d) return 21252-(d-ans);
    else return ans-d;//ans的分类讨论 
}
int main()
{
    while(1)
    {
        t++;
        scanf("%d%d%d%d",&a[1],&a[2],&a[3],&d);
        if(a[1]==-1&&a[2]==-1&&a[3]==-1&&d==-1) break;
        a[1]%=23,a[2]%=28,a[3]%=33;
        ans=intchina(3);
        printf("Case %d: the next triple peak occurs in %d days.\n", t, ans);
    }
}
```

---

## 作者：sunxiaofan (赞：9)

#### 默默悲哀一下：我的第一篇题解居然没过o(╥﹏╥)o
# 这是我的第二篇题解，也希望它能成为我的第一篇通过的题解。恳求!
这个题实际上很简单，先解释一下题干：
输入四个整数 p, e, i 和 d，求最小的x值，使它**大于d，且x%23==p%23&&x%28==e%28&&x%33==i%33**
### 个人感觉这个题是入门难度的
我看大家有用**中国剩余定理**的，不过我想用枚举，因为这个题枚举也能过。
## 强调：介于上一篇题解被认为算法重复，本题解将采用一种特殊的枚举方法，可以稍微降低一下时间复杂度
我们可以先将x的初值定义为i%33,每一次枚举x都增大33，这样便保证了**x%33==i%33**，之后，只要保证**x%23==p%23&&x%28==e%28&&x>d**，就可以求出结果了。x从每次增加1到每次增加33，**时间复杂度自然减少**了。
代码如下（AC）：
``` cpp
#include<cstdio>
using namespace std;
int p,e,i,d,k=1,x;
int main()
{
	for(;;)
	{
		scanf("%d%d%d%d",&p,&e,&i,&d);
		if(p==-1&&e==-1&&i==-1&&d==-1)
		{
			break;
		}
		i%=33;
		for(x=i;;x+=33)
		{
			if(x%28==e%28&&x%23==p%23&&x>d)
			{
				printf("Case %d: the next triple peak occurs in %d days.\n",k,x-d);
				k++;
				break;
			}
		}
	}
	return 0;
}
```
# 望通过

---

## 作者：AcerMo (赞：3)

中国剩余定理的裸题
结果就是x=(r1*a+r2*b+r3*c-d)%23*28*33
代码
```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	int t=1,a,b,c,d,j,emm;
	int r1=33*28,r2=23*33,r3=23*28;emm=23*28*33;
	for (j=1;;j++) if (j*r1%23==1) break;r1*=j;
	for (j=1;;j++) if (j*r2%28==1) break;r2*=j;
	for (j=1;;j++) if (j*r3%33==1) break;r3*=j;
	while (~scanf("%d%d%d%d",&a,&b,&c,&d)&&a!=-1)
	{
		int ans=(r1*a+r2*b+r3*c-d)%emm;
		ans=(ans+emm-1)%emm+1;
		printf("Case %d: the next triple peak occurs in %d days.\n",t++,ans);
	}
	return 0;
}
```

---

## 作者：Huami360 (赞：2)

其实这题暴力也能过，直接从$d$开始枚举，符合条件输出就行了。
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int a, b, c, d, ans, t;
int main(){
	while(233){
	  ++t;
	  scanf("%d%d%d%d", &a, &b, &c, &d);
	  if(a == -1 && b == -1 && c == -1 && d == -1) break;
	  ans = 0;
	  for(int i = d + 1; ; ++i){
         ++ans;
         if(i % 23 == a % 23 && i % 28 == b % 28 && i % 33 == c % 33)
           break;
      }
      printf("Case %d: the next triple peak occurs in %d days.\n", t, ans);
    }
    return 0;
}
```

---

## 作者：Isprime (赞：2)

吐槽一下你谷的RemoteJudge交个题还要注册uva账号

这题是一道（类似）中国剩余定理模板题

这篇题解将会详细讲解中国剩余定理的实现

## 引入

各位小学的时候都应该做过这样一道题（雾）：一个数除以3余2，除以5余1，除以7余2 ~~，当时的算法就是凑~~，这就是一道经典的中国剩余定理

## 定理

（想要学习CRT，你需要先掌握扩展欧几里得算法）

中国剩余定理（孙子定理，Chinese Remainder Theorem,CRT），常用于求解同余方程组
$$ \left\{
\begin{aligned}
x \equiv a_1 (mod \; m_1)\\
x \equiv a_2 (mod \; m_2)\\
...\qquad\qquad\\
x \equiv a_n (mod \; m_n)
\end{aligned}
\right.
$$

其中$m_1,m_2...m_n$是两两互质的整数，$m=\prod^n_{i=1}m_i,M_i=m/m_i$，$t_i$是同余方程$M_it_t\equiv1(mod\;m)$的一个解

对于任意 $n$ 个整数 $a_1,a_2...a_n$方程组有整数解$x=\sum^n_{i=1}a_iM_it_i$

我们来证明一下中国剩余定理。因为$M_i=m/m_i$是除$m_i$外所有模数的倍数，所以$∀k\neq i,a_iM_it_i\equiv0(mod\; m_k)$，又因为$a_iM_it_i\equiv a_i(mod\; m_i)$，代入$x=\sum^n_{i=1}a_iM_it_i$，原方程组成立

中国剩余定理求出了同余方程组的一个特解，方程组的通解可表示为$x+km(k\subseteq\mathbb{Z)}$

## 题解

为什么说这一题类似中国剩余定理模板题呢？

因为题目是要求大于$d$的解，我们可以求解完毕后特判一下，若$x<d$就把$x$加上$m$，最终结果再$mod m$

记得特判最后答案为0的情况

Code

```cpp
#include <cstdio>
#include <cstring>
#define int long long
using namespace std;
int ans=0,M_=21252,d,n=3;
int cnt;
int a[4],m[4]={0,23,28,33},mi[4];
inline int exgcd(int a,int b,int &x,int &y) {
	if(!b) {x=1; y=0; return a;}
	int d=exgcd(b,a%b,x,y);
	int z=x; x=y; y=z-y*(a/b);
	return d;
}
signed main() {
	scanf("%lld%lld%lld%lld",a+1,a+2,a+3,&d);
    cnt=1;
	while(a[1]!=-1) {
		ans=0;
		memset(mi,0,sizeof(mi));
		for(register int i=1;i<=n;++i) {
			mi[i]=M_/m[i];
			int x=0,y=0;
			exgcd(mi[i],m[i],x,y);
			if(x<0) x+=m[i];
			ans+=a[i]*mi[i]*x;
		}
		if(ans<d) ans+=M_;
		ans-=d;
        ans=ans%M_;
        if(!ans) ans=M_;
		printf("Case %lld: the next triple peak occurs in %lld days.\n",cnt,ans);
        scanf("%lld%lld%lld%lld",a+1,a+2,a+3,&d);
        cnt++;
	}
}
```

---

## 作者：Unnamed114514 (赞：1)

根据中国剩余定理，答案比较小，不会超过 $23\times{28}\times{33}=21252$，所以可以考虑枚举。

枚举 $x\in[d+1,d+21252]$，然后满足 $x\bmod23=p\bmod23,x\bmod28=e\bmod28,x\bmod33=i\bmod33$，最后输出 $x-d$ 即可，时间复杂度 $O(1)$。

---

## 作者：封禁用户 (赞：1)

首先，我们要知道，任意两个峰值之间一定相距整数倍的周期，假设一年的第 $N$ 天达到峰值，则下次达到峰值的时间为 $N+T\times k$ （ $T$ 是周期， $k$ 是任意正整数）。所以，三个峰值同时出现的那一天 ( $S$ )应该要满足：

$$S=N_1+T_1\times k_1=N_2+T_2\times k_2=N_3+T_3\times k_3$$

$N_1, N_2, N_3$ 分别为体力，情感，智力出现峰值的日期， $T_1, T_2, T_3$ 分别为体力，情感，智力周期。我们只需求出 $k_1, k_2, k_3$ 三个非负整数使上面的等式成立。

想直接求出 $k_1, k_2, k_3$ 貌似很难 ~~（实际很简单）~~，但是我们的目的只是求出 $S$，我们可以考虑从结果递推。根据上面的等式， $S$ 需要满足 $3$ 个要求：

$$\begin{array}{l} 
  \left\{\begin{matrix} 
  S\equiv N_1\pmod{T_1} \\ 
  S\equiv N_2\pmod{T_2} \\ 
  S\equiv N_3\pmod{T_3}
\end{matrix}\right.    
\end{array} $$

这样，我们就可以寻用韩信点兵或中国剩余定理来计算。

## AC代码

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 1e1 + 3;
const int INF = 0x3f;
int main()
{
	int p, e, i, d, T = 1;
	cin >> p >> e >> i >> d;
	do{
		int lcm = 21512;
		int ans = (5544 * p + 14421 * e + 1288 * i - d + lcm) % lcm;
		if(ans == 0)ans = lcm;
		cout << "Case " << T++ << ":the next triple peak occurs in " << ans << " days." << endl;
		cin >> p >> e >> i >> d;
	}while(p != -1);
    return 0;
}

```

---

## 作者：KEBrantily (赞：1)

~~你谷题意概括就是好啊！~~

本题可以说是中国剩余定理模板。

简单说一下中国剩余定理，就是有方程组：

$$\begin{cases}
x \equiv a_1 \pmod {b_1}\\
x \equiv a_2 \pmod {b_2}\\
x \equiv a_3 \pmod {b_3}\\
\cdots\\
x \equiv a_n \pmod {b_n}
\end{cases}$$

当所有的 $b$ 互质时，方程组存在整数解。

设 $S=\prod_{i=1}^{n} {b_i}$，$s_i=\frac{S}{b_i}$，$t_i$ 为方程 $s_i\times t_i\equiv 1 \pmod {b_i}$ 的任意一个解。

则方程组有一个解为 

$$\sum_{i=1}^{n} a_i\times s_i\times t_i$$

并且方程组在模 $S$ 意义下有唯一解，可以根据扩展欧几里得算法来实现。

具体证明这里不给出。

回到题目。

发现 $28$、$23$、$33$ 互质，给出的式子又满足中国剩余定理的形式，就可以直接求出满足题目要求的 $x$。

要注意求出的 $x$ 必须满足 $x>d$ 的条件。我的处理方法是不断加这三个数的乘积直到满足条件为止。

```cpp
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define rr register 
#define maxn 10000100
#define INF 0x3f3f3f3f
#define Mod 1000000007
//#define int long long 

using namespace std;

const int M=23*28*33;
int a[5],d,Ans,ans,cnt;
int m[5]={0,23,28,33};

inline int read(){
    int s=0,w=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=(s<<1)+(s<<3)+ch-'0',ch=getchar();
    return s*w;
}

int exgcd(int a,int b,int &x,int &y){
    if(!b){x=1;y=0;return a;}
    ans=exgcd(b,a%b,x,y);
    int t=x;x=y;y=t-a/b*y;
    return ans;
}

int main(){
    while(1){
        a[1]=read();a[2]=read();a[3]=read();d=read();Ans=0; 
        if(a[1]==a[2]&&a[2]==a[3]&&a[3]==d&&d==-1) return 0; 
        for(int i=1,times,x,y;i<=3;i++){
            times=M/m[i];
            exgcd(times,m[i],x,y);
            Ans=((Ans+times*a[i]*x)%M+M)%M;
        }
        while(Ans<=d) Ans+=M;
        printf("Case %d: the next triple peak occurs in %d days.\n",++cnt,Ans-d);
    }
} 
```

---

## 作者：dzdolrc (赞：1)

## 前置芝士

在汉朝时期，著名将领韩信有个点兵的故事：

 _三三数之剩二，_

 _五五数之剩三，_

_七七数之剩二。_

_问兵几何_ 


这就需要运用到**[中国剩余定理](https://baike.baidu.com/item/%E5%AD%99%E5%AD%90%E5%AE%9A%E7%90%86/2841597?fromtitle=%E4%B8%AD%E5%9B%BD%E5%89%A9%E4%BD%99%E5%AE%9A%E7%90%86&fromid=11200132&fr=aladdin)**了

先来个简单的题目帮助理解：

设总数为$x$，$x \bmod 7 \equiv 2,x \bmod 5 \equiv 2,x \bmod 3 \equiv 2$求$x$最小值

因为余数都为$2$，那么$x-2$就是$3,5,7$的公倍数。因为$3,5,7$互质，所以最小公倍数为$3 \times 5 \times 7=105$,即$x-2=105$,那么$x$满足条件的最小值就是$107$。

------------
回归到题目，在此题目中，余数不一定相等，所以我们需要将特殊拓展到一般。


由题意得：

$\begin{cases}
x  \bmod 23 \equiv a_1 \\
x  \bmod 28 \equiv a_2 \\
x  \bmod 33 \equiv a_3
\end{cases}$

同简易问题一样，设一个$M$为最小公倍数，易得$M=23\times28\times33$。解决余数这类的问题，我们通常会使用**同余方程**来解决。
### $ax+by=gcd(a,b)$

然而我们手上有三个已知数，该怎么转化为系数$a,b$呢。只需要把$a$作为两个数的乘积，$b$则是另一个数。每个$x$都是对于$a$为两数之积时的解，所以我们需要循环三次$exgcd$（[扩展欧几里得算法](https://www.luogu.com.cn/problem/P1082)，在这里就不展开讲），将每次得到的$x$相加，再根据问题所需的格式输出就可以了

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[4],d,M=23*28*33;
int m[4]={0,23,28,33};
int x,y,t,ans;
void exgcd(int p,int o,int &x,int &y){
	if(o==0){
		x=1;
		y=0;
	}else{
		int tmpx,tmpy;
		exgcd(o,p%o,tmpx,tmpy);
		x=tmpy;
		y=tmpx-p/o*tmpy;
	}
}
int main(){
	while(1){
		cin>>a[1]>>a[2]>>a[3]>>d;
		if(a[1]==-1&&a[2]==-1&&a[3]==-1&&d==-1) break;
		ans=0;
		for(int i=1;i<=3;i++){
			x=0,y=0;
			int Mi=M/m[i];//选择两个数作为系数a
			exgcd(Mi,m[i],x,y);//扩展欧几里得
			x=(x%m[i]+m[i])%m[i];
			ans=((ans+Mi*x*a[i])%M+M)%M;
		}
   	    if(ans<=d) x+=21252;//防止答案为负数
		printf("Case %d: the next triple peak occurs in %d days.\n",++t,ans-d);
}
	return 0;
}
```

---

## 作者：溪水瑶 (赞：1)

## 最短代码：
这题用枚举就可以惹，从d+1开始枚举找到第一个符合条件的就立刻输出然后退出枚举。
下面窝给大家看看窝的代码，记得是多组数据。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p,e,x,d,sum;
int main(){
	while(1){
		sum++;
		cin>>p>>e>>x>>d;
		if(p+e+x+d==-4)return 0;
		for(int i=d+1;i;i++){
			if((i%23)==(p%23))
				if((i%28)==(e%28))
					if((i%33)==(x%33)){
						printf("Case %d: the next triple peak occurs in %d days.\n",sum,i-d);
						break;
					}
		}
	}
	return 0;
}
```
完结撒花✿✿ヽ(°▽°)ノ✿

---

## 作者：Karry5307 (赞：1)

### 题意
求满足$\begin{cases}x_0\equiv x\pmod {23}\\ x_0\equiv y\pmod {28}\\ x_0\equiv z\pmod {33}\\x_0>limit\end{cases}$的$x_0$的最小值。
### 题解
一道线性代数的好题。

这道题可以不用暴力枚举，直接手推。

以下的方程中$x<23,y<28,z<33$，所以输入时要先取模。

考虑模方程组$\begin{cases}x_0\equiv y\pmod {28} & (1)\\x_0 \equiv z \pmod{33} & (2)\end{cases}$

$(2)$式可以化为

$$x_0=33k+z\quad(3)$$

$(3)$式$\bmod\ 28$，得

$$x_0 \equiv {5k+z}\pmod {28}$$

$$\therefore 28\vert 5k+z-y$$

由于$\gcd (5,28)=1$，所以可以算出$5$对于$28$的逆元，为$17$。

$$\therefore k\equiv 17(y-z+28)\pmod {28}$$

这里考虑到可能$y<z$，所以加了$28$。

带进去得到$\min x_0=33(17(y-z+28)\bmod 28)+z$，记$\min x_0$为$best$。

所以说两个方程融合为了一个新的模方程，即$x_0 \equiv best\pmod {28\times 33}$

记$x_0=k^\prime 28\times 33+best$，则

解出$k^\prime=(x-best\bmod 23+23)\times 6\mod 23$。（上一步解出来的$best$可能$>23$，要取模）

所以将$k^\prime$带入算即可，注意最终值不够$limit$要加上$21252$。

最后，**本题输出格式一定要开$long\ long$**！~~我就是活生生的例子~~

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll test,x,y,z,limit,best,res;
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
int main()
{
	while(x=read(),x!=-1)
	{
		y=read()%28,z=read()%33,limit=read();
		x%=23;
		best=33*((y-z+28)*17%28)+z;
		res=(x-(best%23)+23)*6%23;
		res=res*28*33+best;
		while(res<=limit)
		{
			res+=21252;
		}
		printf("Case %lld: ",++test);
		printf("the next triple peak occurs in %lld days.\n",res-limit);
	}
}
```

---

## 作者：Kelier_pkl (赞：1)

# Biorhythms 题解

*本题解有部分不妥善之处，勿怪*

---

## 题意

给定 $p,e,i,d$，求 $\begin{cases} x\equiv p\pmod {23}\\ x\equiv e\pmod {28}\\ x\equiv i\pmod {33}\\ x> d\end{cases}$ 的最小整数解 $x$。

## 思路

通过简化版题意可知，这道题需要运用 CRT，而且因为 $23,28,33$ 互质，所以你甚至不用写 exCRT。

所以这道题……就解了……

吗？

## 实现细节

注意读题，本题题面上说的 $x>d$ 意味着我们的计算结果并非 CRT 计算出的特解。

如果最后得出的答案减去 $d$ 之后是一个负数，说明我们求到的解不满足 $x>d$，在这时候要加上 $\operatorname{lcm}(23,28,33)$，也就是 $21252$。

至此，本题结……



## 补充

可能部分同学不理解为什么这道题可以转换成上面的同余方程组，那么我们就来精简一下这个题目吧。

> 三个周期长度分别为 $23$ 天，$28$ 天，$33$ 天，每个周期中有一天是高峰。
> 给定三个高峰某一次的时间，求出下一次三个高峰在同一天距离给定的今天还有几天。

舒服多了。

那么题面中给出的信息已经很明了了。

简单分析一下，每一次高峰距离下一次高峰正好是一个周期。

那么把周期和取模联系起来，我们很容易就想到每一个高峰取模周期长度得到的值相等，也就是它们都是周期中的同一天。

既然要求的那个时间是三者均高峰的时间，那么也就是说这个时间对三个周期长度取模的结果都为高峰时刻的结果，于是我们便获得了开头的同余方程组。

-----

最后附上 AC 代码

## Code

~~~c++
#include<cstdio>
#define LL long long
using namespace std;
LL a[5],b[5]={0,23,28,33},k,n=3,crt,cnt;
LL exgcd(LL a,LL b,LL &x,LL &y)
{
	if(b==0)
	{
		x=1,y=0;
		return a;
	}
	LL g=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return g;
}
LL CRT()
{
	LL x,y,k,M=b[1],ans=a[1];
	for(int i=2;i<=n;i++)
	{
		LL A=M,B=b[i];
		LL C=(a[i]-ans%B)%B;
		LL gcd=exgcd(A,B,x,y);
		LL Q=B/gcd;
		if(C%gcd!=0)return -1;
		x=((x*C/gcd)%Q+Q)%Q;
		ans+=x*M;
		M*=Q;
		ans=(ans%M+M)%M;
	}
	if(ans-k<=0)ans+=M;
	return ans;
}
int main()
{
	while(1)
	{
		scanf("%lld%lld%lld%lld",&a[1],&a[2],&a[3],&k);
		if((a[1]==-1)&&(a[2]==-1)&&(a[3]==-1)&&(k==-1))break;
		for(int i=1;i<=n;i++)a[i]=a[i]%b[i];
		crt=CRT()-k;
		if(crt<=0)crt+=21252;
		printf("Case %lld: the next triple peak occurs in %lld days.\n",++cnt,crt);
	}
	return 0;
}
~~~

## 友情链接

[中国剩余定理](https://oi-wiki.org/math/number-theory/crt/)

---

## 作者：myyyIisq2R (赞：0)

[POJ1006 $and$ UVA756](https://www.luogu.com.cn/problem/UVA756)

## 分析
首先我们要知道，任意两个峰值之间一定相距整数倍的周期。假设一年的第 $N$ 天达到峰值，则下次达到峰值的时间为 $N+Tk$ （ $T$ 是周期，$k$是任意正整数）。所以，三个峰值同时出现的那一天（ $S$ ）应该满足：

### $S = N_1 + T_1 × k_1 = N_2 + T_2 × k_2 = N_3 + T_3 × k_3$
$N_1$，$N_2$，$N_3$ 分别为体力，情感，智力出现峰值的日期， $T_1$，$T_2$，$T_3$ 分别为体力，情感，智力周期。我们需要求出 $k_1$，$k_2$，$k_3$ 三个非负整数使上面的等式成立。

想直接求出 $k_1$，$k_2$，$k_3$ 貌似很难，但是我们的目的是求出 $S$ ，可以从结果逆推。我们就可以把问题转化为求一个最小数，使其除以 $T_1$ 余 $N_1$ ，除以 $T_2$ 余数为 $N_2$ ，除以 $T_3$ 余数为 $N_3$ .直接使用中国剩余定理即可。

## 参考程序
```cpp
#include <bits/stdc++.h>
#define qwq cout<<"rp++!";
using namespace std;
int main()
{
	int p,e,i,d;
	int t{};
	cin>>p>>e>>i>>d;
	do
	{
		int lcm = 21252;//lcm(23,28,33) 提前计算好
		int ans{(5544*p+14421*e+1288*i-d+lcm) % lcm} ;
		if(!ans)
			ans = lcm;
		cout<<"Case "<<++t<<": the next triple peak occurs in "<<ans<<" days."<<(char)10;
		cin>>p>>e>>i>>d;
	}while(p!=-1);
	return 0;
	qwq
}
```

---

## 作者：little_cindy (赞：0)

## 前置芝士

[CRT 学习笔记](https://www.luogu.com.cn/blog/little-cindy/studynote-of-CRT)

## 思路
如学习笔记中，就是 $n=3,a_1=p,a_2=e,a_3=i,p_1=23,p_2=28,p_3=33$ 而已。

所以只要跑一遍 CRT，假设得到的答案为 $X$，如果 $X<d$，那么就把 $X$ 设为 $X+P$ 即可，如果 $X<d$ 仍然成立，那么就重复执行上面的操作（这里用 while 循环就好了）。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int P=23*28*33;
int a[5],p[5]={0,23,28,33};
int exgcd(int a,int b,int &x,int &y){
	if(b==0){
		x=1;
		y=0;
		return a;
	}
	int d=exgcd(b,a%b,x,y),x0=x,y0=y;
	x=y0;
	y=x0-(a/b)*y0;
	return d;
}
int inv(int a,int p){
	int x,y;
	int d=exgcd(a,p,x,y);
	return (x%p+p)%p;
}
int getAns(){
	int ans=0;
	for(int i=1;i<=3;i++){
		int r=P/p[i];
		ans+=a[i]*inv(r,p[i])*r%P;
	}
	return ans%P;
}
signed main(){
    int tot=0;
	while(1){
	    tot++;//统计次数
		for(int i=1;i<=3;i++){
			cin>>a[i];
		}
		int d;
		cin>>d;
		if(a[1]==-1&&a[2]==-1&&a[3]==-1&&d==-1){
			return 0;
		}
		int X=getAns();//CRT板子
		X=(X%P+P)%P;//取个模
		while(X<=d){//让 X 比 d 大
			X+=P;
		}
		cout<<"Case "<<tot<<": the next triple peak occurs in "<<X-d<<" days."<<endl;
	}
	return 0;
}
```

---

## 作者：FLAMEs_ (赞：0)

一道近乎是板子的**中国剩余定理**题目。

本题解主要讲述中国剩余定理的构造方法。~~证明方法请自行度娘。~~

现有一个一元线性同余方程组 $(S)$：

$(S):
\begin{cases}
  & x \equiv a_{1} \pmod{m_{1}} \\
  & x \equiv a_{2} \pmod{m_{2}} \\
  &\quad  \vdots  \\
  & x \equiv a_{n} \pmod{m_{n}}
\end{cases}$

中国剩余定理给出了以上方程有解情况下的解的构造方法。

中国剩余定理说明：假设整数 $m_{1},m_{2},\dots,m_{n}$ 两两互质，则对任意的整数：$a_{1},a_{2},\dots,a_{n}$，方程组$(S)$有解，并且通解可以用如下方式构造得到：

令$M=\prod_{i=1}^{n} m_{i}$，并设$M_{i}=M/m_{i},\forall i \in \left \{  1,2,\dots,n\right \} $

令 $k_{i}=M_{i}^{-1}$ 为 $M_{i}$ 模 $m_{i}$ 的数论倒数。

则 $k_{i}M_{i}\equiv1 \pmod{m_{i}},\forall i \in \left \{  1,2,\dots,n\right \}$

该方程组在 $ \bmod$ $M$ 意义下仅有一个解，即：

$x=(\sum_{i=1}^{n} a_{i}k_{i}M_{i})\bmod M$

构造完毕。

再来看本题。 本题与中国剩余定理思路相似，构造得出本题通解即可。

几点注意：

1. 一定要注意 $x>d$ 这个条件，不注意两行泪 TAT。
2. 当 $ans=0$ 时要输出 $23 \times 28 \times 33=21252$，不然会 WA（由题意可得）。
3. 输出结果时要判负，输出负数就不好了。


---

## 作者：pldzy (赞：0)

[UVA756 Biorhythms - 传送门](https://www.luogu.com.cn/problem/UVA756)

## 思路

直接来看，它就是一个[中国剩余定理（CRT）](https://469672.blog.luogu.org/shuo-lun-zhong-guo-sheng-yu-ding-li-crt)。

但与[【模板】中国剩余定理(CRT)](https://www.luogu.com.cn/problem/P1495) 不同的是，它已经给出了所有的模数。

在 CRT 思想的基础上，我们可以求出每一个模数对应的正整数 $a$，使得（以第二个模数为例）：
$$
\begin{cases}a\equiv{0}\pmod{23}\\a\equiv{1}\pmod{28}\\a\equiv{0}\pmod{33}\end{cases}
$$

此处可求出 $a=14421$。

同理可求出剩下两个模数的 $a$ 的值。

这样不难得出，题目中的 $x$ 的值就是：

$$ (5544 \times p + 14421 \times e + 1288 \times i)\ \bmod \operatorname{lcm}(23,28,33)$$

最后我们再减去 $d$，取模就可以得出最终答案了。

注意取模时因避免出现负数，所以要先加上模数再取模。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int lcm = 21252;//lcm (23, 28, 33) = 21252
int p, e, i, d;
int T;

inline void inpt ()
{
	scanf ("%d %d %d %d", &p, &e, &i, &d);
}

int main ()
{
	inpt ();
	while (p != -1 and e != -1 and i != -1 and d != -1)
	{
		T += 1;
		int ans = (5544 * p + 14421 * e + 1288 * i - d + lcm) % lcm;
		if (ans == 0) 
			ans = lcm;
		printf ("Case %d: the next triple peak occurs in %d days.\n", T, ans);
		inpt ();
	}
	return 0;
}
```
感谢阅读。

---

## 作者：whale142857 (赞：0)

~~终于找到一个可以写题解的题了呜呜呜~~

题意很清楚，让你去解一个同余方程组

$\begin{cases}
x \equiv a_{1} \pmod {m_{1}}\\
x \equiv a_{2} \pmod {m_{2}}\\
x \equiv a_{3} \pmod {m_{3}}\\
\vdots\\
x \equiv a_{n} \pmod {m_{n}}\\
\end{cases}$

这其实就是中国剩余定理

我这里先讲一下 $m$ 不互质该怎么处理

假设我们已经求出了前 $k$ 个方程的解 $x$ ,即对 $\forall$ $i \in [1,k]$ 满足：
$$
x \equiv a_{i} \pmod {m_{i}}
$$
我们需要求满足前 $k + 1$个方程的解

设 $LCM_{i}$ 为前 $i$ 个 $m$ 的最小公倍数

显然有
$
x + p \times LCM_{k} \equiv a_{i} \pmod {m_{i}}
$
成立

即前 $k$ 个方程的通解为 $x + p \times LCM_{k},(p \in Z)$

将它带入第 $k + 1$ 个方程：
$$
x + p \times LCM_{k} \equiv a_{k + 1} \pmod {m_{k + 1}}
$$
写成带余除法：
$$
p \times LCM_{k} - q \times m_{k + 1} = a_{k + 1} - x
$$
把 $p$ 解出来，$x + p \times LCM_{k}$ 就是满足前 $k + 1$ 个方程的解

循环求出第 $n$ 个解就可以了

---

## 总结一下

1.求出方程组的第一个解 $x$，也就是 $a_{1}$，此时的 $LCM$ 为 $m_{1}$

2.解二元一次不定方程，更新 $LCM$ ，更新 $x$，至于方程怎么解，用 $exgcd$ 就可以了

注意，对答案的取模和更新用哪个 $LCM$ 是需要注意的，具体操作可以看代码：
```cpp
#include<cstdio>


using namespace std;


int LCM,a[4],m[4] = {0,23,28,33},d,ans,x,y,tmp,GCD,t;


int exgcd(int a,int b,int &x,int &y) {
	if(!b) {
		x = 1;
		y = 0;
		return a;
	}
	int t = exgcd(b,a % b,x,y);
	int tmp = x;
	x = y;
	y = tmp - a / b * y;
	return t;
}


int main() {
	while(scanf("%d%d%d%d",&a[1],&a[2],&a[3],&d) != EOF) {
		t += 1;
		if(a[1] == -1 and a[2] == -1 and a[3] == -1 and d == -1) break;
		ans = a[1];
		LCM = m[1];//初始化第一个方程的答案
		for(int i = 2;i <= 3;i += 1) {
			GCD = exgcd(LCM,m[i],x,y);
			tmp = LCM;
			LCM = m[i] / GCD * LCM;//用GCD更新LCM，tmp保存上一个LCM的值
			x = (a[i] - ans) / GCD * x;
			x = (x % LCM + LCM) % LCM;
			ans = (ans + x * tmp) % LCM;//更新答案
		}
		
		if(ans <= d) ans += LCM;
		printf("Case %d: the next triple peak occurs in %d days.\n",t,ans - d);
	}
	return 0;
}
```

但本题的所有 $m$ 是互质的，所以最后的答案可以直接表示成
$$
\sum_{i = 1}^n {a_{i} \times M_{i} \times t_{i}} 
$$
设 $M= \prod_{i=1}^n {m_{i}}$， $M_{i}=M / m_{i}$

$t_{i}$ 为 $M_{i}$ 在模 $m_{i}$ 意义下的逆元

至于为什么，我只会用结论证qwq

因为有
$$
M_{i} \times t_{i} \equiv 1 \pmod {m_{i}}
$$
两边同时乘一个 $a_{i}$
$$
a_{i} \times M_{i} \times t_{i} \equiv a_{i} \pmod {m_{i}}
$$

而
$$
\sum_{i=1}^n {a_{i} \times M_{i} \times t_{i}}=\sum_{i=1,i \ne q}^n {a_{i} \times M_{i} \times t_{i}} + a_{q} \times M_{q} \times t_{q} \equiv 0 + a_{q} \equiv a_{q}\pmod {m_{q}}
$$

可以看出对于 $\forall q \in [1,n]$ 都满足，正确性得证

第一次打这么多公式挺累的hh

---

## 作者：xgwpp6710 (赞：0)

看了一下大家的题解，基本都要用到[中国剩余定理](https://baike.baidu.com/item/%E5%AD%99%E5%AD%90%E5%AE%9A%E7%90%86/2841597?fromtitle=%E4%B8%AD%E5%9B%BD%E5%89%A9%E4%BD%99%E5%AE%9A%E7%90%86&fromid=11200132&fr=aladdin)。但是本蒟蒻不会中国剩余定理，怎么办呢？

其实，这样的题目也可以暴力枚举。就是将 $x$ 设定为 $i$ 模 $33$ 的余数，然后不停地加 $33$ 。这样保证 $x$ 和 $i$ 是模 $33$ 同余的。此时再判断模 $23$ 和 $28$ 的条件是否满足。

代码：
```cpp
#include<bits/stdc++.h>
int p,e,i,d,x,c;
int main()
{
	do
	{
		c++;//记录是第几个数据点
		scanf("%d%d%d%d",&p,&e,&i,&d);
		if(p==-1&&e==-1&&i==-1&&d==-1) return 0;//特判，否则-1 -1 -1 -1输入时还要重新执行
		p%=23;
		e%=28;
		i%=33;//注意取模，否则p,e,i大于23,28,33会卡住
		x=i;//开始枚举！
		while(x%23!=p||x%28!=e) x+=33;//找到符合条件的情况！
		if(x<=d) x+=21252;//特判，解决数据点为0 0 0 0时的问题
		printf("Case %d: the next triple peak occurs in %d days.\n",c,x-d);
	}while(p!=-1||e!=-1||i!=-1||d!=-1);
	return 0;
}
```

---

