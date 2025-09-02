# Find the Different Ones!

## 题目描述

给定一个长度为 $n$ 的序列 $\{a\}$ 和 $q$ 次询问。每次询问给定 $l,r$，求在区间 $[l,r]$ 里是否存在满足 $l \le i,j \le r~,~a_i \ne a_j$ 的 $i,j$，如果存在则求出任意一种可能的情况。

## 说明/提示

对于所有测试点，满足 $1\le t\le10^4$，$2\le n\le2\times10^5$，$1 \le a_i \le 10^6$，$1 \le q \le 2\times10^5$，$1 \le l < r \le n$，单测试点所有测试数据中 $n$ 的和不超过 $2\times10^5$，所有 $q$ 的和也不超过 $2\times10^5$。

## 样例 #1

### 输入

```
5
5
1 1 2 1 1
3
1 5
1 2
1 3
6
30 20 20 10 10 20
5
1 2
2 3
2 4
2 6
3 5
4
5 2 3 4
4
1 2
1 4
2 3
2 4
5
1 4 3 2 4
5
1 5
2 4
3 4
3 5
4 5
5
2 3 1 4 2
7
1 2
1 4
1 5
2 4
2 5
3 5
4 5```

### 输出

```
2 3
-1 -1
1 3

2 1
-1 -1
4 2
4 6
5 3

1 2
1 2
2 3
3 2

1 3
2 4
3 4
5 3
5 4

1 2
4 2
1 3
2 3
3 2
5 4
5 4```

# 题解

## 作者：atomic_int (赞：12)

显然，只需要找出与 $a_l$ 不同的下一个元素的位置，判断是否 $\le r$ 即可。如果不是，那么我们找的另一个数一定会和 $a_l$ 不同。

我们可以 $O(n)$ 预处理出与 $a_i$ 的不同的下一个元素的位置，记作 $b$。设 $l=1,r=2$。当 $a_l \ne a_r$ 的时候，$a_l,a_{l+1},\dots,a_{r-1}$ 一定都是相等的，否则 $r$ 会在前面。$b_{l} \sim b_{r-1}$ 均更新为 $r$。详细细节请见代码。

```cpp
void solve() {
  int n, q;
  cin >> n;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  vector<int> ano(n + 1);
  for (int l = 1, r = 2; l <= n; r++) {
    while (a[r] != a[l]) {
      ano[l] = r, l++;
    }
  }
  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    if (ano[l] > r) {
      cout << "-1 -1\n";
    } else {
      cout << l << " " << ano[l] << "\n";
    }
  }
  cout << "\n";
}
```

---

## 作者：AKPC (赞：10)

官方给的题解很简单，[这里](/paste/mxpdzy6q)是翻译后的官方题解（**非本题解主要内容**，译自 deepL）。

但是这篇题解是我考场上极不要脸的**分块**题解，虽然复杂度高，但是~~能过就行~~拿来练习分块是个不错的题目（细节多警告）。

看到区间查询想到什么？数据结构。

看到 $n\leq2\times10^5$ 先想到什么？**分块**。

维护在每一个块询问的答案，如果块内的答案是 $\{-1,-1\}$，说明这一块的值都是同一个，否则就记录答案。

查询的时候，如果 $l,r$ 在同一块内，就暴力找，否则暴力找两个散块，利用与处理的答案寻找整块答案，如果都是 $\{-1,-1\}$，说明这里同一块内的每个的值都相等，比较相邻两个块内（包括散块）任意两个值，如果还是都相等，说明整个区间都没有答案了，这是显然的。

如何线性复杂度暴力处理答案？假设暴力需要处理 $[x,y]$ 区间，则记录 $p=a_x$，在 $[x+1,y]$ 寻找与 $p$ 不同的值，如果找不到，就是这一段的每个数都相等。

[code](/paste/8oca0kok)

---

## 作者：PikachuQAQ (赞：5)

## **Description**

