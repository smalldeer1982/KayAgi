# Replace the Numbers

## 题目描述

You have an array of integers (initially empty).

You have to perform $ q $ queries. Each query is of one of two types:

- " $ 1 $ $ x $ " — add the element $ x $ to the end of the array;
- " $ 2 $ $ x $ $ y $ " — replace all occurrences of $ x $ in the array with $ y $ .

Find the resulting array after performing all the queries.

## 说明/提示

In the first example, the array changes as follows:

 $ [] $ $ \rightarrow $ $ [3] $ $ \rightarrow $ $ [3, 1] $ $ \rightarrow $ $ [3, 2] $ $ \rightarrow $ $ [3, 2, 2] $ $ \rightarrow $ $ [3, 2, 2, 1] $ $ \rightarrow $ $ [3, 2, 2, 1, 2] $ $ \rightarrow $ $ [3, 2, 2, 3, 2] $ .

In the second example, the array changes as follows:

 $ [] $ $ \rightarrow $ $ [1] $ $ \rightarrow $ $ [1, 2] $ $ \rightarrow $ $ [1, 2, 1] $ $ \rightarrow $ $ [1, 2, 1] $ .

In the third example, the array changes as follows:

 $ [] $ $ \rightarrow $ $ [] $ $ \rightarrow $ $ [1] $ $ \rightarrow $ $ [1, 4] $ $ \rightarrow $ $ [1, 4, 2] $ $ \rightarrow $ $ [1, 4, 4] $ $ \rightarrow $ $ [1, 3, 3] $ $ \rightarrow $ $ [1, 3, 3, 2] $ $ \rightarrow $ $ [1, 3, 3, 7] $ .

## 样例 #1

### 输入

```
7
1 3
1 1
2 1 2
1 2
1 1
1 2
2 1 3```

### 输出

```
3 2 2 3 2```

## 样例 #2

### 输入

```
4
1 1
1 2
1 1
2 2 2```

### 输出

```
1 2 1```

## 样例 #3

### 输入

```
8
2 1 4
1 1
1 4
1 2
2 2 4
2 4 3
1 2
2 2 7```

### 输出

```
1 3 3 7```

# 题解

## 作者：sszcdjr (赞：13)

## 题面简述

给出 $q$ 个操作，操作分为两种：

* ```1 x``` 在序列末尾插入数字 $x$。
* ```2 x y``` 把序列中的所有 $x$ 替换为 $y$。

求这个序列操作后的结果。

## 思路

发现这题一个重要的性质：**离线询问**。

即它不要你每次操作完了就提问，而是最后一次提问。

考虑每次 $2$ 操作的效果。

将所有以前插入的 $x$ 变成 $y$。

我们可以考虑从后往前扫一遍，定义一个 $f$ 数组表示到目前为止 $x$ 实际上表示的数。遇到操作 $1$ 直接将 $f_x$ 塞入数组。遇到操作 $2$ 我们将 $f_x$ 改成 $f_y$ 即可。（注意改成 $f_y$ 而不是 $y$！）

最后逆序输出数组即可。

时间空间复杂度 $O(q)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int bel[500005];
int a[500005];
int opt[500005],x[500005],y[500005];
signed main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	int q;
	cin>>q;
	for(int i=1;i<=500000;i++){
		bel[i]=i;
	}
	for(int i=1;i<=q;i++){
		cin>>opt[i];
		if(opt[i]==1){
			cin>>x[i];
		}
		else{
			cin>>x[i]>>y[i];
		}
	}
	int k=0;
	for(int i=q;i>=1;i--){
		if(opt[i]==1){
			k++;
			a[k]=bel[x[i]];
		}
		else{
			bel[x[i]]=bel[y[i]];
		}
	}
	for(int i=k;i>=1;i--){
		cout<<a[i]<<" ";
	}
	return 0;
}
/* things to check
1.  int overflow or long long memory need
2.  recursion/array/binary search/dp/loop bounds
3.  precision
4.  special cases(n=1,bounds)
5.  delete debug statements
6.  initialize(especially multi-tests)
7.  = or == , n or m ,++ or -- , i or j , > or >= , < or <= , - or =
8.  keep it simple and stupid
9.  do not delete, use // instead
10. operator priority
11. is there anything extra to output?
12. if you don't know where the bug is , try to clear some parts of the code
 and check each part seperately.
13. ...
*/

