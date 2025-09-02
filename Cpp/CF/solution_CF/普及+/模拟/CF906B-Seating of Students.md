# Seating of Students

## 题目描述

Students went into a class to write a test and sat in some way. The teacher thought: "Probably they sat in this order to copy works of each other. I need to rearrange them in such a way that students that were neighbors are not neighbors in a new seating."

The class can be represented as a matrix with $ n $ rows and $ m $ columns with a student in each cell. Two students are neighbors if cells in which they sit have a common side.

Let's enumerate students from $ 1 $ to $ n·m $ in order of rows. So a student who initially sits in the cell in row $ i $ and column $ j $ has a number $ (i-1)·m+j $ . You have to find a matrix with $ n $ rows and $ m $ columns in which all numbers from $ 1 $ to $ n·m $ appear exactly once and adjacent numbers in the original matrix are not adjacent in it, or determine that there is no such matrix.

## 说明/提示

In the first test case the matrix initially looks like this:

`<br></br>1 2 3 4<br></br>5 6 7 8<br></br>`It's easy to see that there are no two students that are adjacent in both matrices.

In the second test case there are only two possible seatings and in both of them students with numbers 1 and 2 are neighbors.

## 样例 #1

### 输入

```
2 4
```

### 输出

```
YES
5 4 7 2 
3 6 1 8 
```

## 样例 #2

### 输入

```
2 1
```

### 输出

```
NO
```

# 题解

## 作者：L7_56 (赞：3)

### 题目大意
---
有一个 $n*m$ 矩阵从 $1$ 一直到 $n*m$

现在要重新排列使得矩阵中没有两个原来相邻的元素相邻

### 分析
---
容易想到暴搜，用dfs枚举每一个点放什么数

但是看数据可以发现，$n,m \le 10^5$

如果开二维数组肯定会炸

又看到 $n*m \le 10^5$

想到用一维数组来存

二维数组有一种表示方式就是

$$a[][]=\{\{ a_{1,1},a_{1,2},a_{1,3} \}, \{a_{2,1},a_{2,2},a_{2,3}\}\}$$

只要把它转化成

$$a'[]=\{a'_1,a'_2,a'_3,a'_4,a'_5,a'_6\}$$

就好了

转化的方法是

$$a_{i,j}\Leftrightarrow a'_{i*m+j}$$

### 代码
---
```cpp
#include<bits/stdc++.h>
#define maxn 100000
using namespace std;

int a[maxn+10];
int n,m;

int xx[]={1,0,-1,0};
int yy[]={0,1,0,-1};

bool beside(int a,int b){
	if(a+m==b||a-m==b||a+1==b||a-1==b) return 1;
	return 0;
}//判断两个数原来是不是挨着的

bool flag;

void dfs(int p){
	if(p==n*m){
		flag=1;return;
	}
	int xp=p/m;
	int yp=p%m;
	for(int i=p;i<n*m;++i){
		swap(a[p],a[i]);
		if((xp&&beside(a[p],a[(xp-1)*m+yp]))||(yp&&beside(a[p],a[xp*m+yp-1])))
		 continue;
		dfs(p+1);
		if(flag) return;
		swap(a[p],a[i]);
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for(int i=0;i<n*m;++i) a[i]=i;
	dfs(0);
	if(flag){
		printf("YES\n");
		for(int i=0;i<n;++i){
			for(int j=0;j<m;++j)
			 printf("%d ",a[i*m+j]+1);
			printf("\n");
		}
	}
	else printf("NO\n");
	return 0;
}

```

---

## 作者：cmll02 (赞：1)

本题解不是搜索。

考虑构造。

将一个图黑白格染色，左上角是黑格。

之后每个白格向下平移四格。如果出图了就从上面回来。

这样可以解决 $n\ge 8$ 或者 $m\ge 8$ 的情况。

但是较小的时候不行。

我们又有一种做法，先将每行打乱：

（举例）Input
```
5 1
```
Output
```
5 3 1 4 2
```
奇偶分开，倒着排序就行了。

再将列也这样做就行了。

这样可以解决 $n\ge4$ 且 $m\ge 4$ 的情况。

那么剩下的情况手算出答案即可。

注意二维数组要 `new` 开。

Code:

