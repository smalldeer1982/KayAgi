# Non Prime Tree

## 题目描述

给你一棵拥有 $n$ 个顶点的树。

你的任务是构造一个包含 $n$ 个不同整数的数组，这些整数从 $1$ 到 $2 \cdot n$ 分别取值。同时要求对于树中的任意一条边 $u_i \leftrightarrow v_i$，对应的数组元素差值 $|a_{u_i} - a_{v_i}|$ 不是质数。

请你找出任意一个符合以上条件的数组，如果不存在这样的数组，请输出 $-1$。

## 说明/提示

如下图所示的答案中，用对应数组 $a$ 的元素替代了顶点编号：

第一组数据的树结构 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2040D/d6a56c20ebd42ea20ac170d596c01c0583a1b831.png)  
第二组数据的树结构 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2040D/8328682bcf4d0da5fcbe8de4a0054b43d22d093e.png)

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
5
1 2
2 3
2 4
3 5
7
1 2
1 3
2 4
3 5
3 6
3 7```

### 输出

```
2 10 1 6 5 
8 7 12 1 4 6 3```

# 题解

## 作者：lfxxx (赞：5)

对原树黑白染色，假若存在黑点 $s$ 与白点 $t$ 不相邻，按照其余黑点，$s$，$t$，其余白点的顺序给所有点赋值为 $2,4,6,\cdots,2 \times n$，由于保证了 $2 \times i,2 \times (i-1)$ 不相邻，所以是对的。

假若不存在不相邻异色点，说明图上最长链长度小于等于 $3$，图一定是一个菊花图，考虑给菊花图的中心赋权为 $2$，四周点赋权为 $1,6,8,\cdots,2 \times n$ 即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+114;
int n;
vector<int> E[maxn];
int ans[maxn];
vector<int> vec[maxn];
int col[maxn];
void dfs(int u,int cl,int lst){
    vec[cl].push_back(u);
    col[u]=cl;
    for(int v:E[u]){
        if(v!=lst) dfs(v,cl^1,u);
    }
}
void work(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        if(E[i].size()==n-1){
            ans[i]=1;
            ans[E[i][0]]=0;
            for(int j=1;j<E[i].size();j++){
                ans[E[i][j]]=j+2;
            }
            for(int j=1;j<=n;j++) cout<<(ans[j]==0?1:2*ans[j])<<' ';
            cout<<'\n';
            for(int j=1;j<=n;j++) E[j].clear();
            return ;
        }
    }
    dfs(1,0,0);
    for(int u=1;u<=n;u++){
        for(int v:E[u]){
            if(E[u].size()>=2&&E[v].size()>=2){
                int s=(E[u][0]==v?E[u][1]:E[u][0]);
                int t=(E[v][0]==u?E[v][1]:E[v][0]);
                if(col[s]==1) swap(s,t);
                int tot=0;
                while(vec[0].size()>0){
                    if(vec[0].back()!=s) ans[vec[0].back()]=++tot;
                    vec[0].pop_back();
                }
                ans[s]=++tot;
                ans[t]=++tot;
                while(vec[1].size()>0){
                    if(vec[1].back()!=t) ans[vec[1].back()]=++tot;
                    vec[1].pop_back();
                }
                for(int j=1;j<=n;j++) cout<<ans[j]*2<<' ';
                cout<<'\n';
                vec[0].clear();
                vec[1].clear();
                for(int j=1;j<=n;j++) E[j].clear();
                return ;
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}


```

---

## 作者：naromil (赞：5)

# CF2040D Non Prime Tree #

如果相邻的点之间的绝对值差必须为非质数，我们不难想到 $2$ 以外的偶数和 $1$，结合所有权值不能超过 $2n$，于是我们有个初步的想法就是为每个点赋值每个偶数，然后找到一个顺序使得没有相邻的点连着赋值。

