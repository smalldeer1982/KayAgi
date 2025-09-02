# Multi-judge Solving

## 题目描述

Makes solves problems on Decoforces and lots of other different online judges. Each problem is denoted by its difficulty — a positive integer number. Difficulties are measured the same across all the judges (the problem with difficulty $ d $ on Decoforces is as hard as the problem with difficulty $ d $ on any other judge).

Makes has chosen $ n $ problems to solve on Decoforces with difficulties $ a_{1},a_{2},...,a_{n} $ . He can solve these problems in arbitrary order. Though he can solve problem $ i $ with difficulty $ a_{i} $ only if he had already solved some problem with difficulty ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF825C/dcc3f539eeb6ae660df27e0ba4735db648eac084.png) (no matter on what online judge was it).

Before starting this chosen list of problems, Makes has already solved problems with maximum difficulty $ k $ .

With given conditions it's easy to see that Makes sometimes can't solve all the chosen problems, no matter what order he chooses. So he wants to solve some problems on other judges to finish solving problems from his list.

For every positive integer $ y $ there exist some problem with difficulty $ y $ on at least one judge besides Decoforces.

Makes can solve problems on any judge at any time, it isn't necessary to do problems from the chosen list one right after another.

Makes doesn't have too much free time, so he asked you to calculate the minimum number of problems he should solve on other judges in order to solve all the chosen problems from Decoforces.

## 说明/提示

In the first example Makes at first solves problems 1 and 2. Then in order to solve the problem with difficulty 9, he should solve problem with difficulty no less than 5. The only available are difficulties 5 and 6 on some other judge. Solving any of these will give Makes opportunity to solve problem 3.

In the second example he can solve every problem right from the start.

## 样例 #1

### 输入

```
3 3
2 1 9
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 20
10 3 6 3
```

### 输出

```
0
```

# 题解

## 作者：dinghongsen (赞：3)

## CF825C Multi-judge Solving Solution（题解）
### [题目传送门](https://www.luogu.com.cn/problem/CF825C)

本题考察的是基本的贪心排序。

将所有题的难度进行排序，由难度低的题向难度高的题做，每做完一个题就更新 $K$ 值

若遇到做不出来的题，$K$ 值变成 $2\times K$， 并记录在其他地方的做题数量，直到做完所有的题。

#### AC Code:

```cpp
# include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 10;
int n, k, cnt;
int a[N];
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) {
	    scanf("%d", &a[i]);
	}
	sort(a, a + n);
	for (int i = 0; i < n; i++) {
		while (2 * k < a[i]) {
		    cnt++;
		    k *= 2;
		}
		k = max(k, a[i]);
	}
	printf("%d", cnt);
	return 0；
}
```


---

## 作者：zhangqiuyanAFOon2024 (赞：1)

### 思路
直接贪心。

显然，要将 $a$ 从小到大排序，然后一道一道做。

按照题意：如果 $a_i>2\times k$，则就做一道其它网站的题，然后按照题意更新即可。

