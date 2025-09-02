# Maximize the Intersections

## 题目描述

On a circle lie $ 2n $ distinct points, with the following property: however you choose $ 3 $ chords that connect $ 3 $ disjoint pairs of points, no point strictly inside the circle belongs to all $ 3 $ chords. The points are numbered $ 1, \, 2, \, \dots, \, 2n $ in clockwise order.

Initially, $ k $ chords connect $ k $ pairs of points, in such a way that all the $ 2k $ endpoints of these chords are distinct.

You want to draw $ n - k $ additional chords that connect the remaining $ 2(n - k) $ points (each point must be an endpoint of exactly one chord).

In the end, let $ x $ be the total number of intersections among all $ n $ chords. Compute the maximum value that $ x $ can attain if you choose the $ n - k $ chords optimally.

Note that the exact position of the $ 2n $ points is not relevant, as long as the property stated in the first paragraph holds.

## 说明/提示

In the first test case, there are three ways to draw the $ 2 $ additional chords, shown below (black chords are the ones initially drawn, while red chords are the new ones):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1552C/704c17cd22decf087937d97766096b41bea230a2.png)We see that the third way gives the maximum number of intersections, namely $ 4 $ .

In the second test case, there are no more chords to draw. Of course, with only one chord present there are no intersections.

In the third test case, we can make at most one intersection by drawing chords $ 1-3 $ and $ 2-4 $ , as shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1552C/abc82045666e4296b48f8b98db9ad5de10f98734.png)

## 样例 #1

### 输入

```
4
4 2
8 2
1 5
1 1
2 1
2 0
10 6
14 6
2 20
9 10
13 18
15 12
11 7```

### 输出

```
4
0
1
14```

# 题解

## 作者：zhongqijun (赞：7)

## 题干

在一个圆上有 $2n$ 个不同的点，具有以下性质：无论你如何选择 $3$ 条连接 $3$ 对互不相干的点的弦，在圆内没有一个点严格属于所有 $3$ 条弦。这些点按顺时针顺序被编号为 $1,2,…,2n$。

最初，$k$ 条和弦连接了 $k$ 对点，其方式是这些和弦的所有 $2k$ 个端点是不同的。

你想画出 $n-k$ 条额外的和弦，连接剩余的$ 2(n-k)$ 个点（每个点必须正好是一个和弦的端点）。

最后，让 $x$ 成为所有 $n$ 条弦的交叉点的总数。计算如果你以最佳方式选择 $n-k$ 条弦，$x$ 能达到的最大值。
请注意，$2n$ 个点的确切位置并不重要，只要第一段中所述的属性成立即可。


## 解题思路

### 首先考虑 $k = 0$ 的情况：

