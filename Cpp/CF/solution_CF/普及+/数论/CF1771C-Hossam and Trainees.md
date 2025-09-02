# Hossam and Trainees

## 题目描述

Hossam has $ n $ trainees. He assigned a number $ a_i $ for the $ i $ -th trainee.

A pair of the $ i $ -th and $ j $ -th ( $ i \neq j $ ) trainees is called successful if there is an integer $ x $ ( $ x \geq 2 $ ), such that $ x $ divides $ a_i $ , and $ x $ divides $ a_j $ .

Hossam wants to know if there is a successful pair of trainees.

Hossam is very tired now, so he asks you for your help!

## 说明/提示

In the first example, the first trainee and the second trainee make up a successful pair:

 $ a_1 = 32, a_2 = 48 $ , you can choose $ x = 4 $ .

## 样例 #1

### 输入

```
2
3
32 48 7
3
14 5 9```

### 输出

```
YES
NO```

# 题解

## 作者：Dream__Sky (赞：3)

观察本题范围，$n\leq10^5$，显然不能用直接暴力枚举两数的方法判断。由于本题要求的是否是**两两**互质，**互质**的要求是两个数之间没有共同的质因子。那么我们推广到多个数的两两互质，即没有一个质数在这些数中出现的次数超过两次，即一个质数只能出现在一个数中。

这个思路，我们第一眼想到的就是预处理出每个数的质因子，然后存在桶里，最后判断桶 $t_i$ 是否大于 $1$。这里的 $t_i$ 需要为质数，所以我们要在一开始就预处理出所有的质数。但由于 $a_i$ 的值域为 $10^9$，直接求不了。

但我们考虑质因数的性质，对于任意非 $0$ 自然数 $n$，最多只能有一个质因子 $p>\sqrt{n}$。所以我们可以分段考虑。

- 对于 $x\leq\sqrt{n}$，直接用桶存。
- 对于 $x>\sqrt{n}$，由于只能有一个，用 `map` 记录即可。


---

## 作者：lraM41 (赞：2)

题意简述：判断是否有两数有大于二的公约数。

