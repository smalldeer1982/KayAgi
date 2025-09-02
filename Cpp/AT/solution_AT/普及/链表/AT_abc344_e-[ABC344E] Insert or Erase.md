# [ABC344E] Insert or Erase

## 题目描述

给定一个长度为 $N$ 的数列 $A=(A_1,\ldots,A_N)$。$A$ 的各个元素互不相同。

接下来有 $Q$ 个操作，请按顺序依次处理。每个操作有以下两种类型之一：

- `1 x y` ：在 $A$ 中元素 $x$ 的后面插入 $y$。保证在该操作时，$A$ 中一定存在 $x$。
- `2 x` ：从 $A$ 中删除元素 $x$。保证在该操作时，$A$ 中一定存在 $x$。

保证每次操作后，$A$ 都非空且所有元素互不相同。

请输出所有操作处理完后的数列 $A$。

## 说明/提示

### 限制条件

- $1 \leq N \leq 2\times 10^5$
- $1 \leq Q \leq 2\times 10^5$
- $1 \leq A_i \leq 10^9$
- $A_i \neq A_j$
- 对于第 1 种操作，$1 \leq x,y \leq 10^9$，且操作时 $A$ 中一定存在 $x$
- 对于第 2 种操作，$1 \leq x \leq 10^9$，且操作时 $A$ 中一定存在 $x$
- 每次操作后，$A$ 都非空且所有元素互不相同
- 输入均为整数

### 样例说明 1

操作依次如下：

- 初始 $A=(2,1,4,3)$。
- 第 1 次操作删除 $1$，$A=(2,4,3)$。
- 第 2 次操作在 $4$ 后插入 $5$，$A=(2,4,5,3)$。
- 第 3 次操作删除 $2$，$A=(4,5,3)$。
- 第 4 次操作在 $5$ 后插入 $1$，$A=(4,5,1,3)$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
2 1 4 3
4
2 1
1 4 5
2 2
1 5 1```

### 输出

```
4 5 1 3```

## 样例 #2

### 输入

```
6
3 1 4 5 9 2
7
2 5
1 3 5
1 9 7
2 9
2 3
1 2 3
2 4```

### 输出

```
5 1 7 2 3```

# 题解

## 作者：qw1234321 (赞：6)

老外不会数据结构！老外不会数据结构！

------------

水 E，简单来说是有两种操作：

1. 把一个元素 $y$ 插到值为 $x$ 的元素的后面。

2. 删掉值为 $x$ 的元素。

有插入和删除，自然想到链表。

插入的时候，把 $x$ 与 $nxt_x$ 断开，把 $y$ 接到 $x$ 后面；$nxt_x$ 前面。

删除的时候，把 $x$ 与 $pre_x$ 和 $nxt_x$ 断开，再把 $pre_x$ 和 $nxt_x$ 连上即可。

注意插入和删除的时候随时维护 $pre_x$ 和 $nxt_x$。

[code](https://atcoder.jp/contests/abc344/submissions/51062069)

---

## 作者：LittleDrinks (赞：3)

# [\[ABC344E\] Insert or Erase](https://www.luogu.com.cn/problem/AT_abc344_e)

注意到“$A$ 中的元素互不相同”，也就是说，一次添加或删除，最多更新一个元素，不用考虑一次加入多个 $x$ 导致复杂度爆炸的情况。

如果用数组模拟新增或删除的过程，单次操作之后需要将该点位后续所有的数字前移或后移，时间复杂度 $O(n)$，会 `TLE`。因此我们需要一种能在 $O(1)$ 时间内完成新增或删除操作的数据结构：**双向链表**。

![双向链表原理](https://cdn.luogu.com.cn/upload/image_hosting/gldn9zh6.png)

具体实现时，由于 $A$ 中元素不重复，可以直接以 $a_i$ 作为下标，用 `map` 进行维护。

[AC 代码提交记录](https://www.luogu.com.cn/record/150188806)

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, q;
map <int, int> pre, nxt;

int main()
{
	cin >> n;
	for (int i=1, la=-1; i <= n; ++i) {
		int a;
		cin >> a;
		nxt[a] = -114514; pre[a]=la; nxt[la]=a;
		la = a;
	}
	cin >> q;
	while (q--) {
		int op; cin >> op;
		if (op == 1) {
			int x, y;
			cin >> x >> y;
			pre[y] = x;
			nxt[y] = nxt[x];
			nxt[x] = y;
			pre[nxt[y]] = y;
		} else {
			int x;
			cin >> x;
			nxt[pre[x]] = nxt[x];
			pre[nxt[x]] = pre[x];
		}
	}
	int now = -1;
	while (nxt[now] != -114514) {
		cout << nxt[now] << " ";
		now = nxt[now];
	}
	return 0;
}
```

---

## 作者：OIer_Tan (赞：3)

## 题意

