# Power Products

## 题目描述

现在给你$n$个正整数 $[a_1,a_2,...,a_n]$ 和一个的正整数$k\geq2$，现在请你求出有多少组 $(i,j)$ ，满足 $(1≤i<j≤n)$且存在一个整数 $x$ 满足 $a_i\times a_j=x^k$

## 说明/提示

样例中有以下几组满足条件的组合

$a_1*a_4=8=2^3$

$a_1*a_6=1=1^3$

$a_2*a_3=27=3^3$

$a_3*a_5=216=6^3$

$a_4*a_6=8=2^3$

一共五组，所以输出为$5$

## 样例 #1

### 输入

```
6 3
1 3 9 8 24 1
```

### 输出

```
5
```

# 题解

## 作者：Melon_Musk (赞：12)

# [CF1225D Power Products](https://www.luogu.com.cn/problem/CF1225D)

### 题目：

给你一个序列 $a$ ，要你求序列中两个数乘起来等于一个数的 $k$ 次方的个数。

形象化的，即询问序列中 $ a_i * a_j = x^k$ 的 $i,j$  $(i<j)$对个数 。题目给出 $k$ 。

### 题解：

我们将 $a_i$ 和 $a_j$ 分解质因数，会得到 

$ a_i = p_1^{A_1} + p_2^{A_2} + p_3^{A_3} + … + p_t^{A_t}$

$ a_j = p_1^{B_1} + p_2^{B_2} + p_3^{B_3} + … + p_t^{B_t}$

那么要求我们得到的 $ a_i * a_j $ 是某数的 k 次方，也就是要求 $A_1 + B_1$ 到 $A_t + B_t$ 都是 $k$ 的 倍数。 即 $ (A_i + B_i) \bmod k = 0$ 。

现在到了怎么匹配的问题，我们把每个数的 $A_i$ 先对 $k$ 取个模，求个哈希值，然后塞到 $map$ 里面，然后在对每个数的哈希值找与他互补的值即可。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define ull unsigned long long 
const int maxn=1e6+7;
const int base=131;
const int mod=1e9+7; 
ll read() 
{
	ll res=0,f=1;
	char c=getchar();
	while(!isdigit(c) && c!='-') c=getchar();
	if(c=='-') f=-1,c=getchar();
	while(isdigit(c)) res=(res<<1)+(res<<3)+c-48,c=getchar();
	return res*f;
}
map<ll,ll> mp;
int tot,n,k;
ll ans;
ull p[maxn];
int isp[maxn],P[maxn],Pid[maxn],a[maxn];
void shai(int n)     //筛一遍质数 
{
	isp[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!isp[i])	P[++tot]=i,Pid[i]=tot;
		for(int j=1;j<=tot && i*P[j]<=n;j++)
		{
			isp[i*P[j]]=1;
			if(i%P[j]==0) break;
		} 
	}
	return ; 
} 
int main()
{
//    freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=read(),k=read();
	for(int i=1;i<=n;i++) a[i]=read();
	shai(100000);
	p[0]=1;
	for(int i=1;i<=tot;i++)
		p[i]=p[i-1]*(ull)base;
	for(int l=n;l;l--)
	{
		int x=a[l];
		ull ha=0,ah=0;
		for(int i=1;i<=tot;i++)
		{
			int cnt=0;
			if(x==1) break;
			if(P[i]*P[i]>x) break;
			if(x%P[i]) continue;
			while(x%P[i]==0) { x/=P[i]; cnt++;} 
			cnt%=k;
			if(cnt==0) continue;
			ha+=p[i]*cnt; ah+=p[i]*(k-cnt);
		}
		if(!isp[x])
			ha+=p[Pid[x]], ah+=p[Pid[x]]*(k-1);
		ans+=mp[ah]; mp[ha]++;
	 } 
	printf("%lld\n",ans);
	return 0;
}
 
