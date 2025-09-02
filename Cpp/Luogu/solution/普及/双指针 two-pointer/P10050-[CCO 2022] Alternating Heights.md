# [CCO 2022] Alternating Heights

## 题目描述

Troy 计划给 CCO 的学生拍一张合影，他向你寻求帮助。

有 $K$ 个学生，编号从 $1$ 到 $K$。Troy 忘记了学生的身高，但他记得没有两个学生的身高相同。

Troy 有一个序列 $A_{1}, A_{2}, \ldots, A_{N}$，表示合影中从左到右的学生顺序。一个学生可能在 $A$ 中出现多次。你不确定这张合影会怎么拍，但你不愿意认为 Troy 犯了错误。

Troy 会给你 $Q$ 个形式为 $x,y$ 的询问，每个询问为「给定学生序列 $A_{x}, A_{x+1}, \ldots, A_{y}$，他们的身高能否形成一个交替序列？」更具体地说，我们用 $h_i$ 表示第 $i$ 个学生的身高。如果存在一种身高分配$ h_1, h_2, \ldots, h_K$，使得 $h_{A_{x}}>h_{A_{x+1}}<h_{A_{x+2}}>h_{A_{x+3}}<\ldots h_{A_{y}}$，回答 `YES`；否则回答 `NO`。

注意，每个查询都是独立的：也就是说，询问 $i$ 的身高分配与询问 $j$ 的身高分配无关 $(i\neq j)$。

## 说明/提示

## 样例说明

对于第一个询问，不可能有 $h_1>h_1$，所以答案是 `NO`。

对于第二个询问，$h_1>h_2<h_3>h_1$ 的一种方案是 $h_1=160 \mathrm{~cm}, h_2=140 \mathrm{~cm}, h_3=180 \mathrm{~cm}$。另一种方案是 $h_1=1.55 \mathrm{~m}, h_2=1.473 \mathrm{~m}, h_3=1.81 \mathrm{~m}$。

对于第三个询问，不可能同时有 $h_1>h_2$ 和 $h_1<h_2$。

## 数据范围

对于所有的数据，有 $2 \leq N \leq 3000$，$2 \leq K \leq N$，$1 \leq Q \leq 10^{6}$。

子任务编号|	分值|	$N$|	$K$|	$Q$
:-:|:-:|:-:|:-:|:-:
$1$|	$16$|	$2 \leq N \leq 3000$|	$K=2$|	$1 \leq Q \leq 10^{6}$
$2$|	$24$|	$2 \leq N \leq 500$|	$2 \leq K \leq \min (N, 5)$|$1 \leq Q \leq 10^{6}$
$3$	|$28$|	$2 \leq N \leq 3000$	|$2 \leq K \leq N$	|$1 \leq Q \leq 2000$
$4$|	$32$| $2 \leq N \leq 3000$	|$2 \leq K \leq N$	|	$1 \leq Q \leq 10^{6}$

## 样例 #1

### 输入

```
6 3 3
1 1 2 3 1 2
1 2
2 5
2 6```

### 输出

```
NO
YES
NO```

# 题解

## 作者：Elysian_Realme (赞：7)

# P10050 [CCO2022] Alternating Heights

## 解题思路

先考虑暴力，对于每一个 $[l,r]$ 的区间，我们都可以将其抽象成一个由大小关系组成的图（从大指向小）。

如果没有环，那么这些学生的身高排序就是这张图的拓扑序。

如果这张图出现了环，那么肯定不成立（因为必定可以推出来 $x < x$）。

如果直接这么写显然就是 $O(n^3+q)$（$O(n^2)$ 枚举每一组 $[l,r]$ 再拓扑）。

不难发现，$\forall l,r\in [1,n],l<r$ 如果 $[l,r]$ 成立，那么 $[l,r-1]$ 必定成立，如果 $[l,r]$ 不成立，那么 $[l,r+1]$ 必定不成立。

这样一来，我们就可以二分预处理出每一个 $l$ 最大的 $r$，复杂度就可以变成 $O(n^2\log n+q)$