给你一个长度为 $N$ 且元素各不相同的序列 $A=(A_1,\ldots,A_N)$。

需要处理 $Q$ 个查询。每个查询属于以下两种类型之一：

- `1 x y`：在 $A$ 中元素 $x$ 后面紧接着插入 $y$。当给出此查询时，保证 $x$ 存在于 $A$ 中。
- `2 x`：从 $A$ 中删除元素 $x$。当给出此查询时，保证 $x$ 存在于 $A$ 中。

保证在处理完每一个查询后，$A$ 都不是空的，并且其元素都是不同的。需要在处理完所有查询后，输出 $A$。

## 思路

很明显，我们需要一种较快的做法来进行插入和删除。

我们想到可以借助链表来完成这道题，因为链表是可以实现 $O(1)$ 插入删除的。为了方便，可以直接使用 `list`。

但是这还不够，我们还要保存好每个数的位置。可以使用 `map` 或 `unordered_map` 来完成保存，再在每次插入和删除后更新数的位置。最后完成后输出 $A$ 就完成了。

使用 `list` 和 `map` 完成的复杂度为 $O(N\log N +Q\log(N+Q))$，使用 `list` 和 `unordered_map` 完成的复杂度为 $O(N+Q)$。

## 代码

下面是通过 `list` 和 `unordered_map` 来完成的。

```cpp
#include <bits/stdc++.h>  

using namespace std ;  

typedef long long ll ;

ll n , q ;

list <ll> A ;  
unordered_map <ll, list<ll>::iterator> element_map;  

int main () 
{  
	cin >> n ;
	for ( ll i = 1 ; i <= n ; i ++ )
	{  
		ll val ;
		cin >> val ;
		auto it = A.push_back ( val ) ;  
		element_map[val] = it ;  
	}  
	cin >> q ;
	while ( q -- )
	{
		ll type ;
		cin >> type;  
		if ( type == 1 )
		{  
			ll x , y ;
			cin >> x >> y;  
			auto it = element_map[x] ;  
			element_map[y] = A.insert ( ++ it , y ) ;
		} 
		else 
		{  
			ll x ;  
			cin >> x ;  
			auto it = element_map[x];  
			A.erase ( it ) ;
			element_map.erase ( x ) ;
		}  
	}
	for ( auto x : A )
	{
		cout << x << " " ;
	}
	return 0 ;  
}
```

---

## 作者：Phartial (赞：3)

大家好啊，我是高贵的 80 min 过 E 人。

注意到我们不用真的删一个数，只需要在最后输出的时候忽略被删掉的数即可。

（事实上需要考虑一下一个值被删后又被插入的情况，但用下文的处理方法的话不用考虑这种问题）

于是只需要考虑插入，这种同时涉及到值和下标两维的操作不是很好做，考虑用一个数据结构（比如 map）把值与下标之间的映射存下来。这样就变成了在下标后面插入数，好做很多。

但是插入一个数会使后面的数的下标改变，而直接维护下标的成本很高，于是考虑一些不会被插入操作影响的东西，链表显然是可以的，但因为我比较笨所以赛时没有想到！

考虑两个相邻的元素 $x,y$，注意到在插入过程中这两个元素的相对位置永远不会改变，而且紧邻 $x$ 插入的元素永远在 $x$ 和 $y$ 之间，这形成了一棵树结构，直接维护即可。

```cpp
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

const int kN = 4e5 + 1;

int n, q, c, a[kN];
vector<int> e[kN];
bool v[kN];
map<int, int> d;

void D(int x) {
  if (!v[x]) {
    cout << a[x] << ' ';
  }
  reverse(e[x].begin(), e[x].end());
  for (int i : e[x]) {
    D(i);
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    d[a[i]] = i, e[i - 1].push_back(i);
  }
  c = n;
  cin >> q;
  for (int o, x, y; q--;) {
    cin >> o >> x;
    if (o == 1) {
      cin >> y;
      a[++c] = y, e[d[x]].push_back(d[y] = c);
    } else {
      v[d[x]] = 1;
    }
  }
  D(1);
  return 0;
}
```

---

## 作者：Kingna (赞：3)

## 问题陈述

给你一个长度为 $N$ 的序列 $A=(A_1,\ldots,A_N)$。$A$ 中的元素是不同的。

请按照给出的顺序处理 $Q$ 个查询。每个查询属于以下两种类型之一：

- `1 x y`：在 $A$ 中元素 $x$ 后面紧接着插入 $y$。当给出此查询时，保证 $x$ 存在于 $A$ 中。
- `2 x`：从 $A$ 中删除元素 $x$。当给出此查询时，保证 $x$ 存在于 $A$ 中。

保证在处理完每一个查询后，$A$ 都不是空的，并且其元素都是不同的。

处理完所有查询后，打印 $A$。


## 思路

