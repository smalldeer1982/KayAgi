# Bear and Three Musketeers

## 题目描述

Do you know a story about the three musketeers? Anyway, you will learn about its origins now.

Richelimakieu is a cardinal in the city of Bearis. He is tired of dealing with crime by himself. He needs three brave warriors to help him to fight against bad guys.

There are $ n $ warriors. Richelimakieu wants to choose three of them to become musketeers but it's not that easy. The most important condition is that musketeers must know each other to cooperate efficiently. And they shouldn't be too well known because they could be betrayed by old friends. For each musketeer his recognition is the number of warriors he knows, excluding other two musketeers.

Help Richelimakieu! Find if it is possible to choose three musketeers knowing each other, and what is minimum possible sum of their recognitions.

## 说明/提示

In the first sample Richelimakieu should choose a triple $ 1 $ , $ 2 $ , $ 3 $ . The first musketeer doesn't know anyone except other two musketeers so his recognition is $ 0 $ . The second musketeer has recognition $ 1 $ because he knows warrior number $ 4 $ . The third musketeer also has recognition $ 1 $ because he knows warrior $ 4 $ . Sum of recognitions is $ 0+1+1=2 $ .

The other possible triple is $ 2,3,4 $ but it has greater sum of recognitions, equal to $ 1+1+1=3 $ .

In the second sample there is no triple of warriors knowing each other.

## 样例 #1

### 输入

```
5 6
1 2
1 3
2 3
2 4
3 4
4 5
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7 4
2 1
3 6
5 1
1 7
```

### 输出

```
-1
```

# 题解

## 作者：yangjinqian (赞：4)

现在数据变大了，一些题解的 $O(n^3)$ 做法不行了。

## 题目大意：

给你一个无向图，要找到三点，且满足：

1. 三个点互相相邻（组成一个环）

2. 三点的邻居个数之和最少（除了相邻两点）

## 思路
用邻接矩阵存图，并把每条边存下来，在用一个数组记录每条边左右两点邻居点的个数。

接下来枚举每条边，找出这条边一点的所有邻居点（不包括另一点），看是否有一邻居点和另一点相邻，若有，则出现环，更新答案，否则继续遍历。

最后输出答案即可。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 4010;
int n, m, minn = 0x3f3f3f3f;
int num[N], x[N], y[N];
int a[N][N];
int main(){
	cin >> n >> m;
	for (int i = 1; i <= m; i++){
		cin >> x[i] >> y[i];
		a[x[i]][y[i]] = 1, a[y[i]][x[i]] = 1, num[x[i]]++, num[y[i]]++;
	}
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			if (a[x[i]][j] && a[j][y[i]])
				minn = min(minn, num[x[i]] + num[y[i]] + num[j]);
	if (minn == 0x3f3f3f3f) cout << -1;
	else cout << minn - 6;
	return 0;
}
```

[AC记录](https://codeforces.com/problemset/submission/574/294307982)

---

## 作者：H_space (赞：4)

[CF原题](https://codeforces.com/problemset/problem/574/B)

## 题目大意

有 $n$ 个人，现从中选出来 $3$ 个人去当火枪手。

选人的原则是，这 $3$ 个人之间必须**两两相互认识**，并且，若用 $cnt_i$ 表示选出来的 $3$ 个人中第 $i$ 个人认识的人的数量(不包括另外两个人)，要求 $cnt_1+cnt_2+cnt_3$ 的值是所有的可能中最小的那个。

现在，给定 $n$ 以及 $m$ 个认识的关系 $(x_i, y_i)$，表示 $x_i$ 和 $y_i$ 相互认识，请你选出合适的三个人，然后只需输出对应的最小的 $cnt_1+cnt_2+cnt_3$ 的值即可。

## 题目思路

由于认识关系没有传递性，所以 $A$ 认识 $B$, $B$ 认识 $C$, 并不意味着 $A$ 认识 $C$。


在录入数据后，利用三重循环遍历，求出和的最小值即可。


下面用代码实现：
```cpp
#include<iostream>
using namespace std;

int n, m, a[4005], b[4005][4005], ans = 1e8; // ans尽量开大 

