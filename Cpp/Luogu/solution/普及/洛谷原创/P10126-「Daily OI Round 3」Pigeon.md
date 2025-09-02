# 「Daily OI Round 3」Pigeon

## 题目背景

> 最近，忙吗，也不说打个电话。哦，是吗，嘿嘿原来没给过你号码。但这，不是，你不找我的理由，下次罚你陪我等到太阳出头。——recollect_i 的博客

## 题目描述

recollect_i 给了你长度为 $n$ 的序列 $x$，你需要求出一个实数 $y$ 使得对于所有 $1\leq i<j\leq n$，$\vert x_j-y\vert>\vert x_i-y\vert$，或报告无解。

## 说明/提示

#### 【提示】

输出格式中 $>10^{-6}$ 只是为了避免精度问题，您可以当成要求 $\vert x_j-y\vert>\vert x_i-y\vert$。

可以证明，如果有解，则一定存在 $y$ 满足 $-2\times 10^{9}\leq y\leq2\times 10^{9}$ 且对于所有 $1\leq i<j\leq n$，$\vert x_j-y\vert-\vert x_i-y\vert>0.2$，且小数点后位数不超过 $3$。

#### 【数据范围】

对于全部数据保证：$5\leq n\leq10^5$，$-10^9\leq x_i\leq10^9$。

## 样例 #1

### 输入

```
5
1 2 3 4 5```

### 输出

```
lovely
-114514```

## 样例 #2

### 输入

```
5
3 2 1 6 7```

### 输出

```
lovely
3.1416```

## 样例 #3

### 输入

```
5
3 2 1 4 5```

### 输出

```
pigeon```

# 题解

## 作者：I_will_AKIOI (赞：7)

题目给的是一个长度为 $n$ 的序列，太麻烦了，我们把数据规模缩小成 $2$ 个数来思考。

假设这两个数是 $2$ 和 $3$，得到方程 $|3-y|>|2-y|$。

若 $y\le2$：

$$3-y>2-y$$

$$3>2$$

无解。

若 $2<y\le3$：

$$3-y>y-2$$

$$5>2y$$

$$y<2.5$$

若 $y>3$：

$$y-3>y-2$$

$$0>1$$

无解。

所以我们可以求出 $y$ 的范围是 $(-\infty,2.5)$。

也可以根据绝对值的几何意义，得出 $y$ 一定在他们中点的左侧。

同样的，如果两个数反过来，那么 $y$ 一定在中点右侧。

于是，我们可以一直枚举相邻两个数，求出 $y$ 的范围，不断缩小。枚举完成后，看看左端点是否**小于**右端点，否则无解。否则输出这个区间的中点。

