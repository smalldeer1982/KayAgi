# [ABC074D] Restoring Road Network

## 题目描述

#### 题面翻译
曾经存在的高桥王国有N个城市，城市与城市之间用长度为正整数的无向道路连接。

现有一考古学家找到了一张N×N的表A，这张表代表了这N座城市两两之间的最短路。即表中的第u行第v列的值代表了从城市u到v的最短路长度。

问能否根据这张表，求出高桥王国的最小道路长度总和。

## 样例 #1

### 输入

```
3
0 1 3
1 0 2
3 2 0```

### 输出

```
3```

## 样例 #2

### 输入

```
3
0 1 3
1 0 1
3 1 0```

### 输出

```
-1```

## 样例 #3

### 输入

```
5
0 21 18 11 28
21 0 13 10 26
18 13 0 23 13
11 10 23 0 17
28 26 13 17 0```

### 输出

```
82```

## 样例 #4

### 输入

```
3
0 1000000000 1000000000
1000000000 0 1000000000
1000000000 1000000000 0```

### 输出

```
3000000000```

# 题解

## 作者：fls233666 (赞：2)

**2020年2月13日更新：根据要求修复排版格式**

-------

看着这张表和这个神奇的数据范围 $(1 \le N \le 300)$，你是否想起了什么？

是最短路算法中的 Floyd 算法，时间复杂度为 $O(n^{3})$，正好符合数据范围！

这个算法的核心语句只有四行：

```cpp
for(int k=1;k<=n;k++)
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
```

而此题的正解，就从改造这四行语句开始：

## 正解思路

因为表 A 是城市两两之间的最短路表，所以我们肯定要三重 for 循环把这个最短路表按 Floyd 的方式遍历一遍。

然后我们想：**如果有 $a_{i,j} = a_{i,k}+a_{k,j}$，那么我们在统计最小边权和时，就不用把$a_{i,j}$统计进去，因为我们把$a_{i,k}$与$a_{k,j}$统计进去了**。

于是我们可以开一个 $N \times N$ 大小的 $\texttt{bool}$ 数组 $p$，把 $p_{i,j}$ 标记一下，那么统计边权和时只要统计**没有标记过的对点最短路长度**即可。因为是无向图，所以最后输出统计的 $\texttt{ans}$ 时要除以 $2$。

至于无解的情况，就是 $a_{i,j}>a_{i,k}+a_{k,j}$，即$a_{i,j}$中的值**不是最短路的值**时，此时无解，输出 $-1$。

最后注意一下，上述的判断过程要在 $i \ne j \ne k$ 时，运行的结果才是正确的。可以思考一下为什么。

完整代码如下：

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int main(){
    
    long long int n,ans=0,i,j,k;
    cin>>n;
    long long int a[n+1][n+1];
    bool p[n+1][n+1];
    memset(p,0,sizeof(p));
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            cin>>a[i][j];
    //读入数据以及初始化操作

    for(k=1;k<=n;k++)      
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++){
                if(k!=j&&k!=i&&i!=j){
                    if(a[i][j]==a[i][k]+a[k][j])
                        p[i][j]=1;  //标记
                    if(a[i][j]>a[i][k]+a[k][j]){
                        cout<<"-1"<<endl;  //不是最短路，无解
                        return 0;
                    }
                }
            }
    //核心操作语句

    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            if(p[i][j]==0)
                ans+=a[i][j]; //统计长度总和
    cout<<ans/2<<endl;
    //统计总和及输出

    return 0;
}
```


---

## 作者：Misserina (赞：1)

### 题目概述

给出一个 $n \times n$ 的矩阵，表示每两点间的最短路，先判断这样的公路网是否可能存在，再求原先的公路网中最短的总公路路程。

### 解析

- 从 $a$ 号点到 $b$ 号点，如果经由某一点距离比这两点之间的最短路径还要短，那么这样的图肯定不存在；
- 如果经由某一点距离等于这两点之间的最短路径，那么这两点之间可以没有公路，否则两点之间有公路。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,arr[305][305],check[305][305];
long long res=0;
bool direct[305][305];
int main() {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=n;j++) {
			scanf("%d",&arr[i][j]);
			direct[i][j]=1;
		}
	}
	for (int i=1;i<=n;i++) {
		direct[i][i]=0;
		for (int j=i+1;j<=n;j++) {
			for (int mid=1;mid<=n;mid++) {
				if (mid!=i && mid!=j && arr[i][j]==arr[i][mid]+arr[mid][j]) direct[i][j]=direct[j][i]=0;
			}
			res+=direct[i][j]*arr[i][j];
		}
	}
	bool can=1;
    for (int i=1;i<=n;i++) {
        for (int j=i+1;j<=n;j++) {
            int mnd=0x7fffffff;
            for (int mid=1;mid<=n;mid++) {
                mnd=min(mnd,arr[i][mid]+arr[mid][j]);
            }
            if (mnd!=arr[i][j]) {
                can=0;
            }
        }
    }
	if (can) printf("%lld",res);
	else printf("-1");
}
```

