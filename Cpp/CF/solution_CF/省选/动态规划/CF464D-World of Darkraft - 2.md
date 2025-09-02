# World of Darkraft - 2

## 题目描述

Roma found a new character in the game "World of Darkraft - 2". In this game the character fights monsters, finds the more and more advanced stuff that lets him fight stronger monsters.

The character can equip himself with $ k $ distinct types of items. Power of each item depends on its level (positive integer number). Initially the character has one $ 1 $ -level item of each of the $ k $ types.

After the victory over the monster the character finds exactly one new randomly generated item. The generation process looks as follows. Firstly the type of the item is defined; each of the $ k $ types has the same probability. Then the level of the new item is defined. Let's assume that the level of player's item of the chosen type is equal to $ t $ at the moment. Level of the new item will be chosen uniformly among integers from segment \[ $ 1 $ ; $ t+1 $ \].

From the new item and the current player's item of the same type Roma chooses the best one (i.e. the one with greater level) and equips it (if both of them has the same level Roma choses any). The remaining item is sold for coins. Roma sells an item of level $ x $ of any type for $ x $ coins.

Help Roma determine the expected number of earned coins after the victory over $ n $ monsters.

## 样例 #1

### 输入

```
1 3
```

### 输出

```
1.0000000000
```

## 样例 #2

### 输入

```
2 1
```

### 输出

```
2.3333333333
```

## 样例 #3

### 输入

```
10 2
```

### 输出

```
15.9380768924
```

# 题解

## 作者：shao0320 (赞：7)

#### 题目大意

$\mathrm{Roma}$ 在游戏“World of Darkraft”（理论上应该是 World of darkcraft，MineCraft 的一个版本）找到一个新角色。$ \mathrm{Roma}$ 有 $k$ 种装备，一开始每种装备各有 $1$ 个，且每种装备的初始等级均为 $1$。游戏中可以靠打怪来获取新装备，总共有 $n$ 只怪兽，每打赢 $1$ 只怪兽后，$\mathrm{Roma}$ 会随机获得一种装备 $a\ (a\in [1,k])$，假设原有的 $a$ 装备的等级为 $t$，那么新获得的装备的等级为 $[1,t+1]$，$\mathrm{Roma}$ 会将新获得的装备和原来的装备中等级较高的装备留下，等级较低的装备卖出，卖出可获得的金币为该装备的等级。 问打完这 $n$ 只怪兽后，$\mathrm{Roma}$ 获得的金币的期望。 $(1 \le n \le 10^5,1\le k \le 100)$

分析：

由于这$k$种装备毫无区别，因此可以先算出一种装备的期望再乘$k$

考虑$dp$,设当前用了$i$次机会,装备最高等级为$j$的期望赚钱数目是$f(i,j)$，注意到这样做需要考虑到目前状态的概率，但如果我们反着做的话，也就是还剩$i$次机会，当前最高等级为$j$的期望是$f(i,j)$的话，就不需要考虑$state(i,j)$的概率了。

考虑$f(i,j)$的转移，它有可能是三种情况：



$1$、爆出了新装备，也就是$j+1$级的新装备，这种情况有$\frac{1}{(j+1)*k}$的概率，有$j$的收益（把当前这把剑卖掉）

$2$、爆出来这种类型的旧装备，这种情况有$\frac{j}{(j+1)*k}$的概率，期望是$\frac{\sum^{x\leq j}_{x=1}x}{j}=\frac{j+1}{2}$。

$3$、爆出了其他装备，有$\frac{k-1}{k}$的概率，没有收益

然后就可以$O(N^2)$转移了。

但是这里有一个问题，当$i$过大时，$j$也可以取很大的值。

但是由$j$级升级到$j+1$级的概率是$\frac{1}{(j+1)*k}$，因此也就是说期望次数是$(j+1)*k$次，也就是说升到$s$级的期望次数是$\sum^{j\leq s}_{j=2}j$次，而这个次数是要小于$n$的，如果概率太小就在容错范围内了。

