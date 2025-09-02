# Nested Segments

## 题目描述

##### 【题目大意】：

你得到了一个序列$a_1,a_2,a_3...a_n$，表示$n$个区间。你的任务是求出一对$(i,j)$，表示区间$j$包含区间$i$（注意是区间$j$包含$i$）。

我们定义区间$[l_2,r_2]$包含区间$[l_1,r_1]$当且仅当$l_1 \geq l_2$且$r_1 \leq r_2$。比如区间$[2,5]$包含区间$[3,5]$，因为$3 \geq 2,5 \leq 5$。再比如区间$[2,5]$不包含区间$[1,4]$，因为$1<2$。

输出一对$(i,j)$表示答案。如果答案不唯一，则输出任意一组解即可（所以本题有`SPJ`）。如果无解，则输出`-1 -1`。

--------------------------------------

## 样例 #1

### 输入

```
5
1 10
2 9
3 9
2 3
2 9
```

### 输出

```
2 1
```

## 样例 #2

### 输入

```
3
1 5
2 6
6 20
```

### 输出

```
-1 -1
```

# 题解

## 作者：caibet (赞：6)

### 题意：

给你 $n$ 个区间 $[l_1,r_1],[l_2,r_2],\dots,[l_n,r_n]$，求两个有包含关系的区间。

### 解法：

既然要求两个区间包含，那就一个个枚举好了？

然而这样是不行的，$3\times 10^5$ 的数据规模不允许。

因此我们需要另想办法。

考虑将所有区间排序，使一个区间如果包含了其他区间，那么一定有一个被包含的区间在原区间前一个位置处。那么排序的依据是什么呢？

如果要让一个区间 $a$ 尽可能包含另一个区间 $b$，则要让 $a$ 的左边界尽量在左，右边界尽量向右。因此我们推出了比较函数 `cmp()`：

```cpp
bool cmp(node x,node y){
	if(x.l!=y.l) return x.l<y.l;
	return x.r>y.r;
}
```

接下来问题就很好解决了。注意，因为题目要求输出的是原来的序号，所以结构体还需要记录一下原来的序号。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int l,r,id;//记录一下原来的编号
} a[314514];
bool cmp(node x,node y){
	if(x.l!=y.l) return x.l<y.l;
	return x.r>y.r;
}
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].l>>a[i].r;
		a[i].id=i;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=2;i<=n;i++){
		if(a[i-1].r>=a[i].r&&a[i-1].l<=a[i].l){//判断区间是否包含
			cout<<a[i].id<<' '<<a[i-1].id<<endl;//输出原位置
			return 0;
		}
	}
	cout<<"-1 -1";//没辙了
	return 0;
}
```


---

## 作者：__AFO__ (赞：2)

## 题解
[题目传送门](https://www.luogu.com.cn/problem/CF976C)

这是一道看区间包含的问题，而这道题最简单的做法就是把外围区间的 $l$ 和 $r$ 尽量变大，这里我们可以运用排序，来实现。

排序规则：如果左节点一样，右节点更大在前面，否则左节点从小到大排序 。

代码：
```cpp
bool cmp(nn x,nn y){
	 if(x.l==y.l) return x.r>y.r;//如果左节点一样，右节点更大在前面 
	 else return x.l<y.l;//否则左节点从小到大排序 
}
```

排序之后我们就依次寻找是否覆盖即可。

代码：
```cpp
 for(long long i=1;i<n;i++){
    	if(a[i].r>=a[i+1].r&&a[i].l<=a[i+1].l){//区间是否包含 
    		printf("%lld %lld",a[i+1].ii,a[i].ii);//直接输出 
    		return 0;
		}
		
	}
