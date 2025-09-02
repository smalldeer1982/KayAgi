# Game Master

## 题目描述

$n$ 个选手正在进行一场比赛。

这场比赛有两个场地。现已明确每个选手在两个场地上的力量值。

有 $n-1$ 场交锋。每次交锋，裁判员从剩余的选手中任选两个，并从两个场地中任选一个。两个选手中，在该场地力量较弱的，会被淘汰。经过 $n-1$ 场交锋后，最终会剩下一位选手，为胜者。

对于每一个选手，判断他是否有机会成为胜者。

本题多测，每个测试点有 $t$ 组数据。

## 样例 #1

### 输入

```
3
4
1 2 3 4
1 2 3 4
4
11 12 20 21
44 22 11 30
1
1000000000
1000000000```

### 输出

```
0001
1111
1```

# 题解

## 作者：Fan_sheng (赞：5)

一道比较显然的隐式图问题。


## 转化
我们考虑一种情况：选手 A 想要获胜，但是存在一个选手 B，A 在两个场地中都无法击败 B，那么应该怎么处理呢？

我们需要找到一个选手 C 来击败 B，这样 A 就不需要直接面对 B 了。如果 A 也无法击败 C 呢？

显然，这个问题具有传递性。我们最终的目的就是要找到一条长得像 $A\rightarrow K\rightarrow \cdots \rightarrow D \rightarrow C \rightarrow B$ 一样的链，使得 A 最终能够击败 K，那么 A 就能击败这条链上的所有选手。

## 思路
考虑对于每个选手建一个点，如果 A 能够在任意一个场地中击败 B，我们就从 A 到 B 连一条有向边。如果从 A 出发可以走到某一个点，说明 A 能够击败这个选手。如果从 A 出发可以遍历全图，说明 A 有可能取得冠军。

这样，对图上每个强连通分量 tarjan 缩点后，**有且只有一个点没有入度，只有在这个点内的所有选手可能成为冠军**，我们找到这个点就解决问题。

简单证明一下：如果缩点后，有边 $u \rightarrow v$，v 无论怎样都不可能打败 u ，就不可能是冠军。又因为可以成为冠军的人可以遍历到其他所有节点，那么他们一定被缩在一个点里，这个点没有入度且能遍历到其他所有节点。

## 建边的优化
在真正写代码的时候，我们会发现，如果真的把每个击败关系都建成边，可以达到 $\mathbb O(n^2)$ 的复杂度，需要优化。实际上，考虑以下的情况： 如果有两条边 $A \rightarrow B$ 和 $B \rightarrow C$,由于具有传递性，$ A \rightarrow C$ 这条边建了跟没建一样。

如果我们对 $a_i$ 和 $b_i$ 排序，只连接排序后大小相邻的两个选手之间的边，就能达到优化为 $\mathbb O(n)$ 的效果。

