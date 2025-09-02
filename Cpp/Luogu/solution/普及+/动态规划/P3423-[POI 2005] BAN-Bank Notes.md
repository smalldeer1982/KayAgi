# [POI 2005] BAN-Bank Notes

## 题目描述

`Byteotian Bit Bank(BBB)` 拥有一套先进的货币系统，这个系统一共有 $n$ 种面值的硬币，面值分别为 $b_1,b_2,\cdots,b_n$。但是每种硬币有数量限制，现在我们想要凑出面值 $k$，求最少要用多少个硬币。数据保证 $k$ 可以被凑出。

## 说明/提示

对于 $100\%$ 的数据，$1 \le n \le 200$，$1 \le b_1 < b_2 < \cdots < b_n \le 2 \times 10^4$，$1 \le c_i \le 2 \times 10^4$，$1 \le k \le 2 \times 10^4$。

## 样例 #1

### 输入

```
3
2 3 5
2 2 1
10```

### 输出

```
3
1 1 1```

# 题解

## 作者：jiangby (赞：35)

看到这一道题其实很容易就看出了第一问的做法就是多重背包，然后第二问要求输出方案，那么我们很容易就会想到DP要输出方案，很简单的一个方法就是保存当前的状态从哪里转移过来的，然后倒着输出就可以了，就做一个数组d，来保存怎么转移的，很多的dp输出方案都可以用类似的方法输出，不知道的同学可以试一下。
```
其中d[i][j]表示状态为f[i][j]时，是由f[i-1][d[i][j]]转移过来的
void print(int x,int y){
	if(!x)return;
	print(x-1,d[x][y]);
	printf("%d ",(y-d[x][y])/w[x]);
}
```

普通的直接多重背包对于这一道题明显会超时，所以我们应该使用优化算法。多重背包一共两种优化（我所知道的），二进制优化和单调队列优化。一般来说用二进制优化是比单调队列快一点的，因为单调队列常数比较大，但如果用二进制优化的话个人感觉不怎么方便统计如何转移过来的，所以我在这一题选择了单调队列优化，使用单调队列优化的话统计如何转移就可以非常简单做出来了。如果你不懂如何单调队列优化我推荐一篇博客，个人感觉讲得不错。

https://blog.csdn.net/sinat_34943123/article/details/52857327

这是我昨天晚上看到这题，当场学单调队列优化真正把我看懂的一篇博客。也感谢这一位dalao的博客，没有这篇博客我肯定过不了这题

代码如下
```
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<queue>
#include<vector>
#include<deque>
#include<set>
#include<map>
#define N 20005
using namespace std;
struct Node{
	int x,y;
}q1[N],q2[N];
int n,m,w[N],c[N],f[N],d[205][N];
int head1,head2,tail1,tail2;
void print(int x,int y){//打印方案 
	if(!x)return;
	print(x-1,d[x][y]);
	printf("%d ",(y-d[x][y])/w[x]);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&w[i]);
	for(int i=1;i<=n;i++)	
		scanf("%d",&c[i]);
	scanf("%d",&m);
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(int i=1;i<=n;i++){//单调队列优化背包 
		for(int j=0;j<w[i];j++){
			head1=head2=1;
			tail1=tail2=0;
			for(int k=j,cnt=0;k<=m;cnt++,k+=w[i]){
				int xx=k/w[i];
				if(tail1-head1==c[i]){
					if(q1[head1].x==q2[head2].x)
						head2++;
					head1++;
				}
				int t=f[k]-cnt;
				q1[++tail1].x=t,q1[tail1].y=k;
				while(head2<=tail2&&t<q2[tail2].x)
					tail2--;
				q2[++tail2].x=t,q2[tail2].y=k;
				f[k]=q2[head2].x+cnt;
				d[i][k]=q2[head2].y;
			}
		}
	}
	printf("%d\n",f[m]);
	print(n,m);
	return 0;
}



```

PS：

1.本来我想用单调队列后，想直接看题解怎么做的单调队列，以此来学习，但题解里只有二进制优化的做法，我又没怎么看懂，就自己学，学了写这篇题解帮助一下和我一样的同学。

2.个人认为讲得比较清楚，但是平常不管是文化课还是竞赛给别人讲题基本别人听不懂。若有不懂可以私聊，我尽量回复。

3.祝NOIP2018 RP++

---

## 作者：我要考北大 (赞：19)

感觉难度是提高-的水题


如果用下面这个方法的话

f[i]表示凑出i元需要的最少硬币数量

g[i][j]表示凑出i元，第j种硬币（题目给的硬币）用了多少枚


a[i]表示第i种硬币的大小

b[i]表示第i种硬币的数量


容易想出来：
-

i元一定是由n种硬币中选一个
和其它已经表示出来的元组成
就是i=（a[j]） + （i-a[j]）

这并不意味着在表示i元时第j种硬币只用了1枚

有可能i-a[j]元里面有好多枚第j种硬币



如果i元可以用含第j种硬币表示

那么i-a[j]元一定可以被表示

因为i-a[j]元就是i元扔掉一枚第j种硬币

f[i]=min(f[i],f[i-a[j]]+1)

在转移时要比i-a[j]元用的所有硬币情况转移给i元

用这个要有条件
1. i-a[j] > 0 

2. 用的第j种硬币数量不超过b[j]

g[i-a[j]][j]+1<=b[j]


