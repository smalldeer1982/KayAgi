# [ABC293F] Zero or One

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc293/tasks/abc293_f

$ 2 $ 以上の整数 $ N $ が与えられます。下記の条件を満たす $ 2 $ 以上の整数 $ b $ の個数を出力してください。

- $ N $ を $ b $ 進法で表記したとき、すべての桁について「その桁が $ 0 $ または $ 1 $ である」が成り立つ。
 
$ T $ 個の独立なテストケースについて答えを求めてください。

なお、本問題の制約下において、上記の「条件を満たす $ 2 $ 以上の整数 $ b $ の個数」は有限であることが証明できます。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 1000 $
- $ 2\ \leq\ N\ \leq\ 10^{18} $
- 入力はすべて整数
 
### Sample Explanation 1

$ 1 $ 番目のテストケースについて、問題文中の条件を満たす $ b $ は、$ b\ =\ 2,\ 3,\ 11,\ 12 $ の $ 4 $ つです。 実際、$ N\ =\ 12 $ を $ 2,\ 3,\ 11,\ 12 $ 進法で表すと、それぞれ $ 1100,\ 110,\ 11,\ 10 $ となります。

## 样例 #1

### 输入

```
3
12
2
36```

### 输出

```
4
1
5```

# 题解

## 作者：falling_cloud (赞：5)

对于找出满足要求的进制 $b$，可以很快想到两种求法：

1. 枚举 $b$ 并将 $n$ 暴力分解为 $b$ 进制。
2. 枚举 $b$ 进制下的数，在每一位上填上 $0$ 或 $1$，再用二分法求出 $b$。

第一种做法在 $b$ 较小时可以被接受，同时第二种做法在 $\log_bn$ 较小时可以被接受。所以考虑把两种做法缝在一起，将 $b$ 枚举至 $n^{\frac{1}{4}}$，然后将其换算为 $b$ 进制并检查合法性，剩余合法的 $b$ 在 $n$ 换算完进制后，一定小于等于四位，那么直接枚举并二分求解。

代码中使用了 map 判断求出的解是否重复。需要注意的一个细节是乘法溢出的问题，所以当最高位为 $1$ 时，二分上界应该为 $10^6$。最高位为 $0$ 且次高位为 $1$ 时，二分上界应为 $10^9$。

