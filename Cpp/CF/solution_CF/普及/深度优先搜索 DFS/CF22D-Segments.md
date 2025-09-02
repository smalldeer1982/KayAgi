# Segments

## 题目描述

You are given $ n $ segments on the Ox-axis. You can drive a nail in any integer point on the Ox-axis line nail so, that all segments containing this point, are considered nailed down. If the nail passes through endpoint of some segment, this segment is considered to be nailed too. What is the smallest number of nails needed to nail all the segments down?

## 样例 #1

### 输入

```
2
0 2
2 5
```

### 输出

```
1
2 ```

## 样例 #2

### 输入

```
5
0 3
4 2
4 8
8 10
7 7
```

### 输出

```
3
7 10 3
```

# 题解

## 作者：xiaoPanda (赞：4)

### Problem
在坐标轴上给定 $n$ 条线段，有 $k$ 个点，使这 $n$ 条线段都至少有一个点在其上面（恰在端点也行）。

求 $k$ 的最小值，并给出一个 $k$ 最小时的方案。

### Solution
ABC230D 的弱化版（然鹅其实区别不大）

很明显是贪心，先假设每条线段都已经按结尾点排好序。

如果一条线段在这以前没有被覆盖，那么一定会在这条线段上增加一个点。

那么这个点放在那里最合适呢？

很明显是这条线段的结尾处，因为如果加在线段中间，就会浪费这个点的功能，在按结尾点排好序后，放在线段结尾一定小于等于下一个没有覆盖的线段的结尾，不会出现新加的点在线段中间覆盖的线段比在结尾少。

举个栗子（样例 2 ）：

