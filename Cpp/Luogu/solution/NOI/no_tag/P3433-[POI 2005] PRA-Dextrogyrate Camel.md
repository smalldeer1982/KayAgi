# [POI 2005] PRA-Dextrogyrate Camel

## 题目背景

征求翻译。如果你能提供翻译或者题意简述，请直接发讨论，感谢你的贡献。


## 题目描述

Byteotia consists of $N$ oasis in the desert, no three of which are collinear. Byteasar lives in one of these oasis and moreover he has an acquaintance in every other. Byteasar wants to pay a visit to as many of them as possible. He plans to travel on the back of his camel. The camel is as obstinate as a mule and thus moves in its own peculiar way:

After departure from an oasis it moves along a straight line, until it gets to another oasis.

The camel turns only at oasis, but it turns only right (clockwise) and by an angle from the interval $[0\degree,180\degree]$ (the camel makes only one turn at an oasis, i.e. it will not turn by f.i. $200\degree$ as a result of two subsequent turns by $100\degree$).

The camel doesn't want to follow its own footprints.

Help Byteasar in planning such a route that he will be able to visit as many friends as possible. It should both begin and end in the oasis where Byteasar lives. It has to consist of segments connecting subsequently visited oasis. The route may not pass through any point two times, except the Byteasar's oasis, where the camel turns up twice: at the beginning and the end of the journey.

Byteasar's camel is initially facing a certain oasis and it has to start moving toward it. The direction the camel faces after returning from the journey is of no importance.

TaskWrite a programme that:

reads from the standard input the camel's coordinates and the direction it faces as well as the coordinates of the Byteotian oasis,determines the maximum number of friends Byteasar can pay a visit to while sticking to the presented rules,writes the result to the standard output.

Byteotia大陆由沙漠中的N个绿洲组成，没有三个绿洲是共线的。Byteasar住在其中的一个绿洲中，而他在每个绿洲里都有一个朋♂友。Byteasar想骑羊驼出去旅行一趟，拜访尽量多的朋友。这只羊驼非常固执，它只以它独特的方式前进： 离开一个绿洲后，它只沿一条直线前进，直到它到达另一个绿洲； 它只在绿洲里转弯，但它只朝右转（顺时针），并且角度在[0°,180°]内（它在一个绿洲只做一次转弯，也就是说，它不会转超过180°）；它的路线不会交叉，也就是说，它不会经过任何一个点两次（除了出发点）。 请你帮助Byteasar（的羊驼）设计一条路线，让他能访问尽量多的朋♂友。这条路线必须从Byteasar住的绿洲出发，最后回到原处。Byteasar最初在绿洲1,他的骆驼首先面朝绿洲2


## 说明/提示