没什么难点，直接放代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int a[N];
int main(){
	int n,k,cnt=0;
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		while(2*k<a[i]) k*=2,cnt++;
		k=max(k,a[i]);//做过最难的题目
	} 
	cout<<cnt;
	return 0;
}
```

---

## 作者：_liuyi_ (赞：1)

# 思路
显然贪心，将 $a$ 排序后，如果 $2 \times k < a_i$，$k=k \times 2$，累加一下答案，注意有个坑点，$k=\max(k,a_i)$，具体看代码实现。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,a,n) for(int i=n;i>=a;i--)
#define fi first
#define se second
#define pb push_back
#define mem(a,x) memset(a,x,sizeof(a))
#define all(x) x.begin(),x.end()
#define lisan(x) {sort(all(x));x.erase(unique(all(x)),x.end());}
#define SZ(x) ((int)((x).size()))
#define debug(x) cout<<#x<<"="<<x<<"\n";
#define ti (db)((db)clock() / CLOCKS_PER_SEC)
typedef long long ll;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
typedef vector<int> VI;
typedef vector<vector<int>> VII;
typedef vector<ll> VL;
typedef vector<vector<ll>> VLL;
typedef unsigned long long ull;
typedef double db;
template<typename T> inline void cmax(T &a,const T b){if(a<b) a=b;}
template<typename T> inline void cmin(T &a,const T b){if(a>b) a=b;}
template<typename T> inline T gcd(T a,T b){return b?gcd(b,a%b):a;}
template<typename T> inline T lcm(T a,T b){return a/gcd(a,b)*b;}
constexpr int N=1e6+10;
constexpr int mod=1e9+7;
//constexpr int mod=998244353;
int n,k,a[N],cnt;
inline void solve(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    cin >> n >> k;
    rep(i,1,n) cin >> a[i];
    sort(a+1,a+1+n);
    rep(i,1,n){
        if(a[i]<=k) continue;
        while(a[i]>2*k) k=k*2,cnt++;
        if(a[i]<=2*k) k=a[i];
    }
    printf("%d\n",cnt);
}
int main(){
    int T=1;
    //scanf("%d",&T);
    while(T--) solve();
}
```


---

## 作者：__lcm (赞：0)

这道题我们要用贪心。

要先排序，如果 $2\times k<a_i$ 就去做别的网站上的题目。

最后更新一下就好了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
int a[N];
int n, m;
int main(){
	int cur = 0;
	cin >> n >> m;
	for(int i = 1; i <= n; i ++) cin >> a[i];
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i ++){
		while(2 * m < a [i]) m *= 2,cur++;
		m = max (m, a[i]);
	} 
	cout << cur << '\n';
	return 0;
}
```

---

## 作者：keep_shining (赞：0)

## 思路：
先考虑贪心，那先排一遍序，不然大小掺杂没法算，然后遍历 $a$ 数组，看每个 $a_i$ 是否小于两倍的 $k$，若大于，那么就去做别的 OJ 上的题，然后把 $k$ 变为原来的两倍，直到 $k$ 大于当前的 $a_i$。

#### 警示：每次做完 $a_i$ 这道题都要更新 $k$ 的值，因为有这样一句话：做完之后 k 就要更新为你做过最难的题目，也就是说要让 $k=\max(k,a_i)$。


## AC code：
```cpp
#include<bits/stdc++.h>

using namespace std;

#define fst ios::sync_with_stdio(false);cin.tie();cout.tie();
#define Endl endl
#define itn int
#define For(i,a,b) for(register int i=a;i<=b;i++)
#define endl '\n'
#define int long long

const int N=1e3+5;
const int M=2e3+5;

int n,k,a[N],ans; 

int read()
{
	register int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}

void write(int x)
{
	if(x>9)write(x/10);
	putchar(x%10+'0');
}