```cpp
// Problem: P10050 [CCO2022] Alternating Heights
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10050
// Memory Limit: 1000 MB
// Time Limit: 2000 ms
// 
// By：lmq
// AC Time：2024-03-28 19:53:18

#include <bits/stdc++.h>
using namespace std;
struct edge{
	int u,v,nxt;
}mp[100005];
int n,k,m,top,cnt,ans;
int a[3003],v[3003];
int idx[3003],rd[3003];
void add(int u,int v){
	rd[v]++;
	mp[++top].u=u;
	mp[top].v=v;
	mp[top].nxt=idx[u];
	idx[u]=top;
}
bool check(int l,int r){
	cnt=0,top=0,ans=0;
	memset(idx,0,sizeof(idx));
	memset(rd,0,sizeof(rd));
	for(int i=l+1;i<=r;i+=2){
		add(a[i-1],a[i]);
		if(i+1<=r){
			add(a[i+1],a[i]);
		}
	}
	queue <int> que;
	for(int i=1;i<=k;i++){
		if(!rd[i])
			que.push(i);
	}
	while(!que.empty()){
		int u=que.front();
		cnt++;
		que.pop();
		for(int i=idx[u];i!=0;i=mp[i].nxt){
			int v=mp[i].v;
			if(!--rd[v])
				que.push(v);
		}
	}
	return cnt==k;
}
signed main(){
	cin>>n>>k>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++){
		int l=i-1,r=n+1;
		while(l+1!=r){
			int mid=(l+r)>>1;
			if(check(i,mid))
				l=mid;
			else
				r=mid;
		}
		v[i]=max(l,i);
	}
	for(int i=1;i<=m;i++){
		int l,r;scanf("%d%d",&l,&r);
		if(r<=v[l])
			cout<<"YES\n";
		else
			cout<<"NO\n";
	}
	return 0;
} 
```

---

## 作者：T_TLucas_Yin (赞：5)

容易发现，题目说“忘了”学生的身高，也就是说学生的身高可以是我们设定的任意值。由于身高的精度也没有限制，所以也不会出现因为所有身高值都被占满导致的无法完成要求。所以，如果每个学生只出现一次，则每个区间都可以符合要求。

也就是说，任何一个区间不能满足要求，一定是因为一个学生出现了多次。这可能会造成（包括但不限于）以下几种情况：

- 一个学生需要比自己高或比自己矮。
- 一个学生需要同时比一个同学高和比这个同学矮。
- 按身高排列 $a>b>c$，但是 $c>a$。

如果我们把这个问题往图论上想，给区间中每一个同学都连一条有向边，指向要求的排列下需要比他高的同学，就会发现：此时若有类似 $a$ 比 $b$ 高且 $b$ 比 $a$ 高这样的矛盾条件，图中就会出现环。则若图中没有出现环，就不会有矛盾情况，这个区间就符合要求。

是不是很妙？判断一个区间是否符合要求只需要跑一遍拓扑排序就可以了。

不妙的是题目有多次操作。这就导致如果每一次都暴力算的话会超时。

进一步动脑子，如果一个区间满足了要求，那么从这个区间里去掉一名同学后肯定还是满足要求的。如果一个区间不满足要求，那么往这个区间里再加上一名同学后肯定更不满足要求。

这就意味着，对于以每一个位置为左端点的合法区间的长度都是有上限的。长度在上限以内的区间就能满足要求。我们可以找出每个左端点的区间最大长度，然后对于每次以它为左端点的查询，判断右端点是否在上限之内就行了。

那么怎么找这个上限呢？暴力枚举肯定会超时。我们应该立刻想到二分查找。这样，每次判定一个区间是否合法需要 $O(n)$，找一个位置的区间最大长度就需要 $O(n\log n)$，找 $n$ 个位置就需要 $O(n^2\log n)$。看看这道题给的时空上限，完全够了，多么舒服。

