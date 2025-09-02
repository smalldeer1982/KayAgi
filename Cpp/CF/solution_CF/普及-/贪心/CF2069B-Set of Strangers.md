# Set of Strangers

## 题目描述

给定一个包含 $n$ 行 $m$ 列的表格。初始时，第 $i$ 行第 $j$ 列的单元格颜色为 $a_{i, j}$。

我们称两个单元格是陌生人（strangers）如果它们不共享任何一条边（允许通过角落接触）。

我们称一个单元格集合为陌生人集合（set of strangers），当且仅当集合中任意两个单元格都是陌生人。根据定义，包含不超过一个单元格的集合总是陌生人集合。

在每一步操作中，你可以选择一个满足以下条件的陌生人集合：集合中所有单元格颜色相同，并将它们全部涂成另一种颜色（可以选择任意一种颜色作为结果颜色）。

问：要将整个表格涂成同一种颜色，最少需要多少步操作？

## 说明/提示

在第一个测试用例中，表格初始时已经是同一种颜色。

在第二个测试用例中，例如可以先选择所有颜色为 $1$ 的单元格并将其涂成 $3$，然后选择所有颜色为 $2$ 的单元格也涂成 $3$。

在第三个测试用例中，可以选择所有颜色为 $5$ 的单元格并将其涂成 $4$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
1 1
1
3 3
1 2 1
2 3 2
1 3 1
1 6
5 4 5 4 4 5
3 4
1 4 2 2
1 4 3 5
6 6 3 5```

### 输出

```
0
2
1
10```

# 题解

## 作者：Walrus (赞：4)

为什么这个题同机房的人交了一堆罚时？这最多红吧。

## Solution

你发现想把一个颜色全部弄成另一种元素（这里假定 $u\to v$）**至多需要两次操作**，因为在你第一次操作后 $u$ 颜色**一定可以通过一些合理的选择使颜色 $u$ 没有相邻的一对**。

故我们得出如下结论：如果一个颜色 $u$ 在原矩阵中有相邻的一对那么其需要两次操作就能转化为其余**任何一种颜色**，反之只要一次，设 $a_u$ 表示 $u$ 颜色是否存在相邻的一对，$a_u=2$ 表示有，$a_u=1$ 表示没有。

这个过程可以直接 $O(NM)$ 暴力找。

然后答案就是 $\sum\limits_{\forall cl\in S} a_{cl}-\max\limits_{\forall cl \in S} a_{cl}$。

---

## 作者：shiyiming (赞：2)

### [题目传送门](https://www.luogu.com.cn/problem/CF2069B)
## 题目大意
给定一个 $n\times m$ 的矩阵，$col_{i,j}$ 表示第 $i$ 行第 $j$ 列方格的颜色。

所有颜色相同，没有共边的方格称为陌生的集合。

每次操作可以将一个陌生的集合变成其他的颜色。

求将整个矩阵都变成同一颜色的最小操作次数。
## 题解
如果整个矩阵都是同一颜色，那么最多可以分成两个集合，所以每种颜色最多只有两个陌生的集合。

最后输出每种颜色的集合个数之和，因为最后只要变成同一种颜色就可以，所以要减去最大的集合个数。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int color[777][777];
int a[1010101];
int cd[777][777];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int maxx=1;
		int ans=0;
		memset(a,0,sizeof a);
		int n,m;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				cd[i][j]=0;
				scanf("%d",&color[i][j]);
				if(a[color[i][j]]==0)
				{
					a[color[i][j]]=1;
					ans++;
					cd[i][j]=1;
				}
				else
				{
					if(color[i-1][j]==color[i][j])
					{
						cd[i][j]=2;
					}
					if(color[i][j-1]==color[i][j])
					{
						cd[i][j]=2;
					}
					if(cd[i][j])
					{
						if(a[color[i][j]]==1)ans++;
						a[color[i][j]]=max(a[color[i][j]],cd[i][j]);
						continue;
					}
					cd[i][j]=1;
				}
			}
		}
		bool flag=true;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(cd[i][j]==2)
				{
					maxx=2;
					flag=false;
					break;
				}
			}
			if(!flag)break;
		}
		printf("%d\n",ans-maxx);
	}
	return 0;
}

```

