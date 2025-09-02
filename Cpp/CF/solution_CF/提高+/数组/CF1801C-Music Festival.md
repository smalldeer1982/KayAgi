# Music Festival

## 题目背景

可以在 [P13530](https://www.luogu.com.cn/problem/P13530) 评测本题。

## 题目描述

小男孩维佳非常喜欢听音乐。他一直关注着自己喜欢的乐队，因此知道本周五将有 $n$ 张新专辑发布，第 $i$ 张专辑包含 $k_i$ 首曲目。当然，作为最忠实的粉丝，维佳已经提前听过了所有即将发布的新歌，并且知道第 $i$ 张专辑中第 $j$ 首歌的“酷炫度”为 $a_{i,j}$。

维佳有一个朋友玛莎，他非常希望邀请玛莎一起去参加有他最喜欢乐队出演的音乐节。不过要想让玛莎答应，玛莎需要先体验一下这些新歌。维佳知道，如果玛莎听到的某首歌酷炫度超过她此前听过的所有歌，她就会获得 $1$ 点“印象值”。遗憾的是，专辑只能整张播放，且专辑内歌曲顺序不能改变。

请帮助维佳安排专辑的播放顺序，使得玛莎获得的印象值尽可能大，这样她一定会答应和他一起去音乐节。

## 说明/提示

### 样例解释

在第一个测试样例中，最优的播放顺序是先听第 $4$ 张、再听第 $2$ 张、第 $3$ 张和第 $1$ 张专辑。这样玛莎依次听到的歌曲为：**1**；**7**；**8**, 6；4, **9**, 4, 6, 8。玛莎将获得 $4$ 点印象值。

在第二个测试样例中，应先播放第 $1$ 张专辑，再播放第 $4$ 张，之后第 $2$ 和第 $3$ 张顺序任意。这样玛莎能获得最大印象值，且第 $1$ 和第 $4$ 张专辑的每首歌都能带来印象值，第 $2$ 和第 $3$ 张专辑则不会带来新的印象值。

## 样例 #1

### 输入

```
2
4
5
4 9 4 6 8
1
7
2
8 6
1
1
4
2
3 4
2
1 8
2
2 8
2
7 9```

### 输出

```
4
4```

# 题解

## 作者：lingying (赞：15)

考试最后几分钟写出来，结果交上去在第二个点错了。考完几下就调完了悲。

## 题意

你有 $n$ 个序列，你可以以任意排列方式组合起这 $n$ 个序列，现在问你组合起来的序列的最长上升子序列长度的最大可能是多少。

每个序列的长度记为 $m_i$，第 $i$ 个序列的第 $j$ 个数为 $a_{i,j}$。

$\sum m_i \le 200000,a_{i,j}\le 200000,n\le200000$。

## 做法

考虑把每个序列可能贡献出来的上升子序列抓出来，具体来讲，这个序列以一开头的上升子序列中的元素都可以作为贡献出来的上升子序列中的最小值。显然，一个序列可以贡献出来的上升子序列的最大值必定是这个序列的最大值。

举个例子，假设一个序列为 $[1,3,2,5,4]$，那么它可能对答案有贡献的上升子序列便为 $[1,3,5],[3,5],[5]$。

假设我们把这若干个上升子序列抓出来了，最小值记为 $l_i$，最大值记为 $r_i$。我们按照 $l_i$ 排序，那么我们可以设一个状态 $f_i$ 表示 $1$ 到 $i$ 这若干个我们抓出来的上升子序列可以组成的最大长度。

则 $f_i=\max\limits_{r_j<l_i}f_j+len_i$。

其中 $len_i$ 表示 $i$ 这个上升子序列的长度。

这个方程可以用树状数组优化，此题结。

时间复杂度为 $O(n\log n )$，这里认为 $n,\sum m_i,a_{i,j}$ 是同阶的。

## 代码

```
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+5;

int _,n,m,top,idx;
int a[N],stk[N],cnt[N],C[N];
struct node
{
	int l,r,w;
	
	bool operator<(const node &b)const{return l==b.l?r<b.r:l<b.l;}
	
}b[N];

void modify(int x,int d)
{
	for(;x<N;x+=x&-x)C[x]=max(C[x],d);
}

void clr(int x)
{
	for(;x<N;x+=x&-x)C[x]=0;
}

int query(int x)
{
	if(!x)return 0;
	int ret=0;
	for(;x;x-=x&-x)ret=max(ret,C[x]);
	return ret;
}

int main()
{
	scanf("%d",&_);
	while(_--)
	{
		idx=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&m);
			int maxn=0;
			for(int j=1;j<=m;j++)
			{
				scanf("%d",&a[j]);
				maxn=max(maxn,a[j]);
			}
			top=0;
			for(int j=m;j>=1;j--)
			{
				while(top&&a[stk[top]]<=a[j])top--;
				if(top)cnt[j]=cnt[stk[top]]+1;
				else cnt[j]=1;
				stk[++top]=j;
			}
			int mx=0;
			for(int j=1;j<=m;j++)
				if(a[j]>mx)
					b[++idx].l=a[j],b[idx].r=maxn,b[idx].w=cnt[j],mx=a[j];
		}
		sort(b+1,b+idx+1);
		int ans=0;
		for(int i=1;i<=idx;i++)
		{
			int v=query(b[i].l-1)+b[i].w;
			ans=max(ans,v);
			modify(b[i].r,v);
		}
		cout<<ans<<'\n';
		for(int i=1;i<=idx;i++)
		{
			clr(b[i].r);
		}
	}
	return 0;
}
```

---

## 作者：Augury (赞：7)

# 题解——[CF1801C Music Festival](https://www.luogu.com.cn/problem/CF1801C)

## 题意

- 你有 $n$ 个专辑，第 $i$ 个专辑中有 $k_i$ 首歌。
- 每首歌有一个权值 $a_{i,j}$。
- 当一首歌的权值大于所有在他之前播放的歌的权值时，你会获得 $1$ 好感度。
- 每个专辑都要连续地播放，就是说不能放到一半停下，也不能从中间开始放。
- 现在让你求出这些专辑的播放顺序，使得到的好感度最高，问最高的好感度是多少。

## 思路

容易发现，在每个专辑内，如果一首歌的权值**小于等于**他前面权值最大的歌，那么这首歌就不会对答案产生任何贡献，因为他永远不可能比它前面的歌权值更高。

因此，我们可以直接删掉这些歌。

显然的，一首歌要对答案产生贡献，那么他一定要大前面播放的歌的权值。

所以，我们定义 $dp_i$ 表示前面播放的歌的权值全部小于等于 $i$ 时能获得的最大好感度。

然后，考虑转移。

举个例子，一个专辑 $[1,4,6]$。

- 如果从 $1$ 开始播放，那么我们一定能对答案造成 $3$ 的贡献。

- 如果从 $4$ 开始播放，那么我们一定能对答案造成 $2$ 的贡献。

- 如果从 $6$ 开始播放，那么我们一定能对答案造成 $1$ 的贡献。
- 总结规律，就是对答案造成后面（包括这首）歌的数量的贡献。

说成状态转移的话，就是：

- `dp[6]=max(dp[6],dp[1-1]+3)`

- `dp[6]=max(dp[6],dp[4-1]+2)`

- `dp[6]=max(dp[6],dp[6-1]+1)`

这里的减一是为了保证不会算重，也符合了状态定义。

总结规律，就是对于每个专辑，在他的歌的权值最大的位置的 $dp$ 值能由这首专辑的歌曲的权值的位置转移过来。

现在，有了转移，就差怎么快速的转移了。

如果我们对于每个 $i$ 都枚举一遍所有的专辑，那么复杂度可以达到惊人的 $\Theta(\max a\times \sum k_i)$，显然是超时的。

容易发现，对于每个专辑，我都只会在权值最大值的位置转移。

所以，我们开一个 $\text{vector}$，表示一个位置有哪些专辑可以转移。

这样，时间复杂度就被优化到了 $\Theta(\max a+\sum k_i)$，十分优秀。

## 正确性

### 无后效性

对于一个 $dp_i$，我要从 $dp_j$ 转移过来，那么一定 $j<i$。

因为我考虑的是歌曲对答案的贡献，所以专辑是否被选择对转移没有影响。

所以无后效性是显然的。

### 一个专辑是否会被选择多次

对于每个专辑，我都只会在一个 $dp_i$ 位置进行转移，而且答案是取最大值，显然一个专辑不会被选择多次。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+100;
struct node{
	int from,val;
};
int n;
int mina,maxa;
int k[maxn];
vector<int>a[maxn];
vector<node>g[maxn];
int dp[maxn];
void real_main(){
	mina=1e9;
	maxa=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){//写得很臭的读入
		scanf("%d",&k[i]);
		a[i].clear();
		for(int j=1,tmp,lst=0;j<=k[i];j++){
			scanf("%d",&tmp);
			if(tmp<=lst)continue;
			lst=tmp;
			maxa=max(maxa,tmp);
			mina=min(mina,tmp);
			a[i].push_back(tmp);
		}
	}
	for(int i=1;i<=n;i++){//很臭的处理转移
		int now=a[i][(int)a[i].size()-1];
		for(int j=0;j<(int)a[i].size();j++){
			int tmp=a[i][j];
			g[now].push_back((node){tmp,(int)a[i].size()-j});
		}
	}
	dp[mina-1]=0;
	for(int i=mina;i<=maxa;i++){
		dp[i]=dp[i-1];
		for(int j=0;j<(int)g[i].size();j++){
			node tmp=g[i][j];
			dp[i]=max(dp[i],dp[tmp.from-1]+tmp.val);
		}
	}
	for(int i=mina;i<=maxa;i++)g[i].clear();
	cout<<dp[maxa]<<'\n';
}
int main(){//恶臭的多组数据
	int t;
	scanf("%d",&t);
	while(t--)real_main();
	return 0;
}
```



---

## 作者：AzusidNya (赞：6)

### C

vp 完后看题解都是数据结构优化 DP，遂提供一种赛时写的图论建模做法，时间复杂度瓶颈在于离散化。

先尝试暴力的建图。将每个位置 $a_{i, j}$ 当作节点。设点 $u$ 能经过一条边权为 $w$ 的边走到 $v$ 的意义是若当前最大值的位置是 $u$，则存在一种方法使得最大值的位置变成 $v$ 并对答案产生 $w$ 的贡献。

考虑同一数列中的点如何连边。因为选择了一个数列时需要把整个数列都选上，所以每个点像数列右边第一个不小于当前点的位置连边，如果两个点相等边权赋为 $0$，否则赋为 $1$。单调栈维护一下即可。

考虑不同数列中如何连边。一个数列一定是最大值连向别的数列。设当前数列最大值为 $x$，则连向所有其它数列中从左到右第一个大于 $x$ 的位置，边权为 $1$。

然后建个起点连向所有数列的第一个位置，再建个终点从每个数列的最大值连向它，边权均设为 $0$，然后在 DAG 上跑最长路就能得到答案。

为什么这是对的呢？因为这条路径上经过的点就是所有的前缀最大值，如果这条路径上没走过一个点说明这个点拼上去后也不会产生贡献。

但是这样边数炸了，每个数列最大值都连 $n$ 条边，边数是 $n^2$ 级别的。

考虑优化建图。

注意到不同数列之间的连边的依据是偏序关系，所以考虑在图中拉一条数轴出来，让判断偏序的连边在数轴上完成。

具体的，将在所有数列中出现过的数存起来离散化，设出现过的数有 $siz$ 个，那么就新建 $siz + 1$ 个点，每个点向后继连边权为 $0$ 的边。

对于每个数列，有用的点仅有本身是前缀最大值的点。

然后就可以把原本的数列最大值连向另一个数列的一个值这一过程分为三步，从当前数列的最大值走到数轴，沿着数轴走到一个另一数列能产生贡献的点，然后再从数轴进入另一数列。

因此，对于每一数列的所有前缀最大值，从数轴上对应的点向它连一条边权为 $1$ 的边，代表进入这一数列，并且因为选择了当前数又产生了 $1$ 的贡献。

然后将每一数列的最大值向它在数轴上的后继节点连一条边权为 $0$ 的边。连向后继节点是因为当前最大值已经不会产生贡献了，同时可以避免成环。

然后上面新建起点和终点的步骤就不需要了，因为数轴的起点可以直接看作起点，而数轴的终点也能看作终点。

这样建出来的图边数是 $O(\sum k_i)$ 级别的。上界是 $3\sum k_i + 1$，当数列中每个数都不同，且所有数列都形成单调上升序列时取到上界。

然后在这张新 DAG 上跑最长路即可，也就是拓扑排序后跑个简单 dp 转移。

样例一建出来的图是这样的。

![](https://cdn.luogu.com.cn/upload/image_hosting/ks8qns3m.png)

同一行的点代表同一数列，最上面的一排是数轴。每个点上方标注的是这个点实际表示的值。结合样例和上面的说明应该能看得懂吧。

在这张图上，$1$ 是起点，$7$ 是终点。有最长路 $\{1, 16, 2, 3, 4, 13, 5 ,14, 6, 9, 7\}$，长度为 $4$，则答案为 $4$。

按题目的表述描述成数列则为 $\{1, 7, 8, 6, 4, 9, 4, 6, 8\}$，前缀最大值为 $\{1, 7, 8, 9\}$，为上述最长路中经过的数列中的点。

[Submission #280521098 - Codeforces](https://codeforces.com/contest/1801/submission/280521098)

code：

```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<queue>
#define int long long
#define eb emplace_back
#define mp make_pair
#define DEBUG
using namespace std;
const int P = 998244353, inf = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;
namespace azus{
	int n, m;
	vector<vector<pii> > edge;
	vector<int> du;
	vector<vector<int> > a;
	vector<int> l;
	vector<int> f;
	int main(){
		cin >> n, m = 0;
		l.assign(n + 5, 0);
		a.assign(n + 5, vector<int> {});
		vector<int> b;
		for(int i = 1; i <= n; i ++){
			cin >> l[i];
			a[i].assign(l[i] + 3, 0);
			for(int j = 1; j <= l[i]; j ++)
				cin >> a[i][j], b.eb(a[i][j]);
			m += l[i];
		}
		sort(b.begin(), b.end());
		auto epos = unique(b.begin(), b.end());
		b.erase(epos, b.end());
		int N = m + b.size() + 5;
		du.assign(N + 5, 0);
		f.assign(N + 5, 0);
		edge.assign(N + 5, vector<pii>{});
		for(int i = 0; i < (int)b.size(); i ++){
			edge[m + i + 1].eb(mp(m + i + 2, 0)), du[m + i + 2] ++;
		}
		auto c = a;
		int nm = 0;
		for(int i = 1; i <= n; i ++){
			int x = -1;
			for(int j = 1; j <= l[i]; j ++){
				nm ++;
				c[i][j] = lower_bound(b.begin(), b.end(), c[i][j]) - b.begin() + 1;
				if(max(x, a[i][j]) == a[i][j])
					edge[c[i][j] + m].eb(mp(nm, 1)), du[nm] ++;
				x = max(x, a[i][j]);
			}
		}
		nm = 0;
		for(int i = 1; i <= n; i ++){
			int u = max_element(a[i].begin() + 1, a[i].begin() + l[i] + 1) - a[i].begin();
			edge[nm + u].eb(mp(c[i][u] + 1 + m, 0));
			du[c[i][u] + 1 + m] ++;
			vector<int> stk(l[i] + 5, 0);
			vector<int> cq(l[i] + 5, 0);
			int top = 0;
			for(int j = l[i]; j >= 1; j --){
				while(top && a[i][stk[top]] <= a[i][j])
					top --;
				cq[j] = stk[top];
				stk[++ top] = j;
			}
			for(int j = 1; j <= l[i]; j ++){
				if(!cq[j]) continue;
				if(a[i][cq[j]] != a[i][j])
					edge[nm + j].eb(mp(nm + cq[j], 1));
				else edge[nm + j].eb(mp(nm + cq[j], 0));
				du[nm + cq[j]] ++;
			}
			nm += l[i];
		}
		queue<int> q;
		vector<int> topo(N + 5, 0);
		int tot = 0;
		for(int i = 1; i <= N; i ++){
			if(du[i] == 0) q.emplace(i);
		}
		while(!q.empty()){
			int u = q.front();
			topo[++ tot] = u;
			q.pop();
			for(auto [v, w] : edge[u]){
				du[v] --;
				if(du[v] == 0) q.emplace(v);
			}
		}
		int t = m + 1 + b.size();
		for(int i = 1; i <= tot; i ++){
			int u = topo[i];
			for(auto [v, w] : edge[u]){
				f[v] = max(f[v], f[u] + w);
			}
		}
		cout << f[t] << "\n";
		return 0;
	}
}
signed main(){
#ifndef DEBUG
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
#endif
	int T = 1;
	cin >> T;
	while(T --)
		azus::main();
	return 0;
}
```

---

## 作者：Hiiragi_Utena (赞：5)

一种单调栈优化 dp 的解法。

---

首先，很容易想到，对于每张专辑（令其为第 $i$ 张），如果其中第 $j$ 首歌曲满足 $a_{i,j}\leq\max_{k=1}^{i-1}\{a_{i,k}\}$，那么这首歌对答案无贡献。

由此，可以把每张专辑中歌曲的“炫酷度”看做单调递增的。不妨设此时第 $i$ 张专辑有 $k'_i$ 首歌曲。

---

另外，对于一种已经确定的专辑的收听顺序，对于某张专辑，如果存在另一张专辑在它前面被收听，且最后一首歌曲（即其中“炫酷度”最高的歌曲）的“炫酷度”$\geq$ 这张专辑最后一首歌曲的“炫酷度”，那么在这张专辑对答案无贡献。

于是可以把问题转化为：对于所有专辑，按照最后一首歌的“炫酷度”从小到大排序。在这里面选出若干个，依次收听，问最多带来多少“好感”。

---

有了上面两个性质，不难想到可以 dp。令 $dp_i$ 为【对于前 $i$ 张专辑，且第 $i$ 张专辑必须听】的答案。

容易想到 $O(n^2)$ 的转移：

$$dp_i=\max_{1\leq j\leq i-1,a_{j,k'_j}<a_{i,k'_i}}\{dp_j+(k'_i-l+1)\}$$

其中 $l$ 为满足 $a_{i,l}>a_{j,k'_j}$ 的最小正整数。

换一种思路：不必枚举 $j$，可以去枚举 $l$：

$$dp_i=\max_{l=1}^{k'_i}\{dp_j+(k'_i-l+1)\}$$

其中 $j$ 为满足 $a_{j,k'_j}<a_{i,l}$ 的，使 $dp_j$ 最大的正整数。其中，$a
_{j,k'_j}$ 具有单调递增，所以满足 $a_{j,k'_j}<a_{i,l}$ 的 $j$ 为某个数以内的所有正整数。而这个数可以通过二分求出。

对 $j$ 的表达进行简化：用单调栈维护 dp 数组。显然，对于 $i>j,dp_i\leq dp_j$，则 $dp_i$ 不会产生贡献。因为 $a_{i,k'_i}\geq a_{j,k'_j}$，而 $dp_i\leq dp_j$（可以理解为：$dp_i$ 比 $dp_j$ 的门槛更高，贡献却更少）。

因此，单调栈内 dp 数组是单调递增的。所以转移方程中 $j$ 就是满足 $a_{j,k'_j}<a_{i,l}$ 的最大的 $j$。

由此，单次转移可以 $O(k'_i\log n)=O(k_i\log n)$。总复杂度为 $O(\log n\sum k_i)=O(n\log n)$。

---

代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
using namespace std;
const int maxn=200005;
int T,n,num[maxn],dp[maxn],mv[maxn],top;
vector<int>p[maxn];
struct node{
	int id,val;
	bool operator<(const node& tmp)const{
		return val<tmp.val;
	}
}l[maxn];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		top=0;
		for(int i=1;i<=n;++i){
			scanf("%d",&num[i]);
			dp[i]=mv[i]=0;
			p[i].clear();
			for(int j=1;j<=num[i];++j){
				int tmp;scanf("%d",&tmp);
				if(p[i].size()==0||tmp>p[i][p[i].size()-1]){
					p[i].push_back(tmp);
				}
			}
			l[i].id=i;l[i].val=p[i][p[i].size()-1];
		}
		int ans=0;
		sort(l+1,l+n+1);
		for(int i=1;i<=n;++i){
			int now=l[i].id,na=0,tv=l[i].val;
			for(int j=0;j<=p[now].size();++j){
				int tmp;
				if(j<p[now].size())tmp=p[now][j];
				else tmp=0x3f3f3f3f;
				int pt=lower_bound(mv+1,mv+top+1,tmp)-mv;
				pt--;
				na=max(na,dp[pt]+(int)p[now].size()-j);
			}
			ans=max(ans,na);
			if(top&&tv==mv[top]&&dp[top]<na)--top;
			if(dp[top]<na){
				mv[++top]=tv;
				dp[top]=na;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
} 
```

