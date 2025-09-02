# Novice's Mistake

## 题目描述

One of the first programming problems by K1o0n looked like this: "Noobish\_Monk has $ n $ $ (1 \le n \le 100) $ friends. Each of them gave him $ a $ $ (1 \le a \le 10000) $ apples for his birthday. Delighted with such a gift, Noobish\_Monk returned $ b $ $ (1 \le b \le \min(10000, a \cdot n)) $ apples to his friends. How many apples are left with Noobish\_Monk?"

K1o0n wrote a solution, but accidentally considered the value of $ n $ as a string, so the value of $ n \cdot a - b $ was calculated differently. Specifically:

- when multiplying the string $ n $ by the integer $ a $ , he will get the string $ s=\underbrace{n + n + \dots + n + n}_{a\ \text{times}} $
- when subtracting the integer $ b $ from the string $ s $ , the last $ b $ characters will be removed from it. If $ b $ is greater than or equal to the length of the string $ s $ , it will become empty.

Learning about this, ErnKor became interested in how many pairs $ (a, b) $ exist for a given $ n $ , satisfying the constraints of the problem, on which K1o0n's solution gives the correct answer.

"The solution gives the correct answer" means that it outputs a non-empty string, and this string, when converted to an integer, equals the correct answer, i.e., the value of $ n \cdot a - b $ .

## 说明/提示

In the first example, $ a = 20 $ , $ b = 18 $ are suitable, as " $ \text{2} $ " $ \cdot 20 - 18 = $ " $ \text{22222222222222222222} $ " $ - 18 = 22 = 2 \cdot 20 - 18 $

## 样例 #1

### 输入

```
3
2
3
10```

### 输出

```
3
20 18 
219 216 
2218 2214 
1
165 162 
1
1262 2519```

# 题解

## 作者：panxz2009 (赞：8)

## 题意
给定 $n,a,b$，令 $x=n \times a - b$，$y$ 表示把 $n$ 拼接 $a$ 次，然后去掉最后 $b$ 位表示的数。

问有多少对 $(a,b)$ 满足 $x=y$。

其中 $1 \le n \le 100,1 \le a \le 10000,1 \le b \le \min(10000,a \times n)$。
## 思路
**幽默解方程**。

观察一下不难发现，可以考虑把 $a$ 固定，列出方程解出 $b$。

设 $n,x$ 的位数分别为 $len_n,len_x$。然后根据题意，列出以下几条方程：
$$
b = n \times a - x\\
b = a \times len_n - len_x
$$
然后联立，得
$$
(n-len_n)\cdot a = x - len_x
$$
发现 $n - len_n,a$ 为定值，因此只要搞出 $x,len_x$ 的值，就可以代入直接解出 $b$。

注意到 $x$ 不可能太大，具体计算一下发现 $x \in [0,10^6]$，那么 $len_x$ 更是只有 $len_x \in [1,6]$。这启发我们考虑枚举 $len_x$。

枚举出 $len_x$ 后，就能解出 $x,b$。计算完后检验一下即可。

时间复杂度 $\mathcal O(a)$。
## 代码
```cpp
#include <bits/stdc++.h>
#define PII pair <int, int>
using namespace std;
int n, x[7], lenn;
vector <PII> ans;
int divide(int n){
	int sum = 0;
	while(n){
		sum++;
		n /= 10;
	}
	return sum;
}
void init(){
	string s = to_string(n);
	int now = 0;
	for(int lenx = 1; lenx <= 6; lenx++){
		x[lenx] = x[lenx - 1] * 10 + (s[now] - '0');
		now = (now + 1) % lenn;
//		cout << lenx << '\n';
	}
}
void Main(){
	scanf("%d", &n);
	lenn = divide(n);
	ans.clear();
	init();
	for(int a = 1; a <= 10000; a++){
		for(int lenx = 1; lenx <= 6; lenx++){
			int b = lenn * a - lenx;
			if(b > 0 && b < min(10000, a * n) && b == n * a - x[lenx]){
				ans.push_back({a, b});
			}
		}
	}
	printf("%d\n", ans.size());
	for(auto tmp : ans){
		printf("%d %d\n", tmp.first, tmp.second);
	}
}
int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		Main();
	} 
	return 0;
}
```

---

## 作者：lzh9 (赞：6)

## 思路

下文中用 $f(x)$ 来表示 $x$ 的位数。

设 $m=a\times n-b,k_1=f(n),k_2=f(m)$。

根据题目中字符串的表示方法，得到 $b=k_1\times a -k_2$。

所以，

