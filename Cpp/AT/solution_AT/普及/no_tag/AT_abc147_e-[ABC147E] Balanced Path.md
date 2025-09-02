# [ABC147E] Balanced Path

## 题目描述

高桥君有一个 $H$ 行 $W$ 列的棋盘，第 $i$ 行 $j$ 列记为 ( $i$ , $j$ ),每个格子里有两个整数， $a_{i,j}$ 和 $b_{i,j}$。

高桥君从( 1,1 )出发要走到( $H$ , $W$ )。每一次只能向左或向下走一格，每一次走过的方格，高桥君会把它上面的数一个染成红色，一个染成蓝色，求做过路径中红色数字的总和减蓝色数字总和的绝对值的最小值。

## 样例 #1

### 输入

```
2 2
1 2
3 4
3 4
2 1```

### 输出

```
0```

## 样例 #2

### 输入

```
2 3
1 10 80
80 10 1
1 2 3
4 5 6```

### 输出

```
2```

# 题解

## 作者：Astatinear (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/AT5288)

### 思路

动态规划 $dp$。

我们定义 $dp[i][j][k]$ 表示到达 $i,j$ 点是否可以做到 涂成红色减去涂成蓝色得数的值 为 $k$，可以做到则为 $1$，不可以做到就是 $0$。然后我们在定义一个 $c[i][j]$ 表示 $a[i][j]-b[i][j]$。

显然，我们可以得到两种大的情况。

第一种，从 $i-1,j$ 走过来，则此时可以得到转移方程为 $dp[i][j][k]|=dp[i-1][j][k-c[i][j]]|dp[i-1][j][k+c[i][j]]$。

第二种，从 $i,j-1$ 走过来，则此时同上，可以得到转移方程为 $dp[i][j][k]|=dp[i][j-1][k-c[i][j]]|dp[i][j-1][k-c[i][j]]$。

