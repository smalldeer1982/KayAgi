# [ARC001C] パズルのお手伝い

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc001/tasks/arc001_3



## 样例 #1

### 输入

```
........
........
.......Q
........
..Q.....
........
.Q......
........```

### 输出

```
Q.......
....Q...
.......Q
.....Q..
..Q.....
......Q.
.Q......
...Q....```

## 样例 #2

### 输入

```
.....Q..
.Q......
........
........
........
Q.......
........
........```

### 输出

```
No Answer```

# 题解

## 作者：EnofTaiPeople (赞：2)

实不相瞒，本蒟蒻到现在连深度优先搜索都不会，于是，翻开了这道题。

AC 时间：10 分钟（这次有点长）。

首先，很容易知道，只有五行五列有放的可能，于是可以使用深度优先搜索算法，把每种情况都考虑一下，当然，如果判定不合法，就不要继续搜下去了，复杂度 $O(n^n)$ 但 $n=5$，所以可以接受。

难点在于如何判定不合法，于是我定义了一系列的 bool 数组：
```cpp
bool crs[10],don[10],rt[20],ans[10][10],lt[20],flag;
```
$ans[i][j]$ 表示 $(i,j)$ 这个位置是否放了皇后。
$crs[i]$ 表示第 $i$ 行是否放了皇后，$don[i]$ 表示第 $i$ 列是否放了皇后，$rt[x]$ 存的是右斜线，因为在同一个右斜线的横纵坐标之差相等，由于坐标差在 $[-7,7]$ 之内，而数组下标不能是负数，于是让它们整体加上 $7$；$lt[x]$ 存的是左斜线，因为在同一个左斜线的横纵坐标之和相等，和一定是正数，所以不需要特殊处理。

对于每一个已放皇后 $(i,j)$，我们进行一个标记：
```cpp
crs[i]=don[i]=lt[i+j]=rt[i-j+7]=ans[i][j]=true;
```
，搜索回溯时，在转换回来。搜到 $9$ 时，直接输出答案，并返回 true，如果返回了 true，即搜到了答案，这时函数直接全部返回 true 就可以了，立刻终止搜索。

