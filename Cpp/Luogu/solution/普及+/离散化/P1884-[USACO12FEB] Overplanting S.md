# [USACO12FEB] Overplanting S

## 题目描述

Farmer John has purchased a new machine that is capable of planting grass within any rectangular region of his farm that is "axially aligned" (i.e., with vertical and horizontal sides).  Unfortunately, the machine malfunctions one day and plants grass in not one, but N (1 <= N <= 1000) different rectangular regions, some of which may even overlap.

Given the rectangular regions planted with grass, please help FJ compute the total area in his farm that is now covered with grass.

在一个笛卡尔平面坐标系里（则 $X$ 轴向右是正方向，$Y$ 轴向上是正方向），有 $N\ (1 \le N \le 1000)$ 个矩形，第 $i$ 个矩形的左上角坐标是 $(x_1,y_1)$，右下角坐标是 $(x_2,y_2)$。问这 $N$ 个矩形所覆盖的面积是多少？

注意：被重复覆盖的区域的面积只算一次。

## 样例 #1

### 输入

```
2
0 5 4 1
2 4 6 2
```

### 输出

```
20```

# 题解

## 作者：Ofnoname (赞：59)

扫描线板子题，可以去搜博客看一下。这里搬运一下以前口胡的。

首先将`y`坐标离散化，但是要保留原坐标。

