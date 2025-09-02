# 「Cfz Round 5」Mata rainen

## 题目背景

题目名称意为：明年见。

小 R 是一个正在上高三的女孩子。她在升入高三的暑假复习了[《种树郭橐（tuó）驼传》](https://baike.baidu.com/item/%E7%A7%8D%E6%A0%91%E9%83%AD%E6%A9%90%E9%A9%BC%E4%BC%A0)，便编出了这道与树有关的题。

在把这道题目丢给出题组后，她决定把全部时间和精力投入到高考的旅程中，期待在 2025 年的暑假在算法竞赛中与大家再会。

## 题目描述

请判断是否存在一棵树满足如下条件。若存在，请尝试给出构造。

树中包含 $n$ 个结点，编号为 $1\sim n$。另外，给定 $m$ 个点对 $(s_i,t_i)$，要求树上这 $m$ 条从点 $s_i$ 到点 $t_i$ 的路径覆盖每条边**恰好**一次 $^\dagger$。

**若你正确判断了是否有解，但不会构造出这棵树，也可以获得一定的分数，详见【评分方式】。**

$\dagger$ 称从点 $s$ 到点 $t$ 的路径覆盖一条边 $(u,v)$，当且仅当边 $(u,v)$ 在点 $s$ 到点 $t$ 的最短路径上。

## 说明/提示

#### 「样例解释 #1」

![](https://cdn.luogu.com.cn/upload/image_hosting/rgnwakkq.png)

左上图为样例输出中给出的树。边 $(1,5),(5,2)$ 被路径 $(1,2)$ 覆盖，边 $(3,5),(5,6),(6,4)$ 被路径 $(3,4)$ 覆盖，符合题目要求。

右上图中边 $(5,6)$ 被路径 $(1,2)$ 和 $(3,4)$ 覆盖，不符合题目要求。

左下图中边 $(5,6)$ 未被任何路径覆盖，不符合题目要求。

右下图不是一棵树，不符合题目要求。

#### 「样例解释 #2」

可以证明不存在符合要求的树。

#### 「评分方式」

本题采用自定义校验器（Special Judge）进行评测。

对于每个测试点：

- 若第一行格式错误或与答案不匹配（大小写不敏感），得 $0\%$ 的分数。
- 若第一行答案正确且为 `No`，得 $100\%$ 的分数。
- 若第一行答案正确且为 `Yes`，**但后 $n-1$ 行格式错误**，得 $0\%$ 的分数。  
因此，**请务必保证输出为一棵树**。
- 若第一行答案正确且为 `Yes`，后 $n-1$ 行格式正确但树不符合要求，得 $20\%$ 的分数。
- 若第一行答案正确且为 `Yes`，后 $n-1$ 行格式正确且树符合要求，得 $100\%$ 的分数。

也就是说，对于第一个样例，在正确输出 `Yes` 的基础上，输出左上图可以得到满分，输出右上图、左下图可以得到 $20\%$ 的分数，输出右下图不能得到任何分数；对于第二个样例，正确输出 `No` 即可得到满分。

#### 「数据范围」

对于所有测试数据，保证：

- $2\le n\le 3\times 10^5$；
- $1\le m\le 3\times 10^5$；
- $1\le s_i,t_i\le n$ 且 $s_i\ne t_i$。

**本题采用捆绑测试。**

- Subtask 0（10 points）：$n\le 3$，$m\le 3$。
- Subtask 1（10 points）：$n\le 10$，$m\le 10$。
- Subtask 2（20 points）：$m=1$。
- Subtask 3（10 points）：$n\le 300$，$m\le 300$。
- Subtask 4（10 points）：$n\le 2\times 10^3$，$m\le 2\times 10^3$。
- Subtask 5（20 points）：$m\le 2\times 10^3$。
- Subtask 6（20 points）：无特殊限制。

#### 「Hack 数据」

本题于赛后添加了部分 Hack 数据。这些数据均满足 Subtask 6 对数据规模的限制，他们被添加到 Subtask 7 中。这些数据不计分，但只有通过所有数据，才算做 AC 本题。

- Subtask 7（0 points）：赛后添加的 Hack 数据。

## 样例 #1

### 输入

```
6 2
1 2
3 4```

### 输出

```
Yes
1 5
2 5
3 5
4 6
5 6```

## 样例 #2

### 输入

```
3 3
1 2
2 3
1 3```

### 输出

```
No```

# 题解

## 作者：floris (赞：12)

## 思路：

首先要判断是否可以建符合题目要求的树，显然，当图中存在环时，不能成为树，因此我们想到使用并查集维护，当输入的两个点的祖先相同时，因为这两个点还会连接，所以一定会成环，此时就结束掉程序；否则就可以建树。

因为这个题目中每条边都只被给出点的最短路径经过了一遍，因此，我们先将输入的点对直接建边（如下图蓝点），然后把剩下的点（下图红点）放在一边，再取出一对输入的点对（绿色点）：

![](https://cdn.luogu.com.cn/upload/image_hosting/lg53l6vo.png)

然后将绿色点作为头和尾将剩余点或树根串联起来，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/pyyr5ij0.png)

这样保证了每条边都可以走到，更重要的是，~~它代码好写。~~

写代码时要注意的是：每次连边后都要记录上一次连边的点，下一次要用。

## code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 300005
int n,m,f[N];
int find(int x){
	if(f[x]==x) return x;
	return f[x]=find(f[x]);
}
int last,cnt=0;
struct node{
	int x,y;
}e[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1;i<=m;i++){
		cin>>e[i].x>>e[i].y;
		if(find(e[i].x)!=find(e[i].y))f[find(e[i].y)]=find(e[i].x);
		else{
			cout<<"No"<<'\n';
			return 0;
		}
	}
	cout<<"Yes"<<'\n';
	for(int i=1;i<m;i++)cout<<e[i].x<<" "<<e[i].y<<'\n';
	last=e[m].x;
	for(int i=1;i<=n;i++){
		if(find(i)==i&&find(i)!=find(e[m].x)){
			cout<<last<<" "<<i<<'\n';
			last=i;
		}
	}
	cout<<e[m].y<<" "<<last<<'\n';
	return 0;
}
```

---

## 作者：Drifty (赞：11)

### Solution

建议降黄。

我们会发现这些关系一定不会构成环，因为如果其构成了环，在一棵树上自然不可能找到不重复的一条路径来满足这些约束。

然后我们考虑如果这些关系不构成环时的情况。我们随便找一个约束 $(s_k, t_k)$ 拿出来，剩下的 $(s_i,t_i)$ 之间直接连边。然后此时我们就有若干个连通块。最后，我们把这些连通块直接串起来，就完成了构造，先前拿出来的 $(s_k, t_k)$ 作为这条链的两个端点就好。

实现上用了并查集判断连通块。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 3e5 + 7;
using i64 = long long;
int n, m, s[N], t[N], v[N], fa[N], h[N];
int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
int main() {
	cin.tie(NULL) -> sync_with_stdio(false);
	cin >> n >> m;
    for (int i = 1; i <= n; i ++) fa[i] = i, h[i] = 1;
    vector <int> un;
    for (int i = 1; i <= m; i ++) {
        cin >> s[i] >> t[i];
        int fu = find(s[i]), fv = find(t[i]);
        if (fu == fv) return cout << "No\n", 0;
        h[fu] += h[fv]; fa[fv] = fu;
    }
    cout << "Yes\n";
    for (int i = 1; i < m; i ++) cout << s[i] << ' ' << t[i] << '\n';
    un.push_back(s[m]);
    for (int i = 1; i <= n; i ++)
        if (find(i) != find(s[m]) && find(i) == i) un.push_back(i);
    un.push_back(t[m]);
    for (int i = 1; i < (int)un.size(); i ++)
        cout << un[i - 1] << ' ' << un[i] << '\n';
    return 0;
}
```

---

## 作者：rui_er (赞：9)

**本题解是「Cfz Round 5」Mata rainen 的官方题解。**

注意到，有解的充要条件为：将输入的 $m$ 个数对 $(s_i,t_i)$ 连边，得到的 $n$ 点 $m$ 边无向图无环。特别地，重复边同样视为有环。

必要性证明：只需证当该无向图有环时原问题无解。树上两点间任意路径一定包含他们之间的最短路径。考察无向图环上代表的两条路径，一定覆盖了这条最短路径至少两次，因此原问题无解，必要性得证。

充分性将由下方的构造给出。

当无向图无环时，其形态为森林，且每条边恰好被覆盖一次。对于两个连通块 $A$ 和 $B$（假设 $A$ 中有至少一条边），我们可以在 $A$ 中任选一条边断掉，并在中间插入 $B$ 中的任意一个点，重新连上两条边。此时，$A$ 和 $B$ 被合并为一个连通块，且依然具有每条边被覆盖恰好一次的性质。

因此，我们只需要用这个方法将所有连通块合并为一棵树即可。

判环可以使用 DFS 或并查集。由于本题本来想出基础赛，而并查集不在大纲入门级算法范围内，标程采用 DFS 判环。

时间复杂度 $O(n+m)$。

```cpp
//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x, y, z) for(int x = (y); x <= (z); ++x)
#define per(x, y, z) for(int x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

template<int mod>
inline unsigned int down(unsigned int x) {
    return x >= mod ? x - mod : x;
}

template<int mod>
struct Modint {
    unsigned int x;
    Modint() = default;
    Modint(unsigned int x) : x(x) {}
    friend istream& operator>>(istream& in, Modint& a) {return in >> a.x;}
    friend ostream& operator<<(ostream& out, Modint a) {return out << a.x;}
    friend Modint operator+(Modint a, Modint b) {return down<mod>(a.x + b.x);}
    friend Modint operator-(Modint a, Modint b) {return down<mod>(a.x - b.x + mod);}
    friend Modint operator*(Modint a, Modint b) {return 1ULL * a.x * b.x % mod;}
    friend Modint operator/(Modint a, Modint b) {return a * ~b;}
    friend Modint operator^(Modint a, int b) {Modint ans = 1; for(; b; b >>= 1, a *= a) if(b & 1) ans *= a; return ans;}
    friend Modint operator~(Modint a) {return a ^ (mod - 2);}
    friend Modint operator-(Modint a) {return down<mod>(mod - a.x);}
    friend Modint& operator+=(Modint& a, Modint b) {return a = a + b;}
    friend Modint& operator-=(Modint& a, Modint b) {return a = a - b;}
    friend Modint& operator*=(Modint& a, Modint b) {return a = a * b;}
    friend Modint& operator/=(Modint& a, Modint b) {return a = a / b;}
    friend Modint& operator^=(Modint& a, int b) {return a = a ^ b;}
    friend Modint& operator++(Modint& a) {return a += 1;}
    friend Modint operator++(Modint& a, int) {Modint x = a; a += 1; return x;}
    friend Modint& operator--(Modint& a) {return a -= 1;}
    friend Modint operator--(Modint& a, int) {Modint x = a; a -= 1; return x;}
    friend bool operator==(Modint a, Modint b) {return a.x == b.x;}
    friend bool operator!=(Modint a, Modint b) {return !(a == b);}
};

const int N = 3e5 + 5;

int n, m, vis[N], blk[N];
vector<tuple<int, int>> G, e[N];

bool dfs(int u, int fr, int rt) {
    vis[u] = 1;
    blk[u] = rt;
    for(auto [v, id] : e[u]) {
        if(id != fr) {
            if(vis[v] == 0) {
                if(!dfs(v, id, rt)) {
                    return false;
                }
            }
            else if(vis[v] == 1) {
                return false;
            }
        }
    }
    vis[u] = 2;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    rep(i, 0, m - 1) {
        int s, t;
        cin >> s >> t;
        G.emplace_back(s, t);
        e[s].emplace_back(t, i);
        e[t].emplace_back(s, i);
    }
    rep(i, 1, n) {
        if(vis[i] == 0) {
            if(!dfs(i, -1, i)) {
                cout << "NO" << endl;
                return 0;
            }
        }
    }
    cout << "YES" << endl;
    auto [s, t] = G[0];
    int lst = s;
    rep(u, 1, n) {
        if(u == blk[u] && u != blk[s]) {
            cout << lst << " " << u << endl;
            lst = u;
        }
    }
    cout << lst << " " << t << endl;
    rep(i, 1, m - 1) {
        auto [u, v] = G[i];
        cout << u << " " << v << endl;
    }
    return 0;
}
```

---

## 作者：xxxalq (赞：5)

[题目链接](https://www.luogu.com.cn/problem/P11486)

# 思路分析：

判断无解很简单，维护一个并查集，遇到每一个点对 $(s,t)$ 就合并 $s$ 和 $t$，无解当且仅当合并之前 $s$ 和 $t$ 已经在一个并查集里了。

如果将 $s$ 和 $t$ 之间连一条边，那么显然同一个并查集里的所有点会构成一棵树，并且这棵树一定满足该联通的所有限制。可以说这棵树就是该连通块内的一种合法构造。

按照这样做就会得到若干棵点集无交的局部合法树，现在考虑如何把这些树合并起来。

参考样例一的解释图示很容易想到。可以让一个点属于多条路径，而且不影响答案，因为只需要满足每条边经过一次即可，每个点可以经过多次。

如果现在有两棵树，只需要取出第一棵树中的一对有直接连边的点 $u,v$ 以及另一棵树中的任意一点 $x$，删除 $u,v$ 间的这条边，然后分别向 $u,x$ 和 $x,v$ 之间连边。

按照上述操作讲每个连通块的树合并起来即可。

**一些代码实现中的提示**：

1. 可以先将所有边连起来，因为最多有 $n$ 个连通块，所以最多删除 $n$ 条边，删边时用 map 套 pair 标记一下即可。

2. 可以以其中的某一连通块为基准，将其他的连通块依次合并进来。

3. 合并时需要不断维护两个树中有直接连边的节点。

# 代码：

```cpp
//code by xxxalq
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn=300003;

int read(){//快读
	int x=0,f=1;
	char ch=getchar();
	while(ch>57||ch<48){
		if(ch==45){
			f=-1;
		}
		ch=getchar();
	}
	while(ch>=48&&ch<=57){
		x=(x<<1)+(x<<3)+(ch-48);
		ch=getchar();
	}
	return x*f;
}

map<pair<int,int>,bool>mp;//标记那条边被删了

int n,m,tot=1,hd[maxn],nxt[maxn<<1],to[maxn<<1],U,V,fa[maxn];//U,V维护两个树中有直接连边的节点

bool mk[maxn];

vector<pair<int,int> >a;//答案的边集

int find(int x){//并查集
	if(fa[x]==x){
		return x;
	}
	return fa[x]=find(fa[x]);
}

void add(int u,int v){//链式前向星
	tot++;
	to[tot]=v;
	nxt[tot]=hd[u];
	hd[u]=tot;
	return;
}

void dfs(int u,int father){//每个连通块内建树2加边
	for(int i=hd[u];i;i=nxt[i]){
		int v=to[i];
		if(v!=father){
			a.push_back(make_pair(u,v));
			if(U==0&&V==0){
				U=u,V=v;
			}
			dfs(v,u);			
		}
	}
	return;
}

int main(){
	int u,v;
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
	while(m--){
		u=read(),v=read();
		if(find(u)==find(v)){
			cout<<"No\n";//判误解
			return 0;
		}
		add(u,v);
		add(v,u);
		fa[find(u)]=find(v);
	}
	for(u=1;u<=n;u++){
		if(mk[find(u)]){
			continue;
		}
		mk[find(u)]=true;
		dfs(u,0);
	}
	for(int i=1;i<=n;i++){
		mk[i]=false;
	}
	int tmp=U;
	for(u=1;u<=n;u++){
		if(mk[find(u)]){
			continue;
		}
		mk[find(u)]=true;
		if(find(tmp)==find(u)){
			continue;
		}
		mp[make_pair(min(U,V),max(U,V))]=true;
		a.push_back(make_pair(U,find(u)));
		a.push_back(make_pair(find(u),V));
		U=find(u);
    //合并连通块
	}
	cout<<"Yes\n";
	for(int i=0;i<a.size();i++){
		u=a[i].first,v=a[i].second;
		if(mp[make_pair(min(u,v),max(u,v))]==false){
			cout<<u<<' '<<v<<'\n';//输出答案
		}
	}
	return 0;
}
```

---

## 作者：Naszt (赞：2)

# P11486 「Cfz Round 5」Mata rainen

## 观前提醒

因为这题是绿题，所以自然有很多种做法。  
我写题解是为了提供一种奇奇怪怪的**代码写法**。

这种代码写法不需要提前判断无解，也不需要最后再计算答案（某种意义）。  

## 思路分析

考虑构造：

直接连接前 $m-1$ 对点：$(s_i,t_i)$。  
最后一对点 $(s_m,t_m)$ 把其他的联通块串成树即可。

如果在过程中形成环，显然一定无解。

## 代码实现

我们可以使用 `stringstream`。  
`stringstream` 实际上是一个输入输出流。  

定义 `stringstream sout`，我们可以把 `sout` 当初 `cout` 来用，  
这样你输出的东就不会在屏幕上，而是在 `sout` 里。  
在最后的时候 `cout<<sout.str();` 即可。

这样我们遇到无解的情况就可以直接 `return puts("No"),0;` 了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,t,fa[300005];
stringstream sout;
int fd(int x){return (fa[x]==x?x:fa[x]=fd(fa[x]));}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)fa[i]=i;
	sout<<"Yes\n";
	for(int i=1;i!=m;i++){
		cin>>s>>t;
		if(fd(s)==fd(t))return puts("No"),0;
		sout<<s<<" "<<t<<"\n",fa[fa[s]]=fa[t];
	}
	cin>>s>>t;
	if(fd(s)==fd(t))return puts("No"),0;
	for(int i=1;i<=n;i++)
		if(fa[i]==i&&fa[s]!=i&&fa[t]!=i)
			sout<<s<<" "<<i<<"\n",fa[i]=fa[s],s=i;
	sout<<s<<" "<<t<<"\n";
	cout<<sout.str();
	return 0;
}
```

---

## 作者：_Kenma_ (赞：2)

## 前言

挺有意思的构造题，但是样例明示做法怎么说。

## 思路分析

不难发现如果给出的路径之间的点连边，如果有环一定无解。

我们断言：除此之外，所有的情况都一定有解。

考虑构造一种合法方案。

首先为了尽可能减少问题的复杂程度，我们希望给出的大部分路径都是树边。

因为图上没有环，所以给出的边一定构成一棵森林。

我们通过观察样例，不难得出一种构造：我们把其中一个连通块的一条边拉长，把其他连通块的根节点串起来，这样做一定是合法的。

就像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/bxoae83c.png)

其中标橙色的两个点是我们拉长的边，其他的边都是给出的路径。

在两个橙色点之间的点都是每个联通块的根。

## 代码实现

用并查集维护连通块就行。

注意不要把橙色点的连通块也串进去。

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> v;
int n,m,cnt,x[300005],y[300005];
int fa[300005];
void init(){
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
}
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	x=find(x);
	y=find(y);
	fa[x]=y;
}
signed main(){
	cin>>n>>m;
	init();
	for(int i=1;i<=m;i++){
		cin>>x[i]>>y[i];
		if(find(x[i])==find(y[i])){
			cout<<"No";
			return 0;
		}
		merge(x[i],y[i]);
	}
	for(int i=1;i<=n;i++){
		if(find(i)==i && i!=find(x[1]) && i!=find(y[1])) v.push_back(i);
	}
	cout<<"Yes"<<'\n';
	for(int i=2;i<=m;i++){
		cout<<x[i]<<' '<<y[i]<<'\n';
		cnt++;
	}
	if(v.size()) cnt++,cout<<x[1]<<' '<<v[0]<<'\n';
	else cout<<x[1]<<' '<<y[1]<<'\n';
	for(int i=0;i+1<v.size();i++){
		cnt++;
		cout<<v[i]<<' '<<v[i+1]<<'\n';
	}
	if(v.size()) cnt++,cout<<v[v.size()-1]<<' '<<y[1]<<'\n';
	//assert(cnt>=n-1);
	return 0;
}
```