---

## 作者：_mi_ka_ (赞：2)

[题目传送门](https://codeforces.com/contest/2069/problem/B)

## 题目大意

对于一个 $n\times m$ 的颜色板，每次操作只能选择若干个相同颜色且**任意两个块都没有相邻的边**的块，将这些块涂成同一种任意颜色，问要将这个颜色板的所有块的颜色统一，最少要进行多少次操作。

## 解题思路

选取一种最终颜色 $c$，对于其中的任意一种颜色 $c'$：

- 如果这种颜色的块中没有相邻的，那么一次以内的操作以定能将其变成颜色 $c$；
- 若果这种颜色的块中有相邻的，第一次操作对于相邻的块，选取其一进行修改，则第二次操作时剩余的块肯定都不相邻，那么最多两次操作一定能将其变成颜色 $c$。

综上，每一种颜色根据其有没有相邻的块可以分成一次和两次修改完，对于颜色板遍历一遍，标记出有相邻块的颜色和没有块的颜色即可。

对于要选取的最终颜色 $c$，只需贪心的选取要进行的操作次数最多的颜色即可。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[720][720];//颜色板 
int ans;//答案 
int tpe[500000];//每种颜色需要进行的操作数 
int re()//快读
void wr(int x)//快写
signed main(){
    int T=re();
    while (T--)
    {
        int n=re(),m=re();
        ans=0;
        for(int i=1;i<=n*m;i++)
            tpe[i]=0;
        for(int i=1;i<=n;i++)
            a[i][m+1]=0;
        for(int i=1;i<=m;i++)
            a[n+1][i]=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                a[i][j]=re();
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            {
                int flag=(a[i][j]==a[i-1][j]||a[i][j]==a[i][j-1]||a[i][j]==a[i+1][j]||a[i][j]==a[i][j+1]);
                //flag代表这种颜色是否有相邻 
                if(tpe[a[i][j]]==0)
                    ans+=tpe[a[i][j]]=int(flag)+1;//有相邻就是2，没相邻就是1 
                else if(tpe[a[i][j]]==1)
                    ans+=int(flag),(tpe[a[i][j]]+=int(flag));//flag==1则为2 
                else
                    continue;
            }
        int maxx=0;//选取操作次数最多的颜色 
        for(int i=1;i<=n*m;i++)
            maxx=max(maxx,tpe[i]);
        wr(ans-maxx),putchar('\n');
    }
    return 0;
}
```

---

## 作者：wuzebang2009 (赞：1)

题目很简单，是一道贪心题，你可以把同一种颜色不相邻的色块变为任意一种颜色，不难发现如果要把一种颜色变为另一种颜色需要的操作数只有 $1$ 或者 $2$ 两种，前者只有当没有任何一对相同颜色的色块相邻，后者则是至少有一对色块相邻时需要的步数，为什么呢，你一定可以把一种同样颜色的色块分成两部分这两部分一定是一组陌生人，而如果本来就是陌生人则不用分。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[800][800];
int color[500010];

void solve(){
	int n,m;
	cin>>n>>m;
	vector<int> cnt;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			if(!color[a[i][j]]) color[a[i][j]]++,cnt.push_back(a[i][j]);
			else if(a[i][j]==a[i-1][j] || a[i][j]==a[i][j-1]) color[a[i][j]]++;
		}
	}
	int ans=0,maxn=0;
	for(int i=0;i<cnt.size();i++){
		if(color[cnt[i]]){
			ans+=color[cnt[i]]==1?1ll:2ll;
//			cout<<ans<<endl;
			maxn=max(maxn,color[cnt[i]]==1?1ll:2ll);
			color[cnt[i]]=0;
		}
	}
	cout<<ans-maxn<<endl;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}
```

---

## 作者：Eason_cyx (赞：1)

个人觉得比 A 好想。

观察得到对于相同的数来说，至多需要两次就可以将他们全部变成另一个数。又发现 $a_i$ 值域不大，所以考虑记 $f_i$ 表示所有 $i$ 如果要全部变成别的数需要几次操作，不难发现 $0 \le f_i \le 2$。这个可以 $O(nm)$ 计算。那么算完之后根据贪心，选择操作次数最多的任意一个数，然后最优策略就是将所有数变成这个数。所以最终答案就是 $ans=\sum f_i - \max f_i$。时间复杂度 $O(nm)$。[提交记录](https://codeforces.com/contest/2069/submission/306950132)

注意，$700 \times 700 = 490000$，不是 $49000$。/oh

---

## 作者：Listar (赞：1)

传送门
---
[洛谷](https://www.luogu.com.cn/problem/CF2069B)  

[CF](https://codeforces.com/contest/2069/problem/B)

赛事简单思路
---

两种不同颜色的操作肯定要分开，所有我们只对一种颜色进行关注即可，最后求每种颜色的操作数总和即可。

对于一种颜色我们注意到可以把所有没有公共边的（即陌生格）全部处理，需要二次处理的只是有接触的格子，两个相邻格子必须需要两次处理，另外我们可以给出一种方法，使得两次处理必能把所有格子处理干净。

具体方法为：

把所有格子分为两类，第一类是奇数行的奇数列格子和偶数行的偶数列格子。第二类是剩下的所有格子，我们发现每一类的所有格子互相均为陌生格。那么这一类构成的集合的子集也总为陌生格。

每次操作一类格子，总能两次把这种颜色的所有格子转化完。

题目要求我们把这些格子转化为一种相同的颜色，我们注意到把格子转化为别的需要转化的颜色总是无意义的，只会有可能增加别的需要转化的颜色的操作次数，我们只需要转化给一种需要的操作次数最多的颜色，这样可以避免这些元素转化给其他元素的操作。

我们可以只留意是否有需要转化两次的颜色出现，我们把所有颜色转化为一种颜色的时候，只需减去操作次数最多的元素，其中操作次数只有一次或者两次，如果有需要转化两次的元素，我们可以直接在所有操作次数减去二，若没有，则减去一。


赛时代码实现
---

对于 python 语言我们只需要开一个列表，来存储颜色和对应的操作数量。


```python
def solve():
    n,m=map(int,input().split())
    line=[]
    for _ in range(n):
        line.append(list(map(int,input().split())))
    ##数据读入
    
    lp=dict()   #字典的键为颜色，对于的值为是否有相连的元素，有则2，没有则为1
    l1=[-1,1]    #上下
    for i in range(n):
        for j in range(m):
            count=1   #统计
            for k in l1: #循环进行减小代码量
                if i+k>=0 and i+k<n:  #防止列表超界
                    if line[i+k][j]==line[i][j]: #判断颜色是否一样
                        count=2
                if j+k>=0 and j+k<m:
                    if line[i][j+k]==line[i][j]:
                        count=2
            lp[line[i][j]]=max(count,lp.get(line[i][j],0))#更新字典的值
    lr=list(lp.values())#获取字典的值的列表

    print(sum(lr)-max(lr))
    #输出结果

T=int(input())
for i in range(T):solve()
```

赛时优化改用 c++ 语言想到了开一个颜色数组去统计。

对于 c++ 语言我们只需开一个颜色的数组，因为 c++ 语言数组对内存占用较小，这样可以保证对应每个块检查次数尽可能的少， c++ 的速度要远快于 python。

```cpp
//
//Created by Listar on 25-2-15.
//
#include<bits/stdc++.h>

using namespace std;

void solve(){
    int n,m;
    cin >> n >> m;
    int a[n+5][m+5]={0},p[n * m+2]={0};
    for(int i = 1;i <= n;i++){
        for (int j = 1;j <= m;j++){
            cin >> a[i][j];
        }
    }
    //读入
    for(int i = 1;i <= n;i++){
        for (int j = 1;j <= m;j++){
            if (p[a[i][j]]==0 || p[a[i][j]]==1){
                if (i>1 && a[i-1][j]==a[i][j]){p[a[i][j]]=2;continue;}
                if (i<n && a[i+1][j]==a[i][j]){p[a[i][j]]=2;continue;}
                if (j>1 && a[i][j-1]==a[i][j]){p[a[i][j]]=2;continue;}
                if (j<m && a[i][j+1]==a[i][j]){p[a[i][j]]=2;continue;}
                p[a[i][j]]=1;//对于颜色进行标记，如果标记为2的颜色直接跳过循环，减少循环次数。
            }
        }
    }

    int c=0,q=1;
    for(int i=1;i<=n*m;i++){
        if (q==1){
            if (p[i]==2) q=2;//判断是否存在需要操作两次的元素
        }
        c+=p[i];
    }
    //统计最终结果，对于其他未被计入的颜色，其初始值零保证了不会多加。
    cout << c-q << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int _ = 1;
    cin >> _;
    while (_ --) {
        solve();
    }
    return 0;
}
```


赛后复盘
---

赛时的 python 代码的缺陷在于每个块都要检查很多次，边缘的块要检查三次，中间的要接近四次，主要原因在于没有用列表统计每个颜色的次数。但是赛时主要担心 python 列表过长导致内存超限。赛后复盘想到了一个每个块只需检查一次的方法，即对每个块进行 dfs，查找颜色相同的代码，这里给出 python 非递归调用的 dfs 实现代码。

```python
def solve():
    n,m=map(int,input().split())
    line=[]
    l=[]
    for _ in range(n):
        line.append(list(map(int,input().split())))
        l.append([0]*m)
    lp=dict()
    lt=[]
    for i in range(n):
        for j in range(m):
            if l[i][j]:continue
            c=0
            lt.append((i,j))
            while lt:
                x,y=lt.pop()
                c+=1
                if x>0 and l[x-1][y]==0 and line[x-1][y]==line[x][y]:
                    l[x-1][y]=1
                    lt.append((x-1,y))
                elif x<n-1 and l[x+1][y]==0 and line[x+1][y]==line[x][y]:
                    l[x+1][y]=1
                    lt.append((x+1,y))
                elif y>0 and l[x][y-1]==0 and line[x][y-1]==line[x][y]:
                    l[x][y-1]=1
                    lt.append((x,y-1))
                elif y<n-1 and l[x][y+1]==0 and line[x][y+1]==line[x][y]:
                    l[x][y+1]=1
                    lt.append((x,y+1))
            if c>1:c=2
            lp[line[i][j]]=max(c,lp.get(line[i][j],0))
    lr=list(lp.values())
    print(sum(lr)-max(lr))


T=int(input())
for i in range(T):solve()
```

---

## 作者：wangboyue (赞：1)

# 题意
给定一个 $n$ 行 $m$ 列的染色网格。每次操作可以选取一组同颜色且不相邻的格子，将它们染为另一种颜色。求出将网格染为同一颜色的最小操作数。
# 思路
1. 明显统一网格颜色的最少操作数就是将每种颜色转换为其它颜色的操作步数和减去操作数最大的颜色的操作数。
2. 对于每种颜色，可以发现不同连通块之间的操作是可以同时进行的。  
即：对于每种颜色，转换为其它颜色的操作步数就是将它的最大连通块转换为其它颜色的操作步数。
3. 在一个连通块中，将它的最大连通块转换为其它颜色的操作步数小于 $2$。  
证明：将连通块 01 染色，使得相邻格子的颜色不同，按照颜色进行操作，操作数最大为 $2$。  
明显当连通块的大小 $size>1$ 时，要操作 $2$ 次，否则操作 $1$ 次。（如果连通块有不止 $1$ 个格子但是它们不相邻，那么它们就不可能在一个连通块中。）在代码实现中按照此思路即可。
# 代码
（本人在写题解时才意识到不需要 01 染色，所以代码中使用的是 01 染色的方法。）
```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=700+5,M=490000+5;
int a[N][N],cmax[M],n,m;
int dx[]={0,1,-1,0,0};
int dy[]={0,0,0,1,-1};
bool vis[N][N],mp[N][N],f0,f1;
void dfs(int x,int y){
	vis[x][y]=true;
	if(mp[x][y]){
		f1=true;
	}
	else{
		f0=true;
	}
	for(int i=1;i<=4;i++){
		int nx=x+dx[i],ny=y+dy[i];
		if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&!vis[nx][ny]&&a[nx][ny]==a[x][y]){
			dfs(nx,ny);
		}
	}
	return;
}
int help(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			vis[i][j]=false;
		}
	}
	for(int i=1;i<=n*m;i++){
		cmax[i]=0;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(!vis[i][j]){
				f0=f1=false;
				dfs(i,j);
				cmax[a[i][j]]=max(cmax[a[i][j]],(long long)f0+f1);
			}
		}
	}
	int ans=0,maxi=0;
	for(int i=1;i<=n*m;i++){
		ans+=cmax[i];
		maxi=max(maxi,cmax[i]);
	}
	return ans-maxi;
}
void pre(){
	bool f=true;
	for(int i=1;i<=700;i++){
		for(int j=1;j<=700;j++){
			f^=1;
			mp[i][j]=f;
		}
		f^=1;
	}
	return;
}
signed main(){
	pre();
	int t;
	cin>>t;
	while(t--){
		cout<<help()<<"\n";
	}
	return 0;
}

```

---

## 作者：yvbf (赞：1)

![](bilibili:BV1DkAzetEX9?t=173)

---

## 作者：xiaobeng_0912 (赞：0)

## $\mathbf{Knowledge}$

1. 模拟

## $\mathbf{Solution}$

对于每一个颜色不是最终颜色的方格，如果这个方格的四周都没有和它同颜色的方格，那么只要用一次操作，将这个方格变成最终颜色就可以了。

如果这个方格的四周有和它同颜色的方格，这些方格构成一个连通块，那么这个连通块里的所有方格一定可以使用两次操作全部变成目标颜色，例如最开始时：

```
1 1 2
2 1 2
1 1 2
```

第一次修改：

```
2 1 2
2 2 2
2 1 2
```

第二次修改：

```
2 2 2
2 2 2
2 2 2
```

对于选那哪种颜色作为最终颜色，只需选取操作次数最多的颜色即可。

## $\mathbf{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,maxn,a[701][701],ans,te[490001];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		maxn=-0x3f3f3f3f;
		ans=0;//多测要清空
		memset(a,0,sizeof(a));//多测要清空
		memset(te,0,sizeof(te));//多测要清空
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				scanf("%d",&a[i][j]);
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(te[a[i][j]]==0){
					te[a[i][j]]=(a[i][j]==a[i-1][j]||a[i][j]==a[i][j-1]||a[i][j]==a[i+1][j]||a[i][j]==a[i][j+1])+1;//标记
					ans+=te[a[i][j]];
				}else if(te[a[i][j]]==1){
					ans+=(a[i][j]==a[i-1][j]||a[i][j]==a[i][j-1]||a[i][j]==a[i+1][j]||a[i][j]==a[i][j+1]);
					te[a[i][j]]+=(a[i][j]==a[i-1][j]||a[i][j]==a[i][j-1]||a[i][j]==a[i+1][j]||a[i][j]==a[i][j+1]);
				}
			}
		}
		for(int i=1;i<=n*m;i++){
			maxn=max(maxn,te[i]);
		}
		printf("%d\n",ans-maxn);
	}
	return 0;
}
```

---

## 作者：chatoudp (赞：0)

我们要让所有颜色相同，自然要变成一个对答案影响最大的颜色（把所有这个颜色变成另一种颜色次数最多的）。

我们可以发现若一种颜色两辆不相邻，仅需 $1$ 次即可将这个颜色变为另一种，否则则需 $2$ 次。

于是我们只需求出所有颜色变成另一种颜色的次数的和，再减去最大的一个即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,mp[705][705],T,cnt,maxn;
bool f[1000005],g[1000005];
int dx[]={0,0,-1,1};
int dy[]={-1,1,0,0};
int main(){
	scanf("%d",&T);
	while(T--){
		maxn=0;
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		scanf("%d%d",&n,&m);;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				scanf("%d",&mp[i][j]),maxn=max(maxn,mp[i][j]),g[mp[i][j]]=1;
		int kk=1;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				for(int k=0;k<4;k++){
					int nx=i+dx[k],ny=j+dy[k];
					if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&mp[nx][ny]==mp[i][j])
						f[mp[i][j]]=1,kk=2;
				}
		int ans=0;
		for(int i=1;i<=maxn;i++) if(g[i]) ans+=f[i]+1;
		printf("%d\n",ans-kk);
	}
	return 0;
}

```

