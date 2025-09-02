# Arrays Sum

## 题目描述

You are given a non-decreasing array of non-negative integers $ a_1, a_2, \ldots, a_n $ . Also you are given a positive integer $ k $ .

You want to find $ m $ non-decreasing arrays of non-negative integers $ b_1, b_2, \ldots, b_m $ , such that:

- The size of $ b_i $ is equal to $ n $ for all $ 1 \leq i \leq m $ .
- For all $ 1 \leq j \leq n $ , $ a_j = b_{1, j} + b_{2, j} + \ldots + b_{m, j} $ . In the other word, array $ a $ is the sum of arrays $ b_i $ .
- The number of different elements in the array $ b_i $ is at most $ k $ for all $ 1 \leq i \leq m $ .

Find the minimum possible value of $ m $ , or report that there is no possible $ m $ .

## 说明/提示

In the first test case, there is no possible $ m $ , because all elements of all arrays should be equal to $ 0 $ . But in this case, it is impossible to get $ a_4 = 1 $ as the sum of zeros.

In the second test case, we can take $ b_1 = [3, 3, 3] $ . $ 1 $ is the smallest possible value of $ m $ .

In the third test case, we can take $ b_1 = [0, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2] $ and $ b_2 = [0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2] $ . It's easy to see, that $ a_i = b_{1, i} + b_{2, i} $ for all $ i $ and the number of different elements in $ b_1 $ and in $ b_2 $ is equal to $ 3 $ (so it is at most $ 3 $ ). It can be proven that $ 2 $ is the smallest possible value of $ m $ .

## 样例 #1

### 输入

```
6
4 1
0 0 0 1
3 1
3 3 3
11 3
0 1 2 2 3 3 3 4 4 4 4
5 3
1 2 3 4 5
9 4
2 2 3 5 7 11 13 13 17
10 7
0 1 1 2 3 3 4 5 5 6```

### 输出

```
-1
1
2
2
2
1```

# 题解

## 作者：jun头吉吉 (赞：5)

