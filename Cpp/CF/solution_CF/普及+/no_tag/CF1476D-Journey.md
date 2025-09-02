# Journey

## 题目描述

有 $n$ 条道路连接着 $n + 1$ 座编号从 $0$ 到 $n$ 的城市，第 $i$ 条道路连接了编号为 $i - 1$ 和 $i$ 的城市，其中 $i\in[1,n]$。

每条道路都有初始方向，初始方向用一个字符串表示。如果第 $i$ 个字符为 $\texttt{L}$，则第 $i$ 条道路一开始从城市 $i$ 连向 $i - 1$；$\texttt R$ 则表示该道路一开始从城市 $i$ 连向 $i+1$。

一个旅行者会从某个城市开始旅行，每次旅行只能沿着道路的方向去到一个相邻的城市，**每走过一次道路之后所有道路的方向都会发生改变**。

对于每个城市，求旅行者从该城市出发最多能到达城市的数量（同一城市可以经过多次，但是只计算一次）。

## 说明/提示

$1\le t\le 1\times 10^4$，对于每组数据 $1\le n\le 3\times 10^5$，且同一测试点内有 $1\le \sum n\le 3\times 10^5$。

## 样例 #1

### 输入

```
2
6
LRRRLL
3
LRL```

### 输出

```
1 3 2 3 1 3 2
1 4 1 4```

# 题解

## 作者：registerGen (赞：5)

[可能更好的阅读体验](https://registergen.github.io/post/solution-cf1476d/)

这道题充分的说明：我数据结构学傻了（

# Solution

首先，一个人如果能从 $a$ 走到 $b$，则他一定在到达 $b$ 的时候立即掉头然后走回 $a$。（为什么？）

所以只需求出这个人往左走能走多远，往右走能走多远，然后加起来即可。

如果一个人能在一个串上一直走下去，则这个串必须是 `LRLRLR...` 或者 `RLRLRL...`。

然后我用了二分 + 线段树（

```cpp
struct Node{
    char l,r; // 这个区间左右端点的字符
    bool ok; // 一个人是否能在这个区间表示的子串上一直走下去
};

inline Node pushUp(Node L,Node R){
	Node res;
	res.l=L.l;
	res.r=R.r;
	res.ok=L.ok&&R.ok&&((L.r=='L'&&R.l=='R')||(L.r=='R'&&R.l=='L'));
	return res;
}
```

这棵线段树可以判断一个区间是否“合法”。

然后就可以二分了。

时间复杂度 $\mathcal O(n\log^2 n)$，可能需要卡常才能过。

# Code

细节比较多。

<https://codeforces.com/contest/1476/submission/105930535>

---

## 作者：TernaryTree (赞：4)

考虑每个点能到达多少个点，本质上是 左边能到达的点数 $+$ 右边能到达的点数 $+$ 自己本身。

如果一个点可以到达左边的点，那么这条路径将会是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/5jdl3tq9.png)

这张图里最右边的点可以到达最左边的点，也就是：`…RLRL`。

同理，还是刚才那张图，最左边的点也可以到达最右边的点，也就是：`RLRL…`。

那么我们如何在线性求出一个点能到达最左边的点的距离以及最右点呢？

考虑动态规划求解。

设 $l_i$ 表示点 $i$ 最多往左走几步，$r_i$ 表示点 $i$ 最多往右走几步。

则有：

$$
l_i=
\begin{cases}
l_{i-2}+2 &(s_{i-1}=\texttt{"R"}\ \&\ s_{i}=\texttt{"L"}) \\
1 &(s_{i-1}=\texttt{"L"}\ \&\ s_{i}=\texttt{"L"}) \\
0 &(s_{i}=\texttt{"R"})
\end{cases}
$$

$$
r_i=
\begin{cases}
r_{i+2}+2 &(s_{i+1}=\texttt{"R"}\ \&\ s_{i+2}=\texttt{"L"}) \\
1 &(s_{i+1}=\texttt{"R"}\ \&\ s_{i+2}=\texttt{"R"}) \\
0 &(s_{i+1}=\texttt{"L"})
\end{cases}
$$

