# Timetable

## 题目描述

Ivan is a student at Berland State University (BSU). There are $ n $ days in Berland week, and each of these days Ivan might have some classes at the university.

There are $ m $ working hours during each Berland day, and each lesson at the university lasts exactly one hour. If at some day Ivan's first lesson is during $ i $ -th hour, and last lesson is during $ j $ -th hour, then he spends $ j-i+1 $ hours in the university during this day. If there are no lessons during some day, then Ivan stays at home and therefore spends $ 0 $ hours in the university.

Ivan doesn't like to spend a lot of time in the university, so he has decided to skip some lessons. He cannot skip more than $ k $ lessons during the week. After deciding which lessons he should skip and which he should attend, every day Ivan will enter the university right before the start of the first lesson he does not skip, and leave it after the end of the last lesson he decides to attend. If Ivan skips all lessons during some day, he doesn't go to the university that day at all.

Given $ n $ , $ m $ , $ k $ and Ivan's timetable, can you determine the minimum number of hours he has to spend in the university during one week, if he cannot skip more than $ k $ lessons?

## 说明/提示

In the first example Ivan can skip any of two lessons during the first day, so he spends $ 1 $ hour during the first day and $ 4 $ hours during the second day.

In the second example Ivan can't skip any lessons, so he spends $ 4 $ hours every day.

## 样例 #1

### 输入

```
2 5 1
01001
10110
```

### 输出

```
5
```

## 样例 #2

### 输入

```
2 5 0
01001
10110
```

### 输出

```
8
```

# 题解

## 作者：_Haoomff_ (赞：9)

#### Part 0 前置：

洛谷翻译够精简！我是看着原题面做的，原题面讲的就是一个人要翘课，请你求出他待在教学楼的时间。

------------

#### Part 1 题面

大概讲一下题面：某人每学期有 $n$ 天要上课，每天的课分为 $m$ 个时段。如果某天第一节课在第 $i$ 个时段，最后一节课在第 $j$ 个时段，则需要在教学楼待上 $j-i+1$ 的时间。而如果某天没有课的话，待在教学楼的时间为 $0$。某人不想上很多的课，所以他决定翘掉这学期的几节课（最多 $k$ 节），剩下没翘的课按照上面的规则去上。此外，如果他翘掉了某天全部的课，那么待在教学楼的时间也为 $0$。

------------

#### Part 2 思路

一道动态规划类背包问题。用 $c_{i,k}$ 表示第 $i$ 天翘 $k$ 节课待的最短时间，$f_{i,j}$ 表示某人待在教学楼的最短总时间。求 $c$ 数组很简单，同时易得 $f$ 数组的状态转移方程：

$$f_{i,j}=\min(f_{i,j},f_{i-1,j-k}+c_{i,k})$$


再求f数组时要注意，每天也可以不翘课（即翘 $0$ 节课）。

------------