int main(){
    cin >> n >> m;
    for(int i = 1; i <= m; i ++) {
        int x, y;
        cin >> x >> y;
        b[x][y] = 1;
        b[y][x] = 1;
        a[x] ++;
        a[y] ++;
    }
    for(int i = 1; i <= n; i ++) {
        for(int j = i + 1; j <= n; j ++) {
            if(b[i][j]) {
                for(int k = j + 1; k <= n; k ++){
                    if(b[i][k] && b[j][k])
                        ans = min(ans, a[i] + a[j] + a[k]-6);
                }
            }
        }
    }
    if(ans != 1e8) cout << ans << endl;
    else cout << "-1" << endl;
    
	return 0;
}


```

 

---

## 作者：zhangzirui66 (赞：2)

# 思路
互相认识没有传递关系，所以 $A$ 认识 $B$，$B$ 认识 $C$，但 $A$ 不一定认识 $C$。直接三层循环模拟即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, a[4005], b[4005][4005], ans = 2e9;//a数组是认识的人数，b是邻接矩阵
int main(){
    cin >> n >> m;
    for(int i = 1; i <= m; i ++){
        int x, y;
        cin >> x >> y;
        b[x][y] = 1;
        b[y][x] = 1;//无向图，所以有两次
        a[x] ++;
        a[y] ++;
    }
    for(int i = 1; i <= n; i ++)
        for(int j = i + 1; j <= n; j ++){
            if(b[i][j]){
                for(int k = j + 1; k <= n; k ++){
                    if(b[i][k] && b[j][k]) ans = min(ans, a[i] + a[j] + a[k] - 6);//他们三个互相认识，要减去6
                }
            }
        }
    if(ans != 2e9) printf("%d\n", ans);
    else puts("-1");
    return 0;
}
```

---

## 作者：MIN__2500 (赞：2)

题目大意：

有n个人,现在要从这n个人当中选出来3个人去当间谍.
选人的原则是,这3个人之间必须两两相互认识,并且,设cnti表示选出来的3个人中第i个人认识的人的数量(不包括另外两个人),要求cnt1+cnt2+cnt3的值是所有的可能中最小的那个.
现在,给你n以及m个认识的关系(xi,yi),表示xi和yi相互认识.
请你选出合适的三个人,然后只需输出对应的最小的cnt1+cnt2+cnt3的值即可.

第一行两个整数n和m(3<=n<=4000,0<=m<=4000).
接下来m行,第i行包含两个正整数ai和bi(1<=ai,bi<=n,ai!=bi).
数据保证每对关系最多出现一次.
认识关系没有传递性,A认识B,B认识C,并不意味着A认识C.

输出只有一个整数,表示满足要求的三个人的cnt1+cnt2+cnt3的值.
如果无法选出任何满足要求的三个人,则输出"-1".

简介：
1认识2.

2认识3.

BUT

1可能不认识3.

AC代码：
```
#include <bits/stdc++.h>
using namespace std;
#define inf INT_MAX//把可能调成最大
int a[4005],b[4005][4005];
int main()
{
    int n,m;
    int mi=inf;
    cin>>n>>m;
    for(int i=1;i<=m;i++)//输入
    {
        int x,y;
        cin>>x>>y;
        b[x][y]=1;
        b[y][x]=1;
        a[x]++;
        a[y]++;
    }
    for(int i=1;i<=n;i++)//三重循环加遍历
    {
        for(int j=i+1;j<=n;j++)
        {
            if(b[i][j])
            {
                for(int k=j+1;k<=n;k++)
                {
                    if(b[i][k]&&b[j][k])
                    {
                        mi=min(mi,a[i]+a[j]+a[k]-6);//求最小值
                    }
                }
            }
        }
    }
    if(mi!=inf)//如果有就输出
        cout<<mi<<endl;
    else//否则
        cout<<"-1"<<endl;//输出-1
    return 0;
}

```

感谢洛谷大佬，

希望可以过。

---

## 作者：_saltFish_ (赞：1)

