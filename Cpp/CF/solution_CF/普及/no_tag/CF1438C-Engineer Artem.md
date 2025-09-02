# Engineer Artem

## 题目描述

Artem is building a new robot. He has a matrix $ a $ consisting of $ n $ rows and $ m $ columns. The cell located on the $ i $ -th row from the top and the $ j $ -th column from the left has a value $ a_{i,j} $ written in it.

If two adjacent cells contain the same value, the robot will break. A matrix is called good if no two adjacent cells contain the same value, where two cells are called adjacent if they share a side.

Artem wants to increment the values in some cells by one to make $ a $ good.

More formally, find a good matrix $ b $ that satisfies the following condition —

- For all valid ( $ i,j $ ), either $ b_{i,j} = a_{i,j} $ or $ b_{i,j} = a_{i,j}+1 $ .

For the constraints of this problem, it can be shown that such a matrix $ b $ always exists. If there are several such tables, you can output any of them. Please note that you do not have to minimize the number of increments.

## 说明/提示

In all the cases, you can verify that no two adjacent cells have the same value and that $ b $ is the same as $ a $ with some values incremented by one.

## 样例 #1

### 输入

```
3
3 2
1 2
4 5
7 8
2 2
1 1
3 3
2 2
1 3
2 2```

### 输出

```
1 2
5 6
7 8
2 1
4 3
2 4
3 2```

# 题解

## 作者：彭天宇 (赞：14)

乍看有一个思路：把矩阵上的数字存入结构体，按照大小排序，最大的数字$+1$显然不会与别的数字不等，也不会影响答案。那么就这样从大到小处理，$+1$能够不矛盾的，就$+1$，否则不加。

就是这样：

```cpp
bool cmp(shuzu x,shuzu y){
	if(x.num==y.num&&x.x==y.x)return x.y<y.y;
	if(x.num==y.num)return x.x<y.x;
	return x.num>y.num;
}
int main(){
	T=read();
	while(T--){
		cnt=0;
		n=read(),m=read();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				s[i][j]=read();
				a[++cnt].num=s[i][j];
				a[cnt].x=i;
				a[cnt].y=j;
			}
		sort(a+1,a+cnt+1,cmp);
		for(int i=1;i<=cnt;i++){
			int x=a[i].x,y=a[i].y;
			if(s[x][y]+1!=s[x-1][y]&&s[x][y]+1!=s[x][y-1]&&s[x][y]+1!=s[x+1][y]&&s[x][y]+1!=s[x][y+1])s[x][y]++;
			a[i].num++;
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)printf("%d ",s[i][j]);
			printf("\n");
		}
	}
	return 0;
}
```
然而很显然这个贪心是错误的，可以构造如下数据：

$3\ 3\ 4$

$4\ 4\ 4$

按照规定方法操作之后发现：（蓝色表示已经处理完毕的数字）

$3\ 3\ \color{blue}{5}$

$\color{blue}{5}\ \color{blue}{4}\ \color{black}{4}$

左下角的$4$加也不对，不加也不对，就出锅了。
### 正解
每个数$+1$其实是改变了一个数的奇偶性，奇数不可能等于偶数，那么就可以将相邻的数字奇偶性保证不同，像棋盘一样。（详见代码）

$\color{black}{odd}\ \color{red}{even}\ \color{black}{odd}\ \color{red}{even}\ \color{black}{odd}\ \color{red}{even}\ $


$\color{red}{even}\ \color{black}{odd}\ \color{red}{even}\ \color{black}{odd}\ \color{red}{even}\ \color{black}{odd}\ $


$\color{black}{odd}\ \color{red}{even}\ \color{black}{odd}\ \color{red}{even}\ \color{black}{odd}\ \color{red}{even}\ $


