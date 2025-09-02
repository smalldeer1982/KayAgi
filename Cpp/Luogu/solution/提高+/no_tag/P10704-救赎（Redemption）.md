# 救赎（Redemption）

## 题目背景

>$$主啊，$$
>
>$$这个人也是我们要拯救的吗\dots$$
>
>$$愿我的弹雨能熄灭你们的痛苦\dots$$
>
>$$如果您见到一位散发着不祥气息的天使，$$
>
>$$请替我转告她：$$
>
>$$我从来没有忘记过她\dots$$

## 题目描述

给出 $n,m$ 和 $n$ 个整数 $a_i$（$1\le i\le n$）。

求：

$$ \sum\limits_{i=1}^{n} \sum\limits_{j=1}^{n}\left \lfloor \frac{m}{a_ia_j}  \right \rfloor$$

输出答案对 $998244353$ 取模的结果。

## 说明/提示

#### 【样例解释】

样例一中的贡献如下：

$(a_1,a_1):\left \lfloor \frac{30}{2\times 2} \right \rfloor =7$。

$(a_1,a_2),(a_2,a_1):\left \lfloor \frac{30}{2\times 2} \right \rfloor \times 2=14$。

$(a_1,a_3),(a_3,a_1):\left \lfloor \frac{30}{2\times 8} \right \rfloor \times 2=2$。

$(a_1,a_4),(a_4,a_1):\left \lfloor \frac{30}{2\times 4} \right \rfloor \times 2=6$。

$(a_1,a_5),(a_5,a_1):\left \lfloor \frac{30}{2\times 2} \right \rfloor \times 2=14$。

$(a_2,a_2):\left \lfloor \frac{30}{2\times 2} \right \rfloor =7$。

$(a_2,a_3),(a_3,a_2):\left \lfloor \frac{30}{2\times 8} \right \rfloor \times 2=2$。

$(a_2,a_4),(a_4,a_2):\left \lfloor \frac{30}{2\times 4} \right \rfloor \times 2=6$。

$(a_2,a_5),(a_5,a_2):\left \lfloor \frac{30}{2\times 2} \right \rfloor \times 2=14$。

$(a_3,a_5),(a_5,a_3):\left \lfloor \frac{30}{2\times 8} \right \rfloor \times 2=2$。

$(a_4,a_4):\left \lfloor \frac{30}{4\times 4} \right \rfloor=1$。

$(a_4,a_5),(a_5,a_4):\left \lfloor \frac{30}{2\times 4} \right \rfloor \times 2=6$。

$(a_5,a_5):\left \lfloor \frac{30}{2\times 2} \right \rfloor=7$。

$7+14+2+6+14+7+2+6+14+2+1+6+7=88$。

#### 【数据范围】

| subtask 编号 | $n$ | $m$ | $a_i$ | 分值 | 特殊性质 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $0$ | $\le 10^2$ | $\le 10^{6}$ | $\le 10^5$ | $10$ | $-$ |
| $1$ | $\le 10^4$ | $\le 10^{10}$ | $\le 10^9$ | $10$ | $-$ |
| $2$ | $\le 10^6$ | $\le 10^{10}$ | $\le 10^4$ | $10$ | $-$ |
| $3$ | $\le 10^6$ | $\le 10^8$ | $\le 10^9$ | $20$ | $-$ |
| $4$ | $\le 10^6$ | $\le 10^{10}$ | $\le 10^9$ | $20$ | $A$ |
| $5$ | $\le 10^6$ | $\le 10^{10}$ | $\le 10^9$ | $30$ | $-$ |

特殊性质 $A$：$\sum\limits_{i=1}^{n}a_i\le10^7$。

对于 $100\%$ 的数据，$1\le n\le10^6$，$1\le a_i\le 10^9$，$\sum\limits_{i=1}^{n}a_i\le10^9$，$1\le m \le10^{10}$。

**特别提醒：本题使用 subtask 捆绑测试，只有通过一个子任务的全部测试点才能获得此子任务的分数。**

## 样例 #1

### 输入

```
5 30
2 2 8 4 2 ```

### 输出

```
88```

## 样例 #2

### 输入

```
10 5035239199
4853 53137 86933 4465 13588 11899 49877 16317 43326 52183 ```

### 输出

```
2715```

# 题解

## 作者：Kreado (赞：17)

[题目传送门](https://www.luogu.com.cn/problem/P10704)。

## 思路

容易得到 $\lfloor\frac{m}{i}\rfloor$ 只有 $2\sqrt m$ 种取值，考虑对 $m$ 数论分块，对于每个区间 $\forall i,j\in[l,r]$，均有 $\lfloor\frac{m}{i}\rfloor=\lfloor\frac{m}{j}\rfloor$，令 $f(r)=\sum_{i=1}^n \sum_{j=1}^n [a_ia_j\le r]$，$b_i=\sum_{j=1}^n [a_j=i]$，那么我们有 

$$f(r)=2\sum_{i=1}^{\lfloor\sqrt{r}\rfloor} b_i\left( \sum_{j=1}^n [a_j\le \lfloor\frac{r}{i}\rfloor]-\sum_{j=1}^n [a_j\le i] \right)+\sum_{i=1}^{\lfloor\sqrt{r}\rfloor} b_i^2$$

由于传入函数 $f$ 的参数均是 $m$ 的整除点值，而 $m$ 的整除点值只有 $2\sqrt m$ 种，括号内的式子我们就可以在 $O(\sqrt m\log n)$ 的时间复杂度内求出。

那么 $f(r)$ 就能在 $O(\sqrt r)$ 的时间复杂度内求出。

最终答案就是：

$$\sum_{l,r}(f(r)-f(l-1))\times \biggl\lfloor\dfrac{m}{l}\biggl\rfloor$$

时间复杂度 $O(m^{3/4}+\sqrt m\log n)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn=1e6+7;
const int Mod=998244353;
ll n,m;
ll a[Maxn]; 
ll sq;
ll ans;
ll sq1[Maxn],sq2[Maxn];
ll bb[Maxn];

inline ll Gt(ll x){
	if(x==0) return 0;
	if(x<=sq) return sq1[x];
	else return sq2[m/x];
}
map<ll,ll>S;
inline ll KP(ll x){
	if(S.count(x)) return S[x];
	ll res=0;
	
	ll pp=__builtin_sqrt(x);
	for(ll i=1;i<=pp;i++)
		res=(res+bb[i]*(Gt(x/i)-Gt(i)))%Mod;
	res=res*2%Mod;
	for(ll i=1;i<=pp;i++) res=(res+bb[i]*bb[i])%Mod;
	return S[x]=res;
}


int main(){
	scanf("%lld%lld",&n,&m);
	sq=sqrt(m);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		if(a[i]<=sq) bb[a[i]]++;
	}
	sort(a+1,a+n+1);
	
	for(ll l=1,r;l<=m;l=r+1){
		r=m/(m/l);
		int res=upper_bound(a+1,a+n+1,r)-a-1;
		if(r<=sq) sq1[r]=res;
		else sq2[m/r]=res;
	}
	for(ll l=1,r;l<=m;l=r+1){
		r=m/(m/l);
		ans=(ans+(KP(r)-KP(l-1))%Mod*(m/l)%Mod)%Mod;
	}
	ans=(ans+Mod)%Mod;
	printf("%lld",ans);
	
	return 0;
}