![](https://cdn.luogu.com.cn/upload/image_hosting/02nqe9hp.png?x-oss-process=image/resize,m_lfit,h_500,w_1000)

首先发现第 $1$ 条线段没有被覆盖，于是在它的结尾 $3$ 处放一个点。

这个点也可以盖住第 $2$ 条边，然后发现第 $3$ 条线段没有被覆盖，再在它的结尾 $7$ 处放一个点。

这个点同样也可以盖住第 $4$ 条边，最后只有第 $5$ 条线段没有被覆盖，在它的结尾 $10$ 处放一个点。

然后具体实现的话先结构体排序一下，然后每次找到没有覆盖的点就答案加一，再往后跳直到再找到这个点覆盖不了的点。
### Code
```cpp
void solve()
{
	int n,ans=0;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&id[i].x,&id[i].y);
		if(id[i].x>id[i].y)swap(id[i].x,id[i].y);//差点被坑到~
	}
	sort(id+1,id+n+1,cmp);//按结束点排序
	for(int i=1;i<=n;i++)
	{
		int k=id[i].y;i++;
		//cout<<id[i].y<<" ";
		while(id[i].x<=k&&i<=n)i++;i--;//往后跳直到找到没有覆盖的点
		ans++;
	}cout<<ans<<endl;
	for(int i=1;i<=n;i++)
	{
		int k=id[i].y;//再做一次找到方案
		cout<<id[i].y<<" ";i++;//这条线段没有覆盖
		while(id[i].x<=k&&i<=n)i++;i--;
	}
	
}
```


---

## 作者：杳冥 (赞：2)

### **主要思想：贪心**
### **思路：**
 将读入的线段按左端点从小到大排序，若遇到未被选择过的线段，则记录这条线段的右端点，然后再进行下一条线段的记录，每次只是记录右端点（$la$），若下一条线段的右端点小于上一次记录的右端点，则将记录的右端点值改为本条线段的右端点；若下一条线段的左端点比上一次记录的端点值大，则 $ans$++，并重新更新 $la$.
### **CODE:**
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define f(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
inline int rd(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
inline void wt(int x){
	if(x<0) x=~x+1,putchar('-');
	if(x>9) wt(x/10);
	putchar(x%10+'0');
}
struct zkw{
	int l,r;
};
zkw a[1010];
int cmp(zkw a,zkw b){ //排序参数
	if(a.l==b.l) return a.r<b.r;
	return a.l<b.l;
}
int n,ans=0;
int yy[1010];
int main(){
	n=rd();
	f(i,1,n){
		a[i].l=rd();a[i].r=rd();
		if(a[i].l>a[i].r) swap(a[i].l,a[i].r);
	}
	sort(a+1,a+n+1,cmp);
	int la=a[1].r;//la为上一个记录点
	ans++;
	yy[ans]=la;
	f(i,2,n){ //对每一条线段一次判断
		if(a[i].l<=la && a[i].r>=la) continue;
		if(a[i].l>la){
			la=a[i].r;
			ans++;
			yy[ans]=la;
			continue;
		}
		if(a[i].r<la){
			la=a[i].r;
			yy[ans]=la;
			continue;
		}
	}
	wt(ans);
	putchar('\n');
	f(i,1,ans){
		wt(yy[i]);
		putchar(' ');
	} 
	return 0;
}
```


---

## 作者：Mistybranch (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF22D)

题目大概意思是：给定 $n$ 条线段的起终点，问至少需要添加几个点才能保证每条线段上至少有一个点。

一道贪心的题，在说思路的同时会配合样例数据来讲：

这是样例 $2$ 的输入数据输入画的图（~~为了让每条线段看起来更加直观，画在了不同坐标轴上，但实际上每条线段是在同一条直线上的~~）：

![](https://cdn.luogu.com.cn/upload/image_hosting/2stko4uv.png)

- 首先先给所有点按照右端点从小到大排序。

![](https://cdn.luogu.com.cn/upload/image_hosting/zlsae4yv.png)

```cpp
struct seg {
	int l, r;
	
	bool operator < (const seg& one) const {//运算符重载
		if (r != one.r) {
			return r < one.r;
		}
		
		return l < one.l;
	}
};

sort(segList + 1, segList + n + 1);
```

- 将每条边扫一遍，如果第 $i$ 条边上没有点，那么就添加第 $i$ 条边的右端点（这样能使得后面更多的线段上有这个点）；如果第 $i$ 条边上有点则跳过。

以样例为例举个例子：

1. 扫到第 $1$ 条边，发现没有点被添加过，添加这条边的右端点 $3$。扫到第 $2$ 条边，发现点 $3$ 在这条边上，直接跳过不添加点。

![](https://cdn.luogu.com.cn/upload/image_hosting/254t6idq.png)

2. 扫到第 $3$ 条边，发现点 $3$ 不在这条边上，添加这条边的右端点 $7$，扫到第 $4$ 条边，发现点 $7$ 在这条边上，直接跳过不添加点。

![](https://cdn.luogu.com.cn/upload/image_hosting/3ko1950e.png)

3. 扫到第 $5$ 条边，发现点 $7$ 不在这条边上（最后添加的点一定是最接近这条边的），添加这条边的右端点 $10$。结束。

![](https://cdn.luogu.com.cn/upload/image_hosting/2uls8817.png)

看似很复杂，代码很简单：

```cpp
for (int i = 1; i <= n; i++) {
	if (res.size() == 0 || segList[i].l > res[res.size() - 1]) {
		res.push_back(segList[i].r);
	}
} 
```
完整代码：

```cpp


#include <bits/stdc++.h>

using namespace std;

struct seg {
	int l, r;
	
	bool operator < (const seg& one) const {
		if (r != one.r) {
			return r < one.r;
		}
		
		return l < one.l;
	}
}segList[1009];

int n;
vector<int> res;

int main () {
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &segList[i].l, &segList[i].r);
		
		if (segList[i].l > segList[i].r) {
			swap(segList[i].l, segList[i].r);
		}
	}
	
	sort(segList + 1, segList + n + 1);
	
	for (int i = 1; i <= n; i++) {
		if (res.size() == 0 || segList[i].l > res[res.size() - 1]) {
			res.push_back(segList[i].r);
		}
	} 
	
	printf("%d\n", res.size());
	
	for (int i = 0; i < res.size(); i++) {
		printf("%d ", res[i]);
	}
	
	printf("\n");
	
	return 0;
}
```


---

## 作者：yzyjh (赞：1)

#### 我的思路：vector来记数，方便排序，在从头到尾扫一遍

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
 
 
int main()
{
	vector<pair<int, int> > v;//vector记录左右端点的位置
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int x, y;
		scanf("%d %d", &x, &y);
		if (y < x)
			swap(x, y);
		v.push_back(make_pair(y, x));
	}
	sort(v.begin(), v.end());//先按小的位置排序，一样的再比打的
	vector<bool> vis(n, false);
	vector<int> ans;
	for (int i = 0; i < n; ++i) {
		if (vis[i])
			continue;
		ans.push_back(v[i].first);
		for (int j = i + 1; j < n; ++j) {
			if (v[j].second <= v[i].first) {
				vis[j] = true;//标记下来
			}
		}
	}
	printf("%d\n", ans.size());//输出k的个数
	for (auto i : ans) {
		printf("%d ", i);//输出k可能的数
	}
	puts("");
	return 0;
}
```




---

## 作者：Allanljx (赞：1)

## 思路

因为要让 $k$ 最小，所以我们可以想到用贪心求 $k$ 的最小值和位置。先用左端点排序，将 $rr$ 赋值为 $r_1$，当 $r_i\leq r_{i-1}$ 时，就需要更新 $rr$ 为 $r_i$，当 $l_i\ge rr$ 时，就需要一个新的点。第 $i$ 条线段的左端点比 $rr$ 大时就需要再加一个新的点。

#### 注意：题目不保证 $l_i\leq r_i$。

## 代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,ans=1,top,b[1005];
struct node
{
	int l,r;
}a[1005];
bool cmp(node &aa,node &bb)
{
	if(aa.l==bb.l) return aa.r<bb.r;
	else return aa.l<bb.l;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].l>>a[i].r;
		if(a[i].r<a[i].l) swap(a[i].l,a[i].r);//l[i]不一定比r[i]小
	}
	sort(a+1,a+n+1,cmp);
	int rr=a[1].r;
	for(int i=2;i<=n;i++)
	{
		if(a[i].l>rr) ans++,b[++top]=rr,rr=a[i].r;
		if(rr>a[i].r) rr=a[i].r;
	}
	cout<<ans<<endl;
	for(int i=1;i<ans;i++) cout<<b[i]<<' ';
	cout<<rr;//不要忘记最后一个点
	return 0;
}
```


---

## 作者：皮卡丘最萌 (赞：1)

本题第一篇题解。

首先看到总共只有$10^3$条线段，且坐标绝对值不超过$10^4$，所以可以直接利用贪心。

先对每条线段按**右端点从小到大**排序。

接着，判断每一条线段是否被标记。

对于每一条未标记的线段，**标记最右端**。这是因为如果你标记了这一条线段，肯定是标记最右端最优，这样才可以标记更多的其他线段。

**注意事项**：

1.这些线段中有些线段需要反转，例如样例中的$4$ $2$，就应该特判。

2.坐标可能为负数(翻译中并未说明)。

代码：
```pascal
var n,i,j,ans:longint; flag:boolean;
f:array[-10001..10001] of boolean;  //负数坐标
a,b,c:array[0..100001] of longint;
procedure sort(l,r: longint);
      var i,j,x,y: longint;
      begin
         i:=l;  j:=r;
         x:=b[(l+r) div 2];
         repeat
           while b[i]<x do inc(i);
           while x<b[j] do dec(j);
           if not(i>j) then
             begin
                y:=a[i];a[i]:=a[j];a[j]:=y;
                y:=b[i];b[i]:=b[j];b[j]:=y;
                inc(i); j:=j-1;
             end;
         until i>j;
         if l<j then sort(l,j);
         if i<r then sort(i,r);
      end;          //按右端点从小到大排序