---

## 作者：taojinchen (赞：1)

# 思路
我们发现当两点之间的最短路和表中不一样时，无解。

当两点之间的最短路可以通过其他点周转过来时，这条边则可以不要。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
unsigned long long a[305][305],i,j,k,t,n,f[305][305],ans,vis[305][305];
int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n;
  for(i=1;i<=n;i++){
    for(j=1;j<=n;j++){
      cin>>a[i][j];
      f[i][j]=a[i][j];
      ans+=a[i][j];//统计
    }
  }
  ans>>=1;//因为是无向边
  for(k=1;k<=n;k++){
    for(i=1;i<=n;i++){
      for(j=1;j<=n;j++){
        f[i][j]=min(f[i][j],f[i][k]+f[k][j]);//最短路
      }
    }
  }
  for(i=1;i<=n;i++){
    for(j=1;j<=n;j++){
      if(f[i][j]!=a[i][j]||a[i][j]!=a[j][i])t=1;//无解
    }
  }
  if(t){//无解
    cout<<-1;
    return 0;
  }
  for(k=1;k<=n;k++){
    for(i=1;i<n;i++){
      if(k==i)continue;
      for(j=i+1;j<=n;j++){
        if(k==j)continue;
        if(f[i][j]==f[i][k]+f[k][j]&&vis[i][j]==0){//不重复删
          ans-=f[i][j],vis[i][j]=1;//这条边则可以不要
        }
      }
    }
  }
  cout<<ans;
  return 0;
}
```


---

## 作者：Naganorhara_Yoimiya (赞：1)

# 题解：AT_arc083_b [ABC074D] Restoring Road Network

## 思路

注意到  $ n ≤ 300 $，所以考虑 Floyd。对于每两个节点，如果跑出来的距离和给出的距离不符，就输出 $ -1 $ （无解情况）。那么，对于有解的情况，如果起始点可以通过其他的点到达目标点，就删除掉该起始点与该目标点之间的那条边。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 305;
int ma[maxn][maxn],f[maxn][maxn],n,tot = 0,head[maxn];
const long long INF = 1e11;
long long ans = 0;
bool vis[maxn][maxn];

void Floyd(){
	for(int k = 1;k <= n;k++)
    	for(int i = 1;i <= n;i++)
      		for(int j = 1;j <= n;j++)
        		f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
}

int main(){
	//freopen("road.in","r",stdin);
	//freopen("road.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin >> n;
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++){
			cin >> ma[i][j];
			f[i][j] = ma[i][j];
			ans += ma[i][j];
		}
	ans = ans / 2; //由于双向建边所以要除以2
	Floyd();
	memset(vis,0,sizeof(vis));
	
	for(int i = 1;i <= n;i++) 
		for(int j = i;j <= n;j++)
			if(f[i][j] != ma[i][j] || ma[i][j] != ma[j][i]) {cout << -1;return 0;}
	
	for(int k = 1;k <= n;k++)      
        for(int i = 1;i <= n;i++)
            for(int j = i + 1;j <= n;j++)
                if(k!=j && k!=i && i!=j && vis[i][j] == 0 && f[i][j]==f[i][k]+f[k][j])
                    ans -= f[i][j],vis[i][j] = 1; 
	
	cout << ans << '\n';            
	return 0; 
}
```

