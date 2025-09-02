# Maximum Diameter Graph

## 题目描述

Graph constructive problems are back! This time the graph you are asked to build should match the following properties.

The graph is connected if and only if there exists a path between every pair of vertices.

The diameter (aka "longest shortest path") of a connected undirected graph is the maximum number of edges in the shortest path between any pair of its vertices.

The degree of a vertex is the number of edges incident to it.

Given a sequence of $ n $ integers $ a_1, a_2, \dots, a_n $ construct a connected undirected graph of $ n $ vertices such that:

- the graph contains no self-loops and no multiple edges;
- the degree $ d_i $ of the $ i $ -th vertex doesn't exceed $ a_i $ (i.e. $ d_i \le a_i $ );
- the diameter of the graph is maximum possible.

Output the resulting graph or report that no solution exists.

## 说明/提示

Here are the graphs for the first two example cases. Both have diameter of $ 2 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1082D/1b7fb105b3cde080c9710b0afa613b7d3cfaed06.png) $ d_1 = 1 \le a_1 = 2 $  $ d_2 = 2 \le a_2 = 2 $

 $ d_3 = 1 \le a_3 = 2 $

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1082D/a291014788668d36fcaf7a8e87cdf44a6c2682df.png) $ d_1 = 1 \le a_1 = 1 $  $ d_2 = 4 \le a_2 = 4 $

 $ d_3 = 1 \le a_3 = 1 $

 $ d_4 = 1 \le a_4 = 1 $

## 样例 #1

### 输入

```
3
2 2 2
```

### 输出

```
YES 2
2
1 2
2 3
```

## 样例 #2

### 输入

```
5
1 4 1 1 1
```

### 输出

```
YES 2
4
1 2
3 2
4 2
5 2
```

## 样例 #3

### 输入

```
3
1 1 1
```

### 输出

```
NO
```

# 题解

## 作者：米奇奇米 (赞：4)

## 题解-CF1082D Maximum Diameter Graph

* **题目大意**

就是让你构造一连通的无向图,使得每个点的度数$\leq a{i}$并且要使得直径足够长。

* $Solution$

**贪心：** 要让直径最长我们就要构造链，对于$2\leq ai$的点把他们加到链上去。然后把那些度为$1$的点粘到链上去。最后一点也是最值得注意的是：我们还可以让链变得更加长，就是把那$2$个度为一点（如果存在）粘到链的两端。这样就可以保证树的直径最长。正确性很显然。

对于那些不合法情况也就两种：

$1.$ 所有点的$ai$都为$1$

$2.$存在还没有被匹配到的点


剩下的就是细节问题了。

* $Code$

