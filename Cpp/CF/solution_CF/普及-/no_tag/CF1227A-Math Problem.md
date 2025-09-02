# Math Problem

## 题目描述

你的数学老师给了你以下问题：

在 $x$ 轴上有 $n$ 个段，$[l_1;r_1],[l_2;r_2]\ldots[l_n;r_n]$。段 $[l;r]$ 包括了边界，即它是 $x$ 的集合，其中 $l \leq x \leq r$。段 $[l;r]$ 的长度等于 $r-l$。

两个段 $[a;b]$ 和 $[c;d]$ 有一个公共点（相交）如果存在一个 $x$ 并满足 $a \leq x \leq b$,$c \leq x \leq d$。例如，$[2;5]$ 和 $[3;10]$ 有一个公共点，但是 $[5;6]$ 和 $[1;4]$ 没有。

你应该添加一个线段，使该线段与每个给定线段至少有一个公共点，并且尽可能短（既具有最小长度）。所需的段可以是一个点（及长度为零的一个段）。添加的段可能在给定的 $n$ 段中，也可能不在其中。

换句话说，您需要找到一个段 $[a;b]$，使得 $[a;b]$ 和每个 $[l_i;r_i]$ 有一个公共点，并且 $b-a$ 是最小的。

## 说明/提示

在样例的第一个测试用例中，我们可以选择分段 $[5;7]$ 作为答案。它是与所有给定线段至少有一个公共点的最短线段。

## 样例 #1

### 输入

```
4
3
4 5
5 9
7 7
5
11 19
4 17
16 16
3 12
14 17
1
1 10
1
1 1
```

### 输出

```
2
4
0
0
```

# 题解

## 作者：fengqiao17 (赞：3)

## Solution
1. 多组数据可以定义函数 $helper(n)$ 。
2. 题目说要求一个最短区间 $a$ 到 $b$，要求对于每一个区间 $l$ 和 $r$ ，都会有一个公共点 $x$ ，那么我们就有思路啦！统计每一个区间，求最小的右端点 $mi$ 和最大的左端点 $ma$ ，返回 $ma - mi$，这样每条线段都会有公共点与我们现在的这条线段相交 ，然后就做完了。~~然后第一个点就愉快地WA了~~

   问题出在哪里呢？注意！！当给定的几条线段本来就拥有公共点时， $ma - mi$ 会小于 $0$ ，此时我们再 $\max(0,ma - mi)$ 一遍即可。

------------

## Code
```cpp
//author:fengqiao17
//转载请标明地址：https://616673.blog.luogu.org/solution-cf1227a
#include<bits/stdc++.h> //万能头
#define ll long long //定义长long long，因为答案可能爆int
using namespace std;
ll helper(int n){ //多组数据用函数
  ll ma = -1e18 , mi = 1e18; //注意最小、最大值为1e18和-1e18
  for(int i = 1 ; i <= n ; i++){
    ll l , r;
    cin>>l>>r; //左右端点
    ma = max(ma , l); //最大左边界
    mi = min(mi , r); //最小右边界
  }
  return ma - mi;
}
int main(){
  int t;
  cin>>t;
  while(t--){
    int n;
    cin>>n;
    cout<<max((ll)0 , helper(n))<<endl; //注意为负数的情况
  }
  return 0; //完结撒花~
}
```

---

## 作者：_Above_the_clouds_ (赞：0)

# 思路：
为了使 $a$ 和 $b$ 区间至少与每个 $l$ 和 $r$ 区间有一个公共点，且 $b$ 与 $a$ 的差最小。

只需找出所有 $l$ 的最大值和所有 $r$ 的最小值，使区间最小，这样每个 $l$ 和 $r$ 的区间都至少有一个公共点。

再判断如果最大值与最小值的差小于 $0$，说明不存在这个区间，输出 $0$；否则，输出它们的差即可。

# 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, l, r, minn, maxx;

int main() {
	cin >> t;
	while (t--) {
		cin >> n;
		minn = 1e9, maxx = 0;
		for (int i = 1; i <= n; i++) {
			cin >> l >> r;
			maxx = max(maxx, l);
			minn = min(minn, r);
		}
		if (maxx - minn < 0)
			cout << 0 << "\n";
		else
			cout << maxx - minn << "\n";
	}
	return 0;
}
```




---

## 作者：QcpyWcpyQ (赞：0)

### 题意

寻找一个区间$\left[a,b\right]$，使得对于任意的区间$\left[l_i,r_i\right]$都与其有公共点，并且让区间长度最小。

### 思路

- 因为一个区间由它的左右端点决定，那么考虑如何求出端点来。

- 若想覆盖所有区间，那么只用考虑最左与最右边的区间，中间的一定是被覆盖的。若覆盖最左区间，因为使长度最小，只用覆盖它的右端点。同理最右区间只覆盖左端点。

- 注意坑点，当最左区间与最右区间有交点时，右端点会比左端点大，答案将是一个负数。因此将答案与 $0$ 比较输出最大值即可。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int T,n,l,r;

int main(){
	cin>>T;
	while(T--){
		cin>>n;
		int lmax=0,rmin=(int)1e9;
		for (int i=1;i<=n;++i){
			cin>>l>>r;
			lmax=max(lmax,l);
			rmin=min(rmin,r);
		} 
		cout<<max(0,lmax-rmin)<<endl;
	}
	return 0;
}

```


---

## 作者：__JiCanDuck__ (赞：0)

### 题意

找到一个段 $[a;b]$，使得 $[a;b]$ 和每个 $[l_i;r_i]$ 有一个公共点，并且 $b-a$ 是最小的。


