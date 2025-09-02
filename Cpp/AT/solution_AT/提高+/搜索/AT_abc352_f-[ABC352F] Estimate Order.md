# [ABC352F] Estimate Order

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc352/tasks/abc352_f

$ N $ 人の人がおり、人にはそれぞれ $ 1,\ 2,\ \ldots,\ N $ の番号が付けられています。

$ N $ 人が競争を行い、順位が付きました。この順位に対して以下の情報が与えられています。

- それぞれの人に対して付けられた順位は相異なる
- 各 $ 1\ \leq\ i\ \leq\ M $ について人 $ A_i $ の順位を $ x $、人 $ B_i $ の順位を $ y $ とすると、$ x\ -\ y\ =\ C_i $ である
 
ただし、この問題では与えられた情報に矛盾しないような順位付けが $ 1 $ つ以上存在するような入力のみが与えられます。

$ N $ 個のクエリの答えを求めてください。$ i $ 番目のクエリの答えは以下により定まる整数です。

- 人 $ i $ の順位が一意に定まるならば、その値を答えとする。そうでない場合、答えは $ -1 $ である。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 16 $
- $ 0\ \leq\ M\ \leq\ \frac{N(N\ -\ 1)}{2} $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ N $
- $ 1\ \leq\ C_i\ \leq\ N\ -\ 1 $
- $ (A_i,\ B_i)\ \neq\ (A_j,\ B_j)\ (i\ \neq\ j) $
- 与えられた情報に矛盾しない順位付けが $ 1 $ つ以上存在する
- 入力される値はすべて整数
 
### Sample Explanation 1

人 $ i $ の順位を $ X_i $ とおくと、$ (X_1,\ X_2,\ X_3,\ X_4,\ X_5) $ は $ (3,\ 4,\ 1,\ 2,\ 5),\ (3,\ 5,\ 2,\ 1,\ 4) $ のいずれかです。 したがって、$ 1 $ 番目のクエリに対する答えは $ 3 $、$ 2,\ 3,\ 4,\ 5 $ 番目のクエリに対する答えは $ -1 $ となります。

## 样例 #1

### 输入

```
5 2
2 3 3
5 4 3```

### 输出

```
3 -1 -1 -1 -1```

## 样例 #2

### 输入

```
3 0```

### 输出

```
-1 -1 -1```

## 样例 #3

### 输入

```
8 5
6 7 3
8 1 7
4 5 1
7 2 1
6 2 4```

### 输出

```
1 -1 -1 -1 -1 -1 -1 8```

# 题解

## 作者：Pursuewind (赞：8)

$n$ 很小，考虑暴搜。

我们肯定不能枚举所有的全排列的，因为这样是 $O(n!)$，我们考虑从 $m$ 入手。

于是可以对于每一条限制进行暴搜，假如限制 $(a_i,b_i,c_i)$ 表示 $p_{a_i}-p_{b_i}=c_i$，我们考虑往 $p_{b_x}$ 填入 $1 \sim n-c_i$，用一个 `set` 维护还能填的数字，判断是否能填入即可。

这样复杂度就是对的，因为每一次暴搜，都会让可填的数的数量减少 $2$，所以复杂度最坏也就是 $O(n(n-2)(n-4)\dots)$，然而很多情况都会被剪掉，所以复杂度远远达不到。

注意特判 $p_{a_i}$ 和 $p_{b_i}$ 已经有数的情况，此时另一个数是确定的。

搜完所有限制之后，怎么判断序列合法呢？

用 $ans$ 记录答案，初始时全为 $-114514$。