这样就迎刃而解了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t,x,y,a[10005],f[10005];//这些是完成题目要求需要的
int d[3005][3005],top[3005],in[3005];
queue<int> q;//这些是拓扑排序需要的
bool check(int l,int r){//拓扑排序
    memset(in,0,sizeof(in));
    memset(top,0,sizeof(top));
    for(int i=l+1;i<=r;i+=2){//区间内的这些点，两边的点都比它高
		if(i-1>0) d[a[i]][++top[a[i]]]=a[i-1],in[a[i-1]]++;
		if(i+1<=r) d[a[i]][++top[a[i]]]=a[i+1],in[a[i+1]]++;//防溢出
    }
    while(!q.empty()) q.pop();
	for(int i=1;i<=m;i++) if(!in[i]) q.push(i);
	int sum=0;
    while(!q.empty()){
        int p=q.front();
		q.pop();
		sum++;
		for(int i=1;i<=top[p];i++){
			in[d[p][i]]--;
			if(!in[d[p][i]]) q.push(d[p][i]);
		}
    }//这里就是纯纯的拓扑
	return sum==m;
}
int F(int k){//二分查找以k为左端点的合法区间最长长度
	int l=k,r=n,mid,p=0;
    while(l<=r){
        mid=(l+r)>>1;
        if(check(k,mid)) p=max(p,mid),l=mid+1;
        else r=mid-1;
    }
    return p;
}
int main(){
    cin>>n>>m>>t;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) f[i]=F(i);//存好最大长度
    for(int i=1;i<=t;i++){
        cin>>x>>y;
        if(y<=f[x]) cout<<"YES\n";
        else cout<<"NO\n";//右端点比上限小就是合法，反之不合法
    }
    return 0;
}
```

---

## 作者：Floating_Trees (赞：4)

![image.png](https://s2.loli.net/2024/12/31/Mn76XraWziBFYle.png)

### 思路
首先我们考虑一个询问 $(x,y)$ 怎样是不合法的。样例中的第 $3$ 组询问给了提示。由 $h_1 > h_2 < h_3 > h_1 < h_2$ 我们可以推出 $h_1 > h_2$ 且 $h_1 < h_2$，那么只要询问中有这样的矛盾，那么一定是不合法的。我们也可以自己举一些例子，可以发现会有如 $h_x > h_y > h_z > h_x$ 这样的式子，那么就矛盾了。

那么我们可以考虑如果 $h_x > h_y$ 则从 $x$ 向 $y$ 连一条边，那么我们只需要判断图中是否有环即可，那么用拓扑排序解决即可。

此时我们有一个算法：对于每一次询问 $(x,y)$，我们只要建图，再判环即可。时间复杂度为 $O(Q\times N)$。

但是对于 $2 \leq N \leq 3000, 1 \leq Q \leq 10^6$ 的数据，这样的算法显然会超时。那么我们可以通过预处理每一个区间 $[l,r]$ 是否合法，再 $O(1)$ 完成询问。时间复杂度为 $O(Q+N^3)$。

但是这样仍然会超时，考虑继续优化。瞪眼可得一个十分重要的性质：对于一个区间 $[l, r]$，若该区间合法，则 $[l, i](l \leq i \leq r)$ 都是合法的（易证）。那么我们只要求出对于每一个 $l$，最大的 $r$ 是多少就行了。可以通过二分求得。时间复杂度为 $O(Q+N^2\log N)$。
### 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int N = 3010;
int n, k, q, ans[N], a[N], in[N];
vector<int> E[N];

bool check(int l, int r)
{
	if (l == r) return true;
	memset(in, 0, sizeof(in));
	for (int i = 1;i <= k;i++)
		E[i].clear();
	for (int i = l;i < r;i++)
		if ((i - l + 1) % 2 == 1)
			E[a[i]].push_back(a[i+1]), in[a[i+1]]++;
		else
			E[a[i+1]].push_back(a[i]), in[a[i]]++;
	queue<int> q;
	int cnt = 0;
	for (int i = 1;i <= k;i++)
		if (!in[i])
			q.push(i);
	while (!q.empty())
	{
		int f = q.front(); q.pop();
		cnt++;
		for (auto i : E[f])
		{
			in[i]--;
			if (!in[i]) q.push(i);
		}
	}
	return cnt == k;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	
	cin >> n >> k >> q;
	for (int i = 1;i <= n;i++)
		cin >> a[i];
	for (int i = 1;i <= n;i++)
	{
		int l = i, r = n, best = -1;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			if (check(i, mid)) best = mid, l = mid + 1;
			else r = mid - 1;
		}
		ans[i] = best;
	}
	int x, y;
	while (q--)
	{
		cin >> x >> y;
		cout << (y <= ans[x] ? "YES" : "NO") << endl;
	}

	return 0;
}
``````

---

## 作者：IkeveLand (赞：4)

## [P10050](https://www.luogu.com.cn/problem/P10050)

## **动态规划求解：**

- 定义一个二维数组 $dp[]$ ,其中 $dp_{i,j}$ 表示以第 $i$ 个学生为倒数第一个学生,第 $j$ 个学生为倒数第二个学生时，是否存在交替序列。

- 根据题目要求，~~递推地~~计算 $dp[]$ 的值。具体来说，对于每一个学生 $H_{x}$ ,需要判断他与他前一个学生 $H_{x-1}$ 的身高关系。如果 $H_{x}$ $>$ $H_{x-1}$ ，则 $dp_{x,x-1}$ 为真，反之。

- 其次，对于每个学生 $H_{y}$ ，我们需要判断他与前一个学生 $H_{y-1}$  的身高关系。如果 $H_{y}$ $>$ $H_{y-1}$ ， $dp_{y,y-1}$ 为真，反之。

- 对于每个学生 $H_{i}$ ，其中 $x<i<y$，我们需要判断他与前两个学生的身高关系。如果 $H_{i}>H_{i-1}$ 且 $H_{i-1}<H_{i-2}$，则 $dp_{i,i-1}$ 为真，反之。

- 最后，我们可以通过查询的范围 $x$ 和 $y$ ，判断 $dp_{y,x-1}$ 的值，如果为真，则回答 **YES**，否则回答 **NO**.

---

## 作者：cff_0102 (赞：4)

~~这题我是看到题目编号是前管理 xht 的 UID 前五位来的。~~

首先，先考虑对于其中一个询问，怎么求是否有一个正确的方案。可以先将问题转化为一个 $r-l$ 条边的有向图，如果根据题面中的要求 $A_i$ 应该大于 $A_{i+1}$，就建一个 $A_{i+1}$ 到 $A_i$ 的边，这样，每条边都从一个身高值相对较小的编号指向一个身高值相对较大的编号。如果这个图没有环，那么所有学生的身高大小就是可以比出来的（具体地说，是按照拓扑序），那么就输出 `YES`，否则输出 `NO`。总结一下，就是先 $O(n)$ 根据大小关系建图，再 $O(n)$（拓扑排序）判断是否有环。这一块时间复杂度就是 $O(n)$。

接着，考虑对于每个可能的 $[l,r]$，计算出对应的答案，到最后直接根据询问的输入输出相应的答案。此时需要用 $O(n^2)$ 枚举 $[l,r]$，再用上面的方法 $O(n)$ 算出是否有答案，总时间复杂度 $O(n^3)$，明显不是正解。

那么如何优化呢？小小的模拟一下上面所说的算法中枚举 $[l,r]$ 并判断答案的过程，可以发现两点：

- 如果 $[l,r]$ 有解，那么 $[l,r-1]$ 必定有解（直接用 $[l,r]$ 解法的方案来解决 $[l,r-1]$ 的问题）。
- 如果 $[l,r]$ 无解，那么 $[l,r+1]$ 必定无解（本来就无解的，又添加一个条件，那不是还是无解吗）。

再看一眼就会发现，对于每个 $l$，存在一个 $r$ 使得 $[l,l+1],[l,l+2],\dots,[l,r-1],[l,r]$ 满足条件，而 $[l,r+1],\dots,[l,n]$ 不满足条件。

于是，这里就可以使用二分，将枚举 $r$ 的 $O(n)$ 降到了用二分找到 $r$ 的 $O(\log n)$ 的复杂度（当然整个二分的复杂度是 $O(n\log n)$，有一个用 $O(n)$ 拓扑实现的 `check` 函数）。总的时间复杂度就从 $O(n^3)$ 降到了 $O(n^2\log n)$。计算一下，$3000\times3000\times\log_23000\approx1.03\times10^8$，在 $2$ 秒的时间限制下是可过的。

具体实现流程：

1. 输入 $A$ 数组。
2. 从 $1$ 到 $n$ 枚举每个可能的 $l$。
3. 使用二分找到最大的 $r$，使得 $[l,r]$ 满足条件（设二分中的左右端点为 $l',r'$）：
   1. 先算出 $mid=\lfloor\dfrac{l'+r'}2\rfloor$。
   2. 然后通过使用拓扑排序的 `check(l,mid)` 判断 $[l,mid]$ 是否满足条件（具体方法见第一段）。
   3. 接着，如果 `check` 函数返回 `false`，则 $[l,mid]$ 不能满足条件，接着二分 $[l',mid-1]$；如果 `check` 函数返回 `true`，则 $[l,mid]$ 满足条件，接着二分 $[mid,r']$。
   4. 直到最后 $l'=r'$，就返回 $l'$（或 $r'$），表示找到的这个 $r$。
   - 注意：这里的 $l$ 是外面循环中枚举的 $l$，不是二分中的 $l'$；同时二分要算出的是满足条件的 $r$，也不要和二分中的 $r'$ 搞混了。二分中的 $l',r'$ 是用来锁定 $r$ 的范围的，表示要找的那个 $r$ 在 $l',r'$ 之间。
4. 找到符合要求的 $r$ 后，将其存在一个数组里，设其为 $B$，$B_l$ 表示使 $[l,r]$ 满足条件的最大的 $l$。
5. 全部 $l$ 枚举完，接着再输入每个询问。对于每个询问，输入 $l,r$，若 $B_l<r$，则输出 `NO`，否则输出 `YES`。

时间复杂度 $O(n^2\log n)$。

---

## 作者：Loser_Syx (赞：4)

首先你发现当区间 $[l,r]$ 满足条件时，由于构造的是 $a_l > a_{l+1} < a_{l+2} > \ldots a_r$，并且条件是一层一层附加的，所以去掉 $a_l > a_{l+1} <$ 后，区间 $[l+2,r]$ 还是满足条件的。  
考虑对于 $l$ 的奇偶分两次进行双指针，每次如果 $[l,r]$ 满足条件，根据上述性质对于每一个 $[l+2,r],[l+4,r],\ldots$ 进行扩充，最后拓展 $r$；如果不满足条件，则扩展 $l$（因为是按照奇偶的所以应为 $l \gets l+2$）。

但是如何判断满足条件呢？发现是否可以构造出合法的身高是需要满足若干的 $h_i > h_j$ 条件中不存在逻辑错误（即环），于是可以直接根据 $h_i>h_j$ 连一条 $i \rightarrow j$ 的边，拓扑即可。

双指针 $O(n)$，拓扑 $O(n)$，复杂度 $O(n^2)$。

```cpp
const int N = 3333;
int head[N], nxt[N], edge[N], d[N], cnt, n, q, Q[N], a[N], k;
void addedge(int x, int y) {
	edge[++cnt] = y;
	nxt[cnt] = head[x];
	head[x] = cnt;
}
bool check(int l, int r) {
	for (int i = 0; i < N; ++i) head[i] = d[i] = 0;
	cnt = 0;
	for (int i = l, j = l+1, flag=0; i < r; ++i, ++j, flag=!flag) {
		if (flag) addedge(a[j], a[i]), ++d[a[i]];
		else addedge(a[i], a[j]), ++d[a[j]];
	}
	int H=1, T=0, C=0;
	for (int i=1;i<=n;++i) if (!d[i]) Q[++T]=i,++C;
	while (H<=T) {
		int u=Q[H++];
		for (int i=head[u];i;i=nxt[i]) {
			d[edge[i]]--;
			if (!d[edge[i]]) {
				Q[++T]=edge[i];
				++C;
			}
		} 
	}
	return C==n;
}
int ans[N][N];
void TwoPointer(int begin) {
	int l = begin, r = begin;
	while (l <= r && r <= n) {
		if (check(l, r)) {
			for (int i = l; i <= r; i += 2) ans[i][r] = 1;
			++r;
		} else {
			l += 2;
			if (l > r) ++r;
		}
	}
}
signed main() {
	read(n, k, q);
	for (int i=1;i<=n;++i) read(a[i]);
	TwoPointer(1); TwoPointer(2);
	while (q--) {
		int x, y; read(x, y);
		puts(ans[x][y] ? "YES" : "NO");
	}
	return 0;
}
```

---

## 作者：Dream__Sky (赞：3)

对于本题，首先可以发现，一个区间是否可能成立，存在单调性。即如果 $[l,r]$ 不满足条件，$[l,r+1]$ 也不会满足条件。因为前面的区间都有高度存在矛盾了，再加一个人，不可能去掉之前的矛盾，只可能会带来新的矛盾。

我们考虑预处理，用二分来解决。枚举每个左端点 $l$，二分枚举右端点 $r$。接下来我们像如何判断此区间是否满足条件。

题目所问的是该区间能不能有一种方式，使高度大小交错，且没有矛盾。我们可以转化为求 `DAG`，从应该小的点向大的点建边，接着跑拓扑排序。如果高度出现了矛盾，那么说明图中会出现环。

举个最简单的例子：

现在有 $a,b,c$ 三人，需要满足 ${a>b<c>a<b}$。
                                 
显然，这个区间是不可能的，其中 $a$ 与 $b$ 就出现了环。
                                   
代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=3e3+10;
int n,k,Q,a[N],rs[N][N],deg[N];
vector<int> E[N];
void build(int l,int r)
{
	for(int i=1;i<=N-10;i++) E[i].clear();
	memset(deg,0,sizeof deg);
	
	for(int i=l+1;i<=r;i+=2)
	{ 
		if(i+1<=r) E[a[i]].emplace_back(a[i+1]),deg[a[i+1]]++;
		if(i-1>0) E[a[i]].emplace_back(a[i-1]),deg[a[i-1]]++;
	}
}
bool check()
{
	queue<int> q;
	for(int i=1;i<=k;i++) 
		if(!deg[i]) q.push(i);
	
	int sum=0;
	while(!q.empty())
	{
		int now=q.front();
		q.pop();
		sum++;
		for(int i=0;i<E[now].size();i++)
		{
			int v=E[now][i];
			deg[v]--;
			if(!deg[v]) q.push(v);
		}	
	} 	 
	return sum==k;
}
int main()
{
	ios::sync_with_stdio(0);
	cin>>n>>k>>Q;
	for(int i=1;i<=n;i++) cin>>a[i];
	
	for(int i=1;i<=n;i++)
	{
		int l=i,r=n,ans=0;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			build(i,mid);
			if(check()) ans=max(ans,mid),l=mid+1;
			else r=mid-1;
		}
		for(int j=i;j<=ans;j++) rs[i][j]=1;
	}
	
	while(Q--) 
	{
		int x,y;
		cin>>x>>y;
		cout<<(rs[x][y]==1?"YES\n":"NO\n");
	}
	return 0;
}


```
                                  
                               