# CF1408B 【Arrays Sum】
[~~宣传blog~~](https://chen-jia-liang.gitee.io/blog/2020/10/01/%E9%A2%98%E8%A7%A3-CF1408B-%E3%80%90Arrays-Sum%E3%80%91/)
## 题意
给出$n$与$k$,有一个长度为$n$的不下降序列$a$,你需要构造若干个不下降序列记为$b_1,b_2,b_3,\ldots,b_m$，并满足：

- 每个$b_i$长度都为$n$
- $a_i=\sum_{j=1}^mb_{j,i}$，即$a$中的第$i$个是所有$b_j$中第$i$个的和。
- $b_i$里不相同的元素不超过$k$

求出最小的$m$

## 题解
ConclusionForces石锤

看到${\color{black}\colorbox{#f0f0f0}{\texttt{greedy}}}$，那么八九不离十是个猜结论题了~~至少对小蒟蒻来说是这样的~~

简单地来讨论一下：
### $1.\ k=1$
这种情况非常显然，~~有手就行~~，但与第二种同样重要。

若$a_1=a_2=\ldots=a_n$则$m=1$，否则无解。
### $2.\ k>1$
这种情况就值得思考了。

首先，此时必然有解存在，比如`1 2 3 4 5`可以为
```
1 1 1 1 1
0 1 1 1 1
0 0 1 1 1
0 0 0 1 1
0 0 0 0 1
```
很明显这不是最优解，因为我们没有很好地利用$k$的条件，既然他说最大有$k$个不同，我就尽可能把$k$个用完。具体来说，就是从第一个开始往后选直到$k$个用完。

然后由于不用输出方案，我们把$a_i=\sum_{j=1}^mb_{j,i}$看成$a_i-\sum_{j=1}^mb_{j,i}=0$，也就是看成减操作。那么我们就可以每次从第一个开始，一直选到不能选位置，把这些全部减到零。在拿`1 2 3 4 5 k=3`举例

由于可以有三个不同，那么`b`就可以为

`1 2 3 3 3`

a:`0 0 0 1 2`

`0 0 0 1 2`

a:`0 0 0 0 0`

于是就得到了答案`2`。

这里我还用了一个玄学操作~~打的时候没看到~~。我们只需要循环到恰好使不相同的个数$\ =k$并把这些数设成$0$。后面的数不用去管，因为同减一个数并不会影响不同的个数。

循环到$a$都为$0$为止
## 代码
```cpp
#include<bits/stdc++.h>
namespace in{
	char buf[1<<21],*p1=buf,*p2=buf;
	inline int getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
	template <typename T>inline void read(T& t){
		t=0;int f=0;char ch=getc();while (!isdigit(ch)){if(ch=='-')f = 1;ch=getc();}
	    while(isdigit(ch)){t=t*10+ch-48;ch = getc();}if(f)t=-t;
	}
	template <typename T,typename... Args> inline void read(T& t, Args&... args){read(t);read(args...);}
}
using namespace std;
int t,n,k,a[200];
bool check(){
	for(int i=1;i<=n;i++)
		if(a[i])
			return false;
	return true;
}
bool flag[200];
signed main(){
	for(in::read(t);t--;){
		in::read(n,k);
		for(int i=1;i<=n;i++)
			 in::read(a[i]);
		if(k==1){//只能全部相等 
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					if(a[i]!=a[j]){
						 cout<<-1<<endl;
						 goto loop;
					}
			cout<<1<<endl;
			loop:;
		}
		else{
			//k>=2必有解 
			int m=0,tmp;a[0]=-1;
			while(!check()){
				m++;tmp=k;
				vector<int>to;
				for(int i=1;i<=n;i++){
					if(a[i]!=a[i-1]){
						if(tmp==0)break;
						else tmp--;
					}
					to.push_back(i);
				}
				for(auto kkk:to)
					a[kkk]=0;
			}
			cout<<m<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Karry5307 (赞：3)

### 题意

略。

### 题解

这题有好多人 FST 啊……这里讲一个不那么容易 FST 的做法。

注意到我们肯定是贪心加，如果某一个序列还没有用完就一直用这个序列，用完了再加，这样一定可以使答案最小。

把最小的答案求出来之后由于答案为 `-1` 有的时候可能还会不满足，最后 check 一下即可。

### 代码

```cpp

// This code is written by Karry5307
#include<bits/stdc++.h>
// Definition
#define For(i,x,y) for(register int i=(x);i<(y);i++)
#define Forr(i,x,y) for(register int i=(x);i<=(y);i++)
#define Rep(i,x,y) for(register int i=(x);i>(y);i--)
#define Repp(i,x,y) for(register int i=(x);i>=(y);i--)
#define ve vector
#define iter iterator
#define pb emplace_back
#define popb pop_back
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size())
#define F first
#define S second
#define PY return (void)puts("Yes")
#define PN return (void)puts("No")
#define P0 return (void)puts("0")
#define P1 return (void)puts("-1")
using namespace std;
// Typedefs
typedef int ll;
typedef long long int li;
typedef unsigned int ul;
typedef unsigned long long int ull;
typedef double db;
typedef long double ldb;
typedef pair<ll,ll> pii;
typedef pair<li,li> pll;
const ll MAXN=2e5+51,MOD=998244353,inf=0x3f3f3f3f;
// Structures and variables
ll test,n,kk,res;
ll x[MAXN],diff[MAXN];
set<ll>st;
// Fast IO
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-') ch=getchar();
    if(ch=='-') neg=-1,ch=getchar();
    while(isdigit(ch)) num=(num<<3)+(num<<1)+(ch-'0'),ch=getchar();
    return neg==1?num:-num;
} 
inline li readu()
{
    register li num=0;
    register char ch=getchar();
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch)) num=(num<<3)+(num<<1)+(ch-'0'),ch=getchar();
    return num;
} 
template<class T>
inline void writep(T x)
{
	if(x<0){return (void)putchar('-'),writep(-x);}
	if(x<10){return (void)putchar(x|48);}
	writep(x/10),putchar((x%10)|48);
}
template<class T>
inline void write(T x,char ch=' '){writep(x),putchar(ch);}
template<class T>
inline void writeln(T x){writep(x),putchar('\n');}
// chkmin and chkmax
template<class T>
inline void chkmax(T &x,const T &y){x=x>y?x:y;}
template<class T>
inline void chkmin(T &x,const T &y){x=x<y?x:y;}
// Functions
template<class T,class Compare>
inline void sort(ve<T>&v,Compare cmp=less<T>()){sort(all(v),cmp);}
template<class T>
inline void reverse(ve<T>&v){reverse(all(v));}
template<class T>
inline void clear(T *arr){memset(arr,0,sizeof(arr));}
template<class T>
inline void setInf(T *arr){memset(arr,0x3f,sizeof(arr));}
// Math funcs
inline ll qpow(ll base,ll exponent)
{
	li res=1;
	while(exponent)
	{
		if(exponent&1)
		{
			res=(li)res*base%MOD;
		}
		base=(li)base*base%MOD,exponent>>=1;
	}
	return res;
}
inline ll gcd(ll x,ll y)
{
	return !y?x:gcd(y,x%y);
}
inline li lcm(ll x,ll y)
{
	return x/gcd(x,y)*y;
}
// Functions
inline void solve()
{
	n=read(),kk=read(),res=0;
	for(register int i=1;i<=n;i++)
	{
		x[i]=read();
	}
	for(register int i=1;i<=n;i++)
	{
		if(i==1)
		{
			diff[++res]=1;
			continue;
		}
		if(x[i]!=x[i-1])
		{
			if(diff[res]!=kk)
			{
				diff[res]++;
			}
			else
			{
				diff[++res]=2;
			}
		}
	}
	for(register int i=1;i<=res;i++)
	{
		if(diff[i]>kk)
		{
			P1;
		}
	}
	printf("%d\n",res);
}
int main()
{
	test=read();
	for(register int i=0;i<test;i++)
	{
		solve();
	}
}
```

---

## 作者：7KByte (赞：2)

考虑贪心。

由于是不降序列，那么整个序列可以分为权值相等的$x$段。

当$x>1$且$k=1$时无解，显然第一次我们只能用第一段的数，第二次必须选$0$，这样后面的元素就无法顾及。

这也提醒了我们正解。贪心的想，第一次我们选择前$k$段，之后每一次都要先选前面的若干个$0$，这样一次就只能选$k-1$段。

那么答案就是$1+\lceil \frac{x-k}{k-1}\rceil$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 500005
using namespace std;
int n,a[N],k;
void solve(){
	scanf("%d%d",&n,&k);
	rep(i,1,n)scanf("%d",&a[i]);
	int sum=0;
	rep(i,1,n)if(i==1||a[i]!=a[i-1])sum++;
	if(k==1&&sum!=1)puts("-1");
	else if(k==1)puts("1"); 
	else {
		int now=max(0,sum-k);
		if(now)printf("%d\n",1+(now-1)/(k-1)+1);
		else printf("%d\n",1);
	}
}
int main(){
	int T;scanf("%d",&T);
	while(T--)solve();
	return 0;
} 
```

