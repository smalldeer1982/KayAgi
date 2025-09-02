# [USACO20DEC] Rectangular Pasture S

## 题目描述

Farmer John 最大的牧草地可以被看作是一个由方格组成的巨大的二维方阵（想象一个巨大的棋盘）。现在，有 $N$ 头奶牛正占据某些方格（$1≤N≤2500$）。

Farmer John 想要建造一个可以包围一块矩形区域的栅栏；这个矩形必须四边与 $x$ 轴和 $y$ 轴平行，最少包含一个方格。请帮助他求出他可以包围在这样的区域内的不同的奶牛子集的数量。注意空集应当被计算为答案之一。 

## 说明/提示

共有 $2^4$ 个子集。FJ 不能建造一个栅栏仅包围奶牛 $1$、$2$、$4$，或仅包围奶牛 $2$、$4$，或仅包围奶牛 $1$、$4$，所以答案为 $2^4-3=16-3=13$。 

 - 测试点 2-3 满足 $N≤20$。
 - 测试点 4-6 满足 $N≤100$。
 - 测试点 7-12 满足 $N≤500$。
 - 测试点 13-20 没有额外限制。

供题：Benjamin Qi 

## 样例 #1

### 输入

```
4
0 2
1 0
2 3
3 5```

### 输出

```
13```

# 题解

## 作者：SBofGaySchool (赞：24)

我来一发纯暴力的吧，不用什么树状数组，也不用（手动）离散化和前缀和，直接暴力肝就好。

### 1. 思路

显然，每行、每列都至多只有一个点。对行坐标排序，滤掉没有牛的行（这实际上相当于离散化）。设 $a[i]$ 代表第 $i$ 行的那头牛所在的列坐标。

考虑下侧木板在第 $i$ 行，上侧木板在第 $j$ 行的情况。**为了避免相同情况重复计算（即围栏形状不同，但圈住的牛相同），第 $i$ 行的牛和第 $j$ 行的牛必须被圈住**。

- 如果第 $j$ 行的牛在第 $i$ 行的牛左边（即 $a[i] > a[j]$）：
  - 任何一头在 **第 $i$ 行与第 $j$ 行之间，在第 $j$ 行的牛左边** 的牛，即满足 **$i<k<j,a[k]<a[j]$ 的 $k$**，都可以作为左侧围栏所在位置的选项（如果不满足此条件，则第 $j$ 行的牛无法被圈住）；当然，第 $j$ 行的牛本身（$a[j]$）也可以作为左侧围栏所在位置的选项。
  
   - 任何一头在 **第 $i$ 行与第 $j$ 行之间，在第 $i$ 行的牛右边** 的牛，即满足 **$i<k<j,a[k]>a[i]$ 的 $k$**，都可以作为右侧围栏所在位置的选项（如果不满足此条件，则第 $i$ 行的牛无法被圈住）；当然，第 $i$ 行的牛本身（$a[i]$）也可以作为右侧围栏所在位置的选项。

- 第 $j$ 行的牛在第 $i$ 行的牛右边（即 $a[i] < a[j]$）的情况同理。

所以，下侧木板在第 $i$ 行，上侧木板在第 $j$ 行的所有可能，即为 **左侧围栏选项总数** $\times$ **右侧围栏选项总数**。

我们只需在枚举 $i,j$ 的过程中，维护：

- 对于第 $i$ 行的牛，在第 $i$ 行与第 $j$ 行之间，有多少头牛在它的左边/右边；
- 对于第 $j$ 行的牛，有第 $i$ 行与第 $j$ 行之间，有多少头牛在它的左边/右边；

顺带累加答案，即可轻松完成此题。

时间复杂度为 $O(N^2)$。