---

## 作者：shinzanmono (赞：3)

容易发现如果区间 $[l,r]$ 不符合条件，那么区间 $[l,r+1]$ 也不符合条件，结合题目没有修改，我们考虑二分。

枚举每个左端点 $l$，二分右端点，将原问题转化为图论问题，即相邻两数由小的向大的连边，如果得到的图是 DAG，说明区间是符合条件的。

总时间复杂度 $O(NK\log N+Q)$，可以通过本题。

```cpp
#include<iostream>
#include<algorithm>
#include<queue>
const int sz=3010;
int a[sz],n,m,q;
bool res[sz][sz];
std::basic_string<int>graph[sz];
int indeg[sz];
bool check(){
    std::queue<int>qq;
    int cnt=0;
    for(int i=1;i<=m;i++)
        if(indeg[i]==0)qq.push(i);
    while(!qq.empty()){
        int u=qq.front();
        qq.pop(),cnt++;
        for(int v:graph[u]){
            indeg[v]--;
            if(indeg[v]==0)qq.push(v);
        }
    }
    return cnt==m;
}
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin>>n>>m>>q;
    for(int i=1;i<=n;i++)std::cin>>a[i];
    for(int l=1;l<=n;l++){
        int bl=l,br=n;
        while(bl<br){
            int mid=bl+br+1>>1;
            for(int i=1;i<=m;i++)graph[i].clear();
            std::fill(indeg+1,indeg+m+1,0);
            for(int i=l+1;i<=mid;i++){
                if(i-l&1)graph[a[i]]+=a[i-1],indeg[a[i-1]]++;
                else graph[a[i-1]]+=a[i],indeg[a[i]]++;
            }
            if(check())bl=mid;
            else br=mid-1;
        }
        for(int i=l;i<=bl;i++)res[l][i]=true;
    }
    while(q--){
        int l,r;
        std::cin>>l>>r;
        if(res[l][r])std::cout<<"YES\n";
        else std::cout<<"NO\n";
    }
    return 0;
}
```

