# Two Teams

## 题目描述

There are $ n $ students standing in a row. Two coaches are forming two teams — the first coach chooses the first team and the second coach chooses the second team.

The $ i $ -th student has integer programming skill $ a_i $ . All programming skills are distinct and between $ 1 $ and $ n $ , inclusive.

Firstly, the first coach will choose the student with maximum programming skill among all students not taken into any team, and $ k $ closest students to the left of him and $ k $ closest students to the right of him (if there are less than $ k $ students to the left or to the right, all of them will be chosen). All students that are chosen leave the row and join the first team. Secondly, the second coach will make the same move (but all students chosen by him join the second team). Then again the first coach will make such move, and so on. This repeats until the row becomes empty (i. e. the process ends when each student becomes to some team).

Your problem is to determine which students will be taken into the first team and which students will be taken into the second team.

## 说明/提示

In the first example the first coach chooses the student on a position $ 3 $ , and the row becomes empty (all students join the first team).

In the second example the first coach chooses the student on position $ 4 $ , and the row becomes $ [2, 1] $ (students with programming skills $ [3, 4, 5] $ join the first team). Then the second coach chooses the student on position $ 1 $ , and the row becomes empty (and students with programming skills $ [1, 2] $ join the second team).

In the third example the first coach chooses the student on position $ 1 $ , and the row becomes $ [1, 3, 5, 4, 6] $ (students with programming skills $ [2, 7] $ join the first team). Then the second coach chooses the student on position $ 5 $ , and the row becomes $ [1, 3, 5] $ (students with programming skills $ [4, 6] $ join the second team). Then the first coach chooses the student on position $ 3 $ , and the row becomes $ [1] $ (students with programming skills $ [3, 5] $ join the first team). And then the second coach chooses the remaining student (and the student with programming skill $ 1 $ joins the second team).

In the fourth example the first coach chooses the student on position $ 3 $ , and the row becomes $ [2, 1] $ (students with programming skills $ [3, 4, 5] $ join the first team). Then the second coach chooses the student on position $ 1 $ , and the row becomes empty (and students with programming skills $ [1, 2] $ join the second team).

## 样例 #1

### 输入

```
5 2
2 4 5 3 1
```

### 输出

```
11111
```

## 样例 #2

### 输入

```
5 1
2 1 3 5 4
```

### 输出

```
22111
```

## 样例 #3

### 输入

```
7 1
7 2 1 3 5 4 6
```

### 输出

```
1121122
```

## 样例 #4

### 输入

```
5 1
2 4 5 3 1
```

### 输出

```
21112
```

# 题解

## 作者：SSerxhs (赞：10)

一道水题，复杂度可以做到$O(n)$，并没有那个$log$

直接模拟题意，每次找到最大值，向两边拓展即可。使用双向链表来维护左右关系，而最大值可以直接从大向小暴力扫，由于原数列是个排列，所以复杂度可以由势能分析得到是均摊$O(n)$

```cpp
#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;
const int N=2e5+2;
int nxt[N],pre[N],dy[N];
char ans[N];
int q,n,m,i,j,k,c,t=50;
inline void read(int &x)
{
	c=getchar();
	while ((c<48)||(c>57)) c=getchar();
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
}
int main()
{
	read(n);read(m);q=n;
	for (i=1;i<=n;i++)
	{
		read(j);dy[j]=i;
		pre[i]=i-1;nxt[i]=i+1;
	}
	nxt[n]=0;
	while (n)
	{
		t^=3;
		while (ans[dy[n]]) --n;
		if (!n) break;ans[dy[n]]=t;
		j=pre[dy[n]];k=nxt[dy[n]];
		for (i=1;(j)&&(i<=m);i++)
		{
			ans[j]=t;
			j=pre[j];
		}
		for (i=1;(k)&&(i<=m);i++)
		{
			ans[k]=t;
			k=nxt[k];
		}
		pre[k]=j;nxt[j]=k;
	}
	fwrite(ans+1,1,q,stdout);
}
```


---

## 作者：da32s1da (赞：5)

