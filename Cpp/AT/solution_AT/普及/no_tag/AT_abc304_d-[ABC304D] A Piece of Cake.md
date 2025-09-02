# [ABC304D] A Piece of Cake

## 题目描述

在 $xy$ 平面上，一块带有一些草莓的蛋糕占据了一块矩形区域 $\{(x,y):0\le x\le W,0\le y\le H\}$。

蛋糕上有 $N$ 个草莓，第 $i$ 个草莓的坐标是 $(p_i,q_i)$。现在，高桥要用小刀按照以下规则将蛋糕切成小块。

- 首先，沿着平行于 $y$ 轴的 $A$ 条直线：直线 $x=a_1$、直线 $x=a_2$、……、直线 $x=a_A$，将蛋糕切开。
- 接着，沿着平行于 $x$ 轴的 $Y$ 条直线：直线 $y=b_1$、直线 $y=b_2$、……、直线 $y=b_B$，将蛋糕切开。

到了最后，蛋糕会被切成 $(A+1)(B+1)$ 块长方形，现在高桥要选择其中一块，求他选择的蛋糕上草莓个数可能的最大值和最小值。

保证切割的边缘线上没有草莓，具体请参照数据范围。

## 说明/提示

-   $3 \le W, H \le 10^9$
-   $1 \le N \le 2 \times 10^5$
-   $0 < p_i < W$
-   $0 < q_i < H$
-   $i \ne j \implies (p_i, q_i) \ne (p_j, q_j)$
-   $1 \le A, B \le 2 \times 10^5$
-   $0 < a_1 < a_2 <\cdots < a_A < W$
-   $0 \lt b_1 \lt b_2 \lt \cdots \lt b_B \lt H$
-   $p_i \notin \{ a_1, a_2, \ldots, a_A \}$
-   $q_i \notin \{ b_1, b_2, \ldots, b_B \}$
-   所有输入的值都是正整数。

## 样例 #1

### 输入

```
7 6
5
6 1
3 1
4 2
1 5
6 2
2
2 5
2
3 4```

### 输出

```
0 2```

## 样例 #2

### 输入

```
4 4
4
1 1
3 1
3 3
1 3
1
2
1
2```

### 输出

```
1 1```

# 题解

## 作者：Fire_flame (赞：4)

没想到吧，这道题目叫“小菜一碟”，哈哈。

# $\mathbf{Solution}$

因为 $(A+1)\times(B+1)\le 4\times 10^{10}$，所以我们应该考虑对每一个格子离散化，这里我直接使用 `map<int, int>`。

然后二分查找出每一个草莓所在的格子，用 `map` 记录一下。另外只维护含有草莓的格子会让空间负担大大减少。

