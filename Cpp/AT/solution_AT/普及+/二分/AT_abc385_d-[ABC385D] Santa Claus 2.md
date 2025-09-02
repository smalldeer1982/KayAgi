# [ABC385D] Santa Claus 2

## 题目描述

在二次元平面上有 $N$ 个点 $(X_1,Y_1),\ldots,(X_N,Y_N)$ 建有房子。

最初，圣诞老人在点 $(S_x,S_y)$。圣诞老人将按照序列 $(D_1,C_1),\ldots,(D_M,C_M)$ 进行以下行动：

- 对于 $i=1,2,\ldots,M$，按顺序进行以下移动：
  - 设 $(x,y)$ 为他当前所在的点。
      - 如果 $D_i$ 是 `U`，则从 $(x,y)$ 沿直线移动到 $(x,y+C_i)$。
      - 如果 $D_i$ 是 `D`，则从 $(x,y)$ 沿直线移动到 $(x,y-C_i)$。
      - 如果 $D_i$ 是 `L`，则从 $(x,y)$ 沿直线移动到 $(x-C_i,y)$。
      - 如果 $D_i$ 是 `R`，则从 $(x,y)$ 沿直线移动到 $(x+C_i,y)$。

请找出他完成所有行动后所在的点，以及他在行动过程中经过或到达的不同房子的数量。如果多次经过同一个房子，只计数一次。

## 说明/提示

- $1 \leq N \leq 2\times 10^5$
- $1 \leq M \leq 2\times 10^5$
- $-10^9 \leq X_i,Y_i \leq 10^9$
- $(X_i,Y_i)$ 互不相同
- $-10^9 \leq S_x,S_y \leq 10^9$
- 点 $(S_x,S_y)$ 没有房子
- 每个 $D_i$ 是 `U`、`D`、`L`、`R` 之一
- $1 \leq C_i \leq 10^9$
- 所有给定数字均为整数

**【样例 #1 解释】**

圣诞老人的行动如下图所示：