注意开始两个端点要赋成最值，并且输出时注意保留 $10$ 位小数。我赛时被卡了好几发。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[100005];
double l=-1e9,r=1e9;
signed main()
{
  ios::sync_with_stdio(0);
  cin>>n;
  for(int i=1;i<=n;i++) cin>>a[i];
  for(int i=1;i<n;i++)
  {
  	if(a[i]<=a[i+1]) r=min(r,0.5*(a[i]+a[i+1]));
  	if(a[i]>=a[i+1]) l=max(l,0.5*(a[i]+a[i+1]));
    //不写if-else的原因是防止两数相等
  }
  if(l>=r) cout<<"pigeon";
  else printf("lovely\n%.10f",0.5*(l+r));
  return 0;
}
```

---

## 作者：Angraecum (赞：5)

主要是讲思考过程，这个 trick 感觉挺好想的。

先从局部入手，我们看某一对 $i,j$ 在什么时候满足题目条件。以第二个样例为例：对于 $3,2$，容易得出当 $y>\dfrac{(3+2)}{2}$，也就是 $y>2.5$ 时它们就满足条件。继续往后推，我们发现对于 $3,6$ 这组 $y$ 应该是 $y< 4.5$ 才满足条件。

由此我们发现，这个问题本质上是一个**求解不等式组**。那么容易得到一个暴力做法：枚举所有 $(i,j)$，如果 $a_j>a_i$ 那么记录一个最小值 $minn$ 表示值最小的小于限制；如果 $a_j<a_i$ 记录最大值 $maxn$ 表示值最大的大于限制。如果 $minn>maxn$ 那么就有解，解就直接输出一个 $maxn+0.000001$ 就行了，题目里有精度保证。这个做法时间复杂度 $O(n^2)$。

考虑优化。以优化找最小值为例，我们发现如果存在 $i<j<k,a_i<a_k,a_j<a_i$ 的话，那么我们珂以直接把 $i$ 丢掉从 $j$ 开始枚举。不管后面出现什么数，只要 $a_j<a_i$ 那么和 $j$ 形成的数对的限制值就一定是更小的，对于 $j$ 以前的数就不用管了。

那么我们考虑维护一个单调指针 $pos$，$pos$ 初始指向 $1$，然后从 $2$ 开始枚举。如果 $a_i>a_{pos}$ 那么就更新最小值，否则将 $pos$ 指向 $i$，这样就一遍 $O(n)$ 遍历就求出了最小值。求最大值也一样，改成 $a_i<a_{pos}$ 更新最大值就行了。

还有我不知道有没有存在相同的数的情况，还是用了一个 ``map`` 判了一下，有相同的数就直接无解了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=2*114514,M=1919810,inf=2e9;
ll n;
double a[N],maxn=-inf,minn=inf; //赋成±2e9，要不然珂能不满足题目条件
map <double,bool> fl;
int main(){
	//ios::sync_with_stdio(0);
	//cin.tie(0); cout.tie(0);别关同步流
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		if(fl[a[i]]){
			cout<<"pigeon";
			return 0;
		}
		fl[a[i]]=1;
	}
	ll pos=1;
	for(int i=2;i<=n;++i){
		if(a[i]>a[pos]) minn=min(minn,(a[i]+a[pos])*1.0/2);
		if(a[i]<a[pos]) pos=i;
	}
	pos=1;
	for(int i=2;i<=n;++i){
		if(a[i]<a[pos]) maxn=max(maxn,(a[i]+a[pos])*1.0/2);
		if(a[i]>a[pos]) pos=i;
	}
	if(minn>maxn) printf("lovely\n%0.6lf",(double)(maxn)+0.000001);
	else cout<<"pigeon";
	return 0;
}
```

这题应该黄到绿之间。

---

## 作者：hh20080501hh (赞：1)

