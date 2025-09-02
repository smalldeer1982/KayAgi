# Save the Magazines

## 题目描述

Monocarp has been collecting rare magazines for quite a while, and now he has decided to sell them. He distributed the magazines between $ n $ boxes, arranged in a row. The $ i $ -th box contains $ a_i $ magazines. Some of the boxes are covered with lids, others are not.

Suddenly it started to rain, and now Monocarp has to save as many magazines from the rain as possible. To do this, he can move the lids between boxes as follows: if the $ i $ -th box was covered with a lid initially, he can either move the lid from the $ i $ -th box to the box $ (i-1) $ (if it exists), or keep the lid on the $ i $ -th box. You may assume that Monocarp can move the lids instantly at the same moment, and no lid can be moved more than once. If a box will be covered with a lid after Monocarp moves the lids, the magazines in it will be safe from the rain; otherwise they will soak.

You have to calculate the maximum number of magazines Monocarp can save from the rain.

## 说明/提示

In the first testcase of the example, Monocarp can move the lid from the second box to the first box, so the boxes $ 1 $ , $ 3 $ and $ 4 $ are covered, and $ 10 + 8 + 9 = 27 $ magazines are saved.

In the second testcase, Monocarp can move the lid from the second box to the first box, then from the third box to the second box, then from the fifth box to the fourth box, and then from the sixth box to the fifth box. The boxes $ 1 $ , $ 2 $ , $ 4 $ and $ 5 $ will be covered, so $ 20 + 10 + 30 + 20 = 80 $ magazines can be saved.

There are no lids in the third testcase, so it's impossible to save even a single magazine.

## 样例 #1

### 输入

```
4
5
01110
10 5 8 9 6
6
011011
20 10 9 30 20 19
4
0000
100 100 100 100
4
0111
5 4 5 1```

### 输出

```
27
80
0
14```

# 题解

## 作者：YYHISBOY (赞：16)

## 考虑模拟

## 题意

* 有 $n$ 个盒子

* 给出一个长度为 $n$ 的字符串，字符串中仅含有 $0$，$1$， 两种字符，

* 字符 $0$ 表示第 $i$ 个盒子上没有盖子，  字符 $1$ 表示第 $i$ 个盒子上有盒子，

* 第 $i$ 个盒子上的盖子可以移动到第 $(i-1)$ 个盒子上，每个盖子能且仅能移动一次，

* 给出 $n$ 个数,表示第 $i$ 个盒子里有 $a_i$ 本杂志，要求能保留下来的杂志的最大数量。

## 思路

我的做法是把它当作模拟题来写。


先交待数组
```
const int M=2000500;
int T,n,ans,a[M];
//T表示测试数据数，n即是题中的n。
//ans就是储存答案的容器，a[M]表示题中所给数据。
char b[M];//存入所给的01串。
bool g[M],vis[M];
//g[M]表示是否有盖子，即该盒子的杂志能否保存。
//vis[M]表示该盒子上的盖子是否移动过。

```
因为第 $i$ 个盒子上的盖子只能通过第 $i+1$ 个盒子上的盖子转移过来，
**所以在循环时要考虑下一个盒子的状态（即有无盖子）**。

