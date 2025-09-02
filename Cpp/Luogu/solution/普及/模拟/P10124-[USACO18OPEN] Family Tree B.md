# [USACO18OPEN] Family Tree B

## 题目描述

Farmer John 拥有一个传承数代的家族经营的农场，其中的奶牛的根源同样也可以在这个农场中追溯数代。通过检索古老的记录，Farmer John 好奇于现在的这群奶牛互相之间是什么关系。请帮帮他！ 

## 样例 #1

### 输入

```
7 AA BB
MOTHER AA
GGMOTHER BB
MOTHER SISTER
GMOTHER MOTHER
GMOTHER AUNT
AUNT COUSIN
GGMOTHER GMOTHER```

### 输出

```
BB is the great-aunt of AA```

# 题解

## 作者：Colubrid_L (赞：5)

## 废话时间
~~我不会橙我不会橙我不会橙我不会橙我不会橙。~~

## 正文
### 剖析题目
给一棵树（或者森林），求出给定的两个点之间的关系。

### 思路
原本我是想用 LCA 来做的，但是看了一眼题解，用 LCA 的大佬太多了，所以用这样一个非常暴力的做法。

在处理情况之前，因为输入都是字符串类型，所以可以考虑使用 map 映射出每个字符串唯一对应的整型，这样便于存图。存图的方法我用了邻接表，而且是由母亲向孩子建的有向边。

首先处理 `NOT RELATED` 的情况。这意味着输入的图是森林，而要查询的两只牛在不同的树中。这一点很简单，可以用并查集实现。

然后用一个 dfs 处理每个点的深度，方便后面的操作。

先处理直系亲属的情况。直系亲属情况很好办，可以从深度较深的那个点往上找。若找到另一个要查询的点，则说明二者存在直系亲属关系，输出若干 `great-` 后输出 `grand-mother` 就可以了。需要注意的是，也有可能不必输出`grand` 直接输出 `mother` 即可。

如果找不到直系亲属，那么还有 `SIBLINGS`，`COUSINS`，`(great-great...) aunt` 三种情况。可以先从最简单的姐妹关系入手。

处理姐妹关系时，由于每个点的母亲是唯一且确定的，我们可以开一个数组来记录每个节点的母亲。如果要查询的两个节点的母亲为同一个，那么此时直接输出 `SIBLINGS`。

再处理旁系亲属的情况。可以遍历深度较深点的直系亲属的孩子。如果在这些孩子中有要查询的另一个点，那么可以确定为旁系亲属关系，输出 `(great-great...) aunt`。

如果以上情况都不是，输出 `COUSINS`。

简化一下。

- 判断为没有关系：使用并查集。
- 判断为姐妹关系：同一个母亲。
- 判断为直系亲属：按深度较深往深度较浅搜。
- 判断为旁系亲属：搜直系亲属的孩子。
- 判断为表姐妹关系：不是以上四种关系。

思路就这样理清了，代码还是有一点难调的。

## 代码
一段段来看。

- 首先，处理深度。
```cpp
void dfs_deep(int id,int dep){
	if(deep[id]!=0)return ;
	deep[id]=dep;
	for(int i=0;i<vec[id].size();i++)
		dfs_deep(vec[id][i],dep+1);//由于建的是有向边，所以不用考虑搜回母亲的情况。
	return ;
}
```
- 判断为没有关系我使用了并查集。代码就不给了，因为很简单。
- 然后是判断姐妹关系。在程序中我使用了 fa 这个数组来存储每个节点的母亲，所以如果要查询的两个点的母亲相同，则在 fa 数组中，两个节点为下标的值相同。
- 判断为直系亲属关系。
```cpp
void dfs_1(int now,int sum){
	if(mp[a]==now){
		cout<<a<<" is the ";
		int flag=sum>1?1:0;
		sum-=2;
		while(sum>0)cout<<"great-",sum--;
		if(flag==1)cout<<"grand-";
		cout<<"mother of "<<b;
		exit(0);
	}
	if(fa[now]==0)return ;
	dfs_1(fa[now],sum+1);
	return ;
}
```
来理解一下这段代码的意思。

首先 $now$ 参数指的是当前处理到了哪个节点。$sum$ 参数指的是要查询的点的深度差。这一点也可以直接使用 $deep$ 数组内的值相减得到。

`if(fa[now]==0)return ;` 的作用是防止搜到最顶上的节点从而无限递归，造成 RE。
~~这个也需要解释吗？~~
- 判断为旁系亲属关系。
```cpp
void dfs_2(int now,int sum){
	for(int i=0;i<vec[now].size();i++){
		if(vec[now][i]==mp[a]){
			cout<<a<<" is the "; 
			sum-=3;
			while(sum>=0)cout<<"great-",sum--;
			cout<<"aunt of "<<b;
			exit(0);
		}
	} 
	if(fa[now]==0)return ;
	dfs_2(fa[now],sum+1);
	return ;
}
```
参数的意义同找直系亲属时参数的意义。

- 找表姐妹关系。如果执行完以上代码仍然没有找到关系，那么确定为表姐妹关系，直接输出就可以了。