#### Part 3 代码
代码不长，但是细节很多。

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int n,nn,m,c[505][505],s[505],a[505],f[505][505];
char ch;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>nn>>m;
	memset(c,0x3f,sizeof(c));//最小价值初始化无穷大 
	for(int i=1;i<=n;++i){
		for(int j=1;j<=nn;++j){
			cin>>ch;
			if(ch=='1')a[++s[i]]=j;//第i天课的数量+1，第s[i]节课在j时段 
		}
		c[i][s[i]]=0;//全翘了，c[i][k]表示第i天翘k节课待的最短时间 
		for(int len=1;len<=s[i];++len){//翘到剩len节课 
			for(int l=1;l+len-1<=s[i];++l){
				int r=l+len-1;//剩下的课是a[l]~a[r] 
				c[i][s[i]-len]=min(c[i][s[i]-len],a[r]-a[l]+1);
			}
		}
	}
	memset(f,0x3f,sizeof(f));//最小价值初始值无穷大 
	for(int j=0;j<=m;++j)f[0][j]=0;//待0天待的总时间为0 
	for(int i=1;i<=n;++i){
		for(int j=0;j<=m;++j)//最少翘0节，最多翘m节 
			for(int k=0;k<=min(j,s[i]);++k)
				f[i][j]=min(f[i][j],f[i-1][j-k]+c[i][k]);
	}
	cout<<f[n][m];
	return 0;
}
```

---

## 作者：天泽龟 (赞：5)

 上网找分组背包找到这题，感觉还是很有思维性的，固写文以记之。

## 此题难点有二：

1. 首先的难点便是怎么将本题转换为背包模型。

我们可以看出对于每一天翘多少课所得到的价值都是互相独立的，那么就很容易想到将每一天都看成一个物品组，翘不同数量的课可以达到不同的**最大价值**，然后跑分组背包即可。

但由于翘课顺序不同导致的剩余价值也不同，所以直接贪心递推地删点是不可取的。

2. 于是第二个难点便是**每一天翘课所得到的最大价值**应如何计算

我们考虑搞一个辅助DP，设$s[i][j]$为第i天翘了j节课所达到的最大价值。

由于我们翘课只有从两边翘才可达到最优，那我们对于一个确定的j，**可以分别枚举左右两边翘课的数量**。

我们设$g[i][j]$为第i天第j节课的时间节点，$pm_i$为第i天不翘课的最长时间，$cl_i$表示第i天总课数，就可得到如下式子：
$$s[i][j]=Max_{(0\leq p\leq max(cl_i,k))} \begin{Bmatrix} g[i][j-p]-g[i][p]+1\end{Bmatrix}$$


$P.S.:$由于我们定义的价值是**翘课所减少的时间**，所以最后要统一用$s[i][j]=pm_i-s[i][j]$更新，这样就可以跑裸的分组背包板子啦！

放上丑陋的代码：

```cpp
#include <iostream>
#include <cstring>
using namespace std;
int s[1000][1000],f[1000],g[1000][1000];
int n,m,k,sum; char c;

int dis(int i,int x,int y){return (g[i][x]-g[i][y]+1);}

int main()
{
	cin>>n>>m>>k; memset(s,0x3f,sizeof(s));
	for (int i=1;i<=n;i++)
	for (int j=1;j<=m;j++) {cin>>c; 
		if (c=='1') g[i][++g[i][0]]=j;}
//~~~~~
	for (int i=1;i<=n;i++)
	{
		int pm=g[i][0],ll=g[i][pm]-g[i][1]+1; s[i][0]=ll; s[i][pm]=0;
		if (pm==0) continue; else 
		for (int p=1;p<=min(k,g[i][0]);p++)//skip p classes in total
			for (int j=0;j<=p;j++) if (pm-(p-j)>=j+1) s[i][p]=min(s[i][p],dis(i,pm-(p-j),j+1));  //skip j before
		for (int p=0;p<=min(g[i][0],k);p++) s[i][p]=ll-s[i][p];
		 sum+=ll;
	}

	for (int i=1;i<=n;i++)
	for (int j=k;j>=1;j--)
	for (int p=0;p<=min(g[i][0],k);p++) 
		if (j>=p) f[j]=max(f[j],f[j-p]+s[i][p]);
	cout<<sum-f[k]<<endl;
}