# 题目
[题面戳我哦~](https://www.luogu.com.cn/problem/P10126)

题意概括：给定一个序列，我们需要找出一个值，使序列每一项到我们找的这个值的距离（就是两个数的绝对值，我们可以想象为坐标轴上的距离）都比它前一项到我们找的这个值的距离大。
# 分析
看到题目的第一眼我想到了二分，但是答案好像不具备单调性，无法判断到底是往左边继续二分还是往右边继续二分。

虽然说二分不可取~~反正我没想到二分怎么做~~，但是这启示了我们一点：**我们可以通过缩小边界来确定我们要找的值**。

考虑如何缩小边界，我们不妨进行分类讨论。在此之前，先将一些概念定义一下，以方便后续讨论。

$res$ 为我们需要找的值，$a_i$ 为当前项，$a_{i-1}$ 为当前项的前一项，$l$ 为我们所确定的左边界，$r$ 为我们所确定的右边界。对于 $i=1$ 的这种边界情况我们暂时不考虑，这是写代码时才需要注意的。
1. 当 $a_i>a_{i-1}$ 时，画个数轴我们可以发现，$res$ 一定会在这两项的中点的左侧，即 $res$ 一定小于 $\frac{a_1+a_{i-1}}{2}$，那么我们的右边界就可以进行缩小了。

1. 当 $a_i<a_{i-1}$ 时，同样的画个数轴，我们可以发现，$res$ 一定会在这两项的中点的右侧，即 $res$ 一定大于 $\frac{a_i+a_{i-1}}{2}$，那么我们的左边界就可以进行缩小了。

好了，我们已经知道有解该怎么解决了，那么无解怎么办呢？

无解同样也很简单。
1. 如果 $l>r$ 就说明取不到任何值了，可以退出去了。
1. 或者 $r-l\le10^{-6}$ 这个时候区间已经很小很小了，而题目已经告诉我们我们要找的 $res$ 小数点后面只有 $3$ 位，所以这个时候也是不满足了。
1. 当然我们不能漏掉一种很重要的情况，那就是当 $a_i$ 与 $a_{i-1}$ 相等时，这个时候无论我们怎么取值，这两项到取值的距离都相等，这也是一种无解情况。

无解和有解我们都知道怎么做了，我们开始写代码。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+10;
const double eps = 1e-6;	//精度

int n;
int a[N];
double l = -2e9 , r = 2e9;	//l和r都是小数，用double存

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> n;
	for (int i=1 ; i<=n ; i++)
	{
		cin >> a[i];
	}
	
	for (int i=2 ; i<=n ; i++)
	{
		if (l>=r || r-l<=eps || a[i]==a[i-1])	//3种无解情况的判断
		{
			cout << "pigeon" << endl;
			return 0;
		}
		if (a[i-1]>a[i])	//有解时缩小左边界
		{
			double mid = (double)(a[i-1]+a[i])/2;
			l = max(mid , l);
		}
		if (a[i-1]<a[i])	//有解时缩小右边界
		{
			double mid = (double)(a[i-1]+a[i])/2;
			r = min(mid , r);
		}
	}
	
	if (l>=r || r-l<eps)	//由于我们是在循环开始的时候判断的，
    					  //所以我们可能会漏掉最后一项和倒数第二项让边界不满足的情况
	{
		cout << "pigeon" << endl;
		return 0;
	}
	cout << "lovely\n";		//别忘记输出这个了
	cout << fixed << setprecision(7) << l+eps << endl; 	//题目说不能保留超过10位小数，那我们保留7位
	return 0;
}
```

---

## 作者：Coffins (赞：1)

首先题目中的限制条件等价于：
$$\forall i\in\{1,2,\cdots,n-1\},|x_i-y|\lt|x_{i+1}-y|$$

然后这样就有共 $n-1$ 对约束条件，每对约束条件形如 $|a-y|\lt|b-y|$。

考虑把他解出来，由于过于简单，这里略过过程，直接给出结论：

当 $a\lt b$ 时，得出 $y\lt\dfrac{a+b}{2}$；

当 $a\gt b$ 时，得出 $y\gt\dfrac{a+b}{2}$；

当 $a=b$ 时，显然无解。

然后就可以维护 $y$ 的一个范围 $(l,r)$ 了，最终若是 $r\gt l$，那么显然 $\dfrac{l+r}{2}$ 为一个解，否则无解。

代码过于简单不贴了。

---

## 作者：Cure_Wing (赞：1)

[P10126 「Daily OI Round 3」Pigeon](https://www.luogu.com.cn/problem/P10126)

### 思路

两个绝对值，我们把它想成数轴上点的距离。

而中间有个大于号，我们把它分成两类。

第一种 $a_i<a_j$，此时可以看出 $p$ 要离 $a_j$ 远一点，所以 $p<\frac{a_i+a_j}{2}$。

第二种 $a_i>a_j$，此时可以看出 $p$ 要离 $a_i$ 远一点，所以 $p>\frac{a_i+a_j}{2}$。

答案也就是这些范围的交集。

我们当然可以枚举所有的 $i,j$ 取计算范围，但是 $n\le10^5$ 却不由得让我停住了脚步。考虑我们求取值范围是一个交集，于是乎我们能不能直接计算出极端情况的值呢？对于第一种情况，假设我们定下来 $a_j$，那么我们选取最小的 $a_i$，这样会使 $p$ 的上限尽可能小；对于第二种情况，假设我们定下来 $a_j$，那么我们选取最大的 $a_i$，这样会使 $p$ 的下限尽可能大。至于寻找最大和最小的 $a_i$，我们直接从前往后扫，边扫边记录最大值和最小值边更新答案就可以了。

计算完 $p$ 的范围，答案也就呼之欲出了。

时间复杂度 $O(n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<iomanip>
using std::cin;using std::cout;
constexpr int N=100005,inf=2e9+1;
int n,x[N],minn,maxn;
double l,r;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
    cin>>n;minn=r=inf;maxn=l=-inf;
    for(int i=1;i<=n;++i){
        cin>>x[i];
        if(maxn>=x[i]) l=std::max(l,(maxn+x[i])/2.0);
        if(minn<=x[i]) r=std::min(r,(minn+x[i])/2.0);
        maxn=std::max(maxn,x[i]);
        minn=std::min(minn,x[i]);
    }
    if(l<r) cout<<"lovely\n"<<std::fixed<<std::setprecision(3)<<(l+r)/2.0;
    else cout<<"pigeon";
    return 0;
}
```

