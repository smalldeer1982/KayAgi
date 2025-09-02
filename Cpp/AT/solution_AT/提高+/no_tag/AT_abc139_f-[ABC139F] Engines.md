# [ABC139F] Engines

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc139/tasks/abc139_f

E869120 君は最初、$ 2 $ 次元平面上の原点 $ (0,\ 0) $ に立っています。

彼は $ N $ 個のエンジンを持っています。エンジンの使い方と機能は以下のようになります。

- $ i $ 個目のエンジンを使うと、E869120 君のいる場所の X 座標が $ x_i $、Y 座標が $ y_i $ 変化する。つまり、E869120 君が座標 $ (X,\ Y) $ にいるときに $ i $ 個目のエンジンを使うと、座標 $ (X\ +\ x_i,\ Y\ +\ y_i) $ に移動する。
- エンジンはどのような順番で使ってもよいが、各エンジンは $ 1 $ 回までしか使えない。ただし、使わないエンジンがあってもよい。

彼は、原点から最も遠い場所に行きたいです。  
 最後に到達する地点の座標を $ (X,\ Y) $ として、原点からの距離 $ \sqrt{X^2\ +\ Y^2} $ の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ -1\ 000\ 000\ \leq\ x_i\ \leq\ 1\ 000\ 000 $
- $ -1\ 000\ 000\ \leq\ y_i\ \leq\ 1\ 000\ 000 $
- 入力はすべて整数

### Sample Explanation 1

うまくエンジンを使うと、最後に到達する地点の、原点からの距離を $ 10 $ にすることができます。 これには次の $ 3 $ 通りの方法があります。 - エンジン $ 1 $ を使って $ (0,\ 10) $ に移動する - エンジン $ 2 $ を使って $ (5,\ -5) $ に移動し、その後エンジン $ 3 $ を使って $ (0,\ -10) $ に移動する - エンジン $ 3 $ を使って $ (-5,\ -5) $ に移動し、その後エンジン $ 2 $ を使って $ (0,\ -10) $ に移動する 距離を $ 10 $ より大きくする方法はないので、最大値は $ 10 $ となります。

### Sample Explanation 2

最後に到達する地点の、原点からの距離の最大値は $ 2\ \sqrt{2}\ =\ 2.82842... $ となります。 これを達成する方法として、次のようなものが挙げられます。 - エンジン $ 1 $ を使って $ (1,\ 1) $ に移動し、その後エンジン $ 2 $ を使って $ (2,\ 1) $ に移動し、最後にエンジン $ 3 $ を使って $ (2,\ 2) $ に移動する

### Sample Explanation 3

エンジン $ 1\ \rightarrow\ 2\ \rightarrow\ 3\ \rightarrow\ 4\ \rightarrow\ 5 $ の順で全部使うと、最終的に $ (15,\ 15) $ にたどり着き、原点からの距離は $ 15\ \sqrt{2}\ =\ 21.2132... $ となります。

### Sample Explanation 4

$ (x_i,\ y_i)\ =\ (0,\ 0) $ である、何の意味も持たないエンジンがある可能性もあります。

### Sample Explanation 5

$ 1 $ 個しかエンジンがない場合もあることにご注意ください。

### Sample Explanation 6

$ 2 $ 個しかエンジンがない場合もあります。

## 样例 #1

### 输入

```
3
0 10
5 -5
-5 -5```

### 输出

```
10.000000000000000000000000000000000000000000000000```

## 样例 #2

### 输入

```
5
1 1
1 0
0 1
-1 0
0 -1```

### 输出

```
2.828427124746190097603377448419396157139343750753```

## 样例 #3

### 输入

```
5
1 1
2 2
3 3
4 4
5 5```

### 输出

```
21.213203435596425732025330863145471178545078130654```

## 样例 #4

### 输入

```
3
0 0
0 1
1 0```

### 输出

```
1.414213562373095048801688724209698078569671875376```

## 样例 #5

### 输入

```
1
90447 91000```

### 输出

```
128303.000000000000000000000000000000000000000000000000```

## 样例 #6

### 输入

```
2
96000 -72000
-72000 54000```

### 输出

```
120000.000000000000000000000000000000000000000000000000```

## 样例 #7

### 输入

```
10
1 2
3 4
5 6
7 8
9 10
11 12
13 14
15 16
17 18
19 20```

### 输出

```
148.660687473185055226120082139313966514489855137208```

# 题解

## 作者：wangyibo201026 (赞：3)

## 题目描述

