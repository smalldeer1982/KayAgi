# Chladni Figure

## 题目描述

Inaka has a disc, the circumference of which is $ n $ units. The circumference is equally divided by $ n $ points numbered clockwise from $ 1 $ to $ n $ , such that points $ i $ and $ i + 1 $ ( $ 1 \leq i < n $ ) are adjacent, and so are points $ n $ and $ 1 $ .

There are $ m $ straight segments on the disc, the endpoints of which are all among the aforementioned $ n $ points.

Inaka wants to know if her image is rotationally symmetrical, i.e. if there is an integer $ k $ ( $ 1 \leq k < n $ ), such that if all segments are rotated clockwise around the center of the circle by $ k $ units, the new image will be the same as the original one.

## 说明/提示

The first two examples are illustrated below. Both images become the same as their respective original ones after a clockwise rotation of $ 120 $ degrees around the center.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1147B/e97ded58f64e835700251efbf078bd03afdc1691.png)

## 样例 #1

### 输入

```
12 6
1 3
3 7
5 7
7 11
9 11
11 3
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
9 6
4 5
5 6
7 8
8 9
1 2
2 3
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
10 3
1 2
3 2
7 2
```

### 输出

```
No
```

## 样例 #4

### 输入

```
10 2
1 6
2 7
```

### 输出

```
Yes
```

# 题解

## 作者：是个汉子 (赞：2)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1147B)	[CF传送门](http://codeforces.com/problemset/problem/1147/B)

### 题意

给你一个 $n$ 个点的图，其中有 $m$ 条线段。求该图形是否为旋转对称图形。

### Solution

我们设旋转 $x$ 个点可以和原图形重合，那么 $k\cdot x$ 个点也可以

反过来，已知旋转一圈就是原图形，此时旋转了 $n$ 个点，我们只要找到一个 $n$ 的因子满足`旋转后和原图形重合`即可。

那么我们枚举 $n$ 的因子和每一位旋转后的情况就好了

判断时设此时枚举到 $d(d|n)$ 和第 $i$ 位，只要判断 $i,i+d$ 所含的线段数量是否相等和每一条线段是否都对应。

小剪枝：枚举每一位的过程中如果出现不相等的情况可以立即跳出，枚举 $n$ 的因子的过程中如果出现满足答案的情况就立即跳出。

注意：输入线段的两个端点 $u,v$ 时，是有两条线段的，一条是 $v-u$ ，一条是 $u-v+n$ ，记得都储存

### Code

```c++
#include<bits/stdc++.h>

using namespace std;
const int N=1e5+10;
vector<int> d,p[N];
int n,m,flag=1;

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n/2;i++)
        if(n%i==0) d.push_back(i);
    for(int i=1,u,v;i<=m;i++){
        scanf("%d%d",&u,&v);
        if(u>v) swap(u,v);
        p[u].push_back(v-u);
        p[v].push_back((n+u-v-1)%n+1);
    }
    for(int i=1;i<=n;i++)
        sort(p[i].begin(),p[i].end());
    for(int i=0;i<d.size();i++){
        flag=1;
        int now=d[i];
        for(int j=1;j<=n;j++){
            if(p[j].size()!=p[(j+now-1)%n+1].size()){
                flag=0;
                break;
            }
            for(int k=0;k<p[j].size();k++){
                if(p[j][k]!=p[(j+now-1)%n+1][k]){
                    flag=0;
                    break;
                }
            }
            if(flag==0) break;
        }
        if(flag==1) break;
    }
    if(flag==0) puts("No");
    else puts("Yes");
    return 0;
}
```



---

## 作者：wizardMarshall (赞：1)

## 题意

在一个正 $n$ 变形上加 $m$ 条边，问最终的图形是不是旋转对称。

## 思路

我们很容易就可以想到枚举旋转的角度（或者说旋转几格）。这里明显的一点就是旋转的角度必须是 $n$ 的因数，否则无法对应上。

枚举了之后就要判断是否合法，假设当前旋转了 $k$，则最终线段左右为 $[(l+k-1)\%n + 1,(r+k-1)\%n + 1]$。如果它们都一一对应就合法。

