# [ABC319E] Bus Stops

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc319/tasks/abc319_e

高橋君ははじめ高橋君の家におり、これから青木君の家に遊びに行きます。

$ 2 $ 人の家の間には $ 1 $ から $ N $ までの番号がつけられた $ N $ 個のバス停があり、高橋君はそれらの間を下記の方法で移動できます。

- 高橋君の家からバス停 $ 1 $ まで $ X $ だけの時間をかけて徒歩で移動できます。
- 各 $ i\ =\ 1,\ 2,\ \ldots,\ N-1 $ について、バス停 $ i $ からは $ P_i $ の倍数である時刻それぞれにバスが出発し、そのバスに乗ることで $ T_i $ だけの時間をかけてバス停 $ (i+1) $ に移動できます。**ここで、$ 1\ \leq\ P_i\ \leq\ 8 $ が制約として保証されます。**
- バス停 $ N $ から青木君の家まで、$ Y $ だけの時間をかけて徒歩で移動できます。
 
各 $ i\ =\ 1,\ 2,\ \ldots,\ Q $ に対して下記のクエリを処理してください。

> 高橋君が高橋君の家を時刻 $ q_i $ に出発するときの、高橋君が青木君の家に到着する時刻としてあり得る最も早いものを求めよ。

なお、バスの出発時刻ちょうどにそのバスが出発するバス停に到着した場合であっても、そのバスに乗ることができます。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ X,\ Y\ \leq\ 10^9 $
- $ 1\ \leq\ P_i\ \leq\ 8 $
- $ 1\ \leq\ T_i\ \leq\ 10^9 $
- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ q_i\ \leq\ 10^9 $
- 入力はすべて整数
 
### Sample Explanation 1

$ 1 $ 番目のクエリについて、高橋君は下記の通りに移動を行って、時刻 $ 34 $ に青木君の家に到着することができます。 - 時刻 $ 13 $ に高橋君の家を出発する。 - 高橋君の家から徒歩で移動し、時刻 $ 15 $ にバス停 $ 1 $ に到着する。 - 時刻 $ 15 $ にバス停 $ 1 $ を出発するバスに乗り、時刻 $ 19 $ にバス停 $ 2 $ に到着する。 - 時刻 $ 24 $ にバス停 $ 2 $ を出発するバスに乗り、時刻 $ 30 $ にバス停 $ 3 $ に到着する。 - 時刻 $ 30 $ にバス停 $ 3 $ を出発するバスに乗り、時刻 $ 31 $ にバス停 $ 4 $ に到着する。 - バス停 $ 4 $ から徒歩で移動し、時刻 $ 34 $ に青木君の家に到着する。 $ 2 $ 番目のクエリについて、高橋君は下記の通りに移動を行って、時刻 $ 22 $ に青木君の家に到着することができます。 - 時刻 $ 0 $ に高橋君の家を出発する。 - 高橋君の家から徒歩で移動し、時刻 $ 2 $ にバス停 $ 1 $ に到着する。 - 時刻 $ 5 $ にバス停 $ 1 $ を出発するバスに乗り、時刻 $ 9 $ にバス停 $ 2 $ に到着する。 - 時刻 $ 12 $ にバス停 $ 2 $ を出発するバスに乗り、時刻 $ 18 $ にバス停 $ 3 $ に到着する。 - 時刻 $ 18 $ にバス停 $ 3 $ を出発するバスに乗り、時刻 $ 19 $ にバス停 $ 4 $ に到着する。 - バス停 $ 4 $ から徒歩で移動し、時刻 $ 22 $ に青木君の家に到着する。

## 样例 #1

### 输入

```
4 2 3
5 4
6 6
3 1
7
13
0
710511029
136397527
763027379
644706927
447672230```

### 输出

```
34
22
710511052
136397548
763027402
644706946
447672250```

# 题解

## 作者：FFTotoro (赞：9)