给你 $n$ 个向量，要求选出一些向量，使得它们的和的模长最大，输出这个模长。

## 前置知识

- 向量的和：对于向量 $\overrightarrow a = (x_1, y_1)$，向量 $\overrightarrow b = (x_2, y_2)$，则称它们的和为向量 $\overrightarrow c = (x_1 + x_2, y_1 + y_2)$。

- 向量的模长：对于向量 $\overrightarrow a = (x, y)$，则称它的模长为 $\sqrt{x^2 + y^2}$。

- 极角排序：可以看成是斜率的大小关系，这个上网搜。

## 思路

我们先按照极角排序，就能发现，选连续的一段点一定是最优的，否则中间没有连起来的点肯定连起来不劣（更优）。

所以代码就很简单了，先排遍序，然后再 $O(n^2)$ 扫就行了。

## 代码：

这里只放部分代码：

```cpp
bool cmp2(Vector x, Vector y){
  return polar(x) < polar(y); // polar 为求极角函数
}

void Solve(){
  cin >> n;
  for(int i = 1; i <= n; i++){
    cin >> a[i].x >> a[i].y;;
  }
  sort(a + 1, a + 1 + n, cmp2); // 极角排序
  for(int i = 1; i <= n; i++){
    a[i + n].x = a[i].x, a[i + n].y = a[i].y; // 注意这里后面的和前面的连起来也是可以的
  }
  double maxi = -1e9;
  for(int i = 1; i <= n; i++){
    double sumx = 0, sumy = 0;
    for(int j = i; j < n + i; j++){ // 如果大于等于 n + i 那么长度就大于 n 了
      sumx += a[j].x;
      sumy += a[j].y;
      maxi = max(maxi, sqrt(sumx * sumx + sumy * sumy));
    }
  }
  cout << fixed << setprecision(10) << maxi;
}
```

---

## 作者：Lskkkno1 (赞：3)

