# Beaver Game

## 题目描述

Two beavers, Timur and Marsel, play the following game.

There are $ n $ logs, each of exactly $ m $ meters in length. The beavers move in turns. For each move a beaver chooses a log and gnaws it into some number (more than one) of equal parts, the length of each one is expressed by an integer and is no less than $ k $ meters. Each resulting part is also a log which can be gnawed in future by any beaver. The beaver that can't make a move loses. Thus, the other beaver wins.

Timur makes the first move. The players play in the optimal way. Determine the winner.

## 说明/提示

In the first sample the beavers only have one log, of $ 15 $ meters in length. Timur moves first. The only move he can do is to split the log into $ 3 $ parts each $ 5 $ meters in length. Then Marsel moves but he can't split any of the resulting logs, as $ k=4 $ . Thus, the winner is Timur.

In the second example the beavers have $ 4 $ logs $ 9 $ meters in length. Timur can't split any of them, so that the resulting parts possessed the length of not less than $ 5 $ meters, that's why he loses instantly.

## 样例 #1

### 输入

```
1 15 4
```

### 输出

```
Timur```

## 样例 #2

### 输入

```
4 9 5
```

### 输出

```
Marsel```

# 题解

## 作者：partychicken (赞：5)

数论+博弈

算不上难题

分三种情况

1.如果有偶数根木条，那就后手获胜，因为可以无耻的模仿，然后愉快地获胜了

2.如果有奇数根木条，那就要看先手的能不能把多出来的那根切没，如果能，就转化为了第一种情况，先后手翻转（~~两级反转~~），所以是先手胜

3.先手做不到，那就呵呵了，后手胜
```
#include<bits/stdc++.h>

using namespace std;

inline bool swin(int a,int min)
{
	int k=sqrt(a)+1;
	for(register int i=1;i<k;++i)
	{
		if(a%i!=0)
		{
			continue;
		}
		if(i>=min&&a/i>1)
		{
			return 0;
		}
		else
		{
			if(i>1&&a/i>=min)
			{
				return 0;
			}
		}
	}
	return 1;
}

int main()
{
	ios::sync_with_stdio(0),cin.tie(0);
	int n,m,k;
	cin>>n>>m>>k;
	if(n%2==0)
	{
		cout<<"Marsel";
	}
	else
	{
		if(swin(m,k))
		{
			cout<<"Marsel";
		}
		else
		{
			cout<<"Timur";
		}
	}
}
```

---

## 作者：ncwzdlsd (赞：1)

~~好爱博弈论~~

通过分析我们可以知道，有以下两种情况：

- 如果 $n$ 是偶数，那么后手必胜，因为他可以模仿先手的每一步；

- 如果 $n$ 是奇数，又要分类讨论：

	- 如果能分割，我们让先手第一次完全切割一根，那么就转化为了后手为“先手”面对偶数根的情况，那么由上面的分析可知，先手必胜；
   
   - 如果不能分割，先手直接输掉。
   
所以问题就转化为判断奇数根或偶数根以及判断先手能否首先处理木棍的问题。

优化：求先手能否首先处理，只用枚举到 $\sqrt{m}$ 即可。

代码主体如下（要自己思考哟！）：
```cpp
    while(~scanf("%d%d%d",&n,&m,&k))
    {
        int flag=0;
        if(n&1)
        {
            for(int i=1;i*i<=m;i++)
                if(m%i==0)
                {
                    if(i>=k&&m/i>1||i>1&&m/i>=k)
                    {
                        flag=1;
                        break;
                    }
                }
        }
        printf("%s\n",flag?"Timur":"Marsel");
    } 
```

---

## 作者：run_away (赞：0)

## 题意

一场博弈游戏，有 $n$ 个长度为 $m$ 木棍。两人轮流进行操作，每次操作可选择一根木棒把它进行任意等分，使得分完后每段长度都小于 $k$。最终无法操作的人判负。

