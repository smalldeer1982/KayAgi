# Gr-idian MST

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2016-qualb/tasks/codefestival_2016_qualB_c

$ xy $平面上の$ 0\ ≦\ x\ ≦\ W,\ 0\ ≦\ y\ ≦\ H $をみたす領域にある$ x,y $ともに整数である点すべてに、ひとつずつ家があります。

$ x $座標が等しく$ y $座標の差が$ 1 $であるか、$ y $座標が等しく$ x $座標の差が$ 1 $であるような$ 2 $点の組のうち、両方の点に家が存在するような全てのものに対し、その$ 2 $点の間には舗装されていない道路があります。

座標$ (i,j) $と$ (i+1,j) $にある家の間の道路を舗装するのには$ j $の値にかかわらずコストが$ p_i $、 座標$ (i,j) $と$ (i,j+1) $にある家の間の道路を舗装するのには$ i $の値にかかわらずコストが$ q_j $かかります。

高橋君は、このうちいくつかの道路を舗装し、舗装された道路のみを通って任意の$ 2 $つの家の間を行き来できるようにしたいです。 かかるコストの総和の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ ≦\ W,H\ ≦\ 10^5 $
- $ 1\ ≦\ p_i\ ≦\ 10^8(0\ ≦\ i\ ≦\ W-1) $
- $ 1\ ≦\ q_j\ ≦\ 10^8(0\ ≦\ j\ ≦\ H-1) $
- $ p_i(0\ ≦\ i\ ≦\ W-1) $は整数である
- $ q_j(0\ ≦\ j\ ≦\ H-1) $は整数である

### Sample Explanation 1

次の$ 8 $本の道路を舗装すればよいです。 - $ (0,0) $と$ (0,1) $にある家を結ぶ道路 - $ (0,1) $と$ (1,1) $にある家を結ぶ道路 - $ (0,2) $と$ (1,2) $にある家を結ぶ道路 - $ (1,0) $と$ (1,1) $にある家を結ぶ道路 - $ (1,0) $と$ (2,0) $にある家を結ぶ道路 - $ (1,1) $と$ (1,2) $にある家を結ぶ道路 - $ (1,2) $と$ (2,2) $にある家を結ぶ道路 - $ (2,0) $と$ (2,1) $にある家を結ぶ道路

## 样例 #1

### 输入

```
2 2
3
5
2
7```

### 输出

```
29```

## 样例 #2

### 输入

```
4 3
2
4
8
1
2
9
3```

### 输出

```
60```

# 题解

## 作者：Rigel (赞：14)

## 题意

给定 $H\times W$ 的二维平面，$\forall i \in [0,H],j \in [0,W]$ 存在一个点。连接 $(i,j)$ 到 $(i+1,j)$ 的边权为 $p_i$，连接 $(i,j)$ 到 $(i,j+1)$ 的边权为 $q_j$。求这张 $(H+1)\times (W+1)$ 个点的图的最小生成树的边权和。

## 思路

对于 $H,W\leq 10^5$，直接 MST 会 TLE。

考虑特殊性质。

容易证明，对 $p$ 与 $q$ 排序不会影响最终答案。

于是我们可以每次选取边权最小的行或列，并记录当前选到的行数或列数。

然而一行或一列不一定能全选。

若当前选择的为一列，且已经选了 $i$ 行时，这一列中能选的边数为这一列的总边数（注意一列中有 $(H+1)$ 条边）减去已选择的行数加 $1$，也就是 $(H-i+2)$。

同理，若当前选择的为一行，且已经选了 $j$ 列时，这一行中能选的边数为 $(W-j+2)$。

