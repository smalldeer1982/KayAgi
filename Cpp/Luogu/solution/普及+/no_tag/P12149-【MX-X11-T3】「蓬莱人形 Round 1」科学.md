# 【MX-X11-T3】「蓬莱人形 Round 1」科学

## 题目背景

原题链接：<https://oier.team/problems/X11D>。

---

「少しの眠れぬ夜に」

「この魔法がほのかに灯るなら」

「今がそんなに悪くないって」

「笑える時まで今日もscience!」


## 题目描述

初始你有 $n$ 个 A 类盒子，第 $i$ 个盒子里有 $a_i$ 个颜色为 $i$ 的球，且每个 A 类盒子的大小无限制。还有 $m$ 个 B 类盒子，购买第 $i$ 个 B 类盒子的花费为 $w_i$，且有大小上限 $b_i$。

你可以进行任意次操作，每次选择一个盒子里的一个球，把它放到另一个盒子中，但你要保证**最终**：

- 每个盒子中的球颜色相同。

- 存在序列长度为 $n$ 的盒子序列 $p$（即**盒子 $p_i$ 可以表示任意一个 A 类或 B 类盒子**），满足对于所有 $i\in[1,n]$，颜色为 $i$ 的小球只会出现在第 $i$ 个 A 类盒子或**盒子 $p_i$**。

你要购买若干个 B 类盒子后（可以不购买）进行上述操作使得所有盒子中球的数量的**最大值最小**，并且**在此基础上**最小化购买 B 类盒子的总花费。

**若未特别标注，则「盒子」表示「A 类盒子」与「B 类盒子」的总称。**

## 说明/提示

**【样例解释 #1】**

买第 $1$ 个 B 类盒子 $(3,3)$，并将第 $1$ 个 A 类盒子中的 $2$ 个颜色为 $1$ 的球放到这个 B 类盒子中即可，花费为 $3$。

**【样例解释 #2】**

买第 $1$ 个 B 类盒子 $(5,2)$ 和第 $4$ 个 B 类盒子 $(1,5)$，并将第 $1$ 个 A 类盒子中的 $1$ 个颜色为 $1$ 的球放到第 $4$ 个 B 类盒子，将第 $3$ 个 A 类盒子中的 $3$ 个颜色为 $3$ 的球放到第 $1$ 个 A 类盒子，将第 $5$ 个 A 类盒子中的 $3$ 个颜色为 $5$ 的球放到第 $1$ 个 B 类盒子，所有盒子球数最大值为 $4$，花费为 $7$。

**【数据范围】**

**本题使用子任务捆绑**。

对于所有测试数据，$1 \le n,m \le 2 \times 10^5$，$1\le a_i,b_i,w_i \le 10^9$。

|子任务编号|$n\le$|$m \le$|特殊性质|分值|
|:-:|:-:|:-:|:-:|:-:|
|$1$|$6$|$6$|无|$10$|
|$2$|$2 \times 10^5$|$1$|无|$15$|
|$3$|$2 \times 10^5$|$5$|无|$20$|
|$4$|$2 \times 10^5$|$2 \times 10^5$|保证所有 $a_i,b_i \le 2$|$15$|
|$5$|$2 \times 10^5$|$2 \times 10^5$|无|$40$|

## 样例 #1

### 输入

```
5 3
5 2 1 3 2 
3 3
1 5
1 4
```

### 输出

```
3 3```

## 样例 #2

### 输入

```
5 5
1 1 7 4 7 
5 2
5 7
1 6
1 5
2 10```

### 输出

```
4 7
```

## 样例 #3

### 输入

```
5 3
1 2 5 4 4 
3 5
4 4
2 1
```

### 输出

```
3 10```

## 样例 #4

### 输入

```
5 3
2 4 3 3 4 
1 1
4 4
5 2
```

### 输出

```
3 3```

# 题解

## 作者：WuMin4 (赞：2)

## [【MX-X11-T3】「蓬莱人形 Round 1」科学](https://www.luogu.com.cn/problem/P12149)

