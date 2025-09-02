# [CCC 2025 Junior] Connecting Territories

## 题目背景

本题满分 15 分。

## 题目描述

Ava 正在一个由格子组成的网格上玩策略游戏。每个格子都有一个对应的花费。当从左到右逐行读取格子的花费时，会呈现一个由前 $M$ 个正整数按递增顺序重复组成的模式：$1, 2, 3, \dots , M, 1, 2, 3, \dots , M, 1, 2, 3, \dots$。在这个模式中，$M$ 表示格子的最大花费。在示例网格中，$M$ 等于 $5$。

![](https://cdn.luogu.com.cn/upload/image_hosting/wbyl4yjv.png)

Ava 需要在每一行购买一个格子，以构建一条从上领地（第一行格子上方）通往下领地（最后一行格子下方）的连通路径。第一个购买的格子必须在第一行。随后购买的每个格子必须与上一个购买的格子共享一条边或一个角。在示例网格中，Ava 的连通路径总花费为 $9$。

![](https://cdn.luogu.com.cn/upload/image_hosting/5h5lj684.png)

给定一个格子网格，你的任务是确定从上领地到下领地的连通路径的最小花费。

## 说明/提示

**样例输入输出解释**

每个格子的花费如图所示。Ava 应购买的格子序列（绿色高亮部分）使得连通路径的花费最小。

![](https://cdn.luogu.com.cn/upload/image_hosting/2onq6n9o.png)

以下表格展示了 15 分的分配情况：

|分值|描述|数据范围|
|:-:|:-:|:-:|
|3|网格有两行且最多十列。|$R = 2$ 且 $C \leq 10$|
|8|网格最多十行且最多十列。|$R \leq 10$ 且 $C \leq 10$|
|2|网格最多 100 行且最多 100 列。|$R \leq 100$ 且 $C \leq 100$|
|2|网格可能非常大。|$R \leq 20\,000$ 且 $C \leq 20\,000$|

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
5
7```

### 输出

```
6```

# 题解

## 作者：This_is_my_choice (赞：2)

终于有题解可以写了。

# solution

虽然一眼 dp 但这题真的是橙吗？

题目大意其它题解有了我就不说了。

### 13pts 做法：

首先处理第一列和最后一列的特殊情况，可以将它们初始化为最大值，然后再推 dp 式子，很容易可以得出: $dp[i][j]=\min(dp[i-1][j-1],\min(dp[i-1][j],dp[i-1][j+1]))+h$ 

但是！

空间会超。

于是正解来了。

### 15pts 做法

可以使用滚动数组优化，因为它只需要上一行的数值，不用全部记录。

 $O(RC)$  可以过，主要是优化空间。

 ### AC CODE

 
```
#include<bits/stdc++.h>
using namespace std;
int dp[2][20005];
int main(){
	//Write the code here
	//Come
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int r,c,m;
	cin>>r>>c>>m;
    int mn=INT_MAX;
    int h=0;
    for(int i=1;i<=r;i++){
    	for(int j=1;j<=c;j++){
            if(h+1>m){
            	h=1;
			}else{
				h++;
			}
            if(j>1){
            	dp[1][j]=min(dp[1][j],dp[0][j-1]);
			}
            if(j<c){
            	dp[1][j]=min(dp[1][j],dp[0][j+1]);
			}
            dp[1][j]+=h;
            if(i==r){
            	mn=min(mn,dp[1][j]);
			}
        }
        for(int j=1;j<=c;j++)dp[0][j]=dp[1][j];
	}
    cout<<mn;
    return 0;
}
//LMAO
//Code by chc
```

## Thank you for reading!

---

## 作者：Bill_luogu (赞：2)

看完此题，容易想到动态规划。

设 $dp_{i,j}$ 为走到当前格子 $(i,j)$ 时的最小花费，有三种情况：
$$dp_{i,j}=\begin{cases}\min(dp_{i,j},dp_{i-1,j+1})+a_{i,j}&j=1\\\min(dp_{i-1,j-1},dp_{i-1,j})+a_{i,j}&j=m\\\min(dp_{i-1,j-1},dp_{i-1,j},dp_{i-1,j+1})+a_{i,j}&1<j<m\end{cases}$$
于是自信提交
![](https://cdn.luogu.com.cn/upload/image_hosting/j4sqzz9t.png)
空间炸了！  
考虑使用滚动数组。  
观察状态转移方程，发现当前的 $dp_{i,j}$ 只和上一行有关联，于是优化：
```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[2][20010];
int n,m,maxx,minn;
int cnt;
int main()
{
	cin>>n>>m>>maxx;
	minn=0x3f3f3f3f;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
            if(++cnt>maxx)cnt=1;//千万别写成cnt=cnt%maxx+1，不然会TLE
            //状态转移方程
            if(j>1)dp[1][j]=min(dp[1][j],dp[0][j-1]);
            if(j<m)dp[1][j]=min(dp[1][j],dp[0][j+1]);
            dp[1][j]+=cnt;
			if(i==n)minn=min(minn,dp[1][j]);//取最小值
		}
		for(int j=1;j<=m;j++)
			dp[0][j]=dp[1][j];
	}
	cout<<minn;
	return 0;
}
```

---

## 作者：uncle_steve (赞：2)

**算法：滚动数组+ DP**

## 解题思路：

此题与 [p1002 过河卒](https://www.luogu.com.cn/problem/P1002) 采用相似做法。

- 定义 $dp_{i,j}$ 为走到坐标为 $i,j$ 的格子时花费的最小代价。因为**购买的每个格子必须与上一个购买的格子共享一条边或一个角**，不难得出转移方程：
  
  $dp[i][j]=\min(dp[i-1][j],\min(dp[i-1][j-1],dp[0][j+1])))$

- 再处理第一列与最后一列的特殊情况，即可得到下列方程：

$dp[i][j] = \begin{cases}
  \min(dp[i-1][j],dp[i-1][j+1]) & j=1 \\
  \min(dp[i-1][j],dp[i-1][j-1]) & j=c \\
  \min(dp[i-1][j],\min(dp[i-1][j-1],dp[0][j+1]))) & 2 \le j \le c-1
\end{cases}$

- 最后，如果处理到最后一行，记录最小答案即可。

空间复杂度 $O(RC)$。结束了？

因为 $R \le 20000$ 且 $C \le 20000$，空间会超。

### 优化做法：

- 由于我们发现，$dp[i][j]$ 的值只于上一行有关，即可定义一个滚动数组，动态记录此行答案。

- 当每行更新完后，将 $dp[0][j]$ 更新为 $dp[1][j]$ 即可。

**注意网格的初始化问题。**

## 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int r,c,m,dp[2][20005],t,minn=2e9;
int main()
{
    cin>>r>>c>>m;
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            if(++t>m) t=1;
            if(j==1) dp[1][j]=min(dp[0][j],dp[0][j+1]);//第一列 
			else if(j==c) dp[1][j]=min(dp[0][j],dp[0][j-1]);//最后一列 
			else dp[1][j]=min(dp[0][j],min(dp[0][j-1],dp[0][j+1]));
            dp[1][j]+=t;
            if(i==r) minn=min(minn,dp[1][j]);//如果是最后一排则记录最小值 
        }
        for(int j=1;j<=c;j++){
        	dp[0][j]=dp[1][j];//滚动更新 
		} 
    }
    cout<<minn<<endl;

    return 0;
}
```

---

## 作者：Zskioaert1106 (赞：2)

题目传送门：[P12613 [CCC 2025 Junior] Connecting Territories](https://www.luogu.com.cn/problem/P12613)

### 做题过程

因为从每行来看不具后效性，故定义 $dp_{i,j}$ 为走到第 $i$ 行第 $j$ 个格子时最小值。

容易想到方程 $dp_{i,j}=\min\limits_{k=\max(j-1,1)}^{\min(j+1,n)} dp_{i-1,k}$。

我赌你 $O(RC)$ 能过。

[空间炸了](https://www.luogu.com.cn/record/218598909)。

考虑优化：当枚举到第 $i$ 行时，第 $i-1$ 行之前的信息就没用了。因此考虑只存这两行的信息：$dp_{0,j}$ 代表上一行，$dp_{1,j}$ 代表这一行。每次走完一行就让 $dp_{0,j} \leftarrow dp_{1,j}$。

```cpp
#include<iostream>
using namespace std;
int n,m,s,cnt,dp[2][20004],ans=2e9;
int main(){
    cin>>n>>m>>s;
    while(n--){
        for(int j=1;j<=m;j++){
            if(++cnt>s)cnt=1;
         // dp[1][j]=dp[0][j];
            if(j>1)dp[1][j]=min(dp[1][j],dp[0][j-1]);
            if(j<m)dp[1][j]=min(dp[1][j],dp[0][j+1]);
            dp[1][j]+=cnt;
            if(!n)ans=min(ans,dp[1][j]);
        }
        for(int j=1;j<=m;j++)dp[0][j]=dp[1][j];
    }
    cout<<ans;
    return 0;
}
```

发现[开 O2 的情况下能过](https://www.luogu.com.cn/record/218599630)。

---

## 作者：kuaiCreator (赞：1)

## 题目大意
给定一个 $r\times c$ 的网格。分别从左往右从上往下填上 $1$ 至 $m$ 的循环数列，问从第一行开始每次可以走左下，正下，右下，走到最后一行的最小值。
## 解题思路
考虑DP。  
#### 定义状态
用 $f(i,j)$ 表示从第一行走到第 $i$ 行第 $j$ 列经过路径的最小值。  
#### 分解子问题
$$f(i,j)= \min(f(i-1,j-1),f(i-1,j),f(i-1,j+1))+a_{ij}$$  
其中 $a_{ij}=((i-1)\times c+j)\bmod m+1$  但是本题不建议用取模运算，会TLE，令一个变量 $a$ 不断自增，若超过 $m$ 就初始化为 $1$。
#### 边界状态
$$f(0,j) = 0$$
#### 问题答案
$$ans=\min\limits_{j=1}^n f(n,j)$$
#### 效率分析
时间复杂度和空间复杂度都为 $O(r\times c)$。

分析完发现 $r,c\le 2\times 10^4$ 肯定炸空间了，观察转移方程当前行状态只会从上一行转移，并且答案只需要从最后一行的状态获取。考虑奇偶滚动数组优化。

## 代码实现

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll r, c, m, dp[2][20005], ans = 1e18, a;
int main() {
	cin >> r >> c >> m;
	memset(dp, 0x3f, sizeof dp);
	for (int j = 1; j <= c; j++)
		dp[0][j] = 0;
	for (int i = 1; i <= r; ++i) {
		int now = i & 1, bef = (i - 1) & 1;	//当前行和上一行的奇偶
		for (int j = 1; j <= c; ++j) {
			a++;
			if (a > m) a = 1;
			dp[now][j] = min(dp[bef][j], min(dp[bef][j - 1], dp[bef][j + 1])) + a;
			if (i == r)	ans = min(ans, dp[now][j]);
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：dashabi35 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P12613)

这是一道十分基础的动态规划 + 优化的题。

当然了，由于这道题的状态转移方程很好推，所以只能评到橙题，但个人认为还是有一定难度的。

我作为一个 LIS 都不会的 dp 废物，居然一眼就看出来了状态转移方程，然后建图也是十分好建，但是一看数据，光是存储就要 $O(RC)$ （当时没考虑优化），直接 MLE 了，所以，决定先拿 $13$ 分。

首先，这个图是十分好建的，按横向一次枚举即可，可以和 dp 放在一起。

接下来开始推 dp 。

注： ```dp[i][j]``` 表示到 ```a[i][j]``` 的最小路程。

第一步，初始化， ```dp[1][j]=a[1][j]``` ，开始必须从上方走过。

第二步，推状态转移方程，由题意知 ```a[i][j]``` 能从 ```a[i-1][j-1]``` 、 ```a[i-1][j]``` 和 ```a[i-1][j+1]``` 走到，边界无法走到，设置为 $+\infty$ 即可，那么易得 ```dp[i][j]=min({dp[i-1][j-1],dp[i-1][j],dp[i-1][j+1]})+a[i][j]``` 。

最后找出 ```dp[c][j]``` 的最小值即可。

CODE:



```cpp
//建图+dp 期望得分 13 
#include<bits/stdc++.h>
using namespace std;
#define int long long
int r,c,m;
int a[105][105];
int dp[105][105];
int cnt,ans=2e9;
signed main()
{
	scanf("%lld%lld%lld",&r,&c,&m);
	for(int i=1;i<=r;++i)
	{
		dp[i][0]=dp[i][c+1]=0x3f3f3f3f;
	}//初始化 
	for(int i=1;i<=r;++i)
	{
		for(int j=1;j<=c;++j)
		{
			++cnt;
			if(cnt>m) 
			{
				cnt=1;
			}//枚举建图 
			a[i][j]=cnt;
			if(i==1)
			{
				dp[i][j]=a[i][j];
			}
			else
			{
				dp[i][j]=min({dp[i-1][j-1],dp[i-1][j],dp[i-1][j+1]})+a[i][j];
			}//状态转移 
			if(i==r)
			{
				ans=min(ans,dp[i][j]);
			}//求答案 
		}
	}
	printf("%lld",ans);
	return 0;
}
```


成功拿下 $13$ 分。

[提交记录](https://www.luogu.com.cn/record/219135134)

接下来拿剩下的 $2$ 分，那么就需要优化，主要是空间优化：

优化 1 ：发现数组 $a$ 只有当前状态有用到，可以用变量 $cnt$ 代替，直接删掉。

优化 2 ：发现 ```dp[i]``` 只和 ```dp[i-1]``` 有关，可以使用滚动数组优化。

然后就有了新的代码;



```cpp
//建图+dp 优化版期望得分 15 
#include<bits/stdc++.h>
using namespace std;
#define int long long
int r,c,m;
int dp[2][200005];
int cnt,ans=2e9;
signed main()
{
	scanf("%lld%lld%lld",&r,&c,&m);
	dp[0][0]=dp[0][c+1]=0x3f3f3f3f;//初始化 
	for(int i=1;i<=r;++i)
	{
		for(int j=1;j<=c;++j)
		{
			++cnt;
			if(cnt>m) 
			{
				cnt=1;
			}//枚举建图 
			if(i==1)
			{
				dp[1][j]=cnt;
			}
			else
			{
				dp[1][j]=min({dp[0][j-1],dp[0][j],dp[0][j+1]})+cnt;
			}//状态转移 
			if(i==r)
			{
				ans=min(ans,dp[1][j]);
			}//求答案 
		}
		for(int j=1;j<=c;++j)
		{
			dp[0][j]=dp[1][j];
		}//滚动数组 
	}
	printf("%lld",ans);
	return 0;
}
```


[提交记录](https://www.luogu.com.cn/record/219135712)

然后就 AC 了（十分有逻辑的代码）。

时间复杂度： $O(RC)$ ，不知道咋过的。

空间复杂度： $O(C)$ 。

小贴士：我一开始将代码中的 ```++cnt; if(cnt>m) cnt=1``` 这句代码写成了 ```cnt=cnt%m+1``` ，然后就 TLE 了。

---

## 作者：GeorgeDeng (赞：1)

明显 DP 题。

其实这道题和 [P1216](https://www.luogu.com.cn/problem/P1216) 非常像。

首先，我们不能够开 $(2\times 10^5) \times (2 \times 10^5)$ 的二维数组，所以考虑滚动优化。

为了 ~~偷懒~~ 算出第 $i$ 行第 $j$ 列是哪个数，我们用一个变量 $now$ 记录当前是哪个数。计算过程不用说了吧，每次加一，如果 $now=M+1$，那么 $now \larr 1$。

显然，第一行的答案就是它本身。因为是要求最小值，所以我们提前把最左边和最右边的东西赋值为 $+\infty$。

我们用 $pre_i$ 表示滚动数组中上一维的第 $i$ 个位置的最小价值，$dp_i$ 表示当前这一维的第 $i$ 个位置的最小价值。

显然，$dp_i$ 可以从 $pre_{i-1}, pre_i, pre_{i+1}$ 这三个点转移过来，那么我们就显而易见地推出了状态转移方程：

$$
dp_i=\min\left\{\begin{matrix} 
pre_{i-1}+now\\
pre_i+now\\
pre_{i+1}+now
\end{matrix}\right.
$$

最后，我们的答案就是 $dp$ 中的的最小值了。

思路非常简单，上代码！

```cpp
#include <iostream>
#define int long long//可能要开long long，反正这就是个好习惯
using namespace std;

int dp[20005];//滚动数组优化空间
int pre[20005];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,m,t;
    cin>>n>>m>>t;//命名习惯问题，不用纠结，分别对应题目中的R,C,M
    int now = 1;//记录当前是哪个数
    for(int i = 1;i<=m;i++){//提前处理出第一维
        pre[i] = now;
        //cout<<now<<' ';
        now++;
        if(now==t+1) now = 1;
    }
    //cout<<endl;
    pre[0] = pre[m+1] = 0x7fffffffffffffff;//防止边界的0影响结果
    for(int i = 2;i<=n;i++){
        for(int j = 1;j<=m;j++){
            dp[j] = min(pre[j-1],min(pre[j],pre[j+1]))+now;//刚刚推过的，把+now提出来和不提出来没有区别
            //cout<<dp[j]<<' ';
            now++;
            if(now==t+1) now = 1;
        }
        for(int j = 1;j<=m;j++){
            pre[j] = dp[j];//滚动数组
        }
        //cout<<endl;
    }
    int ans = 0x7fffffffffffffff;
    for(int i = 1;i<=m;i++){//求出答案
        ans = min(ans,dp[i]);
    }
    cout<<ans;
    return 0;
}
//完结撒花！
```

---

## 作者：蒟蒻whker (赞：0)

显然使用 DP。
### 思路

此题与 [P1176](https://www.luogu.com.cn/problem/P1176) 做法相似。

定义 $dp_{i,j}$ 为走到坐标为 $i,j$ 的格子时的最小代价。因为购买的每个格子必须与上一个购买的格子共享一条边或一个角，因此相当于左上角、正上方、右上角，得出：
  
  $dp_{i,j}=\min(dp_{i-1,j-1},dp_{i-1,j},dp_{i-1,j+1})$

再处理第一列与最后一列的特殊情况（在计算 $j-1$ 和 $j+1$ 时越界），即可得到下列方程：

$dp_{i,j} = \begin{cases}
  \min(dp_{i-1,j},dp_{i-1,j+1}) & j=1 \\
  \min(dp_{i-1,j},dp_{i-1,j-1}) & j=c \\
  \min(dp_{i-1,j},dp_{i-1,j-1},dp_{i-1,j+1}) & 2 \le j \le c-1
\end{cases}$

最后，如果处理到最后一行，记录最小答案即可。

空间复杂度 $O(RC)$，空间会超。

### 优化：

只需要定义两个数组 $last$，$dp$，$last_{i}$ 和 $dp_{i}$ 分别表示上一行和这一行第 $i$ 个位置的最小值，该行计算完后，令 $last_{i}=dp_{i}$ 即可。

注意：数组和记录最小值的变量一定要初始化。

### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int dp[20005]={},last[20005]={};
int r,c,m;
int main(){
	scanf("%d%d%d",&r,&c,&m);
	int s=0;
	int ans=0x3f3f3f3f;//初始化
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			if(++s>m)s=1;
			dp[j]=s;//计算当前格子
			if(j==1)dp[j]+=min(last[j],last[j+1]);//分成上述3种情况
			if(j>1&&j<c)dp[j]+=min(last[j],min(last[j+1],last[j-1]));
			if(j==c)dp[j]+=min(last[j],last[j-1]);	
		}
		for(int j=1;j<=c;j++){
		last[j]=dp[j];//更新滚动数组
		if(r==i)ans=min(ans,dp[j]);//取最小值
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：hzh17 (赞：0)

第一眼以为是 DFS，二维数组会爆空间。

```cpp
void dfs(int k,int x,int sum){

	if(k==n){
		minn=min(minn,sum);return;
			}
	if(k==0){
	
	for(int i=1;i<=y;i++){
		dfs(k+1,i,sum+a[k+1][i]);
	}
}
	else{
		for(int i=max(x-1,1);i<=min(y,x+1);i++){
			dfs(k+1,i,sum+a[k+1][i]);
		}
	}
}
```
进行 DP。

每个点的最小值为上一行相邻三个点中最小值加该点的值。

$$ dp_j  =\min \begin{cases}
  head_{j-1}+t\\
  head_j+t\\
  head_{j+1}+t\end{cases}$$

其中 head 为上一行的值，t 为该点原值。

但要注意，当该点为边界时，要小心越界。


$$j+1 \le C$$

$$i-1 \ge 1$$
  
然后在最后一行中找到最小值即为答案。

上 AC 代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int y,m,x,t,dp[20100],head[20100],minn=1e9;int n;
int main()
{

	cin>>x>>y>>m;
	for(int i=1;i<=x;i++){
	for(int j=1;j<=y;j++){	
	if(i!=1)dp[j]=min(head[max(j-1,1)],
min(head[j],head[min(j+1,y)]));//状态转移，小心越界
	if(t==m)t=0;dp[j]+=++t;//每点初值
	}
	if(i==x){
		for(int j=1;j<=y;j++)
		minn=min(dp[j],minn);//末行最小值
	}
	for(int j=1;j<=y;j++)head[j]=dp[j];
	
}
	cout<<minn;
    return 0;
}
```

---

## 作者：Na1L0n9 (赞：0)

# Solution
## 思路
比较明显的 dp，设 $dp[i][j]$ 为抵达 $(i,j)$ 时的最小花费，$v$ 表示当前位置的花费，则有转移方程：$dp[i][j]=\min(dp[i-1][j-1],dp[i-1][j],dp[i-1][j+1])+v$。

我们可以打出以下代码：

```cpp
    memset(dp, 127, sizeof(dp)); // 只是核心代码
    for (int i = 1; i <= c; i++) {
        dp[0][i] = 0;
    }
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			t++;
            if (t > m) {
                t = 1;
            }
			dp[i][j] = min({dp[i - 1][j - 1], dp[i - 1][j], dp[i - 1][j + 1]}) + t; 
		}
	}
```
但是，由于 $r$ 和 $c$ 的数据范围较大，这个代码并不能通过本题。

注意到 dp 的转移只和上一行有关，所以考虑使用滚动数组进行优化，便有了最终的代码。
## Code

```
#include <bits/stdc++.h>
#define Write ios::sync_with_stdio(0);
#define by cin.tie(0);
#define AquaDaMean1e cout.tie(0);
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 10;
const int MOD = 998244353;
int r, c, m, ans = INT_MAX, dp[2][N], t;
int main() {
	Write by AquaDaMean1e
	cin >> r >> c >> m;
    memset(dp, 127, sizeof(dp));
    for (int i = 1; i <= c; i++) {
        dp[0][i] = 0;
    }
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			t++;
            if (t > m) {
                t = 1;
            }
			dp[1][j] = min({dp[0][j - 1], dp[0][j], dp[0][j + 1]}) + t; 
		}
		for (int j = 1; j <= c; j++) {
			dp[0][j] = dp[1][j];
		}
	}
	for (int i = 1; i <= c; i++) {
		ans = min(ans, dp[1][i]);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：HG27895 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P12613)

# 题意

给定一个花费递增且最大值为 $M$ 的 $R$ 行 $C$ 列的网格，求从第一行走到最后一行的最小花费。

# 思路

一眼 DP。

考虑一个 DP 数组 $f$，令 $f_{i,j}$ 表示走到第 $i$ 行第 $j$ 列的最小花费。因为只能从左上方或正上方或右上方走过来，所以转移方程也很显然，即 $f_{i,j}=\min(f_{i,j},\min(f_{i,j-1},f_{i,j+1}))$。如果是第一行或最后一行，你们就会取最小值 $0$，所以要初始化为一个最大值。但如果是第一行，所有数都为最大值，答案错误，所以还要将第一行全部初始化为 $0$。最后，再对最后一行取最小值，就得到了答案。

于是，我们得到了 MLE 的好成绩。

一看数据范围：$R,C\le20000$，考虑滚动数组。

因为每次的更新只跟上一次的更新有关，所以只需记录上一行和现在一行，等求完现在一行后，更新到上一行就行了。这样，我们就把第一维压到了 $2$。

# AC Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define fi(l) freopen(l".in","r",stdin)
#define fo(l) freopen(l".out","w",stdout)
//#pragma G++ optimize(2)
using namespace std;
inline ll read()
{
	ll v=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		v=v*10+c-'0';
		c=getchar();
	}
	return v*f;
}
inline void out(ll x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x<10)putchar(x+'0');
	else 
	{
		out(x/10);
		putchar(x%10+'0');
	}
}
inline ll ksm(ll a,ll b,ll p)
{
	ll ans=1;
	for(;b;b>>=1,a=a*a%p)
	{
		if(b&1)ans=ans*a%p;
	}
	return ans;
}
ll f[2][20020];//DP数组
int main()
{
	//fi("");
	//fo("");
	//ios::sync_with_stdio(0);
	//cin.tie(0);
	//cout.tie(0);
	ll r=read(),c=read(),m=read();//如题意描述
	ll t=1;//t表示现在这格应为t
	ll ans=LONG_LONG_MAX;//ans初始化为最大值，方便待会取min
	memset(f,0x7f7f7f,sizeof(f));
	for(ll i=1;i<=r;i++)
	{
		if(i==1)//初始化第1行为0
		{
			for(ll j=1;j<=c;j++)
			{
				f[0][j]=0;
			}
		}
		for(ll j=1;j<=c;j++)
		{
			f[1][j]=min(f[0][j],min(f[0][j+1],f[0][j-1]))+t;//转移方程加上当前格的花费
			if(t==m)t=1;//更新当前格
			else t++;
			if(i==r)ans=min(ans,f[1][j]);//现在是最后一行，更新答案
		}
		for(ll j=1;j<=c;j++)
		{
			f[0][j]=f[1][j];//更新滚动数组
		}
	}
	out(ans);
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

##  题目大意
[题目传送门](https://www.luogu.com.cn/problem/P12613)
## 题目分析
希望审核大大给过。

这道题一眼 dp，可是我们看看数据，$(2 \times 10^4) \times (2 \times 10^4)$ 的大小一看内存就会炸，所以需要使用滚动数组。

程序中定义数组 $f_{i,j}$ 为走到第 $i$ 行第 $j$ 个格子时最小值。

根据题意，不难看出动态转移方程为：
$$ 
f_{i,j} = \min_{k = \max(j-1,1)}^{\min(j+1,n)} f_{i-1,k} 
$$
只需按照方程写即可。（一定要用滚动数组啊！！！~~不然会 M 掉~~）
## 题目[代码](https://www.luogu.com.cn/record/218644452)
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define speed ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
int n,m,s,cnt,f[2][20004],ans=2e9;
signed main(){
	speed
    cin>>n>>m>>s;
    while(n--){
        for(int j=1;j<=m;j++){
            if(++cnt>s)cnt=1;
            if(j!=1)f[1][j]=min(f[1][j],f[0][j-1]);
            if(j<m)f[1][j]=min(f[1][j],f[0][j+1]); //转移方程 
            f[1][j]+=cnt;
            if(n==0)ans=min(ans,f[1][j]);
        }
        for(int j=1;j<=m;j++)f[0][j]=f[1][j];
    }
    cout<<ans;
    return 0;
}
```

---

