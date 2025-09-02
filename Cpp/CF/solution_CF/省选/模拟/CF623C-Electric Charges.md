# Electric Charges

## 题目描述

Programmer Sasha is a student at MIPT (Moscow Institute of Physics and Technology) and he needs to make a laboratory work to pass his finals.

A laboratory unit is a plane with standard coordinate axes marked on it. Physicists from Moscow Institute of Physics and Technology charged the axes by large electric charges: axis $ X $ is positive and axis $ Y $ is negative.

Experienced laboratory worker marked $ n $ points with integer coordinates $ (x_{i},y_{i}) $ on the plane and stopped the time. Sasha should use "atomic tweezers" to place elementary particles in these points. He has an unlimited number of electrons (negatively charged elementary particles) and protons (positively charged elementary particles). He can put either an electron or a proton at each marked point. As soon as all marked points are filled with particles, laboratory worker will turn on the time again and the particles will come in motion and after some time they will stabilize in equilibrium. The objective of the laboratory work is to arrange the particles in such a way, that the diameter of the resulting state (the maximum distance between the pairs of points of the set) is as small as possible.

Since Sasha is a programmer, he naively thinks that all the particles will simply "fall" into their projections on the corresponding axes: electrons will fall on axis $ X $ , while protons will fall on axis $ Y $ . As we are programmers too, we will consider the same model as Sasha. That is, a particle gets from point $ (x,y) $ to point $ (x,0) $ if it is an electron and to point $ (0,y) $ if it is a proton.

As the laboratory has high background radiation and Sasha takes care of his laptop, he did not take it with him, and now he can't write a program that computes the minimum possible diameter of the resulting set. Therefore, you will have to do it for him.

Print a square of the minimum possible diameter of the set.

## 说明/提示

In the first sample Sasha puts electrons at all points, all particles eventually fall at a single point $ (1,0) $ .

In the second sample Sasha puts an electron at point $ (1,10) $ , and a proton at point $ (10,1) $ . The result is a set of two points $ (1,0) $ and $ (0,1) $ , which has a diameter of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF623C/2826342a15affce70e459206e8466cd2b66552a3.png).

## 样例 #1

### 输入

```
3
1 10
1 20
1 30
```

### 输出

```
0
```

## 样例 #2

### 输入

```
2
1 10
10 1
```

### 输出

```
2
```

# 题解

## 作者：9AC8E2 (赞：3)

