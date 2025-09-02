# Continued Fractions

## 题目描述

A continued fraction of height $ n $ is a fraction of form ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF305B/19ade84928d3d628a6e212b03adbbf8bc0856736.png). You are given two rational numbers, one is represented as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF305B/ae456f9650d5b3ca46e54c303d07fec088f6ad5e.png) and the other one is represented as a finite fraction of height $ n $ . Check if they are equal.

## 说明/提示

In the first sample ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF305B/a7429bd0927ab226e00de904e1ba240c58b09318.png).

In the second sample ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF305B/a01a984749367ddde5131c663127bc347e31f0a2.png).

In the third sample ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF305B/4db9464841d1b99996f6c98f75df85058aee123f.png).

## 样例 #1

### 输入

```
9 4
2
2 4
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
9 4
3
2 3 1
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
9 4
3
1 2 4
```

### 输出

```
NO
```

# 题解

## 作者：XXh0919 (赞：2)

简单的一道题。

首先暴力是肯定不行的（~~作为懒人的我也不想写高精~~），于是一个很简单的办法就出现了。我们只需要在每次计算时进行约分，约到最后就判断两数分子分母是否相等就行了。注意：$p$ 和 $q$ 也要进行约分！

**Code：**

```cpp
#include<bits/stdc++.h>
#define int long long//记得开 long long
using namespace std;
const int N=3e5+15;

int n,q,p;
int a[N];

signed main(){
	scanf("%lld %lld %lld",&p,&q,&n);
	int t=__gcd(p,q);
	p/=t,q/=t;//约分 
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	int zi=a[n],mu=1;
	for(int i=n-1;i>=1;i--){
		int t=__gcd(zi,mu);
		zi/=t,mu/=t;//约分 
		swap(zi,mu); 
		zi=mu*a[i]+zi;//化成带分数 
	}
	if(p==zi&&q==mu) puts("YES");
	else puts("NO");
	return 0;
} 
```


---

## 作者：王梓涵 (赞：2)

# CF305B Continued Fractions 题解

## 1. 题目大意
第一行输入两个数 $p$ 和 $q$，下一行先输入一个数 $n$，再输入 $n$ 个数 $a_1$，$a_2$，$\cdots$，$a_i$。

判断 $\dfrac{p}{q}$ 是否等于 $a_{1} + \dfrac{1}{a_{2} + \dfrac{1}{\ldots + a_{n}}}$。

其中 $n \leqslant 90$，$1 \leqslant q \leqslant p \leqslant 10^{18}$，$1 \leqslant a_i \leqslant 10^{18}$。

## 2. 解题思路
这道题肯定不能暴力做，由于 $1 \leqslant q \leqslant p \leqslant 10^{18}$，$1 \leqslant a_i \leqslant 10^{18}$，精度肯定是不够的。

可以把每次输入的整数 $a$，移到等式左边，如果输入的 $a$ 大于左边的式子，没结束就出现了有一项等于 $0$，那么一定输出 $NO$。