```cpp
#include <stdio.h>
#include <string.h>
#include <queue>
inline int read()
{
    int num=0,f=1;char c=getchar();
    while(c<48||c>57){if(c=='-')f=-1;c=getchar();}
    while(c>47&&c<58)num=(num<<3)+(num<<1)+(c^48),c=getchar();
    return num*f;
}
inline int read1d()
{
    int num=0;char c=getchar();
    while(c<48||c>57){c=getchar();}
    return c&1;
}
namespace subtask1{
	void solve(int n,int m)
	{
		puts("YES");
		int cnt=0;
		int **b=new int*[n];
		for(int i=0;i<n;i++)b[i]=new int[m];
		int u=n&2147483646;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
			{
				cnt++;
				if((i+j+1)&1)b[i][j]=cnt;
				else
				{
					int q=i+4;
					if(q>=n)
					{
						if(n&1)
							if(q&1)q=q-n+1;
							else q=q-n-1;
						else q=q-n;
					}
					b[q][j]=cnt;
				}
			}
		}
		for(int i=0;i<n;i++,puts(""))
			for(int j=0;j<m;j++)printf("%d ",b[i][j]);
		delete[] b;
	}
}
namespace subtask2{
	void solve(int n,int m)
	{
		puts("YES");
		int cnt=0;
		int **b=new int*[n];
		for(int i=0;i<n;i++)b[i]=new int[m];
		int u=m&2147483646;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
			{
				cnt++;
				if((i+j+1)&1)b[i][j]=cnt;
				else
				{
					int q=j+4;
					if(q>=m)
					{
						if(m&1)
							if(q&1)q=q-m+1;
							else q=q-m-1;
						else q=q-m;
					}
					b[i][q]=cnt;
				}
			}
		}
		for(int i=0;i<n;i++,puts(""))
			for(int j=0;j<m;j++)printf("%d ",b[i][j]);
		delete[] b;
	}
}
#define p(a,b) else if(n==a&&m==b)
namespace subtask3{
	void fill(int*a,int n,int d)
	{
		int cnt=1;
		for(int i=(n+1)>>1;i>0;i--)a[i-1]=d+cnt,cnt+=2;
		cnt=n;
		for(int i=2;i<=n;i+=2)a[--cnt]=d+i;
	}
	void filll(int*a,int m,int d,int n)
	{
		//a a+d a+dd a+ddd a+dddd 
		//a+dddd a+dd a a+ddd a+d
	//	printf("filling %d %d %d %d\n",a,m,d,n);
		int cnt=0;
		for(int i=(n+1)>>1;i>0;i--)a[i-1]=d+cnt,cnt+=m+m;
		cnt=n;
		for(int i=2;i<=n;i+=2)a[--cnt]=d+(i-1)*m;
		for(int i=0;i<n;i++)printf("%d ",a[i]);puts("");
	}
	void solve(int n,int m)
	{
		if(n==1&&m==1)puts("YES\n1");
		else if(n==1&&m==2)puts("NO");
		else if(n==2&&m==1)puts("NO");
		else if(n==2&&m==2)puts("NO");
		else if(n==2&&m==3)puts("NO");
		else if(n==3&&m==2)puts("NO");
		else if(n+m==4)puts("NO");
		else if(n==3&&m==3)puts("YES\n5 1 6\n3 9 4\n7 2 8");
		else
		{
			puts("YES");
			if(n==1&&m==4)puts("3 1 4 2");
			p(2,4)puts("1 3 5 7\n6 8 2 4");
			p(3,4)puts("3 1 7 2\n8 6 4 5\n11 9 12 10");
			//p(4,4)puts("11 2 9 4\n5 16 7 14\n3 10 1 12\n13 8 15 6");
			p(1,5)puts("1 3 5 2 4");
			p(2,5)puts("5 3 1 4 6\n9 7 10 2 8");
			p(3,5)puts("9 3 1 4 6\n13 5 11 14 8\n15 7 10 2 12");
			//p(4,5)puts("7 1 5 12 10\n11 3 15 16 14\n13 9 2 4 18\n13 19 6 8 20");
			//p(5,5)puts("13 3 1 4 8\n15 5 7 10 12\n19 9 11 14 16\n23 17 20 2 22\n25 21 24 6 18");
			p(6,1)puts("1\n3\n5\n2\n4\n6\n");
			p(6,2)puts("1 4\n5 8\n9 12\n2 3\n6 7\n10 11\n");
			p(6,3)puts("1 3 5\n7 9 11\n13 15 17\n2 4 6\n8 10 12\n14 16 18");
			//p(6,4)puts("2 4 5 7\n10 12 13 15\n18 20 21 23\n1 3 6 8\n9 11 14 16\n17 19 22 24");
			//p(6,5)puts("1 3 5 7 9\n11 13 15 17 19\n21 23 25 27 29\n2 4 6 8 10\n12 14 16 18 20\n22 24 26 28 30");
			//p(6,6)puts("")
			p(7,1)puts("7 5 3 1 6 4 2");
			p(7,2)puts("1 5 9 13 4 8 12\n3 7 11 2 6 10 14");
			p(7,3)puts("19 11 3 1 6 4 12\n15 13 5 9 14 8 16\n21 17 7 20 2 10 18");
			p(4,1)puts("3\n1\n4\n2");
			p(4,2)puts("1 6\n4 7\n5 2\n8 3");
			p(4,3)puts("1 3 5\n7 9 11\n6 4 2\n8 10 12");
			p(5,1)puts("1\n3\n5\n2\n4");
			p(5,2)puts("1 6\n4 7\n5 10\n8 3\n9 2");
			p(5,3)puts("1 3 5\n7 9 11\n13 15 2\n4 6 8\n10 12 14");
			p(1,6)puts("1 3 5 2 4 6");
			p(2,6)puts("1 3 5 2 4 6\n11 9 7 12 10 8");
			p(3,6)puts("1 3 5 2 4 6\n11 9 7 12 10 8\n13 15 17 14 16 18");
			p(7,1)puts("1\n3\n5\n7\n2\n4\n6");
			p(7,2)puts("1 14\n4 7\n5 10\n8 11\n9 6\n12 3\n13 2");
			p(7,3)puts("1 3 5\n7 9 11\n13 15 17\n19 21 2\n4 6 8\n10 12 14\n16 18 20");
			else
			{
				int **b=new int*[n];//
				int cnt=0;
				if(n<m)goto charm1;
				for(int i=0;i<n;i++)b[i]=new int[m];
				for(int i=n/2+1;i<=n;i++)fill(b[i-1],m,cnt*m),cnt+=2;
				cnt=1;
				for(int i=1;i<=n/2;i++)fill(b[i-1],m,cnt*m),cnt+=2;
				for(int i=0;i<n;i++,puts(""))
					for(int j=0;j<m;j++)printf("%d ",b[i][j]);
				delete[] b;
				return;
				charm1:;delete[] b;
				if(m>5)
				{
					b=new int*[m];
					for(int i=0;i<m;i++)b[i]=new int[n];
					int cnt=2;
					for(int i=m/2+1;i<=m;i++)filll(b[i-1],m,cnt,n),cnt+=2;
					cnt=1;
					for(int i=1;i<=m/2;i++)filll(b[i-1],m,cnt,n),cnt+=2;
					for(int j=0;j<n;j++,puts(""))
						for(int i=0;i<m;i++)printf("%d ",b[i][j]);
					delete[] b;
				}
			}
		}
	}
}
int main()
{
	//freopen("op.out","w",stdout);
	int n=read(),m=read();
	if(n>7)subtask1::solve(n,m);
	else if(m>7)subtask2::solve(n,m);
	else subtask3::solve(n,m);
	
	return 0;
}

```

