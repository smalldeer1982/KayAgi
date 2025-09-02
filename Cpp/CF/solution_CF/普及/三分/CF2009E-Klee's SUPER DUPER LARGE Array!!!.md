# Klee's SUPER DUPER LARGE Array!!!

## 题目描述

### 题目大意

你将得到一个长度为 $n$ 的序列 $a=[k,k+1,k+2,\dots, k+n-1]$，请求出 $S$ 的值，其中

$$S=\min\limits_{1\le x\le n}|(\sum\limits_{i=1}^x a_i)-(\sum\limits_{i=x+1}^n a_i)|$$

## 样例 #1

### 输入

```
4
2 2
7 2
5 3
1000000000 1000000000```

### 输出

```
1
5
1
347369930```

# 题解

## 作者：Harekaze (赞：3)

感谢洛谷管理员对此题解的审核！

## 1. 题面简述

题目要求我们计算出一段长度为 $n$ 的序列，将其分成前后两段连续的序列，令 $S$ 等于后面一段序列的和减去前面一段序列的和的绝对值，要求使 $S$ 的值最小，输出最小的 $S$ 。

## 2. 题目分析

题目要求将序列分成两段，我们不妨前一段序列的长度为 $R$ ，那么两个序列分别为 $[k,k+R-1]$ 与 $[k+R,k+n-1]$ ，不难发现这两段序列均为等差数列，那么可用高斯求和得，前后两段序列的和为：

- $s1=kR+\displaystyle\frac{1}{2}(0+R-1)R=kR-\displaystyle\frac{1}{2}(R^2-R)$ 

- $s2=k(n-R)+\displaystyle\frac{1}{2}(R+n-1)(n-R)=kn-kR+\displaystyle\frac{1}{2}(n^2-R^2-n+R)$

那么我们即可求得 $S=|s2-s1|=|kn-2kR+\displaystyle\frac{1}{2}(n^2-2R^2+2R-n)|$ ，这样我们只要枚举断点 $R$ 即可，但是暴力的时间复杂度是接受不了的，所以我们考虑其他更优算法。

