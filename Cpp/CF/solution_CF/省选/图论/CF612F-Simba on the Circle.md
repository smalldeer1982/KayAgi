# Simba on the Circle

## 题目描述

环形的数组上有若干个编号为1-n的n个数字， 每个数字大小为$a_i$ ($ -10^9 \le a_i \le 10^9$), 现在机器人辛巴从编号为s的位置出发， 可以朝着顺时针方向或逆时针方向行走， 但是行走需要是不降的序列（也就是下一个位置的数字不小于上一次位置对应的数字）， 并且所有的数字都要被选到， 假设一次行走移动会耗费1的单位时间， 请问辛巴怎么行走移动所花费的时间最少，输出最少时间和行走移动的操作。

## 样例 #1

### 输入

```
9 1
0 1 2 2 2 1 0 1 1
```

### 输出

```
12
+0
-3
-1
+2
+1
+2
+1
+1
+1
```

## 样例 #2

### 输入

```
8 1
0 1 0 1 0 1 0 1
```

### 输出

```
13
+0
+2
+2
+2
-1
+2
+2
+2
```

## 样例 #3

### 输入

```
8 1
1 2 3 4 5 6 7 8
```

### 输出

```
7
+0
+1
+1
+1
+1
+1
+1
+1
```

## 样例 #4

### 输入

```
8 1
0 0 0 0 0 0 0 0
```

### 输出

```
7
+0
+1
+1
+1
+1
+1
+1
+1
```

# 题解

## 作者：grass8cow (赞：4)

题目大意：

给定 $n$ 和 $m$ ，表示 $n$ 个点的环，你开始在点 $m$ 。每个点有权值 $a_i$ ，你走到一个点后可以把 $a_i$ 输出来，问你最少走多少步，能使输出的权值从小到大。输答案以及方案。


先前开了这道题，因为同权值间的转移想麻烦弃了……

### Part 1 思路

权值从小到大，明显 dp：$f_i$ 表示 $\le a_i$ 的点全部走完，来到 $i$ 的最小路程。

先离散化一下。

那么就要考虑，对于 $a_i+1=a_j$ 该如何转移。

设所有从小到大 $a_p=a_j$ 的数为 $p_0,p_1,……,p_{n-1}$ ,其中 $p_k=j$

一个结论：$i$ 必然先走到 $p_{k-1}$ 或 $p_{k+1}$ ，再绕一圈，经过所有 $p$ 后回到 $j$。

那么有 $f_i+d(i,p_{k-1})+d_2(p_{k-1},j)->f_j$ 以及 $f_i+d(i,p_{k+1})+d_2(p_{k+1},j)->f_j$

这个结论为什么是对的?如果走其他点，相对 $p_{k-1}$ 或 $p_{k+1}$ ，打打草稿，必然会有冗余的路径。

### Part 2 实现

有人觉得输方案麻烦？把同权值的丢进一个 $vector$ ，按题目实现就好了。那种 $n-1$ 到 $0$ 的，大不了多讨论一下就好了。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int I=1e9;
int n,m,dp[2010],a[2010],qc[2010],p;
vector<int>g[2010];
int d(int a,int b){return min(abs(a-b),n-abs(a-b));}
struct node{int f,ty;};
node min(node a,node b){if(a.f<b.f)return a;return b;}
node dis(int t,int p,int x){
	int sz=g[t].size();
	if(sz==1)return (node){d(p,g[t][x]),0};
	node ans=(node){I,0};
	if(x>0)ans=min(ans,(node){d(g[t][x-1],p)+n-(g[t][x]-g[t][x-1]),-1});
	else ans=min(ans,(node){d(g[t][sz-1],p)+(g[t][sz-1]-g[t][0]),-1});
	if(x<sz-1)ans=min(ans,(node){d(g[t][x+1],p)+n-(g[t][x+1]-g[t][x]),1});
	else ans=min(ans,(node){d(g[t][0],p)+(g[t][sz-1]-g[t][0]),1});
	return ans;
}
void pri(int co,int now,int x){
	int o=dis(co,now,x).ty,sz=g[co].size(),tr=g[co][(x+o+sz)%sz];
	if(abs(now-tr)<n-abs(now-tr))printf("%c%d\n",(now<=tr)?'+':'-',abs(now-tr));
	else printf("%c%d\n",(now>=tr)?'+':'-',n-abs(now-tr));
	if(!o)return;
	if(o==1){
		int p=(x+1)%sz;
		while(p!=x){
			if(p<sz-1)printf("+%d\n",g[co][p+1]-g[co][p]);
			else printf("+%d\n",n-(g[co][sz-1]-g[co][0]));
			p=(p+1)%sz;
		}
	}
	else{
		int p=(x-1+sz)%sz;
		while(p!=x){
			if(p)printf("-%d\n",g[co][p]-g[co][p-1]);
			else printf("-%d\n",n-(g[co][sz-1]-g[co][0]));
			p=(p-1+sz)%sz;
		}
	}
}
void print(int i,int j){
	if(!i){pri(i,m,j);return;}
	for(int k=0;k<g[i-1].size();k++)if(dp[g[i-1][k]]+dis(i,g[i-1][k],j).f==dp[g[i][j]]){
		print(i-1,k);
		pri(i,g[i-1][k],j);break;
	}
}
int main(){
	scanf("%d%d",&n,&m);m--;
	for(int i=0;i<n;i++)scanf("%d",&a[i]),qc[i]=a[i];
	sort(qc,qc+n);p=unique(qc,qc+n)-qc;
	for(int i=0;i<n;i++)g[a[i]=lower_bound(qc,qc+p,a[i])-qc].push_back(i);
	memset(dp,0x3f,sizeof(dp));
	for(int i=0;i<g[0].size();i++)dp[g[0][i]]=min(dp[g[0][i]],dis(0,m,i).f);
	for(int i=1;i<p;i++)
		for(int j=0;j<g[i-1].size();j++)
			for(int k=0;k<g[i].size();k++)dp[g[i][k]]=min(dp[g[i][k]],dp[g[i-1][j]]+dis(i,g[i-1][j],k).f);
	int ans=1e9,id=-1;
	for(int i=0;i<g[p-1].size();i++)if(dp[g[p-1][i]]<ans)ans=dp[g[p-1][i]],id=i;
	printf("%d\n",ans);print(p-1,id);
	return 0;
}
```

---

## 作者：Hovery (赞：4)

首先不难想到按 $a_i$ 的值分层。

这样是需要处理完一层再去处理下一层。

设 $g_i$ 表示把前几层走完，$i$ 所在的层以 $i$ 为起点开始遍历的最小值。

$f_i$ 表示把前几层走完，$i$ 所在的层以 $i$ 为终点的最小值。

环这个条件十分的麻烦，不妨把原序列复制一遍以消除环的限制。

由于你算到当前层时上一层的 $f$ 值已经全部算出，可以直接把当前层的 $g$ 值预处理出来，复杂度 $\Theta(n^2)$。

设当前层的点的个数为 $siz$。

那么把序列复制过后就会产生 $siz$ 个区间包含当前层的 $siz$ 个元素。

先考虑枚举这个区间，然后再在这个区间里枚举那个点作为终点。

我们假设已经知道了一个点是起点，考虑怎么算答案。

不难发现，最优策略一定是下面两种情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/gekmq8tx.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/fmqbk23w.png)

设 $sum_i$ 表示当前区间左端点到 $i$ 的距离。

那么答案就是：

$\begin{cases}
  sum_r-sum_l+sum_s-sum_l+sum_r-sum_t+g_s & s\le t\\
  sum_r-sum_s+sum_r-sum_l+sum_t-sum_l+g_s & s\ge t \\
\end{cases}$

我们知道 $l,r,t$ 但就是不知道 $s$。

考虑把与 $s$ 有关的提出来 $sum_s+g_s-sum_l,g_s+sum_r-sum_s$。

这里把别的提出来是方便理解。

然后你再做一遍前缀后缀 $\min$ 就可以做到不用枚举这个 $s$。

总时间复杂度 $\Theta(n^2)$。

## Code

没有写输出路径，请谅解。

```
#include<bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;

