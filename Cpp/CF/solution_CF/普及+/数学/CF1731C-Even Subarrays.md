# Even Subarrays

## 题目描述

You are given an integer array $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ).

Find the number of subarrays of $ a $ whose $ \operatorname{XOR} $ has an even number of divisors. In other words, find all pairs of indices $ (i, j) $ ( $ i \le j $ ) such that $ a_i \oplus a_{i + 1} \oplus \dots \oplus a_j $ has an even number of divisors.

For example, numbers $ 2 $ , $ 3 $ , $ 5 $ or $ 6 $ have an even number of divisors, while $ 1 $ and $ 4 $ — odd. Consider that $ 0 $ has an odd number of divisors in this task.

Here $ \operatorname{XOR} $ (or $ \oplus $ ) denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Print the number of subarrays but multiplied by 2022... Okay, let's stop. Just print the actual answer.

## 说明/提示

In the first test case, there are $ 4 $ subarrays whose $ \operatorname{XOR} $ has an even number of divisors: $ [3] $ , $ [3,1] $ , $ [1,2] $ , $ [2] $ .

In the second test case, there are $ 11 $ subarrays whose $ \operatorname{XOR} $ has an even number of divisors: $ [4,2] $ , $ [4,2,1] $ , $ [4,2,1,5] $ , $ [2] $ , $ [2,1] $ , $ [2,1,5] $ , $ [2,1,5,3] $ , $ [1,5,3] $ , $ [5] $ , $ [5,3] $ , $ [3] $ .

In the third test case, there is no subarray whose $ \operatorname{XOR} $ has an even number of divisors since $ \operatorname{XOR} $ of any subarray is either $ 4 $ or $ 0 $ .

## 样例 #1

### 输入

```
4
3
3 1 2
5
4 2 1 5 3
4
4 4 4 4
7
5 7 3 7 1 7 3```

### 输出

```
4
11
0
20```

# 题解

## 作者：Jasper08 (赞：6)

简要题意：

给定一个长度为 $n$ 的数组 $a$，求出满足以下条件的区间 $[i,j]$ 的数量：$a_i\oplus a_{i+1}\oplus \cdots\oplus a_{j}$ 不是完全平方数。共有 $T$ 组数据。$1\le T\le 10^3,\sum n\le 2\cdot 10^5,1\le a_i\le n$。

---

我们可以先求出 $a$ 的异或前缀和 $s$，即 $s_i=a_1\oplus a_2\oplus \cdots\oplus a_i$，特别地，$s_0=0$。那么 $a_i\oplus a_{i+1}\oplus \cdots\oplus a_{j}=s_j\oplus s_{i-1}$。 

发现 $a_i$ 的范围很小，考虑用一个桶 $nums$ 来存储已经出现过的 $s_i$ 的数量。我们可以遍历 $a_1\sim a_n$，用 $cnt$ 表示 $i$ 为区间右端点时对答案的贡献，枚举 $j=1,2,\cdots,650$（因为 $650^2\approx4\cdot10^5$），并判断 $j^2\oplus a_i$ 是否在桶中出现过，如果出现过则 $cnt\leftarrow cnt-nums_{j^2\oplus a_i}$。

时间复杂度 $O(Tn)$。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

typedef long long ll;

const int N = 2e5+10, M = 1e6+10;

int t, n, k;
int a[N], s[N]; 
ll ans;
int nums[M];

