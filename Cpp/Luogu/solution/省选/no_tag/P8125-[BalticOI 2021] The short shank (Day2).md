# [BalticOI 2021] The short shank (Day2)

## 题目描述

你入狱了，你现在正在洛谷第一监狱里。

监狱共有 $N$ 个牢房，从左到右编号为 $1 \sim N$。你和你的狱友们准备策划一场造反，第 $i$ 个牢房里的罪犯准备在第 $t_i$ 个时刻点造反，如果第 $i$ 个牢房的罪犯造反后，第 $i+1$ 个牢房的罪犯会无视他在第 $t_{i+1}$ 个时间点造反的规矩，在第 $t'_i+1$ 个时间点就会造反，其中 $t'_i$ 是第 $i$ 个牢房的罪犯实际造反的时刻。

狱警提前预知了一切，所以他们会放置 $D$ 个床垫，如果在第 $i$ 个牢房和第 $i+1$ 个牢房中间放置一个床垫，那么当第 $i$ 个牢房的罪犯造反时，第 $i+1$ 个牢房的罪犯不会立即造反，而会等到第 $t_{i+1}$ 个时间点。

你想知道，狱警合理安排床垫后，在第 $T$ 个时间点及以前最少会有多少个罪犯造反。

## 说明/提示

#### 样例 1 解释

最优解是在第 $2$ 个牢房和第 $3$ 个牢房之间放入床垫，造反的是第 $1,2,4,5$ 个牢房里的罪犯。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（15 pts）：$N \le 500$。
- Subtask 2（10 pts）：$N \le 5 \times 10^5$，$D=1$。
- Subtask 3（20 pts）：$N \le 4000$。
- Subtask 4（10 pts）：$N \le 7.5 \times 10^4$，$D \le 15$。
- Subtask 5（25 pts）：$N \le 7.5 \times 10^4$。
- Subtask 6（20 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le D<N \le 2 \times 10^6$，$1 \le T,t_i \le 10^9$。

另有 Subtask 0 为样例。

#### 说明