双指针即可。时间复杂度为 $\mathcal{O}(H \log H)$。（视 $H$ 与 $W$ 同阶）

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define maxn 100010
using namespace std;
int H,W,p[maxn],q[maxn],ans;
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')ret=ret*10+(ch&15),ch=getchar();
	return ret*f;
}
signed main(){
	H=read(),W=read();
	for(int i=1;i<=H;i++)p[i]=read();
	for(int i=1;i<=W;i++)q[i]=read();
	sort(p+1,p+H+1);
	sort(q+1,q+W+1);
	int i=1,j=1;
	while(i<=H&&j<=W){
		if(p[i]<=q[j])ans+=p[i++]*(W-j+2);
		else ans+=q[j++]*(H-i+2);
	}
	while(i<=H)ans+=p[i++]*(W-j+2);
	while(j<=W)ans+=q[j++]*(H-i+2);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：RE_Prince (赞：3)

# Atcoder Gr-idian MST Solution

[link](https://www.luogu.com.cn/problem/AT_codefestival_2016_qualB_c)


## Sol

这道题和江西提高的原题很像，建议大家先去做那一道。

好了，进入正题：最小生成树。

本题一眼的最小生成树板子，但用 Kruskal 模拟一下，发现 TLE 妥妥的。因此，我们要优化。


再次审视题目，可以发现这是一个网格图，而每列每行的边全都是一样的价值。不难得出结论：要选，就是选一列或一行所有的边（前提是还有那么多边可选）。简化一下：如果最小生成树剩下的边 $\ge$ 现在要选的边总数，则选这一行或者一列。


但！是！有一个问题：我们无法保证选的边不形成一个环。


那怎么处理呢？

我们可以用两个变量来记录现在选了多少列，多少行。这样，下次选边的时候，就可以轻松地判断这一行或列可以选多少边来符合“树”这个要求。


## 代码

```cpp
#include<bits/stdc++.h>
#include<unordered_map>
#define int long long
using namespace std;
int n,m,i,j,k;
const int N=3e5 + 9;
int a[N],b[N],ans;
signed main()
{
	int l,r;
	cin>>n>>m;
	for(i=1;i<=n;i++) cin>>a[i];
	sort(a,a+n+1);
	for(i=1;i<=m;i++) cin>>b[i];
	sort(b,b+m+1);//排序，别丢了！
	l=1,r=1;//现在选的行列
	int x=n+1,y=m+1;
	while(l+r-2<n+m)
	{
		if(a[l]<b[r]) //选取更优的边
		{
			if(l<=n) k+=a[l++]*y,x--;
			else k+=b[r++]*x,y--;
		}
		else//同理
		{
			if(r<=m) k+=b[r++]*x,y--;
			else k+=a[l++]*y,x--;
		}
	}
	cout<<k<<endl;
	return 0;
}
```

---

## 作者：紊莫 (赞：1)

相似题：[P5687 [CSP-S2019 江西] 网格图](https://www.luogu.com.cn/problem/P5687)。  

## 思路

首先这题显然不能使用朴素的最小生成树来求解，那么考虑网格图带来的性质。

容易发现我们可以选择当前边权最小的列或行，但是又遇到了一个问题，也就是到底应该取几条边呢？盲目的选择整行显然会构成环，此时不妨画个图理解一下。  
![](https://cdn.luogu.com.cn/upload/image_hosting/sy4wjrop.png)  

红色为已经选择的边，假设我下一步希望选竖着的一列，那么要选几条边呢？显然是 $4$ 条，据此可以发现选择的边数和已经选择的行列有关。  

## 代码

这东西是很久之前写的，然而一直 UKE，最近才提交成功。  

```cpp
// Problem: Gr-idian MST
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_codefestival_2016_qualB_c
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//Author: ztr (practice)
//@Turtle_zhu on Luogu (uid=443675)
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 100005;
int n,m,ans,s1=1,s2=1,a[N],b[N];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++) cin>>b[i];
	sort(a+1,a+n+1);sort(b+1,b+m+1);
	for(int i=1,j=1; i<=n || j<=m;){
		if(i>n) ans += b[j++]*(n+2-s2),s1++;
		else if(j>m) ans += a[i++]*(m+2-s1),s2++;
		else if(a[i]<b[j]) ans += a[i++]*(m+2-s1),s2++;
		else ans += b[j++]*(n+2-s2),s1++;
	}
	cout<<ans<<endl;
    return 0;
}
```
实际上求最小生成树的思路是大同小异的，就是去不断取出最短边，唯一区别的是这题还要求计算取到的边数，至于怎么取到，是不需要考虑的。

---

## 作者：One_JuRuo (赞：1)

## 思路

首先想到暴力建边跑最小生成树，但是显然会 TLE。

所以思考有没有时间复杂度更低的做法，考虑到最小生成树是每次取最短的边，所以我们也可以先考虑较短的边。

首先最短的边一定是某一列或者某一行（或者若干列和行），所以我们取边，也应该是一行一行或者一列一列的取。

但是有些时候这样取，或构成环，就不是树了，所以我们取边是有限制的，如果已经取了两行，那么再取某一列就必须要少取这两行之间的一条边，因为同一行和同一列的每条边的值都一样，所以不需要去找是那条边，只需要直接算出来取多少就可以了。

同时，因为后取的边的数量较少，所以我们应该有限取权值较小的边，所以需要排序。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,a[300005],b[300005],ans,aa=1,bb=1;
int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
	for(int i=1;i<=m;++i) scanf("%lld",&b[i]);
	sort(a+1,a+n+1),sort(b+1,b+m+1);
	while(aa+bb-2<n+m) ans+=(a[aa]<=b[bb]&&aa<=n||a[aa]>b[bb]&&bb>m)?a[aa++]*(m-bb+2):b[bb++]*(n-aa+2);//注意取完的情况
	printf("%lld",ans);
}
```

---

## 作者：清烛 (赞：1)

题意：$H \times W$ 的二维平面，$\forall 0\le i\le H, 0\le j\le W$ 有一个点。连接 $(i, j)$ 到 $(i + 1, j)$ 的边权为 $p_i$（$0\le j\le W$），连接 $(i, j)$ 到 $(i, j + 1)$ 的边权为 $q_j$。求这张 $(H + 1)\times (W + 1)$ 个点的图的最小生成树的边权和。$1\le H, W\le 10^5$，$1\le p_i,q_j\le 10^8$。

注意到，连接 $(i, j)$ 到 $(i, j + 1)$ 可以视为合并 $j$ 和 $j + 1$，连接 $(i,j)$ 和 $(i + 1, j)$ 同理。所以我们维护一下横方向和纵方向上还有多少坐标未被合并，假设还有 $a$ 个横坐标未被合并，$b$ 个纵坐标未被合并，则我们连 $a$ 条 $(i,j)$ 到 $(i, j + 1)$ 的边就能使得 $b$ 减一，反之同理。

根据排序不等式，我们从小的 $p_i/q_j$ 开始选，连完为止就是最优的。

```cpp
using ll = long long;
using pli = pair<ll, int>;
int h, w;
vector<pli> p;

int main() {
    read(h, w);
    FOR(i, 1, h) {
        int x; read(x);
        p.push_back(pli(x, 1));
    }
    FOR(i, 1, w) {
        int x; read(x);
        p.push_back(pli(x, 2));
    }
    sort(p.begin(), p.end());
    ll ans = 0;
    int a = h + 1, b = w + 1;
    for (auto now : p) {
        if (now.second == 1) {
            if (a) --a, ans += now.first * b;
        } else {
            if (b) --b, ans += now.first * a;
        }
    }
    print(ans);
    return output(), 0;
}
```

---

## 作者：_Kenma_ (赞：0)

# 解题报告

## 前言

笑点解析：从 P5687 来的，但是改了半天才过。

两个题的输入有点不太一样。

这里就按 P5687 的输入为准吧，可能更好理解。

发现我的贪心和别人的好像不太一样。

## 思路分析

首先你不能直接 kruskal。

考虑发掘性质。

不难发现，如果我们按 $a_i$ 和 $b_i$ 的从小到大对行和列重排序，答案是不变的。但是会好看很多。

比如这是我们的最终答案：

![](https://cdn.luogu.com.cn/upload/image_hosting/gfn157uv.png)

考虑怎样达到这个答案。


然后，为了使得图联通，在每一行和每一列都必须选择至少一个元素。也就是图中的黑色边。

在 P5687 中，选择 $a_1$ 和 $b_1$ 一定是最优的。

然后，从上到下，从左到右考虑整张图，一个点如果想和别的点联通，只能选择上面的点或者左面的点连边。也就是图中的橙色边。

因为我们对行和列重排序过，所以每一行每一个点一定是这样选择的（$0$ 表示左边，$1$ 表示上边）：$0,0,\cdots,0,1,1,\cdots,1$。第 $i$ 行的分界点 $p$ 为 $a_i \ge b_p$。

所以只需要二分找到每一行的分界点，就可以快速统计出答案。

双指针应该也可以做，就是可能麻烦一点。

总体复杂度 $O(n\log n)$。

## 代码实现

P5687 的代码。

```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf=1e9;
int n,m,p,a[500005],b[500005],sum[500005],ans;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0); 
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>b[i];
	}
	sort(a+1,a+1+n);
	sort(b+1,b+1+m);
	for(int i=1;i<=m;i++){
		sum[i]=sum[i-1]+b[i];
	}
	b[m+1]=inf;
	ans=a[1]*(n-1)+b[1]*(m-1);
	for(int i=2;i<=n;i++){
		p=lower_bound(b+2,b+2+m,a[i])-b;
		ans+=sum[p-1]-b[1]+(m-p+1)*a[i];
	}
	cout<<ans;
	return 0;
}

