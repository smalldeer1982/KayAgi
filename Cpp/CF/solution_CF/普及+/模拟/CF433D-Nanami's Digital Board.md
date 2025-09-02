# Nanami's Digital Board

## 题目描述

Nanami is an expert at playing games. This day, Nanami's good friend Hajime invited her to watch a game of baseball. Unwilling as she was, she followed him to the stadium. But Nanami had no interest in the game, so she looked around to see if there was something that might interest her. That's when she saw the digital board at one end of the stadium.

The digital board is $ n $ pixels in height and $ m $ pixels in width, every pixel is either light or dark. The pixels are described by its coordinate. The $ j $ -th pixel of the $ i $ -th line is pixel $ (i,j) $ . The board displays messages by switching a combination of pixels to light, and the rest to dark. Nanami notices that the state of the pixels on the board changes from time to time. At certain times, certain pixels on the board may switch from light to dark, or from dark to light.

Nanami wonders, what is the area of the biggest light block such that a specific pixel is on its side. A light block is a sub-rectangle of the board, in which all pixels are light. Pixel $ (i,j) $ belongs to a side of sub-rectangle with $ (x_{1},y_{1}) $ and $ (x_{2},y_{2}) $ as its upper-left and lower-right vertex if and only if it satisfies the logical condition:

(( $ i=x_{1} $ or $ i=x_{2} $ ) and ( $ y_{1}<=j<=y_{2} $ )) or (( $ j=y_{1} $ or $ j=y_{2} $ ) and ( $ x_{1}<=i<=x_{2} $ )).Nanami has all the history of changing pixels, also she has some questions of the described type, can you answer them?

## 说明/提示

Consider the first sample.

The first query specifies pixel $ (2,2) $ , which is dark itself, so there are no valid light blocks, thus the answer is 0.

The second query specifies pixel $ (1,2) $ . The biggest light block is the block with $ (1,2) $ as its upper-left vertex and $ (1,3) $ as its lower-right vertex.

The last query specifies pixel $ (2,2) $ , which became light in the third operation. The biggest light block is the block with $ (1,2) $ as its upper-left vertex and $ (3,3) $ as its lower-right vertex.

## 样例 #1

### 输入

```
3 4 5
0 1 1 0
1 0 0 1
0 1 1 0
2 2 2
2 1 2
1 2 2
1 2 3
2 2 2
```

### 输出

```
0
2
6
```

## 样例 #2

### 输入

```
3 3 4
1 1 1
1 1 1
1 1 1
2 2 2
1 2 2
2 1 1
2 2 1
```

### 输出

```
6
3
3
```

# 题解

## 作者：SkyRainWind (赞：1)

题意：

七海千秋和日向创在玩游戏。抽象来说是这么一个问题：

一个 $n \times m$ 的矩阵，每个元素都是 $0/1$，有 $q$ 个操作，每个操作形如 $op,x,y$ ，如果 $op$ 为 $1$ ，就将 $(x,y)$ 的 $0/1$ 值取反，如果 $op$ 为 $2$ ，就查询 $(x,y)$ 所在的全为 $1$ 的矩阵中最大的面积（当然 $(x,y)$ 本身也得是 $1$ ），其中 $(x,y)$ 这个点是该矩阵四条边上的一个点。

题解：

这套题浓度爆表啊。。不然我还真不一定能做下去。

$(i,j)$ 在边界上，不妨以左边界为例，其余同理。考虑维护 $lft[i][j]$ 表示 $(i,j)$ 本身为 $1$ ，且能向右拓展1的最远距离。同理维护 $up$ $down$ $right$。

查询的时候就向右扫，记一个 $min_1$ 表示向上的最小长度，$min_2$ 表示向下的，然后当前位置  $(i,y)$ 的贡献就是 $(y-j+1) \times (min_1+min_2-1)$ 。

同理维护其它的即可，代码会有很多重复的部分，一定要仔细。我少复制了一句话调了1h+。