![](https://img.atcoder.jp/abc385/f3d0f313d3b20c135af60ca6eb04900d.png)

- $D_1=$ `L`，所以他从 $(3,2)$ 直线移动到 $(3-2,2)$。在此期间，他经过 $(2,2)$ 处的房子。
- $D_2=$ `D`，所以他从 $(1,2)$ 直线移动到 $(1,2-1)$。
- $D_3=$ `R`，所以他从 $(1,1)$ 直线移动到 $(1+1,1)$。在此期间，他经过 $(2,1)$ 处的房子。
- $D_4=$ `U`，所以他从 $(2,1)$ 直线移动到 $(2,1+2)$。在此期间，他经过 $(2,2)$ 处的房子，但该房子已经被经过。

他在行动期间经过或到达的房子数量为 $2$。

**【样例 #2 解释】**

小心溢出。

## 样例 #1

### 输入

```
3 4 3 2
2 2
3 3
2 1
L 2
D 1
R 1
U 2```

### 输出

```
2 3 2```

## 样例 #2

### 输入

```
1 3 0 0
1 1
R 1000000000
R 1000000000
R 1000000000```

### 输出

```
3000000000 0 0```

# 题解

## 作者：Drifty (赞：11)

### Preface

感觉自己的实现很好，交一篇题解。

### Solution

我们分析一下算法的大致流程。我们考虑第一种行走方式，即 $(x,y)\to (x,y+C_i)$ 这种。你会发现 $x$ 不变，那么此时你固定 $x$，找出所有满足 $X_i = x$ 的 $Y_i$，并找出那些满足 $y\le Y_i\le y + C_i$ 的 $Y_i$，并把这些 $(X_i, Y_i)$ 都删掉。其他情况同理。

然后你会发现这很好写，只需要开一个 `map <int, set <int> >`，同时完成了坐标的离散化和统计，删除的时候就在 `set` 上二分找出左边界和右边界直接暴力删就可以了，因为你会发现最多只有 $M$ 个点会被删掉。

时间复杂度 $\mathcal{O}((m + n)\log n)$，可以通过，事实上，最大点只有 400 ms。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using Map = map <int, set <int> >;
vector <int> temp; Map mpx, mpy;
int n, m; i64 x, y, c, ans;
void work (i64 x, i64 y, i64 u, i64 v, Map &i, Map &j) {
    if (!(!i[x].empty() && abs(x) <= (int)1e9 && abs(y) <= (int)1e9)) return ;
    temp.clear(); auto bg = i[x].lower_bound(y + u), ed = i[x].upper_bound(y + v);
    for (auto it = bg; it != ed; ++ it) ans ++, temp.push_back((* it));
    for (auto p : temp) j[p].erase(x), i[x].erase(p);
}
int main() {
    cin.tie(NULL) -> sync_with_stdio(false);
    cin >> n >> m >> x >> y;
    for (int i = 1, u, v; i <= n; i ++)
        cin >> u >> v, mpx[u].insert(v), mpy[v].insert(u);
    for (int i = 1; i <= m; i ++) {
        char op; cin >> op >> c;
        if (op == 'U') work(x, y,  0, c, mpx, mpy), y = y + c;
        if (op == 'D') work(x, y, -c, 0, mpx, mpy), y = y - c;
        if (op == 'L') work(y, x, -c, 0, mpy, mpx), x = x - c;
        if (op == 'R') work(y, x,  0, c, mpy, mpx), x = x + c;
    } return cout << x << ' ' << y << ' ' << ans << endl, 0;
} // C++ 17 gcc 12.2
```

---

## 作者：The_foolishest_OIer (赞：8)

## 前言

独一档做法，没有之一。

本 tj 做法一共使用 $19$ 个二分和 $2$ 棵线段树。

## 过程（上）

我们以 `U` 操作为例。

先进行移动操作，把 $y$ 加上 $c$。

这个操作整个过程中 $x$ 的值没有任何变化。

所以将所有房屋以 $x$ 为第一关键字，以 $y$ 为第二关键字进行从小到大排序，记为 $a$ 数组。

可以发现如果这个过程中经过的所有房屋必是 $a$ 的某个子段。

先二分最左端的 $x$，然后二分最右端的 $x$，因为之前已经进行了移动操作，所以再二分 $y-c$，最后二分 $y$，中间的所有点都被经过。

我们再以 `L` 操作为例。

先进行移动操作，把 $x$ 减去 $c$。

这个操作整个过程中 $y$ 的值没有任何变化。

所以将所有房屋以 $y$ 为第一关键字，以 $x$ 为第二关键字进行从小到大排序，记为 $b$ 数组。

可以发现如果这个过程中经过的所有房屋必是 $b$ 的某个子段。

先二分最左端的 $y$，然后二分最右端的 $y$，因为之前已经进行了移动操作，所以再二分 $x$，最后二分 $x+c$，中间的所有点都被经过。

所以我们就~~理所当然~~的写出了 $4 \times 4 = 16$ 个二分。

给出此部分 `U` 操作代码：


```cpp
y += c;
int L = 1,R = n;
int l = -1,r = -1;
while (L <= R){
	int mid = (L + R) >> 1;
	if (a[mid].first == x) l = mid;
	if (a[mid].first < x){ // 因为找最左端，所以使用 <
		L = mid + 1;
	}else{
		R = mid - 1;
	}
}
if (l == -1) continue; // 如果没有直接跳出
L = 1,R = n;
while (L <= R){
	int mid = (L + R) >> 1;
	if (a[mid].first == x) r = mid;
	if (a[mid].first <= x){ // 因为找最右端，所以使用 <=
		L = mid + 1;
	}else{
		R = mid - 1;
	}
}
if (r == -1 || l > r) continue;
int l2 = -1,r2 = -1;
L = l,R = r; // 区间为横坐标是 x 的范围
while (L <= R){
	int mid = (L + R) >> 1;
	if (a[mid].second < y - c){
		L = mid + 1;
	}else{
		l2 = mid;
		R = mid - 1;
	}
}
if (l2 == -1) continue;
L = l,R = r;
while (L <= R){
	int mid = (L + R) >> 1;
	if (a[mid].second > y){
		R = mid - 1;
	}else{
		r2 = mid;
		L = mid + 1;
	}
}
if (r2 == -1 || l2 > r2) continue;
```
## 过程（下）

接着发现了一个问题，去重（题目说经过多次只算一次）。

把所有操作范围全部丢到线段树里，最后单点查询，如果第 $i$ 个点至少被访问过一次，那么答案加 $1$。

但是，我们有两个数组，我们要把操作 `L` 和 `R` 的所有贡献也全部放到线段树内。

对于所有的 `U` 和 `D` 操作的贡献，放到第一棵线段树进行统计，剩余的放到第二棵线段树统计。

最后对于第 $i$ 座房屋，二分位置，找到这座房屋在 $a$ 数组中的位置，再将这个点在第二棵线段树的信息转移到第一棵线段树。

最后统计答案。

时间复杂度：$O(n \log n)$。

## CODE

共 $348$ 行，长度是 $7463$。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 2e5 + 10;
int T,n,m,x,y;
int sum[N << 2],lzy[N << 2];
int sum2[N << 2],lzy2[N << 2];
pair <int,int> a[N],b[N];
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
bool cmp (pair <int,int> x,pair <int,int> y){
	if (x.first != y.first) return x.first < y.first;
	return x.second < y.second;
} // 第一种排序方法
bool cmp2 (pair <int,int> x,pair <int,int> y){
	if (x.second != y.second) return x.second < y.second;
	return x.first < y.first;
} // 第二种排序方法
void pushup (int o){
	sum[o] = sum[o << 1] + sum[o << 1 | 1];
}
void maketag (int o,int l,int r,int w){
	lzy[o] += w;
	sum[o] += (r - l + 1) * w;
}
void pushdown (int o,int l,int r){
	int mid = (l + r) >> 1;
	maketag(o << 1,l,mid,lzy[o]);
	maketag(o << 1 | 1,mid + 1,r,lzy[o]);
	lzy[o] = 0;
}
void update (int o,int l,int r,int ql,int qr){
	if (ql <= l && r <= qr){
		maketag(o,l,r,1);
		return;
	}
	pushdown(o,l,r);
	int mid = (l + r) >> 1;
	if (ql <= mid) update(o << 1,l,mid,ql,qr);
	if (qr > mid) update(o << 1 | 1,mid + 1,r,ql,qr);
	pushup(o);
}
int query (int o,int l,int r,int x){
	if (l == r)
		return sum[o];
	pushdown(o,l,r);
	int mid = (l + r) >> 1;
	if (x <= mid) return query(o << 1,l,mid,x);
	else return query(o << 1 | 1,mid + 1,r,x);
}
void pushup2 (int o){
	sum2[o] = sum2[o << 1] + sum2[o << 1 | 1];
}
void maketag2 (int o,int l,int r,int w){
	lzy2[o] += w;
	sum2[o] += (r - l + 1) * w;
}
void pushdown2 (int o,int l,int r){
	int mid = (l + r) >> 1;
	maketag2(o << 1,l,mid,lzy2[o]);
	maketag2(o << 1 | 1,mid + 1,r,lzy2[o]);
	lzy2[o] = 0;
}
void update2 (int o,int l,int r,int ql,int qr){
	if (ql <= l && r <= qr){
		maketag2(o,l,r,1);
		return;
	}
	pushdown2(o,l,r);
	int mid = (l + r) >> 1;
	if (ql <= mid) update2(o << 1,l,mid,ql,qr);
	if (qr > mid) update2(o << 1 | 1,mid + 1,r,ql,qr);
	pushup2(o);
}
int query2 (int o,int l,int r,int x){
	if (l == r)
		return sum2[o];
	pushdown2(o,l,r);
	int mid = (l + r) >> 1;
	if (x <= mid) return query2(o << 1,l,mid,x);
	else return query2(o << 1 | 1,mid + 1,r,x);
}
// 线段树
void solve(){
	cin >> n >> m >> x >> y;
	for (int i = 1 ; i <= n ; i++)
		cin >> a[i].first >> a[i].second;
	for (int i = 1 ; i <= n ; i++){
		b[i].first = a[i].first;
		b[i].second = a[i].second;
	}
	sort (a + 1,a + n + 1,cmp);
	sort (b + 1,b + n + 1,cmp2);
    // 维护 a 数组和 b 数组
	for (int i = 1 ; i <= m ; i++){
		char op;
		int c;
		cin >> op >> c;
		if (op == 'U'){
			y += c;
			int L = 1,R = n;
			int l = -1,r = -1;
			while (L <= R){
				int mid = (L + R) >> 1;
				if (a[mid].first == x) l = mid;
				if (a[mid].first < x){
					L = mid + 1;
				}else{
					R = mid - 1;
				}
			}
			if (l == -1) continue;
			L = 1,R = n;
			while (L <= R){
				int mid = (L + R) >> 1;
				if (a[mid].first == x) r = mid;
				if (a[mid].first <= x){
					L = mid + 1;
				}else{
					R = mid - 1;
				}
			}
			if (r == -1 || l > r) continue;
			int l2 = -1,r2 = -1;
			L = l,R = r;
			while (L <= R){
				int mid = (L + R) >> 1;
				if (a[mid].second < y - c){
					L = mid + 1;
				}else{
					l2 = mid;
					R = mid - 1;
				}
			}
			if (l2 == -1) continue;
			L = l,R = r;
			while (L <= R){
				int mid = (L + R) >> 1;
				if (a[mid].second > y){
					R = mid - 1;
				}else{
					r2 = mid;
					L = mid + 1;
				}
			}
			if (r2 == -1 || l2 > r2) continue;
			update(1,1,n,l2,r2);
		}else if (op == 'D'){
			y -= c;
			int L = 1,R = n;
			int l = -1,r = -1;
			while (L <= R){
				int mid = (L + R) >> 1;
				if (a[mid].first == x) l = mid;
				if (a[mid].first < x){
					L = mid + 1;
				}else{
					R = mid - 1;
				}
			}
			if (l == -1) continue;
			L = 1,R = n;
			while (L <= R){
				int mid = (L + R) >> 1;
				if (a[mid].first == x) r = mid;
				if (a[mid].first <= x){
					L = mid + 1;
				}else{
					R = mid - 1;
				}
			}
			if (r == -1 || l > r) continue;
			int l2 = -1,r2 = -1;
			L = l,R = r;
			while (L <= R){
				int mid = (L + R) >> 1;
				if (a[mid].second < y){
					L = mid + 1;
				}else{
					l2 = mid;
					R = mid - 1;
				}
			}
			if (l2 == -1) continue;
			L = l,R = r;
			while (L <= R){
				int mid = (L + R) >> 1;
				if (a[mid].second > y + c){
					R = mid - 1;
				}else{
					r2 = mid;
					L = mid + 1;
				}
			}
			if (r2 == -1 || l2 > r2) continue;
			update(1,1,n,l2,r2);
		}else if (op == 'L'){
			x -= c;
			int L = 1,R = n;
			int l = -1,r = -1;
			while (L <= R){
				int mid = (L + R) >> 1;
				if (b[mid].second == y) l = mid;
				if (b[mid].second < y){
					L = mid + 1;
				}else{
					R = mid - 1;
				}
			}
			if (l == -1) continue;
			L = 1,R = n;
			while (L <= R){
				int mid = (L + R) >> 1;
				if (b[mid].second == y) r = mid;
				if (b[mid].second <= y){
					L = mid + 1;
				}else{
					R = mid - 1;
				}
			}
			if (r == -1 || l > r) continue;
			int l2 = -1,r2 = -1;
			L = l,R = r;
			while (L <= R){
				int mid = (L + R) >> 1;
				if (b[mid].first < x){
					L = mid + 1;
				}else{
					l2 = mid;
					R = mid - 1;
				}
			}
			if (l2 == -1) continue;
			L = l,R = r;
			while (L <= R){
				int mid = (L + R) >> 1;
				if (b[mid].first > x + c){
					R = mid - 1;
				}else{
					r2 = mid;
					L = mid + 1;
				}
			}
			if (r2 == -1 || l2 > r2) continue;
			update2(1,1,n,l2,r2);
		}else{
			x += c;
			int L = 1,R = n;
			int l = -1,r = -1;
			while (L <= R){
				int mid = (L + R) >> 1;
				if (b[mid].second == y) l = mid;
				if (b[mid].second < y){
					L = mid + 1;
				}else{
					R = mid - 1;
				}
			}
			if (l == -1) continue;
			L = 1,R = n;
			while (L <= R){
				int mid = (L + R) >> 1;
				if (b[mid].second == y) r = mid;
				if (b[mid].second <= y){
					L = mid + 1;
				}else{
					R = mid - 1;
				}
			}
			if (r == -1 || l > r) continue;
			int l2 = -1,r2 = -1;
			L = l,R = r;
			while (L <= R){
				int mid = (L + R) >> 1;
				if (b[mid].first < x - c){
					L = mid + 1;
				}else{
					l2 = mid;
					R = mid - 1;
				}
			}
			if (l2 == -1) continue;
			L = l,R = r;
			while (L <= R){
				int mid = (L + R) >> 1;
				if (b[mid].first > x){
					R = mid - 1;
				}else{
					r2 = mid;
					L = mid + 1;
				}
			}
			if (r2 == -1 || l2 > r2) continue;
			update2(1,1,n,l2,r2);
		}
	}
	int ans = 0;
	for (int i = 1 ; i <= n ; i++){
		if (query2(1,1,n,i) == 0) continue; // 如果这个点在第二棵线段树没有任何贡献，直接跳出
		int L = 1,R = n;
		int l = -1,r = -1;
		while (L <= R){
			int mid = (L + R) >> 1;
			if (a[mid].first == b[i].first) l = mid;
			if (a[mid].first < b[i].first){
				L = mid + 1;
			}else{
				R = mid - 1;
			}
		}
		if (l == -1) continue;
		L = 1,R = n;
		while (L <= R){
			int mid = (L + R) >> 1;
			if (a[mid].first == b[i].first) r = mid;
			if (a[mid].first <= b[i].first){
				L = mid + 1;
			}else{
				R = mid - 1;
			}
		} // 二分 x
		if (r == -1 || l > r) continue;
		int id = -1;
		L = l,R = r;
		while (L <= R){
			int mid = (L + R) >> 1;
			if (a[mid].second == b[i].second) id = mid;
			if (a[mid].second <= b[i].second){
				L = mid + 1;
			}else{
				R = mid - 1;
			}
		} // 二分 y
		update(1,1,n,id,id); // 累计答案
	}
	for (int i = 1 ; i <= n ; i++)
		if (query(1,1,n,i) >= 1)
			ans++; // 统计答案
	cout << x << ' ' << y << ' ' << ans << endl;
}
signed main(){
	close();
	T = 1;
	while (T--) solve();
	return 0;
}
```

---

## 作者：hanhoudedidue (赞：5)

**我真不信有谁的比我另类**

赛时因为懒得想一些其它的妙妙做法，第一眼看上去就觉得是扫描线。个人觉得这种做法非常好理解。首先本题肯定是难在第二问，接下来讲解解法以及思考痕迹。

观察样例：

![](https://img.atcoder.jp/abc385/f3d0f313d3b20c135af60ca6eb04900d.png)

可以发现第二问所求就是它给出的点在自己的路线的路线上的个数。

我们把一个点看作是以它为左下角的一个大小为一的方格，这样便可以扫描线了。

然后正着考虑不好想，考虑容斥，先求出自己路线的面积，设其为 $sum$，再求出自己路线和所有的点并在一起的面积，设其为 $k$，答案即为 $n-k+sum$。然后第一问是好求的，这样这题便做完了。

## code:

```cpp
#include<bits/stdc++.h>
#define int long long
#define ls(x) ((x)<<1)
#define rs(x) ((x)<<1|1)
#define mid ((l+r)>>1)
#define lowbit(x) ((x)&(-x))
using namespace std;
const int N=8e5+5;
bool ST;
int n,m,T;

struct rectangle{
    int x,y,X,Y;
}a[N],b[N];
struct line{
    int y,x,X,flag;
}li[N];
bool cmp(line x,line y){
    return x.y<y.y;
}
int yy[N],xx[N];
struct node{
    int l,r,sum,all,tag,res;
}t[N<<2];
void build(int x,int l,int r){
    t[x].l=l,t[x].r=r;
    if(l==r){
        t[x].all=xx[l+1]-xx[l];
        return;
    }
    build(ls(x),l,mid);build(rs(x),mid+1,r);
    t[x].all=t[ls(x)].all+t[rs(x)].all;
}
void add(int x,int l,int r,int sum){
    if(t[x].l>=l&&t[x].r<=r){
        t[x].tag+=sum;
        if(t[x].tag) {
            t[x].sum=t[x].all;
        } 
        else {
            if(t[x].l!=t[x].r) {
                t[x].sum=t[ls(x)].sum+t[rs(x)].sum;
            }
            else t[x].sum=0;
        }
        return;
    }
    if(t[x].l>r||t[x].r<l) return;
    add(ls(x),l,r,sum);add(rs(x),l,r,sum);
    if(t[x].tag) t[x].sum=t[x].all;
    else t[x].sum=t[ls(x)].sum+t[rs(x)].sum;
}
int solve(int nn){
	xx[0]=yy[0]=0;int mm;int res=0;
    for(int i=1;i<=nn;i++){
//        cin>>a[i].x>>a[i].y>>a[i].X>>a[i].Y;
        xx[++xx[0]]=a[i].x;xx[++xx[0]]=a[i].X;
        yy[++yy[0]]=a[i].y;yy[++yy[0]]=a[i].Y;
    }
    sort(xx+1,xx+xx[0]+1);sort(yy+1,yy+yy[0]+1);
    xx[0]=unique(xx+1,xx+xx[0]+1)-xx-1;yy[0]=unique(yy+1,yy+yy[0]+1)-yy-1;
    mm=2*nn;
    for(int i=1;i<=nn;i++){
        a[i].x=lower_bound(xx+1,xx+xx[0]+1,a[i].x)-xx;
        a[i].y=lower_bound(yy+1,yy+yy[0]+1,a[i].y)-yy;
        a[i].X=lower_bound(xx+1,xx+xx[0]+1,a[i].X)-xx;
        a[i].Y=lower_bound(yy+1,yy+yy[0]+1,a[i].Y)-yy;
        li[i*2-1]=line{a[i].y,a[i].x,a[i].X,1};
        li[i*2]=line{a[i].Y,a[i].x,a[i].X,-1};
    }
    sort(li+1,li+mm+1,cmp);
    build(1,1,xx[0]-1);
    add(1,li[1].x,li[1].X-1,1);
    for(int i=2;i<=mm;i++){
        res+=(yy[li[i].y]-yy[li[i-1].y])*t[1].sum;
        add(1,li[i].x,li[i].X-1,li[i].flag);
    }
    return res;
}
int res=0;
struct in{
	int x,y;
}In[N];
bool ED;
signed main(){
//	cerr<<(&ED-&ST)/1048576.0<<'\n';
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int X,Y;
    cin>>n>>m>>X>>Y;
    for(int i=1;i<=n;i++){
    	cin>>In[i].x>>In[i].y;
    	a[i+m].X=a[i+m].x=In[i].x;
    	a[i+m].Y=a[i+m].y=In[i].y;
    	a[i+m].X++,a[i+m].Y++;
	}
	for(int i=1;i<=m;i++){
		char c;int w;
		cin>>c>>w;
		if(c=='U') {
			a[i].x=a[i].X=X;
			a[i].y=Y,a[i].Y=Y+w;
			Y+=w;
		}
		if(c=='D') {
			a[i].x=a[i].X=X;
			a[i].y=Y-w,a[i].Y=Y;
			Y-=w;
		}
		if(c=='L') {
			a[i].x=X-w,a[i].X=X;
			a[i].y=a[i].Y=Y;
			X-=w;
		}
		if(c=='R') {
			a[i].x=X,a[i].X=X+w;
			a[i].y=a[i].Y=Y;
			X+=w;
		}
		a[i].X++,a[i].Y++;
		b[i]=a[i];
	}
//	cout<<solve(m)<<'\n';
	int rres=n+solve(m);
	for(int i=1;i<=m;i++) a[i]=b[i];
//	cout<<rres<<'\n';
	rres-=solve(n+m);
//    ;
	cout<<X<<' '<<Y<<' '<<rres;
    return 0;
}
```

---

## 作者：Walrus (赞：3)

## 无脑做法
题目一共两个问，第一问只是求移动完成后的坐标，是简单的。

问题在第二问上，要求统计出经过了多少个被标记过的点。

不难发现我们无法快速地知道经过一次移动路过了哪些点且不重不漏地统计出来，但是可以发现移动一次相当于覆盖了一条线段，想到线段树。**线段树上支持区间覆盖区间查询**，由于坐标范围是 $[-10^9,10^9]$，即便离散化后在线段树上也很难对应上，所以考虑动态开点（但对于非线段树部分是可以离散化的）。

怎么开线段树？我最初的想法是对坐标轴上每个象限开 $n$ 棵，但是发现这些象限的线段树是可以合并的，所以考虑改成对**横方向开 $n$ 棵，纵方向开 $n$ 棵**，一共 $2\times n$ 棵，相比于最初想法少了一半。

然后动态开点，为什么无脑呢？因为我们可以将走过的路径直接在树上 $\log$ 求出答案然后覆盖，所以一定是**不重**的，至于会不会漏掉，显然是不会的，在开始时将所有标记点扔到树上等待查询就可以了。

时间复杂度 $O(n\log n)$，常数略大但也能过。

代码是狮山就放链接了。

[code](https://www.luogu.com.cn/paste/omq0cqge)

---

## 作者：ARIS2_0 (赞：3)

### 前言

大家怎么都在 map+set 啊，这题不是二分+差分就做完了吗。

赛时代码 WA 了一发，以为写挂了，调了半天没调出来，最后自暴自弃把数组改成 $5\times10^6$ 交上去竟然就过了……但至今也不知道为什么 $2\times10^5$ 会 WA。

**注意下文的 $a1,a2$ 为两个不同的数组，而不是一个数组的维度，$t1,t2$ 同理**。

### 思路

考虑把 $n$ 个点复制两份，一份以 $x$ 较小为第一关键字，$y$ 较小为第二关键字排序，称作 $a1$；一份以 $y$ 较小为第一关键字，$x$ 较小为第二关键字排序，称作 $a2$。同时，记录点的编号。

对于每次向上或向下的移动，因为 $x$ 不变，$y$ 变化，则此次移动经过的点**在 $a1$ 里一定是连续的**，可以用二分查找来找到这个区间。

对于向左或向右同理，可以用二分查找来找到经过的点在 $a2$ 里的连续区间。

找到连续区间后，我们要把这整个区间都打上标记。可以使用差分数组维护区间加的方式打标记，即对 $a1,a2$ 维护两个差分数组 $t1,t2$。

所有操作完成后，对 $t1,t2$ 做前缀和。

对于 $t1$ 的第 $i$ 个点，若不等于 $0$，则 $res_{p}=1$，其中 $res$ 是统计答案的数组，$p$ 是 $a1$ 的第 $i$ 个点的编号。$t2$ 同理。

最后的答案即为 $\sum\limits_{i=1}^nres_i$。

Update：赛时没有想到差分数组，而是直接树状数组胡过去的。糖丸了。

评价：学数据结构学的。

### AC Code

下面是差分数组代码。

如果有大神佬找出开 $2\times10^5$ WA 的原因，感激不尽。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
const int inf=1e16,maxn=5e6+10;
struct node{
    int id,x,y;
}s1[maxn],s2[maxn];
pii a1[maxn],a2[maxn];
int res[maxn];
bool cmp1(node a,node b){
    if(a.x==b.x)return a.y<b.y;
    return a.x<b.x;
}
bool cmp2(node a,node b){
    if(a.y==b.y)return a.x<b.x;
    return a.y<b.y;
}
int n;
namespace tree{
    struct tree{
        int tree[maxn];//它其实是差分数组。。。
        void add(int l,int r,int pos){
            if(l==0)return;
            if(l>r)return;
            if(l>n)return;//为了防止挂分的各种特判
            tree[l]+=pos;
            if(r<n)tree[r+1]-=pos;
        }
    };
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int m,x,y;cin>>n>>m>>x>>y;
    for(int i=1;i<=n;i++)cin>>s1[i].x>>s1[i].y,s1[i].id=i,s2[i]=s1[i];
    sort(s1+1,s1+n+1,cmp1);
    sort(s2+1,s2+n+1,cmp2);//排序，同时记录编号
    for(int i=1;i<=n;i++){
        a1[i]={s1[i].x,s1[i].y};
        a2[i]={s2[i].y,s2[i].x};//存到 pair 里方便二分
    }
    tree::tree t1,t2;
    while(m--){
        char f;int dist;cin>>f>>dist;
        switch(f){
            case 'D':{
                int toy=y-dist;
                t1.add(lower_bound(a1+1,a1+n+1,mp(x,toy))-a1,upper_bound(a1+1,a1+n+1,mp(x,y))-a1-1,1);
                y=toy;
                break;
            }
            case 'U':{
                int toy=y+dist;
                t1.add(lower_bound(a1+1,a1+n+1,mp(x,y))-a1,upper_bound(a1+1,a1+n+1,mp(x,toy))-a1-1,1);
                y=toy;
                break;
            }
            case 'L':{
                int tox=x-dist;
                t2.add(lower_bound(a2+1,a2+n+1,mp(y,tox))-a2,upper_bound(a2+1,a2+n+1,mp(y,x))-a2-1,1);
                x=tox;
                break;
            }
            case 'R':{
                int tox=x+dist;
                t2.add(lower_bound(a2+1,a2+n+1,mp(y,x))-a2,upper_bound(a2+1,a2+n+1,mp(y,tox))-a2-1,1);
                x=tox;
                break;
            }
        }
    }
    for(int i=1;i<=n;i++){
        t1.tree[i]+=t1.tree[i-1];
        t2.tree[i]+=t2.tree[i-1];//对差分数组做前缀和
    }
    for(int i=1;i<=n;i++){
        if(t1.tree[i])res[s1[i].id]=1;
        if(t2.tree[i])res[s2[i].id]=1;
    }
    int ans=0;
    for(int i=1;i<=n;i++)ans+=res[i];
    cout<<x<<" "<<y<<" "<<ans;
	return 0;
}
```

---

## 作者：hytallenxu (赞：1)

## 前言
赛时 40min 过了前三题，D 直接瞪出来了也写出了正解，但是由于神秘问题炸锅了，最后遗憾离场。

## 正文
拿到这题人傻了，这个值域有点小大。

观察到屋子总数不大，那我们直接开 set 存每一个屋子。

那怎么个存法也是一个问题，我们先往后看怎么维护再回来搞。

每次移动都是横轴或者纵轴移动的，那我们就将每一个屋子存进两个 `map<int,set<int>>`，一个以横轴为 key，另一个以纵轴为 key 即可。

那怎么删除呢？

我们利用 set 一个特别好用的特性：`lower_bound`。

对于每次移动，我们确认起点和终点，然后二分来确定从哪里开始删，后面一个一个在 set 中删就好了。注意横轴移动的话，要同时删纵轴上对应的屋子，反之亦然。

看上去复杂度很假，但实际上，在 $n,m$ 同阶的情况下，每个屋子只被删了 $1$ 次，加上 set 和 map 的时间复杂度的话也只有 $O(n\log^2 n)$。

后面就是模拟了。

## Code
[赛后补的正确代码](https://atcoder.jp/contests/abc385/submissions/61031467)，参考了官方题解。

[赛时挂掉的代码](https://atcoder.jp/contests/abc385/submissions/60987245)，T 了 $6$ 个点。

## 后文
第一次正式打 ABC，没想到还是经验不足，之后要加训限时做题了。

---

## 作者：wangyizhi (赞：1)

**题目传送门：**
**[洛谷](https://www.luogu.com.cn/problem/at_abc385_d) || [AtCoder](https://atcoder.jp/contests/abc385/tasks/abc385_d)**

赛时想到的神奇做法。

~~没想到和标算差不多。~~

## 题目大意

在平面直角坐标系上有 $N$ 个点 $(x_i,y_i)$。从点 $(sx,sy)$ 出发，每次向上下左右中的一个方向走，路程为 $c$，共走了 $M$ 次。问有多少个点被经过过。

其中，$1\le N,M\le2\times10^5$，$-10^9\le x_i,y_i,sx,sy\le10^9$，$1\le C\le10^9$。

## 题目分析

注意到我们每次走的都是沿着平行于 $x$ 轴或 $y$ 轴上的直线上的连续的一段。

因此考虑将横坐标相同的点放在一起，将纵坐标相同的点放在一起。

我们可以开两个 `map<int,set<int>>` 来解决这个问题。比如说我们现在把横坐标相同的点放在一起，那么 `map` 的第一维存横坐标，`set<int>` 记录横坐标相同时的纵坐标。
当我们走过一个点时，只需将它在两个 `map` 中都删除，防止重复走过。这样答案就是原来的点的个数减去整个 `map<int,set<int>>` 的大小和。

那如何删去连续的一段呢？比如说我们现在在 $(sx,sy)$ 向上走，我们首先可以 `lower_bound` 要删的点的最小值 $sy$，然后一直往后找直到值大于 $sy+c$，同时顺便把它在两个 `map<int,set<int>` 里删掉。最后要记得更新现在在的坐标。

然后这题就做完了。

由于每个点只会被删一次，所以时间复杂度 $O(n \log^2 n)$。

~~其实离散化之后应该是可以少掉一个 $\log$ 的，但蒟蒻太懒了不想写。~~

具体的细节还是看代码把，解释起来确实挺麻烦的。

## AC Code

```cpp
// by wangyizhi(571247)
// link: https://atcoder.jp/contests/abc385/submissions/60987547
// 不要试图复制哦！
#include<iostream>
#include<set>
#include<map>
#include<vector>
using namespace std;
using ll=long long;
#define int ll
const int N=2e5+1;
int x[N],y[N];
map<int,set<int>> mx,my;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int n,m,sx,sy;
	cin>>n>>m>>sx>>sy;
	for(int i=1;i<=n;i++)
		cin>>x[i]>>y[i],mx[x[i]].insert(y[i]),my[y[i]].insert(x[i]);
	while(m--)
	{
		char d;int c;
		cin>>d>>c;
		if(d=='U')
		{
			vector<int> v;
			int yy=sy+c;
			auto it=mx[sx].lower_bound(sy); // 向上走，从 sy 走到 sy+c
			for(;it!=mx[sx].end();it++)
			{
				if(*it>yy) break;
				v.push_back(*it),my[*it].erase(sx); 
			}
			for(auto i:v) mx[sx].erase(i);
      // 这里开个 vector 存了再删是因为怕直接删迭代器会出现一些奇奇怪怪的错误
      // 反正也不影响复杂度
			sy+=c;
		}
    // 下面也是同理
		else if(d=='D')
		{
			vector<int> v;
			int yy=sy-c;
			auto it=mx[sx].lower_bound(yy);
			for(;it!=mx[sx].end();it++)
			{
				if(*it>sy) break;
				v.push_back(*it),my[*it].erase(sx);
			}
			for(auto i:v) mx[sx].erase(i);
			sy-=c;
		}
		else if(d=='L')
		{
			vector<int> v;
			int xx=sx-c;
			auto it=my[sy].lower_bound(xx);
			for(;it!=my[sy].end();it++)
			{
				if(*it>sx) break;
				v.push_back(*it),mx[*it].erase(sy);
			}
			for(auto i:v) my[sy].erase(i);
			sx-=c;
		}
		else if(d=='R')
		{
			vector<int> v;
			int xx=sx+c;
			auto it=my[sy].lower_bound(sx);
			for(;it!=my[sy].end();it++)
			{
				if(*it>xx) break;
				v.push_back(*it),mx[*it].erase(sy);
			}
			for(auto i:v) my[sy].erase(i);
			sx+=c;
		}
	}
	int tot=0;
	for(auto i:mx) tot+=i.second.size();
	cout<<sx<<" "<<sy<<" "<<n-tot;
	return 0;
}
```

完结撒花！

---

## 作者：Ivan422 (赞：1)

代码量很大的题，绿得有了。

因为这一题导致我 E 题差一点点就可以在规定时间内提交并一次过了，无语。

我们直入主题，如何求解 $-10^9\leq x,y\leq 10^9$ 的情况？

ABC 非常喜欢考察这一类**超大网格图**的题目，喜欢刷 ABC 的朋友都知道，这种题要用 `set`。

但是，我们发现这个 `set` 甚至无法开 $2\times 10^9$ 个，那我们考虑优化，在这一点上，这一题就比其他的**差大网格题**难上加难。

怎么优化呢？

我们可以把所有的点按照 $y$ 先排序，再按 $x$ 排序，插入到第一个 `set`，设这个 `set` 为 $a$。在这一个 `set` 内有一个特点：**行上连续之点可以排在一起**。

同理，我们可以把所有的点按照 $x$ 先排序，再按 $y$ 排序，插入到第二个 `set`，设这个 `set` 为 $b$。在这一个 `set` 内有一个特点：**列上连续之点可以排在一起**。

虽然这个排序看起来有点绕，但实际上这样我们就很好在 `set` 上处理。

然而，这是这道题代码量最小的一步。

我们发现，在 `U` 和 `D` 操作上，会影响 $y$ 值，而这个 $y$ 的变化可以在 $b$ 中找到连续的一段。

我们发现，在 `L` 和 `R` 操作上，会影响 $x$ 值，而这个 $x$ 的变化可以在 $a$ 中找到连续的一段。

当然，我们发现这两个操作直接枚举段标记会超时。

那么，`set` 的优点将发挥出来。

我们可以在**很好的时间复杂度**内进行删除！

那么，每一个点也只会标记一次。

就**不会出现重复标记**！

这样，这道题也就迎刃而解了。

吗？

不，代码一大堆坑！

我们以 `U` 操作为例。

首先，我们要明确操作区间，即从 $(x,y)$ 到 $(x,y+c)$。

按照顺序，我们要先定位 $(x,y)$ 的位置，直接大力二分。

这时候，我们需要判断这个位置合不合法。要是二分不到，那就是没有解。而当 $x$ 坐标不匹配，也不合法。

而合法后，我们考虑暴力跳。当然每一步都得检查一下。

每一次跳跃，我们首先增加计数器。

接下来，我们要删除 $a$ 中的答案，这里直接删即可。

但是删除 $b$ 中，我们发现直接删会导致指针丢失，所以，我们要写 `b.erase(v++);`，这里 $v$ 是指针，这样，$v$ 能记录到下一个答案，又能够移除，就不会出错。

以此类推，我们可以完成剩下 $3$ 种操作的处理。

处理这种问题的手法，将在**超大网格图**中经常用到。

好了，代码挺长的：[链接](https://atcoder.jp/contests/abc385/submissions/60978956)。

---

## 作者：linjinkun (赞：0)

简单题？不！

赛事没切，~~其实是我懒得想~~。

赛后切了。

一道 STL 运用题。

很容易写出代码，但是复杂度不行，考虑优化，由于每一次我们都是一条线上的查询，考虑使用 map，设 $Y_i$ 表示房屋中坐标的 $x$ 为 $i$ 的 $y$ 坐标有序集，$X_i$ 表示房屋中坐标的 $y$ 为 $i$ 的 $x$ 坐标有序集，然后每次出现上操作或下操作就查询 $Y_x$（$x$ 指当前的 $x$ 坐标）中满足在移动前和移动后的 $y$ 坐标区间内的数量，需要再用一个 map 查重，然后出现左操作或右操作就查询 $X_y$（$y$ 指当前的 $y$ 坐标）中满足在移动前和移动后的 $x$ 坐标区间内的数量，需要再用一个 map 查重。

然后……就做完了？

是的。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
map<int,set<int>>mpy;
map<int,set<int>>mpx;
map<pair<int,int>,int>mp;
signed main()
{
	int n,m;
	long long x,y;
	scanf("%lld %lld %lld %lld",&n,&m,&x,&y);
	int num = 0;
	for(int i = 1;i<=n;i++)
	{
		int x,y;
		scanf("%lld %lld",&x,&y);
		mpy[x].insert(y);
		mpx[y].insert(x);
	}
	mp[{x,y}] = 1;
	for(int i = 1;i<=m;i++)
	{
		char a;
		int b;
		cin >> a >> b;
		if(a == 'U')
		{
			if(mpy.find(x) == mpy.end())
			{
				y+=b;
				continue;
			}
			auto it = mpy[x].lower_bound(y);
			for(auto i = it;i!=mpy[x].end()&&*i<=y+b;)
			{
				if(mp.find({x,*i}) == mp.end())
				{
					mp[{x,*i}] = 1;
					num++;
				}
				i = mpy[x].erase(i);
			}
			y+=b;
		}
		else if(a == 'D')
		{
			if(mpy.find(x) == mpy.end())
			{
				y-=b;
				continue;
			}
			auto it = mpy[x].lower_bound(y-b);
			for(auto i = it;i!=mpy[x].end()&&*i<=y;)
			{
				if(mp.find({x,*i}) == mp.end())
				{
					mp[{x,*i}] = 1;
					num++;
				}
				i = mpy[x].erase(i);
			}
			y-=b;
		}
		else if(a == 'L')
		{
			if(mpx.find(y) == mpx.end())
			{
				x-=b;
				continue;
			}
			auto it = mpx[y].lower_bound(x-b);
			for(auto i = it;i!=mpx[y].end()&&*i<=x;)
			{
				if(mp.find({*i,y}) == mp.end())
				{
					mp[{*i,y}] = 1;
					num++;
				}
				i = mpx[y].erase(i);
			}
			x-=b;
		}
		else if(a == 'R')
		{
			if(mpx.find(y) == mpx.end())
			{
				x+=b;
				continue;
			}
			auto it = mpx[y].lower_bound(x);
			for(auto i = it;i!=mpx[y].end()&&*i<=x+b;)
			{
				if(mp.find({*i,y}) == mp.end())
				{
					mp[{*i,y}] = 1;
					num++;
				}
				i = mpx[y].erase(i);
			}
			x+=b;
		}
	}
	printf("%lld %lld %lld",x,y,num);
	return 0;
}
```

---

