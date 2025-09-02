# Molly's Chemicals

## 题目描述

Tohru从异世界带回来 n 种化学品，排列成一行。 每一种化学品有一个效果值, 第i个效果值为a _i_ 。

Tohru想要Kobayashi爱上她。 她把连续的区间上的化学品混合在一起做成总效果值为k的非负整数幂的媚药。总效果值为连续区间上的化学品效果值的总和。

帮帮她找到符合要求的区间的方案数。

## 样例 #1

### 输入

```
4 2
2 2 2 2
```

### 输出

```
8
```

## 样例 #2

### 输入

```
4 -3
3 -6 -3 12
```

### 输出

```
3
```

# 题解

## 作者：沉石鱼惊旋 (赞：10)

### 题目翻译

给定长度为 $n$ 的序列 $a$，求有多少组 $(l,r)$ 满足 $\sum\limits_{i=l}^ra_i=k^i$。

### 题目思路

首先考虑，枚举 $l$ 和 $r$，判断 $\sum\limits_{i=l}^r$ 是否为 $k$ 的倍数。但是显然这种做法复杂度为 $n^2$ 无法通过。

设 $s$ 为 $a$ 的前缀和数组，我们注意到，我们查找 $s_r-s_{l-1}=k^i$，其实等价于找 $s$ 中是否有 $s_r-k^i$ 这个元素，那么我们只需枚举一个端点以及一个 $k$ 的次幂。

显然在这个题中，除去 $k=\pm1$，上述的 $i$ 最多只需枚举至 $\log_2 (10^9\times 10^5)\approx 60$ 次。

因此，总的时间复杂度为 $\mathcal O(n\log V)$。其中 $V=10^9\times 10^5$。对于 C++ 选手，如果你用 map 来判断 $s_r-k^i$ 是否存在还需乘上一个 $\log_2 n$。