显然我们希望连一条新的弦的时候，与尽可能多的已有的弦相交，而根据题目所给的性质，我们可以知道连一条新的弦可以与所有已有的弦相交，所以我们构造如下方法：一个圆上有 $2n$ 个不同的点，对于一个点 $i$ ，连接它与它的对点形成一条新的弦，它的对点是 $i+n$。
![在这里插入图片描述](https://img-blog.csdnimg.cn/ebef20d8e7ce406cb39bf9b228b615f3.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2JlbGwwNDEwMzA=,size_16,color_FFFFFF,t_70#pic_center)
如此构造可以使得每一条弦都与剩余的弦全部相交，所以答案为 $\operatorname{ans} = \sum_{i = 1}^{n} i=\dfrac{n(n-1)}{2}$

### 然后考虑  $k=1$ 的情况：

对于如下情况：
![在这里插入图片描述](https://img-blog.csdnimg.cn/17b55c46b75f4f15acc7493bb0e26052.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2JlbGwwNDEwMzA=,size_16,color_FFFFFF,t_70#pic_center)

我们考虑令新连上的边尽可能多的与已连边相交，并且新连的边尽可能多的互交。为了使新连上的边尽可能多的与已连边相交，我们已连边下方的 $a$ 个点全部与上方的点相连，得到 $a$ 个交点，同时将这 $a+b$ 个点看作一个新的圆，用  $k=0$ 的情况中的构造方法计算即可，最终答案 $\operatorname{ans} = a+\dfrac{(a+b)(a+b+1)}{2}$

### 最后考虑普遍情况：

其实对于所有情况，我们只要将没有连上边的点全部提出来运用最开始提到的构造方法就可以使得获得的交点最多。对于结论的证明可以考虑用 $k=1$ 的情况类推到所有情况，因为可以将所有已连上的边单独考虑，所以从子问题归纳使得总问题的解法正确性得证。除此以外，考虑新连两条边与已有的一条边的情况，通过画图得知，无论已有的一条边与新连的两条边关系如何，新连的两条边相交总会使得总交点数不减少，所以令任意两条新边相交即为最佳答案。

新连边的交点可以利用公式求得，至于已有边之间的交点与已有边和新连边的交点可以枚举判断求得，对于圆上的点 $a,b,c,d(a<b,c<d)$ 所连成的两条弦 $(a,b),(c,d)$ ，它们相交的条件是 $a<c<b<d$ 或 $c<a<d<b$，时间复杂度$O(n^2)$


------------


### 参考程序

```cpp
#include<iostream>
#include<cstdio>
#include<fstream>

using namespace std;
int n,k,T,ans;
int p[5005][2],a[5005],cnt,x,y;
bool vis[5005];

int main()
{
//	freopen("intersect.in","r",stdin);
//	freopen("intersect.out","w",stdout);
	scanf("%d",&T);
	for(int t = 1;t <= T;t ++)
	{
		scanf("%d%d",&n,&k);
		ans = 0;
		if(k == 0)
		{
			for(int i = 1;i < n;i ++)
				ans += i;
			printf("%d\n",ans);
			continue;
		}
		cnt = 0;
		for(int i = 1;i <= (n+n);i ++ ) vis[i] = 0;
		for(int i = 1;i <= k;i ++)
		{
			scanf("%d%d",&x,&y);
			p[i][0] = min(x,y);
			p[i][1] = max(x,y);
			vis[x] = vis[y] = 1;
		}
		for(int i = 1;i <= (n+n);i ++)
			if(vis[i] == 0)
			{
				cnt ++;
				a[cnt] = i; 
			}
		for(int i = 1;i <= (cnt/2);i ++)
		{
			p[k+i][0] = a[i];
			p[k+i][1] = a[i+(cnt/2)];
		}
		for(int i = 1;i <= k;i ++)
			for(int j = i+1;j <= n;j ++)
				if((p[i][0] < p[j][0] && p[j][0] < p[i][1] && p[i][1] < p[j][1]) || (p[j][0] < p[i][0] && p[i][0] < p[j][1] && p[j][1] < p[i][1]))
					ans ++;
		for(int i = 1;i < (cnt/2);i ++) ans += i;
		printf("%d\n",ans);
	}
	
	return 0;
} 
```



---

## 作者：Eibon (赞：4)

如果两个圆想要相交，则一个的左端点编号小于另一个的右端点编号，大于另一个的左端点编号，且右端点编号大于另一个的右端点编号。

容易发现，将剩余的未使用的点拿出来编号，将 $i$ 号与 $i+n-k$ 号连接在一起是最优的。

只考虑新交的这些弦，考虑如果将这些新交的点进行互换，只会减少交点，使得某两条弦不相交。

再考虑已有的弦，这同样是最优的，因为如果将这些弦交换，并不能增加交点数。

### CODE1

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=200+5;
int T,n,k,L,sum,VIP,ans,cnt;
int num[maxn],b[maxn];
struct node
{
	int x,y;
};
node a[maxn];
signed main()
{
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&n,&k);
		L=n-k;
		for(int i=1;i<=k;i++){
			scanf("%lld%lld",&a[i].x,&a[i].y);
			if(a[i].x>a[i].y){
				swap(a[i].x,a[i].y);
			}
			num[a[i].x]++;
			num[a[i].y]++;
		}
		cnt=k;
		for(int i=1;i<=2*n;i++){
			if(num[i]||b[i]){
				continue;
			}
			a[++cnt].x=i;
			//cout<<"o:"<<cnt<<" "<<i<<endl;
			sum=0;
			for(int j=i+1;j<=2*n;j++){
				if(!num[j]){
					sum++;
				}
				if(sum==L){
					a[cnt].y=j;
					b[j]=1;
					break;
				}
			}
		}
		ans=0;
		//cout<<"v:"<<cnt<<" "<<n<<endl;
		for(int i=1;i<=n;i++){
			//cout<<a[i].x<<" "<<a[i].y<<endl;
			for(int j=1;j<=n;j++){
				if(a[i].x<a[j].x&&a[i].y<a[j].y&&a[j].x<a[i].y){
					ans++;
				}
			}
		}
		printf("%lld\n",ans);
		for(int i=1;i<=k;i++){
			num[a[i].x]=0;
			num[a[i].y]=0;
		}
		for(int i=1;i<=2*n;i++){
			b[i]=0;
		}
	}
	return 0;
}
//dyyyyds
```

### CODE2

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=200+5;
int T,n,k,L,sum,VIP,ans,cnt;
int num[maxn],b[maxn];
struct node
{
	int x,y;
};
node a[maxn];
signed main()
{
	scanf("%lld",&T);
	while(T--){
		ans=cnt=0;
		scanf("%lld%lld",&n,&k);
		for(int i=1;i<=2*n;i++){
			num[i]=0;
		}
		for(int i=1;i<=k;i++){
			scanf("%lld%lld",&a[i].x,&a[i].y);
			if(a[i].x>a[i].y){
				swap(a[i].x,a[i].y);
			}
			num[a[i].x]=num[a[i].y]=1;
		}
		for(int i=1;i<=2*n;i++){
			if(num[i]){
				continue;
			}
			b[++cnt]=i;
		}
		for(int i=1;i<=cnt/2;i++){
			a[++k].x=b[i];
			a[k].y=b[i+cnt/2];
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(a[i].x<a[j].x&&a[i].y<a[j].y&&a[j].x<a[i].y){
					ans++;
				}
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
//dyyyyds
```

