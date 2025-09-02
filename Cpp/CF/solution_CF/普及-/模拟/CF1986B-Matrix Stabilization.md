# Matrix Stabilization

## 题目描述

给你一个大小为 $n \times m$ 的矩阵，矩阵的行从上到下编号为 $1$ 到 $n$，列从左到右编号为 $1$ 到 $m$。矩阵中第 $i$ 行与第 $j$ 列的交点处的元素记为 $a_{ij}$。

我们有一个用于稳定化矩阵 $a$ 的算法：

1. 找到一个单元格 $(i, j)$，该单元格的值严格大于其所有相邻单元格的值。如果没有这样的单元格，则终止算法。如果有多个这样的单元格，选择 $i$ 值最小的单元格；如果仍有多个单元格，选择 $j$ 值最小的单元格。
2. 将 $a_{ij}$ 的值减 1。
3. 回到步骤 1。

在这个问题中，如果两个单元格 $(a, b)$ 和 $(c, d)$ 共享一条边，即 $|a - c| + |b - d| = 1$，则它们被认为是相邻的。

你的任务是输出矩阵 $a$ 在稳定化算法执行后的结果。可以证明，此算法不能无限次运行。

## 样例 #1

### 输入

```
6
1 2
3 1
2 1
1
1
2 2
1 2
3 4
2 3
7 4 5
1 8 10
5 4
92 74 31 74
74 92 17 7
31 17 92 3
74 7 3 92
7 31 1 1
3 3
1000000000 1 1000000000
1 1000000000 1
1000000000 1 1000000000```

### 输出

```
1 1 
1 
1 
1 2 
3 3 
4 4 5 
1 8 8 
74 74 31 31 
74 74 17 7 
31 17 17 3 
31 7 3 3 
7 7 1 1 
1 1 1 
1 1 1 
1 1 1```

# 题解

## 作者：2huk (赞：5)

### 0. 前言

1. 赛后被 Hack 了。div.3 飙到 1600+ 名。
2. 好题。学到很多。
3. 建议评橙。如果真评橙的话这就是我写过的最长的橙题题解。

### 1. 题意

> - 给定 $n \times m$ 的矩阵 $a_{i,j}$。每次操作找到一个 $i$ 最小的前提下 $j$ 最小的，满足 $a_{i,j}$ 严格大于所有与它相邻的值的 $(i, j)$，并将 $a_{i,j} \gets a_{i,j} - 1$。输出不能操作时的矩阵。
> - $n, m \le 100$，$n \cdot m > 1$，$1 \le a_{i,j} \le 10^9$。

### 2. 说明

1. 以下分析复杂度时认为 $n, m$ 同阶。
2. 为方便表述，我们定义下标的不等关系为（其余不等关系 $>, \le, \ge$ 的定义类比）：