参考了[include_BM](https://www.luogu.com.cn/user/336653) 这位大神的题解。

思路：~~暴力? 时限摆在这里呢。~~ 考虑到每个 $a$ 较大，使用分解质因数的方法解决该题。先分解出 $\sqrt{10^9}$ 内的素数，并进行分类讨论。

记 $b$ 为 $a$ 的某个因子 ， $N$ 为 $\sqrt{10^9}$ 。
- $b <N$ 直接分解，拿一个数组记录所有出现过的质因数的次数，只要有个质因数出现超过 $1$ 次，既有两数不互质。
- $b \ge N $ 拿个 map 数组记录这个较大质数出现的次数，保证同一个 $a$ 不会有两个因子 $ \ge N$ 。

详细请看代码：

```
#include<bits/stdc++.h>
using namespace std;
inline int read(){//快读。
	int x=0,m=1;char ch=getchar();
	while(!isdigit(ch)){ if(ch=='-') m=-1; ch=getchar(); }
	while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*m;
}
void write(int x){//快输。
	if(x<0){ putchar('-'); write(-x); return; }
	if(x>=10) write(x/10);
	putchar(x%10+'0');
}
const int N=3.2e4;//上文提到过了。
map<int,int> Map;//记录超过 N 的质因子出现次数。
int p[N],a[100005],n,cnt,z[N];// p：质数 / a：输入数组 / z:小于 N 的质因子的出现次数。
bool f[N],flag;//判断素数及有无两数不互质。
signed main()
{
   for(int i=2;i<N;i++){//判断素数。
      if(!f[i]) p[++cnt]=i;
      for(int j=1;j<=cnt&&i*p[j]<N;j++){
         f[i*p[j]]=1;
         if(!(i%p[j])) break;
      }
   }
   for(int t=read();t;t--){
      Map.clear();//多测要清空。
      flag=0;//同上。
      for(int i=1;i<=cnt;i++) z[i]=0;//同上。
      n=read();//输入
      for(int i=1;i<=n;i++) a[i]=read();
      for(int i=1;i<=n;i++){
         for(int j=1;j<=cnt&&a[i]>=p[j];j++){//因数小于 N 的情况。
            if(a[i]%p[j]==0){
               z[j]++;//累计。
               while(a[i]%p[j]==0) a[i]/=p[j];//除干净。 
            }
         }
         if(a[i]>1){//还有别的因数。
            if(Map[a[i]]){//之前已经出现过了。
               flag=1;//记录答案。
               break;//结束。
            }
            Map[a[i]]=1;//打标记。
         }
      }
      for(int i=1;i<=cnt;i++){//每个素数枚举过去。
         if(z[i]>=2||flag){
            flag=1;
            break;
         }
      }
      puts(flag?"Yes":"No");//输出。
   }
   return 0;//完结撒花 qwq。
}

---

## 作者：include_BM (赞：2)

设 $V$ 为值域，本题中 $V=10^9$。

只用考虑最终找到的 $x$ 为质数的情况，因为若 $x$ 合法，那么 $x$ 的所有因数都合法。

1. 当 $x\le\sqrt{V}$ 时，这样的 $x$ 大概只有 $3000$ 多个，可以直接枚举每个 $x$，再枚举每个 $a_i$，若存在 $\ge2$ 个 $a_i$ 是 $x$ 的倍数，则 $x$ 合法。

2. 当 $x>\sqrt{V}$ 时，由于 $x$ 一定是某个 $a_i$ 的因数，而每个 $a_i$ 最多只有一个 $>\sqrt{V}$ 的质因数，若存在 $\ge2$ 个 $a_i$ 的 $>\sqrt{V}$ 的质因数相同，那么这个因数就是一个合法的 $x$。

```cpp
const int N=1e5+10,M=3.5e4+10;
int n,a[N],isp[M],pri[M],cnt,ans,num[M]; map<int,int> mp;

inline void preworks(){
    for(int i=2;i<M;++i){
        if(!isp[i]) pri[++cnt]=i;
        for(int j=1;j<=cnt&&i*pri[j]<M;++j){
            isp[i*pri[j]]=1;
            if(!(i%pri[j])) break;
        }
    }
}

signed main(){
    preworks();
    for(int T=read();T;--T){
        n=read(),mp.clear(),ans=0;
        for(int i=1;i<=n;++i) a[i]=read();
        for(int i=1;i<=n;++i){
            for(int j=1;j<=cnt&&pri[j]<=a[i];++j) // 处理 <=sqrt(V) 的因数。
                if(!(a[i]%pri[j])){
                    ++num[j];
                    while(!(a[i]%pri[j])) a[i]/=pri[j];
                }
            if(a[i]>1){
                // 剩下的就是那个大于 sqrt(V) 的因数。
                if(mp[a[i]]){ans=1;break;} mp[a[i]]=1;
            }
        }
        for(int i=1;i<=cnt;++i) ans|=(num[i]>=2),num[i]=0;
        puts(ans?"YES":"NO");
    }
    return 0;
}
```

---

## 作者：songge888 (赞：2)

### 题目大意

在一个序列 $a_i$ 中，寻找不互质的两个数。

### 思路

对每个数进行质因子分解，对质因子进行记录，如果有任意一个质因子出现两次及以上，则说明有至少两个数有共同的质因子，故存在两个数不互质。

题目说 $a_i \le 10^9 $，显然直接分解 $a_i$ 是不行的，但是 $\sqrt{10^9}\approx31623$ ，所以可以寻找 $[1,\sqrt{a_i}]$ 的质因子，最后一个比 $\sqrt{a_i}$ 大的进行特判就可以了。

### AC Code

```c++
#include<bits/stdc++.h>
#define bug cout<<"songge888"<<'\n';
#define int long long
using namespace std;
int t,sum[32222],prime[32222],vis[32222],cnt=0;
map<int,int>mp;//map存储质因子出现的次数 
void ola(){
    for(int i=2;i<=32220;i++){
        if(!vis[i]){
            prime[++cnt]=i;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=32220;j++){
            vis[i*prime[j]]=1;
            if(i%prime[j]==0){
                break;
            }
        }
    }
}
bool check(long long x){	
	for(int j=1;j<=cnt&&x>=prime[j];j++){
		if(x%prime[j]==0){
			if(mp[prime[j]]){//这个因子已经出现过了，直接返回即可 
				return 1;
			}
			mp[prime[j]]=1;
			while(x%prime[j]==0){
				x/=prime[j];
			}
		}
	}
	if(x>1){//进行特判 
		if(mp[x]){//同上 
			return 1;
		}
		mp[x]=1;
	}
	return 0;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>t;
	ola();
	while(t--){
		int n,a[100005];
		cin>>n;
		mp.clear();
		int flag=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			if(check(a[i])){
				flag=1;
			}
		}
		if(!flag){
			cout<<"No"<<endl;	
		}
		else{
			cout<<"Yes"<<endl;
		}
	}
	
	return 0;
}
```

---

## 作者：Polaris_Australis_ (赞：1)

题意：一个长度为 $n$ 的序列 $a_i$，问是否满足任意两个数都互质，$n\le10^5$，$1\le a_i\le10^9$。

提前筛出 $\le\sqrt{10^9}$ 的所有质数，对于这些质数逐个判断在哪些数中出现过，把这些质因子除去后剩余的部分一定是质数，对于剩下的这部分直接排序后看是否存在相邻两个相等。

代码：

```cpp
#include<bits/stdc++.h>
#define mem(x,y) memset(x,y,sizeof(x))
using namespace std;
namespace Std{
void gi(int &x){
	x=0;
	int y=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')y=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+(c&15);
		c=getchar();
	}
	x*=y;
}
const int N(31701);
int T,n,pr[N],cnt,a[100010];
bool np[N];
void main(){
	gi(T);
	for(int i(2);i<N;++i){
		if(!np[i])pr[++cnt]=i;
		for(int j(1);j<=cnt&&i*pr[j]<N;++j){
			np[i*pr[j]]=true;
			if(!(i%pr[j]))break;
		}
	}
	bool mark[cnt+10];
	while(T--){
		gi(n);
		mem(mark,0);
		for(int i(1);i<=n;++i){
			gi(a[i]);
		}
		bool ok(false);
		for(int i(1);i<=n;++i){
			bool yes(false);
			for(int j(1);j<=cnt;++j){
				if(!(a[i]%pr[j])){
					if(mark[j]){
						yes=true;
						break;
					}
					mark[j]=true;
					while(!(a[i]%pr[j]))a[i]/=pr[j];
				}
			}
			if(yes){
				puts("YES");
				ok=true;
				break;
			}
		}
		if(ok)continue;
		sort(a+1,a+1+n);
		for(int i(1);i<=n;++i){
			if(a[i]!=1){
				for(int j(i+1);j<=n;++j){
					if(a[j]==a[j-1]){
						ok=true;
						break;
					}
				}
				break;
			}
		}
		if(!ok)puts("NO");
		else puts("YES");
	}
}
}  // namespace Std
#undef int
int main(){
	Std::main();
	return 0;
}
```


---

## 作者：shinzanmono (赞：1)

# 题意：
给定一个长度为 $n$ 的数列 $arr$，询问该序列是否满足以下条件：

$\exists\ x \in \mathbb{N^+}, i, j\in[1, n], x|arr_i, x|arr_j $

# Solution:

我们发现 $arr_i$ 的值域为 $10^9$，$\sqrt{10^9}=3.16 \times 10^4$，且我们知道一个数 $x$ 最多有 $1$ 个大于 $\sqrt{x}$ 的质因子，所以我们考虑枚举质数。

使用一个 `std::map<int, int>`，这个 std::map 的 Key 作为质数，Value 作为这个质数的出现序列中的次数（稍后解释），循环遍历 $arr$ 数组，如果 $arr_i$ 的质因子中含有 $p_i$（第 $i$ 个质数），那么我们就可以给 $p_i$ 的出现次数 $+1$，最后循环遍历 std::map，看看有没有出现次数 $>1$ 的质数，如果有，我们输出 `YES`，否则我们输出 `NO`。

对于质数，我们可以使用线性筛，可以用暴力计算 $3.16\times10^4$ 中的质数只有 $3000$ 左右，完全可以保证时间复杂度。所以该算法的时间复杂度为 $\Theta(n\sqrt{U})$，其中 $U$ 表示 $arr_i$ 的值域。

# CODE:

```cpp
#include<iostream>
#include<map>
#include<cmath>
std::map<int, int> dict;
const int sz = 1e5 + 10;
bool numlist[sz];
int prime[sz], cnt;
void get(int n) {
    for (int i = 2; i <= n; i++) {
        if (!numlist[i])
            prime[++cnt] = i;
        for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
            numlist[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
        }
    }
} // 线性筛函数
int main() {
    std::ios::sync_with_stdio(false);
    int t;
    std::cin >> t;
    get(static_cast<int>(std::sqrt(1e9)));
    while (t--) {
        dict.clear();
        int n;
        std::cin >> n;
        while (n--) {
            int x;
            std::cin >> x;
            for (int i = 1; i <= cnt; i++) {
                if (x % prime[i] == 0) dict[prime[i]]++;
                while (x % prime[i] == 0) x /= prime[i];
            }
            if (x > 1) dict[x]++;
        }
        bool flag = false;
        for (auto i: dict) {
            if (i.second > 1) {
                std::cout << "YES\n";
                flag = true;
                break;
            }
        }
        if (!flag) std::cout << "NO\n";
    }
    return 0;
}
```

---

## 作者：COsm0s (赞：0)

先引出一个性质：对于任意非 $0$ 自然数 $n$，最多只能有一个质因子 $p\geq \sqrt n$。

下面给出证明。

若有两个及以上质因子 $p_1,p_2\cdots p_m$ 满足 $p_1\geq \sqrt n,p_2\geq \sqrt n,\cdots,p_m\geq \sqrt n$。

那么 $n\geq p_1p_2\cdots p_m\geq (\sqrt n)^m=n^{\frac{m}{2}}$。

显然 $m \geq 2$，所以 $n^{\frac{m}{2}}\geq n$。

所以整理得 $n>n$，与事实不符。

故对于任意非 $0$ 自然数 $n$，最多只能有一个质因子 $p\geq \sqrt n$。

现在我们设 $x$ 为 $a_i$ 的质因子。

+ 当 $x<\sqrt n$ 时，暴力记录 $x$ 在 $a$ 序列中的个数。

+ 当 $x \geq \sqrt n$ 时，由刚才性质可得最多只有一个这样的 $x$。那么 `map` 记录即可。

复杂度 $\Theta(n\sqrt {a_i})$。

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
const int N = 1e5 + 10, M = 3.5e4 + 10;
int n, a[N], flag[M], pri[M], cnt, ans, num[M];
map<int, bool> mp;
inline void preworks() {
	for (int i = 2; i < M; i ++) {
		if (!flag[i]) pri[++ cnt] = i;
		for (int j = 1; j <= cnt && i * pri[j] < M; ++j) {
			flag[i * pri[j]] = 1;
			if (!(i % pri[j])) break;
		}
	}
}
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	preworks();
	int T = 1;
	cin >> T;
	while(T --) {
		cin >> n, mp.clear(), ans = 0;
		for (int i = 1; i <= n; i ++) cin >> a[i];
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j <= cnt && pri[j] <= a[i]; j ++) 
				if (!(a[i] % pri[j])) {
					++ num[j];
					while (!(a[i] % pri[j])) a[i] /= pri[j];
				}
			if (a[i] > 1) {
				if (mp[a[i]]) {
					ans = 1;
					break;
				}
				mp[a[i]] = 1;
			}
		}
		for (int i = 1; i <= cnt; i ++) ans |= (num[i] >= 2), num[i] = 0;
		cout << (ans ? "YES" : "NO") << '\n';
	}
	return 0;
}
```
代码由 @Algae 提供。

