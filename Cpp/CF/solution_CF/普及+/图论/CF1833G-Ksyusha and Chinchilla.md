# Ksyusha and Chinchilla

## 题目描述

在一棵树上删去一些边，使得形成的几个连通块，都**有且仅有** $3$ 个结点。

## 样例 #1

### 输入

```
4
9
1 2
4 3
7 9
5 4
4 6
3 2
8 7
1 7
6
1 2
1 3
4 3
1 5
6 1
6
1 2
3 2
3 4
4 5
6 5
5
1 3
5 3
5 2
3 4```

### 输出

```
2
2 8 
-1
1
3 
-1```

## 样例 #2

### 输入

```
4
2
1 2
3
1 2
3 1
6
1 2
3 1
3 4
3 5
6 1
9
2 6
6 9
9 1
9 7
1 8
7 3
8 5
4 7```

### 输出

```
-1
0

1
2 
2
4 3```

# 题解

## 作者：Iniaugoty (赞：8)

## problem

在一棵树上删去一些边，使得形成的几个连通块，都**有且仅有** $3$ 个结点。输出：删边后连通块的数量和删去的边的编号。

## solution

- $n\not\equiv0\pmod3$：显然没有答案。

- $n\equiv0\pmod3$：设 $size_i$ 表示以 $i$ 为根的子树大小，自顶而下递归处理：

   - 若 $size_i=3$，把 $i$ 与其父结点的连边删掉。因为已经不在原图上了，为了不影响其他点的计算，令 $size_i\gets0$。
   
   - 若 $size_i<3$，啥也不用干。
   
   - 若 $size_i>3$，想一下可以发现，这样就无法形成大小 $3$ 的连通块了，故标记一下没有答案。
   
为了方便处理，设结节点为 $1$，其父节结为 $0$。