---

## 作者：tommymio (赞：1)

题意:求出最小的 $m$ ,令 $m$ 个长度为 $n$ 的不降序列 $b_i$，使得 $\forall j\in[1,n],\sum_{i=1}^m b_{i,j}=a_j$。

可以想到，令一个序列负责一段值，其他序列在这个位置的值为 $0$ 即可。序列之间没有顺序，所以我们指定从序列 $b_1$ 开始，到序列 $b_n$。第 $1$ 个序列从 $a_1$ 这一段值开始，可以负责 $k$ 段不同的值，而之后的序列得先从 $0$ 开始，再负责其他段的值，那么就只能负责 $k-1$ 段值。

设序列 $a$ 中有 $cnt$ 个不同的值，如果存在这样的 $m$，根据上述分析，$m=1+\left\lceil\frac{cnt-k}{k-1}\right\rceil$。仅当 $k=1\wedge cnt>1$ 时，不存在这样的 $m$。

```cpp
#include<cstdio>
int a[105];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline int max(const int &x,const int &y) {return x>y? x:y;}
int main() {
	int T=read();
	while(T--) {
		int n=read(),k=read(),cnt=0; a[0]=-1;
		for(register int i=1;i<=n;++i) {a[i]=read(); if(a[i]!=a[i-1]) ++cnt;}
		if(cnt>1&&k==1) printf("-1\n");
		else if(k==1) printf("1\n");
		else if(cnt<=k) printf("%d\n",1);
		else printf("%d\n",1+(max(0,cnt-k)-1)/(k-1)+1);
	} 
	return 0;
}
```