```

---

## 作者：Naszt (赞：11)

和官方题解不同的是我的方法不用**阈值分块**，  
其实仅使用**整除分块**即可 AC。

## 推公式

$$ans=\sum_{i=1}^n\sum_{j=1}^n\left\lfloor\frac{m}{a_ia_j}\right\rfloor=\sum_{i=1}^n\sum_{j=1}^n\left\lfloor\frac{\left\lfloor\frac{m}{a_i}\right\rfloor}{a_j}\right\rfloor$$

设 $f(x)=\sum_{j=1}^n\left\lfloor\frac{x}{a_j}\right\rfloor$

有 $ans=\sum_{i=1}^nf\left(\left\lfloor\frac{m}{a_i}\right\rfloor\right)$

## 算法/工程

考虑到 $f(x)$ 递推之类的关系过于复杂，  
我们先优化 $f(x)$ 的计算。

### 优化 1-1

考虑枚举 $\left\lfloor\frac{x}{a_j}\right\rfloor$ 的结果，  
可以分出 $\le2\sqrt x$ 个块 $[l_i,r_i]$。

$$f(x)=\sum_{i=1}\left(\left\lfloor\frac{x}{r_i}\right\rfloor\sum_{j=1}^n[l_i\le a_j\le r_i]\right)$$

我们对 $a$ 数组进行排序，  
再用二分可以 $\Theta(\log n)$ 快速求出满足 $l_i\le a_j\le r_i$ 的个数。

### 优化 1-2

这样还是不够快，  
究其原因是有时没有一个 $a_j$ 满足 $l_i\le a_j\le r_i$，  
即许多块是空的！

那么设 $j$ 为满足 $l_i\le a_j\le r_i$ 时最大的 $j$，  
则下一个非空块 $l_{next}\le\left\lfloor\frac{x}{a_{j+1}}\right\rfloor$,  
代码中可以直接取等。  

### 对外层循环的优化

因为外层循环和内层循环几乎是一样的向下取整，  
所以也可以进行分块（优化 2-1）和跳过空的块（优化 2-2）。

### 时间复杂度

理论上来说这四个应使时间复杂度越来越优，  
不过加了优化 1-2 反而大幅减慢速度：

| 记录 | 时间 | 优化 |
| :----------: | :----------: | :----------: |
| [link](https://www.luogu.com.cn/record/164371772) | $4.86s$ | 1-1 |
| [link](https://www.luogu.com.cn/record/164351799) | $5.99s$ | 1-1 加 1-2 |
| [link](https://www.luogu.com.cn/record/164358621) | $4.86s$ | 1-1 加 2-1 加 2-2 |
| [link](https://www.luogu.com.cn/record/164358530) | $5.96s$ | 1-1 加 1-2 加 2-1 加 2-2 |


知道原因的大佬希望可以帮忙解释一下，感谢。  
~~我觉得应该还是评测机的锅。~~

时间复杂度实在不好算，  
最坏情况是 $\Theta(m\log n)$。  
优化 1-2 和 2-2 可以加速最坏情况。

我个人感觉更可能是数据点的问题，或许可以加强一下。

## 代码

非常好评测机，使我常数旋转：[评测机不稳定？运行时间大不同！](https://www.luogu.com.cn/discuss/845726)  
这里给出我的可读性最好的代码（只有优化 1-1）：  

```cpp
#include<bits/stdc++.h>
#define mod 998244353
int64_t n,m,a[1000100],ans;
int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0), std::cout.tie(0);
	
	std::cin>>n>>m;
	for(int i=0;i!=n;i++)std::cin>>a[i];
	std::sort(a,a+n);
	
	for(int i=0;i<n;){
		int64_t x=m/a[i],ians=0;
		for(int64_t l=1,r,*L=a,*R;l<=x;l=r+1,L=R){
			r=x/(x/l),R=std::upper_bound(L,a+n,r);
			ians+=(x/l)*(R-L);
		}
		do (ans+=ians)%=mod,++i;
		while(i<n&&m/a[i]==m/a[i-1]);
	}
	
	std::cout<<ans;
	return 0;
}
```


## 后话/闲话

我是隔壁松未的蒟蒻，太久没碰键盘了，代码炸了好几次……  
虽然说感觉数据点很奇怪，不过这道题目做的真的是太爽啦！  
~~还和**能天使**梦幻联动啦！~~

---

## 作者：yywlp (赞：8)

## 题解

一句话总结：阈值分块，整除分块。

观察数据范围发现 $\sum\limits_{i=1}^{n}a_i$ 只有 $10^9$，我们设 $A=\sum\limits_{i=1}^{n}a_i$，在 $B$ 把数分为两块，$B_1\le B,B_2>B$。

### Part 1：$B_1\times B_1$

开个桶存一下每个数有多少个，$B^2$ 枚举任意两个数算方案数即可。时间复杂度 $\Theta(B^2)$。

### Part 2：$B_2\times B_2$

发现 $B_2$ 最多只有 $\frac{A}{B}$ 个数，又发现答案范围为：$\frac{m}{B^2}$。

那么我们枚举答案，再枚举 $B_2$ 中的数，根据**整除分块**的知识即可求出另一个数的范围。

另一个数最大是 $\frac{m}{B}$，前缀和存一下就行。

时间复杂度 $\Theta(\frac{A\times m}{B^3})$。

### Part 3：$B_1\times B_2$

这里我们把 $B_1$ 中的数按 $Q$ 分为 $Q_1\le Q,Q_2>Q$。

对于 $Q_1,B_2$，暴力枚举 $Q_1$ 中数的大小，再枚举 $B_2$ 中的每一个数，通过桶计算方案数即可，不过不要忘记对贡献 $\times 2$，因为每对数正反都会贡献一遍。时间复杂度 $\Theta(\frac{A\times Q}{B})$。

对于 $Q_2,B_2$，会发现答案范围为：$\frac{m}{Q\times B}$
依然枚举答案，枚举 $B_2$ 中的数，根据整除分块算出范围，前缀和算方案数即可，这里和上一种一样，贡献也需要 $\times 2$。时间复杂度 $\Theta(\frac{A\times m}{Q\times B^2})$。

在通过整除分块算边界时有些细节需要稍微注意。

整体下来复杂度是 $\Theta(B^2+\frac{A\times m}{B^3}+\frac{A\times Q}{B}+\frac{A\times m}{Q\times B^2})$。稍微想一下发现 $B=10^4,Q=10^3$ 的时候算出来大概是 $3\times 10^8$，可以通过。

$B$ 和 $Q$ 再稍微调一下可以使每个部分的复杂度都相等，总体会小一点点，不过没有太大必要。

验题人对于计算 $B_1,B_2$ 有一个新的想法：不难发现 $B_2$ 中其实只有 $45000$ 左右个不同的数，那么暴力枚举大概在 $4\times 10^8$，一个是数据不是很极端，再一个是有 $4$s，卡卡常差不多能够通过。

## Code 1

出题人的做法。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define mk(x,y) make_pair(x,y)
const int M=1e6+10,N=1e4+10,mod=998244353;
int n,m,gm;
int a[M];
int t[M];
int s[M];
vector<int>b;
int ans=0;
pii ct[M];
int read() {
	int x = 0, w = 1;
	char ch = 0;
	while (ch < '0' || ch > '9') { 
		if (ch == '-') w = -1;    
		ch = getchar();       
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + (ch - '0');
		ch = getchar();
	}
	return x * w;
}
signed main(){
	freopen("temp.in","r",stdin);
	freopen("temp.out","w",stdout);
	cin>>n>>m;
	gm=ceil(sqrt(m));
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(a[i]<=1e6)t[a[i]]++,s[a[i]]++;
		if(a[i]>1e4)b.push_back(a[i]);
	}
	sort(a+1,a+n+1);
	for(int i=1;i<M;i++)s[i]+=s[i-1];
	for(int i=1;i<=1e4;i++){
		for(int j=1;j<=1e4;j++){
			ans=(ans+m/(i*j)*t[i]%mod*t[j]%mod)%mod;
		}
	}
	int l=1,r;
	while(l<=m){
		r=m/(m/l);
		if(m/l<=gm)ct[m/l]=mk(l,r);
		l=r+1;
	}
	for(int i=1;i<=m/1e8;i++){
		for(int j:b){
			int l=ct[i].first,r=ct[i].second;
			l=ceil(1.0*l/j),r=r/j;
			if(l>r||r<=1e4)continue;
			l=max(l,(int)1e4+1);
			int nex=s[r]-s[l-1];
			ans+=nex*i;
			if(ans>mod)ans%=mod;
		}
	}
	for(int i=1;i<=1e3;i++){
		for(int j:b){
			ans+=m/(i*j)*t[i]*2;
			if(ans>mod)ans%=mod;
		}
	}
	for(int i=1;i<=m/1e7;i++){
		for(int j:b){
			int l=ct[i].first,r=ct[i].second;
			l=ceil(1.0*l/j),r=r/j;
			if(l>r||r<=1e3||l>1e4)continue;
			if(r>1e4)r=1e4;
			if(l<=1e3)l=1e3+1;
			int nex=s[r]-s[l-1];
			ans+=nex*i*2;
			if(ans>mod)ans%=mod;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

## Code 2

验题人的做法。

```cpp
#include <bits/stdc++.h>
typedef long long LL;
const int M = 1e6 + 10, B = 1500;
const int mod = 998244353;
const LL Max_m = 1e10;

LL m, ans;
int n, a[M], pre[Max_m / B + 10];
std::vector<std::pair<int, int> > S, S0, S1;
inline void Init() {
    std::map<int, int> mp;
    for (int i = 1; i <= n; i++)
        if (a[i] <= B) ++mp[a[i]];
    for (auto x : mp) S0.emplace_back(x);
    std::sort(S0.begin(), S0.end());
    for (int i = 1; i <= n; i++)
        if (a[i] > B) ++mp[a[i]];
    for (auto x : mp) S.emplace_back(x);
    std::sort(S.begin(), S.end());
    mp.clear();
    for (int i = 1; i <= n; i++)
        if (a[i] > B) ++mp[a[i]];
    for (auto x : mp) S1.emplace_back(x);
    std::sort(S1.begin(), S1.end());
}