---

## 作者：llamn (赞：1)

首先先考虑什么时候是无解的。数据无解当且仅当有环（重边也算作环）。树是没有环的，所以在树上把环压成链必然会导致路径重复。

现在我们可以想想怎么构造这棵树。下面默认数据中没有环。    
首先，当 $m = n-1$ 时，构造是最简单的：直接把这些边输出就可以了。这启示我们这样做：尽量把所有输入的点对变成最后树上的边。

但是，如果用点对直接建成树，可能会有一些点没有被加进树里。例如：

```
6 3
1 2
1 3
1 5
```
解决方法：我们发现，把一条边变成一条链也是可以的。那么这些没有加进树的点就可以直接塞进某一条边中：
```
Yes
1 2
1 3
1 4
4 6
6 5
```
这里在边 `1 5` 中塞进了点 `4` 和 `6`，变成了后三行。


下一个问题：如果输入的点对之间不连通怎么办？（就像样例1）   
参考刚才的方法。直接将后来的树的根塞进前面树的一条边中。

```cpp
#include <bits/stdc++.h> 
using namespace std;
namespace llamn{
int n,m,i,j,k,t1,t2; 

struct eggy{int to,lst;};
struct eggy e[600100];
int h[300100], cnt;
void add(int u, int w);

bitset <300100> xv;
void dfs(int d, int f); //判断环

bitset<300100> ved,t;
int ped, ansl[300100], ansr[300100];
void adde(int v); //在准备输出的树中的最新一条边中插入点v 
void dfs_ans(int d, int f); 

int s[300100], tp;

#define mk_pair(a,b) ((((long long)(a))<<30)+(b))
unordered_set<long long> qq;
int main()
{
    scanf("%d%d",&n,&m); 
    for (i = 1; i <= m; i++)
    {
    	scanf("%d%d",&t1,&t2);
	    t[t1] = 1, t[t2] = 1;
		add(t1,t2); add(t2,t1);
		
    	if (qq.find(mk_pair(t1,t2)) != qq.end()) //判断重边 
    	{
    		puts("No");
    		return 0;
		}qq.insert(mk_pair(t1,t2));
	}
	for (i = 1; i <= n; i++)
	{
		if (!xv[i]) dfs(i,0); //上下这两行没有关联 
		if (!t[i]) s[++tp] = i; //记录哪些点从未出现 
	}puts("Yes");
	for (i = 1; i <= n; i++)
	{
		if (!t[i]) continue;
		if (ved[i]) continue;
		if (ped) adde(i); //把新树的树根塞进上一棵树的边中 
		dfs_ans(i,-1);
	}for (i = 1; i <= tp; i++) //把没有出现的点塞进一条边中 
	{
		adde(s[i]);
	}
	for (i = 1; i <= ped; i++)
	{
		printf("%d %d\n",ansl[i], ansr[i]);
	}
    return 0;
}
void add(int u, int w)
{
	e[++cnt].to = w;
	e[cnt].lst = h[u];
	h[u] = cnt;
}void dfs(int d, int f)
{
	xv[d] = 1;
	for (int i = h[d]; i; i = e[i].lst)
	{
		if (e[i].to == f) continue;
		if (xv[e[i].to])
		{
			puts("No");
			exit(0);
		}dfs(e[i].to,d);
	}	
}void dfs_ans(int d, int f)
{
	ved[d] = 1;
	for (int i = h[d]; i; i = e[i].lst)
	{
		if(e[i].to == f) continue;
		ansl[++ped] = d; ansr[ped] = e[i].to;
		dfs_ans(e[i].to,d);
	}
}void adde(int v)
{
	t1 = ansr[ped];
	ansr[ped] = v;
	ansl[++ped] = v;
	ansr[ped] = t1;
}

}int main(){llamn::main();return 0;}

/*
元梦树上元梦果，元梦树下我放火
*/

```

