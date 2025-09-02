# Mail Stamps

## 题目描述

One day Bob got a letter in an envelope. Bob knows that when Berland's post officers send a letter directly from city «A» to city «B», they stamp it with «A B», or «B A». Unfortunately, often it is impossible to send a letter directly from the city of the sender to the city of the receiver, that's why the letter is sent via some intermediate cities. Post officers never send a letter in such a way that the route of this letter contains some city more than once. Bob is sure that the post officers stamp the letters accurately.

There are $ n $ stamps on the envelope of Bob's letter. He understands that the possible routes of this letter are only two. But the stamps are numerous, and Bob can't determine himself none of these routes. That's why he asks you to help him. Find one of the possible routes of the letter.

## 样例 #1

### 输入

```
2
1 100
100 2
```

### 输出

```
2 100 1 ```

## 样例 #2

### 输入

```
3
3 1
100 2
3 2
```

### 输出

```
100 2 3 1 ```

# 题解

## 作者：Empty_Dream (赞：7)

# CF29C 解题报告

## 题意

有一封邮件，经过了 $n$ 个城市，每个城市会盖上一个邮戳，代表从城市 $u$ 向城市 $v$ 发送一个邮件。

保证不会经过重复的城市，并且确定只有两条路线。

题目有 **Special Judge**。

## 分析

从题意中确定只有两条路线且不经过重复的城市可得，邮票经过的城市可以看作一条链。

对于一条链，只需要确定一个起点，那么整个链都可以被遍历出来。因此，题目被转化成了求一条链的起点。

易得，一条链的起点只有一条边连着，在通过邻接表存完图后，直接遍历每一个点看是否只连了一条边就好了。

注意：此题点的编号巨大，高达 $1\times 10^9$，不能用传统的邻接表，需要用 map 去套一个 vector 记录每一个点的信息。

最后跑一遍 dfs，从起点开始，边遍历边输出。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
map<int, vector<int>> g;//用 map 套 vector

void dfs(int x, int fa){//因为是一条链，所以只需要记录 father
	cout << x << " ";//边遍历输出
	for (int i = 0; i < g[x].size(); i++){
		int v = g[x][i];
		if (v != fa) dfs(v, x);
	}
}

