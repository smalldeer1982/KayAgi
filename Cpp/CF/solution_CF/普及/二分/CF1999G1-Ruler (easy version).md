# Ruler (easy version)

## 题目描述

本题是问题的简单版本。该版本与困难版之间的唯一区别是在这个版本中，你最多可以进行 $10$ 次查询。

这是一道交互题。

有一把有 $1001$ 个刻度的尺子，刻度分别为 $1 \sim 1001$。不幸的是，尺子丢失了一个刻度 $x$（$2 \le x \le 999$）。当你用尺子量一个长度为 $y$ 的物体时，尺子量出的结果为：
- 若 $y < x$，尺子将会量出正确的结果 $y$。
- 否则，尺子将会量出错误的结果 $y + 1$。

你需要找出丢失的刻度 $x$。你可以每次提供两个 $1$ 至 $1000$ 内的整数 $a,b$，你将会收到尺子量出的 $a$ 的长度与尺子量出的 $b$ 的长度之积。

你可以进行最多 $10$ 次询问。

## 样例 #1

### 输入

```
2

18

25


9999```

### 输出

```
? 3 5

? 4 4

! 4
? 99 100

! 100```

# 题解

## 作者：cjh20090318 (赞：5)

很简单的交互题，不怎么需要动脑子。

## 题意

**这是一道交互题。**

和困难版本不同的是，你**最多**可以进行 $10$ 次查询。

有一个秘密的尺子，上面缺少一个数字 $x$。当你测量一个长度为 $y$ 的物体时，尺子会报告以下值：

- 如果 $y < x$，尺子（正确地）测量物体长度为 $y$。
- 如果 $y \ge x$，尺子错误地测量物体长度为 $y+1$。

你需要找出 $x$ 的值。为此，你可以进行以下形式的查询：

- $\texttt{? a b}$，作为响应，我们将用我们的尺子测量一个 $a \times b$ 的矩形的边长，并将结果相乘，向你报告测量出的矩形面积。

找出 $x$ 的值，回答格式为 $\texttt{! x}$。

## 分析

答案具有单调性，且 $\log_2 999$ 略小于 $10$，考虑二分。

每次可以询问两个值，如果二分同一个值的话未免显得有点浪费。

困难版本中最多询问 $7$ 次，且 $\log_3 999$ 略小于 $7$，考虑三分。

初始时 $l = 2, r = 999$，设 $m_1 = l + \left\lfloor \dfrac{r-l} 3 \right\rfloor, m_2 = r - \left\lfloor \dfrac{r-l} 3 \right\rfloor$。

查询 $m_1 \times m_2$ 组成矩形测出来的面积 $S$，有如下三种情况：

- $S = (m_1 + 1) (m_2 + 1)$，说明 $x \le m_1 \le m_2$，$r \gets m_1$。
- $S = m_1 (m_2 + 1)$，说明 $m_1 < x \le m_2$，$l \gets m_1 + 1, r \gets m_2$。
- $S = m_1 m_2$，说明 $m_1 \le m_2 < x$，$l \gets m_2 + 1$。