如果搜完后剩两个及以上的数，则剩下的位置为 `-1`。否则，将 $ans_i$ 与 $p_i$ 对比即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1005;
int n, m;
int a[N], b[N], c[N], p[N];
int ans[N];
bool is[N];
set <int> have;
void dfs(int x){ //表示当前已经搜到了第 x 条限制 
	if (x == m + 1){
		for (int i = 1; i <= n; i ++){
			if (ans[i] == -1) continue;
			if (ans[i] != p[i]){
				if (!is[i]){
					if (have.size() == 1){
						if (ans[i] == -114514 || ans[i] == *have.begin()) ans[i] = *have.begin();
						else ans[i] = -1;
					}
					else{
						ans[i] = -1;
					}
				}
				else{
					if (ans[i] == -114514) ans[i] = p[i];
					else ans[i] = -1;
				}
			}
		}
	}
	int u = a[x], v = b[x];
	if (p[u]){
		if (!p[v]){
			p[v] = p[u] - c[x];
			int res = p[v];
			if (res <= 0){
				p[v] = 0;
				return ;
			}
			if (have.find(res) == have.end()){
				p[v] = 0;
				return ;
			} 
			have.erase(res);
			dfs(x + 1);
			have.insert(res);
			p[v] = 0;
		}
		if (p[u] - p[v] == c[x]){
			dfs(x + 1);
		}
		return ;
	}
	if (p[v]){
		if (!p[u]){
			p[u] = p[v] + c[x];
			int res = p[u];
			if (res > n){
				p[u] = 0;
				return ;
			}
			if (have.find(res) == have.end()){
				p[u] = 0;
				return ;
			}
			have.erase(res);
			dfs(x + 1);
			have.insert(res);
			p[u] = 0;
		}
		if (p[u] - p[v] == c[x]){
			dfs(x + 1);
		}
		return ;
	}
	for (int i = 1; i <= n - c[x]; i ++){ //尝试向 bx 位填入 i
		if (have.find(i) == have.end() || have.find(i + c[x]) == have.end()) continue; //无法填入
		have.erase(i); have.erase(i + c[x]);
		p[b[x]] = i, p[a[x]] = i + c[x];
		dfs(x + 1);
		have.insert(i); have.insert(i + c[x]);
		p[a[x]] = p[b[x]] = 0;
	}
}
signed main(){
	cin >> n >> m;
	for (int i = 1; i <= n; i ++){
		have.insert(i);
		ans[i] = -114514;
	}
	for (int i = 1; i <= m; i ++){
		cin >> a[i] >> b[i] >> c[i];
		is[a[i]] = is[b[i]] = 1;
	}
	dfs(1);
	for (int i = 1; i <= n; i ++){
		cout << max(ans[i], -1ll) << " ";
	}
	return 0;
}
```

---

## 作者：_determination_ (赞：7)

强烈谴责出题人把爆搜放在 F 的行为。

每个关系，我们都连一条边。这样每个连通块内都能表示数量关系。

对于每个连通块，考虑枚举其中一个数并表示出剩下的数，如果只有一个合法方案那就能确定，否则整个连通块都是 `-1`。

怎么确定？考虑爆搜。因为你只需要确定有无解即可，所以复杂度远小于阶乘。你加几个剪枝（排除不合法情况，优化枚举顺序）就能过掉。复杂度我也不知道，能过就对了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
// #define endl '\n'
#define debug cout << "114514" << endl
int n,m;
vector<pair<int,int> >e[20];
struct node{
    vector<pair<int,int> >vec;
    int siz,mx;
}blk[20];
int vis[20],tot;
void dfs(int x,int c)
{
    if(vis[x])return;
    vis[x]=1;
    blk[tot].vec.push_back({x,c});
    blk[tot].siz++;
    blk[tot].mx=max(blk[tot].mx,c);
    for ( int i = 0 ; i < e[x].size() ; i++ )
    {
        int v=e[x][i].first,w=e[x][i].second;
        dfs(v,w+c);
    }
}
int cmp(node p,node q)
{
    return p.siz>q.siz;
}
int ans[20],flag[20],used[20],kk;
int check(int x)
{
    if(x==kk)return check(x+1);
    if(x==tot+1)
    {
        // for ( int i = 1 ; i <= n ; i++ )
        // {
        //     cout << flag[i] << " ";
        // }
        // cout << endl;
        return 1;
    }
    for ( int i = 1 ; i <= n-blk[x].mx ; i++ )
    {
        int ff=0;
        for ( int j = 0 ; j < blk[x].siz ; j++ )
        {
            int v=blk[x].vec[j].first,w=blk[x].vec[j].second;
            if(w+i<=0||w+i>n||used[w+i])
            {
                ff=1;
                break;
            }
        }
        if(ff)continue;
        for ( int j = 0 ; j < blk[x].siz ; j++ )
        {
            int v=blk[x].vec[j].first,w=blk[x].vec[j].second;
            used[w+i]=1;
            flag[v]=w+i;
        }
        int ans=check(x+1);
        for ( int j = 0 ; j < blk[x].siz ; j++ )
        {
            int v=blk[x].vec[j].first,w=blk[x].vec[j].second;
            used[w+i]=0;
            flag[v]=0;
        }
        if(ans)return 1;
    }
    return 0;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin >> n >> m;
    while(m--)
    {
        int u,v,w;
        cin >> u >> v >> w;
        e[u].push_back({v,-w});
        e[v].push_back({u,w});
    }
    for ( int i = 1 ; i <= n ; i++ )
    {
        if(!vis[i])
        {
            tot++;
            dfs(i,0);
        }
    }
    sort(blk+1,blk+1+tot,cmp);
    for ( int i = 1 ; i <= tot ; i++ )
    {
        int cnt=0;
        kk=i;
        // for ( int j = 0 ; j < blk[i].siz ; j++ )
        // {
        //     cout << blk[i].vec[j].first << " ";
        // }
        // cout << endl;
        for ( int j = 1 ; j <= n-blk[i].mx ; j++ )
        {
            memset(used,0,sizeof(used));
            int ff=0;
            for ( int k = 0 ; k < blk[i].siz ; k++ )
            {
                flag[blk[i].vec[k].first]=blk[i].vec[k].second+j;
                if(blk[i].vec[k].second+j<=0||blk[i].vec[k].second+j>n)ff=1;
                else used[blk[i].vec[k].second+j]=1;
            }
            if(ff)
            {
                for ( int k = 0 ; k < blk[i].siz ; k++ )
                {
                    flag[blk[i].vec[k].first]=0;
                    if(blk[i].vec[k].second+j<=0||blk[i].vec[k].second+j>n)ff=1;
                    else used[blk[i].vec[k].second+j]=0;
                }
                continue;
            }
            if(check(1))
            {
                // cout << i << " " << j << endl;
                cnt++;
                for ( int k = 0 ; k < blk[i].siz ; k++ )
                {
                    ans[blk[i].vec[k].first]=blk[i].vec[k].second+j;
                }
            }
            for ( int k = 0 ; k < blk[i].siz ; k++ )
            {
                flag[blk[i].vec[k].first]=0;
                used[blk[i].vec[k].second+j]=0;
            }
        }
        if(cnt>=2)
        {
            for ( int k = 0 ; k < blk[i].siz ; k++ )
            {
                ans[blk[i].vec[k].first]=-1;
            }
        }
    }
    for ( int i = 1 ; i <= n ; i++ )
    {
        cout << ans[i] << " ";
    }
    return 0;
}
```

---

## 作者：qqqaaazzz_qwq (赞：6)