翻译自 [BalticOI 2021 Day2 A The short shank](https://boi.cses.fi/files/boi2021_day2.pdf)。

## 样例 #1

### 输入

```
5 1 42
13 37 47 11 42```

### 输出

```
4```

## 样例 #2

### 输入

```
5 2 5
1 9 4 6 7```

### 输出

```
2```

# 题解

## 作者：Pekemetier (赞：8)

题意：

>若干间牢房，其中一些会在 $t_i$ 暴乱，每过一时刻所有暴乱的人会使右边的下一个人暴乱（如果没暴乱的话）。可以在至多 $D$ 个人右边放挡板，使其无法传染给下一个人。求 $T$ 时刻最少有多少人暴乱。

显然对于 $t_i>T$ 的 $i$ ，是不会自己暴乱的，只会由其左边的人影响过来（称为 “**传染**” ）。我们把这些人称作 “**普通点**” 。反之，会自己暴乱的点称为 “**特殊点**” 。

同时显然的还有：对于一段连续的普通点，最多只会在其左端点的左侧放置隔板；对于一段连续的特殊点，最多只会在其右端点的右测放置隔板。

然后我们会想到两种统计贡献的方式：对特殊点统计和对普通点统计。
但在研究一番后，发现没有有效的对关键点统计的方法。主要是因为只能设计 dp 维护，但它的状态数是 $O(ND)$ 的。

于是我们对普通点进行统计，令 $l_i$ 表示第一个能传染到他的关键点，那么一个点不会被传染 **当且仅当没有 $l_i$ 或 $[l_i,i]$ 中有隔板** 。

但如果这样进行 dp ，状态数还是 $O(ND)$ 的，怎么办呢？我们发现对于两个普通点 $i<j$ ，必然有 $l_j\leq l_i<i<j$ 或 $l_i<i<l_j<j$ ，既 **只有包含或相离，没有相交** 。

>证明：即证不存在 $l_i<l_j<i<j$ ，此时有 $l_j+(T-t_{l_j})\geq j>i$ ，所以 $l_i$ 应该是更大的 $l_j$ ，矛盾。

对于每个普通点，把满足 $l_j\leq l_i<i<j$ 的最小普通点 $j$ （如果有的话）认作父亲，然后就会建出一个森林。对于森林中的每个叶节点，满足 $l_i=i-1$ ，在 $l_i$ 和 $i$ 之间放一个隔板，会且只会让树上从 $i$ 到根的所有结点不会暴乱。同时，对于任意一种有贡献的放隔板法，必然能找到板子后面第一个 $i$ 使得它到根节点路径上的节点不会暴乱。

因此在树上选 $D$ 条从叶节点向上的不交的链，使其点集交最大即可。可以 **长链剖分** 后，选前 $D$ 长链。

>证明：首先对于一个最优解，每一条链都会让最上端点尽量往上。那么对于一种可能的最优解：
>
>![](https://cdn.luogu.com.cn/upload/image_hosting/91o6g5ya.png?x-oss-process=image/resize,m_lfit,h_170,w_225)~~图丑勿怪~~
>
>讨论某一点的子树，对于一条过根却不是最长链的链（A），如果最长链剩下部分有边，不妨（？）假设剩下部分只有一条链（B），且其包含了最长链剩下部分所有的点，那么将 A 下半部与 B 交换，答案不变；如果最长链剩下部分无边，将 A 直接变成最长链，答案也不降。
>
>对于 “不妨”，可以先向下讨论最长链下方子树，就能得到最长链内只有一条链的结论。

建树时可以顺序依次枚举，将还能施加影响的特殊点及 $l_i$ 是该点的最大的 $i$ 在栈中维护，每次清掉栈顶不可能传染到他的特殊点（肯定也影响不到后面），在清掉的点和第一个能传染到他的点中选深度最大的作为长链并且标上标记（在另一个点的长链中），然后顶掉栈顶的 $i$ 。

把没有 $l_i$ 的点直接加入答案，最后把所有未标记的链扔到优先队列选前 $D$ 长即可。

Code：
```cpp
#include<cstdio>
#include<queue>
#define max(a,b) (a>b?a:b)
using namespace std;
int n,d,t,a[2000001],ans;
int h[2000001],hp[2000001];
int st[2000001],v[2000001],num;
bool vis[2000001];
int main()
{
	scanf("%d%d%d",&n,&d,&t);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		if(a[i]<=t)
		{
			st[++num]=i;
			v[num]=i;
		}
		else
		{
			while(num&&st[num]+t-a[st[num]]<i)
			{
				if(h[v[num]]>h[i])
				{
					h[i]=h[v[num]]；
					hp[i]=v[num];
				}
				--num;
			}
			if(num)
			{
				if(h[v[num]]>h[i])
				{
					h[i]=h[v[num]]；
					hp[i]=v[num];
				}
				++h[i];
				vis[hp[i]]=1;
				v[num]=i;
			}
			else ++ans,vis[i]=1;
		}
	}
	priority_queue<int>q;
	for(int i=n;i;--i)
		if(!vis[i])
			q.push(h[i]);
	while(d--)
	{
		if(q.empty())break;
		ans+=q.top();q.pop();
	}
	printf("%d",n-ans);
}
```


---

## 作者：Creeper_l (赞：3)

首先会发现若 $t_i <= T$ 的话那么他最终一定会造反。

我们只考虑 $t_i >T$ 的情况。设 $lst_i$ 表示 $i$ 左边第一个可以影响（使他造反）到 $i$ 的位置，那么我们一定要在 $[lst_i,i]$ 这个区间中的某一个位置放上床垫才能使 $i$ 不造反。

这样有一个 $O(nd)$ 的 dp，但是复杂度显然会炸。考虑挖掘一些性质，会发现**所有区间都是包含或者不交的**。证明也比较简单，若两个区间有交，即 $i<j,lsti \le lst_j \le i$，那么 $lst_j$ 这个位置也一定能影响到 $i$，矛盾。所以任意两个区间都不交叉。

那么我们按照区间的包含关系建图，就变成了一个森林。考虑转化题意，若在叶子节点的区间中放一个床垫，那么它到根节点的路径上的所有点都不会造反了。所以题意转化为求 $d$ 条不相交的链，使得这些链的总长度最大。这个问题直接长链剖分，然后取前 $d$ 长的链即可。

求 $lst$ 数组以及连边都可以用单调栈维护，最终求前 $d$ 长链可以用优先队列维护，时间复杂度 $O(n+d \log n)$。

关于取前 $d$ 长的链的简单证明：对于两条不是最长链的链，我们都可以把它换成最长链加另外一条链，这样总长度一定不劣（画个图更容易理解）。

```
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e6 + 10;
int n,d,T,t[MAXN],lst[MAXN],ans,fa[MAXN];
int head[MAXN],cnt,depth[MAXN],son[MAXN],mx[MAXN];
struct Node {int u,v,nxt;}e[MAXN << 1];
void Add(int u,int v) {e[++cnt] = {u,v,head[u]};head[u] = cnt;}
priority_queue <int,vector <int>,less <int> > q;
void dfs(int u,int father) {
	depth[u] = depth[father] + 1,mx[u] = depth[u];
	for(int i = head[u]; ~ i;i = e[i].nxt) {
		int now = e[i].v;
		if(now == father) continue;
		dfs(now,u),mx[u] = max(mx[u],mx[now]);
		if(mx[now] > mx[son[u]]) son[u] = now;
	}
} void sdfs(int u,int father,int len) {
	if(son[u] == 0) return q.push(len);
	sdfs(son[u],u,len + 1);
	for(int i = head[u]; ~ i;i = e[i].nxt) 
		if(e[i].v != father && e[i].v != son[u]) sdfs(e[i].v,u,1);
} stack <int> s;
signed main() {
	memset(head,-1,sizeof head);
	cin >> n >> d >> T;
	for(int i = 1;i <= n;i++) cin >> t[i];
	for(int i = 1;i <= n;i++) 
		if(t[i] > T) {
			while(s.size() && t[s.top()] + i - s.top() > T) s.pop(); 
			if(s.size()) lst[i] = s.top();
		} else {
			while(s.size() && t[s.top()] + i - s.top() >= t[i]) s.pop(); 
			s.push(i);
		}
	while(!s.empty()) s.pop();
	for(int i = n;i >= 1;i--) {
		if(lst[i] == 0) continue;
		while(!s.empty() && lst[s.top()] > lst[i]) s.pop();
		if(!s.empty()) Add(s.top(),i),fa[i] = s.top();
		s.push(i); 
	} for(int i = 1;i <= n;i++) {
		if(t[i] <= T) continue;
		if(lst[i] == 0) ans++;
		else if(fa[i] == 0) dfs(i,0),sdfs(i,0,1);
	} while(d > 0 && !q.empty()) 
		ans += q.top(),q.pop(),d--; 
	cout << n - ans;
	return 0;
} 
```

---

## 作者：2018ty43 (赞：3)

### 思路：
首先，如果 $t_{i+1}\le T$ ，第 $i$ 个囚犯必定造反。  
如果某一囚犯左侧没有在 $T$ 之前造反的囚犯，或没有能使该囚犯在 $T$ 之前造反的囚犯，则该囚犯必定不造反。  
因此，要尽量使剩下的尽可能不造反。

某一可能会造反的囚犯不会造反，当且仅当在该囚犯与可以使其造反的最近囚犯之间有一个床垫。  
可以使某一囚犯造反的最近个囚犯可以通过单调栈求得，使栈囚犯中影响到现在访问的囚犯的时间依次递增，影响时间大于 $T$ 的舍弃，栈中最新的囚犯即为使其造反的最近囚犯。

**结论一**  
当某囚犯与可以使其造反的最近囚犯之间存在一个（可能造反的）囚犯没造反，则该囚犯也不会造反。  
显然，该囚犯造反需要使其造反最近囚犯依次使他们中间的囚犯造反，当存在一个囚犯没造反，说明有床垫挡着了，造反也就无法传递。

因此，可以由每一囚犯向其与使其造反的最近囚犯间未被连边的囚犯连边，被连边的说明在右侧有可能造反的囚犯，则已向其等效连边。  
由此形成一个森林，要在其中选 $D$ 个点左侧放床垫，并使被选中的点的祖先节点尽可能多。

**结论二**  
存在一种最优选择方案，选择当前森林中任意一最深节点。  
证明：当任意一最深节点不被选时，如果该树有节点被选，总能找到被选的节点中与其 LCA 最近的节点并替换该节点，新方案结果一致。  
如果该树上没被选的节点，则任意找一被选节点并替换，方案不会变劣。

实现可以用优先队列维护每个节点的子树最深深度，并记录子树最深的儿子，每次找到未被选的节点，一路访问下去，在叶子结点左边放床垫。


### AC代码
```cpp
#include<cstdio>
#include<queue>
struct ed
{
	int x,w;
	bool operator<(const ed &op)const
	{
		return this->w<op.w;
	}
};
std::priority_queue<ed>aa;
int n,d;
long long T,t;
int ans;
int ll;
int quef[2000009],quet[2000009],tt;
int dep[2000009],bs[2000009];
int qu2[2000009],t2;
bool done[2000009];
void dfs(int u)
{
	done[u]=1;
	--ans;
	if(bs[u])dfs(bs[u]);
}
int main()
{
	scanf("%d%d%d",&n,&d,&T);
	for(int i(1);i<=n;++i)
	{
		scanf("%d",&t);
		if(t<=T)
		{
			while(tt&&(long long)(i-quef[tt])+quet[tt]>t)--tt;//维护使其造反最近囚犯的栈 
			quef[++tt]=i;
			quet[tt]=t;
			++ans;
		}
		else
		{
			dep[i]=1;
			while(tt&&(long long)(i-quef[tt])+quet[tt]>T)--tt;
			if(tt)
			{
				while(t2&&qu2[t2]>quef[tt])
				{
					if(dep[qu2[t2]]+1>dep[i])dep[i]=dep[qu2[t2]]+1,bs[i]=qu2[t2];//寻找子树最深的儿子 
					--t2;
				}
				aa.push((ed){i,dep[i]});
				qu2[++t2]=i;//维护未被连边节点的队列 
				++ans;
			}
		}
	}
	for(int i(1);i<=d&&(!aa.empty());++i)
	{
		int e0(aa.top().x);
		aa.pop();
		while(done[e0]&&(!aa.empty()))e0=aa.top().x,aa.pop();
		if(done[e0])break;
		dfs(e0);
	}
	printf("%d\n",ans);
}
```


---

## 作者：123456xwd (赞：0)

我们称被影响导致造反为被感染。

设 $t_i\le T$ 的点为关键点，其余的为普通点。

我们考虑预处理出来一个数组 $L_i$，表示对于普通点 $i$，他会被哪一个关键点感染（取其中最大的那个），这一步可以用单调栈预处理。

然后我们考虑以下，若在 $L_i$ 后面搞一个床垫，那么 $\forall j>i,L_j\le L_i$，他都不会被感染了。

那么我们如何选择在哪些 $L_i$ 后面搞床垫呢？

我们考虑对于每个点 $i$，将其向着最小的满足上面的 $j$ 连接一条边，使 $i$ 为 $j$ 这样子我们就建立出来一个森林，然后取每个点就可以使得其和其祖先不可能被感染，这个 $j$ 也可也用单调栈求。 

由于我们想要最大化不被感染的，重链剖分一下，求最长的 $D$ 条链即可。

但这样子会不会出现一个 $k$，使得 $k>j$ 且 $L_j<L_k<L_i$ 呢，这样子就会导致漏算。

可以证明是没有这样的 $k$ 的，若有，则意味着 $t_{L_k}+k-L_k<t_{L_j}+k-L_j，t_{L_j}+j-L_j<t_{L_k}+j-L_j$，不等式的各项都 $>0$，则有 $t_{L_k}+k-L_k+t_{L_j}+j-L_j<t_{L_j}+k-L_j+t_{L_k}+j-L_j\to 0<0$，显然不可能。

那么我们上面的做法就算正确的。

```c++
#include<bits/stdc++.h>
#define ull unsigned long long
#define int long long
#define p_b push_back
#define m_p make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define ls k<<1
#define rs k<<1|1
#define mid ((l+r)>>1)
#define gcd __gcd
#define lowbit(x) (x&(-x))
using namespace std;
int rd(){
    int x=0,f=1; char ch=getchar();
    for(;ch<'0'||ch>'9';ch=getchar())if (ch=='-') f=-1;
    for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    return x*f;
}
void write(int x){
    if(x>9) write(x/10);
    putchar('0'+x%10);
}
const int N=2e6+5,INF=0x3f3f3f3f3f3f3f3f;

int t[N],T,D,n;
vector<int> G[N],vec;

int son[N],mx[N],deep[N];
bool vis[N],b[N];
void dfs(int u,int fa){
    mx[u]=deep[u]=deep[fa]+1;
    for(auto v : G[u]){
        if(v==fa) continue;
        dfs(v,u);
        mx[u]=max(mx[u],mx[v]);
        if(mx[v]>mx[son[u]]) son[u]=v;
    }
}
void DFS(int u,int len){
    vis[u]=1;
    if(!son[u]){
        vec.p_b(len);
        return;
    }
    DFS(son[u],len+1);
    for(auto v : G[u]){
        if(!vis[v]) DFS(v,1);
    }
}
stack<int> q;
int a[N],L[N];
signed main(){
    n=rd(),D=rd(),T=rd();
    for(int i=1;i<=n;i++) a[i]=rd();
    for(int i=1;i<=n;i++){
        if(a[i]<=T){
            while(!q.empty()&&a[q.top()]+i-q.top()>=a[i]) q.pop();
            q.push(i);
        }
        else{
            while(!q.empty()&&a[q.top()]+i-q.top()>T) q.pop();
            if(!q.empty()) L[i]=q.top();
        }
    }
    while(!q.empty())q.pop();
    for(int i=n;i>=1;i--){
        if(!L[i]) continue;
        while(!q.empty()&&L[q.top()]>L[i]) q.pop();
        if(!q.empty()) G[q.top()].p_b(i),b[i]=1;
        q.push(i);
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(a[i]<=T) continue;
        if(!L[i])ans++;
        else if(!b[i]){
            dfs(i,0);
            DFS(i,1);
        }
    }
    sort(vec.begin(),vec.end());reverse(vec.begin(),vec.end());
    for(int i=0;i<min(D,(int)vec.size());i++) ans+=vec[i];
    printf("%lld\n",n-ans);
    return 0;
}
```

---

