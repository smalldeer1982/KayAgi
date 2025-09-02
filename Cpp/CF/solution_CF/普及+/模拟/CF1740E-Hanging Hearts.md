# Hanging Hearts

## 题目描述

Pak Chanek has $ n $ blank heart-shaped cards. Card $ 1 $ is attached directly to the wall while each of the other cards is hanging onto exactly one other card by a piece of string. Specifically, card $ i $ ( $ i > 1 $ ) is hanging onto card $ p_i $ ( $ p_i < i $ ).

In the very beginning, Pak Chanek must write one integer number on each card. He does this by choosing any permutation $ a $ of $ [1, 2, \dots, n] $ . Then, the number written on card $ i $ is $ a_i $ .

After that, Pak Chanek must do the following operation $ n $ times while maintaining a sequence $ s $ (which is initially empty):

1. Choose a card $ x $ such that no other cards are hanging onto it.
2. Append the number written on card $ x $ to the end of $ s $ .
3. If $ x \neq 1 $ and the number on card $ p_x $ is larger than the number on card $ x $ , replace the number on card $ p_x $ with the number on card $ x $ .
4. Remove card $ x $ .

After that, Pak Chanek will have a sequence $ s $ with $ n $ elements. What is the maximum length of the longest non-decreasing subsequence $ ^\dagger $ of $ s $ at the end if Pak Chanek does all the steps optimally?

 $ ^\dagger $ A sequence $ b $ is a subsequence of a sequence $ c $ if $ b $ can be obtained from $ c $ by deletion of several (possibly, zero or all) elements. For example, $ [3,1] $ is a subsequence of $ [3,2,1] $ , $ [4,3,1] $ and $ [3,1] $ , but not $ [1,3,3,7] $ and $ [3,10,4] $ .

## 说明/提示

The following is the structure of the cards in the first example.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1740E/c21952ecb25b67a195586146f9d068b9b7641f10.png)

Pak Chanek can choose the permutation $ a = [1, 5, 4, 3, 2, 6] $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1740E/4127ff7f189221d666c08b1ef78406f618501ae1.png)

Let $ w_i $ be the number written on card $ i $ . Initially, $ w_i = a_i $ . Pak Chanek can do the following operations in order:

1. Select card $ 5 $ . Append $ w_5 = 2 $ to the end of $ s $ . As $ w_4 > w_5 $ , the value of $ w_4 $ becomes $ 2 $ . Remove card $ 5 $ . After this operation, $ s = [2] $ .
2. Select card $ 6 $ . Append $ w_6 = 6 $ to the end of $ s $ . As $ w_2 \leq w_6 $ , the value of $ w_2 $ is left unchanged. Remove card $ 6 $ . After this operation, $ s = [2, 6] $ .
3. Select card $ 4 $ . Append $ w_4 = 2 $ to the end of $ s $ . As $ w_1 \leq w_4 $ , the value of $ w_1 $ is left unchanged. Remove card $ 4 $ . After this operation, $ s = [2, 6, 2] $ .
4. Select card $ 3 $ . Append $ w_3 = 4 $ to the end of $ s $ . As $ w_2 > w_3 $ , the value of $ w_2 $ becomes $ 4 $ . Remove card $ 3 $ . After this operation, $ s = [2, 6, 2, 4] $ .
5. Select card $ 2 $ . Append $ w_2 = 4 $ to the end of $ s $ . As $ w_1 \leq w_2 $ , the value of $ w_1 $ is left unchanged. Remove card $ 2 $ . After this operation, $ s = [2, 6, 2, 4, 4] $ .
6. Select card $ 1 $ . Append $ w_1 = 1 $ to the end of $ s $ . Remove card $ 1 $ . After this operation, $ s = [2, 6, 2, 4, 4, 1] $ .

