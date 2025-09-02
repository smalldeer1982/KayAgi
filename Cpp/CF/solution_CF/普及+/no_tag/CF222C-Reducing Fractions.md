# Reducing Fractions

## 题目描述

To confuse the opponents, the Galactic Empire represents fractions in an unusual format. The fractions are represented as two sets of integers. The product of numbers from the first set gives the fraction numerator, the product of numbers from the second set gives the fraction denominator. However, it turned out that the programs that work with fractions in this representations aren't complete, they lack supporting the operation of reducing fractions. Implement this operation and the Empire won't forget you.

## 说明/提示

In the first test sample the numerator equals 1000, the denominator equals 500. If we reduce fraction 1000/500 by the greatest common divisor of the numerator and the denominator (by 500), we obtain fraction 2/1.

In the second test sample the numerator equals 2000, the denominator equals 300. If we reduce fraction 2000/300 by the greatest common divisor of the numerator and the denominator (by 100), we obtain fraction 20/3.

## 样例 #1

### 输入

```
3 2
100 5 2
50 10
```

### 输出

```
2 3
2 1
1 1 1
```

## 样例 #2

### 输入

```
4 3
2 5 10 20
100 1 3
```

### 输出

```
1 1
20
3
```

# 题解

## 作者：StayAlone (赞：2)

先分解质因数。直接分解时间复杂度比较危险，先筛出一些质数再分解，时间复杂度可降为每次 $\sqrt{\dfrac{a}{\ln a}}$。

用桶记录下每个质数的出现次数。设 $a$ 数组中的质数 $i$ 总共出现了 $cnt1_i$，$b$ 数组中的质数 $i$ 总共出现了 $cnt2_i$ 次，那么最终的分数会分子分母同时除以 $\prod_{i=1}^v \min\{cnt1_i, cnt2_i\}$，其中 $v$ 是值域。

那么在输出时，对于每个数，重新遍历它的质因数。如果某个质因数 $p$ 需要被除掉，那么就对这个数除以 $p$。