**完整代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e2+5;
map<string,int> mp;//用 map 映射节点
string temp_a,temp_b;
string a,b;
vector<int> vec[N];
int deep[N],n,id,fa[N],sum,fat[N];
int finds(int x){
	return x==fat[x]?x:fat[x]=finds(fat[x]);
}
//处理深度
void dfs_deep(int id,int dep){
	if(deep[id]!=0)return ;
	deep[id]=dep;
	for(int i=0;i<vec[id].size();i++)
		dfs_deep(vec[id][i],dep+1);
	return ;
}
//找直接亲属 
void dfs_1(int now,int sum){
	if(mp[a]==now){
		cout<<a<<" is the ";
		int flag=sum>1?1:0;
		sum-=2;
		while(sum>0)cout<<"great-",sum--;
		if(flag==1)cout<<"grand-";
		cout<<"mother of "<<b;
		exit(0);
	}
	if(fa[now]==0)return ;
	dfs_1(fa[now],sum+1);
	return ;
}
//找旁系亲属 
void dfs_2(int now,int sum){
	for(int i=0;i<vec[now].size();i++){
		if(vec[now][i]==mp[a]){
			cout<<a<<" is the "; 
			sum-=3;
			while(sum>=0)cout<<"great-",sum--;
			cout<<"aunt of "<<b;
			exit(0);
		}
	} 
	if(fa[now]==0)return ;
	dfs_2(fa[now],sum+1);
	return ;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>a>>b;
	for(int i=1;i<=N;i++)fat[i]=i;
	mp[a]=++id,mp[b]=++id;
	for(int i=1;i<=n;i++){
		cin>>temp_a>>temp_b;
		if(mp[temp_a]==0)mp[temp_a]=++id;
		if(mp[temp_b]==0)mp[temp_b]=++id;
		vec[mp[temp_a]].push_back(mp[temp_b]);//可以看到这里只有母亲向孩子建边，是有向边。
		fa[mp[temp_b]]=mp[temp_a];//并查集
		int fax=finds(mp[temp_a]),fay=finds(mp[temp_b]);
		if(fax!=fay)fat[fay]=fax;
        
	}
	for(int i=1;i<=id;i++){
		if(fa[i]==0){
			dfn(i,1);
			break;
		}
	}
	//没有关系
	if(finds(mp[a])!=finds(mp[b])){
		cout<<"NOT RELATED";
		return 0;
	}
	//姐妹关系 
	if(fa[mp[a]]==fa[mp[b]]){
		cout<<"SIBLINGS";
		return 0;
	}
	if(deep[mp[a]]>deep[mp[b]])
		swap(a,b);
	dfs_1(mp[b],0);
	dfs_2(mp[b],0);
    //不是前面任何一种关系，则为表姐妹关系
	cout<<"COUSINS";
	return 0;
}
```

代码就是这个样子，有一点值得注意。题目中的 $n$ 代指的是有多少种关系，而非有多少个点。所以开数组的时候只开 $100$ 是不够的。

最后：祝 CSP J/S 2024 RP++ ！

感谢阅读。

---

## 作者：we_are_the_chuibing (赞：5)

### 思路

首先，设两只奶牛为 $A,B$。

由于族谱是一棵树，所以除非 $A$ 和 $B$ 之间没有关系，否则可以确定，$A$ 的 $n$ 辈祖先是 $B$ 的 $m$ 辈祖先。如果 $A$ 是 $B$ 的祖先，$n = 0$。

我们求的是辈分最小的，所以这不就是最小公共祖先？

由于数据范围小，可以直接暴力求。

求出 $n,m$ 之后，就好办了：

- $n = 0$ 时，$A$ 是 $B$ 的祖先。
- $m = 0$ 时，$B$ 是 $A$ 的祖先。
- $n = 1$ 且 $m = 1$ 时，$A$ 和 $B$ 是姐妹。
- $n = 1$ 且 $m > 1$ 时，$A$ 是 $B$ 的姨母。
- $n > 1$ 且 $m = 1$ 时，$B$ 是 $A$ 的姨母。
- $n > 1$ 且 $m > 1$ 时，$A$ 和 $B$ 是表姐妹。
- 没有查找到关系，就是没有关系。

然后，模拟就可以了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k1=114514,k2=1919810,q=0,w=0;
string a,b,s1[101],s2[101],s3[101],s4[101];
void sc1(string s){
	s3[q]=s;
	q++;
	for(int i=1;i<=n;i++){
		if(s2[i]==s)sc1(s1[i]);
	}
}
void sc2(string s){
	s4[w]=s;
	w++;
	for(int i=1;i<=n;i++){
		if(s2[i]==s)sc2(s1[i]);
	}
}
void init(){
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++){
		cin>>s1[i]>>s2[i];
	}
	sc1(a);
	sc2(b);
}
void now(){
	for(int i=0;i<q;i++){
		for(int j=0;j<w;j++){
			if(s3[i]==s4[j]){
				k1=i;
				k2=j;
				return;
			}
		}
	}
}
int main(){
	init();
	now();
	if((k1==1)&&(k2==1))cout<<"SIBLINGS";
	else if(k1==0){
		cout<<a<<" is the ";
		while(k2>=3){
			cout<<"great-";
			k2--;
		}
		if(k2==2)cout<<"grand-";
		cout<<"mother of "<<b;
	}
	else if(k2==0){
		cout<<b<<" is the ";
		while(k1>=3){
			cout<<"great-";
			k1--;
		}
		if(k1==2)cout<<"grand-";
		cout<<"mother of "<<a;
	}
	else if(k1==1){
		cout<<a<<" is the ";
		while(k2>=3){
			cout<<"great-";
			k2--;
		}
		cout<<"aunt of "<<b;
	}
	else if(k2==1){
		cout<<b<<" is the ";
		while(k1>=3){
			cout<<"great-";
			k1--;
		}
		cout<<"aunt of "<<a;
	}
	else if(k1==114514)cout<<"NOT RELATED";
	else cout<<"COUSINS";
	return 0;
}
```