判断最小值会不会是 $0$ 只需要看格子上面有草莓的数量 $t$。如果 $t<(A+1)\times(B+1)$ 说明有的格子没有覆盖，最小值输出 $0$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + (ch - '0');ch = getchar();}
	return s * f;
}
const int MAXN = 2e5 + 5;
int x, y, n, m, k, a[MAXN], b[MAXN], ans = 1145141919, ans2, num;
struct strawberry{
	int x, y;
}t[MAXN];
map<int, int>mp[MAXN];
signed main(){
	x = read(), y = read(), n = read();
	for(int i = 1;i <= n;i ++)t[i].x = read(), t[i].y = read();
	m = read();
	for(int i = 1;i <= m;i ++)a[i] = read();
	k = read();
	for(int i = 1;i <= k;i ++)b[i] = read();
	for(int i = 1;i <= n;i ++){
		int h = lower_bound(a + 1, a + m + 1, t[i].x) - a;
		int w = lower_bound(b + 1, b + k + 1, t[i].y) - b;
		mp[h][w] ++;
		if(mp[h][w] == 1)num ++;
	}
	for(int i = 1;i <= n;i ++){
		int h = lower_bound(a + 1, a + m + 1, t[i].x) - a;
		int w = lower_bound(b + 1, b + k + 1, t[i].y) - b;
		ans = min(ans, mp[h][w]);
		ans2 = max(ans2, mp[h][w]);
	}
//	printf("%d\n", num);
	if(num < (m + 1) * (k + 1))printf("0 %lld", ans2);
	else printf("%lld %lld", ans, ans2);
	return 0;
}
```


后记：

2023.6.3 我在写这道题时，第一次代码写错了，然后不相信评测结果又交了三次，四次全 WA。后来发现取最大值时写成了 `ans2 = max(ans, ...)` 又交了一次，又 WA。最后发现  $(A+1)\times(B+1)$ 可能爆 int，结果交的时候没有删调试，**总共罚时 $6$ 发，警钟敲烂，警钟敲烂，警钟敲烂，警钟敲烂，警钟敲烂。**

---

## 作者：XSean (赞：2)

## D: A Piece of Cake

[D - A Piece of Cake](https://atcoder.jp/contests/abc304/tasks/abc304_d)

这道题的切割线的数量 $A,B$ 太大，空间时间都会超，但是点的数量只有 $N$ 个。

显然想到的做法：

**1.** 将两组切割线升序排列。

```cpp
rd(A); rep(i, 1, A) rd(a[i]); sort(a, a + A + 1);
rd(B); rep(i, 1, B) rd(b[i]); sort(b, b + B + 1);
```

**2.** 那么用点的坐标来二分，确定区域。

用一个 `map<PII, int>`，`fi` 是点的区域左下的坐标，`se` 是区域内的点数。

```cpp
rep(i, 1, n){
    int X = lower_bound(a, a + A + 1, p[i].fi) - a;
    int Y = lower_bound(b, b + B + 1, p[i].se) - b;
    area[{X, Y}]++;
}
```

**3.** 最后查最小、大值。

若有效区域的数量 $<(A + 1)(B + 1)$，则 `mi = 0`。

```cpp
int mi = inf, mx = 0;
if(area.size() != (A + 1) * (B + 1)) mi = 0;
else go(t, area) mi = min(mi, t.se);
go(t, area) mx = max(mx, t.se);
```

**核心代码：**

```cpp
const int N = 2e5 + 10;
int w, h;
int n;
PII p[N];
map<PII, int> area;
int a[N], b[N];
int main(){
	rd(w, h);
	rd(n);
	rep(i, 1, n) rd(p[i].fi, p[i].se);
	int A, B;
	rd(A); rep(i, 1, A) rd(a[i]); sort(a, a + A + 1);
	rd(B); rep(i, 1, B) rd(b[i]); sort(b, b + B + 1);
	rep(i, 1, n){
		int X = lower_bound(a, a + A + 1, p[i].fi) - a;
		int Y = lower_bound(b, b + B + 1, p[i].se) - b;
		area[{X, Y}]++;
	}
	int mi = inf, mx = 0;
	if(area.size() != (A + 1) * (B + 1)) mi = 0;
	else go(t, area) mi = min(mi, t.se);
	go(t, area) mx = max(mx, t.se);
	prf("%d %d\n", mi, mx);
	return 0;
}
```

[完整代码](https://www.luogu.com.cn/paste/kr62vn5g)

---

## 作者：qwertim (赞：2)

# 题意
有一个长 $W$ 宽 $H$ 的长方形蛋糕，上面有 $n$ 个草莓，第 $i$ 个草莓位于 $(p_i,q_i)$ 上。高桥将蛋糕切成几块，具体如下。

首先，沿着横轴切割蛋糕，共切 $A$ 条线，第 $i$ 次切第 $a_i$ 列。

接着，沿着纵轴切割蛋糕，共切 $B$ 条线，第 $i$ 次切第 $b_i$ 行。

最终，蛋糕将被切为 $(A+1)(B+1)$ 个小蛋糕。高桥将选择其中的一个块来食用，请输出所选块上可能的草莓数量的最小值和最大值。
# 思路
### Part 1
直接暴力枚举每一块小蛋糕上面有几个草莓，取其中的最小值和最大值。代码就不放了。

时间复杂度为 $O(AB)$ ，而数据范围提到 $1 \leq A,B \leq 2 \times 10^5$，则 $A \times B \leq 4 \times 10^{10}$，肯定超时。
### Part 2
仔细看数据范围：$1 \leq n \leq 2 \times 10^5$，则我们可以求出**每块含有草莓的小蛋糕共含有多少个草莓**。

我们用二分找到每一个草莓属于哪一个小蛋糕，如果用二维数组存储每个小蛋糕，肯定存不下。所以我们用一个桶来存储每块小蛋糕，最后再遍历这个桶，找出最小值和最大值即可。

那如果有小蛋糕上没有草莓，没有被存到桶里怎么办？

我们知道 $(A+1)(B+1)$ 是小蛋糕的块数，而桶的大小是包含草莓的小蛋糕块数。如桶的大小小于 $(A+1)(B+1)$，则一定有至少一块小蛋糕没有草莓的。如桶的大小等于 $(A+1)(B+1)$，则每块小蛋糕都包含至少一个草莓，再取最小值即可。
# 最终代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define fo(i,l,r) for(int i=l;i<=r;i++)
using namespace std;
int w,h,n,q[200005],p[200005],aa,a[200005],bb,b[200005],minx=200005,maxn=-1;
bool flag;
map<pair<int,int>,int>mp;
int main(){
	cin>>w>>h>>n;
	fo(i,1,n)scanf("%d %d",&q[i],&p[i]);
	cin>>aa;
	fo(i,1,aa)scanf("%d",&a[i]);
	cin>>bb;
	fo(i,1,bb)scanf("%d",&b[i]);
	fo(i,1,n){
		int l=0,r=aa,mid,posa;
		while(l<=r){
			mid=(l+r)>>1;
			if(a[mid]<=q[i])posa=mid,l=mid+1;
			else r=mid-1;
		}//在小蛋糕左边的边
		l=0,r=bb;
		int posb;
		while(l<=r){
			mid=(l+r)>>1;
			if(b[mid]<=p[i])posb=mid,l=mid+1;
			else r=mid-1;
		}//在小蛋糕上面的边
		mp[{posa,posb}]++;//左边和上面的边代表一个小蛋糕
	}
	ll tmpa=aa+1,tmpb=bb+1,tmpmp=mp.size();//因为ab≤4*10^10，所以一定要开long long！！！
	if(tmpmp<tmpa*tmpb)cout<<0<<' ',flag=1;
	for(auto it:mp){
		maxn=max(maxn,it.second);
		if(!flag)minx=min(minx,it.second);
	}
	if(!flag)cout<<minx<<' ';
	cout<<maxn;
	return 0;
}
```

