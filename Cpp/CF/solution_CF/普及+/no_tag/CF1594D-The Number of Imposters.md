# The Number of Imposters

## 题目描述

Theofanis started playing the new online game called "Among them". However, he always plays with Cypriot players, and they all have the same name: "Andreas" (the most common name in Cyprus).

In each game, Theofanis plays with $ n $ other players. Since they all have the same name, they are numbered from $ 1 $ to $ n $ .

The players write $ m $ comments in the chat. A comment has the structure of " $ i $ $ j $ $ c $ " where $ i $ and $ j $ are two distinct integers and $ c $ is a string ( $ 1 \le i, j \le n $ ; $ i \neq j $ ; $ c $ is either imposter or crewmate). The comment means that player $ i $ said that player $ j $ has the role $ c $ .

An imposter always lies, and a crewmate always tells the truth.

Help Theofanis find the maximum possible number of imposters among all the other Cypriot players, or determine that the comments contradict each other (see the notes for further explanation).

Note that each player has exactly one role: either imposter or crewmate.

## 说明/提示

In the first test case, imposters can be Andreas $ 2 $ and $ 3 $ .

In the second test case, imposters can be Andreas $ 1 $ , $ 2 $ , $ 3 $ and $ 5 $ .

In the third test case, comments contradict each other. This is because player $ 1 $ says that player $ 2 $ is an imposter, and player $ 2 $ says that player $ 1 $ is a crewmate. If player $ 1 $ is a crewmate, then he must be telling the truth, so player $ 2 $ must be an imposter. But if player $ 2 $ is an imposter then he must be lying, so player $ 1 $ can't be a crewmate. Contradiction.

## 样例 #1

### 输入

```
5
3 2
1 2 imposter
2 3 crewmate
5 4
1 3 crewmate
2 5 crewmate
2 4 imposter
3 4 imposter
2 2
1 2 imposter
2 1 crewmate
3 5
1 2 imposter
1 2 imposter
3 2 crewmate
3 2 crewmate
1 3 imposter
5 0```

### 输出

```
2
4
-1
2
5```

# 题解

## 作者：PragmaGCC (赞：18)

首先每个人要么是老实人要么是骗子。

我们考虑每一条信息可以告诉我们什么：

- 假设 $A$ 说 $B$ 是老实人，那么：
  - 如果 $A$ 是老实人，则 $B$ 也是老实人。
  - 如果 $A$ 是骗子，由于 $B$ 不是老实人，所以 $B$ 必然为骗子。
- 如果 $A$ 说 $B$ 是骗子：
  - $A$ 说实话，$B$ 是骗子。
  - $A$ 说谎，$B$ 是老实人。

同样的，如果 $A$ 说 $B$ 是老实人，而 $B$ 确实是老实人，则 $A$ 说的是实话，也是老实人。

其余同理。

可以发现，如果一个人 $A$ 的身份被确定了，其余所有和他有关系的人的身份就都确定了。

我们可以用并查集维护这个东西。令 $i \in [1,n]$ 表示 $i$ 是老实人，$i \in [n + 1, 2n]$ 表示 $i$ 是骗子。