```
int l=0,r=0;//l表示选取到的无盖子的盒子，r表示选取到的有盖子的盒子。
for(int i=1;i<n;i++)
  {
     if(!g[i]&&g[i+1]&&!vis[i+1])//第i个盒子上没有盖子，第i+1上有。
       {                      //并且第i+1个盒子上的盖子没有移动过。
          l=i;                //l的选取条件就如上
          for(int j=i+1;j<=n;j++)//l选取完毕，开始在l后面寻找r。
            if(g[j]&&!vis[j])//r的选取条件，有盖子且盖子不是转移来的。
              {              
                r=j; 
                if(a[l]>a[r]&&l&&r)  
                  {  //如果第l个盒子里的杂志比第r个盒子里的杂志多，则换。
                     for(int t=l;t<r;t++)//整体移动
                       vis[t]=1;//打标记
                     g[l]=1;
                     g[r]=0;
                     l=0;//回溯
                  }
              }
            else if(!g[i]||vis[i])break;
       }//如果在寻找过程中发现有盒子已经被替换过，则说明无法整体移动，跳出循环。
  }
  
```
剩下的都是一些简单的东西，
最后贴上AC代码。
```
#include<bits/stdc++.h>
using namespace std;
const int M=2000500;
int T,n,ans,a[M];
char b[M];
bool g[M],vis[M];
int read()
{
  int x=0,f=1;
  char c=getchar();
  while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
  while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
  return x*f;
}
int main()
{
  T=read();
  for(int k=1;k<=T;k++)
    {
      ans=0;
      n=read();
      cin>>b+1;
      for(int i=1;i<=n;i++)
        if(b[i]=='1')g[i]=1;
      for(int i=1;i<=n;i++)a[i]=read();
      int l=0,r=0;
      for(int i=1;i<n;i++)
        {
          if(!g[i]&&g[i+1]&&!vis[i+1])
            {
              l=i;
              for(int j=i+1;j<=n;j++)
                if(g[j]&&!vis[j])
                  {
                    r=j;
                     if(a[l]>a[r]&&l&&r)
                       {
                         //cout<<l<<' '<<r<<'\n';
                         for(int t=l;t<r;t++)
                           vis[t]=1;
                         g[l]=1;
                         g[r]=0;
                         l=0;
                       }
                  }
                else if(!g[i]||vis[i])break;
            }
        }
      for(int i=1;i<=n;i++)//统计答案
        if(g[i])ans+=a[i];
      printf("%d\n",ans);//输出
      for(int i=1;i<=n;i++)//回溯
        {
          vis[i]=0;
          g[i]=0;
          a[i]=0;
        }
    }
  return 0;
}
```
考试时做的题，是一道 ~~水题~~ （考试时写了1个小时），我还是太菜了！！？？。


---

## 作者：SalomeJLQ (赞：5)

考虑 DP。

设 $f_{i,0/1}$ 表示考虑到第 $i$ 个箱子为止，当前（第 $i$ 个）箱子的盖子往前传 / 留在原地时的最大保护价值。

当 $i$ 处原本有盖子时：

$$
f_{i,0}=\max(f_{i-1,1},f_{i-1,0}+a_{i-1}),\quad
f_{i,1}=\max(f_{i-1,0},f_{i-1,1})+a_i;
$$

否则 $f_{i,0}=f_{i,1}=\max(f_{i-1,0},f_{i-1,1})$。

初值设为全 $0$ 即可。

---

## 作者：Cappuccino_mjj (赞：4)

此题可以使用 dp 来做~

---

## [题目传送门](https://www.luogu.com.cn/problem/CF1743C)

题目意思：

现在有 $n$ 个箱子，每个箱子里装着 $a_i$ 杂志。一些箱子上盖着盖板（防止被雨淋），第 $i$ 个盖板只能移动到第 $i-1$ 个箱子上。请问如何摆放盖板使得不被淋湿的杂志最多？

---

思路：
1. 一个箱子有两种状态：盖盖板或者不盖盖板。
2. 移动一个盖板或者不移动盖板为一个阶段。

因此我们就可以推导出状态转移方程：
1. 如果当前箱子上有盖板时，就考虑将盖板给上一个箱子和不给的最大值。
1. 如果当前箱子没有盖板，就取自身两个状态的最大值。

状态转移方程如下：
```cpp
if(vis[i]=='1')//判断是否有盖板
{
	dp[i][0]=dp[i-1][0]+a[i-1];//将盖板移到上一个箱子
	dp[i][1]=max(dp[i-1][0],dp[i-1][1])+a[i];//将盖板保留给自己
}
else dp[i][0]=max(dp[i-1][0],dp[i-1][1]);//没有盖板
```
有了状态转移方程，其他的也就好写了。

---

代码：
```cpp
#include<iostream>
#include<string.h>
using namespace std;
const int N=1e6+10;
int dp[N][2];
int a[N];
string vis;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
			dp[i][0]=dp[i][1]=0;
		cin>>vis;
		vis=" "+vis;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=n;i++)
		{
			if(vis[i]=='1')
			{
				dp[i][0]=dp[i-1][0]+a[i-1];
				dp[i][1]=max(dp[i-1][0],dp[i-1][1])+a[i];
			}
			else dp[i][0]=max(dp[i-1][0],dp[i-1][1]);
		}
		cout<<max(dp[n][1],dp[n][0])<<endl;
	}
}
```

---

完美撒花~

---

## 作者：Nanani (赞：3)


