# The Supersonic Rocket

## 题目描述

战争结束后，超音速火箭成为了最常见的公共交通工具。

每个超音速火箭由两个“引擎”组成。每个引擎是一组“能量源”。第一个引擎有 $n$ 个能量源，第二个引擎有 $m$ 个能量源。每个能量源可以表示为二维平面上的一个点 $(x_i, y_i)$。每个引擎内的所有点都不相同。

你可以分别对每个引擎进行操作。每个引擎可以进行以下两种操作，每种操作可以执行任意多次。

1. 对该引擎的所有能量源整体平移：$(x_i, y_i)$ 变为 $(x_i+a, y_i+b)$，其中 $a$ 和 $b$ 可以是任意实数。也就是说，所有能量源会整体平移。
2. 对该引擎的所有能量源整体旋转：$(x_i, y_i)$ 变为 $(x_i \cos \theta - y_i \sin \theta, x_i \sin \theta + y_i \cos \theta)$，其中 $\theta$ 可以是任意实数。也就是说，所有能量源会整体旋转。

引擎的工作方式如下：当两个引擎启动后，它们的能量源会合并（此时不同引擎的能量源可能重合）。如果存在两个能量源 $A(x_a, y_a)$ 和 $B(x_b, y_b)$，那么对于所有满足 $0 < k < 1$ 的实数 $k$，会生成一个新的能量源 $C_k(kx_a + (1-k)x_b, ky_a + (1-k)y_b)$。然后，使用所有新旧能量源重复这一过程。最终，会生成所有能量源形成的“能量场”（可以看作是所有出现过的能量源的无限集合）。

如果经过你对引擎的操作后，任意删除一个能量源并再次启动引擎，所生成的能量场与未删除任何能量源时相同，则称该超音速火箭是“安全”的。只有当两个能量场中的任意一个能量源都属于另一个能量场时，才认为两个能量场相同。

给定一个超音速火箭，判断它是否安全。

## 说明/提示

第一个样例：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017E/1f54366cb2efd6f1fd1d0617b722b5e3979dfd89.png) 图中靠近的蓝色和橙色点实际上是重合的。首先，对第一个引擎进行操作：使用第二种操作，取 $\theta = \pi$（即将所有能量源旋转 $180$ 度）。

第一个引擎的能量源变为 $(0, 0)$、$(0, -2)$ 和 $(-2, 0)$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017E/d9732486b953667a46772450be0d244f2cb20626.png) 然后，对第二个引擎进行操作：使用第一种操作，取 $a = b = -2$。

第二个引擎的能量源变为 $(-2, 0)$、$(0, 0)$、$(0, -2)$ 和 $(-1, -1)$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017E/f5d3a1ffc842f837240530d5f9c0ef57b3d408b7.png) 你可以验证，无论删除哪一个点，由两个引擎形成的能量场始终是由 $(0, 0)$、$(-2, 0)$、$(0, -2)$ 组成的实心三角形。

在第二个样例中，无论如何操作引擎，总存在第二个引擎中的某个能量源，使得删除它后能量场会缩小。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 4
0 0
0 2
2 0
0 2
2 2
2 0
1 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3 4
0 0
0 2
2 0
0 2
2 2
2 0
0 0
```

### 输出

```
NO
```

# 题解

## 作者：cjlak1o1 (赞：9)

我们可以看到楼上已经提供了一个非常巨的算法，在这里，本蒟蒻代一位大佬讲述另一种方法。  

本题所需算法:

- [二维凸包(Andrew or Graham)](https://www.luogu.com.cn/problem/P2742)  

- [kmp](https://www.luogu.com.cn/problem/P3375)

### 思路

我们维护凸包的各个边的长度进行比对，但由于我们都知道，只有边是不能证明全等的，那我们需要添加条件。第一种可以像楼上讲的一样，**加角**，当然也可以像蒟蒻一样**加一些边**。我们将凸包压成一个串，每次给串添三条边的长度，分别为凸包上已有的两条边，以及新连一条边连接两条已有边的非公共端点，三条边可以构成一个三角形，由于**三角形的稳定性**(边边边证全等)，所以如果相等只有一种情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/e84vjhua.png)

如图，例如从 $4$ 号点开始，我们逐次压入 $\text{dcC,cbB,baA,aeE,edD}$。

寻找凸包时如果您用 P2742 第一篇题解 Andrew 代码的做法的话，可能会有问题，~~别问我为什么~~。

当我们压成两个串后，只需将其中一条扩成两倍，kmp 寻找另一个串是否出现即可。

对了，翻译可能有一点问题，不只有凸多边形，可能还有直线，~~别问我为什么~~。

时间复杂度应该在 $O(n\log n)$。
```cpp
#include<bits/stdc++.h>
#define int long long 
#define Debug if(true)
#define db long double
#define F(x) (x)*(x)
using namespace std;
//typedef unsigned long long ull;
const int N=1e6+1e3;