One of the longest non-decreasing subsequences of $ s = [2, 6, 2, 4, 4, 1] $ is $ [2, 2, 4, 4] $ . Thus, the length of the longest non-decreasing subsequence of $ s $ is $ 4 $ . It can be proven that this is indeed the maximum possible length.

## 样例 #1

### 输入

```
6
1 2 1 4 2```

### 输出

```
4```

## 样例 #2

### 输入

```
2
1```

### 输出

```
2```

# 题解

## 作者：lenlen (赞：16)

### Problem

题目大意：给定一棵树，$1$ 为根，你可以自由赋给每个点一个权值，但权值必须是 $[1,n]$ 的一个排列，然后每次你选择删除一个叶子节点，将其权值加入序列 $s$ 中，同时，若该节点不为 1 且其父亲节点的权值大于自己的权值，那么交换两个点的权值（**先放权值，再交换**），求 $s$ 的最长不下降子序列的长度。

数据范围： $n \leq 10^5$。

### Solution


首先可以肯定的是，以一个点为根的子树的最长不下降子序列肯定大于等于这个点子树中以它为起点的最长链，显然我们可以将这个子树最长链以外的点权值中的最小值大于最长链的权值最大值，且最长链由下到上递增，那么由于子序列不需要连续，所以这个子树的最长不下降子序列的长度必然大于等于最长链的长度。

同时我们可以发现，若一个点有多个儿子节点，那么我们显然可以依次对这些儿子节点的子树赋值，这样我们先将第 $1$ 个子树贡献增加后，因为我们的依次赋值，必然存在第一个子树的最大值小于第二个子树的最小值，所以子树之间计算互不影响，而显然子树贡献可以相加。

所以我们只用考虑当一个点有多个儿子节点时，应该如何求以该点为根的树的最长不下降子序列的长度，然后 dp 即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/k3o7fyp5.png)

观察上图我们可知，因为父亲节点必须要在儿子节点都操作之后才能计算，而显然操作完 $2,3$ 节点之后 $1$ 的权值会被更改成 $\min(x,y,z)$，显然， $\min(x,y,z) < \max(x,y)$，所以当儿子节点**都**记入贡献时，父亲节点必然无法计入贡献。

所以递推式就很显然了，一个点最长不下降子序列的长度为它的最长链和其儿子节点最长不下降子序列的长度之和中的最大值。