### 2. 代码实现

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
#define MAXN 2505
ll N;
// 每头牛的行/列坐标
pair<ll, ll> x[MAXN];
// 先算上空集
ll ans = 1;
// l[j]代表【第j行的牛】与【当前第i行的牛】之间，有多少头牛在【第j行的牛】左边
// r[j]同理
ll l[MAXN], r[MAXN];
int main() {
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> x[i].first >> x[i].second;
    // 按行坐标排序
    sort(x, x + N);
    // 枚举i
    for (ll i = 0; i < N; i++) {
        ans++;
        // lt代表【第i行的牛】与【当前第j行的牛】之间，有多少头牛在【第i行的牛】左边
        // rt同理
        ll lt = 0, rt = 0;
        for (ll j = i - 1; j >= 0; j--) {
            // 根据【第i行的牛】与【第j行的牛】的相对位置，累加答案，更新计数
            if (x[i].second > x[j].second) {
                ans += (rt + 1) * (l[j] + 1);
                r[j]++;
                lt++;
            } else {
                ans += (lt + 1) * (r[j] + 1);
                l[j]++;
                rt++;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Skies (赞：21)

# 这道题是二位前缀和+一点点思维的题

## 1.思路

我们先离散化

把整张地图压缩到n*n,类似8皇后的地图（每行每列只有一个点）
```cpp
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&po[i].x,&po[i].y);
		ax[i]=po[i].x;ay[i]=po[i].y;
	}
	sort(ax+1,ax+n+1);
	sort(ay+1,ay+n+1);
	for(int i=1;i<=n;i++)
	{
		po[i].x=lower_bound(ax+1,ax+n+1,po[i].x)-ax;
		po[i].y=lower_bound(ay+1,ay+n+1,po[i].y)-ay;
		s[po[i].x][po[i].y]=1;//这里后面前缀和要用
//		cout<<po[i].x<<" "<<po[i].y<<endl;
	}
```


~~二位前缀和应该也都会吧~~

这里我们用他来维护一块区域内的奶牛数

```cpp
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];
		}
	}
    
```
然后想想怎么统计答案

无论矩形长什么样，只要围住相同的牛就是一样的

### 考虑最小的矩形即可

所以矩形的边上一定有一头奶牛

我们先O(n^2)枚举矩形上下两条边

然后看左右两边

假设我们将奶牛a=(xa,ya)和b=(xb,yb)固定在矩形的上下两侧(因此ya≤yb)。那么矩形左边的牛c必须满足xc≤min(xa,xb)和ya≤yc≤yb。

同理，矩形右边的牛d必须满足max(xa,xb)≤xd和ya≤yd≤yb。

换句话说，c的可能数量是矩形内的点的数量[1,min(xa,xb)]×[ya,yb]，而d的可能数量是矩形内的奶牛数量[max(xa,xb)，n]×[ya,yb]。我们可以用二维前缀和来计算这些量。

## code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
const int N=2501;
int ax[N],ay[N];
struct node{
	int x,y;
}po[N];
int s[N][N];
bool cmp(node x,node y)
{
	return x.y<y.y;
}
int get(int x1,int y1,int x2,int y2)
{
	return s[x2][y2] - s[x2][y1-1] - s[x1-1][y2] + s[x1-1][y1-1];
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&po[i].x,&po[i].y);
		ax[i]=po[i].x;ay[i]=po[i].y;
	}
	sort(ax+1,ax+n+1);
	sort(ay+1,ay+n+1);
	for(int i=1;i<=n;i++)
	{
		po[i].x=lower_bound(ax+1,ax+n+1,po[i].x)-ax;
		po[i].y=lower_bound(ay+1,ay+n+1,po[i].y)-ay;
		s[po[i].x][po[i].y]=1;
//		cout<<po[i].x<<" "<<po[i].y<<endl;
	}
   //离散化
	sort(po+1,po+n+1,cmp);//以y为关键字排序，以便后面计算
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];//前缀和
		}
	}
	ll ans=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
			int x1=min(po[i].x,po[j].x),x2=max(po[i].x,po[j].x);
			ans+=get(1,po[i].y,x1,po[j].y)*get(x2,po[i].y,n,po[j].y);
		}
	}
	cout<<ans+1;//空矩形+1
	
	return 0;
}
```
~~管理员大大求过~~

---

## 作者：chlchl (赞：15)

这篇题解估计是**最最最暴力**的题解了，代码保证大家看懂。

不用**算法**，不用**数据结构**，只需要结构体和排序+一点点思维。

等等，还没可以开始打代码！

- 注意**空集**应当被**计算为答案之一**。

因此，一定要对答案额外 +1，初始化为 1 或者最后输出答案 +1 都可以。

$Code:$
```cpp
//#include<bits/stdc++.h> (考试怕爆零)
#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;

const int N = 2500 + 10;
ll n, ans = 1, l[N], r[N];
//ans一定要初始化为1

struct node{
	int x, y;
} index[N];//结构体存坐标

