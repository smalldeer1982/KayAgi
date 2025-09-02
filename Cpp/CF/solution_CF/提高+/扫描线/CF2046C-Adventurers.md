# Adventurers

## 题目描述

曾经，四位罗马商人在一座罗马宅邸中相聚，商讨他们的贸易计划。他们遇到了如下问题：他们都经营同一种商品，如果在同一座城市进行贸易，必然会遭受损失。于是他们决定将各自的贸易城市进行划分。

在本题中，罗马的地图可以表示为一个平面，其中标记了一些点——即罗马帝国的城市。

商人们决定选择一个划分点 $ (x_0, y_0) $。那么，对于坐标为 $ (x_i, y_i) $ 的城市：

- 如果 $ x_0 \le x_i $ 且 $ y_0 \le y_i $，则第一位商人在该城市售卖商品；
- 如果 $ x_0 > x_i $ 且 $ y_0 \le y_i $，则第二位商人在该城市售卖商品；
- 如果 $ x_0 \le x_i $ 且 $ y_0 > y_i $，则第三位商人在该城市售卖商品；
- 如果 $ x_0 > x_i $ 且 $ y_0 > y_i $，则第四位商人在该城市售卖商品。

商人们希望选择 $ (x_0, y_0) $，使得每个人分到的城市数最少值最大（即尽可能公平）。请你帮他们找到这样的一个点。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
4
1 1
1 2
2 1
2 2
4
0 0
0 0
0 0
0 0
8
1 2
2 1
2 -1
1 -2
-1 -2
-2 -1
-2 1
-1 2
7
1 1
1 2
1 3
1 4
2 1
3 1
4 1```

### 输出

```
1
2 2
0
0 0
2
1 0
0
0 0```

# 题解

## 作者：Xy_top (赞：6)

闲话：比赛时在学校上课，当时是体锻课，偷偷拿出手机看了眼题目，结果一眼秒了，要是赛时打估计就上 M 了。/kk

看到最小值的最大值，容易想到二分答案，我们钦定答案为 $a$，来看如何 ``check``。

枚举横坐标 $x$，把横坐标小于等于 $x$ 的点全部加入线段树，在线段树上二分出最小的纵坐标 $y$，使得在 $(x,y)$ 左上方的点的数量大于等于 $a$，接着再查询剩下三个方位是否符合要求即可。

代码很好写就不放了。

---

## 作者：Louis_1346 (赞：4)

### 题解：CF2046C Adventurers

### 题目大意

给定平面直角坐标系，以及 $n$ 对点对 $(a_i,b_i)$。

你需要找到有一个点，使得这个点把坐标系分成四部分，那么这个点的权值就是四个部分中各自点对数量的最小值。

你需要最大化这个最小值，同时，如果某个点正好在划分上，那么都优先分给靠右上的区域。

### 思路

典型的扫描线问题。

首先对 $x$ 排序，然后离散化 $y$。这是预处理的部分。

接着遍历 $x$，对于每一个 $x$，都会把坐标系分成两部分。

对于以 $x$ 分开，两边的部分，用树状数组维护以离散化以后 $y$ 区间个数和的信息，我们就可以快速查出对于每一个 $(x,y)$ 的取值了。

接下来问题转化成：给定两个序列，让你从某一个 $pos$ 把两个序列分开，最终答案是四个部分各自和最小值，最大化这个最小值。

考虑在 $x$ 固定的时候（即上面的问题），$ans=f(pos)$ 的取值，能很快的发现，$f(pos)$ 是一个斜率可以为 $0$ 的极值函数(也就是分段极值函数）。

因为是非严格递增，所以不能使用三分，于是我们只能考虑大力分类讨论的二分。

设两个序列分别为 $A$，$B$。每一段的和为 $a_1$，$a_2$，$b_1$，$b_2$。

一共分成四种情况讨论

- $a_1<a_2,b_1<b_2$

- $a_1<a_2,b_1>b_2$

- $a_1>a_2,b_1<b_2$

- $a_1>a_2,b_1>b_2$

分类讨论完了以后发现，其实不需要四种，我们只需要判断最小值是哪一个，然后判断左移还是右移就可以了。

时间复杂度 $O(n\log^2 n)$。

### code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+10;
int T;
struct node{
	int x,y;
}arr[maxn];
bool cmp(node a,node b){
	if(a.x==b.x) return a.y<b.y; 
	return a.x<b.x;
}
int lowbit(int x){
	return x&-x;
} 
struct BIT{
	int siz;
	int c[maxn];
	void init(int _n){
		memset(c,0,_n*8+20);
		siz=_n;
	}
	void insert(int x,int da){
		while(x<=siz){
			c[x]+=da;
			x+=lowbit(x); 
		}
	}
	int find(int x){
		int sum=0;
		while(x>0){
			sum+=c[x];
			x-=lowbit(x); 
		}
		return sum;
	} 
}lt,rt;
vector<int> v;
int get_ans(int y){
	int mn=0x3f3f3f3f3f3f3f3f;
	mn=min(mn,lt.find(y-1));
	mn=min(mn,lt.find(lt.siz)-lt.find(y-1));
	mn=min(mn,rt.find(y-1));
	mn=min(mn,rt.find(rt.siz)-rt.find(y-1));
	return mn;
}
int n;
int ansx,ansy;
int ans=0;
int count(int x){
	int l=1,r=v.size();
	int ans1=0x3f3f3f3f3f3f;
	while(l<r){
		ans1=0x3f3f3f3f3f3f3f3f;
		int mid=(l+r)>>1;
		int a1=lt.find(mid-1),a2=lt.find(lt.siz)-lt.find(mid-1);
		int b1=rt.find(mid-1),b2=rt.find(rt.siz)-rt.find(mid-1);
		ans1=min({ans1,a1,a2,b1,b2});
		if(ans1>ans){
			ans=ans1;
			ansx=x,ansy=v[mid-1];
		}
		if(a1==ans1||b1==ans1){
			l=mid+1;
		}else{
			r=mid;
		}
	}
	ans1=get_ans(l);
	if(ans1>ans){
		ans=ans1;
		ansx=x,ansy=v[l-1]; 
	}
	return ans;
}
int work(){
	ans=0;
	ansx=0,ansy=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,count(arr[i].x));
		int k=lower_bound(v.begin(),v.end(),arr[i].y)-v.begin()+1;
		lt.insert(k,1);
		rt.insert(k,-1);
//		ans=max(ans,count());
		while(arr[i].x==arr[i+1].x){
			++i;
			k=lower_bound(v.begin(),v.end(),arr[i].y)-v.begin()+1;
			lt.insert(k,1);
			rt.insert(k,-1);
		}
	}
	return ans;
}
void solve(){
	v.clear(); 
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&arr[i].x,&arr[i].y);
		v.push_back(arr[i].y); 
	}
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	lt.init(v.size()),rt.init(v.size());
	sort(arr+1,arr+1+n,cmp);
	for(int i=1;i<=n;i++){
		int k=lower_bound(v.begin(),v.end(),arr[i].y)-v.begin()+1;
		rt.insert(k,1);
	}
	printf("%lld\n",work()); 
	printf("%lld %lld\n",ansx,ansy);
}
signed main(){
	scanf("%lld",&T);
	while(T--) solve();
}

```