---

## 作者：Chillturtle (赞：1)

# 题意

给你一坨两头奶牛的关系，然后给出两只奶牛的名字。求这两只奶牛之间的关系。这里是原题面提供的关系种类：

- 如果BESSIE和ELSIE的母亲是同一头奶牛，输出 `SIBLINGS`。
- BESSIE 可能是 ELSIE 的直系后代，也就是说 ELSIE 是BESSIE 的母亲（`mother`），外祖母（`grand-mother`），外曾外祖母（`great-grand-mother`），外曾外曾外祖母（`great-great-grand-mother`），等等。如果是这种情况，输出 `ELSIE is the (relation) of BESSIE`，其中 `(relation)` 是适当的关系，比如 `great-great-grand-mother`。
- 如果 ELSIE 不是 BESSIE 的某个祖先或姐妹，但是是 BESSIE 的某个祖先的孩子，那么 ELSIE 就是 BESSIE 的姨母（`aunt`）。（译者注：英语原题在这里表述有误，供题人已作出声明。）如果 ELSIE 是 BESSIE 的外祖母的孩子，输出 `ELSIE is the aunt of BESSIE`；如果 ELSIE 是 BESSIE 的外曾外祖母的孩子，输出 `ELSIE is the great-aunt of BESSIE`；如果 ELSIE 是 BESSIE 的外曾外曾外祖母的孩子，输出 `ELSIE is the great-great-aunt of BESSIE`；以此类推。
- 如果 BESSIE 和 ELSIE 有任何其他的亲戚关系（也就是说，她们有共同的祖先），她们就是表姐妹，输出 `COUSINS`。
- 如果 BESSIE 和 ELSIE 既没有共同的祖先，其中任何一头也不是另一头的直系后代，输出 `NOT RELATED`。

# 思路

其实并没有思路阿。。。这边建议直接把两个奶牛之间的关系理清楚直接模拟一下就好了。。。

我们设 1 的 $n$ 倍祖先等于 2 的 $m$ 倍祖先。那么很容易就有以下几条结论：

当 $n=0$ 时，1 是 2 的祖先；

当 $m=0$ 时，2 是 1 的祖先；

当 $n=1$ 且 $m=1$ 时，1 和 2 是姐妹关系；

当 $n=1$ 且 $m>1$ 时，1 是 2 的姨母，反之亦然；

当 $n>1$ 且 $m>1$ 时，显然的，1 和 2 是表姐妹关系。

所以，只要我们知道 1 和 2 的祖先关系，就可以知道它们之间的关系捏。因为数据极小并不需要倍增或者树剖，直接模拟就好了。

代码就不放了捏，太史了。。。

---

## 作者：__Sky__Dream__ (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/P10124)

## 题目大意
**又是一道模拟题**~~（还挺麻烦的）~~。

题意比较简单，就是给定一些奶牛，问它们的关系：

- 如果它们是姐妹，输出 `SIBLINGS`。
- 如果它们是直系亲属（题中的 mother 系列）或旁系亲属（题中的 aunt 系列），那么输出它们的关系。
- 如果它们的关系比 aunt 系列还要远，那么输出 `COUSINS`。
- 如果它们没有关系，那么输出 `NOT RELATED`。