- [AT4900 [ABC139F] Engines](https://www.luogu.com.cn/problem/AT4900)

### 题目描述

给定 $N$ 个向量，选出一些向量使得它们的和的模长最大。

### 正解

发现选出来的向量，在极角排序之后一定是一段连续的区间。

由于数据范围很小，我这里给出的是 $O(n^2)$ 做法，但其实还有更加优秀的 $O(n \log n)$，（复杂度瓶颈在排序上，找区间用 two-pointer ）。

$\color{DeepSkyBlue} Code :$

```cpp
#include <bits/stdc++.h>
#define N 105

using namespace std;

int n;

struct vec {
	long long x, y;
	vec (long long tx = 0, long long ty = 0) { x = tx, y = ty; }
	vec operator + (const vec &t) const { return vec(x + t.x, y + t.y); }
	vec operator - (const vec &t) const { return vec(x - t.x, y - t.y); }
	long long lenth() { return x * x + y * y; }
}a[2 * N];

bool cmp(const vec &lhs, const vec &rhs) {
	return atan2(lhs.y, lhs.x) < atan2(rhs.y, rhs.x);
}

inline int read() {
	int x = 0; bool neg = false; char ch = getchar();
	while(!isdigit(ch)) (ch == '-') && (neg = true), ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	return neg ? -x : x;
}

int main() {
	n = read();
	for(int i = 1; i <= n; ++i)
		a[i].x = read(), a[i].y = read();
	
	sort(a + 1, a + n + 1, cmp);
	
	for(int i = 1; i <= n; ++i)
		a[n + i] = a[i];
	
	vec cur;
	long long ans = 0;
	for(int l = 1; l <= n; ++l) {
		cur = vec(0, 0);
		for(int r = l; r < l + n; ++r) {
			cur = cur + a[r];
			ans = max(ans, cur.lenth());
		}
	}
	
	printf("%.10lf\n", sqrt(ans));
	return 0;
}
```


---

## 作者：CarroT1212 (赞：1)

### 解法分析

模拟赛上遇到这题，没整明白，赛后发现很离谱。

直接 DP 什么的是别想了，这个玩意很明显没什么可有效优化的地方。不如扒一点性质。

推几组比较大的样例试试，发现有一个很神奇的事情：将所有向量按极角排序后，答案达到最大时取的向量一定是连续的。

还挺好理解，如果我取了一堆向量然后中间空了一个，那我再取这个向量肯定能让我顺着其它向量加起来的方向更进一步。当然前提是这些向量覆盖的区域不能超过 $180\degree$，不过把那些超过的向量去掉显然能使答案更优，所以不用管。

所以这个 $O(N^3)$ 的数据范围是留给你枚举左右端点然后暴力计算向量和的！

### 代码

订的时候没想起来有 atan2 这个神奇东西于是手写了 cmp。

```cpp
ll gettyp(node x) {
    if (x.x==0&&x.y>=0) return 1;
    else if (x.x>0&&x.y>0) return 2;
    else if (x.x>0&&x.y==0) return 3;
    else if (x.x>0&&x.y<0) return 4;
    else if (x.x==0&&x.y<0) return 5;
    else if (x.x<0&&x.y<0) return 6;
    else if (x.x<0&&x.y==0) return 7;
    else if (x.x<0&&x.y>0) return 8; 
}
int main() {
    scanf("%lld",&n);
    for (ll i=1;i<=n;i++) scanf("%lld%lld",&a[i].x,&a[i].y);
    sort(a+1,a+n+1,[](node x,node y){
        if (gettyp(x)==gettyp(y)) return x.x*y.y<x.y*y.x;
        else return gettyp(x)<gettyp(y);
    });
    for (ll i=1;i<=n;i++) for (ll j=1;j<=n;j++) {
        ll x=0,y=0;
        for (ll k=i,l=0;k!=j||!l;k=k%n+1,l=1) x+=a[k].x,y+=a[k].y;
        ans=max(ans,x*x+y*y);
    }
    printf("%.15Lf",sqrt((ld)ans));
    return 0;
}
```

---

## 作者：_AyachiNene (赞：1)

# 前置知识：
[模拟退火](https://www.luogu.com.cn/problem/P1337)
# 思路：
这题 $n$ 比较小，且答案数量多，可以可以用模拟退火。直接随机打乱序列在计算价值，以一定概率接受新解。价值的计算可以~~乱搞~~。如果加上一个向量后答案更优就加上它。

**注意：题目要求保留 $10$ 位小数。**
# Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int x,y;
}a[114514];
int n;
int p[114514];
double f()           //计算价值 
{
	double lx=0,ly=0;
	for(int i=1;i<=n;i++)
	{
		double nx=lx+a[p[i]].x,ny=ly+a[p[i]].y;
		if(sqrt(nx*nx+ny*ny)>sqrt(lx*lx+ly*ly))
			lx=nx,ly=ny;
	}
	return sqrt(lx*lx+ly*ly);
}
double ans;
void sa()
{
	double t=3000;
	while(t>1e-15)
	{ 
		int nx=rand()%n+1,ny=rand()%n+1;        //随机打乱顺序 
		swap(p[ny],p[nx]); 
		double sum=f();
		if(sum<ans)
		{
			swap(p[nx],p[ny]);
			if(exp((ans-sum)/t)<(double(rand())/RAND_MAX))
				swap(p[nx],p[ny]);       //以一定概率接受新解 
		}
		else
			ans=sum;
		t*=0.995;      //降温 
	}
}
int main()
{
	cin>>n;
	srand(time(0));
	for(int i=1;i<=n;i++)           //构造序列 
		p[i]=i;
	double ax=0,ay=0;
	for(int i=1;i<=n;i++)
		cin>>a[i].x>>a[i].y,ax+=a[i].x,ay+=a[i].y;
	ans=sqrt(ax*ax+ay*ay);       //计算初始答案 
	for(int i=1;i<=10;i++)
		sa();               //退火 
	printf("%.12lf",ans);
}
```


---

## 作者：hh弟中弟 (赞：0)

极角排序后肯定选连续的一段，这个东西只满足决策单调性，不满足双指针，原因同决策单调性，比如后面有一个更优的，然后全崩了。\
注意到选的一定在一个平角内，因为加上与答案夹角小于 $\frac{\pi}{2}$ 的向量一定不劣，然后可以根据这个做双指针，有一个更聪明的做法，把反向量也加进去，然后先加入 $[\pi,2\pi]$ 的原向量，这样遇到一个向量就加上他的贡献，保证了每个平角都被统计到，时间复杂度 $\mathcal{O}(n\log n)$ 瓶颈是排序。\
[record](https://atcoder.jp/contests/abc139/submissions/61524163)

---

## 作者：AC_love (赞：0)

首先把所有向量按照和 $x$ 轴的夹角排序，不难发现最大的模长一定来自于连续的一段的向量的和。

为什么？感性理解：如果最大的一段是一段不连续的向量的和的话，那么把中间的向量也选上一定会更优。因此最大的一段一定是连续的。

直接枚举所有连续段，复杂度 $O(n^2)$。

不过有复杂度更优的做法。

不难注意到：添加向量的过程中，和向量的模长一定是先增大后减小的。这个东西具有单调性，可以用双指针来做，复杂度 $O(n)$，但需要注意总复杂度是 $O(n \log n)$ 的，瓶颈在于排序。

[code](https://atcoder.jp/contests/abc139/submissions/59086913)

---

## 作者：iamajcer (赞：0)

# 题目描述
给你 $n$ 个向量，选出一些出来，使得选出的向量的和的模长最大。

# 思路
本蒟蒻没用数学知识。~~绝对不是因为我不会。~~


注意到 $n$ 的范围比较小，可以考虑背包，但是由于向量的顺序不一样，会导致求出的答案出错。

但是 $n$ 的范围特别小，我们可以多次随机化，再对每一次随机化后的向量进行 dp，这样就可以求出答案了。

代码很简单，可以看代码理解。

# Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=105;

int n;
struct node
{
	int x, y, s;
}a[N];
double ans=0, f[N][N], g[N][N];
bool cmp(node a, node b)
{
	return a.s<b.s;
}
double get(int a, int b)
{
	return sqrt(a*a*1.0+b*b*1.0)*1.0;
}
double solve()
{
	double res=0;
	
	for (int i=1; i<=n; i++) a[i].s=rand();
	sort(a+1, a+1+n, cmp);
	
	for (int i=1; i<=n; i++)
	{
		for (int j=0; j<=i; j++)
		{
			f[i][j]=f[i-1][j];
			g[i][j]=g[i-1][j];
			if (j)
			{
				int t=f[i-1][j-1]+a[i].x, t2=g[i-1][j-1]+a[i].y;
				if (get(t, t2)>get(f[i][j], g[i][j])) f[i][j]=t, g[i][j]=t2;
			}
		}
	}
	
	for (int i=1; i<=n; i++) res=max(res, get(f[n][i], g[n][i]));
	
	return res;
}
signed main()
{
	srand(time(NULL));
	
    scanf("%lld", &n);
	for (int i=1; i<=n; i++) scanf("%lld%lld", &a[i].x, &a[i].y);
    
    for (int i=1; i<=5000; i++) ans=max(ans, solve());
    
    printf("%.11lf", ans);
    return 0;
}
```

---

## 作者：robinyqc (赞：0)

可以发现，将坐标系旋转后答案不变，考虑放到极坐标系上考虑。结果发现：答案是极坐标系上一段连续区间内向量之和。$O(n^3)$ 暴力做或 $O(n^2)$ 优化着做其实可以通过本题了。

这里给出一个比题解区更强的结论：将所有向量极角排序后，答案一定是 

$$
\max_{i\in \mathbb{R}}\left\{\left|\sum _{\arg(\boldsymbol v)\in [i, i + \pi)} {\boldsymbol{v}} \right|\right\}
$$ 

，也就是某个平角包含的所有向量和。证明很简单：选择一个与目标方向夹角不超过 $90\degree$ 的向量不劣。

其实也有一篇题解的代码或许用到了这个结论，但不知道为什么他并没有指出这个结论。

并不是所有平角我们都要计算。实际上，只需要某个给定向量为左端点就可以了。

一个笨办法是双指针，这样已经可以 $O(n\log n)$ 了，瓶颈在排序。

一个巧妙的解法是，把向量取反加入数组再排序。首先加入 $[0, \pi)$ 的所有原有向量。从 $x$ 轴负方向开始遍历。遍历时，若遇到原有向量，加入贡献；否则，从贡献中去除（先去除，再加入）。这样遍历到某个向量时，得到的就是它前面 $180\degree$（也就是顺时针 $180\degree$）的原向量之和。复杂度仍为 $O(n\log n)$ 瓶颈在排序。

```rust
use proconio::input;
use num::Complex;

fn main()
{
    input! {
        n: usize,
        v: [(i32, i32); n]
    }
    // 将数组转化为复数数组
    let v: Vec<_> = v.iter().map(|x| Complex::<f64>::new(x.0 as f64, x.1 as f64)).collect();
    let mut p = Vec::<(f64, usize)>::new();
    let mut vec_now = Complex::<f64>::new(0.0, 0.0);
    for (i, x) in v.iter().enumerate() {
        let arg = x.arg();
        p.push(((-x).arg(), i));
        p.push((arg, i + n));
        if arg >= 0.0 {
            vec_now += x;
        }
    }
    p.sort_by(|x, y| x.partial_cmp(y).unwrap());
    let mut ans = 0.0;
    for (_, pos) in p {
        if pos < n {
            vec_now -= v[pos];
        }
        else {
            vec_now += v[pos - n];
        }
        ans = f64::max(ans, vec_now.norm());
    }
    println!("{}", ans);
}
```

---

## 作者：Yashajin_Ai (赞：0)

### 思路
模拟退火，这道题十分简单，有模拟退火可以乱搞过掉，选随机生成一个不重复的序列，然后就算生成的序列是否对答案的贡献比之前的大，再算每一项的时候，就看一看是不是加上这一套装备比不加的位置与原点的欧几里得距离更远，是的话就加在答案上，模拟退火其实在这道题中不如随机化序列的效率高，且这道题所贡献答案的点，一定在同一个半个平面内。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
double x,y,ans=0,sum,xx,yy,x2,y2,x3,y3,yw,xw;
struct kkk{
	int x,y,cnt,sum;
}a[100001];
bool cmp(kkk a,kkk b){
	return a.cnt>b.cnt;
}
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++){
		if(x*x+y*y<(x+a[i].x)*(x+a[i].x)+(y+a[i].y)*(y+a[i].y)){
			x+=a[i].x,y+=a[i].y;
		}
	}
	ans=sqrt(x*x+y*y*1.0);
	mt19937 rnd(114514);
	while(clock()<7500){
		shuffle(a+1,a+n+1,rnd);
		x=0,y=0,sum=0;
		for(int i=1;i<=n;i++){
			if(x*x+y*y<(x+a[i].x)*(x+a[i].x)+(y+a[i].y)*(y+a[i].y)){
				x+=a[i].x,y+=a[i].y,sum=sqrt(x*x+y*y*1.0);
			}
		}
		ans=max(ans,sum);
	}
	printf("%.100lf",ans);
}
```

---

## 作者：Kidding_Ma (赞：0)

先极角排序，发现选连续的一段点一定是最优的。

实现上对每个向量取关于原点对称向量后，极角排序。复杂度 $O(n\log n)$。

C++ Code

```cpp
#include "bits/stdc++.h"