但是这个地方我们从要注意一种情况，就是有可能这个值为负数，所以，我们可以将所有的数组多开一倍，然后我们将所有的 $k$ 加上一个 $12800$，就不会存在有负数的情况了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
bool dp[81][81][25601];
int h,w;
int a[85][85],b[85][85],c[85][85];
int sum;
int main()
{
	cin>>h>>w;
	for(int i=1;i<=h;++i)
	{
		for(int j=1;j<=w;++j)
		{
			cin>>a[i][j];
			sum=max(sum,a[i][j]);
		}
	}
	for(int i=1;i<=h;++i)
	{
		for(int j=1;j<=w;++j)
		{
			cin>>b[i][j];
			c[i][j]=a[i][j]-b[i][j];
		}
	}
       //初始值
	dp[1][1][c[1][1]+12800]=1;
	dp[1][1][-c[1][1]+12800]=1;
	for(int i=1;i<=h;++i)
	{
		for(int j=1;j<=w;++j)
		{
			for(int k=0;k<=sum*(h+w-1);++k)
			{
                              //状态转移，记得加上 12800
				dp[i][j][k+12800]|=dp[i-1][j][k+c[i][j]+12800]|dp[i-1][j][k-c[i][j]+12800];
				dp[i][j][k+12800]|=dp[i][j-1][k+c[i][j]+12800]|dp[i][j-1][k-c[i][j]+12800];
				dp[i][j][-k+12800]|=dp[i-1][j][-k+c[i][j]+12800]|dp[i-1][j][-k-c[i][j]+12800];
				dp[i][j][-k+12800]|=dp[i][j-1][-k+c[i][j]+12800]|dp[i][j-1][-k-c[i][j]+12800];
			}
		}
	}
	for(int i=0;i<=sum*(h+w-1);++i)
	{
		if(dp[h][w][i+12800]||dp[h][w][-i+12800])
		{
        		//找到最小的k的值
			cout<<i<<endl;
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：xibaohe (赞：3)

本蒟蒻第三次发题解 ~~(第一次和第二次没通过)~~，恳请大家多多关照。

[题目传送门](https://www.luogu.com.cn/problem/AT_abc147_e)

# 题目大意
帮助高桥君走一个 $H$ 行 $W$ 列的棋盘，每次只能向右或向下走 $1$ 格，每个格子里面有两个数字，一个染成红色，一个染成蓝色，是两种颜色数字之和差最小。

# 题目思路
这是一道很明显的升维动规题，原因是我们需要三个维度来记录横坐标、纵坐标和最小差。我们可以用一个布尔型数组 $dp$ 来进行动态规划。

### $\mathit{dp}_{i,j,k}$ 用来表示从 $(1,1)$ 走到 $(i,j)$ 使最小差为 $k$ 是否有可能。

注意在这里 $k$ 表示的是红色的数字之和 $-$ 蓝色的数字之和，因此我们可以用一个变量 $t$ 存储第一个数字 $-$ 第二个的数字之差。

如果我们选择把第一个数字染红，第二个数字染蓝，相当于在上一步的基础上 $+t$，而上一步又有两种可能：
 - 从左边转移。
 - 从上边转移。

可推出如下状态转移方程：
```cpp
dp[i][j][k]|=(dp[i-1][j][k+t]||dp[i][j-1][k+t]);
```
同理，如果我们选择把第一个数字染蓝，第二个数字染红，相当于在上一步的基础上 $-t$，而上一步还是有两种可能：
 - 从左边转移。
 - 从上边转移。

可推出如下状态转移方程：
```cpp
dp[i][j][k]|=(dp[i-1][j][k-t]||dp[i][j-1][k-t]);
```

总状态转移方程如下：
```cpp
int t=a[i][j]-b[i][j];
dp[i][j][k]|=(dp[i-1][j][k-t]||dp[i][j-1][k-t]);
dp[i][j][k]|=(dp[i-1][j][k+t]||dp[i][j-1][k+t]);
```

但是我们会发现一个问题：如果数组越界怎么办？

# 数组越界问题
为防止数组越界，我们可以给状态转移方程加上两个特判：
 - 若下标小于 $0$，不要转移。
 - 若下标大于 $12720$（题目中所给上界），不要转移。
 
 代码如下：
 ```cpp
int t=a[i][j]-b[i][j];
if(k-t>=0) dp[i][j][k]|=(dp[i-1][j][k-t]||dp[i][j-1][k-t]);
if(k+t<=12720) dp[i][j][k]|=(dp[i-1][j][k+t]||dp[i][j-1][k+t]);
```
但同时我们面临着另一个问题：两种颜色的差不一定是正数，数组下标无法表示负数，怎么办呢？

### 数组下标偏移

简言之，就是用 $\mathit{dp}_{i,j,12720}$ 表示 $\mathit{dp}_{i,j,0}$，最后判断答案时 $-12720$ 就行了。

 ```cpp
int t=a[i][j]-b[i][j];
if(k-t>=12720) dp[i][j][k]|=(dp[i-1][j][k-t]||dp[i][j-1][k-t]);
if(k+t<=25440) dp[i][j][k]|=(dp[i-1][j][k+t]||dp[i][j-1][k+t]);
```
 
# 满分代码

 ```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

const int P=12720;
int h,w,a[85][85],b[85][85];
bool dp[85][85][25445];

int main()
{
	cin>>h>>w;//输入 
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
			cin>>a[i][j];
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
			cin>>b[i][j];
			
	dp[0][1][12720]=dp[1][0][12720]=true;//差距为零肯定为真 
	
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
			for(int k=0;k<=25440;k++)
			{
				int t=a[i][j]-b[i][j];//开始状态转移 
				if(k-t>=12720) dp[i][j][k]|=(dp[i-1][j][k-t]||dp[i][j-1][k-t]);
				if(k+t<=25440) dp[i][j][k]|=(dp[i-1][j][k+t]||dp[i][j-1][k+t]);
			}
	
	for(int i=0;i<=12720;i++)//寻找最小差距并输出 
		if(dp[h][w][12720-i]||dp[h][w][12720+i])
		{
			cout<<i<<endl;
			break;
		}

	return 0;
}
```



---

## 作者：Grisses (赞：3)

[题面](https://www.luogu.com.cn/problem/AT5288)

这道题很简单，就是一个 DP。这个方法可以去[这里](https://www.luogu.com.cn/blog/248400/solution-at5288)看。但是，这种方法并不优秀，我们可以用 bitset 进行优化。

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,ans=INT_MAX,f[85][85];
bitset<25605> dp[85][85];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)scanf("%d",&f[i][j]);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)scanf("%d",&a),f[i][j]-=a,f[i][j]=abs(f[i][j]);//每一个格子的红蓝差
	}
	dp[1][1][f[1][1]+12800]=dp[1][1][-f[1][1]+12800]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			dp[i][j]|=(dp[i-1][j]<<f[i][j])|(dp[i-1][j]>>f[i][j])|(dp[i][j-1]<<f[i][j])|(dp[i][j-1]>>f[i][j]);//状态转移
		}
	}
	for(int i=0;i<=25600;i++){
		if(dp[n][m][i]){
			ans=min(ans,abs(i-12800));//求最优解
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Max6700 (赞：1)

# 说在前面的话。

是道 DP 细节水题，但时间限制有 2 秒。

# 正文。

## [[ABC147E] Balanced Pathd 传送门。](https://www.luogu.com.cn/problem/AT_abc147_e)

## 题目大意和分析。

>高桥君有一个 $H$ 行 $W$ 列的棋盘。

>第 $i$ 行 $j$ 列记为 $(i,j)$ ，每个格子里有两个整数， $a_{i,j}$ 和 $b_{i,j}$ 。

即有一个 $H \times W$ 的棋盘，每个格子有两个数，下标是 $(i,j)$，你可以**自己分配**这两个数的颜色（红蓝）。

>高桥君从 $(1,1)$ 出发要走到 $(H,W)$。

起点 $(1,1)$ 到终点 $(H,W)$。

>每一次只能向左或向下走一格，每一次走过的方格，高桥君会把它上面的数一个染成红色，一个染成蓝色，求做过路径中红色数字的总和减蓝色数字总和的绝对值的最小值。

这段有点长，慢慢理一下：

1. 行走方式：**右**或**下**。

可以按一个棋盘 DP 的思路推。

2. 染色：**分类讨论**第一个数和第二个数分别取红蓝/蓝红。

3. 取值：由染色推出**红减蓝**的绝对值。

## 关于 DP。

dp 数组要开 $3$ 维。

```bool f[i][j][k];//行 列 差值```

即状态为走到 $i$ 行 $j$ 列，**红数和**减去**蓝数和**差值为 $k$ 能否凑成。

由于该做法为枚举差值，即计算差值时不取绝对值，所以 $f$ 的 $k$ 下标可能为负。

为避免数组越界，$f$ 的下标 $k$ 就统一加一个常量，使得其不为负。

## 做法。

在递推时需要考虑两种情况。

1. 第一个数是红，第二个数是蓝。
1. 第一个数是蓝，第二个数是红。

并对于两种情况做出不同限制。

1. ```if(k-ch>=-m)``` 
1. ```if(k-ch<=m)```

注：$ch$ 为红蓝数之差，$-m$ 和 $m$ 为差值的上下限。

## 代码。

```
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

int h,w;//rt
const int m=(80+79)*80;

int a[85][85];//第一个数。
int b[85][85];//第二个数。
int tmp;//每个位置 红数 减 蓝数 最大的绝对值。
bool f[85][85][2*m+5];//dp 数组。

int main(){
	//rt 输入。
	cin>>h>>w;
    
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
			cin>>a[i][j];
            
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
			{cin>>b[i][j];tmp=max(tmp,abs(a[i][j]-b[i][j]));}
	//DP 初始化。
	f[1][0][m]=1;
	f[0][1][m]=1;
   
	//推 DP 公式。
	for(int i=1;i<=h;i++)//棋盘行&列。
		for(int j=1;j<=w;j++)
		{
			for(int k=-tmp*(i+j-1);k<=tmp*(i+j-1);k++)//根据行列动态调整差值。注意正负都要枚举。
			{
				//第一种情况：a(第一个数)是红，b(第二个数)是蓝。
				int ch=a[i][j]-b[i][j];
				//如果能取(下标 k-当前红蓝差 >= 最低下限)
				if(k-ch>=-m)f[i][j][k+m]=f[i-1][j][m+k+ch] || f[i][j][k+m] || f[i][j-1][m+k+ch];//按棋盘DP推，能走到否？

				//第二种情况：a(第一个数)是蓝，b(第二个数)是红。
				ch=b[i][j]-a[i][j];
				//如果能取(下标 k-当前红蓝差 <= 最高上限)。
				if(k-ch<=m)f[i][j][k+m]=f[i-1][j][m+k+ch] || f[i][j][k+m] || f[i][j-1][m+k+ch];//亦然。
			}
		}	
        
	//计算答案 
	int ans=m;
	//当差值为负。
	for(int k=0;k>=-m;k--)
		if(f[h][w][k+m])//固定行列为终点，差值为处理后(即+m)的差值。
			{ans=min(ans,-k);break;}//取最小的差值。
	//反之亦然
	for(int k=0;k<=m;k++)
		if(f[h][w][k+m])
			{ans=min(ans,k);break;}
	cout<<ans;//输出
	return 0;
}

```

---

## 作者：Harrylzh (赞：1)

题意：从左上角走到右下角，使收集到的红数之和与蓝数之和的差值的绝对值最小。

思路：考虑动态规划。$dp[i][j][k]$ 表示走到 $i$ 行 $j$ 列时，差值为 $k$ 的情况能否凑成。转换时，如果左边或上边，$a[i][j]$ 蓝色或 $b[i][j]$ 蓝色共四种情况有一种可以凑成，那 $dp[i][j][k]$ 就可以凑成。

细节：
1. 差值是负数：每次加最大差值。
2. 结果：正数或负数绝对值最小。

代码：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int h,w;
const int maxcha=(80+80-1)*80;//最大差值
int a[80+5][80+5];
int b[80+5][80+5];
bool dp[80+5][80+5][2*maxcha+5];
int main()
{
	cin>>h>>w;
	for(int i=1;i<=h;i++)
	{
		for(int j=1;j<=w;j++)
		{
			cin>>a[i][j];
		}
	}
	
	int temp=0;//枚举时最大差值
	
	for(int i=1;i<=h;i++)
	{
		for(int j=1;j<=w;j++)
		{
			cin>>b[i][j];
			temp=max(temp,abs(a[i][j]-b[i][j]));
		}
	}
	
	dp[1][0][maxcha]=1;
	dp[0][1][maxcha]=1;
	
	for(int i=1;i<=h;i++)
	{
		for(int j=1;j<=w;j++)
		{
			for(int k=-temp*(i+j-1);k<=temp*(i+j-1);k++)
			{
				int cha=a[i][j]-b[i][j];
				if(k-cha>=-maxcha)//避免负数
				{
					dp[i][j][k+maxcha]=dp[i][j][k+maxcha]||dp[i-1][j][k+maxcha-cha];
					dp[i][j][k+maxcha]=dp[i][j][k+maxcha]||dp[i][j-1][k+maxcha-cha];
				}
				if(k+cha>=-maxcha)
				{
					dp[i][j][k+maxcha]=dp[i][j][k+maxcha]||dp[i-1][j][k+maxcha+cha];
					dp[i][j][k+maxcha]=dp[i][j][k+maxcha]||dp[i][j-1][k+maxcha+cha];
				}
			}
		}
	}
	int ans=2e9;//取答案
	for(int i=0;i>=-maxcha;i--)
	{
		if(dp[h][w][i+maxcha])
		{
			ans=min(ans,i);
			break;
		}
	}
	for(int i=0;i<=maxcha;i++)
	{
		if(dp[h][w][i+maxcha])
		{
			ans=min(ans,i);
			break;
		}
	}
	cout<<abs(ans)<<endl;
	return 0;
}
```

---

## 作者：kevin1616 (赞：1)

### 审题
高桥君从 $(1,1)$ 出发要走到 $(H,W)$。每一次只能向左或向下走一格，每一次走过的方格，高桥君会把它上面的数一个染成红色，一个染成蓝色，求做过路径中红色数字的总和减蓝色数字总和的绝对值的最小值。
***
### 方法
【动态规划】看到走方格和最小值，一般都是动态规划。看到此题的数据较小，所以时间和空间比较充足，故此方法可行。
***
### 思路
$dp[x][k]$ 指在坐标为 $(i,j)$ 的点，满足 $i+j=x$，目前的差加上 $12800$ 最小的为 $k$，此时答案可不可行。

每次要讨论来的方向和这个点的涂色。所以推出：

```cpp
dp[i + j][k + N] |= dp[i + j - 1][x] | dp[i + j - 1][y];
```

其中 $i$ 和 $j$ 指在坐标为 $(i,j)$ 的点，$k$ 指上一个的差值，$x$ 指这个点涂红色后的差值，$y$ 指这个点涂蓝色后的差值，$N$ 代表零点偏移的偏移值。
***
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 12800; //零点偏移
int n,m;
int a[85][85];
int b[85][85];
bool dp[165][N * 2 + 5];
// dp[i][c]表示截至(x,y)时，x+y=i，红色与蓝色的差+12800中最接近0的为c
int main(){
    scanf("%d %d",&n,&m);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++) scanf("%d",&a[i][j]);
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++) scanf("%d",&b[i][j]);
    }
    dp[2][N - a[1][1] + b[1][1]] = dp[2][N + a[1][1] - b[1][1]] = 1; //初始化
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(i == 1 && j == 1) continue; //如果已经初始化了的就跳过
            for(int k = -N;k <= N;k++){
                int x = k + N - a[i][j] + b[i][j];
                int y = k + N + a[i][j] - b[i][j];
                dp[i + j][k + N] |= dp[i + j - 1][x] | dp[i + j - 1][y];
            }
        }
    }
    for(int i = 0;i <= N;i++){ //找最小的答案
        if(dp[n + m][N + i] || dp[n + m][N - i]){
            cout << i << endl;
            return 0; //跳出程序，避免重复输出
        }
    }
    return 0; //好习惯
}
```
不抄题解，从我做起！

---

## 作者：pandaSTT (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT5288)

[更好的阅读体验？](https://www.luogu.com.cn/blog/cathyqwq/solution-at5288)

## 前置知识

**背包 DP**

**搜索**

**bitset 优化**

## 分析

观察题目和数据范围，首先想到**记忆化搜索**。

### 1. 记忆化搜索

搜索传入三个参数：**当前的横坐标**，**当前的纵坐标**，**当前的值**，考虑记忆化，  $ dp[i][j][k][0/1] $ 表示当前在坐标为 $ (i,j) $ 的点，目前的差为 $ k $ ，差为正数还是负数。

每个点可以转移到横坐标加一或纵坐标加一的点，而每次转移可以为当前值 $ +a[i][j]-b[i][j] $ 或当前值 $ +b[i][j]-a[i][j] $ ，所以只需要四种情况就行，用记忆化优化一下即可 AC 前 16 个点。
#### 核心代码

```cpp
  int dfs(int x,int y,int p){
      if(x<1||x>n||y<1||y>m){
          return 0x3f3f3f3f;
      }
      if(dp[x][y][abs(p)][p<0]!=0x3f3f3f3f){
          return dp[x][y][abs(p)][p<0];
      }
      if(x==n&&y==m){
          return min(abs(p+a[x][y]-b[x][y]),abs(p-a[x][y]+b[x][y]));
      }
      return dp[x][y][abs(p)][p<0]=min(min(abs(dfs(x+1,y,p+a[x][y]-b[x][y])),abs(dfs(x+1,y,p+b[x][y]-a[x][y]))),min(abs(dfs(x,y+1,p+a[x][y]-b[x][y])),abs(dfs(x,y+1,p+b[x][y]-a[x][y]))));
  }
```
这一看就只能得部分分，于是接着想到**背包DP**。

### 2. 背包DP

$ dp[i][j][k] $ 在坐标为 $ (i,j) $ 的点，目前的差为 $ k $，然后就是二维背包模板。

令 $ c=abs(a[i][j]-b[i][j]) $ ，那么 $ dp[i][j][k] $ 可以由 $ i-1 $ or $ j-1 $ 达到，而值的改变可以为 $ k+c $ or $ k-c $ ，与搜索一样，讨论四种情况即可。

#### 核心代码

```cpp
  for(int i=1;i<=n;i++){
          for(int j=1;j<=m;j++){
              int c=abs(a[i][j]-b[i][j]);
              for(int k=0;k<=12800;k++){
                  if(k-c>0){
                      dp[i][j][k]|=dp[i-1][j][k-c]|dp[i][j-1][k-c];
                  }
                  if(k+c<12800){
                      dp[i][j][k]|=dp[i-1][j][k+c]|dp[i][j-1][k+c];
                  }

              }
          }
      }
```

这个代码虽然可以 AC 但如果 $ n,m $ 的范围变大，这就不行了，所以想到 **bitset 优化**。

### 3. bitset 优化DP

把 k 这一维用 bitset 存储，进行二进制优化，可以省去一个循环，时间复杂度与空间复杂度大大减少。


#### 核心代码

```cpp
  for(int i=1;i<=n;i++){
          for(int j=1;j<=m;j++){
              int c=abs(a[i][j]-b[i][j]);
              dp[i][j]|=(dp[i-1][j]<<c)|(dp[i][j-1]<<c);
              dp[i][j]|=(dp[i-1][j]>>c)|(dp[i][j-1]>>c);
          }
      }
```

---

## 作者：Heavenly_meteorite (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc147_e)

先过一遍题意：每个格子两个数，随便涂色（红或蓝），问最后从左上角走到右下角的过程中每个格子的红色数相加，蓝色数相加，再整体相减取绝对值的最小值。

每道题的**空间限制**，**时间限制**往往会影响做题的思路与算法。至于这道题……哇，空间范围是如此之大。

再看看这道题的内容：嗯，走方格。那大概率是动态规划，深搜，广搜。还记得前面说的范围吗？动态规划明显的数组几乎可以随便开。果断动规。

动态规划三要素：数组定义，状态转移方程，初始化。

1. 数组定义。最**基础**的：答案是啥就开啥。答案问一个最小值，那就定义 $dp_{i,j}$ 为到达格子 $(i,j)$ 时红蓝数的总和之差的最小值。但是这里是不能由上面的格子推出这个格子的。很简单：你怎么知道到上一个格子时红色和大还是蓝色和大，绝对值应该加还是减？都是不知道的。但是，**空间复杂度**表示：你忽略了我的体量。直接大手一挥，开数组为 $dp_{i,j,k}$ 表示走到格子 $(i,j)$ 时由题能否取到值 $k$ 注：没有绝对值。这里要考虑 $k$ 的范围：假设每个格子都是最大差，乘上走过的格子数，则总共就会有：$80 \times 150=12720$。这是最大的绝对值差，实际可能会有正负，为防止**数组越界**，不妨把所有的数都加上这个最大值，使得不会有负数存在，但是最后输出的时候要还原。
2. 状态转移方程。这一块极其重要 ~虽然只是个暴力~ 。其实根据数组定义，**时间范围**和很小的**数据范围**就可以看出，可以循环枚举 $k$。这是显然的，虽然想法很简单，但是代码……依旧很简单。这里直接上代码都是可以看懂的。
```cpp
for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			if(i==1&&j==1){
				continue;
			}
			for(int k=-12720;k<=12720;k++){
				int y=a[i][j]-b[i][j];
				if((check(k-y)&&dp[i-1][j][val(k-y)])||(check(k+y)&&dp[i-1][j][val(k+y)])||(check(k-y)&&dp[i][j-1][val(k-y)])||(check(k+y)&&dp[i][j-1][val(k+y)])){
					dp[i][j][val(k)]=1;
				}
			}
		}
	}
```
注：这里的 $val$ 函数，$check$ 分别是将值调大（详情见数组定义）和控制数据范围，因为在加减过程中可能会超过最大值或者小于最小值，那些越界的直接不判断就行。以及之所以变量 $y$ 在计算时又要加又要减是因为两个数可以随意涂色，当涂色顺序颠倒则两色之差（单格）会变成相反数（显然的）。

3. 初始化。这里只需要处理 $(1,1)$ 上的值就行，也就是：
```cpp
dp[1][1][val(a[1][1]-b[1][1])]=1;
dp[1][1][val(b[1][1]-a[1][1])]=1;
```
最后，完整代码来一波。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int h,w;
const int L=90;
int a[L][L]; 
int b[L][L];
int dp[L][L][30000];
int val(int k){
	return k+12720;
}
bool check(int k){
	return k<=12720&&k>=-12720;
}
int ans=12720;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>h>>w;
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			cin>>b[i][j];
		}
	}
	dp[1][1][val(a[1][1]-b[1][1])]=1;
	dp[1][1][val(b[1][1]-a[1][1])]=1;
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			if(i==1&&j==1){
				continue;
			}
			for(int k=-12720;k<=12720;k++){
				int y=a[i][j]-b[i][j];
				if((check(k-y)&&dp[i-1][j][val(k-y)])||(check(k+y)&&dp[i-1][j][val(k+y)])||(check(k-y)&&dp[i][j-1][val(k-y)])||(check(k+y)&&dp[i][j-1][val(k+y)])){
					dp[i][j][val(k)]=1;
				}
			}
		}
	}
	for(int k=-12720;k<=12720;k++){
		if(dp[h][w][val(k)]==1){
			ans=min(ans,abs(k));
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：uncle_steve (赞：0)

**思维难度：DP……（微水）**

令 $f_{i,j,k}$ 为到了 $i,j$ 差值为 $k$ 的方案是否存在。

假设当前走到 $(i,j)$，两个数字的差值为 $|a_{ij}-b_{ij}|$，那么状态转移就是：

$f[i][j][k\pm cha]=f[i-1][j][k]\texttt{if}(f[i-1][j][k]=\texttt{True})$

$f[i][j][k\pm cha]=f[i][j-1][k]\texttt{if}(f[i][j-1][k]=\texttt{True})$

可以用 bitset 来优化。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=85,M=6450;
bool f[N][N][M<<2];
int a[N][N],b[N][N]; 
int main()
{
    int h,w;cin>>h>>w;int m=12800;
    for(int i=1;i<=h;i++){
        for(int j=1;j<=w;j++){
            cin>>a[i][j];
        }
    }
    for(int i=1;i<=h;i++){
        for(int j=1;j<=w;j++){
            cin>>b[i][j];
        }
    }
    f[1][0][m]=true;
    for(int i=1;i<=h;i++){
        for(int j=1;j<=w;j++){
            for(int k=0;k<=2*m;k++){
                f[i][j][k]|=f[i-1][j][k-(a[i][j]-b[i][j])];
                f[i][j][k]|=f[i-1][j][k-(b[i][j]-a[i][j])];
                f[i][j][k]|=f[i][j-1][k-(a[i][j]-b[i][j])];
                f[i][j][k]|=f[i][j-1][k-(b[i][j]-a[i][j])];
            }
        }
    }
    int ans=1e9;
    for(int i=0;i<=2*m;i++){
        if(f[h][w][i]) ans=min(ans,abs(i-m));
    }
    cout<<ans<<endl;
    
    return 0;
}
```

---

## 作者：__Creeper__ (赞：0)

## 思路

动态规划。定义状态 $f[i][j][k]$ 表示到 $i$ 行 $j$ 列时，差值为 $k$ 能否满足。根据题意，我们可以分为两种情况。

- 从 $i-1,j$ 走来：`f[i][j][k] |= f[i - 1][j][k - ( a[i][j] - b[i][j] )] || f[i][j - 1][k - ( a[i][j] - b[i][j] )]`
- 从 $i,j-1$ 走来：`f[i][j][k] |= f[i - 1][j][k + ( a[i][j] - b[i][j] )] || f[i][j - 1][k + ( a[i][j] - b[i][j] )]`

由于本题差值有可能为负数，所以每次需要加上最大差值。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 85, T = 12720;
int n, m, a[N][N], b[N][N];
bool f[N][N][2 * T + 5];

void solve()
{
	cin >> n >> m;
	for ( int i = 1; i <= n; i++ )
	{
		for ( int j = 1; j <= m; j++ ) cin >> a[i][j];
	}
	for ( int i = 1; i <= n; i++ )
	{
		for ( int j = 1; j <= m; j++ ) cin >> b[i][j];
	}
	f[0][1][T] = f[1][0][T] = 1;
	for ( int i = 1; i <= n; i++ )
	{
		for ( int j = 1; j <= m; j++ )
		{
			for ( int k = 0; k <= 2 * T; k++ )
			{
				// 不要忘记判断边界
				if ( k - ( a[i][j] - b[i][j] ) >= 0 ) f[i][j][k] |= ( f[i - 1][j][k - ( a[i][j] - b[i][j] )] || f[i][j - 1][k - ( a[i][j] - b[i][j] )] );
				if ( k + ( a[i][j] - b[i][j] ) <= 2 * T ) f[i][j][k] |= ( f[i - 1][j][k + ( a[i][j] - b[i][j] )] || f[i][j - 1][k + ( a[i][j] - b[i][j] )] );
			}
		}
	}
	for ( int i = 0; i <= T; i++ )
	{
		if ( f[n][m][T - i] || f[n][m][T + i] )
		{
			cout << i;
			return;
		}
	}
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t = 1;
//	cin >> t;
	while ( t-- ) solve();
	return 0;
}
```

---

## 作者：lovely_qiqi (赞：0)

## 思路

**关键在于调整零点和升维动态规划。**

此题类似 dp 中的常见题型：矩阵转移。

但是又发现如果按以前的方法不行。

所以考虑升维动规。

定义 $f_{i,j,k}$ 为在 $(i,j)$ 方格能否使值为 $k$。

于是根据题意得到方程：

设 $t=a_{i,j}-b_{i,j}$，于是有：
$$f_{i,j,k}=f_{i,j-1,k-t}||f_{i,j-1,k+t}||f_{i,j+1,k+t}||f_{i,j+1,k-t}$$


所以解决了？

不，需要注意的是 $k-t$，$k+t$ 都可能超出上界或者下界，所以让所有数整体加上一个大值。

详见代码。


## 代码

```cpp
#include<bits/stdc++.h>
#define add 13000
//160*80再向上取一点
using namespace std;
int h,w,a[110][110],b[110][110],tmp;
bool dp[110][110][30010];//dp开两倍，不然会爆掉
int main(){
	scanf("%d%d",&h,&w);
	for(int i=1;i<=h;i++) for(int j=1;j<=w;j++) scanf("%d",&a[i][j]);
	for(int i=1;i<=h;i++) for(int j=1;j<=w;j++) scanf("%d",&b[i][j]);
	//初始化读入
	dp[1][0][add]=dp[0][1][add]=true;
	//注意每个dp的状态都会加上add，才能保证不是负数
	//当一开始是肯定为0，所以填true
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){//遍历整个数组
			for(int k=0;k<=2*add;k++){
				tmp=abs(a[i][j]-b[i][j]);//变化量
				if(k-tmp>=0) dp[i][j][k]|=(dp[i][j-1][k-tmp]||dp[i-1][j][k-tmp]);
				if(k+tmp<=2*add) dp[i][j][k]|=(dp[i][j-1][k+tmp]||dp[i-1][j][k+tmp]);
				//dp方程
			}
		}
	}
	for(int k=0;k<=add;k++){
		if(dp[h][w][k+add]||dp[h][w][add-k]){//如果说他的对应量可以取到则输出
			printf("%d",k);
			return 0;
		}
	}
	return 0;
}

```

---

## 作者：bwartist (赞：0)

“红色数字总和” 减 “蓝色数字总和” 可以看成每一步的时候 “红色格子减蓝色格子” 的总和

$dp_{i,j,k}$ 为**走到第 $(i,j)$ 点时，红色总和减蓝色总和的值为 $k$** 能否成立。

从两个方面分类讨论：

>从哪个方向来的 

>这个点这个点要涂蓝色还是红色

设 $c_{i,j}=a_{i,j}-b_{i,j}$

所以推出 ： `dp[i][j][k] = (dp[i-1][j][k+c[i][j]]|dp[i-1][j][k-c[i][j]])|(dp[i][j-1][k+c[i][j]]|dp[i][j-1][k-c[i][j]]);`

细节：

1. 初始值只把 $dp_{0,1}$ 和 $dp_{1,0}$ 设置成0，不能把所有 $dp_{0,i}$ 和   $dp_{i,0}$ 设置成00，因为起始位置不能从任意边缘进入。

2. 因为红色总和减蓝色总和的值可能为负数，所以在实际写程序的时候要把 $k$ 加 $12800$（就是答案可能达到的最大值），这样就能保证 $k>0$，不会有越界的情况。

Code :
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, a[85][85], b[85][85], c[85][85];
bool dp[85][85][30000];
int main () {
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf ("%d", &a[i][j]);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf ("%d", &b[i][j]);
			c[i][j] = a[i][j] - b[i][j];
		}
	}	
	dp[0][0][12800] = true;
	dp[1][0][12800] = true;
	dp[0][1][12800] = true;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int k = 1; k <= 12800*2; k++) {
				dp[i][j][k] = (dp[i-1][j][k+c[i][j]]|dp[i-1][j][k-c[i][j]])|(dp[i][j-1][k+c[i][j]]|dp[i][j-1][k-c[i][j]]);
			}
		}
	}
	int ans;
	for (int k = 12800; k <= 12800*2; k++)	{
		if (dp[n][m][k]) {
			ans = k - 12800;
			break;
		}
	}
	for (int k = 12800; k >= 0; k--) {
		if (dp[n][m][k]) {
			ans = min(ans, 12800 - k);
			break;
		}
	}
	printf ("%d", ans);
	return 0;
}
```


---

## 作者：Unnamed114514 (赞：0)

看到本题，我们可以发现 $H,W,a_{i,j},b_{i,j}$ 都很小，我们可以设 $dp_{i,j,k}$ 表示 $(i,j)$ 这个位置的差值为 $k$ 时是否可以选择。我们一共有 $4$ 种情况，分别是从上面走和从左边走，以及选择 $a_{i,j}$ 和选择 $b_{i,j}$。然后我们可以用 $0/1$ 表示差值为 $k$ 时的答案。初始化 $dp_{1,1}$ 选择 $a_{1,1}$ 和 $b_{1,1}$ 的情况，时间复杂度 $O(25600\times n^2)$。
### AC Code:
```cpp
#include<bits/stdc++.h>
#define dp(a,b,c) dp[a][b][c+12800]
using namespace std;
inline int read(){
	int res=0,f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
		f|=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9')
		res=(res<<1)+(res<<3)+(ch^'0'),ch=getchar();
	return res;
}
int n,m,a[85][85],b[85][85],dp[85][85][25605];
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			a[i][j]=read();		
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			a[i][j]-=read();
	dp(1,1,a[1][1])=dp(1,1,-a[1][1])=1;//初始化
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			for(int k=-12720;k<=12720;++k)
				dp(i,j,k)|=dp(i-1,j,k-a[i][j])|dp(i-1,j,k+a[i][j])|dp(i,j-1,k-a[i][j])|dp(i,j-1,k+a[i][j]);//转移
	for(int i=0;i<=12800;++i)
		if(dp(n,m,i)){
			printf("%d\n",i);
			return 0;
		}
	return 0;
} 
```
### Tips
1. 对于负数的情况，我们可以直接宏定义求解。

2. 因为 $dp_{1,1}$ 初始化的问题，所以转移时使用 `|=`。

3. 因为四种情况只有一种成立即可，所以方程用 `|`。

---

## 作者：Otomachi_Una_ (赞：0)

一道 dp 题，用 $f_{i,j,k}$ 表示在 $i$ 行 $j$ 列的格子是否可以得到差值为 $k$ 的方案，得到转移方程：

$$f_{i,j,k}=(f_{i,j-1,k+a_{i,j}-b_{i,j}} || f_{i,j-1,k-a_{i,j}+b_{i,j}}||f_{i-1,j,k+a_{i,j}-b_{i,j}}||f_{i-1,j,k-a_{i,j}+b_{i,j}})$$

然后就做完了。

代码：

```cpp
#include<cstdio>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=85;
const int MR=6405;
int h,w;
int a[MAXN][MAXN],b[MAXN][MAXN];
bool f[MAXN][MAXN][2*MR];//f[i][j][k]表示i行j列是否可以差为k-MR
int main(){
	cin>>h>>w;
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
			cin>>a[i][j];
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
			cin>>b[i][j];
	f[0][1][MR]=1;
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++){
			int c=abs(a[i][j]-b[i][j]);//记录差值
			for(int k=1;k<2*MR;k++){
				if(k+c<2*MR)
					f[i][j][k]=(f[i][j][k]||f[i][j-1][k+c]||f[i-1][j][k+c]);
				if(k-c>0)
					f[i][j][k]=(f[i][j][k]||f[i-1][j][k-c]||f[i][j-1][k-c]);
			}
		}
	for(int i=0;;i++)
		if(f[h][w][i+MR]){
			cout<<i;
			return 0;
		}
}
```


---