```

---

## 作者：AdzearDisjudge (赞：3)

**友情提醒：我是读英文题面做的，题解也是在洛谷提交前写的……结果发现你谷翻译太精简了，题目背景都没翻译……~~（本来是个挺有趣的逃学计划）~~所以……你们凑合着看吧 ~~嘤嘤嘤~~**

我们考虑dp求解。

令d[i][j]为到第i天为止，一共翘了j节课之后，Ivan最少要在学校呆着的时间。

不难想到，我们首先得知道对于每天我们逃t节课后这天最少要在学校煎熬多久。这样才能从dp[i-1]转移过来。

令p[i][j]表示第i天上j节课最少要在学校的时间（比维护逃j节课更简单些，不过我们得另开一个数组s,s[i]表示第i天有多少节课）。考虑用滑动窗口维护。令l,r为某个上课的时间点（l<=r），当l和r之间（包括l,r）恰有j节课时，更新p数组并右移l，否则只右移r即可。求p数组的复杂度为$O(n*m^{2})$。

接着d数组的维护就很显然了：d[i][j]=min{d[i-1][j-t]+p[i][s[i]-t]}。求d数组的复杂度为$O(n*k^{2})$。

~~最后的答案应该就是d[n][k]，不过我好像脑抽写了个min{d[n][i]}……不过不影响结果2333~~

总复杂度为$O(n*m^{2}+n*k^{2})$。

---

## 作者：Mav11Young (赞：2)

~~吐槽一下本题翻译，为什么会把花费代价和获得代价混起来。。。~~

题意：	在一个n*m的01矩阵中，去掉s个1（s<=k）,使得最后每行头尾两个1的距离和最小。



------------
挺显然的一道dp题，n,m都是小于等于500的，所以可以允许n^3。

f[i][j][0/1]表示第i行从左/右边开始去掉j个1后，剩下的头尾的1之间的距离。

ans[i][j]表示第i行去掉j个1后的剩下的最小距离。~~显然~~ans可由f推来

dp[i][j]表示第i行及以前一共去掉了j个1的前i行的最小距离，所以答案就是max(dp[n][i])(0<=i<=k)。~~显然~~dp可由ans推来。

思路大概就是这样，贴代码~~
```cpp
#include<bits/stdc++.h>
#define debug(a) cout<<#a<<"="<<a<<endl;
#define LL long long
#define re register
using namespace std;
const int N=505;
int a[N][N],f[N][N][2],ans[N][N],dp[N][N],c[N];
char s[N][N];
int main(){
	int n,m,K;
	scanf("%d%d%d",&n,&m,&K);
	for(re int i=1;i<=n;i++){
		scanf("%s",s[i]);
		for(re int j=0;j<m;j++)a[i][j+1]=s[i][j]-'0';
	}
	memset(ans,127,sizeof(ans));
	for(re int i=1;i<=n;i++){
		int cnt=0;
		for(re int j=1;j<=m;j++)
			if(a[i][j])f[i][cnt++][0]=j;
		cnt=0;
		for(re int j=m;j>=1;j--)
			if(a[i][j])f[i][cnt++][1]=j;
		c[i]=cnt;
		for(re int j=0;j<=cnt;j++)
			for(re int k=0;k+j<=cnt;k++){
				if(j+k==cnt)ans[i][j+k]=0;
				else ans[i][j+k]=min(ans[i][j+k],f[i][k][1]-f[i][j][0]+1);
			}
	}
	memset(dp,127,sizeof(dp));
	for(re int i=0;i<=c[1];i++)dp[1][i]=ans[1][i];
	for(re int i=2;i<=n;i++)
		for(re int j=0;j<=min(K,c[i]);j++)
			for(re int k=0;k+j<=K;k++)
				dp[i][j+k]=min(dp[i][j+k],dp[i-1][k]+ans[i][j]);
	int res=1e9;
	for(re int i=0;i<=K;i++)res=min(res,dp[n][i]);
	printf("%d\n",res);
	return 0;
}
```


---

## 作者：yuheng_wang080904 (赞：1)

## 题意

给定 $n(1\le n\le 500)$ 行 01 串，分别代表 $n$ 天的课程，0 代表不上，1 代表要上，每天 $m(1\le m\le 500)$ 节课。对于每一行所要花费的时间是行中第一个 1 和最后一个 1 之间的距离加一，现在你有魔法可以去掉 $k(0\le k\le 500)$ 个 1，问去掉不多于 $k$ 个 1 的情况下，需要花费的最少总时间。

## 思路

很明显是一道 dp 题。

由于时间复杂度的关系，我们需要先预处理数组 $du$。$du_{i,j}$ 表示第 $i$ 天跳 $j$ 节课后所要花费的最少时间。很明显我们应当跳最早的或最晚的课，跳当中的课根本不能使时间变短。因此我们可以假设跳 $x(0\le x\le j)$ 节最早的课，则跳 $j-x$ 节最晚的课，分别算出当天需要花费的时间，则 $du_{i,j}$ 则是这些时间中最短的。

接下来定义数组 $dp$。$dp_{i,j}$ 表示前 $i$ 天跳 $j$ 节课所要花费的最少时间。假设第 $i+1$ 天跳 $x(0\le x\le k-j)$ 节课。则有转移方程 $dp_{i+1,j+x}=min(dp_{i,j}+du_{i+1,x})$。假设共有 $sa$ 节要上的课，则最后结果即为 $dp_{n,min(k,sa)}$。

这个思路的总时间复杂度大约为 $O(n\times m^2+n\times k^2)$。

## 代码

接下来放上我的代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,c[505],sum[505],t[505][505],du[505][505],dp[505][505];
string s[505];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=500;i++){
	for(int j=0;j<=500;j++)du[i][j]=dp[i][j]=1e9;
    }
    for(int i=1;i<=n;i++){
	cin>>s[i];
	for(int j=0;j<s[i].size();j++){
	    if(s[i][j]=='1')c[i]++;
	}
	int p=0;
	for(int j=0;j<s[i].size();j++){
	    if(s[i][j]=='1')t[i][++p]=j;
	}
    }
    for(int i=1;i<=n;i++)sum[i]=sum[i-1]+c[i];
    for(int i=1;i<=n;i++){
	for(int j=0;j<=min(c[i],k);j++){
	    for(int x=j;x>=0;x--){
		if(x+1>c[i]-(j-x))du[i][j]=0;
		else du[i][j]=min(du[i][j],t[i][c[i]-(j-x)]-t[i][x+1]+1);
	    }
	}
    }
    for(int i=0;i<n;i++){
	for(int j=0;j<=min(sum[i+1],k);j++){
            for(int x=0;x<=min(c[i+1],k-j);x++)dp[i+1][j+x]=min(dp[i+1][j+x],dp[i][j]+du[i+1][x]);
	}
    }
    cout<<dp[n][min(sum[n],k)]<<endl;
    return 0;
}
```


