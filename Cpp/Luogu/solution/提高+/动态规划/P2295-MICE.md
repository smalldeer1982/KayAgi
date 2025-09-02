# MICE

## 题目描述

S 国的动物园是一个 $N \times M$ 的网格图，左上角的坐标是 $(1,1)$，右下角的坐标是 $(N,M)$。

小象在动物园的左上角，它想回到右下角的家里去睡觉，但是动物园中有一些老鼠，而小象又很害怕老鼠。动物园里的老鼠是彼此互不相同的。小象的害怕值定义为他回家的路径上可以看见的不同的老鼠的数量。若小象当前的位置为 $(x_1,y_1)$，小象可以看见老鼠，当且仅当老鼠的位置 $(x_2,y_2)$ 满足 $|x_1-x_2| + |y_1-y_2| \leq 1$。由于小象很困了，所以小象只会走一条最近的路回家，即小象只会向下或者向右走。现在你需要帮小象确定一条回家的路线，使得小象的害怕值最小。


## 说明/提示

对于 $20\%$ 的数据，$1 \leq N,M \leq 5$。

对于 $100\%$ 的数据，$1 \leq N,M \leq 1000,0 \leq A_{i,j} \leq 100$。

## 样例 #1

### 输入

```
3 9
0 0 1 0 0 0 0 0 1
1 1 1 1 1 1 0 1 0
1 0 0 1 0 0 1 0 0
```

### 输出

```
9```

# 题解

## 作者：SunsetVoice (赞：9)

