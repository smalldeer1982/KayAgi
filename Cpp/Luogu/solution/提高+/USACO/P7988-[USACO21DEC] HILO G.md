# [USACO21DEC] HILO G

## 题目描述

Bessie 有一个数 $x+0.5$，其中 $x$ 是某个 $0$ 到 $N$ 之间的整数（$1\le N\le 2 \cdot 10^5$）。  

Elsie 正试着猜这个数。她可以以如下形式对于某个 $1$ 到 $N$ 之间的整数提问：「$i$ 是大了还是小了？」如果 $i$ 大于 $x+0.5$，Bessie 会回答 "HI"，如果 $i$ 小于 $x+0.5$ 则回答 "LO"。

Elsie 想到了以下猜测 Bessie 的数的策略。在进行任何猜测之前，她创建了一个包含 $N$ 个整数的序列，其中从 $1$ 到 $N$ 的每个数均恰好出现一次（换句话说，这个序列是长为 $N$ 的一个排列）。然后她遍历这一列表，按列表中的数的顺序依次猜数。

然而，Elsie 会跳过所有不必要的猜测。也就是说，如果 Elsie 将要猜某个数 $i$，而 Elsie 之前已经猜过了某个 $j < i$ 并且 Bessie 回答 "HI"，Elsie 不会再猜 $i$，而是继续猜序列中的下一个数。类似地，如果她将要猜某个数 $i$，而她之前已经猜过了某个 $j > i$ 并且 Bessie 回答 "LO"，Elsie 不会再猜 $i$，而是继续猜序列中的下一个数。可以证明，使用这一策略，对于 Elsie 创建的任意序列，她都可以唯一确定 $x$。

如果我们将所有 Bessie 回答的 "HI" 或 "LO" 拼接成一个字符串 $S$，那么 Bessie 说 "HILO" 的次数为 $S$ 等于 "HILO" 的长为 $4$ 的子串数量。

Bessie 知道 Elsie 将要使用这一策略；此外，她还知道 Elsie 将要使用的排列。然而， Bessie 尚未决定选用哪个值 $x$。

帮助 Bessie 对于每个值 $x$ 求出她会说 "HILO" 的次数。


## 说明/提示

【样例解释】

对于 $x=0$，Bessie 会说 "HIHI"，总计零次 "HILO"。

对于 $x=2$，Bessie 会说 "HILOLOHIHI"，总计一次 "HILO"。

对于 $x=3$，Bessie 会说 "HILOLOHILO"，总计两次 "HILO"。

【数据范围】

- 测试点 1-4 满足 $N \leq 5000$。
- 测试点 5-8 为均匀随机的排列。
- 测试点 9-20 没有额外限制。

## 样例 #1

### 输入

```
5
5 1 2 4 3```

### 输出

```
0
1
1
2
1
0```

# 题解

## 作者：cmll02 (赞：12)

考虑笛卡尔树。

以下标为堆的权值，值为 BST 的权值，建出笛卡尔树。

样例图片：