---

## 作者：foryou_ (赞：1)

难度虚高，建议评橙 / 黄 qwq。

首先我们发现这是一道最短路问题，且 $N \le 300$，于是采取 floyd 算法解决。

具体地，我们分情况分类讨论。令我们当前枚举到的最短路径起点为 $i$，终点为 $j$，中转点为 $k$，输入的矩阵为 $dis$。

- 若 $dis_{i,j}>dis_{i,k}+dis_{k,j}$，则一定无解；

- 若 $dis_{i,j}=dis_{i,k}+dis_{k,j}$，则说明 $i,j$ 最短路无需更新，对答案没有贡献，进行标记；

最后遍历整个 $dis$ 数组，若某条 $i,j$ 最短路未被标记，则令答案累加 $dis_{i,j}$ 即可。

时间复杂度 $O(n^3)$。

---

## 作者：Acerkaio (赞：1)

### [题面](https://www.luogu.com.cn/problem/AT3535)

## 思路：
最短路径。
## 算法实现
我们在这题将要使用 Floyd  算法，至于如何实现，可以先看看[【Clear And Present Danger S】](https://www.luogu.com.cn/problem/P2910)这道板子题。

Floyd 算法是一个基于「贪心」、「动态规划」求一个图中所有点到所有点 最短路径的算法，时间复杂度 $O(n^3)$

重点思想：以每个点为「中转站」，刷新所有「入度」和「出度」的距离。

重点语句（~~扭曲~~）：
```cpp
for(int k=1;k<=n;k++)
		{
			for(int i=1;i<=n;i++)
			{
				for(int j=1;j<=n;j++)
				{
					if(f[i][j]>f[i][k]+f[k][j])
					{
						f[i][j]=f[i][k]+f[k][j];
					}
				}
			}
		}
```
在此题，我们可以利用表 A 使用 Floyd 算法遍历如果 $a_{i,j}=a_{i_k}+a_{k,j}$（其中 i , j 分别为入度和出度 k 是中转点）那就说明表 A 没毛病，标记一下（后面会讲）。

否则“有猫腻”即无解输出 -1 。

Q：为什么要标记呢？

既然相等的话说明出度与入度中间有一个中转点，遍历完了之后只需要统计未被标记的，完事。

# CODE：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int a[9999][9999];
bool b[9999][9999];
signed main()
{	
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			int e;
			cin>>e;
			a[i][j]=e;
		}
	}
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(i!=k&&j!=k&&i!=j)
				{
					if(a[i][j]==a[i][k]+a[k][j])
					{
						b[i][j]=1;
					}
					else
					{
						if(a[i][j]>a[i][k]+a[k][j])
						{
							cout<<-1<<'\n';
							return 0;	
						}
					}
				}
			}
		}
	}
	int maxn=0;
	for(int i=1;i<=n;i++)
	{	
		for(int j=1;j<=n;j++)
		{
			if(!b[i][j])
			{
				maxn+=a[i][j];	
			}
		}
	}
	cout<<maxn/2<<'\n'; //记得无向图要除以二
	return 0;
}
```


---

## 作者：A1C3 (赞：0)

# AT_arc083_b [ABC074D] Restoring Road Network

观察本题数据范围 $ N \le 300$，因此可以使用 Floyd 算法。

对于输入数组 $f$ 进行最短路计算。设途径点为 $k$，起点为 $i$，终点为 $j$，如果发现一组 $(i, j, k)$ 使得 $f_{i, j} > f_{i, k}+f_{k, j}$，则报告无解，输出 -1；如果发现一组 $(i, j, k)$ 使得 $f_{i, j} = f_{i, k}+f_{k, j}$，则从 $i$ 到 $j$ 的最短路没有被更新，将 $(i, j)$ 标记。

最后统计答案，若 $(i, j)$ 未被标记，则答案加上 $f_{i, j}$，输出答案除以 $2$ 即可，因为 $f$ 数组是对称的，答案会被重复算两遍。

细节：在实现 Floyd 的三层循环中，需要特殊判断 $f_{i, j}, f_{i, k}, f_{k, j}$ 均不为 $0$，因为 $0$ 加上任意一个数仍位 $0$，会影响答案的计算；需要开 `long long`。

## AC Code

```cpp
#include <iostream>
using namespace std;
using LL = long long;
const int N = 307;
LL f[N][N];
bool flag[N][N];
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			scanf("%lld", &f[i][j]);
	for (int k = 1; k <= n; ++k)
	for (int i = 1; i <= n; ++i)
	for (int j = 1; j <= n; ++j) {
		if (!f[i][j] || !f[i][k] || !f[k][j]) continue;
		if (f[i][j] > f[i][k]+f[k][j]) return puts("-1"), 0;
		if (f[i][j] == f[i][k]+f[k][j])
			flag[i][j] = true;
	}
	LL ans = 0;
	for (int i = 1; i <= n; ++i)
	for (int j = 1; j <= n; ++j)
		if (!flag[i][j]) ans += f[i][j];
	printf("%lld", ans>>1);
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