---

## 作者：luckydrawbox (赞：1)

## 题意

给出一个 $n$ 行 $m$ 列的 01 串，对于每一行所要花费的代价是行中第一个 $1$ 和最后一个 $1$ 之间的距离**加一**，现在你有魔法可以去除掉 $k$ 个 $1$ ，问去掉不多于 $k$ 个 $1$ 的情况下，你所能获得的最小代价是多少。

## 分析

显然，每一行从首尾开始去掉 $1$ 才有贡献（指减少的代价），设某一行中 $1$ 的位置为 $a_1,a_2,…,a_{e+1}$，则从左往右删的贡献依次为 $a_2-a_1,a_3-a_2,…,a_{e+1}-a_{e},1$，于是设 $l_i$ 表示该行从左到右删除到第 $i$ 个 $1$ 的贡献（不删完），则 $l_i=a_{i+1}-a_i+l_{i-1}(1\le i\le e)$，同理设 $r_i$ 为该行从右到左删除到第 $i$ 个 $1$ 的贡献（不删完），则 $r_i=a_{e-i+2}-a_{e-i+1}+r_{i+1}(1\le i\le e)$。

再设 $w_i$ 为该行删 $i$ 个数的最大贡献，则 $w_i=\begin{cases}\max_{j=0}^il_j+r_{i-j}&1\le i\le e\\l_{i-1}+1&i=e+1\end{cases}$，这样这题就转化成一个分组背包了，设 $dp_{i,j}$ 表示前 $i$ 行删 $j$ 个 $1$ 的最大贡献，就有转移方程 $dp_{i,j}=\max_{o=0}^j dp_{i-1,o}+w_{j-o}$。（**Q**：$j-o>e+1$ 时会不会多算？**A**：多出的部分值为 $0$，不影响答案。）

最后 $\max_{i=1}^k dp_{n,i}$ 为可删除的最大代价，答案就是本来所有的代价和减去 $\max_{i=1}^k dp_{n,i}$。

实现时，我用 $\text{vector<int>}$ 类型的 $e$ 存储 $a_i-a_{i-1}$，并求出初始的代价和 $sum$；如果某行是有 $1$ 的，打上一个标记 $flag=1$，这样就能确定是否有删除到最后的 $1$，若没有就不需要在 $w$ 末尾处的贡献增加一个 $l_i+1$；因为状态转移方程中每一项仅仅与前一项有关，所以我又加了个滚动数组优化。
  
