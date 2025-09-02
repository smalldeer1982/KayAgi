# Don't fear, DravDe is kind

## 题目描述

A motorcade of $ n $ trucks, driving from city «Z» to city «З», has approached a tunnel, known as Tunnel of Horror. Among truck drivers there were rumours about monster DravDe, who hunts for drivers in that tunnel. Some drivers fear to go first, others - to be the last, but let's consider the general case. Each truck is described with four numbers:

- $ v $ — value of the truck, of its passangers and cargo
- $ c $ — amount of passanger on the truck, the driver included
- $ l $ — total amount of people that should go into the tunnel before this truck, so that the driver can overcome his fear («if the monster appears in front of the motorcade, he'll eat them first»)
- $ r $ — total amount of people that should follow this truck, so that the driver can overcome his fear («if the monster appears behind the motorcade, he'll eat them first»).

Since the road is narrow, it's impossible to escape DravDe, if he appears from one side. Moreover, the motorcade can't be rearranged. The order of the trucks can't be changed, but it's possible to take any truck out of the motorcade, and leave it near the tunnel for an indefinite period. You, as the head of the motorcade, should remove some of the trucks so, that the rest of the motorcade can move into the tunnel and the total amount of the left trucks' values is maximal.

## 样例 #1

### 输入

```
5
1 1 0 3
1 1 1 2
1 1 2 1
1 1 3 0
2 1 3 0
```

### 输出

```
4
1 2 3 5 
```

## 样例 #2

### 输入

```
5
1 1 0 3
10 1 2 1
2 2 1 1
10 1 1 2
3 1 3 0
```

### 输出

```
3
1 3 5 
```

# 题解

## 作者：Aw顿顿 (赞：5)

## 题意

给定 $n$ 辆澈澈，每辆对应 $(v_i,l_i,r_i,c_i)$。

分别表示澈澈的价值，前面的人数，后面的人数，自己的人数。

要求给出一种方案，满足题意的同时使得这些澈澈的总价值最大。特别地，你应该要输出留下来的澈澈总数以及他们的编号。

## 解法

先考虑两个人之间的关系，再考虑整体的关系。

我们发现对于相邻的两个人 $(x,y)$ 一定满足以下两个式子：

$$\begin{cases}l_x+c_x=l_y&\text{I.}\\r_x-c_y=r_y&\text{II.}\end{cases}$$

如果 $\text{I.+II.}$ 可以得到 $l_x+c_x+r_x-c_y=l_y+r_y$，经过简单的移项得到了一个十分工整的式子：

$$l_x+c_x+r_x=l_y+c_y+r_y$$

实际上这个式子的意义就是总人数恒不变。因为前面的人 $+$ 后面的人 $+$ 自己 $=$ 总人数，因此对于同一种排列，这个式子是恒成立的。我们考虑按照总人数进行分类，然后去 DP。过程中总人数的分类由于静态数组开不下，考虑用 $\texttt{map}$ 实现。

## 代码

提供一个 $O(n)$ 的 DP，可以通过本题。

```cpp
#include<bits/stdc++.h>
#define N 1000005 
using namespace std;
map<int,int>m[N];
int n,dp[N],s[N],p[N],tot,it;
bool check(int r,int c,int l){
	if(r+c>N)return 1;
	return l&&m[l].find(r+c)==m[l].end(); 
}int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int v,c,l,r;
		cin>>v>>c>>l>>r;
		if(check(r,c,l))continue;
		int cur=m[l][r+c];
		dp[i]=dp[cur]+v;p[i]=cur;
		if(!r&&dp[i]>dp[it])it=i;
		if(dp[i]>dp[m[l+c][r]])m[l+c][r]=i;
	}while(it){
        s[tot++]=it;
        it=p[it];
    }cout<<tot<<endl;
    while(tot--)cout<<s[tot]<<' ';
    return 0;
}
```

---

## 作者：Time_tears (赞：3)

看完这道题目，我们肯定会想如何同时维护前缀人数和后缀人数，但是我们会发现这基本上是难以维护的，那么我们就要考虑一下题目的性质了。

首先因为题目是要前缀刚好为 $l_i$ 人，后缀刚好为 $r_i$ 人，但是我们可以发现，对于相邻的两个人 $i,j$ ，一定有 $l_i+c_i=l_j,r_i=r_j+c_j$ ,等式两边相加得到: $l_i+c_i+r_i=l_j+c_j+r_j$ ！！！我的天啊，这个柿子太美妙了，于是我们可以按 $l_i+c_i+r_i$ 分类，对于每个类，从前向后进行一次 $O(n)$ 的 dp，这样总复杂度就是 $O(n)$ 了。

```cpp
#include<cstdio>
#include<vector>
#define N 300005
using namespace std;
int n,l[N],r[N],f[N],las[N],ans;
int vis[N],mx[N],v[N],p[N],Time,Ans[N];
vector<int>a[N];
inline int read() {
	int s=0,f=0;
	char ch=getchar();
	while(ch<48||ch>57)f=(ch=='-'),ch=getchar();
	while(ch>47&&ch<58)s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
	return f?-s:s;
}
void Get(int x,int y) {
	if(vis[y]!=Time)vis[y]=Time,mx[y]=n+1;
	las[x]=mx[y],f[x]=f[mx[y]]+v[x];
}
void Insert(int x,int y) {
	if(vis[y]!=Time)vis[y]=Time,mx[y]=n+1;
	if(f[x]>f[mx[y]])mx[y]=x;
}
int main() {
	n=read(),f[n+1]=-0x3f3f3f3f;
	for(int i=1; i<=n; ++i)v[i]=read(),p[i]=read(),l[i]=read(),r[i]=read(),a[p[i]+l[i]+r[i]].push_back(i);
	for(int i=1; i<=300000; ++i)
		if(a[i].size()) {
			++Time,Insert(0,0);
			for(int j=0,siz=a[i].size(),x; j<siz; ++j) {
				x=a[i][j],Get(x,l[x]),Insert(x,p[x]+l[x]);
				if(!r[x]&&f[x]>f[ans])ans=x;
			}
		}
	while(ans)Ans[++Ans[0]]=ans,ans=las[ans];
	printf("%d\n",Ans[0]);
	for(int i=Ans[0]; i; --i)printf("%d ",Ans[i]);
	return 0;
}
```


---

## 作者：荣一鸣 (赞：3)

这道题看起来就像dp，所以就要dp

你说不知道怎么dp？那么我们就先把能配在一起的放在一个集合里。

我们可以看到，对于一辆车来说，他前面**一定**有l辆，后面**一定**有r辆，

加上他自己的人数c所以就得到了在这个序列中的人数总和n。

所以处理出来就可以dp了

```
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <map>
using namespace std;
void fff(){
    freopen("dravde.in","r",stdin);
    freopen("dravde.out","w",stdout);
}
const int MAXN=100001;
int n;
map<int,int> m[MAXN];
int f[MAXN],s[MAXN],p[MAXN],cnt=0,z;
int main(){
//	fff();
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        int v,c,l,r;
        scanf("%d%d%d%d",&v,&c,&l,&r);
        if(r+c<MAXN&&(!l||m[l].find(r+c)!=m[l].end())){
            int u=m[l][r+c];
            f[i]=f[u]+v,p[i]=u;
            if(!r&&f[i]>f[z]){
                z=i;
            }
            if(f[i]>f[m[l+c][r]]){
                m[l+c][r]=i;
            }
        }
    }
    while (z){
        s[cnt++]=z;
        z=p[z];
    }
    printf("%d\n",cnt);
    while (cnt--){
        printf("%d ",s[cnt]);
    }
    return 0;
}
```

---

## 作者：vеctorwyx (赞：2)

### ~~黑题都是水题~~，这话是钟神（zhx）说的

求最大价值，考虑$dp$：

设$dp_i$为车队以i车为结尾的最大价值，则有状态转移方程式（不完整）：

$\large dp_i= \max_{ 1\le j< i}dp_j+v_i$

很明显，题目中给的$l_i ,r_i,c_i$~~不是空气~~，还要有一定的限制条件，这是本题的关键。

设已选中的车的集合为$S$，则对于集合中的每一个车$i$，要满足两个条件（集合大小为$m$）：

$\large\begin{cases}
l_i=\sum_{1\le j< i}c_{S_j}\\
r_i=\sum_{i<j\le n}c_{S_j}
\end{cases}$

由于$i$满足条件的同时${i-1}$也满足条件，则以上公式可化为

$\large \begin{cases}
l_i=l_{i-1}+c_{i-1}\\
r_{i-1}=r_i+c_{i}
\end{cases}$

那么完整的状态转移方程就推出来了。

#### 接下来是代码实现和优化：

如果根据上述条件直接暴力枚举进行转移会超时（$O(n^2)$）。

从条件入手：当我们求出$l_i$和$r_i+c_i$后，就可以维护一个二维数组，并以$l_i+c_i$和$r_i$为标进行转移，具体操作可以看代码。

如果直接开数组会爆空间，开个map就好了。

最后就是注意选中的第一辆车和最后一辆车特殊判定。

放心，这题不开$longlong$~~见不了祖宗~~

code：

```
#include<bits/stdc++.h>
using namespace std;
int read()
{
    int x=0,y=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')y=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
    return x*y;
}
int n,v[100010],c[100010],l[100010],r[100010],ji[100010],cnt;
struct node
{
	int dat,pre;//pre记录上一辆车以便于输出
}dp[100010],ans;
map<int,node>q[200010];
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		v[i]=read(),c[i]=read(),l[i]=read(),r[i]=read();
		if(q[l[i]][r[i]+c[i]].dat+v[i]>dp[i].dat&&(q[l[i]][r[i]+c[i]].dat||l[i]==0))//特殊处理第一辆车&从前转移
		{
			dp[i].dat=q[l[i]][r[i]+c[i]].dat+v[i];
			dp[i].pre=q[l[i]][r[i]+c[i]].pre;
		}
		if(dp[i].dat>q[l[i]+c[i]][r[i]].dat)//向后转移
		{
			q[l[i]+c[i]][r[i]].dat=dp[i].dat;
			q[l[i]+c[i]][r[i]].pre=i;
		}
		if(dp[i].dat>ans.dat&&r[i]==0)//只有满足条件的车才能做结尾。
		{
			ans.pre=i;
			ans.dat=dp[i].dat;
		}
	}
	while(ans.pre)//倒序转正序
	{
		ji[++cnt]=ans.pre;
		ans=dp[ans.pre];
	}
	cout<<cnt<<' '<<endl;//注意输出的是什么
	for(int i=cnt;i>=1;i--)
	cout<<ji[i]<<" ";
}
```
后记：

1. 翻译是不是有点锅，没有说清楚输出是啥，~~差点弄错~~

1. 思路借鉴了zhx神仙的讲课内容

1. 第一道黑题

---

## 作者：XL4453 (赞：1)

### 解题思路：

题面可能有一些小问题，题目中并非要求使得某一辆车之前或之后至少有若干个人，而应该是有恰好若干人。（这个问题在 CF 那场比赛的评论区也有反馈）

如果是恰好，那么问题就简单多了，由于对于相邻的两人 $l_{i-1}+c_{i-1}=l_i$ 且 $r_{i-1}=r_i+c_i$，将两个式子相加，得到 $l_i+r_i+c_i=l_{i-1}+r_{i-1}+c_{i-1}$ 也就是对于某一个方案，其中 $l_i+r_i+c_i$ 一定都是相等的。

所以考虑将所有的卡车按照 $l_i+r_i+c_i$ 分组，对于每一组内单独转移。

设 $f_i$ 表示当前车队后面还需要 $i$ 个人时能取得的最大价值，对于每一个卡车 $j$ 都能将 $f_i$ 从 $f_i+c_j$ 处以 $v_j$ 的价值转移过来。

特殊地，有：当 $l_i$ 等于 0 时，这一辆卡车可以放在第一个，也就是可以将 $f_{r_i}=v_i$。

这样每一次的转移复杂度是 $O(1)$ 的，每一辆卡车能且仅能转移一次，所以从复杂度是 $O(n)$ 的，可以通过此题。

---

此外，本题还要求记录方案，所以要额外开一个数组记录下某一个的转移方向。

---
### 代码：

```cpp
#include<cstdio>
#include<vector>
using namespace std;
vector <int> a[600005];
int n,v[600005],l[600005],r[600005],c[600005],f[600005],from[600005],col[600005],id[600005];
int ans,way[600005],tot;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d%d",&v[i],&c[i],&l[i],&r[i]);
		a[c[i]+l[i]+r[i]].push_back(i);
	}
	for(int k=0;k<=300000;k++){
		for(int j=0;j<a[k].size();j++){
			int now=a[k][j];
			if(col[r[now]]!=k)f[r[now]]=-1;
			if(col[r[now]+c[now]]!=k)f[r[now]+c[now]]=-1;
			col[r[now]]=k;
			if(l[now]==0){
				if(f[r[now]]<v[now]){
					f[r[now]]=v[now];
					from[now]=0;
					id[r[now]]=now;
				}
			}
			else{
				if(f[r[now]+c[now]]==-1)continue;
				if(f[r[now]]<f[r[now]+c[now]]+v[now]){
					f[r[now]]=f[r[now]+c[now]]+v[now];
					from[now]=id[r[now]+c[now]];
					id[r[now]]=now;
				}
			}
		}
		if(col[0]==k&&f[0]>ans){
			ans=f[0];
			tot=0;
			for(int j=id[0];j;j=from[j]){
				way[++tot]=j;
			}
		}
	}
	printf("%d\n",tot);
	for(int i=tot;i>=1;i--)
	printf("%d ",way[i]);
	printf("\n");
	return 0;
}
```



---

## 作者：H_D_NULL (赞：0)

### ~~果然黑题和‘岚’题不是一个概念啊~~

------------

### 大致分析

题目要求司机必须按顺序进入（或不进入），所以不难想到用类似01背包的DP；而且给出在他前面必须进入的人数 $l$ 和在后面进入的人数 $r$，即可大概推出状态转移的方式：选用某个司机的最大价值等于**其之前人数为 $l$ ，之后需要人数为 $r+c$ 的所有方案的最大价值**加上**其之后人数为 $r$，之前需要人数为 $l+c$ 的最大价值**；

但是乍一看这显然有后效性，所以我们直接去掉查找其之后的方案及价值，这样就成了线性维护**选用这个司机时总人数为 $l+c$ 且其后需要 $r$ 人的最大价值**，如果 $r$ 为零，则这个司机是一个合法方案的结尾，更新答案。

------------

### 针对题目的解决方法

按照上面的做法，线性枚举到某一司机时（**不管**最终是否能成为一个合法方案的一部分），相当于只更新**总人数为 $l+c$，其后需要 $r$ 人**这一个状态，且更新过程只需要在已有合法状态中找**总人数为 $l$ ，其后需要 $r+c$ 人**的状态，所以如果有一个集合，存入了所有**总人数为 $l$ 的状态**，那么枚举复杂度就会大大降低。综上，我们就用一个 vector 如上来存状态及状态的最大价值，理论时间复杂度远小于 $O(n^2)$。

至于题目要求的一个方案，在更新答案的时候开一个辅助数组一起更新就完事了。

------------

*Talk is cheap, show me the code*

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;

inline int read(){
	re int ret=0;
	re char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9'){
		ret=(ret<<1)+(ret<<3)+(c^48);
		c=getchar();
	}
	return ret;
}

int n;
int las[100005];
int ans,lans,sas[100005];

struct Inf{
	int v,c;
	int l,r;
} t[100005];

struct Dr{
	int size;
	vector <int> seq;
	vector <int> v;
} f[100005];

int main(){
	n=read();
	for(re int i=1,v,c,l,r,maxv;i<=n;i++){
		v=t[i].v=read();
		c=t[i].c=read();
		l=t[i].l=read();
		r=t[i].r=read();
		if(!l){
			f[c].size++;
			f[c].seq.push_back(i);
			f[c].v.push_back(v);
			if(!r){
				if(v>ans){
					ans=v;
					lans=i;
				}
			}
		}
		else{
			maxv=0;
			for(re int j=0;j<f[l].size;j++){ 
				if(t[f[l].seq[j]].r==c+r){
					if(f[l].v[j]>maxv){
						las[i]=f[l].seq[j];
						maxv=f[l].v[j];
					}
				}
			}
			if(!maxv) continue;
			c+=l; maxv+=v;
			f[c].size++;
			f[c].seq.push_back(i);
			f[c].v.push_back(maxv);
			if(!r){
				if(maxv>ans){
					ans=maxv;
					lans=i;
				}
			}
		}
	}
	while(lans){
		sas[++sas[0]]=lans;
		lans=las[lans];
	}
	printf("%d\n",sas[0]);
	while(sas[0]--){
		printf("%d ",sas[sas[0]+1]);
	}
	return 0;
}
```


---

## 作者：xlqs23 (赞：0)

**题意：**

给你$N$个物品，每个物品有其价格$P_i$，之前必须要买的物品价格和$L_i$，之后必须要买的物品价格和$R_i$和价值$W_i$。试给出一种物品的选择方案，使得满足所有选择的物品的条件且选择物品的价值和最大（物品的选择顺序必须要与原来的顺序相同）。$N \leq 10^5 , P , L , R \leq 10^5 , W \leq 10^4$

像背包DP，所以就是背包DP（雾）

我们能够发现从物品$i$转移到物品$j$的充要条件是：$R_i=R_j+P_j$且$L_i+P_i=L_j$。将二式相加得$P_i+L_i+R_i=P_j+L_j+R_j$，也就是说$P+L+R$相等的物品才能够互相转移。所以我们可以考虑使用$vector$存每个$P+L+R$对应的物品，对于每个组跑一次DP。因为每一个物品的转移只能从$L$到$L+P$，所以转移是$O(1)$的，所以DP总复杂度为$O(n)$。注意DP数组的清空推荐使用还原而不是memset，这样还原的复杂度才是$O(n)$。

获得了最大的价值之后，对对应的那一个组别再跑一遍DP，跑出方案。方案的记录可以通过记录某一个物品选择前最后选择的物品来实现。总复杂度为$O(n)$。

注意每一个组别一定要有始有终（也就是选择的物品必须要有$L=0$与$R=0$的物品，也可以通过这一个来剪一些枝降低常数）

关于输出方案其实可以使用递归，但是因为本机会爆栈所以用循环+vector输出

**CODE:**
```cpp
#include<bits/stdc++.h>
#define MAXN 3000010
#define MAXM 200010
using namespace std;

inline int read(){
    int a = 0;
     char c = getchar();
    while(!isdigit(c))
         c = getchar();
     while(isdigit(c)){
        a = (a << 3) + (a << 1) + (c ^ '0');
         c = getchar();
    }
     return a;
}
 
struct thing{
     int w , p , l , r , ind;
 }now;
vector < thing > v[MAXN];
vector < int > anss;
int maxPri[MAXN] , last[MAXM] , k[MAXN] , cnt[MAXN] , ans[MAXN] , maxN = -1 , maxDir;
bool haveEnd[MAXN];
void out(int dir){
     while(dir != -1){
         anss.push_back(v[maxDir][dir].ind);
         dir = last[dir];
     }
     for(int i = anss.size() - 1 ; i >= 0 ; i--)
         printf("%d " , anss[i]);
}

int main(){
     int N = read();
     for(int i = 1 ; i <= N ; i++){
         now.w = read();
         now.p = read();
         now.l = read();
         now.r = read();
        now.ind = i;
       if(cnt[now.p + now.l + now.r] || now.l == 0){
             cnt[now.p + now.l + now.r]++;
             v[now.p + now.l + now.r].push_back(now);
             if(now.r == 0)
                 haveEnd[now.p + now.l + now.r] = 1;
         }
     }
     memset(maxPri , -0x3f , sizeof(maxPri));
     maxPri[0] = 0;
     for(int i = 0 ; i <= 3000000 ; i++)
         if(cnt[i] && haveEnd[i]){
             for(int j = 0 ; j < cnt[i] ; j++)
                 maxPri[v[i][j].l + v[i][j].p] = max(maxPri[v[i][j].l + v[i][j].p] , maxPri[v[i][j].l] + v[i][j].w);
             if(maxN < maxPri[i]){
                 maxN = maxPri[i];
                 maxDir = i;
             }
             for(int j = 0 ; j < cnt[i] ; j++)
                 maxPri[v[i][j].l + v[i][j].p] = -0x3f3f3f3f;
         }
     memset(last , -1 , sizeof(last));
     memset(k , -1 , sizeof(k));
     for(int j = 0 ; j < cnt[maxDir] ; j++)
         if(maxPri[v[maxDir][j].l + v[maxDir][j].p] < maxPri[v[maxDir][j].l] + v[maxDir][j].w){
             maxPri[v[maxDir][j].l + v[maxDir][j].p] = maxPri[v[maxDir][j].l] + v[maxDir][j].w;
             last[j] = k[v[maxDir][j].l];
             k[v[maxDir][j].l + v[maxDir][j].p] = j;
             ans[v[maxDir][j].l + v[maxDir][j].p] = ans[v[maxDir][j].l] + 1;
         }
    printf("%d\n" , ans[maxDir]);
    out(k[maxDir]);
    return 0;
}

---