---

## 作者：Engulf (赞：0)

注意到对于一种颜色 $c$，最多 $2$ 次即可将这种颜色全部变为另一种颜色 $c'$：
- 若颜色 $c$ 的每个四连通（上下左右）意义下的连通块大小均为 $1$，$1$ 次操作即可。
- 若颜色 $c$ 存在一个四连通意义下的连通块大小 $\ge 2$，对所有连通块进行黑白染色（相邻的块颜色不同，在方格图里是一定能做到的），只需两次操作（分别选黑色一次，白色的一次）即可。

对全图进行搜索，找出每种颜色的操作次数，把其他所有颜色都变为操作次数最多的那个颜色即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 705;

int n, m;
int a[N][N];

int cnt[N * N];

bool vis[N][N];

int dfs(int x, int y, int col) {
    if (x < 1 || x > n || y < 1 || y > m || vis[x][y] || a[x][y] != col) return 0;
    vis[x][y] = 1;
    return 1 + dfs(x + 1, y, col) + dfs(x - 1, y, col) + dfs(x, y - 1, col) + dfs(x, y + 1, col);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                cin >> a[i][j], vis[i][j] = 0;
        for (int i = 1; i <= n * m; i++) cnt[i] = 0;

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (!vis[i][j])
                    cnt[a[i][j]] = min(2, max(cnt[a[i][j]], dfs(i, j, a[i][j])));

        sort(cnt + 1, cnt + 1 + n * m);
        int ans = 0;
        for (int i = 1; i < n * m; i++)
            ans += cnt[i];

        cout << ans << "\n";
    }
    return 0;
}
```

---

## 作者：_Kamisato_Ayaka_ (赞：0)

[CF2069B](https://www.luogu.com.cn/problem/CF2069B)

## Statement

给定一个 $n \times m$ 的矩阵，第 $i$ 行 $j$ 列的方格颜色为 $a_{i,j}$。

如果两个方格并不共享边，我们称其为陌生的方格，对于一个又陌生的方格组成的集合，若该集合内方格元素均相同，我们可以将集合内的方格同意涂成另一种颜色。

你需要最少多少操作次数使得所有方格颜色相同。

$n,m \leq 700,\sum{n \cdot m} \leq 5 \times 10^5$。

## Solution

如果说有共享边且颜色相同的方格，显然操作次数会多一次，并且要涂掉一个颜色操作数不是 $1$ 就是 $2$，因为如果同一颜色方格没有共享变一次就可以涂完。

开值域桶记每个颜色的操作数，统计操作数和减去最大操作数就是答案。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
int T, n, A[777][777], B[500005], m;

signed main() {
	scanf ("%d", &T);
	while (T --) {
		scanf ("%d %d", &n, &m);
		fill (B + 1, B + n * m + 1, 0LL);
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j <= m; j ++) {
				scanf ("%d", &A[i][j]);
			}
		}
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j <= m; j ++) {
				bool flag = false;
				for (int k = 0; k < 4; k ++) {
					int nx = i + dx[k], ny = j + dy[k];
					if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
					if (A[i][j] == A[nx][ny]) {
						flag = true;
						break; 
					}
				}
				B[A[i][j]] = max (B[A[i][j]], 1 + flag);
			}
		}
		int Sum = 0, tot = 0;
		for (int i = 1; i <= n * m; i ++) 
			tot = max (tot, B[i]), Sum += B[i];
		printf ("%d\n", Sum - tot);
	}
	return 0;
}
```

