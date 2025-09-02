# PE Lesson

## 题目描述

Smart Beaver decided to be not only smart, but also a healthy beaver! And so he began to attend physical education classes at school X. In this school, physical education has a very creative teacher. One of his favorite warm-up exercises is throwing balls. Students line up. Each one gets a single ball in the beginning. The balls are numbered from $ 1 $ to $ n $ (by the demand of the inventory commission).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF316D1/dd5cf282ea1c98183da55e6989050cd8eabdb84c.png) Figure 1. The initial position for $ n=5 $ . After receiving the balls the students perform the warm-up exercise. The exercise takes place in a few throws. For each throw the teacher chooses any two arbitrary different students who will participate in it. The selected students throw their balls to each other. Thus, after each throw the students remain in their positions, and the two balls are swapped.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF316D1/6b5342e8a9f57fae45c7b1e47abe66718bc85450.png) Figure 2. The example of a throw. In this case there was a throw between the students, who were holding the $ 2 $ -nd and the $ 4 $ -th balls. Since the warm-up has many exercises, each of them can only continue for little time. Therefore, for each student we know the maximum number of throws he can participate in. For this lessons maximum number of throws will be $ 1 $ or $ 2 $ .

Note that after all phases of the considered exercise any ball can end up with any student. Smart Beaver decided to formalize it and introduced the concept of the "ball order". The ball order is a sequence of $ n $ numbers that correspond to the order of balls in the line. The first number will match the number of the ball of the first from the left student in the line, the second number will match the ball of the second student, and so on. For example, in figure $ 2 $ the order of the balls was ( $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ ), and after the throw it was ( $ 1 $ , $ 4 $ , $ 3 $ , $ 2 $ , $ 5 $ ). Smart beaver knows the number of students and for each student he knows the maximum number of throws in which he can participate. And now he is wondering: what is the number of distinct ways of ball orders by the end of the exercise.

## 样例 #1

### 输入

```
5
1 2 2 1 2
```

### 输出

```
120
```

## 样例 #2

### 输入

```
8
1 2 2 1 2 1 1 2
```

### 输出

```
16800
```

# 题解

## 作者：yuzhechuan (赞：5)

小清新思维题

---

### 题解：

首先很容易发现答案与顺序无关，只与"1","2"的数量有关，并记"1"的个数为$a$，"2"的个数为$b$

首先考虑$b=0$的情况

设$f[i]$表示剩余$i$个"1"时的排列数

很容易得到转移$f[i]=f[i-2]\times (i-1)+f[i-1]$，表示$(i-1)$种方法选1个互换，1种方法选自己保持不变

考虑扩展到$b\ne 0$的情况

我们把2次交换的限制看成一次主动交换和一次被动交换

那我们就可以让$b$个"2"都先使用一次主动交换

那么第一个"2"可以从$n$个中选一个

第二个"2"可以从$n-1$中选一个

第三个"2"可以从$n-2$中选一个

。。。以此类推

这样$b$次交换后会剩下正好$a$个"1"（可以用数学轻松证明）

于是答案$ans=f[a]\times \prod\limits_{i=1}^{b}(n-i+1)$

---

### 代码：

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("avx,avx2")
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
    char c=getchar();bool f=0;x=0;
    while(!isdigit(c)) f|=c=='-',c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f) x=-x;return x;
}
template<class t> inline void write(t x){
    if(x<0) putchar('-'),write(-x);
    else{if(x>9) write(x/10);putchar('0'+x%10);}
}

#define int long long

const int mod=1e9+7,N=1e6+5;
int n,ans=1,cnt,f[N];

