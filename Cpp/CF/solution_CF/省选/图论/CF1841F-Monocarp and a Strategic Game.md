# Monocarp and a Strategic Game

## 题目描述

# Monocarp 和一款策略游戏


Monocarp 玩一个策略游戏，在游戏中他开发了一个城市。这个城市有四种不同种族的生物——人类、精灵、兽人和矮人。

城市中的每个居民都有一个幸福值，它是一个整数，取决于城市中不同种族的生物数量。具体来说，每个居民的幸福值默认为 $0$；对于同一个种族的每个其他生物，它会增加 $1$；对于每个敌对种族的每个其他生物，它会减少 $1$。人类对于兽人有敌意（反之亦然），精灵对于矮人有敌意（反之亦然）。

游戏开始时，Monocarp 的城市没有居民。在游戏中，$n$ 组生物会来到他的城市并希望在那里定居。第 $i$ 组包含 $a_{i}$ 个人类，$b_{i}$ 个兽人，$c_{i}$ 个精灵和 $d_{i}$ 个矮人。每次，Monocarp 可以接受或拒绝将整个生物群体加入城市。

游戏根据以下公式计算 Monocarp 的得分：$m+k$，其中 $m$ 是城市中的居民数量，而 $k$ 是城市中所有生物的幸福值之和。

帮助 Monocarp 通过最大化得分来获得游戏的胜利！

## 样例 #1

### 输入

```
5
0 0 1 0
1 3 4 2
2 5 1 2
4 5 4 3
1 4 4 5```

### 输出

```
85```

## 样例 #2

### 输入

```
4
3 3 1 5
5 1 5 3
4 4 4 1
1 3 4 4```

### 输出

```
41```

# 题解

## 作者：Caiest_Oier (赞：3)

# [CF1841F](https://www.luogu.com.cn/problem/CF1841F)  
令最后选了 $A$ 个人类，$B$ 个兽人，$C$ 个精灵，$D$ 个矮人，则最终价值为：       
    
$$A+B+C+D+A\times (A-1-B)+B\times (B-1-A)+C\times (C-1-D)+D\times (D-1-C)$$       

化简得 $(A-B)^2+(C-D)^2$，也就是说，对于一个群体，令其转换为一个向量 $(x_i,y_i)=(a_i-b_i,c_i-d_i)$，则最终的价值就是选中的若干个向量的和的模长平方，目标就是最大化模长。    

这里介绍一种新概念，闵可夫斯基和，对于两个凸包 $X$ 与 $Y$，二者的闵可夫斯基和 $X+Y$ 是一个新的凸包，它的构成方式可以形象地理解为，把 $Y$ 放在 $X$ 的边上走一圈，画出来的新凸包。来张手绘丑图：   