这道题为什么可以用链表做呢？因为这道题只需要最后输出整个序列，而不是实时查询。题目保证 $A$ 中的元素是不同的，这也是可以用链表的核心。


所以链表写扩展性极低，所以比赛时写的分块。为什么某某部分人都写链表呢？不言而喻。但是又想到有个 `rope` 的玩意，于是很开心的写出了以下代码：

```c++
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#include <ext/rope>
using namespace __gnu_cxx;
using namespace std;

const int N = 4e5 + 5;

int n, a[N];
rope<int> b;

signed main() {
	scanf("%d", &n); 
	b.push_back(0);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		b.push_back(a[i]);
	}
	int q;
	scanf("%d",&q);
	while (q--) {
		int op, x, y;
		scanf("%d%d",&op,&x);
		if (op == 1) {
			scanf("%d",&y);
			b.insert(b.find(x)+1, y);
		}
		else {
			b.erase(b.find(x), 1);
		}
	}
	int t = b.size();
	for (int i = 1; i < t; i++) printf("%d ", b.at(i));
}
```

这份代码只过了 $10$ 个点，不知道是 rope 的 find 函数是 $O(n)$ 的，还是常数太大。

---

于是又去写分块了。

而分块思路简单，代码好调好写，清晰明了，常数小，大部分链表代码跑不过分块。

考虑把序列分成 $\sqrt n$ 块，每块用一个 `vector` 动态维护，即把这个块的所有数都放到对应的 `vector` 里面。在某个元素后面插入一个数时，只需要在这个元素的对应块的 `vector` 中插入，由于每块的 `vector` 大小只有 $\sqrt n$，所以插入的时间复杂度只有 $O(\sqrt n)$。删除一个数也是同样的道理。

但是，真的能保证每个 `vector` 都是 $\sqrt n$ 的大小吗？如果我们在固定一个位置加进很多个数，可能对应 `vector` 的大小就达到了 $O(n)$ 级别。所以我们考虑块重构。即对整个序列重新分组，使得所有 `vector` 的大小变平均。

什么时候可以块重构？块重构是需要消耗 $O(n)$ 的时间的，显然不能加一个数重构一次，可以间隔 $\sqrt n$ 次重构一次，块重构复杂度 $O(n\sqrt n)$。

总的时间复杂度也是 $O(n\sqrt n)$，事实上，vector 的 insert 非常快，所以不比链表慢多少。

注意事项：

* 题目不是在某个位置后面添加一个数，而是在某个元素后面添加一个数，所以需要开一个数组 $bel_x$ 代表 $x$ 在序列的第几个块内。

* 本题值域较大，用 $bel$ 数组需要离散化！用 map 复杂度就会变成 $O(n\sqrt n\log n)$，会 TLE！



```c++
// 394ms
#include <bits/stdc++.h>
using namespace std;

const int N = 6e5 + 5, M = 2000;

int n, q, a[N], lx[N], rx[N], len, b[N], tot;
int tmp[N], tl, sum[M], bel[N];
vector<int> bk[M];
// bk_i 存储这个块内的数
// lx_i,rx_i存储这个块的左右端点
// bel存储这个数所在的块 

struct edge {
	int op, l, r;
}ed[N]; 

signed main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), b[++tot] = a[i];
	int sq = sqrt(n);
	len = n / sq;
	for (int i = 1; i <= n / sq; i++) lx[i] = (i - 1) * sq + 1, rx[i] = lx[i] + sq - 1;
	if (n % sq) {
		len++;
		lx[len] = rx[len - 1] + 1;
		rx[len] = n;
	}
	int cnt = 0;
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		scanf("%d", &ed[i].op);
		if (ed[i].op == 1) scanf("%d%d", &ed[i].l, &ed[i].r), b[++tot] = ed[i].l, b[++tot] = ed[i].r;
		else scanf("%d", &ed[i].l); 
	}
	sort(b + 1, b + tot + 1);
	tot = unique(b + 1, b + tot + 1) - b - 1;
	for (int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + tot + 1, a[i]) - b;
	for (int i = 1; i <= q; i++) {
		if (ed[i].op == 1) ed[i].r = lower_bound(b + 1, b + tot + 1, ed[i].r) - b;
		ed[i].l = lower_bound(b + 1, b + tot + 1, ed[i].l) - b; 
	}
	for (int i = 1; i <= len; i++) {
		for (int j = lx[i]; j <= rx[i]; j++) bk[i].push_back(a[j]), bel[a[j]] = i; 
	}
	for (int cas = 1; cas <= q; cas++) {
		int op = 0, l = 0, r = 0;
		op = ed[cas].op;
		cnt++;
		if (op == 1) {
			l = ed[cas].l, r = ed[cas].r;
			int L = bel[l], lenb = bk[L].size(); // L是l所在的块 
			for (int i = 0; i < lenb; i++) {
				if (bk[L][i] == l) {
					l = i; // 扫描到l的位置 
					break;
				}
			}
			if (l == lenb - 1) bk[L].push_back(r);
			else bk[L].insert(bk[L].begin() + l + 1, r);  
			bel[r] = L;
			rx[L]++;
			for (int i = L + 1; i <= len; i++) lx[i]++, rx[i]++;
		}
		if (op == 2) {
			l = ed[cas].l;
			int L = bel[l], lenb = bk[L].size();
			for (int i = 0; i < lenb; i++) {
				if (bk[L][i] == l) {
					l = i;
					break;
				}
			}
			bel[bk[L][l]] = 0;
			bk[L].erase(bk[L].begin() + l);
			rx[L]--;
			for (int i = L + 1; i <= len; i++) lx[i]--, rx[i]--;
		}
		if (cnt >= 5 * sq) { // 一定次数后块重构 
			tl = 0;
			for (int i = 1; i <= len; i++) {
				for (auto j : bk[i]) tmp[++tl] = j;
			}
			sq = sqrt(tl);
			len = tl / sq;
			for (int i = 1; i <= tl / sq; i++) {
				lx[i] = (i - 1) * sq + 1, rx[i] = lx[i] + sq - 1; 
			}
			if (tl % sq) {
				len++;
				lx[len] = rx[len - 1] + 1;
				rx[len] = tl;
			}
			for (int i = 1; i <= len; i++) {
				bk[i].clear();
				for (int j = lx[i]; j <= rx[i]; j++) bk[i].push_back(tmp[j]), bel[tmp[j]] = i; 
			}
			cnt = 0;
		}
	}
	for (int i = 1; i <= len; i++) {
		if (bk[i].size() == 0) continue;	
		for (auto v : bk[i]) printf("%d ", b[v]);
	}
}
```