可删除堆，维护前驱后继

将每个人丢进一个堆中，每次取出最大值，删除$k$个后继和$k$个前驱，把删除的丢进另一个堆中。注意每次取出最大值时，若两个堆堆顶相同，删掉。

```cpp
#include<cstdio>
#include<queue>
using namespace std;
const int N=2e5+50;
typedef pair<int,int> pr;
int n,K,opt,a[N],vis[N],pre[N],net[N];
priority_queue<pr>q,p;
int main(){
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		pre[i]=i-1;net[i]=i+1;//初始化前驱后继
		q.push(pr(a[i],i));
	}net[n]=0;
	while(!q.empty()){
		while(p.size()&&q.top()==p.top())q.pop(),p.pop();int i=0,j=0,k=0;
		if(q.empty())break;//堆顶相同删除
		for(i=1,j=net[q.top().second];i<=K&&j;i++,j=net[j])vis[j]=opt+1,p.push(pr(a[j],j));//后继
		for(i=1,k=pre[q.top().second];i<=K&&k;i++,k=pre[k])vis[k]=opt+1,p.push(pr(a[k],k));//前驱
		vis[q.top().second]=opt+1;q.pop();
		pre[j]=k;net[k]=j;opt^=1;//同时维护前驱后继
	}
	for(int i=1;i<=n;i++)printf("%d",vis[i]);
}
```

---

## 作者：一扶苏一 (赞：4)

