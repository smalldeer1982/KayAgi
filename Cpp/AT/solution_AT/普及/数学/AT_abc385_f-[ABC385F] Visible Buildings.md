# [ABC385F] Visible Buildings

## 题目描述

在数轴上有编号从 $1$ 到 $N$ 的建筑物。第 $i$ 个建筑物位于坐标 $X_i$ 处，高度为 $H_i$。除了高度外的其他方向的尺寸可以忽略不计。

从坐标为 $x$ 且高度为 $h$ 的点 $P$ 看，如果存在建筑物 $i$ 上的某个点 $Q$，使得线段 $PQ$ 不与任何其他建筑物相交，则认为该建筑物是可见的。

请找出在坐标 $0$ 处的最大高度，使得在该高度无法看到所有建筑物。高度必须是非负的；如果在坐标 $0$ 处的高度 $0$ 就能看到所有建筑物，则输出 `-1`。

## 说明/提示

- $1 \leq N \leq 2 \times 10^5$
- $1 \leq X_1 < \dots < X_N \leq 10^9$
- $1 \leq H_i \leq 10^9$
- 所有输入值均为整数。

## 样例 #1

### 输入

```
3
3 2
5 4
7 5```

### 输出

```
1.500000000000000000```

## 样例 #2

### 输入

```
2
1 1
2 100```

### 输出

```
-1```

## 样例 #3

### 输入

```
3
1 1
2 2
3 3```

### 输出

```
0.000000000000000000```

## 样例 #4

### 输入

```
4
10 10
17 5
20 100
27 270```

### 输出

```
17.142857142857142350```

# 题解

## 作者：Emplace (赞：4)

## 思路
这道题其实可以发现就是任意取两点，构造一个一次函数，求斜率最小的哪一个。这里先给一张图。

![](https://cdn.luogu.com.cn/upload/image_hosting/yhz4apxa.png)

图中 $ans$ 的纵坐标就是答案。

可是这样时间复杂度是 $O(n^2)$ 会超时。于是我们考虑只用算相邻两点，我们再给个图证明一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/icpq1f2u.png)

其中有 $1$，$2$，$3$，三条直线。$1$ 与 $2$ 构成的和 $3$ 与 $2$ 为相邻的，而 $1$ 与 $3$ 为不相邻的。它们构成了一个三角形，而根据三角形的性质，$1$ 与 $3$ 这条斜边一定不是最优。

最后还有一种情况。就是如果算出来 $ans$ 的纵坐标为负数，则输出 $-1$。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int x[300000],y[300000],n;
long double ans=-1e100;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
	}
	for(int i=2;i<=n;i++){
		ans=max(ans,y[i]-(long double)(y[i]-y[i-1])/(x[i]-x[i-1])*x[i]);
	}
	if(ans>=0){
		cout<<fixed<<setprecision(12)<<ans;
	}
	else{
		cout<<-1;
	}
	return 0;
}

```

---

## 作者：Noah2022 (赞：3)

### 题目大意
有 $ n $ 个柱子，它离源点距离为 $ x_i $，高度为 $ h_i $。问在 $ 0 $ 这个位置上，高度最少要多少才能看到所有的柱子。

### 思路
给一个图：
![](https://cdn.luogu.com.cn/upload/image_hosting/v1bgswiy.png)
其实求的结果就是 $ y_1 , y_2 , \dots , y_n $ 的最大值。注意：如果它们的 $ \max $ 为负，则输出 $ -1 $。
给一个求 $ y $ 的公式：
```cpp
std::cin>>xx>>hh;
for(register int i(2);i<=n;i=-~i){
    std::cin>>x>>h;
    maxn=std::max(maxn,(long double)(hh*x-xx*h)/(x-xx)); //xx,hh为上一个的x和h
    xx=x,hh=h;
}
```

---

## 作者：未来姚班zyl (赞：2)

能看到所有的建筑相当于与起点的连线斜率递增，则只需有相邻的斜率下降即可。

对于所有相邻的房子，求出房顶连线和 $y$ 轴的交点，则如果选则的 $(0,Y)$ 中 $Y\le y$ 就看不到右侧的建筑。如果 $Y$ 比所有的交点都高，就能看见所有建筑。所以求出最高的交点就可以了。

坐标为有理数，使用 `struct` 存储分数形式的答案即可最大程度上避免精度误差。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define repn(x) rep(x,1,n)
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
using namespace std;
const int N=3e5+5;
int n,a[N],h[N];
struct num{
	int a,b;//a/b
}ans;
inline num mx(num a,num b){
	if(a.a==-1)return b;
	return a.a*b.b>=b.a*a.b?a:b;
}
inline void Main(){
	n=read();
	repn(i)a[i]=read(),h[i]=read();
	ans={-1,1};
	rep(i,1,n-1){
		int dx=a[i+1]-a[i],dy=h[i]-h[i+1];
		int Ny=dx*h[i]+dy*a[i];
		if(Ny<0)continue;
		ans=mx(ans,{Ny,dx});
	}	
	if(ans.a==-1)cout <<-1;
	else printf("%.10lf",(double)ans.a/ans.b);
}
signed main(){
    int T=1;
	while(T--)Main();
	return 0;
}

```