---

## 作者：aeaf (赞：1)

第一次写题解，写的不太好轻喷

首先题目给出重要信息所有数只出现一次，且给出删除和插入操作，故考虑链表进行维护

因为所有数只出现一次，所以我们可以根据这个数来找到它的   next 和 pre 。

于是剩下的就是链表的基本操作啦

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define next nxt
int n;
map<int,int> next,pre;
int head=1e10;
int a[N];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> a[i];
	}
	a[0]=head;
	next[head]=a[1];
	for(int i=1;i<n;i++){
		next[a[i]]=a[i+1];
		pre[a[i]]=a[i-1];
	}
	next[a[n]]=INT_MAX;
	pre[a[n]]=a[n-1];
  //构建链表，写的有点累赘
	int Q;
	cin >> Q;
	while(Q--){
		int op;
		cin >> op;
		if(op==2){
			int x;
			cin >> x;
			next[pre[x]]=next[x];
			pre[next[x]]=pre[x];
		}else{
			int x,y;
			cin >> x >> y;
			next[y]=next[x];
			pre[y]=x;
			pre[next[x]]=y;
			next[x]=y;
		}
	}
	while(next[head]!=INT_MAX){
		cout <<next[head]<<" ";
		head=next[head];
	}
	
	
	
	
	return 0;
}
```

---

## 作者：FallingFYC_ (赞：1)

[原题](https://www.luogu.com.cn/problem/AT_abc344_e)

e 比 d 简单（这是我的首场 AT）。

---
### 思路

看到对一个数组进行插入和删除两种操作，一眼双向链表。题目中并未给定元素的下标，只给了元素，需要开一个 `stl::map` 记录一下。

然后就没了（太水了吧）。

---
### 代码

我手写的链表。

```cpp
#include "bits/stdc++.h"
using namespace std;
struct node
{
    int num , lst , nxt;
}l[400005];
int n , a , cnt , q , op , x , y , fir;
map<int , int > pos;
int main()
{
    cin >> n;
    for (int i = 1 ; i <= n ; i++)
    {
        cin >> a;
        l[i] = {a , i - 1 , i + 1};
        pos[a] = i;
        if (i == 1) l[i].lst = -1;
        if (i == n) l[i].nxt = -1;
    }
    cnt = n; fir = 1;
    cin >> q;
    while (q--)
    {
        cin >> op >> x;
        if (op == 1)
        {
            cin >> y;
            pos[y] = ++cnt;
            l[cnt] = {y , pos[x] , l[pos[x]].nxt};
            if (l[pos[x]].nxt != -1) l[l[pos[x]].nxt].lst = pos[y];
            l[pos[x]].nxt = pos[y];
        }
        else
        {
            if (pos[x] == fir) fir = l[pos[x]].nxt;
            if (l[pos[x]].lst != -1) l[l[pos[x]].lst].nxt = l[pos[x]].nxt;
            if (l[pos[x]].nxt != -1) l[l[pos[x]].nxt].lst = l[pos[x]].lst;
            l[pos[x]] = {0 , -1 , -1};
            pos[x] = 0;
        }
    }
    node now = l[fir];
    while (1)
    {
        cout <<now.num << ' ';
        if (now.nxt == -1) break;
        now = l[now.nxt];
    }
    return 0;
}
```

---

## 作者：spacebar (赞：1)

这题要求我们在某个数字后面插入数字或删除某个数字，很容易想到链表。

不过正常的链表没法记录每个数的位置，要额外记录。

剩下的就是正常的链表操作了。

注意数组要开大，因为可能会插入更多数。

```
#include<bits/stdc++.h>
using namespace std;
int nxt[400010];
int lst[400010];
long long num[400010];
map<long long,int>pl;
int np;
int n,q;
int fr=1;
int cnt;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>num[i];
		pl[num[i]]=i;
		nxt[i-1]=i;
		lst[i]=i-1;
	}
	np=n;
	cin>>q;
	int val;
	long long aa,bb,aap;
	fr=1;
	cnt=n;
	while(q--){
		
		cin>>val;
		if(val==1){
			cnt++;
			cin>>aa>>bb;
			np++;
			aap=pl[aa];
			pl[bb]=np;
			num[np]=bb;
			lst[np]=aap;
			nxt[np]=nxt[aap];
			nxt[aap]=np;
			lst[nxt[np]]=np;
		}else{
			cnt--;
			cin>>aa;
			aap=pl[aa];
			if(fr==aap){
				fr=nxt[aap];
			}
			pl[aa]=0;
			nxt[lst[aap]]=nxt[aap];
			lst[nxt[aap]]=lst[aap];
		}
	}
	int tp=fr;
	while(cnt){
		cout<<num[tp]<<" ";
		tp=nxt[tp];
		cnt--;
	}
	return 0;
}
```

---

## 作者：FReQuenter (赞：1)

特定点插入、删除，考虑链表。

具体地，定义每个数的前驱和后驱。因为值域关系，使用 map 实现。其它就是链表的模板内容，具体可以参考代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int> nxt,pre;
signed main(){
	int n;
	cin>>n;
	int lst=0;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		nxt[lst]=x;
		pre[x]=lst;
		lst=x;
	}
	int q;
	cin>>q;
	while(q--){
		int op,x,y;
		cin>>op>>x;
		if(op==1){
			cin>>y;
			pre[nxt[x]]=y;
			pre[y]=x;
			nxt[y]=nxt[x];
			nxt[x]=y;
		}
		else{
			pre[nxt[x]]=pre[x];
			nxt[pre[x]]=nxt[x];
		}
	}
	int head=0;
	while(nxt[head]) cout<<nxt[head]<<' ',head=nxt[head];
}
```

