# [ABC218D] Rectangles

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc218/tasks/abc218_d

$ 2 $ 次元平面上に $ N $ 個の相異なる点があり、$ 1,2,\ldots\ ,N $ の番号がついています。点 $ i\,(1\ \leq\ i\ \leq\ N) $ の座標は $ (x_i,y_i) $ です。

これらの点のうち $ 4 $ つを頂点とし、全ての辺が $ x $ 軸または $ y $ 軸に平行であるような長方形はいくつありますか？

## 说明/提示

### 制約

- $ 4\ \leq\ N\ \leq\ 2000 $
- $ 0\ \leq\ x_i,\ y_i\ \leq\ 10^9 $
- $ (x_i,y_i)\ \neq\ (x_j,y_j) $ $ (i\ \neq\ j) $
- 入力は全て整数である。

### Sample Explanation 1

点 $ 1 $ 、点 $ 2 $ 、点 $ 3 $ 、点 $ 4 $ を頂点とする長方形、 点 $ 1 $ 、点 $ 2 $ 、点 $ 5 $ 、点 $ 6 $ を頂点とする長方形、 点 $ 3 $ 、点 $ 4 $ 、点 $ 5 $ 、点 $ 6 $ を頂点とする長方形 の合計 $ 3 $ つです。

## 样例 #1

### 输入

```
6
0 0
0 1
1 0
1 1
2 0
2 1```

### 输出

```
3```

## 样例 #2

### 输入

```
4
0 1
1 2
2 3
3 4```

### 输出

```
0```

## 样例 #3

### 输入

```
7
0 1
1 0
2 0
2 1
2 2
3 0
3 2```

### 输出

```
1```

# 题解

## 作者：So_noSlack (赞：10)

[洛谷链接](https://www.luogu.com.cn/problem/AT_abc218_d)&[Atcoder](https://atcoder.jp/contests/abc218/tasks/abc218_d)

本篇题解为此题较**简单做法**及**较少码量**，并且码风优良，请放心阅读。

## 题目简述

给定一个平面内的 $N$ 个点的坐标，求这 $N$ 个点中选 $4$ 个点可构成正方形的**方案数**。

**注**：构成的正方形的边需**平行于** $x$ 轴或 $y$ 轴。

例如下图就不符合要求，则不考虑这种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/0rcryvyg.png)

## 思路

此题基本纯**思维题**，算法考的不多。

一看数据范围，$4 \le N \le 2000$？既然**数据范围这么小**，那么 $O(N^2)$ 的时间复杂度是**能过的**，但如果**暴力枚举** $4$ 个点的话时间复杂度是 $O(N^4)$，**时间复杂度爆炸**啊。

所以还是需要一点**小优化**的，本蒟蒻一开始只想到了枚举 $3$ 个点，接着**判断另一个点是否存在**，但这个想法的时间复杂度是 $O(N^3)$，还是会**超时**。

那么我们沿袭这个思想就可以想到，直接 $N^2$ 枚举 $2$ 的点，接着**判断另外两个点是否存在**即可，但这枚举的两个点**需为两个对角的点**，这里我们枚举左上和右下两个点。

接着只需要解决**如何判断另外两个点是否存在**的问题即可，很容易想到用 map 容器去储存**点是否存在**的信息。

即可推出**判断的语句**：$mp_{x_i,y_i}$ 且 $mp_{x_j,y_j}$ 且 $mp_{x_i,y_j}$ 且 $mp_{x_j,y_i}$ 且 $x_i<x_j$ 且 $y_i<y_j$。

map 容器的初始化直接在输入时**初始化**即可。

经过以上分析，即可得出代码：