signed main(){
	read(n);
	for(int i=1,x;i<=n;i++){
		read(x);
		if(x==1) cnt++;
	}
	f[0]=f[1]=1;
	for(int i=2;i<=cnt;i++) f[i]=(f[i-2]*(i-1)+f[i-1])%mod;
	for(int i=n;i>cnt;i--) ans=ans*i%mod;
	write(ans*f[cnt]%mod);
}
```

---

## 作者：LCuter (赞：1)

## CF316D 题解

##### $\text{Description}$

给定一个序列 $\{t_n\},\forall i,t_i\in\{1,2\}$。问有多少个排列 $p$ 满足 $[1,2,\cdots,n]$ 可以通过有限制地交换任意两位置地数得到，其中第 $i$ 个位置至多只能被交换 $t_i$ 次。

$1\le n\le 10^6$

##### $\text{Solution}$

首先考虑怎样判定一个排列 $p$ 满足条件。

注意到任意两位置可以交换，考虑对于所有 $i$，连一条有向边 $i\rightarrow p_i$，则可以得到一张由若干不相交的简单环组成的有向图。

观察可知若一个排列满足条件，则其对应的图中，任意简单环中 $t$ 为 $1$ 的点不超过两个，可以通过简单构造证明。

问题转换为把这些数分成若干个圆排列，要求每个圆排列中至多有 $2$ 个 $t_i$ 为 $1$ 的点。

考虑先把 $t_i$ 为 $1$ 的点放好，设有 $a$ 个 $t_i$ 为 $1$ 的点，我们要将其分为 $b$ 个圆排列。

设有 $p$ 个圆排列有 $2$ 个这样的点，$q$ 个圆排列只有一个这样的点，解二元一次不等式可得 $p=a-b,q=2b-a$。

我们先把这 $p$ 个圆排列选好，然后剩下的点都是孤立点，由于圆排列间无序，故有：
$$
\frac{A^{2(a-b)}_{a}}{2^{a-b}(a-b)!}
$$
$2^{a-b}$ 消除圆排列内的顺序带来的影响，$(a-b)!$ 消除圆排列间的顺序带来的影响。

剩下 $t_i$ 为 $2$ 的点就可以按照求斯特林数的方式随意插入，故最终答案为：
$$
\frac{n!}{a!}\sum_{b=\lceil\frac{a}{2}\rceil}^a\frac{A^{2(a-b)}_{a}}{2^{a-b}(a-b)!}
$$

##### $\text{Code}$

```
#include<bits/stdc++.h>
#define REG register
using namespace std;
inline void read(int& x){
	static char c;
	while(!isdigit(c=getchar()));x=c^48;
	while(isdigit(c=getchar()))x=(x*10)+(c^48);
}

const int Mod=1000000007,N=5000005;

int T,n,tmp;

int Pow(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=1ll*ans*a%Mod;
		a=1ll*a*a%Mod,b>>=1;
	}
	return ans;
}

int Fac[N],Iac[N],_2Pow[N];
inline void Init(){
	int Inv=Pow(2,Mod-2);
	Fac[0]=Iac[0]=_2Pow[0]=1;
	for(REG int i=1;i<=N-4;++i) Fac[i]=1ll*Fac[i-1]*i%Mod,_2Pow[i]=1ll*Inv*_2Pow[i-1]%Mod;
	Iac[N-4]=Pow(Fac[N-4],Mod-2);
	for(REG int i=N-5;i;--i) Iac[i]=1ll*Iac[i+1]*(i+1)%Mod;
}
inline int Binom(int n,int m){return 1ll*Fac[n]*Iac[m]%Mod*Iac[n-m]%Mod;}

int Ans,t;

inline void Work(){
//	freopen("throw.in","r",stdin);
//	freopen("throw.out","w",stdout);
	Init();
	T=1;
	while(T--){
		t=Ans=0;
		read(n);
		for(REG int i=1;i<=n;++i) read(tmp),t+=tmp==1;
		for(REG int i=(t-1)/2+1;i<=t;++i) Ans=(Ans+1ll*Fac[t]*Iac[2*i-t]%Mod*_2Pow[t-i]%Mod*Iac[t-i]%Mod)%Mod;
		if(!t) ++Ans;
		Ans=1ll*Ans*Fac[n]%Mod*Iac[t]%Mod;
		printf("%d\n",Ans);
	}
}

int main(){Work();}
```



---

## 作者：chufuzhe (赞：1)

可以分开讨论交换一次的人和交换两次的人。

因为只要交换的方案不同，最终的排列就不同，所以可以求不同的交换方案数。

对于交换一次的人，他可以和自己玩，也可以找一个人玩。

所以设 $f[i]$ 表示有 $i$ 个只能交换一次的人的交换方案数，

$f[i]=f[i-1]+(i-1)*f[i-2]$

对于能交换两次的人，他们可选择的交换方案共有 $a!$ ( $a$ 表示能交换两次的人的个数) 种。

最后的答案就是两种方案数的积。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read() //输入量较大，要用快读
{
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int f[1000005]; //定义，f[i]表示i个只能交换一次的人的交换方案数
int main()
{
	int n = read(), cnt1 = 0; //cnt1表示只能交换一次的人的个数，不要和上文中的cnt混淆
	for(int i = 1; i <= n; i++) {
		cnt1 += !(read() - 1); //记录只能交换一次的人的个数
		//当read()=1时，read()-1=0，!(read()-1)为1，所以当read()为1时，cnt++
	}
	f[0] = f[1] = 1; f[2] = 2; //初始化
	for(int i = 3; i <= cnt1; i++) {
		f[i] = (f[i - 1] + f[i-2] * 1ll * (i - 1) % 1000000007) % 1000000007; //可以和自己玩，也可以找一个人玩
	}
	int s = 1; //s表示能交换两次的人的交换方案数
	for(int i = cnt1 + 1; i <= n; i++) { //除了cnt1个只能交换一次的人，其他都是能交换两次的人
		s = s * 1ll * i % 1000000007; //求阶乘
	}
	cout << s * f[cnt1] << endl; //最后的答案就是两种方案数的积
	return 0;
}
```


---