# [ABC074D] Restoring Road Network


#### 无解解释

若从城市 $i$ 走到城市 $j$ 道路长度为 $1$，从城市 $j$ 走到城市 $k$ 道路长度为 $1$，所以从城市 $i$ 到城市 $k$ 要走的距离为 $2$，但如果表中是 $A_{i,k},A_{i,k}>2$，那么无解。

#### 题意说明 & 做法

即给出邻接矩阵，存储每两个城市之间的道路的距离。我们跑一遍最短路后，如果发现从 $i$ 到 $j$ 的最短路径 $<A_{i,j}$，那么说明表 $A$ 存在问题，无解。否则如果我们在更新时发现从 $i$ 到 $k$ 再从 $k$ 到 $j$ 的最短路径 $=A_{i,j}$，那么说明从 $i$ 到 $j$ 的最短路径就是从 $i$ 到 $k$ 再从 $k$ 到 $j$ 的最短路径，为了不重复计算，我们就标记 $dob_{i,j}$ 为 $1$，表示不用统计。

最后，由于图是无向图，所以每条有效路径我们都计算了两遍，所以我们的 $ans$ 需要除以 $2$。

#### Code

```C++
#include <bits/stdc++.h>
#define int long long
using namespace std;
int dob[305][305],n,m,s,t,ans,b;
int dis[305][305];
void flyd(){
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				if(i==j||j==k||k==i)continue;
				if(dis[i][j]==dis[i][k]+dis[k][j])dob[i][j]=1;//防止算重
				else if(dis[i][j]>dis[i][k]+dis[k][j]){
					cout<<-1<<endl;exit(0);
				}
//				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
			}
}
signed main() {
	cin>>n;
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			cin>>dis[k][i];
	
	flyd();
	
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++){
			if(!dob[k][i])ans+=dis[k][i];
		}
			
	
	printf("%lld\n",ans/2);
	return 0;
}
```




---

## 作者：I_am_sb___ (赞：0)

此题是一道非常简单的模板小变形，发现竟然 $N \leq 300$，果断直接用 floyd，只需要判断是否有 $dis_{i,,j} < dis_{i,k}+dis_{k,j}$。若有，则明显此图不可以成立，若相等，就需要记录下此条边加入答案中。

注意此题统计的是最短路之和，而给出的边是无向边，则当以上步骤完成统计之后，答案需要减半。