![](https://cdn.luogu.com.cn/upload/image_hosting/q48rwaqj.png)

容易发现，在一个点如果得到 HI 的结果下一个询问一定在左孩子，否则在右孩子。

直接在笛卡尔树上算根到每个点的路径上有多少个 HILO 就行了。

---

## 作者：houzhiyuan (赞：10)

[更垃圾的阅读体验](https://hydro.ac/d/houzhiyuan/p/P12202/solution)

考虑顺序询问下去，考虑一个询问会对那些答案造成影响。

在第 $a_i$ 之前，已经有 $i-1$ 次询问，容易发现只有在前面 $i-1$ 次询问中小于 $a_i$ 的最大值到大于 $a_i$ 的最小值这段区间会造成影响。

并且一次询问会将这个区间分成两半。

因此直接用 set 维护区间，每个区间记一个四元组 $(l,r,las,s)$，分别表示左右断电，上次询问的回答以及答案就好了。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
struct hzy{int l,r,ff,s;};
int n,a[N];
bool operator<(hzy a,hzy b){return a.l<b.l;}
bool operator>(hzy a,hzy b){return a.l>b.l;}
multiset<hzy> se;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	se.insert((hzy){0,n+1,2,0});
	for(int i=1;i<=n;i++){
		auto it=se.upper_bound((hzy){a[i],a[i],0,0});
		it--;
		if((it->ff)==1)se.insert((hzy){a[i],it->r,0,(it->s)+1});
		else se.insert((hzy){a[i],it->r,0,it->s});
		se.insert((hzy){it->l,a[i],1,it->s});
		se.erase(it);
	}
	for(auto it:se)printf("%d\n",(it.s));
}
```

---

## 作者：DYYqwq (赞：3)

看到这种题直接就想到笛卡尔树！不就是一个询问能把一个区间分成两段吗，这当然和笛卡尔树的实现是一样的！

但是我忘了咋写了啊，怎么办呢？

我们考虑巧妙的使用一个 `set` 维护。

`set` 自然可以代表我们笛卡尔树上的一个区间。里面存储左右端点、自己头上的边是 `Hi` 还是 `Lo` 以及答案。

考虑一个询问对一个区间答案的影响。

首先我们要知道这样的笛卡尔树长成什么样子。

![](https://cdn.luogu.com.cn/upload/image_hosting/yjczz4o5.png)

好就大概是这样的。

如图中所画的那样，如果父亲区间上面的边是 `Hi` 的话，自然我们的右儿子区间就可以加上贡献了。

现在还有最后一个问题：如何找到这东西的父亲区间？于是自然想到 `upper_bound`。然后就轻松愉快的找到啦！

有一个细节需要注意一下：初始别忘了把整段区间打入 `set` 中，要不然你算啥呢。根节点头上肯定没有边，所以边的那个参数随便传即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int l , r , flag , ans;
	bool operator < (const node &qwq) const
	{
		return l < qwq.l;
	}
	bool operator > (const node &qwq) const
	{
		return l > qwq.l;
	}
};
int n,  a[200010];
set<node> s;
int main()
{
	scanf("%d" , &n);
	for(int i = 1 ; i <= n ; i ++) scanf("%d" , &a[i]);
	s.insert({0 , n + 1 , 114514 , 0});
	for(int i = 1 ; i <= n ; i ++)
	{
		auto it = s.upper_bound({a[i] , a[i] , 0 , 0});
		it --;
		node qwq = *it;
		s.erase(it);
		if(qwq.flag == 1) s.insert({a[i] , qwq.r , 0 , qwq.ans + 1});
		else s.insert({a[i] , qwq.r , 0 , qwq.ans});
		s.insert({qwq.l , a[i] , 1 , qwq.ans});
	}
	for(auto it : s) printf("%d\n" , it.ans);
	return 0;
}
```

---

## 作者：UnyieldingTrilobite (赞：3)

这题本身是个不错的题，做法多种多样（至少我已知两种），那么这里就介绍一种我考场上的做法好了，比较屑，但不失为一种思路。

首先，我们试图暴力，对于每一个 $x$ 都把所有回答的结果求出来，那么就显然可以统计了。显然，这个做法是低效的。

然后我们看看能不能优化它。直观的想法就是换种枚举 $x$ 的方式：枚举每一个问题的答案然后把字符串拼出来，同时也就可以把对应的 $x$ 求出来了。由于无效询问的存在，使用深度优先搜索的方式（维护当前 $x$ 的可能取值区间）。这样做的好处是，搜索的过程中可以顺便高效地维护答案。

然后考虑这个搜索的过程，它实际上构成了一棵树的结构。不难发现，如果每一次询问都是有效的，那么每个非叶子结点的度数都至少为 $2$，那么整棵树节点数与叶子节点数同阶，换句话说，复杂度就能够得以保障。于是我们现在的问题转化成了如何高效地查找下一个有效询问。进一步转换，一个排列，每次给定一个区间和一个后缀，查询后缀中值在此区间内的数的最小下标。不难想到使用可持久化线段树解决，复杂度一只 $\log$。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5 + 9;
int n, p[N];
int rt[N], tot;
struct node {
  int mn;
  int l, r;
} tr[N << 5];
void update(int& pos, int ppos, int val, int k, int L, int R) {
  if (!pos) pos = ++tot;
  tr[pos].mn = val;
  if (L == R) return;
  int mid = (L + R) >> 1;
  if (k <= mid)
    tr[pos].r = tr[ppos].r, update(tr[pos].l, tr[ppos].l, val, k, L, mid);
  else
    tr[pos].l = tr[ppos].l, update(tr[pos].r, tr[ppos].r, val, k, mid + 1, R);
}
int query(int pos, int l, int r, int L, int R) {
  if (!pos || L > r || R < l) return n + 1;
  if (L >= l && R <= r) return tr[pos].mn;
  int mid = (L + R) >> 1;
  return min(query(tr[pos].l, l, r, L, mid),
             query(tr[pos].r, l, r, mid + 1, R));
}
int getnxt(int x, int l, int r) { return query(rt[x + 1], l, r, 0, n + 1); }
bool bl[N];
int stot;
int ans[N], nans;
void dfs(int x, int l, int r) {
  if (x == n + 1)
    ans[l] = nans;
  else {
    bl[++stot] = true;
    dfs(getnxt(x, l, p[x] - 1), l, p[x] - 1);
    if (bl[stot - 1]) ++nans;
    bl[stot] = false;
    dfs(getnxt(x, p[x], r), p[x], r);
    if (bl[--stot]) --nans;
  }
}
signed main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> p[i];
  for (int i = n; i; --i) update(rt[i], rt[i + 1], i, p[i], 0, n + 1);
  dfs(1, 0, n + 1);
  for (int i = 0; i <= n; ++i) cout << ans[i] << '\n';
  return cout << flush, 0;
}
```

---

## 作者：XGTD (赞：2)

# P7988 HILO 题解
~~我太菜~~不知道笛卡尔树，想出一种 $O(n \log n)$ 的做法。其实最后代码非常简单，但有些难想。
## Problem Statement
[题目](https://www.luogu.com.cn/problem/P7988)介绍的比较清楚了。
## Solution
~~水平不够改了好几次思路。~~

首先发现 $n$ 方做法很多，这里就不介绍了，而想要达到 $n \log n$ 或者线性肯定不能对每个 $X$ 单独做，而是需要考虑每一个数对哪些 $X$ 做贡献。考虑每个数会作为哪些 $X$ 的 HILO 中的 HI。 发现不好想因为第一，不好找谁是它的 LO 而且找到后还需要判断是否他们两个之间所有其它数都跳过了。

考虑倒过来，每一个数 $i$ 是哪些 $X$ 的 LO。 发现这下它的 HI 就很好找了，一定是他之前所有比它大的数中最小的。因为考虑若有其他数 $j$ 和 $i$ 形成 HILO 且不是比 $i$ 大的中最小的，也就是说有 $k$，使得 $a[j] > a[k] > a[i]$。若 $j < k < i$ 自然 $k$ 不可能被跳过，不行。而若 $k < j < i$，到 $k$ 以后一定会跳掉要么所有大于 $a[k]$ 的要么所有小于 $a[k]$ 的，也就是说 $i$ 和 $j$ 一定有一个被跳。

现在我们知道每一个数只能和谁形成 HILO 了，还要判断到底能不能形成。 

令回答 HI 的数为 $x$，LO 为 $y$。首先发现有两种情况导致形成不了，要么前面有个数夹在他们两个的大小之间，要么他们两个之间有数跳不掉。首先第一种不可能发生，因为 $x$ 已经是第一个比 $y$ 大的了。而第二种情况只会在有数出现在 $a[x]$ 和前面比 $y$ 小的中最大的（称其为 $z$） 之间时才会出现，因为发现其他数要么在过 $a[x]$ 是被“滤”掉了，要么被 $a[z]$ 滤掉了。而我们已经知道 $a[y]$ 和 $a[x]$ 之间没数，而 $a[y]$ 和 $a[z]$ 之间没数，所以只要 $z$ 不在 $x$ 和 $y$ 之间就行了。

所以说了怎么多最后发现只要找到对于每一个数，在他之前比它小的中最大的，和比它大的中最小的在哪里就行了。一个 `set`就搞定了。~~我一开始思路想错了还用单调栈和 st 表来着。~~

最后在用一个前缀和统计每个 $X$ 的答案，对于每一对 $a[x]$ 和 $a[y]$ 显然所有 $a[x] > X \geq a[y]$ 都可行。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, a[200005], fb[200005], fs[200005], pos[200005];
//first one before i that's bigger/smaller then i
int dif[200005], f[200005][25], g[200005][25];
//the difference array of the prefix sum difference
signed main(){
	std::ios::sync_with_stdio(0);
	cin>>n;
	for(int i = 1; i <= n; i++){
		cin>>a[i];
		pos[a[i]] = i;
		f[i][0] = a[i];
		g[i][0] = a[i];
	}
	/*
	我一开始居然还用了st表 
	for(int j = 1; j <= log2(n); j++){
		int p = 1 << (j - 1);
		for(int i = 1; i <= n - (1 << j) + 1; i++){
			f[i][j] = max(f[i][j - 1], f[i + p][j - 1]);
			g[i][j] = min(g[i][j - 1], g[i + p][j - 1]);
		} 
	}
	//st table
	*/
	set<int> tmps;
	//temperary set
	tmps.insert(a[1]);
	fs[1] = 0;
	fb[1] = INT_MAX;
	for(int i = 2; i <= n; i++){
		auto it = tmps.upper_bound(a[i]);
		//first bigger
		if(it == tmps.end()){
			//none are bigger
			fb[i] = INT_MAX;
		}else fb[i] = *it;
		if(it == tmps.begin()){
			//smallest yet
			fs[i] = 0;
		}else{
			it--;
			fs[i] = *it;			
		}
		tmps.insert(a[i]);
	}
	for(int i = 2; i <= n; i++){
		if(fb[i] == INT_MAX)continue;
		int j = pos[fb[i]];
		if(j == i - 1){
			dif[a[i]]++;
			dif[fb[i]]--;
			continue;		
		}
		if(pos[fs[i]] > pos[fb[i]]){//mibt < fb[i] && mabt >= fs[i]){
			continue;
		}
		dif[a[i]]++;
		dif[fb[i]]--;
	}
	for(int i = 0; i <= n; i++){
		if(i != 0)dif[i] += dif[i - 1];
		cout<<dif[i]<<endl;
	}
	return 0;
}
```
## Result
[Result](https://www.luogu.com.cn/record/196173977)
感觉最后代码的难度最多黄题，思路~~要是没像我一样一开始脑子进水~~好像也没有蓝题的水平。

---

## 作者：Helenty (赞：2)

### 思路
所有数一起考虑，考虑到序列里的每个询问 $a_i$ 只有当数字所在的区间包含 $a_i$ 时才会询问，然后 $a_i$ 会把一个区间成两个。

那么先考虑 ``HI``，假设第 $i$ 个询问是 ``HI``，那么首先肯定有 $x < a_i$，然后有 $x > a_j$（$j \in [1, i-1], a_j \leq a_i$）也就是还要在 $a_i$ 目前在的区间内。

之后考虑这个 ``HI`` 的下一个能否是 ``LO``，首先它的下一个被询问的位置肯定是在 $\left[ \max\{a_j\}, a_i \right]$ 这个范围内的 $a_k$。然后我们要的 $x$ 就在 $[a_k, a_i]$ 范围内。

所以用 set 求出每个 $a_i$ 对应的 $\max\{a_j\}$，然后反过来用线段树维护 $a_k$ 就好了。

时间复杂度： $ O(n \log n)$。

### CODE

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;
const int N=2e5+10;
int n,a[N],l[N],s[N],w[N<<2];
set<int> pre;
void Change(int x,int L,int R,int pos,int val){
	w[x]=val;
	if(L==R)return;
	int mid=(L+R)>>1;
	if(pos<=mid)Change(x*2,L,mid,pos,val);
	else Change(x*2+1,mid+1,R,pos,val);
	return;
}
int Ask(int x,int L,int R,int l,int r){
	if(L==l&&R==r)return w[x];
	int mid=(L+R)>>1;
	if(r<=mid)return Ask(x*2,L,mid,l,r);
	if(l>mid)return Ask(x*2+1,mid+1,R,l,r);
	return min(Ask(x*2,L,mid,l,mid),Ask(x*2+1,mid+1,R,mid+1,r));
}
int main()
{
	scanf("%d",&n);
	pre.insert(0);pre.insert(n+1);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		l[i]=*(--pre.upper_bound(a[i]));
		pre.insert(a[i]);
	}
	for(int i=0;i<=n+1;i++)
		Change(1,0,n+1,i,n+1);
	for(int i=n;i>=1;i--){
		int k=a[Ask(1,0,n+1,l[i],a[i])];
		if(k){
			s[a[Ask(1,0,n+1,l[i],a[i])]]++;
			s[a[i]]--;
		}
		Change(1,0,n+1,a[i],i);
	}
	for(int i=1;i<=n;i++)s[i]+=s[i-1];
	for(int i=0;i<=n;i++)printf("%d\n",s[i]);
	return 0;
}