注意到 $R-S$ 函数类似于二次函数，拥有单峰，故可以考虑使用三分，三分写法可参考[三分模版题](https://www.luogu.com.cn/problem/P1883)。

## 3. 代码 

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,k;
ll check(ll r)
{
	return abs(k*n-2*k*r+(n*n-2*r*r+2*r-n)/2);
}
int main()
{
	ll T;
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&k);
		ll l=1,r=n,ans=LONG_LONG_MAX;
		while(l<=r)
		{
			ll mid1=(2*l+r)/3;
			ll mid2=(2*r+l)/3;
			if(check(mid1)<check(mid2))
			{
				if(check(mid1)<=ans)ans=check(mid1);
				r=mid2-1;
			}
			else
			{
				if(check(mid2)<=ans)ans=check(mid2);
				l=mid1+1;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```
- [AC 记录](https://codeforces.com/contest/2009/submission/321791009)

---

## 作者：coderJerry (赞：3)

Upd：格式已经修改好，请管理员再次审核。
#
先把题目要你求最小值的式子：$|a_1+a_2+...+a_x-(a_{x+1}+a_{x+2}+...+a_n)|$ 化简一下。

代入每一项后，得到原式 $=|k+(k+1)+...+(k+x-1)-[(k+x)+(k+x+1)+...+(k+n-1)]|$。

两段等差数列求和一下，得到原式 $=|\frac{(k+k+x-1)\times x}{2}-\frac{(k+x+k+n-1)\times (n-x)}{2}|$。

化简并整理，得到原式 $=|x^2+(2k-1)x+\frac{n(2k+n-1)}{2}|$。

令 $f(x)=x^2+(2k-1)x+\frac{n(2k+n-1)}{2}$，由绝对值的几何意义，可知题目等价于要求 $x \in  \operatorname{N^*}∪ $ $[1,n]$ 时 $f$ 离 $0$ 最近的那个值。由于 $a$ 序列都是正数且单调递增，所以 $x$ 越大，函数值越大，换句话说 $f$ 在 $[1,n]$ 上单调递增。

到这里就可以二分求解了。但是都到这里了，为什么不继续往后推呢？

又因为 $n≥2$，所以 $f(1)<0,f(n)>0,f(1)f(n)<0$。综上可知 $f$ 在区间 $[1,n]$ 内必定有且只有一根。

设这个根为 $t$，则显然与 $0$ 最接近的两个函数值是 $f(\lfloor t \rfloor)$ 与 $f(\lfloor t \rfloor +1)$，取个绝对值找其中的较小值即可。时间复杂度 $O(T)$。如果用二分做，那时间复杂度就要再乘上一个 $\log n$。

赛时代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int f(int x,int b,int c){
    return (int)abs(x*x+b*x-c);
}
signed main(){
    int t,n,k;
    cin>>t;
    while(t--){
        cin>>n>>k;
        int b=2*k-1,c=(n*(2*k+n-1)/2);
        double delta=1.0*b*b+4.0*c;
        double x=1.0*(sqrt(delta)-1.0*b)/2.0;
        //cout<<delta<<" "<<x<<" \n";
        int nx=(int)x;
        cout<<min(f(nx,b,c),f(nx+1,b,c))<<endl;
    }
    return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

菜，不会二分做法。

由于 $x=f(i)=\left|\displaystyle\sum_{j=k}^{k+i-1}j-\sum_{j=k+i}^{k+n-1}j\right|$ 的取值是下凸的，可以三分 $i$ 计算其最小值。化简 $f(i)=\left|\dfrac{(2k+i-1)i}{2}-\dfrac{(2k+i+n-1)(n-i)}{2}\right|$ 即可 $O(1)$ 计算 $f(i)$。

# Code
```cpp
#include<bits/stdc++.h>
int T,n,m;
inline long long calc(int x){
	return std::abs(((m+(m+x-1ll))*x>>1)-(((m+x)+(m+n-1ll))*(n-x)>>1));
}
int l,r,ans;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		l=1;r=n;
		while(l<=r){
			int mid1=l+(r-l)/3,mid2=r-(r-l)/3;
			if(calc(mid1)<calc(mid2))ans=mid2,r=mid2-1;
			else ans=mid1,l=mid1+1;
		}
		printf("%lld\n",calc(ans));
	}
	return 0;
}

```

---

## 作者：cly312 (赞：1)

设 $m$ 为 $a_1+\dots+a_i$，$n$ 为 $a_{i+1}+\dots+a_n$。

我们可以使用二分查找来搜索 $i$，使得 $m-n$ 为最小的负数。

如果我们移动到 $i+1$，则此时 $m-n$ 为最小的正数。答案是两种情况下的最小绝对值。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
pair<long long ,long long >val(long long mid,long long k,long long n){
	long long val1=(mid+k-1+k)*mid/2;
	long long val2=(k+n-1+k)*n/2-val1;
	return{val1,val2};
}
int main(){
	int t;
	cin>>t;
	while(t--){
		long long n,k;
		cin>>n>>k;
		long long lo=1,hi=n,curr=1;
		while(lo<=hi){
			long long mid=(lo+hi)/2;
			auto[a,b]=val(mid,k,n);
			if(b>a){
				curr=mid;
				lo=mid+1;
			}else{
				hi=mid-1;
			}
		}
		auto[a1,b1]=val(curr,k,n);
		auto[a2,b2]=val(curr+1,k,n);
		cout<<min(b1-a1,a2-b2)<<endl;
	}
	return 0;
}

```

---

## 作者：forever516 (赞：0)

# 题意
题意清晰，不做赘述。

# 解法
观察题目，这些数都是有序的，这具有二分的前提要求。然后再往下看，让我们找从
$1$
到
$n$
的最优
$i$。这完全可以二分答案求解。再加上有序区间和可以使用高斯求和公式，这就使时间复杂度变得可行了。

还有就是我们要注意，二分查找出来的答案不一定最优，它只保证答案接近正解，此二分答案保证正解在区间
$ans$
到
$ans+1$
内，因此最后我们要再特判一下再输出！

详见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,k;
void make(int &a,int &b,int tmp){
	a=(tmp+2*k-1)*tmp/2;//s1
	b=(2*k+n-1)*n/2-a;//s2
	//求出到tmp的两个数列前缀和（等差数列求和） 
}
int find(){
	int l=1,r=n,ans=1,a,b,t1,t2,t3,t4;
	while(l<=r){//二分答案 
		int mid=(l+r)>>1;
		make(a,b,mid);
		if(a<b)l=mid+1,ans=mid;//注意记录ans 
		else r=mid-1;
	}
	make(t1,t2,ans),make(t3,t4,ans+1);
	return min(abs(t1-t2),abs(t3-t4));
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>k;
		cout<<find()<<"\n";
	}

	return 0;
}
```

---

## 作者：ZHR100102 (赞：0)

整数三分板子，以前一直都不会打，现在记录一下。

# 观察

推式子可知，$S=|\cfrac{(2k+x-1)x-(2k+n-1+x)(n-x)}{2}|$。

观察可知他是单峰的，显然能够三分。

# 三分

先放板子。

## 凹函数

```cpp
ll l=1,r=n,lmid,rmid,lans,rans;
while(l<r)
{
    lmid=l+(r-l)/3,rmid=r-(r-l)/3;
    lans=cal(lmid),rans=cal(rmid);
    if(lans<=rans)r=rmid-1;
    else l=lmid+1;
}
return l;
```

## 凸函数

```cpp
ll l=1,r=n,lmid,rmid,lans,rans;
while(l<r)
{
    lmid=l+(r-l)/3,rmid=r-(r-l)/3;
    lans=cal(lmid),rans=cal(rmid);
    if(lans>=rans)r=rmid-1;
    else l=lmid+1;
}
return l;
```

## 细节

这里三分不用特判边界问题的原因是当区间长度小于等于 $3$ 的时候它的 $lmid$ 和 $rmid$ 都只会取到边界上，所以是一点一点地进行缩小范围的，所以不需要特判边界，最后的答案取 $l$ 或者 $r$ 都是可以的。这种写法 $l$ 与 $r$ 的初始值是闭区间。

同时注意三分只能用于严格单峰的函数，不能存在一段函数使得这段函数值都相等，因为这样就无法判断单峰的位置了。但是如果这一段就是峰顶应该是可以的，因为三分默认把 $lmid$ 和 $rmid$ 值相等的情况当成单峰在中间的情况处理。

所以这题就是个整数三分的板子了，直接处理即可，时间复杂度 $O(t\log n)$。

# 代码

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define eb(x) emplace_back(x)
#define pb(x) push_back(x)
#define lc(x) (tr[x].ls)
#define rc(x) (tr[x].rs)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using pi=pair<int,int>;
ll n,k;
ll cal(ll x)
{
    return abs(((2*k+x-1)*x-(2*k+n-1+x)*(n-x))/2);
}
void solve()
{
    cin>>n>>k;
    ll l=1,r=n,lmid,rmid,lans,rans;
    while(l<r)
    {
        lmid=l+(r-l)/3,rmid=r-(r-l)/3;
        lans=cal(lmid),rans=cal(rmid);
        if(lans<=rans)r=rmid-1;
        else l=lmid+1;
    }
    cout<<cal(l)<<'\n';
}
int main()
{
    //freopen("sample.in","r",stdin);
    //freopen("sample.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--)solve();
    return 0;
}
```