[**Link**](https://www.luogu.com.cn/problem/CF1927D)

给定一长为 $n$ 的序列 $a_i$，$m$ 次询问，每次询问给定一对 $[l, r]$，请你找出在 $[l, r]$ 区间内任意一对互不相等的 $a_i$ 和 $a_j$，输出它们的下标。如果找不到输出一对 $-1$。

## **Solution**

令 $b_i = b_{i - 1} + [a_i \neq a_{i-1}]$，$b_1 = 0$，表示从 $b_1$ 到 $b_i$ 有多少相邻但 $a_i$ 互不相同的 $i$。

当 $b_r-b_l=0$ 时，$[l, r]$ 没有任何相邻且 $a_i$ 互不相同的 $i$，由此可以证明区间内的数两两相同。即无解。

否则，当 $b_r-b_l>0$ 时，说明 $[l, r]$ 内有解。注意到 $b_i$ 一定是单调不降的，且答案一定可以是 $[l, i]$ 形式，可以二分出区间内 $b_i-b_{i-1}=1$ 的 $i$，当 $b_i-b_{i-1}=1$ 时，可以得出 $a_l$ 一定与 $a_i$ 不相等。输出 $l$ 和 $i$ 即可。

时间复杂度 $O(n\log n)$。

## **Code**

[抢到了最优解。](https://www.luogu.com.cn/record/list?pid=CF1927D&orderBy=1&status=&page=1)

```cpp
// 2024/2/9 PikachuQAQ

#include <algorithm>
#include <iostream>

using namespace std;

const int kMaxN = 2e5 + 7;

int t, n, m, a[kMaxN], pre[kMaxN];

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    for (cin >> t; t--; ) {
        cin >> n, pre[0] = -1;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            pre[i] = pre[i - 1] + (a[i] != a[i - 1]);
        }
        cin >> m;
        for (int i = 1, l = 0, r = 0; i <= m; i++) {
            cin >> l >> r;
            if (pre[r] - pre[l] == 0) {
                cout << "-1 -1\n";
            } else {
                cout << l << ' ' << upper_bound(pre + l + 1, pre + r + 1, pre[l]) - pre << '\n';
            }
        }
        cout << '\n';
    }

    return 0;
}
```

---

## 作者：Dream_poetry (赞：4)

### 题目翻译：

给定一个长度为 $n$ 的序列 $a$，$q$ 次询问，查询在 $l$ 到 $r$ 中哪两个元素不同，输出任意一组的下标；若没有输出 ```-1 -1```。

### 思路：

这个题目不难想到二分。

若有一个元素与它前面的元素不同，向 $b$ 数组中加入它的下标。表示从 $i$ 开始出现了一个新的连续区间。

由于查询时输入的也是下标，我们直接查找它们是否在同一个区间内即可。

我们用 ```upper_bound()``` 函数查找它们所在区间的下一个区间是否相同，若相同输出 ```-1 -1``` 即可，否则输出 $a_l$ 和 $a_{ll}$ 即可。其中 $ll$ 是调用 ```upper_bound()``` 函数找到的 $l$ 所在区间的下一个区间的起始位置。

由于证明过于简单，这里就不说了，直接上代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T;
int n;
int a[500005];
int q,l,r;
int b[500005];
int tot;
 
signed main(){
	cin>>T;
	while (T--){
		tot=0;
		memset(b,0,sizeof(b));		
		cin>>n;
		for (int i=1;i<=n;i++){
			cin>>a[i];
			if (a[i]!=a[i-1]){
				b[++tot]=i;
			}
		}
		cin>>q;
		while (q--){
			cin>>l>>r;
			int ll=upper_bound(b+1,b+tot+1,l)-b;
			int rr=upper_bound(b+1,b+tot+1,r)-b;	
			if (ll==rr){
				cout<<"-1 -1\n";
			}
			else{
				if (a[l]!=a[r]){
					cout<<l<<' '<<r<<endl;
				}
				else{
					cout<<l<<' '<<b[ll]<<endl;
				}
			}
		}
		cout<<endl;
	}	
	
	return 0;
}

```


---

## 作者：include13_fAKe (赞：4)

## 前言
昨晚 C 写挂了，瞪了半天没发现问题。

最后无奈地放弃了，去追 D，又挂了。

反复地在 C 和 D 之间横跳，C 没调出来，把 D 调完了，~~竟然是多测没清空完~~。
## 题意
$t$ 组测试数据。

每一组给定一个长度为 $n$ 的数组 $a$，下标从 $1$ 到 $n$。

$q$ 次询问。

每一次给定 $l,r$，询问是否存在 $l\le i,j\le r$，使得 $a_i\not =a_j$。

若存在，输出一组 $i,j$，否则输出两个 $-1$。

$t\le 10^4$，$2\le n,\sum n\le 2\times10^5$，$1\le q\le 10^5$，$1\le \sum q\le 2\times10^5$。
## 思路
有解当且仅当 $l\sim r$ 的数不全部相同。即在 $l\sim r$ 中存在两个**相邻**的数大小不同。

按顺序枚举 $a_i$，$i$ 从 $2$ 开始，若遇到 $a_{i-1} \not=a_i$ 就将其记录下来。

如何记录呢？

用临时变量 $c$ 记录**从 $a_2$ 至 $a_i$** 满足 $a_{i-1} \not=a_i$ 的最后一个位置。随时更新。~~（$b$ 在哪里？）~~

再用数组 $d$ 记录 $c$ 的值，令 $d_i$ 为枚举到 $a_i$ 时的 $c$ 的值。

每次询问，直接查询 $d_r$ 的值是否**大于** $l$。（为什么不能取等请自行思考）

**记得清零。**
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int a[200005];
int c;
int d[200005];
void solve(){
	c=0;
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=2;i<=n;i++){
		if(a[i-1]!=a[i])	c=i;
		d[i]=c;
	}
	int q;
	cin>>q;
	while(q--){
		int l,r;
		cin>>l>>r;
		if(d[r]>l){
			cout<<d[r]-1<<' '<<d[r]<<endl;
		}
		else	cout<<-1<<' '<<-1<<endl;
	}
	cout<<endl;
	for(int i=1;i<=n;i++){
		a[i]=0;
		d[i]=0;
	}
	return;
}
int main(){
	int T;
	cin>>T;
	while(T--)	solve();
	return 0;
}
```


---

## 作者：Loser_Syx (赞：2)

线段树做法。

我们考虑线段树维护两个值 $x,y$，表示两个不同的下标且 $a_x \neq a_y$，于是我们可以再维护一个值 $z$，$z$ 表示当前区间 $[l,r]$ 是否存在一对 $(x,y)$。

具体考虑一下如何合并，我们记左儿子为 $ls$，右儿子为 $rs$，分类讨论：

- 若 $ls$ 的 $z$ 为 $\mathtt{TRUE}$，则当前 $[l,r]$ 一定有方案，并在 $ls$ 内，用 $ls$ 更新即可。
- 若 $rs$ 的 $z$ 为 $\mathtt{TRUE}$，则当前 $[l,r]$ 一定有方案，并在 $rs$ 内，用 $rs$ 更新即可。
- 若 $a_{ls.x} \neq a_{rs.x}$，则当前 $[l,r]$ 存在方案 $x=ls.x,y=rs.x$ 的方案。
- 否则不存在。

按照这个合并的方法更新即可，复杂度 $O(n \log n)$。

[代码](https://codeforces.com/contest/1927/submission/245134565)。

---

## 作者：2huk (赞：1)

> 给定一个长度为 $n$ 的数组 $a$。
>
> 你需要处理 $q$ 次询问。每次询问给定两个整数 $l, r$，你需要找到任意两个整数 $i, j$ 使得：
>
> - $l \le i \le r$；
> - $l \le j \le r$；
> - $a_i \ne a_j$。
>
> 若无解，输出 $i = j = -1$。
>
> 多测。$t \le 10^4$，$\sum n \le 2 \times 10^5$，$\sum q \le 2 \times 10^5$，$1 \le l < r \le n$，$1 \le a_i \le 10^6$。

如果最终答案是 $i, j$，不妨设 $a_i \le a_j$，那么根据 $a_i \ne a_j$，一定可以推出 $a_j - a_i > 0$。

我们不妨使这个差值最大。那么不难看出只有区间内最大值和最小值的差值最大。

那么当区间内最大值和最小值相等时无解。

所以用 ST 表维护区间最小值和最大值的位置即可。实现上略有技巧。

```cpp
int n, a[N];
 
struct RMQ {
	bool op;
	RMQ(bool _op) : op(_op) {}
	int st[N][20];
	
	int minn(int x, int y) {
		return op ? (a[x] < a[y] ? x : y) : (a[x] > a[y] ? x : y);
	}
	
	void init() {
		fup (i, 1, n) st[i][0] = i;
		
		fup (j, 1, 19)
			for (int i = 1; i + (1 << j - 1) <= n; ++ i ) {
				st[i][j] = minn(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
			}
	}
	
	int query(int l, int r) {
		int k = log2(r - l + 1);
		return minn(st[l][k], st[r - (1 << k) + 1][k]);
	}
	
	void clear() {
		fup (i, 1, n)
			fup (j, 0, 19)
				st[i][j] = 0;
	}
}A(false), B(true);
 
void solve() {
	n = read();
	fup (i, 1, n) a[i] = read();
	A.init(), B.init();
	for (int q = read(); q -- ; ) {
		int l = read(), r = read();
		int x = A.query(l, r), y = B.query(l, r);
		if (a[x] == a[y]) puts("-1 -1");
		else wel(x, y);
	}
	
	A.clear(), B.clear();
	
	puts("");
	return;
}
```



---

## 作者：Wf_yjqd (赞：1)

构造方法多，维护方法也多。

提供一种简单的数据结构做法。

------------

我们考虑维护区间最值的位置。

若最大值和最小值相同则没有，否则输出两个位置。

st 表简单维护即可。

------------

没啥难度放个代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+26,mxx=2e5;
int T,n,m,a[maxn],q,l,r,st[2][maxn][20],mnp,mxp,lg[maxn];
inline int mn(int xy,int zb){
    return a[xy]<a[zb]?xy:zb;
}
inline int mx(int xy,int zb){
    return a[xy]>a[zb]?xy:zb;
}
inline int Query(int l,int r,bool op){
    if(l==r)
        return l;
    m=lg[r-l+1];
    return op?mx(st[op][l][m],st[op][r-(1<<m)+1][m]):mn(st[op][l][m],st[op][r-(1<<m)+1][m]);
}
int main(){
    scanf("%d",&T);
    lg[0]=-1;
    for(int i=1;i<=mxx;i++)
        lg[i]=lg[i>>1]+1;
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            st[0][i][0]=st[1][i][0]=i;
        }
        for(int i=1;i<20;i++)
            for(int j=1;j+(1<<i)-1<=n;j++){
                st[0][j][i]=mn(st[0][j][i-1],st[0][j+(1<<(i-1))][i-1]);
                st[1][j][i]=mx(st[1][j][i-1],st[1][j+(1<<(i-1))][i-1]);
            }
        scanf("%d",&q);
        while(q--){
            scanf("%d%d",&l,&r);
            mnp=Query(l,r,0);
            mxp=Query(l,r,1);
            if(a[mnp]==a[mxp])
                puts("-1 -1");
            else
                printf("%d %d\n",mnp,mxp);
        }
    }
    return 0;
}
```


---

## 作者：_Delete_ (赞：1)

## 思路

题目没有修改，双指针预处理出每个数右侧最近不同数的下标，对于每次询问，输出区间最左侧和对应下标，对应下标不在区间内时，特判一下即可。

### 正确性说明

若区间最左侧的右侧最近不同数不在区间时，即说明区间为相同数，区间内没有合法数对。

## 代码

```cpp
#include<bits/stdc++.h>
#define endl "\n"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
//value
const int Ma=2e5+5; 
int a[Ma],x[Ma];

//function 
void solve(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	int i=0,j=0;
	while(i<n&&j<n){
		//双指针处理x数组
		while(a[i]==a[j])j++;
		for(int k=i;k<j;k++)x[k]=j;
		i=j;
	}
	int q;
	cin>>q;
	while(q--){
		//询问
		//由于下标从零开始，所以实际查询时，应查询l-1
		//查后数字为（实际数字-1）
		int l,r;
		cin>>l>>r;
		if(x[l-1]+1<=r)cout<<l<<' '<<x[l-1]+1<<endl;
		else cout<<-1<<' '<<-1<<endl;
	}
	cout<<endl;
}
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0); 
	
	int T;
	cin>>T;
	while(T--)solve();	
	return 0;
}