[更好的阅读体验~](https://www.luogu.com.cn/blog/myj-cai/p2295-ti-xie)

[原题传送门~](https://www.luogu.com.cn/problem/P2295)

## 本题解概要：
1. 为什么需要多加一维存储方向
2. 三维 dp 思路（包括 dp 五步）
3. code&注意事项

最后更新：修改了标点和英文，中文间的空格。鸣谢 @dyc2022 。
## 1.为什么要多加一维用来存储方向？
二维的正常转移式：
$$dp_{i,j} = \min(dp_{i,j-1}+a_{i-1,j},dp_{i-1,j}+a_{i,j-1})+a_{i,j+1}+a_{i+1_j}$$
放在代码中即为：

```cpp
dp[i][j] = min(dp[i][j-1]+a[i-1][j],dp[i-1][j]+a[i][j-1])+a[i][j+1]+a[i+1][j];
```
但是此时如果途中方案有转弯（比如从 $a_{i-1,j-1}$ 走到 $a_{i-1,j}$ 再走到 $a_{i,j}$）（下图）

| → | ↓ |
|-|-|
|  | ↓ |

则 $a_{i,j-1}$ **会被计算两次**。
诸如此类的，在不思考方向的时候将很难判重。

所以，解决方案是增加一维，变为三维记录值。

~~（血的教训:亲测只用二维数组只能 [50 pts](https://www.luogu.com.cn/record/106512285)）~~
## 2. 三维 dp 思路（dp 五步）
#### 状态表示：

设 $dp_{i,j,0}$ 表示在考虑前 $i$ 行前 $j$ 列且上一步从**左边**走过来时的最小害怕值， 
$dp_{i,j,1}$ 表示在考虑前 $i$ 行前 $j$ 列且上一步从**上面**走过来时的最小害怕值。

#### 阶段划分
逐行逐列完成 dp 数组。~~不用说了吧~~
#### 求解目标
根据状态表示可以得出，$\min(dp_{n,m,0},dp_{n,m,1})$ 即为答案。
#### 状态转移（敲黑板）
**温馨提示：建议读者们跟着草稿纸一起画一边图，以便真正理解 dp。**

**本处将当前格子设为 $a_{i,j}$**。

先说说倒数第一步从上面转移过来的情况：

此时倒数第二步分两种：一种是上一格是从左边转移过来的，即：从 $a_{i-1,j-1}$ 转移（走）到 $a_{i-1,j}$ 再走（转移）到 $a_{i,j}$ 中的。

那么，这种情况下，$dp_{i-1,j-1}$ （ 01  都行 ）显然至少包括了**上下左右中五个格子**，即 $dp_{i-1,j-1}$ 至少包括了 $a_{i-2,j-1},a_{i-1,j-2},a_{i-1,j-1},a_{i,j-1}$ 以及 $a_{i-1,j}$ 这五个格子中的老鼠数目。而 $dp_{i-1,j,0}$ 不仅至少包括了前面所说的五个数，还至少额外添加了 $a_{i,j},a_{i-1,j+1}$ 以及 $a_{i-2,j}$ 这三个格子中的老鼠数目。

汇总一下，在从 $a_{i-1,j-1}$ 转移（走）到 $a_{i-1,j}$ 再走（转移）到 $a_{i,j}$ 的情况下， $dp_{i-1,j,0}$ 至少包括了
 $a_{i-2,j-1},a_{i-1,j-2},a_{i-1,j-1},a_{i,j-1},a_{i-1,j},a_{i,j},a_{i-1,j+1}$ 以及 $a_{i-2,j}$ 这几个格子之中的老鼠总数目。

有些头晕？画一个表格或是平面直角坐标系对着看一看吧。

继续，我们发现原来需要考虑五格(上下左右中)的 $dp_{i,j}$ 这个格子现在继承一下 $dp_{i-1,j,0}$ 就等于继承了至少 3 格（ $a_{i-1,j},a_{i,j},a_{i,j-1}$），所以，$dp_{i,j,1} = dp_{i-1,j,0}+ $ 剩下两格 $a_{i+1,j}+a_{i,j+1}$。

呼！第一种情况总结完了，第二种呢？

第二种情况是从 $a_{i-2,j}$ 转移（走）到 $a_{i-1,j}$ 再转移（走）到 $a_{i,j}$ 中。

但，与之不同的是，$dp_{i-1,j,1}$ 并不包括 $a_{i,j-1}$。

> 想一想，为什么？

继续，我们发现原来需要考虑 5 格(上下左右中)的 $dp_{i,j}$ 这个格子现在继承一下 $dp_{i-1,j,1}$ 就等于继承了 2 格（$a_{i-1,j},a_{i,j}$)，所以，$dp_{i,j,1} = dp_{i-1,j,0}+$ 剩下两格  $a_{i+1,j}+a_{i,j+1}$。

所以，$dp_{i,j,1} = dp_{i-1,j,1}+$ 剩下 3 格 $a_{i+1,j}+a_{i,j+1}+a_{i,j-1}$。

最后一步了！我们把以上两种情况汇总一下就得到了以下方程式：
$$dp_{i,j,1} = \min(dp_{i-1,j,0}+a_{i+1,j}+a_{i,j+1},dp_{i-1,j,1}+a_{i,j-1}+a_{i+1,j}+a_{i,j+1})$$
再稍微简化一下：
$$dp_{i,j,1} = \min(dp_{i-1,j,0},dp_{i-1,j,1}+a_{i,j-1})+a_{i+1,j}+a_{i,j+1}$$

呼！恭喜恭喜！你已经推完了倒数第一部向下的情况了！
###### ~~所以接下来倒数第一步向右走的情况就不需要我再说了吧？~~

什么？你还蒙圈？

好的，再说说倒数第一步从左面转移过来的情况：

其实倒数第一步向右走的情况也分两种（倒数第二步向下或向右），而且推导方法和上面极为相似。好的，继续。

第一种：向右再向下。

即：从 $a_{i-1,j-1}$ 转移（走）到 $a_{i,j-1}$ 再走（转移）到 $a_{i,j}$ 中。

此时 $dp_{i,j-1,1}$ 已经覆盖了 $a_{i,j},a_{i,j-1},a_{i+1,j}$ 这 3 个位置的数。
所以，第一种情况中， $dp_{i,j,0} = dp_{i,j-1,0}+a_{i+1,j}+a_{i,j+1}$。

第二种：向右再向右。

即：从  $a_{i,j-2}$  转移（走）到 $a_{i,j-1}$ 再走（转移）到 $a_{i,j}$ 中。

此时 $dp_{i,j-1,0}$ 已经覆盖了 $a_{i,j},a_{i,j-1}$ 这两个位置的数。
所以，第二种情况中， $dp_{i,j,0} = dp_{i,j-1,0}+a_{i-1,j}+a_{i+1,j}+a_{i,j+1}$。

又是最后一步了！把以上两种情况汇总一下就得到了以下方程式：
$$dp_{i,j,0} = \min(dp_{i,j-1,1},dp_{i,j-1,0}+a_{i-1,j})+a_{i+1,j}+a_{i,j+1}$$

好了，第二种情况也讨论完了！把以上两个方程式整合一下然后隆重推出-----------------
$$dp_{i,j,0} = \min(dp_{i,j-1,1},dp_{i,j-1,0}+a_{i-1,j})+a_{i+1,j}+a_{i,j+1}$$
$$dp_{i,j,1} = \min(dp_{i-1,j,0},dp_{i-1,j,1}+a_{i,j-1})+a_{i+1,j}+a_{i,j+1}$$

#### 初始状态/边界条件

特殊的，
$$dp_{1,1,0} = a_{1,1}+a_{1,2}+a_{2,1}$$

$$dp_{1,1,1} = a_{1,1}+a_{1,2}+a_{2,1}$$

## 3.code&注意事项：
请注意：初始值最好赋值成正无穷。
#### code：

OK，接下来就是喜闻乐见的代码时间！

ACcode：
```cpp

#include<bits/stdc++.h>
using namespace std;
int main(){
	long long i,j,n,m,dp[1002][1002][3] = {0},a[1002][1002] = {0};
	cin>>n>>m;
	for(i = 1;i<=n;i++){
		for(j = 1;j<=m;j++){
			cin>>a[i][j];
			dp[i][j][0] = 999999999;
			dp[i][j][1] = 999999999;
		}
	}
	dp[1][1][0] = a[1][1]+a[1][2]+a[2][1];
	dp[1][1][1] = a[1][1]+a[1][2]+a[2][1];
	for(i = 2;i<=m;i++)dp[1][i][0] = dp[1][i-1][0]+a[1][i+1]+a[2][i];
	for(i = 2;i<=n;i++)dp[i][1][1] = dp[i-1][1][1]+a[i+1][1]+a[i][2];
	for(i = 2;i<=n;i++){
		for(j = 2;j<=m;j++){
			dp[i][j][1] = min(dp[i-1][j][0],dp[i-1][j][1]+a[i][j-1])+a[i+1][j]+a[i][j+1];
			dp[i][j][0] = min(dp[i][j-1][1],dp[i][j-1][0]+a[i-1][j])+a[i+1][j]+a[i][j+1];
		}
	}
	cout<<min(dp[n][m][0],dp[n][m][1])<<endl;
	return 0;
}
```
[祝你 AC ~](https://www.luogu.com.cn/record/106644610)


同时也感谢你看到结尾！附赠小彩蛋：50pts 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long i,j,n,m,dp[1002][1002] = {0},a[1002][1002] = {0};
	cin>>n>>m;
	for(i = 1;i<=n;i++){
		for(j = 1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	dp[1][1] = a[1][1]+a[1][2]+a[2][1];
	for(i = 2;i<=m;i++)dp[1][i] = dp[1][i-1]+a[1][i+1]+a[2][i];
	for(i = 2;i<=n;i++)dp[i][1] = dp[i-1][1]+a[i+1][1]+a[i][2];
	for(i = 2;i<=n;i++){
		for(j = 2;j<=m;j++){
			dp[i][j] = min(dp[i][j-1]+a[i-1][j],dp[i-1][j]+a[i][j-1])+a[i][j+1]+a[i+1][j];
			if(dp[i][j]==dp[i-1][j]+a[i][j-1]+a[i][j+1]+a[i+1][j] and 
			(dp[i-1][j]==dp[i-1][j-1]+a[i-2][j]+a[i-1][j+1]+a[i][j] or dp[i-1][j]+a[i-2][j]==dp[i-1][j-1]+a[i-2][j]+a[i-1][j+1]+a[i][j]))dp[i][j]-=a[i][j-1];
			/*
			This is for:
			----
			   ↓
			   ↓
			   ↓
			And This is for:
			↓
			↓
			↓
			→→→→	
			*/ 
			if(dp[i][j]==dp[i][j-1]+a[i-1][j]+a[i][j+1]+a[i+1][j] and (dp[i][j-1]==dp[i-1][j-1]+a[i][j]+a[i][j-2]+a[i+1][j-1] or dp[i][j-1]+a[i][j-2]==dp[i-1][j-1]+a[i][j]+a[i][j-2]+a[i+1][j-1]))dp[i][j]-=a[i-1][j];
		}
	}
//	cout<<endl;
//	for(i = 1;i<=n;i++){
//		for(j = 1;j<=m;j++){
//			printf("%02lld ",dp[i][j]);
//		}
//		cout<<endl;
//	}
	cout<<dp[n][m]<<endl;
	system("pause");
}
```

### 广告：
[Myblog](https://www.luogu.com.cn/blog/myj-cai/)


END~

---

## 作者：GNAQ (赞：6)

网格DP，注意是判重，看一下转移的时候哪些老鼠已经被数过了就好了。当前的位置之和上一步的位置和上上一步的位置有关，多开一位记录。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

int n,m;
int dp[1010][1010][2]={0};
int mapx[1010][1010]={0};
int wayx[4]={0,1,0,-1},wayy[4]={-1,0,1,0};

inline void readx(int& x)
{
	x=0; int k=1; register char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int main()
{
	freopen("data.in","r",stdin);
	
	memset(dp,0x3f,sizeof(dp));
	
	readx(n); readx(m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			readx(mapx[i][j]);
	
	dp[1][1][0]=dp[1][1][1]=mapx[1][1]+mapx[1][2]+mapx[2][1];
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) if (i*j!=1)
		{
			dp[i][j][0]=min(dp[i][j-1][0]+mapx[i-1][j],dp[i][j-1][1])+mapx[i+1][j]+mapx[i][j+1];
			dp[i][j][1]=min(dp[i-1][j][1]+mapx[i][j-1],dp[i-1][j][0])+mapx[i+1][j]+mapx[i][j+1];
		}
		
	printf("%d\n",min(dp[n][m][0],dp[n][m][1]));
	return 0;
}
```

---

## 作者：hzoi_liuchang (赞：4)

## 分析
很好的一道网格中的$DP$题

我们设$f[x][y]$为小象到达坐标为$(x,y)$的点时看到的最少的老鼠的数量

但是这样定义是不好转移的，因为小象可能从上面的格子转移下来，也可能从上面的格子转移过来

所以我们用三维数组记录状态，我们设$f[x][y][0]$为当前格子从正上方的格子转移过来所看到的最少的老鼠的数量

$f[x][y][1]$为当前格子从正左方的格子转移过来所看到的最少的老鼠的数量

我们来分情况讨论一下

无非是考虑当前的位置和当前上下左右的$4$个格子，去一下重

1、当前格子从正上方转移过来，当前格子正上方的格子也由正上方的格子转移过来

此时当前格子的价值$a[i][j]$已经在$f[i-1][j][0]$中计算过

而当前格子正上方的格子的价值$a[i-1][j]$已经在$f[i-2][j][0]$或$f[i-2][j][1]$中计算过

$$ f[i][j][0]=min(f[i][j][0],f[i-1][j][0]+a[i][j-1]+a[i][j+1]+a[i+1][j]);$$

2、当前格子从正上方转移过来，当前格子正上方的格子由正左方的格子转移过来

此时当前格子的价值$a[i][j]$已经在$f[i-1][j][1]$中计算过

当前格子正左方格子的价值$a[i][j-1]$已经在$f[i-1][j-1][1]$或$f[i-1][j-1][0]$中计算过

当前格子正上方格子的价值$a[i-1][j]$也已经在$f[i-1][j-1][1]$或$f[i-1][j-1][0]$中计算过

$$ f[i][j][0]=min(f[i][j][0],f[i-1][j][1]+a[i][j+1]+a[i+1][j]);$$

3、当前格子从正左方转移过来，当前格子正左方的格子也由正左方的格子转移过来

此时当前格子的价值$a[i][j]$已经在$f[i][j-1][1]$中计算过

当前格子正左方格子的价值$a[i][j-1]$已经在$f[i][j-2][1]$或$f[i][j-2][0]$中计算过

$$f[i][j][1]=min(f[i][j][1],f[i][j-1][1]+a[i-1][j]+a[i][j+1]+a[i+1][j]);$$

4、当前格子从正左方转移过来，当前格子正左方的格子由正上方的格子转移过来

此时当前格子的价值$a[i][j]$已经在$f[i][j-1][0]$中计算过

当前格子正左方格子的价值$a[i][j-1]$已经在$f[i-1][j-1][1]$或$f[i-1][j-1][0]$中计算过

当前格子正上方格子的价值$a[i-1][j]$也已经在$f[i-1][j-1][1]$或$f[i-1][j-1][0]$中计算过

$$f[i][j][1]=min(f[i][j][1],f[i][j-1][0]+a[i][j+1]+a[i+1][j]);$$

要注意初始化

$$ f[1][1][0]=f[1][1][1]=a[1][1]+a[1][2]+a[2][1];$$

## 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1055;
int a[maxn][maxn],f[maxn][maxn][3];
int main(){
    memset(f,0x3f,sizeof(f));
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&a[i][j]);
        }
    }
    f[1][1][0]=f[1][1][1]=a[1][1]+a[1][2]+a[2][1];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            f[i][j][0]=min(f[i][j][0],f[i-1][j][0]+a[i][j-1]+a[i][j+1]+a[i+1][j]);
            f[i][j][0]=min(f[i][j][0],f[i-1][j][1]+a[i][j+1]+a[i+1][j]);
            f[i][j][1]=min(f[i][j][1],f[i][j-1][1]+a[i-1][j]+a[i][j+1]+a[i+1][j]);
            f[i][j][1]=min(f[i][j][1],f[i][j-1][0]+a[i][j+1]+a[i+1][j]);
        }
    }
    printf("%d\n",min(f[n][m][0],f[n][m][1]));
    return 0;
}

