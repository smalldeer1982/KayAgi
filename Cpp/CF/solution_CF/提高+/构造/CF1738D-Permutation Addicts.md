# Permutation Addicts

## 题目描述

Given a permutation $ a_1, a_2, \dots, a_n $ of integers from $ 1 $ to $ n $ , and a threshold $ k $ with $ 0 \leq k \leq n $ , you compute a sequence $ b_1, b_2, \dots, b_n $ as follows.

For every $ 1 \leq i \leq n $ in increasing order, let $ x = a_i $ .

- If $ x \leq k $ , set $ b_{x} $ to the last element $ a_j $ ( $ 1 \leq j < i $ ) that $ a_j > k $ . If no such element $ a_j $ exists, set $ b_{x} = n+1 $ .
- If $ x > k $ , set $ b_{x} $ to the last element $ a_j $ ( $ 1 \leq j < i $ ) that $ a_j \leq k $ . If no such element $ a_j $ exists, set $ b_{x} = 0 $ .

Unfortunately, after the sequence $ b_1, b_2, \dots, b_n $ has been completely computed, the permutation $ a_1, a_2, \dots, a_n $ and the threshold $ k $ are discarded.

Now you only have the sequence $ b_1, b_2, \dots, b_n $ . Your task is to find any possible permutation $ a_1, a_2, \dots, a_n $ and threshold $ k $ that produce the sequence $ b_1, b_2, \dots, b_n $ . It is guaranteed that there exists at least one pair of permutation $ a_1, a_2, \dots, a_n $ and threshold $ k $ that produce the sequence $ b_1, b_2, \dots, b_n $ .

A permutation of integers from $ 1 $ to $ n $ is a sequence of length $ n $ which contains all integers from $ 1 $ to $ n $ exactly once.

## 说明/提示

For the first test case, permutation $ a = [1,3,2,4] $ and threshold $ k = 2 $ will produce sequence $ b $ as follows.

- When $ i = 1 $ , $ x = a_i = 1 \leq k $ , there is no $ a_j $ ( $ 1 \leq j < i $ ) that $ a_j > k $ . Therefore, $ b_1 = n + 1 = 5 $ .
- When $ i = 2 $ , $ x = a_i = 3 > k $ , the last element $ a_j $ that $ a_j \leq k $ is $ a_1 $ . Therefore, $ b_3 = a_1 = 1 $ .
- When $ i = 3 $ , $ x = a_i = 2 \leq k $ , the last element $ a_j $ that $ a_j > k $ is $ a_2 $ . Therefore, $ b_2 = a_2 = 3 $ .
- When $ i = 4 $ , $ x = a_i = 4 > k $ , the last element $ a_j $ that $ a_j \leq k $ is $ a_3 $ . Therefore, $ b_4 = a_3 = 2 $ .

 Finally, we obtain sequence $ b = [5,3,1,2] $ . For the second test case, permutation $ a = [1,2,3,4,5,6] $ and threshold $ k = 3 $ will produce sequence $ b $ as follows.

- When $ i = 1, 2, 3 $ , $ a_i \leq k $ , there is no $ a_j $ ( $ 1 \leq j < i $ ) that $ a_j > k $ . Therefore, $ b_1 = b_2 = b_3 = n + 1 = 7 $ .
- When $ i = 4, 5, 6 $ , $ a_i > k $ , the last element $ a_j $ that $ a_j \leq k $ is $ a_3 $ . Therefore, $ b_4 = b_5 = b_6 = a_3 = 3 $ .

 Finally, we obtain sequence $ b = [7,7,7,3,3,3] $ . For the third test case, permutation $ a = [6,5,4,3,2,1] $ and threshold $ k = 3 $ will produce sequence $ b $ as follows.

- When $ i = 1, 2, 3 $ , $ a_i > k $ , there is no $ a_j $ ( $ 1 \leq j < i $ ) that $ a_j \leq k $ . Therefore, $ b_4 = b_5 = b_6 = 0 $ .
- When $ i = 4, 5, 6 $ , $ a_i \leq k $ , the last element $ a_j $ that $ a_j > k $ is $ a_3 $ . Therefore, $ b_1 = b_2 = b_3 = a_3 = 4 $ .

 Finally, we obtain sequence $ b = [4,4,4,0,0,0] $ .

## 样例 #1

### 输入

```
3
4
5 3 1 2
6
7 7 7 3 3 3
6
4 4 4 0 0 0```

### 输出

