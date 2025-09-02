# Defender of Childhood Dreams

## 题目描述

Even if you just leave them be, they will fall to pieces all by themselves. So, someone has to protect them, right?

You find yourself playing with Teucer again in the city of Liyue. As you take the eccentric little kid around, you notice something interesting about the structure of the city.

Liyue can be represented as a directed graph containing $ n $ nodes. Nodes are labeled from $ 1 $ to $ n $ . There is a directed edge from node $ a $ to node $ b $ if and only if $ a < b $ .

A path between nodes $ a $ and $ b $ is defined as a sequence of edges such that you can start at $ a $ , travel along all of these edges in the corresponding direction, and end at $ b $ . The length of a path is defined by the number of edges. A rainbow path of length $ x $ is defined as a path in the graph such that there exists at least 2 distinct colors among the set of $ x $ edges.

Teucer's favorite number is $ k $ . You are curious about the following scenario: If you were to label each edge with a color, what is the minimum number of colors needed to ensure that all paths of length $ k $ or longer are rainbow paths?

Teucer wants to surprise his older brother with a map of Liyue. He also wants to know a valid coloring of edges that uses the minimum number of colors. Please help him with this task!

## 说明/提示

The corresponding construction for the first test case looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1583F/801e0382f5a18f576bb5e0cead518269b69fb25e.png) It is impossible to satisfy the constraints with less than $ 2 $ colors.The corresponding construction for the second test case looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1583F/e9f61e2ad637bf2a7f7bff1fd5146004ff52820b.png) One can show there exists no construction using less than $ 3 $ colors.

## 样例 #1

### 输入

```
5 3```

### 输出

```
2
1 2 2 2 2 2 2 1 1 1```

## 样例 #2

### 输入

```
5 2```

### 输出

```
3
3 2 2 1 2 2 1 3 1 1```

## 样例 #3

### 输入

```
8 7```

### 输出

```
2
2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1```

## 样例 #4

### 输入

```
3 2```

### 输出

```
2
1 2 2```

# 题解

## 作者：enucai (赞：14)

一篇来自蒟蒻的题解，不喜误喷，有误请私信。

~~考场上都没来得及看题，wtcl。~~


## 题目简述

有 $n$ 个点，对于每两个点 $i,j$ 满足 $i< j$，在 $i$ 与 $j$ 之间都会有一条连边。现在要对这 $\frac{n\times (n-1)}{2}$ 条边进行染色。要求对于每一条长度大于等于 $k$ 的路径，所有边的颜色种类至少要有两种。问至少要用几种颜色，并输出一种染色方案。

## 题目分析

是一道构造题，代码很好写，只要想清楚构造的方法。

首先，我们很容易发现（~~甚至可以不发现~~），只要保证每条长度为 $k$ 的路径满足条件，那么长度大于 $k$ 的所有路径都一定满足条件。证明随便想想，略。

我们先将 $1,2,3,\dots ,k$ 这些点之间的所有边都染上颜色 $1$ ，因为这 $k$ 个点之间的最长边的长度也没到 $k$ 。

同理，将 $k+1,k+2,k+3,\dots ,2k$ 之间的所有边都染上颜色 $1$ ，将 $2k+1,2k+2,2k+3,\dots ,3k$ 之间的所有边都染上颜色 $1$ ，以此类推，最后到 $k^2-k+1,k^2-k+2,k^2-k+3,\dots ,k^2$ 这些点之间的所有边都染上颜色 $1$，简单来说，就是现将 $n$ 以 $k$ 个元素为一组分组，组内全部边都染 $1$ 。

接下来，考虑将这 $n$ 个数按照 $k^2$ 个元素为一组再进行分组，属于同一组内的两个点间还没有染色的边都染上颜色 $2$，仔细想想，这要就能保证这 $k^2$ 个元素之间的所有长度等于 $k$ 的路径上的颜色种类数至少有两个了。如果想不明白，可以看下蒟蒻证明：

用反证法：假设有一条长度为 $k$ 的路径上的颜色种类只有 $1$ 种。

定义：一个 $k^2$ 个元素的分组叫做组，组内的每 $k$ 个元素组成的分组叫块。