[AC record](https://www.luogu.com.cn/record/115654877)

```cpp
int n, m, a[MAXN], b[MAXN], cnt1[Q], cnt2[Q], del[Q], del2[Q];
int tot, pri[MAXN << 2]; bitset <Q> vis;
vector <int> num1[MAXN], num2[MAXN];

il void init() {
	rep1(i, 2, 1e7) {
		if (!vis[i]) pri[++tot] = i;
		for (int j = 1; j <= tot && 1ll * pri[j] * i <= 1e7; ++j) {
			vis[i * pri[j]] = 1;
			if (i % pri[j] == 0) break;
		}
	}
}

int main() {
	read(n, m); init(); rer(i, 1, n, a); rer(i, 1, m, b);
	rep1(i, 1, n) {
		int x = a[i];
		rep1(j, 1, tot) {
			int p = pri[j];
			if (p > sqrt(x)) break;
			while (x % p == 0) ++cnt1[p], x /= p, num1[i].eb(p);
		}
		if (x > 1) ++cnt1[x], num1[i].eb(x);
	}
	rep1(i, 1, m) {
		int x = b[i];
		rep1(j, 1, tot) {
			int p = pri[j];
			if (p > sqrt(x)) break;
			while (x % p == 0) ++cnt2[p], x /= p, num2[i].eb(p);
		}
		if (x > 1) ++cnt2[x], num2[i].eb(x);
	}
	rep1(i, 1, 1e7) del[i] = del2[i] = min(cnt1[i], cnt2[i]);
	printf("%d %d\n", n, m);
	rep1(i, 1, n) {
		for (auto v : num1[i]) if (del[v]) --del[v], a[i] /= v;
		printf("%d ", a[i]);
	} puts("");
	rep1(i, 1, m) {
		for (auto v : num2[i]) if (del2[v]) --del2[v], b[i] /= v;
		printf("%d ", b[i]);
	} puts("");
	rout;
}
```

---

## 作者：蒟酱 (赞：1)

虽然是朴素的筛法，但是跑的比希儿的 Pollard-rho 快。  
$\mathcal O(n\sqrt n)$ 的质因数分解是不行的，Pollard-rho 的码量也过于麻烦，直接在线性筛里筛出每个数的最小质因子，怎么筛？线性筛的本质是每个数只会被自己的最小质因子筛到，记录即可。  
对分母分子每个数筛出来的质因子放入桶里，对两个桶取 `min` 就是要除掉的部分。  
再对分母分子进行筛，如果筛出来的质因子在桶里有，把桶里的计数减去 `1`，否则就不去除这个数。  
代码（略有压行）：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cassert>
#define siz(x) int((x).size())
#define cauto const auto
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
using std::cin;using std::cout;
using loli=long long;
using uloli=unsigned long long;
using lodb=long double;
using venti=__int128_t;
using pii=std::pair<int,int>;
using inlsi=const std::initializer_list<int>&;
constexpr venti operator""_vt(uloli x){return venti(x);}
constexpr int N=1e7+1;
int n,m,mif[N];
std::basic_string<int>pt,ans1,ans2;
bool pr[N];
pii cnt[N];
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);cin.tie(nullptr);
	for(int i=2;i<N;i++){if(!pr[i])pt+=i,mif[i]=i;for(int j:pt){if(i*j>=N)break;pr[i*j]=true;mif[i*j]=j;if(i%j==0)break;}}
	cin>>n>>m;
	for(int i=1,x;i<=n;i++)for(int p=mif[cin>>x,ans1+=x,x];x!=1;p=mif[x/=p])cnt[p].fi++;
	for(int i=1,x;i<=m;i++)for(int p=mif[cin>>x,ans2+=x,x];x!=1;p=mif[x/=p])cnt[p].se++;
	for(int i=1,x;i<N;i++)if(cnt[i].fi<cnt[i].se)cnt[i].se=cnt[i].fi;else cnt[i].fi=cnt[i].se;
	cout<<n<<' '<<m<<'\n';
	for(int y;int x:ans1){for(int p=mif[y=1,x];x!=1;p=mif[x/=p])if(cnt[p].fi>0)cnt[p].fi--;else y*=p;cout<<y<<' ';}
	cout<<'\n';
	for(int y;int x:ans2){for(int p=mif[y=1,x];x!=1;p=mif[x/=p])if(cnt[p].se>0)cnt[p].se--;else y*=p;cout<<y<<' ';}
	return 0;
}
```

---

## 作者：loser_seele (赞：1)

首先考虑如何实现约分过程。

分别分解分子和分母，把每个质因子的数量相加后取较小的那个即可，在构造答案时时如果还有剩余的质因子没有约分则补上 $ 1 $，同时将质因子的数量 $ -1 $，否则乘上这个质因子即可。

但是题目数据范围是 $ n,m \leq 10^5 $，$ a_i \leq 10^7 $，朴素的质因数分解是 $ \mathcal{O}(n \sqrt{a_i}) $ 的，难以通过。

于是考虑使用更快的质因数分解方法：Pollard-rho 算法，在 $ \mathcal{O}(n \times a_i^{\frac{1}{4}}) $ 的时间复杂度内解决了本题。

同时也可以先预处理出每个数的最小质因子之后再分解，实际运行效率更快。

实现的时候要注意不能用 long long，可能会导致超时，分解时先预处理出所有质数，如果是质数则直接返回以加速，遇到已经分解过的数时最好开一个哈希表记录，尽量避免重复计算。~~本质上是一种乱搞。~~

下面的代码常数较大，最慢点跑了接近 2 秒，惊险通过。

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
    return a*b%mod;
}
ll pow(ll a, ll b, ll m) 
{
  ll ans = 1;
  for (a %= m; b; b >>= 1, a = mul(a, a, m))
    if (b & 1) 
        ans = mul(ans, a, m);
  return ans;
}
const int maxn=1e7+10;
signed prime[maxn];
bool vis[maxn];
int tot=0;
void pre(int n)
{
for(int i=2;i<n;i++)
{
    if(!vis[i])
        prime[tot++]=i;
    for(int j=0;j<tot;++j)
    {
    if(i*prime[j]>n)
        break;
    vis[i*prime[j]]=1;
    if(i%prime[j]==0)
        break;
    }
}
}
inline bool MR_check(ll a, ll p, ll s, int d) 
{
  ll k = pow(a, s, p);
  if (k == 1) 
      return true;
  for (; d; --d, k = mul(k, k, p)) 
  {
    if (k == p - 1) 
        return true;
    if (k == 1) 
        return false;
  }
  return k == 1;
}
inline bool MR(signed x) 
{
  static const signed cnt = 12;
  static const signed p[cnt] = { 2, 3, 5, 7, 11, 13, 17, 19, 61, 2333, 4567, 24251 };
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
signed PR_check(signed c, signed p) 
{
  signed y = rand() % p, z = y;
  signed k = 1, j = 0;
  while(1145141919810) 
  {
    z = (mul(z, z, p) + c) % p;
    int t = __gcd(p, std::abs(z - y));
    if (t > 1) 
        return t;
    if (++j == k) 
        y = z, k <<= 1;
  }
}
void factor_(signed x, std::vector<ll> &v) 
{
  if (x == 1) 
      return;
  if (!vis[x]) 
  { 
      v.push_back(x); 
      return; 
  }
  ll y = x;
  while (y == x) 
      y = PR_check(rand() % x, x);
  factor_(y, v);
  factor_(x / y, v);
}
void factor(signed x, std::vector<ll> &v) 
{
  v.clear();
  factor_(x, v);
  std::sort(v.begin(), v.end());
}
}
using Pollard_Rho::factor;
const int maxm=1e7+10;
signed cnt[2][maxm],a[100020],b[100020];
bool vis2[maxm];
unordered_map<signed,vector<signed> >p;
signed main()
{
    int T=1;
    pre(1e7);
    for(;T;--T)
    {
    	int n,m;
        r(n),r(m);
        for(int i=1;i<=n;i++)
        {
            r(a[i]);
            vector<int>d;
            if(vis2[a[i]])
                for(auto x:p[a[i]])
                d.push_back(x);
            else
            {
            vis2[a[i]]=1;
    	    Pollard_Rho::factor(a[i],d);
            for(auto x:d)
            p[a[i]].push_back(x);
            }
            for(auto x:d)
            cnt[0][x]++;
        }
        for(int i=1;i<=m;i++)
        {
            r(b[i]);
            vector<int>d;
            if(vis2[b[i]])
            for(auto x:p[b[i]])
            d.push_back(x);
            else
            {
            vis2[b[i]]=1;
    	    Pollard_Rho::factor(b[i],d);
            for(auto x:d)
                p[b[i]].push_back(x);
            }
            for(auto x:d)
                cnt[1][x]++;
        }
        for(int i=1;i<=1e7;i++)
            cnt[0][i]=min(cnt[1][i],cnt[0][i]),cnt[1][i]=cnt[0][i];
        cout<<n<<' '<<m<<'\n';
        for(int i=1;i<=n;i++)
        {
            vector<int>d;
        if(vis2[a[i]])
            for(auto x:p[a[i]])
                d.push_back(x);
        else
        {
        vis2[a[i]]=1;
    	Pollard_Rho::factor(a[i],d);
        for(auto x:d)
            p[a[i]].push_back(x);
        }
        int ans=1;
        for(auto x:d)
            if(cnt[0][x])
                cnt[0][x]--;
            else
            ans*=x;
        cout<<ans<<' ';
        }
        cout<<'\n';
        for(int i=1;i<=m;i++)
        {
            vector<int>d;
            if(vis2[b[i]])
                for(auto x:p[b[i]])
                d.push_back(x);
        else
        {
            vis2[b[i]]=1;
    	    Pollard_Rho::factor(b[i],d);
            for(auto x:d)
            p[b[i]].push_back(x);
        }
            int ans=1;
            for(auto x:d)
            if(cnt[1][x])
                cnt[1][x]--;
            else
                ans*=x;
            cout<<ans<<' ';
        }
    }
}
```