```

这样下来时间复杂度只有一个  $N$ ，比纯暴力 $N^2$ 好多了，如果还看不懂的话建议去看[这篇题解](https://www.luogu.com.cn/article/ddb0fx1q) 。

---

## 作者：龙之吻—水货 (赞：2)

这道题要找一个区间包含另一个区间，直接找是n方的，3e5基本上是凉了~~不过如果你可以n方过百万的话当我没说~~。

那么，我们思考一下，如果一个区间包含另一个区间的话，那么这个区间的l值更小，r值更大。如果我们按照l值从小到大把区间排序的话，后面的是不可能包含前面的区间的；前面的如果想包含后面的区间，就需要r值比后面的大。

这样，问题就转化为了已知一个数列，找出其中的一组逆序对。

至于如何找一组逆序对，我们思考快排的过程，实际上就是不断地交换逆序对，只需要在快排中魔改一下就好了。

详见代码：
```
#include<cstdio>
#include<algorithm> 

using namespace std;

int x, y, n;

struct Node{
	int l, r, id;
};
Node a[300100], b[300100], r[300100];

bool cmp(Node p, Node q) {
	if (p.l == q.l) {
		return p.r > q.r;
	}
	return p.l < q.l;
}

bool flag;

void qsort(int l,int r){
	int i, j, mid, p;
	i = l;j = r;
	mid = a[(l + r) / 2].r;
	do{
		while (a[i].r < mid) {
        	i++;
        }
		while (a[j].r > mid) {
        	j--;
        }
		if (i <= j){
			if (i != j) {
				printf("%d %d\n", a[j].id, a[i].id);
				exit(0);				
			}
			i++;
            j--;
		}
	} while(i <= j);
	if(l < j) qsort(l,j);
	if(i < r) qsort(i,r);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &a[i].l, &a[i].r);
		a[i].id = i;
	}
	sort(a + 1, a + 1 + n, cmp);
	for (int i = 1; i < n; i++) {
		if (a[i].l == a[i + 1].l && a[i].r == a[i + 1].r) {
			printf("%d %d", a[i].id, a[i + 1].id);
			return 0;
		}
	}
	qsort(1,n);
	printf("-1 -1\n");
	return 0;
}
```

---

## 作者：Fido_Puppy (赞：1)

时隔一年，本蒟蒻又回来看这道之前没做出来的题。~~（蒟蒻叹息）~~

~~然后就把它 AC 了。~~

## Solution

对于两个区间 $(l_1,r_1)$ 和 $(l_2,r_2)$。

当 $l_1\geq l_2$ 并且 $r_1\le r_2$ 时，区间 $(l_1,r_1)$ 包含在 $(l_2,r_2)$ 内。

所以我们先按 $l$ 排序。

$l$ 小的在前，如果 $l$ 相同 $r$ 大的在前。

这样能保证对于第 $i$ 个区间，只有第 $x\ (i\le x\le n)$ 个区间可能被它包含。

然后我们要求的就是判断对于一个 $i$ 是否存在一个 $x$，使得 $r_x\le r_i$ 并且 $x>i$。

我们就可以用一个树状数组来判断。

对每一个可能的数加上 $1$，如果查询到前 $r_i$ 个数的和大于 $0$ 则说明有。

退出循环后暴力搜一下即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define UP(l,i,a,b) for(l i=a;i<=b;i++)
const int N=3e5+10;
struct node {
	int l,r,id;
}a[N];
int d[N],n,x=0,y=0;
bool flag=false;
struct Tree {
	int t[N];
	inline void clear() {
		memset(t,0,sizeof(t));
	}
	inline int lowbit(int x) {
		return x&(-x);
	}
	inline void change(int x,int v) {
		while (x<=n) {
			t[x]+=v;
			x+=lowbit(x);
		}
	}
	inline int query(int x) {
		int ans=0;
		while (x>0) {
			ans+=t[x];
			x-=lowbit(x);
		}
		return ans;
	}
}T;
inline bool cmp(node a,node b) {
	return a.l<b.l||a.l==b.l&&a.r>b.r;
}
int main() {
	IOS; cin>>n; UP(int,i,1,n) cin>>a[i].l>>a[i].r,d[i]=a[i].r,a[i].id=i;
	sort(d+1,d+n+1); int M=unique(d+1,d+n+1)-d-1;
	UP(int,i,1,n) a[i].r=lower_bound(d+1,d+n+1,a[i].r)-d; // 由于数据范围为 1e9，所以需要离散化。
	sort(a+1,a+n+1,cmp);
	T.clear(); UP(int,i,1,n) T.change(a[i].r,1);
	UP(int,i,1,n) {
		T.change(a[i].r,-1);
		if (T.query(a[i].r)) {flag=true; x=i; break;}
	}
	if (flag==false) {
		cout<<"-1 -1"<<endl; return 0;
	}
	UP(int,i,x+1,n) if (a[i].r<=a[x].r) {
		y=i; break;
	}
	cout<<a[y].id<<" "<<a[x].id<<endl;
	return 0;
}
```
完结撒花 の_^