```

---

## 作者：cmaths (赞：3)

一种现有题解中没出现的简洁的 `set` 做法。

可以发现难点在于操作 `2`，于是我们需要一种可以快速查询给定数值的所有下标，并且支持合并的数据结构。

发现值域在 $5 \cdot 10^5$ 之内，自然地想到在值域上建立 `set`。

于是操作 `1` 转化为在对应 `set` 添加当前下标，操作 `2` 转化为合并两个值上的 `set`，使用启发式合并保证复杂度。

最后输出时将每个 `set` 中的元素对应位置赋值即可。

时间复杂度 $O(n\operatorname{log}n)$。

代码：

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>

using namespace std;

const int N = 500000, A = 500000;
set <int> s[A + 5];
int a[N + 5];

int cnt = 0;
void solve()
{
	int op;
	scanf("%d", &op);
	if(op == 1)
	{
		int x;
		scanf("%d", &x);
		cnt++;
		s[x].insert(cnt);
	}
	else
	{
		int x, y;
		scanf("%d %d", &x, &y);
		if(x == y)
		{
			return;
		}
		if(s[x].size() > s[y].size())
		{
			swap(s[x], s[y]);
		}
		s[y].insert(s[x].begin(), s[x].end());
		s[x].clear();
	}
}

void out()
{
	for(int i = 1; i <= A; i++)
	{
		while(s[i].size())
		{
			int x = *s[i].begin();
			s[i].erase(s[i].begin());
			a[x] = i;
		}
	}
	for(int i = 1; i <= cnt; i++)
	{
		printf("%d ", a[i]);
	}
}

int main()
{
	int qq;
	scanf("%d", &qq);
	while(qq--)
	{
		solve();
	}
	out();
	return 0;
}
```


---

## 作者：2huk (赞：2)

> 维护一个初始为空的队列，执行 $q$ 次操作：
>
> - `1 x`：在数列末尾加一个数字；
> - `2 x y`：将队列中所有值为 $x$ 的数的值替换成 $y$。
>
> 输出最终队列。
>
> $1 \le q, x, y \le 5 \times 10^5$。

可以发现值域很小，因此维护 $5 \times 10^5$ 个 set，其中 $S_i$ 表示目前队列中所有值为 $i$ 的元素出现的位置。

对于两种操作：

