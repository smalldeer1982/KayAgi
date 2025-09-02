# [USACO06JAN] Corral the Cows G

## 题目描述

Farmer John wishes to build a corral for his cows. Being finicky beasts, they demand that the corral be square and that the corral contain at least C (1 <= C <= 500) clover fields for afternoon treats. The corral's edges must be parallel to the X,Y axes.


FJ's land contains a total of N (C <= N <= 500) clover fields, each a block of size 1 x 1 and located at with its lower left corner at integer X and Y coordinates each in the range 1..10,000. Sometimes more than one clover field grows at the same location; such a field would have its location appear twice (or more) in the input. A corral surrounds a clover field if the field is entirely located inside the corral's borders.


Help FJ by telling him the side length of the smallest square containing C clover fields.

Farmer John 希望为他的奶牛们建立一个畜栏。

这些挑剔的奶牛要求畜栏必须是正方形的，而且至少要包含 $C$ 片三叶草，来当做它们的下午茶。

约翰的土地里一共包含 $N$ 片三叶草，每单位三叶草位于一个 $1\times 1$ 的土地区域内。坐标都为整数，范围在 $1$ 到 $10000$ 以内。

**多片的三叶草可能会位于同一个 $1\times 1$ 的区域内，所以在输入内，同一个区域坐标可能出现多次。**

请你帮 Farmer John 计算一下，在能包含至少 $C$ 片三叶草的情况下，畜栏的最小边长是多少。

$1\le C\le N\le 500$。

## 说明/提示

Explanation of the sample:



```php
|*   *
| * *
+------
```

Below is one 4x4 solution (C's show most of the corral's area); many others exist.

```php
|CCCC
|CCCC
|*CCC*
|C*C*
+------
```

## 样例 #1

### 输入

```
3 4
1 2
2 1
4 1
5 2```

### 输出

```
4```

# 题解

## 作者：RyexAwl (赞：20)

菜鸡第一次写题解，有什么不足欢迎提出-w-。


------------

## 思路
由题面可知我们要求的问题是平面上有n个点（但是是在格子内w），在这个平面上圈出边长为len的正方形使得正方形内包含c个点。怎样圈才能使得len最小。

这道题直接做很显然是很难做的。

那么根据题意我们很容易把这个问题转化为一个判定问题：我们可以枚举边长len的正方形，判断一下边长为len的正方形内包不包含c个点。而直接枚举len的话，必然会T掉。而这个问题很明显具有单调性：即大于某个值的len都可以满足，而小于这个值的都不满足。那么我们就可以二分解决。如果记点的坐标为$(x,y)$的话，那么二分的复杂度为$O(log\ max(x,y))$。

那么我们应该如何判定呢？

1.二维前缀和:

我们可以通过$O(max(x,y)^2)$的时间预处理出二维前缀和，并可以在$O(1)$的时间内进行单点查询。如果我们枚举所有边长为len的正方形的话，判定的复杂度就近似为$O(max(x,y)^2)$

那么总复杂度为$O(max(x,y)^2\ log\ max(x,y))$ 代入最大规模可以算出最坏情况下的运算次数为$10^8*10 \ =\ 10^9$过于极限，容易被卡，因此我们在一个长度为10000的二维前缀和数组里做二分是不现实的。

那么我们需要如何处理？

2.离散化

因为$c<=n<=500$，所以至多存在1000个数，那么我们就可以通过$O(c+n)$的时间进行离散化，将数x和y的据规模虽小到$(1-1000)$并可以在$O(log\ (c+n))$的时间内查询离散化结果。

那么如果将离散化的数据规模代入一下，最坏情况下运算次数为$10^6*10=10^7$。

~~虽说还是很高而且略去了离散化的复杂度~~，这个复杂度我们还是能接受的。


那么我们就可以通过$O((c+n)\log\ (c+n))$的离散化之后通过$O(log\ (c+n))$的查询处理二维前缀和$sum$，并用长度最多为1000的二维前缀和数组$sum$进行二分，设离散化后的最大数据规模为m复杂度为$O(m^2log\ max(x,y))$。
## 代码
对于离散化，我们可以初始化一个动态数组numbers，直接在读入的时候向里面push_back(x)与push_back(y)，因为我们的目的只是缩小规模，因此我们只需要开一维，把x和y存在同一个vector内进行查找。
```cpp
for (int i = 0; i < n; i++){
        int x,y;
        cin >> x >> y;
        numbers.push_back(x);
        numbers.push_back(y);
}
```

而因为我们要进行二分查找，所以我们必须对其进行排序并去重。

```cpp
sort(numbers.begin(),numbers.end());
numbers.erase(unique(numbers.begin(),numbers.end()),numbers.end());
```
那么我们接下来就可以二分查找原坐标离散化后的位置用其初始化二维前缀和数组。

```cpp
for (int i = 0; i < n; i++){
    int x = get(points[i].first),y = get(points[i].second);
    sum[x][y]++;
}
for (int i = 1; i < numbers.size(); i++){
        for (int j = 1; j < numbers.size(); j++){
            sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
     }
}
```
对于二分答案

如果mid合法那么最优解必然是在mid的左边，而不合法最优解则在mid的右边。
```cpp
int l = 1,r = 10000;
while (l < r){
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
}
```


而对于check，我们可以枚举所有边长为mid的矩形，通过二维前缀和判断是否存在c个目标。

而我们在枚举边长为mid的矩形时，所算的边长必须为离散化之前的边长，而离散化之前的边长就存在numbers数组内。

而以点$(i,j)$为右下角的边长为len的正方形的和$S$为

$S[i][j]-S[i - len][j] - S[i][j -len]+S[i-len][j-len]$

那么我们就可以枚举$x_1$,$x_2$与$y_1$,$y_2$。

其中$x_1$相当于$i-len$,$x_2$相当于$i$,$y_1$相当于$j-len$,$y_2$相当于$j$。

而因为目标是在格子里，所以有：

```cpp
while(numbers[x2] - numbers[x1 + 1] + 1 > len) x1++;
```

```cpp
while(numbers[y2] - numbers[y1 + 1] + 1 > len)y1++;
```


而如果$sum[x2][y2] - sum[x1][y2] - sum[x2][y1] + sum[x1][y1] >= c$
则$return\ true$否则$return\ false$

