# 单向TSP Unidirectional TSP

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=52

[PDF](https://uva.onlinejudge.org/external/1/p116.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA116/8f55250e58c560c3ec06a86150f26e2b1e1f75c6.png)

## 样例 #1

### 输入

```
5 6
3 4 1 2 8 6
6 1 8 2 7 4
5 9 3 9 9 5
8 4 1 3 2 6
3 7 2 8 6 4
5 6
3 4 1 2 8 6
6 1 8 2 7 4
5 9 3 9 9 5
8 4 1 3 2 6
3 7 2 1 2 3
2 2
9 10 9 10```

### 输出

```
1 2 3 4 4 5
16
1 2 1 5 4 5
11
1 1
19```

# 题解

## 作者：sunnyb179 (赞：6)

新手第一次写题解，求大佬给意见！！！
```cpp
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
using namespace std; //用于自动排序 
int x,y;  //存放矩阵长和宽的变量 
struct point	//结构体变量，一个存放位置一个存放大小 
{
	int a,b;
};
point c[5];		//做一个组形式的结构体变量，方便比较 
bool cmp(point m,point n)	//比较大小， 比较两个两之间的大小关系，大小小的优先，大小相等，位置较小优先 
{
	if(m.a<n.a)		//判断值的大小并且返回 
		return true;
	else if(m.a==n.a)	//值相等时比较位置大小并返回 
	{
		if(m.b<n.b)
			return true;
	}
	return false;	
}
int main(int argc, char *argv[]) //下面进入主程序部分 
{
	while(scanf("%d %d",&x,&y)!=EOF)	//这个while用于不断执行程序，直到EOF（end of file）程序结束 
	{
		int q,p,ma[101][101],f=0,rou[101][101]; 
		//创建变量的位置，q p 表示为正在处理的数的坐标（q行 p列），f 为存放最小值答案的变量
		//ma数组为矩阵的存放位置，rou数组为路径的存放位置 
		for (q=0;q<x;q++)	//用于初始化以及定义数组的双层for循环 
			for(p=y-1;p>-1;p--)	//PS:这里数组倒着 
			{
				scanf("%d",&ma[q][p]);//输入矩阵 
				rou[q][p]=-1;	//初始化路径数组 
			}
		f=1e9;				//把结果拟定成一个大数 
		for(p=1;p<y;p++)	//寻找路径开始，动态规划思想，只不过是从相反的方向找（所以前面要把数组反着输入） 
		{					//简单说就是把每列的每个数分为三个三个一组表示能下一列每一格能够走到的地方 
			for(q=0;q<x;q++) //从这三个里面选出一个最小的，加到下一行里面对应的位置上，以此类推直到最后一列 
			{				//最后一行就为每个位置开始的最小值，只要从这里调出最小的值就是最终的答案 
				int q1=q,q2,q3;	//q1,q2,q3分别代表可以走的，中，上，下三个位置 
				if(q1-1<0)		//判断往上走有没有出界限 
					q2=x-1;		//出了的话就换到最后一行 
				else
					q2=q1-1;	//没有出界正常向上移动一行 
				if(q1+1>=x)		//同理判断向下一行 
					q3=0;		//这里出界换成第一行 
				else
					q3=q1+1;
				c[0].a=ma[q1][p-1];  //这里把这三个可以走的路径以及他们的值放入结构体比较 
				c[0].b=q1;	
				c[1].a=ma[q2][p-1];
				c[1].b=q2;
				c[2].a=ma[q3][p-1];
				c[2].b=q3;
				sort(c,c+3,cmp);	//按照上面的方法排序 
				rou[q][p-1]=c[0].b;  //记录一下路径，最小的是第一个，把位置放入答案数组里 
				ma[q][p]+=c[0].a;	// 然后按照动态规划思想把数加到下一行 
			}
		}
		int qqq,ppp,order[y],posi=y-1;	//动态规划结束，开始输出环节，qqq和ppp为输出路径时的坐标，方便区分所以不用p和q ，order数组存最后唯一答案的路径，posi是代表order数组的位置 
		for(q=x-1;q>-1;q--)	//找出最后一列的最小值，并把它的位置记录下来 
		{
			if(ma[q][y-1]<=f)
			{
				qqq=q;			//记录位置 
				f=ma[q][y-1];	//记录大小 
			}
		}
		order[posi]=qqq+1;		//把最后一个位置放入数组最后一个格 
		for(ppp=y-2;ppp>-1;ppp--)//把剩下的路径通过rou数组把路径存进最后的答案里 
		{
			posi=ppp;			//确认最终答案数组位置 
			qqq=rou[qqq][ppp];	//把存放的坐标取出，用来找再上一个坐标 
			order[posi]=qqq+1;	//把坐标存入最终数组 
		} 
		for(posi=y-1;posi>0;posi--)	//最后的输出for循环，按顺序把路径输出 
			printf("%d ",order[posi]);
		printf("%d\n%d\n",order[0],f);	//最后注意格式，不留空格再把最后的值输出 
	}
	return 0;//终于结束咯！！！：） 
}
```

---

## 作者：sss7020 (赞：4)

这题很经典，纪念一下。   
这题显然是一道dp题目，因为不出现环。

$dp(x,y)$表示以$x$行$y$列为起点通向最后一行的最小值。   
剩下的就显然易见了。

$$dp(x,y)=min\{dp((x+1)\%m,y+1),dp(x,y+1),dp((x-1+m)\%m,y+1\}+mp[x][y]$$

可以使用递推完成。

详见代码：

```cpp
#include<iostream>
#include<cstring>//memset
using namespace std;

const int MAXM=10+5,MAXN=100+5,INF=0x7f7f7f7f;
int mp[MAXM][MAXN];
int dp[MAXM][MAXN];
bool G[MAXM][MAXN][MAXM][MAXN];
int m,n;

void p(int x,int y){//经典输出路径方法
	cout<<(y==0?"":" ")<<x+1;//去除每行末尾的1空格
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			if(G[x][y][i][j]&&dp[i][j]==dp[x][y]-mp[x][y]){
				p(i,j);
				return;//寻找结束
			}//如果可以通向，则输出这个。
		}
	}
}

int main(){
	while(cin>>m>>n){
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				cin>>mp[i][j];
		memset(dp,0,sizeof(dp));
		for(int i=0;i<m;i++)
			dp[i][n-1]=mp[i][n-1];
            //最后一列的dp值一定是本身
		memset(G,0,sizeof(G));
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				G[i][j][(i+1)%m][j+1]=1;
				G[i][j][i][j+1]=1;
				G[i][j][(i-1+m)%m][j+1]=1;
			}
		}//确定能通向的点，以便输出路径
		for(int j=n-2;j>=0;j--){
			for(int i=0;i<m;i++){
				dp[i][j]=min(min(dp[(i+1)%m][j+1],dp[i][j+1]),dp[(i-1+m)%m][j+1])+mp[i][j];
			}
		}//根据最后一行开始递推
		int kx,ans=INF;
		for(int i=0;i<m;i++){
			if(ans>dp[i][0]){
				kx=i;
				ans=dp[i][0];
			}
		}//找出最大的
		p(kx,0);
		cout<<endl<<ans<<endl;
	}
	return 0;
} 
```

$THE\ END$

---

## 作者：Kaizyn (赞：4)

~~详情可见紫书P271~~

f[ i ][ j ]表示从[ i, j ]到最后的最小值

nex[ i ][ j ]表示[ i, j ]到下一列的行号(记录路径)

------------

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int Maxm = 10 + 2;
const int Maxn = 100 + 7;
const int INF = 0x7fffffff;

int n, m;
int a[Maxm][Maxn], f[Maxm][Maxn], nex[Maxm][Maxn];

int main()
{
    while(scanf("%d%d", &m, &n) == 2)
    {
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                scanf("%d", &a[i][j]);

        int mini, minv = INF;
        for(int j = n-1; j >= 0; --j)
            for(int i = 0; i < m; ++i)
            {
            	// 最后一列,直接初始化
                if(j == n-1) f[i][j] = a[i][j];
				else 
				{
                	// 初始化为最大值
					f[i][j] = INF;
					nex[i][j] = INF;
                    // 下一步可以达到的三个方向
	                for(int k = -1, row, val; k <= 1; ++k)
		            {
                    	// 这就是我为什么用[0,j-1]了
			            row = (i + k + m) % m;
				        val = a[i][j] + f[row][j+1];
					    if(val < f[i][j])
						{
	                        f[i][j] = val;
		                    nex[i][j] = row;
			            }
                        // 如果有字典序更小的路径,更新
				        else if(val == f[i][j])
					        nex[i][j] = min(row, nex[i][j]);
					}
				}
                // 到第一列了,记录答案
                if(j == 0 && f[i][0] < minv) 
                { 
                	minv = f[i][0]; 
                    mini = i; 
                }
            }
		// 诡异的输出格式
        printf("%d", mini+1);
        for(int j = 1, i = nex[mini][0]; j < n; i = nex[i][j], j++)
            printf(" %d", i+1);
        printf("\n%d\n", minv);
    }
    return 0;
}


```



------------
```cpp
// 紫书的确保字典序方法
int row[3]={i,i-1,i+1};
if (i==1) row[1]=m;
if (i=m) row[2]=1;
sort(row,row+3);
```

------------
WA了无数次，翻阅了无数大佬的AC代码，终于发现列数为1的巨坑数据……

---

## 作者：安静学习 (赞：4)

一个简单的DAG图上的动态规划

算是一个很中规中矩的DAG最短路递归吧，不懂的建议去B站查mit的2011年算法导论的动态来看，直接上代码

dp表示的是当前状态到最后一列的最短路，在每一个可能的结果中取全局的最小值，然后用Next表示当前状态的下一行是往哪里走

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <fstream>
using namespace std;
#define ine 0x3f3f3f3f
const int maxn = 100 + 10;
int ver[maxn][maxn], m, n, dp[maxn][maxn], Next[maxn][maxn]/*当前状态下一行在哪*/;
struct Node{
    int x, y;//下一个结点
};

bool com(Node a, Node b){
    return a.x < b.x;
}

int Dp(int x, int y){//返回当前结点到最后一列的最小值
    if(dp[x][y] != -1){return dp[x][y];}
    if(y == n - 1){//最后一列
        dp[x][y] = ver[x][y];
        Next[x][y] = x;
        return dp[x][y];
    }
    Node a[3];
    a[0].y = y + 1; a[1].y = y + 1; a[2].y = y + 1;
    a[0].x = x;
    a[1].x = (x + 1) % m;
    a[2].x = x - 1;
    if(a[2].x == -1){a[2].x = m - 1;}
    stable_sort(a, a + 3, com);
    int ans = ine, idx = -1;
    for(int i = 0; i < 3; i++){
        if(Dp(a[i].x, a[i].y) < ans){
            ans = Dp(a[i].x, a[i].y);
            idx = i;
        }
    }
    /*cout << x << ' ' << y << endl;
    for(int i = 0; i < 3; i++){
        cout << ' ' << a[i].x << ' ' << a[i].y << endl;
    }*/
    dp[x][y] = ver[x][y] + ans;
    Next[x][y] = a[idx].x;
    return dp[x][y];
}

int main(){
    while(cin >> m >> n){
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                cin >> ver[i][j];
            }
        }
        memset(dp, -1, sizeof(dp));
        memset(Next, -1, sizeof(Next));
        int ans = ine, idx = -1;
        for(int i = 0;i < m; i++){
            if(Dp(i, 0) < ans){
                ans = Dp(i, 0);
                idx = i;//从每行的第一列开始
            }
        }
        cout << idx + 1;
        idx = Next[idx][0];
        int y = 1;
        for(; y < n; idx = Next[idx][y++]){
            cout << ' ' << idx + 1;
        }
        cout << endl;
        cout << ans << endl;
    }
    return 0;
}

```


---

## 作者：CrTsIr400 (赞：2)

似乎发现别的题解代码不够简洁，在下蒟蒻写一篇简洁易懂的题解。

因为 $O(3^{nm})$ 的时间复杂度太大，于是我们考虑 $DP$。

设 $f[i][j]$  为到达第 $i$ 行 $j$ 列的最短路径值，那么根据题目含义，我们可以通过**顺推法**来进行DP。

$(i,j)$ 能转移到 $(i+1,j+1) ||| (i-1,j+1) ||| (i,j+1)$ 这 $3$ 个点。（注意一些边界条件）

因为 dp 要基于最优子决策，于是我们大可证明这是对的。

于是呢？

* $f[i+1][j+1]\to min\{f[i][j]+a[i+1][j+1]\}$;

* $f[i-1][j+1]\to min\{f[i][j]+a[i-1][j+1]\}$;

* $f[i][j+1]\to min\{f[i][j]+a[i][j+1]\}$;

最后的答案和输出路径部分请读者自行思考。

如果仍未有思路，请看下列代码。

```cpp
	int f[11][102],a[11][101],pa[11][101];
	int n,m;
	void init()
	{
		if(!in(n))exit(0);
		in(m);
		for(RI i=1;i<=n;++i)for(RI j=1;j<=m;++j)in(a[i][j]);
		for(RI i=1;i<=n;++i)for(RI j=1;j<=m;++j)f[i][j]=inf,pa[i][j]=0;
	}
	int ls(int x){return x-1<1?n:x-1;}int rs(int x){return x+1>n?1:x+1;}
	void Ppath(int x,int y){if(x==0)return;Ppath(pa[x][y],y-1);printf("%d ",x);}
	int dp(){
		RI ans=1;
		for(RI i=1;i<=n;f[i][1]=a[i][1],++i);
		for(RI j=1;j<m;++j)for(RI i=1;i<=n;++i){
			if(f[i][j]+a[ls(i)][j+1]<f[ls(i)][j+1])
			f[ls(i)][j+1]=f[i][j]+a[ls(i)][j+1],pa[ls(i)][j+1]=i;
			if(f[i][j]+a[rs(i)][j+1]<f[rs(i)][j+1])
			f[rs(i)][j+1]=f[i][j]+a[rs(i)][j+1],pa[rs(i)][j+1]=i;
			if(f[i][j]+a[i][j+1]<f[i][j+1])
			f[i][j+1]=f[i][j]+a[i][j+1],pa[i][j+1]=i;
		} 
		for(RI i=2;i<=n;++i)if(f[ans][m]>f[i][m])ans=i;
		Ppath(pa[ans][m],m-1);printf("%d\n%d\n",ans,f[ans][m]);
	}
	void ANS(){init();dp();}
```

---

## 作者：JK_LOVER (赞：2)

我认为其他题解很不错，但是都不是很明朗，这里再说一下

- 求路径最小值  ->  数字三角形动规
- 输出路径  ->  保留前驱
- 取mod的时候要注意负数

做法不复杂，思维难度不高，处理好逻辑关系就行

下面放代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 10000;
struct node{
	int word;
	int val;
};//便于处理字典序
bool cmp(node xx,node yy)
{
	return xx.val<yy.val||(xx.val == yy.val && xx.word < yy.word);//处理字典序
}
int tu[N][N],dp[N][N],pre[N][N];//分别是原图，dp数组，前驱
int n,m;
int main()
{
	while(scanf("%d %d",&n,&m) == 2)
	{
		memset(pre,-1,sizeof(pre));
		memset(dp,0x3f,sizeof(dp));
		for(int i = 0;i < n;i++)
		{
			for(int j = 0;j < m;j++)
			{
				cin>>tu[i][j];
			}
		}
		for(int i = 0;i < n;i++)
		dp[i][m-1] = tu[i][m-1]; 
		int ans = 0x3f3f3f3f;
		for(int i = m-2;i >= 0;i--)
		{
			for(int j = 0;j < n;j++)
			{
				node next[3] = { (node){(j+1)%n,dp[(j+1)%n][i+1]},(node){j,dp[j][i+1]},(node){(j-1+n)%n,dp[(j-1+n)%n][i+1]} };//可拓展方向
				sort(next,next+3,cmp);	//排个序
				pre[j][i] = next[0].word;
				dp[j][i] = next[0].val + tu[j][i];//转移
			}
		}

		for(int i = 0;i < n;i++)
		{
			ans = min(ans,dp[i][0]);//最小值
		}
		for(int i = 0;i < n;i++)
		{
			if(ans == dp[i][0])//第一个找到的字典序一定最小
			{
				int total = 0,k = i;
				cout<<i+1;
				while(pre[k][total] != -1)
				{
					cout<<" "<<pre[k][total]+1;
					k = pre[k][total];
					total++;
				}
				cout<<endl<<ans<<endl;
				break;
			}
		}
	}
	return 0;
}
```


---

## 作者：fengjack (赞：1)

本蒟蒻语言较贫乏，只好直接上代码了QwQ(代码里有注释--希望能帮大家更好理解)

```
#include<bits/stdc++.h>
using namespace std; 
const int N=12,M=105,inf=0x3f3f3f3f;
int n,m,first,son,road[N][M];
long long dp[N][M],a[N][M];
long long ans,d;//数据太大用long long 

int main()
{
  while(cin>>n>>m)
  {
  memset(dp,0,sizeof(dp));
  memset(road,0,sizeof(road));
  memset(a,0,sizeof(a));
  ans=inf;
  for(int i=0;i<n;i++)
    for(int j=0;j<m;j++)//因为矩阵上下可通,故从0开始,便于取模 
      cin>>a[i][j];
  for(int i=0;i<n;i++)dp[i][m-1]=a[i][m-1];//边界条件 
  for(int j=m-2;j>=0;j--)//倒推(便于记录字典序) 
    for(int i=0;i<n;i++)
    {
      int x[3]={(i-1+n)%n,i,(i+1)%n};//储存行数 
      sort(x,x+3);//排序--为了求字典序(可不用判断是否相等) 
      d=dp[x[0]][j+1],son=x[0];
      for(int k=1;k<3;k++)
      	if(d>dp[x[k]][j+1])
      	  d=dp[x[k]][j+1],son=x[k];//求最小值并记录行数 
	  dp[i][j]=d+a[i][j],road[i][j]=son;
	}
  for(int i=0;i<n;i++)
    if(ans>dp[i][0])
      ans=dp[i][0],first=i;
  cout<<first+1;//注意+1--从0开始 
  for(int i=road[first][0],j=1;j<m;i=road[i][j],j++)
    cout<<" "<<i+1;
  cout<<endl<<ans<<endl;	
  }
  return 0;
}
```


------------
其实这道题也可用DAG做的QwQ

希望大家能对本片题解提出宝贵意见，谢谢！

---

## 作者：我很辣ji看头像 (赞：1)

首先，吐槽一下 
# **为什么你谷更新后我交不了这道题啊啊啊啊，但我确定我是对的啊啊啊**
期末考压力有点儿大所以做一道5秒题放松一下//顺带练英语阅读

再吐槽一下：
为何DALAO们都写辣么长。。。

我的思路是 纯暴力DP走人。
### 注释在代码里我这里就不细讲了

蒟蒻认为这道题本质DP非常简单 
但作为一道UVA，它一如既往地想要在输入输出上卡死众多无 **咕**  的蒟蒻/滑稽
```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,m,a[10010][10010],dp[10010][10010];
int p[10010][10010],ans;
struct node{
	int q,w;
}x[10];//定义结构体 
bool compare(node e,node r){
	//根据题意进行比较 
	if(e.q<r.q){
		return true;
	}
	else if(e.q==r.q){
		if(e.w<r.w) return true;
	} 
	return false;
} 
int back(int y,int u,int o,int yy,int uu,int oo){
	//函数作用：记录当前位置的上一个位置 
	x[0].q = y,x[1].q = u,x[2].q = o;//back函数里前三个变量是前三个方向的数值 
	x[0].w = yy,x[1].w = uu,x[2].w = oo;//后三个变量是前三个方向的下标 
	sort(x,x+3,compare);//排序 
	return x[0].w;
}
//
int main(){
	//ios::sync_with_stdio(false);
	//cin>>n>>m;
	while(scanf("%d%d",&n,&m) != EOF){
		
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin>>a[i][j];
		}
	}
	for(int i=n-1;i>=0;i--) dp[i][m-1] = a[i][m-1];
	//初始化  将最后一列数值录入DP数组 
	for(int j=m-1;j>=0;j--){
		for(int i=0;i<n;i++){
			if(j!=m-1){
				dp[i][j] = min(dp[(i+1+n)%n][j+1],min(dp[(i-1+n)%n][j+1],dp[i][j+1])) + a[i][j];
				//从矩阵右向矩阵左DP 
				p[i][j] = back(dp[(i+1+n)%n][j+1],dp[(i-1+n)%n][j+1],dp[i][j+1],(i+1+n)%n,(i-1+n)%n,i);
				//调用BACK函数记录上一个位置 
			}             
		}
	}
	int ans = dp[0][0];
	int ii = 0;
	for(int i=0;i<n;i++) {
		//ans = ans,dp[i][0]);
	    if(dp[i][0]<ans) {
	    	ans = dp[i][0];
	    	ii = i;
	    	//这个方法好像有个什么名字但我忘了。。。。 
		}
	}
	for(int j=0;j<m;j++){
		//cout<<p[ii][j]<<" ";  TEST一下 
		//以下判断是否符合题意 
		if(j!=m-1) cout<<ii+1<<" ";
		else cout<<ii+1<<endl;
		ii = p[ii][j];
	}
	cout<<ans<<endl; 
}
	return 0;
}
```

---

## 作者：zhowipc (赞：0)

##  _**代码里有注释 **_  


```java
package com.zho.answers;

