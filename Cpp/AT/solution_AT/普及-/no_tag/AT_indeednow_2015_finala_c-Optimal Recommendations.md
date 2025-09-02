# Optimal Recommendations

## 题目描述

[problemUrl]: https://atcoder.jp/contests/indeednow-finala-open/tasks/indeednow_2015_finala_c

 求職者と求人会社のマッチングを手助けしている Indeed 社は、求職者に最適な求人を提示するサービスを開発することにした。  
 Indeed 社のデータベースには、独自テストで得られた、各求職者の技術力、語学力、コミュニケーション力が保存されている。  
 またそのデータベースには、各求人会社が応募条件として要求した、それら $ 3 $ つの力の最低限必要な値とその会社の年収も保存されている。  
 データベースのデータがすべて与えられるので、各求職者ごとに、その人が応募可能な会社の中で一番高い年収を示しなさい。

## 样例 #1

### 输入

```
3 6
1 2 3 3
3 3 3 6
4 4 4 8
3 4 3
4 4 4
100 100 1
2 3 4
0 0 0
100 100 100```

### 输出

```
6
8
0
3
0
8```

# 题解

## 作者：Struggle_ong (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/AT1275)

### 题目大意
有 $ n $ 家公司招聘，有 $ a $，$ b $，$ c $ 三种评判标准。有 $ m $ 人想要应聘，条件为 $ x $，$ y $，$ z $，问求职者入职的最高收入为多少。

### 思路
我们先看数据范围，$1 \le N, M \le 50000$，~~哇，好大~~。

但是 $0 \le a_i, b_i, c_i \le 100$，$1 \le w_i \le 10^9$，

所以我们可以想出状态转移方程：
在输入每家公司的要求时，$ dp_{a,b,c}$ 来记录能力为 $ a $，$ b $，$ c $ 的人的最大收入。在循环枚举，补全 $ dp $ 数组（注意从 $ 0 $ 开始）。最后在输入求职者信息时，输出信息所对应的$ dp $ 中的值即可。

#### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[110][110][110];
int main()
{
	int n,m,a,b,c,x,y,z,w;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{cin>>a>>b>>c>>w;dp[a][b][c]=max(dp[a][b][c],w);}//输入，并写出状态转移方程
	for(int i=0;i<=100;i++){
		for(int j=0;j<=100;j++){
			for(int z=0;z<=100;z++){//枚举 
				if(i!=0)dp[i][j][z]=max(dp[i-1][j][z],dp[i][j][z]);//因为我们是从零开始循环的，所以要判断掉 i，j，z 为 0 的情况 
				if(j!=0)dp[i][j][z]=max(dp[i][j-1][z],dp[i][j][z]);
				if(z!=0)dp[i][j][z]=max(dp[i][j][z-1],dp[i][j][z]);
				// 状态转移方程
			}
		}
	}
	for(int i=1;i<=m;i++)//输入应聘者的信息 
	{cin>>x>>y>>z;cout<<dp[x][y][z]<<'\n';}//输出 
	return 0;
}