因为公交车到达的时间为各个 $P_i$ 的倍数，所以我们不用考虑具体的时间，只用考虑时间对各个 $P_i$ 取模的值。可以发现，实际上只要考虑时间对 $\operatorname{lcm}_{i=1}^NP_i$ 取模的值。

为方便处理，这里令 $L=\operatorname{lcm}\{1,2,3,4,5,6,7,8\}=840$，先预处理出发时间为 $0,1,\ldots,839$ 的答案 $r_0,r_1,\ldots,r_{839}$，对于询问的具体时间 $x$，答案即为 $r_{x\bmod 840}+840\left\lfloor\frac{x}{840}\right\rfloor$。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int,int> pii;
int r[840];
int f(int n,int x){
  if(n%x)return (n/x+1)*x;
  else return n;
} // 找大于等于 n 且是 x 的倍数的最小整数
main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int n,x,y; cin>>n>>x>>y;
  vector<pii> a(n-1);
  for(auto &[p,t]:a)cin>>p>>t;
  for(int i=0;i<840;i++){
    r[i]=i+x;
    for(auto [p,t]:a)r[i]=f(r[i],p)+t;
    r[i]+=y;
  } // 模拟答案
  int q; cin>>q;
  while(q--){
    int b; cin>>b;
    cout<<r[b%840]+b/840*840<<'\n';
  } // 处理询问
  return 0;
}
```

---

## 作者：Fire_flame (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc319_e)

这一场上大分（1338 升到 1429），喜。

## $\mathtt{Solution}$

首先发现不可以直接做，超时。

但是这个问题目前没有一种通用的数据结构（例如线段树）去解决。

所以我们考虑预处理。

根据数学直觉，我们发现 $\operatorname{lcm}\{1,2\dots,8\}=840$，也就是说，至多每 $840$ 分钟会有一次周期。

那么就好做了，预处理出初始时间为 $0\sim 839$ 的答案即可。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + (ch - '0');ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 2e5 + 5;
int n, m, k, q, a[MAXN], b[MAXN], ans[MAXN];
signed main(){
	n = read(), m = read(), k = read();
	for(int i = 1;i < n;i ++)a[i] = read(), b[i] = read();
	for(int i = 0;i < 840;i ++){//预处理
		int nt = i + m;
		ans[i] = m;//起点到高桥的家花费的时间
		for(int j = 1;j < n;j ++){
			while(nt % a[j] != 0)nt ++, ans[i] ++;//需要等待巴士
			nt += b[j], ans[i] += b[j];//前往下一个站
		}
		ans[i] += k;//终点到青木的家花费的时间
	}
	q = read();
	while(q --){
		int x = read();
		printf("%lld\n", x + ans[x % 840]);
	}
	return 0;
}

```


---

## 作者：Genius_Star (赞：3)

### 题意：

有 $n-1$ 个公交站台，第 $i$ 个公交站台只会在时间为 $p_i$ 的倍数时候发车，消耗 $t_i$ 时间到 $i+1$ 号点，到达 $1$ 号公交站台要用 $x$ 的时间，从 $n-1$ 号公交站台到终点需要 $y$ 的时间。

现在给你 $q$ 次询问，第 $i$ 次询问给出一个整数 $k$，求出如果当前时间为 $k$，达到终点的最短时间是多少？

### 思路：

直接暴力做的话是 $O(n \times q)$ 的，肯定过不去，所以要考虑优化。

我们注意到 $p_i \le 8$，这说明什么？其一，说明有很多的公交站台的 $p_i$ 是重复的，其次，我们可以得到 $\operatorname{lcm}(1,2,3,4,5,6,7,8)$ 的状态。

举个例子，$p_1=5,p_2=10$，那么有着有着 $\operatorname{lcm}(5,10)$ 的状态。即 $10$，表示分别对于两种 $p$ 取模的可能方案，就像中国剩余定理两个同于方程式合并一样。