---

## 作者：Link_Cut_Y (赞：1)

给你长度为 $n$ 的序列 $x$，你需要求出一个实数 $y$ 使得对于所有 $1\leq i<j\leq n$，$\vert x_j-y\vert>\vert x_i-y\vert$，或报告无解。

-------------

首先将不等式两边平方去掉绝对值，得到：

$$(x_j - y) ^ 2 > (x_i - y) ^ 2$$

$$x_j ^ 2 - 2 yx_j +y ^ 2 > x_i ^ 2 - 2yx_i +y ^ 2$$

$$x_j ^ 2 - x_i ^ 2 > 2y(x_j - x_i)$$

$$(x_j + x_i)(x_j - x_i) > 2y(x_j - x_i)$$

发现不等号两边都有 $(x_j - x_i)$ 这一项。我们想要约掉它，就需要讨论 $(x_j - x_i)$ 的正负。

 - $x_j - x_i > 0$，原不等式转化为 $x_j + x_i > 2y$，即 $y < \dfrac{x_i + x_j}{2}$。
 
 - $x_j - x_i < 0$，原不等式转化为 $x_j + x_i < 2y$，即 $y > \dfrac{x_i + x_j}{2}$。
 
我们得到了一个关于 $y$ 的不等式。我们只需要将所有不等式解出来取交集就行了。

观察式子，我们发现，在 $x_j$ 不变时，当 $x_j > x_i$（也就是第一个不等式），$x_i$ 越小约束越紧。在第二个不等式中，同理，$x_i$ 越大约束越紧。

我们枚举 $j$，并且维护处前 $j - 1$ 个里面 $x$ 的最小值和最大值，就可以做到对 $y$ 最严格的约束。

时间复杂度 $O(n)$。

需要注意的是，如果数列中有相等的两个元素，可以直接输出无解。

```cpp
const int N = 100010;
int n; db a[N], b[N], u, l, mx, mn;
map<db, bool> bin;
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i ++ ) scanf("%lf", &a[i]);
	for (int i = 1; i <= n; i ++ ) {
		if (bin[a[i]]) return puts("pigeon"), 0;
		bin[a[i]] = 1;
	}
	mx = mn = a[1]; u = 2e9, l = -2e9;
	for (int i = 1; i <= n; i ++ ) {
		if (mn < a[i]) u = min(u, (mn + a[i]) / 2.0);
		if (mx > a[i]) l = max(l, (mx + a[i]) / 2.0);
		mx = max(mx, a[i]), mn = min(mn, a[i]);
	}
	if (l >= u) return puts("pigeon"), 0;
	l = max(l, -2e9), u = min(u, 2e9);
	puts("lovely");
	printf("%.8lf\n", (db)(l + u) / 2.00);
	return 0;
}
```

---

## 作者：Wei_Han (赞：1)

观察题目中的条件，可以发现，最后的序列一定为一个单调递增序列。

那么我们就可以分情况讨论了，假设两数分别是 $a$，$b$：

当 $a>b$ 时，即两数递减时，我们需要改变大小关系，那么一定有 $y>\frac{a+b}{2}$。

同样当 $a<b$ 时，即两数递增时，我们不能改变大小关系，那么一定有 $y<\frac{a+b}{2}$。（此处算一算样例也能得出）

那么我们只需要找到 $y$ 能取到的上下界即可，也就是找到最小一组顺序对，最大的一组逆序对。遍历过程中记录最大最小值就可以了。

无解情况判断序列中存在相同数或者 $y$ 的上下界取不到值。

时间复杂度 $O(n)$。

