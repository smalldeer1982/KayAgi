# Convex Shape

## 题目描述

### 题意

有一个 $n \times m$ 的方格阵。开始时，所有的方格都是白色的。小 $Z$ 已经把其中的一些方格（至少 $1$ 个）涂成了黑色。如果在方格中从任意一个黑色方格沿着黑色方格走到另一个黑色方格最多只需要拐弯一次的话，我们就称黑色方格组成的区域为凸多边形。如下图所示，左边是凸多边形而右边的不是。

现在你需要判断一个方阵中黑色格子组成的图形是不是凸多边形。

## 样例 #1

### 输入

```
3 4
WWBW
BWWW
WWWB
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
3 1
B
B
W
```

### 输出

```
YES
```

# 题解

## 作者：0okoukio0 (赞：2)

看着这题没有题解着实有那么点难受，为了给来做这道题目的萌（cai）新（ji）一点提醒，正义的我来写题解了！

首先，我们要看的是黑色的方块，所以为了判定的时候不至于再找一遍黑方块，输入的时候就单独把黑方块的xy坐标全部单独记录在一个坐标数组里

再往下看，对于任意的两个黑方块，它们的位置关系可以分成三种：

1.在同一行
2.在同一列
3.既不在同一行，也不在同一列

如果在同一行，这两个方块之间一定不能有白方块，否则就像题目里给出的第二幅图片一样要绕路，必须拐2次，同一列也一样。

如果是第三种情况，那么要走到那个位置至少要拐弯一次，那么只要判段走到那个位置的拐角是不是被白块给挡住了（不要问我为什么不判定路上有没有空位，程序能进行到那里就已经排除了路上没空位的事情）

讲了这么多，代码怎么实现呢？大概讲一下思路：输入每一行后，内部循环读出黑块的位置，注意单独用一个数来存储下标，然后从第一个黑块开始，测试这个黑块和它往后的所有黑块是否只需要拐弯一次，然后循环往复已知测试到倒数第二个黑块，如果不行直接在循环内部输出no后return，这样跳出循环后的一定是合法的，输出yes后return

该给出代码了：
```cpp
#include<bits/stdc++.h>
#define N 3000
#define LL long long
#define UNLL unsigned long long
using namespace std;
int n,m,x[N],y[N],cnt;
char s[N][N];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>(s[i]+1);//让每行的纵坐标从1开始 
		for(int j=1;j<=m;j++){
			if(s[i][j]=='B'){
				x[++cnt]=i,y[cnt]=j;
			}//记录所有黑方块的坐标 
		}
	}
	for(int i=1;i<cnt;i++){
		int a=x[i],b=y[i];//记录第i个黑方块的坐标 
		for(int j=i+1;j<=cnt;j++){
			int c=x[j],d=y[j];//记录第j个黑方块的坐标 
			if(a==c){
				for(int k=min(b,d);k<=max(b,d);k++){
					if(s[a][k]=='W'){
						cout<<"NO";
						return 0;
					}
				}//如果在同一行，必须之间没有白方块挡路，否则绕路需要至少2次拐弯 
			}
			else if(b==d){
				for(int k=min(a,c);k<=max(a,c);k++){
					if(s[k][b]=='W'){
						cout<<"NO";
						return 0;
					}
				}//如果在同一列，必须之间没有白方块挡路，否则绕路需要至少2次拐弯 
			}
			else{
				if(s[a][d]=='W'&&s[c][b]=='W'){
					cout<<"NO";
					return 0;
				}//在满足前两个情况(能循环到这里说明其他在同一行和同一列的方块都活过去了)的情况下，只需要判断拐点的位置是白还是黑 
			}
		}
	}
	cout<<"YES";//走出循环，说明所有方块走到其他方块都至多需要1次拐弯，符合要求 
	return 0;
}
```
看了题解却发现没有的人，现在有福可以享了/偷笑

---

## 作者：LRL65 (赞：1)

刚刚才做掉的题。

思路：