## 解题思路
我们用两个数组 $mom_i$ 和 $dad_i$ 来记录每一对给出的关系（暂时将就着用），然后用比较抽象又暴力的方式找到它们的最近的共同祖先（具体见代码），用 $a$ 和 $ans$ 分别记录它们和最近祖先的距离，近的则为前辈，远的则为晚辈（输出时不要忘了**前辈在前晚辈在后**），如果能找到，说明它们有关系，最后确定关系并输出即可。

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAX=105;
int n;
string dad[MAX];
string mom[MAX];
string dfs(string cow)
{
	for(int i=0;i<n;i++)
		if(cow==dad[i]) return mom[i];
	return "";
}
//如果cow1是cow2的直系祖先，则返回其代数
//否则返回-1
int count(string cow1,string cow2)
{
	int cnt=0;
	while(cow2!="")
	{
		if(cow1==cow2) return cnt;
		cow2=dfs(cow2);
		cnt++;
	}
	return -1;
}
int main()
{
	string x,y;
	cin>>n;
	cin>>x>>y;
	for(int i=0;i<n;i++) cin>>mom[i]>>dad[i];
	string cow=x;
	int ans=0;
	//找共同祖先
	while(cow!="")
	{
		//如果cow是y的直系祖先
		if(count(cow,y)!=-1) break;
		cow=dfs(cow);
		ans++;
	}
	if(cow=="")
	{
		cout<<"NOT RELATED"<<"\n";
		return 0;
	}
	//确定关系
	int a=count(cow,y);
	if(a==1&&ans==1) cout<<"SIBLINGS"<<"\n";
	else if(a>1&&ans>1) cout<<"COUSINS"<<"\n";
	else
	{
		if(a>ans) swap(x,y),swap(a,ans);
		cout<<y<<" is the ";
		for(int i=0;i<ans-2;i++) cout<<"great-";
		if(ans>1&&a==0) cout<<"grand-";
		if(a==0) cout<<"mother";
		else cout<<"aunt";
		cout<<" of "<<x<<"\n";
	}
	return 0;
}
```
#### 题目坑比较多，大家做的时候要认真，切勿抄袭！！！

---

## 作者：Z3k7223 (赞：1)

[题目链接](https://www.luogu.com.cn/problem/P10124)

一道很裸的 LCA + 模拟。

## Solution

先用 `map` 把字符串转为节点编号，直接按照题意模拟即可。

模拟的时候首先判一下无血缘关系的情况，从一个询问的对应节点跑一遍 DFS 即可，如果另一个询问的对应 vis 数组没有被更新就是两个点不连通。顺便还可以记录入度为 $0$ 的节点作为根，方便跑 LCA。

题意很裸，但很坑。题目给了 `mother` 和 `aunt` 两种情况，需要两个询问的字符串**在不同顺序**都不符合这种情况才能看下一种，需要一边判断一边 `swap`（不理解这句话的看代码），最后求出 LCA 依题意判断即可。

## Code：

树剖是直接复制模板的，实际上有很多优化的空间。

```
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
int n;
int fa[N], top[N], siz[N], dep[N], son[N];
int ind[N], root, vis[N];
vector<int> e[N];
string aska, askb;
unordered_map<string, int> mp;
int cnt;

void dfs0(int x) {
	if (!ind[x]) {//顺便找根
		root = x;
	}
	vis[x] = 1;
	for (auto v : e[x]) {
		if (!vis[v]) {
			dfs0(v);
		}
	}
}

void dfs1(int x, int fa_, int depth) {//LCA板子
	dep[x] = depth;
	fa[x] = fa_;
	siz[x] = 1;
	int maxx = 0;
	for (auto v : e[x]) {
		if (v == fa_) {
			continue;
		}
		dfs1(v, x, depth + 1);
		siz[x] += siz[v];
		if (siz[v] > maxx) {
			maxx = siz[v];
			son[x] = v;
		}
	}
}

void dfs2(int x, int topfa) {
	top[x] = topfa;
	if (!son[x]) {
		return;
	}
	dfs2(son[x], topfa);
	for (auto v : e[x]) {
		if (v != fa[x] && v != son[x]) {
			dfs2(v, v);
		}
	}
}

int lca(int x, int y) {
	while (top[x] != top[y]) {
		if (dep[top[x]] > dep[top[y]]) {
			swap(x, y);
		}
		y = fa[top[y]];
	}
	return dep[x] < dep[y] ? x : y;
}

int main() {
	cin >> n >> aska >> askb;
	for (int i = 1; i <= n; i++) {
		string a, b;
		int u, v;
		cin >> a >> b;
		if (mp.count(a)) {
			u = mp[a];
		} else {
			u = mp[a] = ++cnt;
		}
		if (mp.count(b)) {
			v = mp[b];
		} else {
			v = mp[b] = ++cnt;
		}
		ind[v]++;//只有没有母亲（好怪喔）的节点才可能成为根
		e[u].push_back(v);
		e[v].push_back(u);
	}
	if (!mp.count(aska) || !mp.count(askb)) {//没出现直接return
		puts("NOT RELATED");
		return 0;
	}
	dfs0(mp[aska]);
	if (!vis[mp[askb]]) {//不联通也return
		puts("NOT RELATED");
		return 0;
	}
	dfs1(root, 0, 1);
	dfs2(root, root);
	int l = lca(mp[aska], mp[askb]);
	if (fa[mp[aska]] == fa[mp[askb]]) {//这里以后都是按题目描述模拟
		puts("SIBLINGS");
		return 0;
	}
	string ans = "";
	for (int i = 1; i <= 2; swap(aska, askb), i++) {//注意细节，特别是循环次数
		if (l == mp[askb]) {
			int tmp = dep[mp[aska]] - dep[l];
			ans = "mother";
			if (tmp >= 2) {
				ans = "grand-" + ans;
				for (int i = 3; i <= tmp; i++) {
					ans = "great-" + ans;
				}
			}
			cout << askb << " is the " << ans << " of " << aska << endl;
			return 0;
		}
	}
	for (int i = 1; i <= 2; swap(aska, askb), i++) {
		if (l == fa[mp[askb]]) {
			int tmp = dep[mp[aska]] - dep[l];
			ans = "aunt";
			if (tmp >= 3) {
				for (int i = 3; i <= tmp; i++) {
					ans = "great-" + ans;
				}
			}
			cout << askb << " is the " << ans << " of " << aska << endl;
			return 0;
		}
	}
	puts("COUSINS");//没有mother和aunt的关系就是cousin
	return 0;
}
```

---

## 作者：dengruijie2 (赞：0)

先用 `map` 把字符串转为节点编号，直接按照题意模拟即可。

模拟的时候首先判一下无血缘关系的情况，从一个询问的对应节点跑一遍 DFS 即可，如果另一个询问的对应 vis 数组没有被更新就是两个点不连通。顺便还可以记录入度为 $0$ 的节点作为根，方便跑 LCA。

题意很裸，但很坑。题目给了 `mother` 和 `aunt` 两种情况，需要两个询问的字符串在不同顺序都不符合这种情况才能看下一种，需要一边判断一边 `swap`（不理解这句话的看代码），最后求出 LCA 依题意判断即可。

## 废话少说，上代码
```cpp
include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e3 + 5;
int n;
int fa[N], top[N], siz[N], deep[N], son[N];
int intt[N], root, f[N];
vector<int> e[N];
string aska, askb;
unordered_map<string, int> mp;
int cnt;

