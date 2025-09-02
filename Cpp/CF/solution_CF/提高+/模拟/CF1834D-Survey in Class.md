# Survey in Class

## 题目描述

Zinaida Viktorovna has $ n $ students in her history class. The homework for today included $ m $ topics, but the students had little time to prepare, so $ i $ -th student learned only topics from $ l_i $ to $ r_i $ inclusive.

At the beginning of the lesson, each student holds their hand at $ 0 $ . The teacher wants to ask some topics. It goes like this:

- The teacher asks the topic $ k $ .
- If the student has learned topic $ k $ , then he raises his hand by $ 1 $ , otherwise he lower it by $ 1 $ .

Each topic Zinaida Viktorovna can ask no more than one time.

Find the maximum difference of the heights of the highest and the lowest hand that can be in class after the survey.

Note that the student's hand can go below $ 0 $ .

## 说明/提示

In the first test case, Zinaida Viktorovna can ask the topics $ 5, 6, 7, 8 $ . Then the hand of the $ 2 $ -nd student will be at the height of $ 4 $ , and the hand of the $ 4 $ -th will be at the height of $ -2 $ , that is, the difference will be equal to $ 6 $ .

In the second test case, you can ask about the topics $ 1 $ and $ 3 $ . Then the hand of the $ 1 $ -st student will be at the height of $ 2 $ and the hand of the $ 3 $ -rd student will be at the height of $ -2 $ . So the difference will be $ 4 $ .

In the third test case, the difference between the highest and lowest hand will be $ 0 $ for any set of topics asked.

In the fifth test case, you can ask all topics. Then the difference between the heights of the $ 1 $ -st and $ 3 $ -rd students' hands will be $ 12 $ .

## 样例 #1

### 输入

```
6
4 8
2 6
4 8
2 7
1 5
3 3
1 3
2 3
2 2
3 5
1 5
1 5
1 5
3 5
1 1
3 3
5 5
4 7
1 7
1 3
3 3
4 5
2 4
1 3
2 4```

### 输出

```
6
4
0
2
12
2```

# 题解

## 作者：ケロシ (赞：9)

提出一种 $O(n)$ 的思路。

这道题无非两种情况。

一、区间一包含区间二。

二、区间一与区间二互相不包含。

接下来分类讨论。

假设有第一种情况是，那么第一种情况的最大值就为最长的区间包含最短的区间，为 $\max_{i=1}^n len_i - \min_{i=1}^n len_i$。

如果最长的区间不包含最短的区间，那肯定答案比 $\max_{i=1}^n len_i - \min_{i=1}^n len_i$ 大，考虑第二种情况。

所以答案必须大于等于 $\max_{i=1}^n len_i - \min_{i=1}^n len_i$。

随后在第二种情况中，为了使答案最大，第二个区间的左端点越靠右，或者右端点越靠左，那么直接记录所以区间中最靠右的左端点为 $ml = \max_{i=1}^n l$，记录最靠左的右端点为 $mr = \min_{i=1}^n r$。

那么综上所述，答案就为：$\max(\max_{i=1}^n len_i - \min_{i=1}^n len_i,\max_{i=1}^{n}\min(len_i,\max(ml-l_i,r_i-mr)))$。

代码如下。

```cpp
#define FOR(i, m, n) for(int i=(m);i<=(n);i++)
#define ROF(i, m, n) for(int i=(m);i>=(n);i--)
#define REP(i, n) for(int i=0;i<(n);i++)
#define BG(v) v.begin()
#define ED(v) v.end()
#define ALL(v) (v).begin(), (v).end()
template <typename T, typename U>
inline bool chmax(T& a, U b) { return a < b ? (a = b, true) : false; }
template <typename T, typename U>
inline bool chmin(T& a, U b) { return a > b ? (a = b, true) : false; }
void solve() {
	int n, m;
	cin >> n >> m;
	vector<int> l(n), r(n), len(n);
	REP(i, n) {
		cin >> l[i] >> r[i];
		len[i] = r[i] - l[i] + 1;
	}
	int ans = 0;
	int mx = *max_element(ALL(len));
	int mn = *min_element(ALL(len));
	chmax(ans, mx - mn);
	int ml = *max_element(ALL(l));
	int mr = *min_element(ALL(r));
	REP(i, n) {
		chmax(ans, min(len[i], max(ml - l[i], r[i] - mr)));
	}
	cout << ans * 2 << endl;
}
```