[本场题解地址](https://www.cnblogs.com/yifusuyi/p/10727303.html)

# E

## Description

有 $n$ 个人站成一排，他们每个人都有一个能力值，能力值互不相同。

有两个教练，分别是 $1$ 队教练和 $2$ 队教练。由 $1$ 队教练先挑，每次教练会将场上剩下的人中能力值最高的和他左右各 $k$ 个人从场上挑出，加入自己的队伍，然后由另一名教练再挑。

在挑选时如果一侧不足 $k$ 个人则将这些人都挑入队伍。

请求出每个人最终加入的是哪个队伍

## Limitation

$1~\leq~k~\leq~n~\leq~2~\times~10^5$

## Solution

考虑先将每个人的位置按照他们的能力值排序，然后配合一个是否被删除的标记数组就可以均摊 $O(1)$ 的去确定每个状态下能力值最高的人在哪个位置了。

考虑将自己和左右 $k$ 个人选出的操作可以使用双向链表完成。由于每个人只会被删除一次，所以总复杂度 $O(n)$。

再删除的时候可以顺手标记上这个人已经被删除了，如果求能力值最高的人时该人被删除，则查找下一个即可。

加上排序总复杂度 $O(n \log n)$

## Code

```cpp
#include <cstdio>
#include <algorithm>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif

typedef long long int ll;

namespace IPT {
  const int L = 1000000;
  char buf[L], *front=buf, *end=buf;
  char GetChar() {
    if (front == end) {
      end = buf + fread(front = buf, 1, L, stdin);
      if (front == end) return -1;
    }
    return *(front++);
  }
}

template <typename T>
inline void qr(T &x) {
  char ch = IPT::GetChar(), lst = ' ';
  while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
  while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
  if (lst == '-') x = -x;
}

namespace OPT {
  char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
  if (x < 0) {x = -x, putchar('-');}
  int top=0;
  do {OPT::buf[++top] = static_cast<char>(x % 10 + '0');} while (x /= 10);
  while (top) putchar(OPT::buf[top--]);
  if (pt) putchar(aft);
}

const int maxn = 200009;

int n, k, cot;
int MU[maxn], pos[maxn], lf[maxn], rf[maxn], ans[maxn];
bool dlt[maxn];

inline bool cmp(const int _a, const int _b) {
  return MU[_a] > MU[_b];
}

int main() {
  freopen("1.in", "r", stdin);
  qr(n); qr(k);
  for (int i = 1; i <= n; ++i) qr(MU[i]);
  for (int i = 1; i <= n; ++i) pos[i] = i;
  std::sort(pos + 1, pos + 1 + n, cmp);
  for (int i = 1; i <= n; ++i) {
    lf[i] = i - 1; rf[i] = i + 1;
  } rf[n] = 0;
  for (int i = 1; i <= n; ++i) if (!dlt[pos[i]]) {
    if (cot != 1) cot = 1;
    else cot = 2;
    int s = lf[pos[i]];
    int cnt = 0;
    while ((cnt < k) && (s)) {
      dlt[s] = true;
      ans[s] = cot;
      ++cnt;
      if (lf[s]) rf[lf[s]] = rf[s];
      if (rf[s]) lf[rf[s]] = lf[s];
      s = lf[s];
    }
    s = rf[pos[i]];
    cnt = 0;
    while ((cnt < k) && (s)) {
      dlt[s] = true;
      ans[s] = cot;
      ++cnt;
      if (lf[s]) rf[lf[s]] = rf[s];
      if (rf[s]) lf[rf[s]] = lf[s];
      s = rf[s];
    }
    s = pos[i];
    if (lf[s]) rf[lf[s]] = rf[s];
    if (rf[s]) lf[rf[s]] = lf[s];
    ans[pos[i]] = cot; dlt[pos[i]] = true;
  }
  for (int i = 1; i <= n; ++i) qw(ans[i], ' ', false);
  putchar('\n');
  return 0;
}
```

---

## 作者：WsW_ (赞：3)

还没看到用 `set` 加双向链表做的。

---
### 思路
有以下要做到的点：  
1. 查询最大值。
2. 删除已经被选择的人。
3. 向左和右分别找 $k$ 个人。  

用 `set` 维护 $1,2$，用双向链表维护 $3$。  
**注意：删除一个人，需要在 `set` 和链表中同时删除。**

由于每个数只会分别在 `set` 和链表中删除一次，所以时间复杂度为 $O(n\log n)$。

其他按要求模拟即可。

---
### 代码和[提交记录](https://www.luogu.com.cn/record/130055683)
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,n1;
int ans[200003];
int p[200003];
struct node{
	int x,nxt,lst;
}l[200003];
int now=1;
set<int>s;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>k;   n1=n;
	for(int i=1;i<=n;i++){
		cin>>l[i].x;
		l[i].nxt=i+1;  l[i].lst=i-1;
		p[l[i].x]=i;//记录数字在哪个位置，方便查询。
		s.insert(l[i].x);
	}
	while(n1){//n1记录还剩多少人
		int x=*(--s.end());
		ans[p[x]]=now;
		for(int i=l[p[x]].nxt,j=1;i<=n&&j<=k;j++,i=l[i].nxt){//向右遍历
			n1--;
			ans[i]=now;
			s.erase(l[i].x);//这三行为删除
			l[l[i].nxt].lst=l[i].lst;
			l[l[i].lst].nxt=l[i].nxt;
		}
		for(int i=l[p[x]].lst,j=1;i>0&&j<=k;j++,i=l[i].lst){//向左遍历
			n1--;
			ans[i]=now;
			s.erase(l[i].x);
			l[l[i].nxt].lst=l[i].lst;
			l[l[i].lst].nxt=l[i].nxt;
		}
		n1--;
		s.erase(x);
		l[l[p[x]].nxt].lst=l[p[x]].lst;
		l[l[p[x]].lst].nxt=l[p[x]].nxt;
		now=now%2+1;
	}
	for(int i=1;i<=n;i++)cout<<ans[i];
	return 0;
}
```

---

## 作者：YangXiaopei (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1154E)

## 前言：

不懂链表的请先自学再来看此题解或直接跳过。

## Solution：

一看到题，就有一个思路：模拟。

但很明显，不管怎样，时间复杂度都为 $O(n^2)$，无法通过。

我们再来看，每个人只会出一次队，那我们只需再 $O(1)$ 中找到能力最高的人即可，这里可用优先队列模拟，但我这要介绍一种更巧妙的方法。

由于有出队这种操作，我们先想到用链表。

再加上每个人的能力值为 $1$ 到 $n$ 的排列，我们只需把能力值存入链表，用一个标记数组判断是否出过队，再用 `while` 循环是否为空，每次循环 $n$ 到 $1$，找到第一个没出队的能力值，再分别左遍历 $k$，右遍历 $k$，每次打上标记并把它从链表里删除即可。

最终代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, k, cnt, pre, l[200010], r[200005], a[200005], f[200005], y[200005], z[200005];
//l、r存链表，f为标记数组，y存下标，z存最终输出。
void link(int x, int y){加入链表操作
	r[x] = y;
	l[y] = x;
	return;
}
void del(int x){删除操作
	link(l[x], r[x]);
	f[x] = 1;
	z[y[x]] = pre;
	return;
}
int HEAD = 0;
int END = 200001;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	int last = 0;
	for(int i = 1; i <= n; i++){//把下标存入链表。
		cin >> a[i];
		link(last, a[i]);
		last = a[i];
		y[a[i]] = i;
	}
	link(a[n], END);
	pre = 1;//用来记录该加入那个队了。
	while(cnt < n){
		for(int i = n; i >= 1; i--){
			if(f[i] == 0){//找到第一个没出队的。
				f[i] = 1;
				for(int j = r[i], m = 1; j != END && m <= k; j = r[j], m++){//右找k个。
					cnt++;
					del(j);
				}
				for(int j = l[i], m = 1; j != HEAD && m <= k; j = l[i], m++){//左找k个。
					cnt++;
					del(j);
				}
				del(i);
				cnt++;
				break;
			}
		}
		pre++;//当前队伍变换。
	}
	for(int i = 1; i <= n; i++){//最终输出
		z[i] %= 2;
		if(z[i] == 0){
			z[i] = 2;
		}
		cout << z[i];
	}
	return 0;
}

```