```


---

## 作者：Symbolize (赞：4)

# 思路
因为 $a,b,c,x,y,z$ 的范围较小，所以我们就可以用下面这种思路。

第一步：我们首先循环输入每个公司的标准 $a,b,c$ 与 $w$ 和薪资，$a,b,c,w$ 不需要用数组，用一个三维数组 $f$，记录下来，$f_{a,b,c}$ 表示目前为止，能力值为 $a,b,c$ 的人能获得的最大薪资。

第二步：然后我们三层循环 $i,j,k$ 的值(注意从 $0$ 开始)，利用状态转移方程补全 $f$ 数组的值。

第三步：最后输入每人的能力值 $x,y,z$ 直接输出 $f_{x,y,z}$。

### 状态转移方程推导
第一步的状态转移方程：

$f$ 数组初始化为 $0$，将每次输入的 $a,b,c$ 并运行状态转移方程 $f_{a,b,c}=\max(f_{a,b,c},w)$。

第二步的状态转移方程：

每个 $f_{i,j,k}$ 的值都只能是每项能力值都不大于 $i,j,k$ 的 $f$ 值。

所以：

$f_{i,j,k}=\max(f_{i,j,k},\max(f_{i-1,j,k},\max(f_{i,j-1,k},f_{i,j,k-1})))$。

但由于 $i,j,k$ 是从 $0$ 开始，所以要判 $0$！

所以：

当 $i\neq0$ 时 $f_{i,j,k}=\max(f_{i,j,k},f_{i-1,j,k})$

当 $j\neq0$ 时 $f_{i,j,k}=\max(f_{i,j,k},f_{i,j-1,k})$

当 $k\neq0$ 时 $f_{i,j,k}=\max(f_{i,j,k},f_{i,j,k-1})$

最后附上 AC 代码！！！
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
const int N=1e2+10;
using namespace std;
int n,m,f[N][N][N],x,y,z,w,a,b,c;//定义 
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)//输入公司要求及薪资 
	{
		cin>>a>>b>>c>>w;
		f[a][b][c]=max(f[a][b][c],w);//第一步的状态转移方程 
	}
	for(int i=0;i<=100;i++) 
	{
		for(int j=0;j<=100;j++) 
		{
			for(int k=0;k<=100;k++) //三重循环，枚举i，j，k，的值 
			{
				if(i) f[i][j][k]=max(f[i][j][k],f[i-1][j][k]);
				if(j) f[i][j][k]=max(f[i][j][k],f[i][j-1][k]);
				if(k) f[i][j][k]=max(f[i][j][k],f[i][j][k-1]);//第二步状态转移方程 
			}
		}
	}
	for(int i=1;i<=m;i++)//输入每位员工的能力值 
	{
		cin>>x>>y>>z;
		cout<<f[x][y][z]<<endl;//输出最终值 
	}
	return 0;//完美收场 
}
```

---

## 作者：Nygglatho (赞：2)

由于 $N, M$ 范围很大，有 $50000$，但是 $a_i, b_i, c_i$ 和 $x_i, y_i, z_i$ 范围很小，只有 $100$，所以考虑递推。

最开始，先开一个大小为 $100$ 的三维数组 $f$，$f(i, j, k)$ 代表三项能力分别为 $(i, j, k)$ 的人最大的可能收入。

接下来，如果 $f(i, j, k)$ 的能力刚好满足公司最低的招聘条件，并且收入比 $f(i, j, k)$（初始值都为 $0$）大的话，那么 $f(i, j, k)$ 就肯定需要变成这家公司的收入了。

然后，我们从 $0$ 至 $100$ 三重循环枚举，查看三项能力中任意一项刚好低 $1$ 的，如果这一个的收入还比 $f(i, j, k)$ 多，那么 $f(i, j, k)$ 更新为这一个的收入。

证明为：

设发现一个公司，招聘最低条件为三项能力分别为 $(x_1, x_2, x_3)$，收入比三项能力分别为 $(y_1, y_2, y_3)$ 的当前收入高（即 $f(x_1, x_2, x_3) \ge f(y_1, y_2, y_3)$），且 $y_1 \ge x_1, y_2 \ge x_2, y_3 \ge x_3$，那么：
- 如果仅有一个 $i(1 \le i \le 3)$，能满足 $y_i - x_i = 1$，并且对于不是 $i$ 的情况，$y_i = x_i$，那么一次即可更新。
- 否则，$(y_1, y_2, y_3)$ 可以查看 $(y_1, y_2, y_3 - 1)$，$(y_1, y_2, y_3 - 1)$ 可以先查看 $(y_1, y_2, y_3 - 2)$，以此类推，那么 $(y_1, y_2, x_3)$ 也可以先查看 $(y_1, y_2 - 1, x_3)$，也以此类推，最终 $(y_1, y_2, y_3)$ 可以查看到 $(x_1, x_2, x_3)$，并且 $f(y_1, y_2, y_3)$ 也将会更新为 $f(x_1, x_2, x_3)$。

所以是正确的，最后 $O(1)$ 处理每一个人即可。