int n, s, a[4010], pre[4010], suf[4010], b[4010];
vector<int> G[4010];
int sum[4010];
int _1[4010], _2[4010];

int calc(int x,int y)
{
    if (y > n)
    y -= n;
    if (x > y)
    return calc(y, x);
    return min(y - x, abs(n - y + x));
}

signed main()
{
    cin >> n >> s;
    for (int i = 1;i <= n;i++)
    {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    int cnt = unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1;i <= n;i++)
    {
        a[i] = lower_bound(b + 1, b + cnt + 1, a[i]) - b;
        G[a[i]].pb(i);
    }
    int tmp = cnt;
    for (int i = 1;i <= tmp;i++)
    {
        int siz = G[i].size();
        cnt = 0;
        for (int j = 0;j < siz;j++)
        {
            b[++cnt] = G[i][j];
            b[cnt + siz] = G[i][j] + n;
        }
        cnt = 2 * siz;
        for (int j = 1;j <= cnt;j++)
        {
            _1[b[j]] = _2[b[j]] = 1e9;
        }
        sum[1] = 0;
        for (int j = 2;j <= cnt;j++)
        {
            sum[j] = sum[j - 1] + b[j] - b[j - 1];
        }
        if (i == 1)
        {
            for (int j = 1;j <= cnt;j++)
            {
                _1[b[j]] = min(_1[b[j]], calc(s, b[j]));
            }
        }
        else {
            for (int j = 1;j <= cnt;j++)
            {
                for (auto k : G[i - 1])
                {
                    _1[b[j]] = min(_1[b[j]], calc(b[j], k) + _2[k]);
                }
            }
        }
        if (siz == 1)
        {
            for (int j = 1;j <= cnt;j++)
            {
                _2[b[j]] = _1[b[j]];
            }
        }
        else
        {
            for (int j = 1;j <= cnt - siz + 1;j++)
            {
                pre[j - 1] = 1e8;
                for (int k = j; k <= j + siz - 1;k++)
                {
                    pre[k] = min(pre[k - 1], _1[b[k]] + sum[k] - sum[j]);
                }
                suf[j + siz] = 1e8;
                for (int k = j + siz - 1;k >= j;k--)
                {
                    suf[k] = min(suf[k + 1], _1[b[k]] + sum[j + siz - 1] - sum[k]);
                }
                for (int k = j;k <= j + siz - 1;k++)
                {
                    _2[b[k]] = min({_2[b[k]], pre[k - 1] + 2 * sum[j + siz - 1] - sum[j] - sum[k], suf[k + 1] + sum[j + siz - 1] - sum[j] + sum[k] - sum[j]});
                }
            }
        }
        for (int j = 1;j <= siz;j++)
        {
            _2[b[j]] = min(_2[b[j]], _2[b[j] + n]);
        }
    }
    int ans = 1e17;
    for (auto i : G[tmp])
    {
        ans = min(ans, _2[i]);
    }
    cout << ans;
}
```

---

## 作者：ilibilib (赞：3)

[可能不会更好的体验](https://www.cnblogs.com/ilibilib/p/18535213)

## 分析：

对于输出答案真的很好做，然后被输出路径恶心到了。。。



上来先离散化 + 去重简化题目，用 $v[i]$ 记录权值为 $i$ 的点，$a[i]$ 为点 $i$ 的权值。

那么行径的每一步可以分为两类：

1. 从 $v[i]$ 内的点到 $v[i+1]$ 的点。

2. 从 $v[i]$ 内的点到 $v[i]$ 内的点。

设 $dp[i]$ 为走完了所有权值**小于等于** $a[i]$ 的点后留在了 $i$ 的最小花费。

设 $f[i]$ 为走完了所有权值**小于** $a[i]$ 的点(以及 $i$ 本身)后留在了 $i$ 的最小花费。

我们发现由 $dp[x]$ 推出 $f[y]$ $(a[y]=a[x]+1)$ 便是第一类步，由 $f[x]$ 推出 $dp[y]$ $(a[x]=a[y])$为第二类步。



第一类很好处理：

$$f[y]=\min(dp[x]+\min(abs(x-y),n-abs(x-y)))(y\in v[a[y]-1])$$

$\min(abs(x-y),n-abs(x-y))$ 即是考虑图是环形，$f[y]$ 为走完了所有权值**小于** $a[y]$ 的点后留在 $y$ 的花费，应该由一个已经处理了所有权值**小于等于** $a[y]-1$ 的地方推来的，即是属于 $v[a[y]-1]$ 的 $x$ 的 $dp[x]$。



第二类：

![](https://cdn.luogu.com.cn/upload/image_hosting/roidud0h.png)

请不要在意中间的三座火山，两座活火山，一座死火山...那只是心血来潮的产物，大人总是需要我来解释，这让我很心累（。

显然要求从一个点出发然后遍历完所有的点，最后停留在一个点便是从 $f$ 的状态变为了 $dp$ 的状态了。

从 $x$ 出发到 $y$。

如果 $y$ 与 $x$ 不相邻，显然要求从 $x$ 出发转一圈后停在与 $x$ 相邻的一个点后再返回 $y$，这必然不会优于直接停留在那个与 $x$ 相邻的点，因此只用考虑 $x$ 与 $y$ 相邻两种情况（左右）了。

## code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e3+10;
int a[N],b[N],dp[N],f[N];
vector<int>v[N];
int main()
{
    int n,cnt=0,m=0,s;
    cin>>n>>s;
    for(int i=1;i<=n;++i) cin>>a[i],b[++m]=a[i];
    sort(b+1,b+n+1);m-=b+m+1-unique(b+1,b+n+1);
    for(int i=1;i<=n;++i) a[i]=lower_bound(b+1,b+m+1,a[i])-b,v[a[i]].push_back(i);
    memset(dp,63,sizeof(dp));memset(f,63,sizeof(f));
    for(int i=1;i<=m;++i)
    {
        for(auto x:v[i])
        {
            if(i==1) {int y=s;dp[x]=min(dp[x],min(abs(x-y),n-abs(x-y)));}
            else {for(auto y:v[i-1]) dp[x]=min(dp[x],dp[y]+min(abs(x-y),n-abs(x-y)));};
        }
        if(v[i].size()==1) continue;
        for(int j=0;j<v[i].size();++j)
        {
            int x=v[i][j],y,w1,w2;
            if(j!=0) y=v[i][j-1],w1=dp[y]+n-(x-y);
            else y=v[i][v[i].size()-1],w1=dp[y]+y-x;
            if(j!=v[i].size()-1) y=v[i][j+1],w2=dp[y]+n-(y-x);
            else y=v[i][0],w2=dp[y]+x-y;
            f[x]=min(w1,w2);
        }
        for(auto x:v[i]) dp[x]=f[x];
    }
    int ed=0;
    for(auto x:v[m]) if(dp[x]<dp[ed]) ed=x;
    cout<<dp[ed]<<'\n';
    return 0;
}
```