using namespace std;
using i64 = long long;

using Real = double;
using Point = complex<Real>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<Point> p(n);
    for (int i = 0; i < n; i++) {
        int x, y;
		cin >> x >> y;
      
        p[i] = Point(x, y);
    }

    vector<pair<double, int>> a;
    Point res;
    for (int i = 0; i < n; i++) {
        double a1 = arg(p[i]);
        double a2 = arg(-p[i]);
        a.push_back({a1, i + 1});
        a.push_back({a2, -(i + 1)});
        if (a1 > a2) {
            res += p[i];
        }        
    }

    sort(a.begin(), a.end());

    double ans = 0;
    for (auto &[_, v] : a) {
        if (v < 0) {
            res -= p[-v - 1];
        } else {
            res += p[v - 1];
        }
        ans = max(ans, norm(res));
    }
    cout << fixed << setprecision(15) << sqrt(ans) << '\n';

    return 0;
}
```


---

## 作者：lfxxx (赞：0)

我们注意向量加法的几何意义。

将多个向量向加时，最优的情况是所有边的极坐标单调。

但是有一种特殊情况，就是从极角最大的到极角最小的。

因此把所有向量极角排序，在做一些处理就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+100;
const double eps = 1e-15;
const double pi = acos(-1);
struct Vector{
    double x,y;
    Vector(double X=0,double Y=0){x=X,y=Y;}
}p[maxn];
Vector operator+(Vector x,Vector y){
    return Vector(x.x+y.x,x.y+y.y);
}
Vector operator-(Vector x,Vector y){
    return Vector(x.x-y.x,x.y-y.y);
}
Vector operator*(Vector x,double y){
    return Vector(x.x*y,x.y*y);
}
double polar(Vector x){
    return atan2(x.x,x.y);
}
double len(Vector x){
    return sqrt(x.x*x.x+x.y*x.y);
}
bool cmp(Vector p1,Vector p2)
{
    return polar(p1)<polar(p2);
}
int n;
double ans;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }
    sort(p+1,p+n+1,cmp);
    for(int i=1;i<=n;i++)
        p[i+n]=p[i];
    for(int i=1;i<=2*n;i++){
        for(int j=i;j<=2*n;j++){
            if((j-i+1)>n) continue;
            Vector res=Vector(0,0);
            for(int k=i;k<=j;k++){
                res=res+p[k];
            }
            ans=max(ans,len(res));
        }
    }
    printf("%.13f",ans);
}
```


---

