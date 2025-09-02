# [COCI 2012/2013 #2] INFORMACIJE

## 题目背景

**本题分值按 COCI 原题设置，满分 $140$。**

## 题目描述

Mirko 很无聊，所以他拿起一张纸，写下了一个含有 $N$ 个元素的序列 $A$，$1\sim N$ 的所有正整数在其中恰好仅出现一次。然后，他拿了另外一张纸，写下了 $M$ 个关于 $A$ 的描述。

每个描述有两种方式：

- `1 x y v`：表示 $[x,y]$ 区间中最大的数为 $v$。

- `2 x y v`：表示 $[x,y]$ 区间中最小的数为 $v$。

随后 Slavko 来偷走了他的第一张纸。Mirko 感到绝望，他想要你找到满足这些描述的序列，不需要跟原序列完全相同。

## 样例 #1

### 输入

```
3 2
1 1 1 1
2 2 2 2```

### 输出

```
1 2 3```

## 样例 #2

### 输入

```
4 2
1 1 1 1
2 3 4 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
5 2
1 2 3 3
2 4 5 4
```

### 输出

```
1 2 3 4 5```

# 题解

## 作者：cyffff (赞：2)

[$\text{Link}$](https://www.luogu.com.cn/problem/P8299)
## 题意
构造一个长为 $n$ 的排列 $p_{1\sim n}$，使得其满足给出的 $m$ 条限制，每条限制形如：
- `1 l r v`，要求 $p_{l\sim r}$ 的最大值为 $v$。
- `2 l r v`，要求 $p_{l\sim r}$ 的最小值为 $v$。

无解输出 `-1`。

$n\le200$。

Bonus：$n\le 2\times 10^4$。
## 思路
记 $p_{1\sim n}$ 的逆排列为 $q_{1\sim n}$，则题目的要求可转化为 $2n$ 条限制：$p_i\in[l_i,r_i]$，$q_v\in[a_v,b_v]$，不难看出可转化为二分图匹配问题，可以通过本题。

在平面直角坐标系上画出水平线段与竖直线段各 $n$ 条，分别为：
- $x=i$，$l_i\le y\le r_i$；
- $y=v$，$a_v\le x\le b_v$。

则水平线段 $i$ 与竖直线段 $v$ 连边当且仅当两条线段相交，可以使用主席树优化建图，对横坐标做扫描线，在端点出插入删除水平线段，扫到一个横坐标时将该竖直线段与当前区间内存在的水平线段连边。

点数与边数均为 $O(n\log n)$。

考虑一个点 $i$ 能连向哪些值 $v$，若值 $v$ 未在任意限制中出现，则可直接建出这类值的线段树，对每个位置 $i$ 使用普通线段树优化建图连向区间内的这类值。

否则注意到对于一个 $p_i\in[l,r]$，位置 $i$ 可取且覆盖位置 $i$ 的限制的值只可能为 $l$ 或者 $r$，我们只需要根据 $q_l,q_r$ 的条件判断 $p_i$ 是否可取到值 $l,r$ 便可。

点数为 $O(n)$，边数为 $O(n\log n)$。

使用 Dinic 算法即可通过 $n\le 2\times 10^4$ 版本。

---

## 作者：Svemit (赞：1)

# Sol:

首先考虑只要求最大值小于等于 $v$ 和最小值大于等于 $v$ 的怎么做。

直接处理出每个位置能放的数的上下界 $L_i,R_i$。

找到一组解就相当于 $i$ 向 $[L_i, R_i]$ 连边，在这个二分图上找到一个匹配。

最大值等于 $v$ 怎么做？

在刚刚的条件上，发现最大值等于 $v$ 等价于在 $[l, r]$ 中一定出现 $v$ 这个数。

考虑如何钦定 $v$ 一定出现在某个区间。

处理出 $Lv_i$ 和 $Rv_i$ 表示 $v$ 能放的位置的上下界。

建图时再判一下 $L, R, Lv, Rv$ 是否都满足条件即可。

跑二分图最大匹配，最大匹配为 $n$ 即为有解，否则 `-1`。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e2 + 5;

int n, m;
int L[N], R[N];
int Lv[N], Rv[N];
vector<int> e[N];
bool b[N];
int match[N];
int ans[N];

bool dfs(int u) {
	for (auto v : e[u]) {
		if (!b[v]) {
			b[v] = true;
			if (!match[v] || dfs(match[v])) {
				match[v] = u;
				return true;
			}
		}
	}
	return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    cin >> n >> m;
    
    for (int i = 1; i <= n; i ++) {
    	L[i] = Lv[i] = 1;
		R[i] = Rv[i] = n;
	}
    
    for (int i = 1; i <= m; i ++) {
    	int op, l, r, v;
    	cin >> op >> l >> r >> v;
    	Lv[v] = max(l, Lv[v]), Rv[v] = min(r, Rv[v]); 
    	for (int j = l; j <= r; j ++) {
    		if (op == 2) {
    			L[j] = max(L[j], v);
			} else {
				R[j] = min(R[j], v);
			}
		}
	}
	
	for (int i = 1; i <= n; i ++) {
		for (int j = Lv[i]; j <= Rv[i]; j ++) {
			if (L[j] <= i && i <= R[j]) {
				e[i].push_back(j);
			}
		}
	}
	
	int cnt = 0;
	for (int i = 1; i <= n; i ++) {
		memset(b, false, sizeof b);
		if (dfs(i)) {
			cnt ++;
		}
	}
	
	if (cnt != n) {
		cout << -1 << "\n";
	} else {
		for (int i = 1; i <= n; i ++) {
			cout << match[i] << " ";
		}
	}

    return 0;
}
```

---

## 作者：Laisira (赞：1)

## 水一篇增广路的题解
### 题面
给出 $m$ 个限制条件，形如 $opt,x,y,v$ 指：

- $opt=1,\max^{y}_{i=x}=v$
- $opt=2,\min^{y}_{i=x}=v$

然后构造一个由 $1$ 到 $n$ 组成的数列符合限制，找不到就打印 $-1$。

### 思路
对于每个位置，他可以选择的数是可知且有限的，而我们就是要给每个位置一个数，从可选的数选就不用担心不合法。然后把每个位置和可选的数连边，跑一边二分图最大匹配，如果匹配的数小于 $n$ 输出 $-1$，否则输出匹配完的就行了。

### 代码
```cpp
#include<bits/stdc++.h>
#define Maxn 405 
using namespace std;
int mp[Maxn][Maxn];
int fid[Maxn],dfn[Maxn];
vector<int> q[Maxn];
bool dfs(int x,int Time) {
    if(dfn[x] == Time)return false;
    dfn[x]=Time;
    for(int u:q[x]) {
        if(fid[u]==0||dfs(fid[u],Time)) {
            fid[u]=x;
            fid[x]=u;
            return true;
        }
    } return false;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin>>n>>m;
    while(m--) {
        int opt,l,r,x;
        cin>>opt>>l>>r>>x;
        if(opt == 2) {
            for(int i=l;i<=r;i++)
                for(int j=1;j<x;j++)
                    mp[i][j+n]=1;
            for(int i=1;i<=n;i++)
                if(i<l||i>r)mp[i][x+n]=1;
        } else {
            for(int i=l;i<=r;i++)
                for(int j=x+1;j<=n;j++)
                    mp[i][j+n]=1;
            for(int i=1;i<=n;i++)
                if(i<l||i>r)mp[i][x+n]=1;
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(!mp[i][j+n])
                q[i].push_back(j+n);
    int cnt=0;
    for(int i=1;i<=n;i++) 
        if(dfs(i,i))cnt++;
        else break;
    if(cnt!=n)cout<<-1;
    else {
        for(int i=1;i<=n;i++)
            cout<<fid[i]-n<<" ";
    }
    return 0;
}
```

---

## 作者：有趣的问题 (赞：1)

### 题意

你需要构造一个 $1∼N$ 的排列，满足 $M$ 个要求，要求形式是给出 $l,r$ 中的最大值或最小值。

### 思路

不难看出，这是一个二分图匹配问题。我们要给每个位置匹配一个数。那么怎么建边呢？我们发现根据题目给出的要求，好像不是很好直接看出每个位置能匹配哪些数。不过正难则反，题目给出的要求是很容易看出每个位置不能匹配哪些数的。显然如果题目给出 $[l,r]$ 中最小的数是 $x$，那么这些位置不能与任何小于 $x$ 的数匹配。大于同理。

这样就够了吗？其实是有问题的。我们这样无法保证 $x$ 这个数一定被分配到 $[l,r]$ 这个区间里。所以我们还有让所有不在 $[l,r]$ 的数都不能匹配到 $x$，这样就保证满足题目条件了。

至于二分图匹配部分，可以用匈牙利，当然我用的 Dinic。

### 丑陋的代码（跑得贼慢）

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
bool ok[205][205];
int n,m,cnt=1,lst[415],s,t,inf=0x3f3f3f3f,now[415],dep[415],flow,seat[415]; 
struct edge{
	int f,t,val,lst;
	edge(int f=0,int t=0,int val=0,int lst=0):
		f(f),t(t),val(val),lst(lst){}; 
}e[400005];
void add(int u,int v,int w){
	e[++cnt]=edge(u,v,w,lst[u]);lst[u]=cnt;
	e[++cnt]=edge(v,u,0,lst[v]);lst[v]=cnt;
}
bool bfs(){
	memset(dep,-1,sizeof(dep));
	dep[s]=0;
	queue<int> q;
	q.push(s);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		now[u]=lst[u];
		for(int i=lst[u];i;i=e[i].lst){
			int v=e[i].t;
			if(dep[v]==-1&&e[i].val){
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	} 
	return dep[t]!=-1;
}
int dfs(int u,int in){
	if(u==t)return in;
	int out=0;
	for(int i=now[u];i;i=e[i].lst){
		now[u]=i;
		int v=e[i].t;
		if(dep[v]==dep[u]+1&&e[i].val){
			int go=dfs(v,min(in,e[i].val));
			in-=go,out+=go;
			e[i].val-=go,e[i^1].val+=go;
			if(!in)break;
		}
	}
	if(!out)dep[u]=-1;
	return out;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int op,u,v,x;
		cin>>op>>u>>v>>x;
		if(op==1){
			for(int j=u;j<=v;j++){
				for(int k=x+1;k<=n;k++){
					ok[j][k]=1;
				}
			}
			for(int j=1;j<u;j++){
				ok[j][x]=1;
			}
			for(int j=v+1;j<=n;j++){
				ok[j][x]=1;
			}
		}
		else{
			for(int j=u;j<=v;j++){
				for(int k=1;k<x;k++){
					ok[j][k]=1;
				}
			}
			for(int j=1;j<u;j++){
				ok[j][x]=1;
			}
			for(int j=v+1;j<=n;j++){
				ok[j][x]=1;
			}
		}
	}
	s=0,t=n*2+1;
	for(int i=1;i<=n;i++){
		add(s,i,1);
		add(i+n,t,1);
		for(int j=1;j<=n;j++){
			if(!ok[i][j])add(i,j+n,1);
		}
	}
	while(bfs()){
		flow+=dfs(s,inf);
	}
	if(flow!=n)puts("-1");
	else{
		for(int i=2;i<=cnt;i++){
			if(!e[i].val&&e[i^1].val&&e[i].f<=n&&e[i].f&&e[i].t>n&&e[i].t!=t){
				seat[e[i].f]=e[i].t;
			}
		}
		for(int i=1;i<=n;i++)cout<<seat[i]-n<<' ';
	}
	return 0;
}


---

## 作者：XuYueming (赞：0)

## 前言

题目链接：[洛谷](https://www.luogu.com.cn/problem/P8299)。

[更好？的体验](https://www.cnblogs.com/XuYueming/p/18389339)。

## 题意简述

你需要构造一个 $1 \sim n$ 的排列 $a$，满足 $m$ 个条件，格式如下：

- `1 x y v`：$\max \limits _ {i = l} ^ r a_i = v$。

- `2 x y v`：$\min \limits _ {i = l} ^ r a_i = v$。

## 题目分析

首先这个最值很难受，考虑能不能转化成我们喜欢的二元关系。比如，当 $[l, r]$ 的最值为 $v$ 时，说明 $v$ 必须出现在这段区间内。再思考一下，对于最大值，为了保证这段区间的最大值是 $v$，那么大于 $v$ 的数就不能出现在这段区间内，最小值同理。把前者“必须出现”转化为补集的“不能出现”，这样我们处理出了对于每一个值 $v$ 不能出现的位置。

有什么用呢？我在膜尼赛上用爆搜骗分。直接骗肯定不好看，这时候就需要一些常见的剪枝优化。对于限制类题目，我们把限制多的先搜索能节约不少时间。此外，寻找到一个没有确定的位置可以使用双向链表优化。预处理区间覆盖转化为差分。能够得到 $86$ 分的[好成绩](https://www.luogu.com.cn/record/175407763)。

话说回来，这么搜肯定是错的，那还有什么做法呢？我们必须敏感地注意到位置和值的特殊二元关系。到了最后，每一个位置一定一一对应一个值，将“不能”反转得到若干“可能”的匹配关系，最后的对应一定这些可能匹配中的一种。

不妨继续抽象模型。有红黄两种颜色的小球各 $n$ 个，我们知道了每一个红球可能和哪些黄球匹配，找到一种匹配方式，使得红黄球一一对应。这不就是二分图的裸题了吗？我们将可能得匹配方式看作是值向位置的连边，最终的答案就是位置对应的那个值。

注意到存在无解的情况，此时说明二分图不存在完美匹配，判断即可。

时间复杂度理论上来说可以优化到：$\Theta(m \log n + n^{\frac{5}{2}})$，但是可能比不过常数小的 $\Theta(nm + n ^ 3)$？

## 代码

```cpp
#include <cstdio>

#define isdigit(x) ('0' <= x && x <= '9')
inline void read(int &x) {
    x = 0; char ch = getchar();
    for (; !isdigit(ch); ch = getchar());
    for (;  isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch ^ 48);
}

const int N = 220;

int n, m, val[N], mi[N], mx[N], cant[N][N];
int to[N * N], nxt[N * N], head[N], tot;
int vis[N], timer, mark[N];

bool dfs(int now) {
    for (int i = head[now]; i; i = nxt[i]) {
        int to = ::to[i];
        if (vis[to] != timer) {
            vis[to] = timer;
            if (!mark[to] || dfs(mark[to])) {
                mark[to] = now;
                return true;
            }
        }
    }
    return false;
}

signed main() {
    read(n), read(m);
    for (int i = 1; i <= n; ++i) mx[i] = n;
    for (int i = 1, op, l, r, v; i <= m; ++i) {
        read(op), read(l), read(r), read(v);
        ++cant[v][1], --cant[v][l];
        ++cant[v][r + 1], --cant[v][n + 1];
        for (int j = l; j <= r; ++j) {
            if (op == 1)
                v < mx[j] && (mx[j] = v);
            else
                v > mi[j] && (mi[j] = v);
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cant[i][j] += cant[i][j - 1];
            if (mi[j] <= i && i <= mx[j] && !cant[i][j]) {
                to[++tot] = j;
                nxt[tot] = head[i];
                head[i] = tot;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        ++timer;
        if (!dfs(i)) return puts("-1"), 0;
    }
    for (int i = 1; i <= n; ++i) printf("%d ", mark[i]);
    return 0;
}
```

## 总结 & 反思

说实话，都想到爆搜，想不到二分图匹配确实不应该，应该归根结底是二分图模型不熟悉了。

二分图是处理两种不同类型的物件之间的对应关系。对于本题，一个排列的构造，我们如果能找出值和下标的二元关系，就能建立二分图，跑匹配，最后输出匹配的方案。

---

## 作者：LOVE_Ynoi (赞：0)

我们可以发现这些限制关系给了我们每个位置不能填上什么东西。  
所以考虑建图，若第 $i$ 位可以填上 $j$ 就把 $i$ 和 $j$ 连边，二分图完美匹配即可。  
考虑如何求出这些某个点是否可以放某个数。

**举一个例子**：

例如样例三中的 ``1 2 3 3``，  
**他标志着从 2 到 3 的最大值为 3，则 2 到 3 中不可能出现 4 和 5，同时其他的位置不可能出现 3。**  
可以用 ``set`` 和 ``vector`` 等来完成这个操作。

对于每一个位置开一个 ``set``，标志这个位置能连向哪一个位置。  
对于一个询问，$[l,r]$ 中删除比 $v$ 大（最大值询问）或小（最小值询问）
的所有值，对于 $[l,r]$ 以外的值就直接删除 $v$ 即可。

我的代码使用的是 `set`，二分图匹配用的是匈牙利算法。

时间复杂度 $O(mn \log n + n^3)$。（最多有 $n^2$ 条边，$n$ 个点。）

```c++
#include<bits/stdc++.h>
using namespace std;
int n,m;
set<int> se[210];
vector<int> G[210];
int vistag[200010];
int mtch[200010];
bool dfs(int u,int tag)
{
    if(vistag[u] == tag) return false;
    vistag[u] = tag;
    for(auto to : G[u])
    {
        if(mtch[to] == 0 || dfs(mtch[to],tag))
        {
            mtch[to] = u;
            return true;
        }
    }
    return false;
}
int pos[200010];
int main()
{
    // freopen("informacije.in.1a","r",stdin);
    cin >> n >> m;
    for(int i = 1;i <= n;i ++)
    {
        for(int j = 1;j <= n;j ++)
        {
            se[i].insert(j);
        }
    }
    for(int i = 1;i <= m;i ++)
    {
        int op,l,r,v;
        cin>>op>>l>>r>>v;
        for(int j = 1;j < l;j ++) se[j].erase(v);
        for(int j = r + 1;j <= n;j ++) se[j].erase(v);
        for(int j = l;j <= r;j ++)
        {
            bool fl = se[j].find(v) != se[j].end();
            if(op == 2) se[j].erase(se[j].begin(),se[j].lower_bound(v));
            else se[j].erase(se[j].lower_bound(v),se[j].end());
            if(fl) se[j].insert(v); //注意这里如果原先存 v 在上面会被删除，这里把它加回来。
        }
    }
    for(int i = 1;i <= n;i ++)
    {
        for(auto to : se[i])
        {
            G[i].push_back(to);
        }
    }
    int ans = 0;
    for(int i = 1;i <= n;i ++) 
    {
        ans += dfs(i,i);
    }
    if(ans == n)
    {
        for(int i = 1;i <= n;i ++) pos[mtch[i]] = i;
    }else return cout<<-1<<endl,0;
    for(int i = 1;i <= n;i ++) cout<<pos[i]<<" ";
    cout<<endl;
    return 0;
}
```

---

## 作者：Graphcity (赞：0)

考虑限制 `1 x y v`，可以得到如下信息：

- 下标区间 $[x,y]$ 对应的值 $\le v$。
- $v$ 值对应的下标在 $[x,y]$ 内。

第二种限制同理。这样，我们就得到了每个下标对应的值域区间，和每个值对应的下标区间。

如果一个值和下标都互相在对方的区间内，则连一条边。有解当且仅当这张二分图有完美匹配。

直接跑匈牙利算法就行了。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=400;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,m,L[Maxn+5],R[Maxn+5],S[Maxn+5],T[Maxn+5];
int vis[Maxn+5],mch[Maxn+5];
vector<int> v[Maxn+5];

inline int dfs(int x)
{
    if(vis[x]) return 0; vis[x]=1;
    for(auto y:v[x]) if(!mch[y] || dfs(mch[y]))
        return mch[x]=y,mch[y]=x,1;
    return 0;
}

int main()
{
    n=read(),m=read();
    For(i,1,n) L[i]=1,R[i]=n,S[i]=1,T[i]=n;
    while(m--)
    {
        int op=read(),l=read(),r=read(),x=read();
        if(op==1)
        {
            For(i,l,r) R[i]=min(R[i],x);
            S[x]=max(S[x],l),T[x]=min(T[x],r);
        }
        if(op==2)
        {
            For(i,l,r) L[i]=max(L[i],x);
            S[x]=max(S[x],l),T[x]=min(T[x],r);
        }
    }
    For(i,1,n) For(j,1,n) if(L[i]<=j && j<=R[i] && S[j]<=i && i<=T[j])
        v[i].push_back(n+j),v[n+j].push_back(i);
    For(i,1,n)
    {
        memset(vis,0,sizeof(vis));
        if(!dfs(i)) {cout<<-1<<endl; return 0;}
    }
    For(i,1,n) cout<<mch[i]-n<<' '; cout<<endl;
    return 0;
}
```

---

## 作者：y0y68 (赞：0)

建图好题

考虑以下做法：如果第 $i$ 个位置能放上数 $j$，那么将 $i$ 到 $j$ 之间连有向边。最后跑一遍二分图匹配就出来了。

只用求出在哪些点对间连边即可。

记 $posl[i],posr[i]$ 分别表示能放置数 $i$ 的最左端和最右端。

记 $numl[i],numr[i]$ 分别表示能放置在第 $i$ 个位置上的数的最小值和最大值。

那么对于每个限制 $(opt,l,r,x)$，有：

$$posl[x]=\max\{posl[x],l\}$$
$$posr[x]=\min\{posr[x],r\}$$

意思是对于每个 $x$，无论它是 $[l,r]$ 内的最小值还是最大值，$[l,r]$ 内必定要出现 $x$，于是可以限制 $x$ 的放置范围。

对于 $opt=1$，有：

$$numr[i]=\min\{numr[i],x\}(l \le i \le r)$$

意思是对于每个 $[l,r]$ 中的位置，由于 $[l,r]$ 中最大数为 $x$，故 $[l,r]$ 内每个位置可放置的数的最大值可以被限制。

同理，对于 $opt=2$，有：

$$numl[i]=\max\{numl[i],x\}(l \le i \le r)$$

于是这四个数组就处理完了。之后连边跑匈牙利即可。

```
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=205;
bool vis[N];
vector<int>g[N];
int n,m,mt[N],numl[N],numr[N],posl[N],posr[N];
inline bool match(int u){
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(vis[v])continue;
		vis[v]=1;
		if(!mt[v]||match(mt[v])){
			mt[v]=u;return true;
		}
	}
	return false;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		posl[i]=numl[i]=1;
		posr[i]=numr[i]=n;
	}//初始化范围
	while(m--){
		int opt,l,r,x;
		scanf("%d%d%d%d",&opt,&l,&r,&x);
		posl[x]=max(posl[x],l);
		posr[x]=min(posr[x],r);
		for(int i=l;i<=r;i++){
			if(opt==1)numr[i]=min(numr[i],x);
			else numl[i]=max(numl[i],x);
		}
	}
	for(int i=1;i<=n;i++)//枚举位置
		for(int j=1;j<=n;j++)//枚举放置的数
			if(numl[i]<=j&&j<=numr[i]&&posl[j]<=i&&i<=posr[j])//位置和放置的数都在彼此的限制范围之内
				g[j].push_back(i);//注意从位置到数连边，方便输出方案
	bool flag=0;
	for(int i=1;i<=n;i++){
		memset(vis,0,sizeof vis);
		if(!match(i)){flag=1;break;}
	}
	if(flag){
		puts("-1");return 0;
	}
	for(int i=1;i<=n;i++)
		printf("%d ",mt[i]);//匹配结果
	return puts(""),0;
}
```

---