```cpp
bool check(int len){
    for (int x1 = 0,x2 = 1; x2 < numbers.size(); x2++){
        while(numbers[x2] - numbers[x1 + 1] + 1 > len)x1++;
        for (int y1 = 0, y2 = 1; y2 < numbers.size(); y2++){
            while(numbers[y2] - numbers[y1 + 1] + 1 > len)y1++;
            if (sum[x2][y2] - sum[x1][y2] - sum[x2][y1] + sum[x1][y1] >= c) return true;
        }
    }
    return false;
}
```
完整代码：
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int,int> PII;
int n,c;
PII points[1010];
vector<int> numbers;
int sum[1010][1010];
int get(int x){
    return lower_bound(numbers.begin(),numbers.end(),x) - numbers.begin();
}
bool check(int len){
    for (int x1 = 0,x2 = 1; x2 < numbers.size(); x2++){
        while(numbers[x2] - numbers[x1 + 1] + 1 > len)x1++;
        for (int y1 = 0, y2 = 1; y2 < numbers.size(); y2++){
            while(numbers[y2] - numbers[y1 + 1] + 1 > len)y1++;
            if (sum[x2][y2] - sum[x1][y2] - sum[x2][y1] + sum[x1][y1] >= c) return true;
        }
    }
    return false;
}
int main(){
    cin >> c >> n;
    numbers.push_back(0);
    for (int i = 0; i < n; i++){
        int x,y;
        cin >> x >> y;
        points[i] = {x,y};
        numbers.push_back(x);
        numbers.push_back(y);
    }
    sort(numbers.begin(),numbers.end());
    numbers.erase(unique(numbers.begin(),numbers.end()),numbers.end());
    for (int i = 0; i < n; i++){
       int x = get(points[i].first),y = get(points[i].second);
       sum[x][y]++;
    }
    for (int i = 1; i < numbers.size(); i++){
        for (int j = 1; j < numbers.size(); j++){
            sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }
    int l = 1,r = 10000;
    while (l < r){
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l;
    return 0;
}

```



---

## 作者：zhzh2001 (赞：20)

# 思路


一个正方形可以由左上角坐标和边长确定，只要枚举所有正方形就能找到答案。所以时间复杂度=枚举左上角坐标的时间\*枚举边长的时间\*统计正方形内的草场的时间。原题$N\le500$，实际上$O(N^3)$就能过了。我们可以做二维前缀和，并二分枚举边长，并用单调性在$O(N^2)$的时间内判断，总的复杂度是$O(N^2\log N)$的。但是我一开始两次二分，所以时间复杂度$O(N^2\log^2N)$，非常慢。


实际上，这个问题是可以做到更快的。二分仍然是必不可少的，而判定性问题可以转换成`USACO14MAR The Lazy Cow`(懒惰的牛)。可以发现，如果有至少一个方格被以草场为一角的正方形覆盖了达到$C$次就符合要求了。而这个问题可以用扫描线+线段树在$O(N\log N)$内解决，因此总时间复杂度$O(N\log^2N)$。官方题解中并没有给出这种方法，我是受到懒惰的牛(金组)的启发才想到的。


# 代码


```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 505;
struct clover
{
    int x, y;
} a[N];
struct event
{
    int x, yl, yr, val;
    bool operator<(const event &rhs) const
    {
        return x < rhs.x;
    }
} e[N * 2];
int y[N * 2];
struct node
{
    int max, lazy;
} tree[1 << 11];
//注意离散化后有2N
void build(int id, int l, int r)
{
    tree[id].max = tree[id].lazy = 0;
    if (l < r)
    {
        int mid = (l + r) / 2;
        build(id * 2, l, mid);
        build(id * 2 + 1, mid + 1, r);
    }
}
inline void pushdown(int id, int l, int r)
{
    if (tree[id].lazy && l < r)
    {
        tree[id * 2].max += tree[id].lazy;
        tree[id * 2].lazy += tree[id].lazy;
        tree[id * 2 + 1].max += tree[id].lazy;
        tree[id * 2 + 1].lazy += tree[id].lazy;
        tree[id].lazy = 0;
    }
}
void update(int id, int l, int r, int L, int R, int val)
{
    if (L <= l && R >= r)
    {
        tree[id].lazy += val;
        tree[id].max += val;
    }
    else
    {
        pushdown(id, l, r);
        int mid = (l + r) / 2;
        if (L <= mid)
            update(id * 2, l, mid, L, R, val);
        if (R > mid)
            update(id * 2 + 1, mid + 1, r, L, R, val);
        tree[id].max = max(tree[id * 2].max, tree[id * 2 + 1].max);
    }
}
int main()
{
    ios::sync_with_stdio(false);
    int c, n;
    cin >> c >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i].x >> a[i].y;
    int l = 1, r = 1e4;
    while (l < r)
    {
        int mid = (l + r) / 2, en = 0, yn = 0;
        for (int i = 1; i <= n; i++)
        {
            e[++en].x = a[i].x - mid + 1;
            //以草场为右下角的正方形
            y[++yn] = e[en].yl = a[i].y - mid + 1;
            y[++yn] = e[en].yr = a[i].y;
            e[en].val = 1;
            e[++en].x = a[i].x + 1;
            e[en].yl = a[i].y - mid + 1;
            e[en].yr = a[i].y;
            e[en].val = -1;
        }
        sort(e + 1, e + en + 1);
        sort(y + 1, y + yn + 1);
        build(1, 1, yn);
        int now = 0;
        for (int i = 1; i <= en; i++)
        {
            if (e[i].x != e[i - 1].x)
                now = max(now, tree[1].max);
            //同一个x都更新再更新答案
            update(1, 1, yn, lower_bound(y + 1, y + yn + 1, e[i].yl) - y, lower_bound(y + 1, y + yn + 1, e[i].yr) - y, e[i].val);
        }
        if (now < c)
            l = mid + 1;
        else
            r = mid;
    }
    cout << r << endl;
    return 0;
}
```

### 题外话


这题虽然比较简单，但比较容易写错细节，很适合用于出题……我曾经T1出过$N\le3,000$，直接$O(N^2\log N)$会被卡常，需要用官方的神奇优化或用$O(N\log^2N)$的方法。当然，现在可以$N\le50,000$，作为T2？另外，实际上\*std::lower\_bound\*确实比较慢，要求高时还是自己实现比较好。


有兴趣可以看一下我的题目，T3也是原题：https://zhzh2001.github.io/test/day2/


---

## 作者：ysner (赞：15)

咦，我竟然是0ms跑过的最优解。。。那就发个题解总结一下。

二维双指针法的完美结合

双指针法就是令l=1，从1到n枚举右指针r，然后始终保证[l,r]的区间是满足题目要求的区间，不满足就使l++，并每次用[l,r]更新答案（感觉就是简化的单调队列）

如果坐标都是一维的，我们只用双指针法就能搞定，但是由于是二维的，所以我们要用两重双指针法（四指针法。。。）

先二分答案，分别用双指针法维护纵坐标和横坐标，具体还是看代码吧~

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int n,m,nx,ny;
struct field
{
    int x,y;
}p[510];
int rx[510],ry[510],s[510];
bool cmp1(field a,field b)
{
    return a.x<b.x;
}
bool cmp2(field a,field b)
{
    return a.y<b.y;
}
bool solve(int ml)
{
    int i,a,b,c,d,sc,sd;
    a=b=0;
    memset(s,0,sizeof(s));
    while(b<n&&rx[p[b+1].x]-rx[1]+1<=ml)  s[p[++b].y]++;
    for(;b<=n;s[p[++b].y]++)
    {
        while(rx[p[b].x]-rx[p[a+1].x]+1>ml)  s[p[++a].y]--;
        c=d=sc=sd=0;
        while(d<ny&&ry[d+1]-ry[1]+1<=ml)  sd+=s[++d];
        for(;d<=ny;sd+=s[++d])
        {
            while(ry[d]-ry[c+1]+1>ml)    sc+=s[++c];
            if(sd-sc>=m) return true;
        }
    }
    return false;
}
int main()
{
    scanf("%d%d",&m,&n);
    int i;
    rx[0]=ry[0]=-1;
    for(i=1;i<=n;i++)    scanf("%d%d",&p[i].x,&p[i].y);
    sort(p+1,p+n+1,cmp2);
    for(i=1;i<=n;i++)
    {
        if(p[i].y>ry[ny])    ry[++ny]=p[i].y;
        p[i].y=ny;
    }
    sort(p+1,p+n+1,cmp1);
    for(i=1;i<=n;i++)
    {
        if(p[i].x>rx[nx])    rx[++nx]=p[i].x;
        p[i].x=nx;
    }
    int l=1,r=max(rx[nx],ry[ny]),mid;
    while(l<r)
    {
        mid=l+r>>1;
        if(solve(mid))  r=mid;
        else    l=mid+1;
    }
    printf("%d",r);
    return 0;
}

```

---

## 作者：LiRewriter (赞：11)

先orz第一的大佬。。这里来稍微说一下所谓非常慢的$O(N^2logN)$算法。一共用了6个小时左右把这道题A掉，WA了八次，各位可以在记录中看到我的惨淡经历...

个人认为这道题像楼下那样跑四指针是非常丧病的行为，虽然这样有助于提高代码能力。别问我是怎么知道的。

第一步还是对答案二分，但在横坐标的枚举上，我们可以简化一下，直接枚举每个区间$[N, N + mid]$，这样就少了两个指针。那么怎么统计出这个区间内最大的点数目呢？

首先我们另外开一个数组，维护以纵坐标为第一关键字、横坐标为第二关键字排序的点。然后我们对这个数组进行一次遍历，可以取出所有符合条件的点的纵坐标，并存在一个新数组m中。这样，m中保存的就是横坐标在区间$[N, N + mid]$内所有点以纵坐标排序的结果。

这个时候，我们将p1p2作为两个指针指向数组m的最前面，然后首先将p2滚动到离p1最远的符合条件的位置。这样的话就很舒适了，我们不断的滚动p2，并修改p1使之符合条件，直到p2到达m的最后一个元素。

当然有几个细节必须注意。如果WA了八次并且每次WA的都是不同点的话可以看一下我下面的注释。。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define N 503

struct node{
	int x, y;
}le[N], cz[N];
int m[N], cnt;
int n, E;

bool cmp1 (node a, node b) {
	return a.x == b.x ? a.y < b.y : a.x < b.x;
}
bool cmp2 (node a, node b) {
	return a.y == b.y ? a.x < b.x : a.y < b.y;
}

int getcnt(int l, int a) {
	int r = l + a - 1;
	cnt = 0;
	for(int i = 1; i <= n; ++i) { //处理m
		if(cz[i].x <= r && cz[i].x >= l)
			m[++cnt] = cz[i].y;
	}
	int p1 = 1, p2 = 1;
	while(m[p2] - m[p1] + 1 <= a && p2 <= cnt) ++p2;  //滚动p2
	if(p2 > cnt || m[p2] - m[p1] + 1 > a) --p2;
    //一定要注意这里！指针有可能滚过头了，还要让她滚回来！！！
	int ans = 0;
	while(p1 <= p2 && p2 <= cnt) {
		ans = max(ans, p2 - p1 + 1); //p2 - p1 + 1就是包含的点数
		++p2;
		while(m[p2] - m[p1] + 1 > a) ++p1; //根据p2滚动p1
	}
	return ans;
}

bool check(int mid) { //枚举每一个点并求出[L, L + mid]的最大点数
	for(int i = 1; i <= n; ++i) {
		if(getcnt(le[i].x, mid) >= E) {
			return true;
		}
	}
	return false;
}

int erfen(int l, int r) { //二分答案
	if(l == r) return l;
	int mid = l + r >> 1;
	if(check(mid)) erfen(l, mid);
	else erfen(mid + 1, r);
} 

int main() {
	scanf("%d%d", &E, &n);
	for(int i = 1; i <= n; ++i) 
		scanf("%d%d", &le[i].x, &le[i].y), 
		  cz[i].x = le[i].x, cz[i].y = le[i].y;
	sort(le + 1, le + n + 1, cmp1); //横坐标第一关键字排序
	sort(cz + 1, cz + n + 1, cmp2); //纵坐标第一关键字排序
	int ans = erfen(1, 10003);
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Fheiwn (赞：6)

首先，这是一个二分   但如果用前缀和的话好像并不能AC。

我们可以想想，减少一个坐标的限制。


所以，按 行坐标排序 ，同样二分答案， 再去找满足条件的 “上下边界”，

在满足条件的“上下边界”中，找一个"左右边界"，再去判断








```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
#include<set>
#include<bitset>
#include<sstream>
#include<cstdlib>
#define QAQ int
#define TAT long long 
#define ORZ double
#define OwO bool
#define SHO short
#define F(i,j,n) for(QAQ i=j;i<=n;++i)
#define E(i,j,n) for(QAQ i=j;i>=n;--i)
#define MES(i,j) memset(i,j,sizeof(i))
#define MEC(i,j) memcpy(i,j,sizeof(j))
using namespace std;
const QAQ N=1005;
QAQ n,m,l,r,ans;
QAQ t[N];
struct data{
    QAQ x,y;
    friend OwO operator < (const data &a,const data &b){//按行坐标 从小到大排序 
        return a.x<b.x;
    }
}a[N];
OwO ok(QAQ l,QAQ r,QAQ L){
    if(r-l+1<m) return 0;
    QAQ js=0;
    F(i,l,r) t[++js]=a[i].y;//将 坐标 在上下边之内的点的 列坐标 统计起来 
    sort(t+1,t+js+1);//再去找 二分的边长内 是否有 m个 
    F(i,m,js) if(t[i]-t[i-m+1]<=L) return 1;
    return 0;
}
OwO pd(QAQ L){
    QAQ js=1;
    F(i,1,n) {//找上下边界 ——即下底和上底 
        if(a[i].x-a[js].x>L){//若当前的底 比 二分的边长 长 
            if(ok(js,i-1,L)) return 1;//去判断 这一段区间内 是否有满足条件的 左右边 
        }
        while(a[i].x-a[js].x>L) js++;
    }
    return ok(js,n,L);//最后别忘记再判断 
}
QAQ main(){
    scanf("%d%d",&m,&n);
    F(i,1,n) scanf("%d%d",&a[i].x,&a[i].y);
    sort(a+1,a+n+1);
    r=10000;
    while(l<=r){//二分答案：边长 
        QAQ mid=l+r>>1;
        if(pd(mid)) ans=mid,r=mid-1;
        else l=mid+1;
    }
    printf("%d\n",ans+1);//别忘了加一  因为二分的是点到点之间线段长 而不是点到点的距离 
    return 0;
}
```

---

## 作者：raincity (赞：5)

## 原题链接
[P2862 [USACO06JAN]Corral the Cows G](https://www.luogu.com.cn/problem/P2862)

## 分析
（文中把坐标范围$10000$称为$SIZE$）

第一反应：二分正方形边长，枚举正方形的一个顶点，前缀和判断。时间：O($SIZE^2 \log SIZE$)。 空间：O($SIZE^2$)。结果：$\color{white}\colorbox{black}{TLE} \color{red}{and} \color{white}\colorbox{black}{MLE}$。不太行的样子。

我们发现，虽然需要枚举的正方形顶点可能性很多，但是有的情况根本不需要枚举，比如当前行连一块草地也没有的时候，把这个正方形整体向下挪一行，包含的草地数一定不会变少。而一共只有最多$N$行有草地。时间优化为O($SIZE \times N \times \log SIZE$)。空间不变，为O($SIZE^2$)。结果：$ \color{white}\colorbox{black}{MLE}$。还是不太行的样子。

还有没有继续优化空间的好办法呢？

有的。我们使用前缀和是为了O(1)求出每个正方形包含的草地数。而我们实际上只需要快速知道在边长不变的顶点在同一行的正方形中包含的草地数。并不需要O(1)。

突然有一个比前缀和更加朴素的新想法：直接枚举每一块草地是否在正方形内部不就行了吗？这样做空间变成了O(N)，时间却变慢了，变成了O($\log SIZE \times N^2 \times SIZE$)。

但是这样做更容易优化了。先按照$y$坐标排序。然后，既然顶点在同一行，那么我们可以提前找出所有符合行条件的草地。接着，使用两个单调指针，扫描每块草地的$y$，让$y$也满足条件，只要两个指针之差大于等于$c$就可行。这样的话时间变成了O($\log SIZE \times SIZE \times N$)，只需要大概2.5s就可以得出答案。

终极优化：如果符合行条件的草地数量已经小于$c$，这一行就可以不看。这个条件能够在$c$较大时加速运行。而如果$c$较小，那么只要找到一个正方形满足条件，check就返回true。所以实际上远远用不到2.5s。经测试，用上述~~玄学~~算法最大点只需要34ms。

## 解决

直接上代码：
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#define R register
#define il inline

using namespace std;

const int N = 505;
struct grass {
	int x, y;
	bool operator <(const grass &nxt) const { return y < nxt.y; }
};
int f[10005];
bool exist[10005];

inline void read(int &ret) {
	ret = 0;
	R char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9') ret = ret * 10 + c - '0', c = getchar();
}

int main() {
    R int n, c, tot, ok;
    R grass a[N], b[N];
	read(c), read(n);
	for (R int i = 1; i <= n; i++) {
		read(a[i].x), read(a[i].y);
		exist[a[i].x] = true;
	}
	for (R int i = 1; i <= 10000; i++)
		if (exist[i])
			f[++tot] = i;
	sort(a + 1, a + n + 1);
	R int l = 1, r = 10000, ans = 0, mid;
	while (l <= r) {
 		R bool flag = false;
		mid = (l + r) / 2;
		for (R int i = 1; i <= tot; i++) {
			if (flag)
				break;
			ok = 0;
			for (R int j = 1; j <= n; j++)
				if (a[j].x >= f[i] && a[j].x < f[i] + mid)
					b[++ok] = a[j];
            if (ok < c)
                continue;
			for (R int j = 1, k = 1, l = 1; j <= 10000; j++) {
				while (b[k].y < j && k <= ok) k++;
				while (b[l].y < j + mid && l <= ok) l++;
				if (l - k >= c) {
					flag = true;
					break;
				}
			}
		}
		if (flag)
			ans = mid, r = mid - 1;
		else
			l = mid + 1;
	}
	cout << ans << endl;
	return 0;
}
```

### THE END

---

## 作者：陷语 (赞：5)

## 把牛

**思路**:先将每头牛的的出现次数统计一下，再将牛的原位置位置离散化一下，离散化之后再将每个位置的出现次数统计进前缀和数组s中，再通过二分答案找到合适的答案。

如果我们没有离散化直接暴力统计的话，那么时间复杂度是O(N ^ 2)，此时N的最大范围为10000，显然会炸！

如果我们离散化之后再通过二分答案寻求答案，那时间复杂度则为O(N + Nlog(N) + C ^ 2)，即使再加上求前缀和S的时间复杂度也不会超时，毕竟C的最大范围为500。

**关于二分答案** 如果我们枚举的边长符合条件，很显然我们下一步该做的就是再次缩小答案范围找更优解，直到枚举的答案不符合条件，则上解则为最优。

在这里需要**注意**的是：l和r的范围一定要符合答案定义域，既不能太大，也不能太小，不然枚举的答案会有问题 **~~QAQ~~** 。

**附上代码**：

```cpp
#include <cstdio>

using namespace std;
const int N = 550;
const int MAX = 10050;

int c, n, head_x, head_y;
int s[N][N], ax[MAX], ay[MAX], bx[N], by[N];

struct cow{int x, y;} a[N];
//离散化 
inline void discrete(){
	for(int i = 1; i <= 10000; ++i) {
		if(ax[i]) bx[++head_x] = i;
		ax[i] = head_x;
		if(ay[i]) by[++head_y] = i;
		ay[i] = head_y;
	}
}
//二分答案 
inline bool check(int x) {
	for(int i = ax[x]; i <= head_x; ++i)
		for(int j = ay[x]; j <= head_y; ++j) {
			int tx = 0, ty = 0;
			if(bx[i] - x >= 0) tx = ax[bx[i] - x];
			if(by[j] - x >= 0) ty = ay[by[j] - x];
			if(s[i][j] - s[tx][j] - s[i][ty] + s[tx][ty] >= c) return 1;
		}
	return 0;
}

int main() {
//	freopen("in.txt", "r", stdin);
	
	scanf("%d %d", &c, &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d %d", &a[i].x, &a[i].y);
		ax[a[i].x]++;
		ay[a[i].y]++;
	}
	
	discrete();
	
	for(int i = 1; i <= n; ++i) s[ax[a[i].x]][ay[a[i].y]]++;
	//求前缀和
	for(int i = 1; i <= head_x; ++i)
		for(int j = 1; j <= head_y; ++j)
			 s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
	
	int l = 1, r = 10000, mid;//注意，l和r的范围一定要符合题意，既不能太大，也不能太小。 
	while(l < r) {
		mid = (l + r) >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	
	printf("%d\n", l);
	return 0;
}
```


---

## 作者：wizard（偷开O2 (赞：4)

一道挺好的二分题。

### 题意

在一个平面直角坐标系中有 $n$ 个坐标为整数的点，求出一个边长最小的正方形使其范围内正好有 $c$ 个点。

### 分析

如果我们直接暴力枚举不同边长为 $len$ 的正方形的话，必然会超时，观察题目和样例，发现大于最小边长的 $len$ 也满足要求，所以问题必然满足单调性，直接二分。

但分析之后二分的复杂度也不满足要求，预处理就是最好的选择了。

1.离散化

观察数据范围，$1 \le C \le N \le 500$，所以我们可以在离散化后缩小数据规模，并且在 $O(log(n+c))$ 复杂度下直接查询。

为了节省空间，我们可以在一维数组内把一个点的横坐标和纵坐标都存进去，放在同一个数组中进行查找。接着我们进行排序和去重处理。

```cpp
	sort(vec.begin(),vec.end());
	vec.erase(unique(vec.begin(),vec.end()),vec.end());
```

2.前缀和

对于前缀和操作，我们不能像普通的那样一次进行操作：$S_{i,j}=S_{i-1,j} + S_{i,j-1} -S_{i-1,j-1} + a_{i,j}$。

因为横坐标和纵坐标是存储在一起的，所以需要先二分找到各个点存在的位置并标记，在进行前缀和操作。

```cpp
	for(int i=0;i<n;i++){
		int x=lower_bound(vec.begin(),vec.end(),fle[i].first)-vec.begin();
		int y=lower_bound(vec.begin(),vec.end(),fle[i].second)-vec.begin();
		sum[x][y]++;
	}
	int len=vec.size();
	for(int i=1;i<len;i++){
		for(int j=1;j<len;j++){
			sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
		}
	}
```

3.二分操作

对于查找中的每个边长 $len$，循环过程中，我么可以规定出正方形左上角和右下角的坐标，如果说长度大于当前的 $len$ 的话，就不断缩小范围的规模，直到符合标准为止。

达到标准后，利用范围中的前缀和进行计算，判断是否范围中存在的点数 $\ge c$，若符合，直接返回。

### 实现

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 
const int maxn=1e6+10;
vector <int> vec;
int sum[1005][1005];
typedef pair <int,int> pll;
pll fle[maxn];
int n,c;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
bool check(int len){
	int si=vec.size();
	for(int i=0,j=1;j<si;j++){
		while(vec[j]-vec[i+1]>len-1){
			i++;
		}
		for(int i1=0,j1=1;j1<si;j1++){
			while(vec[j1]-vec[i1+1]>len-1){
				i1++;
			}
			if(sum[j][j1]-sum[i][j1]-sum[j][i1]+sum[i][i1]>=c){
				return 1;
			}
		}
	}
	return 0;
}
signed main(){
	c=read();
    n=read();
	vec.push_back(0);
	for(int i=0;i<n;i++){
		int x;
		x=read();
		int y;
		y=read();
		vec.push_back(x);
		vec.push_back(y);
		fle[i]={x,y};
	}
	sort(vec.begin(),vec.end());
	vec.erase(unique(vec.begin(),vec.end()),vec.end());
	int len=vec.size();
	for(int i=0;i<n;i++){
		int x=lower_bound(vec.begin(),vec.end(),fle[i].first)-vec.begin();
		int y=lower_bound(vec.begin(),vec.end(),fle[i].second)-vec.begin();
		sum[x][y]++;
	}
	for(int i=1;i<len;i++){
		for(int j=1;j<len;j++){
			sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
		}
	}
	int l=1;
	int r=10000,ans=0;
	while(l<r){
		int mid=(l+r)>>1;
		if(check(mid)){
			r=mid;
		}else{
			l=mid+1;
		}
	}
	cout << l << endl;
	return 0;
}
```

---

## 作者：dinic (赞：4)

做法：此题应把横坐标从小到大排序,对正方形边长进行二分答案并检验。

**CAUTION:点的坐标就是每一个格子的坐标,面积为1*1.所以检验当选定两个x,一个上限,一个下限,差<=L时,其中是否有C个点满足纵坐标之差小于边长时要加1！！！.**
```cpp
#include<bits/stdc++.h>
using namespace std;
int const M=505;
int N,C;
struct node
{
    int x,y;
}a[M];
bool cmp(node aa,node bb)
{
    if(aa.x!=bb.x)return aa.x<bb.x;
    else return aa.y<bb.y;;
}
int L,R,mid,ans,temp[M];
bool pd(int l,int r)
{
    if(r-l+1<C)return 0;
    for(int i=l;i<=r;++i)temp[i-l+1]=a[i].y;
    std::sort(temp+1,temp+r-l+2);
    for(int i=C;i<=r-l+1;++i)if(temp[i]-temp[i-C+1]+1<=mid)return 1;
    return 0;
}
bool check()
{
    int last=1;
    bool ret=0;
    for(int i=1;i<=N;++i)
    {
        if(a[i].x-a[last].x+1>mid)ret|=pd(last,i-1);
        if(ret)return ret;
        while(a[i].x-a[last].x+1>mid)last++;
    }
    if(a[N].x-a[last].x+1<=mid)ret|=pd(last,N);
    return ret;
}
int main(){
    scanf("%d %d",&C,&N);
    for(int i=1;i<=N;++i)scanf("%d %d",&a[i].x,&a[i].y),R=std::max(R,std::max(a[i].x,a[i].y));
    sort(a+1,a+1+N,cmp);
    L=1;
    while(L<=R)
    {
        mid=(L+R)>>1;
        check()?ans=mid,R=mid-1:L=mid+1;
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：dyc2022 (赞：3)

考虑使用离散化+二维前缀和+二分答案。

### 一、离散化

注意到数据范围中每一个三叶草的坐标 $\le 10^4$，如果直接当做数组下表来存储显然会爆炸。但是总共至多 $500$ 棵三叶草，最多有 $500 \times 2 = 1000$ 个坐标。于是可以进行离散化。大致操作是将已有的数集排序后去重，然后使用 `lower_bound` 函数得出当前的数字在排序去重后的序列的位置。

### 二、二维前缀和

当我们确定一个正方形左上角的坐标和边长，我们就可以确定这个正方形。

定义 $sum_{i,j}$ 为 $(1,1)$ 和 $(i,j)$ 围成的矩形中三叶草的数量，即二维前缀和数组。转移过程为 $sum_{i,j} = sum_{i,j-1} + sum_{i-1,j} - sum_{i-1,j-1} + a_{i,j}$，其中 $a_{i,j}$ 表示 $(i,j)$ 上的三叶草数。

### 三、二分答案

考虑对边长进行二分答案。可以用 $O(1)$ 的复杂度进行查询一个二维区间内的三叶草数目。$(i,j)$ 和 $(k,l)$ 围成的矩形中的和为 $sum_{k,l}-sum_{i-1,l}-sum_{k,j-1}+sum_{i-1,j-1}$。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define N 1005
#define M 10006
using namespace std;
int c,n,x[M],y[M],sum[N][N];
vector<int> v;
main()
{
	scanf("%lld%lld",&c,&n);
	v.push_back(0);
	for(int i=1;i<=n;i++)scanf("%lld%lld",&x[i],&y[i]);
	for(int i=1;i<=n;i++)v.push_back(x[i]),v.push_back(y[i]);
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	int siz=v.size()-1;
	for(int i=1;i<=n;i++)sum[lower_bound(v.begin(),v.end(),x[i])-v.begin()][lower_bound(v.begin(),v.end(),y[i])-v.begin()]++;
	for(int i=1;i<=siz;i++)
		for(int j=1;j<=siz;j++)sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
	int l=1,r=10000;
	while(l<r)
	{
		int mid=l+r>>1,ok=0;
		for(int i=0,j=1;j<=siz;j++)
		{
			while(v[j]-v[i+1]>=mid)i++;
			for(int k=0,l=1;l<=siz;l++)
			{
				while(v[l]-v[k+1]>=mid)k++;
				if(sum[j][l]-sum[i][l]-sum[j][k]+sum[i][k]>=c)ok=1;
			}
		}
		if(ok)r=mid;
		else l=mid+1;
	}
	printf("%lld",l);
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：3)

大概是 $O(n ^ 2 \log^2 n )$ 的方法，其实可以优化但是我很懒就直接扔了。               

具体的我们发现如果我们现在有一些点，我们要用一个最小正方形来囊括它们，其边长为这些点中横坐标极差与纵坐标极差的最大值。              

然后就很套路了，先按 $x$ 排序，然后二分答案，枚举每个点作为 $x$ 最小的一个点然后向右尽量扩展，接着就变成了一个区间内选择 $n$ 个点使得 
$y$ 的极差不超过二分的值，这个直接在内部排序后暴力枚举就好了。                 

```cpp 
#include "bits/stdc++.h"
using namespace std;
const int Len = 505;
int n,m;
struct node
{
	int x,y;
}Sec[Len],SSS[Len];
bool cmpx(node x,node y){return x.x < y.x;}
bool cmpy(node x,node y){return x.y < y.y;} 
bool check(int res)
{
	for(int i = 1 ; (i + n - 1) <= m ; i ++)//枚举x最小的点 
	{
		int idx = i;
		while(idx <= m && Sec[idx].x - Sec[i].x + 1 <= res) idx ++;
		idx --; 
		if(idx - i + 1 < n) continue;
		sort(Sec + i , Sec + idx + 1 , cmpy);
		for(int j = i ; j + n - 1 <= idx ; j ++) 
			if(Sec[j + n - 1].y - Sec[j].y + 1 <= res) 
			{
				for(int k = i ; k <= idx ; k ++) Sec[k] = SSS[k];
				return true;
			}
		for(int j = i ; j <= idx ; j ++) Sec[j] = SSS[j];
	}
	return false;
}
int main()
{
	scanf("%d %d",&n,&m);
	for(int i = 1 ; i <= m ; i ++) scanf("%d %d",&Sec[i].x,&Sec[i].y);
	sort(Sec + 1 , Sec + 1 + m , cmpx);
	for(int i = 1 ; i <= m ; i ++) SSS[i] = Sec[i];
	int l = 1 , r = 20000 , anss = 0;
	while(l <= r)
	{
		int mid = (l + r) >> 1;
		if(check(mid)) anss = mid , r = mid - 1;
		else l = mid + 1;
	}
	printf("%d\n",anss);
	return 0; 
} 
```

---

## 作者：CWzwz (赞：2)

### [P2862](https://www.luogu.com.cn/problem/P2862) 题解

------------

写数据结构的时候碰到的，最后发现和 ds 没啥关系。

数据范围很小，可以接受大约 $O(n^2\cdot \log n)$ 的复杂度。

以下 $v$ 表示值域（本题为 $10^4$)。

先考虑暴力枚举正方形位置。

那么需要枚举**左上角**顶点位置和边长，$O(v^3)$；判断合法性可以二维前缀和，$O(1)$ 查询，判断三叶草数量是否大于等于 $C$。

故复杂度 $O(v^3)$，考虑优化。

暴力的主要复杂度来源有两个：

1. 枚举顶点

1. 枚举边长

------------

真的有必要枚举值域内所有点吗？有哪些点不可能作为答案？

将 **有三叶草的行列** 涂成灰色。

![](https://cdn.luogu.com.cn/upload/image_hosting/r4qemt2w.png)

只有灰色部分可能作为正方形左上角。

如果（正方形顶点）取在白色部分，必然不优于取在它右下方。因为向右下移动 **不会减少三叶草数量**，但 **更省边长**。

所以，离散化再枚举，复杂度 $O(v^2)\to O(n^2)$。

------------

考虑边长枚举的优化。

发现单调性：顶点枚举了，是固定的，那么正方形中的三叶草数量随边长增加而不减。可以二分。

$O(v)\to O(\log v\cdot \log n)$

（这个 $\log n$ 是实现的时候带的，蒟蒻不知道怎么优化掉，但是能过qwq）

------------

时间复杂度 $O(n^2\cdot \log n\cdot \log v)$，空间复杂度 $O(n^2)$。

时空复杂度带常数 $4$。

那么就剩下代码了。

```cpp
//Problem: P2862
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
#define i32 INT_MAX
#define i64 LONG_LONG_MAX
#define pii pair<int, int>
#define pll pair<long long, long long>
#define pb push_back
typedef long long ll;
const int N = 1010;
ll read(){ll x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}return x*f;}
void print(ll x){if(x<0)putchar('-'),x=-x;if(x>9)print(x/10);putchar(x%10+48);}
char gc(){char c=getchar();while(c==' '||c=='\n')c=getchar();return c;}

int n, m, c, xmax, ymax, answer = inf, l, r, mid, ans;
int x[N], y[N];
int b[N];
int map[N][N], s[N][N];

int sum(int x1, int y1, int x2, int y2) {
    return s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1 - 1][y1 - 1];
}
// 查询：左上角 (x1, y1)，右下角 (x2, y2) 正方形中三叶草数

int main() {
    std::cin >> c >> n;
    for(int i = 1; i <= n; i++) {
        x[i] = b[++m] = read();
        y[i] = b[++m] = read();
        xmax = std::max(xmax, x[i]);
        ymax = std::max(ymax, y[i]); // 记录这个是为了判越界~
    }
    std::sort(b + 1, b + m + 1); m = std::unique(b + 1, b + m + 1) - b - 1;
    for(int i = 1; i <= n; i++) {
        x[i] = std::lower_bound(b + 1, b + m + 1, x[i]) - b;
        y[i] = std::lower_bound(b + 1, b + m + 1, y[i]) - b;
        map[x[i]][y[i]]++; // map是四叶草数量数组
    } // 离散化
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= m; j++)
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + map[i][j];
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= m; j++) {
            int cx = b[i], cy = b[j]; // 正方形左上角为原图中的 (cx, cy); 离散坐标 (i, j)
            if(cx > xmax || cy > ymax) continue;
            l = 0, r = std::max(xmax - cx , ymax - cy) + 1, mid, ans = inf; // 二分正方形的边长为多少原图长度
            while(l <= r) { // 二分边长
                mid = l + r >> 1;
                if(sum(i, j, std::upper_bound(b + 1, b + m + 1, cx + mid) - b - 1, std::upper_bound(b + 1, b + m + 1, cy + mid) - b - 1) >= c) {
                // upper_bound 搜索：原坐标 对应的 离散后坐标
                    r = mid - 1;
                    ans = mid;
                } else {
                    l = mid + 1;
                }
            }
            answer = std::min(answer, ans);
        }
    }
    std::cout << answer << '\n';
    return 0;
}
```

---

## 作者：qinyiyang2012 (赞：2)

### 思路：

我们一看到这道题的 $x,y$ 范围过大时，便知道开一个普通二维数组存储坐标一定是会 MLE 的，因此我们可以想到**离散化**这个好东西。

什么是离散化呢？

离散化： 是把无限空间中有限的个体映射到有限的空间中去，以此提高程序的时空效率的一种技巧。通俗的说，离散化是在不改变数据相对大小的条件下，对数据进行相应的缩小。

离散化模板：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,a[N];
vector<int> v;
int find(int x){return lower_bound(v.begin(),v.end(),x)-v.begin()+1;}//找到原数组的值对应在离散化数组 v 中的值，这里用到了 lower_bound 函数，作用是二分查找左边界
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
   //读入、输出优化
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		v.push_back(a[i]);//将原数组的值拷贝到离散化数组中
	}
	sort(v.begin(),v.end());//必须先排序才能确定映射位置
	v.erase(unique(v.begin(),v.end()),v.end());//unique 函数，用于去重，这行语句的意义是把 v 数组重复的值删除
	for(int i=1;i<=n;i++)a[i]=find(a[i]);//离散化 a 数组
	for(int i=1;i<=n;i++)cout<<a[i]<<" ";//输出被离散化后的数组
	return 0;
}
```

