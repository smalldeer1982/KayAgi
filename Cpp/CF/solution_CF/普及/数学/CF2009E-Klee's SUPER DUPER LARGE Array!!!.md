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

## 作者：cly312 (赞：0)

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