---

## 作者：Enthon_Yuan (赞：0)

总结：

不难但是毒瘤。（小声

~~差点 `duel` 失败然后翻车了。。~~

给一个不同于其他题解的~~小众~~做法。

### 题目大意：

给定两个序列 $a,b$，乘积分别作为分式的分子和分母。

要求约分分式至**最简**，然后**以乘积的形式**输出。

要求：输出数量小于等于 $10^5$ 且每个数小于等于 $10^7$。

## Solution：

### PART 1

很显然我们应该先使用线筛，筛出所有的质数。

不会线筛的右转 [OI-WIKI](https://oi-wiki.org/math/number-theory/sieve/#%E7%BA%BF%E6%80%A7%E7%AD%9B%E6%B3%95) 了解一下。

那么我们可以用线筛同时处理每个数能够分解它的一个质数。

为什么要这么做呢？

这样有利于直接分解一个值域内的数。

不妨简单证明一下时间复杂度：

每次我们提取出一个质因数，然后将 $x$ 除以这个质因数。

我们知道，质数都是 $x\ge2$ 的，所以每次除法至少令 $x$ 减少到一半。

所以时间复杂度是小于等于 $\log_2n$ 的。

证毕。

### PART 2

那么接下来的操作就很简单了。

我们直接暴力对每个数分解质因数，然后抵消若干相同的质因数。然后想办法输出就可以了。

欸？为什么说是想办法输出呢？

### PART 3

方法1：直接输出所有的质数。

结果1：你会得到 `Wrong answer on test 13`。

死因1：输出量太太太多了。

方法2：我直接用一个变量存一下啊，乘起来，要超过 $10^7$ 就输出不久行了？？

结果2：你会得到 `Wrong answer on test 42`。

死因2：这么直接乘法可能会浪费一些数的空间。导致你的输出量依然很大很大。。

~~不要问作者是怎么知道的。~~

那么我们应该怎么办呢？

我们可以在分解的时候记录一下这个数来自原来那里。

然后在乘法的时候乘到那个位置就好了。

为什么是对的？因为输入是合法的。并且约分后每个位置的数不可能变大。

然后就是代码了。


```cpp
const int N = 1e7+5;
const int M = 1e5+5;
const int K = 664580;
int n,m,is[N],pri[N],cnt;
int a[M],b[M];
vector<int> s1[K],s2[K];
// 用于二分查找一个质数的在 pri 数组中的位置
int fd(int x)
{
	int l = 1,r = cnt,mid,ans=0;
	while(l <= r)
	{
		mid = l+r>>1;
		if(pri[mid] < x) l=mid+1;
		else if(pri[mid] > x) r=mid-1;
		else return mid;
	}
	assert(0);
	return 0;
}
// 分解分子质因数，并记录来源的位置
void q1(int x,int y)
{
	while(is[x])
	{
		s1[is[x]].emplace_back(y);
		x /= pri[is[x]];
	}
	if(x > 1) s1[fd(x)].emplace_back(y);
	return ;
}
// 同上
void q2(int x,int y)
{
	while(is[x])
	{
		s2[is[x]].emplace_back(y);
		x /= pri[is[x]];
	}
	if(x > 1) s2[fd(x)].emplace_back(y);
}
int ans1[M],ans2[M];
int main()
{
	// 弱化版 线筛，但是够用
	fo(i,2,1e7)
	{
		if(!is[i]) pri[++cnt]=i;
		fo(j,1,cnt)
		{
			ll g = pri[j]*i;
			if(g > 1e7) break;
			is[g] = j;
		}
	}
	read(n,m);
	fo(i,1,n) read(a[i]),q1(a[i],i),ans1[i]=1;//记得此处要赋初值为 1
	fo(i,1,m) read(b[i]),q2(b[i],i),ans2[i]=1;
	fo(i,1,cnt)
	{
		int mm = min(s1[i].size(),s2[i].size()); // 约掉一些分子分母共同的质数因子
		fo(j,mm,(int)s1[i].size()-1) ans1[s1[i][j]]*=pri[i];
		fo(j,mm,(int)s2[i].size()-1) ans2[s2[i][j]]*=pri[i];
	}
	printf("%d %d\n",n,m);
	fo(i,1,n) printf("%lld ",ans1[i]);printf("\n");
	fo(i,1,m) printf("%lld ",ans2[i]);printf("\n");
	return 0;
}
```

---

## 作者：冰冻罗非鱼 (赞：0)

 ### 题目大意：
 >给出两个集合，第一个集合数的乘积是分子，第二个集合的数的乘积是分母，要求够造一个同样的集合，但是得到的分数是最简分数。
 
 ### 分析：
 寻找思路并不复杂，对两个集合的每个数进行质因数分解，然后统计整个集合的质因数分解情况，再将两个集合的质因数的次数大减小即可。构造时使两个集合中元素的个数不变，尽可能地构造成原先集合的数，如果不行就填一个 $1$。但质因数分解的过程中不能采用 $O(\sqrt n)$ 的复杂度，会超时，接下来介绍本题中进行质因数分解的方法。
 其实也不是很复杂，就是对于每个被分解的数，优先除以它最大的质因数即可。当然，需要提前处理一下每个数最大的质因数。
 ### AC代码：
 ```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int M = 1e7;
const int MAXN = 1e4;
int n,m;
map<int,int> cnt1,cnt2;
set<int> s;
int prime[M + 5],up[M + 5],down[M + 5],a[M + 5],bb[M + 5];


signed main(){
	//freopen("B.out","r",stdin);
	//prime.push_back(9999991);
    for(int i = 2; i <= M; i++){//预处理每个数的最大质因数 
        if(prime[i] == 0){
        	prime[i] = i;
        	for(int j = i + i; j <= M + 3; j+=i){
        		prime[j] = i;
			}
		}
    }
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        int j;
    	for(j = a[i]; j > 1; j /= prime[j]){//质因数分解 
   			s.insert(prime[j]);
    		up[prime[j]]++;//存储分子的质因数分解情况 
		}
    }
    for(int i = 1; i <= m; i++){
        cin >> bb[i];
        int j;
    	for(j = bb[i]; j > 1; j /= prime[j]){//质因数分解 
   			s.insert(prime[j]);
    		down[prime[j]]++;//存储分母的质因数分解情况 
		}
    }
    int b;
    int now = 1;
    cout << n << " " << m << "\n";
    for(int i = 1; i <= n; i++){
    	int j;
    	int tmp  =1;
    	for(j = a[i]; j > 1; j /= prime[j]){
    		if(down[prime[j]] > 0){
    			down[prime[j]]--;//如果当前该数的质因数能在分母里也含油1，那么就将它约去，否则将它乘到答案里面
			}
			else{
				tmp *= prime[j];
			}
		}
		cout << tmp << " ";
	}
	puts("");
	for(int i = 1; i <= m; i++){
    	int j;
    	int tmp = 1;
    	for(j = bb[i]; j > 1; j /= prime[j]){
    		if(up[prime[j]] > 0){
    			up[prime[j]]--;//同上
			}
			else{
				tmp *= prime[j];
			}
		}
		cout << tmp << " ";
	}
    return 0;
}
```

---