code：
```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

const int N = 307;

int n;
int ans;
int a[N][N];
bool b[N][N];

signed main(){	
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= n; ++ j)
		{
			int x;
			cin >> x;
			a[i][j] = x;
		}
	for(int k = 1 ; k <= n ; ++ k)
		for(int i = 1 ; i <= n ; ++ i)
			for(int j = 1 ; j <= n ; ++ j)
				if(i != k && j != k && i != j)
				{
					if(a[i][j] == a[i][k] + a[k][j]) b[i][j] = true;
					else
					{
						if(a[i][j] > a[i][k] + a[k][j])
						{
							puts("-1");
							return 0;	
						}
					}
	            }
	for(int i = 1 ; i <= n ; ++ i)
        for(int j = 1 ; j <= n ; ++ j)
			if(!b[i][j]) ans += a[i][j];
	cout << ans / 2 << "\n";
	return 0;
}
```

---

## 作者：WaterSun (赞：0)

# 思路

因为 $n \leq 300$，于是可以用 Floyd 算法求解。

我们在跑 Floyd 的过程中，判断一下当前 $g_{i,j}$ 是否与 $g_{i,k} + g_{k,j}$ 相等。

如果相等，用一个 $vis_{i,j}$ 标记一下（不然到时候算答案的时候回算多）；否则，直接输出 `-1`。