最后得到的 $l$ 即为缺失的数字 $x$，每次询问区间长度会缩小到原来的 $\dfrac 1 3$ 倍，询问次数可以保证。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#define FLUSH fflush(stdout)
using namespace std;
int check(const int x,const int y){
	printf("? %d %d\n",x,y),FLUSH;
	int ret;scanf("%d",&ret);
	return ret;
}
void solve(){
	int l=2,r=999;
	for(int m1,m2,ret;l<r;){
		m1=l+(r-l)/3,m2=r-(r-l)/3;
		ret=check(m1,m2);
		if(ret==(m1+1)*(m2+1)) r=m1;
		else if(ret==m1*(m2+1)) l=m1+1,r=m2;
		else l=m2+1;
	}
	printf("! %d\n",l),FLUSH;
}
int main(){
	int T;scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：Pink_Cut_Tree (赞：3)

# CF1999G1 Ruler (easy version) 题解

[Luogu Link](https://www.luogu.com.cn/problem/CF1999G1)|[CF Link](https://codeforces.com/problemset/problem/1999/G1)|[My AC submission](https://codeforces.com/contest/1999/submission/274939687)。

一眼二分。

### 解析

答案具有单调性，加之 $2^{10}=1024>999$，所以可以二分，复杂度也是可以的。

我们固定一边为 $1$，另一边为 $mid$，如果给出的答案为 $mid$，则断点一定在后面，否则在前面。特殊地，若答案大于 $2$ 倍的 $mid$，断点一定是 $1$。

### 代码

其实交之前可以自己测几发。


```cpp
#include<bits/stdc++.h>
using namespace std;
int T,x;
signed main(){
	cin>>T;
	while(T--){
		int l=1,r=999;
		bool flag=0;
		while(l<r){
			int mid=l+r>>1;
			cout<<"? 1 "<<mid<<"\n";
			cin>>x;
			if(x>=2*mid){
				cout<<"! 1"<<endl; flag=1; break;
			}
			if(x==mid){
				l=mid+1;
			}
			else{
				r=mid;
			}
		}
		if(flag==0){
			cout<<"! "<<l<<endl;
		}	
	}
return 0;
}
```

---

## 作者：WsW_ (赞：3)

我切的第一道交互。

---
## 思路
学过 OI 的都知道，$9<\log_2 999<10$，数据范围明示二分。  
考虑如何将这道题变成[P1947 猜数](https://www.luogu.com.cn/problem/P1947)。  

如果我们可以直接询问一条长度为 $a$ 的线段多长，我们就能判断 $x$ 和 $a$ 的大小关系。  

询问一个 $1\times a$ 的矩形多大，实际上就是询问一条长度为 $a$ 的线段多长。  

所以每次询问 $1\times a$，然后这道题就变成猜数了。  
接着二分就行了。

---
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
 
void work(){
	int l=2,r=999,mid,ans;
	int s;
	while(l<=r){
		mid=l+r>>1;
		printf("? 1 %d\n",mid);
		fflush(stdout);
		scanf("%d",&s);
		if(s==mid){
			l=mid+1;
		}
		else{
			r=mid-1;
			ans=mid;
		}
	}
	printf("! %d\n",ans);
	fflush(stdout);
}
 
int main(){
	scanf("%d",&T);
	while(T--){
		work();
	}
	return 0;
}
```

---

## 作者：__const_int__ (赞：1)

### Description
交互题。存在一个值 $x$，每次询问两个数 $p$ 和 $q$。如果 $p \geq x$，那么 $p \gets p+1$。如果 $q \geq x$，那么 $q \gets q+1$。返回 $p \times q$。$2 \leq x \leq 999$，至多询问 $10$ 次。
### Analysis
首先答案具有单调性（尺子的刻度是具有单调性的），考虑二分。$2^{10} = 1024$，大于 $999$，这样就保证最多询问 $10$ 次。设左边界 $l$ 初始值为 $2$，右边界 $r$ 初始值为 $999$，中值 $mid$ 为 $\lfloor \dfrac{l+r}{2} \rfloor$，每次询问 $1$ 和 $mid$，如果得到的值等于 $mid$，说明$x \geq mid$，缩小左边界，$l \gets mid+1$。如果得到的值大于 $mid$，说明 $x \leq mid$，缩小右边界，$r \gets mid$。
### Code
```cpp
#include<bits/stdc++.h>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t;
  std::cin >> t;
  while(t--){
    int l = 2, r = 999;
    while (l < r) {
      int mid = (l + r) / 2, area;
      std::cout << "? " << 1 << " " << mid << std::endl;
      std::cin >> area;
      if(area > mid){
        r = mid;
      }else{
        l = mid + 1;
      }
    }
    std::cout<< "! " << l << std::endl;
  }
}
```

---

## 作者：xxxalq (赞：1)

[洛谷链接](https://www.luogu.com.cn/problem/CF1999G1) & [CF链接](http://codeforces.com/problemset/problem/1999/G1)

# 思路

看到询问次数小于等于 $10$ 且 $x\le 999$ 所以很容易想到二分来求解。

我们每次只询问 `? 1 mid` 其中 $mid$ 为我们要询问的数，即二分的中点，因为 $x\ge2$，所以查询 $1$ 的时候一定会返回 $1$，这样我们就把二维的询问转化成了一维的询问。问题就变成了有一个数 $x$，你最多可以进行 $10$ 次询问，每次询问一个数，如果这个数小于 $x$，则交互库返回这个数，否则返回这个数加一。求出这个数 $x$。

此时问题就会变得非常简单了，如果交互库返回的数等于你询问的数，证明你这个数小于答案，且比他小的数都不是答案，如果返回的数等于你询问的数加一，那么证明这个数大于答案，且比它大的数都不是答案。这样每次就能将可能的答案范围缩小一半，进而求出解。

# 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int T;
int main(){
	cin>>T;
	while(T--){
		int l=2,r=999,mid;
		while(l<r){
			mid=(l+r)/2;
			cout<<"? 1 "<<mid<<endl;
			int x;
			cin>>x;
			if(x>mid){
				r=mid;
			}else{
				l=mid+1;
			}
		}
		cout<<"! "<<l<<endl;
	}
	return 0;
}
```

---

## 作者：ICU152_lowa_IS8 (赞：1)

两种做法：二分和三分。

二分只能通过本道题，三分可以通过本题的[加难版](https://www.luogu.com.cn/problem/CF1999G2)，故本篇题解仅讲解三分（二分其它题解有讲）。

猜数字的另一种形式，假设当前知道答案在 $[l,r]$ 当中：

找到将区间“三等分”的两个点 $l_1$ 和 $l_2$（假设 $l_1\le l_2$），并向程序询问：

如果返回 $(l_1+1)\times(l_2+1)$，答案必然在 $[l,l_1]$ 中。

如果返回 $l_1\times(l_2+1)$，答案必然在 $[l_1+1,l_2]$ 中。

如果返回 $l_1\times l_2$，答案必然在 $[l_2+1,r]$ 中。

一次可以将区间的长度变为原来的 $\dfrac{1}{3}$，可以通过本题。

另外注意，询问的时候数字不能大于 $1000$（赛时因为这个挂了）。

代码：


```
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int t;
	scanf("%lld",&t);
	while(t--){
		int l=2,r=999,l1,l2,ans;
		while(l<=r){
			l1=l+(r-l)/3;
			l2=r-(r-l)/3;
			printf("? %lld %lld",l1,l2);
			cout<<endl;
			int s;
			scanf("%lld",&s);
			if(s==(l1+1)*(l2+1)){
				r=l1-1;
				ans=l1;
			}
			else if(s==l1*(l2+1)){
				l=l1+1;
				ans=l1+1;
				r=l2-1;
			}
			else{
				ans=l2+1;
				l=l2+1;
			}
		}
		printf("! %lld",ans);
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：wmrqwq (赞：1)

需要我教你怎么 AK div.4 吗？

# 题目链接

[CF1999G1](https://www.luogu.com.cn/problem/CF1999G1)

[CF1999G2](https://www.luogu.com.cn/problem/CF1999G2)

# 解题思路

考虑三分。

我们发现，我们每次可以给出两个数字来作为限制。

因此我们可以将这两个数字设为断开区间的点，由于尺子上缺少的数字只有一个，因此我们可以通过每一次询问来减少 $\dfrac{2}{3}$ 的剩余区间长度。

询问次数 $\log_3 V$ 次，可以通过 G1 和 G2，其中 $V$ 为值域。

# 参考代码

```cpp
/*
Tips:

你数组开小了吗？
你MLE了吗？
你觉得是贪心，是不是该想想dp？
一个小时没调出来，是不是该考虑换题？
打 cf 不要用 umap！！！

记住，rating 是身外之物。

该冲正解时冲正解！

Problem:

算法：

思路：

*/
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
//#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define x first
#define y second
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
#define maxqueue priority_queue<ll>
#define minqueue priority_queue<ll,vector<ll>,greater<ll>>
ll pw(ll x,ll y,ll mod){if(x==0)return 0;ll an=1,tmp=x;while(y){if(y&1)an=(an*tmp)%mod;tmp=(tmp*tmp)%mod;y>>=1;}return an;}
void Max(ll&x,ll y){x=max(x,y);}
void Min(ll&x,ll y){x=min(x,y);}
ll _t_;
void _clear(){}
ll n,m;
ll ans,An;
ll ask(ll x,ll y){
	cout<<"? "<<x<<' '<<y<<endl;
	ll z;
//	An++;
	cin>>z;
//	z=(x+(x>=ans))*(y+(y>=ans));
	return z;
}
/*
8
*/
ll L,R;
void solve()
{
	_clear();
	L=2,R=999;
	while(L<R)
	{
		ll Mid1=L+(R-L)/3,
		   Mid2=R-(R-L)/3;
		ll now=ask(Mid1,Mid2);
		if(now==Mid1*Mid2)
			L=Mid2+1;
		else if(now==Mid1*(Mid2+1))
			L=Mid1+1,R=Mid2;
		else
			R=Mid1;
	}
	cout<<"! "<<L<<endl;//<<" queries = "<<An<<endl;
	An=0;
}
int main()
{
//	IOS;
	_t_=1;
 	cin>>_t_;
	while(_t_--)
		solve();
// 	forl(i,2,_t_)
//		ans=i,solve();
	QwQ;
}
```

---

## 作者：PineappleSummer (赞：0)

Div4 放交互题，一点不会。

此题与困难版的区别在于这题至多可以询问 $10$ 次，而困难版至多可以询问 $7$ 次。

设 $n=10^3$，这题可以通过 $\mathcal O(\log_2n)$ 的二分做法，而困难版只能用 $\mathcal O(\log_3n)$ 的三分做法。

**此篇题解仅讲解三分做法。**

初始 $l=1,r=10^3$，设 $L=l+\left\lfloor\dfrac{r-l}{3}\right\rfloor,R=r-\left\lfloor\dfrac{r-l}{3}\right\rfloor$。

那么每次询问就是 $[L,R]$ 这个区间。

分类讨论一下返回的值 $x$。

- 如果 $x=L\times R$，说明目标位置大于 $R$，$l\gets R+1$。

- 如果 $x=L\times (R+1)$，说明目标位置在 $L+1$ 与 $R$ 之间，$r\gets R$，$l\gets L+1$。

- 如果 $x=(L+1)\times (R+1)$，说明目标位置小于等于 $L$，$r\gets L$。

$l$ 的值就是最后答案。时间复杂度 $\mathcal O(\log_3n)$。

```cpp
void solve () {
	int l = 1, r = 1e3;
	while (l < r) {
		int L = l + (r - l) / 3, R = r - (r - l) / 3;
		cout << "? " << L << ' ' << R << '\n';
		int init; cin >> init;
		if (init == -1) exit (0);
		else if (init == L * R) l = R + 1;
		else if (init == L * (R + 1)) r = R, l = L + 1;
		else if (init == (L + 1) * (R + 1)) r = L;
	}
	cout << "! " << l << endl;
}
```

---

## 作者：block_in_mc (赞：0)

## 题目大意

**本题为交互题**。有一个尺子，但是上面缺失了数 $x$，你需要找出 $x$ 的值（$2\le x\le999$）。使用这个尺子测量长度为 $n$ 的线段时，若 $n<x$，则测量结果时正确的；否则测量结果为 $n+1$。你每次可以询问用这把尺子测量实际宽度为 $a$，长度为 $b$ 的矩形的面积值（即用这把尺子分别测量长和宽的结果的乘积）。

你有 $10$ 次（Easy Version）或 $7$ 次（Hard Version）询问机会。

## 解题思路

首先考虑 Easy Version 如何解决。按照题意，如果我们询问 $1$ 和 $n$，若返回值为 $n$，则有 $x>n$；若返回值为 $n+1$，则有 $x\le n$。显然可以进行二分，由于 $2^{10}>999$，能够通过 Easy Version。

但是这个解决方案中没有利用矩形的第二条边，考虑如何利用——三分。但是这个三分是与二分类似的，而不是寻找单峰函数的峰值。具体地，在二分的基础上，令 $p=\lfloor\dfrac{l+r}{3}\rfloor$，$mid_1=l+p$，$mid_2=r-p$，我们将区间 $l\sim r$ 分为了三部分。我们询问 $mid_1$ 和 $mid_2$：

- 若返回值为 $mid_1mid_2$，则 $mid_2< x\le r$；
- 若返回值为 $mid_1(mid_2+1)$，则 $mid_1<x\le mid_2+1$；
- 若返回值为 $(mid_1+1)(mid_2+1)$，则 $l\le x\le mid_1$.

需要注意的是上面的不等号是否能够取等。

由于 $3^7>999$，三分可以通过 Hard Version。

那为什么我们正常不使用三分呢？因为正常情况下，我们对 $mid$ 进行两次合法性检查能够用二分缩小 $\dfrac{3}{4}$ 的范围，但是要求知道第一次合法性检查的结果再进行第二次，而这里只能同时进行，但也因此两次合法性检查只能缩小 $\dfrac{2}{3}$ 的范围。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, l, r, mid1, mid2, ans;
int main() {
    cin >> t;
    while (t--) {
        l = 2, r = 999;
        while (l < r) {
            mid1 = l + (r - l) / 3, mid2 = r - (r - l) / 3;
            cout << "? " << mid1 << " " << mid2 << endl;
            cin >> ans;
            if (ans == mid1 * mid2) l = mid2+1;
            else if (ans == mid1 * (mid2 + 1)) l = mid1 + 1, r = mid2;
            else r = mid1;
        }
        cout << "! " << l << endl;
    }
    return 0;
}
```

---

## 作者：GenesisCrystal (赞：0)

简单

## Solution

我们令 $l = 1,r=1000$，使用二分，每次求 $l \times \dfrac{l + r}{2}$，如果等于 $l \times \dfrac{l + r}{2}$，那么没有的尺码一定在 $\dfrac{l + r}{2}$ 以上，那么令 $l = \dfrac{l + r}{2} + 1$，否则令 $r = \dfrac{l + r}{2}$。

这样可以在 $[\log_2 1000] = 10$ 次内通过。

## Code

```cpp
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <queue>
#include <map>
#include <set>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using db = double;

int t;

int main() { 
  for (cin >> t; t; t--) {
    int l = 1, r = 1000;
    while (l < r) {
      int mid = (l + r)  >> 1;
      cout << "? " << l << ' ' << mid << endl;
      int x;
      cin >> x;
      if (x == l * mid) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    cout << "! " << l << endl;
  }
  return 0; 
}
```

---

## 作者：__O_v_O__ (赞：0)

我们观察到：$9<\log_{2}(999)<10$，于是这题一定使用二分。

如何二分？我们每次取 $l$ 和 $r$ 的中点 $m$，询问 $m\times m$ 的矩形，看结果是否正确。如果正确，则左端点更新为 $m$，否则右端点更新为 $m$。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
signed main(){
	ios::sync_with_stdio(0),cin>>t;
	while(t--){
		int l=1,r=1000;
		while(l<r){
			int mi=l+r>>1;
			cout<<"? "<<mi<<' '<<mi<<'\n';
			cout.flush();
			int x;
			cin>>x;
			if(x!=mi*mi)r=mi;
			else l=mi+1;
		}
		cout<<"! "<<l<<'\n';
		cout.flush();
	}return 0;
}
```

---

## 作者：_O_v_O_ (赞：0)

[点此查看这个蒟蒻写的该场比赛所有题目的题解](https://www.luogu.com.cn/article/opat7vrj)

我们注意到 $\log_2 {1000}$ 是接近 $10$ 的，于是考虑二分。

具体来说，我们二分到了一个 $mid$ 时，每次输出 $\tt ?\ 1\ mid$，如果输入的数 $x=mid$，那么 $l=mid$，否则 $r=mid$。



```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+5;
int T;
int x;

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>T;
	while(T--){
		int r=1000,l=0;
		while(l+1<r){
			int mid=l+r>>1;
			cout<<'?'<<' '<<mid<<' '<<1<<endl;
			cin>>x;
			if(x==mid) l=mid;
			else r=mid;
		}
		cout<<'!'<<' '<<r<<endl;
	}
	return 0;
}
```

---

## 作者：incra (赞：0)

赛后 VP，光速 AK，爽爽爽！

### Sol

考虑到只能询问 $7$ 次，但是问的两条边，所以实际上我们可以问 $14$ 次。

考虑三分，设当前三分区间 $[l,r]$，三分的节点分别为 $m1,m2$，不妨设 $m1<m2$，设询问 $m1,m2$ 的结果为 $x$，接下来分情况讨论：

1. 当 $x=m1\times m2$，此时 $m1,m2$ 均小于 $x$，那么 $r\gets m1-1$。
2. 当 $x=(m1+1)\times m2$，此时 $m1\le x < m2$ 那么 $l\gets m1,r\gets m2-1$。
3. 当 $x=(m1+1)\times (m2+1)$，此时 $x\ge m2$ 那么 $l\gets m2$。

建议读者自行思考二分的开闭区间，对于理解有帮助。

操作次数为 $\log_3 999\le 7$，足以通过 G1 和 G2。
### Code
```
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cassert>
#include <chrono>
#include <random>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
#define IOS ios :: sync_with_stdio (false),cin.tie (0),cout.tie (0)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
int fastio = (IOS,0);
#define puts(s) cout << (s) << endl
int T;
int main () {
	cin >> T;
	while (T--) {
		int l = 1,r = 999;
		while (l < r) {
			int mid1 = l + (r - l + 1) / 3,mid2 = r - (r - l + 1) / 3;
			cout << "? " << mid1 << ' ' << mid2 << endl;
			int x;
			cin >> x;
			if (x == mid1 * mid2) l = mid2 + 1;
			else if (x == mid1 * (mid2 + 1)) l = mid1 + 1,r = mid2;
			else if (x == (mid1 + 1) * (mid2 + 1)) r = mid1;
			else exit (-1);
		}
		cout << "! " << l << endl;
	}
	return 0;
}
```

---

## 作者：qinshi0308 (赞：0)

## 一、题目大意：
这是一道交互题。

有一把尺子，但是有一个问题：尺子上少了一个数 $x$。这就导致用它测量一件实际长度 $y$ 的物体时，如果 $y<x$，则测量出来的结果是正确的，否则，如果 $y\ge x$，则测量出来的长度是 $y+1$。现在请你求出 $x$ 的值（$2\le x \le 999$）。

对于每组数据，你最多可以问 $10$ 个问题。

提问格式为 `? a b`，意思是给评测机一个实际为 $a\times b$（$1\le a,b \le 1000$）的长方形，评测机会用这把有问题的尺子测量这个长方形的长和宽，并把测量的两个结果相乘得到长方形的面积并把这个结果返回。

给出答案的格式为 `! x`，其中 $x$ 是你的答案。

有 $t$ 组数据。

## 二、思路：

首先看题，第一眼：这不二分吗？就是询问格式有点怪，好像不太好处理……

第二眼：好像可以询问一个 $1\times n$ 的长方形，而且 $2\le x \le 999$，所以测量 $1$ 一定正确，所以只要返回的面积和实际面积不相等，就说明 $x\le n$，然后就可以愉快的二分啦。

**小提示：交互题输出后记得刷新缓冲区，可以使用 `cout<<endl;`、`cout.flush();` 或 `fflush(stdout);`。**

## 三、代码：

```cpp
# include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int l=0,r=1000;
        while(l<r){
            int mid=(l+r)/2;
            cout<<"? 1 "<<mid<<endl;
            int x;
            cin>>x;
            if(x>mid){
                r=mid;
            }else{
                l=mid+1;
            }
        }
        cout<<"! "<<l<<endl;
    }
    return 0;
}
```

---

## 作者：BLuemoon_ (赞：0)

[link](https://www.luogu.com.cn/record/171136085)

## 题意

**交互题，最多问 $10$ 次**

你有一个缺了一个刻度 $x$ 的尺子，当实际长度 $y \ge x$ 时，会测出 $y+1$，否则会测出 $y$。

你可以询问实际为 $a \times b$ 矩形用这个尺子测出的面积，请求出 $x$。

## 思路

二分板子，按正常二分，只是改为询问正方形面积，平方即可。

## 代码

```cpp
// BLuemoon_
#include <bits/stdc++.h>
 