---

## 作者：gcx114514 (赞：2)

首先我们发现对关键点的坐标离散化是不会有问题的，但是最后选取的点不一定在关键点上（被这个卡了好久）。

那么我们考虑用两个树状数组同时从左到右进行扫描（当前扫描到 $i$），假设 $t_1$ 维护的是横坐标小于 $i$ 的，而 $t_2$ 维护的是横坐标大于等于 $i$ 的。

考虑如何计算当前横坐标的最优值，我们先考虑枚举纵坐标，可以发现随着纵坐标的增大在其上方点的个数就会减小（这好像是句废话），那么考虑二分。就是分别二分纵坐标在当前二分中点上面的贡献刚好大于下面的和下面大于上面的值，由于最后是取最小值，所以这一定是对的。

这样的时间复杂度就是 $O(n\log^2n)$，空间复杂度 $O(n)$，可以通过。

（注意：不要将横纵坐标搞混。）

### Code

```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb emplace_back
#define int long long
#define mk make_pair
#define reaD read
#define raed read
#define haed head
#define cotu cout
#define se second
#define fi first
#define itn int
using namespace std;
bool Mst;
const int Max=1e6+10;
const int mod=998244353;
const int inf=1e9+10;
const int Inf=1e9;

inline int read(){
	int res=0,v=1;
	char c=getchar();
	while(c<'0'||c>'9'){v=(c=='-'?-1:1);c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<3)+(res<<1)+(c^48);c=getchar();}
	return res*v;
}


template <typename T>
struct TreeArray{

	vector<T>sum;
	int len;
	inline int lowbit(int x){return x&(-x);}
	void init(int n){sum.clear();sum.resize(n+10);len=n;}
	inline T Query(int x){T ans=0;while(x){ans+=sum[x],x-=lowbit(x);}return ans;}
	inline void Modify(int x,T val){while(x<=len){sum[x]+=val,x+=lowbit(x);}}
	inline T Query(int l,int r){if(r<l)return 0;return Query(r)-Query(l-1);}

};

TreeArray<int>t1,t2;

struct point{
	int x,y;
	point(int x=0,int y=0):
		x(x),y(y){;}
}a[Max],b[Max];

vector<int>ysx,ysy;

vector<pii>s[Max];

struct Ans{
	int a1,a2,a3,a4;
}ans[Max];

void work(){
	int n=read();
	ysx.clear();ysy.clear();
	for(int i=1;i<=n;++i){
		int x,y;
		x=read();y=read();
		a[i]=point(x,y);
		ysx.pb(x);ysy.pb(y);
	}
	ysx.pb(-inf);ysy.pb(-inf);
	ysx.pb(-Inf);ysy.pb(-Inf);
	ysx.pb(Inf);ysy.pb(Inf);
	sort(ysx.begin(),ysx.end());
	sort(ysy.begin(),ysy.end());
	ysx.erase(unique(ysx.begin(),ysx.end()),ysx.end());
	ysy.erase(unique(ysy.begin(),ysy.end()),ysy.end());
	for(int i=1;i<=n;++i){
		a[i].x=lower_bound(ysx.begin(),ysx.end(),a[i].x)-ysx.begin();
		a[i].y=lower_bound(ysy.begin(),ysy.end(),a[i].y)-ysy.begin();
		s[a[i].x].pb(mk(a[i].y,i));
	}
	int m=ysx.size()-1;
	int N=ysy.size();
	t1.init(N);t2.init(N);
	for(int i=1;i<=n;++i)t2.Modify(a[i].y,1);
	for(int i=1;i<=m;++i){
		int l=1,r=N,res=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(min(t1.Query(1,mid-1),t2.Query(1,mid-1))<=min(t2.Query(mid,N),t1.Query(mid,N))){  //上面刚好大于下面
				res=mid;
				l=mid+1;
			}else{
				r=mid-1;
			}
		}
		l=1,r=N;int Res=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(min(t1.Query(1,mid-1),t2.Query(1,mid-1))>=min(t2.Query(mid,N),t1.Query(mid,N))){   //下面刚好大于上面
				Res=mid;
				r=mid-1;
			}else{
				l=mid+1;
			}
		}
		int r1=min(t1.Query(1,res-1),min(t2.Query(1,res-1),min(t1.Query(res,N),t2.Query(res,N))));
		int r2=min(t1.Query(1,Res-1),min(t2.Query(1,Res-1),min(t1.Query(Res,N),t2.Query(Res,N))));
		for(auto j:s[i]){
			t1.Modify(j.fi,1);
			t2.Modify(j.fi,-1) ;
		}
		if(r1<r2){
			ans[i].a1=r2;
			b[i]=point(i,Res);
		}else{
			ans[i].a1=r1;
			b[i]=point(i,res);
		}
	}
	int Res=-inf,pos=0;
	for(int i=1;i<=m;++i){
		int res=-inf;
		res=ans[i].a1;
		if(res>Res){
			pos=i;
			Res=res;
		}
	}
	cout << Res << "\n"	<< ysx[b[pos].x]  << ' ' << ysy[b[pos].y] << "\n";
	for(int i=1;i<=n;++i){
		s[a[i].x].clear();
	}
}


bool Med;
signed main(){
	int T=read();
	while(T--)work();
	

	cerr<< "Time: "<<clock()/1000.0 << "s\n";
	cerr<< "Memory: " << (&Mst-&Med)/1000000.0 << "MB\n";
	return 0;
}

```