```

---

## 作者：黑星 (赞：4)

蒟蒻考试的时候刚开始打了个暴力，然后玄学dp，dp本来是只考虑了当前点与下一个点的关系，后来发现没那么简单（好吧其实是样例都没过的原因），当前点与上一点都会影响下一点的老鼠值（因为每只老鼠只能见一次呀）   


------------
题目上说的看见老鼠的条件第一眼看上去很感jio很复杂（可能是我太弱了），实际上就是上下左右四个点

于是画图 ，发现有四种情况 

以下颜色说明，蓝色是第一个点，红色是移动一次后的点，黄色是移动两次后的点，被颜色覆盖的点说明该点的老鼠能被看见，有多种颜色的，说明被覆盖了多次

第一种，向下再向下（图画的丑，请求谅解）![](http://ae01.alicdn.com/kf/Had9667ca00d04988b40e8a67f3a15ab9i.png)

我们可以观察到，当前到达的点(x,y)（黄色），实际能看到的老鼠（在到达该点之前没有被看光），只有(x,y-1),(x,y+1),(x+1，y)的老鼠能看

所以，以此类推，向下再向右，向右再向下，向右再向右的点都可以找到规律啦（好吧是图太难画了）

当前点的老鼠与上个点与上上个点走的方向有关，所以我们设计两个状态，0往下走，1往右走

上代码（里面有注释）

```cpp
void work()
{
	//h[3]={1,0},l[3]={0,1},0是向下走，1是向下走
	//f[i][j][0/1]是到点(i,j)看老鼠的最小值 
	f[1][1][0] = f[1][1][1] = a[1][1]+a[2][1]+a[1][2]; //第一个点特殊处理 
	for(int i = 1;i <= n; i++)
	{
		for(int s = 1;s <= m; s++)
		{
			if(i==1 && s==1) continue;//起点怕出错，所以特判了一下 
			
			int li=i-h[0] , ls=s-l[0];//走下面 	
			if(li>0&&li<=n && ls>0&&ls<=m)
			f[i][s][0] = min(f[li][ls][0]+a[i+1][s]+a[i][s-1]+a[i][s+1] , f[li][ls][1]+a[i][s+1]+a[i+1][s]);
			//f[li][ls][0]+a[i+1][s]+a[i][s-1]+a[i][s+1] 上一个点是上上一个点走下边来的，剩下的都一样啦 
			//画图理解更好
			li=i-h[1] , ls=s-l[1]; //走右边
			if(li>0&&li<=n && ls>0&&ls<=m)
			f[i][s][1] = min(f[li][ls][0]+a[i][s+1]+a[i+1][s] , f[li][ls][1]+a[i-1][s]+a[i+1][s]+a[i][s+1]); 
		}
	}
}


