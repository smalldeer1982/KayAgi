# Rectangle Filling

## 题目描述

There is an $ n \times m $ grid of white and black squares. In one operation, you can select any two squares of the same color, and color all squares in the subrectangle between them that color.

Formally, if you select positions $ (x_1, y_1) $ and $ (x_2, y_2) $ , both of which are currently the same color $ c $ , set the color of all $ (x, y) $ where $ \min(x_1, x_2) \le x \le \max(x_1, x_2) $ and $ \min(y_1, y_2) \le y \le \max(y_1, y_2) $ to $ c $ .

This diagram shows a sequence of two possible operations on a grid:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1966B/d8e91236088d989799638772d594a0a137d702f1.png)Is it possible for all squares in the grid to be the same color, after performing any number of operations (possibly zero)?

## 说明/提示

In the first example, it is impossible to ever change the color of any square with an operation, so we output NO.

The second example is the case pictured above. As shown in that diagram, it is possible for all squares to be white after two operations, so we output YES.

In the third and fourth examples, all squares are already the same color, so we output YES.

In the fifth example we can do everything in two operations. First, select positions $ (2, 1) $ and $ (1, 4) $ and color all squares with $ 1 \le x \le 2 $ and $ 1 \le y \le 4 $ to white. Then, select positions $ (2, 1) $ and $ (3, 4) $ and color all squares with $ 2 \le x \le 3 $ and $ 1 \le y \le 4 $ to white. After these two operations all squares are white.

## 样例 #1

### 输入

```
8
2 1
W
B
6 6
WWWWBW
WBWWWW
BBBWWW
BWWWBB
WWBWBB
BBBWBW
1 1
W
2 2
BB
BB
3 4
BWBW
WBWB
BWBW
4 2
BB
BB
WW
WW
4 4
WWBW
BBWB
WWBB
BBBB
1 5
WBBWB```

### 输出

```
NO
YES
YES
YES
YES
NO
YES
NO```

# 题解

## 作者：huhaoming2011 (赞：3)