最终时间复杂度 $O(nm^2+nk^2)$，空间复杂度 $O(m)$。

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
const int N=510;
int n,m,k;
vector<int>e;
ll w[N],l[N],r[N],dp[2][N],sum,mx;
int main(){
	n=read();m=read();k=read();
	for(int i=1;i<=n;i++){
		bool flag=0;
		e.clear();
		for(int j=1,lst=0,x;j<=m;j++){
			scanf("%1d",&x);
			if(x){
				if(lst){
					e.push_back(j-lst);
					sum+=j-lst;
				}
				else{
					sum++;
					flag=1;
				}
				lst=j;
			}
		}
		memset(l,0,sizeof(l));
		memset(r,0,sizeof(r));
		memset(w,0,sizeof(w));
		for(int j=0;j<e.size();j++)
			l[j+1]=l[j]+e[j];
		for(int j=e.size()-1,o=0;j>=0;j--,o++)
			r[o+1]=r[o]+e[j];
		for(int j=1;j<=e.size();j++)
			for(int o=0;o<=j;o++)
				w[j]=max(w[j],l[o]+r[j-o]);
		if(flag)
			w[e.size()+1]=l[e.size()]+1;
		for(int j=1;j<=k;j++)
			for(int o=0;o<=j;o++)
				dp[i&1][j]=max(dp[i&1][j],dp[(i&1)^1][o]+w[j-o]);
	}
	for(int i=0;i<=k;i++)
		mx=max(mx,dp[n&1][i]);
	write(sum-mx);
	return 0;
}
```


---

## 作者：linziyang1 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF946D)

## 题目大意

题目翻译讲得很清楚了，这里不再赘述。

## 思路

我们只需处理出每一行删除若干个 $1$ 可得的最大减少的代价，再把每行当作一些花费为删除 $1$ 的数量、价值为得到的最大减少代价的物品，使用分组背包分配每行删除 $1$ 的数量，统计最大减少的代价即可。

考虑如何处理每行删除若干个 $1$ 获得的最大减少代价。容易发现，如果删除中间的 $1$，而不删除旁边的 $1$，对答案是没有贡献的。所以我们预处理出只删除若干个最左边的 $1$ 减少的代价和只删除若干个最右边的 $1$ 减少的代价，再枚举删除左边（或右边）$1$ 的个数，使用左右减少代价之和更新答案即可。

需要注意删除每行最后一个 $1$ 减少的代价是 $1$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int pre[505][505], suf[505][505]; // 全删左边减少的代价，全删右边减少的代价
int hang[505][505]; // 第一维行删除第二维个减少的最大代价
int f[505]; // 最终减少的最大代价
int a[505][505];
int flag[505][505], cnt[505]; // 标记每行中 1 的位置，每行中 1 的数量
int s[505]; // 每行初始代价
vector<int> w[505], c[505]; // 每个物品的价值，花费
int main() {
	int n, m, K;
	cin>>n>>m>>K;
	for (int i = 1; i <= n; ++i) {
		string st;
		cin>>st;
		for (int j =1; j <= m; ++j) {
			a[i][j]=st[j-1]-'0';
			if (a[i][j])flag[i][++cnt[i]]=j;
		}
		for (int j = 1; j < cnt[i]; ++j) {
			pre[i][j]=pre[i][j-1]+flag[i][j+1]-flag[i][j];
		} if (cnt[i]) pre[i][cnt[i]]=pre[i][cnt[i]-1]+1;
		for (int j = cnt[i]; j > 1; --j) {
			suf[i][cnt[i]-j+1]=suf[i][cnt[i]-j]+flag[i][j]-flag[i][j-1];
		}if (cnt[i]) suf[i][cnt[i]]=suf[i][cnt[i]-1]+1;
		s[i]=pre[i][cnt[i]];
		for (int j = 1; j < cnt[i]; ++j) {
			for (int k = 0; k <= j; ++k) {
				hang[i][j]=max(hang[i][j],pre[i][k]+suf[i][j-k]);
			}
		}
		hang[i][cnt[i]]=s[i];
	}
	int sum=0;
	for (int i = 1; i <= n; ++i) sum+=s[i];
	// 分组背包
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= cnt[i]; j++) {
			w[i].push_back(hang[i][j]);
			c[i].push_back(j);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = K; j >= 0; j--) {
			for (int k = 0; k < cnt[i]; k++) {
				if (j >= c[i][k]) {
  					f[j] = max(f[j], f[j - c[i][k]] + w[i][k]);
				}
			}
		}
	}
	cout << sum-f[K];
	return 0;
}
```

