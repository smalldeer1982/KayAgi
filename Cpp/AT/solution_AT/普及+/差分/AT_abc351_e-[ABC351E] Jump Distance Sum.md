# [ABC351E] Jump Distance Sum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc351/tasks/abc351_e

座標平面上に $ N $ 個の点 $ P_1,P_2,\ldots,P_N $ があり、点 $ P_i $ の座標は $ (X_i,Y_i) $ です。  
$ 2 $ つの点 $ A,B $ の距離 $ \text{dist}(A,B) $ を次のように定義します。

> 最初、ウサギが点 $ A $ にいる。  
> $ (x,y) $ にいるウサギは $ (x+1,y+1) $, $ (x+1,y-1) $, $ (x-1,y+1) $, $ (x-1,y-1) $ のいずれかに $ 1 $ 回のジャンプで移動することができる。  
> 点 $ A $ から点 $ B $ まで移動するために必要なジャンプの回数の最小値を $ \text{dist}(A,B) $ として定義する。  
> ただし、何度ジャンプを繰り返しても点 $ A $ から点 $ B $ まで移動できないとき、$ \text{dist}(A,B)=0 $ とする。

$ \displaystyle\sum_{i=1}^{N-1}\displaystyle\sum_{j=i+1}^N\ \text{dist}(P_i,P_j) $ を求めてください。

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 2\times\ 10^5 $
- $ 0\leq\ X_i,Y_i\leq\ 10^8 $
- $ i\neq\ j $ ならば $ (X_i,Y_i)\neq\ (X_j,Y_j) $
- 入力はすべて整数

### Sample Explanation 1

$ P_1,P_2,P_3 $ の座標はそれぞれ $ (0,0) $, $ (1,3) $, $ (5,6) $ です。 $ P_1 $ から $ P_2 $ へはウサギは $ (0,0)\to\ (1,1)\to\ (0,2)\to\ (1,3) $ と $ 3 $ 回で移動でき、$ 2 $ 回以下では $ P_1 $ から $ P_2 $ まで移動できないため、 $ \text{dist}(P_1,P_2)=3 $ です。 $ P_1 $ から $ P_3 $ および $ P_2 $ から $ P_3 $ へはウサギは移動できないため、$ \text{dist}(P_1,P_3)=\text{dist}(P_2,P_3)＝0 $ となります。 よって、答えは $ \displaystyle\sum_{i=1}^{2}\displaystyle\sum_{j=i+1}^3\text{dist}(P_i,P_j)=\text{dist}(P_1,P_2)+\text{dist}(P_1,P_3)+\text{dist}(P_2,P_3)=3+0+0=3 $ となります。

## 样例 #1

### 输入

```
3
0 0
1 3
5 6```

### 输出

```
3```

## 样例 #2

### 输入

```
5
0 5
1 7
2 9
3 8
4 6```

### 输出

```
11```

# 题解

## 作者：weitianyi (赞：13)

#### 题目大意
在一个平面上有 $n$ 个点，求 $\sum_{i=1}^{n-1}\sum_{j=i+1}^n dist(i,j)$ 的值。

$dist(i,j)$ 定义为 从点 $i$ 走到点 $j$ 的最少步数，每一步只沿格子的对角线走。
#### 简要题解
首先发现点 $i$ 能走到点 $j$ 当且仅当 $x_i + y_i$ 和 $x_j + y_j$ 奇偶性相同，因此一种很显然的思路是将点按 $x+y$ 的奇偶性分成两组，分别进行处理。

先考虑 $x + y$ 是偶数的情况，如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/cyt5g37m.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

发现直接做似乎不行，因此将整张图旋转 $45\degree$ 就可以了， 如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/i1pcmhn9.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

神奇地发现，在新网格（蓝色）上，原本难以处理的 $dist(i,j)$ 变成了普通的距离，原来的 $(x,y)$ 就变成了 $(\frac{x-y}{2},\frac{x+y}{2})$，对于新位置 $(x_i,y_i)$，答案 $dist(i, j)$ 就变成了 $|x_i-x_j|+|y_i-y_j|$，分别按 $x$ 和 $y$ 排序进行处理即可（具体过程见代码）。

