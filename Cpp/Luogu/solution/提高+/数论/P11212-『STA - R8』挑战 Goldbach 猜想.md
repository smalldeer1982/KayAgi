# 『STA - R8』挑战 Goldbach 猜想

## 题目描述

$q$ 次询问，每次给一个正整数 $n$，问有多少个不超过 $n$ 的正整数 $i$ 使得 $i$ 和 $n\bmod i$ 都是质数。



## 说明/提示

**本题采用捆绑测试。**

数据范围：

- Subtask 1 (30pts)：$q=1$。
- Subtask 2 (70pts)：无特殊限制。

对于全部数据，$1\le n,q\le2\times10^5$。

洛谷代码长度限制：50 KB。

## 样例 #1

### 输入

```
5
5
55
555
5555
55555```

### 输出

```
1
3
22
93
447```

# 题解

## 作者：jijidawang (赞：15)

记号约定：$\operatorname{isp}(n)$ 当 $n$ 为素数时为 $1$、否则为 $0$，$\operatorname{gpf}(n)$ 表示 $n$ 的最大素因子。

枚举 $x=n\bmod i$，则注意到一个 $i$ 满足 $n\bmod i=x$ 当且仅当 $i\mid(n-x)$ 且 $i>x$。

那么就是要算 $\displaystyle\sum_{i=1}^{n-1}\operatorname{isp}(i)\sum_{d\mid(n-i)}\operatorname{isp}(d)[d>i]$。注意到对于 $i>\sqrt n$，$\displaystyle\sum_{d\mid(n-i)}\operatorname{isp}(d)[d>i]$ 最大只可能为 $1$。所以可以先考虑计算 $\displaystyle\sum_{i=1}^n\operatorname{isp}(i)[\operatorname{gpf}(n-i)>i]$ 再以 $O(\sqrt n)$ 的代价修正答案。

令 $f_i=\operatorname{isp}(i),\,g_i=[\operatorname{gpf}(i)+i>n]$，则对于一个固定的 $n$，答案即为卷积 $(f\times g)_n$。对于多组询问，可以考虑先离线，把所有数按 $\operatorname{gpf}(i)+i$ 排序，使用单调指针动态维护当前的 $g$。那么只需要维护一个数据结构，支持对 $g$ 单点修改，对 $f\times g$ 单点求值。

此处可以考虑根号重构，令 $B$ 是块长。每 $B$ 次修改真正计算一次 $f\times g$ 的值，那么每次询问时只需要处理 $O(B)$ 个单点修改，这可以在线性时间复杂度内简单处理。假设 $n,q$ 同阶则时间复杂度为 $O(\frac nBn\log n+nB)$，取 $B=\sqrt{n\log n}$ 得最优复杂度 $O(n\sqrt{n\log n})$。

然后就能过了~

---

## 作者：bingo888 (赞：12)

赛后看出题人题解感到有点震惊，这道题要是这么做多半是黑题，但这是道蓝题，一定有蓝题的做法。  

我们发现线性筛后朴素暴力时间复杂度为 $\mathcal{O}(\frac{nq}{\log n}+n)$，但是正向优化可能和出题人题解一样难，所以我们考虑逆向算法。  

我们发现答案的贡献一定可以写成 $n=kp_1+p_2\quad (p_1>p_2)$，于是直接枚举 $p_1,p_2,k$，对答案做贡献，总时间复杂度为 $\mathcal{O}(\frac{n^2\log\log n}{\log^{2}n}+q)$ ，没有取模运算，常数小，一般优秀能在不到半秒的时间内跑出来，足以通过此题。  

这种做法相比于出题人题解做法简单太多，我认为没有给代码的必要。  
***
### Updated on Oct.21  
这里补充关于复杂度的说明：  
更准确的复杂度应该为 $\mathcal{O}(\frac{n^2}{\log^{2}n}+q)$，即没有 $\log\log n$。  
由素数定理可知我们枚举的每一个素数是 $\frac{n}{\log n}$ 级别的，很容易知道在不枚举 $k$ 的时间复杂度是 $\mathcal{O}(\frac{n^2}{\log^{2}n})$，但是针对枚举的 $k$ 随着 $p_1$ 的增大而减少，结合 $n$ 的增长使得具体变化函数我不太会，但是通过暴力比较是否枚举 $k$ 的循环次数比值可知这个函数大概是先增后减的，记为 $w$，具体如下：  


