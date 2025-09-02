# 「PFLOI R1」PFL 团主的 PFL 操作

## 题目背景

比赛结束后，智力、旸麦、花猫邀来碓瑘，四人从此结交为友。

--------------------

实际上，不光碓瑘，智力、旸麦、花猫都曾是 OI 界中最强的存在。一次又一次 AK 一场又一场 Trash Round 后，它们厌倦了，从此销声匿迹，退出江湖。

今天看到碓瑘才气不减当年，它们又念想起那些和 OI 作伴的时光……兴意，顿生心头。

于是它们找到了 PFLOI 团长珺珺，请求珺珺给它们再次辉煌的机会——出一场属于自己的比赛。

听完它们的事迹后，珺珺颇为感动，欣然同意。5 人就此相聚在 PFLOI。

但是旸麦进入 PFLOI 后~~乱出题~~太调皮了，珺珺可不乐意了，于是：

![](https://cdn.luogu.com.cn/upload/image_hosting/9m9343n9.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/znp6x2ta.png)

## 题目描述

有 $n$ 次操作，每次操作会等概率地进行以下事件中的一个：

1. 将 $a_i$ 加入团队，操作后 $a_i$ 为成员。
2. 将 $a_i$ 踢出团队。
3. 将 $a_i$ 设置为管理员。
4. 将 $a_i$ 设置为成员。

**注意：**

+ 开始时没有人在团队里。  
+ 如果 $a_i$ 不在团队中，则 2、3、4 操作无效果。  
+ 如果 $a_i$ 为成员，则 1、4 操作无效果。  
+ 如果 $a_i$ 是管理员，则 1、2、3 操作无效果。  

最后输出团队中管理员个数的期望，答案对 $998244353$ 取模。

## 说明/提示

**本题采用捆绑测试**。

| 子任务编号	 | $\text{type}=$ | $n$ | $a_i$ | 分值 |
| :---: | :---: | :---: | :---: | :---: |
| $1$ | $1$ | $n\le 100$ | $1\le a_i\le10$ | $25$ |
| $2$ | $1$ | $n\le 5\times 10^5$ | $1\le a_i\le 10^{18}$ | $35$ |

| 子任务编号	 | $\text{type}=$ | $n$ | $a_0,p,q$ | 分值 |
|:---------:|:------:|:---:|:-----:|:-----:|
| $3$ | $2$ | $n\le 10^6$ | $1\le a_0,p<q\le 20$ | $10$ |
| $4$ | $2$ | $n\le 10^{18}$ | $1\le a_0,p<q\le 3\times 10^5$ | $30$ |

对于所有数据，$1\le n\le 10^{18}$。

## 样例 #1

### 输入

```
1
6
1 1 2 1 2 1
```

### 输出

```
760381441```

## 样例 #2

### 输入

```
2
11 4 5 14```

### 输出

```
686292993```

# 题解

## 作者：Unnamed114514 (赞：8)

### Update

2023.8.28 转移矩阵好像有个地方写错了。

***

[操作](https://www.luogu.com.cn/problem/P9590)

被出题人强制要求，于是把题解写详细点。

### Subtask 0

状压，每个人共三个状态：不在团队中（$0$），是团队成员（$1$），不是团队成员（$2$）。

那么我们就能定义 $dp_{i,j}$ 表示当前是第 $i$ 次操作，并且状态为 $j$ 的期望管理员数，用三进制按照题目模拟即可。 

时间复杂度 $O(n3^a)$，期望得分 $25$。

### Subtask 1&2

容易想到管理员总数的期望等于每个人成为管理员的期望和，又因为每个人的贡献为 $1$，所以就是等价于求概率。

对于 $dp_{i,0/1/2}$ 表示一个人经过 $i$ 次操作后不在团队中/是团队成员/是团队管理员的概率。

对于 $dp_{i,0}$，那么可以由上一次的成员踢出，也可能是上一次不在团队内，这一次进行了无效操作，转移为 $dp_{i,0}\gets\dfrac{3}{4}dp_{i-1,0}+\dfrac{1}{4}dp_{i-1,1}$。

对于 $dp_{i,1}$，那么可以由上一次的管理员变成成员，上一次不在团队内这一次加入，也可能是上一次设置为团员后，这一次进行了无效操作，转移为 $dp_{i,1}\gets\dfrac{1}{4}dp_{i-1,0}+\dfrac{1}{2}dp_{i-1,1}+\dfrac{1}{4}dp_{i-1,2}$。

对于 $dp_{i,2}$，那么可以由上一次的成员设置为管理员，也可能是上一次的管理员这一次进行了无效操作，转移为 $dp_{i,2}\gets\dfrac{1}{4}dp_{i-1,1}+\dfrac{3}{4}dp_{i-1,2}$。

那么我们在初始化了 dp 后，原问题就转化为了求每个 $a$ 的出现次数。

时间复杂度 $O(n\log n)$，瓶颈是在统计出现次数，期望得分 $70$。

### Subtask 3

首先根据余数的周期性，可以发现：对于同一个 $x$，它们下一次操作得到的 $x'$ 是相同的。

那么 $a$ 就有周期性，并且最多只有 $q$ 个 $a$，那么我们可以暴力统计每个 $a$ 的出现次数。

但是 dp 不能初始化，但是发现这个递推式非常特殊，于是考虑矩阵加速：

目标矩阵应该很好拿到：

$$
\begin{bmatrix}
f_{i,0}\\
f_{i,1}\\
f_{i,2}
\end{bmatrix}
$$

设矩阵加速的转移如下：

$$
\begin{bmatrix}
f_{i-1,0}\\
f_{i-1,1}\\
f_{i-1,2}
\end{bmatrix}\times\begin{bmatrix}
a\ b\ c\\
d\ e\ f\\
g\ h\ i
\end{bmatrix}=\begin{bmatrix}
f_{i,0}\\
f_{i,1}\\
f_{i,2}
\end{bmatrix}
$$

根据矩阵乘法，我们可以得到如下的方程：

$$f_{i,0}=af_{i-1,0}+bf_{i-1,1}+cf_{i-1,2}$$

$$f_{i,1}=df_{i-1,0}+ef_{i-1,1}+ff_{i-1,2}$$

$$f_{i,0}=gf_{i-1,0}+hf_{i-1,1}+if_{i-1,2}$$

带入上面的状态转移方程，有：

$$\begin{cases}a=\frac{3}{4}\\b=\frac{1}{4}\\c=0\\d=\frac{1}{4}\\e=\frac{1}{2}\\f=\frac{1}{4}\\g=0\\h=\frac{1}{4}\\i=\frac{3}{4}\end{cases}$$

那么矩阵加速的矩阵乘法就应该是这样的：

$$
\begin{bmatrix}
f_{i-1,0}\\
f_{i-1,1}\\
f_{i-1,2}
\end{bmatrix}\times\begin{bmatrix}
\frac{3}{4}\ \frac{1}{4}\ 0\\
\frac{1}{4}\ \frac{1}{2}\ \frac{1}{4}\\
0\ \frac{1}{4}\ \frac{3}{4}
\end{bmatrix}=\begin{bmatrix}
f_{i,0}\\
f_{i,1}\\
f_{i,2}
\end{bmatrix}
$$

那么转移矩阵就是：

$$\begin{bmatrix}
\frac{3}{4}\ \frac{1}{4}\ 0\\
\frac{1}{4}\ \frac{1}{2}\ \frac{1}{4}\\
0\ \frac{1}{4}\ \frac{3}{4}
\end{bmatrix}$$

初始化 $f_{0,0}\gets 1$，那么初始矩阵就是：

$$
\begin{bmatrix}
1\\
0\\
0
\end{bmatrix}
$$

对于每次乘上转移矩阵，就会从 $i-1$ 转移到 $i$，那么令一个数的出现次数为 $cnt$，我们只需要用初始矩阵乘上转移的 $cnt$ 次方即可，最后我们需要的是成为管理管的概率，所以最后当前的概率就是目标矩阵的第 $3$ 行第 $1$ 列。

时间复杂度 $O(q\log n)$，期望得分 $100$。

---

## 作者：ckain (赞：5)

答案为每一个人成为管理员的概率的求和．

$P_i$ 表示一个人被操作 $i$ 次后成为管理员的概率，$vis_i$ 表示 $n$ 次操作中对第 $i$ 个人的操作次数．那么有：

$$
ans=\sum_{i}P_{vis_i}
$$

考虑在 $i$ 很大的时候如何快速求出 $P_i$．

使用矩阵快速幂．设 $F_{i,0/1/2}$ 表示操作 $i$ 次后成为 非成员/成员/管理员 的概率．有矩阵转移：

$$
\begin{bmatrix}
F_{i,0} & F_{i,1} & F_{i,2}
\end{bmatrix}
\times
\begin{bmatrix}
3/4 & 1/4 & 0\\
1/4 & 2/4 & 1/4\\
0	& 1/4 & 3/4
\end{bmatrix}
=
\begin{bmatrix}
F_{i+1,0} & F_{i+1,1} & F_{i+1,2}
\end{bmatrix}
$$


### $type=1$

对于每个人直接记下来操作的次数即可．

### $type=2$

考虑 $a_i$ 一定存在一个 $\le q$ 的周期：$a_i$ 的每种取值对应一种 $\bmod\ q$ 的剩余系，当出现两个相同的 $a_i$ 即出现了周期，而根据抽屉原理，在 $a_{1}\sim a_{q+1}$ 中一定会出现两个相同的 $a_i$．算出每个人被操作了几次，然后情况和 $type=1$ 就类似了．

code
```cpp
#include<bits/stdc++.h>
#define pii pair<int, int>
#define fr first
#define sc second
#define int long long
using namespace std;
inline int rd(void){
	int s=0, f=1; char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') f=0; c=getchar();}
	while(c>='0' && c<='9') {s=s*10+c-'0'; c=getchar();}
	return f? s:-s;
}
void write(int num){
	if(num>9) write(num/10);
	putchar(num%10+'0');
}

const int N=5e6+5, Mod=998244353, inv4=748683265;

int qpow(int a, int b){
	int re=1; for(; b; b>>=1, a=a*a%Mod) if(b&1) re=re*a%Mod;
	return re;
}

struct Matrix{
	int c[3][3];
	Matrix(bool if_bas=0){
		memset(c, 0, sizeof(c));
		if(if_bas)
			c[0][0]=c[1][1]=c[2][2]=1;
	}
	Matrix operator *(const Matrix &o)const{
		Matrix re;
		for(int i=0; i<3; i++){
			for(int j=0; j<3; j++){
				for(int k=0; k<3; k++){
					re.c[i][j]=(re.c[i][j]+c[i][k]*o.c[k][j]%Mod)%Mod;
				}
			}
		}
		return re;
	}
};

Matrix qpow(Matrix a, int b){
	Matrix re(1); for(; b; b>>=1, a=a*a) if(b&1) re=re*a;
	return re;
}

int type, n, p, q, a[N], cnt[N];
int ls[N], lsi;

// 处理 type=2 
int cy[N], pre[N];
//

signed main(){
	type=rd();
	
	Matrix Trs;
	Trs.c[0][0]=inv4*3%Mod;
	Trs.c[0][1]=inv4;
	Trs.c[1][0]=inv4;
	Trs.c[1][1]=inv4*2%Mod;
	Trs.c[1][2]=inv4;
	Trs.c[2][1]=inv4;
	Trs.c[2][2]=inv4*3%Mod;
	
	if(type==1){
		n=rd();
		for(int i=1; i<=n; i++) ls[i]=(a[i]=rd());
		sort(ls+1, ls+1+n); lsi=unique(ls+1, ls+1+n)-ls-1;
		for(int i=1; i<=n; i++) cnt[lower_bound(ls+1, ls+1+lsi, a[i])-ls]++;
		int ans=0;
		for(int i=1; i<=lsi; i++){
			Matrix Trsi=qpow(Trs, cnt[i]);
			ans=(ans+Trsi.c[0][2])%Mod;
		}
		write(ans);
		puts("");
	}
	else{
		n=rd(), a[0]=rd(), p=rd(), q=rd();
		int cycle=0, ed=0;
		for(int i=1; i<=n; i++){
			a[i]=(a[i-1]+1)*p%q+1;
			cnt[a[i]]++;
			if(pre[a[i]]){
				cycle=i-pre[a[i]];
				for(int j=pre[a[i]]+1; j<=i; j++) cy[a[j]]++;
				ed=i;
				break;
			}
			pre[a[i]]=i;
		}
		if(ed){
			for(int i=1; i<=q; i++) cnt[i]+=(n-ed)/cycle%(Mod-1)*cy[i]%(Mod-1), cnt[i]%=(Mod-1);
			int now=a[ed];
			for(int i=1; i<=(n-ed)%cycle; i++){
				now=(now+1)*p%q+1;
				cnt[now]++;
			}
		}
		int ans=0;
		for(int i=1; i<=q; i++){
			Matrix Trsi=qpow(Trs, cnt[i]);
			ans=(ans+Trsi.c[0][2])%Mod;
		}
		write(ans);
		puts("");
	}
	return 0;
}
```

---

## 作者：Grisses (赞：5)

## 对于第 $1$ 部分：

首先，因为期望的可加性，我们可以处理每个人成为管理员的概率，乘上其权值后求和即可。

设 $dp_{i,0/1/2}$ 是进行 $i$ 次操作后一个人不在团队/只是成员/是管理员的概率。

记关于第 $i$ 个人的操作有 $k_i$ 次，最后的答案就是 $\sum dp_{k_i,3}$。

容易推导：

- 如果第 $i$ 次操作后一个人不在团队，他可能是本身就不在团队，也可能是作为一个成员被踢出去。

所以：$dp_{i,0}=\frac{3}{4}dp_{i-1,0}+\frac{1}{4}dp_{i-1,1}$。

- 如果第 $i$ 次操作后一个人是成员，他可能是本身就是成员，也可能是作为一个管理员被撤职，还有可能是被加入到团队中。

所以：$dp_{i,1}=\frac{1}{4}dp_{i-1,0}+\frac{2}{4}dp_{i-1,1}+\frac{1}{4}dp_{i-1,2}$。

- 如果第 $i$ 次操作后一个人是管理员，他可能是本身就是管理员，也可能是作为一个成员被提升为管理员。

所以：$dp_{i,2}=\frac{1}{4}dp_{i-1,1}+\frac{3}{4}dp_{i-1,2}$。

同时 $dp_{0,0}=1,dp_{0,1}=dp_{0,2}=0$。

## 对于第 $2$ 部分：

首先，我们可以发现如果 $a_x=a_y$，那么也会有 $a_{x+1}=a_{y+1}$，并且 $a_i$ 最多只有 $q$ 种取值。所以，得出结论，$a$ 数组一定存在长度不大于 $q$ 的循环节，并且循环部分前的非循环部分的长度也一定不超过 $q$。

所以我们可以先找出循环节，求出每种 $a_i$ 出现的次数，然后就可以像第 $1$ 部分一样 dp 处理。

但是，由于 $n$ 过于巨大，所以直接暴力 dp 还是会 TLE。

所以我们需要用到矩阵快速幂优化 dp。

$$
\begin{array}{c}
\begin{matrix}
\frac{3}{4}&\frac{1}{4}&0\\
\\
\frac{1}{4}&\frac{2}{4}&\frac{1}{4}\\\\
0&\frac{1}{4}&\frac{3}{4}
\end{matrix}
\end{array}
\times 

\begin{matrix}
dp_{i,0}\\\\
dp_{i,1}\\\\
dp_{i,2}
\end{matrix}

=
\begin{matrix}
dp_{i+1,0}\\\\
dp_{i+1,1}\\\\
dp_{i+1,2}
\end{matrix}
$$

然后就可以了。

---

## 作者：Super_Cube (赞：1)

# Solution

首先，最后团队中管理员个数的期望等价于最后每个人作为管理员的概率之和，因为每个人作为管理员对于总管理员个数只有 $1$ 的贡献。

还有个重要的性质：每个人最后是管理员的概率只与他被操作的次数有关。

考虑 dp，定义 $dp_{i,0/1/2}$ 表示一个人被操作过 $i$ 次后不在团队内，是成员，是管理员三种状况的概率。

那么转移方程如下：

+ $dp_{i,0}=\dfrac{3dp_{i-1,0}+dp_{i-1,1}}{4}$

本身就不在团队内或者作为成员被踢出。

+ $dp_{i,1}=\dfrac{dp_{i-1,0}+2dp_{i-1,1}+dp_{i-1,2}}{4}$

从团队外加入，本身就是成员或者从管理员被设置为成员。

+ $dp_{i,2}=\dfrac{dp_{i-1,1}+3dp_{i-1,2}}{4}$

作为成员被设置为管理员或者本身就是管理员。

初始化：$dp_{0,0}=1$。

如何计算答案？对于每个 $a_i$ 统计出现次数，假设为 $c$，最后的期望就会增加 $dp_{c,2}$。

时间复杂度 $O(n)$，可以通过前三个 Subtask。

现在来关注第四个 Subtask。

特点：输入是由生成器得到，$n$ 巨大，$q$ 较小。

先不管读入，巨大的 $n$ 使得之前的算法不再适用，考虑优化。

观察这个 dp 的转移式，发现能很轻松的写成矩阵形式，如下：

$$
\begin{bmatrix}
dp_{i-1,0} & dp_{i-1,1} & dp_{i-1,2}
\end{bmatrix}
\times
\begin{bmatrix}
\dfrac{3}{4} & \dfrac{1}{4} & 0\\\\
\dfrac{1}{4} & \dfrac{1}{2} & \dfrac{1}{4}\\\\
0 & \dfrac{1}{4} & \dfrac{3}{4}
\end{bmatrix}

=
\begin{bmatrix}
dp_{i,0} & dp_{i,1} & dp_{i,2}
\end{bmatrix}
$$

初始矩阵：$\begin{bmatrix}1 & 0 & 0\end{bmatrix}$。

这样 dp 的复杂度就降为了 $O(\log n)$。

再来解决输入。发现 $a_i$ 的计算式中有对 $q$ 取模且只与 $a_{i-1}$ 的值有关。根据鸽巢原理，一定会出现循环节且循环节的长度不会超过 $q$。

所以可以直接打桶暴力寻找循环节。注意开头可能不是循环节的第一位。

假设前面不属于循环节的个数为 $p$，循环节长度为 $c$。

那么当 $n\le p$ 时，期望为 $0$，因为非循环节部分每个数一定只会出现一次，不可能成为管理员。

当 $n>p$ 时，循环节中 $c-((n-p) \bmod c)$ 个数会出现 $\left\lfloor\dfrac{n-p}{c}\right\rfloor$ 次，而剩下的 $(n-p) \bmod c$ 个数会出现 $\left\lfloor\dfrac{n-p}{c}\right\rfloor+1$ 次，最后非循环节中的数不用考虑，因为在循环节中不可能有这些数。所以期望就是把这两部分答案加起来。

# Code

```cpp
//type=1
#include<bits/stdc++.h>
const int mod=998244353;
std::unordered_map<long long,int>cnt;
int dp[500005][3];
long long a;
int n,ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%lld",&a),++cnt[a];
	dp[0][0]=1;
	for(int i=1;i<=n;++i)
		dp[i][0]=(249561089ll*dp[i-1][0]+748683265ll*dp[i-1][1])%mod,
		dp[i][1]=(748683265ll*(dp[i-1][0]+dp[i-1][2])+499122177ll*dp[i-1][1])%mod,
		dp[i][2]=(249561089ll*dp[i-1][2]+748683265ll*dp[i-1][1])%mod;
	for(const auto&i:cnt)
		ans=(ans+dp[i.second][2])%mod;
	printf("%d",ans);
	return 0;
}
```
```cpp
//type=2
#include<bits/stdc++.h>
const int mod=998244353;
struct matrix{
	int arr[3][3];
	inline matrix(int x=0){
		memset(arr,0,sizeof(arr));
		if(x)
			for(int i=0;i<3;++i)
				arr[i][i]=1;
	}
	inline int* operator[](const int&i){return arr[i];}
	inline const int* operator[](const int&i)const{return arr[i];}
	inline matrix operator*(const matrix&x)const{
		matrix res;
		for(int i=0;i<3;++i)
			for(int k=0;k<3;++k)
				if(arr[i][k])
					for(int j=0;j<3;++j)
						res[i][j]=(res[i][j]+1ll*arr[i][k]*x[k][j]%mod)%mod;
		return res;
	}
	inline friend matrix operator^(matrix x,long long y){
		matrix res(1);
		while(y){
			if(y&1)res=res*x;
			y>>=1;
			x=x*x;
		}
		return res;
	}
}mat,base;
int vis[300005];
int a,p,q;
long long n;
int cir,pre;
int main(){
	scanf("%lld%d%d%d",&n,&a,&p,&q);
	for(int i=1;;++i)
		if(vis[a=(p*(a+1ll))%q+1]){
			cir=i-vis[a];
			pre=vis[a]-1;
			break;
		}else vis[a]=i;
	if(n<=pre)return 0&putchar(48);
	mat[0][0]=1;base[0][0]=base[2][2]=249561089;base[0][1]=base[1][0]=base[1][2]=base[2][1]=748683265;base[1][1]=499122177;
	printf("%lld",(1ll*(cir-(n-pre)%cir)*(mat*(base^((n-pre)/cir)))[0][2]+1ll*((n-pre)%cir)*(mat*(base^((n-pre)/cir+1)))[0][2])%mod);
	return 0;
}
```

---