$$ \left\{
\begin{aligned}
 b&= a\times n - m\\
 b&=a \times k_1 - k_2
\end{aligned}
\right.
$$

于是我们可以得到 $a\times n-m=a\times k_1-k_2$，解这个一元一次方程可以得到 $a$，再带入上式得到 $b$，如果 $a$ 和 $b$ 都满足题目中的要求，则统计答案。

考虑枚举 $m$，因为 $m$ 最多 $10^7$，所以最多只有 $7$ 种 $m$。

注意 $n=1,m=1$ 时上式永远成立（$m$ 为其他值时都无解），所以需要特判输出。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t;
long long n,m,k;
string zh(long long x)
{
	string res="";
	while(x)
	{
		res=char(x%10+'0')+res;
		x/=10;
	}
	return res;
}
long long zh2(string s)
{
	long long ret=0;
	for(long long i=0;i<s.size();i++)
	{
		ret=ret*10+s[i]-'0';
	}
	return ret;
}
long long ansa[1000000+5],ansb[1000000+5],cur=0;
void sol()
{
	cur=0;
	cin>>n;
	if(n==1)
	{
		cout<<9999<<"\n";
		for(long long i=1;i<10000;i++)
		{
			cout<<i+1<<' '<<i<<"\n";
		}
		return;
	}
	string sn=zh(n);
	long long k1=sn.size();
	sn=sn+sn+sn+sn+sn+sn+sn;
	sn=' '+sn;
	for(long long i=1;i<=7;i++)
	{
		long long k2=i;
		string sw=sn.substr(1,i);
		long long w=zh2(sw);//w是文中的m
		if((n-k1)==0) continue;
		if((w-k2)%(n-k1)!=0) continue;
		if((w-k2)/(n-k1)>=1&&(w-k2)/(n-k1)<=10000&&(w-k2)/(n-k1)*n-w>=1&&(w-k2)/(n-k1)*n-w<=10000) ansa[++cur]=(w-k2)/(n-k1),ansb[cur]=(w-k2)/(n-k1)*n-w;
	}
	cout<<cur<<"\n";
	for(long long i=1;i<=cur;i++) cout<<ansa[i]<<' '<<ansb[i]<<"\n";
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		sol();
	}
  return 0;
}
```

---

## 作者：Yoyo_01 (赞：5)

### 题目大意

给你一个正整数 $n$ ($1 \le n \le 100$)，请求出所有满足条件的正整数对 $(a,b)$，使得 $n \times a - b$ 等于将 $n$ 重复 $a$ 遍再去掉后 $b$ 位的结果。其中 $1 \le a \le 10000$，$1 \le b \le \min(10000,a \times n)$。

### 暴力做法

直接枚举 $a$ 和 $b$ 然后判断是否满足条件。

复杂度 $\Theta(ab)$，不能通过此题。

### 优化

刚才的暴力做法的算法瓶颈在于：枚举 $b$ 的那重循环的范围太大，那能否缩小 $b$ 的枚举范围呢？

我们知道 $n \times a - b$ 的最大值是 $100 \times 10000 - 1 = 999999$，也就是说计算结果的位数最多只有 $6$ 位。

那么，将 $n$ 重复 $a$ 遍再去掉后 $b$ 位的结果的位数也就不能超过 $6$ 位。

写成算式就是：$len(n) \times a - b \le 6$，即 $len(n) * a - 6 \le b$。其中 $len(n)$ 表示 $n$ 的位数。

根据题面可知，$b < len(n) \times a$。

于是，我们就可以得出优化后 $b$ 的取值范围：$len(n) * a - 6 \le b < len(n) \times a$，这个取值范围中，$b$ 最多枚举 $6$ 次，复杂度降为 $\Theta(a)$，可以通过此题。

### AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10;

int t,n;

struct Ans{
	int a,b;
} ans[N];

int sizes(int x){
	int res = 0;
	while(x != 0)
		res++,x /= 10;
	return res;
}

int main(){
	scanf("%d",&t);
	for(int T = 1;T <= t;T++){
		scanf("%d",&n);
		int cnt = 0,len = sizes(n);
		string now = "",nt = to_string(n);
		for(int a = 1;a <= 10000;a++){
			now = now + nt; // 将 n 重复 a 遍
			for(int b = max(len * a - 6,1);b < len * a;b++){
				string q = now.substr(0,len * a - b);
				if(to_string(a * n - b) == q)
					ans[++cnt] = Ans{a,b};
			}
		}
		printf("%d\n",cnt);
		for(int i = 1;i <= cnt;i++)
			printf("%d %d\n",ans[i].a,ans[i].b);
	}
	return 0;
}
```

---

## 作者：zengziqvan (赞：5)

本题是一道数学好题。

注：本题解篇幅较长，请耐心观看。

考虑将字符串化为数学的形式。

根据某场 ABC D 题的套路将原式化为等比数列求和的形式。

设 $n$ 转化为字符串形式后长度为 $len$。

那么将 $n$ 重复 $a$ 次后所得到的数值就是：

$$
\begin{aligned}
&\;\;\;\;\sum_{i=1}^{a} n\times 10^{(i-1)\times len}\\
&=n\times(1+10^{len}+10^{2\times len}+\dots +10^{(a-1)\times len})\\
&=n\times \frac{10^{a\times len}-1}{10^{len}-1}
\end{aligned}
$$

由于要去掉最后 $b$ 位，所以还要除以一个 $10^b$ 向下取整。即：

$$
an-b=\lfloor\frac{n\times \frac{10^{a\times len}-1}{10^{len}-1}}{10^b}\rfloor
$$

求满足上述方程的所有 $\leq 1\times 10^4$ 的所有 $a$，$b$。

化简式子：由于将 $n$ 重复 $a$ 次再去掉最后 $b$ 个字符等价于将 $n$ 重复 $a-\lfloor{\frac{b}{len}}\rfloor $ 次再去掉最后 $b\bmod len$ 个字符，所以原式可写为：

$$
\large\lfloor \frac{n\times\frac{10^{(a-\lfloor\frac{b}{len}\rfloor)\times len}-1}{10^{len}-1}}{10^{b\bmod len}}\rfloor
$$

整体考虑无从下手。

发现 $len$ 只有 $3$ 种取值，考虑分类讨论。

1. $len=1$

上式显然可以写成：

$$
n\times \frac{10^{a-b}-1}{9}=an-b
$$

故

$$
\frac{10^{a-b}-1}{9}=\frac{an-b}{n}
$$