注意点大集：

- 注意每条线段是**一一对应**，仅仅在下一个位置有线段存在还不够。可能有多条线段对到同一条。

- $k\ne n$。如果不加这个限制，你会发现所有不符合的情况都会成立（因为每条线段恰好转一圈和自己对应）。

- 输入的线段没有保证 $l < r$，计算出来的也不一定满足大小关系，因此要手动调整以保证格式统一。

## 代码

似乎比较简洁？

```c++
#include <bits/stdc++.h>
using namespace std;


pair <int, int> a[200005];
int n, m;
map <pair <int, int>, bool> mp;
void check(int k) {//判断函数
	for (int i = 1; i <= m; i++) {//先把所有线段标记一遍
		mp[a[i]] = 1;
	}
	for (int i = 1; i <= m; i++) {
		int v1 = (a[i].first + k - 1) % n + 1, v2 = (a[i].second + k - 1) % n + 1;
		if (v1 > v2)swap(v1, v2);//大小调整
		if (!mp[{v1, v2}]) {//不存在这条线段
			return;
		}mp[{v1, v2}] = 0;//每个只和一个对应，用完就删标记
	}
	cout << "Yes";//每个线段都有对应
	exit(0);
}
signed main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &a[i].first, &a[i].second);
		if (a[i].first > a[i].second)swap(a[i].first, a[i].second);//同样手动调整
	}
	for (int i = 1; i * i <= n; i++) {
		if (n % i == 0) {//枚举因数
			check(i);
			if (i * i != n && i != 1)check(n / i);//这里要规避k=n的情况
		}
	}cout << "No";
	return 0;
}
```

---

## 作者：绝顶我为峰 (赞：1)

题意：给一个正多边形上挂多条线段，问多边形是否旋转对称。

旋转对称的定义是图形旋转某个角度之后与原图重合。

由于这里是正 $n$ 边形，我们不妨枚举转过的边数。

自然想到枚举 $n$ 的因数，否则不可能重合。

然后我们对于每个因数，暴力枚举每条边，查询端点平移后是否有匹配的线段即可，这个过程可以 set 维护，时间复杂度 $O(n\sqrt n\log n)$。

注意线段平移之后是可以匹配自己的，所以查找到线段本身也算匹配。

```cpp
#include<iostream>
#include<cstdio>
#include<set>
#include<cmath>
using namespace std;
int n,m;
set<pair<int,int> > s;
int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;++i)
    {
        int x,y;
        cin>>x>>y;
        if(x>y)
            x^=y^=x^=y;
        s.insert({x,y});
    }
    for(int i=2;i*i<=n;++i)
        if(n%i==0)
        {
            int g=i;
            bool flag=1;
            for(auto i:s)
            {
                pair<int,int> p={(i.first+g-1)%n+1,(i.second+g-1)%n+1};
                if(p.first>p.second)
                    p.first^=p.second^=p.first^=p.second;
                if(!s.count(p))
                {
                    p={p.second,p.first};
                    if(s.count(p))
                        continue;
                    flag=0;
                    break;
                }
            }
            if(flag)
            {
                puts("YES");
                return 0;
            }
            g=n/i;
            flag=1;
            for(auto i:s)
            {
                pair<int,int> p={(i.first+g-1)%n+1,(i.second+g-1)%n+1};
                if(p.first>p.second)
                    p.first^=p.second^=p.first^=p.second;
                if(!s.count(p))
                {
                    p={p.second,p.first};
                    if(s.count(p))
                        continue;
                    flag=0;
                    break;
                }
            }
            if(flag)
            {
                puts("YES");
                return 0;
            }
        }
    int g=1;
    bool flag=1;
    for(auto i:s)
    {
        pair<int,int> p={(i.first+g-1)%n+1,(i.second+g-1)%n+1};
        if(p.first>p.second)
            p.first^=p.second^=p.first^=p.second;
        if(!s.count(p))
        {
            p={p.second,p.first};
            if(s.count(p))
                continue;
            flag=0;
            break;
        }
    }
    if(flag)
    {
        puts("YES");
        return 0;
    }
    puts("NO");
    return 0;
}
```