---

## 作者：shinzanmono (赞：2)

# [ABC304D] A Piece of Cake

~~题目居然叫小菜一碟。~~

对于一颗草莓，我们可以二分查找它所在的蛋糕块。现在，最大的问题就是，我们如何存储这些数据。

看到数据范围是 $1\leq A,B\leq2\times10^5$，那么 $(A+1)(B+1)\leq4\times10^{10}$，很显然，数组存不下。

我们再考虑草莓的个数，$N\leq2\times10^5$。于是不难想到，我们可以使用一个 `std::map`，维护**有草莓**的蛋糕，然后把所有有草莓的蛋糕找到后，如果总数 $\ne(A+1)(B+1)$，那么一定有不带草莓的蛋糕，最小值便是 $0$。枚举每一个有草莓的蛋糕，找出草莓数量最小值和最大值即可。最后总时间复杂度 $O(n\log n)$。

给出代码：

```cpp
#include<iostream>
#include<algorithm>
#include<map>
const int sz=2e5+10;
std::map<std::pair<int,int>,int>cnt;
int a[sz],b[sz],x[sz],y[sz];
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n,m,k,na,nb;
    std::cin>>n>>m>>k;
    for(int i=1;i<=k;i++)
        std::cin>>x[i]>>y[i];
    std::cin>>na;
    for(int i=1;i<=na;i++)std::cin>>a[i];
    a[na+1]=n+1;
    std::cin>>nb;
    for(int i=1;i<=nb;i++)std::cin>>b[i];
    b[nb+1]=m+1;
    for(int i=1;i<=k;i++){
        int w=std::lower_bound(a+1,a+na+2,x[i])-a;
        int h=std::lower_bound(b+1,b+nb+2,y[i])-b;
        cnt[std::make_pair(w,h)]++;
    }
    int min=k,max=0;
    if(cnt.size()!=(long long)(na+1)*(nb+1))min=0;
    for(auto x:cnt)
        min=std::min(min,x.second),max=std::max(max,x.second);
    std::cout<<min<<" "<<max<<"\n";
    return 0;    
}
```