### 思路

思路还是很简单的，只需要看最大的端点，和最小的端点的差。为什么呢？因为对于每一个 $[l_i;r_i]$ 至于要考虑最大的节点，和最小的节点。其他的我不关心，因为最极限的两个点都满足要求，中间的为什么不满足呢？

### 代码
``` cpp 
#include<bits/stdc++.h>
#define ll long long  //不开long long 见祖宗。
using namespace std;
ll t,n,ma,mi;  //祖数和每组的数和最大和最小。
int main()
{
  cin>>t;
  while(t--)
  {
    ma=-1e17,mi=1e17;//保险其见，开大点。
    cin>>n; 
    for(ll i=1;i<=n;i++)
    { 
      ll l,r;
      cin>>l>>r;
      mi=min(mi,r);//小的。
      ma=max(ma,l);//大的。
    }
    cout<<max((ll)0 ,(ma-mi))<<endl;//可能是一个负数哦，所以和0取max。
  }
  return 0;
}
```

---

## 作者：shipeiqian (赞：0)

# 思路

根据题意，我们可以推断出，为了让每条线段都有公共点，最短的一条线的左端就要往右靠，即 $max_l$；它的右端就要往左靠，即 $min_r$。但当给定的几条线段原本就拥有公共点 $x$ 时，右端点会比左端点大，将是一个负数，那么就用 $max$ 直接输出 $0$。

# AC CODE
```cpp
#include <iostream>
using namespace std;
void solve(){
	long long n,maxl=0,minr=1e9;
	cin >>n;
	for(int i=1;i<=n;i++){
		long long l,r;
		cin >>l >>r;
		maxl=max(maxl,l);//最大左端点
		minr=min(minr,r);//最大右端点
	}
	cout <<max((long long)0,maxl-minr) <<endl;
    //如果右端点比左端点小，说明几条线段已经有公共点，输出0。
}
int main(){
	int t;
	cin >>t;
	while(t--){
		solve();
	}
	return 0;
}

```


---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
给出 $n$ 条线段（含端点），请你给出一条最短的线段，使其与所有线段都有交，输出最短的长度（$r-l$）.  
$n\le10^5$
## $\text{Solution}$
要求均有交的充要条件是：$l\le\min r_i\land r\ge\max l_i$.  
所以答案就是 $\max(0,\max l_i-\min r_i)$.
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=5e5+100;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n,m,k;

signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  int T=read();
  while(T--){
    int l=2e9,r=-2e9;
    n=read();
    for(int i=1;i<=n;i++){
      int x=read(),y=read();
      l=min(l,y);r=max(r,x);
    }
    r=max(l,r);
    printf("%d\n",r-l);
  }
  return 0;
}
/*

*/

```


---

## 作者：SpeedStar (赞：0)

#### 算法分析

只需找到所有区间的右端点的最小值$r_{min}$和所有区间的左端点的最大值$l_{max}$即可，然后待求区间的最小长度为 $max(0, l_{max} - r_{min})$。


#### C++ 代码

```cpp
#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::max;
using std::min;

int main() {
	int t;
	cin >> t;
	
	while (t--) {
		int n;
		cin >> n;
		int l, r;
		int lmax =0, rmin = (int)1e9;
		for (int i = 0; i < n; ++i) {
			cin >> l >> r;
			lmax = max(lmax, l);
			rmin = min(rmin, r);
		} 
		cout << max(0, lmax - rmin) << '\n';
	}
	
	return 0;
}
```


---

## 作者：rainygame (赞：0)

这道题还算简单的。

想要找一个 $[a;b]$ 使得其和所有段相交，且 $b-a$ 最小。

有一种贪心的思路，就是找所有 $l$ 的最大值和 $r$ 的最小值。

因为这样可以保证一定和任何一个段都有相连。

注意可能会出现最小值减去最大值为负数的情况，这个时候就要算成 $0$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define for1(i, s, t) for (int i(s); i<=t; ++i)
#define for2(i, t, s) for (int i(t); i>=s; --i)
#define for3(i, vec) for (auto i: vec)
#define INF 0x3f3f3f3f
#define opb pop_back
#define pb push_back
#define pf push_front
#define opf pop_front
#define fi first
#define se second
#define gc() getchar()
#define pc(x) putchar(x)
#define sp pc(' ')
#define el pc('\n')
#define Yes printf("YES");
#define No printf("NO");
#define err assert(0);
//const int MAXN(1e5);
//const ll MOD(1e9+7);

ll read(){
	ll x(0), f(1);
	char ch;
	while ((ch = gc()) < 48) f = ch == '-' ? -1 : 1;
	do{
		x = (x << 1) + (x << 3) + (ch ^ 48);
	}while ((ch = gc()) > 47);
	return x * f;
}

void uwrite(ll x){
	ll tmp(x/10);
	if (tmp) uwrite(tmp);
	pc(x-(tmp<<1)-(tmp<<3)^48);
}

void write(ll x){
	if (x < 0){
		pc('-');
		x = -x;
	}
	uwrite(x);
}

int n, l, r, maxn, minn;

void solve(){
	n = read();
	maxn = 0;
	minn = INF;
	while (n--){
		l = read();
		r = read();
		maxn = max(maxn, l);
		minn = min(minn, r);
	}
	write(max(maxn-minn, 0));
}

int main(){
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);

	int t(1);
	t = read();
	while (t--){
		solve();
		putchar('\n');
	}

	return 0;
}
```


---