![](https://cdn.luogu.com.cn/upload/image_hosting/aej2htfm.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)     

容易发现，两个凸包的闵可夫斯基和的边，是由两个凸包的边按斜率排序而来的。而我们对于若干向量也可以合并出它们的闵可夫斯基和（这里将向量视作两边形，所以要补上一条反向边）。合并出来后，模长最大值一定在顶点上，我们遍历顶点就好了。    

当然，排序后我们虽然可以得到闵可夫斯基和，但是我们无法确定初始点坐标，于是我们钦定，起点为 $y$ 值最小的点，如果有同样小的，取 $x$ 最大的，这样当我们加入一条向下或水平向右的向量时，改变出始点坐标即可。    

代码：


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k1,k2,k3,k4,k5,k6,k7,k8,k9;
long double ans;
int stx,sty;
vector<pair<int,int> >v;
bool comp(pair<int,int>X,pair<int,int>Y){
	if(X.second>=0&&Y.second>=0){
		if(X.second*Y.first!=X.first*Y.second)return X.second*Y.first>X.first*Y.second;
		return X.first<Y.first;
	}
	if(X.second<0&&Y.second>=0)return false;
	if(X.second>=0&&Y.second<0)return true;
	return X.second*Y.first>X.first*Y.second;
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld%lld",&k1,&k2,&k3,&k4);
		if(k1==k2&&k3==k4)continue;
		v.emplace_back(make_pair(k2-k1,k4-k3));
		v.emplace_back(make_pair(k1-k2,k3-k4));
		k5=k2-k1;
		k6=k4-k3;
		if(k6<0||(k6==0&&k5>0))stx+=k5,sty+=k6;
	}
	sort(v.begin(),v.end(),comp);
	for(auto i:v){
		ans=max(ans,(long double)(stx)*(long double)(stx)+(long double)(sty)*(long double)(sty));
		stx+=i.first;
		sty+=i.second;
	}
	printf("%.1Lf",ans);
	return 0;
}
```


---

## 作者：一扶苏一 (赞：3)

# Analysis

题意转化不再赘述，可以看[另一篇题解](https://www.luogu.com.cn/problem/solution/CF1841F)的第二段。总之最后题意转化出来是：给定 $n$ 个二维向量 $(x_i, y_i)$，从中选择若干个，使得所选的向量之和的模长最大。

如果把一个向量看作 $\{(0,0),(x_i, y_i)\}$ 这样一个点集，那么我们发现所有可行解恰好就是这 $n$ 个点集的[闵可夫斯基和](https://www.cnblogs.com/Jekyll-Y/p/16340934.html)。

**证明**：归纳法，假设前 $k-1$ 个向量对应点集的闵可夫斯基和构成了前 $k-1$ 个向量的可行解，那么给这个点集里每个点加上 $(0,0)$ 表示不选 $k$ 这个向量；给每个点加上 $(x_{k}, y_k)$ 表示选上第 $k$ 个向量。这两种点的并恰好就是前 $k$ 个向量对应点集的闵可夫斯基和。得证。

显然，最优解一定在所有点集的闵可夫斯基和对应的凸包上（考虑如果一个点在内部，模长显然不如在凸包上的点长）。那么考虑如何求出这个闵可夫斯基和凸包。闵可夫斯基和凸包的性质是：两个凸多边形 $A$ 和 $B$ 的闵可夫斯基和凸包上的边一定是由这两个凸多边形原来的边平移后围成的。如下图（图源 https://www.cnblogs.com/Jekyll-Y/p/16340934.html）：

![](https://cdn.luogu.com.cn/upload/image_hosting/82oax3es.png)


推广一下，$n$ 个凸多边形的闵可夫斯基和凸包上的边一定是这 $n$ 个多边形原有的边平移围成的。而一个 $A \to B$ 的向量可以看作由 $A \to B$ 和 $B \to A$ 两条边组成的『二边形』。于是我们就知道了最终凸包上一共有 $2n$ 条边，也就是 $n$ 条向量 $(x_i, y_i)$ 构成的边和 $n$ 条向量 $(-x_i, -y_i)$ 构成的边。只需要把这 $2n$ 条边按方向和斜率排个序，就能按顺序遍历这个凸包了。枚举凸包上每个点，找到距原点距离最远的点，即为答案。

## Code

这里解释一下代码里为什么会有

```cpp
if (c < d || ((c == d) && (a < b))) {
  sx += a - b; sy += c - d;
}
```

凸包上的边在 $v$ 数组里是按第 $2 \to 1 \to 3 \to 4$ 象限的顺序排序的。（注意，一个两维都为正的向量自身属于第一象限，但是它在凸包上属于第四象限，因为第四象限的边是从左下到右上的）。想要在凸包上走，就要找到第四象限左侧的第一个点，这个点就是 $y$ 坐标最小的且在 $y$ 轴左侧离 $y$ 轴最近的点。这个 if 就是在累计 $sx$ 和 $sy$ 找这个点。

```cpp
#include <cmath>
#include <vector>
#include <iomanip>
#include <iostream>
#include <algorithm>