```

点个赞吧qwq

---

## 作者：Tarsal (赞：7)

CF1225D：

题意：$a_i * a_j = x^k$ 求有多少组不同的$(i,j)$对

很妙的一道hash题/雾

对于原来的柿子：
$a_i * a_j = x^k$

我们可以转化成一种什么问题呢？

看到后面的 $x^k$你就会想到分解原式，利用唯一分解定理可以得出：

$$a_i = \prod_{i = 1}^{n}{p_i}^{A_i}$$
$$b_i = \prod_{i = 1}^{n}{p_i}^{B_i}$$
$$x = \prod_{i = 1}^{n}{p_i}^{C_i}$$

再看回原来的柿子，可以得到：

$$\prod_{i = 1}^{n}{p_i}^{A_i} * \prod_{i = 1}^{n}{p_i}^{B_i} = \prod_{i = 1}^{n}{p_i}^{C_i^{k}}$$

化简：

$$\prod_{i = 1}^{n}{p_i}^{A_i + B_i} = \prod_{i = 1}^{n}{p_i}^{C_i^{k}}$$

因为对于所有 $p_i$都是质数，且对于所有 $C_i$都是未定的值，所以只要满足：
$A_i + B_i = k * t$ 即 $(A_i + B_i) \% k = 0$

那么这个问题解决了，接下来就是要匹配了，肯定不可以 ~~$n^2$暴力~~ 

那么就是hash出场了，众所周知 $hash$ 是个很玄学的东西，你把每个 $a_i$分解出来的 $A_i$ 看出一个字符串，并对它$(A_i)$和它的互补$hash$串$(B_i)$进行 $hash$运算记录下来，并且用神器$map$记录每个$hash$出现的个数，然后最后只要$O(n)$统计一下它的互补$hash$串的个数就行了。


---

## 作者：aRenBigFather (赞：5)

## 0x01 大体思路

对于一个数，找到和它相乘符合题意的数有多少个，加入答案

## 0x02 简单推导

可以发现，设当前正处理的数为 $i$，将其分解质因数过后的结果为

$i = {p_1}^{x_1}{p_2}^{x_2}{p_3}^{x_3}...{p_t}^{x_t}$

符合与$i$配对的数$j$，当且仅当将$j$分解质因数后

$j = {p_1}^{y_1}{p_2}^{y_2}{p_3}^{y_3}...{p_t}^{y_t}$

对于每个质因数$p_i$，$x_i+y_i$为$k$的整数倍的时候，$i$与$j$成功配对

因为 $i * j = {p_1}^{x_1+y_1}{p_2}^{x_2+y_2}{p_3}^{x_3+y_3}...{p_t}^{x_t+y_t}$，此时$i*j$必为某数$X^k$

## 0x03 问题转化

现在的问题变为对于当前处理的$i$，如何找到符合**0x02**所提到的性质的数有多少个

但是要找对应质因数指数加起来为$k$倍数的，可能加起来为$k$的一倍，也可能两倍...等等很多情况

为了化简这样的问题，这里可以将每个数都分解质因数，然后将每个质因数的指数对$k$取个模，这样就相当于要找到有哪一些数$j$和当前的这个数$i$的对应质因数指数相加起来为$k$就行了。

## 0x04 实现过程

对于寻找符合要求的数$j$有多少个，这里可以采用的方法为**哈希 + std::map**

我们对每个数质因数指数情况做一次哈希，指数情况相同的数将得到相同的哈希值

我们使用`std::map`存储对应哈希值下有多少个数，然后从后往前处理每一个数

将每一个数分解质因数，边分解的同时，可以边计算出当前这个数$i$的哈希值**xhash**，以及符合与$i$匹配的$j$的哈希值**aimhash**。

最后，查找map里面是否有符合要求的$j$的哈希值**aimhash**，如果有，那么答案加上哈希值为**aimhash**的数的个数

最后在**xhash**的位置个数+1

## 0x05 代码

这里使用的是`unsigned long long` 自然溢出版本的哈希，$hashbase=2333$

```cpp
# pragma G++ optimize "O2"
# pragma GCC optimize "O2"
# pragma G++ optimize "O3"
# pragma GCC optimize "O3"
# pragma G++ optimize "Ofast"
# pragma GCC optimize "Ofast"
#include <bits/stdc++.h>
#define LL(x) static_cast<long long>(x)
using namespace std;
#define rg register
typedef long long ll;
typedef unsigned long long ull;
inline int read(){
	rg char ch = getchar();
	register int ret = 0;
	while(!(ch >= '0' && ch <= '9')) ch = getchar();
	while(ch >= '0' && ch <= '9') ret = (ret << 3) + (ret << 1) + (ch ^ 48),ch = getchar();
	return ret;
}
int n,k;
const int maxn = 200010;
const int hashbase = 2333;
const int maxcnt = 60000;
int a[maxn];
int prime[maxn],cnt=0;
int primeid[maxn];
bool vis[maxn];
ull hashfac[maxn];
void initPrime(){
	vis[1] = 1;
	for(rg int i=2;i<100010;i++){
		if(!vis[i]) {
			prime[++cnt] = i;
			primeid[i] = cnt;
		}
		for(rg int j=1;j<=cnt;j++){
			if(prime[j] * i >= 100010) break;
			vis[prime[j] * i] = true;
			if(i % prime[j]) break;
		}
	}
}
void initHash(){
	hashfac[1] = hashbase;
	for(rg int i=2;i<=maxcnt;i++) hashfac[i] = hashfac[i-1] * hashbase;
}
map<ull,int> mp;
ll ans = 0;
void solve(int x){
	ull xhash = 0;
	ull aimhash = 0;
	int bakx = x;
	for(rg int i=1;i<=cnt;i++){
		if(x == 1) break;
		if(prime[i] * prime[i] > x) break;
		if(x % prime[i] == 0){
			int pcnt = 0;
			while(x % prime[i] == 0){
				x /= prime[i];
				pcnt++;
				if(pcnt >= k) pcnt -= k;
			}
			xhash += hashfac[i] * pcnt;
			if(pcnt != 0){
				aimhash += hashfac[i] * (k - pcnt);
			}
		}
	}
	if(x != 1){
		xhash += hashfac[primeid[x]];
		aimhash += hashfac[primeid[x]] * (k-1);
	}
	if(mp.count(aimhash)){
		ans += mp[aimhash];
	}
	mp[xhash]++;
}
int main(){
	n = read(),k = read();
	for(rg int i=1;i<=n;i++){
		a[i] = read();
	}
	initPrime();
	initHash();
	
	for(rg int i=n;i>=1;i--){
		solve(a[i]);
	}
	
	printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：mraymes (赞：4)

本文将同步到 [Hexo 博客](https://mraymes.github.io/).

题目让你求 ${ a_1, a_2, a_3, \cdots, a_n }$ 中能满足积为形如 $x^k$ 的数的数对个数 ($k$ 是给定的), 第一反应便是将所有可能的 $x^k$ 枚举出来, 并且对于每一个数都枚举一遍因子, 计算符合条件的数对个数.

<!--more-->

对于 $k > 2$ 的情况, 这种方法能卡进时限, 而对于 $k = 2$ 的情况来讲, 这种方法会超时, 因此我们就要想一种适用 $k = 2$ 并且更加高效的方法.

如果一个数 $n$ 中已经有了形如 $x^2$ 的因子, 那么将 $\dfrac{n}{x^2}$ 与任何一个数相乘是不会影响积是否是一个完全平方数. 换一句话说, 如果 $nm$ 是一个完全平方数, 那么 $\dfrac{nm}{x^2}$ 也是一个完全平方数; 如果 $\dfrac{nm}{x^2}$ 不是完全平方数, 那么 $nm$ 也不是完全平方数.

当我们对 $a$ 中所有的数都如此处理后, 数对的个数就等于新数组中, 满足两个数相等的数对的个数. 如果两个数不等, 那么肯定不能相乘得到完全平方数, 因为所有完全平方因子已经去除了.

最后有一个坑点: 不要用快速幂求符合条件的形如 $x^k$ 的数. 搞不好就会错. 取模的操作也是不可取的, 因为超出了范围也无法知道. ~~这是个人亲身经历~~

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int n;
int m;
int exponent; // 指数
ll pmax;
int nmax;
int a[100001];
ll b[100001];
int cnt[100001];
ll ans = 0;

template <typename T>
inline T read() {
    T x = 0;
    T multiplier = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            multiplier = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch & 15);
        ch = getchar();
    }
    return x * multiplier;
}