## 题目大意
每次选择的位置 $(x_1,y_1)$ 和 $(x_2,y_2)$，它们目前都是相同的颜色 $c$，则将 $\min(x_1,x_2) \le x \le \max(x_1,x_2)$ 和 $\min(y_1,y_2) \le y \le \max(y_1,y_2)$ 中所有 $(x,y)$ 的颜色设置为 $c$。做以上操作知道（分辨出是）无解或所有颜色统一。
## 分析
根据样例可以发现：只要有（至少一组）对顶顶点的颜色可以相同，则有解，否则无解。那么只需要判断四个点的颜色中是否有对顶顶点的颜色相同，有则直接输出，否则继续判断是否有点的颜色可变（即判断四个顶点所在列与行是否各有至少一点颜色不与该顶点相同，因为这样就能覆盖掉（改变）该顶点颜色），有则有解，否则无解。时间复杂度 $O(T \times n \times m)$。
## 代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000;
int n,m,g[N][N],bz[N];
signed main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		bz[1]=bz[2]=bz[3]=bz[4]=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
		{
			int j=0;
			char ch=getchar();
			while(ch!='W'&&ch!='B') ch=getchar();
			while(ch=='W'||ch=='B')
			{
				j++;
				if(ch=='B') g[i][j]=1;
				else g[i][j]=0;
				ch=getchar();
			}
		}
		if(g[n][1]==g[1][m]||g[1][1]==g[n][m])
		{
			printf("YES\n");
		}
		else
		{
			int ff=0;
			for(int i=1;i<=n;i++)
			{
				if(g[i][1]!=g[1][1]&&bz[1]==0)
				{
					bz[1]++;
				}
				if(g[i][m]!=g[1][m]&&bz[2]==0)
				{
					bz[2]++;
				}
				if(g[i][1]!=g[n][1]&&bz[3]==0)
				{
					bz[3]++;
				}
				if(g[i][m]!=g[n][m]&&bz[4]==0)
				{
					bz[4]++;
				}
			}
			for(int i=1;i<=m;i++)
			{
				if(g[1][i]!=g[1][1]&&bz[1]==1)
				{
					
					ff=1;
					printf("YES\n");
					break;
				}
				if(g[1][i]!=g[1][m]&&bz[2]==1)
				{
					ff=1;
					printf("YES\n");
					break;
				}
				if(g[n][i]!=g[n][1]&&bz[3]==1)
				{
					ff=1;
					printf("YES\n");
					break;
				}
				if(g[n][i]!=g[n][m]&&bz[4]==1)
				{
					ff=1;
					printf("YES\n");
					break;
				}
			}
			if(ff==0) printf("NO\n");
		}
	}
	return 0;
}
```
到此结束，谢谢！

---

## 作者：yyz1005 (赞：2)

题意：给定一个 $n \times m$ 的黑白色方阵，每次可以选两个同色格子以他们为对顶点构成的长方形全部染成他们的颜色，求能否染成完全同色。

注意到四个边上每个边都有一个同颜色格子就能把整个方阵全染成这个颜色，否则，没有该夜色的那一边显然是无法被染成这种颜色的，就做出来了。

[Code](https://codeforces.com/contest/1966/submission/258432261)

---

## 作者：BDFZ_hym_AK_hym_ing (赞：1)

#### [题目传送门](https://www.luogu.com.cn/problem/CF1966B)
### 题目大意
给你 $t$ 组数据，每组数据输入两个字母 $n$ 和 $m$，表示你有一个 $n \times m$ 的白黑格网。  
可以通过变化使格网只剩一种颜色，求是否可以达成，可以的输出 `YES`，反之输出 `NO`。
### 题目分析
首先，题目规定的变化方式是选择两个点，如果两个点为同一种颜色，则这两个点所包围的所有点都变成这两个点的颜色。  

所以如果要让所有都变成一种颜色的话必须让至少有一个对角是同色。所以可以首先特判有没有对角，有的话直接输出 `YES`。  

接下来，我们判断能不能让一个角变成对角的颜色，如果要让角上的颜色变化的话，只能选择相邻的边上的两个点，所以可以每次暴力判断。
### 代码
这是正确的[code](https://www.luogu.com.cn/paste/um4gpkdw)。

---

## 作者：Lame_Joke (赞：1)

- ### 题目大意

  对于给定的一个 $N$ 乘 $M$ 的黑白矩阵，可以进行此操作：选定一个子矩阵，若其一对对角颜色相同，则能将这个子矩阵染成这对对角的颜色。判断给出的矩阵是否能被染成纯色。

- ### 大体思路

  不难想到，在这样的题目要求下，只要矩阵的上下左右每条边上都有一个白色或黑色就可以将矩阵染成纯色了。所以，枚举四条边，标记即可。

- ### 具体实现

  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int t,n,m;
  char ch;
  int a[505][505];
  int main()
  {
  	scanf("%d",&t);
  	while(t--)
  	{
  		int cnt=0,cnt1[4]={0,0,0,0},cnt2[4]={0,0,0,0};
  		scanf("%d%d",&n,&m);
  		for(int i=1;i<=n;i++)
  		{
  			while(ch!='W'&&ch!='B') ch=getchar();
  			cnt=0;
  			while(ch=='W'||ch=='B')
  			{
  				a[i][++cnt]=(ch=='W'?1:0);
  				ch=getchar();
  			}
  		}
  		for(int i=1;i<=n;i++)
  		{
  			if(a[i][1]==1) cnt1[0]=1;
  			if(a[i][m]==1) cnt1[1]=1;
  			if(a[i][1]==0) cnt2[0]=1;
  			if(a[i][m]==0) cnt2[1]=1;
  		}
  		for(int i=1;i<=m;i++)
  		{
  			if(a[1][i]==1) cnt1[2]=1;
  			if(a[n][i]==1) cnt1[3]=1;
  			if(a[1][i]==0) cnt2[2]=1;
  			if(a[n][i]==0) cnt2[3]=1;
  		}
  		if((cnt2[0]==1&&cnt2[1]==1&&cnt2[2]==1&&cnt2[3]==1)||(cnt1[0]==1&&cnt1[1]==1&&cnt1[2]==1&&cnt1[3]==1)) printf("YES\n");
  		else printf("NO\n");
  	}
  }
  ```

  [AC 链接](https://codeforces.com/contest/1966/submission/261520146)

---

## 作者：junee (赞：1)

# CF1966B题解

## 题目分析

本题问我们是否可以进行若干次操作使整个矩形颜色相同。当任意两个小方格颜色相同，我们可以使以两个方格为顶点的矩形内部变为同一个颜色。

我们发现当对角线是同一个颜色时，我们直接选择这两个小方格即可。由于本题只有两个颜色，所以我们发现四个顶点必定有两个以上为同一个颜色，当有三个顶点颜色相同时，一定是可以的，否则是对角线也是可以的。如果没有对角线，那么我们可以证明，同一颜色的顶点连线一定是矩形的一条边，此时我们只需要在它的对边上再找一个点就可以完全覆盖。

## Code

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=510;
char a[N][N];
int T,n,m;
int main(){
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)cin>>a[i][j];
        }
        if(n==1){
            if(a[1][1]!=a[1][m])cout<<"NO"<<'\n';
            else cout<<"YES"<<'\n';
            continue;
        }
        if(m==1){
            if(a[1][1]!=a[n][1])cout<<"NO"<<'\n';
            else cout<<"YES"<<'\n';
            continue;
        }
        if(a[1][1]==a[n][m]||a[n][1]==a[1][m]){
            cout<<"YES"<<'\n';
            continue;
        }
        if(a[1][1]==a[n][1]){
            int f=1;
            for(int i=1;i<=n;i++){
                if(a[i][m]==a[1][1]){
                    cout<<"YES"<<'\n';
                    f=0;
                    break;
                }
            }
            if(!f)continue;
            for(int i=1;i<=n;i++){
                if(a[i][1]==a[n][m]){
                    cout<<"YES"<<'\n';
                    f=0;
                    break;
                }
            }
            if(!f)continue;
        }
        if(a[1][1]==a[1][m]){
            int f=1;
            for(int i=1;i<=m;i++){
                if(a[1][1]==a[n][i]){
                    cout<<"YES"<<'\n';
                    f=0;
                    break;
                }
            }
            if(!f)continue;
            for(int i=1;i<=m;i++){
                if(a[n][m]==a[1][i]){
                    cout<<"YES"<<'\n';
                    f=0;
                    break;
                }
            }
            if(!f)continue;
        }
        cout<<"NO"<<'\n';
    }
    return 0;
}
```

---

## 作者：QoQ_ (赞：0)

# [Problem](https://www.luogu.com.cn/problem/CF1966B)

## 思路：

通过观察样例可以发现，如果网格中的四条边都存在白色或黑色，那么网格中的所有方格就可以变成相同的颜色，则输出 `Yes`，若没有则输出 `No`，所以我们只要用两个数组来判断四条边是否存在黑色或白色，最后判断两个数组中是否有一个数组的所有空间都被我们打上了标记即可。

## code 参考：

```
#include<bits/stdc++.h>
using namespace std;
char a[1001][1001];
int n,m,t;
bool temp[4]={false};
bool cmpb[4]={false};
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                cin>>a[i][j];
            }
        }
        for(int i=0;i<=3;i++){
            temp[i]=cmpb[i]=false;
        }
        for(int i=1;i<=n;i++){
            if(a[i][1]=='W'){
                temp[0]=true;
            }
            if(a[i][m]=='W'){
                temp[1]=true;
            }
            if(a[i][1]=='B'){
                cmpb[0]=true;
            }
            if(a[i][m]=='B'){
                cmpb[1]=true;
            }
        }
        for(int i=1;i<=m;i++){
			if(a[1][i]=='W'){
				temp[2]=true;
			}
			if(a[n][i]=='W'){
				temp[3]=true;
			}
			if(a[1][i]=='B'){
				cmpb[2]=true;
			}
			if(a[n][i]=='B'){
				cmpb[3]=true;
			}
        }
        if(temp[0]==true&&temp[1]==true&&temp[2]==true&&temp[3]==true){
            printf("Yes\n");
        }else if(cmpb[0]==true&&cmpb[1]==true&&cmpb[2]==true&&cmpb[3]==true){
            printf("Yes\n");
        }else{
            printf("No\n");
        }
    }
    return 0;
}
```

写完代码要习惯看一下数据范围哦：

$1 \le t \le10^4$，$1 \le n,m \le500$。

`int` 足够。

完结撒花~

---

## 作者：lgydkkyd (赞：0)

由于本题思维难度不是很高，于是直接放思路了：因为按照题意可以选矩阵中的任意两个相同颜色的方格，然后要将它们之间的子矩阵内的所有格染成那一种颜色，可得如下的结论了，若矩阵的上下左右每条边上都有一个白色的格或是黑色的格，就可以将矩阵染成白色的或黑色的了。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,w[114],b[114];
char a[1001][1001];
int main(){
	cin>>t;
	while(t--){
		memset(w,0,sizeof w);
		
		memset(b,0,sizeof b);
		cin>>n>>m;
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>a[i][j];
		for(int i=1;i<=n;i++){
			
			if(a[i][1]=='W'){
				w[0]=1;
			}
			if(a[i][m]=='W'){
				
				w[1]=1;
			}
			
			if(a[i][1]=='B'){
				b[0]=1;
			}
			
			if(a[i][m]=='B'){
				b[1]=1;
			}
			
		}
		for(int i=1;i<=m;i++){
			
			if(a[1][i]=='W'){
				w[2]=1;
			}
			
			if(a[n][i]=='W'){
				w[3]=1;
			}
			
			if(a[1][i]=='B'){
				b[2]=1;
			}
			
			if(a[n][i]=='B'){
				b[3]=1;
			}
			
		}
		if(w[0]==1&&w[1]==1&&w[2]==1&&w[3]==1){
			cout<<"Yes\n";
		} 
		else if(b[0]==1&&b[1]==1&&b[2]==1&&b[3]==1){
			cout<<"Yes\n";
		}
		else{
			cout<<"No\n";
		}
	}
	return 0;
}
```