---

## 作者：EternalAlexander (赞：1)

估计是做复杂了。当时半夜头发昏只想得到这么搞。

首先按左端点排序，然后从左到右扫一遍。那么对于每一个区间，如果在所有左端点小于等于它的左端点的区间的区间中存在右端点大于等于它的右端点的区间，那么它就是被那个区间包含的。

用堆搞一搞就好了。最后还要判一下两个区间是否是同一个区间。

```cpp
#include <cstdio>
#include <queue>
#include <algorithm>

struct segment {
	int l, r, id;
} a[4000000];

int cmp(segment p, segment q) {
	if (p.l!=q.l) return p.l<q.l;
	else return p.r>q.r;
}  bool operator < (segment a, segment b) {
    return a.r<b.r;
}

int main() {
	int l, r;
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d %d", &l, &r);
		a[i].l=l; a[i].r=r; a[i].id=i;
	}std::sort(a+1, a+n+1, cmp);
	std::priority_queue <segment> q;
	l=1;r=1; int last = a[1].l; int New;
	//for (int i = 1; i <= n; ++i) printf("%d %d\n", a[i].l, a[i].r);
	q.push(a[1]);
	while (l<=n) {
		r++;
		New=a[r].l;
		while (a[r].l==New&&r<=n+1) {
			if (r<=n) {
				q.push(a[r]);
			//	printf("push > %d %d-%d\n", a[r].id, a[r].l, a[r].r);
			}r++;
		}r--; 
	//	printf("%d-%d\n", l+1, r);
		for (int i =l+1;i<=r&&i<=n;++i) {
			segment s = q.top();
			if (s.r>=a[i].r) {
				if (s.id!=a[i].id) {
					printf("%d %d", a[i].id, s.id);
					return 0;
				} else {
					if (!q.empty()) {
						q.pop();
						segment s2 = q.top();
						if (s2.r>=a[i].r) {
							printf("%d %d", a[i].id, s2.id);
							return 0;
						}q.push(s);
					}
				}
			}
		}l=r;
	}printf("-1 -1");
}
```

~~会不会被叉呀~~

---

## 作者：Addicted_Game (赞：0)

# [传送门](https://www.luogu.com.cn/problem/CF976C)

## 题目大意
给定 $n$ 个区间，找两个区间完全包含。

