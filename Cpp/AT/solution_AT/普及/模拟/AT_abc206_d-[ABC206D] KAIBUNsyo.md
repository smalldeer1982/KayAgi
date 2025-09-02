# [ABC206D] KAIBUNsyo

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc206/tasks/abc206_d

$ N $ 項からなる正整数列 $ A=(A_1,A_2,\ \dots\ A_N) $ が与えられます。  
 以下の操作を $ 0 $ 回以上何度でも行える時、操作を最小何回行えば、$ A $ を回文にすることができますか？

- ある正整数の組 $ (x,y) $ を選ぶ。その後、現在 $ A $ に含まれる $ x $ をすべて $ y $ に置き換える。

なお、この問題では、全ての整数 $ i $ ($ 1\ \le\ i\ \le\ N $) について、$ A_i=A_{N+1-i} $ が成り立つとき、またその時に限って、$ A $ が回文であると言います。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ A_i\ \le\ 2\ \times\ 10^5 $

### Sample Explanation 1

\- はじめ、$ A=(1,5,3,2,5,2,3,1) $ です。 - $ A $ に含まれる $ 3 $ を全て $ 2 $ に置き換えると、$ A=(1,5,2,2,5,2,2,1) $ となります。 - $ A $ に含まれる $ 2 $ を全て $ 5 $ に置き換えると、$ A=(1,5,5,5,5,5,5,1) $ となります。 以上の操作を行うと、$ A $ を $ 2 $ 回の操作で回文にすることができ、これが最小です。

### Sample Explanation 3

$ A $ がはじめから回文である可能性もあります。

## 样例 #1

### 输入

```
8
1 5 3 2 5 2 3 1```

### 输出

```
2```

## 样例 #2

### 输入

```
7
1 2 3 4 1 2 3```

### 输出

```
1```

## 样例 #3

### 输入

```
1
200000```

### 输出

```
0```

# 题解

## 作者：_shine_ (赞：3)

#### 半分做法
一个没考虑到多次变更的做法。

既然要让该序列为回文序列，显然要让对称的两两相等。使用 ```map``` 来记录 $a_i$ 更改后的实际数字，只要每次不相等，就让两者进行更改（赋值均可），再统计答案即可。

[link](https://atcoder.jp/contests/abc206/submissions/45962767)

但是可以发现，该数只要多次进行更改，每次就会出错，因为会这样无法及时的把所有现在赋值为 $a_i$ 的都改成 $a_j$，所以只有半分，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/m2u5ijmf.png)
如图，在更改 $2$ 次中，你的程序无法把其他的值为 $7$ 的更改为 $6$，换句话说，如果两边都有多个相同，则无法拥有足够的时间使得都更改。
#### AC做法
半分优化做法。

