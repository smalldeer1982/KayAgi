# Product 1 Modulo N

## 题目描述

#### 题目大意：

给定一个正整数 $n$ ，找到排列 $[1,2,...,n-1]$ 的最长子序列，使它满足它元素的乘积模 $n$ 意义下为 $1$ 。

注意：子序列的定义： $b$ 是 $a$ 的子序列当且仅当可以通过删去 $a$ 的若干个（可以是 $0$ 个） 元素得到 $b$ 。

## 样例 #1

### 输入

```
5```

### 输出

```
3
1 2 3```

## 样例 #2

### 输入

```
8```

### 输出

```
4
1 3 5 7```

# 题解

## 作者：Lynkcat (赞：10)

比较妙的一道题。

首先考虑这么一个问题，如果我们选中的数中有与 $n$ 不互质的数，会怎么样？

我们设选中的数中有一个数和 $n$ 的 $\gcd$ 为 $x$ ，$x$ 不为 $1$ 。

那么最终乘出来的积必定是 $x$ 的倍数，也就是说，答案一定会是 $x,2x,3x……,(\frac{n}{x}-1)\times x,0$ 中的一个，显然这个答案不会是 $1$ 。

也就是说，我们选中的数中必须全部与 $n$ 互质。

接下来再考虑一个问题，如果全部都选与 $n$ 互质的数，那么最后的答案可不可能与 $n$ 不互质？

我们设最后答案为 $y$ （$y$ 与 $n$ 不互质），那么积可以用 $y+pn$ 的形式表示出来，而我们知道 $n$ 中可以提取出至少一个 $y$ 出来，也就是说，选中的数中必定有一个的因数包含 $y$ 。这与假设的全部都选与 $n$ 互质的数相矛盾。

得证：如果全部都选与 $n$ 互质的数，那么最后的答案与 $n$ 必定互质。

那么我们考虑把与 $n$ 互质的数全选上，最后的答案必定与 $n$ 互质，而与 $n$ 互质并且小于 $n$ 的数我们都已经选过了，那么这个答案的数值我们也必定选了，把他去掉就行了。

代码：
```c++
#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for (int i=(a);i<=(b);i++)
#define R(i,a,b) for (int i=(a);i<(b);i++)
#define D(i,a,b) for (int i=(a);i>=(b);i--)
#define go(i,x) for (int i=head[x];i;i=e[i].nx)
#define mp make_pair
#define pb push_back
#define pa pair < int,int >
#define fi first
#define se second
#define re register
#define be begin()
#define en end()
#define sqr(x) ((x)*(x))
#define ret return puts("-1"),0;
#define put putchar('\n')
#define inf 1000000005
#define mod 998244353
#define int ll
//#define N
using namespace std;
inline char gc(){static char buf[100000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int n,ans;
vector<int>G;
signed main()
{
	n=read();ans=1;
	for (int i=1;i<=n;i++)
		if (__gcd(n,i)==1) 
		{
			ans=ans*i%n;G.push_back(i);
		}
	if (ans!=1)
	{
				writeln(G.size()-1);
				for (auto v:G)
				{
					if (v==ans) continue;
					writesp(v);
				}
				return 0;
	}else
	{
	writeln(G.size());
	for (auto u:G) writesp(u);}
	
}
/*

*/



---

## 作者：Ryo_Yamada (赞：6)

> 在 $1 \sim n-1$ 中取出若干个数组成一个序列 $A$，使 $(\prod A_i) \!\!\mod n = 1$。求序列最长的长度及取出哪些数，升序输出。

首先，对于 $1 \sim n-1$ 中的数，只能取与 $n$ 互质的数，否则乘积必定不为 $1$。我们将互质的数全部取出，求出它们的乘积 $k\!\!\mod n$。如果 $k \not=1$，可以证明 $k$ 一定是与 $n$ 互质的，也就是我们取出序列中的数。此时在序列中删除 $k$ 就是最优解。

$\text{Code}$：

```cpp
		ll now = 1;
		qread(n);
		rep(i, 1, n - 1) {
			if(gcd(i, n) == 1) {
				(now *= i) %= n;
				ans[++cnt] = i;
			}
		}
		if(now != 1) {
			printf("%d\n", cnt - 1);
			rep(i, 1, cnt) {
				if(ans[i] != now) printf("%d ", ans[i]);
			}
		}
		else {
			printf("%d\n", cnt);
			rep(i, 1, cnt) printf("%d ", ans[i]);
		}
		puts("");