```cpp
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define For(i,a,b) for ( int i=(a);i<=(b);i++ )
#define Dow(i,a,b) for ( int i=(a);i>=(b);i-- )
#define FOR(i,t) for ( int i=head[t];i;i=E[i].nex )
//#define int long long
#define db double
#define mem(x,s) memset(x,s,sizeof(x))
#define cpy(x,s) memcpy(x,s,sizeof(x))
#define lowbit(x) x&(-x)
using namespace std;

namespace IO {
	#define gc getchar
	#define pt putchar
	inline int read() {
		int sum=0,ff=1; char ch=gc();
		while(!isdigit(ch)) {
			if(ch=='-') ff=-1;
			ch=gc();
		}
		while(isdigit(ch))
			sum=sum*10+(ch^48),ch=gc();
		return sum*ff;
	}

	inline void write(int x) {
		if(x<0) pt('-'),x=-x;
		if(x>9) write(x/10);
		pt(x%10|48);
	}

	inline void wln(int x) {
		write(x); pt('\n');
	}

	inline void wrn(int x) {
		write(x); pt(' ');
	}
}

using namespace IO;

const int N=505;
const int M=N*N;

int n,m,du[N],tmp[N],G[N][N];
int tot,ans,md,Du[N],e[M][3];
int head[N],cnt,rt,one[N],s;
struct nood {
	int nex,to,w;
};
nood E[M];

inline void jia(int u,int v) {
	E[++cnt]=(nood){head[u],v};
	head[u]=cnt;
}

inline void dfs(int u,int fa,int dep) {
	if(dep>md) {
		md=dep;
		rt=u;
	}
	FOR(i,u) {
		int v=E[i].to;
		if(v==fa) continue;
		dfs(v,u,dep+1);
	}
}

int main() {
	n=read();
	For(i,1,n) {
		int s=read();
		du[i]=s;
		if(s==1) one[++s]=i;
	}
	if(one[1]) tmp[1]=one[1];
	For(i,1,n) if(du[i]!=1) tmp[++tot]=i;
	if(one[2]) tmp[++tot]=one[2];
	if(!tot) return printf("NO\n"),0;
	For(i,1,tot-1) {
		e[++m][0]=tmp[i];
		e[m][1]=tmp[i+1];
		Du[tmp[i]]+=1;
		Du[tmp[i+1]]+=1;
		G[tmp[i]][tmp[i+1]]=G[tmp[i+1]][tmp[i]]=1;
	}
	For(i,1,tot) if(du[tmp[i]]>=2) {
		if(Du[tmp[i]]>=du[tmp[i]]) continue;
		For(j,1,n) 
			if(du[j]==1&&j!=tmp[i]&&!G[j][tmp[i]]) {
				if(Du[j]>=du[j]) continue;
				if(Du[tmp[i]]>=du[tmp[i]]) continue;
				e[++m][0]=tmp[i];
				e[m][1]=j;
				Du[tmp[i]]+=1;
				Du[j]+=1;
			}
	}
	For(i,1,n) if(!Du[i]) return printf("NO\n"),0;
	printf("YES ");
	For(i,1,m) jia(e[i][0],e[i][1]),jia(e[i][1],e[i][0]);
	dfs(1,0,0);
	md=0;
	dfs(rt,0,0);
	wln(md);
	wln(m);
	For(i,1,m) wrn(e[i][0]),wln(e[i][1]);
	return 0;
}
						
	
```


---

## 作者：Dilute (赞：3)

## 图论构造

_其实我一直搞不懂为什么$n$只有$500$……明明可以$O(n)$做的呀……_

我们瞪一眼题目，发现对于一张图，只有最短路树上的边才会对答案产生贡献，所以我们完全可以去掉所有多余的边，即仅仅建立一棵树，答案就是这棵树的直径

然后我们可以发现，如果不考虑度数限制，答案最优的情况是一条链，然后我们考虑从一条链的情况开始扩展

我们发现，对于度数限制$\geq 2$的节点，我们可以直接无脑将 它们连成一条链，像这样

```
O-----O-----O-----O-----O-----O
O     O     O
```
对于其他的节点，我们考虑一下如何将它们接到这条链上

如果直接连的话，可能长这样↓

```
O-----O-----O-----O-----O-----O
|     |
|  +--+--+
O  O     O
```

但是这样连显然不优，我们应该这么连↓
```
O-----O-----O-----O-----O-----O-----O
|     |
|     |
O     O
```
所以我们需要先把一个点加到链的最后，再从前面开始加

上代码～～

