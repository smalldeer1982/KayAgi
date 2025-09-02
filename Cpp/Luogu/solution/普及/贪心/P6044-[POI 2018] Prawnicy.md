# [POI 2018] Prawnicy

## 题目背景

**题目译自 [POI XXV - I etap](https://sio2.mimuw.edu.pl/c/oi25-1/dashboard/) 「[Prawnicy](https://sio2.mimuw.edu.pl/c/oi25-1/p/pra/)」**

## 题目描述

“Bajtazar 父子”律师事务所刚刚收到一位非常重要的客户的订单。案件严重、紧急，需要与律师事务所的律师举行会议。每个律师都有一段固定的空闲时间可以参加会议。你应该选择这样的 $k$ 位律师，以便召开会议的时间（即他们都空闲的时间）尽可能长。

[简要题意](https://www.luogu.com.cn/problem/U252799)

## 说明/提示

#### 样例解释

三位律师会议可能的最大时长是 $4$。编号为 $1$、$2$ 和 $4$ 的律师可以参加，持续时间从 $4$ 到 $8$。另一个同样好的方案是让编号为 $2$、$4$ 和 $5$ 的律师参加，持续时间从 $5$ 到 $9$。

![](https://cdn.luogu.com.cn/upload/image_hosting/187yuqy1.png)

#### 附加样例

参见 `pra/pra*.in` 和 `pra/pra*.out`：

- 附加样例 $1$：$1$ 组数据，$n=7$，$k=3$，且选择律师的方案有两种。

- 附加样例 $2$：$1$ 组数据，$n=k=1000$，$a_i=i$，$b_i=10^6+i$；

- 附加样例 $3$：$1$ 组数据，$n=1000$，$k=1$，$a_i=2i-1$，$b_i=2i$；

#### 数据范围与提示

测试集分为以下子任务。每个子任务的测试由一个或多个单独的测试组组成。

| Subtask # | 额外限制                         | 分值  |
|:---------:|:----------------------------:|:---:|
| $1$         | $n\le 20$       | $20$  |
| $2$         | $n\le 300$，$a_i,b_i\le 300$      | $15$  |
| $3$         | $n\le 5000$       | $15$  |
| $4$         | $n\le 10^6$，$k\in \{1,n\}$       | $15$  |
| $5$         | $n\le 10^6$       | $35$  |

如果你的程序在第一行输出了正确的时长，但其余的输出是错误的，那么你将获得 $40\%$ 的分数。

## 样例 #1

### 输入

```
6 3
3 8
4 12
2 6
1 10
5 9
11 12
```

### 输出

```
4
1 2 4
```

# 题解

## 作者：longlinyu7 (赞：10)

# 分析题意
[简要题意](https://www.luogu.com.cn/problem/U252799)

即有 $n$ 条线段，选出 $k$ 条线段，使得他们的交集长度最大并输出任意一种方案。

易知最终得到的区间是**某一线段的左端点**与**另一线段的右端点**。
# 解题思路

### 贪心  
若先判断左端点，那将左端点按值从小到大排序，然后从前遍历即可。
### 优先队列
剩下只用判断右端点，需要维护 $k$ 条线段的右端点值，那么用优先队列，可以比较方便的得出。针对该题，我们使用小根堆。

### 如何获得答案
维护合法右端点减去左端点的最大值，最后输出即可。

对于线段的编号，需要顺带维护最大长度的左端点与右端点，记为 $l$ 和 $r$。我们重新遍历一边，找到左端点小于等于 $l$ 和右端点大于等于 $r$ 的线段，输出即可。

# 代码
```
#include <bits/stdc++.h>
using namespace std;
const int N=1000005;
int n,k,tail,head,tim;
struct node{int x,y,num;}a[N];
priority_queue<int,vector<int >,greater<int > >r;//小根堆
bool cmp(node a,node b){
    return a.x==b.x?(a.y<b.y):(a.x<b.x);
}
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i].x>>a[i].y;
        a[i].num=i;
    }
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++){
        r.push(a[i].y);
        while(r.size() >k){
            r.pop();
        }
        if(r.size()==k){ //如果合法
            if(tim<(r.top()-a[i].x)){//替换
                tail=r.top();head=a[i].x;
                tim=tail-head;
            }
        }
    }
    cout<<tim<<endl;
    for(int i=1;i<=n;i++){//重新遍历
        if(a[i].x<=head&&a[i].y>=tail&&k){
            k--;
            cout<<a[i].num<<" ";
        }
    }
    return 0;
}
```

---

## 作者：Je_son (赞：4)

[**题目传送门**](https://www.luogu.com.cn/problem/P6044)
- - -
# 题目大意
现有 $n$ 条线段，第 $i$ 条线段左端点为 $a_i$，右端点为 $b_i$，选取其中的 $k$ 条线段，使它们共同的部分（交集）最长。
# 做题思路

![](https://cdn.luogu.com.cn/upload/image_hosting/187yuqy1.png)

从这张图中我们可以发现，$k$ 条边的交集的长度满足：
1.  头是我们选择的 $k$ 条边中的**最靠右的左端点**；
2.  尾是 $k$ 条边中**最靠左的右端点**。

我们考虑对每条边的左端点进行升序排序，使第 $i$ 条边的左端点一定比前面的边的左端点更靠右（或等于），满足条件1，然后用一个小根堆维护当前 $k$ 条边中最小的右端点，在 小根堆长度 $> k$ 时，删除小根堆中最小右端点直到 小根堆长度 $= k$，删除结束后如果目前结果比先前更优（长度更长），则记录交集的左端点和右端点。最后输出交集最长的 $k$ 条边即可。
# 代码实现
```
#include <bits/stdc++.h>
#define PII pair <int, int>
#define LL long long
#define DB double

namespace FastIO
{
	inline void read(int MOD, int &ret){
		char ch = getchar();int ngtv = 1; ret = 0;
		if(MOD == 0) {while(ch < '0' || ch > '9'){if(ch == '-') ngtv = -1;ch = getchar();}while(ch >= '0' && ch <= '9'){ret = ret * 10 + (ch - '0');ch = getchar();}}
		else {while(ch < '0' || ch > '9'){if(ch == '-') ngtv = -1;ch = getchar();}while(ch >= '0' && ch <= '9')
		{ret = (ret * 10 % MOD + (ch - '0') % MOD) % MOD;ch = getchar();} }
	}
	inline char cread(){char ch;while(ch == ' ' || ch == '\n' || ch == '\r' || ch == 0) ch = getchar();ch = getchar();return ch;}
	// 快读
}
using namespace FastIO;
using namespace std;

const int N = 1e6 + 10;
int n, k, l, r;
int dp[N];
priority_queue <int, vector <int> , greater <int> > q;
// 小根堆

struct Node
{
	int l, r, num;
	// 分别记录一条边的左端点、右端点和编号
}A[N];

bool cmp(Node x, Node y)
{
	return x.l < y.l;
}

signed main()
{
	read(0, n), read(0, k);
	
	for(int i = 1; i <= n; i ++ )
	{
		read(0, A[i].l);
		read(0, A[i].r);
		A[i].num = i;
	}
	
	// 排序
	sort(A + 1, A + n + 1, cmp);
	
	for(int i = 1; i <= n; i ++ )
	{
		// 右端点入队
		q.push(A[i].r);
		while(q.size() > k)
			q.pop();
		// 有更优解
		if(q.size() == k && q.top() - A[i].l > r - l)
		{
			l = A[i].l;
			r = q.top();
		}
	}
	
	printf("%d\n", r - l);
	// 最长交集
	for(int i = 1; i <= n && k; i ++ )
	{
		if(A[i].l <= l && A[i].r >= r)
		{
			k -- ;
			// 只输出 k 条边
			printf("%d ", A[i].num);
		}
	}
	puts("");
	// 养成换行好习惯
	
	return 0;
}

```

---

## 作者：JackMerryYoung (赞：3)

# 前言

![](https://cdn.luogu.com.cn/upload/image_hosting/i6pks571.png)

~~SG 老师日常~~

# 正文

题意就是：有 $N$ 条线段，选出 $K$ 条线段，使得他们的交集长度最大并输出任意一种方案。

初步看来，大概就是个很典的题。很 naive 的想法就是直接上值域做法的尺取，但是发现会寄，不妨思考一下贪心。

我们发现从左到右枚举起始点，然后去删掉终止点靠后的线段，这样一定不劣。

于是乎我们先以左端点为第一关键字，右端点为第二关键字排序，然后把线段依次扔进大根堆里，使堆保持在 $K$ 的大小，这样交集一定能取到最长。

其实这个做法感觉也挺类似尺取的，无非是离散化了一下？

# 代码

``` cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define rint register ll

struct lawyer {
    ll a, b, num;
} arr[1000005];

ll N, K;
priority_queue<ll, vector<ll>, greater<ll>> heap;

bool operator <(lawyer la, lawyer lb) 
{
    return (la.a == lb.a) ? (la.b < lb.b) : (la.a < lb.a);
}

ll ansl, ansr;

signed main()
{
    cin >> N >> K;
    for(ll i = 1; i <= N; ++ i)
    {
        cin >> arr[i].a >> arr[i].b;
        arr[i].num = i;
    }

    sort(arr + 1, arr + N + 1);
    for(ll i = 1; i <= N; ++ i)
    {
        heap.push(arr[i].b);
        while(heap.size() > K) heap.pop();
        if(heap.size() == K && (heap.top() - arr[i].a) > (ansr - ansl))
        {
            ansl = arr[i].a;
            ansr = heap.top();
        }
    }

    cout << ansr - ansl << endl;
    ll cnt = 0;
    for(ll i = 1; i <= N; ++ i)
    {
        if(arr[i].a <= ansl && arr[i].b >= ansr && cnt < K)
        {
            ++ cnt;
            cout << arr[i].num << ' ';
        }
    }

    return 0;
}
```

# 后言

关于这道题的 Ex 有趣的讨论：https://www.luogu.com.cn/discuss/560582

---

## 作者：cdxxx04 (赞：2)

# 题解：P6044 [POI2018] Prawnicy

**[题目传送门](https://www.luogu.com.cn/problem/P6044)**

---

## 简要题意
定义一个区间 $(l,r)$ 的长度为 $r-l$ ，空区间的长度为 $0$。

给定数轴上 $n$ 个区间，请选择其中恰好 $k$ 个区间，使得交集的长度最大。

（摘自 [U252799 [POI2018]Prawnicy](https://www.luogu.com.cn/problem/U252799) ）
## 解题思路

这道题是一个很明显的贪心。显然，合法区间肯定是从一个端点开始到一个端点结束。证明：

>因为如果它不是从端点开始结束必定可以延伸到一条线段的端点，如图：
>
>![](https://s3.bmp.ovh/imgs/2024/08/15/d08a4aebc7114641.png)

所以我们只需要从小到大枚举左端点，找到右端点求差值就行了。

怎么枚举呢？我们可以那一个堆或者优先队列维护一个关于线段的三元组，左端点为第一项，右端点为第二项，序号最后一项（没有序号线段放入队列是顺序会变，不方便输出）。然后把线段扔入，计算合法法的最大差值，大小为超过 $K$ 时，把左端点最小的出堆。为什么是最小的呢？证明：

>我们可以分类讨论
>
>* 线段的右端点不是最大\
>  在这种情况下，由于还有其他线段的右端点比它大，它无法做出更大的贡献，所以加上不会导致结果更优。
>  
>* 线段的右端点是最大的\
>  在这种情况下，其他的线段一定包含在它中（因为它左端点最小右端点最大），长度取决于其它线段，所以加上不会导致结果更优。
>
>![](https://s3.bmp.ovh/imgs/2024/08/15/cdfccf2607a56376.png)

在比较差值时，要记录起点和终点，方便输出选取的是那几条线段。

## AC代码


```cpp
#include<bits/stdc++.h>
using namespace std;

int n,k;
const int N=1e6+5;
struct node{
	int beginn,endd,id;
	//左右端点和 ID 。
}a[N];
void in(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i].beginn>>a[i].endd,a[i].id=i;
}//输入线段，由于顺序会改变所以记录ID。

bool cmp(node x,node y){
	if(x.beginn!=y.beginn)
		return x.beginn<y.beginn;
	return x.endd<y.endd;
}//排序，左端点小的在前。相同时右端点小的在前。
priority_queue<int,vector<int>,greater<int> > q;
//建立小根堆。
int timen=INT_MIN,start=-1,finish=-2;
void work(){
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		q.push(a[i].endd);
		//加入线段
		if(q.size()>k)	q.pop();
		//维持大小为 K 。
		if(q.size()==k)
			if(timen<q.top()-a[i].beginn){
				timen=q.top()-a[i].beginn;
				//求最大差值。
				start=a[i].beginn;	finish=q.top();
				//记录起点、终点。
			}
	}
}

void out(){
	cout<<timen<<'\n';
	int t=k;
	for(int i=1;i<=n&&t;i++)
		if(a[i].beginn<=start&&a[i].endd>=finish)
			cout<<a[i].id<<' ',t--;
			//输出符合条件的线段
}

signed main(){
	in();
	work();
	out();
	return 0;
	//结束
}
```

---

## 作者：XIxii (赞：2)

有点小水……

假如我们已经确定了最终区间的左端点 $L$，那么我们选择的区间一定是左端点在 $L$ 左边，且右端点最右的 $K$ 个点。

所以我们将所有区间按左端点排序，用小根堆维护左端点在左边，且右端点最大的 $K$ 个点。每次用第 $K$ 大值更新答案即可。

下面直接给代码：

```
#include <bits/stdc++.h>
using namespace std;
struct Node
{
    int l,r,id;
}a[1000001];
int n,k,l,r,ans,x,y;
priority_queue<int,vector<int>,greater<int> >q;
inline int read()
{
    int x=0,w=1; 
    char c=getchar();
    while (c<'0' || c>'9') 
    {
        if (c=='-') 
        w=-1; 
        c=getchar();
    }
    while(c>='0' && c<='9') x=x*10+c-'0',c=getchar();
    return x*w;
}
bool cmp(Node a,Node b)
{
    return a.l<b.l;
}
int main()
{
    n=read(); 
    k=read();
    for(int i=1;i<=n;i++)
    {
        l=read(); 
        r=read();
        a[i]=(Node){l,r,i};
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++)
    {
        q.push(a[i].r);
        if(q.size()>k) 
        {
            q.pop();
        }
        if(q.size()==k && q.top()-a[i].l>ans)
        {
            ans=q.top()-a[i].l, x=a[i].l, y=q.top();
        }
    }
    cout<<ans<<endl;
    for(int i=1;i<=n;i++)
    {
        if(a[i].l<=x && a[i].r>=y)
        {
            cout<<a[i].id<<" ";
            k--;
            if(!k) 
            {
                break;
            }
        }
    }
    return 0;
}
```


---

## 作者：zhangliyuan111 (赞：1)

###### ~~第一次见到一个人也能开会的~~

### [**题目传送门**](https://www.luogu.com.cn/problem/P6044)

# 分析题意
### [**简要题意**](https://www.luogu.com.cn/problem/U252799)

把每个律师的空闲时间看成一条线段，开会的时间为所选律师的公共最长空闲时间，即 $k$ 条线段之间的重叠部分的长度。

从 $n$ 条线段中取 $k$ 条，使得重叠部分的长度最长。输出最长长度和选取的线段。

因为有最优解不唯一，只用输出一组即可。

# 解题思路

### 贪心 + 堆（优先队列）。

为方便操作，**先以线段的左端点对线段进行升序排序**。这样保证后一个线段的左端点比前面所有左端点大。

分析题意，知要**以线段的右端点建一个小根堆**，并维护开会时间，包括开始和结束时间。

对于每一条线段，如果数量不到 $k$ 个，则将它加入。若数量已达到 $k$ 个，移除堆顶（即右端点最小的线段），加入此线段后，比较开会时间是否延长。延长则加入；反之不加入。

在求出最长会议时间后，可以**枚举所有线段，找出  $k$ 个包含开会时间的线段，输出编号**。这时在排序前记录编号就很有用了。

是 $O(n\log n)$ 的算法，可以通过 $n≤10^6$ 的数据。




## 代码实现（1）

```cpp
#include <bits/stdc++.h>
using namespace std;

struct man { // 律师 
	int n;   // 编号 
	int l;   // 左端点 
	int r;   // 右端点
} a[1000100];
int answ[1000100];
bool cmp(man a, man b) {	//自定义排序 
	if(a.l!=b.l)
		return a.l < b.l;	//对左端点升序 
	return a.r < b.r;		//左端点相同时用右端点 
}
priority_queue<int,vector<int >,greater<int > >b;
							//用STL优先队列实现小根堆 
int main() { 
	int n,k;
	cin>>n>>k;
	for(int i=0; i<n; i++) {
		cin>>a[i].l>>a[i].r;
		a[i].n=i+1;			//记录编号，方便输出 
	}
	sort(a,a+n,cmp);		//左端点升序排序

	int tim=-1,l,r; 		//维护开会时间，包括开始和结束时间 
	for(int i=0; i<n; i++) {
		b.push(a[i].r);
		if(b.size()>k) {	//数量超过所需时，移除堆顶 
			b.pop();
		}
		if(b.size()==k) {	 
			if(tim<(b.top()-a[i].l)) {//判断第i个律师可不可取 
				r=b.top();	//加入此律师，更新数据 
				l=a[i].l;
				tim=r-l;
			}
		}
	}
	cout<<tim<<endl;

	int cnt=0;
	for(int i=0; i<n; i++) {//遍历寻找k个律师满足条件 
		if(a[i].l<=l&&a[i].r>=r&&cnt<=k) {
			answ[cnt]=a[i].n;
			cnt++;
		}
		if(cnt>k)break;
	}
	//因为之前排序打乱了顺序，所以序号乱了 
	sort(answ,answ+k);
	//输出 
	for(int i=0; i<k; i++) {
		cout<<answ[i]<<' ';
	}
	return 0;
}
``````
 [AC 记录](https://www.luogu.com.cn/record/172814729)


## **问题**

但在 BZOJ 版（[U252799](https://www.luogu.com.cn/problem/U252799)）WA 了 4 个点（[WA 记录](https://www.luogu.com.cn/record/172817543)）

分析错误数据，发现有数据中不存在 $k$ 个律师，使会议时间 $>0$ 。
**也就是说，任意 $k$ 个律师的交集都为空！**
~~（律师都好忙啊）~~
所以要对此数据进行特判。

又因为题目的神奇 spj ，无法开会也要硬拉 $k$ 个律师，但我们只要任意输出 $k$ 个即可。

修改后代码如下：

## 代码实现（2）
```cpp
#include <bits/stdc++.h>
using namespace std;

struct man { // 律师 
	int n;   // 编号 
	int l;   // 左端点 
	int r;   // 右端点
} a[1000100];
int answ[1000100];
bool cmp(man a, man b) {	//自定义排序 
	if(a.l!=b.l)
		return a.l < b.l;	//对左端点升序 
	return a.r < b.r;		//左端点相同时用右端点 
}
priority_queue<int,vector<int >,greater<int > >b;
							//用STL优先队列实现小根堆 

int main() { 
	int n,k;
	cin>>n>>k;
	for(int i=0; i<n; i++) {
		cin>>a[i].l>>a[i].r;
		a[i].n=i+1;			//记录编号，方便输出 
	}
	sort(a,a+n,cmp);		//左端点升序排序 
	int tim=-1,l,r; 		//维护开会时间，包括开始和结束时间 
	for(int i=0; i<n; i++) {
		b.push(a[i].r);
		if(b.size()>k) {	//数量超过所需时，移除堆顶 
			b.pop();
		}
		if(b.size()==k) {	 
			if(tim<(b.top()-a[i].l)) {//判断第i个律师可不可取 
				r=b.top();	//加入此律师，更新数据 
				l=a[i].l;
				tim=r-l;
			}
		}
	}
	if(tim<=0) {			//特判 
		cout<<0<<endl;		//输出0，即无法开会
		//因为题目的神奇spj，无法开会也要找全k个律师
		//已经无法开会了，只要任意找k个就行 
		for(int i=1; i<=k; i++) {
			cout<<i<<' ';
		}
		return 0;
	}
	int cnt=0;
	cout<<tim<<endl;
	
	for(int i=0; i<n; i++) {//遍历寻找k个律师满足条件 
		if(a[i].l<=l&&a[i].r>=r&&cnt<=k) {
			answ[cnt]=a[i].n;
			cnt++;
		}
		if(cnt>k)break;
	}
	//因为之前排序打乱了顺序，所以序号乱了 
	sort(answ,answ+k);
	//输出 
	for(int i=0; i<k; i++) {
		cout<<answ[i]<<' ';
	}
	return 0;
}
``````
[AC 记录](https://www.luogu.com.cn/record/172824010)
## 总结
本题也是一题非常经（模）典（板）的题。再推荐一道贪心好题： [P1230 智力大冲浪](https://www.luogu.com.cn/problem/P1230)

---

## 作者：hinin (赞：1)

使用优先队列（堆）来维护当前可以空闲的律师集合，并通过排序和遍历律师的时间表来寻找最优解。

遍历每个律师的时间段，更新最优解的时间长度和对应的律师编号。更新逻辑基于当前律师的开始时间与队列顶部律师的结束时间之间的差值。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
// #define min(x, y) (x < y ? x : y)
// #define max(x, y) (x > y ? x : y)
#define ll long long
#define pii pair<int, int>

using namespace std;

struct dta { int l, r, id; }; 

const int N = 1e6 + 1; 
dta a[N];
priority_queue<int, vector<int>, greater<int>> q;
int n, k, l, r, ans, x, y;

bool cmp(dta a, dta b) { return a.l < b.l; }

signed main()
{
	ios::sync_with_stdio(false); 
	cin.tie(nullptr); 

	cin >> n >> k; 
	for(int i = 1; i <= n; ++i) {
		cin >> l >> r; 
		a[i] = (dta){l, r, i};
	}

	sort(a + 1, a + n + 1, cmp);

	for(int i = 1; i <= n; i++) {
		q.push(a[i].r);
		if(q.size() > k) { q.pop(); }
		if(q.size() == k and q.top() - a[i].l > ans) {
			ans = q.top() - a[i].l;
			x = a[i].l; 
			y = q.top();
		}
	}

	cout << ans << endl; 
	for(int i = 1; i <= n; i++) {
		if(a[i].l <= x and a[i].r >= y) {
			cout << a[i].id << ' ';
			k--;
			if (not k) { break; }
		}
	}

	return 0; 
}
```

---

## 作者：2021changqing52 (赞：1)

## Solution
- 首先，$n$ 条线段的交集一定是最靠右的左端点到最靠左的右端点。

- 根据这个性质，我们不妨将所有线段**按左端点为关键字排序**，依次**枚举最终交集的左端点**，同时，我们还需维护一个小根堆，维护前 $k$ 大的右端点，每次我们通过堆顶减去当前枚举线段的左端点更新答案。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000010;
struct segment{
        int id,l,r;
};
int n,k,ans,l,r,len;
priority_queue<pair<int,int> >q;
int res[MAXN];
bool cmp(segment a,segment b){
        if(a.l==b.l)return a.r>b.r;
        return a.l<b.l;
}
vector<segment>a(MAXN);
int main(){
        cin>>n>>k;
        for (int i=1;i<=n;i++) {
            a[i].id=i;
            cin>>a[i].l>>a[i].r;
        }
        sort(a.begin()+1,a.end(),cmp);
        ans=0;
        for(int i=1;i<=n;i++){
            if(q.size()<k){
                q.push({-a[i].r, a[i].id});
                if(q.size()==k){
                    ans=max(ans,-q.top().first-a[i].l);
                    l=a[i].l; 
                    r=-q.top().first;
                    continue;
                }
            }else{
                if(a[i].r<-q.top().first)continue;
                pair<int,int>tmp=q.top();q.pop();
                q.push({-a[i].r,a[i].id});
                if(-q.top().first-a[i].l>ans){
                    ans=-q.top().first-a[i].l;
                    l=a[i].l; 
                    r=-q.top().first;
                }
            }    
        }
        printf("%d\n", ans);
        if(ans==0){
            for(int i=1;i<=k;i++)printf("%d ",i);
            return 0;
        }
        len=0;
        for(int i=1;i<=n;i++){
            if(a[i].l<=l&&a[i].r>=r){
                res[++len]=a[i].id;
                if(--k==0)break;
            }
        }
        for(int i=1;i<=len;i++)printf("%d ", res[i]);
        return 0;
}
```
~~码风怪异，不喜勿喷~~。

---

## 作者：TheForgotten (赞：0)

# P6044 [POI2018] Prawnicy 题解
[题目传送门](https://www.luogu.com.cn/problem/P6044)
## 题目大意
定义一个区间 $(l,r)$ 的长度为 $r-l$ ，且空区间的长度为 $0$。
给定数轴上 $n$ 个区间，请选择其中恰好 $k$ 个区间，使得交集的长度最大。
## 思路
观察一下样例中给出的图片，容易发现最长的交集是某一根线段的左端点和某一根线段的右端点组成的区间。根据这一点，我们便想到可以进行端点排序，不如将左端点从小到大排序，从起始点开始判断。

我们发现还有右端点，那么继续思考。既然也是维护有序性，那么考虑使用优先队列，维护合法右端点减去左端点的最大值，利用小根堆，找到合法的最大答案后输出即可，

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
const int N=1000005;
int n,k,t,e,o;
struct node{
	int x;
	int y;
	int num;
}a[N];
bool cmp(node a,node b){
    return a.x==b.x?(a.y<b.y):(a.x<b.x);
}
priority_queue<int,vector<int>,greater<int> >r;
signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i].x>>a[i].y;
        a[i].num=i;
    }
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++){
        r.push(a[i].y);
        while(r.size() >k){
            r.pop();
        }
        if(r.size()==k){ 
            if(o<(r.top()-a[i].x)){
                t=r.top();e=a[i].x;
                o=t-e;
            }
        }
    }
    cout<<o<<endl;
    for(int i=1;i<=n;i++){
        if(a[i].x<=e&&a[i].y>=t&&k){
            k--;
            cout<<a[i].num<<" ";
        }
    }
    return 0;
}
```

---

## 作者：Dream_poetry (赞：0)

### 思路：
考虑贪心。

不难发现，对于我们所求的最优解，必然是某条线段的右端点减去某条线段的左端点。

再参考样例，当我们把最优解相关的线段放在一起，可以看出我们所求的最长时间就是**最靠左的右端点**减去**最靠右的左端点**。

所以我们按照左端点排序，保证了排序后左端点单调递增，随后用堆来加入右端点，当堆的大小与 $k$ 相等时更新答案，并更新左右端点。

最后输出时只需要遍历所有线段，当它能包含我们求出的左右端点时，输出它的编号即可。

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,k,r,l,ans;
struct node{
	int x,y,id;
}a[2000004];

priority_queue<int,vector<int>,greater<int> > p;

bool cmp(node a,node b){
    if (a.x!=b.x) return a.x<b.x;
    return a.y<b.y;
}

signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i].x>>a[i].y;
        a[i].id=i;
    }
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++){
        p.push(a[i].y);// 入堆 
        while(p.size()>k){ // 弹出多余的元素。 
            p.pop();
        }
        if(p.size()==k){ 
            if( ans < (p.top()-a[i].x) ){ // 时间更长，更新 
                r=p.top();
				l=a[i].x;
                ans=r-l;
            }
        }
    }
    cout<<ans<<'\n';
    for(int i=1;i<=n;i++){
        if(a[i].x<=l && a[i].y>=r && k!=0){
            k--;
            cout<<a[i].id<<" ";
        }
    }
    return 0;
}
```

### 更正：
2024.6.24：更正了数组大小，感谢 **@program_xwl**。

---

## 作者：KohaD_SEGA (赞：0)

这题关键思想是：

1. 贪心，将所有律师的空闲时间段按照开始空闲时间从小到大进行排序；
2. 使用优先队列（堆）来选择满足条件的律师，以确保会议的时长尽可能长，从而有效地解决问题。

如果优先队列中的律师数量小于所需的律师数量 `k` ，则将当前律师加入队列，并更新 `maxDuration` 和会议的开始时间 `meetingStart` 和结束时间 `meetingEnd` ；如果优先队列中的律师数量已经达到 `k` ，则考虑当前律师是否可以替换优先队列中结束时间最早的律师。如果当前律师的结束时间晚于队列中最早结束的律师，那么替换并更新相应的变量。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

struct LawyerTime {
    int id, start, end;
};

bool compareLawyers(const LawyerTime &a, const LawyerTime &b) {
    if (a.start == b.start) 
        return a.end > b.end;
    return a.start < b.start;
}

vector<LawyerTime> inputLawyers(int n) {
    vector<LawyerTime> lawyers;
    lawyers.reserve(n);
    for (int i = 0; i < n; i++) {
        int start, end;
        scanf("%d%d",&start,&end);
        lawyers.emplace_back(LawyerTime{i + 1, start, end});
    }
    return lawyers;
}

pair<int, pair<int, int>> selectLawyers(vector<LawyerTime> &lawyers, int k) {
    sort(lawyers.begin(), lawyers.end(), compareLawyers);

    int maxDuration = 0, meetingStart = 0, meetingEnd = 0;
    priority_queue<pair<int, int>> selectedLawyers;

    for (const auto &lawyer : lawyers) {
        if (selectedLawyers.size() < k) {
            selectedLawyers.push({-lawyer.end, lawyer.id});
            if (selectedLawyers.size() == k) {
                maxDuration = max(maxDuration, -selectedLawyers.top().first - lawyer.start);
                meetingStart = lawyer.start;
                meetingEnd = -selectedLawyers.top().first;
                continue;
            }
        } else {
            if (lawyer.end < -selectedLawyers.top().first) continue;
            auto tmp = selectedLawyers.top();
            selectedLawyers.pop();
            selectedLawyers.push({-lawyer.end, lawyer.id});
            if (-selectedLawyers.top().first - lawyer.start > maxDuration) {
                maxDuration = -selectedLawyers.top().first - lawyer.start;
                meetingStart = lawyer.start;
                meetingEnd = -selectedLawyers.top().first;
            }
        }
    }

    return {maxDuration, {meetingStart, meetingEnd}};
}

void outputResults(int maxDuration, const vector<LawyerTime> &lawyers, int k, pair<int, int> meetingTime) {
    if (maxDuration == 0) {
        for (int i = 1; i <= k; i++) cout << i << " ";
    } else {
        int selectedLawyerCount = 0;
        for (const auto &lawyer : lawyers) {
            if (lawyer.start <= meetingTime.first && lawyer.end >= meetingTime.second) {
                cout << lawyer.id << " ";
                if (++selectedLawyerCount == k) break;
            }
        }
    }
}

int main() {
    int n, k;
    scanf("%d%d",&n,&k);
    vector<LawyerTime> lawyers = inputLawyers(n);
    auto [maxDuration, meetingTime] = selectLawyers(lawyers, k);
    cout << maxDuration << "\n";
    outputResults(maxDuration, lawyers, k, meetingTime);
    
    return 0;
}
```

本题卡 `cin/cout` 。

---