蒟蒻第一次题解，如有错帮忙指出，谢谢巨佬们！！
```


---

## 作者：Last_Reincarnation (赞：2)

~~明天文化课考试，文化课蒟蒻在机房颓废， 且这道题还爆o了~~

看了一下题解，写的不够详细， 蒟蒻看不懂， 于是蒟蒻要写题解解释一下

进入正题

本题， 看完题面， 会想到搜索和$dp$


1.搜索 $20$ 分

dfs从（1， 1） 到（n， m）的所有路径， 更新答案
    
代码实现不是很难， 复杂度（不会算）
        
2.$dp$ $100$ 分

定义$map[i][j]$ 为格子（i，j） 上老鼠数量
    
$f[i][j][0]$表示当前小象位于格子(i,j)，且上一个位置是(i-1,j)所看见的老鼠的最少数量，即小象是从上面过来的
    
$f[i][j][1]$表示当前小象位于格子(i,j)，且上一个位置是(i,j-1)所看见的老鼠的最少数量，即小象是从左面过来的
    
    
转移方程
	
$f[i][j][0] = min(f[i-1][j][0] + map[i][j-1],f[i-1][j][1]) + map[i+1][j] + map[i][j+1]$
    
$f[i][j][1] = min(f[i][j-1][0],f[i][j-1][1] + map[i-1][j]) + map[i+1][j] + map[i][j+1]$


答案为  $min(f[n][m][0],f[n][m][1])$。

复杂度：$O(N*M)$

code
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define Re register
using namespace std;

const int inf = 0x3f3f3f3f;
const int maxn = 1010;

int n, m;
int map[maxn][maxn];
int f[maxn][maxn][2];

int f_;
char ch_;
template <class T>
	inline T read(T &x_){
		x_ = 0, f_ = 1, ch_ = getchar();
		while (ch_ < '0' || ch_ > '9'){if (ch_ == '-') f_ = -1; ch_ = getchar();}
		while (ch_ >= '0' && ch_ <= '9') x_ = (x_ << 3) + (x_ << 1) + ch_ - 48, ch_ = getchar();
		return x_ *= f_;
	} //快读
	
inline int Min(int X, int Y){
	if(X < Y) return X;
	return Y;
} //手写Min（习惯）

int main(){
	read(n);
	read(m);
	for (Re int i = 1;i <= n; ++i)
		for (Re int j = 1;j <= m; ++j){
			read(map[i][j]);
		}
	for (Re int i = 0;i <= n; ++i)
		for (Re int j = 0;j <= m; ++j){
			f[i][j][1] = f[i][j][0] = inf;
		} //边界一定要处理好
	f[1][1][1] = f[1][1][0] = map[1][1] + map[1][2] + map[2][1];
	for (Re int i = 1;i <= n; ++i)
		for (Re int j = 1;j <= m; ++j){
			if (i == 1 && j == 1) continue;
			f[i][j][0] = Min(f[i][j-1][0] + map[i-1][j], f[i][j-1][1]) + map[i+1][j] + map[i][j+1];
			// 0为上一个状态是从上面转移过来的，则其为上上个也是上面转移过来的 和 上一个是从左边转移过来的取小 
			f[i][j][1] = Min(f[i-1][j][1] + map[i][j-1], f[i-1][j][0]) + map[i+1][j] + map[i][j+1];
			// 1为上一个状态是从左边转移过来的，则其为上上个也从左边转移过来 和从上边转移过来取最小 
		}
	printf ("%d\n", Min(f[n][m][0], f[n][m][1])); 
	return 0; // 这是一个好习惯
}

```

~~明天考试估计GG了~~

完结.....



---

## 作者：smallpeter (赞：1)

## 题目大意

小象从 $(1,1)$ 出发，家在 $(n,m)$ 处。小象的害怕值定义为他回家的路径上可以看见的不同的老鼠的数量。若小象当前的位置为 $(x1,y1)$，小象可以看见老鼠，当且仅当老鼠的位置 $(x2,y2)$ 满足 $\left\vert x1-x2\right\vert+\left\vert y1-y2\right\vert\le1$。求小象到最小的害怕值。

$n,m\le1000$

## 解题思路

不难发现小象只能看到相邻格子（为四联通）和当前位置上的老鼠。

看到这题的数据范围不难想到用状态 $f_{i,j}$ 表示从起点 $(1,1)$ 到当前位置 $(i,j)$ 最小的害怕值。然后分两种情况讨论：

### 1、从左边过来的

那么 $f_{i,j}$ 就是 $\min(f_{i,j},f_{i,j-1}+new)$，其中 $new$ 表示新遇到的老鼠。

### 2、从上方过来的

那么 $f_{i,j}$ 就是 $\min(f_{i,j},f_{i-1,j}+new)$，$new$ 的定义同上。

不难发现现在唯一的问题就是怎么求 $new$（也就是新遇上的老鼠）。

一种很直接的想法就是 $new$ 为绿色方块上的数之和：（红色方块是上一步的 $new$，橙色方块是上两步的 $new$）