完结撒花

---

## 作者：Nuyoah_awa (赞：3)

### 题目分析
首先想到暴力，找到一个能力最大的人，将他左边 $k$ 个没被选的和右边 $k$ 个没被选的将其归队。

总的时间效率是 $O(n ^ 2)$ 的。

考虑到每回在找旁边 $k$ 个人时有很多是已经被选过的，所以可以使用双向链表，将所有被选过的从链表中删掉，在剩下的人里面向两边找 $k$ 个。

楼上大佬使用栈实现 $O(1)$ 查找最大，我使用的是下标排序法：一个数组，$a_i$ 表示第 $i$ 大的数的下标（如下 `node2`），顺序遍历。

由于每个点都只被归一次队，所以最终的时间复杂度是 $O(n)$的。

### code
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
struct node1{
	int val, ans, left, right;
}p[1000000];
struct node2{
	int val, ans, pos;
}q[1000000];
bool cmp(node2 x, node2 y)
{
	return x.val > y.val;
}
int main(int argc, char** argv)
{
	int n, k, i, j, s = 1;
	scanf("%d %d", &n, &k);
	p[0].left = n;
	p[0].right = 1;
	for(i = 1;i <= n;i++)
	{
		scanf("%d", &p[i].val);
		q[i].val = p[i].val;
		q[i].pos = i;
		p[i].ans = 0;
		p[i].left = i - 1;
		p[i].right = i + 1;
	}
	p[n].right = n + 1;
	sort(q + 1, q + n + 1, cmp);
	for(i = 1;i <= n;i++)
	{
		if(p[q[i].pos].ans != 0)
			continue;
		p[q[i].pos].ans = s;
		int now = q[i].pos;
		for(j = 1;j <= k;j++)
		{
			now = p[now].right;
			if(now == n + 1)
				break;
			p[now].ans = s;
			p[p[now].left].right = p[now].right;
			p[p[now].right].left = p[now].left;
		}
		now = q[i].pos;
		for(j = 1;j <= k;j++)
		{
			now = p[now].left;
			if(now == 0)
				break;
			p[now].ans = s;
			p[p[now].left].right = p[now].right;
			p[p[now].right].left = p[now].left;
		}
		now = q[i].pos;
		p[p[now].left].right = p[now].right;
		p[p[now].right].left = p[now].left;
		s = 3 - s;
	}
	for(i = 1;i <= n;i++)
		cout << p[i].ans;
	return 0;
}
```

---

## 作者：卷王 (赞：3)

## 题目大意

[传送门](https://www.luogu.com.cn/problem/CF1154E)

## 思路

$O(n^2)$ 的暴力模拟不用说。

我们得想办法优化这一模拟过程。

于是，我想到了优先队列。

开两个优先队列，一个记录现在队里面的人，一个记录被挑选出来的人。这个人要有两个参数，一个是能力值，一个是编号。我们可以用结构体轻松解决。

然后开个双向链表（其实可以用数组维护），维护每个数的前驱后继，在模拟过程中直接运用就行了。

模拟过程如下：

```cpp
n = read(), k = read();
	for(int i = 1; i <= n; i++) {
		a[i] = read();
		lst[i] = i - 1; nxt[i] = i + 1;
		x.push((node){a[i], i});
	} int turn = 1;
	nxt[n] = 0, lst[1] = 0;
	while(!x.empty()) {
		while(!y.empty() && y.top().value == x.top().value)x.pop(), y.pop();
		if(x.empty()) break;
		node u = x.top(); x.pop();
		int pre = nxt[u.num], suc = lst[u.num];
		ans[u.num] = turn;
		for(int i = 1; i <= k && pre; i++) {
			ans[pre] = turn;
			y.push((node){a[pre], pre});
			pre = nxt[pre];
		}
		for(int i = 1; i <= k && suc; i++) {
			ans[suc] = turn;
			y.push((node){a[suc], suc});
			suc = lst[suc];
		}
		nxt[suc] = pre, lst[pre] = suc;
		if(turn == 1) turn = 2;
		else turn = 1;
	}
	for(int i = 1; i <= n; i++)
		printf("%d", ans[i]);