---

## 作者：zac2010 (赞：4)

排序加树状数组优化动态规划题。

我们先存下每个组合中数值比当前组合前面的最大值还大的所有数值，存在动态数组里。

我们按照 $n$ 动态数组最后的元素排序进行处理（动态数组中最后的元素即一个组合中最大的元素）——假设前面比后面大，那后面的贡献就只能为 $0$ 了。

至于处理，我们可以由前面任意位置转移而来，转移的话可以枚举从当前动态数组那个点开始有贡献，即前面的最大数必须小于当前的枚举的位置。

时间复杂度是线性再带一个 $\log$ 级别的。

[代码](https://codeforces.com/contest/1802/submission/196768423)。

---

## 作者：PikachuQAQ (赞：1)

## Description

[Link](https://www.luogu.com.cn/problem/CF1801C)

## Solution

对于每个数列，我们进行一个预的处理：扫一遍数列，只加入一些数，使得数列单调递增。

为什么呢？对于一个数列，它对于最长上升子序列的最大贡献为这个数列的最大值。那么把这个数列最长的单调递增的序列拿出来，固定 $r=a_j$，其中，$a_j$ 为最大值，我们枚举 $l\in[1,r-1]$，进行一个贡献的计算，看哪个数列的最长上升子序列贡献最大取最大贡献即可。

如有数列 $a = \{4, 2, 3, 5, 1\}$，我们取出它的最长上升子序列 $a'=\{2,3,5\}$，对于这个序列，我们算一下最大的贡献，就是求 $\{5\}$，$\{3,5\}$，$\{2,3,5\}$ 的最大贡献。

怎么算最大贡献呢？我们进行一个 dp：有 $f_i$ 表示数列 $i$ 的最大贡献，显然，状态转移方程是：

$$f_i=\max(f_i,f_j+l_i)$$

其中，$l_i$ 表示子最长上升子序列的长度，$f_j$ 中的 $j$ 是枚举从 $l-1$ 到 $1$，枚举的子序列的左端点。

主要是这个 $f_j$，需要更新最大值。非常的恶心。这使得时间复杂度到达了 $O(n^2)$。

我们需要一个区间修改，单点查询最大值的数据结构。

树状数组可以实现。我们开一个树状数组 $c$，$c_i$ 表示以 $i$ 为右端点的最长上升子序列长度。

然后我们查询 $i$ 数列中保留的数最小的那位（不包括它自己）的
数列的最大值，这样就把 $O(n)$ 的更新 $f_j$ 改成 $O(\log n)$ 的查询了。于是方程更新为：

$$f_i=\max(f_i,\operatorname{query}(a_i-1)+l_i)$$

最后求完 $f_i$ 后，我们更新答案最大值，随后将更新好的 $f_i$ 插入树状数组中即可。

注意多测要清空。 

## Code

```cpp
// 2023/9/22 _Pikachu_

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int kMaxN = 2e5 + 7;

int t, n, ans, f[kMaxN], c[kMaxN];
vector<vector<int> > b;

int lowbit(int x) {
    return x & -x;
}

void add(int x, int y) {
    for (int i = x; i < kMaxN; i += lowbit(i)) {
        c[i] = max(c[i], y);
    }
}

int sum(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) {    
        res = max(res, c[i]);
    }
    return res;
}

void clear(int x) {
    for (int i = x; i < kMaxN; i += lowbit(i)) {
        c[i] = 0;
    }
}

bool cmp(vector<int> &x, vector<int> &y) {
    return x.back() < y.back();
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    for (cin >> t; t; t--) {
        cin >> n;
        b.clear(), b.resize(n + 1);
        for (int i = 1, k = 0; i <= n; i++) {
            cin >> k;
            for (int j = 1, a = 0; j <= k; j++) {
                cin >> a;
                if (b[i].size() == 0 || a > b[i].back()) {
                    b[i].push_back(a);
                }
            }
        }
        sort(b.begin() + 1, b.end(), cmp);
        for (int i = 1; i <= n; i++, ans = max(ans, f[i - 1])) {
            for (int j = b[i].size() - 1, cnt = 0; j >= 0; j--) {
                f[i] = max(f[i], ++cnt + sum(b[i][j] - 1));
            }
            add(b[i].back(), f[i]);
        }
        cout << ans << '\n';
        for (int i = 1; i <= n; i++) {
            clear(b[i].back());
        }
        ans = 0, fill(f, f + n + 1, 0);
    }

    return 0;
}
```

---

## 作者：MuelsyseU (赞：1)

显然我们把最小值和最大值，对每个序列搞出一个值域区间。那么每个序列在对应的值域区间内撒点（必须保证这些点都是起码在自身序列内是严格前缀最大值）。

那么就是选一些区间，每个区间内有一部分点贡献为 $1$。

很显然一定是按照右端点升序顺序去选，否则最大值都比先前的小，这个序列就没有任何贡献。 

于是任何重叠部分中只有右端点最小的那个区间内的这部分的点有贡献。显然不会选被完全包含的区间，所以 DP 一下就可以了。 

每个区间的贡献一定是一个后缀，直接枚举这个后缀包含的点数 $t$，总共只枚举 $O(n)$ 次。然后找右端点在 $(x_{t+1}, x_t]$ 内的 $f$ 的最值，拿 $f_j + t$ 更新 $f_i$。

其中 $x_t$ 表示从右往左第 $t$ 个严格前缀最大值的值。

线段树解决这个问题。$O(n \log n)$。

```cpp
#include <bits/stdc++.h>
#define ls(p) (p << 1)
#define rs(p) (p << 1 | 1)
#define mid ((l + r) / 2)
using namespace std;

const int inf = 0x3f3f3f3f, maxn = 200005;
int T, n, x, y, l[maxn], r[maxn], p[maxn];
vector<int> a[maxn], b[maxn];
int ans, t[maxn * 6], f[maxn];
inline bool cmp(int x, int y) {
	return r[x] < r[y];
}
inline void reset(int p, int l, int r, int i) {
	if (l > i || r < i) return;
	t[p] = 0;
	if (l != r) reset(ls(p), l, mid, i), reset(rs(p), mid + 1, r, i);
}
inline void insert(int p, int l, int r, int i, int x) {
	if (l > i || r < i) return;
	t[p] = max(t[p], x);
	if (l != r) insert(ls(p), l, mid, i, x), insert(rs(p), mid + 1, r, i, x);
}
inline int query(int p, int l, int r, int ql, int qr){
	if (l > qr || r < ql) return -inf;
	if (l >= ql && r <= qr) return t[p];
	return max(query(ls(p), l, mid, ql, qr), query(rs(p), mid + 1, r, ql, qr));
}
signed main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n), ans = 0;
		for (int i = 1; i <= n; ++i) {
			l[i] = inf, r[i] = -inf, a[i].clear(), b[i].clear();
			scanf("%d", &x), p[i] = i;
			while (x--) {
				scanf("%d", &y), a[i].push_back(y);
				if (r[i] < y) r[i] = y, b[i].push_back(y);
				if (l[i] > y) l[i] = y;
			}
		}
		sort(p + 1, p + n + 1, cmp);
		for (int x = 1; x <= n; ++x) {
			int i = p[x];
			int sz = b[i].size();
			f[i] = query(1, 0, maxn, 0, r[i]);
			f[i] = max(f[i], query(1, 0, maxn, 0, b[i][0] - 1) + sz);
			for (int j = 0; j < sz - 1; ++j)
				f[i] = max(f[i], query(1, 0, maxn, b[i][j], b[i][j + 1] - 1) + sz - j - 1);
			ans = max(ans, f[i]), insert(1, 0, maxn, r[i], f[i]);
		}
		for (int x = 1; x <= n; ++x) reset(1, 0, maxn, r[p[x]]);
		printf("%d\n", ans);
	}
	return 0;
} 
```

---

## 作者：wycha (赞：1)

## 题意
$n$ 个序列，每个序列 $a_i$ 的长度为 $k_i$，$\sum k_i\leqslant 200\ 000$。  
以任意顺序排列，使最后得到的序列中，比前面所有数大的数数量最多。  
*（反正**不是**最长上升子序列，我不会更简洁的表达，有巨佬教教吗？）*

## 题解
对每个序列，按严格单调递增化简。  
可以发现每个序列只有结尾（最大值）影响了之后的贡献，所以首先考虑结尾数字小的，再考虑大的。

设 $dp[i]$ 表示 $i$ 为结尾时获得的最大贡献，每个序列 $a_i$ 的结尾（最大值）为 $v_{a_i}$，  
那么每个序列只会对 $dp[v_{a_i}]$ 产生贡献。

因此排完序后，遍历序列 $a_i$，对于 $a_i[j]$，  
$dp[v_{a_i}] \gets\max(dp[v_{a_i}], \max_{\ 1\leqslant k\leqslant a_i[j] - 1}\ dp[k] + a_i.\operatorname{length} - j)$，  
结果就是 $dp[\max v_{a_i}]$。

其中求 $\max_{\ 1\leqslant k\leqslant a_i[j] - 1}\ dp[k]$ 可用线段树完成，总的时间复杂度 $\mathcal{O}((\sum k_i+\sum n)\log V)$，其中 $V$ 是值域，$\sum n \leqslant\sum k_i\leqslant 200\ 000$，可过。

```cpp
#include <bits/stdc++.h>
//码头
#define ll long long
#define il inline
#define gtc getchar()
#define ptc(x) putchar(x)
#define rd read()
il int read(){int x=0;char c=gtc;while(c<'0'||c>'9')c=gtc;while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=gtc;}return x;}
il int max(int x, int y){return (x > y) ? x : y;}

const int N = 200010;
const int mxn = 200000;
std::vector<int>a[N];
int v[N], rk[N];

//线段树维护最大值 
int t[N << 2];
il int ls(int o){return o << 1;}
il int rs(int o){return o << 1 | 1;}
il void pushup(int o){t[o] = max(t[ls(o)], t[rs(o)]);}
il void build(int o, int l, int r){
	t[o] = 0;
	if(r <= l) return;
	int m = l + r >> 1;
	build(ls(o), l, m);
	build(rs(o), m + 1, r);
}
void upd(int o, int l, int r, int k, int x){
	if(r <= l) {t[o] = max(t[o], x); return ;}
	int m = l + r >> 1;
	if(k <= m) upd(ls(o), l, m, k, x);
	else upd(rs(o), m + 1, r, k, x);
	return (void)(pushup(o));
}
int query(int o, int l, int r, int x, int y){
	if(x > y) return 0;
	if(x <= l && y >= r) return t[o];
	int m = l + r >> 1, mx = 0;
	if(x <= m) mx = query(ls(o), l, m, x, y);
	if(y > m) mx = max(mx, query(rs(o), m + 1, r, x, y));
	return mx;
}
void cov(int o, int l, int r, int k, int x){
	if(r <= l) {t[o] = x; return ;}
	int m = l + r >> 1;
	if(k <= m) cov(ls(o), l, m, k, x);
	else cov(rs(o), m + 1, r, k, x);
	return (void)(pushup(o));
}

il void work();
signed main(){int T=rd;while(T--)work();return 0;}

il bool cmp(int x, int y){return v[x] < v[y];}
il void work(){
	
	int n = rd;
	int i, x, j, ls, k, mx;
	for(i = 1; i <= n; ++i){
		k = rd;
		ls = rd;
		a[i].clear();
		a[i].push_back(ls);
		for(j = 2; j <= k; ++j){
			x = rd;
			if(x > ls) a[i].push_back(x), ls = x;
			//序列化简，vector存储
		}v[i] = ls;
		rk[i] = i;
	}

	std::sort(rk + 1, rk + 1 + n, cmp);//按最大值排序

	upd(1, 1, mxn, v[rk[1]], a[rk[1]].size());
	for(k = 2, i = rk[k]; k <= n; ++k, i = rk[k]){
		mx = 0;
		for(j = 0; j < a[i].size(); ++j){
			mx = max(mx, query(1, 1, mxn, 1, a[i][j] - 1) + a[i].size() - j);;
			//查询dp[1]~dp[aij - 1]的最大值
		}upd(1, 1, mxn, v[i], mx);//更新dp[Vai]
	}

	printf("%d\n", t[1]);
	for(int i = 1; i <= n; ++i) cov(1, 1, mxn, v[i], 0);
	//清空，这里要注意

	return;
}
```

一个小细节是不能每次重新建树，那样时间复杂度是 $\mathcal{O}(tV)$，假了。  
蒟蒻第一次写题解，欢迎提意见。

---

## 作者：Xy_top (赞：0)

一道需要挖掘一些性质的 dpt，居然独立想出来了。

本蒟蒻太菜了只会树状数组的做法，单调栈不会。

先考虑只管对答案有贡献的音乐，这当然是正确的，因为我们可以把对答案没有贡献的音乐放到最后。

对于每一首乐曲，我们也能对它进行一个简单的处理来模拟听的过程，维护一个值 $lst$，每次输入的数 $x$ 如果大于 $lst$，那么听了这个片段后答案就会加一，将 $x$ 存入数组中，否则忽略它。

假设每个音乐的好听程度为其中最美妙的片段。

处理后有一个可以感性理解的结论：无论当前听过的最好听的片段是什么，听了一首乐曲，能够使答案增加的一定是存入数组中的片段。

证明考虑反证，假设当前听过最好听的片段好听值为 $mx$，现在听乐曲 $i$，能够找到一个位置使得 $a_{i,j} \geq mx$ 且 $a_{i,j}$ 被忽略。这是显然不可能得一件事，因为如果 $a_{i,j}$ 被忽略，就说明前面有一个更好听的片段，而 $mx$ 应该先听到的是更好听的片段就忽略了 $a_{i,j}$。

再来想，有答案贡献的音乐放在一起，每个音乐的好听程度一定是递增的。

做法于是很显然了，先将所有音乐按照好听程度排序，设 $f_i$ 为考虑第 $1$ 个音乐到第 $i$ 个音乐，其中第 $i$ 个音乐必须选的最大答案，设 $mx_j$ 为第 $j$ 首乐曲的好听程度，那么大体结构就是枚举前一个听的乐曲 $j$，然后再算出听 $i$ 之后的答案，所有的取个 $\max$ 即可。

上述为 $O(n^2)$ 做法，很烂，会超时，貌似可以用单调栈优化，超时原因是没有用到 $\sum k_i \leq 200000$ 这个条件。

考虑对于每一个乐曲的转移改为枚举这个乐曲中的每一个没被忽略的片段，然后去找前面的某个乐曲 $j$，使得 $j$ 的好听程度 $<$ 这个片段的美妙值，然后就能从 $dp_j$ 转移过来，再听这个片段以及这个片段后面没有被忽略的。

很绕口，读不懂多读几遍，然后这是个单点修改求前缀最值可以用树状数组优化到 $O(n\log n)$。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, x, cnt;
int c[200005], dp[200005], idx[200005];
vector <int> a[200005];
vector <int> v[200005];
void add (int x, int y) {for (; x <= 200000; x += x & -x) c[x] = max (c[x], y);}
int query (int x) {return (x == 0 ? 0 : max (query (x - (x & -x) ), c[x]) );}
void clear (int x) {for (; x <= 200000; x += x & -x) c[x] = 0;}
set <int> s;
void solve () {
	s.clear ();
	scanf ("%lld", &n);
	For (i, 1, n) {
		scanf ("%lld", &cnt);
		int last = 0;
		while (cnt --) {
			scanf ("%lld", &x);
			if (x > last) {
				a[i].push_back (x);
				last = x;
			}
		}
		s.insert (last);
		v[last].push_back (i);
	}
	cnt = 0;
	for (int i : s) for (int j : v[i]) idx[++ cnt] = j;
	int ans = 0;
	For (i, 1, n) {
		for (int j = 0; j < a[idx[i] ].size (); j ++)
			dp[i] = max (dp[i], query (a[idx[i] ][j] - 1) + (long long) (a[idx[i] ].size () ) - j);
		add (a[idx[i] ].back (), dp[i]);
		ans = max (ans, dp[i]);
	}
	cout << ans;
	For (i, 1, n) {
		clear (a[i].back () );
		v[a[i].back ()].clear ();
		a[i].clear ();
		dp[i] = 0;
	}
}
signed main () {
	int _ = 1;
	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}

```


---

## 作者：Fishing_Boat (赞：0)

首先，这道题我们不难发现，一个数如果在自己这个序列中都不是严格前缀最大值，那么它对答案是没有任何贡献的。

其次，就是假设当前已经排好的序列的最大值是 $x$，那么剩下的序列中最大值小于 $x$ 的序列都不会产生贡献。于是问题就转化成将序列按序列中最大值从小到大排序，每个序列都可以选或不选，求最终的贡献。

设 $dp_i$ 表示当前拼接成的序列的最大值不超过 $i$ 的所有选法中的最大值，那么一个新的序列 $a_i$，所产生的最大贡献也就是 $\max\limits_{j=1}^{j\le k_i} dp_{a_j-1}+k_i-j+1$，用树状数组维护一下即可。
```cpp
#include<bits/stdc++.h>
#define inf 0x7fffffff
#define ll long long
#define cmax(a,b) a=max(a,b)
#define cmin(a,b) a=min(a,b)
#define rst(a,x) memset(a,x,sizeof(a))

using namespace std;

vector <int> v[200005],his;
int n,val[200005],dp[200005],maxv,id[200005];

bool cmp(int x,int y){
	return v[x][v[x].size()-1]<v[y][v[y].size()-1];
}

int lowbit(int x){
	return x&(-x);
}

void add(int x,int val){
	his.push_back(x);
	for(;x<=maxv;x+=lowbit(x)) cmax(dp[x],val);
}

void clr(int x){
	for(;x<=maxv;x+=lowbit(x)) dp[x]=0;
}

int query(int x){
	int res=0;
	for(;x;x-=lowbit(x)) cmax(res,dp[x]);
	return res;
}

void clear(){
	for(auto x:his) clr(x);
	his.clear();
}

int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	int t;
	cin>>t;
	while(t--){
		int tot=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			id[i]=i;
			v[i].clear();
			int m,maxn=0;
			cin>>m;
			for(int j=1;j<=m;j++){
				int x;
				cin>>x;
				if(x>maxn) v[i].push_back(x);
				cmax(maxn,x);	
			}
			cmax(maxv,maxn);
		}
		sort(id+1,id+n+1,cmp);//排序时要注意不能直接用 vector 排，否则会 T 的飞起
		for(int x=1;x<=n;x++){
			int maxn=0,i=id[x];
			for(int j=0;j<v[i].size();j++){
				cmax(maxn,query(v[i][j]-1)+(int)v[i].size()-j);
			}
			add(v[i][v[i].size()-1],maxn);
		}
		cout<<query(maxv)<<'\n';
		if(t)clear();
	}
	return 0;
}