---

## 作者：Rubedo_N (赞：0)

# 思路
由于可以选择任意两个同色的方格，并将它们之间的子矩形内所有方格染成那种颜色，可得：若矩阵的上下左右每条边上都有一个白色或黑色，就可以将矩阵染成白色或黑色。

枚举四条边，如果四边上都有同一种颜色，就能染成纯色。
# AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
int visw[4],visb[4];
char a[1010][1010];
signed main(){
	cin>>t;
	while(t--){
		int visw[4]={0,0,0,0},visb[4]={0,0,0,0};
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>a[i][j];
			}
		}
		for(int i=1;i<=n;i++){
			if(a[i][1]=='W')visw[0]=1;
			if(a[i][m]=='W')visw[1]=1;
			if(a[i][1]=='B')visb[0]=1;
			if(a[i][m]=='B')visb[1]=1;
		}
		for(int i=1;i<=m;i++){
			if(a[1][i]=='W')visw[2]=1;
			if(a[n][i]=='W')visw[3]=1;
			if(a[1][i]=='B')visb[2]=1;
			if(a[n][i]=='B')visb[3]=1;
		}
		if(visw[0]==1&&visw[1]==1&&visw[2]==1&&visw[3]==1)cout<<"Yes"<<endl; 
		else if(visb[0]==1&&visb[1]==1&&visb[2]==1&&visb[3]==1)cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
	return 0;
}
```

---

## 作者：liuhongyang123 (赞：0)

# 题目大意

给你一个 $n \times m$ 的矩阵，里面有黑白两种颜色，你可以选择两个颜色一样的点，把以他们为对顶点构成的长方形中的点染成跟这两个点颜色一样颜色。

求：可不可以让矩阵只有一种颜色。

# 方法

只有这个矩阵四条边上都有至少一个相同的颜色就可以，否则，不行。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e3+10;
int n,t,h[MAXN],m,ans,k,bh[MAXN],bl[MAXN],wl[MAXN],wh[MAXN];
char a[MAXN][MAXN];
signed main(){
	cin>>t;
	while(t--){
		int a1=0,a2=0,a3=0,a4=0,b1=0,b2=0,b3=0,b4=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>a[i][j];
				if(i==1){
					if(a[i][j]=='B') a1=1;
					else b1=1;
				}
				if(j==1){
					if(a[i][j]=='B') a2=1;
					else b2=1;
				}
				if(i==n){
					if(a[i][j]=='B') a3=1;
					else b3=1;
				}
				if(j==m){
					if(a[i][j]=='B') a4=1;
					else b4=1;
				}
			}
		}
		if((a1&&a2&&a3&&a4)||(b1&&b2&&b3&&b4)) cout<<"YEs";
		else cout<<"No";
		cout<<endl;
	}
	return 0;
}
```