## Code
```cpp
#include<bits/stdc++.h>
#define INF 2e9
#define pr printf("\n")
#define pp printf(" ")
#define pii pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(ll i = a ; i <= b ; i ++ )
#define Fo(a,i,b) for(ll i = a ; i >= b ;-- i  )
using namespace std;
typedef long long ll;
typedef double db;
const int N=5e5+5;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
ll n,a[N];
map<ll,ll> mp;
int main(){
	read(n);
	fo(1,i,n) read(a[i]);
	ll maxx=a[1],minx=a[1];
	db maxn=-INF,minn=INF;
	mp[a[1]]=1;
	ll flag2=0,flag1=0;
	fo(2,i,n){
		if(mp[a[i]]){printf("pigeon");return 0;}
		mp[a[i]]=1;
		if(a[i]<maxx) maxn=max(maxn,(maxx+a[i])/2.0);
		maxx=max(maxx,a[i]);
		if(a[i]>minx) minn=min(minn,(minx+a[i])/2.0);
		minx=min(minx,a[i]);
	}
	
	db l=maxn,r=minn;
	if(l<r&&(l+r)/2!=maxn&&(l+r)/2!=minn) printf("lovely\n%.5lf",(l+r)/2.0);
	else printf("pigeon");
	return 0;
}
``````

---

## 作者：NTT__int128 (赞：1)

## 题意简述
给定长度为 $n$ 的序列 $x$，求实数 $y$ 使得对于所有 $j>i$，有 $\vert x_j-y\vert>\vert x_i-y\vert$，或报告无解。
## 解题思路
我们发现，对于任意的 $a_i$，能限制 $y$ 的就只有在 $a_i$ 后面大于 $a_i$ 的最小值与小于 $a_i$ 的最大值。令 $maxn$ 为 $a_i$ 后面的最大值， $minn$ 为 $a_i$ 后面的最小值，在 $a_i$ 后面大于 $a_i$ 的最小值为 $maxx$，在 $a_i$ 后面小于 $a_i$ 的最大值为 $minx$，会有以下几种情况：

- 若 $a_i \le minn$，则可得此时 $y<(a_i+minn)\div 2$
- 若 $a_i \ge maxn$，则可得此时 $y>(a_i+maxn)\div 2$
- 其他情况，则可得此时 $y>(a_i+minx)\div 2$，$y<(a_i+maxx)\div 2$

记录每次的限制条件，若 $y$ 大于一个数，却又小于一个小于等于这个数的数，则无解，否则在此开区间内的任意实数都是解。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std ;
int n ;
double x[100005] , l = -1e9 , r = 1e9 ;
map <double , bool> mp ;
int main()
{
	cin >> n ;
	for(int i = 1 ; i <= n ; i++)
	{
		cin >> x[i] ;
		if(mp.count(x[i]))
		{
			cout << "pigeon" ;
			return 0 ;
		}
	}
	vector <double> v ;
	v.push_back(x[n]) ;
	for(int i = n - 1 ; i >= 1 ; i--)
	{
		if(x[i] < v[0])
		{
			r = min(r , (v[0] + x[i]) / 2) ;
		}
		else if(x[i] > v.back())
		{
			l = max(l , (v.back() + x[i]) / 2) ;
		}
		else
		{
			double minn = v[lower_bound(v.begin() , v.end() , x[i]) - 1 - v.begin()] , maxn = v[lower_bound(v.begin() , v.end() , x[i]) - v.begin()] ;
			l = max(l , (x[i] + minn) / 2) ;
			r = min(r , (x[i] + maxn) / 2) ;
		}
		v.insert(lower_bound(v.begin() , v.end() , x[i]) , x[i]) ;
	}
	if(l >= r)	cout << "pigeon" ;
	else
	{
		cout << "lovely\n" ;
		printf("%lf" , (l + r) / 2) ;
	}
	return 0 ;
}
```

---

## 作者：Shadow_T (赞：1)

### 题目大意

给定序列 $x$，你需要求出一个满足 $1 \leq i <j\leq n$ 的 $y$ 使得 $|x_j-y|>|x_i-y|$，或无解。

### 题目分析

最重要的就是这个绝对值。

1. 如果 $x_i\geq x_j$，则 $y$ 最小可以是 $\dfrac{x_j+x_i+eps}{2}$。最终取这些限制的最大值。

2. 如果 $x_i<x_j$，则 $y$ 最大可以是 $\dfrac{x_i+x_j-eps}{2}$。最终取这些限制的最小值。