---

## 作者：yy0707 (赞：2)

### 题目大意

给你 $N$ 栋建筑的坐标以及高度，让你求从坐标 0 无法看见所有建筑的最高高度。

我们先考虑对于两栋建筑 $i$ 和 $j$，从坐标 0 无法看见建筑 $j$ 的最高高度。$(i<j)$  
不难想到，答案为 $h_j-x_j\div(x_j-x_i)\times(h_j-h_i)$。   
但很明显，这样做的话时间复杂度是 $O(n^2)$ 的，会超时，所以我们需要优化。

我们可以发现，对于以下这个情况，$i$ 和 $k$ 这两栋建筑对答案是没有贡献的。
![](https://cdn.luogu.com.cn/upload/image_hosting/cxm8p7yn.png)
+ 如果 $i$ 到 $k$ 的线段被 $j$ 挡住了，那么很明显 $i$ 和 $k$ 是无法产生贡献的。 
+ 如果 $i$ 到 $k$ 的线段没有被 $j$ 挡住，那么 $i$ 和 $k$ 两这两栋建筑的斜率是要比 $i$ 和 $j$ 要低的，所以还是对答案没有贡献。

所以对于每一栋建筑，只需要考虑它被它前面那栋建筑挡住的位置就行了，时间复杂度 $O(n)$。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long double n,x[200001],h[200001],ans=-100;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>h[i];
		if(i>1)ans=max(ans,h[i]-x[i]/(x[i]-x[i-1])*(h[i]-h[i-1]));
	}if(ans<0)cout<<-1;else cout<<fixed<<setprecision(15)<<ans;
}
```
upd 24.12.25：优化了一些语言的表述。

---

## 作者：_zqh_ (赞：1)

> 小学二年级就会的基本一次函数知识。

抽象一下题意：

求 $n$ 个点 $(X_i, H_i)$ 中任意两个点组成的直线的截距的最大值（不小于 $0$，$X_i$ 递增）。

---

先说结论：先特判 $n = 1$，然后答案只可能是由编号相邻的两个点组成的一次函数的截距。

为了方便，我们记 $B\{(a, b), (c, d)\}$ 为 $(a, b)$、$(c, d)$ 两点组成的一次函数的截距。

> 若 $B \{ (X_i, H_i), (X_{i + 1}, H_{i + 1}) \} \lt B \{ (X_{i - 1}, H_{i - 1}), (X_{i + 1}, H_{i + 1}) \}$；
>
> 则必有 $B \{ (X_{i - 1}, H_{i - 1}), (X_{i + 1}, H_{i + 1}) \lt B \{ (X_{i - 1}, H_{i - 1}), (X_{i}, H_{i}) \}$。
>
> 证明：
> 
> 根据已知条件，$(X_i, H_i)$ 必在直线 $(X_{i - 1}, H_{i - 1}) \leftrightarrow (X_{i + 1}, H_{i + 1})$ 之下。
>
> 那么 $(X_{i + 1}, H_{i + 1})$ 就在直线 $(X_{i - 1}, H_{i - 1}) \leftrightarrow (X_{i}, H_{i})$ 之上。
>
> （可能语言~~有点疏漏~~太抽象，看图就好理解了）
>
> ![](https://cdn.luogu.com.cn/upload/image_hosting/17bbq2cl.png)

那么只需要枚举出任意两个编号相邻的点算一次函数的截距，并取最大值即可。

---

**如果你不知道一次函数相关知识，那就~~别做这题~~学习一下罢。**

给一个斜率与截距的计算公式：

$$
k = \frac{y_1 - y_2}{x_1 - x_2}, b = y_1 - k \times x_1
$$

不给代码了。

---

## 作者：hwc2011 (赞：1)

考虑横坐标位于 $i$、$j$、$k$ 上的三个建筑，我们可以分两种情况考虑（其中 $i < j < k$）：
![](https://cdn.luogu.com.cn/upload/image_hosting/4nhb5vqg.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)
设 $f(i,j)$ 表示对于只存在横坐标在 $i$、$j$ 的两个建筑时在纵轴上只能看到横坐标在 $i$ 的建筑的最高点的纵坐标，如果我们先找出 $(0,f(i,k))$，将它与横坐标在 $k$ 的建筑的顶端相连（如图所示），则：
1. 如果所连线段穿过横坐标在 $j$ 的建筑，则答案为 $f(j,k)$。
2. 如果所连线段未穿过横坐标在 $j$ 的建筑，则答案为 $f(i,j)$。

我们就会发现对于几个建筑而言，答案肯定存在于两栋相邻的建筑（假设他们的横坐标在 $i$、$j$），即 $f(i,j)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long double a,b,c,d,ans=-1;
signed main(){
	cin>>n>>a>>b;
	for(int i=1;i<n;i++){
		cin>>c>>d;
		ans=max(ans,d-c*(d-b)/(c-a));
		a=c;
		b=d;
	}
	if(ans<0) cout<<-1;
	else printf("%.10Lf",ans);
}
```