那么我们就可以先将点按深度分类，然后不难发现如果总深度 $\ge 5$，就可以先遍历每个奇数深度行，然后遍历每个偶数深度行，对每行的所有点依次赋值每个偶数，然后就解决了。如果总深度 $=1$，答案直接输出 $1$ 即可。

对于剩下的深度，我们发现无论怎么遍历都会有两行相邻。于是我们不难想到可以将一个叶子作为根，然后 $1$，$2$ 行就都将只有一个点了。然后我们就可以对总深度分类讨论，解决剩下的深度。

- 树深度 $=2$，先对 $1$，$2$ 层依次赋偶数。
- 树深度 $=3$，先对 $3$，$1$，$2$ 层依次赋偶数。
- 树深度 $=4$，先对 $4$，$2$，$1$，$3$ 层依次赋偶数。

然后由于 $1$，$2$ 层各只有一个点，且它们差值为 $2$，我们直接将根节点 $+ 1$ 或 $- 1$，使得差值为 $1$，就解决了。


```cpp
#include<bits/stdc++.h>
#define emp emplace_back
using namespace std;
using ll=long long;
const int kn=2e5+25;
int n,dep[kn],a[kn],rot,maxdep;
vector<int> c[kn];
void dfs(int u,int b){
	rot=u;
	dep[u]=dep[b]+1;
	for(auto v: c[u]){
		if(b==v) continue;
		dfs(v,u);
	}
}
vector<int> fl[kn];
inline void _solv(){
	cin>>n;
	maxdep=rot=0;
	for(int i=1;i<=n;++i){ c[i].clear(); fl[i].clear(); }
	for(int i=2,x,y;i<=n;++i){ cin>>x>>y; c[x].emp(y); c[y].emp(x); }
	dfs(1,0); dfs(rot,0);
	for(int i=1;i<=n;++i){ fl[dep[i]].emp(i); maxdep=max(maxdep,dep[i]); }
	int cnt=0;
	if(maxdep==1){ printf("1\n"); return; }
	else if(maxdep==2){ printf("1 2\n"); return; }
	else if(maxdep==3){
        for(auto cr: fl[3]) a[cr]=(cnt+=2);
	    a[fl[1][0]]=(cnt+=3);
	    cnt=a[fl[2][0]]=++cnt;
	}
	else if(maxdep==4){
        for(auto cr: fl[4]) a[cr]=(cnt+=2);
        a[fl[2][0]]=(cnt+=2);
        a[fl[1][0]]=(cnt+=1);
        ++cnt;
        for(auto cr: fl[3]) a[cr]=(cnt+=2);
	}
	else{
        for(int i=1;i<=maxdep;i+=2) for(auto cr: fl[i]) a[cr]=(cnt+=2);
        for(int i=2;i<=maxdep;i+=2) for(auto cr: fl[i]) a[cr]=(cnt+=2);
	}
	for(int i=1;i<=n;++i){ printf("%d ",a[i]); }
	printf("\n");
}
signed main(){
	cin.tie(0)->ios::sync_with_stdio(false);
	int T; cin>>T;
	while(T--) _solv();
	return 0;
}

```

---

## 作者：bsdsdb (赞：4)

题意：给定一棵树，你需要为每个点赋一个 $[1,2n]$ 之间的点权，要求点权之间两两不同，且相邻的点的点权之差非质数。

考虑如下构造：

```cpp
ll st = 1;
void srh(ll x, ll pr) {
	ans[x] = st++;
	for (ll i : e[x]) {
		if (i == pr) {
			continue;
		}
		while (st - ans[x] != 1 && (((st - ans[x]) % 2) || st - ans[x] == 2)) {
			++st;
		} // 将 st 赋为比当前所有点权都大的，合法的（与 x 权值差 1，或奇偶性相同），x 的下一个子节点的可能的权值
		srh(i, x);
	}
}
```

