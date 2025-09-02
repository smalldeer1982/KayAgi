# [PumpkinOI Round 1] 瓦解

## 题目背景

> 时间把镜头带走 不假思索 回忆不放手

## 题目描述

你手上有一个长为 $n$ 的数列 $a$。小 Q 想让你将其分成不超过 $m$ 段**非空**连续段，且每段内数字**严格单调递增**。现在小 Q 想知道一共有几种划分方案。由于方案数可能很大，你只需要告诉她方案数对 $998244353$ 取模的结果。

## 说明/提示

### 样例解释

- 对于第一组数据，只有 $[2,3],[1]$ 这一种方案。

### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 0（0 pts）：样例。
- Subtask 1（10 pts）：$\sum n\le 10$。
- Subtask 2（20 pts）：$\sum n\le 1000$。
- Subtask 3（10 pts）：保证数列本身严格单调递增。
- Subtask 4（30 pts）：$\sum n\le 10^6$。
- Subtask 5（30 pts）：$\sum n\le 10^7$。

对于所有数据，保证 $1\le \sum n\le 10^7,1\le m\le n,1\le a_i\le 10^9$。

## 样例 #1

### 输入

```
2
3 2
2 3 1
10 5
7 10 9 23 1 6 7 8 9 20```

### 输出

```
1
29```

# 题解

## 作者：ztd___ (赞：10)

你点开了题目。

题目中的“方案数对 $998244353$ 取模的结果”，都无时无刻不在告诉你：这是道计数题。

但是你会不了一点计数。你只学过组合数和 DP，对其他内容一无所知。

你伤心透顶，却看见榜上过题的人数正在飞快增长，大家用行动提醒你：这题并不难。

看着 $10^7$ 的数据范围，你认为这题正解一定是线性，而目前自己学过的线性计数算法只有 DP 了。你用你敏锐的目光发现了 $n$ 和 $m$ 两个字母。

“有 $n$ 和 $m$，那大概率是 DP 了。”但是你忘了，组合数的标准形式就是 $C_n^m$。

思考正解无果，你决定思考部分分。~~思考部分分无果后，~~ 你回想起之前自己做过的一些 DP 题目和有关套路，突发奇想，想到了该如何设计状态。

“部分分做法可以先不用在意复杂度吧，那完全可以用 $dp_{i,j}$ 表示前 $i$ 个数字分成 $j$ 段的方案数啊！然后当 $a_i \le a_{i-1}$ 时，必须单独分段，即 $dp_{i,j} = dp_{i-1,j-1}$，否则可以多分一段，即 $dp_{i,j} = dp_{i-1,j}+dp_{i-1,j-1}$，最后注意一下边界不就好了？”

你兴高采烈，写完代码提交上去，却只有可怜的 30pts。你汗流浃背了。你分析复杂度，发现是 $O(nm)$。那肯定过不了了啊。

你非常慌张，一直思考怎么将问题化为一维。思考无果。你以 30pts 的好成绩退下了比赛。

赛后，你观看了题解。

“哎哎哎不是，这怎么是组合数啊？？？”

你悲痛万分，为自己在 DP 上花费的 2h+ 而心如刀绞。

痛定思痛。你决定仔细研究一下这题。

你发现这题转化后就是典型的组合数。

将问题转化为从若干个间隔里选若干个间隔的方案，然后再去掉必须隔开的 $a_i \le a_{i-1}$ 的情况（设其个数为 $cnt$），总间隔数就是 $n - 1 - cnt$，可选择的间隔数可以从 $0$ 到 $m - 1 - cnt$ 枚举，将答案相加即可。$cnt$ 完全可以线性处理。

形式化地，就是求出：
$$\sum_{i=0}^{m-1-cnt} C_{n-1-cnt}^{i}$$

发现这题确实这么简单，你心中更难受了。

你决定先把框架写了。
```cpp
void _solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	int cnt = 0, ans = 0;
	for (int i = 2; i <= n; i++) {
		if (a[i] <= a[i - 1]) cnt++;
	}
	for (int i = 0; i <= m - cnt - 1; i++) {
		ans = (ans + C(n - 1 - cnt, i)) % MOD;
	}
	if (cnt > m - 1) cout << 0 << "\n";
	else cout << ans << "\n";
}
```

正当你准备写组合数部分时，你突然发现组合数没法算，用杨辉三角递推太慢了，只能用阶乘直接算。即：

$$C_n^m = \frac{n!}{(n-m)! \times m!}$$

阶乘可以线性预处理，但除法呢？众所周知，在模意义下不能直接算除法啊。