因此$s$取$1000$即可通过此题。

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n;
double k,f[2][1005];
int main()
{
	cin>>n>>k;
	int cur=1;
	for(int i=1;i<=n;cur^=1,i++)
	{
		for(int j=0;j<=1000;j++)
		{
			f[cur][j]=0.0;
			f[cur][j]+=(f[cur^1][j+1]+j)/((j+1)*k);
			f[cur][j]+=(f[cur^1][j]+(j+1)/2.0)*j/((j+1)*k);
			f[cur][j]+=(f[cur^1][j])*(k-1)/k;
		}
	}
	printf("%.12lf\n",f[cur^1][1]*k);
	return 0;
}
```





---

## 作者：EricQian (赞：4)

[CF464D World of Darkraft - 2](https://www.luogu.com.cn/problem/CF464D)

**update on 2022.7.24：更新了一处公式**

为什么没有人正着推啊啊啊！！！

$\bigstar$ 发现 $k$ 种装备一点区别都没有，可以计算一种装备的期望再乘 $k$。

（设这个幸运的装备编号为 $p$，为了方便表述）

设 $f_{i,j}$ 表示抽卡 $i$ 次后 $p$ 装备等级为 $j$ ，卖出这种装备的期望收益；$p_{i,j}$ 表示抽卡 $i$ 次后 $p$ 装备等级为 $j$ 的概率。

我们分类讨论列出转移方程（**注意期望的转移要乘上转移概率，而新加入的贡献要乘上转移概率和状态概率！！！**）：

+ 如果这一次得到的装备是 $p$，但等级在 $[1,j]$ 之间，从 $(i-1,j)$ 转移来：
    $$
    p_{i,j}\leftarrow p_{i-1,j}\times \frac{1}{k}\times \frac{j}{j+1}\\
    f_{i,j}\leftarrow \left(f_{i-1,j}\times \frac{1}{k}\times \frac{j}{j+1}\right)+\left(\frac{j\times (j+1)}{2}\times p_{i-1,j}\times \frac{1}{k}\times \frac{j}{j+1}\right)
    $$

+ 如果这一次得到的装备是 $p$，而且等级为 $j+1$，从 $(i-1,j-1)$ 转移而来：（注意由于上一个是 $j-1$，所以选中 $(j-1)+1=j$ 的概率为 $\frac{1}{j}$ ）
    $$
    p_{i,j}\leftarrow p_{i-1,j-1}\times \frac{1}{k}\times \frac{1}{j}\\
    f_{i,j}\leftarrow \left(f_{i-1,j-1}\times \frac{1}{k}\times \frac{1}{j}\right)+\left(j\times p_{i-1,j-1}\times \frac{1}{k}\times \frac{1}{j}\right)
    $$

+ 如果得到的装备不是 $p$，从 $(i-1,j)$ 转移来：
    $$
    p_{i,j}\leftarrow p_{i-1,j}\times \frac{k-1}{k}\\
    f_{i,j}\leftarrow f_{i-1,j}\times \frac{k-1}{k}
    $$

那么直接转移即可，最终答案就是 $k\times \sum_{i=1}^n f_{n,i}$，但是这样是 $\mathcal{O(n^2)}$ 的。

忽然发现每次升级的概率是 $\frac{1}{k\times (j+1)}$，在等级比较高的时候概率非常小，而且是保留小数？！！

那么钦定最大等级为 $s=600$ 时就可以啦？允许精度误差哦！

```cpp
// Author:A weak man named EricQian
#include<bits/stdc++.h>
using namespace std;
#define Maxs 1005
int n,opt;
double ans,k,f[2][Maxs],p[2][Maxs],sum[2][Maxs];
int main()
{
	scanf("%d%lf",&n,&k),p[0][1]=1;
	for(int i=1;i<=n;i++)
	{
		opt^=1;
		double p1,p2,p3;
		for(int j=1;j<=600;j++)
		{
			p1=1.0/k*(1.0*j)/(1.0*j+1.0);
			p2=1.0/k/(1.0*j);
			p3=(k-1.0)/k;
			p[opt][j]=p[opt^1][j]*p1+p[opt^1][j-1]*p2+p[opt^1][j]*p3;
			f[opt][j]=p1*(f[opt^1][j]+p[opt^1][j]*(j+1)/2.0)+
				p2*(f[opt^1][j-1]+p[opt^1][j-1]*(1.0*j-1.0))+
				p3*f[opt^1][j];
		}
	}
	for(int i=1;i<=1000;i++) ans+=k*f[opt][i];
	printf("%.10lf\n",ans);
	return 0;
}
```

---

## 作者：chihik (赞：4)


首先明确一点，所有装备的期望相同，只需求出任意一种后答案乘 $k$ 即可。

令 $dp[i][j]$ 表示还需要打 $i$ 只怪，装备等级为 $j$ 的金币数量期望。

那么有三种情况：

1.得到的并不是当前类型装备，概率为 $\frac{k-1}{k}$，这种情况下你一分钱也得不到。

2.得到当前装备的 $j+1$ 级，概率为 $\frac{1}{k} \times \frac{1}{j+1}$，然后你可以得到 $j$ 元。

3.得到当前装备的 $[1,j] $ 级 ，概率为 $\frac{1}{k} \times\frac{j}{j+1} $。

此时金币的期望为 $\sum_{i=1}^{j} i \times\frac{1}{j}=\frac{\frac{j \times (j+1)}{2}}{j}=\frac{j+1}{2}$。

用滚动数组优化一下，这样可以 $n^2$ 转移。

但是 $n \le 10^5$ ， 我们得优化一下。

我们要相信 $\mathrm{Roma}$ 跟我一样非，装备等级不会太高。

理性计算一下：

由上面分析可得，装备由 $j$ 级 到 $j+1$ 级的概率为 $\frac{1}{k \times(j+1)}$ ，那么期望次数为 $k \times(j+1)$

记期望最高等级为 $l$，那么 $2k+3k+...+lk \le n$

解得：

$$l < \sqrt{\frac{2(n+1)}{k}}$$

理论上开 $500$ 即可，但这样有 $0.0000002$ 的误差，开 $525$ 即可。

```cpp
#include <cstdio>