### 一个很简单的贪心

看题干可以发现，如果出现两个 $0$ 相连，那前面一个 $0$ 一定不能通过移动它之后的 $1$ 来使它变成 $1$。反之如果 $0$ 后接的是 $1$，那这个 $0$ 一定可以通过移动 $1$ 来变成 $1$。也就是说，在一个区间内，如果只有 $1$ 个 $0$ 且 $0$ 后都是 $1$，那我们可以实现改变 $0$ 的位置，即 $0$ 可变到这个区间的任意一个位置。
### 从后往前递推，因为只有遇到没盖盖板的才用考虑后面的用不用往前挪，所以我们可以以每一个没盖板的作为节点。用总和减去每一段的最小值就是答案（有几个 $0$ 一定就有几个被淋到）。




###### 下面是代码捏
------------
```cpp
//by 72
#include<bits/stdc++.h>
#define N 2000005
#define F(i,a,b) for(int i=a;i<=b;i++)
#define Fd(i,a,b) for(int i=a;i>=b;i--)
#define il inline
il int read()
{
	int x=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')x=10*x+c-'0',c=getchar();
	return x*f;
}
il int read2()//这个是用来读中间没有空格的0和1的
{
	int x=0;char c=getchar();
	while(c>'9'||c<'0'){c=getchar();}
	x=c-'0';return x;
}
int t,n,a[N],judge[N],visit[N],ans,minn; 
int main()
{
	t=read();
	for(;t;t--)
	{
		n=read();ans=0;
		F(i,1,n)judge[i]=read2();
		F(i,1,n)a[i]=read(),ans+=a[i];minn=a[n];//minn初始化
		Fd(i,n,1)
		{
		    if(a[i]<minn)minn=a[i];
		    if(judge[i]==0)ans-=minn,minn=a[i-1];//碰到0就减当前这些数的最小值 然后更新minn
		}
		cout<<ans<<"\n";
	}
	return 0; 
}
//以上 
//小q好困 QAQ 

```


------------
结束啦。

---

## 作者：CENRUIYANG (赞：2)

考虑dp，设 $f_{i,0/1}$ 表示考虑到第 $i$ 个位置，该位置是/否有盖子的最大值。

考虑初始化， $f_{0,0}=0$，剩下的全部设成 $- \infty$ 即可。

考虑如何转移。

- $s_i=1\ \ \ \ f_{i,0}=f_{i-1,0}+a_{i-1}\ \ \ \ f_{i,1}=\max(f_{i-1,0},f_{i-1,1})+a_i$
- $s_i=0\ \ \ \ f_{i,0}=\max(f_{i-1,0},f_{i-1,1})$

当 $s_i=1$ 的时候，更新 $f_{i,0}$ 时我们需要将盖子移到 $i-1$ ，两个盖子叠在一块显然是不优的，所以我们只需用 $f_{i-1,0}$ 来更新即可。

当 $s_i=0$ 的时候，由于只考虑前 $i$ 个，我们无法使 $i$ 这个位置变成有盖子的状态，故不更新，保留初始的 $-\infty$（不合法）。

最后输出 $\max(f_{n,0},f_{n,1})$ 即可。