你想到了一个东西：[乘法逆元](https://oi-wiki.org/math/number-theory/inverse/)。

仔细学习了若干小时后，你学会了线性递推求乘法逆元！

你开始写代码，然后又发现了问题：阶乘取模后可能还是很大，线性递推推不到那么大。

你仔细地推了一段公式，其中 $inv_i$ 表示 $i$ 在模 $998244353$ 意义下的逆元：

>$\because i! = (i - 1)! \times i$
>
>$\therefore inv_{i!} = inv_{(i-1)! \times i}$
>
>根据同余易得：$inv_{(i-1)! \times i} = inv_{(i-1)!} \times inv_{i}$
>
>所以 $inv_{i!} = inv_{(i-1)!} \times inv_i$

感觉推了跟没推一样啊！但是你发现这个结论确实不需要很难的推理，而且 $1! = 1$ 没有变化，所以可以直接从 $1$ 开始推。你决定开始写代码。

其中，你为了节省空间，决定用预处理过的 $inv$ 数组直接处理 $i!$ 的逆元。阶乘数组求组合数时需要用来表示分子 $n!$，但是逆元数组没有用处，所以可以直接在逆元数组 $inv$ 上推。

你写出了预处理代码。
```cpp
const int N = 1e7 + 77;
const int MOD = 998244353;
int inv[N], fac[N], n, m, a[N];
void _init() {
	inv[0] = inv[1] = fac[0] = fac[1] = 1;
	for (int i = 2; i <= 1e7; i++) {
		inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
		fac[i] = fac[i - 1] * i % MOD;
	}
	for (int i = 2; i <= 1e7; i++) {
		inv[i] = inv[i - 1] * inv[i] % MOD;
	}
}
```

然后你发现组合数的计算就一行，算上框架也才三行，所以把它写了出来。
```cpp
int C(int n, int m) {
	return fac[n] * inv[n - m] % MOD * inv[m] % MOD;
}
```

然后你发现将上述代码块拼起来，加个 `main` 函数和头文件啥的就 [AC](https://www.luogu.com.cn/record/200597688) 了。
```cpp
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	_init();
	int T;
	cin >> T;
	while (T--) _solve();
	return 0;
}
```

你发现自己还是太菜了。

---

## 作者：封禁用户 (赞：7)

首先把必须分段的地方无脑分段，即 $a_i \ge a_{i + 1}$ 时。

发现其他地方可以随便分，因为上面分好以后其他段都是有序的。

组合数求一下即可，感觉没有绿。

---

## 作者：2022_37_yzyUUU (赞：6)

# P11616 题解

# 题目描述

你手上有一个长为 $n$ 的数列 $a$ 。小 Q 想让你将其分成**不超过
$m$ 段**非空连续段，且每段内数字**严格单调递增**。现在小 Q 想知道一共有几种划分方案。由于方案数可能很大，你只需要告诉她方案数对 
$998244353$ 取模的结果。

## 思路

首先想一下它最少要分成几段，是不是它每次一个数比上一个数小或者等于上一个数，即不满足单调递增，那样我们就不得不再分一段，我们把分的次数设为 $cnt$，这是第一种情况。

不过由于分 $cnt$ 次，实际得到的是 $cnt+1$ 块，若是连最少分的段数都比 $m$ 大，那么输出 $0$ 。

否则考虑剩余分 $cnt+1$ 到 $m-1$ 次的情况，设这个次数为 $i$ ，由于总的空数是 $n-1$ 个，而其中已经有 $cnt$ 个空固定了，因此我们要把 $i-cnt$ 个东西分到 $n-1-cnt$ 个空里，显而易见是 $C(n-1-cnt,i-cnt)$ 。组合数的求法就不再赘述了。

## 代码

```cpp
#include<bits/stdc++.h>
#define P 998244353
#define int long long
using namespace std;
int T,ans;
int n,m,cnt;
int a[10000007];
int mul[10000007];
int qpow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=(ans*a)%P;
		a=(a*a)%P;
		b>>=1;
	}
	return ans%P;
}
int C(int n,int m){
	return (mul[n]*(qpow((mul[m]*mul[n-m])%P,P-2)%P))%P;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;mul[0]=1;
	for(int i=1;i<=10000000;i++){
		mul[i]=(mul[i-1]*i)%P;
	}
	while(T--){
		cin>>n>>m;cnt=ans=0;
//		,ans=1;
		for(int i=1;i<=n;i++){
			cin>>a[i];		
			if(a[i]<=a[i-1]){
				cnt++;
			}
		}
		for(int i=cnt;i<m;i++){
			ans=(ans+C((n-1)-(cnt),i-cnt))%P;
		}
		cout<<ans<<"\n";
	}
}
```

## 谢谢观看，如果有帮助能点个赞吗

---

## 作者：chenly8128 (赞：5)

### 题解

最多分成 $m$ 段非空连续段，等价于选择 $m-1$ 个不重合的分割点。

为了满足严格单调的条件，递减（或相等）的连续两个数之间**必须**要有一个分割点。因此只有**剩下的分割点可以在剩下的间隔中任意选择**。设必须要有的分割点有 $cnt$ 个。则总的可能数为 $ans = \sum_{i=0}^{m-1-cnt} C_{n-1-cnt}^{i}$。组合数可以递推累加。复杂度为 $O(\sum_{}n)$。

### 代码
```cpp

// Author: chenly8128
// Created: 2025-01-25 13:49:52

#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
inline int read(void) {
	int res = 0;bool flag = true;char c = getchar();
	while (c < '0' || c > '9') {flag ^= (c == '-');c = getchar();}
	while (c >= '0' && c <= '9') {res = (res << 3) + (res << 1) + (c ^ 48);c = getchar();}
	return flag ? res : -res;
}
long long qpow (long long x,int k) {
	long long ans = 1;
	while (k) {
		if (k&1) ans = ans * x % mod;
		x = x * x % mod;
		k >>= 1;
	}
	return ans;
}
int main (void) {
	int T = read();
	while (T--) {
		int n = read();int m = read()-1,x,last = -0x3f3f3f3f;
		int cnt = 0;
		for (int i = 1;i <= n;i++) {
			x = read();
			if (x <= last) cnt++;
			last = x;
		}
		if (cnt > m) {
			printf ("0\n");
			continue;
		}
		long long ans = 1,now = 1;
		for (int i = 1;i <= m-cnt;i++) {
			now = now * (n-cnt-i) % mod * qpow(i,mod-2) % mod;
			ans += now;
		}
		printf ("%d\n",ans % mod);
	}
	return 0;
}
```

---

## 作者：Lyw_and_Segment_Tree (赞：5)

## 开始解题！

组合数好题。

拿样例举例，就比如 $n = 10, m = 5, a = [7, 10, 9, 23, 1, 6, 7, 8, 9, 20]$ 时，我们先把这个数列分成最少的严格单调递增的连续子序列，即 $[7, 10], [9, 23], [1, 6, 7, 8, 9, 20]$。

那么接下来怎么做呢？

仍然以上面的样例举例，我们发现答案至少是 $3$，所以先将 $m$ 减去 $3$，如果此时 $m < 0$，那么无法做到，输出 $0$。

否则，若减完之后 $m = 0$，说明与我们上面的分法刚好一样，并且有且仅有这一种分法。输出 $1$。

讨论完了上面两种特殊情况，我们来考虑一般情况。

首先我们发现，要想继续往下分，就相当于要拿几块隔板来划分。

设 $siz_i$ 表示我们分出来的第 $i$ 个连续子序列的大小。

可以发现，第 $i$ 个连续子序列算上头尾就会有 $siz_i + 1$ 个空格，然后这个子序列的头尾不能被划分，所以实际只有 $siz_i - 1$ 个空格来放隔板，而 $\sum siz_i = n$。

所以，我们只需要求出最少的严格单调递增的连续子序列数量 $cnt$，答案就即为 $1 + \sum \limits _ {i = 1} ^ {m - cnt} C _ {n - cnt} ^ {i}$，注意原本的 $cnt$ 个也是一个答案，而组合数用逆元进行求解即可。

而 $cnt$ 求解是简单的，直接判断有多少个 $a _ i \le a _ {i - 1}$ 然后累加即可。

code : 

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define endl "\n"

namespace fastio {
	char buf[1 << 21], *p1 = buf, *p2 = buf;
	
	const ll getc() {
	    return p1 == p2 && ( p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1 ++;
	}
	
	const ll read() {
		ll x = 0, f = 1;
		
		char ch = getc();
		
		while (ch < '0' || ch > '9') {
			if (ch == '-') f = -1; ch = getc();
		}
		
		while (ch >= '0' && ch <= '9') {
			x = (x << 1) + (x << 3) + (ch ^ 48), ch = getc();
		}
		
		return x * f;
	}
	
	const void write(ll x) {
		if (x < 0) {
			putchar('-'), x = -x;
		}
		
	    ll sta[35], top = 0;
	    
	    do {
	        sta[top++] = x % 10, x /= 10;
	    } while (x);
	    
	    while (top) putchar(sta[--top] + 48);
	}
}

using namespace std;

#define read fastio::read
#define write fastio::write 

const ll mod = 998244353;

ll T, n, m, a[10000005], fac[10000005], inv[10000005];

ll cal(ll n, ll m) {
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}

void solve() {
    n = read(), m = read();
    
    ll now = m;
    
    ll cnt = 1;
    
    for (ll i = 1; i <= n; i++) {
        a[i] = read();
    }
    
    for (ll i = 2; i <= n; i++) {
        if (a[i] <= a[i - 1]) cnt ++;
        // cout << cnt << " ";
    }

    // cout << cnt << endl;
    
    ll ans = 1;
    
    if (m - cnt < 0) {
        write(0), puts("");
        return ;
    }

    if (m - cnt == 0) {
        write(1), puts("");
        return ;
    }
    
    for (ll i = 1; i <= m - cnt; i++) {
        ans += cal(n - cnt, i);
    }
    
    ans %= mod;
    
    write(ans), puts("");
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(0), cout.tie(0);
    
    
    T = read();
    
    fac[0] = fac[1] = 1, inv[0] = inv[1] = 1;

    for (ll i = 2; i <= 10000000; i++) {
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = (mod - inv[mod % i] * (mod / i) % mod) % mod; 
    }

    for (ll i = 2; i <= 10000000; i++) inv[i] = inv[i] * inv[i - 1] % mod;

    while (T--) {
        solve();
    }
}
```

[AC record](https://www.luogu.com.cn/record/200579495)

---

## 作者：_Deer_Peach_ (赞：4)

一个长度为 $n$ 的序列分成**不超过** $m$ 段，使每段都**严格单调递增**，求分割的方案数。答案对 $998244353$ 取模。

思路：

当有相邻两个数不满足**严格单调递增**，则必须分割。分不超过 $m$ 段即在不超过 $m-1$ 处分割，设必须分割处的数量为 $cnt$，则还需要分 $0$ 到 $m-1-cnt$ 处，组合数学算出方案数，注意取模和预处理逆元。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
const int N=1e7,Mod=998244353;
int t,n,m,a[N+1],b[N+1],c[N+1];
int C(int x,int y){
	return b[x]*c[y]%Mod*c[x-y]%Mod;
}int Pow(int x,int y){
	int res=1;while(y){
		if(y&1)(res*=x)%=Mod;
		y>>=1;(x*=x)%=Mod;
	}return res%Mod;
}signed main(){
    IOS;b[0]=1;for(int i=1;i<=N;i++)b[i]=(b[i-1]*i)%Mod;
	c[N]=Pow(b[N],Mod-2);
	for(int i=N-1;i>=0;i--)c[i]=(c[i+1]*(i+1))%Mod;//预处理
	cin>>t;while(t--){
    	cin>>n>>m;int ans=0;
    	for(int i=1;i<=n;i++)cin>>a[i];
    	int cnt=0;
    	for(int i=1;i<n;i++)if(a[i]>=a[i+1])cnt++;//记录必须分割的数量
		for(int i=cnt;i<m;i++){//枚举剩余部分
			int x=n-1-cnt;
			int y=i-cnt;
			(ans+=C(x,y)%Mod)%=Mod;//用组合数算出答案
		}cout<<ans<<endl;
	}return 0;
}
```

---

## 作者：wizard（偷开O2 (赞：4)

一道组合数的好题。

## 题意

把一个长为 $n$ 的无序序列 $A_{n}$ 分割成不超过 $m$ 个非空段，保证分割的每一段单调递增，求方案数。

## 分析

转化题意，本质上就是从 $n-1$ 个间隙中挑选 $m-1$ 个间隙且满足分割区间单调递增的方案数。

为了保证区间单调，在满足 $A_{i} \ge A_{i+1}$ 时，必须分割 $i$ 和 $i+1$ 处。

假设我们保底要切割 $dex$ 处，那么你的剩余切割次数就变成了 $m-dex-1$，也就是说，要从 $n-dex-1$ 个空隙中最多选择 $m-dex-1$ 个空隙切割的方案数目。

所以答案为 $$\sum_{i=0}^{m-dex-1} C_{n-dex-1}^i$$。

求个逆元，组合数求解即可。

记得快读。可以扔一个我写过的东西 [组合数笔录](https://www.luogu.com.cn/article/y49px6kk)。

## 代码

```cpp
//ways:
//orz aqx wvr zak 
//noip 2024 rp++ 
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ls ((now<<1))
#define rs ((now<<1)|1)
#define mid ((l+r)>>1)
#define checkbug cout << "okok" << endl;
//#define len (r-l+1)
const int maxn=1e7+10;
const int inf=1e9;
const int maxa=2e3+10;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,m;
const int modd=998244353;
//int ipo(int x){
//	int ans=1;
//	for(int i=1;i<=x;i++)ans*=i;
//	return ans;
//}
int f[maxn],inv[maxn];//jiecheng niyuan
void init(){
	inv[0]=inv[1]=f[0]=f[1]=1;
	for(int i=2;i<=maxn-10;i++){
		inv[i]=(modd-modd/i)*inv[modd%i]%modd;
		f[i]=f[i-1]*i%modd;
	}
	for(int i=2;i<=maxn-10;i++){
		inv[i]=inv[i-1]*inv[i]%modd;
	}
}
inline int C(int n,int m){return f[n]*inv[m]%modd*inv[n-m]%modd;}
inline void add(int &a,int b){a=(a+b)%modd;}
int pre,dex;
void work(){
	n=read(),m=read(),pre=read();
	dex=0;
	for(int i=1;i<n;i++){
		int now;now=read();
		if(pre>=now)dex++;
		pre=now;
	}
	int ans=0;
	for(int i=0;i<=m-dex-1;i++){
		add(ans,C(n-dex-1,i));
	}
	cout << ans << endl;
}
signed main(){
	init();
	int t;
	cin >> t;
//	cin >> n >> m;
	while(t--){
		work();
	}
//	for(int i=1;i<=15;i++){
//		cout << f[i] << endl;
//	}
	return 0;
}
```

---

## 作者：WsW_ (赞：3)

### 思路
把分几段转化为在原数列上切几刀。令末尾必须也切一刀，切的刀数就等于段数。  
首先分尽可能少的段，让每段都单增。容易发现无论怎么分这几刀都是必须要切的。  
假设这切了 $t$ 刀（包括末尾），那么就还要切 $0\sim m-t$ 刀。本身原数列有 $n$ 个地方可供切刀，现在已经切掉了 $t$ 个地方，那就还剩 $n-t$ 个地方可供切刀。在 $n-t$ 个地方切 $0\sim m-t$ 刀，方案数就是 $\sum\limits_{i=0}^{m-t}C_{n-t}^{i}$。  
线性预处理组合数逆元，统计的时候直接按上面式子加起来即可。  
时间复杂度为 $O(\sum n)$。

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod=998244353;
vector<int>a;
ll fact[10000003],inv[10000003],ifact[10000003];

ll C(int m,int n){
	return fact[m]*ifact[n]%mod*ifact[m-n]%mod;
}

void work(){
	a.clear();
	int n,m;cin>>n>>m;
	int lst=0,len=0;
	for(int i=1;i<=n;i++){
		int x;cin>>x;
		if(x>lst)++len;
		else a.push_back(len);
		lst=x;
	}
	a.push_back(len);
	
	m-=a.size();
	n-=a.size();
	ll ans=0;
	for(int i=0;i<=m;i++)(ans+=C(n,i))%=mod;
	cout<<ans<<'\n';
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	
	fact[0]=ifact[0]=inv[0]=1;
	fact[1]=ifact[1]=inv[1]=1;
	for(int i=2;i<=10000000;i++){
		fact[i]=fact[i-1]*i%mod;
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
		ifact[i]=inv[i]*ifact[i-1]%mod;
	}
	int T;cin>>T;
	while(T--)work();
	return 0;
}
```

---

## 作者：gghack_Nythix (赞：3)

## 前言：

推式子一分钟，调代码一小时。

## 分析：



先将题目转化为对序列的 $n-1$ 个空切 $m-1$ 刀。$\forall i\in[1,n]$，如果 $a_i\leq a_{i-1}$，意味着必须在 $i$ 和 $i-1$ 之间切一刀划分开来，算完这个之后我们还有一些剩下的操作次数，这些随便放在哪个空都可以，用组合数算一下就好了。

---

## 作者：Yannik (赞：3)

## 题目大意：
切割一个长为 $n$ 的无序序列 $A_n$ 成为最多 $m$ 个非空段，保证分割的每一段单调递增，求方案数。

## 转化与理解：
想一想切割为 $x$ 段的意思是不是往 $A_n$ 这个序列里面切 $x-1$ 刀。我们再来思考，如果一个序列中存在 $A_i≥A_{i+1}$ 那么我们就必须切一刀，比如样例：7 10 $|$ 9 23 $|$ 1 6 7 8 9 20 必须先这样切 $2$ 刀。
这时候我们再将 $m=5$ 转化为可以切 $m=4$ 刀，然而已经切了 $2$ 刀，还剩下 $2$ 刀随便切（可以选择切      $0$ 刀，$1$ 刀，$2$ 刀）。但必须切没切过的位置，而这个位置就是 $A_i≤A_{i+1}$。

## 公式：
 定义：$may$ 为可以选择切的空位，$must$ 必须切的位置。  $may=m-must-1$。
 ### $ \sum_{i=0}^{must} C_{may}^{i}$ 。
组合数模板在下面代码也有，基本上很全面，大家可以参考一下。

## 代码： 
```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
#include<random>
#define int long long 
using namespace std;
const int N = 1e7 +10,mod = 998244353;
int f[N],ifac[N];
int ksm(int m,int n){
	int ans=1;
	for(;n;n>>=1,m=m*m%mod){
		if(n&1) ans=ans*m%mod;
	}
	return ans%mod;
}
int A(int n,int m){
	if(n<m||m<0)return 0;
	return f[n]*ifac[n-m]%mod;
}
int C(int n,int m){
	if(n<m||m<0)return 0;
	return f[n]*ifac[n-m]%mod*ifac[m]%mod;
}
int T,n,m,a[N];
signed main(){
	cin.tie(0);
	ios::sync_with_stdio(0);
	f[0]=1;
	for(int i=1;i<=N-10;i++){
		f[i]=f[i-1]*i%mod;
	}
	ifac[N-10]=ksm(f[N-10],mod-2);
	for(int i=N-10;i;i--){
		ifac[i-1]=ifac[i]*i%mod;
	}//以上为组合数模板，有需要的可以拷贝
	cin>>T;
    while(T--){
        cin>>n>>m;
        int ans=0,must=0,may=0;
        cin>>a[1];
        for(int i=2;i<=n;i++){
            cin>>a[i];
            if(a[i]<=a[i-1]){
                must++;
            } else {
				may++;
			}
        }
		int res=0;
		for(int i=0;i<=m-must-1;i++){
			res+=C(may,i)%mod;
			res%=mod;
		}
		cout<<res%mod<<"\n";
    }
}
```
###### 谢谢啦～

---

## 作者：K_J_M (赞：2)

## 题目描述

你手上有一个长为 $n$ 的数列 $a$。小 Q 想让你将其分成不超过 $m$ 段**非空**连续段，且每段内数字**严格单调递增**。现在小 Q 想知道一共有几种划分方案。由于方案数可能很大，你只需要告诉她方案数对 $998244353$ 取模的结果。
## Solution
由于我们的数列是需要严格单调递增的，而且需要非空，那么对于下降的一段，我们不得不将他们单独分成一段。比如，$\{1,2,3,5,10,4,6,8,7,6,10\}$，我们就需要将它分成 $\{1,2,3,5,10\}，\{4,6,8\}，\{7\}，\{6,10\}$ 这四段。原本我们有 $10$ 个可供选择划分位置，现在由于某些地方不得不划分导致我们的划分位置只剩下 $10-3=7$ 个。假设我们有 $k$ 个不得不划分的地方，那么此时剩下 $n-k-1$ 个剩余划分位置，还需划分为 $m-k-1$ 段。

现在问题转化为从 $n-k-1$ 个物品中选出不超过 $m-k-1$ 个的方案数。使用排列组合，我们的答案应该是
$$\sum_{i=0}^{m-k-1}C_{n-k-1}^{i}$$
我们可以先预处理出 $10^7$ 以内的阶乘和逆元，如果不会线性求逆元，可以移步我的 [Blog](https://www.luogu.com.cn/article/x9y51ij6)。\
[Ac Code](https://www.luogu.com.cn/paste/u6xhig01)

---

## 作者：ini2015_____ (赞：2)

唯一一道场切的题 qwq ，还是太蒻了。

### 题目大意
给定序列 $\{a_n\}$ 与 $m$ ，求将 $\{a_n\}$ 分成 $m$ 个严格单增非空连续段的方案数

### Subtask 1
$n\le10$ ，随便乱搞都能过
### Subtask 2
考虑 dp ，记 $f(i,j)$ 为当前处理到 $a_i$ ，已经分出 $j$ 段的情况数，那么可以写出递推方程： 
$$
f(i,j)=\begin{cases}
 f(i-1,j-1) & a_i\le a_{i-1} \\
 f(i-1,j)+f(i-1,j-1) & a_i > a_{i-1}
\end{cases}
$$
解释：

- 若 $a_i>a_{i-1}$ 则此时可以选择分段，也可选择不分段
- 若 $a_i \le a_{i-1} $ 则此时必须分段

初始状态 $f(0,0)=1$ ，求出 $\sum_{i=1}^mf(n,i)$ 即可

### Subtask 3
保证 $a_i$ 单增，则此时可以随便分，那么利用隔板法，分 $m$ 段相当于在 $n-1$ 个空隙中插入 $m-1$ 个隔板，答案为 $\sum_{i=1}^m\begin{pmatrix}
  n-1  \\
  i-1  
\end{pmatrix}$

### Subtask 4,5
有了 subtask3 的经验，我们考虑用组合数处理这道题，由于 $a_i\le a_{i-1}$ 时必须分段， $a_i>a_{i-1}$ 时可分可不分，那么记必须分段处的个数为 $t$ ，我们相当于在 $n-1-t$ 个空隙中分配至少 $m-1-t$ 个隔板，仍然可以用组合数解决。

coding:

```
#define int long long//要开long long
int a[N];
int n,m;
int frac[N],revf[N];
inline int fpow(int a,int b,int p){
	if(!b)return 1;
	int mid=fpow(a,b/2,p);
	if(b%2==0)return mid*mid%MOD;
	return ((mid*mid)%MOD*a)%MOD;
}//快速幂 
inline int rev(int x){
	if(revf[x])return revf[x];
	return revf[x]=fpow(frac[x],MOD-2,MOD);
}//逆元复杂度较高，这里记忆化一下 
inline void build(){
	frac[0]=1;
	for(int i=1;i<N;i++)frac[i]=((frac[i-1]*i)%MOD);
}//预处理阶乘 
inline int C(int x,int y){//choose m in n
	return (frac[y]*rev(x)%MOD)*rev(y-x)%MOD; 
}//组合数 
inline int read(){
	int x=0;
	char c=getchar_unlocked();
	while(c<'0' or c>'9')c=getchar_unlocked();
	while(c<='9' and c>='0'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar_unlocked();
	}
	return x;
}//快读 
signed main(){
	int T=read();
	build();
	while(T--){
		n=read(),m=read();
		int t=0;
		for(register int i=1;i<=n;i++)a[i]=read();
		for(register int i=2;i<=n;i++)if(a[i]<=a[i-1])m--,t++;//处理出必须分段的数量 
		int ans=0;
		for(register int j=1;j<=m;j++)ans=(ans+C(j-1,n-1-t))%MOD;
		cout<<ans<<endl;
	}
}

```

---

## 作者：lzx111218 (赞：1)

# P11616 瓦解
[题目传送门](https://www.luogu.com.cn/problem/P11616)
## 思路

考虑 **DP**。我们用一个二维数组 $dp_{i,j}$ 来表示前 $i$ 个元素被划分为 $j$ 段递增子序列的方案数。初始时，$dp_{0,0} = 1$，表示没有元素时，只有一种划分方式。然后，我们通过状态转移来更新 $dp_{i,j}$
 的值。对于每个位置 $i$，我们需要遍历它前面的所有位置 $j$，并检查 $a_j < a_i$ 的情况。如果满足条件，我们就可以将前 $j$ 个元素的划分方式加到 $dp_{i,j}$ 中。

由于每个位置 $i$ 可能会影响多个位置 $j$，因此直接计算可能会导致超时。为了提高效率，我们可以利用前缀和来加速计算。具体来说，我们维护一个前缀和数组，将前面所有位置的划分方案数累加输出即可。
### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 998244353;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T, n, m;
    cin >> T;

    while (T--) {
        cin >> n >> m;

        vector<ll> a(n + 1), ni(n + 1, 0);
        int k = 0;

        ni[1] = 1; 
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            if (i > 1 && a[i] <= a[i - 1]) {
                k++;  
            }

            if (i > 1) {
                ni[i] = ni[MOD % i] * (MOD - MOD / i) % MOD;
            }
        }

        n -= k + 1;
        m -= k + 1;

        if (m < 0) {
            cout << 0 << '\n';
            continue;
        }

        ll sum = 1, ans = 1;
        for (int i = 1; i <= m; i++) {
            sum = sum * ((n - i + 1) * ni[i] % MOD) % MOD;
            ans = (ans + sum) % MOD;
        }

        cout << ans << '\n';
    }

    return 0;
}
```

---

## 作者：Camellia_Spoil (赞：1)

# 题意
总共有 $t$ 次询问，每次询问给你一个长度为 $n$ 的序列 $a$，可以分割成不超过 $m$ 段**非空连续子段**，问有多少种分割方案可以使得这 $m$ 段非空子段都是**严格单调递增**的，答案要对 $998244353$ 取模。

# 分析
一道~~非常简单~~的数学题。

首先，这个序列 $a$ 不一定本身就是严格单调递增的。我们可以将题意转换一下，即在长度为 $n$ 的 $a$ 序列中插入不多于 $m-1$ 个隔板，使得这些隔板分割出来的连续子段都是严格单调递增的。注意长度为 $n$ 的数列只可以插入 $n-1$ 个隔板。

对于每一个 $i$，如果 $a_i \le a_{i-1}$，说明严格单调递增序列到 $a_i$ 断开了，那么 $a_i$ 与 $a_{i-1}$ 之间就要插入隔板，不断开则无法满足每一段都是单调递增序列的要求。

记上述操作一共对序列 $a$ 插入了 $x$ 个隔板，则我们最多还可以在序列 $a$ 中插入 $m-1-x$ 个隔板，在上述操作后我们已经将不是单调递增的序列分割成了几个单调递增序列，所以我们只需要在剩余的 $n-1-x$ 个可以放置隔板的位置插入不超过 $m-1-x$ 个隔板即可。

那方案数怎么统计呢？我们可以用组合数来统计。我们在对初始的 $a$ 序列插入隔板时，已经将使导致原序列不是单调递增序列的位置插入隔板，故我们只需要在剩余位置任意插入不超过 $m-1-x$ 个隔板即可。答案为：
$\begin{aligned} \sum _ {i = 0} ^ {m-1-x}  C_{n-1-x}^{i}\end{aligned}$

# AC Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define N 10000001
using namespace std;
inline long long read()
{
	long  long x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-')f=-1;ch=getchar();} 
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
const int mod=998244353;
inline void write(ll x){
	if(x>=10)write(x/10);
	putchar(x%10+'0'); 
}
ll f[N],g[N];
int a[N];
inline ll qsm(ll a,int b){//快速幂求组合数 
    ll s=1;
    while(b){
      if(b&1) s=s*a%mod;
      a=a*a%mod;
      b>>=1; 
    }
  return s;
}
inline ll C(ll n,ll m){
  return f[n]*g[m]%mod*g[n-m]%mod;//组合数计算公式 
}
signed main(){
    int t;
    t=read();
    f[0]=g[0]=1;
    for(register int i=1;i<=9000000;i++){//预处理组合数 
        f[i]=f[i-1]*i%mod;
        g[i]=qsm(f[i],mod-2)%mod;
    }
    while(t--)
    {
        int n,m;
        n=read();m=read();
        int x,y,ans=0;
        for(register int i=1;i<=n;++i)
        {
            a[i]=read();
            if(a[i]<=a[i-1]) ans++;//计算出原序列一定要插入隔板的位置个数 
        }
        ll sum=0;
        for(register int i=0;i<=m-ans-1;++i) sum+=C(n-ans-1,i)%mod;//统计答案 
        write(sum%mod);
        printf("\n");
    }
	return 0;
}
```

---

## 作者：HasNoName (赞：1)

### 思路
不难发现，其实答案与数字大小无关，只与每个单调递增数列长度有关。

于是我们先考虑数列本身严格单调递增的情况。

发现这个答案就是有 $n$ 个球，将其分成 $m$ 个以内个组的方案总数，利用插板法可以得到答案为 $\sum_{i=0}^{m-1} C_{n-1}^i$ 种。

再考虑一般情况，我们发现，$n$ 个球之间，有的空位是必需插板的，所以，如果数列中有 $k$ 个极长的严格单调递增序列，则答案为 $\sum_{i=0}^{m-k} C_{n-k}^i$。

对于这个式子，递推求解即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD=998244353;
ll a[10000005],ni[10000005];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T,n,m;
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		int k=0;
		ni[1]=1;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			if(a[i]<=a[i-1])k++;//个数
			if(i>1)ni[i]=ni[MOD%i]*(MOD-MOD/i)%MOD;//逆元
		}
		n-=k+1;m-=k+1;
		if(m<0)
		{
			cout<<0<<'\n';
			continue;
		}
		ll sum=1,ans=1;
		for(int i=1;i<=m;i++)
		{
			sum=sum*((n-i+1)*ni[i]%MOD)%MOD;
			ans=(ans+sum)%MOD;
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：ForgetOIDuck (赞：1)

容易发现若存在 $a_i\ge a_{i+1}$，则 $i$ 与 $i+1$ 之间一定要断开。假设我们有 $k$ 个这种必须断开的地方，目前需要分成 $l$ 段，那么我们还需要再断开 $l-k$ 次，也就是在剩余的 $n-k-1$ 个空隙中选择 $l-k$ 个空隙插板，方案为 $C_{n-k-1}^{l-k}$，枚举 $l$ 即可。

预处理组合数我们使用其原始公式 $C_n^m=\frac{n!}{m!(n-m)!}$，可通过线性预处理阶乘与阶乘逆元来做到 $O(10^7)$ 实现。然后处理这些必须断开的地方也是 $O(n)$ 的。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353, N = 10000000;
long jc[10000002], ic[10000002];
ll  T, k, m, ans, n, a[2];
ll qmi(ll x, ll y) {
	ll res = 1;
	while (y) (res *= (y % 2 ? x : 1)) %= mod, (x *= x) %= mod, y >>= 1;
	return res;
}
ll c(ll a, ll b) {
	if (a < 0 || b < 0) return 0;
	return (ll)jc[a] * ic[b] % mod * ic[a - b] % mod;
}
int main() {
	jc[0] = 1;
	for (ll i = 1; i <= N; i ++ ) jc[i] = ((ll)jc[i - 1] * i) % mod;
	ic[N] = qmi(jc[N], mod - 2);
	for (ll i = N - 1; i >= 0; i -- ) ic[i] = ((ll)ic[i + 1] * (i + 1)) % mod;
	cin >> T;
	while (T -- ) {
		cin >> n >> m;
		for (ll i = 1; i <= n; i ++ ) scanf("%d", &a[i % 2]), k += (a[i % 2] <= a[i % 2 ^ 1] && i != 1);
		ans = 0;
		for (ll i = k; i < m && i < n; i ++ ) ans = (ans + c(n - 1 - k, i - k)) % mod;
		k = 0;
		cout << ans << endl;
	}
}
```

---

## 作者：sbno333 (赞：0)

乍一看没啥思路，仔细一想，发现挺水的。

当 $a_i\le a_{i-1}$ 时，这中间必须插一个隔板，否则随便。

考虑插板法。

分成 $m$ 个区间就是 $m-1$ 个插板，$n$ 个数就是 $n-1$ 个插板空位，一些地方必须插板，一旦发现，就让插板数和可以插板的地方数都减一。

计算组合数即可。

然后调了 $114514$ 年样例，为啥呢？因为题面说**不超过** $m$，所以最终你要对插板数为 $0$ 到总插板数都计算一遍组合数，求和。啥？超时？因为你需要线性求逆元，预处理出阶乘逆元，组合数 $O(1)$ 即可通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mod 998244353ll
int a[10000009];
int jc[10000009];
int ny[10000009];
int ksm(int a,int b){
	int ans;
	ans=1;
	while(b){
		if(b&1){
			ans*=a;
			ans%=mod;
		}
		a*=a;
		a%=mod;
		b>>=1;
	}
	return ans;
}
int c(int n,int m){
	if(m>n||m<0){
		return 0;
	}
	return jc[n]*ny[m]%mod*ny[n-m]%mod;
} 
void _main(){
	int n,m;
	cin>>n>>m;
	int nn;
	nn=n-1;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]<=a[i-1]){
			nn--;
			m--;
		} 
	}
	m--;
	int ans;
	ans=0;
	n=nn;
	for(int i=0;i<=m;i++){
		ans+=c(n,i);
		ans%=mod;
	}
	cout<<ans<<"\n";
}
signed main(){
	cin.tie(0);
	cout.tie(0);
	std::ios::sync_with_stdio(0);
	jc[0]=1;
	for(int i=1;i<=10000000;i++){
		jc[i]=jc[i-1]*i;
		jc[i]%=mod;
	}
	ny[10000000]=ksm(jc[10000000],mod-2);
	for(int i=9999999;i>=0;i--){
		ny[i]=ny[i+1]*(i+1)%mod;
	}
	int t;
	cin>>t;
	while(t--){
		_main();
	}
	return 0;
}
```

---

## 作者：可爱大黄兔 (赞：0)

我们可以先求出满足 $a_i>a_i-1$ 的个数 $cnt$，然后答案就可以转化为依次求出在 $(n-cnt)$ 个数内选出 $(i-cnt)$ 个数的方案数。根据组合数学可以求出答案为 $\sum_{i=cnt}^n C_{n-cnt}^{i-cnt}$。

```cpp
#include<bits/stdc++.h>
// 7 10
// 9 23
// 1 6 7 8 9 20
typedef long long ll;
using namespace std;
int T;
int n,m;
ll a[10000010];
ll fac[10000010];
ll inv[10000010];
ll finv[10000010];
const ll mod=998244353;
ll fastpow(ll a, ll b) {
	ll ans = 1, base = a;
	while (b != 0) {
		if (b & 1)
			ans = (ans * base % mod) % mod;
		base = (base * base) % mod;
		b >>= 1;
	}
	ans %= mod;
	return ans;
}

ll C(ll n,ll m){
	if(m<0||m>n)return 0;
	return fac[n]*finv[n-m]%mod*finv[m]%mod;
}
int main(){
	inv[1]=1;
    for(int i=2;i<=10000000;i++)inv[i]=((mod-mod/i)*inv[mod%i])%mod;
	fac[0]=finv[0]=1;
	for(int i=1;i<=10000000;i++)fac[i]=fac[i-1]*i%mod,finv[i]=finv[i-1]*inv[i]%mod;
	cin>>T;
	while(T--){
		ll cnt=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			if(a[i]<=a[i-1]){
				cnt++;
			}
		}
		cnt++;
//		if(m<cnt){
//			puts("0");
//			continue;
//		}
//		puts("Run");
		ll ans=0;
		for(int i=cnt;i<=m;i++){
			ans+=C(n-cnt,i-cnt);
			ans%=mod;
		}
		cout<<ans%mod<<endl;
		
	}
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

首先，我们必须截出不超过 $m$ 个区间，也就是分 $m-1$ 次。

显然对于不满足 $a_{i-1}<a_i$ 的位置必须断开。

于是问题就变成了有一些可断可不断的位置，你可能还剩一些次数可以向其中随意分配。

显然就是一堆组合数的和，预处理阶乘与逆元可以做到线性。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
constexpr int p=998244353;
int t,n,m,a[10000005],jc[10000005],ny[10000005],ans;
inline int qpow(int a,int b=p-2){
	int ret=1;
	for(;b;b>>=1,a=a*a%p)
		(b&1)&&(ret=ret*a%p);
	return ret;
}
inline int cvl(int n,int m){
	if(n<m||n<0||m<0) return 0;
	return jc[n]*ny[m]%p*ny[n-m]%p;
}
signed main(){
	ios::sync_with_stdio(0); jc[0]=1;
	for(int i=1;i<=1e7;++i) jc[i]=jc[i-1]*i%p;
	ny[10000000]=qpow(jc[10000000]);
	for(int i=1e7;i>0;i--) ny[i-1]=ny[i]*i%p;
	for(cin>>t;t;t--){
		cin>>n>>m; m--; int tn=n;
		for(int i=1;i<=tn;++i) cin>>a[i];
		for(int i=1;i<tn;++i)
			(a[i]>=a[i+1])&&(m--,n--);
		n--; ans=0;
		for(int i=0;i<=m;++i)
			ans=(ans+cvl(n,i))%p;
		cout<<ans<<endl;
	}
	return 0;
} 
```

---