const int MAXN = 525;
int n , k;
double dp[ 2 ][ MAXN + 5 ];

int main( ) {
    scanf("%d %d",&n,&k);
    
    for( int i = 1 ; i <= n ; i ++ )
        for( int j = 1 ; j <= MAXN ; j ++ )
            dp[ i & 1 ][ j ] = ( dp[ ( i - 1 ) & 1 ][ j ] * ( ( k - 1 ) * 1.0 / k ) + ( dp[ ( i - 1 ) & 1 ][ j + 1 ] + j ) * ( 1.0 / ( k * ( j + 1 ) ) ) + ( dp[ ( i - 1 ) & 1 ][ j ] + ( 1 + j ) / 2.0 ) * ( j * 1.0 / ( k * ( j + 1 ) ) ) );
    
    printf("%.10f\n", dp[ n & 1 ][ 1 ] * k );
    return 0;
}
```


---

## 作者：Acc_Robin (赞：3)

[题目链接](https://www.luogu.com.cn/problem/CF464D)

为了方便叙述，下面的内容以 $m$ 代替题目中的 $k$。

由于期望的线性性，我们可以单独考虑 $1$ 个装备的期望，再乘以 $m$ 即可。

那么思路就很明显了：

令 $f[i][j]$ 表示还剩 $i$ 个怪兽没打，当前等级为 $j$ 级时的期望收益。

分个类（用全概率公式）：

- 有 $\frac {m-1}m$ 的概率抽到其他的装备，此时的贡献是

$$
\frac {m-1}mf[i-1][j]
$$

- 有 $\frac 1m $的概率抽到这件装备

	- 此情况下有 $\frac 1{j+1}$ 的概率抽到 比当前等级高的装备，贡献为 
    $$
    f[i-1][j+1]+j
    $$
    
    - 有 $\frac j{j+1}$ 的概率抽到等级更低的，枚举那个等级，可以得到
    
    $$
    \frac {(j+1)j}2+j\cdot f[i-1][j]
    $$

化简柿子，最终有

$$
f[i][j]\leftarrow \frac {(mj+m-1)\cdot f[i-1][j] + f[i-1][j+1]+\frac {(j+3)\cdot j}2}{m\cdot (j+1)}
$$

可以滚动数组优化空间到 $O(n)$，但时间是 $O(n^2)$ 的。

考虑为什么题目要用浮点数，浮点数可以在精度范围内胡搞。

对于某一件装备，它从 $x$ 级升到 $x+1$ 级的概率为 $\frac{1}{m(x+1)}$，由几何分布可知期望次数为 $m(x+1)$ 次。

那么一件装备从 $1$ 级升级到 $x$ 级的期望次数就是 
$$
2m+3m+\cdots +(x+1)m \approx \frac 12x^2m
$$

令 
$$
\frac 12x^2m\le n
$$

解得

$$
x\le \sqrt{\frac {2n}m} < 500
$$

于是我们只要给 $m$ 一个合适的上界来满足精度即可，我使用的是 $1000$。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Acc{
	const int N=1e3;
	using db=double;
	db dp[2][N],*f,*g;
	int n,m,i,j;
	void work(){
		cin>>n>>m,f=dp[0],g=dp[1];
		for(i=1;i<=n;++i,swap(f,g))
			for(j=1;j<N;++j)
				f[j]=((m*j+m-1)*g[j]+g[j+1]+(j+3)*j/2.)/((j+1.)*m);
		cout<<fixed<<setprecision(10)<<g[1]*m<<'\n';
	}
}
int main(){return Acc::work(),0;}
```