- 操作一：额外维护 $n$ 表示目前队列长度，然后在集合 $S_x$ 中添加 $n$；
- 操作二：将 $S_x$ 中的元素全部移到 $S_y$ 中。仿照 [ABC329F](https://www.luogu.com.cn/problem/AT_abc329_f) 的做法启发式合并即可。

最后统计答案。若令 $\{a\}$ 表示最终的答案序列，那么若 $j \in S_i$ 则 $a_j = i$。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 500010;

int q, n, op, x, y;
set<int> S[N];
int res[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> q;
	while (q -- ) {
		cin >> op >> x;
		if (op == 1) S[x].insert( ++ n);
		else {
			cin >> y;
			if (x == y) continue;
			if (S[x].size() < S[y].size()) {
				for (int i : S[x]) S[y].insert(i);
				S[x].clear();
			}
			else {
				for (int i : S[y]) S[x].insert(i);
				S[y].clear();
				swap(S[x], S[y]);
			}
		}
	}
	
	for (int i = 1; i < N; ++ i )
		for (int j : S[i])
			res[j] = i;
	
	for (int i = 1; i <= n; ++ i ) cout << res[i] << ' ';
	
	return 0;
}
```



---

## 作者：Presentation_Emitter (赞：2)

题意：给一个空序列和两种操作。`1` 操作在序列末尾插入一个值 $x$。`2` 操作将序列中所有 $x$ 改成 $y$。求所有操作后的序列。

~~直接贺未来日记（bs）~~

用并查集维护数列里哪些位置的值相同，然后用一个数组 $val$ 表示每个位置代表什么值，再用数组 $tr$ 表示每个值对应的位置。然后就做完了。时间复杂度 $\Theta(q \cdot \alpha(q))$

不理解这个题为什么要放在 E 的位置。

赛时代码：

```cpp
ll q,n,fa[500005],val[500005],tr[500005],a[500005];
il ll getfa(ll x){while(x^fa[x])x=fa[x]=fa[fa[x]];ret x;}
int main()
{
	q=rd();
	for(int i=1;i<=q;++i)
	{
		ll op=rd(),x=rd(),y;
		if(op==1)a[++n]=i,fa[i]=i,val[i]=x,(tr[x])?fa[i]=tr[x]:(tr[x]=i);
		else
		{
			y=rd();
			if(x==y||!tr[x])continue;
			if(!tr[y])val[tr[y]=tr[x]]=y,tr[x]=0;
			else fa[getfa(tr[x])]=getfa(tr[y]),tr[x]=0,fa[i]=i;
		}
	}
	for(int i=1;i<=n;++i)prt(val[getfa(a[i])]," \n"[i==n]);
	ret 0;
}
```

---

## 作者：cff_0102 (赞：1)

考虑建立一个数组 $b$，$b_i$ 表示到目前为止，在 $a$ 数组中的数 $i$ 最后会变成 $b_i$。

接下来考虑逆序进行操作。

当处理到操作 $2$ 时，可以知道目前所有的 $x$ 都会变成 $y$，然后在“之后”（因为是逆序，所以已经处理过了）的操作 $2$ 中可能再变成其它的数。因为“之后”的操作已经被我们处理了，我们知道在这个操作“之后”，数字 $y$ 会最终变成 $b_y$。又因为这个操作时所有的 $x$ 会变成 $y$，所以这个操作之后，所有的 $x$ 最终都会变成 $b_y$。因此，碰到操作 $2$ 时，直接将 $b_x$ 的值赋值为 $b_y$，表示到目前为止（在“之前”的操作还没有处理）所有的 $x$ 都会变成 $b_y$。

当处理到操作 $1$ 时，我们知道数字 $x$ 插入进来后它会变成怎么样（会变成 $b_x$），而在它插进来“之前”（还没有处理）的操作实际上不会对它造成影响。所以直接将 $b_x$ 插到一个记录 $a$ 数组最后的样子的数组（代码中是 $s$ 数组）里面即可。

因为逆序操作（最后一次处理的操作 $1$ 实际上是第一次处理的操作 $1$，这时插入的数本应该在最终数组的最前面），所以最后的 $s$ 数组还要反过来输出。

```cpp
#include<bits/stdc++.h>
using namespace std;
int c[500005],x[500005],y[500005];// 记录操作 
int s[500005],b[500005];
int main(){
	ios::sync_with_stdio(false);
	int q;cin>>q;// 操作次数
	for(int i=0;i<q;i++){
		cin>>c[i]>>x[i];
		if(c[i]==2)cin>>y[i];
	}// 输入并存储操作
	int l=0;// 表示最终数组的长度 
	for(int i=0;i<500005;i++)b[i]=i;// 预处理 b 数组，表示没有操作时数字 i 最终还是数字 i 
	for(int i=q-1;i>=0;i--){// 逆序处理 
		if(c[i]==1){
			// a 数组中插入了 x[i]，所以在 s 数组中插入 b[x[i]] 
			s[l++]=b[x[i]];
		}else{
			// 将 b[x] 赋值为 b[y]，原因见上面解析
			b[x[i]]=b[y[i]];
		}
	}
	for(int i=l-1;i>=0;i--){
		cout<<s[i]<<" ";// 逆序输出最终的答案 
	}
	return 0;
}
```

---

## 作者：GaryH (赞：1)

# CF1620E 题解

**题意**：

维护一个初始为空的序列，要求支持两种操作：

1. $1,x$： 在序列末尾添加一数 $x$；
2. $2,x,y$：将序列中所有值为 $x$ 的数改成 $y$。

**做法**：

首先，为方便叙述，我们将一个数的值定义成成该数的颜色。

因为两个颜色相等的数永远不可能变得不相等，故我们可以用树形结构表达数之间的关系。

我们将每个数看成一个节点，那么每个新加进序列的点所在树的根就是自己。

而我们恰当的维护这个树形结构，最后每个节点所在树的根的颜色就是该节点对应数的颜色。

我们对每个颜色开一个 vector，记录当前有哪些根节点是这个颜色，

同时我们再记两个数组： $c_u$ 代表点 $u$ 的颜色是什么，$fa_u$ 代表点 $u$ 的父亲是哪个点。

执行 $1,x$ 操作时，我们建一个新点代表当前新加的数，

并将这个点的颜色设置成 $x$，父亲设置成自己；

在执行 $2,x,y$ 操作时，我们可以新建一个虚拟点 $u$，

然后将颜色 $x$ 的 vector 中每个点的父亲都赋成 $u$，再将这个 vector 清空。

最后，我们将虚拟节点 $u$ 的颜色设置成 $y$，并将点 $u$ 放入颜色 $y$ 的 vector 中。

在所有操作的最后，我们只需要遍历整棵树，求出每个点所在树中的根节点的颜色即可。

这样做的复杂度看似很高，但实际上是线性的，因为：

我们定义全局的势能为 $\phi$，实际意义为所有 vector 中的点数和，则：

初始时 $\phi=0$，每一次 $1,x$ 操作只将 $\phi$ 加一，

而我们设某次 $2,x,y$ 操作遍历了 $t$ 个点，则 $\phi$ 会减少 $t-1$。

也就是说，我们每次操作，无论哪种，都会让势能加一，

而我们也有可能花费若干数量的时间复杂度，去减少同样数量的势能。

因为势能的总增加量是 $q$，故总时间复杂度是 $O(q)$ 级别的。

**code**：

```
#define pb push_back
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)