---

## 作者：Oracynx (赞：1)

## [ABC344E] Insert or Erase 题解

### 思路分析

感觉难度还不如 D 题。

由于这道题涉及到了大量的插入和删除操作，我们使用链表解决。

节点类的定义如下：

```cpp
class node
{
  public:
    int x;
    node *left;
    node *right;
    node()
    {
        x = 0;
        left = nullptr;
        right = nullptr;
    }
};
```

变量名为字面意思。

除此以外，我们用一个 `std::map<int, std::string>` 存储对应数值的节点的地址。每次插入和删除的代码如下：

```cpp
if (op == 1)
{
    int x, y;
    scanf("%d%d", &x, &y);
    auto b = map[x];
    auto k = new node;
    k->x = y;
    k->left = b;
    k->right = b->right;
    b->right->left = k;
    b->right = k;
    map[y] = k;
}
else if (op == 2)
{
    int x;
    scanf("%d", &x);
    auto k = map[x];
    node *l, *r;
    l = k->left;
    r = k->right;
    k->left->right = r;
    k->right->left = l;
    delete map[x];
    map[x] = nullptr;
}
```

### 代码实现

比较基础的链表题。

```cpp
#include <cstdio>
#include <unordered_map>
constexpr int MaxN = 2e5 + 5;
class node
{
  public:
    int x;
    node *left;
    node *right;
    node()
    {
        x = 0;
        left = nullptr;
        right = nullptr;
    }
};
int n, q;
node *head;
node *tail;
std::unordered_map<int, node *> map;
int main()
{
    scanf("%d", &n);
    head = new node;
    tail = new node;
    head->left = tail;
    head->right = tail;
    tail->left = head;
    tail->right = head;
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        auto k = new node;
        k->x = x;
        k->left = tail->left;
        k->right = tail;
        tail->left->right = k;
        tail->left = k;
        map[x] = k;
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; i++)
    {
        int op;
        scanf("%d", &op);
        if (op == 1)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            auto b = map[x];
            auto k = new node;
            k->x = y;
            k->left = b;
            k->right = b->right;
            b->right->left = k;
            b->right = k;
            map[y] = k;
        }
        else if (op == 2)
        {
            int x;
            scanf("%d", &x);
            auto k = map[x];
            node *l, *r;
            l = k->left;
            r = k->right;
            k->left->right = r;
            k->right->left = l;
            delete map[x];
            map[x] = nullptr;
        }
    }
    for (node *cur = head->right; cur != tail; cur = cur->right)
    {
        printf("%d ", cur->x);
    }
    printf("\n");
    return 0;
}
```