int n;
std::vector<std::pair<int, int>> v;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n;
  long long sx = 0, sy = 0;
  for (int a, b, c, d; n; --n) {
    std::cin >> a >> b >> c >> d;
    if ((a == b) && (c == d)) continue;
    v.push_back(std::make_pair(a - b, c - d));
    v.push_back(std::make_pair(b - a, d - c));
    if (c < d || ((c == d) && (a < b))) {
      sx += a - b; sy += c - d;
    }
  }
  auto section = [](const std::pair<int, int> &a) -> int {
    if (a.first > 0 && a.second >= 0) return 1;
    else if (a.first <= 0 && a.second > 0) return 2;
    else if (a.first < 0 && a.second <= 0) return 3;
    else return 4;
  };
  std::sort(v.begin(), v.end(), [&](const std::pair<int, int> &a, const std::pair<int, int> &b) -> bool {
    if (int x = section(a), y = section(b); x != y) return x < y;
    return 1ll * a.first * b.second > 1ll * a.second * b.first;
  });
  double ans =  1.0 * sx * sx + 1.0 * sy * sy;
  for (auto [x, y] : v) {
    sx += x; sy += y;
    ans = std::max(ans, 1.0 * sx * sx + 1.0 * sy * sy); 
  }
  std::cout << std::fixed << std::setprecision(10) << ans << '\n';
}
```

---

## 作者：Kidding_Ma (赞：3)

题意抽象为在 $n$ 个 $a_i,b_i,c_i,d_i$ 中取 $k$ 个 $a_i,b_i,c_i,d_i$，$k$ 为任意数。

然后求最大的 $\sum\limits_{j=1}^{k} a_{j}^{2}+b_{j}^{2}-2a_{j}b_{j}+c_{j}^{2}+d_{j}^{2}-2c_{j}d_{j}$，记 $\vec{p_j}=(b_j-a_j,d_j-c_j)$，则题意转化为计算几何问题，取 $k$ 个向量求最大 $\sum p_j$。

发现是原题，[双倍经验](https://atcoder.jp/contests/abc139/tasks/abc139_f)。

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
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        p[i] = Point(b - a, d - c);
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
    cout << fixed << setprecision(15) << ans << '\n';

    return 0;
}

```

---

## 作者：YocyCraft (赞：1)

题意简介：有四个种族的生物，A 类生物与 B 类生物敌对，C 类生物与 D 类生物敌对，每个生物的舒适度定义为同种族的其他生物数量减去敌对种族的生物数量。现有 $N$ 组生物，每组生物中四种生物的数量分别为 $a_i, b_i, c_i, d_i$，你可以选择任意多组生物并计算得分（得分为生物数量与所有生物的舒适度之和），求最高得分。

题目分析：设最终选定的四种生物数量为 $A, B, C, D$， 考虑每个生物的贡献。每个 A 类生物自身对生物数量贡献为 $1$，同类其他生物带来的舒适度为 $A-1$， 敌对生物带来的舒适度为 $-B$，则总贡献为 $A-B$。 类似地，每个 B 类生物的贡献为 $B-A$，因此 A 类生物与 B 类生物贡献之和为 $A(A-B)+B(B-A)=(A-B)^2$。同理，C 类生物与 D 类生物贡献之和为 $(C-D)^2$。这样，我们就得到了题目的代数表示：设  $w_i \in \{0, 1\}$，求 $\max (\sum w_i(a_i-b_i))^2 + (\sum w_i(c_i-d_i))^2$。