## 代码
习惯压行，看着很丑陋。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,head[100005],flag,dfn[100005],low[100005],st[100005],color[100005],timer,cnt;
bool in[100005];
struct star{
	int to,nxt;
}edge[400005],po[100005];
inline void add(int u,int v){
	edge[++flag]=(star){v,head[u]};head[u]=flag;
}
bool cmp(star a,star b){
	return a.nxt<b.nxt;
}
inline void clear(){
	memset(dfn,0,sizeof(dfn));memset(low,0,sizeof(low));
	memset(head,0,sizeof(head));flag=timer=cnt=0;
}
void tarjan(int id){
	dfn[id]=low[id]=++timer,in[id]=1,st[++st[0]]=id;
	for(int i=head[id];i;i=edge[i].nxt){
		int v=edge[i].to;
		if(!dfn[v]){
			tarjan(v);low[id]=min(low[id],low[v]);
		}
		else if(in[v])low[id]=min(low[id],dfn[v]);
	}
	if(dfn[id]==low[id]){
		cnt++;
		while(st[st[0]]!=id)color[st[st[0]]]=cnt,in[st[st[0]]]=0,st[0]--;
		color[id]=cnt,in[id]=0,st[0]--;
	}
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);clear();
		for(int times=1;times<=2;times++){//读入a和b，相当于循环两次 
			for(int i=1;i<=n;i++){
			   scanf("%d",&po[i].nxt);po[i].to=i;
		    }
		    sort(po+1,po+n+1,cmp);
		    for(int i=2;i<=n;i++)add(po[i].to,po[i-1].to);
		}
		for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i);
		for(int i=1;i<=n;i++)
		for(int j=head[i];j;j=edge[j].nxt){
			int v=edge[j].to;if(color[i]!=color[v])in[color[v]]=1;
			//in之前是标记是否在tarjan栈内的，这里被我用来标记是否有入度了 
		}
		for(int i=1;i<=n;i++)putchar(in[color[i]]?'0':'1');putchar('\n');
	}
	return 0;
}
```


---

## 作者：Sword_K (赞：5)

# CF1608C Game Master

提供一种没在题解区看到的解法。

如果简单的考虑一个人是否可以通过自己不断地改变 $a,b$ 场地来获得最终的胜利是连样例都过不了的。为什么呢？举个例子：某个人的战斗力分别是 $4$ 和 $1$  ，而另一个人是 $5$ 和 $2$ ，那么现在看来前者永远赢不了。但如果这时候来了一个人是 $3$ 和 $3$ ，那么他就可以先让这个人把那个啥都比他强的人干掉，然后自己把他干掉。

所以这道题的限制条件看上去比较复杂，但仔细思考一下这个例子可以发现，设两个人的战斗力分别是 $(a_1,b_1),(a_2,b_2)$ ，如果有
$$
(a_1>a_2\wedge b_1<b_2)\vee(a_1<a_2\wedge b_1>b_2)
$$
那么这两个人的胜负关系是等价的，即他们要么都能赢，要么都会输。

证明比较简单，他们可以利用双方较大的值来将两个人“合并”成一个人，战斗力为 $(\max(a_1,a_2),\max(b_1,b_2))$ ，如果能把其他人干掉，那他们可以最后可以随便选一个人赢；如果干不掉，那他们自己肯定干不掉。

有这个条件好像就可以像大多数题解一样建图搞了，但我是建立了坐标系。

把每个人看成一个二维坐标上的点，坐标为 $(a,b)$ 。

那么，如果两个点的胜负关系等价，他们的位置关系如图所示：

![img](https://cdn.luogu.com.cn/upload/image_hosting/3ajwzg4q.png?x-oss-process=image/resize,m_lfit,h_1000,w_1000)

那我们可以在这样的所有点对之间连一条线（其实就是图论的连边），然后由于 $a$ 最大的点肯定可以获胜，所以所有和 $a$ 最大的点联通的点都可以获胜。然后考虑如果暴力连边的话复杂度是 $O(n^2)$ 的。于是可以考虑这样一件事情：我们只考虑和 $a$ 最大的点联通的点，把当前已经确定联通的点全部拿出来，画出这样一个图：

![img](https://cdn.luogu.com.cn/upload/image_hosting/jg9ueeiv.png?x-oss-process=image/resize,m_lfit,h_1000,w_1000)

为啥要这样干呢？因为考虑到一个点它可以连线到的点所在范围长这样子：

![img](https://cdn.luogu.com.cn/upload/image_hosting/bzdg6glm.png?x-oss-process=image/resize,m_lfit,h_1000,w_1000)

那么，这些点共同形成的有效区域即为这个样子：

![img](https://cdn.luogu.com.cn/upload/image_hosting/06qo7za7.png?x-oss-process=image/resize,m_lfit,h_1000,w_1000)

其实容易发现有效区域只由四条线决定：$x=\max\{a\},x=\min\{a\},y=\max\{b\},y=\min\{b\}$ 。

然后就可以考虑维护有效区域来连边了：

先对所有点按 $a$ 从小到大排序。用一个 set 存之前处于非有效区域的点（有效区域只会随点数的增加变大，之前不处于有效区域的之后可能处于）。倒着考虑，第一个点肯定满足要求。然后依次考虑加进来的每个点。

由于是按 $a$ 从大到小加的，所以当前点的位置关系其实只有两种情况：

![img](https://cdn.luogu.com.cn/upload/image_hosting/3adreuk7.png?x-oss-process=image/resize,m_lfit,h_1000,w_1000)

![img](https://cdn.luogu.com.cn/upload/image_hosting/4b0sx0eq.png?x-oss-process=image/resize,m_lfit,h_1000,w_1000)

（深蓝色线表示有效区域）

对于第一种情况，它不属于有效区域，那么就把它加入 set 。

对于第二种情况，它属于有效区域，那么就标记它合法，并更新有效区域且要维护 set 。

对于有效区域的更新其实很简单，因为排过序，所以决定一个点是否在有效区域内的唯一标准只有 $\min\{b\}$ ，大于它就在里面，反之不在（虽然对于这个点来说这个更新没有意义）。

然后考虑维护 set 。满足什么样条件的点会被新的有效区域覆盖并被标记合法呢？对于 $a$ 这一维，因为排过序，所以一定合法。而对于 $b$ 这一维，可以发现只要比当前点的 $b$ 小就行了。（注意这时就要更新 $\min\{b\}$ 了）

这样算法就结束了，实际实现的时候set用堆替换就行了。

---

## 作者：npqenqpve (赞：5)

### 题意：

给定 $n$ 个人分别在两张地图上的能力值，每次选出其中两人在任意地图上战斗，能力值低者被淘汰，获胜者为最后没被淘汰的那个人，问那些人可以通过控制比赛获胜，那些人一定无法获胜

### 思路：

考虑那些必败者，要么打不过任何人，要么能打过的人打不过任何人，要么能打过的人能打过的人打不过任何人，以此类推，考虑优化

不妨将两个能力值分别排序，并记录所属编号，从后往前扫，可以发现，如果存在一个位置 $i$，使得分别在两个图中前 $i$ 强的人都是某 $i$ 个人，那么它内部一定每个人都能在这 $i$ 个人的集合中获胜，并且不在这个集合中的任意一个人一定都打不过这个集合里的任意一个人，然后在这 $i$ 个人的集合中的人一定都能获胜，剩下的必败。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
pair<int,int>a[(int)(1e5+10)],b[(int)(1e5+10)];
set<int>s;
char ans[(int)(1e5+10)];
signed main()
{
    int t;cin>>t;
    while(t--)
    {
        int n;cin>>n;
        s.clear();
        for(int i=0;i<=n-1;i++) 
        {
            cin>>a[i].first;a[i].second=i;
        }
        for(int i=0;i<=n-1;i++)
        {
            cin>>b[i].first;b[i].second=i;
            ans[i]='0';
        }
        sort(a,a+n);sort(b,b+n);
        ans[n]=0;
        int i;
        for(i=n-1;i>=0;i--)
        {
            s.insert(a[i].second);
            s.insert(b[i].second);
            if(s.size()==n-i) break;
        }
        while(i<=n-1) ans[a[i].second]='1',i++;
        puts(ans);
    }
}
```