# 完结散花

---

## 作者：IOI_official (赞：0)

## 题意：
### 题目描述
给定一个 $n\times m$ 的矩形，矩阵由黑白两种颜色组成，你可以进行一些操作，每次操作可以任选两个颜色相同格子，将以他们为对顶点构成的矩形染成与这两个点相同的颜色，问能不能将整个矩形染成相同的颜色。

有 $t$ 组数据。

### 输入格式
第一行一个整数 $t(1\le t\le 10^{4} )$，表示有 $t$ 组数据。

每组数据的第一行为两个整数 $n,m(1\le n,m\le 500)$，表示矩形的行数和列数。

接下来 $n$ 行，每行 $m$ 个字符，表示矩形的初始颜色。

### 输出格式
一共 $t$ 行，每行为 `YES` 或 `NO`，表示能否把这组数据中的矩形染成相同的颜色。

## 思路：
我们可以发现如果有两个对角的颜色相同，那么可以直接将整个矩形染色。

如果没有对角颜色相同，我们可以尝试着把其中某一对对角染成相同的颜色，以达到第一种情况。

如果在其中一个角所在的边和列上都有与它不同的颜色，我们就可以将这个角染成与它相反的颜色。

按此方法枚举每个角即可。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
bool f,f1;
char a[1145][1145];
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>a[i][j];
			}
		}
		if(a[1][1]==a[n][m]||a[1][m]==a[n][1]){
			cout<<"YES"<<endl;
			continue;
		}
		f1=f=0;
		for(int i=2;i<=n;i++){
			if(a[i][1]!=a[1][1]){
				f=1;
				break;
			}
		}
		for(int i=2;i<=m;i++){
			if(a[1][m]!=a[1][1]){
				if(f==1){
					cout<<"YES"<<endl;
					f1=1;
					break;
				}
			}
		}
		if(f1==1){
			continue;
		}
		f1=f=0;
		for(int i=1;i<=m-1;i++){
			if(a[1][i]!=a[1][m]){
				f=1;
				break;
			}
		}
		for(int i=2;i<=n;i++){
			if(a[i][m]!=a[1][m]){
				if(f==1){
					cout<<"YES"<<endl;
					f1=1;
					break;
				}
			}
		}
		if(f1==1){
			continue;
		}
		f1=f=0;
		for(int i=1;i<=n-1;i++){
			if(a[i][1]!=a[n][1]){
				f=1;
				break;
			}
		}
		for(int i=2;i<=m;i++){
			if(a[n][i]!=a[n][1]){
				if(f==1){
					cout<<"YES"<<endl;
					f1=1;
					break;
				}
			}
		}
		if(f1==1){
			continue;
		}
		f1=f=0;
		for(int i=1;i<=m-1;i++){
			if(a[n][i]!=a[n][m]){
				f=1;
				break;
			}
		}
		for(int i=1;i<=n-1;i++){
			if(a[i][m]!=a[n][m]){
				if(f==1){
					cout<<"YES"<<endl;
					f1=1;
					break;
				}
			}
		}
		if(f1==1){
			continue;
		}
		cout<<"NO"<<endl;
	}
	return 0;
}
```

---

## 作者：_dbq_ (赞：0)

## 前言
没有读题的同学可以点击[这里](https://www.luogu.com.cn/problem/CF1966B)先读题。

## 思路
我们发现当对角线的两端的格子是相同颜色时，可以直接将棋盘全部染色。

当两种颜色不同时，我们可以将其中一个格子染成另外一种颜色，这样就能转化为上一种情况，全部染色。

这个格子能否被染成另外一种颜色的条件是，它所在的行和列是否都有和它不同的颜色。如果有则可以，反之就不行。

## 代码
```cpp
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<string>
#include<stdlib.h>
#include<cstdio>
#include<cstring>
#include<queue>
#include<stack>
#include<vector>
#define LL long long
#define ULL unsigned long long
#define cint const int 
using namespace std;
cint INTINF=0x7f7f7f7f;
const LL LLINF=9e18;
char c[510][510];//存数据
inline auto read(){//快读
    auto x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int main()
{
    #ifdef dbq
    freopen("CF1966B.in","r",stdin);
    freopen("CF1966B.out","w",stdout);
    #endif
    int T=read();//多组数据
    while(T--)
    {
        cint n=read(),m=read();
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                cin>>c[i][j];
        if(c[1][1]==c[n][m]||c[1][m]==c[n][1]) cout<<"YES"<<endl;//判断对角线的两端
        else//以下的步骤极其繁琐，如有更好的代码，可以私信我
        {
            int rw1=0,cw1=0,rw2=0,cw2=0,rw3=0,cw3=0,rw4=0,cw4=0,rb1=0,cb1=0,rb2=0,cb2=0,rb3=0,cb3=0,rb4=0,cb4=0;//记录行列上的格子颜色
            //依次记录
            for(int i=2;i<=m;i++)
                if(c[1][i]=='W') rw1++;
                else if(c[1][i]=='B') rb1++;
            for(int i=2;i<=n;i++)
                if(c[i][1]=='W') cw1++;
                else if(c[i][1]=='B') cb1++;
            for(int i=1;i<m;i++)
                if(c[1][i]=='W') rw2++;
                else if(c[1][i]=='B') rb2++;
            for(int i=2;i<=n;i++)
                if(c[i][m]=='W') cw2++;
                else if(c[i][m]=='B') cb2++;
            for(int i=2;i<=m;i++)
                if(c[n][i]=='W') rw3++;
                else if(c[n][i]=='B') rb3++;
            for(int i=1;i<n;i++)
                if(c[i][1]=='W') cw3++;
                else if(c[i][1]=='B') cb3++;
            for(int i=1;i<m;i++)
                if(c[n][i]=='W') rw4++;
                else if(c[n][i]=='B') rb4++;
            for(int i=1;i<n;i++)
                if(c[i][m]=='W') cw4++;
                else if(c[i][m]=='B') cb4++;
            
            //判断能否染色
            if(c[1][1]=='W'&&rb1!=0&&cb1!=0) cout<<"YES"<<endl;
            else if(c[1][1]=='B'&&rw1!=0&&cw1!=0) cout<<"YES"<<endl;
            else if(c[1][m]=='B'&&rw2!=0&&cw2!=0) cout<<"YES"<<endl;
            else if(c[1][m]=='W'&&rb2!=0&&cb2!=0) cout<<"YES"<<endl;
            else if(c[n][1]=='B'&&rw3!=0&&cw3!=0) cout<<"YES"<<endl;
            else if(c[n][1]=='W'&&rb3!=0&&cb3!=0) cout<<"YES"<<endl;
            else if(c[n][m]=='B'&&rw4!=0&&cw4!=0) cout<<"YES"<<endl;
            else if(c[n][m]=='W'&&rb4!=0&&cb4!=0) cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
        }
    }
    return 0;
}
```

---

## 作者：Pyrf_uqcat (赞：0)

题目思路还是很简单的，看一眼标签，**模拟**。

题板挺好理解，选择两个颜色一样的点，可以把之间的矩阵染成和这两个颜色同色。

既然要找两个点，那就枚举找两个同色点。

判断矩阵四条边是否有同色点，就能染色，把矩阵变成这种颜色，否则就不能染。这题就简单秒了。

---