### Code

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+7232;
int n,x;
int dp[N],ans,f[N];
struct hl{
    int v,nxt;
}e[N<<1];
int h[N],cnt;
void add(int u,int v)
{
    e[++cnt].v=v;e[cnt].nxt=h[u];h[u]=cnt;
}
void dfs(int x)
{
    for(int i=h[x];i;i=e[i].nxt)
    {
        dfs(e[i].v);
        f[x]=max(f[x],f[e[i].v]+1);//f求链长
        dp[x]+=dp[e[i].v];//dp先求儿子节点长度的最大值
    }
    if(!f[x]) f[x]=1;//叶子节点自身大小为1
    dp[x]=max(dp[x],f[x]);
}
int main()
{
    scanf("%d",&n);
    for(int i=2;i<=n;i++) scanf("%d",&x),add(x,i);
    dfs(1);
    printf("%d\n",dp[1]);
}
```


---

## 作者：Gao_yc (赞：2)

本蒟蒻第一道赛时做出的 Div2 E题，写篇题解纪念下（

[题目传送门](https://www.luogu.com.cn/problem/CF1740E)

题意简述：给你一个树的结构，让你给这个树赋点权（$1 \sim n$ 的排列）。然后每次删掉一个没有儿子（或儿子都被删去）的点，将这个点的点权加入答案序列中；如果该点父亲的点权小于该点的点权，则用该点的点权更新父亲点权。

使得答案序列 的 最长非严格单调递增子序列 最长，输出这个长度。

# Solution：

显然每个点被加入到答案序列中时，这个点权是其子树内点权的最小值。

手玩一下样例，可以推测 ~~（连蒙带猜）~~，答案最优时一定是把一个子树删完之后再删其他的子树，且先删权值小的点。

### 赛时假做法：

本人在赛时猜了一个这样的结论：答案为儿子数不大于 $1$ 的点数，交上去，WA on #6 。虽然没有多测，但是能过前5个点说明~~数据很水~~这个做法可能很接近正解。

为什么儿子数大于 $1$ 的点就不能在最长非严格单调递增子序列内？因为先删掉权值小的儿子，并将其加入最长子序列，再删权值大的儿子，也将其加入了最长子序列 **（下文中定义其为“被选”）**，那么父亲就不能再加被选了。

但是，同样的，如此操作后，父亲节点的父亲也不能**被选**了，因此这个做法不符合题意。

hack 数据：

![](https://cdn.luogu.com.cn/upload/image_hosting/1wsgnwki.png)

**数字不是点权，只是在表示一个结构。**

如图，如果按照这个假做法，应选除了第 $3$ 个点外的所有点，但是我们发现，如果选了 $4$、$5$、$6$、$7$ 后，$1$、$2$ 就不能**被选**了。

------------

### 由假做法启发得到的正解

上文提到，如果一个点的两个儿子都**被选**，那么这个点就不能够再被选择了。

相对的，如果一个点**被选**，那么它的儿子，只有一个能**被选**。

而我们要选择尽量多的点。

这不就是直接树上 dp 吗？？？！！！

$f_{i,1/0}$  表示在点 $i$ 的子树中，点 $i$ 选/不选 的最大答案。

初值：$f_{x,1}=1$。

转移如下。

$$f_{x,0}=\sum_{y \in son(x)} \max(f_{y,0},f_{y,1})$$

$$f_{x,1}=\max_{y \in son(x)}(f_{y,1}+1)$$

做完了……

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,f[N][2];
int tot,head[N],ver[N],nxt[N];
void add(int u,int v){ver[++tot]=v,nxt[tot]=head[u],head[u]=tot;}
void dfs(int x){
	f[x][1]=1;
	for(int i=head[x],y;i;i=nxt[i]){
		y=ver[i];
		dfs(y);
		f[x][1]=max(f[x][1],f[y][1]+1);
		f[x][0]+=max(f[y][1],f[y][0]);
	}
}
int main()
{
   scanf("%d",&n);
   for(int i=2,p;i<=n;++i) scanf("%d",&p),add(p,i);
   dfs(1);
   printf("%d\n",max(f[1][0],f[1][1]));
    return 0;
}
```


---

## 作者：Daidly (赞：1)

考虑以 $x$ 为根子树中的最小值的位置 $z$，它与 $x$ 之间能组成长度为路径上点个数的不降子序列，而这条链上的其他点的点权都会被最小值掩盖。所以，$z$ 的最优位置一定是在最长链的底端，或是样例 $1$ 所表现的在 $x$ 上。

若最小值即为根节点，则根节点一定不会对子树内不降子序列长度做贡献。答案则由它的儿子子树推出。

设 $f[x][0/1]$ 为在以 $x$ 为根的子树内，$x$ 上的数是否是最小值。

$$
f[x][0]=\max_{y\in son(x)}(f[y][1])
$$
$$
f[x][1]=\sum_{y\in son(x)}\max(f[y][0],f[y][1])
$$

对于叶子节点 $f[x][0]=1$ 虽然与定义有些矛盾，但是转移没问题。当然 $f[x][0]$ 也可以理解为最长链长度加 $1$，就没问题了。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}

void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int N=1e5+5;
int n,ans,len[N],f[N][2];
vector<int>e[N];

void dfs(int x,int fa){
	f[x][0]=1;
	for(auto y:e[x]){
		if(y==fa)continue;
		dfs(y,x);
		f[x][0]=max(f[x][0],f[y][0]+1);
		f[x][1]+=max(f[y][0],f[y][1]);
	}
}