---

## 作者：ghfchgh (赞：1)

# 洛谷题解：P10050 [CCO2022] Alternating Heights

### 题目传送门：
[题目传送](https://www.luogu.com.cn/problem/P10050)

### 转换思想：
这道题可以转化为一个图论问题。将序列中的每个元素看作图中的一个节点，如果序列中两个元素相邻，则在对应的节点之间连一条边。这样思考会使问题转化为在图中找到 $k$ 个节点，使得这 $k$ 个节点互不相邻（即不通过边直接相连）。

二分查找：对于每一次询问，我们需要找到一个最大的数  $ans$ ，使得从位置 $i$ 开始的子序列中，存在 $k$ 个互不相同且两两不相邻的元素。我们使用二分查找来确定这个 $ans$ 的值。

### check 函数：
 check 函数用于检查在给定的子序列中是否存在 $k$ 个互不相同且两两不相邻的元素。作者使用队列来实现这个函数。

### 如何使用队列实现：
在 check 函数中，使用队列来实现 BFS（广度优先搜索）。先将所有未被访问的节点加入队列。然后，遍历队列中的每个节点，对于每个节点，检查其相邻节点，如果相邻节点的入度减 $1$ 后为 $0$ ，则将该相邻节点加入队列。如果遍历结束后，队列中的节点数等于 $k$ ，则说明存在 $k$ 个互不相同且两两不相邻的元素。

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
struct edge{
	int u,v,nxt;
}mp[100005];
int n,k,m,top,cnt,ans,a[3003],v[3003],idx[3003],rd[3003];
void add(int u,int v){//add函数用于在图中添加一条边
	rd[v]++;
	mp[++top].u=u;
	mp[top].v=v;
	mp[top].nxt=idx[u];
	idx[u]=top;
}
bool check(int l,int r){//check函数用于检查从l到r的子序列中是否存在k个互不相同且两两不相邻的元素
	cnt=0,top=0,ans=0;
	memset(idx,0,sizeof(idx));
	memset(rd,0,sizeof(rd));
	for(int i=l+1;i<=r;i+=2){
		add(a[i-1],a[i]);
		if(i+1<=r) add(a[i+1],a[i]);
	}
	queue<int> que;
	for(int i=1;i<=k;i++) if(!rd[i]) que.push(i);
	while(!que.empty()){
		int u=que.front();
		cnt++;
		que.pop();
		for(int i=idx[u];i!=0;i=mp[i].nxt){
			int v=mp[i].v;
			if(!--rd[v]) que.push(v);
		}
	}
	return cnt==k;
}
signed main(){
	cin>>n>>k>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		int l=i,r=n,ans=l;
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(i,mid)){
				ans=mid;
				l=mid+1;
			}
			else r=mid-1;
		}
		v[i]=ans;
	}
	for(int i=1;i<=m;i++){
		int l,r;
		cin>>l>>r;
		if(r<=v[l]) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}