其中 $s_i$ 表示连接点 $i-1$ 与 $i$ 的路的方向。

记得 $l_i$ 是正推，$r_i$ 是倒推。

然后直接依次输出 $l_i+r_i+1$ 即可 AC。

时间复杂度：$\Theta(\sum n)$

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e5 + 1;

int t, n;
char s[maxn];
int l[maxn], r[maxn];

int main() {
    cin >> t;
    while (t--) {
        cin >> n >> (s + 1);
        l[0] = 0, l[1] = s[1] == 'L';
        r[n] = 0, r[n - 1] = s[n] == 'R';
        for (int i = 2; i <= n; i++) l[i] = s[i - 1] == 'R' && s[i] == 'L' ? l[i - 2] + 2 : s[i] == 'L';
        for (int i = n - 2; i >= 0; i--) r[i] = s[i + 1] == 'R' && s[i + 2] == 'L' ? r[i + 2] + 2 : s[i + 1] == 'R';
        for (int i = 0; i <= n; i++) cout << l[i] + r[i] + 1 << " "; cout << endl;
        for (int i = 0; i <= n; i++) s[i] = l[i] = r[i] = 0;
    }
    return 0;
}
```

---

## 作者：Dzhao (赞：4)

题意：有点 $0...n$ ，对于第 $i$ 条边 $(i-1,i)$ 告诉你该边的方向，每走一步所有边的方向都会反转，对于每个点请你求出从该点最多能走到多少个不同的点。

题解：从某个点开始往右走，依次经过的边必定是 $\texttt{RLRL...RL(RR)(L)}$，同理往左走依次经过的边必定是 $\texttt{LRLR...LR(LL)(R)}$。也就是说走的过程中**如果碰到两条相同的边，就会往回走，沿原路返回到起点，然后再重复以上过程。**

所以我们只要预处理出每个点向右走和向左走分别能走到多远就行了。

后面的部分我们均假设： $0$ 方向为 $\texttt R$，$1$ 方向为 $\texttt L$

令：

$Lmin[i][0/1]$ 表示从 $i$ 点往**左**走，经过的第一条边方向为 $(0/1)$，**最远**能走到哪个点。

$Rmax[i][0/1]$ 表示从 $i$ 点往**右**走，经过的第一条边方向为 $(0/1)$，**最远**能走到哪个点。

$g[i]$ 表示第 $i$ 条边的方向。

易根据性质推出转移方程：
```cpp
Lmin[i][g[i]] = Lmin[i - 1][!g[i]]
Rmax[i][g[i + 1]] = Rmax[i + 1][!g[i + 1]]
```
预处理一下，对于每个点能到的点即为他往左走能到的最远点与往右走能到的最远点之间的所有点，输出答案即可。

时间复杂度 $\mathcal{O}(n)$。

（注意：若 $i$ **不能**往某个方向走，则往该方向走能到达的最远点即为**该点本身**）

$\mathcal{View\ Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int n,g[N],T,Rmax[N][2],Lmin[N][2];char s[N];

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%s",&n,s);
		for(int i=0;i<=n;i++) Rmax[i][0]=Rmax[i][1]=Lmin[i][0]=Lmin[i][1]=i; 
		for(int i=1;i<=n;i++) g[i]=(s[i-1]=='L');
		for(int i=n-1;i>=0;i--)
			Rmax[i][g[i+1]]=Rmax[i+1][!g[i+1]];
		for(int i=1;i<=n;i++) 
			Lmin[i][g[i]]=Lmin[i-1][!g[i]];
		for(int i=0;i<=n;i++) 
		{
			int l=i,r=i;
			if(i!=0 && g[i]==1) l=Lmin[i][g[i]];
			if(i!=n && g[i+1]==0) r=Rmax[i][g[i+1]];
			printf("%d ",r-l+1);
		}
		printf("\n");
	}
	return 0;
}
```