然后证明这种构造能让所有点的权值落在 $[1,2n]$ 内。考虑其充分条件：令 $\mathrm{subv}_u:=\{\mathrm{val}_v\mid v\ \text{is in the subtree of}\ u\}$，则有 $\forall u\in V:\exist k\in\mathbb{N}:\mathrm{subv}_u\subseteq[k,k+2(\mathrm{sz}_u-1)]$，然后对这个条件进行归纳证明。首先，如果一个节点是叶子，那么显然成立；如果不是，令这个点 $u$ 的权值为 $v$，$s_{u,i}$ 表示节点 $u$ 的第 $i$ 个子节点，则 $\mathrm{subv}_{s_{u,1}}\subseteq[v+1,v-1+2\mathrm{sz}_{s_{u,1}}]$。如果 $u$ 只有一个儿子，那么命题显然成立，下文讨论 $u$ 不只有一个儿子的情况。如果 $\mathrm{sz}_{s_{u,1}}=1$，那么 $\mathrm{val}_{s_{u,2}}=v+4=\mathrm{val}_{s_{u,1}}+2\mathrm{sz}_{s_{u,1}}+1$，否则 $\mathrm{val}_{s_{u,2}}=\min\{x\mid x>\max\mathrm{subv}_{s_{u,1}}\land (x-v)\text{ not prime}\}\overset{\mathrm{val}_{s_{u,2}}\equiv v\pmod 2}{\le}\max\mathrm{subv}_{s_{u,1}}+2\le \mathrm{val}_{s_{u,1}}+2(\mathrm{sz}_{s_{u,1}}-1)+2=\mathrm{val}_{s_{u,1}}+2\mathrm{sz}_{s_{u,1}}$。类似地，我们有 $\forall i>1:\mathrm{val}_{s_{u,i}}\le\mathrm{val}_{s_{u,i-1}}+2\mathrm{sz}_{s_{u,i-1}}$，也即 $\mathrm{val}_{s_{u,i}}\le v+2+2\sum_{j=1}^{i-1}\mathrm{sz}_{s_{u,j}}$。设 $u$ 有 $c$ 个儿子，则 $\max\mathrm{subv}_u=\max\mathrm{subv}_{s_{u,c}}=\mathrm{val}_{s_{u,c}}+2\mathrm{sz}_{s_{u,c}}-2\le v+2+2\sum_{j=1}^{c}\mathrm{sz}_{s_{u,j}}-2=v+2\mathrm{sz}_u-2$，原命题得证。

Q：能不能说人话

A：就是先证明叶子肯定可以，然后设两个相邻子树的值域分别为 $[a,b],[c,d]$，那么可证 $c-b\le 3$，取等当且仅当 $[a,b]$ 是第一个子树，且只有一个节点，此时 $a=b=v+1,c=v+4$。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
// using namespace __gnu_pbds;
// tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>T;
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef long double ldb;
//#define umap unordered_map
#define umap __gnu_pbds::cc_hash_table
#define mkp make_pair
#define prque priority_queue
#define emp emplace
#define empb emplace_back
#define empf emplace_front
random_device rndv;
mt19937 rd(rndv());
const ll inf = 0x3f3f3f3f3f3f3f3fll;
const ldb eps = 1e-8;
const vector<ll> millerrabin = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
inline void enter(){putchar('\n');}
inline void space(){putchar(' ');}
inline ll readll(){ll ret=0,k=1;char c;do{c=getchar();if(c=='-'){k=-1;}}while(('0'>c)|('9'<c));do{ret=(ret<<3)+(ret<<1)+c-48;c=getchar();}while(('0'<=c)&(c<='9'));return ret*k;}
inline void read(ll&x){x=readll();}
inline char readchar(){char ret;do{ret=getchar();}while(ret<=32);return ret;}
inline void read(char&x){x=readchar();}
inline string readstr(){string ret;char c;do{c=getchar();}while(c<=32);do{ret+=c;c=getchar();}while((c>32)&(c!=EOF));return ret;}
inline void read(string&x){x=readstr();}
inline void write(ll x){if(!x){putchar('0');return;}if(x<0){putchar('-');x*=-1;}char op[20]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){putchar(op[cur--]);}}
inline ostream& operator<<(ostream& out, __int128 x){if(!x){out<<"0";return out;}if(x<0){out<<"-";x*=-1;}char op[40]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){out<<op[cur--];}return out;}
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const ll MAXN = 2e5 + 5;

