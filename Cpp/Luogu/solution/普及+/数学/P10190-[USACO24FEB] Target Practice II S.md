# [USACO24FEB] Target Practice II S

## 题目背景

**注意：本题的时间限制为 2.5 秒，通常限制的 1.25 倍。**

**注意：这个问题涉及到的整数可能需要使用 64 位整数型（例如，C/C++ 中的 `long long`）。**

## 题目描述

巴黎哞运会即将来临，Farmer John 正在对他的奶牛队进行射箭训练！他在二维坐标平面上设置了以下练习。

有 $N$（$1\le N\le 4\cdot 10^4$）个四边与坐标轴平行的矩形箭靶和 $4N$ 头奶牛。每头牛都必须被分配一个不同的箭靶顶点。对于 $1\le i\le N$，在时刻 $i$：

1. 箭靶 $i$ 出现。
2. 分配其顶点的 $4$ 头奶牛向它们射箭。
3. 如果奶牛的箭在击中所分配的顶点之前穿过箭靶内部，或未命中，则奶牛们的练习失败。
4. 箭靶消失，为下一个箭靶腾出空间。

每头牛都位于 $y$ 轴（$x=0$）上，每个箭靶都是一个矩形，其中箭靶 $i$ 的左下顶点坐标为 $(X_1,y^{(i)}_1)$，右上顶点坐标为 $(x^{(i)}_2,y^{(i)}_2)$。所有坐标满足 $1\le X_1<x^{(i)}_2\le 10^9$ 以及 $1\le y^{(i)}_1<y^{(i)}_2\le 10^9$（注意：$X_1$ 对于每个箭靶都是相同的）。

此外，每头奶牛都有一个正在钻研的「瞄准」角度。因此她们在射箭时会转向特定的角度。考虑到她们的箭从她们的位置沿直线射向指定的顶点，奶牛 $i$ 的箭的轨迹可以用轨迹的斜率 $s_i$（$0<|s_i|<10^9$）来表示。

为了能够仔细检查奶牛们的技术，Farmer John 希望尽量缩短最远的奶牛之间的距离。如果 Farmer John 以最佳方式给每头奶牛分配箭靶顶点并将她们放置在 $y$ 轴上，你能否帮助他求出最远奶牛之间的最小距离是多少，或者奶牛是否总是会练习失败？

每个测试点包含 $T$（$1\le T\le 10$）个独立的测试用例。输入保证所有测试用例的 $N$ 之和不超过 $4\cdot 10^4$。 

## 说明/提示

### 样例解释

对于测试用例 $1$，一个最佳分配方案是分别为奶牛 $1-8$ 分配以下目标顶点：

$$(6,1),(6,3),(3,4),(3,6),(1,4),(1,3),(1,6),(1,1)$$

这得出了奶牛 $1-8$ 的 $y$ 坐标如下：

$$−5,9,−2,12,1,6,2,5$$

这给出了最小距离 $12−(−5)=17$。

第二个测试用例的答案是不可能的原因之一是，如果箭不穿过箭靶 $1$ 的内部，不可能射中 $(6,3)$ 处的顶点（箭靶 $1$ 的右上顶点）。

### 测试点性质

- 测试点 $2$：对于所有的 $1\le i\le 4N$，$|S_i|$ 均相同。
- 测试点 $3-9$：所有测试用例的 $N$ 之和不超过 $1000$。
- 测试点 $10-15$：没有额外限制。

## 样例 #1

### 输入

```
3
2 1
1 3 6
4 6 3
1 -1 2 -2 3 -3 4 -4
2 1
1 3 6
4 6 3
1 1 2 2 3 3 4 4
2 1
1 3 3
4 6 3
1 -1 2 -2 3 -3 4 -4```

### 输出

```
17
-1
11```

# 题解

## 作者：tiko_tao (赞：8)

# P10190 [USACO24FEB] Target Practice II S