using namespace std;
 
int t, l, r, p;
 
bool C(int x) {
  cout << "? " << x << ' ' << x << endl;
  cin >> p;
  return p > (x * x);
}
 
int main() {
  for (cin >> t; t; t--) {
    for (l = 1, r = 1000; l <= r;) {
      int mid = (l + r) >> 1;
      if (C(mid)) {
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    cout << "! " << l << endl;
  }
  return 0;
}
```

---

## 作者：int_stl (赞：0)

一道二分板子题，Clist 评分居然有 $1600$？

我们考虑使用二分求解，对于每一次二分，我们都询问 $1$ 和 $mid$。设每次询问的结果为 $q$，若 $q = mid$，说明答案小了，此时增大左边界，否则缩小右边界。

时间复杂度 $O(n \log n)$。

代码请读者自行实现。

---

## 作者：nightwatch.ryan (赞：0)

### 思路
这是一道交互题。

首先，尺子的刻度是具有单调性的，你想到了什么？一定是二分对不对。其次题目中提到，$2 \leq x \leq 999$，并且至多询问 $10$ 次，$\lceil \log_2 999 \rceil = 10$，很显然了，这道题就是用二分做。

设左边界 $l$ 为 $2$，右边界 $r$ 为 $1000$。每次询问 $1 \times \lfloor \dfrac{l+r}{2} \rfloor$ 的矩形，也就是 $1 \times mid$ 的矩形。如果询问得到的结果大于 $mid$，说明这个值比 $x$ 要大，将 $r$ 设为 $mid$，如果询问得到的结果等于 $mid$ 则说明 $mid \leq x$，将 $l$ 设为 $mid+1$。如果 $l \geq r$ 则结束二分。

最后输出 $l$ 即可。注意你需要清空缓冲区。
### 代码
```cpp
#include<iostream>
#define int long long
void solve(int T){
	if(T==0)return;
	int l=2,r=1000;
	while(l<r){
		int mid=(l+r)>>1;
		std::cout<<"? "<<1<<" "<<mid<<std::endl;
		int ans;
		std::cin>>ans;
		if(ans==1*mid)l=mid+1;
		else r=mid;
	}
	std::cout<<"! "<<l<<std::endl;
	solve(T-1);
}
signed main(){
	int T;
	std::cin>>T;
	solve(T);
}
signed main(){
	int T;
	std::cin>>T;
	solve(T);
}
```

---

