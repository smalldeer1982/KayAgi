# Find the Car

## 题目描述

Timur is in a car traveling on the number line from point $ 0 $ to point $ n $ . The car starts moving from point $ 0 $ at minute $ 0 $ .

There are $ k+1 $ signs on the line at points $ 0, a_1, a_2, \dots, a_k $ , and Timur knows that the car will arrive there at minutes $ 0, b_1, b_2, \dots, b_k $ , respectively. The sequences $ a $ and $ b $ are strictly increasing with $ a_k = n $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1971E/d53ef18fd3d7973a4983a5295563984c39a519c6.png)Between any two adjacent signs, the car travels with a constant speed. Timur has $ q $ queries: each query will be an integer $ d $ , and Timur wants you to output how many minutes it takes the car to reach point $ d $ , rounded down to the nearest integer.

## 说明/提示

For the first test case, the car goes from point $ 0 $ to point $ 10 $ in $ 10 $ minutes, so the speed is $ 1 $ unit per minute and:

- At point $ 0 $ , the time will be $ 0 $ minutes.
- At point $ 6 $ , the time will be $ 6 $ minutes.
- At point $ 7 $ , the time will be $ 7 $ minutes.

For the second test case, between points $ 0 $ and $ 4 $ , the car travels at a speed of $ 1 $ unit per minute and between $ 4 $ and $ 10 $ with a speed of $ 2 $ units per minute and:

- At point $ 6 $ , the time will be $ 5 $ minutes.
- At point $ 4 $ , the time will be $ 4 $ minutes.
- At point $ 2 $ , the time will be $ 2 $ minutes.
- At point $ 7 $ , the time will be $ 5.5 $ minutes, so the answer is $ 5 $ .

For the fourth test case, the car travels with $ 1.2 $ units per minute, so the answers to the queries are:

- At point $ 2 $ , the time will be $ 1.66\dots $ minutes, so the answer is $ 1 $ .
- At point $ 6 $ , the time will be $ 5 $ minutes.
- At point $ 5 $ , the time will be $ 4.16\dots $ minutes, so the answer is $ 4 $ .

## 样例 #1

### 输入

```
4
10 1 3
10
10
0
6
7
10 2 4
4 10
4 7
6
4
2
7
1000000000 1 1
1000000000
1000000000
99999999
6 1 3
6
5
2
6
5```

### 输出

```
0 6 7 
5 4 2 5 
99999999 
1 5 4```

# 题解

## 作者：Harrylzh (赞：6)