```


---

## 作者：寒鸽儿 (赞：5)

$1$ 必然选。  
对 $2 \cdots n-1$ 中的数字 , 首先考虑没有逆元的数字 , 易知这些数字是不应该选。否则无法保证乘积在模意义下等于 $1$。  
$a$ 在模 $n$ 意义逆元不存在等价于 $\gcd(a,n) \neq 1$。  
排除掉所有与 $n$ 不互素的数 , 剩下的数字的乘积的逆元必然存在。  
来证一下两个数字的情况 :  
$$
aa^{-1} \equiv 1 \pmod n 
$$
$$
bb^{-1} \equiv 1 \pmod n
$$
$$
(ab)(a^{-1}b^{-1}) \equiv 1 \pmod n
$$
那么这个数一定在有逆元的数的集合 , 把它删掉就好了。  
```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
vector<int> res;
 
int main() {
    if(fopen("yl.in", "r")) {
        freopen("yl.in", "r", stdin);
        freopen("yl.out", "w", stdout);
    }
    int n, prod = 1; scanf("%d", &n);
    res.push_back(1);
    for(int i = 2; i < n; ++i) if(__gcd(i, n) == 1) res.push_back(i), prod = 1ll * prod * i % n;
    printf("%ld\n", res.size() - (prod==1?0:1));
    for(int i = 0; i < res.size(); ++i) if(!i || res[i] != prod) printf("%d ", res[i]);
    puts("");
    return 0;
}
```

---

## 作者：zsyyyy (赞：3)

# CF1514C 1600 贪心+数学

## 题目

给定一个正整数 $n$ ，找到排列 $[1,2,...,n-1]$ 的最长子序列，使它满足它元素的乘积模 $n$ 意义下为 $1$。


**输入格式**：

一行一个正整数 $n$ $(2≤n≤10^5)$，意义如题所述。

**输出格式**：

第一行一个正整数 $len$，表示最长子序列的长度。

第二行以升序输出子序列中的元素。

如果有多组数据，可以输出任意一个。


## 思路

易知如果选取的数 $x$ 不与 $n$ 互质，那么最终的余数一定是 $x$ 与 $n$ 的最大公因数的倍数，一定不可能为 $1$，所以最多只能选所有与 $n$ 互质的数。

如果乘积模 $n$ 已经为 $1$，那么直接输出所有与 $n$ 互质的数即可。否则，余数一定在 $[0,n-1]$ 之间，因为所选的所有数都与 $n$ 互质，所以乘积也与 $n$ 互质，所以乘积模 $n$ 也一定与 $n$ 互质，又因乘积模 $n$ 在 $[0,n-1]$ 之间，所以乘积模 $n$ 一定在所选数中。

设该余数为 $b$，该乘积则为 $k·n+b$（$k$为整数），因为该余数 $b$ 一定在所选数中，所以该乘积除以 $b$ 为 $k1·n+1$（$k1$为整数），也就是模 $n$ 为 $1$ 的符合题意的情况。

也就是说，只要从所选数中去掉该余数，余数就会变为 $1$。

时间复杂度：$O(nlogn)$



## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e5+10;
int n,a[MAXN],cnt,sum=1;
bool flag;
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) //枚举所有与n互质的数
	{
		if(__gcd(i,n)==1)
		{
			sum=(sum*i)%n;
			a[++cnt]=i;
		}
	}
    //sum为乘积除以n的余数
	if(sum!=1)  printf("%lld\n",cnt-1);
	else  printf("%lld\n",cnt);
	for(int i=1;i<=cnt;i++)
	{
		if(a[i]!=sum||i==1)  printf("%lld ",a[i]);
	}
	return 0;
}
```


---