```

完结，撒花！（求过审）

---

## 作者：tanghg (赞：0)

发现对于多组数据每组单独处理肯定是无法做到的。可以看看能不能先根据一些区间的连续性来推出每一个区间是否合法。

之后发现对于一个区间  $[l,r]$ 合法，那么 $[l,i],i\in [l,i]$ 全部合法。若 $[l,r] $ 不合法，则 $[l,i],i\in[r,n]$ 一定全部不合法。所有我们发现可以枚举每一个 $l$，尝试二分求出一个最大的 $r$ 使 $[l,r]$ 合法。

之后考虑如何判断 $[l,r]$ 是否合法。发现类似与差分约束，可是只有大于关系没有不等式关系。于是对于每一个要求的 $h_{A_{x-1}}>h_{A_x}<h_{A_{x+1}}$，我们连两个有向边 $A_{x-1}\rightarrow A_x$ 和 $A_{x+1}\rightarrow A_x$。之后得到一张有向无权图。

显然如果图出现了环就非法，没有就合法。考虑到 $h$ 互不相同的条件发现所有的有向边的约束全部是大于关系，且没有规定 $h$ 的值域，所以自然不存在相等情况。

时间复杂度 $O(Q+n^2\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN=3000+5;
const ll MAXQ=1e6+5;
ll n,k,Q;
ll a[MAXN];
bool gd[MAXN][MAXN];
vector<ll>adj[MAXN];
ll ind[MAXN];
void add(ll u,ll v){
	adj[u].push_back(v);
	ind[v]++;
}
bool check(ll l,ll r){
	memset(ind,0,sizeof(ind));
	for(int i=1;i<=k;++i){
		adj[i].clear();
	}
	for(int i=l+1;i<=r;i+=2){
		add(a[i-1],a[i]);
		if(i+1<=r){
			add(a[i+1],a[i]);
		}
	}
	queue<ll>q;
	ll tot=0;
	for(int i=1;i<=k;++i){
		if(!ind[i]){
			q.push(i);
		}
	}
	while(!q.empty()){
		ll u=q.front();
		q.pop();
		tot++;
		for(auto v:adj[u]){
			ind[v]--;
			if(!ind[v]){
				q.push(v);
			}
		}
	}
	return tot==k;
}
ll ans[MAXN];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>k>>Q;
	for(int i=1;i<=n;++i){
		cin>>a[i];
	}
	for(int i=1;i<=n;++i){
		ll l=i,r=n;
		ans[i]=i;
		while(l<=r){
			ll mid=(l+r)>>1;
			bool good=check(i,mid);
			if(good){
				l=mid+1;
				ans[i]=mid;
			}else{
				r=mid-1;
			}
		}
	};
	for(int i=1;i<=Q;++i){
		ll x,y;
		cin>>x>>y;
		if(y<=ans[x]){
			cout<<"YES\n";
		}else{
			cout<<"NO\n";
		}
	}
	return 0;
}

```