int read(){
	int res=0,f=1;char c;
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) res=(res<<1)+(res<<3)+(c^48);
	return res*f;
}

struct vec{
	db x,y;
	bool operator < (const vec a){
		if(x!=a.x) return x<a.x;
		return y>a.y;
	}
	vec(){}
	vec(int _x,int _y){x=_x,y=_y;}
}st[N],p[N];

int top;

db cross(vec A,vec B){return A.x*B.y-A.y*B.x;}

db check(vec a,vec b,vec c)
{
	vec A=vec(b.x-a.x,b.y-a.y);
	vec B=vec(c.x-a.x,c.y-a.y);
	return cross(A,B);
}

void Andrew(int n)
{
	sort(p+1,p+n+1);
	/*Debug{
		cout<<endl<<"*********************"<<endl;
		for(int i=1;i<=n;i++) cout<<p[i].x<<" "<<p[i].y<<endl;
		cout<<"*****************"<<endl; 
	}*/
	st[1]=p[1],top=1;
	for(int i=2;i<=n;i++)
	{
		while(top>=2&&check(st[top-1],st[top],p[i])<=0) top--;
		st[++top]=p[i];
	}
	int tt=top;
	for(int i=n-1;i>=1;i--)
	{
		while(top>=tt+1&&check(st[top-1],st[top],p[i])<=0) top--;
		st[++top]=p[i];
	}
	st[++top]=st[2];
	//if(top==5) top-=2;
	/*Debug cout<<endl<<"/"<<endl;
	Debug for(int i=1;i<=top;i++) cout<<st[i].x<<" j "<<st[i].y<<endl;
	Debug cout<<endl;*/
}

int cnt1,cnt2;
db a[N],b[N];

db _dis(vec a,vec b){return sqrt(F(a.x-b.x)+F(a.y-b.y));}

void build1(int n)
{
	for(int i=3;i<=n;i++)
	{
		a[cnt1++]=_dis(st[i-1],st[i-2]);
		a[cnt1++]=_dis(st[i],st[i-1]);
		a[cnt1++]=_dis(st[i],st[i-2]);
	}
}

void build2(int n)
{
	for(int i=3;i<=n;i++)
	{
		b[cnt2++]=_dis(st[i-1],st[i-2]);
		b[cnt2++]=_dis(st[i],st[i-1]);
		b[cnt2++]=_dis(st[i],st[i-2]);
	}
}

int pi[N];

bool comp(db a[],db b[])
{
	for(int i=0;i<cnt1;i++) a[i+cnt1]=a[i];
	for(int i=1;i<cnt2;i++)
	{
		int j=pi[i-1];
		while(j>0&&b[i]!=b[j]) j=pi[j-1];
		if(b[i]==b[j]) j++;
		pi[i]=j; 
	}
	int j=0;
	for(int i=0;i<cnt1*2;i++)
	{
		while(j>0&&a[i]!=b[j]) j=pi[j-1];
		if(a[i]==b[j]) j++;
		if(j==cnt2) return true;
	}
	return false;
}

int n,m;
db ans1,ans2;