$\mathcal{Thanks\ for\ watching}$

---

## 作者：walk_alone (赞：2)

提供一个和其他题解不一样的做法。

在打比赛的时候没想出来，一直想的是说用$f[0][i]$与$f[1][i]$做转移——$f[1][i]$表示奇数步到$i$遍历城市数，$f[0][i]$表示偶数步到$i$遍历城市数，结果记搜崩了，并且被ABC题拖累导致没有时间做这个题……当然这题也可以DP，其他题解有提到。

其实这个题可以用**图论**的想法去做。

注意到，每走一次路就会全部反向。那么第一：整个连接状态就两种，要么全正着要么全反着；第二，走两次图就恢复了；第三，来的时候怎么走过去接下来一步就可以怎么走回去：

假设现在有一条边从2单向指向3，从2出发可以走到3，然后由于走过了一步，所有道路反向，那么现在这个路是从3指向2的，3又可以走回到2。因而，如果$i$能到$j$，那么$j$就一定能回到$i$。

基于这几个性质，我们就可以发现：**走的顺序不会影响连通性**。从一个点出发，无论是先走左边再遍历右边，还是中间穿插左右横跳式游览，**能到的城市总是能到**。那么我们就可以考虑直接研究这个图而非每个节点了。

那么这个图应该怎么抽象出来呢？

我们注意到：**走的步数不同的时候一个点所能到达的点的状态不同**。例如一个节点如果给的是$\tt LR$，那么第奇数步的时候图是正图，两边都能去；而如果是第偶数步到达这个点，那么就两边都不能去，因为连接状态变成了$\tt RL$。因而，我们应该考虑**分层图**——用连接状态做分层依据。结合上面的分析，我们就得到了建图方法：

**如果是$\tt L$，则第一层$i-1$向第二层$i$连双向边；如果是$\tt R$，则是第一层$i$连向第二层的$i-1$，连双向边;第一层$i$与第二层$i$不相连。**

最后答案直接统计每个点所属的连通块和每个连通块的大小即可。因为是无向图，同一连通块内可以互相到达，因而一个连通块内答案相同；由于同一节点不同层不能到达，因而不会出现一个节点两层同时出现在一个连通块中，因而连通块大小就是到达城市数，其中在第二层的节点为偶数步到达的，第一层节点是奇数步到达的。

代码也比较简单，只给出核心部分代码。

```cpp
for (int i = 1; i <= n;i++)//建边。字符串中从1开始编号
	if(a[i]=='R')//如果是R的情况，黑体字分析了。
	{
		add(i - 1, i + n + 1);
		add(i + n + 1, i - 1);
	}
	else//L的情况
	{
		add(i, i + n);
		add(i + n, i);
	}
for (int i = 0; i <= 2 * n + 1; i++)//一个朴素的计算连通块数目和连通块大小的代码
	if (!col[i])
		bfs(i, ++tot);//图的遍历，遍历这个连通块，tot为染色专用
```


---

## 作者：绝顶我为峰 (赞：2)

来一发并不怎么正常的 $O(n\log n)$ 做法。

显然，如果你可以通过一条边到达相邻的点，那么这条边反向之后你还可以再走回来，反之，你既不能走过去，也不能走回来。

由于从一个点出发经过若干点回到原点一定经过偶数条边，所以如果初始一条边可以通过，那么在**任何时刻**都可以从**任何方向**通过，反之则**任何时刻**不能从**任何方向**通过。

由于从一个点出发经过若干点回到原点一定经过偶数条边，我们还可以得出我们从某点出发向一个方向走，再回到原点，道路的方向和初始时是相同的，所以不需要考虑两边先后顺序。

那么我们直接分两边计算贡献，一直走到走不过去就好了。

接下来我们需要考虑什么样的序列可以产生贡献，因为每走一步道路方向都会改变，那么我们只要序列交替出现 `L` 和 `R` 就好了。

立即有了一个 naive 的做法：每个点向两边暴力延伸。然而这会被卡。