---

## 作者：Meickol (赞：0)

题意：求 $\large S=\min\limits_{1\le x\le n}|(\sum\limits_{i=1}^x a_i)-(\sum\limits_{i=x+1}^n a_i)|$。

根据等差数列求和公式，我们可以知道 $S$ 表达式中的前一项：
$$
\large \sum \limits _{i=1}^x a_i=\dfrac{x (k+k+x-1)}{2}=\dfrac{x(2k+x-1)}{2}
$$
同理，$S$ 表达式的后一项：
$$
\large \sum \limits _{i=x+1}^n a_i=\dfrac{(n-x) (k+x+k+n-1)}{2}=\dfrac{(n-x)(2k+n+x-1)}{2}
$$
于是 $S$ 就可以被 $x,k,n$ 表示出来：
$$
\large S=  \left \lvert \dfrac{x(2k+x-1)}{2} - \dfrac{(n-x)(2k+n+x-1)}{2} \right \rvert
$$


因为这个式子中 $n,k$ 均为已知量，因而这个 $S$ 是仅有一个 $x$ 变量的函数。

为了方便分析其凹凸性，可将该函数化简，进而发现上式等价于：
$$
\large S=  \left \lvert \dfrac{2x^2+(4k-1)x+C}{2}\right \rvert
$$
显然这是一个凹函数，最后我们对这个函数用 **三分法** 求谷值即可解决本题的最小值问题。