---

## 作者：I_Love_FYC (赞：1)

这是一道 diff 为 $1902$ 的题目，看上去十分困难。

经过小脑的卖力思考，你得知了这些：

- 令 $h[i][j]$ 为建筑物 $i$ 不被建筑物 $j$ 遮挡的最低高度。
- 答案就是 $h$ 数组中的最大值。

但是，直接计算会导致 $N^2$ 的时间复杂度，你开始烧了起来。

根据人类的智慧和数学直觉，你的大脑发现了：
- 从点 $P(0, h)$ 出发，若要看到建筑物 $i$，需要存在建筑物 $i$ 上的某个点 $Q(X_i, H_i)$，使得线段 $PQ$ 不被其他任何建筑物遮挡。
- 这可以转化为：**从 $P$ 到每个建筑物的视线斜率必须严格递增。**

很快，思路开始清晰：

1. **斜率计算**：
   - 从 $P(0, h)$ 到建筑物 $i$ 的斜率为 $\frac{H_i - h}{X_i}$。
   - 为了确保视线不被遮挡，这些斜率需要满足严格递增的关系，即对于所有 $i < j$ ，有 $\frac{H_i - h}{X_i} < \frac{H_j - h}{X_j}$。

2. **临界高度的确定**：
   - 对于每对相邻的建筑物 $(i-1, i)$ ，我们可以通过设定它们的斜率相等来求出一个临界高度 $h_i$：
     $\frac{H_{i-1} - h_i}{X_{i-1}} = \frac{H_i - h_i}{X_i}$
     
     解得：
     $h_i = \frac{H_{i-1} \cdot X_i - H_i \cdot X_{i-1}}{X_i - X_{i-1}}$
   - 最大的这些 $h_i$ 即为我们所求的最大高度。为什么只用考虑相邻的呢？因为上面式子就已经让斜率递增了，他都递增了总不可能突然掉下去吧，所以只要相邻的都在上升，整体就已经也在上升。

3. **最终判断**：
   - 如果所有计算得到的 $h_i < 0$，则意味着即使在高度 $0$ 也能看到所有建筑物，此时输出 `-1`。
   - 否则，输出最大的 $h_i$。