考虑优化算法，看到最长不重复的子串，容易想到用线段树维护。（之前有一个题目叫“好一个一中腰鼓”，考的就是这个东西，可惜这题现在没掉了，不过我写了一篇题解，不懂怎么用线段树维护的可以先看一下→[传送门](https://www.luogu.com.cn/blog/FrozaFerrari/solution-p2253)）

其实这一题会比刚才提到的那一题更简单一些，因为我们查询的时候要的都是包含左（右）端点的最长合法子串，于是我们并不需要维护区间最大值。

查询的时候直接合并答案就好了。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int t,n,ql[300005<<2][2],qr[300005<<2][2],len[300005<<2],ans;
char c[300005];
struct element
{
    int q[2],len;
    element()
    {
        q[0]=q[1]=len=0;
    }
};
inline int ls(int k)
{
    return k<<1;
}
inline int rs(int k)
{
    return k<<1|1;
}
inline void push_up(int k)
{
    len[k]=len[ls(k)]+len[rs(k)];
    ql[k][0]=ql[ls(k)][0];
    ql[k][1]=ql[ls(k)][1];
    qr[k][0]=qr[rs(k)][0];
    qr[k][1]=qr[rs(k)][1];
    if(ql[ls(k)][0]==len[ls(k)])
        ql[k][0]+=ql[rs(k)][len[ls(k)]&1];
    if(ql[ls(k)][1]==len[ls(k)])
        ql[k][1]+=ql[rs(k)][(len[ls(k)]&1)^1];
    if(qr[rs(k)][0]==len[rs(k)])
        qr[k][0]+=qr[ls(k)][len[rs(k)]&1];
    if(qr[rs(k)][1]==len[rs(k)])
        qr[k][1]+=qr[ls(k)][(len[rs(k)]&1)^1];
}
void build(int k,int l,int r)
{
    if(l==r)
    {
        len[k]=1;
        ql[k][c[l]=='R']=qr[k][c[l]=='R']=1;
        ql[k][c[l]=='L']=qr[k][c[l]=='L']=0;
        return;
    }
    int mid=(l+r)>>1;
    build(ls(k),l,mid);
    build(rs(k),mid+1,r);
    push_up(k);
}
element query1(int node,int l,int r,int k)
{
    if(r<=node)
    {
        element res;
        res.len=len[k];
        res.q[0]=qr[k][0];
        res.q[1]=qr[k][1];
        return res;
    }
    int mid=(l+r)>>1;
    element res,tmp;
    tmp=query1(node,l,mid,ls(k));
    if(mid<node)
        res=query1(node,mid+1,r,rs(k));
    if(!res.len&&!res.q[0]&&!res.q[1])
        return tmp;
    if(res.q[0]==res.len)
    {
        res.q[0]+=tmp.q[res.len&1];
        res.len+=tmp.len;
    }
    if(res.q[1]==res.len)
    {
        res.q[1]+=tmp.q[(res.len&1)^1];
        res.len+=tmp.len;
    }
    return res;
}
element query2(int node,int l,int r,int k)
{
    if(l>=node)
    {
        element res;
        res.len=len[k];
        res.q[0]=ql[k][0];
        res.q[1]=ql[k][1];
        return res;
    }
    int mid=(l+r)>>1;
    element res,tmp;
    tmp=query2(node,mid+1,r,rs(k));
    if(mid>=node)
        res=query2(node,l,mid,ls(k));
    if(!res.len&&!res.q[0]&&!res.q[1])
        return tmp;
    if(res.q[0]==res.len)
    {
        res.q[0]+=tmp.q[res.len&1];
        res.len+=tmp.len;
    }
    if(res.q[1]==res.len)
    {
        res.q[1]+=tmp.q[(res.len&1)^1];
        res.len+=tmp.len;
    }
    return res;
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(register int i=1;i<=n;++i)
        {
            c[i]=getchar();
            if(c[i]!='L'&&c[i]!='R')
                c[i]=getchar();
        }
        build(1,1,n);
        for(register int i=1;i<=n+1;++i)
        {
            ans=1;
            if(i^1)
                ans+=query1(i-1,1,n,1).q[0];
            if(i^(n+1))
                ans+=query2(i,1,n,1).q[1];
            printf("%d ",ans);
        }
        puts("");
    }
    return 0;
}
```


---

## 作者：henrytb (赞：2)

由于路的方向在人每走一格就会变，因此，一个人能从他所在的点走出去，当且仅当他走的路的初始方向是**左右交替**的且一开始出去的那条路是出去的方向。这样左右交替的路交替地变方向，每一次都是他要的方向。另外，由于他走过的路左右交替，他还可以原路返回去另一个方向走。

因此，我们需要预处理一个点往左的最长交替路径和一个点往右的最长交替路径的长度。

开一个数组 $f_{i,0/1}$ 表示点 $i$ 向左的路的初始方向是 **左/右** 时，向左的最长交替路径。$g_{i,0/1}$ 表示点 $i$ 向右的路的初始方向是 **右/左** 时，向右的最长交替路径。

可以发现这个 $f,g$ 都可以线性递推。

$$f_{i,0}=\left\{\begin{matrix}
f_{i-1,1}+1 & s[i]=L\\ 
0 & s[i]=R
\end{matrix}\right.$$

$$f_{i,1}=\left\{\begin{matrix}
f_{i-1,0}+1 & s[i]=R\\ 
1 & s[i]=L
\end{matrix}\right.$$

$$g_{i,0}=\left\{\begin{matrix}
g_{i+1,1}+1 & s[i]=R\\ 
0 & s[i]=L
\end{matrix}\right.$$

$$g_{i,1}=\left\{\begin{matrix}
g_{i+1,0}+1 & s[i]=L\\ 
1 & s[i]=R
\end{matrix}\right.$$

答案即为 $f_{i,0}+g_{i+1,0}+1$，$+1$ 是因为他本身就能到他自己所在的地方。

代码：

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int N=3e5+5;
int _,n;
char s[N];
int f[N][2],g[N][2];
int main() {
    for(scanf("%d",&_);_;--_) {
        scanf("%d",&n);
        rep(i,0,n+1) f[i][0]=f[i][1]=g[i][0]=g[i][1]=0;
        scanf("%s",s+1);
        rep(i,1,n) {
            if(s[i]=='L') f[i][0]=f[i-1][1]+1,f[i][1]=0;
            else f[i][1]=f[i-1][0]+1,f[i][0]=0;
        }
        per(i,n,1) {
            if(s[i]=='R') g[i][0]=g[i+1][1]+1,g[i][1]=0;
            else g[i][1]=g[i+1][0]+1,g[i][0]=0;
        }
        rep(i,0,n) {
            printf("%d ",f[i][0]+g[i+1][0]+1);
        }
        puts("");
    }
    return 0;
}
```