## 作者：江户川·萝卜 (赞：3)

### 题目大意
在 $[1,n-1]$ 区间中选取若干个整数使得乘积模 $n$ 为  $1$，最大化选取的数的个数。

---
赛时想了好久。。。

首先思考一个问题，如果选中不与 $n$ 互质的数 $x$ （即 $\operatorname{gcd}(n,x)>1$）会是什么情况呢？

设 $d=\operatorname{gcd}(n,x),x=k_1d,n=k_2d$，其他选取数的乘积是 $A$。

则$Ak_1d\equiv1\pmod{k_2d}$，$Ak_1d+k\cdot k_2d=1$，$(Ak_1+k\cdot k_2)d=1$。

因为 $d>1$ 且 $(Ak_1+k\cdot k_2)$ 是整数，易知上式不成立。

**所以只能够选取与 $n$ 互质的数。**

那它们的乘积肯定与 $n$ 互质，模 $n$ 后肯定也与 $n$ 互质。

如果不与 $n$ 互质（设为 $x$），再设 $d=\operatorname{gcd}(n,x)$，则模 $n$ 前的乘积是 $kn+x=d(\frac{kn}{d}+\frac{x}{d})$，也即存在因数 $d$，与乘积与 $n$ 互质矛盾。

所以乘积模 $n$ 的值与 $n$ 互质。

如果这个值不为 $1$ 则只要在原先选取的数中剔除掉即可。

（蒟蒻没学过证明，如有语言上的错误还请见谅）

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int gcd(int x,int y){return y?gcd(y,x%y):x;}
bool hz[1000005];
int main(){
	int n,cnt=0;
	scanf("%d",&n);
	long long ans=1;
	hz[1]=1;cnt++;
	for(int i=2;i<=n;i++){
		if(gcd(i,n)==1) cnt++,hz[i]=1,ans=(ans*i)%n;
	}
	if(ans!=1) hz[ans]=0,cnt--;
	printf("%d\n",cnt);
	for(int i=1;i<=n;i++) if(hz[i]) printf("%d ",i);
	return 0;
}
```

---

## 作者：dead_X (赞：1)

## 题意
在 $1,2,3,\cdots,n-1$ 之间选尽可能多的数，使得这些数的乘积模 $n$ 等于 $1$。

$n\leq 10^5$。
## 思路
显然如果你选了 $x$ 使得 $\gcd(n,x)$，则乘积必为 $\gcd(n,x)$ 的倍数，模 $n$ 后不可能为 $1$。

于是我们只能在 $\gcd(n,x)=1$ 的 $x$ 中选数。

此时，我们尝试将所有数都选出，会发现其乘积必定在这些数里面。如果乘积不为 $1$，则不选这个数，我们就得到了最优解。

如果乘积在这些数里面，这个构造的正确性显然。而 $\forall \gcd(a_i,n)=1$，因此 $\gcd(\prod a_i,n)$ 也为 $1$，因此可以保证正确性。 
## 代码
```cpp
// Problem: C. Product 1 Modulo N
// Contest: Codeforces - Codeforces Round #716 (Div. 2)
// URL: https://codeforces.com/contest/1514/problem/C
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)
 
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int p=998244353;
int qp(int x,int y)
{
	int res=1;
	for(int t=x; y; y>>=1,t=t*t%p) if(y&1) res=res*t%p;
	return res;
}
signed main()
{
    int n=read();
    int ans=1;
    int C=0;
    for(int i=1; i<n; ++i) if(__gcd(n,i)==1)
    ans=ans*i%n,++C;
    if(ans!=1) --C;
    printf("%lld\n",C);
    printf("1 ");
    for(int i=2; i<=n; ++i) if(__gcd(n,i)==1&&i!=ans)printf("%lld ",i);
	return 0;
}
```

---

## 作者：The_foolishest_OIer (赞：0)

遇到这种神奇的题目直接打表。

首先可以发现，关于 $n$ 的排列如果有整数 $i$，整数 $i$ 肯定满足 $\gcd(i,n) = 1$。

把这些数全部列出来，发现结果（即这些数的乘积模 $n$ 所得的余数）不是 $1$ 就是 $n - 1$。

| $n$ | 合法的 $i$ | 结果 |
|:-:|:-:|:-:|
| $2$ | $1$ | $1$ |
| $5$ | $1,2,3,4$ | $4$ |
| $8$ | $1,3,5,7$ | $1$ |
| $20$ | $1,3,7,9,11,13,17,19$ | $1$ |

发现合法的 $i$ 中必有 $n - 1$（$n$ 与 $n - 1$ 互质），如果结果是 $n - 1$ 去掉 $n - 1$ 即可。


```
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 1e5 + 10;
int n,mod,cnt;
int a[N];
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
signed main(){
	close();
	cin >> n;
	mod = 1;
	for (int i = 1 ; i < n ; i++){
		if (__gcd(i,n) == 1){
			a[++cnt] = i;
			mod *= i;
			mod %= n;
		}
	}
	if (mod != 1) cnt--;
	cout << cnt << endl;
	for (int i = 1 ; i <= cnt ; i++) cout << a[i] << ' ';
	return 0;
}
```

---

## 作者：LiveZoom (赞：0)

# CF1514C Product 1 Modulo N 题解

~~赛时想了一下就过了~~

一个显然的结论：给定一个正整数 $n$，很多个与 $n$ 互质的正整数的积与 $n$ 互质。

由于这题要求的数的乘积被 $n$ 除余 $1$，所以这些数都是与 $n$ 互质的。

所以长度 $\leq$ $n$ 的既约剩余系长度（指的就是 $1\sim n$ 与 $n$ 互质的数的个数）。

由于这些数的乘积 $\bmod n$ 不一定为 $1$，所以要考虑去掉一些最少的数使得剩下的数的积满足条件。然后很明显去掉这个乘积 $\bmod n$ 即为最多的情况。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, tot, a[N];

int gcd (int m, int n) {
	if (m < n) swap(m, n);
	if (n == 0) return m;
	return gcd(n, m % n);
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		if (gcd(i, n) == 1) a[++tot] = i;
	}
	int times = 1;
	for (int i = 1; i <= tot; ++i) {
		times = 1ll * times * a[i] % n;
	}
	if (times == 1) {
		cout << tot << endl;
		for (int i = 1; i <= tot; ++i) cout << a[i] << " ";
		cout << endl;
	}
	if (times > 1) {
		cout << tot - 1 << endl;
		for (int i = 1; i <= tot; ++i)
			if (a[i] != times) cout << a[i] << " ";
		cout << endl;
	}
	return 0;
}
```