最后，你没有使用高深的技巧，也没有去百度复制数据结构模版，就得到了AC：

### STD

```cpp
#pragma GCC optimize("O3")
#include<bits/stdc++.h>
std::string __NAME = "Problem";
std::string __IN = __NAME+".in";
std::string __OUT = __NAME+".out";
using namespace std;
#define int long long
#define endl '\n'
typedef __int128 i128;
typedef pair<int,int> pii;
typedef map<int,int> mii;
#define sz(x) ((int)x.size())
#define F(i, j, k) for(int i = (j); i <= (k); ++i)
#define D(i, j, k) for(int i = (j); i >= (k); --i)
#define Fe(i,j) for(auto&i:j)
const int inf = INT_MAX * 200ll;
#define mem(a, x) memset(a, x, sizeof(a))
#define __mid(a,b) (a+(b-a)/2)
#define __lcm(a,b) (a/__gcd(a,b)*b)
const int mod = 998244353;
const int MOD = 998244353;
#define vi vector<int>
#define stoi stoll
#define eb emplace_back
#define pb push_back
#define COUT cout
#define oyes cout<<"Yes"<<endl
#define ono cout<<"No"<<endl
#define CIN cin
#define ENDL '\n'
#define max(a,b) ((a>b)?(a):(b))
#define min(a,b) ((a<b)?(a):(b))
#define elif else if
#define debug(x) cout << (x) << " : " << x << endl
using db = long double;
#define sqrt sqrtl
#define umap unordered_map
#define uset unordered_set
#define all(x) x.begin()+1,x.end()
#define all2(x) x.begin(),x.end()
#define se second
#define fir first
const int N = 1e6+100;
const int M = 2e5+100;
#define setps fixed<<setprecision(20)
#define vii vector<vector<int>>

signed main(){
	// freopen(__IN.c_str(),"r",stdin);freopen(__OUT.c_str(),"w",stdout);
	ios::sync_with_stdio(false),cin.tie(nullptr);
	int n;cin>>n;
	if(n==1)return cout<<-1,0;
	vector<pair<db,db>>a(n);
	F(i,0,n-1)cin>>a[i].fir>>a[i].se;
	db mh=-1e20;
	F(i,1,n-1){
        db f=a[i-1].second*a[i].first-a[i].second*a[i-1].first;
        mh=max(mh,f/(a[i].first-a[i-1].first));
	}
	const db eps=1e-12;
    if(mh<-eps)cout<<"-1";
    else{
        if(fabs(mh)<=eps)cout<<fixed<<setprecision(20)<<"0";
        else{
            if(mh<=0)cout<<fixed<<setprecision(20)<<"0";
            else cout<<fixed<<setprecision(20)<<mh;
        }
    }
	return 0;
}
```



- **时间复杂度**：$O(N)$
- **空间复杂度**：$O(N)$

---

## 作者：gavinliu266 (赞：1)

# 思路
转换一下题意：给定 $n$ 个点的坐标，任意选择两个点，最大化它们的截距。

大胆猜结论：从后往前，维护一个下凸壳或上凸壳。

画一下样例，发现是下凸壳，但是我们要证明它。

如图。

