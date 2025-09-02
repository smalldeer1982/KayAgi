# Pasha and Pixels

## 题目描述

Pasha loves his phone and also putting his hair up... But the hair is now irrelevant.

Pasha has installed a new game to his phone. The goal of the game is following. There is a rectangular field consisting of $ n $ row with $ m $ pixels in each row. Initially, all the pixels are colored white. In one move, Pasha can choose any pixel and color it black. In particular, he can choose the pixel that is already black, then after the boy's move the pixel does not change, that is, it remains black. Pasha loses the game when a $ 2×2 $ square consisting of black pixels is formed.

Pasha has made a plan of $ k $ moves, according to which he will paint pixels. Each turn in his plan is represented as a pair of numbers $ i $ and $ j $ , denoting respectively the row and the column of the pixel to be colored on the current move.

Determine whether Pasha loses if he acts in accordance with his plan, and if he does, on what move the $ 2×2 $ square consisting of black pixels is formed.

## 样例 #1

### 输入

```
2 2 4
1 1
1 2
2 1
2 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
2 3 6
2 3
2 2
1 3
2 2
1 2
1 1
```

### 输出

```
5
```

## 样例 #3

### 输入

```
5 3 7
2 3
1 2
1 1
4 1
3 1
5 3
3 2
```

### 输出

```
0
```

# 题解

## 作者：_Flame_ (赞：0)

## 思路

思路很简单，对于每一次操做进行一次模拟判断即可。

题目求是否有一个 $2\times 2$ 的矩阵全部为黑色，对于某个点 $(x,y)$ 来说，其实只有四种情况，及以这个点为 $2\times 2$ 矩阵的左上、左下、右上、右下进行搜索，假如遇见 $(x,y),(x+1,y+1),(x+1,y),(x,y+1)$ 或 $(x,y),(x-1,y+1),(x-1,y),(x,y+1)$ 或 $(x,y),(x+1,y-1),(x+1,y),(x,y-1)$ 或 $(x,y),(x-1,y-1),(x-1,y),(x,y-1)$ 四种中的任意一种出现了全是黑色的情况，即为出现了一个 $2\times 2$ 的全黑矩阵，此时输出当前的次数 $T$ 即可。

## Code

```cpp

#include<bits/stdc++.h>
using namespace std;

int n,m,k;
int a[1001][1001];

bool check(int x,int y){
	if(a[x][y]==1&&a[x-1][y-1]==1&&a[x-1][y]==1&&a[x][y-1]==1){
		return 1;
	}
	if(a[x][y]==1&&a[x+1][y+1]==1&&a[x+1][y]==1&&a[x][y+1]==1){
		return 1;
	}
	if(a[x][y]==1&&a[x+1][y-1]==1&&a[x+1][y]==1&&a[x][y-1]==1){
		return 1;
	}
	if(a[x][y]==1&&a[x-1][y+1]==1&&a[x-1][y]==1&&a[x][y+1]==1){
		return 1;
	}
	return 0;
}

int main(){
	cin>>n>>m>>k;
	for(int t=1;t<=k;t++){
		int x,y;
		cin>>x>>y;
		a[x][y]=1;
		if(check(x,y)){
			cout<<t<<endl;
			return 0;
		}
	}
	cout<<0<<endl;
	return 0;
}

```

---

## 作者：f_x_f (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF508A) [CF传送门](https://codeforces.com/contest/508/problem/A) [更好的食用指南](https://www.cnblogs.com/bairixingchen/p/16684927.html)

话说这道题咋这么多坑！

## 具体思路
把全部位置第一次染成黑色的轮次是第几轮，时间复杂度为 $\varTheta(k)$ ，接着从点 $1,1$ 一直到点 $n-1,m-1$ 全部都判断一遍 ，时间复杂度为 $\varTheta(nm)$ ，总时间复杂度为 $\varTheta(nm+k)$ 又因为 $n,m\le 10^3$ 且 $k\le 10^5$ ，所以并不会超时。

## 做法讲解
### 1 存法
我用了一个 $a_{i,j}$ 表示在位置 $i,j$ 第一次被染色的时候是第几次。

但是由于题目要求取的是最小值，因此需要用一个 min 函数来辅助我们更新数值。

$ans$ 表示答案，及最小的次数，使得出现 $2\times 2$ 的黑色格子时，至少需要经过多少次。