由于 $b\le an$，所以 $a-b \ge 0$。

又因为不能重复 $0$ 次，所以 $a-b>0$。

所以等号左边是整数（显然），即等号右也是整数，即 $b$ 是 $n$ 的倍数。

且等号左边一定是 $111\dots 11$ 的形式，所以我们枚举 $n$ 的倍数，根据上述式子算就行了。

```c++
cin>>n;ans.clear();
if(len(n)==1) {
	int pos[4]={1,11,111,1111},c[4]={1,2,3,4};
	for(int k=1;k*n<=10000;++k) {
		int b=k*n; 
		FOR(j,0,3) {
			int a=pos[j]+k;
			if(a<b||a-b!=c[j]) continue;
			if(a<=10000) ans.pb(mkp(a,b));
		}
	}
}
```

为什么 pos 只枚举 $10000$ 以内的 $11\dots 11$ 形式的数就够了？

因为 $\frac{an-b}{n}$ 可写成 $a-k$ 的形式，又因为 $k>0$，并且 $a\le 1\times 10^4$，就证完了。

2. $len=2$

这个需要再讨论 $b$ 的奇偶性。

1. b 是奇数。

$$
\lfloor \frac{n\times\frac{10^{(2a-\lfloor\frac{b}{2}\rfloor\times 2)}-1}{99}}{10}\rfloor
$$

即
$$
\lfloor \frac{n\times\frac{10^{2a-b+1}-1}{99}}{10}\rfloor=an-b
$$

发现左式就是 $n\times\frac{10^{2a-b+1}-1}{99}$ 转化为字符串后去掉最后一位，而最后一位必然是 $n\bmod 10$。所以

$$
\lfloor \frac{n\times\frac{10^{2a-b+1}-1}{99}}{10}\rfloor=\frac{n\times\frac{10^{2a-b+1}-1}{99}-n\bmod 10}{10}
$$

故

$$
n\times\frac{10^{2a-b+1}-1}{99}=10an-10b+n\bmod 10
$$

设 $n\times({10^{2a-b+1}-1})=zl$，根据式子求值，途中判断是否可以整除。再枚举 $b$（奇数）求出 $an$，再求出 $a$ 判断是否满足条件即可。

```c++
int pos[6]={99,9999,999999,99999999,9999999999,999999999999},c[6]={2,4,6,8,10,12};//zl的最大值会很大，在 1e11 左右，故pos开到10^12
FOR(k,0,5) {
	int zl=pos[k]*n;
	if(zl%99) continue;
	zl/=99;zl-=(n%10);
	if(zl%10) continue;
	zl/=10;
	for(int b=1;b<=10000;b+=2) {
		int an=zl+b;
		if(an%n) continue;
		int a=an/n;
		if(c[k]==2*a-b+1&&a<=10000) ans.pb(mkp(a,b));
	}
}
```
2. $b$ 是偶数

$$
n\times\frac{10^{2a-b}-1}{99}=an-b
$$

和上面一样的想法。

```c++
if(len(n)==2) {
	int pos[6]={99,9999,999999,99999999,9999999999,999999999999},c[6]={2,4,6,8,10,12};
	FOR(k,0,5) {
		int zl=pos[k]*n;
		if(zl%99) continue;
		zl/=99;zl-=(n%10);
		if(zl%10) continue;
		zl/=10;
		for(int b=1;b<=10000;b+=2) {
			int an=zl+b;
			if(an%n) continue;
			int a=an/n;
			if(c[k]==2*a-b+1&&a<=10000) ans.pb(mkp(a,b));
		}
	}
	FOR(k,0,5) {
		int zl=pos[k]*n;
		if(zl%99) continue;
		zl/=99;
		for(int b=2;b<=10000;b+=2) {
			int an=zl+b;
			if(an%n) continue;
			int a=an/n;
			if(c[k]==2*a-b&&a<=10000) ans.pb(mkp(a,b));
		}
	}
}
```

3. $len=3$

由于 $len=3$ 的情况只有 $n=100$，可以暴力预处理 $n=100$ 时的答案，在 $n=100$ 的询问中输出。

但显然，暴力比数学要难得多，所以我选择数学。

老生常谈的代入 $len=3$：

$$
\lfloor \frac{n\times\frac{10^{(a-\lfloor\frac{b}{3}\rfloor)\times 3}-1}{999}}{10^{b\bmod 3}}\rfloor=an-b
$$

由于 $n=100$，所以 $n\times\frac{10^{(a-\lfloor\frac{b}{3}\rfloor)\times 3}-1}{999}$ 的最后两位一定是 $0$。

所以可以把取整号去掉。

$$
\frac{n\times\frac{10^{(a-\lfloor\frac{b}{3}\rfloor)\times 3}-1}{999}}{10^{b\bmod 3}}=an-b
$$

和 $len=2$ 且 $b$ 为偶数的情况近乎一致。

值得一提的是：当 $n=100$ 时，无满足条件的 $a$，$b$。

```c++
if(len(n)==3) {
	int pos[4]={999,999999,999999999,999999999999},c[4]={3,6,9,12},pw[4]={1,10,100,1000};
	FOR(k,0,3) {
		int zl=pos[k]*n;
		if(zl%999) continue;
		zl/=999;
		FOR(b,1,10000) {
			int zl2=zl/pw[b%3];
			int an=zl2+b;
			if(an%100) continue;
			int a=an/100,b3=b/3;
			if(a<=10000&&c[k]==(3*a-3*b3)) ans.pb(mkp(a,b));
		}
	}
}
```