|$n$|$w$|
|:-:|:-:|
|$50$|$1.409520$|
|$200$|$1.470530$|
|$500$|$1.554760$|
|$2000$|$1.521190$|
|$5000$|$1.463940$|
|$20000$|$1.387920$|
|$200000$|$1.285080$|

因此，我们发现这个比值均小于 $2$，可以近似看作一个常数，更准确的复杂度应该为 $\mathcal{O}(\frac{n^2}{\log^{2}n}+q)$。

---

## 作者：PassName (赞：9)

这里提供两种非官解做法。

对于正整数 $n$，不超过 $n$ 的素数个数大约有 $\frac{n}{\ln n}$ 个。预处理筛素数随便写个筛就行，对于复杂度影响不大。考虑对于小于 $n$ 枚举每一个素数。那么复杂度就是 $O(\frac{n^2}{\ln n})$。我们可以很轻松的将暴力打出来。但是交上去显然过不了。

考虑复杂度瓶颈，我们先忽略代码正确性，将取模运算随便换成别的运算交上去（或者本地测），运行时间甚至没有超过 $2s$。所以瓶颈在于取模运算。

将 $n$ 个答案预处理出来，我们可以预处理出所有的答案记为 $f_i$，每询问一次 $n$ 输出 $f_n$ 即可。至于预处理时的优化取模，我们可以定义一个变量代表余数，跟随你的枚举而改变，当大小等于模数时重新变为 $0$ 即可。可以通过。