int main() {
    scanf("%d", &t);
    while (t -- ) {
        memset(nums, 0, sizeof nums); ans = 0;

        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            s[i] = s[i-1] ^ a[i];
        }

        nums[0] ++;
        for (int i = 1; i <= n; ++i) {
            int cnt = i;
            for (int j = 0; j <= 650; ++j) {
                int t = j * j ^ s[i];
                if (nums[t])
                    cnt -= nums[t];
            }
            nums[s[i]] ++;
            ans += cnt;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：Engulf (赞：4)

本题可以使用容斥原理及补集的思想，一共有 $\dfrac{n(n+1)}{2}$ 个子序列，减去子序列异或和为奇数的即为答案。

1. 完全平方数有奇数个因子。[证明](https://www.luogu.com.cn/paste/6xlfeqgc)

2. $a \oplus b = c \Leftrightarrow a \oplus c = b$。[证明](https://www.luogu.com.cn/paste/g0slmh1b)

我们可以处理一个异或前缀和，再统计每个前缀的值的出现次数。

然后枚举右端点，再枚举 $\le 2n$ 的完全平方数，由（2）可以得到左端点，累加左端点的出现次数。

时间复杂度 $\mathcal{O}(n \sqrt n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int inf = 0x3f3f3f3f;
const LL infLL = 0x3f3f3f3f3f3f3f3fLL;

int main()
{
	int tt;
	scanf("%d", &tt);
	while (tt -- )
	{
		int n;
		scanf("%d", &n);
		vector<int> cnt(2 * n + 5);
		cnt[0] ++ ;
		LL res = (LL)n * (n + 1) / 2;
		int pre = 0;
		for (int i = 1, x; i <= n; i ++ )
		{
			scanf("%d", &x);
			pre ^= x;
			for (int j = 0; (pre ^ j * j) <= 2 * n; j ++ )
				res -= cnt[pre ^ j * j];
			cnt[pre] ++ ;
		}
		printf("%lld\n", res);
	}
	return 0;
}
```

---

## 作者：loser_seele (赞：1)

首先不难发现完全平方数一定有奇数个因子。题目中假设 $ 0 $ 有奇数个因子，满足条件。

证明：如果一个数有奇数个因子则质因数分解后一定满足 $ \prod_{i=1}^n{(a_i+1)} $ 的形式，其中 $ a_i $ 表示质因子的指数，则显然这些指数必须全部是偶数，则这个数是完全平方数。

完全平方数的个数是根号级别的，考虑补集转化，用全部区间数减去异或和为完全平方数的区间个数，则对于每个完全平方数，统计区间异或和为这个数的个数。

这就是经典的题了，不难有区间 $ [l,r] $ 的异或和为 $ sum_r \oplus sum_{l-1} $，于是直接插入 $ sum $ 数组后统计 $ sum_r \oplus sum_{l-1}=x $ 的个数即可，也就是统计满足等于 $ sum_{r} \oplus x $ 的数的个数。

总时间复杂度 $ \mathcal{O}(n\sqrt{n}) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
#define int long long
int p[4000040];
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int sum[20000020];
signed main() 
{
	int T;
	cin>>T;
	while(T--) 
    {
		int n,ans=0;
		cin>>n;
		for(int i=0;i<=2*n;i++)
		p[i]=0;
		for (int i=1;i<=n;i++) 
        {
			int x=read();
			sum[i]=sum[i-1]^x;
		}
		for(int i=0;i<=n;i++)
			p[sum[i]]++;
        for(int j=0;j*j<=2*n;j++)
        {
		for (int i=0;i<=n;i++)
		{
			p[sum[i]]--;
		ans+=p[sum[i]^(j*j)];
		}
		for(int i=0;i<=n;i++)
			p[sum[i]]++;
        }
		cout<<n*(n+1)/2-ans<<'\n';
	}
}
```


---

## 作者：yinhee (赞：0)

[题目传送门](https://codeforces.com/contest/1731/problem/C)

首先一个性质：有奇数个因数的数一定是完全平方数。为什么？

因为一个自然数的因数个数即为它所有质因数的最高次幂数 $+1$ 的积。既然要求这个值是奇数，那么每一个质因数的最高次幂数一定是偶数，所以这个数就一定是完全平方数了。

既然题目问子段异或和为偶数的数量，那么我们也可以用总数减去为奇数的数量。而我们又可以发现 $\leq n$ 的完全平方数只有 $\sqrt n$ 个，所以可以枚举最后子段的异或和，然后转换成求子段异或和为 $k$ 的子段数量的经典问题，对前缀异或和进行哈希即可。总时间复杂度 $O(n\sqrt n)$。

这题还有两个易错点：

1、事实上，一些 $\ge n$ 的完全平方数也可能对答案有贡献。具体地说，可以枚举到 $n\times 2$。

2、在解决上面的问题后，会发现此时计算时要用到的 $sum\oplus k$ 值会超出 $n\times 2$，所以要将空间开到 $4$ 倍或是特判一下开 $2$ 倍。

code：

```cpp
int n,m,e[N],box[N<<2];
void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)read(e[i]);
	ll ans=0;
	for(int k=0;k*k<=n<<1;k++){
		for(int i=1;i<=n<<1;i++)box[i]=0;
		box[0]=1;
		for(int i=1,sum=0;i<=n;i++){
			sum^=e[i];
			ans+=(ll)box[sum^(k*k)];
			box[sum]++;
		}
	}
	printf("%lld\n",(ll)n*(n+1)/2-ans);
}
signed main(){
	int t=1;
	scanf("%d",&t);
	while(t--)solve();
}
```

---

## 作者：Withers (赞：0)

显然可以发现所有有奇数个约数的数都为平方数
因为我们要求一段的异或和，而异或和的逆运算为自己，所以我们可以做一个前缀和，所以 $a[i] \oplus a[i+1] \oplus \cdots a[j] = xr[j] \oplus xr[i-1]$，此处 $xr[i]$ 为原数组的异或前缀和

因为我们要求所有的异或和不为平方数子数列，我们只需要求是平方数的即可。

对于每个结尾为 $a[x]$ 的子数列，我们只需要枚举所有可能的平方数，求出可能的开头个数即可

因为 $1 \le a[i] \le n(1\le i \le n)$,所以复杂度 $\mathcal{O}(n \sqrt{n})$

code:
```cpp
#pragma comment(linker,"/stack:200000000")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include<bits/stdc++.h>
#define Withers using
#define AK namespace
#define IOI std
#define int long long
Withers AK IOI;typedef long long ll;typedef pair<int,int>pii;int n,m,u,v,w,x,y,z,l,r,minn=INT_MAX,maxx=INT_MIN,k;int tst;int a[200010];char s[200010];mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());char t[200010];
#define infll 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
#define endl '\n'
static char buf[1<<18],*paa=buf,*pddd=buf;static char buf2[1<<18],*pppp=buf2;
#define getchar()paa==pddd&&(pddd=(paa=buf)+fread(buf,1,1<<18,stdin),paa==pddd)?EOF:*paa++
inline void pc(char ch){if(pppp-buf2==1<<18)fwrite(buf2,1,1<<18,stdout),pppp=buf2;*pppp++=ch;}inline void pcc(){fwrite(buf2,1,pppp-buf2,stdout);pppp=buf2;}inline void rd(int&n){int w=1;register int x(0);register char c(getchar());while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();n=w*x;return;}inline void write(int x){if(x<0)pc('-'),x=-x;static int sta[20];int top=0;do{sta[top++]=x%10,x/=10;}while(x);while(top)pc(sta[--top]+48);}inline void we(int x){write(x);pc('\n');}inline void ws(int x){write(x);pc(' ');}
#define YES cout<<"YES"<<endl
#define NO cout<<"NO"<<endl
#define deb(x)cout<<#x<<"="<<x<<" ";
#define pb push_back
#define fi first
#define se second
#define mx3(a,b,c)((a>b?a:b)>c?(a>b?a:b):c)
#define mn3(a,b,c)((a<b?a:b)<c?(a<b?a:b):c)
#define mem(a,b)memset(a,b,sizeof(a))
#define rep(i,a,b)for(int i=a;i<=b;i++)
int xr[200010];
int p[5000010]={};
int sq[2000];
void rd(int n,int a[]){for(int i=1;i<=n;i++)rd(a[i]);}void rda(){rd(n);for(int i=1;i<=n;i++)rd(a[i]);}void adde(vector<pii>g[],int x,int y,int z){g[x].push_back({y,z});g[y].push_back({x,z});}
int get(char s[]){char ch=' ';int cnt=0;int len=strlen(s+1);for(int i=1;i<=len;i++)s[i]=0;while(ch==' '||ch=='\n'||ch=='\r'||ch==EOF)ch=getchar();while(!(ch==' '||ch=='\n'||ch=='\r'||ch==EOF))s[++cnt]=ch,ch=getchar();return cnt;}void put(char s[]){int len=strlen(s+1);for(int i=1;i<=len;i++)pc(s[i]);}void get(string&s){s="";char ch=' ';while(ch==' '||ch=='\n'||ch=='\r'||ch==EOF)ch=getchar();while(!(ch==' '||ch=='\n'||ch=='\r'||ch==EOF))s.push_back(ch),ch=getchar();return;}void put(string s){int len=s.size();for(int i=0;i<len;i++)pc(s[i]);}void file(string s){freopen((s+".in").c_str(),"r",stdin);freopen((s+".out").c_str(),"w",stdout);}
void solve()
{
	//do somethin
	//mp.clear();
	//p[0]=0;
	int mx=-1;
	rd(n);
	rep(i,1,n) xr[i]=0;
	rep(i,1,n) rd(a[i]);
	rep(i,1,n) xr[i]=xr[i-1]^a[i],mx=max(mx,xr[i]);
	int cnt=0;
	int lmx=sqrtl(5*n);
	rep(i,1,n)
	{
		for(int j=0;j<=lmx;++j)
		{
			//cerr<<j*j<<" "<<sq[j]<<" "<<(sq[j]^xr[i])<<" "<<p[(sq[j]^xr[i])]<<endl;
			if(sq[j]==xr[i]) {++cnt;}
			if(p[sq[j]^xr[i]]) cnt+=p[sq[j]^xr[i]];
		}
		p[xr[i]]++;
		//cout<<cnt<<endl;
	}
	rep(i,1,n) p[xr[i]]--;
	we(n*(n+1)/2-cnt);
}
void multi()
{
	rep(i,0,1999) sq[i]=i*i;
	rd(tst);
	//tst=1;
	while(tst--)
	{
		solve();
	}
	pcc();
}
signed main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	multi();
}
```


---

## 作者：tZEROちゃん (赞：0)

注意到大部分数的因子数都是偶数，因为因数是成对出现的，如果 $x$ 是 $n$ 的一个因子，那么 $\dfrac{n}{x}$ 必定也是一个因子。

那什么情况下会是奇数呢？显然只有当这个数是完全平方数的情况。比如 $16$，$4$ 是一个因子，而 $16\div 4=4$，两个是一样的。此时因子数就是奇数。

总共的子数组的数量是 $\dfrac{n(n+1)}2$，我们可以求出因子数的奇数的数量，然后再用 $\dfrac{n(n+1)}2$ 减去它。

注意到完全平方数的个数是非常少的，我们考虑枚举完全平方数。

记 $s_i$ 表示前 $i$ 个数的前缀异或和，如果 $s_r \oplus s_{l-1} = x$，其中 $x$ 是一个完全平方数，那么 $s_r \oplus x = s_l$，然后用一个计数数组记录之前的 $s_i$，每次统计即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int q;

long long n, m;

vector<int> perfectSquare;

void init() {
   for (int i = 0; i * i <= 5e5; ++i) {
      perfectSquare.push_back(i * i);
   }   
}

const int N = 4e5 + 10, M = 1e6 + 10;
int sum[M], a[N], s[N];

void solve() {
   cin >> n;
   for (int i = 1; i <= n; ++i) {
      cin >> a[i];
   }
   for (int i = 1; i <= n; ++i) {
      s[i] = s[i - 1] ^ a[i];
   }
   long long ans = 0;
   sum[0] = 1;
   for (int i = 1; i <= n; ++i) {
      for (int x : perfectSquare) {
         ans += sum[s[i] ^ x];
      }
      sum[s[i]]++; 
   }
   for (int i = 1; i <= n; ++i) {
      sum[s[i]] = 0;
   }
   ans = n * (n + 1) / 2 - ans;
   printf("%lld\n", ans); 
}

int main() {
   init();
   cin >> q;
   while (q--) {
      solve();
   }
}
```

---

## 作者：Gaode_Sean (赞：0)

看到这题，首先想到的是正难则反，即统计异或和因子个数是奇数（完全平方数）的序列数量。

考虑从前往后扫描这个数组，设 $s_i$ 表示 $a_1$ 到 $a_i$ 的异或和，$c_i$ 表示当前前缀异或和为 $i$ 的数量。并且对于每一个 $a_i$，枚举所有的平方数（假设是 $x^2$），把答案加上 $c_{s_{i \oplus x^2}}$。

最后输出 $\frac{n(n-1)}{2}$ 减去答案即可。

时间复杂度 $\mathcal{O}(Tn\sqrt n)$，空间复杂度 $\mathcal{O}(n)$。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=4e5+5;
ll T,a[N],b[N],cnt[N],tot,s;
ll n,ans;
void solve()
{
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(ll i=0;i<=2*n;i++) cnt[i]=0;
    cnt[0]=1;
    s=0; ans=(n+1)*n/2ll;
    for(ll i=1;i<=n;i++)
    {
        s^=a[i];
        for(ll j=0;j<=tot;j++) if((s^b[j])<=2*n) ans-=ll(cnt[s^b[j]]);
		cnt[s]++;
	}
	printf("%lld\n",ans);
}
int main()
{
	scanf("%lld",&T);
	for(ll i=1;i<=sqrt(N-1);i++) b[i]=i*i; 
	tot=(ll)sqrt(N-1);
	while(T--) solve();
	return 0;
}
```

---