总时间复杂度 $\operatorname{O}(VT)$，其中 $V$ 为 $b$ 的值域。

```c++
#include <bits/stdc++.h>
#define LL long long
#define ULL unsigned long long
#define int long long
//#define double long double
#define FOR(i,l,r) for(int i=l;i<=r;++i)
#define ROF(i,r,l) for(int i=r;i>=l;--i)
#define mkp make_pair
#define fr first
#define se second
#define pb push_back
#define cmax(a,b) a=max(a,b)
#define cmin(a,b) a=min(a,b)
using namespace std;
void IOS() {
	ios::sync_with_stdio(false);
	cin.tie(0);
}
void Document() {
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
}
inline int read(){
	int s=0,w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=(s<<3)+(s<<1)+(ch^48);ch=getchar();}
	return s*w;
}
inline void write(int x){
	if(x<0){putchar('-');x=-x;}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
void Tell() {
	//写数据结构注意Build！
	//并查集注意初始化！
	//浮点数类题目过不了优先考虑精度！
	//vector动态开点注意内存重分配！
	//有本地写freopen！没本地别写！！！
	//最后几分钟给我老老实实坐那里，别手贱！！！
}
int t,n;
int len(int x) {
	int res=0;
	while(x) {
		x/=10;
		res++;
	}
	return res;
}
vector<pair<int,int> >ans;
void solve() {
	cin>>n;ans.clear();
	if(len(n)==1) {
		int pos[4]={1,11,111,1111},c[4]={1,2,3,4};
		for(int k=1;k*n<=10000;++k) {
			int b=k*n; 
			FOR(j,0,3) {
				int a=pos[j]+k;
				if(a<b||a-b!=c[j]) continue;
				if(a<=10000) ans.pb(mkp(a,b));
			}
		}
	} else if(len(n)==2) {
		int pos[6]={99,9999,999999,99999999,9999999999,999999999999},c[6]={2,4,6,8,10,12};
		FOR(k,0,5) {
			int zl=pos[k]*n;
			if(zl%99) continue;
			zl/=99;zl-=(n%10);
			if(zl%10) continue;
			zl/=10;
			for(int b=1;b<=10000;b+=2) {
				int an=zl+b;
				if(an%n) continue;
				int a=an/n;
				if(c[k]==2*a-b+1&&a<=10000) ans.pb(mkp(a,b));
			}
		}
		FOR(k,0,5) {
			int zl=pos[k]*n;
			if(zl%99) continue;
			zl/=99;
			for(int b=2;b<=10000;b+=2) {
				int an=zl+b;
				if(an%n) continue;
				int a=an/n;
				if(c[k]==2*a-b&&a<=10000) ans.pb(mkp(a,b));
			}
		}
	} else if(len(n)==3) {
		int pos[4]={999,999999,999999999,999999999999},c[4]={3,6,9,12},pw[4]={1,10,100,1000};
		FOR(k,0,3) {
			int zl=pos[k]*n;
			if(zl%999) continue;
			zl/=999;
			FOR(b,1,10000) {
				int zl2=zl/pw[b%3];
				int an=zl2+b;
				if(an%100) continue;
				int a=an/100,b3=b/3;
				if(a<=10000&&c[k]==(3*a-3*b3)) ans.pb(mkp(a,b));
			}
		}
	}
	cout<<ans.size()<<"\n";
	for(pair<int,int>p:ans) 
		cout<<p.fr<<" "<<p.se<<"\n";
	return ;
}
main() {
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：Aurie (赞：1)

# 1. 暴力

本题首先考虑暴力枚举 $ a $，$ b $ 的值，由于其范围都是 $ 1 \sim 10^4 $，暴力时间复杂度显然是超时的，那么就从范围小的值入手。

# 2. 从范围小的值入手并AC

设 $ x = a \times n-b $，记 $ n $，$ x $ 的字符串格式为 $ n' $，$ x'$。

### 2. 1. 我们考虑枚举 $ x $

$\because b>0 $

$\therefore 0<x<a \times n $

$\therefore len(x')=\log_{10}{x}<log_{10}{a \times n}$


$\because x' $ 只可能是由 $ n' $ 循环拼出的

$\therefore x $ 和 $ x' $ 的每一位是唯一确定的

$\therefore$ 对于每组确定的 $ a $，$ b $，$ x $ 和 $ x' $ 均最多只有 $ \log_{10}{a \times n} $ 种可能（大约是 $ 7 $ 种）

综上所述外层循环枚举 $ x $ 的每种可能：

```cpp
for(int i = 0;i<7;i++){
    x=x*10+n[i%n.length()]-'0';//n为输入的字符串
    ......
}
```

### 2. 2. 在枚举 $ x $ 的基础上我们考虑枚举 $ a $ ,求 $ b $
$\because x = a \times n-b $

$\therefore b = a \times n - x $

$\because b > 0 $

$\therefore a \times n-x \geq 0 $

$\therefore a \geq \frac{x}{n} $

$\therefore a $ 的枚举范围为：$ \frac{x}{n} \leq a \leq 10^4 $

由此得出代码：

```cpp
for(int i = 0;i<7;i++){
    x=x*10+n[i%n.length()]-'0';
    for(int a = x/nn;a<=1e4;a++){
        b = a*nn-x;//O(1)计算b值
        if(b<=0||b>min(10000,a*nn))continue;//注意根据题目处理b的范围
        ......
    }
}
```

### 2. 3. 根据枚举出来的 $ a $ , $ b $ 求出 $ x' $ 并与 $ x $ 相比较，查看其样子是否一致

我们需要根据枚举出的 $ a $，$ b $ 求出 $ x' $，但我们其实不需要 $ x' $ 的具体值。

因为刚刚我们推出 $ x $ 和 $ x' $ 每一位的值在同一组 $ a $，$ b $ 下都是唯一且固定的，因此我们只需要保证：$ x' $ 的长度 $ = x $ 的长度。

由此得出代码：

```cpp
		for(int i = 0;i<7;i++){
			x=x*10+n[i%n.length()]-'0';
			for(int a = x/nn;a<=1e4;a++){
				b = a*nn-x;
				if(b<=0||b>min(10000,a*nn))continue;
				if(i+1==a*n.length()-b){//若它们长度相等
					vec.push_back({a,b}); //记录答案
				}
			}
		}