---

## 作者：daniEl_lElE (赞：1)

观察到有容错范围，容易发现最终装备的等级大概率不会很高。取一个阈值 $B=800$。

容易发现每种装备等价且独立，只需要考虑一种装备。考虑 $g_{i,j}$ 表示打了 $i$ 个怪兽，装备目前等级为 $j$ 的概率，$f_{i,j}$ 表示打了 $i$ 个怪兽，装备目前等级为 $j$ 的情况下得到金币数的期望。转移的时候分以下几类考虑：

* 选择了其他装备；
* 选择了这个装备，但是等级小于等于 $j$；
* 选择了这个装备，且等级等于 $j+1$。

最后答案就是 $k\sum_{i=1}^{B}f_{n,j}$。注意要滚动数组，时间复杂度 $O(nB)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define min(i,j) ((i<j)?i:j)
#pragma GCC optimize(2,3,"Ofast","inline")
using namespace std;
double f[2][1001],g[2][1001],tot[100005];
signed main(){
	int n,k; cin>>n>>k;
	g[0][1]=1;
	for(int i=1;i<=n;i++){
	    memset(f[i&1],0,sizeof(f[i&1]));
	    memset(g[i&1],0,sizeof(g[i&1]));
		for(int j=1;j<=800;j++){
			g[i&1][j]+=g[(i&1)^1][j]*(j*1.0/(j+1))*1.0/k+g[(i&1)^1][j]*(k-1)*1.0/k;
			f[i&1][j]+=f[(i&1)^1][j]*(j*1.0/(j+1))*1.0/k+g[(i&1)^1][j]*(j*1.0/2)*1.0/k+f[(i&1)^1][j]*(k-1)*1.0/k;
			g[i&1][min(j+1,800ll)]+=g[(i&1)^1][j]/(j+1)*1.0/k;
			f[i&1][min(j+1,800ll)]+=f[(i&1)^1][j]/(j+1)*1.0/k+g[(i&1)^1][j]/(j+1)*j*1.0/k;
		}
	}
	double tot=0;
	for(int i=1;i<=800;i++) (tot+=f[n&1][i]);
	cout<<fixed<<setprecision(10)<<tot*k;
	return 0;
}
```

---

## 作者：RedLycoris (赞：1)

题目大意：

一款游戏中有 $k$ 种装备，你一开始每种装备各有 $1$ 个，且每种装备的初始等级均为 $1$。游戏中可以靠打怪来获取新装备，总共有 $n$ 只怪兽，每打赢 $1$ 只怪兽后会随机获得一种装备 $a \in [1,k]$。假设原有的 $a$ 装备的等级为 $t$，那么新获得的装备的等级为 $[1,t+1]$，且你会将新获得的装备和原来的装备中等级较高的装备留下，等级较低的装备卖出，卖出可获得的金币为该装备的等级。 问打完这 $n$ 只怪兽后，获得的金币的期望。 

$1 \le n \le 10^5, 1 \le k \le 100$

题解：

期望 dp

观察到这 $k$ 种装备都是“一样”的，所以我们可以随便选择一种装备来考虑它在打这 $n$ 个怪兽时是如何变化的，然后对答案乘上 $k$ 就可以了。

令 $dp_{i,j}$ 表示考虑到 **还剩** $i$ 个怪兽没打，且此时装备的等级为 $j$ 时的期望答案。

为什么是 **还剩** $i$ 个怪兽，而不是 **打了** $i$ 个怪兽呢？因为如果我们如果设计是**打了** $i$ 个怪兽的话，每次往后转移的时候还要考虑到这种情况出现的概率，不好处理。而如果从后往前转移的话，就避免了复杂的计算。

**这个trick在期望题中很常用**

考虑转移。

+ 正好拿到了这种装备，而且等级为 $j+1$

卖掉了原有的等级为 $j$ 的装备，可能性为 $\frac{1}{k\times(j+1)}$，收益为 $j$

+ 拿到了这种装备，但等级不为 $j+1$

那就相当于拿到了又卖了

可能性为 $\frac{j}{(j+1)\times k}$，收益为 $\frac{\sum\limits_{f=1}^{j}f}{j}=\frac{j\times(j+1)}{2\times j}=\frac{j+1}{2}$

+ 拿到了其它装备

可能性为 $\frac{k-1}{k}$，对其它装备有影响，而对这个装备的收益为 $0$

但发现这个方程的转移是 $O(n^2)$ 的，无法通过。

你想了想，发现这题要求输出的是**小数**，就打算在这上面动心思。

考虑每一次升级的概率。

从 $j$ 级升到 $j+1$ 的期望次数为 $k\times(j+1)$，所以从 $1$ 级升到 $j+1$ 级的期望次数为 $\sum\limits_{f=1}^{j}k\times(j+1)=k\times\sum\limits_{f=1}^{j}f=\frac{k\times j \times (j+1)}{2}$

发现到了后面就很大可能不会再升级了。

所以，我们可以假定一个最大等级 $l=1000$，当达到最大等级后就不再升级，这样也是在误差范围内的。

Code:
```cpp
using namespace std;
int n;
#define ld long double
ld dp[2][1005],k; //滚动了下，防炸空间
inline void solve(){
	cin>>n>>k;
	int cur=0,pre=1;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=1000;++j){
			dp[cur][j]=0;
			dp[cur][j]+=(dp[pre][j+1]+j)/(j+1)/k;
			dp[cur][j]+=(dp[pre][j]+(j+1.0)/2.0)*1.0*j/k/(1.0*(j+1));
			dp[cur][j]+=(dp[pre][j])*(k-1)/k;
		}
		swap(cur,pre);
	}
	cout<<fixed<<setprecision(9)<<dp[pre][1]*k<<'\n';
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T=1;
	//cin>>T;
	for(;T--;)solve();
	return 0;
}
```

---

## 作者：ivyjiao (赞：0)

所有装备完全相同，所以只需要算一种装备，再将答案 $\times k$。

设 $dp_{i,j}$ 为还有 $i$ 件装备没拿（还有 $i$ 个怪没打），且当前装备等级为 $j$ 的期望收益。

那么有三种情况：

1. 新装备等级不大于当前装备，直接卖了，概率为 $\dfrac 1 k\times \dfrac j{j+1}=\dfrac j{k\times {j+1}}$，期望收益为 $\sum_{i=1}^{j} i\times \dfrac 1 j=\dfrac{\sum_{i=1}^{j} i}j=\dfrac{\dfrac{(j+1)\times j}2}j=\dfrac{(j+1)\times j}{2j}=\dfrac{j+1}2$，注意你是从未来向现在推的，需要从 $dp_{i-1,j+1}$ 转移。
2. 新装备等级大于当前装备，原装备直接卖了，概率为 $\dfrac 1 k\times \dfrac 1{j+1}=\dfrac 1{k\times {j+1}}$，期望收益为 $j$。
3. 不是当前位置的装备，概率为 $\dfrac{k-1}k$，期望收益为 $0$，不用管，直接转移。

空间不够，用滚动数组优化一下，这样可以 $O(n^2)$ 转移。

dp 式太长，不写了。

但是这样还是会 TLE，我们假设小 $R$ 很非，最多只能抽到 $1000$ 级的装备，然后时间复杂度就变成了 $O(sn)$，其中 $s$ 是你设的最高等级，能过（毕竟允许误差）。

你说为什么倒序是对的？“还有 $n$ 件装备没拿（还有 $n$ 个怪没打），且当前装备等级为 $1$ 的期望收益”不就是推回初始状态了吗，然后就等同于答案了。你正着推还要考虑当前状态的概率，多难写啊。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
double dp[2][1001];
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=1000;j++){
            dp[i&1][j]=0;
            dp[i&1][j]+=(dp[(i-1)&1][j+1]+j)/((j+1)*k);
            dp[i&1][j]+=(dp[(i-1)&1][j]+(j+1)/2.0)*j/((j+1)*k);
            dp[i&1][j]+=dp[(i-1)&1][j]*(k-1)/k;
        }
    }
    printf("%.10f",dp[n&1][1]*k);
}
```