signed main()
{
	n=read();
	k=read();
	For(i,1,n)
	{
		a[i]=read();
	}
	sort(a+1,a+1+n);//排个序
	For(i,1,n)
	{
		while(2*k<a[i])//做不了就去别的网站上做，直到可以做
		{
			ans++;//去别的网站上做题数+1
			k*=2;//变成两倍
		}
		k=max(a[i],k);	//做完之后k就要更新为你做过最难的题目
	}
	write(ans);
    return 0;
} 
```

---

## 作者：Melo_DDD (赞：0)

一道简单的贪心题，感觉没有黄？

# 题目大意

如果对于你将要做的题：$a_i>2\times k$，那么你就需要在别的 OJ 上做。

# 题目实现

当然要先进行排序，不然一会大一会小的怎么算。

排序之后直接枚举，内层套一个循环，在 $a_i\le2\times k$ 之前一直需要在别的 OJ 上做，将答案加一之后再将 $k$ 乘 $2$。

需要注意的是当 $a_i\le2\times k$ 时循环结束，那么我们的 $k$ 值没有更新，最后要单独乘个 $2$。

```
做完之后 k 就要更新为你做过最难的题目。
```
所以还得对 $a_i$ 取 $\min$。

## 代码

```cpp
#include <bits/stdc++.h>
#define rep(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
using namespace std ;
const int N = 1e5 + 7 ;
int n ,k ,a[N] ,res ;
template <typename T> inline void read (T &x) {
	x = 0 ;
	char ch = getchar () ;
	while (! isdigit (ch)) {
		ch = getchar () ;
	}
	while (isdigit (ch)) {
		x = (x << 1) + (x << 3) + (ch xor 48) ;
		ch = getchar () ;
	}
}
int main () {
	read (n) ,read (k) ;
	rep (i ,1 ,n ,1) {
		read (a[i]) ;
	}
	sort (a + 1 ,a + n + 1) ;
	rep (i ,1 ,n ,1) {
		if (a[i] <= k) goto her ;
		while (2 * k < a[i]) {
			res ++ ;
			k *= 2 ;
		}
		k = min (k * 2 ,a[i]) ;
		her : ;
	}
	cout << res << '\n' ;
	return 0 ;
}
//kafka & かみや & やえみこ
```

---

## 作者：Breath_of_the_Wild (赞：0)

这道题显然是贪心题。

思路：把 $a$ 数组从小到大排序后，枚举每一个 $i$，如果 $2\times k$ 小于 $a_i$，就一直让 $k$ 乘 $2$，计数器加 $1$，直到 $k$ 大于等于 $a_i$。然后根据题意，做完之后 $k$ 就要更新为做过最难的题目，即求最大值。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e3+5;
ll n,m,ans=0,a[N];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		while(2*m<a[i]){
        //做不出来就在其他 OJ 上做题，计数器加一
        	ans++;
        	m*=2;
		}
		m=max(m,a[i]);
	}
	cout<<ans<<'\n';
	return 0;
}

---

## 作者：TemplateClass (赞：0)

显然的贪心题，如果 $a_i > 2 \times k$，就一直做其它 OJ 的题目，最后更新 $k$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n, k, a[1009], ans = 0;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> k;
	for(int i = 1; i <= n; ++i){
		cin >> a[i];
	}
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; ++i){
		if(a[i] <= k) continue;
		else{
			while(a[i] > 2 * k) {
				ans ++, k <<= 1;
			}
			k = max(k, a[i]);
		}
	}
	cout << ans << "\n";
	
	return 0;
} 
```

---

## 作者：Not_lazy (赞：0)