```
# 5. 时间复杂度分析
外层 for 循环的执行次数是 $ \log_{10}{a \times n} $，由于其不超过 $ 7 $ 因此可以看作一个小常数。内层循环的执行次数是 $ a $ 次，$ a $ 最大为 $ 10^4 $。循环内每次操作均能 $ O(1) $ 完成。如果将外层循环看作小常数，则是 $ O(a) $ 的时间复杂度！否则是 $O(a\log(an))$ 的时间复杂度。
# 4. 最后附上完整代码

```cpp
#include<bits/stdc++.h>

using namespace std;
int t,nn,x,b;
string n;
struct node{
	int a,b;
};
vector<node> vec;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		nn = x = 0;
		vec.clear();
		for(int i = 0;i<n.length();i++){
			nn=nn*10+n[i]-'0';
		}
		for(int i = 0;i<7;i++){
			x=x*10+n[i%n.length()]-'0';
			for(int a = x/nn;a<=1e4;a++){
				b = a*nn-x;
				if(b<=0||b>min(10000,a*nn))continue;
				if(i+1==a*n.length()-b){
					vec.push_back({a,b}); 
				}
			}
		}
		cout<<vec.size()<<endl;
		for(int i = 0;i<vec.size();i++){
			cout<<vec[i].a<<" "<<vec[i].b<<endl; 
		}
	}
  return ~~( 0 ^ 0 )+~~0;
}
```

---

## 作者：Iniaugoty (赞：1)

### [CF1992E Novice's Mistake](/problem/CF1992E)

最短的题解，思维难度最小的做法！

设 $a \times n - b = t$。由 $n, a, b$ 的范围可知必然 $t < 10 ^ 6$，即 $t$ 不超过 $5$ 位；由 2 可知 $t$ 是一个以 $n$ 为循环节的充分长的字符串的前缀。综合这两条，发现 $t$ 只有 $5$ 种不同的可能取值。

那么直接枚举 $t$，然后枚举 $a$，可得 $b = a \times n - t$，记 $x$ 的位数为 $f(x)$，判断是否有 $b > 0$ 并且 $f(t) = f(n) \times a - b$ 即可。由于多测，总运算量约为 $100 \times 5 \times 10 ^ 4$。或许也可以枚举 $b$ 吧，但是感觉上会麻烦很多。

[code](https://codeforces.com/contest/1992/submission/276210781)，超级好写！

---

## 作者：Awsdkl (赞：1)

[题目传送门](https://codeforces.com/contest/1992/problem/E)  
#### 暴力：  
先考虑暴力，我们用外层循环枚举 $a$ ，用内层循环枚举 $b$ ，发现达到了 $O(ab)$，又是多组数据，已经超时了，因此需要考虑优化。  
#### 优化：  
为了方便，下面用 $n_s$ 表示字符串的 $n$，用 $n_i$ 来表示整形的 $n$，并分别用 $|n_s|$ 和 $|n_i|$ 表示其长度或数字个数。  
题目要求我们找出两个数 $a,b$，使 $n_s \cdot (a-b) = n_i \cdot a - b$。  
因为 $1 \le a \le 10^4, 1 \le n_i \le10^2$，则 $1 \le a \cdot n_i \le 10^6$，而又被一个正整数 $b$ 减去后，不难发现，$a \cdot n_i - b$ 的数位一定小于 $6$，则 $|n_s \cdot (a-b)| < 6$，不难推出当 $b$ 最小时，$b_{min} = |n_s| \cdot a - 6$，而 $b_{max} = |n_s| \cdot a$。  
得出结论：  
$b_{max} = |n_s| \cdot a$。  
$b_{min} = b_{max} - 6$。  
因为 $b_{max}$ 可能本身小于 $6$，所以：  
$b_{min} = \max(1,b_{max} - 6)$。  
此时，我们即可只枚举 $a$，然后求出 $b$ 的最大和最小值，再进行判断是否为找的两个数。因为对于 $b$ 的枚举最多循环 $6$ 次，可以忽略，时间复杂度为 $O(a)$。  
#### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

int t;
int n;
int ansn;
int ansa[1000005],ansb[1000005];

int Len(int x) //此函数用于得到一个数的数位个数
{
	int cnt = 0;
	while(x)
	{
		x /= 10;
		cnt++;
	}
	return cnt;
}
int e[15] = {1,10,100,1000,10000,100000}; //懒得思考了，反正最大5位，打一下表qwq。
int mkint(int num,int len,int lenn) //此函数用于生成 ns * a - b这个数的数位个数
{
	int ans = 0;
	for(int i = 1;i <= len;i++)
	{
		ans *= 10;
		ans += (num/e[lenn - (i-1)%lenn-1])%10;
	}
	return ans;
}
int main()
{
	scanf("%d",&t);
	
	while(t--)
	{
		ansn = 0;
		scanf("%d",&n);
		int len = Len(n);
		for(int a = 1;a <= 10000;a++)
		{
			int maxb = len * a;
			int minb = max(1,len * a - 6);
			for(int b = minb;b <= maxb;b++)
			{
                if(a*n-b == 0) continue; //不要忘记特判
				if(a * n - b == mkint(n,len*a-b,len))
				{
					ansa[++ansn] = a;
					ansb[ansn] = b;
				}
			}
		}
		printf("%d\n",ansn);
		for(int i = 1;i <= ansn;i++)
		{
			printf("%d %d\n",ansa[i],ansb[i]);
		}
	}
	
	return O;//防抄
}
```