const int N (1e6 + 10);

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') f = ch == '-' ? -1 : 1, ch = getchar();
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}

int tot;
int cnt;
int q, n;
int c[N];
int fa[N];
vector < int > col[N];

int f_set (int x) {
	if (fa[x] == x) return x;
	return fa[x] = f_set (fa[x]);
}

int main() {
	q = read(), n = 5e5;
	tot = 0, cnt = n;
	rep (i, 1, n * 2) fa[i] = i;
	while (q--) {
		int op = read(), x, y;
		if (op == 1) col[x = read()].pb(++tot), c[tot] = x;
		else {
			x = read(), y = read(), ++cnt;
			for (int u : col[x]) fa[u] = cnt;
			col[x].clear(), col[y].pb(cnt), c[cnt] = y;
		}
	}
	rep (i, 1, tot) {
		int rt = f_set (i);
		printf ("%d ", c[rt]);
	}
	return 0;
}
```



---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1620E)

------------
# 思路：
1. 影响复杂度的是第二种操作，如果将一个数组中所有的 $x$ 变为 $y$，极其影响复杂度，考虑使用数组标记。

2. ``` p[i] = j``` 代表数组中所有的 $i$ 变为 $j$。

3. 从前往后操作的话，出现第二种操作：它的作用域在该数之前，但是我们没有好的办法进行改变。所以我们可以从后往前来，先用 ```p[i]``` 记录 $i$ 变为 $j$，然后之后出现 $i$ 的话，直接将 ```p[i]```加入答案中。这样类似由结果往前推导，有点类似后缀数组计算。

4. 最后的答案是倒序的，我们只要反转一下即可。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int unsigned long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
int n,a[N],q,x[N],y[N],z[N],s[N];
signed main(){
	cin>>q;
	for(int i=1;i<=q;i++){
		cin>>x[i]>>y[i];
		if(x[i]==2){
			cin>>z[i];
		}
	}
	for(int i=1;i<=N;i++){
		s[i]=i;
	}
	for(int i=q;i>=1;i--){
		if(x[i]==1){
			a[++n]=s[y[i]];
		}else{
			s[y[i]]=s[z[i]];
		}
	}
	for(int i=n;i>=1;i--){
		cout<<a[i]<<" ";
	}
	return 0;
}
```
完结撒花~