---

## 作者：_Weslie_ (赞：1)

### 思路

由题面我们容易联想到链表。

但是我们显然不能直接写个链表，因为这样不仅不好查找，而且写起来也不方便。

这时我们就要使用 ```map```，设 $mp_i$ 表示 $i$ 的后一个数（即后缀）。

同理 $pre_i$ 表示 $i$ 的前缀。

**$i$ 表示的是数字，不是下标！**

### 代码实现

为什么要记录 $pre$？因为这样在删除时可以 $\operatorname{O}(1)$ 删除，否则需要在队伍中查找后删除，时间复杂度劣。

同时，如果删除的是第一个元素，要将队头进行修改。

### Code

```
#include<iostream>
#include<map>
using namespace std;
map<int,int>mp;
map<int,int>pre;
int q,n,head;
int a[200005];
int main() {
	cin>>n;
	for(int i=1; i<=n; i++) {
		cin>>a[i];
		mp[a[i-1]]=a[i];
		pre[a[i]]=a[i-1];
	}
	head=a[1];
	cin>>q;
	while(q--) {
		int opt,x,y;
		cin>>opt>>x;
		if(opt==1) {
			cin>>y;
			mp[y]=mp[x];
			pre[y]=x;
			pre[mp[y]]=y;
			mp[x]=y;
		} else {
			if(head==x) {
				y=mp[x];
				mp[pre[x]]=y;
				pre[y]=pre[x];
				head=y;
			} else {
				y=mp[x];
				mp[pre[x]]=y;
				pre[y]=pre[x];
			}
		}
	}
	int _=head;
	while(mp[_]!=0) {
		cout<<_<<' ';
		_=mp[_];
	}
	cout<<_;
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc344_e)

## 思路

看到插入、删除操作马上想到链表。又看到数据范围是 $1\le A_i,x,y\le 10^9\space(1\le i\le N)$，又可以想到用 map 保存。于是本题做法为：用 map 保存的双向链表。

**插入操作**：下一个点的前驱记录为 $y$；加入点的前驱为 $x$，后继为下一个点；最后记录这个点的后继为 $x$。**最后修改 $x$ 的后继**防止内存丢失。

**删除操作**：上一个点的后继记录为下一个点，下一个点的前驱记录为上一个点。

- 可选优化：把 ``map``替换为复杂度更优的 ``unordered_map``。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,q,a[N];
struct node{
	int head,tail;//head 前驱，tail 后继。
};unordered_map<int,node>mp;
int main(){
	cin>>n;
	for(int i=1;i<=n;++i)a[i]=read();
	mp[0].tail=a[1];//记得保存 0 的后继，查询时用。
	for(int i=1;i<=n;++i){
		mp[a[i]].head=a[i-1];//记录每个点的前驱和后继。
		mp[a[i]].tail=a[i+1];
	}
	cin>>q;
	while(q--){
		int op,x;
        cin>>op>>x;
		if(op==1){
			int k;
            cin>>k;
			mp[mp[x].tail].head=k;
			mp[k].head=x;
			mp[k].tail=mp[x].tail;
			mp[x].tail=k;//最后改。
		}
		else{
			mp[mp[x].head].tail=mp[x].tail;
			mp[mp[x].tail].head=mp[x].head;
			mp[x].head=mp[x].tail=0;
		}
	}
	int k=mp[0].tail;
	while(k){
		cout<<k<<" ";//从第一个点一直输出。
		k=mp[k].tail;
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/150189553)

---

## 作者：FBW2010 (赞：0)

# 题意简述

[传送门](https://www.luogu.com.cn/problem/AT_abc344_e)

给定一个数列和 $Q$ 次操作。操作有两种：在 $x$ 后插入 $y$，或删除 $x$。

# 思路

根据题意，我们需要一个能在 $O(\log n)$ 以下插入与删除的数据结构。于是我们可以很容易地想到链表，它的复杂度为 $O(n+q)$，能通过此题。

由于需要删除指定的一个数，所以要使用双向链表。同时数的范围较大，用数组存不下，而本蒟蒻又不会指针，于是就用 map 代替了数组。

其余详见代码。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,a[200005];
map<int,int> le,ri; //左指针和右指针 
int main(){
	//初始化 
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		le[a[i]]=a[i-1];
		ri[a[i-1]]=a[i];
	}
	ri[a[n]]=-1;
	
	//双向链表基操 
	scanf("%d",&q);
	while(q--){
		int f,x,y;
		scanf("%d",&f);
		if(f==1){
			scanf("%d %d",&x,&y);
			//插入 
			ri[y]=ri[x];
			le[y]=x;
			le[ri[x]]=y;
			ri[x]=y;
			
		}
		else{
			scanf("%d",&x);
			//删除 
			ri[le[x]]=ri[x];
			le[ri[x]]=le[x];
			
		}
	}
	
	//遍历输出 
	int x=0;
	while(ri[x]!=-1){
		x=ri[x];
		printf("%d ",x);
	}
	return 0;
}
```