样例解释：

 ![](https://cdn.luogu.com.cn/upload/pic/8961.png) 

感谢@Paperback\_Writer 提供翻译


## 样例 #1

### 输入

```
6
1 1
-1 4
0 -1
4 1
0 3
1 4```

### 输出

```
4```

# 题解

## 作者：Hope2075 (赞：7)

这题成为我人生第一道灰题（可能很快就不是了）

先平移坐标系，把起点移到原点，方便讨论

首先看看什么样的路线是合法的

![](https://cdn.luogu.com.cn/upload/pic/55436.png)

似乎有点什么特点

![](https://cdn.luogu.com.cn/upload/pic/55437.png)

![](https://cdn.luogu.com.cn/upload/pic/55438.png)

瞎猜一个结论：除了起点和终点外，，其它部分只要突出就可以

而且可以得到结论：最多转一圈

否则，当回来的时候，会发现起点已经被完全包围了

如果想绕进去，则会把自己困住

所以合法路径的特点：除了起点外，其它角度正确，且只绕一圈

考虑把点按极角排序，2号点极角为0，其它为从2号点顺时针旋转的角度

DP的时候，可以简单地认为从2号点出发，只能向顺时针方向前进

先考虑状态

如果只记录每个点，则不能判断能否继续走

如果再记录从哪个点来？

直接记录是$O(n^2)$状态

转移时，需要枚举所有可能的点对

这样是$O(n^3)$的，还有较多的计算，可能会超时

考虑一下性质：对每个点，将所有能到达它的点恰当地排序，可以满足接下来可以走的点数单调减少

如果不理解，可以看看这个图

![](https://cdn.luogu.com.cn/upload/pic/55441.png)

如果恰当地排序，则当选出的绿色点向下移动时，可以选的红色点向上减少

反过来也一样：选出的红色点向下移动时，可以选的绿色点会向上减少

可以想到单调队列或类似做法

但是这样会比较复杂

所以我就换了一个思路：记录当前点答案不小于$k$时，使得可选点范围最大的源点

这样可以发现DP值满足类似的性质，也就是：可以二分

转移时，枚举之前的点，二分最优答案，判断是否合法即可

另外，因为可能存在答案更差而且可选范围减小的结果，所以每完成一个点，从后向前扫一遍，把不优的DP值改成更优的就行

具体实现

为了防止精度问题，全文用int和叉积

按极角排序：

我的比较函数：先判断是否在基准线两侧

如果是，则可以直接得到结果

否则，两个点的极角差不会大于180度，可以用叉积判断

转移

枚举时判合法，只要这两个点相对位置正确就可以（用叉积判）

二分时，需要判断两条线段间夹角是否合法，也是用的叉积

二分完了要注意：如果一定不合法，要忽略这个答案

![](https://cdn.luogu.com.cn/upload/pic/55444.png)

这种情况下，左下角那一个没有连上线段的点不会有DP值，也就不会更新后面的点

不然就可以开心地WA了

代码：

这里有些区别，请自行理解

包含输出方案功能部分，把```if(0)```改成```if(1)```就行

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1024;
struct vec{
	int x,y;
};
vec operator+(vec a,vec b){
	return (vec){a.x+b.x,a.y+b.y};
}
vec operator-(vec a,vec b){
	return (vec){a.x-b.x,a.y-b.y};
}
int operator*(vec a,vec b){
	return a.x*b.y-a.y*b.x;
}
vec base;
inline int sgn(int num){
	if(num>0)return 1;
	else if(num<0) return -1;
	else return 0;
}
bool operator<(vec a,vec b){
	if(sgn(a*base)*sgn(b*base)==-1){
		return a*base>0;
	}else{
		return a*b<0;
	}
}
int n;
vec list[N];
int dp[N][N];
vec F,P,C;
int l,r,mid;
int road[N],cnt;
int maxn,maxid;
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	cin>>list[n].x>>list[n].y;
	for(int i=1;i<n;i++){
		cin>>list[i].x>>list[i].y;
		list[i]=list[i]-list[n];
	}
	list[n].x=list[n].y=0;
	base=list[1];
	sort(list+2,list+n);
	dp[1][0]=dp[1][1]=n;
	for(int i=2;i<=n;i++){
		C=list[i];
		for(int j=1;j<i;j++){
			P=list[j];
			if(P*C>0)continue;
			l=0,r=n+1;
			while(l!=r){
				mid=((l+r)>>1);
				if(dp[j][mid]==0){
					r=mid;
					continue;
				}
				F=list[dp[j][mid]];
				if((P-F)*(C-P)<=0){
					l=mid+1;
					continue;
				}else{
					r=mid;
				}
			}
			if(dp[j][l-1]==0)continue;
			//这里一定要判，否则会产生不合法转移
			if(maxn<l){
				maxn=l;
				maxid=i;
			}
			if(dp[i][l]==0){
				dp[i][l]=j;
			}else{
				F=list[dp[i][l]];
				if((C-P)*(C-F)<0){
					dp[i][l]=j;
				}
			}
		}
		for(int j=n;j>=0;j--){
			if(dp[i][j]==0)dp[i][j]=dp[i][j+1];
			else{
				if(dp[i][j+1]==0)continue;
				F=list[dp[i][j]];
				P=list[dp[i][j+1]];
				if((C-P)*(C-F)<0){
					dp[i][j]=dp[i][j+1];
				}
			}
		}
	}
	cout<<maxn-1<<endl;
	road[cnt++]=n;
	for(int p=dp[n][maxn],t=maxn;p!=n;--t,p=dp[p][t]){
		road[cnt++]=p;
	}
	if(0){
		for(int i=cnt-1;i>=0;i--){
			cout<<road[i]<<" ";
		}
	}
}
```

---

## 作者：Dallda_Mavericks (赞：2)

首先平移坐标系，使 $1$ 号点为原点。

考虑什么样的路径是合法的：（此处借用了这位[大佬题解](https://www.luogu.com.cn/blog/ima/solution-p3433)中的图片）

![](https://cdn.luogu.com.cn/upload/pic/55441.png)

图中的蓝色点为 $1$ 号点，红色与绿色为其他点，当选择了某个红色点时，其上方的所有红色点都无法再走到了；同样的，选择了某个绿色点时，其下方的所有绿色点也无法走到了。

因此，将 $1$ 号点外的点极角排序，那么最优选择一定时从 $2$ 号点开始沿顺时针方向走（此时合法的目标点一定再顺时针方向）。因此可以极角排序后，将 $2$ 号点排在首位，其他点按顺时针方向依次加入。设 $dp_{i,j}$ 表示现在走到了第 $i$ 个点，上一个走到的点位 $j$ 号点时的最长路径。然后 $O(n)$ 枚举下一个转移点并判断能否到达。状态是 $O(n^2)$ 的，因此总复杂度位 $O(n^3)$。

考虑优化，将 $dp_{i,j}$ 改为走到了第 $i$ 个点，经过了 $\ge j$ 个点时能使得可选择后继范围最大的前驱。那么转移时，枚举当前点 $i$ 以及前驱 $j$，即可二分找到能够从 $j$ 到达 $i$ 的前提下，经过的路径最大是多少，如果二分出的答案是 $k$，就可以用 $dp_{j,k}$ 更新 $dp_{i,k+1}$。更新完之后，再对与每个 $i$，将 $j$ 从大到小扫一遍，用  $dp_{i,j}$ 更新 $dp_{i,j-1}$ 选择可选后继范围更大的一个前驱。判断谁的可选范围最大可以使用叉积完成。

最终复杂度优化到 $O(n^2\operatorname{log}n)$。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2010;
const double pi=acos(-1.0);
int n,pos[N],dp[N][N];
double ang[N];
struct pt{
	int x,y;
	pt(int _x=0,int _y=0){x=_x;y=_y;}
}p[N];
inline ll operator ^(const pt& a,const pt& b){return 1ll*a.x*b.y-1ll*a.y*b.x;}
inline pt operator -(const pt& a,const pt& b){return pt(a.x-b.x,a.y-b.y);}
inline bool cmp(int x,int y){return ang[x]<ang[y];}
inline bool check(int i,int j,int k){return ((p[pos[j]]-p[pos[i]])^(p[pos[k]]-p[pos[j]]))<0;}
inline void upd(int pos,int &x,int y){
	if(x==-1){x=y;return ;}
	(check(pos,y,x))&&(x=y);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d%d",&p[i].x,&p[i].y);
	for(int i=2;i<=n;++i) p[i]=p[i]-p[1];p[1]=p[1]-p[1];
	for(int i=0;i<n;++i) pos[i]=i+1,ang[i+1]=atan2(p[i+1].y,p[i+1].x);
	double tmp=ang[2];
	for(int i=2;i<=n;++i){
		ang[i]=tmp-ang[i];
		ang[i]=fmod(ang[i]+6*pi,2*pi);
	}
	sort(pos+1,pos+n,cmp);
	memset(dp,-1,sizeof(dp));
	dp[1][1]=0;
	int ans=1;
	for(int i=2;i<n;++i){
		for(int j=1;j<i;++j){
			if(check(j,i,0)){
				int l=1,r=j,ret=-1;
				while(l<=r){
					int mid=(l+r)>>1;
					if((~dp[j][mid])&&check(dp[j][mid],j,i)) l=mid+1,ret=mid;
					else r=mid-1;
				}
				if(~ret) upd(i,dp[i][ret+1],j),ans=max(ans,ret+1);
			}
		}
		for(int j=i-1;~j;--j) if(~dp[i][j+1]) upd(i,dp[i][j],dp[i][j+1]);
	}
	printf("%d\n",ans);
	return 0;
}

```


---