---

## 作者：Inui_Sana (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1620E)

解题思路：链表

看到这道题，发现可以用一个链表来维护这些操作。创建出一个链表，存储数 $x$ 所在位置。

对于操作 $1$，将它在序列中所在的位置 $i$ 连上头节点为 $x$ 的链表中，时间复杂度 $O(1)$。

对于操作 $2$，则将当前 $x$ 链表中的所有节点连上头节点为 $y$ 的链表中，将 $y$ 的尾节点连上 $x$ 的头节点即可。时间复杂度 $O(1)$。

总时间复杂度 $O(q)$。

代码：

```cpp

#include<cstdio>
using namespace std;
typedef long long ll;
const int maxn=5e5+7,inf=2147483647;
const int mod=1;
int n,m,cnt,d[maxn];
int tot,head[maxn],tail[maxn];
struct node{
	int id,nxt;
}e[maxn];
signed main(){
	scanf("%d",&m);
	for(int i=1,op,x,y;i<=m;i++){
		scanf("%d",&op);
		if(op==1){
			scanf("%d",&x);
			e[++tot]={++n,0};
			if(head[x])e[tail[x]].nxt=tot;//尾插法
			else head[x]=tot;
			tail[x]=tot;
		}else{
			scanf("%d%d",&x,&y);
			if(!head[x]||x==y)continue;//需要特判一下x==y的情况
			if(!head[y])head[y]=head[x];
			else e[tail[y]].nxt=head[x];
			tail[y]=tail[x];
			head[x]=0;tail[x]=0;
		}
	}
	for(int i=1;i<=500000;i++){
		if(!head[i])continue;
		int now=head[i];
		while(now){
			d[e[now].id]=i;//最后处理每个数位置
			now=e[now].nxt;
		}
	}
	for(int i=1;i<=n;i++)printf("%d ",d[i]);
}
```

---

## 作者：Coros_Trusds (赞：0)

暗中观察兔队审题解，发现审到这篇了。

改了。

# 题目大意

维护一个数列，这个数列初始为空。

对于这个数列，总共有 $q$ 次操作，每次操作分为如下两个种类：

1. `1 x`，意为在数列末尾加一个数字。
2. `2 x y`，意为将数列中所有值为 $x$ 的数的值替换成 $y$。

请在 $q$ 次操作后，输出这个数列。

# 题目分析

考虑使用并查集(DSU)。

我们令 $val_i$ 表示位置 $i$ 的值，$num_i$ 表示元素 $i$ 对应的位置，再用并查集维护相同值。

+ 如果当前需要在末尾添加一个数字 $x$：

> 直接暴力在序列中插入 $x$，然后初始化该元素对应的值即可。
>
> 即 $val[now\_index]\gets x$。
>
> 给值 $x$ 一个位置（位置使用并查集维护，故只需要保存序列中任意一个值为 $x$ 的数的下标）

+ 将所有值为 $x$ 的数替换为 $y$ 值：

> 分类讨论一下：
> 
> 若 $y$ 没有出现过，那么直接交换 $x,y$ 的所有信息就好了。
>
> 如 $y$ 出现过，那么将这两个数的位置合并（就是 $y$ 现在的数量包含原来 $y$ 的数量和原来 $x$ 的数量之和）。

**并查集注意初始化。**

# 代码