[代码](https://codeforces.com/contest/1743/submission/180100820)

---

## 作者：i_love_tym (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1743C)

# 考虑 DP

那么我们不妨用 $f_{i,0/1}$ 来表示前 $i$ 个箱子有盖子 / 没盖子所能剩下的最大杂志数量。

假设第 $i$ 个箱子原本有盖子，容易得出:

$f_{i,0}=\max(f_{i-1,1} , f_{i-1,0}+a_{i-1})$

$f_{i,1}=\max(f_{i-1,1} , f_{i-1,0}+a_{i-1})$。

反之，如果第 $i$ 个箱子原本没有盖子，那么

$f_{i,0}=f_{i,1}=\max(f_{i-1,1}f_{i-1,0})$。

综上，我们可以写出[代码](https://www.luogu.com.cn/paste/cz0ho0tp)。



---

## 作者：孤芒星河233 (赞：1)

# CF1743C Save the Magazines

[洛谷题面](https://www.luogu.com.cn/problem/CF1743C)

[CF题面](https://codeforces.com/problemset/problem/1743/C)

## 思路

  应该是道贪心题？赛时想到的是动态规划。$f_{i,0/1}$ 表示第 $i$ 个箱子，$0$ 表示不移动板子，$1$ 表示移动板子时最多能保留多少报纸。

  显然，当第 $i$ 个箱子上**无板子**时，有 $f_{i,0}=\max(f_{i-1,1},f_{i-1,0})$

  当第 $i$ 个箱子上**有板子**时，可以选择是否移动这个板子，不移动则有 $f_{i,0}=\max(f_{i-1,1},f_{i-1,0})+a_i$
  
  若第 $i-1$ 没有板子则可以直接移动，有 $f_{i,1}=f_{i-1,0}+a_{i-1}$
  
  反之需要先移动第 $i-1$ 个板子，有 $f_{i,1}=f_{i-1,1}+a_{i-1}$
  
## 代码

  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  
  const int N=2e5+9;
  int n,T,a[N],f[N][2];
  char s[N];
  
  int main(){
      scanf("%d",&T);
      while(T--){
          scanf("%d%s",&n,s+1);
          for(int i=1;i<=n;i++) scanf("%d",&a[i]);
          f[1][0]=f[1][1]=0;
          if(s[1]=='1') f[1][0]=a[1];//初始化
          for(int i=2;i<=n;i++){
              if(s[i]=='0') f[i][0]=max(f[i-1][0],f[i-1][1]),f[i][1]=0;
              else{
                  f[i][0]=max(f[i-1][0],f[i-1][1])+a[i];
                  if(s[i-1]=='0') f[i][1]=f[i-1][0]+a[i-1];
                  else f[i][1]=f[i-1][1]+a[i-1];
              }
          }
          printf("%d\n",max(f[n][1],f[n][0]));
      }
      return 0;
  }
  ```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1743C)

------------
# 思路：
设定 $dp_{i,0/1}$ 表示前 $i$ 个盒子的最大值，以及第 $i$ 个盒子的盖子是否移动。

下面进行分类讨论即可。

如果没有盖子，那就直接继承上一个的最大值。

如果有盖子，那就考虑移动和不移动两种情况，不移动也是直接继承上一个的最大值。

否则就讨论第 $i - 1$ 个是否有盖子，没有不需要移动第 $i - 1$ 个，否则就需要移动才能加上第 $i$ 个。

------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int dp[N][2],a[N],vis[N],T,n;
int main(){
	scanf("%d",&T);
	while(T--){
		memset(dp,0,sizeof(dp));
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%1d",&vis[i]);
		}
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			if(vis[i]){
				dp[i][0]=a[i];
			}
		}
		for(int i=2;i<=n;i++){
			if(vis[i]){ 
				dp[i][0]=max(dp[i-1][0]+a[i],dp[i-1][1]+a[i]);
				if(!vis[i-1]){
					dp[i][1]=dp[i-1][0]+a[i-1];
				}else{
					dp[i][1]=dp[i-1][1]+a[i-1];
				}
			}else{
				dp[i][0]=max(dp[i-1][0],dp[i-1][1]);
			}
		}
		printf("%d\n",max(dp[n][0],dp[n][1]));
	}
	return 0;
}
```

---

## 作者：zbk233 (赞：0)

## 思路

考虑贪心。

从描述中可以看出，若一个盖板要向左移动，那么在它左边和它相邻的盖板（如果有的话）就都要移动。

我们把一段连续的盖板看作一个整体，容易看出若是移动就一定是整体的移动。

那么我们就能求出一段连续的盖板移动的最优值。

具体实现是先预处理出一个盖板向左移动能获得的价值（可能为负），之后对于一个连续为 $1$ 的区间，求出移动价值的前缀和的最大值。

## 代码

```cpp
#include<iostream>
using namespace std;
int a[200005],b[200005],c[200005];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		int n,sum=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			char c;
			cin>>c;
			a[i]=c-'0';
		}
		for(int i=1;i<=n;i++){
			cin>>b[i];
			if(a[i]) sum+=b[i];
			c[i]=b[i-1]-b[i];
		}
		int s1,s2,s3=0;
		for(int i=1;i<=n;){
			s1=s2=0;
			while(!a[i]&&i<=n) i++;
			while(a[i]&&i<=n){
				s1+=c[i];
				s2=max(s1,s2);
				i++;
			}
			s3+=s2;
		}
		cout<<sum+s3<<'\n';
	}
	return 0;
}
```


---