## 思路
我看到这道题有一种似曾相识的感觉，很像贪心的入门题。先按照左端点从小到大排序，左端点相同再按照右端点从大到小，再找一个区间作为大区间。当大区间无法包含时就进行更新。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct node{
	int l,r,num;
}a[300005];
bool cmp(node x,node y){
	if(x.l!=y.l) return x.l<y.l;
	return x.r>y.r;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i].l,&a[i].r);
		a[i].num=i;
	}
	sort(a+1,a+n+1,cmp);
	int now=1;
	for(int i=2;i<=n;i++){
		if(a[i].r<=a[now].r){
			printf("%d %d",a[i].num,a[now].num);
			return 0;
		}
		if(a[i].r>a[now].r){
			now=i;
		}
	}
	printf("-1 -1");
	return 0;
}
```

---

## 作者：DHT666 (赞：0)

## 题意

[传送门](https://www.luogu.com.cn/problem/CF976C)

给出一个长度为 $N$ 的区间：$(l_1,r_1),(l_2,r_2),…,(l_n,r_n)$，想让你求出一对数 $i$ 和 $j$，使得 $(l_i,r_i)$ 被 $(l_j,r_j)$ 所包含，即 $l_j \le l_i$ 且 $r_i \le l_i$，若无解，输出 `-1 -1`。

## 思路

如果暴力的话，$1\le N\le 3\times 10^5$，$O(N^2)$ 显然超时

于是考虑区间问题，按**左端点大到小**，**右端点小到大**排序，这样排名**越靠前**的左端点就大，右端点就小，更容易被后面的线段所覆盖，排序时间复杂度 $O(n\log n)$。

如果排序后还是没有找到，就说明无解。

注意题目想要的答案是它给出的编号，注意在排序的时候存编号。

## 代码

~~~cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 3e5 + 10;

int n;

struct node {
	int l,r,id;
}a[N];

bool cmp(node x,node y) {
	if(x.l == y.l) return x.r < y.r; // 相等排右端点：从小到大
	return x.l > y.l; // 优先排左端点：从大到小
}

int main() {
	cin >> n;
	for(int i = 1;i <= n;i++) {
		cin >> a[i].l >> a[i].r;
		a[i].id = i; // 存编号
 	}
	
	sort(a + 1,a + 1 + n,cmp);
	
	for(int i = 1;i < n;i++) {
		if(a[i].r <= a[i + 1].r && a[i].l >= a[i + 1].l) { // i 被 i + 1 包含
			cout << a[i].id << " " << a[i + 1].id;
			return 0;
		}
	}
	
	cout << "-1 -1"; // 无解
	
	return 0;
}
~~~

---

## 作者：nyC20 (赞：0)

# 思路
很简单的区间覆盖，但是暴力过不了一点。然后考虑优化，将存左右段点的数组按左端点从小到大排序，如果左端点相等，则按右端点从大到小排序，这样就只需判断线段 $a_i$ 能否被 $a_{i-1}$ 包含，然后输出答案。注意，排序后数组下标会被改变，需要开结构体存数组初始下标。
# 代码
```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
struct node{
	int l, r, num;
}a[300003];
bool cmp(node a, node b){
	if(a.l!=b.l)return a.l<b.l;
	else return a.r>b.r;
}
int n;
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i].l,&a[i].r);
		a[i].num=i;
	}
	sort(a+1,a+1+n,cmp);
	for(int i=2;i<=n;i++){
		if(a[i].l>=a[i-1].l&&a[i].r<=a[i-1].r){
			printf("%d %d",a[i].num,a[i-1].num);
			return 0;
		}
	}
	printf("-1 -1");
	return 0;
}
```

---

## 作者：louliu (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF976C)

### 分析

首先想到的就是暴力，开个结构体记录首，尾，下标，直接就来了一个二重循环：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,n,m,x,y,ans,wps,o;
struct node{
	int x,y,z;
}b[1000005];
bool cmp(node a,node b){
	return a.x<b.x;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>a;
	for(long long i=1;i<=a;i++){
		cin>>b[i].x>>b[i].y;
		b[i].z=i;
	}
	sort(b+1,b+a+1,cmp);
	for(long long i=1;i<=a;i++){
		o=0;
		for(long long j=1;j<=a;j++){
			if(i==j)continue;
			if(b[j].x<=b[i].x){
				if(b[j].y>=b[i].y){
					cout<<b[i].z<<" "<<b[j].z;
					return 0;
				}				
			}
			else{
				break;	
			}
		}
	}
	cout<<-1<<" "<<-1;
	return 0;
}
```

结果在第十二个数据点卡住了！

##### Time limit exceeded on test 12

随后想到的是一重循环，因为排了序，所以只用比较前后这两个比较相近的数就可以了！

### 注意边界

核心代码如下：

```cpp
	for(long long i=2;i<=a;i+=2){
		if(b[i-1].x<=b[i].x&&b[i-1].y>=b[i].y){
			cout<<b[i].z<<" "<<b[i-1].z;
			return 0;
		}
	}
```