```


---

## 作者：wmrqwq (赞：1)

~~盲猜没人用此做法~~

# 题目链接

[CF1927D Find the Different Ones!](https://codeforces.com/contest/1927/problem/D)

# 解题思路

考虑分块，在一块内的数**当且仅当**他们是**连续**的且**权值相同**，并记录下他们的左右端点同时记录每一个数在哪个块内，对于每个块维护它的左右端点，然后对于每组询问如果 $l,r$ 在同一个块内，那么 $l \sim r$ 的所有权值一定相同，输出 `-1 -1`，否则 $l \sim r$ 中一定有权值不同的数，这时输出 $l$ 和下一个块的左端点表示的数即可。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define map unordered_map
#define forl(i,a,b) for(register long long i=a;i<=b;i++)
#define forr(i,a,b) for(register long long i=a;i>=b;i--)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) x&-x
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define ll long long
ll t;
void solve()
{
	ll n,m;
	cin>>n;
	ll k=0,a[n+10]={0},b[n+10]={0},l[n+10]={0},r[n+10]={0},num[n+10]={0};
	forl(i,1,n)
	{
		cin>>a[i];
		if(a[i]!=a[i-1])
			r[k]=i,l[++k]=i,num[k]=a[i];
		b[i]=k;
	}
	cin>>m;
	r[k]=n;
	while(m--)
	{
		ll L,R;
		cin>>L>>R;
		if(b[L]==b[R])
			cout<<"-1 -1\n";
		else
			cout<<L<<' '<<l[b[L]+1]<<endl;
	}
	cout<<endl;
}
int main()
{
	IOS;
	t=1;
	cin>>t;
	while(t--)
		solve();
	QwQ;
}
```