begin
readln(n);
for i:=1 to n do
  begin
  readln(a[i],b[i]);
  if a[i]>b[i] then
    begin a[0]:=a[i];a[i]:=b[i];b[i]:=a[0]; end;
                          //翻转线段
  end;
sort(1,n);
for i:=1 to n do
  begin
  flag:=false;
  for j:=a[i] to b[i] do
    if f[j] then
      begin flag:=true; break; end;  
                       //判断是否被标记
  if flag then continue;
  inc(ans); c[ans]:=b[i]; f[b[i]]:=true;
                       //标记最右的端点并保存
  end;
writeln(ans);
for i:=1 to ans do write(c[i],' ');  //输出答案
end.
```


---

## 作者：Special_Tony (赞：0)

# 思路
首先在看这题前你得学会差分约束，类似 P1250。

先建立几个不等式（$a_x$ 表示 $1\sim x$ 中最少有几个点）：
1. $a_{x+1}-a_x\ge0$（相邻的点最少不加点）；
1. $a_x-a_{x+1}\ge-1$（相邻的点里最多 $1$ 个点）；
1. $a_r-a_{l-1}\ge1$（线段里至少 $1$ 个点）。

就建这么几条边跑一个 SPFA 就行啦！
# 注意事项
首先可能 $l>r$，建边前要先交换。

然后 $l,r$ 可能是负数，可以先在建边时 $+10001$，输出时减掉。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n, m, x, y, dis[20005];
vector <pii> v[20005];
bitset <20005> vis;
queue <int> q;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> m;
	while (m --) {
		cin >> x >> y;
		if (x > y)
			swap (x, y);
		x += 10001, y += 10001;
		v[x - 1].push_back ({y, 1});
		n = max (n, y);
	}
	for (int i = 0; i < n; ++ i)
		v[i].push_back ({i + 1, 0}), v[i + 1].push_back ({i, -1});
	fill (dis + 1, dis + 1 + n, -1);
	q.push (0);
	while (! q.empty ()) {
		x = q.front ();
		q.pop ();
		vis[x] = 0;
		for (pii& i : v[x])
			if (i.second + dis[x] > dis[i.first]) {
				dis[i.first] = dis[x] + i.second;
				if (! vis[i.first])
					q.push (i.first), vis[i.first] = 1;
			}
	}
	cout << dis[n] << '\n';
	for (int i = 1; i <= n; ++ i)
		if (dis[i] > dis[i - 1])
			cout << i - 10001 << ' ';
	return 0;
}
```