---

## 作者：Otomachi_Una_ (赞：4)

一道很喵的萌萌题。

## 题目简述
- 有 $n$ 个人。每个人有两个属性 $a_i,b_i$。
- 我们说一个人 $x$ 能打得过一个人 $y$ 当且仅当 $a_x>a_y||b_x>b_y$。
- 现在进行随机淘汰赛。求哪些人可以成为冠军。
- 多组数据，$t\leq100,\sum n\leq10^5$

## 解题思路
一开始想到了建图，但是显然不行。

我们对 $a_i,b_i$ 分别进行排序。假设排序后下标分别为 $id_1,id_2\dots id_n$，$ie_i,ie_2\dots ie_n$。

我们寻找一个**最小的** $i\in N^{+}$ 使得 $\{id_1,id_2\dots id_i\}=\{ie_1,ie_2\dots ie_i\}$。下面证明只有这些人可以成为冠军，这里使用数学归纳法。

我们证明这个命题：$P(x):$对于任意的 $j\leq x$，$id_j$ 可以成为冠军。

$P(1)$ 是显然成立的。

假设 $P(t-1)$ 成立，我们考虑 $P(t)(t\leq i)$，这只要证明 $id_t$ 可以成为冠军即可。

显然 $id_t\not =ie_t$（否则 $i$ 不是最小的），假设 $id_t=ie_s$。显然 $ie_s$ 可以打的过 $ie_t$。又让 $ie_t=id_r$。因为 $P(t-1)$ 成立，所以 $id_r$ 可以成为 $1,2\dots t-1$ 当中的冠军。然后再让 $id_t$ 打败 $ie_t$，$id_t$ 就成为了冠军。

所以上述命题成立。

又因为 $id_{i+1},id_{i+2}\dots id_n$ 两种实力都比 $id_1,id_2\dots id_i$ 差，所以他们不可能成为冠军。

所以我门只需要找到这样的 $i$ 即可。（详情看代码）