$\operatorname{lcm}(1,2,3,4,5,6,7,8)$ 的值手推一下，就是 $2520$ 差不多，也就是说，对于所有 $n$ 个公交站取模的总不同方案（注意是方案，不是取模后的结果）只有 $2520$ 个方案。

所以，我们可以先预处理出每一个状态到达终点的最短距离，查询的时候我们直接输出 $ans_{k \bmod 2520}+x+y$ 即可。

现在想想怎么预处理 $ans$ 数组，其实很简单，对于每一个状态，一次遍历每一个公交站台，则在原来的基础上我们还需要增加的时间是：

$$p_j-\operatorname{F}((ans_i+i)\bmod p_j,j)+t_j$$

$$\operatorname{F}(x,j)=\begin{cases}p_j&x=0\\x& x \ne 0 \end{cases}$$

其中 $i$ 为我们的状态，$j$ 为计算到了第 $j$ 个公交站台。

其中 $ans_i$ 当前就相当于计算到了到达 $j-1$ 号公交站台的最小时间，然后我们对于当前状态下除余 $p_j$ 的取值就是 $i \bmod a_j$，两者相加就是当前的一个时间取模 $p_j$ 的值。

最后用 $p_j$ 减去当前的时间除余 $p_j$ 的值，就是在当前状态，需要等待这一趟公交车的时间。

这里解释一下 $\operatorname{F}$ 的定义，其实就是如果当前时间被整除了，那么自然不需要等待了，如果直接写 $\bmod$ 的话得到的结果是 $0$ 就会错误。

