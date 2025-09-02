# [CCC 2015 S5] Greedy For Pies

## 题目描述

给定一个长度为 $n$ 的序列 $a$ 和一个长度为 $m$ 的序列 $b$，你可以将 $b$ 序列中的元素任意插入到 $a$ 序列的任何位置（包括开头和末尾）。之后，你可以从新的序列中选一些元素，但你不能选择两个相邻的元素。

你需要使得你选出的数之和最大，输出这个最大值即可。

## 说明/提示

**【数据范围】：**

对于 $20\%$ 的数据，$m = 0$。

对于另外 $20\%$ 的数据，$m = 1$。

对于另外 $20\%$ 的数据，$m \leq 10$。

对于 $100\%$ 的数据，$1 \leq n \leq 3 \times 10^{3}$，$0 \leq m \leq 100$，$1 \leq a_{i},b_{i} \leq 10^{5}$。

## 样例 #1

### 输入

```
5
10
12
6
14
7
3
1
8
2```

### 输出

```
44```

# 题解

## 作者：Bulyly (赞：5)

- [原题链接](https://www.luogu.com.cn/problem/P9814)。

- 一道较为直接的 dp。首先我们要清楚 $b$ 数组的作用，显然可以分为以下两类。第一种是用来当炮灰，就是让我们可以选两个 $a$ 中两个连续的数，第二种是用来作为被选择的数。对于 $b$ 中要选的数，我们贪心的选取最大的数，炮灰用最小的显然最优。

- 定义状态 $f_{i,j,k,0/1}$ 表示对于 $a$ 中的前 $i$ 个数，已经用来 $j$ 个 $b$ 数组中的数，其中有 $k$ 个不是炮灰。有如下转移：
	
    - 不加入 $b$：
    
    	$f_{i,j,k,0}=\max(f_{i-1,j,k,0},f_{i-1,j,k,1})$。
    
    	$f_{i,j,k,1}=f_{i-1,j,k,0}+a_i$。
    
    - 加入 $b$：
    
    	要选：$f_{i,j,k,0}=\max(f_{i,j,k,0},f_{i-1,j-1,k-1,0+b_{m-k+1}})$。
    
    	炮灰：$f_{i,j,k,1}=\max(f_{i,j,k,1},f_{i-1,j-1,k,1+a_i})$。

- 如果 $b$ 数组没有用完，显然用完一定不劣。所以我们还要对每个没用完 $b$ 的状态继续仿照上面 dp。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

const int N=4e3+10;
int n,m,ans,a[N],b[105],f[2][105][105][2];

int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++) scanf("%d",&b[i]);
	sort(b+1,b+m+1);
	for(int i=1;i<=n;i++) {
		int now=i&1,pre=now^1;
		for(int j=0;j<=m;j++) {
			for(int k=0;k<=j;k++) {
				f[now][j][k][0]=max(f[pre][j][k][1],f[pre][j][k][0]);
				f[now][j][k][1]=f[pre][j][k][0]+a[i];
				if(j&&k) f[now][j][k][0]=max(f[now][j][k][0],f[pre][j-1][k-1][0]+b[m-k+1]);
				if(j-1>=k) f[now][j][k][1]=max(f[now][j][k][1],f[pre][j-1][k][1]+a[i]);
				ans=max({ans,f[now][j][k][0],f[now][j][k][1]});
			} 
		}
	}
	for(int i=n+1;i<=n+m;i++) {
		int now=i&1,pre=now^1;
		for(int j=0;j<=m;j++) {
			for(int k=0;k<=j;k++) {
				if(j) f[now][j][k][0]=max(f[pre][j-1][k][1],f[pre][j-1][k][0]);
				if(j&&k) f[now][j][k][1]=f[pre][j-1][k-1][0]+b[m-k+1];
				ans=max({ans,f[now][j][k][0],f[now][j][k][1]});
			} 
		}
	}
	cout<<ans<<"\n";		
	return 0;
}
```


---

## 作者：Error_Eric (赞：4)

### Statement 

[Link](https://www.luogu.com.cn/problem/P9814)

### Sol

略微不同的解法。

考虑先确定 $a$ 数组怎么选。在「选」的数字下面写 $\texttt 1$，「不选」的数字下面写 $\texttt 0$。这样会形成一个长度为 $n$ 的 $\texttt{01}$ 串。

进行 dp。

$f_{i,j,k,l_1,l_2,}$ 表示已经确定了前 $i$ 个字符，其中有 $j$ 个 $\texttt{00}$（可以无损插入一个 $b$ 中的数字），有 $k$ 个 $\texttt{11}$ （需要插入一个 $b$ 中的数字作为炮灰），开头是 $l_1$ ，结尾是 $l_2$ 的 $\texttt{01}$ 串的最大价值。转移只需要对当前和之前的 $l_2$ 分类讨论即可。

但是可能有远超 $m$ 个 $\texttt{00}$ 或者 $\texttt{11}$。但是只有 $m$ 个位置是有意义的。因此我们特殊的认为 $j,k$ 等于 $m+1$ 的时候，表示对应的子串足够多。

但是这里计算的只是 $a$ 数组贡献的价值。还应当计算 $b$ 数组贡献的价值。

$b$ 数组中有 $k$ 个是炮灰。这 $k$ 个一定是数字最小的。

有 $j+[l1=0]+[l2=0]$ 个免费的位置。这里面先插入最大的数字。

剩下的数字（如果有）则把其中较大的一半（向下取整）选中，剩下的当炮灰即可。

这里不难发现选中的总是 $b$ 最大的一段。因此可以用 $b$ 的前缀和快速计算。

dp 里面有 $4n(m+1)(m+1)=O(nm^2)$ 个状态，每个状态最多转移两次。排序为 $O(m\log m)$，后续计算价值是 $O(m^2)$ 因此总复杂度为 $O(nm^2)$。 $nm^2=3\times 10^7$ **理论上《容易通过》。**

### Code

注意区分 $n$ 和 $m$。

特判不建议在函数里面特判，因为会 TLE。

预处理不建议在函数里面特判，因为会 TLE。

需要滚动数组，不然会 MLE。

数据可以搜索 Canadian Computing Competition 然后到滑铁卢大学官网去下载。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N=3e3+5,M=105;
int n,m,a[N],b[M],cb[M],f[2][M][M][2][2],ans=-1;
//f i j k 
// i determined j 11  k 00 
void tomax(int&o,int v){
    if(o<v)o=v;
}
int fun(int xx,int oo,int xaa,int aax){
    int ava=max(0,m-xx),fre=min(ava,oo+2-xaa-aax);
    return cb[fre+(ava-fre)/2];
}
int main(){
    
    ios::sync_with_stdio(0),
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    cin>>m;
    for(int i=1;i<=m;i++)
        cin>>b[i];
    sort(b+1,b+m+1),reverse(b+1,b+m+1);
    for(int i=1;i<=m;i++)
        cb[i]=cb[i-1]+b[i];
    for(int i=0;i<=m+1;i++)
        for(int j=0;j<=m+1;j++)
            for(int k1:{0,1})
                for(int k2:{0,1})
                    f[1][i][j][k1][k2]=-0x7fffffff;
    f[1][0][0][1][1]=a[1];
    f[1][0][0][0][0]=0;
    //cout<<"input"<<endl;
    for(int i=2;i<=n;i++){
        for(int j=0;j<=m+1;j++){
            for(int k=0;k<=m+1;k++){
                for(int l:{0,1}){
                    int&f1=f[i&1][j][k][1][l],&f0=f[i&1][j][k][0][l];
                    f1=f[(i&1)^1][j][k][0][l]+a[i];
                    if(j) tomax(f1,f[(i&1)^1][j-1][k][1][l]+a[i]);
                    f0=f[(i&1)^1][j][k][1][l];
                    if(k) tomax(f0,f[(i&1)^1][j][k-1][0][l]);
                    
                    if(j==m+1)
                        tomax(f1,f[(i&1)^1][j][k][1][l]+a[i]);
                    if(k==m+1)
                        tomax(f0,f[(i&1)^1][j][k][0][l]);
                    
                }
            }
        }
    }
    for(int i=0;i<=m;i++)
        for(int j=0;j<=m+1;j++)
            for(int k1:{0,1})
                for(int k2:{0,1})
                    ans=max(ans,f[n&1][i][j][k1][k2]+fun(i,j,k1,k2));
    cout<<ans<<endl;
}
```