## 3. 参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	long long p, q, n, a; // 由于本题数据过大，需要开long long
	scanf("%lld%lld%lld", &p, &q, &n);
	while (n != 0)
	{
		scanf("%lld", &a);
		if (q == 0 || p / q < a)
		{
			break;
		}
		long long t = q;
		q = p - a * q;
		p = t;
		n--;
		// 完成a到等式左边，可以判断了
	}
	if (n || q)
	{
		cout << "NO" << endl;
	}
	else
	{
		cout << "YES" << endl;
	}
	return 0; // 完结撒花
}
```


---

## 作者：EasonLiang (赞：1)

做[这道题](https://www.luogu.com.cn/problem/CF305B)的时候想出一种**奇妙的**解法，发现题解区没有，遂分享一番。

## 题意

给定 $10^{18}$ 以内的正整数 $p,q$、正整数列 $\{a_n\}$，其中 $n\le90$，判断 $\dfrac{p}{q}$ 与 $a_1+\dfrac{1}{a_2+\dfrac{1}{...+\dfrac{1}{a_n}}}$ 是否相等。

## 思路

选定一个大质数 $P$，我们可以将题中分数转换为**模 $P$ 意义下**所对应的整数，根据题意暴力计算，最终比较二者结果。

对于一个分数 $\dfrac{p}{q}$，其在模 $P$ 意义下相当于它的分子乘以分母的逆元，即：

$$\dfrac{p}{q} \equiv p \times q^{-1} \pmod P$$

如果不了解求乘法逆元的线性算法，可以参考 [P3811 【模板】乘法逆元](https://www.luogu.com.cn/problem/P3811) 中的[这篇讲解](https://www.cnblogs.com/zjp-shadow/p/7773566.html#%E7%BA%BF%E6%80%A7%E7%AE%97%E6%B3%95)，里面有原理证明和代码示例。

这一操作相当于给有理数分配相对应的**哈希值**，因而可能存在“**哈希冲突**”，可以采用**双哈希**或**多哈希**减小冲突概率。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int maxn = 9e1 + 20;
const ll mod[2] = {ll (1e9 + 7), ll (1e7 - 9)}; // 双哈希，注意要用大质数
int n;
ll p, q, a[maxn], val[2][2]; // val[0] 数组存 p/q 的值，val[1] 数组存连分数的值

ll inv (ll x, ll mod) { // 在 log 时间内求出逆元
    return x ^ 1 ? (mod - mod / x) * inv (mod % x, mod) % mod : 1;
}

int main () {
    scanf ("%lld%lld%d", &p, &q, &n);

    for (int i = 1; i <= n; ++i) scanf ("%lld", &a[i]);

    val[0][0] = (p % mod[0]) * inv (q % mod[0], mod[0]) % mod[0];
    val[0][1] = (p % mod[1]) * inv (q % mod[1], mod[1]) % mod[1];
    val[1][0] = a[n] % mod[0]; val[1][1] = a[n] % mod[1];
    
    for (int i = n - 1; i >= 1; --i) // 模拟题意计算连分数的值
        val[1][0] = (inv (val[1][0], mod[0]) + a[i]) % mod[0],
        val[1][1] = (inv (val[1][1], mod[1]) + a[i]) % mod[1];

    return !printf ((val[0][0] ^ val[1][0] || val[0][1] ^ val[1][1]) ? "NO" : "YES"); // 判断哈希值是否相等并输出结果
}
```

---

## 作者：ztxtjz (赞：1)

## 【题意】
判断$p/q$是否等于那一串式子
## 【思路】
暴力肯定是不行的，精度不够。考虑记录每一次的分子、分母，并通过$gcd$不断约分，最后判断两式的分子、分母是否都相等，相等输出$YES$，不等输出$NO$。