![图](https://cdn.luogu.com.cn/upload/image_hosting/nk0ypr7b.png)

出现了一个上凸点 $B$，对于在左边某点，设直线 $AC$ 交它到 $x$ 轴的垂线于 $D$：
- 若该点与 $D$ 重合，则点 $A$ 与点 $C$ 都比 $B$ 更优。
- 若该点在 $D$ 下方，如点 $F$，选择点 $C$ 一定更优。
  
  证明：这里两条直线都过点 $F$，所以只需证明 $B$ 在 $FC$ 上方。注意到只有 $F$ 在直线 $BC$ 与 $DE$ 的交点上方或与之重合时 $B$ 才不在 $FC$ 上方，又因为 $B$ 是上凸点，所以这个交点一定在 $D$ 上方，与 $F$ 在 $D$ 下方矛盾，所以 $B$ 一定在 $FC$ 上方。
- 若该点在 $D$ 上方，如点 $F$，同理，选择点 $A$ 一定更优。

综上，点 $B$ 无法为接下来加入的点产生新贡献，应该弹出。

于是，剩下来的一定是一个下凸壳，所以最后选择栈顶的两个计算截距就可以了。

你开心的交了上去，然后喜提 WA。

为什么呢？如图。

![图](https://cdn.luogu.com.cn/upload/image_hosting/qlc26eld.png)

上凸点 $B$ 弹出后，循环结束，答案为直线 $AC$ 的截距，这当然是不对的。

因为弹出上凸点可能会影响它以前的贡献，所以我们还要在弹出前也把栈顶的两个元素计算一次贡献，就可以了。

时间复杂度：$O(n)$。

最后，其实也可以从左往右做，但是要维护上凸壳。

# 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define double long double
const int N = 2e5 + 5;
int n;
int x[N], h[N];
double ans = -1e300;
ll xt(int ax, int ay, int bx, int by) { return (ll)ax * (ll)by - (ll)bx * (ll)ay; }
ll gxt(int a, int b, int c) { return xt(x[b] - x[a], h[b] - h[a], x[c] - x[b], h[c] - h[b]); }
// 叉积
int stk[N], tp;  // 单调栈维护下凸壳
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d%d", &x[i], &h[i]);
    for(int i = n; i >= 1; --i) {
        while(tp >= 2 && gxt(i, stk[tp], stk[tp - 1]) < 0) {
            double b = (double)((ll)x[stk[tp]] * (ll)h[stk[tp - 1]] - (ll)x[stk[tp - 1]] * (ll)h[stk[tp]]) / (double)(x[stk[tp]] - x[stk[tp - 1]]);
            ans = max(ans, b);
            --tp;
        }
        stk[++tp] = i;
    }
    if(tp >= 2) {
        double b = (double)((ll)x[stk[tp]] * (ll)h[stk[tp - 1]] - (ll)x[stk[tp - 1]] * (ll)h[stk[tp]]) / (double)(x[stk[tp]] - x[stk[tp - 1]]);
        ans = max(ans, b);
    }
    ans += 1e-18;
    if(ans < 0) printf("-1\n");
    else printf("%.17Lf\n", ans);
}
```

# 另解
看了官方题解。

图懒得画了，这个图是官方题解的。

![图](https://img.atcoder.jp/abc385/5da48964cee4cd1aacd8c07c0bd21a4e.png)

意思是给定 $i$，$j$，$k$ 三个点，如果 $i$，$j$，$k$ 三点共线，那么 $(i,k)$ 可以忽略。否则 $(i,j)$ 与 $(j,k)$ 中一定有一个比 $(i,k)$ 更优。

所以，只需要考虑相邻两个即可。

时间复杂度也是 $O(n)$，但是我的那个常数巨大。

---

## 作者：HasNoName (赞：1)

https://www.geogebra.org/calculator/qvkesfcg

### 思路
个人感觉是一道一次函数的好题（因为我太菜了）。

其实不需要用到任何数据结构。

先给出一个结论：如果有三个点 $A$、$B$、$C$，且它们的横坐标单调递增，则三个点中的于纵轴的最高交点一定不为直线 $AC$。

![](https://cdn.luogu.com.cn/upload/image_hosting/j5q20d91.png)

分 $C$ 点在 $AB$ 上 $C$ 点在 $AB$ 下方两种情况讨论即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define double long double//用double可能会挂两个点。
const int N=500005;
typedef long long ll;
int x[N],y[N];
double f(double x1,double y1,double x2,double y2)//一次函数计算与y轴交点
{
	return y1-x1*(y1-y2+0.0)/(x1-x2);
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	double n,ans=-1;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x[i]>>y[i];
		if(i>1)ans=max(ans,f(x[i-1],y[i-1],x[i],y[i]));
	}
	if(ans<0)cout<<"-1\n";//低于x轴
	else printf("%.10Lf\n",ans);
	return 0;
}
```

---

## 作者：wangyizhi (赞：1)

**题目传送门：**
**[洛谷](https://www.luogu.com.cn/problem/at_abc385_f) || [AtCoder](https://atcoder.jp/contests/abc385/tasks/abc385_f)**

人类智慧题。

## 题目大意

给定 $N$ 条一端在 $x$ 轴正半轴上，另一端在第一象限上的垂直于 $x$ 轴的线段。记上端点坐标为 $(x_i,h_i)$。找 $y$ 轴上一点使得这一点与给定线段上端点的连线与其它给定线段（不包括端点）不交。求满足条件的点的纵坐标最小值。特别地，若这个值小于 $0$，输出 `-1`。其中 $N \le 2\times10^5$。

## 题目分析

把题目转化一下，就变成了：给定 $N$ 个点，求经过任意两点直线与 $y$ 轴交点的最大值。

可以画图模拟一下，这里不再证明。

那然后怎么做呢？

###### ~~蒟蒻想过单调栈维护凸包但觉得 ABC E 题应该不至于出那玩意。~~


> *我们充分发扬人类智慧：*
>
> *每次只取一个点向前的 100 个点计算，*
>
> *可以猜到答案一定是这些值的最大值。*

~~**咦？样例过了？甚至 AC 了？？？**~~

先摆结论：每次只要取一个点向前的一个点计算即可。

证明很简单。假设现在有两点 $A$，$B$。若 $AB$ 间有一点 $C$，当 $C$ 在 $AB$ 上方时，显然 $AC$ 产生的结果大于 $AB$ 产生的结果；当 $C$ 在 $AB$ 下方时，显然 $BC$ 产生的结果大于 $AB$ 产生的结果。因此非相邻的两点肯定不比相邻两点更优。

然后就做完了。

## AC Code

```cpp
// by wangyizhi(571247)
// link: https://atcoder.jp/contests/abc385/submissions/60977990
#include<iostream>
#include<iomanip>
using namespace std;
using ld=long double;
const int N=2e5+1;
const ld eps=1e-15;
struct __pt
{
	ld x,y;
}a[N];
inline ld getb(__pt x,__pt y)
{
	ld k=1.l*(y.y-x.y)/(y.x-x.x);
	return x.y-k*x.x;
}
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].x>>a[i].y;
	ld ans=-1e38;
	for(int i=1;i<n;i++)
		ans=max(ans,getb(a[i],a[i+1]));
	if(ans<0.l) cout<<-1;
	else cout<<fixed<<setprecision(15)<<ans;
	return 0;
}
```

---

## 作者：Nagato_ (赞：0)

### 题目简述：
在一条数轴上，存在 $N$ 座编号从 $1$ 到 $N$ 的建筑物。建筑物 $i$ 位于坐标 $X_i$，高度为 $H_i$。除了高度以外的其他方向的大小可以忽略不计，以上输入均为正整数。

从坐标为 $x$、高度为 $h$ 的点 $P$ 出发，如果存在建筑物 $i$ 上的某个点 $Q$，使得线段 $PQ$ 不与任何其他建筑物相交，则建筑物 $i$ 被认为是可见的。

现在需要找出在坐标 $0$ 处，无法看到所有建筑物的最大高度。高度必须为非负数；如果在坐标 $0$ 处高度 $0$ 可以看到所有建筑物，那么报告 $-1$。

### 解法
首先，我们考虑只有两栋建筑物，最高能到多高，仍看不到所有建筑物。如图所示，显然两栋建筑物的顶点连线与 $y$ 轴的交点，就是最高的高度。因为一旦高度更高，我们与第二栋建筑物的连线就不交与任何建筑物，就能看到了。

![](https://cdn.luogu.com.cn/upload/image_hosting/wbcndn8x.png)

然后，我们考虑加入第三栋建筑物在中间会如何。

若这栋建筑物在原直线的下面，如图，那么新加入的建筑物与左边的建筑物组合，得到了更高的一条连线，这是新的最高的高度。

![](https://cdn.luogu.com.cn/upload/image_hosting/f66mmm3k.png)

若这栋建筑物在原直线的上面，如图，那么新加入的建筑物与右边的建筑物组合，得到了更高的一条连线，这是新的最高的高度。

![](https://cdn.luogu.com.cn/upload/image_hosting/wl1bi1uy.png)

于是我们得到结论，对于每一栋建筑物，我们只需要考虑与其相邻的建筑物，连线，并找到与 $y$ 轴相交点的最大高度即可。

### 实现
我们考虑两个点，坐标为 $(x_1,y_1)$，$(x_2,y_2)$。

待定系数，得

$\begin{cases}
  k x_1 + b = y_1\\
  k x_2 + b = y_2\\
\end{cases} $

解得

$ b = \frac{ x_1 y_2 - x_2 y_1 }  {x_1-x_2} $

将 $x = 0$ 带入，坐标即为 $(0,b)$，此题完结。

### 细节
输入有 $1 \leq X_1 < X_2 < \cdots < X_N \leq 10^9 $，所以无需按 $x$ 排序，且 $x$ 相乘小于 $10^{18}$，不用担心溢出问题。

---

## 作者：sjh0626 (赞：0)

## 题意概括
在一条数轴上有 $N$ 幢编号为 $1$ 至 $N$ 的建筑物。  
建筑物 $i$ 位于坐标 $X_i$ 上，高度为 $H_i$ 。除高度外，其他方向的大小可以忽略不计。

从坐标为 $x$ 、高度为 $h$ 的点 $P$ 出发，如果在建筑物 $i$ 上存在点 $Q$ ，且线段 $PQ$ 不与任何其他建筑物相交，则认为建筑物 $i$ 是可见的。

求坐标 $0$ 处无法看到所有建筑物的最大高度。高度必须是非负数；如果在坐标 $0$ 处的高度 $0$ 可以看到所有建筑物，则输出 `-1`。
## 前置知识
- 斜率，参见这篇文章：[直线的斜率（坡度）](https://www.shuxuele.com/gradient.html)。
## 思路分析
首先我们要知道，我们要在什么时候才能刚好无法看到所有建筑物。

根据斜率，我们可以知道，当且仅当第一个建筑物与眼睛的斜率 $=$ 第二个建筑物与第一个建筑物的斜率时，才刚好看不到。

在这里，设眼睛的高度为 $h$，则我们可以得出一个方程。

$$\frac{H_i-h}{X_i-0}=\frac{H_{i+1}-H_i}{X_{i+1}-X_i}$$

解完方程并化简可以得出 $h=\displaystyle\frac{H_iX_{i+1}-H_{i+1}X_i}{X_{i+1}-X_i}$。

最后循环取每个 $h$ 的最大值，若 $h < 0$，则无解，输出 `-1`。
## 代码解析
```cpp
#include<bits/stdc++.h>
#define sjh0626s return
#define code 0
using namespace std;
int n;
long double nh,nx,ph,px,ans=-1e9; 
int main(){
	cin>>n>>px>>ph;
	for(int i=2;i<=n;i++){
		cin>>nx>>nh; 
		ans=max(ans,(ph*nx-nh*px)/(nx-px)); //当前高度 
		px=nx,ph=nh;
	} 
	if(ans<0){
		cout<<-1;
	}
	else cout<<fixed<<setprecision(15)<<ans;
	sjh0626s code;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

这是怎么在 kenkoooo 上评蓝的。

结论：只有相邻的点对答案才有贡献。画个图就明了了。

![](https://cdn.luogu.com.cn/upload/image_hosting/7rs9ahke.png)

若有两个不相邻的点产生了贡献，无论在它们中间的点在这条线上方还是下方，都有一种更优的连法使另一条直线纵截距更大。因此套用纵截距公式去对相邻两个点算一下就好了。

## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ld long double
#define eps 1e-11
ld x[200010],y[200010];
int main()
{
	int n;
	ld ans=-1;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
	for(int i=2;i<=n;i++)
	{
		ans=max(ans,(y[i]*x[i-1]-y[i-1]*x[i])/(x[i-1]-x[i]));
	}
	if(ans<0) cout<<-1;
	else cout<<fixed<<setprecision(11)<<(ans<0?-1:(ans==-0?0:ans));
}

---

