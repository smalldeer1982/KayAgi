# Anji's Binary Tree

## 题目描述

Keksic keeps getting left on seen by Anji. Through a mutual friend, he's figured out that Anji really likes binary trees and decided to solve her problem in order to get her attention.

Anji has given Keksic a binary tree with $ n $ vertices. Vertex $ 1 $ is the root and does not have a parent. All other vertices have exactly one parent. Each vertex can have up to $ 2 $ children, a left child, and a right child. For each vertex, Anji tells Keksic index of both its left and its right child or tells him that they do not exist.

Additionally, each of the vertices has a letter $ s_i $ on it, which is either 'U', 'L' or 'R'.

Keksic begins his journey on the root, and in each move he does the following:

- If the letter on his current vertex is 'U', he moves to its parent. If it doesn't exist, he does nothing.
- If the letter on his current vertex is 'L', he moves to its left child. If it doesn't exist, he does nothing.
- If the letter on his current vertex is 'R', he moves to its right child. If it doesn't exist, he does nothing.

 Before his journey, he can perform the following operations: choose any node, and replace the letter written on it with another one. You are interested in the minimal number of operations he needs to do before his journey, such that when he starts his journey, he will reach a leaf at some point. A leaf is a vertex that has no children. It does not matter which leaf he reaches. Note that it does not matter whether he will stay in the leaf, he just needs to move to it. Additionally, note that it does not matter how many times he needs to move before reaching a leaf.

Help Keksic solve Anji's tree so that he can win her heart, and make her come to Čačak.

## 说明/提示

In the first test case, vertex $ 1 $ has $ 2 $ as its left child and $ 3 $ as its right child. Vertices $ 2 $ and $ 3 $ do not have children and are therefore leaves. As 'L' is written on vertex $ 1 $ , Keksic will go to vertex $ 2 $ , therefore he has to do no operations.

In the second test case, vertex $ 1 $ has $ 3 $ as its left child and $ 2 $ as its right child. Vertices $ 2 $ and $ 3 $ are leaves. As 'U' is written on vertex $ 1 $ , Keksic needs to change it to either 'L' or 'R' in order for him to reach a leaf.

In the third case, vertex $ 1 $ has only a right child, which is vertex $ 2 $ . As 'L' is written on it, Keksic needs to change it to 'R', otherwise he would be stuck on vertex $ 1 $ .

In the fourth case, he can change $ 3 $ characters so that letters on the vertices are "LURL", which makes him reach vertex $ 2 $ .

In the fifth case, there are $ 3 $ leaves, $ 3 $ , $ 6 $ and $ 7 $ . To reach either leaf $ 6 $ or leaf $ 7 $ , he needs to change $ 2 $ characters. However, if he changes character on vertex $ 1 $ to 'R', he will reach leaf $ 3 $ , therefore the answer is $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1900C/9018896e1391d18f63af647e477e71929a6a2577.png) The initial tree in test case 5.

## 样例 #1

### 输入

```
5
3
LRU
2 3
0 0
0 0
3
ULR
3 2
0 0
0 0
2
LU
0 2
0 0
4
RULR
3 0
0 0
0 4
2 0
7
LLRRRLU
5 2
3 6
0 0
7 0
4 0
0 0
0 0```

### 输出

```
0
1
1
3
1```

# 题解

## 作者：_smart_stupid_ (赞：7)

# [题目](https://www.luogu.com.cn/problem/CF1900C)

## 思路：

用一个数组 $dist$ 记录根到每一个节点要改变多少次，DFS 一遍，答案就是所有叶子节点中取 $dist$ 的最小值。

时间复杂度：$O(n)$。

## 细节一点的做法：

链式前向星存树，从根遍历树，对于每一个节点 $u$，设它的左儿子为 $l$，右儿子为 $r$。如果它在字符串对应中的字符是 L，$dist_l$ 就为 $dist_u$，否则为 $dist_u + 1$；如果是 R，$dist_r$ 就为 $dist_u$，否则为 $dist_u + 1$。

存树时用一个 $isleaf$ 数组记录是不是叶子节点， $isleaf_i = 0$ 表示他是叶子节点，最后在 $dist$ 数组里找答案时，还要用这个数组判叶子节点。