ll n, st, ans[MAXN]; 
vector<ll> e[MAXN];

void srh(ll x, ll pr) {
	ans[x] = st++;
	for (ll i : e[x]) {
		if (i == pr) {
			continue;
		}
		while (st - ans[x] != 1 && (((st - ans[x]) & 1) || st - ans[x] == 2)) {
			++st;
		}
		srh(i, x);
	}
}

void init() {
	st = 0;
	fill(ans, ans + n + 1, 0);
	for (ll i = 1; i <= n; ++i) {
		e[i].clear();
	}
}
int mian() {
	read(n);
	for (ll i = 1; i < n; ++i) {
		ll u, v;
		read(u), read(v);
		e[u].empb(v), e[v].empb(u);
	}
	st = 1;
	srh(1, 0);
	for (ll i = 1; i <= n; ++i) {
		write(ans[i]), space();
	}
	enter();
	return 0;
}

int main() {
	ll T;
	read(T);
	while (T--) {
		init();
		mian();
	}
	return 0;
}

;             ;;;;;;;;          ;
;                   ;          ; ;
;                  ;          ;   ;
;                 ;          ;     ;
;                ;          ;;;;;;;;;
;               ;          ;         ;
;              ;          ;           ;
;;;;;;;;;;;   ;;;;;;;;   ;             ;

   ;                        ;
  ;                          ;
 ;                            ;
;                              ;
;                              ;
;                              ;
 ;                            ;
  ;         ;;          ;;   ;
   ;        ;;          ;;  ;