signed main(){
    n=read();m=read();
    //first
    for(int i=1;i<=n;i++) p[i].x=read(),p[i].y=read();
	Andrew(n);
	if(top==4) ans1=_dis(st[1],st[2]);
	build1(top);
	//second
	for(int i=1;i<=m;i++) p[i].x=read(),p[i].y=read();
	Andrew(m);
	if(top==4) ans2=_dis(st[1],st[2]);
	int tot2=top;
	build2(top);
	if(cnt1!=cnt2){
		printf("NO\n");
		return 0;
	}
	if(ans1!=0||ans2!=0) 
	{
		//cout<<ans1<<" "<<ans2<<endl;
		if(ans1==ans2) printf("YES\n");
		else printf("NO\n");
		return 0;
	}
	if(comp(a,b)) printf("YES\n");
	else printf("NO\n");
	return 0;
}
/*
8 9
4965 24651225
0 0
0 36000000
5004 25040016
4354 30107169
1309 30107169
2301 30107169
5487 30107169
30107169 513
30107169 2849
30107169 998
25040016 996
30107169 2249
30107169 1567
36000000 6000
0 6000
24651225 1035
*/
/*
YES
*/
```

---

## 作者：KKarshilov (赞：2)

中规中矩的做法，题目要求的是给出两个点集，求出它们的凸包并判断是否旋转同构

举个例子：

(0, 0) (1, 0) (0, 1)

(1, 0) (1, 1) (0, 1)

这就是一组旋转同构

并没有参加比赛，但是hyc在群里提了这道题，让我们思考

求解凸包直接使用基于水平序的Andrew算法，具体做法请参考[凸包模板](https://www.luogu.org/problemnew/show/P2742)

我一看，旋转同构？如果能找到对应点，拆开成一条链多好判啊

当然，我并不知道怎么找对应点，如果有巨佬会请告诉我

然后我就从这个思路想到了某个很像的东西

最小循环同构！或者说最小表示法

但是和这题还是没什么关系，不过由这个点我们就可以想到很多东西：旋转同构转循环同构

字符串的循环同构本身就是将字符串首位相接成环，从不同的地方断开就是不同的字符串，如此得到的的字符串都是循环同构的

那么怎样将这个东西用在凸包上，或者多边形上呢？

我们要保证凸包的信息不变且可以识别，并且和字符串具有某些共性以便于以后的操作

凸包的信息集中在点上，对于每个点，它同时属于两条边和一个角

所以将凸包拆分成边-角-边-角-边……的形式，边用长度表示，角用弧度表示，就是一个数列了，比如:(1, 0) (0, 1) (0, 0)

数列形式: 1.41421--Pi/4--1--Pi/2--1--Pi/4

然后我们的问题就变成了判断两个数列循环同构

将其中一个复制一倍接在尾部，用另一个数列去匹配，采用KMP算法即可解决

```cpp
#include <bits/stdc++.h>
#define eps 1e-8
#define delta 0.98
#define Get(a, b) atan2(a, b)
using namespace std;

const int MAXN = 100100;

struct Point {
    double x, y;
    Point () {}
    Point (double _x, double _y) : x(_x), y(_y) {}
};

typedef Point Vector;
typedef Point Polygon[MAXN];

template <typename T> inline void read(T &x) {
    int c = getchar();
    bool f = false;
    for (x = 0; !isdigit(c); c = getchar()) {
        if (c == '-') {
            f = true;
        }
    }
    for (; isdigit(c); c = getchar()) {
        x = x * 10 + c - '0';
    }
    if (f) {
        x = -x;
    }
}

Vector read_Vector() {
    double x, y;
    scanf("%lf%lf", &x, &y);
    return Vector(x, y);
} 

int dcmp(double x) {if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;}

Vector operator + (Vector A, Vector B) {return Vector(A.x + B.x, A.y + B.y);}

Vector operator - (Vector A, Vector B) {return Vector(A.x - B.x, A.y - B.y);}

Vector operator * (Vector A, double B) {return Vector(A.x * B, A.y * B);}

Vector operator / (Vector A, double B) {return Vector(A.x / B, A.y / B);}

bool operator == (const Vector&a, const Vector&b) {return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;}

double Dot(Vector A, Vector B) {return A.x * B.x + A.y * B.y;}

double Length(Vector A) {return sqrt(A.x * A. x + A. y * A.y);}

double Angle(Vector A, Vector B) {return acos(Dot(A, B) / Length(A) / Length(B));}

double Cross(Vector A, Vector B) {return A.x * B.y - A.y * B.x;}

double GetS(Vector A, Vector B, Vector C) {return Cross(B - A, C - A);}