最后，枚举 $i,j$，把没有标记过的权值加上即可。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 310;
int n,ans;
int g[N][N];
bool vis[N][N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

signed main(){
	n = read();
	for (re int i = 1;i <= n;i++){
		for (re int j = 1;j <= n;j++) g[i][j] = read();
	}
	for (re int k = 1;k <= n;k++){//Floyd 
		for (re int i = 1;i <= n;i++){
			for (re int j = 1;j <= n;j++){
				if (i != j && i != k && j != k){
					int res = g[i][k] + g[k][j];
					if (g[i][j] == res) vis[i][j] = true;
					else if (g[i][j] > res){
						puts("-1");
						return 0;
					}
				}
			}
		}
	}
	for (re int i = 1;i <= n;i++){//求答案 
		for (re int j = 1;j <= n;j++){
			if (!vis[i][j]) ans += g[i][j];
		}
	}
	printf("%lld",ans >> 1);//无向图要除以 2 
	return 0;
}
```

---

## 作者：_AyachiNene (赞：0)

# 思路：
这道题 $n$ 最大为 $300$，也就暗示我们用弗洛伊德做。如果用弗洛伊德更新时，还可以松弛，说明给的数据是有问题的，输出 $-1$ 即可。如果数据是正确的，我们能发现，有的边是与其他几条边等效的，我们用弗洛伊德更新时，发现有这种边就标记一下，最后的答案就是没被标记的边的权值和。

**注意：边是双向边，答案除以二。**
# Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[114*3][514],ans,vis[1145][1145];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];        //输入 
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				if(a[i][j]>a[i][k]+a[k][j])           //可以进行松弛操作 
				{
					cout<<-1;
					return 0;
				}
				if((a[i][j]==a[i][k]+a[k][j])&&i!=j&&j!=k&&k!=i)       //找到可以有等效的几条边替代的边 
					vis[i][j]=1;
			}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(!vis[i][j])
				ans+=a[i][j];              //统计答案 
	cout<<ans/2;
}
```


---

## 作者：JuRuo_QAQ (赞：0)

一道 Floyd 算法的板子题

Floyd 运用了贪心和动态规划的思想，可以求出一张图中所有点对之间的最短路，复杂度为 $O(n^3)$

本题核心代码如下~~我没有压行~~：
```cpp
for(int i=1;i<=n;i++)
	for(int k=1;k<=n;k++)
		for(int j=1;j<=n;j++)
			if(i!=k&&j!=k&&i!=j){
				if(a[i][j]==a[i][k]+a[k][j]) vis[i][j]=1;
				if(a[i][j]>a[i][k]+a[k][j]){cout<<-1<<endl;return 0;}
			}

```
这里有一个小技巧：循环时中间变量以 i，k，j 的层次顺序，可以加快运行速度，这是因为这对计算机缓存比较友好

~~你问我为什么？我又不是学硬件的我也不知道~~

同时，根据题意，计算最短路时如果 $a_{i,j}=a_{i,k}+a_{k,j}$ 就不用再计算这一条边了（不然会重复），如果 $a_{i,j}=a_{i,k}+a_{k,j}$ 则无解

完整代码：
```cpp
#include<iostream>
#define int long long
using namespace std;
int n,a[310][310],ans;
bool vis[310][310];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++)
		for(int k=1;k<=n;k++)
			for(int j=1;j<=n;j++)
				if(i!=k&&j!=k&&i!=j){
					if(a[i][j]==a[i][k]+a[k][j]) vis[i][j]=1;
					if(a[i][j]>a[i][k]+a[k][j]){cout<<-1<<endl;return 0;}
				}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(!vis[i][j]) ans+=a[i][j];
	cout<<ans/2<<endl;//无向图要除以2
	return 0;
} 

```
这里有一个~~毒瘤~~技巧：将 int 定义为 long long，然后将主函数前的 int 改为 signed

~~岛国题目文末必须输出换行符害我多交了两次~~

双倍经验：[P1119 灾后重建](https://www.luogu.com.cn/problem/P1119)

---

## 作者：REAL_曼巴 (赞：0)

此题的题意是给你一个弗洛伊德的结果，让你还原。

这里就需要对这个算法的意义有很深的了解了。

算法弗洛伊德算法可以求出图中任意两点的最短路，首先枚举松弛操作的中间点，再枚举松弛的左右两个点，可以用邻接矩阵进行操作。

如何还原那？

我们可以在三重循环暴力统计最小边权和时中，进行路径和判断时符合，就可以开一个数组进行标记。最后加和时，直接统计没有被标记过得边即可。

因为是无向图，所以最后要除以二。

```
#include<bits/stdc++.h>
using namespace std;//开long long 
long long n,maxn=0;
long long a[1001][1001],b[1001][1001];
int main(){	
	cin>>n;
	for(long long i=1;i<=n;i++)
		for(long long j=1;j<=n;j++){
			long long opt;
			cin>>opt;
			a[i][j]=opt;
	}
	for(long long k=1;k<=n;k++)
		for(long long i=1;i<=n;i++)
			for(long long j=1;j<=n;j++){
				if(i!=k&&j!=k&&i!=j){
					if(a[i][j]==a[i][k]+a[k][j])b[i][j]=1;
					else{
						if(a[i][j]>a[i][k]+a[k][j]){
							cout<<-1;
							return 0;	
						}
					}
				}
			}
		
	
	for(long long i=1;i<=n;i++)for(long long j=1;j<=n;j++)if(!b[i][j])maxn+=a[i][j];	
	maxn/=2;
    cout<<maxn;
	return 0;
}
```


---

## 作者：让风忽悠你 (赞：0)

[原题](https://www.luogu.com.cn/problem/AT3535)

看不懂题目于是观察样例找规律（

不难发现对于三个点 $i,j,k$，如果 $a_{i,j}=a_{i,k}+a_{k,j}$，则认为 $i,j$ 之间没有直接道路，即计算答案时不加入 $a_{i,j}$。

接下来考虑无解情况，即表出现错误，对于三个点 $i,j,k$，如果出现 $a_{i,j}>a_{i,k}+a_{k,j}$，说明 $a_{i,j}$ 并不是最短路，则无解。

```cpp
#include<cstdio>
#include<algorithm>
#define N 305
#define ll long lnog

using namespace std;

int n;
ll dis[N][N],ans; // 记得开ll 
bool pd[N][N];

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%lld",&dis[i][j]);
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				if(k==j || k==i || i==j) continue;
				if(dis[i][j]==dis[i][k]+dis[k][j])
					pd[i][j]=1; // 判断 i,j 之间是否存在直接道路 
				else if(dis[i][j]>dis[i][k]+dis[k][j]){
					printf("-1"); // 判断是否无解 
					return 0;
				}
			}
				
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(!pd[i][j])
				ans+=dis[i][j]; // 统计答案 
	printf("%lld",ans/2ll); // 由于是无向图所以结果要 /2 
	return 0;
} 
```


---