因为要求是 $|x_j-y|>|x_i-y|$ 而不是 $|x_j-y| \geq |x_i-y|$，所以不能等于，要再多移动一点，要加或减 $eps$，这个 $eps$ 我选取了 $10^{-1}$。

但是这时候复杂度是 $O(n^2)$ 的，我们可以使用万能的 vector 来维护，实现每次可以插入且保持有序。

```cpp
v.insert(lower_bound(v.begin(),v.end(),x[i]),x[i]);
```

很明显在 $x_i$ 压缩两边限制时，可以每次找到小于 $x_i$ 且最大的值。如果找不到，就说明 $x_i$ 最小，没有逆序对，则用 $x_i$ 和 $v_0$ 进行操作 $2$；否则用 $x_i$ 和找到的值进行操作 $1$。

最后复杂度 $O(n \log n)$。比较慢，代码长，被标程薄纱，仅供参考。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
double x[maxn];
signed main()
{
	int n;
	cin>>n;
	double ma=2e9,mi=-2e9;
	int X;
	for(int i=1;i<=n;i++)
	cin>>X,x[i]=X;
	vector<double> v;
	v.push_back(x[n]);
	for(int i=n-1;i>=1;i--)
	{
		int it=lower_bound(v.begin(),v.end(),x[i])-v.begin()-1;
		if(v[it]==x[i])
		{
			cout<<"pigeon\n";
			return 0; 
		}
		else if(x[i]<v[0]) ma=min(ma,(x[i]+v[0]-0.1)/2);
		else mi=max(mi,(v[it]+x[i]+0.1)/2);
		v.insert(lower_bound(v.begin(),v.end(),x[i]),x[i]);
	}
	bool p=true;
	if(mi>ma) p=false;
	vector<double> x1;
	for(int i=1;i<=n;i++)
	x1.push_back(abs(x[i]-mi));
	sort(x1.begin(),x1.end());
	for(int i=1;i<=n;i++)
	if(abs(x[i]-mi)!=x1[i-1]) p=false;
	for(int i=1;i<n;i++) if(x1[i]==x1[i+1]) p=false;
	if(!p) cout<<"pigeon\n";
	else 
	{
		cout<<"lovely\n";
		printf("%.3lf\n",mi);
	}
}
```

---

## 作者：xvl_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10126)

一道红黑树题。

首先对于每个 $x_i<x_j$ 带回原不等式可以推出 $y < \frac{x_i+x_j}{2}$，同理，若 $x_i>x_j$ 则能推出 $y>\frac{x_i+x_j}{2}$。若存在 $x_i=x_j$，则 $y$ 无解。

我们可以维护两个变量 $l,r$，为答案 $y$ 的范围（即 $l<y<r$）。然后枚举所有的 $x_i$，每次寻找比它大的最小值更新 $r$，再寻找比它小的最大值更新 $l$。这个过程可以使用~~红黑树~~ `set` 中的 `lower_bound` 函数实现。

若最后 $l \ge r$，说明答案无解。否则任意输出一个 $(l,r)$ 范围内的实数即可（建议输出 $l$ 与 $r$ 的平均数，即 $\frac{l+r}{2}$）。

### Code

```cpp
#include <bits/stdc++.h>

const long long IMX = 1ll << 30;
const long long LMX = 1ll << 60;
const long long MOD = 998244353;

using ll = long long;
using i128 = __int128;
using ld = long double;
using f128 = __float128;