```cpp
#include<iostream>
#include<map>
using namespace std;

int n, x[2005], y[2005];
long long ans = 0; // 开 long long 好习惯
map<int, map<int, bool> > mp; // 不要写成 >>，中间要有空格

int main() {
    cin >> n; // 输入
    for(int i = 1; i <= n; i ++) {
        cin >> x[i] >> y[i]; // 输入
        mp[x[i]][y[i]] = true; // 初始化处理
    }
    for(int i = 1; i <= n; i ++) {
        for(int j = 1; j <= n; j ++) {
            if(i == j) continue; // 特判 i = j 的情况
            if(mp[x[i]][y[i]] && mp[x[j]][y[j]] && mp[x[i]][y[j]] && mp[x[j]][y[i]] && x[i] < x[j] && y[i] < y[j]) ans ++; // 满足要求 ans++
        }
    }
    cout << ans << endl; // 输出，记得换行
    return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/117160948)

$$\text{The End!!}$$

---

## 作者：Hope888 (赞：3)

这道题是 2021CSP-J 第一轮完善程序第二题原题，CCF 的代码甚至跑到了最优解第一页。
# 思路
一个矩形只需它的两个相对的点确定，如果两个相对的点的坐标分别为 $(x1,y1),(x2,y2)$，那么另外两个点的坐标即为 $(x1,y2),(x2,y1)$，只需查找这两个点是否存在即可。

可以先将矩形按照坐标大小排序（详见 `cmp` 函数），就可以使用二分查找优化寻找其他两个点的过程。
# 代码
这里我直接使用了 CCF 改过码风的代码捏，有不理解的可以 bdfs。
```cpp
#include<iostream>
using namespace std;
struct point
{
	int x,y,id;
};
bool equals(point a,point b)
{
	return a.x==b.x&&a.y==b.y;
}
bool cmp(point a,point b)
{
	return a.x!=b.x?a.x<b.x:a.y<b.y;
}
void sort(point A[],int n)
{
	for(int i=0;i<n;i++)
		for(int j=1;j<n;j++)
			if(cmp(A[j],A[j-1]))
			{
				point t=A[j];
				A[j]=A[j-1];
				A[j-1]=t;
			}
}
int unique(point A[],int n)
{
	int t=0;
	for(int i=0;i<n;i++)
		if(t==0||!equals(A[i],A[t-1]))
			A[t++]=A[i];
	return t;
}
bool binary_search(point A[],int n,int x,int y)
{
	point p;
	p.x=x;
	p.y=y;
	p.id=n;
	int a=0,b=n-1;
	while(a<b)
	{
		int mid=(a+b)>>1;
		if(cmp(A[mid],p))a=mid+1;
		else b=mid;
	}
	return equals(A[a],p);
}
const int MAXN=2000;
point A[MAXN];
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>A[i].x>>A[i].y;
		A[i].id=i;
	}
	sort(A,n);
	n=unique(A,n);
	int ans=0;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(A[i].x<A[j].x&&A[i].y<A[j].y&&binary_search(A,n,A[i].x,A[j].y)&&binary_search(A,n,A[j].x,A[i].y))
			{
				ans++;
			}
	cout<<ans<<endl;
}
```

---

## 作者：tbdsh (赞：1)

# 题意简述
[题目传送门](/problem/at_abc218_d)

[更好的阅读体验](/blog/tianbiandeshenghuo11/solution-at-abc218-d)

给你 $n$ 个不同的点的坐标，请你求出这 $n$ 个点中任意四个点构成的矩形中有多少个矩形是长方形。
# 分析
首先考虑暴力做法。

不难想到可以暴力枚举四个点，判断是否构成长方形。

具体实现的核心代码如下：
```cpp
bool ccheck(int x, int y){
  return a[x].x == a[y].x || a[x].y == a[y].y;
}
bool check(int a, int b, int c, int d){
  return ccheck(a, b) && ccheck(c, d) && ccheck(a, c) && ccheck(b, d);
}

for (int i = 1; i <= n; i++){
    for (int j = i + 1; j <= n; j++){
      for (int k = j + 1; k <= n; k++){
        for (int l = k + 1; l <= n; l++){
          ans += check(i, j, k, l);
        }
      }
    }
  }