建立一个并查集，每次查找是否在一个集合中，如果没有，显然要进行修改，答案加 $1$，这样就可以使得不存在多次修改的问题，并且也不存在合并时到底怎么赋值。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
int n,ans;
int a[maxn];
int f[maxn];
map<int,int>p;
int e[maxn],num;
int find(int x){
	if(f[x]==x)return x;
	else return f[x]=find(f[x]);
}
signed main(){
	cin >> n;
	for(int i=1;i<=n;++i){
		cin >> a[i];
		if(p[a[i]]==0){
			e[++num]=a[i];
			p[a[i]]=i;
		}
		f[i]=p[a[i]];
	}
	int idx=n+1;
	for(int i=1;i<=n/2;++i){
		--idx;
		if(find(i)!=find(idx)){
			f[find(i)]=find(idx);
			ans++;
		}
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：_GW_ (赞：2)

## 思路
回文串，即以中心对称的两点要相等。

若这两点分别为 $x$ 和 $y$ 时，如 $x=y$，那么不用改。

否则，要么把 $x$ 改为 $y$，要么把 $y$ 改成 $x$。

然后呢，$x=y$ 了，那么再往后看到 $x$ 和 $y$，他们就是一样的了。

如何维护 $x$ 和 $y$ 的关系呢？用一个并查集，修改时合并一下即可。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int a[N],b[N],sum[N],n,m,x,y,fa[N],res;
int find(int x)
{
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
int main()
{
    for(int i=0;i<N;i++) fa[i]=i;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(int i=1;i<=n/2;i++)
    {
         if(a[i]!=a[n-i+1])
         {
             int x=find(a[i]),y=find(a[n-i+1]);
             if(x!=y)
             {
                 fa[x]=fa[y];
                 res++;
             }
         }
    }
    cout<<res<<endl;
    return 0;
}
```


---

## 作者：__xxy_free_ioi__ (赞：1)

# 题解：AT\_abc206\_d \[ABC206D] KAIBUNsyo

好题。

## 解法

我们观察题目发现，对于每个 $1 \le i \le n$，$a_i$ 必须等于 $a_{n-i+1}$。所以，可以把这种关系看成图上的关系，每个数是一个节点，需要相等的数之间有一条连边，那么，答案就是总点数减去连通块数量。

这个既可以用 DFS 求，也可以用并查集求。

## 代码

```
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define up(i, s, t) for (int i = s; i <= t; i++)
#define down(i, s, t) for (int i = s; i >= t; i--)

const int N = 2e5 + 10;

int n;
unordered_set<int> s, c;
int a[N], fa[N];

int find(int x) { return fa[x] == x ? x : (fa[x] = find(fa[x])); }

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> n;
	iota(fa + 1, fa + N + 1, 1);
	up(i, 1, n) cin >> a[i], s.insert(a[i]);
	for (int l = 1, r = n; l <= r; l++, r--) fa[find(a[l])] = find(a[r]);
	up(i, 1, n) c.insert(find(a[i]));
	cout << s.size() - c.size();
	
	return 0;
}
```

---

## 作者：_hxh (赞：1)

### 题意

有一个长度为 $n$ 的正数序列 $A$，每次可以把序列中的每一个 $x$ 都换为 $y$，求让序列 $A$ 变成回文序列的最少操作次数。

### 分析

目标是让序列中的每个元素 $A_i$ 都满足 $A_i = A_{n - i + 1}(1 \le i \le n)$，那么对于初始的序列 $A$，其中的元素 $A_i(1 \le i \le n)$ 只有两种情况：

1. $A_i = A_{n - i + 1}$，这样我们不用去管它们，因为它们要么不变，要么因为其他的修改操作一起被改成某个数，它们始终是相等的；
2. $A_i \ne A_{n - i + 1}$，通常我们可能会想到底要修改谁，但其实不用这么麻烦。我们只要标记这两个数要修改成同一个数就行，即在接下来的操作中这两个数被认为是同一个数。这种合并操作可以很方便地用并查集实现。每合并一次就相当于执行了一次把序列中的每一个 $x$ 都换为 $y$ 的操作。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n,a[N],f[N],ans;
int find(int k)
{
	if (f[k] == k)
		return k;
	return f[k] = find(f[k]);
}
int main()
{
	cin >> n;
	for (int i = 1;i <= n;i++)
	{
		cin >> a[i];
		f[i] = i;
	}
	for (int i = n + 1;i < N;i++)
		f[i] = i;
	for (int i = 1;i <= n / 2;i++)
		if (find(a[i]) != find(a[n - i + 1]))
		{
			f[find(a[i])] = find(a[n - i + 1]);
			ans++;
		}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：yzht (赞：0)

## 题目大意
有一个长度为 $n$ 的正数序列，每次可以把序列中的每一个 $x$ 都换为 $y$，求让这一个序列变成回文序列的最少操作次数。

## 整体思路
对于每一组 $x$ 和 $y$ 来说，进行替换操作就相当于 $x$ 等价于 $y$ ，就可以建立一个 $x$ 的集合来存储那些值于 $x$ 等价，也就是把 $x$ 等价的值放进 $x$ 这一个联通块中。就可以发现问题就变成了一个经典并查集的问题。

## 易错点
用来存储父亲节点的 $f$ 数组的下标其实时题目中的 $A$ 序列，所以在还原时循环次数是 $100000$ 次。

## 给出代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[200005];
int f[200005];
int ans;
int find(int x){//用于寻找祖宗节点
    if(f[x]!=x){
        f[x]=find(f[x]);
    }
    return f[x];
}
int main(){
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i]);
    }
    for(int i=1; i<=200005; i++){//将父亲设置为自己
        f[i]=i;
    }
    for(int i=1; i<=n/2; i++){
        int l=find(a[i]);
        int r=find(a[n-i+1]);
        if(l!=r){//判断是否已在同一个集合中
            f[l]=r;//合并
            ans++;//统计答案
        }
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：guaidaokenan (赞：0)

### 题目大意
有一个长度为 $n$ 的正数序列 $A$，每次可以把序列中的每一个 $x$ 都换为 $y$，求让序列 $A$ 变成回文序列的最少操作次数。
### 整体思路
对于每一对 $x$ 和 $y$ 来说，进行替换操作就相当于 $x$ 等价于 $y$ ，就可以建立一个 $x$ 的集合来存储那些值于 $x$ 等价。就可以发现问题就变成了一个并查集的问题。
### 易错点
用来存储父亲节点的 $f$ 数组的下标其实时题目中的 $A$ 数组，所以再还原时循环次数是 $100000$ 次。

最后附上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[200005];
int f[200005];
int ans;
int find(int x){//用于寻找祖宗节点
    if(f[x]!=x){
        f[x]=find(f[x]);
    }
    return f[x];
}
int main(){
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i]);
    }
    for(int i=1; i<=200005; i++){
        f[i]=i;
    }
    for(int i=1; i<=n/2; i++){
        int l=find(a[i]);
        int r=find(a[n-i+1]);
        if(l!=r){
            f[l]=r;
            ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：liruizhou_lihui (赞：0)

## 前置知识
并查集。
## 思路分析

要把这个序列变成回文序列，需要使得任何的 $ i(1\le i\le \lfloor \frac{n}{2} \rfloor)$，满足 $a_i=a_{n-i+1}$。

如果 $a_i=a_{n-i+1}$，那就不用管这两个。因为如果变了那他们还是相等的，如果不一样就选其中一个数把整个序列的另一个数变为这个数。

但你总不能找到一个不一样的就跑一遍吧。

可以用并查集维护，如果两个不一样就放到一个家族。在检验的时候直接看家族是否相同即可。

把路径压缩和按秩合并叠到一起跑的飞快。

其实还可以离散化一下（

## 最终代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
int a[200005];
int fa[200005];
int cnt[200005];
int findfa(int u)//找爸爸 
{
	if(u==fa[u])
	{
		return u;
	}
	return fa[u]=findfa(fa[u]);
}
void add(int u,int v)//把两个不同的数设为一个家族 
{
	int fau=findfa(u);
	int fav=findfa(v);
	if(fau!=fav)
	{
		if(cnt[fau]<cnt[fav])//按秩合并 
		{
			cnt[fav]+=cnt[fau];
			fa[fav]=fau;
		}
		else
		{
			cnt[fau]+=cnt[fav];
			fa[fau]=fav;
		}
	}
}
bool check(int u,int v)
{
	int fau=findfa(u);
	int fav=findfa(v);
	return fau==fav;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		fa[a[i]]=a[i];//初始的时候自己的爸爸是自己 
		cnt[a[i]]++;
	}
	for(int i=1;i<=n/2;i++)
	{
		if(!check(a[i],a[n-i+1]))//如果家族不同 
		{
			ans++;//需要变换一次
			add(a[i],a[n-i+1]);//合并 
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Thorongil_Gondor (赞：0)

# [ABC206D] KAIBUNsyo 题解
## 题意
通过每次选择一对正数 $(x,y)$，将序列中的每一个 $x$ 都换为 $y$，用最小次数将序列变为回文序列。
## 思路
由于是回文序列，每个 $a_i$ 和 $a_{n-1-i}$ 必须相等。  
可以将这种关系视为图，每个数字是一个节点，相等的数字之间有一条边。故相同数即为已有的连通分量，应达到连通分量数为节点数，答案即为答案就是节点总数减去连通分量数量。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int vis[200010],n,cnt;
vector<int> a,b[200010];
unordered_set<int> s;
void dfs(int x){
	vis[x]=1;
	for(int y:b[x])if(!vis[y])dfs(y);
}
int main(){
	cin>>n;
	a.resize(n);
	for(int &x:a)cin>>x,s.insert(x);
	for(int l=0,r=n-1;l<=r;l++,r--)if(a[l]!=a[r])b[a[l]].push_back(a[r]),b[a[r]].push_back(a[l]);
	for(int x:a)if(!vis[x])dfs(x),cnt++;
	cout<<s.size()-cnt;
  	return 0;
}
```

---

## 作者：Link_1314 (赞：0)

# 思路 
观察到，对于每个位置 $i$，$A_i$ 和 $A_{N-1-i}$ 最终必须相等。

我们可以将这种关系看作一个图，其中每个数字是一个节点，需要相等的数字之间有一条边。

所以，问题就转化为找到这个图中的连通分量数量，**答案就是节点总数减去连通分量数量**。

# 正解代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using VI = vector<int>;
const int NN = 2e5 + 4;
VI G[NN];
int Vis[NN], N;
void dfs(int u) {
  Vis[u] = 1;
  for (int v : G[u])
    if (!Vis[v]) dfs(v);
}
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  cin >> N;
  VI A(N);
  unordered_set<int> S;
  for (int &a : A) cin >> a, S.insert(a);
  for (int l = 0, r = N - 1; l <= r; ++l, --r)
    if (A[l] != A[r]) G[A[l]].push_back(A[r]), G[A[r]].push_back(A[l]);
  int cc = 0;
  for (int a : A)
    if (!Vis[a]) dfs(a), ++cc;
  cout << S.size() - cc;
  return 0;
}
```

---

## 作者：lovely_codingcow (赞：0)

## 思路

观察到替换数字的过程，实际上就是将两个数字归为一类。借此不难联想到并查集的工作过程，因此我们可以考虑使用并查集解决这个问题。

我们使用并查集维护当前数字所属的集合，初始时对于数字 $x$，它位于集合 $x$ 中。当我们发现本应相同但是并不在同一个集合内的数字时，我们不得不将其合并，并记录下一次操作。在操作的过程中，你不需要去判断究竟是改为了左边的或者右边的数字，只需要知道它们二者同属一个集合即可。需要注意的是，对于 $a_i$，他一开始属于集合 $a_i$ 而不是集合 $i$，这个搞得我调了好一会儿，服了。

简单分析可以得到，程序的时间复杂度控制在了极其优秀的 $\mathcal{O}(n \,\alpha(n))$。

## 代码

```cpp
#include <iostream>

#define int long long
#define get(x) (n - x + 1)

using namespace std;

int n, fa[200009], a[200009];

int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		fa[a[i]] = a[i];
	}
	int ans = 0;
	for (int i = 1; i <= n / 2; i++) {
		if (find(a[i]) != find(a[get(i)])) {
			fa[find(a[i])] = find(a[get(i)]);
			ans += 1;
		}
	}
	cout << ans;
}
```

---

## 作者：loser_seele (赞：0)

观察到如果 $ A_i $ 与 $ A_{N-i+1} $ 不相同的话，那么必须要把它们修改为相同的数字。

于是考虑对于每个满足 $ A_i $ 与 $ A_{N-i+1} $ 不相同的 $ i $，在 $ A_i $ 与 $ A_{N-i+1} $ 之间建边。

接下来考虑单个连通块内需要的修改次数，这显然等于连通块的大小 $ -1 $，因此每个连通块对答案的贡献就是 $ -1 $。

因此问题转化为 $ A $ 中不同数字的个数减去连通块数，这个可以直接用并查集维护，时间复杂度 $ \mathcal{O}(n\log{n}) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
const int mod=1e18;
int n,q,u,v,c;
char op;
struct Splay
{
    int ch[maxn][2],fa[maxn],siz[maxn],val[maxn],sum[maxn],add[maxn],mul[maxn],rev[maxn];
    void clear(int x)
    {
        ch[x][0]=ch[x][1]=fa[x]=siz[x]=val[x]=sum[x]=add[x]=rev[x]=0;
        mul[x]=1;
    }
    int getch(int x)
    {
        return (ch[fa[x]][1]==x);
    }
    int isroot(int x)
    {
        clear(0);
        return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
    }
    void maintain(int x)
    {
        clear(0);
        siz[x]=(siz[ch[x][0]]+1+siz[ch[x][1]])%mod;
        sum[x]=(sum[ch[x][0]]+val[x]+sum[ch[x][1]])%mod;
    }
    void pushdown(int x)
    {
        clear(0);
        if(mul[x]!=1)
        {
            if(ch[x][0])
            mul[ch[x][0]]=(mul[x]*mul[ch[x][0]])%mod,val[ch[x][0]]=(val[ch[x][0]]*mul[x])%mod,sum[ch[x][0]]=(sum[ch[x][0]]*mul[x])%mod,add[ch[x][0]]=(add[ch[x][0]]*mul[x])%mod;
            if(ch[x][1])
            mul[ch[x][1]]=(mul[x]*mul[ch[x][1]])%mod,val[ch[x][1]]=(val[ch[x][1]]*mul[x])%mod,sum[ch[x][1]]=(sum[ch[x][1]]*mul[x])%mod,add[ch[x][1]]=(add[ch[x][1]]*mul[x])%mod;
            mul[x]=1;
        }
        if(add[x])
        {
            if(ch[x][0])
            add[ch[x][0]]=(add[ch[x][0]]+add[x])%mod,val[ch[x][0]]=(val[ch[x][0]]+add[x])%mod,sum[ch[x][0]]=(sum[ch[x][0]]+add[x]*siz[ch[x][0]])%mod;
            if(ch[x][1])
            add[ch[x][1]]=(add[ch[x][1]]+add[x])%mod,val[ch[x][1]]=(val[ch[x][1]]+add[x])%mod,sum[ch[x][1]]=(sum[ch[x][1]]+add[x]*siz[ch[x][1]])%mod;
            add[x]=0;
        }
        if(rev[x])
        {
            if(ch[x][0])
            rev[ch[x][0]]^=1,swap(ch[ch[x][0]][0],ch[ch[x][0]][1]);
            if(ch[x][1])
            rev[ch[x][1]]^=1,swap(ch[ch[x][1]][0],ch[ch[x][1]][1]);
            rev[x]=0;
        }
    }
    void update(int x)
    {
        if(!isroot(x))
        update(fa[x]);
        pushdown(x);
    }
    void rotate(int x)
    {
        int y=fa[x],z=fa[y],chx=getch(x),chy=getch(y);
        fa[x]=z;
        if(!isroot(y))
        ch[z][chy]=x;
        ch[y][chx]=ch[x][chx^1];
        fa[ch[x][chx^1]]=y;
        ch[x][chx^1]=y;
        fa[y]=x;
        maintain(y);
        maintain(x);
        maintain(z);
    }
    void splay(int x)
    {
        update(x);
        for(int f=fa[x];f=fa[x],!isroot(x);rotate(x))
        if(!isroot(f))
        rotate(getch(x)==getch(f)?f:x);
    }
    void access(int x)
    {
        for(int f=0;x;f=x,x=fa[x])
        splay(x),ch[x][1]=f,maintain(x);
    }
    void makeroot(int x)
    {
        access(x);
        splay(x);
        swap(ch[x][0],ch[x][1]);
        rev[x]^=1;
    }
    int find(int x)
    {
        access(x);
        splay(x);
        while(ch[x][0])
        x=ch[x][0];
        splay(x);
        return x;
    }
    void final_mul(int u,int v,int c)
    {
    makeroot(u), access(v), splay(v);
      val[v] = val[v] * c % mod;
      sum[v] = sum[v] * c % mod;
      mul[v] = mul[v] * c % mod;
    }
    void final_add(int u,int v,int c)
    {
    makeroot(u), access(v), splay(v);
      val[v] = (val[v] + c) % mod;
      sum[v] = (sum[v] + siz[v] * c % mod) % mod;
      add[v] = (add[v] + c) % mod;
    }
    int query1(int u,int v)
    {
    makeroot(u), access(v), splay(v);
    return sum[v];
    }
    void link(int u,int v)
    {
    if (find(u) != find(v)) 
    makeroot(u), fa[u] = v;
    }
    void cut(int u,int v)
    {
    makeroot(u);
      access(v);
      splay(v);
      if (ch[v][0] == u && !ch[u][1]) 
      ch[v][0] = fa[u] = 0;
    }
    bool query2(int u,int v)
    {
    return find(u) == find(v);
    }
}st;
int find(int x)
{
return st.find(x);
}
void merge(int u,int v)
{
st.link(u,v);
}
int a[2000020];
set<int>p;
bitset<2000020>vis,vis2;
signed main()
{
cin>>n;
if(n==1)
{
cout<<0;
return 0;
}
for(int i=1;i<=n;i++)
cin>>a[i],p.insert(a[i]),st.clear(i),st.maintain(i),st.splay(i);
for(int i=1;i<=n/2;i++)
if(a[i]!=a[n-i+1])
st.link(a[i],a[n-i+1]);
int ans=0;
for(int i=1;i<=n;i++)
if(!vis[st.find(a[i])])
vis[st.find(a[i])]=1,ans++;
cout<<p.size()-ans;
}
```