**[题目链接](https://atcoder.jp/contests/abc352/tasks/abc352_f)**

把限制当成边，建出带权图，最终的图肯定会形成若干个连通块，我们以连通块为单位来重新考虑这个问题。

如果第 $i$ 个连通块的排名可以被确定下来，就说明 **我无论怎么安排其他连通块的排名，最终为这个连通块准备的排名应该是唯一确定的**。

看到 $n \leq 16$，于是考虑可能是 ~~爆搜~~ 状压DP。

对于每个连通块，我们将它移走，用剩下连通块去拼排名，如果拼出来结果是唯一的，那这个连通块的排名就能确定下来。

剩下的见代码吧。

```cpp
#include <bits/stdc++.h>
#define FAST ios::sync_with_stdio(false);cin.tie(0)
using namespace std;
int n,m;
//f[i][st] 前 i 个连通块里面选择，
//当前选出的排名状态压缩后为 st，是否有可能？
vector<pair<int,int> > v[30];
int vis[30];
vector<int> g[30];
vector<int> k[30];//存这个连通块可能出现的排名情况 
int idx;
const int qwq = 114514;
int skip;
int f[30][65540];

void dfs(int d){
	g[idx].push_back(d);
	for (auto i : v[d]){
		if(vis[i.first]==qwq){
			vis[i.first] = vis[d]-i.second;
			dfs(i.first);
		}
	}
	return;
}
bool cmp(int x,int y){
	return vis[x]<vis[y];
}

void dp(){
	memset(f,false,sizeof(f));
	f[0][0] = true;
	int cnt = 0,res = 0;
	for (int i=0;i<idx-1;i++){
		for (int j=0;j<(1<<n);j++){
			for (auto q : k[i+1]){
				if((j&q)==0){
					f[i+1][(j|q)] |= f[i][j];
				}
			}
		}
	}
	return;
}
int ans[30];
int popcount(int x){
	int res = 0;
	while(x){
		res++;
		x -= (x&-x);
	}
	return res;
}

signed main()
{
	cin >> n >> m;
	for (int i=1;i<=m;i++){
		int x,y,z;
		cin >> x >> y >> z;
		v[x].push_back(make_pair(y,z));
		v[y].push_back(make_pair(x,-z));
	}
	for (int i=1;i<=n;i++){
		vis[i] = qwq;
		ans[i] = -1;
	}
	for (int i=1;i<=n;i++){
		if(vis[i]==qwq){
			vis[i] = 0;
			++idx;
			dfs(i);
		}
	}
	for (int i=1;i<=idx;i++){
		sort(g[i].begin(),g[i].end(),cmp);
		int x = vis[g[i][0]];
		int st = 0;
		for (auto j : g[i]){
			st |= (1<<(vis[j]-x));
		}
		while(st<=(1<<n)-1){
			k[i].push_back(st);
			st <<= 1;
		}
	}
	for (int i=1;i<=idx;i++){
		swap(k[i],k[idx]);
		dp();
		swap(k[i],k[idx]);
		int cnt = 0,res = 0;
		for (auto q : k[i]){
			if(f[idx-1][(1<<n)-1-q]){
				cnt++;
				res = (1<<n)-1-q;
			}
		}
		if(cnt!=1) continue;//排名不唯一
		int ret = 1;
		for (auto j : g[i]){
			while(res&1){
				res >>= 1;
				ret++;
			}
			ans[j] = ret;
			res >>= 1;
			ret++;
		}
	}
	for (int i=1;i<=n;i++) cout << ans[i] << " ";
	return 0;
}
```

---

## 作者：Fire_flame (赞：3)

## $\mathtt{Solution}$

因为数据范围很小，所以考虑 dfs。

考虑没有约束的点的数量 $k$，要进行一个分讨。

如果 $k=1$，这个点可能是唯一确定的（可见样例 $1$）。

否则，这些没有约束的点一定不可能唯一确定。

然后对于每一个约束条件相连的连通块，暴力枚举其中最小的点的取值。

但是这些点的取值可能会导致一个点同时有不同的取值，矛盾，需要判断。

最后记录每一个合法的答案，看看有没有改变即可。

复杂度有点悬，可以采取优化，如果某一个连通块最大的数的值大于 $n$，可以跳过这种情况。

实现起来有点难，赛后 $10$ 分钟才过。

时间复杂度 $O(n\times \dfrac{n!}{[\dfrac{n}{2}]!})$（乱分析），实际要比这个小很多。

参考代码：

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + (ch - '0');ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 205, MR = 205;
struct edge{
	int from, to, len, nxt;
}e[MR];
int n, m, k, pq, res, cnt, head[MAXN], fa[MAXN], a[MAXN], b[MAXN], c[MAXN], d[MAXN], p[MAXN];
int in[MAXN], flag, num[MAXN], ct[MAXN], ans[MAXN], cnt2[MAXN];
int find(int x){//并查集计算连通块
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void add_edge(int u, int v, int w){
	e[++ cnt] = {u, v, w, head[u]};
	head[u] = cnt;
}
void dfs(int x, int last){//计算连通块中的最大值
	if(num[x] >= last)return ;//剪枝
	num[x] = last, res = max(res, num[x]);
	for(int i = head[x];i;i = e[i].nxt){
		int v = e[i].to, w = e[i].len;
		dfs(v, last + w);
	}
}
void dfs3(int x, int last){//从最小的数推出其他的数
//	puts("-1");
	d[x] = last;
	for(int i = head[x];i;i = e[i].nxt){
		int v = e[i].to, w = e[i].len;
		if(d[v]){
			if(d[v] != last + w)flag = 1;//约束条件之间互相矛盾，不合法
			continue;
		}
		dfs3(v, last + w);
	}
}
void calc(){
	memset(d, 0, sizeof(d));
	memset(cnt2, 0, sizeof(cnt2));
	flag = 0;
	for(int i = 1;i <= n;i ++){
		if(!in[i] && ct[find(i)] != 1)dfs3(i, p[i]);
	}
	if(flag)return ; 
	for(int i = 1;i <= n;i ++){
		if(!d[i])continue;
		cnt2[d[i]] ++;
//		printf("%d %d\n", i, d[i]);
		if(cnt2[d[i]] > 1)return ;//出现重复的数字
	}
	int ntu = 0;
	for(int i = 1;i <= n;i ++){
		if(!cnt2[i])ntu = i;
	}
//	printf("%d\n", ntu);
	for(int i = 1;i <= n;i ++){
//		printf("%d %d\n", i, d[i]);
		if(ct[find(i)] != 1){
			if(ans[i] == 0)ans[i] = d[i];
			else if(ans[i] != d[i])ans[i] = -1;
		}
		if(ct[find(i)] == 1 && pq == 1){//如果只有一个没有约束的点，它的取值可能固定
			if(ans[i] == 0)ans[i] = ntu;
			else if(ans[i] != ntu)ans[i] = -1;
		}
		else if(ct[find(i)] == 1 && pq != 1)ans[i] = -1;
	}
}
vector<int>g;
void dfs2(int x){
//	printf("%d\n", x);
	if(x > k){
		calc();
		return ;
	}
	for(int i = 1;i <= n;i ++){
		if(i < num[g[x - 1]])continue;//如果最大数超过n，不合法
//		used[i] = 1;
		p[g[x - 1]] = i - num[g[x - 1]] + 1;
		dfs2(x + 1);
//		used[i] = 0;
	}
}
int main(){
	n = read(), m = read();
	for(int i = 1;i <= n;i ++)fa[i] = i;
	for(int i = 1;i <= m;i ++){
		a[i] = read(), b[i] = read(), c[i] = read();
		fa[find(a[i])] = find(b[i]), in[a[i]] ++;
		add_edge(b[i], a[i], c[i]);
	}
	for(int i = 1;i <= n;i ++)ct[find(i)] ++;
	for(int i = 1;i <= n;i ++){
		if(!in[i] && ct[find(i)] != 1)res = 0, dfs(i, 1), k ++, num[i] = res, g.push_back(i);
		if(ct[find(i)] == 1)pq ++;
	}
//	return 0;
	dfs2(1);
	if(m == 0){
		for(int i = 1;i <= n;i ++)printf("-1 ");
		return 0;
	}
	for(int i = 1;i <= n;i ++)printf("%d ", ans[i]);
	return 0;
}
```

---

## 作者：六楼溜刘 (赞：3)

### 题意

- 有一个长度为 $N$ 的排列 $A_i$，现在给定若干对关系，每对关系形如 $(x,y,c)$，表示 $A_x-A_y=c$。
- 对于所有 $i\in[1,N]$，若 $A_i$ 只有一种取值，输出 $A_i$，否则输出 $-1$。
- $1\le N\le 16$，保证至少一种合法的序列 $A_i$。

### 题解

容易想到用并查集处理有哪些 $A_i$ 是有关联的，具体来说，存储 $rank_{i,j}$ 表示若 $A_j=A_i+rank_{i,j}$，不存在则为 $0$，这个在并查集时可以暴力维护，复杂度 $O(N^2)$。

那么处理出相关联的集合后应该怎么做呢？

注意到 $N\le 16$，那么容易想到状态压缩，可以用一个 $16$ 位的整数存储某集合 $S$ 中数的相对大小（比如 $S_i=\{i_1,i_2,i_3,i_4\}$，其中 $A_{i_2}=A_{i_1}+3,A_{i_3}=A_{i_1}+4,A_{i_4}=A_{i_1}+15$，那么可以用 $B_i=1000000000011001$ 表示 $S$），然后问题就变成了若干个数 $1$ 的总数为 $n$，将它们每个左移若干位，使得或起来恰好为 $2^N-1$，且不相交。那么若 $B_i$ 有且仅有一种左移的位数能在加入其它数后变成一个合法的解，就**说明 $S_i$ 中所有元素均有唯一解**，并且 $A_i$ 的具体值是容易得到的。

于是容易想到 dp，具体来说，设 $f_{i,msk}$ 表示将前 $i$ 个数合并起来后能否得到 $msk$，转移比较简单，存储上一次塞了 $i-1$ 的所有 $msk$，然后枚举 $B_i$ 左移多少位从这些 $msk$ 转移即可。

这样只能求出有无解（但是题目保证有解捏），看起来很蠢啊。但是容易发现这说明 $f_{N,2^N-1}$ 的所有前驱**都能在进行一定操作后变成一个合法的解**，那么我们可以存储 $B_i$ 的每种左移的位数能转移到哪些 $f_{i,msk}$，再看有哪些左移位数所转移到的状态集合中有 $f_{N,2^N-1}$ 的前驱，就能得到 $S_i$ 有中的元素是否有唯一解了。

因为每个 $msk$ 只会出现一次，所以其实可以把 $i$ 这一维压掉，复杂度就是 $O(n^2+n2^n)$，非常可以接受。

### code

```cpp
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
#define forup(i,s,e) for(int i=(s);i<=(e);i++)
#define fordown(i,s,e) for(int i=(s);i>=(e);i--)
#ifdef DEBUG
#define msg(args...) fprintf(stderr,args)
#else
#define msg(...) void()
#endif
using namespace std;
#define gc getchar()
inline int read(){
    int x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const int N=20,inf=0x3f3f3f3f;
int n,m,ans[N];
int fa[N],rk[N][N],mx[N];
int bs[N];
int getfa(int x){return x==fa[x]?x:fa[x]=getfa(fa[x]);}
int flag[1<<16],num[N];
vector<int> e[1<<16];
void merge(int u,int v,int k){
	int fu=getfa(u),fv=getfa(v);
	if(fu==fv) return;
	int aa=rk[fv][v]+k-rk[fu][u];
	if(aa<0){
		aa=-aa;
		swap(fu,fv);
	}
	bs[fv]=bs[fv]|(bs[fu]<<aa);
	fa[fu]=fv;
	forup(i,1,n){
		if(rk[fu][i]){
			rk[fv][i]=rk[fu][i]+aa;
			rk[fu][i]=0;
			mx[fv]=max(mx[fv],rk[fv][i]);
		}
	}
	bs[fu]=0;
}
vector<int> vec[N][N];
void dfs(int x){
	for(auto i:e[x]){
		if(flag[i]) continue;
		flag[i]=true;
		dfs(i);
	}
}
signed main(){
	n=read();m=read();
	forup(i,1,n){
		fa[i]=i;
		mx[i]=1;
		bs[i]|=1;
		rk[i][i]=1;
	}
	forup(i,1,m){
		int a=read(),b=read(),k=read();
		merge(a,b,k);
	forup(i,1,n){
		forup(j,1,n){
			msg("%d ",rk[i][j]);
		}
		msg("|%d %d\n",bs[i],mx[i]);
	}
	}
	vector<int> v1,v2;
	v1.push_back(0);
	forup(i,1,n){
		if(fa[i]!=i) continue;
		for(auto j:v1){
			forup(k,0,n-mx[i]){
				if(j&(bs[i]<<k)) continue;
				int nxt=j|(bs[i]<<k);
				vec[i][k].push_back(nxt);
				v2.push_back(nxt);
				e[nxt].push_back(j);
			}
		}
		sort(v2.begin(),v2.end());
		v2.erase(unique(v2.begin(),v2.end()),v2.end());
		swap(v1,v2);v2.clear();
	}
	flag[(1<<n)-1]=true;
	dfs((1<<n)-1);
	forup(i,1,n){
		if(fa[i]!=i) continue;
		int cnt=0,lst=0;
		forup(j,0,n-mx[i]){
			for(auto k:vec[i][j]){
				if(flag[k]){
					++cnt;
					lst=j;
					break;
				}
			}
		}
		if(cnt>1){
			forup(j,1,n){
				if(rk[i][j]) ans[j]=-1;
			}
		}else{
			forup(j,1,n){
				if(rk[i][j]){
					ans[j]=rk[i][j]+lst;
				}
			}
		}
	}
	forup(i,1,n){
		printf("%d ",ans[i]);
	}
}
```

---

## 作者：xpz0525 (赞：2)

### [ABC352F] Estimate Order 题解


首先题目中保证了一定存在一种排序方式能使得约束之间不冲突，所以我们可以假定约束是正确的。 

由于这个约束非常的强，告诉了我们两个人之间排名的差值，因此如果将一条约束看作一条边建图的话，一个连通块内任意两个人之间的相对排名我们都可以求出。所以我们可以首先对每个连 通块都求出连通块内所有人与连通块内排名最靠前（数值最小）的那个人的相对排名。以样例 3 为例：

![](https://cdn.luogu.com.cn/upload/image_hosting/5xnkddb8.png)

图中每个节点上的 `rk` 代表在该连通块内，与排名最靠前的人的相对排名。

那么接下来如何找到一种合法的排名分配方案呢？很显然，我们现在不再需要考虑单个人了，而是按连通块为单位进行查找。由于本题的 $N$ 非常小，因此我们可以应用状态压缩的思想，用一个长度为 $N$ 的二进制数，第 $i$ 位 $1$ 或 $0$ 代表排名 $i$ 是否被占用。然后就可以使用 DP 跑出全的状态是否可达了。具体的，记第$i$ 个连通块的 `mask`（将连通块内各节点的 `rk` 对应的二进制位都设为 $1$）为 $mask[i]$，设 $dp[i][S]$ 代表考虑前 $i$ 个连通块，排名占用情况为 $S$ 是否可行，那么转移 时，我们只要用满足 `S & mask[i]<<x == 0` 的这些 $x$，去做 $dp[i-1][S] \rightarrow dp[i][S | mask[i]<<x]$ 即可。

但是题目要我们判断的是第 $i$ 个人的排名是否能被唯一确定。应该怎么判断这个呢？考虑到如果 第 $i$ 个人的排名能被唯一确定，那么他所属连通块的其他人的排名也能被唯一确定，所以其实只要连通块整体的位置（即上述的 $x$）能被唯一确定即可。一种较简单的判断方法是，我们每次排除一个连通块后，去跑上述的 DP，最后去判断这个被排除的连通块是否存在多种“插入”回其余连通块组成的排名的方案即可。

以下是 **AC** 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans[16];
vector<pair<int,int>> g[16];
int vis[17];
vector<pair<int,int>> c[17];
int tot,mask[17];
bool dp[17][1<<16];
void dfs(int u,int sum,int cid){ // 计算连通的各节点的相对排名，同时将节点编号及相对排名存入c中
	vis[u]=1;
	c[cid].push_back({u,sum});
	for(auto [v,w]:g[u]){
		if(vis[v])continue;
		dfs(v,sum+w,cid);
	}
}
int main(){
	cin>>n>>m;
	for(int i=1,u,v,w;i<=m;i++){
		cin>>u>>v>>w;
		u--;v--;
		g[u].push_back({v,-w}); // u到v的边权代表u的排名数值比v小了多少
		g[v].push_back({u,w});
	}
	for(int i=0;i<n;i++){ // 扫描每一个约束连通块
		if(vis[i])continue;
		dfs(i,0,++tot); // 连通块编号从1开始，为了方便后续dp初始状态
	}
	for(int i=1;i<=tot;i++){
		sort(c[i].begin(),c[i].end(),[](auto &a,auto &b){ // 连通块内按相对排名从小到大排序
			return a.second<b.second;
		});
		int base=c[i][0].second; // 将每个连通块的最小排名都平移到0
		for(auto &[u,w]:c[i]){
			w-=base;
			mask[i]|=(1<<w); // 计算连通块i的bitmask，这个位运算代表将mask[i]的第w位设置为1，不熟悉的可以重新看下位运算相关知识
		}
	}
	for(int i=0;i<n;i++)ans[i]=-1; // 初始化答案数组为-1
	for(int i=1;i<=tot;i++){ // 排除掉第i个连通块
		memset(dp,0,sizeof dp);
		dp[0][0]=true; // dp初始状态是全空
		for(int j=1;j<=tot;j++){
			if(i==j){ // 如果枚举到被排除的连通块了，直接“跳过”
				memcpy(dp[j],dp[j-1],sizeof dp[0]); // 复制上一行的dp状态到这一行，假装这行不存在
				continue;
			}
			for(int k=0;k<(1<<n);k++){ // 枚举添加第j个连通块前的状态
				if(!dp[j-1][k])continue; // 如果本来就不可达，那就跳过
				for(int s=mask[j];s<(1<<n);s<<=1){ // 移动第j个连通块的bitmask
					if((k&s)!=0)continue; // 如果存在冲突就跳过
					dp[j][k|s]=true; // 否则新状态可行
				}
			}
		}
		int pos=-1; // 当前连通块唯一可行的摆放位置 -1代表还没找到，-2代表有多个可行位置
		for(int s=0;s<(1<<n);s++){ // 枚举其他连通块摆完以后的排名状态
			if(!dp[tot][s])continue; // 如果其他连通块摆不出来这个状态就跳过
			for(int x=0;(mask[i]<<x)<(1<<n);x++){ // 尝试移动第i个连通块的bitmask
				if((s&(mask[i]<<x))!=0)continue; // 如果有冲突就跳过
				if(pos==-1) pos=x; // 找到第一个可行的摆放位置了
				else pos=-2; // 之前已经有别的可行位置了，标记成-2
			}
		}
		if(pos<0)continue; // 没有唯一位置就跳过
		for(auto [u,w]:c[i]){ // 将连通块内所有点的答案都计算出来
			ans[u]=w+pos+1; // w为u到连通块内排名最靠前的人的相对排名，pos为连通块的摆放位置（排名最靠前的人的绝对排名）。题目中的排名是从1开始的
		}
	}
	for(int i=0;i<n;i++){
		cout<<ans[i]<<' ';
	}
}
```

---

## 作者：Heldivis (赞：1)

## [ABC352F] Estimate Order

注意到 $N\le16$，考虑 Dfs 暴力搞。

考虑对某一个度数为零单点，如果有不止一个单点，它们可以互相交换，于是这些点都是 $-1$。

其他的点暴力搜索它可以是的值，每一个连通块只需要有一个点确定，就全部确定了。

这种情况下，当 $N=16$，最坏情况下连通块大小为 $\{1,2,2,2,2,2,2,3\}$，此时计算量大约为 $16\times15\times13\times11\times9\times7\times5\times3 \approx 3\times10^7$ 可以接受。

代码：

```cpp

#include <bits/stdc++.h>
#define int long long
using namespace std;
int read() { ... }
const int N = 20;
int n, m, du[N] /* 度数 */, sing /* 单点个数 */, res[N] /* 搜出来的结果 */,
    now[N] /* 当前结果 */, f[N] /* 是否用过当前排名 */;
vector<pair<int, int>> g[N];
void Dfs(int x) {
  if (x > n) {  // 全搜完了
    for (int i = 1; i <= n; i++)
      if (res[i] == 0) {  // 第一次查到
        res[i] = now[i];
      } else if (res[i] != now[i])  // 两次查询结果不一样
        res[i] = -1;
    return;
  }
  if (du[x] == 0 && sing > 1) {  // 单点如果不止一个就不用搜
    Dfs(x + 1);
    return;
  }
  for (auto i : g[x]) {
    int y = i.first, w = i.second;
    if (now[y] > 0) {  // 用 y 计算 x
      if (now[y] + w <= 0 || f[now[y] + w] == 1 || now[y] + w > n)
        return now[x] = 0, void(0);  // 当前排名不合法或用过了
      if (now[x] == 0)
        now[x] = now[y] + w;  // 当前点没有被排过名
      else if (now[x] != now[y] + w)
        return now[x] = 0, void(0);  // 当前点原有的排名与当前排名冲突
    }
  }
  if (now[x] > 0) {  // 算出来了
    f[now[x]] = 1;   // 标记当前用过点了
    Dfs(x + 1);      // 下一个
    f[now[x]] = 0;   // 回溯
    now[x] = 0;
    return;
  }
  for (int i = 1; i <= n; i++)  // 没搜到
    if (f[i] == 0) {            // 遍历每一个还没用过的点赋值
      f[i] = 1, now[x] = i;
      Dfs(x + 1);
      f[i] = now[x] = 0;  // 回溯
    }
}
signed main() {
#ifdef ____
  freopen(".in", "r", stdin);
  freopen(".out", "w", stdout);
#endif
  n = read();
  m = read();
  for (int i = 1; i <= m; i++) {
    int u = read(), v = read(), w = read();
    g[u].push_back({v, w});
    g[v].push_back({u, -w});
    du[u]++;
    du[v]++;
  }
  for (int i = 1; i <= n; i++) sing += (!du[i]);  // 计算单点
  if (sing > 1)  // 如果不止一个，那么他们可以相互交换，答案为 -1
    for (int i = 1; i <= n; i++)
      if (du[i] == 0) res[i] = -1;
  Dfs(1);
  for (int i = 1; i <= n; i++) printf("%lld ", res[i]);
  return 0;
}
```

---

## 作者：2022liaojianxiang (赞：1)

由题目可知，$N$ 的取值范围是 $N \le 16$。那么很明显是爆搜。

有一些人是没有任何排名关系的，有的有排名关系，我们把没有排名关系的叫做孤点，后者称为联立点。

首先分两种情况讨论：
- 有 $2$ 个以上的孤点；
- 有 $1$ 个或没有孤点。

那么第一种的孤点肯定都是不确定的，因为只要剩下多个选择的数字，就可以在这些孤点中互相交换，所以可以先把他们答案改为 $-1$。

第二种则只有 $1$ 个孤点那么剩下的那个数字就是这个孤点本身。否则没有则无需处理。

处理完孤点后我们先对每个联立点连边，连双向边，反过来则权值也取相反数。这样构成了一个有权图。接下来我们直接暴力搜索每个点的值（即每个人的排名）即可。我们看一下是否有联立关系对当前点造成影响，如果有则采取，并判断是否合法，不合法就返回（注意不能有相同的排名需要判重以及是否越界）。如果没有联立关系那么就枚举一个点给它。最后看一下是否是一个不确定取值的点，输出答案即可。

这种方法看似时间复杂度有 $O(N!)$，但实际上因为有联立关系的剪枝会小得多，只能说这是一个很普通而简单的搜索题。看个人的实现能力。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=10000009;
int n,m,a[N],b[N],c[N],t[N],s[N];
int bz1[N],e[N][2],ls[N],nx[N],em,bz[N];
void add(int x,int y,int z)
{
	em++;
	e[em][0]=y,e[em][1]=z;
	nx[em]=ls[x];
	ls[x]=em;
}
void dg(int x)
{
	if(x>n)
	{
		for(int i=1;i<=n;i++)
		{
			if(s[i]==0) s[i]=t[i];
			else if(s[i]!=t[i]) s[i]=-1;
		}
		return;
	}
	if(bz[x]==0)
	{
		dg(x+1);
		return;
	}
	for(int i=ls[x];i;i=nx[i])
	{
		if(t[e[i][0]]>0)
		{
			if(t[e[i][0]]+e[i][1]==0||bz1[t[e[i][0]]+e[i][1]]==1) {t[x]=0;return;}
			if(t[x]==0&&t[e[i][0]]+e[i][1]>0&&t[e[i][0]]+e[i][1]<=n) t[x]=t[e[i][0]]+e[i][1];
			else if(t[x]!=t[e[i][0]]+e[i][1]){t[x]=0;return;}
		}
	}
	if(t[x]>0)
	{
		bz1[t[x]]=1;
		dg(x+1);
		bz1[t[x]]=0;
		t[x]=0;
		return;
	}
	for(int i=1;i<=n;i++)
		if(bz1[i]==0)
		{
			bz1[i]=1,t[x]=i;
			dg(x+1);
			bz1[i]=t[x]=0;
		}
	t[x]=0;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&a[i],&b[i],&c[i]);
		add(a[i],b[i],c[i]),add(b[i],a[i],-c[i]);
		bz[a[i]]++,bz[b[i]]++;
	}
	int p=0;
	for(int i=1;i<=n;i++)
		if(bz[i]==0) p++;
	if(p>1) {for(int i=1;i<=n;i++) if(bz[i]==0) s[i]=-1; }
	else for(int i=1;i<=n;i++) if(bz[i]==0) bz[i]=-1;
	dg(1);
	for(int i=1;i<=n;i++) 
		printf("%d ",s[i]);
	return 0;
}
```

---

## 作者：GI录像机 (赞：1)

## 思路

看到这么小的数据范围，考虑暴搜。

有一些人的相对排名是确定的，因此在搜索时我们把它们一起决策。

但如果暴力枚举每一种可能的排名，在 $m=0$ 时是 $n!$ 的，显然无法通过。

这时候就需要一些优化，当一个人 $i$ 出现了多种可能的排名，那么他的答案就已经确定为 $-1$，我们无需再去枚举他。

因此在搜索时，先枚举答案未确定为 $-1$ 的人，在最后统计时判断已经被确认为 $-1$ 的人能不能填进剩余的位置即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 2e5 + 10, MOD = 1e9 + 7, INF = 0x3f3f3f3f;
int n = read(), m = read(), bel[N], id[N], useful[N], tot, ovo[N], ran[N], gg[N];
bool vis[N];
vector<pair<int, int> >v[N];
bool sfd(int now) {
	int ttmp = useful[now];
	if (now == tot + 1)return 1;
	if (gg[ttmp] != -1)return sfd(now + 1);
	bool tmp = 0;
	for (int j = 1; j <= n; j++) {
		bool flag = 1;
		for (int i = 0; i < v[ttmp].size(); i++)
			if (ran[v[ttmp][i].first + j]) {
				flag = 0;
				break;
			}
		if (flag) {
			for (int i = 0; i < v[ttmp].size(); i++)ran[v[ttmp][i].first + j] = v[ttmp][i].second;
			tmp = sfd(now + 1);
			for (int i = 0; i < v[ttmp].size(); i++)ran[v[ttmp][i].first + j] = 0;
			if (tmp)return tmp;
		}
	}
	return tmp;
}
void dfs(int now) {
	int ttmp = useful[now];
	if (now == tot + 1) {
		if (!sfd(1))return;
		for (int i = 1; i <= n; i++) {
			if (!ran[i])continue;
			if (ovo[ran[i]] && ovo[ran[i]] != i)ovo[ran[i]] = -1, gg[bel[ran[i]]] = -1;
			else ovo[ran[i]] = i;
		}
		return;
	}
	for (int j = 1; j <= n; j++) {
		if (gg[ttmp] == -1) {
			dfs(now + 1);
			return;
		}
		bool flag = 1;
		for (int i = 0; i < v[ttmp].size(); i++)
			if (ran[v[ttmp][i].first + j]) {
				flag = 0;
				break;
			}
		if (flag) {
			for (int i = 0; i < v[ttmp].size(); i++)ran[v[ttmp][i].first + j] = v[ttmp][i].second;
			dfs(now + 1);
			for (int i = 0; i < v[ttmp].size(); i++)ran[v[ttmp][i].first + j] = 0;
		}
	}
}
signed main() {
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	memset(ran, 1, sizeof(ran));
	for (int i = 1; i <= n; i++)v[i].push_back({0, i}), bel[i] = i, id[i] = ran[i] = 0;
	for (int i = 1; i <= m; i++) {
		int a = read(), b = read(), c = read();
		int fa = bel[a], fb = bel[b];
		if (fa != fb) {
			int ad = c + v[fb][id[b]].first - v[fa][id[a]].first;
			for (int j = 0; j < v[fa].size(); j++) {
				v[fa][j].first += ad;
				bel[v[fa][j].second] = fb;
				id[v[fa][j].second] = v[fb].size();
				v[fb].push_back(v[fa][j]);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		if (vis[bel[i]])continue;
		vis[bel[i]] = 1;
		useful[++tot] = bel[i];
		sort(v[bel[i]].begin(), v[bel[i]].end());
		for (int j = 1; j < v[bel[i]].size(); j++)v[bel[i]][j].first -= v[bel[i]][0].first;
		v[bel[i]][0].first = 0;
	}
	dfs(1);
	for (int i = 1; i <= n; i++) {
		write(ovo[i]);
		putchar(' ');
	}
	return 0;
}
```

---

## 作者：DGH_Didi (赞：1)

## 这是一篇只需要暴力的题解

### 题目大意

一场比赛有 $N$ 个人参与，给定 $M$ 组排名关系，求每个人的排名。

- $1\leq N\leq 16$
- $0 \leq M \leq \frac{N(N - 1)}{2}$

### 解题思路
考虑到总人数较少，直接暴力即可。具体地，先处理出每组关系所能拓展出的关系链，再用链之间尝试匹配。

这里有两个可以剪枝的地方，一是同样的链我们不需要，二是无排名关系的人可以先不考虑。每次匹配时就检查排名是否会重复，匹配完将每个人的排名塞到答案数组中。对于无排名关系的人，如果超过一个必然不确定，而如果是一个则检查其是否有多个可能的位置即可。

### 部分代码
- 寻找关系链
```
bool dfs(int x, int pos) {
    ok[x] = true;
    vis[pos] = x;
    bool flag = true;
    for (auto [y, d] : e[x]) {
        int np = pos + d;
        if (np < 1 || np > n) {
            return false;
        }
        if (vis[np] != 0 && vis[np] != y) {
            return false;
        }
        if (vis[np] == 0) {
            flag &= dfs(y, np);
        }
    }
    return flag;
}
```
- 尝试匹配
```cpp
void work(int x) {
    if (x == tot) {
        for (int i = 1; i <= n; i++) {
            ans[now[i]].insert(i);
        }
        return;
    }
    for (int i = 0; i < arr[qwq[x]].size(); i++) {
        const array<int, N> &nxt = arr[qwq[x]][i];
        bool flag = true;
        for (int j = 1; j <= n; j++) {
            if (now[j] && nxt[j]) {
                flag = false;
                break;
            }
        }
        if (!flag) {
            continue;
        }
        for (int j = 1; j <= n; j++) {
            if (nxt[j]) {
                now[j] = nxt[j];
            }
        }
        work(x + 1);
        for (int j = 1; j <= n; j++) {
            if (nxt[j]) {
                now[j] = 0;
            }
        }
    }
}
```

### [完整代码点这里](https://atcoder.jp/contests/abc352/submissions/53161261)

---

## 作者：Jerrycyx (赞：0)

> $N$ 方过百万，**暴力**碾标算。
> 
> **爆搜**挂着机，C++ NB。
> 
> 打表出奇迹，骗分过样例。
> 
> **暴力**进省一，AK CSP！

所以我们尝试对这道题使用暴搜。

-----

完全暴搜，即枚举所有可能的排名，其时间复杂度是 $O(N!)$，在 $N=16$ 时会达到 $20\ 922\ 789\ 888\ 000 \approx 2 \times 10^{13}$，明显过不去，我们需要**剪枝**和**优化**。

我的做法时对于每一个人，枚举他可能的排名，即 DFS 的参数是人的编号。

### 剪枝

下面列举的剪枝按照（我个人认为的）有效程度从高到底排序：

#### 剪枝 #1

没有必要非得枚举到底再统一判断是否合法，在枚举过程中每次只挑合法的排名来赋给当前这个人。具体来说，合法的排名需要满足以下条件：

+ 它与之前所已经选的排名没有冲突
+ 这个人使用这个排名不会与任意条件互相矛盾

对于第一条，可以记录已经选择的排名，每次只选未选择的排名。

对于第二条，可以记录与当前这个人构成条件关系的所有条件，然后就可以 $O(N)$ 判断（暴力判断是 $O(M)=O(N^2)$ 的）

**因为关系是双向的**（~~双向奔赴~~）**，所以 $a$ 比 $b$ 大 $c$ 等价于 $b$ 比 $a$ 大 $-c$，这两个关系需要同时纳入计算。**

#### 剪枝 #2

如果某一个人不与其他任何人构成条件关系，我们将这个人称为“独行侠”。

如果“独行侠”超过一个，那么交换任意两个“独行侠”得到的排名序列也是合法的，此时所有“独行侠”的有效排名数量一定大于 $1$，它们的答案就应该是 `-1`。

特别的，如果“独行侠”只有一个（如样例一的第 $1$ 个人），那么它无法与其它“独行侠”交换，仍然可以有确定排名。

#### 剪枝 #3

排名条件关系具有传递性，即如果 $x$ 比 $y$ 大 $2$，$y$ 比 $z$ 大 $3$，那么 $x$ 比 $z$ 大 $5$。

因此我们可以使用类似 Floyd 算法的方法，将所有的关系进行扩展，这会使得每一个连通块中都形成完全图。

这样可以增加限制条件，让枚举受限更大，可以有效剪枝。

### 优化

这里的内容仅用于卡一卡常数，理论上这些优化不是必要的。

另外你还可以手动加一加 `O2`。

#### 优化 #1

`bool` 数组可以全部用 `bitset` 代替，常数上略有优化。

同时，`bitset` 自带的 `_Find_first()` 和 `_Find_next()` 函数可以快速找到未被占用的排名，同样可以优化枚举效率。

#### 优化 #2

存储关系可以采用图论的存储方式，不用每次遍历所有关系。

邻接表或邻接矩阵均可，邻接表理论上要更快一些，不过 $n$ 并不大，也许邻接矩阵更快呢。

-----

差不多就这些，这样跑下来可以做到最大测试点 $122$ ms，[测评记录](https://atcoder.jp/contests/abc352/submissions/60003631)。

代码如下，带有上面所述的所有剪枝和优化：

```cpp
#include<cstdio>
#include<bitset>
#include<vector>
#include<algorithm>
#pragma GCC optimize(2)
using namespace std;

const int N=25,M=305;
int n,m;
int raw[N][N];
vector<pair<int,int>> g[N];
int only_one;

int rk[N];
bitset<N> can_use;
bitset<N> avail_rk[N];
void DFS(int p)
{
	if(p>n)
	{
		for(int i=1;i<=n;i++)
			avail_rk[i][rk[i]]=true;
		return;
	}
	if(g[p].empty() && only_one>1)
	{
		DFS(p+1);
		return;
	}
	for(int i=can_use._Find_first();i<=n;i=can_use._Find_next(i))
	{
		//try to place p in rank i
		bool ok=true;
		for(pair<int,int> tmp:g[p])
		{
			if(tmp.first>=p) break;
			if(i-rk[tmp.first]!=tmp.second)
			{
				ok=false;
				break;
			}
		}
		if(ok)
		{
			can_use[i]=false;
			rk[p]=i;
			DFS(p+1);
			can_use[i]=true;
		}
	}
	return;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int x,y,c;
		scanf("%d%d%d",&x,&y,&c);
		raw[x][y]=c,raw[y][x]=-c;
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(raw[i][k]&&raw[k][j])
					raw[i][j]=raw[i][k]+raw[k][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(raw[i][j]) g[i].push_back({j,raw[i][j]});
	for(int i=1;i<=n;i++)
	{
		sort(g[i].begin(),g[i].end());
		can_use[i]=true;
		if(g[i].empty()) only_one++;
	}
	DFS(1);
	for(int i=1;i<=n;i++)
	{
		if(avail_rk[i].count()==1 && !(g[i].empty() && only_one>1))
		{
			for(int j=1;j<=n;j++)
				if(avail_rk[i][j])
				{
					printf("%d ",j);
					break;
				}
		}
		else printf("-1 ");
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

考虑把限制看作无向边，最后就是若干个连通块。

为什么不是有向？因为有向边建出来的图奇奇怪怪很难拓扑序。

考虑对一限制 $(x,y,z)$ 建 $x\to y$，边权 $z$ 以及 $y\to x$，边权 $-z$，这样是等价的。


设共有 $k$ 个连通块，则第 $i$ 个连通块随意找一点 $x_i$，记录该连通块中的点与 $x_i$ 的限制差即可。

时间复杂度的证明：

注意到只考虑大小 $\ge 2$ 的连通块（否则无意义），所以 $k_{\max}=\dfrac{n}{2}$，总时间复杂度 $O(k! n^2) \approx O(10^7)$。

[代码](https://www.luogu.com.cn/paste/vc0ug97o)，细节有点多。

---

## 作者：zrl123456 (赞：0)

[题目](https://www.luogu.com.cn/problem/AT_abc352_f)

考察：~~爆搜~~状压 dp。  
题目简述：
给你一个 $n$，有一个 $1$ 到 $n$ 的排列 $a$，给你 $m$ 个关系，表示 $a_x$ 比 $a_y$ 大 $z$，问每一个数是否确定，若确定，输出是多少，若不是，输出 $-1$。  
数据保证有解。  
数据范围：  
$2\le n\le 16$  
$0\le m\le \frac{n(n-1)}{2}$

------------
首先我们像图一样建边，每条边 $u,v,w$ 表示 $a_u$ 比 $a_v$ 大 $w$（$w$ 可以是负数），然后我们再来几遍 dfs，得出每个部分中的每个元素比部分中的代表元素多了多少。设 $siz_i$ 表示第 $i$ 个部分的大小，$pos_i$ 表示第 $i$ 个元素比代表元素大多少。  

然后我们很容易想到状压，一个 $n$ 位的二进制数码，第 $i$ 位表示一个部分是否拥有一个比代表元素大 $i-1$ 的数。  
我们设第 $i$ 个部分的二进制数码是 $res_i$，这样，问题就变成了能否取合适的 $x$，使 $res_{i}\times 2^x$ 两两不相交（交集为空）。  

我们很容易发现一个部分内的元素，要么都不确定，要么都确定。那么只要把除一个之外的部分放上去，若剩余部分是固定的，则该部分都是固定的。那么我们先把除一个部分以外的部分都塞进去，然后再塞那个部分，统计一下 $x$ 有几个即可。  

总体复杂度为 $O(2^nn^3)$。  
代码：  
```cpp
#include<bits/stdc++.h>
#define inl inline
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;++i)
#define per(i,x,y) for(int i=x;i>=y;--i)
#define fst ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define INF LLONG_MAX
using namespace std;
const int N=25,M=(1ll<<16)+5;
int n,m,a,b,c,num,pos[N],res[N],siz[N],ans[N],vis[N];
vector<pair<int,int> >g[N],d;
bool f[N][M];
set<int>st;
inl bool cmp(pair<int,int>x,pair<int,int>y){
	return x.second<y.second;
}
inl void dfs(int x,int sum){
	vis[x]=num;
	d.push_back({x,sum});
	for(auto pr:g[x])
		if(!vis[pr.first]) dfs(pr.first,sum+pr.second);
}
signed main(){
	fst;
	cin>>n>>m;
	rep(i,1,m){
		cin>>a>>b>>c;
		g[a].push_back({b,-c});
		g[b].push_back({a,c});
	}
	rep(i,1,n)
		if(!vis[i]){
			d.clear();
			++num;
			dfs(i,0);
			sort(d.begin(),d.end(),cmp);
			for(auto pr:d){
				pos[pr.first]=pr.second-d[0].second;
				res[num]|=1ll<<pos[pr.first];
			}
			siz[num]=d[d.size()-1].second-d[0].second+1;
		}
	memset(ans,-1,sizeof(ans));
	rep(i,1,num){
		memset(f,0,sizeof(f));
		f[0][0]=1;
		rep(j,1,num)
			if(j==i) memcpy(f[j],f[j-1],sizeof(f[j-1]));
			else rep(k,0,(1ll<<n))
				if(f[j-1][k])
					rep(l,0,n-siz[j])
						if((k&(res[j]<<l))==0) f[j][k|(res[j]<<l)]=1;
		st.clear();
		rep(j,0,(1ll<<n)-1)
			if(f[num][j])
				rep(k,0,n-siz[i])
					if((j&(res[i]<<k))==0) st.insert(k);
		if(st.size()==1)
			rep(j,1,n)
				if(vis[j]==i) ans[j]=(*st.begin())+pos[j]+1;
	}
	rep(i,1,n) cout<<ans[i]<<' ';
	return 0;
} 
```

---

## 作者：yemuzhe (赞：0)

看到 $n \le 16$ 不难想到状压。

如果把人一个个加入进去，就无法确定之前的人的位置。

于是考虑把若干群没有关系的人同时加入。

想到可以用并查集维护有关系的人之间的关系。我们可以把最前面的人作为并查集森林中某棵树的根，然后类似[食物链](https://www.luogu.com.cn/problem/P2024)这题来做就好了（因为题目保证有解所以比那题简单些）。

我们可以在合并的时候顺便维护一下这群人的状态。具体来说，我们假设最前面的人是 $1$，在最前面的人 $k$ 名之后的人是 $2 ^ k$，直接状压在一起即可。

然后考虑状压 DP，状态就是 $f _ {i, j}$，表示选了前 $i$ 个集合、排名被占用的情况为 $j$。

发现如果一次性就 DP 完好像不能判唯一解……于是我们可以对于每一个集合，把其他集合 DP 一遍，再判这个集合能插入的位置是否唯一即可。

最后答案为 $i$ 号节点所属的集合能插入的位置加上 $i$ 号节点的深度。

时间复杂度 $O (2 ^ n n ^ 3)$，能过。

```cpp
#include <cstdio>
#include <algorithm>
#include <bitset>
#define N 20
#define PN 66005
using namespace std;

int n, m, fa[N], d[N], state[N];
int tot, to, a[N], b[N], id[N], ans[N];

bitset <PN> f[N];

int find (int x)
{
	if (!fa[x]) return x;
	int res = find (fa[x]);
	return d[x] += d[fa[x]], fa[x] = res;
}

void merge (int x, int y, int z)
{
	int fx = find (x), fy = find (y);
	if (fx == fy) return ;
	int w = d[x] + z - d[y];
	if (w < 0) swap (fx, fy), w = -w;
	fa[fy] = fx, state[fx] |= state[fy] << w, d[fy] = w;
	return ;
}

int main ()
{
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= n; i ++) state[i] = 1;
	for (int i = 1, x, y, z; i <= m; i ++)
	{
		scanf ("%d%d%d", &x, &y, &z), merge (y, x, z);
	}
	for (int i = 1; i <= n; i ++)
	{
		if (find (i) != i) continue;
		a[++ tot] = state[i], id[i] = tot;
	}
	f[0][0] = 1;
	for (int i = 1; i <= tot; i ++)
	{
		int cnt = to = 0, pos;
		for (int j = 1; j <= tot; j ++)
		{
			if (i != j) b[++ to] = a[j];
		}
		for (int j = 1; j <= to; j ++)
		{
			f[j].reset ();
			for (int k = b[j]; k < 1 << n; k <<= 1)
			{
				int rk = ~k & (1 << n) - 1;
				f[j][k] = f[j][k] | f[j - 1][0];
				for (int u = rk; u; u = u - 1 & rk)
				{
					f[j][u | k] = f[j][u | k] | f[j - 1][u];
				}
			}
		}
		for (int j = a[i], p = 1; j < 1 << n; j <<= 1, p ++)
		{
			int rj = ~j & (1 << n) - 1;
			if (f[to][rj]) cnt ++, pos = p;
		}
		if (cnt == 1) ans[i] = pos;
	}
	for (int i = 1; i <= n; i ++)
	{
		int t = ans[id[find (i)]];
		printf ("%d ", t ? t + d[i] : -1);
	}
	return 0;
}
```

---