为此，我们定义平面向量 $\bold{v}_i = (a_i-b_i, c_i-d_i)$，问题转化为：给定若干个平面向量，选出若干个使其和的模长最大。由于可行解的数量可以达到 $2^n$ 个，我们无法枚举所有可行解。但我们只需要求出模长最大的可行解，则答案一定在包含所有可行解的凸包上。我们可以按以下的方法求出凸包：首先初始时凸包包含原点 $(0, 0)$， 然后对每个 $\bold{v}_i$ 我们将原凸包的所有顶点朝着 $\bold{v}_i$ 的方向移动，求出包含移动前后的所有点的凸包。经过一定尝试可以看出凸包始终是中心对称图形，且每次加入新的向量 $\bold{v}_i$ 都相当于将 $\bold{v}_i$ 与 $-\bold{v}_i$ 加入到组成凸包边界的向量集合中。因此我们可以维护凸包最左边顶点的坐标以及凸包的上边界：当 $\bold{v}_i$ 指向右边时我们将其直接加入组成上边界的向量集合；当 $\bold{v}_i$ 指向左边时我们将 $-\bold{v}_i$ 加入上边界，同时将最左边顶点的坐标加上 $\bold{v}_i$。在将所有向量排序后，我们就能将这个凸包求出来了。

参考代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pll = pair<ll, ll>;
using vpll = vector<pll>;