[代码](https://atcoder.jp/contests/abc293/submissions/39627388)

---

## 作者：FReQuenter (赞：2)

考虑分成两部分实现。

第一部分，$b$ 较小，直接枚举 $b$ 即可。

第二部分，$b$ 较大，这时可以直接枚举目标进制的 $01$ 串，二分进制使得这个串最接近 $n$。如果这个串刚好是 $n$ 在 $b$ 进制下的表示，则答案加一。注意两种情况的重复部分。

复杂度证明：以分界点为 $1000$ 为例，第一部分复杂度 $O(\sum_{b=2}^{\min(n,1000)}\log_b n)$，第二部分串的长度取到 $6$ 就足够（$\log_{1000}10^{18}$），复杂度 $O((2^{6})^{2}\log_2{n})$，可以通过。

注意二分时边界以及计算过程中爆 long long 的可能。

```cpp
#include<bits/stdc++.h>
#define int __int128
using namespace std;
int read(){
	int n=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') n=n*10+ch-48,ch=getchar();
	return n;
}
int check(int mid,int B){
	int ans=0,base=1; 
	for(int i=0;i<=5;i++){
		if((1<<i)&B){
			ans+=base;
			if(ans>1e18) return 2e18;
		} 
		if(base>1e18/mid) base=2e18;
		else base*=mid;
	}
	return ans;
}
signed main(){
	int t=read();
	while(t--){
		int ans=0,n=read();
		for(int i=2;i<=min(n,(__int128)1000);i++){
			int tmp=n,f=1;
			while(tmp){
				if(tmp%i>1){
					f=0;
					break;
				}
				tmp/=i;
			}
			ans+=f;
		} 
		if(n<=1000) cout<<(signed)ans<<'\n';
		else{
			for(int i=(1<<6)-1;i;i--){
				int l=0,r=1e18,as=0;
				while(l<=r){
					int mid=(l+r)>>1;
					if(check(mid,i)>=n) r=mid-1,as=mid;
					else l=mid+1;
				}
				if(check(as,i)==n&&as>1000) ans++;
			}
			cout<<(signed)ans<<'\n';
		}
	}
} 
```

---

## 作者：rui_er (赞：2)

我们可以暴力检查进制数不超过 $B$ 的是否符合要求；然后对于进制数大于 $B$ 的，位数不超过 $\log_BN$，可以暴力枚举每一位的值然后二分进制数检查。

代码中 $B=10^3$。

```cpp
// Problem: F - Zero or One
// Contest: AtCoder - AtCoder Beginner Contest 293
// URL: https://atcoder.jp/contests/abc293/tasks/abc293_f
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(ll x=(y);x<=(z);x++)
#define per(x,y,z) for(ll x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
#define likely(exp) __builtin_expect(!!(exp), 1)
#define unlikely(exp) __builtin_expect(!!(exp), 0)
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
ll randint(ll L, ll R) {
	uniform_int_distribution<ll> dist(L, R);
	return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

ll T, n;

ll cmp(ll n, ll S, ll B) {
	__int128 val = 0;
	rep(i, 0, 5) {
		val = val * B + ((S >> i) & 1);
		if(val > n) return 1;
	}
	return val < n ? -1 : 0;
}

int main() {
	for(scanf("%lld", &T); T; T--) {
		scanf("%lld", &n);
		ll ans = 0;
		rep(B, 2, 1000) {
			bool ok = true;
			for(ll i = n; i; i /= B) ok &= i % B <= 1;
			ans += ok;
		}
		rep(i, 1, 63) {
			ll L = 1001, R = n; bool ok = false;
			while(L <= R) {
				ll M = (L + R) >> 1, qwq = cmp(n, i, M);
				if(!qwq) {ok = M > 1000; break;}
				if(qwq == -1) L = M + 1;
				else R = M - 1;
			}
			ans += ok;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：xiaruize (赞：2)

**题意**

$T$ 组数据，每组一个正整数 $n$，保证 $2\leq n \leq 10^{18}$ ，对于每个 $n$ 求满足条件的 $b$ 的个数，使得 $n$ 的 $b$ 进制表示只包含 $0$ 或 $1$

**思路**

官方题解给出了一种正经的做法，这里给出一种简单的数据分治做法

对于每个数 $n$ ，考虑将对答案的贡献分为以下三类:

1. $n-1$ , $n$
   
   显然这两种情况下的表示分别为 ``10``, ``11``

2. 位数 $\leq 3$
   1. 位数为 $2$ 时可以在 $\sqrt{n}$ 的周围暴力枚举约 $1000$ 个
   2. 位数为 $3$ 时同理在 $\sqrt[3]{n}$ 周围暴力枚举

3. 枚举进制 $b$ ，暴力检查

时间复杂度：

情况1: $O(1)$

情况2: $O(1000\cdot \log{n})$

情况3: $O(\sqrt[4]{n})$

显然不会超时

**警示后人**

不要用 ``pow`` !!!! 赛时 ``pow``炸了痛失rating

**Code**

```cpp
// bool st;
int t;
int n;
// bool en;

bool check(int x, int k) //检查x在k进制下是否可行
{
    while (x)
    {
        if (x % k > 1)
            return false;
        x /= k;
    }
    return true;
}

int get(int x) //二分求三次方根
{
    int l = 1, r = 1e6;
    while (l < r)
    {
        int mid = l + r + 1 >> 1;
        if (mid * mid * mid <= x)
            l = mid;
        else
            r = mid - 1;
    }
    return l;
}

void solve()
{
    cin >> n;
    if (n == 2)
    {
        cout << "1" << endl;
        return;
    }
    int x = sqrt(n);
    int y = get(n);
    int res = 0;
    for (int i = 2; i <= 1e5 && i * i * i * i <= n; i++)
    {
        if (check(n, i))
            res++;
    }
    //两位
    for (int i = max(2ll, x - 1000); i <= min(x + 1000, n - 2); i++)
    {
        if (i * i + i + 1 == n || i * i + 1 == n || i * i + i == n || i * i == n)
            res++;
    }
    //三位
    for (int i = max(2ll, y - 1000); i <= min(y + 1000, n - 2); i++)
    {
        if (i * i * i + i * i + i + 1 == n || i * i * i + i * i + 1 == n || i * i * i + i * i + i == n || i * i * i + i * i == n || i * i * i + i + 1 == n || i * i * i + 1 == n || i * i * i + i == n || i * i * i == n)
            res++;
    }
    cout << res + 2 << endl; //+2是n-1,n
}
```

---

## 作者：liruizhou_lihui (赞：1)

## 思路分析

暴力会挂。

考虑两种情况 $b \le 10^3$ 和 $b > 10^3$ ，再把这两种情况拼起来就好了。可能说的有点抽象。

不难发现：$1001^6>10^{18}$ 。所以对于一个合法 $b$ 进制肯定不超 $6$ 位。所以有 $2^{6}-1$ 种可能。可以枚举 $b$ 的值。你会发现对于一个 $b$ 进制下的数，那么 $b$ 越大这个数十进制下就越小。符合单调性直接上二分！

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool check1(int a,int b)//判断数字 a 在 b  进制下是否只有 1,0 。 
{
	while(a>0)
	{
		if(a%b>1)
		{
			return 0;
		}
		a/=b;
	}
	return 1;
}
int cal(int b,int sum,int a)//进制转换 
{
	int res=0;
	int now=1;
	while(sum>0)
	{
		if(sum%2==1)
		{
			res+=now;
			if(res>a)
			{
				return a+1;
			}
		}
		sum/=2;
		if(now>a/b+1&&sum>0)
		{
			return a+1;
		}
		now*=b;
	}
	return res;
}
bool check2(int a,int sum)//二分查找 a 在几进制下是 sum （sum 为 1,0 构成）？
{
	int l=1001;
	int r=a;
	bool res=0;
	while(l<=r)
	{
		int mid=(l+r)/2;
		int now=cal(mid,sum,a);
		if(now==a)
		{
			return 1;
		}
		if(now<a)
		{
			l=mid+1;
		}
		if(now>a)
		{
			r=mid-1;
		}
	}
	return 0;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t,a;
	cin>>t;
	while(t--)
	{
		cin>>a;
		int ans=1;//本轮答案。 
		for(int b=3;b<=min(1000LL,a);b++)// 3~1000 暴力枚举。 
		{
			ans+=check1(a,b);
		}
		if(a>1000)//超过一千。 
		{
			for(int sum=1;sum<=(1<<6)-1;sum++)//1~2^6-1 枚举。 
			{
				ans+=check2(a,sum);
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：ttq012 (赞：1)

有趣的缝合怪。

直接做不好做，于是考虑根号分治。

设一个阈值 $k$。首先对于 $b\in [2,k]$，考虑直接暴力分解出 $b$ 进制判断是否符合条件。当 $b\in [k+1,10^{18}]$ 的时候，由于此时答案很少，可以先算出二进制有多少位，然后对于每一个位置添上 $0$ 和 $1$，二分判断是否存在一组合法的值即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, cnt;
int a[10];
__int128 check(int base)
{
  __int128 res = 0;
  for (int i = 1; i <= 7; i++)
  {
    res = res * base + a[i];
    if (res > LLONG_MAX)
      break;
  }
  return res;
}
void dfs(int dep)
{
  if (dep == 8)
  {
    int l = 1001, r = 1e18, best = -1;
    while (l <= r)
    {
      int mid = l + r >> 1;
      __int128 val = check(mid);
      if (val == n)
      {
        cnt++;
        break;
      }
      else if (val > n)
        r = mid - 1;
      else
        l = mid + 1;
    }
    return ;
  }
  a[dep] = 0;
  dfs(dep + 1);
  a[dep] = 1;
  dfs(dep + 1);
}
signed main()
{
  int T;
  cin >> T;
  while (T--)
  {
    cnt = 0;
    cin >> n;
    int fa = 1000;
    for (int i = 2; i <= fa; i++)
    {
      bool flag = true;
      for (int j = n; j; j /= i)
        if (j % i > 1)
        {
          flag = false;
          break;
        }
      if (flag)
        cnt++;
    }
    dfs(1);
    cout << cnt << '\n';
  }
  return 0;
}
```


---

## 作者：Neil_Qian (赞：1)

# [ABC293F] Zero or One 题解

给定整数 $n\le10^{18}$，把它分解成一个进制，使得在这个进制下所有位的值为 $0/1$，求方案数。多测。

直接枚举进制肯定不行，二进制枚举每一位肯定也不行。把它们结合起来？设计算边界 $BASE$，即区间 $[1,BASE]$ 由第一种计算，区间 $[BASE,n]$ 由第二种计算。

这样下来，第一种时间复杂度 $O(BASE\times \log_{BASE}n)$，第二部分 $O(2^{\log_{BASE}n}\times \log_n\times \log_{BASE}n)$。可以自由决定 $BASE$ 的值，建议范围 $[100,10^4]$。文中取值部分留空。

下面简述两个部分（因为比较基础）：

- 对于第一部分，循环枚举进制 $[2,BASE]$，对于每个分解即可。

- 对于第二部分，枚举每一位是多少（二进制枚举），在二分查找多少进制符合即可。每次要枚举每一位。

综上，本题得解。

```cpp
//文中“/**/”为自行取值部分
#include<bits/stdc++.h>
using namespace std;typedef __int128 ll;//保险的__int128
ll T,n,B/**/,y,ans,now,L,R,mid,a,h;bool f;char c;
inline ll read(){
	h=0,c=getchar();
	while(!(c>='0'&&c<='9'))c=getchar();
	while(c>='0'&&c<='9')h=(h<<1)+(h<<3)+(c^48),c=getchar();
	return h;
}
inline void write(ll x){
	if(x>9)write(x/10);
	putchar((x%10)^48);
}
int main(){
	T=read();
	while(T--){
		n=read(),ans=0;
		for(int i=2;i<=B;i++){//第一部分
			y=n,f=1;
			while(y){
				now=y%i,y/=i;
				if(now!=0&&now!=1){f=0;break;}
			}
			ans+=f;
		}
		for(int i=0;i<(1<</**/)-1;i++){//第二部分
			L=B+1,R=n,f=0;
			while(L<=R){
				mid=(L+R)>>1,a=1,now=0;
				for(int j=0;j</**/;j++){//计算进制
					now=now*mid+((i>>j)&1);
					if(now>n)break;//防溢出
				}
				if(now==n){f=(mid>B);break;}//注意前面是否算过
				(now>n?R=mid-1:L=mid+1);
			}
			ans+=f;//统计
		}
		write(ans),putchar('\n');
	}
	return 0;
}
```

---

## 作者：_Imaginary_ (赞：1)

## Problem

给你一个很大的数 $N$，问有多少个 $b$，使得 $N$ 在 $b$ 进制下每一位为 $0$ 或 $1$.

多组数据，$T\le 1000$。

## Solution

先考虑一个简单的问题。给你一个 $b$，判断是否合法。

最简单的思路就是把 $N$ 写成 $b$ 进制下的数，每位一次判断，复杂度为 $\Theta(\log_b N)$。

于是，我们可以暴力枚举 $2\sim 1000$ 的所有 $b$，每个 $b$ 暴力判断是否符合，总运算次数约为 $1000\log N$，大概是 $6\times 10^4$ 以内。

对于更大的 $b$，容易发现 $1001^6>10^{18}$，所以最多只有 $6$ 位。我们就可以转而枚举每一位是不是 $0$ 或 $1$，总共 $63$ 种情况。对于每一种情况，二分查找符合要求的 $b$。

举个例子：枚举到一个二进制数为 $100110$，那么我们要找一个 $b$ 使得：

$$
b^5+b^2+b=N
$$

这显然关于 $b$ 单调，所以可以二分。

关于时间复杂度，由于 $1000+63$ 和 $T$ 同阶，所以总复杂度为 $O(T^2 \log N)$，可过。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n;
bool ok(ll n,int b)
{
	while(n)
	{
		if(n%b!=0 && n%b!=1) return 0;
		n/=b;
	}
	return 1;
}
void write(__int128 x)
{
	int sta[30];
	int top=0;
	do{
		sta[top++]=x%10,x/=10;
	}while(x);
	while(top) putchar(sta[--top]+48);
}
int cmp(ll n,int t,ll b)
{
	__int128 m=n;
	__int128 cur=0;
	for(int i=6;i>=0;i--)
	{
		cur*=b;
		if(t&(1<<i)) cur+=1;
//		write(cur);printf("\n");
		if(cur>m) return 1;
	}
	if(cur<m) return -1;
	if(cur==m) return 0;
}
bool s1(ll n,int t)
{
	ll L=1001,R=n,mid;
	int res;
	while(L<=R)
	{
		mid=(L+R)>>1;
		res=cmp(n,t,mid);
//		printf("n=%lld t=%lld mid=%lld: get %d\n",n,t,mid,res);
		if(res==0)
		{
			if(mid>=1001) return 1;
		}
		if(res==-1) L=mid+1;
		if(res==1) R=mid-1;
	}	
	return 0;
}
ll solve()
{
	ll ans=0;
	for(int i=2;i<=1000;i++)
		if(ok(n,i)) ans++;
	for(int i=1;i<=63;i++)
		if(s1(n,i)) ans++;
	return ans;
}
int main()
{
	int qwq;
	scanf("%d",&qwq);
	while(qwq--)
	{
		scanf("%lld",&n);
		printf("%lld\n",solve());
	}
	return 0;
}

```

---

## 作者：liruizhou_lihui (赞：0)

## 思路分析

暴力会挂。

考虑两种情况 $b \le 10^3$ 和 $b > 10^3$，再把这两种情况拼起来就好了。可能说的有点抽象。

不难发现：$1001^6>10^{18}$。所以对于一个合法 $b$ 进制肯定不超 $6$ 位。所以有 $2^{6}-1$ 种可能。可以枚举 $b$ 的值。你会发现对于一个 $b$ 进制下的数，那么 $b$ 越大这个数十进制下就越小。符合单调性直接上二分！

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool check1(int a,int b)//判断数字 a 在 b 进制下是否只有 1,0。 
{
	while(a>0)
	{
		if(a%b>1)
		{
			return 0;
		}
		a/=b;
	}
	return 1;
}
int cal(int b,int sum,int a)//进制转换 
{
	int res=0;
	int now=1;
	while(sum>0)
	{
		if(sum%2==1)
		{
			res+=now;
			if(res>a)
			{
				return a+1;
			}
		}
		sum/=2;
		if(now>a/b+1&&sum>0)
		{
			return a+1;
		}
		now*=b;
	}
	return res;
}
bool check2(int a,int sum)//二分查找 a 在几进制下是 sum （sum 为 1,0 构成）？
{
	int l=1001;
	int r=a;
	bool res=0;
	while(l<=r)
	{
		int mid=(l+r)/2;
		int now=cal(mid,sum,a);
		if(now==a)
		{
			return 1;
		}
		if(now<a)
		{
			l=mid+1;
		}
		if(now>a)
		{
			r=mid-1;
		}
	}
	return 0;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t,a;
	cin>>t;
	while(t--)
	{
		cin>>a;
		int ans=1;//本轮答案。 
		for(int b=3;b<=min(1000LL,a);b++)// 3~1000 暴力枚举。 
		{
			ans+=check1(a,b);
		}
		if(a>1000)//超过一千。 
		{
			for(int sum=1;sum<=(1<<6)-1;sum++)//1~2^6-1 枚举。 
			{
				ans+=check2(a,sum);
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：liruizhou_lihui (赞：0)

## 思路分析

暴力会挂。

考虑两种情况 $b \le 10^3$ 和 $b > 10^3$ ，再把这两种情况拼起来就好了。可能说的有点抽象。

不难发现：$1001^6>10^{18}$ 。所以对于一个合法 $b$ 进制肯定不超 $6$ 位。所以有 $2^{6}-1$ 种可能。可以枚举 $b$ 的值。你会发现对于一个 $b$ 进制下的数，那么 $b$ 越大这个数十进制下就越小。符合单调性直接上二分！

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool check1(int a,int b)//判断数字 a 在 b  进制下是否只有 1,0 。 
{
	while(a>0)
	{
		if(a%b>1)
		{
			return 0;
		}
		a/=b;
	}
	return 1;
}
int cal(int b,int sum,int a)//进制转换 
{
	int res=0;
	int now=1;
	while(sum>0)
	{
		if(sum%2==1)
		{
			res+=now;
			if(res>a)
			{
				return a+1;
			}
		}
		sum/=2;
		if(now>a/b+1&&sum>0)
		{
			return a+1;
		}
		now*=b;
	}
	return res;
}
bool check2(int a,int sum)//二分查找 a 在几进制下是 sum （sum 为 1,0 构成）？
{
	int l=1001;
	int r=a;
	bool res=0;
	while(l<=r)
	{
		int mid=(l+r)/2;
		int now=cal(mid,sum,a);
		if(now==a)
		{
			return 1;
		}
		if(now<a)
		{
			l=mid+1;
		}
		if(now>a)
		{
			r=mid-1;
		}
	}
	return 0;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t,a;
	cin>>t;
	while(t--)
	{
		cin>>a;
		int ans=1;//本轮答案。 
		for(int b=3;b<=min(1000LL,a);b++)// 3~1000 暴力枚举。 
		{
			ans+=check1(a,b);
		}
		if(a>1000)//超过一千。 
		{
			for(int sum=1;sum<=(1<<6)-1;sum++)//1~2^6-1 枚举。 
			{
				ans+=check2(a,sum);
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