```

希望我的题解对大家有帮助。

---

## 作者：ztntonny (赞：1)

## 思路

从队列中拿出人，第一眼链表加模拟。

1. 写一个链表，每一个元素包含这个人的能力值、这个人前面的人是谁以及后面是谁，以及一个表示该人还是否在队列中的布尔。
2. 打一个结构体数组，每一个元素包含这个人的能力值、这个人初始的位置，排序后找到能力值排名以及对应的人。
3. 从大到小遍历能力值，每一次判断该能力值所对应人是否还在队列中，如果是，则用链表向两边延伸，左右各 $k$ 个都标记在输出数组中、状态变为不在队列中。在都遍历完后，将向右向左的第 $k+1$ 个的两个人连接在一起。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

struct T
{
	ll bef , aft , ability;
	bool state;
}t[1000005];

struct A
{
	ll abi , pos;
}a[1000005];

bool cmp( A x , A y )
{
	return x.abi > y.abi;
}

ll k , n , st[1000005] , srt;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL) , cout.tie(NULL);
	cin >> n >> k;
	for ( int i = 0; i < 1000005; i++ )	t[i].bef = i - 1 , t[i].aft = i + 1 , t[i].state = false;
	for ( int i = 1; i <= n; i++ )	cin >> t[i].ability , t[i].state = true , a[i].abi = t[i].ability , a[i].pos = i;
	sort( a + 1 , a + n + 1 , cmp );
	for ( int i = 1; i <= n; i++ )
	{
		if ( t[a[i].pos].state )
		{
			if ( srt == 1 )	srt = 2;
			else	srt = 1;
			st[a[i].pos] = srt;
			ll p = t[a[i].pos].bef;
			for ( int i = 1; i <= k && p >= 1; i++ )	st[p] = srt , t[p].state = false , p = t[p].bef;
			ll l = p;
			p = t[a[i].pos].aft;
			for ( int i = 1; i <= k && p <= n; i++ )	st[p] = srt , t[p].state = false , p = t[p].aft;
			ll r = p;
			t[l].aft = r , t[r].bef = l;
		}
	}
	for ( int i = 1; i <= n; i++ )	cout << st[i];
	return 0;
}
```

---