## 思路

使得最大值最小显然二分，考虑知道最大值该如何检查是否可以满足条件。

设球的数量最大值为 $k$，则我们需要对所有满足 $a_i>k$ 的球进行移动。此处我们首先要满足 $a_i\le 2\times k$，因为球最多只能在两个盒子内，根据抽屉原理，当 $a_i> 2\times k$ 时，至少会有一个箱子中的球大于 $k$ 个，则永远不会满足条件。

对于所有满足 $a_i>k$ 的球可以分为以下两种移动方式：

1. 将多余的球移到一个 B 类盒子中，此时需要移动到 B 类盒子中球的数量即为 $a_i-k$。

2. 将一个 A 类箱子 $j$ 中的球移到一个 B 类盒子中，再将 A 类箱子 $i$ 中多余的球移到 A 类箱子 $j$ 中，此时需要移动到 $B$ 类盒子中球的数量即为 $a_j$。

于是我们将满足 $a_i>k$ 的 $a_i-k$ 和满足 $a_j<k$ 的 $a_j$ 加入一个数组并排序。设满足 $a_i>k$ 的 $i$ 的数量为 $cnt$，则取该数组前 $cnt$ 小即为最佳移动方案。

我们可以贪心的按照数量从大到小为每个球选择满足大小限制条件且代价最小的盒子。当没有满足条件的盒子时，则表示该情况无解，否则可以求出最小代价。此处选择代价最小的盒子可以采用优先队列维护。