---

## 作者：_masppy_ (赞：0)

### 题目链接：[Link](https://www.luogu.com.cn/problem/CF946D)

&nbsp;

### 题目大意：
给定一个 $n$ 行 $m$ 列的 $01$ 串，让你在最多删除 $k$ 个 $1$ 的情况下，使得每行以第一个 $1$ 和最后一个 $1$ 为边界的区间内元素个数之和尽量小，并给出这个最小值

&nbsp;

### 解题思路：
不难想到用 `dp` 求解，然后考虑如何一步步处理问题。

首先可以发现 $0$ 对于答案并没有影响，于是在存储串时只记录 $1$ 的位置即可。然后考虑先求出每行中消除不同个数的 $1$ 时最小的答案，这里记为  $ldp_{i,j}$，代表第 $i$ 行消除 $j$ 个 $1$ 时的最小答案。由于消除时肯定是从两端向内消除，于是对于每对 $(i,j)$ ，枚举从左端消除的个数，这里记为 $q$，然后可以得出这个方程： 
$$ldp_{i,j}=\min(ldp_{i,j},a_{i,one_i-q}-a_{i,q+1})$$

$one_i$ 代表第 $i$ 行中 $i$ 的个数，$a$ 则为存储 $01$ 串的数组。

之后根据求出的 $ldp$，我们便可以递推求最终的 `dp` 数组了，我们可以记 $dp_{i,j}$ 为前 $i$ 行中消除 $j$ 个 $1$ 后可以得到的最小结果，那么对于第 $i$ 行，删除的 $j$ 个 $1$ 显然会有 $k$ 个是在前 $i-1$ 行中删除的，剩余的则是在第 $i$ 行中删除。于是显然的，我们可以枚举一下 $k$，然后通过这个转移方程转移：
$$dp_{i,j}=\min(dp_{i,j},dp_{i-1,k}+ldp_{i,j-k})$$

最后输出 $dp_{n,k}$ 即可。

代码如下，与前文可能有些出入，具体请看注释：
```cpp
int main(){
	//freopen("test.in","r",stdin);
	scanf("%d%d%d",&n,&m,&k);
	
	for(int i=1;i<=n;i++){
		char c[maxn];
		scanf("%s",c+1);
		for(int j=1;j<=m;j++){
			if(c[j]=='1') a[i][++one[i]]=j;//存储1出现位置
		}
	}
	memset(dp,0x3f,sizeof(dp));
	for(int i=0;i<=k;i++) dp[0][i]=0;
	memset(ldp,0x3f,sizeof(ldp));
	
	
	for(int i=1;i<=n;i++){
		ldp[i][one[i]]=0;
		ldp[i][one[i]-1]=1;
		for(int j=0;j<one[i]-1;j++){
			for(int q=1;q<=j+1;q++){//这里是枚举的q+1
				ldp[i][j]=min(a[i][q+one[i]-j-1]-a[i][q]+1,ldp[i][j]);
				//cout<<ldp[i][j]<<endl;
			}
		}
	}
	
	for(int i=1;i<=n;i++){
		for(int j=0;j<=k;j++){//枚举k
			for(int q=0;q<=one[i]&&q+j<=k;q++){//枚举第i行消除的1的个数
				dp[i][j+q]=min(dp[i][j+q],dp[i-1][j]+ldp[i][q]);
			}
		}
	}
	
	printf("%d",dp[n][k]);
	return 0;
}

```
完结撒花 OvO！！！

---

## 作者：XiaoQuQu (赞：0)

设 $f_{i,j}$ 表示考虑前 $i$ 天逃了 $j$ 节课最短上课的时间。

显然，我们只会逃两端的课（因为逃中间的课没有任何收益）。如果我们已知第 $i$ 天要逃 $j$ 节课，那么我们可以枚举一个 $l$ 表示在左边逃 $l$ 节课，那么在右边就要逃 $t_i-(j-l)$ 节课，其中 $t_i$ 代表第 $i$ 天一共有 $t_i$ 节课。