```

---

## 作者：cancan1234 (赞：2)

很好的乱搞题，使我罚时 $+1$，爱来自 Codeforces。

赛时胡了个贪心，莫名其妙过了，第二天中午证出来了它是对的。

考虑一个非常自然的贪心。假设现在已经构造出来了一个大小为 $sz - 1$ 的合法连通块，然后我们要往里面加入一个与这个连通块相邻的点 $u$。

维护一个集合 $s$ 表示当前还没有用到的数。先向 $s$ 中加入 $2sz$ 和 $2sz - 1$ 这两个数。然后**从大到小**遍历 $s$，将第一个合法的元素作为 $u$ 的权值，然后删除这个数。

下面来证明一下在遍历 $s$ 的时候最多访问 $O(1)$ 个数就会找到解。

设 $u$ 与已经构造好的连通块中的点 $v$ 有一条连边，加入点 $u$ 后连通块大小为 $sz$，分两种情况讨论：

- $a_{v} = 2sz - 2$ 或 $a_{v} = 2sz - 3$

  此时大于 $a_{v}$ 的所有数必然都没有被加入。将权值设为 $a_{v} + 1$ 即可满足条件。

- 其他情况。

  这种情况下 $2sz$ 和 $2sz - 1$ 中会有一个数和 $a_{v}$ 奇偶性相同，且差值大于 $2$。则 $2sz$ 和 $2sz - 1$ 中必定存在满足条件的数。

综上，只需要访问最大的 $O(1)$ 个未被选择的数即可满足条件。并且从这个构造也可以看出来本题是**一定有解**的。

code:

```cpp
set <int , greater <int> > s;
void dfs(int u , int fa){
    siz++;
    s.insert(siz * 2);
    s.insert(siz * 2 - 1);
    for (auto x : s){
        if (isp[abs(ans[fa] - x)]){
            ans[u] = x;
            break;
        }
    }
    s.erase(ans[u]);
    for (int i = head[u];i;i = e[i].nxt){
        int to = e[i].to;
        if (to != fa)dfs(to , u);
    }
}
```

---

## 作者：BigSmall_En (赞：2)

# CF992Div2 D-solution

> 给定一个 $n$ 个节点的树，你可以不重复地给树的节点填 $1\sim 2n$ 之间的数，求一种构造方案，使得每两个相邻的节点上的数之差的绝对值为合数。

我们规定每次填的数只会变大（就是在以某种方法遍历的时候后面的数一定比前面的数大）。现在我们假设填到了 $u$ 节点，$u$ 节点填的数是 $val_u$，$u$ 的儿子为 $v_0,v_1,v_2,\dots$，其中 $v_0$ 是~~长儿子~~任意一个儿子。

现在我们**归纳证明**，如果每个 $v$ 子树内最大的数**小于** $val_v+siz_v\times 2 -1$，则存在一种构造方案，使得 $u$ 子树内最大的数**小于** $val_u+siz_u\times 2-1$。这样做下去根节点 $1$ 的子树内最大的数小于 $n\times 2$，满足题意。

如果 $siz_u=1$，即 $u$ 没有儿子，显然满足条件。

------

我们填 $val_{v_0}=val_{u}+1$，下一个子树还能填的数是 $x=val_{v_0}+siz_{v_0}\times 2-1=val_{u}+siz_{v_0}\times 2$

1. 如果 $siz_{v_0}\neq 1$。

   显然 $x-val_u=siz_{v_0}\times 2$ 是一个合数，我们直接填 $val_{v_1}=x$。则填完后还能从 $x'=val_{v_1}+siz_{v_1}\times 2-1 =val_u+(siz_{v_0}+siz_{v_1})\times 2-1$ 填下一个子树，我们填 $val_{v_2}=x'+1$ 即可满足合数条件。执行这样的操作，我们可以保证填完所有子树后，还能填的数是 $val_u+\sum siz_v\times 2-1<val_u+siz_u\times 2-1$，成立。

2. 如果 $siz_{v_0}=1$。

   - 如果 $siz_u=2$，即 $u$ 只有这一个子树，显然 $val_u+1<val_u+siz_u\times 2-1$。 

   - 否则填 $val_{v_1}=val_u+4$，那么接下来能填的数 $x'=val_u+4+siz_{v_1}\times 2-1=val_u+(siz_{v_0}+siz_{v_1})\times 2+1$，于是我们填 $val_{v_2}=x’+1$ 即可满足合数条件。执行这样的操作，我们可以保证填完所有子树后，还能填的数是 $val_{u}+\sum siz_v \times 2+1=val_u+siz_u\times 2-1$，成立。

于是就得证了。

------

所以只要一个 $val_v=val_u+1$，剩下的 $u$ 的儿子找一个最小的 $k>1$，填 $val_u+2k$ 大于目前已填的数即可。

我写代码的时候是用长链填连续的数写的，稍微麻烦一点。主要还是证明要严格比较费脑子。

下面的代码是上面的做法。

```cpp 
#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int>ttfa;
typedef long long ll;

const int N=200005;
int Test;
int n,tot=0,ans[N];

vector<int>tar[N];

void dfs(int u,int f){
	bool flag=0;
	ans[u]=++tot;
	for(auto v:tar[u]){
		if(v==f)continue;
		if(!flag){
			dfs(v,u);
			flag=1;
			continue;
		}
		if(tot+1-ans[u]==2)tot=ans[u]+3;
		else if((tot+1-ans[u])%2==1)++tot;
		dfs(v,u);
	}
}

