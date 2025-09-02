# Santa Clauses and a Soccer Championship

## 题目描述

The country Treeland consists of $ n $ cities connected with $ n-1 $ bidirectional roads in such a way that it's possible to reach every city starting from any other city using these roads. There will be a soccer championship next year, and all participants are Santa Clauses. There are exactly $ 2k $ teams from $ 2k $ different cities.

During the first stage all teams are divided into $ k $ pairs. Teams of each pair play two games against each other: one in the hometown of the first team, and the other in the hometown of the other team. Thus, each of the $ 2k $ cities holds exactly one soccer game. However, it's not decided yet how to divide teams into pairs.

It's also necessary to choose several cities to settle players in. Organizers tend to use as few cities as possible to settle the teams.

Nobody wants to travel too much during the championship, so if a team plays in cities $ u $ and $ v $ , it wants to live in one of the cities on the shortest path between $ u $ and $ v $ (maybe, in $ u $ or in $ v $ ). There is another constraint also: the teams from one pair must live in the same city.

Summarizing, the organizers want to divide $ 2k $ teams into pairs and settle them in the minimum possible number of cities $ m $ in such a way that teams from each pair live in the same city which lies between their hometowns.

## 说明/提示

In the first test the orginizers can settle all the teams in the city number $ 2 $ . The way to divide all teams into pairs is not important, since all requirements are satisfied anyway, because the city $ 2 $ lies on the shortest path between every two cities from $ {2,4,5,6} $ .

## 样例 #1

### 输入

```
6 2
1 2
1 3
2 4
2 5
3 6
2 5 4 6
```

### 输出

```
1
2
5 4 2
6 2 2
```

# 题解

## 作者：I_AK_IOI_and_NOI (赞：1)

~~**这题竟然还没有题解啊，赶紧水一发……**~~

## 解法讲解

