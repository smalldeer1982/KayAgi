# Powered Addition

## 题目描述

You have an array $ a $ of length $ n $ . For every positive integer $ x $ you are going to perform the following operation during the $ x $ -th second:

- Select some distinct indices $ i_{1}, i_{2}, \ldots, i_{k} $ which are between $ 1 $ and $ n $ inclusive, and add $ 2^{x-1} $ to each corresponding position of $ a $ . Formally, $ a_{i_{j}} := a_{i_{j}} + 2^{x-1} $ for $ j = 1, 2, \ldots, k $ . Note that you are allowed to not select any indices at all.

You have to make $ a $ nondecreasing as fast as possible. Find the smallest number $ T $ such that you can make the array nondecreasing after at most $ T $ seconds.

Array $ a $ is nondecreasing if and only if $ a_{1} \le a_{2} \le \ldots \le a_{n} $ .

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case, if you select indices $ 3, 4 $ at the $ 1 $ -st second and $ 4 $ at the $ 2 $ -nd second, then $ a $ will become $ [1, 7, 7, 8] $ . There are some other possible ways to make $ a $ nondecreasing in $ 2 $ seconds, but you can't do it faster.

In the second test case, $ a $ is already nondecreasing, so answer is $ 0 $ .

In the third test case, if you do nothing at first $ 2 $ seconds and select index $ 2 $ at the $ 3 $ -rd second, $ a $ will become $ [0, 0] $ .

## 样例 #1

### 输入

```
3
4
1 7 6 5
5
1 2 3 4 5
2
0 -4```

### 输出

```
2
0
3```

# 题解

## 作者：一扶苏一 (赞：13)

## 【构造】【CF1338A】 Powered Addition

### Solution

从构造的角度考虑可以避开分类讨论和对于一些奇怪性质的证明。

问题等价于找到一个序列 $b$，满足 $b$ 中都是非负整数，且将 $b$ 加到 $a$ 上以后得到的序列单调不降，最小化 $b$ 的最大值。也即我们要求对于 $i \geq 2$，满足

$$b_i + a_i \geq b_{i - 1} + a_{i - 1}$$

移项得到

$$b_i \geq b_{i - 1} + a_{i - 1} - a_i$$

由于要最小化 $b$，所以 $b_{i} = \max(0, b_{i - 1} + a_{i - 1} - a_i)$。

而 $b_1$ 显然等于 $0$ 是最优的。直接求 $b$ 即可。

### Code

```cpp
namespace Fusu {

const int maxn = 100005;

int n;
ll a[maxn], b[maxn];

int lg2(ll x) {
  int ret = 0;
  while ((1ll << ret) <= x) ++ret;
  return ret;
}

void Main() {
  int t;
  for (qr(t); t; --t) {
    qr(n);
    int ans = 0;
    qra(a + 1, n);
    b[1] = 0;
    for (int i = 2; i <= n; ++i) {
      b[i] = std::max(0ll, b[i - 1] + a[i - 1] - a[i]);
      ans = std::max(ans, lg2(b[i]));
    }
    qw(ans, '\n');
  }
}

} // namespace Fusu
```



---

## 作者：Wenoide (赞：6)

对每一个 $a_i$ 加上 $\max(a_j-a_i)$，即可在最短的时间内得到一个不下降序列。其中 $j\in [1,i]$。

可以在 $O(n)$ 的复杂度内求出 $k_{\max}=\max(a_j-a_i)$。

- $k_{\max}=0$。

	则原序列已经不下降。答案为 $0$。

- $k_{\max}>0$。

	**$2^0,2^1,\dots,2^{x-1}$ 可以组合出 $[1,2^x-1]$ 内的所有整数。**
    
    则有 $k_{\max}<=2^x-1$。

	解得 $x=\lceil \log_2(k_{\max}+1)\rceil$。即 $k_{\max}$ 的二进制位数。

------------