void dfs0(int x) {
	if (!intt[x]) {//顺便找根
		root = x;
	}
	f[x] = 1;
	for (auto v : e[x]) {
		if (!f[v]) {
			dfs0(v);
		}
	}
}

void dfs1(int x, int fa_, int depth) {//LCA板子
	deep[x] = depth;
	fa[x] = fa_;
	siz[x] = 1;
	int maxx = 0;
	for (auto v : e[x]) {
		if (v == fa_) {
			continue;
		}
		dfs1(v, x, deepth + 1);
		siz[x] += siz[v];
		if (siz[v] > maxx) {
			maxx = siz[v];
			son[x] = v;
		}
	}
}

void dfs2(int x, int topfa) {
	top[x] = topfa;
	if (!son[x]) {
		return;
	}
	dfs2(son[x], topfa);
	for (auto v : e[x]) {
		if (v != fa[x] && v != son[x]) {
			dfs2(v, v);
		}
	}
}

int lca(int x, int y) {
	while (top[x] != top[y]) {
		if (deep[top[x]] > deep[top[y]]) {
			swap(x, y);
		}
		y = fa[top[y]];
	}
	return deep[x] < deep[y] ? x : y;
}

int main() {
	cin >> n >> aska >> askb;
	for (int i = 1; i <= n; i++) {
		string a, b;
		int u, v;
		cin >> a >> b;
		if (mp.count(a)) {
			u = mp[a];
		} else {
			u = mp[a] = ++cnt;
		}
		if (mp.count(b)) {
			v = mp[b];
		} else {
			v = mp[b] = ++cnt;
		}
		intt[v]++;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	if (!mp.count(aska) || !mp.count(askb)) {//没出现直接return
		puts("NOT RELATED");
		return 0;
	}
	dfs0(mp[aska]);
	if (!f[mp[askb]]) {//不联通也return
		puts("NOT RELATED");
		return 0;
	}
	dfs1(root, 0, 1);
	dfs2(root, root);
	int l = lca(mp[aska], mp[askb]);
	if (fa[mp[aska]] == fa[mp[askb]]) {//这里以后都是按题目描述模拟
		puts("SIBLINGS");
		return 0;
	}
	string ans = "";
	for (int i = 1; i <= 2; swap(aska, askb), i++) {//注意细节，特别是循环次数
		if (l == mp[askb]) {
			int tmp = deep[mp[aska]] - deep[l];
			ans = "mother";
			if (tmp >= 2) {
				ans = "grand-" + ans;
				for (int i = 3; i <= tmp; i++) {
					ans = "great-" + ans;
				}
			}
			cout << askb << " is the " << ans << " of " << aska << endl;
			return 0;
		}
	}
	for (int i = 1; i <= 2; swap(aska, askb), i++) {
		if (l == fa[mp[askb]]) {
			int tmp = deep[mp[aska]] - deep[l];
			ans = "aunt";
			if (tmp >= 3) {
				for (int i = 3; i <= tmp; i++) {
					ans = "great-" + ans;
				}
			}
			cout << askb << " is the " << ans << " of " << aska << endl;
			return 0;
		}
	}
	puts("COUSINS");//没有mother和aunt的关系就是cousin,一定要大写
	return 0;
}
```

---

## 作者：违规用户名^3Zj=Oha (赞：0)

## 一、思路分析
先去找第一头奶牛的祖上，若直接没有了，就输出"NOT RELATED"。若还剩下，就去找他们俩个的祖先，用一个变量去存下隔了几代，然后输出，若隔了超过两代，就用 for 循环输出 $ans-2$ 个"great-"，最后输出是 aunt 还是 mother 即可。

## 二、构造代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=0;
string x,y,v,b[105],a[105];
string dfs(string v){
	for(int i=0;i<n;i++){
		if(v==b[i]) return a[i];
	}
	return "";
}
int main(){
	cin>>n>>x>>y;
	for(int i=0;i<n;i++) cin>>a[i]>>b[i];
	v=x;
	while(v!=""){
		string t=y;
		int cnt=0,flag=-1;
		while(t!=""){
			if(v==t){
				flag=cnt;
				break;
			}
			t=dfs(t);
			cnt++;
		}
		if(flag!=-1) break;
		v=dfs(v);
		ans++;
	}
	if(v==""){
		cout<<"NOT RELATED"<<endl;
		return 0;
	}
	int cnt=0,flag=-1;
	string t=y;
	while(t!=""){
		if(v==t){
			flag=cnt;
			break;
		}
		t=dfs(t);
		cnt++;
	}
	if(flag==1&&ans==1) cout<<"SIBLINGS"<<endl;
	else if(flag>1&&ans>1) cout<<"COUSINS"<<endl;
	else{
		if(flag>ans){
			swap(x,y);
			swap(flag,ans);	
		}
		cout<<y<<" is the ";
		for(int i=0;i<ans-2;i++) cout<<"great-";
		if(ans>1&&!flag) cout<<"grand-";
		if(!flag) cout<<"mother";
		else cout<<"aunt";
		cout<<" of "<<x<<endl;
	}
	return 0;
}
```

---

## 作者：Ren_Hx (赞：0)

### 分析
为了求解这个问题，我们需要构建奶牛之间的家谱关系，如下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/j7xel1y2.png)
确定了 BESSIE 和 ELSIE 之间对应的关系后,那我们可以使用图的数据结构来表示这个家谱，并通过深度优先搜索来探索这俩奶牛的关系。