## AC Code：

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <list>
#include <set>
using namespace std;
int t;
int n;
char s[300100];
int l[300100], r[300100];
int dist[300100];
bool is_leaf[300100];
void dfs(int now) {
	if (now == 0) return ;
	dist[l[now]] = dist[now] + 1;
	dist[r[now]] = dist[now] + 1;
	if (s[now] == 'L') {
		dist[l[now]] = dist[now];
	}
	if (s[now] == 'R') {
		dist[r[now]] = dist[now];
	}
	dfs(l[now]);
	dfs(r[now]);
}
int ans;

int main() {
	scanf("%d", &t);
	while (t--) {
		ans = 0x3f3f3f3f;
		scanf("%d", &n);
		scanf("%s", &s[1]);
		memset(is_leaf, 0, sizeof(is_leaf));
		for (int i = 1; i <= n; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			l[i] = u, r[i] = v;
			if (u || v) is_leaf[i] = 1;
		}
		dist[1]=0;
		dfs(1);
		for (int i = 1; i <= n; i++) {
			if (!is_leaf[i]) {
				ans = min(ans, dist[i]);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：CuteChat (赞：2)

## 题意

给你一个二叉树，有人想从 $1$ 节点开始走到叶子节点，行动方法如下：

1. 当前点类型为 $L$，走到左儿子；
2. 当前点类型为 $R$，走到右儿子；
3. 当前点类型为 $U$，走到父亲。

行动前你可以修改点的类型，问至少需要修改多少次才能使得这个人**能走到**叶节点。

## 解题

因为我们是想要走到叶子，向上走明显是**多余**的行为，所以我们移动的时候不可能向上走。

如果我们节点 $i$ 是 $U$ 类型节点，那要么修改当前节点、要么修改父亲使其不会走到 $i$，很明显都需要修改 $1$ 次，显然多余。所以每个节点最多走一次。

既然每个节点最多走一次，那么先修再走就不如边走边修。

考虑目前是 $i$ 号节点，则有一下 $3$ 种情况：

1. $i$ 是空节点：永远不可能走到叶子，答案为 $\inf$。
2. $i$ 是叶节点：已经走到叶子了，答案为 $0$。
3. $i$ 不满足以上两个条件。


对于第 $3$ 种情况，再次考虑两种情况，因为我们可以向左走或者向右走。
1. 走到左儿子，若当前的点类型不是 $L$，就要动一次修，所以走到左儿子的代价为走到左儿子所需的代价加 $[S_i \neq L]$。
2. 走到右儿子，若当前的点类型不是 $R$，就要动一次修，所以走到右儿子的代价为走到右儿子所需的代价加 $[S_i \neq R]$。

显然两种情况取 $\min$ 即可。

发现这其实就是 DP，所以，我们记 $dp_i$ 表示从 $i$ 走到叶子的答案，那么则有：

$$
dp_i = \left\{\begin{aligned} \inf \space (i=0) \\ 0(L_i = 0 \land R_i = 0) \\
\min(dp_{L_i} + [S_i \neq L], dp_{R_i} + [S_i \neq R])(\text{其余情况})
\end{aligned}\right.
$$

显然没有后效性，因为说了不可能往回走。

从 $1$ 出发答案显然为 $dp_1$。

## 代码

```cpp
int dfs(int i) {
	if (i == 0) return 1 << 30;
	else if (l[i] == 0 && r[i] == 0) return 0;
	else return min(dfs(l[i]) + (s[i] != 'L'), dfs(r[i]) + (s[i] != 'R'));
}
```

---

## 作者：梦应归于何处 (赞：2)

### 题目大意

现在有一棵树，其中根节点为 $1$。现在给出每个节点上的字符表示他要往哪里走，如果是 $U$ 则去他的父亲节点，若没有父亲节点则什么都不做。如果是 $L$ 则去他的左儿子节点，若没有左儿子节点则什么都不做。如果是 $R$ 则去他的右儿子节点，若没有右儿子节点则什么都不做。

现在问你想要从根节点走到任意一个叶子节点最少需要修改几个节点上的字符。

### 思路

思路就是每次从根去搜索然后就记录走到当前节点最少需要改多少个字符，如果碰到叶子就更新答案。

### 代码

~~~cpp
#include <bits/stdc++.h>
#define db double
#define ll long long
#define ex exit(0)
#define endl "\n"
#define inl inline
#define null NULL
#define pb(a) push_back(a)
using namespace std;
inline ll read() {
	ll x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * f;
}
bool isye[300005];
string s;
struct node {
	ll l, r;
	char to;
} a[300005];
ll f[300005];
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll t;
	t = read();
	while (t--) {
		ll n;
		n = read();
		for (int i = 1; i <= n; i++) {
			f[i] = 0;
			isye[i] = 0;
			a[i].l = 0;
			a[i].r = 0;
		}
		f[1] = 0;
		cin >> s;
		s = " " + s;
		for (int i = 1; i <= n; i++) {
			a[i].to = s[i];
			a[i].l = read(), a[i].r = read();
			f[a[i].l] = i;
			f[a[i].r] = i;
			if (a[i].l == 0 && a[i].r == 0) {
				isye[i] = 1;
			}
		}
		ll ans = 1e18;
		queue<pair<ll, ll> > q;
		q.push(make_pair(1, 0));
		while (!q.empty()) {
			pair<ll, ll> u = q.front();
			q.pop();
			if (isye[u.first]) {
				ans = min(ans, u.second);
				continue;
			}
			if (a[u.first].l != 0) {
				if (a[u.first].to == 'U' || a[u.first].to == 'R') {
					q.push(make_pair(a[u.first].l, u.second + 1));
				} else {
					q.push(make_pair(a[u.first].l, u.second));
				}
			}
			if (a[u.first].r != 0) {
				if (a[u.first].to == 'U' || a[u.first].to == 'L') {
					q.push(make_pair(a[u.first].r, u.second + 1));
				} else {
					q.push(make_pair(a[u.first].r, u.second));
				}
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
~~~

---

## 作者：GWBailang (赞：1)

[**原题传送**](https://www.luogu.com.cn/problem/CF1900C)

题目大意就是给你一颗二叉树，树上的每个节点都标有一个字符。你要从根节点开始移动，如果当前所在节点上的字符为 `L`，你就可以去到这个节点的左孩子；如果字符为 `R`，你就可以去到这个节点的右孩子;如果字符为 `U`，你可以回到这个节点的父节点。现在问最少更改几个节点的字符，可以从根节点走到一个叶节点（走到一个即可）。

直接从树根开始找不好计算，那么就从叶节点入手。也就是枚举每个叶节点从根节点走，修改几次字符才能走到这个叶节点。对于一个叶节点，每次看它的父节点上的字符，如果它是它父亲的左节点，但是它父亲的字符不为 `L`，或它是它父亲的右节点，但是父亲的字符不为 `R`，则必须修改一次字符，才能从它的父节点走到它。就这么一直找，直到走到树根为止。

最后取个最小值完事，提交，~~喜提 TLE！~~

显然我们在走的过程中会干很多重复的事，所以需要加上记忆化搜索。

#### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long f[300005];
long long l[300005];
long long r[300005];
char c[300005];
long long g[300005];
void dfs(long long u){
	if(u==1||g[u]!=0)return;
	dfs(f[u]);
	g[u]=g[f[u]];
	if(l[f[u]]==u)
		if(c[f[u]]!='L')g[u]=g[f[u]]+1;
	if(r[f[u]]==u)
		if(c[f[u]]!='R')g[u]=g[f[u]]+1;
}
int main(){
	//freopen("A/in.in","r",stdin);
	//freopen("A/out.out","w",stdout);
	long long t,n,xiao;
	cin>>t;
	while(t--){
		cin>>n;
		for(long long i=1;i<=n;i++)
			f[i]=l[i]=r[i]=g[i]=0;
		xiao=INT32_MAX;
		for(long long i=1;i<=n;i++)cin>>c[i];
		for(long long i=1;i<=n;i++){
			scanf("%lld %lld",&l[i],&r[i]);
			f[l[i]]=i,f[r[i]]=i;
		}
		for(long long i=1;i<=n;i++){
			if(l[i]==0&&r[i]==0){
				dfs(i);
				xiao=min(xiao,g[i]);
			}
		}
		cout<<xiao<<endl;
	}
	return 0;
}
```

---

## 作者：IOI_AK_TLR (赞：1)

# 题意

给你一颗二叉树，每个结点都有一个编号、写着一个字母，根节点是一号节点。

**你从根节点开始出发**，如果当前节点上的字母是 **L**，那么下一步就必须走到当前节点的**左子节点**（若不存在则什么也不做）；如果当前节点上的字母是 **R**，那么下一步就必须走到当前节点的**右子节点**（若不存在则什么也不做）；如果当前节点上的字母是 **U**，那么下一步就必须走到当前节点的**父亲节点**（若不存在则什么也不做）。

你想通过更改一些节点上的字母来使得你能走到某个**叶子节点**上，请你输出至少要更改多少次（你不必考虑最终是否会停留在叶子节点上，只要走到就行）。

------------

# 思路

直接 DFS 计算从根节点到每个叶子节点至少要改多少次，取最小值即可。

更具体地，如果下一步要搜索的是当前节点的左子树，而当前节点上的字母**不是** **L**，或是下一步要搜索的是当前节点的右子树，而当前节点上的字母**不是** **R**，就把改动的次数加一，否则不变。

------------

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=3e5+10;
struct Node{
	char dat;
	int L,R;
};
string s;
int t,n,L_i,R_i,ans=INT_MAX;
void dfs1(Node*tr,int x,int sum=0)
{
	if(tr[x].L==0&&tr[x].R==0)
	{
		ans=min(ans,sum);
		return;
	}
	if(tr[x].L)
		dfs1(tr,tr[x].L,sum+(tr[x].dat!='L'));			
	if(tr[x].R)
		dfs1(tr,tr[x].R,sum+(tr[x].dat!='R'));
}
Node tr[N];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>t;
	while(t--)
	{
		cin>>n;
		cin>>s;
		for(int i=0;i<n;i++)
			tr[i+1].dat=s[i];
		for(int i=1;i<=n;i++)
		{
			cin>>L_i>>R_i;
			tr[i].L=L_i;
			tr[i].R=R_i;
		}
		ans=INT_MAX;
		dfs1(tr,1,0);
		cout<<ans<<'\n';
		for(int i=1;i<=n;i++)
			tr[i].L=tr[i].R=tr[i].dat=0;
	}
	return 0;
}

```


---

## 作者：huangrenheluogu (赞：0)

暴力，直接算到每个节点需要改变的最少次数 $f_i$。更新的时候判断是否加步数即可。

首先，$f_x$ 必然是 $1$ 到 $x$ 路径上的点更新的，不然必然走到了 $x$。

所以复杂度是 $\mathcal{O}(n)$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
int T, n, ls[N], rs[N], f[N], dep[N], fa[N], rt, ans;
char s[N];
inline void dfs(int x){
	if(!ls[x] && !rs[x]){
		ans = min(ans, f[x]);
		return ;
	}
	if(s[x] == 'L' || s[x] == 'R'){
		if(f[fa[x]] > f[x] + 1 && fa[x]){
			f[fa[x]] = f[x] + 1;
			dfs(fa[x]);
		}
	}
	if(s[x] == 'U' || s[x] == 'L'){
		if(rs[x] && f[rs[x]] > f[x] + 1){
			f[rs[x]] = f[x] + 1;
			dfs(rs[x]);
		}
	}
	if(s[x] == 'R' || s[x] == 'U'){
		if(ls[x] && f[ls[x]] > f[x] + 1){
			f[ls[x]] = f[x] + 1;
			dfs(ls[x]);
		}
	}
	if(s[x] == 'L'){
		if(ls[x] && f[ls[x]] > f[x]){
			f[ls[x]] = f[x];
			dfs(ls[x]);
 		}
	}
	if(s[x] == 'R'){
		if(rs[x] && f[rs[x]] > f[x]){
			f[rs[x]] = f[x];
			dfs(rs[x]);
		}
	}
	if(s[x] == 'U'){
		if(fa[x] && f[fa[x]] > f[x]){
			f[fa[x]] = f[x];
			dfs(fa[x]);
		}
	}
}
int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		scanf("%s", s + 1);
		for(int i = 1; i <= n; i++) fa[i] = 0, f[i] = n + 1;
		ans = n + 1;
		for(int i = 1; i <= n; i++){
			scanf("%d%d", &ls[i], &rs[i]);
			fa[ls[i]] = i, fa[rs[i]] = i;
		}
		f[1] = 0;
		dfs(1);
		printf("%d\n", ans);
	}
	return 0;
}
```

[评测链接](https://codeforces.com/contest/1900/submission/236861727)

---

## 作者：Halberd_Cease (赞：0)

首先，往回走这种情况肯定是不行的（叶节点除外，实际上叶节点的字母是什么根本不重要），那么到达每一个节点有且仅有一种可能的路径，即从根到节点的简单路径，我们考虑 dfs，求出从根节点到每一个节点的最小改变数量。

如果这一个节点有左儿子，那么考虑往下递归，如果这个点的字母是 `L`，就可以直接往下走，否则代价加上 $1$ 过后往下走，走到叶节点之后统计答案。右儿子同理。初始根节点的代价为 $0$。

关于存边，两个数组即可。

递归代码如下：
```cpp
void dfs(int now,int dis)
{
    if(l[now]==r[now])
    {
        ans=min(ans,dis);
        return ;
    }
    if(l[now]!=0)
    {
        if(str[now]=='L')dfs(l[now],dis);
        else dfs(l[now],dis+1);
    }
    if(r[now]!=0)
    {
        if(str[now]=='R')dfs(r[now],dis);
        else dfs(r[now],dis+1);
    }
}
```

---

## 作者：Phartial (赞：0)

注意到 $\mathtt{U}$ 是完全没用的，因为路径必然是一条从根到叶子的路径，而从不会往上走。

考虑树形 dp，设 $f_i$ 表示从 $i$ 出发想走到一个以 $i$ 为根的子树的叶子上的最小代价。

则有转移方程：$f_i=\min(f_{l_i}+[s_i\ne\mathtt{L}],f_{r_i}+[s_i\ne\mathtt{R}])$。直接按此转移即可。

```cpp
#include <iostream>

using namespace std;

const int kN = 3e5 + 1;

int tt, n, l[kN], r[kN], f[kN];
string s;

void D(int x) {
  if (!x) {
    return;
  }
  if (!l[x] && !r[x]) {
    f[x] = 0;
    return;
  }
  D(l[x]), D(r[x]);
  f[x] = min(f[l[x]] + (s[x] != 'L'), f[r[x]] + (s[x] != 'R'));
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  for (cin >> tt; tt--;) {
    cin >> n >> s;
    s = "#" + s;
    for (int i = 1; i <= n; ++i) {
      cin >> l[i] >> r[i];
    }
    f[0] = 1e9;
    D(1);
    cout << f[1] << '\n';
  }
  return 0;
}
```

---

## 作者：technopolis_2085 (赞：0)

题意：

给你一个 $n$ 个点的树，其中每个节点上有一个字母，你需要按照字母来确定你的下一个节点。你初始时在根节点，然后允许你进行一些修改操作而更改节点的字母，问你最少要改几个才能走到其中一个叶子节点上。

$n ≤ 3 × 10^5$。

分析：

肯定是 dp。

令 $dp_i$ 表示当前在 $i$ 节点时，最少的操作次数。

然后根据 $s_i$ 来分类讨论：

若 $s_i = L$：则用 $dp_{ls_i}$ 和 $dp_{rs_i}+1$ 中的较小值来更新 $dp_i$，因为走到左儿子不需要操作，走到右儿子需要将操作数量加 $1$，即修改 $s_i$ 为 $R$。

若 $s_i = R$ 时同理，用 $dp_{ls_i}+1$ 和 $dp_{rs_i}$ 来更新 $dp_i$。

若 $s_i = U$：则分类讨论 $s_{fa_i}$。（此时假设 $i$ 为 $fa_i$ 的左节点。右节点同理。）

- 若 $s_{fa_i}$ 等于 $L$：则会在这两个节点之间更改一个。所以直接更改 $s_i$。

- 若 $s_{fa_i}$ 等于 $R$：则在计算 $dp_{fa_i}$ 时，直接走到右节点即可，不需要走到左节点，否则需要更改 $s_i$。

- 若 $s_{fa_i}$ 等于 $U$：和当前情况一样。

所以，直接修改 $s_i$ 不会劣，则要在 $dp_{ls_i}+1$ 和 $dp_{rs_i}+1$ 中取较小值。

然后从下往上递归求解即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=3e5+10;
int ch[maxn][2];
int n;
char s[maxn];
int dp[maxn];

int dfs(int u){
	if (ch[u][0]==0&&ch[u][1]==0) return dp[u]=0;//叶子节点
	
  //记得判断是否有左/右儿子
	if (s[u]=='L'){
		if (ch[u][0]) dp[u]=min(dp[u],dfs(ch[u][0]));
		if (ch[u][1]) dp[u]=min(dp[u],1+dfs(ch[u][1]));
	}
	
	if (s[u]=='R'){
		if (ch[u][0]) dp[u]=min(dp[u],1+dfs(ch[u][0]));
		if (ch[u][1]) dp[u]=min(dp[u],dfs(ch[u][1]));
	}
	
	if (s[u]=='U'){
		if (ch[u][0]) dp[u]=min(dp[u],1+dfs(ch[u][0]));
		if (ch[u][1]) dp[u]=min(dp[u],1+dfs(ch[u][1]));
	}
	
	return dp[u];
}

int main(){
	int T;
	scanf("%d",&T);
	
	while (T--){
		scanf("%d",&n);
		scanf("%s",s+1);
		
		for (int i=1;i<=n;i++){
			scanf("%d%d",&ch[i][0],&ch[i][1]);
			dp[i]=1e9+7;
		}
		dfs(1);
		printf("%d\n",dp[1]);
	}
	return 0;
}
```


---

## 作者：AlexandreLea (赞：0)

## 题目大意

有一棵二叉树，由 $n$ 个节点构成。每个节点上写着 `ULR` 三个字母之一。旅行从根节点开始，节点如果写着 `U`，就走到父节点；如果写着 `L`，就走到左子节点；如果写着 `R` 就走到右子节点。（当然如果不存在就不走）。现在，你需要给出，最少修正多少顶点的字母，能够从根节点开始进行旅行并在任意的叶子节点结束。

## 题目思路

这是一道标准的树形 dp 板子。

首先，我们需要规定状态：$f_u$ 代表 $u$ 需要修正子树内的多少个点可以达到叶子节点。

初始值是很明显的：$f_{\text{leaf}}=0$.

而后，考虑合并子树。

由于 `U` 和 父亲的某个字母一定会让你在这两个节点反复横跳，因此我们需要避免它，就一定需要一次更改。

而 `L` 或者 `R` 中只要我们当前到达子树的修改次数足够小，我们就没有理由去修改要到达的点。否则的话，我们就得修改了。

因而，我们给出动态转移方程式：

$$f_u=\begin{cases}0&u\text{ is leaf}\\\infty&u\text{ is not exist}\\1+\min\{f_{ch_{u,0}},f_{ch_{u,1}}\}&s_u=\texttt U\\\min\{1+f_{ch_{u,0}},f_{ch_{u,1}}\}&s_u=\texttt R\\\min\{f_{ch_{u,0}},1+f_{ch_{u,1}}\}&s_u=\texttt L\end{cases}$$

十分简单。赛时代码如下。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+10;
int n,ch[N][2];
char lru[N];
int dp(int u){
    if(u==0) return 0x3f3f3f3f3f3f3f3f;
    if(ch[u][0]==0&&ch[u][1]==0) return 0;
    int dlch=dp(ch[u][0]),drch=dp(ch[u][1]);
    if(lru[u]=='U') return 1+min(dlch,drch);
    else if(lru[u]=='L') return min(dlch,1+drch);
    else if(lru[u]=='R') return min(1+dlch,drch);
    return -1;
}
void solve(){
    cin>>n;
    for(int i=1;i<=n;++i) cin>>lru[i];
    for(int i=1;i<=n;++i) cin>>ch[i][0]>>ch[i][1];
    cout<<dp(1)<<endl;
}
signed main(){
    int t;
    cin>>t;
    while(t--) solve();
    return 0;
}
```

**EOF**

---

## 作者：abensyl (赞：0)

原题：[C. Anji's Binary Tree](https://codeforces.com/contest/1900/problem/C)。

树形 dp 板子题，~~我蒟蒻 $7$ 分钟切掉了~~。

## 简要题意

从一棵以 $1$ 号节点为根节点的二叉树上往下走，每个节点都有一个字母，分别为 `U`、`L` 或 `R`，表示在这个节点的前进方向，`U` 表示移向父节点，`L` 表示移向左儿子，`R` 表示移向右儿子，如果该方向上有节点，那么就会移动向这个方向，否则就会停止。

要求改变最少的节点的方向，使得按照新的方向序列，路径可以经过任意一个叶节点（既没有左儿子也没有右儿子的节点），输出最少需要改变方向的节点数。

## 思路

从根节点到叶子的最小花费，可以考虑反着从叶节点往上进行 dp。

首先，我们要明确，当出现 `U` 的时候，实际上说明我们这一步是废掉的，因为一个节点肯定是又他的父亲走下来的，如果出现 `U` 说明又走回了他的父亲，这样循环往复是不会改变 dp 值的，而且我们这样一直循环着走也不可能到达叶节点。

那么，我们设置状态 $dp_i$ 表示从任意一个叶节点到达节点 $i$ 所需要的最小代价，即最少改变方向的节点数。

显然地，初始状态应为所有叶节点的 dp 值均为 $0$，其余的非叶节点 dp 值为 INF。

然后在深度优先搜索回溯的过程中进行转移，如果一个点的方向是 `L`，那么他就可以在不进行改变的情况下来到他的左儿子，所以它的 dp 值可以用左儿子的 dp 值直接更新（前提是它有左儿子），为 `R` 的情况同理，否则，需要用左儿子的 dp 值加一和右儿子的 dp 值加一进行更新。

最终输出的答案，就是 $1$ 号根节点的 dp 值。

[我的 AC 代码](https://codeforces.com/contest/1900/submission/234445286)。

---

## 作者：yuyc (赞：0)

### 题意
给定一颗二叉树，每个结点上有一个字符 `'U'`、`'L'`或`'R'`，字符含义如下：

-  `'U'`，走到当前结点的父节点，如不存在则不走。
-  `'L'`，走到当前结点的左儿子节点，如不存在则不走。
-  `'R'`，走到当前结点的右儿子节点，如不存在则不走。

约定根结点编号为 $1$，求从根结点出发，按照结点上的字符走，至少修改多少个结点上的字符可以**经过**一个叶子结点。

### 解析
我们可以从根节点开始，尝试每一条路径，也可以从每一个叶子结点开始，往根节点走，这里只分析从叶子结点开始走的方法。

从叶子结点开始走，必定是往父节点的方向走。我们可以判断叶子结点是其父结点的左儿子结点还是右儿子结点，从而判断是否需要修改其父结点上的字符，并递归的方式来统计需要修改的结点数量。

为了避免超时，我们还需要做一点优化，令 $step[i]$ 表示从根节点走到结点 $i$ 所需要修改的结点数量，这样当下一次走到结点 $i$ 时，就可以直接返回 $step[i]$，避免做无用的递归。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 300005;
struct node{
	int l = 0,r = 0,fa = 0;
	char dir = ' ';
}tree[N];
vector<int> leaf;
vector<int> step;
int func(int x){
	int res = 0;
	if(x == 1) return 0;
	if(step[x] != -1) return step[x];
	if(x == tree[tree[x].fa].l && tree[tree[x].fa].dir != 'L') res = 1;
	else if(x == tree[tree[x].fa].r && tree[tree[x].fa].dir != 'R') res = 1;
	return step[x] = res + func(tree[x].fa);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin>>T;
	while(T--){
		int n,ans = 1e9;
		cin>>n;
		step.clear();
		leaf.clear();
		step.resize(n + 5);
		for(int i=1;i<=n;i++){
			cin>>tree[i].dir;
		}
		for(int i=1;i<=n;i++){
			step[i] = -1;
			cin>>tree[i].l>>tree[i].r;
			tree[tree[i].l].fa = i,tree[tree[i].r].fa = i;
			if(!tree[i].l && !tree[i].r) leaf.push_back(i);
		}
		step[1] = 0;
		for(int i=0;i<leaf.size();i++){
			ans = min(ans,func(leaf[i]));
		}
		cout<<ans<<'\n';
	}	
	return 0;
}
```


---