时间复杂度 $O(n\log^2n)$，可以通过。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[200005];
struct node{
	int b,w;
}b[200005];
bool cmp(node x,node y){
	return x.b>y.b;
}
int check(int mid){
	vector<int> mr;
	int mrs=0;
	for(int i=1;i<=n;i++)
		if(a[i]>mid) mr.push_back(a[i]-mid),mrs++;
	for(int i=1;i<=n;i++)
		if(a[i]<mid) mr.push_back(a[i]);
	sort(mr.begin(),mr.end());
	if(mr.size()==0) return 0;
	if(mr[mr.size()-1]>mid) return -1;
	int r=1,tot=0;
	priority_queue<int,vector<int>,greater<int>> c;
	for(int i=mrs-1;i>=0;i--){
		while(b[r].b>=mr[i]) c.push(b[r].w),r++;
		if(c.empty()) return -1;
		tot+=c.top();c.pop();
	}
	return tot;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++) cin>>b[i].b>>b[i].w;
	sort(b+1,b+1+m,cmp);
	int l=1,r=1e9,mid,res1=1e9+1,res2=0;
	while(l<=r){
		mid=(l+r)/2;
		int tmp=check(mid);
		if(tmp!=-1) r=mid-1,res1=mid,res2=tmp;
		else l=mid+1;
	}
	cout<<res1<<" "<<res2<<endl;
	return 0; 
}
```

---

## 作者：Lmx120815 (赞：1)

感觉题目有点晦涩难懂哈。 

一看到最大值最小，考虑二分答案。我们可以二分最大值。考虑如何判断。我们发现对于那些数量大于二分最大值的盒子，一定要分出多的部分，装到其他的盒子里。

而一旦有一个盒子大于二分最大值的两倍，那就一定不合法。同时对于那些小于二分最大值的盒子，其实也可能会移动。我们可以将一个小的盒子移动到一个卖的盒子中，而将其他盒子的超出部分放到原先的盒子里，因为原先的盒子是不限制大小的。

然后我们发现可以将这两种可能会移动的盒子存起来，然后排序，将可以最大的几个优先放入无上限的盒子。其他的盒子，记录比自己大的能买的盒子中最便宜的盒子，这个可以用优先队列维护，然后记录答案即可。

具体实现看代码吧。
```cpp
#include <bits/stdc++.h>
#define int long long
#define ll long long
#define ull unsigned long long
#define inf 1e12
#define eps 1e-9
#define endl "\n"
#define il inline
#define ls 2*k
#define rs 2*k+1
using namespace std;
const int N=2e5+5,M=1e5+5;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*f;
}
int n,a[N],m;
struct node{
	int b,w;
	friend bool operator < (node x,node y){
		return x.b>y.b;
	}
}b[N];
inline int check(int x){
	vector<int>todo;
	int cnt=0,num=0;
	for(int i=1;i<=n;i++) if(a[i]>x) todo.push_back(a[i]-x),cnt++;
	for(int i=1;i<=n;i++) if(a[i]<x) todo.push_back(a[i]),num++;
	sort(todo.begin(),todo.end());
	if(todo.size()==0) return 0;
	if(todo[todo.size()-1]>x) return -1;
	priority_queue<int,vector<int>,greater<int> >q;
	int now=1,tot=0;
	for(int i=cnt-1;i>=0;i--){
		while(b[now].b>=todo[i]) q.push(b[now].w),now++;
		if(q.empty()) return -1;
		tot+=q.top(),q.pop();
	}
	return tot;
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=m;i++) b[i].b=read(),b[i].w=read();
	sort(b+1,b+m+1);
	int l=1,r=inf;
	int ans1,ans2;
	while(l<=r){
		int mid=(l+r)>>1;
		int tmp=check(mid);
		if(tmp!=-1) r=mid-1,ans1=mid,ans2=tmp;
		else l=mid+1;
	}
	printf("%lld %lld\n",ans1,ans2);
	return 0;
}
```

---

## 作者：xuanfeng101 (赞：1)

## 思路
首先看到形如**最大值最小**的问题是我们就要条件反射到**二分答案**，我们答案具有**单调性**（最大值越大的话需要的盒子肯定不会更多，也就是说答案是**向左趋近的**。

因此我们可以**二分最大值**，记为 $v$，我们可以发现，对于$a_i \le v$ 的 $a_i$ 我们一定要把其拆开，因为题目繁杂的限制其实意思是小球要么出现在自己**原来的盒子**中要么再找一个**空盒子**扔进去，所以对于多出的部分我们要再找一个盒子。然而剩下的部分只能待在原来的盒子中，那么我们就将其**固定住**, 而用 $a_i - v$ 作为剩余小球个数。 那么对于 $a_i \le v$ 的小球不难发现我们没有必要把他们拆开多占空间, 那么我们就可以**整体移动**它们，我们可以发现这样处理与处理剩下的 $a_i - v$ 类型的小球方式是一样的。

也就是说，现在我们有若干种若干数量的小球，我们要把**同一种小球**塞进**同一箱子**，问最小代价。那么我们可以将原来可以自由移动的 $a$ 箱子中的求先拿出来，把这些箱子视作代价为 $0$ 而空间为 $\operatorname{INF}$ 的箱子。

那么我们就可以开始**贪心**了。将剩下所有小球排序，把**数量较多的小球**优先放入多出的 $a$ 箱子中，再**从大到小**扫一遍剩余小球，装入 $b$ 箱子，用**小根堆**维护可以装当前种小球的箱子的最小代价。

## 时间复杂度
$O(n\log^2n)$

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
typedef pair<int, int> pii;
const int N = 2e5 + 10;
int n, m, ans;
int a[N];
pii b[N];

bool cmp(pii a, pii b)
{
	return a.x > b.x;
}

bool check(int v)
{
	ans = 0;
	vector<int> vec;
	priority_queue<int, vector<int>, greater<int>> q;
	int cnt = 0;
	for (int i = 1; i <= n; i ++ ) 
		if (a[i] > v) 
		{
			if (a[i] > v * 2) return 0;
			vec.push_back(a[i] - v);
			cnt ++ ;
		}
		else vec.push_back(a[i]);
	sort(vec.begin(), vec.end());	
	for (int i = cnt - 1, j = 1; i >= 0; i -- )
	{
		while (j <= m && b[j].x >= vec[i]) q.push(b[j ++ ].y);
		if (!q.size()) return 0;
		ans += q.top(), q.pop();
	}
	return 1;
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i ++ ) cin >> a[i];
	sort(a + 1, a + 1 + n);
	for (int i = 1; i <= m; i ++ ) cin >> b[i].x >> b[i].y;
	sort(b + 1, b + 1 + m, cmp);
	int l = 1, r = 1e9;
	while (l < r)
	{
		int mid = l + r >> 1;
		if (check(mid)) r = mid;
		else l = mid + 1; 
	}
	check(l);
	cout << l << ' ' << ans;
	return 0;
}
```