bool operator < (Point a, Point b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

int ConvexHull(Point * p, int N, Point * ch) {
    sort(p, p + N);
    int sum = 0;
    for(int i = 0; i < N; i++) {
        while(sum > 1 && dcmp(Cross(ch[sum - 1] - ch[sum - 2], p[i] - ch[sum - 2])) >= 0) sum--;
        ch[sum++] = p[i];
    }
    int k = sum;
    for(int i = N - 2; i >= 0; i--) {
        while(sum > k && dcmp(Cross(ch[sum - 1] - ch[sum - 2], p[i] - ch[sum - 2])) >= 0) sum--;
        ch[sum++] = p[i];
    }
    if(N > 1) sum--;
    return sum;
}

bool chdb (double a, double b) {
    return fabs(a - b) <= eps;
}

int nxt[MAXN << 1];

bool KmpSearch(double * s, double * p, int sLen, int pLen) {  
    int i = 0;  
    int j = 0;    
    while(i < sLen && j < pLen) {  
        if(!chdb(s[i], p[j])) {
            if(j == 0) i++;			
            j = nxt[j];
        }		  
        while(j < pLen && chdb(s[i], p[j])) i++, j++;
        if (j == pLen) return 1;
    }  
    return 0;      
}  

void GetNext(double * p, int Nxt[], int pLen) {  
    Nxt[0] = -1;
    Nxt[1] = 0;  
    int j = 0, i = 1;
    for(i = 1; i < pLen; i++) {  
        while(j > 0 && !chdb(p[i], p[j])) j = Nxt[j];  
        if(chdb(p[i], p[j])) j++;  
        Nxt[i + 1] = j;
    }
}  

int n, m;
Polygon p1, p2, c1, c2;
int sum1, sum2, cnts, cntt;
double S[MAXN << 2], T[MAXN << 1];

void print(double * s, int len) {
    for(int i = 0; i < len; i++) {
        printf("%.2lf%c", s[i], i == len - 1 ? '\n' : ' ');
    }
}

signed main() {
    read(n), read(m);
    for(int i = 0; i < n; i++) p1[i] = read_Vector();
    for(int i = 0; i < m; i++) p2[i] = read_Vector();
    sum1 = ConvexHull(p1, n, c1);
    sum2 = ConvexHull(p2, m, c2);
    if(sum1 != sum2) {
        puts("NO");
        return 0;
    }
    c1[sum1] = c1[0]; c1[sum1 + 1] = c1[1];
    c2[sum2] = c2[0]; c2[sum2 + 1] = c2[1];
    for(int i = 0; i < sum1; i++) {
        S[cnts++] = Length(c1[i + 1] - c1[i]);
        S[cnts++] = Angle(c1[i + 2] - c1[i + 1], 
                    c1[i + 1] - c1[i]);
    }
    for(int i = 0; i < sum2; i++) {
        T[cntt++] = Length(c2[i + 1] - c2[i]);
        T[cntt++] = Angle(c2[i + 2] - c2[i + 1], 
                    c2[i + 1] - c2[i]);
    }
    for(int i = cnts; i < cnts * 2 - 1; i++) S[i] = S[i - cnts];
    GetNext(T, nxt, cntt);
    if(KmpSearch(S, T, cnts * 2 - 2, cntt - 1)) puts("YES");
    else puts("NO");
    return 0;
} 
```

---

## 作者：Nelofus (赞：1)

其实就是问两个凸包是不是同一个形状。

那么我们枚举第一个凸包的每一个点当做起点，逆时针哈希一圈，判断值是不是和第二个凸包相同即可。

因为题目里面给的所有点都是整点所以可以全部用整数。

随便用一个可以把面积/线段长度和角度的信息都带上的哈希函数即可，注意这里对顺序有要求，要类似字符串哈希的进制哈希，而且要特判掉凸包点数 $=2$ 的情况。

我这里的哈希函数是，假设 $\overrightarrow v_1$ 和 $\overrightarrow v_2$ 分别是到点 $x$ 逆时针上一个点和下一个点的向量，上一个点记为 $y$，则：
$$
h(x)=h(y)\times base+(\overrightarrow v_1\cdot \overrightarrow v_2)\times |\overrightarrow v_1|^2
$$

```cpp
#include <bits/stdc++.h>
using i64 = long long;
using Hash = std::pair<i64, i64>;
std::random_device seed;
std::mt19937_64 rng(seed());

constexpr double eps = 1e-15;
constexpr int N = 1e5 + 10;
constexpr int mod = 469762049;

inline i64 Plus(i64 a, i64 b) {
	return a + b >= mod ? a + b - mod : a + b;
}
inline i64 Minu(i64 a, i64 b) {
	return a - b < 0 ? a - b + mod : a - b;
}

/* Hashing */
Hash operator * (const Hash &a, const Hash &b) {
	return std::make_pair(a.first * b.first % mod, a.second * b.second % mod);
}
Hash operator + (const Hash &a, const Hash &b) {
	return std::make_pair(Plus(a.first, b.first), Plus(a.second, b.second));
}
Hash operator - (const Hash &a, const Hash &b) {
	return std::make_pair(Minu(a.first, b.first), Minu(a.second, b.second));
}

i64 reg(i64 a) {
	return (a % mod + mod) % mod;
}

inline i64 f_pow(i64 a, i64 k) {
	i64 base = 1;
	for (; k; k >>= 1, a = a * a % mod)
		if (k & 1)
			base = base * a % mod;
	return base;
}

struct Point {
	i64 x, y;
	Point() { }
	Point(i64 nx, i64 ny) : x(nx), y(ny) { }
};

using Vector = Point;
Vector operator + (const Vector &a, const Vector &b) {return Vector(a.x + b.x, a.y + b.y);}
Vector operator - (const Vector &a, const Vector &b) {return Vector(a.x - b.x, a.y - b.y);}
Vector operator * (const Vector &a, const int &x) {return Vector(a.x * x, a.x * x);}

i64 Cross(const Vector &A, const Vector &B) {return 1ll * A.x * B.y - 1ll * B.x * A.y;}
i64 Dot(const Vector &A, const Vector &B) {return A.x * B.x + A.y * B.y;}
Vector ft(const Point &A, const Point &B) {return B - A;}

double Length(const Vector &A) {return sqrt(Dot(A, A));}

int n, m;

std::vector<Point> ConvexHull(std::vector<Point> s) {
	auto cmp = [](const Point &a, const Point &b) {
		return a.x == b.x ? a.y < b.y : a.x < b.x;
	};
	std::sort(s.begin(), s.end(), cmp);

	static std::array<Point, N> stk;
	static int tt = 0;
	for (int i = 0; i < s.size(); i++) {
		while (tt > 1 && Cross(ft(stk[tt - 2], stk[tt - 1]), ft(stk[tt - 2], s[i])) <= 0)
			tt--;
		stk[tt++] = s[i];
	}
	int tt2 = tt;
	for (int i = s.size() - 2; i >= 0; i--) {
		while (tt2 > tt && Cross(ft(stk[tt2 - 2], stk[tt2 - 1]), ft(stk[tt2 - 2], s[i])) <= 0)
			tt2--;
		stk[tt2++] = s[i];
	}
	std::vector<Point> vec(tt2);
	for (int i = 0; i < tt2; i++) {
		vec[i] = stk[i];
	}
	tt = 0;
	return vec;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	std::vector<Point> P1(n), P2(m);
	for (auto &[x, y] : P1)
		std::cin >> x >> y;
	for (auto &[x, y] : P2)
		std::cin >> x >> y;

	auto Conv1 = ConvexHull(P1);
	auto Conv2 = ConvexHull(P2);
	
	// 只有两个点
	if (Conv1.size() == Conv2.size() && Conv1.size() == 3) {
		if (fabs(Length(ft(Conv1[0], Conv1[1])) - Length(ft(Conv2[0], Conv2[1]))) <= eps)
			std::cout << "YES\n";
		else
			std::cout << "NO\n";
		return 0;
	}

	int t = Conv1.size() - 1;
	std::vector<Hash> hs(Conv1.size() * 2 - 1);
	Conv1.resize(Conv1.size() * 2 - 1);

	for (int i = t; i < (int)Conv1.size(); i++)
		Conv1[i] = Conv1[i - t];

	Hash base;
	base.first = rng() % 150 + 10;
	base.second = rng() % 150 + 10;
//	std::cerr << '\n' << base.first << ' ' << base.second << '\n';
	Hash ans = std::make_pair(0ll, 0ll);
	for (int i = 1; i < Conv2.size() - 1; i++) {
		auto v1 = ft(Conv2[i], Conv2[i - 1]), v2 = ft(Conv2[i], Conv2[i + 1]);
		i64 val = reg(Dot(v1, v1)) * reg(Dot(v1, v2)) % mod;
		ans = ans * base + std::make_pair(val, val);
	}

	bool flag = false;
	// 其实只有总数 - 1 个角
	Hash basek = std::make_pair(f_pow(base.first, t - 1), f_pow(base.second, t - 1));
	for (int i = 1; i < Conv1.size() - 1; i++) {
		auto v1 = ft(Conv1[i], Conv1[i - 1]), v2 = ft(Conv1[i], Conv1[i + 1]);
		i64 val = reg(Dot(v1, v1)) * reg(Dot(v1, v2)) % mod;
		hs[i] = hs[i - 1] * base + std::make_pair(val, val);
		if (i >= t) {
			auto tmp = hs[i] - (hs[i - (t - 1)] * basek);
			if (tmp == ans) {
				flag = true;
				break;
			}
		}
	}
	if (flag)
		std::cout << "YES" << '\n';
	else
		std::cout << "NO" << '\n';
	return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
垃圾题，考虑用垃圾做法过。

广告：[『从入门到入土』串串学习笔记](https://www.luogu.com.cn/article/dv6dig1o)。
## 思路分析
判断两个图形是否同构？

直接二维凸包给他包一圈。

这里直接用 Andrew 就行了。

然后把图形拍成序列。

拍成序列的方法考虑线直接用长度表示，图形的形状，也就是角度则考虑用向量的点积/叉积替代即可。

接着判断是否出现直接给一个倍长，KMP 查询出现即可。

然后就挂了。

这个时候我们会发现角度要用 cos 来表示，也就是不能使用叉积。

所以我们直接换成点积用 `acos` 判断。

然后就被 nan 大神创死了。

因为角度有关的没加 eps 所以会直接搞出来 nan。

这个时候特判 nan 就能过了。

eps 随便取，卡这个太没意思了。
## 代码

```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=8e5+10,V=4e5+10,M=21,INF=1e18,p=13331,mod=1004535809;
const double eps=1;
int n,m,la,lb,l,ll,nxt[N];double s[N],t[N];pair<int,int> a[N],b[N],sa[N],sb[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline pair<int,int> add(pair<int,int> a,pair<int,int> b){return {a.first+b.first,a.second+b.second};}
inline int cross(pair<int,int> a,pair<int,int> b){return a.first*b.second-a.second*b.first;}
inline int slope(pair<int,int> a,pair<int,int> b,pair<int,int> c){return cross({b.first-a.first,b.second-a.second},{c.first-a.first,c.second-a.second});}
inline void get(pair<int,int> a[],pair<int,int> st[],int&t,int n)
{
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++)
    {
        while(t>1&&slope(st[t-1],st[t],a[i])<=0) t--;
        st[++t]=a[i];
    }int tt=t;
    for(int i=n-1;i>=1;i--)
    {
        while(t>tt&&slope(st[t-1],st[t],a[i])<=0) t--;
        st[++t]=a[i];
    }t--;
}
inline int dot(pair<int,int> a,pair<int,int> b){return a.first*b.first+a.second*b.second;}
inline double len(pair<int,int> a){return sqrt(a.first*a.first+a.second*a.second);}
inline double get(pair<int,int> a,pair<int,int> b)
{
	double x=dot(a,b)/len(a)/len(b);
	if(x!=cos(acos(x))) x=eps;
	return acos(x);
}
inline pair<int,int> del(pair<int,int> a,pair<int,int> b){return {a.first-b.first,a.second-b.second};}
inline void get(pair<int,int> a[],double s[],int n,int&m)
{
	for(int i=1;i<=n;i++)
	{
		int j=i+1,k=i+2;if(j>n) j-=n,k-=n;if(k>n) k-=n;
		s[++m]=(a[i].first-a[j].first)*(a[i].first-a[j].first)+(a[i].second-a[j].second)*(a[i].second-a[j].second);
		s[++m]=get(del(a[k],a[j]),del(a[j],a[i]));
	}
}
namespace KMP
{
	inline void kmp(double s[],int n,int nxt[])
	{
		for(int i=2,j=0;i<=n;i++)
		{
			while(j&&s[i]!=s[j+1]) j=nxt[j];
			if(s[i]==s[j+1]) j++;
			nxt[i]=j;
		}
	}
	inline int findstr(int n,int m,double s1[],double s2[],int nxt[])
	{
		int j=0,res=0;
		for(int i=1;i<=n;i++)
		{
			while(j&&s2[j+1]!=s1[i]) j=nxt[j];
			if(s2[j+1]==s1[i]) j++;
			if(j==m) res++,j=nxt[j];
		}return res;
	}
}
using namespace KMP;
inline void solve()
{
    n=read();m=read();
    for(int i=1;i<=n;i++) a[i].first=read(),a[i].second=read();
    for(int i=1;i<=m;i++) b[i].first=read(),b[i].second=read();
    get(a,sa,la,n);get(b,sb,lb,m);
    get(sa,s,la,l);get(sb,t,lb,ll);kmp(t,ll,nxt);
    for(int i=1;i<l;i++) s[i+l]=s[i];l<<=1;l--;
    put(findstr(l,ll,s,t,nxt)?"YES\n":"NO\n");
}
signed main()
{
    int T=1;
    // T=read();
    while(T--) solve();
    genshin:;flush();return 0;
}
```

---