AC代码就出来啦：
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
bool crs[10],don[10],rt[20],ans[10][10],lt[20],flag;
bool dfs(int a){
	register int i,j;
	if(a==9){
		for(i=1;i<=8;++i){
			for(j=1;j<=8;++j){
				if(ans[i][j])putchar('Q');
				else putchar('.');
			}putchar('\n');
		}return true;
	}
	if(crs[a])return dfs(a+1);
	for(i=1;i<=8;++i){
		if(don[i]||rt[a-i+7]||lt[a+i])continue;
		crs[a]=don[i]=ans[a][i]=rt[a-i+7]=lt[a+i]=true;
		if(dfs(a+1))return true;
		crs[a]=don[i]=ans[a][i]=rt[a-i+7]=lt[a+i]=false;
	}return false;
}
int main(){
	register int i,j;
	register char ch;
	for(i=1;i<=8;++i)
		for(j=1;j<=8;++j){
			for(ch=getchar();ch!='Q'&&ch!='.';ch=getchar());
			if(ch=='Q'){
				if(crs[i]||don[j]||rt[i-j+7]||ans[i][j]||lt[i+j])
					flag=true;else
				crs[i]=don[j]=rt[i-j+7]=ans[i][j]=lt[i+j]=true;
			}
		}
	if(flag){printf("No Answer\n");return 0;}
	if(!dfs(1))printf("No Answer\n");
	return 0;
}
```

---

## 作者：龙潜月十五 (赞：1)

## 一、前言

本题是一道搜索题，是经典老题 **八皇后** 的变式。

## 二、题意

在 $8 \times 8$ 的棋盘中，已给出 $3$ 个皇后的位置，要你求出放满 $8$ 个皇后后的情况。每个皇后不可以 **在同一行、同一列、同一对角线** 上。

## 三、思路

普通的搜索回溯 DFS 即可。在选择放一个皇后后，给它的行、列、对角线都打上标记。

至于对角线怎么表示。我们通过画图可以发现，在同一条 **从左下到右上** 的对角线上的点 **横纵坐标之和相等**，在同一条 **从右下到左上** 的对角线上的点 **横纵坐标之差相等**，因此可以标记。

## 四、注意点

横纵坐标之差可能小于零，所以要加上一个数防止数组越界。

无解的情况有两种：给出的 $3$ 个皇后本身冲突；DFS 后没有答案。都需要判断。

## 五、代码

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

const int N=14;
char mp[N][N];
bool b[N][N],h[N],l[N],djx1[N*2],djx2[N*2],flag;

void print()
{
	for(int i=0;i<=7;i++)
	{
		for(int j=0;j<=7;j++)
			if(b[i][j])
				printf("Q");
			else
				printf(".");
		printf("\n");
	}
}

void dfs(int now)
{
	if(now==5)
	{
		flag=true;
		print();
		exit(0); 
	}
	
	for(int i=0;i<=7;i++)
		if(!h[i])
			for(int j=0;j<=7;j++)
				if(!l[j]&&!djx1[i+j]&&!djx2[i-j+N])
				{
					//打上标记 
					b[i][j]=true;
					h[i]=true;
					l[j]=true;
					djx1[i+j]=true;
					djx2[i-j+N]=true;
					
					dfs(now+1);
					
					//回溯：取消标记 
					b[i][j]=false;
					h[i]=false;
					l[j]=false;
					djx1[i+j]=false;
					djx2[i-j+N]=false;
				}	
		
}
int main()
{
	for(int i=0;i<=7;i++)
		cin>>mp[i];

	for(int i=0;i<=7;i++)
		for(int j=0;j<=7;j++)
			if(mp[i][j]=='Q')
			{
				if(!h[i]&&!l[j]&&!djx1[i+j]&&!djx2[i-j+N])
				{
					b[i][j]=true;
					h[i]=true;
					l[j]=true;
					djx1[i+j]=true;
					djx2[i-j+N]=true;
				}
				else
					return printf("No Answer\n"),0;
			}	
	
	dfs(0);
	
	if(!flag)
		printf("No Answer\n");
		
	return 0;
 } 

```


---

## 作者：Blancа (赞：1)

### 题意：
很经典的八皇后问题，已知三个皇后的位置，求剩下五个皇后的位置，如果无解输出“$No Answer$”  
### 思路：
很显然dfs可以解决，暴力枚举每一行放的位置，通过已经放过的皇后的位置可以判断出很多不合法的位置  
暴力将选的点所在的列，行，两条对角线上的点加一，如果撤销就减一，防止已经被其他点打上标记的点被删去标记  
模拟一个样例可以发现可以选的点数很少，加上剪枝即可

