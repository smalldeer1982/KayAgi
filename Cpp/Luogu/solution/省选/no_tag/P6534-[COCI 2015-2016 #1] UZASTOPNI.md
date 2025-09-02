# [COCI 2015/2016 #1] UZASTOPNI

## 题目描述

这里有一棵有 $n$ 个点的树，每一个树上的节点有一个权值，即为 $v_i$，以 $1$ 为根，点以 $1\sim n$ 编号。

现在，我们想从选出一些点，并满足以下条件：

1. 一个点的父亲点若未被选择则其不能被选择。
1. 所选点的集合内不能有相同的权值。
1. 对于每一个选择的点，其子树中所有被选择点的权值必须可以构成公差为 $1$ 的等差数列。

您只需要输出满足上述条件的方案个数。

**注意：这里的方案指所选的数的集合不同的方案。**

## 说明/提示

#### 【样例解释】
#### 样例 1 解释
如下为选点的权值的六种情况：

$\{2\},\{2,3\},\{2,3,4\},\{1,2,3,4\},\{1,2\},\{1,2,3\}$。

#### 样例 2 解释
如下为选点的权值的三种情况：

$\{3\},\{3,4\},\{3,4,5\}$。

注意到不能选权值为 $6$ 的点，因为其父亲点与其构成的子树 $\{4,6\}$ 不符条件。
#### 【数据范围及限制】
- 对于 $50\%$ 的数据，保证 $n\le 100$。
- 对于 $100\%$ 的数据，保证 $1\le n\le 10^4$，$1\le v_i\le 100$，$1\le a_i,b_i\le n$。
#### 【说明】
**本题满分 $160$ 分。**

本题译自 [Croatian Open Competition in Informatics 2015/2016](https://hsin.hr/coci/archive/2015_2016) [Contest #1](https://hsin.hr/coci/archive/2015_2016/contest1_tasks.pdf) T6 UZASTOPNI。

## 样例 #1

### 输入

```
4
2 1 3 4
1 2
1 3
3 4 ```

### 输出

```
6```

## 样例 #2

### 输入

```
4
3 4 5 6
1 2
1 3
2 4```

### 输出

```
3```

## 样例 #3

### 输入

```
6
5 3 6 4 2 1
1 2
1 3
1 4
2 5
5 6 ```

### 输出

```
10```

# 题解

## 作者：A_Sunny_Day (赞：15)

## [COCI2015-2016#1] UZASTOPNI

题目链接：[COCI2015-2016#1UZASTOPNI](https://www.luogu.com.cn/problem/P6534)

---

​	写在前面：我代码中数组空间的开大是因为这道题在我们校内 OJ 上加了一个数据更大的点 $1\le n\le10^5,1\le v_i\le2000$。对于这道题来说，可以自行改小。

---

​	简化一下题意，意思就是选出来的权值要构成一个**连续的序列**。这里有一个重要的性质，我们从一棵子树入手，设这棵子树的根为 $rt$ ，它的权值为 $v_{rt}$，我们设它的任意一个儿子为 $son$，接下来我们分类讨论一下它儿子权值的情况。

+ $v_{rt}>v_{son}$。

  如果要选择 $son$ 这个点，那么 $rt$ 这个点就一定要选，同时由于集合中不能有**相同的权值**。所以在 $son$ 为根的子树里面不能选 $v_{rt}$ 这个权值，那么在以 $son$ 为根的子树里面选出权值构成的连续序列的最大值 $v_{max}$ 一定要小于 $v_{rt}$。我们可以用反证法来证明，如果 $v_{max}$ 被选了，由于 $v_{son}<v_{rt}<v_{max}$，为了构成一个连续的序列，我们必须选 $v_{rt}$，而我们又必须选 $rt$，这就矛盾了。

+ $v_{rt}<v_{son}$。

  这种情况与上述相似，我们设以 $son$ 为根的子树选出权值构成的连续序列的最小值为 $v_{min}$。如果 $v_{min}<v_{rt}$，又因为 $v_{min}<v_{rt}<v_{son}$，所以以 $son$ 为根的子树里面一定要选 $v_{rt}$，而 $rt$ 也一定要选，这不符合题意，所以 $v_{min}>v_{rt}$。

​	那么我们得到了一个重要信息：对于一个子树的根 $rt$ 来说，如果选择了它的一个儿子 $son$ ，那么以 $son$ 为根的子树里能构成的**连续权值序列**是不会跨越 $v_{rt}$ 的。（即最小值大于 $v_{rt}$ 或最大值小于 $v_{rt}$）

​	根据这个性质我们可以定下我们的 dp 数组。设 $L_{i,j}$ 表示以 $i$ 为根的子树能不能选出一个连续的序列为 ${j,j+1,\dots,v_i}$（$j\le v_i$ 即向左边扩展）。设 $R_{i,j}$ 为以 $i$ 为根的子树能不能选出一个连续的序列为 $v_i,v_i+1,\dots,j$（$v_i\le j$ 即向右边扩展）。然后更新的时候我们要注意我们只将类似于 $[1,2],[3,4]$ 的区间合并，而类似于 $[1,2],[2,3]$ 这类区间我们不合并（因为有重复的权值）。

​	还有一点需要注意的是，我们 dp 的顺序也有讲究，合并权值小于 $v_{rt}$ 的要按权值降序排序，合并权值大于 $v_{rt}$ 时要按权值升序排序。也就是我们要先合并 $|v_{rt}-v_{son}|$ 较小的儿子。

但是这样我们的时空都是 $O(n\times v)$，对于这道题我们绰绰有余，但是对于我前文提到 $n\le10^5,v\le2000$ 的数据来说是铁定过不了的，这时候我们使用 bitset 进行优化，关于 bitset 这里不再赘述，因为没用 bitset 也能过，有兴趣的读者可以去 oiwiki 自行查看。

​	那么用 bitset 优化后时空都变成了 $O(\dfrac{n\times v}{w})$。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN = 1e5+5;
int n,v[MAXN];
vector <int> e[MAXN];
bitset<2005> L[MAXN],R[MAXN];
bool cmp(int x,int x_)
{
	return v[x]<v[x_];
}
void dfs(int cur,int fa)
{
	L[cur].set(v[cur]);R[cur].set(v[cur]);
	for(int i=0;i<e[cur].size();++i)
	{
		int to=e[cur][i];
		if(to==fa) continue;
		dfs(to,cur);
	}
	int to;
	for(int i=0;i<e[cur].size();++i)//升序
		if(v[to=e[cur][i]]>v[cur]&&((R[cur]<<1)&L[to]).any()) R[cur]|=R[to];
	for(int i=e[cur].size()-1;i>=0;--i)//降序
		if(v[to=e[cur][i]]<v[cur]&&((L[cur]>>1)&R[to]).any()) L[cur]|=L[to];
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&v[i]);
	for(int i=1;i<n;++i)
	{
		int u,v;
		scanf("%d %d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for(int i=1;i<=n;++i)
		sort(e[i].begin(),e[i].end(),cmp);
	dfs(1,0);
	printf("%lld",(ll)L[1].count()*(ll)R[1].count());
	return 0;
}
```







---

## 作者：Feyn (赞：6)

[link](https://www.luogu.com.cn/problem/P6534) & [博客园食用](https://www.cnblogs.com/dai-se-can-tian/p/16491304.html)

建议管理大大评紫。理由：巧妙的树形DP。

题意是说给定一棵有根树，需要从中选出一些节点符合：

- 每个选中节点的父亲也被选中

- 任意选中节点在原树对应的子树内所有选中的节点点权连续。

- 选中的所有节点不能有权值相同的。

求方案数，其中两个方案不同当且仅当它们选出的点的点权集合不同。

由于点权的值域不大，可以考虑以值域为下标。用 $\mathit{f_{i,j}}$ 来代表子树 $x$ 选出值域完全覆盖 $[l,r]$ 是否可行，然后发现似乎开不下。想到子树 $x$ 一定会选出点权为 $a_x$ 的点，可以把上述状态转移成 $\mathit{f_{x,l,a_x}}$ 和 $\mathit{f_{x,a_x,r}}$，去掉无用状态就是 $\mathit{f_{x,l}}$ 和 $\mathit{f_{x,r}}$。

考虑如何转移。由于数据范围很小可以直接枚举区间断点，然后看分割出来的两个区间是否都是可行的。

有一些需要注意的细节。假如不对孩子加以排序，第二个样例都无法通过，原因是假如当前的 $a_i=1$，有一个孩子是 $2$ ，另一个是 $3$ 。假如先用后面的孩子去更新当前结点的答案，那么显然是无法更新的，毕竟 $[1,2]$ 和 $[1,3]$ 都无法用那个孩子凑成。但事实上假如先用前面的孩子去更新就不会出现错误，得出结论应当先把所有孩子按和当前结点点权差的绝对值从小到大排序。由于卡空间要用 vector。

统计答案直接看树根的值两边各有多少可能的选择，乘起来即可。

还有一些细节，具体看代码。

附：由衷感谢管理大大三分钟就审了蒟蒻的题解并耐心地指出错误，希望洛谷越来越好！

```cpp
#include<bits/stdc++.h>
//#define feyn
const int N=10010;
const int M=110;
using namespace std;
inline void read(int &wh){
	wh=0;int f=1;char w=getchar();
	while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
	while(w>='0'&&w<='9'){wh=wh*10+w-'0';w=getchar();}
	wh*=f;return;
}

struct edge{
	int t,next;
}e[N];
int head[N],esum;
inline void add(int fr,int to){
	e[++esum]=(edge){to,head[fr]};head[fr]=esum;
}

int m,a[N];
bool f[N][M],g[M];
inline bool ok(int wh,int l,int r){//子树wh是否可以选出区间[l,r] 
	if(a[wh]<l||a[wh]>r)return false;//根节点是一定会选的，如果根节点不在区间内必然不合法 
	return f[wh][l]&&f[wh][r]; //返回左右两边是否都可行 
}
int now;
inline int ff(int wh){return wh<0?-wh:wh;}
inline bool cmp(int s1,int s2){
	return ff(a[s1]-a[now])<ff(a[s2]-a[now]);//按差的绝对值排序 
}
void solve(int wh){
	f[wh][a[wh]]=true;
	vector<int>son;
	for(int i=head[wh],th;i;i=e[i].next){
		solve(th=e[i].t);son.push_back(th);//记录所有孩子 
	}
	now=wh;sort(son.begin(),son.end(),cmp);//排序 
	for(int i=0;i<son.size();i++){
		int th=son[i];
		for(int j=1;j<=100;j++){
			g[j]=f[wh][j];if(j==a[wh])continue;
			for(int k=min(j,a[wh])+1;k<=max(j,a[wh]);k++){
				if(j<a[wh])g[j]=g[j]||(f[wh][k]&&ok(th,j,k-1));
				//区间[j,a[wh]]被分成了[j,k-1]和[k,a[wh]] 
				else g[j]=g[j]||(f[wh][k-1]&&ok(th,k,j));
				//区间[a[wh],j]被分成了[a[wh],k-1]和[k,j] 
			}
		}
		for(int j=1;j<=100;j++)f[wh][j]=g[j];//用辅助数组中的值更新 
	}
}

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);int s1,s2;
	for(int i=1;i<=m;i++)read(a[i]);//读入点权 
	for(int i=1;i<m;i++){
		read(s1);read(s2);add(s1,s2);//加边 
	}
	solve(1);//递归进行树形DP 
	int x=1,y=1;
	for(int i=1;i<a[1];i++)x+=f[1][i];
	for(int i=a[1]+1;i<=100;i++)y+=f[1][i];
	printf("%d\n",x*y);
	
	return 0;
}
```

---

## 作者：xiaolilsq (赞：6)

[题目链接](https://www.luogu.com.cn/problem/P6534)

这是本人做的第一道bitest题目，如果有什么说的不对的地方，可以在评论区里提出。

看到题目，要求等差数列公差为$ 1 $，相当于是权值要排成一段连续的区间$ [l,r] $，发现$ 1 \le v_i \le 100 $，数据范围特别小，于是可以想到一种十分暴力的做法：设$ dp_{u,l,r}$表示在以$ u $为根的子树中是否可以选出权值恰好排成$ [l,r] $一段区间，这个数组是bool类型的，转移的方法就先把所有子树可选区间抠出来，然后从小到大枚举右端点，一次次地并起来就行了。

但是这样是过不了的，由于权值只有100，考虑用bitset压位优化，如果还是不懂的话建议直接看代码，代码已经写得很详细了（~~估计是我写得最详细的代码~~）。

AC代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<bitset>
using namespace std;
#define ch() getchar()
#define pc(x) putchar(x)
template<typename T>inline void read(T&x){
	int f;char c;
	for(f=1,c=ch();c<'0'||c>'9';c=ch())if(c=='-')f=-f;
	for(x=0;c<='9'&&c>='0';c=ch())x=x*10+(c&15);x*=f;
}
template<typename T>inline void write(T x){
	static char q[64];int cnt=0;
	if(!x)pc('0');if(x<0)pc('-'),x=-x;
	while(x)q[cnt++]=x%10+'0',x/=10;
	while(cnt--)pc(q[cnt]);
}
const int maxn=10005;
int val[maxn],bro[maxn],son[maxn];//val数组是权值（注意，这份代码的val是在0到99范围内的），bro和son用来存树边 
struct segment{//用来存区间的结构体 
	int l,r;
	segment(int l=0,int r=0):l(l),r(r){}//初始化函数 
};
vector<segment>S[maxn];//S用来存每个点的可行区间 
vector<segment>::iterator it0;//用来遍历S的迭代器 
vector<int>T[100];//T[l]用来临时存对于所有儿子某个l，所有可行的r有哪些 
vector<int>::iterator it1;//用来遍历T的迭代器 
bitset<100>dp[100];//dp[l]用来存对于自己的某个l，所有可行的r有哪些，可以理解为所有T的并 
void dfs(int u){
	for(int v=son[u];v;v=bro[v])dfs(v);//处理所有子树 
	for(int i=0;i<100;++i)T[i].clear();//清空T，循环利用 
	for(int v=son[u];v;v=bro[v])
		for(it0=S[v].begin();it0!=S[v].end();++it0)
			T[(*it0).l].push_back((*it0).r);//把所有儿子的可行区间先丢到T数组里面 
	//注意，下面的dp数组计算时是不考虑包含val[u]这个权值的 
	for(int i=99;i>=0;--i){//枚举所有权值作为左端点 
		dp[i].reset();//别忘了清空 
		if(i==val[u]){//相当于把u这个点的权值放到第i处 
			dp[i]|=dp[i+1];//后面的区间再并上u这个点的权值得到以当前的i作为左端点所有可行的右端点 
			dp[i].set(i);//[i,i]也是可行的 
		}
		else{
			for(it1=T[i].begin();it1!=T[i].end();++it1){
				if((*it1)<val[u]||i>val[u]){//区间不可以包含val[u]，因为只要选了这棵子树，val[u]是必选的，不可以有重复 
					dp[i]|=dp[(*it1)+1];//同上，并上后面的权值 
					dp[i].set((*it1));//[i,r]也是可行的 
				}
			}
		}
	}
	S[u].clear();//不要忘记清空，即使只有一次操作，清空也是个好习惯 
	//[l,r]必须包含val[u] 
	for(int r=val[u];r<100;++r)
		for(int l=0;l<=val[u];++l)
			if(dp[l].test(r))
				S[u].push_back(segment(l,r));
}
int main(){
	int n;read(n);
	for(int i=1;i<=n;++i)
		read(val[i]),--val[i];
	for(int i=2;i<=n;++i){
		int u,v;
		read(u),read(v);
		bro[v]=son[u],son[u]=v;//建树 
	}
	dfs(1);
	write(S[1].size()),putchar('\n');//输出答案 
	return 0;
}

```

---

## 作者：xiao7_Mr_10_ (赞：0)

# 前言

做这题还是因为看了隔壁机房讲题，然后发现隔壁机房有人写了题解，我就也水一下……

# 正文

翻译一下条件吧：

- 选的这些点必须是一个包括根节点的**联通块**。

- 点的集合**不超过**值域 $V$，权值不等。

- 对于每一个被选点 $u$，子树备选点权值必须是**连续区间** $[l,r]$。

这些条件引导我们做树形 dp。然后我们有一个很简单的设计思路就是：设 $f_{u,l,r}$ 表示子树 $u$ 内必选点 $u$，是否可以恰好选取区间 $[l,r]$ 的数。

这是好做的，直接分类讨论 $a_v$ 与 $a_u$ 的大小关系，然后类似区间 dp 的拼接思想枚举断点 $k$ 判断转移，可以做到 $O(nV^2)$，时间卡的很紧。当然如果你用 bitset 优化或者常数写好看点也是能过的。

然而我们有更快的做法，缩减状态数。由题目性质可得合法区间满足 $a_u \in [l,r]$，可以看做是两个区间 $[l,a_u]$ 与 $[a_u,r]$，显然是可以拼接的。

所以我们把状态设计为 $L_{u,i}$ 表示 $u$ 中子树是否可以恰好选取区间 $[i,a_u]$ 中的数。$R_{u,i}$ 表示 $u$ 中子树是否可以恰好选取区间 $[a_u,i]$ 中的数。

分开转移，和处理 $f_{u,l,r}$ 的方式一样，求答案是好做的，直接乘法原理统计合法区间乘积即可，可以做到 $O(nV)$，追求速度用 bitset 优化可以做到 $O( \frac{nV}{w})$。

这是部分代码：

```cpp
void dfs(int u,int fa){
	L[u][a[u]]=R[u][a[u]]=1;
	for(int i = 0;i < e[u].size();i++){
		int v=e[u][i];
		if(v==fa)continue;
		dfs(v,u);	
		if(a[v]>a[u]&&((R[u]<<1)&L[v]).count())R[u]|=R[v];	
	}
	for(int i = e[u].size()-1;i >= 0;i--){
		int v=e[u][i];
		if(v==fa)continue;
		if(a[v]<a[u]&&((L[u]>>1)&R[v]).count())L[u]|=L[v];
	}
}
```

---

## 作者：Emplace (赞：0)

# 思路
这道题是一道十分巧妙的树形DP。

其中 $dpl_{x,i}$ 表示以结点 $x$ 为根的子树当中，等差数列的首项为 $i$ 是否可行。$dpr_{x,i}$ 表示已结点 $x$ 为根的子树中等差数列末项为 $x$ 为根是否可行。其中 $dpl_{x,i}$ 中的 $i$ 要满足 $i \le v_u$，$dpr_{x,i}$ 中的 $i$ 要满足 $i \ge v_u$（题目要求当选了一个结点后必须选它的上司，与就是父亲结点）。

那对于 $dpl_{x,i}=1$ 需要 $x$ 的一个子节点 $y$ 中 $dpl_{y,i}=1$。然后发现，如果想要让 $dpl_{x,i}=1$，还需要让 $y$ 的整颗子树能与 $x$ 组成等差数列，并且必须是与笑话编号比 $x$ 小的组成，不然它就无法成为等差数列的首项。既然必须是 $x$ 的首项，那 $y$ 中就必须是末项。

对于 $dpr_{x,i}$ 是一样的，只需把上面全都反过来。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,v[20000],h[20000],ne[20000],e[20000],idx,l[20000][200],r[20000][200];
void add(int u,int v){
	e[idx]=v,ne[idx]=h[u],h[u]=idx++;
} 
void dfs(int x){
	vector<int> tl,tr;
	for(int i=h[x];~i;i=ne[i]){
		int j=e[i];
		dfs(j);
		if(v[j]<v[x]) tl.push_back(j);
		if(v[j]>v[x]) tr.push_back(j);
	}
	l[x][v[x]]=1,r[x][v[x]]=1;
	for(int i=v[x]-1;i>=1;i--){
		for(auto p:tl){
			if(l[p][i]){
				for(int j=i;j<v[x];j++){
					if(r[p][j]&&l[x][j+1]){
						l[x][i]=1;
						break;
					}
				}
			}
		} 
	}
	for(int i=v[x]+1;i<=100;i++){
		for(auto p:tr){
			if(r[p][i]){
				for(int j=v[x]+1;j<=i;j++){
					if(l[p][j]&&r[x][j-1]){
						r[x][i]=1;
						break;
					}
				}
			}
		} 
	}
}
int main(){
	memset(h,-1,sizeof(h));
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>v[i];
	}
	for(int i=1;i<=n-1;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
	}
	dfs(1);
	int lans=0,rans=0;
	for(int i=1;i<=100;i++){
		lans+=l[1][i];
		rans+=r[1][i]; 
	}
	cout<<lans*rans;
	return 0;
}

```

---

## 作者：XuYueming (赞：0)

## 前言

题目链接：[洛谷](https://www.luogu.com.cn/problem/P6534)。

[更好的体验](https://www.cnblogs.com/XuYueming/p/18316367)。

## 题意简述

一棵有根树，节点数 $n \leq 10^5$，每个点有权值 $v_i \leq 2000$，现在选出一些点，满足：

1. 一个点的父亲点若未被选择则其不能被选择。
1. 所选点的集合内不能有相同的权值。
1. 对于每一个选择的点，其子树中所有被选择点的权值必须可以构成公差为 $1$ 的等差数列。

求满足上述条件构成的等差数列的方案数。

## 题目分析

凭直觉是树形 DP。考虑记 $f[i][l][r]$ 表示在 $i$ 子树，$i$ 必选，能否构成 $l \sim r$ 的等差数列。发现有冗余状态，即由于 $i$ 必选，一定有 $l \leq v_i \leq r$，其他状态是不合法的。

进一步发现，对于 $yzh \in \operatorname{son}(i)$，她对 $i$ 的贡献要么全在 $v_i$ 左边，要么全在右边，否则会因为已经选中了一个权值为 $v_i$ 的点不符合要求。进一步发现，如果 $v_{yzh} < v_i$，她只能贡献左边，反之如果 $v_{yzh} > v_i$ 贡献右边。即 $yzh$ 不会对 $i$ 两边都产生贡献。

所以将状态砍半，记 $L[i][l]$ 和 $R[i][r]$ 分别表示在 $i$ 子树，$i$ 必选，能否构成 $l \sim v_i$ 的等差数列或 $v_i \sim r$ 的等差数列。边界为 $L[i][v_i] = R[i][v_i] = \text{true}$。由于讨论过一个孩子不可能对左右多产生贡献，所以 $L$ 和 $R$ 是独立的，答案就是乘法原理，$L[1]$ 中为 $\text{true}$ 的个数与 $R[1]$ 中为 $\text{true}$ 的个数之积即为答案。

说了这么多，考虑转移。考虑 $v_{yzh} < v_i$ 的情况，反之同理。如果存在一个值 $k$，满足在 $yzh$ 中能够得到 $v_{yzh} \sim k$，并且在之前的 $i$ 中能够得到 $k + 1 \sim v_i$，那么，就可以把 $L[yzh]$ 或到 $L[i]$ 上。需要注意的是，转移的顺序也要考虑。即我们要先考虑 $v_{yzh}$ 靠近 $v_i$ 的孩子，这样后续可能会使用到这次更新过来的信息。

时间复杂度：$\Theta(n(V + \log n))$，如果使用 `bitset` 优化，则是：$\Theta(\cfrac{nV}{w} + n \log n)$。

## 代码

```cpp
// #pragma GCC optimize(3)
// #pragma GCC optimize("Ofast", "inline", "-ffast-math")
// #pragma GCC target("avx", "sse2", "sse3", "sse4", "mmx")
#include <iostream>
#include <cstdio>
#define debug(a) cerr << "Line: " << __LINE__ << " " << #a << endl
#define print(a) cerr << #a << "=" << (a) << endl
#define file(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout)
#define main Main(); signed main() { return ios::sync_with_stdio(0), cin.tie(0), Main(); } signed Main
using namespace std;

#include <algorithm>
#include <vector>
#include <bitset>

int n, val[100010];
vector<int> edge[100010];
bitset<2010> L[100010], R[100010];

void dfs(int now) {
	L[now][val[now]] = R[now][val[now]] = 1;
	for (const auto& to: edge[now]) dfs(to);
	for (int i = 0; i < (int)edge[now].size(); ++i) {
		int to = edge[now][i];
		if (val[to] > val[now]) {
			if (((R[now] << 1) & L[to]).any()) {
				R[now] |= R[to];
			}
		}
	}
	for (int i = (int)edge[now].size() - 1; i >= 0; --i) {
		int to = edge[now][i];
		if (val[to] < val[now]) {
			if (((L[now] >> 1) & R[to]).any()) {
				L[now] |= L[to];
			}
		}
	}
}

signed main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &val[i]);
	for (int i = 1, u, v; i <= n - 1; ++i) {
		scanf("%d%d", &u, &v);
		edge[u].push_back(v);
	}
	for (int i = 1; i <= n; ++i)
		sort(edge[i].begin(), edge[i].end(), [] (const int &a, const int &b) {
			return val[a] < val[b];
		});
	dfs(1);
	printf("%llu", L[1].count() * R[1].count());
	return 0;
}
```

---