int main() {
    n = read<int>(), exponent = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
    }

    if (exponent == 2) { // 指数为 2
        for (int i = 1; i <= n; i++) {
            for (int j = 2; j * j <= a[i]; j++) {
                while (a[i] % (j * j) == 0) { // 有完全平方因子
                    a[i] /= j * j; // 去除因子
                }
            }
            cnt[a[i]]++; // 桶
            nmax = max(nmax, a[i]); // 最大值
        }

        for (int i = 1; i <= nmax; i++) {
            // 处理后值为 i 的数中任选两个, C(cnt[i], 2)
            ans += 1LL * cnt[i] * (cnt[i] - 1) / 2;
        }
        printf("%lld\n", ans);
    } else {
        for (int i = 1; i <= n; i++) {
            cnt[a[i]]++; // 还是桶
        }

        // 排序以便取最大值 (nmax) 以及成绩最大值 (pmax)
        sort(a + 1, a + n + 1);
        nmax = a[n];
        pmax = 1LL * a[n - 1] * a[n];

        // b[i] 为 i 的 k 次方
        for (int i = 1; true; i++) {
            b[i] = 1;
            for (int j = 1; j <= exponent; j++) {
                b[i] *= i;
                if (b[i] > pmax) { // 越界就退出
                    b[i] = -1;
                    break;
                }
            }
            if (!~b[i]) { // 等价于 b[i] == -1
                m = i - 1; // m 为最大底数
                break;
            }
        }

        for (int i = 1; i <= m; i++) {
            // 枚举因子
            for (int j = 1; 1LL * j * j <= b[i]; j++) {
                if (b[i] % j == 0) {
                    ll k = b[i] / j;
                    if (k > nmax) { // 越界了
                        continue;
                    }
                    if (j ^ k) { // 两个因子不相等, 直接相乘
                        ans += 1LL * cnt[j] * cnt[k];
                    } else { // 两个因子相等, C(cnt[j], 2)
                        ans += 1LL * cnt[j] * (cnt[j] - 1) / 2;
                    }
                }
            }
        }

        printf("%lld\n", ans);
    }

    return 0;
}
```



---

## 作者：thjkhdf12 (赞：2)

题目以为给定一个数组，计算有多少组数的乘积开$k$次方是整数且一组数倒过来算是相同的（因为要求$i<j$）

对于一个可以开$k$次方的数，分解其质因子，必然有每个质因子的数量都是$k$的倍数，举例比如$k$为$2$，$1600$分解质因子为$1600=2*2*2*2*2*2*5*5$，其中有$3k$个$2$和$k$个$5$，开$k(2)$次方后为$40=2*2*2*5$，包含$3$个$2$和$1$个5，所以可见，如果两个数的乘积开$k$次方是整数，那么这两个数一定包含加起来是$k$的倍数个相同的质因子，那么这个问题就转变成了求出一个数的质因子序列，寻找与它互补的质因子序列（互补：两个数所有质因子个数加在一起都是$k$的倍数）

于是本题得解，对于序列数量可以使用$map$保存，$map$的键值默认是$0$，每次扫到一个数就把这个数序列对应的键值++就可以了

**由于蒟蒻我是看了dalao的代码才想出来的，可能代码与一些dalao相似度很高，特此声明绝非抄袭**

```cpp
#include<iostream>
#include<vector>
#include<map>
using namespace std;

