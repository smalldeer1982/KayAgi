# 「SWTR-7」Scores（hard version）

## 题目背景

#### 本题是 Scores 的 hard 版本。注意题目限制与 [easy](https://www.luogu.com.cn/problem/P7873) 版本不同。

#### 请注意特殊的时空限制。

## 题目描述

小 A 的班上有 $n$ 个学生。最近他们进行了一场考试，共有 $m$ 个学科。第 $i$ 个学生第 $j$ 门学科的得分为**整数** $s_{i,j}\ (0\leq s_{i,j}\leq 100)$。

同学们很重视自己在班上的排名，所以他们经常会比较自己和别的同学的分数。如果一个学生 $i$ **至少有一门学科**的分数比 $j$ **高**，ta 就会觉得自己不比 $j$ 差；相反，如果 ta **每门学科**的分数都比 $j$ **低**，ta 就会觉得自己被 $j$ 吊打了。

实际上，**上述两种情况并不是严格意义上相反的**。但是喜好八卦的小 A 打听到了每两个同学之间的分数情况，他惊讶地发现：**一个同学 $i$ 要么被 $j$ 吊打，要么不比 $j$ 差。** 同时，**如果 $i,j$ 被同一个人吊打，或同时吊打同一个人，则他们之间也有一方被另一方吊打**。我们用一个矩阵 $a_{i,j}\ (i\neq j)$ 来描述小 A 知道的同学们之间的分数关系：$a_{i,j}=0$ 表示 $i$ 被 $j$ 吊打；$a_{i,j}=1$ 表示 $i$ 不比 $j$ 差。

小 A 想知道这种情况会不会发生，即是否存在这样一张 $n\times m$ 的成绩表 $s$ 满足矩阵 $a$ 所描述的分数关系，从而确定有没有撒谎的同学。如果存在 $s$，请先输出 $\texttt{YES}$，再**任意**输出一种符合要求的成绩表；否则输出 $\texttt{NO}$。

注意：这里所求的 $s$ 所需满足的条件是 $a$ 的限制，而**不只是**小 A 所发现的性质，因为**他发现的性质已经在给出的 $a$ 中体现**。

## 说明/提示

**「Special Judge」**

**本题使用 Special Judge。请认真阅读输出格式，输出格式有误可能导致 UKE 或 WA。**

SPJ 首先会判断你的第一行输出是否与答案相同。  
如果相同且答案为 $\texttt{YES}$，则 SPJ 会判断你的输出是否符合所有限制。  
如果有解且你输出 $\texttt{YES}$，但给出方案错误，你将获得该测试点 $50\%$ 的分数。

你需要满足的限制如下：  
- $0\leq s_{i,j}\leq 100$。
- 对于任意 $i,j\ (i\neq j)$，若 $a_{i,j}=0$，则对于任意 $k\ (1\leq k\leq m)$，有 $s_{i,k}<s_{j,k}$；若 $a_{i,j}=1$，则存在一个 $k\in [1,m]$，使得 $s_{i,k}>s_{j,k}$。

你需要注意的是，所有输出都应严格符合输出格式。如果你对答案的存在性判断正确，但是输出方案时 $s_{i,j}<0$ 或 $s_{i,j}>100$，SPJ 会判定为 WA，得 $0$ 分，而不是 $50\%\ \times$ 该测试点分数。

**「数据范围与约定」**

本题共有 6 个测试点。

- Testcase #0（1 point）：是样例。
- Testcase #1（10 points）：$n=1$。
- Testcase #2（10 points）：$m=1$。
- Testcase #3（30 points）：$m=2$。
- Testcase #4（20 points）：$a_{i,j}=1\ (i\neq j)$。
- Testcase #5（29 points）：无特殊限制。

对于 $100\%$ 的数据，$1\leq n,m\leq 100$，$a_{i,j}\in\{0,1\}$，$T=50$（除 Testcase #0）。  
对于 $a$ 的限制：若 $a_{i,j}=a_{i,k}=0$，则 $a_{j,k}$ 和 $a_{k,j}$ 中至少有一个为 $0$；若 $a_{i,k}=a_{j,k}=0$，则 $a_{i,j}$ 和 $a_{j,i}$ 中至少有一个为 $0$。  
对于所有测试点，**时间限制 500ms，空间限制 16MB。**

**「题目来源」**