---

## 作者：Honor誉 (赞：0)


### 这道题我们考虑概率DP

### 设dp[i][j]表示打赢只要求出了前i只怪兽后某种装备被替换后价值为j的期望。

### 为什么是某装备？

### 因为所有装备的期望值是相同的，所以我们只要求出一种装备的期望，再乘上k即可。

### 有两种情况：

## 1.爆出了等级为j+1的神装。（概率为$1/(j+1)$）

### dp[i][j]+=(dp[i-1][j-1]+j)/j+1。

## 2.只得到等级<=j的装备。（概率为$j/(j+1)$）

### dp[i][[j]+=(dp[i-1][j]+(j+1)/2)*j/(j+1);//因为1至j是等概率出现的，所以取平均（j+1）/2。

### 但是这样你打出来你会发现自己MLE或TLE了，为什么？

## i过于大，j也过于大。

### 优化：1.dp[i][j]的更新只需要他前一个的情况，所以我们可以考虑用滚动数组记录。

### 2.因为这个状态的转移是会收敛的，所以j越大他所产生的变化就越小，最终小到可以忽略不计，所以j只用取到很小就可以当作答案用了（有很多神仙j取600就过了，不过保险起见最好取1000）。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,s=1;
double dp[2][1010];
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++,s^=1)
	{
		for(int j=min(n,1000);j;j--)
		{
			dp[s][j]=((dp[s^1][j+1]+j)/(j+1.0)+(dp[s^1][j]+(j+1)/2.0)*j/(j+1.0))/double(k)+dp[s^1][j]*(k-1.0)/double(k);
		}
	}
	printf("%.11lf\n",dp[s^1][1]*k);
	return 0;
}
```

---