typedef pair<int, int> intpair;

const int maxn = 100010;

int minprime[maxn];
map<vector<intpair>, int>cnt;
vector<intpair>sub;
vector<intpair>csub;
int n, k;
int a[maxn];
unsigned long long int ans;	//ans很大，会超出int范围

void init()
{//求出所有数的最小质因子，省去对质因子个数序列进行排序的麻烦
	for (int i = 2; i <= maxn; i++)
	{
		if (minprime[i]) continue;	//不是质数
		minprime[i] = i;	//质数的最小质因子是自己
		for (int j = i; j <= maxn; j += i)
		{
			if (!minprime[j]) minprime[j] = i;
            //j是i的倍数，j的最小质因子是i
		}
	}
}

inline void divide(int a)
{
	int pro;	//表示质因子数量
	int t;
	while (a != 1)
	{
		t = minprime[a];
		pro = 0;
		while (a != 1 && !(a % t))
		{
			a /= t;
			(pro += 1) %= k;	
            //由于质因子数量和只要是k的倍数就可以了，所以对k取模
		}
		if (pro)	
        //如果某质因子的个数本来就是k的整数倍，那就不必加入序列
		{
			sub.push_back(intpair(t, pro));	
            //sub为这个数的质因子数量序列
			csub.push_back(intpair(t, k - pro));
            //csub为这个数的互补序列
		}
	}
}