```

现在你可以在 P5687 的基础上做出这道题了，快去试试吧！

## 后记

很 OI 的性质题。

---

## 作者：Union_Find (赞：0)

首先，直接用最小生成树是会 `TLE` 的。

这时，我们发现，在加上边的时候，它是一整排或一整列加的，而且每次取 $a,b$ 中的最小值，那么就可以用双指针做了。

具体做法就是用 $l,r$ 两个指针，指向 $a,b$ 数组，然后每次移动较小的值，求出总和。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
ll n, m, a[300005], b[300005], ans, rr, cc, l, r, tot;
int main(){
	scanf ("%lld %lld", &n, &m);
	for (int i = 1; i <= n; i++) scanf ("%lld", &a[i]);
	for (int j = 1; j <= m; j++) scanf ("%lld", &b[j]);
	sort (a + 1, a + n + 1);
	sort (b + 1, b + m + 1);
	ans = a[1] * (m - 1) + b[1] * (n - 1), rr = cc = 1, l = r = 2, tot = n + m - 2;
	while (tot != n * m - 1){
		if (a[l] < b[r]) ans += a[l++] * (m - rr), cc++, tot += m - rr;
		else ans += b[r++] * (n - cc), rr++, tot += n - cc;
	}
	printf ("%lld", ans);
	return 0;
}

```