```

---

## 作者：liujy_ (赞：0)

 设 $dp_i$ 表示当前已经放好的序列中的最大值为 $i$ 的最大答案。  
 对于一个小的序列，如果前面已经放好的序列中的其中一个的最大值大于当前序列的最大值，那么当前序列不能对答案产生贡献。所以我们转移之前先把每个序列按最大值从小到大排序。   
 对于在最末尾放进一个新的序列，考虑如何转移。我们枚举序列中每一个数，钦定其为当前序列中第一个可以对答案产生的位置，这个位置必须是当前序列的前缀最大值。假设这一位的数值为 $x$，那么答案即为 $\max_{i=1}^x{dp_i}$ 加上它自己所处的小序列中以它开头的最长上升子序列。前面那个部分可以用树状数组维护前缀最大值，后面那部分用单调栈预处理好就行了。    
 ```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int N=2e5+5;
int t,n,maxn,ans,top,a[N],b[N],c[N],p[N],sta[N];
int id[N],mx[N],sum[N],pre[N],len[N],st[N];
bool cmp(int x,int y){return mx[x]<mx[y];}
void add(int x,int y){for(;x<=maxn;x+=x&-x)c[x]=max(c[x],y);}
int qry(int x){int s=0;for(;x;x-=x&-x)s=max(c[x],s);return s;}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);maxn=ans=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&len[i]);id[i]=i;
			st[i]=st[i-1]+len[i-1];mx[i]=0;
			if(i==1)st[1]=1;
			for(int j=st[i];j<st[i]+len[i];j++)scanf("%d",&b[j]),p[j]=b[j];
		}
		sort(p+1,p+st[n]+len[n]);
		int ll=unique(p+1,p+st[n]+len[n])-(p+1);
		for(int i=1;i<=n;i++){
			for(int j=st[i];j<st[i]+len[i];j++){
				b[j]=lower_bound(p+1,p+ll+1,b[j])-p;
				mx[i]=max(mx[i],b[j]),maxn=max(maxn,b[j]);
			}sum[0]=0;
			sta[top=1]=st[i]+len[i]-1;sum[sta[1]]=1;
			for(int j=st[i]+len[i]-2;j>=st[i];j--){
				while(top&&b[sta[top]]<=b[j])top--;
				sum[j]=sum[sta[top]]+1;
				sta[++top]=j;
			}
		}
		for(int i=1;i<=maxn;i++)c[i]=0;sort(id+1,id+n+1,cmp);
		for(int i=1;i<=n;i++){int x=0,mxx=0;
			for(int j=st[id[i]];j<st[id[i]]+len[id[i]];j++){
				if(b[j]>mxx)x=max(x,qry(b[j]-1)+sum[j]);
				mxx=max(b[j],mxx);
			}
			add(mx[id[i]],x);ans=max(ans,x);
		}
		printf("%d\n",ans);
	}
	return 0;
}