前缀和预处理，暴力枚举两个点，因为两个点拐一次有两种可能（除非同行同列），所以看两种可能的路上是否全是黑色的。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,sh[55][55],sl[55][55];
char c[55][55];
int main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) {
			cin>>c[i][j];
			sh[i][j]=sh[i][j-1];
			if(c[i][j]=='B')sh[i][j]++;
		}
	for(int j=1;j<=m;j++)
		for(int i=1;i<=n;i++) {
			sl[j][i]=sl[j][i-1];
			if(c[i][j]=='B')sl[j][i]++;
		}
    
	for(int i1=1;i1<=n;i1++) 
		for(int j1=1;j1<=m;j1++) 
			for(int i2=1;i2<=n;i2++)
				for(int j2=1;j2<=m;j2++)
                if(c[i1][j1]=='B'&&c[i2][j2]=='B') {
					if((sh[i1][j2]-sh[i1][j1-1]+sl[j2][i2]-sl[j2][i1-1]!=i2-i1+1+j2-j1+1)&&(sh[i2][j2]-sh[i2][j1-1]+sl[j1][i2]-sl[j1][i1-1]!=i2-i1+1+j2-j1+1)) {
						cout<<"NO"<<endl;
						return 0;
					}
                }
	cout<<"YES"<<endl;
}
```


---

## 作者：2023lpx (赞：0)

# Convex Shape 题解

## 前置知识

链式前向星。

## 思路

一看 $1 \le n,m \le 50$，很明显暴力啊。

先用链式前向星存黑色的位置，免得后面再去找浪费时间。

分三种情况讨论。

1. 在同一列。
  
2. 在同一行。
  
3. 不在同一行也不再同一列。
  

对于前面两种情况，暴力即可。

对于最后一种，由于前面的循环肯定已经将同一行和同一列的扫过了，所以我们只用 $O(1)$ 判断即可。

时间复杂度 $O(n^3)$。

## code

```cpp
#include<cstdio>
using namespace std;
int n,m;
bool c[51][51];
int min(int a,int b){
	return a<b?a:b;
}
int max(int a,int b){
	return a>b?a:b;
}
int abs(int a){
	return a<0?-a:a;
}
int cnt;
int x[51*51];
int y[51*51];
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char in=getchar();
			while(in!='B'&&in!='W'){
				in=getchar();
			}
			if(in=='B'){
				c[i][j]=1;
				cnt++;
				x[cnt]=i;
				y[cnt]=j;
			}
			
		}
	}
	for(int a=1;a<=cnt;a++){
		for(int b=a+1;b<=cnt;b++){
			if(x[a]==x[b]){//同一行
				for(int i=min(y[a],y[b]);i<=max(y[a],y[b]);i++){
					if(c[x[a]][i]==0){
						printf("NO");
						return 0;
					}
				}
				continue;
			}
			else if(y[a]==y[b]){//同一列
				for(int i=min(x[a],x[b]);i<=max(x[a],x[b]);i++){
					if(c[i][y[a]]==0){
						printf("NO");
						return 0;
					}
				}
				continue;
			}
			else if(c[x[a]][y[b]]==0&&c[x[b]][y[a]]==0){//其他
				printf("NO");
				return 0;
			}
		}
	}
	printf("YES");
	return 0;
}
```

---

## 作者：vandijk (赞：0)

题意：

有一个 n*m 的方格阵。开始时，所有的方格都是白色的。小 Z 已经把其中的一些方格（至少 1 个）涂成了黑色。如果在方格中从任意一个黑色方格沿着黑色方格走到另一个黑色方格最多只需要拐弯一次的话，我们就称黑色方格组成的区域为凸多边形。如下图所示，左边是凸多边形而右边的不是。

现在你需要判断一个方阵中黑色格子组成的图形是不是凸多边形。

一看就知道，可以枚举(x,y),(i,j),表示从(x,y)到(i,j),众所周知，(x,y)到(i,j)最多有两条路径，于是，就想到50的5次方的做法。

算一下时间复杂度，发现差不多是 _3*1e8_ 的时间，于是常数写大点就很容易TLE。

话不多说，先上代码->

(AC）

```
#include <bits/stdc++.h>
using namespace std;
int n,m;
char c[55][55];
int main()
{
	cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			cin>>c[i][j];
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(c[i][j]=='W')continue;
			for(int i2=0;i2<n;i2++)
			{
				for(int j2=0;j2<m;j2++)
				{
					if(c[i2][j2]=='W')continue;
					bool ok=0,flag=0;
					for(int k=min(i,i2);k<=max(i,i2);k++)//纵列走
					{
						if(c[k][j]=='W')ok=1;
						if(c[k][j2]=='W')flag=1;
					}
					for(int k=min(j,j2);k<=max(j,j2);k++)//横行走
					{
						if(c[i][k]=='W')flag=1;
						if(c[i2][k]=='W')ok=1;
					}
					if(ok&&flag)
					{
						cout<<"NO"<<endl;
						return 0; 
					}
				}
			}
		}
	}
	cout<<"YES"<<endl;
	return 0;
}
```

再想一想，有什么优化的办法呢？

有，前缀和。

先把前缀和处理出来后，再看中间是不是全是黑的就行了。

正解Code->

```
#include <bits/stdc++.h>
using namespace std;
int n,m;
char c[55][55];
int a[55][55];
int b[55][55];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>c[i][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		a[i][0]=0;
		for(int j=1;j<=m;j++)
		{
			a[i][j]=a[i][j-1]+(c[i][j]=='B');
		}
	}
	for(int i=1;i<=m;i++)
	{
		b[0][i]=0;
		for(int j=1;j<=n;j++)
		{
			b[j][i]=b[j-1][i]+(c[j][i]=='B');
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(c[i][j]=='W')continue;
			for(int i2=1;i2<=n;i2++)
			{
				for(int j2=1;j2<=m;j2++)
				{
					if(c[i2][j2]=='W')continue;
					if(a[i][j2]-a[i][j-1]!=j2-j+1&&a[i2][j2]-a[i2][j-1]!=j2-j+1)
					{
						cout<<"NO"<<endl;
						return 0;
					}
					if(b[i2][j]-b[i-1][j]!=i2-i+1&&b[i2][j2]-b[i-1][j2]!=i2-i+1)
					{
						cout<<"NO"<<endl;
						return 0;
					}
				}
			}
		}
	}
	cout<<"YES"<<endl;
	return 0;
}
```


---