---

## 作者：RegisterFault (赞：1)

## 简述题意

在圆环上均匀分布 $n$ 个点，有 $m$ 条线段，每条线段的端点都在圆上。求该图形是否为旋转对称图形。

## 题目分析

首先暴力算法就是枚举旋转多少，然后检查旋转后的图形和原图形是否相等即可。这样的时间复杂度显然是 $O(n ^ 2)$ 的，无法通过。

然后可以发现题目有一个性质：设旋转了 $x$ 个单位，则 $x$ 一定是 $n$ 的约数。因为考虑如果旋转 $x$ 之后，则旋转 $kx$ 之后也一定重合。

所以就可以暴力枚举 $x$ 的所有约数，旋转之后暴力 `check` 即可。

关于本题的时间：我们可以将每条线段用类似字符串哈希的方式转化成整数，然后开一个哈希表存储。这样时间复杂度就是 $O(n \times \sigma_0 (n))$。

```cpp
#include <unordered_map>
#include <iostream>
#include <cstring>
#include <cstdio>
#define a first
#define b second

using namespace std;

const unsigned long long P = 998244353;
const int N = 500010;
using PII = pair<int, int>;
using ULL = unsigned long long;
PII p[N]; int n, m;
unordered_map<ULL, bool> Map;
ULL get(PII x) {
	return (1ull * x.first * P + 1ull * x.second);
}
bool check(int x) {
	if (x == n) return false;
	for (int i = 1; i <= m; i ++ ) {
		if (!Map.count(get({(p[i].a + x) % n, (p[i].b + x) % n})))
			return false;
	} return true;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i ++ ) {
		scanf("%d%d", &p[i].a, &p[i].b);
		p[i].a -- , p[i].b -- ;
		Map[get(p[i])] = true;
		PII tmp = {p[i].b, p[i].a};
		Map[get(tmp)] = true;
	}
	for (int i = 1; i <= n / i; i ++ ) {
		if (n % i == 0) {
			if (check(i)) return puts("Yes"), 0;
			if (check(n / i)) return puts("Yes"), 0;
		}
	} return puts("No"), 0;
}
```

截止到 2023.08.10 是最优解。

---

## 作者：Piwry (赞：1)

这里给出一种比较暴力的做法

（upd: 补充了 $O(m\log n+n)$ 的做法qaq）

## 解析

由于每种不同类型的线段仅能由相同类型的线段 “替代”，因此考虑对每种边分别讨论

对于一条线段 $a, b$，我们取出其中一个作为 “代表端点”；设 “代表端点” 为 $x$，另一点为 $y$，我们要求 $y$ 逆时针到 $x$ 的距离小于等于 $\lfloor\frac n 2\rfloor$

对于每组线段，我们就相当于要找到所有 $k$ 使得对于每个 “代表端点” $x_i$，都有 $x_i+k$（循环意义下的下标）存在；对于所有线段，我们就相当于要找到一个 $k_0$，使得每组线段都存在一个 $k=k_0$

然后发现这是个判定性问题；于是就可以想到用 `bitset` 优化。复杂度 $O(\frac {mn} w)$，$n\leq 10^5, m\leq 2\cdot 10^5$ 能过

关于具体实现，这里仅提下对于每种线段怎么找到所有满足要求的 $k$

设 `bitset` 的第 $i$ 位表示该下标是否存在端点。我们枚举需该组要检查的端点 $x_i$，将 $[0, x_i-1]$ 单独拎出来，再将 $[x_i, n]$ 单独拎出来；并将 $[0, x_i-1]$ “搬” 到 $[x_i, n]$ 的右边，再给元素重新标号（具体来说，对于 $[x_i, n]$，第 $y$ 位变为第 $y-x_i$ 位；对于 $[0, x_i-1]$，第 $y$ 位变为第 $y+(n-x_i)$ 位）。这样第 $i$ 位的值若为 $1$，就代表 $x_i+i$ 存在端点，即 $i$ 对于 $x_i$ 是一个可行的 $k$。再把所有 $x_i$ 的答案都 $\&$ 起来，就得到了该组线段的答案