int main()
{
	init();
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++)
	{
		divide(a[i]);
		ans += cnt[csub];	//ans+=互补序列的数量
		cnt[sub]++;	//这种序列的数量++
		sub.clear();
		csub.clear();
	}
	cout << ans;
	return 0;
}
```

---

## 作者：逆流之时 (赞：2)

昨天第一次打CF，虽然直接specialist, 1462，但卡在了这题。

先给出官方题解：

https://codeforces.com/blog/entry/70898  

题意简析：从n个数中选出两个数，使两个数的积为k次方数，求符合题意的方案数。

官方方法是用了map，但我考试时想到了一种特殊的方法。我昨天做了[LOJ10050 The XOR Largest Pair](https://loj.ac/problem/10050)这题，于是想到了用字典树的解法：因为这些数可以唯一分解，所以用字典树的边存储质数的指数，根据当前节点的深度判断这个节点往下连的边对应的质数。

结果我发现这个做法的细节非常多，导致我后来又调了两个小时。  

首先是因为字典树空间大，所以需要控制字典树的每个节点的边数。虽然`k<=100`，但是我们知道$2^{16}=65536,2^{17}>100000$。我一开始没有仔细思考，只设定边数为16。但卡在了第9组数据（第9组数据n=100000，k=32，一半是1，一半是65536，可以用这组数据对拍）。所以边数应为32（因为k最大为32，即两个65536相乘）。

但是，这并不代表k>32时就可以输出0，因为此时还有两个1相乘的情况，需要特判一下（第8组数据就是100000个1）。结果我没有开long long，又浪费了提交次数。  
设$a={p_1}^{c_1}{p_2}^{c_2}...{p_m}^{c_m}$，当$ab=x^k$，有$b={p_1}^{d_1}{p_2}^{d_2}...{p_n}^{d_n}$，且$c_i+d_i=yk(y \in Z)$。所以我们可以把两个数分解质因数后得到的质数的次数模一下k。我们每次插入一个数，并在已插入的数字中寻找与这个数相乘满足题意的数。当我们插入一个数，用`p`表示所在节点，用`p1`表示往答案方向走的节点，如果将要往`trie[p][sum]`走（sum是当前节点所在字典树层数对应的质数模k的值），就把`p1`往`trie[p1][(k-sum)%k]`走，如不能走则无解。

当$p$到达了最终位置时，我们用一组vector存一下这个数出现的次数。

为了减少时间和空间，我只把$sqrt(100000)=317$以内的质数和他们的次数存在字典树，当x除尽317以下的质数时，x最多只剩下一个大于317，且次数为1的质数。我们同样放到一个vector里，访问到最终节点时，在这个节点的vector里逐个比较。

但字典树的大小比较难确定。本地的随机数据下字典树不超过$2n$层，但实际下我为了保险，开了5000000卡空间。

好像说得不是非常清楚，直接上代码讲解吧。

```
#include<cstdio>
#include<vector>
using namespace std;
const int N=500000;
int trie[N][33],tot;
int a[N];
int n,k;
long long ans;
int prime[70],cnt;
vector<int> v[N],vis[N];
void pri(){//筛掉371以内的质数
	bool vis[420]={};
	for(int i=2;i<=317;i++){
		if(!vis[i])prime[++cnt]=i;
		for(int j=i*i;j<=317;j+=i)vis[j]=1;
	}
}
void insert(int x){//插入一个数，同时查找之前插入的数中与x相乘满足题意的数
	int p=0,p1=0;//p是插入的数的当前节点，p1是查找之前对应的数的节点
	for(int i=1;i<=cnt;i++){
		int sum=0;
		while(x%prime[i]==0)x/=prime[i],sum++;
		sum%=k;
		if(!trie[p][sum])trie[p][sum]=++tot;
		p=trie[p][sum];
		if(p1!=-1&&trie[p1][(k-sum)%k])p1=trie[p1][(k-sum)%k];//p1与p往刚好相反的方向走
		else p1=-1;
	}
	if(p1!=-1){
		for(int i=0;i<v[p1].size();i++){//比较一下，更新答案
			if(v[p1][i]==x){
				ans+=vis[p1][i];
				break;
			}
		}
	}
	bool flag=0;
	for(int i=0;i<v[p].size();i++){//插入
		if(v[p][i]==x){
			flag=1;
			vis[p][i]++;
			break;
		}
	}
	if(!flag){
		v[p].push_back(x);
		vis[p].push_back(1);
	}
}
int main(){
	scanf("%d%d",&n,&k);
	if(k>32){//特判
		long long sum=0;
		for(int i=1,x;i<=n;i++){
			scanf("%d",&x);
			if(x==1)sum++;
		}
		printf("%lld",sum*(sum-1)/2);
		return 0;
	}
	pri();
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d",&x);
		insert(x);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：xukuan (赞：1)

这题还是有点坑的。

先讲一个错误的思路：

我们把所有形如$x^k$形式的数全部找出来，统计每个数在$a$中出现了几次。然后枚举每一个$a_i$，判断次数

这个做法的时间复杂度是$O(n log_k \sum_{i=1}^n a_i)$

在$k \geq 3$的时候可以通过，但这题恶心就恶心在有$k==2$的情况。

注意有一个特殊性质：如果两个数之积是k次方，那么二者的质因子次数之和一定是$k$的倍数。

一种正确思路是对$k==2$的情况做特别处理，把每一个$a_i$分解质因数之后判断$a_i$中有几个质因子$k$，然后直接除。

另外就是用map直接做了

代码：

```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
#define ull unsigned long long
using namespace std;

const ll N=200010,base=19260817;
ll n,k,ans,cnt,a[N],v[N],prime[N],primeid[N];
ull mi[N];
map<ull,ll> mp;

inline ll read(){
    ll x=0,tmp=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-') tmp=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        x=(x<<3)+(x<<1)+(ch^48);
        ch=getchar();
    }
    return tmp*x;
}

inline void getprime(){
    v[1]=1;
    for(ll i=2; i<=100010; i++){
        if(!v[i]){
            prime[++cnt]=i;
            primeid[i]=cnt;
        }
        for(ll j=1; j<=cnt; j++){
            if(prime[j]*i>=100000) break;
            v[prime[j]*i]=1;
            if(i%prime[j]) break;
        }
    }
}

inline void gethash(){
    mi[0]=1;
    for(ll i=1; i<=60000; i++) mi[i]=mi[i-1]*base;
}

inline void solve(ll t){
    ull x=0,y=0;
    ll bak=t;
    for(ll i=1; i<=cnt; i++){
        if(x==1) break;
        if(prime[i]*prime[i]>t) break;
        if(t%prime[i]==0){
            ll p=0;
            while(t%prime[i]==0){
                t/=prime[i];
                p=(p+1)%k;
            }
            x+=mi[i]*p;
            if(p) y+=mi[i]*(k-p);
        }
    }
    if(t!=1){
        x+=mi[primeid[t]];
        y+=mi[primeid[t]]*(k-1);
    }
    ans+=mp[y];
    mp[x]++;
}

int main(){
    n=read(); k=read();
    for(ll i=1; i<=n; i++) a[i]=read();
    getprime(); gethash();
    for(ll i=n;  i>=1; i--) solve(a[i]);
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：reyik (赞：1)

~~好不容易找到一个div1的~~

这题要乘积是一个数的$k$次

显然意味着每一个质因数的指数和要是$k$的倍数

用一个$vector$存下每一个数的质因数分解结果为$x$，注意指数要$mod$ $k$，并且不记录$mod $ $k=0$的情况

每一个数在质因数分解的时候记录与$x$相同质因数相加是$k$的倍数的状态为$x1$

用map维护每一个状态的合法总数，答案加上$mp[x1]$,把$mp[x]$$+1$就好了

code::

```cpp
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map>
#include <vector>
using namespace std;
map <vector< pair<int,int> > , int > mp;
vector<pair<int,int>> x,x1; 
int n,k,a[300005];
long long ans=0;
int main() {
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;++i) {
		scanf("%d",&a[i]);
		x.clear();x1.clear();
		int aa=a[i];
		for (int j=2;j*j<=a[i];++j) {
			int tot=0;
			while(aa%j==0) {
				++tot;
				aa/=j;
				tot%=k;
			}
			if(!tot) continue;
			x.push_back({j,tot});
			x1.push_back({j,k-tot});
		}
		if(aa!=1) {
			x.push_back({aa,1});
			x1.push_back({aa,k-1});
		}
		ans=ans+mp[x1];
		++mp[x];
	}
	printf("%lld\n",ans);
}
		
