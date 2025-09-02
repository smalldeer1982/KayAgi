# [POI 2010] TEL-Teleportation

## 题目描述

**译自 POI 2010 Stage 2. Day 2「[Teleportation](https://szkopul.edu.pl/problemset/problem/fKO3YZL0f_UM1nHQNDvw7mku/site/?key=statement)」**

现在有 $n$ 个点，目前在 $1$ 号点和 $2$ 号点之间有一条无向边，长度为 $250\min$ 。  
除此之外，还有 $m$ 条无向边，长度都为 $1\ \textrm{h}$ （即 $60\min$）， Byteasar 想知道，还能最多在添加多少条长度为 $1\ \textrm{h}$ 的无向边，使得新图无重边无自环，且 $1$ 号点到 $2$ 号点的最短路仍为 $250\min$ 。

## 样例 #1

### 输入

```
10 10
1 3
3 5
5 7
7 9
2 9
1 4
4 6
6 8
8 10
2 10```

### 输出

```
10```

# 题解

## 作者：XL4453 (赞：7)


$\text{Update : 最后分配点的正确性证明。}$

---
### 解题思路：

将整个图分成有顺序的 $6$ 个部分，每一部分只和相邻的两个（端点只有一个）部分相连，这样从第一个部分到第六个部分一定要经过至少 $5$ 条边，也就是题目条件。

将第一个点放在第一个部分，与第一个点直接相连的部分放在第二个部分，与第二个部分有连边的放在第三个部分。再将第二个点放在第六个部分，与第二个点直接相连的放在第五个部分，与第五个部分有连边的放在第四个部分。都不满足的先放一边。

然后对于每一个部分的内部，一定可以任意连边，这一部分的价值可以直接统计。相邻的两个部分之间也可以直接连边，代价也可以直接算出来。

最后将那些都不满足的边放到中间两个部分中能产生最大价值的就行了。

注意题目要求的是增加的边的数量，需要减去原有的边数 $m$。

---
最后一步分配剩余的点的正确性证明：

先考虑只有一个点的情况。不妨设第二部分到第五部分的点的数量分别为 $a$，$b$，$c$，$d$，这个点之前就有的连边一共有 $u$ 条。

然后分情况讨论，将这个点放在第一到第五个部分能产生的价值分别是：$a+b+1-u$，$a+b+c-u$，$b+c+d-u$ 和 $c+d+1-u$，由于题目中保证 $1$ 和 $2$ 两个点联通，所以 $b,c\ge 1$。由此得出一定放在中间两个部分，且取 $a$ 和 $d$ 中较大的一个的相邻位置（这个点可能和中间两个位置中的一个有连边，此时不能放在与连边部分相对的位置，但是即使能放也不可能产生更大的价值，所以可以不用考虑）。

---

由此拓展到多个点，由之前一个点的推导，这样的一些点一定是放在中间两个部分中的一个，所以不妨设总共有 $t$ 个可以任意放置的点，放在第三个部分的点有 $x$ 个，则放在第四个部分的点有 $t-x$ 个，沿用之前每一个部分点的数量。

此时可以将产生的总价值表示为 $\dfrac{t(t+1)}{2}+x(a+b+c)+(t-x)(b+c+d)$，变形得到 $\dfrac{t(t+1)}{2}+t(b+c+d)+x(a-d)$，其中变化的只有 $x$。

这是一个 $x$ 的一次式，求导之后的结果为定值 $a-d$，最大值一定取在端点处，也就是一定在 $x=0$ 或者 $x=t$ 处取最大，具体取决于 $a-d$ 和 $0$ 的大小关系。换句话说，要不然全都放在第三个部分，要不然就全都放在第四个部分，也就是之前得到的结论。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
#define int long long
const int MAXN=4000005;
int n,m,head[MAXN],nxt[MAXN],num[MAXN],x,y,cnt,col[MAXN],cnt2,cnt5,cnt3,cnt4,ans;
void add(int x,int y){
	nxt[++cnt]=head[x];head[x]=cnt;num[cnt]=y;
}
signed main(){
	scanf("%lld%lld",&n,&m);
	col[1]=1;col[2]=6;
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",&x,&y);
		add(x,y);add(y,x);
	}
	for(int i=head[1];i;i=nxt[i]){
		col[num[i]]=2;cnt2++;
	}
	for(int i=head[2];i;i=nxt[i]){
		col[num[i]]=5;cnt5++;
	}
	for(int i=1;i<=n;i++){
		if(col[i]==2){
			for(int j=head[i];j;j=nxt[j])
			if(col[num[j]]==0)col[num[j]]=3,cnt3++;
		}
		if(col[i]==5){
			for(int j=head[i];j;j=nxt[j])
			if(col[num[j]]==0)col[num[j]]=4,cnt4++;
		}
	}
	for(int i=1;i<=n;i++)
	if(col[i]==0){
		if(cnt2>cnt5)cnt3++;
		else cnt4++;
	}
	ans=cnt2+cnt5+cnt2*(cnt2-1)/2+cnt3*(cnt3-1)/2+cnt4*(cnt4-1)/2+cnt5*(cnt5-1)/2
	+cnt2*cnt3+cnt3*cnt4+cnt4*cnt5-m;
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Reywmp (赞：6)

- ## P3505 【[POI2010]TEL-Teleportation】

一道图论题，挺考思维的，如果从题目特征切入还是可以得出思路的。

~~虽然没有看起来那么难，但是还是很有难度的题目的~~

模拟赛整了这道题，于是特地来写题解报告。

洛谷的题面是直接给出抽象的题目模型，有一说一在bzoj上看时还挺难理解的。

后来才发现1h要换算成60min，亏出题人想得出来这巧妙的思路转换，~~赞美出题人。~~

------------

- ### Prelude

虽然没有给部分分，我们可以先考虑一些暴力或者错误结论骗分。

暴力可以考虑$\text{Floyd}$的思路或者直接跑$\text{Dijkstra}$记录`dist`全源最短路，然后点与点两两匹配。

或者跑贪心，尽量拿远的点匹配，如果已经不存在更优情况了就结束贪心。

这都是看到这种建边题可能会口胡出的思路。

那么我们来考虑思维过程。

首先，为什么特地要挑选长度至少为$5$呢，为什么不为$6$，不为$114514$，边为什么不带权呢。

题目要求输出最大能建的边数，一个一个加自然不可能。那么什么情况下可以快速计算出总数呢。我们可以考虑**集合**与**容斥**的思路。

------------

- ### Solution

对于图论题，我们如何在图上划分出多个集合呢。我们可以考虑把图分层。

而对于这题就相对比较清楚了。

我们可以把图就分为5层。第一层为点1而最后一层为点2。与1有连边的放第二层，与2有连边的为第4层。那么现在很显然一层一层穿过就已经有了2条边。而中间剩下的那些点该怎么连呢。

![](https://cdn.luogu.com.cn/upload/image_hosting/9kslgdcu.png)

我们给出样例的图示（略丑）。红边是可以新建的而黑色的是本来就有的。

考试时我们也可以自己手造几个小数据推一下找找感觉。

首先我们很清楚每一层的边之间都可以互相连边。因为是一层一层传过，所以层内加边只会增加距离。

其次只有相邻的层的点之间可以连边，不然距离必然缩短至5以内。可以反证证明。

考虑第三层的边，第三层的边一共有3种。

- 与第二层有连边的点；

- 与第四层有连边的点；

- 只与层内点相连的点或者没有任何连边的点。

我们发现，对于与第二层有连边的点，我们不能将其与第四层直接连边，不然必然出现第一层$\rightarrow$第二层$\rightarrow$第三层$\rightarrow$第四层$\rightarrow$第五层的长度4的路径。第二种同理。

亦可以理解为，当一条路径走过第三层的点时，我们要保证必须在第三层层内也走一次。所以第三层不存在同时连第二四层的点。

如何保证答案最大化呢。

我们只需要保证：

- 每一层内的点都两两相连

- 对于第三层已经与第二层相连的点将其与第二层所有点都连一遍。

- 对于第三层已经与第四层相连的点将其与第四层所有点都连一遍，

这样思路就出来了，我们的程序只需要及时计数就行。

------------

- ### Code

对于这一题思路不好想，但是思路出来程序实现不难，但是由于需要**保证不重复计数**。代码实现细节并不是很简单。

具体见代码

```cpp

#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>
#include<algorithm>

#define N 400005

using namespace std;

struct Rey
{
	int nxt,to;
}e[N*10];

int head[N],cnt;
int n,m,sec1,sec2,sec3;
int secs[N];

void add(int u,int v)
{
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	head[u]=cnt;
}

int main()
{
	scanf("%d %d",&n,&m);	

	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		add(x,y);add(y,x); 
	}	

	for(int i=head[1];i;i=e[i].nxt)
	{
		int go=e[i].to;
		secs[go]=1;
		sec1++;		
	}//第二层
	
	for(int i=head[2];i;i=e[i].nxt)
	{
		int go=e[i].to;
		secs[go]=2;
		sec2++;
	}//第四层
	sec3=n-sec1-sec2-2;//第三层
	int l1,l2;
	l1=sec1;
	l2=sec2;
	int ans=0;
	for(int i=3;i<=n;i++)
	{
		if(!secs[i])//属于第三层
		{
			ans+=--sec3;
			int been;
			int tot;
			been=tot=0;
            //been记录这个点是否已经连了第二层或是第四层
            //tot记录如果连了，连了多少条，这样记录答案不需要重复加上
			for(int j=head[i];j;j=e[j].nxt)
			{
				int go=e[j].to;
				if(secs[go])tot++,been=secs[go];//是否与2，4层相连
				else
				{
					if(go>i)ans--;//防止重复计数！go>i就是说明这个边之前有连
				}
			}
			if(been==1)ans+=sec1-tot;
			if(been==2)ans+=sec2-tot;
			if(been==0)ans+=max(sec1,sec2);//都没连，就往多的那一层连
		}
		else
        {
        	if(secs[i]==1)ans+=--l1;
        	if(secs[i]==2)ans+=--l2;
            //--l1,--l2都是因为这个点连了以后，后面别的点再加答案就不需要考虑他了。
            for(int j=head[i];j;j=e[j].nxt)if(secs[e[j].to]&&e[j].to>i)ans--;//同理
        }
	}
	
	printf("%d\n",ans);
	return 0;

}

```

---

## 作者：mulberror (赞：3)

首先来安利一波自己的博客：[传送门](https://www.cnblogs.com/chhokmah/p/10465905.html)

## 题目大意

给出了一个图，然后让你加最多的边，让点$1$到$2$之间至少要经过5条边

-----

## 解法

比较清楚，我们可以将这个图看作一个分层图，点$1$为第一层，再将$2$作为第五层，这样第一层和第五层直接加边就可以保证我们之间至少有$5$条边经过了。

那么剩下的点我们还是分成$3$层，其中第$2$层为与$1$直接相连的节点，第$4$层为直接和节点$2$相连的节点，剩下的节点我们就放在了第$3$层中，那么这样我们就做好了分层工作。

很明显最优的方案就是每一层的节点都两两相连，那么我们就先将所有的点都连起来，在减掉所有不可以的边。

什么边是不可以的呢？比如说是重复的边，或者是从点$1$连到到了$2$的边，这些边都是不可以的边。

那么我们每次只需要保证我们连接的边的两个端点是$u,v$是$u<v$就可以了。

若一个第三层的点连到某个第一层的点，则该点可以向第一层的所有点连边。若一个第三层的点连到某个第四层的点，则该点可以向所有第四层的点连边。否则的话就向节点数较多的那一层连边就好了。

## ac代码（我丑陋的代码不要吐槽QAQ）
```cpp
# include <cstdio>
# include <cstring>
# include <algorithm>
# include <ctype.h>
# include <iostream>
# include <cmath>
# include <map>
# include <vector>
# include <queue>
# define LL long long
# define ms(a,b) memset(a,b,sizeof(a))
# define ri (register int)
# define inf (0x7f7f7f7f)
# define pb push_back
# define fi first
# define se second
# define pii pair<int,int>
using namespace std;
inline int gi(){
    int w=0,x=0;char ch=0;
    while(!isdigit(ch)) w|=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return w?-x:x;
}
# define N 1000005
struct edge{
	int to,nt;
}E[N<<1];
int cnt,n,m,s1,s2;//s1表示第2层的点数，s2表示第4层点的个数
int H[N],link[N];
void addedge(int u,int v){//加边不说
	E[++cnt]=(edge){v,H[u]}; H[u]=cnt;
}
int main(){
	n=gi(),m=gi();
	for (int i=1;i<=m;i++){
		int u=gi(),v=gi();
		addedge(u,v); addedge(v,u);
	}
	for (int e=H[1];e;e=E[e].nt) link[E[e].to]=1,s1++;//将所有与1相连的节点计算出来
	for (int e=H[2];e;e=E[e].nt) link[E[e].to]=2,s2++;//累计所有和2相连的节点
	int ans=0,s3=n-s1-s2-2,now1=s1,now2=s2;//now分别表示当前我们还有处理的与1和2相连的节点个数
	for (int i=3;i<=n;i++){
		if (link[i]==1){//如果当前节点和1相连
			now1--,ans+=now1;//表示当前这个节点和其他和
			for (int e=H[i];e;e=E[e].nt){
				int v=E[e].to;
				if (link[v]&&v>i) ans--;//减掉重复的边
			}
		}
		if (link[i]==2){
			now2--,ans+=now2;
			for (int e=H[i];e;e=E[e].nt){
				int v=E[e].to;
				if (link[v]&&v>i) ans--;//减掉重复的边
			}
		}
		if (!link[i]){
			s3--; ans+=s3;
			int fg=0,s=0;
			for (int e=H[i];e;e=E[e].nt){
				int v=E[e].to;
				if (link[v]) fg=link[v],s++;
				else if (v>i) ans--;
			}
			if (fg==1) ans+=s1-s;
			else if (fg==2) ans+=s2-s;
			else ans+=max(s1,s2);
		}
	}
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：_Cheems (赞：1)

小清新图论题。

题意等价于加尽量多边使得 $1\to 2$ 最短路边长 $\ge 5$。边权都是 $1$，所以不难想到 bfs，那么条件等价于从 $1$ 开始跑 bfs，然后按 bfs 的过程分层，$1$ 在第一层，那么 $2$ 的层数需满足 $\ge 6$。

bfs 分层的限制是：每一层的点只能被上一层的点连边，且必须被至少一个上一层的点连边。还是不好做，于是放宽限制，不要求与至少一个上一层的点连边，但是不能有空层。可以发现，不会影响判定，因为这样搞每个点的层数只会比原先小，非法情况依旧非法。

同时，并不在意除 $2$ 之外层数 $\ge 6$ 的点到底在哪，所以不妨将它们都扔到第 $5$ 层，显然无影响。也就是说，我们需要确定一个分层方案，满足第一层只有 $1$、第六层只有 $2$、一个点只能向它相邻层的点连边（包括自己层），且每层至少有一个点。

再考虑原图的边 $(u,v)$ 对分层的限制，即 $u,v$ 必须处于相邻层或同一层。

那么问题可以转述为：依次考虑每个点，假如放在第 $k$ 层，那么需原图与之相邻的点的层数 $p$ 只能是 $k-1,k,k+1$，然后会产生 $k-1,k,k+1$ 层的点数的贡献，要令总贡献最大。

明确一点，放 $3$ 层肯定比放 $2$ 层“发展潜力”大，也就是会对之后的点贡献更多，因为后者还可对 $4$ 层贡献。

首先与 $1$ 相邻的点只能放 $2$ 层，与 $2$ 相邻同理。再考虑与这些点相邻的点，若是与 $1$ 相邻的点相邻，则可以放 $2,3$ 层，那我一定放 $3$ 层。为啥？考虑调整法，最终局面每层必有点，然后将这个点从 $2$ 调整至 $3$ 层一定不劣。其它情况同理。


再考虑剩下的 $cnt$ 个点。容易发现放 $3$ 层一定优于 $2$ 层，因为 $4$ 层至少存在一个点；同理 $4$ 层一定优于 $5$ 层。而且还不用管这些点在原图的连边情况，因为分层方案中它们一定相邻。那么放 $3$ 还是 $4$ 呢？

注意到剩下的点互相连边的边数是确定的，为 $\frac {cnt(cnt-1)}2$。所以只需要令它们与原先的点连边数最多。记原先 $2,3,4,5$ 层的点数分别为 $a,b,c,d$，那么贡献即为 $cnt\max(a+b+c,b+c+d)$。

复杂度 $O(n+m)$。
#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define LL long long
const int N = 1e5 + 5;
int n, m, u, v, a, b, c, d;
int col[N]; 
LL ans, cnt;
vector<int> to[N]; 

signed main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i) scanf("%d%d", &u, &v), to[u].push_back(v), to[v].push_back(u);
	col[1] = 1, col[2] = 6;
	for(auto i : to[1]) col[i] = 2, ans += a + 1, ++a;
	for(auto i : to[2]) col[i] = 5, ans += d + 1, ++d;
	for(int i = 3; i <= n; ++i) 
		if(col[i] == 2){
			for(auto j : to[i])
				if(!col[j]) col[j] = 3, ans += a + b + c, ++b;
		}
		else if(col[i] == 5){
			for(auto j : to[i])
				if(!col[j]) col[j] = 4, ans += b + c + d, ++c;
		}
	for(int i = 3; i <= n; ++i) cnt += (col[i] == 0);
	ans += 1ll * cnt * (cnt - 1) / 2;
	ans += 1ll * max(a + b + c, b + c + d) * cnt;
	cout << ans - m;  
	return 0;
}
```

---

## 作者：Musity (赞：1)

# Solution

首先贪心，算出每个点和 $1、2$ 的距离，如果距离之和大于 $5$，那么一定可以连边使它与 $1、2$两点之间的距离等于 $5$（题目保证 $1$、$2$ 间有大于 $4$ 的路径）。故最优时所有点距离 $1、2$两个点的距离之和等于 $5$。

由此想到分层图：把与 $1$ 距离 $0 \sim 5$ 的点记为第 $1 \sim 6$ 层，第一层只有$1$,第六层只有 $2$，只有上一层能到下一层，刚好满足任意点到两端的距离之和为 $5$，最后所有层内部可以连边，上一层可以和下一层连边，除去最开始的边即为答案,见下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/6sg9i075.png)

现在目标就变成了求每一层有几个点能使答案最优。首先一开始就与 $1$ 直接相连的点肯定是第二层的，与第二层直接相连的点且不在前两层肯定是第三层的。同理可以从 $2$ 往前找第五层与第四层。其余的点就是距离 $1、2$ 都大于 $2$ 的，也就是距离两边大于 $5$，应把它放入某一层。

因为一开始的点、边已经确定，要想加的边最多，只用考虑如何放其他点使**总边数最多**即可（不考虑原来有没有边）。

- 放入第一层，会连点 $1$ 以及第二层的点
- 放在第二层，会连点 $1$，第二层的点，第三层的点。显然优于放第一层。
- 放第三层，会连第二层的点，第三层的点，第四层的点，因为第四层的点数大于等于一，放第三层不会比放第二层差。

同理也可得到放第四层会比第五第六优。考虑放三还是四。无论放三还是四，第三层，第四层的点都会连上，区别在于多连的是第二层还是第五层，比较哪一个点多即可。

# Code


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 4e4+5;

int n, m, ans, dep[N], cnt[8];
vector<int> e[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1, x, y; i <= m; i++) {
		cin >> x >> y;
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dep[1] = 1, dep[2] = 6;
	for (auto y : e[1]) {
		dep[y] = 2;
	}
	for (auto y : e[2]) {
		dep[y] = 5;
	}
	for (int i = 1; i <= n; i++) {
		if (dep[i] == 2) {
			for (auto y : e[i])
				dep[y] = dep[y]==0 ? 3 : dep[y]; // 不在 1,2 层中 
		}
		if (dep[i] == 5) {
			for (auto y : e[i])
				dep[y] = dep[y]==0 ? 4 : dep[y]; // 不在 5,6 层中 
		}
	}
	for (int i = 1; i <= n; i++)
		cnt[dep[i]]++;
	for (int i = 1; i <= n; i++) {
		if (dep[i] == 0) {
			if (cnt[2] > cnt[5])
				cnt[dep[i] = 3]++;
			else 
				cnt[dep[i] = 4]++;
		}
	}
	for (int i = 1; i <= 6; i++) {
		ans += cnt[i]*cnt[i+1];    // 与下一层连边，第六层没有下一层(cnt7=0) 
		ans += cnt[i]*(cnt[i]-1)/2;// 本层内部连边, 1,2能连的边为零 
	}
	cout << ans-m << '\n';
	return 0;
}
```

---

