# Parking Lot

## 题目描述

A parking lot in the City consists of $ n $ parking spaces, standing in a line. The parking spaces are numbered from 1 to $ n $ from left to right.

When a car arrives at the lot, the operator determines an empty parking space for it. For the safety's sake the chosen place should be located as far from the already occupied places as possible. That is, the closest occupied parking space must be as far away as possible. If there are several such places, then the operator chooses the place with the minimum index from them. If all parking lot places are empty, then the car gets place number $ 1 $ .

We consider the distance between the $ i $ -th and the $ j $ -th parking spaces equal to $ 4·|i-j| $ meters.

You are given the parking lot records of arriving and departing cars in the chronological order. For each record of an arriving car print the number of the parking lot that was given to this car.

## 样例 #1

### 输入

```
7 11
1 15
1 123123
1 3
1 5
2 123123
2 15
1 21
2 3
1 6
1 7
1 8
```

### 输出

```
1
7
4
2
7
4
1
3
```

# 题解

## 作者：jianhe (赞：4)

### 前言：
细节好多，怒调 2h。

### 思路：
“所有车在停车时会停在距相邻的车最远的车位上”，所以我们要维护相邻车两两之间的距离，停车时找距离最远的两辆停在中间（向下取整），开车时找到这个点的前驱和后继再合并即可。

我们需要能动态维护区间最大值，能方便地插入、删除的数据结构。所以用 `set`。

具体来说，用 `set` 维护每个区间的左端点与区间长度（可以由此计算出最优停车点），按区间长度除以二（即与相邻车的最小距离）从大到小、左端点从小到大排序。

其余操作与第一段所述相同。

### 细节：
边界问题比较烦人。

可以特判 $1$ 和 $n$ 的情况。

可以再开一个 `set` 记录已用的停车位，方便找前驱、后继以及最左边与最右边的点。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=1e6+10;
ll n,m,t,id,p[N];
bool flag1,flagn;
struct P{
	ll x,len;//左端点，区间长度（右端点-左端点）
	friend bool operator<(const P& A,const P& B){return A.len/2==B.len/2?A.x<B.x:A.len/2>B.len/2;}//注意要 / 2
};
set<P> s;
set<ll> tail;//找前驱、后继，以及最左、最右端点
bool check1(){
	if(tail.empty()) return 1;//停车场没有车就选 1
	ll t=*tail.begin()-1;//1~第一个已停的距离
	if(!s.empty()&&s.begin()->len/2>t) return 0;
	if(flagn) return 1;//包含在上一行里
	ll t2=n-*--tail.end();//最后一个已停~n 的距离
	return t>=t2;//1 的下标最小，所以可以取等
}
bool checkn(){
	ll t=n-*--tail.end();
	if(s.begin()->len/2>=t) return 0;//n 的下标最大，所以不能取等
	return 1;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	while(m--){
		cin>>t>>id;
		if(t==1){
			if(!flag1&&check1()){//1 没车而且最优
				ll y=1;cout<<y<<"\n";p[id]=1;
				if(tail.size()) s.insert({1,*tail.begin()-1});
				flag1=1;tail.insert(1);
				continue;
			}
			if(!flagn&&checkn()){//n 没车而且最优
				ll y=n;cout<<y<<"\n";p[id]=n;
				s.insert({*--tail.end(),n-*--tail.end()});
				flagn=1;tail.insert(n);
				continue;
			}
			auto it=s.begin();s.erase(it);
			ll x=it->x,len=it->len;
			ll y=x+len/2;cout<<y<<"\n";p[id]=y;
			s.insert({x,y-x});s.insert({y,x+len-y});tail.insert(y);
		}else{
			ll x=1,y=p[id],len;
			auto it=tail.lower_bound(y),it2=tail.upper_bound(y);
			bool p=0;
			if(it!=tail.begin()) x=*--it,p=1;
			if(it2==tail.end()) flagn=0,s.erase({x,y-x});//删去最右边的，只需要删去前一个与这个之间的区间
			else{
				len=*it2-x;
				if(p) s.erase({x,y-x}),s.erase({y,x+len-y}),s.insert({x,len});//两个区间拼接起来
				else flag1=0,s.erase({y,*it2-y});//删去最左边的，只需要删去这个与后一个之间的区间
			}
			tail.erase(y);
			if(y==1) flag1=0;
			if(y==n) flagn=0;
		}
	}
	return 0;
}
```

---

## 作者：BLX32M_10 (赞：1)

## CF219E 题解

将没车的位置填 $1$，有车的位置填 $-\infty$，可以把问题转化成类似最大子段和问题。

此时的子段和大小就是连续的空车位个数，而题目的要求是与其他车的距离最小值最大。

所以，连续空车位分为两种（设连续空车位长度为 $x$）：

- 序列的头或尾：最大距离 $x - 1$；
- 非序列头或尾：最大距离 $\lfloor \frac{x-1}{2}\rfloor$。

因为此题涉及修改，我们用线段树维护最大子段和及其位置，但判定条件是 $\lfloor\frac{x-1}{2}\rfloor$ 最大。对于头和尾，线段树最大子段和会顺便维护，直接取出来就行。

具体的实现见代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 2e5 + 5;
int n, m;

#define ls (x << 1)
#define rs (x << 1 | 1)
#define mid ((l + r) >> 1)
#define root 1,1,n
const int maxc = maxn * 2.67;
// 最大子段和 最大前缀和  最大后缀和  总和    最大子段左端 最大后缀左端
int c[maxc], lc[maxc], rc[maxc], s[maxc], p[maxc], rp[maxc];
inline void pu(int x)
{
    s[x] = s[ls] + s[rs];
    lc[x] = max(lc[ls], s[ls] + lc[rs]);
    rc[x] = rc[rs];
    rp[x] = rp[rs];
    if (s[rs] + rc[ls] >= rc[x])
    {
        rc[x] = s[rs] + rc[ls];
        rp[x] = rp[ls];
    }
    c[x] = rc[ls] + lc[rs];
    p[x] = rp[ls];
    if ((c[ls] - 1) / 2 >= (c[rs] - 1) / 2 && (c[ls] - 1) / 2 >= (c[x] - 1) / 2)
    {
        p[x] = p[ls];
        c[x] = c[ls];
    }
    else if ((c[rs] - 1) / 2 > (c[x] - 1) / 2)
    {
        p[x] = p[rs];
        c[x] = c[rs];
    }
}
inline void bd(int x, int l, int r)
{
    if (l == r)
    {
        c[x] = lc[x] = rc[x] = s[x] = 1;
        p[x] = rp[x] = l;
        return ;
    }
    bd(ls, l, mid);
    bd(rs, mid + 1, r);
    pu(x);
}
inline void upd(int x, int l, int r, int k, int val)
{
    if (l == r)
    {
        
        c[x] = lc[x] = rc[x] = s[x] = val;
        return ;
    }
    if (k <= mid)
        upd(ls, l, mid, k, val);
    else
        upd(rs, mid + 1, r, k, val);
    pu(x);
}
inline pair <int, int> qry()
{
    if ((c[1] - 1) / 2 <= lc[1] - 1 && lc[1] >= rc[1])
        c[1] = lc[1], p[1] = 1;
    else if ((c[1] - 1) / 2 < rc[1] - 1)
        c[1] = rc[1], p[1] = rp[1];
    return make_pair(c[1], p[1]);
}
unordered_map <int, int> mp;
signed main()
{
    scanf("%lld %lld", &n, &m);
    bd(root);
    while (m--)
    {
        int x, y;
        scanf("%lld %lld", &x, &y);
        if (x == 1)
        {
            int pos;
            pair <int, int> p = qry();
            int a = p.first, b = p.second;
            if (b == 1)
                pos = 1;
            else if (a + b - 1 == n)
                pos = n;
            else
                pos = b + a - 1 - a / 2;
            printf("%lld\n", pos);
            mp[y] = pos;
            upd(root, pos, -0x3f3f3f3f);
        }
        else
        {
            upd(root, mp[y], 1);
            mp.erase(y);
        }
    }
    return 0;
}
```