---

## 作者：船酱魔王 (赞：0)

## 题意回顾

$ k $ 元不等式，有 $ n $ 项，第 $ i $ 项为第 $ a_i $ 个元。每次询问 $ [l,r] $ 区间的不等式即 $ x_{a_l}>x_{a_{l+1}}<x_{a_{l+2}}>\cdot \cdot \cdot x_{a_r} $ 是否存在 $ x $ 变量的赋值方案使其满足。

$ 2 \le k \le n \le 3000 $，询问次数较大。

## 分析

首先大于号小于号全反过来是本质相同的，询问具有单调性，若一个区间满足条件子区间必定满足条件，这类问题考虑找到每个左端点的最大答案为是的右界。

刻画问题为，较大的变量向对应较小的变量连边，若存在环则为不可行。转化为有向图找环问题，可以用拓扑排序等方式解决。

找界可以二分。

总时间复杂度为 $ O(n(n+k) \log n) $。

## 参考实现

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int N = 3005;
int n, k, q;
int a[N];
int wzj[N];
vector<int> g[N];
int ind[N];
queue<int> que;
inline bool lwhzkj(int l, int r) {
    for(int i = 1; i <= n; i++) g[i].clear();
    for(int i = l; i < r; i++) {
        if(i % 2 == 0) g[a[i]].push_back(a[i + 1]), ind[a[i + 1]]++;
        else g[a[i + 1]].push_back(a[i]), ind[a[i]]++;
    }
    for(int i = 1; i <= n; i++) {
        if(!ind[i]) que.push(i);
    }
    int u, v;
    while(!que.empty()) {
        u = que.front(), que.pop();
        for(int i = 0; i < g[u].size(); i++) {
            v = g[u][i], ind[v]--;
            if(!ind[v]) que.push(v);
        }
    }
    u = 0;
    for(int i = 1; i <= n; i++) u += min(1, ind[i]), ind[i] = 0;
    return u == 0;
}
int main() {
    scanf("%d%d%d", &n, &k, &q);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    int l, r, mid;
    for(int li = 1; li <= n; li++) {
        l = li, r = n + 1;
        while(l + 1 < r) {
            mid = (l + r) >> 1;
            if(lwhzkj(li, mid)) l = mid;
            else r = mid;
        }
        wzj[li] = l;
    }
    for(int i = 1; i <= q; i++) scanf("%d%d", &l, &r), puts((wzj[l] >= r) ? "YES" : "NO");
    return 0;
}