## CF825C Multi-judge Solving  Solution（题解）
[题目](https://www.luogu.com.cn/problem/CF825C)

[博客食用更佳](https://www.luogu.com.cn/blog/820437/Solution-CF825C)

---
### 题意
@Aw 顿顿 已经写的很清楚了（在此鸣谢）。

---
### 正文
考察的是对贪心排序的使用能力。

贪心算法：将所有题的难度进行排序，由难度低的题向难度高的题做，每做完一个题就更新 $K$ 值。

若遇到做不出来的题，即在其他地方做题，使得 $K$ 值变成 $2 \times K$，并记录在其他地方的做题数量，直到做完所有的题。我们要尽可能的增大，但是不能一直 $\times 2$。

“我们要尽可能地少在其他 OJ 上做题，而在 DoceForces 上做的题目不算在内，也就是说，如果你能够通过某个 $a_i$ 在当做跳板，那你就可以扩大自己的 $k$，而不需要浪费一次使用其他 OJ 的机会。”

---
### 参考代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2000;
int n,k,cnt;
int a[N];
int main(){
	scanf("%d %d",&n,&k);
	for(int i=1; i<=n; i++)scanf("%d",&a[i]);
	sort(a + 1, a + 1 + n);
	for(int i=1; i<=n; i++){
		while(2 * k < a[i])cnt ++, k *= 2;
		k = max(k, a[i]);
	}
	printf("%d\n",cnt);
	return 0;
}
```


---

## 作者：___cjy__ (赞：0)

# CF825C Multi-judge Solving 题解

[题目传送门](https://www.luogu.com.cn/problem/CF825C)

[更好的阅读体验](https://www.luogu.com.cn/blog/509668/solution-cf825c)

### 题目大意：

有 $N$ 个问题，第 $i$ 题的难度为 $a_i$。之前做到了最大难度为 $K$ 的题，现在我们可以做 $a_i \le 2 \times K$ 的题，每次做完一个题，$K$ 的值为当前做过的最难的题的难度。

若我们无法再做任何题，便可以到其他地方做题。每在其他地方做一个题 $K$ 值就可以变成 $2 \times K$。

求要想做完所有的 $N$ 个题，至少要在其他地方做几个题。

### 正文：

贪心：将所有题的难度进行排序，由难度低的题向难度高的题做，每做完一个题就更新 $K$ 值。

若遇到做不出来的题，即在其他地方做题，使得 $K$ 值变成 $2 \times K$，并记录在其他地方的做题数量，直到做完所有的题。

### AC Code：

```cpp
#include<bits/stdc++.h>
#define N 1234
#define int long long

using namespace std;

int n, k, cnt;
int a[N];

signed main(){
	cin >> n >> k;
	for(int i=1; i<=n; i++){
		cin >> a[i];
	}
	sort(a + 1, a + 1 + n);
	for(int i=1; i<=n; i++){
		while(2 * k < a[i]){
			cnt ++, k *= 2;
		}
		k = max(k, a[i]);
	}
	
	cout << cnt << endl;
	
	return 0;
}
```

---

## 作者：Aw顿顿 (赞：0)

## 题意

DecoForces 上存在 $n$ 个问题，难度为 $a_1,a_2,a_3\cdots a_n$，你已经做到了难度为 $k$ 的题目。

现在存在两种 OJ，一个是上述的 DecoForces，一个是其他的 OJ。对于任意一个难度为 $y$ 的题目，都存在于上述两种 OJ 的其中一种。

假设你现在做到了难度为 $k$ 的题目，那你下次可以做 $a_i\le 2\times k$ 的题目，做完之后 $k$ 就要更新为你做过最难的题目。

你至少要在其他 OJ 上做几道题？

## 解法

读入，排好序，然后开始操作，这是一道贪心的题目。

每次都想让这个数尽可能地增大，那是不是一直 $\times 2$ 就行了？

并不如此。

我们要尽可能地少在其他 OJ 上做题，而在 DoceForces 上做的题目不算在内，也就是说，如果你能够通过某个 $a_i$ 在当做跳板，那你就可以扩大自己的 $k$，而不需要浪费一次使用其他 OJ 的机会。

同样的，只有在两个 $a_i$ 的差距实在太大的时候，才需要使用其他 OJ。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 1005
inline int read(){
   register int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
   return s*w;
}int a[MAXN],n,k,s;
int mx(int x,int y){return x>y?x:y;}
signed main(){
    n=read(),k=read();
    for(int i=1;i<=n;i++)
        a[i]=read();
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++){
        while(a[i]>2*k)s++,k<<=1;
        k=mx(a[i],k);
    }printf("%lld\n",s);
    return 0;
}
```

---

## 作者：xzggzh1 (赞：0)

题意：

现在有 $N$ 个问题，已知之前已经最难做到了难度为 $K$ 的题，现在我们如果想要做一个题，我们可以做 $a_i \leq 2\times K $ 的题，每次做完难题之后，更新 $K$ 值。

我们现在可以在其他OJ上做题，来提升自己的实力，问做完这 $N$ 个题最少需要在其他OJ做几个题。

---

每一次到其他OJ上做题可以使得 $k$ 变成原来的两倍，因为我们要最小化到其他OJ上做题的数量，所以每次做题的时候要让 $k$ 变得尽可能大。

所以只要按照难度排序，贪心的只有当遇到难度高的没法做到的就去其他OJ上做题。

---

代码：

```cpp
#define int long long 
int a[1005];
signed main()
{
    int n,k;
    scanf("%lld%lld",&n,&k);
    int ans=0;
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    sort(a+1,a+1+n);
    for(int i=1;i<=n;k=max(k,a[i]),i++)
    while(a[i]>k*2){ans++;k*=2;}
    printf("%lld\n",ans);
}
```

---