---

## 作者：hellolin (赞：0)

# ABC344E Insert or Erase 题解

前往 [博客暂时关闭] 可能获得更好阅读体验。

不会真的有人写分块重构吧/kx

看到 **在某元素后插入** 和 **删除某元素** 这样的操作，第一反应应该是链表。

因为元素都唯一，我们使用一个 `unordered_map` 存储整数对应链表的哪个指针（或迭代器），插入操作更新被插入元素的指针，之后就是正常的链表模板题啦。

复杂度 $O(N)$。

## 代码实现

仅给出核心代码。

### 手写链表版

不知道为啥赛时 STL 链表写炸了，估计迭代器没处理好，最后是手写的/kel

一定要注意空指针的判定！

有关下面提到的悬空指针，请参阅 [维基百科](https://zh.wikipedia.org/wiki/%E8%BF%B7%E9%80%94%E6%8C%87%E9%92%88)。

``` cpp
namespace hellolin {
int n, q;
struct node {
  int x;
  node *pre, *nxt;
} rt, *cur;
unordered_map<int, node *> it;
void ins(int x, int y) {
  cur = it[x];
  auto tmp = new node();
  tmp->x = y;
  tmp->pre = cur, tmp->nxt = cur->nxt;
  if (cur->nxt) cur->nxt->pre = tmp;
  cur->nxt = tmp;
  it[y] = tmp;
}
void del(int x) {
  cur = it[x];
  if (cur->pre) cur->pre->nxt = cur->nxt;
  if (cur->nxt) cur->nxt->pre = cur->pre;
  // tmp 的作用是防止 cur 变为悬空指针
  // 但我这里 cur 是循环使用的，不加应该也没啥大问题
  auto tmp = cur;
  cur = cur->nxt;
  delete tmp;
  it[x] = nullptr;
}
void main() {
  cin >> n;
  cur = &rt;
  for (int i = 1, x; i <= n; ++i) {
    cin >> x;
    auto tmp = new node();
    tmp->x = x, tmp->pre = cur;
    cur->nxt = tmp, cur = tmp;
    it[x] = cur;
  }
  cin >> q;
  for (int i = 1, op, x, y; i <= q; ++i) {
    cin >> op >> x;
    if (op == 1) {
      cin >> y;
      ins(x, y);
    } else {
      del(x);
    }
  }
  cur = rt.nxt;
  for (; cur; cur = cur->nxt) cout << cur->x << ' ';
  cout << '\n';
}
} // namespace hellolin
```

### std::list 版

果然还是 STL 大法好！

``` cpp
namespace hellolin {
int n, q;
list<int> a;
unordered_map<int, list<int>::iterator> it;
void main() {
  cin >> n;
  for (int i = 1, x; i <= n; ++i) {
    cin >> x;
    it[x] = a.insert(a.end(), x);
  }
  cin >> q;
  for (int i = 1, op, x, y; i <= q; ++i) {
    cin >> op >> x;
    if (op == 1) {
      cin >> y;
      it[y] = a.insert(next(it[x]), y);
    } else {
      a.erase(it[x]);
      it.erase(x);
    }
  }
  for (const int &i : a)
    cout << i << ' ';
  cout << '\n';
}
} // namespace hellolin
```

---

## 作者：odt63 (赞：0)

## Solution:

本题需要模拟一个链表，考虑需要加入时需要知道一个点的后继，删除时需要知道一个点的前驱和后继，所以我们采用双向链表维护。用数组维护每个点的前驱和后继。由于值域是 $10^9$ 的，所以我们采用`map`维护。

首先考虑构建链表。我们把序列中的点顺次放入链表中，具体地说，对于每个点 $a_i$，它的前驱是 $a_{i-1}$，后继是 $a_{i+1}$。特别地，我们建立两个虚拟节点，分别作为 $a_1$ 的前驱和 $a_n$ 的后继。

考虑添加点。我们很容易得知要添加点的左右两个点 $L$ 和 $R$，设添加的点为 $X$，对于后继，把 $L$ 的后继连向 $X$，$X$ 的后继连向 $R$，前驱同理，如图所示：

![](https://s21.ax1x.com/2024/03/10/pFy8CH1.png)

![](https://s21.ax1x.com/2024/03/10/pFy89BR.png)

考虑删除。我们很容易得知要删除点的左右两个点 $L$ 和 $R$，把 $L$ 的后继连向 $R$，$R$ 的前驱连向 $L$ 如图所示：

![](https://s21.ax1x.com/2024/03/10/pFy8iAx.png)

最后从最左边的虚拟点开始，向右寻找后继输出，直至寻找到最右边的点，输出结束。

时间复杂度 $O(n \log n)$。

## Code:

```cpp
// By 0x0F
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9') {x = x * 10 + ch - 48; ch = getchar();}
    return x * f;
}
const int pL = -1, pR = 1145141919810LL;
unordered_map<int ,int> nxt, frm;
int a[200010];
signed main() {
    int n = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    a[0] = pL, a[n + 1] = pR;
    nxt[pL] = a[1], nxt[a[n]] = pR, frm[pR] = a[n], frm[a[1]] = pL;
    for (int i = 1; i < n; i++) nxt[a[i]] = a[i + 1];
    for (int i = 2; i <= n; i++) frm[a[i]] = a[i - 1];
    int q = read();
    while (q--) {
        int op = read();
        if (op == 1) {
            int x = read(), y = read();
            int xl = x, xr = nxt[x];
            nxt[xl] = y, nxt[y] = xr;
            frm[xr] = y, frm[y] = xl;
        } else {
            int x = read();
            int xl = frm[x], xr = nxt[x];
            nxt[xl] = xr, frm[xr] = xl;
        }
        int st = nxt[pL];
    }
    int st = nxt[pL];
    while (st != pR) {
        printf("%lld ", st);
        st = nxt[st];
    } 
    return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

省流：赛时脑子被僵尸啃了！

因为我们不能快速找到 $x$，所以我们可以使用块状链表！

因为我懒得打链表，所以可以块内维护 `vector`！

用 `unordered_map` 维护每个块内有哪些值！

时间复杂度 $O(n\sqrt{n})$！

但是会被卡常！

转化一下，可以想到维护每个元素是在哪个块里面的！

因为担心 `map` 会被卡，所以离散化一下用数组存就行了！

时间复杂度 $O(n\sqrt{n})$，卡过去了！

[幸好时限是 2s！](https://atcoder.jp/contests/abc344/submissions/51069807)

---

## 作者：Genius_Star (赞：0)

### 思路：

~~链表板子……~~

首先数字的范围太大，先将所有操作离线下来，将数字进行**离散化**处理。

因为操作是在一个数后插入另外一个数和删除一个数，那么考虑定义 $next_i$ 和 $pre_i$ 表示数 $i$ 的上一个数和下一个数。

那么在 $x$ 后插入 $y$，相当于：

$$next_y=next_x$$

$$pre_{next_x}=y$$

$$pre_y=x$$

$$next_x=y$$

将 $x$ 删除，相当于：

$$next_{pre_x}=next_x$$

$$pre_{next_x}=pre_x$$

但是这样我们会发现一个问题，无法找到序列的第一个数，就无法按顺序遍历整个序列。

那么考虑刚开始的时候建立一个超级节点 $root$ 连接初始的第一个数即可。

时间复杂度为 $O(N \log N + N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=400400;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
	ll next,pre;
}A[N];
struct Ques{
	ll op;
	ll x,y;
}Q[N];
ll n,q,op,x,y,cnt;
ll a[N],b[N];
void add(ll x,ll y){
	A[x].next=y;
	A[y].pre=x;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		b[++cnt]=a[i];
	}
	q=read();
	for(int i=1;i<=q;i++){
		op=read(),x=read();
		if(op==1){
			y=read();
			b[++cnt]=y;
			Q[i]={op,x,y};
		}
		else
		  Q[i]={op,x,0};
	}
	sort(b+1,b+cnt+1);
	cnt=unique(b+1,b+cnt+1)-(b+1);
	for(int i=1;i<=n;i++)
	  a[i]=lower_bound(b+1,b+cnt+1,a[i])-b;
	for(int i=1;i<=q;i++){
	    if(Q[i].op==1)
	      Q[i].y=lower_bound(b+1,b+cnt+1,Q[i].y)-b;
	    Q[i].x=lower_bound(b+1,b+cnt+1,Q[i].x)-b;
	}
	add(0,a[1]);
	for(int i=1;i<n;i++)
	  add(a[i],a[i+1]);
	for(int i=1;i<=q;i++){
		if(Q[i].op==1){
			ll t=A[Q[i].x].next;
			add(Q[i].x,Q[i].y);
			add(Q[i].y,t);
		}
		else
		  add(A[Q[i].x].pre,A[Q[i].x].next);
	}
	ll x=0;
	while(1){
		if(!A[x].next)
		  break;
		write(b[A[x].next]);
		putchar(' ');
		x=A[x].next;
	}
	return 0;
}
```

---