### Code
```cpp
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <set>
using namespace std;
struct Node {
    string name;
    string parent;
    string relation;
};
unordered_map<string, vector<string>> tree;
unordered_map<string, string> parents;
string gr(int depth) {
    if (depth == 0) return "";
    string result = "great-";
    for (int i = 1; i < depth; i++) {
        result += "great-";
    }
    result += "grandmother";
    return result;
}
void find(const string& start, const string& target, unordered_map<string, string>& path, string& relation, int& depth) {
    if (start == target) {
        return;
    }
    for (const auto& child : tree[start]) {
        path[child] = start;
        depth++;
        find(child, target, path, relation, depth);
        if (!relation.empty()) return;
        depth--;
    }
}
string ch(const string& A, const string& B) {
    unordered_map<string, string> path;
    path[A] = "";
    int depth = 0;
    string relation = "";
    find(A, B, path, relation, depth);
    if (!relation.empty()) {
        return B + " is the " + gr(depth) + " of " + A;
    }
    path.clear();
    path[B] = "";
    depth = 0;
    find(B, A, path, relation, depth);
    if (!relation.empty()) {
        return A + " is the " + gr(depth) + " of " + B;
    }
    if (path.find(A) != path.end()) {
        return B + " is the aunt of " + A;
    } else if (path.find(B) != path.end()) {
        return A + " is the aunt of " + B;
    }
    set<string> ana, anb;
    for (const auto& p : path) {
        ana.insert(p.first);
    }
    path.clear();
    path[B] = "";
    find(B, A, path, relation, depth);
    for (const auto& p : path) {
        anb.insert(p.first);
    }
    if (!ana.empty() && !anb.empty()) {
        for (const auto& a : ana) {
            if (anb.find(a) != anb.end()) {
                return "COUSINS";
            }
        }
    }
    return "NOT RELATED";
}
int main() {
    int N;
    cin >> N;
    string A, B;
    cin >> A >> B;
    unordered_map<string, string> parents;
    unordered_map<string, vector<string>> tree;
	for (int i = 0; i < N; i++) {
        string mother, child;
        cin >> mother >> child;
        tree[mother].push_back(child);
        parents[child] = mother;
    }
    cout << ch(A, B) << endl;   
    return 0;
}
```

---

## 作者：xujingyu (赞：0)

## 题意

给出一堆关系，求输入两个人的关系（这些牛好像都是女的？）。

## 解法

这题真难调……

先列出我踩过的坑：

* 只有姨母关系和直系亲属关系要输出句子；
* 不是只有 $X$ 和 $Y$ 不在 $N$ 行的输入中时输出 `NOT RELATED`；
* 在我的做法中，找表姐妹关系要 dfs，因为她可以是姨母的孩子或者孙女或者曾孙女或者啥啥啥的；
* `great` 和 `grand` 不是一回事，别像我一样弄混了；
* 数组不要只开 $101$ 啊；
* 最重要的（这里我调了挺久……），$X$ 和 $Y$ 有可能需要进行 `swap`，例如看一组数据：
  ```
  4 A B
  C A
  A B
  B D
  D E
  ```
  这样的情况，在我的做法里要交换 $X$ 和 $Y$，因为 $X$ 深度小；
* **有可能输入是森林**，即有很多根。

好了讲解法吧。

首先给每个人一个编号，将字符串转为整数方便图论，再存储每个节点的母亲和**每个**孩子。

如果输入的那 $N$ 行中没有出现 $X$ 或 $Y$，直接输出 `NOT RELATED`。

然后找到**每个**没有母亲的节点，即根节点，依次 dfs，算出每个节点的深度。现在，可以根据上文条件交换 $X$ 和 $Y$ 啦。

现在，从 $X$ 节点开始遍历它的每个祖先，先是母亲，再是奶奶，以此类推。

若遍历到的那个祖先是 $Y$，输出一堆 `great-` 再输出 `grand-mother`，可能不需要 `grand-`。

