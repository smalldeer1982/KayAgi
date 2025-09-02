# Move and Turn

## 题目描述

A robot is standing at the origin of the infinite two-dimensional plane. Each second the robot moves exactly $ 1 $ meter in one of the four cardinal directions: north, south, west, and east. For the first step the robot can choose any of the four directions, but then at the end of every second it has to turn 90 degrees left or right with respect to the direction it just moved in. For example, if the robot has just moved north or south, the next step it takes has to be either west or east, and vice versa.

The robot makes exactly $ n $ steps from its starting position according to the rules above. How many different points can the robot arrive to at the end? The final orientation of the robot can be ignored.

## 说明/提示

In the first sample case, the robot will end up 1 meter north, south, west, or east depending on its initial direction.

In the second sample case, the robot will always end up $ \sqrt{2} $ meters north-west, north-east, south-west, or south-east.

## 样例 #1

### 输入

```
1```

### 输出

```
4```

## 样例 #2

### 输入

```
2```

### 输出

```
4```

## 样例 #3

### 输入

```
3```

### 输出

```
12```

# 题解

## 作者：pyyyyyy (赞：11)

> 有一个无限展的二维平面，一个机器人每秒可以前进一个单位，但是每一秒之后，机器人必须向左转或者向右转。问你$n$秒之后机器人可能出现的坐标的数量。

找规律的话，就先用$bfs$打表(注意$bfs$会爆内存)，然后就能发现规律：

- 若$n$是偶数，则答案为$(n / 2 + 1)^2$

- 若$n$是奇数，则答案为$k=\frac{n}{2},2*(k+1)(k+2)$

考虑$n$为偶数时的情况。无论初始方向如何，我们将进行$n/2$个水平步和$n/2$个垂直步。此外，水平和垂直步数的方向可以单独决定。

比如有$k$个水平方向的选择，那么最后的落点横坐标就是$[-k,-k+2,.....k]$

则偶数答案为$(n/2+1)^2$

奇数的情况需要考虑第一步是水平的还是垂直的，这里首先说明一个结论

**最终的水平位置x的奇偶性与水平步数相同**

由此得出：**从垂直和水平步数开始都不可能到达相同的位置**

$n=2k+1$是奇数。如果我们从水平步开始，那么总共将进行$k+1$个水平步和$k$个垂直步，那么最后到达点数是$(k+1)*(k+2)$（可以参考偶数情况理解）

最后答案就是$2*(k+1)*(k+2)，k=n/2$

本题告诉我们，像这类在二维坐标系上移动的题目：

- 可以单独分离出横纵坐标，然后利用简单计数原理进行求解

- 从奇偶数角度考虑


---

## 作者：Warriors_Cat (赞：2)