```

---

## 作者：int1 (赞：0)

给个比较离谱的做法吧。

值域只有 $10^5$，因此两个数的乘积只有 $10^{10}$ 级别，在 $k \ge 3$ 的时候只有不到 $3 \times 10^3$ 个有效的 $x$ 能满足 $x^k$ 在范围内。所以这部分可以直接暴力。

$k = 2$ 的情况，因为一个数 $n$ 只有不超过一个 $> \sqrt n$ 的质因子，所以可以根据这个质因子将所有的数分类，那么只有同类的数之间才能产生贡献（只有同时具有这个质因子才能使得乘积这个质因子的指数为偶数）。

对于 $\le \sqrt n$ 的质因子，将它们指数的奇偶性压成一个二进制数，在同类数的哈希表内查询相同奇偶性的数个数即可。

这部分有个坑点是 $< \lceil\sqrt{10^5}\rceil = 317$ 的质数个数略大于 $64$，因此用一个 $64$ 位整数是压不下的，一个解决方案是直接开 `__int128`。vp 的时候因为这个送了好几发罚时/px


```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>

typedef long long LL;

const int Maxn = 1e5 + 5, A = 317;

__gnu_pbds::gp_hash_table<long long, int> c;
std::map<__int128, int> g[Maxn];

bool vis[Maxn]; int pri[Maxn], cp;

void sieve(int N) {
	for(int i = 2; i <= N; ++i) {
		if(!vis[i]) pri[++cp] = i;
		for(int j = 1; j <= cp && pri[j] <= N / i; ++j) {
			vis[i * pri[j]] = 1;
			if(i % pri[j] == 0) break;
		}
	}
}

LL pk[Maxn]; int cc;

const __int128 I = 1;

int main() {
	LL ans = 0;
	int n, k, x; std::cin >> n >> k;
	if(k >= 3) {
		for(int i = 1; i <= 3000; ++i) {
			pk[i] = 1;
			bool flag = 1;
			for(int j = 1; j <= k; ++j) {
				pk[i] *= i;
				if(pk[i] > 10000000000ll) {
					flag = 0;
					break;
				}
			}
			if(!flag) break; cc = i;
		}
		while(n--) {
			std::cin >> x;
			for(int i = 1; i <= cc; ++i) {
				if(pk[i] % x) continue;
				ans += c[pk[i] / x];
			}
			c[x]++;
		}
	} else {
		sieve(100000);
		while(n--) {
			std::cin >> x; __int128 S = 0;
			for(int i = 1; pri[i] <= 100000 / pri[i]; ++i) {
				int p = pri[i];
				while(x % p == 0) {
					x /= p;
					S ^= (I << (i - 1));
				}
			}
			ans += g[x][S];
			g[x][S]++; 
		}
		std::cout << ans;
	}
	return 0;
}
```

---

## 作者：Sweetlemon (赞：0)

#### CF #596 Div. 2, D (CF1225D), Power Products

这题非常巧妙，非常值得一做！

两个数的积为 $k$ 次方数，当且仅当每一质因子的次数和都是 $k$ 的倍数。

我们把每一个数的质因数分解的每一个次数都模 $k$，那么同一对里的两个数，一个的次数为 $t$，另一个的次数就必须是 $-t$（$\mod{k}$ 同余意义下）。

首先当然是有一个暴力枚举的思路——枚举数对中靠后的一个数，找它之前有多少可以与它组成“合法数对”（满足上一段所述条件）的数，累加即可。

沿用暴力枚举的思路，如果“找”这一步能用 $O(\log n)$ 的复杂度解决，那么问题就解决了。

如果我们把整数用质因数分解向量形式表示，那么我们也就需要对于一个特定的 $(a_2,a_3,a_5,\cdots)$（指这个数 $2,3,5,\cdots$ 的次数），找到向量 $(-a_2,-a_3,-a_5)$ 的个数。

向量和字符串非常类似（事实上向量 (vector) 就是序列嘛，字符串也不就是 vector<char> 嘛），因此我们可以考虑用字符串的方法来解题。（事实上这句话是赛后总结各种做法的时候才悟出来的。）

从字符串的角度考虑，这就是一个——插入字符串、查询字符串出现次数的问题。

这个问题有两种解法。

一是利用 Trie。当然这题中 Trie 有很多需要调整的地方，比如直接开会 MLE，需要各种分条件优化等（比如把质因子按 $\sqrt{n}$ 分治）。这个可以参考 [$\textcolor{red}{\text{逆流之时}}$](https://www.luogu.org/space/show?uid=144740) 的[题解](https://www.luogu.org/blog/returntime/solution-cf1225d)。

二是利用 Hash（Hana~!）。如果我们能有一种把这些向量准确地 Hash 的方法，就很容易判断是否存在了。

回忆一下哥德尔不完备定理的证明过程，哥德尔是把逻辑公式的字符表示成数，再把数的向量 hash 成自然数的吧？

这个 hash 方法对于一般字符串来说完全不可行，因为 hash 值随随便便就会变得很大。

但我们的向量本来不就是质因数分解向量嘛！这就说明即使把我们的向量用质因数分解方法表示，它也不会很大！

于是，我们的思路就是，对于每一个数，用一个“指数模 $k$ 后的数”来**代表**它。

例如，当 $k=3$ 时，$2^4\times 3^3 \times 7^2 \times 11^1$ 可以用 $2^1\times 3^0 \times 7^2 \times 11^1$ 来代表。

我们每次寻找时只需寻找这个数所需的向量的代表数，如上例中数要配对只需寻找 $2^2\times 3^0 \times 7^1 \times 11^2$ 即可。

接下来似乎就没有问题了。存哈希值用一个 multiset 就可以了吧。

然而……lower_bound 和 upper_bound 之间的距离怎么算呢？

用 std::distance 吧？然而，复杂度：**线性**。

干脆用 multiset::count 吧？复杂度：与容器大小的对数和找到元素的个数成**线性**，也就是说，复杂度是 $O(v+\log n)$ 的，其中 $v$ 指 count 的返回值。
  
上述两个复杂度的参考资料：

[std::distance](https://zh.cppreference.com/w/cpp/iterator/distance)
  
> 线性。

> 然而，若 InputIt 额外满足遗留随机访问迭代器 (LegacyRandomAccessIterator) 的要求，则复杂度是常数。
  
[std::multiset::count](https://zh.cppreference.com/w/cpp/container/multiset/count)

> 与容器大小成对数，加上与找到的元素数成线性。 

所以最终我们还是选择了 map……

因此这题有一个额外的价值，那就是科普了上述两个函数的复杂度，尤其是 multiset::count 的诡异复杂度。

附代码。

（我第一次交这篇题解的时候看错题号了……交到了 CF 596D 上去……太丢人了）

```cpp
#include <cstdio>
#include <cctype>
#include <map>
#include <algorithm>
#define MAXIOLG 25
#define FILENAME(x) \
freopen(x".in","r",stdin); \
freopen(x".out","w",stdout);
#define MD(x) (((x)>=MOD)?((x)-=MOD):(0))
#define MAXN 100005
#define N 100000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef ll io_t;