参考代码：
```
#include<cstdio>
const int MAXN=100000+10;
int p[MAXN];
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n;
		scanf("%d",&n);
		for(int i=0;i<n;++i){
			scanf("%d",p+i);
		}
		int max=-1e9,ans=0;
		for(int i=0;i<n;++i){
			if(p[i]>max){
				max=p[i];
			}
			if(ans<max-p[i]){
				ans=max-p[i];
			}
		}
		//寻找最大差值。
		if(ans==0){
			printf("0\n");
			continue;
		}
		//特判原序列已经不下降的情况。
		int cnt=0;
		while(ans!=0){
			ans>>=1;
			++cnt;
		}
		//计算二进制位数。
		printf("%d\n",cnt);
	}
	return 0;
}
```

---

## 作者：lgswdn_SA (赞：4)

早上没人做题，抢了个沙发~

这题挺水的，可以先参考那个积木大赛那题（某年提高水题）。这题和积木大赛有很大的相似之处。

然后处理 $2^{j-1}$ 这个东西。看到这种 $2$ 的次数幂，可以想道倍增。我们倍增找到通过加上一些 $2^{j-1}$ 可以获得的小的 $\max{j}$，最后处理一下答案即可。

代码中倍增的一些细节其实和其他倍增是一样的（比如说 LCA 的倍增），不多解释。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+9;
int T,a[N];
signed main(){
	cin>>T;
	for(int i=1;i<=T;i++){
		int n; scanf("%lld",&n); 
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
		int mx=0,ans=0;
		for(int i=2;i<=n;i++){
			if(a[i]<a[i-1]){
				for(int j=60;j>=1;j--){ //倒序倍增（详见LCA）
					if(a[i]+(1ll<<(j-1))<=a[i-1]){ //可以用这个j且必须用
						mx=max(mx,j); a[i]+=(1ll<<(j-1));//更新答案和a
					}
				}
			}
		}
		printf("%lld\n",mx);
	}
	return 0;
} 
```

---

## 作者：devout (赞：3)

我们发现每次加上去的那个数都是$2^k$的形式

所以对于答案$j$，我们可以给每个数任意加上$[0,2^{j+1}-1]$中的任意一个数

也就是说我们要让每个数加上的数的最大值最小

考虑维护一个变量$mx$表示之前的中的最大值

如果$a_i\leq mx$，那么我们把$a_i$增加到$mx$

否则更新$mx=a_i$

然后对于增加的数量中最大的那个取个对数就好了

```cpp
#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=1e5+5;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int t,n;
int a[N];