$\color{red}{even}\ \color{black}{odd}\ \color{red}{even}\ \color{black}{odd}\ \color{red}{even}\ \color{black}{odd}\ $
```cpp
int main(){
	T=read();
	while(T--){
		n=read(),m=read();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				s[i][j]=read();
				if((i+j)%2==0&&s[i][j]%2==0)s[i][j]++;
				if((i+j)%2==1&&s[i][j]%2==1)s[i][j]++;
			}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)printf("%d ",s[i][j]);
			printf("\n");
		}
	}
	return 0;
}

```
不是很好想到的方法，也不能通过样例推测生成方式，大约只能通过$+1$的特殊性想到吧，这题算是让我拓宽了思路。

---

## 作者：EuphoricStar (赞：6)

## 思路

提供一个 2-SAT 的解法（

对于每个元素建立两个点 $(x,y)$ 和 $\neg(x,y)$，分别表示 $(x,y)$ 不加一和加一。然后对于每一个格子 $(x,y)$，枚举与它相邻的格子 $(nx, ny)$。易知它们可能会产生冲突当且仅当 $|a_{x,y} - a_{nx,ny}| \le 1$。

- 若 $a_{x,y} = a_{nx,ny}$，则要么 $a_{x,y}$ 加一，要么 $a_{nx,ny}$ 加一。连 $(x,y) \to \neg(nx,ny)$，$\neg(x,y) \to (nx,ny)$。

- 若 $a_{x,y} + 1 = a_{nx,ny}$，则如果 $a_{x,y}$ 加一，$a_{nx,ny}$ 也必须加一，否则它们就相等了。连 $\neg(x,y) \to \neg(x,y)$。

- 若 $a_{x,y} - 1 = a_{nx,ny}$，则如果 $a_{x,y}$ 不加一，$a_{nx,ny}$ 也必须不加一。连 $(x,y) \to (nx,ny)$。

最后跑一遍 2-SAT 再输出方案即可。

## 代码