---

## 作者：Prean (赞：2)

场上 $ O(n) $ 切掉的一道挺水的题。

首先向左走和向右走，一个很明显的结论是，如果向左走了一段距离又回到原点，那么方向是不会变的，所以只需要求出能够向左走的最远距离和向右走的最远距离，加起来即可。

看上去是 $ O(n^2) $ 的，实际上能够递推。

设 $ L[i] $ 是 $ i $ 向左走的最远距离，$ R[i] $ 是 $ i $ 向右走的最远距离。

当 $ i \leq n \And 2 \leq i $ 时，若从 $ i $ 开始能向左走 $ 2 $ 格（此时道路方向还原，那么相当于可以从 $ i-2 $ 开始走），$ L[i] = L[i-2]+2 $，$ R[i] $ 累死。

对于 $ 0,1,n-1,n $ 可以特判。

code:
```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
typedef long long ll;
const int M=3e5+5; 
int T,n,L[M],R[M];bool a[M];char s[M];
signed main(){
	register int i;
	scanf("%d",&T);
	while(T--){
		scanf(" %d%s",&n,s+1);
		for(i=1;i<=n;++i)a[i]=s[i]=='L';
		R[n]=0;R[n-1]=!a[n];
		L[0]=0;L[1]=a[1];
		for(i=n-2;i>=0;--i){
			if(!a[i+1]){
				if(a[i+2])R[i]=R[i+2]+2;
				else R[i]=1;
			}
			else R[i]=0;
		}
		for(i=2;i<=n;++i){
			if(a[i]){
				if(!a[i-1])L[i]=L[i-2]+2;
				else L[i]=1;
			}
			else L[i]=0;
		}
		for(i=0;i<=n;++i)printf("%d ",L[i]+R[i]+1);printf("\n");
	}
}
```