### 代码实现：
```c++
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
inline int read () {
	int x = 0, f = 1; char ch = getchar();
	for (;!isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
	for (; isdigit(ch); ch = getchar()) x = x * 10 + ch - '0';
	return x * f;
}
const int maxn = 10;
int choose[maxn][maxn];
int ans[maxn][maxn];
int col[maxn];
void updata (int x, int y) {
	for (int k = 1; k <= 8; k++) choose[x][k]++, choose[k][y]++;
	for (int k = 1; k + x <= 8 && k + y <= 8; k++) choose[x + k][y + k]++;
	for (int k = 1; x - k >= 1 && y - k >= 1; k++) choose[x - k][y - k]++;
	for (int k = 1; x - k >= 1 && y + k <= 8; k++) choose[x - k][y + k]++;
	for (int k = 1; x + k <= 8 && y - k >= 1; k++) choose[x + k][y - k]++;
	choose[x][y]--;
}
void Delete (int x, int y) {
	for (int k = 1; k <= 8; k++) choose[x][k]--, choose[k][y]--;
	for (int k = 1; k + x <= 8 && k + y <= 8; k++) choose[x + k][y + k]--;
	for (int k = 1; x - k >= 1 && y - k >= 1; k++) choose[x - k][y - k]--;
	for (int k = 1; x - k >= 1 && y + k <= 8; k++) choose[x - k][y + k]--;
	for (int k = 1; x + k <= 8 && y - k >= 1; k++) choose[x + k][y - k]--;
	choose[x][y]++;
}
bool judge = false;
void dfs (int num) {
	if (num == 9) {
		judge = true;
		return;
	}
	if (col[num]) dfs (num + 1);
	if (judge == true) return;
	for (int i = 1; i <= 8; i++) {
		if (choose[num][i]) continue;
		ans[num][i] = 1;
		updata (num, i);
		dfs (num + 1);
		if (judge == true) return;
		ans[num][i] = 0;
		Delete (num, i);
	}
	if (judge == true) return;
}
int main () {
	char c;
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			scanf (" %c", &c);
			if (c == 'Q') {
				if (choose[i][j] != 0) return puts("No Answer"), 0;
				ans[i][j] = 1;
				col[i] = 1;
				updata (i, j);
			}
		}
	}
	dfs (1);
	if (judge == true) {
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++) {
				if (ans[i][j] == 1) printf ("Q");
				else printf (".");
			}
			puts("");
		}
	} else {
		puts("No Answer");
	}
	return 0;
}

```

---

## 作者：monstersqwq (赞：1)

类似八皇后的一道 dfs 题目。

#### 思路：

定义 $h,l,le,ri$ 四个 bool 类型的数组，$h_i,l_i,le_i,ri_i$ 分别记录第 i 行，第 i 列，第 i 左斜列，第 i 右斜列有没有被使用过。定义一个 a 数组记录答案，s 数组记录地图（为了防止换行符带来的影响，我使用了 string 类型，因为 string 下标从0开始，所以要稍微更改一下，具体可在代码中查看），定义一个 bool 变量 flag 记录是否有答案。

对于点 $s_{i,j}$，它属于 $h_i,l_j,le_{i+j-1},ri_{i-j+8}$。（在 $ri$ 那里 $+8$ 是让数组下标变为正数）

输入：如果在 $s_{i,j}$ 发现了 Q，如果 $h_i,l_j,le_{i+j-1},ri_{i-j+8}$ 之中有任何一个使用过了，就直接输出无解，结束程序。如果都没有用过，则把四个 bool 变量标记使用过，并 $a_i \gets j$。

dfs：一个变量 x，记录当前搜的是第 x 行，如果$x >8$ 直接输出整个 a 数组，并 $flag \gets true$，然后即可用 $\operatorname{exit}(0)$ 结束程序。

如果 $x \le 8$，如果枚举可能的点（记作 $s_{x,y}$,枚举 y），如果该点对应的 $h,l,le,ri$ 都没有使用过，就当成一种可能，并标记为使用，并 $a_x \gets y$ 然后搜索下一层，最后在把四个 bool 变量重新标记成未使用。（注意，如果 $h_x=true$ 直接搜索下一层，不需要枚举了，作者就在这里被坑了）

最后判断一下有无答案，无答案输出无解即可。