## 参考代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
#define ll long long 
const int MAXN=1e5+5;
int t,n;
struct aaa{
	int a,id;
}p[MAXN];
struct bbb{
	int b,id;
}q[MAXN];
bool cmp(aaa x,aaa y){return x.a>y.a;}
bool cmq(bbb x,bbb y){return x.b>y.b;}
bool used[MAXN];
int main(){
	cin>>t;
	while(t--){
		for(int i=1;i<MAXN;i++)
			used[i]=false;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>p[i].a,p[i].id=i;
		for(int i=1;i<=n;i++)
			cin>>q[i].b,q[i].id=i;
		sort(p+1,p+n+1,cmp);
		sort(q+1,q+n+1,cmq);
		int cnt=0;
		for(int i=1;i<=n;i++){
			used[p[i].id]=!used[p[i].id];
			used[q[i].id]=!used[q[i].id];
			if(p[i].id!=q[i].id){
				if(used[p[i].id]) cnt++;else cnt--;
				if(used[q[i].id]) cnt++;else cnt--;
			}
			//cout<<i<<" "<<cnt<<endl;
			if(cnt==0){
				for(int j=1;j<=i;j++)
					used[p[j].id]=true;
				for(int j=1;j<=n;j++)
					cout<<used[j];
				cout<<endl;
				break;
			}
		}
	}
	return 0;
} 
```


---

## 作者：enucai (赞：4)

~~**前言：我想再骂一下这场比赛的 fst。**~~

## 题意简述

有 $n$ 个人在玩游戏，第 $i$ 个人有两个能力值 $a_i$ 与 $b_i$。如果第 $i$ 个玩家的任意一个能力值大于第 $j$ 个玩家，则称第 $i$ 个玩家可战胜第 $j$ 个玩家。现在要进行 $n-1$ 场淘汰赛，问每个玩家是否有可能成为总冠军。输出一个长度为 $n$ 的 01 串表示答案。

数据范围 $n\le 10^5$。

## 思路简述

看着就像要把这些玩家放到无向图上，然后跑 tarjan 缩点。

但是，这里介绍一种贪心的方案。

首先先按照 $a$ 值的大小将玩家排序。然后求出排序后的序列的后缀 $b$ 最大值，称 $suf_i$。

从左往右扫的时候，记录一下前缀可能成为冠军的玩家的 $b$ 的最小值，称 $pre_i$。

初始排序后的第一个人肯定能成为冠军，直接用 $a$ 值滥杀。

对于后面的每一个人，如果 $suf_i>pre_i$，则他可能成为冠军，因为他可以先用 $a$ 杀掉他后面 $b$ 值最大的人，那个人的 $b$ 值又可以杀掉前面的某个冠军，那么他也就能成为冠军了。

对于 $pre$ 值：

- 如果 $ans_i=0$，则 $pre_{i+1}=pre_i$；

- 否则 $pre_{i+1}=\max(pre_i,b_i)$。

注意不能对所有的人都进行取 $\max$，因为后面的人杀掉一个前面无法成为冠军的人是没用的。~~（考场上就死在这里）~~

正确性的证明感性理解一下就好。

## 蒟蒻代码

**Talk is cheap, show me the code.**

```cpp
int n;
struct node{
	int id,a,b;
}a[100010];
int ans[100010],M[100010],Md[100010];
bool cmp1(node x,node y){
	return x.a>y.a;
}
void work(){
	n=read();
	For(i,1,n) a[i].id=i,a[i].a=read();
	For(i,1,n) a[i].b=read();
	sort(a+1,a+n+1,cmp1);
	For(i,1,n) ans[i]=0;
	M[n+1]=0;
	Rof(i,n,1){
		if(a[i].b>M[i+1]) M[i]=a[i].b,Md[i]=i;
		else M[i]=M[i+1],Md[i]=Md[i+1];
	}
	int mn=1000000007;
	For(i,1,n){
		if(M[i]>mn||i==1){
			ans[a[i].id]=1;
			ckmn(mn,a[i].b);
		}
	}
	For(i,1,n) printf("%d",ans[i]);
	puts("");
}
signed main(){
	int T=read();
	while(T--) work();
}
```

---

## 作者：0xFF (赞：4)

### 题意简述：

给定 $n$ 个人分别在两张地图上的能力值，每次选出其中两人在任意地图上战斗，能力值低者被淘汰，获胜者为最后没被淘汰的那个人，问哪些人可以通过控制比赛获胜，哪些人一定无法获胜。

### 思路：
根据题意建一张有向图。一条从 $a$ 到 $b$ 的边代表 $a$ 可以击败 $b$。
考虑一种情况：$A$ 在两张地图里都无法击败 $B$，那么 $A$ 想要获胜就必须找到一个 $C$ 来击败 $B$，同时 $C$ 要满足可以被 $A$ 击败才能满足 $A$ 获胜。但是如果 $C$ 也不能满足被 $A$ 击败那么就需要找到一个 $D$ 来击败 $C$ 同时还要被 $A$ 击败，以此类推……
我们的目标就是找一条链 $A→M→…→D→C→B$ 使得 $A$ 能够最终击败 $M$。

综上结论我们就得到了本题的解决思路：对于每个选手建一个点，如果 $A$ 能够在任意一个场地中击败 $B$，我们就从 $A$ 到 $B$ 连一条有向边。如果从 $A$ 出发可以走到某一个点，说明 $A$ 能够击败这个选手。如果从 $A$ 出发可以遍历全图，说明 $A$ 有可能成为冠军。

对图上每个强连通分量通过 Tarjan 算法缩点后，必然有且只有一个点没有入度，只有在这个点内的所有选手才可能成为冠军，我们只需找到这个点来解决问题。

### 其他的一些问题：
如果把每两个人之间的关系都建一条边那么复杂度将会达到  $O(N^2)$。考虑两者之间的关系具有传递性: $A→B$ 和 $B→C$ 等同于 $A→C$ 故不需要建 $A→C$ 这条边。

解决方式就是将 $a$ 和 $b$ 分别排序，只连接相邻两个选手之间的边，故可将时间复杂度降至 $O(N)$。


### 代码实现：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<cctype>
#include<queue>
using namespace std;
const int maxn = 1e5 + 7;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}//快读 
int T,n,head[maxn],tot,dfn[maxn],low[maxn],stk[maxn],col[maxn];
int timer,cnt;
bool vis[maxn];
struct node{
	int to,next;
}edge[maxn<<2],pos[maxn];
inline void addedge(int u,int v){
	edge[++tot].to = v;
	edge[tot].next = head[u];
	head[u] = tot;
}
bool cmp(node a,node b){
	return a.next<b.next;
}
inline void clear(){
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(head,0,sizeof(head));
	tot=timer=cnt=0;
}
void tarjan(int id){
	dfn[id]=low[id]=++timer;
	vis[id]=1;
	stk[++stk[0]]=id;
	for(int i=head[id];i;i=edge[i].next){
		int v=edge[i].to;
		if(!dfn[v]){
			tarjan(v);
			low[id]=min(low[id],low[v]);
		}
		else if(vis[v])
			low[id]=min(low[id],dfn[v]);
	}
	if(dfn[id]==low[id]){
		cnt++;
		while(stk[stk[0]]!=id)
			col[stk[stk[0]]]=cnt,vis[stk[stk[0]]]=0,stk[0]--;
		col[id]=cnt,vis[id]=0,stk[0]--;
	}
}
int main(){
	T = read();
	while(T--){
		n = read();
		clear();
		for(int i=1;i<=2;i++){ 
			for(int j=1;j<=n;j++){
			   pos[j].next = read();
			   pos[j].to=j;
		    }
		    sort(pos+1,pos+n+1,cmp);
		    for(int j=2;j<=n;j++)
				addedge(pos[j].to,pos[j-1].to);
		}
		for(int i=1;i<=n;i++)
			if(!dfn[i]) tarjan(i);
		for(int i=1;i<=n;i++)
			for(int j=head[i];j;j=edge[j].next){
				int v=edge[j].to;
				if(col[i]!=col[v])
					vis[col[v]]=1; 
		}
		for(int i=1;i<=n;i++)
			putchar(vis[col[i]]?'0':'1');
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：Troubadour (赞：3)

赛时想到了做法，没有调出来，然后赛后半小时直接切掉了……

不过来看排名比预想的要高，可能是因为大家都 FST 在了这题的多组数据上。

我们考虑，一个人可以战胜别人，当且仅当有一项能力值比对方要高。

所以我们根据这个被击败关系，对于一个人的每项能力，分别向所有这项能力比自己高的人连边，维护包含第一项能力最高的人和第二项能力最高的人的连通块，在这个连通块里的人都有可能获胜。

具体如何实现呢，我们考虑**线段树优化建图**，以能力值为下标开两棵线段树，每次从这个人的点向能力比他大的这段区间连边即可。

### Code:
```cpp
#include<bits/stdc++.h>
namespace GGMZ
{
	const int N = 1e5 + 5;
	struct edge
	{
		int to, nxt;
	}e[N << 5];
	int head[N << 5], cnt;
	void add(int u, int v)
	{
		cnt++;
		e[cnt].to = v;
		e[cnt].nxt = head[u];
		head[u] = cnt;
	}
	int val1[N], val2[N];
	std::vector<int>g;
	int fval1[N], fval2[N];
	int num[N];
	struct seg
	{
		int l, r, val;
	}f[N << 2];
	void build(int p, int l, int r)
	{
		f[p].l = l, f[p].r = r;
		if (l == r)
		{
			f[p].val = fval1[l];
			add(p, num[fval1[l]]);
			return;
		}
		int mid = (l + r) >> 1;
		build(p << 1, l, mid);
		build(p << 1 | 1, mid + 1, r);
		add(p, p << 1);
		add(p, p << 1 | 1);
	}
	int s;
	void add(int p, int l, int r, int u)
	{
		if (l <= f[p].l&&f[p].r <= r)
		{
			add(u, p);
			return;
		}
		int mid = (f[p].l + f[p].r) >> 1;
		if (mid >= l)add(p << 1, l, r, u);
		if (mid < r)add(p << 1 | 1, l, r, u);
	}
	int rr = N * 4 + 5;
#define f f1
	struct seg1
	{
		int l, r, val;
	}f[N << 2];
	void build1(int p, int l, int r)
	{
		f[p].l = l, f[p].r = r;
		if (l == r)
		{
			f[p].val = fval2[l];
			add(p + rr, num[fval2[l]]);
			return;
		}

		int mid = (l + r) >> 1;
		build1(p << 1, l, mid);
		build1(p << 1 | 1, mid + 1, r);
		add(p + rr, (p << 1) + rr);
		add(p + rr, (p << 1 | 1) + rr);
	}
	void add1(int p, int l, int r, int u)
	{
		if (l <= f[p].l&&f[p].r <= r)
		{
			add(u, p + rr);
			return;
		}
		int mid = (f[p].l + f[p].r) >> 1;
		if (mid >= l)add1(p << 1, l, r, u);
		if (mid < r)add1(p << 1 | 1, l, r, u);
	}
#undef f
	bool vis[N << 5];
	void bfs()
	{
		std::queue<int>q;
		q.push(s);
		vis[s] = 1;
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			for (int i = head[u];i;i = e[i].nxt)
			{
				int v = e[i].to;
				if (!vis[v])
				{
					vis[v] = 1;
					q.push(v);
				}
			}
		}
	}
	int n;
	void work()
	{
		using std::cin;
		cin >> n;
		for (int i = 1;i <= n;i++)
		{
			cin >> val1[i];
			g.push_back(val1[i]);
		}
		std::sort(g.begin(), g.end());
		int size = n;
		for (int i = 1;i <= n;i++)
		{
			val1[i] = std::lower_bound(g.begin(), g.begin() + size, val1[i]) - g.begin() + 1;
			fval1[val1[i]] = i;
		}
		g.clear();
		for (int i = 1;i <= n;i++)
		{
			cin >> val2[i];
			g.push_back(val2[i]);
		}
		std::sort(g.begin(), g.end());
		size = n;
		for (int i = 1;i <= n;i++)
		{
			val2[i] = std::lower_bound(g.begin(), g.begin() + size, val2[i]) - g.begin() + 1;
			fval2[val2[i]] = i;
		}
		g.clear();
		for (int i = 1;i <= n;i++)
		{
			num[i] = N * 10 + i;
		}
		build1(1, 1, n);
		build(1, 1, n);
		s = n * 20 + 2;
		for (int i = 1;i <= n;i++)
		{
			add(1, val1[i], n, num[i]);
			add1(1, val2[i], n, num[i]);
		}
		add(s, num[fval1[n]]);
		add(s, num[fval2[n]]);
		bfs();
		for (int i = 1;i <= n;i++)
		{
			std::cout << vis[num[i]];
		}
		memset(vis, 0, sizeof(vis));
		memset(head, 0, sizeof(head));
		cnt = 0;
		puts("");
	}
}
int main()
{
	int t;
	std::cin >> t;
	while (t--)GGMZ::work();
	return 0;
}
```

---

## 作者：Hooch (赞：2)

### 题目大意

有 $n$ 个选手正在两张不同的地图中比赛。

所有选手都有两个**力量值**，代表选手在两张地图中的实力，第 $i$ 位选手的力量值是 $x_i$ 和 $y_i$。

你可以指定两个选手在任意一张地图上决斗，而决定他们谁胜谁负的就是他们在**这张地图**上的实力的大小，实力**强**的选手胜，另一位选手被淘汰。

你要输出一个 $01$ 序列，第 $i$ 个元素代表选手 $i$ 是否可能成为最后一个**不被淘汰**的人。

### 思路

我们可以把每个人的**强弱关系**看成一个图，如果 $x_i>x_j$ 或者  $y_i>y_j$，那么就连一条 $i\to j$ 的边。

可是这样建边的时间复杂度为 $Θ(n^2)$，我们发现按 $x$ 从小到大排序之后只需要建 $pos_i\to pos_{i-1}$ 的边就行了（$pos$ 是排序之后的原数组下标）。

若想要使用 $pos_i\to pos_{i-2}$ 这条边（$i>2$），只需要经过 $pos_i\to pos_{i-1}$ 和 $pos_{i-1}\to pos_{i-2}$ 这两条边就行了。

接着我们发现建出来的图不一定是个 DAG，会形成**环**，因为有可能出现 $x_i>x_j\land y_j>y_k\land x_k>x_i$ 的情况。

所以我们缩点，缩了之后找**入度为 $0$** 的强连通分量，因为缩点后是一个 DAG，而入度为 $0$ 的点可以通向任意一个点。所以其中的所有点都可以成为最后的赢家。

### 代码

代码：

```cpp
#include <bits/stdc++.h>
#define rep1(i, j, n) for (register int i = j; i <= int(n); ++i)
#define rep2(i, j, n) for (register int i = j; i >= int(n); --i)
#define il inline
using namespace std;
namespace D_K_D {
	const int Buffer_Size = 1 << 10;
	char buffer[Buffer_Size], *ihead = buffer + Buffer_Size, *itail = ihead;
	char Next_Char() {
		if (ihead == itail) fread(buffer, 1, Buffer_Size, stdin), ihead = buffer;
		return *ihead++;
	}
	template <typename T>
	il void read(T &x) {
		x = 0; T f = 1; char ch = Next_Char();
		while (!isdigit(ch)) {if (ch == '-') f = -1; ch = Next_Char();}
		while (isdigit(ch)) {x = (x << 1) + (x << 3) + (ch & 15); ch = Next_Char();} x *= f;
	}
}
using namespace D_K_D;
const int N = 1e5 + 5, inf = 0x3f3f3f3f, mod = 1;
struct node {int x, y, pos; } a[N];
int t, n;
bool qs[N];
il bool cmp1(const node &x, const node &y) {return x.x < y.x;}
il bool cmp2(const node &x, const node &y) {return x.y < y.y;}
struct A {int to, nxt;} edge[N << 1]; int tot, head[N], nxt[N << 1];
il void add(int x, int y) {edge[++tot] = (A) {x, y}; nxt[tot] = head[x]; head[x] = tot;}
int dfn[N], low[N], cnt, cl, col[N]; bool vis[N]; stack <int> st;
il void tarjan(int x) {
	dfn[x] = low[x] = ++cnt; vis[x] = 1;
	st.push(x);
	for (int i = head[x]; i; i = nxt[i]) {
		int v = edge[i].nxt;
		if (!dfn[v]) tarjan(v), low[x] = min(low[x], low[v]);
		if (vis[v]) low[x] = min(low[x], dfn[v]);
	}
	if (dfn[x] == low[x]) {
		++cl; int tt;
		do {
			tt = st.top();
			vis[tt] = 0; col[tt] = cl;
			st.pop();
		} while (tt ^ x); 
	}
} int in[N];
signed main(void) {
	read(t);
	while (t--) {
		memset(a, 0, sizeof a); memset(col, 0, sizeof col);
		memset(head, 0, sizeof head); memset(nxt, 0, sizeof nxt);
		memset(in, 0, sizeof in); memset(qs, 0, sizeof qs); cnt = tot = 0;
		memset(dfn, 0, sizeof dfn); memset(low, 0, sizeof low); //初始化
		read(n);
		rep1(i, 1, n) read(a[i].x), a[i].pos = i;
		rep1(i, 1, n) read(a[i].y);
		sort(a + 1, a + 1 + n, cmp1);
		rep1(i, 2, n) add(a[i].pos, a[i - 1].pos);
		sort(a + 1, a + 1 + n, cmp2);
		rep1(i, 2, n) add(a[i].pos, a[i - 1].pos); //建边
		rep1(i, 1, n) if (!dfn[i]) tarjan(i);
		rep1(i, 1, n) {
			for (int j = head[i]; j; j = nxt[j]) {
				int v = edge[j].nxt;
				if (col[v] != col[i]) ++in[col[v]];
			}
		}
		rep1(i, 1, cl) 
			if (!in[i]) qs[i] = 1;//找入度为 0 的点
		rep1(i, 1, n) printf("%d", qs[col[i]]); puts("");
	}
}
```

---

## 作者：清烛 (赞：1)

## Description
$n$ 个玩家正在玩一个游戏。

游戏有 $2$ 个竞技场，每个玩家在每个竞技场的实力 $a_i$、$b_i$ 已知，一场比赛中，实力大的一定打败实力小的。

每次可以指定没有被淘汰的两个玩家在一个竞技场内比赛，输者淘汰。

最后一个剩下的玩家获胜。

问，这 $n$ 个玩家中，有哪些玩家有可能获胜。

## Solution
我们将其建模成一张有向图。$u$ 可达 $v$ 说明 $u$ 能打败 $v$。乍一看发现要连 $O(n^2)$ 条边，其实不然。

对于 $i$ 号玩家，我们将其分别向 $j$ 和 $k$ 连边，其中 $a_j$ 是 $a_i$ 的前驱，$b_k$ 是 $b_i$ 的前驱。意思就是，只要 $a_i > a_j$ 或者 $b_i > b_j$，$i$ 就能赢 $j$。

当然这样连边是可能出现环的，代表环上的每个玩家都能打败整个环上的所有玩家。观察样例 $2$，发现整张图就是一个强连通分量。

我们将所有强连通分量 tarjan 缩点，然后会得到一张拓扑图。首先这张图必然连通，因为我们是按照 $a_i$ 和 $b_i$ 的偏序关系建的图。其次，入度为 $0$ 的强连通分量有且仅有一个。因为若出现多个，说明他们之间没有能打败/被打败的关系，这是不可能的。

因此，我们的做法就是，建图，缩点，找入度为 $0$ 的 SCC，这个 SCC 里面的点，都是能获胜的玩家。

## Implementation
放个丑陋的场上代码。

```cpp
const int maxn = 1e5 + 5;
vector<int> G[maxn];
int n, a[maxn], b[maxn], a0[maxn], b0[maxn], ia[maxn], ib[maxn];
int dfn[maxn], low[maxn], dfnClock, scc[maxn], ins[maxn], sccCnt, stk[maxn], top;
int ind[maxn];
int ans[maxn];

