# Vasya's Function

## 题目描述

Vasya正在学习数论。他定义了一个函数f(a, b)：
### 
f(a, 0) = 0;
f(a, b) = 1 + f(a, b – gcd(a, b)),gcd(a, b)就是a和b的最大公因数。

Vasya有两个数字x和y，并且他想要算出f(x,y)的值。他想要自己去算，但发现可能会需要很长的时间。所以他向你求助，请你给出一个能够快速得出答案的程序。

## 样例 #1

### 输入

```
3 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
6 3
```

### 输出

```
1
```

# 题解

## 作者：_liuyi_ (赞：7)

~~感谢[同学](https://www.luogu.com.cn/user/730883)帮我推式子%%%。~~
# 思路
本题有个重要的性质：

$f(a,b)=f(\frac{a}{\gcd(a,b)},\frac{b}{\gcd(a,b)})$。

证明：

我们令 $d=\gcd(a,b)$。

因为 $d \mid b$，所以 $d \mid b-d$，又因为 $d \mid a$，因此可以得出后面 $b$ 减的数一定是 $\ge d$ 的，并且这个数一定是 $d$ 的倍数。

我们可以把 $b$ 看成 $d \times \frac{b}{d}$，令每次减的数为 $l$，那么实际上 $b$ 的变化为 $d \times (\frac{b}{d}-\frac{l}{d})$，那么当括号里的这一坨为 $0$ 时，$b$ 就为 $0$，那么这个东西就构成了一个子问题。

大概证明了一下性质后，我们要特判一下 $\gcd(a,b)=1$ 的情况，这时我们要找到一个最大的数 $l$，满足 $l\le b$，$l\mid a$。方法也不是很难枚举一下 $a$ 的质因数，然后取个下整就可以了，具体看代码，复杂度时 $a$ 质因子个数的平方加个分解质因数，大概是 $O(\sqrt a+\log_2^2a)$。

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
typedef vector<int> VI;
typedef unsigned long long ull;
typedef	double db;
template<typename T> inline void cmax(T &a,const T b){if(a<b) a=b;}
template<typename T> inline void cmin(T &a,const T b){if(a>b) a=b;}
template<typename T> inline T gcd(T a,T b){return b?gcd(b,a%b):a;}
template<typename T> inline T lcm(T a,T b){return a/gcd(a,b)*b;}
const int N=1e6+10;
const int mod=1e9+7;
//const int mod=998244353;
ll a,b,num[N],ans;
int cnt,p[N];
inline void f(ll a,ll b){
	if(!b) return;
	ll mx=0;
	int id=0;
	rep(i,1,cnt){
		if(b<num[i]) break;
		if(!p[i]) continue;
		if(mx<b/num[i]*num[i]) mx=b/num[i]*num[i],id=i; 
	}
	if(!id){
		ans+=b;
		return;	
	} 
	ans+=b-mx;
	p[id]--;
	f(a/num[id],b/num[id]);
}
inline void solve(){
	scanf("%lld%lld",&a,&b);
	ll tmp=a;
	rep(i,2,sqrt(tmp)){
		if(tmp%i==0){
			cnt++;
			num[cnt]=i;
		}
		while(tmp%i==0){
			p[cnt]++;
			tmp/=i;
		}
	}
	if(tmp!=1) p[++cnt]++,num[cnt]=tmp;
	f(a,b);
	printf("%lld",ans);
}
int main(){
	int T=1;
	//scanf("%d",&T);
	while(T--) solve();
}
```


---

## 作者：Daniel_yuan (赞：2)

按照题意，有 $f(a,b)=1+f(a,b-gcd(a,b))$，可以发现每次 $b$ 的减少量都是 $gcd(a,b)$。那么 $b$ 和 $a$ 的比值每次会从 $\frac{a}{b}$ 变成 $\frac{a}{b-gcd(a,b)}$ ，约分一下发现这个和 $\frac{\frac{a}{gcd(a,b)}}{\frac{b}{gcd(a,b)}-1}$ 是一样的。所以我们有了一个很好的性质：$f(a,b)=f(\frac{a}{gcd(a,b)},\frac{b}{gcd(a,b)})$。~~这部分的证明可能有点糊……~~

那么我们现在就只需要考虑 $f(a,b)$（ $a$，$b$ 互质）经过几次操作后 $gcd(a,b)\not=1$ 。（ 也就是找到一个小于 $b$ 的最大的 $k$ 使得 $gcd(a,k)\not=1$ ）

考虑枚举所有 $a$ 的质因子 $p$，通过数学方法计算出小于 $b$ 的最大的 $p$ 的倍数，把所有的倍数取最大值，设其为 $k$，那么这个 $k$ 就是小于 $b$ 的最大的 $k$ 使得 $gcd(a,k)\not=1$。

那么之后就直接把 $b$ 跳到这个 $k$，答案的增量就是 $b-k$，再把 $a,b$ 同时除掉 $gcd(a,b)$ ，如此反复，直到 $b=0$ 。

由于一开始需要求 $a$ 的所有质因子，计算的时候每次需要枚举所有 $a$ 的质因子，一共枚举质因子个数次，那么总复杂度可以看成 $O(\sqrt{a}+\log_2^2a)$。

```cpp
#include <bits/stdc++.h>
#define RI register int
typedef long long LL;
#define int LL

using namespace std;

int const MAXN = 1e6 + 5;
int Notprime[MAXN], Prime[MAXN], tot;
int stk[MAXN], tong[MAXN], top;

void Euler(int Max) {
  for (RI i = 2; i <= Max; ++i) {
    if (!Notprime[i]) Prime[++tot] = i;
    for (RI j = 1; j <= tot && i * Prime[j] <= Max; ++j) {
      Notprime[i * Prime[j]] = 1;
      if (i % Prime[j] == 0) break;
    }
  }
}

signed main() {
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
  Euler(1e6);
  LL x, y;
  cin >> x >> y;
  
  LL sq = sqrt(x * 1.0), tmp = x;
  for (RI i = 1; Prime[i] <= sq && i <= tot; ++i) {  // 对 x 质因数分解
    int cnt = 0;
    while (tmp % Prime[i] == 0) ++cnt, tmp /= Prime[i];
    if (cnt) stk[++top] = Prime[i], tong[top] = cnt;
  }
  if (tmp != 1) stk[++top] = tmp, tong[top] = 1;
  
  LL ans = 0;
  while (666) {
    
    LL mmax = 0, pos = 0;
    for (RI i = 1; i <= top; ++i) // 求出小于 y 的最大的 k 使得 gcd(x,k)≠1
      if (tong[i]) {
        tmp = y / stk[i] * stk[i];
        if (tmp > mmax) mmax = tmp, pos = i;
      }
    
    ans += y - mmax;
    y = mmax;
    if (!y) break;
    --tong[pos];
    x /= stk[pos];
    y /= stk[pos];
  }
  cout << ans << endl;
  return 0;
}


```

---

## 作者：Crazyouth (赞：1)

## 分析

注意到在函数递归时，$a$ 的值不会改变，于是若某次递归后 $\operatorname{gcd}(a,b)$ 的值变化了，那么只能是变为它的倍数，所以每次 $\operatorname{gcd}(a,b)$ 都至少乘二，并且始终不超过 $a$，所以其最多变化 $\log a$ 次。而由于 $a$ 的因数个数不超过 $\sqrt a$，则我们可以在每一次 $\operatorname{gcd}$ 变化时统计下一次 $\operatorname{gcd}$ 的变化位置。$\operatorname{gcd}$ 不再变化的充要条件是 $b$ 为 $a$ 的倍数（包括 $b=0$），因此这样做的复杂度是 $O(\sqrt a\times \log a)$。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<int> fac;
vector<pair<int,int>> nxt; 
signed main()
{
	int a,b;
	cin>>a>>b;
	for(int i=1;i*i<=a;i++)
	{
		if(a%i==0)
		{
			fac.push_back(i);
			if(a/i!=i) fac.push_back(a/i);
		}
	}
	sort(fac.begin(),fac.end());
	int now=__gcd(a,b),ans=0;
	while(b&&b!=a)
	{
		if(b%a==0)
		{
			cout<<b/a+ans;
			return 0;
		}
		nxt.clear();
		for(auto i:fac) if(i>now&&i%now==0) nxt.push_back({b/i*i,i});
		sort(nxt.begin(),nxt.end(),greater<pair<int,int>>());
		ans+=(b-nxt[0].first)/now;
		now=nxt[0].second;
		b=nxt[0].first;
	}
	cout<<ans+(b==a);
}

---

## 作者：stansxt (赞：1)

# 前言
- 这道题不是很难，也没什么代码量，感觉差不多是一个橙题。
- 题解目前只有一篇，那我就来一发吧~
---
# 思路

- 纯暴力就没什么好说的了，直接按题意递归。最坏情况下应该是$O(m\times\log_2m)$的。~~我试过，只能过两个点QwQ~~
- 这道题的意思其实是给定$a$、$b$，$b$每次减少$\gcd(a,b)$，问多少次减到0。
- 设$d=\gcd(a, b)$，$\because d|b$, $\therefore d|b-d$。
- 而$a$是不变的，因此恒有$d|a$。
- 由于要求的是减了多少次，那么我们很自然的想到可以把减数与被减数同时除以$d$。当然，为了保证之后的$d$不出现错误，$a$也要除$d$。
- 有了这个性质，我们发现$b$每次减小的数都变成了1。不难发现我们的操作变成了把$b$减去一个数再除以一个数再减去一个数再除以一个数……一直到$b$变成$0$。
- 那么我们为了降低复杂度，肯定需要知道每次减少多少，然后一下减完。
- 也就是说，当前的$b$(与$a$的$\gcd$为1的)减去多少后与$a$的$\gcd$不再为1。
- 注意到这题另一个很好的特点就是$a$不会变，那么$\gcd(a,b)$一定是$a$的因数。我们做的时候，每次只需考虑一个预处理出的质因数（该因数除完后若$\gcd$仍不为1还可以继续除）。
- 那么每次$b$要变成的数就是$<b$ 的最大的与$a$有$\gcd$的数。也就是说要减掉一个 __最小__ 的数，使得减完与$a$不互质。
- 显然，所要减的便是 __$b$对所有$a$的质因数的余数中最小的__ 。
- $a$的质因数最多只可能有$\log$个，所以我们可以每次去删除一个$a$的质因数，然后再逐一寻找被$b$除的余数最小的那个继续删。注意$a$可能比$b$大很多，所以$b$减到1后就可以$break$了。
- 还有一个细节，如果某时刻$a$变成1了（大家可以自己想一下什么时候会出现这种情况），而$b$还不是1，这时候循环会结束，那么我们需要在$ans$上额外加$b$（因为此时$\gcd$一定是一）。
- 另外我代码里的$sort$其实不需要，因为我们只需要找当前最小的，后面的不需要排序。
- 再加上预处理$a$的质因数，我的复杂度是$O(\sqrt a+\log_2^2a\times\log_2\log_2a)$，但是其实最后那个是可以去掉的。~~不过，去不去问题也不大，1e12取完两次log只有6、7的样子，跑的依然挺快的www。~~

# 代码
```
//CF837E Vasya's Function
//submit 1 
//By sxt on 2020.8.26 
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<queue>
#include<algorithm>
#define rg register int
#define il inline
#define is_(x) (x<='9'&&x>='0')
#define mid (l + r >> 1)
#define el else if
#define lowbit(x) (x&(-x))
#define Mem(x) memset(x, 0, sizeof(x))
#define in read()
#define _num (ch<='9'&&ch>='0')
#define int long long
using namespace std;
const int N = 23;
il int read(){
	int x=0,f=1;
	char ch=getchar();
	while(!_num){
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(_num){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
char f[11];
int pcnt;
il void pint(int x){
	pcnt = 0;
	if(x == 0) putchar('0');
	if(x < 0){
		x = -x;
		putchar('-');
	}
	while(x){
		f[++pcnt] = x % 10 + '0';
		x /= 10;
	}
	while(pcnt) putchar(f[pcnt--]);
	putchar('\n');
}
int n, m, pc, ls, ans;
struct node{
	int num;
	int mo;
	int id;
}mo[N];
bool operator<(const node&x, const node&y){return x.num < y.num;}
signed main()
{
//	freopen("1.txt", "r", stdin);
//	freopen("3.txt", "w", stdout);
	n = in, m = in;
	ls = n;
	for(rg i = 2; i <= sqrt(ls); ++ i)if(!(ls % i)){
		mo[++pc].mo = i;
		for(; !(ls % i); ls /= i);
		mo[pc].id = pc;
		mo[pc].num = m % i;
	}
	if(ls != 1) mo[++pc] = (node){m % ls, ls, pc};
	ls = 1;
	sort(mo+1, mo+pc+1);
	for(rg i = 1; i <= pc; ++ i){
		ans += mo[i].num;
		n /= mo[i].mo, m /= mo[i].mo;
		if(m == 1) break;
		ls = mo[i].mo;
		if(!(n % mo[i].mo))	-- i;
		for(rg j = i + 1; j <= pc; ++ j)
			mo[j].num = m % mo[j].mo;
		sort(mo+i+1, mo+pc+1);
	}
	if(!(m-1)) ++ ans;
	el(!(n-1)) ans += m;
	pint(ans);
    return 0;
}

```

---

## 作者：Priestess_SLG (赞：0)

可以证明下面的等式成立：

$$
f(a,b)=f(a/\gcd(a,b),b/\gcd(a,b))
$$

于是问题就变得简单了。首先先对 $a,b$ 进行操作直到 $\text{gcd}(a,b)=1$ ，然后分类讨论：

+ 若此时 $b=0$，则无需进行任何操作，返回 $0$ 。
+ 若此时 $b=1$，则只需要进行一次操作，返回 $1$ 。
+ 否则，需要一直执行 $b$ 减少 $1$ 的操作，直到第一次 $\text{gcd}(a,b)\neq 1$ 。找到第一个这样的 $b$ 是容易的。只需要对 $a$ 分解质因数，枚举 $a$ 的每一个质因子，并计算至少需要减少多少次，才可以使得 $b$ 是这个质因子的倍数。将上述所有答案取 $\min$ 就是该部分的答案。

可以证明，每一次操作结束后， $a,b$ 两数都要同时除以 $\text{gcd}(a,b)$ ，而操作完后 $\gcd(a,b)$ 至少为 $2$，也就是说最多执行 $O(\text{gcd}\max(a,b))$ 次操作， $b$ 元素的值就会 $\le 1$ 。直接暴力模拟就可以通过该问题。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    cerr << fixed << setprecision(5);
    int x, y;
    cin >> x >> y;
    if (!y) cout << "0\n";
    else if (y == 1) cout << "1\n";
    else if (x == 1) cout << y << '\n';
    else {
        int g = __gcd(x, y);
        x /= g, y /= g;
        if (y == 1) cout << "1\n";
        else {
            int cnt = 0;
            while (y > 1) {
                vector<int> div;
                int xx = x;
                for (int i = 2; i * i <= xx; ++i)
                    if (xx % i == 0) {
                        while (xx % i == 0) xx /= i;
                        div.emplace_back(i);
                    }
                if (xx > 1) div.emplace_back(xx);
                int res = 1e18;
                for (int &i : div) res = min(res, y % i);
                cnt += res;
                y -= res;
                int g = __gcd(x, y);
                x /= g, y /= g;
                if (x == 1) {
                    cnt += y;
                    y = 2;
                    break;
                }
            }
            if (y == 1) ++cnt;
            cout << cnt << '\n';
        }
    }
    return 0;
}
```

---