我们用一根竖直的线从左向右依次扫描，每当与矩形的竖直边重合时就累加一次面积，相当于把并集图形分割为一个一个小的矩形。
![](https://s2.ax1x.com/2019/10/26/KBlI4P.png)

具体来说，建立数组$d[i]$保存这个y坐标被覆盖了多少次，并把矩形的竖边按$(x,y1,y2,d)$表示，d表示这是矩形的左边界(1)还是右边界(-1)，比如图中第一条边就是$(2,3,7,1)$，并按x排序依次考虑。

对所有竖线先按`x`排序，有些写法里对竖线排序时如果`x`相等会按`c`排序，但是容易发现这是毫无影响的。

对于每条边，我们把$[y1,y2)$的值都加上d，表示这条左数边把y轴这些地方又覆盖了一次，或者右数边表示该矩形对y轴影响已经结束。

（为什么是左闭右开：我们把点转化为线段来求覆盖次数，点的数量是比线段的数量多1个的，比如第一条线段里$[3,7]$是有5个点的，但是放在d数组里只有4个值需要修改。）

接着统计答案，下一个矩形的宽就是相邻两根竖边的x坐标差，而长度就是d数组里至少被覆盖一次的坐标数。

（图中：$2*4+2*6+1*8+2*7+1*7+1*4+3*4+0*0\ =\ 60$）

d数组涉及了区间修改和区间查询，可以使用线段树来维护。

由于只需要查询$(1,N)$里的覆盖次数，我们的懒标记可以不用下推。更新时，如果一个节点有懒标记（表示自己被完全覆盖的次数），那么他的贡献就是区间总长度（因为被覆盖），否则递归计算左右儿子并相加。

```cpp
#include <bits/stdc++.h>
#define MAX (2000 + 7)
using namespace std;

struct Node { int x, y0, y1, c; } a[MAX];
int cmp(Node a, Node b) { return a.x < b.x; }

unordered_map <int, int> H;

int N, M, qy[MAX];
long long ans;

struct Segtree
{
	#define i0 (i << 1)
	#define i1 (i << 1 | 1)
	int L[MAX << 2], R[MAX << 2], v[MAX << 2], len[MAX << 2];
	void init(int i, int l, int r)
	{
		L[i] = l, R[i] = r, v[i] = len[i] = 0;
		if (l != r) {
			int mid = l + r >> 1;
			init(i0, l, mid), init(i1, mid+1, r);
		}
	}
	void add(int i, int l, int r, int c)
	{
		if (r < L[i] || R[i] < l) return;
		if (l <= L[i] && R[i] <= r)
			v[i] += c;
		else add(i0, l, r, c), add(i1, l, r, c);
		if (v[i]) len[i] = qy[R[i]+1] - qy[L[i]];//完全覆盖时的长度应该是离散化前的y坐标（实际长度）。
		else len[i] = len[i0] + len[i1];
	}
} Seg;

int main()
{
	scanf("%d", &N), H.clear();
	for (int i = 1, x0, y0, x1, y1; i <= N; i++)
	{
		scanf("%d%d%d%d", &x0, &y1, &x1, &y0);//注意是左上和右下
		a[i] = Node{x0, y0, y1, 1};
		a[i+N] = Node{x1, y0, y1, -1};
		qy[++M] = y0, qy[++M] = y1;
	}
	sort(qy+1, qy + M+1), M = unique(qy+1, qy + M+1) - qy - 1;
	for (int i = 1; i <= M; i++)
		H[qy[i]] = i;//离散化
	
	Seg.init(1, 1, (N <<= 1));
	sort(a + 1, a + N + 1, cmp);
	for (int i = 1; i <= N; i++)
	{
		Seg.add(1, H[a[i].y0], H[a[i].y1] - 1, a[i].c);
		ans += (long long)Seg.len[1] * (a[i+1].x - a[i].x);
	} printf("%lld\n", ans);
}
```

另外，本题`N`规模为1000，最多2000个不同的坐标，线段树开8000是足够的，但是上面的代码如果开了`O2`就会`WA`。必须要开更大的空间才能过，如果有知道原因的dalao欢迎来踩。

---

## 作者：山蛙or山兔 (赞：46)

思路就不多说了，就是将整个图用竖线切开，然后进行扫描。

重点在于，如何用较为清晰的代码将此题写出来。

思路是这样的：

1、将所有竖线从小到大排序；

2、遍历竖线，将两条竖线都穿过的长方形加入数组；

3、将数组内的长方形按照顶边由大到小排列；

4、维护当前最低的顶边h和最低的底边d，在每次维护的时候更新答案。

代码如下：

```cpp
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#define maxn 1010
using namespace std;

long long n,x[maxn],y[maxn],x2[maxn],y2[maxn],side[2*maxn];
int arr[maxn];
long long ans;

bool cmp(int a,int b)
{
	return y[a]>y[b];
}

int main()
{
	cin >> n;
	for (int i=0;i<n;i++) 
	{
		cin >> x[i] >> y[i] >> x2[i] >> y2[i];
		side[2*i]=x[i];
		side[2*i+1]=x2[i];
	}
	sort(side,side+2*n);
	ans=0;
	for (int i=1;i<2*n;i++)
	{
		if (side[i-1]==side[i]) continue;
		int m=0;
		for (int j=0;j<n;j++)
		{
			if (x[j]<=side[i-1] && side[i]<=x2[j]) arr[m++]=j;
		}
		sort(arr,arr+m,cmp);
		long long h=y[arr[0]],d=y2[arr[0]],w=side[i]-side[i-1];
		for (int j=1;j<m;j++)
		{
			int temp=arr[j];
			if (y[temp]>d)
			{
				ans+=(h-y[temp])*w;
				h=y[temp];
			}
			else
			{
				ans+=(h-d)*w;
				h=y[temp];
			}
			if (y2[temp]<d) d=y2[temp];
		}
		ans+=(h-d)*w;
	}
	cout << ans << endl;
}
```


---

## 作者：Shik__Utau (赞：36)

此题大佬都用离散化+线段树，那么某蒟蒻就只能讲讲矩形切割的做法了。

那么，先来介绍一下矩形切割

矩形切割是计算平面矩形的一种有效方法。同时许多统计类的问题通过数学建模后也能使用
矩形切割的思想来解决。

它的基本思想是，用当前矩形去切割之前所有加入至矩形集合 _S_ 中的矩形，将它们分成更多的小矩形，并再加入集合 _S_ 中，并删除原来在集合 _S_ 中的矩形，最后加入当前矩形。

我们先建立矩形的结构体：
```cpp
struct node{ll x1,y1,x2,y2;}a[maxn];
```
然后，我们写出添加操作Add：
```cpp
void Add(ll x1,ll y1,ll x2,ll y2)
{a[++tot]=(node){x1,y1,x2,y2};}
```
那么问题是，如何切割呢？

假设目前插入的矩形为（x3,y3,x4,y4），则我们现在要用他来切割集合内的矩形(x1,y1,x2,y2)。

我们先在x轴方向上进行线段切割

k1=max(x1,x3)  
k2=min(x2,x4)

则k1,k2即为两个矩形x轴上的交点。

倘若x1<k1，说明产生了新矩形(x1,y1,k1,y2)

倘若x2>k2，说明产生了新矩形(k2,y1,x2,y2)

然后我们再在y轴上切割，过程类似。请各位画图理解（qwq）

切割代码如下：
```cpp
void Cut(int p,ll x1,ll y1,ll x2,ll y2,int cmd){
	ll k1,k2;
	if(!cmd){//x轴切割
		k1=max(x1,a[p].x1);
		k2=min(x2,a[p].x2);
		if(a[p].x1<k1)Add(a[p].x1,a[p].y1,k1,a[p].y2);
		if(k2<a[p].x2)Add(k2,a[p].y1,a[p].x2,a[p].y2);
		Cut(p,k1,y1,k2,y2,1);
	}
	else{//y轴切割
		k1=max(y1,a[p].y1);
		k2=min(y2,a[p].y2);
		if(a[p].y1<k1)Add(x1,a[p].y1,x2,k1);
		if(k2<a[p].y2)Add(x1,k2,x2,a[p].y2);
	}
}
```
这样，集合当中便只会保存每个区域一次，相当于处理完后，集合内所有矩形的面积和即为所有原矩形的面积并。

这就是矩形切割的思想。

对于此题，要注意的是为数据给出的是左上角至右下角，需要稍微调整一下。那么给出Code：
```cpp
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
const int maxn=1005;
struct node{ll x1,y1,x2,y2;}a[maxn];
int n,tot=0;
void Add(ll x1,ll y1,ll x2,ll y2){a[++tot]=(node){x1,y1,x2,y2};}
void Cut(int p,ll x1,ll y1,ll x2,ll y2,int cmd){
	ll k1,k2;
	if(!cmd){
		k1=max(x1,a[p].x1);
		k2=min(x2,a[p].x2);
		if(a[p].x1<k1)Add(a[p].x1,a[p].y1,k1,a[p].y2);
		if(k2<a[p].x2)Add(k2,a[p].y1,a[p].x2,a[p].y2);
		Cut(p,k1,y1,k2,y2,1);
	}
	else{
		k1=min(y1,a[p].y1);
		k2=max(y2,a[p].y2);
		if(a[p].y1>k1)Add(x1,a[p].y1,x2,k1);
		if(k2>a[p].y2)Add(x1,k2,x2,a[p].y2);
	}
}
int main(){
	scanf("%d",&n);
	ll x1,y1,x2,y2;
	scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
	Add(x1,y1,x2,y2);//先加入一个矩形
	for(int i=2;i<=n;i++){
		scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
		for(int j=1;j<=tot;j++){
			if(a[j].x1>=x2||a[j].x2<=x1||a[j].y1<=y2||a[j].y2>=y1)continue;//判断是否相交
			Cut(j,x1,y1,x2,y2,0);//若相交，则用当前矩形去切割
			a[j]=a[tot];//删除原矩形，用最后一个矩形来覆盖它
			tot--;j--;
		}
		Add(x1,y1,x2,y2);//加入新矩形
	}
	ll ans=0;
	for(int i=1;i<=tot;i++)ans+=(a[i].x2-a[i].x1)*(a[i].y1-a[i].y2);//计算面积并
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：pocafup (赞：24)

什么,扫描线需要线段树?

那我第一个不干啊(~~其实是不会写~~)

这里介绍一种裸的扫描线:

我们根据x排序,对于相等的 $x$ ,将 $y$ 进入和退出分类讨论,然后全部放进set里面.每次 $x$ 不相等的时候,答案就是 **(现在y覆盖的乘以(现在的x-以前的x))**

具体的判断方法:

1.y的判断:

将每个长方形的上方点记做出口,下方点记做入口.用一个set记录在某区间内所有的 $y$ 值.每次从下往上扫,如果某个y是入口就将 $sz$ +1,否则就将 $sz$ -1.如果 $sz$==0 的时候就将你整个区间的值加到re里面

![](https://cdn.luogu.com.cn/upload/image_hosting/njydtqar.png)
如图,每次x变的时候只需要保存中间y的值,然后用移动的x乘y就好了

**注:我保存y进入和退出状态的原因就是为了记录中间是否有空位.可以发现,如果中间有空位,那么证明所有进入的点已经退出了,所以那一段不需要加上去(不懂可以画一下图)**

```cpp
long long query_up(){
  long long re = 0,prev = -1,sz = 0;
  for (multiset<pair<long long,bool> >::iterator i=se.begin();i!=se.end();++i){
    pair<long long,bool> now = *i;
    if (sz==0) {prev = now.f;sz++;}
    else if (now.s) sz++;
    else sz--;
    if (sz==0) re+=(now.f-prev);//如果现在所以的y都已经出去了,那么答案就是最后一个y的出口-第一个y的入口
  }
  return re;
}
```

想到了这点以后这题的难点基本上就解决了.

因为有负数,我将每个数都加上了1e8,这样就可以完全不管负数了

**不开long long见祖宗**

完整代码:

```cpp
#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>
#include <utility>
using namespace std;
const long long MAXN = 1e5+5;
#define pp pair<long long,long long>
#define f first
#define s second
long long n,ans = 0;
multiset<pair<long long,bool> > se;
struct Edge{
  long long x,y; bool in,in2;
}edge[MAXN*4];
Edge add_edge(long long a, long long b, bool bo,bool bo2){
  Edge tmp;
  tmp.x = a;
  tmp.y = b;
  tmp.in = bo;
  tmp.in2 = bo2;
  return tmp;
}
bool sorted(Edge a, Edge b){
  return a.x<b.x;
}
long long query_up(){
  long long re = 0,prev = -1,sz = 0;
  for (multiset<pair<long long,bool> >::iterator i=se.begin();i!=se.end();++i){
    pair<long long,bool> now = *i;
    if (sz==0) {prev = now.f;sz++;}
    else if (now.s) sz++;
    else sz--;
    if (sz==0) re+=(now.f-prev);
  }
  return re;
}
int main(){
  cin >> n;
  for (long long i=0;i<n;i++){
    long long a,b,c,d; cin >> a >>b >> c >> d;
    a+=1e8;b+=1e8;c+=1e8;d+=1e8;
    edge[4*i] = add_edge(a,b,1,0);
    edge[4*i+1] = add_edge(a,d,1,1);
    edge[4*i+2] = add_edge(c,b,0,0);
    edge[4*i+3] = add_edge(c,d,0,1);
    //两种状态,第一种表示x变不变,第二种表示y变不变
  }
  sort(edge,edge+4*n,sorted);
  long long prev = 0;
  for (long long i=0;i<4*n;i++){
    if (edge[i].x!=prev){//如果x变了
      if (se.size()) ans += (edge[i].x-prev)*query_up();
      prev = edge[i].x;
    }
    if (edge[i].in==1) se.insert(make_pair(edge[i].y,edge[i].in2));//如果这点是进入的点,就将y加入set
    else se.erase(se.find(make_pair(edge[i].y,edge[i].in2)));
//否则将y扔出set
  }
  cout << ans;
}

```

留一组测试数据造福后人
```cpp
3
3 7 7 3
1 5 5 1
2 2 7 -2

```
答案45

---

## 作者：上进的z君 (赞：15)

楼下都已经给出很详细的关于[B]离散化[/B]的做法了，那我在这里就介绍另一种思路。

那就是直接进行[B]矩形切割[/B]。直接将不规则的图形切割成一个个小的矩形计算面积。


[MOVE]下面看[COLOR]代码+注释[/COLOR][/MOVE]


[code]



    
    
    
    
    
    

    
    
    
    
```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
using namespace std;
const int maxn=19;
int x1[maxn],x2[maxn],y1[maxn],y2[maxn],n,ans=0;
void Work(int left,int right,int high,int low,int t){
    if(left>right||high<low)return;//将不符合要求的矩形过滤掉
    while(t>0&&(left>=x2[t]||right<=x1[t]||high<=y2[t]||low>=y1[t]))//如果当前矩形与之前的矩形无冲突就不管了
    t--;
    if(!t){
        ans+=(right-left)*(high-low);//没有冲突就累加进答案
        return;
    }
    //下面就是切割了，变量名已经很明显了，就不再重复地解释了
    if(left<x1[t]){
        Work(left,x1[t],high,low,t-1);
        left=x1[t];
    }
    if(right>x2[t]){
        Work(x2[t],right,high,low,t-1);
        right=x2[t];
    }
    if(high>y1[t]){
        Work(left,right,high,y1[t],t-1);
        high=y1[t];
    }
    if(low<y2[t]){
        Work(left,right,y2[t],low,t-1);
        low=y2[t];
    }
    return;
}
int main()
{
    //freopen("c.in","r",stdin);
    //freopen("c.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    scanf("%d%d%d%d",&x1[i],&y1[i],&x2[i],&y2[i]);
    for(int i=1;i<=n;i++)
    Work(x1[i],x2[i],y1[i],y2[i],i-1);
    printf("%d\n",ans);
    return 0;
}
[/code]
```

---

## 作者：mywwzh (赞：13)

要统计覆盖，而且不计重复，可以自然地想到差分后求前缀和的做法，并且此题数据范围较大，还需离散化。

我们定义结构体 `Node` 来存储每个矩形的左上角和右下角，$f_{i,j}$ 表示横坐标 $i$ 和纵坐标 $j$ 处有多少个矩形覆盖。

对于每次覆盖，我们只需对 $f$ 数组进行差分，最后前缀和还原出每个位置的实际覆盖次数。最后我们只需遍历每一个 $f_{i,j}$，如果其覆盖次数不为 $0$，就计算该位置所对应的面积并加到最终答案中即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()
#define debug(a) cout << a << "\n";
#define pb push_back
#define mp make_pair
#define mem(a, b) memset(a, b, sizeof(a))
#define endl "\n"
typedef long long ll;
typedef unsigned long long ull;
constexpr int MOD = 1e9 + 7;
constexpr int MAXN = 1e3 + 10;

struct Node
{
    int X1, Y1, X2, Y2; // X1, Y1 是左上角，X2, Y2 是右下角
};

Node a[4 * MAXN];
int b[4 * MAXN], c[4 * MAXN], f[4 * MAXN][4 * MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, top = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].X1 >> a[i].Y1 >> a[i].X2 >> a[i].Y2;
        // 将点扔进 b 数组，方便离散化
        b[++top] = a[i].X1;
        b[++top] = a[i].Y1;
        b[++top] = a[i].X2;
        b[++top] = a[i].Y2; 
    }
    sort(b + 1, b + top + 1);
    b[0] = INT_MIN;
    auto end = unique(b + 1, b + top + 1);
    int new_top = distance(b, end) - 1;
    for (int i = 1; i <= n; i++)
    {
		// 二分法离散化
        a[i].X1 = lower_bound(b + 1, end, a[i].X1) - b;
        a[i].Y1 = lower_bound(b + 1, end, a[i].Y1) - b;
        a[i].X2 = lower_bound(b + 1, end, a[i].X2) - b;
        a[i].Y2 = lower_bound(b + 1, end, a[i].Y2) - b; 
    }
    for (int i = 1; i <= new_top; i++)
    {
        c[i] = b[i];
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = a[i].X1; j < a[i].X2; j++)
        {
            // 差分
            f[j][a[i].Y1]++; 
            f[j][a[i].Y2]--;
        }
    }
    for (int i = 1; i < new_top; i++)
    {
        for (int j = 1; j < new_top; j++)
        {
            f[i][j] += f[i][j - 1];
        }
    }
    ll ans = 0;
    for (int i = 1; i < new_top; i++)
    {
        for (int j = 1; j < new_top; j++)
        {
            if (f[i][j] != 0)
            {
                ans += (ll)(c[i + 1] - c[i]) * (c[j + 1] - c[j]); // 如果被覆盖过，计算面积
            }
        }
    }
    cout << ans;
    return 0;
}

```

---

## 作者：wanglichao1121 (赞：10)

介绍一个好写一点的算法：

看起来是二维，实际上可以把它转化成一维。

读入时把数据中横轴的最大值和最小值记录下来。（记得把横纵都-1，因为它是以点为单位的）

用i从最小值扫描到最大值，

然后找一遍n，找到经由i这条横轴的所有矩阵，存起来。

接下来，线段覆盖（不会的先去把“火烧赤壁”过了）。

这里顺便也讲了吧：

1.把所有重叠的压成同一个（这就是离散化）

2.全加

所有值加起来，输出——OVER


---

## 作者：zhengrunzhe (赞：10)

离散化

就是个二维的P1496火烧赤壁

具体不详细解释见P1496

把纵坐标的最大值到最小值+1(因为面积是按边长不是按点)都做一遍火烧赤壁

然后把每一行的答案累计起来

对于存每一行的线段

我选择set，写个运算符重载就可以自动排序了

用二维数组也可以，不过就是需要都手动排序一遍

```cpp
#include<set>
#include<cstdio>
#include<algorithm>
#define reg register
using namespace std;
const int INF=2147483647;
inline void read(reg int &in)
{
    reg int out=0,fh=1;
    reg char ch=getchar();
    if (ch=='-')fh=-1;
    while (ch<48||ch>57)ch=getchar();
    while (ch>47&&ch<58)
        out=out*10+ch-48,ch=getchar();
    in=out*fh;
}
struct line
{
    int l,r;
    bool operator<(const line &ll)const
    {
        if (l!=ll.l)return l<ll.l;  //先按左端点从小到大 
        return r<ll.r; //左端点相同就按右端点 
    }
};
set<line>s[20001];  //s[i]表示纵坐标为i的行上有的线段 
int ans,n,maxy=-INF,miny=INF;
int main()
{
    read(n);
    while (n--)
    {
        reg int x1,y1,x2,y2;
        read(x1);read(y1);read(x2);read(y2);
        y1+=10000;y2+=10000;  //把纵坐标+10^4不然数组会炸 
        miny=min(y2,miny);maxy=max(y1,maxy); //求最小最大的纵坐标 
        for (reg int i=y1;i>y2;i--) //将y1到y2+1每一行都添加一段x1x2的线段 
            s[i].insert((line){x1,x2});
    }
    for (reg int i=maxy;i>miny;i--)  //可参考P1496火烧赤壁的做法，不详细解释 
    {
        if (s[i].empty())continue; //没加这句话80分 
        reg int end=(*s[i].begin()).r,
                start=(*s[i].begin()).l,sum=0;
        for (set<line>::iterator j=s[i].begin();j!=s[i].end();j++)
        {
            if (j==s[i].begin())continue;
            if (end<=(*j).r&&end>=(*j).l)
                end=max((*j).r,end);
            else
                if ((*j).l>end)
                    sum+=end-start,
                    start=(*j).l,end=(*j).r;
        }
        ans+=sum+end-start;   //累积答案
    }
    printf("%d",ans);
}
```

---

## 作者：mulberror (赞：8)

# 题目链接
[【洛谷传送门】](https://www.luogu.org/problemnew/show/P1884)

# 题解
矩阵面积的并模板。（请求洛谷加为模板题）
很明显是要离散化的。
> 我们将矩阵与$x$轴平行的两个线段取出来。并且将这两个端点的$x1$和$x2$进行离散化。  
> 因为每一次我们都会对当前的这一层的某一段线段进行操作，那么就用权值线段树维护是否存在。

这个只是矩阵面积的并。
还有加强版：[【HDU 1542】](https://vjudge.net/problem/HDU-1542)
还有矩阵面积的交。

# 代码
```cpp
#include <bits/stdc++.h>
#define gc getchar
#define lc (nod << 1)
#define rc (nod << 1 | 1)
using namespace std;
typedef long long ll;
const int N = 2003;
template <typename T> void read(T &x) {
	x = 0; T fl = 1; char c = 0;
	for (; c < '0' || c > '9'; c = gc()) 
		if (c == '-') fl = -1;
	for (; c >= '0' && c <= '9'; c = gc()) 
		x = (x << 1) + (x << 3) + (c ^ 48);
	x *= fl;
}
struct E{ int l, r, h, d; } ed[N * 2];
bool cmp_sl(E x, E y) { return x.h < y.h; }
ll ans = 0ll; 
int n, dcnt;
int disc[N];
struct seg { ll s, tag; } tr[N << 2];
void pushup(int nod, int l, int r) {
	if (tr[nod].tag) tr[nod].s = disc[r + 1] - disc[l];
	else if (l == r) tr[nod].s = 0;
	else tr[nod].s = tr[lc].s + tr[rc].s; 
}
void upd(int nod, int l, int r, int ql, int qr, int val) {
	if (ql <= l && r <= qr) {
		tr[nod].tag += val;
		pushup(nod, l, r); 
		return; 
	}
	int mid = (l + r) >> 1;
	if (ql <= mid) upd(lc, l, mid, ql, qr, val);
	if (qr > mid) upd(rc, mid + 1, r, ql, qr, val); 
	pushup(nod, l, r); 
}
int main() {
	read(n);  
	for (int i = 1, x1, y1, x2, y2; i <= n; i ++) {
		read(x1); read(y1); read(x2); read(y2); 
		disc[++ dcnt] = x1; ed[dcnt] = (E){x1, x2, y1, 1}; 
		disc[++ dcnt] = x2; ed[dcnt] = (E){x1, x2, y2, -1};
	}
	sort(disc + 1, disc + 1 + dcnt); 
	sort(ed + 1, ed + 1 + dcnt, cmp_sl);
	int m = unique(disc + 1, disc + 1 + dcnt) - disc - 1;
	for (int i = 1; i < dcnt; i ++) {
		int l = lower_bound(disc + 1, disc + 1 + m, ed[i].l) - disc;
		int r = lower_bound(disc + 1, disc + 1 + m, ed[i].r) - disc;
		if (l < r) upd(1, 1, m, l, r - 1, ed[i].d); 
		ans += tr[1].s * (ed[i + 1].h - ed[i].h); 
	}
	cout << ans << endl; 
	return 0; 
}
```

---

## 作者：顾z (赞：3)


# [顾](https://www.luogu.org/blog/RPdreamer/#)[z](https://www.cnblogs.com/-guz/)

~~你没有发现两个字里的blog都不一样嘛~~ qwq

难得遇到一个裸的扫描线的题,竟然没切掉 emmm.

看到$x,y$的坐标范围,离散化就好了！

没有一遍切,竟然是没开$long \ \ long$!!!

太难受了,关于这个的话就不多BB,网上讲解很多.

大家可以去搜一下。(貌似NOIP不会考,暂且学了)

将来有时间写讲解好了 qwq.

``代码``

```c++
#include<cstdio>
#include<algorithm>
#include<iostream>
#define int long long 
#define R register

using namespace std;

const int gz=10086;

inline void in(int &x)
{
	int f=1;x=0;char s=getchar();
	while(!isdigit(s)){if(s=='-')f=-1;s=getchar();}
	while(isdigit(s)){x=x*10+s-'0';s=getchar();}
	x*=f;
}

struct cod
{
	int l,r,h;
	int f;
	bool operator <(const cod&a)const
	{
		return h<a.h;
	}
}edge[gz];

struct tre
{
	int l,r,s;
	int len;
}tr[gz];

#define ls o<<1
#define rs o<<1|1

int x[gz],n,tot;

void build(R int o,R int l,R int r)
{
	tr[o].l=l;tr[o].r=r;
	if(l==r)return;
	R int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
}

inline void up(R int o)
{
	if(tr[o].s)
		tr[o].len=x[tr[o].r+1]-x[tr[o].l];
	else if(tr[o].l==tr[o].r)
		tr[o].len=0;
	else tr[o].len=tr[ls].len+tr[rs].len;
}

void change(R int o,R int l,R int r,R int del)
{
	if(tr[o].l==l and tr[o].r==r)
	{
		tr[o].s+=del;
		up(o);
		return;
	}
	R int mid=(tr[o].l+tr[o].r)>>1;
	if(r<=mid) change(ls,l,r,del);
	else if(l>mid) change(rs,l,r,del);
	else change(ls,l,mid,del),change(rs,mid+1,r,del);
	up(o);
}

signed main()
{
	in(n);
	for(R int i=1;i<=n;i++)
	{
		R int x1,x2,y1,y2;
		in(x1),in(y1),in(x2),in(y2);
		edge[++tot].l=x1;edge[tot].r=x2;edge[tot].f=-1;
		edge[tot].h=y1;x[tot]=x1;
		edge[++tot].l=x1;edge[tot].r=x2;edge[tot].f=1;
		edge[tot].h=y2;x[tot]=x2;
	}
	sort(edge+1,edge+tot+1);
	sort(x+1,x+tot+1);
	int new_n=1;
	for(R int i=2;i<=tot;i++)
		if(x[new_n]!=x[i])x[++new_n]=x[i];
	build(1,1,new_n);
	int ans=0;
	for(R int i=1;i<=tot;i++)
	{
		R int l=lower_bound(x+1,x+new_n+1,edge[i].l)-x;
		R int r=lower_bound(x+1,x+new_n+1,edge[i].r)-x-1;
		change(1,l,r,edge[i].f);
		ans+=(edge[i+1].h-edge[i].h)*tr[1].len;
	}
	printf("%lld",ans);
}
```





---

## 作者：lych (赞：1)

本题可以用离散化优化到O(N^3)，也可以用wanglichao1121的方法优化到O(N(Y[I]-X[I])，但是，如果把两者结合在一起，可以写出O(N^2)的程序，虽然对于本题的数据，简直就是杀鸡用牛刀，但是普及一下还是很不错的。


首先给出O(N(Y[I]-X[I])的程序，思路详见wanglichao1121的题解（虽然说思路是我想出来的）：

```delphi
var
  x1,x2,x,y1,y2,y:array[0..100] of longint;
  min,max,n,i,j,k,tail,ans:longint;
procedure swap(var a,b:longint);
var t:longint;
begin
  t:=a; a:=b; b:=t;
end;
procedure qsort(r,l:longint);
var
  i,j,mid:longint;
begin
  i:=r; j:=l;
  mid:=y1[(i+j) shr 1];
  repeat
    while y1[i]<mid do inc(i);
    while y1[j]>mid do dec(j);
    if i<=j then
      begin
        swap(x1[i],x1[j]);
        swap(x2[i],x2[j]);
        swap(y1[i],y1[j]);
        swap(y2[i],y2[j]);
        inc(i); dec(j);
      end;
  until i>j;
  if i<l then qsort(i,l);
  if r<j then qsort(r,j);
end;//根据y坐标从小到大排序，方便后面的O(N)求线段覆盖
begin
  readln(n);
  for i:=1 to n do
    begin
      readln(y1[i],x1[i],y2[i],x2[i]);
      x1[i]:=-x1[i];//因为是数字越大，就越上面，所以横坐标需要取反，适合人的思路
      x2[i]:=-x2[i]-1;//注意是点边，所以要减去1
      //y2[i]:=y2[i];
    end;//读入
  qsort(1,n);//排序
  min:=maxlongint; max:=-min;
  //min:=x1[1]; max:=x2[n];
  for i:=1 to n do
    begin
      if x1[i]<min then min:=x1[i];
      if x2[i]>max then max:=x2[i];
    end;//寻找最上面的边和最下面的边
  //writeln(min); writeln(max);
  for i:=min to max do//从上到下枚举每条边
    begin
      k:=0;
      for j:=1 to n do
        if (x1[j]<=i) and (x2[j]>=i) then
          begin
            inc(k);
            x[k]:=y1[j];
            y[k]:=y2[j];
          end;//统计矩形内含有这条边的矩形
      if k=0 then continue;
      //head:=x[1];
      tail:=y[1];
      ans:=ans+tail-x[1];
      for j:=2 to k do
        if y[j]>tail then
          if x[j]<tail then
            begin ans:=ans+y[j]-tail; tail:=y[j]; end else
            begin ans:=ans+y[j]-x[j]; tail:=y[j]; end;//O(N)线段覆盖，详见洛谷online judge的火烧赤壁题解
    end;
  writeln(ans);
end.
```

我们画出图形之后，可以发现有许多线段是属于同一组矩形的，这就给了我们优化的思路。因为上述算法枚举线段明显存在可以合并的地方。因此我们先把所有的横坐标记录下来，用一维普通离散化的思路将横坐标排序，然后判断任意两个坐标之间的矩形，用O(N)扫描完成统计，最后×坐标差并累加，就可以完成了。

```delphi
var
  a,x1,x2,x,y1,y2,y:array[0..100] of longint;
  min,max,n,i,j,k,tail,ans,sum,m:longint;
procedure swap(var a,b:longint);
var t:longint;
begin
  t:=a; a:=b; b:=t;
end;
procedure qsort(r,l:longint);
var
  i,j,mid:longint;
begin
  i:=r; j:=l;
  mid:=y1[(i+j) shr 1];
  repeat
    while y1[i]<mid do inc(i);
    while y1[j]>mid do dec(j);
    if i<=j then
      begin
        swap(x1[i],x1[j]);
        swap(x2[i],x2[j]);
        swap(y1[i],y1[j]);
        swap(y2[i],y2[j]);
        inc(i); dec(j);
      end;
  until i>j;
  if i<l then qsort(i,l);
  if r<j then qsort(r,j);
end;
procedure sort(r,l:longint);
var
  i,j,mid,t:longint;
begin
  i:=r; j:=l;
  mid:=a[(i+j) shr 1];
  repeat
    while a[i]<mid do inc(i);
    while a[j]>mid do dec(j);
    if i<=j then
      begin
        t:=a[i]; a[i]:=a[j]; a[j]:=t;
        inc(i); dec(j);
      end;
  until i>j;
  if i<l then sort(i,l);
  if r<j then sort(r,j);
end;
begin
  readln(n);
  for i:=1 to n do
    begin
      readln(y1[i],x1[i],y2[i],x2[i]);
      x1[i]:=-x1[i];
      x2[i]:=-x2[i];//不需要减一，切记切记！！！
      a[i shl 1-1]:=x1[i];
      a[i shl 1]:=x2[i];
    end;
  m:=n shl 1;
  qsort(1,n);  sort(1,m);
  for i:=1 to m-1 do//枚举每个横坐标之间的空间，M个横坐标，M-1个区间
    begin
      k:=0;
      for j:=1 to n do
        if (x1[j]<=a[i]) and (x2[j]>=a[i+1]) then
          begin
            inc(k);
            x[k]:=y1[j];
            y[k]:=y2[j];
          end;//包含此区间的矩形
      if k=0 then continue;
      tail:=y[1];
      sum:=tail-x[1];
      for j:=2 to k do
        if y[j]>tail then
          if x[j]<tail then
            begin sum:=sum+y[j]-tail; tail:=y[j]; end else
            begin sum:=sum+y[j]-x[j]; tail:=y[j]; end;//O(N)扫描
      sum:=sum*(a[i+1]-a[i]);//乘以区间的宽
      ans:=ans+sum;//累加
    end;
  writeln(ans);
end.
```

---