---

## 作者：Cure_Wing (赞：0)

说明：修正了数学公式。

------------


[CF1552C Maximize the Intersections](https://www.luogu.com.cn/problem/CF1552C)

### 思路

如果一开始没有连线，那么就变成了基础题：$n$ 条不重合的直线最多能形成几个交点。

对于这个问题，我们的答案是让后进来的每一条直线与前面的每一条直线都产生一个交点。而放到本题，也就是 $k=0$ 的特殊情况，我们可以让 $i$ 与 $i+n$ 分别连一条弦。由于题目保证了任意三条弦不交于一点，所以这样子得到的一定是最大值。

而当 $k>0$ 时，我们选择未被连接的点，让它们依次编号，继续按如上方式连边。这样子，新添的弦之间的交点达到了最大值，而已添的弦交点个数不会发生变化，所以我们需要考虑新添的弦与已添的弦交点个数。

考虑对于已添的一条弦最多能多产生几个交点。我们设这条弦把圆上还未连接的点的个数分为了 $a,b$ 个，那么容易得出它们连线最多能与这条弦有 $\min\{a,b\}$ 个交点。因为唯一产生交点的方式是选择左边的一个点，再选择右边的一个点连线。而当我们用 $k=0$ 的方式连接时，因为 $\frac{a+b}{2}\ge\min\{a,b\}$，所以含有较少点的那一侧一定会全部向对面连边，也就达到了这条弦的最大值。

至此，我们证明了这样连边的正确性。

连完边后，直接暴力数交点即可，时间复杂度 $O(\sum(n^2))$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using std::cin;using std::cout;
constexpr int N=103;
int t,n,k,p[N][2],r[N<<1],m,ans;
bool vis[N<<1];
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
    for(cin>>t;t--;cout<<ans<<'\n'){
        cin>>n>>k;ans=m=0;
        for(int i=1;i<=2*n;++i) vis[i]=0;
        for(int i=1;i<=k;++i){
            cin>>p[i][0]>>p[i][1];
            if(p[i][0]>p[i][1]) std::swap(p[i][0],p[i][1]);
            vis[p[i][0]]=vis[p[i][1]]=1;
        }
        for(int i=1;i<=2*n;++i) if(!vis[i]) r[++m]=i;
        for(int i=1;i<=m/2;++i){p[++k][0]=r[i];p[k][1]=r[i+m/2];}//上述连边
        for(int i=1;i<=k;++i)//统计交点
            for(int j=1;j<=k;++j)
                ans+=p[i][0]<p[j][0]&&p[j][0]<p[i][1]&&p[i][1]<p[j][1];
    }
    return 0;
}
```

---

## 作者：AmamiyaYuuko (赞：0)

考虑如何最大化加上去的边的交点个数。设要加的边的端点为 $1, 2, \cdots, 2(n - k)$，不难发现连边 $i \rightarrow i + n - k$ 是最优的，在这种情况下，任意交换两条边的端点都会减少答案。

这样连边是否会减少与已有的边之间的交点个数呢？答案是不会。我们可以分类讨论这样的情况：

设点为 $a, b, c, d$，当它们在某一条边同侧时，显然交点个数都为 $0$。

当 $a$ 在边的一侧，$b, c, d$ 在边的另一侧时，$a \rightarrow (b, c, d)$ 中总会有一条边产生贡献，剩下的边如果相交则会再产生一个交点。

当 $a, b$ 在边的一侧，$c, d$ 在另一侧时，很容易发现 $a \rightarrow c$ 和 $b \rightarrow d$ 是最优的。

于是我们只需要统计没有使用的点，然后通过上面的策略连边，之后 $O(n^2)$ 统计答案即可。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

template <class T>
inline void read(T &x) {
    x = 0;
    int f = 0;
    char ch = getchar();
    while (!isdigit(ch))    { f |= ch == '-'; ch = getchar(); }
    while (isdigit(ch))     { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
    x = f ? -x : x;
    return ;
}

typedef unsigned long long uLL;
typedef long long LL;

struct Node {
    int x, y;
};

std::vector<Node> g;
std::vector<int> v;
int T, n, k, ans;
bool vis[210];

bool check(Node a, Node b) {
    if (a.x > b.x)    std::swap(a, b);
    return a.x < b.x && b.x < a.y && a.y < b.y;
}

int main() {
    read(T);
    while (T--) {
        g.clear(), v.clear(), ans = 0;
        read(n), read(k);
        for (int i = 1; i <= n + n; ++i)    vis[i] = false;
        for (int i = 1, x, y; i <= k; ++i) {
            read(x), read(y);
            if (x > y)    std::swap(x, y);
            g.push_back((Node){x, y});
            vis[x] = vis[y] = true;
        }
        for (int i = 1; i <= n + n; ++i) {
            if (!vis[i]) {
                v.push_back(i);
            }
        }
        for (int i = 0; i < n - k; ++i)    g.push_back((Node){v[i], v[i + n - k]});
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                ans += check(g[i], g[j]);
            }
        }       
        printf("%d\n", ans);
    }
    return 0;
}
```

---