---

## 作者：johnsmith0x3f (赞：1)

## 0x00 [Outline](https://codeforces.com/contest/219/problem/E)

见题面[翻译](https://www.luogu.com.cn/problem/CF219E)。

## 0x01

若把空车位连续段视为区间，则操作 $1$ 相当于找到 $\lfloor \frac {len} 2 \rfloor$ 最大的区间，在中间停车，将其分成两个新的区间，操作 $2$ 则相反。

则我们需要一种数据结构，支持快速查找某个位置到相邻的车距离的最大值，及快速插入删除元素。

用 `set` 维护三元组，三个关键字分别为距离，所在区间的左端点，及最大值对应的车位。用链表维护每辆车左右相邻的车位置。

亦可转化为最大子段和问题：空车位赋值为 $1$，有车的车位赋值为 $-\infty$，则需求最大子段和及其位置，可用线段树实现。

## 0x02 Code

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read() {
    int x = 0, f = 1; char c = getchar();
    while(isdigit(c)^1) f &= c != 45, c = getchar();
    while(isdigit(c)) x = (x<<1) + (x<<3) + (c^48), c = getchar();
    return f ? x : -x;
}

typedef pair<int, int> pii;

const int inf = 0x3f3f3f3f;
const int maxn = 1000005;
int n, m, ans[maxn], pre[maxn], nxt[maxn];
set<pair<int, pii>> ss;

pair<int, pii> make(const int &l, const int &r) {
    if(l == 0 && r == n+1) return {-inf, {0, 1}};
    if(l == 0) return {-(r-1), {0, 1}};
    if(r == n+1) return {-(n-l), {l, n}};
    return {-((r-l)/2), {l, l+(r-l)/2}};
}

int main() {
    n = read(), m = read(), pre[n+1] = 0, nxt[0] = n+1;
    ss.insert({-inf, {0, 1}});
    for(int i = 1; i <= m; ++i) {
        int x = read(), y = read();
        if(x & 1) {
            pii tmp = ss.begin()->second;
            ss.erase(ss.begin());
            int l = tmp.first, p = tmp.second, r = nxt[l];
            pre[p] = l, pre[r] = p;
            nxt[p] = r, nxt[l] = p;
            printf("%d\n", ans[y] = p);
            ss.insert(make(l, p)), ss.insert(make(p, r));
        }
        else {
            int p = ans[y], l = pre[p], r = nxt[p];
            ss.erase(make(l, p)), ss.erase(make(p, r));
            pre[r] = l, nxt[l] = r;
            ss.insert(make(l, r));
        }
    }
    return 0;
}
```

---