---

## 作者：dutianchen1 (赞：0)

# Novice's Mistake

### 题面翻译：
在给定 $n$ 的情况下，有下方两种操作可以得到一个数 $x$：

1. 令 $x = a \times n - b$
2. 将 $n$ 复制 $a$ 次，在减去最后 $b$ 位后得到的数即为 $x$。

求有多少对满足两种操作得到的 $x$ 相等的 $a$ 和 $b$。

### 思路简析

假设操作后得到的数为 $x$，给定的 $n$ 的位数为 $len_{n}$，数 $x$ 的位数为 $len_{x}$，那么我们可以得到下方方程组：
$$
\left\{\begin{matrix} 
 b = a \times n - x  \\ 
 b = a \times len_{n} - len_{x}\\ 
\end{matrix}\right. 
$$

我们再将方程组联立，可以得到：
$$
a \times (n - len_{n})= x - len_{x}
$$

我们已知 $n$ 与 $len_{n}$，并且上方式子只需要知道其中两个未知量就可以推得第三个未知量，并且代回方程组就可以得到 $b$ 的值。

再考虑到 $a \in [1,10000]$，$x \in [1,1000000]$ 和 $len_{x} \in [1,6]$，我们枚举两个范围较小的值 $a$ 和 $len_{x}$，再代入求得 $b$ 与 $x$ ，验证是否满足我们要求的性质，满足即可记为答案。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6+5;
inline ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
ll T;
ll n,numx[N],numn[N];
ll lenn,k,x,b,tot;
ll ans[N][2];
void init()
{
	while(k)
	{
		numn[++lenn]=k%10;
		k/=10;
	}
	for(int i=1;i<=6;i++)//预处理x在不同lenx的各种可能
	{
		numx[i]=numx[i-1]*10+numn[i%lenn+1];
	} 
//	for(int i=1;i<=6;i++){
//		cout<<numx[i]<<'\n';
//	}
}
int main()
{
	T=read();
	while(T--){
		n=read();
		lenn=0,tot=0,k=n;
		init();
		for(int a=1;a<=10000;a++)//枚举a 
		{
			for(int lenx=1;lenx<=6;lenx++)//枚举 lenx 
			{
				b=a*lenn-lenx;x=a*(n-lenn)+lenx;
				if(b>=1&&b<=min(10000ll,a*n)&&b==a*n-numx[lenx])
				{
					ans[++tot][0]=a;
					ans[tot][1]=b;
				}
			}
		}
		cout<<tot<<'\n';
		for(int i=1;i<=tot;i++)cout<<ans[i][0]<<' '<<ans[i][1]<<'\n';
	}
	return 0;
}

```

---

## 作者：splendore (赞：0)

### 思路

赛时看题感觉答案应该很少，且可以推出 $n \le 6$ ，可以表过。

打表程序按题面模拟即可，值得注意的是整体复杂度大概在 $10^{10}$ 级别，所以不要使用 string 和 atoi() 等低效实现，即便在 O3 的环境下跑的也非常慢，最好用 char 和 sprintf 等更高效实现。
#### Maker：
```
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int L=1e4+5;
char t[L*10],A[L*10],B[L*10];
int main(){
	freopen("E.cpp","w",stdout);
	for(int n=2;n<=100;++n){
		sprintf(t,"%d",n);
		int len=strlen(t);
		for(int i=len;i<len*5;++i)
			t[i]=t[i-len];
		for(int a=1;a<=10000;++a){
			int bt=min(10000,a*n);
			for(int b=1;b<=bt;++b){
				sprintf(B,"%d",n*a-b);
				int tlen=a*len-b,blen=strlen(B);
				if(blen!=tlen)continue;
				bool bj=1;
				for(int i=0;i<blen;++i)
					if(t[i]!=B[i]){bj=0;break;}
				if(bj)printf("v[%d].push_back({%d,%d})\n",n,a,b);
			}
		}
	}
	return 0;
}
```

#### Code：
```
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
vector<pair<int,int>>v[105];
int main(){
	v[2].push_back({20,18});
	v[2].push_back({219,216});
	v[2].push_back({2218,2214});
	v[3].push_back({165,162});
	v[4].push_back({14,12});
	v[4].push_back({147,144});
	v[4].push_back({1480,1476});
	v[5].push_back({138,135});
	v[7].push_back({129,126});
	v[10].push_back({1262,2519});
	v[11].push_back({12,21});
	v[11].push_back({123,242});
	v[11].push_back({1234,2463});
	v[13].push_back({119,234});
	v[14].push_back({1178,2351});
	v[16].push_back({1154,2303});
	v[18].push_back({1136,2267});
	v[20].push_back({112,220});
	v[21].push_back({11,19});
	v[24].push_back({110,216});
	v[35].push_back({107,210});
	v[68].push_back({104,204});
	v[90].push_back({1033,2061});
	v[94].push_back({1032,2059});
	int T;scanf("%d",&T);
	while(T--){
		int n;
		scanf("%d",&n);
		if(n==1){
			printf("%d\n",9999);
			for(int i=2;i<=10000;++i)
				printf("%d %d\n",i,i-1);
			continue;
		}
		printf("%d\n",(int)v[n].size());
		for(auto i:v[n])
			printf("%d %d\n",i.first,i.second);
	}
	return 0;
}
```

---

## 作者：block_in_mc (赞：0)

## 题目大意

对于字符串 $s$ 与正整数 $n$，定义 $s\times n=\underbrace{s + s + \dots + s + s}_{n\ \text{个}s}$；$s-n$ 为将 $s$ 的后 $n$ 个字符删除后所得的字符串，特别地，若 $n>|s|$，$s-n$ 为空。

对于正整数 $n$，设其对应的字符串为 $n'$，求满足 $n\times a-b=n'\times a-b$ 的二元组 $(a,b)$ 的个数，且 $1\le a,b\le10^4$。

## 解题思路

用 $n'$ 代表正整数 $n$ 的字符串形式，不妨设 $n\times a-b=n'\times a-b=x$：

- 由于 $x=n'\times a-b$，即 $x$ 是由 $n'\times a$ 删除后 $b$ 个字符得到的，所以 $x$ 一定是 $n'+n'+n'+\cdots$ 的前缀；
- 由于 $n\le100$，$a,b\le 10^4$，$x=n\times a-b<10^6$，即 $x$ 最多只有 $6$ 位。

综合来看，以 $n=100$ 为例，可能的 $x$ 值只有 $1,10,100,1001,10010,100100$ 六种。

枚举每一个可能的 $x$，对于每一个 $x$ 再枚举所有可能的 $a$，可用 $n\times a-b=x$ 即 $b=n\times a-x$ 计算出 $b$ 的值。现在，我们只需要判断 $n'\times a-b$ 是否等于 $x$ 即可得知 $(a,b)$ 是否为一组合法的解。上面已经证明，$x=n'\times a-b$ 均为 $n'+n'+n'+\cdots$ 的前缀，只需判断其位数是否相等即可。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
string n;
int t, x, nn;
vector<pair<int, int>> res;
int main() {
    cin >> t;
    while (t--) {
        res.clear();
        cin >> n;
        x = 0, nn = stoi(n);
        for (int i = 0; i <= 6; i++) {
            x = x * 10 + n[i % n.length()] - '0';
            for (int a = x / nn; a <= 10000; a++) {
                int b = a * nn - x;
                if (b <= 0 || b > min(10000, a*nn)) continue;
                if (i + 1 == n.length() * a - b) res.push_back({a, b});
             }
        }
        cout << res.size() << endl;
        for (int i = 0; i < res.size(); i++)
            cout << res[i].first << " " << res[i].second << endl;
    }
    return 0;
}
```

---

## 作者：Garry_HJR (赞：0)

## 题目大意

给定 $n,a,b$，给你两种计算方法。

1. 直接计算 $n\times a - b$ 的值。

2. 把 $n$ 拼接 $a$ 次，抹掉最后面 $b$ 位。

问你对于已经给定的 $n(1\le n \le 100)$，有多少对 $a(1\le a \le 10000),b(1 \le b \le \min(10000,a\times n))$ 满足两种计算方法的值相同。

## 思路分析

给一种不是很正经的做法（确信）。

我们观察到这个数据范围，$n\le 100,a\le 10000$，还有 $100$ 组测试数据，这前面的 $n,a$ 不禁让我们想到了一个词：未雨绸缪。

是的，我们要预处理每个 $n$ 对应的答案。

我们考虑对于每个 $n$ ，枚举 $a,b$ 然后分别带入上面两种计算方式对比答案是否一致即可。

但这样的复杂度很高，无法通过本题目。

那么，这个缺点给我们一个启发：我们能不能只枚举 $n,a$，然后通过这个来推导对应的 $b$ 呢？

是的，我们可以。

古人有句话说：“打蛇打七寸。”观察到方式 $1$ 我们无法看出什么特别之处，于是这个题目的“七寸”就在于这个计算方式 $2$。

仔细一看不难发现，我们所获得的答案必须是由 $n$ 组成的。

考虑最坏的情况，$100 \times 10000 = 1000000$，因此最多 $6$ 位。

我们不妨把 $n$ 的每一位拆了，然后循环加入每一位数到一个存储变量 $x$ 作为计算结果，这一遍加完了从头加下一遍，每一次加的时候推出这个 $b$。

差不多加个 $9$ 位左右就全了。

详细地，原来我们 $n \times a - b$ 就被换成了 $x$，也就是 $n\times a - b =x$，由于我们知道 $n,a,x$，自然可以推 $b = n\times a - x$。

不要忘了 $b$ 的取值范围是 $0 \le b \le \min(10000,a\times n)$，因此要把不合法的去了。

这样的话，复杂度变成了 $\varTheta(kn)$，其中 $k=90000$，就过了。

得解。
## 释放代码

本人代码风格可能不是很好看，请见谅。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
int ch[15];
int mx;
void pro(long long x){
	mx=0;
	int xx=x;
	for(int i=1;i<=9;i++){
		ch[i]=x%10;
		x/=10;
		if(ch[i]!=0)mx=i;
	}
	reverse(ch+1,ch+mx+1);
	for(int i=mx+1;i<=9;i++)ch[i]=ch[i-mx];//拆完了以后我们要再多重复几遍，够9位 
}
vector<pair<int,int> >V[105];
void init(){
	for(int i=1;i<=100;i++){//枚举n 
		pro(i);//把n拆了然后重排 
		for(int j=1;j<=10000;j++){//枚举a 
			long long yuan=i*j;//这个是原来的 n*a 
			long long now=0;
			
			for(int k=1;k<=9;k++){//枚举得数 x 
				//  n*a  -  b = x
				// 已知        已知
				//  -b = x-n*a
				//   b= n*a-x 
				now=now*10; 
				now+=ch[k];//不断增加位数 
				long long cha=yuan-now;//b=n*a-x
				if(cha>min(10000ll,yuan)||cha==0)continue;//移除不符合范围的答案 
				if(mx*j-cha==k)V[i].push_back(make_pair(j,cha));//记录合法答案 
			}
		}
		sort(V[i].begin(),V[i].end());
	}
}
int main(){
	cin>>t;
	init();//预处理 
	while(t--){
		cin>>n;
		cout<<V[n].size()<<endl;
		for(auto to:V[n]){
			cout<<to.first<<' '<<to.second<<endl;
		}
	}
}
```

---

## 作者：Vanilla_chan (赞：0)

[CF1992E Novice's Mistake](https://codeforces.com/contest/1992/problem/E)

同步于[个人博客](https://vanilla-chan.cn/blog/2024/07/15/CF1992E-Novice-s-Mistake/)。

一个粗浅的办法就是，枚举 $a\in[1,1000],b\in[1,\min\{10000,a\cdot n\}]$，使用等比数列求和公式推式子，注意需要对于 $n$ 的位数和 $b$ 的值分类讨论。

但注意到 $1\le t\le 100$，这个算法是过不去的。

为了接下来方便说明，我们规定：
- $n \otimes a-b$ 是指将 $n$ 当作字符串重复 $a$ 次再删去后 $b$ 位得到的数。
- $n\cdot a-b$ 是指数学意义上的乘法。
- $| n | $ 是指 $n$ 的位数。

注意到 $n \cdot a-b\le 10^6$，这意味着 $n \otimes a-b$ 不能超过 $6$ 位，也就是 $1\le | n \otimes a-b | \le6$，所以 $| n| \cdot a-6\le b\le | n | \cdot a-1$。这样我们可以缩小 $b$ 的枚举范围，只需要枚举 $6a$ 次即可。

对于每一组 $(a,b)$，我们只需生成 $n \otimes a$ 的前 $| n | \cdot a-b$ 位，判断其是否与 $na-b$ 相等，即可做到快速判断 $n \otimes a-b=na-b$ 是否成立。

## Code

```cpp
vector<pair<int,int>>ans;
int main()
{
	int t=1;
	cin>>t;
	while(t--)
	{
		LL n;
		ans.clear();
		cin>>n;
		string nn=to_string(n);
		for(LL a=1;a<=10000;a++)
		{
			for(LL b=max(1ll,nn.size()*a-6);b<=nn.size()*a-1;b++)
			{
				string x;
				int wei=nn.size()*a-b;
				for(int i=0;i<wei;i++)
				{
					x.push_back(nn[i%nn.size()]);
				}
				if(x==to_string(n*a-b)) ans.push_back(make_pair(a,b));
			}
		}
		
		cout<<ans.size()<<endl;
		for(unsigned int i=0;i<ans.size();i++){
			cout<<ans[i].first<<" "<<ans[i].second<<endl;
		}
	}
	return 0;
}
```

感谢管理员们对我的题解格式的耐心斧正，让我意识到了写作的规范性。

---

## 作者：_Ubuntu_ (赞：0)

## 题意

给出 $n$，你需要求出将 $n$ 拼接 $a$ 次后删掉最后 $b$ 位的结果是否和 $n \times a - b$ 的结果相等，给出所有满足条件的 $a、b$ 的值。     

数据范围：  $1 \le a \le 10000$、$1 \le n \le 100$、$1 \le b \le \min(10000, a \cdot n)$。



## 思路

观察数据范围，我们很容易得出 $n \times a - b$ 的位数不超过 $5$ 位。

那么，我们就可以利用上面的信息再加上题中信息——结果是由 $n$ 拼接 $a$ 次删掉 $b$ 位而形成的，就可以拼凑出 $n \times a - b$ 的结果，一共有 $5$ 种。

接着，枚举 $a$ 和 $5$ 种结果，然后检查是否符合条件即可。

## code:

```c++
void solve()
{
	int n;
	cin >> n;
	string str = to_string(n);
	vector<string> s(6);
	vector<int> res(6);
	for(int i=1, idx = 0; i<=5; i++, idx++)
	{
		if(idx == str.size())
			idx = 0;
		s[i] = s[i-1] + str[idx];
		// cout << s[i] << '\n';
		res[i] = stoi(s[i]);
	}

	int w = 0, x = n;
	while(x)
		x /= 10, w++;


	vector<pii> ans;
	for(int a=1; a<=10000; a++)
	{
		// a * n - b == res
		for(int i=1; i<=5; i++)
		{
			int b = a * n - res[i];
			if(b > 0 && b < min(a * n, 10000) && a * w - i == b)
				ans.push_back({a, b});
		}
	}	
	cout << ans.size() << '\n';
	for(pii tmp : ans)
		cout << tmp.first << ' ' << tmp.second << '\n';
}
```

---