## CODE

解析中不清楚的地方可以参考代码理解qaq

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>
using std::vector;
using std::sort;
using std::bitset;

const int MAXN =1e5+20;

/*------------------------------IO------------------------------*/

int read(){
	int x =0; char c =getchar(); bool f =0;
	while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
	while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
	return (f) ? -x : x;
}

/*------------------------------Main------------------------------*/

inline int dist(const int &a, const int &b, const int &n){/*b 逆时针到 a 的距离*/
	if(a < b)
		return b-a;
	else
		return b+(n-a);
}

vector<int> v[MAXN];/*每种长度的线段的 "较左" 的端点 ( 设其为 a，b 逆时针到 a 的距离小于 n/2 )*/
bitset<MAXN+1> nw1, nw2, able, ans;

int main(){
	int n =read(), m =read();
	for(int i =0; i < m; ++i){
		int a =read(), b =read();
		if(dist(a, b, n) > n/2)
			a ^=b ^=a ^=b;
		v[dist(a, b, n)].push_back(a);
	}
	ans.set();
	for(int i =1; i <= n/2; ++i){
		sort(v[i].begin(), v[i].end());
		nw1.reset(), nw2.reset(), able.set();
		for(int index:v[i])/*端点应不会有重复*/
			nw1[index] =1;
		for(int index:v[i]){
			nw1[index] =0;
			able &=((nw1>>index)|(nw2<<(n-index)));
			if((n&1) == 0 && i == n/2)/*<- 注意特例，即自己 " 替代 " 自己*/
				able[n/2] =1;
			nw2[index] =1;
		}
		ans &=able;
	}
	if(ans.any())
		puts("Yes");
	else
		puts("No");
}
```

## 关于另一做法的证明

（即复杂度为 $O(m\cdot d(n))$ 的做法）

感觉好像没什么地方有讲...

具体来说，我们需要证明转 $k$ 和转 $\gcd(n, k)$ 是等价的

考虑为一种线段的一个端点 $x$（或者说刚才的的 “代表端点”）找替代的端点，不妨以顺时针顺序，那么应该是 $x+k$；接着又给 $x+k$ 找替代的端点，那么就是 $x+2k$...

我们可以证明第一次遇到曾经访问过的点一定是 $x$；如果不是，显然我们可以往回跳若干个 $k$ 到 $x$，那么我们必然已经第二次跳到 $x$（可能有些细节问题，但差不多就是这个意思）

于是我们访问的总点数就是 $\frac {\text{lcm}(k, n)} k$，即 $\frac {n} {\gcd(n, k)}$。可以发现每隔 $\gcd(n, k)$ 个点一定有一个点我们需要访问；于是转 $k$ 和转 $\gcd(n, k)$ 是等价的

## $O(m\log n+n)$ 的做法（补充）

看见社论有提到...现在回来把坑填了

先考虑一个较简单的版本：所有线段的 “代表端点” 都不重复

考虑给 “代表端点” 根据其线段的长度分配一种字符；空位置也分配一种字符。这样原题就相当于问字符串是否存在非平凡的（即循环节不为整个串）循环节长度（这里的 “循环节” 当然是对整个串）

可以考虑求最小循环节长度；即最多循环节重复次数。求这个的方法有很多，这里就不具体展开讲了；社论提到 z-algorithm，但这里用的是 kmp

对于线段的 “代表端点” 重复的情况，可以考虑将某个端点的所有线段按长度排序，然后将这 整个序列，或说 字符串，视为 一种字符

问题在于去重。可以考虑用 Trie-tree；但由于字符集较大（是 $O(n)$ 级别的，考虑线段的不同长度的个数），需要用 `map` 存儿子，于是这部分复杂度就是 $O(m\log n)$ 的

## CODE（$O(m\log n+n)$ 版本）

```cpp
#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
using std::max;
using std::vector;
using std::map;

const int MAXN =1e5+20, MAXM =2e5+20;

/*------------------------------IO------------------------------*/