```



---

## 作者：六楼溜刘 (赞：0)

## 题意
- 给你 $n$ 个数列，你要把它们按任意顺序首尾连接起来。
- 最大化连接后能成为严格前缀最大值的数的数量。
- 多组测试数据，$1 \leq n \leq 2 \times 10^5$。

## 题解
首先这道题看起来就像 DP。

我们发现，在每个数列里面，本来就不能成为严格前缀最大值的数不可能对最终结果产生贡献，我们可以直接把它们删掉。

另外我们还发现，如果把所有序列按序列最大值升序排序，每次将靠后的接在靠前的后面，最终答案必然是不劣的（感性理解，如果将小的排在大的后面，那绝对不可能产生贡献，反之就有可能）。

做完这两步后，我们开始考虑 DP 的状态。我的做法是定义 $dp_i$ 为以数值 $i$ 结尾的最大贡献。

对于转移，我们发现，每个序列的每个后缀都可能产生贡献。

![图片示意](https://cdn.luogu.com.cn/upload/image_hosting/2slsubp7.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

比如像这样，接在前面时整个红色的后缀都会产生贡献。

所以对于排序后第 $p$ 个序列，转移方程为：

$$dp_{M_p}=\max\limits_{i=1}^{k_p}(\max\limits_{j=0}^{a_{p,i}}dp_j+k_p-i+1)$$

其中 $M_p$ 为第 $p$ 个序列的最大值（即处理后的最后一项），$k_p$ 为题目中第 $p$ 个序列的长度。

我们发现，这样做的时间复杂度是 $O(\sum k_i \times lim)$（$lim$ 表示值域）的，保准会 TLE，这时我们只需要简单地用树状数组维护一下 $dp$ 数组的前缀最大值，就可以在 $O(\log lim)$ 的复杂度内实现转移。

排序的时间复杂度为 $O(n \log n)$，DP 的时间复杂度为 $O(\sum k_i \times \log lim)$ 的。有多组数据，故总的复杂度为 $O( t\times \text{初始化需要的时间}+\sum( n \log n)+ \sum k_i \times \log lim)$。但这其实是非常危险的，我们要注意一下初始化不能是 $O(lim)$ 的，不然容易被卡到 $O(n^2)$ 级别（正确的做法是回退每一次修改）。另外还要注意排序的常数，我们不要在比较函数里传参，而要用 `&` 引用来避免传整个 `vector` 巨大的常数，不然会 TLE。
## code
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<string.h>
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
#define gc getchar()
inline int read(){
	int x=0,f=1;char c;
	while(!isdigit(c=gc))if(c=='-')f=-1;
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=gc;}
	return x*f;
}
#undef gc
const int N=2e5+5;
int t,n;
vector<int> a[N];
struct tree{
	int c[N];
	void upd(int x,int k){for(;x<=N&&c[x]<k;x+=x&-x)c[x]=k;}
	int ask(int x){int res=0;for(;x;x-=x&-x)res=max(res,c[x]);return res;}
	void clear(int x){for(;x<=N;x+=x&-x)c[x]=0;}
}dp;
inline bool cmp(vector<int> &a,vector<int> &b){
//引用
	return a.back()<b.back();
}
signed main(){
	t=read();
	while(t--){
		for(register int i=1;i<=n;i++){
			dp.clear(a[i].back());//回退之前的操作
			a[i].clear();
		}
		n=read();
		for(register int i=1;i<=n;i++){
			a[i].clear(); 
			int k=read();
			for(register int j=1;j<=k;j++){
				int ipt=read();
				if(a[i].empty()||ipt>a[i].back()){
					a[i].emplace_back(ipt);
				}
			}
		}
		sort(a+1,a+n+1,cmp);
		for(register int i=1;i<=n;i++){
			int len=a[i].size(),mx=a[i].back();
			for(register int j=len-1;j>=0;j--){
				dp.upd(mx,dp.ask(a[i][j]-1)+len-j);
			}
		}
		printf("%d\n",dp.ask(N));
	}
}

```


---

