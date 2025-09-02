# [POI 2007] OSI-Axes of Symmetry

## 题目描述

Johnny 是一位非常年轻的数学家，但他此刻正在为他妹妹的数学作业烦恼。

这个周末，他的妹妹需要完成一项作业，计算各种几何图形的对称轴数量。因为 Johnny 这个周末想要去海边旅行，所以他希望他的妹妹能尽快完成这项作业。

于是他找到了擅长编程的你，你一定能帮助他完成这项任务的！

## 说明/提示

$1 \leq t \leq 10$，$3 \leq n \leq 10^5$，$-10^8 \leq x_i,y_i \leq 10^8$。

## 样例 #1

### 输入

```
2
12
1 -1
2 -1
2 1
1 1
1 2
-1 2
-1 1
-2 1
-2 -1
-1 -1
-1 -2
1 -2
6
-1 1
-2 0
-1 -1
1 -1
2 0
1 1```

### 输出

```
4
2```

# 题解

## 作者：白桦树 (赞：8)

发一下KMP的做法
### 广告
无耻地安利一下本蒟蒻的blog
[蒟蒻の博客](https://www.cnblogs.com/birchtree/)
### 题面

给定一个多边形，求对称轴数量。

### 分析

初看这似乎是一道计算几何的题目，但是如果暴力枚举对称轴，再去判断对称轴两边的边和角是否相等，时间复杂度为$O(n^2)$,显然会TLE

##### 问题转换

顺时针转一圈，将角和边的值连在一起就得到了一个环

假如有一个边长为1的等边三角形，则它的角和边序列应该是：
1,60°,1,60°,1,60°，围成一个含有2n个元素的环（角为环上的边，边为环上的结点）之后就

变成了：

![](https://i.loli.net/2018/10/27/5bd416c45a371.jpg)

将1记为a,60°记为b，则环变为：

![](https://i.loli.net/2018/10/27/5bd41708b3bdf.jpg)

而对称轴会把这些点分成两部分，且两部分完全一样，对应到序列上就是：断开环上的某一条边，且连

成的序列是回文的

![](https://i.loli.net/2018/10/27/5bd4171182f47.jpg)

##### 环的处理

对于环上的回文问题，我们不好处理。一种常见的处理方法是**选择任意一个位置断开，将序列复制成**

**为2倍长度的链**。
![](https://i.loli.net/2018/10/27/5bd417117ca36.jpg)

然后我们在这条长度为4n的链上找长度为2n的回文串



##### 找回文串

如何找回文串？Manacher算法是一种很有效的方法，但KMP的使用范围更广。先选择任意一个位置断开，记该序列为S0,再复制一遍得到序列S，将S0反过来得到串T，求S中有多少个位置和T匹配即可

时间复杂度$O(n)$



##### 一些细节

- 如何处理边和角？ 边直接用长度表示（注意不必要开方，直接用长度的平方算，大量计算根号会导致TLE），而角由于考虑到图形不一定是凸多边形，采用叉积的方法记录角度，而不是点积。这里运用了叉积的性质：两向量夹角小于180°为正值，夹角大于180°为负值
- 边和角都用long long 存储，不必用double
- 序列S的长度为4n,序列T的长度为2n,数组不要开小了

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define maxn 100005
using namespace std;
inline void qread(int &x) {
	x=0;
	int sign=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-') sign=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		x=x*10+c-'0';
		c=getchar();
	}
	x=x*sign;
}

int n;
int T;
struct point {//点 
	long long x;
	long long y;
	point() {

	}
	point(long long xx,long long yy) {
		x=xx;
		y=yy;
	}
	friend point operator +(point a,point b) {
		return point(a.x+b.x,a.y+b.y);
	}
	friend point operator -(point a,point b) {
		return point(a.x-b.x,a.y-b.y);
	}
} a[maxn];
typedef point vector;//在程序实现上，点和向量没有区别 
long long dot(vector a,vector b) {//点积 
	return a.x*b.x+a.y*b.y;
}
long long cross(vector a,vector b) {//叉积 
	return a.x*b.y-a.y*b.x;
}

long long dist(point a,point b) {//计算两点间距离 
	vector v=a-b;
	return dot(v,v);
}

long long work_edge(int x) {//逐一处理多边形的边，注意编号为n的点下一个点是1 
	int y=x+1;
	if(y>n) y=1;
	return dist(a[x],a[y]);
}
long long work_ang(int x) {//处理角，同样注意编号为n的点下一个点是1 
	int y=x+1,z=x+2;
	if(y>n) y=y%n;
	if(z>n) z=z%n;
	return cross(a[y]-a[x],a[z]-a[y]);
}
long long edge[maxn];
long long ang[maxn];
long long tmp[maxn];
int s[maxn*4];
int t[maxn*2];

int next[maxn*4];
int f[maxn*4];
int KMP(int *a,int n,int *b,int m) {//KMP模板 
	next[1]=0;
	for(int i=2,j=0; i<=n; i++) {
		while(j>0&&a[i]!=a[j+1]) j=next[j];
		if(a[i]==a[j+1]) j++;
		next[i]=j;
	}
	for(int i=2,j=0; i<=m; i++) {
		while(j>0&&b[i]!=a[j+1]) j=next[j];
		if(b[i]==a[j+1]) j++;
		f[i]=j;
	}
	int cnt=0;
	for(int i=1; i<=m; i++) {
		if(f[i]==n) cnt++;
	}
	return cnt;
}
int main() {
	int x,y;
	qread(T);
	while(T--) {
		qread(n);
		for(int i=1; i<=n; i++) {
			qread(x);
			qread(y);
			a[i].x=x;
			a[i].y=y;
		}
		for(int i=1; i<=n; i++) {
			edge[i]=work_edge(i);
			ang[i]=work_ang(i);
		}
		int newn=0;
		int newm=0;
		for(int i=1; i<=n; i++) {//由于计算的角是第i与i+1条边之间的夹角，所以先加入边，再加入角 
			s[++newn]=edge[i];
			s[++newn]=ang[i];
		}
		for(int i=1; i<=n; i++) {
			s[++newn]=edge[i];
			s[++newn]=ang[i];
		}
		for(int i=n*2; i>=1; i--) {
			t[++newm]=s[i];
		}
		printf("%d\n",KMP(t,newm,s,newn));
	}
}


```

---

## 作者：Drinkwater (赞：8)

NYG讲的神题，这一眼看上去像是计算几何的题目，但是巧妙地转换一下变成字符串处理会更好处理，我们把边和角（叉积）都hash下，然后跑一遍manacher，或者搞个反串跑个kmp，或者后缀数组，SAM什么的都可以，求个最长回文串，ok了，抢个沙发啊啊啊。












```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<map>
using namespace std;
typedef long long LL;
#define REP(i,a,b) for(register int i = (a),i##_end_ = (b); i <= i##_end_; ++i)
#define DREP(i,a,b) for(register int i = (a),i##_end_ = (b); i >= i##_end_; --i)
#define mem(a,b) memset(a,b,sizeof(a))
template<typename T> inline bool chkmin(T &a,const T &b) { return a > b ? a = b , 1 : 0;}
template<typename T> inline bool chkmax(T &a,const T &b) { return a < b ? a = b , 1 : 0;}
int read()
{
    register int f = 1,s = 0;char c = getchar();
    while(!isdigit(c)) { if(c == '-')f = -1;c = getchar();}
    while(isdigit(c)) { s = s * 10 + c - '0';c = getchar();}
    return f * s;
}
const int maxn = 100011;
int T,n;
typedef double db;
struct node
{
    int x,y;
}p[maxn];
int dis(int i,int j)
{
    db xa = p[i].x,ya = p[i].y,xb = p[j].x,yb = p[j].y;
    return (xa-xb)*(xa-xb)+(ya-yb)*(ya-yb);
}
int cross(int i,int j,int k)
{
    node p1,p2;
    p1.x = p[j].x-p[i].x;p1.y = p[j].y-p[i].y;
    p2.x = p[k].x-p[i].x;p2.y = p[k].y-p[i].y;
    return p1.x*p2.y-p2.x*p1.y;
}
int s[maxn<<3];
int RL[maxn<<3],Maxr,pos;
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
#endif
    T = read();
    REP(I,1,T)
    {
        n = read();mem(s,0);mem(p,0);
        mem(RL,0);Maxr = pos = 0;
        REP(i,0,n-1)p[i].x = read(),p[i].y = read();
        REP(i,0,n-1)s[i<<1|1] = dis(i,(i+1)%n);
        REP(i,0,n-1)s[i<<1] = cross(i,(i-1+n)%n,(i+1)%n);
        //REP(i,0,(n<<1)-1)cout<<s[i]<<" ";puts(" ");
        int N = n<<1;
        REP(i,0,n-1)s[i+N] = s[i];
        int ans = 0;
        N<<=1;
        REP(i,0,N-1)
        {
            if(i < Maxr)RL[i] = min(RL[2*pos-i],Maxr-i);
            else RL[i] = 1;
            while(i - RL[i] >= 0 && i + RL[i] <= N && s[i+RL[i]] == s[i-RL[i]])RL[i]++;
            if(i+RL[i] > Maxr)Maxr = i+RL[i],pos = i;
            if(RL[i] >= n+1)ans++;
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：pythoner713 (赞：7)

按顺序，交替地，记录下多边形的边角信息。

例如样例中的第二个多边形：

![](https://cdn.luogu.com.cn/upload/image_hosting/ow4r7evq.png)

以右下角为起点，逆时针交替记录边角，得到长度为 $2n$ 的序列：

$$\sqrt2\to90\degree\to\sqrt2\to135\degree\to2\to135\degree\to\sqrt2\to90\degree\to\sqrt2\to135\degree\to2\to135\degree$$

这里的序列可以看作一个环，最后一项连向第一项。

角度与边长都是实数，不好处理。不如使用两条边向量的叉积代替角度，用边长的平方代替边长，这样就以将实数环转化为整数环：

$$2\to\underline2\to2\to2\to\underline4\to2\to2\to\underline2\to2\to2\to\underline4\to2$$

此时，原多边形有几条对称轴即可转化为下列问题：**环上有几个位置，满足将环从这里断开后，可以得到一条回文链？**

在这个样例中，共有 $4$ 个位置满足条件，因此多边形有 $2$ 个对称轴（一条对称轴穿过两个位置）。

现在，我们把一个计算几何问题转化成了字符串问题。而本题解的创新之处在于返璞归真地用哈希解决了问题：我们将原长为 $2n$ 的序列倍长为 $4n$，然后对于每个 $1\le i\le 2n$，检查区间 $[i,i+2n]$ 是否为回文串（断环成链）。回文串的检查可以用哈希优化至 $\mathcal O(1)$，也就是对于原串正反分别做一次哈希，然后判断该区间的正反哈希值是否相等即可。

---

```cpp
#include<bits/stdc++.h>
#define nb 400010
#define int long long
using namespace std;

int _, n, s[nb];
unsigned int B = 131, H1[nb], H2[nb], P[nb] = {1};
struct point{int x, y;}p[nb];

bool check(int l, int r){
	unsigned int h1 = H1[r] - H1[l - 1] * P[r - l + 1];
	unsigned int h2 = H2[l] - H2[r + 1] * P[r - l + 1];
	return h1 == h2;	// 正反哈希值相等说明回文
}

signed main(){
	for(int i = 1; i < nb; i++)
		P[i] = P[i - 1] * B;
	for(cin >> _; _--;){
		cin >> n;
		int ans = 0;
		for(int i = 1; i <= n; i++)
			cin >> p[i].x >> p[i].y;
		for(int i = 1; i <= n; i++){
			int A = i, B = i + 1, C = i + 2;
			B -= (B > n) * n, C -= (C > n) * n;
			s[i * 2 - 1] = pow(p[A].x - p[B].x, 2) + pow(p[A].y - p[B].y, 2);
			s[i * 2] = (p[A].x - p[B].x) * (p[B].y - p[C].y) - (p[A].y - p[B].y) * (p[B].x - p[C].x);
			// s[2i - 1] 和 s[2i] 分别记录边角信息
			// 叉积公式: (a, b) × (c, d) = ad - bc
		}
		for(int i = 1; i <= n * 2; i++) s[i + n * 2] = s[i];		  // 断环成链
		for(int i = 1; i <= n * 4; i++) H1[i] = H1[i - 1] * B + s[i]; // 正向哈希
		for(int i = n * 4; i >= 1; i--) H2[i] = H2[i + 1] * B + s[i]; // 反向哈希
		for(int i = 1; i <= n * 2; i++) ans += check(i, i + n * 2);	  // 判断回文
		cout << ans / 2 << endl;									  // 答案除二
	}
	return 0;
}
```


---

## 作者：iuyi (赞：7)

这题看似要用到字符串算法，其实暴力就可以过

为了方便处理，可以在相邻两个点之间插入两个点的中点，

这样就只需要考虑对称轴经过两个点的情况了

枚举每个位置，然后暴力判断是否为对称轴

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef complex<double> cp;

int n;
cp a[200005];
int p[100005];

double dj(cp x, cp y) {
	return x.real()*y.real() + x.imag()*y.imag();
}

double cj(cp x, cp y) {
	return x.real()*y.imag() - x.imag()*y.real();
}

bool chk(int ps) {
	auto dz = a[(ps+n/2-1)%n+1] - a[ps];
	for (int i = 1; i*2 < n; i++) {
		int ps1 = (ps+p[i]-1)%n+1;
		int ps2 = (ps-p[i]-1+n)%n+1;
		auto md = (a[ps1]+a[ps2]) / (double)2;
		if (cj(md-a[ps],dz) != 0 || dj(a[ps2]-a[ps1],dz) != 0) {
			return 0;
		}
	}
	return 1;
}

signed main() {
//	srand(time(0));
	int t;
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 0; i < n; i++) {
			int x;
			scanf("%d",&x);
			a[i*2+1].real(x);
			scanf("%d",&x);
			a[i*2+1].imag(x);
		}
		for (int i = 1; i < n; i++) {
			a[i*2] = (a[i*2-1] + a[i*2+1]) / (double)2;
		}
		a[n*2] = (a[1] + a[n*2-1]) / (double)2;
		for (int i = 1; i < n; i++) {
			p[i] = i;
		}
//		random_shuffle(p+1,p+n);
		int as = 0;
		n *= 2;
		for (int i = 1; i*2 <= n; i++) {
			if (chk(i)) {
				as++;
			}
		}
		cout << as << endl;
	}
	return 0;
}
```

下面来说说为什么暴力可过

因为多边形的所有坐标都是整点，所以对称轴的数量不会太多

如果某个位置不是对称轴的话，通常枚举不了几次就可以找到不对称的点对

（如果所有点都均匀分布在一条直线上（然而题目中并没有这种情况），判断对称轴时枚举次数会比较多，这时需要随机打乱枚举顺序）

所以说 n^2 的暴力实际上跑得飞快

~~不过坐标是实数的话暴力就不好用了~~

---

## 作者：xtx1092515503 (赞：4)

Manacher做法。

------------

考虑一个多边形的对称轴有什么性质——

明显，如果沿着对称轴的一端把整个环状的多边形裁成一条链，则链上相邻两条边的夹角，必定是回文的。

回文就直接上Manacher啦。

我们把整个多边形断环成链复制三份，然后对着复制完的多边形的所有夹角构成的串跑一遍Manacher。假如发现里面出现了一条长度 $\geq n$ 的回文串，就意味着出现了一条对称轴。

注意，因为对称轴会在其与多边形的两个交点处被计算两遍，故最终答案应除以 $2$。

具体实现时，可以使用叉积判夹角相同，但实际上使用 ```atan2``` 暴力算夹角然后用 ```double``` 判相同也够用了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
const double pi=acos(-1);
const double eps=1e-10;
struct Vector{
	double x,y;
	Vector(double X=0,double Y=0){x=X,y=Y;}
	friend Vector operator +(const Vector &u,const Vector &v){return Vector(u.x+v.x,u.y+v.y);}
	friend Vector operator -(const Vector &u,const Vector &v){return Vector(u.x-v.x,u.y-v.y);}
	friend Vector operator *(const Vector &u,const double &v){return Vector(u.x*v,u.y*v);}
	friend Vector operator /(const Vector &u,const double &v){return Vector(u.x/v,u.y/v);}
	friend double operator &(const Vector &u,const Vector &v){return u.x*v.y-u.y*v.x;}//cross times
	friend double operator |(const Vector &u,const Vector &v){return u.x*v.x+u.y*v.y;}//point times
	double operator ~()const{return sqrt(x*x+y*y);}//the modulo of a vector
	double operator !()const{return atan2(y,x);}//the angle of a vector
	void read(){scanf("%lf%lf",&x,&y);}
}p[300100];
int m;
double ang[600100];
int Centre,Rpos,rad[600100];
double FMOD(double ip){
	if(ip<0)ip+=2*pi;
	if(ip>=2*pi)ip-=2*pi;
	return ip;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n),m=0;
		for(int i=1;i<=n;i++)p[i].read(),p[n+i]=p[2*n+i]=p[i];
		p[0]=p[n],p[3*n+1]=p[1];
		ang[++m]=-1;
		for(int i=1;i<=3*n;i++){
			ang[++m]=FMOD(!(p[i+1]-p[i])-!(p[i]-p[i-1]));
			ang[++m]=-1;
		}
		Centre=Rpos=0;
		for(int i=1;i<=m;i++){
			rad[i]=(i<Rpos)?min(Rpos-i,rad[Centre*2-i]):1;
			while(i+rad[i]<=m&&i-rad[i]>=1)if(fabs(ang[i+rad[i]]-ang[i-rad[i]])<eps)rad[i]++;else break;
			if(i+rad[i]>Rpos)Rpos=i+rad[i],Centre=i;
		}
		int res=0;
		for(int i=2*n+1;i<=4*n;i++)res+=(rad[i]>=n);
		printf("%d\n",res>>1);
	}
	return 0;
} 
```

---

## 作者：jijidawang (赞：3)

$n^2$ 过百万，暴力碾标算？

思路主要来自 WintersRain & pythoner713 .

***

首先顺时针 / 逆时针转一圈记录角度和边长，然后把序列连成一个环，问题就变成有多少个断点可以使得断开后的串是回文串（观察对称轴之定义）.

这个直接 $O(n^2)$ 暴力，跑得比 Hash 还快 .

避免浮点误差可以角度 -> 叉积，边长直接平方 .

```cpp
// 和源代码有出入（暴戾语言被和谐为 123，注意这个过不了编译）
#include <bits/stdc++.h>
template<typename T>
inline T chkmin(T& x, const T& y){if (x > y) x = y; return x;}
template<typename T>
inline T chkmax(T& x, const T& y){if (x < y) x = y; return x;}
template<typename T>
inline T sqr(const T& x){return x * x;}
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
const int N = 5e5+5;
int n;
pii a[N];
int _[N];
inline void fstmod_(int& x, const int& P){if (x > P) x -= P;}
int cross(const pii& A, const pii& B){return A.first * B.second - A.second * B.first;}
int dot(const pii& A, const pii& B){return A.first * B.first + A.second * B.second;}
pii 123(const pii& A, const pii& B){return make_pair(A.first - B.first, A.second - B.second);}
inline void solve()
{
	scanf("%d", &n);
	for (int i=1; i<=n; i++) scanf("%d%d", &a[i].first, &a[i].second);
	for (int i=1; i<=n; i++)
	{
		int p=i, q=i+1, r=i+2; fstmod_(q, n); fstmod_(r, n);
		_[(i<<1)-1] = dot(123(a[p], a[q]), 123(a[p], a[q])); _[i<<1] = cross(123(a[p], a[q]), 123(a[q], a[r]));
	}
	n <<= 1;
	for (int i=1; i<=n; i++) _[i+n] = _[i];
	int ans = n;
	for (int i=1; i<=n; i++)
		for (int j=i; j<=i+n; j++)
			if (_[j] != _[i+n+1-j]){--ans; break;}
	printf("%d\n", ans);
}
int main()
{
	int T; scanf("%d", &T);
	while (T--) solve();
	return 0;
}
```

---

## 作者：Butterfly_qwq (赞：1)

这题大部分题解要不是错误的（见[这里](https://www.luogu.com.cn/discuss/1007106)），要不是暴力。所以这篇题解可能是目前唯一复杂度和正确性都有保证的一篇题解。

考虑对于每一个边角信息都交替记录下来，串成一个环。考虑如果一个地方是对称轴的话，那么从这里断开环，剩下的那一条链一定是回文的。

首先断环为链（即倍长原串），然后枚举 $1\le i\le2n$，判断有几个 $i$ 使得 $[i,i+2n]$ 是为回文即可。这个可以使用 manacher 算法，但是我实现的是哈希做法。

至此，此题得解……吗？

还有被我们忽略掉的一个问题：

如果用上面的方法，浮点数精度太烂并且几乎没法取模。

边长是好处理的，可以直接平方，但是角度怎么办？

考虑 $\theta_1=\theta_2\leftrightarrow \sin\theta_1=\sin\theta_2\wedge\cos\theta_1=\cos\theta_2$，于是就直接存 $\sin$ 和 $\cos$ 就行了。

但是 $\sin$ 和 $\cos$ 仍然是有理数，所以我们使用一个维护点乘和叉乘模长的 `pair<int,int>` 就行了。

还有一个问题就是如果用上面的方法，边长值域达到了 $10^{16}$，而角度值域达到了惊人的 $10^{32}$，普通哈希 fst 掉的概率很大。

但是你发现不同的边角其实最多有 $10^5$ 种，于是跑个离散化就行了。

时间复杂度 $O(Tn\log n)$ 或 $O(Tn)$，由于前者已经足够通过，所以我实现了前者。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100005,bas=100019,mod=399985681,inv=283659948;
int T,n,cnta,cntb,ans,x[N],y[N],X[N],Y[N],a[N],t[N<<2],pw[N<<2],iv[N<<2],hs1[N<<2],hs2[N<<2];
pair<int,int>b[N],o[N];
int geths1(int l,int r){return ((hs1[r]-hs1[l-1])*iv[l  -1]%mod+mod)%mod;}
int geths2(int l,int r){return ((hs2[l]-hs2[r+1])*iv[n*4-r]%mod+mod)%mod;}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>T;
	pw[0]=iv[0]=1;
	for(int i=1;i<400005;i++)
	{
		pw[i]=pw[i-1]*bas%mod;
		iv[i]=iv[i-1]*inv%mod;
	}
	while(T--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)cin>>x[i]>>y[i];
		for(int i=1;i<=n;i++)
		{
			X[i]=x[i%n+1]-x[i];
			Y[i]=y[i%n+1]-y[i];
			t[i*2-1]=a[i]=X[i]*X[i]+Y[i]*Y[i];
		}
		for(int i=1,p,q;i<=n;i++)
		{
			p=X[i]*Y[i%n+1]-X[i%n+1]*Y[i];
			q=X[i]*X[i%n+1]+Y[i]*Y[i%n+1];
			o[i]=b[i]=make_pair(p,q);
		}
		sort(a+1,a+n+1);cnta=unique(a+1,a+n+1)-a-1;
		sort(b+1,b+n+1);cntb=unique(b+1,b+n+1)-b-1;
		for(int i=1;i<=n;i++)
		{
			t[i*2-1]=lower_bound(a+1,a+cnta+1,t[i*2-1])-a;
			t[i*2  ]=lower_bound(b+1,b+cntb+1,o[i    ])-b;
		}
		for(int i=n*2+1;i<=n*4;i++)t[i]=t[i-2*n];
		for(int i=1;i<=n*4;i++)hs1[i]=(hs1[i-1]+t[i]*pw[i-1  ]%mod)%mod;
		for(int i=n*4;i>=1;i--)hs2[i]=(hs2[i+1]+t[i]*pw[n*4-i]%mod)%mod;
		ans=0;
		for(int i=1;i<=n*2;i++)if(geths1(i,i+n*2)==geths2(i,i+n*2))ans++;
		cout<<ans/2<<'\n';
	}
}
```

---

## 作者：lzh0220 (赞：0)

## 题意

给你一个多边形，问你这个多边形有几条对称轴。

## 思路

考虑轴对称的图形有什么共性。

随意画一个轴对称图形，将它的一条对称轴画出，观察两边翻折后完全一样，这非常像一个回文序列的形式。

于是有了一个比较基础的思路：将每条边的长度和每个角的角度求出来，组成一个长度为 $2n$ 的环，在环上操作。

考虑将环变成链，那我们就可以在这个链上使用 manacher 求出每个位置的最长回文串长度。如果这个长度大于等于 $n$，那么就说明该位置有一条对称轴。

最后答案由于会被统计两遍，因此要除以 $2$。

时间复杂度 $O(n)$。

## code

```cpp
signed main(){
	int t;cin>>t;
	while(t--){
		int n;cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y;
		for(int i=1;i<=n-1;i++)lst[i]=a[i+1]-a[i];
		lst[n]=a[1]-a[n];
        for(int i=1;i<=n;i++)a[i]=lst[i];
		for(int i=1;i<=n-1;i++){
			lst[i*2-1]=Dot{length(a[i]),0};
			lst[i*2]=Dot{dot(a[i],a[i+1])/length(a[i])/length(a[i+1]),cross(a[i],a[i+1])/length(a[i])/length(a[i+1])};
		}
		lst[n*2-1]=Dot{length(a[n]),0};
		lst[n*2]=Dot{dot(a[n],a[1])/length(a[n])/length(a[1]),cross(a[n],a[1])/length(a[n])/length(a[1])};
		for(int i=1;i<=n*2;i++)lst[i+n*2]=lst[i];
		memset(ans,0,sizeof(ans));manacher(4*n);
		int tot=0;
		for(int i=n+1;i<=3*n;i++)if(ans[i]>=n)tot++;
        cout<<tot/2<<endl;
	}
}
```

---