两人都执行最优操作，先手名为 `Timur`，后手名为 `Marsel`，输出最终赢家。

## 分析

可以分为两种情况：

1. $n$ 为偶数，此时无论先手怎么分，后手都可以进行同样操作，先手必败。
2. $n$ 为奇数，则先手需把多出来的一根分完，从而转换为第一种情况的后手，此时先手必胜，否则先手必败。

对于一根木棍，因为是等分，所以最多分成 $\sqrt m$ 份，然后进行 $O(1)$ 判断。

总时间复杂度 $O(\sqrt m)$。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
ll n,m,k;
signed main(){
    n=read(),m=read(),k=read();
    if(!(n&1))puts("Marsel"),exit(0);//n为偶数
    for(ll i=1;i*i<=m;++i){
        if(m%i)continue;//无法等分成n/i份
        if(i>=k&&m/i>1||i!=1&&m/i>=k)puts("Timur"),exit(0);//i为每份长度或i为份数
    }
    puts("Marsel");//先手必败
    return 0;
}
```

---

## 作者：zdq20110120 (赞：0)

## [原题戳这里](https://www.luogu.com.cn/problem/CF78C)

### 题目大意
两只海狸（$\texttt{Timur, Marsel}$）做游戏，有 $n$ 条长度为 $m$ 的木棍，从 $\texttt{timer}$ 开始游戏，每只海狸轮流将一根已有的木棍任意等分，但是要**保证等分后的每一段长度都是不小于 $k$ 的整数**（整数 $m, n, k \leq 10^9$）。

### 情况分类
- 若有偶数根木条，则**后手**每一次都模仿先手的操作即可**获胜**。
- 若有奇数根木条，那么有一下两种情况：
> - 若先手能将木棍分割为偶数根，那么就转化为上面偶数跟木条的情况，所以**先手获胜**。
> - 若先手不能将木棍分割为偶数根，那么**后手获胜**。
### 代码实现
```cpp
#include <bits/stdc++.h>
#define ll long long 
using namespace std;
const int maxn = 1e5 + 5;
ll n, m, k;
bool flag;
int main() {
	ios :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> k;
	if ((n & 1) == 0) {
		cout << "Marsel";
	}
	else {
		for (int i = 1; i * i <= m; i++) {
			if (m % i != 0) {
				continue;
			}
			if (i >= k and m / i > 1 or i > 1 and m / i >= k) {
				flag = true;
				break;
			}
		}
		if (!flag) {
			cout << "Marsel";
		}
		else {
			cout << "Timur";
		}
	}
}
```

---

## 作者：hhhppp (赞：0)

_一道博弈论水题。_ 

## 简述题意

两只海狸（Timur and Marsel）做游戏，有 $n$ 条长度为 $m$ 的木棍，从 Timur 开始，每只海狸轮流将一根已有的木棍任意等分，但要保证等分后的每一段长度都是**不小于** $k$ 的整数。

## 思路

- #### 如果 $n$ 为偶数
	那么后手每一次都可以模仿先手的每一步，因此**后手胜**。
- #### 如果 $n$ 为奇数
	- #### 如果能分割
    先手把木棍切为偶数根，那么就转化为上面 $n$ 为偶数的情况，所以**先手胜**。
   - #### 如果不能分割
   那么**先手输**，因为都没有可以分割的了。

## _那么，理论存在，实践开始。_ 


## 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int main(){
	int n,m,k;
	cin>>n>>m>>k;
	if(n%2==0){//n为偶数的情况 
		cout<<"Marsel"<<endl;
		return 0;	
	}
	//n为奇数的情况 
	int g=sqrt(m)+1;
	for(int i=1;i<g;i++){
		if(m%i!=0) continue;
		if(i>=k&&m/i>1){
			cout<<"Timur"<<endl;
			return 0;
		}
		else if(i>1&&m/i>=k){
			cout<<"Timur"<<endl;
			return 0;
		}
	}
	cout<<"Marsel"<<endl;
	return 0;//完美结束QAQ 
}
```