做统计的时候考虑每个集合的代表是老实人/骗子的情况下，哪种老实人数量更多，累加起来就是答案。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 2e5 + 5;
char s[N];
int T, n, m;
int fa[N << 1], siz[N << 1];
int find(int x) { 
    if (x == fa[x]) return x;
    fa[x] = find(fa[x]);
    siz[fa[x]] += siz[x];
    siz[x] = 0;
    return fa[x];
}
void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx == fy) return ;
    siz[fx] += siz[fy]; siz[fy] = 0;
    fa[fy] = fx;
}
int main(void) {
    for (scanf("%d", &T); T; T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n << 1; i++) fa[i] = i, siz[i] = i <= n;
        for (int i = 1, x, y; i <= m; i++) {
            scanf("%d%d%s", &x, &y, s);
            if (s[0] == 'c') merge(x, y), merge(x + n, y + n);
            else merge(x, y + n), merge(y, x + n);
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (find(i) == find(i + n)) {ans = -1; break;} // 一个人既诚实又说谎，出现矛盾
            ans += max(siz[find(i)], siz[find(i + n)]);
            siz[find(i)] = siz[find(i + n)] = 0; // 统计过的地方记得清空
        }
        printf("%d\n", ans);
    }
}
```



---

## 作者：智子 (赞：6)

## 题意

有 $n$ 个玩家和 $m$ 句话，每个玩家可能是船员或内鬼，每句话的形式为“玩家 $i$ 说玩家 $j$ 是船员/内鬼”，求最多可能有多少个内鬼。（如果自相矛盾，输出 $-1$。）

PS：题目背景出自国外的著名游戏  _Among Us_ ，中文名为《我们之中》，也被叫做《内鬼杀》或《太空狼人杀》。游戏背景设置于太空，玩家将扮演船员（英语：Crewmate）或内鬼（英语：Impostor）之一。船员的目标是找出伪装者并完成任务，而伪装者的目标是杀死所有船员而不被发现。

## 思路

这种题目很容易让人联想到并查集。就像 [NOI2001 食物链](https://www.luogu.com.cn/problem/P2024) 一样，这道题可以用“扩展域”并查集来解决。

用 $x$ 表示玩家 $x$ 是船员，$x + n$ 表示船员 $x$ 是内鬼。

对于一句话，如果是“玩家 $x$ 说玩家 $y$ 是船员”，就意味着：

- 如果这句话为真，那么玩家 $x$ 和玩家 $y$ 都是船员。

- 如果这句话为假，那么玩家 $x$ 和玩家 $y$ 都是内鬼。

同理，如果是“玩家 $x$ 说玩家 $y$ 是内鬼”，就意味着：

- 如果这句话为真，那么玩家 $x$ 是船员，玩家 $y$ 是内鬼。

- 如果这句话为假，那么玩家 $x$ 是内鬼，玩家 $y$ 是船员。

按照这个规则合并并查集，然后检查如果存在 $find(x) = find(x + n)$，说明无解，输出 `-1`。

否则，对于每一个点 $i$，考虑分别包含 $i$ 和 $i + n$ 的两个集合，哪个集合包含的内鬼多就选取哪个集合，并累加答案。

## 代码

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

const int MAXN = 200000 + 5;

int f[MAXN * 2], vis[MAXN * 2], cnt[MAXN * 2];
int n, m, p;

int find(int k) {
    return k == f[k] ? k : f[k] = find(f[k]);
}

int main() {
    int T;

    cin >> T;
    while(T--) {
        char s[20];

        memset(vis, 0, sizeof(vis));
        memset(cnt, 0, sizeof(cnt));
        memset(f, 0, sizeof(f));
        cin >> n >> m;
        for(int i = 1; i <= n * 2; i++) {
            f[i] = i;
        }
        for(int i = 1; i <= m; i++) {
            int x, y;

            cin >> x >> y >> s;
            if(s[0] == 'c') {
                f[find(x)] = f[find(y)];
                f[find(x + n)] = find(y + n);
            } else {
                f[find(x)] = find(y + n);
                f[find(x + n)] = find(y);
            }
        }
        bool flag = true;
        for(int i = 1; i <= n; i++) {
            if(find(i) == find(i + n)) {
                flag = false; // 无解
            }
        }
        if(!flag) {
            cout << -1 << endl;
            continue;
        }
        p = 0;
        for(int i = 1; i <= n * 2; i++) {
            if(i > n) {
                cnt[find(i)]++; //统计每个集合的内鬼总数
            }
        }
        int ans = 0;
        for(int i = 1; i <= n; i++) {
            if(vis[find(i)] || vis[find(i + n)]) {
                continue; //如果这个点已经访问过，就不再访问
            }
            ans += max(cnt[find(i)], cnt[find(i + n)]); //选取内鬼较多的集合，加上其内鬼总数
            vis[find(i)] = true;
            vis[find(i + n)] = true; //标记访问
        }
        cout << ans << endl;
    }

    return 0;
}
```

---

## 作者：leexzq (赞：2)

# 题意 #
在游戏 Among them 中，有 $n$ 个人，其中每个人可能是好人或杀手。  

好人永远说真话，杀手永远说假话。  

给出 $m$ 条对话，即 $i$ 说 $j$ 是好人/杀手。  

根据这些对话，判断这 $n$ 个人中最多有多少杀手，若对话自相矛盾则输出 $-1$。
# solution # 
我们想想每条对话代表什么：  

- 如果一个人说另一个人是杀手，则他们属于不同阵营（互踩）。  

- 如果一个人说另一个人是好人，则他们属于相同阵营（发金水）。  

而很明显这些关系是可以传递的，而每个人之间的关系又有多种，所以我们可以想到扩展域并查集。  