[博客食用效果更佳](https://www.cnblogs.com/ytxy-bolg/articles/16583141.html)。

看到这一题，应该第一时间就想得到一个 $\mathcal{O}({n}^{3})$ 的算法：考虑枚举这个环上的三个点，再判断这三个点是否构成环，更新答案即可。

对于答案的计算，我们可以用一个数组 $du[i]$ 来记录每个节点的度数。而对于一个无向图中的点来说，它的邻居数量就是它的度数。

根据题意还需要去掉环中的另外两个点（~~题面的表述好模糊~~）。

综上，对于一个点 $a$ 来说，它对它所在的环的贡献即为 $du[a]-2$。

那么对于 $a,b,c$ 三个点构成的环计算的答案即为 $du[a] + du[b] + du[c] - 6$。

但是很明显会被本题 $n \le 4\times10^{3}$ 的数据范围给卡掉。

仔细思考后不难发现能优化的只有枚举三个点的过程，在枚举的过程中产生了大量的无用情况。

那么如果我们枚举边呢。

考虑使用链式前向星或邻接表来存储整张图，枚举第一个节点（下称 $a$），再由 $a$ 的所有边延伸到第二个点（下称 $b$），再由 $b$ 延伸到第三个点（下称 $c$），这样一来就保证了 $a$ 与 $b$ 之间有连边，$b$ 与 $c$ 之间有连边。

这时就只需要判断 $a$ 与 $c$ 是否有连边即可，而这一过程可以使用邻接矩阵来优化。

在这一顿优化后，算法就快得飞起了，很多测试点只有 $0$ 毫秒，最慢的测试点都只有 $77$ 毫秒，成功轰下你谷最优解。

而且[吸氧](https://www.luogu.com.cn/record/83599984)和[不吸氧](https://www.luogu.com.cn/record/83600038)的用时~~居然一样~~。

```cpp
#include<iostream>
using namespace std;
const int N(4e3+5);
int n,m,ans=0x7fffffff;
int tot,h[N],nxt[N<<1],to[N<<1],du[N];
bool can[N][N];
inline void add(int x,int y){
	nxt[++tot]=h[x],to[h[x]=tot]=y;
	nxt[++tot]=h[y],to[h[y]=tot]=x;
}
int main(){
	#ifdef ytxy
	freopen("in.txt","r",stdin);
	#endif
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		du[u]++;du[v]++;
		can[u][v]=can[v][u]=1;
		add(u,v);
	}
	for(int i=1;i<=n;i++){
		for(int j=h[i];j;j=nxt[j]){
			int v1=to[j];
			for(int k=h[v1];k;k=nxt[k]){
				int v2=to[k];
				if(can[v2][i]) ans=min(ans,du[i]+du[v1]+du[v2]-6);
			}
		}
	}
	if(ans==0x7fffffff) cout<<-1;
	else cout<<ans;
}
```

---

## 作者：Noby_Glds (赞：1)

这题比较暴力。
### 思路：
首先我们可以想到一个 $O(n^3)$ 的垃圾算法，就是枚举三个点，判断他们是否形成一个环，然后更新答案。

于是，该算法在 $n \le 4000$ 的数据范围下，死了。

我们考虑优化暴力。

可以发现，上面的算法枚举了很多无用的情况。

于是我们用链式前向星存图（用邻接表也行），然后枚举第一个点，然后从第一个点往下搜枚举第二个点，继续往下搜枚举第三个点。

这样就可以保证第一个点和第二个点直接连接，第二个点和第三个点直接连接。

只需要判断第一个点和第三个点是否直接连接，然后更新答案就行了。
### 代码：
```cpp
#include<bits/stdc++.h>
#define N 4010
using namespace std;
struct hhh{
	int v,next;
}dl[N*2];
int n,m,u,v,in[N],ans,tot,vis[N][N],head[N];
void qxx(int u,int v){
	dl[++tot].v=v;
	dl[tot].next=head[u];
	head[u]=tot;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>u>>v;
		in[u]++,in[v]++,vis[u][v]=vis[v][u]=1;
		qxx(u,v),qxx(v,u);
	}
	ans=INT_MAX;
	for(int i=1;i<=n;i++){
		for(int j=head[i];j;j=dl[j].next){
			int v=dl[j].v;
			for(int k=head[v];k;k=dl[k].next){
				int v2=dl[k].v;
				if(vis[v2][i]==1) ans=min(ans,in[i]+in[v]+in[v2]-6);
			}
		}
	}
	if(ans==INT_MAX) cout<<"-1";
	else cout<<ans;
	return 0;
} //马蜂较丑请见谅
```


---

## 作者：sbh2012 (赞：0)

## 大意
有 $n$ 个人，现从中选出来 $3$ 个人去当火枪手。这 $3$ 个人之间必须两两相互认识。
## 思路
互相认识没有传递关系，所以尽管 $A$ 认识 $B$ 且 $B$ 认识 $C$ ，但 $A$ 不一定认识 $C$ 。所以需要直接三层循环模拟。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[4005],G[4005][4005],mx=1e9;
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        G[x][y]=1;
        G[y][x]=1;
        a[x]++;
        a[y]++;
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(G[i][j]){
                for(int k=j+1;k<=n;k++){
                    if(G[i][k]&&G[j][k]){
                    	mx=min(mx,a[i]+a[j]+a[k]-6);
					}
                }
            }
        }
    }
    if(mx!=1e9){
    	cout<<mx;
	}else{
		cout<<-1;
	} 
	return 0;
}
```

---

## 作者：Archy_ (赞：0)

[洛谷传送门](https://www.luogu.com.cn/problem/CF574B)
[CF传送门](https://codeforces.com/problemset/problem/574/B)

## 题目大意：

一个图上 $n$ 个点，有 $m$ 对点相连，也就是读入 $n$，$m$ 后读入 $m$ 对 $a$，$b$。

如果三个点**互相**相连，也就是**形成了一个环**。

令第一个点与 $x$ 个点（除它们三个以外的点）相连，第二个点为 $y$，第三为 $z$。

也就是求 $x + y + z$ 的**最小值**。

不得不说本题翻译的很精炼。

## 解题思路：

考虑暴力，建立一个 bool 数组 $vis$ 记录两点之间是否相连，建立 int 数组 $p$ 记录每个点与其他点相连的个数。

每当输入一对 $a$，$b$，进行如下操作：
```cpp
int a = read(), b = read();
p[a]++, p[b]++;
vis[a][b] = 1, vis[b][a] = 1;
```
$p_a$，$p_b$ 都加 $1$，$vis$ 数组应两对都改为 true。

接着枚举 $vis$ 数组即可。
```cpp
#define reg register
for(reg int i=1;i<=n;i++)
	for(reg int j=i+1;j<=n;j++)
		if(vis[i][j])
			for(reg int k=j+1;k<=n;k++)
				if(vis[j][k]&&vis[i][k])
					ans=min(ans,p[i]+p[j]+p[k]-6);