对于 $x+y$ 为奇数的情况，可以将所有 $y$ 加上 $1$ 变成和偶数一样的情况，对答案不会造成影响。

妙哉！

#### 参考代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
vector<pair<int, int> > ou, ji;
bool cmp1(pair<int, int> x, pair<int, int> y) {
    return x.first < y.first;
}
bool cmp2(pair<int, int> x, pair<int, int> y) {
    return x.second < y.second;
}
int solve(vector<pair<int, int> > point) {
    for (auto &it : point) {
        int x = it.first, y = it.second;
        it.first = (x - y) / 2;
        it.second = it.first + y;
    }
    sort(point.begin(), point.end(), cmp1);
    int ans = 0, now = 0;
    for (int i = 0; i < (int) point.size(); i++) {
        ans += point[i].first * i - now;
        now += point[i].first;
    }
    sort(point.begin(), point.end(), cmp2);
    int ans2 = 0, now2 = 0;
    for (int i = 0; i < (int) point.size(); i++) {
        ans2 += point[i].second * i - now2;
        now2 += point[i].second;
    }
    return ans + ans2;
}
signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        if ((x + y) % 2 == 0) ou.push_back({x, y});
        else ji.push_back({x, y + 1});
    }
    cout << solve(ou) + solve(ji) << endl;
    return 0;
}
```

---

## 作者：zrl123456 (赞：5)

[题目](https://www.luogu.com.cn/problem/AT_abc351_e)

考察：思维。  
题目简述：  
定义 $\text{dist}(A,B)$ 表示：  
- 一开始它在 $A$ 点。  
- 设 $A$ 点坐标为 $(x,y)$，然后它可以向 $(x+1,y+1),(x+1,y-1),(x-1,y-1),(x-1,y+1)$ 移动一步，$\text{dist}(A,B)$ 为移动的最小步数。
- 当其永远无法达到时，$\text{dist}(A,B)=0$。  

给你 $n$ 个点，其坐标分别为 $A_i$，求 $\displaystyle\sum_{i=1}^{n-1}\sum_{j=i+1}^n\text{dist}(A_i,A_j)$。  

------------
我们很容易分析出 $\text{dist}((x_i,y_i),(x_j,y_j))=\max(x_i-x_j,y_i-y_j)$，在 $(x_i+y_i)\bmod 2\ne(x_j+y_j)\bmod 2$ 时，$\text{dist}((x_i,y_i)(x_j,y_j))=0$。  
暴力模拟的话，时间复杂度为 $O(n^2)$，无法通过 $n\le 2\times 10^5$ 的数据。

我们可以尝试把他转化成曼哈顿距离，如图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/t8hwgpj7.png)
我们将其旋转 $45$ 度，使 $(0,0)$ 还是 $(0,0)$，这样 $(0,2)$ 变成了 $(-1,1)$。  
我们很容易发现 $(x,y)$ 变成了 $\displaystyle(\frac{x_i+y_i}{2},\frac{y_i-x_i}{2})$。  
以上是 $(x_i+y_i)\bmod 2=0$ 的情况，$(x_i+y_i)\bmod 2=1$ 时我们只需要让 $y_i$ 减去 $1$ 就可以了。  

这样，式子就变成了 $\displaystyle\sum_{i=1}^{n-1}\sum_{j=i+1}^n|x_i-x_j|+|y_i-y_j|$，那么我们可以排一个序（值是不变的），然后：
$$\sum_{i=1}^{n-1}\sum_{j=i+1}^nx_j+y_j-x_i-y_i=\sum_{j=2}^n\sum_{i=1}^{j-1}x_j+y_j-x_i-y_i$$
然后我们可以维护前缀和（$\displaystyle sumx_x=\sum_{i=1}^xx_i,sumy_x=\sum_{i=1}^xy_i$），这样：  
$$\sum_{j=2}^n\sum_{i=1}^{j-1}x_j+y_j-x_i-y_i=\sum_{j=2}^n(j-1)(x_j+y_j)-sumx_{j-1}-sumy_{j-1}$$
这样就可以了。  

代码：  
```cpp
#include<bits/stdc++.h>
#define int long long
#define inl inline
#define INF LLONG_MAX
#define rep(i,x,y) for(int i=x;i<=y;++i)
#define rer(i,x,y,cmp) for(int i=x;i<=y&&cmp;++i)
#define per(i,x,y) for(int i=x;i>=y;--i)
#define FAST ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define endl '\n'
using namespace std;
const int N=4e5+5;
int n,x[N],y[N],ans;
vector<int>gx[5],gy[5];
signed main(){
	FAST;
	cin>>n;
	rep(i,1,n) cin>>x[i]>>y[i];
	rep(i,1,n){
		int k=(x[i]^y[i])&1;
		gx[k].push_back((x[i]+y[i]-k)>>1);
		gy[k].push_back((y[i]-x[i]-k)>>1);
	}
	rep(i,0,1){
		sort(gx[i].begin(),gx[i].end());
		sort(gy[i].begin(),gy[i].end());
	}
	rep(k,0,1){
		int sumx=0,sumy=0,siz=gx[k].size();
		rep(i,0,siz-1){
			int x=gx[k][i],y=gy[k][i];
			ans+=x*i-sumx+y*i-sumy;
			sumx+=x;
			sumy+=y;
		}
	}
	cout<<ans;
	return 0;
}	
```

---

## 作者：Pentiment (赞：3)

还可以的题。

首先注意到 $\text{dist}$ 的定义很像切比雪夫距离，只不过不能够水平或者竖直移动。

我们发现，对于点 $(a,b)$ 和 $(c,d)$，每一次移动对 $|a-c|+|b-d|$ 的改变量一定是偶数。因此我们可以判断：当数对 $(a,c)$ 与 $(b,d)$ 的奇偶性都相同或都不同时，答案就是切比雪夫距离：$\max(|a-c|,|b-d|)$；否则答案为 $0$。

然后就是经典 trick：把切比雪夫距离 $\max(|a-c|,|b-d|)$ 转化为曼哈顿距离 $|a-c|+|b-d|$。具体地说，将点 $(x,y)$ 变为 $\left(\dfrac{x+y}{2},\dfrac{x-y}{2}\right)$。

因为每个点对刚好被计算一次，所以我们可以将所有点按照转化后的 $x$ 坐标排序，按照转化后的 $x$ 坐标从大到小遍历，这样我们就把 $x$ 一维的绝对值去掉了。然后，对于纵坐标为 $y$ 的点，答案分两种：纵坐标大于 $y$ 的点，以及纵坐标小于 $y$ 的点。用树状数组分别维护每种奇偶性中纵坐标 $\leq y$​ 的点的纵坐标之和与个数即可。由于转化后的点坐标范围较大，需要事先离散化。

代码中为了简便没有将转换后的坐标除以 $2$，所以答案最后要除回去。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200005;
int n, a[N], b[N], len;
struct point {
	int x, y, xx, yy;
} p[N];
bool cmp(point a, point b) { return a.xx == b.xx ? a.yy < b.yy : a.xx < b.xx; }
ll sum[2][2], cnt[2][2], ans, tmp1, tmp2;
struct BIT {
	ll c[N];
	void update(int x, int d) { while (x <= n) c[x] += d, x += x & -x; }
	ll query(int x) { ll y = 0; while (x) y += c[x], x -= x & -x; return y; }
} t1[2][2], t2[2][2];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &p[i].x, &p[i].y);
		p[i].xx = p[i].x + p[i].y;
		p[i].yy = p[i].x - p[i].y;
	}
	sort(p + 1, p + 1 + n, cmp);
	for (int i = 1; i <= n; i++) b[i] = p[i].yy;
	sort(b + 1, b + 1 + n);
	len = unique(b + 1, b + 1 + n) - b - 1;
	for (int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + 1 + len, p[i].yy) - b;
	for (int i = n; i >= 1; i--) {
		int fx = abs(p[i].x) & 1, fy = abs(p[i].y) & 1;
		ans += sum[fx][fy] - (ll)p[i].xx * cnt[fx][fy];
		ans += sum[fx ^ 1][fy ^ 1] - (ll)p[i].xx * cnt[fx ^ 1][fy ^ 1];
		sum[fx][fy] += p[i].xx, cnt[fx][fy]++;
		tmp1 = t1[fx][fy].query(len) - t1[fx][fy].query(a[i]);
		tmp2 = t2[fx][fy].query(len) - t2[fx][fy].query(a[i]);
		ans += tmp1 - tmp2 * p[i].yy;
		tmp1 = t1[fx][fy].query(a[i] - 1);
		tmp2 = t2[fx][fy].query(a[i] - 1);
		ans += tmp2 * p[i].yy - tmp1;
		tmp1 = t1[fx ^ 1][fy ^ 1].query(len) - t1[fx ^ 1][fy ^ 1].query(a[i]);
		tmp2 = t2[fx ^ 1][fy ^ 1].query(len) - t2[fx ^ 1][fy ^ 1].query(a[i]);
		ans += tmp1 - tmp2 * p[i].yy;
		tmp1 = t1[fx ^ 1][fy ^ 1].query(a[i] - 1);
		tmp2 = t2[fx ^ 1][fy ^ 1].query(a[i] - 1);
		ans += tmp2 * p[i].yy - tmp1;
		t1[fx][fy].update(a[i], p[i].yy);
		t2[fx][fy].update(a[i], 1);
	}
	printf("%lld", ans / 2);
}
```