---

## 作者：TruchyR (赞：3)

## Part 1 思路
- UPD 插入两个分隔和一个计入答案其实与插入一个分隔，再在最后统计答案等价，可删去。

这是一道比较显而易见的 DP 题（指类型）。  
大致观察数据范围可以得出一个 $O(nm^2)$ 的算法。  
下文默认输入的 $b$ 为排序后的。  
设 $f_{i,j,k,op}$ 为在 $a$ 的前 $i$ 个数中，插入了 $b$ 的前 $j$ 个数与后 $k$ 个数，第 $i$ 个数选/不选的选出数字和的最大值。  
其中：  
插入的 $j$ 个数是用于分隔 $a$ 的相邻 $2$ 数字，以便同时选中的。  
插入的 $k$ 个数是用于计入答案的。  
注意到空间最好还是开个滚动数组。  
一下是我的代码使用的递推式（可能有多余）：  
最基础的几个递推：  
- 如果第 $i$ 个数不选：  
$f_{i,j,k,0}$ 可以由 $f_{i-1,j,k,0}$ 和 $f_{i-1,j,k,1}$ 转移。  
- 如果第 $i$ 个数选：  
$f_{i,j,k,1}$ 可以由 $f_{i-1,j,k,0}+a_i$ 转移。 

接下来考虑插入分隔 $a$ 的数 $(j\geq 1)$：  
- 插入后这个数可以和上一个数同时选。
- $f_{i,j,k,1}$ 可以由 $f_{i-1,j-1,k,1}+a_i$ 转移。