---

## 作者：liruizhou_lihui (赞：0)

## 前置知识
先看一个好康的视频：《如果我们的家族相同，那我就是你爹了！》
![](bilibili:BV1ge4y1b78w)

## 思路分析

要把这个序列变成回文序列，需要使得任何的 $ i(1\le i\le \lfloor \frac{n}{2} \rfloor)$，满足 $a_i=a_{n-i+1}$。

如果 $a_i=a_{n-i+1}$，那就不用管这两个。因为如果变了那他们还是相等的，如果不一样就选其中一个数把整个序列的另一个数变为这个数。

但你总不能找到一个不一样的就跑一遍吧。

可以用并查集维护，如果两个不一样就放到一个家族。在检验的时候直接看家族是否相同即可。

把路径压缩和按秩合并叠到一起跑的飞快。

其实还可以离散化一下（

## 最终代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
int a[200005];
int fa[200005];
int cnt[200005];
int findfa(int u)//找爸爸 
{
	if(u==fa[u])
	{
		return u;
	}
	return fa[u]=findfa(fa[u]);
}
void add(int u,int v)//把两个不同的数设为一个家族 
{
	int fau=findfa(u);
	int fav=findfa(v);
	if(fau!=fav)
	{
		if(cnt[fau]<cnt[fav])//按秩合并 
		{
			cnt[fav]+=cnt[fau];
			fa[fav]=fau;
		}
		else
		{
			cnt[fau]+=cnt[fav];
			fa[fau]=fav;
		}
	}
}
bool check(int u,int v)
{
	int fau=findfa(u);
	int fav=findfa(v);
	return fau==fav;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		fa[a[i]]=a[i];//初始的时候自己的爸爸是自己 
		cnt[a[i]]++;
	}
	for(int i=1;i<=n/2;i++)
	{
		if(!check(a[i],a[n-i+1]))//如果家族不同 
		{
			ans++;//需要变换一次
			add(a[i],a[n-i+1]);//合并 
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：umcalla (赞：0)

## 思路
要使序列成为回文序列，即让 $A_{i} = A_{n-i+1}$。

如果 $A_{i} \ne A_{n-i+1}$ 要么将 $A_{i}$ 转化成 $A_{n-i+1}$，要么将 $A_{n-i+1}$ 转化成 $A_{i}$。

假如 $a$ 要转化成 $b$，$c$ 要转化成 $a$，那么就可以让 $c$ 转化成 $b$。

由此我们可以将要互相转换的数字并为一组，这一组对答案的贡献就是组内元素的数量 $ - 1$，用并查集维护即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int si[200010],f[200010];
bool v[200010];
int a[200010],ans;
int find(int x)
{
	return x==f[x]?x:f[x]=find(f[x]);
}
void merge(int x,int y)
{
	int fx=find(x),fy=find(y);
	if(fx!=fy)
	{
		f[fx]=fy;
		si[fy]+=si[fx];
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=200000;i++)
		f[i]=i,si[i]=1;
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	for(int i=1;i<=n/2;i++)
	{
		if(a[i]!=a[n-i+1])
			merge(a[i],a[n-i+1]);
	}
	for(int i=1;i<=200000;i++)
	{
		int fi=find(i);
		if(!v[fi])
		{
			ans+=si[fi]-1;
			v[fi]=1;
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：xzy090626 (赞：0)

一眼结论题。

观察到，

- 当序列两个对应位置相同时，即使对其数字进行修改也不会有影响。

- 当两个对应位置不同时，无论中间如何修改，最终的结果一定是**两者修改后的结果相同**。

我们可以将第二种情况记录为两个不同值之间的关系，那么很显然是两个值一旦出现这种关系，那么它们修改后的结果必定一样，而且这种关系具有传递性。

因此可以用并查集来维护这样的关系。

总而言之，我们不必考虑到底是如何修改的，只需要在出现差异时进行合并并记录即可。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 7;
int s[N];
int n;
int ans;
int fa[N];
int find(int x){
	if(fa[x]==x) return x;
	return fa[x] = find(fa[x]);
}
void Uni(int x,int y){
	x = find(x);
	fa[x] = find(y);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>s[i];
		fa[s[i]] = s[i];
	}
	for(int i=1;i<=n/2;++i){
		if(s[i]==s[n-i+1]) continue;
		if(find(s[i])!=find(s[n-i+1])){
			Uni(s[i],s[n-i+1]);
			ans++;
		}
	}
	cout<<ans;
	return 0;
}
```

另外，如果观察样例可得，修改操作的顺序会对结果产生影响。不过我们这种方法并不关心其顺序，只关心其最终结果是否相同，从而巧妙地获得了最优解的答案。

---