---

## 作者：Tachibana27 (赞：0)

我们考虑一个东西：对于某种颜色，把所有这种颜色的格子变成其他颜色一定不超过 $2$ 步。待会我会讲如何做到。

有以下可能：

1. 某种颜色不存在于这个矩阵中，其变化为其他颜色的代价为 $0$ 步。

2. 对于所有是某种颜色的格子，若都互不相邻，则为 $1$ 步。

3. 否则，我们考虑将原矩阵**黑白染色**，容易证明存在染法使得同色不相邻。此时，对于某种颜色，黑色格子上的颜色一组，白色的一组，不超过 $2$ 步。

最后，有一种颜色是不需要变的，显然选某个代价最大的颜色即可。

建议评黄或绿。

我因为用了一些迷的判断方式导致吃了几发罚时。

code:

```cpp
#define int long long
int t;
int n,m;
int a[786][786];
class node{
	public:
		int l;
		int r;
};
std::vector<node>e[500086];
bool cmp1(node a,node b){
	return a.l==b.l?a.r<b.r:a.l<b.l;
}
bool cmp2(node a,node b){
	return a.r==b.r?a.l<b.l:a.r<b.r;
}
signed main(){
	t=read();
	// t=1;
	while(t--){
		int maxn=0;
		int sum=0;
		n=read();
		m=read();
		for(int i=1;i<=n*m;i++)
			e[i].clear();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				a[i][j]=read();
				e[a[i][j]].push_back((node){i,j});//存下所有颜色为某种颜色的格子的位置
				// std::cout<<a[i][j]<<" "<<i<<" "<<j<<"\n";
			}
		for(int i=1;i<=n*m;i++){
			if(e[i].size());//存在此颜色
			else
				continue;
			std::sort(e[i].begin(),e[i].end(),cmp1);//先按 x 排序，再按 y 排序
			bool flag=false;
			for(int j=1;j<e[i].size();j++){
				// std::cout<<e[i][j].l<<" "<<e[i][j].r<<" "<<e[i][j-1].l<<" "<<e[i][j-1].r<<"\n";
				if(e[i][j].l==e[i][j-1].l and abs(e[i][j].r-e[i][j-1].r)<=1){
					flag=true;
					// std::cout<<e[i][j].l<<" "<<e[i][j].r<<"\n";
					break;
				}
			}
			if(flag){
				sum+=2;
				maxn=2;
				continue;
			}
			std::sort(e[i].begin(),e[i].end(),cmp2);
			for(int j=1;j<e[i].size();j++)
				if(e[i][j].r==e[i][j-1].r and abs(e[i][j].l-e[i][j-1].l)<=1){
					flag=true;
					break;
			}
			if(flag){
				sum+=2;
				maxn=2;
				continue;
			}
			sum++;
			maxn=std::max(maxn,1LL);
		}
		std::cout<<sum-maxn<<"\n";
		// n=read();
		// for(int i=1;i<=n;i++)
		// 	a[i]=read();
	}
	return 0;
}
```

---