### 2 判断与求解
接下来是判断部分，我们首先需要将每个地方都判断过一次，如果这个数与其右边，下边，右下边均不为初始化的值，那么我们可以对 $ans$ 进行更新，代码如下：
```cpp
			if(a[i][j]<114514&&a[i][j+1]<114514&&a[i+1][j]<114514&&a[i+1][j+1]<114514){
				ans=min(ans,max(a[i][j],max(a[i+1][j],max(a[i][j+1],a[i+1][j+1]))));
				//答案要取最小值（题目要求）
			}
```
由此，我们可以得出代码。

## 奉上代码
```cpp
#include<bits/stdc++.h>
namespace my_std{
	using namespace std;
	#define ll long long
	#define ref(i,x,y) for(register int i=(x);i<=(y);i++)
	#define fer(i,x,y) for(register int i=(x);i>=(y);i--)
	#define il inline
	#define mpii map<int,int>
	#define mpib map<int,bool>
	#define mpplll map<pll,ll>
	#define mppccl map<pcc,ll>
	#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
	char buf[1<<21],*p1=buf,*p2=buf;
	inline ll read(){
	    char c=getchar();
	    ll x=0;
	    for(;!isdigit(c);c=getchar());
	    for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	    return x;
	}
}
using namespace my_std;
int n,m,k,ans=114514;
int a[1010][1010];
int main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(false);
	//输入输出优化，正常来讲可以不写
	cin>>n>>m>>k;
	memset(a,114514,sizeof(a));
	/*
	初始化a[i][j]要为一个很大的数
	因为后面需要取较小的值
	*/
//	ref(i,1,n){
//		ref(j,1,m){
//			cin>>a[i][j];
//		}
//	}
	ref(i,1,k){
		int x,y;
		cin>>x>>y;
		a[x][y]=min(a[x][y],i);
		//a[i][j]尽量的小，因此需要用min函数
	}
	ref(i,1,n){
		ref(j,1,m){
			if(a[i][j]<114514&&a[i][j+1]<114514&&a[i+1][j]<114514&&a[i+1][j+1]<114514){
				ans=min(ans,max(a[i][j],max(a[i+1][j],max(a[i][j+1],a[i+1][j+1]))));
				//答案要取最小值（题目要求）
			}
		}
	}
	cout<<((ans==114514)?0:ans)<<endl;
}


```

---

## 作者：S__X (赞：0)

问第一次出现 $2\times 2$ 的全部涂成黑色的矩阵是第几个操作。

## 思路：
每查找一个格子就判断一下，看看是否构成一个 $2\times 2$ 的矩阵。如果构成了 $2\times 2$ 的矩阵，就输出当前的序号。

### 判断是否构成 $2\times 2$ 的矩阵：
1. 以当前格子为右上角进行搜索：要搜索的点为 $(x,y)(x-1,y)(x,y-1)(x-1,y-1)$。
2. 以当前格子为左上角进行搜索：要搜索的点为 $(x,y)(x+1,y)(x,y-1)(x+1,y-1)$。
3. 以当前格子为左下角进行搜索：要搜索的点为 $(x,y)(x+1,y)(x,y+1)(x+1,y+1)$。
3. 以当前格子为右下角进行搜索：要搜索的点为 $(x,y)(x-1,y)(x,y+1)(x-1,y+1)$。

## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t,x,y,i,a[1001][1001];
bool search(int x,int y){
	if(a[x][y]==1&&a[x-1][y]&&a[x][y-1]==1&&a[x-1][y-1]==1) return 1;//以当前格子为右上角进行搜索
	if(a[x][y]==1&&a[x+1][y]&&a[x][y-1]==1&&a[x+1][y-1]==1) return 1;//以当前格子为左上角进行搜索
	if(a[x][y]==1&&a[x+1][y]&&a[x][y+1]==1&&a[x+1][y+1]==1) return 1;//以当前格子为左下角进行搜索
	if(a[x][y]==1&&a[x-1][y]&&a[x][y+1]==1&&a[x-1][y+1]==1) return 1;//以当前格子为右下角进行搜索
	return 0;
}
int main(){
	cin>>n>>m>>t;
	for(i=1;i<=t;i++){//当前操作序号
		cin>>x>>y;
		a[x][y]=1;
		if(search(x,y)) {//判断是否为2*2的矩阵
			cout<<i<<endl;
			return 0;
		}
	}
	cout<<0<<endl;
	return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
有一个 $n\times m$ 的矩阵，一开始全部格子被染成白色。 接下来有 $k$ 个操作，每一个操作表示把一个格子染成黑色。问第一次出现 $2\times 2$ 的全部涂成黑色的矩阵是第几个操作，或者没有出现这样的矩阵。

**数据范围：$1\leqslant n,m\leqslant 1000,1\leqslant k\leqslant 10^5$。**
## Solution
我们可以边涂黑边判断，假设现在将 $(x,y)$ 涂成黑色。那么，出现一个 $2\times 2$ 的全部涂成黑色的矩阵只会有 $4$ 种情况：

1. $(x,y),(x-1,y),(x,y-1),(x-1,y-1)$ 全部涂成黑色。
2. $(x,y),(x+1,y),(x,y-1),(x+1,y-1)$ 全部涂成黑色。
3. $(x,y),(x-1,y),(x,y+1),(x-1,y+1)$ 全部涂成黑色。
4. $(x,y),(x+1,y),(x,y+1),(x+1,y+1)$ 全部涂成黑色。

只要满足上面四种情况中的任意一种，直接输出答案结束。否则，操作全部执行完毕还是没有出现，输出 $0$。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

int n, m, k, a[1007][1007];

bool check1(int x, int y) {
	return a[x][y] && a[x - 1][y] && a[x][y - 1] && a[x - 1][y - 1];
}
bool check2(int x, int y) {
	return a[x][y] && a[x + 1][y] && a[x][y - 1] && a[x + 1][y - 1];
}
bool check3(int x, int y) {
	return a[x][y] && a[x - 1][y] && a[x][y + 1] && a[x - 1][y + 1];
}
bool check4(int x, int y) {
	return a[x][y] && a[x + 1][y] && a[x][y + 1] && a[x + 1][y + 1];
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= k; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		a[x][y] = 1;
		if(check1(x, y) || check2(x, y) || check3(x, y) || check4(x, y))
			return printf("%d", i), 0;
	}
	return printf("0"), 0;
}
```

---

## 作者：封禁用户 (赞：0)

题目传送门：[CF508A Pasha and Pixels](https://www.luogu.com.cn/problem/CF508A)

**题解：** 这题直接模拟，当有一个点被染成黑色，就判断这个点分别为左上角、右上角、左下角、右下角时，是否能构成$2\times 2$的黑色格子。

$Code:$

```pascal
var n,m,k,i,x,y:longint;
    a:array[1..1002,1..1002] of integer;
begin
  read(n,m,k);
  for i:=1 to k do
  begin
    read(x,y);
    a[x,y]:=1;
    if (a[x-1,y-1]=1) and (a[x-1,y]=1) and (a[x,y-1]=1) then begin write(i); halt; end
    else if (a[x-1,y+1]=1) and (a[x-1,y]=1) and (a[x,y+1]=1) then begin write(i); halt; end
    else if (a[x+1,y-1]=1) and (a[x+1,y]=1) and (a[x,y-1]=1) then begin write(i); halt; end
    else if (a[x+1,y+1]=1) and (a[x+1,y]=1) and (a[x,y+1]=1) then begin write(i); halt; end
  end;
  write('0');
end.
```


---

## 作者：A_Đark_Horcrux (赞：0)

暴力模拟。每输入一个坐标，就判断一次是否构成2*2的黑色正方形，如果行就直接输出，不行最后输出0即可。

直接看代码吧：
```cpp
#include<cstdio>
using namespace std;
int n,m,t,x,y,i,a[1001][1001];
bool pd(int x,int y)//暴力判断
{
	if(a[x][y]==1&&a[x-1][y]&&a[x][y-1]==1&&a[x-1][y-1]==1) return 1;//以当前格子为右下角判断
	if(a[x][y]==1&&a[x+1][y]&&a[x][y+1]==1&&a[x+1][y+1]==1) return 1;//以当前格子为左上角判断
	if(a[x][y]==1&&a[x-1][y]&&a[x][y+1]==1&&a[x-1][y+1]==1) return 1;//以当前格子为右上角判断
	if(a[x][y]==1&&a[x+1][y]&&a[x][y-1]==1&&a[x+1][y-1]==1) return 1;//以当前格子为左下角判断
	return 0;//如果都不行，返回不行
}
int main()
{
	scanf("%d %d %d",&n,&m,&t);
	for(i=1;i<=t;i++)
	{
		scanf("%d %d",&x,&y); a[x][y]=1;//输入，标记黑色
		if(pd(x,y)) return !printf("%d",i);//如果OK，直接输出i
	}
	printf("0");//如果不OK，最后输出0
	return 0;
}
```


---