至于输出路径？只需要简单地在记录最小值时记录是从哪儿推出的就行了...有些繁琐但只需要注意点细节就行了，所以不在此赘述。

完整代码：[Submission #265943935 - Codeforces](https://codeforces.com/contest/612/submission/265943935)

---

## 作者：EityDawn (赞：3)

## 思路：

观察发现：

起点一定是最小的，终点一定是最大的。

在相同大小的数字间走，一定是走离他最近的大小相同的位置，否则肯定不优。

先对点权进行离散化，然后对点权进行分类。

这一步就相当于将大环拆成了一个个小环，我们需要先在小环上 dp，从一个环转移到另一个环上，继续 dp。

不难发现，在同一个环内走的路径一定是以某点为起点，断开与它相邻的某点之间的边，形成的链的另一段就是我们的终点。

而从一个环走到另一个环上，只需枚举从哪里走过来就行啦。

我们再对问题进行转化：从最大的某点开始，走出不增序列。

那么我们不妨定义 $dp_i$ 为走完不小于 $a_i$ 的点停在 $a_i$ 最小花费。记 $i$ 的在所在环上前驱为 $pre_i$，后继为 $suf_i$。

设按权值分类分出了 $m$ 个环，每个环的总长为 $sum_i$。

初始时，最大点权的那个环上的每个点 $j$，有 $dp_j=\min(sum_i-dis(j,pre_j),sum_i-dis(j,suf_j))$，其中 $dis(i,j)$ 表示由 $i$ 走到 $j$ 的最短路径。转移时记录看哪一个做链头和链尾。

然后从点权大的环朝点权小的环转移，记录环之间从这个点从哪一个点来的。

现在还要考虑在相同点权之间怎么转移。

我们不妨再定义一个 $f_i$ 来帮助我们转移。每次从上一个环转移至当前环时，有 $f_j=\min(dp_{pre_j}+sum_i-dis(j,pre_j),dp_{suf_j}+sum_i-dis(j,suf_j))$。

转移完后，当前环上的 dp 值全部更新为 $f_i$。

最后确定终点位置，按照我们沿路记录的环上链头到链尾的方向输出同权值点间的路径，接着跳到链尾，从链尾跳到另一个环上时，输出一次路径，如此往复。

## code:

```cpp
#include<iostream>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<climits>
#include<queue>
#include<vector>
#include<map>
#include<set>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=2100;
int dp[N],f[N];
vector<int>S[N];
int a[N],b[N],n,st,ed;
int sum[N];
int last[N];
int nexts[N];
int calc(int x,int y)
{
    if(x>y) swap(x,y);
    return min(abs(x-y),abs(n-y+x));
}
#define siz(a) a.size()
#define all(a) a.begin(),a.end()
int pre[N],suf[N];
string go(int x,int y)
{
    string dir;
    if(x>y)
        dir=x-y<n-(x-y)?"-":"+";
    else dir=y-x<n-(y-x)?"+":"-";
    if(x>y) swap(x,y);
    int dis=calc(x,y);
    return dir+to_string(dis);
}
void init(int m)
{
    for(int i=1;i<=m;i++)
    {
        for(int j=0;j<siz(S[i]);j++)
            pre[S[i][j]]=S[i][(j-1+S[i].size())%S[i].size()],
            suf[S[i][j]]=S[i][(j+1+S[i].size())%S[i].size()];
    }
    return;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>st;
    for(int i=1;i<=n;i++) cin>>a[i],b[i]=a[i];
    sort(b+1,b+1+n);
    int m=unique(b+1,b+1+n)-(b+1);
    for(int i=1;i<=n;i++)
        a[i]=lower_bound(b+1,b+1+m,a[i])-b;
    for(int i=1;i<=n;i++)
        S[a[i]].push_back(i);
    init(m);
    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<=m;i++)
    {
        for(int now:S[i])
            sum[i]+=calc(now,suf[now]);
        if(i==m)
            for(int now:S[i])
            {
                int w1=sum[i]-calc(now,pre[now]),w2=sum[i]-calc(now,suf[now]);
                if(w1<w2) nexts[now]=pre[now];
                else nexts[now]=suf[now];
                dp[now]=min(w1,w2);
            }
                
    }
    for(int i=m-1;i;i--)
    {
        for(int to:S[i])
        {
            for(int from:S[i+1])
            {
                if(dp[from]+calc(to,from)<dp[to])
                    dp[to]=dp[from]+calc(to,from),last[to]=from;
            }
                
        }
        for(int now:S[i])
        {
            int w1=sum[i]-calc(now,suf[now])+dp[suf[now]],w2=sum[i]-calc(now,pre[now])+dp[pre[now]];
            if(w1<w2) nexts[now]=suf[now];
            else nexts[now]=pre[now];
            f[now]=min(w1,w2);
        }
        for(int to:S[i]) dp[to]=f[to];
    }
    int ans=2e9;
    for(int to:S[1])
        if(dp[to]+calc(st,to)<ans)ans=dp[to]+calc(st,to),ed=to;
    cout<<ans<<'\n';
    cout<<go(st,ed)<<'\n';
    for(int i=1;i<=m;i++)
    {
        int nt=lower_bound(all(S[i]),nexts[ed])-S[i].begin();
        if(S[i][nt]==pre[ed]){
            for(int now=ed;now!=pre[ed];now=suf[now])
                cout<<go(now,suf[now])<<'\n';
        }
        else{
            for(int now=ed;now!=suf[ed];now=pre[now])
                cout<<go(now,pre[now])<<'\n';
        }
        if(i^m) cout<<go(nexts[ed],last[nexts[ed]])<<'\n';
        ed=last[nexts[ed]];
    }
    return 0;
}
```

---

## 作者：ademik (赞：3)

### [Simba on the Circle](https://www.luogu.com.cn/problem/CF612F)

代码思路参考自 [bicsi](https://codeforces.com/profile/bicsi)，快去 %%% 他吧。 

---

我们可以按照权值将点分成几层，要求按照点权有小到大的顺序，且每次只有遍历完当前层上的所有节点后才能进入下一层，求遍历完所有节点所需要经过的路径总长。

考虑遍历每一层上所有节点所得到的路径形状：

![](https://s2.loli.net/2023/11/01/ZNeaHf8R46oJm3F.png)

我们进一步的考虑如何建图解决这个问题，对于在同一层中的节点，我们在两两相邻的节点建出一条边权为对应劣弧的长度的边即可，建边数为 $O(n)$，对于相邻的两层，我们需要对任意两个点建出一条建出一条他们之间的距离的边，以支持可以由当前层上的一点转移到下一层中的任意一点，建边数为 $O(n^2)$。此外，我们需要将一个点拆成一个出点和一个入点，以保证必须经过一个弧长才能转移到下一层节点。

然后用 dijkstra 跑一遍最短路即可，时间复杂度为 $O(n^2\log n)$。

至于输出路径，具体见代码解释。

---

```cpp
# include <bits/stdc++.h>
# define TIME 1e3 * clock() / CLOCKS_PER_SEC
# define debug(x) cerr <<(x) <<" "; 
using std :: cin; using std :: cout; using std :: max; 
using std :: min; using std :: cerr; using std :: abs; 
using std :: make_pair; using std :: vector; 
typedef long long i64; 
typedef std :: pair < int, int > pii; 
const int N = 1e5 + 50, Inf = 0x3f3f3f3f;
int n, m, idx, a[N], si; 
std :: map < int, int > id;
std :: vector < int > vec[N];
std :: vector < pii > e[N];  
int get_dis(int i, int j) { // 计算环上任意两点间的较短的弧的长度。  
	if(j < i) std :: swap(i, j); 
	return min(j - i, n + i - j); 
}  
void add_edge(int u, int v, int w) {
	e[u].push_back(make_pair(v, w)); 
}
int dis[N], pre[N]; bool vis[N]; 
void dijkstra()
{
	std :: priority_queue < pii, vector < pii >, std :: greater < pii > > q;
	memset(dis, 0x3f, sizeof(dis)); dis[0] = 0; 
	memset(vis, false, sizeof(vis)); vis[0] = false; 
	q.push(make_pair(dis[0], 0)); 
	while(!q.empty()) {
		int u = q.top().second; q.pop(); 
		if(vis[u]) continue; vis[u] = true; 
		for(auto __ : e[u]) {
			int v = __.first, w = __.second; 
			if(dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w; 
				pre[v] = u; 
				q.push(make_pair(dis[v], v)); 
			} 
		}
	}
	return; 
}
char get_note(int i, int j, int d = -1) { // 处理当前输出的符号问题 
	if(d == -1) d = get_dis(i, j); // 如果没有 d 传入 
	if(j == i + d || j == i + d - n) return '+'; // 顺时针方向 
	return '-'; 
}
int get_now(int id) {return id - (id > n ? n : 0);} // 计算 id 所代表的节点(出点 -> 入点) 
void print(int u)
{
	if(pre[u] == 0) { // 没有前驱节点，由初始的 si 到 u 点。  
		cout <<get_note(si, get_now(u)) <<get_dis(si, get_now(u)) <<"\n"; 
	} else {
		print(pre[u]); int v = pre[u]; 
		if(v > n && u <= n) { // v 是出度点， u 是入度点， 是层与层之间的连边， 可以直接输出 
			cout <<get_note(get_now(v), get_now(u)) <<get_dis(get_now(v), get_now(u)) <<"\n"; 
		} else { // 否则的话是层内的点的连边， 所代表的是一段弧线而不仅仅是一条边 
			int d = dis[u] - dis[v]; // v 到 u 的边权大小 
			char ch; int flag, x = 0;
			// 这里是判断弧整体的移动方向 
			if(get_note(get_now(v), get_now(u), d) == '+') ch = '+', flag = 1; 
			else ch = '-', flag = -1; 
			// 枚举这段弧上所有的点， 如果点权相等， 即是一条路径。  
			for(int pos = get_now(v) + flag, i = 1; i <= d; i ++, pos += flag) {
				if(pos > n) pos -= n; if(pos <= 0) pos += n; 
				x ++; 
				if(a[pos] == a[get_now(v)]) cout <<ch <<x <<"\n", x = 0; 
			}
		}
	}
	return; 
} 
int main()
{
	std :: ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0); 
	cin >>n >>si; 
	for(int i = 1; i <= n; i ++) {
		cin >>a[i]; id[a[i]] = 1; 
	}
	for(auto &now : id) now.second = ++idx; 
	for(int i = 1; i <= n; i ++) {
		a[i] = id[a[i]]; vec[a[i]].push_back(i); 
	}
	for(int i = 1; i <= n; i ++) { // 层与层之间的连边。  
		for(int j = 1; j <= n; j ++) {
			if(a[j] != a[i] + 1) continue; 
			add_edge(i + n, j, get_dis(i, j)); 
		}
	}
	for(int i = 1; i <= idx; i ++) {
		if(vec[i].size() == 1) { // 只有一个点的情况下可以直接从入点到出点。  
			add_edge(vec[i].back(), vec[i].back() + n, 0);  
		} else { // 相邻的点之间连边 
			for(int j = 1; j < vec[i].size(); j ++) {
				int u = vec[i][j - 1], v = vec[i][j]; 
				add_edge(u, v + n, n - (v - u) /*v > n, 代表弧的长度*/); 
				add_edge(v, u + n, n - (v - u)); 
			}
			int u = vec[i][0], v = vec[i].back(); 
			add_edge(u, v + n, v - u); add_edge(v, u + n, v - u); 
		}
	}
	// 以 0 为源点， 向所有点权最小的点连边，表示可以从此处开始 。 
	for(int i = 1; i <= n; i ++) {
		if(a[i] == 1) add_edge(0, i, get_dis(si, i)); 
	}
	pre[0] = -1; dijkstra(); 
	int minn = Inf, pos = -1; 
	for(int i = 1; i <= n; i ++) {
		if(a[i] == idx && dis[i + n] < minn) {
			minn = dis[i + n]; pos = i; 
		}
	}
	cout <<minn <<"\n"; 
	print(pos + n); return 0; 	
}
```

---

## 作者：little_sheep917 (赞：1)

> 给出一个有 $n$ 个数的序列 . 所有元素从 $1$ 到 $n$ 顺时针排列成一个圈. 第 $i$ 个格子的数为 $a_i$ . 机器人一开始在位置 $s$ .
>
> 每一个时刻，机器人都在某个格子里. 接下来，它可以花费 $1$ 个时间顺时针和逆时针走 $1$ 格 . 或者，不花费时间地写下 $a_i$ ，每个格子里的数只能被写 $1$ 次.
>
> 机器人想用不降的顺序写下数列中的每一个数. 求写下序列中每个数需要花费的最小时间. 并且求出机器人的路径.
>
> $1\leq s\leq n\leq 2000,\ -10^9\leq a_i\leq 10^9$

首先，把 $a$ 离散化.

考虑有同色的情况，对于同色的情况，肯定是选取一个起始点，顺时针或者逆时针走到终止点 . 

那么，用 $dp(i,j)$ 表示用将要写第 $i$ 个数，在位置 $j$​ 的最小花费数 . 

预处理出每个节点开始，到同种颜色结束的最小步数和方向 .  

这样就可以处理 $dp(i,j)\rightarrow dp(i+1,k)$​ 的转移 .

对于 $dp(i,j)\rightarrow dp(i,k)$ 的转移，是一个环形的. 考虑用最短路求.

可以考虑用 bfs 和 dijkstra ,

但是 bfs 维护起来细节比 dijkstra 多，而且 dijkstra 的时间复杂度可能也不是跑得很满.

对于 $(i,j)\rightarrow (i,j-1)$ 和 $(i,j)\rightarrow (i,j+1)$ 分别建一条代价为 $1$​ 的边.

可以通过记录路径求出机器人写下数的顺序 .

对于机器人的路径，再预处理出相邻两点间的最短路径以及方向 .

时间复杂度 : $O(n^2\log n+n^2)$

空间复杂度 : $O(n)$

第一次提交 : Wrong answer on test 8

code

```c++
#include<bits/stdc++.h>
using namespace std;
const int inf=1e9+10;
int n,s;
int a[2010],cnt[2010];
int num=0;
map<int,int>Map;
int dp[2010][2010];
pair<int,int>fr[2010][2010];
pair<pair<int,int>,bool>b[2010];
//step endpos direction
pair<int,int>dis[2010][2010];
//step direction
priority_queue<pair<int,int> >Q;
vector<int>ans;
void get_ans(int i,int p){
	int li=fr[i][p].first,np=fr[i][p].second;
//	cout<<i<<" "<<p<<" "<<li<<" "<<np<<endl;
	if(li==-1)return;
	if(li+1==i){
		// from p -> np 
		int pos=p,dir=b[np].second;
		if(dir==0)dir=-1;
		else dir=+1;
		while(true){
			if(a[pos]==li){
			//	cout<<pos<<endl;
				ans.push_back(pos);
			}
			if(pos==np)break;
			pos=(pos+dir+n)%n;
		}
	}
	get_ans(li,np);
}
void bfs(int id){
	while(!Q.empty())Q.pop();
	for(int i=0;i<n;i++){
		Q.push(make_pair(-dp[id][i],i)); 
	}
	while(!Q.empty()){
		int val=Q.top().first,x=Q.top().second;
		Q.pop();
		if(dp[id][x]<val)continue;
		if(dp[id][(x+1)%n]>dp[id][x]+1){
			dp[id][(x+1)%n]=dp[id][x]+1;
			fr[id][(x+1)%n]=make_pair(id,x);
			Q.push(make_pair(-dp[id][(x+1)%n],(x+1)%n));
		} 
		if(dp[id][(x-1+n)%n]>dp[id][x]+1){
			dp[id][(x-1+n)%n]=dp[id][x]+1;
			fr[id][(x-1+n)%n]=make_pair(id,x);
			Q.push(make_pair(-dp[id][(x-1+n)%n],(x-1+n)%n));
		}
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>s;
	s--;
	for(int i=0;i<n;i++){
		cin>>a[i];
		Map[a[i]]=true;
	}
	for(map<int,int>::iterator it=Map.begin();it!=Map.end();it++){
		it->second=num++;
	}
	for(int i=0;i<n;i++)a[i]=Map[a[i]];
	for(int i=0;i<n;i++)cnt[a[i]]++;
	for(int i=0;i<2010;i++)for(int j=0;j<2010;j++){
		dp[i][j]=inf;
		fr[i][j]=make_pair(-1,-1);
		dis[i][j]=make_pair(inf,-1);
	}
	for(int i=0;i<n;i++){
		int j,sum,step;
		j=i;sum=1;step=0;
		while(true){
		//	cout<<a[j]<<","<<a[i]<<","<<sum<<","<<cnt[a[i]]<<endl;
			if(sum==cnt[a[i]]){
				b[i]=make_pair(make_pair(step,j),false);
				break;
			}
			j=(j+1)%n;
			if(a[j]==a[i])sum++;
			step++;
		}
		j=i;sum=1;step=0;
		while(true){
		//	cout<<a[j]<<","<<a[i]<<","<<sum<<","<<cnt[a[i]]<<endl;
			if(sum==cnt[a[i]]){
				b[i]=min(b[i],make_pair(make_pair(step,j),true));
				break;
			}	
			step++;
			j=(j-1+n)%n;
			if(a[j]==a[i])sum++;
		}
	//	cout<<i<<endl;
	}
	for(int i=0;i<n;i++){
		int step=0;
		dis[i][i]=make_pair(0,0);
		for(int j=i+1;;j++){
			int pos=j%n;
			if(pos==i)break;
			++step;
			dis[i][pos]=min(dis[i][pos],make_pair(step,0));
		}
		step=0;
		for(int j=i-1;;j--){
			int pos=(j+n)%n;
			if(pos==i)break;
			++step;
			dis[i][pos]=min(dis[i][pos],make_pair(step,1));
		}
	}
	dp[0][s]=0;
	for(int i=0;i<num;i++){
		bfs(i);
		for(int j=0;j<n;j++){
			if(a[j]==i){
			//	cout<<b[j].first.second<<" "<<dp[i][j]<<" "<<b[j].first.first<<endl;
				if(dp[i+1][b[j].first.second]>dp[i][j]+b[j].first.first){
					dp[i+1][b[j].first.second]=dp[i][j]+b[j].first.first;
					fr[i+1][b[j].first.second]=make_pair(i,j);
				}
			}
		}
	}
	int step=inf,pos=-1;
	for(int i=0;i<n;i++){
		if(dp[num][i]<step){
			step=dp[num][i];
			pos=i;
		}
	}
	cout<<step<<endl;
	get_ans(num,pos);
	ans.push_back(s);
	reverse(ans.begin(),ans.end());
//	for(int i=0;i<(int)ans.size();i++)cout<<ans[i]<<" ";
//	cout<<endl;	
	for(int i=1;i<(int)ans.size();i++){
		int be=ans[i-1],ed=ans[i];
		if(dis[be][ed].second==0)cout<<"+";	
		else cout<<"-";
		cout<<dis[be][ed].first<<"\n";
	}
	return 0;
}
/*inline? ll or int? size? min max?*/

```



---

## 作者：chenxia25 (赞：1)

这道题做的真是累死了……

----

显然，题目要求是要对于每一种数，依次输出所有等于这个值的位置，同一个值之间的输出顺序随便。

然后可以想到一个很自然的以数的值从小到大为阶段的 DP：$dp_{i,j}$ 表示第 $i$ 大的数值输出完后，停在 $j$ 最小步数。这样 DP 值数量是 $n^2$ 的，那么就意味着需要均摊 $\mathrm O(1)$ 转移/jk。但实际上这事可实现的。

我们考虑如何转移。我们考虑从决策（也就是起点）$k$ 跑到 $j$，并且中途经过所有该输出的位置，的最小步数的走法。显然 $j,k$ 把整个环分成两段，一段是 $k\to j$ 顺时针走，一段是逆时针（这里我们可以把时针方向等价到线性结构上来理解，顺时针走就是加，逆时针就是减）。那不难想到最优路线一定是先解决一部分，然后绕另一部分走到 $j$。后者显然可以完整地经过对应部分，而前者只需要走到最后一个该输出的位置就可以改变方向了。于是把这两种情况各自算然后取个 $\min$ 即可。

然后考虑其中一种情况怎么算（以先逆后顺为例）。我们考虑固定住 $j$，那么 $k\to j$ 的逆时针路线上的最后一个该输出的点显然只有两种可能：没有，或 $j$ 的顺时针方向第一个。设「$j$ 的顺时针方向第一个」为 $p$（$p$ 可以 two-pointers 算出来），我们考虑枚举 $j,k,p$ 的相对位置，对于每种位置显然可以列出简单式，不带分段和绝对值的。**到了这时候我们就应该拿出一整张空白的草稿纸，静下心来一类一类分类讨论，而不是一遍分类一边跟 hsc 聊天。**

| 序号 |                       图                       | $\ \ \ \ \ \ \ \ \ \ $ 式子 $\ \ \ \ \ \ \ \ \ \ $ |
| :--: | :--------------------------------------------: | :-----------------------------------------------------: |
| $1$  | ![](https://s3.ax1x.com/2020/12/22/rspjJK.png) |         $dp_{i-1,k}+n-(k-j)=(dp_{i-1,k}-k)+n+j$         |
| $2$  | ![](https://s3.ax1x.com/2020/12/22/rs9Ny4.png) |   $dp_{i-1,k}+n-(p-j)+(k-p)=(dp_{i-1,k}+k)+n-(p-j)-p$   |
| $3$  | ![](https://s3.ax1x.com/2020/12/22/rs95kt.png) | $dp_{i-1,k}+2n-(j-k)-2(p-j)=(dp_{i-1,k}+k)+2n-j-2(p-j)$ |
| $4$  | ![](https://s3.ax1x.com/2020/12/22/rsCPcF.png) |         $dp_{i-1,k}+n-(k-j)=(dp_{i-1,k}-k)+n+j$         |
| $5$  | ![](https://s3.ax1x.com/2020/12/22/rsCBuQ.png) |           $dp_{i-1,k}+(j-k)=(dp_{i-1,k}-k)+j$           |
| $6$  | ![](https://s3.ax1x.com/2020/12/22/rsPYqJ.png) |      $dp_{i-1,k}+2(k-p)+(j-k)=(dp_{i-1,k}+k)-2p+j$      |

其中前三类是 $p>j$ 的情况，后三类是 $p\leq j$，事实上只可能有一个得到满足，到时候 `if else` 一下即可。那么这样显然我们只需要维护区间 $dp_{i-1,k}+k$ 和 $dp_{i-1,k}-k$ 的最小值。其中有四类是可以直接前后缀的，还剩两类需要单调队列（因为注意到 $j,p$ 都单调且单调方向相同）。然后发现先顺后逆的情况，和上述六种情况是恰好成镜像的，把能反的都反过来（相对大小、式子里的符号、更新顺序），CV 然后改一改就好了。

然后最后还需要输出路径，就记录路径（不仅要记录转移对象，还要记录是先逆后顺还是先顺后逆）。非常难写。

**_[code]( https://www.luogu.com.cn/paste/5vrt3634 )_**

---

上面我自己 yy 的方法非常难推且难写，码量 4k，我昨天晚上做了 2h，今天放学回来又做了 1h。

然后看到 ymx 的题解，得出一个结论：凡是烦一点的题，我一定是做的最麻烦的人。

ymx 的 DP 是一维的，他的 DP 状态可以等价理解为，我的状态加上这么一个优化：只可能停留在当前数值的位置，然后再开一个表示当前阶段的开始位置，也是只能开始于当前数值的位置。**这样一来总状态数是线性的了。**$i-1\to i$ 的转移只需要暴力枚举转移对，然后 $i\to i$（也就是我的方法麻烦的主体）自然也可以暴力枚举了。至于说也要分个几类讨论一下路线，但显然是严格方便于我的方法的。我还要用 DS 维护，我枯了啊/kk

好好的一个 2600 题被我做成了这样，就当是练习了一下复杂的分类讨论能力吧（

题解也写吐了（

---

## 作者：ZaireEmery (赞：0)

一道好想但不好写的dp题。

$dp_i$ 表示遍历了所有颜色 $\leq a_i$ 的格子，目前停在第 $i$ 个格子花费的最小时间。

虽然 $-10^9 \leq a_i \leq 10^9$，但不同的 $a_i$ 最多只有 $n$ 个，因此我们将 $a_i$ 离散化。现在考虑遍历了所有颜色 $\leq i$ 的格子，当前位置为 $pos$，如何遍历所有颜色为 $i+1$ 的格子。显然，最优的方法是，从 $pos$ 走到某个颜色为 $i+1$ 的格子 $k$，然后从 $k$ 按照顺时针或逆时针的顺序遍历所有的颜色为 $i+1$ 的格子，最终停在最后一个被遍历到的颜色为 $i+1$ 的格子上，设为 $x$ 和 $y$ (分别是顺时针和逆时针)。

可以发现，枚举 $pos$ 或 $x,y$ 都不太方便，于是我们选择枚举 $k$ ,先通过枚举确定到 $k$ 代价最小的 $pos$，然后遍历所有的颜色为 $a_k$ 的格子，并更新 $dp_x$ 和 $dp_y$。**注意：一定要按$a_k$从小到大的顺序枚举 $k$，并且要特殊处理 $a_k=1$ 的情况。**

计算最小时间的部分就做完了，但这题还要我们输出方案。我们可以定义 `pair<int,int> prv[2010],f[2010]`，$prv_i$ 表示第一个被遍历到的颜色为 $a_i$ 的格子（也就是前文中的 $k$） 以及最后一个被遍历到的颜色为 $a_i-1$ 的格子（也就是前文中的 $pos$）。f_i则代表从 $pos$ 到 $k$ 和从 $k$ 到 $i$ 分别是顺时针还是逆时针，$1$ 代表顺时针，$0$ 代表逆时针。更新 $dp$ 的时候同步更新，最后递归模拟过程并输出即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s,cnt,x,y,ans=1e9,pos;
int a[2010],dp[2010];
pair<int,int> p[2010],prv[2010],f[2010];
vector<int> v[2010];
int next(int x){return (x+1<=n?x+1:1);}
int prev(int x){return (x-1?x-1:n);}
int dist0(int i,int j){return (i-j>=0?i-j:i+n-j);}
int dist1(int i,int j){return (j-i>=0?j-i:j+n-i);}
void Print(int i,int j){
	if(!j) return;
	Print(prv[i].second,j-1);
	if(f[i].second) cout<<"+"<<dist1(prv[i].second,prv[i].first)<<endl;
	else cout<<"-"<<dist0(prv[i].second,prv[i].first)<<endl;
	int idx=prv[i].first,c=0;
	if(!f[i].first){
		while(idx!=i){
			idx=prev(idx);
			c++;
			if(a[idx]==j) cout<<"-"<<c<<endl,c=0;
		}
	}else{
		while(idx!=i){
			idx=next(idx);
			c++;
			if(a[idx]==j) cout<<"+"<<c<<endl,c=0;
		}
	}
}
signed main(){
	cin>>n>>s;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		p[i]={a[i],i};
	}
	sort(p+1,p+n+1);
	v[0].push_back(s);
	for(int i=1;i<=n;i++){
		if(p[i].first!=p[i-1].first||i==1) cnt++;
		a[p[i].second]=cnt;
		v[cnt].push_back(p[i].second);
	}
	memset(dp,63,sizeof(dp));
	for(int i=1;i<=cnt;i++)
		for(int j=0;j<v[i].size();j++){
			int res=1e9,respos,resf;
			for(int t=0;t<v[i-1].size();t++)
				if((i==1?0:dp[v[i-1][t]])+min(dist0(v[i-1][t],v[i][j]),dist1(v[i-1][t],v[i][j]))<res){
					res=(i==1?0:dp[v[i-1][t]])+min(dist0(v[i-1][t],v[i][j]),dist1(v[i-1][t],v[i][j]));
					respos=v[i-1][t];
					resf=(dist0(v[i-1][t],v[i][j])>=dist1(v[i-1][t],v[i][j]));
				}
			x=prev(v[i][j]),y=next(v[i][j]);
			while(a[x]!=i) x=prev(x);
			while(a[y]!=i) y=next(y);
			if(res+n-(v[i][j]-x>0?v[i][j]-x:v[i][j]+n-x)<dp[x]){
				dp[x]=res+n-(v[i][j]-x>0?v[i][j]-x:v[i][j]+n-x);
				prv[x]={v[i][j],respos};
				f[x]={1,resf};
			}
			if(res+n-(y-v[i][j]>0?y-v[i][j]:y+n-v[i][j])<dp[y]){
				dp[y]=res+n-(y-v[i][j]>0?y-v[i][j]:y+n-v[i][j]);
				prv[y]={v[i][j],respos};
				f[y]={0,resf};
			}
	}
	for(int i=1;i<=n;i++)
		if(a[i]==cnt&&dp[i]<ans)
			ans=dp[i],pos=i;
	cout<<ans<<endl;
	Print(pos,cnt);
	return 0;
}
```


---

## 作者：xtx1092515503 (赞：0)

挺烦人的一道DP题。

------------

首先，本题的阶段是很容易设想出来的：因为要求“输出的东西不降”，所以必须先将所有 $1$ 输出，然后是所有 $2$，然后是所有 $3$……在不同的数字间，转移是有序的；但是在同一数字间，转移就可能不太trival了。

首先先设出DP状态。设 $f_i$ 表示若 $i$ 是所有值为 $a_i$ 的位置中第一个被输出的，此时所移动的最短距离，再设 $g_i$ 表示若 $i$ 是所有值为 $a_i$ 的位置中最后一个被输出的，此时所移动的最短距离。则答案即为

$$\min\limits_{a_i\text{ is maximum}}g_i$$

先考虑不同数字间的转移。假如 $j,k$ 分别是一个小一点的数和一个大一点的数，则有

$$g_j+\min\Big\{(k-j)\bmod n,(j-k)\bmod n\Big\}\rightarrow f_k$$

因为 $n$ 只有 $2000$，所以暴力枚举这样的 $(j,k)$ 进行转移即可。

然后再考虑相同数字间的转移。我们可以大胆猜测，假如我们从一个 $f_j$ 转移到 $g_k$，则必定是先顺时针/逆时针走到 $k$ 的前一个数，然后再掉头一路走到 $k$。

具体式子很长，直接看代码即可。明显这里仍然可以 $n^2$ 枚举转移。

比较恶心的是输出，不同数字间的转移还好，烦人的是相同数字间的转移。按照上文所述的实际意义进行转移即可，详情见代码。

总时间复杂度 $O(n^2)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,p,a[2010],f[2010],g[2010],F[2010],G[2010],res=0x3f3f3f3f;//f:the minimal starting from i; g:the minimal ending at i
vector<int>v[2010],u;
stack<int>s;
int main(){
	scanf("%d%d",&n,&p),p--,memset(f,0x3f,sizeof(f)),memset(g,0x3f,sizeof(g));
	for(int i=0;i<n;i++)scanf("%d",&a[i]),u.push_back(a[i]);
	sort(u.begin(),u.end()),u.resize(m=unique(u.begin(),u.end())-u.begin());
	for(int i=0;i<n;i++)v[a[i]=lower_bound(u.begin(),u.end(),a[i])-u.begin()+1].push_back(i);
//	for(int i=0;i<n;i++)printf("%d ",a[i]);puts("");
//	for(int i=1;i<=m;i++){for(auto j:v[i])printf("%d ",j);puts("");}
	for(auto i:v[1])f[i]=min((i+n-p)%n,(p+n-i)%n),F[i]=-1;
	for(int i=1;i<=m;i++){
		int len=v[i].size();
		for(int j=0;j<len;j++)for(int k=0;k<len;k++){
			if(j==k)continue;
			int J=v[i][j],K=v[i][k];
			int A=(v[i][(k+len-1)%len]+n-J)%n*2+(J+n-K)%n;
			int B=(J+n-v[i][(k+1)%len])%n*2+(K+n-J)%n;
			if(g[K]>f[J]+min(A,B))g[K]=f[J]+min(A,B),G[K]=J;
		}
		if(len==1)g[v[i][0]]=f[v[i][0]],G[v[i][0]]=v[i][0];
		if(i==m)continue;
		for(auto j:v[i])for(auto k:v[i+1])if(f[k]>g[j]+min((k+n-j)%n,(j+n-k)%n))f[k]=g[j]+min((k+n-j)%n,(j+n-k)%n),F[k]=j;
	}
//	for(int i=0;i<n;i++)printf("%d ",f[i]);puts("");
//	for(int i=0;i<n;i++)printf("%d ",g[i]);puts("");
	for(auto i:v[m])res=min(res,g[i]);
	printf("%d\n",res);
	for(auto K:v[m]){
		if(g[K]!=res)continue;
		for(int i=m;i;i--){
			int len=v[i].size();
			int J=G[K];
			int j=lower_bound(v[i].begin(),v[i].end(),J)-v[i].begin(),k=lower_bound(v[i].begin(),v[i].end(),K)-v[i].begin();
			int A=(v[i][(k+len-1)%len]+n-J)%n*2+(J+n-K)%n;
			int B=(J+n-v[i][(k+1)%len])%n*2+(K+n-J)%n;
			if(len>1){
				if(A<B){
					for(int l=k;(l+1)%len!=j;(++l)%=len)s.push(-(v[i][(l+1)%len]+n-v[i][l])%n);
					s.push(-(v[i][(k+len-1)%len]+n-v[i][(j+len-1)%len])%n);
					for(int l=(k+len-1)%len;l!=j;(l+=len-1)%=len)s.push((v[i][l]+n-v[i][(l+len-1)%len])%n);
				}else{
					for(int l=k;(l+len-1)%len!=j;(l+=len-1)%=len)s.push((v[i][l]+n-v[i][(l+len-1)%len])%n);
					s.push((v[i][(j+1)%len]+n-v[i][(k+1)%len])%n);
					for(int l=(k+1)%len;l!=j;(++l)%=len)s.push(-(v[i][(l+1)%len]+n-v[i][l])%n);
				}				
			}
			A=J,B=F[J];
			if(B==-1)B=p;
			s.push((A+n-B)%n<(B+n-A)%n?(A+n-B)%n:-(B+n-A)%n);
			K=B;
		}
		break;
	}
//	auto S=s;while(!S.empty())printf("%d ",(p+=S.top()+n)%n),S.pop();puts("");
	while(!s.empty())printf("%c%d\n",(s.top()>=0?'+':'-'),abs(s.top())),s.pop();
	return 0;
}
```

---

