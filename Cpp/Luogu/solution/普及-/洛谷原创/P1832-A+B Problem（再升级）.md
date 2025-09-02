# A+B Problem（再升级）

## 题目背景

题目名称是吸引你点进来的。

实际上该题还是很水的。


## 题目描述

- $1+1=?$ 显然是 $2$。
- $a+b=?$ P1001 回看不谢。
- 哥德巴赫猜想 似乎已呈泛滥趋势。

_以上纯属个人吐槽_

给定一个正整数 $n$，求将其分解成若干个素数之和的方案总数。



## 说明/提示

### 样例解释

存在如下三种方案：

- $7=7$。
- $7=2+5$。
- $7=2+2+3$。

### 数据范围及约定

- 对于 $30\%$ 的数据 $1\le n\le 10$。
- 对于 $100\%$ 的数据，$1\le n\le 10^3$。


## 样例 #1

### 输入

```
7```

### 输出

```
3```

## 样例 #2

### 输入

```
20```

### 输出

```
26```

# 题解

## 作者：hmh13951417981 (赞：194)

# 思想贴上：
## 既然说要都用素数，必须先筛出素数
## 如果是素数，就要判断是否取
## 每个素数可以无限取-->完全背包
## ~~记得结果会很大一定要开long long~~

------------

```c
#include<bits/stdc++.h>
using namespace std;
int i,j,n;
long long dp[1001];//dp数组存储第i个数的组成种数
bool b[1001];//b数组判断是否为素数
void prime(){
	for(i=2;i<=500;i++)
		if(!b[i])
			for(j=2;i*j<=1000;j++)
				b[i*j]=1;
}//筛法
int main()
{	prime();//预处理，筛出素数
	cin>>n;//输入
    //完全背包经典代码
	dp[0]=1;//边界值：当取数和为0时值为1
	for(i=2;i<=n;i++)//循环每个数取或不取
		if(!b[i])//是素数才能考虑是否能取
		for(j=i;j<=n;j++)//从i开始到n,因为你要得到的数肯定不小于取的数
			dp[j]+=dp[j-i];////取这个素数，则减去这个素数方案数累加到总方案数
	cout<<dp[n];//输出n的方案数
  	return 0;
}
```

---

## 作者：NaCly_Fish (赞：133)

来补一篇理论复杂度 $\Theta(n \log n)$ 的题解。

很容易想到问题转化：  
一个容积为 $n$ 的背包，有一些体积为素数的物品，都有无限个，求有多少种方法填满这个背包。  

朴素的 $\Theta(n^2)$ 做法是直接 DP，但是我们可以把每个物品的方案看成生成函数，再乘起来就是答案了。