Code：
```cpp
//注意卡常，且尽量少写函数，不然可能会 TLE。
#include <iostream>
using std::cin;
using std::cout;
const char endl = '\n';

inline int max(int a, int b) {return a > b ? a : b;}

int f[105][105][105];



int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		int x, y, z, w;
		cin >> x >> y >> z >> w;
		f[x][y][z] = max(f[x][y][z], w);
		//能力刚好够的更新收入
	}
	for (int i = 0; i <= 100; ++i) {
		for (int j = 0; j <= 100; ++j) {
			for (int k = 0; k <= 100; ++k) {
				//发现就更新收入
				if (i) f[i][j][k] = max(f[i - 1][j][k], f[i][j][k]);
				if (j) f[i][j][k] = max(f[i][j - 1][k], f[i][j][k]);
				if (k) f[i][j][k] = max(f[i][j][k - 1], f[i][j][k]);
			}
		}
	}
	for (int i = 1; i <= m; ++i) {
		int x, y, z;
		cin >> x >> y >> z;
		cout << f[x][y][z] << endl;
		//O(1) 处理每一个人
	}
}
```

---

## 作者：Dream__Sky (赞：2)

## 题目描述：
在 $n$ 家公司中，每家公司有 3 个标准及工资，问：符合条件的 $m$ 人每人能达到的最大工资。
  
## 题目分析
首先看数据范围， $1≤N,M≤50000$。暴力时间复杂度为 $O(nm)$，但是我们可以先选择暴力+优化（~~万一~~能过）。