[code](https://codeforces.com/contest/1438/submission/155285909)

---

## 作者：zhouchuer (赞：3)

## [题目传送门](https://www.luogu.com.cn/problem/CF1438C)

### 思路
很简单，只要分类讨论一下即可。

如果 $i+j$ 与 $a_{i,j}$ 奇偶性不同就把 $a_{i,j}$ 加一，否则不变，目的就是让相邻两个值奇偶性相反。

为什么要这样做呢？因为奇偶性不同的数肯定不会相等，这一做法的目的就是让奇偶数错开，绝对不会有相邻元素相等。

### 方法正确性证明
我们来验证一下这个方法的可行性。

给大家一个 $4 \times 4$ 的矩阵：
```c
0 9 6 0
1 1 2 7
1 2 7 6
1 2 7 9
```
那么操作之后矩阵就是这样：
```c
0 9 6 1
1 2 3 8
2 3 8 7
1 2 7 10
```
是不是符合要求了？那我们思考一下，$i+j$ 和 $i+j+1$ 肯定不相等吧？那么不论是前后还是左右，只要用这个条件判断改造数组，相邻的数必定只有奇数和偶数，奇数和偶数当然不相等，所以这种方法可以解决此问题。

### 不完全代码
```c
#include<bits/stdc++.h>
using namespace std;

int a[105][105];
int main(){
	int t,n,m; 
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>a[i][j];
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if() a[i][j]+=1;//如果 i+j 和 a[i][j] 奇偶性不同，就把 a[i][j] 加一
			}
		}
		//以下是输出，不用我再打一遍了吧
		for(){
			for(){
				
			}
		}
	}
	return 0;
}
```
要是对代码有疑问可以看[这篇题解](https://www.luogu.com.cn/article/e2p2srkr)。

---

## 作者：WangYunpei (赞：2)

### 题意
给出一个$n\times m$的矩阵$a$,可将矩阵中若干个元素加一使得矩阵里没有相邻两个数字相同，输出修改后的矩阵。

------------

### 思路
+ 1.奇数不等于偶数(废话)
+ 2.一个奇数一定可以通过加1变成偶数(还是废话)
+ 3.一个偶数一定可以通过加1变成奇数(仍然是废话)

虽然是三条废话，但合起来就是这道题的正解，根据第一条废话，可以知道假如修改后的矩阵是奇数旁边全是偶数，偶数旁边全是奇数，是可以的。根据第二条和第三条废话，可以知道，一定可以通过修改将矩阵中的任何一个数的奇偶性变成想要的。就可以变成奇数旁边全是偶数，偶数旁边全是奇数。
### 代码
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int t,n,m,a[105][105];//t组数据，n行，m列，a是原矩阵
int main(){
	cin>>t;
	while(t--){//相当于for(int i=1;i<=t;i++)
		cin>>n>>m;//n行，m列
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				cin>>a[i][j];//输入矩阵
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){//循环每个点
				if(a[i][j]%2!=(i+j)%2)//每个点的行列坐标之和的奇偶性一定和它相邻的点不同，所以只要输出的数与行列坐标之和的奇偶性相同，就一定与它相邻的点不同
					cout<<a[i][j]+1<<" ";
				else
					cout<<a[i][j]<<" ";
			}				
			cout<<endl;
		}			
	}
}
```


---

## 作者：Milky_Cat (赞：1)

前言：和机房初二 Master 大神 duel 的时候做到了这题，看到 2-SAT 标签豁然开朗，结果险胜。

注意到这道题每一个格子都有 $+1$ 和 $+0$ 两种状态，可以对应布尔型变量，自然而然就能想到 2-SAT。

我们不妨考虑如何建图。注意到：

+ 如果两个格子相邻且相等，两个格子中至少要有一个是 $0$，至少要有一个是 $1$，否则依然相等。

+ 如果两个格子相邻且差 $1$，较小的格子为 $0$ 或者较大的格子为 $1$，否则这两个格子相等。

于是我们建图跑 Tarjan 就做完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, m, a[105][105];
int dx[] = {0, 1, -1, 0, 0}, dy[] = {0, 0, 0, 1, -1};
int tid(int x, int y){
	return (x - 1) * m + y;
}
bool Invalid(int x, int y){
	if (x < 1 || y < 1 || x > n || y > m)
		return 1;
	else
		return 0;
}
vector<int> G[2000005], SCC[2000005];
int ig[2000005], dfn[2000005], low[2000005], col[2000005], vl[2000005];
int a1, a2, cnt, ign, ans, ccnt;
bool vis[2000005], vvis[2000005];
stack<int> s;
queue<int> q;
void tarjan(int u){
	dfn[u] = low[u] = ++cnt;
	s.push(u);
	vis[u] = 1;
	for (auto &v : G[u]){
		if (!dfn[v]){
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}else if (vis[v])
			low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]){
		ccnt++;
		while (!s.empty()){
			int v = s.top();
			s.pop();
			vis[v] = 0;
			col[v] = ccnt;
			SCC[u].push_back(v);
			if (u == v)
				break;
		}
	}
}
void addedge(int u, int a, int v, int b){
	G[u + n * m * a].push_back(v + n * m * (b ^ 1));
	G[v + n * m * b].push_back(u + n * m * (a ^ 1));
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> t;
	while (t--){
		cin >> n >> m;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				cin >> a[i][j];
		for (int i = 1; i <= ccnt; i++)
			SCC[i].clear();
		for (int i = 1; i <= 2 * n * m; i++){
			G[i].clear();
			vis[i] = 0;
			col[i] = 0;
			low[i] = dfn[i] = 0;
		}
		cnt = ccnt = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++){
				for (int k = 1; k <= 4; k++){
					int nx = i + dx[k], ny = j + dy[k];
					if (Invalid(nx, ny))
						continue;
					if (a[nx][ny] == a[i][j]){
						int u, a, v, b;
						u = tid(i, j), v = tid(nx, ny);
						a = 1; b = 1;
						addedge(u, a, v, b);
						a = 0; b = 0;
						addedge(u, a, v, b);
					}else if (a[nx][ny] == a[i][j] + 1){
						int u, a, v, b;
						u = tid(i, j), v = tid(nx, ny);
						a = 0, b = 1;
						addedge(u, a, v, b);
					}else if (a[nx][ny] == a[i][j] - 1){
						int u, a, v, b;
						u = tid(i, j), v = tid(nx, ny);
						a = 1, b = 0;
						addedge(u, a, v, b);
					}
				}
			}
		for (int i = 1; i <= 2 * n * m; i++)
			if (!dfn[i])
				tarjan(i);
	//	for (int i = 1; i <= 2 * n * m; i++)
	//		cout << col[i] << " ";
	//	cout << "\n";
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= m; j++)
				cout << a[i][j] + (col[tid(i, j)] < col[tid(i, j) + n * m]) << " ";
			cout << "\n";
		}
	}
	return 0;
}
```