int read(){
	int x =0; char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
	return x;
}

/*------------------------------Trie------------------------------*/

vector<int> arr[MAXN/2];
// 每种长度的 " 代表端点 " //
vector<int> str[MAXN];

int ID;
map<int, int> son[MAXM];
int vis[MAXM], tot;

int insert(const int &x, const int &cur, vector<int> &Str){
	if(cur == (int)Str.size()-1){
		if(!vis[x])
			return vis[x] =++ID;
		else
			return vis[x];
	}
	else{
		if(!son[x].count(Str[cur+1]))
			son[x].insert(std::pair<int, int>(Str[cur+1], ++tot));
		return insert(son[x].find(Str[cur+1])->second, cur+1, Str);
	}
}

/*------------------------------Main------------------------------*/

inline int dist(const int &a, const int &b, const int &n){/*b 逆时针到 a 的距离*/
	if(a < b)
		return b-a;
	else
		return b+(n-a);
}

int s[MAXN], pi[MAXN];
// 下标从 $1$ 开始 //

int main(){
	int n =read(), m =read();
	
	for(int i =0; i < m; ++i){
		int a =read(), b =read();
		int Dist =dist(a, b, n);
		// 要求 a 顺时针到 b 的距离不大于 n/2 //
		if(Dist > n/2)
			a ^=b ^=a ^=b, Dist =dist(a, b, n);
		// 这一步是为了避免排序的复杂度 //
		// 不过之后维护 trie-tree 儿子列表的复杂度还是带 log 的... //
		arr[Dist].push_back(a);
		if(Dist == n/2 && n%2 == 0)
			arr[Dist].push_back(b);
	}
	for(int i =1; i <= n; ++i)
		str[i].push_back(-1);
	for(int i =0; i <= n/2; ++i)
		for(int j:arr[i])
			str[j].push_back(i);
	for(int i =1; i <= n; ++i)
		s[i] =insert(0, -1, str[i]);
	
	int mx =1;
	for(int i =2; i <= n; ++i){
		int j =pi[i-1];
		while(j && s[j+1] != s[i])
			j =pi[j];
		if(s[j+1] == s[i])
			pi[i] =j+1;
		else
			pi[i] =0;
	}
	for(int cur =pi[n]; cur; cur =pi[cur]){
		int cur_len =n-cur;
		if(n%cur_len == 0)
			mx =max(mx, n/cur_len);
	}
	
	if(mx > 1)
		puts("Yes");
	else
		puts("No");
}
```

---

## 作者：incra (赞：0)

### Sol
提供一个脑抽后想出的做法。

考虑用一个数 $f_i$ 表示从第 $i$ 出发构成的图的形态，显然可以用 $i$ 的所有出边 $(i,j)$，$\sum j \times rd_i$ 来表示，其中 $rd_i$ 表示对于第 $i$ 个点的随机权值。

那么问题就转化成了，如何快速找到两个 $i,j$ 满足 $f_i=f_j,f_{i+1}=f_{j+1}\dots f_{i+n-1}=f_{j+n-1}$，不难想到字符串哈希。

注意赛时代码没有乘上 $rd_i$，加上后被 WA 的概率就会低一些。

### Code
```cpp
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cassert>
#include <chrono>
#include <random>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
#define IOS ios :: sync_with_stdio (false),cin.tie (0),cout.tie (0)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
int fastio = (IOS,0);
#define puts(s) cout << s << endl
#define endl '\n'
const int N = 200010,BASE = 100003;
const LL MOD = 100000000000031;
int n,m;
vector <int> g[N];
LL w[N];
LL f[N];
LL s1[N],s2[N];
__int128 h[N],p[N];
int main () {
	p[0] = 1;
	for (int i = 1;i < N;i++) p[i] = p[i - 1] * BASE % MOD;
	cin >> n >> m;
	for (int i = 1;i <= n;i++) w[i] = w[i + n] = rd (1,1e7);
	for (int i = 1;i <= 2 * n;i++) w[i] += w[i - 1];
	while (m--) {
		int a,b;
		cin >> a >> b;
		g[a].pb (b),g[b].pb (a);
	}
	for (int i = 1;i <= n;i++) {
		for (int j : g[i]) f[i] += (j - i < 0 ? j - i + n : j - i);
		f[i + n] = f[i];
	}
	for (int i = 1;i <= 2 * n;i++) h[i] = (h[i - 1] * BASE + f[i]) % MOD;
	set <__int128> vis;
	for (int i = 1;i <= n;i++) {
		vis.insert ((h[i + n - 1] - h[i - 1] * p[n] % MOD + MOD) % MOD);
	}
	if (vis.size () < n) puts ("Yes");
	else puts ("No");
	return 0;
}
```

---

## 作者：aaaaaaaawsl (赞：0)

### 题意：

给定圆上均匀分布的 $n$ 个点，编号 $1$ 到 $n$。给出某些点之间的边，问组成的新图形是不是旋转对称图形。

--------

### 分析：

一个图形如果是旋转对称图形，那么一定存在一个 $x < n$，转 $x$ 个点后图形重合。假设不存在，那么设 $x = kn+b$，于是可以先转 $k$ 次 $n$，此时图形和原图形一样，再转 $b$ 个点和原图形重合，与原命题矛盾，所以得证。所以我们枚举 $1$ 到 $n - 1$ 判断就行。

进一步的，只需要枚举 $n$ 的因数就可以了。详细证明不太会，但是“因为如果转 $2\times x$ 那么转 $x$ 一定是”这样的观点显然是完全错误的。 比如十二个点，$1,7$ 连一条边，最少转六个点，但是不能转三个。那为什么枚举 $n$ 的因数一定对呢？我给一个感性的证明：考虑完全重合的点的对应点的映射，由于转的点数小于 $n$，将映射连边，正好不重不漏的包裹了 $n$ 个点。每一条边跨越的点数相等，所以一定存在 $n$ 的因数满足条件。

枚举到转了 $x$ 个点，怎么判断呢？注意到点之间的相对位置不变，我们开数组记录每个点与其他点的钦定方向后的相对距离，计算即可。

---------

### Code

```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<vector>