![](https://www.freesion.com/images/327/0be8298e4cf99a2fef8f3c25866b226f.png)

如上图,只要找到这样一个节点就可以了。

它的父亲和儿子们所在的子树在图中标为 ①②③...。

只要它们的大小 $size \times2 \le k$，

则这个节点就是符合要求的了，你可以从这个节点开始 dfs 一次。

然后把某个队的家乡加入到一个 vector 里面(按 dfs 序)，最后 for 一遍。

这样子的话，将 $v[i]$ 和 $v[i+k/2]$ 配对就可以了，因为每个子树的大小都小于等于 $k \div 2$。


则可知 $v[i+k/2]$ 必然是这个节点的另外一个儿子的子树里面的节点。

则 $v[i]$ 和 $v[i+k/2]$ 必然不是在同一个子树里面，则它们俩连接的时候要经过中间这个节点 $u$。

这样的讨论对所有的 $i$ 都成立 ($ 1\le i \le 2\times k $)，则每个配对都会经过这节点 $u$。

## 代码时间

```
#include <bits/stdc++.h>
using namespace std;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define LL long long
#define rep1(i,a,b) for (int i = a;i <= b;i++)
#define rep2(i,a,b) for (int i = a;i >= b;i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define rei(x) scanf("%d",&x)
#define rel(x) scanf("%I64d",&x)
 
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
 
const int MAXN = 2e5+100;
const int dx[9] = {0,1,-1,0,0,-1,-1,1,1};
const int dy[9] = {0,0,0,-1,1,-1,1,-1,1};
const double pi = acos(-1.0);
 
int n,k,macnt[MAXN],cnt[MAXN];
bool team[MAXN];
vector <int> G[MAXN],ans;
 
void dfs1(int x,int fa)
{
    if (team[x])
        cnt[x]++;
    for (int y:G[x])
    {
        if (y==fa)
            continue;
        dfs1(y,x);
        cnt[x] += cnt[y];
        macnt[x] = max(macnt[x],cnt[y]);
    }
}
 
void dfs2(int x,int fa)
{
    if (team[x])
        ans.pb(x);
    for (auto y:G[x])
    {
        if (y==fa) continue;
        dfs2(y,x);
    }
}
 
int main()
{
    rei(n);rei(k);
    k<<=1;
    rep1(i,1,n-1)
    {
        int x,y;
        rei(x);rei(y);
        G[x].pb(y);G[y].pb(x);
    }
    rep1(i,1,k)
    {
        int x;
        rei(x);
        team[x] = true;
    }
    dfs1(1,-1);
    int u = -1;
    rep1(i,1,n)
        if ( (k-cnt[i])*2 <= k && macnt[i]*2 <= k)
        {
            u = i;
            break;
        }
    puts("1");
    cout << u << endl;
    if (team[u])
        ans.pb(u);
    for (int s : G[u])
        dfs2(s,u);
    rep1(i,0,k/2 -1 )
        printf("%d %d %d\n",ans[i],ans[i+k/2],u);
    return 0;
}
```

~~求过QWQ~~

---

## 作者：_edge_ (赞：0)

简单的 $2300$。

首先通过各种各样神奇手玩，大概可以知道他的 $m$ 必定是 $1$。

相当于是弱化版的树的重心，就是，对于每一颗子节点内的标记节点不能超过 $k$ 个。

可以尝试自行手玩，反正根据各种各样调整应该可以的。

然后知道这个结论就比较好做题了，我们需要寻找一个节点 $sz_x$ 不超过 $k$，那么类似于树的重心，我们把子节点取 $\max$，对于祖先的我们用 $2 \times k - sz_x$，值得注意的是，当前这个是否是标记节点是没有任何关系的。

接着，我们把每颗子树的标记节点都拎出来，最大和次大进行匹配即可。

我明白证明的不够严谨，但是 OI 的话也只需要猜出该结论就可以了。

```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int INF=2e5+5;
struct _node_edge{
	int to_,next_;
}edge[INF<<1];
int n,k,head[INF],sz[INF],num[INF],tot,fl,vis1[INF],res1,vis[INF];
void add_edge(int x,int y) {
	edge[++tot]=(_node_edge){y,head[x]};
	head[x]=tot;return ;
}
vector <int> cnt[INF];
struct _node_queue {
	int pos,dis_v;
	bool operator < (const _node_queue &x) const {
		return x.dis_v>dis_v;
	}
};
priority_queue <_node_queue> q;
void print(int x,int fa,int f) {
//	cout<<x<<" "<<fa<<" "<<f<<" qweij\n";
	if (vis[x]) {
//		cout<<x<<" qwiejo\n";
		num[f]++;
		cnt[f].pb(x);
	}
	for (int i=head[x];i;i=edge[i].next_) {
		int v=edge[i].to_;
		if (v==fa) continue;
		print(v,x,f);
	}
}
void DFS(int x,int fa) {
	if (fl) return ;
	sz[x]=vis[x];
	int Max=0;
	for (int i=head[x];i;i=edge[i].next_) {
		int v=edge[i].to_;
		if (v==fa) continue;
		DFS(v,x);
		if (fl) return ;
		sz[x]+=sz[v];
		Max=max(Max,sz[v]);
	}
	Max=max(Max,2*k-sz[x]);
	if (Max<=k) {
		cout<<"1\n";
		cout<<x<<"\n";
		for (int i=head[x];i;i=edge[i].next_) {
			int v=edge[i].to_;
			print(v,x,v);
			if (num[v]) q.push({v,num[v]});
		}
		if (vis[x]) num[x]++,cnt[x].pb(x),q.push({x,num[x]});
		int res=x;
		while (q.size()) {
			auto x=q.top();q.pop();
			auto y=q.top();q.pop();
			cout<<cnt[x.pos][num[x.pos]-1]<<" "<<cnt[y.pos][num[y.pos]-1]<<" "<<res<<"\n";
			num[x.pos]--;num[y.pos]--;
			x.dis_v--;y.dis_v--;
			if (x.dis_v==0) ;
			else q.push(x);
			
			if (y.dis_v==0) ;
			else q.push(y);
		}
		exit(0);
	}
	return ;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for (int i=1;i<n;i++) {
		int a=0,b=0;cin>>a>>b;
		add_edge(a,b);add_edge(b,a);
	}
	for (int i=1;i<=k*2;i++) {
		int x=0;cin>>x;
		vis[x]=1;
	}
	DFS(1,0);
	return 0;
}
```


---