int main(){
	scanf("%d",&Test);
	while(Test--){
		scanf("%d",&n);tot=0;
		for(int i=1;i<=n;++i)
			tar[i].clear();
		for(int i=1;i<n;++i){
			int u,v;scanf("%d%d",&u,&v);
			tar[u].push_back(v);
			tar[v].push_back(u);
		}
		dfs(1,0);
		for(int i=1;i<=n;++i)
			printf("%d ",ans[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：OoXiao_QioO (赞：2)

我们充分发扬人类智慧：注意到 $1$ 到 $2n$ 中合数的密度远远大于素数的密度，而数据范围又不大，所以考虑随机化。

具体地，先预处理出素数表，然后先给根节点砸个数上去，再依次 dfs，对于每个节点随机填数，直到满足条件，还是比较好想的。正确性显然，速度上也不劣。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ine long long
mt19937 rnd(time(0));
bool is_prime[1000001];
int prime[1000010],cnt;
void work(int n)
{
	is_prime[1] = 1;
	int i,j;
	for(i=2;i<=n;i++)
	{
		if(is_prime[i]==0)
			prime[++cnt]=i;
		for(j=1;j<=cnt&&i*prime[j]<=n;j++)
		{
			is_prime[i*prime[j]] = 1;
			if(i%prime[j]==0)
				break;
		}
	}
}
map<int,int> mp;
vector<int> e[1000001];
int T;
int n;
int a[1000001];
void dfs(int u,int fa)
{
	vector<int> now;
	for(auto i:e[u])
	{
		if(i!=fa&&!a[i])
		{
			int times;
			now.push_back(i);
			while(1)
			{
				int k = rnd()%(2*n)+1;
				if(is_prime[abs(k-a[u])]&&!mp[k])
				{
					mp[k] = 1;
					a[i] = k;
					break;
				}				
			}
			if(!a[i])
			{
				int j;
				for(j=2*n;j>=1;j--)
				{
					if(is_prime[abs(j-a[u])]&&!mp[j])
					{
						mp[j] = 1;
						a[i] = j;
						break; 
					}
				}
			}
		}
	}
	for(auto i:now)
		dfs(i,u);
}
void solve()
{
	srand(time(0));
	cin>>n;
	int i;
	for(i=1;i<=n*2;i++)
		e[i].clear(),a[i] = 0;
	for(i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	mp.clear(); 
	a[1] = rnd()%(2*n)+1;
	mp[a[1]] = 1;
	dfs(1,0);
	for(i=1;i<=n;i++)
		cout<<a[i]<<' ';
	cout<<endl;
}
int main()
{
	work(1000000);
	cin>>T;
	while(T--)
		solve(); 
	return 0;
}
```

---

## 作者：hgcnxn (赞：2)

## CF2040D Non Prime Tree题解

### 前言

本题解与 [lfxxx](https://www.luogu.com.cn/user/520748) 的题解思路相同，可看做更详细的版本。

### 题目大意

给定一棵有 $n$ 个节点的树，你要给这棵树上的每一个点填上一个权值 $v$，满足：

- $\forall\ 1\le i\le n$，$1\le v_i\le 2\times n$

- $\forall\ 1\le i<j\le n$，$v_i\ne v_j$

- 如果点 $i$ 和点 $j$ 之间有边相连，那么 $\left\vert v_i-v_j\right\vert$ 不能为质数。

输出一种填入权值的方案，或报告无解。

### 思路

不难想到，除了 $2$ 以外的所有偶数都不是质数，因此考虑只将权值设为偶数，并将相邻两点之差设为大于 $2$ 的偶数。所以，两个差值为 $2$ 的偶数一定不能放在相邻的点上。

我们考虑将这棵树进行黑白染色，并假设有 $m$ 个黑点，黑点个数不小于白点。那么，我们将 $2$，$4\ldots 2\times m$ 放在黑点上，$2\times(m+1)$，$2\times(m+2)\ldots 2\times n$放在白点上。这样，我们只需要避免 $2\times m$ 和 $2\times (m+1)$ 不相邻即可。

这时候，如果存在两个不相邻的黑点与白点，那么我们将 $2\times m$ 和 $2\times (m+1)$ 放在这两个点上就好了。但是，如果不存在这种情况怎么办？

此时，所有黑点与所有白点都相邻。因此，白点中只有一个。那么，这是一张菊花图。考虑到 $1$ 也不是质数，所以我们在白点放上 $2$，在黑点上放上 $1$，$6$，$8\ldots 2\times n$ 即可。

### 代码

代码中并没有保证黑点个数不小于白点，因此对菊花图的中心颜色进行了分讨。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,u,v,B,W,f[200005],F,p,q,ans[200005],sum;
vector<int>g[200005];
void dfs(int u,int fa){
	for(int i=0;i<g[u].size();i++){
		if(g[u][i]==fa)continue;
		f[g[u][i]]=f[u]^1;
		if(f[g[u][i]]==0)B++;
		else W++;
		dfs(g[u][i],u);
	}
}//染色 
int dfs1(int u,int fa,int dep){
	if(dep==3)return u;//如果两个点距离为 3，它们一定不同色且不相邻 
	for(int i=0;i<g[u].size();i++){
		if(g[u][i]==fa||dep!=2&&g[g[u][i]].size()==1)continue;
		return dfs1(g[u][i],u,dep+1);
	}
}//找到不相邻的黑点和白点 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)g[i].clear();
		for(int i=1;i<n;i++){
			cin>>u>>v;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		B=1,W=0;
		f[1]=0;
		dfs(1,-1);
		if(B==1){
			F=2;
			for(int i=1;i<=n;i++){
				if(f[i]==0&&B==1)cout<<"2 ";
				else{
					if(F==2)cout<<"1 ";
					else cout<<F*2<<" ";
					F++;
				}
			}
		}
		else if(W==1){
			F=2;
			for(int i=1;i<=n;i++){
				if(f[i]==1&&W==1)cout<<"2 ";
				else{
					if(F==2)cout<<"1 ";
					else cout<<F*2<<" ";
					F++;
				}
			}
		}//判断菊花图 
		else{
			for(int i=1;i<=n;i++){
				if(g[i].size()==1){
					p=i;
					q=dfs1(p,-1,0);
					break;
				}
			}
			sum=2;
			for(int i=1;i<=n;i++){
				if(f[i]==f[p]&&i!=p){
					ans[i]=sum;
					sum+=2;
				}
			}
			ans[p]=sum;
			sum+=2;
			ans[q]=sum;
			sum+=2;
			for(int i=1;i<=n;i++){
				if(f[i]==f[q]&&i!=q){
					ans[i]=sum;
					sum+=2;
				}
			}
			for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
		}//一般的做法
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：tian720 (赞：1)

题目传送门：[[CF2040D] Non Prime Tree](https://www.luogu.com.cn/problem/CF2040D)。
## Solution：
考虑抓特殊点进行构造。

不是质数可以转化为是 $1$ 或合数。我们考虑从 $1$ 到 $2n$ 这个特殊点入手。那么可以想到选这 $2n$ 个数中的偶数，这样就能将 $n$ 个点不重不漏地考虑，且让这棵树中的任意两个相邻点的权值差为 $2x(x\ge 1)$。

那么可以将整棵树分层，将其分为奇数层和偶数层，然后再求出它的 bfs 序。我们根据 bfs 序依次将 $2,4,6,8,...$ 填入奇数层，再将 $2n,2n-2,2n-4,2n-6,...$ 填入偶数层，此时最多有一条边不符合（最后一层的最后一条边的点权差为 $2$），其它边的点权差一定为大于 $2$ 的偶数。那么我们就将最后这个点权 $+1$ 或 $-1$（使它们差为 $1$）就行了。
## Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5,M=4e5+5;
int las[N],nex[M],en[M],idx;
int dep[N],t[N],n;
void add(int x,int y){
	en[++idx]=y;
	nex[idx]=las[x];
	las[x]=idx;
}
int ans[N];
struct node{
	int x,fa;
};
queue<node> q;
void bfs(){
	dep[1]=1;
	q.push({1,0});
	int tmp=0,now1=0,now2=2*n+2;
	while(!q.empty()){
		node aa=q.front();
		q.pop();
		t[aa.x]=++tmp;
		if(dep[aa.x]&1) ans[aa.x]=now1+=2;//奇偶层判断 
		else ans[aa.x]=now2-=2;
		if(t[aa.x]==n&&abs(ans[aa.fa]-ans[aa.x])==2){//可能没有边不符合
			if(dep[aa.x]&1) ans[aa.x]++;
			else ans[aa.x]--;
		}
		for(int i=las[aa.x];i;i=nex[i]){
			int j=en[i];
			if(j==aa.fa) continue;
			dep[j]=dep[aa.x]+1;
			q.push({j,aa.x});
		}
	}
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) las[i]=0;
		idx=0;
		for(int i=1;i<n;i++){
			int a,b;
			scanf("%d%d",&a,&b);
			add(a,b),add(b,a);
		}
		bfs();
		for(int i=1;i<=n;i++) printf("%d ",ans[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：wmrqwq (赞：1)

# 题目链接

[CF2040D Non Prime Tree](https://www.luogu.com.cn/problem/CF2040D)

# 解题思路

挺好的题啊，赛时 10min 胡了个正解，但是 $ans$ 数组打成 $a$ 虚空调试 15min，怎么回事呢。

## 解法一

赛时做法。

可以看出当前无论怎么填，只要状态合法，那么一定有至少一种方案可以将整棵树都被填满，~~但是我不会证明啊~~。

于是我们就有一个[暴力做法](https://codeforces.com/contest/2040/submission/295593341)，那就是直接钦定根节点的值为 $1$，然后直接暴力枚举最早的子节点的值使其合法，就行了。

感觉时间复杂度是 $O(n^2)$？我不会证啊。

发现上述算法的瓶颈只在于暴力枚举，我们又注意到 $1 \sim n$ 的合数密度是很大的，因此直接从根到叶子结点依次随机出可行的权值就行了。

时间复杂度近似 $O(n)$ 吧，我不会证啊。


## 解法二

应该是正经做法吧。

发现相邻节点结点填差为 $1$ 时总是最优的。

尽量多构造这种东西，然后就下来形如构造 $4,6,8 \dots$ 的差的形式即可。

容易证明上述构造的权值可以 $\le 2n$。

其他题解应该讲的挺清晰了吧，在此不再叙述代码细节。

时间复杂度 $O(n)$。

# 参考代码

[解法一](https://codeforces.com/contest/2040/submission/295598970)的代码，觉得有问题的可以来 hack。

---

## 作者：xiaoyang222 (赞：0)

从一个点向下遍历，我们对于儿子就可以找到和父亲最小的满足条件的数，赋值，再继续向下遍历。

为什么这个是对的呢？首先讨论下面情况。

1. 当这个儿子是他的第一个儿子，他将会跳到父亲的下一个数。

2. 当这个儿子是他后面的儿子，如果当前的数刚好是奇数，只需要加一，否则是偶数，除了 $2$ 的偶数都可以。

所以一个数最多会让计数器浪费一次，所以最多计数器为 $2n$，满足要求。

代码很短。

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int N=2e5+5,M=5e5+5;
bool f[M];
void init(){
	f[1]=1;
	for (int i=2;i<M;++i){
		if (!f[i])
			for (int j=i+i;j<M;j+=i)
				f[j]=1;
	}
}
vector<int> t[N];
int ans[N],cnt;
void dfs(int u,int fa){
	ans[u]=cnt++;
	for (int &v:t[u]){
		if (v==fa) continue;
		while (!f[cnt-ans[u]]) ++cnt;
		dfs(v,u);
	}
}
void solve(){
	int n;
	cin >> n;
	for (int i=1;i<=n;++i) t[i].clear();
	for (int i=1;i<n;++i){
		int u,v;
		cin >> u >> v;
		t[u].emplace_back(v),t[v].emplace_back(u);
	}
	cnt=1;
	dfs(1,0);
	for (int i=1;i<=n;++i) cout<<ans[i]<<" ";cout<<"\n";
}
int main(){
	init();
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;
	cin >> T;
	for (int _=0;_<T;++_) solve();
	cout.flush();
	return 0;
}
```

---