---

## 作者：_smart_stupid_ (赞：0)

所以题目名字为什么不是 “空飛ぶ巫女の不思議な毎日”？

## 思路

首先，很显然，第一问答案小于等于 $\lceil\frac{\max\limits_{i=1}^n{a_i}}{2}\rceil$，且满足单调性，所以二分答案第一问。我们将 AB 盒子排序后，假设答案为 $x$，按以下方式放置：

将前 $k$ 小的盒子用 B 盒子装起来，且保证 $k$ 尽量大，将前 $k$ 大的盒子超过 $x$ 的部分分摊到空了的 $k$ 个 A 盒子里，剩下的 A 盒子将超过 $x$ 部分的用剩下的 B 盒子装起来。

所以我们这样写 `check`（我将 A 和 B 从大到小排序）：

```cpp
bool check(int x) {
	for (int i = 1; i <= m; i++) b1[i] = b[i].b;
	int pos = m, k = 0;
	for (int i = n; i >= 1; i--) {
		while (pos > 0 && b1[pos] < a[i]) pos--;
		if (!pos) break; // 装不动了
		b1[pos] = 0, k++; // 被用过了
	}
	pos = 1;
	for (int i = k + 1; i <= n; i++) { // 忽略前 k 大的
		while (pos <= m && !b1[pos]) pos++;
		if (a[i] - b1[pos] > x) return 0;
		pos++;
	}
	return 1;
}
```

第一问出来了，第二问就直接把超过 $x$ 的部分放进 B 里面。由于 A 盒子可以乱放，所以只需要把超出 $x$ 的盒子减去 $x$，再取这些盒子最小的那一部分，装进 B 里面，选哪些盒子可以用单调队列求解。