插入计入答案的数 $(k\geq 1)$：  
- 插入这个数，必须这个数和上个数同时不选。
- $f_{i,j,k,0}$ 可以由 $f_{i-1,j,k-1,0}+b_{m-k+1}$ 转移。

插入一个分隔和一个计入答案？
- 需要满足这个数和上一个数一个选，一个不选。  
- $f_{i,j,k,0}$ 可以由 $f_{i-1,j-1,k-1,1}+b_{m-k+1}$ 转移。
- $f_{i,j,k,1}$ 可以由 $f_{i-1,j-1,k-1,0}+a_i+b_{m-k+1}$ 转移。

最后计入答案该如何计入呢？  
显然可能会有剩余的 $b$ 的元素未选入，那么计算一下可以选入几个：  
- 如果第 $n$ 个数选了，那么还有 $\left \lfloor \dfrac{m-j-k}{2} \right \rfloor $ 个数能计入答案。  
（一个分隔，一个记录。）  
- 如果第 $n$ 个数不选，那么还有 $\left \lceil \dfrac{m-j-k}{2} \right \rceil $ 个数能计入答案。  
（一个记录，一个分隔。）

体现在更新答案中就分别是：
- 第 $n$ 个数选了，$f_{i,j,k,0}+\sum_{i=m-k-\left \lfloor \frac{m-j-k}{2} \right \rfloor}^{m-k} b_i$ 更新答案。  
- 第 $n$ 个数不选，$f_{i,j,k,0}+\sum_{i=m-k-\left \lceil \frac{m-j-k}{2} \right \rceil}^{m-k} b_i$ 更新答案。  

