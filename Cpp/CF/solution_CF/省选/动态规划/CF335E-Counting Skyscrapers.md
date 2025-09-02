# Counting Skyscrapers

## 题目描述

A number of skyscrapers have been built in a line. The number of skyscrapers was chosen uniformly at random between $ 2 $ and $ 314! $ (314 factorial, a very large number). The height of each skyscraper was chosen randomly and independently, with height $ i $ having probability $ 2^{-i} $ for all positive integers $ i $ . The floors of a skyscraper with height $ i $ are numbered $ 0 $ through $ i-1 $ .

To speed up transit times, a number of zip lines were installed between skyscrapers. Specifically, there is a zip line connecting the $ i $ -th floor of one skyscraper with the $ i $ -th floor of another skyscraper if and only if there are no skyscrapers between them that have an $ i $ -th floor.

Alice and Bob decide to count the number of skyscrapers.

Alice is thorough, and wants to know exactly how many skyscrapers there are. She begins at the leftmost skyscraper, with a counter at 1. She then moves to the right, one skyscraper at a time, adding 1 to her counter each time she moves. She continues until she reaches the rightmost skyscraper.

Bob is impatient, and wants to finish as fast as possible. He begins at the leftmost skyscraper, with a counter at 1. He moves from building to building using zip lines. At each stage Bob uses the highest available zip line to the right, but ignores floors with a height greater than $ h $ due to fear of heights. When Bob uses a zip line, he travels too fast to count how many skyscrapers he passed. Instead, he just adds $ 2^{i} $ to his counter, where $ i $ is the number of the floor he's currently on. He continues until he reaches the rightmost skyscraper.

Consider the following example. There are $ 6 $ buildings, with heights $ 1 $ , $ 4 $ , $ 3 $ , $ 4 $ , $ 1 $ , $ 2 $ from left to right, and $ h=2 $ . Alice begins with her counter at $ 1 $ and then adds $ 1 $ five times for a result of $ 6 $ . Bob begins with his counter at $ 1 $ , then he adds $ 1 $ , $ 4 $ , $ 4 $ , and $ 2 $ , in order, for a result of $ 12 $ . Note that Bob ignores the highest zip line because of his fear of heights ( $ h=2 $ ).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF335E/9d367cf028f39a08adbadadae64bb921b844f30a.png)Bob's counter is at the top of the image, and Alice's counter at the bottom. All zip lines are shown. Bob's path is shown by the green dashed line and Alice's by the pink dashed line. The floors of the skyscrapers are numbered, and the zip lines Bob uses are marked with the amount he adds to his counter.

When Alice and Bob reach the right-most skyscraper, they compare counters. You will be given either the value of Alice's counter or the value of Bob's counter, and must compute the expected value of the other's counter.

## 说明/提示

In the first example, Bob's counter has a 62.5% chance of being 3, a 25% chance of being 4, and a 12.5% chance of being 5.

## 样例 #1

### 输入

```
Alice
3 1
```

### 输出

```
3.500000000
```

## 样例 #2

### 输入

```
Bob
2 30
```

### 输出

```
2
```

## 样例 #3

### 输入

```
Alice
2572 10
```

### 输出

```
3439.031415943
```

# 题解

## 作者：lzqy_ (赞：3)

提供一种最劣解第一且巨大难写的做法（

# Bob

显然真正的楼量可以达到 $314!$，是没办法直接做的，再加上唯一方案的样例，可以猜测有简单的结论。

考虑当楼高度为 $k(k<h)$ 时，每种高度对答案的贡献为 $2^{k-1}\times 2^{-k}$，即 $\frac{1}{2}$，当楼高度为 $k(k \ge h)$ 时，每种高度对答案的贡献和为 $2^k\times 2^{-k}$，即 $1$。显然贡献都与 $h$ 无关，也就是结论只和 $n$ 有关，随便推几组数据再加上样例，容易猜出答案即为 $n$。

**Code：**

```cpp
void Sub2(){
	scanf("%d%d",&n,&h);
	printf("%d\n",n);
}
```

# Alice

观察到高度 $\ge h$ 的楼本质上是一致的，可以钦定楼的高度区间为 $[1,h]$（高度为 $h$ 的概率变为 $2^{1-h}$）。

设 $k$ 号楼的高度最高，则 Bob 一定会经过 $k$ 号楼。容易发现，在 $k$ 号楼前，Bob经过的楼的高度**单调不降**，$k$ 号楼后**单调不升**。

注意，为了防止重复计算，若高度相同，钦定靠前的最高。

然后就可以转移了。