$$
[(i_1, j_1) < (i_2, j_2)] = \left\{\begin{matrix}
 [i_1 < i_2] & i_1 \ne i_2\\
 [j_1 < j_2] & i_1 = i_2\end{matrix}\right.
$$

3. 定义「操作 $(i, j)$」为 $a_{i,j} \gets a_{i,j} - 1$。
4. 与 $(i, j)$ 相邻的位置可能会有 $1, 2, 3, 4$ 个。方便起见我们在 $a$ 的上下左右分别用 $0$ 填满。这样就一定是 $4$ 个了。

### 3. 题解

暴力做法显然会爆炸。例如当 $a = \begin{Bmatrix}
 1 & 10^9
\end{Bmatrix}$ 时我们会将 $a_{1,2}$ 操作 $10^9$ 次。

进一步观察发现，如果 $(i, j)$ 是满足「大于所有与它相邻的值」的，那么接下来会「操作 $(i, j)$」若干**次**，直到 $a_{i,j}$ 不满足「大于所有与它相邻的值」，也就是成为这些值中的最大值。

此时你就有了一个 $\mathcal O(n^4)$ 的做法：执行至多 $\mathcal O(n^2)$ 次，每次以 $\mathcal O(n^2)$ 的复杂度找到这个 $(i, j)$，然后 $\mathcal O(1)$ 修改。

[这个时候就不得不讲个笑话了](https://codeforces.com/contest/1986/hacks/1051981)。

考虑如何优化复杂度。如果我们称「『操作 $(i, j)$』若干**次**直到 $a_{i,j}$ 不满足『大于所有与它相邻的值』」为一**轮**操作，事实上，如果这一**轮**操作 $(i, j)$，那么下一**轮**操作的 $(i', j')$ 一定满足 $(i, j) < (i', j')$。换言之，你只需要从上一**轮**找到的 $(i, j)$ 开始往后找新一**轮**的 $(i', j')$ 即可。

### 4. 代码

很显然写复杂了。

```cpp
pair<int, int> getpos(pair<int, int> t) {
	int x = t.first, y = t.second;
	for (int i = x; i <= n; ++ i )
		for (int j = i == x ? y : 1; j <= m; ++ j ) {
			bool flg = true;
			for (int t = 0; t < 4; ++ t ) {
				int nx = i + dx[t], ny = j + dy[t];
				if (nx > 0 && ny > 0 && nx <= n && ny <= m && a[nx][ny] >= a[i][j]) {
					flg = false;
					break;
				}
			}
			if (flg) return {i, j};
		}
	
	return {-1, -1};
}

void solve() {
	cin >> n >> m;
	
	for (int i = 1; i <= n; ++ i )
		for (int j = 1; j <= m; ++ j )
			cin >> a[i][j];
	
	pair<int, int> p = getpos({1, 1});
	while (~p.first) {
		int x = p.first, y = p.second;
		a[x][y] = -114514;
		for (int i = 0; i < 4; ++ i ) {
			int nx = x + dx[i], ny = y + dy[i];
			if (nx > 0 && ny > 0 && nx <= n && ny <= m) a[x][y] = max(a[x][y], a[nx][ny]);
		}
		
		p = getpos(p);
	}
	
	for (int i = 1; i <= n; ++ i ) {
		for (int j = 1; j <= m; ++ j ) {
			cout << a[i][j] << ' ';
		}
		cout << '\n';
	}
}
```

### 5. 证明

很显然前面那坨过不了审。补个证明。

实际上我们需要证明两件事情：

1. 如果 $(i, j)$ 是满足「大于所有与它相邻的值」的，那么接下来会「操作 $(i, j)$」若干**次**，直到 $a_{i,j}$ 不满足「大于所有与它相邻的值」，也就是成为这些值中的最大值。
2. 如果这一**轮**操作 $(i, j)$，那么下一**轮**操作的 $(i', j')$ 一定满足 $(i, j) < (i', j')$。

显然这两个命题可以合并成：

3. 如果这一**次**操作 $(i, j)$，那么下一**次**操作的 $(i', j')$ 一定满足 $(i, j) \le (i', j')$。

考虑反证法。证明：

4. 如果这一**次**操作 $(i, j)$，那么下一**次**操作的 $(i', j')$ 可能满足 $(i, j) > (i', j')$。

是伪的。

分类讨论。以下讨论的前提都是 $(i, j) > (i', j')$：

- $(i', j'),(i, j)$ 相邻：那么操作 $(i', j')$ 后一定有 $a_{i',j'} = \max(a_{i'-1,j'}, a_{i',j'-1}, a_{i', j'+1}, a_{i'+1,j}) \ge a_{i, j}$。此时显然无法「操作 $(i, j)$」，因为 $(i', j')$ 就是一个与 $(i,j )$ 相邻的且不大于 $a_{i, j}$ 的位置。因此矛盾。
- $(i', j'), (i, j)$ 不相邻：如果「操作 $(i, j)$」**后**可以「操作 $(i', j')$」，那么「操作 $(i, j)$」**前**也一定可以「操作 $(i', j')$」。所以上一步一定是「操作 $(i', j')$」而不是「操作 $(i, j)$」，这是因为 $(i', j') < (i, j)$。因此矛盾。

综上，原命题得证。

---

## 作者：ThisIsLu (赞：4)

赛时瞪眼瞪出来解法。

为了方便，以下的操作指把一个格子权值变成相邻格子权值的最大值。

让我们先想想，一个格子会被操作几次？

一个格子被操作了，则无论操作前操作后权值必然大于等于相邻格子的权值。

那么，相邻格子就无法被操作。

既然相邻格子不变，那么被操作的格子也不可能再操作一次。

这意味着，一个格子若被操作了，就会变成相邻格子的最大值，且相邻格子不可能被操作，也就是权值不变。

而又很明显，所有权值大于相邻格子的格子的都要操作。

所以说对于每个格子，先判断是否大于相邻格子，若大于则直接变成相邻格子的最大值即可。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=100;
int n,m,a[N+5][N+5];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
void solve(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int res=0;
            for(int k=0;k<4;k++){
                int nx=i+dx[k],ny=j+dy[k];
                if(1<=nx&&nx<=n&&1<=ny&&ny<=m){
                    res=max(res,a[nx][ny]);
                }
            }
            a[i][j]=min(a[i][j],res);
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) solve();
    return 0;
}
```

---

## 作者：GCSG01 (赞：1)

## 思路
模拟，我们按照题目所说，从 $(1,1)$ 到 $(n,m)$ 依次枚举 $a_{i,j}$，如果 $a_{i,j}$ 是周围四个中最大的一个，进行操作。  
操作：如果当前的数减 $1$ 后不满足条件，那么就不用再进行操作，如果减 $1$ 后任满足条件，那么它一定会减小至周围四个数的最大值，至此，输出即可。


## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int a[105][105];
void check(int x,int y)
{
	int A,B,C,D;
	A=B=C=D=0;
	if(x-1>=1)A=a[x-1][y];
	if(x+1<=n)B=a[x+1][y];
	if(y-1>=1)C=a[x][y-1];
	if(y+1<=m)D=a[x][y+1];
	int s=a[x][y];
	if(s<A||s<B||s<C||s<D)return;
	a[x][y]=max(A,max(B,max(C,D)));
	return ;
}
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				cin>>a[i][j];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				check(i,j);
		for(int i=1;i<=n;i++,cout<<"\n")
			for(int j=1;j<=m;j++)
				cout<<a[i][j]<<" ";
	}
	return 0;
}
```

---

## 作者：Harrylzh (赞：1)

## 思路
按题意模拟即可。


从上到下，从左到右枚举元素，每次如果此元素严格大于周围的元素，就赋值为周围四个元素中最大的。考虑会不会因为操作使得前面的元素不符合要求，因为操作以后还是没有严格小于周围的元素，所以不会。

注意，边上的元素取最大值时可能会超出边界，所以每组数据要把边界外的元素都设为 $0$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,m;
long long mp[2000+5][2000+5];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		long long ans=0;
		cin>>n>>m;
		for(long long i=0;i<=n+1;i++)
		{
			mp[i][0]=0;
			mp[i][m+1]=0;
		}
		for(long long i=0;i<=m+1;i++)
		{
			mp[0][i]=0;
			mp[n+1][i]=0;
		}
		for(long long i=1;i<=n;i++)
		{
			for(long long j=1;j<=m;j++)
			{
				cin>>mp[i][j];
			}
		}
		for(long long i=1;i<=n;i++)
		{
			for(long long j=1;j<=m;j++)
			{
				mp[i][j]=min(mp[i][j],max(mp[i-1][j],max(mp[i+1][j],max(mp[i][j-1],mp[i][j+1]))));
				cout<<mp[i][j]<<' ';
			}
			cout<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：FXLIR (赞：0)

### 题意
给你一个 $n \times m$ 的矩阵 $a$。

重复执行以下操作，直至无法执行：

- 找到一个大于所有相邻单元格的单元格 $a_{i,j}$，将其改为 $a_{i,j} - 1$。

在所有操作执行完毕后，输出矩阵 $a$。

### 做法

可以发现，对于一个 $a_{i,j}$，如果它被修改的话，最后它的值一定是它所有相邻单元格中的最大值。

由于数据范围很小，所以可以直接遍历整个矩阵，对于每个 $a_{i,j}$，如果它比它的所有相邻单元格都大，那么就把它更新为它所有相邻单元格中的最大值。

时间复杂度 $O(nm)$，可以通过本题。

### AC code

```cpp
#include<cstdlib>
#include<cstring>
#include<iostream>
#define int long long
using namespace std;
const int N=1e2+5;
int t,n,m,a[N][N];
int fmax(int i,int j,int k,int l){
	return max(max(i,j),max(k,l));
}
signed main(){
	cin>>t;
	while(t--){
		memset(a,0,sizeof(a));//清空是为了防止上一组样例中的矩阵影响下一组样例
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>a[i][j];
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){//从 1 开始是为了防止数组越界
				a[i][j]=min(a[i][j],fmax(a[i-1][j],a[i][j-1],a[i+1][j],a[i][j+1]));//fmax 取的是 a[i][j] 所有邻居中的最大值
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cout<<a[i][j]<<" ";
			}
			cout<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：int_stl (赞：0)

一道水题，赛后秒切。

首先，直接模拟是会超时的，但是我们有一个做法：令当前的 $a_{i, j}$ 变成：

$$
\max_{1 \le x \le n, 1 \le y \le m, |i - x| + |j - y| = 1} a_{x, y}
$$

这样做可以节省时间，因为我们很容易发现 $a_{i, j}$ 不能操作的条件是它严格不大于与它在一条公共边上的任意单元格，所以这个算法是正确的。

时间复杂度 $O(nm)$。

代码如下，注意一些小细节：

```cpp
int t;
int a[103][103], n, m;
int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };
int main() {
	read(t);
	while (t--) {
		read(n, m);
		FORL(i, 1, n, 1) {
			FORL(j, 1, m, 1) {
				read(a[i][j]);
			}
		}
		FORL(i, 1, n, 1) {
			FORL(j, 1, m, 1) {
				bool flag = 1;
				int maxn = -1;
				FORL(k, 0, 3, 1) {
					int xx = i + dx[k], yy = j + dy[k];
					if (xx < 1 || xx > n || yy < 1 || yy > m) continue;
					if (a[i][j] <= a[xx][yy]) {
						flag = 0;
						break;
					}
				}
				if (flag) {
					int cnt = 0;
					FORL(k, 0, 3, 1) {
						int xx = i + dx[k], yy = j + dy[k];
						if (xx < 1 || xx > n || yy < 1 || yy > m) continue;
						cnt++, maxn = max(maxn, a[xx][yy]);
					}
					if (cnt) a[i][j] = maxn;
				}
			}
		}
		FORL(i, 1, n, 1) {
			FORL(j, 1, m, 1) {
				writes(a[i][j]);
			}
			putchar('\n');
		}
	}
}
```

---

## 作者：ztksc07 (赞：0)

# 题解：CF1986B Matrix Stabilization

## 题目大意

给定一个矩阵，每次选择一个比它所有“邻居”都大的项，不断减一直到它不满足以上条件，求修改完后的矩阵。

“邻居”的定义是左右相邻或上下相邻，不包括对角线的情况。

## 解题思路

我们首先要明白一点，别看题目中讲要找坐标小的先修改，实际上修改顺序是不重要的。

而要明白这一点我们又要明白另一点，那就是所有被选中的项都互不是“邻居”。这一点很好想，假设有两个项 $a_{i,j}$ 和 $a_{i+1,j}$，它们互为邻居。你先修改 $a_{i,j}$，修改完成后 $a_{i,j}$ 应该等于它所有“邻居”中的最大值，而 $a_{i+1,j}$ 也是它的邻居，那么自然 $a_{i+1,j}$ 就不会比 $a_{i,j}$ 要大，不会被选中。

明白了这一点，刚才那一点也就好想了，因为不同被选中的项是互不干扰的，它们的“邻居”自始至终都不会变，先修改哪一个都无所谓。

那么我们从 $a_{1,1}$ 依次遍历到 $a_{n,m}$，看 $a_{i,j}$ 是否满足比所有“邻居”大的条件，如果是，那么就把 $a_{i,j}$ 直接修改为所有“邻居”中的最大值。全部修改完成后就是所求矩阵了。

## 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int t,n,m,maxx;
int a[110][110];
int main(){
	scanf("%d",&t);
	while(t--){
		memset(a,0,sizeof(a));
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				scanf("%d",&a[i][j]);
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				maxx=0;
				maxx=max(maxx,max(a[i+1][j],max(a[i-1][j],max(a[i][j+1],a[i][j-1]))));
				if(maxx<a[i][j]) a[i][j]=maxx;
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				printf("%d ",a[i][j]);
			}
			printf("\n");
		}
	}
	return 0;
}
```

时间复杂度 $O(nm)$，题目中说所有 $n \times m$ 的和不会超过 $2 \times 10^5$，稳过。

## 注意事项

- 如果不特判边界的话记得每次清空矩阵 $a$，否则在遍历到 $a$ 的边界时会受到上一次输入的干扰。

---

## 作者：linjinkun (赞：0)

就是一道模拟题。

首先满足题目要求的所有 $(i,j)$ 都是互不相邻的。

那么不管先操作那个 $(i,j)$ 都对答案没有影响。

我们可以将 $a_{i,j}$ 不断地减 $1$ 压缩成 $a_{i,j} = \max(a_{i+1,j},a_{i,j+1},a_{i-1,j},a_{i,j-1})$。因为只要与四个相邻的单元格相同，就会停止操作。

不过为了防止边界问题（这题可以不用考虑，是我多疑了），可以采用搜索的套路，设计两个方向数组，一个控制行，一个控制列。

代码（有注释）：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e2+5;
int a[N][N];
int dx[] = {0,0,-1,1};//方向数组
int dy[] = {-1,1,0,0};
signed main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n,m;
		scanf("%d %d",&n,&m);
		for(int i = 1;i<=n;i++)
		{
			for(int j = 1;j<=m;j++)
			{
				scanf("%d",&a[i][j]);
			}
		}
		for(int i = 1;i<=n;i++)
		{
			for(int j = 1;j<=m;j++)
			{
				bool flag = 1;//用来记录(i,j)是否满足题目要求
				int maxx = 0;//记录相邻点最大值
				for(int k = 0;k<4;k++)
				{
					int r = i+dx[k],c = j+dy[k];//正常套路
					if(r<=n&&c<=m&&r>=1&&c>=1)//判断没有超过边界
					{
						maxx = max(maxx,a[r][c]);//更新最大值
						if(a[r][c]>=a[i][j])//如果不符合要求
						{
							flag = 0;//记录不行
							break;//退出
						}
					}
				}
				if(flag == 1//成立
				{
					a[i][j] = maxx;//上面的压缩操作
				}
			}
		}
     //最后输出
		for(int i = 1;i<=n;i++)
		{
			for(int j = 1;j<=m;j++)
			{
				printf("%d ",a[i][j]);
			}
			printf("\n");
		}
	}
    return 0;
}
```

---

## 作者：Weekoder (赞：0)

### 思路

这里我们称“符合条件的数”为在题目中元素值严格大于所有相邻单元格的值的数。

结论：在 $a_{i,j},a_{i+1,j},a_{i,j+1},a_{i-1,j},a_{i,j-1}$ 这五个元素中，若 $a_{i,j}$ 为符合条件的数，则剩下的四个元素都不符合条件。也就是说，如果 $a_{i,j}$ 符合条件，则直接让 $a_{i,j}=\max(a_{i+1,j},a_{i,j+1},a_{i-1,j},a_{i,j-1})$ 即可。

时间复杂度 $\mathcal{O}(nm)$。

代码：

```cpp
#include <bits/stdc++.h>

#define int long long
    
using namespace std;

const int N = 105;

int T, n, m, a[N][N];

void solve(int i, int j) {
	int A, B, C, D;
	A = B = C = D = 0;
	if (i > 1) A = a[i - 1][j];
	if (j > 1) B = a[i][j - 1];
	if (i < n) C = a[i + 1][j];
	if (j < m) D = a[i][j + 1];
	if (a[i][j] <= A || a[i][j] <= B || a[i][j] <= C || a[i][j] <= D) {
		cout << a[i][j] << " ";
		return ;
	}
	a[i][j]	= max({A, B, C, D});
	cout << a[i][j] << " ";
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
	cin >> T;
	while (T --) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				cin >> a[i][j];
		for (int i = 1; i <= n; i++, cout << "\n")
			for (int j = 1; j <= m; j++)
				solve(i, j);
	}
    return 0;
}
```

---

## 作者：nightwatch.ryan (赞：0)

### 思路
题目中说严格大于所有相邻单元格的值才能进行 $-1$ 操作。这里先设这个值为 $x$。所以，$x$ 如果不能修改了，那么 $x$ 一定是其相邻单元格的最大值，并且 $x$ 的相邻单元格也不能被修改了，因为他们都不严格大于 $x$。

分类讨论：
- 一个单元格如果严格大于他的所有相邻单元格，那么我们就将这个单元格赋值为**他的所有相邻单元格的最大值**。
- 一个单元格如果不严格大于他的所有相邻单元格，那么这个单元格的值**不变**。

注意多测清空。
### 代码
```cpp
#include<iostream>
#include<algorithm>
#define int long long
#define N 105
int a[N][N],t,n,m;
signed main(){
	std::ios::sync_with_stdio(0);
	std::cin>>t;
	while(t--){
		std::cin>>n>>m;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				std::cin>>a[i][j];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				a[i][j]=std::min(a[i][j],std::max({a[i-1][j],a[i][j-1],a[i+1][j],a[i][j+1]}));
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)
				std::cout<<a[i][j]<<" ";
			std::cout<<std::endl;
		}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				a[i][j]=0;
	}
}
```

---

## 作者：GeYang (赞：0)

# 题意

给你一个 $n \times m$ 的矩阵 $a$。

- 找到一个大于附近四个单元格的单元格 $a_{i,j}$ 并将其改为 $a_{i,j-1}$。

- 重复执行以上指令直至无法执行。

求最后得出的矩阵。

# 思路

因为数据范围较小，所以可以直接遍历所有单元格，每次如果这个单元格大于附近所有的单元格，就赋值为附近四个元素中最大的。

因为操作一次之后还是不会出现小于四周单元格的单元格，所以不用担心操作一次之后会影响之前的单元格。

记得重置矩阵以防遍历到边界时上一组的数据影响下一组数据。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,m,maxn;
long long a[105][105];
void solve()
{
	memset(a,0,sizeof(a));//重置 
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			maxn=0;
			maxn=max(maxn,max(a[i+1][j],max(a[i-1][j],max(a[i][j+1],a[i][j-1]))));//比较 
			if(maxn<a[i][j]) a[i][j]=maxn;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cout<<a[i][j]<<" ";//输出 
		}
		cout<<endl;
	}
}
int main(){
	cin>>t;
	while(t--)
	{
		solve();
	} 
	return 0;
}
```

---