---

## 作者：_lxy_ (赞：0)

### 题意

有 $n$ 条线段在一条直线上，问最少找几个点使每条线段上至少有一个点。

### 分析

一道贪心题。我们先按左端点从小到大排序，记录一下当前需要新取的点的坐标，初始值是第一条线段的右端点的坐标。对于一条新加进来的线段，如果这条线段的右端点比当前点靠左，为了使这条线段上也有一个点，需要把当前点的坐标更新为这条线段的右端点；如果这条线段的左端点比当前点靠右，为了保证全局最优，需要新取一个点，坐标为这条线段的右端点。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=10007;
inline void qread(){}template<class T1,class ...T2>
inline void qread(T1 &IEE,T2&... ls)
{
	register T1 x=0;register bool f=false;char ch=getchar();
	while(ch<'0') f|=(ch=='-'),ch=getchar();
	while(ch>='0') x=(x*10)+(ch^48),ch=getchar();
	x=(f?-x:x);IEE=x;qread(ls...);
}
int n;
struct node
{
	int l,r;
	node(){;}
	node(int _l,int _r):l(_l),r(_r){}
	bool operator < (const node &o)const{return l<o.l;}
};
vector<node>a;
vector<int>ans;
int main()
{
	qread(n);int i,j,t;
	for(i=0;i<n;i++) 
	{
		int x,y;qread(x,y);
		if(x>y) swap(x,y);
		a.push_back(node{x,y});
	}
	sort(a.begin(),a.end());
	int now=a[0].r;
	for(i=1;i<n;i++)
	{
		if(now>a[i].r) now=a[i].r;
		else if(a[i].l>now) ans.push_back(now),now=a[i].r;
	}
	ans.push_back(now);
	printf("%d\n",ans.size());
	for(auto i:ans) printf("%d ",i);
	return 0;
}
```



---

## 作者：zsyyyy (赞：0)

# CF22D 1900 贪心

## 题意

在坐标轴上给定 $n$ 条线段，有 $k$ 个点，使这 $n$ 条线段都至少有一个点在其上面（恰在端点也行）。

求 $k$ 的最小值，并给出一个 $k$ 最小时的方案。

## 思路

先将所有线段按右端点排序，在一段区间中，如果需要找一个点 $x$ 使得该点在这条线段上，为了使 $k$ 最小，肯定是希望 $x$ 能够同时在后面的线段上。因为已经将这些线段按照右端点排序了，所以选该区间的右端点为 $x$ 一定是最优的。

原因：在按照右端点排序的前提下，如果该区间的某一个点（非右端点）可以使得后面的某些线段也满足有一个点在上面，那么该区间的右端点也一定可以。

注意：判断右端点是否大于左端点，如果不是就要交换。

时间复杂度：$O(n)$



## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAX=1005;
int n,last,cnt,ans[1000005];
struct node
{
	int l,r;
}t[MAX];
bool cmp(node x,node y)
{
	return x.r<y.r;
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&t[i].l,&t[i].r);
		if(t[i].l>t[i].r)  swap(t[i].l,t[i].r);
	}
	sort(t+1,t+n+1,cmp); //按右端点排序
	last=LONG_LONG_MAX;
	for(int i=1;i<=n;i++)
	{
		if(last<=t[i].r&&last>=t[i].l)  continue; //该区间已被包含
		ans[++cnt]=t[i].r; //记录
		last=t[i].r; //选定该区间的右端点
	}
	printf("%lld\n",cnt);
	for(int i=1;i<=cnt;i++)  printf("%lld ",ans[i]);
	return 0;
}
```


---