用两个点表示第 $i$ 个人，其中第 $i$ 号点表示与他身份相同的人的集合（正集），第 $i+n$ 号点表示与他身份不同的人的集合（反集）。  

对每一条对话，若说别人为好人，合并他们的正反集与对方的合并，否则把他们的正集与对方的反集合并，最后判断对立的两个集合大小，取较大值求和即可。  

代码： 
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define ld long double
using namespace std;
const int N=2e5+10,M=5e5+10;
int fa[N*2],siz[N*2],n,m,a[M],x[M],y[M],b[M];
int get(int x){return x==fa[x]?x:fa[x]=get(fa[x]);}
void merge(int x,int y)
{
	if(x==y)return;
	fa[x]=y,siz[y]+=siz[x];
}
//扩展域并查集 
int solve(int ans=0)
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)fa[i]=i,siz[i]=1,b[i]=0;
	for(int i=n+1;i<=2*n;i++)fa[i]=i,siz[i]=0,b[i]=0;
	for(int i=1;i<=m;i++)
	{
		string s;
		cin>>x[i]>>y[i]>>s;
		if(s[0]=='i')a[i]=1;
		else a[i]=0;
	}
	for(int i=1;i<=m;i++)
	{
		int x1=get(x[i]),y1=get(y[i]),x2=get(x[i]+n),y2=get(y[i]+n);
		if(a[i]==1)
		{
			if(x1==y1||x2==y2)return -1;
			merge(y2,x1),merge(x2,y1);
		}
		else
		{
			if(x1==y2||x2==y1)return -1;
			merge(x1,y1),merge(x2,y2);
		}
	}
	for(int i=1;i<=n;i++)
	{
		int x1=get(i),x2=get(i+n);
		if(!b[x1]&&!b[x2])ans+=max(siz[x1],siz[x2]),b[x1]=b[x2]=1;
	}
	return ans;
}
int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	while(t--)cout<<solve()<<endl;
}

```


---

## 作者：reailikezhu (赞：1)

这题逐渐难起来了。

然后考虑一个性质。

就是如果 $i$ 说 $j$ 是 imposter，那么 $i,j$ 一定是一个 imposter，一个 crewmate。如果 $i$ 说 $j$ 是 crewmate，那么 $i,j$ 一定是同一个东西。考虑这东西和异或可以产生联系。

考虑建一个无向图。对于每组 $i,j$，如果 $i$ 说 $j$ 是 imposter，那么边权为 $1$ 否则边权为 $0$。

跑联通块。设这个块中的一个点为 imposter，然后的话跑联通块。然后每个点的权值是他的之前的点异或这个边权。然后矛盾情况是两次经过同一个点时，这个点的权值出现不同。

统计答案是对于每个联通块直接 dfs 遍历，然后遍历到的这个点的权值异或边权即可获得下一位的权值。

放个代码：
```cpp
#include<stdio.h>
#include<string>
#include<iostream>

using std::string;
using std::cin;

int t;
int n,m;
int head[200010],tot,w[1000010],nxt[1000010],ver[1000010];
int a[200010];
bool vis[200010];
int ansx,ansy;
int ans;
bool no;

void add(int x,int y,int z){
	nxt[++tot]=head[x];
	ver[tot]=y;
	w[tot]=z;
	head[x]=tot;
}

int max(int a,int b){ return a>b?a:b; }

void dfs(int x){
	if(a[x]==0) ansx++;
	else ansy++;
	vis[x]=1;
	for(int i=head[x];~i;i=nxt[i]){
		int y=ver[i],z=w[i];
		if(vis[y]==1){
			if((a[x]^z)!=a[y]){
				no=1;
				return;
			}
		}
		else a[y]=a[x]^z,dfs(ver[i]);
	}
	return;
}