---

## 作者：huangrenheluogu (赞：2)

## CF1834D 分类

找不到合适的算法，本质就是暴力。

我学长和我在打比赛（模拟 CF），我在 2h 内就做到这一道题，还是比较菜的。但是写一篇题解纪念一下第一次打 CF（~~虽然不是赛时打的~~）。

总体来说这道题是比较简单的，我们分类讨论一下情况就好了。

改变一下题意：一堆线，找到一个有，另一个没有的部分，最大化这部分的值。

- 包含

![](https://cdn.luogu.com.cn/upload/image_hosting/fabe5ekv.png)

如上图所示，我们需要维护 $r_1-r_2+l_2-l_1$。把同一根线放在一起就是 $(r_1-l_1)-(r_2-l_2)$。所以我们需要维护 $r_i-l_i$ 的值。（但是由于我脑抽了，维护 $r_i-l_i+m$），但是反正会消掉的。

```cpp
for(int i = 1; i <= n; i++){
	read(a[i].l), read(a[i].r);
	maxn = max(maxn, a[i].r - a[i].l);
	minn = min(minn, a[i].r - a[i].l);
}
```

- 自己的右边到别人的右边/自己的左边（图示蓝色部分）

![](https://cdn.luogu.com.cn/upload/image_hosting/r13blt20.png)

发现可以找到 $r$ 的最小值，然后每一个都是自己的右边到这个右端点即可。

但是观察到下面这个样例。

```cpp
3 5
1 1
3 3
5 5
```

我才发现要**特判自己的左端点**。

所以我们可以写出：

```cpp
sort(a + 1, a + n + 1, cmp1);
for(int i = 2; i <= n; i++){
	ans = max(ans, a[i].r - max(a[i].l - 1, a[1].r));
}
```
不要问我为什么不 $O(n)$ 找最大值，而是用 `sort`，因为赛时写的，作者~~因为懒~~不想改了，但是还是可以通过。建议改成 $O(n)$ 求。

- 左边的差别

![](https://cdn.luogu.com.cn/upload/image_hosting/2q6jpigz.png)

这里跟情况二是一样的，我就不赘述了，大家可以自己推。

参考代码略。

Code 环节！

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5;
int T, n, m, maxn, minn, ans;
struct node{
	int l, r;
}a[N];;
inline void read(int &res){
	char ch=getchar();int f=1;res=0;
	while('0'>ch||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while('0'<=ch&&ch<='9'){
		res=(res<<1)+(res<<3)+(ch^48);
		ch=getchar();
	}
	res*=f;
}
inline bool cmp1(node x, node y){
	return x.r < y.r;
}
inline bool cmp2(node x, node y){
	return x.l < y.l;
}
inline int lowbit(int x){
	return x & -x;
}
signed main(){
//	freopen("11.out", "w", stdout);
	read(T);
	while(T--){
		maxn = -2e9, minn = 2e9;
		read(n), read(m);
		for(int i = 1; i <= n; i++){
			read(a[i].l), read(a[i].r);
			maxn = max(maxn, a[i].r - a[i].l);
			minn = min(minn, a[i].r - a[i].l);
		}
		ans = maxn - minn;
		sort(a + 1, a + n + 1, cmp1);
		for(int i = 2; i <= n; i++){
			ans = max(ans, a[i].r - max(a[i].l - 1, a[1].r));
		}
		sort(a + 1, a + n + 1, cmp2);
		for(int i = n - 1; i >= 1; i--){
			ans = max(ans, min(a[n].l, a[i].r + 1) - a[i].l);
		}
		printf("%lld\n", ans * 2);
	}
	return 0;
}
```

---

## 作者：masonpop (赞：2)

很妙的题，可惜赛时没想到那个关键结论。

首先，我们考虑如果两个人所处的区间确定为 $a,b$ 的情况下怎么做。显然，我们只需要选出所有只有 $a,b$ 之一会的题即可。因此，答案是 $a$ 去掉 $b$ 中元素后的大小，或者反过来。先只考虑第一种情况，第二种把区间反转一下就行。

首先将区间按照左端点从小到大排序。先考虑当 $a$ 和 $b$ 不存在包含关系时，显然选择左端点最大的区间和 $a$ 相交。

如果存在包含关系，注意到关键结论：**只有最短的区间才可能产生更优的结果。**

考虑证明，如图。其中区间 $b$ 是左端点最大的区间，$c$ 是被 $a$ 完全包含的区间。

![](https://cdn.luogu.com.cn/upload/image_hosting/y3lbi1nj.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

如果区间 $c$ 更优，那么，蓝色部分一定小于红色部分。则当然有区间 $c$ 的长度小于区间 $b$ 的长度。

那么，对于第三种情况，我们只需要枚举每一个区间，看是否把长度最小的那个区间完全包含，并更新答案即可。

总时间复杂度 $O(n\log n)$，即排序的复杂度。当然可以通过记录最大最小值避免排序从而降到 $O(n)$，不过懒得改了。[代码](https://codeforces.com/contest/1834/submission/210199376)。

---

## 作者：y_kx_b (赞：2)

### 题目大意

有 $n$ 个学生，每个学生只学了第 $l_i$ 到第 $r_i$ 课。老师可以按照以下的形式问若干个不重复的问题：

- 询问大家是否学了第 $k$ 课（$k$ 自己定）。
- 如果第 $i$ 个学生学了第 $k$ 课，那么他把手升高 $1$ 个高度，否则降低 $1$ 个高度。

一开始所有学生的手的高度均为 $0$。问若干问题后，这 $n$ 名学生的手的最高高度与最低高度的距离（也就是极差）最大可能值是多少。

---
### Sol.
首先可以每次询问时把每个人的手先放下 $1$，等到第 $i$ 个学生会的时候把手升高 $2$ 即可。那么题意变成了选出 $\{1\sim m\}$ 的子集使得 $n$ 个区间和它的交的元素数量的极差最大。

首先有贪心：保证交元素数量最少的那个学生 交的元素数量为 $0$。因为好理解，如果有交，那就不问这个交，一定不劣（手最高的高度可能降低 $0$ 或 $2$ 但最低一定降低 $2$）。

那么有第一思路：枚举哪个学生和子集完全没有交（即最低手的学生），然后其他地方全选，查询最大交。也就是说，找到一个区间使得这个区间去掉（最低手的学生的区间）之后的元素数量最大。

发现不太可做，于是改枚举最高手的学生，问题变成了这 $n$ 个区间与该区间的交的最小值。分类讨论，可能有 $3$ 种可能的情况：

（令该枚举的最高手的学生的区间为 o（original） 区间，与 o 区间交（尽可能小）的区间为 x 区间。）

1. x 区间与 o 区间交为 x 左端点往右一直到 o 区间右端点。如果不考虑 o 区间包含 x 区间的情况，显然可以让 x 区间左端点最大来让交最小。（如果太大到超过了 o 区间右端点也没问题，这时交就是 0 了。）**如果考虑 o 区间包含 x 区间的情况，这种情况一定会在 3. 中产生更小的贡献。**
2. x 区间与 o 区间交为 x 右端点往左一直到 o 区间左端点。同理可让 x 区间右端点最小，**如果考虑 o 区间包含 x 区间的情况，这种情况一定会在 3. 中产生更小的贡献。**
3. o 区间包含 x 区间，这时就尽可能让 o 区间长度最小。如果不考虑 x 区间没有完全被 o 区间包含的情况，那么这种情况贡献就是 $n$ 个区间中的最小长度。**如果考虑 x 区间 没有完全被 o 区间包含的情况，这种情况一定会在 1./2. 中产生更小的贡献（显然交的大小不大于 x 区间大小）。**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int N = 114514;
#define l first
#define r second
pii a[N];
int main()
{
	int T, n, m;
    cin >> T;
    while(T--){
        cin >> n >> m;
        for(int i = 1; i <= n; i++)
            cin >> a[i].l >> a[i].r;
        int maxl = 0, minr = 2e9, minlen = 2e9;
        for(int i = 1; i <= n; i++)
        	maxl = max(maxl, a[i].l), minr = min(minr, a[i].r),
        	minlen = min(minlen, a[i].r - a[i].l + 1);
        int ans = 0;
        for(int i = 1; i <= n; i++)
        	ans = max(ans, a[i].r - a[i].l + 1 -
        			min({max(a[i].r - maxl + 1, 0), max(minr - a[i].l + 1, 0), minlen}));
    	cout << ans * 2 << endl;
    }
    return 0;
}
```
D 非常好题目，爱来自 cf。

（好像有更简便的做法？）

---

## 作者：Priestess_SLG (赞：0)

好题啊！

考虑一个经典套路。

> 若一个人不会，则她的分数 $-1$，否则她的分数 $+1$。

转化问题。

> 首先一个人的分数 $-1$，若她会，则她的分数 $+2$。

此时考虑两个人 $A$，$B$。对于问题 $i$：

+ $A$ 和 $B$ 都不会问题 $i$。则相对贡献为 $0$。
+ $A$ 和 $B$ 都会问题 $i$。则相对贡献为 $0$。
+ $A$ 会问题 $i$，$B$ 不会问题 $i$，则相对贡献为 $2$。
+ $B$ 会问题 $i$，$A$ 不会问题 $i$，则相对贡献为 $-2$。

因而若 $A$ 和 $B$ 两个人贡献了极差，且 $A$ 的分数不低于 $B$ 的分数，则令 $A$ 会的问题集合为 $S_a$，$B$ 会的问题集合为 $S_b$，则答案为 $2|S_a-(S_a\cap S_b)|$。问题变为找到两个人 $i$，$j$ 满足 $2|S_i-(S_i\cap S_j)|$ 的值最大。

枚举 $i$ 表示令 $A=i$，则考虑计算 $B=j$（$j\neq i$）时对答案的贡献。

+ $B$ 被 $A$ 完全包含。此时 $A$ 长度固定，因此 $B$ 的长度越短越好。
+ $A$ 被 $B$ 完全包含。~~这还打个【数据删除】？~~
+ $B$ 在 $A$ 左侧。显然最小化答案需要让两个集合的交尽量小。因此需要让 $B$ 的右端点尽量小。
+ $B$ 在 $A$ 右侧。显然最小化答案需要让两个集合的交尽量小。因此需要让 $B$ 的左端点尽量大。

分三类讨论，时间复杂度为 $O(n)$ 或 $O(n\log n)$，可以简单通过。

代码：

```cpp
#pragma GCC optimize(3) 
#include <bits/stdc++.h>
#define eb emplace_back
#define int long long
using namespace std;
const int N = 1000100;
const int mod = 998244353;
const int base = 256;
const int inf = 0x0d000721ll << 2 | 0xAC66666;

int read() {
    int o = 1, x = 0;
    char ch;
    while (!isdigit(ch = getchar())) {
        if (ch == '-') {
            o = -o;
        }
    }
    x = ch & 15;
    while (isdigit(ch = getchar())) {
        x = (x << 3) + (x << 1) + (ch & 15);
    }
    return x * o;
}

int l[N], r[N];

signed main() {
    int T;
    T = read();
    while (T--) {
        int n, m;
        n = read(), m = read();
        int L = -inf, R = inf;
        int mx = -inf, mlen = inf;
        for (int i = 1; i <= n; ++i) {
            l[i] = read(), r[i] = read();
            L = max(L, l[i]);
            R = min(R, r[i]);
            mlen = min(mlen, r[i] - l[i] + 1);
        }
        for (int i = 1; i <= n; ++i) {
            mx = max({mx, (r[i] - l[i] + 1 - min({max(0ll, R - l[i] + 1), max(0ll, r[i] - L + 1), mlen}) << 1)});
        }
        cout << mx << '\n';
    }
    return 0;
}

/*



*/

```

---

## 作者：ZLCT (赞：0)

# CF1834D Survey in Class
## 题目翻译
有 $n$ 条线段和 $m$ 个点，第 $i$ 条线段覆盖 $l_i-r_i$，定义一条线段的分数为在线段内点的数量减不在线段内点的数量。下面要选择任意点并使线段分数的极差最大，输出这个极差。
## 暴力解法
首先我们可以发现极差只与最大最小值有关，所以我们有种思路就是去枚举它的最大值最小值是哪两个，并且算出选这两条线段能构造的最大极差，取它们的最大值即可。\
那么我们来考虑一下，对于两条线段如何处理才能使极差最大。
- 第一种情况就是两条线段不相交，那么极差最大肯定就是两条线段中最长的长度。这个证明也比较好考虑，因为选择这两条线段都不覆盖的点肯定不会产生影响（都 $-1$ 极差不变）。所以极差最大肯定就是某一个线段全选，另一个全空。
- 第二种情况是一个包含另一个，那么极差最大只能是大线段长度减小线段长度（选小线段包含的点都 $+1$，选大线段不包含的点都 $-1$，不影响极差）。
- 第三种情况是两线段相交，这种情况类似前面的讨论，我们只需要比较两个线段分别不相交部分的最大值（因为其它点都同减同加不会产生贡献）。

这样我们就产生了一个 $O(n^2)$ 的暴力了。接下来考虑如何优化。
## 优化暴力
观察上面三种情况，其实会发现我们所构造的方法就是把一条线段为空，另一条线段把相交部分排除其余全填满。\
那我们考虑确定了一条填满的线段，我们肯定是希望另一条线段尽可能与它相交的部分小。\
这看起来也没什么用啊？但是我们思考一下会发现这样的情况其实很简单。
- 包含情况。这种情况其中一个一定是最短的一条线段。\
我们来考虑证明一下：\
假设没有最短的一条线段，那么我们把留白的那一条换成最短的那一条，那无论是否包含，覆盖的点一定不比原来多。所以一定可以通过调整换成最短的那一条。
- 相交情况。这种情况我们断定要么有一条是右端点最左的，要么有一条是左端点最右的。\
证明：假设相交线段左边那一条是空白，那么我们把它调整为右端点最左的线段，一定不会使覆盖区间更大；右侧同理。

于是我们对于每个线段只需要考虑分别与这三条线段进行构造，最后一定能得到答案。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+666;
int n,m,pid,ans,debug;
pair<int,int>a[N],pl[N],pr[N];
int cnt1,cnt2,maxlid,minrid;
pair<int,int>minp(pair<int,int>&c1,pair<int,int>&c2){
    return c1.second-c1.first<c2.second-c2.first?c1:c2;
}
pair<int,int>p;
int getans(pair<int,int>&p1,pair<int,int>&p2){
    int l1=p1.first,r1=p1.second,l2=p2.first,r2=p2.second;
    if(l1==l2&&r1==r2)return 0;
    if(l1==l2){
        return max(r1,r2)-min(r1,r2);
    }
    if(r1==r2){
        return max(l1,l2)-min(l1,l2);
    }
    if(l1>l2){
        swap(l1,l2);
        swap(r1,r2);
    }
    if(r2<r1){
        return r1-l1+1-(r2-l2+1);
    }else if(l2<=r1){
        return max(r1-l1+1,r2-l2+1)-(r1-l2+1);
    }else{
        return max(r1-l1+1,r2-l2+1);
    }
}
void solve(){
    map<pair<int,int>,bool>mp;
    cin>>n>>m;
    ans=0;
    p.first=-1;p.second=m+1;
    maxlid=minrid=0;
    for(int i=1;i<=n;++i){
        cin>>a[i].first>>a[i].second;
        if(mp[a[i]])continue;
        mp[a[i]]=1;
        if(a[i].second-a[i].first+1<p.second-p.first+1){
            p=a[i];
            pid=i;
        }
        if(maxlid==0||a[i].first>a[maxlid].first)maxlid=i;
        if(minrid==0||a[i].second<a[minrid].second)minrid=i;
    }
    cnt1=0;cnt2=0;
    for(int i=1;i<=n;++i){
        if(i==pid)continue;
        ans=max(ans,getans(p,a[i]));
    }
    for(int i=1;i<=n;++i){
        auto stl=a[minrid],str=a[maxlid];
        ans=max(max(getans(stl,a[i]),getans(str,a[i])),ans);
    }
    cout<<ans*2<<'\n';
}
signed main(){
    int T;cin>>T;
    while(T--)solve();
    return 0;
}
```

---

## 作者：nullqtr_pwp (赞：0)

#### 【题目描述】

给定有 $n$ 个区间 $[l_i,r_i]$ 以及 $n$ 个点权 $a_i$，初始为 $0$。你可以选若干个不重复的数 $q_i$。每次选数 $q_i$，对于每个 $j$ 进行以下操作：若 $q_i\subseteq [l_j,r_j]$，则 $a_j\leftarrow a_j+1$；否则 $a_j\leftarrow a_j-1$。最小化操作后序列 $a$ 的极差。

$2\leq n\leq 10^5,1\leq m\leq 10^9$。
#### 【解答】
考虑钦定一个线段 $[l,r]$ 当最大值，此时考虑另一个最小值线段 $[l_1,r_1]$，$=|[l,r]\cap[l_1,r_1]|$，我们可以只选 $[l,r]-\lbrace[l,r]\cap[l_1,r_1]\rbrace$ 的点。此时答案为 $[l,r]$ 的长度与交集长度的差 $\times 2$。

考虑把所有线段按照左端点从小到大排序。考虑钦定 $[l_i,r_i]$ 是最大值。先考虑向左相交的情况。维护所有 $j<i$ 中 $r_j$ 的最小值，如果存在不交的那么交集可以是空的，更新答案，否则就是 $r_i-\min r_j$，这时要求 $r_j\ge l_i$。

再考虑向右相交的情况，直接找 $[l_i,r_i]$ 和 $[l_n,r_n]$ 相交去，依然是排序后的。

考虑包含的情况，可以倒序按照 $l$ 扫描线。对于线段 $[l_i,r_i]$，记录 $r_i$ 在所有 $r$ 中是第 $k$ 小的，可以离散化实现。那么被 $[l_i,r_i]$ 包含的线段 $[l_j,r_j]$ 需要满足 $l_j\ge l_i,r_j\leq r_i$。并且 $[l_j,r_j]$ 的长度最小。此时 $l$ 已经用倒序扫描的方法解决了。而 $r$ 可以线段树维护。因为相交的线段需要满足 $r_j$ 是所有 $r$ 中第 $p$ 小，而且 $p<k$，那么我们可以直接在 $[1,k-1]$ 的所有 $r$ 点找最小值。可以用支持单点修改，区间查最小值的线段树维护。

时间复杂度 $O(n\log n)$。

```cpp
namespace seg{
	int t[maxn<<2];
	#define ls (o<<1)
	#define rs (o<<1|1)
	void update(int o,int l,int r,int pos,int x){
		if(l==r) return t[o]=min(t[o],x),void();
		int mid=(l+r)>>1;
		if(pos<=mid) update(ls,l,mid,pos,x);
		else update(rs,mid+1,r,pos,x);
		t[o]=min(t[ls],t[rs]);
	}
	int query(int o,int l,int r,int ql,int qr){
		if(ql<=l&&qr>=r) return t[o];
		int mid=(l+r)>>1,rt=1e9;
		if(ql<=mid) rt=query(ls,l,mid,ql,qr);
		if(qr>mid) rt=min(rt,query(rs,mid+1,r,ql,qr));
		return rt;
	}
}
using namespace seg;
map<int,int>mp;
void solve(){
	mp.clear();
	int n=read(),m=read();
	vector<pair<int,int>>a(n);
	vector<int>lsh(n),len(n);
	F(i,1,n<<2) t[i]=1e9;
	F(i,0,n-1) a[i].fi=read(),a[i].se=read();
	sort(a.begin(),a.end());
	F(i,0,n-1) lsh[i]=a[i].se,len[i]=a[i].se-a[i].fi+1;
    sort(lsh.begin(),lsh.end());
	F(i,0,n-1) mp[lsh[i]]=i+1;
	int ans=0,p=1e9;
	F(i,0,n-1){
		if(p<a[i].fi) ans=max(ans,len[i]);
		else ans=max(ans,a[i].se-p);
		p=min(p,a[i].se);
	}
	F(i,0,n-1){
		if(a[i].se<a[n-1].fi) ans=max(ans,len[i]);
		else ans=max(ans,a[n-1].fi-a[i].fi);
	}
   	dF(i,n-1,0){
   		int id=mp[a[i].se];
   		ans=max(ans,len[i]-1-query(1,1,n,1,id));
   		update(1,1,n,id,len[i]-1);
   	}
    printf("%d\n",ans*2);
}
```

---

## 作者：QianianXY (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1834D)

设两个区间为 $A$、$B$ 且 $A$ 是好学生。下面讨论提问的问题对极差的贡献。

选择只在 $A$ 里，不在 $B$ 里的问题，贡献为 $2$。

选择共同在 $A$、$B$ 或共同不在 $A$、$B$ 的问题，贡献为 $0$。

选择只在 $B$ 里的问题，贡献为 $-2$。

由此，题目转变为求两个区间 $A$、$B$，满足 $|A-(A\cap B)|$ 最大。答案为

$$2|A-(A\cap B)|$$

$\Theta(n)$ 枚举 $n$ 个区间分别为 $A$ 的情况来找出 $B$。$B$ 有且仅有下列 3 种情况：

1. $B$ 在 $A$ 的左方（可能有一部分相互包含）。显然 $B$ 的右端点越小，交集越小。

2. $B$ 在 $A$ 的右方（可能有一部分相互包含）。显然 $B$ 的左端点越大，交集越小。

3. $B$ 完全包含在 $A$ 内。显然 $B$ 越短，交集越小。

因此，对应三种情况，我们可以在枚举之前先预处理出右端点最小的区间、左端点最大的区间、以及长度最小的区间。它们三个之中与区间 $A$ 交集最小的区间即为 $B$ 区间。判断是 $\Theta(1)$ 的。

```cpp
#include <bits/stdc++.h>
#define N 100010
using namespace std;
typedef long long ll;

template <typename T> inline void read(T &x)
{
	x = 0; T f = 1; char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -f; ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + ch - 48; ch = getchar();}
	x *= f;
}

int n, T, maxl, minr, minl, m, ans;
struct Node {int l, r;} a[N];

inline void WORK()
{
	read(n); read(m);
	maxl = ans = 0; minr = minl = m;
	for (int i = 1; i <= n; i++) {
		read(a[i].l); read(a[i].r);
		maxl = max(maxl, a[i].l);
		minr = min(minr, a[i].r);
		minl = min(minl, a[i].r - a[i].l + 1);
	}
	for (int i = 1; i <= n; i++)
		ans = max(ans, a[i].r - a[i].l + 1 - min(max(minr - a[i].l + 1, 0), min(max(a[i].r - maxl + 1, 0), minl)));
	printf("%d\n", ans << 1);
}

int main()
{
	read(T);
	while (T--) WORK();
	return 0;
}
```


---

## 作者：shinkuu (赞：0)

赛时 1.5h 脑子不知道出什么问题了，光荣掉蓝，场下 10min 就切了，来鞭打自己。

以下最大、最小区间指题目所述手的高度最大、最小的区间。

容易证明一个结论：指定最大的那个区间后，把这个区间全选不会更劣。因为在这个区间内位置一定被最大区间包含（这是句废话），所以贡献只有可能是 $2$ 或 $0$。

此时，发现如果每个区间为一个集合，钦定最大的区间为集合 $S_i$，则答案即为 $\min (|S_i|-|S_i\cap S_j|)$，也就是要求交集最小。分两种情况讨论：

- 最小区间被最大区间包含时：

转化成一个二维偏序问题，排序然后线段树维护。

- 否则：

发现 $r_i$ 尽可能小或 $l_i$ 尽可能大的区间更优，找到 $\min(r_i)$ 和 $\max(l_i)$ 计算即可。

$m$ 较大，所以先离散化一遍，离散化要尤其注意初始化范围。

code：

```cpp
int n,m,d[N<<1];
int tr[N<<3];
struct node{
	int l,r,len;
}e[N];
inline void pushup(int o){
	tr[o]=min(tr[o<<1],tr[o<<1|1]);
}
void update(int l,int r,int o,int x,int y){
	if(l==r){
		tr[o]=min(tr[o],y);
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)
		update(l,mid,o<<1,x,y);
	else 
		update(mid+1,r,o<<1|1,x,y);
	pushup(o);
}
int query(int l,int r,int o,int x,int y){
	if(l>=x&&r<=y)
		return tr[o];
	int mid=(l+r)>>1;
	if(x<=mid&&y>mid)
		return min(query(l,mid,o<<1,x,y),query(mid+1,r,o<<1|1,x,y));
	if(x<=mid)
		return query(l,mid,o<<1,x,y);
	return query(mid+1,r,o<<1|1,x,y);
}
inline bool cmp1(node x,node y){
	return x.r<y.r;
}
void solve(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&e[i].l,&e[i].r);
		e[i].len=e[i].r-e[i].l+1;
		d[i]=e[i].l,d[i+n]=e[i].r;
	}
	sort(d+1,d+n*2+1);
	m=unique(d+1,d+n*2+1)-d-1;
	for(int i=1;i<=n;i++){
		e[i].l=lower_bound(d+1,d+m+1,e[i].l)-d;
		e[i].r=lower_bound(d+1,d+m+1,e[i].r)-d;
	}
	sort(e+1,e+n+1,cmp1);
	int ans=0;
	for(int i=1;i<=m*4;i++)
		tr[i]=inf;
	for(int i=1;i<=n;i++){
		ans=max(ans,e[i].len-query(1,m,1,e[i].l,e[i].r));
		update(1,m,1,e[i].l,e[i].len);
	}
	int x=inf,y=-inf;
	for(int i=1;i<=n;i++){
		x=min(x,d[e[i].r]);
		y=max(y,d[e[i].l]);
	}
	for(int i=1;i<=n;i++)
		ans=max(ans,e[i].len-min(max(x-d[e[i].l]+1,0),max(d[e[i].r]-y+1,0)));
	printf("%d\n",ans*2);
}
signed main(){
	int t=1;
		scanf("%d",&t);
	while(t--)
		solve();
}
```

---