---

## 作者：jasonliujiahua (赞：0)

# CFCF1771C

[题目传送门](https://www.luogu.com.cn/problem/CF1771C)
## 题意简述：
有 $T$ 组数据，每组数据给出 $n$ 和长度为 $n$ 的数列 $a_i$，判断有没有两个数不互质，如果有输出 $\text{YES}$，没有输出 $\text{NO}$。

$\sum n \le 10^5,a_i \le 10^9$。
## 题目分析：
可以将题意转化为：**判断该数列是否两两互质**（见昨天模拟赛的 [T3](https://www.luogu.com.cn/problem/P9473)）。

大体思路是：由于 $O(n^2)$ 枚举加 $\gcd$ 的复杂度为 $O(n^2\log n)$，显然无法通过，因此考虑将每个 $a_i$ 质因数分解，开一个桶记录 $a_i$ 的质因数是否在 $a_i$ 之前出现过。
### Step 1：质数预处理
线性筛（或者埃筛等）即可，范围见下。
### Step 2：分解质因数
考虑 $\sqrt{a_i}$ 以内的每一个质数 $p_j$，如果在 $a_i$ 之前 $p_j$ 就被桶标记过，说明 $a_i$ 之前存在 $a_k(k<i)$ 与 $a_i$ 共有一个质因数 $p_j$，即：$a_i$ 之前存在 $a_k$ 与 $a_i$ 不互质。但是还有问题，如果 $a_i$ 有 $\sqrt{a_i}$ 以外的质因数呢？设该数为 $x$，可以证明 $x$ 在 $a_i$ 中对应的指数 $c\le 1$。

证明：若 $c\ge2$，由于 $x > \sqrt{a_i}$，故 $x^c > a_i$。但由于 $x^c|a_i$ 必须 $x^c \le a_i$，故矛盾，故 $c \le 1$。

所以 $x^c=1(c=0)$ 或 $x^c=x(c=1)$。因此当 $a_i$ 除去所有 $\sqrt{a_i}$ 以内的质数后要么剩下 $1$，要么剩下的 $x$ 一定为质数。

根据以上分析，我们只需求出 $\sqrt{a_i}$ 以内的质数即可，故我们只用筛出 $\sqrt{\max{a_i}}=10^{4.5}$ 以内的质数。（$a_i$ 的值域为 $[1,10^9]$）
## 注意事项：
桶不能开 $\text{bool}$ 数组，可能 MLE，因此可以开一个 `map`。
## 参考代码：
```c++
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+10;
int t,n,sum,d,m,a[maxn],b[maxn],v[maxn],p[maxn],c[maxn],lc;
map<int,bool>w;//注意不能开bool数组（会MLE）
void prime()//线性筛
{
    for(int i=2;i<=maxn;i++)//其实maxn比10^4.5要大，不过多筛一点并不影响（懒得算10^4.5）
    {
        if(!v[i])
        {
            p[++sum]=i;//sum记录质数个数
            v[i]=i;
        }
        for(int j=1;j<=sum && i*p[j]<=maxn;j++)
        {
            v[i*p[j]]=p[j];
            if(i%p[j]==0) break;
        }
    }
}
void init()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=lc;i++) w[c[i]]=0;
    lc=0;
}
bool check(int i)
{
    for(int j=1;j<=sum && p[j]*p[j]<=a[i];j++)//分解质因数
    {
        if(a[i]%p[j]==0)
        {
            if(w[p[j]]) return false;
            w[p[j]]=1;
            c[++lc]=p[j];//用于清空桶
        }
        while(a[i]%p[j]==0) a[i]/=p[j];
    }
    if(a[i]!=1)//a[i]即上文x
    {
        if(w[a[i]]) return false;
        w[a[i]]=1;
        c[++lc]=a[i];
    }
    return true;
}
void work()
{
    bool ok=0;
    for(int i=1;i<=n;i++)
        if(!check(i)) ok=1;
    if(ok) cout<<"YES\n";
    else cout<<"NO\n";
}
int main()
{
    prime();//预处理质数
    cin>>t;
    while(t--)
    {
        init();
        work();
    }
    return 0;
}
```

---

## 作者：loser_seele (赞：0)

有一个很显然的做法：暴力分解质因数，然后统计是否有一个大于 $ 1 $ 的数出现超过一次。

但是暴力分解质因数的复杂度有些玄学，不一定保证能跑过，于是考虑用 Pollard-rho 分解质因数，于是做到了 $ \mathcal{O}(n^{\frac{1}{4}}) $ 的复杂度内分解质因数。

总时间复杂度 $ \mathcal{O}(n \times \max{a_i}^{\frac{1}{4}}) $，实际测试最慢的点跑到了 1.45s 以上，不过可以通过。

听说暴力分解也能过，不过复杂度劣一些，但因为 MR 常数较大所以差距不是很大。

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
ll gcd(ll a,ll b)
{
	return b?gcd(b,a%b):a;
}
ll lcm(ll a,ll b)
{
	return a/gcd(a,b)*b;
}
bool MR_check(ll a, ll p, ll s, int d) 
{
  ll k = pow(a, s, p);
  if (k == 1) return true;
  for (; d; --d, k = mul(k, k, p)) 
  {
    if (k == p - 1) 
    return true;
    if (k == 1) 
    return false;
  }
  return k == 1;
}
bool MR(ll x) 
{
  static const int cnt = 12;
  static const int p[cnt] = { 2, 3, 5, 7, 11, 13, 17, 19, 61, 2333, 4567, 24251 };
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
ll PR_check(ll c, ll p) 
{
  ll y = rand() % p, z = y;
  int k = 1, j = 0;
  while(1145141919810) 
  {
    z = (mul(z, z, p) + c) % p;
    ll t = gcd(p, std::abs(z - y));
    if (t > 1) 
    return t;
    if (++j == k) 
    y = z, k <<= 1;
  }
}
void factor_(ll x, std::vector<ll> &v) 
{
  if (x == 1) return;
  if (MR(x)) { v.push_back(x); return; }
  ll y = x;
  while (y == x) y = PR_check(rand() % x, x);
  factor_(y, v);
  factor_(x / y, v);
}
void factor(ll x, std::vector<ll> &v) 
{
  v.clear();
  factor_(x, v);
  std::sort(v.begin(), v.end());
  v.erase(std::unique(v.begin(), v.end()), v.end());
}
}
using Pollard_Rho::factor;
unordered_map<int,int>p;
signed main()
{
    int T;
    for(r(T);T;--T)
    {
    	int n;
        r(n);
        p.clear();
    	for(int i=1;i<=n;i++)
        {
        int x;
        r(x);
        vector<int>d;
        factor(x,d);
        for(auto x:d)
        p[x]++;
        }
        bool ok=1;
        for(auto x:p)
        if(x.second>1)
        {
        ok=0;
        cout<<"YES\n";
        break;
        }
        if(ok)
        cout<<"NO\n";
    }
}
```


---

## 作者：EBeason (赞：0)

# 题面翻译
问是否存在两个数不互质。
# 解法
对每个数进行一个质因数分解，如果分解的因数与之前的冲突，那么就存在两个数不互质。反之，则不存在。  
维护冲突用 map 就可以很好的实现。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned ll
#define int ll
#define ls p<<1
#define rs p<<1|1
#define lowbit(x) ((x)&(-x))
const int MaxN=1e6+100;
const int INF=1e9;
int N,M,T,a[MaxN],pd,q[MaxN],top;
map<int,int>mp;
template<class T>
inline void qread(T &sum)
{
    sum=0;int boo=1;
    char x=getchar();
    while(x<'0'||x>'9'){if(x=='-')boo=-1;x=getchar();}
    while(x>='0'&&x<='9'){sum=(sum<<1)+(sum<<3)+x-'0';x=getchar();}
    sum*=boo;
}
template<class T>
void qput(T x)
{
    if(x<0) {x=-x;putchar('-');}
    if(x>9){qput(x/10);}
    putchar(x%10+48);
}
inline ll mul(ll a,ll b,ll p)//快速乘
{
    ll x=(long double)a/p*b;
    return ((ull)a*b-(ull)x*p+p)%p;
}
inline ll ksm(ll x,ll y,ll p)
{
    ll res=1;
    while(y)
    {
        if(y&1) res=mul(res,x,p);
        x=mul(x,x,p);
        y>>=1;
    }
    return res;
}
ll gcd(ll x,ll y)
{
    if(y==0) return x;
    return gcd(y,x%y);
}
inline bool check(ll x)
{
    if(x==0||x==1) return 0;
    if(x==2) return 1;
    if(x%2==0) return 0;
    ll p=x-1,q=0;
    while(p%2==0) q++,p/=2;
    for(int i=1;i<=10;i++)
    {
        int a=rand()%(x-1)+1;
        ll v=ksm(a,p,x);
        if(v==1) continue;
        int j;
        for(j=1;j<=q;j++)
        {
            if(v==x-1) break;
            v=mul(v,v,x);
        }
        if(j>q) return 0;
    }
    return 1;

}
inline ll f(ll x,ll c,ll p)
{
    return (mul(x,x,p)+c)%p;
}
inline ll PR(ll n)
{
    if(n==4) return 2;
    ll x=rand()%(n-1)+1,y=x,c=rand()%(n-1)+1;
    x=f(x,c,n),y=f(f(y,c,n),c,n);
    for(int i=1;x!=y;i=min(i<< 1,128ll))
    {   
        ll cnt = 1;
        for(int j = 0 ; j <i; j ++) 
        {
            cnt =mul(cnt,abs(x - y),n);
            if(!cnt) break;
            x = f(x , c , n) , y = f(f(y , c , n) , c , n);
        }
        ll d = gcd(cnt , n);
        if(d != 1) return d;
    }
    return n;
}
void dfs(ll n)
{
    ll d=PR(n);
    while(d==n) 
    d=PR(n);
    ll d2=n/d;
    if(check(d))
	{
		q[++top]=d;
	}
    else dfs(d);
    if(check(d2))
	{
		q[++top]=d2;
	}
    else dfs(d2);
}
inline void Solve()
{
	mp.clear();
	qread(N);pd=0;
	for(int i=1;i<=N;i++)
	{
		qread(a[i]);
		if(pd==1||a[i]==1)	continue;
		if(check(a[i]))
		{
			if(mp[a[i]])
			pd=1;
			else
			mp[a[i]]++;
		}
		else
		{
			top=0;
			dfs(a[i]);
			for(int j=1;j<=top;j++)
			{
				if(mp[q[j]])
				pd=1;
			}
			for(int j=1;j<=top;j++)
			{
				mp[q[j]]++;
			}
		}
	}
	if(pd==1)
	printf("YES\n");
	else
	printf("NO\n");
}
signed main()
{
	qread(T);
	while(T--) Solve();
}
```

---

## 作者：紊莫 (赞：0)

考虑一个 $O(\dfrac{n\sqrt{V}}{\ln V})$ 的暴力算法。

首先筛出质数，然后对于每个 $a$，暴力分解质因数，时间复杂度 $O(\dfrac{\sqrt{V}}{\ln V})$，不筛质数的话复杂度就是根号，比较卡。

然后就做完了。

统计？直接使用 ``unordered_map``，此题不可能被卡。或者你用类似根号分治的思想，一部分直接数组存，另一部分用其他数据结构。

```cpp
const int N = 200005, M = 100000, inf = 0x3f3f3f3f, mod = 1e9 + 7;
int n, m, a[N], p[N], v[N];
void solve() {
  cin >> n;
  unordered_map<int, int> mp;
  F(i, 1, n) { cin >> a[i]; }
  F(i, 1, n) {
    for (int k = 1; (ll) p[k] * p[k] <= a[i]; k++) {
      int j = p[k];
      if (a[i] % j == 0) {
        if (mp.count(j)) {
          cout << "YES\n";
          return;
        }
        mp[j] = 1;
        while (a[i] % j == 0) a[i] /= j;
      }
    }
    if (a[i] > 1) {
      if (mp.count(a[i])) {
        cout << "YES\n";
        return;
      }
      mp[a[i]] = 1;
    }
  }
  cout << "NO\n";
}
signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  for (int i = 2; i <= M; i++) {
    if (!v[i]) p[++m] = i;
    for (int j = 2; j * i <= M; j++) {
      v[i * j] = 1;
    }
  }
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
```


---

