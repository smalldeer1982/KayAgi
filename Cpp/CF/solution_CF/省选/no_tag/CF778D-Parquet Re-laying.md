# Parquet Re-laying

## 题目描述

Peter决定在大小为n×m的房间里放一个拼花，拼花是由大小为1×2的瓷砖组成。当工人们铺设拼花地板时，很明显，瓷砖的图案看起来不像Peter喜欢的，工人们将不得不重新铺设它。

工人们决定把整块拼花地板搬开，然后重新铺设，这是一项非常困难的任务，所以他们决定每小时做一次这样的操作:把两块拼花地板拆下来，形成一个2×2的正方形，把它们旋转90度，再放回原来的位置。

帮助Peter为工人们制定一个计划，或者告诉他们这是不可能的。计划最多包含100000条命令。

## 样例 #1

### 输入

```
2 3
ULR
DLR
LRU
LRD
```

### 输出

```
2
1 2
1 1
```

## 样例 #2

### 输入

```
4 3
ULR
DLR
LRU
LRD
ULR
DUU
UDD
DLR```

### 输出

```
3
3 1
3 2
2 2```

# 题解

## 作者：OceanLiu (赞：3)

又是一道神仙构造题……构造题为什么都那么神啊……

现在假设矩形的宽为偶数（如果不是偶数将矩形翻转即可）。然后我们考虑一个**中间状态**：因为所有操作都是可逆的，所以我们只需要考虑一个中间状态，将起始状态和终止状态都旋转到那个状态即可。我们不妨考虑中间状态为所有矩形都是横着放的（与矩形的宽平行）。

现在的问题是怎么构造出这样的状态。我们可以从上到下，从左到右扫一遍，把矩形放在正确的位置。如果现在遇到一个矩形是竖着放置的，那么会有三种情况：

1.旁边的矩形与它平行：

