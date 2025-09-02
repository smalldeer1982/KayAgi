# Palindromic Paths

## 题目描述

You are given a matrix with $ n $ rows (numbered from $ 1 $ to $ n $ ) and $ m $ columns (numbered from $ 1 $ to $ m $ ). A number $ a_{i, j} $ is written in the cell belonging to the $ i $ -th row and the $ j $ -th column, each number is either $ 0 $ or $ 1 $ .

A chip is initially in the cell $ (1, 1) $ , and it will be moved to the cell $ (n, m) $ . During each move, it either moves to the next cell in the current row, or in the current column (if the current cell is $ (x, y) $ , then after the move it can be either $ (x + 1, y) $ or $ (x, y + 1) $ ). The chip cannot leave the matrix.

Consider each path of the chip from $ (1, 1) $ to $ (n, m) $ . A path is called palindromic if the number in the first cell is equal to the number in the last cell, the number in the second cell is equal to the number in the second-to-last cell, and so on.

Your goal is to change the values in the minimum number of cells so that every path is palindromic.

## 说明/提示

The resulting matrices in the first three test cases:

 $ \begin{pmatrix} 1 & 1\\ 0 & 1 \end{pmatrix} $  $ \begin{pmatrix} 0 & 0 & 0\\ 0 & 0 & 0 \end{pmatrix} $  $ \begin{pmatrix} 1 & 0 & 1 & 1 & 1 & 1 & 1\\ 0 & 1 & 1 & 0 & 1 & 1 & 0\\ 1 & 1 & 1 & 1 & 1 & 0 & 1 \end{pmatrix} $

## 样例 #1

### 输入

```
4
2 2
1 1
0 1
2 3
1 1 0
1 0 0
3 7
1 0 1 1 1 1 1
0 0 0 0 0 0 0
1 1 1 1 1 0 1
3 5
1 0 1 0 0
1 1 1 1 0
0 0 1 0 0```

### 输出

```
0
3
4
4```

# 题解

## 作者：Fairicle (赞：4)

由于这题的路径是只能从 $(1,1)$ 往下走到 $(n,m)$ 也就是说每走一步，横坐标加一或者纵坐标加一。那么可以很容易的发现，一个回文路径上相对应的两个点，他们的横纵坐标之和的和是不变的。

例如 $(1,1)$ 和 $(n,m)$ 是对应的，$(1,2)$ 和 $(n-1,m)$ 是对应的。可以发现总和都是 $n+m+2$。

如果一个点的坐标为 $(x_1,y_1)$，它所对应的点的集合为 $(x_2,y_2),x_2+y_2=n+m+2-x_1-y_1$。

也由上可见，横纵坐标和相等的点集，他们的值必定是一样的（除非这些点都是奇数长度回文的中点）。

那么只需要在读入的时候处理一下横纵坐标和即可。

回文长度为奇数和偶数计算答案时分别处理。多组数据要清空！