```cpp
#include<bits/stdc++.h>

#define ll long long
#define INF 2147483647

int inp(){
    char c = getchar();
    int neg = 1;
    while(c < '0' || c > '9'){
        if(c == '-')
            neg = -1;
        c = getchar();
    }
    int sum = 0;
    while(c >= '0' && c <= '9'){
        sum = sum * 10 + c - '0';
        c = getchar();
    }
    return sum * neg;
}

struct Node{
    int x;
    int res;
}s[1000];

int head[1000];
int nxt[2010];
int end[2010];
int cou = 0;
int dis[1000];
int d[1000];

void link(int a, int b){
    nxt[++cou] = head[a];
    head[a] = cou;
    end[cou] = b;
}

void dfs(int cur, int last){
    for(int x = head[cur]; x != -1; x = nxt[x]){
        if(end[x] == last)
            continue;
        dis[end[x]] = dis[cur] + 1;
        dfs(end[x], cur);
    }
}

int main(){
    memset(head, -1, sizeof(head));
    int n = inp();
    for(int i = 1; i <= n; i++){
        d[i] = inp();
        if(d[i] == 0){
            printf("NO");
            return 0;
        }
    }
    int c = 0;
    for(int i = 1; i <= n; i++){
        if(d[i] >= 2)
            s[++c] = (Node){i, d[i] - 2};
    }
    if(c == 0){
        printf("NO");
        return 0;
    }
    int cur = 1;
    s[1].res++;
    s[c].res++;
    // printf("%d\n", s[1].res);
    bool flg = false;
    for(int i = 1; i <= n; i++){
        if(d[i] < 2){
            if(!flg){
                link(i, s[c].x);
                link(s[c].x, i);
                s[c].res--;
                flg = true;
                continue;
            }
            while(s[cur].res <= 0 && cur <= c)
                cur++;
            if(cur > c){
                printf("NO");
                return 0;
            }
            s[cur].res--;
            link(i, s[cur].x);
            link(s[cur].x, i);
        }
    }
    for(int i = 1; i < c; i++){
        link(s[i].x, s[i + 1].x);
        link(s[i + 1].x, s[i].x);
    }
    dfs(1, -1);
    int max = 0;
    int maxk;
    for(int i = 1; i <= n; i++)
        if(dis[i] > max){
            max = dis[i];
            maxk = i;
        }
    dis[maxk] = 0;
    dfs(maxk, -1);
    int ans = 0;
    for(int i = 1; i <= n; i++){
        if(dis[i] > ans)
            ans = dis[i];
    }
    printf("YES %d\n", ans);
    printf("%d\n", n - 1);
    for(int i = 1; i <= n; i++)
        for(int x = head[i]; x != -1; x = nxt[x])
            if(end[x] > i)
                printf("%d %d\n", i, end[x]);
}
```

---

## 作者：lzyqwq (赞：2)