```

---

## 作者：Nuyoah_awa (赞：0)

### 题目大意

对于一些可能重复出现的人，问其身高能否形成交替序列。

### 题目分析

我们考虑先来看看交替序列的一些性质：

1. 对于一些人，若其满足 $h_{A_{x}} > h_{A_{x+1}} < h_{A_{x+2}} > \dots < h_{A_{y}}$，则其一定满足 $h_{A_{x}} < h_{A_{x+1}} > h_{A_{x+2}} < \dots > h_{A_{y}}$。所以我们发现“交替序列”真的只需要“交替”，而先大于还是先小于并不影响。

2. 对于一些人，若其满足 $h_{A_{x}} > h_{A_{x+1}} < h_{A_{x+2}} > \dots < h_{A_{y}}$，则 $\forall l,r\in[x,y]$ 都有 $h_{A_{l}} > h_{A_{l+1}} < h_{A_{l+2}} > \dots < h_{A_{r}}$。

所以我们发现若 $A_{l}\sim A_{r}$ 满足“交替序列”，且 $A_{l}\sim A_{r+1}$ 不满足“交替序列”，即 $r$ 为以 $l$ 为左界，最长的“交替序列”的右界，那么若以 $l+1$ 为左界，则 $A_{l+1}\sim A_{r}$ 一定满足“交替序列”，所以以 $l+1$ 为左界的最远右界 $r'$，一定满足 $r' \ge r$。

以此类推，我们令 $r_i$ 为以 $i$ 为左界的最远右界，则 $r$ 数组具有单调性。于是可以考虑双指针预处理出 $r$，对于询问 $(x,y)$，若 $y \le r_x$，则存在。

### code
```cpp
#include <iostream>
#include <cstdio>
#include <set>
#include <map>

using namespace std;

const int N = 3e3 + 5;
int n, k, q, a[N], f[N], l, r;
bool cnt[N];
set <int> e[N];
map <pair<int, int>, int> mp;

inline bool dfs(int x, int goal)
{
    //printf("%d\n", x);
    if(x == goal)   return true;
    if(cnt[x])  return false;
    cnt[x] = true;
    for(set<int>::iterator it = e[x].begin();it != e[x].end();it++)
        if(dfs(*it, goal))
            return true;
    return false;
}

int main()
{
    scanf("%d %d %d", &n, &k, &q);
    for(register int i = 1;i <= n;i++)
        scanf("%d", &a[i]);
    for(register int i = 1, j = 1;i <= n;i++)
    {
        f[i] = j;
        while(j < n)
        {
            j++;
            if(j & 1)
            {
                for(register int l = 1;l <= n;l++)   cnt[l] = false;
                //printf("%d %d\n", a[j], a[j-1]);
                if(dfs(a[j], a[j-1]))
                {
                    j--;
                    break;
                }
                if(mp[make_pair(a[j-1], a[j])] == 0)
                    e[a[j-1]].insert(a[j]);
                mp[make_pair(a[j-1], a[j])]++;
            }
            else
            {
                for(register int l = 1;l <= n;l++)   cnt[l] = false;
                //printf("%d %d\n", a[j-1], a[j]);
                if(dfs(a[j-1], a[j]))
                {
                    j--;
                    break;
                }
                if(!mp[make_pair(a[j], a[j-1])])
                    e[a[j]].insert(a[j-1]);
                mp[make_pair(a[j], a[j-1])]++;
            }
            f[i] = j;
        }
        //printf("%d %d %d\n", i, f[i], j);
        if(j > i)
        {
            if(i & 1)
            {
                if(--mp[make_pair(a[i+1], a[i])] == 0)
                    e[a[i+1]].erase(a[i]);
            }
            else
            {
                if(--mp[make_pair(a[i], a[i+1])] == 0)
                    e[a[i]].erase(a[i+1]);
            }
        }
        else
        {
            j = i + 1;
        }
    }
    //for(int i = 1;i <= n;i++)
    //    printf("%d\n", f[i]);
    while(q--)
    {
        scanf("%d %d", &l, &r);
        puts(r <= f[l] ? "YES" : "NO");
    }
    return 0;
}
```

---

