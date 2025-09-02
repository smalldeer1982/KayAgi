# [CEOI 2002] Bugs Integrated,Inc.

## 题目描述

Bugs Integrated,Inc. 是高级存储芯片的主要制造商。他们正在开始生产新的 $6$ TB Q-RAM 芯片。每个芯片由以 $2×3$ 的矩形排列的六个方形硅片块组成。Q-RAM 芯片的制造方式是将一块长方形的大硅片分成 $N×M$ 个方形硅片块。然后仔细测试所有方形硅片块，坏的用黑色标记。  
![TuLi](https://cdn.luogu.com.cn/upload/image_hosting/qqjfauh0.png)  
最后，将硅片切割成存储芯片。每个芯片由 $2×3$（或
 $3×2$）单位方形硅片块组成。当然，任何芯片都不能包含任何坏的（标记的）方形硅片块。它可能不能将硅片切割成每一个好的方形硅片块都成为某些存储芯片的一部分。该公司希望尽可能少地浪费好方形硅片块。因此他们想知道如何切割硅片以尽可能多地切出芯片。  
现您将获得几个硅片的尺寸和其每个硅片所有坏方形硅片块的列表。你的任务是编写一个程序，计算每个硅片最多可以从其切下的芯片数量。

## 说明/提示

#### 数据规模与约定  
对于 $100 \%$ 的数据，$1 \leq D \leq 5$，$1 \leq N \leq 150$，$1 \leq M \leq 10$，$0 \leq K \leq M×N$，$1 \leq x \leq N$，$1 \leq y \leq M$。  
#### 样例说明  
![TuLi](https://cdn.luogu.com.cn/upload/image_hosting/v4ugwh72.png)  
#### 题目说明  
来源于 CENTRAL-EUROPEAN OLYMPIAD IN INFORMATICS 2002 的 [Bugs Integrated,Inc.](https://web.ics.upjs.sk/ceoi/documents/tasks/bugs-tsk.pdf)。  
由 @[求学的企鹅](/user/271784) 翻译整理。

## 样例 #1

### 输入

```
2
6 6 5
1 4
4 6
2 2
3 6
6 4
6 5 4
3 3
6 1
6 2
6 4```

### 输出

```
3
4```

# 题解

## 作者：lg_zhou (赞：11)

> 其实，动规都是想明白后超简单 QaQ

相比楼上的题解没用啥优化，可能实现方法不大一样。

由典型的一道题：[炮兵阵地](https://www.luogu.com.cn/problem/P2704) 入手。这道题很显然可以设 $f[i][j][k]$ 代表到 $i$ 行为止，$i$ 行状态是 $j$，$i-1$ 行状态是 $k$，炮兵互不冲突大最大答案。这样的复杂度是枚举阶段的 $n$ 乘状态 $2^m*2^m$ 乘决策，即枚举上面前两行的状态，复杂度为 $O((2^m)^3)$。只是因为有每一行的合法状态很少（相邻两个一中间至少有两个零，大概 $100$ 个），这样才把复杂度减少，从而通过这一题。

然而这一类问题有更普遍的一种解法，就是用更高的进制位（三进制）进行压缩，并存储更多的信息。我们规定放炮兵的位置为 $2$，$2$ 的下面必须放 $1$，$1$ 的下面必须放 $0$。$0$ 的下面才可以任意放。这样我们内存可以省去一维，只用存当前第 $i$ 行的状态

采用正向递推。考虑第 $i+1$ 行填什么状态。需要满足：

1. 第 $i$ 行第 $j$ 位为 $2$ 时，第 $i+1$ 行第 $j$ 位填 $1$
2. 第 $i$ 行第 $j$ 位为 $1$ 时，第 $i+1$ 行第 $j$ 位填 $0$
3. 山地不能填 $2$
4. 一个格子填 $2$ 后，右边两个格子不能填 $2$

因为转移比较复杂，不用写出转移方程，相邻两行进行 $dfs$ 即可。

回到这题，我们将 $2*3$ 和 $3*2$ 的矩阵分别化为

$$2\quad 2$$

$$1\quad 1$$

$$0\quad 0$$

和

$$1\qquad 1 \qquad 1$$

$$0\qquad 0 \qquad 0$$

与炮兵阵地类似，采用正向递推，需要满足如下条件：

1. 第 $i$ 行第 $j$ 位不为 $0$ 且第 $i+1$ 行第 $j$ 位已损坏，转移失败
2. 第 $i$ 行第 $j$ 位为 $2$ 时，第 $i+1$ 行第 $j$ 位填 $1$
3. 第 $i$ 行第 $j$ 位为 $1$ 时，第 $i+1$ 行第 $j$ 位填 $0$
4. 已损坏的格子填零跳过
5. 可以尝试填上连续三个 $1$ 或者连续两个 $2$

这样这道题就做完了，我做的时候，想过一个问题，就是何时累加答案，若在填连续两个 $2$ 或者连续三个 $1$ 的时候累加，那么最后一行填连续两个 $2$ 显然是不合法的，芯片的下半部分就超出范围了。有两种解决办法，一种是判断一下边界条件，我采用的是另一种，正常做，只不过计算答案的时候直接用 $f[n][0]$ 即可。

内存限制很小，滚动一下就行，改动不大。

放代码，注释很详细：

```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 155;
const int maxm = 11;
int a[maxn][maxm];
int T,n,m,k;
int f[2][60005];
int pow[11];
void init(){
	pow[0] = 1;
	for (int i = 1; i <= 10; i++) pow[i] = pow[i-1]*3;
}
int suan(int x, int pos){ // 数 x 的三进制第 pos 位是多少 
	return x%pow[pos]/pow[pos-1];
}
bool ifok(int x, int pos, int lst){ // 第 x 行第 pos 位是否能放 
	if (!a[x][pos] && !suan(lst,m-pos+1)) return 1; // 当前位置不能损坏，上一行当前位置必须为零 
	return 0; 
}
void dfs(int x/*这是第几行*/, int lst/*上一行的状态*/, int now/*当前行搜索到的状态*/,  int pos/*从左往右搜到第三进制几位*/, int cnt/*放了几个数了*/){
	if (!pos){ // 更新状态 
		 f[x%2][now] = max(f[x%2][now],f[(x-1)%2][lst]+cnt);
		 return;
	}
	if (suan(lst,pos)){//上一行当前非零 
		if (a[x][m-pos+1]) return;
		if (suan(lst,pos) == 2) dfs(x,lst,now*3+1,pos-1,cnt);
		else dfs(x,lst,now*3, pos-1,cnt); 
	} 
	else{
		dfs(x,lst,now*3,pos-1,cnt);//什么都不放，跳！ 
		if (pos >= 2 && ifok(x,m-pos+1,lst) && ifok(x,m-pos+2,lst)){ //尝试放 3*2 的 （竖的） 
			dfs(x,lst,(now*3+2)*3+2,pos-2,cnt+1); 
		} 
		if (pos >= 3 &&  ifok(x,m-pos+1,lst) && ifok(x,m-pos+2,lst) && ifok(x,m-pos+3,lst)){ //尝试放 2*3 的 （横的） 
			dfs(x,lst,((now*3+1)*3+1)*3+1,pos-3,cnt+1);
		}
	}
}
int main(){
	//freopen("a.in","r",stdin);
	init();
	cin >>T;
	
	while (T--){
		
		cin >> n >> m >> k;
		memset(a,0,sizeof a);
		for (int i = 1; i <= k; i++){
			int x,y;
			cin >> x >> y;
			a[x][y] = 1;
		}
		
		memset(f,-0x3f3f3f3f,sizeof f);
		f[0][0] = 0;
		for (int i = 0; i < n; i++){
			for (int j = 0; j < pow[m]; j++) f[(i+1)%2][j] = -0x3f3f3f3f;
			for (int j = 0; j < pow[m]; j++){
				if (f[i%2][j] < 0) continue;
				dfs(i+1,j,0,m,0);
			}
		}
		cout << f[n%2][0] << endl;
	}
	return 0;
}
```









---

## 作者：渡鸦2007 (赞：10)

首先，我们采用正向递推。
把 $2\times 3 $ 与 $3 \times 2$ 的芯片分别表示为：
$$\text{ 2            2  }$$


$$\text{ 1             1 }$$  


$$\text{ 0             0 }$$


与

$$\text{ 1       1      1 }$$ 

$$\text{ 0       0      0 }$$

考虑第 $i+1$ 行的状态（三进制数）。需要满足以下条件：
1. 第 $i$ 行第 $j$ 位为 $2$ 时，第 $i+1$ 行第 $j$ 位填 $1$。
2. 第 $i$ 行第 $j$ 位为 $1$ 时，第 $i+1$ 行第 $j$ 位填 $0$。
3. 必须连续填完一整个芯片

因为转移方程难以写出，我们选择**行内**进行 dfs 判断转移。

这里再补充一下第一篇题解里几个没讲清楚的点。
- pos 从 $m$ 到 $0$，是因为三进制数的最末尾对应的是地图的最右端。
- 搜索的开始要判定上一行是否合法才能开始本行的搜索。

我的代码变量从 $1$ 开始，可能更适合阅读。
```cpp
bool wr[160][12];
int n,m,k;
int thr[20]= {1,3,9,27,81,243,729,2187,6561,19683,59049};
int f[2][65536];
int get(int num,int pos)
{
	return num%thr[pos]/thr[pos-1];
}
bool able(int r,int c,int bef)
{
	if (wr[r][c]==0 && get(bef,m-c+1)==0) return 1;
	else return 0;
}
int ans=0;
void dfs(int line,int bef,int now,int pos,int cnt)//本行三进制数的位置,芯片数量
{
	if (pos==0)//本行搜完了
	{
		f[line&1][now]=max(f[line&1][now],f[line-1&1][bef]+cnt);
		return;
	}
	int bt=get(bef,pos);//上一行这一位
	if (bt!=0)
	{
		if (wr[line][m-pos+1]) return;
		if (bt==2) dfs(line,bef,now*3+1,pos-1,cnt);
		else if (bt==1) dfs(line,bef,now*3,pos-1,cnt);
	}
	else
	{
		dfs(line,bef,now*3,pos-1,cnt);
		if (pos>=2 && able(line,m-pos+1,bef) && able(line,m-pos+2,bef))
			dfs(line,bef,(now*3+2)*3+2,pos-2,cnt+1);
		if (pos>=3 && able(line,m-pos+1,bef) && able(line,m-pos+2,bef) && able(line,m-pos+3,bef))
			dfs(line,bef,((now*3+1)*3+1)*3+1,pos-3,cnt+1);
	}
}
int main()
{
	int d;d=read();
	while (--d>=0)
	{
		n=read();m=read();k=read();
		for (int i=1; i<=k; ++i)
		{
			wr[read()][read()]=1;
		}
		memset(f,-0x3f,sizeof f);
		f[0][0]=0;
		for (int i=1;i<=n;++i)
		{
			for (int j=0;j<thr[m];++j) f[i&1][j]=-0x3f3f3f3f;
			for (int j=0;j<thr[m];++j)
			{
				if (f[i-1&1][j]<0) continue;
				else dfs(i,j,0,m,0);
			}
		}
		cout<<f[n&1][0]<<endl;
		memset(wr,0,sizeof wr);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}

```


---

## 作者：Tyyyyyy (赞：5)

## P7689

提供一种不太一样的做法，也许本质上相差不多？

考虑将每个格子表示为 $6$ 种状态：

- $0$，表示该格子未被覆盖。

- $1\sim 3$，表示该格子是某个 $2\times 3$ 矩形中的第 $1\sim 3$ 列。

- $4\sim 5$，表示该格子是某个 $3\times 2$ 矩形终点第 $1\sim 2$ 列。

那么对于一列而言，合法的状态需要满足：

- 连续且相同的 $1\sim 3$ 的个数是 $2$ 的倍数。

- 连续且相同的 $4\sim 5$ 的个数是 $3$ 的倍数。

对于可以出现在相邻两列的状态而言，需要满足：

- 这两列的状态都满足上面的条件。

- 对于每一行，都可以从第一列转移到第二列。（可以转移的有 $0\to 0,0\to 1,0\to 4$，$1\to 2,2\to 3$，$3\to 0,3\to 1,3\to 4$，$4\to 5$，$5\to 0,5\to 1,5\to 4$。

搜索出每一列所有合法的状态，可以发现在 $m=10$ 的情况下也只有 $5779$ 种。再搜索出这些状态之间哪些可以出现为相邻两列，发现只有 $174881$ 对状态满足。

于是，设 $f_{i,j}$ 表示考虑到第 $i$ 列，第 $i$ 列状态为 $j$，按之前搜索出的状态关系转移即可。

极限情况下时间复杂度为 $O(174881n)$，可以通过。

Code：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int N=160,M=11,S=5800,E=174885;
int T,n,m,K,a[N][M],f[2][S],b[N],c[S],d[S],num[S];
int sta[S][M],tot,tmp[M],now;
int fr[E],to[E],cnt;
void dfs(int x)
{
	if(x==m+1)
	{
		tot++;
		for(int i=1;i<=m;i++)sta[tot][i]=tmp[i];
		return;
	}
	tmp[++now]=0,dfs(x+1),now--;
	if(x+2<=m+1)
	{
		for(int i=1;i<=3;i++)
			tmp[++now]=i,tmp[++now]=i,dfs(x+2),now-=2;
	}
	if(x+3<=m+1)
	{
		for(int i=4;i<=5;i++)
			tmp[++now]=i,tmp[++now]=i,tmp[++now]=i,dfs(x+3),now-=3; 
	}
}
bool chk(int x){return !x||x==3||x==5;}
unordered_map<int,int>id;
int p;
void expand(int x,int key)
{
	if(x==m+1)return fr[++cnt]=p,to[cnt]=id[key],void();
	if(chk(sta[p][x]))expand(x+1,key*6);
	if(x+2<=m+1&&chk(sta[p][x])&&chk(sta[p][x+1]))expand(x+2,(key*6+1)*6+1);
	if(x+3<=m+1&&chk(sta[p][x])&&chk(sta[p][x+1])&&chk(sta[p][x+2]))expand(x+3,((key*6+4)*6+4)*6+4);
	if(sta[p][x]==1)expand(x+1,key*6+2);
	if(sta[p][x]==2)expand(x+1,key*6+3);
	if(sta[p][x]==4)expand(x+1,key*6+5);
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&n,&m,&K);
		for(int i=1;i<=n;i++)b[i]=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				a[i][j]=1,b[i]|=(1<<j);
		for(int i=1,x,y;i<=K;i++)
			scanf("%d%d",&x,&y),a[x][y]=0,b[x]^=(1<<y);
		tot=0,id.clear(),dfs(1);
		for(int i=1;i<=tot;i++)
		{
			c[i]=num[i]=0;int c1=0,c2=0;
			for(int j=1;j<=m;j++)
				if(sta[i][j])c[i]|=(1<<j);
			for(int j=1;j<=m;j++)
				c1+=(sta[i][j]==3),c2+=(sta[i][j]==5),num[i]=num[i]*6+sta[i][j];
			d[i]=c1/2+c2/3,id[num[i]]=i;
		}
		cnt=0;
		for(int i=1;i<=tot;i++)p=i,expand(1,0);
		memset(f,~0x3f,sizeof(f));
		f[0][1]=0;int ans=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=cnt;j++)
				if((c[to[j]]&b[i])==c[to[j]])
					f[i&1][to[j]]=max(f[i&1][to[j]],f[(i&1)^1][fr[j]]+d[to[j]]);
			for(int j=1;j<=tot;j++)f[(i&1)^1][j]=-1e9,ans=max(ans,f[i&1][j]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：pengyule (赞：4)

一年以前没有 AC 的状压 DP 模板题。

- 设状态：$f_{i,x,y}$ 代表第 $i-1$ 行采用 $x$ 号状态的情况下，第 $i$ 行采用 $y$ 号状态最多能裁出的芯片数。
	- 【注1】二进制状态的定义：每一个状态包含 $2\times3$ 芯片的状态和 $3\times2$ 芯片的状态。以下图方式记录一行的状态：
    ![image.png](https://s2.loli.net/2021/12/13/h6JDOW29ZMq5UkF.png)
    - 【注2】“$x$ 号”状态的含义：由于一个状态可能*自相矛盾*，即上表中“对应二进制状态”在一行之中成为图案是不可能不重叠的，因此预处理出合法的状态。假如将每一个状态编号存起来，那么这就是某号状态的含义。另外，经统计，合法状态的数量最多在 270 左右。
- 列转移：$f_{i,x,y}\gets\max(f_{j,z,x})$。标准的状压转移，注意判断合法性来剪枝。但由于常数问题和剪枝顺序的不同程序的效率可能受影响。下面给出一种可行的实现方式。
```cpp
//options[x]表示第x号合法状态
//p[x]表示第x行的板子状态，1表示坏了，0表示能用
for(int i=3;i<=n-1;i++)
			for(int z=1;z<=num;z++)if(!((options[z].occ1|options[z].occ2)&p[i]|(options[z].occ1|options[z].occ2)&p[i+1]|options[z].occ2&p[i-1]))
				for(int x=1;x<=num;x++)if(!((options[x].occ1|options[x].occ2)&(options[z].occ1|options[z].occ2)))
					for(int y=1;y<=num;y++)if(!((options[y].occ1|options[y].occ2)&options[z].occ2))
						if(f[i&1^1][y][x] || x==1)
							f[i&1][x][z]=max(f[i&1][x][z],f[i&1^1][y][x]+cnt[options[z].s1]+cnt[options[z].s2]);
```
- 边界：边界就是“当前行”为 1 或 2 的情况，特别地转移即可。这也是为什么上面的 $i$ 是从 3 开始的。
- [提交记录](https://loj.ac/s/1321936)

---

## 作者：luckydrawbox (赞：2)

[$\text{Link}$](https://www.luogu.com.cn/problem/P7689)

## 题意

一个 $m$ 行 $n$ 列的网格，里面可以放 $2\times3$ 和 $3\times2$ 两种不同的芯片，其中 $k$ 个格子被损坏不能占用，求最多可以放下多少个芯片。

## 分析

注意到 $m$ 特别小，不超过 $10$，因此可以考虑使用状态压缩 $\text{dp}$，参考[炮兵阵地](https://www.luogu.com.cn/problem/P2704)这题在《算法竞赛进阶指南》上的解法二，我们可以设计一种类似的状态表示方式：

- $2\times 3$ 的芯片的表示方法：

$$\begin{aligned}2\ \ \ \ 1\ \ \ \ 0\\ 2\ \ \ \ 1\ \ \ \ 0\end{aligned}$$

- $3\times 2$ 的芯片的表示方法：

$$\begin{aligned}1\ \ \ \ 0\\1\ \ \ \ 0\\1\ \ \ \ 0\end{aligned}$$

$2\times3$ 的芯片的两个 $2$ 和 $3\times2$ 的三个 $1$ 都表示放了一个芯片，规定 $2$ 后面必须填 $1$，$1$ 后面必须填 $0$，只有 $0$ 后面才可以放新的芯片，我们称之为“自由格”，记为 $-1$，显然，$-1$ 的位置可能填 $0$ 或 $1$ 或 $2$。

这样，每一列都可以被状态压缩为一个 $m$ 位三进制数，可以用一个 $0\sim 3^m-1$ 之间的一个十进制整数表示。

设 $dp_{i,s}$ 表示第 $i$ 列状态为 $s$ 时，前 $i$ 列可以放的芯片个数，若状态不合法则值应为 $-1$。我们枚举一个合法的状态 $s$，把它按三进制位拆分到 $a_{1\sim m}$ 中，考虑它可以转移到第 $i+1$ 列的哪些状态 $t$，先求出 $t$ 的待定数组 $b_{1\sim m}$，根据前面的表示方法，有 $b_i=a_i-1$，若 $b_i$ 已经被损坏，则 $b_i=0$，若 $b_i$ 被损坏的同时 $a_i\ge1$，说明在状态 $s$ 下 $b_i$ 应被占用却是损坏的，要转移到 $t$ 也是不合法的，应该排除这种情况下的状态 $s$。

然后我们通过待定数组 $b$ 求出合法转移状态 $t$，但像这种状态表示比较复杂，冗余比较多的题目，我们不一定非要写出确切的状态转移方程，可以通过深度优先搜索确定可以转移到的 $t$：

- 若 $b_i\le0$，则 $b_i$ 被强制用为 $0$ 或为自由格，这个格子可以填 $0$。
- 若 $b_i=1$，则 $b_i$ 被强制用为 $1$，这个格子必须填 $1$。
- 若 $b_i=-1$，则 $b_i$ 为自由格，则查询接下去的 $1$ 或 $2$ 个格子是否也是自由格，若是则可以放芯片，芯片数量增加 $1$。

目标状态为 $dp_{n,0}$。

看起来这道题目已经做完了，不过交上去你会发现 $\text{MLE}$ 了，原来这道题目过于毒瘤，只留了 $\text{8MB}$ 的空间，于是我们可以使用滚动数组优化空间，不过要注意重置数组（我就是这样调到凌晨 $1$ 点的）。

这种做法的时间复杂度是 $O(N3^M\times?)$，十分玄学，会 $\text{TLE}$ 得死死的，我们可以加一个小优化：注意到枚举状态 $s$ 时，有一些损坏的格子的状态一定是 $0$，完全不需要花太多时间去枚举他们，我们记录第 $i$ 列的损坏的格子的个数 $in_i$，只要枚举 $3^{m-in_i}$ 个 未损坏的格子的状态即可。

然而这种做法还是过于垃圾，只能得到 $70$ 分，得加上大量的优化，选择合适的语言，开启 $\text{O2}$ 后卡卡常数才可以压线过。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long read(){
	long long x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=160,M=12,S=6e4+10;
int d,n,m,k,m3[M]={1},dp[2][S],in[N],a[M],s,b[M];
bool v[N][M];
void make(int x,int j){
	s=0;
	for(int i=m;i>=1;i--){
		if(v[x][i])
			a[i]=0;
		else{
			a[i]=j%3;
			j/=3;
		}
		s=s*3+a[i];
		b[i]=a[i]-1;
		if(v[x+1][i]&&a[i]){//跳过特殊不合法状态 
			s=m3[m];
			return;
		}
		if(v[x+1][i])
			b[i]=0;
	}
}
void dfs(int x,int y,int t,int sum){
	if(!y){
		dp[x^1][t]=max(dp[x^1][t],dp[x][s]+sum);
		return;
	}
	//填 0
	if(b[y]<=0)
		dfs(x,y-1,t*3,sum);
	//强制填 1 
	if(b[y]==1)
		dfs(x,y-1,t*3+1,sum);
	//可以放芯片 
	if(b[y]==-1){
		//3*2
		if(y-2>0&&b[y-1]==-1&&b[y-2]==-1)
			dfs(x,y-3,t*27+1*9+1*3+1,sum+1);
		//2*3
		if(y-1>0&&b[y-1]==-1)
			dfs(x,y-2,t*9+2*3+2,sum+1);
	}
}
int main(){
	for(int i=1;i<12;i++)
		m3[i]=m3[i-1]*3;
	d=read();
	while(d--){
		n=read();m=read();k=read();
		memset(v,0,sizeof(v));
		memset(in,0,sizeof(in));
		memset(dp,-1,sizeof(dp));
		for(int i=1,x,y;i<=k;i++){
			x=read();y=read();
			v[x][y]=1;
			in[x]++;
		}
		dp[0][0]=0;
		for(int i=0;i<n;i++){
			for(int j=0;j<m3[m-in[i]];j++){
				make(i,j);
				if(dp[i&1][s]==-1)//不合法状态 
					continue;
				dfs(i&1,m,0,0);
			}
			for(int j=0;j<m3[m-in[i+2]];j++){//重置数组 
				make(i+2,j);
				dp[i&1][s]=-1;
			}
		}
		write(dp[n&1][0]);
		puts("");
	}
	return 0;
}
```


---

## 作者：_yolanda_ (赞：2)


[博客园食用更佳](https://www.cnblogs.com/yolanda-yxr/p/16472169.html)

[原题链接](https://www.luogu.com.cn/problem/P7689)

## 题目分析

#### 思路

看到这道题第一反应是 [蒙德里安的梦想](https://www.acwing.com/problem/content/293/)，很像，只是这道题放的长方形大小不太一样。

那道题的一个做法是状压 DP，每行状态二进制中 $1$ 表示一个骨牌的上半部分（即这个骨牌一定竖着放），$0$ 代表其他情况。最后答案是 $f_{n,0}$。

再看这道题数据范围，$M$ 很小，八九不离十是状压 DP 了。仿照上面的做法，会发现由于长方形大小的原因，单纯的二进制似乎无法满足所有要求。

横着放只有 $2$ 行可以表示，但竖着放时就有 $3$ 行。那可以自然地想到 $3$ 进制。

可以这样表示：

![](https://cdn.luogu.com.cn/upload/image_hosting/0je4s84i.png)

然后可以枚举每一行，从上一行的可行状态来考虑枚举这一行的符合条件的所有状态，再更新。

---

#### 枚举状态细节

1. 如果上一行当前位置有值，但这个点不能用，直接返回。
2. 如果当前点不能用，为 $0$ 。
3. 如果上一行的当前位置非零，为上一行的值 $-1$ 。
4. 如果上一行这个位置即后面两个位置都为零，且这一行这几个点都可用，可以一起设为 $1$ 。
5. 如果上一行这个位置即后面一个位置都为零，且这一行这几个点都可用，可以一起设为 $2$ 。
6. 这个位置为 $0$ 。

先满足前三个，如果是前三个的一种，搜索完直接返回。

否则枚举完剩下三种情况。具体见代码。

因为空间范围很小，所以滚动一下数组。

## Code

```cpp
#include<bits/stdc++.h>
//By _yolanda_
using namespace std;
#define int long long

const int N=6e4+5,INF=1e15;
int f[2][N],w[200][20];
int n,m;
int in[15];

inline int read(){
	int sum=0,f=1;char a=getchar();
	while(a<'0' || a>'9'){if(a=='-') 	f=-1;a=getchar();}
	while(a>='0' && a<='9') 	sum=sum*10+a-'0',a=getchar();
	return sum*f;
}

inline int get(int x,int y){ //找3进制下x的第y位
	int tmp=in[y];
	return (x/tmp)%3;
}
void dfs(int x,int y,int no,int pre,int sum){
	if(y==m){//到边界，更新
		f[x%2][no]=max(f[(x%2)^1][pre]+sum,f[x%2][no]);
		return;
	}
	int t=get(pre,m-y-1); //上一行，这个位置的值
	if(w[x][y+1]){ //这个位置不能用
		if(t)	return;
		dfs(x,y+1,no*3,pre,sum);
	}
	else if(t){
		dfs(x,y+1,no*3+t-1,pre,sum);//第3种情况
	}
	else{
		if(x<n && m-y>=3 && !get(pre,m-y-2) && !get(pre,m-y-3) && !w[x][y+2] && !w[x][y+3]){
			int tmp=no*3+1;tmp=tmp*3+1,tmp=tmp*3+1;
			dfs(x,y+3,tmp,pre,sum+1);
		}//连着填3个1
		if(x<n-1 && m-y>=2 && !get(pre,m-y-2) &&!w[x][y+2]){
			int tmp=no*3+2;tmp=tmp*3+2;
			dfs(x,y+2,tmp,pre,sum+1);
		}//连着填3个2
		dfs(x,y+1,no*3,pre,sum);//填0
	}
}

signed main(){
	
	in[0]=1;
	for(int i=1;i<=10;++i)	in[i]=in[i-1]*3;
	int T,k;T=read();
	while(T--){
		memset(w,0,sizeof w);
		memset(f,0,sizeof f);
		n=read(),m=read(),k=read();
		
		int tp=pow(3,m);
		int xx,yy;
		for(int i=1;i<=k;++i){
			xx=read(),yy=read();
			w[xx][yy]=1;
		}
		dfs(1,0,0,0,0);
		for(int i=2;i<=n;++i){
			for(int j=0;j<tp;++j)	f[i%2][j]=-INF;
			for(int j=0;j<tp;++j)
				if(f[(i-1)%2][j]>=0)	dfs(i,0,0,j,0);
				//上一行这个状态可得到才更新，否则会TLE
		}
		printf("%lld\n",f[n%2][0]);
	}
	
	return 0;
}
```

---

## 作者：WisNourx_ (赞：1)

本题和 [[NOI2001] 炮兵阵地](https://www.luogu.com.cn/problem/P2704) 与 [AcWing 291 蒙德里安的梦想](https://www.acwing.com/problem/content/293/) 比较类似，算是两者的结合升级版，可以先去看看这两题，会对理解本题有帮助。

### 题目大意

给定一个 $N \times M$ 的网格图，有 $K$ 个地方不能放置，求最多能放下多少个 $2 \times 3$ 的矩形。

### 思路

由于有不能放置的格子，判定放置的条件可能太复杂，考虑状压 DP。

设 $f_{i, j}$ 表示前 $i$ 行状态为 $j$ 时的最大放置数。判定放置矩形只需要知道上两行的状态即可，故第一维可以滚动优化，只记录这一行与上一行的状态，用上一行来表示出上上行。

第二维的状态用三进制表示，对于每一位 $k$，$0$ 表示上一行和本行的第 $k$ 位都可放置，$1$ 表示本行的第 $k$ 位可放置，$2$ 表示上一行和本行的第 $k$ 位都不可放置。

三进制的状态转移一般使用 dfs 转移，即每列逐位填数判定。在 dfs 时以每个位置为左下角判断是否可以填充的矩形（注意横竖要分开计算）并与上一状态比较维护 $f$ 数组，最后统计最大值即可。

细节：注意三进制的转换和表示，dfs 时边界处理以及 $0, 1, 2$ 所代表的意义。

### Code
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

char buf[1<<20], *p1=buf, *p2=buf;
#define getchar() (p1==p2&&(p2=buf+fread(p1=buf, 1, 1<<20, stdin), p1==p2)?EOF:*p1++)
template <typename T>
void read(T &x)
{
	x=0;int f=1;char c=getchar();
	while (!isdigit(c)) f=(c=='-')?-1:1, c=getchar();
	while (isdigit(c)) x=(x<<1)+(x<<3)+c-'0', c=getchar();
	x*=f;
}

typedef long long LL;
const int N=160, M=12;
int n, m, k, f[2][59060];
bool v[N][M];int pre[M], cur[M];
int fac[M]={1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147};

int three_to_ten(int tmp[])
{
	int res=0;
	for (int i=0;i<m;i++)
		res+=tmp[i]*fac[i];
	return res;
}

void ten_to_three(int tmp[], int x)
{
	for (int i=0;i<m;i++)
	{
		tmp[i]=x%3;
		x/=3;
	} 
}

void dfs(int now, int j, int last, int state)
{
	f[now][state]=max(f[now][state], last);
	if (j>=m) return ;
	if (j+1<m&&!pre[j]&&!pre[j+1]&&!cur[j]&&!cur[j+1])
	{
		cur[j]=cur[j+1]=2;
		dfs(now, j+2, last+1, three_to_ten(cur));
		cur[j]=cur[j+1]=0;
	}
	if (j+2<m&&!cur[j]&&!cur[j+1]&&!cur[j+2])
	{
		cur[j]=cur[j+1]=cur[j+2]=2;
		dfs(now, j+3, last+1, three_to_ten(cur));
		cur[j]=cur[j+1]=cur[j+2]=0;
	}
	dfs(now, j+1, last, state);
}

void solve()
{
	memset(pre, 0, sizeof pre);
	memset(cur, 0, sizeof cur);
	memset(f[0], -1, sizeof f[0]);
	for (int i=0;i<m;i++) pre[i]=v[1][i]?2:1;
	int tmp=three_to_ten(pre), now=0;
	f[now][tmp]=0;
	for (int i=2;i<=n;i++)
	{
		now^=1;
		memset(f[now], -1, sizeof f[now]);
		for (int j=0;j<fac[m];j++)
		{
			if (f[now^1][j]==-1) continue;
			ten_to_three(pre, j);
			for (int k=0;k<m;k++)
			{
				if (v[i][k]) cur[k]=2;
				else cur[k]=pre[k]?pre[k]-1:0;
			}
			tmp=three_to_ten(cur);
			dfs(now, 0, f[now^1][j], tmp);
		}
	} 
	int ans=0;
	for (int i=0;i<fac[m];i++) ans=max(ans, f[now][i]);
	printf("%d\n", ans);
}

int main()
{
	int T;read(T);
	while (T--)
	{
		memset(v, 0, sizeof v);
		read(n), read(m), read(k);
		for (int i=1;i<=k;i++)
		{
			int x, y;
			read(x), read(y);
			v[x][--y]=1;
		}
		solve();
	} 
	return 0;
}
```


---

## 作者：splendore (赞：1)

### 题意
用 $2×3$ 或 $3×2$ 的方块尽量填满 $N×M$ 的格子（有地方不可填）。

### 思路
考虑到二进制不能很好的表示状态，所以我们将状态压位成三进制。

可表示为如下：
```
2 2
1 1
0 0
```
```
1 1 1
0 0 0
```
那么我们就可以上记忆化搜索了。
代码如下：
```
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
constexpr int d[]={1,3,9,27,81,243,729,2187,6561,19683,59049};
int n,m,k,f[2][59049];
bool g[151][11];
inline int get(int x,int p){return x%d[p]/d[p-1];}
inline bool vaild(int r,int c,int x){return !g[r][c]&&!get(x,m-c+1);}
void dfs(int r,int num,int now,int p,int s){
	if(!p)return f[r&1][now]=max(f[r&1][now],f[(r-1)&1][num]+s),void();
	int pre=get(num,p);
	if(!pre){
		dfs(r,num,now*3,p-1,s);
		if(p>=2&&vaild(r,m-p+1,num)&&vaild(r,m-p+2,num)){
			dfs(r,num,(now*3+2)*3+2,p-2,s+1);
			if(p>=3&&vaild(r,m-p+3,num))
				dfs(r,num,((now*3+1)*3+1)*3+1,p-3,s+1);
		}
	}
	else if(!g[r][m-p+1])dfs(r,num,now*3+(pre==2),p-1,s);
}
int main(){
	int T;scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&m,&k);
		memset(g,0,sizeof(g));
		for(int i=1,x,y;i<=k;++i)
			scanf("%d%d",&x,&y),g[x][y]=1;
		memset(f,0xbf,sizeof(f));f[0][0]=0;
		for(int i=1;i<=n;++i)
			for(int j=0;j<d[m];++j)
				if(f[(i-1)&1][j]>=0)
					dfs(i,j,0,m,0),f[(i-1)&1][j]=0xbfbfbfbf;
		printf("%d\n",f[n&1][0]);
	}
	return 0;
}
```

---

## 作者：Fzrcy (赞：0)

类似 [P2704 [NOI2001] 炮兵阵地](https://www.luogu.com.cn/problem/P2704) 这道题，考虑用 $f_{i,j,k}$ 表示到第 $i$ 行，该行的状态为 $j$，第 $i-1$ 行的状态为 $k$ 的方案数，但是时间复杂度显然不对，考虑状态压缩。

我们发现第 $i$ 行的放置方案只与 $(i,j)$ 是否能放置芯片有关，考虑用高进制来表示状态。

首先将 $(2\times 3)$ 和 $(3\times 2)$ 的芯片分别表示为：

$$
\begin{aligned}
&1 \quad 1 \quad 1\\
&0 \quad 0 \quad 0\\
\end{aligned}
$$

和

$$
\begin{aligned}
&2 \quad 2\\
&1 \quad 1\\
&0 \quad 0\\
\end{aligned}
$$

设 $a_{i,j}$ 表示 $(i,j)$ 所填的值，那么有：

1. 若 $a_{i,j}$ 的值为 $2$，则 $a_{i+1,j}$ 的值为 $1$。

2. 若 $a_{i,j}$ 的值为 $1$，则 $a_{i+1,j}$ 的值为 $0$。

3. 若 $(i,j)$ 已经损坏，则 $a_{i-1,j}=0$，且 $a_{i,j}=0$。

那么以 $(i,j)$ 为左上角放置一个 $2\times 3$ 的芯片就是将 $a_{i,j}=a_{i,j+1}=a_{i,j+2}=1$、$a_{i+1,j}=a_{i+1,j+1}=a_{i+1,j+2}=0$。

以 $(i,j)$ 为左上角放置一个 $3\times 2$ 的芯片就是将 $a_{i,j}=a_{i,j+1}=2$、$a_{i+1,j}=a_{i+1,j+1}=1$、$a_{i+2,j}=a_{i+2,j+1}=0$。

状态转移方程容易写出，但是不容易递推实现，可以考虑 $\texttt{DFS}$ 进行转移。

由于内存只有 $\texttt{8.00 MB}$，所以要用滚动数组，注意状态转移数组的清空。

```cpp
#include <bits/stdc++.h>
using std::cin;    using std::cout;
using std::printf; using std::scanf;
template<typename T> inline void Max(T &x, const T &y){x<y?x=y:0;return;}
const int N=3e2+1;

int Pow3[55];
void init_pow_base_3(int tt){
  Pow3[1]=1;
  for(int i=2; i<=tt+1; i++)
    Pow3[i]=Pow3[i-1]*3;
}

int n, m, K, vis[N][55], f[2][200000];

int getith(int F, int pos){return (F/Pow3[pos])%3;}
int allow(int I, int F, int Pos){return getith(F, Pos)==0&&vis[I][Pos]==0;}

void dfs(int I, int Last, int F, int Pos, int Cnt){
  if(Pos==m+1) return Max(f[I&1][F], f[(I-1)&1][Last]+Cnt);
  int L=getith(Last, Pos);
  if(L!=0){
    if(vis[I][Pos])return;
    dfs(I, Last, F+Pow3[Pos]*(L-1), Pos+1, Cnt);
    return;
  }
  else{
    dfs(I, Last, F, Pos+1, Cnt);

    if(Pos<m&&allow(I, Last, Pos)&&allow(I, Last, Pos+1))
      dfs(I, Last, F+2*(Pow3[Pos]+Pow3[Pos+1]), Pos+2, Cnt+1);

    if(Pos<m-1&&allow(I, Last, Pos)&&allow(I, Last, Pos+1)&&allow(I, Last, Pos+2))
      dfs(I, Last, F+1*(Pow3[Pos]+Pow3[Pos+1]+Pow3[Pos+2]), Pos+3, Cnt+1);
  }
  return;
}
int main(){
  int T;
  scanf("%d", &T);
  init_pow_base_3(11);

  while(T--){
    scanf("%d %d %d", &n, &m, &K);
    memset(vis, 0, sizeof vis);
    for(int i=1, a, b; i<=K; i++)
      scanf("%d %d", &a, &b), vis[a][b]=1;

    memset(f, -0x3f3f3f3f, sizeof f);
    f[0][0]=0;

    for(int i=1; i<=n; i++){
      for(int j=0; j<Pow3[m+1]; j++)
        f[i&1][j]=-0x3f3f3f3f;

      for(int j=0; j<Pow3[m+1]; j++)
        if(f[(i-1)&1][j]>=0) dfs(i, j, 0, 1, 0);
    }

    cout<<f[n&1][0]<<'\n';
  }
  return 0;
}
```



---

## 作者：registerGen (赞：0)

本文同步发表于 [cnblogs](https://www.cnblogs.com/registergen/p/p7689_solution.html)。

## Solution

感谢同学对这个题的~~精彩~~讲解！

设 $f_{i,S_1,S_2}$ 表示处理完前 $i$ 行，第 $i+1$ 行的“突起”状态为 $S_1$，第 $i+2$ 行的“突起”状态为 $S_2$。

转移时，我们设第 $i$ 行的状态为 $S$，第 $i-1$ 行 **“突起”到第 $\bm{i+1}$ 行** 的状态为 $S_0$，那么我们要从 $f_{i-1,S,S_0}$ 转移到 $f_{i,S_1,S_2}$：

$$f_{i,S_1,S_2}=f_{i-1,S,S_0}+\frac{|S_2|}2+\frac{|S_1\backslash S_2\backslash S_0|}3$$

注：$S_2$ 即占据了 $i\sim i+2$ 的 $3\times 2$ 方块，$|S_1\backslash S_2\backslash S_0|$ 即占据了 $i\sim i+1$ 的 $2\times 3$ 方块，可以自行画图理解。

于是这个东西时间复杂度太高，过不去。

注意到 $S_0,S_2$ 中连续 $1$ 的个数必须是偶数，$|S_1\backslash S_2\backslash S_0|$ 中连续 $1$ 的个数必须是三的倍数，我们可以只枚举这些符合要求的状态，这样可以节省很多无用枚举。

另外还有很多小的剪枝，比如 $S_2\subseteq S_1$ 必须成立、$S_0\subseteq S_1\backslash S_2$ 必须成立等等，具体见代码。

另外为了压空间，需要使用 `uint8_t`、`uint16_t` 等类型。

## Code

```cpp
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
using namespace std;

#define count(x) (__builtin_popcount(x))

const int N = 150, M = 10;

int n, m, k;
uint8_t f[2][1 << M][1 << M];
uint16_t a[N + 10];

bool check(int x, int y) {
  int cnt = 0;
  for (int i = 0; i <= (1 << m) - 1; i++) {
    if ((x >> i) & 1) cnt++;
    else {
      if (cnt % y) return 0;
      cnt = 0;
    }
  }
  return 1;
}

void mian() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= k; i++) {
    int x, y; scanf("%d%d", &x, &y);
    a[x] |= (1 << (y - 1));
  }
  uint16_t tot = (1 << m) - 1;
  vector<uint16_t> ok1; // 2
  a[n + 1] = a[n + 2] = tot;
  set<uint16_t> ok2; // 3
  for (uint16_t i = 0; i <= (1 << m) - 1; i++) {
    if (check(i, 2)) ok1.push_back(i);
    if (check(i, 3)) ok2.insert(i);
  }
  // msk0 msk msk1 msk2
  for (int i = 1, ii = 1; i <= n; i++, ii = i % 2)
    for (auto msk2 : ok1)
      if ((msk2 & a[i + 2]) == 0)
        for (uint16_t msk1 = 0; msk1 <= tot; msk1++)
          if ((msk1 & msk2) == msk2 && (msk1 & a[i + 1]) == 0 && (msk1 & a[i]) == 0)
            for (auto msk0 : ok1)
              if ((msk0 & a[i]) == 0 && (msk0 & a[i - 1]) == 0 && ((msk1 - msk2) & msk0) == msk0 && ok2.find(msk1 - msk2 - msk0) != ok2.end())
                for (uint16_t msk = 0; msk <= tot; msk++)
                  if ((msk & a[i]) == 0 && (msk & a[i - 1]) == 0 && ((msk1 - msk0) & msk) == 0 && (msk1 & msk0) == msk0)
                    f[ii][msk1][msk2] = max(f[ii][msk1][msk2], uint8_t(f[(ii + 1) % 2][msk][msk0] + count(msk2) / 2 + count(msk1 - msk2 - msk0) / 3));
  printf("%d\n", int(f[n % 2][0][0]));
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    memset(f, 0, sizeof(f)); memset(a, 0, sizeof(a));
    mian();
  }
  return 0;
}
```

---