考虑把答案分成两个部分求，整的（$b_i$ 可以找到的），多的（需要通过求速度来找答案）。通过 `lower_bound()` 来找到 $d$ 所处的段，就可以求出上面两个值，找到答案。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t;
long long a[1000000+5],b[1000000+5];
long long n,k,q;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>k>>q;
		for(long long i=1;i<=k;i++)cin>>a[i];
		for(long long i=1;i<=k;i++)cin>>b[i];
		while(q--)
		{
			long long d;
			cin>>d;
			long long ress=lower_bound(a+1,a+k+1,d)-a;
			cout<<b[ress-1]+(d-a[ress-1])*(b[ress]-b[ress-1])/(a[ress]-a[ress-1])<<' ';
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：JXR_Kalcium (赞：3)

## 题目大意

给出一个长度为 $n$ 的线段，有一动点 $P$ 在这条线段上运动，这条线段上有 $k$ 个标记 $a_i$，同时每个 $a_i$ 都有对应的 $b_i$，表示点 $P$ 运动到 $i$ 时用的时间。$P$ 在相邻的两个标记中为匀速运动，求 $P$ 运动到 $d$ 所耗费的时间，结果向下取整。

## 解题思路

### 暴力

我们可以枚举所有的标记，找到 $d$ 在两个标记 $a_t$ 和 $a_{t+1}$ 之间，因为 $P$ 已经运动了 $a_t$ 的长度，所以时间就是 $b_t$。剩下的一段，因为时间等于路程除以速度，当前的路程还剩 $d-a_t$，速度又等于所处这一段的路程除以时间，所以速度为 $\displaystyle \frac{a_{t+1}-a_t}{b_{t+1}-b_t}$。需要注意的是，去括号后是先除再乘，因为除法会自动向下取整，所以要改成先乘再除，即最后的总时间为 $b_t+(b_{t+1}-b_t)\cdot \displaystyle \frac{d-a_t}{a_{t+1}-a_t}$，时间复杂度为 $O(qk)$。

### 二分

因为 $1\le k,q\le 10^5$，所以需要更好的解决方法。我们发现，最耗时的地方就是枚举 $d$ 的位置。有没有更快寻找的办法呢？

**二分！！！**

我们可以通过二分来用 $\log$ 级别的时间查找 $d$ 的位置，每次二分判断 $a_{mid}$ 是否小于 $d$，如果是的话区间就往右移动，否则就往左，最后的 $l$ 即为上文中的 $t+1$，时间复杂度就压到了 $O(q\log k)$。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

long long t,n,k,q,a[100001],b[100001],x,l,r,mid;

int main()
{
	scanf("%lld",&t);
	
	while(t--)
	{
		scanf("%lld%lld%lld",&n,&k,&q);
		for(int i=1; i<=k; ++i) scanf("%lld",&a[i]);
		for(int i=1; i<=k; ++i) scanf("%lld",&b[i]);
		
		for(int i=1; i<=q; ++i)
		{
			scanf("%lld",&x);
			l=1; r=k;
			
			while(l<=r)
			{
				mid=(l+r)>>1;
				if(a[mid]<x) l=mid+1;
				else r=mid-1;
			}
			
			printf("%lld ",b[l-1]+(b[l]-b[l-1])*(x-a[l-1])/(a[l]-a[l-1]));
		}
		
		printf("\n");
	}
	
	return 0;
}
```

---

## 作者：mc_xiexie (赞：2)

# CF1971E Find the Car
## 题意
给你到达一个标志的用时，让你求出要多少分钟才能到 $c$ 处。

Tip：
1. 任何两个相邻的标志，汽车以恒定的速度行驶。
2. 向下取整。
## 思路
### 路程问题
标志之间的速度 $r$ 和 $r+1$ 是 $\frac{a_{r+1}-a_r \cdot di}{b_{r+1}-b_r \cdot min}$（$\frac{di}{min}$ 为速度公式）。

总共走过了一段距离 $c$，（$c−a_r$）是自最后一个标志以来走过了一段距离，自最后一个标志到目前的位置的分钟数为
 $ \frac{a_{r+1}-a_r}{b_{r+1}-b_r} \frac{di}{min} \times (c-a_r di) = (c-a_r) \times \frac{a_{r+1}-a_r}{b_{r+1}-b_r} min $。

$di$：路程（点）。

$min$：时间（分钟）。

由此写出代码。
## 完整代码

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
    int t;
    cin >> t;
    while (t--) {
        int n, k, q;
        cin >> n >> k >> q;
        vector<ll> a(k+5), b(k+5);
        for(int i = 1; i <= k; i++)
        {
            cin >> a[i];
        }
        for(int i = 1; i <= k; i++)
        {
            cin >> b[i];
        }
        for(int i = 0; i < q; i++)
        {
            ll c;
            cin >> c;
            int l = 0, r = k;
            while(l <= r)
            {
                int mid = l + (r - l) / 2;
                if(a[mid] > c)
                {
                    r = mid-1;
                }
                else
                {
                    l = mid+1;
                }
            }
            if(a[r] == c)
            {
                cout << b[r] << " ";
                continue;
            }
            ll ans = b[r] + (c-a[r])*(b[r+1]-b[r])/(a[r+1]-a[r]);
            cout << ans << " ";
        }
        cout << endl;
    }
}
```

---

## 作者：__XU__ (赞：1)

## CF1971E Find the Car

### 题目大意：

在线段上寻查动点到达定点所需的时间。

### 做法：

考虑使用 二分查找 解决。

对于每次询问 $d$ 找到第一个大于等于它的元素的位置，可求出它所在的路段。最后将 $a,b$ 数组代入速度公式即可求出答案。

## AC code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
void solve() {
    int n,q,k,c;
    cin>>n>>k>>q;
    vector<int> a(k+1),b(k+1);
    a[0]=0;b[0]=0;
    for (int i=1;i<=k;i++){
        cin>>a[i];
    }
    for (int i=1;i<=k;i++){
        cin>>b[i];
    }
    while (q--){
        int cnt=0;
        cin>>c;
        cnt=upper_bound(a.begin(),a.end(),c)-a.begin()-1;
        cout<<b[cnt]+(c-a[cnt])*(b[cnt+1]-b[cnt])/(a[cnt+1]-a[cnt])<<' ';
    }
    cout<<'\n';
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);   
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
```

谢谢观看。

---

## 作者：nsty_iridescent (赞：1)

### 题目大意

在一条线段上有一些动点，我们需要根据动点的位置和速度，计算它们在指定时间点到达指定位置所需的时间。

### 思路

通过二分查找来解决。

首先，我们可以考虑从如何有效地找到车辆所在的路段入手。因为路段数组是按照起点进行排序的，所以我们可以利用二分查找解决问题。具体步骤如下：

* 对路段数组 $a$ 进行排序，确保路段按照起点的顺序排列。

* 对于每个查询的指定点 $d$，使用二分查找找到第一个大于等于 $d$ 的元素的位置，即找到指定点所在的路段。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int maxn=100005;
int t,n,k,q,d;
int a[maxn],b[maxn];
signed main(){
	cin>>t;
    while(t--){
        cin>>n>>k>>q;
        for(int i=1;i<=k;i++)cin>>a[i];// 每个点的位置 
        for(int i=1;i<=k;i++)cin>>b[i];// 每个点的速度 
        sort(a+1,a+1+k);
        for(int i=1;i<=q;i++){
            cin>>d;
            int now=lower_bound(a+1,a+k+1,d)-a;// 在有序的动点位置数组中找到第一个大于等于查询位置的位置
            if(now==1)cout<<b[1]*d/a[1]<<endl;// 如果查询位置小于等于第一个动点位置，直接计算时间并输出
            else{
                int ans=b[now-1]+(int)(d-a[now-1])*(b[now]-b[now-1])/(a[now]-a[now-1]);// 两个动点之间的线性插值来计算时间
                cout<<ans<<endl;
            }
        }
    }

    return 0;
}

```

---

## 作者：_ayaka_ (赞：1)

### 思路
二分的板子。一段区间内的速度是均匀的，只需要求出 $d$ 所在的区间并用到此区间所用的时间加上从此区间的起点到 $d$ 所用的时间就可以了。

对于这种查找一个数在不下降序列里位于哪两个数之间的问题，我们可以使用 `lower_bound()` 快速求解，不用为了二分而苦恼，是非常好用的函数。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t, n, k, q, a[100005], b[100005], d, len;
signed main() {
	cin >> t;
	while (t--) {
		cin >> n >> k >> q;
		for (int i = 1; i <= k; i++) cin >> a[i];
		for (int i = 1; i <= k; i++) cin >> b[i];
		for (int i = 1; i <= q; i++) {
			cin >> d;
			len = lower_bound(a + 1, a + k + 1, d) - a;//查找
			d = (d - a[len - 1]) * (b[len] - b[len - 1]) * 1.0 / (a[len] - a[len - 1]);//计算
			cout << d + b[len - 1] << " ";
		}
		cout << "\n";
	}
	return 0;
}
```

---

## 作者：Cute__yhb (赞：1)

## 思路

二分，找到第一个大于等于当前 $d$ 的位置，利用 $a$ 和 $b$ 数组求出当前速度，然后求解。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define re register
#define ri register int
#define rll register long long
#define ld long double
#define endl '\n'
#define fi first
#define se second
#define pii pair<int,int>
#define p_q priority_queue
#define iter iterator
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define nep(i,a,b) for(int i=(a);i>=(b);i--)
#define popcount __builtin_popcount
#define pb push_back
#define mem(a,x) memset((a),x,sizeof(a))
#define eps 1e-8
#define oper operator
#define mk make_pair
ll a[100005],b[100005],k,n,q;
void solve(){
	cin>>n>>k>>q;
	for(int i=1;i<=k;i++){
		cin>>a[i];
	}
	for(int i=1;i<=k;i++) cin>>b[i];
	while(q--){
		ll d;
		cin>>d;
		int l=1,r=k,ans=1;
		while(l<=r){//二分
			int mid=(l+r)/2;
			if(a[mid]>=d){
				ans=mid;
				r=mid-1;
			}else l=mid+1;
		}
		ll sum=b[ans-1],m=b[ans]-b[ans-1];//m是时间
		sum+=(d-a[ans-1])*m/(a[ans]-a[ans-1]);//(a[ans]-a[ans-1])/m是速度
		cout<<sum<<' ';
	}
	puts("");
}
int main(){
	int t;
	cin>>t;
	while(t--) solve();
    return 0;
}
```

---

## 作者：tder (赞：1)

[CF1971 场记](https://tder6.github.io/articles/CF1971A%20to%20CF1971G%20%E5%9C%BA%E8%AE%B0.html) 食用效果更佳。

---

**【题意】**

数轴上有一点，在 $b_i$ 时刻到达 $a_i$ 处，设其在两个 $a_i$ 之间匀速通过。多次询问，查询何时到达 $d$ 处，四舍五入。多测。

**【思路】**

考虑先二分出查询的 $d$ 在哪个区间 $[a_i,a_{i+1}]$ 中。最终答案即为：

$$
\begin{aligned}
\text{ans}&=b_i+t \\
&=b_i+\dfrac sv \\
&=b_i+(d-a_i)\div\dfrac{a_{i+1}-a_i}{b_{i+1}-b_i} \\
&=b_i+(d-a_i)\cdot\dfrac{b_{i+1}-b_i}{a_{i+1}-a_i}
\end{aligned}
$$

注意多测清空，否则你会 WA on #2。

单组数据复杂度 $O(n+q\log n)$。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 1e5 + 5;
int n, k, q, a[N], b[N];
void solve() {
	cin>>n>>k>>q;
	for(int i = 1; i <= k; i++) cin>>a[i];
	for(int i = 1; i <= k; i++) cin>>b[i];
	a[k + 1] = b[k + 1] = 0;
	while(q--) {
		int d; cin>>d;
		int l = 0, r = k;
		while(l <= r) {
			int m = (l + r) / 2;
			if(a[m] > d) r = m - 1;
            else l = m + 1;
		}
		// if(a[r + 1] == a[r]) cout<<"qwq "<<r<<endl, exit(-1);
		cout<<b[r] + (d - a[r]) * (b[r + 1] - b[r]) / (a[r + 1] - a[r])<<" ";
	}
	cout<<endl;
}
int t;
signed main() {
	cin>>t;
	while(t--) solve();
}
```

---

## 作者：Just_A_Sentence (赞：1)

# 题意翻译

一条笔直的公路上有 $k$ 个标志，已知这条公路的长度 $n$，第 $i$ 个标志位于 $a_{i}$ 点，一辆大巴车从 $0$ 点出发，并在 $b_{i}$ 分钟经过第 $i$ 个标志。现给出 $q$ 个询问，求大巴车经过 $d$ 点的时间（向下取整）。

输入有 $t$ 组，对于每组数据的 $q$ 个询问，输出一行，用空格间隔。

对于 $100\%$ 的数据，$1\le t\le 10^4$，$k\le n\le 10^9$，$1\le k,q\le 10^5$，$1\le a_1<a_2<\ldots<a_k=n$，$1\le b_1<b_2<\ldots<b_k\le 10^9$。

# 分析

首先我们可以发现，$\mathcal O(kq)$ 的暴力是过不了的，那么我们就需要优化。怎么优化呢？**二分**

注意到 $a,b$ 数组都具有单调递增性，所以我们很容易就想到了二分。

我们可以通过二分查找**第一个小于等于询问点的标志**，再计算从这个标志点到询问点的时间。

时间复杂度 $\mathcal O(q\log k)$，空间复杂度 $\mathcal O(k)$，可以完美 AC 此题。

代码如下：

~~~cpp
#include<bits/stdc++.h>
using namespace std;
long long a[100005],b[100005];//如果输出是和我一样打法的一定要开long long！！！赛时就是这里WA了两发！！！
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n,k,q;
		scanf("%d%d%d",&n,&k,&q);
		for(int i=1;i<=k;i++){
			scanf("%lld",&a[i+1]);
		}
		for(int i=1;i<=k;i++){
			scanf("%lld",&b[i+1]);
		}
		a[0]=b[0]=-1e9;
		a[1]=b[1]=0;
		int l=1,r=k+1;
		for(int i=1;i<=q;i++){
			l=1,r=k+1;
			long long x;
			scanf("%lld",&x);
			if(x<=a[2]){
				printf("%lld ",x*b[2]/a[2]);
				continue;
			}
			while(l<r){
				int mid=(l+r+1)>>1;//这里要右偏。
				if(x<a[mid-1]) r=mid-1;
				else if(x>a[mid]) l=mid;
				else{
					l=mid;
					r=mid;
				}
			}
			printf("%lld ",b[r-1]+(b[r]-b[r-1])*(x-a[r-1])/(a[r]-a[r-1]));
		}
		printf("\n");
	}
	return 0;
}
~~~

---

## 作者：a_123_a (赞：0)

### 思路
分析题目·发现是二分，因为一段区间内的速度是均匀的 ~~还好均匀~~，只需要求出 $ d $ 所在的区间到的时间再加上从区间的起点到 $ d $ 的时间就可以了。

对于这种查找一个数在单调序列里位于哪两个数之间的问题，我们可以使用 ```lower_bound()``` ~~方便，可以不用手写二分~~ 快速求解。

```c
#include<bits/stdc++.h>
using namespace std;
#define N 100005
#define intl long long
#define For(i,a,b) for(intl i=a;i<=b;i++)
#define deo(i,a,b) for(intl i=a;i>=b;i--)
intl n,k,q,a[N],b[N],d;
int main() {
	int T;scanf("%d",&T);
	while (T--) {
		scanf("%lld %lld %lld ",&n,&k,&q); 
		For(i,1,k) scanf("%lld",a + i);
		For(i,1,k) scanf("%lld",b + i);
		For(i,1,q) {
			scanf("%lld",&d);
			intl len=lower_bound(a+1,a+k+1,d)-a;
			intl t=(d-a[len-1])*(b[len]-b[len-1])*1.0/(a[len]-a[len-1]);
			printf("%lld ",t+b[len-1]);
		}
		printf("\n");
	}
	return 0;
}
```

---