code：
```cpp
#define ll long long
#define ri register int
#define N 100
int t,n,m,a[40][40],c[65][2];
int main(){
	t=rd();
	while(t--){
		int ans=0;
		n=rd(),m=rd();
		memset(a,0,sizeof(a));
		memset(c,0,sizeof(c));
		for(ri i=1;i<=n;++i) for(ri j=1;j<=m;++j) a[i][j]=rd(),c[i+j][0]+=(a[i][j]==0),c[i+j][1]+=(a[i][j]==1);
		if((n+m)%2==1){
			for(ri i=2;i<=(n+m+2)/2;++i){
				ans+=c[i][0]+c[i][1]+c[n+m+2-i][0]+c[n+m+2-i][1]-max(c[i][0]+c[n+m+2-i][0],c[i][1]+c[n+m+2-i][1]);
			}
		}
		else{
			for(ri i=2;i<(n+m+2)/2;++i){
				ans+=c[i][0]+c[i][1]+c[n+m+2-i][0]+c[n+m+2-i][1]-max(c[i][0]+c[n+m+2-i][0],c[i][1]+c[n+m+2-i][1]);
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：45dinо (赞：4)

题目要求所有路径都要是回文，需要对矩阵和回文有所认识。

回文及矩阵的定义：略

以样例 #1的第二组输入的矩阵为例：

![](https://cdn.luogu.com.cn/upload/image_hosting/hosfg53d.png)

每一条路径都会经过灰-蓝-绿-橙-红-紫-棕色各一次（这颜色似乎有所暗示）

发现所有灰色数字的坐标和都是 2，所有蓝色数字坐标和都是 3……

如果要保证回文，所有灰色数字必须等于棕色数字，所有蓝色数字都要等于紫色数字……

统计出每一种颜色 1 和 0 的个数，计算完全匹配的代价即可。

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,ans,num0[61],num1[61],a;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		ans=0;
		memset(num0,0,sizeof(num0));
		memset(num1,0,sizeof(num1));
		for(int i=1;i<=n;i++)
			for(int l=1;l<=m;l++)
			{
				scanf("%d",&a);
				if(a&1)
					num0[i+l-1]++;
				else
					num1[i+l-1]++;
			}
		for(int i=1;i*2<n+m;i++)
			ans+=min(num0[i]+num0[n+m-i],num1[i]+num1[n+m-i]);
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：qwq___qaq (赞：1)

我们可以考虑以到起点和终点的曼哈顿距离的最小值分层。

那么我们可以发现，其实每一层都是在回文串中对应相等的点。

我们先找到一条路径上对应的两个点 $(x,y)$ 和 $(p,q)$，容易想到当 $a_{x,y}\ne a_{p,q}$ 时，我们需要更改 $(x,y)$ 或 $(a,b)$，考虑更改时会造成哪些影响：

以更改 $(x,y)$ 为例，那么之前在对面和 $(x,y)$ 的所有点都会更改，同时，在自己这边的所有和自己相同颜色的点都会被对面的点给更改颜色。

那么我们就可以记录每一层 $0$ 和 $1$ 的个数，然后选数量少的一个更改即可。

注意：当回文串长度为奇数时，中间的不用考虑。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,cnt[2][1000],c;
int main(){
	scanf("%d",&T);
	while(T--){
	    scanf("%d%d",&n,&m);
		memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j){
				scanf("%d",&c);
				int x=abs(i-1)+abs(j-1),y=abs(i-n)+abs(j-m);
				++cnt[c][min(x,y)];
			}
		int ans=0;
		for(int i=0;i<(n+m-1)/2;++i)
			ans+=min(cnt[0][i],cnt[1][i]);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：3_14 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1366C)

# 思路

按照单元格与起点的距离对它们进行分组：组 $0$ 由单个单元格 $\left ( 1,1\right ) $ 组成;组 $1$ 由单元格  $\left ( 1, 2\right ) $ 和 $\left ( 2, 1\right ) $ 组成，依此类推。总共有 $n + m - 1$ 组。

让我们分析一下 $k$ 和 $n + m - 2 - k$ 组。有两种情况：

- 如果 $k = 0$ 或 $n + m - 2 - k = 0$，那么我们看到的是起始单元格和结束单元格，它们的内容应该相等;
- 否则，假设两个单元格 $\left ( x, y\right ) $ 和 $\left ( x + 1,y - 1\right ) $ 属于同一组。我们可以很容易地证明这两个单元格的内容应该是相等的（例如，通过分析两条穿过单元格 $\left ( x + 1, y\right ) $ 并在该单元格之后重合的路径，但一条路径从 $\left ( x, y\right ) $ 到达 $\left ( x + 1, y\right ) $，另一条路径从 $\left ( x + 1, y - 1\right )$ 。并且，使用归纳法，我们可以证明一组中所有单元格的内容都应该相等。由于路径应该是回文的，因此组 $k$ 的内容应等于组 $n + m - 2 - k$ 的内容。

因此，在每对组中，我们应该计算 $1$ 和 $0$ 的数量，并选择要更改的其中哪一个。请注意，如果 $n + m$ 是偶数，则中心组没有对，因此不应修改。

# 代码


```cpp
#include<bits/stdc++.h>
#define lcm(x,y) x/__gcd(x,y)*y;
#define str to_string
using namespace std;
using ll=long long;
const int MAX=1e5+1;
const double EPS=1e-6;
int n,m,t;
void work(){
	cin>>n>>m;
	vector<vector<int>>a(n,vector<int>(m));
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cin>>a[i][j];
	vector<vector<int>>cnt(n+m-1,vector<int>(2));
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cnt[i+j][a[i][j]]++;
	int ans=0;
	for(int i=0;i<=n+m-2;i++){
		int j=n+m-2-i;
		if(i<=j)continue;
		ans+=min(cnt[i][0]+cnt[j][0],cnt[i][1]+cnt[j][1]);
	}
	cout<<ans<<'\n';
	return;
}
int main(){
	cin>>t;
	while(t--)work();
	return 0;
}
```


## [AC记录](https://codeforces.com/problemset/submission/1366/296180545)

---