### 完整代码

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
int n;
ll st[100];
int top;
ll pw=1;
ll k,ans;
ll a[100020];
ll s[100020];
map<ll,int>mp;
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        s[i]=a[i]+s[i-1];
    }
    for(int i=0;i<=60;i++)
    {
        if(abs(pw)>1e14)break;
        st[++top]=pw;
        pw*=k;
    }
    mp[0]=1;
    for(int i=1;i<=n;i++)
    {
        if(k==1)ans+=mp[s[i]-1];
        else if(k==-1)ans+=mp[s[i]-1]+mp[s[i]+1];
        else 
        {
            for(int _=1;_<=top;_++)
            {
                ans+=mp[s[i]-st[_]];
            }
        }
        mp[s[i]]++;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：__Hacheylight__ (赞：4)

【题意】：

给你$n$个数和一个数$k$，让你求有多少个区间的和是$k$的整数次幂？

【分析】：

区间的和明显可以通过前缀和处理

那么现在的问题就是有多少区间$sum[r]-sum[l]=pow(k,i)$呢？

我们能够发现$i$最大也就是$log(10^{14})≈60$

那么我们可以先枚举$i$，然后转化成判定性问题有多少l和r满足$sum[r]-pow(k,i)=sum[l]$

显而易见这个东西可以通过一只$map$去查找

那么时间复杂度就变成了$O(60n)≈O(n)$

不错啊。

【代码】：
```cpp
#include <bits/stdc++.h>
using namespace std ;

#define rep(i, a, b) for (int (i) = (a); (i) <= (b); (i)++)
#define Rep(i, a, b) for (int (i) = (a) - 1; (i) < (b); (i)++)
#define REP(i, a, b) for (int (i) = (a); (i) >= (b); (i)--)
#define clr(a) memset(a, 0, sizeof(a))
#define Sort(a, len, cmp) sort(a + 1, a + len + 1, cmp)
#define ass(a, sum) memset(a, sum, sizeof(a))

#define ls ((rt) << 1)
#define rs ((rt) << 1 | 1)
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define endl '\n'
#define ENDL cout << endl
#define SZ(x) ((int)x.size())

typedef long long ll ;
typedef unsigned long long ull ;
typedef vector <int> vi ;
typedef pair <int, int> pii ;
typedef pair <ll, ll> pll ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
typedef map <ll, ll> mll ;

const int N = 100010 ;
const double eps = 1e-8 ;
const int iinf = INT_MAX ;
const ll linf = 1e14 ;
const double dinf = 1e30 ;
const int MOD = 1000000007 ;

inline int read(){
    int X = 0, w = 0 ;
	char ch = 0 ;
    while (!isdigit(ch)) { w |= ch == '-' ; ch = getchar() ; }
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar() ;
    return w ? - X : X ;
}

void write(int x){
     if (x < 0) putchar('-'), x = - x ;
     if (x > 9) write(x / 10) ;
     putchar(x % 10 + '0') ;
}

void print(int x) {
	cout << x << endl ;
	exit(0) ;
}

void PRINT(string x) {
	cout << x << endl ;
	exit(0) ;
}

void douout(double x){
	 printf("%lf\n", x + 0.0000000001) ;
}

int n ;
ll k, ans ;
ll sum[N] ;
set <ll> a ;
map <ll, ll> x ;

signed main(){
    scanf("%d%lld", &n, &k) ;
	sum[0] = 0 ;
	for (int i = 1; i <= n; i++) scanf("%lld", &sum[i]), sum[i] += sum[i - 1] ;
	a.insert(1) ;
	ll tmp = k ;
	for (int i = 1; i <= 60; i++) { // 枚举pow(k,i)
		if (tmp > linf) break ;
		a.insert(tmp) ;
		tmp *= k ;
	}
	ll ans = 0 ;
	x[0] = 1 ;
	for (int i = 1; i <= n; i++) {
		for (set <ll>::iterator it = a.begin(); it != a.end(); it++) ans += x[sum[i] - *it] ;
		x[sum[i]]++ ;
	}
	printf("%lld\n", ans) ;
}
```




---

## 作者：wanyiheng (赞：1)

## 思路:

枚举 $k$ 的幂，在枚举过程中运用 map 来维护出现过和的次数再减，再用一个 map 来记录那些幂已经被遍历了，用于 $1$ 和 $-1$ 这种任意次方可能与之前相同的情况。出现过的和可用前缀和来优化。

## code:

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N=1e5+10;

int n,k,m=1,ans,sum;
int a[N],h[N];

map<int,int>ma;
map<int,bool>st;

signed main() {
	scanf("%lld%lld", &n, &k);

	for(int i=1;i<=n;i++){
		scanf("%lld", &a[i]);
		sum+=abs(a[i]);
		h[i]=h[i-1]+a[i];
	}

	while(sum>=abs(m)){
		if(st[m])break;
		st[m]=true;
		ma.clear();
		for(int i=0;i<=n;i++){
			ans+=ma[h[i]-m];
			ma[h[i]]++;
		}
		m*=k;
	}
	
	printf("%lld\n", ans);

	return 0;
}
```

---

## 作者：happybob (赞：1)

容易发现整个序列和的绝对值 $\leq 10^{14}$，令其为 $V$。

那么当 $k \neq \pm 1$ 时，$k$ 的非负整数幂只有 $O(\log_k V) = O(\log V)$ 个不同的小于 $V$ 的结果。

于是大力枚举 $k$ 的所有非负整数幂，暴力即可。题目转化为每次给 $x$，求区间和为 $x$ 的数的个数，用前缀和加 `map` 即可。复杂度两只 $\log$。

```cpp
#pragma GCC optimize("-Ofast,fast-math,-inline")
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <map>
using namespace std;

const int N = 1e5 + 5;

int n;
long long a[N], sum[N], k, ans = 0;
map<long long, int> mp;

int main()
{
	scanf("%d%lld", &n, &k);
	long long rk = k;
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]), sum[i] = sum[i - 1] + a[i];
	for (int i = 1; i <= n; i++)
	{
		ans += mp[sum[i] - 1];
		if (sum[i] == 1) ans++;
		mp[sum[i]]++;
	}
	while (true)
	{
		if (k == 1) break;
		if (k > (long long)1e14 || k < (long long)-1e14)
		{
			break;
		}
		mp.clear();
		for (int i = 1; i <= n; i++)
		{
			ans += mp[sum[i] - k];
			if (sum[i] == k) ans++;
			mp[sum[i]]++;
		}
		k *= rk;
	}
	printf("%lld\n", ans);
	return 0;
} // 1
```


---

## 作者：songzhixin (赞：0)

### 解题思路

[原题](https://www.luogu.com.cn/problem/CF776C)

我们可以将任何一个区间表示成两个前缀和之差，设前缀和为 $s$ 数组，则可以表示为 $s_i - s_j$，判断它有多少个就看 $s_i$ 到这个区间后有多少个 $s_j$ 即可。
 
枚举 $k$ 的几次方，可以用一个 `map` 记录 $s_j$，再枚举 $s_i$ 即可。

注意可能为附负数，需要加上一个偏移量，因为是次方，所以时间复杂度为约为 $O(\log n)$，不会超时。

### 正确代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=1e5+5;
long long a[N],s[N];
bool v[N];
map<long long,long long> x;
int main(){
	long long sum=0;
	long long n,k;
	scanf("%lld%lld",&n,&k);
	for(long long i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		s[i]=s[i-1]+a[i];
		sum+=abs(a[i]);
	}
	long long y=1,ans=0;
	while(abs(y)<=sum){
		if(abs(y)<100){
			if(v[y+100]==true){
				printf("%lld\n",ans);
				return 0;
			}
			v[y+100]=true;
		}
		x.clear();
		for(long long i=0;i<=n;i++){
			ans+=x[s[i]-y];
			x[s[i]]++;
		}
		y*=k;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：ny_jerry2 (赞：0)

###    思路
   这道题涉及到区间，需要用两个端点来寻找，实际上转换一下式子就能让我们求解时只需要 _一个端点_。
  
   约定 $sum$为前缀和 。
   
  根据题意，它实际上可以转换为一个式子:  
  $$
  sum_r-sum_{l-1}=pow(k,i)
  $$
  其中：$pow(k,i)$ 即 $k^i$。
    
  让我们求解满足这个式子的方案数是多少。 
    
   转换一下就能发现,这是让我们求在 $sum$ 中是否可以找到  _$sum_r-pow(k,i)$_  这个元素。  
    
   考虑到是求满足区间和为 $pow(k,i)$ 的方案数，那么我们只需要暴力枚举 $k$ 次幂，并让答案加上该情况下的方案数即可 。
   
  推算可得最多枚举几十次，属于常数级别。
    
   值得注意的是，当 $k$ 为  $+1$ 或 $-1$ 时，程序可能陷入死循环，所以我们要特判一下。
    
###     代码
   ```cpp
  #include<iostream>
  #include<map>
  #include<algorithm>
  #define int long long
  using namespace std;
  int n,m;
  const int N=100010;
  int a[N];
  map<int,bool> v;
  map<int,int> f;
  int sum;
  int h[N];
  signed main(){
      cin>>n>>m;
      for(int i=1;i<=n;i++){
          scanf("%lld",&a[i]);
          sum+=abs(a[i]);
          h[i]=h[i-1]+a[i];
      }
      int k=1,ans=0;
      while(sum>=abs(k)){
          if(v[k]){
              break;
          }
          v[k]=1;
          f.clear();
          for(int i=0;i<=n;i++){
              ans=ans+f[h[i]-k];
              f[h[i]]++;
          }
          k*=m; 
      }
      cout<<ans;
  }
   ```
   难度：还是有一定的思维难度，~~但不至于蓝题吧~~。

---

## 作者：Addicted_Game (赞：0)

## [CF776C Molly's Chemicals](https://www.luogu.com.cn/problem/CF776C)

### 题目大意
给定一个数组 $a$ 与数字 $k$，求有多少种方法可以使 $\sum ^r_{i=l}a_i=k^p(p \ge 0)$ 成立。

### 想法
首先肯定想到的是暴力 $O(n^2)$，但是对不起，$n \le 10^5$，不可取。

然后我想到的是一种 $O (n \log n)$ 的解法：一个区间 $(l,r)$ 的和 $\sum_{i=l}^r a_i$ 是等于 $(\sum_{i=r}^na_i)-(\sum_{i=1}^{l-1}a_i)$ 的，所以说我们可以枚举 $\sum_{i=r}^na_i$，再用二分找出有多少个$(m_{i=r}^na_i)-(\sum_{i=l}^r a_i)$ 也 $\sum_{i=1}^{l-1}a_i$，但是细节太多了，没有写出来。

### 正解思路
其实就是我的第二种思路的优化。

需要找出的 $\sum_{i=1}^{l-1}a_i$ 可以直接存在 map 之中，需要时直接调用就可以了。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,ans;
long long a[100005];
long long cf[55],len,ts;
long long sum[100005];
map<long long,long long> m;
int main(){
	scanf("%lld%lld",&n,&k);
	for(long long i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		sum[i]=sum[i-1]+a[i];
		ts+=abs(a[i]);	
	}
	cf[0]=1;
	while(abs(cf[len])<=ts){//预处理k的次方 
		if(k==1) break;
		if(k==-1){
			cf[++len]=-1;
			break;
		}//1和-1会循环，需要特殊处理 
		len++;
		cf[len]=cf[len-1]*k;
	}
	long long te=0;
	for(int i=i;i<=n;i++){
		for(int j=0;j<=len;j++){
			ans+=m[sum[i]-cf[j]];
		}
		m[sum[i]]++;//计算后再标记，避免重复计算 
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：appear_hope (赞：0)

概括题意，对 $a_i$ 做一次前缀和，即 $s_i = s_{i - 1} + a_i$。求 $s_r - s_{l - 1} = k^x$ 的数量。 求这个问题可以先把这个式子移个项得 $s_r = s_{l - 1} + k^x$, 由于 $k^x \le 10^{14}$，即最大所有数字之和。直接枚举并不超时(如果 $|k| \ne 1$)，其中 $x \le 63$, 因为 $k^x \le$ `LLONG_MAX`。如果 $|k| = 1$, $1$ 的非负整数次幂只有 $1$, 而 $-1$ 的非负整数次幂为 $-1$ 或 $1$, 然后题目只需再开个前缀桶记录 $s_i$ 的数量，再根据前缀桶累计答案即可，注意开 `long long`。

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 1e5 + 5, INF = 1e14;

map<int, int> mp;
int n, k, sum, ans;

int power(int x, int p){
  if(!p){
    return 1;
  }
  int v = power(x, p / 2);
  return (p % 2 == 0 ? v * v : v * v * x);
}

int main(){
  cin >> n >> k;
  mp[0] = 1;
  for(int i = 1, x; i <= n; i--){
    cin >> x;
    sum += x;
    if(abs(k) == 1){ //特殊情况
      ans += mp[sum - 1];
      if(k == -1){
        ans += mp[sum + 1]; 
      }
    }
    else{
      for(int j = 0; power(k, j) <= INF; j++){
        ans += mp[sum - power(k, j)];
      }
    }
    mp[sum]++;
  }
  cout << ans;
  return 0;
}
//切勿抄袭
```

