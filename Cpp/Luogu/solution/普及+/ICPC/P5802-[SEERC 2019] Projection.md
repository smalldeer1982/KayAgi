# [SEERC 2019] Projection

## 题目描述

![TensorFlow](https://cdn.luogu.com.cn/upload/image_hosting/gdl3vztm.png)

你是一个 TensorFlow 的死忠粉，因此，你想要从两个投影图形来还原出 TensorFlow 的图标。

假定你有一个 3D 空间，尺寸为 $n \times m \times h$，以及两个投影图形（一个 $n \times m$ 的矩阵和一个 $n \times h$ 的矩阵，矩阵里的元素都为 $0$ 或 $1$）。你需要计算出一些 $1 \times 1 \times 1$ 的小正方体的集合，使得这些正方体放入 3D 空间后构成的立体的正投影（光照立体正面在立体后侧形成的投影）和右投影（光照立体左面在立体右侧形成的投影）与题目给定的投影图形一致。如果无解，输出 $-1$。如果有解，你需要计算出两个满足条件的集合，一个包含的小正方体数量最少，另一个最多。假定正方体的摆放不受重力影响（即小正方体在 3D 空间中可以随意放置，悬空也不需要支撑）。规定矩阵中的 $1$ 代表有阴影遮住，$0$ 代表无阴影遮住。

如果有多解，你需要输出字典序最小的解。一个解 $a$ 字典序比解 $b$ 小，当且仅当对于两个解中第一对不相同的数字，$a$ 中的数字小于 $b$ 中的。

例如，解 $[(0, 0, 0), (1, 1, 1)]$ 比解 $[(1, 1, 1), (0, 0, 0)]$ 字典序更小。

## 说明/提示

一个放置在 $(x, y, z)$ 的小正方体会在正投影的 $(x, y)$ 位置产生一个有阴影遮住的区域，并在右投影的 $(x, z)$ 位置产生一个有阴影遮住的区域。

坐标从 $0$ 开始编号。

## 样例 #1

### 输入

```
5 3 3
111
010
010
010
010
111
100
110
100
100```

### 输出

```
14
0 0 0
0 0 1
0 0 2
0 1 0
0 1 1
0 1 2
0 2 0
0 2 1
0 2 2
1 1 0
2 1 0
2 1 1
3 1 0
4 1 0
8
0 0 0
0 1 1
0 2 2
1 1 0
2 1 0
2 1 1
3 1 0
4 1 0```

## 样例 #2

### 输入

```
2 2 2
00
00
11
11```

### 输出

```
-1```

## 样例 #3

### 输入

```
2 3 2
101
011
10
11```

### 输出

```
6
0 0 0
0 2 0
1 1 0
1 1 1
1 2 0
1 2 1
4
0 0 0
0 2 0
1 1 0
1 2 1```

# 题解

## 作者：南阳刘子骥 (赞：8)

一道模拟题。  
题目说了让求两种情况，我这里也就分两种情况来说明。

在这之前先说明一下无解的情况。

无解的情况有且只有一种，就是对于某一层，一个视图里面有阴影而另一个视图里面没有。

## 块数最多

容易想到能填上的位置的都填上这一想法。

那么我们对于某一层正视图上的每一个阴影方块，找到同一层右视图中每一个阴影方块，在两者交汇的位置上放上一个方块，就可以把所有能填上的位置都填上方块了。

比如下图：

![p5802-1.png](https://s2.loli.net/2022/09/21/dZO6ItfJ9j2HheD.png)

## 块数最少

当某一层正视图与右视图阴影数量一样多的时候，可以明显想到一一对应这一解法。

而当数量不同的时候，我采用的策略是让多的一侧多出来的那一部分与少的一侧的第一个阴影匹配。

比如下面两个图：

![p5802-2.png](https://s2.loli.net/2022/09/21/ouCOjM3LUK46crS.png)

![p5802-3.png](https://s2.loli.net/2022/09/21/JKd7GeS2LO61yzv.png)

两图分别说明了正视图与右视图多出来的时候的解决方法。

## 实现

这里我使用 `vector` 存储代表方块的结构体，全部放进去之后再一遍 `sort()`，最后遍历输出答案即可。

为了方便遍历，我同样使用了 `vector` 来存储每一层两个视图的阴影状态，只不过这里是倒序存储的。

代码如下：

``` cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 110;
int n, m, h;
vector<int>frn[N], rgh[N];//front & right
struct Block
{
	int x, y, z;
	Block(int _x, int _y, int _z)
	{
		x = _x, y = _y, z = _z;
	}
	bool operator < (const Block &a) const
	{
		return (x == a.x) ? (y == a.y) ? (z < a.z) : (y < a.y) : (x < a.x);
	}
};
void solveMax()
{
	vector<Block>ans;
	for(int i = 0; i < n; i++)
		for(int j : frn[i])
			for(int k : rgh[i])
				ans.emplace_back(i, j, k);
	sort(ans.begin(), ans.end());
	printf("%d\n", ans.size());
	for(auto i : ans)
		printf("%d %d %d\n", i.x, i.y, i.z);
}
void solveMin()
{
	vector<Block>ans;
	for(int i = 0; i < n; i++)
	{
		if(frn[i].size() < rgh[i].size())
		{
			for(int j = 0; j < rgh[i].size(); j++)
				ans.emplace_back(i, frn[i][min((int)frn[i].size() - 1, j)], rgh[i][j]);
		}
		else if(frn[i].size() > rgh[i].size())
		{
			for(int j = 0; j < frn[i].size(); j++)
				ans.emplace_back(i, frn[i][j], rgh[i][min((int)rgh[i].size() - 1, j)]);
		}
		else
		{
			for(int j = 0; j < frn[i].size(); j++)
				ans.emplace_back(i, frn[i][j], rgh[i][j]);
		}
	}
	sort(ans.begin(), ans.end());
	printf("%d\n", ans.size());
	for(auto i : ans)
		printf("%d %d %d\n", i.x, i.y, i.z);
}
int main()
{
	scanf("%d%d%d", &n, &m, &h);
	for(int i = 0; i < n; i++)
	{
		string s;
		cin >> s;
		for(int j = m; ~j; j--)
			if(s[j] == '1')frn[i].push_back(j);
	}
	for(int i = 0; i < n; i++)
	{
		string s;
		cin >> s;
		for(int j = h; ~j; j--)
			if(s[j] == '1')rgh[i].push_back(j);
	}
	for(int i = 0; i < n; i++)
	{
		if(frn[i].empty() ^ rgh[i].empty())
		{
			puts("-1");
			return 0;
		}
	}
	solveMax();
	solveMin();
	return 0;
}
```



---

## 作者：jiezecheng (赞：0)

## 题解：P5802 [SEERC 2019] Projection

### 题意分析
给定一个三维结构（由边长为 $1$ 的正方体所构成）的后视图与左视图，求构成这个结构的正方体数量的最大值与最小值，输出每个正方体的具体位置。

本题解内含输出模拟器，可以翻到最后一点。
### 思路分析

不难想到两层之间是没有关联的，所以每一层分别处理。
#### 1. 最大值
这点比较容易，对于正方体 $(i,j,k)$ 如果后视图 $(i,j)$ 有阴影且左视图 $(i,k)$ 有阴影，这个方块就是合法的。
#### 1.5 无解判断

根据所求最大答案，尝试将答案还原为后视图与左视图，判断是否与题目给出的**完全一样**。

#### 2. 最小值
较难的是最小值，对于一层 $i$。



设其后视图阴影个数为 $cnt_1$，后视图阴影坐标存入 $F$；
左视图阴影个数为 $cnt_2$，左视图阴影坐标存入 $R$；
分 $3$ 种情况讨论。
- $cnt_1=cnt_2$：一一对应即可，即答案增加 $(i,F_j,R_j)(1\le j\le cnt_1)$；
- $cnt_1<cnt_2$：多的那个多出来的部分 $R_{j}(cnt_1\le j\le cnt_2)$ 对应少的第一个（$F_0$），剩余一一对应；
- $cnt_1>cnt_2$：多的那个多出来的部分 $F_{j}(cnt_2\le j\le cnt_1)$ 对应少的第一个（$R_0$），剩余一一对应。

### 代码
按照上述思路实现即可。（我写完代码才发现下标从 $0$ 开始，最后答案减一即可）。
:::info[代码能不看就不看]
```
#include<bits/stdc++.h>
using namespace std;
const int N=105;
int fr[N][N];
int ri[N][N];
int tfr[N][N];
int tri[N][N];
/*
For block(i,j,k)
front->(i,j)
right->(i,k)
*/
vector<pair<int,pair<int,int> > > ans_max;
vector<pair<int,pair<int,int> > > ans_min;

int main(){
	int n,m,h;
	cin>>n>>m>>h;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char c;
			cin>>c;
			if(c=='1'){
				fr[i][j]=1;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=h;j++){
			char c;
			cin>>c;
			if(c=='1'){
				ri[i][j]=1;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k=1;k<=h;k++){
				if(fr[i][j] and ri[i][k]){
					ans_max.push_back(make_pair(i,make_pair(j,k)));
				}
			}
		}
	}
	for(auto a:ans_max){
		tfr[a.first][a.second.first]=1;
		tri[a.first][a.second.second]=1;
	}
	bool flag=true;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k=1;k<=h;k++){
				if(tfr[i][j]!=fr[i][j] or tri[i][k]!=ri[i][k]){
					flag=false;
					break;
				}
			}
			if(!flag) break;
		}
		if(!flag) break;
	}
	if(!flag){
		cout<<"-1\n";
		return 0;
	}
	for(int i=1;i<=n;i++){
		vector<int> wait_fr;
		vector<int> wait_ri;
		for(int j=1;j<=m;j++){
			if(fr[i][j]){
				wait_fr.push_back(j);
			} 
		}
		for(int j=1;j<=h;j++){
			if(ri[i][j]){
				wait_ri.push_back(j);
			} 
		}
		if((int)wait_fr.size()==(int)wait_ri.size()){
			for(int j=0;j<(int)wait_fr.size();j++){
				ans_min.push_back(make_pair(i,make_pair(wait_fr[j],wait_ri[j])));
			}
		}else if((int)wait_fr.size()>(int)wait_ri.size()){
			int cha=(int)wait_fr.size()-(int)wait_ri.size();
			for(int j=0;j<wait_fr.size();j++){
				if(j<=cha){
					ans_min.push_back(make_pair(i,make_pair(wait_fr[j],wait_ri[0])));
				}else{
					ans_min.push_back(make_pair(i,make_pair(wait_fr[j],wait_ri[j-cha])));
				}
			}
		}else{
			int cha=(int)wait_ri.size()-(int)wait_fr.size();
			for(int j=0;j<wait_ri.size();j++){
				if(j<=cha){
					ans_min.push_back(make_pair(i,make_pair(wait_fr[0],wait_ri[j])));
				}else{
					ans_min.push_back(make_pair(i,make_pair(wait_fr[j-cha],wait_ri[j])));
				}
			}
		}
	}
	cout<<ans_max.size()<<"\n";
	for(auto a:ans_max){
		cout<<a.first-1<<" "<<a.second.first-1<<" "<<a.second.second-1<<"\n";
	}
	cout<<ans_min.size()<<"\n";
	for(auto a:ans_min){
		cout<<a.first-1<<" "<<a.second.first-1<<" "<<a.second.second-1<<"\n";
	}
	
	
}
```
:::
### 输出模拟

将你的答案（最大答案或最小答案）输入进此代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> x,y,z;
void out(vector<int> v){
	cout<<"[";
	for(int i=0;i<v.size();i++){
		cout<<v[i]<<((i==v.size()-1) ? "]" : ",");
	}
	cout<<"\n";
}
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		int a,b,c;
		cin>>a>>b>>c;
		x.push_back(a);
		y.push_back(b);
		z.push_back(c);
	}
	cout<<"X=";
	out(x);
	cout<<"Y=";
	out(y);
	cout<<"Z=";
	out(z);
	cout<<"D=(X,Y,Z)\n";
	cout<<"F=(X,Y)\n";
	cout<<"R=(X,Z)\n";
}
```
打开 [desmos3D](https://www.desmos.com/3d?lang=zh-CN) 将程序输出复制进去即可。

比如样例 $1$ 的最小情况输出：

[![pV8gunO.png](https://s21.ax1x.com/2025/07/21/pV8gunO.png)](https://imgse.com/i/pV8gunO)

---