---

## 作者：Rubedo_N (赞：1)

# CF1438C Engineer Artem 题解
## [题目传送门](https://www.luogu.com.cn/problem/CF1438C)
## 思路
一个奇数和一个偶数不可能相等，导致相邻两数不相等。  
于是得出解法：确定每一个位置的奇偶性。如果 $a_{i,j}$ 与 $i+j$ 奇偶性不同，则按照 $b_{i,j}=a_{i,j}+1$ 修改。
## 核心代码
```cpp
for(int i=1;i<=n;i++){
	for(int j=1;j<=m;j++){
		if(a[i][j]%2!=(i+j)%2)a[i][j]++;//奇偶性不同，进行操作。
	}
}
```

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2000}$

---
### 解题思路：

本质上是诈骗题。

任何一个奇数和任何一个偶数都不可能相等，而题目中给出的数都是可以自由选择奇偶性的。

所以不妨确定每一个位置的奇偶性，然后直接按照那个更改就好了。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
int T,n,m,x;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				scanf("%d",&x);
				if((i+j)%2==0)x+=(x%2==0);
				else x+=(x%2==1);
				printf("%d ",x);
			}
			printf("\n");
		}
	}
	return 0;
}
```


---

## 作者：Aiopr_2378 (赞：1)

### 思路分析

根据题目，我们可以对每一个元素进行加一操作，并且只能操作一次。

~~根据CF做题法则，~~ 我们就可以将题目进行翻译。由题可得出，其实我们的操作就是将元素进行**奇偶性转换**。如果我们把元素弄成了奇偶交错排列的情况（如下图，奇数用 `⚪` 表示，偶数用 `×` 表示），就一定合法。

	⚪ × ⚪ × ⚪ ×
	× ⚪ × ⚪ × ⚪
  	⚪ × ⚪ × ⚪ ×
  	× ⚪ × ⚪ × ⚪
  	⚪ × ⚪ × ⚪ ×
  	× ⚪ × ⚪ × ⚪
    
这样，我们就可以轻松地根据当前为应该为的奇偶性，来进行加一操作。

可以用一组样例进行详细说明。

1. 读入一组样例：

        1 1
        2 2
        
1. 分析样例奇偶性：
 
        ⚪ ⚪
         ×  ×

        
1. 根据排列法则进行加一操作即可：

        1 2
        2 3
        
### 参考程序

```cpp
#include<iostream>
using namespace std;
int n,m,k,a[105][105];
int main(){
    cin>>k;
    while(k--){
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++) cin>>a[i][j];
        }
        for(int i=1;i<=n;i++){
            bool op=i%2;//分析每行开始应该是奇数还是偶数
            for(int j=1;j<=m;j++){
                //对不符合奇偶排序的数进行加一操作以更改当前数奇偶性
                if(a[i][j]%2!=op) a[i][j]++;
                op=op^1;
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                cout<<a[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    return 0;
}
```


---

## 作者：mot1ve (赞：1)

由于只能 $+1$ ，可以想到奇偶性的变化，奇数一定不等于偶数，所以一奇一偶构造就行了，真的没什么好说的。算是一个比较套路的题。



``` 
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,T;
int a[110][110],b[110][110];
signed main()
{
	cin>>T;
	while(T--)
	{
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				scanf("%lld",&a[i][j]);
			}
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(i%2==1)//开头放奇 
				{
					if(j%2==1)//这个要放奇 
					{
						if(a[i][j]%2!=1)
						a[i][j]++;
					}
					if(j%2==0)
					{
						if(a[i][j]%2!=0)//这个要放偶 
						a[i][j]++;
					}
				}
				if(i%2==0)//开头放偶 
				{
					if(j%2==1)//这个要放偶 
					{
						if(a[i][j]%2!=0)
						a[i][j]++;
					}
					if(j%2==0)
					{
						if(a[i][j]%2!=1)//这个要放奇
						a[i][j]++;
					}
				}
			}
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				cout<<a[i][j]<<" ";
			}
			cout<<endl;
		}
	}
	return 0;
} 