二分答案,那么问题转化为是否存在一个划分方案使得
$$\left\{\begin{aligned}\max_{i\in X}\{x_i^2\}+\max_{i\in Y}\{y_i^2\}\leq mid\\\max_{i,j\in X}\{x_i-x_j\}\leq \sqrt{mid}\\\max_{i,j\in Y}\{y_i-y_j\}\leq \sqrt{mid}\end{aligned}\right.$$

其中 $X$ 为映射在 $x$ 轴上的点的集合, $Y$ 为映射在 $y$ 轴上的点的集合

将点按 $x$ 排序

显然,如果存在方案,一定存在使得 $X$ 中的点编号连续的划分方案

枚举钦定一个点作为 $X$ 中产生贡献的那个点,将尽可能多的点划分进 $X$ 中,将剩下的点划分进 $ Y$,通过预处理前缀 $\min$,前缀 $\max$,后缀 $\min$,后缀 $\max$可以 $O(1)$ 计算这部分的贡献

```
#include<bits/stdc++.h>
using namespace std;
#define Ri register
template<typename T>inline T read(Ri T&t)
{Ri T f=1;Ri char ch=getchar();t=0;
while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
while(ch>='0'&&ch<='9')t=t*10+ch-'0',ch=getchar();t*=f;return t;}
template<typename T,typename...Args>
inline void read(T&t,Args&...args)
{read(t);read(args...);}
const long long p=998244353;
inline long long power(Ri long long x,Ri long long k=p-2)
{Ri long long re=1;for(;k;k>>=1,x=x*x%p)if(k&1)re=re*x%p;return re;}
struct node{long long x,y;}v[100005];
int n;
long long l_min[100005],l_max[100005];
long long r_min[100005],r_max[100005];
#define squ(X) ((X)*(X))
bool check(long long mid)
{
	int r=1;
	for(int l=1;l<=n;l++)//钦定左端点产生贡献 
	{
		if(v[l].x>0)break;
		while(abs(v[r+1].x)<=abs(v[l].x)&&squ(v[r+1].x-v[l].x)<=mid&&r+1<=n)r++;
		while(abs(v[r].x)>abs(v[l].x))r--;
//		printf("l=%d r=%d\n");
		long long X=max(squ(v[l].x),squ(v[r].x));
		if(squ(v[l].x-v[r].x)>mid||X>mid)
			continue;
		if(l==1&&r==n)
			return 1;
		if(l==1&&r!=n)
			if(X+max(squ(r_max[r+1]),squ(r_min[r+1]))<=mid&&squ(r_max[r+1]-r_min[r+1])<=mid)
				return 1;
		if(l!=1&&r==n)
			if(X+max(squ(l_max[l-1]),squ(l_min[l-1]))<=mid&&squ(l_max[l-1]-l_min[l-1])<=mid)
				return 1;
		if(l!=1&&r!=n)
		{
			long long low=min(l_min[l-1],r_min[r+1]);
			long long high=max(l_max[l-1],r_max[r+1]);
			if(X+max(squ(low),squ(high))<=mid&&squ(low-high)<=mid)
				return 1;
		}
	}
	int l=n;
	for(int r=n;r>=1;r--)
	{
		if(v[r].x<0)break;
		while(abs(v[l-1].x)<=abs(v[r].x)&&squ(v[r].x-v[l-1].x)<=mid&&l-1>=1)l--;
		while(abs(v[l].x)>abs(v[r].x))l++;
//		printf("l=%d r=%d\n",l,r);
		long long X=max(squ(v[l].x),squ(v[r].x));
		if(squ(v[l].x-v[r].x)>mid||X>mid)
			continue;
		if(l==1&&r==n)
			return 1;
		if(l==1&&r!=n)
			if(X+max(squ(r_max[r+1]),squ(r_min[r+1]))<=mid&&squ(r_max[r+1]-r_min[r+1])<=mid)
				return 1;
		if(l!=1&&r==n)
			if(X+max(squ(l_max[l-1]),squ(l_min[l-1]))<=mid&&squ(l_max[l-1]-l_min[l-1])<=mid)
				return 1;
		if(l!=1&&r!=n)
		{
			long long low=min(l_min[l-1],r_min[r+1]);
			long long high=max(l_max[l-1],r_max[r+1]);
			if(X+max(squ(low),squ(high))<=mid&&squ(low-high)<=mid)
				return 1;
		}
	}
	return 0;
}
int main()
{
	read(n);
	if(n==1)return printf("0"),0;
	for(int i=1;i<=n;i++)
		read(v[i].x,v[i].y);
	sort(v+1,v+n+1,[](node a,node b){return a.x<b.x;});
	long long ans=squ(v[1].x-v[n].x);
//	return printf("%lld\n",ans);
	l_min[1]=l_max[1]=v[1].y;
	for(int i=2;i<=n;i++)
		l_min[i]=min(l_min[i-1],v[i].y),
		l_max[i]=max(l_max[i-1],v[i].y);
	r_min[n]=r_max[n]=v[n].y;
	for(int i=n-1;i>=1;i--)
		r_min[i]=min(r_min[i+1],v[i].y),
		r_max[i]=max(r_max[i+1],v[i].y);
	ans=min(ans,squ(r_max[1]-r_min[1]));
	long long l=0,r=4e16;
//	return printf("check 0=%d\n",check(0));
	while(l<r)
	{
		long long mid=((l+r)>>1);
		if(check(mid))r=mid;
		else l=mid+1;
	}
	printf("%lld\n",min(l,ans));
	return 0;
}

```

---

## 作者：紊莫 (赞：2)

提供一种自然的二分判断方法，避免了其他题解中抽象的钦定左右端点做法。

前面的结论就不说了，可见其他题解，我们分别对 $x, y$ 轴计算，下面以 $x$ 轴为例。

对于 ``check``，我们双指针维护 $l, r$ 表示当前选的 $x$ 坐标的极长段。

那么计算答案可以通过前后缀的 $\max y,\min y$ 和 $l, r$ 两点的 $x$ 坐标来得到。

问题在于我们不能得到了这个最长的线段后再去判断，而是需要边维护 $r$ 边判断答案，详见代码。

不理解的可以看这一组 hack：


```
5
3 6
4 8
7 2
8 2
10 1
```

答案是：


```
20
```

那么做法就直接维护前缀后缀最大最小即可。


```cpp
#include <bits/stdc++.h>
#define int long long

#define F(i, a, b) for (int i = (a); i <= (b); ++i)
#define dF(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int N = 200005, M = (N << 1), inf = 1e18, mod = 1e9 + 7;
int n, pmn[N], pmx[N], smn[N], smx[N]; pii p[N];
inline int pf(int x) { return x * x; }
inline int dis(pii x, pii y) { return pf(x.first - y.first) + pf(x.second - y.second); }
int ck(int l, int r, int mid) {
    int mn = inf, mx = -inf;
    mn = min(pmn[l - 1], smn[r + 1]);
    mx = max(pmx[l - 1], smx[r + 1]);
    if (mn == inf && mx == -inf) return 1;
    if (pf(mx - mn) <= mid) {
        int d = dis({p[l].first, 0}, {0, mx});
        d = max(d, dis({p[l].first, 0}, {0, mn}));
        d = max(d, dis({p[r].first, 0}, {0, mn}));
        d = max(d, dis({p[r].first, 0}, {0, mx}));
        if (d <= mid) return 1;
    }
    return 0;
}
int check(int mid) {
    for (int l = 1, r = 1; l <= n; l++) {
        if (l <= r && ck(l, r, mid)) return 1;
        while (r < n && pf(p[r + 1].first - p[l].first) <= mid) {
            r++;
            if (ck(l, r, mid)) return 1;
        }
    }
    return 0;
}
void init() {
    sort(p + 1, p + n + 1);
    pmn[0] = inf, pmx[0] = -inf;
    smn[n + 1] = inf, smx[n + 1] = -inf;
    F(i, 1, n) {
        pmn[i] = min(pmn[i - 1], p[i].second);
        pmx[i] = max(pmx[i - 1], p[i].second);
    }
    dF(i, n, 1) {
        smn[i] = min(smn[i + 1], p[i].second);
        smx[i] = max(smx[i + 1], p[i].second);
    }
}
signed main() {
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    F(i, 1, n) cin >> p[i].first >> p[i].second;
    init();
    ll l = 0, r = 1e18, ans = 0;
    while (l <= r) {
        ll mid = l + r >> 1;
        if (check(mid)) {
            r = mid - 1, ans = mid;
        } else {
            l = mid + 1;
        }
    }
    F(i, 1, n) swap(p[i].first, p[i].second);
    init();
    l = 0, r = 1e18;
    while (l <= r) {
        ll mid = l + r >> 1;
        if (check(mid)) {
            r = mid - 1, ans = min(ans, mid);
        } else {
            l = mid + 1;
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

首先离散化。

二分答案（即最终 $dis$ 的最小值），设为 $mid$。双指针出保留 $x$ 坐标在 $[l,r]$ 内的情况。显然对于一个 $l$，一定会选择一个最远的 $r$ 使得 $(r-l)^2\leq mid^2$。

$l,r$ 同号时，不妨设 $0\leq l\leq r$，对于 $x$ 坐标在其他范围内的点显然只能排到 $y$ 轴上去。预处理出 $x$ 坐标前缀/后缀的 $|y|$ 的最大值。判断 $r^2+|y|_{\max}^2\leq mid^2$ 即可。

$l,r$ 异号时，不妨设 $|l|\geq|r|$。同样像上面一样处理即可。

总复杂度 $O(n\log n)$。细节比较多，具体见代码。

```cpp
#pragma GCC optimize(2,3,"Ofast","inline")
#include <bits/stdc++.h>
#define int long long
#define s(i,j) ((i-1)*m+j)
#define add(i,j) ((i+j>=mod)?i+j-mod:i+j)
using namespace std;
int tmv;
struct node{
	int x,y;
}a[100005],b[100005],c[100005],la[100005],lb[100005],lc[100005];
int sufbmin[100005],sufcmin[100005];
int sufbmax[100005],sufcmax[100005];
int m,k;
bool cmpx(node p,node q){
	return llabs(p.x)<llabs(q.x);
}
int realsqrt(int n){
	int p=sqrtl(n);
	while((p+1)*(p+1)<=n) p++;
	while(p*p>n) p--;
	return p;
}
int v[100005];
signed main(){
	int n=100000; cin>>n;
	for(int i=1;i<=n;i++){
 		cin>>a[i].x>>a[i].y;
		la[i].x=llabs(a[i].x);
		la[i].y=llabs(a[i].y);
		if(a[i].x<0) b[++m]=a[i];
		else c[++k]=a[i];
	}
	sort(b+1,b+m+1,cmpx);
	sort(c+1,c+k+1,cmpx);
	for(int i=1;i<=m;i++) lb[i].x=llabs(b[i].x),lb[i].y=llabs(b[i].y);
	for(int i=1;i<=k;i++) lc[i].x=llabs(c[i].x),lc[i].y=llabs(c[i].y);
	sufbmin[m+1]=sufcmin[k+1]=1e18;
	sufbmax[m+1]=sufcmax[k+1]=-1e18;
	for(int i=m;i>=1;i--) sufbmin[i]=min(b[i].y,sufbmin[i+1]),sufbmax[i]=max(b[i].y,sufbmax[i+1]);
	for(int i=k;i>=1;i--) sufcmin[i]=min(c[i].y,sufcmin[i+1]),sufcmax[i]=max(c[i].y,sufcmax[i+1]);
	int L=0,R=4e18;
	while(L<R){
		int mid=(L+R)>>1;
		int dis=realsqrt(mid),ok=0;
		{
			int r=0;
			for(int i=1;i<=m;i++){
				if(llabs(b[i].x-b[1].x)>dis) break;
				while(r!=k&&llabs(c[r+1].x-b[i].x)<=dis&&llabs(c[r+1].x)<=llabs(b[i].x)){
					r++;
				}
				while(r&&llabs(c[r].x-b[i].x)>dis){
					r--;
				}
				int tp1=-min(sufbmin[i+1],sufcmin[r+1]),tp2=max(sufbmax[i+1],sufcmax[r+1]);
				if(tp1<0) tp1=0;
				if(tp2<0) tp2=0;
				if(i==m&&r==k){
					ok=1;
				}
				else{
					if((tp1+tp2)*(tp1+tp2)<=mid){
						if(max(tp1,tp2)*max(tp1,tp2)+b[i].x*b[i].x<=mid){
							ok=1;
						}
					}
				}
			}
		}
		{
			int r=0;
			for(int i=1;i<=k;i++){
				if(llabs(c[i].x-c[1].x)>dis) break;
				while(r!=m&&llabs(b[r+1].x-c[i].x)<=dis&&llabs(b[r+1].x)<=llabs(c[i].x)){
					r++;
				}
				while(r&&llabs(b[r].x-c[i].x)>dis){
					r--;
				}
				int tp1=-min(sufbmin[r+1],sufcmin[i+1]),tp2=max(sufbmax[r+1],sufcmax[i+1]);
				if(tp1<0) tp1=0;
				if(tp2<0) tp2=0;
				if(i==k&&r==m){
					ok=1;
				}
				else{
					if((tp1+tp2)*(tp1+tp2)<=mid){
						if(max(tp1,tp2)*max(tp1,tp2)+c[i].x*c[i].x<=mid){
							ok=1;
						}
					}
				}
			}
		}
		if(ok) R=mid;
		else L=mid+1;
	}
	int minv=1e9,maxv=-1e9;
	for(int i=1;i<=n;i++) minv=min(minv,a[i].y),maxv=max(maxv,a[i].y);
	cout<<min((maxv-minv)*(maxv-minv),L);
	return 0;
}
```

---