---
[题墓链接](https://www.luogu.com.cn/problem/P10190)

做法：二分答案。  
与一般的二分答案有些区别，一般的二分是二分结果的，是距离，但这个题没有具体的端点，于是我们考虑二分两个**端点**。

题意简述：

说实话本题我理解了挺久的，发现画个图会更好理解。

平面直角坐标系中，共有 $n$ 个矩形(依次出现)，我们认为每个矩形的**四个顶点**为奶牛需要射击的靶子，题目给出 $4n$ 头**在 y 轴上的奶牛**的**射击斜率**，我们要给每个奶牛分配一个**一一对应的**靶子，然后奶牛就会在 y 轴上有一个对应的位置。  
要求：射击的过程中**不穿过**矩形内部(因为矩形依次出现，所以我们只需考虑单个矩形即可)。  
最终要使最高的奶牛和最低的奶牛的距离差值**最小**。

注意题目中的细节：每个矩形的**左边那条边**所在的 x (即 $X1$ )不变。  
下面给出样例(第一个)。

```
2 1
1 3 6
4 6 3
1 -1 2 -2 3 -3 4 -4
```
![](https://cdn.luogu.com.cn/upload/image_hosting/rnq1jabl.png)  
可以看到两个矩形的左边的边都在 $x = 1$ 轴上。

现在我们考虑怎么把奶牛放在 y 轴上。  
经过简单分析题目的要求，我们可以发现对于每个矩形**右上**的顶点，我们只能用一个射击斜率为**负数**的奶牛来打。  
同理，对于**右下角**，我们只能用斜率**正数**的奶牛来打。

因此，当我们把正数或负数的奶牛用完之后，如果矩形右端的对应顶点**没有被打完**，这就是题目中的无解情况，输出 -1。

无解的情况处理完了，那怎么使最高的奶牛和最低奶牛这个距离差最小呢？

首先，我们是可以贪心确定每个顶点对应的是正斜率的奶牛还是负斜率的奶牛的。  
右顶点就不赘述了。对于左顶点，因为正斜率的奶牛射击时肯定是在要射击顶点的**下方**，而负斜率的奶牛相反，在**上方**。又因为左顶点都在同一根轴上，为了满足距离差最小，我们会将**正斜率**的奶牛尽量分给**靠上的**顶点，而负斜率就是**靠下的**顶点。  
先用两个 vector 数组分别存哪些顶点给正斜率，哪些给负斜率，方便后面的检查。

一般看到最值，不难想到二分的做法。但是这个题没法直接二分这个距离，因此我们要二分最高奶牛和最低奶牛的**位置**，然后再判断有没有一种方案，可以让左右奶牛都在这个范围内，是满足单调性的。

至于怎么判断，我用一个图解释。  
![](https://cdn.luogu.com.cn/upload/image_hosting/02omiqrb.png)  
假设我们当前二分到这个绿色的 min 点，我们要保证所有奶牛的位置**大于等于**它。拿所有奶牛的斜率算位置有点麻烦？那我们就考虑拿斜率比较呗 qwq。

我们把点 min 与所有矩形上的顶点连一条边(图上仅连了一条)，我们可以计算这些边的斜率。显然，一个奶牛的位置在 min 之上，当且仅当这个奶牛的斜率**小于等于**我们所计算的斜率。

我们需要一个东西，它可以快速找到一堆数中**大于等于一个数的最小的数**，并且把它删除(每只奶牛仅用一次)。

是的没错就是集合。  
我们把正斜率的奶牛和负斜率的奶牛分别存到两个集合里面方便判断。由于不知道有没有斜率重复的奶牛，我们用多重集合。

以上是求 min 的过程，求 max 同理，有一些细节上的不同，所以要写两个二分。

因为两个二分有大部分重复内容，代码有点长。  
复杂度 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
#define rep(i,a,n) for(int (i)=(a);(i)<=(n);(i)++)
#define pre(i,a,n) for(int (i)=(a);(i)>=(n);(i)--)
#define ull unsigned long long
#define int long long
#define y11 y1
#define pb push_back
using namespace std;
const int N = 40000 + 10;
struct node
{
	int x, y;
	bool operator < (const node &nd) const { 
		return y < nd.y;
	}
};
int n, x1;
int s[N];
multiset<int> st1, st2; //分别存斜率大于0和斜率小于零的牛 
vector<node> va, vb, vc; //分别存最终用斜率大于0的牛射击的点和用斜率小于0射击的点 
bool check1(int mid)
{
	multiset<int> st = st1;
	for (node &t : va)
	{
		int s = (t.y - mid) / t.x;
		auto k = st.upper_bound(s);
		if (k == st.begin()) return false; 
		k--; //取 >s 的前一个数 
		st.erase(k);
	}
	return true;
}
bool check2(int mid)
{
	multiset<int> st = st2;
	for (node &t : vb)
	{
		int s = (t.y - mid) / t.x;
		auto k = st.lower_bound(s); //取大于等于s的第一个数 
		if (k == st.end()) return false; 
		st.erase(k);
	}
	return true;
}
void init()
{
	va.clear(), vb.clear(), vc.clear();
	st1.clear(), st2.clear(); 
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--)
	{
		init(); //多测清空 
		cin >> n >> x1;
		rep(i, 1, n)
		{
			int y1, y2, x2;
			cin >> y1 >> y2 >> x2;
			va.pb(node{x2, y1}); //右下角 
			vb.pb(node{x2, y2}); //右上角
			vc.pb(node{x1, y1}); //轴上的点暂时不确定，先存起来
			vc.pb(node{x1, y2});
		}
		rep(i, 1, 4 * n) 
		{
			int s; cin >> s;
			if (s > 0) st1.insert(s); //正斜率集合
			else st2.insert(s); //负斜率集合
		}
		if (st1.size() < n || st2.size() < n) //右侧的端点无法安排牛 
		{
			cout << -1 << "\n";
			continue; 
		}
		sort(vc.begin(), vc.end()); //将轴上的点按高低排序 
		int cnt = n;
		for (node t : vc)
		{
			if (cnt < st1.size()) va.pb(t), cnt++; //分配轴上的点
			else vb.pb(t);
		}
		int r = vc[0].y, l = -1e18, mid, mi, mx = 0;
		while (l <= r) //二分最大的最小端点
		{
			mid = l + r >> 1;
			if (check1(mid))
			{
				mi = mid;
				l = mid + 1;
			}
			else r = mid - 1;
		}
		l = vc.back().y, r = 1e18;
		while (l <= r) //二分最小的最大端点
		{
			mid = l + r >> 1;
			if (check2(mid))
			{
				mx = mid;
				r = mid - 1;
			}
			else l = mid + 1;
		}
		cout << mx - mi << "\n";
	}
	return 0;
}
```
完结撒花\OWO/。

---

## 作者：EricWan (赞：7)

**作者提醒**：这是一篇没有证明的“乱搞优化贪心暴力”的题解，如果你不是为了学习骗分方法，请参考其它题解。

这篇题解只是为了纪念这种离谱的最优解的。

我们充分发扬人类的智慧：

根据样例，我们可以想到：靶心可以被分成三类点，左侧的，右上的，右下的。

左侧点肯定没有匹配限制，右上点一定匹配负斜率，右下点一定匹配正斜率。（所以如果正斜率或者负斜率不够 $N$，就可以直接无解了。）

还可以证明：左侧的点一定是匹配绝对值较大的斜率。

之后，我们似乎可以观察到：右侧的两类点一定是可以通过“从绝对值大到绝对值小枚举斜率”后“找出一个点使得匹配之后牛的位置最靠近中间”进行贪心暴力匹配。（为什么这是对的呢，我也不知道，如果别的题解写了，可以去看别的题解的证明，我没看。）

于是，我们就有显而易见的 $O(N^2)$ 纯暴力了。（[不错，洛谷神机跑出来 14 个点](https://www.luogu.com.cn/record/204733547)）

```cpp
#include <bits/stdc++.h>
#define int long long
#define MAXN 1600005
using namespace std;
bool right_up_flag[MAXN], right_down_flag[MAXN];
int n, x_1, l[MAXN], s[MAXN], positive[MAXN], negative[MAXN];
int y_1[MAXN], y_2[MAXN], x_2[MAXN], up_limit, down_limit;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	int _;
	cin >> _;
	while (_--) {
		l[0] = positive[0] = negative[0] = 0;
		up_limit = -1e18;
		down_limit = 1e18;
		cin >> n >> x_1;
		for (int i = 1; i <= n; i++) {
			cin >> y_1[i] >> y_2[i] >> x_2[i];
			if (y_1[i] > y_2[i]) {
				swap(y_1[i], y_2[i]);
			}
			l[++l[0]] = y_1[i];
			l[++l[0]] = y_2[i];
			right_up_flag[i] = 1;
			right_down_flag[i] = 1;
		}
		for (int i = 1; i <= 4 * n; i++) {
			cin >> s[i];
			if (s[i] > 0) {
				positive[++positive[0]] = s[i];
			}
			else if (s[i] < 0) {
				negative[++negative[0]] = -s[i];
			}
		}
		if (positive[0] < n || negative[0] < n) {
			cout << "-1\n";
			continue;
		}
		sort(positive + 1, positive + positive[0] + 1);
		sort(negative + 1, negative + negative[0] + 1);
		sort(l + 1, l + 2 * n + 1);
		for (int i = n; i >= 1; i--) {
			int maxid = 0, maxn = -1e18;
			for (int j = 1; j <= n; j++) {
				if (!right_down_flag[j]) {
					continue;
				}
				if (y_1[j] - x_2[j] * positive[i] > maxn) {
					maxn = y_1[j] - x_2[j] * positive[i];
					maxid = j;
				}
			}
			down_limit = min(maxn, down_limit);
			right_down_flag[maxid] = 0;
		}
		for (int i = n; i >= 1; i--) {
			int maxid = 0, maxn = 1e18;
			for (int j = 1; j <= n; j++) {
				if (!right_up_flag[j]) {
					continue;
				}
				if (y_2[j] + x_2[j] * negative[i] < maxn) {
					maxn = y_2[j] + x_2[j] * negative[i];
					maxid = j;
				}
			}
			up_limit = max(maxn, up_limit);
			right_up_flag[maxid] = 0;
		}
		int I = 2 * n;
		for (int i = positive[0]; i > n; i--) {
			down_limit = min(down_limit, l[I] - x_1 * positive[i]);
			I--;
		}
		I = 1;
		for (int i = negative[0]; i > n; i--) {
			up_limit = max(up_limit, l[I] + x_1 * negative[i]);
			I++;
		}
		cout << up_limit - down_limit << endl;
	}
	return 0;
}
```

~开大招直接可以过。~

然后我们发现那一个 T 飞的点是一个特殊性质，我们可以~考虑数据点分治~想想为什么会被那种数据卡。

原因是瓶颈处太慢了。

优化方法类似 Dinic 中的当前弧优化，记录一下第一个 `right_down_flag[j]` 仍然是 $1$ 的位置然后跳过去。

交一发，还是看不见边。

继续优化，我们~发现~猜测最终的可以匹配的 $j$ 一定不会离当前弧优化的当前弧太远，因此可以将枚举上界改为 `min(n, min_not0_right_down_flag + 1000)` 试试，然后就过了。

code：

```cpp
#include <bits/stdc++.h>
#define int long long
#define MAXN 1600005
#define K 500
#define min(x,y) (((x)<(y))?(x):(y))
#define max(x,y) (((x)>(y))?(x):(y))
#define abs(x) (((x)<(0))?(-(x)):(x))
#define swap(a,b) a^=b^=a^=b
using namespace std;
bool right_up_flag[MAXN], right_down_flag[MAXN];
int n, x_1, l[MAXN], s[MAXN], positive[MAXN], negative[MAXN];
int y_1[MAXN], y_2[MAXN], x_2[MAXN], up_limit, down_limit;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	register signed _;
	cin >> _;
	while (_--) {
		l[0] = positive[0] = negative[0] = 0;
		up_limit = -1e18;
		down_limit = 1e18;
		cin >> n >> x_1;
		for (register signed i = 1; i <= n; i++) {
			cin >> y_1[i] >> y_2[i] >> x_2[i];
			if (y_1[i] > y_2[i]) {
				swap(y_1[i], y_2[i]);
			}
			l[++l[0]] = y_1[i];
			l[++l[0]] = y_2[i];
			right_up_flag[i] = 1;
			right_down_flag[i] = 1;
		}
		for (register signed i = 1; i <= 4 * n; i++) {
			cin >> s[i];
			if (s[i] > 0) {
				positive[++positive[0]] = s[i];
			}
			else if (s[i] < 0) {
				negative[++negative[0]] = -s[i];
			}
		}
		if (positive[0] < n || negative[0] < n) {
			cout << "-1\n";
			continue;
		}
		sort(positive + 1, positive + positive[0] + 1);
		sort(negative + 1, negative + negative[0] + 1);
		sort(l + 1, l + 2 * n + 1);
		register signed min_not0_right_down_flag = 1;
		register signed min_not0_right_up_flag = 1;
		for (register signed i = n; i >= 1; i--) {
			register int maxid = 0, maxn = -1e18;
            const int j_limit = min(n, min_not0_right_down_flag + K);
			for (register signed j = min_not0_right_down_flag; j <= j_limit; j++) {
				if (!right_down_flag[j]) {
					continue;
				}
				if (y_1[j] - x_2[j] * positive[i] > maxn) {
					maxn = y_1[j] - x_2[j] * positive[i];
					maxid = j;
				}
			}
			down_limit = min(maxn, down_limit);
			right_down_flag[maxid] = 0;
			while (!right_down_flag[min_not0_right_down_flag] && min_not0_right_down_flag < n) {
				min_not0_right_down_flag++;
			}
		}
		for (register signed i = n; i >= 1; i--) {
			register int maxid = 0, maxn = 1e18;
            const int j_limit = min(n, min_not0_right_up_flag + K);
			for (register signed j = min_not0_right_up_flag; j <= j_limit; j++) {
				if (!right_up_flag[j]) {
					continue;
				}
				if (y_2[j] + x_2[j] * negative[i] < maxn) {
					maxn = y_2[j] + x_2[j] * negative[i];
					maxid = j;
				}
			}
			up_limit = max(maxn, up_limit);
			right_up_flag[maxid] = 0;
			while (!right_up_flag[min_not0_right_up_flag] && min_not0_right_up_flag < n) {
				min_not0_right_up_flag++;
			}
		}
		register signed I = 2 * n;
		for (register signed i = positive[0]; i > n; i--) {
			down_limit = min(down_limit, l[I] - x_1 * positive[i]);
			I--;
		}
		I = 1;
		for (register signed i = negative[0]; i > n; i--) {
			up_limit = max(up_limit, l[I] + x_1 * negative[i]);
			I++;
		}
		cout << up_limit - down_limit << "\n";
	}
	return 0;
}
```

---

## 作者：Fire_flame (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/P10190)

一个二分答案出那么难（

## $\mathtt{Solution}$

首先发现一个靶子的右上角对应的斜率一定为负，右下角对应的斜率为正，剩下的随便。

也就是说，如果斜率为正或为负的数量小于 $n$，输出 $-1$。

注意到，对左边的点按 $y$ 坐标从大到小排序，最前面的几个对应的斜率为正，其他的为负，这样选一定不劣。

现在我们就确定哪些点对应的斜率为正，哪些对应的为负了。

然后考虑二分答案，可以发现斜率的选择是单调的，也就是说，如果你选了斜率为 $x$ 的超出了范围，那么选择斜率绝对值大于 $x$ 的也不行。

所以把正、负斜率分别按照绝对值排序，对于每一个点求出最后一个能满足要求的斜率，然后判断一下即可。

代码（3.2k）：
```cpp
#include<bits/stdc++.h>
#define int __int128
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(!isdigit(ch)){if(ch == '-')f = -1;ch = getchar();}
	while(isdigit(ch)){s = s * 10 + ch - '0';ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 2e5 + 5;
struct node{
	int x, y;
	bool operator < (const node &zzz)const{
		return y > zzz.y;
	}
}pt[MAXN], pt2[MAXN], pt3[MAXN];
int t, n, x, cnta, cntb, cntx, cnty, a[MAXN], b[MAXN], c[MAXN], p[MAXN], q[MAXN], num[MAXN];
bool check(int k){
	for(int i = 1;i <= cnta;i ++)num[i] = 0;
	for(int i = 1;i <= cnta;i ++){
		if((pt[i].y - pt[i].x * q[1]) < k)return false;
		int lpos = 1, rpos = cnta, res = 0;
		while(lpos <= rpos){
			int mid = (lpos + rpos) / 2;
			if((pt[i].y - pt[i].x * q[mid]) < k)rpos = mid - 1;
			else res = mid, lpos = mid + 1;
		}
		num[res] ++;
//		printf("%lld %lld %lld %lld %lld\n", i, k, res, pt[i].x, pt[i].y);
	}
	for(int i = 1;i <= cnta;i ++){
		num[i] += num[i - 1];
		if(num[i] > i)return false;
	}
	return true;
}
bool check2(int k){
	for(int i = 1;i <= cntb;i ++)num[i] = 0;
	for(int i = 1;i <= cntb;i ++){
		if((pt2[i].y - pt2[i].x * p[1]) > k)return false;
		int lpos = 1, rpos = cntb, res = 0;
		while(lpos <= rpos){
			int mid = (lpos + rpos) / 2;
			if((pt2[i].y - pt2[i].x * p[mid]) > k)rpos = mid - 1;
			else res = mid, lpos = mid + 1;
		}
		num[res] ++;
	}
	for(int i = 1;i <= cntb;i ++){
		num[i] += num[i - 1];
		if(num[i] > i)return false;
	}
	return true;
}
signed main(){
//	freopen("P10190_3.in", "r", stdin);
//	freopen("a.out", "w", stdout);
	t = read();
	while(t --){
		n = read(), x = read(), cnta = cntb = cntx = cnty = 0;
		for(int i = 1;i <= n;i ++)a[i] = read(), b[i] = read(), c[i] = read();
		for(int i = 1;i <= 4 * n;i ++){
			int x = read();
			if(x < 0)p[++ cntx] = x;
			else q[++ cnty] = x;
		}
		if(cntx < n || cnty < n){
			puts("-1");
			continue;
		}
		for(int i = 1;i <= n;i ++){
			pt3[2 * i - 1] = {x, a[i]};
			pt3[2 * i] = {x, b[i]};
		}
		sort(pt3 + 1, pt3 + 2 * n + 1);
		sort(p + 1, p + cntx + 1, greater<int>());
		sort(q + 1, q + cnty + 1);
		cntx -= n, cnty -= n;
		int tot = 0;
		for(int i = 1;i <= n;i ++){
			pt[++ cnta] = {c[i], a[i]};
			pt2[++ cntb] = {c[i], b[i]};
			tot ++;
			if(tot <= cnty)pt[++ cnta] = pt3[tot];
			else pt2[++ cntb] = pt3[tot];
			tot ++;
			if(tot <= cnty)pt[++ cnta] = pt3[tot];
			else pt2[++ cntb] = pt3[tot];
		}
//		for(int i = 1;i <= cnta;i ++)printf("%lld %lld\n", pt[i].x, pt[i].y);
//		puts("");
//		for(int i = 1;i <= cntb;i ++)printf("%lld %lld\n", pt2[i].x, pt2[i].y);
//		puts("");
//		for(int i = 1;i <= cnta;i ++)printf("%lld %lld\n", p[i], q[i]);
		int lpos = -5e18, rpos = 5e18, maxx = 0, minn = 0;
		while(lpos <= rpos){
			int mid = (lpos + rpos) / 2;
			if(check(mid))maxx = mid, lpos = mid + 1;
			else rpos = mid - 1;
		}
		lpos = -5e18, rpos = 5e18;
		while(lpos <= rpos){
			int mid = (lpos + rpos) / 2;
			if(check2(mid))minn = mid, rpos = mid - 1;
			else lpos = mid + 1;
		}
		write(minn - maxx), puts("");
	}
	return 0;
}
```

---

## 作者：LuckiestShawn (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P10190)

可以发现箭靶的右上角的顶点一定是被运动斜率大于 $0$ 的箭射中，右下角的顶点一定是被斜率小于 $0$ 的箭射中，而射中箭靶左边两个顶点的箭的运动斜率则无限制。

为了简化语言，这里记箭靶 $i$ 左侧两个的顶点 $a$，右上角的为 $b$，右下角的为 $c$，$k_u$ 为一支斜率为 $k_u$ 的箭射中顶点 $u$。

不难发现题目即求 $y$ 坐标最大的奶牛和 $y$ 坐标最小的奶牛的坐标差。

如果纯贪心的话，会发现存在后效性，无法确定每个顶点应该选择哪个 $k$。

考虑先确定最大的 $y$ 坐标 $y_{max}$，即确定奶牛纵坐标上界。不难发现坐标为 $y_{max}$ 的奶牛射出的箭的斜率一定小于 $0$。先遍历 $b_i$，再遍历 $a_i$（需要先对 $a_i$ 从小到大排序），遍历到的顶点 $u$ 的 $k_u$ 从可重集 $\{k_i|i\in[1,4n],k_i<0\}$ 中选择，每选出一个就把选出的 $k$ 从集合中删去，且 $|k_u|$ 应尽可能大。

先遍历 $b_i$ 的原因是 $b_i$ 只能接收 $k<0$ 的箭，而 $a_i$ 无限制，如果先遍历 $a_i$ 可能会把这些箭消耗完，故先遍历 $b_i$，再遍历 $a_i$。在遍历过程中若找不到一个满足条件的 $k$，则说明此 $y_{max}$ 不合法；若遍历过程中 $k$ 的集合空了，则此顶点需要 $k>0$ 的箭，而 $y_{max}$ 一定大于等于任何一个顶点的纵坐标，故此节点的 $k$ 的选法不会影响到 $y_{max}$。

$y_{min}$ 同理，$y_{min}$ 和 $y_{max}$ 的合法性具有单调性，可以二分查找。

下面是证明 $y_{max}$ 的选取不会影响 $y_{min}$ 的选取。

考虑 $y_{max}+1\to y_{max}$。此变化可能会造成一些 $a_i,b_i$ 所选择的 $|k|$ 需要变小一点才能符合条件，但最终选择的 $k$ 永远不会大于 $0$，且选择 $k<0$ 的箭的点集一定不会变。又因为 $y_{min}$ 只与 $k>0$ 的箭和选择 $k>0$ 的箭的点集有关系，故命题得证。时间复杂度 $O(n\log{n}\log{Y})$。

```cpp
#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <set>
#define int long long
using namespace std;
struct XY{int x,y;};
vector <XY> a,b,c;
vector <int> up,dn;
multiset <int> rup,rdn;
void init(){
	a.clear(), b.clear(), c.clear();
	up.clear(), dn.clear();
}
bool checkup(int mx){
	rdn.clear();
	for(int k:dn) rdn.insert(k);
	for(XY p:b){
		auto k = rdn.upper_bound( (mx-p.y)/p.x );
		if( k == rdn.begin() ) return false;
		rdn.erase(--k);
	}
	for(int i=a.size()-1;i>=0;i--){
		XY p = a[i];
		if( rdn.empty() ) break;
		auto k = rdn.upper_bound( (mx-p.y)/p.x );
		if( k == rdn.begin() ) return false;
		rdn.erase(--k);
	}
	return true;
}
bool checkdn(int mi){
	rup.clear();
	for(int k:up) rup.insert(k);
	for(XY p:c){
		auto k = rup.upper_bound( (p.y-mi)/p.x );
		if( k == rup.begin() ) return false;
		rup.erase(--k);
	}
	for(int i=0;i<a.size();i++){
		XY p = a[i];
		if( rup.empty() ) break;
		auto k = rup.upper_bound( (p.y-mi)/p.x );
		if( k == rup.begin() ) return false;
		rup.erase(--k);
	}
	return true;
}
int T,n,x1,k,mx,mi;
signed main(){
	scanf("%lld",&T);
	while(T--){
		init();
		scanf("%lld%lld",&n,&x1);
		for(int i=1,y1,y2,x2;i<=n;i++){
			scanf("%lld%lld%lld",&y1,&y2,&x2);
			a.push_back({x1,y1}), a.push_back({x1,y2});
			b.push_back({x2,y2}), c.push_back({x2,y1});
		}
		for(int i=1;i<=n*4;i++){
			scanf("%lld",&k);
			if( k > 0 ) up.push_back(k);
			else dn.push_back(-k);
		}
		
		if( up.size() < n || dn.size() < n )
			{ puts("-1"); continue; }
		
		sort(a.begin(),a.end(),[](XY a,XY b){ return a.y > b.y; });
		sort(b.begin(),b.end(),[](XY a,XY b){ return a.y > b.y; });
		sort(c.begin(),c.end(),[](XY a,XY b){ return a.y < b.y; });
		
		int l = -2e18, r = 2e18, mid;
		while( l < r ){
			mid = (l+r)>>1;
			if( checkup(mid) )
				r = mid;
			else l = mid+1;
		}
		mx = r;
		
		l = -2e18, r = 2e18, mid;
		while( l < r ){
			mid = (l+r+1)>>1;
			if( checkdn(mid) )
				l = mid;
			else r = mid-1;
		}
		mi = r;
		
		printf("%lld\n",mx-mi);
		
	}
	return 0;
}
```

---

## 作者：Suite_No1_G (赞：4)

省流：比赛时题没看懂爆零，后来看懂题后一遍过。

------------
分开考虑上界和下界，则答案为最小上界减去最大下界。

分析了一下，发现矩形右下角的点只能由斜率是正数的牛射掉（从下往上射箭），矩形右上角的点只能由斜率是负数的牛射掉（从上往下射箭），因为题目说了不允许箭穿过矩形内部。

对于矩形左上角和左下角，发现都在一条直线上，那么这条直线上面部分的点就从下往上射掉（即斜率为正），直线下面的点就从上往下射掉（即斜率为负）。

然后，根据这个性质，如果斜率为正的牛数量小于 $n$ 或者斜率为负的牛数量小于 $n$，则无解。

以下界为例（上界处理方法同理，只不过注意符号），我们发现答案具有单调性，所以可以二分出最大上界。假设当前二分到 $mid$。

 检验的时候贪心处理：对于每一个点（矩形右下角），设其坐标为 $(x,y)$，则找到斜率的 **绝对值** 最大的一头牛，用这头牛射掉这个点，设斜率为 $s$，我们发现 $y-x×s≥mid$。找到 **绝对值** 最大的牛，并用这头牛射掉，并删除这头牛。
 
这个贪心方法是正确的，因为如果一个点能用斜率为 $s1$ 和 $s2$ 的点射掉，且 $s1≥s2$，（此情况为下界），那么用斜率为 $s1$ 的牛来射这个点不会劣。

这样，我们 $O(n)$ 枚举点，$O(n)$ 枚举斜率，再加上二分的复杂度，时间复杂度为 $O(n^2 \log V)$，可以过前面 $9$ 个点。

考虑优化。我们发现瓶颈在于 $O(n)$ 枚举斜率，我们可以使用 multiset 来记录斜率，然后查找删除，时间复杂度优化到 $O(\log n)$。

综上，可以优化到 $O(n \log n \log V)$。注意上下界的区别。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
struct node{
	int x,y;
};
node rightDown[maxn],rightUp[maxn],Line[maxn];
int init[maxn];
multiset<int> slope_pos, slope_nega;
int n,X;
int tot1=0,tot2=0,tot3=0;
int len1=0,len2=0;
int P[maxn],N[maxn];

bool cmp(node i,node j){
	return i.y>j.y;
}

bool check1(int mid){
	slope_pos.clear();
	for (int i=1;i<=len1;i++) slope_pos.insert(P[i]);
	int left=len1;
	for (int i=1;i<=tot1;i++){
		int need=(rightDown[i].y-mid)/rightDown[i].x;
		multiset<int>::iterator it=slope_pos.upper_bound(need);
		if (it==slope_pos.begin()) return false;
		it--;
		int num=(*it);
		slope_pos.erase(slope_pos.find(num));
		left--;
	}
	
	for (int i=1;i<=left;i++){
		int need=(Line[i].y-mid)/X;
		multiset<int>::iterator it=slope_pos.upper_bound(need);
		if (it==slope_pos.begin()) return false;
		it--;
		int num=(*it);
		slope_pos.erase(slope_pos.find(num));
	}
	return true;
}

bool check2(int mid){
	slope_nega.clear();
	for (int i=1;i<=len2;i++) slope_nega.insert(N[i]);
	int left=len2;
	for (int i=1;i<=tot2;i++){
		int need=(mid-rightUp[i].y)/rightUp[i].x;
		multiset<int>::iterator it=slope_nega.upper_bound(need);
		if (it==slope_nega.begin()) return false;
		it--;
		int num=(*it);
		slope_nega.erase(slope_nega.find(num));
		left--;
	}
	
	for (int i=tot3-left+1;i<=tot3;i++){
		int need=(mid-Line[i].y)/X;
		multiset<int>::iterator it=slope_nega.upper_bound(need);
		if (it==slope_nega.begin()) return false;
		it--;
		int num=(*it);
		slope_nega.erase(slope_nega.find(num));
	}
	return true;
} 

void solve(){
	slope_pos.clear(); slope_nega.clear();
	scanf("%lld%lld",&n,&X);
	tot1=0,tot2=0,tot3=0;
	len1=0,len2=0;
	for (int i=1;i<=n;i++){
		int y_1,y_2,x_2;
		scanf("%lld%lld%lld",&y_1,&y_2,&x_2);
		rightDown[++tot1]=(node){x_2,y_1};
		rightUp[++tot2]=(node){x_2,y_2};
		Line[++tot3]=(node){X,y_1}, Line[++tot3]=(node){X,y_2};
	}
	sort(Line+1,Line+tot3+1,cmp);
	
	for (int i=1;i<=4*n;i++){
		int num; scanf("%lld",&num);
		if (num>0) P[++len1]=num;
		else N[++len2]=-num;	
	}
	
	if (len1<n||len2<n){
		printf("-1\n");
		return;
	}
	
	int l=-2e18,r=2e18;
	int best1=-2e18,best2=2e18;
	while (l<=r){
		int mid=(l+r)/2;
		if (check1(mid)){
			best1=mid;
			l=mid+1;
		}else r=mid-1;
	}
	
	if (best1==-2e18){
		printf("-1\n"); return;
	}
	
	l=best1,r=2e18;
	while (l<=r){
		int mid=(l+r)/2;
		if (check2(mid)){
			best2=mid;
			r=mid-1;
		}else l=mid+1;
	}
	if (best2==2e18){
		printf("-1\n"); return;
	}	
	printf("%lld\n",best2-best1);
}

signed main(){
//	freopen("random.in","r",stdin);
//	freopen("wrong.out","w",stdout);
	int T;
	scanf("%lld",&T);
	while (T--){
		solve();
	}
	return 0;
}
```


---

## 作者：zjc5 (赞：1)

求最小距离，其实是让上界尽可能小，下界尽可能大。

于是把斜率分成正负两种，一个靶子右上的点只能被负斜率设中，右下的点只能被正斜率设中，左侧的点两种斜率都可以。

正负斜率都要排序。

容易发现，对于左侧的点，上面的点应该用正斜率，下面的点应该用负斜率。

上界可以通过二分枚举得到，先求出应该为负斜率的点斜率最多为多少，并排序。让它们与负斜率一一对应，检查是否匹配。下界同理。

注意上界的最大值是 $10^9\times10^9=10^{18}$，因此需要开 long long。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=400010;
int T,n,a,x,up[N],dn[N],cntu,cntd,mx,mn;
int d[N],l,r,mid,s,xi[N];
struct node{
	int a1,b1,a2,b2;
}f[N];
bool check1(int x){
	for(int i=1;i<=n;i++)
		xi[i]=(x-f[i].b2)/f[i].a2;//斜率上限为多少
	for(int i=n*2;n*3-i+1<=cntd;i--)
		xi[n*3-i+1]=(x-d[i])/a;//从下往上枚举左侧的点，这样可以斜率上限尽可能大
	sort(xi+1,xi+cntd+1);
	for(int i=1;i<=cntd;i++)
		if(xi[i]<dn[i]) return 0;//无匹配斜率
	return 1;
}
bool check2(int x){
	for(int i=1;i<=n;i++)
		xi[i]=(f[i].b1-x)/f[i].a2;
	for(int i=1;n+i<=cntu;i++)
		xi[n+i]=(d[i]-x)/a;
	sort(xi+1,xi+cntu+1);
	for(int i=1;i<=cntu;i++)
		if(xi[i]<up[i]) return 0;
	return 1;
}
signed main(){
	cin>>T;
	while(T--){
		mx=0,mn=1e9;
		cntu=cntd=0;
		cin>>n>>a;
		for(int i=1;i<=n;i++){
			f[i].a1=a;
			cin>>f[i].b1>>f[i].b2>>f[i].a2;
			d[i*2-1]=f[i].b1;
			d[i*2]=f[i].b2;//把左侧的点单独提出来
			mx=max(mx,f[i].b2);
			mn=min(mn,f[i].b1);
		}
		for(int i=1;i<=n*4;i++){
			cin>>x;
			if(x>0) up[++cntu]=x;
			else dn[++cntd]=-x;//把向上和向下分开
		}
		if(cntu<n||cntd<n) {
			puts("-1");
			continue;
		}
		sort(d+1,d+n*2+1);
		sort(up+1,up+cntu+1);
		sort(dn+1,dn+cntd+1);
		l=mx,r=2e18;
		while(l<=r){
			mid=(l+r)/2;
			if(check1(mid)) r=mid-1;
			else l=mid+1;
		}//枚举上界
		s=r+1;
		l=mn,r=-2e18;
		while(l>=r){
			mid=(l+r)/2;
			if(check2(mid)) r=mid+1;
			else l=mid-1;
		}//枚举下界
		cout<<s-r+1<<"\n";
	}
	return 0;
}
```

---

## 作者：huhangqi (赞：0)

首先进行分类讨论。

对于每个右上角的点，为了不让箭穿过箭靶，必须分配一只向下射的奶牛，即斜率为负数的奶牛。

右下角的点同理，只能选择斜率为正数的点。

对于左上角左下角，不管斜率为正还是负都可以射到。

那么无解条件明显就是斜率为正的和斜率为负的其中有一个不到 $n$。

但是我们的高度会受到射击点的 $x$ 和 $y$ 坐标以及奶牛的斜率 $k$ 影响。

此时我们发现这并不好直接贪心处理。

但是我们可以发现题目所问的问题是最小的最大距离，明显可以二分。

那么我们可以二分两次，分别得到最低的最高点和最高的最低点。

我们二分出来一个最高点，再枚举每个斜率为负的需要射的点，此时计算出一个满足条件的最大斜率，分配小于等于这个斜率的最大斜率即可，可以用 set 维护。

那么最低点也是同理了。

但是对于左边的点又该怎么分配？

容易发现左边的点 $x$ 都相等，那么有影响的只有 $y$ 和 $k$ 了，我们将 $y$ 小的分给斜率为负的，$y$ 大的分给斜率为正的即可。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,sx,a[160005],b[160005],cnta,cntb;
struct P{
	int x,y,yy;
}c[40005];
int d[80005];
multiset<int> s;
bool check(int mid){
	s.clear();
	for(int i=1;i<=cntb;i++)s.insert(-b[i]);
	for(int i=1;i<=n;i++){
		if(mid<c[i].yy)return false;
		auto it=s.upper_bound((mid-c[i].yy)/c[i].x);
		if(it==s.begin())return false;
		it--;
		s.erase(it);
	}
	for(int i=2*n;i>3*n-cntb;i--){
		if(mid<d[i])return false;
		auto it=s.upper_bound((mid-d[i])/sx);
		if(it==s.begin())return false;
		it--;
		s.erase(it);
	}
	return true;
}
bool check2(int mid){
	s.clear();
	for(int i=1;i<=cnta;i++)s.insert(a[i]);
	for(int i=1;i<=n;i++){
		if(mid>c[i].y)return false;
		auto it=s.upper_bound((c[i].y-mid)/c[i].x);
		if(it==s.begin())return false;
		it--;
		s.erase(it);
	}
	for(int i=1;i<=cnta-n;i++){
		if(mid>d[i])return false;
		auto it=s.upper_bound((d[i]-mid)/sx);
		if(it==s.begin())return false;
		it--;
		s.erase(it);
	}
	return true;
}
signed main(){
	cin>>T;
	while(T--){
		cnta=cntb=0;
		cin>>n>>sx;
		for(int i=1;i<=n;i++)cin>>c[i].y>>c[i].yy>>c[i].x;
		for(int i=1,x;i<=4*n;i++){
			cin>>x;
			if(x>0)a[++cnta]=x;
			else b[++cntb]=x;
		}
		if(cnta<n||cntb<n){
			cout<<-1<<endl;
			continue;
		}
		for(int i=1;i<=n;i++)d[i]=c[i].y,d[i+n]=c[i].yy;
		sort(d+1,d+2*n+1);
		int l=-1e18,r=1e18;
		while(l<=r){
			int mid=l+r>>1;
			if(check(mid))r=mid-1;
			else l=mid+1;
		}
		int res=r+1;
		l=-1e18,r=1e18;
		while(l<=r){
			int mid=l+r>>1;
			if(check2(mid))l=mid+1;
			else r=mid-1;
		}
		cout<<res-l+1<<endl;
	}
	return 0;
}
``````

---

## 作者：Jerrywang09 (赞：0)

考虑拆分未知量（最远奶牛之间的最小距离），其实就是要求最上面和最下面两头奶牛的位置。

将矩形的四个顶点分类：

1. 左上左下两个点；
2. 右上；
3. 右下。

将奶牛按照斜率的正负分开处理。斜率为正的奶牛向上打 1、3 类点，可以求得最下面的奶牛位置；斜率为负的奶牛向下打 1、2 类点，可以求得最上面的奶牛位置。

两种牛都使用了 1 类点。有一个贪心策略：靠上的 1 类点给斜率为正的奶牛向上打，靠下的 1 类点给斜率为负的奶牛向下打。这样就确定了两类奶牛打的点的点集。

下面只说最下面的奶牛位置如何求。另一个同理。

现在二分到最下面的奶牛纵坐标 $y$。然后处理出 $(0,y)$ 到达点集内点 $i$ 的斜率 $k_i$。把所有点按照 $k_i$ 从小到大排序。也把所有牛按照斜率从小到大排序。依次检查每头牛是否能匹配上对应的点。

注意要开 `__int128`，避免浮点数除。

```cpp
// Title:  Target Practice II
// Source: USACO24FEB Silver
// Author: Jerrywang
#include <bits/stdc++.h>
#define x first
#define y second
#define pii pair<ll, ll>
#define ll long long
#define lll __int128
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=100010; ll inf=1e18;
using namespace std;

int n, x1; vector<pii> a, b;
vector<int> L, posi, nega;
ll m;

bool cmp1(int i, int j)
{
    // return (a[i].y-m)/a[i].x<(a[j].y-m)/a[j].x;
    return (lll)(a[i].y-m)*a[j].x<(lll)(a[j].y-m)*a[i].x;
}
bool checkPositive()
{
    vector<int> ord;
    rep(i, 0, (int)a.size()-1) ord.push_back(i);
    sort(posi.begin(), posi.end());
    sort(ord.begin(), ord.end(), cmp1);
    rep(j, 0, (int)a.size()-1)
    {
        int i=ord[j];
        // if(posi[j]>(a[i].y-m)/a[i].x)
        if(posi[j]*a[i].x>(a[i].y-m))
            return 0;
    }
    return 1;
}
ll Positive()
{
    ll l=-inf, r=inf, res;
    while(l<=r)
    {
        m=l+r>>1;
        if(checkPositive()) res=m, l=m+1; else r=m-1;
    }
    return res;
}

bool cmp2(int i, int j)
{
    // return (b[i].y-m)/b[i].x<(b[j].y-m)/b[j].x;
    return (lll)(b[i].y-m)*b[j].x<(lll)(b[j].y-m)*b[i].x;
}
bool checkNegative()
{
    vector<int> ord;
    rep(i, 0, (int)b.size()-1) ord.push_back(i);
    sort(nega.begin(), nega.end());
    sort(ord.begin(), ord.end(), cmp2);
    rep(j, 0, (int)b.size()-1)
    {
        int i=ord[j];
        // if(nega[j]<(b[i].y-m)/b[i].x)
        if(nega[j]*b[i].x<(b[i].y-m))
            return 0;
    }
    return 1;
}
ll Negative()
{
    ll l=-inf, r=inf, res;
    while(l<=r)
    {
        m=l+r>>1;
        if(checkNegative()) res=m, r=m-1; else l=m+1;
    }
    return res;
}

void solve()
{
    a.clear(), b.clear(), L.clear(), posi.clear(), nega.clear();
    scanf("%d%d", &n, &x1);
    rep(i, 1, n)
    {
        int y1, y2, x2; scanf("%d%d%d", &y1, &y2, &x2);
        a.push_back({x2, y1}); b.push_back({x2, y2});
        L.push_back(y1), L.push_back(y2);
    }
    rep(i, 1, 4*n)
    {
        int k; scanf("%d", &k);
        if(k>0) posi.push_back(k); else nega.push_back(k);
    }
    if(posi.size()<a.size() || nega.size()<b.size())
    {
        puts("-1"); return;
    }
    sort(L.begin(), L.end(), greater<int>());
    int i;
    for(i=0; i<L.size() && posi.size()>a.size(); i++)
        a.push_back({x1, L[i]});
    for(; i<L.size(); i++) b.push_back({x1, L[i]});
    ll lo=Positive(), hi=Negative();
    printf("%lld\n", hi-lo);
}

int main()
{
    #ifdef Jerrywang
    freopen("in.txt", "r", stdin);
    #endif
    int T; scanf("%d", &T);
    while(T--) solve();
    
    return 0;
}
```

---