import java.util.Arrays;
import java.util.Scanner;

public class Puva116 {
    //d[i][j] 表示从格子(i, j)道最后一列的最小开销
    static int[][] d = new int[13][120];
    //地图
    static int[][] a = new int[13][120];
    static int[][] nex = new int[13][120];

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        while (true) {
            int m = input.nextInt();
            int n = input.nextInt();
            //初始化
            for (int i = 0; i < 12; i++)
                for (int j = 0; j < 103; j++)
                    a[i][j] = 0;

                //读入
            for (int i = 0; i < m; i++)
                for (int j = 0; j < n; j++) {
                    a[i][j] = input.nextInt();
                }
            //最小开销
            int ans = Integer.MAX_VALUE;
            int first = 0;
            for (int j = n - 1; j >= 0; j--) { //逆推
                for (int i = 0; i < m; i++) {
                    if (j == n - 1)
                        d[i][j] = a[i][j]; // 边界  最后一列没有下一列
                    else {
                        //下一列的行号
                        int[] rows = {
                                i, i - 1, i + 1
                        };
                        if (i == 0)  //第0行上面是第m-1行
                            rows[1] = m - 1;
                        if (i == m - 1)  //第m-1行下面是第0行
                            rows[2] = 0;
                        //字典序排序  找到最小
                        Arrays.sort(rows);
                        d[i][j] = Integer.MAX_VALUE;//初始化
                        for (int k = 0; k < 3; k++) {
                            //当前列和下一列的（右走，右上，右下）比较出最小值
                            int v = d[rows[k]][j + 1] + a[i][j];
                            if (v < d[i][j]) {
                                d[i][j] = v;
                                nex[i][j] = rows[k];//储存最小值的下一列的行号
                            }
                        }

                    }
                    //到达第一列   判断出最小开销
                    if (j == 0 && d[i][j] < ans) {
                        ans = d[i][j];
                        first = i; //存储最小开销的行号
                    }
                }
            }
            System.out.print(first + 1 + " "); //输入第一列的行号

            //  i = nex[first][0] -> 第二列的行号  i表示下一列的行号
            //i = nex[i][j]  nex[i][j] i表示第几行  j表示第几列  表示第i行第j列的下一列的行号
            for (int i = nex[first][0], j = 1; j < n; i = nex[i][j], j++) {
                System.out.print(i + 1 + " ");
            }
            System.out.println();
            System.out.println(ans);
        }
    }
}