```cpp
// LUOGU_RID: 94164894
// by SkyRainWind
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define mpr make_pair
#define debug() cerr<<"Yoshino\n"
#define rep(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)
#define pii pair<int,int>
 
using namespace std;
 
typedef long long LL;
 
const int inf = 1e9, INF = 0x3f3f3f3f, maxn = 1005;
 
int n,m,q,a[maxn][maxn],ut[maxn][maxn][4];	// 0 left 1 right 2 up 3 down
 
signed main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;){
			if(a[i][j] == 0){
				ut[i][j][0] = 0;
				++ j;
				continue;
			}
			int cnt = 0;
			while(a[i][j]){
				ut[i][j][0] = ++ cnt;
				++ j;
			}
		}
		for(int j=m;j>=1;){
			if(a[i][j] == 0){
				ut[i][j][1] = 0;
				-- j;
				continue;
			}
			int cnt = 0;
			while(a[i][j]){
				ut[i][j][1] = ++ cnt;
				-- j;
			}
		}
	}
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;){
			if(a[i][j] == 0){
				ut[i][j][2] = 0;
				i ++;continue;
			}
			int cnt = 0;
			while(a[i][j] == 1){
				ut[i][j][2] = ++ cnt;
				++ i;
			}
		}
		for(int i=n;i>=1;){
			if(a[i][j] == 0){
				ut[i][j][3] = 0;
				i --;continue;
			}
			int cnt = 0;
			while(a[i][j] == 1){
				ut[i][j][3] = ++ cnt;
				-- i;
			}
		}
	}
	
	while(q --){
		int op,x,y;scanf("%d%d%d",&op,&x,&y);
		if(op == 2){
			if(a[x][y] == 0){
				puts("0");
				continue;
			}
			// 0 left 1 right 2 up 3 down
			int ans = ut[x][y][2] + ut[x][y][3] - 1;
			
			int mn1=ut[x][y][2], mn2 = ut[x][y][3];
			for(int i=y+1;i<=y+ut[x][y][1]-1;i++){
				mn1 = min(mn1, ut[x][i][2]);
				mn2 = min(mn2, ut[x][i][3]);
				ans = max(ans, (mn1 + mn2 - 1) * (i-y+1));
			}	// to rightmost
			
			mn1=ut[x][y][2], mn2 = ut[x][y][3];
			for(int i=y-1;i>=y-ut[x][y][0]+1;i--){
				mn1 = min(mn1, ut[x][i][2]);
				mn2 = min(mn2, ut[x][i][3]);
				ans = max(ans, (mn1 + mn2 - 1) * (y-i+1));
			}	// to leftmost
			
			mn1=ut[x][y][0], mn2 = ut[x][y][1];
			ans = max(ans, mn1 + mn2 - 1);
			
			for(int i=x+1;i<=x+ut[x][y][3]-1;i++){
				mn1 = min(ut[i][y][0], mn1);
				mn2 = min(ut[i][y][1], mn2);
				ans = max(ans, (mn1 + mn2 - 1) * (i-x+1));
			} 	// to bottom
			mn1 = ut[x][y][0], mn2 = ut[x][y][1];
			
			for(int i=x-1;i>=x-ut[x][y][2]+1;i--){
				mn1 = min(ut[i][y][0], mn1);
				mn2 = min(ut[i][y][1], mn2);
				ans = max(ans, (mn1 + mn2 - 1) * (x-i+1));
			} 	// to top
			printf("%d\n",ans);
		}else{
			a[x][y] ^= 1;
			if(a[x][y] == 1){
				ut[x][y][1] = ut[x][y+1][1] + 1;
				ut[x][y][0] = ut[x][y-1][0] + 1;
				ut[x][y][2] = ut[x-1][y][2] + 1;
				ut[x][y][3] = ut[x+1][y][3] + 1;
			}else ut[x][y][0] = ut[x][y][1] = ut[x][y][2] = ut[x][y][3] = 0;
		
			for(int i=y-1;i>=1;i--){
				if(a[x][i] == 0)break;
				ut[x][i][1] = ut[x][i+1][1] + 1;
			}
			for(int i=y+1;i<=m;i++){
				if(a[x][i] == 0)break;
				ut[x][i][0] = ut[x][i-1][0] + 1;
			}
			for(int i=x+1;i<=n;i++){
				if(a[i][y] == 0)break;
				ut[i][y][2] = ut[i-1][y][2] + 1;
			}
			for(int i=x-1;i>=1;i--){
				if(a[i][y] == 0)break;
				ut[i][y][3] = ut[i+1][y][3] + 1;
			}
		}
	}
 
	return 0;
}
```

---

## 作者：_JF_ (赞：0)