[题面传送门](https://www.luogu.com.cn/problem/CF1459B)。

题意可以从上面看。

---

### $Solution:$

~~众所周知，看到这种输入量少的题，我们应当找规律。——WYXkk~~

考虑将小数据[打表](https://www.luogu.com.cn/paste/x2c9bwl4)，观察其性质。

然后我们就会发现：

当 $n$ 是奇数时，能到达的点和不能到达的点刚好交错开来，这时答案为 $\dfrac{(n + 2) * (n + 2) - 1}{2}$；

当 $n$ 是偶数时，将这些 `1` 压缩刚刚好成一个正方形，其边长为 $\dfrac{n}{2}+1$，于是答案为 $(\dfrac{n}{2}+1)^2$。

证明的话，直接归纳即可。对于每一个 $n$，$n + 2$ 的情况就相当于 $n$ 的所有 `1` 走一个 $2 \times 2$ 的对角线。

over，时间复杂度为 $O(1)$。

---

### $Code:$

以下为赛时代码。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;
#define ll long long
#define fi first
#define se second
#define y1 y_csyakioi_1
#define y0 y_csyakioi_0
#define dingyi int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1;
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
const int N = 1010; int n;
inline void work(){
	n = read();
	if(n & 1) printf("%d\n", ((n + 2) * (n + 2) - 1) / 2);
	else printf("%d\n", (n / 2 + 1) * (n / 2 + 1));
}
int main(){
	int t = 1; while(t--) work();
	return 0;
}
```


---

## 作者：hzoi_liuchang (赞：2)

## 分析
对于方格中移动的问题，可以用 $dp$ 解决

设 $f[i][j][k][0/1]$ 表示当前走到第 $i$ 步，位于坐标 $(j,k)$，并且这一步是南北方向$(0)$ 或东西方向 $(1)$

然后转移就非常简单了

$f[i][j][k][1]->f[i+1][j+1/j-1][k][0]$

$f[i][j][k][0]->f[i+1][j][k+1/k-1][1]$

用滚动数组可以解决空间的问题，但是时间复杂度 $n^3$ 有点大

因为 $n$ 只有 $1000$ ，所以可以打表
## 代码
``` cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define rg register
inline int read(){
	rg int x=0,fh=1;
	rg char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*fh;
}
const int maxn=2e3+5,bas=1e3+2;
bool f[2][maxn][maxn][2];
int ans;
int main(){
	rg int now=1;
	f[1][bas+1][bas][0]=1;
	f[1][bas-1][bas][0]=1;
	f[1][bas][bas+1][1]=1;
	f[1][bas][bas-1][1]=1;
	for(rg int o=2;o<=1000;o++){
		now^=1;
		for(rg int i=bas-o;i<=bas+o;i++){
			for(rg int j=bas-o;j<=bas+o;j++){
				f[now][i][j][0]=f[now][i][j][1]=0;
			}
		}
		for(rg int i=bas-o;i<=bas+o;i++){
			for(rg int j=bas-o;j<=bas+o;j++){
				if(f[now^1][i][j][0]){
					f[now][i][j+1][1]=f[now][i][j-1][1]=1;
				}
				if(f[now^1][i][j][1]){
					f[now][i+1][j][0]=f[now][i-1][j][0]=1;
				}
			}
		}
		ans=0;
		for(rg int i=bas-o;i<=bas+o;i++){
			for(rg int j=bas-o;j<=bas+o;j++){
				ans+=(f[now][i][j][0]|f[now][i][j][1]);
			}
		}
		printf("%d,",ans);
	}
	return 0;
}
```

---

## 作者：vеctorwyx (赞：2)

### 题目大意：

在一个无限大的平面上游走，每次移动一个单位，不能跟上次方向相同或相反，即如果上一步向东或向西走的，这一步必须向南或北走。

求走$n$步有多少地方可以到达。

### sol

手玩几个小数据可以发现，走$i$步可以到达$\large(\lfloor \frac {i}{2}\rfloor\times4)$个以前从未到达过的点，这些可以直接记录（建议画图理解）。

其他点要分奇偶处理：

- 奇数：

	可以用三步代替一步来走， 但是方向会改变，如图
    
    ![可能图坏了](https://cdn.luogu.com.cn/upload/image_hosting/60jmnz3a.png)
    
    所以奇数还可以额外到达$i-2$步能到达的所有点。
    
- 偶数：
	
    可以用四步代替0步来走，没有方向限制，如果
    
    ![可能图崩了](https://cdn.luogu.com.cn/upload/image_hosting/3o57au9s.png)
    
    所以偶数还以额外到达$i-4$步能到达的所有点。
    
    （奇数不这么算是因为$i-2$步里也已经算过了）
    
然后就可以递推求解了。

code:

```

#include<bits/stdc++.h>
using namespace std;
int n, dp[1010];
signed main(){
	scanf("%d", &n);
	dp[0] = 1;
	dp[1] = dp[2] = 4;
	if(n&1)
	for(int i=3;i<=n;i+=2)
		dp[i] = dp[i-2] +4*(i+1)/2;
	else
	for(int i=4;i<=n;i+=2)
		dp[i] = dp[i-4] +4 * i/2;
	cout<<dp[n];
	return 0;
}
```

---

## 作者：wrzSama (赞：1)

## 题意
找出从平面内原点出发行走 $n$ 步的一个机器人的终点位置数量，它每次移动时可以向上、下、左、右行走一格，但方向需要与上一次的前进方向垂直。
## 思路
若 $n$ 为偶数的话，相当于沿对角线移动了 $n/2$ 步，观察几个样例可发现，它的所有终点就是一个边长为 $n/2+1$ 的正方形，所以终点数就为 $n/2+1$ 的平方。而如果 $n$ 是奇数的话，那么它的所有终点就形成了两个长为 $(n+3)/2$ 宽为 $(n+1)/2$ 的长方形，所以它的终点数就为 $(n+1)/2*(n+3)/2*2$ 。
## 代码
~~~cpp
#include<iostream>
using namespace std;
int main()
{
	int n;
	scanf("%d",&n);
	if(n%2==0)
		printf("%d",((n/2)+1)*((n/2)+1));
	else
		printf("%d",(n+1)/2*(n+3)/2*2);
	return 0;
}
~~~

---

## 作者：L_shadow (赞：0)

## 思路
因为只输入一个数，尝试一下找规律。

令 $sum$ 为最后能走到的点的数量（即答案）。

令 节点为最后能走到的点。

当 $n=1$ 时，$sum=4$。

当 $n=2$ 时，$sum=4$。

当 $n=3$ 时，$sum=12$。

当 $n=4$ 时，$sum=9$。

当 $n=5$ 时，$sum=24$。

比较容易想到分奇数和偶数：

1.偶数（比较简单）：

$n$：$2,4$。

$num$：$4,9$。

可以得到，当 $n$ 为偶数时，$sum=(n\div2+1)^2$。

经过模拟，可以发现，$n=2$ 时，节点形成了一个边长为 $2$ 的正方形；$n=4$ 时，节点形成了一个边长为  $3$ 的正方形。由几何意义得出此式。

2.奇数（比较难）：

$n$：$1,3,5$。

$num$：$4,12,24$。

乍一看，好像 $sum$ 没啥规律。

但是细细一看，好像两者的差值有点规律。

$sum_i-sum_{i-1}$：$4,8,12$。

我们惊奇的发现，每两个相邻的 $sum$ 差值是一个等差数列！

算出来，当 $n$ 为奇数时，$sum=2 \times((n+1)\div2+2)\times((n+1)\div2-1)+4$。

经过模拟，可以发现，$n=1$ 时，节点在原点的上下左右四个方向（分界线为 $y=x$ 和 $y=-x$，易知在分界线上不会有任何节点）各形成了 $1$ 个节点；$n=3$ 时，节点在 $n=1$ 的基础上，多了生成 $2$ 个节点；$n=5$ 时，节点在 $n=3$ 的基础上，多了生成 $3$ 个节点。由几何意义得出此式。

## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
	cin>>n;
	if(!n%2){
		n=n/2+1;//化简一下，不然式子很长
		cout<<n*n;
	}
	else {
		n=(n+1)/2;//同上 
		cout<<2*(n+2)*(n-1)+4;
	}
	return 0;
}
```

---

## 作者：Ant1K (赞：0)

## DP模拟解法
如题，我用动态规划模拟了机器人移动的过程来解决本问题。

由题干可知开始时有 $4$ 个方向可以选择。

但实际上我们只需要求机器人一开始只往两个初始方向移动所带来的部分终点(我选择了 x,y 正半轴以及第一象限上的终点)，然后根据对称性求最终答案即可。


走完第一步后每一步有在原方向上向左走和向右走的两种状态，由此我们可以写出如下内容:

1. 定义 dp 数组(我们求第一象限以及 x,y 正半轴上的状态)

```cpp
dp[i][x][y]
```



$i$ 表示当前朝向，$x,y$ 表示坐标($0 \leq x \leq 501,0 \leq y \leq 501$)

2. 初始化

```cpp
dp[0][1][0]=1
dp[1][0][1]=1
```

3. 递推

```cpp
int dx[4]={1,0,-1,0}
int dy[4]={0,1,0,-1}
int i1=(i+1)%4
int i2=i-1<0?3:i-1
dp[i][x][y]->dp[i1][x+dx[i1]][y+dy[i1]]
dp[i][x][y]->dp[i2][x+dx[i2]][y+dy[i2]]
```

考虑到空间复杂度太大，故使用滚动数组来优化，这里我开了两个数组来实现。

递推结束后，利用对称性得到答案，具体如下:

由于这里我只求了 x,y 正半轴及第一象限的终点，记答案为 $ans$ 那么根据对称性就有:

- 若终点在坐标轴上，则 $ans=ans+2$
- 若终点不在坐标轴上，则 $ans=ans+4$
- 特殊地,若终点在坐标原点上，则 $ans=ans+1$

考虑时间复杂度，$n=1000$ 时,循环体运行次数约为:
$4\times5\times10^2\times5\times10^2\times10^3=10^9$

而时间限制为 $2s$，理论上最多能也只能跑到 $10^9$，因此我通过更新最大的 $x$ 与 $y$ 来降低复杂度使得 $n=1000$ 时能够跑到 $2s$ 以内。



#### 参考代码:

```cpp
#include<bits/stdc++.h>
using namespace std;

int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};

int dp1[4][502][502];
int dp2[4][502][502];
int vis[502][502];
int maxx=1,maxy=1,ans;
int main(){
	int n;
	cin>>n;
	dp1[0][1][0]=1;
	dp1[1][0][1]=1;
	bool flag=1;
	while(--n){
		if(flag){
			//dp1->dp2
			memset(dp2,0,sizeof(dp2));
			for(int x=0;x<=maxx;x++){
				for(int y=0;y<=maxy;y++){
					for(int i=0;i<4;i++){
						if(dp1[i][x][y]==1){
							int i1=(i+1)%4;
							int i2=i-1<0?3:i-1;
							if(x+dx[i1]>=0&&y+dy[i1]>=0){
								dp2[i1][x+dx[i1]][y+dy[i1]]=1;
								maxx=max(x+dx[i1],maxx);
								maxy=max(y+dy[i1],maxy);
							}
							if(x+dx[i2]>=0&&y+dy[i2]>=0){
								dp2[i2][x+dx[i2]][y+dy[i2]]=1;
								maxx=max(x+dx[i2],maxx);
								maxy=max(y+dy[i2],maxy);
							}
						}
					}
				}
			}
		}else{
			//dp2->dp1
			memset(dp1,0,sizeof(dp2));
			for(int x=0;x<=maxx;x++){
				for(int y=0;y<=maxy;y++){
					for(int i=0;i<4;i++){
						if(dp2[i][x][y]==1){
							int i1=(i+1)%4;
							int i2=i-1<0?3:i-1;
							if(x+dx[i1]>=0&&y+dy[i1]>=0){
								dp1[i1][x+dx[i1]][y+dy[i1]]=1;
								maxx=max(x+dx[i1],maxx);
								maxy=max(y+dy[i1],maxy);
							}
							if(x+dx[i2]>=0&&y+dy[i2]>=0){
								dp1[i2][x+dx[i2]][y+dy[i2]]=1;
								maxx=max(x+dx[i2],maxx);
								maxy=max(y+dy[i2],maxy);
							}
						}
					}
				}
			}
		}
		flag=!flag;
	}
	
	if(!flag){
		//统计dp2中内容 
		for(int x=0;x<=maxx;x++){
			for(int y=0;y<=maxy;y++){
				for(int i=0;i<4;i++){
					if(dp2[i][x][y]==1&&vis[x][y]==0){
						vis[x][y]=1;
						if(x>0&&y>0)ans+=4;
						else if(x!=0||y!=0)ans+=2;
						else ans++;
					}
				}
			}
		}
	}else{
		for(int x=0;x<=maxx;x++){
			for(int y=0;y<=maxy;y++){
				for(int i=0;i<4;i++){
					if(dp1[i][x][y]==1&&vis[x][y]==0){
						vis[x][y]=1;
						if(x>0&&y>0)ans+=4;
						else if(x!=0||y!=0)ans+=2;
						else ans++;
					}
				}
			}
		}
	}
	cout<<ans;
	
}

```


---