```

---

## 作者：ckain (赞：2)

场上当时不知道笛卡尔树一说想出的逆天做法．时间带多一个 $\log$，码量也比较大．

我们考虑猜数的过程，将 $i$ 看做横坐标，$a_i$ 看做纵坐标．给定 $x$ 时，$a_i$ 被猜满足 $a_i \le x$ 且 $a_i$ 的左上方没有点，或 $a_i > x$ 且 $a_i$ 的左下方没有点．$x$ 将平面分成两部分，被猜的点集是上部的一个递降序列和下部的一个递增序列．从小到大枚举 $x$，有一些上部的点到了下部来，我们维护上下两个被猜点集的变化即可．然后我们发现加入点比删除点好做很多——可以将上点集删除点的操作看作从最终状态加点的过程，模拟的过程中将操作记下即可．

```cpp
#include<bits/stdc++.h>
#define pii pair<int, int>
#define fr first
#define sc second
using namespace std;
inline int rd(void){
	int s=0, f=1; char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') f=0; c=getchar();}
	while(c>='0' && c<='9') {s=s*10+c-'0'; c=getchar();}
	return f? s:-s;
}
const int N=2e5+5;
int n, a[N], p[N];

int stk[N], tp;
vector<int> act_hi[N];
vector<int> act_lo[N];
void prework(){
	for(int i=1; i<=n; i++){
		int pos=p[i];
		while(tp && stk[tp]>pos) act_lo[i].push_back(stk[tp--]);
		stk[++tp]=pos;
	}
	tp=0;
	for(int i=n; i; i--){
		int pos=p[i];
		while(tp && stk[tp]>pos) act_hi[i].push_back(stk[tp--]);
		stk[++tp]=pos;
	}
}