int main(){
	cin >> n;
	for (int i = 1, u, v; i <= n; i++){
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (auto it : g){//遍历每一个点
		if (it.second.size() == 1){//是否为起点
			dfs(it.first, -1);
			return 0;
		}
	}
	return 0;
}
```



---

## 作者：Minecraft万岁 (赞：3)

~~我迈出了 $AC$ 的一小步 却是题解的一大步~~   
本题解语言较为粗俗 望大佬们见谅  


------------

首先这道题是让我们求出 从某一个点开始 **不重复**的走完其他所有的点 **保证有解** 让你输出你是怎么走完点的 按顺序输出点的编号 ~~貌似有 SPJ~~  
我们考虑 $dfs$ 但是有一点较为毒瘤 ~~就是你选哪个点作为开始?~~    
题目中说有解 我们来几个例子 **自己画的图要符合题目条件**

- 某个点周围只有 $1$ 条路径时  
![](https://cdn.luogu.com.cn/upload/image_hosting/o2c7eui0.png)  
多试几个图 你会发现从 某个周围只有 $1$ 条路径的点出发 一定可以不重复的走完全部图的点 
- 没有上面的情况   
![](https://cdn.luogu.com.cn/upload/image_hosting/sjb39euj.png)   
那就~~毒瘤~~简单了 从哪一点开始都可以走完的  
于是我们确定了算法的主题 现在主要细节   
1. 题目中点的编号 $\leq 10^9$   
这样开 $vis[]$ 数组肯定炸 我们考虑离散化 也就是用 $map$ 映射 令 $mp[]$ 为从原来编号映射到数组可以存的下的**不重复**编号   
2. 怎么输出呢？  
我们可以在 $dfs$ 中递归输出 把 $dfs$ 的类型设置为 $bool$ 如果搜索到最后发现可以 输出并返回 $true$ 之前的 调用的 $dfs$ 中判断上一个的是否返回 $true$ 是的话也输出当前点的编号 也返回 $true$ 交给上一层就可以啦   
3. $dfs$ 中怎么输出真实的编号？   
我们考虑再搞一个 $map$ 就叫 $fmp[]$ 这家伙和 $mp[]$ 的作用相反 $fmp[]$ 为从数组可以存的下的编号映射到原来编号 于是就可以~~简洁的~~输出啦   

接下来就是愉快的代码啦 


------------
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<map>
#include<algorithm>
using namespace std;
typedef long long ll;
struct node
{
	int from;
	int to;
}e[200005];//链式前向星 
int head[100005],tot;//链式前向星标准变量 
map<int,int> mp;//真实编号->离散化编号 
map<int,int> fmp;//离散化编号->真实编号 
int np;//当前点的编号就是这个点是第几次出现的 
int n,x,y;
int st;//开始点 
int d[100005];//看看每个点周围有几条边 
bool vis[100005];//dfs中的标记访问数组 
inline void read(int &x)//快读 
{
	int f;char c;
	for (f=1,c=getchar();c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for (x=0;c<='9'&&c>='0';c=getchar()) x=x*10+(c&15);x*=f;
}
inline void add(int from,int to)//连边 
{
	e[++tot].to=to;
	e[tot].from=head[from];
	head[from]=tot;
}
inline int mn(int _x,int _y)
{
	return _x<_y?_x:_y;
}
inline int mx(int _x,int _y)
{
	return _x>_y?_x:_y;
}
inline int ab(int _x)
{
	if(_x<0) return -_x;
	else return _x;
}
inline bool dfs(int p,int dep)//bool类型的 dfs p:当前点的编号 dep:搜了几个点 用于结束循环 
{
	if(dep==np)//到这个点都搜完了 
	{
		printf("%d ",fmp[p]);//输出真实编号 
		return true;
	}
	for(int i=head[p];i;i=e[i].from)//访问所有的点 
	{
		if(!vis[e[i].to])//没有访问过的话 
		{
			vis[e[i].to]=true;//这个设置为访问过了 
			if(dfs(e[i].to,dep+1))//如果返回值为真 说明下一层是可行的 那么这层也同样可行  
			{ 
				printf("%d ",fmp[p]);//输出真实编号 
				return true;//同理 返回 true 
			}
			vis[e[i].to]=false;//dfs标准还原操作 
		}
	}
}
int main()
{
	read(n);
	for(int i=1;i<=n;i++)
	{
		read(x);read(y);
		if(!mp[x])//没有映射过 也就是新的点 
		{
			++np;//新出现的增加 1 个 
			mp[x]=np;//建立两个映射 
			fmp[np]=x;
		}
		if(!mp[y])//同上 
		{
			++np;
			mp[y]=np;
			fmp[np]=y;
		}
		add(mp[x],mp[y]);//把题目中的当成无向图 
		add(mp[y],mp[x]);
		d[mp[x]]++;//周围的边多了一个 
		d[mp[y]]++;
	}
	st=1;//设置为1 如果没有情况1 默认从1开始dfs 
	for(int i=1;i<=np;i++)
	{
		if(d[i]==1) st=i;//有了情况1 记一下 循环后就从这个开始 
	}
	vis[st]=true;//从这个开始 当然访问过了 
	dfs(st,1);//开始愉快的dfs 题目保证有解 
	puts(""); 
	return 0;
}



```


---

## 作者：XL4453 (赞：2)

### 解题思路：

评蓝有点高了。

其实没有那么复杂，由于题目保证有解，且每一个城市要不然作为起点，要不然被且仅被提到两次，所以直接建图，统计每一个点的度数，然后从任意一个度数为 $1$ 的点出发，遍历全图就可以了。

需要注意的是，本题中城市的编号可能很大，是离散的，导致不能直接用城市编号建图，所以考虑用一个 map 来进行离散化。建立一一对应的关系后再跑图就方便了。

---
### 代码：

```cpp
#include<cstdio>
#include<map>
using namespace std;
map <int,int> mp;
int head[200005],next_[200005],num[200005],n,cnt,x,y,d[200005],tot,re[200005],v[200005];
void add(int x,int y){
	next_[++cnt]=head[x];head[x]=cnt;num[cnt]=y;
}
void dfs(int now){
	v[now]=1;
	printf("%d ",re[now]);
	for(int i=head[now];i;i=next_[i])
	if(v[num[i]]==0)
	dfs(num[i]);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&x,&y);
		if(mp[x]==0)mp[x]=++tot,re[tot]=x;
		if(mp[y]==0)mp[y]=++tot,re[tot]=y;
		add(mp[x],mp[y]);add(mp[y],mp[x]);
		d[mp[x]]++;d[mp[y]]++;
	}
//	printf("%d",tot);
	for(int i=1;i<=n;i++)
	if(d[i]==1){
		dfs(i);
		return 0;
	}
	return 0;
}
```


---

## 作者：Jerrywang09 (赞：1)

### 先说几句

不好说难度问题。应该是链表的裸题。

### 解题思路

对于每行输入，都包含两个数，分别是起始点和终到点。

把每个数出现的次数统计，不难发现，只出现 $1$ 次的数肯定是这趟旅行的起始点或终点。

用 边表 保存输入。从上面找出的点出发，执行 dfs 或者 迭代。执行迭代时注意，用一个变量 $prev$ 表示上个点，以免发生死循环。

### 奉上代码

千万不要抄，小心棕名！

```cpp
// 29C Mail Stamps
#include <bits/stdc++.h>
#define var long long
#define SIZE 200010
#define debug(x) cout<<#x<<":"<<x<<endl;
using namespace std;

map<int, vector<int>> a;
map<int, int> m;

int main()
{
	int n; cin>>n;
	for(int i=0; i<n; i++)
	{
		int x, y; cin>>x>>y;
		a[x].push_back(y);
		a[y].push_back(x);
		m[x]++; m[y]++;
	}
	int v;
	for(auto x:m)
		if(x.second==1)
		{
			v=x.first;
			break;
		}
	int prev=-1;
	while(!(a[v].size()==1 && prev!=-1))
	{
		cout<<v<<" ";
		for(int to:a[v])
			if(to!=prev)
			{
				prev=v;
				v=to;
				break;
			}
	}
	cout<<v;

    return 0;
}
```

---

## 作者：YuYuanPQ (赞：0)

题意是让你遍历一条链。

找到入度为 $1$ 的点开始遍历即可。

因为题目有 **Special Judge**，所以 $2$ 种路线都可以。

```cpp
#include<bits/stdc++.h>
#define MAXN 100010
using namespace std;
int n;
int st;
map<int,int>in;
map<int,bool>b;
queue<int>q;
map<int,vector<int>>g;
int mmin(int x,int y){return x<y?x:y;}
void dfs(int x,int fa)
{
    printf("%d ",x);
    for(auto y:g[x])
    {
        if(y==fa) continue;
        dfs(y,x);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        g[x].push_back(y),g[y].push_back(x);
        in[x]++,in[y]++;
        if(!b[x]) q.push(x),b[x]=1;
        if(!b[y]) q.push(y),b[y]=1;
    }
    while(q.size())//找入度为1的点
    {
        int t=q.front();
        q.pop();
        if(in[t]==1)
        {
            dfs(t,0);
            break;
        }
    }
    putchar('\n');
    return 0;
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
既然这题没有环，又要用到所有的边，这不就是一条链嘛！直接找到任意一个度为 $1$ 的点作为起点后 dfs 一次，因为是一条链，所以 dfs 途中只要不走回头路就一定是一次就找到答案，时间复杂度 $O(n)$。
# 代码
```cpp
# include <bits/stdc++.h>
typedef long long ll;
using namespace std;
int n, du[100005], s, ans[100005], x, y, a[100005],tot;
bitset <100005> vis;
vector <int> v[100005];
map <int, int> mp;
void dfs (int x, int step) {
	ans[step] = x;
	if (step > n) {
		for (int i = 1; i <= step; ++ i)
			cout << a[ans[i]] << ' ';
		exit (0);
	}
	for (int& i : v[x])
		if (! vis[i])
			vis[i] = 1, dfs (i, step + 1), vis[i] = 0;
	return ;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n;
	for (int i = 0; i < n; ++ i) {
		cin >> x >> y;
		if (mp[x])
			x = mp[x];
		else
			mp[x] = ++ tot, a[tot] = x, x = tot;
		if (mp[y])
			y = mp[y];
		else
			mp[y] = ++ tot, a[tot] = y, y = tot;
		++ du[x];
		++ du[y];
		v[x].emplace_back (y);
		v[y].emplace_back (x);
	}
	for (int i = 1; i <= tot; ++ i)
		if (du[i] & 1) {
			s = i;
			break ;			
		}
	vis[s] = 1;
	dfs (s, 1);
	return 0;
}
```

---

## 作者：DengDuck (赞：0)

这题如果是蓝题，那么太阳会坠落，乌云会发愁。

建议评黄捏。

题意是遍历一个链，找到一个度数为 $1$ 的点直接遍历就行。

唐。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
#define fir first
#define sec second
using namespace std;
//const LL inf;
const LL N=1e5+5;
//const LL M;
//const LL mod;
//const LF eps;
//const LL P;
LL n;
map<LL,vector<LL>>v;
map<LL,LL>du;
void dfs(LL x,LL f)
{
	printf("%lld ",x);
	for(LL i:v[x])
	{
		if(i==f)continue;
		dfs(i,x);
	}
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		LL x,y;
		scanf("%lld%lld",&x,&y);
		du[x]++,du[y]++;
		v[x].pb(y),v[y].pb(x);
	}
	for(pLL i:du)
	{
		if(i.sec==1)
		{
			dfs(i.fir,0);
			return 0;
		}
	}
	dfs(1,0);
	return 0;
}
//RP++
```

---

## 作者：Ag2WO4 (赞：0)

注意审题，这题其实很简单！

“邮局的工作人员并不会将一封信寄往这封信之前到过的城市”，这说明整条路径只有两端是一条边，其他端点都是两条边。直接开字典记录每个点与其他哪些点连接，只连接一个点的就是起止点，路径中对于每个非起止点连接的另外两个点，一个是来源，一个是去路。处理数据、找起止点、遍历路径都是 $O(n)$ 的。
#### 代码
```Python
a={}
for i in range(int(input())):
    b,c=input().split()
    if b in a:a[b].append(c)
    else:a[b]=[c]
    if c in a:a[c].append(b)
    else:a[c]=[b]
for i in a:
    if len(a[i])==1:
        e=[i,a[i][0]]
        while len(a[e[-1]])-1:
            for j in a[e[-1]]:
                if j!=e[-2]:e.append(j);break
        print(' '.join(e));break
```

---

## 作者：Expert_Dream (赞：0)

 题目就是要在图中找一条经过所有边的链。实际上就是要找到这条链的起点，因为一个点度数为 $1$ 那么肯定是起点或者终点，那么找到度为 $1$ 的点为起点。然后从起点开始 dfs 暴力寻找路径，直到找到那个终点，然后因为有 SPJ 所以可以轻松通过此题目。因为每一个点的数值很大，所以我们需要 map 里放 vector。

```cpp
const int N = 2e5+5,M = 2e5+5;
int n;
map<int,int> vis;
map<int,int>mp;
map<int,vector<int> > s;
void solve(){
	cin >> n;
	for(int i = 1;i <= n;i++){
		int x,y;
		cin>>x>>y;
		mp[x]++,mp[y]++;
		s[x].pb(y);
		s[y].pb(x);
	}		
	int x;
	for(auto it:mp){
		if(it.se == 1){
			x = it.fir;
			break;
		}
	}
	vis[x]=1;
	while(1){
		cout<<x<<" ";
		int flag=1;
		for(auto it:s[x]){
			if(vis[it]==0){
				vis[it]=1;
				flag=0;
				x=it;
				break;
			}
		}if(flag) break;
	}
	
}

---

## 作者：_DeadPig_ (赞：0)

# CF29C

[题目](https://www.luogu.com.cn/problem/CF29C)大致意思就是给出多条路径的两个端点，求这条路径（正反皆可）

## 分析

- 首先因为题目的 SPJ，我们可以用链式前向星双向连边存图。

- 其次，我们可以看出，在给出的 $n$ 条路径中的 $2n$ 个端点中，只出现了**一次**的必定是**起点或终点**，因为在中间的端点，必定会有两个路径包括它，一个是以这个端点为起点的路径，一个是以这个端点为终点的路径，只要找出其中一个在输入中只出现了一次的端点，并以它为起点进行搜索，便可以确定所有端点的先后顺序。

- 想要实现上面的寻找起点，就要做一个计数，看到端点取值的数据范围 $1 \le x \le 10^9$，那么开一个桶来计数显然是不行的，这个时候我们需要用到 map 来进行一个离散化，用这个端点在输入中出现的编号来作为 key 值，映射这个端点的真实编号。

- 那么在 dfs 中如何输出这个城市的真实编号？我们可以再开一个 map，用端点的真实编号来映射端点在输入中出现的编号。

最后是 AC 代码。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct edge{
	int u,v;
}e[100005<<1];
int head[100010],ar[100010],tot=0;
int n,now,s;
bool vis[100010]={false};

map <int,int> mp;
map <int,int> fmp;

inline int read(){
	register int x=0,t=1;
	register char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') t=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*t;
}
inline void add(int u,int v){
	e[++tot].v=v;
	e[tot].u=head[u];
	head[u]=tot;
}
bool dfs(int noww,int sum){
	if(sum==now){
		cout<<fmp[noww]<<' ';
		return true;
	}
	for(int i=head[noww];i;i=e[i].u){
		if(!vis[e[i].v]){
			vis[e[i].v]=true;
			if(dfs(e[i].v,sum+1)){
				cout<<fmp[noww]<<' ';
				return true;
			}
			vis[e[i].v]=false;
		}
	}
}
signed main(){
	n=read(); 
	for(int i=1,x,y;i<=n;++i){
		x=read();y=read();
		++ar[mp[x]];
		++ar[mp[y]];
		add(mp[x],mp[y]);
		add(mp[y],mp[x]);
		if(!mp[x]){
			++now;
			mp[x]=now;
			fmp[now]=x;
		}
		if(!mp[y]){
			++now;
			mp[y]=now;
			fmp[now]=y;
		}
	}
	for(int i=1;i<=now;++i){
		if(ar[i]==1){
			s=i;
			break;
		}
	}
	vis[s]=true;
	dfs(s,1);
	return 0;
}
```

---