```

---

## 作者：_Clown_ (赞：0)

# B.Bear and Three Musketeers
$\mathtt{Difficulty}$=$\mathtt{1500}$

~~使用暴力可以通过本题。~~

我们考虑暴力枚举 $3$ 个点，

条件为两两之间都有连边，

然后取这 $3$ 个点的度数之和的最小值。

因为不包括这 $3$ 个点本身，

所以最终答案还要 $-6$。

**但是**，

这样写会得到 $\texttt{TLE}$，

不难想到一个基础的剪枝，

就是如果选的 $2$ 个点已经没有连边，

就直接 `break` 掉。

代码就不难写出了。

```cpp
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
using namespace std;
int N,M,Deg[4001];
bool Map[4001][4001];
int main(void)
{
	BetterIO;
	register int i,j,k;cin>>N>>M;
	for(i=1;i<=M;i++)
	{
		register int U,V;cin>>U>>V;
		Map[U][V]=Map[V][U]=true,Deg[U]++,Deg[V]++;
	}
	register int Ret(INT_MAX);
	for(i=1;i<=N;i++)for(j=i+1;j<=N;j++)if(Map[i][j])for(k=j+1;k<=N;k++)if(Map[i][j]&&Map[i][k]&&Map[j][k])Ret=min(Ret,Deg[i]+Deg[j]+Deg[k]);
	if(Ret==INT_MAX)Ret=5;
	cout<<Ret-6<<endl;
	return 0;
}
```

---