[code](https://www.luogu.com.cn/paste/t5pqc0nw)

如果不预处理在线计算的做，记忆化一下。开个数组记录已经出现过的答案。然后如果询问的值之前出现过直接输出，否则现场计算。在进行取模的时候，使用巴雷特快速取模算法进行优化。取模慢是因为做除法慢，算法原理大概就是将除法变成其运算加速。具体地，将除以任意数转化成乘一个数、除以一个 $2^k$。可能是细节处理的不太好，这个做法最慢的点跑了 $3s$。但也足以通过。

[code](https://www.luogu.com.cn/paste/v3n56yp9)

当然，出题人还友善的提醒了我们代码长度限制。显然是怕我们打表。不难发现，对于大部分答案，大概都是个三位数。计算一下发现对于超出洛谷代码限制我们可以打大概 $13000$ 个数字。打个表存起来，对于大于 $13000$ 的再在线暴力计算。代码太长就不放了。

---

## 作者：Exp10re (赞：7)

Update：补充了对于 $V$ 表示的答案规模的证明，感谢 @Argon_Cube 以及 @joke3579 给出的证法。

赛时。

尽管你并没有自信能写出这道题，但是抱着能拿一分是一分的心态，你还是点开了这道题，打算打一个暴力。于是：

## 解题思路

你注意到本题的说明提示一栏有着这样一行字：

> 洛谷代码长度限制：50 KB。

试想若没有这一限制，本题的一种做法是什么？答案呼之欲出，就是打表。

于是，你将这道题的表打了出来。

![](https://cdn.luogu.com.cn/upload/image_hosting/l9bzq2wf.png)

然后发现一个表最短 862 KB，显然不可行。

虽然打表这条路走不通，但你所做的并非无用功。你惊喜地发现，这张表里所有数的和大约为 $S=2.08\times 10^8$，也就是说，如果你有有效的方法统计贡献，那么一整个程序运行下来两秒不到。

你考虑到枚举 $n$ 之后未必能枚举每一个有效质数对，也就是说会产生大量无用的枚举冗余，于是你决定拆式子：

记 $p_2=n \bmod p_1$，则有 $n=p_1\lfloor\frac {n} {p_1} \rfloor+p_2$，这个式子中若 $p_1,p_2$ 均为质数则对 $n$ 产生 $1$ 的贡献。

你发现枚举范围内的每一对 $(p_1,p_2,\lfloor\frac {n} {p_1} \rfloor)$ 都会产生恰好 $1$ 的贡献，显然没有冗余的枚举状态。

故枚举预处理后每一组询问输出答案即可。时间复杂度 $O(S+q)$。

---

为什么 $S$ 是这个规模？@Argon_Cube 给出了一种较为迅速的证明方法。

注意到 

$$\Theta(\sum\limits_{i=1}^{n}\frac{1} {\log i})=\Theta(\frac{n} {\log n})$$

枚举 $i$ 为第 $i$ 个质数（即文中的 $p_1$），再枚举前 $i$ 个质数作为 $n \bmod i$（即文中的 $p_2$），最后枚举 $\frac {V} {i\log i}$ 个可能的 $n$，复杂度为：

$$\Theta(\sum\limits_{i=1}^{\frac {V} {\log V}}i\frac{V} {i\log i})=\Theta(V\frac{\frac {V} {\log V}} {\log \frac {V} {\log V}})=\Theta(\frac{V^2} {\log^2 V})$$


由此答案规模便得证，时间复杂度实际为 $O(\frac{V^2} {\log^2 V}+q)$ 规模。

另外，@joke3579 也给了另外一种证明方法，鉴于其较长，这里给出[博客链接](https://www.cnblogs.com/joke3579/p/-/chitchat241019)，感兴趣的可以自行查阅。

---

## 作者：saixingzhe (赞：7)

# 分析
记 $x$ 为小于等于 $n$ 的质数的个数，当 $n$ 为 $2\times 10^5$ 时，$x$ 为 $17984$。

首先我们肯定要打一个质数表，朴素暴力是枚举小于 $n$ 的质数，判断 $n$ 对于它的模数是不是质数，复杂度 $\mathcal O(xq)$。

根据取模的性质我们想到记录答案时一定为 $n=k\times i+j$，其中 $i,j$ 为质数且 $i>j$。

于是我们可以预处理答案，枚举 $i,j,k$ 把所有 $k\times i+j$ 的答案加一即可，对于每次询问 $\mathcal O(1)$ 回答，复杂度比较神秘，因为各种常数大概抵消，你可以理解为 $\mathcal O(x^2+q)$，实际上比这个稍小一些。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
bool isprime[200005];
int pri[18000],ans[200005],cnt,q,s; 
void slove(int n){
	for(int i=2;i<=n;i++){
		if(!isprime[i])	pri[++cnt]=i;
		for(int j=1;j<=cnt&&(long long)i*pri[j]<=n;j++){
			isprime[i*pri[j]]=1;
			if(i%pri[j]==0) break;
		}
	}
	for(int i=1;i<=cnt;i++)
		for(int j=1;j<i;j++)
		for(int k=1;k*pri[i]+pri[j]<=n;k++)	ans[k*pri[i]+pri[j]]++;
}
int main(){
	scanf("%d",&q);
	slove(200000);
	while(q--){
		scanf("%d",&s);
		printf("%d\n",ans[s]);
	}
	return 0;
}
```

---

## 作者：mishitaotuoyyds (赞：4)

# 思路：
许多人数都是 $30$ 分，原因就是思路不对，这是因为大家都是枚举所有小于 $n$ 的数字，但是我们根据 $i$ 和 $n$ 除以 $i$ 都是质数可知，我们只需要将所有小于最大的 $n$ 的质数找到，预处理一下，将所有质数相互匹配，然后就能找到所有可以 $n\bmod i$ 得到质数的数值了，一个值每被找到一次加 $1$ 就可以了，最后查询一下就行了。

望管理大大通过。

实现代码如下。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m[210000],ans=0,jl,zd=0,zs[200000],sl=1,jlans[210000];
bool zss(long long a){//质数筛
	if(a==2) return 1;
	if(a==1||a==0)return 0;
	for(int i=2;i<=sqrt(a);i++)if(a%i==0)return 0;
	return 1;
}
int read(){//快读
	char ch=getchar();
	long long s=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*w;
}
int main()
{
	n=read();
	jl=n;
	for(int i=1;i<=n;i++){
		m[i]=read();
		if(m[i]>zd){
			for(int y=zd+1;y<=m[i];y++){
				if(zss(y)){
					zs[sl++]=y;
				}
			}
		}
	    zd=max(zd,m[i]);
	}
	for(int i=1;i<sl;i++){//找到所有可以mod a=b的值
		for(int y=1;y<i;y++){	
			for(int u=zs[y];u<=zd;u+=zs[i]){
				jlans[u]+=(u>zs[i]);
			}
		}
	}
	for(int i=1;i<=n;i++){
		cout<<jlans[m[i]]<<endl;
	}
    return 0;
} 
```

完结撒花。

---

## 作者：coderJerry (赞：3)

设 $x$ 是质数，不难发现 $n=px+q$（$p,q$ 也是质数，$q<p$）就一定会产生贡献，于是欧拉筛预处理质数，再离线算出每个 $n$ 对应的答案即可。可以在 400ms 内卡过。


```cpp
#include <bits/stdc++.h>
using namespace std;
int cnt=0,n,q;
vector<int> ans(200002),prime(200002);
vector<bool> vis(200002);
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    for(int i=2;i<200001;i++){
        if(!vis[i]) prime[++cnt]=i; 
        for(int j=1;j<=cnt&&(long long)prime[j]*i<200001;j++){
            vis[prime[j]*i]=1;
            if(i%prime[j]==0) break;
        }
    }
    for(int i=1;i<=cnt;i++){
        for(int j=1;j<i;j++){
            for(int k=1;prime[i]*k+prime[j]<=200000;k++){
                ans[prime[i]*k+prime[j]]++;
            }
        }
    }
    cin>>q;
    while(q--){cin>>n;cout<<ans[n]<<endl;}
    return 0;
}
```

---

## 作者：Super_Cube (赞：3)

# Solution

看到 $n\le 2\times 10^5$ 且给了 3.5s，还在提示里写道洛谷的代码长度限制，考虑暴力。

先筛出 $2\times 10^5$ 范围内的质数，对于询问枚举不大于 $n$ 的所有质数并判断 $n\bmod i$ 是否为质数。很可惜，极限数据下要跑约 4.5s，不能通过。

尝试打表，但是因为有着代码长度限制导致实际也优化不了多少。

思考如何预处理答案。现在来枚举 $n\bmod i$ 与 $i$ 的值，记为 $p,q$，有 $q>p$，$p,q\in\operatorname{prime}$，此时会对 $\forall k\in\N^*,n=p+kq$ 造成贡献。发现运算量约为 $2\times 10^8$，可以通过此题。实测本地只需 0.4s 即可完成答案预处理。

---

## 作者：Vct14 (赞：2)

$n$ 的范围很小，感觉这题应该是橙啊/jy

前置知识：埃氏筛。

题目即求将 $n$ 分为 $i\times x+j$（$0\leqslant j<i$，$i,j$ 为质数，$x\in\mathbb{N}$）的方案数。我们筛得所有质数，然后枚举 $(i,j,x)$，求出 $n$ 后将小于或等于 $2\times10^5$ 的 $n$ 的方法数加一即可。

询问 $O(1)$ 回答。

时间复杂度非常优秀，[$413$ 毫秒](https://www.luogu.com.cn/record/184440819)可过。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define N 200000
#define I x*prime[i]+prime[j]

bool isp[N+2];
int prime[N];
int ans[N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int s=0;
	for(int i=2; i<=N; i++){
		if(!isp[i]) prime[++s]=i;
		for(int j=2*i; j<=N; j+=i) isp[j]=true;
	}
	for(int i=1; i<=s; i++) for(int j=1; j<i; j++) for(int x=1; I<=N; x++) ans[I]++;
	int q;cin>>q;
	while(q--){
		int n;cin>>n;
		cout<<ans[n]<<"\n";
	}
	return 0;
}
```

---

## 作者：yzx3195 (赞：2)

~~感觉这题我的方法只有黄题水平？~~
# 题目大意

$q$ 次询问，每次给一个正整数 $n$，问有多少个不超过 $n$ 的正整数 $i$ 使得 $i$ 和 $n\bmod i$ 都是质数。
# 这题诈骗
考虑暴力的做法，显然 $n=k\times p_i+p_j$，其中 $p$ 为质数，$k$ 为自然数。


我们先用欧拉筛筛出 $2 \times 10^5$ 内的所有质数，然后枚举一个 $i$，然后在枚举一个小于 $i$ 的数 $j$，设它们所对应的质数分别为 $p_i$，$p_j$，那么我们按照上面说的暴力思路更新 $ans$ 数组，$O(1)$ 回答。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e05 * 2 + 7;

int q;

bool bz[MAXN];

int prime[MAXN];

int ans[MAXN];

int cnt;

void EL(int n)
{
	for(int i = 2; i <= n; i++)
	{
		if(!bz[i])
			prime[++cnt]=i;
		for(int j = 1; prime[j] * i <= n and j <= cnt; j++)
		{
			bz[prime[j] * i] = true;
			if(i % prime[j] == 0)
			{
				break;
			}
		}
	}
	return ;
}

signed main()
{
	EL(200000);
	
	cin >> q;

	for(int i = 1; i <= cnt; i++)
	{
		for(int j = 1; j < i; j++)
		{
			for(int k = prime[i] + prime[j]; k <= 2e5; k += prime[i])
			{
				++ans[k];
			}
		}
	}
	
	while(q--)
	{
		int n; 
		scanf("%d", &n);
		printf("%d", ans[n]);
		puts("");
	}
	
	return 0;	
}
```

---

## 作者：RAND_MAX (赞：1)

感觉朴素做法很好想啊，不至于到蓝吧（不过题解做法至少紫题以上难度）。

由于要 $i$ 和 $n\bmod i$ 均为质数，即对每个 $n$ 求 $i\times k+j=n$ 的方案数，其中 $i$ 与 $j$ 是质数。我们只需枚举 $i,j,k$ 即可。时间复杂度 $O(\sum\limits^{\frac{n}{\log n}}_{i=1}\frac{n\times i}{i\log i})=O(\frac{n^2}{\log^2n})$，也可参考[这里](https://www.cnblogs.com/joke3579/p/-/chitchat241019)。


```cpp
#include<bits/stdc++.h>
#define int long long
#define R read()
using namespace std;
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+c-48,c=getchar();
	return x*f;
}
void write(int x,char xx)
{
	static int st[35],top=0;
	if(x<0){x=-x;putchar('-');}
	do
	{
		st[top++]=x%10,x/=10;
	}while(x);
	while(top) putchar(st[--top]+48);
	putchar(xx);
}
int q,n,ans[200010],num;
bool isp[200010];
vector<int>p;
void init(int n)
{
	for(int i=2;i<=n;i++)
	{
		if(!isp[i]) p.push_back(i);
		for(int j:p)
		{
			if(i*j>n) break;
			isp[i*j]=1;
			if(i%j==0) break;
		}
	}
}
signed main()
{
	n=2e5;
	init(n);
	for(int i:p)
	{
		for(int j:p)
		{
			if(j>=i) break;
			num=1;
			while(i*num+j<=n) ans[i*num+j]++,num++;
		}
	}
	q=R;
	while(q--) write(ans[R],'\n');
 	return 0;
}
```

---

## 作者：Rose_Melody (赞：0)

## Solution - P11212 挑战 Goldbach 猜想

[题目传送门](https://www.luogu.com.cn/problem/P11212)

### 题目分析

先看数据范围：

$$1\le n,q \le 2 \times 10^{5}$$

很显然，这要求我们做到 **$O(n)$ 的预处理和 $O(1) $ 的查询**。

我们可以把 $n$ 看做 $k \times p_{t} + p_{j}$，($p_{t}$ 和 $p_{j}$ 均为素数)。考虑枚举 $p_{t}$ 即是我们要求的 $i$，先用线性筛把素数都筛出来，累加贡献即可。

### AC Code


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 ;
int q , x , f[N + 5] ;
int cnt , vis[N + 5] , p[N + 5] ;
void prime(){
	vis[0] = vis[1] = 1 ;
	for(int i = 2;i <= N;i ++){
		if(! vis[i]) p[++ cnt] = i ;
		for(int j = i * i;j <= N;j += i){
			vis[j] = 1 ;
		}
	}
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout); 
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	prime() ;
	for(int i = 1;i <= cnt;i ++){
		for(int j = 1;j < i; j ++){
			for(int k = 1;p[i] * k + p[j] <= N;k ++){
				f[p[i] * k + p[j]] ++ ;
			}
		}
	}
	cin >> q ;
	while(q --){
		cin >> x ;
		cout << f[x] << '\n' ; 
	}
	return 0;
}
```

---

## 作者：hyk2019 (赞：0)

朴素做法：先预处理出 $2\times10^5$ 以内的素数，对于每个询问的 $n$，枚举小于 $n$ 的所有素数，统计使得 $n\bmod i$ 也是质数的个数。可得 30 分。

优化做法：根据题目中“$i$ 和 $n\bmod i$ 都是质数”，考虑把 $n$ 表示成 $k\times p_1+p_2$（$p_1,p_2$ 是素数），答案就是把 $n$ 表示成 $k\times p_1+p_2$ 的方案数。由于 $1\le n\le2\times10^5$，所以可以直接存储每个 $n$ 对应的答案。

先枚举 $p_1$（就是题目中的 $i$），再枚举 $p_2$（$2\le p_2<p_1$），然后枚举 $k$，每次得到的 $k\times p_1+p_2$ 都是 $n$ 的一种表示方法，注意 $n$ 不能超过 $2\times10^5$，并且 $n>p_1$。[1s 内](/record/183849901)可过。

```cpp
#include <bits/stdc++.h>
using namespace std;
int primes[17984], cnt, q, n, ans[200005];
bool isprime[200005] = {true, true};
int main() {
	for(int i = 2; i * i <= 200000; i ++)
		if(!isprime[i]) {
			primes[cnt ++] = i;
			for(int j = i * i; j <= 200000; j += i)
				isprime[j] = true;
		}
	for(int i = primes[cnt - 1] + 1; i < 200000; i ++)
		if(!isprime[i])
			primes[cnt ++] = i;
	// k * p1 + p2 == N  <-->  N % p1 == p2
	for(int t1 = 0; t1 < cnt; t1 ++) 
		for(int t2 = 0; t2 < t1; t2 ++) 
			for(int N = primes[t2]; N <= 200000; N += primes[t1]) // 可以改成累加
				if(N > primes[t1])
					ans[N] ++;
	scanf("%d", &q);
	while(q --) {
		scanf("%d", &n);
		printf("%d\n", ans[n]);
	}
	return 0;
}
```

---

## 作者：ELECTRODE_kaf (赞：0)

考虑预处理答案。题目要求可以转化为求有多少对**质数** $(i,j)$ 满足 $n=ik+j$，其中 $i>j,k>0,k\in N$。

所以线性筛求质数，然后三重循环枚举 $i,j,k$，给相应的 $n$ 贡献一个答案。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define rep(i,x,y) for(ll i=x;i<=y;i++)
#define pause system("pause")
#define pll pair<ll,ll>

const ll N=2e5+10;
ll q,n,ans[N+1];
bool b[N+1];
vector<ll> pri;

int main() {
	rep(i,2,N) {
		if(b[i]) continue;

		pri.push_back(i);

		for(ll j=2; i*j<=N; j++) b[i*j]=1;
	}
	
	rep(i,0,pri.size()-1) {
		rep(j,0,i-1) {
			rep(k,1,N) {
				if(k*pri[i]+pri[j]>=N) break;

				ans[k*pri[i]+pri[j]]++;
			}
		}
	}

	cin>>q;

	while(q--) {
		cin>>n;
		cout<<ans[n]<<'\n';
	}
}
```

---