---

## 作者：ydkxj (赞：0)

# 题解

### 前置算法

**博弈论** ,又称为对策论（Game Theory）、赛局理论等，既是现代数学的一个新分支，也是运筹学的一个重要学科。详情可以点[这里](https://blog.csdn.net/A_Comme_Amour/article/details/79347291)

## 题意

有 $n$ 条长度为 $m$ 的木棍 从 $Timur$ 开始，每只海狸轮流将一根已有的木棍**任意等分** 但要保证等分后的每一段长度都是**不小**于 $k$ 的整数 （$m$，$n$，$k$ 为小于等于 $1000000000$ 的正整数）

从这句话中，我们可以解读出以下几个信息：

- $Timur$ 为先手
- 这道题使用 int 即可
- 需要使用博弈论

所以我们便可以得出以下情况：

1．如果有偶数根木条，那就后手获胜，因为可以无限 copy 先手的操作，然后愉快地获胜了。

2．如果有奇数根木条，那就要看先手的能不能把多出来的那根完整的切完，如果能，就转化为了第一种情况，先手变后手，后手变先手，所以是先手胜。

3．先手做不到，那就寄了，后手胜。


## CODE

```javascript
//抄题解是不好的习惯（但借鉴可以）。 
#include<iostream>
#include<cmath>
using namespace std;
bool hp(int m,int k) {
	int sum=sqrt(m);    //只需枚举到根号n即可 
	for(int i=1; i<=sum; i++) {
		if (m % i != 0)
			continue;
		if (i >= k and m / i > 1) 
			return 0;
		else {                            //题目给的公式将它具象化 
			if (i > 1 and m / i >= k)
				return 0;
		}
	}
}
int main() {
	int n,m,k;
	cin>>n>>m>>k;  
	if(n%2==0)cout<<"Marsel",exit(0); //如果是偶数，那后手直接复制前手的策略即可 
	if(hp(m,k))cout<<"Marsel";
	else cout<<"Timur";
	return 0;
}
```
求过！

---

## 作者：Super_dark (赞：0)

## 题目分析
这是一道简单的博弈论，接下来我们来分析一下。
- 如果 $n$ 为偶数，那么后手只需模仿先手即可获胜。
- 如果 $n$ 为基数，那么我们可以只讨论一根木棍，剩下偶数条木棍。
	- 如果那一根木棍先手不能平分，那么先手必输。
   - 如果那一根木棍先手可以平分，那么先手可以先“完全平分”那一根。那么在接下来的偶数根中，后手就成了“先手”。那么根据上文，先手必胜。

分析结束，放代码。
## 代码实现

```
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int main() {
	scanf("%d%d%d",&n,&m,&k);
	cin>>n>>m>>k;
	if(n&1&&k<=m) {
		for(int i=1; i<=sqrt(m); i++)
			if(!(m%i)&&((m/i>=k&&i>1)||(i>=k&&m/i>1))) {
				printf("Timur");
				return 0;
			}
		printf("Marsel");
		return 0;
	} else printf("Marsel");
	return 0;
}
```


---

## 作者：loser_seele (赞：0)

提供一个复杂度更优的实现。

首先当木头的根数为偶数时显然是后手获胜，只要模仿先手的操作即可。

再考虑木头的根数为奇数的情况，实际上只要处理一根木头的情况即可，因为之后可以使用根数为偶数的时候的策略。

那么问题便转化为判断 $ m $ 的最大因子是否 $ \geq k $，这一步可以用质因数筛法求出最小质因子实现，但这里使用了 Pollard-rho 优化时间复杂度，为 $ \mathcal{O}(m^{\frac{1}{4}}) $。

注意用这种方法实现的话要特判 $ m=1 $ 的情况。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define gc c=getchar()
#define r(x) read(x)
#define ll long long
#define int long long
template<typename T>
inline void read(T&x)
{
    x=0;T k=1;char gc;
    while(!isdigit(c)){if(c=='-')k=-1;gc;}
    while(isdigit(c)){x=x*10+c-'0';gc;}x*=k;
}
#define li inline
#define re register
inline int add(int a,int b,int p)
{
	a+=b;
	if(a>=p)
    a-=p;
	return a;
}
inline int mul(int a,int b,int mod)
{
return (a*b-(int)((long double)a/mod*b)*mod+mod)%mod;
}
ll pow(ll a, ll b, ll m) 
{
  ll ans = 1;
  for (a %= m; b; b >>= 1, a = mul(a, a, m))
    if (b & 1) 
    ans = mul(ans, a, m);
  return ans;
}
ll gcd(ll a,ll b)
{
	return b?gcd(b,a%b):a;
}
ll lcm(ll a,ll b)
{
	return a/gcd(a,b)*b;
}
bool MR_check(ll a, ll p, ll s, int d) 
{
  ll k = pow(a, s, p);
  if (k == 1) return true;
  for (; d; --d, k = mul(k, k, p)) 
  {
    if (k == p - 1) 
    return true;
    if (k == 1) 
    return false;
  }
  return k == 1;
}
bool MR(ll x) 
{
  static const int cnt = 12;
  static const int p[cnt] = { 2, 3, 5, 7, 11, 13, 17, 19, 61, 2333, 4567, 24251 };
  if (x == 1) 
  return false;
  ll s = x - 1; 
  int d = 0;
  while (!(s & 1)) 
  ++d, s >>= 1;
  for (int i = 0; i < cnt; ++i) 
  {
    if (x % p[i] == 0) 
    return x == p[i];
    if (!MR_check(p[i], x, s, d)) 
    return false;
  }
  return true;
}
namespace Pollard_Rho 
{
ll PR_check(ll c, ll p) 
{
  ll y = rand() % p, z = y;
  int k = 1, j = 0;
  while(1145141919810) 
  {
    z = (mul(z, z, p) + c) % p;
    ll t = gcd(p, std::abs(z - y));
    if (t > 1) 
    return t;
    if (++j == k) 
    y = z, k <<= 1;
  }
}
void factor_(ll x, std::vector<ll> &v) 
{
  if (x == 1) return;
  if (MR(x)) { v.push_back(x); return; }
  ll y = x;
  while (y == x) y = PR_check(rand() % x, x);
  factor_(y, v);
  factor_(x / y, v);
}
void factor(ll x, std::vector<ll> &v) 
{
  v.clear();
  if (!(x & 1)) { v.push_back(2); x /= (x & -x); }
  factor_(x, v);
  std::sort(v.begin(), v.end());
  v.erase(std::unique(v.begin(), v.end()), v.end());
}
}
using Pollard_Rho::factor;
signed main()
{
    int n,m,k;
    cin>>n>>m>>k;
    if(n%2==0)
    {
    	cout<<"Marsel";
    	return 0;
    }
    else
    {
    	bool ok=0;
    	vector<int>d;
    	factor(m,d);
    	if(m<=k)
    		ok=0;
    	else if(m/d[0]>=k)
    		ok=1;
    	if(ok)
    		cout<<"Timur";
    	else
    		cout<<"Marsel";
    }
}
```


---

## 作者：Michvior_AC (赞：0)

# Beaver Game 题解

## 题意

有 $n$ 条长为 $m$ 的木棍，$T$ 和 $M$ 两人轮流将一根已有的木棍任意等分，但要保证每次等分完后每一段长度不小于 $k$ 的整数，先无法进行操作的人输（两人绝顶聪明）。你需要判断谁可以获胜。

## 思路

这道题不需要任何信息学博弈论等知识，是道思维好题。

考虑分两种情况:

1. $n$ 为偶数时，后手 $(M)$ 必胜。

证明:

无论先手怎么操作，后手都可以模仿先手进行一样的操作，所以到最后一定是先手先无法进行。

2. $n$ 为奇数时,如果先手能把木棍切成偶数根，那么就和情况 $1$ 一样了，先手变后手，后手成先手。 $(T)$ 必胜。如果不能，那还是 $(M)$ 必胜。

所以这道题就到此为止啦。

$Code:$

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, k;

bool sg(int m, int k)
{
    int sum = sqrt(m) + 1;
    for (int i = 1; i < sum; i++)
    {
        if (m % i != 0)
            continue;
        if (i >= k and m / i > 1)
            return 0;
        else
        {
            if (i > 1 and m / i >= k)
                return 0;
        }
    }
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    if (n % 2 == 0)
    {
        cout << "Marsel";
        return 0;
    }
    if (sg(m, k))
    {
        cout << "Marsel";
    }
    else
    {
        cout << "Timur";
    }
    return 0;
}
```

---

## 作者：Exiler (赞：0)

## 原题

[CF78C Beaver Game](https://www.luogu.com.cn/problem/CF78C)

---

## 思路概述

### 题意分析

简单博弈论水题。给定 $n$ 条长为 $m$ 的木棍，Timur与Marsel两只海狸从中轮流将一条木棍分为任意等分且要保证等分出的木棍长度 $len≥k$ ，且Timur先手。最先无法操作的判为失败，求谁必胜。

### 思路分析

考虑本题数据规模 $n,m,k∈[1,10^9]$ ，不可能DP打表，直接往结论题方向思考。

---

## 算法实现

### $n$ 为偶数的情况

对于 $\frac{n}{2}∈N^*$ 的情况，无论先手方采取任何措施，后手方只需要模仿先手方操作即可。由于一次只能操作一条木棍，所以当先手方将一条木棍切分到不可分时，后手方也可以将另一条木棍切分到不可分。以此类推，最终必然是后手方切分完最后一条木棍，先手方必败。

### $n$ 为奇数的情况

根据博弈论常识不难知道，一个必胜态当且仅当可以在自己操作的一步内将状态转移为必败态。

所以对于 $\frac{n}{2}∉N^*$ 的情况，先手方是否有必胜策略的条件即为能否在一步内将一条木棍切为不可分的状态，即将状态转移为 $n$ 为偶数的情况。

对长度 $m$ 进行因子分解，若 $m$ 存在一个因子 $p$ 满足 $p≠1 \text{ and } \frac{m}{p}≥k$ ，则说明先手方可以将一条木棍等分为 $\frac{m}{p}$ 份，将这条木棍分为不可再分的状态。切分后状态为必败态，故此时先手方必胜，反之必败。

由上文就得到了本题的判断函数（设函数值为 $1$ 则必胜，反之必败）如下：

$$f(x)=\begin{cases}1,\frac{n}{2}∉N^*\text{ and }∃p,p≠1 \text{ and } \frac{m}{p}≥k\\0,\text{otherwise} \end{cases}$$

---

## AC code
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#include<set>
#include<ctime>
#define RI register int
using namespace std;
int n,m,k;
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);
	cin >> n >> m >> k;
	if(n&1 && k<=m)/*n为奇数且k≤m时 才有必胜态的存在可能*/
	{
		for(RI i=1,lim=(int)sqrt(m)+1;i<=lim/*也可以写成i*i<=m 但速度稍慢*/;++i)
			if(!(m%i) && ((i>=k && m/i>1) || (m/i>=k && i>1)))
			{
				/*对于m存在因子i满足i≠1且m/i≥k或i≥k 则Timur可以第一轮就将状态改变为偶数条木棍 即必败态*/
				puts("Timur");
				return 0;
			}
		puts("Marsel");	
	}
	else puts("Marsel");
	return 0;
}
```



---