暴力做多项式乘法是过不去的，把每个函数取 $\ln$，加起来再做 $\exp$ 就可以 $\Theta(n \log n)$ 搞定，详细解释见 [P4389](https://www.luogu.org/problem/P4389)。

由于 $n=1000$ 时答案就已经达到了 $10^{17}$ 量级，所以可以用两个模数，比如 $998244353$ 和 $1004535809$ 分别做一遍之后 CRT 即可。

参考代码 ( 只用了一个模数，并不能通过所有测试点 )：
```cpp
//orz zjx
//zjx ak ioi
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<ctime>
#define reg register
#define N 4099
#define LIM 4096
#define zjx 998244353
#define add(x,y) (x+y>=zjx?x+y-zjx:x+y)
#define dec(x,y) (x<y?x-y+zjx:x-y)
#define ll long long
#define clear(x) memset(x.a,0,sizeof(x.a))
using namespace std;

inline int power(int a,int t){
	int res = 1;
	while(t){
		if(t&1) res = (ll)res*a%zjx;
		a = (ll)a*a%zjx;
		t >>= 1;
	}
	return res;
}

struct poly{
	int a[N];
	int t;
	inline int operator [] (const int& x) const{ return a[x]; }
	inline int& operator [] (const int& x){ return a[x]; }
};

int rev[N],lg2[N],rt[N],irt[N],inv[N];

void init(){
	rt[0] = irt[0] = inv[1] = 1;
	for(reg int i=2;i!=N;++i){
		lg2[i] = lg2[i>>1]+1;
		inv[i] = (ll)(zjx-zjx/i)*inv[zjx%i]%zjx;
	}
	rt[1] = power(3,(zjx-1)/LIM);
	irt[1] = power(rt[1],zjx-2);
	for(reg int i=2;i!=LIM;++i){
		rt[i] = (ll)rt[i-1]*rt[1]%zjx;
		irt[i] = (ll)irt[i-1]*irt[1]%zjx;
	}
}

inline void NTT(poly &f,int type,int lim){
	reg int w,y,l = lg2[lim]-1;
	for(reg int i=1;i!=lim;++i){
		rev[i] = (rev[i>>1]>>1)|((i&1)<<l);
		if(i<rev[i]) swap(f[i],f[rev[i]]);
	}
	l = LIM>>1;
	for(reg int mid=1;mid!=lim;mid<<=1){
		for(reg int j=0;j!=lim;j+=(mid<<1)){
			for(reg int k=0;k!=mid;++k){
				w = type==1?rt[l*k]:irt[l*k];
				y = (ll)w*f[j|k|mid]%zjx;
				f[j|k|mid] = dec(f[j|k],y);
				f[j|k] = add(f[j|k],y);
			}
		}
		l >>= 1;
	}
	if(type==1) return;
	w = inv[lim];
	for(reg int i=0;i!=lim;++i) f[i] = (ll)f[i]*w%zjx;
}

poly inverse(poly f){
	poly g,h,q;
	clear(g);
	int lim = 1,n = f.t,top = 0;
	int s[30];
	while(n){
		s[++top] = n;
		n >>= 1;
	}
	g[0] = power(f[0],zjx-2);
	while(top--){
		g.t = n = s[top+1];
		q = g,h = f;
		for(reg int i=n+1;i<=f.t;++i) h[i] = 0;
		while(lim<=(n<<1)) lim <<= 1;
		NTT(g,1,lim),NTT(h,1,lim);
		for(reg int i=0;i!=lim;++i) g[i] = (ll)g[i]*g[i]%zjx*h[i]%zjx;
		NTT(g,-1,lim);
		for(reg int i=0;i<=n;++i) g[i] = dec(add(q[i],q[i]),g[i]);
		for(reg int i=n+1;i!=lim;++i) g[i] = 0;
	}
	return g;
}

inline poly deriv(poly f){
	for(reg int i=0;i!=f.t;++i) f[i] = (ll)f[i+1]*(i+1)%zjx;
	f[f.t] = 0;
	return f;
}

inline poly integ(poly f){
	for(reg int i=f.t;i;--i) f[i] = (ll)f[i-1]*inv[i]%zjx;
	f[0] = 0;
	return f;
}

poly log(poly f){
	poly g = deriv(f);
	f = inverse(f);
	int lim = 1;
	while(lim<=(f.t<<1)) lim <<= 1;
	NTT(f,1,lim),NTT(g,1,lim);
	for(reg int i=0;i!=lim;++i) f[i] = (ll)f[i]*g[i]%zjx;
	NTT(f,-1,lim);
	for(reg int i=f.t+1;i!=lim;++i) f[i] = 0;
	return integ(f);
}

poly exp(poly f){
	poly g,h;
	clear(g);
	int lim = 1,n = f.t,top = 0;
	int s[30];
	while(n){
		s[++top] = n;
		n >>= 1;
	}
	g[0] = 1;
	while(top--){
		g.t = n = s[top+1];
		h = g,g = log(g);
		for(reg int i=0;i<=n;++i) g[i] = dec(f[i],g[i]);
		g[0] = add(g[0],1);
		while(lim<=(n<<1)) lim <<= 1;
		NTT(g,1,lim),NTT(h,1,lim);
		for(reg int i=0;i!=lim;++i) g[i] = (ll)g[i]*h[i]%zjx;
		NTT(g,-1,lim);
		for(reg int i=n+1;i!=lim;++i) g[i] = 0;
	}
	return g;
}

int pr[N>>2];
bool vis[N];
int cnt;

inline void sieve(int n){
	for(reg int i=2;i<=n;++i){
		if(!vis[i]) pr[++cnt] = i;
		for(reg int j=1;j<=cnt&&i*pr[j]<=n;++j){
			vis[i*pr[j]] = true;
			if(i%pr[j]==0) break;
		}
	}
}

poly F;
int n;

int main(){
	init();
	scanf("%d",&n);
	sieve(n);
	for(reg int i=1;i<=cnt;++i)
		for(reg int j=1;pr[i]*j<=n;++j)
			F[pr[i]*j] = add(F[pr[i]*j],inv[j]);
	F.t = n;		
	F = exp(F);
	printf("%d",F[n]);
    return 0;
}
```

---

## 作者：Misaka19280 (赞：90)

###### 蒟蒻的第一篇题解
此题难度不大，可以联想到“[过河卒](https://www.luogu.org/problemnew/show/P1002)”（把二维改成一维，觉得楼下dalao解释成完全背包不是很清楚），过河卒中卒是从左边或上面来的，也就是f[i,j]是从f[i-1,j]或f[i,j-1]来的，所以f[i,j]=f[i-1,j]+f[i,j-1]，本题中步数不确定，f[j]是从f[j-i]（i为任意素数）来的，所以**f[j]=f[j]+f[j-i]**。
还有一个就是预处理素数，本题数据不大，埃氏筛可以满足。
注意！本题结果可能很大，一定要开qword，c++开long long。
---------------------------------------------------------------------------------------------------------------------------
                                 
```
Var
	f:array[0..1000]of qword;   //数据较大，开qword
	n,i,j:longint;
	sha:array[1..1000]of boolean;  //负责筛素数
	
Begin
	readln(n);
	fillchar(sha,sizeof(sha),true);
	for i:=2 to n do
		if sha[i] then 
			begin
				j:=i;
				while (j+i<=n) do      //蒟蒻用的埃氏筛
					begin
						j:=j+i;
						sha[j]:=false;
					end;
			end;
	f[0]:=1;  //这里注意一下，2、3这样的素数的f值从0来
	for i:=2 to n do
		begin
			if sha[i] then            //如果是素数，就累加
				for j:=i to n do
					f[j]:=f[j]+f[j-i];  //转移方程，第j个数从j-i来
		end;
	writeln(f[n]);
End.```

---

## 作者：Ajwallet (赞：58)

这题经过分析，可以看出是一个完全背包问题。

for i=1..sushu(n)   //sushu(n)表示1到n之间的素数个数

 for j=a[i]..n   //完全背包

f[j]=f[j]+f[j-a[i]];

最后的结果就是f[n]

代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#define read scanf //pascal后遗症
#define write printf //pascal后遗症
using namespace std;
int n,a[1005];
long long dp[1005];
int sushu(int x) //统计一到x之间的素数个数
{
    int flag[x+10];
    memset(flag,1,sizeof(flag));
    for(int i=2;i<=x;i++)
     {
         if (flag[i])
            for(int j=i*2;j<=x;j+=i)
             flag[j]=0;
     }
    int k=0;
    for(int i=2;i<=x;i++)    
     if (flag[i]) a[++k]=i;
    return k;
}
int main()
{
    memset(dp,0,sizeof(dp));
    dp[0]=1;//什么都不选
    read("%d",&n); //pascal后遗症
     for(int i=1;i<=sushu(n);i++)
      for(int j=a[i];j<=n;j++) 
       dp[j]+=dp[j-a[i]];
    write("%lld",dp[n]); //pascal后遗症
}
```

---

## 作者：单线程小伙 (赞：53)

###### 首先讲一下素数筛法，虽说这道题的数据不是很大，但是总有需要的时候，我们用一个数组，v[i]为真的时候代表不是素数，为假当然就是素数了。那么很显然，2x2，2x3，2x4……3x3，3x4……就都不是素数，我们就可以将其标为1.这样，我们只需要从2开始，走一遍程序，就可以得到所有的素数了。代码如下：
```cpp
int m=sqrt(n);
	for(int i=2;i<=m;i++)
	{
		if(!v[i])
		{
			for(int j=i;j<=n/i;j++)
			{
				v[i*j]=1;
			}
		}
	}
```
###### 其中的n就是题中的数据范围了。


###### 如果对背包熟悉的话，其实这就是一道类似于装箱问题的背包问题，其中正整数n是总容量，而不大于n的所有素数就相当于物品了，这样模型就抽象出来了，接下来，装箱问题已经明白的请自行忽略orz，

我们就对样例进行一下分析，看看究竟怎么实现；
n=7；所有的素数是2，3，5，7；
首先要明确的是0是初始状态（很重要），同时用ans[i]表示和为i的种类数，显然ans[i]=1.

第一步，就是对第一个素数2的操作，首先0就是初始状态，所以加上第一个素数就是2，所以ans[2]=1,再运行到和为2的时候再加上2就是4了(因为题目没有说素数不可以重复，所以同一个素数可以用多次，运行完之后和为0，2，4，6都有一种情况了)，所以ans[4]=1;如下所示

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 1 | 0 | 1 | 0 | 1 | 0 | 1 | 0 |

第二步，对第二个素数3的操作，类似于第一步，初始0，加上3，所以ans[3]=1,运行到2的时候，ans[5]=1,运行到3的时候ans[6]=1,运行到4的时候ans[7]=1,

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 1 | 0 | 1 | 1 | 1 | 1 | 1 | 1 |

第三步，同理把所有ans值为真的加上这个素数之后的数就会有一种新的拆分方法；

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 1 | 0 | 1 | 1 | 1 | 2 | 1 | 2 |

第四步，素数7

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 1 | 0 | 1 | 1 | 1 | 2 | 1 | 3 |

所以答案就愉快的出来了。

附上代码
```cpp
#include<iostream>
using namespace std;
bool f(int x){
	for(int i=2;i<x;i++){
		if(x%i==0){
			return 0;
		}
	}
	return 1;
}
long long ans[1005];
int main()
{
	int n;
	cin>>n;
	ans[0]=1;
	for(int i=2;i<=n;i++){
		if(!f(i)){
			continue;
		}
		for(int j=0;j<=n;j++){
			if(ans[j]&&j+i<=n){
				ans[j+i]+=ans[j];
			}
		}
	}
	cout<<ans[n];
}
```

需要说明的是，我自己写的时候没有用素数筛法，只是用了最朴素的方法，orz，如果有什么不对的可以在评论区提醒我一下哦，谢谢大家

---

## 作者：zoezoykit (赞：22)

显而易见，此题是一道背包题。

首先要注意：

### 若干个素数之和

所以，可以先筛出 $n$ 以下的所有素数。

### 下面进入入门级科普环节（神犇请忽略）：

这里提供几种筛法，请自行选择：

①欧拉筛
```cpp
for(int i=2;i<=n;i++) 
{
	if(!v[i]) 
	{
		p[++p[0]]=i;    //记录质数，p[0]用来计数 
	}
	for(int j=1;j<=p[0]&&i*p[j]<=n;j++) 
	{
    	v[i*p[j]]=1;	//把p数组中记录的素数，升序依次作为需消去的合数的最小质因子
    	if(!(i%p[j])) 		//若i为p[j]的倍数，则i=a*p[j]（a为常数），如果直接进入下一轮循环，j=j+1，i*p[j+1]=a*p[j]*p[j+1]，这里p[j]是最小的质因子，当i=a*p[j+1]时会重复，所以应该跳出循环
    	{
      		break;
    	}	
	}
}
```


②埃氏筛	
```cpp
for(int a=2;a<=sqrt(k);a++)				 
{
   	if(pd[a]==0)		//如果a是质数，那么a的所有倍数都不为质数
	{
   		for(int b=2;a*b<=k;b++)
   		{
   			pd[a*b]=1;
		}
	}
}
```
埃氏筛法的缺陷：对于一个合数，有可能被筛多次，浪费时间


③整数唯一分解定理：STL大法好

整数的唯一分解定理：一个大于1的整数一定可以被分解成若干质数的乘积。这个是数论知识，下面的代码基于这个定理，就不注释了

```cpp
vector<int> k;
for(int a=2;a*a<=m;a++)
{
	while(!(m%a))
	{
		k.push_back(a);
		m=m/a;
	}
}
if(m>1)
{
	k.push_back(m);
}
return k;
```

筛完质数，下面就是完全背包最为基础的版本。那么完全背包是什么呢？

### 下面进入普及级科普环节（神犇仍请忽略）：

与01背包一样，完全背包也是一个经典的动规问题，不同的地方在于01背包中，每件物品最多选择一件；而完全背包反之：只要装得下，每件物品可选择多件。所以解决策略已经不再是选或者不选的逻辑选择，而是取$n$（$0≤n≤\frac{T}{Vi}$）件。

~~但是完成这题似乎不需要理解那么多~~……

至于这题怎么用完全背包解决，已在代码后注释。

------------


Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

int k;

int main()
{   
    cin>>k;
    int pd[k+1];					//bool类型亦可 
    long long whole[k+1];			//不开long long见祖宗 
    
    memset(pd,0,sizeof(pd));
    memset(whole,0,sizeof(whole));
    whole[0]=1;						//这里必须要特殊赋边界值（属于完全背包的环节） 
    
	//筛法求素数（上文已述，请自行补充）
        
    for(int m=2;m<=k;m++)			//最基础的完全背包代码 
    {
    	if(pd[m]==0)			//与筛法求质数一样，判断是否为质数
    	{
    		for(int n=m;n<=k;n++)
    		{
    			whole[n]=whole[n]+whole[n-m];		//总数=当前一轮循环的总分解方式数+当前二轮循环质数减去一轮循环的单独分解方式数
			}
		}
	}
        
    cout<<whole[k];
    return 0;
}
```


---

## 作者：樱式分解 (赞：20)

### 这道题一开始我轻敌了，直接用了dfs。
#### 代码如下
```cpp
#include <iostream>
#include <cmath>
using namespace std;
int f[1010];
int ans=0;
bool zhu(int i){
	if(i==2)return true;
	for(int j=2;j<=sqrt(i);j++){
		if(i%j==0)return false; 
	}
	return true;
} 
void dfs(int i,long long sum){
	if(sum>n)return;
	if(sum==n){
	ans++;return;}
	else for(int j=i;j<=n-sum;j++){
		if(f[j])dfs(j,sum+j);
	} 
} 
int main(){
	cin>>n;
	for(int i=2;i<=n;i++){
		if(zhu(i))f[i]=true;
	}
	dfs(1,0);
	cout<<ans<<endl;
} 
```
### 结果爆掉了，真悲剧啊！
#### 于是我就改换动规思路，发现这是上星期刚学的背包。
#### 于是AC了。
```
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
int n;
long long f[1001];
int a[1001];
int t=0;
bool zhu(int i){//判断素数
	if(i==2)return true;
	for(int j=2;j<=sqrt(i);j++){
		if(i%j==0)return false;
	} 
	return true;
}
int main(){
	cin>>n;
	memset(f,0,sizeof(f));//全赋值为0；
	f[0]=1;//把零看作一种凑法；
	for(int i=2;i<=n;i++){
		if(zhu(i))a[++t]=i;把指数都装进去，就像背包里的物品
	}
	for(int i=1;i<=t;i++)
	for(int j=a[i];j<=n;j++){
	   f[j]+=f[j-a[i]];//看看有多少种凑法。
	}
	cout<<f[n]<<endl;//输出n的凑法
	return 0;
}
```
### 管理员求过
## 用心写题解，希望给大家带来点帮助呀！

---

## 作者：Julytree (赞：10)

膜楼下大佬orz……


这道题实际上就是求组成方案数。和完全背包的思路是一样的，只不过dp[]的含义由价值变为方案数之和。

状态转移方程：dp[i]=dp[i]+dp[i-比他小的素数]

关于判断哪些是素数，可以一开始打个表。用埃氏筛即可（每找到一个素数，它的倍数都去掉）。


注意：1.dp[0]=1。即什么都不选；

          2.dp数组要开long long;

一维代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
int n,a[1005]; 
long long dp[1005];
using namespace std;
int sushu(int x)
{
  int flag[x+10];
  memset(flag,1,sizeof(flag));    
  for(int i=2;i<=x;i++)
      if(flag[i])
        for(int j=i\*2;j<=x;j+=i)
          flag[j]=0;
  int sum=0;         
  for(int i=2;i<=x;i++)    
    if(flag[i]) a[++sum]=i;
    
  return sum;  
}
int main()
{
  memset(dp,0,sizeof(dp));
  dp[0]=1;//什么都不选
  scanf("%d",&n);
  for(int i=1;i<=sushu(n);i++)
    for(int j=a[i];j<=n;j++)//完全背包的正循环
      dp[j]=dp[j]+dp[j-a[i]];
      
   printf("%lld",dp[n]);   
return 0;
}
···

---

## 作者：ylch (赞：5)

别的大佬们都用完全背包做的，蒟蒻（我）提供一种添加限制的方法。

## Analysis

开始会想到枚举小于 $n$ 的每个素数为基础进行分解。

设 $f(m)$ 表示将 $m$ 拆分成素数的方案数，则对于 $n$，可以分解为一些类似 $n=prime_i+f(n-prime_i)$ 的方案。但这样会有重复，比如分解 $10$：

$10=2+f(8)$

$10=3+f(7)$

$10=5+f(5)$

$10=7+f(3)$

发现 $3+f(7)$ 和 $7+f(3)$ 明显存在方案数上的重复（重复一直是求方案数这一类问题的主要错误点之一）。


------------

在做计数类题目的时候，有一种常用的方法，即给函数添加一个限制条件，以保证枚举全的情况下避开重复的情况。

不妨设 $f(m,l)$ 表示以小于等于 $l$ 的数拆分 $m$ 的方案数。

那么对 $10$ 的分解如下：

$10=2+f(8,2) \rightarrow 2+2+2+2+2=10$

$10=3+f(7,3) \rightarrow 3+3+2+2=10$

$10=5+f(5,5) \rightarrow 5+5=10\ \operatorname{and}\ 5+3+2=10$

$10=7+f(3,7) \rightarrow 7+3=10$

这样五种策略都凑齐了，再验证几个数字，发现都是正确的。

这样为什么是对的？

答：因为我们加了小于等于 $l$ 的限制，这样可以使枚举的所有方案都是升序的，不会出现重复（和进行 dfs 爆搜的结果顺序一样）。

## Code

代码实现：先筛素数，然后用记忆化搜索进行动态规划。递归的终止条件是 $m=0$，表示分解成功，返回 $1$；否则返回所有分解的方案数之和。

这样的时间复杂度约为 $\text{O}(\frac{n^3}{\log_2 n})$，虽然没有背包快，但通过本题也是足够的。

> 十年 OI 一场空，不开 long long 见祖宗。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 7;

int prime[maxn], cnt; // 存储素数的数组、数组长度的指针
int vis[maxn]; // 筛素数的数组

void getPrime()
{
    for(int i = 2; i < maxn; i ++){
        if(!vis[i]){
            prime[cnt ++] = i;
            for(int j = 2 * i; j < maxn; j += i) vis[j] = 1;
        }
    }
}

ll f[1010][1010];
ll dfs(int m, int l) // 以小于等于l的素数拆分m的方案数
{
    if(m == 0) return 1; // 如果减到0了，证明可以成功分解
    if(f[m][l] != -1) return f[m][l];
    f[m][l] = 0; // 初始化为0，不然会累加上-1
    for(int i = 0; prime[i] <= l && prime[i] <= m; i ++){ // 枚举小于l和m的，不然会把m减出负数
        f[m][l] += dfs(m - prime[i], prime[i]);
    }
    return f[m][l];
}

signed main()
{
    getPrime();
    memset(f, -1, sizeof f);
    int n;
    cin >> n;
    cout << dfs(n, n) << endl;
    return 0;
}
```

---

## 作者：jokers (赞：5)

思路清奇

这题就是打表找素数然后一个完全背包

重点是这个完全背包的理解

感觉几篇题解说  DP[0]=1这个是什么都不取不太好

个人理解是为了之后的操作

因为要的是方案数 所以f[i]存的不是价值而是数目

把转移方程 DP[i]+=DP[i-prime[j]]这里prime是素数 和DP[0]=1一起看

可以说DP[0]=1是为了辅助这个方程的

# 推理一波

当i较小时  i可能会减掉prime[j]后直接等于0 

这时DP[0]会给DP[i]加一个1  表示一种素数和为i的方案 

所以当prime[j]变化时   DP[i]的方案就会不断增加

## 总结来说 当i较小时DP[0]=1会不断给DP[i]++
## 表示有多少种方案可以由i减到0

由此可得

当i较大时  

DP[i]+=DP[i-prime[j]]就表示i有多少种方法减到i-prime[j]

又因为DP[i-prime[j]]表示i-prime[j]有多少种方案减到0

就是一个动规的过程

# 然后上代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
const int maxn=1010;
using namespace std;
long long f[maxn];
int n,prime[maxn];
int tot=0;
bool su[maxn];
int read(){
	char c=getchar();
	int x=0;
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+c-'0',c=getchar();
	return x;
}
void prime_do(){
    //一波欧筛装一装
    //看不懂可以去看别的题解的埃筛
	su[1]=1;
	for(int i=2;i<=n;i++){
		if(!su[i]) prime[++tot]=i;
		for(int j=1;j<=tot&&prime[j]*i<=n;j++){
			su[i*prime[j]]=1;
			if(i%prime[j]==0) break;
		}
	}
	return;
}
int main(){
	n=read();
    //read是读入优化可以用cin或scanf都行
	memset(f,0,sizeof(f));
	memset(su,0,sizeof(su));
	memset(prime,0,sizeof(prime));
    //初始化数组
	prime_do();
    //打出素数表
	f[0]=1;
	for(int i=1;i<=tot;i++)
	  for(int j=prime[i];j<=n;j++)
	    f[j]+=f[j-prime[i]];
	printf("%lld",f[n]);
    //这里数据很大所以要开long long
	return 0;
}
```

---

## 作者：ww3113306 (赞：4)

一道完全背包+筛素数。

这里强推线性筛，虽然这个数据范围不用也可以

```cpp
#include<bits/stdc++.h>
using namespace std;
int have[1010],tot,n;long long f[1010];bool z[1010],zx=false;
void sun(int x)//线性筛
{
    int i,j;
    for(i=2;i<=n;i++)
    {
        if(!z[i]) //如果是素数，就存入have数组
        {
            tot++;
            have[tot]=i;
        }
        j=1;
        while(i%have[j]!=0&&j<=tot)
```
不论是否是素数，都要依次乘have数组里的素数，直到遇到一个可以被i整除的数
```cpp
        {
            if(i*have[j]>n)
            {
                zx=true;
                break;
            }
            z[i*have[j]]=true;
            j++;
        }
        if(i%have[j]==0&&j<=tot)相当于一个特判，
```
因为第一个可以被i整除的数其实还是要乘的，
不过是最后一个乘的数罢了

```cpp
            if(i*have[j]<=n)z[i*have[j]]=true;
    }
}
int main()
{
    int i,j;
    memset(z,0,sizeof(z));
    scanf("%d",&n);
    if(n==1)
    {
        printf("0");
        return 0;
    }
    sun(n);
    f[0]=1;
    for(i=1;i<=tot;i++)//注意，枚举素数放在前面，下面枚举数字相当于完全背包的容量，而素数则是物品，所以物品在前 
        for(j=have[i];j<=n;j++)
            f[j]+=f[j-have[i]];
    printf("%lld",f[n]);    
    return 0;
}
```

---

## 作者：开挂老司机 (赞：4)

此题其实就是
# 完全背包！
思路：

首先找出1到n之间的所有素数（筛表），再用背包一步步找出将n分解成若干个素数之和的方案总数就行。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	bool t[1001]={0};
	int a[1001],step=0,n;
	long long f[1001]={0};//dp数组需用long long
	cin>>n;
	t[1]=true;//1不是素数！
	for(int i=2;i<=sqrt(n);i++)
	  if(!t[i])
		for(int j=2;j<=n/i;j++)
		  t[i*j]=true;//筛表法
	f[0]=1;
	for(int i=2;i<=n;i++)
	  if(!t[i])
	  	a[++step]=i;//记录1..n之间的所有素数
	for(int i=1;i<=step;i++)
	  for(int j=a[i];j<=n;j++)
	    f[j]+=f[j-a[i]];//完全背包
	cout<<f[n]<<endl;//输出
	return 0;
}

```

---

## 作者：_maze (赞：2)

很显然这道题是一道完全背包，只是背包的体积与价值都变成了素数

所以就用一个最朴素的循环素数就可以了，加个sqrt小小的优化。接下来我们来推一推状态转移方程：

```cpp
dp[j]=dp[j]+dp[j-a[i]];
```

01背包压缩到一维数组大家都会吧，于是这个代码就呼之欲出了！

```cpp
#include<bits/stdc++.h>
#define chen xiaoke is so cute 
using namespace std;
long long dp[10001],n,a[10001],v,he=0,number[10001]; 
int pd(int n){//判断素数 
    if(n<2) return 0;//特判一下 
    for(int i=2;i<=sqrt(n);i++) if(n%i==0) return 0;//直接返回 
    return 1;
}
int main()
{
    cin>>n;//输入 
    for(int f=2;f<=n;f++){
        if(pd(f)==1){
        	he++;
        	a[he]=f;//储存素数 
        }
    }
    dp[0]=1;//初始化 
    for(int i=1;i<=he;i++){//从1到he逐个枚举 
        for(int j=a[i];j<=n;j++){//完全背包板子不解释 
            dp[j]=dp[j]+dp[j-a[i]];//逐个加上之前的情况 
        }
    }
    cout<<dp[n];//输出 
    return 0;//完美结束？ 
}
```


---

## 作者：titititing (赞：2)

此题打下一个素数表




```cpp
var
  n,i,j,ans:longint;
  a,f:array[0..1005]of int64;
function pd(x:longint):boolean;素数表构造部分，只用判断1-1000就够了
var
  i:integer;
begin
  for i:=2 to trunc(sqrt(x)) do
    if x mod i=0 then
      exit(false);
  exit(true);
end;
begin
  readln(n);
  for i:=2 to 1000 do
  begin
    if pd(i) then
    begin
      inc(j);
      a[j]:=i;
    end;
  end;
```
有没有发现打完素数表和背包问题很像？
没错，就是完全背包。


```cpp
  f[0]:=1;
  for i:=1 to n do
  begin
    if a[i]<>0 then
    for j:=a[i] to n do仔细分析后得出的状态转移方程为f[j]:=f[j]+f[j-a[i]]
      f[j]:=f[j]+f[j-a[i]];
  end;
  writeln(f[n]);答案输出
end.

```

---

## 作者：xuan__xuan (赞：2)

首先你要一个素数表，然后用背包，怎么背包就不讲了，反正就是求方案总数嘛，还有，数量没有限制，所以记得要正着搜


```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
const int MAXN = 10001;
long long int prime[MAXN],num,Q;
long long int P[MAXN];
long long int F[10001];
void p(){
    for(int i = 2; i < 10001; i++)
    {
        if(P[i] == 0)
        {
            P[i] = 1,prime[++num]  = i;
            for(int j = i * i; j < 10001;j+=i)
                P[j] = 1;
        }
    }
}
int main(){
    scanf("%lld",&Q);
    p();
    F[0] = 1;
    for(int i = 1; (prime[i] <= Q && i <= num); i++)
        for(int V = prime[i]; V <= Q; V++)
        {
            F[V] += F[V-prime[i]];
        } 
    cout << F[Q] << endl;
    return 0;
}//一开始没开longlong被卡了
```

---

## 作者：H15teve (赞：2)




```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
long long f[1001];
bool prime[1001];
int main()
{
    int n;
    memset(prime,true,sizeof(prime));
    memset(f,0,sizeof(f));
    f[0]=1;f[1]=0;
    cin>>n;
    for (int i=2;i<=(int)sqrt(n);i++)
      if (prime[i]) for(int j=2;j<=n/i;j++) prime[i*j]=0;//用的是埃拉托斯特尼筛法
    for (int i=2;i<=n;i++)
      if (prime[i]) for (int j=i;j<=n;j++)
          {
              f[j]+=f[j-i];//递推公式没什么好说的
              //cout<<i<<' '<<j<<' '<<f[j]<<endl;
        }
    cout<<f[n];
    return 0;
}
```

---

## 作者：usqwedf (赞：2)

[Problem 系列题 I]

[A+B Problem]

思路：

设f[i]表示组成i的方案总数

显然我们可以得到递推公式 f[i]=f[i]+f[i-j] (i<=j<=n 且 i为质数)

```delphi

var  
  n,i,j:longint;  
  a:array[0..1001] of boolean;  
  f:array[0..1001] of int64;  
begin  
  readln(n);  
  fillchar(a,sizeof(a),true);  
  for i:=2 to trunc(sqrt(n)) do  
    if a[i] then for j:=2 to n div i do a[i*j]:=false;  
  f[0]:=1;  
  for i:=2 to n do   
    if a[i] then   
      for j:=i to n do f[j]:=f[j]+f[j-i];  
  writeln(f[n]);  
end.
```

---

## 作者：eaten_apple (赞：2)

## 刚看到这道题，内心狂喜，什么？A+BProblem？
### 然鹅，一秒后，崩了
于是，开始愉快的完全背包吧！

先搞一个判断质数的函数，然后在主函数里进行完全背包。

好吧，我承认，做出来这道题后，我发现其实是~~一道水题~~。。。。。。
```cpp
#include<bits/stdc++.h>
using namespace std;
int prime[1005];
bool check(int x)//判断质数 
{
	for(int i=2;i<=sqrt(x);i++)//i的范围 
	{
		if(x%i==0)
			return false;//x不是质数 
	}
	return true;//质数 
}
int main()
{
	int n,ans=0;
	long long dp[1005]={0};//dp[i]凑出整数i的方法数 
	//本题数据很大，要开long long 
	cin>>n;
	for(int i=2;i<=n;i++)
	{
		if(check(i)==true)
		{
			ans++;//质数计数器 
			prime[ans]=i;
		}
	}
	dp[0]=1;//dp初始化 
	//开始完全背包 
	for(int i=1;i<=ans;i++)//物品 
	{
		for(int j=prime[i];j<=n;j++)//容量，数字 
		{
			dp[j]=dp[j]+dp[j-prime[i]];
		}
	}
	cout<<dp[n]<<endl;//输出 
	return 0;//结束 
}
```


---

## 作者：yyy14159 (赞：2)

本蒟蒻看到dp就有点方...

不过这道题数据范围不是很大，不需要什么nb的思路，先做出一个素数表，然后就是完全背包问题了，素数表用埃氏筛啊，线性筛啊都可以的吧。然后dp采用一维滚动数组比较节约空间。

    
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
long long dp[1003];
bool prime[1003];
int list[1003];
int n;
int main()
{
    memset(prime,1,sizeof(prime));
    scanf("%d",&n);
    prime[1]=0;
    for(int i=2;i<=sqrt(n);i++)
    {
        if(prime[i])
        {
            int x=i<<1;
            while(x<=n)
            {
                prime[x]=0;
                x+=i;
            }
        }
    }
    int k=1;
    for(int i=1;i<=n;i++)
    if(prime[i])    list[k++]=i;
    dp[0]=1;
    for(int i=1;i<k;i++)
    {
        for(int j=0;j<=n;j++)
        {
            if(j>=list[i])    dp[j]=dp[j]+dp[j-list[i]];
            //cout<<dp[j]<<" ";
        }
        //cout<<endl;
    }    
    /*for(int i=1;i<k;i++)
    {
        for(int j=1;j<=n;j++)
        cout<<dp[j]<<" ";
        cout<<endl;
    }*/
    cout<<dp[n]<<endl;
    return 0;
}
```

---

## 作者：cxy004 (赞：2)

看成完全背包变种

每个素数都是一个物品

求背包方案总数（背包九讲第九讲：一般只需将状态转移方程中的max改成sum即可）

还有要用long long（int64） //表被printf坑了还用高精呵呵

```cpp
#include<cstdio>
#include<cmath>
using namespace std;

int n;
long long f[1001]={1};

bool ss(int m) //判断素数
{if(m>3) for(int i=sqrt(m);i>=2;--i) if(!(m%i)) return false;return true;}

int main()
{
    scanf("%d",&n);
    for(int i=2;i<=n;++i) if(ss(i)) for(int j=i;j<=n;++j) f[j]+=f[j-i];
    printf("%I64d",f[n]);
    return 0;
}
```

---

## 作者：于丰林 (赞：1)

一道简单题。。。

确实挺简单的，但是这道题把很多知识点结合的特别好。。。

虽然简单但是还是比较值得去做一下的。。。

这道题首先我们看到了方案总数，那么显然就是动态规划了。。。

那么这道题怎么做呢？

考虑一下我们分解n所得到的数都是质数，而且可以相等！！！（我就因为这个卡了！！！），那么我们就是从小于n的质数表（由于情怀我选择线性筛）中找出若干个数（可以重复），使得它们的相加和等于n。

欸？听着这么耳熟？

无限选取？选与不选？动规？

裸的完全背包啊！！！

所以我们得到动态转移方程：f[j]=f[j]+f[j-c[i]]

还是比较好理解的，我们对于每一个物品都要枚举j，那么我们就要加上之前得到的结果（简单的加法原理）

f[0]=1显然只有全都不取一种情况。。。

最后，附上本题代码：

```cpp
#include<cstdio>
#include<algorithm>
#define maxn 1000
#define LL long long
using namespace std;

LL n,prime[maxn+5],cnt,f[maxn+5];
bool vis[maxn+5];

void pre_fir()
{
    for(int i=2;i<=n;i++)
    {
        if(vis[i]==0)
        {
            prime[++cnt]=i;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++)
        {
            vis[i*prime[j]]=1;
            if(i%prime[j]==0)
            {
                break;
            }
        }
    }
}
int main()
{
    scanf("%lld",&n);
    pre_fir();
    f[0]=1;
    for(int i=1;i<=cnt;i++)
    {
        for(int j=prime[i];j<=n;j++)
        {
            f[j]+=f[j-prime[i]];
        }
    }
    printf("%lld\n",f[n]);
    return 0;
}
```


---

## 作者：yz0414 (赞：1)

这题就是完全背包啦

至于是不是质数，只要筛法求一下就可以了

初始：f[0]:=1;

状态转移方程：f[i]:=f[i]+f[i-j]

思路：先用筛法求一遍素数，再过一遍完全背包，如果是素数就做一遍加进来，最后输出总个数就可以了，大家一定已经懂了吧，下面附上超短代码：

```pascal
var n,i,j:longint;
    b:array[1..1000]of boolean;
    f:array[0..1000]of int64;
begin
   for i:=2 to 500 do
     if b[i]=false then
      for j:=2 to 1000 div i do
        b[i*j]:=true;
   readln(n);
   f[0]:=1;
   for i:=2 to n do
     if b[i]=false then
      for j:=i to n do
        f[j]:=f[j]+f[j-i];
   writeln(f[n]);
end.
```
第一遍交题解是说字数不够，所以在此稍微凑一点字数，嘻嘻~~


---