io_t shin[MAXIOLG];
io_t seto(void); //快读
void ayano(io_t x,char spliter='\n'); //快写
    
int minp[MAXN]={0};
int prime[MAXN],pr=0; //质数筛
int a[MAXN];
int mxdg[MAXN]; //防越界处理,每个数不超过 1e5 的最大次幂
map<ll,int> st;
void make_p(int n); //线性筛
ll kasumi(ll a,ll b);
    
int main(void){
    make_p(100000);
    int n,k;
    ll ans=0;
    n=seto(),k=seto();
    for (int i=1;i<=n;i++)
        a[i]=seto();
    mxdg[1]=0; //无意义
    //计算每个数不超过 1e5 的最大幂
    for (int i=2;i<=N;i++){
        int tans=1;
        ll tx=i;
        while (tx*i<=N)
            tans++,tx*=i;
        mxdg[i]=tans;
    }
    for (int i=1;i<=n;i++){
        ll x=a[i]; //当前枚举数列的后一个数为 x
        ll y=1; //x 的 hash 为 y
        ll u=1; //x 所匹配的 hash 为 u
        int uok=1; //防溢出处理, 如果 x 所匹配的数超过了范围则此变量为 0
        while (x>1){
            int tdeg=0; //此质因数的次数
            //质因数分解
            int tminp=minp[x];
            while (minp[x]==tminp)
                x/=tminp,tdeg++;
            tdeg%=k; //次数模 k
            y*=kasumi(tminp,tdeg); //计算 x 的 hash
    
            int udeg; //x 所匹配的数的此项次数
            udeg=(k-tdeg)%k;
            
            if (udeg>mxdg[tminp]) //如果超过了 1e5 的范围
                uok=0;
            else
                u*=kasumi(tminp,udeg);
        }
        (uok && st.count(u))?(ans+=st[u]):(0); //如果存在 x 所匹配的数, 则累加
        //将 x 的 hash 加入 map
        if (st.count(y))
            st[y]++;
        else
            st[y]=1;
        
    }
    ayano(ans); //输出答案
    return 0;
}
    
void make_p(int n){
    //线性筛
    int nd2=n>>1;
    minp[1]=0;//No meaning
    for (int i=2;i<=n;i++){
        if (!minp[i]){
            minp[i]=i;
            prime[pr++]=i;
        }
        int t;
        for (int j=0;j<pr && (t=prime[j]*i)<=n;j++){
            minp[t]=prime[j];
            if (prime[j]==minp[i])
                break;
        }
    }
}
    
ll kasumi(ll a,ll b){
    //快速幂
    ll ans=1;
    while (b){
        (b&1)?(ans*=a):(0);
        a*=a,b>>=1;
    }
    return ans;
}
    