[**题目传送门**](https://www.luogu.com.cn/problem/CF1082D)

> - 给出一个数列 $a_1\sim a_n$，构造一个 $n$ 个点的**简单**无向连通图，满足：
>
>    - 第 $i$ 个点的度数 $d_i\le a_i$。
>
>    - 图上两点间的最短路尽可能长。
>
> - $n\le 500$。

首先，构造出来的肯定是一棵树（记为 $T$），可以考虑把环（记带环的图为 $C$）拆掉，度数的限制仍然满足。而且对于 $T$ 中任意两点 $u,v$ 间的最短路径（即唯一的路径）$dis_{T,u,v}$，这条路径一定在 $C$ 中出现，因此 $dis_{C,u,v}\le dis_{T,u,v}$，我们发现 $T$ 上两点间的最短路径一定是不劣的。

再考虑 $\forall i\in[1,n],a_i\ge 2$ 的情况，显然直接构造一条链最优。

推广到 $\sum\limits_{i=1}^n[a_i=1]\le 2$ 的情况，我们对于 $a_i\ge2$ 的点 $i$ 仍然构造一条链，然后把 $a_i=1$ 的点 $i$ 放在链的开头和结尾即可。

再考虑另一种情况，即 $\sum\limits_{i=1}^n[a_i=1]> 2$，我们还是构造一条链，并选两个 $a_i=1$ 的点放在链的开头和结尾，然后维护一个 $res_i$ 数组表示链上的点 $i$ 最多还能挂几个叶子，并把剩下的 $a_i=1$ 的点 $i$ 当作叶子结点往链上的某个 $res_i>0$ 点 $i$ 上挂，这一步可以用队列（双端队列亦可）维护，将链上的能挂叶子的点入队，每次取队头，如果这个点还能继续挂就再压回去。如果挂不了则无解，否则先构造出最长链，然后在挂点的过程中记录边即可。

时间、空间复杂度均为 $\mathcal{O}(n)$。$n\le 500$ 是为了给 SPJ 跑多源最短路的，并没有很大的参考价值。

笔者人比较傻，因此写的特别麻烦，但至少思路是清晰的。

[**评测记录**](https://codeforces.com/problemset/submission/1082/221815564)

```cpp
#include<bits/stdc++.h>
#define pii pair<int,int> 
#define fi first 
#define se second
#define mk make_pair
using namespace std;
const int N=505;
int a[N],n,ans,cnt,du1[3],st,ed;
vector<pii>g;
bool vis[N];
deque<pii>q;
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        if(a[i]==1){
            ++cnt;
        }
    }
    if(cnt<=2){
        cout<<"YES "<<n-1<<'\n'<<n-1<<'\n';
        if(!cnt){
            for(int i=1;i<n;++i){
                cout<<i<<' '<<i+1<<'\n';
            }
        }else if(cnt==1){
            for(int i=1,la=0;i<=n;++i){
                if(a[i]==1)du1[1]=i;
                else{
                    if(ed)g.emplace_back(ed,i);
                    else st=i;
                    ed=i;
                }
            }
            g.emplace_back(du1[1],st);
            for(pii i:g){
                cout<<i.fi<<' '<<i.se<<'\n';
            }
        }else{
            int tot=0;
            for(int i=1;i<=n;++i){
                if(a[i]==1)du1[++tot]=i;
                else{
                    if(ed)g.emplace_back(ed,i);
                    else st=i;
                    ed=i;
                }
            }
            g.emplace_back(du1[1],st),g.emplace_back(du1[2],ed);
            for(pii i:g){
                cout<<i.fi<<' '<<i.se<<'\n';
            }
        }
        return 0;
    }
    cnt=0;
    for(int i=1;i<=n;++i){
        if(a[i]==1&&cnt<2){
            a[i]=0;
            vis[i]=1;
            ++cnt;
            du1[cnt]=i;
            ++ans;
        }else if(a[i]!=1){
            a[i]-=2;
            if(!ed){
                st=i;
            }else{
                g.emplace_back(ed,i);
            }
            ed=i;
            if(a[i]){
                q.emplace_back(a[i],i);
            }
            vis[i]=1;
            ++ans;
        }
    }
    g.emplace_back(du1[1],st);
    g.emplace_back(ed,du1[2]);
    for(int i=1;i<=n;++i){
        if(!vis[i]&&a[i]==1){
            if(!q.size()){
                cout<<"NO";
                return 0;
            }
            pii u=q.front();
            q.pop_front();
            --u.fi;
            g.emplace_back(i,u.se);
            if(u.fi){
                q.emplace_front(u);
            }
        }
    }
    cout<<"YES "<<ans-1<<'\n'<<g.size()<<'\n';
    for(pii i:g){
        cout<<i.fi<<' '<<i.se<<'\n';
    }
    return 0;
}
```


---

## 作者：Rty123 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1082D)
### 题目大意
- 给出每个点的最大度数，构造出一张 $\mathcal n$ 个点的无向图
- 没有重边和自环，要求直径最长

### 解题思路
这道题一眼丁真为**贪心**，我们只需要构造出来一条最长的链来满足答案，这条链**两端**可以为度数 $\le1$ 的点（如果有的情况下），而链中其他点就必须为度数  $\ge2$ 的点。其余不在链中的点随意连接即可（在度数条件满足的情况下）。

不合法的情况有以下两种：
1. 没有度数 $\ge2$ 的点。
1. 在满足度数条件的情况下无法连接所有点

特判一下这两种情况即可

剩下的细节看~~我的屎山~~代码

### 代码展示
```cpp
#include<bits/stdc++.h>
#define PII pair<int,int> 
using namespace std;
int n;
int a[505],sum,k,s[3],b[505];
queue<PII> q;
int main(){
	cin>>n;
	int o=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[i]=a[i];
		if(a[i]==1&&k<2){//链两端的点 
			k++;
			s[k]=i;
			b[i]-=1;
		}
		if(a[i]>=2){//链中间的点 
			sum++;
			b[i]-=2;
			o+=b[i];
			if(b[i]>0)
			q.push(make_pair(i,b[i]));
		}
	}
	int h=0;
	for(int i=1;i<=n;i++){
		if(i==s[1]||i==s[2])continue;
		if(a[i]==1)h++;
	}
	if(sum==0||h>o){//特判两种不合法情况 
		cout<<"NO";
		return 0;
	}
	cout<<"YES"<<' ';
	int ans=sum+k-1;
	cout<<ans<<'\n';
	cout<<ans+h<<'\n';
	if(k==2){
		cout<<s[1]<<' ';
		for(int i=1;i<=n;i++){
			if(i==s[1]||i==s[2])continue;
			if(a[i]<2)continue;
			cout<<i<<'\n'<<i<<' ';
		} 
		cout<<s[2]<<'\n';//输出构造的最长链
		for(int i=1;i<=n;i++){
			if(i==s[1]||i==s[2])continue;
			if(a[i]<2){
				cout<<i<<' '<<q.front().first<<'\n';
				PII e=q.front();
				q.pop();
				e.second--;
				if(e.second==0)continue;
				q.push(e);
			}
		}//其余随意连接的点
	}
	if(k==1){//和上面一种情况类似 
		cout<<s[1]<<' ';
		for(int i=1;i<=n-1;i++){
			if(i==s[1])continue;
			if(a[i]<2)continue;
			cout<<i<<'\n'<<i<<' ';
		}
		cout<<n<<'\n';
		for(int i=1;i<=n;i++){
			if(i==s[1]||i==s[2])continue;
			if(a[i]<2){
				cout<<i<<' '<<q.front().first<<'\n';
				PII e=q.front();
				q.pop();
				e.second--;
				if(e.second==0)continue;
				q.push(e);
			}
		}
	}
	if(k==0){
		cout<<"1 ";
		for(int i=2;i<=n-1;i++){
			cout<<i<<'\n'<<i<<' ';
			if(a[i]<2)continue;
		}
		cout<<n<<'\n';
		for(int i=1;i<=n;i++){
			if(i==s[1]||i==s[2])continue;
			if(a[i]<2){
				cout<<i<<' '<<q.front().first<<'\n';
				PII e=q.front();
				q.pop();
				e.second--;
				if(e.second==0)continue;
				q.push(e);
			}
		}
	}
	return 0;
} 
```


---

## 作者：Sakura_梦瑶 (赞：2)

这是一个贪心,对答案产生贡献的是链,也就是说除了两端允许为入度为一的点,其余都要>=2,这样就可以区分出两种点；然后将1的点一个一个尝试加入到>=2的点,至于>=2的点因为要构成链,预处理的时候要注意。
```cpp
#include<bits/stdc++.h>
#define N 1<<23
using namespace std;
int n,cnt,l,e[N],v[N],r,p,c,tat,t;
struct q{int n,l;}a[N];
inline bool cmp(q s,q f){return s.l<f.l;}
int main(){
	cin>>n;for(int i=1;i<=n;i++)scanf("%d",&a[i].l),a[i].n=i;sort(a+1,a+1+n,cmp);
	for(int i=n;i;i--){if(a[i].l==1){l=i,tat=i+1;break;}else cnt+=(a[i].l-=2);}
	
	if(a[n].l!=1)a[l+1].l++,a[n].l++,cnt+=2;else cnt=1;
	if(cnt<l)cout<<"NO",exit(0);else cout<<"YES ";cout<<n-l+min(l,2)-1<<'\n';
	
	c=l+1,t=l;if(l!=0){
		if(t>=1)r=c,e[++p]=a[1].n,v[p]=a[n].n,l=2;
		if(t>=2)e[++p]=a[2].n,v[p]=a[tat].n,l=3,a[tat].l--;
		while(l<c){while(r<=n&&!a[r].l)r++;e[++p]=a[l++].n,v[p]=a[r].n,a[r].l--;}
	}
	for(int i=c;i<n;i++)e[++p]=a[i].n,v[p]=a[i+1].n;
	cout<<p<<'\n';for(int i=1;i<=p;i++)printf("%d %d\n",v[i],e[i]);
} 
```

---

## 作者：xiaofu15191 (赞：0)

非常好 $*1800$ 构造题使我的 duel 旋转。

下面我称题目中的数字 $a_i$ 为“最大度数”。

构造图的直径尽可能长，这让我们想到去构造一个基本形状为链的图（树）。下面我称这个链为“主链”。我们发现只有最大度数大于 $2$ 的点才可以成为“主链”上的点。

构造完“主链”之后，我们考虑将最大度数等于 $1$ 的点连接到“主链”的两端以增大答案。所以，我们要将最大度数最大的点放到“主链”的两端，然后再将剩下的点按照先两端后中间的顺序挂到“主链”上。

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
long long n,num[510],tmp_point,dis[510];
bool bz[510];
bool cmp(long long a,long long b)
{
	if(num[a]>num[b]) return true;
	else if(num[a]==num[b]&&a<b) return true;
	else return false;
}
vector<pair<long long,long long>>ans;
vector<long long>graph[510];
void dfs(long long now,long long fa)
{
	bz[now]=1;
	for(auto to:graph[now])
	{
		if(to==fa) continue;
		dis[to]=dis[now]+1;
		if(dis[to]>dis[tmp_point]) tmp_point=to;
		dfs(to,now);
	}
}
int main()
{
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++) scanf("%lld",&num[i]);
	vector<long long>v;
	for(long long i=1;i<=n;i++)
		if(num[i]>=2)
		{
			v.push_back(i);
			bz[i]=1;
		}
	if(v.empty())
	{
		printf("NO\n");
		return 0;
	}
	sort(v.begin(),v.end(),cmp);
	long long tmp=v[0];
	v.erase(v.begin());
	v.push_back(tmp);
	if(v.size()>1)
	{
		num[v[0]]--;
		num[v[v.size()-1]]--;
	}
	for(long long i=1;i<v.size();i++)
	{
		long long x=v[i-1],y=v[i];
		if(i!=v.size()-1) num[v[i]]-=2;
		ans.push_back(make_pair(x,y));
	}
	bool check0=0,check1=0;
	for(long long i=1;i<=n;i++)
		if(!bz[i])
		{
			if(check0==0&&num[v[0]]>0)
			{
				ans.push_back(make_pair(v[0],i));
				num[v[0]]--;
				bz[i]=1;
				check0=1;
			}
			else if(check1==0&&num[v[v.size()-1]]>0)
			{
				ans.push_back(make_pair(v[v.size()-1],i));
				num[v[v.size()-1]]--;
				bz[i]=1;
			}
			else
			{
				for(long long j=0;j<v.size();j++)
					if(num[v[j]]>0)
					{
						ans.push_back(make_pair(v[j],i));
						num[v[j]]--;
						bz[i]=1;
						break;
					}
				if(bz[i]==0)
				{
					printf("NO\n");
					return 0;
				}
			}
		}
	for(long long i=0;i<ans.size();i++)
	{
		graph[ans[i].first].push_back(ans[i].second);
		graph[ans[i].second].push_back(ans[i].first);
	}
	memset(bz,0,sizeof(bz));
	dfs(ans[0].first,0);
	for(long long i=1;i<=n;i++)
		if(!bz[i])
		{
			printf("NO\n");
			return 0;
		}
	dis[tmp_point]=0;
	printf("YES ");
	dfs(tmp_point,0);
	printf("%lld\n%lld\n",dis[tmp_point],(long long)(ans.size()));
	for(long long i=0;i<ans.size();i++)
		printf("%lld %lld\n",ans[i].first,ans[i].second);
}
```

---