namespace xvl_ { 
	#define SP(n, x) std :: setprecision(n) << std :: fixed << x
	#define REP(i, l, r) for (auto i = (l); i <= (r); i++)
	#define PER(i, r, l) for (auto i = (r); i >= (l); i--)
	#define DEBUG(x) std :: cerr << #x << " = " << x << '\n'
	#define SZ(x) (x.size())
	#define fst first
	#define snd second
	template <typename T> T Max(T a, T b) { return a > b ? a : b; } template <typename T, typename... Args> T Max(T a, Args... args) { return a > Max(args...) ? a : Max(args...); }
	template <typename T> T Min(T a, T b) { return a < b ? a : b; } template <typename T, typename... Args> T Min(T a, Args... args) { return a < Min(args...) ? a : Min(args...); }
}
using namespace std;
using namespace xvl_;
ll n;
ll a[100005];
double l = -IMX, r = IMX;
set <ll> S;
map <ll, bool> mp;
int main() {
	// freopen("InName.in", "r", stdin);
	// freopen("OutName.out", "w", stdout);
	ios :: sync_with_stdio(0);
	cin.tie(nullptr);
	cin >> n;
	REP(i, 1, n) {
		cin >> a[i];
		if (mp[a[i]]) return cout << "pigeon", 0; // 判断是否有重复的整数
		mp[a[i]] = 1;
		S.insert(a[i]);
	}
	REP(i, 1, n - 1) {
	    S.erase(a[i]);
		auto it = S.lower_bound(a[i]);
		if (it != S.end()) r = Min(r, (a[i] + *it) * 1.0 / 2);
		if (it != S.begin()) l = Max(l, (a[i] + *(--it)) * 1.0 / 2);
	}
	if (l >= r) return cout << "pigeon", 0;
	cout << "lovely\n" << SP(5, (l + r) / 2);
	return 0;
}
```

---

## 作者：maomao233 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10126)

赛时想到正解，不会实现了。全方面变菜。  
赛事也想到使用 `set` 维护，但是自己被迭代器整死了也失败了。所以现在来实现一下。

首先由于题面中提到 $i<j$，所以我们从后往前维护。

其次，对于不等式 $|x_j-y|>|x_i-y|$：  
根据绝对值的几何意义，表示数轴上 $x_j$ 与 $y$ 的距离比 $x_i$ 与 $y$ 的距离更近。所以 $y$ 应该在 $[x_i,x_j]$ 范围内取值，且更靠近 $x_j$ 的那一侧。具体地：

$$\begin{cases}y<\dfrac{x_i+x_j}{2}&x_i>x_j\\y>\dfrac{x_i+x_j}{2}&x_i<x_j\end{cases}$$

于是我们可以维护两个端点变量 $l,r$，循环遍历每个 $a_i$。  
对于每个 $a_i$，求出比它大的最小值和比它小的最大值分别取平均数，然后再用如上的公式求平均数更新 $l,r$。  
其中，求 “比它大的最小值” 和 “比它小的最大值” 可以使用两个 `set` 和 `lower_bound` 实现。  
实现过程中，求 “比它大的最小值” 可以直接使用 `*s1.lower_bound(a[i])` 实现，而求 “比它小的最大值” 可以直接使用 `*s2.lower_bound(-a[i])` 实现。

同时，我们还需要注意：遍历过程中，若 $a_i$ 本身即为序列最大值或最小值，此时 `lower_bound` 函数会无效。  
所以我们需要特判。若出现此类情况，只更新另一个端点变量即可。

最后判断 $l,r$ 是否构成区间即可。输出反正 $l<ans<r$ 都行。

于是有代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
template<typename T>inline void rd(T &x){x=0;char c=getchar();bool f=0;while(!isdigit(c)){if(c=='-'){f=1;}c=getchar();}while(isdigit(c)){x=(x<<3)+(x<<1)+(c^'0');c=getchar();}if(f){x=~(x-1);}}
template<typename T,typename...Args>inline void rd(T &x,Args&...args){rd(x);rd(args...);}
inline void wt(int x){if(x<0){putchar('-'),x=-x;}if(x>9){wt(x/10);}putchar(x%10+'0');}
#define pc(x) putchar(x)
#define wtl(x) wt(x),pc('\n')
#define kg pc(' ')
#define hh pc('\n')
#define lb(x) x&-x
#define itn int
inline string its(int x){stringstream ss;string s;ss<<x;ss>>s;return s;}
inline int sti(string s){stringstream ss;int x;ss<<s;ss>>x;return x;}
inline string jia(string a1,string b1){int a[10010],b[10010],c[10010];int lena=a1.size(),lenb=b1.size();for(int i=0;i<lena;i++){a[i]=a1[lena-1-i]-'0';}for(int i=0;i<lenb;i++){b[i]=b1[lenb-1-i]-'0';}int lenc=max(lena,lenb),t=0;for(int i=0;i<lenc;i++){c[i]=a[i]+b[i]+t;if(c[i]>=10){t=1,c[i]%=10;}else{t=0;}}if(t==1){lenc++;c[lenc-1]=1;}string s;for(int i=lenc-1;i>=0;i--){s+=c[i]+'0';}return s;}
inline string jian(string a1,string b1){if(a1.size()<b1.size()||a1.size()==b1.size()&&a1<b1){pc('-'),swap(a1,b1);}int a[10010],b[10010],c[10010];int lena=a1.size(),lenb=b1.size();for(int i=0;i<lena;i++){a[i]=a1[lena-1-i]-'0';}for(int i=0;i<lenb;i++){b[i]=b1[lenb-1-i]-'0';}int lenc=lena;for(int i=0;i<lenc;i++){if(a[i]<b[i]){a[i+1]--,a[i]+=10;}c[i]=a[i]-b[i];}while(lenc>=1&&c[lenc-1]==0){lenc--;}string s;for(int i=lenc-1;i>=0;i--){s+=c[i]+'0';}return s;}
inline int qpow(int a,int b,int p){int ans=1;while(b){if(b&1){ans=(ans*a)%p;}b>>=1;a=(a*a)%p;}return ans;}
inline int qp(int a,int b){int ans=1;while(b){if(b&1){ans*=a;}b>>=1;a*=a;}return ans;}
int a[100010];
set<int>s1,s2;
signed main()
{
	int n;
	rd(n);
	for(int i=1;i<=n;i++)
	{
		rd(a[i]);
	}
	s1.insert(a[n]),s2.insert(-a[n]);
	double l=-2e9,r=2e9;
	int mx=a[n],mn=a[n];
	for(int i=n-1;i;i--)
	{
		if(a[i]>mx)
		{
			mx=a[i];
		}
		else
		{
			r=min(r,(a[i]+(*s1.lower_bound(a[i])))/2.0);
		}
		if(a[i]<mn)
		{
			mn=a[i];
		}
		else
		{
			l=max(l,(a[i]+(-*s2.lower_bound(-a[i])))/2.0);
		}
		s1.insert(a[i]),s2.insert(-a[i]);
	}
	if(l>=r)
	{
		puts("pigeon");
	}
	else
	{
		puts("lovely");
		printf("%.2lf\n",(l+r)/2.0);
	}
	return 0;
}
```