递推由此结束。
## Part 2 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,res,a[3005],b[105],c[105],f[2][105][105][2];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	cin>>m;
	for(int i=1;i<=m;i++) cin>>b[i];
	sort(b+1,b+1+m);
	for(int i=1;i<=m;i++) c[i]=c[i-1]+b[i];
	memset(f,-0x3f,sizeof(f));
	f[0][0][0][0]=0;
	for(int i=1;i<=n;i++){
	for(int j=0;j<=m;j++){
	for(int k=0;k+j<=m;k++){
		f[i&1][j][k][0]=max(f[(i&1)^1][j][k][0],f[(i&1)^1][j][k][1]);
		f[i&1][j][k][1]=f[(i&1)^1][j][k][0]+a[i];
		if(j>=1)
			f[i&1][j][k][1]=max(f[i&1][j][k][1],f[(i&1)^1][j-1][k][1]+a[i]);
		if(k>=1)
			f[i&1][j][k][0]=max(f[i&1][j][k][0],f[(i&1)^1][j][k-1][0]+b[m-k+1]);
		if(j>=1 && k>=1){
			f[i&1][j][k][0]=max(f[i&1][j][k][0],f[(i&1)^1][j-1][k-1][1]+b[m-k+1]);
			f[i&1][j][k][1]=max(f[i&1][j][k][1],f[(i&1)^1][j-1][k-1][0]+a[i]+b[m-k+1]);
		}
		if(i==n){
			res=max(res,f[i&1][j][k][0]+c[m-k]-c[m-k-(m-j-k+1)/2]);
			res=max(res,f[i&1][j][k][1]+c[m-k]-c[m-k-(m-j-k)/2]);
		}
	}}}cout<<res;
	return 0;
}
```


---

## 作者：4C45 (赞：1)

模拟赛因为没判负下标 RE 掉了，悲。

## 分析

DP。

对于一段得到的序列，发现在确定 $b$ 元素插入的下标和选择的所有下标后，可以随便排列插入的原 $b$ 数列的元素。所以我们先将 $b$ 排好序，然后转移中尽量往大的选。

设 $f_{i,j,k}$ 为选择**前** $i$ 个来自 $a$ 数列元素和**任意** $j$ 个来自 $b$ 数列的元素后，组成的 $i+j$ 长度的序列中，选择 $k$ 个 $b$ 数列的元素，并且选择了最终序列中的第 $i+j$ 个元素得到的答案的最大值。

接下来看看怎么转移。

首先考虑只选了第 $i+j$ 位的情况，$f_{i,j,k}=\max\{a_i,b_k\}$。

显然由题目限制，$i+j$ 长度的结果只能从长度不大于 $i+j-2$ 的结果转移过来。

对于向序列尾部添加一个 $a_i$ 的操作，转移为：

$$f_{i,j,k}=\max\limits_{x\lt i,x+y\le i+j-2} \{f_{x,y,k}\}+a_i$$

对于向序列尾部添加一个 $b_k$ 的操作（排好序后的第 $k$ 大），为：

$$f_{i,j,k}=\max\limits_{y\lt j,x+y\le i+j-2} \{f_{x,y,k-1}\}+b_k$$

合起来转移就好了。

于是我们得到了一个 $\mathcal O(n^2 m^3)$ 的复杂度巨大的解法。接下来让我们优化它。

注意到上面两个 $\max$ 都是在同一维取得的（$k$ 和 $k-1$），把这一维先忽略掉，然后把 $f_{i,j}$ 看作平面上点 $(i,j)$，那么 $i+j-2$ 的限制就变成了曼哈顿距离不小于 $2$。

![](https://cdn.luogu.com.cn/upload/image_hosting/kuv07oen.png)

接下来将以对 $f_{4,3}$ 的转移举例。

把 $a_i$ 的转移框选出来。

![](https://cdn.luogu.com.cn/upload/image_hosting/7fepa8pi.png)

这可以拆分为一个 $(0,0)$ 到 $(x-2,y)$ 的矩形和一个 $(0,0)$ 到 $(x-1.y-1)$ 的矩形。转移变成了求矩形里面点权最大值。

然后是 $b_k$。

![](https://cdn.luogu.com.cn/upload/image_hosting/otmh9z74.png)

这可以拆分为一个 $(0,0)$ 到 $(x,y-2)$ 的矩形和一个 $(0,0)$ 到 $(x-1.y-1)$ 的矩形。

再把维度 $k$ 加回来。我们设在 $k$ 维上一个 $(0,0)$ 到 $(i,j)$ 的矩形框选的最大值为 $g_{i,j,k}$。当我们算出 $f_{i,j,k}$，就可以转移：

$$g_{i,j,k}=\max\{g_{i-1,j,k},g_{i,j-1,k},f_{i,j,k}\}$$

最终的 $f_{i,j,k}$ 的转移式就是：

$$f_{i,j,k}=\max\{a_i,b_k,g_{i-2,j,k}+a_i,g_{i-1,j-1,k}+a_i,g_{i-1,j-1,k-1}+b_k,g_{i,j-2,k-1}+b_k\}$$

答案就是 $\max\limits_{i=0}^m g_{n,m,i}$。现在 $\mathcal O(nm^2)$ 了。

## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define ir(i,a,b) for(int i=b;i>=a;i--)
using namespace std;
int f[3001][101][101],g[3001][101][101];
int a[3080],b[108]; 
int main()
{
	int n,m;
	cin>>n;
	rep(i,1,n) cin>>a[i];
	cin>>m;
	rep(i,1,m) cin>>b[i];
	sort(b+1,b+m+1,greater<int>());
	rep(i,0,n)
	{
		rep(j,0,m)
		{
			rep(k,0,j)
			{
				f[i][j][k]=max(a[i],b[k]);
				if(i>=2) f[i][j][k]=max(f[i][j][k],g[i-2][j][k]+a[i]);
				if(i>=1 and j>=1) f[i][j][k]=max(f[i][j][k],g[i-1][j-1][k]+a[i]);
				if(i>=1 and j>=1 and k>=1) f[i][j][k]=max(f[i][j][k],g[i-1][j-1][k-1]+b[k]);
				if(j>=2 and k>=1) f[i][j][k]=max(f[i][j][k],g[i][j-2][k-1]+b[k]);
				if(i>=1) g[i][j][k]=max(g[i][j][k],g[i-1][j][k]);
				if(j>=1) g[i][j][k]=max(g[i][j][k],g[i][j-1][k]);
				g[i][j][k]=max(g[i][j][k],f[i][j][k]);
			}
		}
	}
	int ans=0;
	rep(k,0,m) ans=max(ans,g[n][m][k]);
	cout<<ans;
}
```