```cpp
LL n,k;
LL calc(LL x){
	return abs(x*(2*k+x-1)/2-(n-x)*(2*k+n+x-1)/2);
}
void solve(){
	cin>>n>>k;
	LL l=1,r=n;
	while(l<r){
		LL m1=l+(r-l)/3,m2=r-(r-l)/3;
		if(calc(m1)>calc(m2)) l=m1+1;
		else r=m2-1;
	}
	cout<<calc(l);
}
```

---

## 作者：cqbzrjx (赞：0)

[原题传送门](https://codeforces.com/contest/2009/problem/E)

## 前置知识

- [等差数列（数学知识）](https://zhuanlan.zhihu.com/p/365793447)
- [二分](https://blog.csdn.net/Mr_dimple/article/details/114656142/)

## 分析

题目要求我们前 $i$ 个数取正，后面 $n - i$ 个数取负，然后汇总求和。列一个等差数列，那么前 $i$ 个数的总和为 $\frac{(2 \times k + i - 1) \times i}{2} $，反之后面 $n - i$ 个数的总和为 $\frac{(2 \times k + n + i - 1) \times (n - i)}{2}$，求差之后变为 $\frac{(-2 \times k \times n + 4 \times k \times i - n ^ 2 + n + 2 \times i ^ 2 - 2 \times i)}{2}$。这是一个单调递增的函数，我们需要查找绝对值越小的数，也就是越趋近于 $0$ 的数。设第一个的正值的位置为 $vis$，那么答案就是 $\min(\left\vert a_{vis - 1} \right\vert,\left\vert a_{vis} \right\vert)$。又因为它是单调函数所以使用二分答案。仔细思考发现这个函数一定会存在至少一个负值和至少一个正值，所以不用担心找不到导致越界的问题。

时间复杂度：$O(t \times \log n)$。

## Code

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i = a;i <= b;i++)
#define per(i,a,b) for(int i = a;i >= b;i--)
#define pb push_back
#define PII pair<int,int>
using namespace std;
typedef long long ll;
ll t,n,k;
inline ll alc(ll x)
{
	return (-2 * k * n + 4 * k * x - n * n + n + 2 * x * x - 2 * x) / 2;
}
inline bool check(ll x)
{
	return alc(x) >= 0;
}
inline void solve()
{
	cin>>n>>k;
	ll l = 1,r = n;
	while(l < r)
	{
		ll mid = l + r >> 1;
		if(check(mid))  r = mid;
		else l = mid + 1;
	}
	cout<<min(abs(alc(l - 1)),abs(alc(l)))<<"\n";
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}
```

[AC submissions](https://codeforces.com/contest/2009/submission/280007199)

---