```cpp
//2022/1/7

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <cstdio>

#include <climits>//need "INT_MAX","INT_MIN"

#include <cstring>//need "memset"

#define enter() putchar(10)

#define debug(c,que) cerr<<#c<<" = "<<c<<que

#define cek(c) puts(c)

#define blow(arr,st,ed,w) for(register int i=(st);i<=(ed);i++)cout<<arr[i]<<w;

#define speed_up() cin.tie(0),cout.tie(0)

#define endl "\n"

#define Input_Int(n,a) for(register int i=1;i<=n;i++)scanf("%d",a+i);

#define Input_Long(n,a) for(register long long i=1;i<=n;i++)scanf("%lld",a+i);

#define mst(a,k) memset(a,k,sizeof(a))

namespace Newstd
{
	inline int read()
	{
		int x=0,k=1;
		char ch=getchar();
		while(ch<'0' || ch>'9')
		{
			if(ch=='-')
			{
				k=-1;
			}
			ch=getchar();
		}
		while(ch>='0' && ch<='9')
		{
			x=(x<<1)+(x<<3)+ch-'0';
			ch=getchar();
		}
		return x*k;
	}
	inline void write(int x)
	{
		if(x<0)
		{
			putchar('-');
			x=-x;
		}
		if(x>9)
		{
			write(x/10);
		}
		putchar(x%10+'0');
	}
}

using namespace Newstd;

using namespace std;

const int ma=5e5+5;

int a[ma],fa[ma],val[ma],num[ma];
//val[i]:i 位置的值 
//num[i]:i 值对应的位置 

int n,q;

namespace DSU
{
	inline int getf(int x)
	{
		if(fa[x]==x)
		{
			return x;
		}
		
		return fa[x]=getf(fa[x]);
	}
	
	inline void merge(int x,int y)
	{
		int f1=getf(x),f2=getf(y);
		
		if(f1!=f2)
		{
			fa[f1]=f2;
		}
	}
}

int main(void)
{
	q=read();
	
	for(register int i=1;i<=q;i++)
	{
		int opt=read();
		
		if(opt==1)
		{
			int x=read();
			
			a[++n]=i,fa[i]=i,val[i]=x;
			
			if(num[x]!=0)
			{
				fa[i]=num[x];
			}
			
			else
			{
				num[x]=i;
			}
		}
		
		else
		{
			int x=read(),y=read();
			
			if(x!=y && num[x]!=0)
			{
				if(num[y]==0)
				{
					num[y]=num[x];
					
					val[num[y]]=y;
					
					num[x]=0;
				}
				
				else
				{
					DSU::merge(num[x],num[y]);
					
					num[x]=0,fa[i]=i;
				}
			}
		}
	}
	
	for(register int i=1;i<=n;i++)
	{
		printf("%d ",val[DSU::getf(a[i])]);
	}
	
	enter();
	
	return 0;
} 
```

---

## 作者：lsroi (赞：0)

**前言：** 这篇题解是对官方题解第二种方法的一个优化？

官方题解的第二种方法是一个顺序处理的过程，将每个数字的所有位置存储在数组中。然后，对于每一个操作2，将x数组中的所有元素转移到y中即可。

**重点：** 转移的方法决定了时间复杂度。

①憨憨做法：暴力转移，显然时间复杂度可卡到O(q^2)

②官方题解：按秩合并，时间复杂度O(qlogq)

③我的方法：利用链表，O(1)合并，总时间复杂度O(q)

**代码如下：**

```cpp
//by_lsroi
#include<iostream>
using namespace std;
const int maxq=5e5+1;
struct Node{
	int num;
	Node *next;
};
Node *head[maxq],*tail[maxq],*p;
int ans[maxq],q,len=0;
int main(){
	ios::sync_with_stdio(false);
	cin>>q;
	for(int i=1;i<maxq;i++)head[i]=tail[i]=nullptr;
	while(q--){
		int opt,x,y;
		cin>>opt;
		if(opt==1){
			cin>>x;
			p=new Node;
			p->num=len++;
			p->next=nullptr;
			if(tail[x]==nullptr)head[x]=tail[x]=p;
			else tail[x]->next=p,tail[x]=p;
		}
		else {
			cin>>x>>y;
			if(x==y||tail[x]==nullptr)continue;
			if(tail[y]==nullptr){head[y]=head[x];tail[y]=tail[x];}
			else {tail[y]->next=head[x];tail[y]=tail[x];}
			head[x]=tail[x]=nullptr;
		}
	}
	for(int i=1;i<maxq;i++){
		while(head[i]!=nullptr){
			ans[head[i]->num]=i;
			head[i]=head[i]->next;
		}
	}
	for(int i=0;i<len;i++)cout<<ans[i]<<" ";cout<<endl;
	return 0;
}
```


---