int ans[N], now;
set<pii> s;

void ins(int pos, int c){
	s.insert({pos, c});
	auto ite=s.lower_bound({pos, c});
	if(ite!=s.begin()){
		ite--;
		int prec=(*ite).sc;
		if(prec==1 && c==0) now++;
		ite++, ite++;
		if(ite!=s.end()){
			if(c==1 && (*ite).sc==0) now++;
			if(prec==1 && (*ite).sc==0) now--;
		}
	}
	else if(c==1){
		++ite;
		if(ite!=s.end() && (*ite).sc==0) now++;
	}
}

void del(int pos, int c){
	auto ite=s.lower_bound({pos, c});
	if(ite!=s.begin()){
		ite--;
		int prec=(*ite).sc;
		if(prec==1 && c==0) now--;
		ite++, ite++;
		if(ite!=s.end()){
			if(c==1 && (*ite).sc==0) now--;
			if(prec==1 && (*ite).sc==0) now++;
		}
	}
	else if(c==1){
		++ite;
		if(ite!=s.end() && (*ite).sc==0) now--;
	}
	s.erase({pos, c});
}

void work(){
	ans[0]=0;
	for(int i=1; i<=tp; i++) s.insert({stk[i], 1});
	for(int i=1; i<=n; i++){
		for(int x:act_hi[i]) ins(x, 1);
		del(p[i], 1);
		for(int x:act_lo[i]) del(x, 0);
		ins(p[i], 0);
		ans[i]=now;
	}
}