---

## 作者：technopolis_2085 (赞：1)

题意：

给你一个区间，让你找出区间中两个不同的数，如果找不到则输出 $-1$。

分析：

如果一个区间内有至少两种数，则区间中至少有一个 $i$，满足 $a_i≠a_{i+1}$。
可以反证，如果不满组此条件，则可以推出 $a_l=a_{l+1}=a_{l+2}=...=a_r$，与已知矛盾，得证。

所以可以记录每一个 $i$ 使得 $a_i≠a_{i+1}$ 到数组 $b_i$ 中，然后对于一个区间，看有没有满足条件的 $i$ 即可。

可以使用二分来查找。先将 $b$ 数组排序，然后找到第一个大于等于 $l$ 的位置 $pos1$，找到第一个严格小于 $r$ 的位置 $pos2$，并检测 $pos1$ 和 $pos2$ 的大小关系。

如果 $pos1≤pos2$，则 $a_{b_{pos1}}$ 和 $a_{b_{pos1}+1}$ 必然不相等。否则，如果 $pos1>pos2$，此时无解。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=2e5+10;
int a[maxn];
int b[maxn];

int main(){
	int T;
	scanf("%d",&T);
	while (T--){
		int n;
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		int tot=0;
		for (int i=1;i<n;i++){
			if (a[i]!=a[i+1]) b[++tot]=i;
		}
		
		int q;
		scanf("%d",&q);
		while (q--){
			int le,ri;
			scanf("%d%d",&le,&ri);
			
			int l=1,r=tot;
			int best1=-1,best2=-1;
			while (l<=r){
				int mid=(l+r)/2;
				if (b[mid]>=le){
					best1=mid;
					r=mid-1;
				}else l=mid+1;
			}
			if (best1==-1){
				printf("-1 -1\n");
				continue;
			}
			
			l=1,r=tot;
			while (l<=r){
				int mid=(l+r)/2;
				if (b[mid]<ri){//注意此处是严格小于
					best2=mid;
					l=mid+1;
				}else r=mid-1;
			}
			
			if (best2==-1){
				printf("-1 -1\n");
				continue;
			}
			
			if (best1<=best2){
				printf("%d %d\n",b[best1],b[best1]+1);
			}else printf("-1 -1\n");
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：LiaoYF (赞：0)

给大家看一个我赛时的唐氏做法。

## 做法

ST 表预处理区间最大值和最小值，再开 $10^6$ 个 vector 存所有 $a_i=x$ 的数的下标。然后每次询问，如果区间最大值等于最小值，无解。否则二分查找最大值和最小值的下标并输出。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,a[200005],stmax[200005][25],stmin[200005][25],vis[1000005];
vector<int> b[1000005];
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            vis[a[i]]=0;
        }
        for(int i=1;i<=n;i++){
            b[a[i]].clear();
        }
        for(int i=1;i<=n;i++){
            b[a[i]].push_back(i);
        }
        for(int i=1;i<=n;i++){
            if(!vis[a[i]]){
                vis[a[i]]=1;
                sort(b[a[i]].begin(),b[a[i]].end());
            }
        }
        for(int i=1;i<=n;i++){
            stmax[i][0]=a[i];
            stmin[i][0]=a[i];
        }
        for(int j=1;(1<<j)<=n;j++){
            for(int i=1;i+(1<<j)-1<=n;i++){
                stmax[i][j]=max(stmax[i][j-1],stmax[i+(1<<(j-1))][j-1]);
                stmin[i][j]=min(stmin[i][j-1],stmin[i+(1<<(j-1))][j-1]);
            }
        }
        cin>>m;
        for(int i=1;i<=m;i++){
            int l,r;
            cin>>l>>r;
            int x=log2(r-l+1);
            int maxn=max(stmax[l][x],stmax[r-(1<<x)+1][x]);
            int minn=min(stmin[l][x],stmin[r-(1<<x)+1][x]);
            if(maxn!=minn){
                int ans1=lower_bound(b[maxn].begin(),b[maxn].end(),l)-b[maxn].begin();
                int ans2=lower_bound(b[minn].begin(),b[minn].end(),l)-b[minn].begin();
                cout<<b[maxn][ans1]<<" "<<b[minn][ans2]<<"\n";
            }else{
                cout<<"-1 "<<"-1"<<"\n";
            }
        }
        cout<<"\n";
    }
    return 0;
}
```

---

## 作者：Wei_Han (赞：0)

## 题目大意
多测。给定长度为 $n$ 的数组，$q$ 次询问，每次询问一组 $l$，$r$ 查询 $l$ 到 $r$ 区间中不相等的数的位置，不存在输出 $-1$。
## Solution
对于查询区间内不相等数位置，我们不好处理，换个思路，记录区间内相同数区间的位置，当存在一个以上区间时，那么一定存在解，输出第一个相同数区间的左端点和右端点 $+1$ 即可。

预处理出所有相同数的区间，查询时二分就行了。
## Code
```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define pr printf("\n")
#define pp printf(" ")
#define pii pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(ll i = a ; i <= b ; i ++ )
#define Fo(a,i,b) for(ll i = a ; i >= b ;-- i  )
using namespace std;
typedef int ll;
typedef double db;
const int N=2e5+5;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
ll t,n,q,a[N],cnt;
struct node{
	ll l,r;
}b[N];
int main(){
	read(t);
	while(t--){ 
		read(n);cnt=0;
		ll L=0;
		fo(1,i,n){
			read(a[i]);
			if(a[i]!=a[i-1]){if(L) b[++cnt].l=L,b[cnt].r=i-1;L=i;}
		}
		if(L) b[++cnt].l=L,b[cnt].r=n;
		read(q);
		fo(1,i,q){
			ll L,R;
			read(L),read(R);
			ll le=1,ri=cnt;
			while(le<ri){
				ll mid=(le+ri+1)>>1;
				if(b[mid].l<=L) le=mid;
				else ri=mid-1;
			}
			ll opl=le;
			le=1,ri=cnt;
			while(le<ri){
				ll mid=(le+ri)>>1;
				if(b[mid].r>=R) ri=mid;
				else le=mid+1;
			}
			ll opr=ri;
			if(opl==opr) printf("-1 -1\n");
			else{
				wr(max(b[opl].l,L)),pp;
				wr(b[opl].r+1),pr;
			}
		}
		pr;
		fo(1,i,cnt) b[i].l=b[i].r=0;
	}
	return 0;
}
``````