再遍历这个祖先的每个孩子，称为姨母。若有 $Y$，输出一堆 `great-` 再输出 `aunt`，也可能只需输出 `SIBLINGS`。

再 dfs 遍历这个姨母的每个孩子和孙女和曾孙女和啥啥啥，找到就输出 `COUSINS`。

啥也没找到就输出 `NOT RELATED`。

最后赠送一组数据：

输入：
```
7 G C
A B
B C
B D
A E
F A
F G
G H
```
输出：
```
G is the great-aunt of C
```

放代码吧，应该没人打暴力做还比我长……

最后的最后，如果你看到了这里来了（应该不会有人有这个耐心），就再听我叨一句：这题真 ** 难调……

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,tot,fa[1001],rt[1001],rtc,deep[1001];
map <string,int> m;//每个字符串的编号
string a,b,x,y,id[1001];
vector <int> son[1001];

void dfs(int u)//找表姐妹
{
	for(int i = 0;i < son[u].size();i++)
	{
		int v = son[u][i];
		if(id[v] == b){cout << "COUSINS";exit(0);}
		dfs(v);//继续找
	}
	return;
}

void change(int u)//计算深度
{
	for(int i = 0;i < son[u].size();i++)
	{
		int v = son[u][i];
		deep[v] = deep[u] + 1;//更新
		change(v);
	}
	return;
}

signed main()
{
	cin >> n >> a >> b;
	for(int i = 1;i <= n;i++)
	{
		cin >> x >> y;
		if(!m[x]) m[x] = ++tot;//给一个编号
		if(!m[y]) m[y] = ++tot;
		int fx = m[x],fy = m[y];
		id[fx] = x;//根据编号找字符串
		id[fy] = y;
		fa[fy] = fx;//母亲
		son[fx].push_back(fy);//孩子
	}
	if(!m[a] || !m[b]){cout << "NOT RELATED";return 0;}//未出现
	for(int i = 1;i <= tot;i++) if(!fa[i]) rt[++rtc] = i;//根
	for(int i = 1;i <= rtc;i++) change(rt[i]);//遍历每个根
	if(deep[m[a]] < deep[m[b]]) swap(a,b);//交换
	for(int i = fa[m[a]],num = 0;i;i = fa[i],num++)//X的每个祖先
	{
		if(id[i] == b)//直系亲属
		{
			cout << b << " is the ";
			for(int j = 1;j < num;j++) cout << "great-";
			if(num) cout << "grand-";
			cout << "mother of " << a;
			return 0;
		}
		for(int j = 0;j < son[i].size();j++)//姨母或姐妹
		{
			if(id[son[i][j]] == b)
			{
				if(!num) cout << "SIBLINGS";
				else
				{
					cout << b << " is the ";
					for(int i = 1;i < num;i++) cout << "great-";
					cout << "aunt of " << a;
				}
				return 0;
			}
			dfs(son[i][j]);//表姐妹
		}
	}
	cout << "NOT RELATED";//没有
    return 0;
}
```

---

## 作者：__DayLight__ (赞：0)

## 前言
纯粹暴力大模拟。
## 思路
- 根据题目给出的关系建树。

- **依次**判断题目给出的 $5$ 种情况。

声明：代码中用 $c_1$ 和 $c_2$ 分别表示需要查找的两头奶牛。

针对每一种情况有如下思路。

1. 母亲为同一奶牛（兄弟姐妹）：访问每个母亲的孩子，若 $c_1$ 和 $c_2$ 出现在同一母亲的孩子中，则答案为 `SIBLINGS`。

2. 其中一头奶牛为另一头的直系后代（祖母）：访问其中一头奶牛的所有祖先，若另一头为其中之一，则答案为 `mother`，详细的前缀处理见代码。

3. 其中一头奶牛为另一头的祖先的孩子（姨母）：访问其中一头奶牛的所有祖先的孩子，若另一头为其中之一，则答案为 `aunt`，详细的前缀处理见代码。

4. 有公共祖先（表姐妹）：暴力枚举两头奶牛各自的祖先，若有相同则答案为 `COUSINS`。

5. 若上述 $4$ 种情况都不符合，那答案就是 `NOT RELATED`。

注意：由于题目没有给出 $c_1$ 与 $c_2$ 的辈分谁大谁小，所以在进行第 $2$ 与 第 $3$ 种操作时，要**交替**判断 $2$ 次。

## 代码

判断的顺序是**不能**调换的，每种判断都建立在前一种**不成立**的条件下。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
map<string,vector<string>>G;//单独一个字符串存储母亲，用动态数组存储孩子。 
bool F;
int dep;//存储 代数，用于处理输出祖母或姨母关系时前缀单词 grand- 与 great- 的问题。
 
//直系后代 
void dfs1(string ma,string da)//daughter
{
	if(F)return;//找到就返回，避免重复计算。 
	dep++;
	for(auto it:G)
		for(int j=0; j<it.second.size(); j++)
			if(it.second[j]==da)//找所有的祖先 
			{
				if(it.first==ma)
				{
					F=1;
					return;
				}
				dfs1(ma,it.first);
			}
}

//甥女姨母 
void dfs2(string ni,string au)//niece
{
	if(F)return;
	dep++;
	for(auto it:G)
		for(int j=0; j<it.second.size(); j++)
			{
				if(it.second[j]==ni)
				{
					bool FL=0;
					for(int i=0; i<G[it.first].size(); i++)//找所有祖先的孩子 
						if(G[it.first][i]==au)FL=1;
					if(FL)
					{
						F=1;
						return;
					}
					dfs2(it.first,au);
				}
			}
}

//共同祖先
bool f1,f2;
void dfs3(string c1,string c2)//不用 LCA 是因为我不太会啊 
{
	if(f1&&f2)return;//都有记录表明都没祖先了，找完了，返回 
	string ma1="114514",ma2="1919810";
	for(auto it:G)
		for(int j=0; j<it.second.size(); j++)//依次找上一代 
		{
			if(it.second[j]==c1)ma1=it.first;
			if(it.second[j]==c2)ma2=it.first;
		}
	if(ma1=="114514")ma1=c1,f1=1;//没变意味着没有祖先了，插旗记录 
	if(ma2=="1919810")ma2=c2,f2=1;
	if(ma1==ma2)//直接判断，因为只要有一个共同祖先，那么再往上找的其他祖先都是相同的 
	{
		F=1;
		return;
	}
	dfs3(ma1,ma2);
}
string c1,c2,x,y;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>c1>>c2;
	for(int i=1; i<=n; i++)
	{
		cin>>x>>y;
		G[x].push_back(y);
	}
	
	//同一母亲 
	for(auto it:G)
	{
		bool f1=0,f2=0;
		for(int j=0; j<it.second.size(); j++)//访问每个母亲的孩子
		{
			if(it.second[j]==c1)f1=1;
			if(it.second[j]==c2)f2=1;
			//出现就插旗标记 
		}
		if(f1&&f2)//都有标记则为同一母亲 
		{
			cout<<"SIBLINGS";
			return 0;
		}
	}
	
	//c2 为  c1 直系后代 
	dep=F=0;
	dfs1(c1,c2);
	if(F)
	{
		cout<<c1;
		if(dep==1)cout<<" is the mother of "<<c2;//女儿与母亲 
		else
		{
			//通过代数判断 great- 的数量 
			cout<<" is the ";
			dep-=2;
			while(dep--)
				cout<<"great-";
			cout<<"grand-mother of "<<c2;
			//需要注意的是若只是祖母，则不是 great-，而是 grand-，所以 dep 要减 2
		}
		return 0;
	}
	
	//c1 为  c2 直系后代 
	dep=F=0;
	dfs1(c2,c1);//交替判断，c1 与 c2 位置交换。 
	if(F)
	{
		cout<<c2;
		if(dep==1)cout<<" is the mother of "<<c1;
		else
		{
			cout<<" is the ";
			dep-=2;
			while(dep--)
				cout<<"great-";
			cout<<"grand-mother of "<<c1;
		}
		return 0;
	}
	
	//c2 为  c1 某个祖先的孩子 
	dep=F=0;
	dfs2(c1,c2);
	if(F)
	{
		cout<<c2<<" is the ";
		dep-=2;
		while(dep--)
			cout<<"great-"; 
		cout<<"aunt of "<<c1;
		//找姨母的过程中会多找一代，所以 dep 减 2 
		return 0;
	}
	
	//c1 为  c2 某个祖先的孩子 
	dep=F=0;
	dfs2(c2,c1);//交替判断，c1 与 c2 位置交换。
	if(F)
	{
		cout<<c1<<" is the ";
		dep-=2;
		while(dep--)
			cout<<"great-"; 
		cout<<"aunt of "<<c2;
		return 0;
	}
	
	//c1 与 c2 有共同祖先
	F=0;
	dfs3(c1,c2);
	if(F)cout<<"COUSINS";
	
	//没关系 
	else cout<<"NOT RELATED";
	return 0;
}
```