## AC 代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, a[200100];
struct node{
	int b, w;
} b[200100];
int b1[200100];
bool cmp(node a, node b) {
	return a.b > b.b;
}
bool operator <(node a, node b) {
	return a.w > b.w;
}
priority_queue<node> pq;
bool check(int x) {
	for (int i = 1; i <= m; i++) b1[i] = b[i].b;
	int pos = m, k = 0;
	for (int i = n; i >= 1; i--) {
		while (pos > 0 && b1[pos] < a[i]) pos--;
		if (!pos) break; // 装不动了
		b1[pos] = 0, k++; // 被用过了
	}
	pos = 1;
	for (int i = k + 1; i <= n; i++) { // 忽略前 k 大的
		while (pos <= m && !b1[pos]) pos++;
		if (a[i] - b1[pos] > x) return 0;
		pos++;
	}
	return 1;
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= m; i++) {
		cin >> b[i].b >> b[i].w;
	}
	sort(b + 1, b + m + 1, cmp);
	sort(a + 1, a + n + 1, greater<int>());
	int ans1 = 0, ans2 = 0;
	int l = a[1] / 2 + a[1] % 2, r = 1000000000;
	while (l < r) {
		int mid = (l + r) / 2;
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	ans1 = l;
	int cnt = 0; // 超出 x 盒子的数量
	for (int i = 1; i <= n; i++) {
		if (a[i] > ans1) a[i] -= ans1, cnt++;
	}
	sort(a + 1, a + n + 1);
	int pos = 1;
	for (int i = cnt; i >= 1; i--) {
		while (pos <= m && b[pos].b >= a[i]) { 
			pq.push(b[pos]);
			pos++;
		// 将可以装下当前 A 盒子的 B 盒子放进去。
		}
		if (!pq.empty()) {
			ans2 += pq.top().w;
			pq.pop();
		}
	}
	cout << ans1 << ' ' << ans2 << '\n';
	return 0;
}
```

---

## 作者：fish_love_cat (赞：0)

感谢 @[wanggk](https://www.luogu.com.cn/user/252664) 大神帮我调题并且提供 check 思路 /bx

然后就是我几次有了 [hack](https://www.luogu.com.cn/discuss/1072218) 还没写出来，怎么这么笨啊啊啊。

---

首先最大值最小想到二分答案，然后思考 check 怎么写。

最小化花费，于是想到试着贪心。

我们把每个超出最大值的点按照降序排序，找可以用的盒子中价格最小的用，如果出现没盒的情况即为无解。

然后挂了，你会发现你少考虑一种把小数字扔出去然后把大数字占据小数字没有上限的原盒的情况。

于是风铃草决定把这两种情况分开处理，拼尽全力没有写出来。

其实有更好的做法，我们把所有数字和盒子拆开，然后注意到超出最大值的数字对应盒子是拆不下来的，于是只拿了部分数字出来。

于是局面转化为了若干个不超过最大值的数字与若干盒子，此时再用上面的那个贪心就行了。

复杂度 $O(n \log ^2 n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200005];
struct fish{
    int w,b;
}b[200005];
int ans;
bool cmp(fish x,fish y){
    return x.b<y.b;
}
bool cmp1(int x,int y){
    return x>y;
}
int maxx;
int n,m;
int check(int x){
    priority_queue<int,vector<int>,greater<int> >q;
    int ret=0;
    vector<int>v;
    vector<fish>e;
    for(int i=1;i<=n;i++){
        if(a[i]<=x)v.push_back(a[i]),e.push_back({0,x});
        else v.push_back(a[i]-x);
    }
    for(int i=1;i<=m;i++)e.push_back(b[i]);
    sort(e.begin(),e.end(),cmp);
    sort(v.begin(),v.end(),cmp1);
    int id=e.size()-1;
    for(int i=0;i<v.size();i++){
        while(id>=0&&e[id].b>=v[i])q.push(e[id].w),id--;
        if(q.empty())return -1;
        ret+=q.top(),q.pop();
    }
    return ret;
}
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>a[i],maxx=max(maxx,a[i]);
    for(int i=1;i<=m;i++)
        cin>>b[i].b>>b[i].w;
    int l=maxx/2+maxx%2,r=maxx;
    while(l<r){
        int mid=(l+r)/2;
        int ret=check(mid);
        if(ret!=-1)ans=ret,r=mid;
        else l=mid+1;
    }
    check(3);
    cout<<r<<' '<<ans;
    return 0;
}
/*
2 1
5 3
1 1

4 1
*/
```

---

## 作者：clarify (赞：0)