using namespace std;

inline int read(){
	register int x = 0, f = 1; register char ch = getchar();
	for(; ch > '9' || ch < '0'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return x * f;
}

const int N = 1e5 + 10;

int factor[N];
int n, m;
vector<int> tp[N];

bool check(int x){ if(x == n + 1) return 0;
	for(int i = 1; i <= n; ++ i){
		if(tp[i].size() != tp[x].size()) return 0;
		for(int j = 0; j < tp[i].size(); ++ j) if(tp[i][j] != tp[x][j]) return 0;
		x ++; if(x == n + 1) x = 1;
	}
}

int main(){
	n = read(); m = read();
	for(int i = 1; i <= m; ++ i){
		int a = read(), b = read();
		if(a > b) swap(a, b);
		tp[a].push_back(b - a);
		tp[b].push_back(n - b + a);
	}
	for(int i = 1;  i <= n; ++ i) if(!tp[i].empty()) sort(tp[i].begin(), tp[i].end()); 
	for(int i = 1; i <= sqrt(n); ++ i) if(!(n % i)) factor[++ factor[0]] = i, factor[++ factor[0]] = n / i;
	for(int i = 1; i <= factor[0]; ++ i) if(check(factor[i] + 1)){puts("Yes"); return 0;}
	puts("No"); return 0;
}
```



---

## 作者：Lagerent (赞：0)

[水题。](https://www.luogu.com.cn/problem/CF1147B)

我们发现，每次旋转的可能合法格子数一定是 $n$ 的约数。设转 $x$ 个节点后可以和原图形重合，那么旋转 $k \times x$ 也一定可以。原图旋转 $n$ 个点一定可以和原图重合，那么我们只需要判断 $d (d | n)$ 即可。

每次判断，我们只需要暴力查看每条线段旋转后是否有对应线段即可。

我是使用 map 维护，带个 $\log$ 但是无伤大雅。

时间复杂度 $O(\sqrt{n} \times m\log m)$。

代码就不放了。

---