```cpp
#include<bits/stdc++.h>
using namespace std;
int g[20001][201];
int f[20001];
int n;
int a[201],b[201],k;
int main()
{
 #ifndef ONLINE_JUDGE
	freopen("cin.txt","r",stdin);
//	freopen("cout.txt","w",stdout);
	#endif

	scanf("%d",&n);
	int minn=0x3f3f3f3f;
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),f[a[i]]=1,g[a[i]][i]=1,minn=min(minn,a[i]);//初始化 
	for(int i=1;i<=n;i++)scanf("%d",&b[i]);
	scanf("%d",&k);
	
	for(int i=minn+1;i<=k;i++)//比minn小的一定表示不了 
	{
		for(int j=1;j<=n;j++)
		{
			if(i-a[j]>0&&g[i-a[j]][j]+1<=b[j]&&f[i-a[j]]+1<f[i])
			{
				f[i]=f[i-a[j]]+1;
				for(int jj=1;jj<=n;jj++)g[i][jj]=g[i-a[j]][jj];//转移情况 
				g[i][j]=g[i-a[j]][j]+1;
			}
		}
	}
	
	printf("%d\n",f[k]);
	for(int j=1;j<=n;j++)
	{
		printf("%d ",g[k][j]);
	}
}
```




---

## 作者：namespace_std (赞：18)

### 引言(void)

      {

              这道题可真是毒瘤······

              其实式子都不难推，关键是方案（废话）

              将物品拆包（二进制拆分），然后转化为传统背包dp求方案数

              下面用：
              
              m来表示要凑的钱数；
              
              v[i]来表示第i个包的金币数；
              
              w[i]来表示第i个包的金币价值；
              
              k[i]来表示第i个包的金币面值编号；
              
              dp(i)[j]为选前i个包，组成j元钱的方案数（此处可以滚动数组，并倒序枚举，即省略i这一维）。

              根据DP基本素养易知

                  dp([i])[j]=min(dp([i-1])[j],dp([i-1])[j-w[i]]+v[i]);

              第一问答案显然是dp[m]

              然而，怎么记录转移状态呢？

              显然是用from记转移点

              然而一维的from似乎不行（自己试试就知道了）

              然后开始狂M不止······

      }

### ~~二维int from[ ][ ]被卡M了(0pts)~~

      {

              233（没什么可说的）

      }

### ~~二维short from[ ][ ]被卡M了(85pts)~~

      {

              用from[i][j]来记录dp[i][j]处为取得最优解应先选取的包

              易知这个数只会在[1,200*16]，即[1,3200]之间

              所以用short存显然可以

              由此，可以推出式子

                  from[i][j]=i (在(i,j)处转移)

                  from[i][j]=from[i-1][j] (在(i,j)处不转移)

              于是代码华丽丽地亮相了
              
              
              由于我一般代码习惯驱使我把j写成ii，然后我还不想修改了，就苟且吧

                  #include<cstdio>
                  #include<cstring>
                  #define min(x,y) (x<y?x:y)
                  struct bag
                  {
                      int v,w,k;
                  }b[3000];int tot;
                  inline void buildbag(int v,int w,int k)
                  {b[++tot]=(bag){v,w,k};}
                  int dp[20000],n,m,v[20000],c;
                  short from[3000][20000],sum[20000];
                  int main()
                  {
                      memset(dp,0x3f3f3f3f,sizeof(dp));
                      dp[0]=0;
                      register int i,ii;
                      scanf("%d",&n);
                      for(i=1;i<=n;i++)
                          scanf("%d",&v[i]);
                      for(i=1;i<=n;i++)
                      {
                          scanf("%d",&c);
                          for(ii=1;c>=ii;c-=ii,ii<<=1)
                              buildbag(ii,ii*v[i],i);
                          if(c)buildbag(c,c*v[i],i);
                      }scanf("%d",&m);
                      for(i=1;i<=tot;i++)
                          for(ii=m;ii>=0;ii--)
                          {
                              if(ii<b[i].w)
                              {
                                  from[i][ii]=from[i-1][ii];
                                  continue;
                              }
                              int s=dp[ii-b[i].w]+b[i].v;
                              if(s<dp[ii])
                                  from[i][ii]=ifrom[i][ii]=i,dp[ii]=s;
                              else from[i][ii]=from[i-1][ii];
                          }
                      printf("%d\n",dp[m]);
                      int s=m;
                      for(i=tot;dp[m];)
                      {
                          int t=from[i][s];
                          dp[m]-=b[t].v,sum[b[t].k]+=b[t].v;
                          i=t-1,s-=b[t].w;
                      }
                      for(i=1;i<n;i++)
                          printf("%d ",sum[i]);
                      printf("%d\n",sum[n]);
                  }
                  
              然后我们交上去发现只有85分

              再回去一看，memory limit = 64 MB , orz！

              于是这显然不行（新评测姬内存消耗普遍增大了|%_%|）

              于是继续优化······

      }