### code：
```cpp
#include <bits/stdc++.h>
using namespace std;
struct info 
{
	int x,y,z,w;//x、y、z为三项能力，w为收入。
}a[50005];
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i].x>>a[i].y>>a[i].z>>a[i].w;//输入
	for(int i=1;i<=m;i++)
	{
		int x,y,z,maxn=0;
		cin>>x>>y>>z;
		for(int j=1;j<=n;j++)
			if(a[j].x<=x&&a[j].y<=y&&a[j].z<=z) maxn=max(maxn,a[j].w);//如能力符合，求最大收入
		cout<<maxn<<endl;//输出
	}
    return 0;
}

```
发现严重超时。[提交记录](https://www.luogu.com.cn/record/83657714)
## 算法优化：

* 首先加读入优化：
```cpp
ios::sync_with_stdio(0); 
```


发现：再次超时。[提交记录](https://www.luogu.com.cn/record/83658212)

* 进一步优化：
按工资排序后，我们只要找到符合条件的公司可以立马选择。（一定是最优的）
[提交记录](https://www.luogu.com.cn/record/83659759)

我们离 AC 不远了。

* 再次发现，我们在排序时可以加入优化。

如：当工资一样时，按需要的能力大小排序，可以避免一些能力较小，但有许多工资相等，但能力需要较高的公司数量较多的情况。

举例：

有人能力为
```latex
1 1 1 
```
有 3 家公司

| 2| 3| 4| 5|
| -----------: | -----------: | -----------: | -----------: |
| 2| 5| 4| 5|
| 1| 1|  1|5|


不排序需要查找次数为 2 次。

（第 1 条与第 2 条）

排序需要查找一次。

（排序前第 3 条）

发现直接 AC。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
struct info 
{
	int x,y,z,w;//x、y、z为三项能力，w为收入。
}a[50005];
bool cmp(info x,info y)
{
	return x.w>y.w||(x.w==y.w&&x.x<y.x)||(x.w==y.w&&x.x==y.x&&x.y<x.y)||(x.w==y.w&&x.x==y.x&&x.y==x.y&&x.z<y.z); //多个关键字排序，收入相同时，按能力大小排序，解释在上面。
}
int main()
{
	 ios::sync_with_stdio(0);//读入优化。
	 register int n,m;
	 cin>>n>>m;
	for(register int i=1;i<=n;++i)  cin>>a[i].x>>a[i].y>>a[i].z>>a[i].w;//输入。
	sort(a+1,a+1+n,cmp);//排序。
	for(register int i=1;i<=m;++i)
	{
		register int x,y,z;
		 cin>>x>>y>>z;//输入求职者能力。
		for(register int j=1;j<=n;++j)
		{
			if(a[j].x<=x&&a[j].y<=y&&a[j].z<=z) //如果能力符合，直接选。排序时已保证是最优解。
			{
				 cout<<a[j].w<<endl;//输出收入。
				goto LOOP;//退出循环。
			}
		}	
		 cout<<0<<endl;//如果都进不了，输出0。
		LOOP:;
	}//暴力
    return 0;
}//完结撒花

```


---

## 作者：AirQwQ (赞：1)

## 入手

- 这道题数据范围 $ 1\le N ,M \le 50000 $，时间复杂度 $ O(nm) $ 但是时限 $2s$ 优化一下可过。


## 实现优化


* **自定义排序**（重点）

 1. 将每个公司的各种信息存在一个结构体变量中。（应该都会吧）

 1. 因为题目中要求每个人得到最大工资如果打暴力，需要遍历所有公司，所以把公司按照工资由大到小排序，即可在每个人遇到的第一个能接受自己的公司时便是最大工资，然后停止循环，即可剪枝。（即使是最坏情况也和暴力一样）
 
 2. 再对 $a$，$b$，$c$ 依次从小到大排序，即可在相同工资时，找到最容易公司就马上进行加入，减小循环次数。
 
 举个栗子：
 
1. 不排序时
 
 | 公司 | $a$ | $b$ | $c$ | 马内 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $2$ | $2$ | $2$ | $100$
| $2$ | $5$ | $4$ | $6$ | $100$
| $3$ | $11$ | $45$ | $14$ |$114514$
| $4$ | $0$ | $0$ | $0$ | $0$



 | 人 | $a$ | $b$ | $c$ | 要判断的次数 |公司
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $114514$ | $114514$ | $114514$ | $4$ |$3$
| $2$ | $3$ | $10$ | $5$ | $4$|$1$
| $3$ | $1$ | $1$ | $1$ | $4$|$4$
| $4$ | $0$ | $0$ | $0$ | $4$|$4$

总共判断次数：$16$

2. 排序时

 | 公司 | $a$ | $b$ | $c$ | 马内 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $11$ | $45$ | $14$ | $114514$
| $2$ | $2$ | $2$ | $2$ | $100$
| $3$ | $5$ | $4$ | $6$ |$100$
| $4$ | $0$ | $0$ | $0$ | $0$



 | 人 | $a$ | $b$ | $c$ | 要判断的次数 |公司
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $114514$ | $114514$ | $114514$ | $1$ |$1$
| $2$ | $3$ | $10$ | $5$ | $2$|$2$
| $3$ | $1$ | $1$ | $1$ | $4$|$4$
| $4$ | $0$ | $0$ | $0$ | $4$|$4$

总共判断次数：$11$

明显可以看出两个的区别。
 
```cpp
bool cmp(gongsi a,gongsi b){
	if(a.sum!=b.sum)
		return a.sum>b.sum;//先排工资。
	if(a.a!=b.a)
		return a.a<b.a;
	if(a.b!=b.b)
		return a.b<b.b;
	else
		return a.c<b.c;//再排标准低。
}
```

* 主函数内处理


上面说过，因为排序时是按照工资由高到低进行的，所以找到第一个满足条件的公司直接加入。

```cpp

int x,y,z;
bool f=1;
scanf("%d%d%d",&x,&y,&z);
for(int j=1;j<=n;j++){
    if(x>=ng[j].a&&y>=ng[j].b&&z>=ng[j].c){
    	 printf("%d\n",ng[j].sum);
    	 f=0;
    	 break;
    }
 }
 if(f) printf("0\n");
        
```
## 提醒

1. 不能用普通 ```cin``` 不然超时。

2. 还有一个公司都加入不进去的人记得特判。

## AcCode
```cpp
#include<bits/stdc++.h>
using namespace std;
struct gongsi{
	int a,b,c,sum;
}ng[50005];
bool cmp(gongsi a,gongsi b){
	if(a.sum!=b.sum)
		return a.sum>b.sum;
	if(a.a!=b.a)
		return a.a<b.a;
	if(a.b!=b.b)
		return a.b<b.b;
	else
		return a.c<b.c;
}
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        scanf("%d%d%d%d",&ng[i].a,&ng[i].b,&ng[i].c,&ng[i].sum);
    sort(ng+1,ng+1+n,cmp);
    for(int i=1;i<=m;i++){
    	int x,y,z;
    	bool f=1;
    	scanf("%d%d%d",&x,&y,&z);
    	for(int j=1;j<=n;j++){
    		if(x>=ng[j].a&&y>=ng[j].b&&z>=ng[j].c){
    		    printf("%d\n",ng[j].sum);
    			f=0;
    			break;
    		}
    	}
    	if(f) printf("0\n");
    }
    return 0;
}
```





---