---

## 作者：—维尼— (赞：1)

## 题目大意
给定一个矩阵，任意一个格子，你可以选择使格子上的数加一，最后要保证矩阵内相邻的数不相等，输出这个矩阵

## 题目思路

虽然只有加一的选择，但是我们可以通过相邻元素奇偶性的不同来保证相邻元素不相同

怎么做，我们在奇数行保证整行数按照（奇偶奇偶奇偶……）这样排列

偶数行保证整行按照（偶奇偶奇偶奇……）这样排列

举个例子

$1\ 2$

$3\ 2$

这个矩阵

奇数行已经是目标序列了

我们把偶数行改成偶奇偶奇……

即为

$1\ 2$

$4\ 3$

所以这种方法是明显可行的

注意分类讨论就行

## 代码
```c++
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int a[105][105];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,m;
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)
				cin>>a[i][j];
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(i%2){
					if(j%2){
						if(a[i][j]%2==0)
							cout<<a[i][j]+1<<" ";
						else
							cout<<a[i][j]<<" ";
					}
					else{
						if(a[i][j]%2==0){
							cout<<a[i][j]<<" ";
						}
						else
							cout<<a[i][j]+1<<" ";
					}
				}
				else{
					if(j%2){
						if(a[i][j]%2)
							cout<<a[i][j]+1<<" ";
						else
							cout<<a[i][j]<<" ";
					}
					else{
						if(a[i][j]%2)
							cout<<a[i][j]<<" ";
						else
							cout<<a[i][j]+1<<" ";
					}
				}
			}
			cout<<endl;
		}
	}
}

```

---

## 作者：Beautiful_nebula (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF1438C)
### 思路
这是一道比较简单的黄题，代码不是很难，但是有一定的思维难度。

题目要求我们改造一个矩阵，可以将若干个元素加一，相邻的两个元素一定不相等。看到这些马上想到可以用奇偶性做这道题：定义一个二维数组 $a$，输入完毕后遍历一下二维数组，如果 $i+j$ 与 $a_{i,j}$ 奇偶性相同就将 $a_{i,j}$ 加一，这样就可以让奇偶性相同的数错开，这道题目就通过了。

举个例子理解一下：
```cpp
1 1
1 0
2 1
```
把矩阵变成这样就是合法的：
```cpp
1 2
2 1
3 2
```
是不是解决问题了？那么就按照这个思路写代码。

### 核心代码
```cpp
for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
        if((i+j)%2!=a[i][j]%2) a[i][j]+=1;
    }
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
不难发现奇偶性不同的数一定不同（废话），而 $+1$ 操作可以改变一个数的奇偶性，所以我们只要对数组黑白染色，一边变奇数一边变偶数即可。
# 代码
```cpp
# pragma GCC optimize("Ofast,no-stack-protector")
# pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
# include <bits/stdc++.h>
# define I return
# define AK 0
# define IOI ;
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n, m, x;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n >> m;
		for (int i = 0; i < n; ++ i, cout << '\n')
			for (int j = 0; j < m; ++ j)
				cin >> x, cout << x + ((i ^ j ^ x) & 1) << ' ';
	}
	I AK IOI
}
```

---

## 作者：ZettaByte (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1438C)

### 题意

给你一个矩阵 $a$，你可以选择任意个数增加 $1$，最终你需要使得 $a$ 中相邻的元素互不相等。

### 解法

感谢 @[qxp101](https://www.luogu.com.cn/user/223559) 的题解，神啊。

我们只需判断 $a_{i,j}$ 的奇偶性是否与 $i+j$ 相同即可，若不相同则增加 $1$。

因为奇偶性不同的两个数不可能相等，所以相邻的数必然不会相等。

#### AC CODE：

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[110][110];

int main()
{
	int T; scanf("%d", &T);
	while (T--)
	{
		int n, m; scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				if (a[i][j] % 2 != (i + j) % 2) a[i][j]++;
		for (int i = 1; i <= n; i++, printf("\n"))
			for (int j = 1; j <= m; j++) printf("%d ", a[i][j]);
	}
	return 0;
}
```