---

## 作者：zmx_wzx_JY (赞：0)

场上乱猜的解法就过了。

首先只能选不互质的数，然后我就猜到所有与 $n$ 互质的数的乘积只可能模 $n$ 余 1 或 -1， 如果是负一就把 $n-1$ 去掉就可以了。

然后就过了。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define Rep(i,x,y) for(int i = (x), stOxrj = (y); i<=stOxrj; ++i)
#define Irep(i,x,y) for(int i = (x), stOxrj = (y); i>=stOxrj; --i)
#define vec vector<int>
#define IT iterator
#define pb push_back
#define il inline
#define ci const int&
using namespace std;
inline int read(){
	int x; scanf("%d", &x);
	return x;
}
int n; vec ans;
int gcd(int x,int y){
	if( x<y ) swap(x, y);
	return y ? gcd(y, x % y) : x; 
}
signed main(){
	n = read();
	LL tim = 1;
	Rep(i,1,n-1) if( gcd(i, n)==1 ) ans.pb(i), tim = tim * i %n;
	if( tim!=1 ) ans.pop_back();
	cout<<ans.size()<<endl;
	for(auto t:ans) cout<<t<<" "; cout<<endl;
	return 0;
}
```

IEE 老师提供的感性证明：

一个数 $i$ 有 $i^{-1}=i$，就和 $n-i$ 配对(显然 $i\neq n-i$)，否则和 $i^{-1}$ 配对，这样每一对的积为 1 或 -1， 所以所有和 $n$ 互质的数的乘积就为 1 或 -1。

---