- 如果都是颜色 $1$，那么一定在同一个块内。已经证明了不可以。

- 如果都是颜色 $2$，那么采用贪心：从第一个块中任意一个点出发，走颜色为 $2$ 的边，一定回到第二个块中，再走走走，到第 $k$ 个块（即组内最后一个块），整条路径的长度也只有 $k-1$，不可能到 $k$。

总上，假设不成立，故原名题得证。

证明了这点，接下来又是“以此类推”了。以 $k^3$ 个元素划分组，组内还未染色的边全部染成 $3$；再以 $k^4$ 个元素划分组，组内还未染色的边全部染成 $4$ ……

所以最后最少的颜色数量是 $\lceil \log_k n\rceil$。所有边的颜色上面都处理好了，直接输出即可。

### Talk is cheap, show me the code!

[Codeforces Status](https://codeforces.com/contest/1583/submission/132607093)

```cpp
int n=read(),k=read();
int ans=1,sum=k;
while(sum<n) ans++,sum*=k;//计算⌈logkN⌉
printf("%d\n",ans);
For(i,0,n-1){
    For(j,i+1,n-1){
        int x=i,y=j,d=0;
        while(x!=y) x/=k,y/=k,d++;//算每条边属于哪种跨度的
        printf("%d ",d);
    }
}
```

---

## 作者：Alex_Wei (赞：5)

> ### *1586F. [Defender of Childhood Dreams](https://codeforces.ml/contest/1586/problem/F)

神仙题。

---

一上来猛冲正解是不对的，先考虑 $k=2$ 怎么做：由于不能出现长度为 $2$ 的路径，所以我们只能将节点分成前后两半，然后这两部分之间跨块的节点对相互连边。然后呢？不难发现**对于两部分内部节点的连边处理变成了两个子问题**。由于颜色不能相同，因此子问题与父问题之间连边的颜色不能相同。为了使颜色最少，我们需要把这两部分尽量均分，每次递归减少一半的问题规模，故答案为 $\lceil\log_2n\rceil$。

想到 $k=2$ 怎么做，$k>2$ 就很显然了：将节点按顺序分为 $k$ 份且跨块的节点对连颜色相同的边，那么颜色相同路径长度最大值显然为 $k-1$，符合要求，故答案为 $\lceil \log_kn\rceil$。

怎么证明充分性呢？归纳万岁：$n=k^{0}=1$ 时，显然答案为 $c=0$。假设用 $c$ 种颜色最多能使有 $k^c$ 个节点的图满足题意，那么我们选 $k$ 个点集 $s_1,s_2,\cdots,s_k$，每个点集符合条件且最多用 $c$ 个颜色（因为若用了第 $c+1$ 种颜色，那么跨点集连边时就会出现长度为 $k$ 且颜色都为 $k+1$ 的路径，不符合题意），那么点集大小之和，即使用 $c+1$ 种颜色能够满足题意的图的大小 $\leq k\times k^c=k^{c+1}$。

时间复杂度 $\mathcal{O}\left(n^2+\dfrac{n^2}{k}+\dfrac{n^2}{k^2}+\cdots\right)=\mathcal{O}(n^2)$。

```cpp
const int N = 1e3 + 5;

int n, k, e[N][N];
int solve(int l, int r) {
	if(l == r) return 0;
	int cnt = 1, len = r - l + 1;
	if(len < k) {
		for(int i = l; i <= r; i++)
			for(int j = i + 1; j <= r; j++)
				e[i][j] = cnt;
		return cnt;
	}
	int p = len / k, rest = len % k;
	vint pos(k + 1, 0), col(n + 1, 0); // 这里开了大小为 n 的数组所以时间复杂度是 n ^ 2 log n, 精细实现即可 n ^ 2
	for(int i = 1; i <= k; i++)
		pos[i] = pos[i - 1] + p + (i <= rest);
	for(int i = 1; i <= k; i++)
		cnt = max(cnt, solve(l + pos[i - 1], l + pos[i] - 1) + 1);
	for(int i = 1; i <= k; i++)
		for(int j = pos[i - 1]; j < pos[i]; j++)
			col[l + j] = i;
	for(int i = l; i <= r; i++)
		for(int j = i + 1; j <= r; j++)
			if(col[i] != col[j])
				e[i][j] = cnt;
	return cnt;
}
int main(){
	cin >> n >> k, cout << solve(1, n) << endl;
	for(int i = 1; i <= n; i++)
		for(int j = i + 1; j <= n; j++)
			cout << e[i][j] << " ";
    return flush(), 0;
}
```

---

## 作者：phoenixzhan (赞：3)

相似题目：P9384

不一样的构造？

观察样例猜测答案为 $\left \lceil\log_k{n}\right \rceil$，构造 $i,j$ 间的边权为 $k$ 进制下 $i\operatorname{xor}j$ 的 $\operatorname{highbit}$ 即可，容斥原理容易证明其正确性。

$x\operatorname{xor}y$ 为 $k$ 进制下 $x,y$ 的逐位二进制异或，$\operatorname{highbit}(x)$ 为 $k$ 进制下 $x$ 最高的**非零**位。


---

## 作者：王熙文 (赞：1)

## 思路

发现在一种构造中删除掉颜色最大的边，连通块个数一定小于等于 $k$，因为这些连通块的每两个点都需要连接，如果不满足一定有长度为 $k$ 的链。

所以每多一种颜色最多使点数乘 $k$。因此若用 $c$ 种颜色，最大的点数为 $k^c$。

想要颜色个数最小，那么当前颜色要将序列分得尽量平均。那么每次令每段的长度为 $\lceil\dfrac{n}{k}\rceil$ 即为最优。递归处理每一段，将任意两个不在同一段的点连上当前颜色即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int a[1010][1010];
int ax=0;
void solve(int l,int r,int now)
{
	if(l==r) return;
	ax=max(ax,now);
	for(int i=l; i<=r; ++i)
	{
		for(int j=i+1; j<=r; ++j) a[i][j]=now;
	}
	int len=(r-l+1+k-1)/k;
	for(int i=1; i<=k && l<=r; ++i) solve(l,min(l+len-1,r),now+1),l+=len;
}
int main()
{
	cin>>n>>k;
	solve(1,n,1);
	cout<<ax<<'\n';
	for(int i=1; i<=n; ++i)
	{
		for(int j=i+1; j<=n; ++j) cout<<a[i][j]<<' ';
	}
	return 0;
}
```

---

## 作者：laoliu12345 (赞：0)

## CF1583F
[题目传送门](https://www.luogu.com.cn/problem/CF1583F)
### 解法说明
首先我们来思考一个较为简单的问题：一共有   $n=5000$  条边，要求是使每经过的长度为  43  的路不能有重色，一条边默认长度为  1  ，问最少用几种颜色并构造出其中一种方案。

经过思考我们发现：**每次可以在点集中选择  $t=43$  个点，使其中的边染同一种颜色，很明显此时同种颜色的路最大长度不超过  43  ，满足题意**。而后在分出来的点集中再次选择  43  个点集，使其中边染为同一种颜色。以此类推，那么最少就是   $\log_tn$   种颜色即  3  种。

**经过上述推导我们发现颜色数就是  $\log_tn$  。**
至于方案就按照上述方法染色即可。

那就可以愉快的写代码了。
#### 题目代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b;
int check(int i,int j)
{
	int cnt=0;
	while(1)
	{
		if(i==j) break;
		i/=b,j/=b;
		cnt++;
	}
	return cnt;
}
signed main()
{
	cin>>a>>b;
	cout<<ceil(log10(a)/log10(b))<<endl;
	for(int i=0;i<a;i++)
	    for(int j=i+1;j<a;j++)
	    	cout<<check(i,j)<<" ";
	return 0;
}
```

---

## 作者：Yizhixiaoyun (赞：0)

[本套题所有题解](https://www.luogu.com.cn/blog/yizhixiaoyun/cf1583-ti-xie)

由于笔者水平较弱，所以可能只能一路做到自己做不了的题，不保证能全部写完。

------------

构造专场是吧。

一直分组，先将 $k$ 个点分为一组，称为小组。每个小组内部的边全部涂上一种颜色，那么该组内部的任意一条路径长度一定不大于 $k$。

然后接着分，将 $k$ 个小组分为一个大组。如果两个点，它们在同一个大组，但是不在一个小组，那么再将它们涂上第二种颜色。这样就只有涂上了第二种颜色的路径长度小于 $k$。

再分下去，最多分 $\lceil \log_kn \rceil$ 组，则最少要用 $\lceil \log_kn \rceil$ 种颜色。

代码不长，似乎没人写 $\text{python}$？我来一个吧。

```python
n,k=map(int,input().split())
cnt=0
sum=1
while sum<n:
    sum=sum*k
    cnt=cnt+1
print(cnt)
for i in range(0,n):
    for j in range(i+1,n):
        u=i
        v=j
        ans=0
        while u!=v:
            u//=k
            v//=k
            ans=ans+1
        print(ans,end=' ')
```

---

## 作者：hgzxwzf (赞：0)

### [CF1583F](https://codeforces.com/contest/1583/problem/F)

结论：最小颜色数为 $\lceil\log_kn\rceil$。

证明：

我们将所有点 $k$ 个分成一组，每组内部两个点的连边涂上颜色 $1$，因为同一组内一条路径长度小于 $k$，所以这样连边合法。

再将所有组 $k$ 个分成一块，在同一块但不在同组两个点的连边涂上颜色 $2$，只有 $2$ 一种颜色的最长路径小于 $k$。

因为如果同一组内的两个点出现了两次，那么就说明经过了一条颜色为 $1$ 的边，那么这条路径就会同时存在颜色 $1,2$，所以一个组内最多有一个点在这条路径上出现，这条路径上最多 $k$ 个点，$k-1$ 条边。

同理继续分，最多分 $\lceil\log_kn\rceil$ 次，分一次多一种颜色。

对于两个点 $i$ 和 $j$，他们连边的颜色就是最小且满足 $\lfloor\frac{i}{k^t}\rfloor=\lfloor\frac{j}{k^t}\rfloor$ 的 $t$。
```cpp
#include<cstdio>
#include<set>
#include<algorithm>
#include<vector>
#include<stack>
#include<cmath>
#include<vector>
#include<cstring>
#include<queue>
#include<string>
#include<iostream>
#include<map>
#include<bitset>
#include<ctime>

#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=z;x>=y;x--)
#define LL long long
#define pi pair<int,int>
#define mk make_pair
#define fi first
#define se second

using namespace std;
const int N=1e3+10;

vector<int>ans;

int main()
{
	int n,k,mx=0;
	scanf("%d%d",&n,&k);
	rep(i,0,n-1)
	{
		rep(j,i+1,n-1)
		{
			int tk=k,h=1;
			while(i/tk!=j/tk) tk*=k,h++;
			mx=max(mx,h);
			ans.push_back(h);
		}
	}
	printf("%d\n",mx);
	for(int &i: ans)
		printf("%d ",i);
	return 0;
}
```


---

## 作者：_Clown_ (赞：0)

# F.Defender of Childhood Dreams
这是一道构造题。

读完题目后并没有思路。

然后我们考虑找找规律。

经过~~同机房巨佬口胡~~反复运算，

我们得到一种可行的构造：

就是对于 $(k^p+i,k^p+j)$，我们以同一种颜色建边。

不难发现，这种构造显然成立。

代码极短，不难写出了。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int N,K,Ret[1001][1001];
signed main(void)
{
	register int Now(1),Ans(0),i,j,k;cin>>N>>K;
	while(Now<=N)
	{
		Now*=K,Ans++;
		register bool Flag(false);
		for(k=0;Now*k+1<=N;k++)for(i=1;i<=Now;i++)for(j=i+1;j<=Now&&k*Now+i<=N&&k*Now+j<=N;j++)if(!Ret[k*Now+i][k*Now+j])Ret[k*Now+i][k*Now+j]=Ans,Flag=true;
		if(!Flag)Ans--;
	}
	cout<<Ans<<endl;
	for(i=1;i<=N;i++)for(j=i+1;j<=N;j++)cout<<Ret[i][j]<<' ';
	cout<<endl;
	return 0;
}
```

---