注意，$p$和$q$也要进行约分，否则会WA（惨痛教训）。
## 【代码】
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n,fz,fm=1,p,q,a[100],ans;  //fz是分子，fm是分母
ll gcd(ll a,ll b){return a==0?b:gcd(b%a,a);}  //最大公约数
int main()
{
	cin>>p>>q>>n;
	ll t=gcd(p,q);  //p、q约分
	p/=t,q/=t;
	for(int i=1;i<=n;i++) cin>>a[i];
	fz=a[n];  //分子初始化
	for(int i=n-1;i;i--)
	{
		ll t=gcd(fz,fm);  //最大公约数
		fz/=t,fm/=t;  //分子、分母约分
		swap(fz,fm);  //分数取倒数
		fz=a[i]*fm+fz;  //通分
	}
	if(p==fz&&q==fm) printf("YES");
	else printf("NO");
	return 0;
}
```

---

## 作者：lgx57 (赞：1)

# CF305B Continued Fractions 题解
~~一道水绿~~
## 1.题意
就是问你 $\frac{p}{q}=a_1+\frac1{a_2+\frac1{...+\frac1{a_n}}}$ 这个等式是否成立。
## 2.思路
显然，直接暴力做会精度丢失。所以我们考虑更朴素的做法。  
根据我们小学二年级就学过的分数加减法，我们可以将每一个 $ a_{i}$ 从右边移到左边，然后再取倒数，最后只需要判断  $\frac{p}{q}$ 是否与 $a_{n}$ 相等即可。
## 3.参考代码
码风较丑，不喜勿喷。
```cpp
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
const int inf=1e9;
void fio(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
}
void ll(){
	#define int long long
}
long long a[95];
signed main(){
	ll();
	long long p,q;
	cin>>p>>q;
	int cnt=__gcd(p,q);
	p/=cnt,q/=cnt;
	int n;
	cin>>n;
	for (int i=1;i<=n;i++){
		cin>>a[i];
	}
	for (int i=1;i<n;i++){
		p-=q*a[i];//相减
		swap(p,q);//取倒数
		cnt=__gcd(p,q);
		p/=cnt;
		q/=cnt;//约分
	}
	if (p==a[n]&&q==1){//判断
		cout<<"YES";
	}
	else{
		cout<<"NO";
	}
	return 0;//完结撒花！
```

---

## 作者：ZLCT (赞：0)

# CF305B Continued Fractions
## 题目翻译
给定 $p,q$ 以及 $n$ 个数 $a_1…a_n$，问 $\frac{p}{q}$ 是否等于 $\displaystyle a_1+\frac{1}{a_2+\frac{1}{…+\frac{1}{a_n}}}$。
## solution
首先我们肯定不能暴力计算后面式子的值，这个精度是不可能够的，直接 $a_2=10^{18}$ 都会直接归零。\
那我们接下来考虑一步一步地抽丝剥茧。\
对于一开始的 $a_1$，我们是好处理的，直接在 $\frac{p}{q}$ 上通分并减去 $a_1$ 即可。那式子就变成了 $\frac{p-a_1q}{q}$ 是否等于 $\displaystyle \frac{1}{a_2+\frac{1}{…+\frac{1}{a_n}}}$。观察左边我们发现它就是 $\displaystyle a_2+\frac{1}{a_3+\frac{1}{…+\frac{1}{a_n}}}$ 的倒数，那一个数若等于另一个数，它们的倒数肯定也相等。因此原式可以变成 $\frac{q}{p-a_1q}$ 是否等于 $\displaystyle a_2+\frac{1}{a_3+\frac{1}{…+\frac{1}{a_n}}}$。我们令 $p'=q,q'=p-a_1q$，这个式子就又变成我们一开始的形式了，我们不断递归求解直到减完 $a_n$ 后判断是否为 $0$ 即可。\
注意这里有个小问题，两个 $10^{18}$ 级别的数相乘会爆 long long，那我们有两种解决办法，一个是直接开 `__int128`，一种是在 $p<a_iq$ 时直接跳出循环，反正这种情况也一定不合法。这种情况可以把 $q$ 除到左边变成 $\frac{p}{q}<a_i$，这样就不会爆了。
## code
```cpp
#include<bits/stdc++.h>
#define int __int128
using namespace std;
pair<int,int>num;
signed n;
signed main(){
    long long a,b;cin>>a>>b;
    num={a,b};
    cin>>n;
    for(int i=1;i<=n;++i){
        long long y;cin>>y;
        int x=y;
        if(x>num.first/num.second){
            cout<<"NO\n";
            return 0;
        }
        x=x*num.second;
        num.first-=x;
        if(num.first==0&&i!=n){
            cout<<"NO\n";
            return 0;
        }
        if(i==n&&num.first){
            cout<<"NO\n";
            return 0;
        }
        swap(num.first,num.second);
    }
    cout<<"YES\n";
    return 0;
}
```

---

## 作者：QWQ_123 (赞：0)

对于原式 $\frac{p}{q}$ 可以将其化为带分数的形式：$k\frac{p - kq}{q}(p-kq<q)$，那么我们发现 $a_1=k$，然后继续由于是 $a_1+\frac{1}{a_2+\dots}$，所以考虑将 $\frac{p-kq}{q}$ 化成：$\frac{1}{q\div (p-kq)}$，对于下面的 $\frac{q}{p-kq}$ 就可以按照 $a_1$ 的做法做了。

但是要注意一下，对于最后一个，要是 $a_n=1$，那么 $\frac{q}{p-kq}$ 的整数应为 $a_{n-1}+1$ 且 $(p-kq) | q$。

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
ll p, q;
ll n;
ll a[110];
 
ll gcd(ll a, ll b) {
	return !b ? a : gcd(b, a % b);
}
 
int main() {
	scanf("%lld%lld%lld", &p, &q, &n);
	for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
	if (n == 1) {
		ll G = gcd(p, q);
		p /= G, q /= G;
		if (q != 1 || p != a[1]) puts("NO");
		else puts("YES");
		return 0;
	}
	for (int i = 1; i <= n; ++i) {
		if (q == 0) {
			puts("NO");
			return 0;
		}
 
		ll t = (p / q);
		if (t != a[i] && i != n - 1) {
			puts("NO");
			return 0;
		}
 
		ll tmp = p;
		p = q;
		q = tmp - t * q;
 
		if (i == n - 1) {
			ll G = gcd(p, q);
			p /= G, q /= G;
			if (q == 0) {
				if (p - 1 == 0 && a[n] == 1) {
					puts("YES");
					return 0;
				}
			}
			if (q != 1 || p != a[n]) {
				puts("NO");
				return 0;
			}
 
			puts("YES");
			return 0;
		}
 
	}
	return 0;
}
```

---

## 作者：very_easy (赞：0)

题目意思很简单，就是求两个分数是否相同。

思路很明确就是将两个分数都化简为最简分数然后直接比较就好了。

$\frac{p}{q}$ 应该很好求，关键就是后面那一大串式子怎么求，直接求肯定不行，除非你想使用~~臭名昭著~~的高精度算法。

可以考虑一边求一边约分，将假分数直接换成带分数计算会简单很多。

约分需要用到求最大公约数，我个人比较喜欢用辗转相除法（又叫欧几里得算法），还不会的同学可以先去看一下[最大公约数](http://ybt.ssoier.cn:8088/problem_show.php?pid=2021)（洛谷居然没有一道最大公约数的板子题）。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
#define int long long//emm…… 
const int N=100;
int a[N];
int gcd(int a,int b){
	return b?gcd(b,a%b):a;//gcd模板 
}
signed main(){
	int n,q,p;
	cin>>p>>q>>n;
	int tmp=gcd(q,p);
	p/=tmp,q/=tmp;//先约分 
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int fz=a[n],fm=1;
	for(int i=n-1;i>=1;i--){
		int t=gcd(fz,fm);
		fz/=t,fm/=t;//约分 
		swap(fz,fm); 
		fz=fm*a[i]+fz;//假分数化带分数，a[i]相当于整数部分 
	}
	if(p==fz&&q==fm) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	return 0;
}

```

---

## 作者：drah_yrev (赞：0)

## 题意

输入 $p$，$q$，$a_1$，$a_2$，…$a_n$，问 $\frac{p}{q}$ 是否等于 $a_1+\frac{1}{a_2+\frac{1}{…+a_n}}$。

## 思路
暴力精度不够。我们可以求每一次的分子和分母，并不断约分，最后判断两个分数是否相等。

## 代码
```cpp
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
int p,q,a[100005],n;
int a1,a2;
void add(int a,int b,int c,int d){
	int val=b*d/__gcd(b,d);
	a*=val/b;
	c*=val/d;
	b=val,d=val;
	a+=c;
	a1=a/__gcd(a,b),a2=b/__gcd(a,b);
}
int main(){
	cin>>p>>q>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	a1=a[n],a2=1;
	for(int i=n-1;i>=1;i--){
		swap(a1,a2);
		add(a[i]*a2,a2,a1,a2);
	}
	a1/=__gcd(a1,a2),a2/=__gcd(a1,a2);
	q/=__gcd(q,p),p/=__gcd(q,p);
	if(p==a1&&q==a2)cout<<"YES";
	else cout<<"NO";
	return 0;
}

```


---

## 作者：_Clown_ (赞：0)

这题肯定不能暴力，精度太低。

我们考虑记录分子和分母。

如果最后结果分子和分母都对应相等，那我们就认为正确。

记得将P，Q也约分好。

约分就是将两个数同时除以他们的Gcd。

答案呼之欲出。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long Ll;
Ll P,Q;
Ll Total;
Ll Array[101];
inline Ll GetGcd(Ll A,Ll B)
{
	return B==0?A:GetGcd(B,A%B);
}
inline void Offset(Ll &A,Ll &B)
{
	register Ll Gcd;
	Gcd=GetGcd(A,B);
	A/=Gcd;
	B/=Gcd;
}
int main(void)
{
	register int i;
	cin>>P>>Q;
	cin>>Total;
	for(i=1;i<=Total;i++)
	{
		cin>>Array[i];
	}
	Offset(P,Q);
	register Ll AnsA,AnsB;
	AnsA=Array[Total];
	AnsB=1;
	for(i=Total-1;i>=1;i--)
	{
		Offset(AnsA,AnsB);
		swap(AnsA,AnsB);
		AnsA=Array[i]*AnsB+AnsA;
	}
	if(P==AnsA&&Q==AnsB)
	{
		cout<<"YES"<<endl;
	}
	else
	{
		cout<<"NO"<<endl;
	}
	return 0;
}
```
# THE END

---