---

## 作者：_byta (赞：0)

第一眼看题似乎很棘手，我们一步步分析。

首先手玩一下样例可以发现当 $k=1$ 时若数组所有元素都相等那可以构造一个与给定数组一致的数组，否则无解。

接下来考虑一般情况，我们想让 $m$ 尽可能小，那我们构造的每一个数组肯定要尽可能多的抵消原数组中的数，也就是说构造的每个数组都要多的与原数组不同的数匹配。

于是我们可以按照这个思路贪心处理，首先找到 $a$ 数组开头的 $k$ 个不同的数，单独分一组，之后由于 $a$ 的前 $k$ 个不同的数已经匹配了，所以要补零，我们每次向后找 $k-1$ 个不同的数分组，输出组数即可。

另外有一些细节需要特判，具体见代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100002;
int n, m, l, r, p, t, k, ans, sum, tot, cnt, a[N], b[N], c[N], dif, yoy;
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
	{
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9')
	{
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int main()
{
    int T = read(); 
    while (T--)
    {
    	n = read(); k = read();
    	dif = 1;
    	ans = 0;
    	for (int i = 1; i <= n; i++)
    	{
    		a[i] = read();
    		if(i > 1 && a[i] != a[i - 1]) dif++;
    	}
    	if(k == 1)
    	{
    		if(a[1] == a[n]) 
    		{
    			cout << "1" << endl;
    			continue;
			}
			else 
			{
				cout << "-1" << endl;
    			continue;
			}
		}
    	if(dif == 1)
    	{
    		cout << "1" << endl;
    		continue;
		}
    	t = 1;
    	for (int i = 2; i <= n; i++)
    	{
    		if(a[i] != a[i - 1]) t++;
    		if(t > k)
    		{
    			ans++;
    			t = 2;
			}
		}
		if(t == 1 && a[n] != a[n - 1]) ans++;
		if(t > 1) ans++;
		cout << ans << endl;
	}
    return 0;
}
```



---

## 作者：s_r_f (赞：0)

记 $cnt = a$ 序列中不同的数的个数。

不难发现如果确定了 $m$ ， 那么 $cnt \leq m * (k-1) + 1$ 的数列都能被表示出来。

至于证明，考虑一下差分数组即可。

每一个 $b_i$ 都可以使差分数组上的 $k-1$ 个位置有值，那么就可以表示出有不超过 $ m * (k-1) + 1$ 个不同数字的 $a_i$ 了。

最后特判一下 $-1$ 即可。

$\Theta(n)$

code : 
```cpp
#include <bits/stdc++.h>
using namespace std;
template <typename T> void read(T &x){
	static char ch; x = 0,ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0',ch = getchar();
}
inline void write(int x){if (x > 9) write(x/10); putchar(x%10+'0'); }
int a[1000],n,k;
inline void solve(){
	int i,tot = 0;
	read(n),read(k);
	for (i = 1; i <= n; ++i) read(a[i]),tot += (i==1 || a[i] != a[i-1]);
	if (tot <= k){ cout << 1 << '\n'; return; }
	if (k == 1){ cout << -1 << '\n'; return; }
	int cnt = 1; tot -= k;
	while (tot > 0) tot -= k-1,++cnt;
	cout << cnt << '\n';
}
int main(){ int T; read(T); while (T--) solve(); return 0; }
```

---

## 作者：钓鱼王子 (赞：0)

贪心。

每次操作，当前位置如果需要且还能用不同的数就用（把自己变成 $0$），直到不能用为止。

也就是说，第一次操作可以使 $k$ 个数变为 $0$，之后每次操作可以使 $k-1$ 个数变为 $0$。

直接计算即可，注意特判 $k=1$，以及 C++ 中负数除法的处理方式，最好额外特判一下。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,m,a[1000002],b[1000002],t,ans,c[1000002],p[1000002];
int main(){
	t=read();
	while(t--){
		n=read(),m=read();
		for(re int i=1;i<=n;++i)a[i]=read();a[0]=-1;
		if(m==1){
			if(a[1]==a[n])puts("1");
			else puts("-1");
			continue;
		}ans=0;
		for(re int i=1;i<=n;++i)if(a[i]^a[i-1])++ans;
		if(ans>m)
		printf("%d\n",(ans-m-1)/(m-1)+2);
		else puts("1");
	}
}
```




---

## 作者：Little09 (赞：0)

先说一句，我 FST 了。

题意就不说了。可以想到，对于一个 $a_{i+1}$ 相对于 $a_i$ 来说 $(a_i≠a_{i+1})$，在 $m$ 个 $b$ 数组中只需要有一个的 $b_{i+1}$ 与 $b_i$ 不同。这是很显然的。

举个例子：

7 = 2 + 2 + **3**    
9 = 2 + **2**  +**5**  
17= 2 +**10**  +5

黑色标出的是发生变化的。

那么，要是 $m$ 个 $b$ 的不同元素数量小于等于 $k$，就是这几个 $b$ 轮流进行变换，周期是 $m$。那么就可以推出来 $m$ 的表达式。若用 $cnt$ 表示 $a$ 不同元素数量，则：

$$m=\lceil\dfrac{cnt-1}{k-1} \rceil$$

另外，$k=1$ 肯定是要特判的。还有个 FST 的坑点，就是 $m$ 不可能等于 $0$ 啊。也就是说 $cnt$ 等于 $1$ 的时候也是要注意的。

时间复杂度 $O(tn)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k; 
int a[109];
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		cin >> n >> k;
		for (int i=1;i<=n;i++) cin >> a[i];
		if (k==1)
		{
			for (int i=2;i<=n;i++)
			{
				if (a[i]!=a[i-1]) 
				{
					cout << -1 << endl;
					goto yy;
				}
			}
			cout << 1 << endl;
			yy:;
			continue; 
		}
		int cnt=1;
		for (int i=2;i<=n;i++) if (a[i]!=a[i-1]) cnt++;
		int ans=(cnt+k-3)/(k-1);
		if (ans==0) ans++;
		cout << ans << endl;
	}
	return 0;
}
```


---

## 作者：vectorwyx (赞：0)

令 $f(k)$ 表示一个数组 $k$ 中出现的不同取值数。

当 $k\ge f(a)$ 时，我们只需要令 $b_{1}$ 等于 $a$，答案为1。

当 $k<f(a)$ 时，我们考虑把原本的数组 $b_{1}$ 拆成几个满足 $f(b_{i})\le k$ 的数组。

设经过拆分后的 $b_{1}$ 为 $b_{1}^{'}$，则 $f(b_{1}^{'})=k$。换句话说，我们要把 $b_{1}$ 中 $f(b_{1})-k$ 个不同的取值变成与任意一个其它的取值相同的值。

这句话有点绕，我以样例中的第三组为例解释一下：

$k=3$

$a={0,1,2,2,3,3,3,4,4,4,4}$

$b_{1}={0,1,2,2,3,3,3,4,4,4,4}$

最开始 $a$ 和 $b_{1}$ 是一样的，由于 $f(a)=f(b_{1})=5>k=3$，所以我们需要把 $b_{1}$ 中的$f(b_{1})-k=2$ 个不同的取值变成与任意一个其它的取值相同的值。$b_{1}$ 中元素的取值有五个:${0,1,2,3,4}$，所以我们要做的就是选择两个不同的取值，比如说 ${2,3}$，然后把 $2,3$ 变成 ${0,1,4}$ 中任何一个数，比如说 $0$，那么我们的 $b_{1}$ 就变成了 $0,1,0,0,4$，分出来的 $b_{2}$ 就是 ${0,0,2,3,0}$。

但这并不满足不下降的性质，而显然，我们把 $b_{1}$ 中的后 $f(b_{1})-k$ 个取值变成第 $k$ 个取值就一定能满足条件。因此，对于刚才那个例子，我们需要把 ${3,4}$ 变成${2}$，这样$b_{1}={0,1,2,2,2},b_{2}={0,0,0,1,2}$，均是不下降的。

这种方法可以保证得到的 $b_{1}$ 不下降，$f(b_{1})\le k$ 且 $b_{2}$ 不下降。那如何让 $f(b_{2})\le k$ 呢？我们发现这是一个形式完全一致的子问题，递归求解即可。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int maxn=105;
int a[maxn],k;

int solve(int x,int last){//递归求解,x为当前数组的f值，last为上一个数组的f值 
	//printf("solve(%d,%d)\n",x,last);
	if(x==last) return -1;//如果这一次递归相比上一次递归，数组的f值并没有减小，那么肯定无解 
	if(x<=k) return 1;//当前数组已经满足条件，无需继续递归。 
	int qwq=solve(x-k+1,x);
	if(qwq==-1) return -1;
	return qwq+1;//solve函数事实上返回的是递归的层数，因此需要把下一层的层数+1再返回 
}

void work(){
	int n=read(),cnt=1;
	k=read();
	fo(i,1,n) a[i]=read(); 
	fo(i,2,n) if(a[i]!=a[i-1]) cnt++;//先求出f(a)
	printf("%d\n",solve(cnt,-1));
	//puts("");
}
int main(){
	int T=read();
	while(T--){
		work();
	}
	return 0;
}
```