---

## 作者：Iniaugoty (赞：2)

### [CF2046C Adventurers](/problem/CF2046C)

真是 DD 又 SS 啊。

考虑当分割点的 $x _ 0$ 已经确定时，如何求出答案。

最大化最小值，二分出最大的 $k$，使得存在一个 $y _ 0$，满足 $(x _ 0, y _ 0)$ 分出来的四部分都 $\ge k$。

考虑如何 check。先二分出一个最小的 $y _ 1$，使得 $(x _ 0, y _ 1)$ 左下的点的数量 $\ge k$；再二分出一个最小的 $y _ 2$，使得 $(x _ 0, y _ 2)$ 右下的点的数量 $\ge k$。

要求 $(x _ 0, y _ 0)$ 左下和右下都 $\ge k$，必然要求 $y _ 0 \ge \max (y _ 1, y _ 2)$。那只需要检查 $y _ 0 = \max (y _ 1, y _ 2)$ 即可。

对 $x, y$ 都离散化，枚举 $x _ 0$，两层二分再用树套树或者 KDT 维护二维数点，就得到了一个非常幽默的 $O(n \log ^ 4 n)$ 或者 $O(n \log ^ 2 n \sqrt n)$ 的做法。

注意到这里的二维数点在 $x$ 维上只是查前后缀，左右两半还是分开查的，于是分开维护两个线段树或者树状数组，利用扫描线的思想，左边的树不断加点，右边的树不断删点。二维数点的复杂度少了一个 $\log n$。