io_t seto(void){
    //快读
    io_t x=0;
    char ch=getchar();
    int symbol=0;
    while (!isdigit(ch))
        (ch=='-')?(symbol=1):(0),ch=getchar();
    while (isdigit(ch))
        x=(x*10)+(ch-'0'),ch=getchar();
    return (symbol)?(-x):(x);
}
void ayano(io_t x,char spliter){
    //快写
    if (!x){
        putchar('0'),putchar(spliter);
        return;
    }
    if (x<0)
        putchar('-'),x=-x;
    int len=0;
    while (x){
        io_t d=x/10;
        shin[len++]=x-d*10;
        x=d;
    }
    while (len--)
        putchar(shin[len]+'0');
    putchar(spliter);
}
```

---

## 作者：ql12345 (赞：0)

### 废话：

- 团队里直接就“数论 练习3”，也没想hash，也用不着呀！为啥题解都说hash？

	~~就是数学瞎搞~~

- 一开始竟然想的思路：

	k>4的时候找出所有范围内的可能的k次方数（不到300个），然后双指针统计乘积等于每个数的方案数

	2<=k<=4的时候用现在想的这个正解。。。。。。

	然后发现正解直接用就行~

### 前置知识：

1. 线性筛质数

1. 快速幂

1. ~~快读~~

1. ~~简单的压行技巧~~

### Solution：

- 肯定先想到什么每个质因子指数之和都是k的倍数之类的。。。

	然后就**显然**可以发现对一个数，它自己有k个是没用的，所以读入的时候，将它质因子分解，指数大于k的直接%k

	接下来对于一个元素来说，它要找的就是与它质因子指数关于k互补的，因为不会出现乘积里有它没有的质因子的情况（这样的话，这个质因子指数为k的倍数，已经被完全消去了）

- 质因子分解的话，试除法肯定是不行的（大量不是约数的数浪费时间）

	线性筛质数的时候不是把mindiv筛出来了嘛，用呀！肯定不会被不是约数的数打扰了吧！复杂度不会高于log

- 最后一个Part了，可能是跟hash有点关系吧

	任务：已经确定每个数的目标~~另一半（/xyx）~~，统计对数
    
    考虑一对中后面那个点来表示这一对，每到一个点，直接找他前面记录过的目标数就行了，目标数？桶呀

### Code：

（众大佬为什么都写那么长呀？）

```
const int N=100010;
il int power(re int a,re int b){int res=1;for(;b;b>>=1,a*=a)if(b&1)res*=a;return res>=N?-1:res;}
int b[N],minv[N],pri[N],cnt,ans;
il void euler(re int n=N-9){
	for(re int i=2;i<=n;++i){
		if(!minv[i])minv[i]=i,pri[++cnt]=i;
		for(re int j=1;j<=cnt;++j){
			if(i*pri[j]>n)break;minv[i*pri[j]]=pri[j];if(i%pri[j]==0)break;
		}
	}
}
signed main(){
	euler(); int n,k; read(n),read(k);
	for(re int i=1,a,c=1,d=1;i<=n;++i,c=1,d=1){
		read(a);
		while(a!=1){
			int now=minv[a],tot=0;
			while(a%now==0)a/=now,++tot;
			tot=(tot+k)%k;
			if(tot>0)c*=power(now,tot),d*=power(now,k-tot);if(d<0)d=N;
		}
		if(d<N)ans+=b[d]; ++b[c];
	}
	return cout<<ans,0;
}
```

### 吐槽：

为什么T2绿比T1紫还难。。。

---

## 作者：杨铠远 (赞：0)

做人好难啊，我又来水题解了

题意：有多少组数一一配对乘起来后刚好是一个数的k次方

毫无头绪？
## 哈希！

将每个数分解因数（质因数也行）将这个因数的指数哈希下来

扔进表里，$nlog(n)$查一下统计答案就好了

```cpp
//Code by : Y-k-y
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
#include <set>
#include <map>
#define int unsigned long long
const int N=100010;
#define base 1331
using namespace std;
inline int rnd(){
	int res=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){res=res*10+ch-'0';ch=getchar();}
	return res*f;
}
inline void wr(int x){
	if(x<0){putchar('-');x=-x;}if(x>9) wr(x/10);putchar(x%10+'0');
}
int n,k,ans;
int aa[N],fac[N],bb[N];
signed main(){
	cin>>n>>k;
	for(int i=1,x;i<=n;i++){
		x=rnd();
		int sq=sqrt(x);
		int &a=aa[i],&b=bb[i];
		for(int j=2;j<=sq;j++){
			int num=0;
			if(x%j==0){
				while(x%j==0){
					num++;x/=j;
				}
			}
			num%=k;
			if(num){
				a=a*base+j;
				a=a*base+num;
				b=b*base+j;
				b=b*base+k-num;
			}
			if(x==1)break;
		}
		if(x!=1){
			a=a*base+x;
			a=a*base+1;
			b=b*base+x;
			b=b*base+k-1;
		}
		if(a==b)ans--;
	}
	sort(aa+1,aa+1+n);
	for(int i=1;i<=n;i++){
		ans+=upper_bound(aa+1,aa+1+n,bb[i])-lower_bound(aa+1,aa+1+n,bb[i]);
	}
	wr(ans/2);
	return 0;
}

```
拜拜

---