## code

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int head[N],cnt;//head[i] 表示起点为 i 的第一条边
struct star{//链式前向星存边
	int next,to,id;//next 是下一条边，to 是边的终点，id 是边的编号
}e[N<<1];//无向边二倍空间！
void add(int u,int v,int w){//加边函数
	e[++cnt].next=head[u];
	e[cnt].to=v;
	e[cnt].id=w;
	head[u]=cnt;
}
int T,n,size[N];//T 是数据组数，n 是点数
bool ans,cut[N];//ans 表示是否有答案，cut[i] 表示是否要删去编号 i 的边
void dfs(int step,int father){//step 是当前结点，father 是其父结点
	if(!ans) return;//如果已经确定没有答案，就返回
	int f=0;//如果要删边，要删的边的编号
	for(int i=head[step];i;i=e[i].next)
		if(e[i].to==father) f=e[i].id;//记录编号
		else dfs(e[i].to,step),size[step]+=size[e[i].to];//递归子节点，并计算 size
	size[step]++;//算上自己
	if(size[step]==3) size[step]=0,cut[f]=1;//删边
	//如果 step 是根结点，此时 f 就是 0，不影响 cut 数组，所以不用特判
	else if(size[step]>3) ans=0;//可以确定没有答案
}
signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--){
		for(int i=1;i<=n;i++){//不要 memset！
			head[i]=size[i]=cut[i]=0;//不要 memset！！
			e[(i<<1)-1]=e[i<<1]={0,0,0};//不要 memset！！！
		}//除非是 bool 型，否则多测清空不要用 memset，容易超时
		cin>>n,cnt=0;
		for(int i=1,u,v;i<n;i++)
			cin>>u>>v,add(u,v,i),add(v,u,i);//无向图建双向边
		ans=!(n%3);//若 n 不是 3 的倍数，直接标记没有答案
		dfs(1,0);//求答案
		if(!ans) cout<<"-1\n";//没有答案直接输出 -1
		else{
			cout<<n/3-1<<"\n";//删掉的边数
			for(int i=1;i<n;i++)//遍历每条边
				if(cut[i]) cout<<i<<" ";//输出要删的
			cout<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：Coffee_zzz (赞：4)

### 分析

首先当 $n=3$ 时一定可以，直接输出 `0` 和一个空行即可。

其次当 $n\bmod 3\neq 0$ 的时候，切割后一定会剩下一部分内容，输出 `-1`。

对于剩余的情况，我们设 $siz_i$ 表示以 $i$ 为根的子树的大小。

对于某个非根节点 $u$：

- 若 $siz_u=3$，则切断 $u$ 与其父亲节点之间的连边，同时将 $siz_u$ 设为 $0$；

- 若 $siz_u>3$，则无法切割，修改标记答案的变量。

由于 $siz_u$ 的值会修改，所以我们可以在求出所有儿子节点的 $siz$ 值后再根据新的 $siz$ 求 $siz_u$ 的值。

别忘了多测要清空。

### 代码

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
namespace IO{
	char ibuf[(1<<20)+1],*iS,*iT;
	#if ONLINE_JUDGE
	#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read(){
		reg char ch=gh();
		reg long long x=0;
		reg char t=0;
		while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();
		while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();
		return t?-x:x;
	}
}
using IO::read;
const int N=4e5+5;
struct Edge{
	int to,nxt,id;
}edge[N<<1];
int cnt,head[N],n,ans[N],pos,siz[N];
void add(int u,int v,int id){
	edge[++cnt].to=v;
	edge[cnt].nxt=head[u];
	edge[cnt].id=id;
	head[u]=cnt;
}
bool init(int u,int f){
	int v,e;
	siz[u]=1;
	for(int i=head[u];i;i=edge[i].nxt){
		v=edge[i].to;
		if(v==f){
			e=i;
			continue;
		}
		init(v,u);
		siz[u]=siz[u]+siz[v];
	}
	if(f==0) return 1;
	if(siz[u]==3){
		siz[u]=0;
		ans[++pos]=edge[e].id;
	}
	else if(siz[u]>3){
		return 0;
	}
	return 1;
}
void solve(){
	int u,v;
	pos=0;
	n=read();
	for(int i=1;i<n;i++){
		u=read(),v=read();
		add(u,v,i),add(v,u,i);
	}
	if(n==3){
		printf("0\n\n");
		for(int i=1;i<=n;i++) head[i]=0,ans[i]=0;
		return;
	}
	if(n%3!=0){
		printf("-1\n");
		for(int i=1;i<=n;i++) head[i]=0,ans[i]=0;
		return;
	}
	if(init(1,0)&&ans[n/3-1]){
		cout<<pos<<endl;
		for(int i=1;i<=pos;i++) cout<<ans[i]<<' ';
		cout<<endl;
	}
	else{
		cout<<"-1\n";
	}
	for(int i=1;i<=n;i++) head[i]=0,ans[i]=0;
}
signed main(){
	int T=read();
	while(T--) solve();
	return 0;
}
```

---

## 作者：Zhangikun (赞：3)

## 题意：
给定一颗无根树，删掉若干条边，使得将树分成若干个点数为 $3$ 的连通块。
## 思路：
从小问题往大问题去想，假设当前考虑的点为 $cur$，根节点为 $1$。

如果以 $cur$ 为根节点的子树内有且仅有 $3$ 个结点，我们把它叫做合法子树。
比如：
```
	   cur
	   / \
       儿子1 儿子2

      cur
      /
    儿子
     /
    孙子
```
很显然，这种子树不需要删边。

再稍微复杂一点：
```
        cur
       / | \
    儿子1儿子2儿子3
    /    |     /\
  孙子1 孙子2 孙子3 孙子4
        |
       孙子2的好大儿
```
显然，$cur$ 的子树中以儿子 $2$ 和 $3$ 为根的子树为合法子树，直接劈掉它们和 $cur$ 的边：
```
        cur
       /    
    儿子1 儿子2 儿子3
    /     |      /\
  孙子1  孙子2  孙子3 孙子4
         |
        孙子2的好大儿
```
此时树就被分成了三个合法的连通块。可以总结出来边的劈法：先劈合法的子树，劈不了的留着，看剩余的点数是否为 $3$，如果是，将该树也看作合法子树，再往上一层进行操作。

证明：倘若这样不正确，那么对于一个有且仅有 $3$ 个结点的合法子树就可以被另外的分法切开，而切开后必然会有一部分与该子树的父亲脱连，由于是将合法子树切开，所以两部分必然不为 $3$，一旦与祖先脱节，将再也没有可能将连通块的点数增加。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int cxk=2e5+5;
int n,hd[cxk],init;
vector<pair<int,int>>nbr[cxk];
vector<int>erz_nbr;
void dfs(int cur,int fa)//树形dp，hd[i]表示以i为根节点的子树的节点数量
{
    hd[cur]=1;//初始状态：算上自己
    for(auto p:nbr[cur])
    {
        int nxt=p.first;
        if(nxt==fa)continue;//由于是无向边，不能走到他爹，避免卡死
        dfs(nxt,cur);//先递归下去算出hd[nxt]，再加上
        hd[cur]+=hd[nxt];
    }
}
void dfs2(int cur,int fa)
{
    for(auto p:nbr[cur])
    {
        int nxt=p.first,id=p.second;
        if(nxt==fa)continue;
        if(hd[nxt]==3)//子节点属于第一种合法子树
        {
            erz_nbr.push_back(id);//删边
            hd[cur]-=3;//减少少3个点
            init+=3;//解决3个点
            continue;//解决完了就不用递归了
        }
        hd[cur]-=hd[nxt];//等会dfs2要修改hd[nxt]，减去，修改完后再加上
        dfs2(nxt,cur);
        if(hd[nxt]==3)//修改完之后合法
        {
            erz_nbr.push_back(id);//同上
            init+=3;
            //这里hd[cur]不用减了，前面已经把该子树的点数剪掉了
            continue;
        }
        hd[cur]+=hd[nxt];
    }
}
void help()
{
    cin>>n;
    //初始化------------------------------------
    init=0;
    erz_nbr.clear();
    for(int i=1;i<=n;i++)
    {
        hd[i]=0;
        nbr[i].clear();
    }
    //------------------------------------------
    for(int i=1,x,y;i<n;i++)//连边
    {
        cin>>x>>y;
        nbr[x].push_back({y,i});//把边的编号当边权带入
        nbr[y].push_back({x,i});
    }
    dfs(1,0);//预处理hd
    dfs2(1,0);//执行砍边
    //init表示已经解决的点数
    if(hd[1]==3)//如果根节点剩下的点为3，说明这3点可以被解决掉
    {
        init+=3;//这里就不用删边了，想想为什么
    }
    if(init!=n)return cout<<"-1\n",void();//没解决够n个，无解
    cout<<erz_nbr.size()<<"\n";//输出删除的边数
    sort(erz_nbr.begin(),erz_nbr.end());//也可以不排序
    for(int x:erz_nbr)//for(int i=0;i<erz_nbr.size();i++)
    {                 //{
        cout<<x<<" ";     //cout<<erz_nbr[i]<<" ";                  
    }                 //}
    cout<<"\n";
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    for(cin>>t;t--;)
    {
        help();
    }
}
```


---

## 作者：I_am_sb___ (赞：3)

比赛时做到了此题，特来写个题解。

先考虑骗分，题面中提到，需要将一棵树划分成几个内部有且仅有三个点的连通块，不难发现，由于无法通过操作来改变点的数量，所以只有当 $n \bmod 3 = 0$ 时，才有可能有解，但是由于多测其实这样是骗不了分的。

那么思考有解情况，因为需要将树变成有且仅有三个结点的连通块，所以可以想到从叶子结点从下往上删以此的方法

定义 $size_{i}$ 表示 $i$ 的子树**还未被删除结点的个数**：

当 $size_{i} < 3$ 时，继续往上递归；

当 $size_{i} = 3$ 时，直接将 $i$ 结点于其父亲的边删掉，然后再将 $size_{i}$ 更新为 $0$；

当 $size_{i} > 3$ 时看上去是比较难想的情况，但是其实非常简单，会发现只有以下 $3$ 种情况（手绘勿喷）：
    ![屏幕截图 2023-07-11 121031.png](https://img1.imgtp.com/2023/07/11/lK7I8uUv.png)
    就不难看出，我们无法将这种情况分成有且仅有三个点的连通块，于是可以得出，当递归到 $size_{i}>3$ 的情况时，只需要判为无解即可；
    
code：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>

#define mp make_pair
#define PII pair<int , int>

using namespace std;

template<typename T>inline void read(T &FF){
	T RR=1;FF=0;char CH=getchar();
	for(;!isdigit(CH);CH=getchar())if(CH=='-')RR=-1;
	for(;isdigit(CH);CH=getchar())FF=(FF<<1)+(FF<<3)+(CH^48);
	FF*=RR;
}

template<typename T>inline void write(T x){
	if(x<0)putchar('-'),x*=-1;
	if(x>9)write(x/10);
	putchar(x%10+48);
}

const int N = 200007;
const int inf = 1 << 31;
const int mod = 1e9 + 7;

int n , siz[N];
int head[N] , idx;
bool flag;
bool st[N];
struct edge
{
	int ne , to , id;
} e[N << 1];

void add(int a , int b , int c)
{
    e[idx] = {head[a] , b , c};
	head[a] = idx;
    ++ idx;
}

void DFS(int u , int fa)
{
	if(!flag) return;
	int t = 0;
	for(int i = head[u] ; i != -1 ; i = e[i].ne)
	{
    	if(e[i].to == fa) t = e[i].id;
		else 
        {
            DFS(e[i].to , u);
            siz[u] += siz[e[i].to];
        }
    }
	++ siz[u];
	if(siz[u] == 3) siz[u] = 0 , st[t] = true;
	else if(siz[u] > 3) flag = false;
}

int main(){
    int T;
	read(T);
	while(T --)
    {
        idx = 0;
        memset(head , -1 , sizeof(head));
        memset(siz , 0 , sizeof(siz));
        memset(st , 0 , sizeof(st));
        memset(e , 0 , sizeof(e));
		read(n);
        int a , b ,c;
		for(int i = 1 ; i < n ; ++ i)
        {
			read(a);read(b);
            add(a , b , i);
            add(b , a , i);
        }
		flag =! (n % 3);
		DFS(1 , 0);
		if(!flag) puts("-1");
		else
        {
			write(n / 3 - 1);
            puts("");
			for(int i = 1 ; i < n ; ++ i) if(st[i]) write(i) , putchar(' ');
			puts("");
		}
	}
	return 0;
}
```

---

## 作者：Yun_Mengxi (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1833G)

## 题意

给定一棵树，问能不能每三个一组，分成若干组。

## 分析

首先，$n\not\equiv0\pmod3$，显然是无解的，然后，对于 $n\equiv0\pmod3$，分类讨论一下：

- 对于树上任意结点 $u$，我们设 $sz_u$ 为以 $u$ 为根的子树大小，对于 $sz_u$，有如下 $3$ 种情况：

 1. $sz_u < 3$，那么暂时不用干，因为 $u$ 之上还会有子树。

 2. $sz_u = 3$，那么直接令 $sz_u \gets 0$，删的边加上一条。

 3. $sz_u > 3$，充分发扬人类智慧一下，分成三种情况：
 
 ![](https://cdn.luogu.com.cn/upload/image_hosting/xeikwc89.png)
 
 如果将任意三个点划为一个连通块，剩下的节点肯定无解。
 
而删除的边数也很显然，肯定有 $\dfrac{n}{3}-1$ 条。
 
## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 2e5 + 5;

int t;
int n;
int cnt, fla;
int head[kMaxN];
int sz[kMaxN];
bool vis[kMaxN];

struct edge {
  int nxt, to, id;
} e[kMaxN << 1];

void add(int u, int v, int w) {
  e[++cnt].nxt = head[u];
  e[cnt].to = v;
  e[cnt].id = w;
  head[u] = cnt;
}

void dfs(int step, int father) {
  if (!fla) return;
  int f = 0;
  for (int i = head[step]; i; i = e[i].nxt)
    if (e[i].to == father) {
      f = e[i].id;
    } else {
      dfs(e[i].to, step);
      sz[step] += sz[e[i].to];
    }
  sz[step]++;
  if (sz[step] == 3) {
    sz[step] = 0, vis[f] = 1;
  } else if (sz[step] > 3) {
    fla = 0;
  }
}

int mian() {
  for (int i = 1; i <= n; i++) {
    head[i] = sz[i] = vis[i] = 0;
    e[(i << 1) - 1] = e[i << 1] = {0, 0, 0};
  }
  cin >> n;
  cnt = 0;
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    add(u, v, i);
    add(v, u, i);
  }
  fla = !(n % 3);
  dfs(1, 0);
  if (!fla) {
    cout << "-1\n";
  } else {
    cout << n / 3 - 1 << '\n';
    for (int i = 1; i < n; i++) {
      if (vis[i]) {
        cout << i << ' ';
      }
    }
    cout << '\n';
  }
  return 0;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    mian();
  }
  return 0;
}
```

$$\text{-EOF-}$$

---

## 作者：_GW_ (赞：2)

## 思路

考虑树形 dp。

对于每条输入的边，建立无向图，注意要存储边的编号，便于输出。

然后预处理出每个节点以此节点为根的子树大小。

最后再树形 dp。对于一个节点，枚举它的每颗子树，若它的此棵子树大小正好为 $3$，直接把此节点的子树大小减去 $3$，把连接它和它的子树的边的编号打到答案数组里面。

否则就先处理它的此棵子树，然后再看子树大小是否为 $3$。

同时每次砍边的时候要更新一下此时已经把多少个节点给砍掉了，记为 $res$。

最后 dp 完之后要特判一下包含根节点在内是否还有一颗大小为 $3$ 的树，若有，最后再更新一下 $res$。

如果 $res=n$，输出答案数组，否则就是无解

## code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int a[N],ans[N],len,b[N],num,val,si[N],n,m,k,res,T;
vector<pair<int,int> > v[N];
void ikun(int u,int fa)//计算以此节点为根的子树大小 
{
    si[u]=1;
    for(pair<int,int> i:v[u])
    {
        if(i.first==fa) continue;
        ikun(i.first,u);
        si[u]+=si[i.first];
    }
}
void dfs(int u,int fa)//树形dp 
{
    for(pair<int,int> i:v[u])
    {
        if(i.first==fa) continue;
        if(si[i.first]==3)
        {
            si[u]-=3;
            res+=3;
            ans[++len]=i.second;
            continue;
        }
        si[u]-=si[i.first]; 
        dfs(i.first,u);
        if(si[i.first]==3)
        {
            res+=3;
            ans[++len]=i.second;
            continue;
        }
        si[u]+=si[i.first];
    }
}
int main()
{
    cin>>T;
    while(T--)
    {
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            v[i].clear();
            si[i]=0;
        }
        res=0;
        len=0;
        for(int i=1,x,y;i<n;i++)
        {
            cin>>x>>y;
            v[x].push_back({y,i});
            v[y].push_back({x,i});
        }
        ikun(1,-1);
        dfs(1,-1);
        if(si[1]==3)
        {
        	res+=3;
        }
        if(res==n)
        {
            cout<<len<<endl;
            for(int i=1;i<=len;i++)
            {
                cout<<ans[i]<<" ";
            }
            cout<<endl;
        }
        else
        {
            cout<<-1<<endl;
        }
    }
    return 0;
}
```


---

## 作者：yangruoyi (赞：2)

题目大意：给定一棵树，问能否通过删除若干条边，使得剩下来的每个连通块大小都为 $3$。

首先 DFS，求出每个子树的大小，并求出它的子树中余数为 $0,1,2$ 的子树个数。
```cpp
ll dfs(ll x){
    zs[x]=1;
    for(int i=head[x];i!=0;i=nxt[i])
        if(edge[i]!=fa[x]){fa[edge[i]]=x;ll y=dfs(edge[i]);tj[x][y%3]++;zs[x]+=y;}
    return zs[x];
}
```
显然一颗树只有大小是 $3$ 的倍数的时候，才能被分割。

再深搜一遍（`dfs2`）。对于一个子树 $A$（节点个数为 $S$）：

1. $3|S$，将它与它的父亲切断。

以题中最下面的图为例，对于以 $7$ 为根的子树，将边 $8$ 删掉。

2. $S\equiv 1 \pmod 3$，那么它的根节点与它的父亲连，将它与它的子树切断。
```cpp
if(zs[y]%3==1){//zs[y] 表示以 y 为根的子树的大小。
	for(int j=head[y];j!=0;j=nxt[j])
		if(fa[edge[j]]==y){
			if(!dfs2(edge[j]))return 0;//无法成立。
			else b[j>>1]=1;//用前向星建边且初始时 tot=1,所以 j>>1 就是边的编号。
		}
}
```

3. $S\equiv 2 \pmod 3$，那么它的根节点和它的子树中的一点与父亲连。由于切断根节点后，所有子树都不连通。所以当且仅当它的子树中有且仅一个子树 $B$ 大小 $\equiv 1 \pmod 3$，其余子树的大小是 $3$ 的倍数时，将 $B$ 的根节点和 $A$ 的根节点与 $A$ 的根节点的父亲相连。

如图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/xdb3qafe.png)

```cpp
                if(tj[y][1]!=1||tj[y][2]!=0)return 0;//tj[y][a] 表示 y 节点的子树中大小除以 3 余数是 a 的子树的个数。
                for(int j=head[y];j!=0;j=nxt[j])
                    if(edge[j]!=fa[y]){
                        if(zs[edge[j]]%3==0){
                            if(fa[edge[j]]==y){
                                if(!dfs2(edge[j]))return 0;
                                else b[j>>1]=1;    
                            }                 
                        }
                        else{
                            ll z=edge[j];
                            for(int k=head[z];k!=0;k=nxt[k])
                                if(fa[edge[k]]==z){
                                    if(!dfs2(edge[k]))return 0;
                                    else b[k>>1]=1;
                                }
                        }
                    }
```

主函数里注意：`memset` 会 TLE。

---

## 作者：foryou_ (赞：0)

首先，若 $n \bmod 3 \neq 0$，则一定无解。

考虑 $n \bmod 3 = 0$ 的情形：

首先肯定是先进行一遍树形 dp，求出树上每个节点 $x$ 的子树大小 $size_x$。

若当前节点的 $size$ 值 $=3$，则说明需要切断当前节点于其父节点的连边，使得其子树成为一个大小为 $3$ 的单独连通块。

于是将 $cut_{id}$（$cut_i$ 表示第 $i$ 条边是否需要切断，$id$ 表示当前节点与其父节点连边的编号）设为 $1$，并且为了方便接下来的处理，将 $size_x$ 设为 $0$ 即可。

否则说明这颗子树无法贡献答案的，直接递归回溯即可。

注意多测清空！

核心代码：

```cpp
//树形dp
void dfs(int x,int pre){ //pre是x的父节点
	sz[x]=1;
	if(!ans) return; //无法贡献答案就递归回溯
	int nid=0;
	for(auto i:G[x]){
		if(i.to==pre) nid=i.id; //记录父节点
		else dfs(i.to,x),sz[x]+=sz[i.to]; //求子树大小
	}
	if(sz[x]==3) sz[x]=0,cut[nid]=1; //切断x和pre间的连边
	else if(sz[x]>3) ans=0; //这颗子树无法贡献答案
}
```

---

## 作者：xujunlang2011 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1833G)

## 思路

首先每个联通块有且仅有 $3$ 个结点，所以对于 $n\bmod 3\ne0$ 可以直接输出 $-1$。

然后我们以任意一个点为根，直接 `dfs`，先搜到叶子节点，然后开始回溯。记$siz_i$为回溯到节点 $i$ 时的子节点的 $siz$ 之和加 $1$，叶子节点的 $siz$ 为 $1$。

在回溯的过程中，当一个节点 $i$ 的所有儿子的 $siz$ 和为 $3$ 时，将 $siz_i$ 减 $3$，并记录节点 $i$ 与节点 $i$ 的父亲的连边。当一个节点 $i$ 的所有儿子的 $siz$ 和大于 $3$ 时，直接退出搜索，并输出 $-1$。

搜索完之后直接输出答案即可。

还有，多组数据，记得清空。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int t, n, cnt, sum, s[N][3], hc[N], r[N];
bool F = 0;
struct node
{
    int p, q, h, k;
}a[N * 2];
void add(int p, int q, int kkk)
{
    a[++cnt].p = p;
    a[cnt].q = q;
    a[cnt].h = hc[p];
    a[cnt].k = kkk;
    hc[p] = cnt;
}
int dfs(int k, int fa)
{
    if (F)
    {
        return 0;
    }
    int num = 1, l;
    for (int i = hc[k];i != 0;i = a[i].h)
    {
        if (a[i].q != fa)
        {
            num += dfs(a[i].q, k);
        }
        else
        {
            l = a[i].k;
        }
    }
    if (num == 3)
    {
        if (k != 1)
        {
            r[++sum] = l;
        }
        num -= 3;
    }
    if (num >= 3)
    {
        F = 1;
    }
    return num;
}
int main()
{
	cin >> t;
	for (int ti = 1;ti <= t;ti++)
	{
	    cin >> n;
	    for (int i = 1;i < n;i++)
	    {
	        cin >> s[i][1] >> s[i][2];
	    }
	    if (n % 3 != 0)
	    {
	        cout << "-1\n";
	        continue;
	    }
        for (int i = 1;i < n;i++)
	    {
	        add(s[i][1], s[i][2], i);
	        add(s[i][2], s[i][1], i);
	    }
	    dfs(1, 1);
	    if (F)
	    {
	        F = 0;
	        cout << "-1\n";
	    }
	    else
	    {
	        cout << sum << "\n";
	        sort(r + 1, r + sum + 1);
	        for (int i = 1;i <= sum;i++)
	        {
	            cout << r[i] << " ";
	        }
	        cout << "\n";
	    }
	    cnt = sum = 0;
	    for (int i = 1;i <= n;i++)
	    {
	        hc[i] = 0;
	    }
	}
	return 0;
} 
```

---

## 作者：UniGravity (赞：0)

## Solution CF1833G Ksyusha and Chinchilla
~~克修沙和毛丝鼠？（赞美机翻）~~

### 题意简述
在一棵树上删去一些边，使得形成的几个连通块，都**有且仅有** $3$ 个结点。

### 题目思路
首先对于已经删去的点，我们就不用考虑它与主树（以 $1$ 为根节点的树）的关系。

那么对于以 $i$ 为根节点的子树，我们可以记录其大小为 $s_i$，分为以下情况：

* 当 $s_i<3$ 时，此时无法删去，我们保留这条边。
* 当 $s_i=3$ 时，注意到刚好凑成一个 $3$ 个点的连通块，我们删去 $i$ 到 $i$ 的父节点这条边，删去后大小 $s_i\gets0$。
* 当 $s_i>3$ 时，可以证明无解，具体思路如下：  
首先由于不相关的节点已经被删去，$i$ 的子节点 $j$ 满足 $s_j<3$。    
我们删去 $j$ 的子树和 $i$，根节点被删去，路径中断，由于 $s_i>3$，此时仍有剩下的节点无法连通，因此无解。   

------------
发现 $s_i$ 只与子节点有关，我们不用开数组存 $s_i$，直接将其作为函数的返回值即可。
```cpp
int dfs(int x, int fa) {
    int sz = 1; // s_i
    int res, y, faedge = 0; // 需要删去的边
    for (int i = 0; i < edge[x].size(); i++) {
        y = edge[x][i].first;
        if (y == fa) {
            faedge = edge[x][i].second;
            continue;
        }
        
        res = dfs(y, x);
        if (res == -1) return -1;
        sz += res;
    }
    
    if (sz < 3) return sz;
    else if (sz == 3) { // 删去边
        del[faedge] = true;
        cnt++;
        return 0;
    }
    else return -1; // 无解
}
```

### 完整代码
代码实现起来~~虽然不难，但是容易~~。   
[提交记录](https://www.luogu.com.cn/record/list?pid=CF1833G&user=582360)
```cpp
#include <bits/stdc++.h>
using namespace std;

vector< pair< int, int > > edge[200005];
bool del[200005];
int cnt;
int t, n;

int dfs(int x, int fa) {
    int sz = 1;
    int res, y, faedge = 0;
    for (int i = 0; i < edge[x].size(); i++) {
        y = edge[x][i].first;
        if (y == fa) {
            faedge = edge[x][i].second;
            continue;
        }
        
        res = dfs(y, x);
        if (res == -1) return -1;
        sz += res;
    }
    
    if (sz < 3) return sz;
    else if (sz == 3) {
        del[faedge] = true;
        cnt++;
        return 0;
    }
    else return -1;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        memset(del, 0, sizeof(del));
        for (int i = 1; i <= n; i++) {
            edge[i].clear();
        }
        int x, y;
        for (int i = 1; i < n; i++) {
            scanf("%d %d", &x, &y);
            edge[x].push_back({y, i});
            edge[y].push_back({x, i});
        }
        
        if (n % 3) {
            printf("-1\n");
            continue;
        }
        
        cnt = 0;
        int res = dfs(1, 0);
        if (res != 0) {
            printf("-1\n");
            continue;
        }
        
        printf("%d\n", cnt - 1);
        for (int i = 1; i < n; i++) {
            if (del[i]) printf("%d ", i);
        }
        printf("\n");
    }
    return 0;
}
```

---

## 作者：Po7ed (赞：0)

**[题目传送门](https://www.luogu.com.cn/problem/CF1833G)**

### 题意简介

在一棵树上删去一些边，使得形成的几个连通块，都**有且仅有** $3$ 个结点。

多个答案时仅需输出任意一个。

每个测试点有多组测试数据。

### 解法

#### 思路

首先注意到每个连通块都有且仅有 $3$ 个结点，所以节点数 $n$ 必须是 $3$ 的倍数。可以先特判。

考虑有解时，我们可以从下往上进行断边操作，可用 dfs 实现。
具体见 _算法流程_。 

#### 算法流程

- 记 $siz_i$ 为当前节点的子树中**未被切断为单独的连通快**的节点个数（有点绕）。换句话说，**不经过断开的边**所能到达的子树中的节点的个数。如下图，红色边为应断开的边，

![花了我半小时](https://cdn.luogu.com.cn/upload/image_hosting/u3c2jv48.png)


|   $i$   | $1$  | $2$  | $3$  | $4$  | $5$  | $6$  | $7$  | $8$  | $9$  |
| :-----: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| $siz_i$ | $3$  | $2$  | $3$  | $1$  | $3$  | $2$  | $1$  | $1$  | $1$  |

可以自行理解一下。

- 计算 $siz_i$：将各个调用的返回值累加。
- $siz_i$ 可分以下情况：（记 $pre$ 为 $i$ 的父亲。）
  - 当 $siz_i=3$ 时，断开边 $(i,pre)$。同时返回 $0$ 表示没有未被切断的节点（都被切断了）。
  - 当 $siz_i<3$ 时，还不够一个连通块的节点数量 $3$，所以返回 $siz_i$。
  - 当 $siz_i>3$ 时，节点数量太多，输出 $\texttt{-1}$，结束。
- 返回到主函数后，若返回值为 $0$，则有解，输出解。否则输出 $\texttt{-1}$，结束。

#### 代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct edge
{
	int v,id;
};

vector<edge> del;//记录删除的边
vector<edge> e[200001];//边表


int dfs(int now,int pre)
{
	int siz=1;
	edge tofa;
	for(edge to:e[now])//遍历所有连边
	{
		if(to.v!=pre)
		{
			siz+=dfs(to.v,now);//累加返回值
		}
		else
		{
			tofa=to;//标记与父亲连的边
		}
	}
	if(siz==3)//判断siz
	{
		if(pre!=-1)//特判，如果是根节点（1号），它没有父亲，不能删除与父亲连的边，不然会出错
		{
			del.push_back(tofa);
		}
		return 0;
	}
	else if(siz<3)
	{
		return siz;
	}
	else
	{
		// puts("-1");不能直接输出-1，因为不能退出程序，也无法直接回到main函数
		return 0x3f3f3f3f;//让返回值极大，导致在主函数的特判中判定为无解
	}
	return 114514;//没用的，只是为了让编译器不报错
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		del.clear();//清除上一次的记录
		// fill(vtoid,vtoid+n+1,0);
		int n;
		scanf("%d",&n);
		int u,v;
		if(n%3)
		{
			puts("-1");
			for(int i=1;i<n;i++)
			{
				scanf("%d %d",&u,&v);
			}
			continue;
		}
		for(int i=1;i<=n;i++)
		{
			e[i].clear();
		}
		for(int i=1;i<n;i++)
		{
			scanf("%d %d",&u,&v);
			e[u].push_back({v,i});
			e[v].push_back({u,i});
		}
		if(!dfs(1,-1))//特判，如果返回值为0，则完美分配了所有节点。反之没有，就无解。
		{
			printf("%d\n",del.size());
			for(edge d:del)
			{
				printf("%d ",d.id);
			}
			puts("");
		}
		else
		{
			puts("-1");
		}
	}
	return 0;
}

```

---