## 作者：TammyZhao (赞：1)

# 题解

- 这题就是个双向链表模板，没有什么难点（但这题也不至于评黄吧，至少比 F 难）。

- 排序，但注意保留原数组，排序数组记录原数和其位置。从大到小找到第一个没有被选过的数，在原数组中找到这个数，两边跳 $k$ 次，注意这是每个数的左右并不是原数组的左右，而是左右没被选过的数，这用数组来记录就行了，最后在更新一下每个数左右端点。

- 由于每个数最多找一遍，所以时间复杂度大概是 $O(n)$。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

struct node
{
	int l, r, num;
}a[200005];

struct node2
{
	int num, idx;
}b[200005];

int n, k, top = 1, ans[200005], cnt = 1;
bool vis[200005];

bool cmp(node2 x, node2 y)
{
	return x.num > y.num;
}

int main()
{
	cin >> n >> k;
	for (int i = 1 ; i <= n ; i ++)
	{
		cin >> a[i].num;
		a[i].l = i - 1;
		a[i].r = i + 1;
		b[i].idx = i;
		b[i].num = a[i].num;
	}
	sort(b + 1, b + 1 + n, cmp);
	while (top <= n)
	{
		while (vis[b[top].idx])
		{
			top ++;
		}
		int s = b[top].idx;
		int L = a[s].l, R = a[s].r;
		vis[s] = 1;
		ans[s] = (cnt % 2 == 0 ? 2 : 1);
		for (int i = 1 ; i <= k && L > 0 ; i ++)
		{
			ans[L] = (cnt % 2 == 0 ? 2 : 1);
			vis[L] = 1;
			L = a[L].l;
		}
		for (int i = 1 ; i <= k && R <= n ; i ++)
		{
			ans[R] = (cnt % 2 == 0 ? 2 : 1);
			vis[R] = 1;
			R = a[R].r;
		}
		a[L].r = R;
		a[R].l = L;
		cnt ++;
	}
	for (int i = 1 ; i <= n ; i ++)
	{
		cout << ans[i];
	}
	return 0;
}
```


---

## 作者：JohnJoeZhu (赞：1)

（今天又水了几道orange）
### 正题：[CF1154E](https://www.luogu.org/problemnew/show/CF1154E)
（事实上，这是一道没有紫色的紫色）
###### 题意：
有 n 个人站成一排，他们每个人都有一个能力值，能力值**互不相同**。

有两个教练，分别是 1 队教练和 2 队教练。

由 **1** 队教练先挑，每次教练会将场上剩下的人中能力值最高的和他左右各 k 个人从场上挑出，加入自己的队伍，然后由另一名教练再挑。

在挑选时如果一侧不足 k 个人则将这些人都挑入队伍。

请求出每个人最终加入的是哪个队伍
##### 解法
我们可以很容易想到**双向链表+模拟**

双向链表：处理每个人的左右k个人

模拟：将每个人所属的队伍标记

在寻找剩余最大值时，这里采用了排序的方法（也可以用优先队列）

跳过已经别挑选的人，剩下的就是中点了
### 代码与注意事项
一个在本人打代码时的**错误**

特判$ k*2+1==n $ 的情况，事实上没有必要，甚至出错

（这里只是提出，方便学习）
```cpp
#include<cstdio>
#include<algorithm>
using namespace std; 
struct pp{
    int l,r,t;
}a[200010];
struct pa{
    int t,num;
}b[200010];
int n,k,ans[200010];
bool vis[200010];
bool cmp(pa a1,pa a2)
{
    return a1.t>a2.t;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i].t);
        a[i].l=i-1;
        a[i].r=i+1;
        b[i].num=i;//分别储存（采用结构体）
        b[i].t=a[i].t;
    }
    sort(b+1,b+1+n,cmp);//高度要排序
    int top=1,x=1;
    while(top<=n)//要等于，等于，等于！！！（不然在剩下1个的时候就没人选了）
    {
        while(vis[b[top].num]) top++;//跳过挑选过的人
        int g=b[top].num;
        int ll=a[g].l,rr=a[g].r;
        ans[g]=(x%2==0?2:1);
        vis[g]=1;//打标记
        for(int i=1;i<=k&&ll!=0;i++)//向左
        {
            ans[ll]=(x%2==0?2:1);
            vis[ll]=1;
            ll=a[ll].l;
        }
        for(int i=1;i<=k&&rr!=n+1;i++)//向右
        {
            ans[rr]=(x%2==0?2:1);
            vis[rr]=1;
            rr=a[rr].r;
        }
        a[rr].l=ll;
        a[ll].r=rr;
        x++;//计数（决定哪一个教练选）
    }
    for(int i=1;i<=n;i++) printf("%d",ans[i]);
    return 0;
 } 