[Link](https://www.luogu.com.cn/problem/CF433D)

~~这老哥差点连模拟都做不出来。~~

注意 $(x,y)$ 必须是四条边上的点，我们以让他成为最上面那条边来举例，其他类似。

首先我们先考虑查询，一个想法是我们处理出来当前行每个点往下延申最长连续 $1$ 的个数，记为 $s_i$，然后计算 $[l,r]$ 的答案其实就是 $(\min \limits_{i=l}^r s_i)\times (r-l+1)$。

这个 $\min$ 其实不好处理，我们不妨记 $s'_i$ 表示从起点 $y$ 出发，到当前点 $r$ 的 $s_i$ 最小值。（在我们讨论的这种情况内，我们只用考虑纵坐标），这里 $s'$ 的含义就是，选择了以 $[y,r]$ 段时的宽的长度。

那么显然，如果我选了 $[y,r]$ 这一段，这个宽就是 $s'_r$。且我们能够发现，这个 $s'$ 在 $y$ 的左边和右边恰好的单调不升的。

所以，我们这时候看成两段，枚举 $s'_i$，钦定他是最小值，以右边段为例，这时候 $[y,i]$ 我们肯定可以拿到，然后在左边 $\geq s'_i$ 的位置我们也都能拿到。这个直接二分求解即可。

然后你发现其实剩下的三个方向，单独拎出来也是一样的问题。

哦，还有修改。修改就是，你观察到每次改变 $(x,y)$，只会对当前行和当前列有影响，直接重构就行了。

不好想，也不好写。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1010;
int n,m,t,a[N][N],Up[N][N],Down[N][N],Left[N][N],Right[N][N];
int dus[N],Dus1[N],Dus2[N],tot,Ans;
void CG_H(int x){
	int Dus=0;
	for(int i=1;i<=m;i++){
		if(a[x][i]==1)	Dus++; else Dus=0;
		Left[x][i]=Dus;	
	}
	Dus=0;
	for(int i=m;i>=1;i--){
		if(a[x][i]==1)	Dus++; else Dus=0;
		Right[x][i]=Dus;
	}
}
void CG_L(int x){
	int Dus=0;
	for(int i=1;i<=n;i++){
		if(a[i][x]==1)	Dus++;	else Dus=0;
		Up[i][x]=Dus;	
	}
	Dus=0;
	for(int i=n;i>=1;i--){
		if(a[i][x]==1)	Dus++;   else Dus=0;
		Down[i][x]=Dus;
	}
} 
void Slove(int id){
	for(int i=id-1;i>=1;i--)	dus[i]=min(dus[i],dus[i+1]);
	for(int i=id+1;i<=tot;i++)	dus[i]=min(dus[i],dus[i-1]);
	Ans=max(Ans,dus[id]);
	for(int i=1;i<=id;i++)	Dus1[i]=dus[i];
	for(int i=tot,p=1;i>=id;i--,p++)	Dus2[p]=dus[i];
	
	int Len1=tot-id+1;
	for(int i=1;i<=id;i++){
		int pre=Dus1[i],Len=(id-i+1);
		
		int lst=lower_bound(Dus2+1,Dus2+Len1+1,pre)-Dus2;
		if(lst<=Len1)
			Len+=(Len1-lst+1)-1;
		Ans=max(Ans,pre*Len);
	}
	
	for(int i=1;i<=Len1;i++){
		int pre=Dus2[i],Len=(Len1-i+1);
		int lst=lower_bound(Dus1+1,Dus1+id+1,pre)-Dus1;
		if(lst<=id)
			Len+=(id-lst+1)-1;
		Ans=max(Ans,pre*Len);
	}
	
}
int main(){
//	freopen("1.in","r",stdin);
//	freopen("ans1.out","w",stdout);
	cin>>n>>m>>t;
	for(int i=1;i<=n;i++)	for(int j=1;j<=m;j++)	cin>>a[i][j];
	for(int i=1;i<=n;i++)	CG_H(i);
	for(int i=1;i<=m;i++)	CG_L(i);
	while(t--){
		int op,x,y;
		cin>>op>>x>>y;
		if(op==1){
			a[x][y]=!a[x][y];
			CG_H(x); CG_L(y);
		}
		else{	
			Ans=0;
			
			tot=0;
			for(int i=1;i<=m;i++)	dus[++tot]=Down[x][i];
			Slove(y);
			
			tot=0;
			for(int i=1;i<=m;i++)	dus[++tot]=Up[x][i];
			Slove(y);	
			
			tot=0;
			for(int i=1;i<=n;i++)	dus[++tot]=Left[i][y];
			Slove(x);
				
			tot=0;
			for(int i=1;i<=n;i++)	dus[++tot]=Right[i][y];
			Slove(x);	
		
			cout<<Ans<<endl;	
		}
	}
	return 0;
} 
```

---