---

## 作者：tyr_04 (赞：1)

[传送门](https://www.luogu.com.cn/problem/P9814)

## 题意

给你两个序列，你可以从序列二中取出一些数插在序列二的任何位置。

此后，你可以从新的序列中取出一些不相邻的数，问你取出的数的和的最大值是多少。

## 思路

一眼动态规划。

假设第一个序列长为 $n$，第二个序列长为 $m$。



定义：$dp_{i,j,k,x,y}$ 表示目前枚举到第 $i$ 个数，有 $j$ 个相邻的数要选，有 $k$ 个相邻的数两个都不选时的和的最大值。其中 $x$ 表示目前这个数选不选（$0$ 表示不选，$1$ 表示选），$y$ 表示整个序列的第一个数选不选 （$0$ 表示不选，$1$ 表示选）。

为了保证有解，我们要使 $j$ 的值必须小于等于 $m$，而 $k$ 的值可以大于 $m$，因为相邻两个数不选的情况也是不相邻。

一旦 $k$ 的值等于 $m+1$ 后，我们就不用管 $k$ 比 $m+1$ 更大的情况了，因为此时 $k$ 的值对最终答案没有影响。

我们可以先取出序列一中的数，找出每一个情况的和的最大值，并且要拿出 $j$ 个序列二中的数来当中间的数，因为对答案没有影响，又要使情况最优，所以要优先拿小的数。

接下来，我们可以把序列二剩下的数优先填入两个都不选的中间位置，也就是 $k$ 个位置，因为对答案有影响，又要使情况最优，所以要优先拿大的数。

设剩下的序列二中的数有 $s$ 个，这 $s$ 个数可以插到开头或结尾的位置。

如果开头的数选，结尾的数不选，则应该把剩下的数插到结尾位置，对答案有贡献的数有 $\frac {s}{2}$（向上取整）个数。

如果开头的数不选，结尾的数选，则应该把剩下的数插到开头位置，对答案有贡献的数有 $\frac {s}{2}$（向上取整）个数。

如果开头的数选，结尾的数也选，则应该把剩下的数插到开头或结尾的任意位置，对答案有贡献的数有 $\frac {s}{2}$（向下取整）个数。

如果开头的数不选，结尾的数也不选，则应该把剩下的数平均分配到开头和结尾的位置，对答案有贡献的数有 $\frac {s}{2}+1$（向下取整）个数。

为了使答案最优，我们要在剩下的序列二的数中取尽量大的数，最后再加上满足条件的 dp 数组中的情况就是答案了。

# AC 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[3005],b[105],zans=0,dp[2][105][105][2][2];//全部数量，00个数，11个数，目前的01，第一个数的01 
bool cmp(int x,int y)
{
	return x>y;
}
int qh(int i,int j,int x,int y)
{
	int o=m-j,sum=0;
	for(int s=1;s<=min(o,i);s++)
	{
		sum+=b[s];
	}
	if(o<=i)
	{
		return sum;
	}
	int p=m-min(o,i)-j;
	int f=p+(!x)+(!y);
	for(int s=min(o,i)+1;s<=min(o,i)+f/2;s++)
	{
		sum+=b[s];
	}
	return sum;
}
signed main()
{
	scanf("%lld",&n); 
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	scanf("%lld",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%lld",&b[i]);
	}
	sort(b+1,b+m+1,cmp);
	for(int i=1;i<=n;i++)
	{
		memset(dp[i%2],128,sizeof(dp[i%2]));
		if(i==1)
		{
			dp[1][0][0][0][0]=0;
			dp[1][0][0][1][1]=a[1];
			continue;
		}
		for(int j=0;j<=m+1;j++)
		{
			for(int k=0;k<=m;k++)
			{
				if(j==0)
				{
					dp[i%2][j][k][0][0]=dp[(i-1)%2][j][k][1][0];
					dp[i%2][j][k][0][1]=dp[(i-1)%2][j][k][1][1];
				}
				else
				{
					dp[i%2][j][k][0][0]=max(dp[(i-1)%2][j-1][k][0][0],dp[(i-1)%2][j][k][1][0]);
					dp[i%2][j][k][0][1]=max(dp[(i-1)%2][j-1][k][0][1],dp[(i-1)%2][j][k][1][1]);
				}
				if(j==m+1)
				{
					dp[i%2][j][k][0][0]=max(dp[(i-1)%2][j][k][0][0],dp[i%2][j][k][0][0]);
					dp[i%2][j][k][0][1]=max(dp[(i-1)%2][j][k][0][1],dp[i%2][j][k][0][1]);
				}
				if(k==0)
				{
					dp[i%2][j][k][1][0]=dp[(i-1)%2][j][k][0][0]+a[i];
					dp[i%2][j][k][1][1]=dp[(i-1)%2][j][k][0][1]+a[i];
				}
				else
				{
					dp[i%2][j][k][1][0]=max(dp[(i-1)%2][j][k][0][0],dp[(i-1)%2][j][k-1][1][0])+a[i];
					dp[i%2][j][k][1][1]=max(dp[(i-1)%2][j][k][0][1],dp[(i-1)%2][j][k-1][1][1])+a[i];
				}
			}
		}
	}
	for(int i=0;i<=m+1;i++)
	{
		for(int j=0;j<=m;j++)
		{
			for(int x=0;x<=1;x++)
			{
				for(int y=0;y<=1;y++)
				{
					if(dp[n%2][i][j][x][y]>0)
					{
						int ans=dp[n%2][i][j][x][y];
						zans=max(zans,ans+qh(i,j,x,y));
					}
				}
			}
		}
	}
	cout<<zans;
	return 0;
}
```

---

## 作者：naroto2022 (赞：0)

# P9814 题解

[博客园里查看更佳](https://www.cnblogs.com/naroto2022/p/19024211)

### 题面

[原题传送门](https://www.luogu.com.cn/problem/P9814)

### 思路

发现 $n\leqslant3\times10^3,m\leqslant100$，所以允许 $O(nm^2)$ 的做法。

设 $dp_{i,j,k,0/1}$ 表示遍历到 $a$ 数组的第 $i$ 个位置，$b$ 数组插了 $j$ 位，$b$ 数组选了 $k$ 个数做贡献，$a_i$ 选或不选的最大值。

首先贪心的，只要在一种情况下一个数可选可不选，（即选了不会影响其他数选或不选）选了显然更优。

而 $b$ 数组是任意顺序插入的，所以可以从大到小排序插入。

则转移式有四种情况：

1. 不插入 $b_j$，不选 $a_i$，那么 $a_{i-1}$ 选或不选没有什么区别，于是 $dp_{i,j,k,0}=\max(dp_{i-1,j,k,0},dp_{i-1,j,k,1})$。
2. 不插入 $b_j$，选 $a_i$，那么 $a_{i-1}$ 肯定不能选了，于是 $dp_{i,j,k,1}=dp_{i-1,j,k,0}+a_i$。
3. 插入 $b_j$，并且选上 $b_j$，则 $a_i,a_{i-1}$ 不能选，于是 $dp_{i,j,k,0}=\max(dp_{i,j,k,0},dp_{i-1,j-1,k-1,0}+b_k)$。
4. 插入 $b_j$，并且不选 $b_j$，则 $a_i,a_{i-1}$ 选了更优，于是 $dp_{i,j,k,1}=\max(dp_{i,j,k,1},dp_{i-1,j-1,k,1}+a_i)$。

但是这还没完，$b$ 完全非常有可能没有选完，而这个时候我们还要继续 dp。

1. 不选 $b_k$，那 $b_{k-1}$ 选或不选也没有什么区别，于是 $dp_{i,j,k,0}=\max(dp_{i-1,j-1,k,0},dp_{i-1,j-1,k,1})$。
2. 选 $b_k$，那 $b_{k-1}$ 肯定就不能选了，于是 $dp_{i,j,k,1}=dp_{i-1,j-1,k-1,0}+b_k$。

于是我们终于做完了，怕空间爆的话 dp 数组开滚一下就行。

### 代码 

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
//#define gc getchar
#define gc()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#define ll long long
#define ni i&1
#define li i&1^1
using namespace std;
const int MN=3e3+5,MM=105;
ll n,m,a[MN],b[MM],dp[2][MM][MM][2],ans;
char buf[1<<23],*p1=buf,*p2=buf;
void write(ll n){if(n<0){putchar('-');write(-n);return;}if(n>9)write(n/10);putchar(n%10+'0');}
ll read(){ll x=0,f=1;char ch=gc();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=gc();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=gc();}return x*f;}
bool cmp(ll x, ll y){return x>y;}
int main(){
    //ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    n=read();for(int i=1; i<=n; i++) a[i]=read();
    m=read();for(int i=1; i<=m; i++) b[i]=read();
    sort(b+1,b+1+m,cmp);
    for(int i=1; i<=n; i++) for(int j=0; j<=min((ll)i,m); j++) for(int k=0; k<=j; k++){
        dp[ni][j][k][0]=max(dp[li][j][k][0],dp[li][j][k][1]);
        dp[ni][j][k][1]=dp[li][j][k][0]+a[i];
        if(j&&k) dp[ni][j][k][0]=max(dp[ni][j][k][0],dp[li][j-1][k-1][0]+b[k]);
        if(j-1>=k) dp[ni][j][k][1]=max(dp[ni][j][k][1],dp[li][j-1][k][1]+a[i]);
        ans=max(ans,max(dp[ni][j][k][0],dp[ni][j][k][1]));
    }
    for(int i=n+1; i<=n+m; i++) for(int j=0; j<=min((ll)i,m); j++) for(int k=0; k<=j; k++){
        if(j) dp[ni][j][k][0]=max(dp[li][j-1][k][0],dp[li][j-1][k][1]);
        if(j&&k) dp[ni][j][k][1]=dp[li][j-1][k-1][0]+b[k];
        ans=max(ans,max(dp[ni][j][k][0],dp[ni][j][k][1]));
    }
    write(ans);putchar('\n');
    return 0;
}//250805
```

---

## 作者：Like_Amao (赞：0)

**前言**

[题目传送门](https://www.luogu.com.cn/problem/P9814)

**思路**

dp。

首先我们定义一个数组 $b$，很明显，他可以分成两种类型：

* 让我们可以选两个 $a$ 中两个连续的数。
* 作为被选的数

对于 $b$ 中要选的数，我们通过贪心来选取最大的数，第一种类型的数用最小的显然最优。

我们设 $f _ {i , j , k , 0 / 1}$ 表示表示对于 $a$ 数组中的前 $i$ 个数，已经用来 $j$ 个 $b$ 数组中的数，其中有 $k$ 个不是第一种类型的数字。有如下转移：

* 不加入 $b$：

$f _ {i , j , k , 0} = \max (f _ {i - 1 , j , k , 0} , f _ {i - 1 , j , k , 1})$。

$f _ {i , j , k , 1} = f _ {i - 1 , j , k , 0} + a _ i$。

* 加入 $b$：

要选：$f _ {i , j , k , 0} = \max (f _ {i , j , k , 0} , f _ {i - 1 , j - 1 , k - 1 , 0 + b _ {m - k + 1}})$

第一种类型：$f _ {i , j , k , 1} = \max (f _ {i , j , k , 1} , f _ {i - 1 , j - 1 , k , 1 + a _ i})$。

* 如果 $b$ 数组仍有剩余，显然，用完一定不劣，所以我们还要对每个没用完的 $b$ 继续 dp。

**代码**


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans,a[4001],b[105],f[2][105][105][2];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>b[i];
	}
	sort(b+1,b+m+1);
	for(int i=1;i<=n;i++)
	{
		int now=i&1,pre=now^1;
		for(int j=0;j<=m;j++)
		{
			for(int k=0;k<=j;k++)
			{
				f[now][j][k][0]=max(f[pre][j][k][1],f[pre][j][k][0]);
				f[now][j][k][1]=f[pre][j][k][0]+a[i];
				if(j and k)
				{
					f[now][j][k][0]=max(f[now][j][k][0],f[pre][j-1][k-1][0]+b[m-k+1]);
				}
				if(j-1>=k)
				{
					f[now][j][k][1]=max(f[now][j][k][1],f[pre][j-1][k][1]+a[i]);
				}
				ans=max(ans,max(f[now][j][k][0],f[now][j][k][1]));
			}
		}
	}
	for(int i=n+1;i<=n+m;i++)
	{
		int now=i&1,pre=now^1;
		for(int j=0;j<=m;j++)
		{
			for(int k=0;k<=j;k++)
			{
				if(j)
				{
					f[now][j][k][0]=max(f[pre][j-1][k][1],f[pre][j-1][k][0]);
				}
				if(j and k)
				{
					f[now][j][k][1]=f[pre][j-1][k-1][0]+b[m-k+1];
				}
				ans=max(ans,max(f[now][j][k][0],f[now][j][k][1]));
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Aveiro7 (赞：0)

**提示**：本篇文章并非本人原创，原文来源于：[传送门](https://blog.csdn.net/jiangtaizhe/article/details/108075126?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522169910669416800182733821%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=169910669416800182733821&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-1-108075126-null-null.142^v96^pc_search_result_base4&utm_term=CCC%202015%20S5%5D%20Greedy%20For%20Pies&spm=1018.2226.3001.4187)

## 题意

给定一个长度为 $n$ 的序列 $a$ 和一个长度为 $m$ 的序列 $b$，你可以将 $b$ 序列中的元素任意插入到 $a$ 序列的任何位置（包括开头和末尾）。之后，你可以从新的序列中选一些元素，但你不能选择两个相邻的元素。

你需要使得你选出的数之和最大，输出这个最大值即可。

## 思路

* 暴力方法：对于每个 $b_i$ 枚举插入点，最后做一遍 DP 就可以了，时间复杂度 $O(M^N(M+n))$ 超时。

* 贪心方法：我们发现贪心的做法是错误的。

* 我们发现题目没有要求输出路径，那么可以考虑 DP 的方法。

## DP

我们发现在取糖果的时候不能连续取，那么我们将 $b$ 数组进行升序排序，这样就可以让 $b$ 数组的前一部分一定不取，后面的可以取也可以不取。

令函数 $\operatorname f(i,j,k,0/1)$ 代表 $a_{1\to i} b_{1\to j,k\to m}$，以及 $a_i$ 和 $b_k$ 不取/取。$b$ 升序。

可得：

$\operatorname f(i,j,k,0)=\max(\operatorname f(i,j-1,k,0),\operatorname f(i,j-1,k,1),\operatorname f(i-1,j,k,1),\operatorname f(i-1,j,k,0))$

$\operatorname f(i,j,k,1)=\max(\operatorname f(i-1,j,k,0)+a_i,\operatorname f(i,j,k+1,0)+b_k)$

## 细节
前面的 DP 式搞定了，还要看一下怎么迭代。初始值很简单，全部是 $0$ 就可以了。考虑循环的范围，因为要考虑到全部用来垫的情况和全部使用的情况，所以伪代码如下：

```cpp
for i=1 to n
for j=0 to m+1
for k=m+1 to k

```

最后统计最大值即可。

## Code

```cpp
#include<cstdio>
#include<algorithm>
#define maxn 3039
#define maxm 139
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
int f1[maxn],f2[maxn];
int f[maxn][maxm][maxm][2];
int a[maxn],b[maxm];
int n,m;
int main(){
	//freopen("candy.in","r",stdin);
	//freopen("candy.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
        scanf("%d",&b[i]);
    if(m==0){
    	f1[0]=f1[0]=0;
    	for(int i=1;i<=n;i++){
	    f1[i]=f2[i-1]+a[i];
		f2[i]=max(f1[i-1],f2[i-1]);
	    }
	    printf("%d",max(f1[n],f2[n]));
	    return 0;
	}
	sort(b+1,b+m+1);
	for(int i=1;i<=n;i++)
    for(int j=0;j<=m+1;j++)
    for(int k=m+1;k>=j;k--){
        f[i][j][k][0]=max(f[i-1][j][k][1],f[i-1][j][k][0]);
        if(j) f[i][j][k][0]=max(f[i][j][k][0],max(f[i][j-1][k][0],f[i][j-1][k][1]));
        f[i][j][k][1]=max(f[i-1][j][k][0]+a[i],f[i][j][k+1][0]+b[k]);
        //else f[i][j][k][1]=f[i-1][j][k][0]+a[i];
	}
	int maxx=-1;
	for(int i=0;i<=m;i++)
	    maxx=max(maxx,max(f[n][i][i+1][1],f[n][i][i+1][0]));
	printf("%d",maxx);
	return 0;
}

```


---