然后我们发现，第 $i$ 天逃 $j$ 节课的收益其实是固定下来的，与我们总共逃几节课没有任何关系，所以我们可以与处理出 $g_{i,j}$ 表示第 $i$ 天逃 $j$ 节课的最小的上课时间。

那么我们就有 $f_{i,j}=\min\limits_{l=1}^j(f_{i-1,l}+g_{i,j})$，其中我们枚举的 $l$ 代表前 $i-1$ 天逃 $l$ 节课。

```cpp
// Problem: D. Timetable
// Contest: Codeforces - Educational Codeforces Round 39 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/946/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid (l + r) >> 1
#define endl '\n'

const int MAXN = 505;
int n, m, k, f[MAXN][MAXN], b[MAXN][MAXN], t[MAXN], g[MAXN][MAXN], u[MAXN];
char s[MAXN][MAXN];

signed main(void) {
    ios::sync_with_stdio(false), cin.tie(NULL);
    cin >> n >> m >> k;
    memset(f, 0x3f, sizeof f); memset(g, 0x3f, sizeof g);
    for (int i = 1; i <= n; ++i) {
    	cin >> (s[i] + 1);
        for (int j = 1; j <= m; ++j) {
            if (s[i][j] == '1') {
                b[i][++t[i]] = j;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
    	for (int j = 0; j <= min(t[i], k); ++j) { 
    		if (t[i] == 0) g[i][j] = 0;
            else if (j == 0) g[i][j] = b[i][t[i]] - b[i][1] + 1;
            else if (j == t[i]) g[i][j] = 0;
            else for (int l = 0; l <= j; ++l) {
                int r = t[i] - (j - l);
                if (r < 0) continue;
                else g[i][j] = min(g[i][j], b[i][r] - b[i][l + 1] + 1);
            }
    	}
    }
    f[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
    	for (int j = 0; j <= t[i]; ++j) { 
            for (int l = 0; l <= k - j; ++l) {
                f[i][l + j] = min(f[i][l + j], f[i - 1][l] + g[i][j]);
            }
    	}
    }
    int ans = 0x7f7f7f7f;
    for (int i = 0; i <= k; ++i) ans = min(f[n][i], ans);
    cout << ans << endl;
    return 0;
}

```


---

## 作者：hegm (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF946D)

可以用背包的思想来看待它。

对于第 $i$ 行我们可以在 $1 \sim size_i$ 的代价中选择一个，也只能选择一个。

如果你选了代价 $k$ ,那么你就不能再选择其他代价。

类似于分组背包的同组之间的关系。

我们对于每一行 $i$ ，
枚举左右的总共删除数量 $j$ 。

$s_{i,j}$ 表示第 $i$ 行第 $j$ 个 $1$ 所在的位置

$ans_{i,j}=\min \limits _{l\in\{0\sim j\},r=j-l} s_{i,r}-s_{i,l}+1$ 。

以上就是本题的做法和思路，主要在于转化为分组背包。