int main() {
    scanf("%d%lld", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    Init();

    for (auto [x, a] : S) {
        LL v = m / x;
        for (auto [y, b] : S0) {
            if (x < y) break;
            if (1ll * x * y > m) break;
            if (x == y)
                ans += 1ll * a * b % mod * (v / y % mod);
            else
                ans += 2ll * a * b % mod * (v / y % mod);
            ans %= mod;
        }
    }

    for (auto [x, a] : S1)
        if (x <= m / B) pre[x] += a;
    for (int i = B; i <= m / B; i++) pre[i] += pre[i - 1];
    for (LL l = 1, r; l <= m; l = r + 1) {
        r = m / (m / l);
        if (m / l <= m / B / B)
            for (auto [x, a] : S1) {
                LL p = m / l;
                LL _l = l / x + (bool)(l % x), _r = r / x;
                // m / (x * y) = p
                // _l <= y <= _r
                if (_r >= _l) {
                    ans += 1ll * pre[_r] * p % mod * a % mod;
                    if (_l > 0) ans += mod - 1ll * pre[_l - 1] * p % mod * a % mod;
                    ans %= mod;
                }
            }
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：_Yonder_ (赞：6)

写了一个很奇怪的做法，跑的倒是很快。

我们令 $B$ 为分治界，然后我们要提前求出 $a_i\le B$ 的 $\displaystyle\sum_{j = 1}^{n}\left \lfloor \frac{m}{a_ia_j} \right \rfloor$，这里只需整除分块加差分即可。

$a_i>B$ 的就简单了，暴力求倍数加二分查询即可。

时间复杂度 $O(n\sqrt B+\frac{m}{B})$，会发现 $B$ 取 $10^5$ 时最优（这个做法不需要 $\displaystyle\sum_{i= 1}^{n} a_i\le10^9$ 的条件，而且跑的非常快）。
# Code
```
#include<bits/stdc++.h>
#ifdef ONLINE_JUDGE
static char buf[4500000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,4500000,stdin),p1==p2)?EOF:*p1++
#endif
#define S std::ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define rep(i,l,r) for(register int i=l;i<=r;i++)
#define per(i,l,r) for(register int i=l;i>=r;i--)
#define ll long long
#define lt __int128
using namespace std;
template<typename P>inline void read(P&x){bool f=0;x=0;char c=getchar();while(!isdigit(c)) f|=c=='-',c=getchar();while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();x=f?~(x-1):x;}
template<typename P>inline void write(P x){if(x<0) putchar('-'),x=-x;if(x>9) write(x/10);putchar((x%10)^48);}
//template<typename P>inline void wu(P x){}
#define int long long
const int N=1e6+5,M=5e3+5,mod=998244353;const long long inf=1e17;
int n,m,a[N],last,ans,len,v[N],cnt[N],c[N],b=1e5;
signed main(){
    read(n),read(m);rep(i,1,n) read(a[i]);sort(a+1,a+1+n);
    per(i,n,1)
        if(v[len]==m/a[i]) cnt[len]++;
        else v[++len]=m/a[i],cnt[len]=cnt[len-1]+1;
    rep(i,1,len){
        for(register int l=1,r=0;l<=min(b,v[i]);l=r+1){//数论分块
            register int o=v[i]/l;
            r=v[i]/o,r=min(r,b);o%=mod;
            c[l]+=o*(cnt[i]-cnt[i-1]),c[r+1]-=o*(cnt[i]-cnt[i-1]);//差分
            c[l]%=mod,c[r+1]%=mod;
        }
    }rep(i,1,b) c[i]=((c[i]+c[i-1])%mod+mod)%mod;//忘记+mod调半天
    v[++len]=1e16;//边界
    rep(i,1,n){
        if(a[i]==a[i-1]){ans=(ans+last)%mod;continue;}last=0;
        if(a[i]<=b){last=c[a[i]];ans=(ans+last)%mod;continue;}//分治
        for(register int j=a[i];j<=m;j+=a[i]){
            int l=lower_bound(v+1,v+1+len,j)-v;
            if(l==len) break;//边界
            int r=lower_bound(v+1,v+1+len,j+a[i])-v;
            if(v[r]>=(j+a[i])){
                if(l==r){//对于搜不到时的小优化
                    j=v[r]/a[i]*a[i]-a[i];//for循环时会加上ai，所以提前减去ai
                    continue;
                }
                r--;
            }
            last=((j/a[i])*1ll*(cnt[r]-cnt[l-1])%mod+last)%mod;
            if(r+1==len) break;
            j=v[r+1]/a[i]*a[i]-a[i];//小优化
        }ans=(ans+last)%mod;
    }write(ans);
    return 0;
}
```

---

## 作者：what_can_I_do (赞：5)

[传送门](https://www.luogu.com.cn/problem/P10704)

本篇题解先对序列排序，因为排序不会影响结果。

数据范围中说了 $\sum_{i=1}^{n} a_i\le 10^9$，所以一个序列中不同的数的数量最多不超过 $5\times 10^4$。原因：$\sum_{i=1}^x\le 10^9$，解该不等式。

那么我们就对序列进行去重，并且同时把每一个数出现过的次数记录，次数记为 $v_i$，然后暴力计算，但是答案加上的数得要乘上两个数出现过的次数，假设这两个数为 $i$ 和 $j$，这是因为用先选 $i$ 再选 $j$ 的方式选择这两个数的话那么在原序列（指还没排序时的序列）中就可以有 $v_i\times v_j$ 种选法。

但是这么做只有 $70$ 分。

接下来考虑优化。

在赛时我们可以注意到有 $\frac{m}{2}$ 个 $a_i\times a_j$ 可以使 $\lfloor\frac{m}{a_i\times a_j}\rfloor$ 等于 $1$，有 $\frac{m}{2}-\frac{m}{3}$ 个 $a_i\times a_j$ 可以使 $\lfloor\frac{m}{a_i\times a_j}\rfloor$ 等于 $2$，有 $\frac{m}{3}-\frac{m}{4}$ 个 $a_i\times a_j$ 可以使 $\lfloor\frac{m}{a_i\times a_j}\rfloor$ 等于 $3$ 等等。因为 $\frac{m}{2}\ge \frac{m}{2}-\frac{m}{3}\ge \frac{m}{3}-\frac{m}{4}$，后面的以此类推，所以 $\lfloor\frac{m}{a_i\times a_j}\rfloor$ 越大能涵盖的数就越多。

于是我们先枚举 $\lfloor\frac{m}{a_i\times a_j}\rfloor$ 的结果 $x$，此时已知 $\lfloor\frac{m}{a_i}\rfloor$，我们就可以用二分找到满足 $\lfloor\frac{m}{a_i\times a_j}\rfloor\le x$ 时 $a_j$ 的最小值的下标 $j$，再利用上一次二分的结果，也就是满足 $\lfloor\frac{m}{a_i\times a_j}\rfloor\le x-1$ 时 $a_j$ 的最小值的下标 $j$，即可得出满足 $\lfloor\frac{m}{a_i\times a_j}\rfloor= x$ 时 $j$ 的范围，记为 $l\le j\le r$。那么答案就要加上 $\sum_{k=l}^{r} x\times v_i\times v_k$，很明显可以变为 $x\times v_i\times \sum_{k=l}^{r} v_k$，对于 $\sum_{k=l}^{r} v_k$ 的部分可以用前缀和来求。

记去重后不同元素的个数为 $c$，亲测枚举 $x$ 时的上限选择 $\sqrt{c}$ 时时间复杂度算是比较优的，可以过本题。

不过会有一些元素并没有在枚举 $x$ 时被计算到，那么只要把剩下这些元素暴力计算即可。

# CODE:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
ll m;
ll a[1000001];
ll ans;
ll dy[1000001];
ll v[1000001];
ll s[1000001];
ll tot;
const ll mod=998244353;
inline ll read()
{
	register ll x=0;register char ch=getchar();
	while(ch<'0'||'9'<ch) ch=getchar();
	while('0'<=ch&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x;
}
inline ll ef(ll x,ll y)
{
	ll l=1,r=tot,ss=tot+1;
	while(l<=r)
	{
		ll mid=(l+r)>>1;
		if(x/a[mid]<=y) r=mid-1,ss=mid;
		else l=mid+1;
	}
	return ss;
}
int main()
{
	n=read(),m=read();
	for(register int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1);
	for(register int i=1;i<=n;i++)
		if(a[i]!=a[i-1]) tot++,dy[tot]=a[i],v[tot]++;
		else v[tot]++;
	unique(a+1,a+n+1);
	for(register int i=1;i<=tot;i++) s[i]=s[i-1]+v[i];
	for(register int i=1;i<=tot;i++)
	{
		ll x=dy[i];
		if(x>m) break;
		ll mm=m/x,kk=ef(mm,0)-1;
		for(register ll j=1;j*j<=tot;j++)
		{
			ll xx=ef(mm,j);
			ans+=j*v[i]%mod*(s[kk]-s[xx-1])%mod,ans%=mod;
			kk=xx-1;
			if(kk<1) break;
		}
		for(register ll j=kk;j>=1;j--)
		{
			ll y=dy[j];
			if(1ll*x*y>m) break;
			ans+=m/x/y*v[i]%mod*v[j]%mod;
			if(ans>=mod) ans-=mod;
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：EuphoricStar (赞：4)

不依赖 $a_i \le 10^9$ 的做法。

设 $b_x$ 为有多少个 $i$ 使得 $a_i = x$。

设一个阈值 $B$。当 $\frac{m}{a_i a_j} > B$ 时 $a_i a_j < \frac{m}{B}$，可以直接枚举 $a_i$ 和 $a_j$ 然后利用 $b$ 数组统计。这部分时间复杂度为 $O(\frac{m}{B} \ln \frac{m}{B})$。

当 $\frac{m}{a_i a_j} \le B$ 时，统计 $\left\lfloor\frac{m}{a_i a_j}\right\rfloor$ 之和可以转化为对于一个整数 $k \in [1, B]$，有多少对 $(i, j)$ 满足 $x \le \frac{m}{a_i a_j}$ 即 $x \cdot a_i \cdot a_j \le m$。可以排序后双指针统计。这部分时间复杂度为 $O(nB)$。

总时间复杂度为 $O(\frac{m}{B} \ln \frac{m}{B} + nB)$。取 $B = 350$ 可以通过。

```cpp
#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

const int maxn = 1000100;
const int N = 30000000;
const ll mod = 998244353;

ll n, m, a[maxn], b[N + 5];

void solve() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
		if (a[i] <= N) {
			++b[a[i]];
		}
	}
	sort(a + 1, a + n + 1);
	ll ans = 0;
	for (int i = 1; i <= N; ++i) {
		if (!b[i]) {
			continue;
		}
		for (int j = 1; i * j <= N; ++j) {
			if (b[j]) {
				ll x = m / i / j;
				if (x <= 350) {
					continue;
				}
				x %= mod;
				ans = (ans + b[i] * b[j] % mod * x) % mod;
			}
		}
	}
	for (int x = 1; x <= 350; ++x) {
		for (int i = n, j = 0, k = 1; i; --i) {
			while (j < n && x * a[i] * a[j + 1] <= m) {
				++j;
			}
			while (k <= n && a[i] * a[k] * 351 <= m) {
				++k;
			}
			ans += j - k + 1;
		}
	}
	printf("%lld\n", ans % mod);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}

```

---

## 作者：XeCtera (赞：2)

[题目链接](/problem/P10704)

此做法不依赖 $a_i$ 的值域限制。时间复杂度 $O(n+m^{3/4})$，空间复杂度 $O(\sqrt m)$。

----

记 $\displaystyle f(x)=\sum_j\left\lfloor\dfrac x{a_j}\right\rfloor$，则答案为

$$ans=\sum_if(m/a_i)$$

记 $sq=\sqrt m$（**没有下取整**），考虑整除分块：

- 对于 $a_i>sq$ 的部分，枚举 $x=m/a_i:$

$$ans_1=\sum_{1\le x\le sq}f(x)\sum_{a_i>sq}[m/a_i=x]$$

- 对于 $a_i\le sq$ 的部分，枚举 $y=a_i:$

$$ans_2=\sum_{1\le y\le sq}f(m/y)\sum_{a_i\le sq}[a_i=y]$$

- 最后得到 $ans=ans_1+ans_2$。

其中关于 $a_i$ 的和式容易用桶排序求出。

那么只需计算所有 $f(x)$ 和 $f(m/y)$。

-----

先处理较为简单的 $f(x)$。

$$\begin{aligned}
f(x)&=\sum_j\left\lfloor\dfrac x{a_j}\right\rfloor\\
&=\sum_j\sum_{i}[i\cdot a_j\le x]
\end{aligned}$$

（其中变量 $i$ 为正整数）

设阈值 $B=\sqrt x$（**没有下取整**），考虑分别计算 $i\le B,a_j\le B$ 的部分，再减去公共部分：

$$\begin{aligned}
f(x)&=\sum_{i\le B}\sum_j[a_j\le x/i]+\sum_{a_j\le B}\sum_i[i\le x/a_j]-\sum_{i\le B}\sum_{a_j\le B}1\\
&=\sum_{i\le B}{\color{blue}\sum_{a_j\le x/i}1}+\sum_{a_j\le B}(x/a_j)-\lfloor B\rfloor\sum_{a_j\le B}1
\end{aligned}$$

这种处理方法被称为「Dirichlet 双曲型求和法」。

关于 $a_j$ 的和式容易用桶排序求出。

那么可以 $O(\sqrt x)$ 计算 $f(x)$。

----

计算 $f(m/y)$ 也同理。只需注意，上式中蓝色部分变为$\displaystyle\sum_{a_j\le m/y/i}1$，这需要不同的处理：

- 若 $yi>sq$，则 $m/(yi)<sq$，因此$\displaystyle\sum_{a_j\le m/(yi)}1$ 已经由桶排序处理得到；

 - 若 $yi\le sq$，将其改写为 $\displaystyle\sum_{m/a_j\le yi}1$，亦可由桶排序得到。

至此即完成全部计算。

----

总时间复杂度为

$$\begin{aligned}
T(n)&=n+\sum_{x\le\sqrt m}\sqrt x+\sum_{y\le\sqrt m}\sqrt{m/y}\\
&=O(n+m^{3/4})
\end{aligned}$$

空间复杂度为 $O(\sqrt m)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for (int i=l; i<=r; ++i)
typedef long long i64;
using namespace std;

const int M=1e5+8,P=998244353;
int n,sq,x; i64 m,ans;
int v[M],V[M],s[M],S[M];

i64 calc(int x) {
    int B=sqrt(x),j; i64 ans=0;
    rep(i,1,B) j=x/i,ans+=s[j]+1ll*j*v[i];
    return (ans-1ll*B*s[B])%P;
}
i64 Calc(int y) {
    i64 x=m/y,ans=0; int t=sq/y,B=sqrt(x),j;
    rep(i,1,t) ans+=S[i*y]+1ll*x/i*v[i];
    rep(i,t+1,B) j=x/i,ans+=s[j]+1ll*j*v[i];
    return (ans-1ll*B*s[B])%P;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cin>>n>>m; sq=sqrtl(m);
    while (n--) { cin>>x; x<=sq?++v[x]:++V[m/x]; }
    rep(i,1,sq) s[i]=s[i-1]+v[i];
    S[sq+1]=s[sq];
    for (int i=sq; i; --i) S[i]=S[i+1]+V[i];
    rep(i,1,sq) if (V[i]) ans+=V[i]*calc(i);
    rep(i,1,sq) if (v[i]) ans+=v[i]*Calc(i);
    cout<<ans%P;
    return 0;
}
```

-----

实际上，以上用到的「Dirichlet 双曲型求和法」与整除分块几乎等价。  
因此，仅使用整除分块也可以完成本题。读者不妨自行尝试。

---

## 作者：KazamaRuri (赞：2)

题意简明，不再赘述。

## 分析

简单的套路题，首先有 $ \lfloor \frac{m}{a_i a_j} \rfloor = \lfloor \frac{\lfloor \frac{m}{a_i} \rfloor}{a_j} \rfloor $，发现枚举 $ a_i $ 时，分子为定值，考虑简化。所以定义一个函数 $ f(x) = \sum\limits_{i=1}^{n} \lfloor \frac{x}{a_i} \rfloor $，那么所求答案变为 $ \sum\limits _{i=1}^{n} f(\lfloor \frac{m}{a_i} \rfloor) $。

看到取整自然想到整除分块，这题就变成了整除分块套整除分块。与常规的整除分块不同，$ a_i $ 所对应的自然数并不连续。考虑将 $ a $ 数组排序，当我们处理到 $ a_i $ 时，二分查找最靠右的 $ a_j $，使得 $ \lfloor \frac{m}{a_i} \rfloor = \lfloor \frac{m}{a_j} \rfloor $（这一步实际上是查找整除分块的块右端点），之后计算一次 $ f(\lfloor \frac{m}{a_i} \rfloor) $，再乘上区间长度，就是当前块的答案，然后将 $ i $ 挪到 $ j+1 $。

额，可能有点突然，我比赛时就是这样过了，严谨时间复杂度不会算，但显然一定是在 $ O(n) $ 到 $ O(m) $ 范围内的，且远远跑不到 $ O(m) $。

## 代码

没有刻意压行，代码和思路有略微差别，差别在于代码里二分的是块右端点右一个的位置。

```cpp
#include <iostream>
#include <algorithm>
#define int ll
using namespace std;
using ll= long long;
const int N=1e6+5,mod=998244353;
ll n,m,a[N],ans;
char buf[1<<20],*p1,*p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)
inline int read(){
	int x=0; char ch=getchar(); while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar(); return x;
}
inline ll f(ll x){ ll ret=0;
	for(int i=1,j=1;i<=n;i=j){
		if(a[i]>x) break;
		j=upper_bound(a+1,a+1+n,x/(x/a[i]))-a;
		(ret+=(ll)(j-i)*(x/a[i])%mod)%=mod;
	} return ret;
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	sort(a+1,a+1+n);
	for(int i=1,j=1;i<=n;i=j){
		if(a[i]>m) break;
		j=upper_bound(a+1,a+1+n,m/(m/a[i]))-a;
		(ans+=(j-i)*f(m/a[i])%mod)%=mod;
	} return !printf("%lld",ans);
}
```

---

## 作者：operator_ (赞：1)

# P10704 救赎（Redemption）

[题目传送门](https://www.luogu.com.cn/problem/P10704)

## 题解

一个简单易想的方法，但是需要卡常。

我们定一个阈值 $T$，如果两个数都小于等于 $T$，我们直接开个桶 $O(T^2)$ 暴力。

否则，一定有至少一个数大于 $T$，那么我们先对所有数排序，然后对于每一个大于 $T$ 的数整数分块，每一块内在原数组中二分边界并计算答案。

考虑一下复杂度，大于 $T$ 的数最多有 $\dfrac{\sum a}{T}$ 个，整数分块复杂度 $O(\sqrt{\dfrac{m}{T}})$，带上二分的 $\log$，得到总复杂度 $O(\dfrac{\sqrt m\log n\sum a}{T^{\frac{3}{2}}})$，平衡一下 $T$ 取 $20000$ 左右较优，然而经过实测，后一部分跑不满，故我取 $16000$ 过了。

代码：

```cpp
/*
 * @Author: operator_ 
 * @Date: 2024-07-06 13:53:32 
 * @Last Modified by: operator_
 * @Last Modified time: 2024-07-06 22:04:52
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int rd() {
    int s=0,m=0;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')m=1;ch=getchar();}
    while( isdigit(ch)) s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return m?-s:s;
}
const int M=998244353,ii=1e9;
int n,m,s1,s2,s3,a[1000005],cnt[20005],T;
signed main(){
    cin>>n>>m;T=16000;
    for(int i=1;i<=n;i++) a[i]=rd();
    for(int i=1;i<=n;i++) if(a[i]>T) s1=(s1+m/(a[i]*a[i]))%M;
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++) {
        if(a[i]>T) {
            int x=m/a[i],lst=0,now=0;
            for(int l=1,r;l<=x;l=r+1) {
                r=x/(x/l);int ll=lst,rr=i-1,mid;
                while(ll<=rr) {
                    mid=(ll+rr)>>1;
                    if(a[mid]>r) rr=mid-1;
                    else ll=mid+1,now=mid;
                }
                s2=(s2+(x/l)*(now-lst))%M;lst=now;
            }
        }
        else cnt[a[i]]++;
    }
    for(int i=1;i<=T;i++) if(cnt[i]) 
        for(int j=1;j<=T;j++) if(cnt[j])
            s3=(s3+(m/(i*j))*cnt[i]%M*cnt[j]%M)%M;
    printf("%lld\n",(s1+s2*2+s3)%M);
    return 0;
}
```

---

## 作者：251Sec (赞：1)

首先 $\left\lfloor\frac{m}{a_ia_j}\right\rfloor=\left\lfloor\frac{\left\lfloor\frac{m}{a_i}\right\rfloor}{a_j}\right\rfloor$，众所周知地，$\left\lfloor\frac{m}{x}\right\rfloor$ 的不同值个数只有 $O(\sqrt m)$ 种，考虑对每种值 $t$ 计算 $\sum\limits_j\left\lfloor\frac{t}{a_j}\right\rfloor$。可以直接再套一层整除分块，问题就变成了求一个区间里的 $a_i$ 个数。直接实现是 $O(m^{\frac{3}{4}}\log n)$ 的，这很不牛，我们发现询问的区间 $[l,r]$ 中，$r$ 和 $(l-1)$ 都是 $\left\lfloor\frac{m}{x}\right\rfloor$ 的形式，所以可以预处理 $[1,\left\lfloor\frac{m}{x}\right\rfloor]$ 的 $a_i$ 个数。总复杂度就是 $O(n \log n+m^{\frac{3}{4}})$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int P = 998244353;
int n, bC;
ll m, a[1000005], b[1000005], B;
ll f[1000005], g[1000005];
ll &F(ll x) {
	if (x > B) return g[m / x];
	else return f[x];
}
ll f1[1000005], g1[1000005];
ll G(ll x) {
	ll &t = x > B ? g1[m / x] : f1[x];
	if (~t) return t;
	t = 0;
	for (ll l = 1, r; l <= x; l = r + 1) {
		r = x / (x / l);
		t += x / l * (F(r) - F(l - 1)) % P;
	}
	return t %= P;
}
int main() {
	scanf("%d%lld", &n, &m), B = sqrt(m);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i);
	sort(a + 1, a + n + 1);
	for (ll l = 1, r; l <= m; l = r + 1) {
		r = m / (m / l);
		b[++bC] = m / l;
	}
	reverse(b + 1, b + bC + 1);
	for (int i = 1; i <= bC; i++) F(b[i]) = upper_bound(a + 1, a + n + 1, b[i]) - a - 1;
	memset(f1, -1, sizeof(f1)), memset(g1, -1, sizeof(g1));
	ll ans = 0;
	for (int i = 1; i <= n; i++) ans += G(m / a[i]);
	printf("%lld\n", ans %= P);
	return 0;
}
```

---

## 作者：oyoham (赞：1)

### Problem  
求：

$$ \sum\limits_{i=1}^{n} \sum\limits_{j=1}^{n}\left \lfloor \frac{m}{a_ia_j}  \right \rfloor$$
### Solution
$$ 
\begin{aligned}
\sum\limits_{i=1}^{n} \sum\limits_{j=1}^{n}\left \lfloor \frac{m}{a_ia_j}  \right \rfloor &= \sum\limits_{i=1}^{n} \sum\limits_{j=1}^{n}\left \lfloor \dfrac{\left \lfloor\tfrac{m}{a_i}\right \rfloor}{a_j}\right \rfloor\\
&=\sum\limits_{i=1}^{n} \left(\sum\limits_{x=1}^{n}\left[\left \lfloor\dfrac{m}{a_x}\right \rfloor=i\right]\right)\sum\limits_{j=1}^{n}\left \lfloor \dfrac{i}{a_j}\right \rfloor\\
&=\sum\limits_{i=1}^{n} \left(\sum\limits_{x=1}^{n}\left[\left \lfloor\dfrac{m}{a_x}\right \rfloor=i\right]\right)\sum\limits_{j=1}^{n}\left(\sum\limits_{y=1}^{n}\left[\left \lfloor \dfrac{i}{a_y}\right \rfloor=j\right]\right)
\end{aligned}
$$
分别进行整除分块即可，时间复杂度为$\Theta(m^\frac{3}{4})$。
### Code
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define ll long long
#define int ll
inline ll read(){
    ll x=0;
    short f=1;
    char c=getchar();
    while(c>57||c<48){
        if(c==45) f=-1;
        c=getchar();
    }
    while(c<58&&c>47){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
    if(x<0ll) putchar(45),x=~x+1;
    if(x>9ll) write(x/10);
    putchar(x%10|48);
}
#define mod 998244353
int n=read(),m=read();
int a[1000005],b[1000005];
int c[1000005];
int _split(int X){
    int ans=0;
    for(int l=1,r;l<=n;l=r+1){
        if(X<a[l]) return ans%mod;
        r=upper_bound(a+1,a+n+1,X/(X/a[l]))-a-1;
        ans+=(r-l+1)*(X/a[l]);
        ans%=mod;
    }
    return ans%mod;
}
int split(){
    int ans=0;
    for(int l=1,r;l<=n;l=r+1){
        if(m<a[l]) return ans%mod;
        r=upper_bound(a+1,a+n+1,m/(m/a[l]))-a-1;
        ans+=(r-l+1)*_split(m/a[l]);
        ans%=mod;
    }
    return ans%mod;
}
void solve(){
    sort(a+1,a+n+1);
    write(split());
}
signed main(){
    for(int i=1;i<=n;i++) a[i]=read();
    solve();
}
```

---

## 作者：gcx12012 (赞：1)

### 题意
求:
$$ \sum_{i=1}^n \sum_{j=1}^n \lfloor\frac{m}{a_ia_j}\rfloor$$

数据范围：$n\leq 10^6,\sum a_i\leq10^9,m\leq 10^{10}$。
### Solution
这里需要猜到一个结论：
$$ \lfloor\frac{m}{a_ia_j}\rfloor=\lfloor\frac{\lfloor \frac{m}{a_i}\rfloor}{a_j}\rfloor=\lfloor\frac{\lfloor \frac{m}{a_j}\rfloor}{a_i}\rfloor$$
证明：
设
$$ \lfloor\frac{m}{a_ia_j}\rfloor=k$$
则有
$$ka_ia_j\leq m <(k+1)a_ia_j$$
即
$$ka_j\leq \frac{m}{a_i} <(k+1)a_j$$
代入式子后等式成立，证毕。

有了这个结论以后题会更好想一些。

我们考虑两个数 $i=j$ 和 $i<j$ 时对答案的贡献。

第一类很容易计算，将一个数的出现次数存到 map 里，然后设 $i$ 出现了 $k$ 次，那么它对答案的贡献为 $ik^2$。

我们考虑第二类如何计算。

设一个阈值 $V$，当 $a_i \leq V$ 时，我们可以直接暴力枚举计算贡献，当 $a_i >V$ 时，考虑到这样的数最多只会有 $\frac{\sum a_i}{V}$ 个，因此我们可以对每一个这样的数做数论分块，统计前面的数用前缀和维护即可。

设 $V=1000$ 可以通过。

具体细节请看代码。
### Code 
```cpp
#include<bits/stdc++.h>
#include<cmath>
#define ll long long
#define lll __int128
#define ull unsigned long long
#define N 1000010
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rof(i,a,b) for(int i=a;i>=b;i--)
#define ls x<<1
#define rs x<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r 
#define pb push_back
#define mk make_pair
#define pque priority_queue
#define pii pair<int,int>

using namespace std;
bool st;
const ll mod=998244353;
map<ll ,ll >mp;
ll a[N],b[N];
ll n,m,ans;
bool ed;

ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
ll ask(int l,int r){
	if(l>r) return 0;
	return b[r]-b[l-1];
}

int main()
{
    //fprintf(stderr,"%d",(&ed-&st)/1024/1024);
    //freopen("xinyue.in","r",stdin);
    //freopen("xinyue.out","w",stdout);
    n=read(),m=read();
    For(i,1,n) a[i]=read(),mp[a[i]]++;
    For(i,1,n){
    	if(mp[a[i]]){
    		ans=(ans+(m/a[i]/a[i])%mod*mp[a[i]]%mod*mp[a[i]]%mod)%mod;
    		mp[a[i]]=0;
		}
	}
	sort(a+1,a+n+1,[&](ll x,ll y){return x<y;});
	For(i,1,n) if(a[i]<=1000000) b[a[i]]++;
	For(i,1,1000000) b[i]+=b[i-1];
	Rof(i,n,1){
		if(a[i]<=10000) break;
		ll now=m/a[i],l=1,r;
		while(l<=now && l<a[i]){
			r=now/(now/l);
			if(r>=a[i]) r=a[i]-1;
			ans=(ans+2ll*ask(l,r)%mod*(now/l)%mod)%mod;
			l=r+1;
		}
	}
	For(i,1,10000){
		For(j,1,i-1){
			ans=(ans+2ll*(m/i/j)*(b[i]-b[i-1])%mod*(b[j]-b[j-1])%mod)%mod;
		}
	}
	cout<<ans;
	return 0;
}
/*

*/
```

---

## 作者：diqiuyi (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10704)。

似乎不需要用到 $\sum a_i \le 10^9$ 的性质。

看到 $m$ 在分子上，所以考虑整除分块，然后就转化成了求有多少个 $i$，$j$ 满足 $l\le a_ia_j \le r$，显然可以拆成前缀和的形式。

不妨令 $a_i \le a_j$，则 $a_i \le \sqrt{x}$，其中 $x$ 是某个 $\lfloor m/i \rfloor$。考虑杜教筛的时间复杂度，直接枚举 $a_i$ 的时间复杂度是 $O(m^{3/4})$，枚举完 $a_i$ 后还要 $O(\log n)$ 计算 $a_j$ 的个数，无法接受。

但是可以考虑设一个阈值 $B$，对于 $\le B$ 的数处理出它们个数的前缀和，那么在 $a_i \ge x/B$ 时就可以 $O(1)$ 算出 $a_j$ 的个数了，时间复杂度为 $O(m^{3/4}+\dfrac{m}{B}\log m \log n+n\log n+B)$。取 $B=\sqrt{m\log m\log n}$ 可以有最优复杂度 $O(m^{3/4}+\sqrt{m\log m\log n}+n\log n)$。实际上随便取个数都能过。

**code**
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x=0,f=1,ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch&15);
    return f*x;
}
const int mod=998244353,B=1000000;
int n,m,a[1000005],scnt[B+5],cnt[B+5],ans,s[B+5],sq;
vector<int> v;
int cl(int x){
    if(x<=B) return scnt[x];
    return upper_bound(a+1,a+n+1,x)-a-1;
}
int calc(int x){
    int res=0;
    for(int i=1;i*i<=x;i++)
        res+=cnt[i]*(2*(cl(x/i)-scnt[i])+cnt[i]),res%=mod;
    return res;
}
signed main(){
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        if(a[i]<=B) cnt[a[i]]++;
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=B;i++) scnt[i]=scnt[i-1]+cnt[i];
    for(int l=1,r;l<=m;l=r+1)
        r=m/(m/l),ans=(ans+(m/l)*(calc(r)-calc(l-1)))%mod;
    printf("%lld\n",(ans+mod)%mod);
    return 0;
}
```

---

## 作者：鲤鱼江 (赞：1)

需要卡常的赛时做法。

考虑直接暴力进行整除分块。

$$ \sum\limits_{i=1}^{n} \sum\limits_{j=1}^{n}\left \lfloor \frac{m}{a_ia_j}  \right \rfloor=\sum\limits_{i=1}^{n} \sum\limits_{j=1}^{n}\left \lfloor\frac{\left \lfloor \frac{m}{a_i}\right \rfloor}{a_j}  \right \rfloor$$

拆开之后发现后面是一个经典的整除分块形式，所以选择暴力整除分块。

也就是枚举 $a_i$，对后面的 $\left \lfloor \frac{m}{a_i}\right \rfloor$ 进行整除分块，并将整除分块时拿出的区间在 $a$ 序列中二分，看有多少个数在这个区间，具体可以见代码。

这里有一个保证复杂度的地方~~所以不算太暴力~~，就是要先将 $a$ 序列排序，相同的 $a_i$ 只做一遍。

由于题目限定了 $\sum\limits_{i=1}^na_i\leq10^9$ 所以本质不同的数只有不超过 $\sqrt{10^9}$ 个，所以复杂度类似于杜教筛，是 $O(n^{\frac{3}{4}}\log n)$ 的。

但是要卡常，不过很简单，只需要两个优化：只需要每次只二分一遍，然后只在统计答案时取模。

```cpp
#include<bits/stdc++.h>
#define ll long long

using namespace std;

inline int read(){
	int x=0,f=0;
	char c=getchar();
	while(c<'0'||c>'9'){f|=(c=='-');c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}
	return f?-x:x;
}

const int mod=998244353;
struct modint {
    ll val;
    inline int Mod(const int &x){return x>=mod?x-mod:x;}
    modint() : val(0) {}
    modint(const int& m) : val(m) {}
    modint(const ll &m):val(m%mod){}
    modint& operator+=(const modint& o) { return val = Mod(val + o.val), *this; }
    modint& operator*=(const modint& o) { return val = static_cast<int>(1ll * val * o.val % mod), *this; }
    modint operator+(const modint& o) const { return modint(*this) += o; }
    modint operator*(const modint& o) const { return modint(*this) *= o; }
};

const int N=1e6+10;
int a[N],n;
modint ans;
ll m;

signed main(){
	n=read();scanf("%lld",&m);
	for(int i=1;i<=n;++i) a[i]=read();
	sort(a+1,a+1+n);ll res=0;
	for(int i=1;i<=n;++i){
		if(i!=1&&m/a[i]==m/a[i-1]){ans+=res;continue;}
		ll t=m/a[i],tmp=0,las=0;res=0;
		for(ll j=1,k=0;j<=t;j=k+1){
			j=(t/j);k=t/j;
			tmp=upper_bound(a+1,a+1+n,k)-a-1;;
			res+=1ll*(tmp-las)*j;
			las=tmp;
		}
		ans+=res;
	}
	printf("%lld\n",ans.val);
	return 0;
}
```

---

## 作者：TTpandaS (赞：1)

首先 $\left\lfloor\dfrac{m}{a_ia_j}\right\rfloor=\left\lfloor\dfrac{\left\lfloor\dfrac{m}{a_i}\right\rfloor}{a_j}\right\rfloor$，那么对于每个 $a_i$，先算出 $b_i=\left\lfloor\dfrac{m}{a_i}\right\rfloor$，由此可知不同的 $b_i$ 只有 $\sqrt m=10^5$ 种。

由 $\sum a_i \leq 10^9$ 可知不同的 $a_i$ 只有 $4 \times 10^4$ 种左右。

如果直接枚举不同的 $b_i$ 和 $a_i$ 算贡献，可以得到 $70 pts$，而只有第 $19$ 个测试点无法通过。

考虑优化。如果 $a_i$ 的种类非常多，那么肯定就会有很多较小的 $a_i$。每次我们计算 $\left\lfloor\dfrac{b_i}{a_j}\right\rfloor$ 的时候，只需要计算 $a_j<b_i$ 的情况，那么对于较小的 $b_i$，可以对 $b_i$ 进行数论分块，然后二分在 $[l,r]$ 内的 $a_i$ 的数量。需要注意的是由于这里 $l,r$ 递增，所以记录一下二分的左端点，不然还是会超时。

时间复杂度看起来还是错的，但其实跑得飞快。

---

## 作者：1234567890sjx (赞：0)

萌新刚刚学完整除分块，然后写了一道 ~~[aimat](/user/746544) 大佬场上没过的~~ 比较经典（简单且模板）的整除分块题。但是为啥这个 $n$ 要开到 $10^6$ 啊！！！！可爱的数据范围给人一种吃答辩的美感。

### 离开坐位

题意很清晰，就是求 $\large\sum\limits_{i=1}^n\sum\limits_{j=1}^n\lfloor\frac{m}{a_ia_j}\rfloor$ 的值。

容易发现上面这个式子可以化简为 $\large\sum\limits_{i=1}^n\sum\limits_{j=1}^n\lfloor\frac{\lfloor\frac{m}{a_i}\rfloor}{a_j}\rfloor$。

考虑枚举 $i$，再枚举 $j$，时间复杂度为 $O(n^2)$，但是这样过不去。考虑优化。

### 进入厕所

为了让这个式子清晰一些，令 $T=\lfloor\frac{m}{a_i}\rfloor$。则式子变为 $\large\sum\limits_{i=1}^n\sum\limits_{j=1}^n\lfloor\frac{T}{a_j}\rfloor$。这个式子为一个经典的整除分块问题。因此考虑枚举 $i$，然后用整除分块来做右边的 $\sum\limits_{j=1}^n \lfloor\frac{T}{a_j}\rfloor$ 的值。考虑使用珂朵莉树的类似方式来维护整除分块中的每一个区间，这个东西的数量级别为 $O(\sqrt n)$。然后因为 $a$ 数组中元素的顺序无关，考虑将 $a$ 数组有序，即从小到大排序。然后对于每一个除出来之后得数相同的区间 $[l,r]$，使用二分查找在有序数组中查找出在这一段区间内的数的个数即可。时间复杂度为 $O(n\sqrt n\log n)$。

顺便提一嘴：记得及时取模。这个【】因为没有取模调试了 $20$ 分钟。

附一下代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1000100, mod = 998244353;
int a[N];
signed main() {
    int n, m;
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &a[i]);
    sort(a + 1, a + n + 1);
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        int t = m / a[i];
        if (t > 0) {
            int l = 1, r, p1 = 0, p2 = 0;
            while (l <= t) {
                r = min(t, t / (t / l));
                // p\in [l, r] 一段区间内 t / p 的值相同
                // 找全局第一个 >= l 的数
                int ll = 1, rr = n, best = n + 1;
                while (ll <= rr) {
                    int mid = ll + rr >> 1;
                    if (a[mid] >= l)
                        best = mid, rr = mid - 1;
                    else
                        ll = mid + 1;
                }
                int p1 = best;
                // 找全局最后一个 <= r 的数
                ll = 1, rr = n, best = 0;
                while (ll <= rr) {
                    int mid = ll + rr >> 1;
                    if (a[mid] <= r)
                        best = mid, ll = mid + 1;
                    else
                        rr = mid - 1;
                }
                int p2 = best;
                if (p1 <= p2)
                    res += (p2 - p1 + 1) * ((t / a[p1]) % mod) % mod, res %= mod;
                l = r + 1;
            }
        }
    }
    printf("%lld\n", res);
}
```

### 开吃答辩

因为上述做法时间复杂度为 $O(n\sqrt n\log n)$，因为 $n\le 10^6$，最大可以跑到 $10^6\times \sqrt{10^6}\times \log 10^6\approx 2\times 10^{10}$，就算是 4s 也没用。获得了和最低档暴力同分的 $20$ 分高分！

于是我们，开始吃大便！

---------

**第一坨大便**

考虑观察每一次二分的性质。容易发现整除分块内执行的 $O(\sqrt n)$ 次 $\log n$ 级二分，其答案区间一定能恰好覆盖 $[1,n]$ 区间中每一个整点一次，因此我们可以对我们美丽的二分记忆化。也就是说，若上一次二分出的右端点，她的值为 $p$，则下一次二分出的左端点的值一定不会大于 $p+1$。所以我们可以直接美丽的钦定我们下一次求左端点的二分的值为 $p+1$，然后还需要二分右端点即可。右端点二分的时候，直接从左端点的位置开始二分就行了：因为右端点的值一定不可能小于左端点。

于是我们优化掉了一次二分和一次二分的判断。

特殊的，求左端点的时候，可能 $p+1$ 是不符合左端点条件的。此时左端点的值为 $p$。然后这样实现可能稍微有一点点小小的细节。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1000100, mod = 998244353;
int a[N];
signed main() {
    int n, m;
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &a[i]);
    sort(a + 1, a + n + 1);
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        int t = m / a[i];
        if (t > 0) {
            int l = 1, r, p1 = 0, p2 = 0;
            int lastp = 0;
            while (l <= t) {
                r = min(t, t / (t / l));
                int p1 = lastp + 1;
                int ll = p1 - 1, rr = n, best = 0;
                while (ll <= rr) {
                    int mid = ll + rr >> 1;
                    if (a[mid] <= r)
                        best = mid, ll = mid + 1;
                    else
                        rr = mid - 1;
                }
                int p2 = lastp = best;
                if (p1 <= p2 && a[p1] >= l)
                    res += (p2 - p1 + 1) * ((t / a[p1]) % mod) % mod, res %= mod;
                l = r + 1;
            }
        }
    }
    printf("%lld\n", res);
}
```

前后对比：

前：`2.98s, 3.02s`。

后：`1.33s, 1.40s`。

其实优化了不止一倍。但是还是 $20$ 分。

**第二坨大便**

开始卡常！使用 `upper_bound` 比使用手写二分快一些。把判定无解的环节去掉可以让程序的运行时长变为原来的 $\frac{5}{6}$。使用 `register` 和 `fread` 可以让程序的运行时长变为原来的 $\frac{49}{50}$。

但是这还是不够。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1000100, mod = 998244353;
int a[N], b[N];
char *p1,*p2,buf[10000010];
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,10000009,stdin),p1==p2)?EOF:*p1++)
inline int read(){
	register int x=0;
	register char c=gc();
	while(c<48)c=gc();
	while(c>47)x=(x<<3)+(x<<1)+(c^48),c=gc();
	return x;
}
inline long long lread(){
	register long long x=0;
	register char c=gc();
	while(c<48)c=gc();
	while(c>47)x=(x<<3)+(x<<1)+(c^48),c=gc();
	return x;
}
int qun[65536];
signed main() {
    register int n, res = 0;
    register long long m;
    n = read(), m = lread();
    for (register int i = 1; i <= n; ++i)
        a[i] = read();
    sort(a + 1, a + n + 1);
    for (register int i = 1; i <= n; ++i) {
        register long long t = m / a[i];
        if (t > 0) {
            register long long l = 1, r;
            register int lastp = 0;
            while (l <= t) {
                r = min(t, t / (t / l));
                // 找 <= r 的最大整数
                register int p1 = lastp + 1, p2 = (upper_bound(a + lastp, a + n + 1, r) - a) - 1;
                lastp = p2;
                res += 1ll * (p2 - p1 + 1) * ((t / l) % mod) % mod, res %= mod;
                l = r + 1;
            }
        }
    }
    printf("%d", res);
}
```

**第三坨大便**

还记得 LiuMaXiao OI 第一题吗？考虑对于相同的 $a_i$ 将它们的值一并计算。可以优化不少倍的常数。

实测这样可以通过。大概是因为 $\sum a_i\le 10^9$ 然后导致重复的 $a_i$ 的值过多吧。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1000100, mod = 998244353;
int a[N], b[N];
char *p1,*p2,buf[10000010];
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,10000009,stdin),p1==p2)?EOF:*p1++)
inline int read(){
	register int x=0;
	register char c=gc();
	while(c<48)c=gc();
	while(c>47)x=(x<<3)+(x<<1)+(c^48),c=gc();
	return x;
}
inline long long lread(){
	register long long x=0;
	register char c=gc();
	while(c<48)c=gc();
	while(c>47)x=(x<<3)+(x<<1)+(c^48),c=gc();
	return x;
}
int qun[65536];
signed main() {
    register int n, res = 0;
    register long long m;
    n = read(), m = lread();
    for (register int i = 1; i <= n; ++i)
        a[i] = read();
    sort(a + 1, a + n + 1);
    register int lint = 0;
    for (register int i = 1; i <= n; ++i) {
        register long long t = m / a[i];
        if (t > 0) {
            if (a[i] != a[i - 1]) {
                lint = 0;
                register long long l = 1, r;
                register int lastp = 0;
                while (l <= t) {
                    r = min(t, t / (t / l));
                    register int p1 = lastp + 1, p2 = (upper_bound(a + lastp, a + n + 1, r) - a) - 1;
                    lastp = p2;
                    lint += 1ll * (p2 - p1 + 1) * ((t / l) % mod) % mod, lint %= mod;
                    l = r + 1;
                }
            }
            res = (res + lint) % mod;
        }
    }
    printf("%d", res);
}
```

### 走出厕所

放一堆更快的代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1000100, mod = 998244353;
int a[N], b[N];
char *p1,*p2,buf[10000010];
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,10000009,stdin),p1==p2)?EOF:*p1++)
inline int read(){
	register int x=0;
	register char c=gc();
	while(c<48)c=gc();
	while(c>47)x=(x<<3)+(x<<1)+(c^48),c=gc();
	return x;
}
inline long long lread(){
	register long long x=0;
	register char c=gc();
	while(c<48)c=gc();
	while(c>47)x=(x<<3)+(x<<1)+(c^48),c=gc();
	return x;
}
void msort(int left,int right,int a[],int b[]){
	if(left==right)return;
	register int mid=left+right>>1;
	msort(left,mid,a,b),msort(mid+1,right,a,b);
	register int i=left,j=mid+1,tot=left;
	while(i<=mid&&j<=right)if(a[i]<a[j])b[tot++]=a[i++];else b[tot++]=a[j++];
	while(i<=mid)b[tot++]=a[i++];while(j<=right)b[tot++]=a[j++];
	for(int i=left;i<=right;++i)a[i]=b[i];
}
int qun[65536];
signed main() {
    register int n, res = 0;
    register long long m;
    n = read(), m = lread();
    for (register int i = 1; i <= n; ++i)
        a[i] = read();
    msort(1, n, a, b);
    register int lint = 0;
    for (register int i = 1; i <= n; ++i) {
        register long long t = m / a[i];
        if (t > 0) {
            if (a[i] != a[i - 1]) {
                lint = 0;
                register long long l = 1, r;
                register int lastp = 0;
                while (l <= t) {
                    r = min(t, t / (t / l));
                    register int p1 = lastp + 1, p2 = (upper_bound(a + lastp, a + n + 1, r) - a) - 1;
                    lastp = p2;
                    lint += 1ll * (p2 - p1 + 1) * ((t / l) % mod) % mod, lint %= mod;
                    l = r + 1;
                }
            }
            res = (res + lint) % mod;
        }
    }
    printf("%d", res);
}
```

~~总结：吃了三坨大便。~~

---

## 作者：Unnamed114514 (赞：0)

首先我们有一个经典的结论：$\lfloor\dfrac{m}{a_ia_j}\rfloor=\lfloor\dfrac{\lfloor\frac{m}{a_i}\rfloor}{a_j}\rfloor$。

考虑枚举外层的 $i$，得到 $m'=\dfrac{m}{a_i}$，注意到 $m'$ 共 $O(\sqrt m)$ 种取值。

注意到内层如果直接 $O(\sqrt m')$ 的话，时间复杂度 $O(m^{\frac{3}{4}})$。

内层直接整除分块，对于每个区间，查询 $[l,r]$ 中数的数量，乘上 $\lfloor\dfrac{m}{l}\rfloor$。

查询数的数量这一步，直接二分即可，具体就是 $r$ 的 `upper_bound` 减去 $l$ 的 `lower_bound`。

这样做会 TLE 60。

注意到在同一个整除分块中，$l_i=r_{i-1}+1$（$i$ 表示第 $i$ 次询问），所以 $l_i$ 的 `lower_bound` 就是 $r_{i-1}$ 的 `upper_bound`。

这样我们利用了上一次查询到的值，优化了一半的常数，就过了。

时间复杂度 $O(m^{\frac{3}{4}}\log n)$。

---

## 作者：dgdyrkst (赞：0)

## 思路
第一眼看到这题，想到的就是数论分块。可以参见 [P2261](https://www.luogu.com.cn/problem/P2261)。

但显然还是有点不同的，因为这题有两个求和，该怎么办呢？

我稍微思考了一下，发现就是 $\left \lfloor \frac{m}{a_ia_j}  \right \rfloor$ 这个东西，可以考虑先将 $i$，$j$ 分开。它可以是 $\left \lfloor \frac{\left \lfloor \frac{m}{a_i} \right \rfloor}{a_j}  \right \rfloor$，然后对于 $j$ 的求和就是一个标准的数论分块。

但是这里数论分块貌似有点特殊，因为分母不都是连续的，看来只能离散化然后每次二分或者倍增跳，很好很好。

感觉没什么问题，算一下复杂度是 $O(n\sqrt{m})$，这也过不了啊?

+ $\sum\limits_{i=1}^{n}a_i\le10^9$

没错这东西肯定是有用的，因为 $1$ 加到 $50000$ 是大于 $10^9$ 的，那么 $a_i$ 的种类数肯定是不超过 $50000$ 的，这样就可以在枚举 $i$ 的时候直接改成枚举 $a_i$ 的值，乘上对应系数即可。

不愧是我。复杂度 $O(50000 \times \sqrt{m})$，注意到时间限制足足有 $4s$，加上信仰足矣。开冲！！！

## 代码
以下为代码参考。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5;
const ll mod=998244353;
ll n,m,a[N],ans,g[N],c[N],sumc[N],tot;
int main()
{
	scanf("%lld%lld",&n,&m);
	for (int i=1;i<=n;i++)scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	ll cnt=0;
	for (int i=1;i<=n;i++)
	{
		if (a[i]!=a[i-1])c[tot]=cnt,g[++tot]=a[i],cnt=1;
		else cnt++;
	}
	c[tot]=cnt;
	for (int i=1;i<=tot+1;i++)sumc[i]=sumc[i-1]+c[i];
	for (int t=1;t<=tot;t++)
	{
		ll k=m/g[t];
		for (int i=g[1],j,pos=1,lpos;i<=1e9 && j<=1e9 && pos<=tot;i=g[pos])
	    	{
	        	if (k/i)j=min(k,k/(k/i));
	        	else j=1e9;
	        	lpos=pos-1;
	        	pos=upper_bound(g+1,g+tot+1,j)-g;
	      		ans+=(k/i)%mod*c[t]%mod*(sumc[pos-1]-sumc[lpos])%mod;
	      		ans%=mod;
	        	if (i>g[tot])break;
	    	}
	}
	printf("%lld",ans);
	return 0;
}
```
稍微有点丑陋，不管了。