---

## 作者：james1BadCreeper (赞：2)

无脑做法。

将网格黑白染色，任意同色点之间都能互相到达，要求的是同色点之间的切比雪夫距离之和，那么转成曼哈顿距离，直接做即可。

如果你不知道什么是切比雪夫距离转曼哈顿距离，可以拉到文末。

```cpp
#include <bits/stdc++.h>
using namespace std; 
typedef long long i64; 

int n; 
int x[200005], y[200005], xx[200005], yy[200005]; 
i64 px[200005], py[200005]; 

i64 solve(vector<pair<int, int>> poi) {
    int n = 0; 
    for (auto [u, v] : poi) ++n, xx[n] = x[n] = u + v, yy[n] = y[n] = u - v; 
    sort(xx + 1, xx + n + 1); sort(yy + 1, yy + n + 1); 
    for (int i = 1; i <= n; ++i) px[i] = px[i - 1] + xx[i], py[i] = py[i - 1] + yy[i]; 
    i64 ans = 0;  
    for (int i = 1; i <= n; ++i) {
        int k1 = lower_bound(xx + 1, xx + n + 1, x[i]) - xx; 
        int k2 = lower_bound(yy + 1, yy + n + 1, y[i]) - yy; 
        i64 v1 = 1ll * k1 * x[i] - 1ll * (n - k1) * x[i] + px[n] - 2ll * px[k1]; 
        i64 v2 = 1ll * k2 * y[i] - 1ll * (n - k2) * y[i] + py[n] - 2ll * py[k2]; 
        ans += v1 + v2; 
    }
    assert(ans % 4 == 0); 
    return ans / 4; 
}

int main(void) {
    ios::sync_with_stdio(0); 
    vector<pair<int, int>> v1, v2; 
    cin >> n; 
    for (int i = 1; i <= n; ++i) {
        int u, v; cin >> u >> v; 
        if (u + v & 1) v1.emplace_back(u, v); 
        else v2.emplace_back(u, v); 
    }
    cout << solve(v1) + solve(v2) << "\n"; 
    return 0; 
}
```

---

曼哈顿距离是指 $x,y$ 坐标的差的和，而切比雪夫距离指的是差的最大值。

从曼哈顿距离转化成切比雪夫距离，令 $x_i'=x_i+y_i,y_i'=x_i-y_i$，反着转的时候反过来解一下二元一次方程组就行。


> [\[TJOI2013\] 松鼠聚会](https://www.luogu.com.cn/problem/P3964)。
> 
> 给定平面上的 $n$ 个点，求其余点到一点的切比雪夫距离之和的最小值。


容易解出转为曼哈顿距离后点的坐标为 $\left(\cfrac{x+y}{2},\cfrac{x-y}{2}\right)$。枚举中心点 $i$，分别讨论横纵坐标的贡献即可直接计算。[代码](https://uoj.ac/submission/663385)。

---