```
2
1 3 2 4
3
1 2 3 4 5 6
3
6 5 4 3 2 1```

# 题解

## 作者：yingkeqian9217 (赞：13)

# Foreword

本题解适合初学者使用，大佬们不喜勿喷~ QwQ

# Problem

有一个 $n$ 个数的**排列** $a$ 和一个数 $k (0 \le k \le n)$，可以计算出一个 $n$ 个数的序列 $b$ ，规则如下：

- 当 $a_i \le k$ 时，若存在 $a_j > k (1 \le j < i)$ 且 $i - j$ **最小**，则 $b_{a_i} = a_j$，**否则** $b_{a_i} = n + 1$；
- 当 $a_i > k$ 时，若存在 $a_j \le k (1 \le j < i)$ 且 $i - j$ **最小**，则 $b_{a_i} = a_j$，**否则** $b_{a_i} = 0$。

目前你知道 $b$ 与 $n$，请求出 **任意一种** $a$ 及对应的 $k$。

# Solution

### Part.1

简单来说，题目中的两个操作就是求 $a_i$ 之前**第一个** $> k$ （$\le k$）的数，然后给 $b_{a_i}$ 赋上这个值，没有的话分别**特殊处理**。

而我们知道的只有 $n$ 与 $b$，希望求得 $k$ 和 $a$。

------------

### Part.2

考虑 $b$ 数组的特点：若有 $b_i>k$ 那么说明 $i\le k$; 若有 $b_i \le k$ 那么说明 $i > k$。于是我们很自然地得到 $k$ 的性质：

$k\in [\min(i,b_i),\max(i,b_i)+1]\ \ , i\in[1,n]$，我们**限制边界**即可，证明的话楼顶大佬已经给出了。

------------

### Part.3

那么，接下来的 $a$ 数组怎么求呢？~~这时候我们就需要看一眼CF的算法标签。~~

因为这里 $b_i$ 算的是 $i$ **前面**的第一个满足条件的数，以第一个样例为例，我们可以画一个图。

