# Graph

## 题目背景

**hack 数据已添加，位于 Subtask#5，不计分。**


## 题目描述

有一张 $n$ 个点的图，每个点可以是**黑色**或**白色**的。

有 $m$ 条限制，第 $i$ 条限制会给定 $a_i,b_i,c_i$，表示 $a_i\Rightarrow b_i$ 需要有一条长度为 $c_i$ 的路径，路径可以重复经过某条边或点。

问是否存在一个若干条边权为 $1$ 有向边的图，满足：

- 满足上述 $m$ 个条件。
- 假如这张图有 $k$ 条边，则对于每个 $\forall 1\le i\le k$，设第 $i$ 条边是由 $u_i$ 指向 $v_i$ 的，那么 $u_i$ 的颜色与 $v_i$ 的不同。

## 说明/提示

**【样例解释】**

可以构造出

![](https://cdn.luogu.com.cn/upload/image_hosting/oz6rr27f.png)

以满足要求。



------------

**【数据范围】**

**本题采用捆绑测试。**
- Subtask #1（$5\text{pts}$）：$m=0$。
- Subtask #2（$20\text{pts}$）：$n\le 10$。
- Subtask #3（$25\text{pts}$）：$n\le 10^3$。
- Subtask #4（$50\text{pts}$）：无特殊限制。

对于 $100\%$ 的数据，$1\le T\le 10$，$1\le n\le 10^6$，$0\le m\le 10^6$，$1\le a_i,b_i\le n$，$0\le c_i\le 10^9$。

## 样例 #1

### 输入

```
1
5 4
1 3 4
4 2 7
4 4 0
5 2 1```

### 输出

```
Yes```

# 题解

## 作者：封禁用户 (赞：8)

显然，$c_i$ 为偶数时，$a_i$ 与 $b_i$ 颜色相同，否则不同。

因为只会在不同颜色的点之间连边，所以每一步走到的点一定与当前点颜色不同。

然后就做完了，并查集维护一下就行，感觉严格小于 T3。

---

## 作者：_zjzhe (赞：4)

这道题和 [P1955 [NOI2015] 程序自动分析](https://www.luogu.com.cn/problem/P1955) 很像

注意到题中给出 **路径可以重复经过某条边或点** 且 **边权为1**，我们让不同颜色的点全部连上边。则若一条限制中路径长为偶数，可以在一条边上反复走消耗长度，直到剩下长度为 2，此时一定回到了起点，再经任意一个另一颜色的点中转即可到达终点，且起点与终点为同一颜色；若长度为奇数，那么最后会剩下 1 的长度，只能走向另一颜色的点。所以根据路径长度奇偶性来判断两点是否为同一颜色即可，剩下就和程序自动分析一样了，先把相同颜色的点合并，然后再枚举颜色不同的点对，若出现矛盾就输出 `No`。

Tips：注意特判 $c=0$ 而 $a\ne b$ 的情况，遇到直接输出 `No`。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int T,n,m,fa[N];
vector<pair<int,int> > vec1,vec2;
int get(int x){
	if(fa[x]==x) return x;
	return fa[x]=get(fa[x]);
}
int main(){
	cin>>T;
	while(T--){
		vec1.clear();vec2.clear();
		cin>>n>>m;
		for(int i=1;i<=n;i++) fa[i]=i;
		for(int i=1;i<=m;i++){
			int a,b,c;cin>>a>>b>>c;
			if(c&1) vec1.push_back({a,b});
			else {
				if(c==0&&a!=b) {
					cout<<"No"<<'\n';
					goto nxt;
				}
				vec2.push_back({a,b});
			}
		}
		for(auto [a,b] : vec2) fa[get(a)]=get(b);
		for(auto [a,b] : vec1) {
			if(get(a)==get(b)){
				cout<<"No"<<'\n';
				goto nxt;
			}
		}
		cout<<"Yes"<<'\n';
		nxt:;
	}
	
	return 0;
}
```
感觉用点 `goto` 还挺方便的（

---

## 作者：covonant (赞：3)

并查集，与 [P1525](https://www.luogu.com.cn/problem/P1525) 类似，开两倍的 $fa$ 数组，$i$ 与 $i+n$ 互为“敌对”关系。

容易想到对 $c_i$ 进行分类讨论：
- $c_i$ 是偶数，此时 $a_i$ 与 $b_i$ 同色，将 $a_i$ 与 $b_i$ 合并，同时把 $a_{i+n}$ 与 $b_{i+n}$ 合并。
- $c_i$ 是奇数，此时 $a_i$ 与 $b_i$ 异色，将 $a_i$ 与 $b_{i+n}$ 合并，同时把 $a_{i+n}$ 与 $b_i$ 合并（敌人的敌人是朋友）。

一些注意点：
- 若每个点均同色，此时无解。
- 若 $c_i=0$  ，且 $a_i$ 与 $b_i$ 不相等，此时无解。

最后给出code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int fa[2000005];
int a[1000005],b[1000005],c[1000005];
int T;
int find(int x){
	if(fa[x]==x) return x;
	else return fa[x]=find(fa[x]);
}
void join(int x,int y){
	int t=find(x),k=find(y);
	if(t!=k) fa[t]=k;
}
bool check(int x,int y){
	int t=find(x),k=find(y);
	return t==k;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--){
		int n,m;
		cin>>n>>m;
		for(int i=1;i<=2*n;i++){//注意是2倍空间
			fa[i]=i;
		}
		int flag=0;
		for(int i=1;i<=m;i++){
			cin>>a[i]>>b[i]>>c[i];	
			if(a[i]!=b[i]&&c[i]==0){//特判
				flag=1;
				continue;
			}
			if(c[i]%2==0){//偶
				join(a[i],b[i]);
				join(a[i]+n,b[i]+n);
			}
			else{//奇
				join(a[i]+n,b[i]);
				join(a[i],b[i]+n);
			}
		}
		if(flag){
			cout<<"No\n";
			continue;
		}
		flag=0;
		for(int i=1;i<=n;i++){
			if(check(i,n+i)){//有无矛盾
				flag=1;
				break;
			}
		}
		if(flag){
			cout<<"No\n";
			continue;
		}
		flag=0;
		for(int i=2;i<=n;i++){
			if(find(i)!=find(1)){//特判
				flag=1;
			}
		}
		if(flag){
			cout<<"Yes\n";
		}else{
			cout<<"No\n";
		}
	}
	return 0;
}
```

---

## 作者：zxh923 (赞：2)

# P11640 Graph 题解

[题目传送门](https://www.luogu.com.cn/problem/P11640)

### 思路

注意到如果图中存在一个奇环，则存在两个点的颜色无法满足要求。换句话说，如果有两个要求同时要求两点之间有一条奇数和偶数长度的路径，就不合法。

这里的判断使用拓展域并查集即可。

同时还有几个特殊情况：

+ $n=1$ 时，若有一条边的边权不为 $0$，则不合法。

+ 存在一个 $i$ 使得 $a_i\ne b_i$ 时，若边权为 $0$，则不合法。

+ 最后发现所有点的颜色都相同时，不合法。

### 代码

```
#include<bits/stdc++.h>
#define int long long
#define N 2000005
#define pii pair<int,int>
#define x first
#define y second
#define pct __builtin_popcount
#define mod 998244353
#define pi acos(-1)
#define inf 2e18
#define eps 1e-8
using namespace std;
int T=1,n,m,fa[N];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void solve(int cs){
	cin>>n>>m;
	for(int i=1;i<=n*2;i++){
		fa[i]=i;
	}
	bool f=1;
	for(int i=1;i<=m;i++){
		int a,b,c;
		cin>>a>>b>>c;
		if(a!=b&&c==0)f=0;
		if(n==1&&c!=0)f=0;
		if(!f)continue;
		if(c%2==0){
			if(find(a+n)==find(b)||find(a)==find(b+n)){
				f=0;
				continue;
			}
			fa[find(a)]=find(b);
			fa[find(a+n)]=find(b+n);
		}
		else{
			if(find(a)==find(b)||find(a+n)==find(b+n)){
				f=0;
				continue;
			}
			fa[find(a+n)]=find(b);
			fa[find(a)]=find(b+n);
		}
	}
	if(n==1){
		if(f)cout<<"Yes\n";
		else cout<<"No\n";
		return;
	}
	int x=find(1);
	bool g=0;
	for(int i=1;i<=n;i++){
		if(find(i)!=x){
			g=1;
			break;
		}
	}
	f&=g;
	if(f)cout<<"Yes\n";
	else cout<<"No\n";
}
void solution(){
    /*
    nothing here
    */
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
//	init();
	cin>>T;
    for(int cs=1;cs<=T;cs++){
        solve(cs);
    }
    return 0;
}
```

---

## 作者：luogu_gza (赞：2)

看春晚的时候想来凑凑热闹，然后发现 T4 咋这么简单，是不是参赛的人菜了。

考虑黑白点实际上是二分图的左部点和右部点，我们可以构造图满足所有的左部点和右部点的点对都有两个方向的边各一条，可以注意到这样一定是不劣的。

观察：存在一条 $a_i \to b_i$ 长度为 $c_i$ 的路径，根据 $c_i \bmod 2$ 可以判定 $a_i$ 和 $b_i$ 是否在同一侧。

用并查集判定条件是否能够满足所有的限制即可。

---

## 作者：sbno333 (赞：1)

感谢 hack。

要求连边两端颜色不同，不难想到二分图。

当图是二分图二条件成立，否则不成立。

然后我们可以给二分图建满边，我们就只关心 $c_i$ 的奇偶性。

然后变成了给定 $u,v$，告诉你们他们是一个集合或不同集合，类似关押囚犯的做法，搞一个并查集，同一个集合直接合并，否则记录他和他不是一个集合，如果其中一个点已经记录了，那就敌人的敌人是朋友，没记录的和记录的不同集合点合并，然后只要操作过后这些记录的不同集合条件仍然成立，，就一定成立（不考虑细节）。

当然 $u=v$ 和 $c_i=0$ 要记得特判。

最后别忘了特判至少有两个不同集合。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int fa[1000009];
int getfa(int t){
	if(t==fa[t]){
		return t;
	}
	return fa[t]=getfa(fa[t]);
}
void merge(int u,int v){
	fa[getfa(u)]=getfa(v);
}
int bt[1000009];
void _main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		fa[i]=i,bt[i]=0;
	}
	bool fl;
	fl=0;
	while(m--){
		int u,v;
		cin>>u>>v;
		int rie;
		bool g;
		cin>>rie;
		g=(rie&1);
		if(rie==0&&(u!=v)){
			fl=1;
		}
		if(g){
			if(getfa(u)==getfa(v)){
				fl=1;
			}
			if(bt[u]){
				merge(bt[u],v);
			}else if(bt[v]){
				merge(bt[v],u);
			}else{
				bt[u]=v,bt[v]=u;
			}
		}else{
			merge(u,v);
		}
	}
	for(int i=1;i<=n;i++){
		if(bt[i]){
			if(getfa(i)==getfa(bt[i])){
				fl=1;
			}
		}
	}
	bool yq;
	yq=1;
	for(int i=2;i<=n;i++){
		if(getfa(i)!=getfa(1)){
			yq=0;
		}
	}
	fl|=yq; 
	cout<<(fl?"No":"Yes")<<endl;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		_main();
	}
	return 0;
}
```

---

## 作者：_O_v_O_ (赞：1)

我们令所有黑点向所有白点连边，白点向黑点连边。那么这样当一条路径长度为偶数时，两个点同色，否则异色。

也就是说，当 $c_i\bmod 2=0$ 时，两点同色，否则异色。

那么这个问题就变成了一个二分图判定，直接 dfs 即可。

注意特判 $c_i=0$ 的情况。

---

## 作者：xuyifei0302 (赞：0)

读完题我们就可以发现，所谓只能在不同颜色的点之间连边权为 $1$ 的边。所以若 $c_i$ 是偶数，则 $a_i$ 一定和 $b_i$ 同色。若 $c_i$ 是奇数，则 $a_i$ 一定和 $b_i$ 异色。

所以，我们会发现，这似乎可以直接用扩展域并查集，也就是种类并查集来维护。

然后，不知为什么，光荣 MLE。

所以，我们考虑先把异色关系的边记录下来，同色关系就直接合并为一个连通块。

然后判定应为异色的 $a_i$ 和 $b_i$ 是否在同一个连通块，若在同一个连通块，则不合法。

注意，若只有一个连通块，则所有 $c_i$ 必须为 $0$，否则不合法。而且，若 $c_i$ 为 $0$，则 $a_i$ 一定等于 $b_i$，否则也不合法。

下面是代码环节：


```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node {
	int u, v;
} edge[1000005];
int t, n, m, f[1000005], cnt, num, num1;
bool flag;
int get_father(int x) {
	return f[x] == x ? x : f[x] = get_father(f[x]);
}
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t --) {
		cin >> n >> m;
		for (int i = 1; i <= n; i ++) {
			f[i] = i;
		}
		flag = true;
		for (int i = 1; i <= m; i ++) {
			int x, y, z;
			cin >> x >> y >> z;
			if (z & 1) {
				edge[++cnt].u = x;
				edge[cnt].v = y;
			} else {
				int fx = get_father(x), fy = get_father(y);
				f[fx] = fy;
			}
			if (z == 0) {
				if (x != y) {
					flag = false;
				}
				num ++;
			}
		}
		for (int i = 1; i <= cnt; i ++) {
			int fx = get_father(edge[i].u), fy = get_father(edge[i].v);
			if (fx == fy) {
				flag = false;
			}
		}
		for (int i = 1; i <= n; i ++) {
			if (f[i] == i) {
				num1 ++;
			}
		}
		if (num1 == 1 && num != m) {
			flag = false;
		}
		num1 = 0;
		cnt = 0;
		num = 0;
		if (flag) {
			cout << "Yes\n";
		} else {
			cout << "No\n";
		}
	}
	return 0;
}
```

---

## 作者：Lele_Programmer (赞：0)

# P11640 题解

## 思路

在两个相邻的点走一个来回，则可以抵消掉长度 $2$ 的路径。

那么 $c$ 为偶数，则 $a,b$ 不相邻，$c$ 为奇数，则 $a,b$ 相邻。其实这里不一定相邻，但是为了判定是否有解，我们可以这样做。

相邻点颜色不同，这很容易想到染色法判定二分图。

但是这道题小细节比较多，比如 $c=0$，如果 $a \neq b$，显然无解。若 $a = b$ 且 $c \neq 0$，也显然无解。

真的只有这样吗？

不妨看看这组数据：

```cpp
1
4 3
1 2 2
2 3 2
3 4 2
```

以上这组数据不会出现上文所说的无解情况，但它的确是无解的。

因为每一组 $a,b (a \neq b)$ 合在一起恰好覆盖所有的点，并且 $c$ 都是不为 $0$ 的偶数，意思就是说要构造出一张 $n$ 个点的连通图，使相邻的点颜色不同，而 $n$ 个点的颜色又必须相同，这显然十分矛盾。

而如果所有点颜色相同但不必全部连成一个连通块，则依然有解。

所以这种特例可以用并查集做掉。

剩下的不多说啦，染色法判定二分图板子。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define TIMESTAMP cerr<<fixed<<setprecision(3)<<clock()*1.0/CLOCKS_PER_SEC<<"s"<<endl;
#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for (int i=(a);i<=(b);c)
#define _rrep(i,a,b) for (int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for (int i=(a);i>=(b);c)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)
#define _graph(i,u) for (int i=h[u];~i;i=ne[i])
#define rint register int
#define LL long long
#define i32 signed
#define i64 long long
#define i128 __int128
#define u32 unsigned
#define u64 unsigned long long
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef pair<double,double> pdd;

namespace IO {
    template<typename T> inline void read(T& x) {
        int s=1; char c=getchar(); x=0;
        while (!isdigit(c)) { if (c=='-') s=-1; c=getchar(); }
        while (isdigit(c)) x=x*10+(c-'0'),c=getchar();
        x*=s;
    }
    template<typename T> inline void write(T x) {
        if (x<0) putchar('-'),x=-x;
        if (x/10) write(x/10);
        putchar('0'+(x%10));
    }
    template<typename T> inline void writesp(T x) { write(x); putchar(' '); }
    template<typename T> inline void writeln(T x) { write(x); putchar(10); }
};

using namespace IO;

const int N=2000005;
const int M=4000005;

int T,n,m,ext;
int e[M],ne[M],h[N],tot;
int flag[N];
bool ok;
int p[N];

int find(int x) {
    if (p[x]==x) return p[x];
    else return p[x]=find(p[x]);
}

void add(int a,int b) {
    e[tot]=b,ne[tot]=h[a],h[a]=tot++;
}

void dfs(int u) {
    _graph(i,u) {
        if (flag[e[i]]==-1) {
            flag[e[i]]=flag[u]^1;
            dfs(e[i]);
        } else if (flag[e[i]]==flag[u]) {
            ok=false;
            return;
        }
        if (!ok) return;
    }
}

int main() {
    read(T);
    while (T--) {
        memset(h,-1,sizeof(h)); tot=ext=0;
        memset(flag,-1,sizeof(flag)); ok=true;
        read(n),read(m);
        _rep(i,1,n) p[i]=i;
        while (m--) {
            int a,b,c;
            read(a),read(b),read(c);
            if (a==b) {
                if (c&1) ok=false;
                continue;
            }
            if (a!=b && !c) ok=false;
            if (c&1) add(a,b),add(b,a);
            else p[find(a)]=find(b),++ext,add(a,n+ext),add(n+ext,a),add(b,n+ext),add(n+ext,b); 
        }
        bool allsame=true;
        _rep(i,2,n) {
            if (find(i)!=find(1)) {
                allsame=false;
                break;
            }
        }
        if (allsame && n!=1) {
            puts("No");
            continue;
        }
        _rep(i,1,n) {
            if (!ok) break;
            if (!~flag[i]) flag[i]=0,dfs(i);
        }
        if (!ok) puts("No");
        else puts("Yes");
    }
    return 0;
}
```

---