int main()
{
    read(t);
    while(t--){
        read(n);
        Rep(i,1,n)read(a[i]);
        int mx=a[1],dmx=0;
        Rep(i,2,n){
            if(a[i]>mx)mx=a[i];
            else dmx=max(dmx,mx-a[i]);
        }
        int ans=0;
        while(dmx){
            dmx/=2;
            ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
```


---

## 作者：dead_X (赞：1)

## 题意简述
给你 $n$ 个数，你可以执行 $x$ 轮操作。

每轮操作可以任选一些数(也可以不选) 并全部加上 $2^{x-1}$ 。

问至少几轮操作可以让原来的 $n$ 个数变成一个非严格递增序列。
## 思路简述
我们对每一个数进行考虑。

如果这一个数比前一个大，没问题，就这么留着，显然是最优的。

如果这一个数比前一个小，我们考虑它至少需要几轮操作才能比前一个更大。

这里给出一个结论: 若一定轮后能使这个数加上 $k(k>0)$ ，那么一定也能在这么多轮后使这个数加上 $k-1$ 。

证明显然，二进制拆分即可， $k-1$ 的最高位一定不会比 $k$ 更高。

所以我们先直接加 $2$ 的次方，算出最少轮数，然后加到前一个数加上 $1$ 即可。
## 代码
```
#include<bits/stdc++.h>
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
inline long long readll(){
   long long s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
using namespace std;
long long a[114514];
int main()
{
	int T=read();
	while(T--)
	{
		int n=read();
		for(int i=1; i<=n; i++) a[i]=readll();
		long long lst=-1234567890;
		int ans=0;
		for(int i=1; i<=n; i++) 
		{
			if(lst<a[i]) 
			{
				lst=a[i];
				continue;
			}
			int cnt=0;
			long long now=1;
			while(a[i]<lst) ++cnt,a[i]+=now,now<<=1;
			ans=max(ans,cnt);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：VenusM1nT (赞：1)

二分。  
（哇其他神仙都是什么神仙做法）  
观察发现要求最大值的最小值，容易想到二分，则对 $j$ 进行二分（边界为 $[0,31]$）。对于二分出的 $j$ 进行考虑，得到我们可以对每个数加上 $[0,2^j-1]$ 的数，此处应用贪心的思想，逆序考虑，将后面的数调得尽可能得大，如果 $a_i$ 无论如何都比 $a_{i+1}$ 大则不成立。

```cpp
#include<bits/stdc++.h>
#define MAXN 100005
#define reg register
#define inl inline
#define int long long
using namespace std;
int n,a[MAXN],t[MAXN];
inl bool Check(reg int mid)
{
	for(reg int i=1;i<=n;i++) t[i]=a[i];
	reg int maxn=(1<<mid)-1;
	t[n]+=maxn;
	for(reg int i=n-1;i>=1;i--)
	{
		if(t[i]>t[i+1]) return 0;
		t[i]=min(t[i]+maxn,t[i+1]);
	}
	return 1;
}
signed main()
{
	int Time;
	scanf("%lld",&Time);
	while(Time--)
	{
		scanf("%lld",&n);
		for(reg int i=1;i<=n;i++) scanf("%lld",&a[i]);
		reg int l=0,r=31,ans=31;
		while(l<=r)
		{
			reg int mid=(l+r)>>1;
			if(Check(mid))
			{
				r=mid-1;
				ans=min(ans,mid);
			}
			else l=mid+1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：SuyctidohanQ (赞：0)

### 题目分析

我们要想到的就是他最后什么时候结束？因为时间越久我们能使用的 $2$ 的幂越大，所以我们考虑最后是给谁补的（差距最大的一次递减），所以直接找最大下降空间即可。

### 代码实现

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll MAXN = 1e5 + 10;
ll T, x, jie[MAXN], shu[MAXN], maxx, maxxx, sum = 1;
int main() {
    jie[0] = 1;
    for (ll i = 1; i <= 32; i ++) {
		sum *= 2;
		jie[i] = sum;
	}
	scanf ("%lld", &T);
	while (T --) {
        scanf ("%lld", &x);
        maxx = INT_MIN; maxxx = INT_MIN;
        for (ll i = 1; i <= x; i ++) {
            scanf ("%lld", &shu[i]);
            maxxx = max (maxxx, shu[i]); maxx = max (maxx, maxxx - shu[i]);
        }
        if (maxx == INT_MIN) printf ("0\n");
        else printf ("%d\n", upper_bound (jie, jie + 33, maxx) - jie);
    }
	return 0;
}
```

---

## 作者：guozhe6241 (赞：0)

# 题目传送门

[CF1338A](https://www.luogu.com.cn/problem/CF1338A)

# 思路

我们将输入的数组遍历，对于当前的数，如果这个数比前一个数小，我们就对他进行操作。

因为数的最大减最小值是 $10^{18}$，所以我们从 $62$ 开始向 $1$ 遍历，看看当前数加上 $2^{j-1}$ 能否比下一个数大，如果可以，将答案与 $j$ 取最大值，最后输出。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+5;
int t,n;
int a[maxn];
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int mx=0,ans=0;
	for(int i=2;i<=n;i++){
		if(a[i]<a[i-1]){
			for(int j=62;j>=1;j--){
				if(a[i]+(1ll<<(j-1))<=a[i-1]){
					mx=max(mx,j);
					a[i]+=(1ll<<(j-1));
				}
			}
		}
	} 
	cout<<mx<<endl;
}
signed main(){
	cin>>t;
	while(t--){
		solve();
	}
    return 0;
}

```

[提交记录](https://www.luogu.com.cn/record/147635813)

---

## 作者：Ericby666 (赞：0)

## [题目链接](https://www.luogu.com.cn/problem/CF1338A)
赛时不小心将倒序倍增打成正序倍增惨遭爆零。

本题其实就是求将一个序列中的某些数选择一些 $j$，加上 $\sum2^{j-1}$，使其变成单调不降序列时最大的 $j$ 的最小值。所以我们可以从 $2^{60}$ 开始向下枚举，从而找到最大的 $j$ 的最小值。

AC 代码：
```cpp
#include<bits/stdc++.h>
#define int long long//记得开long long！！！
using namespace std;
int t,n,a[100005],maxx;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//优化输入
	cin>>t;
	while(t--){
		cin>>n;
		maxx=0;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=2;i<=n;i++)
			if(a[i]<a[i-1])
				for(int j=60;j>0;j--)//倒序倍增
					if(a[i]+(1ll<<(j-1))<=a[i-1]){
						maxx=max(maxx,j);//记录最大值
						a[i]+=(1ll<<(j-1));
					}
		cout<<maxx<<'\n';
	}
	return 0;
}
```

---

## 作者：Engulf (赞：0)

若 $a_{i - 1} > a_i$，显然让 $a_i$ 变大，令 $\Delta = a_{i - 1} - a_i$，对 $\Delta$ 进行二进制拆分，我们发现，一定存在一种方案使得 $a_i = a_{i - 1}$，只要把 $\Delta$ 拆分后为 $1$ 的位加上即可。所以 $j$ 的最大值即为所有 $\Delta$ 的最高为 $1$ 的位的位置，可以取对数来快速求出。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        int n;
        cin >> n;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        int ans = 0;
        for (int i = 1; i < n; i++)
            if (a[i - 1] > a[i]) {
                int d = log2(a[i - 1] - a[i]) + 1;
                ans = max(ans, d);
                a[i] = a[i - 1];
            }
        cout << ans << "\n";
    }
    return 0;
}
```

---

## 作者：_Revenge_ (赞：0)

### 题目简化和分析：    

- $a_{i}\ge a_{i-1}$ 已经满足直接跳过

- $a_{i}<a_{i-1}$ 我们就要将其的差进行二进制的分解，使得 $a_{i-1}=a_i$ 

我也不知道一开始我怎么想的还开了个  $f$  数组。   

$f_i=f_{i-1}+(2^{f_{i-1}}=i)$   这部妥妥的 MLE。    

所以还是暴力吧，毕竟二进制也快。   

### Solution:

**注意以下代码的 for 循环 k 的初始值，估计是太大会 UB?**   

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const int N=1e5+50;
const int M=1e5+50;
const int Mod=1e9+7;

inline ll read(){
    ll x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
ll t,n;
ll a[N];
int main()
{
	t=read();
	while(t--){
		n=read();
		for(int i=1;i<=n;++i){
			a[i]=read();	
		}
		ll ans=0;
		for(int i=2;i<=n;++i){
			if(a[i]>=a[i-1]) continue;
			for(ll k=31;k>=1;--k){
				if(a[i]+(1<<k-1)<=a[i-1])
				{
					a[i]+=(1<<k-1);
					ans=max(ans,k);
				}
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

## 作者：YuanZhizheng (赞：0)

中文题面有了，就不解释了。

在看题解之前，你需要知道，**二进制的数字可以组合成一切数字**！

我们来看看样例。

就比如样例1的1 7 6 5。我们现在访问到6，我们**要尽可能减少我们的增加量，这样使得后面的也增加得尽可能少，这样才能让秒数最小**。

于是，在1s以后我们可以让序列变成1 7 7 5。在样例的解释那里，题目说让序列变成1 7 7 8，实际上我认为变成1 7 7 7是更好的选择。

然后我们看，假如有存在a[i]-a[i+1]=8，我们最好的操作，就是在第4秒的时候，让第i+1位增加8，使得a[i]=a[i+1]，这样既满足题目要求，也不会给后面增加压力，假如我们让第i+1位增加1+2+4+8呢？如果第i+2位恰好是和a[i]相等，后面这样操作不就还需要增加秒数吗？

同时我们可以观察到，操作的时候增加的是2进制数，**2的0到n-1次幂相加，是永远比2的n次幂要小1的**。简单点来说，如果你和前面那个数相差了8，那么你**必须**要等到第4秒才能弥补差距，如果差了9，你也**必须**要等到第4秒，当然仅仅补一个8是达不到的，但是在这之前你可以补一个1上去，这样刚好相等，就做到了尽可能减少增加量又满足题目条件的目的。

**所以需要的最大秒数，实际上是取决于最大的差值，其他的差值可以在弥补完最大差值之前就补上，而最大差值在到达必须的秒数之前无论如何也是无法弥补的**，我们就可以遍历数组并且维护最大差值，最终计算秒数即可。

下面是AC代码。
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[100005];
ll sum[50];
int main()
{
    sum[0]=1;
    for(ll j=1;j<=40;j++)
    {
        sum[j]=(1LL<<j)+sum[j-1];
    }
    int t;
    scanf("%d",&t);
    while(t--)
    {
        ll maxx=0-1e10;
        ll ans=0;
        int n;
        scanf("%d",&n);
        for(int i=1; i<=n; i++)
        {
            scanf("%lld",&a[i]);
            maxx=max(maxx,a[i]);
            if(a[i]<maxx)
            {
                for(ll j=0; j<=40; j++)
                {
                    //cout<<((1LL)<<j)+a[i]<<endl;
                    if(sum[j]+a[i]>=maxx)
                    {
                        ans=max(ans,j+1);
                        break;
                    }
                }
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}

```

---

## 作者：gyh20 (赞：0)

一个常用的套路：由于每一次操作的个数没有限制，位置也没有限制，所以对每一位单独考虑求最大值即可。

对于每一个数，如果比上一个数小，贪心，使它和上一个数一样大，可以发现这样的操作次数更少。如果比上一个数大，就不管，因为让前面的数变大没有意义。

对于每一个位置，找到之前的最大值，如果该数大于最大值，则不管，否则计算差值的最高位，因为增加这么多要等到这个时间。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define int long long
inline int read(){
	re int t=0,f=0;re char v=getchar();
	while(v<'0')f|=(v=='-'),v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return f?-t:t;
} 
int n,m,t,a[100002],mx,ans;
inline int check(re int x){
	for(re int i=40;~i;--i){
		if(x&(1ll<<i))return i+1;
	}
}
signed main(){
	t=read();
	while(t--){
		n=read();
		for(re int i=1;i<=n;++i)a[i]=read()+1e9;
		mx=ans=0;
		for(re int i=1;i<=n;++i){
			if(a[i]>=mx)mx=a[i];
			else ans=max(ans,check(mx-a[i]));
		}
		printf("%lld\n",ans);
	}
}
```



---

## 作者：sto__Liyhzh__orz (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1338A)

题解区好多大佬啊，本蒟蒻瑟瑟发抖……

即： $b$ 加到 $a$ 上以后得到的序列单调不降，最小化 $b$ 的最大值。

显然 $a_{i-1}+b_{i-1} \le a_i+b_i$。

所以 $b_{i} \ge a_{i-1}-a_i+b_{i-1}$。

由于 $b_i\ge0$，所以得：$b_i =\max(0,a_{i-1}-a_i+b_{i-1})$。

---

