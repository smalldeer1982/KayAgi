# 「QMSOI R1」 生熏鱼

## 题目背景

一切起源于一个叫神荀彧的武将...

[那这道题与神荀彧的关系在哪里呢？](https://www.luogu.com.cn/paste/pk12x8vh)

![](https://patchwiki.biligame.com/images/msgs/thumb/e/eb/1d6q6kksj6krwhaoqdoh3029glw4ypn.jpg/376px-%E7%A5%9E%E8%8D%80%E5%BD%A7-%E7%BB%8F%E5%85%B8%E5%BD%A2%E8%B1%A1.jpg)



## 题目描述

一共有 $n$ 种攻击，第 $i$ 种攻击会先让你得到 $a_i$ 点经验，然后让你失去 $b_i$ 点血量。

你将**依次**受到 $k$ 次攻击，其中，第 $i$ 次攻击的种类是 $c_i$，你的初始血量为 $m$。

为了获得更多的经验，你可以选择 $n$ 种攻击中的任意种，并防止你受到的第一次这种攻击，防止后既不会损失血量，也不会增加经验值。

现在你想知道的是在你的血量降到 $0$ 及以下前，最多能获得多少点经验。

## 说明/提示

### 样例解释

样例 $1$ 的数据中 $a=\{953888980,904140652\},b=\{6583,80624\},c=\{1,2,1,1,2\}$。

此时显然可以不防止任何攻击或者防止第一次类型 $2$ 的攻击获得 $953888980\times 3+904140652=3765807592$ 的经验值。

可以证明，不存在获得经验值更多的方案。

### 数据范围
**本题使用 subtask 进行捆绑测试**，每个 subtask 的具体分值如下：
| 子任务 | $n$ | $k$  | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| $0$ | $\le 10$ | $\le 10^3$ | $20$ |
| $1$ | $\le 20$ | $\le 10^7$ |$30$ |
| $2$ | $\le 24$ | $\le 2\times 10^7$ |$50$ |

对于所有数据，满足 $1\le n \le 24$，$1 \le k \le 2\times 10^7$，$1\le s,m\le 10^9$。

## 样例 #1

### 输入

```
2 100000 5 114514```

### 输出

```
3765807592```

# 题解

## 作者：ylch (赞：10)

## Description

抽象题意：有 $n$ 种、$k$ 个物品，和一个体积为 $m$ 的背包，每个物品的收益为 $a_i$，体积为 $b_i$。

你只能**依次**选择这 $k$ 个物品，且无法跳过不选。

为了获得更多的收益，有一种超能力，可以从 $n$ 种物品中选择若干种物品，并在这些种类的物品**第一次出现时**放弃选择该种物品。

求最后能获得的最大收益。

## Analysis

这道题的正解是 01 背包。（我个人认为出题人的解法复杂度并不稳定，可能只是因为随机数据卡过去了）

具体地，首先用前缀和的思想统计所有的经验和损失，然后顺序遍历 $k$ 次攻击，假设当前是第 $i$ 次攻击，同时当前血量 $m<0$，那么，我们就要想办法从前面防御一些攻击，使得血量刚好可以回正（即减少 $1-m$ 的伤害），同时又不损失过多的经验。

那么，我们可以在每种物品第一次出现时，做一次 01 背包，得到要回一定血量所需的最小代价。

然后，对于血量 $m<0$ 的情况，通过在总经验上减去 $dp[1-m]$ 的经验，来维持血量，同时统计经验最大值


---


注意两个细节：

1. 我们减去的 $dp[1-m]$ 的经验要取后缀最小值，因为会出现回血多、经验值损失反而少的情况（题目并不保证失去血量越大，经验值越多）。
   
2. 我们“减去经验”“回血”等都是为了统计答案所使用，不能改变正常的血量、前缀和，因为这只是我们做出的“假设”，不对正常状况做出影响。

   也可以这么理解：这里的经验损失、回血一定会在之后的循环中被其他 dp 状态所包含（因为越往后累计伤害越大、被迫损失经验越多）。


---


这样时间复杂度为 $O(k + n^2 \times C)$，因为每种攻击只在第一次出现时跑 dp，所以背包 dp 的循环只会执行 $n$ 次。
同时，题目的血量最大值 $C \le 10^5+5$，数组的空间不会超限。

## Summary

这道题和普通 01 背包的区别是：这道题是随着 $k$ 次伤害的遍历、是否有某种攻击的首次出现来进行 dp，
而不是传统的先对全部情况 dp 预处理，再在处理询问时直接输出。

这道题可以更好地加深我们对传统背包 dp 的理解。

## Code

附详细注释。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 30, maxk = 2e7 + 5;
const int M = 1e9, C = 1e5 + 5;

int n, m, k, s;
int a[maxn], b[maxn], c[maxk];
ll dp[C * maxn], suf[C * maxn]; // dp[j]表示（前i种攻击）剩余血量为j时，得到的最小经验值；suf是后缀最小值
bool vis[maxn]; // vis[i]表示第i种攻击是否出现过

void solve()
{
	cin>>n>>m>>k>>s;
	mt19937 rand(s);
	for(int i=1;i<=n;i++)  a[i]=rand()%M+1,b[i]=rand()%C+1;
	for(int i=1;i<=k;i++)  c[i]=rand()%n+1;
	
	// 初始化为较大值（加法不爆）
	memset(dp, 0x3f, sizeof dp);
	memset(suf, 0x3f, sizeof suf);
	dp[0] = 0;
	
	ll sum = 0, maxn = 0; // s统计经验前缀和、maxn统计能获得的最大经验
	for(int i = 1; i <= k; i ++){
		if(!vis[c[i]]){ // 如果这是第c[i]种攻击第一次出现
			vis[c[i]] = 1;
			// 背包dp
			for(int j = C * n; j >= b[c[i]]; j --){ // 注意滚动数组要倒着遍历，避免提前计算
				dp[j] = min(dp[j], dp[j - b[c[i]]] + a[c[i]]);
			}
			// 统计后缀最小值
			for(int j = C * n; j >= 0; j --){
				suf[j] = min(suf[j + 1], dp[j]);
			}
		}
		
		sum += a[c[i]];
		if(m <= 0){
			// 防止越界 和 不存在的状态被计入答案
			if(1 - m <= C * n && suf[1 - m] != LLONG_MAX){
				maxn = max(maxn, sum - suf[1 - m]);
				// 这里不用把sum减去经验值，因为回血只是为统计做出的假设，不影响正常进程
			}
			else break; // 否则说明救不回来了，退出循环即可
		}
		else{ // 注意这个else非常关键，因为如果进了上一个if，当前统计上的s应该是减去一部分经验值的，而不是原值
			maxn = max(maxn, sum);
		}
		m -= b[c[i]]; // 和sum同理，这里不用把m回正
	}
	
	cout << maxn << '\n';
}

signed main()
{
	ios :: sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	solve();
	return 0;
}
```

## End

管理员大大辛苦啦~

谢谢大家！

---

## 作者：_Communist (赞：5)

#### Step 0
一个时间复杂度 $O(C\times n^2+k)$ 的做法，应该不会被非随机数据卡掉。

如果 $C$ 变大用指针扫 $2^n$ 状态也是可以做的，但那样就和题解差不多了。
#### Step 1
不妨将抵挡伤害的贡献后置。从前往后扫，令当前血量为 $M$。

- 若 $M>0$，贪心的去前面所有经验。

- 若 $M\leq 0$，此时需要抵挡前面的伤害以回复至少 $-M+1$ 的血量。
#### Step 2
如何快速求出回复 $X$ 血量最小失去的经验值？背包 dp 显然是一种好的方法。而题目中血量值域 $C \leq 10^5+5$，可以通过。

#### Code
```cpp
inline int find(int x) {
	if (x > C * n || suf[x] == 0x3f3f3f3f3f3f3f3f) return -1;
	return suf[x];
}//回复 x 血量至少损失的经验
//do something
for (int i = 1; i <= k; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (i == mn[j]) {//做背包
				for (int l = C * n; l >= b[j]; --l) {
					dp[l] = min(dp[l], dp[l - b[j]] + a[j]);
				}
				for (int l = C * n; l >= 0; --l) suf[l] = min(suf[l + 1], dp[l]);
			}
		}
		int cur = sa[i];//经验前缀和
		if (m <= 0) {//
			int add = find(-m + 1);
			if (add == -1) break;
			cur -= add;
		}
		ans = max(ans, cur);
		m -= b[c[i]];
	}
```

---

## 作者：tkdqmx (赞：3)

出题人题解

### 30pts

直接暴力枚举每种攻击是否要抵消第一次伤害，然后 $O(k)$ 判断哪次攻击是致命伤害，那这一次枚举的答案就是这次攻击及之前获得的经验值了。

### 50pts

首先搜索 $O(2^n)$ 枚举每种攻击是否要抵消第一次伤害，统计答案时 $O(n)$ 计算在每种攻击第一次伤害前血量的损失值，这个过程需要用到前缀和，然后我们就知道致命伤害出现在哪段区间内了，再对这段区间做二分即可，总复杂度 $O(2^n(n+\log k))$。

### 100pts

先将每种攻击按第一次这种攻击的时间排序，在搜索时多开一个前缀和数组，把 50pts 中计算答案的 $O(n)$  替换成二分的 $O(\log n)$ 即可，总复杂度 $O(2^n(\log n +\log k))$。

~~~cpp
#include<bits/stdc++.h>
using namespace std;
#define N 20000005
#define LL long long
bool use[30];
const int M=1e9,C=1e5+5;
LL n,m,k,s,ans,a[30],b[30],ft[30],jma[30],jmb[30],c[N],dy[N],aum[N],bum[N];
void dfs(int x){
    if(x>n){
        LL l=1,r=n+1,tmp;
        jma[x]=jma[x-1],jmb[x]=jmb[x-1];
        while(l<r){
            int mid=(l+r)>>1;
            if(bum[ft[mid]]-jmb[mid]<m)  l=mid+1;
            else r=mid;
        }
        tmp=r,l=min(ft[r-1]+1,k),r=ft[r];
        while(l<r){
            int mid=(l+r)>>1;
            if(bum[mid]-jmb[tmp-1]<m)  l=mid+1;
            else r=mid;
        }
        return ans=max(ans,aum[l]-(l==ft[tmp]?jma[tmp]:jma[tmp-1])),void();
    }
    jma[x]=jma[x-1],jmb[x]=jmb[x-1],dfs(x+1);
    jma[x]+=a[dy[ft[x]]],jmb[x]+=b[dy[ft[x]]],use[x]=1,dfs(x+1);
    jma[x]-=a[dy[ft[x]]],jmb[x]-=b[dy[ft[x]]],use[x]=0;
}
int main(){
    scanf("%lld%lld%lld%lld",&n,&m,&k,&s);
    mt19937 rand(s);
    for(int i=1;i<=n;i++)  a[i]=rand()%M+1,b[i]=rand()%C+1;
    for(int i=1;i<=k;i++){
        c[i]=rand()%n+1;
        if(!ft[c[i]])  ft[c[i]]=i,dy[i]=c[i];
        aum[i]=aum[i-1]+a[c[i]],bum[i]=bum[i-1]+b[c[i]];
    }
    sort(ft+1,ft+n+1),ft[n+1]=k,dfs(1),printf("%lld\n",ans);
}
~~~

---

## 作者：Nagato_ (赞：1)

### Step 1

我们可以对经验值和血量都做一次前缀和，并且进行 $O(2^n)$ 的免疫方案搜索枚举。  
不难发现，此时我们可以将免疫第 $x$ 次攻击视为将血量增加 $b_x$ 点，并将最终能得到的经验减少 $a_x$ 点，然后在完成一次方案的搜索后，对血量的前缀和数组二分。  
此时，我们就能 $O(\log k)$ 的寻找一种免疫攻击的方案（以下简称免疫方案）所能获得的经验值，总体时间复杂度 $O(2^n \log k)$。

### Step 1 补充

显然，至此，现在的做法有一个严重的问题，就是在免疫一次攻击时，不一定能保证在角色血量降到 $0$ 前遇到这次攻击。

例如 攻击 $1$ 的伤害是 $1000$ , 可获得的经验值也是 $1000$ 。攻击 $2$ 的伤害是 $3000$ , 可获得的经验值却只有 $1$ 。血量 $m$ 为 $2000$ 。此时，我们考虑这样的一个攻击序列
$$
1,1,1,1,1,2
$$
显然，无论如何免疫攻击，最多都只能获得 $2000$ 的经验。但若是采取 Step 1 的方法，则会免疫掉攻击 $2$ ，只减少了 $1$ 点经验，却增加了 $3000$ 的血量，足以吃完五个 $1$ ，并且获得 $5000$ 的经验。因此，现在的做法不正确。

~~但实际上该做法可以AC，我觉得是因为用了随机生成数据导致数据极弱。~~

### Step 2
接下来我们就要判断在血量降到 $0$ 之前，被免疫的攻击是否出现过，这决定该免疫方案是否可行。注意，判断只能使用 $O(1)$ 的做法，否则会超时。

那我们该怎么办呢？

我们先假设 Step 1 中二分的结果返回了一个下标 $l$ ，
此时，我们可以得到一个显而易见的结论：  

> 若我们现在的免疫方案选取了 $s$ 个攻击，那么这 $s$ 个攻击都应该在 $ c_{1 \cdots l-1} $ 中出现，而若这 $s$ 个攻击都该在 $ c_{1 \cdots l-1} $ 中出现了，那这个免疫方案一定可行。

显然，如果在血量降到 $0$ 之前，被免疫的攻击 $x$ 没有出现，那么血量 $m$ 加上 $b_x$ 后，下标 $l$ 还是无法增加到该次攻击后，因为这次攻击的伤害就是 $b_x$ 。 反之，如果出现了，那下标 $l$ 一定能增加到这次攻击后。

那么，如何 $O(1)$ 的判断在 $ c_{1 \cdots l-1} $ 中是否出现了这些被免疫的攻击呢？

### Step3

考虑状态压缩。

我们把免疫方案编码成形如 $x_1,x_2 \cdots x_n$ 的 $01$ 字符串，免疫第 $i$ 种攻击，就将 $x_i$ 放为 $1$ 。同时对 $c$ 进行类似前缀和的操作，对于 $c_i$ 而言，只要第 $x$ 种攻击在 $c_{1\cdots i}$ 中出现过，我们就将 $c_{i,x}$ 放为 $1$ 。然后将其视为一个二进制数，存储。

此时我们再次假设 Step 1 中二分的结果返回了一个下标 $l$ ，同时该种免疫方案设为 $x$ 。显然，如果 $c_{l-1,i}$ 为0，但 $x_{i-1}$ 却为 $1$ ，就意味着该种免疫方案不可行，因为在免疫方案中出现了一种攻击，这种攻击没有在 $c_{1\cdots {l-1}}$ 中出现。

如何实现呢？

换句话说，我们希望进行一次位运算，当且仅当 $a=0,b=1$ 时返回 $1$ ，若是返回了 $1$ 则说明该方案不可行。显然，只要将位运算设为 (a^b)&b ( ^ 表示按位异或， & 表示按位与 )即可。

至此，全过程结束。

### 实现

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m,k,s;

int a[30],b[30],c[20000010];

long long exper[20000010] , xp[20000010] , fe[30] , f[20000010] ,ans , to_x;

const int M=1e9,C=1e5+5;
void read()
{
    cin>>n>>m>>k>>s;
    
    mt19937 rand(s);
    
    for(int i=1;i<=n;i++)
    {
    	a[i]=rand()%M+1;
    	
		b[i]=rand()%C+1;
	}
		
    for(int i=1;i<=k;i++)  
	{
		c[i]=rand()%n+1;	
		
		exper[i] = exper[i-1] + a[c[i]];
		xp[i] = xp[i-1] + b[c[i]];
		
		f[i] = f[i-1] ;
		if(!fe[c[i]])
		{
			fe[c[i]] = 1;
			f[i] += ( 1 << c[i] );
		}
	}
}

int down_find(int x) //找到第一个大于等于的数字
{
	int l=1,r=k,mid;
	
	while(l<r)
	{
		mid = (l+r)>>1 ;
		
		if( xp[mid] < x )
			l = mid + 1;
		else
			r = mid ;
	}
	return l;
}

void dfs(int x , long long s_xp , long long s_exper , int s )
{
	if( x >= n+1 )
	{
		to_x = down_find( m + s_xp );
		
		if( !( ( f[ to_x - 1 ] ^ s ) & s ) )
			ans = max(ans , exper[ to_x ] - s_exper );
		
		return;
	}
	
	dfs(x+1 , s_xp + b[x] , s_exper + a[x] , s + ( 1 << x ) );
	
	dfs(x+1 , s_xp , s_exper , s );
	
	return ;
}

int main()
{
	
	read();
	
	dfs(1,0,0,0);
	
	cout<<ans;
	
	return 0;
}
```

---

## 作者：ELECTRODE_kaf (赞：1)

知识点：二分、前缀和

穷举每一种攻击是否跳过第一次，二分攻击序列计算答案。如果决定跳过该攻击，那么在计算的时候把它的代价加到总血量上，并减去它的价值，这样就把统计工作转化成前缀和解决。

实现：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define rep(i,x,y) for(ll i=x;i<=y;i++)

const int M=1e9,C=1e5+5,N=30,K=3e7;
ll n,m,k,s,a[N],b[N],c[K],ps_a[K],ps_b[K],ans;

ll bs(ll x){
	ll l=1,r=k;
	
	while(l<r){
//		cout<<"l="<<l<<",r="<<r;
//		system("pause");
		ll mid=l+r>>1;
		
		if(ps_b[mid]>=x){
			r=mid;
		}else{
			l=mid+1;
		}
	}
	
	return l;
}

void dfs(ll x,ll v,ll hp){
	if(x==n+1){
		ll p=bs(m+hp);
		ans=max(ans,ps_a[p]-v);
	}else{
		dfs(x+1,v,hp);
		dfs(x+1,v+a[x],hp+b[x]);
	}
}

int main() {
	cin>>n>>m>>k>>s;
	mt19937 rand(s);
	for(int i=1; i<=n; i++)  a[i]=rand()%M+1,b[i]=rand()%C+1;
	for(int i=1; i<=k; i++)  c[i]=rand()%n+1;
	
//	rep(i,1,n){
//		cout<<a[i]<<' '<<b[i]<<'\n';
//	}
	
	rep(i,1,k){
		ps_a[i]=ps_a[i-1]+a[c[i]];
		ps_b[i]=ps_b[i-1]+b[c[i]];
//		cout<<ps_a[i]<<' '<<ps_b[i]<<'\n';
	}
	
//	cout<<"bs(m)="<<bs(m)<<'\n';
	dfs(1,0,0);
	cout<<ans;
}
```

---

## 作者：VelvetChords (赞：0)

# P11069 「QMSOI R1」 生熏鱼
## 0.前言
标签是什么，没看到。
## 1.思路
有多种攻击方式，每种攻击会带来一定的经验值和损失的血量。目标是在给定的攻击序列中，尽可能地获取最大的经验值，同时保持血量不低于零。

翻题解的时候看到有人提背包，觉得神奇，马上关掉细细研究。

这道题为什么能用背包？

在这个问题中，物品其实就是随机生成的 $n$ 个项目的抽象形态。每个物品都有对应的价值和重量。而重量就是每个物品的，由 $b_i$ 表示。价值是每个物品的价值，由 $a_i$ 表示，其中 $a_i$ 是第 $i$ 个物品的价值。也就是说，这道题其实可以抽象成 01 背包。因为对于每个物品，你有两个选择：

选择该物品（其实就是放入背包），消耗其对应的重量，并获得其价值。

不选择该物品（也就是不放入背包），不消耗重量，也不获得价值。

知道这是背包以后，就好写多了。设 $dp_i$ 表示当前血量为 $i$ 时的最小经验损失，再开一个数组表示当前状态下，血量为 $i$ 时的最小经验值,我们叫它 $t_i$。

如果当前血量为 $j$，那么可以选择使用第 $i$ 种攻击（消耗 $b_{c_i}$ 的血量），更新状态为 $j-b_{c_i}$。因此，新的经验损失为 $f_{j-b_{c_i}} + a_{c_i}$。我们在这里找 $\min$。

如果血量不足，根据 $t_j$ 检查减去一定血量后的经验值是否可行，并更新最大经验值。

然后，就结束了。

---

## 作者：T_TLucas_Yin (赞：0)

首先，题目的描述有点繁琐了。让我们讲题目描述形式化一下：

> 有 $n$ 种物品，第 $i$ 种物品的价值为 $a_i$，重量为 $b_i$。你有一个容量为 $m$ 的背包，要依次拿起 $k$ 个物品，第 $j$ 个物品是第 $c_j$ 种，一旦有一个物品无法装进背包，后面的物品就都无法获取了。对于每一种物品，你可以选择扔掉拿到的第一个该种物品。求最后能获取的最大价值。

这样这道题目就转化为了一个背包问题。

我们先考虑没有扔掉物品能力的情况。注意到由于所有物品的价值都为正数，所以肯定是拿的物品越多越好。那么从前往后拿物品，到容量不够时退出即为最优情况。

现在考虑加入了扔物品能力。这个变化带来的影响显然是在某些原来不能拿新物品的情况下，可以在之前省掉一些空间，从而能获得后面价值更高的物品。那么我们可以考虑记录下省掉一定空间最少要扔掉多少价值的物品（01 背包板子），然后从前往后取物品，当容量不够时，先判断一下是否可以通过扔掉前面的物品来省出足够的空间，若无法达到则退出，否则在价值中去掉扔掉物品的贡献。

注意此时取到更靠后的物品时总价值不一定更大，所以需要一个变量记录答案的最大值。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int M=1e9,C=1e5+5;
bool flag[105];
int n,a[105],b[105],m,c[20000005],k,S;
long long f[4000005],d[4000005];
signed main(){
	cin>>n>>k>>m>>S;
	mt19937 rand(S);
	for(int i=1;i<=n;++i) a[i]=rand()%M+1,b[i]=rand()%C+1;
	for(int i=1;i<=m;++i) c[i]=rand()%n+1;
	for(int j=n*C+1;j>=0;--j) f[j]=d[j]=3e18;
	f[0]=0;
	long long sum=0,maxn=0;
	for(int i=1;i<=m;++i){
		if(!flag[c[i]]){//同种物品只有第一个能被扔掉
			flag[c[i]]=1;
			for(int j=n*C;j>=b[c[i]];--j) f[j]=min(f[j],f[j-b[c[i]]]+a[c[i]]);
			for(int j=n*C;j>=0;j--) d[j]=min(d[j+1],f[j]);
			//由于回复一定的血量不一定必须刚好回最小值，所以取后缀最小
		}
		sum+=a[c[i]];
		int p=sum;
		if(k<=0){
			if(-k+1<=n*C&&d[-k+1]!=3e18) p-=d[-k+1];
			//回血越少损失的经验就越小。所以回使血量能变为正数的最小值
			else break;
		}
		maxn=max(maxn,p);
		k-=b[c[i]];
	}
	printf("%lld",maxn);
	return 0;
}
```

---