signed main(){
	n=rd();
	for(int i=1; i<=n; i++){
		a[i]=rd();
		p[a[i]]=i;
	}
	prework();
	work();
	for(int i=0; i<=n; i++) printf("%d\n", ans[i]);
	return 0;
}
/*
5
3 1 4 5 2 
*/
```

---

## 作者：CrTsIr400 (赞：2)

题意：对于每个数进行猜数过程（比大小的过程形成 `HI` 或者 `LO` 的结果，而且需要剪枝，剪枝的过程题目中已讲述），求形成的结果串之内子串 `HILO` 的数量。

[提供另外一组样例数据。](https://www.luogu.com.cn/discuss/571191)

思路：观察到暴力一个个去处理 `HI` 和 `LO` 的结果，只能过数据随机那一档分数，这个算法也不好处理对于每个数的全局查询一类结果，于是考虑转化思路，把所有询问一起处理。（这是一种类似于整体二分的思想）

显然可知，在不断进行处理询问的过程之中，一些区间的答案是一样的，直到最后第 $n$ 个操作才把所有询问的答案独立。

手动模拟一下，发现每次操作实质上是分裂一个区间，然后对它们统计不同的答案。

实际上每次操作所涉及的 $a_i$ 仅仅影响到包含 $a_i$ 的这个区间的答案，使这个区间分裂成为两半（左半部分打上 `HI` 的标记而右半部分打上 `LO` 的标记，并且转移答案），这样的操作是珂朵莉树的 `split` 操作，实现时候只需要使用 `set` 维护区间集即可。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;typedef int I;
struct nd{
	mutable I l,r,frid,ans;
	friend bool operator <(nd a,nd b){
		return a.l<b.l;}};
set<nd>s;
void split(I id){
	auto it=s.upper_bound(nd{id,id,0});
	--it;auto p=*it;
	s.erase(it);
	if(p.l<=id-1)s.insert(nd{p.l,id-1,0,p.ans});
	s.insert(nd{id,p.r,1,p.ans+(p.frid^1)});
}I n;
int main(){
	scanf("%d",&n);
	s.insert(nd{0,n,1,0});
	for(I i=n,x;i;--i)scanf("%d",&x),split(x);
	for(auto i:s)printf("%d\n",i.ans);
	return 0;
}

```