如果没写过分组背包，这里有[模板](https://www.luogu.com.cn/problem/P1757)。

放上全部代码

```cpp
#include<bits/stdc++.h>
#define N 505
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,m,mp[N][N],k,size[N],num[N][N],cnt[N][N],dp[N],tot,awa;
int main()
{
	n=read();m=read();k=read();
	char c;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>c;
			mp[i][j]=c-'0';
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			size[i]+=bool(mp[i][j]);
			if(mp[i][j])num[i][size[i]]=j,awa++;
		}
	}
	for(int i=1,l,r;i<=n;i++)
	{
		cnt[i][0]=num[i][size[i]]-num[i][1]+1;
		if(size[i]==0)
		{
			cnt[i][0]=0;
			continue;
		}
		tot+=cnt[i][0];
		for(int j=1,con=min(size[i],k),ans;j<=con;j++)
		{
			ans=m+5;
			for(int l=0,r;l<=j;l++)
			{
				r=j-l;
				if(size[i]-r<1+l)continue;
				ans=min(ans,num[i][size[i]-r]-num[i][1+l]+1);
		    }
		    if(j==size[i])cnt[i][j]=cnt[i][0];
			else cnt[i][j]=cnt[i][0]-ans;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=k;j>=0;j--)
		{
			for(int p=1;p<=size[i];p++)
			{
				if(p>j)break;
				dp[j]=max(dp[j],dp[j-p]+cnt[i][p]);
			}
		}
	}
	if(awa<=k)cout<<0;
	else cout<<tot-dp[k];
	return 0;
}
```

---

## 作者：World_Creater (赞：0)

一道很有意思的 $\verb!DP!$ 题。  
我们可以预处理出删掉 $x$ 个 $1$ 还可以获得的价值，这部分我们记录所有 $1$ 出现的位置，显然删除两端的 $1$ 更优秀，于是我们使用贪心解决。

然后问题就变成了类似于一种背包的结构：对于每种物品，花费 $k_i$ 的代价，（即删掉 $k_i$ 个 $1$）可以获得 $v_i$ 的价值，直接使用背包解决。

复杂度 $O(nmk)$ 
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
char a[505][505];
int f[505][505],use[505][505],l[505],r[505],cnt1,cnt2;
int main()
{
	cin>>n>>m>>k;
	memset(use,0x3f,sizeof(use));
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		//puts("");
		cnt1=0,cnt2=0;
		for(int j=0;j<m;j++)
		{
			if(a[i][j]=='1') l[cnt1++]=j;
		}
		for(int j=m-1;j>=0;j--)
		{
			if(a[i][j]=='1') r[cnt2++]=j;
		}//记录位置
		for(int j=0;j<=k;j++)
		{
			for(int t=0;t<=j;t++)
			{
				use[i][j]=min(use[i][j],max(r[j-t]-l[t]+1,0));//use[i][j] 表示第i行删掉j个1的最小价值
			}
		}
	}
	memset(f,0x3f,sizeof(f));
	for(int i=0;i<=k;i++)
	{
		f[0][i]=use[0][i];
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<=k;j++)
		{
			for(int t=0;t<=j;t++)
			{
				f[i][j]=min(f[i][j],f[i-1][t]+use[i][j-t]);//背包
			}
		}
	cout<<f[n-1][k];
}
```

---

## 作者：D2T1 (赞：0)

[CF link](https://codeforces.com/problemset/problem/946/D) [Luogu link](https://www.luogu.com.cn/problem/CF946D)

细节有点多的水题。

设 $w_{i,j}$ 表示第 $i$ 行删掉 $j$ 个 `1` 后的最小花费代价，$f_{i,j}$ 表示前 $i$ 行删掉 $j$ 个 `1` 后的最小花费代价。

容易发现 $w$ 数组能够很容易地求到，接下来考虑 $f$ 数组。可以发现这是个背包模型，转移式子为：

$$f_{i,j} = \min\limits_{0\leq l\leq j\leq k}\{f_{i-1,l}+w_{i,j-l}\}$$

```cpp
//CF946D
#include <algorithm> 
#include <cstring>
#include <cstdio>
using namespace std;

const int N = 510;
int n, m, k, pos[N], w[N][N], f[N][N];
char s[N];

int main(){
	memset(w, 0x3f, sizeof(w));
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; ++ i){
		scanf("%s", s+1);
		int tot = 0;
		for(int j = 1; j <= m; ++ j){
			if(s[j] == '1') pos[++tot] = j;
		}
		for(int j = 0; j <= tot; ++ j){
			int len = tot - j;
			for(int l = 1; l + len - 1 <= tot; ++ l){
				w[i][j] = min(w[i][j], pos[l+len-1] - pos[l] + 1);
			}
			w[i][tot] = 0;
		}
	}
	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;
	for(int i = 1; i <= n; ++ i){
		for(int j = 0; j <= k; ++ j){
			for(int l = 0; l <= j; ++ l){
				f[i][j] = min(f[i][j], f[i-1][l] + w[i][j-l]);
			}
		}
	}
	int ans = 0x3f3f3f3f;
	for(int i = 0; i <= k; ++ i){
		ans = min(ans, f[n][i]);
	}
	printf("%d\n", ans);
	return 0;
}
```

---