```


---

## 作者：Daniel_7216 (赞：0)

大致思路：

首先，这是一个 DP 题（废话）。对于走到第 $j$ 列的阶段，我们有三种决策，即直行、右上、右下。边界是对于右边界，最小开销就是当前格的数字，其余格子的状态转移方程是：
```cpp
dp[i][j] = min(dp[line[k]][j + 1] + a[i][j], dp[i][j]);
```
表示走到 $i$ 行 $j$ 列的最小开销。其中 $a_{i,j}$ 表示 $i,j$ 上的数字， $line_k$ 表示当前可以走到的行号，由于题目中要求字典序最小，所以要对所有可以走到的行号在每一次决策前排序。其余细节部分看蒟蒻的代码吧，代码丑勿喷。
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int INF = 100001;
int a[10][100], dp[10][100];
int line[3], tmp, ans[10][100];
int n, m;
int main() {
	while (scanf("%d%d", &m, &n) != EOF) {
		int tmp_ans = INF;
		int first_line = 0;
		for (int i = 0; i <= m; i++) {
			for (int j = 0; j <= n; j++) {
				scanf("%d", &a[i][j]);
			}
		}
		for (int j = n - 1; j >= 0; j--) {
			for (int i = 0; i < m; i++) {
				if (j == n - 1) {
					dp[i][j] = a[i][j];
				} else {
					line[0] = i - 1;
					line[1] = i;
					line[2] = i + 1;
					if (i == m - 1) line[2] = 0;
					if (i == 0) line[0] = m - 1;
					sort(line, line + 3);
					dp[i][j] = INF;
					for (int k = 0; k < 3; k++) {
						tmp = dp[line[k]][j + 1] + a[i][j];
						if (tmp < dp[i][j]) {
							dp[i][j] = tmp;
							ans[i][j] = line[k];
						}
					}
				}
				if (j == 0 && dp[i][j] < tmp_ans) {
					first_line = i;
					tmp_ans = dp[i][j];
				}
			}
		}
		printf("%d", first_line+1);
        for (int j = 1, i = ans[first_line][0]; j < n; i = ans[i][j], j++){
        	printf(" %d", i + 1); 
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：mureZ (赞：0)

此题是多段图最短路的经典例题
只要逆推就可以了

其实感觉和数字三角形有点像，就是数字三角形的扩展

直接上代码
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int a[11][101],d[11][101],next[11][101];
const int INF = 0xfffff;	//最大值设置
int first;	//记录最小字典序的值
int main(){
    int n,m;
    while (!cin.eof()){	//输入判断循环
        cin>>m>>n;
        int ans=INF;	//初始化答案
        for (int i=1;i<=m;i++)
            for (int j=1;j<=n;j++)
                cin>>a[i][j];	//输入
        for (int j=n;j>0;j--){	//根据DP思想，我们要逆推
            for (int i=1;i<=m;i++){
                if (j==n) d[i][j]=a[i][j];	//边界条件判定
                else {
                    int row[3]={i,i-1,i+1};	//方向数组
                    if (i==1) row[1]=m;	//边界判定
                    if (i=m) row[2]=1;	//边界判定
                    sort(row,row+3);	//因为在边界地区的字典序不同所以需要排序重新生成最小字典序
                    d[i][j]=INF;	//DP初始化
                    for (int k=1;k<3;k++){
                        int v=d[row[k]][j+1]+a[i][j];
                        if (v<d[i][j]) d[i][j]=v,next[i][j]=row[k];	//DP核心
                    }
                }
                if (j==1&&d[i][j]<ans) ans=d[i][j],first=i;
            }
        }
        cout<<first<<endl;
        for (int i=next[first][1],j=1;j<=n;i=next[i][j],j++)
            cout<<i<<" ";
        cout<<endl; 
    }
    return 0;	//完美结束
} 
```
搬运自紫薯P271

---