二分模拟砍掉的 $w$ 值，对所有的 $A$ 类盒子中多出 $w$ 值的小球拿出来，如果原盒子内小球数量大于 $2 \times w$ 则说明无法满足当前的最值。可以看出 $A$ 类盒子损耗是大于 $B$ 类盒子的，需优先处理小球个数多的放于 $A$ 类盒子。将剩下的小球按大的优先放置即可，使用优先队列，否则超时。
![](https://cdn.luogu.com.cn/upload/image_hosting/fg45xud0.png)

Code:
```
#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> PII;
typedef long long ll;
const int N = 200010;
int n, m;
ll res;
int a[N], b[2 * N];
struct Node
{
    int b, w;
    bool operator<(const Node &n) const
    {
        if (b != n.b)
            return b > n.b;
        return w < n.w;
    }
} node[N];

int check(int x)
{
    res = 0;
    int cnt = n;
    for (int i = 1; i <= n; i ++ )
    {
        b[i] = a[i];
        if (b[i] > x)
        {
            b[ ++ cnt] = b[i] - x;
            b[i] -= x;
            if (b[i] > x)
                return 0;
        }
    }
    sort(b + 1, b + cnt + 1, greater<int>());

    priority_queue<int, vector<int>, greater<int>> pq;
    int j = 1;

    for (int i = n + 1; i <= cnt; i ++ )
    {
        while (j <= m && node[j].b >= b[i])
        {
            pq.push(node[j].w);
            j ++ ;
        }

        if (pq.empty())
            return 0;

        auto w = pq.top();
        pq.pop();
        res += w;
    }

    return 1;
}

int main()
{
    cin >> n >> m;
    int maxa = 0;
    for (int i = 1; i <= n; i ++ )
    {
        cin >> a[i];
        maxa = max(maxa, a[i]);
    }
    for (int i = 1; i <= m; i ++ )
    {
        cin >> node[i].b >> node[i].w;
    }
    sort(node + 1, node + m + 1);
    ll mincnt = 0, cost = 0;
    int l = 0, r = maxa + 1;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
        {
            r = mid;
            mincnt = mid;
            cost = res;
        }
        else
            l = mid + 1;
    }
    cout << mincnt << " " << cost;
    return 0;
}
```

---

## 作者：可爱大黄兔 (赞：0)

## 思路
根据**最大值最小**为首要条件可知用二分。而二分性质向右，因此我们要往左二分。
设球最多 $x$ 个，则我们可以这样做：把 $a_i ≤ x$ 的 $a_i$ 个球和 $a_i ≥ x$ 的 $x - a_i$ 个球放到一个待匹配的 vector，再将盒子放到另一个 vector 内，两个数组从小到大排序，从后往前使用小顶堆贪心即可。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;
typedef pair<ll, ll> PII;
ll a[400010];
ll b[400010], w[400010];
PII pt[400010];
int n, m;
vector<ll> wt_ball; // 待匹配
vector<PII> box;
// value id
ll V = 0;
ll ans2 = 0x3f3f3f3f3f3f3f3f;
priority_queue<ll, vector<ll>, greater<ll> >hp;

ll check(ll mid) {
	wt_ball.clear();
	box.clear();
	hp = (priority_queue<ll, vector<ll>, greater<ll> >) {};
	for (int i = 1; i <= n; i++) {
		if (a[i] > mid)
			wt_ball.push_back(a[i] - mid);
		if (a[i] <= mid) {
			wt_ball.push_back(a[i]);
			box.push_back({mid, 0ll});
		}
	}
	for (int i = 1; i <= m; i++) {
		box.push_back({min(mid, b[i]), w[i]});
	}
	sort(wt_ball.begin(), wt_ball.end());
	sort(box.begin(), box.end());
	ll cnt = 0ll;
	int j = box.size() - 1;
	for (int i = wt_ball.size() - 1; i >= 0; i--) {
		while (j >= 0 && box[j].first >= wt_ball[i]) {
			hp.push(box[j].second), j--;
		}
		if (hp.size() == 0) {
			return 0;
		}
		cnt += hp.top();
		hp.pop();
	}
//	printf("===%lld %lld\n", mid, cnt);
	return cnt;
}

signed main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]), V = max(V, a[i]);
	for (int i = 1; i <= m; i++) {
		ll x, y;
		scanf("%lld%lld", &x, &y);
		b[i] = x, w[i] = y;
	}
	ll l = 1, r = V;
	while (l < r) {
		ll mid = (l + r) / 2;
		ll t = check(mid);
		if (t)
			r = mid, ans2 = t;
		else
			l = mid + 1;

	}
	printf("%lld %lld", r, check(r));
	return 0;
}
```

---

## 作者：sbno333 (赞：0)

看到最大值最小直接考虑二分答案。

我们考虑一种颜色只能最多分配到两个盒子，所以如果一种颜色数量达到二分的答案两倍，直接报告不可能。

然后考虑多出来的部分都要买盒子，但是我们可以鸠占鹊巢，干掉小球少的颜色的盒子给我们，然后那种颜色代替我们找新盒子。

能这样做当且仅当少的那个的总数量比我们比答案多的数量小。

然后贪心干掉，得到一个序列，每个元素存储需要找一个至少大小为元素大小的新盒子来装。

我们按元素从大到小排序，然后扫一遍，扫到元素后将没有丢到优先队列里并且能装下这个元素的盒子丢到优先队列，然后队列里取个最便宜的，装下，如果队列里没元素就报告答案不可能。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int a[1000009];
struct st{
	int b,w;
	bool operator<(const st dd)const{
		return w<dd.w;
	}
	bool operator>(const st dd)const{
		return w>dd.w;
	}
}b[1000009];
bool cmp(st a1,st a2){
	return a1.b<a2.b;
}
int xl[1000009];
priority_queue<st,vector<st>,greater<st> > q;
int check(int x){
	int inn;
	inn=0;
	for(int i=n;i>=1;i--){
		if(a[i]>x){
			xl[++inn]=a[i]-x;
		}
	}
	int z;
	z=1;
	for(int i=1;i<=n;i++){
		if(a[i]<=x&&z<=inn){
			xl[z]=min(xl[z],a[i]);
			z++;
		}
	}
	sort(xl+1,xl+1+inn);
	while(q.size()){
		q.pop();
	}
	int ans;
	ans=0;
	int p;
	p=m;
	for(int i=inn;i>=1;i--){
		
		while(p>0&&b[p].b>=xl[i]){
			q.push(b[p]);
			p--;
		}
		if(!q.size()){
			return -1;
		}
		ans+=q.top().w;
		q.pop();
	}
	return ans;
}
signed main(){
	cin>>n>>m;
	int z;
	z=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		z=max(a[i],z);
	}
	sort(a+1,a+1+n);
	for(int i=1;i<=m;i++){
		cin>>b[i].b>>b[i].w;
	}
	sort(b+1,b+1+m,cmp);
	int l,r;
	l=z-z/2;
	r=z;
	while(l<r){
		int mid;
		mid=l+r;
		mid>>=1;
		if(check(mid)<0){
			l=mid+1;
		}else{
			r=mid;
		}
	}
	cout<<l<<" "<<check(l)<<endl;
	return 0;
}
```