但又错了！

##### Wrong answer on test 17

又思考了一下，其实还是边界问题，一次 $i+2$ 那就会忽略一些情况，所以最终代码如下：

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,n,m,x,y,ans,wps,o;
struct node{
	int x,y,z;
}b[1000005];
bool cmp(node a,node b){
	if(a.x!=b.x)return a.x<b.x;
	return a.y>b.y;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>a;
	for(int i=1;i<=a;i++){
		cin>>b[i].x>>b[i].y;
		b[i].z=i;
	}
	sort(b+1,b+a+1,cmp);
	for(int i=2;i<=a;i++){//修改的地方
		if(b[i-1].y>=b[i].y&&b[i-1].x<=b[i].x){
			cout<<b[i].z<<" "<<b[i-1].z;
			return 0;
		}
	}
	cout<<-1<<" "<<-1;
	return 0;
}
```

---

## 作者：ZHANGyutao123 (赞：0)

# CF976C题解
## [传送门](https://www.luogu.com.cn/problem/CF976C)
## 题目大意
给定一个由一维区间组成的序列 $a_{1},a_{2},...,a_{n}$，其中区间编号为 $1$ 到 $n$。

你的任务是找到两个不同的索引 $i$ 和 $j$，使得区间 $a_{i}$ 在区间 $a_{j}$ 内。


如果区间 $[l_{1},r_{1}]$ 在区间 $[l_{2},r_{2}]$ 内部，那么满足条件 $l_{1} \geq l_{2}$ 且 $r_{1} \leq r_{2}$。


输出索引 $i$ 和 $j$。如果有多个答案，请输出任意一个。如果不存在答案，请输出 `-1 -1`。

## 过程分析
暴力。

题目要求我们找出在给定区间序列中，一个区间包含另一个区间的情况。首先需要遍历所有可能的组合，判断其中一个区间是否包含另一个区间。

我们可以使用两层循环来遍历所有可能的组合。外层循环用于遍历所有区间，内层循环用于判断当前区间是否包含其他区间。

对于每个区间 $i$，我们将通过内层循环从头到尾遍历所有区间 $j$。如果区间 $j$ 的左边界小于等于区间 $i$ 的左边界，且区间 $j$ 的右边界大于等于区间 $i$ 的右边界，那么区间 $i$ 就包含在区间 $j$ 内。

如果找到了满足条件的区间 $i$ 和 $j$，我们可以立即输出结果。


## 参考代码
```cpp
#include <iostream>
#include <vector>
using namespace std;

struct Interval {
    int left;
    int right;
};

vector<int> findContainedIntervals(const vector<Interval>& intervals) {
    vector<int> result;

    for (int i = 0; i < intervals.size(); i++) {
        for (int j = 0; j < intervals.size(); j++) {
            if (i != j && intervals[j].left <= intervals[i].left && intervals[i].right <= intervals[j].right) {
                result.push_back(i + 1);
                result.push_back(j + 1);
                return result;
            }
        }
    }
    
    return result;
}

int main() {
    int n;
    cin >> n;

    vector<Interval> intervals(n);
    for (int i = 0; i < n; i++) {
        cin >> intervals[i].left >> intervals[i].right;
    }

    vector<int> result = findContainedIntervals(intervals);

    if (result.empty()) {
        cout << "-1 -1";
    } else {
        cout << result[0] << " " << result[1];
    }

    return 0;
}
```


---

## 作者：cppcppcpp3 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF976C)。

按照 $r$ 从小到大、$l$ 从大到小的（$r$ 为第一关键字）的顺序对 $n$ 个区间进行排序。这样可以保证越靠后的区间右端点越大；同时相等的 $r$，越靠后的 $l$ 越小，越有可能成为 $j$。

所以只需枚举一次所有区间，判断 $\max\limits_{j=1}^{i-1}l_j$ 是否大于等于 $l_i$。而前面这个东西在扫的过程中用一个变量维护即可。

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
const int N=3e5+5;
const int inf=1e9+7;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1; c=getchar();}
	while(isdigit(c)){x=x*10+c-48,c=getchar();}
	return x*f;
}

int n,lst,pos;

struct Line{
	int l,r,id;
	bool operator < (const Line &L) const{
		return r^L.r ? r<L.r : l>L.l;
	}
}a[N];

main(){
	n=wrd();
	for(int i=1;i<=n;++i) a[i]={wrd(),wrd(),i};
	sort(a+1,a+n+1);
	
	for(int i=1;i<=n;++i){
		if(lst>=a[i].l) return printf("%d %d",a[pos].id,a[i].id),0;
		else lst=a[i].l,pos=i;
	}
	return puts("-1 -1"),0;
}
```