[Sweet Round 07](https://www.luogu.com.cn/contest/51773) A2。  
idea & solution & data：[Alex_Wei](https://www.luogu.com.cn/user/123294)；验题：[chenxia25](https://www.luogu.com.cn/user/138400)。

## 样例 #1

### 输入

```
0
5
5 3
0 1 1 1 1
1 0 1 1 1
1 1 0 1 1
1 1 1 0 1
1 1 1 1 0
2 7
0 1
0 0
5 4
0 1 1 0 1
0 0 0 0 1
0 1 0 0 1
1 1 1 0 1
1 1 1 1 0
3 1
0 1 1
1 0 1
1 1 0
3 2
0 1 0
0 0 1
1 0 0```

### 输出

```
YES
100 99 97
98 100 99
95 97 100
0 98 100
99 99 99
YES
98 100 94 98 72 53 53
97 99 93 97 71 52 52
YES
90 80 70 60
50 40 30 20
60 50 40 30
100 90 80 70
40 60 80 100
NO
NO```

# 题解

## 作者：by_chance (赞：7)

[P7876 「SWTR-07」Scores（hard version）](https://www.luogu.com.cn/problem/P7876)

考察思维的构造题。

## Testcase #1：$n=1$。


------------

这时只有一个人，随便输出即可，比如全部满分。

```cpp
if(t==1){
	printf("YES\n");
	for(int i=1;i<=m;i++)printf("100 ");
	printf("\n");
}
```


## Testcase #4：$a[i][j]=1(i≠j)$。


------------

这时题目和A1一样，还要进一步分类讨论。

$n=1$ 时，必然有解；$m=1$ 且 $n≠1$ 时，必然无解；

$m≥2$ 时，可以让所有人第一门学科的分数单调递减，第二门学科的分数单调递增，剩余的分数随意，比如全部满分。

```cpp
if(t==4){
	if(n==1){
		printf("YES\n");
		for(int i=1;i<=m;i++)printf("100 ");
		printf("\n");
	}
   else if(m==1&&n!=1)printf("NO\n");
	else{
		printf("YES\n");
		for(int i=1;i<=n;i++){
			printf("%d %d ",i,100-i);
			for(int j=3;j<=m;j++)printf("100 ");
			printf("\n"); 
		}
	}
}
```


## Testcase #2 ：$m=1$。


------------

这时，$a[i][j]=1$ 表示 $i$ 的分数比 $j$ 高，$a[i][j]=0$ 表示 $i$ 的分数比 $j$ 低。由此可知 $a[i][j]=a[j][i]$ 时无解。

于是只需考虑每个人的排名，那么怎么得到这个排名呢？

由于每个人分数互不相同，只需统计每个人比多少个人分数高即可。如果有两人比同样多的人分数高则无解。

```cpp
bool f=1;
for(int i=1;i<=n;i++)
	for(int j=1;j<i;j++)
		if(a[i][j]==a[j][i])f=0;
for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		if(i!=j&&!a[i][j])add[j]++;
for(int i=1;i<=n;i++){
	if(vis[add[i]])f=0;
	vis[add[i]]=1;
}
if(!f)printf("NO\n");
else{
	printf("YES\n");
	for(int i=1;i<=n;i++)printf("%d\n",add[i]);
}
```

## Testcase #3 ：$m=2$。


------------

到目前为止，我们还没有用到题目中的一个条件：

**如果 $i$,$j$ 被同一个人吊打，或同时吊打同一个人，则他们之间也有一方被另一方吊打。**

这么一来，我们假设某人 $X$ 被 $A$、$B$、$C$…吊打，吊打 $a$、$b$、$c$…，那么 $a$、$b$、$c$、…、$A$、$B$、$C$、…、$X$ 之间的所有吊打关系就明了了。由于吊打关系是具有传递性的，于是这些人之间就形成了明确的排名。为了叙述方便，称这样的一群人为一块。

利用并查集，我们可以处理出所有的块；再利用 Testcase #2 时所用到的方法，确定每个人在该块中的排名。

还是由于这个条件，各块之间一定是互相不比对方差。此时就可以套用 Testcase #4 的情况进行构造。在处理块的同时记录每一块内的第一名，然后各个块的第一名的第一个分数递减，第二个分数递增；每两个块之间要留出足够的分数区间给块内其他人，这就需要记录一下每一块的大小。每块内其他的人用该块第一名减去排名得到分数。

此时的无解情况有两种：各个块内排名有重复，或者存在 $a[i][j]=0$，$a[j][k]=0$，但 $a[i][j]=1$。

## Testcase #5 ：无特殊限制。


------------

在 Testcase #3 的基础上，把每组最高分的另外 $m-2$ 个分数初始化为 $100$ 即可。

具体细节参见代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
int t,T,n,m,tot,f=1;
int a[110][110],vis[110],rk[110],fa[110],cnt[110],root[110],ans[110][110]; 
vector<int> g[110];//记录各个块内的人员 
int get(int x){return (x==fa[x]?x:(fa[x]=get(fa[x])));}
void Union(int x,int y){fa[get(x)]=get(y);}
int main(){
	t=read();T=read();
	while(T--){
		memset(rk,0,sizeof(rk));//每个人在自己的块内的排名 
		memset(vis,0,sizeof(vis));  //计算排名时，记录该排名是否有人 
		memset(cnt,0,sizeof(cnt));  //每个块内的人数 
		tot=0;						//块的个数 
		f=1;						//是否有解 
		n=read();m=read();
		for(int i=1;i<=n;i++)while(g[i].size())g[i].pop_back();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				a[i][j]=read();
		for(int k=1;k<=n;k++)
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++){
					if(i==j||j==k||k==i)continue;
					if(a[i][k]==0&&a[k][j]==0&&a[i][j]!=0)f=0;
				} 
		for(int i=1;i<=n;i++)fa[i]=i;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(i!=j&&!a[i][j])Union(i,j);//处理块 
		for(int i=1;i<=n;i++)g[get(i)].push_back(i);
		for(int x=1;x<=n;x++)
			if(g[x].size()){
				memset(vis,0,sizeof(vis));
				++tot;
				cnt[x]=g[x].size();
				for(int i=0;i<g[x].size();i++)
					for(int j=0;j<g[x].size();j++){
						int t1=g[x][i],t2=g[x][j];
						if(t1!=t2&&a[t1][t2]==0)rk[t1]++; 
					} 
				for(int i=0;i<g[x].size();i++){
					if(vis[rk[g[x][i]]])f=0;
					vis[rk[g[x][i]]]=1;
					if(rk[g[x][i]]==0)root[x]=g[x][i];
				}//判定无解 
			}
		if(f==0||(m==1&&tot!=1)){printf("NO\n");continue;}
		int sum=0;
		for(int i=1;i<=n;i++)if(cnt[i]){
			ans[root[i]][1]=sum+cnt[i];
			ans[root[i]][2]=100-sum;
			for(int j=3;j<=m;j++)ans[root[i]][j]=100;
			for(int j=0;j<g[i].size();j++){
				int tmp=g[i][j];
				for(int k=1;k<=m;k++)
					ans[tmp][k]=ans[root[i]][k]-rk[tmp];
			}
			sum=sum+cnt[i];//记录已处理的人数，确定下一块最高分前两门学科的分数 
		}
		printf("YES\n");
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)
				printf("%d ",ans[i][j]);
			printf("\n");
		}
	}
	return 0;
}
```

---

## 作者：intel_core (赞：6)

显然，我就是那个被吊打的人......

---------
首先，我们先考虑怎么把不行的情况排除：    
* 如果吊打的关系形成了环，很显然这是非法的     
* 如果 $\text{A}$ 吊打了 $\text{B}$ ，$\text{B}$ 吊打了 $\text{C}$ ，$\text{A}$ 却没有吊打 $\text{C}$ ，这同样也是不合法的     

这看上去非常的对，但是我们需要考虑 $m=1$ 时的情况：    
1.  一种合法的情况一定满足所有人的分数互不相同     
2.  将分数从高到低排好后，分数高的人吊打分数低的人      

那么我们应该怎样处理这两个限制条件呢？     
首先，注意到分数互不相同，所以拓扑排序后没有两点的拓扑序相同     
当没有两点拓扑序相同时，我们就可以依赖于拓扑序来构造满足条件的分数了    

处理完 $m=1$ 的特殊情况后，我们来看看对正解有怎样的启发：    
我们也可以先跑出每个点的拓扑序，然后排掉一部分   
类似的，我们也可以检查一个点的上游节点是否都吊打了这个点     
如果 $m >1$ ，那么我们可以入手让没有吊打关系的两个点的分数互不吊打   
将具有吊打关系之间的学生称为小组，那么每个人在小组内有一个排名    
我们可以假定 1 组的人科目一的分数从 $100$ 递减，科目二从 $0$ 递增   
2 组的所有人的科目一分数都比 1 组的人低，科目 2 分数都比 1 组人高  
这样我们就把前两个科目的分数分配到了每一个组里     
在同一组内，两个科目的分数都从高到低分配即可   
其余科目分数和拓扑序相同即可    

上代码：
```cpp