### 正解(accepted)

      {

              我们做到这里可能会发现

                  from[i][j]=i;

              这一语句告诉我们，from[i][j]一定在更新时取i

              似乎发现了什么？？？？

              没错，那还留from[i][j]的具体值有何用？？？我们不再需要具体数字，只需要记录是否发生了转移！

              所以······我们的from就变成了bool式的

              只需要在转移时打上标记即可

              所以？？？ 就没有所以了啊

              本题至此得到了完美的解决

              即用

                  from[i][j]=1 (在(i,j)处转移)

                  from[i][j]=0 (在(i,j)处不转移)

              来表示转移

              初始化i为包数，j为m
              
              每次循环i--,from[i][j]=1时统计答案（sum[k[i]]+=v[i]）然后跳j（j-=w[i]）
              
              预估时间复杂度O(3000*20000)，空间复杂度O(3000*20000)，可以通过此题（实测487ms/19.35MB）

              下面拿出代码来

                  #include<cstdio>
                  #include<cstring>
                  #include<cstdlib>
                  #define min(x,y) (x<y?x:y)
                  struct bag
                  {
                      int v,w,k;
                  }b[3201];int tot;
                  inline void buildbag(int v,int w,int k)
                  {b[++tot]=(bag){v,w,k};}
                  int dp[20001],n,m,v[20001],c,sum[20001];
                  bool from[3201][20001];
                  int main()
                  {
                      memset(dp,0x3f3f3f3f,sizeof(dp));
                      dp[0]=0;
                      register int i,ii;
                      scanf("%d",&n);
                      for(i=1;i<=n;i++)
                          scanf("%d",&v[i]);
                      for(i=1;i<=n;i++)
                      {
                          scanf("%d",&c);
                          for(ii=1;c>=ii;c-=ii,ii<<=1)
                              buildbag(ii,ii*v[i],i);
                          if(c)buildbag(c,c*v[i],i);
                      }scanf("%d",&m);
                      for(i=1;i<=tot;i++)
                          for(ii=m;ii>=b[i].w;ii--)
                          {
                              int s=dp[ii-b[i].w]+b[i].v;
                              if(s<dp[ii])
                                  from[i][ii]=1,dp[ii]=s;
                          }
                      printf("%d\n",dp[m]);
                      int s=m,k=dp[m];
                      for(i=tot;k;)
                      {
                          while(!from[i][s])i--;
                          k-=b[i].v,sum[b[i].k]+=b[i].v,s-=b[i--].w;
                      }
                      for(i=1;i<n;i++)
                          printf("%d ",sum[i]);
                      printf("%d\n",sum[n]);
                  }
           
             //congratulations! You have got another AC!
      }
### $\color{red}\texttt{  P.S. 楼主写题解不容易，请勿ctrl+c*ctrl+V，尊重楼主的劳动成果}$

---

## 作者：CuBernie (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/P3423)

观察一下题目，发现此题具备背包的基本条件，具体如下：物品数量为$\ n\ $ ，背包体积为$\  k\  $，物品体积为$\ b_i\ $，物品数量为$\ c_i\ $。

思路一：**普通** DP 。

式子：$\ F_{i,j}=\min(f_{i,j},f_{i-1,j-b_i\times k})\ $ ，此时 $\ k \leq  \min(c_i, \left \lfloor \dfrac{m}{b_i} \right \rfloor)\ $。但这是 $\ O(n^2)\ $ 的 DP，在此题的数据范围下是会 $\ TLE\ $ 的。

这时候就要请出**单调队列**来优化它了。

思路二：**单调队列**优化 DP 。

单调队列，重在**单调**和**队列**。

单调，指的是队列内元素的**递增**或**递减**，但我认为是队列内的元素**保证合法**（如果不对请轻点打）。队列，指的是只能在**队头**和**队尾**对元素进行操作。综上所述，单调队列就是保留合法的状态，去除不合法的状态，再由此阶段的合法状态得出下一阶段的状态。

最后，题目还要求输出方案。我们可以使用 DFS 。我们可以用 $\ num_{i,j}\ $ 表示当选用第 $\ i\ $ 个硬币时，想要让重量为 $\ j\ $ 最少需要几个硬币，然后从 $\ num_{n,m}\ $ 开始，减去此时所使用的硬币数量乘硬币重量，得到上一个硬币使用后所得到的总重量就好了，当查询到第 $\ 0\ $ 个硬币时返回即可。

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m,h,r,w[205],c[205],g[20005],q[20005],f[20005],num[205][20005];
void output(int x,int y) {
	if(!x) {
		return;
	}
	output(x-1,y-num[x][y]*w[x]);
	cout<<num[x][y]<<" ";
}
int main() {
    memset(f,63,sizeof(f));//初始化 
    f[0]=0;
    cin>>n;
    for(int i=1; i<=n; i++) {
        cin>>w[i];
    }
    for(int i=1; i<=n; i++) {
        cin>>c[i];
    }
    cin>>m;
    for(int i=1; i<=n; i++) {//枚举各个硬币 
        for(int b=0; b<w[i]; b++) {//b表示小于第i个硬币的重量
            h=1;
            r=0;
            for(int k=0; k<=(m-b)/w[i]; k++) {//此时使用了k个硬币
                while(h<=r&&b+k*w[i]-q[h]>c[i]*w[i]) {//超过k个硬币的移出队列 
                    h++;
                }
                while(h<=r&&g[r]>=f[b+k*w[i]]-k) {//重量相同时大于等于k个硬币的同样移出队列 
                    r--;
                }
                r++;
                q[r]=b+k*w[i];//更新重量 
                g[r]=f[b+k*w[i]]-k;//更新最小使用数 
                f[b+k*w[i]]=g[h]+k;//更新最小使用数 
                num[i][b+k*w[i]]=(q[r]-q[h])/w[i];//储存DFS需要用到的路径
            }
        }
    }
    cout<<f[m]<<endl;
    output(n,m);
    cout<<endl;
    return 0;
}
```

---

## 作者：smallpeter (赞：4)

感觉这题就是一个简单的背包。题面已经够简洁的了，可以直接去看题面。

# 思路

给你 $b_x$ 个硬币，每个硬币的价值为 $a_x$，要凑出的数为 $k$，不难发现这种价值的硬币你最多使用 $\min(\lfloor \dfrac{k}{a_x} \rfloor,b_x)$ 个。这题最坏情况下第 $i$ 种硬币选的上限为 $\lfloor \dfrac{k}{a_i} \rfloor$，且 $a_1$ 到 $a_n$ 为 1 到 $n$ 的任意排列。那么经过处理后最多有
$$ \lfloor \dfrac{k}{a_1} \rfloor+\dots\lfloor \dfrac{k}{a_x} \rfloor+\dots\lfloor \dfrac{k}{a_n} \rfloor=\lfloor \dfrac{k}{1} \rfloor+\dots\lfloor \dfrac{k}{x} \rfloor+\dots\lfloor \dfrac{k}{n} \rfloor\approx k\lg(k)$$

个硬币可以选择，再加上枚举当前选到了第几个硬币的复杂度，总复杂度就是 $O(n k\lg(k))$，~~吸个氧就~~能通过本题。

# 细节

本题~~毒瘤的~~要求出方案，于是我们要记录当前状态下选了几个硬币，最后再倒推每个硬币用了几次。

# 代码
```
#include<bits/stdc++.h>
using namespace std;