---

## 作者：K_yuxiang_rose (赞：1)

先将输入的点对进行并查集，再构造一条链，以其中一个点对（这里我用的是第一个点对）的 $s_i$ 作为链的头部，以 $t_i$ 作为尾部，中间部分是处理好的每个集合的父亲，最后在链上的各个父亲与儿子连边即可。

需要判断无解情况，显然当边数恰好等于点数加一的是树，否则不是，那我们检查一下会不会输出 $n-1$ 条边即可判断这是不是树。

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[300005];
int s[300005];
int t[300005];
int f1[300005];
int find(int x)
{
	if(x==f[x]) return x;
	return f[x]=find(f[x]);
}
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1;i<=m;i++)
	{
		cin>>s[i]>>t[i];
		int a=find(s[i]),b=find(t[i]);
		f[a]=b;
	}
	int sum=m;
	f1[find(s[1])]=1;
	f1[find(t[1])]=1;
	for(int i=1;i<=n;i++)
	{
		if(!f1[find(i)])
		{
			sum++;
			f1[find(i)]=1;
		}
	}//模拟输出部分，统计输出的边的个数
	if(sum!=n-1)
	{
		cout<<"No";
		return 0;
	}
	memset(f1,0,sizeof(f1));//上面模拟了一遍，需要清空
	cout<<"Yes"<<endl;
	cout<<s[1]<<" ";
	f1[find(s[1])]=1;
	f1[find(t[1])]=1;
	for(int i=1;i<=n;i++)
	{
		if(!f1[find(i)])
		{
			cout<<i<<endl<<i<<" ";
			f1[find(i)]=1;
		}
	}//输出链
	cout<<t[1]<<endl;
	for(int i=2;i<=m;i++) cout<<s[i]<<" "<<t[i]<<endl;//将父亲和儿子连边
	return 0;
}
```

---

## 作者：_sin_ (赞：1)

先将题目提供的 $m$ 对点对连边，这样会连出来一个森林，如果不是森林必然无解。

考虑如何将这几个森林合并成一棵树。钦定一个连通块中最小的点为这个连通块的根，然后分类讨论两个连通块的合并。
1. 两个连通块的大小都大于一：\
   设两个连通块的根节点分别为 $x,y$。在 $y$ 中任意选择一条边，设这条边的两个端点是 $u,v$，断开这条边。再让 $x,u$ 和 $x,v$ 连一条边。这样显然满足要求。
3. 两个连通块的大小只有一个等于一：
   设两个连通块的根节点分别为 $x,y$。在 $x$ 中任意选择一条边，设这条边的两个端点是 $u,v$，断开这条边。再让 $y,u$ 和 $y,v$ 连一条边。这样显然满足要求。
5. 两个连通块大小都等于一：\
   因为 $m\ge 1$，所以这种情况是可以规避掉的。

连通块使用并查集维护一下即可，时间复杂度 $O(n\log n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e6+5;
int n,m,fa[N],hd[N],X[N],Y[N];
vector<pair<int,int> >ans,vec[N];
vector<int>tmp,sb[N];

int find(int x){return fa[x]=fa[x]==x?x:find(fa[x]);}
void merge(int x, int y){x=find(x),y=find(y);if(x<y)swap(x,y);fa[x]=y;}

bool cmp(int x,int y){return sb[x].size()>sb[y].size();}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=1;i<=m;i++){
        int x,y;scanf("%d%d",&x,&y);
        if(x>y)swap(x,y);X[i]=x,Y[i]=y;
        if(find(x)==find(y))return puts("No"),0;
        merge(x,y);
    }
    for(int i=1;i<=n;i++)sb[find(i)].emplace_back(i);
    for(int i=1;i<=n;i++)if(fa[i]==i){
        sort(sb[i].begin(),sb[i].end());
        for(int x:sb[i])hd[x]=sb[i][0];
    }
    for(int i=1;i<=m;i++)vec[hd[X[i]]].emplace_back(X[i],Y[i]);
    for(int i=1;i<=n;i++)if(hd[i]==i)tmp.emplace_back(i);
    sort(tmp.begin(),tmp.end(),cmp);
    for(int i=1;i<tmp.size();i++){
        int u=tmp[0],v=tmp[i];
        // printf("%d %d\n",i,v);
        if(vec[v].empty()){
            // printf("%d %d ",u,v);
            // printf("%d \n",vec[u][0].second);
            vec[u].emplace_back(v,vec[u][0].second);
            vec[u][0].second=v;
        }else{
            vec[v].emplace_back(u,vec[v][0].second);
            vec[v][0].second=u;
        }
    }
    for(int x:tmp)for(auto p:vec[x])ans.emplace_back(p);
    puts("Yes");
    for(auto p:ans)printf("%d %d\n",p.first,p.second);
    return 0;
}
```