#define all(a) (a).begin(),(a).end()

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	vpll v;
	ll x0=0,y0=0;
	for(int i=0;i<n;i++){
		ll a,b,c,d;
		cin>>a>>b>>c>>d;
		ll x=a-b;
		ll y=c-d;
		if(x==0 && y==0) continue;
		if((x==0 && y>0) || x>0){
			v.emplace_back(x,y);
		}else{
			x0+=x;
			y0+=y;
			v.emplace_back(-x,-y);
		}
	}
	sort(all(v),[&](const auto& p1,const auto& p2){
		auto [x1,y1]=p1;
		auto [x2,y2]=p2;
		return y1*x2>x1*y2;
	});
	double ans=0;
	for(int i:{1,-1}){
		for(auto [x,y]:v){
			x0+=x*i;
			y0+=y*i;
			double score=(double)x0*x0+(double)y0*y0;
			ans=max(ans,score);
		}
	}
	cout<<setprecision(15)<<ans;
}
```

[CF代码链接](https://codeforc.es/contest/1841/submission/209539110)

---

## 作者：xiezheyuan (赞：0)

## 简要题意

你在玩一种游戏，角色有四种类型，分别为 $A,B,C,D$，$A,B$ 互相敌对，$C,D$ 互相敌对。

有 $n$ 个需求，第 $i$ 个需求表示为四元组 $(a,b,c,d)$，这意味着有每个类型分别有给定数量的人希望入住。定义每个角色的收益，为与其同类型的角色数（不包括自己）减去与其敌对的角色数。定义你的收益为所有角色的收益总和加上入住的角色数。

你需要选取任意个需求并满足，使得你的收益尽可能大，输出这个最大值。

$1\leq n\leq 3\times 10^5$。

## 思路

### Part 1

考虑最后每个类型分别有 $A,B,C,D$ 个角色入住，则收益为：

$$
\begin{aligned}
&A(A-1)+B(B-1)+C(C-1)+D(D-1)-2AB-2CD+(A+B+C+D)\\
=&A^2+B^2+C^2+D^2-2AB-2CD\\
=&(A-B)^2+(C-D)^2\\
=&|(A-B,C-D)|^2
\end{aligned}
$$

最后可以得到一个类似点到点的距离的形式，我们不妨写成向量模长的形式。由于向量加法就是每一维相加，于是自然而然可以用向量去描述游戏的操作。对于每一个入住需求，可以表示成 $(a-b,c-d)$，转换为下面的问题：

> 有 $n$ 个向量，你需要选出若干个向量，使得它们的和的模长最大，输出这个最大值。

### Part 2

先来观察一下有若干个向量，模长最大的那一个有什么性质。首先向量可以只保留终点，那么就变成研究点集。平面点集的研究方法很有限，我们很容易想到，模长最大的向量的终点一定在所有终点的凸包上。根据凸包的性质，这也是容易理解的。

于是我们想维护所有子集的向量和的终点的凸包（这有一个时髦的概念：闵可夫斯基和）。不过我们不妨画出凸包的形状：

![](https://cdn.luogu.com.cn/upload/image_hosting/a9ta32mk.png)

图中，红色的向量表示凸包相邻之间构成的向量，绿色的点表示所有子集得到的向量和的终点，蓝色的向量表示初始的向量集合中的向量。

仔细观察上图，可以发现**凸包上的所有边都是与初始向量集平行的**，进一步发现**凸包上的向量，是由初始向量和其相反向量构成的**。在此，我们不加证明地给出这个结论，至于证明请参考扶苏的题解。

于是凸包边只有 $2n$ 条，并且向量是已知的。我们先对这些向量极角排序，方便构建这个凸包，以期枚举凸包上的点来统计答案。

### Part 3

如果我们确定了凸包上的一个点，就可以还原出凸包了，现在我们需要找到一个点。

注意到正常的极角排序是从斜率为负的向量开始，所以最开始的一条边就是上凸壳最左侧的边，于是我们可以将所有 $x$ 为负数的点累加即可，注意如果为 $0$，我们希望在 $y$ 轴下。

时间复杂度 $O(n\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
using namespace std;

using i128 = __int128;
using i64 = long long;
const int N = 3e5 + 5;
tuple<int,int,double> p[N << 1];
int n;

i128 hypt(i64 x, i64 y){ return (i128)x * x + (i128)y * y; }

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    i64 x = 0, y = 0;
    for(int i=1,a,b,c,d;i<=n;i++){
        cin >> a >> b >> c >> d;
        p[(i << 1) - 1] = {a - b, c - d, atan2(a - b, c - d)};
        p[i << 1] = {b - a, d - c, atan2(b - a, d - c)};
        if(a - b > 0 || (a == b && c < d)) x += a - b, y += c - d;
    }
    sort(p + 1, p + (n << 1) + 1, [](auto a, auto b){
        return get<2>(a) < get<2>(b);
    });
    i128 ans = hypt(x, y);
    for(int i=1;i<=(n<<1);i++){
        x += get<0>(p[i]), y += get<1>(p[i]);
        ans = max(ans, hypt(x, y));
    }
    string s;
    if(!ans) s = "0";
    while(ans) s += (ans % 10) + '0', ans /= 10;
    reverse(s.begin(), s.end());
    cout << s << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：hh弟中弟 (赞：0)

首先简单推下式子 $a^2+b^2-2ab+c^2-d^2-2cd=(a-b)^2+(c-d)^2$，这个东西肯定不好直接做，看成 $(a-b,c-d)$ 的向量后就是找最大模长。\
极角排序后肯定选连续的一段，这个东西只满足决策单调性，不满足双指针，原因同决策单调性，比如后面有一个更优的，然后全崩了。\
注意到选的一定在一个平角内，因为加上与答案夹角小于 $\frac{\pi}{2}$ 的向量一定不劣，然后可以根据这个做双指针，有一个更聪明的做法，把反向量也加进去，然后先加入 $[\pi,2\pi]$ 的原向量，这样遇到一个向量就加上他的贡献，保证了每个平角都被统计到，时间复杂度 $\mathcal{O}(n\log n)$ 瓶颈是排序。\
[record](https://codeforces.com/contest/1841/submission/300400177)

---

## 作者：Celebrate (赞：0)

我一开始尝试用贪心的思路，发现根本行不通。

然后根据题目的提示，感觉可以转化成一个平面图来做，也就是选择若干个向量使得它们的和的模最大。

然后想象，如果确定一个方向，那么只需要把这个方向 $90^0$ 以内的向量全部做垂线到这个方向上（并且称这些向量为这个方向的集合），然后全部加起来即可。显然，答案即使和最大的方向。

容易发现，如果把相同集合的方向合并， 那么总数是 $O(n)$ 的，对于一个集合并不需要去考虑具体方向的值，只要把向量全部加起来即可。

于是，我们把所有的向量挪到原点，并按照极角排序，然后将一条过原点的直线旋转，并不断统计直线一侧的向量之和，答案即使最大值。

后面瞄了一眼题解，发现用的是一种叫做闵可夫斯基凸包的做法，但从具体做法来讲和我的差不多。


```cpp
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define dwn(i,x,y) for(int i=x;i>=y;i--)
#define ll long long
using namespace std;
template<typename T>inline void qr(T &x){
    x=0;int f=0;char s=getchar();
    while(!isdigit(s))f|=s=='-',s=getchar();
    while(isdigit(s))x=x*10+s-48,s=getchar();
    x=f?-x:x;
}
int cc=0,buf[31];
template<typename T>inline void qw(T x){
    if(x<0)putchar('-'),x=-x;
    do{buf[++cc]=int(x%10);x/=10;}while(x);
    while(cc)putchar(buf[cc--]+'0');
}
const int N=6e5+10;
const double pi=acos(-1.0),eps=1e-10;
struct node{
    ll x,y;double z;
}a[N];int n;
bool cmp(node p1,node p2){
    return p1.z<p2.z;
}
void solve(){
    qr(n);
    rep(i,1,n){
        ll x,y;
        qr(x),qr(y);
        a[i].x=x-y;
        qr(x),qr(y);
        a[i].y=x-y;
        a[i].z=atan2(a[i].y,a[i].x);
        if(a[i].z<0)a[i].z+=2.0*pi;
    }
    sort(a+1,a+n+1,cmp);
    rep(i,1,n){
        a[i+n]=a[i];
        a[i+n].z+=2.0*pi;
    }
    double liml=0,limr=pi;
    int l=1,r=0;
    long long sumx=0,sumy=0;
    double ans=0.0;
    while(liml<2.0*pi){
        while(r<2*n&&a[r+1].z<limr-eps){
            r++;
            sumx+=a[r].x,sumy+=a[r].y;
        }
        while(l<2*n&&a[l].z<liml+eps){
            sumx-=a[l].x,sumy-=a[l].y;
            l++;
        }
        ans=max(ans,1.0*sumx*sumx+1.0*sumy*sumy);
        double disl=a[l].z-liml;
        double disr=r==2*n?1000:a[r+1].z-limr;
        liml+=min(disl,disr)+2.0*eps;
        limr=liml+pi;
    }
    cout<<fixed<<setprecision(10)<<ans<<endl;
}
int main(){
    int tt;tt=1;
    while(tt--)solve();
    return 0;
}
```


---

## 作者：蒟蒻君HJT (赞：0)

推一下式子，发现本质上就是给定 $n$ 个二维向量 $(a_i-b_i,c_i-d_i)$，选出若干个使得向量的和的模长最大。

考虑枚举最终向量的方向（有无数个，但先不管），转而求出选出向量在这个方向上的的投影之和的最大值（错误的方向答案一定不优，正确的方向恰好是答案），如果我们确实可以枚举的话，会发现一定是与这个方向夹角小于 $90$ 度的全选，其他不选。

那我们其实也不用求投影，直接求这些向量的和就可以了。将所有向量的起点平移到原点，答案一定是用一条过原点的直线划分出两个半平面，在一侧的向量全选得到。

考虑将向量根据极角逆时针排序，并复制一份接在末尾。双指针求出每个向量 $v_i$ 上一个转到它不大于 $180$ 度的向量 $l_{v_{i}}$ 即可。只需要枚举一端是 $v_i$，另一端是 $[l_{v_i},l_{v_{i+1}}]$ 的答案就行。

然而笔者没怎么写过计算几何，这样写太多细节调不出来 [细节挂掉代码](https://codeforces.com/contest/1841/submission/226979649)。

观察到依据以上结论，后端点顺时针转时，前端点也单调顺时针转，决策点分治即可，复杂度不上升。

[for reference only.](https://codeforces.com/contest/1841/submission/226990518)

附：细节挂掉代码的 hack 数据是 

```cpp
Input

3
0 10 0 0
2 0 0 0
3 0 0 0

Answer

100
```

暂时没想好怎么处理细节比较简单。


---