bool cmp(node xx, node yy){
	if(xx.x == yy.x)	return xx.y < yy.y;
	else	return xx.x < yy.x;
}//排序规则

int main(){
    cin >> n;
    for(int i=0;i<n;i++)	cin >> index[i].x >> index[i].y;//读入
    sort(index, index + n, cmp);//能做绿题的这个应该都会了
    for(ll i=0;i<n;i++){
        ans++;
        ll cntl = 0, cntr = 0;
        for(ll j=i-1;j>=0;j--){
            if(index[i].y > index[j].y){
                ans += (cntr + 1) * (l[j] + 1);
                r[j]++;
                cntl++;
                //枚举第 i 到 j 行之间，有多少头牛在它的左边。
            }else{
                ans += (cntl + 1) * (r[j] + 1);
                l[j]++;
                cntr++;
                //枚举第 i 到 j 行之间，有多少头牛在它的右边
            }
            //这里就是上面说的操作
        }
    }
    cout << ans << endl;
    return 0;//码量也不多，就是一道思维题吧
}
```

如果看完觉得绿题好像~~没有想象中这么难~~，就别吝啬点个赞啦。
### 拜拜

---

## 作者：wsyhb (赞：12)

## 题意简述

网格图上有 $N$ 头奶牛，第 $i$ 头奶牛坐标为 $(x_i,y_i)$。

现在用一个大小至少为 $1$ 的矩形覆盖若干格子，问被覆盖的区域包含的奶牛集合有多少种情况，包含空集。（矩形恰好完整覆盖若干格子）

**数据范围与约定**：$N \le 2500$，$0 \le x_i,y_i \le 10^9$ 且**保证 $x_i$ 和 $y_i$ 分别互不相同**。

## 分析 + 题解

由于不包含奶牛的格子不影响答案，考虑离散化，将其转化为一个 $N \times N$ 的棋盘，设第 $i$ 头奶牛坐标为 $(i,p_i)$（将奶牛从左到右排序）。

我们考虑将**矩形区域中最靠左的奶牛和最靠右的奶牛**作为矩形的标志，对于每种标志单独统计情况数，避免算重。

设第 $i$ 头奶牛最靠左，第 $j$ 头奶牛最靠右，其中 $i<j$。由于该矩形左右边界确定，考虑其上下边界——

设下边界为 $l$，上边界为 $r$，记 $a=\min(p_i,p_j)$，$b=\max(p_i,p_j)$，则 $l \le a$ 且 $r \ge b$。

设 $cnt_1$ 表示第 $i+1$ 至 $j-1$ 头奶牛中纵坐标 $\le a$ 的点的个数，$cnt_2$ 表示这些奶牛中纵坐标 $\ge b$ 的点的个数，形式化地说：

$$cnt_1=\sum_{k=i+1}^{j-1}[p_k \le a] , cnt_2=\sum_{k=i+1}^{j-1}[p_k \ge b]$$

由乘法原理可知这样的情况数为 $(cnt_1+1)(cnt_2+1)$，说明如下：

由于下边界可以位于这 $cnt_1$ 个点中任意两个相邻点之间，也有可能在其上方或下方，故有 $cnt_1+1$ 种可能，上边界同理。

**最后别忘了考虑奶牛集合大小 $\le 1$ 的情况**——

1. 不包含奶牛，$1$ 种情况（即空集）；

2. 包含一头奶牛，$N$ 种情况（即 $1 \times 1$ 的正方形）。

具体实现的话，枚举 $i,j$，并在枚举 $j$ 的同时，将当前点的纵坐标加入树状数组，查询可知当前的 $cnt_1$ 和 $cnt_2$。

总时间复杂度：$O(N^2log_{2}N)$

## 代码

如果还有不清楚的地方就看代码吧，有详细注释哟~

``` cpp
#include<bits/stdc++.h>
using namespace std;
int N;
const int max_N=2500+5;
struct node
{
	int x,y;
}p[max_N];//结构体记录节点信息 
bool cmp(node a,node b)
{
	return a.x<b.x;
}//按横坐标从左到右排序 
int Hash[max_N];//用于离散化 
namespace BIT//树状数组相关操作 
{
	int c[max_N];
	inline void init()
	{
		for(int i=1;i<=N;++i)
			c[i]=0;
	}
	inline void modify(int k,int v)
	{
		if(k>0)
		{
			for(int i=k;i<=N;i+=i&(-i))
				c[i]+=v;
		}
	}
	inline int query(int k)
	{
		int res=0;
		for(int i=k;i>0;i-=i&(-i))
			res+=c[i];
		return res;
	}
}
int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N;++i)
		scanf("%d%d",&p[i].x,&p[i].y);
	sort(p+1,p+N+1,cmp);//此处没有必要将横坐标标为 1~N，因为我们会使用下标来表示它 
	for(int i=1;i<=N;++i)
		Hash[i]=p[i].y;
	sort(Hash+1,Hash+N+1);
	for(int i=1;i<=N;++i)
		p[i].y=lower_bound(Hash+1,Hash+N+1,p[i].y)-Hash;//离散化 
	long long ans=N+1;//初始值为 N+1，并且记得开 long long 
	for(int i=1;i<=N;++i)
	{
		BIT::init();//清空树状数组 
		for(int j=i+1;j<=N;++j)
		{
			int l=min(p[i].y,p[j].y);//下边界的上界，对应上文中的 a 
			int r=max(p[i].y,p[j].y);//上边界的下界，对应上文中的 b 
			int a=BIT::query(l-1);//由于横纵坐标分别互不相同，l 与 l-1 均可，下同 
			int b=(j-i-1)-BIT::query(r);//用总数减去后缀 
			ans+=1ll*(a+1)*(b+1);//a,b 对应上文中的 cnt1 和 cnt2 
			BIT::modify(p[j].y,1);//别忘了将纵坐标加入树状数组 
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Unordered_OIer (赞：8)

# P7149 题解
## 题意
求一共有多少个奶牛子集可以被恰好包围住。
## 题解
首先暴力的方法就是枚举子集了。

然后考虑正解：

因为值域是 $10^{9}$，所以要先离散化一下。对于这道题而言离散化对答案其实并没有影响。

考虑先把 $x,y$ 排个序，以此枚举矩形上下界，再考虑这个上下界内其他需要包含的牛。

在上侧牛为 $i$ ，下侧牛为 $j$ 的矩形中最左侧的牛 $k$ 需要满足 $x_k \leq \min(x_i,x_j),y_i \leq y_k \leq y_j$，最右侧的牛 $f$ 需要满足 $x_f \geq \max(x_i,x_j),y_i \leq y_f \leq y_j$。

然后这两个牛的决策使用二维前缀和维护一下即可。

最后要注意的是因为空集也算，所以答案要加上 1。

复杂度 $\mathcal O(n^2)$，期望得分 $100$ 分。

---

## 作者：lnwhl (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P7149)
## 思路
题目说 $x,y$ 都是 $10^9$ 级别的，但其实是个纸老虎，是只要**离散化**一下就可以了。然后求一下**二维前缀和**（后面有用）。

因为子集跟最小矩形一一对应，所以穷举**最小矩形**。因为每行每列最多只有一个棋子，所以可以穷举矩形的四条边，且这四条边必须经过一个棋子，这样保证枚举的每个矩形恰好覆盖一个特定的子集（覆盖该子集的最小矩形）。

暴力的思路肯定是四重循环枚举矩形，然后枚举的上边界的行坐标是否是最小的，列坐标是否在左右边界之间，再判断下边界的的行坐标是否是最大，列坐标是否在左右边界之间，再判断左边界，再判断右边界，如果都和法，则矩形合法。

当然我们需要优化一下：

枚举一个矩形左上角为棋子 $(X_{a},Y_{a})$，右下角为棋子$(X_{b},Y_{b})$.

![](https://cdn.luogu.com.cn/upload/image_hosting/sq8uqz5k.png)

快速统计（用前面算的二维前缀和）有多少个子集的最小覆盖矩形在左边界在点 $A$ 的左侧，右边界在 $B$ 的右侧。也就是统计左侧和右侧上下两虚线之间有多少个点，然后利用**乘法原理**得出答案。

复杂度 $O(n^2)$。

**Tips**:
1. 不要忘了加 $1$，因为空也是一种情况。
2. 记得要开 ```long long``` 啊！

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{int x,y;}poi[2505];
int n,whl1[2505],whl2[2505],sum[2505][2505];
long long ans=0;
int get_s(int a,int b,int c,int d)
{
	return sum[c][d]-sum[a-1][d]-sum[c][b-1]+sum[a-1][b-1];
}
bool cmp(node q,node w){return q.y<w.y;}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>poi[i].x>>poi[i].y;
		whl1[i]=poi[i].x;
		whl2[i]=poi[i].y;
	}	
	sort(whl1+1,whl1+n+1);
	sort(whl2+1,whl2+n+1);
	for(int i=1;i<=n;i++)
	{
		poi[i].x=lower_bound(whl1+1,whl1+n+1,poi[i].x)-whl1;
		poi[i].y=lower_bound(whl2+1,whl2+n+1,poi[i].y)-whl2;
		sum[poi[i].x][poi[i].y]=1;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
	sort(poi+1,poi+1+n,cmp);
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
		{
			int xmin=min(poi[i].x,poi[j].x);
			int xmax=max(poi[i].x,poi[j].x);
			ans+=get_s(1,i,xmin,j)*get_s(xmax,i,n,j); 
		}
	cout<<ans+1;
	return 0;
}
```


---

## 作者：andyc_03 (赞：2)

考虑到每个矩形的边上一定有点，否则我们可以缩小这个矩形，还保证得到的点集不变

所以我们需要先**离散化**一下

然后我们可以枚举最上面一行的点i，和最下面一行的点j   

那么  
最左侧的节点的$x\leq min(x[i],x[j])$ $ y[i]\leq y \leq y[j]$   
最右侧的节点的$x\geq max(x[i],x[j])$ $ y[i]\leq y \leq y[j]$

所以我们可以使用**二维前缀和**维护

时间复杂度:$O(N^2)$


代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2500+5;
typedef long long ll;
int n;
struct point
{
	int x,y;
}p[maxn];
bool cmp(point aa,point bb)
{
	if(aa.x!=bb.x) return aa.x<bb.x;
	return aa.y<bb.y;
}
bool cmpp(point aa,point bb)
{
	return aa.y<bb.y;
}
int pre[maxn][maxn];
ll calc(int x1,int y1,int x2,int y2)
{
	return pre[x2][y2]-pre[x2][y1-1]-pre[x1-1][y2]+pre[x1-1][y1-1];
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&p[i].x,&p[i].y);
	sort(p+1,p+n+1,cmp);
	//离散化 
	for(int i=1;i<=n;i++) p[i].x=i;
	sort(p+1,p+n+1,cmpp);
	for(int i=1;i<=n;i++) p[i].y=i;
	//前缀和 
	for(int i=1;i<=n;i++) pre[p[i].x][p[i].y]=1;
	for(int i=1;i<=n+1;i++)
		for(int j=1;j<=n+1;j++)
			pre[i][j]+=pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1];
	ll ans=0;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
		{
			int l=min(p[i].x,p[j].x);
			int r=max(p[i].x,p[j].x);
			ans+=calc(1,i,l,j)*calc(r,i,n,j);
		}
	printf("%lld",ans+1); //注意空集 
	return 0;
}
```


---

## 作者：xbb2 (赞：1)

### 前置知识：二维前缀和

具体实现：[OI-wiki](https://oi-wiki.org//basic/prefix-sum/#%E4%BA%8C%E7%BB%B4%E5%A4%9A%E7%BB%B4%E5%89%8D%E7%BC%80%E5%92%8C)

简单的来说就是基于容斥原理

### 具体思路

先离散化，在用二维前缀和维护一个矩形中的奶牛个数。

根据题意，可以知矩形区域的大小是和无关的，和答案有的只是其中的奶牛。

所以只要考虑小的矩阵就可以了，容易思考，最小时一定有奶牛在矩形上界和下界。

然后可以尝试暴力枚举一个矩形在上下界的两只奶牛(如图蓝色大框中的红框)。

![](https://cdn.luogu.com.cn/upload/image_hosting/mqi4iser.png)

然后考虑左右边界，容易想到左边界的奶牛数（图中绿色箭头指的框） $+1$ 就是合法的左边界数，右边界的奶牛数（图中橙色箭头指的框） $+1$ 就是合法的右边界数。

左右边界数乘就是答案数。

注意1：开 ```long long``` !!!

注意2：最后答案要 $+1$（考虑空）。

代码：

```cpp
const long long N=2500+10;
const long long mod=1e9+9;
const long long inf=0x3f3f3f3f;
long long n,ans=0,x[N],y[N],f_x[N],f_y[N],sum[N][N];
struct tip{long long x,y;}a[N];
bool cmp(tip a,tip b){return a.y<b.y;}
long long getsum(long long x1,long long y1,long long x2,long long y2){ return sum[x2][y2]-sum[x2][y1-1]-sum[x1-1][y2]+sum[x1-1][y1-1];}
long long check(long long s,long long t){
	return  getsum(1,a[s].y,min(a[s].x,a[t].x),a[t].y)*
			getsum(max(a[s].x,a[t].x),a[s].y,n,a[t].y);
}
int main(){
	cin>>n;
	for(long long i=1;i<=n;i++) scanf("%lld%lld",&a[i].x,&a[i].y);
	for(long long i=1;i<=n;i++) f_x[i]=a[i].x,f_y[i]=a[i].y;
	sort(f_x+1,f_x+1+n),sort(f_y+1,f_y+1+n);
	for(long long i=1;i<=n;i++) a[i].x=lower_bound(f_x+1,f_x+1+n,a[i].x)-f_x;
	for(long long i=1;i<=n;i++) a[i].y=lower_bound(f_y+1,f_y+1+n,a[i].y)-f_y;
	for(long long i=1;i<=n;i++) sum[a[i].x][a[i].y]++;
	for(long long i=1;i<=n;i++)
		for(long long j=1;j<=n;j++)
			sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
	sort(a+1,a+1+n,cmp);
	for(long long i=1;i<=n;i++)
		for(long long j=i;j<=n;j++)
			ans+=check(i,j);
	printf("%lld",ans+1);
	return 0;
}

```


---

## 作者：Coros_Trusds (赞：1)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15730144.html)

不需 $\operatorname{Discretization}\&\operatorname{BIT}$ 并且时间复杂度优秀的一篇题解！

本篇题解是对 [这篇题解](https://www.luogu.com.cn/blog/_post/300106) 的补充。

# 题目大意

网格图上有 $N$ 头奶牛，第 $i$ 头奶牛坐标为 $(x_i,y_i)$。

现在用一个大小至少为 $1$ 的矩形覆盖若干格子，问被覆盖的区域包含的奶牛集合有多少种情况，包含空集。（矩形恰好完整覆盖若干格子）

# 题目分析

> _我们没必要将边界放在空格上。_

我们首先对所有坐标按照行从小到大排序。**之后所有的牛都按照这个顺序来操作。**

设 $y[i]$ 表示第 $i$ 头牛的列，$l[j]$ 表示第 $j$ 行的牛与当前第 $i$ 行的牛之间,有多少头牛在第 $j$ 行的牛的左边，$r[j]$ 表示第 $j$ 行的牛与当前第 $i$ 行的牛之间,有多少头牛在当前第 $i$ 行的牛的右边。

因为我们需要求出包含的奶牛集合有多少种情况 ，所以我们不妨讨论第 $i$ 头奶牛作为下方边界，第 $j$ 头奶牛作为上方边界。

这样子，我们就将题目简化了。接下来分情况讨论：

1. 第 $j$ 头牛在第 $i$ 头牛的左边时：

	+ 当第 $k$ 行的牛在第 $i$ 行的牛在第 $j$ 头牛之间且在第 $j$ 头牛左边，即 $i\lt k\lt j,y[k]\lt y[j]$ 时：

	$k$ 一定可以作为当前框定的左边界，当前情况的方案数为 $(rnum+1)\times(l[j]+1)$。

	$rnum$ 表示第 $i$ 行的牛与当前第 $j$ 行的牛之间，有多少头牛在第 $i$ 行的牛右边。加 $1$ 是因为可以选择边界。
    
    + 当第 $k$ 行的牛在第 $i$ 行的牛在第 $j$ 头牛之间且在第 $i$ 头牛右边，即 $i\lt k\lt j,y[k]\gt y[i]$ 时：

	$k$ 一定可以作为当前框定的右边界，当前情况的方案数为 $(lnum+1)\times(r[j]+1)$。

	$lnum$ 表示第 $i$ 行的牛与当前第 $j$ 行的牛之间，有多少头牛在第 $j$ 行的牛左边。加 $1$ 是因为可以选择边界。

2. 第 $j$ 头牛在第 $i$ 头牛的右边时同理。

---
时间复杂度 $\mathcal{O}(n^2)$。

# 代码

```cpp
#define int long long

const int ma=2505;

struct Node
{
	int x;
	
	int y;
};

Node node[ma];

int l[ma],r[ma];
//l[j]:排序后,第 j 行的牛与当前第 i 行的牛之间,有多少头牛在第 j 行的牛的左边
//r[j]:排序后,第 j 行的牛与当前第 i 行的牛之间,有多少头牛在当前第 i 行的牛的右边

int n;

inline bool cmp(Node x,Node y)
{
	if(x.x!=y.x)
	{
		return x.x<y.x;
	}
	
	return x.y<y.y;
}

#undef int

int main(void)
{
	#define int long long
	
	n=read();
	
	for(register int i=1;i<=n;i++)
	{
		node[i].x=read(),node[i].y=read();
	}
	
	sort(node+1,node+n+1,cmp);
	
	int ans=1;
	 
	for(register int i=1;i<=n;i++)
	{
		ans++;
		
		int lnum=0,rnum=0;
		
		for(register int j=i-1;j>=1;j--)
		{
			if(node[i].y>node[j].y)
			{
				ans+=(rnum+1)*(l[j]+1);
				
				lnum++,r[j]++; 
			}
			
			else
			{
				ans+=(lnum+1)*(r[j]+1);
				
				rnum++,l[j]++;
			}
		}
	}
	
	printf("%lld\n",ans);
	
	return 0;
}
```

---

## 作者：ETHANK (赞：1)

## 题意
二维方阵上$N$头奶牛，第$i$头坐标为$(x_i,y_i)$，问有多少种恰好被矩形覆盖的奶牛子集(可以为空集)。
## 思路

先对数据进行离散化和排序，然后枚举矩形的最左点$i$和最右点$j$。发现矩形的上边最小为$u=max(y_i,y_j)$，下边最大为$d=min(y_i,y_j)$。子集数量则为满足$x_i<x<x_j,y>u$的$(x,y)$点数量，与$x_i<x<x_j,y<d$的$(x,y)$数量相乘。

如何统计这些点的个数呢？我们可以二维前缀和预处理，时间复杂度为$\Theta(n^2)$，可以通过本题。


## 代码

### 时间复杂度:$\Theta(n\log n)+\Theta(n^2)$
```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
struct node{
    int x,y;
}a[2505];
bool cmp(node a,node b){
    if(a.x==b.x)return a.y<b.y;
    return a.x<b.x;
}
int n,tot,f[2505],sum[2505][2505];
ll ans;
inline ll getsum(int l,int r,int x,int y){
    return sum[r][y]-sum[l-1][y]-sum[r][x-1]+sum[l-1][x-1];
}
int main(){
    n=read();
    for(int i=1;i<=n;i++){
        a[i].x=read(),a[i].y=read();
    }
    //离散化
    for(int i=1;i<=n;i++)f[i]=a[i].x;
    sort(f+1,f+n+1);
    for(int i=1;i<=n;i++)a[i].x=lower_bound(f+1,f+n+1,a[i].x)-f;
    for(int i=1;i<=n;i++)f[i]=a[i].y;
    sort(f+1,f+n+1);
    for(int i=1;i<=n;i++)a[i].y=lower_bound(f+1,f+n+1,a[i].y)-f;
    for(int i=1;i<=n;i++)sum[a[i].x][a[i].y]++;
    for(int i=1;i<=n;i++){//预处理二维前缀和
        for(int j=1;j<=n;j++){
            sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
        }
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            int up=max(a[i].y,a[j].y),down=min(a[i].y,a[j].y);
            //上面数量
            ll upans=1+getsum(i,j,up+1,n);
            //下面数量
            ll dans=1+getsum(i,j,1,down-1);
            ans+=upans*dans;
        }
    }
    printf("%lld\n",ans+1);//算空集
    return 0;
}
```

---

## 作者：MolotovM (赞：1)

# 树状数组维护计数

先离散化点的坐标

按横坐标升序排序

枚举起点和终点

对于每个子集，只有包含起点和终点才能保证不与其他区间统计时重复

确定横坐标区间的合法子集个数为可行的上起点个数和可行的下起点个数之积

可以乘法原理统计

树状数组维护当前横坐标区间内纵坐标区域点数即可

时间复杂度$O(nlogn)$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int Read(){
  	int s = 0 , w = 1;
	char ch = getchar();
	while(ch > '9' || ch < '0'){
		if(ch == '-') w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		s = (s << 1) + (s << 3) + ch - '0';
		ch = getchar();
	}
	return s * w;
}
const int MAXN = 2500 + 50;
struct Pnt{
	int x,y,id;
}s[MAXN];
int n;
bool cmpx(Pnt a,Pnt b){
	return a.x < b.x;
}
bool cmpy(Pnt a,Pnt b){
	return a.y < b.y;
}
bool cmpid(Pnt a,Pnt b){
	return a.id < b.id;
}
int ans;
int t[MAXN];
int lowbit(int x){
	return x&(-x);
}
void add(int pos,int x){
	while(pos <= n){
		t[pos] += x;
		pos += lowbit(pos);
	}
}
int query(int pos){
	int res = 0;
	while(pos > 0){
		res += t[pos];
		pos -= lowbit(pos);
	}
	return res;
}
#undef int 
int main(){
	#define int long long
	n = Read();
	for(int i = 1 ; i <= n ; i ++){
		s[i].x = Read() , s[i].y = Read() , s[i].id = i;
	}
	sort(s + 1,s + 1 + n,cmpx);
	for(int i = 1 ; i <= n ; i ++){
		s[i].x = i;
	}
	sort(s + 1,s + 1 + n,cmpy);
	for(int i = 1 ; i <= n ; i ++){
		s[i].y = i;
	}
	sort(s + 1,s + 1 + n,cmpx);
	for(int i = 1 ; i <= n ; i ++){
		ans ++;
		add(s[i].y,1);
		for(int j = i + 1 ; j <= n ; j ++){
			add(s[j].y,1);
			int res;
			if(s[j].y > s[i].y) res = (query(n) - query(s[j].y - 1)) * query(s[i].y);
			else if(s[j].y < s[i].y) res = (query(n) - query(s[i].y - 1)) * query(s[j].y);
			ans += res;
		}
		memset(t,0,sizeof(t));
	}
	cout << ans + 1 << endl;
	return 0;
}
```

---

## 作者：Ark__Skadi (赞：0)

# 前言

大家好像都是 $O(n^2)$ 的算法，这里给一种思想暴力的简单算法。
# 前置芝士
[树树树树状数组](https://www.luogu.com.cn/problem/P3374)
# 题解
不难发现，我们可以枚举两头奶牛来圈定一个矩形的基础范围。

而在范围内的奶牛是必选的。

则我们可以按 $x$ 坐标排序，每次扫到一个点计算已经扫到过

（即横坐标在范围内）的不在基础范围内的点（即可以扩大矩

形包进来）的选择方式（上×下）

我们使用树状数组动态统计大于基础范围上界或小于下界的点

数，每次清空即可。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct node{
	int x,y;
}a[2505];
long long ans;
bool cmp1(node x,node y)
{
	return x.x<y.x;
}
bool cmp2(node x,node y)
{
	return x.y<y.y;
}
int lowbit(int x)
{
	return x&-x; 	
}
struct BIT{
	int c[2505];
	void update(int x,int v)
	{
		while(x<=n)
		{
			c[x]+=v;
			x+=lowbit(x);
		}
	}
	int query(int x)
	{
		int sum=0;
		while(x)
		{
			sum+=c[x];
			x-=lowbit(x);
		}
		return sum;
	}
}c1,c2;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].x>>a[i].y;
	sort(a+1,a+n+1,cmp2);
	for(int i=1;i<=n;i++)
		a[i].y=i;
	sort(a+1,a+n+1,cmp1);
	for(int i=1;i<=n;i++)
	{
		memset(c1.c,0,sizeof(c1.c));
		memset(c2.c,0,sizeof(c2.c));
//		cout<<a[i].x<<' '<<a[i].y<<endl;
		ans++;
		for(int j=i+1;j<=n;j++)
		{
//			for(int k=1;k<=n;k++)
//				cout<<c2.query(k)<<' ';
//			cout<<endl;
			ans+=(c2.query(min(a[i].y,a[j].y))+1)*(c1.query(max(a[i].y,a[j].y))+1);
			c2.update(a[j].y,1);
			c1.update(a[j].y,-1);
			c1.update(1,1);
		}
//		cout<<ans<<endl;
	}
	cout<<ans+1<<endl;
}
```


---