---

## 作者：_Ad_Astra_ (赞：0)

首先考虑如何判断每个草莓在哪一块蛋糕里。由于切的位置是单调递增的，很容易想到二分，就是查找比草莓位置大的最小的切的位置，使用 `stl::upper_bound` 即可。

但是观察到 $1 \le A,B \le 2 \times 10^5$，也就是共有最多 $4 \times 10^{10}$ 块，无论在空间上还是时间上都会炸，怎么办？因为最多只有 $N$ 块草莓，意味着最多有 $N$ 块蛋糕上有草莓，那么不难想到使用 `std::map` 来记录。当然可能有蛋糕上没有放置草莓，因此要特判最小值为 $0$ 的情况。

时间复杂度 $O(n \log n)$。

code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fir first
#define sec second 
const int inf=0x3f3f3f3f3f3f3f3f; 
int n,m,k,k1,k2,x[200010],y[200010],a[200010],b[200010],ans1=inf,ans2;
map<pii,int>mp;
signed main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++)cin>>x[i]>>y[i];
	cin>>k1;
	for(int i=1;i<=k1;i++)cin>>a[i];
	cin>>k2;
	for(int i=1;i<=k2;i++)cin>>b[i];
	for(int i=1;i<=k;i++)
	{
		int id1=upper_bound(a+1,a+k1+1,x[i])-a;
		int id2=upper_bound(b+1,b+k2+1,y[i])-b;
		mp[pii(id1,id2)]++;
	}
	for(auto i:mp)
	{
		ans1=min(ans1,i.sec);
		ans2=max(ans2,i.sec);
	}
	cout<<(mp.size()<(k1+1)*(k2+1)?0:ans1)<<" "<<ans2;//注意特判 
	return 0;
}
```

---

## 作者：_zzzzzzy_ (赞：0)

显然这题和题目名一样小菜一碟。

# 思路
我们可以把切的所有刀当成一张表格。

对于一个草莓我们可以用二分 $O(\log n)$ 的复杂度找到相应的格子。

下面给出具体操作和格子的下标.

先用二分找到格子的 $x$ 坐标，`lower_bound(a + 1, a + 1 + A, x[i]) - a - 1`。

然后用同样的方法找到 $y$ 坐标，`lower_bound(b + 1, b + 1 + B, y[i]) - b - 1`。

然后开一个计数器来记录格子里面的草莓个数，最大值边加边统计就可以了。

最小值我们可以发现当草莓数比格子数少的时候必然会有空的格子，那么剩下的情况暴力复杂度已经能够通过了。

那么我们就解决这道题了。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int maxn = 1000000;
map<int, map<int, int>> st;
int x[maxn], y[maxn];
int a[maxn], b[maxn];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int h, w;
	cin >> h >> w;
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> x[i] >> y[i];
	}
	int A, B;
	cin >> A;
	for (int i = 1; i <= A; i++) {
		cin >> a[i];
	}
	cin >> B;
	for (int i = 1; i <= B; i++) {
		cin >> b[i];
	}
	sort(a + 1, a + 1 + A);
	sort(b + 1, b + 1 + B);
	int maxx = 0;
	for (int i = 1; i <= n; i++) {
		int l = lower_bound(a + 1, a + 1 + A, x[i]) - a - 1;
		int r = lower_bound(b + 1, b + 1 + B, y[i]) - b - 1;
		++st[l][r];
		maxx = max(maxx, st[l][r]);
	}
	if ((i64)(A + 1) * (B + 1) <= n) {
		int minn = INT_MAX;
		for (int i = 0; i < (A + 1); i++) {
			for (int j = 0; j < (B + 1); j++) {
				minn = min(minn, st[i][j]);
			}
		}
		cout << minn << " " << maxx;
		return 0 ;
	}
	cout << "0 " << maxx;
	return 0;
}
```