---

## 作者：yyrwlj (赞：0)

## 题意简述

给定一个序列，每次询问要求输出区间 $[l,r]$ 内的两个不同元素下标，若全部相同输出两个 $-1$。

## 思路

我们发现一个区间内的元素不全相同，当且仅当区间内的最大值不等于最小值，可以使用线段树维护。

输出位置就让线段树在维护最值时，同时维护最值的位置，在回朔统计两个子树信息时，看最值是由哪个子树转移过来的即可。

## Code

```cpp
#define v first
#define pos second
const int N = 200005;
typedef pair<int, int> PII;
int a[N];
PII mn[N << 2], mx[N << 2];
void build(int u,int l,int r)
{
    if (l == r)
    {
        mn[u] = mx[u] = {a[l], l};
        return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    if (mx[u << 1].v > mx[u << 1 | 1].v)
        mx[u] = {mx[u << 1].v, mx[u << 1].pos};
    else
        mx[u] = {mx[u << 1 | 1].v, mx[u << 1 | 1].pos};
    if (mn[u << 1].v < mn[u << 1 | 1].v)
        mn[u] = {mn[u << 1].v, mn[u << 1].pos};
    else
        mn[u] = {mn[u << 1 | 1].v, mn[u << 1 | 1].pos};
}
PII query1(int u,int l,int r,int L,int R)
{
    if (L <= l && r <= R)
        return mn[u];
    int mid = (l + r) >> 1;
    PII ans = {2e9, 0};
    if (L <= mid)
        ans = query1(u << 1, l, mid, L, R);
    if (mid < R)
    {
        PII ans2 = query1(u << 1 | 1, mid + 1, r, L, R);
        if (ans2.v < ans.v)
            ans = ans2;
    }
    return ans;
}
PII query2(int u,int l,int r,int L,int R)
{
    if (L <= l && r <= R)
        return mx[u];
    int mid = (l + r) >> 1;
    PII ans = {-2e9, 0};
    if (L <= mid)
        ans = query2(u << 1, l, mid, L, R);
    if (mid < R)
    {
        PII ans2 = query2(u << 1 | 1, mid + 1, r, L, R);
        if (ans2.v > ans.v)
            ans = ans2;
    }
    return ans;
}
void work()
{
    int n;
    scanf("%d", &n);
    for (int i=1;i<=n;i++)
        scanf("%d", &a[i]);
    build(1, 1, n);
    int q;
    scanf("%d", &q);
    while (q--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        PII ans1 = query1(1, 1, n, l, r), ans2 = query2(1, 1, n, l, r);
        if (ans1.v == ans2.v)
            puts("-1 -1");
        else
            printf("%d %d\n", ans1.pos, ans2.pos);
    }
    putchar('\n');
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
        work();
    return 0;
}
```