```
但是这样很显然会超时，时间复杂度达到 $O(n^4)$，所以我们要考虑优化。

我们可以发现：对于一个长方形，它的同一边的点的坐标 $(x,y)$ 肯定有一个是相同的。下借 @[zhangzhengyan0831](/user/715244) 的图片进行描述。

![](https://cdn.luogu.com.cn/upload/image_hosting/bovpcrbk.png)

可以发现：长方形的四个点的坐标实际只有四个：$x_1,y_1,x_2,y_2$。那么，我们就可以枚举两个点的坐标 $(x_1,y_1)$ 和 $(x_2,y_2)$，然后判断点 $(x_1,y_2)$ 和点 $(x_2,y_1)$ 是否存在即可。

但是，我们要怎样判断呢？

这时，我们就可以借助 `map` 直接判断一个点是否存在。

**但是**，这里还有一个细节。我们要避免重复枚举。所以还需要保证枚举的两个点的坐标满足 $x_1<x_2$ 和 $y_1<y_2$ 才能累加答案。

时间复杂度：$O(n^2\times \log n)$。

空间复杂度：$O(n^2)$。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
int n, ans;
map<int, map<int, bool>> b;
struct Node{
  int x, y;
} a[2005];
int main(){
  cin >> n;
  for (int i = 1; i <= n; i++){
    cin >> a[i].x >> a[i].y;
    b[a[i].x][a[i].y] = 1;
  }
  for (int i = 1; i <= n; i++){
    for (int j = 1; j <= n; j++){
      ans += a[i].x < a[j].x && a[i].y < a[j].y && b[a[i].x][a[j].y] && b[a[j].x][a[i].y];
    }
  }
  cout << ans;
  return 0;
}
```

---

## 作者：Crasole (赞：0)

###### ~~此题好像有原题(~~

## 题意

给出 $N$ 个二维平面上的点，用 $x_i , y_i  ( 1 \le i \le n)$ 表示。

问：一共有多少个点能组成矩形，且四条边分别平行与 $x$ 轴和 $y$ 轴。

## 思路

首先，满足题目要求的矩形肯定如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/6vry8ucd.png)

观察图片，我们可以发现，当左上角和右下角确定的时候，另外两个点也是确认的。假设左上角是 $(x_i , y_i)$，右下角是 $(x_j , y_j)$，那么右上角就是 $(x_i , y_j)$，左下角就是 $(x_j , y_i)$。

我们可以使用结构体来存储每个点，再按 $x$ 轴和 $y$ 轴来从小到大排序。

接着，我们就可以枚举左上角点 $a_i$ 和右下角点 $a_j$，首先判断 $a_i$ 是否小于 $a_j$，如果不成立，就不用这两个点。

然后再计算出右上角和左下角，在判断右上角和左下角是否真实存在，直接扫一遍可能会超时，所以我们可以使用二分。如果右上角和左下角是真实存在的，那么 `ans++`。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct point{
	int x,y;
}a[2010];
int n;
bool cmp(point a,point b){//如果x相等就比y，否则直接比x
	return a.x!=b.x?a.x<b.x:a.y<b.y;
}
bool cmp2(int i,int j){//判断点i是否小于点j
	return a[i].x<a[j].x&&a[i].y<a[j].y;
}
bool unq(point u,point v){//判断两个点是否相同
	return u.x==v.x&&u.y==v.y;
}
bool check(int x,int y){//二分出一个点
	point u;
	u.x=x,u.y=y;
	int l=1,r=n,mid;
	while(l<=r){
		mid=(l+r)>>1;
		if(cmp(a[mid],u))
			l=mid+1;
		else r=mid-1;
	}
   //二分出的点可能只是与目标的点相近，因为这个点u可能不存在，所以要判断一下
	return unq(u,a[l]);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].x>>a[i].y;
	sort(a+1,a+n+1,cmp);
	int ans=0;
   //枚举点i和点j
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(cmp2(i,j)&&check(a[i].x,a[j].y)&&check(a[j].x,a[i].y))
				ans++;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Luxingguang (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc218_d)

## 一、简述题意
------------
在一个 $2$ 维的平面上有 $N$ 个不同的点，
编号为 $1,2,\ldots\,N$。
点 $i\,(1\ \leq\ i\ \leq\ N)$ 的坐标是 $(x_i,y_i)$。有多少个矩形，使这些点中的 $4$ 个点为顶点，所有的边都平行于 $x$ 或 $y$ 轴？
## 二、思路分析
------------
### $O(N^4)$ 做法
四重 for 循环枚举所有的端点，但是 $N = 2 \times 10^3$，所以 $N^4 = 1.6 \times 10^{13}$，会超时。

### $O(N^3\times (\log N)^2)$
三重 for 循环枚举 $3$ 个端点，再用二维 map 存储所有端点，但是 $N = 2 \times 10^3$，所以 $N^3\times (\log N)^2 = 8 \times 10^9 \times 10^2 =8 \times 10^{11}$，会超时。

### $O(N^2\times (\log N)^2)$

由于我们只需要两个端点就可以确定矩形的位置，所以用二维 map 确定能否形成一个矩形，$N^2\times (\log N)^2 = 4 \times 10^6 \times 10^2 =4 \times 10^8$。