---

## 作者：JWRuixi (赞：0)

这道题很有质量。

- **题意**

调整一个矩阵使得任意相邻两个元素不相等。

- **分析**

遇到这种类型的题，第一想法应该是贪心，我觉得应该有两种大致的思路——大小和奇偶性。

如果分析大小的话，必须考略改变数字对之前已经确定的数字的影响，不甚好做。

所以分析一下奇偶，可以通过每一个位置的坐标来确定。

对于一个坐标 $(i,j)$ :

1. 若 $i+j$ 为偶，令 $mps_{i,j}$ 为偶；
2. 若 $i+j$ 为奇，令 $mps_{i,j}$ 为奇；

- **CODE :**

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace q_wr {
	inline int read() {
		char c = getchar();
		int x = 0, f = 1;
		while (c < '0' || c > '9') {
			if (c == '-') f = -1;
			c = getchar();
		}
		while (c >= '0' && c <= '9') {
			x = (x << 1) + (x << 3) + c - '0';
			c = getchar();
		}
		return x * f;
	}
	inline void write(int x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using namespace q_wr;

int t, n, m, mps[2000][2000], ans[2000][2000];

int main () {
	t = read();
	while (t--) {
		n = read(), m = read();
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				mps[i][j] = read();
				ans[i][j] = abs(mps[i][j] % 2 - (i + j) % 2);//记录是否要改变奇偶性
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				write(mps[i][j] + ans[i][j]);//输出结果
				putchar(' ');
			}
			putchar('\n');
		}
	}
} 
```


---

## 作者：sinsop90 (赞：0)

我们可以轻易得到如果 $k_1 = 2n$, $k_2 = 2m+1$ (n, m为正整数)，则必定有 $k_1≠k_2$

因此我们想到改变原本的矩阵，使得任意两个相邻的元素奇偶性不同

假设 $1,1$ 上面的元素为奇数，则 $(1,2)$ 上面的元素为偶数，$(2,1)$ 也一样为偶数

易得若一个坐标为 $(i,j)$：

如果 $i , j$ 均为奇数,则 $b_{i,j}$ 应该为奇数

如果 $i , j$ 中正好一个为偶数,则 $b_{i,j}$ 应该为偶数

如果 $i , j$ 都为偶数,则 $b_{i,j}$ 应该为奇数

因此有如下代码:

```
#include <bits/stdc++.h>
using namespace std;
int T, n, m, mps[1005][1005];
int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1;i <= n;i++) {
			for(int j = 1;j <= m;j++) {
				scanf("%d", &mps[i][j]);
				if(i % 2 == 1 && j % 2 == 1 && mps[i][j] % 2 == 0) mps[i][j] ++;
				if(i % 2 == 1 && j % 2 == 0 && mps[i][j] % 2 == 1) mps[i][j] ++;
				if(i % 2 == 0 && j % 2 == 1 && mps[i][j] % 2 == 1) mps[i][j] ++;
				if(i % 2 == 0 && j % 2 == 0 && mps[i][j] % 2 == 0) mps[i][j] ++;
			}
		}
		for(int i = 1;i <= n;i++) {
			for(int j = 1;j <= m;j++) {
				cout << mps[i][j] << " ";
			}
			cout << endl;
		}
	}
}
```


---