const int N=2e2+10,M=2e4+10,INF=1e9;

int n,a[N],b[N],k,g[N][M],f[N][M],ans[N];
//f_{i,j} 表示前 i 种硬币凑出 j 最少要用多少硬币，g_{i,j} 表示表示前 i 种硬币凑出 j 第 i 种硬币要选几个 
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) scanf("%d",&b[i]);
	scanf("%d",&k);
	for(int i=1;i<=n;i++){
		b[i]=min(b[i],k/a[i]);//处理出每个硬币最多合理使用多少次
	}
	for(int i=0;i<N;i++) for(int j=0;j<M;j++) f[i][j]=INF;
	for(int l=0;l<=b[1];l++){
		f[1][l*a[1]]=l;
		g[1][l*a[1]]=l;
	}
	for(int i=2;i<=n;i++){
		for(int j=0;j<=k;j++){
			for(int l=0;l<=b[i];l++){
				if(l*a[i]<=j){
					if(f[i-1][j-l*a[i]]+l<=f[i][j]){
						f[i][j]=f[i-1][j-l*a[i]]+l;
						g[i][j]=l;
					}
				}
			}
		}
	}
	printf("%d\n",f[n][k]);
	int l=k;
	for(int i=n;i>=1;i--){
		ans[i]=g[i][l];
		l-=g[i][l]*a[i];
	}
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);
}
```

感觉这么做不如楼上几位大佬的，但也能通过本题了。

---

## 作者：king_xbz (赞：3)

# 前言
题解区大佬们的单调队列优化以及二进制优化的题解本萌新一个都看不懂。对输出路径的方法也不是很清晰。所以我就自己研究发一篇给像我一样的萌新提供帮助。
# 思路
这题乍一看可能没有头绪，但仔细一想好像和[货币系统](https://www.luogu.com.cn/problem/P5020)又几分相似。
我们可以设物品件数为n，背包体积为k，每件物品体积为1（1个硬币）,每件物品价值为$b_i$,每件物品数量$c_i$

那么，**就将问题转化为了多重背包**。

众所周知，裸的多重背包的时间复杂度是$O(nmk)$，状态转移方程为：
$f_{j}=max(f_{j-w{i}}+v_i)$。放在这道题显然是过不了的。那么我们就需要考虑优化。

**怎么优化**？将一件物品可以选多次转化为多件物品，每件物品只能选一次，这样就压掉了一重循环！

**怎么转化**？使用二进制拆分的原理即可。

举个例子：`3,9,6`（体积，价值，数量）

拆成$3×2^0，3×2^0$，剩余数量为5

$3×2^1，9×2^1$，剩余数量为3

下面c小于2^2,拆不成2进制了，直接拆c清零

$3×3，9×3$剩余数量为0

这样就被拆成了3件不同的物品。

这种用2的幂次方来表示物品的方式就叫做二进制拆分。

代码：
```cpp
int main()
{
	int n,W;
	cin>>n>>W;
	int a,b,c;
	int cnt=0;
	for(fint i=1;i<=n;i++)
	{
		cin>>a>>b>>c;
		for(fint j=1;j<=c;j<<=1)
		v[++cnt]=j*a,w[cnt]=j*b,c-=j;
		if(c)
		v[++cnt]=c*a,w[cnt]=c*b;
	}
	for(fint i=1;i<=cnt;i++)
	for(fint j=W;j>=w[i];j--)
	f[j]=max(f[j],f[j-w[i]]+v[i]);
	cout<<f[W];
	return 0;
}
```
（别抄，不是这道题的代码doge）

背包问题处理完了，我们该研究一下对路径的输出了。这个路径显然不能像图论一样通过记录pre结点输出。那么怎么办呢？**DFS**！

我们在更新的使用用vis数组记录物品件数和选择的数量，然后再DFS过程中递归找到被记录得到路径，记下此时物品种类以及件数。

代码：
```cpp
for(fint i=1;i<=n;i++)
for(fint j=m;j>=w[i];j--)
for(fint k=v;k>=zu[i];k--)
if(f[j-w[i]][k-zu[i]]+t[i]>f[j][k])
f[j][k]=f[j-w[i]][k-zu[i]]+t[i],vis[i][j][k]=1;
inline void dfs(int n,int m,int v)
{
	if(vis[n][m][v])
	{
		if(n==1)
		cout<<1<<" ";
		else
		m-w[n]>=0&&v-zu[n]>=0?dfs(n-1,m-w[n],v-zu[n]):dfs(n-1,m,v),cout<<n<<" ";
		return ;
	}
	if(n==1)
	return ;
	if(!vis[n][m][v])
	dfs(n-1,m,v);
	return ;
}
```
(仍然是别的题的代码)

注意，由于我们此前在二进制拆分时把许多物品给变成别的物品了，所以我们要先记录物品的原归属。
# 代码实现
```cpp
int main()
{
	cin>>n;
	for(fint i=1;i<=n;i++)
	cin>>val[i];
	for(fint i=1;i<=n;i++)
	cin>>num[i];
	int k;
	cin>>k;
	for(fint i=1;i<=n;i++)
	{
		for(fint j=1;j<=num[i];j<<=1)
		v[++cnt]=j*val[i],w[cnt]=j,jin[cnt]=i,num[i]-=j;
		if(num[i])
		v[++cnt]=num[i]*val[i],w[cnt]=num[i],jin[cnt]=i,num[i]=0;
	}
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(fint i=1;i<=cnt;i++)
	for(fint j=k;j>=v[i];j--)
	if(f[j-v[i]]+w[i]<f[j])
	f[j]=f[j-v[i]]+w[i],vis[i][j]=1;
	cout<<f[k]<<endl;
	dfs(k);
	return 0;
} 