---

## 作者：一只大龙猫 (赞：0)

我们可以先将区间先按左端点从小到大排序，如果左端相同，则按右端点从大到小排序。

此时不难看出，如果排序后的区间 $i$ 将区间 $j$ 包含（$i < j$），那么 $i$ 的右端点一定**大于等于** $j$ 的右端点。

有没有感觉非常眼熟？

这与[P1908 逆序对](https://www.luogu.com.cn/problem/P1908)几乎一模一样！

所以，我们可以使用树状数组从 $1$ 到 $n$ 去统计逆序对的数量，当出现逆序对时，则遍历整个数组去查找具体是哪一对是逆序对。如果逆序对的数量一直为 $0$，则直接输出`-1 -1`。

同时，还要注意下面三点：

1. P1908 中的“逆序对”指的是“序列中 $a_i > a_j$ 且 $i<j$ 的有序对”，这里则要改成`str[i].r>=str[j].r`。相应的，原来的代码中`i-sum(a[i])`也要相应地改为`i-sum(str[i].r-1)-1`。（至于为什么后面会讲。）

2. 由于 $l$ 与 $r$ 的最大值可以达到 $10^9$，开一个这么大的数组肯定会爆空间，所以我们需要**离散化**。如果不了解离散化是什么的话，可以看看[这篇](https://www.cnblogs.com/cytus/p/8933597.html)博客。

3. 输出时要输出**原来的编号**，而不是排序后的下标。~~（我不会告诉你我在这里卡了将近一小时的……）~~

代码如下：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,c[500001],ans,t[500001],m;
struct node{
    int l,r,id;
    bool operator<(node x)const{
        return l==x.l?r>x.r:l<x.l;
    }
}str[500001];
inline int lowbit(int x){
    return x&-x;
}
void add(int i,int x){
    while(i<=n){
        c[i]+=x;
        i+=lowbit(i);
    }
    return;
}
int sum(int i){
    int s=0;
    while(i>0){
        s+=c[i];
        i-=lowbit(i);
    }   
    return s;
}
void find(int x){
    for(int i=1;i<x;i++){
        if(str[i].r>=str[x].r){
            cout<<str[x].id<<" "<<str[i].id;
            return;
        }
    }
}
void work(){
    for(int i=1;i<=n;i++){
        add(str[i].r,1);
        if(i-sum(str[i].r-1)-1>=1){//与排序后的第i个区间的右端点组成逆序对的数量 
        	find(i);
        	return;
		}
	}
    cout<<"-1 -1"<<endl;
    return;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>str[i].l>>str[i].r;
        str[i].id=i;
        t[i]=str[i].r;
    }
    sort(str+1,str+n+1);
    /*离散化*/
    sort(t+1,t+n+1);
    int m=unique(t+1,t+n+1)-t-1;
    for(int i=1;i<=n;i++){
        str[i].r=lower_bound(t+1,t+m+1,str[i].r)-t;
    }
    work();
    return 0;
}
```

时间复杂度：

排序、离散化和树状数组的时间复杂度都是 $O(n \log n)$，所以整个程序的时间复杂度就是 $O(n \log n)$。

注：

`sum(str[i].r-1)`统计的是所有小于`str[i].r`的数的个数，`i-sum(str[i].r-1)`自然就是大于等于`str[i].r`的数的个数了。但要注意，刚刚我们把`str[i].r`插入了树状数组，`i-sum(str[i].r-1)`会把`str[i].r`自己也算进去，所以我们要减去`str[i].r`自己这一个数，即`i-sum(str[i].r-1)-1`。

`lowbit()`、`add()`和`sum()`函数都是树状数组的函数，如果还不是很了解树状数组，建议看看[这篇](https://www.cnblogs.com/xenny/p/9739600.html)博客，并做一下 P1908。

为了提高效率，结构体`node`中的`operator<()`函数重载了运算符`operator<`（小于号）， 并使用了三目运算符进一步提高效率。如果还不了解，可以看看[这篇](https://www.runoob.com/cplusplus/cpp-overloading.html)教程（重载运算符）与[这篇](https://www.cnblogs.com/yjd_hycf_space/p/7881345.html)博客。

---

## 作者：linwenchen (赞：0)

这题题意很明显，难点在于数据较大，n*n大小的模拟比较会超时，所以我们得想个方法来优化一下。

很显然我们可以先按左区间来从大到小排序，左区间(l)大的明显是不可能包含左区间小的，比如 

3 5

1 4

3 5很明显是包含不了1 4这个区间的因为左区间3比1大。

同时如果左区间相等的我们就按右区间(r)递增来排序，也就是如果i和i+1的左区间相等的话，那么右区间大的排在后面,

i: 2 3

i+1: 2 4

(可以发现i和i+1的左区间如果相等的话，那一定有答案的，而且答案就是i和i+1)

但是可能会存在都不相等的情况，这时dl们祭出了线段树，堆等数据结构。。。而看不懂的我就自闭了，然后想了一下，其实并不需要！

如果存在解a b(0 <= a,b < n)的话，那么肯定有r(b) < r(a)！

因为排序后已经保证l(a)<l(b)了，也就是存在ra<rb的情况就行了。

那么我们只需要在从l最大的也就是数组的第一个元素开始，将其存为temp,然后往后扫，遇到r比它小的就更新temp，遇到比它r大的直接输出答案，扫完一遍还没有答案，说明不存在，直接输出-1 -1.


```c
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define MAX 300005
struct Node{
	int l,r;//左右区间
	int index;
}N[MAX];
bool cmp(Node a,Node b)
{
	if(a.l > b.l)return 1;
	else if(a.l == b.l)return a.r < b.r;
	return 0;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 0;i<n;i++)
	{
		scanf("%d %d",&N[i].l,&N[i].r);
		N[i].index = i+1;
	}
	sort(N,N+n,cmp);
	Node temp;
	for(int i = 0;i < n;i++)
	{
		if(i<n-1 && N[i].l == N[i+1].l)
		{
			printf("%d %d",N[i].index,N[i+1].index);
			return 0;
		}
		if(i && N[i].r >= temp.r)
		{
			printf("%d %d",temp.index,N[i].index);
			return 0;
		}
		else
			temp = N[i];//此时0~i里r最小的
	}
	printf("-1 -1");
	return 0;
}
```


---

## 作者：___nyLittleT___ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF976C)  
## 思路
排序+枚举。首先一个一个比较肯定是要超时的，所以我们考虑用排序解决。  
时间复杂度 $\mathcal O(n \log n)$。  

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct line {
	long long l;
	long long r;
	int idx;
} a[300005];
bool cmp(line a,line b) {//按照题目要求排序
	if(a.l!=b.l) return a.l>b.l;
	return a.r<b.r;
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++) {
		scanf("%lld%lld",&a[i].l,&a[i].r);
		a[i].idx=i;//存原来的编号
	}
	sort(a+1,a+1+n,cmp);
	for(int i=2; i<=n; i++) {
		if(a[i-1].l>=a[i].l&&a[i-1].r<=a[i].r) {//检查相邻两个
			printf("%d %d",a[i-1].idx,a[i].idx);
			return 0;
		}
	}
	printf("-1 -1");
	return 0;
}
```

---