---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1927D)

典。

在这里我把所有数都相等的一段区间且是满足此条件的最大区间称为块。

先跑一遍序列统计出每个块的左端点和右端点，然后二分查找 $l$ 所在的块的右端点和 $r$ 所在的块的左端点，分别记为 $kl$ 和 $kr$。若 $kl\ge kr$，那么就说明在一个块，输出 `-1 -1`，否则输出 $kl$ 和 $kl+1$，因为这利用了两个块之间每个值不相等的性质，虽然这显而易见。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n,a[200010];
int lk1[200010]={0},m1=0,lk2[200010]={0},m2=0,q;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(register int i=1;i<=n;i++) scanf("%d",&a[i]);
		m1++,lk1[m1]=1;
		for(register int i=2;i<=n;i++)
			if(a[i]!=a[i-1]) m1++,lk1[m1]=i,m2++,lk2[m2]=i-1;
		m2++,lk2[m2]=n;
		scanf("%d",&q);
		while(q--)
		{
			int l,r;
			scanf("%d%d",&l,&r);
			l=lower_bound(lk2+1,lk2+m2+1,l)-lk2;
			r=upper_bound(lk1+1,lk1+m1+1,r)-lk1-1;
			if(l==r) printf("-1 -1\n");
			else printf("%d %d\n",lk2[l],lk2[l]+1);
		}
		m1=m2=0,printf("\n");
	}
	return 0;
}
```

---