void tarjan(int u) {
    dfn[u] = low[u] = ++dfnClock;
    stk[++top] = u, ins[u] = 1;
    for (auto v : G[u]) {
        if (!dfn[v])
            tarjan(v), low[u] = min(low[u], low[v]);
        else if (ins[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        ++sccCnt;
        while (true) {
            int now = stk[top--];
            ins[now] = 0;
            scc[now] = sccCnt;
            if (now == u) break;
        }
    }
    return;
}

int main() {
    int T; read(T);
    while (T--) {
        read(n);
        FOR(i, 1, n) read(a[i]), a0[i] = a[i];
        FOR(i, 1, n) read(b[i]), b0[i] = b[i];
        sort(a0 + 1, a0 + n + 1), sort(b0 + 1, b0 + n + 1);
        FOR(i, 1, n) {
            a[i] = lower_bound(a0 + 1, a0 + n + 1, a[i]) - a0;
            b[i] = lower_bound(b0 + 1, b0 + n + 1, b[i]) - b0;
            ia[a[i]] = i, ib[b[i]] = i;
            G[i].clear();
            dfn[i] = low[i] = scc[i] = ins[i] = ind[i] = ans[i] = 0;
        }
        FOR(i, 1, n) {
            if (a[i] != 1)
                G[i].push_back(ia[a[i] - 1]);
            if (b[i] != 1)
                G[i].push_back(ib[b[i] - 1]);
        }
        sccCnt = dfnClock = 0;
        FOR(i, 1, n) if (!dfn[i]) tarjan(i);
        FOR(i, 1, n) {
            if (a[i] != 1 && scc[i] != scc[ia[a[i] - 1]])
                ++ind[scc[ia[a[i] - 1]]];
            if (b[i] != 1 && scc[i] != scc[ib[b[i] - 1]])
                ++ind[scc[ib[b[i] - 1]]];
        }
        int ansid = 0;
        FOR(i, 1, sccCnt) if (!ind[i]) ansid = i;
        FOR(i, 1, n) putchar(scc[i] == ansid ? '1' : '0');
        putchar('\n');
    }
    return output(), 0;
}
```

---