---

## 作者：XL4453 (赞：2)

### 解题思路：

考虑直接把这个询问的树建立出来。

转化一下就是一个二叉排序树，但是要求询问得早的节点要在询问得节点的上方，也就是一个堆的性质。二叉排序树的性质来自于在询问得到结果之后只会向一个特定的方向走，堆的性质则是来自于询问的顺序的优先级。

然后发现这就是一个笛卡尔树，二叉树权值是题目给出的数的权值，堆的权值是题目给出的数的顺序，直接 $O(n)$ 建立笛卡尔树。

---
然后考虑什么样的情况下会说出 $\text{HILO}$，很明显的一种情况是先向左子树走，然后再向右子树走。需要注意的是，当走到一个节点的时候，如果这个节点恰好是询问的那一个，会回答 $\text{LO}$，也就是说，当向左走之后的一个节点在统计答案的时候需要加一，但是这个加一不会保留到其他子节点。

然后就直接对着这个笛卡尔树遍历一下就好了。

---
特殊地，询问 $0$ 的时候会一直 $\text{HI}$，不会出现 $\text{HILO}$，直接输出 $0$ 就好了。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=2e5+7;
struct str{
	int num,id;
	bool operator < (str x)const{
		return num<x.num;
	}
}p[MAXN];
int n,a[MAXN],stk[MAXN],ls[MAXN],rs[MAXN],ans[MAXN],tot,s;
void dfs(int now,int last){
	
	if(now==0)return;
	//1 向左 2 向右 
	if(last==1)ans[now]=tot+1;
	else ans[now]=tot;
	dfs(ls[now],1);
	
	if(last==1)tot++;
	dfs(rs[now],0);
	if(last==1)tot--;
}
int main(){
    scanf("%d",&n);
    printf("0\n");
    for(int i=1;i<=n;i++){
    	scanf("%d",&p[i].num);
    	p[i].id=i;
	}
	s=p[1].num;
    sort(p+1,p+n+1);
    for(int i=1;i<=n;i++){
    	a[i]=p[i].id;
	}
	for(int i=1,pos=0,top=0;i<=n;++i){
        pos=top;
        while(pos&&a[stk[pos]]>a[i])pos--;
        if(pos)rs[stk[pos]]=i;
        if(pos<top)ls[i]=stk[pos+1];
        stk[top=++pos]=i;
    }
    dfs(s,-1);
    
//    for(int i=1;i<=n;i++)
//    printf("%d %d\n",ls[i],rs[i]);
    
    for(int i=1;i<=n;i++)
    printf("%d\n",ans[i]);
    return 0;
}
/*
先向左再向右算一次，到节点上算一次右 
*/
```


---

## 作者：鱼跃于渊 (赞：1)

## 解法

考虑先把所有询问的树建出来。  
由于询问得到结果后只会进入固定的一个儿子结点，所以这是一颗二叉搜索树。  
由于先询问的结点会在后询问的结点上方，所以这又是一个堆。  
两者一结合，正是一颗笛卡尔树。  
于是我们以下标为堆的权值，原权值为二叉搜索树的权值建出一颗笛卡尔树。  

遍历这颗笛卡尔树。  
考虑怎样才会说出一个 $\texttt{HILO}$，显然是在树上先往左儿子走后又往右子树走，统计这种情况的出现次数。  
特别的，如果当前结点恰好是询问的那一个，会回答 $\texttt{LO}$，把这个也统计进答案即可。  
时间复杂度 $O(n)$，可以通过。  

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define per(i,a,b) for(int i=(a);i<=(b);i++)
#define rep(i,b,a) for(int i=(b);i>=(a);i--)
#define all(x,l,r) &(x)[l],&(x)[r]+1
const int N=2e5+5;
int n,p[N],a[N],ans[N];
int rt,ls[N],rs[N],vis[N];
int top,st[N];
void dfs(int u,int fa,int cnt){
	if(!u) return;
	ans[u]=cnt+(!fa);
	dfs(ls[u],0,cnt);
	dfs(rs[u],1,cnt+(!fa));
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n;
    per(i,1,n) cin>>p[i];
    iota(all(a,1,n),1);
    sort(all(a,1,n),[](const int &x,const int &y){
        return p[x]<p[y];
    });
	st[top=1]=1;
	per(i,2,n){
		while(top&&a[i]<a[st[top]]) ls[i]=st[top--];
		if(top) rs[st[top]]=i;
		st[++top]=i;
	}
    per(i,1,n) vis[ls[i]]++,vis[rs[i]]++;
    per(i,1,n) if(!vis[i]) rt=i;
	dfs(rt,-1,0);
	per(i,0,n) cout<<ans[i]<<'\n';
    return 0;
}
```

---