## 三、代码实现
------------
```cpp
#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
int n,x[2005],y[2005],ans;
map<int,map<int,int> > m;
map<int,int> l;
int p;
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d%d",&x[i],&y[i]);
		if(l[x[i]]==1) p=1;
		l[x[i]]=1;
		m[x[i]][y[i]]=1;
	}
	if(p==0){
		puts("0");
		return 0;
	}//无交点时无解
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(i==j) continue;
			if(m[x[i]][y[i]]&&m[x[j]][y[j]]&&m[x[i]][y[j]]&&m[x[j]][y[i]]&&x[i]<x[j]&&y[i]<y[j]) {
				ans++;
			}
		}
	}printf("%d",ans);
	return 0;
}


```


---

## 作者：xxxalq (赞：0)

### [原题链接](https://www.luogu.com.cn/problem/AT_abc218_d)

## 题意简述：

给定 $n$ 个点的坐标，求有多少个矩形，使这些点中的 $4$ 个点为顶点，所有的边都平行于 $x$ 或 $y$ 轴。

## 思路分析：

如下图所示：

![xxxalq](https://cdn.luogu.com.cn/upload/image_hosting/ma8hz38t.png)

对于图 $A,B,C,D$ 四个点，当且仅当：

$$x_A=x_D,x_B=x_c,y_A=y_B,y_C=y_D$$

因为 $ (x_i,y_i)\ \neq\ (x_j,y_j) $ $ (i\ \neq\ j) $，所以可以通过 pair 或结构体类型的 map 或桶存储每个 $xy$ 坐标是否有点，$0$ 表示没有，$1$ 表示有，$-1$ 表示已经被访问过。

接着进行标记，$O(n^2)$ 的时间复杂度 $(n\le 2000)$ 枚举所有点，对于每个点，枚举剩下所有点，如果符合条件。就把这个点和另外 $3$ 个点都标记成 $-1$，且答案加一，下次就不重复访问了。

经过以上分析和推理，很容易即可得出代码了。

---

## 作者：zhaomumu1218 (赞：0)

### 题意简述
给 $n$ 个点，问能围成多少个长方形。
### 思路
可以暴力枚举 $4$ 个点的坐标，但是会超时。       
不过虽然枚举 $4$ 个点不行，但 $2$ 个点可行。       
我们枚举长方形的左上和右下 $2$ 个点，再判断这个正方形是否存在。具体代码如下：
```
if(s[{x[i],y[j]}]&&s[{x[j],y[i]}]&&x[i]<x[j]&&y[i]<y[j]) ans++;
```
这里 $s$ 是一个 map，如果 $s_{x,y}$ 是 $1$，那说明存在坐标为 $x,y$ 的点。
### 代码
```
#include <bits/stdc++.h>
using namespace std;
int x[2010],y[2010],ans;
map<pair<int,int>,bool> s;
int main() {
    int n;
    scanf("%d", &n);
    for (int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]),s[{x[i],y[i]}]=1;
    for (int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(s[{x[i],y[j]}]&&s[{ x[j], y[i] }]&&x[i]<x[j]&&y[i]<y[j])
                ans++;
    printf("%d", ans);
    return 0;
}
```

---

## 作者：Hog_Dawa_IOI (赞：0)

看到 $n \leq 2000$ 的数据范围，好东西，$O(n^2)$ 走起。   
首先给每一个点排序，以横坐标为第一关键字升序，以纵坐标为第二关键字升序，排序后每个点便呈现一种从上到下、从左往右的顺序。    
接着枚举一个长方形的左上角的点和右下角的点，或者右上角的点和左下角的点。      
对于两个可能作为一个长方形左上角和右下角的点 $(x1,y1)$ 和 $(x2,y2)$，它们需要满足：
- $x1<x2,y1<y2$。
- 给定的点中存在 $(x1,y2),(x2,y1)$ 这两个点。

对于两个可能作为一个长方形右上角和左下角的点 $(x1,y1)$ 和 $(x2,y2)$，它们需要满足：
- $x1<x2,y1>y2$。
- 给定的点中存在 $(x1,y2),(x2,y1)$ 这两个点。     

对于每种情况的第二条限制，只需要用一个 map，把每个点的横坐标和纵坐标做成一个 pair 放进 map 里面，查询的时候到 map 里面查找即可。   
最后把所有统计的情况算出来，除以二输出，就做完了。    
代码：
```cpp
#include<map>
#include<cstdio>
#include<algorithm>
using namespace std;
map<pair<int,int>,int>point;
int n,ans;bool cmp(sss a,sss b){return a.x<b.x||a.x==b.x&&a.y<b.y;}
int main()
{
    scanf("%d", &n);
    for(int i=1;i<=n;i++) scanf("%d%d",&s[i].x,&s[i].y),
    point[make_pair(s[i].x,s[i].y)]=1;
    sort(s+1,s+n+1,cmp);
    for(int i=1;i<n;i++) for(int j=i+1;j<=n;j++)
    if(s[i].x!=s[j].x&&s[i].y!=s[j].y
    &&point[make_pair(s[i].x,s[j].y)]==1
    &&point[make_pair(s[j].x,s[i].y)]==1)
    ans++;
    printf("%d", ans/2);
}
```

---

## 作者：DengDuck (赞：0)

为了实现 $O(n^2)$ 级别的快速算法，我们可以考虑先处理出所有线段，这些线段全部平行于 y 轴，也就是 $x_i=x_j$。

同时我们对这些线段进行归纳，能构成一个矩形的边 $(y_i,y_{i'})$ 与 $(y_j,y_{j'})$ 应该满足 $y_i=y_{i'},y_j=y_{j'}$，因此我们以 $y_i,y_j$ 来对线段 $(i,j)$ 归纳。

最后对于一类线段直接计数一手即可。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=2005;
struct node
{
	LL x,y;
}a[N];
LL n,ans;
map<pair<LL,LL>,LL>ma;
bool cmp(node x,node y)
{
	if(x.x==y.x)return x.y<y.y;
	return x.x<y.x;
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&a[i].x,&a[i].y);
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i-1;j++)
		{
			if(a[i].x==a[j].x)
			{
				ma[{a[i].y,a[j].y}]++;
			}
		}
	}
	for(pair<pair<LL,LL>,LL> i:ma)
	{
		LL t=i.second;
		ans+=t*(t-1)/2;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：_zzzzzzy_ (赞：0)

# 思路
知道了相对的两个点就能够构造出来整个长方形，我们设相对的两个点的坐标为 $(x1,y1),(x2,y2)$，那么剩下的两个节点的坐标就是 $(x1,y2),(x2,y1)$，最后我们暴力枚举两个点，在判断另外的两个点可以用一个结构体来表示坐标，用哈希表记录下来这个坐标，最后判断的时候用哈希表判断就可以了。

![](https://cdn.luogu.com.cn/upload/image_hosting/bovpcrbk.png)

像这个长方形，只用枚举用蓝色标出来的点就可以确定下来这一个长方形，为了防止重复枚举这一个长方形，我们可以在枚举的时候强制枚举的第一个点在第二个点的左上方。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define x first
#define y second
const int maxn=1000005;
pair<int,int>a[maxn];
map<pair<int,int>,int>mp;
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		int x,y;
		cin>>x>>y;
		a[i]={x,y};
		mp[{x,y}]=1;
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[i].x<a[j].x&&a[i].y<a[j].y&&mp[{a[i].x,a[j].y}]&&mp[{a[j].x,a[i].y}]){
				ans++;
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：loser_seele (赞：0)

很显然，如果我们知道一个矩形的左下角和右下角，则剩下两个点的坐标也可以求出。

于是暴力枚举左下角和右下角的坐标，注意要满足左下角的 $ x,y $ 坐标严格小于右上角的，然后判断剩下两个角的坐标即可。

用 STL 的 unordered_map 可以做到 $ \mathcal{O}(1) $ 查询，但是 unordered_map 并不支持 pair<int,int> 的哈希，于是需要手写哈希，注意溢出问题即可。

时间复杂度 $ \mathcal{O}(n^2) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
#define int unsigned long long
using namespace std;
const int BASE=2000000000;
int x[2020],y[2020],n;
unordered_map<int,bool>p;
int hasher(int x,int y)
{
	return x*BASE+y;
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>x[i]>>y[i],p[hasher(x[i],y[i])]=1;
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(x[i]<x[j]&&y[i]<y[j]&&p[hasher(x[i],y[j])]&&p[hasher(x[j],y[i])])
				ans++;
	cout<<ans;
}
```


---