---

## 作者：Lele_Programmer (赞：0)

# P12149 题解

## 思路

二分答案，求盒子中球个数最大值的最小值，然后在二分的过程中，顺便统计最小花费。

题目说得很复杂，简单来看，其实就是每个盒子中的球颜色相同，并且同一种颜色最多出现在 $2$ 个不同盒子内。

考虑对于一个 $k$，要判定盒子中球的个数的最大值能否等于 $k$，则对于每一个 $a_i > k$，将 $a_i-k$ 插到一个数组里面，表示需要一个新的盒子装这些球，由于 B 类盒子容量有限，所以我们尽可能将数量多的球放进 A 类盒子里面。

假设有 $s$ 种球是需要拆开来的，那么可以将这 $s$ 种球和原数组 $a$ 放在一起形成一个新序列，升序排序，取前 $s$ 种，表示需要将这 $s$ 种球放进新的 B 类盒子中。

对于 B 类盒子，$b$ 作为第一关键字升序排序，$w$ 作为第二关键字升序排序，于是可以轻松地处理出对于每一个 $i$ 满足 $1 \le i \le s$，$s_i$ 可以选的盒子的范围 $[st_i, m]$。

然后按照 $st_i$ 从大到小的顺序枚举，从 $[st_i, m]$ 这个区间里面选取一个未被选过的 $w$ 最小的盒子。注意这里应该降序枚举，因为正着枚举有可能前面枚举到的数把后面应该拿到的数先抢走了。

求区间最小值，可以用线段树。对于取掉的盒子，把它的值改为正无穷，如果枚举的时候取出了正无穷的盒子，就意味着无解了。在枚举完之后，把线段树上修改的值还原回去就行了。