inline void dfs(int x)
{
	if(x==0)
	{
		for(fint i=1;i<=n;i++)
		cout<<ans[i]<<" ";
		exit(0);
	}
	while(!vis[cnt][x]&&cnt)
	cnt--;
	x-=v[cnt],ans[jin[cnt]]+=w[cnt];
	cnt--;
	dfs(x);
	return ;
}
```
别走，还有下文！
# 题目推荐
二进制优化背包问题：[宝物筛选](https://www.luogu.com.cn/problem/P1776)
[樱花](https://www.luogu.com.cn/problem/P1833)

背包路径记录问题：[通天之潜水](https://www.luogu.com.cn/problem/P1759)

最后祝大家AC愉快哦！

---

## 作者：ThinkofBlank (赞：3)

​	本题有两个问，**第一个是求最少硬币数，第二个则是求方案**(翻译竟然没写。。。)。

​	首先，我们来解决第一问。

​	我们可以很容易想出，这是一个dp，我们设dp[i]表示凑出面值i最少需要多少个硬币，然后打个多重背包就好了。。。于是你就T了。。。

​	对于多重背包，我们通常使用一种手段:**二进制拆分**(听说还可以使用单调队列优化,但是本弱鸡并不会。。。QwQ)

​	二进制拆分，它的原理是:**任何一个数都可以用2^0^,2^1^,2^2^...2^k^表示(每个最多取1个)**。

​	于是，对于一个物品的个数C，我们把它成:C=2^0+2^1+2^2...+2^k+X(X<2^(k+1)),这我们就能表示0-C的所有数，然后，我们跑一遍01背包就好了,对于一个物品，它拆分出的物品中，被选的物品所代表的个数之和即是这个物品被选了几个。

​	复杂度O(nklog(n))，于是,我们成功切掉了第一问。。。

​	那么，重要的是第二问了。。。

​	**某dalao曰:最优美的算法是用的暴力还能A题。**

​	于是，我们就考虑使用**dfs**来解决此题

​	首先，我们把问题转化成了01背包，那么我们我们就需要知道：**我们选了哪些数**，我们怎么解决呢？

​	首先我们设每个物品的参数:B[i]->面值，C[i]->对答案的影响值(其实就是二进制拆分时拆出来的物品个数)，D[i]->由哪个物品拆出来的。

​	我们假设，现在我们要知道面值x可以由哪些物品组合出来，那么，我们知道，要选择物品i的话，**其必要条件是:x>=B[i]并且dp[x-B[i]]+C[i]==dp[x]。**于是我们就可以用dfs来枚举选哪些物品了。

​	代码:
```cpp
//#pragma GCC optimize()//手动Ox优化
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+1,M=2600001;
int dp[N],b[N],c[N];
int B[M],C[M],D[M];
int ti[N];
bool vis[N];
int e;int n;
inline void dfs(int x){
    if(!x){
        for(int i=1;i<=n;++i){
            printf("%d ",ti[i]);
        }
        exit(0);//找到一种方案后，输出，然后直接强制结束程序
    }
    for(int i=1;i<=e;++i){
        if(vis[i]||B[i]>x){//如果被选过了，或者超出了，则不选 
            continue;
        }
        if(dp[x]==dp[x-B[i]]+C[i]){//如果可以选 
            vis[i]=1;
            ti[D[i]]+=C[i];//第D[i]个选上C[i]个 
            dfs(x-B[i]);
            ti[D[i]]-=C[i];
            vis[i]=0;
        }
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=n;++i){
        scanf("%d",&c[i]);
        for(int k=0;k<=13;++k){//二进制拆分 
            if(c[i]>=(1<<k)){
                B[++e]=(1<<k)*b[i];
                C[e]=(1<<k);
                D[e]=i;
                c[i]-=(1<<k);
            }else{
                break;
            }
        }
        if(c[i]){//处理剩余的 
            B[++e]=c[i]*b[i];
            C[e]=c[i];
            D[e]=i;
        }
    }
    memset(dp,0x3f3f,sizeof(dp));//初始化 
    dp[0]=0;
    int v;
    scanf("%d",&v);
    for(int i=1;i<=e;++i){
        for(int j=v;j>=B[i];--j){
            dp[j]=min(dp[j],dp[j-B[i]]+C[i]);
        }
    }
    printf("%d\n",dp[v]);
    dfs(v);
    return 0;
}	
```

这个代码吸氧可过，不吸氧的话，不清楚，大家可以试验下。。。

不过，这明显不是我们希望的效果。

那么，我们可以考虑**优化**，怎么优化呢？

我提出一种思路:

我们把所有满足:dp[v-B[i]]+C[i]==dp[v]的物品叫做v的可行物品。

我们想下，为什么不是所有可行物品可以被选择。

理由是:对于物品i，他会对dp[v],与dp[v-B[i]]的结果同时造成影响。也即是说，有可能v-B[i]的可行物品中有i，v中又有i，那么i就被选了两次！

那么，我们就可以推出:必选物品的条件:

一个物品必定被选，就相当于，该物品是可行物品且选两个该物品后就会错误或者无法选两个，即:

v>=B[i]并且dp[v]==dp[v-B[i]]+C[i],且:

v>=2B[i],dp[v-2B[i]]+2C[i]!=dp[v]或者v<2B[i]

那么，我们把所有必选的物品选了，再去dfs，就会快上许多，当然，我们可以重复这个过程直到没有关于现在体积的必选物品为止。

代码:

```cpp
//pragma GCC optimize()//手动Ox优化
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+1,M=2600001;
struct node{
	int B,C,D;
}t[N];
int dp[N],b[N],c[N];
int B[M],C[M],D[M];
int ti[N];
bool vis[N],vit[N];
int e,n,cnt;
inline void dfs(int x){
	if(!x){
		for(int i=1;i<=n;++i){
			printf("%d ",ti[i]);
		}
		exit(0);
	}
	for(int i=1;i<=cnt;++i){
		if(!vit[i]&&dp[x-t[i].B]+t[i].C==dp[x]){
			vit[i]=1;
			ti[t[i].D]+=t[i].C;
			dfs(x-t[i].B);
			ti[t[i].D]-=t[i].C;
			vit[i]=0;
		}
	}
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=n;++i){
        scanf("%d",&c[i]);
        for(int k=0;k<=13;++k){
            if(c[i]>=(1<<k)){
                B[++e]=(1<<k)*b[i];
                C[e]=(1<<k);
                D[e]=i;
                c[i]-=(1<<k);
            }else{
                break;
            }
        }
        if(c[i]){
            B[++e]=c[i]*b[i];
            C[e]=c[i];
            D[e]=i;
        }
    }
    memset(dp,0x3f3f,sizeof(dp));
    dp[0]=0;
    int v;
    scanf("%d",&v);
    for(int i=1;i<=e;++i){
        for(int j=v;j>=B[i];--j){
            if(dp[j-B[i]]+C[i]<dp[j]){
                dp[j]=dp[j-B[i]]+C[i];
            }
        }
    }
    printf("%d\n",dp[v]);
    while(true){
		bool flag=0;
	    for(int i=1;i<=e;++i){
	    	if(vis[i]){
	    		continue;
			}
	    	if((v>=2*B[i]&&dp[v-B[i]-B[i]]+C[i]+C[i]!=dp[v]&&dp[v-B[i]]+C[i]==dp[v])||(v<2*B[i]&&v>=B[i]&&dp[v-B[i]]+C[i]==dp[v])){//必选 
	    		v-=B[i];
	    		ti[D[i]]+=C[i];
	    		flag=1;
	    		vis[i]=1;
			}
		}
		if(!flag){//如果没有必选物品了，就退出 
			break;
		}
	}
	for(int i=1;i<=e;++i){
		if(vis[i]){
			continue;
		}
		if(v>=B[i]&&dp[v-B[i]]+C[i]==dp[v]){//统计所有的可行物品 
    		t[++cnt]={B[i],C[i],D[i]};
		}
	}
	dfs(v);//dfs 
    return 0;
}
```

加了此优化后，速度飞起，仅用257ms就过了此题

---

## 作者：万万没想到 (赞：2)

[原题传送门：P3423 [POI2005]BAN-Bank Notes](https://www.luogu.com.cn/problem/P3423)

题目大意：
给出一个容量为 $k$ 的背包，共有 $n$ 种物品，每种物品有自己的价值 $b_i$ 和这个物品的个数 $c_i$ ，求刚好装满背包的最少的物品方案，输出所需物品个数，和对于每一个物品个数的方案。

数据范围：
- $1 \leq n \leq 200,1 \leq k \leq 20000$
- $1 \leq b_1 < b_2 < ⋯ \leq b_n \leq 20000$
- $1 \leq c_1 < c_2 < ⋯ \leq c_n \leq 20000$

思考过程：

这是一个背包的问题，由于每一种物品有不同个数，那么可以确定，这是一个多重背包，朴素的多重背包时间复杂度是 $O(k \Sigma c_i)$，单调队列优化的时间复杂度是 $O(kn)$ 

这里提供另外一种思路，由于这里我们求的是相同价值求最少物品，其实可以转化为将价值作为外层循环的条件。每一个价值必然由更小的价值递推而来，那么递推而来的那一个价值与当前进行DP的价值之间的差必定是某个 $b_i$ 。

接下来，我们考虑递推，对于某个 $b_i$ ，如果包含在 $dp_i$ 的方案中，只要满足使用数不超过 $c_i$ ，那么不管在方案中的哪一个位置都可以，那么不如能放在前面就放在前面。我们再考虑，如果 $b_i$ 大的和小的都可以递推而来，那么先放大的，因为我们要求最少方案，那么局部最优可以推至整体最优，时间复杂度为 $O(kn)$ ，同单调队列复杂度一样。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,b[205],c[205],dp[20005][205],cost[20005];
int main(){
	memset(cost,0x3f,sizeof(cost));
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",&b[i]);
	for(int i=1;i<=n;++i)scanf("%d",&c[i]);
	scanf("%d",&k);
	int minn,position,temp;
	cost[0]=0;
	for(int i=1;i<=k;++i){
		minn=2e9,position=0;
		for(int j=1;j<=n;++j){
			temp=i-b[j];
			if(b[j]<=i&&dp[temp][j]<c[j]){
				if(cost[temp]<cost[i-b[position]])position=j;
			}
		}
		if(!position)continue;
		for(int j=1;j<=n;++j)dp[i][j]=dp[i-b[position]][j];
		dp[i][position]=dp[i-b[position]][position]+1;
		cost[i]=cost[i-b[position]]+1;
	}
	printf("%d\n",cost[k]);
	for(int i=1;i<=n;++i){
		printf("%d ",dp[k][i]);
	}
	printf("\n");
	return 0;
}
```