代码：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
using namespace std;
int a[25];
bool h[25],l[25],le[25],ri[25],flag;
string s[10];
void dfs(int x)
{
	if(x>8)
	{
		flag=true;
		for(int i=1;i<=8;i++)
		{
			for(int j=1;j<=8;j++)
			{
				if(a[i]==j)
				{
					cout<<"Q";
				}
				else
				{
					cout<<".";
				}
			}
			    cout<<endl;
		}
		exit(0);	
	}
    if(h[x]==true)
    {
        dfs(x+1);
        return;
    }
	for(int y=1;y<=8;y++)
	{
		if(!l[y]&&!le[x+y-1]&&!ri[x-y+8])
		{
		    a[x]=y;
		    l[y]=true;
		    le[x+y]=true;
		    ri[x-y+8]=true;
		    dfs(x+1);
		    l[y]=false;
		    le[x+y]=false;
		    ri[x-y+8]=false;
		}
	}
		
}
int main()
{
	for(int i=1;i<=8;i++)
		cin>>s[i];
	for(int i=1;i<=8;i++)
    {
		for(int j=0;j<=7;j++)
		{
			if(s[i][j]=='Q')
			{
				int tmp=j+1;
				if(!h[i]&&!l[tmp]&&!le[i+tmp-1]&&!ri[i-tmp+8])
				{
					a[i]=tmp;
					h[i]=true;
					l[tmp]=true;
					le[i+tmp-1]=true;
					ri[i-tmp+8]=true;
				}
				else
				{
					cout<<"No Answer";
					return 0;
				}
			}
		}
    }
	dfs(1);
	if(flag==false)
	{
		cout<<"No Answer";
	}
	return 0;
}
```


---

## 作者：RioBlu (赞：1)

可以打表，把8皇后的所有方案存进数组里，然后对于这个Q的位置进行判断

___
```
#include<bits/stdc++.h>
using namespace std;
int k[100][8]={1,5,8,6,3,7,2,4,1,6,8,3,7,4,2,5,1,7,4,6,8,2,5,3,1,7,5,8,2,4,6,3,2,4,6,8,3,1,7,5,2,5,7,1,3,8,6,4,2,5,7,4,1,8,6,3,2,6,1,7,4,8,3,5,2,6,8,3,1,4,7,5,2,7,3,6,8,5,1,4,2,7,5,8,1,4,6,3,2,8,6,1,3,5,7,4,3,1,7,5,8,2,4,6,3,5,2,8,1,7,4,6,3,5,2,8,6,4,7,1,3,5,7,1,4,2,8,6,3,5,8,4,1,7,2,6,3,6,2,5,8,1,7,4,3,6,2,7,1,4,8,5,3,6,2,7,5,1,8,4,3,6,4,1,8,5,7,2,3,6,4,2,8,5,7,1,3,6,8,1,4,7,5,2,3,6,8,1,5,7,2,4,3,6,8,2,4,1,7,5,3,7,2,8,5,1,4,6,3,7,2,8,6,4,1,5,3,8,4,7,1,6,2,5,4,1,5,8,2,7,3,6,4,1,5,8,6,3,7,2,4,2,5,8,6,1,3,7,4,2,7,3,6,8,1,5,4,2,7,3,6,8,5,1,4,2,7,5,1,8,6,3,4,2,8,5,7,1,3,6,4,2,8,6,1,3,5,7,4,6,1,5,2,8,3,7,4,6,8,2,7,1,3,5,4,6,8,3,1,7,5,2,4,7,1,8,5,2,6,3,4,7,3,8,2,5,1,6,4,7,5,2,6,1,3,8,4,7,5,3,1,6,8,2,4,8,1,3,6,2,7,5,4,8,1,5,7,2,6,3,4,8,5,3,1,7,2,6,5,1,4,6,8,2,7,3,5,1,8,4,2,7,3,6,5,1,8,6,3,7,2,4,5,2,4,6,8,3,1,7,5,2,4,7,3,8,6,1,5,2,6,1,7,4,8,3,5,2,8,1,4,7,3,6,5,3,1,6,8,2,4,7,5,3,1,7,2,8,6,4,5,3,8,4,7,1,6,2,5,7,1,3,8,6,4,2,5,7,1,4,2,8,6,3,5,7,2,4,8,1,3,6,5,7,2,6,3,1,4,8,5,7,2,6,3,1,8,4,5,7,4,1,3,8,6,2,5,8,4,1,3,6,2,7,5,8,4,1,7,2,6,3,6,1,5,2,8,3,7,4,6,2,7,1,3,5,8,4,6,2,7,1,4,8,5,3,6,3,1,7,5,8,2,4,6,3,1,8,4,2,7,5,6,3,1,8,5,2,4,7,6,3,5,7,1,4,2,8,6,3,5,8,1,4,2,7,6,3,7,2,4,8,1,5,6,3,7,2,8,5,1,4,6,3,7,4,1,8,2,5,6,4,1,5,8,2,7,3,6,4,2,8,5,7,1,3,6,4,7,1,3,5,2,8,6,4,7,1,8,2,5,3,6,8,2,4,1,7,5,3,7,1,3,8,6,4,2,5,7,2,4,1,8,5,3,6,7,2,6,3,1,4,8,5,7,3,1,6,8,5,2,4,7,3,8,2,5,1,6,4,7,4,2,5,8,1,3,6,7,4,2,8,6,1,3,5,7,5,3,1,6,8,2,4,8,2,4,1,7,5,3,6,8,2,5,3,1,7,4,6,8,3,1,6,2,5,7,4,8,4,1,3,6,2,7,5};
long long u[10];
string n;
bool ok;
int main()
{
	for(int s=0;s<8;s++)
	{
		cin>>n;
		u[s]=n.find("Q")+1;
		if(n.find("Q",u[s])!=-1)//一行两个Q，我本来以为高桥君很高智商，但判断一下就满分了
		{
			puts("No Answer"); 
			return 0;
		}
	}
	for(int s=0;s<92;s++)//92个方案
	{
		ok=1;
		for(int v=0;v<8;v++)
		{
			if(!u[v])continue;//如果原来没有Q
			if(u[v]!=k[s][v])//与方案不符合
			{
				ok=0;break;
			}
		}
		if(ok)
		{
			for(int v=0;v<8;v++)
			{
				cout<<string(k[s][v]-1,'.')<<"Q"<<string(8-k[s][v],'.')<<endl;//输出
			}
			return 0;
		}
	}
	puts("No Answer"); 
	return 0;
}