---

## 作者：zhoumurui (赞：1)

### 题面展示

请判断是否存在一棵树满足如下条件。若存在，请尝试给出构造。

树中包含 $n$ 个结点，编号为 $1\sim n$。另外，给定 $m$ 个点对 $(s_i,t_i)$，要求树上这 $m$ 条从点 $s_i$ 到点 $t_i$ 的路径覆盖每条边**恰好**一次。

### 解题思路

考虑钦定给出的一个点对 $(s_1,t_1)$，将其他 $m-1$ 个点对直接用一条边连起来，产生若干个连通块，再用一条从 $s_1$ 到 $t_1$ 的链把产生的连通块全部连起来，这样显然是一棵树。

无解很容易判，如果把 $m$ 个点对都用一条边连起来，会产生环就是无解，否则显然有解。

下面的代码使用并查集。

### 核心代码展示

```cpp
int n,m;
int u[300005],v[300005];
int f[300005];
int find(int x){
    if (!f[x])return x;
    else return f[x]=find(f[x]);
}
signed main(){
    int n,m;
    cin>>n>>m;
    for (int i=1;i<=m;i++){
        cin>>u[i]>>v[i];
        int x=find(u[i]),y=find(v[i]);
        if (x==y){
            cout<<"No";
            return 0;
        }
        f[x]=y;
    }
    cout<<"Yes\n";
    for (int i=2;i<=m;i++){
        cout<<u[i]<<" "<<v[i]<<"\n";
    }
    int p=find(u[1]);
    vector<int> k;
    k.push_back(u[1]);
    for (int i=1;i<=n;i++){
        if (f[i]==0&&i!=p){
            k.push_back(i);
        }
    }
    k.push_back(v[1]);
    for (int i=0;i<k.size()-1;i++){
        cout<<k[i]<<" "<<k[i+1]<<"\n";
    }
    return 0;
}
```

