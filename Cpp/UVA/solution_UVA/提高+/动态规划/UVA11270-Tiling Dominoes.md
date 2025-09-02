# Tiling Dominoes

## 题目描述

题目大意

给定一个m×n的矩形网格，用1×2多米诺骨牌完全平铺。 请注意，即使一个平铺的旋转与另一个平铺相匹配，它们仍算作不同的平铺。 下面显示了一个平铺示例。

## 样例 #1

### 输入

```
2 10
4 10
8 8```

### 输出

```
89
18061
12988816```

# 题解

## 作者：Clu3ter (赞：48)

[![](https://cdn.luogu.com.cn/upload/image_hosting/c988ay6n.png)](https://www.luogu.com.cn/problem/UVA11270)

------------

看到了很多dalao发的题解，但是理解得不是特别清楚，研究了一下午终于懂了(:D)

这里我们**逐格**进行DP。但记录的状态是各行内的**轮廓线**上格子的覆盖情况。

$f[i][s]$表示第i行的轮廓线状态为s时的方案数。

轮廓线……是啥？

请看下图

![](https://cdn.luogu.com.cn/upload/image_hosting/4bwrk3uw.png)

图中绿色格子为$\color{LimeGreen}\text{当前}$推到的格子。那条金黄色亮闪闪的线就是$\color{Goldenrod}\text{轮廓线}$。

我们用格子所在的列数 来给轮廓线上方的格子（白色格子）编号。编完号后即可二进制**状态压缩**，用1表示被覆盖，用0表示未被覆盖。

如图：
（由于数字的一般为从高到低，便于与图示对应我们这里采用“逆写法”）
![](https://cdn.luogu.com.cn/upload/image_hosting/1xjpbszv.png)

按照题目的设定，要 _覆盖整个网格_ ，**轮廓线之上的所有格子都应该是1**，**但**！**是**！由于考虑到有**竖放**的骨牌，我们使与轮廓线相邻的这些方格（白色）中能够存在0，起到一个类似“缓冲？”的作用。$\color{red}\text{<重点1>}$（具体的意思可以看下文）

好，状态表示完毕，接下来我们来看转移的方法

显然，对于当前格（绿），只有3种决策：

>1.竖放（向上）
>
>2.横放（向左）
>
>3.留空

**设白色格内的状态为$k$，转移后为$k'$**

**设绿色格所在列数为$j$**

**仅第$x$位为1的状态为$p[x]\quad$** (即1<<(x-1))

![](https://cdn.luogu.com.cn/upload/image_hosting/es7g8u60.png)

我们来分类讨论：

### 1.竖放：

什么时候需要竖放呢？$\quad$应该观察当前格**上方**的格子状态。

当前格上方的状态用数据表示即为$k \& p[j]$

- 如果当前格上方为**0**,那么**必须放一个竖放的骨牌**

为什么呢？因为上方白色格子的内容是**已经确定**的，也就是说，此时不放一块向上的骨牌，那么上方这个格子就会**永远无法被覆盖**,这与题目要求的**覆盖整个网格**不符。因此必须放一个竖向骨牌$\color{red}\text{<重点2>}$

- 那么当前格上方为**1**,那么你肯定**无法**放一个向上的骨牌。

**综上**，若上方为0则放置竖向骨牌(!(k&p[j]))

同时，当前格也**不能位于第一行**。(j>1)

接下来我们来整个转移方程出来。

上图


![UIzAht.gif](https://s1.ax1x.com/2020/07/21/UIzAht.gif)

在经过转移后，我们的动规推进了一格，**k的第j位在推进前后，从当前格的上一个格子，变成了当前格本身(观察左下角的格子排列)**(理解这一点很重要(至少对于我自己来说))$\color{red}\text{<重点3>}$

即k的第j位 从0变成了1，而原来的上方格子则不用再考虑了

>#或许你可以停下来思考一下……

由于求的是总方案数，因此转移时采用**加和**，初始化为0。

因此，状态转移方程如下:
$${\text{if}((i>1)\,  \&\&\,!(k\&p[j]))}\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad$$
$$ k'=k|p[j]$$
$$ f[i][k']+=f[i-1][k] $$


### 2.横放：

现在有了第一种的经验，我们可以依样画葫芦，轻松地推出其他的情况

>#试着自己推一推？

情况1中我们已经得知，**如果上方的格子未被覆盖，则必定要放一个竖向骨牌将其填满**(重点2处)。即下文条件2.

横放的条件是
	
1. 左侧格子没有被覆盖(!(k&q[j-1]))
2. 上方的格子已经被覆盖(k&q[j])
3. 不在第一列(j>1)

而具体的转移方法 则是

横放后$k'$的第$j$位(本身)与第$j-1$位(左侧格子)都应该是**1**。而由条件2可知原k的第$j$位原来就是**1**，故只需要将左侧格子改为1。

状态转移方程：
$${\text{if((j>1) \&\& !(k\&q[j-1]) \&\& (k\&q[j]))}}\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad$$
$$ k'=k|p[j-1]$$
$$ f[i][k']+=f[i-1][k] $$

### 3.留空：

同情况2条件2，只有在上方格子被覆盖的情况下，才可以进行除了竖放以外的操作，而对于留空，则没有什么要求。

则条件是：
	
1. 上方的格子已经被覆盖(k&q[j])

转移方法则是$k'$的第$j$位改为0；

$${\text{if(k\&q[j])}}\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad$$
$$ k'=k\; xor\; p[j-1]$$
$$ f[i][k']+=f[i-1][k] $$

>#思考 留空 与 竖放 的关系

#### 可以结合下面这张图来理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/kn2k4u5o.png)

初始化为f[0][(1<<m)-1]=1;
（把第0行填满）

最终答案为f[d][(1<<m)-1];
(最后一行填满)

### 一些优化

- 由于每一行的状态仅有上一行推出，且最终只取最后一行，可以使用2行的**滚动数组**优化；

- 预处理p数组(即1<<(i-1));

- 防止**状态压缩**超出整数范围，始终保证n>m,使m≤10；

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m;
long long int f[2][(1<<10)];
int p[20];

int main(){
	for(int i=1;i<=15;i++){
		p[i]=1<<(i-1);
	}//预处理 
	while(~scanf("%d %d",&n,&m))
    {
    	if(n<m)	swap(n,m);//交换，使m不大于10 
		int d=0;//滚动数组下标 
		memset(f,0,sizeof(f));//清空 
		f[0][(1<<m)-1]=1;//初始化 
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				d^=1;//d在0与1之间滚动 
				memset(f[d],0,sizeof(f[d]));//清空 
				for(int k=0;k<(1<<m);k++){
					
					if(k&p[j])
						f[d][k^p[j]]+=f[d^1][k];//留空
					
					if((j>1) && !(k&p[j-1]) && (k&p[j]))//横放
						f[d][k|p[j-1]]+=f[d^1][k];
					
					if((i>1) && !(k&p[j]))
						f[d][k|p[j]]+=f[d^1][k];//竖放 
					
				}
			}
		}
		cout<<f[d][(1<<m)-1]<<endl;//最终输出最后一行也填满的情况 
	}

} 
```


---

## 作者：Red_Lantern (赞：10)

这是一篇暴力状压 dp 的题解，想必学过状压的人都做过一道叫 互不侵犯 的经典题，这题就和那题类似。话说这题好像在今年 WC 上插头 dp 的例题讲过吧，原题应该叫“蒙德里安的梦想”。

我们一般都是把较小的元素状压，首先看到 $n×m<100$ 范围，就可以发现 $n,m$ 中较小的那个肯定不超过 $10$ ，那只要判断一下再交换行列就行了。而且没有方案可以铺满的话， $n$ 和 $m$ 一定都是奇数，因为铺在棋盘上是 $1×2$ 的长方形，可以列方程证明。

设 $f[i][S]$ 为第 $i$ 行列的状态为 $S$ 的方案数，如果是行数更小那就交换 $n,m$ 。这个方案数其实就是所有竖放的方块的方案数，因为竖放的方块全部确定了，横放的就必须去填满剩下的空格，那就只管竖放的就好了，二进制位为 $1$ 表示在第 $i$ 行的这一列放了一个竖的方块。比如 $S=9_{(1001)}$ 时，就表示第 $i$ 行的方块状态是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/2d6lit5i.png)

则最后 $ans←f[n][0]$ ，表示第 $n$ 行没有竖放的方块（不然就会有方格凸出到 $n+1$ 行），初始化 $f[0][0]←1$ 。然后可以根据上面的状态推出 $f[i][k]←f[i][k]+f[i-1][j]$ ，其中 $k$ 为 $i$ 行的状态， $j$ 为 $i-1$ 行的状态。

但显然这个东西是不能直接转移的，要保证这个转移合法，首先要确保 $i-1$ 行和 $i$ 行 都是合法的，也就是 $j\&k=0$ ，表示如果 $i-1$ 行的某列放了个竖的，那 $i$ 行的这列就不能再放个竖的；其次要使这个 $k$ 和 $j$ 两个状态放在 $i$ 和 $i-1$ 行上面之后，仍然可以通过横放把图填满，读者在这里可以自己思考或画图一下，什么情况会使之后 **没有任何横放的方法** 可以 **填满** 现在竖放完之和 **剩下的空** 。

结论很好想，其实只要某一行竖的放完了之后，这行还剩下 **奇数个连续的空**，就一定不能只靠横放 $1×2$ 的长方形把它填满。所以可以先处理出 $0...2^m-1$ 所有状态是否有连续奇数个 $0$ ，表示这一行填了若干竖方块后能否用横的去填满，因为然后再判断 $j|k$ 后的结果是否有奇数个连续的空，就可以转移了。

UOJ 的数据也不水，不仅要开 long long ，而且我发现一开始裸 dp 超时了，但是我把 $n,m$ 所有数据都跑了一遍发现只跑了 800ms ，于是就想到了记忆化已经做过的答案（其实还可以打表），最后跑了 720ms ，在最优解里排倒数。。。

代码：
```cpp
#include<bits/stdc++.h>
#define ulol unsigned long long
#define rep(x,l,r) for (register int x=l; x<=r; x++)
using namespace std;
bool b[2100]; // b 表示该状态是否合法，合法为 0 ，不合法为 1 
int n,m;
ulol f[106][2100],a[106][106]; // f 表示方案数，a 是记忆化数组 
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	memset(a,-1,sizeof(a));
	while (cin>>n>>m)
	{
		if (n<m) swap(n,m);
		if (a[n][m]!=-1){ cout<<a[n][m]<<endl; continue;}
		if ((n&1)&&(m&1)||n==0||m==0){ cout<<0<<endl; continue;}
		memset(f,0,sizeof(f)),memset(b,0,sizeof(b));
		f[0][0]=1ll;
		rep(i,0,(1<<m)-1)
		{
			int cnt=0; // cnt 统计连续的 0 的个数 
			rep(j,0,m-1)
			if (!(1<<j&i)) cnt++; // 如果 i 的第 j 位为 0
			else {if (cnt&1) b[i]=1; cnt=0;}
			if ((cnt&1)) b[i]=1;
		}
		rep(i,1,n) rep(j,0,(1<<m)-1)
		rep(k,0,(1<<m)-1)
		if (!b[j|k]&&!(j&k)) f[i][k]+=f[i-1][j];
		a[n][m]=f[n][0]; //记忆化操作 
		cout<<f[n][0]<<endl;
	}
	return 0;
}
```

---

## 作者：star_fish (赞：6)

# [铺放骨牌](https://www.luogu.com.cn/problem/UVA11270)




###### 我的第一篇题解捏
这题可以用状压 dp 解决。

分析状态，我们将含有**竖着的骨牌的脑袋**的格子视为 ```1```，其余格子皆当做 ```0```（或者说根据当前格子是否能对下一状态施加影响定为 ```1``` 或 ```0```）。

由于旋转后相同的平铺属于不同的平铺，因此为了节省空间与时间，我们通过交换 $n$ 和 $m$ 的值使列小于行。

状压 dp 通过枚举当前状态（状态 $1$ ）和上一行的状态（状态 $0$），若状态 $1$ 可以从状态 $0$ 转化，则用状态 $0$ 更新状态 $1$。 

对于状态是否能合法地转换：

首先，在同一列上，若状态 $0$ 为 ```1```，显然状态 1 不能为 ```1```。这个判断可以通过 ```&``` 运算实现。

其次，横着的骨牌占了两个格子，因此**记录横着的骨牌的 ```0```** 是成对出现的。

但是我们怎么判断一个 `0` 是不是记录横着的骨牌呢？

请看注释：

```cpp 
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 11
int f[150][1<<N];
int n,m,t;
bool check(int s,int t){//判断能否合法转化
	int sum0=0,sum1=0;//记录0和1的数量 
	while(s||t){
		if(s%2==1||t%2==1){
			//无论当前位置放了竖骨牌的屁股还是脑袋,都不能将这个位置当做正常的0。
			//不妨在计数和断点时把这个位置当做1来算 
			if(sum0%2==1)return 0;
			sum1++;
		}
		else sum0++;
		s/=2;t/=2;
	}
	sum0+=m-sum1-sum0;//只剩0了。剩下的0全是连着的,且不再受到"1"的影响 
	if(sum0%2) return 0;
	return 1;
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	while(cin>>n>>m){
		if(m>n) swap(n,m);//使列小于行
		for(int t=0;t<(1<<m);t++){//初始化,显然第0行不会影响第1行,因此第0行状态为(0) 
			f[1][t]=(check(t,0)); 
			f[2][t]=0;
		}	
		for(int i=2;i<=n;i++)//在下面枚举状态1和状态0 
			for(int t=0;t<(1<<m);t++){
				f[i+1][t]=0;
				for(int s=0;s<(1<<m);s++){
					if((s&t)||!check(s,t)) continue;
					f[i][s]+=f[i-1][t];
				}
			}
		cout<<f[n][0]<<'\n';//最后一行的状态肯定都是0 因为放不下脑袋了 
	} 
	return 0;
}
```

---

## 作者：cff_0102 (赞：4)

状态压缩的典型例题了。

设 $dp_{h,w,S}$ 为在填充高度为 $h$ 的矩形且剩余宽度为 $w$，最后一列被填充的状态为 $S$（用 $h$ 位二进制数表示）时，填多米诺的方案。

用记忆化搜索，代码更容易理解。

dfs 的时候枚举最后一列没被填的空的子集，选择这几个空放一个横着的多米诺，然后判断剩下的状态能不能全部填竖着的多米诺。如果可以就继续搜索左边一列，状态就是这一列被横着填的格子（显然）。

所以 $dp$ 的那个 $h$ 实际上是不会改变的，只不过对每个 $h$ 存一下的话，以后碰到一样 $h$ 的询问就可以直接把答案拿出来了。

记得开 `long long`，另外如果 $h>w$ 要把这两个数交换一下，这样就保证 $h\le10$，`dp` 数组不用开太大。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int dp[15][105][5000];
bool check(int h,int S){//这个状态，要全部在空位里面填竖着的多米诺，是否合法 
	bool a[h+2];
	for(int i=1;i<=h;i++){
		a[i]=(S&(1<<(i-1)));
	}
	a[h+1]=1;
	for(int i=1;i<=h;i++){
		if(!a[i]){
			if(a[i+1]){
				//出现单个空位，不合法
				return 0; 
			}else{
				//填上双个空位
				a[i]=a[i+1]=1; 
			}
		}
	}
	return 1;
}
int dfs(int h,int w,int S){//高度，剩余宽度，最右侧一列状态 
	if(dp[h][w][S]!=-1)return dp[h][w][S];
	if(w==1)return dp[h][w][S]=check(h,S);
	//枚举这一列所有填的方案
	//先填横的，填完后看竖着的能不能填进来，如果不能则状态不合法
	int ans=0;
	for(int i=0;i<(1<<h);i++)if(!(i&S)){
		if(check(h,(S|i))){
			ans+=dfs(h,w-1,i);//左边被占用的其实就是这一列横着填的 
		}
	}
	return dp[h][w][S]=ans;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int h,w;
	memset(dp,-1,sizeof(dp));
	while(cin>>h>>w){
        if(h>w)swap(h,w);
		cout<<dfs(h,w,0)<<endl;
	}
	return 0;
}
```

---

## 作者：da32s1da (赞：4)

考虑轮廓线DP。

对于一个格子来说，有4种情况。

1. 上面没有格子，左面没有格子。这种情况必须**向上填**。
2. 上面没有格子，左边有格子。同上。
3. 上面有格子，左面没有格子。可以向左面填，也可以不填。
4. 上面有格子，左面有格子。必须**不填**。

这里的二进制数表示的是**该行到此格子的前一个及此格子的上一个格子到上一行结束的填充方案**。

~~不用记忆化啊~~

```
#include<cstdio>
#include<cstring>
typedef long long LL;
int n,m,opt,fal,_2[14];
LL f[2][2100];
int main(){
	_2[0]=1;
	for(int i=1;i<14;i++)_2[i]=_2[i-1]<<1;
	while(scanf("%d%d",&n,&m)!=EOF){
		if(n*m%2==1){
			puts("0");
			continue;
		}
		memset(f,0,sizeof(f));
		if(n<m)opt=n,n=m,m=opt;
		opt=0;
		fal=(1<<m)-1;
		f[0][fal]=1;
		for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			opt^=1;
			memset(f[opt],0,sizeof(f[opt]));
			for(int k=0;k<=fal;k++){
				if(!(k&_2[j]))f[opt][k|_2[j]]+=f[opt^1][k];
                //上面没格子，必须填上面
				if(j&&(k&_2[j])&&!(k&_2[j-1]))f[opt][k|_2[j-1]]+=f[opt^1][k];
                //上面有格子，左面没有，可以填左边
				if(k&_2[j])f[opt][k^_2[j]]+=f[opt^1][k];
				//上面有格子，左边没有，可以不填
                //上面有格子，左面有，必须不填
                //这两种情况用一种转移
            }
		}
		printf("%lld\n",f[opt][fal]);
	}
}
```

---

## 作者：happyZYM (赞：4)

# 记忆化动态规划 ~~什么鬼~~
这题是一道典型的插头DP（轮廓线动态规划），由于如果不记录轮廓线无法转移且m和n中至少有一个不超过10，所以可以用二进制编码将轮廓线计入状态，详细推导过程见《算法竞赛入门经典训练指南》P384。

这是裸的插头DP：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=15;
int n,m,pos;
LL d[2][1<<maxn];
inline void update(int a,int b) { if(b&(1<<m)) d[pos][b^(1<<m)]+=d[pos^1][a]; }
int main()
{
#ifdef local
	freopen("pro.in","r",stdin);
#endif
	while(scanf("%d%d",&n,&m)==2)
	{
		if(m>n) swap(n,m);
		memset(d,0,sizeof(d));
		pos=0;
		d[0][(1<<m)-1]=1;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
			{
				pos^=1;
				memset(d[pos],0,sizeof(d[pos]));
				for(int k=0;k<(1<<m);k++)
				{
					update(k,k<<1);
					if(i&&!(k&(1<<(m-1)))) update(k,(k<<1)^(1<<m)^1);
					if(j&&!(k&1)) update(k,(k<<1)^3);
				}
			}
		printf("%lld\n",d[pos][(1<<m)-1]);
	}
	return 0;
}
```
TLE4次后一怒之下交了个表：
```cpp
#include<cstdio>
long long res[105][105];
int main()
{
#ifdef local
	freopen("pro.in","r",stdin);
#endif
	res[1][1]=res[1][1]=0ll;
	res[1][2]=res[2][1]=1ll;
	res[1][3]=res[3][1]=0ll;
	res[1][4]=res[4][1]=1ll;
	res[1][5]=res[5][1]=0ll;
	res[1][6]=res[6][1]=1ll;
	res[1][7]=res[7][1]=0ll;
	res[1][8]=res[8][1]=1ll;
	res[1][9]=res[9][1]=0ll;
	res[1][10]=res[10][1]=1ll;
	res[1][11]=res[11][1]=0ll;
	res[1][12]=res[12][1]=1ll;
	res[1][13]=res[13][1]=0ll;
	res[1][14]=res[14][1]=1ll;
	res[1][15]=res[15][1]=0ll;
	res[1][16]=res[16][1]=1ll;
	res[1][17]=res[17][1]=0ll;
	res[1][18]=res[18][1]=1ll;
	res[1][19]=res[19][1]=0ll;
	res[1][20]=res[20][1]=1ll;
	res[1][21]=res[21][1]=0ll;
	res[1][22]=res[22][1]=1ll;
	res[1][23]=res[23][1]=0ll;
	res[1][24]=res[24][1]=1ll;
	res[1][25]=res[25][1]=0ll;
	res[1][26]=res[26][1]=1ll;
	res[1][27]=res[27][1]=0ll;
	res[1][28]=res[28][1]=1ll;
	res[1][29]=res[29][1]=0ll;
	res[1][30]=res[30][1]=1ll;
	res[1][31]=res[31][1]=0ll;
	res[1][32]=res[32][1]=1ll;
	res[1][33]=res[33][1]=0ll;
	res[1][34]=res[34][1]=1ll;
	res[1][35]=res[35][1]=0ll;
	res[1][36]=res[36][1]=1ll;
	res[1][37]=res[37][1]=0ll;
	res[1][38]=res[38][1]=1ll;
	res[1][39]=res[39][1]=0ll;
	res[1][40]=res[40][1]=1ll;
	res[1][41]=res[41][1]=0ll;
	res[1][42]=res[42][1]=1ll;
	res[1][43]=res[43][1]=0ll;
	res[1][44]=res[44][1]=1ll;
	res[1][45]=res[45][1]=0ll;
	res[1][46]=res[46][1]=1ll;
	res[1][47]=res[47][1]=0ll;
	res[1][48]=res[48][1]=1ll;
	res[1][49]=res[49][1]=0ll;
	res[1][50]=res[50][1]=1ll;
	res[1][51]=res[51][1]=0ll;
	res[1][52]=res[52][1]=1ll;
	res[1][53]=res[53][1]=0ll;
	res[1][54]=res[54][1]=1ll;
	res[1][55]=res[55][1]=0ll;
	res[1][56]=res[56][1]=1ll;
	res[1][57]=res[57][1]=0ll;
	res[1][58]=res[58][1]=1ll;
	res[1][59]=res[59][1]=0ll;
	res[1][60]=res[60][1]=1ll;
	res[1][61]=res[61][1]=0ll;
	res[1][62]=res[62][1]=1ll;
	res[1][63]=res[63][1]=0ll;
	res[1][64]=res[64][1]=1ll;
	res[1][65]=res[65][1]=0ll;
	res[1][66]=res[66][1]=1ll;
	res[1][67]=res[67][1]=0ll;
	res[1][68]=res[68][1]=1ll;
	res[1][69]=res[69][1]=0ll;
	res[1][70]=res[70][1]=1ll;
	res[1][71]=res[71][1]=0ll;
	res[1][72]=res[72][1]=1ll;
	res[1][73]=res[73][1]=0ll;
	res[1][74]=res[74][1]=1ll;
	res[1][75]=res[75][1]=0ll;
	res[1][76]=res[76][1]=1ll;
	res[1][77]=res[77][1]=0ll;
	res[1][78]=res[78][1]=1ll;
	res[1][79]=res[79][1]=0ll;
	res[1][80]=res[80][1]=1ll;
	res[1][81]=res[81][1]=0ll;
	res[1][82]=res[82][1]=1ll;
	res[1][83]=res[83][1]=0ll;
	res[1][84]=res[84][1]=1ll;
	res[1][85]=res[85][1]=0ll;
	res[1][86]=res[86][1]=1ll;
	res[1][87]=res[87][1]=0ll;
	res[1][88]=res[88][1]=1ll;
	res[1][89]=res[89][1]=0ll;
	res[1][90]=res[90][1]=1ll;
	res[1][91]=res[91][1]=0ll;
	res[1][92]=res[92][1]=1ll;
	res[1][93]=res[93][1]=0ll;
	res[1][94]=res[94][1]=1ll;
	res[1][95]=res[95][1]=0ll;
	res[1][96]=res[96][1]=1ll;
	res[1][97]=res[97][1]=0ll;
	res[1][98]=res[98][1]=1ll;
	res[1][99]=res[99][1]=0ll;
	res[1][100]=res[100][1]=1ll;
	res[2][2]=res[2][2]=2ll;
	res[2][3]=res[3][2]=3ll;
	res[2][4]=res[4][2]=5ll;
	res[2][5]=res[5][2]=8ll;
	res[2][6]=res[6][2]=13ll;
	res[2][7]=res[7][2]=21ll;
	res[2][8]=res[8][2]=34ll;
	res[2][9]=res[9][2]=55ll;
	res[2][10]=res[10][2]=89ll;
	res[2][11]=res[11][2]=144ll;
	res[2][12]=res[12][2]=233ll;
	res[2][13]=res[13][2]=377ll;
	res[2][14]=res[14][2]=610ll;
	res[2][15]=res[15][2]=987ll;
	res[2][16]=res[16][2]=1597ll;
	res[2][17]=res[17][2]=2584ll;
	res[2][18]=res[18][2]=4181ll;
	res[2][19]=res[19][2]=6765ll;
	res[2][20]=res[20][2]=10946ll;
	res[2][21]=res[21][2]=17711ll;
	res[2][22]=res[22][2]=28657ll;
	res[2][23]=res[23][2]=46368ll;
	res[2][24]=res[24][2]=75025ll;
	res[2][25]=res[25][2]=121393ll;
	res[2][26]=res[26][2]=196418ll;
	res[2][27]=res[27][2]=317811ll;
	res[2][28]=res[28][2]=514229ll;
	res[2][29]=res[29][2]=832040ll;
	res[2][30]=res[30][2]=1346269ll;
	res[2][31]=res[31][2]=2178309ll;
	res[2][32]=res[32][2]=3524578ll;
	res[2][33]=res[33][2]=5702887ll;
	res[2][34]=res[34][2]=9227465ll;
	res[2][35]=res[35][2]=14930352ll;
	res[2][36]=res[36][2]=24157817ll;
	res[2][37]=res[37][2]=39088169ll;
	res[2][38]=res[38][2]=63245986ll;
	res[2][39]=res[39][2]=102334155ll;
	res[2][40]=res[40][2]=165580141ll;
	res[2][41]=res[41][2]=267914296ll;
	res[2][42]=res[42][2]=433494437ll;
	res[2][43]=res[43][2]=701408733ll;
	res[2][44]=res[44][2]=1134903170ll;
	res[2][45]=res[45][2]=1836311903ll;
	res[2][46]=res[46][2]=2971215073ll;
	res[2][47]=res[47][2]=4807526976ll;
	res[2][48]=res[48][2]=7778742049ll;
	res[2][49]=res[49][2]=12586269025ll;
	res[2][50]=res[50][2]=20365011074ll;
	res[3][3]=res[3][3]=0ll;
	res[3][4]=res[4][3]=11ll;
	res[3][5]=res[5][3]=0ll;
	res[3][6]=res[6][3]=41ll;
	res[3][7]=res[7][3]=0ll;
	res[3][8]=res[8][3]=153ll;
	res[3][9]=res[9][3]=0ll;
	res[3][10]=res[10][3]=571ll;
	res[3][11]=res[11][3]=0ll;
	res[3][12]=res[12][3]=2131ll;
	res[3][13]=res[13][3]=0ll;
	res[3][14]=res[14][3]=7953ll;
	res[3][15]=res[15][3]=0ll;
	res[3][16]=res[16][3]=29681ll;
	res[3][17]=res[17][3]=0ll;
	res[3][18]=res[18][3]=110771ll;
	res[3][19]=res[19][3]=0ll;
	res[3][20]=res[20][3]=413403ll;
	res[3][21]=res[21][3]=0ll;
	res[3][22]=res[22][3]=1542841ll;
	res[3][23]=res[23][3]=0ll;
	res[3][24]=res[24][3]=5757961ll;
	res[3][25]=res[25][3]=0ll;
	res[3][26]=res[26][3]=21489003ll;
	res[3][27]=res[27][3]=0ll;
	res[3][28]=res[28][3]=80198051ll;
	res[3][29]=res[29][3]=0ll;
	res[3][30]=res[30][3]=299303201ll;
	res[3][31]=res[31][3]=0ll;
	res[3][32]=res[32][3]=1117014753ll;
	res[3][33]=res[33][3]=0ll;
	res[4][4]=res[4][4]=36ll;
	res[4][5]=res[5][4]=95ll;
	res[4][6]=res[6][4]=281ll;
	res[4][7]=res[7][4]=781ll;
	res[4][8]=res[8][4]=2245ll;
	res[4][9]=res[9][4]=6336ll;
	res[4][10]=res[10][4]=18061ll;
	res[4][11]=res[11][4]=51205ll;
	res[4][12]=res[12][4]=145601ll;
	res[4][13]=res[13][4]=413351ll;
	res[4][14]=res[14][4]=1174500ll;
	res[4][15]=res[15][4]=3335651ll;
	res[4][16]=res[16][4]=9475901ll;
	res[4][17]=res[17][4]=26915305ll;
	res[4][18]=res[18][4]=76455961ll;
	res[4][19]=res[19][4]=217172736ll;
	res[4][20]=res[20][4]=616891945ll;
	res[4][21]=res[21][4]=1752296281ll;
	res[4][22]=res[22][4]=4977472781ll;
	res[4][23]=res[23][4]=14138673395ll;
	res[4][24]=res[24][4]=40161441636ll;
	res[4][25]=res[25][4]=114079985111ll;
	res[5][5]=res[5][5]=0ll;
	res[5][6]=res[6][5]=1183ll;
	res[5][7]=res[7][5]=0ll;
	res[5][8]=res[8][5]=14824ll;
	res[5][9]=res[9][5]=0ll;
	res[5][10]=res[10][5]=185921ll;
	res[5][11]=res[11][5]=0ll;
	res[5][12]=res[12][5]=2332097ll;
	res[5][13]=res[13][5]=0ll;
	res[5][14]=res[14][5]=29253160ll;
	res[5][15]=res[15][5]=0ll;
	res[5][16]=res[16][5]=366944287ll;
	res[5][17]=res[17][5]=0ll;
	res[5][18]=res[18][5]=4602858719ll;
	res[5][19]=res[19][5]=0ll;
	res[5][20]=res[20][5]=57737128904ll;
	res[6][6]=res[6][6]=6728ll;
	res[6][7]=res[7][6]=31529ll;
	res[6][8]=res[8][6]=167089ll;
	res[6][9]=res[9][6]=817991ll;
	res[6][10]=res[10][6]=4213133ll;
	res[6][11]=res[11][6]=21001799ll;
	res[6][12]=res[12][6]=106912793ll;
	res[6][13]=res[13][6]=536948224ll;
	res[6][14]=res[14][6]=2720246633ll;
	res[6][15]=res[15][6]=13704300553ll;
	res[6][16]=res[16][6]=69289288909ll;
	res[7][7]=res[7][7]=0ll;
	res[7][8]=res[8][7]=1292697ll;
	res[7][9]=res[9][7]=0ll;
	res[7][10]=res[10][7]=53175517ll;
	res[7][11]=res[11][7]=0ll;
	res[7][12]=res[12][7]=2188978117ll;
	res[7][13]=res[13][7]=0ll;
	res[7][14]=res[14][7]=90124167441ll;
	res[8][8]=res[8][8]=12988816ll;
	res[8][9]=res[9][8]=108435745ll;
	res[8][10]=res[10][8]=1031151241ll;
	res[8][11]=res[11][8]=8940739824ll;
	res[8][12]=res[12][8]=82741005829ll;
	res[9][9]=res[9][9]=0ll;
	res[9][10]=res[10][9]=14479521761ll;
	res[9][11]=res[11][9]=0ll;
	res[10][10]=res[10][10]=258584046368ll;
	int n,m;
	while(scanf("%d%d",&n,&m)==2) printf("%lld\n",res[n][m]);
	return 0;
}
```
然后就过了。
# 小心输入有大量重复数据！！！
# 小心输入有大量重复数据！！！
# 小心输入有大量重复数据！！！
正解应该是在每一次DP之前判断当前这个数据是否计算过，是则直接查表输出，否则将结果加入表中并输出。

正解：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=15;
int n,m,pos;
LL d[2][1<<maxn];
inline void update(int a,int b) { if(b&(1<<m)) d[pos][b^(1<<m)]+=d[pos^1][a]; }
LL res[105][105];
int main()
{
#ifdef local
	freopen("pro.in","r",stdin);
#endif
	memset(res,-1,sizeof(res));
	while(scanf("%d%d",&n,&m)==2)
	{
		if(m>n) swap(n,m);
		if(res[n][m]>-1) { printf("%lld\n",res[n][m]); continue; }
		memset(d,0,sizeof(d));
		pos=0;
		d[0][(1<<m)-1]=1;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
			{
				pos^=1;
				memset(d[pos],0,sizeof(d[pos]));
				for(int k=0;k<(1<<m);k++)
				{
					update(k,k<<1);
					if(i&&!(k&(1<<(m-1)))) update(k,(k<<1)^(1<<m)^1);
					if(j&&!(k&1)) update(k,(k<<1)^3);
				}
			}
		printf("%lld\n",res[n][m]=d[pos][(1<<m)-1]);
	}
	return 0;
}
```

---

## 作者：skydogli (赞：3)

## 来一个通俗易懂的状压
做这题时并不知道这是插头$DP$的模板,于是自己手糊了个状压,复杂度一般,但是能过,然后交上去,$rank3?$上面2个打表?看来状压常数还是不错的.

### 思路:

先看数据范围,$n*m<=100$,那么$n,m$中较小的一个肯定小于等于$10$,同时有个很显然的性质,把$n,m$互换不会对结果产生影响,所以我们可以将小的作为$m$,于是每一行就可以进行状态压缩了

因为骨牌是$1*2$的,所以要么横着放,要么竖着放,横着放需要满足空位必须是二的倍数,而竖着放就会对后面有影响.

于是我们可以设$DP$状态$f[i][st]$表示第$i$行状态为$st$,的方案数,其中$st$为m个格子分别是怎么填的,1表示这个格子要从这行开始竖着放,如$f[2][100010]$表示第二行的第一和第五个格子都要放一个竖着的骨牌(其它先不管).

然后我们枚举前一排的状态,如果前一排的状态$st'$&$st!=0$,就意味着上一排的竖着的骨牌占了这一排竖着的骨牌的位置了,那么就不合法.

将$st$|$st'$后,我们就知道当前枚举的状态中有多少个格子被填充了,剩下的就只能横着放,我们就判断这个状态中,0是否成双出现,否则不合法,这个操作可以$O(m)$判断,最后确定都合法后,我们就把$f[i-1][st']$的值加入$f[i][st]$就行了.

### 时间复杂度及优化

按照朴素想法,每一行扫一遍,枚举当前行状态,枚举上一行状态,判断0成双出现,时间复杂度$O(n*2^m*2^m*m)=O(nm 2^{2m})$就算能过也被插头$DP$吊打,相当没面子,所以我们可以想一些优化:

##### 优化$1:$枚举上一行状态的优化

这是做状压时的常用技巧.很显然因为$st$&$st'=0$,所以$st'$必然是$st$的补集的子集,以$10010$为例,合法的状态肯定是$01101$的子集$01100$,$01001$,$01000$,$00101$,$01100$等等,于是我们可以写下以下玄学的代码
```cpp
//Maxn为(1<<m)-1,chk为判断0成双出现的函数
for(int j=0;j<=Maxn;++j){
	f[i][j]=0;
	int o=Maxn^j;
	for(int k=o;k;k=(k-1)&o){
		if(chk((j|k),m)){f[i][j]+=f[i-1][k];}
	}
	if(chk(j,m)){f[i][j]+=f[i-1][0];}
}

```
可以证明,上面2个$for$循环的复杂度是$O(3^m)$次方的,然而我不会证~~信息学不需要证明!~~

于是复杂度变成了$O(nm3^m)$

##### 优化2:记住算过的值
事实上,chk函数只需要判断$(1<<m)*m)$种状态,那么我们可以把chk过的数记录下来,再碰到就直接输出结果

这个然后复杂度就变成$O(n3^m)$了

另外,听另一篇题解说有很多重复的问题,于是我们可以再记录算过的答案,进一步剪枝

于是其实和插头$DP$的$O(nm2^m)$在$m<=10$时其实相差无几了,实际测试时因为常数小所以跑得飞快

##### 优化3?:记录每个与当前$st$ or运算后合法的$st'$
这个留给大家试试吧,还没有付诸实践,m=10时,所有有效的组合大概是$3^m$的十分之一,可能会再快一点(然而已经$0ms$了,所以也懒得试了)

### 代码:
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
bool vis[1<<11|1][11],ok[1<<11|1][11];
//用于判断该状态中0是否成双出现
int n,m;
long long f[103][1<<11|1],ans[103][103];
//f用于DP,ans保存答案
bool chk(int a,int m){
    if(vis[a][m]){return ok[a][m];}
    vis[a][m]=1;
    int s=0,tmp=a;//a会改变,记得先存在tmp里
    for(int i=1;i<=m;++i){//不能用while因为可能有前缀0
        if(a&1){if(s&1)return ok[tmp][m]=0;}
            else ++s;
        a>>=1;
    }
    if(s&1)return ok[tmp][m]=0;
    ok[tmp][m]=1;
    return 1;
}
int main(){
    for(int i=0;i<=100;++i)for(int j=0;j<=100;++j)ans[i][j]=-1;
    while(~scanf("%d%d",&n,&m)){
        if(n<m)swap(n,m);//m取小的
        if(!n||!m){puts("0");continue;}
        if(ans[n][m]!=-1){printf("%lld\n",ans[n][m]);continue;}
        int Maxn=(1<<m)-1;
        f[0][0]=1LL;
        for(int i=1;i<=n;++i)
            for(int j=0;j<=Maxn;++j){
                f[i][j]=0;//先清零
                int o=Maxn^j;
                for(int k=o;k;k=(k-1)&o){
                    if(chk((j|k),m)){f[i][j]+=f[i-1][k];}
                }
                if(chk(j,m)){f[i][j]+=f[i-1][0];}
            }
        ans[n][m]=f[n][0];
        printf("%lld\n",f[n][0]);
    }
    return 0;
}

```








---

## 作者：Exber (赞：2)

## 题意
- #### 给你一个 $n\times m$ 的棋盘，求用 $1\times2$ 的长方形骨牌完全覆盖这个棋盘的方案数。

## 做法
插头 dp。

#### 前置芝士：
- ##### 状态压缩

本题十分适合学习插头 dp。

插头 dp 是一种很神奇的 dp 算法，它还有另外一个大名：**轮廓线 dp**。顾名思义，轮廓线 dp 就是在一条叫**轮廓线**的线上进行 dp。

#### 轮廓线是什么?

![](https://cdn.luogu.com.cn/upload/image_hosting/b075t08a.png)

当推到黄色格子时，轮廓线就是那条**绿色的线**。

因为决定当前格子状态的其实只有轮廓线上面的那几个格子，所以只要知道它们的状态，就能推出当前的的方案数。

我们可以利用状态压缩，用二进制表示轮廓线上格子的覆盖状态。覆盖则那一位为 `1`，未覆盖则那一位为 `0`。

就像这样：(**轮廓线上**灰色的格子表示已覆盖，白色的表示未覆盖)

![](https://cdn.luogu.com.cn/upload/image_hosting/neegehd9.png)

这时轮廓线上的状态就用二进制 `100110111` 来表示。

#### 轮廓线上为什么会有未覆盖的格子？

这是一个比较难理解的事情。

由于必须全覆盖，所以格子应该都是覆盖了的啊？

可是别忘了，**轮廓线上的**格子可以被覆盖黄色格子的骨牌覆盖。例如这种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/w9a1pfij.png)

就可以放一个横着的骨牌来覆盖黄色格子和黄色格子左边的格子，或者放一个竖着的骨牌来覆盖黄色格子和黄色格子上边的格子。就像这样：


![](https://cdn.luogu.com.cn/upload/image_hosting/iahpo90u.png)

和这样

![](https://cdn.luogu.com.cn/upload/image_hosting/ap2w6tp1.png)

#### 如何定义 dp 状态？

定义 $dp_{i,j,k}$ 表示推到格子 $(i,j)$，**推完之后的**轮廓线上格子的覆盖状态是 $k$ 时的方案数。

**什么是推完之后的轮廓线？**

推完一个格子，这个格子的覆盖情况就会被确定，那么轮廓线就可以从

![](https://cdn.luogu.com.cn/upload/image_hosting/b075t08a.png)

变成

![](https://cdn.luogu.com.cn/upload/image_hosting/a9gkwg4j.png)

这样就可以为下一次转移做铺垫。

#### 如何求解？

首先得有一个数组 `only`。$only_i$ 存只有 $i$ 位为 `1` 的二进制对应的值，即 `1<<i-1`。

而在 dp 时需要枚举每一个格子，记当前格子为 $(i,j)$。再枚举轮廓线上格子的覆盖状态，记为 $k$。

因为当前格子的轮廓线实际上是左边格子推完之后的轮廓线，所以 $k$ 应该作为 $dp_{i,j-1}$ 的第三维下标，即 $dp_{i,j-1,k}$。

对于状态转移，只有三种情况：
- ##### 黄色格放一个竖放的骨牌
- ##### 黄色格放一个横放的骨牌
- ##### 黄色格不放骨牌

**对于黄色格放一个竖放的骨牌**

如果黄色格上面那个格子未覆盖，那就一定要放竖放的骨牌，否则就不能放竖放的骨牌。

当然，在第一行时也不能放竖放的骨牌。

写成代码就是
```
if(i>=2&&!(k&only[j]))
{
	dp[i][j][k|only[j]]+=dp[i][j-1][k];
}
```

为什么要求那么**强硬**呢？

很简单，如果上面的格子没被覆盖，那你也不能指望其它骨牌覆盖它了。因为它旁边的格子就只有黄色格子的状态未定。

**对于黄色格放一个横放的骨牌**

如果不能放竖放的骨牌，才能考虑放横放的。

而只有当黄色格子左边那个格子未覆盖时，**才能放**横放的骨牌。

注意，并不是**一定要放**横放的骨牌，因为左边那个格子还能被下面的格子放的竖放的骨牌覆盖。

当然，再第一列时也不能放横放的骨牌。

写成代码就是
```
if(j>=2&&!(k&only[j-1])&&(k&only[j]))
{
	dp[i][j][k|only[j-1]]+=dp[i][j-1][k];
}
```

**对于黄色格不放骨牌的情况**

同考虑放横放的骨牌，如果不能放竖放的骨牌，才能考虑不放。

不放骨牌就没什么要求了。

写成代码就是 
```
if(k&only[j])
{
	dp[i][j][k^only[j]]+=dp[i][j-1][k];
}
```

#### 如何初始化？
由于是累加，所以初始化十分重要。

$dp_{0,m,(1<<m)-1}=1$

$dp_{i,0,k}=dp_{i-1,m,k}$（$k$ 是任意状态）

第一个初始化很好理解，可是第二个初始化就有点难理解了。

$dp_{i,0,k}$ 所对应的推完之后的轮廓线是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/gipg37ib.png)

而 $dp_{i-1,m,k}$ 所对应的推完之后的轮廓线是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/c0rb52ad.png)

由于这两条轮廓线本质上是同一条，所以同一状态下的方案数也一样了。

#### 优化
如果 $n<m$，那么交换一下 $n$ 和 $m$ 来防止状态对应的十进制数过大。

由于每行状态只和上一行有关，所以可以把数组压成二维的，令 `memset` 的时间变短。[不然……](https://www.luogu.com.cn/record/51469658)

## AC 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int n,m,only[15];        // 行数，列数，only 数组 
long long dp[15][1<<10]; // 压缩 

int main()
{
	ios::sync_with_stdio(false); // 加快读入速度 
	// 预处理 only 
	for(int i=1;i<=10;i++)
	{
		only[i]=1<<i-1;
	}
	while(cin>>n>>m)
	{
		if(n<m) // 优化 
		{
			int t=n;
			n=m;
			m=t;
		}
		int endd=(1<<m)-1;
		memset(dp,0,sizeof(dp));
		dp[m][endd]=1; // 初始化 
		for(int i=1;i<=n;i++)
		{
			for(int k=0;k<=endd;k++)
			{
				dp[0][k]=dp[m][k]; // 初始化 
			}
			for(int j=1;j<=m;j++)
			{
				memset(dp[j],0,sizeof(dp[j]));
			}
			for(int j=1;j<=m;j++)
			{
				for(int k=0;k<=endd;k++)
				{
					if(k&only[j])
					{
						dp[j][k^only[j]]+=dp[j-1][k]; // 不放 
						if(j>=2&&!(k&only[j-1]))
						{
							dp[j][k|only[j-1]]+=dp[j-1][k]; // 横着放 
						}
					}
				 	else if(i>=2)
					{
						dp[j][k|only[j]]+=dp[j-1][k]; // 竖着放 
					}
				}
			}
		}
		cout<<dp[m][endd]<<endl; // 输出答案 
	}
	return 0;
}
```


---

## 作者：CommonDigger (赞：1)

### 题意
使用 $1\times2$ 的牌铺满一个大长方形。

### 方法
涉及到的算法：插头 DP（轮廓线 DP）。

从题目数据范围可以看到，长方形面积不超过 $100$，故长方形的宽最大为 $10$，且每一格只有放或不放两种可能，所以可以用二进制下的 $0\sim1023$ 表示所有状态。

设 `f[i<=10][j<=1024]` 表示长方形的第 `i` 列，轮廓状态为 `j` 时的方案数。

这一题中，轮廓就是当前格子左边、当前格子上一行右边的几个格子的状态。具体的图像可参见一楼大佬的文章。

由于轮廓状态是二进制形式枚举的，所以可设其二进制下的第 $i$ 位就是*从左至右*第 $i$ 个格子的状态。（$2^0$ 位是第一格，$2^1$ 位是第二格等）如果当前格子位置是 $j$，则其左边格子的位置就是是 $j-1(j\geqslant1)$。

对于要枚举的这个格子，有三种方法：横着放或竖着放，还有不放。

为了利用好轮廓，横着放的时候只考虑占用这个格子左边一个；竖着放时，只考虑占用这个格子上面的格子。

1. 竖放：如果要在第 $j$ 个格子处竖着放，则当前格子上方必须是未使用的，即这一位的二进制为 $0$。放上去后，得到的新状态的该位修改为 $1$。
2. 横放：注意，如果当前格子上面是空的，此时横放就会把上面格子永远挡住。所以仅当上面格子已放时才考虑横着放（或者不放）。得到的新状态的左边格子修改为 $1$（这一位本身就是 $1$，记录的是该位上面已填充）。
3. 不放：与 $2$ 同理，仅当上面格子已填充才考虑不放。新状态的该位修改为 $0$。

状态可能从多个地方转移，故 `dp` 值采用累加，并且及时 `memset`。

另外，需要只用滚动数组，方便访问上一行的状态。**如果不使用**则会出现 $j=1$ 时错误访问等一些玄学问题。

### 代码
```cpp
/*
Luogu UVA11270 Tiling Dominoes
https://www.luogu.com.cn/problem/UVA11270
*/
#include "iostream"
#include "cstring"
using namespace std;
int n, m, temp, q;
unsigned long long f[2][1024];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    while(cin >> n >> m){
        if(m>n) swap(m, n);
        temp=1<<m;
        memset(f, 0, sizeof(f));
        f[0][temp-1]=1;
        for(int i=1;i<=n;i++){ // 行（不需要作为dp状态）
            for(int j=1;j<=m;j++){ // 列
                q^=1;
                memset(f[q], 0, sizeof(f[q]));
                for(int k=0;k<temp;k++){ // k: 当前轮廓
                    if(k&(1<<(j-1))){ // 这一位上面已填充
                        f[q][k^(1<<(j-1))]+=f[q^1] [k]; // 不放
                        if(j>1 && !(k&(1<<(j-2)))){ // 如果左边是空的，考虑横向
                            f[q][k|(1<<(j-2))]+=f[q^1][k];
                        }
                    }else{ // 上面是空的，必须竖放
                        if(i) f[q][k|(1<<(j-1))]+=f[q^1][k];
                    }
                }
            }
        }
        cout << f[q][temp-1] << "\n";
    }
}
```

---

## 作者：rnf5114 (赞：1)

轮廓线动规入门题。

可以发现题目中的 $n$ 和 $m$ 都并非大数，但是如果对全局的情况直接状压肯定爆空间，又因为我们当前的这一行的决策只会受到上一行或者这一行的影响，所以我们只考虑将这一部分进行状压即可。

可以发现对于当前这一格子我们只会出现以下几种情况：

1. 上方格子为空，必须竖放。
2. 上方格子不为空，左边如果为空则可以横放。
3. 只要上方格子不为空，当前格子为空则可以不放。

那么我们的状态定义就很显然了 $dp_{i,j,k}$ 表示第 $i$ 行第 $j$ 列的格子，前 $m$ 个格子（包含自身）状态为 $k$ 的可能数。又因为每个格子的前 $m$ 个格子的状态可以用上个格子直接得到，所以可以考虑滚动数组。

为了写起来方便一点，我们直接按照列的出现顺序给每个元素标好它在状压转移时的转边的影响。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,dp[2][1<<10],p[20];
signed main(){
	for(int i=1;i<=19;i++)
		p[i]=(1<<(i-1));
	while(cin>>n>>m){
		if(m>n)
			swap(n,m);
		memset(dp,0,sizeof dp);
		dp[0][(1<<m)-1]=1;
		int cur=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cur^=1;
				memset(dp[cur],0,sizeof dp[cur]);
				for(int k=0;k<(1<<m);k++){
					if(i!=1&&(!(k&p[j]))){
						int nk=(k|p[j]);
						dp[cur][nk]+=dp[1-cur][k];
					}
					if(j!=1&&(k&p[j])&&(!(k&p[j-1]))){
						int nk=(k|p[j-1]);
						dp[cur][nk]+=dp[1-cur][k];
					}
					if(k&p[j]){
						int nk=(k^p[j]);
						dp[cur][nk]+=dp[1-cur][k];
					}
				}
			}
		}
		cout<<dp[cur][(1<<m)-1]<<"\n";
	}
	return 0;
}

/*
       ┏┓　　　┏┓
     ┏┛┻━━━┛┻┓
     ┃　　　　　　　┃
     ┃　　　━　　　┃
     ┃　┳┛　┗┳　┃
     ┃　　　　　　　┃
     ┃　　　┻　　　┃
     ┃　　　　　　　┃
     ┗━┓　　　┏━┛
         ┃　　　┃
         ┃　　　┃
         ┃　　　┗━━━┓
         ┃　　　　　 ┣┓
         ┃　　　　 ┏┛
         ┗┓┓┏━┳┓┏┛
           ┃┫┫　┃┫┫
*/

```


后记：自己感觉比较适合初学者的[延申题](https://www.iai.sh.cn/problem/812)。

---

## 作者：EnofTaiPeople (赞：1)

数据范围较小，先处理，不妨让 $m \le n$，则 $m\le10$，可以状压。朴素方法是逐行递推，复杂度为 $O(n4^m)$，多测会被卡 TLE，所以使用轮廓线动态规划，逐格递推，复杂度为 $O(mn2^m)$，可以通过。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long dp[2][1030];
int n,m,now,w;
inline void Upd(int a,int b){if((b>>m)&1)dp[now][b^(1<<m)]+=dp[!now][a];}
int main(){
	int i,j,k;
	while(scanf("%d%d",&n,&m)==2){
		if(n<m)n^=m^=n^=m;w=1<<m;
		memset(dp,0,sizeof(dp));
		dp[now=0][w-1]=1;
		for(i=0;i<n;++i)
			for(j=0;j<m;++j){
				now^=1;for(k=0;k<w;++k)dp[now][k]=0;
				for(k=0;k<w;++k){
					Upd(k,k<<1);
					if(i&&!(k&(1<<m-1)))Upd(k,(k<<1)^w^1);
					if(j&&!(k&1))Upd(k,(k<<1)^3);
				}
			}printf("%lld\n",dp[now][w-1]);
	}
	return 0;
}
```

---

## 作者：_l_l_ (赞：1)

upd:2021-07-04 修改了定义

[**题目传送门**](https://www.luogu.com.cn/problem/UVA11270)

## 题解

这道题目将使用轮廓线 DP。

定义 $f_{i,j,k}$ 为 DP 到第 $i$ 行第 $j$ 列时，状态为 $k$ 的方案数。

我们定义状态 $0$ 为本方块未被占领，$1$ 为本方块已被占领，则当我们推理黄色格时我们只需要将如图的 $m$ 个方块的状态记录下来，组成二进制即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/7on5uont.png)

假设我们正在求 $f_{i,j,k}$：

1. 摆一个竖着的骨牌
   
   若第 $i-1$ 行第 $j$ 列的方块是状态 $0$，则**必须**摆一个竖着的骨牌，并且将第 $i$ 行第 $j$ 列的方块状态变为 $1$。
   
   ![](https://cdn.luogu.com.cn/upload/image_hosting/tueyxdqs.png)
   
2. 摆一个横着的骨牌

   若第 $i-1$ 行第 $j$ 列的方块是状态 $1$ 且第 $i$ 行第 $j-1$ 列的方块是状态 $0$，则**可以**摆一个横着的骨牌，并且将第 $i$ 行第 $j$ 列的方块状态变为 $1$。
   
   ![](https://cdn.luogu.com.cn/upload/image_hosting/v6q9411w.png)
   
3. ~~懒~~，什么都不干

   若第 $i-1$ 行第 $j$ 列的方块是状态 $1$，则**可以**什么都不干，并且将第 $i$ 行第 $j$ 列的方块状态变为 $0$。
   
将以上三个状态结合起来就可以写出转移方程。

## 代码

使用 **C++** 语言

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring> 
using namespace std;
int n, m;
long long Dp[2][1 << 10];
int main() {
	while (~scanf("%d %d", &n, &m)) {
		if (n < m) swap(n, m);
		int qwq = 0;
		memset(Dp, 0, sizeof Dp);
		Dp[0][(1 << m) - 1] = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				qwq ^= 1;
				memset(Dp[qwq], 0, sizeof Dp[qwq]);
				for (int k = 0; k < (1 << m); k++) {
					if (k & (1 << j - 1)) {
						Dp[qwq][k ^ (1 << j - 1)] += Dp[qwq ^ 1][k];
					}
					if ((j > 1) && !(k & (1 << j - 2)) && (k & (1 << j - 1))) {
						Dp[qwq][k | (1 << j - 2)] += Dp[qwq ^ 1][k];
					}
					if ((i > 1) && !(k & (1 << j - 1))) {
						Dp[qwq][k | (1 << j - 1)] += Dp[qwq ^ 1][k];
					}
				}
			}
		}
		printf("%lld\n", Dp[qwq][(1 << m) - 1]);
	}
	return 0;
}
```

---

## 作者：Soh_paramEEMS (赞：0)

## 题意

给定一个 $m×n$ 的矩形网格，用 $1×2$ 多米诺骨牌完全平铺。问有多少种铺设方案。

$m\times n\le 100$
## 思路
本人的记搜却被这题卡时间。果然还是得会写轮廓线 dp 的纯 dp 形式。

考虑将行换为 $\min(n,m)$，令 $f_{i,s}$ 表示第 $i$ 行的状态，状态中 $1$ 表示竖块 $1\times2$ 的**顶部**、$0$ 表示填了横块 $2\times 1$ 或者留空或者有上面的竖块伸下来（那么就不再考虑下面填一个竖块能伸上去的情况了）。

设枚举到当前行总状态为 $s$，上一行状态是 $s'$，那么可以得到几个初步需要注意的：

- 同一列上下两个状态不能同为 $1$，因为上下两个竖块就**重叠**了（如下图）；

![](https://cdn.luogu.com.cn/upload/image_hosting/ju2s6fa6.png)

- 当前行状态 $s$ 处理完毕后，不能存在有奇数个 $0$ 或 中间有连续个奇数个 $0$，因为上文说过**不再考虑下面填一个竖块能伸上去的情况**，中间要是有奇数个 $0$，就不能用横块填满，那么下面的行就不能补上空着的这个了。

![](https://cdn.luogu.com.cn/upload/image_hosting/0lo3b8zy.png)

初始时 $f_{0,0}=1$。

考虑枚举上一行的状态 $s'$，上文提到**不能重叠**，那就必须有 $s\ \textrm{and}\ s'=0$，那么 $s'$ 从 $s$ 的逐位取反开始枚举子集（包括 $0$ 对应的全部填横块的）。

把上一行状态和本行状态与起来，那么上一行填了竖块的的状态 $1$ 就可以补到下面来，这时候再检查一下，有没有连续奇数个 $0$ 的情况。如果合法，就加上上一行状态为 $s'$ 的状态数。
$$f_{i,s}\xleftarrow[]{\textrm{check}(s|s')=\rm true} f_{i-1,s'}$$

为了节省时间，用一个 $ans$ 数组记录每一对 $(n,m),n>m$ 的答案，然后当 $n\times m$ 为 $0$ 或奇数就不可能填完的，直接输出 $0$ 即可。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=102,M=11,S=(1<<M)+3;
ll n,m;
ll ans[N][N],f[N][S];
bool vis[S][M],lian[S][M];//有没有连着的空位 
bool check(ll s,ll m)
{
	if(vis[s][m])return lian[s][m];
	vis[s][m]=1;
	ll tem=s,cnt_empty=0;
	for(int i=1;i<=m;i++)
	{
		if(tem&1){if(cnt_empty&1)return lian[s][m]=0;}//不空，但前面已经有了奇数个空块，填不下了
		else cnt_empty++;
		tem>>=1;
	}
	if(cnt_empty&1)return lian[s][m]=0;
	return lian[s][m]=1;
}
int main()
{
	memset(ans,-1,sizeof(ans));
	while(~scanf("%lld%lld",&n,&m))
	{
		if(n<m)swap(n,m);
		if((n*m)&1||n==0||m==0){puts("0");continue;}
		if(ans[n][m]>-1){printf("%lld\n",ans[n][m]);continue;}
		f[0][0]=1;
		ll M=(1<<m)-1;
		for(int i=1;i<=n;i++)
		{
			for(int s=0;s<=M;s++)
			{
				f[i][s]=0;
				ll ns=s^M;
				//如果上一行的状态s'&s!=0，那么有两块竖块冲突，不合法
				//上一行的状态是当前行的取反的子集 
				for(int j=ns;j>=0;j=(j-1)&ns)//上一行能不能有竖的伸下来 
				{
					if(check((s|j),m))f[i][s]+=f[i-1][j];//把上一行伸下来的补上去 
					if(j==0)break;//记得特判0哦
				}
			}
		}
		ans[n][m]=f[n][0];//最后一行不能填竖块
		printf("%lld\n",ans[n][m]);
	}
	return 0;
}
```

---

## 作者：Remarks (赞：0)

一个针对此题比较抽象的转移方案。

刚跟同学 saber 的时候碰到的题，之前没写过，然后自己搞出来的神秘做法。

### solution

计 $f_{i,s}$ 为当前填满前 $i$ 行，且 $i$ 行**竖直**放置的方块的状态集，摆放方法种类数。

例如：

![](https://cdn.luogu.com.cn/upload/image_hosting/od30xw64.png)

相信状态设计大家都看懂了。也容易看出来，初值 $f_{0,0}=0$，答案是 $f_{n,0}$。

然后看转移。这里我直接上代码：

```cpp
void dfs(long long s,long long r,long long v,long long lst){
    //s 状态集，r更新答案用的行数，v是转移值，lst下文会说。
    if(v==0)return;//这一行为了节省时间
    f[r][s]+=v;
    for(long long i=lst;i<m-1;i++){
        if((s&(1<<i))&&(s&(1<<(i+1)))){
            dfs(((s^(1<<i))^(1<<(i+1))),r,v,i+2);
        }
    }
    return ;
}

for(long long i=1;i<=n;i++){
    for(long long s=0;s<=mx;s++)f[i][s]=0;
    for(long long s=0;s<=mx;s++){
        dfs(s^mx,i,f[i-1][s],0);
    }
}
```

我们从状态 $s'$ 转移而来，那这一行我们能填的就是 $s$ 取反。

我们先假设这些空位都用竖直块来填，如图 `I` 。然后我们发现两个挨着的可以合成一个横着的。我们发现可以用 dfs 来更新。如上代码所示。下面有图示。

![哈哈哈](https://cdn.luogu.com.cn/upload/image_hosting/szef2byb.png)

然后我们 dfs 每一层变两个就行。为了防止重复，我们再计一个 lst ，表示这一层的更新最小下标。

剩下的直接做就行。注意令 $n$ 比 $m$ 小，才能正确状压。开 long long。

代码：

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
long long n,m;
long long f[100][100000];
using namespace std;
void dfs(long long s,long long r,long long v,long long lst){
    //s 状态集，r更新答案用的行数，v是转移值，lst下文会说。
    if(v==0)return;//这一行为了节省时间
    f[r][s]+=v;
    for(long long i=lst;i<m-1;i++){
        if((s&(1<<i))&&(s&(1<<(i+1)))){
            dfs(((s^(1<<i))^(1<<(i+1))),r,v,i+2);
        }
    }
    return ;
}
int main(){
    while(cin>>n>>m){
        if(n<m)swap(n,m);
        long long mx=(1<<m)-1;
        f[0][0]=1;
        for(long long i=1;i<=n;i++){
            for(long long s=0;s<=mx;s++)f[i][s]=0;
            for(long long s=0;s<=mx;s++){
                dfs(s^mx,i,f[i-1][s],0);
            }
        }
        cout<<f[n][0]<<endl;
    }
}
```

---

## 作者：rickyxrc (赞：0)

本文章遵守知识共享协议 CC-BY-NC-SA，同步发表于洛谷题解区，转载时须在文章的任一位置附上原文链接和作者署名（rickyxrc）。推荐在[我的个人博客](https://blog.rickyxrc.cc)阅读。

轮廓线 dp 还是很强的，这就是其中的一个应用，也是插头 dp 的前置。

## 题面大意

求用 $1 \times 2$ 的骨牌铺满 $n \times m$ 的矩形的方案数。

## 解题思路

传统的状态压缩在这里不占优势了，我们需要一种新的方法进行动态规划。

我们做如下考虑：如果我们可以一格一格地推进，将已确定状态和未确定状态之间的这条线（以下称作“轮廓线”）逐渐确定下来，那整个图就会被逐渐确定下来，在确定图的过程中我们可以对某些数据进行统计，来达成我们的目的。

![](https://cdn.luogu.com.cn/upload/image_hosting/cqgyut15.png)

如上图中浅色的部分就是轮廓线。

那么我们实际上就是在逐渐确定并转移这条轮廓线，我们不妨用反转数组的思路来考虑这样的思路，这样的话，上一条轮廓线其实就是已确定状态的部分，我们可以直接将其纳入动态规划的转移中。

![](https://cdn.luogu.com.cn/upload/image_hosting/3i8qmf43.png)

说简单点，我们就是在将轮廓线的状态压缩并存入 $f$ 数组中进行动态规划。

在代码里，我们的 $f$ 数组定义如下：

```cpp
long long dp[2][1<<12];
```

此时可能有人会有疑问：最终的棋盘不是填满的吗？为什么轮廓线中还有 $0$ 和 $1$ 之分呢？其实很简单，因为轮廓线下方的状态还没有被确定，所以我们将其置为 $0$，代表这里有一个空位需要被填充。

然后我们要枚举状态 $b \in [0,2^m)$，并在此时考虑三种状态：

1. 竖直放置

![](https://cdn.luogu.com.cn/upload/image_hosting/h5xkyeoy.png)

当且仅当这个格子上面的格子为空的时候，我们需要且只能竖直放置这个矩形，否则我们就再也没有机会填补这个空位了。

代码里的判断条件应该是 $(b \operatorname{and} 2^j) = 0$ 且 $i \neq 0$，代表轮廓线第 $j$ 位上方是空位，应该在此放置竖直的矩形。

```cpp
if (i && !(b & p[j])) // 这一位的上方为空，需要竖放填充
    dp[now][b ^ p[j] /*增加这一位的1，因为上面保证了 b 的 p[j] 位无1*/] += dp[now ^ 1][b];
```

2. 该行留空

![](https://cdn.luogu.com.cn/upload/image_hosting/70at9rgp.png)

什么时候这一行需要留空呢？只要上面不为空，这里就可以留空，等待下一行填补。

代码里的判断条件是 $b \operatorname{and} 2^j \neq 0$，代表轮廓线第 $j$ 位上方不是空位，可以留空。

```cpp
if (b & p[j]) // 这一位的上方被填充，可以留空
    dp[now][b ^ p[j] /*去掉了这一位的1，因为上面保证了 b 的 p[j] 位有1*/] += dp[now ^ 1][b];
```

3. 横向放置

![](https://cdn.luogu.com.cn/upload/image_hosting/1gcl9k0m.png)

当这个格子的上方不为空，左方为空时，我们可以横放填充。

代码中的判断条件是 $b \operatorname{and} 2^j \neq 0$ 且 $j \neq 0$ 且 $b \operatorname{and} 2^{j-1} = 0$

```cpp
if (j && !(b & p[j - 1]) && (b & p[j])) // 这一位的上方不为空，左方为空，需要横放填充
    dp[now][b ^ p[j - 1] /*增加上一位的1*/] += dp[now ^ 1][b];
```

最后我们只需要输出 $f_{now,2^m-1}$ 即可（最后一行最后一轮廓线被填满的方案）。

```cpp
#include <stdio.h>
#include <string.h>

typedef long long i64;

const int maxn = (1 << 13);

i64 dp[2][maxn], p[32], n, m, now;

int main()
{
    for (int i = 0; i < 30; i++)
        p[i] = 1ll << i;

    while (scanf("%lld%lld", &n, &m) != EOF)
    {
        if (n < m)
            n ^= m ^= n ^= m; // 交换 n 和 m，使得 m 的规模不至于太大

        memset(dp, 0, sizeof dp);
        now = 0;

        dp[now][(1 << m) - 1] = 1; // 可以理解为第 -1 行已经被填满

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                now ^= 1;
                memset(dp[now], 0, sizeof dp[now]);

                for (int b = 0; b < (1 << m); b++)
                {
                    if (b & p[j]) // 这一位的上方被填充，可以留空
                        dp[now][b ^ p[j] /*去掉了这一位的1，因为上面保证了 b 的 p[j] 位有1*/] += dp[now ^ 1][b] /*上一位的方案数*/;

                    if (i && !(b & p[j])) // 这一位的上方为空，需要竖放填充
                        dp[now][b ^ p[j] /*增加这一位的1，因为上面保证了 b 的 p[j] 位无1*/] += dp[now ^ 1][b] /*上一位的方案数*/;

                    if (j && !(b & p[j - 1]) && (b & p[j])) // 这一位的上方不为空，左方为空，需要横放填充
                        dp[now][b ^ p[j - 1] /*增加上一位的1*/] += dp[now ^ 1][b] /*上一位的方案数*/;
                }
            }

        printf("%lld\n", dp[now][(1 << m) - 1]);
    }
    return 0;
}
```

---