---

## 作者：gan1234 (赞：0)

来个不需要根号分治的做法。

（A 了这题后才发现还有 $\sum a_i<10^9$ 的性质......）

### 分析

根据套路，考虑数论分块，枚举 $a_ia_j$ 的值。令 $S_{x}$  表示有多少 $i,j$ 满足 $a_ia_j\le x$。我们现在要求的相当于是：

$$\sum (S_{r}-S_{l-1})\lfloor \frac m l \rfloor$$

问题就转化如何求 $S$。

考虑如果 $a_ia_j\le x$，那么 $\min(a_i,a_j)\le \sqrt x$，因此我们对于每个 $x$ 只需要 $O(\sqrt x)$ 枚举较小的那个数，前缀和统计答案即可。然后我们就做完了。

看上去十分暴力，这样的复杂度真的是对的吗？

我们来算一下复杂度：

$$O(\sum \sqrt{\lfloor\frac m l \rfloor})\approx O(\int_1^n\sqrt{\frac{m}{x}}dx)=O(\sqrt{nm})$$

实际上远比 $O(\sqrt{nm})$ 要小，用程序算一下第一个式子，大概只有 $10^7$ 左右。

### 代码

实际上有不少细节，例如为保证复杂度要去重，统计答案时要乘上 $2$，不要忘了取模。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define MAXN 1000005
#define mod 998244353
using namespace std;
int n,m,ans;
int a[MAXN],s[MAXN];
int b[MAXN],c[MAXN],N;
int tot;
struct Q{
	int l,r,s;
}q[MAXN];
int get(int x){
	return upper_bound(a+1,a+n+1,x)-a-1;
}
signed sum[MAXN*100];
int solve(int x){
	int res=0;
	for(int i=1;N>=i;i++)
		if(b[i]*b[i]<=x)res+=c[i]*c[i];
		else break;
	for(int i=1;N>=i;i++){
		if(b[i]*b[i]>x)return res;
		if(b[i]<=100){
			res+=(get(x/b[i])-sum[b[i]])*2*c[i];
		}else{
			res+=(sum[x/b[i]]-sum[b[i]])*2*c[i];
		}
	}
	return res;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;n>=i;i++)cin>>a[i];
	
	sort(a+1,a+n+1);
	for(int i=1;n>=i;i++)
		if(a[i]==a[i-1]){
			c[N]++;
		}else{
			c[++N]=1;b[N]=a[i];
		}
	for(int i=1;n>=i;i++)
		if(a[i]<=100000000)
			sum[a[i]]++;
	for(int i=1;100000000>=i;i++)sum[i]+=sum[i-1];


	int l=1,r;
	while(l<=m){
		r=m/(m/l);
		q[++tot].l=l;q[tot].r=r;q[tot].s=m/l;
		l=r+1;	
	}
	int lst=0;
	for(int i=1;tot>=i;i++){
		int s=solve(q[i].r);
		ans=(ans+(s-lst)%mod*q[i].s%mod)%mod;  
		lst=s;
	}
	cout<<ans<<endl;
	return 0;
} 
```

---

## 作者：sbno333 (赞：0)

容易想到 $\lfloor\frac{m}{a_i a_j}\rfloor=\lfloor\frac{\lfloor\frac{m}{a_i}\rfloor}{a_j}\rfloor$。

于是乎，我们想到枚举每一个 $\lfloor\frac{m}{a_i}\rfloor$，然后计算其除以每个数向下取整的和。

然而，常规方法肯定会因为 $O(n^2)$ 而超时，所以考虑奇奇怪怪的方法。

看到除后向下取整，自然地想到整数分块。

我们考虑由 $\lfloor\frac{m}{a_i}\rfloor$ 按数论分块构成的每一块。

每一块我们可以处理出这一块的区间内 $a_j$ 的数量并求出总贡献。

于是我们只需要维护区间内 $a_j$ 的数量。

不难想到树状数组，由于 $a_j$ 范围大，考虑用 `map` 来实现树状数组，此时，单次询问的复杂度为 $O(\log^2 n)$。

当然，这不是重点，我们考虑大头的时间复杂度是否正确。

值的注意的是，$\lfloor\frac{m}{a_i}\rfloor$ 只有 $\sqrt m$ 种，同时只要 $\lfloor\frac{m}{a_i}\rfloor$ 相同，贡献相同，因此有个必要的优化就是枚举时记录每个 $\lfloor\frac{m}{a_i}\rfloor$ 的贡献，如果记录过就直接使用，不在计算。

因为 $\sqrt m\le10^5$，$n\le10^6$，因此认为 $\sqrt m<n$，所以优化是有效的，同时我们的 $n$ 也用 $\sqrt m$ 代替。

对于单次的 $\lfloor\frac{m}{a_i}\rfloor$，时间复杂度不考虑 $\log$ 就是 $O(\sqrt{\lfloor\frac{m}{a_i}\rfloor})$。

考虑计算 $\sum_{i=1}^n\sqrt{\lfloor\frac{m}{a_i}\rfloor}$，但由于 $n>\sqrt m$，因此每个 $\lfloor\frac{m}{a_i}\rfloor$ 都有可能出现，因此就是 $\sum\sqrt{\lfloor\frac{m}{x}\rfloor}$。

此时变形，就是 $\sum\frac{10^5}{\sqrt x}=\sum\frac{10^5\sqrt x}{x}\le10^{2.5}\times\sum\frac{10^5}{x}=10^{7.5}\times\log 10^5\le5\times10^8$。

发现虽然很紧，但是在我们能接受的范围内，同时这是向上扩张后的结果，因此真正的复杂度一定是可以的。

此时交上去发现 $50$ 分，原来 $\log$ 太多，同时人傻常数大，因此超时。

怎么办呢？考虑优化 $\log$。

发现树状数组询问是先进行插入，然后寻找，可以把插入的 $a$ 数组排序，然后询问时二分，此时变成了一只 $\log$，询问时就是两个前缀答案的差。

于是我们获得了 $60$ 分。

发现不需要两次前缀的差，或者说某一次的小的前缀为上一个的大的前缀，于是我们每次只询问一个，常数减半，$70$ 分。

继续探索，发现有一部分不需要二分，不可能为答案。

然后就 AC 了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mod 998244353
signed a[1000009];
int n;
map<int,int> an; 
map<int,bool> b;
signed main(){
	std::ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+1+n);
	int ans;
	ans=0;
	for(int i=1;i<=n;i++){
		int mm;
		mm=m/a[i];
		if(b[mm]){
			ans+=an[mm];
			ans%=mod;
		}else{
			b[mm]=1;
			int sum;
			sum=0;
			int z;
			z=0;
			for(int l=1,r=1;l<=mm;l=r+1,r=mm/(mm/l)){
				int cc;
				cc=upper_bound(a+z,a+1+n,r)-a-1;
				if(cc>n||cc<0){
					cc=n;
				}
				sum+=(cc-z)*(mm/l);
				z=cc;
				if(r==mm){
					break;
				}
			}
			an[mm]=sum;
			ans+=sum;
			ans%=mod;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：lilong (赞：0)

看到 $\sum \limits_{i=1}^n a_i \le 10^9$，可以很快发现不同的 $a_i$ 大约只有 $42000$ 个。设去重后的 $a_i$ 为 $k$ 个，则不难得到一个 $O(k^2)$ 的做法，可以获得 $70$ 分。
```cpp
for( int i = 1 ; i <= n ; i ++ )
{
	if( a[i] != a[i - 1] ) b[++ tot] = a[i],cnt[tot] = 1;
	else cnt[tot] ++;
}
for( int i = 1 ; i <= tot ; i ++ )
{
	s = ( s + 1ll * ( m / ( b[i] * b[i] ) ) * cnt[i] % MOD * cnt[i] ) % MOD;
	for( int j = i + 1 ; j <= tot ; j ++ )
	{
		if( b[i] * b[j] > m ) break;
		ans = ( ans + 1ll * ( m / ( b[i] * b[j] ) ) * cnt[i] % MOD * cnt[j] ) % MOD;
	}
}
```

然而面对大约 $42000$ 的数据，这个算法仍需改进。注意到题目中有一个向下取整的符号，这暗示着**虽然 $a_i \times a_j$ 不同，但最终得到的值却可能是一样的**。我们就从这一点下手优化。

设去重后的数组为 $b$，并且 $b$ 已经排序。对于每个 $b_i$，首先确定 $\left \lfloor \frac{m}{b_ib_j}  \right \rfloor$ 相同时 $j$ 的取值范围。显然，相同时 $j$ 是连续的，因此可以直接二分求得左右边界即可。再通过前缀和维护这段区间内的数的总个数，即可求得该段的贡献。以此类推。

时间复杂度大约为 $O(k \sqrt m \log k )$，实际上完全跑不满，因此能够通过。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#define int long long
#define MOD 998244353
//#define ll long long

using namespace std;

int n;
int a[1000001],b[1000001],tot,cnt[1000001],mx,s,ans,m,S[1000001],L,R,nw;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

int ck( int x , int ti , int Ll )
{
	int l = Ll,r = tot,mid,Rr = Ll;
	while( l < r )
	{
		mid = ( l + r ) / 2 + 1;
		if( ( m / ( b[x] * b[mid] ) ) < ti ) r = mid - 1;
		else l = mid,Rr = mid;
	}
	return Rr;
}

signed main()
{
	n = read(),m = read();
	for( int i = 1 ; i <= n ; i ++ )
		a[i] = read();
	sort( a + 1 , a + n + 1 );
	for( int i = 1 ; i <= n ; i ++ )
	{
		if( a[i] != a[i - 1] ) b[++ tot] = a[i],cnt[tot] = 1;
		else cnt[tot] ++;
	}
	for( int i = 1 ; i <= tot ; i ++ )
		S[i] = S[i - 1] + cnt[i];
	for( int i = 1 ; i <= tot ; i ++ )
	{
		s = ( s + 1ll * ( m / ( b[i] * b[i] ) ) * cnt[i] % MOD * cnt[i] ) % MOD;
		if( i == tot ) continue;
		L = i + 1,nw = ( m / ( b[i] * b[L] ) );
		while( L <= tot )
		{
			R = ck( i , nw , L );
			ans = ( ans + nw * cnt[i] % MOD * ( S[R] - S[L - 1] ) ) % MOD;
			L = R + 1;
			if( L > tot ) break;
			nw = m / ( b[i] * b[L] ); 
		}
	}
	cout << ( ans * 2 + s ) % MOD;
	return 0;
}
```

---