---

## 作者：code_hyx (赞：0)

这道题其实很简单，只要算出每个草莓在哪块蛋糕上就行了。  
可以从横纵两个维度分别用 lower_bound 定位，用一个 map 存每块**有草莓**的蛋糕。  
然后，还要判断一下最小可不可能为 $0$，也就是有没有无草莓的块。  
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int w,h,n,m,k,maxx,minn=0x3f3f3f3f,a[200005],b[200005];
map<pair<int,int>,int> mp;
struct pt
{
	int x;
	int y;
};
pt p[200005],stw[200005],c[200005];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>w>>h>>k;
	for(int i=1;i<=k;i++)
	{
		cin>>p[i].x>>p[i].y;
	}
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];	
	} 
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>b[i];	
	} 
	for(int i=1;i<=k;i++)
	{
		int x=upper_bound(a+1,a+n+1,p[i].x)-a;
		if(p[i].x>a[n])x=n+1;
		stw[i].x=x;
		int y=upper_bound(b+1,b+m+1,p[i].y)-b;
		if(p[i].y>b[m])y=m+1;
		stw[i].y=y;
		c[i]=(pt){x,y};
		mp[make_pair(x,y)]++;
	}
	bool flag=true;
	if((n+1)*(m+1)<=k)
	{
		for(int i=1;i<=n+1;i++)
		{
			if(flag==false)break;
			for(int j=1;j<=m+1;j++)
			{
				//cout<<i<<" "<<j<<" "<<mp[make_pair(i,j)]<<"\n";
				if(mp[make_pair(i,j)]==0)
				{
					flag=false;
					break;
				}
			}
		}
	}
	else flag=false;
	if(flag==false)minn=0;
	if(minn==0)cout<<0<<" ";
	for(int i=1;i<=k;i++)
	{
		maxx=max(mp[make_pair(c[i].x,c[i].y)],maxx);
		minn=min(mp[make_pair(c[i].x,c[i].y)],minn);
	}
	if(flag==true)cout<<minn<<" ";
	cout<<maxx;
	return 0;
}
```


---

## 作者：DengDuck (赞：0)

正着做显然就是一个二维矩阵统计的问题，主席树不难实现。

但这是一个 D 题。

考虑反着做，对于每个草莓让其找自己的那块蛋糕，这里可以二分查找，最后统计即可。

坐标会很多，建议用 `map` 来维护。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=5e5+5;
map<LL,LL>m;
LL w,h,n,x[N],y[N],a1[N],a2[N],a,b,mn=1e9,mx;
int main()
{
	cin>>w>>h>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x[i]>>y[i];
	}
	cin>>a;
	for(int i=1;i<=a;i++)
	{
		cin>>a1[i];
	}
	cin>>b;
	for(int i=1;i<=b;i++)
	{
		cin>>a2[i];
	}
	for(int i=1;i<=n;i++)
	{
		LL t1=lower_bound(a1+1,a1+a+1,x[i])-a1;//求出对于的蛋糕
		LL t2=lower_bound(a2+1,a2+b+1,y[i])-a2;
		m[t1*N+t2]++;//统计
	} 
	if(m.size()!=(a+1)*(b+1))mn=0;//说明有些蛋糕没草莓
   // 下面不统计这些蛋糕，所以要统计
	for(int i=1;i<=n;i++)
	{
		LL t1=lower_bound(a1+1,a1+a+1,x[i])-a1;//我们只统计有草莓的蛋糕，使得统计的时间快些
		LL t2=lower_bound(a2+1,a2+b+1,y[i])-a2;
		LL k=m[t1*N+t2];//查找与统计
		mn=min(mn,k),mx=max(mx,k);
	} 	
	cout<<mn<<' '<<mx<<endl;
}
```

---