```

---

## 作者：_caiji_ (赞：0)

### 前言
[这道题](https://www.luogu.com.cn/problem/AT47)与[八皇后](https://www.luogu.com.cn/problem/P1219)很像，可以做完八皇后再来做这道题。如果你 $\color{white}\colorbox{red}{WA}$ 了，请检查你有没有换行，有没有混淆大小写。

### 题意简述
一个 $8\times 8$ 的棋盘，要摆 $8$ 个皇后，要求每位皇后所在的 $2$ 条直线和 $2$ 条斜线上不能摆另一个皇后。现在已经摆了 $3$ 个，如果有解，输出解，否则输出`No Answer`。

### 思路
很明显，这是一道`dfs`的题目，我们要一行行的`dfs`。

我们开 $4$ 个`bool`数组 $fh,fl,fzx,fyx$ （行、列、左斜、右斜），对于点 $(x,y)$ 来说，它占领了第 $fh_x$ 行，第 $fl_y$ 列，第 $fzx_{x+y-1}$ 条左斜线，第 $fyx_{x-y+8}$ 条右斜线。这个稍微画个图推个规律就能知道。如果`fh[x]||fl[y]||fzx[x+y-1]||fyx[x-y+8]`为真，说明这个格子摆不了皇后了，继续枚举下一个点。

注意，如果这一行已经摆了皇后了，直接搜下一行，这一行就不用管了。

无解有 $2$ 种情况：
1. 输入的棋盘上有两个同一条直线或斜线上的皇后。
2. `dfs`搜不到解。

对于情况一，我们只需在输入时判断就可以了；对于情况二，可以在`dfs`结束但无输出时输出。

更多的细节请看代码。

### 完整代码
```cpp
#include <cstdio>
#include <cstdlib>
using namespace std;
#define S 20//开到2*8-1+1=16就够了，为了保险开大点
int n=8;//用n代替8，如果扩大棋盘大小，改变n一样能运行
bool a[S][S],fh[S],fl[S],fzx[S],fyx[S];//a数组记录棋盘情况
void input(){//输入
	char ipt[S];
	bool flag=0;
	for(int i=1;i<=n;i++){
		scanf("%s",ipt+1);//ipt+1能让字符串下标从1开始，老技巧了
		for(int j=1;j<=n;j++){
			if(ipt[j]=='Q'){
				if(a[i][j]||fh[i]||fl[j]||fzx[i+j-1]||fyx[i-j+n])//可以不判断a[i][j]，但为了代码的整齐，还是加一下
					flag=1;//为防止没读完数据RE的情况，我们用flag标记
				a[i][j]=fh[i]=fl[j]=fzx[i+j-1]=fyx[i-j+n]=1;//标记这个皇后占领的地方
			}//不用判断是'.'的情况，它又不会改变什么东西
		}
	}
	if(flag) puts("No Answer"),exit(0);//输入就错了，无解
}
void output(){//输出
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
			if(a[i][j]) putchar('Q');//putchar比printf快
			else putchar('.');
		puts("");//puts自带换行
	}
	exit(0);//数据保证唯一解或无解，输出完一个解就能走人了
}
void dfs(int x){//dfs本体
	if(x==n+1) output();//搜到第9行，说明有解，输出
	else if(fh[x]) dfs(x+1);//这一行有皇后，直接下一行
	else{
	    for(int y=1;y<=n;y++){//枚举这一行的格子
		    if(a[x][y]||fh[x]||fl[y]||fzx[x+y-1]||fyx[x-y+n]) continue;//这个点被占领就跳过
		    a[x][y]=fh[x]=fl[y]=fzx[x+y-1]=fyx[x-y+n]=1;
		    dfs(x+1);//下一行
		    a[x][y]=fh[x]=fl[y]=fzx[x+y-1]=fyx[x-y+n]=0;//回溯
		}
    }
}
int	main(){//极简主函数
	input();
	dfs(1);
	puts("No Answer");//如果没调用到output就说明无解
	return 0;
}
```

---

## 作者：陈晋衍 (赞：0)


其实阿，我的思路其实比较类似八皇后问题。

这道题就是八皇后问题的改编版。

（基本上没啥变化）

[八皇后](www.luogu.org/problemnew/show/P1219)

废话不多说，直接上代码：


```cpp
#include<iostream>
using namespace std;
string s[9];
int a[9][9];
int b[10],c[20],d[20];
int n=8;
bool flag=0;
int dfs(int k)//大深搜
{
	if(flag)return 0;
	if(k==9)
	{
		if(flag)return 0;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(a[i][j]==1){
					cout<<"Q";
				}
				else cout<<".";
			}
			cout<<endl;
		}
		//cout<<"!!!!!!!!!!!";
		flag=1;return 0;
	}
	if(a[k][0]==0)
	{	
		for(int i=1;i<=n;i++)
		{
			if(b[i]==0&&c[i+k]==0&&d[k-i+10]==0)
			{
				if(flag)return 0;
				b[i]++;c[i+k]++;d[k-i+10]++;a[k][i]=1;//每个都要标记一下
				dfs(k+1);if(flag)return 0;
				b[i]--;c[i+k]--;d[k-i+10]--;a[k][i]=0;//记得要回去
				if(flag)return 0;
			}
		}
		
	}
	else dfs(k+1);
	if(flag)return 0;
}
int main()
{
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
	}
    //预处理
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(s[i][j-1]=='Q'){
				a[i][j]=1;
				a[i][0]=1;
				b[j]++;
				c[i+j]++;
				d[i-j+10]++;
				if(b[j]==2||c[i+j]==2||d[i-j+10]==2){
					cout<<"No Answer";return 0;
				}
			}
		}
	}
	dfs(1);
    //注意这个特判，我险些被坑
	if(flag==0)cout<<"No Answer";
	
	return 0;
}
```

---