---

## 作者：lyh4 (赞：0)

### 题意：
给出 $n$ 对关系，并根据这些求出给定奶牛的关系。

### 思路：
一看到此题，立即想到了并查集。可并查集只能知道是否有关系，无法得知是什么关系。后来一想，发现是最近公共祖先。

### 实现：
先根据读入的关系建树。接着，递归求解 LCA，并记录最近公共祖先距离两源点的深度。考虑本题数据范围小，朴素做法即可。
#### LCA：
先将两点中深度较深的点“提”到与另一点深度相同，然后将两点同时向上“提”，直到两点一样。
#### 记录答案：
**我们规定：$A$ 与 $B$ 为被查询的两只奶牛，$n$ 和 $m$ 为 $A_n$ 和 $B_m$ 一致时的最小值。**    
$n=0$ 时，$A$ 为 $B$ 的祖先。  
$m=0$ 时，$B$ 为 $A$ 的祖先。  
$n=1$ 且 $m=1$ 时，$A$ 和 $B$ 为姐妹。  
$n=1$ 且 $m>1$ 时，$A$ 为 $B$ 的姨母。  
$m=1$ 且 $n>1$ 时，$B$ 为 $A$ 的姨母。  
$n>1$ 且 $m>1$ 时，$A$ 和 $B$ 为表姐妹。  
未查询到，则 $A$ 与 $B$ 无关系。

---