这样我们就用 $O(n)$ 的时间复杂度预处理了这个问题（~~常熟略微大一点点……~~），查询是 $O(1)$ 的。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=100100;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,x,y,q,k;
ll p[N],t[N],ans[N];
ll F(ll x,ll j){
	return (x==0?p[j]:x);
}
int main(){
	n=read(),x=read(),y=read();
	for(int i=1;i<n;i++){
		p[i]=read();
		t[i]=read();
	}
	for(int i=0;i<2520;i++)
	  for(int j=1;j<n;j++)
		ans[i]+=(p[j]-F((i+ans[i])%p[j],j))+t[j];
	q=read();
	while(q--){
		k=read();
		k+=x;
		k+=ans[k%2520];
		k+=y;
		write(k);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：joe_zxq (赞：2)

# 思路

不难发现，每 $\operatorname{lcm}(p_i)$ 个单位时间是一周期，所以只需预处理出 $1 \sim \operatorname{lcm}(p_i)$ 的答案即可。

时间复杂度：$\operatorname{lcm}(p_i) \times N$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t[214514],p[214514];
long long ans[3000];
long long n,x,y; 
long long calc(long long s){
	long long time=s;
	for(long long i=1;i<n;i++){
		if(time%p[i])time+=p[i]-time%p[i];
        time+=t[i];
	}
	return time;
}
void solve(){
	scanf("%lld %lld %lld",&n,&x,&y);
	for(long long i=1;i<n;i++)scanf("%lld %lld",&p[i],&t[i]);
	long long l=p[1];
	for(long long i=2;i<n;i++)l=l*p[i]/__gcd(l,p[i]);
	for(long long i=0;i<=l+2;i++){
		ans[i]=calc(i);
	}
	long long q; scanf("%lld",&q);
	while(q--){
		long long s; scanf("%lld",&s);
		printf("%lld\n",ans[(s+x)%l]+y+(s+x-(s+x)%l));
	}
}
int main(){
	long long tc=1;
    while(tc--)solve();
    return 0;
}
```

---

## 作者：WaterSun (赞：1)

# 思路

首先不难发现，在一个公交站 $i$，需要等待的时间与 $tim \bmod p_i$ 有关。（其中 $tim$ 为当前时间）

那么，我们不妨定义 $l = \operatorname{lcm}(p_i)$，那么，如果我们将起始时间分别为 $0 \sim (l - 1)$ 的这部分处理出来，记作 $ans_i$。

那么，对于任意起始时间 $x$，都有最终的时间为：

$$
ans_{x \bmod l} + x - x \bmod l
$$

由于 $l$ 的值域很小（最大也只有 $840$），所以直接暴力做即可。

时间复杂度 $\Theta(l \times n)$。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 1e5 + 10;
int n,A,B,q,l = 1;
int arr[N],brr[N],ans[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline int gcd(int a,int b){
	if (!b) return a;
	return gcd(b,a % b);
}

inline int f(int x){
	int tim = A + x;
	for (re int i = 1;i < n;i++){
		if (tim % arr[i] == 0) tim += brr[i];
		else tim += arr[i] - (tim % arr[i]) + brr[i];
	}
	return tim + B;
}

signed main(){
	n = read();
	A = read();
	B = read();
	for (re int i = 1;i < n;i++){
		arr[i] = read();
		brr[i] = read();
		l = l * arr[i] / gcd(l,arr[i]);
	}
	for (re int i = 0;i < l;i++) ans[i] = f(i);
	q = read();
	while (q--){
		int x;
		x = read();
		printf("%lld\n",x - x % l + ans[x % l]);
	}
	return 0;
}
```

---

## 作者：DerrickLo (赞：1)

注意到如果把开始时间对 $p_1,p_2,\ldots p_n$ 的最小公倍数进行取模，需要的时间还是一样的，因为所有的公交车要等待的时间都不变。

所以我们可以预处理出从 $0$ 到 $p_1,p_2,\ldots p_n$ 的最小公倍数之间的所有数，然后暴力计算出所需时间，最后把答案处理一下即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x,y,t[100005],p[100005],q,mx=1,ans[1005],xx;
signed main(){
	cin>>n>>x>>y;
	for(int i=1;i<n;i++)cin>>p[i]>>t[i],mx=mx*p[i]/__gcd(mx,p[i]);
	for(int i=0;i<=mx;i++){
		ans[i]=i+x;
		for(int j=1;j<n;j++){
			if(ans[i]%p[j]!=0)ans[i]+=p[j]-ans[i]%p[j];
			ans[i]+=t[j];
		}
		ans[i]+=y;
	}
	cin>>q;
	while(q--){
		cin>>xx;
		cout<<ans[xx%mx]-xx%mx+xx<<"\n";//把所需的时间减去取模后的时间再加上原先的时间
	}
	return 0;
}
```

---

## 作者：Mortidesperatslav (赞：1)

这题直接枚举肯定超时，我们注意到 $1 \leq P_i \leq 8$，那么我们只要预处理出除以 $\operatorname{lcm}(1,2,3,4,5,6,7,8)=840$ 的每个余数，计算出需要多少时间走完，就可以 $O(1)$ 查询了。

时间复杂度 $O(Q)$，可以通过。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x,y,t[100005],p[100005],f[841],q,qu; 
signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>x>>y;
	for(int i=1;i<n;i++)cin>>p[i]>>t[i];
	for(int u=0;u<840;u++){//预处理
		f[u]=u;
		for(int i=1;i<n;i++){
			if(f[u]%p[i]!=0)f[u]=f[u]-f[u]%p[i]+p[i];//不是Pi的倍数，等待
			f[u]+=t[i];//走到下一站
			//if(u==15)cerr<<"::"<<f[u]<<"\n";
		}
	}
	cin>>q;
	while(q--){
		cin>>qu;
		cout<<qu+x+y+f[(qu+x)%840]-((qu+x)%840)<<"\n";//注意走到第一站需要x时间
	}
}
```

---

## 作者：_zzzzzzy_ (赞：1)

# 思路

发现这些汽车都是 $\operatorname{lcm}(p_1,p_2\dots,p_n)$，然后因为 $p$ 是小于等于 $8$ 的，那么我们就可以先用程序算出来小于等于 $8$ 的 $\operatorname{lcm}$，发现是 $840$。

然后因为是很小的麻，所以就可以直接先暴力处理出来出发时间为 $0\sim 839$ 的答案，然后最后 $O(1)$ 输出就好了。

# 代码

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define per(i, l, r) for (int i = (r); i >= (l); i--)
#define Debug(...) fprintf(stderr, __VA_VRGS__)
using namespace std;
using i64 = long long;
const int maxn = 1000000;
i64 p[maxn], t[maxn];
i64 a[maxn];
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    
    int n, x, y;
    int m = 840;
    cin >> n >> x >> y;
    rep(i, 1, n - 1) {
        cin >> p[i] >> t[i];
    }
    rep(i, 0, m - 1) {
        a[i] = i;
        a[i] += x;
        rep(j, 1, n - 1){
            a[i] += (p[j] - a[i] % p[j]) % p[j];
            a[i] += t[j];
        }
        a[i] += y;
    }
    int Q;
    cin >> Q;
    while(Q--) {
        i64 x;
        cin >> x;
        cout << (x / m) * m + a[x % m] << "\n";
    }
    return 0;
}
```

---

## 作者：TG_Space_Station (赞：1)

# 翻译（人物已篡改）
TG_Space_Station 从家出发，步行 $x$ 分钟到达巴士第一站，坐巴士到达第 $n$ 站，再步行 $y$ 分钟到达朋友家。  
这些巴士很特别，每个只开一站。  

设当前时间为 $time$。  
对于车站 $i$ 满足 $1 \le i \le n-1$，有两个参数 $p_i,a_i$。  
$p_i$ 表示对于每个 $time$ 满足 $p_i \mid time$，都会发车。  
$t_i$ 表示这辆巴士开到下一站需要 $t_i$ 分钟。注意，到了下一站就会被赶下车。

有 $Q$ 个询问，每个询问会给出一个数：$q_i$。你需要回答：TG_Space_Station 从时间 $q_i$ 出发，最早会在什么时间到达朋友家呢？  
![](https://cdn.luogu.com.cn/upload/image_hosting/vtk3r2s8.png)
# 思路
仔细思考会发现（也可以说是据小学数学可知）：整个线路以 $x$（$x = \operatorname{lcm}_{i=1}^{n-1}p_i$） 分钟为一周期。  
由于：$1 \le p_i \le 8$，则选取第一个周期算出其中所有时间为起始时间的答案，最后对于每个询问 $O(1)$ 查询。  
最终时间复杂度：$O(x \times n + q)$。  
具体见代码。
# [$AC code$](https://atcoder.jp/contests/abc319/submissions/45423459)
```
#include <bits/stdc++.h>
using namespace std;
const long long N = 1e5 + 5;

long long q, a;
long long ans[N];
long long TGpanda;//LCM
long long n, x, y;
long long p[N], t[N];

long long get_ans(long long m)
{
	long long i, tmp = m + x;
	
	for(i = 1; i < n; i++)
		tmp = ceil(tmp * 1.0 / p[i]) * p[i] + t[i];
	
	return tmp + y;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	long long i;
	TGpanda = 1;
	cin >> n >> x >> y;
	
	for(i = 1; i < n; i++)
	{
		cin >> p[i] >> t[i];
		TGpanda = TGpanda * p[i] / __gcd(p[i], TGpanda);//lcm(a,b) * gcd(a,b) = a * b
	}
	
	for(i = 0; i < TGpanda; i++)
		ans[i] = get_ans(i);
	
	cin >> q;
	
	for(i = 1; i <= q; i++)
	{
		cin >> a;
		cout << a - a % TGpanda + ans[a % TGpanda] << "\n";
	}
	return 0;
}
```
# 求过QwQ

---

## 作者：ldj2006 (赞：0)

# [ABC319E] Bus Stops 题解

## 题意简介

&emsp;&emsp;给定 $n$ 个公交站。对于第 $i$ 个公交站，在时刻 $p_i \times k,k \in \mathbb{N}$ 有一辆公交车出发，在经过 $t_i$ 的时间后，到达第 $i+1$ 个公交站。

&emsp;&emsp;在走到第一个公交车之前需要走 $X$ 时刻，做到最后一个公交站之后下车以后还需要走 $Y$ 时刻。

&emsp;&emsp;约束：$1 \le p_i \le 8$

&emsp;&emsp;给定 $m$ 次询问，每次询问给定出发时间 $q_i$，问所需要花费的最小时间。就是 $q_i + X + \text{坐公交车花费时间} + Y$。

## 题目分析

&emsp;&emsp;考虑到 $1 \le p_i \le 8$，这里有个小技巧：我们考虑（1~8）最小公倍数 840 时间范围内的时刻就够了。

&emsp;&emsp;如果 $p_i$ 中出现了全部 1~8，那么经过 840 时刻之后，所有车站发车的“小周期”就可以“耦合”成大周期。如果不全部出现 1~8，那么 840 一定包含了其大周期。

&emsp;&emsp;我们考虑 $f_i$ 表示在第 $i$ 个时刻到达第 1 个车站情况下，坐到最后一个车站所需要花费的时间。我们贪心地一站一站往前坐车即可。

&emsp;&emsp;我们对于 840 个时刻全部预处理一遍，时间复杂度 $O(\text{lcm}(p_i)\times n)$。对于每个询问，我们可以除掉周期，用余数代入 $f_i$，$O(1)$ 地得到答案，时间复杂度 $O(m)$。总时间复杂度 $O(\text{lcm}(p_i)\times n + m)$。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 1e5 + 5;
const LL P = 840;

LL n,p[N],t[N],x,y;
LL f[P+5];

void init()
{
	for(int i = 0;i < P;i++)
	{
		f[i] = i;
		for(int j = 1;j <= n-1;j++)
		{
			if(f[i]%p[j] == 0)
			{
				f[i] += t[j];
			}
			else
			{
				f[i] = t[j] + (((f[i]-1)/p[j])+1)*p[j];
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> x >> y;
	for(int i = 1;i <= n-1;i++)
	{
		cin >> p[i] >> t[i];
	}
	init();
	LL ques = 0;
	cin >> ques;
	while(ques--)
	{
		LL q;
		cin >> q;
		q += x;
		cout << (LL)(q/P*P + f[q%P] + y) << "\n";
	}
	return 0;
}
```

---

## 作者：incra (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc319_e)
### 题解
注意到 $P_i\le 8$，可以得到答案是有循环节的，长度为 $\displaystyle\operatorname{lcm}_{i=1}^{8}=840$，这样就很好做了，直接枚举 $0\sim839$，求出每一个答案，加上前面的时间，这题就做完了。

以后一定要留心观察数据范围，这可能是突破口。
### 代码
```
#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,-1,0,0},dy[] = {0,0,1,-1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) exit (0);
	char ch = cin.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = cin.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = cin.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
const int N = 100010;
int n,q,x,y;
int p[N],t[N];
LL ans[840];
LL get (LL s) {
	for (int i = 1;i <= n - 1;i++) s = s + (p[i] - s % p[i]) % p[i] + t[i];
	return s + y;
}
int main () {
	cin >> n >> x >> y;
	for (int i = 1;i <= n - 1;i++) cin >> p[i] >> t[i];
	p[n] = 1e9;
	for (int i = 0;i < 840;i++) ans[i] = get (i);
	cin >> q;
	while (q--) {
		LL u;
		cin >> u;
		cout << (u + x) / 840 * 840 + ans[(u + x) % 840] << endl;
	}
	return 0;
}
```

---

