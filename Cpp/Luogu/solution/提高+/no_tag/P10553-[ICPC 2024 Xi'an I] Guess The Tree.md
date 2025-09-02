# [ICPC 2024 Xi'an I] Guess The Tree

## 题目描述

有一个满二叉树，具有 $n$ 层（因此它恰好有 $2^n-1$ 个节点）。每个节点都有一个从 $1$ 到 $2^n-1$ 的整数 ID，这 $2^n-1$ 个 ID 形成一个从 $1$ 到 $2^n-1$ 的排列，但你并不知道具体的排列。

你需要通过最多 $4800$ 次查询找到这 $2^n-1$ 个节点的 ID。

## 说明/提示

在这个例子中，树的根是 $3$，它的两个儿子是 $1$ 和 $2$。

对于任何查询 "? a b"，如果 $a
eq b$，评测系统将返回答案 $3$。

因此我们找到了树的根是 $3$。（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
2

3

3

3```

### 输出

```

? 1 2

? 2 3

? 1 3

! 3 3 -1```

# 题解

## 作者：_LiWenX_ (赞：2)

场上差 $10$ 秒首 A 这个题，无语了。

赛时做法。

这种完全二叉树的问题考虑分治递归处理。

首先考虑在树上随一个点，查询所有点与它的 $\operatorname{lca}$ 可以得到什么。

不难发现可以得到它的所有祖先，设祖先 $u$ 的出现次数 $t_u$，如果我们对这些祖先按照 $t$ 排序，显然就可以把它们在树上的深度固定，我们就确定出了树上的一条链了。

不仅如此，我们还可以知道每一个节点在哪个祖先的子树当中，这样就比较好递归处理了。

唯一的问题是，考虑我们最开始随出来的点 $s$，如果 $s$ 不是叶子节点，它的子树扣掉了这个点，并不是一个完全二叉树了，其实这并不好处理，而随机出 $s$ 为叶子的概率只有 $\dfrac{1}{2}$，如何保证必然可以得到一个叶子呢。

注意到，假如我们最开始随出来的是 $s$，对于枚举的一个 $i$，若 $\operatorname{lca}(s,i)=s$，我们可以通过把 $s$ 变成 $i$，不断的迭代，就必然可以保证 $s$ 成为叶子节点，再套用刚刚的做法就可以过了。

实现的时候可以稍微精细化一点，比如对于 $3$ 个点的完全二叉树，可以查询一次解决（直接一次找出它的根）。

貌似 $n=10$ 的时候，这个做法询问次数固定为 $4480$ 次，有点厉害。

```cpp
#include<bits/stdc++.h>
using namespace std;
int ask(int x,int y){
	cout<<"? "<<x<<' '<<y<<endl;
	int ret;cin>>ret;
	return ret;
}
int fa[1<<10],siz[1<<10];
bool vis[1<<10];
bool cmp(int x,int y){
	return siz[x]>siz[y];
}
vector<int> nxt[1<<10]; 
int n;
void solve(vector<int> vec,int F){
	if(vec.size()<=2){
		for(int u:vec) fa[u]=F;
		return ;
	}
	if(vec.size()==3){
		int lca=ask(vec[0],vec[1]);
		fa[lca]=F;
		for(int u:vec){
			if(u==lca) continue;
			fa[u]=lca;
		}return ;
	}
	int s=vec[0];
	map<int,bool> ma;
	for(int i=1;i<(int)vec.size();i++){
		int lca=ask(s,vec[i]);
		if(lca==s) s=vec[i];
		fa[vec[i]]=lca;
		siz[lca]++;
		ma[lca]=1;
	}
	vector<int> l;
	for(auto u:ma){
		if(u.first==s) continue;
		l.push_back(u.first);
	}
	sort(l.begin(),l.end(),cmp);
	fa[l[0]]=F;
	for(int i=1;i<(int)l.size();i++){
		fa[l[i]]=l[i-1];
	}fa[s]=l.back();
	for(int u:l) vis[u]=1,nxt[u].clear();vis[s]=1,nxt[s].clear();
	for(int u:vec){
		if(vis[u]) continue;
		nxt[fa[u]].push_back(u);
	}
	for(int u:l){
		solve(nxt[u],u);
	}solve(nxt[s],s);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n;n=(1<<n)-1;
	vector<int> vec;
	for(int i=1;i<=n;i++){
		fa[i]=-1;
		vec.push_back(i);
	}
	solve(vec,-1);
	cout<<"! ";
	for(int i=1;i<=n;i++){
		cout<<fa[i]<<" ";
	}
}
```

---

## 作者：SSHHXD (赞：1)

# 题意
是一道交互题，要去猜一颗**满二叉树**。

给定树的深度 $n(1 \le n \le 10)$。  
结点的编号是 $1 \sim 2^{n}-1$ 的排列。 

你可以询问节点 $u,v$ 的最近公共祖先至多 $4800$ 次。最后要输出每个节点的父节点的编号。根节点父节点编号为 $-1$。

# 题解
给出一种我自己想出来的方法。能过。
## 概述

求出树的根节点，找到左子树节点集合，右子树节点集合，并递归树的左右子树，找到左右子树的根节点，则这两个根节点的父节点就是根节点。以此类推，可以求得每颗子树的根节点以及其父节点，再进行优化就可以了。

## 详细做法
首先可以特判，当 $n=1$ 时，只有根节点，答案就是 $-1$。

**Step.1**

对于 $n=2$ 的树，随便选取树上的两个点 $u,v$，查询其最近公共祖先 $f$，这一定是这棵树的根节点。剩下两个节点的父节点便是 $f$。这需要耗费 $1$ 次机会，就结束了。

对于 $n > 2$ 的树，首先选取一个**不是根节点的节点** $u$。选取的方法是这样：在树上任取两个不同的节点，查询其最近公共祖先，与最近公共祖先节点编号不相同的节点，一定不可能是树的根节点。  

**Step.2**

接下来就要通过这个不是根节点的节点 $u$ 去寻找这棵树的根节点。  
让 $u$ 对这个树中所有的节点 $i$ 都求一个最近公共祖先。因为是满二叉树，可以知道会有超过一半的得到的最近公共祖先都会是根节点。说明如下：  
不妨假设 $u$ 在左子树（相对的，在哪个子树都没有影响，因为是一颗满二叉树，左右子树节点个数相同），那么 $u$ 就会与左子树的节点，根节点以及右子树的节点进行求最近公共祖先。  
枚举 $i$（树中的所有节点）:  
+ 当 $i$ 在左子树时，得到的最近公共祖先 $f$ 也会在左子树；   
+ 当 $i$ 在右子树时，得到的最近公共祖先 $f$ 一定是根节点；  
+ 当 $i$ 是根节点时，得到的最近公共祖先 $f$ 自然是根节点。  

左右子树节点个数相同，此时得到最近公共祖先的次数就是 $2^{n-1}-1$，当 $i$ 是根节点的还会再多一个。用式子表示就是  $2^{n-1}$ 个 $f$ 都会是根节点，超过了一半，可以记录每个 $f$，出现次数最多的 $f$ 就是根节点。

上述，我们就求出了根节点。

**Step.3**

接下来，以 $u$ 为参照点，枚举 $i$。那么 $i$ 和 $u$ 的最近公共祖先 $f$ 如果不是根节点，则这两个节点是在同一个子树（左子树）的。如果是根节点，则说明节点 $i$ 在另一个子树（右子树）。

这样就得到了左子树和右子树的节点集合。

**Step.4**

接着，对左子树，右子树递归进行 Step.1 ~ Step.3 的操作。递归过程中，每次带着这棵树的根节点 $r$ 来递归左右子树，在得到子树根后，就可以直接得到这个子树根的父亲是 $r$。

递归完后，每个节点的父亲也就得到了。这题就做完了...吗？

正确地写完代码后，不难发现，有一些点会 [WA](https://www.luogu.com.cn/record/list?pid=P10553&user=SSHHXD&page=2)。  
原因是，题目只允许访问最近公共祖先 $4800$ 次。而对于每颗子树，我们都询问了 树的节点个数 次最近公共祖先。

这个时候，我们做法的时间复杂度大致是接近 $O(n\times 2^n)$ 的（如有错误请指出）。

在 $n\le 9$ 的情况下，或许可以勉勉强强过去，但是一旦到了 $n=10$，询问次数就要超过 $10000$ 了。**需要优化**。

## 优化
**First**

可以发现，我们在求 $u$ 与 $v$ 的最近公共祖先的时候，难免会出现重复询问的情况。而节点个数是不会超过 $1023$ 的，所以可以建立一个数组存储询问过的答案。在再次询问前，先看看是否询问过了，调用询问过的，就不必再浪费那么多机会了。

还有一个显然的是，当 $u=v$ 的时候，其最近公共祖先一定是 $u$（$v$ 也可以）。可以提前预处理出来。

以及，$u,v$ 的最近公共祖先和 $v,u$ 的最近公共祖先肯定是相同的。这个要储存下来。

很好，这个时候，$n=10$ 的询问次数已经下降到 $6000$ 左右的量级了。但是还是过不了。。还需要进一步优化。

**Second**

在 Step.1 中，我们用了一次机会去找到一个 $n=2$ 的树的根节点 或 选取一个 $n>2$ 的树的非根节点的点。

实际上，我们可以大胆的暴力枚举整棵树的节点集合，寻找有记录过最近公共祖先的两个点。这样就可以省掉一次机会。当然，如果没找到，那还是不可避免地得花费一次机会询问。

**Thrid**

在 Step.2 中，我们发现我们在枚举 $i$ 的时候会花费至多 树的节点个数 次机会。能否少用一次机会呢？能！

对于某一个没有被询问过最近公共祖先的 $i,u$，我们不查了。但是这个不查的机会只会有一次。  
而后，我们知道是满二叉树，所以左子树节点个数和右子树节点个数应当是相同的。而少一个节点没查，最终找出的左右子树节点集合必然会出现其中一个子树节点个数相对较少，那么没查的这个点 $i$ 就是节点个数较少的子树少了的那个点。加进去即可。

这样做，查树根的时候不会收到影响吗？  
会！

![](https://cdn.luogu.com.cn/upload/image_hosting/m8f61o5a.png)

对于这颗树，忽略红框框的 $v$，选取的节点为 $u$，那么实际上就可以发现，此时查询得到的 $f$ 的出现次数最多的（3次）不仅有根节点 $1$，也有 $u$。

对于这个，我们可以有两种处理方式：  
1. 当 $i=u$ 时，跳过，不计入次数。  
2. 因为 $u$ 选取时就注定了其必然不是根节点，所以出现次数最多中出现的 $u$ 的必然不是根节点。

可以说明，根节点一定出现次数最多，$u$ 的出现次数小于或等于根节点的出现次数，不会有其他节点出现次数最多。

好。又省掉了一点查询的次数。。

提交：[AC](https://www.luogu.com.cn/record/161025464) 啦！

下面放代码。
# 代码
```cpp
#include <bits/stdc++.h>
#define N 2020
using namespace std;
struct info{
	int u,v,anser;
}answ[N][N];
int rt[N],fa[N],n,u,v,ans,p,rght[N][N],lft[N][N],tot,rtcnt,times,cnt,vis[N][N],f[N][N],mx,tanss;
/*
times是用来查询问了多少次的,tot递归到了第几课树
rt存根节点的数组，fa存u节点的父节点的编号的数组，
n树的层数，p这棵树节点的个数，rght节点u的右子树节点集合，
lft节点u的左子树的节点集合，vis记录询问过的u和v的最近公共祖先的集合
f记录在第i棵树第j个节点出现次数，mx记录出现次数最大值
*/

void query(int u,int v){
	times++;
	cout<<"? "<<u<<" "<<v<<endl;
}
int get_a_rand(int u,int v){//随便选两个点
	if(!vis[u][v]){
		times++;
		cout<<"? "<<u<<" "<<v<<endl;
		cin>>ans;
		vis[u][v]=ans;
		vis[v][u]=ans;
	}
	else ans=vis[u][v];
	if(ans==v)return u;//Step.1
	return v;
}
int get_a_rand2(int u,int v){//随便选两个点
	if(vis[u][v])return vis[u][v];
	times++;
	cout<<"? "<<u<<" "<<v<<endl;
	cin>>ans;	
	vis[u][v]=ans;
	vis[v][u]=ans;
	return ans;
}
void getrts(int n,int father,int* lis){
	int p=pow(2,n)-1;
	int j;
	tot++;
	if(n==2){//n=2情况，直接枚举
		if(vis[lis[1]][lis[2]]){
			j=vis[lis[1]][lis[2]];
		}else if(vis[lis[2]][lis[3]]){
			j=vis[lis[2]][lis[3]];
		}else if(vis[lis[1]][lis[3]]){
			j=vis[lis[1]][lis[3]];
		}//优化Second
		else j=get_a_rand2(lis[1],lis[2]);
		
		fa[lis[1]]=j;
		fa[lis[2]]=j;
		fa[lis[3]]=j;
		fa[j]=father;
		return;
	}
	
	int flag=0;
  //下面开始优化Second，枚举找到记录过的点
	for(int kk=1;kk<=p;kk++){
		for(int kk2=1;kk2<=p;kk2++){
			if((kk!=kk2)&&(vis[lis[kk]][lis[kk2]])){
				j=vis[lis[kk]][lis[kk2]];
				if(j==lis[kk])j=lis[kk2];
				else j=lis[kk];
				flag=1;
				break;
			}
		}
		if(flag)break;
	}
	if(!flag)j=get_a_rand(lis[1],lis[2]);
  //如果没找到，只能选取两个点进行询问。
	cnt=0;
	answ[tot][++cnt].anser=j;
	answ[tot][cnt].u=j;
	answ[tot][cnt].v=j;
	flag=0; 
	for(int k=1;k<=p;k++){
		int i=lis[k];//取树集合中的点
		if(i==j)continue;//优化Thrid，忽略i=u情况
		
		if(!vis[i][j]){
			if(!flag){
				flag=i;
				answ[tot][++cnt].u=i;
				continue;
			}
			query(i,j);
			cin>>ans;
			vis[i][j]=ans;
			vis[j][i]=ans;//优化First，记录询问过的
		}else ans=vis[i][j];
		answ[tot][++cnt].anser=ans;
		answ[tot][cnt].u=i;
		answ[tot][cnt].v=j;
		f[tot][ans]++;
	}
	mx=0;
	for(int i=1;i<=p;i++){
		if(f[tot][lis[i]]>mx){
			mx=f[tot][lis[i]];//找最多出现次数
			tanss=lis[i];
		}
	}
	rt[tot]=tanss;//得到根了，下面找左右子树
	for(int i=1;i<=p;i++){
		if(answ[tot][i].u==flag)continue;
		if(answ[tot][i].anser==rt[tot]&&answ[tot][i].u!=rt[tot]){
			lft[rt[tot]][++lft[rt[tot]][0]]=answ[tot][i].u;
		}else if(answ[tot][i].u!=rt[tot]){
			rght[rt[tot]][++rght[rt[tot]][0]]=answ[tot][i].u;
		}//分别放到左子树和右子树中
	}
  //下面是优化Thrid
	if(flag){
		if(lft[rt[tot]][0]<rght[rt[tot]][0])lft[rt[tot]][++lft[rt[tot]][0]]=flag;
		else if(lft[rt[tot]][0]>rght[rt[tot]][0])rght[rt[tot]][++rght[rt[tot]][0]]=flag;
	}
	flag=0;
  
	fa[rt[tot]]=father;
  
	int gg=rt[tot];
	getrts(n-1,gg,lft[gg]);//递归下去
	getrts(n-1,gg,rght[gg]);
	
}
int main(){
	fflush(stdout);
	cout.flush();
	cin>>n;
	if(n==1){
		cout<<"! -1"<<endl;
		return 0;
	}//n=1特判
	
	if(n==2){
		cout<<"? 1 2"<<endl;//随便选两个点都行
		cin>>ans;
		fa[1]=ans;
		fa[2]=ans;
		fa[3]=ans;
		fa[ans]=-1;
		cout<<"! "<<fa[1]<<" "<<fa[2]<<" "<<fa[3]<<endl;
		return 0;
	}//n=2特判
  
	int rttree[N];int p=pow(2,n)-1;
	for(int i=1;i<=p;i++)rttree[i]=i;//树的节点列表
	getrts(n,-1,rttree);//开始递归整个树

	while(times>4800)cout<<1;//报警用的
	cout<<"! ";
	for(int i=1;i<=p;i++)cout<<fa[i]<<" ";
	return 0;
}

```

---

## 作者：win114514 (赞：1)

挺有意思的题。

### 思路

考虑一个比较自然的做法。

我们每次对于一棵树，我们将它的某一条链抽出来。

这样，我们只需要知道这颗树的所有节点与链底的 $\text{lca}$，就可以知道它是属于这条链上哪一个节点的下面。

然后就可以递归处理。

由于交互库不是自适应的。

我们可能可以想到随机一个点。

求出这个点与整颗树的 $\text{lca}$。

求出 $\text{lca}$ 之后，我们一定可以知道这个节点一直到根的链是哪些点，以及他们的父子关系，这个有很多求法，我采用的是按子树大小排序。

这样，我们就已经得到了一个比较优秀的做法。

精细实现后可以做到 $4700\sim 5000$ 次操作。

但是这个还过不了，因为它的操作次数过于随机，经常会变成 $4900\sim 5000$。

我们需要更加好的做法。

考虑什么时候对树的划分最为完全。

一定是一个根到叶子的链可以达到最优的状态。

那么我们不妨将开始随机的点往下跳几步。

具体的：

- 开始随机一个点 $x$。
- 对于现在在的点 $x$，我们遍历到了 $i$。
- 求 $\text{lca}(x,i)$。
- 若 $\text{lca}(x,i)=x$，那么让 $x\rightarrow i$，然后继续遍历。
- 否则直接继续遍历。

这样遍历完所有节点后，一定到了一个叶子节点。

但是你写完之后，会发现你的操作次数变成了 $5000\sim 6000$。

思考一下问题在哪里。

我们在往下跳的过程中使用了过多的冗余操作。

我们想要把这些操作也用上。

考虑：
> 若 $x$ 为 $y$ 的子树内一点，$z$ 为 $y$ 的子树外一点，那么 $\text{lca}(y,z)=\text{lca}(x,z)$。

所以，我们在不断往下跳的过程中，$\text{lca}$ 其实是同样可以往下继承的。

这样就可以在恰好 $siz-1$ 次操作找到叶子，并求出 $\text{lca}$（随机没用了）。

然后你的操作次数就变成了定值，这个定值基于你的实现。

$10$ 层是可以做到 $4608$ 或 $4480$（特判三个点）。

复杂度基于实现。

### Code

这份代码是 $4480$ 的。

```cpp
/*
  ! 如果没有天赋，那就一直重复
  ! Created: 2024/06/05 09:10:14
*/
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
// #define int long long
#define mp(x, y) make_pair(x, y)
#define eb(...) emplace_back(__VA_ARGS__)
#define fro(i, x, y) for (int i = (x); i <= (y); i++)
#define pre(i, x, y) for (int i = (x); i >= (y); i--)
inline void JYFILE19();

using i64 = long long;
using PII = pair<int, int>;

bool ST;
const int N = 1100;
const int mod = 998244353;

int n, m, fa[N], sz[N], mp[N][N];
vector<int> to[N];

inline int lca(int x, int y) {
  if (mp[x][y]) return mp[x][y];
  cout << "? " << x << " " << y << endl;
  cin >> mp[x][y];
  return mp[y][x] = mp[x][y];
}
inline void upd(int x, int y, int k) {
  if (mp[x][y]) return;
  mp[x][y] = mp[y][x] = k;
}
inline auto sol(vector<int> all, int las = 0) {
  if (all.size() == 0) return 0;
  if (all.size() == 1) return all[0];
  if (all.size() == 2) return fa[all[0]] = las, all[1];
  if (all.size() == 3) {
    int x = lca(all[0], all[1]);
    for (auto i : all) if (i != x) fa[i] = x;
    return x;
  }
  int x = all[0]; vector<int> res;
  for (auto i : all) {
    if (lca(i, x) == x) {
      for (auto j : all) {
        if (i == j) break;
        upd(i, j, lca(x, j));
      }
      x = i;
    }
  }
  for (auto i : all) {
    sz[lca(i, x)]++;
    res.eb(lca(i, x));
  }
  sort(res.begin(), res.end(), [&](int x, int y) {
    return sz[x] < sz[y];
  });
  res.erase(unique(res.begin(), res.end()), res.end());
  for (int i = 0; i < res.size() - 1; i++)
    fa[res[i]] = res[i + 1];
  for (auto i : all) {
    for (auto j : res) if (i == j) goto ed;
    if (lca(i, x) != i) to[lca(i, x)].eb(i);
    ed:;
  }
  for (auto i : res) {
    auto nt = to[i];
    to[i].clear();
    auto x = sol(nt, i);
    if (x != i) fa[x] = i;
  }
  return res.back();
}

signed main() {
  JYFILE19();
  cin >> n, n = (1 << n) - 1;
  vector<int> all;
  fill(fa + 1, fa + n + 1, -1);
  fro(i, 1, n) all.eb(i), mp[i][i] = i;
  sol(all);
  cout << "! ";
  fro(i, 1, n) cout << fa[i] << " ";
  cout << endl;
  return 0;
}

bool ED;
inline void JYFILE19() {
  // freopen("", "r", stdin);
  // freopen("", "w", stdout);
  srand(random_device{}());
  ios::sync_with_stdio(0), cin.tie(0);
  double MIB = fabs((&ED - &ST) / 1048576.), LIM = 32;
  // cerr << "MEMORY: " << MIB << endl, assert(MIB <= LIM);
}
```

---

## 作者：Petit_Souris (赞：0)

拿到题目的第一个想法就是把一个点和所有点都问询一遍，这样得到了类似下图的结构：

![](https://cdn.luogu.com.cn/upload/image_hosting/hjz56iu7.png)

（问询的是红点，设为 $u$）

这时候我们就能确定 $u$ 的所有祖先了（作为 LCA 出现的次数从小到大，从浅到深。）这样把整棵树分成了若干个更小的满二叉树，可以递归继续进行问询。

但是这样的问询次数会超过要求。我们更倾向于问询一个叶子节点，这样问询次数就是 $f(n)=2^n-1+\sum\limits_{i<n}f(i)$，计算得满足条件。那么我们在问询 $(u,v)$ 的时候，如果 $\mathrm{LCA}(u,v)=u$，就将 $u$ 修改为 $v$，这样相当于往子树内走，最后一定会走到一个叶子节点。这样就可以通过了。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=1029;
ll n,fa[N];
mt19937 rnd(time(0));
ll Q(ll x,ll y){
    cout<<"? "<<x<<" "<<y<<"\n";
    fflush(stdout);
    ll z;cin>>z;
    return z;
}
ll solve(vector<ll>v){
    if((ll)v.size()==1)return v[0];
    if((ll)v.size()==3){
        ll x=v[0],y=v[1];
        ll z=Q(x,y);
        for(ll p:v){
            if(p!=z)fa[p]=z;
        }
        return z;
    }
    ll p=rnd()%(ll)v.size();
    ll q=v[p];
    vector<ll>rca(v.size(),0);
    rep(i,0,(ll)v.size()-1){
        if(i==p)continue;
        ll w=Q(v[i],q);
        if(w==q)rca[p]=q,p=i,q=v[i];
        else rca[i]=w;
    }
    rca[p]=q;
    map<ll,ll>mp1,mp2;
    ll rt=0;
    vector<ll>qd;
    rep(i,0,(ll)v.size()-1)mp2[rca[i]]++;
    rep(i,0,(ll)v.size()-1){
        if(!mp1.count(rca[i])){
            qd.push_back(rca[i]);
            mp1[rca[i]]=1;
            vector<ll>nv;
            rep(j,0,(ll)v.size()-1){
                if(rca[j]==rca[i]&&v[j]!=rca[i])nv.push_back(v[j]);
            }
            if(!nv.size())continue;
            ll nrt=solve(nv);
            fa[nrt]=rca[i];
        }
    }
    sort(qd.begin(),qd.end(),[&](ll x,ll y){
        return mp2[x]<mp2[y];
    });
    rep(i,0,(ll)qd.size()-2)fa[qd[i]]=qd[i+1];
    rt=qd.back();
    return rt;
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    cin>>n;
    memset(fa,-1,sizeof(fa));
    vector<ll>v;
    rep(i,1,(1<<n)-1)v.push_back(i);
    solve(v);
    cout<<"! ";
    rep(i,1,(1<<n)-1)cout<<fa[i]<<" ";
    cout<<"\n";
    fflush(stdout);
    return 0;
}
```

---