---

## 作者：cqbzhzf (赞：1)

### 思路
- 注意读题，每走一步，**所有道路**都会翻转。所以如果走过的步数为偶数步，对所有的道路没有就没有影响。进一步说，如果从 $i$ 出发，走了 $x$ 步后回到原地，总步数为 $2\times x$ 步，所以所有的道路没有变化，也就是说从 $i$ 出发先向哪个方向走对最终的答案**没有影响**。
- 如果当前处于 $i$，那么想要走到 $i+1$，必须要满足字符串为 `LR` 或 `RL` 这样的**交替字符串**，所以令 $L_i$ 为 $i$ 出发向左最长的交替字符串的位置，$R_i$ 同理，那么当前位置的答案为 $R_i-L_i+1$。
- 问题转化为求出 $L_i$ 和 $R_i$，使用 DP 解决即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int t,n,cnt[N],L[N][2],R[N][2];
string s;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>s;
		for(int i=0;i<=n;i++) 
			R[i][0]=R[i][1]=L[i][0]=L[i][1]=i; 
		for(int i=1;i<=n;i++) 
			cnt[i]=(s[i-1]=='L');//cnt[i]为 1 时向左，为 0 时向右
		for(int i=n-1;i>=0;i--)
			R[i][cnt[i+1]]=R[i+1][!cnt[i+1]];
		for(int i=1;i<=n;i++) 
			L[i][cnt[i]]=L[i-1][!cnt[i]];//当前位置和下一个位置方向不同才能转移
        //注意 L 和 R 转移状态的方向不同
		for(int i=0;i<=n;i++)
		{
			int l=i,r=i;
			if(i!=0&&cnt[i]==1) 
				l=L[i][cnt[i]];
			if(i!=n&&cnt[i+1]==0) 
				r=R[i][cnt[i+1]];//注意 i 的范围
			cout<<r-l+1<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：_xm_ (赞：1)

## [CF1476D Journey](https://codeforces.com/problemset/problem/1476/D)（\*1700）

我们通过手玩我们可以发现：

- 向右走需要经过一段形式为 $\texttt{(RLRL...)}$ 的字符串，

- 向左走则需要经过一段形式为 $\texttt{(LRLR...)}$ 的字符串。

题目要求我们找到每个位置能延伸的最远边界。

由于向左和向右的处理方式相同，我们先考虑向右的边界。

设 $f_{i}$ 为字符串 $s_{i \ .. \ n}$ 向右延伸的最大边界长度。我们可以通过暴力搜索每个位置的边界，但这样做的时间复杂度为 $O(n^2)$，显然不可接受。

通过观察字符串 $\texttt{...(RLRLRL)L}$，我们可以发现，当前边界的偶数长度后缀也是合法边界。基于这一点，我们可以得出 $f_{i}$ 的递推关系：$f_i=f_{i-2}-2$。如果 $f_{i-2} - 2 \le 0$，则说明 $f_{i}$ 无法作为合法边界的后缀，此时我们暴力向右扩展。

每当暴力扩展 $k$ 次时，会更新 $\frac{k}{2}$ 个位置的答案。均摊复杂度 $O(n)$。

## Code:

```cpp
// by xm
// 2024.11.13
// Problem: D. Journey
// Contest: Codeforces - Educational Codeforces Round 103 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/1476/D
// Memory Limit: 512 MB
// Time Limit: 2000 ms

#include <bits/stdc++.h>
using namespace std;
using ll = long long; using ull = unsigned long long; using pll = pair<ll, ll>;
using ld = long double; using pdd = pair<ld, ld>; template <typename T> using Matrix = vector<vector<T>>;
void fileIO(const string& x) { freopen((x + ".in").c_str(), "r", stdin), freopen((x + ".out").c_str(), "w", stdout); }
template<typename T1, typename T2> bool chkmin(T1& x, const T2& y) { bool flag = (y < x); x = (y < x) ? y : x; return flag; }
template<typename T1, typename T2> bool chkmax(T1& x, const T2& y) { bool flag = (y > x); x = (y > x) ? y : x; return flag; }

const ll N = 3e5 + 5, Inf = 1e18, Mod = 1e9 + 7;

const char t1[] = {'R', 'L'}, t2[] = {'L', 'R'};

ll test_case = 1, n, f[N], g[N];
char s[N];

void solution() {
	cin >> n >> (s + 1);
	for(int i = 0; i <= n + 2; i++) f[i] = g[i] = 0;
	
	for(int i = 1; i <= n; i++) {
		f[i] = max(f[i - 2] - 2, 0ll);
		
		if(f[i] == 0) { // 暴力拓展
			ll& len = f[i];
			while(s[i + len] == t1[len % 2]) len++;
		}
	}
	
	for(int i = n; i >= 1; i--) {
		g[i] = max(g[i + 2] - 2, 0ll);
		
		if(g[i] == 0) { // 暴力拓展
			ll& len = g[i];
			while(s[i - len] == t2[len % 2]) len++;
		}
	}
	
	for(int i = 0; i <= n; i++) {
		cout << f[i + 1] + g[i] + 1 << " ";
	}
	cout << "\n";
}

double start_time, end_time;
int main() {
	//fileIO("");
	ios::sync_with_stdio(false), cin.tie(nullptr);
	start_time = clock(); cin >> test_case; while(test_case--) solution(); end_time = clock();
	cerr << 1000 * (end_time - start_time) / CLOCKS_PER_SEC << "ms\n";
	return 0;
}
```

---

## 作者：_RainCappuccino_ (赞：0)

> $\mathtt{TAGS}$：图论，DP，DSU

一种图论建模做法。

# First. 建模
每次走完图反转，所以，不妨建两层图：正图和反图，连边由正图向反图连无向边。这样就实现了每次移动反转图。

# Second. 求答案

很显然，对于每个点的答案就是从正图出发，多少点与正图中的该点联通。

由于是无向图，所以并查集维护集合大小即可。

每次合并，将集合大小也合并就行了。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int , int> pi;
#define endl '\n'
const int N = 1e6 + 10;
int n;
string s;
int siz[N];
int fa[N];
int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}
void merge(int x , int y) {
    x = find(x) , y = find(y);
    if (x == y) return;
    fa[y] = x , siz[x] += siz[y];
}