signed main(){
	n=read();
	for(int i=2;i<=n;++i){
		int x=read();
		e[x].push_back(i);
		e[i].push_back(x);
	}
	dfs(1,0);
	print(max(f[1][0],f[1][1]));
	return 0;
}
```

---

## 作者：RuntimeErr (赞：1)

给你一棵树，树有点权。你需要维护一个序列，每次选择一个叶子节点删去，加到序列里，并将父亲的权值与其取 $\min$。你可以安排每个点的权值（是 $1\sim n$ 的排列），问最终序列的**最长不下降子序列**的长度最大为多少。

我们可以设 $f_u$ 表示以 $u$ 为根的子树构造出的答案。

如果子序列不以 $u$ 结尾，此时其子节点都是独立的，全部加起来就可以了。

如果以 $u$ 结尾，考虑怎样安排点权是最优的，由于每次都要和父亲取 $\min$，且求的是最长**不下降**子序列，则我们给深度**越深**的结点安排**越小**的权值就行了。因为这样，一个结点 $u$ 只会被其子树内最深的结点所影响（因为其点权最小），如果选择的子序列以 $u$ 结尾，长度也是最优的。

综上，有 $f_u=\max(\sum f_v,\max (dep_v+1))$。

```cpp
#define pb push_back
const int N=1e5+10;

int n;
vector<int>e[N];
int f[N],maxdep[N];

void dfs(int u){
    f[u]=0,maxdep[u]=1;
    for(int v:e[u]){ dfs(v);
        maxdep[u]=max(maxdep[u],maxdep[v]+1),
        f[u]+=f[v];
    }f[u]=max(maxdep[u],f[u]);
}
int main(){
    read(n);
    for(int i=2,p;i<=n;++i)read(p),e[p].pb(i);
    dfs(1);printf("%d\n",f[1]);
    return 0;
}
```

---

## 作者：5ab_juruo (赞：0)

看了一眼题解好像没有非递归的写法，介绍一下。

题意等价于，每个点有一个初始权值，最终权值是每个点子树内权值的 $\min$。求所有后序遍历对应的权值序列中最长的不降子序列的长度。

对于每个节点所在的子树有两种情况：

1. 包括了根节点，此时最长的不降子序列中都是子树内的最小值，长度即为最小值对应节点到根路径上的节点个数。把最小值放到子树中最深的点即可取到最大值。
2. 不包括根节点，显然可以通过调整初始权值使得：第一棵子树内的权值都小于第二棵，第二棵内的都小于第三棵，以此类推。这样答案是所有子树内答案的和。

对这两种情况取一个 $\max$，做树形 dp 即可。

注意到这道题的输入很有特点，不仅给的是每个节点的父亲，而且保证了 $p_i<i$。所以 $1\sim n$ 就是这棵树的一个 bfs 序。求深度可以直接正着遍历，求答案反着对父亲取 $\max$，求和即可。

代码非常简单：

```cpp
/* name: 1740E
 * author: 5ab
 * created at: 2022-11-06
 */
#include <iostream>
using namespace std;

typedef long long ll;
const int max_n = 100000;

int fa[max_n], dep[max_n], mxdep[max_n], ans[max_n];

inline void chmax(int& _a, int _b) { if (_a < _b) _a = _b; }
signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n;
	
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		cin >> fa[i];
		dep[i] = dep[--fa[i]] + 1;
	}
	
	fa[0] = -1;
	for (int i = n - 1; i >= 0; i--)
	{
		chmax(mxdep[i], dep[i]);
		chmax(ans[i], mxdep[i] - dep[i] + 1);
		if (fa[i] != -1)
		{
			ans[fa[i]] += ans[i];
			chmax(mxdep[fa[i]], mxdep[i]);
		}
	}
	
	cout << ans[0] << endl;
	
	return 0;
}
// started coding at: 11-06 10:23:25
// finished debugging at: 11-06 10:28:10
```

---