利用线段树上二分的技巧可以把内层二分的 $\log n$ 去掉。最后时间复杂度是 $O(n \log ^ 2 n)$，[代码](https://codeforces.com/contest/2047/submission/295509362)。

---

## 作者：内拉组里 (赞：1)

一道二维偏序（扫描线）的比较板的题

# Thoughts :

> 易得最终选择的目标点的横纵坐标一定在所给城市的坐标中，
>
> 故考虑直接离散化，然后对每一列开一个 vector 记录城市坐标デス～
>
> 考虑到随着行数增加区域所包含城市数存在一个单调性，所以可以二分最小城市数量。
>
> check
>
> > 开两个树状数组分别记录扫描线两边城市的横坐标。
> >
> > 记 $ T1 $ 记录扫描线左侧，$ T2 $ 记录扫描线右侧。
> >
> > 初始状态所有城市都在 $ T2 $ 中，
> >
> > 然后从左往右扫，
> >
> > 每次把扫描线上的点从 $ T2 $ 移到 $ T1 $。
> >
> > 这里加一点优化，记扫过的城市数为 $ cnt $，
> >
> > 那么当 $ cnt \lt 2k $ 时说明肯定还没有扫到合适的分界线，直接跳过。
> >
> > 同样地，当 $ n - cnt \lt 2k $ 时说明再往后扫也不可能扫到合适的分界线了，直接跳过。
> >
> > 然后再树状数组上倍增求第 $ k $ 小デス～
>
> 还有一些细节处理在代码里，不理解的话多看几遍吧。

# Analyses :

> 总时间复杂度 $ \Theta (N \log^2{N}) $ 
>
> 总空间复杂度 $ \Theta (N) $ 

# Code :

```cpp
/* reference : @SYZOJ.admin2 */
#include	<algorithm>
#include	<iostream>
#include	<cstring>
#include	<vector>
#include	<cmath>
using namespace std;
constexpr int maxn = 1e5+4;

int x[maxn];
int y[maxn];
int fx[maxn];
int fy[maxn];
vector<int> hd[maxn];
int T, cntx, cnty, ansx, ansy;

namespace TreeArr
{
	int n;
	int C1[maxn];
	int C2[maxn];
	
	inline int lowbit (int k)
	{
		return k & -k;
	}
	
	void add1 (int idx, int val)
	{
		for (int i = idx; i <= n; i += lowbit (i)) C1[i] += val;
	}
	
	void add2 (int idx, int val)
	{
		for (int i = idx; i <= n; i += lowbit (i)) C2[i] += val;
	}
	
	int sum1 (int idx)
	{
		int ans = 0;
		for (int i = idx; i; i -= lowbit (i)) ans += C1[i];
		return ans;
	}
	
	int sum2 (int idx)
	{
		int ans = 0;
		for (int i = idx; i; i -= lowbit (i)) ans += C2[i];
		return ans;
	}
    
	int kth1 (int k)
	{
		int idx = 0;
		for (int i = log2 (n); i > -1; i--)
		{
			if (idx + (1 << i) <= n && C1[idx + (1 << i)] < k)
			{
				idx += (1 << i);
				k -= C1[idx];
			}
		}
		return idx + 1;
	}
	
	int kth2 (int k)
	{
		int idx = 0;
		for (int i = log2 (n); i > -1; i--)
		{
			if (idx + (1 << i) <= n && C2[idx + (1 << i)] < k)
			{
				idx += (1 << i);
				k -= C2[idx];
			}
		}
		return idx + 1;
	}
}
using namespace TreeArr;

int check (int k)
{
	memset (C1, 0, sizeof C1);
	memset (C2, 0, sizeof C2);
	for (int i = 1; i <= n; i++) add2 (x[i], 1);
	int cnt = 0;
	for (int i = 1; i <= cnty; i++)
	{
		for(int j : hd[i])
		{
			add1 (j, 1);
			add2 (j, -1);
			++cnt;
		}
		if (cnt < (k << 1)) continue;
		if (n - cnt < (k << 1)) return 0;
		int l1 = kth1 (k) + 1;
		int l2 = kth2 (k) + 1;
		int r1 = kth1 (cnt - k + 1);
		int r2 = kth2 (n - cnt - k + 1);
		if (max (l1, l2) <= min(r1, r2))
		{
			ansx = fx[max(l1, l2)];
			ansy = fy[i + 1];
			return 1;
		}
	}
	return 0;
}

int main()
{
	cin >> T;
	while (T--)
	{
		cin >> n;
		for (int i = 1; i <= n; i++)
		{
			cin >> x[i] >> y[i];
			fx[i] = x[i];
			fy[i] = y[i];
			hd[i].clear();
		}
		sort (fx + 1, fx + n + 1);
		sort (fy + 1, fy + n + 1);
		cntx = unique (fx + 1, fx + n + 1) - fx - 1;
		cnty = unique (fy + 1, fy + n + 1) - fy - 1;
		for (int i = 1; i <= n; i++)
		{
			x[i] = lower_bound (fx + 1, fx + cntx + 1, x[i]) - fx;
			y[i] = lower_bound (fy + 1, fy + cnty + 1, y[i]) - fy;
			hd[y[i]].push_back(x[i]);
		}
		
		ansx = ansy = 0;
		int l = 1;
		int r = n;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			if (check (mid)) l = mid + 1;
			else r = mid - 1;
		}
		cout << l - 1 << endl;
		cout << ansx << ' ' << ansy << endl;
	}
	return 0;
}
```

---

## 作者：hnczy (赞：1)

## pts50

其实可以直接用一个离散化后的前缀和写的。

但是这里建议用扫描线加二维偏序来写，因为题目这就很二维偏序，而且容易优化。

怎么写呢？可以用两个树状数组来写一个记一下上面的点的分布，一个记一下下面的点的分布。

这样就可以实现 $O(nm\log(n))$ 的爆炸时间复杂度。

核心代码：

```c++
for(int i=1;i<=cnt2;i++){
	for(int j=1;j<=cnt1;j++){
		int mi=min({bit1.query(j-1),bit1.query(j,cnt1),bit2.query(j-1),bit2.query(j,cnt1)});
		if(ans<mi){
			ans=mi;
			xx=b1[j],yy=b2[i];
		} 
	} 
	for(int x:e[i]){
		bit1.add(x,1);
		bit2.add(x,-1);
	}
}
```

## pts100

可以用树状数组搞一个求第 $k$ 大的数是什么的功能。

代码如下：
```c++
int kth(int k){
		int x=0;
		for(int i=log2(n);i>=0;i--){
			if(x+(1<<i)<n&&c[x+(1<<i)]<k){
				x+=(1<<i);
				k-=c[x];
			}
		}//类似一个倍增 
		return x+1;
	}
```

再整体实现一个二分，来二分每一个商人所管辖的大小即可。

check 如下:

```c++
		for(int i=1;i<=cnt2;i++){
			for(int j=1;j<=cnt1;j++){
				int mi=min({bit1.query(j-1),bit1.query(j,cnt1),bit2.query(j-1),bit2.query(j,cnt1)});
				if(ans<mi){
					ans=mi;
					xx=b1[j],yy=b2[i];
				} 
			} 
			for(int x:e[i]){
				bit1.add(x,1);
				bit2.add(x,-1);
			}
		}
```

---

## 作者：_Ch1F4N_ (赞：1)

首先给所有点横纵坐标离散化。

然后枚举 $x_0$，类似扫描线那样去维护 $x = x_0$ 分割出的两个平面上的所有点的 $y$ 坐标，然后考虑对于一个 $y_0$ 而言，其带来的贡献是是 $y = y_0$ 下方两个平面内点数 $\min$ 与其上方的两个平面点数 $\min$ 再取 $\min$，观察到移动 $y_0$ 时形如一个非递增序列与一个非递减序列取 $\min$，这不是我们冰火战士吗？二分出最后一个非递减序列小于等于非递增序列的位置，这个位置与其后面一个位置中一定产生了最大值，因为其他位置一定可以向左移动或者向右移动一个位置并且使得答案不变劣，考虑在维护扫描线的数据结构上二分，这里我写的是树状数组上倍增，时间复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+114;
const int inf = 1e9;
int n;
int X[maxn],Y[maxn];
int u[maxn],v[maxn];
int totx,toty;
int tr[maxn][2];
vector<int> P[maxn];//(x,y)
pair<int,pair<int,int> > ans;
void add(int u,int c,int ty){
    while(u<=n) tr[u][ty]+=c,u+=(u&(-u));
}
int pre(int u,int ty){
    int c=0;
    while(u>0) c+=tr[u][ty],u-=(u&(-u));
    return c;
}
void work(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>u[i]>>v[i],X[i]=u[i],Y[i]=v[i];
    sort(X+1,X+n+1);
    sort(Y+1,Y+n+1);
    totx=unique(X+1,X+n+1)-(X+1);
    toty=unique(Y+1,Y+n+1)-(Y+1);
    for(int i=1;i<=n;i++){
        int l=1,r=totx+1;
        while(l+1<r){
            int mid=(l+r)>>1;
            if(X[mid]<=u[i]) l=mid;
            else r=mid;
        }
        u[i]=l;
        l=1,r=toty+1;
        while(l+1<r){
            int mid=(l+r)>>1;
            if(Y[mid]<=v[i]) l=mid;
            else r=mid;
        }
        v[i]=l;
        P[u[i]].push_back(v[i]);
        add(v[i],1,1);
    }
    for(int x=1;x<=totx;x++){
        for(int y:P[x]) add(y,-1,1),add(y,1,0);
        int sum0=pre(n,0),sum1=pre(n,1);
        int now0=0,now1=0;
        int p=0;
        for(int j=18;j>=0;j--){
            if(p+(1<<j)>n) continue;
            int c0=tr[p+(1<<j)][0],c1=tr[p+(1<<j)][1];
            if(min(now0+c0,now1+c1)<=min(sum0-now0-c0,sum1-now1-c1)) now0+=c0,now1+=c1,p+=(1<<j);
        }
        if(p!=0) ans=max(ans,make_pair(min(min(pre(p,0),pre(p,1)),min(pre(n,0)-pre(p,0),pre(n,1)-pre(p,1))),make_pair(x,p)));
        if(p+1<=n) p++,ans=max(ans,make_pair(min(min(pre(p,0),pre(p,1)),min(pre(n,0)-pre(p,0),pre(n,1)-pre(p,1))),make_pair(x,p)));
    }
    cout<<ans.first<<'\n'<<min(inf,X[ans.second.first]+1)<<' '<<min(Y[ans.second.second]+1,inf)<<'\n';
    for(int i=1;i<=n;i++) tr[i][0]=tr[i][1]=0,P[i].clear();
    ans=make_pair(-1,make_pair(-1,-1));
    return ;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
```

---