signed main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        cin >> s;
        s = '.' + s;
        for (int i = 0; i <= n * 2 + 1; i++) siz[i] = 1 , fa[i] = i;
        for (int i = 1; i <= n; i++) {
            if (s[i] == 'L') merge(i , i - 1 + n + 1);
            else merge(i - 1 , i + n + 1);
        }
        for (int i = 0; i <= n; i++) {
            cout << siz[find(i)] << ' ';
        }
        cout << endl;
    }
    return 0;
}
```

---

## 作者：hjqhs (赞：0)

从 edge+vscode 转 chrome+cpeditor 且大改码风的第一道题，写题解纪念一下。  
容易想到，如果可以一直往左，则路径一定是 `RLRLRLRL`，并且一定在 `LL` 处返回。而如果一直往右，则路径一定是 `RLRLRLRL`，并且一定在 `RR` 处返回。  
所以设 $l_i$ 为第 $i$ 个点向左可以走到的距离，$r_i$ 为第 $i$ 个点向右可以走到的距离。对于第 $i$ 个点，答案即为 $l_i+r_i+1$。  
按上述说法转移即可，注意 $l$ 从左往右转移，$r$ 从右往左转移。
```cpp
// Problem: D. Journey
// Contest: Codeforces - Educational Codeforces Round 103 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1476/problem/D
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Created Time: 2023-11-18 19:58:57
// Author: hjqhs
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i <= b; ++ i)
#define per(i, a, b) for (int i = a; i >= b; -- i)