#include<bits/stdc++.h>
using namespace std;
const int NR=110;
int n,m,a[NR][NR];
bool flag[NR][NR],vis[NR];
int from[NR],size[NR],s[NR],cnt[NR],level[NR];

int main(){
	int t,T;cin>>t>>T;
	while(T--){
		memset(flag,false,sizeof(flag));
		memset(from,0,sizeof(from));
		memset(size,0,sizeof(size));
		memset(cnt,0,sizeof(cnt));
		memset(vis,false,sizeof(vis));
		memset(s,0,sizeof(s));
		memset(level,0,sizeof(level));
		memset(a,0,sizeof(a));
		cin>>n>>m;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)scanf("%d",&a[i][j]);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(i!=j&&a[i][j]==0)
					flag[j][i]=1,cnt[j]++;
		int lcy=n,wxb=0;bool can=true;
		queue<int>q;
		while(lcy){
			int tmp=0;wxb++;
			for(int i=1;i<=n;i++)
				if(!cnt[i]&&!vis[i])q.push(i);
			while(!q.empty()){
				int x=q.front();q.pop();
				tmp++;lcy--;level[x]=wxb;vis[x]=true;
				for(int j=1;j<=n;j++)
					if(flag[j][x])flag[j][x]=false,cnt[j]--;
			}
			if(!tmp){
				can=false;
				break;
			}
		}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(i!=j&&a[i][j]==0)
					flag[i][j]=flag[j][i]=1;
		int sum=0;
		for(int i=1;i<=n;i++)
			if(!from[i]){
				from[i]=++sum;size[sum]=1;q.push(i);
				while(!q.empty()){
					int x=q.front();q.pop();
					for(int j=1;j<=n;j++)
						if(flag[x][j]&&!from[j]){
							from[j]=sum;
							q.push(j);size[sum]++;
						}
				}
			}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(i!=j&&from[i]==from[j]&&level[i]==level[j])can=false;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(from[i]==from[j]&&level[i]>level[j]&&a[j][i])can=false;
		if(!can){
			puts("NO");
			continue;
		}
		if(m==1){
			if(sum==1){
				puts("YES");
				for(int i=1;i<=n;i++)cout<<level[i]<<endl;
			}
			else puts("NO");
		}
		else{
			puts("YES");
			for(int i=1;i<=sum;i++)s[i]=s[i-1]+size[i];
			for(int i=1;i<=n;i++){
				for(int j=1;j<=m;j++){
					if(j==1)cout<<s[from[i]-1]+level[i]<<" ";
					else if(j==2)cout<<100-s[from[i]]+level[i]<<" ";
					else cout<<level[i]<<" ";
				}
				puts("");
			}
		}
	}
	return 0;
} 
```

---

## 作者：enucai (赞：4)

### 前言：立志写一篇清晰易懂的题解，虽然我一定是那个被吊打的人。
----
题意就不说了。

先来判断无解的情况，有两种可能：

- A吊打了B，B吊打了C，C又吊打了A

- A吊打了B，B吊打了C，C没有被A吊打

判完无解情况后，我们可以将吊打关系转化为一张图。

假如 $a$ 吊打 $b$ ，那么我们就在 $a$ 与 $b$ 两个结点之间连一条有向边。

可以证明，最后建出来的图经过化简后，一定是由几条链组成的。

为什么？首先容易证明构成的图一定是一张DAG。然后要证明是几条链组成的，只要证明以下两种情况不可能：

1.有一个点同时连出多条边（此处以2为例，其余同理）

![](https://cdn.luogu.com.cn/upload/image_hosting/zt545wmy.png)

根据题目：**如果 $i,j$ 被同一个人吊打，或同时吊打同一个人，则他们之间也有一方被另一方吊打**可知，图中 $p,q$ 两点之间一定有一条有向边。如：

![](https://cdn.luogu.com.cn/upload/image_hosting/vqb6jdlp.png)

那么图中 $k,p$ 之间的连边可以删除，因此也可以看作一条链。

2.有多个条边同时连向一个点（此处以2为例，其余同理）

![](https://cdn.luogu.com.cn/upload/image_hosting/fuyo0y14.png)

根据题目：**如果 $i,j$ 被同一个人吊打，或同时吊打同一个人，则他们之间也有一方被另一方吊打**可知，图中 $p,q$ 两点之间一定有一条有向边。如：

![](https://cdn.luogu.com.cn/upload/image_hosting/wz6j8xvf.png)

那么图中 $q,i$ 之间的连边可以删除，因此也可以看作一条链。

知道了这点以后，就可以处理出每一条链中的元素与每一条链中元素的相对位置关系。

接下来，假设有 $3$ 条链，第一条链 $4$ 个元素，第二条链 $5$ 个元素，第三条链 $3$ 个元素，那么就可以通过两门学科构造出一种合法的情况如下：

每个元素一个二元组，每个二元组的第一个数表示第一门学科分数，第二个数表示第二门学科分数。

| person1 | person2 | person3 | person4 | person5 |
| ----------- | ----------- | ----------- | ----------- | ----------- |
| (100,1) | (99,2) | (98,3) | (97,4) |  |
| (96,5) | (95,6) | (94,7) | (93,8) | (92,9) |
| (91,10) | (90,11) | (89,12) |  |  |

这样就能满足题目要求了qwq。然后剩下的学科按照第一门学科的分数填充一下就好了。

**但是请注意**： $m=1$ 时需要特判，即图中必须只能有一条合法的链，否则答案为`NO`。

最后代码实现就很简单了（代码和思路有些不一样，主要是因为再写题解释发现了一些其他的讲解方法，代码用作参考为主qwq）：

```cpp
#define justFUCK {puts("NO");return;}
int n,m,a[110][110];
int fa[110],king[110];
int find(int x) {return fa[x]==x?x:fa[x]=find(fa[x]);}
void merge(int x,int y) {if(find(x)!=find(y)) fa[find(x)]=find(y);}
vector<int> son[110];
int cnt[110],ans[110][110];
bool has[110];
void work(){
    n=read(),m=read();
    For(i,1,n) For(j,1,n) a[i][j]=read();
    For(i,1,n) For(j,1,n) For(k,1,n) if(i!=j&&j!=k&&k!=i&&a[i][j]==0&&a[j][k]==0&&a[i][k]==1) justFUCK;
    For(i,1,n) fa[i]=i,cnt[i]=0,king[i]=0;
    For(i,1,n) For(j,1,n) if(i!=j&&a[i][j]==0) merge(i,j);
    For(i,1,n) son[i].clear();
    For(i,1,n) son[find(i)].pb(i);
    For(i,1,n) if(son[i].size()!=0){//在这个组中只存在吊打关系(构成一条链)
        memset(has,false,sizeof(has));
        for(auto u:son[i]) for(auto v:son[i]) if(u!=v&&a[u][v]==0) cnt[u]++;
        for(auto u:son[i]){
            if(has[cnt[u]]) justFUCK;
            has[cnt[u]]=true;
            if(cnt[u]==0) king[i]=u;//这个人吊打了所有人，是这个组中最奆的人
        }
    }
    /**m=1特判**/
    if(m==1){
        bool check=false;
        For(i,1,n) if(king[i]!=0){
            if(!check) check=true;
            else justFUCK;
        }
    }
    /**m=1特判**/
    For(i,1,n) For(j,1,m) ans[i][j]=0;
    int tot=0;
    For(i,1,n) if(son[i].size()!=0){
        int sb=king[i];
        ans[sb][1]=100-tot;
        ans[sb][2]=tot+son[i].size();
        For(i,3,m) ans[sb][i]=100;
        for(auto j:son[i]) if(j!=sb){
            For(k,1,m) ans[j][k]=ans[sb][k]-cnt[j];
        }
        tot+=son[i].size();
    }
    puts("YES");
    For(i,1,n) {For(j,1,m) printf("%d ",ans[i][j]); puts("");}
}
```

**求管理员通过qwq**

---