---

## 作者：LiaoYF (赞：0)

## 做法

一种类似二分的方法。

首先二分 $y$ ，然后判断相邻的两个数的绝对值大小是否递增，如果不满足要求，即存在一个 $i$ 使得 $|x_i| \geq |x_{i+1}|$ ，根据 $x_i$ 和 $x_{i+1}$ 的符号可以知道 $y$ 是大了还是小了，分类讨论结果如下表。

|$x_i$|$x_{i+1}$|$y$|
| :----------: | :----------: | :----------: |
|正 | 正| 小了 |
|正 | 负 | 小了 |
|负 | 正 | 大了 |
|负 | 负 | 大了 |


最后二分完了输出即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
long double a[100005],b[100005];
int check(long double x){
    for(int i=1;i<=n;i++){
        b[i]=a[i]-x;
    }
    for(int i=1;i<n;i++){
        if(abs(b[i])-abs(b[i+1])>1e-7){
            if(b[i]<0){
                return -1;
            }
            if(b[i]==0){
                return b[i+1]>0?-1:1;
            }
            if(b[i]>0){
                return 1;
            }
        }
        if(abs(abs(b[i])-abs(b[i+1]))<=1e-7){
            if(b[i]==b[i+1]){
                return -154;
            }else if(b[i]<0&&b[i+1]>0){
                return -1;
            }else{
                return 1;
            }
        }
    }
    return 0;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    long double l=-2e9,r=2e9,eps=1e-8;
    while(r-l>eps){
        long double mid=(l+r)/2;
        int x=check(mid);
        if(x==0){
            cout<<fixed<<setprecision(10)<<"lovely\n"<<mid<<"\n";
            return 0;
        }else if(x==1){
            l=mid;
        }else if(x==-1){
            r=mid;
        }else if(x==-154){
            cout<<"pigeon";
            return 0;
        }
    }
    cout<<"pigeon";
    return 0;
}
```

---

