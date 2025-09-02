# [USACO05DEC] Barn Expansion G

## 题目描述

Farmer John 有 $N$（$1 \leq N \leq 25000$）个矩形牛棚，它们的墙与坐标轴平行，且坐标在 $[0,10^6]$ 范围内。保证任意两个牛棚不重叠，但可能有公共的墙。

由于奶牛数量不断增加，FJ 打算扩张牛棚。一个牛棚是可以扩张的，当且仅当它的墙与其他牛棚的墙没有公共部分。如果两个牛棚有一个公共角，这两个牛棚均不可扩张。

请你求出有多少牛棚是可以扩张的。

## 说明/提示

前两个牛棚可以扩张。

## 样例 #1

### 输入

```
5
0 2 2 7
3 5 5 8
4 2 6 4
6 1 8 6
0 0 8 1```

### 输出

```
2```

# 题解

## 作者：海洋守卫者 (赞：5)

# [P6081](https://www.luogu.com.cn/problem/P6081) - Barn Expansion 牛棚扩张

[**【双倍经验】**](https://www.luogu.com.cn/problem/SP702)

## 解题思路

> 一种基于“贪心-区间问题”的优雅暴力解题方法。

根据题意，如果两个牛棚的边有相交的部分，那么这两个牛棚都不可扩张。

首先观察样例，我们可以得出下图：

![样例图解](https://cdn.luogu.com.cn/upload/image_hosting/k6jnjk9g.png)

此时结合题面，有人就会得出结论：两两矩形之间不可能相交。

说的太对了！但这条信息对于本篇题解没有任何意义。

请再次用我们大大的眼睛去好好盯一盯这张图片，将眼光从最左边，缓缓地移到最右边——你就会发现，如果两个矩形的边有重合的部分，那两个矩形在横坐标轴上的投影必然相交——假设共用一个端点也算相交的话。（不用我解释投影是什么吧）

这也太明显了！小学二年级的同学也可以看出来好吧。这真的对解题有帮助吗？

你想想，如果这样的话，那我是不是可以利用这一条性质，写一份优化过的 $O(n^2)$ 的暴力……嗯？

按照左边界为第一关键字，下边界为第二关键字（用于加速），对所有矩形进行排序。然后，从左往右，选定一个矩形，再从左往右扫描与他横坐标相交的矩形，判断纵坐标上是否相交，是的话就将两者全部标记（说白了就是暴力）。

虽然时间复杂度为 $O(n^2)$，但实际可以跑得飞快。

关键代码如下：

```cpp
sort(p+1,p+1+n,cmp);
for(int i=1;i<=n;i++)
{
	int l=p[i].a,r=p[i].c,u=p[i].d,d=p[i].b;  //左、右、上、下
	for(int j=i+1;j<=n&&p[j].a<=r;j++)
	{
		if(p[j].d>=d&&p[j].b<=u)could[i]=could[j]=false;
	}
}
```

## 实现细节

本题不要多测清空，除此之外没有任何细节。

## 完整代码
```cpp
#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;
struct Square{
	int a,b,c,d;
}p[50005];
inline bool cmp(Square A,Square B)
{
	return A.a<B.a;
}
bool could[50005];
int n,ans;
int main()
{ 
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d %d %d %d",&p[i].a,&p[i].b,&p[i].c,&p[i].d);
		if(p[i].a>p[i].c)swap(p[i].a,p[i].c);
		if(p[i].b>p[i].d)swap(p[i].b,p[i].d);
		could[i]=true;
	}
	sort(p+1,p+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		int l=p[i].a,r=p[i].c,u=p[i].d,d=p[i].b;  //左、右、上、下
		for(int j=i+1;j<=n&&p[j].a<=r;j++)if(p[j].d>=d&&p[j].b<=u)could[i]=could[j]=false;
	}
	for(int i=1;i<=n;i++)if(could[i])ans++;
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Mustard_Zjld (赞：1)

### 一种新奇的解法

我讨厌树状数组。  
我讨厌线段树。  
我讨厌扫描线。  
怎么办？

**Hint1**：  
二维统计过于麻烦，考虑将长方形化成线性区间。  
首先，我们将所有点都按照横纵坐标都和它们的 id 分开存储（`vector x`，`vector y`），那么每一个长方形都在数组中被标为一条线段。  
那么我们可以用两种操作统计重复的边：  
1. 对于每一行有线段存在的 $x$，计算相交的 $y$ 区间，并将相交的 $y$ 区间标记为 `false`（即不可以扩张）。  
2. 对于每一列有线段存在的 $y$，计算相交的 $x$ 区间，并将相交的 $x$ 区间标记为 `false`（即不可以扩张）。  

考虑怎么计算相交的区间并标记？

**Hint2**：  
是不是可以考虑使用亿些数据结构来寻找线段的并？


# 正解

我们以行为例，列的操作同理。  
1. 先将所有线段以左端点坐标大小排序，并遍历所有线段。  
2. 对于每一条线段：  
   - 在统计完后将该线段的结尾加入一个小根堆，并将其的 `vis` 数组标为 1。  
   - `while` 判断小根堆顶的数值是否大于当前线段的起点，如果严格小于，那么标记该数值所在的线段的 `vis` 为 0，即不可能与后面的任何一个线段有交。（因为操作 1 已将所有线段以左端点坐标大小排序）  
   - 如果在堆中还有元素，这就说明该线段一定与其他的线段有交，我们使用一个 `stk` 存储目前所有可行的线段，这样的好处是这些线段在 `stk` 中都保持以左端点坐标大小排序。如果栈顶元素在 `vis` 中显示不可用（既不在堆中），我们可以随时弹出，直到栈顶元素在堆中，这样我们可以轻松的求出与该线段的最后一条线段，此时我们只需将栈顶与该线段同时标记即可。之后将该线段在 `vis` 中标记，并入堆和入栈即可。  
3. 以此方式遍历完整个序列。并输出所有没有交的长方形。

### 亿些细节

1. 为保证 `vis` 的存储的唯一性，对于每一个点我们可以使用 `x * 1000000 + y` 为下标的方式表示，很容易想到 `map`。  
2. 不要忘记清空堆和栈。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool f[25003];
int n,xs,xe,ys,ye,MAXx,MAXy,ans;
stack<int> stk;
map<int,int> vis;
priority_queue<pair<int,int> > q;
vector<pair<pair<int,int>,int> > x[1000003],y[1000003];
void clacx(int u)
{
    int l=y[u].size();
    sort(y[u].begin(),y[u].end());
    for(int i=0;i<l;i++)
    {
        while(q.size()&&q.top().first<y[u][i].first.first)
        {
            vis[q.top().second*1000000+q.top().first]=1;
            q.pop();
        }
        while(stk.size()&&vis[y[u][stk.top()].first.first*1000000+y[u][stk.top()].first.second])
            stk.pop();
        if(stk.size())
        {
            f[y[u][stk.top()].second]=0;
            f[y[u][i].second]=0;
        }
        vis[y[u][i].first.first*1000000+y[u][i].first.second]=0;
        q.push({y[u][i].first.second,y[u][i].first.first});
        stk.push(i);
    }
    while(q.size())
    {
        vis[q.top().second*1000000+q.top().first]=1;
        q.pop();
    }
    while(stk.size())
        stk.pop();
    return;
}
void clacy(int u)
{
    int l=x[u].size();
    sort(x[u].begin(),x[u].end());
    for(int i=0;i<l;i++)
    {
        while(q.size()&&q.top().first<x[u][i].first.first)
        {
            vis[q.top().second*1000000+q.top().first]=1;
            q.pop();
        }
        while(stk.size()&&vis[x[u][stk.top()].first.first*1000000+x[u][stk.top()].first.second])
            stk.pop();
        if(stk.size())
        {
            f[x[u][stk.top()].second]=0;
            f[x[u][i].second]=0;
        }
        vis[x[u][i].first.first*1000000+x[u][i].first.second]=0;
        q.push({x[u][i].first.second,x[u][i].first.first});
        stk.push(i);
    }
    while(q.size())
    {
        vis[q.top().second*1000000+q.top().first]=1;
        q.pop();
    }
    while(stk.size())
        stk.pop();
    return;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        f[i]=1;
        cin>>xs>>ys>>xe>>ye;
        MAXx=max(MAXx,xe);
        MAXy=max(MAXy,ye);
        x[xs].push_back({{ys,ye},i});
        if(xe!=xs)
            x[xe].push_back({{ys,ye},i});
        y[ys].push_back({{xs,xe},i});
        if(ye!=ys)
            y[ye].push_back({{xs,xe},i});
    }
    for(int i=0;i<=MAXx;i++)
        if(x[i].size())
            clacy(i);
    for(int i=0;i<=MAXy;i++)
        if(y[i].size())
            clacx(i);
    for(int i=1;i<=n;i++)
        ans+=f[i];
    cout<<ans;
    return 0;
    //by zjld
}
```

## 启示

可以以该方法在 $O(n \log n)$ 的时间复杂度内求得线段的并。

---

## 作者：Tang_chao (赞：1)

大↘神↗教我STL/jy
## P6081 [USACO05DEC] Barn Expansion G 题解

把每个牛棚拆成四条边，暂时先考虑每个横向的墙（纵向的同理）。结构体里要存这些墙的左右端点和高度，以及原牛棚编号。  

不难发现当两个墙处于同一行时才有可能有公共边。可以把在同一行的墙塞进一个可重集，按左端点排序。

对于每个墙，在对应行二分即可。  

具体地，记墙的左右端点为 $l,r$。二分找到第一个墙，满足左端点**不小于** $l$，这个墙记为 $L$。二分找到第一个墙，满足左端点**大于** $r$，这个墙记为 $R$。  
直接暴力枚举 $[L,R)$ 的墙，如果存在别的牛棚的墙，则这些墙都不能扩张，同时 $[l,r]$ 这个墙也不能扩张。可能有点绕，详见代码。

举个例子。这是在同一个可重集中的二分情况：
![](https://cdn.luogu.com.cn/upload/image_hosting/isq7qr2s.png)
红色区间会把黄色框框里的墙，还有它自己，设为不可扩张的。  
可能有的小朋友会说左边的墙没被查到。实际上对于左边的墙，它可以二分到红色的墙，也会被设为不可扩张的。  
现在正确性没得说吧。

最坏复杂度 $O(n^2)$，不过显然跑不满。优化下辈子再补一个。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 25009
#define M 1000009
#define IT multiset<range>::iterator
int n;
bool ans[N];
struct node{ int x,y,u,v; } p[N];
struct range{ int l,r,id; };
bool operator < (range x,range y){ return x.l < y.l; }
multiset<range> s[2][M];
void check(int op,int x,int l,int r,int id){
	IT L = s[op][x].lower_bound((range){l,0,0});
	IT R = s[op][x].upper_bound((range){r,0,0});
	for(IT it = L;it != R;it++)
		if(it->id != id){
			ans[id] = 0;
			ans[it->id] = 0;
		}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i = 1;i <= n;i++){
		ans[i] = 1;
		cin>>p[i].x>>p[i].y>>p[i].u>>p[i].v;
		s[0][p[i].x].insert((range){p[i].y,p[i].v,i});
		s[0][p[i].u].insert((range){p[i].y,p[i].v,i});
		s[1][p[i].y].insert((range){p[i].x,p[i].u,i});
		s[1][p[i].v].insert((range){p[i].x,p[i].u,i});
	}
	for(int i = 1;i <= n;i++){
		check(0,p[i].x,p[i].y,p[i].v,i);
		check(0,p[i].u,p[i].y,p[i].v,i);
		check(1,p[i].y,p[i].x,p[i].u,i);
		check(1,p[i].v,p[i].x,p[i].u,i);
	}
	int cnt = 0;
	for(int i = 1;i <= n;i++) cnt += ans[i];
	cout<<cnt<<endl;
	//for(int i = 1;i <= n;i++) cout<<ans[i]; cout<<endl; 
	return 0;
}
```

---

## 作者：Betrayer_of_love (赞：1)

大力扫描线，防止一些麻烦的情况就从左往右和从右往左都做一遍。

把一个矩形拆成两个部分 $(l,d,u)(r,d,u)$ 表示横坐标为 $l/r$ ，纵坐标从 $d$ 到 $u$ 的两个线段。

然后按照横坐标排序 如果横坐标相等则插入的优先。

然后先处理新插入的情况 这题矩形有交只有两种情况 上下相邻和左右相邻。

上下相邻比较好处理：

开两个 $O(M)$ 的数组， $M$ 是坐标大小。

$f[i][0]$ 表示以 $i$ 为下端点的矩形的号码。

$f[i][1]$ 表示以 $i$ 为上端点的矩形的号码。

因为矩形不存在重叠等情况 所以在任何时刻他的值是唯一的。

所以可以插入的时候查询一下那两个端点就可以了。

左右情况可以开两个 $O(M)$ 树状数组。

第一个 $F1(x)$ 记录下端点为 $x$ 的前缀和。

第二个 $F2(x)$ 记录上端点为 $x$ 的前缀和。

如果一个矩形和其他的有左右相邻的话。

那么如果 $F1(u)-F2(d)>0$ 就表示有相邻（稍微 $YY$ 一下比较显然）。

这样开一个 bool 数组记录一下是否已经不行了 最后答案就是 bool 数组里为 $0$ 的个数。


### CODE:


```cpp
#include<bits/stdc++.h>
#define Rep(i,x,y) for(int i=x;i<y;++i)
#define For(i,x,y) for(int i=x;i<=y;++i)
using namespace std;
const int N = 3e5 + 5;
const int M = 1e6 + 5;
struct data {
	int x, u, d, id;
	bool kd;
	bool operator < (const data&b) const {
		return x < b.x || x == b.x && kd < b.kd;
	}
} a[N];
struct bit {
	int c[M];
#define lowbit(x) (x&-x)
	void insert(int x) {
		for (int i = x; i < M; i += lowbit(i))
			c[i]++;
	}
	void erase(int x) {
		for (int i = x; i < M; i += lowbit(i))
			c[i]--;
	}
	int query(int x) {
		if (!x) return 0;
		int res = 0;
		for (int i = x; i; i -= lowbit(i))
			res += c[i];
		return res;
	}
	void init() {
		memset(c, 0, sizeof(c));
	}
} T1, T2;
int cnt;
int n;
bool nok[N];
int f[M][2];
void del(int i) {
	T1.erase(a[i].d);
	T2.erase(a[i].u + 1);
	f[a[i].u][0] = 0;
	f[a[i].d][1] = 0;
}
void INS(int i) {
	f[a[i].u][0] = a[i].id;
	f[a[i].d][1] = a[i].id;
	T1.insert(a[i].d);
	T2.insert(a[i].u + 1);
}
void ins(int l, int r) {
	For(i, l, r)
	INS(i);
	For(i, l, r) {
		del(i);
		if (f[a[i].u][1]) {
			nok[a[i].id] = 1;
			nok[f[a[i].u][1]] = 1;
		}
		if (f[a[i].d][0]) {
			nok[a[i].id] = 1;
			nok[f[a[i].d][0]] = 1;
		}
		if (T1.query(a[i].u) - T2.query(a[i].d) > 0) nok[a[i].id] = 1;
		INS(i);
	}
}
int main() {
	scanf("%d", &n);
	For(i, 1, n) {
		int l, r, u, d;
		scanf("%d%d%d%d", &l, &d, &r, &u);
		++l;
		++r;
		++d;
		++u;
		a[++cnt] = (data) {
			l, u, d, i, 0
		};
		a[++cnt] = (data) {
			r, u, d, i, 1
		};
	}
	n <<= 1;
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n;) {
		int l = i;
		int r = i;
		for (; r <= n && a[r].x == a[l].x && a[r].kd == 0; ++r);
		ins(l, r - 1);
		for (; r <= n && a[r].kd == 1; ++r)
			del(r);
		i = r;
	}
	memset(f, 0, sizeof(f));
	T1.init();
	T2.init();
	for (int i = n; i;) {
		int r = i;
		int l = i;
		for (; l > 0 && a[l].x == a[r].x && a[l].kd == 1; --l);
		ins(l + 1, r);
		for (; l > 0 && a[l].kd == 0; --l) del(l);
		i = l;
	}
	int res = 0;
	For(i, 1, n / 2) if (!nok[i]) ++res;
	cout << res << endl;
	return 0;
}
```

---

## 作者：Henry_C (赞：1)

# 题目解读
$\qquad$二维平面上有 $n(1 \le n \le 2.5 × 10^4)$ 个长方形, 这些长方形可能相切，但不会重叠。求有多少个长方形和其他长方形是分离的。

# 解题思路
$\qquad$记录所有的点 $(x,y)$ ，先描平行于 $y$ 轴的边，把这些边的点排序；对于 $x$ 值相同的点,有可能出现长方形相接。点分为边的起点和终点。当处理到某个起点时,之前有某个边只有起点,终点还没出现,则当前长方形肯定与前面某个长方形相切。 

$\qquad$用双指针法： 用双指针法确定 $x$ 值相同的点的区间,然后针对这一段用BIT统计。这样只能求当前点是否和某一个正方形相接,但是不知道是和之前哪个相接。 不过没关系,我们只是这样的情况没有统计好: 某个长方形的一条边很长，在起点前其他长方形已经结束; 这个长边在延伸过程中，包裹了另外的线段, 此时这个长边我们无法统计进来。这种情况很好解决， 用字典记录这个长边的起点处理时我们进过了多少个点，这个长边的终点处理时又经过了多少个点， 如果两次点差值为 $1$ ，则中间没有别的点，否则中间包裹了新的点。 同理,对平行于 $x$ 轴的线也进行如上的操作，找出上下边相接的情况。


# 思考
$\qquad$如果正方形可以相互重叠, 那就必须用线段树统计。当然这道题也可以用线段树来做，代码量差不多。虽然有两百来行，但是要做两遍，实际上很多代码是相似的，特别是双指针法处理的一部分。这个算法的时间复杂度是 $O(n\text{log}_2n)$ ，处理次数不超过 $10^5$ 。

# 代码
```cpp
#include<iostream>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;
const int Nmax = 5e4+5; //平行边的数目 是牛棚的2倍
const int Pmax = 1e5+5; //一个长方形有4个顶点

int tou[Nmax];//某个正方形是否相接
int n;//长方形个数

struct BIT{
    int c[Nmax];
    int n; //存储1~n区间

    void init(int n){
        memset(c, 0, sizeof(c));
        this->n = n;
    }

    inline int lowBit(int x){
        return x&(-x);
    }

    void add(int x, int v){//x节点及其父节点+v
        while(x<=n){
            c[x] += v;
            x += lowBit(x);
        }
    }

    int get(int x){ //计算1~x单元的总和
        int sum = 0;
        while(x>=1){
            sum += c[x];
            x -= lowBit(x);
        }
        return sum;
    }
};
BIT bTree;

struct Node{
    int x,y,id,at; //id 长方形编号, at 0 起点, 1 终点
    Node(){};
    Node(int x, int y, int id, int at){
        this->x = x, this->y = y, this->id = id, this->at= at;
    }
};
Node nArr[Pmax];

struct Data{
    int x0,y0,x1,y1;
    Data(){};
    Data(int x0, int y0, int x1, int y1){
        this->x0=x0, this->y0=y0, this->x1=x1, this->y1=y1;
    }
} dArr[Nmax];


bool cmpXascYasc(Node a, Node b){//找平行于Y轴的线, 按Y值降序
    if(a.x == b.x){//x相同
        if(a.y == b.y)//y相同
            return a.at<b.at; //0 起点, 1 终点； x y都相同, 先起点 后终点
        else
            return a.y<b.y; //x相同时, y从小到大排列
    }
    return a.x<b.x; //x不同 按x升序排列
}

bool cmpYascXasc(Node a, Node b){//找平行于x轴的线, 按x值升序
    if(a.y == b.y){//y相同
        if(a.x == b.x)//x相同
            return a.at<b.at; //0 起点, 1 终点； x y都相同, 先起点 后终点
        else
            return a.x<b.x; //y相同时, x从小到大排列
    }
    return a.y<b.y; //y不同 按y升序排列
}

void findYparTouch(int cntN) { //找出与Y轴平行的边相接的情况
    //找到x值相同的点
    int front = 1, back = front;
    while (front <= cntN || back <= cntN) {
        while (front <= cntN && back <= cntN && nArr[front].x != nArr[back].x) {
            front++;
            back++;
        }
        while (front <= cntN && back <= cntN && nArr[front].x == nArr[back].x) {
            back++;
        }
        back--;
        if (front != back) { //此时front和back中间的点在一条线上
//            BIT bTree;
//            bTree.init(n); //标记属于某个长方形的边是否结束 1没结束, 0 结束了
            map<int, int> mStCnt;//key=id, val=cnt, 记录某个线段起点位置时 在front->back区间已经处理的点数
            map<int, int> mEnCnt;//记录某个线段终点位置时 在front->back区间已经处理的点数
            for (int i = front; i <= back; i++) {
                int idCur = nArr[i].id;
                if (nArr[i].at == 0) {//起点
                    mStCnt[idCur] = i - front + 1;
                    if (bTree.get(n) > 0)
                        tou[idCur] = 1; //有未结束的边, 当前点和其他方形相接
                    bTree.add(nArr[i].id, 1);//插入起点
                } else { //终点
                    mEnCnt[idCur] = i - front + 1;
//                    if (bTree.get(n) > 1) //除了自己的起点外,还有其他起点
//                        tou[idCur] = 1; //有未结束的边, 当前点和其他方形相接
                    bTree.add(idCur, -1);//插入终点
                }
            }

            for (auto iter: mStCnt) { //起点和终点中包含其他点, 处理长区间完全包含短区间,长区间无法被统计的情况
                int idCur = iter.first;
                if (mEnCnt[idCur] - mStCnt[idCur] > 1)
                    tou[idCur] = 1;
            }
            front = back = back + 1;
        }
    }
}

void findXparTouch(int cntN){ //找出与X轴平行的边相接的情况
    //找到x值相同的点
    int front=1, back=front;
    while(front<=cntN || back<=cntN){
        while(front<=cntN && back<=cntN && nArr[front].y != nArr[back].y){
            front++; back++;
        }
        while(front<=cntN && back<=cntN && nArr[front].y == nArr[back].y){
            back++;
        }
        back--;
        if(front != back){ //此时front和back中间的点在一条线上
            map<int, int> mStCnt;//key=id, val=cnt, 记录某个线段起点位置时 在front->back区间已经处理的点数
            map<int, int> mEnCnt;//记录某个线段终点位置时 在front->back区间已经处理的点数
            for(int i=front; i<=back; i++){
                int idCur = nArr[i].id;
                if(nArr[i].at == 0){//起点
                    mStCnt[idCur] = i-front+1;
                    if(bTree.get(n) > 0)
                        tou[idCur] = 1; //有未结束的边, 当前点和其他方形相接
                    bTree.add(nArr[i].id, 1);//插入起点
                } else{ //终点
                    mEnCnt[idCur] = i-front+1;
//                    if(bTree.get(n) > 1) //除了自己的起点外,还有其他起点
//                        tou[idCur] = 1; //有未结束的边, 当前点和其他方形相接
                    bTree.add(idCur, -1);//插入终点
                }
            }

            for(auto iter: mStCnt){ //起点和终点中包含其他点, 处理长区间完全包含短区间,长区间无法被统计的情况
                int idCur = iter.first;
                if(mEnCnt[idCur]-mStCnt[idCur]>1)
                    tou[idCur] = 1;
            }
            front = back = back + 1;
        }
    }
}

void checkYparXascYasc(){ //检查Y轴平行的线
    memset(nArr, 0 ,sizeof(Node)*Pmax);
    int cntN=0;
    for(int i=1; i<=n; i++){
        nArr[++cntN] = Node(dArr[i].x0, dArr[i].y0, i, 0);
        nArr[++cntN] = Node(dArr[i].x0, dArr[i].y1, i, 1);
        nArr[++cntN] = Node(dArr[i].x1, dArr[i].y0, i, 0);
        nArr[++cntN] = Node(dArr[i].x1, dArr[i].y1, i, 1);
    }

    sort(nArr+1, nArr+cntN+1, cmpXascYasc);
    findYparTouch(cntN);
}

void checkXparYascXasc(){//检查X轴平行的线
    memset(nArr, 0 ,sizeof(Node)*Pmax);//一个正方形 四个端点
    int cntN=0;
    for(int i=1; i<=n; i++){
        nArr[++cntN] = Node(dArr[i].x0, dArr[i].y0, i, 0);
        nArr[++cntN] = Node(dArr[i].x0, dArr[i].y1, i, 0);
        nArr[++cntN] = Node(dArr[i].x1, dArr[i].y0, i, 1);
        nArr[++cntN] = Node(dArr[i].x1, dArr[i].y1, i, 1);
    }

    sort(nArr+1, nArr+cntN+1, cmpYascXasc);
    findXparTouch(cntN);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
//    freopen("3.in", "r", stdin);
//    freopen("my.out", "w", stdout);

    cin >> n;
    for(int i=1; i<=n; i++){
        int x0,y0,x1,y1;
        cin >> x0 >> y0 >> x1 >> y1;
        dArr[i] = Data(x0,y0,x1,y1);
    }

    bTree.init(n); //标记属于某个长方形的边是否结束 1没结束, 0 结束了  BIT bTree;
    checkYparXascYasc();
    checkXparYascXasc();

    int sum = 0;
    for(int i=1; i<=n; i++){
        if(tou[i]>0) sum++;
    }
    cout << n - sum << endl;

    return 0;
}
```


---

## 作者：LCGUO (赞：1)

写在题解之前：感谢 $\text{rsc}$ 大佬的思路

---

~~尽管这只是个讲暴力的题解~~

最低档的暴力思路很简单，$O(n^2)$ 枚举矩形，如果两个矩形有相交的部分，记录这两个，最后统计一共有多少个矩形没有被记录，没有被记录的矩形个数就是可以扩展的矩形的个数：

```cpp
for(rint i=1;i<=n;++i)
    for(rint j=1;j<i;++j)
        if(check(i,j)) vis[i]=vis[j]=1;
for(rint i=1;i<=n;++i) if(!vis[i])ans++;
```

$\operatorname{check}$ 函数用来判断两个矩形是否相交

---

下面就是优化后的暴力了。

我们先把他按照上边界为第一关键字，左边界为第二关键字，排一遍序。

如果当时矩形 $j$ 的上边界大于矩形 $i$ 的下边界的话，证明 $j$ 以后的矩形都不会与矩形 $i$ 相交，即可以退出第二重循环，这样在一定程度上减小了复杂度，然后只T了一个点。

最后开一下 O2 优化，就可以 AC 了αωα

---

代码如下：

```cpp
#include<bits/stdc++.h>
#define rint register int 
using namespace std;
inline int read(){
    int s=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=0;c=getchar();}
    while(c>='0'&&c<='9')s=(s<<1)+(s<<3)+c-48,c=getchar();
    return f?s:-s;
}
struct hhd{
    int lx,ly,rx,ry;
    friend bool operator < (hhd a,hhd b){
        return a.lx==b.lx?a.ly<b.ly:a.lx<b.lx;
    }
}a[25010];
int n,ans,vis[25010];
int main(){
    n=read();
    for(rint i=1;i<=n;++i){
        a[i].lx=read(); a[i].ly=read();
        a[i].rx=read(); a[i].ry=read();
    }
    sort(a+1,a+1+n);
    for(rint i=1;i<=n;++i)
        for(rint j=i+1;j<=n;++j){
            if(a[j].lx>a[i].rx) break;
            if(a[j].ly>a[i].ry) continue;
            if(a[i].lx==a[j].rx||
            (a[i].ry==a[j].ly&&a[j].lx<=a[i].rx&&a[j].rx>=a[i].lx)||
            (a[i].ly==a[j].ry&&a[j].lx<=a[i].rx&&a[j].rx>=a[i].lx)||
            (a[i].rx==a[j].lx&&a[j].ly<=a[i].ry&&a[j].ry>=a[i].ly)) vis[i]=vis[j]=1;
    }
    for(rint i=1;i<=n;++i)
        if(!vis[i]) ++ans;
    printf("%d",ans);
    return 0;
}
```

码风有点丑，凑合着看吧/kk

---

## 作者：ycy1124 (赞：1)

### 题意
在一个直角坐标系上有 $n$ 个互不重叠矩形，求有多少个矩形与其他所有矩形的边没有公共部分（公共角也算）。
### 思路
考虑朴素暴力，对于每个矩形暴力枚举每个矩形的每一条边是否能匹配上其余矩形的每一条边。

此时我们发现，每一个矩形的顶边只能匹配上其他矩形的底边。于是我们可以将每一个矩形的顶边存到他顶边的 $y$ 坐标的 vector 里面。然后我们按每个顶边的左侧端点排个序，然后对于每个矩形的底边枚举他底边的 $y$ 坐标的 vector 与其匹配。至于左侧边则同理。剪枝，当你枚举到的顶边的左侧端点大于当前边的右侧端点就可以停止枚举退出。

此时的复杂度最坏可以达到 $\mathcal{O}( n^2 )$，但是在你谷评测机与剪枝的帮助下还是可以顺利通过。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node{
	int l,r,id;
};
int ans,x[25005][2],y[25005][2];
vector<Node>a[1000005];
bool bj[25005];
inline bool cmp(Node x1,Node x2){
	return x1.l<x2.l;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n;
	cin>>n;
	ans=n;
	for(int i=1;i<=n;i++){
		cin>>x[i][0]>>y[i][0]>>x[i][1]>>y[i][1]; 
	}
	for(int i=1;i<=n;i++){
		a[y[i][0]].push_back({x[i][0],x[i][1],i});
	}
	for(int i=1;i<=1000000;i++){
		sort(a[i].begin(),a[i].end(),cmp);
	}
	for(int i=1;i<=n;i++){
		for(auto it:a[y[i][1]]){
			if(it.l>x[i][1]){
				break;
			}
			if(it.id==i){
				continue;
			}
			if(it.r>=x[i][0]){
				if(!bj[i]){
					bj[i]=1;
					ans--;
				}
				if(!bj[it.id]){
					bj[it.id]=1;
					ans--;
				}
			}
		}
	}
	for(int i=1;i<=1000000;i++){
		a[i].clear();
	} 
	for(int i=1;i<=n;i++){
		a[x[i][0]].push_back({y[i][0],y[i][1],i});
	}
	for(int i=1;i<=1000000;i++){
		sort(a[i].begin(),a[i].end(),cmp);
	}
	for(int i=1;i<=n;i++){
		for(auto it:a[x[i][1]]){
			if(it.l>y[i][1]){
				break;
			}
			if(it.id==i){
				continue;
			}
			if(it.r>=y[i][0]){
				if(!bj[i]){
					bj[i]=1;
					ans--;
				}
				if(!bj[it.id]){
					bj[it.id]=1;
					ans--;
				}
			}
		}
	}
	cout<<ans;
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/193259045)。

---