![](https://cdn.luogu.com.cn/upload/image_hosting/ngqfvtub.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/lczzsbuh.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/8mcinfgz.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/a746i9ii.png)

结果我们发现绿色方块的数量和位置不仅跟当前状态是由哪里转移过来的有关，还和上一步是由哪里转移过来的有关。所以我们把状态改进为 $f_{i,j,x}$。若 $x=0$ 则是由左边转移过来的，若 $x=1$ 则是由上面转移过来的。

那我们的状态转移就很好写了：

$$f_{i,j,0}=\min(f_{i,j-1,0}+a_{i-1,j}+a_{i,j+1}+a_{i+1,j},f_{i,j-1,1}+a_{i,j+1}+a_{i+1,j})$$
$$f_{i,j,1}=\min(f_{i-1,j,0}+a_{i+1,j}+a_{i,j+1},f_{i-1,j,1}+a_{i,j-1}+a_{i+1,j}+a_{i,j+1})$$

其中 $a_{i,j}$ 表示第 $i$ 行第 $j$ 列上老鼠的数量。

## 初始化

$$f_{1,1,0}=a_{1,1}+a_{1,2}+a_{2,1}$$
$$f_{1,1,1}=a_{1,1}+a_{1,2}+a_{2,1}$$

初始位置 $(1,1)$ 上小象只能看到 $(1,1),(1,2),(2,1)$ 上的老鼠。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define LL long long

const LL N=1e3+10;

LL n,m,a[N][N],v[N][N],f[N][N][2];

void scanff()
{
	scanf("%lld%lld",&n,&m);
	memset(a,0,sizeof(a));
	for(LL i=1;i<=n;i++)
	{
		for(LL j=1;j<=m;j++)
		{
			scanf("%lld",&a[i][j]);
		}
	} 
}

void init()
{
	memset(f,0x3f,sizeof(f));
	f[1][1][0]=f[1][1][1]=a[1][1]+a[2][1]+a[1][2];
}

void count()
{
	for(LL i=1;i<=n;i++)
	{
		for(LL j=1;j<=m;j++)
		{
			if(i==1&&j==1) continue;
			f[i][j][0]=min(f[i][j-1][0]+a[i-1][j]+a[i][j+1]+a[i+1][j],f[i][j-1][1]+a[i][j+1]+a[i+1][j]);
			f[i][j][1]=min(f[i-1][j][0]+a[i+1][j]+a[i][j+1],f[i-1][j][1]+a[i][j-1]+a[i+1][j]+a[i][j+1]);
		}
	}
}

void print()
{
	printf("%lld\n",min(f[n][m][0],f[n][m][1]));
}

void solve()
{
	scanff();
	init();
	count();
	print();
}

int main()
{
	LL T=1;
	while(T--)
	{
		solve();
	}
}
```

若有遗漏错误之处麻烦各位大佬指出。

---

## 作者：Celebrimbor (赞：1)

久违地水一发题解

### 题意描述

- 一个 $n\times m$ 的矩阵 $A$，从 $(1,1)$ 走到 $(n,m)$，取走到路线曼哈顿距离小于等于 $1$ 的位置上的权值，最小化该权值和。
- $1\leq n,m\leq 1000$，$1\leq A_{i,j}\leq 100$

### 分析

看数据范围，应该是个 $O(n^2)$ 的dp。若设计状态为 $dp_{i,j}$ 表示走到 $(i,j)$ 的最大值，转移时会存在问题。例如，从当前点上方转移至当前点时，当前点下方、右方的权值显然是一定要加上的，但左方点权值是否要加上，取决于先前路径上是否经过点 $(i-1,j-1)$，这就产生了后效性。

为消除后效性，考虑添加一维状态，取值 $0/1$，表示从左侧或上方转移过来。

于是可得方程：

$dp_{i,j,0} = min(dp_{i,j-1,0}+A_{i-1,j},dp_{i,j-1,1})+A_{i+1,j}+A_{i,j+1}$

$dp_{i,j,1} = min(dp_{i-1,j,1}+A_{i,j-1},dp_{i-1,j,0})+A_{i+1,j}+A_{i,j+1}$

注意处理边界，初始化为正无穷。

### 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 1005;
int n, m, A[MAXN][MAXN], dp[MAXN][MAXN][2];

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &(A[i][j]));
	memset(dp, 0x3f, sizeof(dp));
	dp[1][1][0] = dp[1][1][1] = A[1][1]+A[1][2]+A[2][1];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (i == 1 && j == 1) continue;
			dp[i][j][0] = min(dp[i][j-1][0]+A[i-1][j], dp[i][j-1][1])+A[i+1][j]+A[i][j+1];
			dp[i][j][1] = min(dp[i-1][j][1]+A[i][j-1], dp[i-1][j][0])+A[i+1][j]+A[i][j+1];
		}
	}
	printf("%d\n", min(dp[n][m][0], dp[n][m][1]));
	return 0;
}
```

良心数据，long long 都不用开。

---

## 作者：一只小兵 (赞：1)

~~我太弱了,DP就没做对过~~
## 思路
	这是一道DP的题,只不过连续的两次状态有一定的关联,所以需要在DP的过程中储存两个状态.
-------
## 思考过程

第一眼看到这道题的时候,以为是DP,打到一半发现当前状态与先前状态有关联,于是又重构了一份~~玄学的~~记忆化搜索 ~~(又打错了)~~ 就在模拟赛中暴零了  QAQ

其实这道题就是一个DP的题，当前节点的状态只会与先前一个节点有关（只会走最短路），所以维护先前的状态就可以开始DP了。

### 在给出状态转移方程前,先画图分析一波

~~免得等下看不懂~~

对于任意一个节点都存在两个可以转移的位置

![一个节点](https://cdn.luogu.com.cn/upload/pic/72693.png)

先对向右转移分析:右节点存在如下四个相关的节点,而四个相关的节点中只会和前一个节点的前一个节点(爷爷节点)有关联.

![向右转移](https://cdn.luogu.com.cn/upload/pic/72695.png)![关联分析](https://cdn.luogu.com.cn/upload/pic/72698.png)

向下转移同理

![向下转移](https://cdn.luogu.com.cn/upload/pic/72699.png)

由此可见对于每一次转移,都只与前两次节点有关.

所以我们需要转移前两个位置

----------

## 动态转移方程

终于到了~~最激动人心的~~动态转移方程

先对当前状态定义:
$f\lbrack k \rbrack \lbrack x \rbrack \lbrack y \rbrack$

k为0表示从上方节点转移到当前节点,为1表示从左方节点转移到当前节点

x,y 表示当前节点位置

### 动态转移方程:

1. 从上方的上方节点转移 

$f\lbrack 0 \rbrack \lbrack x \rbrack \lbrack y \rbrack$ $=$ $f\lbrack 0 \rbrack \lbrack x $-$ $1$ \rbrack \lbrack y \rbrack$ $+$ 当前节点的四周节点

2. 从上方的左方节点转移(注意会有关联节点)

$f\lbrack 0 \rbrack \lbrack x \rbrack \lbrack y \rbrack$ $=$ $f\lbrack 1 \rbrack \lbrack x $-$ $1$ \rbrack \lbrack y \rbrack$ $+$ 当前节点的四周节点

3. 从左方的左方节点转移

$f\lbrack 0 \rbrack \lbrack x \rbrack \lbrack y \rbrack$ $=$ $f\lbrack 1 \rbrack \lbrack x  \rbrack \lbrack y $-$ $1$ \rbrack$ $+$ 当前节点的四周节点

4. 从左方的上方节点转移

$f\lbrack 0 \rbrack \lbrack x \rbrack \lbrack y \rbrack$ $=$ $f\lbrack 0 \rbrack \lbrack x  \rbrack \lbrack y $-$ $1$ \rbrack$ $+$ 当前节点的四周节点

----------

## 核心代码

```cpp
	for(int i = 2 ; i <= n ; i++){
		for(int j = 2 ; j <= m ; j++){
			//从上方转移到目标节点
			int on = i-1,now_on;
			mouse_disappear(on,j);
			//从上方的上方节点转移 
			now_on = f[0][on][j];
			now_on += look_around(i,j);
			f[0][i][j] = min(f[0][i][j],now_on);
			//从上方的左方节点转移
			now_on = f[1][on][j];
			mouse_disappear(on,j-1);
			now_on += look_around(i,j);
			f[0][i][j] = min(f[0][i][j],now_on);
			mouse_appear(on,j-1);
			mouse_appear(on,j);
			//从左方转移到目标节点
			int left = j-1,now_left;
			mouse_disappear(i,left);
			//从左方的左方节点转移
			now_left = f[1][i][left];
			now_left += look_around(i,j);
			f[1][i][j] = min(f[1][i][j],now_left);
			//从左方的上方节点转移
			now_left = f[0][i][left];
			mouse_disappear(i-1,left);
			now_left += look_around(i,j);
			f[1][i][j] = min(f[1][i][j],now_left);
			mouse_appear(i-1,left);
			mouse_appear(i,left);
		}
	}
```
可能比较长~~不太会压行~~

## 最后附上AC代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e3+7;
long long read(){
	char ch = getchar();
	bool flag = true;
	while(ch < '0' || ch > '9') {
		if(ch == '-') flag = false;
		ch = getchar();
	}
	long long k = ch -'0';
	while(ch = getchar(), ch <= '9' && ch >= '0') {
		k = (k<<1)+(k<<3);
		k += (ch-'0');
	}
	if(flag) return k;
	return -k;
}
int n,m;
int tu[maxn][maxn],f[2][maxn][maxn];//f[][][]后两个位置，前一个表示从哪个状态到达 0表示从上方节点转移，1表示有左方节点到达 
int be_find[maxn][maxn];
int look_around(int x,int y){
	int cnt_m = 0;
	if(!be_find[x][y]) cnt_m += tu[x][y];
	if(x > 1 && !be_find[x-1][y]) cnt_m += tu[x-1][y];
	if(x < n && !be_find[x+1][y]) cnt_m += tu[x+1][y];
	if(y > 1 && !be_find[x][y-1]) cnt_m += tu[x][y-1];
	if(y < m && !be_find[x][y+1]) cnt_m += tu[x][y+1];
	return cnt_m;
}
void mouse_appear(int x,int y){//重新加入节点
	--be_find[x][y];
	if(x > 1) --be_find[x-1][y];
	if(x < n) --be_find[x+1][y];
	if(y > 1) --be_find[x][y-1];
	if(y < m) --be_find[x][y+1];
}
void mouse_disappear(int x,int y){//去除关联节点
	++be_find[x][y];
	if(x > 1) ++be_find[x-1][y];
	if(x < n) ++be_find[x+1][y];
	if(y > 1) ++be_find[x][y-1];
	if(y < m) ++be_find[x][y+1];
}
int main(){
	n=read(),m=read();
	for(int i = 1 ; i <= n ; i++){
		for(int j = 1 ; j <= m ; j++){
			tu[i][j] = read();
			f[0][i][j] = f[1][i][j] = 1e9+17;
		}
	}
	for(int i = 1 ; i <= n ; i++){
		f[0][i][1] = look_around(i,1)+f[0][i-1][1];
		mouse_disappear(i,1);
	}
	for(int i = 1 ; i <= n ; i++) mouse_appear(i,1);
	for(int i = 1 ; i <= m ; i++){
		f[1][1][i] = look_around(1,i)+f[1][1][i-1];
		mouse_disappear(1,i);
	}
	for(int i = 1 ; i <= m ; i++) mouse_appear(1,i);
	for(int i = 2 ; i <= n ; i++){
		for(int j = 2 ; j <= m ; j++){
			//从上方转移到目标节点
			int on = i-1,now_on;
			mouse_disappear(on,j);
			//从上方的上方节点转移 
			now_on = f[0][on][j];
			now_on += look_around(i,j);
			f[0][i][j] = min(f[0][i][j],now_on);
			//从上方的左方节点转移
			now_on = f[1][on][j];
			mouse_disappear(on,j-1);
			now_on += look_around(i,j);
			f[0][i][j] = min(f[0][i][j],now_on);
			mouse_appear(on,j-1);
			mouse_appear(on,j);
			//从左方转移到目标节点
			int left = j-1,now_left;
			mouse_disappear(i,left);
			//从左方的左方节点转移
			now_left = f[1][i][left];
			now_left += look_around(i,j);
			f[1][i][j] = min(f[1][i][j],now_left);
			//从左方的上方节点转移
			now_left = f[0][i][left];
			mouse_disappear(i-1,left);
			now_left += look_around(i,j);
			f[1][i][j] = min(f[1][i][j],now_left);
			mouse_appear(i-1,left);
			mouse_appear(i,left);
		}
	}
	printf("%d",min(f[1][n][m],f[0][n][m]));
	return 0;
}

```
### 最后说一点注意

- 注意当前是从哪个节点转移来的,关联节点去除









---

## 作者：Dehydration (赞：0)

### 前言：

最优解，想看有质量题解来这里。

[problem](https://www.luogu.com.cn/problem/P2295)。

[最优解](https://www.luogu.com.cn/record/list?pid=P2295&orderBy=1&status=&page=1)。

### 思路：

一眼 `DP` 大水题，与 `DP` 入门机器人相似，但唯一坑点就是要去重，要不是是一道蓝题，我才懒得推样例。

去重很简单，因为操作只能往下或者往右走，便可以记录当前是从上面下来还是从左边往右边来，所以有三维数组  $dp_{i,j,k}$ 表示在 $(i,j)$ 点看到的最小老鼠数量，$k=0$ 表示从上边下来，$k=1$ 表示从左边过来。






因为存在 $4$ 种情况，分别为左下，下下，左左和下左，所以我们对他们进行一一解决。

注：图中黑圈为 $(i,j)$，蓝圈为上一个点，紫圈为上上个点，红圈为已覆盖点，绿圈为可覆盖点。

![](https://cdn.luogu.com.cn/upload/image_hosting/h4q8k0yf.png)

于是愉快的给出从左边过来的式子：

```
            dp[i][j][0]=Min(dp[i][j][0],dp[i-1][j][0]+a[i][j-1]+a[i][j+1]+a[i+1][j]);
            dp[i][j][0]=Min(dp[i][j][0],dp[i-1][j][1]+a[i][j+1]+a[i+1][j]);
            dp[i][j][1]=Min(dp[i][j][1],dp[i][j-1][1]+a[i-1][j]+a[i][j+1]+a[i+1][j]);
            dp[i][j][1]=Min(dp[i][j][1],dp[i][j-1][0]+a[i][j+1]+a[i+1][j]);//Min为优化
```

明白了吗？于是上代码。

### 代码：

```
//I LOVE CHTHOLLY FOREVER!!!
#include<bits/stdc++.h>
#define r register
using namespace std;
inline int read()
{
	register int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}
inline void write(int X)
{
    if(X<0) {X=~(X-1); putchar('-');}
    if(X>9) write(X/10);
    putchar(X%10+'0');
}
inline int Min(r int x,r int y)
{
	return x>y?y:x;
}
int dp[1005][1005][2],a[1005][1005];
int main()
{
	r int n,m;
	cin>>n>>m;
	for(r int i=(1);i<=n;++i)for(r int j(1);j<=m;++j)a[i][j]=read();
	memset(dp,0x3f,sizeof(dp));
	dp[1][1][1]=dp[1][1][0]=a[1][1]+a[1][2]+a[2][1];
	for(r int i(1);i<=n;++i)
	{
		for(r int j(1);j<=m;++j)
		{
			dp[i][j][0]=Min(dp[i][j][0],dp[i-1][j][0]+a[i][j-1]+a[i][j+1]+a[i+1][j]);
            dp[i][j][0]=Min(dp[i][j][0],dp[i-1][j][1]+a[i][j+1]+a[i+1][j]);
            dp[i][j][1]=Min(dp[i][j][1],dp[i][j-1][1]+a[i-1][j]+a[i][j+1]+a[i+1][j]);
            dp[i][j][1]=Min(dp[i][j][1],dp[i][j-1][0]+a[i][j+1]+a[i+1][j]);//见上图
		}
	}
	write(Min(dp[n][m][0],dp[n][m][1]));
	return 0;
}
```


---

## 作者：猪龙骨丶丶 (赞：0)

对于一个点有2种情况，可能是从上走来或者从左边往右边走，且对于该点的上一个点也同样有2种情况。因为观察可知上一个点的情况不同，对于该点也会产生影响。用0表示该点是从上走到下，1表示从左走到右。
```
	dp[1][1][0]=dp[1][1][1]=g[1][1]+g[1][2]+g[2][1];
	for(int j=2;j<=m;j++)
		dp[1][j][1]=dp[1][j-1][1]+g[1][j+1]+g[2][j];
	for(int i=2;i<=n;i++
		dp[i][1][0]=dp[i-1][1][0]+g[i+1][1]+g[i][2];
	for(int i=2;i<=n;i++)
		for(int j=2;j<=m;j++){
			dp[i][j][0]=min(dp[i-1][j][0]+g[i][j-1]+g[i][j+1]+g[i+1][j],dp[i-1][j][1]+g[i][j+1]+g[i+1][j]);
			dp[i][j][1]=min(dp[i][j-1][1]+g[i-1][j]+g[i+1][j]+g[i][j+1],dp[i][j-1][0]+g[i+1][j]+g[i][j+1]);
		}
```


---

## 作者：sodak (赞：0)

本来想写二维，$f[i][j]$代表在第i行第j列的最优解，显然，这样写对于我这个蒟蒻来说很难，所以改成了三维$f[i][j][k]$,表示在第i行第j列，k用来表示从哪一状态转移过来，$k=1$代表从左边（即$i,j-1$）转移过来，$k=2$代表从上面（即$i-1,j$）转移过来，当前状态转移，只与上一状态和上上状态有关，结合图形，我们可以推得以下公式
```cpp
f[i][j][1]=min(f[i][j-1][1]+a[i-1][j]+a[i+1][j]+a[i][j+1],f[i][j-1][2]+a[i][j+1]+a[i+1][j]);
f[i][j][2]=min(f[i-1][j][2]+a[i][j-1]+a[i][j+1]+a[i+1][j],f[i-1][j][1]+a[i][j+1]+a[i+1][j]);
```

举个栗子，对于$f[i][j][1]$来说，它由$f[i][j-1][1]$和$f[i][j-1][2]$转移过来，一种是三个状态（当前状态，上一状态，和上上状态）横着排列，那么最新看到的老鼠为$a[i-1][j]$，$a[i+1][j]$，$a[i][j+1]$，另一种状态是上一状态由上上状态向下转移，当前状态由上一状态向右转移，那么新看到的老鼠只有$a[i][j+1]$，$a[i+1][j]$，很明显就可以看出来。
关于初始化，将f数组初始化为无穷大，dp的时候在$（1,1）$的位置特判一下就ok了

下面是代码（带注释）
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000+10;
int f[maxn][maxn][2];//维护三维dp数组
int a[maxn][maxn];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&a[i][j]);
		}
	}
	memset(f,0x7f,sizeof(f));//初始化
	for(int i=1;i<=n;i++){//枚举行数
		for(int j=1;j<=m;j++){//枚举列数
			if(i==1&&j==1){//特殊处理一下
				f[i][j][1]=a[i][j]+a[i+1][j]+a[i][j+1];
				f[i][j][2]=a[i][j]+a[i+1][j]+a[i][j+1];
			}
			else{//进行转移
				f[i][j][1]=min(f[i][j-1][1]+a[i-1][j]+a[i+1][j]+a[i][j+1],f[i][j-1][2]+a[i][j+1]+a[i+1][j]);
				f[i][j][2]=min(f[i-1][j][2]+a[i][j-1]+a[i][j+1]+a[i+1][j],f[i-1][j][1]+a[i][j+1]+a[i+1][j]);
			}
		}
	}
	printf("%d\n",min(f[n][m][2],f[n][m][1]));//最后在（n，m）位置的两个状态中取个最小值就ok了
}
```

---

## 作者：Vocanda (赞：0)

## 题目
[题目链接](https://www.luogu.com.cn/problem/P2295)
## 分析
经典的一个$dp$模型，这个题中给出了小象的移动方向，我们就可以预处理每个点能够看到的不同种老鼠数量，然后进行状态转移，首先定义状态数组为$f[i][j]$是到$i$行$j$列的害怕值。

题目中给出了小象会害怕的一个范围：
$$|x1-x2|+|y1-y2|\le 1$$
我们就可以根据这个推出来只有老鼠在小象的上下左右时才会害怕，然后开始预处理。

但是预处理也是有点门道的，我在开始预处理的时候想的是在当前点上下左右的都加起来，但是写完以后发现答案要大好多，仔细分析一下，我们可以发现几个特点：

$1$、当前点由左边或上边转移而来，所以左边或上边已经能够看到当前点的左边和上边的点，所以只需要预处理该点下和右边的数量。

$2$、当前点是从左或上转移而来，如果上边的点仍然从上边转移来，那么该点的左边一定是没有统计过的，而从左边转移来的点上一次转移还是左边也是一样的，该点上边的点一定没有统计，所以我们就需要第三维来记录从左还是上转移而来。数组也就变成了$f[i][j][1]$，和$f[i][j][0]$，分别表示从左边来还是从右边来。如果一直从左转移，那么需要加上上边的害怕值，从上同理。

那么我们这样就得到了状态转移方程和预处理。预处理$val[i][j]$数组表示第$i$行$j$列会得到的害怕值，根据上边的分析得到只需要看这个点右边和下边即可。然后就是状态转移方程：
$$f[i][j][1] = min(f[i][j-1][1]+val[i][j]+a[i-1][j],f[i][j-1][0]+val[i][j]);$$
$$f[i][j][0] = min(f[i-1][j][1]+val[i][j],f[i-1][j][0]+val[i][j]+a[i][j-1]);$$

最后只需要比较$f[i][j][1]$和$f[i][j][0]$的最小值就好了。

## 代码
```cpp


#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e3+10;
int a[maxn][maxn],f[maxn][maxn][3];
int val[maxn][maxn];
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=0;i<=n;++i){
		for(int j=0;j<=m;++j){
			if(a[i][j+1] != 0)val[i][j]+=a[i][j+1];//加上右边的老鼠
			if(a[i+1][j] != 0)val[i][j]+=a[i+1][j];加上下边的老鼠
		}
	}
	memset(f,0x3f,sizeof(f));//初始化极大值
	f[1][0][0] = f[1][0][1] = val[1][0];//边界初始化
	f[0][1][0] = f[0][1][1] = val[0][1];
	f[1][1][0] = f[1][1][1] = 0;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			f[i][j][1] = min(f[i][j-1][1]+val[i][j]+a[i-1][j],f[i][j-1][0]+val[i][j]);//从左转移来
			f[i][j][0] = min(f[i-1][j][1]+val[i][j],f[i-1][j][0]+val[i][j]+a[i][j-1]);//从上转移来
		}
	}
	int ans = min(f[n][m][1],f[n][m][0]);//统计最小值
	printf("%d\n",ans);
	return 0;
}

```


---

## 作者：Boxxxxxx (赞：0)

[博客链接](https://blog.csdn.net/qq_43804974/article/details/104259770)

很水的dp，~~用于在你蓝题dp做疯了的时候来提高下信心。~~ 


首先那个距离就是曼哈顿距离，所以小于等于1的格子就是当前格子的上下左右，还包含自身。

其实唯一的问题就是如何计算贡献的时候不要算重复了，那么分情况考虑就可以不算重复，f[i][j][0]代表到达ij点的走法是从上面走下来，f[i][j][1]代表到达ij点的走法是从左边走过来。

那么到达ij点后，有向下走和向右走，当你画出了图，就什么都知道了。

黑色线代表的是当前的ij节点以及他旁边被算过的格子。

蓝色线代表的是走到ij点的那个点在哪里（上面还是左边），和他旁边被算过的格子。

红色线代表的是ij点下一步怎么走，以及他所需要计算的格子。

黄色荧光笔就是你需要新计算的内容啦（没有画到的内容你看是不是都已经被其他的格子覆盖过一次了呢？）

有了这个图，我相信方程就是大家都会写了，只需要走的那一步加上黄色荧光笔所在格子的贡献就可以啦。
![](https://cdn.luogu.com.cn/upload/image_hosting/m30l3ivf.png)

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<time.h>
#include<string>
#include<cmath>
#include<map>
#include<set>
#define ll long long
//#define double long double
using namespace std;
const long long max_ = 1000 + 7;
const int mod = 1e9 + 7;
const int inf = 1e9;
const long long INF = 1e18;
int read() {
	int s = 0, f = 1;
	char ch = getchar();
	while (ch<'0' || ch>'9') {
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0'&&ch <= '9') {
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * f;
}

int min(int a, int b) {
	return a < b ? a : b;
}
int max(int a, int b) {
	return a > b ? a : b;
}
int node[max_][max_],f[max_][max_][5];
int main() {
	int n = read(), m = read();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			node[i][j] = read();
		}
	}
	memset(f, 1, sizeof(f));
	f[1][1][0] = f[1][1][1] = node[1][1] + node[1][2] + node[2][1];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			f[i+1][j][0] = min(f[i][j][0] + node[i + 1][j + 1] + node[i + 1][j - 1] + node[i + 2][j], f[i + 1][j][0]);
			f[i][j + 1][1] = min(f[i][j][0] + node[i][j + 2] + node[i + 1][j + 1], f[i][j + 1][1]);

			f[i + 1][j][0] = min(f[i][j][1] + node[i + 1][j + 1] + node[i + 2][j], f[i + 1][j][0]);
			f[i][j + 1][1] = min(f[i][j][1] + node[i-1][j + 1] + node[i][j + 2] + node[i+1][j+1], f[i][j + 1][1]);
		}
	}
	cout << min(f[n][m][0],f[n][m][1]);
	return 0;
}
```



---