int main(){
	scanf("%d",&t);
	while(t--){
		ans=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++) head[i]=-1;
		for(int i=1;i<=n;i++) vis[i]=0;
		tot=0;
		for(int i=1;i<=m;i++){
			int x,y;
			string s;
			scanf("%d%d",&x,&y);
			cin>>s;
			if(s=="imposter"){
				add(x,y,1);
				add(y,x,1);
			}
			else{
				add(x,y,0);
				add(y,x,0);
			}
		}
		bool flag=0;
		for(int i=1;i<=n;i++){
			if(!vis[i]){
				a[i]=1;
				ansx=ansy=no=0;
				vis[i]=1;
				dfs(i);
				if(no==1){
					printf("-1\n");
					flag=1;
					break;
				}
				else ans+=max(ansx,ansy);
			}
		}
		if(!flag) printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Acc_Robin (赞：1)

考虑如何连边：

- 若 $x$ 查证 $y$ 是 `imposter`，说明 $x$ 和 $y$ 身份**一定不相同**，连无向有权边 $(x,y,1)$

- 若 $x$ 查证 $y$ 是 `crewmate`，说明 $x$ 和 $y$ 身份**一定相同**，连无向有权边 $(x,y,0)$

若这个图存在边权异或和为 $1$ 的奇环，则无解。

否则，此图保留边权为 $1$ 的边后一定是二分图，答案就是取每个联通块最大的一部分并相加即可。

使用带权并查集维护上述操作，复杂度即为 $O(m\alpha(n))$。

[代码](https://codeforces.com/contest/1594/submission/131252622)

---

## 作者：GaryH (赞：0)

# CF1594D 题解

一道朴素的dfs题。

注意到虽然题中给的是单向边，但实际上我们可以沿着一条单向边反着计算。

例如，若有一条单向边 $(u,v,w)$ ，我们如果知道了 $v$ 的身份，我们可以根据这个身份与边权 $w$ 是否相同，来推断出 $u$ 的身份是真还是假，故可以将单向边转化成双向。

那么，将上述单向边换成双向边后，在一个连通块中，我们确定了一个人的身份，就可以确定连通块中所有人的身份，从而计算出这个连通块中可以包含的假人最多有多少。而不同的连通块间不会产生相互影响，所以将每一个连通块的最多假人数加在一起，就是最终答案。

那我们只需要用并查集维护连通块，再对每一个联通块，分别dfs染色即可。

因为每个点最多被搜索一次，所以dfs的复杂度是 $O(N+M)$ 的，而并查集的复杂度是 $O(N \alpha(N))$ 的，故若 $N,M$ 同级，则总复杂度是 $O(N \alpha(N))$，足以通过本题。

给出单组数据的代码：

```
const int N(2e6+10);
struct Edge {int to, dis, nxt, op;};

int ok;
int cnt;
int siz;
int n, m;
int fa[N];
Edge e[N];
int vis[N];
int head[N];

inline void add(int u, int v, int w, int op) {
	e[++cnt] = (Edge) {v, w, head[u], op}, head[u] = cnt;
}

inline int dfs(int u, int col) {
	if (ok == 1) return 0;
	int res = 0;
	if (vis[u] != -1) {
		if (vis[u] ^ col) ok = 1;
		return 0;
	}
	vis[u] = col, siz++;
	if (col == 1) res++;
	edg (i, v, u) {
		int ncol = col ? 1 - e[i].dis : e[i].dis;
		if (e[i].op) ncol = (col ^ e[i].dis) ? 1 : 0;
		res += dfs(v, ncol);
	}
	return res;
}

char tmp[55];

inline int f_set(int x) {
	if(x == fa[x]) return x;
	return fa[x] = f_set(fa[x]);
}

inline void work() {
	n = read(), m=read(), ok = cnt = 0;
	rep (i, 1, n)
	head[i] = 0, vis[i] = -1, fa[i] = i;
	rep (i, 1, m)
	e[i].to = e[i].dis = e[i].nxt = e[i].op = 0;
	rep (i, 1, m) {
		int u = read(), v = read(), w;
		scanf("%s", tmp);
		if (tmp[0] == 'i') w = 1;
		else w = 0;
		add(u, v, w, 0), add(v, u, w, 1);
		if(f_set(u) ^ f_set(v)) fa[f_set(u)] = f_set(v);
	}
	int ans = 0;
	rep (i, 1, n) {
		if (fa[i] == i) {
			siz = 0;
			int ret = dfs(i, 0);
			if (ok) {
				puts("-1");
				return ;
			}
			ckmax(ret, siz - ret);
			ans += ret;
		}
	}
	cout << ans << endl;
}

```



---

## 作者：WitheredZeal (赞：0)


## 题意  

有 $n$ 个人，每个人可能是诚实的人或者说谎的人。  
诚实的人永远说真话，说谎的人永远说假话。  
有 $m$ 个条件，分别表示 $i$ 说 $j$ 是诚实的人/说谎的人。  
你需要判断在这些限制条件下，最多有可能有几个诚实的人，或输出 `-1` 声明不可能存在这种情况。  

## 题解  

我们设诚实的人是 $1$，说谎的人是 $0$。  
那么：  
- $1$ 会说 $1$ 是 $1$。
- $1$ 会说 $0$ 是 $0$。
- $0$ 会说 $1$ 是 $0$。
- $0$ 会说 $0$ 是 $1$。  
我们发现这就是一个同或。  
也就是说，一个限制相当于是钦定了两个点的异或值。  
我们用并查集来维护，顺便维护出与根的异或值是 $0$ 还是 $1$。  
那么就做完了。  



## 代码

我的代码可能比较阴间，`fa[i]/2` 表示父亲节点，`fa[i]%2` 表示与父亲的值的异或值。 

```cpp
int n,m,k,ans,cnt;
int fa[N];
int a[N][2];
char s[N];
bool flag=0;
void getfa(int X){if (X*2==fa[X]) return;getfa(fa[X]/2);int u=fa[fa[X]/2],v=fa[X]&1;fa[X]=u^v;return;}
bool merge(int X,int Y,int t)
{
    if (X==Y) return !t;
    getfa(X);getfa(Y);
    if (fa[X]/2!=fa[Y]/2) {fa[fa[X]/2]=fa[Y]^t^(fa[X]&1);return 1;}
    return ((fa[X]&1)^(fa[Y]&1))==t;
}
void DOIT()
{
	rd(n);rd(m);flag=1;
	for (int i=1;i<=n;i++) fa[i]=i*2;
	while (m--)
	{
		int x,y,z,u,v;rd(x);rd(y);scanf("%s",s);
		if (s[0]=='i') z=1;else z=0;
		flag&=merge(x,y,z);
	}
	if (!flag) {puts("-1");return;}
	for (int i=1;i<=n;i++) getfa(i);
	for (int i=1;i<=n;i++) a[i][1]=a[i][0]=0;
	for (int i=1;i<=n;i++) a[fa[i]/2][fa[i]%2]++;
	ans=0;for (int i=1;i<=n;i++) ans+=max(a[i][0],a[i][1]);
	cout<<ans<<endl;
}
```

---

## 作者：vectorwyx (赞：0)

$i$ 说 $j$ 为假，若 $j$ 为假则 $i$ 为真，$j$ 为真则 $i$ 为假；$i$ 说 $j$ 为真，若 $j$ 为真则 $i$ 为真，$j$ 为假则 $i$ 为假。

用异或来描述，给每个点赋一个 $01$ 权值，$0$ 代表它为假，$1$ 代表它为真。然后用边权描述其两端点点权的异或和，如果 $i$ 说 $j$ 为假则在 $i,j$ 之间连一条边权为 $1$ 的无向边，$i$ 说 $j$ 为真则连一条边权为 $0$ 的无向边。对于每个连通块，只要有一个点的真/假确定了那么其余点也就随着确定了。对每个连通块进行 dfs 二染色即可，注意判无解。

代码如下：
```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define int ll 
#define ll long long
#define db double
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){if(ch=='-') fh=-1; ch=getchar();} while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0'; ch=getchar();} return x*fh;}
inline void out(int *a,int l,int r){fo(i,l,r) printf("%lld ",*(a+i));puts("");}

const int N=1e6+5;
struct Edge{
	int to,next,val;
}e[N<<1];
int head[N],tot,col[N],top,rp;

void connect(int x,int y,int val){
	e[++tot]=(Edge){y,head[x],val};
	head[x]=tot;
}

bool dfs(int x){
	++top;if(col[x]) rp++;
	for(int i=head[x];i;i=e[i].next){
		int p=e[i].to;
		if(col[p]<0){
			col[p]=col[x]^e[i].val;
			if(!dfs(p)) return 0;
		}else if((col[p]^col[x])!=e[i].val) return 0;
	}
	return 1;
}

void solve(){
	int n=read(),m=read(),ans=0;
	fo(i,1,n) head[i]=0,col[i]=-1;tot=0;
	fo(i,1,m){
		int x=read(),y=read();
		string s;cin>>s;
		if(s[0]=='i') connect(x,y,1),connect(y,x,1);
		else connect(x,y,0),connect(y,x,0);
	}
	fo(i,1,n) if(col[i]==-1){
		top=rp=0;col[i]=0;
		if(!dfs(i)){
			puts("-1");
			return;
		}
		ans+=max(rp,top-rp);
	}
	cout<<ans<<endl;
}

signed main(){
	int T=read();
	while(T--) solve();
	return 0;
}
/*
-------------------------------------------------
*/

```


---