---

## 作者：__lyh__ (赞：1)

做完此题，像平常一样点开题解，不出意料地看到题解区基本都是二进制拆分/单调队列优化来做的多重背包。

想起了 [NOI Online 普及T3 买表](https://www.luogu.com.cn/problem/P6567) 考场上二进制优化被卡常卡挂50分的惨痛经历。。。所以，我弄了个完全背包来做此题。

我们在买东西时，一般先从面值大的钱找起，用完全背包思想做这题同理，每个答案都从大硬币累加小硬币而来，我们要先给硬币按面值大小从大到小排序。

我们用一个$d$数组存储当答案为$j$时的最小方案至少要用到多少张面值为$a[i]$的硬币，注意$d$数组每次循环都要清零。

输出具体方案也很简单，用$pre[i]$来存储当答案为$i$时的前驱节点，用桶排记录每个硬币要求的数量即可。

时间复杂度为$O（nk）$，与单调队列优化一样，但是常数比单调队列优化小很多，时间快到飞起。

不开O2：[196ms](https://www.luogu.com.cn/record/36986993)

开O2：[88ms](https://www.luogu.com.cn/record/36988098)

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read()//习惯性开快读，蒟蒻被卡常卡怕了QAQ 
{
	int f=1,x=0;char ch=getchar();
	while((ch<'0'||ch>'9')&&ch!='-'){ch=getchar();}
	if(ch=='-'){f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
struct no
{
	int b,c;//面值，数量 
};
bool cmp(no a,no b)
{
	return a.b>b.b;
}
no a[205];
int n,f[20005],m,g,d[20005],pre[20005],z[20005],o[205];
int main()
{
	memset(f,0x3f,sizeof(f));//赋一个最大值 
	f[0]=0;
	n=read();
	for(int i=1;i<=n;i++) a[i].b=read();
	for(int i=1;i<=n;i++) a[i].c=read();
	m=read();
	for(int i=1;i<=n;i++)
	{
		z[a[i].b]=i;//由于后面要排序，把面值所代表的序号用数组存起来 
	}
	sort(a+1,a+n+1,cmp);//从大到小排序 
	for(int i=1;i<=n;i++)
	{
		memset(d,0,sizeof(d));//d数组用来记录当答案为j时的最小方案至少要用到多少张面值为a[i].b的硬币
		for(int j=a[i].b;j<=m;j++)
		{
			if(d[j-a[i].b]<a[i].c)
			{
				if(f[j-a[i].b]+1<f[j])
				{
					d[j]=d[j-a[i].b]+1;
					f[j]=f[j-a[i].b]+1;
					pre[j]=a[i].b;//记录前驱节点 
				}
			}
		}
	}
	printf("%d\n",f[m]);
	while(m)//循环记录每种硬币所需数量 
	{
		ll ans=z[pre[m]];
		o[ans]++;
		m-=pre[m];
	}
	for(int i=1;i<=n;i++)
	{
		printf("%d ",o[i]);
	}
	return 0;
}
```


---

## 作者：Coros_Trusds (赞：0)

多重背包输出方案数题。

# 题目大意

$\verb!Byteland!$ 拥有一套先进的货币系统，这个系统一共有 $n$ 种面值的硬币，面值分别为 $b_1,b_2,\cdots,b_n$。但是每种硬币有数量限制，现在我们想要凑出面值 $k$，求最少要用多少个硬币.

输出每个硬币使用的个数。

# 题目分析

首先是板子，可以采用二进制拆分优化来做。

然后我们发现，如果选了一个硬币，设它的价值为 $x$，代价为 $y$，则有 $dp[now]=dp[now-y]+x$，根据定义来说，这是显然的。随后我们参考这个，可以进行一遍暴力的原始 $\verb!dfs!$，如果选了这个硬币，那么就沿着这个分支下去，随后若 $now$ 变成 $0$ 了，说明已经遍历完了，此时直接输出方案数并结束程序即可。

# 代码

```cpp
//you should use O2
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <iomanip>
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	inline int read() {
		int ret = 0,f = 0;char ch = getchar();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getchar();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getchar();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;

const int N = 2e5 + 5;
int mon[N],num[N],v[N],w[N],dp[N],id[N],path[N];
bool vis[N];
int n,m,idx;
inline void dfs(int now) {
	if (now == 0) {
		for (register int i = 1;i <= n; ++ i) printf("%d ",path[i]);
		exit(0);
	}
	for (register int i = 1;i <= idx; ++ i) {
		if (vis[i] == false && v[i] <= now) {
			if (dp[now] == dp[now - v[i]] + w[i]) {
				vis[i] = true;
				path[id[i]] += w[i];
				dfs(now - v[i]);
				path[id[i]] -= w[i];
				vis[i] = false;
			}
		}
	}
}
int main(void) {
	n = read();
	for (register int i = 1;i <= n; ++ i) mon[i] = read();
	idx = 0;
	for (register int i = 1;i <= n; ++ i) {
		num[i] = read();
		int a = mon[i],b = 1,c = num[i];
		for (register int j = 1;j <= c;j <<= 1) {
			v[++ idx] = j * a,w[idx] = j * b;
			id[idx] = i;
			c -= j;
		}
		if (c) {
			v[++ idx] = c * a,w[idx] = c * b;
			id[idx] = i;
		}
	}
	m = read();
	mst(dp,0x3f);
	dp[0] = 0;
	for (register int i = 1;i <= idx; ++ i) {
		for (register int j = m;j >= v[i]; -- j) {
			dp[j] = std::min(dp[j],dp[j - v[i]] + w[i]);
		}
	}
	printf("%d\n",dp[m]);
	dfs(m);
	
	return 0;
}
```

---

## 作者：cold_cold (赞：0)

[安利一波博客](https://www.cnblogs.com/cold-cold/p/10015491.html)

这一题其实很容易看出是一道背包问题，为什么我NOIP2018没有想到，此题应该属于[多重背包](https://www.cnblogs.com/cold-cold/p/9991315.html)问题，我们显然可以，将f[i]定为拼出i元需要的最少钞票数，将v定为花费的钞票数，将w定为这些钞票加起来的总价值，再利用多重背包的拆分方法。上链接已述，此处不多做叙述。

但重点在于怎样记录：一开始我的想法是将每个f[i]都记录其转移的来pre[i]，输出的时候向下不断temp=pre[temp]来输出。但这样是不行的

错误代码如下：

```cpp
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
using namespace std;
typedef long long ll;
inline int read()
{
    register int p(1),a(0);register char ch=getchar();
    while((ch<'0'&&ch>'9')&&ch!='-') ch=getchar();
    if(ch=='-') p=-1,ch=getchar();
    while(ch>='0'&&ch<='9') a=a*10+ch-48,ch=getchar();
    return a*p;
}
const int N=210,M=20010;
int n,m,f[M],b[N],biao[M][2],zh[M][N],pre[M],hole[N],c[N],temp=1;
int main()
{
    n=read();
    for(int i=1;i<=n;i++) b[i]=read();
    for(int i=1;i<=n;i++) c[i]=read();
    m=read();
    memset(f,0x3f,sizeof(f));
    f[0]=0;
    for(int i=1;i<=n;i++)
    {
        temp=1;
        while((temp<<1)<=c[i]+1&&b[i]*temp<=m)
        {
            for(int j=m;j>=b[i]*temp;j--) if(f[j]>f[j-b[i]*temp]+temp)
            {
                f[j]=f[j-b[i]*temp]+temp;
                biao[j][0]=i,biao[j][1]=temp;
                pre[j]=j-b[i]*temp;
            }
            temp<<=1;
        }
        if((temp<<1)>=c[i])
        {
            temp=c[i]-temp+1;
            for(int j=m;j>=b[i]*temp;j--) if(f[j]>f[j-b[i]*temp]+temp)
            {
                f[j]=f[j-b[i]*temp]+temp;
                biao[j][0]=i,biao[j][1]=temp;
                pre[j]=j-b[i]*temp;
            }
        }
    }
    printf("%d\n",f[m]);
    temp=m;
    while(temp)
    {
        printf("%d ",temp);
        hole[biao[temp][0]]+=biao[temp][1];
        temp=pre[temp];
    }
    for(int i=1;i<=n;i++)
        printf("%d ",hole[i]); 
    return 0;
}

```

这样做连样例都过不了，我们考虑是为什么。首先我们考虑01背包为什么要倒叙循环，因为这样就不会重复使用同一个物品。那么此算法的错误之处就出在这里。

样例中要求拼出的数是10，有2 3 5三个数，其中5 只有一个，那么我们从f[10] ( f[m] ) 开始循环，我们首先取到5，于是我们接着我们循环f[5]这时我们就发现biao[5]在第循环5的时候被修改过了，所以它也用的是5这张钞票，但5的钞票只有一张，于是就出现错误了

显然一维无法解决这个问题了，必须用二维。此题卡空间，int[3000][20000],消耗约228MB，而此题空间上限为64MB，而如果我们使用bool类型就可以过，

我们用cun[i][j]，表示在f[i][j]处是否发生转移而下一个要循环的其实是可以算出来为f[i-1][j-w[i]],就这样知道j为0为止

实现如下：

```cpp

#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
using namespace std;
typedef long long ll;
inline int read()
{
    register int p(1),a(0);register char ch=getchar();
    while((ch<'0'&&ch>'9')&&ch!='-') ch=getchar();
    if(ch=='-') p=-1,ch=getchar();
    while(ch>='0'&&ch<='9') a=a*10+ch-48,ch=getchar();
    return a*p;
}
const int N=210,M=20010,N2=3010;
int n,m,f[M],b[N],v[N2],w[N2],bef[N2],hole[N],c[N],temp=1,cnt=0,ji=0;
bool cun[N2][M];
int main()
{
    n=read();
    for(int i=1;i<=n;i++) b[i]=read();
    for(int i=1;i<=n;i++) c[i]=read();
    m=read();
    memset(f,0x3f,sizeof(f));
    f[0]=0;
    for(int i=1;i<=n;i++)
    {
        temp=1;
        while((temp<<1)<=c[i]+1&&b[i]*temp<=m)
        {
            v[++cnt]=temp;
            w[cnt]=b[i]*temp;
            bef[cnt]=i;
            temp<<=1;
        }
        if((temp<<1)>=c[i])
        {
            temp=c[i]-temp+1;
            v[++cnt]=temp;
            w[cnt]=b[i]*temp;
            bef[cnt]=i;
            temp<<=1;
        }
    }
    for(int i=1;i<=cnt;i++)
        for(int j=m;j>=w[i];j--)
        {
            if(f[j]>f[j-w[i]]+v[i])
            {
                f[j]=f[j-w[i]]+v[i];
                cun[i][j]=true;
            }
        }
    printf("%d\n",f[m]);
    temp=m,ji=cnt;
    while(temp)
    {
        while(!cun[ji][temp]&&ji) --ji;
        temp-=w[ji];hole[bef[ji]]+=v[ji];
        --ji;
    }
    for(int i=1;i<=n;i++)
        printf("%d ",hole[i]); 
    return 0;
}
```



---