---

## 作者：ChenZQ (赞：1)

我们可以先只考虑题目给的限制的几个点。

假设输入了两个点，那么我们就给这两个点建一条边。因为题目要求是树，所以如果出现环了自然就是无解。

而我们会发现，那些没有出现过的点，我们可以把他连续地插入到一条边中。

如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/7r4myu5l.png)

而建完边之后自然就是有多棵树，对于每两棵树，我们可以取以根的一个儿子为根的一颗子树和剩下的子树，分别接在另一个树的根上。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/1ktmb07b.png)

这样的话，原本树的两点之间能被覆盖，而根和被拆出来的儿子也可以多走一个点覆盖掉所有边。

不断地合并，然后就能合出最终答案了。

代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
bool f[500010];
map<int,map<int,int> > dl;
int n,m;
int h[N],e[N],ne[N],idx;
int fath[N],fa[N];
void add(int a,int b)
{
	e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}
void dfs(int a,int b)
{
	f[a]=1;
	for(int i=h[a];i!=-1;i=ne[i])
	{
		if(e[i]==b) continue;
		if(f[e[i]])
		{
			puts("No");
			exit(0);
		}
		f[e[i]]=1;
		dfs(e[i],a);
	}
}
vector<int> k;
int g[N],vis[N];
int tot=0;
vector<int> l;
void sky(int u,int v)
{
	fath[u]=v;
	vis[u]=1;
	if(u==v) l.push_back(u);
	for(int i=h[u];i!=-1;i=ne[i])
	{
		if(e[i]!=v) sky(e[i],u);
	}
}
bool shu[N];
int main()
{
	scanf("%d%d",&n,&m);
	if(m>n-1)
	{
		puts("No");
		return 0;
	}
	memset(h,-1,sizeof h);
	for(int i=1;i<=m;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		g[a]=1,g[b]=1;
		if(dl[a][b])
		{
			puts("No");
			return 0;
		}
		dl[a][b]=dl[b][a]=1;
		add(a,b);add(b,a);
	}
	for(int i=1;i<=n;i++)
	{
		if(!f[i]) dfs(i,i);
	}
	puts("Yes");
	for(int i=1;i<=n;i++)
	{
		if(!vis[i] && g[i]) sky(i,i);
		if(!g[i]) k.push_back(i);
	}
	int gl=k.size();
	int t=l.size();
	for(int i=0;i<t-1;i++)
	{
		int tou=l[i];
		int k=e[h[tou]];
		fath[k]=l[i+1],fath[tou]=l[i+1];
	}
	for(int i=0;i<gl-1;i++)
	{
		fath[k[i]]=k[i+1];
	}
	int mid;
	for(int i=1;i<=n;i++) if(fath[i]!=i && g[i]){
		mid=i;
		break;
	}
	if(gl>0)fath[k[gl-1]]=fath[mid];
	if(gl>0)fath[mid]=k[0];
	for(int i=1;i<=n;i++)
	{
		if(shu[i]) continue;
		int x=i;
		while(x!=fath[x] && !shu[x])
		{
			printf("%d %d\n",x,fath[x]);
			shu[x]=1;x=fath[x];
		}
	}

}
```

我使用了记录父亲节点的方式保存每棵树，然后通过每一个点往上走输出边，标记掉往上走的路径就不会有重复的，因为最多 $n$ 个点，每个点只会走一遍所以不会超时。

---

## 作者：DecemberFox (赞：0)

# P11486 「Cfz Round 5」Mata rainen 题解

## 题目分析

要求构造出一棵由 $n$ 个节点构成的树，使得其完全由给定的 $m$ 条自 $s_i$ 至 $t_i$ 的**最短的不重复路径**构成。

## 解法分析

先考虑仅满足这 $m$ 条路径存在，显然只需要按照 $m$ 条路径的要求构建成森林即可。其中，如果出现了几个路径的首尾相连形成了环，要么不能构成一棵树，要么就一定会经过原有的路径，因此该方案是不合法的，可以直接输出 `No`。 

但是题目要求必须为一棵树，因此需要想办法将森林合并成一棵树。

为了连接时不破坏原有的路径，可以将其中一棵树的任意一条边断开连接到另一棵树的任意一点上，这样对两棵树的路径都没有影响。需要注意的是，如果连接的一方中有一棵树为点，那么就只能断开另一棵树的边了。这样的操作方式适用于任何不全为单个点的树组成的森林。由于题中给出 $m\ge1$，因此此时一定有解，输出 `Yes`。

时间复杂度为 $O(n+m)$。

```cpp
#include<iostream>
#include<cstdio>
namespace io
{
	void read()
	{
		return;
	}
	template<typename nowtype,typename ...nexttype>
	void read(nowtype &now,nexttype &...next)
	{
		register char c=getchar();
		register int sign(1);
		now=0;
		while(!isdigit(c)){if(c=='-') sign=-1;c=getchar();}
		while(isdigit(c)){now=(now<<1)+(now<<3)+(c^48);c=getchar();}
		now*=sign;
		read(next...);
	}
	template<typename nowtype>
	void write(nowtype num,char end='\n')
	{
		register unsigned long long unum(0);
		if(num<0) putchar('-'),unum=-1ll*num;
		else unum=num;
		register int c[35],top(0);
		do c[top++]=unum%10,unum/=10;while(unum);
		while(top) putchar(c[--top]+48);
		putchar(end);
	}
	template<typename nowtype,typename ...nexttype>
	void write(nowtype num,char end,nexttype ...next)
	{
		register unsigned long long unum(0);
		if(num<0) putchar('-'),unum=-1ll*num;
		else unum=num;
		register int c[35],top(0);
		do c[top++]=unum%10,unum/=10;while(unum);
		while(top) putchar(c[--top]+48);
		putchar(end);
		write(next...);
	}
}
//以上为快读快写
using namespace io;
namespace SOLVE
{
	typedef long long ll;
	typedef unsigned long long ull;
	typedef __int128 lll;
	typedef unsigned __int128 ulll;
	const int const1=3e5+10;
	struct edges
	{
		int next,to;
	}edge[const1<<2];
	int Head[const1],f[const1],cnt;
	void AddEdge(int from,int to)
	{
		edge[++cnt].to=to;
		edge[cnt].next=Head[from];
		Head[from]=cnt;
	}
	void modify(int x,int y,int z)
	{
		int i;
		edge[Head[x]].to=z;
		for(i=Head[y];i;i=edge[i].next)
		{
			if(edge[i].to==x)
			{
				edge[i].to=z;
				break;
			}
		}
		AddEdge(z,x);
		AddEdge(z,y);
	}
	int find(int x)
	{
		if(x==f[x]) return x;
		return f[x]=find(f[x]);
	}
	void merge(int x,int y)
	{
		if(find(x)==find(y)) return;
		f[find(x)]=find(y);
	}
	void treeput(int x,int f)
	{
		int i;
		for(i=Head[x];i;i=edge[i].next)
		{
			if(edge[i].to==f) continue;
			write(x,' ',edge[i].to);
			treeput(edge[i].to,x);
		}
	}
	void solve()
	{
		int i,n,m,s,t,ts(0),lst;
		bool mt(false);
		read(n,m);
		for(i=1;i<=n;++i) f[i]=i;
		for(i=1;i<=m;++i)
		{
			read(s,t);
			if(!ts) ts=s;
			if(find(s)==find(t))
			{
				printf("No\n");
				return;
			}
			merge(s,t);
			AddEdge(s,t);
			AddEdge(t,s);
		}
		lst=find(ts);
		for(i=1;i<=n;++i)
		{
			if(i==ts) continue;
			if(find(i)!=lst)
			{
				if(!Head[i]) modify(ts,edge[Head[ts]].to,i);
				else modify(i,edge[Head[i]].to,find(lst));
				merge(i,lst);
			}
			lst=find(i);
		}
		printf("Yes\n");
		treeput(1,1);
	}
}
int main()
{
	SOLVE::solve();
	return 0;
}
```

---

## 作者：fish_love_cat (赞：0)

容易想到直接按照他给的限制进行连边。

显然此时如果出现了环那么无解。

否则我们会发现原图变成了若干个树。

我们知道目前连出的所有边都是合法的。接下来要做的就是使这张图联通。

那也就很简单了，找到一对限制，把边拆开，中间像串个糖葫芦那样把除了这个限制所在树外的所有的树任意取一个节点插进来即可。注意到所出现的新边全部被拆开来的这对限制给搞定了。

那么就做完了，因为要判个联通还要取点所以直接糊个并查集就行。

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>ve[300005];
int f[300005];
int find(int x){
    return(f[x]==x?x:f[x]=find(f[x]));
}
int xx,yy;
vector<int>flc;
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)f[i]=i;
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        xx=x,yy=y;
        if(xx>yy)swap(xx,yy);
        ve[x].push_back(y);
        ve[y].push_back(x);
        if(find(x)==find(y)){
            puts("No");
            return 0;
        }
        f[find(x)]=find(y);
    }
    puts("Yes");
    flc.push_back(xx);
    for(int i=1;i<=n;i++){
        if(i==f[i]&&f[i]!=find(xx)&&f[i]!=find(yy))
        flc.push_back(i);
        for(int j=0;j<ve[i].size();j++)
        if(ve[i][j]>i&&!(i==xx&&ve[i][j]==yy||i==yy&&ve[i][j]==xx))cout<<i<<' '<<ve[i][j]<<'\n';
    }
    flc.push_back(yy);
    for(int i=0;i<flc.size()-1;i++)
    cout<<flc[i]<<' '<<flc[i+1]<<'\n';
    return 0;
}
```

另外的，我觉得 T1 难度显著高于 T2，怎么回事呢。

---