设 $f_{i,j,k,0/1}$ 表示转移完第 $i$ 栋楼，最后一个经过的 $x$ 号楼的高度为 $j$，$[x+1,i]$ 中最大高度为 $k$，是/否 经过最高的楼的**期望**。

设 $g_{i,j,k,0/1}$ 表示转移完第 $i$ 栋楼，最后一个经过的 $x$ 号楼的高度为 $j$，$[x+1,i]$ 中最大高度为 $k$，是/否 经过最高的楼的**概率**。

DP的时候用刷表法，枚举第 $i$ 栋楼的高度转移即可。时间复杂度 $O(nh^3)$ 要卡亿点常并滚动数组。

**Code：**

```cpp
const double eps=1e-15;
const int maxn=30010;
const int maxh=35;
int n,h;
double g[2][maxh][maxh][2];
double f[2][maxh][maxh][2];
double V[maxh],S[maxh];
void Sub1(){
	scanf("%d%d",&n,&h);
	for(int i=0;i<h;i++){
		V[i]=1.0/(1<<i+1),S[i]=(1-1.0/(1<<i));
		f[1][i][0][0]=V[i]+0.5,g[1][i][0][0]=V[i];
	} 
	if(h) V[h]=V[h-1],S[h]=(1-1.0/(1<<h));
    else V[h]=1;
	for(int i=0;i<=h;i++) f[1][i][0][1]=V[i],g[1][i][0][1]=V[i];
	//以上是初始化
    double tmp1,tmp2,tmp;
	for(int i=1,ii=1,iii=0;i<n;i++,ii^=1,iii^=1){
		memset(f[iii],0,sizeof(f[iii]));
		memset(g[iii],0,sizeof(g[iii]));
      	//注意,为了处理当j=i时(Bob经过当前楼)k也为0的情况
      	//这里枚举的k,u都加了1(j=0时k才为0)
      
      	//为了卡常,转移的式子很丑,但本质是一样的
		for(int j=0;j<=h;j++)
			for(int k=0;k<=j;k++){
				tmp1=f[ii][j][k][0],tmp2=g[ii][j][k][0],tmp=tmp2/2;
				if(tmp1>eps){
					//u<=k
					f[iii][j][k][0]+=tmp1*S[k];
					g[iii][j][k][0]+=tmp2*S[k];
					tmp1*=V[k],tmp2*=V[k];
					//--------
				 	for(int u=k+1;u<=h+1;u++){
						if(u-1>=j) f[iii][u-1][0][0]+=tmp1+tmp,g[iii][u-1][0][0]+=tmp2;
						else f[iii][j][u][0]+=tmp1,g[iii][j][u][0]+=tmp2;
						if(u-1>j) f[iii][u-1][0][1]+=tmp1,g[iii][u-1][0][1]+=tmp2;
						if(u<h) tmp1/=2,tmp2/=2;
					}
					f[iii][h][0][0]+=tmp;
				}
				tmp1=f[ii][j][k][1],tmp2=g[ii][j][k][1],tmp=tmp2/2;
				if(tmp1>eps){
					//u<=k
					f[iii][j][k][1]+=tmp1*S[k];
					g[iii][j][k][1]+=tmp2*S[k];
					tmp1*=V[k],tmp2*=V[k];
					//--------
                  for(int u=k+1;u<=j+1;u++){
						f[iii][u-1][0][1]+=tmp1+tmp,g[iii][u-1][0][1]+=tmp2;
						if(u-1<j) f[iii][j][u][1]+=tmp1,g[iii][j][u][1]+=tmp2;
						if(u<h) tmp1/=2,tmp2/=2; 
					}
					if(j==h) f[iii][h][0][1]+=tmp;
				} 
			}
	}
	double ans=0;
	for(int i=0;i<=h;i++)
		ans+=f[n&1][i][0][1];
	printf("%.9lf",ans);
}
```

### 能不能更快？

上述期望DP本质上是分了 $[1,k],[k+1,j][j+1,h]$ 三个区间分别转移行和列，考虑将决策点放到线段树上，则问题转换为了线段树的区间修改/单点查询，时间复杂度 $O(nh^2\log h)$。

但由于要对 $f,g$、是否经过最高楼、行或列分类讨论，所以要开 $8nh$ 棵线段树，本地极限数据要跑 $10s+$，没有实质效果。

### 能不能更快？

观察到转移方程与 $n$ 无关，考虑构造 $h\times h$ 的矩阵，跑矩阵快速幂即可，时间复杂度 $O(h^3logn)$，可以通过本题，时间与空间上都更优。

---