---

## 作者：_299817_ (赞：0)

## Part 0：前言
好像题解都没有图，这里有图，而且提供一个和其他题解不太一样的做法，比起克鲁斯卡尔，更容易理解。

主要思路来自 <https://www.luogu.com.cn/blog/208529/solution-p5687>。

## Part 1：主要思路
首先，我们得明确一个很简单的贪心性质：

对于点 $(i,j)$，如果点 $(i-1,j)$ 和点 $(i,j-1)$ **都已经在当前的最小生成树内**，那么将点 $(i,j)$ 加入最小生成树后，答案的变化为 $\min(p_i,q_j)$。

而且：还有一个性质，就是 $p$ 和 $q$ 中的数的顺序的改变不会影响答案。

我们这里可以先结合第二个样例来理解（这里是已经排好序的）：

![](https://cdn.luogu.com.cn/upload/image_hosting/vqthln0z.png)

不难发现，不论样例怎样，我们都必须选第一行和第一列。

接着，我们对于每一列的横线，从第二个开始，选择所有比其小的竖线的值，接着剩下的所有的数的个数个这个列的横线的值。

也就是说，设这一列的横线的值为 $val$，一列竖线上的值组成的数组（已经排好序）为 $\{a\}$（大小为 $sz$），$\{a\}$ 一共有 $t$ 个数比 $val$ 小，那么最后这一列所有横线对答案所产生的贡献为 $\sum_{i=1}^{i \le t} a_i + val \times (sz-t)$。

对于这个式子，$val$、$sz$、$\{a\}$ 是知道的，而 $t$ 可以通过二分求得，$\sum_{i=1}^{i \le t} a_i$ 可以通过前缀和求得。

于是这题就做完了。

时间复杂度 $O(H\log{H})$（$H$、$W$ 同阶）。

记得开 `long long`。

## Part 2：完整代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#include<map>
#include<queue>
#include<stack>
#include<bitset>
#define sort stable_sort
#define map unordered_map
#define int long long // 开 long long
using namespace std;
typedef long long ll;

int n, m;
int a[300010];
int b[300010];
int sum[300010];
int ans;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
	int sum1 = 0, sum2 = 0; // 记录每一行的和
    for(int i = 1; i <= n; i++){
        cin >> a[i];
		sum1 += a[i];
    }
    for(int i = 1; i <= m; i++){
        cin >> b[i];
		sum2 += b[i];
    }
    sort(a + 1, a + n + 1), sort(b + 1, b + m + 1);
	ans += sum1 + sum2; // 答案要加上和
    for(int i = 1; i <= m; i++){
        sum[i] = sum[i - 1] + b[i]; // 记录前缀和
    }
    for(int i = 1; i <= n; i++){
        int now = lower_bound(b + 1, b + 1 + m, a[i]) - b - 1; // 上面描述中 t 的值
        ans += sum[now];
        ans += (m - now) * a[i];
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：零殇 (赞：0)

PS：我的标点符号好像没加空格，管理大大能否指正一下？

#### 题意

给定 $H$ 和 $W$，连接 $(i,j)$ 和 $(i+1,j)$ 的费用为 $p_i$，连接 $(i,j)$ 和 $(i,j+1)$ 的费用为 $q_j$。求连接所有点的最小费用。

#### 思路

可以运用贪心的思想。

多次连接 $(i,j)$ 和 $(i+1,j)$，就可以把 $i$ 与 $i+1$ 行连接起来，多次连接 $(i,j)$ 和 $(i,j+1)$，就可以把 $j$ 与 $j+1$ 列连接起来。

当每行每列都连接起来，那么所有点都连接完了。

因此要先给 $p$ 和 $q$ 分别从小到大排序。

那么每次都要连接几次呢？

我们不妨用 $temp1$ 和 $temp2$ 记录列与行（即横坐标与纵坐标）每次应该连接的次数。

那么 $temp1$ 和 $temp2$ 的初值分别是 $H+1$ 与 $W+1$。

而每次连接的次数则是相对应的 $temp$ 值。

由于一次连接让某一行或某一列合并成了整体，因此应该让另一个 $temp$ 减 $1$。

那么每次取 $p$ 和 $q$ 中的总最小值，连接相对应的行或列，再把总乘积相加。

关于连接行与列的正确性证明：

可以把每个点都看作一个整体，每次连接都是把两个整体合并成一个，我们的目的就是把所有整体合并。因此我们每次一定是连接最小费用的两个整体。

但最小费用的连接不止一个，因此我们每次都要把所有费用最小的整体连接。

而每个费用最小的连接，则对应着相应的行或列中不属于一个整体的两个。因此把所有费用最小的路径连接，其实就是合并相对应的行或列，因此我们每次合并费用最小的行或列，最后的答案一定最小。

上代码：
```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>
const int N=2e5+7;
using namespace std;
int H,W;
long long ans;
int father[N];
long long p[N],q[N];
int main() {
	scanf("%d%d",&H,&W);
	for(int i=1;i<=H;i++)
		scanf("%lld",&p[i]);
	for(int i=1;i<=W;i++)
		scanf("%lld",&q[i]);
	sort(p,p+H+1);
	sort(q,q+W+1);
	int temp1=1,temp2=1,flag=0,sum1=H+1,sum2=W+1;
	while(flag<H+W) {
		if(p[temp1]<q[temp2]) {
			if(temp1<=H) {
				ans+=p[temp1]*sum2;
				flag++;
				sum1--;
				temp1++;
			}
			else {
				ans+=q[temp2]*sum1;
				flag++;
				sum2--;
				temp2++;
			}
		}
		else {
			if(temp2<=W) {
				ans+=q[temp2]*sum1;
				flag++;
				sum2--;
				temp2++;
			}
			else {
				ans+=p[temp1]*sum2;
				flag++;
				sum1--;
				temp1++;
			}
		}
	}
	printf("%lld",ans);
	return 0;
}
```
完结撒花~

---