---

## 作者：zajasi (赞：0)

## 题意
给你长度为 $n$ 的序列，问有多少个子序列满足和为 $m$ 的次幂？
## 解题思路
如果我们固定某一个和，这道题就好做了。也就是运用 map 来维护出现过和的次数再减就行了。

此时没有固定值，我们就枚举！只需要枚举 $m$ 的次幂就可以了。观察到最大的区间和为 $10^9 \times 10^5 = 10^{14}$，但是 $10^{18}$ 也不过就是 $2$ 的六十几次幂。所以次数小到几乎可以不考虑。

此题解终了......哎，错了！

发现没有考虑 $1$ 和 $-1$ 的情况。这两种可以特判一下。
## AC 代码
```cpp
/*
written by : zjs123
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long  
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
int n,m;
int a[100010];
int z;
int x,c,ans;
int d[100010];
main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        z=max(z,a[i]);
    }
    x=1;
    while((x<=1e15&&abs(m)!=1)||(m==-1&&c<2)||(m==1&&c<1)){
        c++;
        map<int,int> mm;//统计出现次数
        int zz=0;
        mm[0]=1;
//        cout<<x<<" ";
        for(int i=1;i<=n;i++){
            d[i]=d[i-1]+a[i];//前缀和
            zz+=mm[d[i]-x];//增加答案
//            cout<<mm[d[i]-x]<<" "<<d[i]<<"\n";
            mm[d[i]]++;
        }
//        cout<<zz<<"\n";
        ans+=zz;
        x*=m;//计算目前的总和
    }
    cout<<ans;
    return 0;
}

```

---

## 作者：__AFO__ (赞：0)

## 题解

[出处](https://www.luogu.com.cn/problem/CF776C)

大致是将两个前缀和的差转换成 k 的 i 次方，用 map 来寻找，其实思路很简单。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[100005],s[100005],v[100005],sum=0;
long long n,k,y=1,ans=0;
map<long long,long long> x;
int main() {	
	scanf("%lld%lld",&n,&k);
	for(long long i=1; i<=n; i++) {
		scanf("%lld",&a[i]);
		s[i]=s[i-1]+a[i];
		sum+=abs(a[i]);
	}
	
	while(abs(y)<=sum) {
		if(abs(y)<100) {
			if(v[y+100]==1) {
				printf("%lld\n",ans);
				return 0;
			}
			v[y+100]=1;
		}
		x.clear();
		for(long long i=0; i<=n; i++) {
			ans+=x[s[i]-y];
			x[s[i]]++;
		}
		y*=k;
	}
	printf("%lld\n",ans);
	return 0;
}
```

### END

---