线段树操作是 $\mathcal{O}(\log n)$，所以单次判定需要 $\mathcal{O}(n \log n)$，所以最终复杂度就是 $\mathcal{O}(n \log^2 n)$。

## 代码

```cpp
#define int long long

const int N=200005;
const int inf=1e18;

int n,m,mx;
int a[N];
int ans;

struct Box {
    int b,w;
    friend bool operator < (const Box& a,const Box& b) {
        if (a.b!=b.b) return a.b<b.b;
        else return a.w<b.w;
    }
} arr[N];

struct Seg {
    int l,r;
    int v,i;
    void init() {
        v=i=inf;
    }
} tr[N<<2];

void pushup(Seg& u,Seg& l,Seg& r) {
    u.v=min(l.v,r.v);
    if (u.v==l.v) u.i=l.i;
    else u.i=r.i;
}

void pushup(int u) {
    pushup(tr[u],tr[u<<1],tr[u<<1|1]);
}

void build(int u,int l,int r) {
    tr[u]={l,r,arr[l].w,l};
    if (l==r) return;
    int mid=l+r>>1;
    build(u<<1,l,mid),build(u<<1|1,mid+1,r);
    pushup(u);
}

void modify(int u,int p,int k) {
    if (tr[u].l==p && tr[u].r==p) tr[u].v=k;
    else {
        int mid=tr[u].l+tr[u].r>>1;
        if (p<=mid) modify(u<<1,p,k);
        else modify(u<<1|1,p,k);
        pushup(u);
    }
}

Seg query(int u,int l,int r) {
    if (tr[u].l>=l && tr[u].r<=r) return tr[u];
    Seg ans,L,R;
    L.init(),R.init();
    int mid=tr[u].l+tr[u].r>>1;
    if (l<=mid) L=query(u<<1,l,r);
    if (r>mid) R=query(u<<1|1,l,r);
    pushup(ans,L,R);
    return ans;
}

bool check(int mid) {
    // puts("===========================");
    // printf("CHECK: %lld\n",mid);
    vector<int> vec;
    _rep(i,1,n) {
        if (a[i]<=mid) continue;
        vec.emplace_back(a[i]-mid);
    }
    int sz=(int)vec.size();
    int t=1;
    _rep(i,1,n) vec.emplace_back(a[i]);
    sort(vec.begin(),vec.end());
    while ((int)vec.size()>sz) vec.pop_back();
    // printf("vec: "); _iter(it,vec) writesp(*it); putchar(10);
    // printf("tree: "); _rep(i,1,m) writesp(query(1,i,i).v); putchar(10);
    vector<int> st;
    vector<pii> md;
    int cur=1,sum=0;
    bool ok=true;
    _iter(it,vec) {
        int k=*it;
        while (cur<=m && arr[cur].b<k) cur++;
        if (cur==m+1) return false;
        st.emplace_back(cur);
    }
    _rrep(i,(int)vec.size()-1,0) {
        int k=vec[i];
        auto t=query(1,st[i],m);
        // printf("query: %lld %lld\n",st[i],m);
        // printf("get: %lld %lld\n",t.v,t.i);
        if (t.v==inf) {
            ok=false;
            break;
        }
        sum+=t.v;
        modify(1,t.i,inf);
        md.emplace_back(pii{t.i,t.v});
    }
    _iter(it,md) modify(1,it->first,it->second);
    if (ok) ans=sum;
    return ok;
}

i32 main() {
    // FRR("D.in");
    read(n),read(m);
    _rep(i,1,n) read(a[i]),mx=max(mx,a[i]);
    _rep(i,1,m) read(arr[i].b),read(arr[i].w);
    sort(a+1,a+1+n);
    sort(arr+1,arr+1+m);
    build(1,1,m);
    int l=(mx/2)+(mx%2),r=mx;
    while (l<r) {
        int mid=l+r>>1;
        if (check(mid)) r=mid;
        else l=mid+1;
    }
    writesp(r),write(ans);
    return 0;
}
```

---