---

## 作者：LRL65 (赞：0)

这道题在考场上被坑了好几波。

听说有不少人FST了，还好我没有FST。值得庆祝的是本蒟蒻这场比赛加了217分，上绿了。


------------
### 题意：

就是将一个长度为 $n$ 的 $a$ 数组分成 $m$ 个长度为 $n$ 的数组。而且每个数组最多有 $k$ 个不同的数。同时，使这 $m$ 个数组的第 $i$ 位加起来等于 $a_i$ 。问 $m$ 最小是多少？



------------
### 思路：

首先考虑什么时候输出 $-1$，当 $k=1$ 且 整个数组有两种不同的数，那么就输出 $-1$ 。那么除此之外 $k=1$ 时就应该输出 $1$ 。

然后考虑普通的，我们先统计所有不同数字的数量。然后每一轮可以减掉 $k-1$ ，因为我们还需要留一个给不变的（也就是减 $ 0$ 的）用。最后如果数量已经小于 $k$ 了就输出 $ans+1$ ，因为最后一次就可以了。


------------

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,t,a[105];
int main() {
	cin>>t;
	while(t--) {
		cin>>n>>k;
		bool f[105];
        int cnt=0;
        for(int i=0;i<105;i++)f[i]=0;//清0
		for(int i=1;i<=n;i++) {
			cin>>a[i];
			if(f[a[i]]==0) f[a[i]]=1,cnt++;//统计数量
		}
		if(k==1&&cnt>1)cout<<-1<<endl;//特判
		else if(k==1)cout<<1<<endl;
		else {
            int ans=0;
            while(1) {
                if(cnt<=k) {
                    cout<<ans+1<<endl;//小于就输出
                    break;
                }
			    cnt=cnt-(k-1);//每次减k-1
                ans++;
            }
		}
	}
}
```


---

## 作者：Isshiki_Hugh (赞：0)

$O(1)$输出

先判断一下特殊情况，即$k=1$的情况

之后我只需要尽可能多的让一组消掉更多的数就行了，由于第一组最多消去$k$个数，之后的每一组最多消去$k-1$个数(因为需要前导0来占位)

```cpp
// 头文件略
const int N = 1e6+9;
const int inf = 1e9+9;
const double eps = 1e-7;
int _,n,k,a[2*N],ans;


int main(){
    std::ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    #ifdef LOCAL //use "g++ xxx.cpp -DLOCAL"
        freopen("in.in", "r", stdin);
    #endif
    cin >> _;
    while(_--){
        cin >> n >> k;ans = 0;
        rep(i,1,100) a[i] = 0;
        rep(i,1,n) cin >> a[i];

        int len = std::unique(a+1,a+n+1) - a - 1;

        if(k == 1 && len > 1){
            cout << "-1\n";
        } else if(k == 1){
            cout << 1 << "\n";
        } else if(k >= len){
            cout << 1 << "\n";
        } else {
            int x = len - k;
            if(x % (k-1)) ans = x / (k-1) + 2;
            else ans = x / (k-1) + 1;
            cout << ans << "\n";
        }
    }
    return 0;
}
```

---