---

## 作者：流绪 (赞：1)

dfs,从第一个位置向后搜,对于每个位置枚举他后面的所有位置,看看交换后能不能符合题意,可以的话往下搜,不行的话换回去,继续枚举

对于整个图 n,m 最大会达到 1e5 二维数组会超内存,但是 n*m<=1e5 所以我们可以用一维数组存,再计算他们的坐标。或者可以用 map 存? STL不太会,只能用数组了...

下面是 AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int dx[]={0,0,-1,1};
int dy[]={-1,1,0,0};
int p[100010];
int n,m;
bool check(int a,int b)//判断换完能不符合题意
{
	int x1=a/m;
	int y1=a%m;
	int x2=b/m;
	int y2=b%m;
	for(int i=0;i<4;i++)
		if(x1+dx[i] == x2&&y1+dy[i] == y2)
			return 1;
	return 0;
}
bool dfs(int pos)//搜索
{
	if(pos == n*m)
		return 1;
	int x=pos/m;
	int y=pos%m;
	for(int i=pos;i<n*m;i++)
	{
		swap(p[pos],p[i]);
		if((x && check(p[pos],p[(x-1)*m+y])) || (y&&check(p[pos],p[x*m+y-1])))
			continue;
		if(dfs(pos+1))
			return 1;
		swap(p[pos],p[i]);
	}
	return 0;
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for(int i=0;i<n*m;i++)
		p[i] = i;//给每个点赋初值
	if(dfs(0))
	{
		cout << "YES\n";
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
				cout << p[i*m+j]+1 << " ";
			cout << endl;
		}
	}
	else
		cout << "NO";	
} 
```


---

