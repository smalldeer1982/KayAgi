# 『JROI-5』Color

## 题目背景

【被三月删除的图片】

泷泽三月 Orz

---
被删除图片会偷偷展示给报名讲评的同学（

## 题目描述

**请注意到并不正常的时间限制。**

小 C 有一棵 $dep$ 层 $n$ 个节点的**完全二叉树**，她希望选择其中一个**包含根节点**的**连通块**染色，她想知道有几种不同的染色方案，答案对 $998,244,353$ 取模。

## 说明/提示

你可以通过学习 [OI-Wiki 树基础](https://oi-wiki.org/graph/tree-basic/) 来了解题面中的名词。

【样例解释】

对于样例 #1，可以画出如下所示二叉树。

![7sc6Yj.png](https://s4.ax1x.com/2022/01/19/7sc6Yj.png)

我们对该二叉树按照**前序遍历标号**（如图），得到点集 $\left(1,2,3\right)$。

则仅有 $\left(1,2,3\right),\left(1,2\right),\left(1,3\right),\left(1\right)$ 是合法的染色方案。
****
对于样例 #3，可以画出如下所示二叉树。

![7sc1eO.png](https://s4.ax1x.com/2022/01/19/7sc1eO.png)

我们对该二叉树按照**前序遍历标号**（如图），得到点集 $\left(1,2,3,4,5\right)$。

则仅有 $\left(1,2,3,4,5\right),\left(1,2,3,4\right),\left(1,2,3\right),\left(1,2,4\right),\left(1,2\right),\left(1,2,3,5\right),\left(1,2,4,5\right),\left(1,2,5\right),\left(1,5\right),\left(1\right)$ 是合法的染色方案。

显然 $\left(2,3,4\right),\left(1,3,4\right)$ 不是合法的染色方案，前者没有包含根节点，后者染色的点集不是联通的。
***
对于 $30\%$ 的数据，$1\leq T\leq 10, 1\leq dep \leq 20$。

对于另外 $20\%$ 的数据，树是满二叉树（即完美二叉树，perfect binary tree）。

对于 $100\%$ 的数据，$1\leq T\leq 10, 1\leq dep \leq 10^6$。



## 样例 #1

### 输入

```
1
2
10```

### 输出

```
4```

## 样例 #2

### 输入

```
1
3
100```

### 输出

```
25```

## 样例 #3

### 输入

```
1
3
010```

### 输出

```
10```

## 样例 #4

### 输入

```
见附件```

### 输出

```
见附件```

# 题解

## 作者：Cocoly1990 (赞：9)

**D**

**part1** 问题等价于给定一颗完全二叉树，求其包含根的子树个数。 首先，先考虑满二叉树。 我们可以发现，答案只和树的深度(dep)有关，可以想到用 $dp_i$ 表示深度为 $i$ 的满二叉树的答案。   

显然 $dp_1 = 1$ 。我们考虑用 $dp_{i - 1}$ 来计算 $dp_i$。



![HVH0bt.png](https://s4.ax1x.com/2022/02/03/HVH0bt.png)


以 $dp_3$ 为例，我们可以发现，1 号节点为根节点，必须选。 对于每一种左子树和右子树的方案，我们只需要直接加上根节点，就可以对应一种新树的方案；而对于每一种新树的方案，去掉根节点就可以对应到一种左右子树的方案。由乘法原理可以得知其答案为左子树与右子树的选法乘积。   我们可以直接利用已经算出来的 $dp_2$ ，表示深度为 2 的包含根的子树个数，但是 $dp_2$ 包含的方案中，不包括不选子树的根节点的情况。但是在新树中，我们没有这个要求，我们还可以左子树一个都不选，所以 $dp_i = (dp_{i - 1} + 1) ^ 2$。 期望得分：20。

**part2** 类似的，我们也可以通过分别递归计算左右子树答案，再相乘的做法来对一颗不规则的树来计数。 



![HVHc8g.png](https://s4.ax1x.com/2022/02/03/HVHc8g.png)


以一颗深度为 5 ，底层节点数为 5 的树为例。我们可以拆成以 2 和 3 为根节点的子树分别递归地去求，求完后相乘。   我们按从上到下，从左到右给树标号，若 $d_i$ 表示以 $i$ 为根的答案，则 $d_i = (d_{2i} + 1)(d_{2i + 1} + 1)$ 。直接 dfs 即可，答案为 $d_1$。 由于我们需要对于每一个节点递归一次，复杂度为 $\mathcal{O}(T\times 2^{dep})$。 结合 part1，期望得分：50。 

**part3** 我们可以发现，在我们的 dfs 中，有许多满二叉树，所以我们根本不需要对每个节点 dfs 一次。



![HVHo5T.png](https://s4.ax1x.com/2022/02/03/HVHo5T.png)

比如以 3，4，11 为根节点的子树分别就是深度为 3, 2, 1 的满二叉树。 更形式化的，我们可以发现，对于每一个节点，其左右子树中必有一颗为满二叉树。 由完全二叉树的性质，若右子树不为满二叉树，则其左子树必为满二叉树，而若左子树不为满二叉树，则其底层节点根本没有覆盖到右子树，右子树为满二叉树。 所以，我们可以用 part1 的做法，预处理出所有满二叉树的答案。每次 dfs 的，直接调用即可。而我们只需要 dfs 一条链。（图中 1-2-5-10-20） 所以，我们的问题变为对于每个节点，确定其哪颗子树为满二叉树，并且求出子树高度。即我们需要求出从根节点到最后一个叶节点的路径，每次 dfs 路径上的下一个节点，直接调用求出另外一个节点的答案。 观察到本题给出底层节点个数的方式非常特殊，用二进制给出。暂时忽略满二叉树的情况，去掉第一个0，比如 5 为 0101。我们从根节点开始，对于这个二进制字串，从左到右，如果遇到 0 就走左子树，遇到 1 就走右子树，我们可以发现对于任意一棵树，我们都可以走到当前最后一个节点的下一个节点。  



![HVHb24.png](https://s4.ax1x.com/2022/02/03/HVHb24.png)


仔细研究一下，我们可以发现 5 的 00101，第一位的 0 表示其节点数小于 16 ，即位于根为 1 的子树上，而第二个 1 表示其节点数小于 8，位于 1 的左子树上，第三个 1 表示其节点数大于等于 4 ，位于 2 的右子树上。 由此，我们再考虑满二叉树，图中满二叉树底层节点为 16，表示为 10000，第一位的 1 表示其节点数大于等于 16，即其最后一个节点的下一个节点根本就不在根为 1 的子树上。 设其底层节点个数为 $s$， $s$ 的二进制表示可以直接求出其最后一个节点的下一个节点的路径，那么 $s - 1$ 的二进制表示的就是我们需要求的路径了。 下面是求出子树高度，设当前节点深度为 k，那么若左子树为满二叉树，那么从根节点到当前叶节点的距离为 dep，即高度为 $dep - k$。若是右子树为满二叉树，由于缺少了底层节点，其距离为 $dep - 1$，即树高为 $dep - k - 1$。 由于我们每次只会 dfs 一条链，所以复杂度为 $\mathcal{O}(T \times dep)$。 



```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e6 + 5;
const int MOD = 998244353;
int dep, a[MAXN], dp[MAXN];
string s;
int dfs(int k) {
	if (k == dep)
		return 1; //到最后一层
	if (a[k] == 0) 
		return (dfs(k + 1) + 1) * (dp[dep - k - 1] + 1) % MOD; //右子树为满二叉树，dfs左子树
	else return (dp[dep - k] + 1) * (dfs(k + 1) + 1) % MOD; //左子树为满二叉树，dfs右子树
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	dp[1] = 1;
	for (int i = 1; i < MAXN; ++i)
		dp[i] = (dp[i - 1] + 1) * (dp[i - 1] + 1) % MOD; //预处理
	int T;
	cin >> T;
	while (T--) {
		cin >> dep >> s;
		int pos = 0;
		for (int i = 1; i < s.length(); ++i) {
			a[i] = s[i] - '0';
			if (a[i] == 1)
				pos = i;
		}
		a[pos] = 0; 
		for (int i = pos + 1; i < dep; ++i)
			a[i] = 1;//s-1 的二进制表达
		cout << dfs(1) << endl;
	}
	return 0;
}
```



当然还有另一种优化方法，由 Part 2 我们得到转移方程 $f_i = (f_{2i} + 1)(f_{2i + 1} + 1)$.（嗯上下两个题解不是同一个人写的）。

显然状态不是很好优化，那么思考如何优化转移。可以发现，每个 $f_x$ 是相互独立的，也就是说，我们可以把特殊的 $f_x$ 预处理出来。 考虑到满二叉树总共只有 $\log n$ 种，不妨把他们的染色方案与处理出来，预处理他们的时间复杂度$\mathcal{O}\left(dep\right)$ ![5lpIvn.png](https://z3.ax1x.com/2021/10/14/5lpIvn.png) 比如这颗树，我们把能预处理的满二叉树给他处理掉。 ![5lpJnx.png](https://z3.ax1x.com/2021/10/14/5lpJnx.png) ![5lp8j1.png](https://z3.ax1x.com/2021/10/14/5lp8j1.png) 

绿色表示处理过的，然后会发现**每层只有两个节点需要向上传递**。所以复杂度是对数级别的。

我们可以通过 $s$ 处理出 $s_0$ 表示次底层的叶子节点。（二进制高精度）

具体的说，对 $s$ 从左向右处理 1 ，处理到 $\texttt{dep}$ 数组里，表示当前每层预处理的结果。 $s_0$ 从右向左处理 1 ，同样储存到数组里，如果碰到已经储存过的位置，那么从那个点开始向上递推。

```c++
#include<bits/stdc++.h>
#define int long long
#define elif else if
#define ALL(x) x.begin(),x.end()
#define lowbit(x) (x&(-x))
using namespace std;
void fileio(const string &s)
{
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}
const int INF=4e18;
inline int read()
{
	int x=0;
	bool flag=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
			flag=0;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return (flag?x:~(x-1));
}
const int mod=998244353;
int t,dep,a[1000001];
vector<int> f[1000001];
char s1[1000000],s2[1000000];
void solve()
{
	dep=read();//8 00111001 00100011
	scanf("%s",s1);
	scanf("%s",s2);//假设s1是最底层叶子节点，s2是次底层叶子节点。具体的需要二进制高精度。
	reverse(s1,s1+dep);
	reverse(s2,s2+dep);
	for(int i=0;i<=dep;i++)
		f[i].clear();
	for(int i=0;i<dep;i++)
		if(s1[i]=='1')
			f[dep-i].push_back(a[i+1]);
	for(int i=0;i<dep;i++)
		if(s2[i]=='1')
			f[dep-i-1].push_back(a[i+1]);
	for(int i=dep;i;i--)
		if(f[i].size()==1)
			f[i-1].push_back(f[i][0]+1);
		elif(f[i].size()==2)
			f[i-1].push_back((f[i][0]+1)*(f[i][1]+1)%mod);
	cout<<f[0][0]-1<<'\n';
}
signed main()
{
	a[1]=1;
	for(int i=2;i<=1000000;i++)
		a[i]=(a[i-1]+1)*(a[i-1]+1)%mod;
	t=read();
	while(t--)
		solve();
	return 0;
}
```

隐藏图片：

【数据删除】


---

## 作者：囧仙 (赞：9)

本文所用二叉树图片均使用 $\textrm{Ti\textit kZ } \& \scriptsize\textrm{ PGF}$ 绘制。

## 题解

首先考虑一个朴素 $\text{dp}$。对于原树的一棵以 $u$ 为根节点的子树，定义 $\mathit{dp}(u)$ 表示子树 $u$ 中，**包含**节点 $u$ 的连通块的方案数。

设 $u$ 的左儿子为 $l$，右儿子为 $r$，那么就有：

$$\mathit{dp}(u)=(\mathit{dp}(l)+1)\cdot (\mathit{dp}(r)+1)$$

意义：考虑左子树内选择一个包含 $l$ 节点的连通块的方案数为 $\mathit{dp}(l)$，但是考虑到包含 $u$ 的连通块内可以不选择左子树的任何节点，所以左子树的情况数为 $\mathit{dp}(l)+1$。同理，右子树的情况数为 $\mathit{dp}(r)+1$。根据乘法原理，包含 $u$ 的连通块的方案数即为 $(\mathit{dp}(l)+1)\cdot (\mathit{dp}(r)+1)$（因为包含了 $u$，所以必定非空。并且左右子树的情况是互相独立的）。特别地，若 $l$ 或者 $r$ 不存在，则认为该子树的情况总数为 $1$。

那么考虑一棵满二叉树（每一层的节点都完全排满了的二叉树），设高度为 $d$ 的满二叉树的方案数为 $p_d$，那么有：

$$p_d=\begin{cases}1 & d=1 \cr (p_{d-1}+1)^2 & d>1\end{cases}$$

回到本题上面来。考虑画出题目中所给的这棵完全二叉树。这里举一个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/q46zejhu.png)

这棵树对应的高度为 $5$。最下面一层共有 $10$ 个节点，对应的二进制数码是 $01010$。

容易发现，一棵高度为 $d$ 的二叉树，第 $d$ 层的节点的个数最多是 $2^{d-1}$ 个。设根节点的两棵子树分别为 $L,R$，因为完全二叉树最底层的儿子应当是从左往右排列的，因此如果 $L$ 的 $\mathit{dep}$ 层儿子没有被排满，那么 $R$ 的第 $\mathit{dep}$ 层应当是没有节点的；反之，只有 $L$ 的最底层儿子被排满了，$R$ 的 $\mathit{dep}$ 层才可能会有节点。

![](https://cdn.luogu.com.cn/upload/image_hosting/b0iz9sn1.png)

对于这个例子，很容易发现 $L$ 的 $\mathit{dep}$ 层被排满了。那么 $L$ 应当是一个**满二叉树**，它对 $\mathit{dp}(1)$ 而言，情况数一共会有 $p_{4}+1$ 种，也就是 $\mathit{dp}(2)=p_{4}$。那么我们需要计算 $\mathit{dp}(3)$ 的值。

![](https://cdn.luogu.com.cn/upload/image_hosting/3erjn4c1.png)

拖出这个以 $3$ 为根的子树。容易发现它的左子树没有被排满，因此它的右子树的第 $\mathit{dep}$ 层应该是没有任何节点的。因而对于 $\mathit{dp}(3)$ 而言，它的情况数一共有 $p_2+1$ 种，也就是 $\mathit{dp}(7)=p_2$。那么就需要计算 $\mathit{dp}(6)$ 的值。

![](https://cdn.luogu.com.cn/upload/image_hosting/g7nfk1me.png)

对于以 $6$ 为根的子树而言，它的左子树是被排满了的。因此对于 $\mathit{dp}(6)$ 而言，左子树的情况个数为 $\mathit{dp}(2)+1$ 种。最后递归处理 $\mathit{dp}(13)$，容易发现 $\mathit{dp}(13)=1$。

最后可以回溯计算出 $\mathit{dp}(1)$ 的值。

下面考虑如何知道一棵子树的左儿子是否被排满了。可以发现，如果 $S_{i+1}$ 为 $1$，则表示当前处理到的第 $i$ 层的这个节点左子树的 $\mathit{dep}$ 层已经被排满，否则没有排满。对于 $S$ 当中剩下来的 $[i+2,\mathit{dep}]$ 部分，它恰好描述了并没有被排满的那棵子树，它的 $\mathit{dep}$ 层节点的情况。这一点需要读者仔细理解，可以结合上面的例子。

总结一下我们的流程：

- 首先预处理出 $p$ 数组。对于本题而言，由于 $\mathit{dep}\le 10^6$，因此只需要预处理出 $p_1,p_2,\cdots,p_{10^6}$ 的值对 $998,244,353$ 取模后的结果。
- 对于每一次询问，首先判断 $S$ 的第一个数码 $S_1$。若 $S_1=1$，就说明这棵树本身就是一个满二叉树，输出 $p_{\mathit{dep}}$ 即可。
- 否则枚举当前已经处理到了递归的层数，记为第 $x$ 层。如果 $S_{x+1}=1$，则说明它的左子树是高度为 $\mathit{dep}-x$ 的满二叉树，情况数为 $p_{\mathit{dep}-x}+1$，否则它的右子树为高度是 $\mathit{dep}-x-1$ 的满二叉树，情况数为 $p_{\mathit{dep}-x-1}+1$。当枚举到 $x=\mathit{dep}-1$ 时进行回溯。

容易发现复杂度为 $\mathcal O(\sum \mathit{dep}_i)$，可以通过本题。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int INF =2147483647;
const int MAXN=1e6+3;
const int MOD =998244353;
int F[MAXN],G[MAXN],n=1e6; char S[MAXN];
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
int main(){
    F[1]=1; up(2,n,i) F[i]=1ll*(F[i-1]+1)*(F[i-1]+1)%MOD;
    dn(qread(),1,T){
        int d=qread(),ans=0; scanf("%s",S+1);
        if(S[1]=='1') printf("%d\n",F[d]); else{
            up(2,d,i){
                if(S[i]=='1') G[i]=F[d-i+1]+1;
                else          G[i]=F[d-i  ]+1;
            }
            dn(d,2,i) ans=1ll*(ans+1)*G[i]%MOD;
            printf("%d\n",ans);
        }
    }
    return 0;
}
```

---

## 作者：water_three (赞：4)

放眼一看，$1≤dep≤10^6$。我本来还想看看 $2^{10^6}$ 等于多少，结果发现等于~~无效输入~~。

### 思路：
我们首先先从部分分看起，对于 $20$ 分，树是满二叉树（即完美二叉树。设 $dd_{i-1}$ 为总共 $i-1$ 层的满二叉树**包含根节点的连通块染色的个数**，经过推算可以得出 $dd_i \gets dd^2_{i-1} + 2 \times dd_{i-1} + 1$。

#### 证明：
以样例 $1$ 为例，我们将节点 $2$ 看成是一棵有 $2$ 种合法方案的子树，假设有 $\left(2,4\right),\left(2,5\right)$ 为合法方案。那么节点 $3$ 看成有 $3$ 种合法方案的子树，假设有 $\left(3,6\right),\left(3,7\right),\left(3,8\right)$，为合法方案。最后和根节点 $1$ 合并起来就是：

* 先将 $\left(2,4\right),\left(2,5\right)$ 前加上 $1$ 得   $\left(1,2,4\right),\left(1,2,5\right)$。
* 将 $\left(3,6\right),\left(3,7\right),\left(3,8\right)$ 加上 $1$ 得  $\left(1,3,6\right),\left(1,3,7\right),\left(1,3,8\right)$。
* 将左子节点和右子节点通过分步相乘得到 $2$ 乘 $3$ 等于 $6$ 种。
* 加上根节点的 $1$ 得 $\left(1\right)$。

### 正解：

完全二叉树和满二叉树有什么区别？

不就多了几个叶节点吗。

那么我们直接从根节点开始递归，由于是完全二叉树，所以**根节点的左节点和右节点必有一个是满二叉树**。对于是满二叉树的那一部分，我们通过预处理 $dd_i$ 来解决，**然后往不是满二叉树的方向递归**。设 $x$ 为当前所在的层数，设 $DEP$ 为当前子树一共有多少层。

* 当左子节点是满二叉树时，左边的方案数为 $dd_{DEP-1}$，右边递归。
* 当右子节点是满二叉树时，右边的方案数为 $dd_{DEP-2}$，左边递归。

**判断哪边为满二叉树：** 模拟一下可以发现，当一棵树的叶子节点个数，在二进制下的位数（设为 $TOT$ ）小于 $DEP$ 减 $1$ 时，右子树就是满二叉树。

#### 叶子节点的转移：
* 当向左子节点递归时，叶子节点数不变。
* 当向右子节点递归时，叶子节点数减少 $2^{DEP-2}$。（画图很好理解）

#### 特判：
当叶子节点数刚好是 $2^{dep-1}$ 时，直接输出 $dd_{dep}$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353,MAXN=1e6+1;
bool a[MAXN],pan=1;
long long tot=0,dd[MAXN],T,dep;
inline long long read() {
	long long x=0;
	bool flag=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-')
			flag=0;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return (flag?x:~(x-1));
}
inline void READ() {//读入01字符串 
	char e=getchar();
	tot=0;
	while(!(e>='0'&&e<='9'))e=getchar();
	if(e=='0')pan=0;
	while(e=='0')e=getchar();//注意去除补的0 
	while(e>='0'&&e<='9') {
		a[++tot]=e-'0';
		if(pan==1&&(tot!=1&&e=='1'))pan=0;
		e=getchar();
	}
	return ;
}
int di(int x,int DEP,int TOT,int front) {
	if(TOT<DEP-1) {
		int h=di(x+1,DEP-1,TOT,front)%mod;
		return (h*dd[DEP-2]%mod+h+dd[DEP-2]+1)%mod;
	} else {
		front++,TOT--;
		while(a[front]==0&&front<=tot)TOT--,front++;//注意去0 
		if(front>tot)return (dd[DEP-1]*dd[DEP-2]+dd[DEP-2]+1+dd[DEP-1])%mod;//特判，当两边都是满二叉树 
		int h=di(x+1,DEP-1,TOT,front)%mod;
		return (h*dd[DEP-1]%mod+h+dd[DEP-1]+1)%mod;
	}
}
void prepare() {
	dd[1]=1;//预处理dd[i] 
	for(long long i=2; i<=MAXN; i++) {
		dd[i]=(1+2*dd[i-1]%mod+dd[i-1]%mod*dd[i-1]%mod)%mod;
	}
}
int main() {
	prepare();
	T=read();
	while(T--) {
		dep=read();
		pan=1;
		READ();
		if(pan) {//如果是满二叉树 
			cout<<dd[dep]<<endl;
			continue;
		} else {//front是a数组的指针，因为叶子节点减少2^DEP-2,就相当于将二进制的最高位减掉。 
			int front=1;
			cout<<di(1,dep,tot,front)<<endl;
		}
	}
}
```


---

## 作者：Raymondzll (赞：2)

## P8089 Color

### 来自一个考场上想到正解，数组没开够的菜鸡。

- 真的有第四题的难度吗？设疑。

- Update：评分出来了，第二、第三题和这个评分都一样，没啥奇怪的了。

### 解题思路

拿到题目，看到了完全二叉树的条件。

完全二叉树不就是满二叉树和一堆叶子吗……

另外数据量极小的情况下 $ans(x)=(ans(l_x)+1)\times(ans(r_x)+1)$ 可以每个节点由下而上递推求吧……边界条件就是 $ans(x)=1$……看上去我们只是要优化计算量，从 $2^{dep}$ 级别变成 $dep$ 级别……

带着这些疑问，这只蒟蒻开始了切题的旅途。

![](https://cdn.luogu.com.cn/upload/image_hosting/sgcj7hdp.png)

#### Part1：满二叉树

根据上面的式子可得 $f(x)=(f(x-1)+1)^2$。

看起来后面会多次使用满二叉树的答案，加之多组数据，我把它们预处理掉了。

```cpp
//fbin stands for full_binary.
fbin[1]=1;
for(int i=2;i<=1000000;i++){
	fbin[i]=1ll*(fbin[i-1]+1)*(fbin[i-1]+1)%Mod;
}
```

#### Part2：一堆叶子

叶子是以二进制形式给出的，其实不仅规避了数太大的问题，还方便我们处理。

如果叶子是 ```100...0``` 这样的，那这就是一棵满二叉树，直接按照满二叉树的方式处理掉。

否则一位一位看。

如果这一位是 $1$，那么当前位的左儿子是满二叉树。

![](https://cdn.luogu.com.cn/upload/image_hosting/5ul74cwt.png)

如果这一位是 $0$，那么当前位的右儿子也是满二叉树，只不过它的深度会少一。（一个叶子也没有）

![](https://cdn.luogu.com.cn/upload/image_hosting/91zfbjko.png)

最后注意一下处理最后一位时的赋值情况即可。

### 代码部分

**注意看代码中的注释，这是考场代码，实现细节和讲解略有不同（主要是```val[x]```的含义。）**

```cpp
#include <bits/stdc++.h>
using namespace std;
void file(string str){
	freopen((str+".in").c_str(),"r",stdin);
	freopen((str+".out").c_str(),"w",stdout);
}
const int Mod=998244353;
int fbin[1000010];//full_binary.
int dep;
char ch[1000010];
int lc[5000010],rc[5000010],tot;
int val[5000010];//就是讲解中的ans，但含义有细微差别（看dfs函数）
int dfs(int x){
	long long res=1;
	if(val[lc[x]])res*=val[lc[x]];
	else res*=dfs(lc[x]);
	if(val[rc[x]])res*=val[rc[x]];
	else res*=dfs(rc[x]);
	res++;
	/*
	和讲解中不太一样，
	这里实现的是val[x]=val[lc]*val[rc]+1
	而不是val[x]=(val[lc]+1)*(val[rc]+1) 
	*/
	res%=Mod;
	return res;
}
int solve(){
	scanf("%d%s",&dep,ch);
	if(ch[0]=='1')return fbin[dep];//排除掉满二叉树的情况 
	int pnt=1;//就是讲解中的now 
	tot=1;
	for(int i=1;i<dep;i++){
		lc[pnt]=++tot;rc[pnt]=++tot;
		if(ch[i]=='1'){
			val[lc[pnt]]=fbin[dep-i]+1;
			if(i==dep-1)val[rc[pnt]]=1;
			else val[rc[pnt]]=0;//这里的意思是多测顺便清零 
			pnt=rc[pnt];//递归 
		}else{
			val[rc[pnt]]=fbin[dep-i-1]+1;
			if(i==dep-1)val[lc[pnt]]=1;
			else val[lc[pnt]]=0;//同上 
			pnt=lc[pnt];
		}
	}
	return (dfs(1)+Mod-1)%Mod;//由于上面val意义的不同，这里我们需要减1 
}
int main(){
	fbin[1]=1;
	for(int i=2;i<=1000000;i++){
		fbin[i]=1ll*(fbin[i-1]+1)*(fbin[i-1]+1)%Mod;
	} 
	int T;scanf("%d",&T);
	while(T--)cout<<solve()<<endl;
	return 0;
}
```

---

## 作者：JerryTcl (赞：2)

首先，若一个节点左子树有 $x$ 种染色方案，右子树有 $y$ 种，那整棵子树的染色方案数即为：

$$xy+x+y+1=(x+1)(y+1)$$

即选完根节点后，左右子树都选，只选左子树，只选右子树，左右子树都不选的方案数之和

先预处理出满二叉树的方案数

由于二叉树顺序是不固定的，我们可以将其二进制拆分

先从最后一层取出一个节点，依次枚举剩下的节点二进制第 $i$ 位

若第 $i$ 位为 $1$，就相当于新增一个高为 $i$ 的满二叉树，计算即可

---