using namespace std;

const int N = 300005;

int T;
int n, l[N], r[N];
char s[N];

void solve () {
	memset(l, 0, sizeof(l));
	memset(r, 0, sizeof(r));
	memset(s, 0, sizeof(s));
	
	cin >> n >> (s + 1);
	
	l[0] = r[n] = 0;
	l[1] = (s[1] == 'L');
	r[n - 1] = (s[n] == 'R');
	
	// cout << "debug " << l[1];
	
	rep (i, 2, n) {
		if (s[i - 1] == 'R' && s[i] == 'L') {
			l[i] = l[i - 2] + 2;
		} else if (s[i - 1] == 'L' && s[i] == 'L') {
			l[i] = 1;
		} else {
			l[i] = 0;
		}
	}
	
	per (i, n - 2, 0) {
		if (s[i + 1] == 'R' && s[i + 2] == 'L') {
			r[i] = r[i + 2] + 2;
		} else if (s[i + 1] == 'R' && s[i + 2] == 'R') {
			r[i] = 1;
		} else {
			r[i] = 0;
		}
	}
	
	// rep (i, 0, n) cout << l[i] << ' ' << r[i] << '\n';
	rep (i, 0, n) cout << l[i] + r[i] + 1 << ' ';
	cout << '\n';	
	
	return void();
}

int main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	
	cin >> T;
	while (T --) {solve(); } 
	
	return 0;
}
```

---

## 作者：chlchl (赞：0)

还是蛮简单的一道题，能看出来非常 CF。

## Solution
显然能够观察出来，一个点能向右走当且仅当它右边的边形成“RLRLRLRL……”的形状（向左走类似）。因为每走一步都会变向。

然后我们发现，如果能够走到某个点，那么必然可以从那个点走回来。这是显而易见的，因为走到这个点之后边反向，可以沿着原路回去，它此时必然指向回家的路。

那么我们的核心思路就是求出从每个点出发向两边延伸连续最长的“LRLRLR……”长度（记为 $l_i,r_i$），那么最后输出 $l_i+r_i+1$ 即可。

这个 $l,r$ 数组可以递推实现：
- $s_{i}=L,s_{i-1}=R$：$l_i=l_{i-2}+2$；
- $s_{i}=L,s_{i-1}\neq R$：$l_i=1$；
- $s_{i}=R$：$l_i=0$。



$r$ 数组的递推相似的，不过注意枚举顺序，具体可以看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 10;
int T, n, l[N], r[N];
char s[N];

void solve(){
	scanf("%d", &n);
	for(int i=0;i<=n;i++)
		l[i] = r[i] = 0;
	scanf("%s", s + 1);
	if(s[1] == 'L')
		l[1] = 1;
	for(int i=2;i<=n;i++){
		if(s[i] == 'L' && s[i - 1] == 'R')
			l[i] = l[i - 2] + 2;
		else if(s[i] == 'L')
			l[i] = 1;
	}
	if(s[n] == 'R')
		r[n - 1] = 1;
	for(int i=n-2;i>=0;i--){
		if(s[i + 1] == 'R' && s[i + 2] == 'L')
			r[i] = r[i + 2] + 2;
		else if(s[i + 1] == 'R')
			r[i] = 1;
	}
	for(int i=0;i<=n;i++)
		printf("%d ", l[i] + r[i] + 1);
	printf("\n");
	return ;
}

int main(){
	scanf("%d", &T);
	while(T--)
		solve();
	return 0;
}
```


---