解决了这个瓶颈后，我们继续看题。我们发现要求一个正方形矩阵的总和以统计该矩阵是否包含了至少 $c$ 个三叶草，那么自然而然地可以想到**二维前缀和**，可以 $O(n^2)$ 预处理，$O(1)$ 回答。

[最大空方阵](https://iai.sh.cn/problem/602)：二维前缀和例题，与本题目极像。

如果你不会二维前缀和，那么请仔细阅读 [一维、二维前缀和详解](https://blog.csdn.net/melonyzzZ/article/details/128170956)。

我们可以枚举边长，用二维前缀和判断一下边长为 $len$ 的正方形内有没有至少 $c$ 片三叶草。而直接枚举 $len$ 的话，必然会 TLE。而这个问题很明显具有单调性：即大于某个值的 $len$ 都可以满足，而小于这个值的都不满足。那么我们就可以二分解决。如果记点的坐标为 $(x,y)$ 的话，那么二分的复杂度为 $O(\log_2\max(x,y))$。

解决了以上问题后，我们综合考虑，得出该程序时间复杂度为 $O(\max(n^2,\log_2\max(x,y))$，时间大约为 64ms，轻松 AC！

### 参考代码：

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define PII pair<int,int>
#define numsin nums.push_back
const int N=1e3+5;
int c,k,n,a[N][N];
vector<PII> nodes;
vector<int> nums;
int find(int x){//离散化
    int l=0,r=nums.size()-1,mid;
    while(l<r){//手写二分
        mid=(l+r+1)>>1;
        if(nums[mid]<=x)l=mid;
        else r=mid-1;
    }
    return r;
}
bool check(int x){//检查边长是否合理
    for(int x1=1,x2=1;x2<nums.size();x2++){
        while(nums[x2]+1-nums[x1]>x)x1++;
        for(int y1=1,y2=1;y2<nums.size();y2++){
            while(nums[y2]+1-nums[y1]>x)y1++;
            if(a[x2][y2]-a[x1-1][y2]-a[x2][y1-1]+a[x1-1][y1-1]>=c)return true;//成立直接返回
        }
	}
    return false;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
   //读入、输出优化
	cin>>c>>k;
	nums.push_back(0);//防止越界，补零
	for(int i=0;i<k;i++){
		int x,y;
		cin>>x>>y;
		n=max(n,max(x,y));//取坐标最大值
		numsin(x),numsin(y);//推入离散化数组中
		nodes.push_back({x,y});//存储坐标
	}
	sort(nums.begin(),nums.end());//必须先排序才能确定映射位置
	nums.erase(unique(nums.begin(),nums.end()),nums.end());//unique 函数，用于去重，这行语句的意义是把 v 数组重复的值删除
	for(int i=0;i<k;i++){
        int x=find(nodes[i].first),y=find(nodes[i].second);
        a[x][y]++;//建立地图
	}
	for(int i=1;i<nums.size();i++)for(int j=1;j<nums.size();j++)a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1];//初始化前缀和数组
    int l=1,r=n;//二分查找最小边长
    while(l<r){
        int mid=(l+r)>>1;
        if(check(mid))r=mid;
        else l=mid+1;
    }
    cout<<l;
	return 0;
}
```

---

## 作者：dduck705 (赞：1)

分享一个勉强过问的 $O(N^{2}\log^{2}{N})$ 做法。考虑二分答案，记 `test(m)` 表示边长为 $m$ 的正方形是否能覆盖 $C$ 片三叶草。于是，可以写出  
```cpp
while(left<right){
	middle = (left+right)>>1;
	if(test(middle)){
		right = middle;
	}else{
		left = middle+1;
	}
}
```
对于 `test(m)` 的实现，可以使用二维前缀和，然后依次尝试判断所有边长为 $m$ 的正方形。注意到三叶草坐标的取值范围在 $1$ 到 $10000$ 之间，又有 $N\leq500$ ，所以应当进行离散化。  
## 离散化  
我们的目的是将原先可能有 $10000\times10000$ 大小的地图压缩到 $N\times N$ 以内，则不需要考虑那些没有任何三叶草的行或列，即不需要考虑所有三叶草的坐标中都没有出现的行或列。我们将所有坐标暂时存储进数组 `points[][]` 中，所有出现的坐标值全部存储进数组 `arr[]` 中。将 `arr` 排序，再对 `arr` 去重后的数组 `dis` 中各点的下标即为它们离散化后的坐标。然后定义二分查找函数 `f(x)` 与 `g(x)` 分别表示原始坐标对应的离散化后的坐标或其后继和原始坐标对应的离散化后的坐标或其前驱。此时，便可通过 `points[][]` 建立离散化后的地图 `map_` 。  
```cpp
//这里arr存储了所有坐标值，一个三叶草有x,y两个坐标值，所以arr内有2n个数。
std::sort(arr+1,arr+n*2+1);
for(int i=1;i<=n*2;i++){
	if(i==1 || arr[i]!=arr[i-1]){
		dis[++cnt] = arr[i];
	}
}
for(int i=1;i<=n;i++){
	points[i][0] = f(points[i][0]);
	points[i][1] = f(points[i][1]);
	map_[points[i][0]][points[i][1]] = true;
}
```  
以样例为例，样例中没有任何三叶草在第 $3$ 行或第 $3$ 列，可见， $(1,2)$ 离散化后为 $(1,2)$ ， $(2,1)$ 离散化后为 $(2,1)$ ， $(4,1)$ 离散化后为 $(3,1)$ ， $(5,2)$ 离散化后为 $(4,2)$ 。  
## 离散化后的二维前缀和  
 `map_` 为原始数组， `sums` 为其前缀和。  
 预处理和往常一样，有  
$s[i][j] = s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j]$  
下面讨论在 `test(m)` 中测试时正方形的取值。  
定义 $x_1,y_1$ 为测试的正方形的左上角坐标（不在正方形内部）， $x_2,y_2$ 为测试的正方形的左上角坐标（在正方形内部）。我们将枚举所有可能的 $x_2,y_2$ 。理想情况下， $m$ 有其对应的离散化后的坐标， $x_2,y_2$ 的取值从此到 `cnt` 即可。但为了避免漏算，若不存在这样的坐标，应从其前驱开始，所以每次循环开头，应令 $x_2=g(m)$ ， $y_2=g(m)$ 。在知晓 $x_2$ 后，对于 $x_1$ 的取值，比较直接的想法是 $x_2$ 对应的原始值减去 $m$ 后所对应的离散化后的值或其后继 $-1$ ，即 $x_1 = f(dis[x_2]-m)-1$ 。但是，这里 $x_2$ 也许会作为前驱存在，这么做极易发生多算的情况。解决办法很简单， $+1$ 即可。所以，正确的做法是  
$$x_1 = f(dis[x_2]-m+1)-1$$  
同理，对于 $y_1$ 有  
$$y_1 = f(dis[y_2]-m+1)-1$$  
在确定正方形的两个坐标点后，按照常规的二维前缀和做法计算正方形内三叶草的和并加以判断即可。至此，本题结束。 `test(m)` 的时间复杂度为 $O(N^{2} \log{N})$ ，乘上二分答案的 $O(\log{N})$ ，总体时间复杂度为 $O(N^{2}\log^{2}{N})$ 。下面给出代码。
```cpp
#include<bits/stdc++.h>

//数组记得开大一点
int n,c,cnt,arr[10005],dis[10005],points[5005][2],sums[5005][5005];
bool map_[5005][5005];

int f(int x){//二分查找后继 
	int l = 1,r = cnt,mid;
	while(l<r){
		mid = (l+r)>>1;
		if(dis[mid]>=x){
			r = mid;
		}else{
			l = mid+1;
		}
	}
	return l;
}

int g(int x){//二分查找前驱 
	int l = 1,r = cnt,mid;
	while(l<r){
		mid = (l+r+1)>>1;
		if(dis[mid]<=x){
			l = mid;
		}else{
			r = mid-1;
		}
	}
	return l;
}

bool test(int m){//判断边长为m的正方形是否可行 
	int x1,y1,x2,y2,st = g(m);
	for(x2=st;x2<=cnt;x2++){
		for(y2=st;y2<=cnt;y2++){
			x1 = f(dis[x2]-m+1)-1;
			y1 = f(dis[y2]-m+1)-1;
			if(sums[x2][y2]-sums[x1][y2]-sums[x2][y1]+sums[x1][y1]>=c){
				return true;
			}
		}
	}
	return false;
}

int main(){
	
	scanf("%d %d",&c,&n);
	for(int i=1,x,y;i<=n;i++){
		scanf("%d %d",&x,&y);
		arr[i*2-1] = points[i][0] = x;
		arr[i*2] = points[i][1] = y;
	}
	
	std::sort(arr+1,arr+n*2+1);//离散化 
	for(int i=1;i<=n*2;i++){
		if(i==1 || arr[i]!=arr[i-1]){
			dis[++cnt] = arr[i];
		}
	}
	for(int i=1;i<=n;i++){
		points[i][0] = f(points[i][0]);
		points[i][1] = f(points[i][1]);
		map_[points[i][0]][points[i][1]] = true;
	}
	
	for(int i=1;i<=cnt;i++){//前缀和 
		for(int j=1;j<=cnt;j++){
			sums[i][j] = sums[i-1][j]+sums[i][j-1]-sums[i-1][j-1]+map_[i][j];
		}
	}
	
	int left = 1,right = dis[cnt],middle;//二分答案 
	while(left<right){
		middle = (left+right)>>1;
		if(test(middle)){
			right = middle;
		}else{
			left = middle+1;
		}
	}
	
	printf("%d",left);
	
	return 0;
}
```  
第一篇题解，可能写的不是很清楚欸qwq。

---

## 作者：D0000 (赞：1)

# P2862 [USACO06JAN] Corral the Cows G 题解
## 思路
枚举正方形右下角，二分边长，判断正方形内部三叶草数量是否大于等于 $C$，由于前缀和会爆空间，三叶草又很少，所以直接循环判断每一个三叶草在不在正方形内部，最后再取最小的符合条件的边长作为答案。复杂度 $\text{O}(t^2\log(t^2)n)$，其中 $t$ 表示坐标范围，$t^2$ 就已经 $10^8$ 了，肯定超时。

那就考虑在枚举右下角时去掉一些不优的方案。

首先，我一开始以为只有有三叶草的格子才可能作为右下角。但是一个很明显的反例：

![](https://cdn.luogu.com.cn/upload/image_hosting/6bi6q8n2.png)

橙色代表三叶草，很明显红色格子是得考虑作为右下角的！

但是若当前格子有三叶草，是必须考虑的。

而若当前格子没有三叶草，则：

1. 若当前格子正左方没有三叶草，则它不比它上面的格子更优，不考虑。
1. 若当前格子正上方没有三叶草，则它不比它左面的格子更优，不考虑。

然后，就完了！

总而言之，只有当前格子有三叶草或当前格子的正左正上都有三叶草，才需考虑将其作为右下角，这样符合条件的格子就一定不超过 $({\frac{n}{2}})^2+n$ 个。

最后总时间复杂度 $\text{O}(\frac{n^2}{4}\log(\frac{n^2}{4})n)$，刚刚好够。

虽然复杂度较高，但代码简单，如下：

```cpp
#include<cstdio>
int c,n,nodex[1000005],nodey[1000005],cnt,zans=1e4;
bool b[10005][10005],bx[10005];
int main(){
	scanf("%d%d",&c,&n);
	for(int i=1;i<=n;i++)scanf("%d%d",&nodex[i],&nodey[i]),b[nodex[i]][nodey[i]]=1;
	cnt=n+1;
	for(int i=1;i<=1e4;i++){
		bool bb=0;
		for(int j=1;j<=1e4;j++){
			if(b[i][j])bb=1,bx[j]=1;
			if(bb&&bx[j])nodex[cnt]=i,nodey[cnt++]=j;
		}
	}
	for(int i=1;i<cnt;i++){//printf("%d %d\n",nodex[i],nodey[i]);
		int xx=nodex[i],yy=nodey[i];
		int l=1,r=1e4,mid,ans=1e4;
		while(l<=r){
			mid=(l+r)>>1;
			int j=0;
			for(int k=1;k<=n;k++)if(nodex[k]<=xx&&nodey[k]<=yy&&xx-nodex[k]<mid&&yy-nodey[k]<mid)j++;
			if(j>=c)r=mid-1,ans=mid;
			else l=mid+1;
		}
		zans>ans?zans=ans:ans=ans;
	}
	printf("%d",zans);
}
```

---

## 作者：syzf2222 (赞：1)

考虑二分答案，问题转化为能否用边长为$len$的正方形框住大于等于$c$个草场。

继续转化问题，即边长为$len$的正方形能框住的最多草场数是否大于$c$。

考虑每一个右下角$(x,y)$，则每一个横坐标在$[x-len+1,x]$，纵坐标在$[y,y+len-1]$中的草场都可以被框住。

转而考虑每一个草场$(x,y)$的贡献，它对横坐标在$[x,x+len-1]$，纵坐标在$[y-len+1,y]$的右下角都有贡献。

考虑扫描线，对于每一个草场可以看成两个线段，即$\{x,y-len+1,y,1\}$和$\{x+len,y-len+1,y,-1\}$。

即这个草场从$x$起在区间$[y-len+1,y]$上生效，从$x+len$起失效。

线段树维护最大值即可，时间复杂度$\Theta(nlogn)$（二分+扫描线）。

代码如下，仅供参考：
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
const int maxn=1e4+10;
const int N=1e4+5;
int n,m,ans,a[maxn],b[maxn],tot;
struct node{int pos,l,r,val;}p[maxn];
inline int cmp(node x,node y){
	if(x.pos==y.pos)return x.val<y.val;
	return x.pos<y.pos;
}
int tr[maxn<<4],lazy[maxn<<4];
inline void build(int h,int l,int r){
	tr[h]=lazy[h]=0;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(h<<1,l,mid);
	build(h<<1|1,mid+1,r);
}
inline void pushup(int h,int z){
	tr[h]+=z;lazy[h]+=z;
}
inline void pushdown(int h){
	if(!lazy[h])return;
	pushup(h<<1,lazy[h]);
	pushup(h<<1|1,lazy[h]);
	lazy[h]=0;
}
inline void update(int h,int l,int r,int x,int y,int z){
	if(l>y||r<x)return;
	if(l>=x&&r<=y){pushup(h,z);return;}
	pushdown(h);
	int mid=(l+r)>>1;
	update(h<<1,l,mid,x,y,z);
	update(h<<1|1,mid+1,r,x,y,z);
	tr[h]=max(tr[h<<1],tr[h<<1|1]);
}
inline int check(int len){
	build(1,-N,N);tot=0;
	for(int i=1;i<=n;i++){
		p[++tot]=(node){a[i],b[i]-len+1,b[i],1};
		p[++tot]=(node){a[i]+len,b[i]-len+1,b[i],-1};
	}
	sort(p+1,p+1+tot,cmp);
	for(int i=1;i<=tot;i++){
		update(1,-N,N,p[i].l,p[i].r,p[i].val);
		if(tr[1]>=m)return 1;
	}
	return 0;
}
int main(){
	m=read(),n=read();
	for(int i=1;i<=n;i++)
		a[i]=read(),b[i]=read();
	int l=1,r=N;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
```
深深地感到自己的弱小。


---

## 作者：Thomastine (赞：1)

# #### 蒟蒻第一次发题解（~~外加第一次用MARKDOWN~~）
一眼就能看出的二分题
主函数中二分枚举答案，
判断时每次将合理x轴范围p[i].x到p[i].x+qh-1内所有点按照p[i].y从小到大排序，再以要求的个数分组判断是否在区间内
核心代码
### # if(p[sb[j]].y-p[sb[j-c+1]].y+1<=qh) return 1;
以下是代码
```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<map>
#include<cstring>
using namespace std;
const double inf = 1e10;
const int maxn = 0x7f7f7f7f;
inline void read(int &x)
{
    x=0;int f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') f=-1; c=getchar();}
    while(c<='9'&&c>='0'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    x*=f;
}
inline void print(int x)
{
    if(x<0){x=-x;putchar('-');}
    if(x>9) print(x/10);
    putchar(x%10+'0');
}
struct po{
    int x,y;
}p[555];
int c,n;
int sb[501];
inline bool mmp(int a,int b)
{
	return p[a].y<p[b].y;
}
inline int check(int qh)
{
    for(register int i=1;i<=n;i++)
    {
    	int tot=0,maxx=qh+p[i].x-1;
    	for(register int j=i;j<=n;j++)
		{
			if(p[j].x<=maxx)
			{
				tot++;
				sb[tot]=j;
			}
			else break;
		}
		if(tot<c) continue;
		stable_sort(sb+1,sb+tot+1,mmp);                                                
    	for(int j=tot;j>=c;j--)
    		if(p[sb[j]].y-p[sb[j-c+1]].y+1<=qh) return 1;
	}
    return 0;
}
inline bool cmp(po a,po b)
{
    if(a.x==b.x) return a.y<b.y;
    return a.x<b.x;
}
int main()
{
	int zuida=-maxn,zuixiao=maxn;
    read(c);read(n);
    for(register int ii=1;ii<=n;ii++)
    { 
        read(p[ii].x);
        read(p[ii].y);
	}
    stable_sort(p+1,p+n+1,cmp);
    int l=1,r=10001,ans=0,temp=-1,mid=-1;
    for(int ii=1;ii<=100;ii++)
    {
    	temp=mid;
      	mid=(l+r)>>1;
      	if(temp==mid) break;
        if(check(mid))
        {
            ans=mid;
            r=mid;
        }
        else l=mid;
    }
    print(ans);
}
```



---

## 作者：ybc2026lhy (赞：0)

### 分析

  对于这个问题，我们发现，方格的坐标点范围是 10000 以内，但是，草场的数量 $n$ 最多只有 500 个，因此，拿到这个题的第一件事就是进行离散化，将 $10000 \times 10000$ 的地图变为最多 $500 \times 500$ 的范围内进行。

  在离散化完成以后，为了更好地求到每个区域内的草场数量，因此，需要对地图进行二维前缀和。然后，为了更快地找到最终的答案，我们可以使用二分来查找答案，对于每一个二分得到的 $mid$，在行和列上分别暴力枚举范围 $[r,r+mid],[c,c+mid]$，再利用前缀和快速求到枚举范围内的数值大小，最后得到答案。
  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int n,m,x[N],y[N],px[N],py[N],tx,ty;
inline int queryx(int x){return upper_bound(px+1,px+tx,x)-px-1;}
inline int queryy(int y){return upper_bound(py+1,py+ty,y)-py-1;}
int s[N][N];
inline bool check(int len){
	for(int i=1,lx=0;i<tx;i++){
		while(lx<tx-1&&px[i]>=px[lx+1]+len){
			lx++;
		}
		for(int j=1,ly=0;j<ty;j++){
			while(ly<ty-1&&py[j]>=py[ly+1]+len){
				ly++;
			}
			if(s[i][j]-s[i][ly]-s[lx][j]+s[lx][ly]>=n){
				return true;
			}
		}
	}
	return false;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL),cout.tie(NULL);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>x[i]>>y[i];
		px[++tx]=x[i],py[++ty]=y[i];
	}
	sort(px+1,px+tx+1);
	tx=unique(px+1,px+tx+1)-px;
	sort(py+1,py+ty+1);
	ty=unique(py+1,py+ty+1)-py;
	for(int i=1;i<=m;i++){
		x[i]=queryx(x[i]);
		y[i]=queryy(y[i]);
		s[x[i]][y[i]]++;
	}
	for(int i=1;i<tx;i++){
		for(int j=1;j<ty;j++){
			s[i][j]+=s[i][j-1]+s[i-1][j]-s[i-1][j-1];
		}
	}
	int l=1,r=10000;
	while(l<r){
		int mid=(l+r)>>1;
		if(check(mid)){
			r=mid;
		} else {
			l=mid+1;
		}
	}
	cout<<l;
	return 0;
}

---