![](https://cdn.luogu.com.cn/upload/image_hosting/697rue1w.png)

没错，我们将 $b_i$ 指向 $b_{b_i}$ ——换句话说，是将 $i$ 指向 $b_i$，表示 $i$ 是由 $b_i$ 得来的，即题面中的 $a_i$ 与 $a_j$，因为 $j<i$，所以在 $a$ 数组中，$b_i$ 在 $i$ **之前**。

于是我们就得到了 $a$ 中一些数对的大小关系，我们直接从 $n+1$（即 5）开始沿着箭头遍历输出即可。我们可以发现这可以被拉成**一条链**，为了方便，接下来的图中所有箭头将会**逆过来**。

![](https://cdn.luogu.com.cn/upload/image_hosting/j8r71k0h.png)

------------

### Part.4

当我们想要在第二个样例上故技重施时，我们会发现无法再简单地以从 $n+1$ 点开始顺序遍历了，因为我们将它拉开后，会发现它成为了一个 DAG，更准确的说，是一棵**树**。

![](https://cdn.luogu.com.cn/upload/image_hosting/ar9pw4ue.png)

**注**：这里我们虽然使用 $b_i$ 作为节点，但实际编写时，使用 $i$ 作节点对输出更加方便，其实本质上都一样。

那么，我们应该按怎样的顺序遍历才能使输出如图所示呢？

分析条件，当前我们唯一没有用到的条件就是“且 $i - j$ 最小”了（此处的 $i,j$ 与后文中的没有关系），既然已经保证 $b_i$ 关于 $i$ 满足条件，那么我们只要保证 $b_i$ 和 $i$ 之间没有同样满足条件的即可。

猜想有一种遍历方式可以正确遍历，我们不妨先考虑 DFS（BFS 也可以）。那么输出序列中，父节点 $b_i$ 到子节点 $i$ 之间的就是在 $i$ 之前输出的它的兄弟节点。显然兄弟节点本身不会影响答案，但它们的儿子有可能影响。所以我们要在访问有儿子的节点之前访问没有儿子的——也就是叶子节点。

当然这是在父亲节点最多只有一个有儿子的子节点的前提下，具体的证明留给读者。

# Code
```cpp
#include<bits/stdc++.h>
#define maxn 290001
using namespace std;
int T,n,rt,kl,kr,k,a[maxn],b[maxn];
vector<int>son[maxn];//记录儿子
void dfs(int x){
	if(x&&x!=n+1) printf("%d ",x);//根节点不用输出
	for(int i:son[x])
	 if(son[i].empty())
	  printf("%d ",i);//优先输出叶子，注意循环不能合并
	for(int i:son[x])
	 if(!son[i].empty())
	  dfs(i);
}
void solve(){
	scanf("%d",&n);
	kl=0,kr=n;//维护k的边界
	for(int i=0;i<=n+1;i++) son[i].clear();//清空
	for(int i=1;i<=n;i++){
		scanf("%d",&b[i]);
		if(!b[i]||b[i]==n+1) rt=b[i];//记录根
		son[b[i]].push_back(i);
		kl=max(kl,min(i,b[i]));//相当于交集，不要写反
		kr=min(kr,max(i,b[i])+1);
	}
	printf("%d\n",kl);
	dfs(rt);
	printf("\n");
}
signed main(){
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

# P.S.

有问题私信作者，或者在评论区指出。

画图不易，给个赞罢！

---

## 作者：Alex_Wei (赞：8)

若 $b_i > i$，说明 $i\leq k < b_i$，否则说明 $b_i \leq k < i$。据此可以确定唯一的 $k$。

证明：若我们得到 $k' < k$，考虑 $b_{k' + 1}$，因为 $k' + 1 \leq k$，所以它一定大于 $k$，与 $k'\in [k' + 1, b_{k' + 1} - 1]$ 矛盾。对于 $k' > k$ 同理。

从 $b_x$ 向 $x$ 连边。这些边形成一棵以 $0$ 或 $n + 1$ 为根的树（不可能成环，因为 $b_x$ 在 $a$ 中的下标小于 $x$ 在 $a$ 中的下标），取决于 $b_1$ 是否不大于 $k$。令点 $x$ 的颜色 $c_x$ 为 $[x \leq k]$，则 $b_x\to x$ 的限制形如排列 $b_x$ 和 $x$ 之间不能有其它颜色和 $b_x$ 相同的数 $v$，否则与 $b_x$ 的定义矛盾。又因为 $b_x$ 和 $x$ 的颜色不同，所以假设点 $u$ 有若干后继 $v_1, v_2, \cdots, v_k$，则这些数恰为从 $u$ 到排列中下一个与 $u$ 颜色相同的点之间的所有数。因为保证有解，所以它们当中至少有 $k - 1$ 个数没有后继。任取 $k - 1$ 个没有后继的数排在 $u$ 后面，将剩下一个数排在它们之后，然后类似 $u$ 处理这个数直到它没有后继。

时间复杂度 $\mathcal{O}(n)$。[代码](https://codeforces.com/contest/1738/submission/174184464)。

---

## 作者：sgl654321 (赞：3)

都想到构造出树的那一步了，还是没敢接着往下想。

## 题目大意
告诉你一个长度为 $n$ 的序列 $b$，让你构造一个长度为 $n$ 的排列 $a$ 和一个相应的数 $k(k\in[0,n])$，满足下列条件。

- 若 $a_i \le k$，则 $b_{a_i} = a_j$，其中 $a_j > k$，$j<i$ 且 $i - j$ 最小。若不存在，则 $b_{a_i} = n + 1$。

- 若 $a_i >k$，则 $b_{a_i} = a_j$，其中 $a_j \le k$，$j <i$ 且 $i - j$ 最小。若不存在，则 $b_{a_i} = 0$。

## 解题思路
多条件问题，我们考虑逐一击破。我们先从 $k$ 的值进行思考。
### 1. 寻找 $k$

- 对于 $x \le k$ 的 $x$，他们的 $b_x$ 一定是在 $[k + 1,n + 1]$ 中间的，所以 $b_x > x$。 
- 对于 $x > k$ 的 $x$，他们的 $b_x$ 一定是在 $[0,k]$ 中间的，所以 $b_x < x$。

所以我们扫一遍序列 $b$，前面一串 $b_i$ 都会大于 $i$，一直到 $x$ 这个位置。从位置 $x + 1$ 开始，$b_i$ 都变成小于 $i$ 了。而这个 $x$ 就等于 $k$。

### 2. 建立图论模型

求出 $k$ 之后，我们思考本题最为特殊的地方：$b_i = 0$ 和 $b_i = n +1$ 的情况。**下面证明，$0$ 和 $n + 1$ 有且只有一个在序列 $b$ 中出现**。

> 若 $a_1 \le k$ 那么所有大于 $k$ 的数的 $b_i$ 都不可能等于 $0$ 了，因为再不济，他还是有 $b_1$ 给他垫底。若 $a_1 >k$ 类似，所有小于等于 $k$ 的数，$b_i$ 都不可能等于 $n + 1$ 了。

进一步考虑还原序列 $a$。根据题意 $b_i$ 这个数肯定在 $a$ 中出现的位置，比 $i$ 的位置要前。也就是说，**如果从 $b_i$ 向 $i$ 连一条有向边，是不会出现环的**。

同时所有可能的 $b_i,i$ 共有 $n + 1$ 种，即 $[0,n]$ 或者 $[1,n+1]$。你连的边共有 $n$ 条。我们可以发现，这样我们将会得到一棵树！它的根节点，要么是 $n + 1$ 要么是 $0$，取决于 $a_1$。

### 3. 进一步发掘性质

本题还有一个重要条件，即 $i -j$ 最小。也就是说你要找到前面最近的，具有不同性质的数。

我们这棵从根到叶子的外向树，只能保证 $b_i$ 一定在 $i$ 的前面。那最近这个条件怎么办呢？

这个时候又要引入一个重要性质：**对于这个外向树上的每一个节点 $x$，设它的儿子集合为 $S_x$，$S_x$ 中只有一个是非叶子节点。**

为什么呢？如果 $S_x$ 中有两个非叶子，我们以下图为例： $n = 5,k = 2$。

![](https://cdn.luogu.com.cn/upload/image_hosting/3b5tn47v.png)

注意看 $1$ 这个点，$4$ 在 $1$ 的前面，这是显然的。$3$ 也在 $1$ 的前面，因为如果 $3$ 在 $1$ 后面，那么 $3$ 的父亲就不是 $0$ 了，就是 $1$ 了。**说明 $4$ 和 $3$ 都在 $1$ 前面，且 $4$ 更靠后。**

再注意看 $2$ 这个点，我们可以**推出 $3$ 和 $4$ 都在 $2$ 前面，且 $3$ 更靠后**。这不就自相矛盾了吗！题目又保证有解，说明此种情况不存在。

进行类比，就可以知道，$S_x$ 中不可能有大于 $1$ 个非叶子节点。

### 4. 遍历树求得答案
由 $3$ 中证明的性质，容易想到通过 dfs 遍历整棵树，设当前到了节点 $x$，输出 $x$。如果是叶子那就退出好了。

否则，我们先遍历其中是叶子的儿子节点，再遍历那一个非叶子儿子节点。

这样我们就可以保证，$b_i$ 既在 $i$ 的前面，又是最靠近 $i$ 的一个不同性质的数了。

## 参考代码

### 注意点
1. 多测清空一定要记得把 $0$ 和 $n + 1$ 也清空了。

### 代码

```cpp
#include<bits/stdc++.h>
#define maxn 100010
#define maxm 100010 
using namespace std;
typedef long long ll;
ll tt, n, b[maxn], flag, kk, poi[maxn], v[maxm], nex[maxm];
ll k, root, siz[maxn], nt[maxn];
void add_edge(ll x, ll y){
	kk++; v[kk] = y; nex[kk] = poi[x]; poi[x] = kk;
} 
void dfs1(ll x){
	ll save = poi[x]; siz[x] = 1;
	while(save){
		dfs1(v[save]); siz[x] += siz[v[save]];
		if(siz[v[save]] != 1) nt[x] = v[save];
		save = nex[save];
	}
}
void dfs2(ll x){
	if(x != root) cout << x << ' ';
	ll save = poi[x];
	while(save){
		if(v[save] != nt[x]) dfs2(v[save]);
		save = nex[save];
	}
	if(nt[x] != -1) dfs2(nt[x]);
} 
void solve(){
	cin >> n; flag = 0;
	for(int i = 0; i <= n + 1; i++) poi[i] = siz[i] = 0, nt[i] = -1;
	
	for(int i = 1; i <= kk; i++) v[i] = nex[i] = 0;
	kk = 0;
	
	for(int i = 1; i <= n; i++){
		cin >> b[i];
		if(b[i] == n + 1) flag = 1;
		add_edge(b[i], i);
	}
	k = 0;
	for(int i = 1; i <= n; i++){
		if(b[i] > i) k = i;
		else break;
	}	
	cout << k << endl;
	if(flag == 0) root = 0; else root = n + 1;
	dfs1(root);
	dfs2(root); cout << endl;
}
int main(){
	cin >> tt;
	while(tt--) solve();
	return 0;
}
```

---

## 作者：_masppy_ (赞：1)

### 题目链接：[Link](https://www.luogu.com.cn/problem/CF1738D)

&nbsp;

### 题目大意
有一个从 $1$ 到 $n$ 的全排列 $a$ 和一个基准数 $k$，通过以下规则转换得到了序列 $b$：
- 对于 $a_i \leq k$，若有 $j < i$ 且 $a_j > k$，则有 $b_{a_i}=a_j$，否则 $b_{a_i}=n+1$。
- 对于 $a_i > k$，若有 $j < i$ 且 $a_j \leq k$，则有 $b_{a_i}=a_j$，否则  $b_{a_i}=0$。

现给出序列 $b$ 和长度 $n$，求一个合法的序列 $a$ 和数 $k$。

&nbsp;

### 解题思路
首先确定 $k$ 的范围，发现对于 $b_i>i$，$b_i$一定由规则 $1$ 得到，于是得出    $i \leq k$，而对于 $b_i < i$，$b_i$ 一定由规则 $2$ 得到，于是得出 $b_i \leq k$，依照这种方法遍历整个 $b$ 序列后，便能够得到 $k$ 的最小值，把 $k$   赋为此值即可。

接下来求序列 $a$，发现对于 $b$ 序列中若干个值为 $x$ 的数，它们的下标在 $a$   中一定连续的出现在 $x$ 之后，而对于值为 $0$ 或 $n+1$ 的数，在序列 $a$ 中则一定出现在开头位置。于是可以从$b_i$ 向 $i$ 连一条边，然后先将所有值为 $0$   或 $n+1$ 且没有连边的数放在序列开头，然后将值为 $0$ 或 $n+1$ 且有出边的点放在后面，再把和这个点连边的点接在后面，并把有出边的点挪到这一组数的最后，之后重复这一系列操作即可。

代码如下：
```cpp
int main(){
	while(t--){
		for(int i=1;i<=n+1;i++){//清空
			edge[i].clear();
		}
		scanf("%d",&n);
		
		int l=0,r=n;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			l=max(l,min(a[i],i));//求出k的最小值
			edge[a[i]].push_back(i);//连边
		}
		
		printf("%d\n",l);
		for(int i=1;i<=n;i++){
			if(a[i]==0||a[i]==n+1){
				if(!edge[i].size()) printf("%d ",i);
				else q.push(i); //将有连边的点放在最后并入队
			}
		}
		
		while(!q.empty()){
			printf("%d ",q.front());//前一组数的最后一个
			int x=q.front();
			q.pop();
			int siz=edge[x].size();
			for(int i=0;i<siz;i++){
				int y=edge[x][i];
				if(!edge[y].size()) printf("%d ",y);
				else q.push(y);//有连边的点入队
			}
		}
		printf("\n");
	}
	return 0;
}

```
完结撒花 OvO


---

## 作者：LYY_yyyy (赞：0)

显然地，我们可以发现序列 $b$ 中要么有 $0$ 要么有 $n+1$。我们将 $a$ 映射成一个 $01$ 序列，大于 $k$ 的数映射为 $1$，小于等于 $k$ 的数映射为 $0$，于是 $a$ 就由若干 $01$ 连续段组成。我们可以发现 $b_i$ 相等的 $i$ 在 $a$ 中一定处在同一个连续段中，$b_i$ 等于 $a$ 中前一个连续段的最后一个数。考虑从 $0$ 或 $n+1$ 开始，在所有等于当前考虑的数的 $b_i$ 的 $i$ 中找到存在 $j$ 满足 $b_j=i$ 的数作为下一个考虑的数，并将这个 $i$ 放在这个连续段的末尾。同时判断这个连续段是 $0$ 还是 $1$ 来更新 $k$ 的上下界即可。 

时间复杂度 $Θ(n)$，代码有些冗杂但感觉挺直观的（）

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n;
int a[100010];
int ans[100010];
vector<int> s[100010];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>n;
		int minn=1e9,maxx=-1e9;
		for(int i=0;i<=n+1;i++) s[i].clear();
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			s[a[i]].push_back(i);
		}
		int tot=0;
		int now,ne;
		if(s[0].size())
		{
			for(auto i:s[0]) 
			{
				ans[++tot]=i,minn=min(minn,i);
				if(s[i].size()) ne=i;
			}
			for(int i=1;i<=tot;i++)
			{
				if(ans[i]==ne)
				{
					swap(ans[i],ans[tot]);
					break;
				}
			}
			now=0;
		}
		else
		{
			now=1;
			for(auto i:s[n+1])
			{
				ans[++tot]=i;
				maxx=max(maxx,i);
				if(s[i].size()) ne=i;
			}
			for(int i=1;i<=tot;i++)
			{
				if(ans[i]==ne)
				{
					swap(ans[i],ans[tot]);
					break;
				}
			}
		}
		while(tot<n)
		{
			int nee=-1,lasttot=tot;
			for(auto i:s[ne]){
				ans[++tot]=i;
				if(now) minn=min(minn,i);
				else maxx=max(maxx,i);
				if(s[i].size()) nee=i;
			}
			ne=nee;
			for(int i=lasttot+1;i<=tot;i++){
				if(ans[i]==ne)
				{
					swap(ans[i],ans[tot]);
					break;
				}
			}
			now^=1;
		}
		if(minn!=1e9) cout<<minn-1<<'\n';
		else cout<<maxx<<"\n";
		for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
		cout<<"\n";
	}
	return 0;
}

```


---

## 作者：XenonWZH (赞：0)

[更好的阅读体验请点这](https://xenonwzh.github.io/cf-1738d/)

# 题意描述

[Codeforces 链接](https://codeforces.com/contest/1738/problem/D)

有一个 $n$ 个数的排列 $a$ 和一个数 $k (0 \le k \le n)$，你计算出了一个有 $n$ 个数的序列 $b$，计算方法如下：

- 当 $a_i \le k$ 时，若存在 $a_j > k (1 \le j < i)$ 且 $i - j$ 最小，则 $b_{a_i} = a_j$，否则 $b_{a_i} = n + 1$；
- 当 $a_i > k$ 时，若存在 $a_j \le k (1 \le j < i)$ 且 $i - j$ 最小，则 $b_{a_i} = a_j$，否则 $b_{a_i} = 0$。

目前你知道 $b$ 与 $n$，请求出任意一种 $a$ 及对应的 $k$。

# 解题思路

分析可得对于 $i \le k$，满足 $b_i > i$；对于 $i > k$，满足 $b_i < i$。证明显然。这样我们可求出 $k$。

对于每个 $b_i$，若 $i \neq n + 1$ 且 $i \neq 0$，显然 $b_i$ 在 $i$ 的后面，若有 $m$ 个 $b_i = 0$ 或 $b_i = n + 1$，则这 $m$ 个数必定在前 $m$ 位，且 $b_i = 0$ 和 $b_i = n + 1$ 两者必定有且只有一者出现。于是我们可以直接建树，连边 $i \rightarrow b_i$，然后对 $0$ 或 $n + 1$ 进行 DFS 即可。对于一个节点 $u$，它的子节点中若有以节点 $v$ 为根的子树大于 $1$，就最后遍历 $v$ 即可。显然对于每个节点至多只有一个子节点为根的子树大小大于 $1$。

# 代码演示

```cpp
#include <cstdio>
#include <iostream>
#include <vector>

const int MAXN = 1e5;

struct Node {
    int size, p;
    Node(int p) : p(p) {}
};

int n;
std::pair<int, std::vector<int>> e[MAXN + 2];

int dfs1(int p) {
    e[p].first = 1;
    if (e[p].second.size() == 0) return 1;
    for (int each : e[p].second) e[p].first += dfs1(each);
    return e[p].first;
}

void dfs2(int p) {
    if (p != 0 && p != n + 1) printf("%d ", p);
    int max = 0;
    for (int each : e[p].second) max = std::max(max, e[each].first);
    for (int each : e[p].second) {
        if (e[each].first != max) {
            dfs2(each);
        }
    }
    for (int each : e[p].second) {
        if (e[each].first == max) {
            dfs2(each);
        }
    }
}

void solve() {
    static int b[MAXN + 1];

    scanf("%d", &n);

    int k = 0;
    bool flag = true;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &b[i]);
        if (b[i] > i) k = i;
        if (b[i] == 0) flag = false;
    }
    printf("%d\n", k);

    for (int i = 0; i <= n + 1; i++) e[i].second.clear();
    for (int i = 1; i <= n; i++) e[b[i]].second.push_back(i);

    if (flag) {
        dfs1(n + 1);
        dfs2(n + 1);
    } else {
        dfs1(0);
        dfs2(0);
    }
    putchar('\n');
}

int main() {
    int t;

    scanf("%d", &t);

    while (t--) solve();

    return 0;
}
```

---