![1](https://cdn.luogu.com.cn/upload/image_hosting/h4l4x20z.png)

这种我们直接旋转就好。

2.旁边有两个矩形与它垂直：

![2](https://cdn.luogu.com.cn/upload/image_hosting/dfjtnkh2.png)

这时我们可以把右面这两个矩形旋转，然后再旋转这个竖着的矩形。

3.如果是这样的情况：

![3](https://cdn.luogu.com.cn/upload/image_hosting/rm2weyab.png)

我们现在就是要将这个横着的矩形竖过来，然后再一起旋转。这显然是一个子问题，可以递归解决。

总操作次数是$n^3$级别，可以通过此题。

代码：
```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#define pii pair<int,int>
using namespace std;
int N,M;
char s[55][55],t[55][55];
vector<pii> step;
char getc(){
	char c=getchar();
	while(c==' '||c =='\n')
		c=getchar();
	return c;
}
inline void rotate(int x,int y)
{
	step.push_back(pii(x,y));
	if (s[x][y]=='L')
	{
		s[x][y]=s[x][y+1]='U';
		s[x+1][y]=s[x+1][y+1]='D';
	}
	else
	{
		s[x][y]=s[x+1][y]='L';
		s[x][y+1]=s[x+1][y+1]='R';
	}
}
inline void dfs(int x,int y)
{
	if (s[x][y]=='L') return;
	if (s[x][y+1]=='L'){
		dfs(x+1,y+1);
		rotate(x,y+1);rotate(x,y);
	}else rotate(x,y);
}
vector<pii> change()
{
	int n=N,m=M;
	if (M&1)
	{
		for (int i=1;i<=N;i++)
			for (int j=1;j<=M;j++)
			{
				if (s[i][j]=='U') t[j][i]='L';
				if (s[i][j]=='D') t[j][i]='R';
				if (s[i][j]=='L') t[j][i]='U';
				if (s[i][j]=='R') t[j][i]='D';
			}
		memcpy(s,t,sizeof(s));
		swap(n,m);
	}
	step.clear();
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (s[i][j]=='U') dfs(i,j);
	if (M&1) 
		for (int i=0;i<step.size();i++)
			swap(step[i].first,step[i].second);
	return step;		
}
int main()
{
	scanf("%d%d",&N,&M);
	for (int i=1;i<=N;i++)
		for (int j=1;j<=M;j++)
			s[i][j]=getc();
	vector<pii> pre=change();
	for (int i=1;i<=N;i++)
		for (int j=1;j<=M;j++)
			s[i][j]=getc();
	vector<pii> nxt =change();
	printf("%d\n",pre.size()+nxt.size());
	for(auto t:pre) printf("%d %d\n",t.first,t.second);
	reverse(nxt.begin(),nxt.end());
	for(auto t:nxt) printf("%d %d\n",t.first,t.second);
	return 0;
}
```

---

## 作者：良心WA题人 (赞：2)

首先考虑一个弱化版的问题：将所有块全都变成横着摆放。

注意到将初始状态和结束状态都变成这个状态，然后正着跑初始状态的操作，倒着跑结束状态的操作，就可以完成操作。

如果无法全部横着摆放，此时 $m\bmod 2=1$，因为保证初始状态是存在的，所以 $n\bmod 2=0$，变成全部竖着摆放即可。

下面考虑如何操作。对于下面这种情形：

```
UU
DD
```

显然可以直接变为

```
LR
LR
```

然后我们发现别的情况貌似无法消掉了。注意到，我们可以将 

```
ULR
DLR
```

变为

```
LRU
LRD
```

此时竖着的块一定会向右挪动。那么一定可以在有限次操作内进入无法操作的状态。（这个数量级最坏是 $n^3$ 的，因为每一块最多挪动 $n$ 次，且最多有 $n^2$ 块。）

注意到无法操作的状态要么是已经达到了目标，要么是任何位置都不满足上述两种条件。此时只有一种情况：

```
....ULRLRLRLRLR....
....DULRLRLRLRL....
.....DULRLRLRLR....
......DULRLRLRL....
...................
```

我们发现最右侧一定有一半的行会凸出来一个，所以无法做到在有限的棋盘内摆放出如上的图形。所以通过反证法可以得证此时一定是达到了目标。

那么每次平方暴力枚举找到可以操作的位置操作即可。时间复杂度 $O(n^5)$。

不过如果不每次枚举把每个位置枚举完可以分析到 $O(n^4)$，原因是两行的竖着的两块距离大于 $2$ 的时候都会进行操作，则上面一行距离下一行的距离要么等于初始距离，要么为 $2$，显然是 $O(n)$ 级别次扫描即可完成操作。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=54;
char s[NN][NN],t[NN][NN];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%s",s[i]+1);
	for(int i=1;i<=n;i++)
		scanf("%s",t[i]+1);
	if(!(n%2))
	{
		vector<pair<int,int> >ans1,ans2;
		while(1)
		{
			bool flag=false;
			for(int i=1;i<n;i++)
				for(int j=1;j<m;j++)
					if(s[i][j]=='L')
					{
						if(s[i+1][j]=='L')
						{
							ans1.push_back({i,j});
							s[i][j]=s[i][j+1]='U';
							s[i+1][j]=s[i+1][j+1]='D';
						}
						else if(s[i+1][j]=='U'&&s[i+1][j+1]=='U')
						{
							ans1.push_back({i+1,j});
							ans1.push_back({i,j});
							s[i][j]=s[i][j+1]='U';
							s[i+1][j]=s[i+1][j+1]='D';
							s[i+2][j]='L',s[i+2][j+1]='R';
						}
						flag=true;
					}
			if(!flag)
				break;
		}
		while(1)
		{
			bool flag=false;
			for(int i=1;i<n;i++)
				for(int j=1;j<m;j++)
					if(t[i][j]=='L')
					{
						if(t[i+1][j]=='L')
						{
							ans2.push_back({i,j});
							t[i][j]=t[i][j+1]='U';
							t[i+1][j]=t[i+1][j+1]='D';
						}
						else if(t[i+1][j]=='U'&&t[i+1][j+1]=='U')
						{
							ans2.push_back({i+1,j});
							ans2.push_back({i,j});
							t[i][j]=t[i][j+1]='U';
							t[i+1][j]=t[i+1][j+1]='D';
							t[i+2][j]='L',t[i+2][j+1]='R';
						}
						flag=true;
					}
			if(!flag)
				break;
		}
		printf("%d\n",ans1.size()+ans2.size());
		for(int i=0;i<ans1.size();i++)
			printf("%d %d\n",ans1[i].first,ans1[i].second);
		for(int i=ans2.size()-1;~i;i--)
			printf("%d %d\n",ans2[i].first,ans2[i].second);
	}
	else
	{
		vector<pair<int,int> >ans1,ans2;
		while(1)
		{
			bool flag=false;
			for(int i=1;i<n;i++)
				for(int j=1;j<m;j++)
					if(s[i][j]=='U')
					{
						if(s[i][j+1]=='U')
						{
							ans1.push_back({i,j});
							s[i][j]=s[i+1][j]='L';
							s[i][j+1]=s[i+1][j+1]='R';
						}
						else if(s[i][j+1]=='L'&&s[i+1][j+1]=='L')
						{
							ans1.push_back({i,j+1});
							ans1.push_back({i,j});
							s[i][j]=s[i+1][j]='L';
							s[i][j+1]=s[i+1][j+1]='R';
							s[i][j+2]='U',s[i+1][j+2]='D';
						}
						flag=true;
					}
			if(!flag)
				break;
		}
		while(1)
		{
			bool flag=false;
			for(int i=1;i<n;i++)
				for(int j=1;j<m;j++)
					if(t[i][j]=='U')
					{
						if(t[i][j+1]=='U')
						{
							ans2.push_back({i,j});
							t[i][j]=t[i+1][j]='L';
							t[i][j+1]=t[i+1][j+1]='R';
						}
						else if(t[i][j+1]=='L'&&t[i+1][j+1]=='L')
						{
							ans2.push_back({i,j+1});
							ans2.push_back({i,j});
							t[i][j]=t[i+1][j]='L';
							t[i][j+1]=t[i+1][j+1]='R';
							t[i][j+2]='U',t[i+1][j+2]='D';
						}
						flag=true;
					}
			if(!flag)
				break;
		}
		printf("%d\n",ans1.size()+ans2.size());
		for(int i=0;i<ans1.size();i++)
			printf("%d %d\n",ans1[i].first,ans1[i].second);
		for(int i=ans2.size()-1;~i;i--)
			printf("%d %d\n",ans2[i].first,ans2[i].second);
	}
	return 0;
}
```

---