```
——————————————————————————————————————2019.7.3

---

## 作者：wasa855 (赞：1)

#### Heap + 双向链表   
用双向链表维护未被选走的队员的左右关系，用堆维护目前的最大值。   
具体的操作见代码
``` cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005];
int l[200005];
int r[200005];
bool used[200005];
int t[200005];
priority_queue<int> q;
int ans[200005];
int main()
{
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        l[i]=i-1;
        r[i]=i+1;
        t[a[i]]=i;
        q.push(a[i]);
    }
    l[1]=0;
    r[n]=0;
    int res=1;
    while(!q.empty())
    {
        int x=q.top();
        q.pop();
        int pl=t[x];
        if(ans[pl]!=0)
        {
            continue;
        }
        int i=k;
        int left=pl;
        ans[pl]=res;
        while(i--)
        {
            left=l[left];
            if(left==0)
            {
                break;
            }
            ans[left]=res;
        }
        i=k;
        int right=pl;
        while(i--)
        {
            right=r[right];
            if(right==0)
            {
                break;
            }
            ans[right]=res;
        }
        int ll=l[left];
        int rr=r[right];
        if(ll!=0)
        {
            r[ll]=rr;
        }
        if(rr!=0)
        {
            l[rr]=ll;
        }
        if(res==1)
        {
            res=2;
        }
        else
        {
            res=1;
        }
    }
    for(int i=1;i<=n;i++)
    {
        printf("%d",ans[i]);
    }
    return 0;
}
```

---

## 作者：acup (赞：0)

双向链表+优先队列,
写一个把所有量都入结构体中的写法
```cpp
#include<bits/stdc++.h>
#define For(i,l,r) for(int i=(l);i<=(r);i++)
#define ReFor(i,l,r) for(int i=(l);i>=(r);i--)
#define INF 0x7fffffff
#define lowbit(x) (x)&-(x)
#define ll long long
#define N 200010
using namespace std;
int n,k;
struct nod{
	int id,v,t,l,r;//id编号，v战斗力，t队伍编号，l前一个，r后一个 
}s[N];
bool operator < (const nod &a, const nod &b){
	return a.v<b.v;
} 
priority_queue<nod> q;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0' && ch<='9'){x=x*10+ch-'0'; ch=getchar();}
	return f*x;
}
int main(){
	n=read(); k=read();
	For(i,1,n){
		s[i].id=i;
		s[i].v=read();
		s[i].t=0;//未选 
		s[i].l=i-1;
		s[i].r=i+1;
		q.push(s[i]);
	}
	s[n].r=0;
	int h=1;
	while(q.size()){
		while(!q.empty() && s[q.top().id].t!=0) q.pop();
		if(q.empty()) break;
		nod x=q.top();
		s[x.id].t=h;//当前当战斗力最强的归入队伍 
		int cnt=0,i,j;
		for(i=s[x.id].l;i && cnt<k;i=s[i].l){
			cnt++;
			s[i].t=h;
		}
		cnt=0;
		for(j=s[x.id].r;j && cnt<k;j=s[j].r){
			cnt++;
			s[j].t=h;
		}
		s[i].r=j;
		s[j].l=i;
		h=h^3;//1 2 1 2 1 2...
	}
	For(i,1,n)
		printf("%d",s[i].t);
	printf("\n");
    return 0;
}

```


---

