# [USACO15OPEN] Palindromic Paths G

## 题目描述

Farmer John 的农场是一个 $N \times N$ 的网格（$1 \le N \le 500$），每个格子标有一个字母。例如：

```
ABCD
BXZX
CDXB
WCBA
```

每天，奶牛 Bessie 从左上角的格子走到右下角的格子，每一步只能向右或向下移动一个格子。Bessie 会记录下她走过的路径所生成的字符串，这个字符串由她经过的格子上的字母组成。然而，如果这个字符串是一个回文串（即正读和反读相同），她会感到非常困惑，因为她会分不清自己走过的方向。请帮助 Bessie 计算她可以走的不同路径中，对应回文串的数量。即使生成相同回文串的方式不同，也需要分别计数。请输出答案对 1,000,000,007 取模的结果。

## 说明/提示

Bessie 可以生成以下回文串：

- 1 个 "ABCDCBA"
- 1 个 "ABCWCBA"
- 6 个 "ABXZXBA"
- 4 个 "ABXDXBA"

## 样例 #1

### 输入

```
4
ABCD
BXZX
CDXB
WCBA```

### 输出

```
12```

# 题解

## 作者：ouuan (赞：18)

思路和其它题解大致相同，本题解主要是详细说明状态转移方式以及和其它题解不同的滚动数组方式。

### 总体思路

因为是回文串，所以不如从左上角和右下角同时向中间走，每一步必须走字母相同的格子，最后到中间汇合就可以得到方案数了。

如果分别枚举两个点的坐标则是O(n^4)的，会超时，但可以看出步数相同时两个点的横纵坐标和有一定规律，分别为2+step和2n-step，因此只要枚举步数和两点纵（横）坐标即可。

### 状态表示

f(i,j,k)表示:

- 走了i步
- 左上的点纵坐标为j
- 右下的点纵坐标为k

的方案总数

### 状态转移

因为只有两点字母相同时才能走，因此当两点字母不同时方案数为0，否则为每个可以走过来的状态的方案数之和，即：

当a[j][i+2-j]==a[k][n*2-i-k]时f(i,j,k)=f(i-1,j,k)+f(i-1,j-1,k)+f(i-1,j,k+1)+f(i-1,j-1,k+1)，否则f(i,j,k)=0

### 空间优化

这题数据范围到了500，如果开500^3的数组会MLE

考虑到每次状态转移只需用到f(i-1,j,k)，可以用滚动数组优化空间

因为每次转移只会用到j、j-1、k、k+1，逆序枚举j、正序枚举k即可避免覆盖还未转移的状态。

### 代码

```
#include <iostream>

const int M=1000000007; //记得取模

using namespace std;

char a[510][510];
int n,f[510][510],ans;

int main()
{
    int i,j,k;
    
    cin>>n;
    
    for (i=1;i<=n;++i)
    {
        for (j=1;j<=n;++j)
        {
            cin>>a[i][j];
        }
    }
    
    if (a[1][1]==a[n][n]) //若左上角和右下角不同则直接输出0
    {
        f[1][n]=1; //初始化状态，两个点分别在左上角和右下角时方案数为1
        for (i=1;i<=n-1;++i)
        {
            for (j=i+1;j>=1;--j) //逆序枚举j
            {
                for (k=n-i;k<=n;++k) //正序枚举k
                {
                    if (a[j][i+2-j]==a[k][n*2-i-k]) //只有两点所在字母相同时才能转移
                    {
                        f[j][k]=(1ll*f[j][k]+f[j-1][k]+f[j][k+1]+f[j-1][k+1])%M; //1ll*是为了避免爆int，把数组开为long long也可以
                    }
                    else
                    {
                        f[j][k]=0;
                    }
                }
            }
        }
        
        for (i=1;i<=n;++i)
        {
            ans=(ans+f[i][i])%M; //只有最后到同一点才计入答案
        }
    }
    
    cout<<ans;
    
    return 0;
}
```

---

## 作者：米奇奇米 (赞：6)

## 题解-P3126 USACO15OPEN 回文的路径

### 双倍经验:[戳这里](https://www.luogu.org/problemnew/show/CF570E)

### 题目意思：
让你求出图中有多少条回文路径。

### $DP$
* 状态：$f[s][i][j][k][p]$表示走了$s$步，$A$在$(i,j)$位置，$B$在$(k,p)$位置的方案数。

但是显然这样设计状态会时空双爆，于是我们要优化状态

* 优秀的状态：$f[s][x][y]$表示走了$s$步，$A$在$x$行，$B$在$y$行的方案数（然后再把$s$滚掉）

**为什么这样的设计是正确的的呢？**

因为我们知道了在哪一行以及走的步数是可以计算出在哪一列的。

* 转移：$f[v][i][j]=(f[v][i][j]+$
$f[v$^$1][i-1][j+1]+f[v$^$1][i-1][j]+f[v$^$1][i][j+1]+f[v$^$1][i][j])$

这个转移很好想的吧，因为它可以从上/下-左/右转移过来

* 统计答案：

因为$(n+m)$&$1$不一定为$0$所以要分类讨论，

对于$(n+m)$为奇数的情况答案为 $∑(f[v][i][i]+f[v][i][i+1])$

否则为$∑(f[v][i][i])$



---

## 作者：listenteresaX (赞：5)


思路与其它题解大致相同,只是从中间（对角线）往两头走

从(1,n)到(n,1)画一条对角线，对角线上的点横纵坐标之和为n+1， 

设对角线上左上的点横纵坐标之和为k1 

设对角线上右下的点横纵坐标之和为k2

那么回文便是要求横纵坐标之和(n+1)-k1=k2-(n+1) 的某点对字母相同了

转念，k1=(n+1)-x,k2=(n+1)+x, x属于[1,n-1]
便有如上dp了 

原谅这奇异~~抽风~~的代码君


```
#include<bits/stdc++.h>
using namespace std;
int n,s,t,k1,k2;
long long f[2][505][505];
char c[505][505];
#define mod 1000000007
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	scanf("%s",c[i]+1);
	for(int i=1;i<=n;i++)
	f[(n+1)%2][i][i]=1;//只长一个字母时的初始化
	k1=n;k2=n+2;//坐标和
	for( ;k1>=2;k1--,k2++)
	{
		memset(f[k1%2],0,sizeof(f[k1%2])); 
		for(int i=1;i<=k1-1;i++)//k1的横坐标
		for(int j=k2-n;j<=n;j++)//k2的横坐标
		if(c[i][k1-i]==c[j][k2-j])
		f[k1%2][i][j]=(f[(k1+1)%2][i][j-1]+f[(k1+1)%2][i][j]+f[(k1+1)%2][i+1][j-1]+f[(k1+1)%2][i+1][j])%mod;
	}
	cout<<f[0][1][n]<<endl;//(1,1),(n,n)坐标和%2自然为0
	return 0;
}

```

---

## 作者：MattL (赞：4)

[题目链接](https://www.luogu.com.cn/problem/P3126) [双倍经验](https://www.luogu.com.cn/problem/CF570E)

这题其实叫回文路径……

---

### **题意：**

有个人分别从左上往右下走，问有多少条路经是回文的。

---
### **分析**

这种题是多进程动规题。（[同类题](https://www.luogu.com.cn/paste/9zlg23m6)）

多进程动规，顾名思义，就是有多个同时进行的动规。

像这题，可以理解成有两个人同时从左上和右下开始，向中间集合，问有多少种走法，两人所经过的路径构成的字符串，有多少种走法是一样的。

---

### **动规分析：**

**1级算法**

数组： $f_{s,x1,y1,x2,y2}$ 表示走了s步，从左上和右上来的人的坐标分别为 $x1,y1$ 和 $x2,y2$ 。

转移方程： 
$$f_{s,x1,y1,x2,y2}=f_{s-1,x1-1,y1,x2+1,y2}+f_{s-1,x1,y1-1,x2,y2+1}+f_{s-1,x1-1,y1,x2,y2-1}+f_{s-1,x1,y1-1,x2+1,y2}$$

循环：枚举 $s,x1,x2,y1,y2$ 。

复杂度：时间 $O(n^5)$ ，空间 $O(n^5)$ ，明显时、空双爆。

---
**2级算法**

数组： $f_{s,x1,x2}$ 表示走了s步，从左上和右上来的人的行坐标分别为 $x1$ 和 $x2$ 。

转移方程： 
$$f_{s,x1,x2}=f_{s-1,x1-1,x2+1}+f_{s-1,x1-1,x2}+f_{s-1,x1,x2+1}+f_{s,x1,x2}$$

循环：枚举 $s,x1,x2$ 。

优化来源：可以根据 $s,x1,x2$ 推出 $y1$ 和 $y2$ 。

复杂度：时间 $O(n^3)$ ，空间 $O(n^3)$ ，时间勉强过，空间会爆。

---

**3级算法**

数组： $f_{x1,x2}$ 表示从左上和右上来的人的行坐标分别为 $x1$ 和 $x2$ 。

转移方程： 
$$f_{x1,x2}=f_{x1-1,x2+1}+f_{x1-1,x2}+f_{x1,x2+1}+f_{x1-1,x2+1}$$

循环：枚举 $s,x1$ （逆序） $,x2$ 。

优化来源：可以根据转移方程把 $s$ 这维压了。

复杂度：时间 $O(n^3)$ ，空间 $O(n^2)$ ，时、空双过。

---

**细节见代码↓**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
char a[555][555];
int n,f[555][555],ans;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    	for(int o=1;o<=n;o++)
    		cin>>a[i][o];//输入字符矩阵
    if(a[1][1]==a[n][n])//小优化，头尾不一样直接输出0
    {
        f[1][n]=1;//初始化，在起点时有1条方案
        for(int i=1;i<=n-1;i++)//枚举走了多少步
            for(int o=i+1;o>=1;o--)//左上角来的行坐标
                for(int u=n-i;u<=n;u++)//右下角来的行坐标
                    if (a[o][i+2-o]==a[u][n*2-i-u])//两边的字符一样
                        f[o][u]=(1ll*f[o][u]+f[o-1][u]+f[o][u+1]+f[o-1][u+1])%mod;//转移方程和定义见上文解释，1ll是防爆的，还有别忘了取模
                    else
                        f[o][u]=0;//不一样直接取0
        for(int i=1;i<=n;i++)//结束后要走在一起
            ans=(ans+f[i][i])%mod;
    }
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：littleming (赞：4)

https://li-mi.github.io/2017/06/02/Usaco2015-Open-Gold-Palindromic-Paths/

哇哇哇本人蒟蒻做了好久其实不难。。

n=500。。好像只用O(n^3)的方法可以过。。

那就dp吧，从（1,1）和（n,n）同时向中间走（lz的第一反应是双向bfs，超时，改成从两头的dp）

状态大概就是dp（i,j,k,l），表示走到（i,j）和（k,l）时的方案数，转移↓

dp[i][j][k][l]=dp[i-1][j][k+1][l]+dp[i-1][j][k][l+1]+dp[i][j-1][k+1][l]+dp[i][j-1][k][l+1]

但是好像会超时超空间。。状态得修改一下↓

时间优化：既然是从两头同时走，可以记一下走的步数，再留一个i和k就可以了，这样就变成O(n^3)。

dp（s,i,k）像这样就可以了。。

lz在网上看到了另一种状态设计↓

dp[i][j][k]表示左上结束节点是第i条副对角线上的第j个点，右下结束节点是第n\*2-i条副对角线上的第k个点，构成回文的方案数。（引用地址：http://www.cnblogs.com/czllgzmzl/p/5645030.html）

其实，我也是按照这位大佬的方法做的，因为k表示起来简单啊（但也有麻烦的地方）

转移为dp[s][i][k]=dp[s-1][i-1][k-1]+dp[s-1][i-1][k]+dp[s-1][i][k-1]+dp[s-1][i][k]

完了吗？

有没有发现要开500^3的数组，爆空间了。。

空间优化：dp最常见的空间优化–>滚动数组（能状压的大佬请无视蒟蒻）

第一维好像只需要2个（每次只跟前一次状态有关），这样就可以压了


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MOD=1000000007;
int n;
LL dp[2][508][508],ans;
char a[508][508];
bool now,pre;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)    cin>>a[i]+1; 
    if(a[1][1]!=a[n][n]){
        cout<<'0';
        return 0;
    }
    now=1;pre=0;
    dp[now][1][1]=1;
    for(int step=3;step<=n+1;step++){//从第二条副对角线到第n+1条，就是走的步数
        swap(now,pre);
        for(int i=1;i<step;i++){
            for(int k=1;k<step;k++){
                if(a[i][step-i]==a[n-step+1+k][n-k+1])//细心地推一下右下角点的坐标，容易错
                    dp[now][i][k]=(dp[pre][i-1][k-1]+dp[pre][i-1][k]+dp[pre][i][k-1]+dp[pre][i][k])%MOD;
                else    dp[now][i][k]=0;//滚动数组一定要清零，不然后面会误用前面的值
            }
        }
    }
    for(int i=1;i<=n;i++)    ans=(ans+dp[now][i][i])%MOD;
    cout<<ans;
    return 0;
}
```

---

## 作者：Augen_stern (赞：3)

### Part 1 算法分析

坐标类 DP 一道

首先，直接可以想到朴素算法：

暴力枚举每一条路径，然后一条一条地判断是否回文，可是在一张 $500\times 500$ 的地图上，从 $(1,1)$ 到 $(500,500)$ 共 896,346,411,204,565,376 种路径，可以明显看出这种算法是不可取的；

所以我们尝试 DP:

1，因为要使最后的路径回文，所以如果 $(1,1)$ 和 $(n,n)$ 的字符不同，则直接输出 0 ，并结束程序；

2，路径长度为 $2\times n-1$ ,必定为奇数，所以其中间点为这张图的一条对角线（非从 $(1,1)$ 到 $(n,n)$）；

3，然后我们可以从上边和下边一起搜，一样则可以状态转移，否则等于 0。

### Part 2 问题解决

很容易可以推出动态转移方程：
```cpp
f[j][k]=(f[j][k]+f[j-1][k]+f[j][k+1]+f[j-1][k+1])%mod;
```
$f(j,k)$ 表示左上的点纵坐标为 $j$ 右下的点纵坐标为 $k$ 的方案总数。

（这里省略了走 $i$ 步）

### Part 3 CODE

```cpp
#include<iostream>
#include<math.h>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define INF 0x7fffffff/2
using namespace std;
int n,m;
char map[505][505];
long long f[505][505]; // 不开龙龙见祖宗 
long long mod=1000000007;
long long ans=0; 
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			cin>>map[i][j];
		}
	}
	if(map[1][1]!=map[n][m]) { // 特判 
		printf("0\n");
		return 0;
	}
	f[1][n]=1; // 初始化 
	for(int i=1; i<n; i++) { // 枚举步数 
		for(int j=i+1; j>=1; j--) { // 逆向枚举 
			for(int k=n-i; k<=m; k++) { // 正向枚举 
				if(map[j][i+2-j]==map[k][2*n-i-k]) {
					f[j][k]=(f[j][k]+f[j-1][k]+f[j][k+1]+f[j-1][k+1])%mod; // 别忘了取 mod  
				} else f[j][k]=0;
			}
		}
	}
	for(int i=1; i<=n; i++) ans=(ans+f[i][i])%mod; // 只有最后到同一个点才记作一组答案 
	printf("%lld\n",ans);
	return 0;
}
```

自给自足，丰衣足食！！！

2021.8.23 12:55 第一次初稿成；

2021.8.25 13.10 完善了排版；

2021.8.25 17:00 再次完善了排版。

---

## 作者：Randolph、 (赞：3)

[P3126 [USACO15OPEN]回文的路径Palindromic Paths](https://www.luogu.org/problemnew/show/P3126)

看到这题题解不多，蒟蒻便想更加通俗易懂地分享一点自己的心得，欢迎大佬批评指正^_^

像这种棋盘形的两边同时做的dp还有
[P1006 传纸条,](https://www.luogu.org/problemnew/show/P1006)
[P1004 方格取数,](https://www.luogu.org/problemnew/show/P1004)
[T35377 大教室中传纸条](https://www.luogu.org/problemnew/show/T35377)

## 一、思路改进

对于这种题目最暴力的方法无非是分别枚举左上角和右下角两点坐标（**f[ i ][ j ][ k ][ l ]=f[ i-1 ][ j ][ k+1 ][ l ]+f[ i-1 ][ j ][ k ][ l+1 ]+f[ i ][ j-1 ][ k+1 ][ l ]+f[ i ][ j-1 ][ k ][ l+1 ]**）一起往中间走，即当两个点重合时便有了路径——O（n^4），像这种数据较大的题会爆

于是便有了新的思路，**由于两点是一起走的，步数相同，所以可以枚举步数，又因为横纵坐标之和等于所走路径长+1（横纵坐标会重合一点，可以看下图理解）**,所以只需枚举两点的横坐标（j，k）就可以求出两点的纵坐标

|  | 1 |2  | 3 | 4 |5  |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 1 | 左上角 |  |  |  |E|
| 2 |  |  |  | D |  |
| 3 |  |  |C  |  |  |
| 4 |  |B |  |  |  |
| 5 |A  |  |  |  | 右下角 |

i表示步数（注：**左上角和右下角只有一种走法，我们可以从第二步开始走，又因为横纵坐标重合一点，为了使横坐标+纵坐标=i，我们可以从3开始枚举**）

上图字母是路径长为5，i（所枚举的步数）为5+1=6的情况

设j为左边点的横坐标（纵坐标为i-j），**k为右边点所走路径的竖直长【如上图点A，枚举到它时k为1，横坐标为n-(i-k)+1=n-i+k+1=5-6+1+1=1，纵坐标为n-k+1=5-1+1=5】**

即f（i,j,k）=f（i-1,j,k）+f（i-1,j-1,k）+f（i-1,j,k-1）+f（i-1,j-1,k-1）【j-1，而i不变，说明点的纵坐标+1，其实这个式子与上面暴力的式子是一样的】

## 二、空间优化

然而，这题数据范围到了500，如果开500^3的数组会MLE，考虑到每次状态转移只需用到f(i-1,j,k)，可以用滚动数组优化空间

逆序枚举j、k【**f[j][k]=f[j][k]+f[j-1][k-1]+f[j-1][k]+f[j][k-1]等式左侧步数为i，而右侧其实是上次枚举的状态，步数为i-1**】（与01背包的滚动数组优化同理）即可避免覆盖还未转移的状态。

## 三、代码

只有两点字母相同时才能走，因此当两点字母不同时方案数为0，否则为每个可以走过来的状态的方案数之和

具体细节可以在代码中进一步理解
```cpp
#include<iostream>
#define rint register int
using namespace std;
char a[501][501];
int n;
long long f[501][501],ans;
int main() {
    cin>>n;
    for (int i=1; i<=n; i++)
        for (int j=1; j<=n; j++)
            cin>>a[i][j];
    if (a[1][1]!=a[n][n]) {
        cout<<0;
        return 0;
    }//如果左上角和右下角字母不同则无解
    f[1][1]=1;//当两点分别处于左上角和右下角时方案为1
    for (rint i=3; i<=n+1; i++)
        for (rint j=i-1; j>=1; j--)
            for (rint k=i-1; k>=1; k--) {
                if (a[j][i-j]==a[n-i+k+1][n-k+1])//（用j，k分别求出所对应的横纵坐标）此两点字母是否相同？
                    f[j][k]=(f[j][k]+f[j-1][k-1]+f[j-1][k]+f[j][k-1])%1000000007;
                else f[j][k]=0;//不相同则方案为0
            }
    for (int i=1; i<=n; i++)//统计所有方案数
        ans=(ans+f[i][i])%1000000007;//当j=k说明两点重合
    cout<<ans;
}
```


---

## 作者：yx666 (赞：1)

# P3126 Palindromic Paths G 题解
## Part 1：题意
### Part 1.1：题干
给定一个 $n$ 行 $n$ 列的填满字符的矩形，从 $(1,1)$ 出发，每次只能向下或向右移动一步。

求出以 $(1,1)$ 为开头，$(n,n)$ 为结尾，且为回文字符串的路径数量（结果对 $10^9+7$ 取模）。

### Part 1.2：限制
- $n\footnotesize\in[2,500]$。

- 时限 $1$ 秒。  

- 空间 $125$ MB。

### Part 1.3：相似题目
[CF570E](https://www.luogu.com.cn/problem/CF570E)，数据范围相同，时限、空间增大，唯一不同的是矩形是 $n$ 行 $m$ 列。$n$、$m$ 可能不同（故在枚举答案上有一定差别）。

## Part 2：分析
$n\footnotesize\in[2,500]$，显然不是搜索（~~或者我打不出来~~），尝试分析 DP。

### Part 2.1：定义问题状态
和 [方格取数](https://www.luogu.com.cn/problem/P1004) 类似，均为坐标 DP。

把题意抽象成有两个小人，一个从 $(1,1)$ 出发到 $(i,j)$，一个从 $(n,n)$ 出发到 $(x,y)$ 处，要求两人走过的路径（字符串）相等。

所以，定义 $f_{i,j,x,y}$ 表示两个小人分别在 $(i,j)$ 处与 $(x,y)$ 处时路径相同的情况总数。

显然，$i,j,x,y\footnotesize\in[2,500]$ 空间会爆炸。结合 [方格取数](https://www.luogu.com.cn/problem/P1004) 的思想，开始优化空间复杂度。

重新定义 $f_{s,i,j}$ 表示两个小人走了 $s$ 步后，横坐标分别为 $i,j$ 时路径相同的情况总数。

现在空间复杂度 $O(n^3)$，$n\footnotesize\in[2,500]$，基本不会炸了（下面还会优化）。

### Part 2.2：状态转移方程
#### Part 2.2.1：无滚动优化
稍微推一下，就能得到 $f_{s,i,j}$ 时，小人分别在 $(i,s-i+1)$ 与 $(j,2n-s-j+1)$ 处。

记 $p= s-i+1$，$q=2n-s-j+1$，$mp_{i,j}$ 表示 $(i,j)$ 处的字符，则得到状态转移方程：

$$f_{s,i,j}=\begin{cases}0 &mp_{i,p}\ne mp_{j,q}\\f_{s-1,i-1,j}+f_{s-1,i,j+1}+f_{s-1,i-1,j+1}+f_{s-1,i,j}&mp_{i,p}=mp_{j,q}\end{cases}$$

#### Part 2.2.2：有滚动优化
发现 $f_{s,i,j}$ 只依赖于前一项，可滚动优化。

记 $now\gets s\bmod 2$，$bef\gets (s-1)\bmod 2$，这样可以保证 $now,bef\in[0,1]$ 且 $now\neq bef$。

其余不变，得到方程：

$$f_{now,i,j}=\begin{cases}0 &mp_{i,p}\ne mp_{j,q}\\f_{bef,i-1,j}+f_{bef,i,j+1}+f_{bef,i-1,j+1}+f_{bef,i,j}&mp_{i,p}=mp_{j,q}\end{cases}$$

### Part 2.3：初始化与边界状态
1. $f_{1,1,n}\gets1$，其余的初始化为 $0$。

2. 最多能向下走 $n$ 步，向右走 $n$ 步，再加之是双向走，所以 $s\footnotesize\in[1,n]$。

### Part 2.4：计算顺序
对于 $f_{s,i,j}$：

1. 外层：$s\footnotesize\in[1,n]$，$s$ 递增。特别的，$s=1$ 时，$f_{1,1,n}\gets1$。

2. 中层：$i\footnotesize\in[1,\min(n,s)]$，递增。

3. 内层：$j\footnotesize\in[\max(n-s,i),n]$，递增。

代码写成下面这样：

``` cpp
f[1][1][n]=1;
int now=1,bef=0;
for(int s=2;s<=n;++s){
	now^=1;bef=now^1;
	memset(f[now],0,sizeof f[now]);
	
	for(int i=1;i<=min(n,s);++i){
		int p=s-i+1;
		for(int j=n;j>=max(n-s,i);--j){
			int q=n+m-s-j+1;
			
			if(mp[i][p]==mp[j][q]){
				f[now][i][j]=f[bef][i-1][j]+f[bef][i][j+1]+f[bef][i-1][j+1]+f[bef][i][j];
				f[now][i][j]%=MOD;
			}
		}
	}	
}
```
### Part 2.5：答案
可以理解为扫一遍对角线。

$$ans=\left(\sum^n_{i=1} f_{now,i,i}\right)\bmod 10^9+7$$


代码如下：

``` cpp
int ans=0;	
for(int i=1;i<=n;++i){
	ans=(ans+f[now][i][i])%MOD;
}

cout<<ans;
```

## Part 3：代码
> 十年 oi 一场空，不开 `long long` 见祖宗。

``` cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

#define N 502
const int MOD=1e9+7;

int n;
int f[2][N][N];
string mp[N];
signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	cin>>n;
	
	string ss;
	for(int i=1;i<=n;++i){
		cin>>ss;
		mp[i]=' '+ss;
	}
	
	// 特判，上面没有提到，但很好理解。
	// 如果开头不一致，肯定无法构成回文。
	if(mp[1][1]!=mp[n][n]){
		cout<<0;
		return 0;
	}
	
	f[1][1][n]=1;
	
	int now=1,bef=0;
	for(int s=2;s<=n;++s){
		now^=1;bef=now^1;
		
		memset(f[now],0,sizeof f[now]);
		
		for(int i=1;i<=min(n,s);++i){
			int p=s-i+1;
			for(int j=n;j>=max(n-s,i);--j){
				int q=n+n-s-j+1;
				
				if(mp[i][p]==mp[j][q]){
					f[now][i][j]=f[bef][i-1][j]+f[bef][i][j+1]+f[bef][i-1][j+1]+f[bef][i][j];
					f[now][i][j]%=MOD;
				}
			}
		}	
	}
	
	int ans=0;	
	for(int i=1;i<=n;++i){
		ans=(ans+f[now][i][i])%MOD;
	}
	
	cout<<ans;
	return 0;
}
```

---

## 作者：大菜鸡fks (赞：1)

第一眼是想到了上次的线段树优化dp.后来仔细一想暴力就可以直接过。（我没想过更好的复杂度的dp）

可以知道，知道了步数。左上角走到的行数，右下角走到的行数就可以知道两个的坐标，都是可以唯一确定的；
于是O（n^3）的dp就很显然了，当然数组需要滚存。（我代码是按照这个思路写的）

我自己的想法一开始和这个也大同小异。
我给每个点对应过去的可能可以对应上的点都编了一下号（就是一条对角线最多n个编号），所以更新dp数组的时候不需要枚举四个坐标。当然这也是基于确定步数，两个坐标中的其中一个，就可以唯一确定坐标的思路吧。

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=505,mod=1e9+7;
int n;
char a[maxn][maxn];
inline void init(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		scanf("%s",a[i]+1);
	}
}
int dp[2][maxn][maxn],cur,ans;
inline void pushup(int &x,int v){
	(x+=v)%=mod;
}
inline void solve(){
	dp[0][1][n]=1;
	for (int i=1;i<=n;i++){
		memset(dp[cur^1],0,sizeof dp[cur^1]);
		for (int x1=1;x1<=n;x1++){
			int y1=i+1-x1;
			if (y1>=1&&y1<=n){
				for (int x2=1;x2<=n;x2++){
					int y2=(n+1)*2-x1-y1-x2;
					if (y2>=1&&y2<=n){
						if (a[x1][y1]==a[x2][y2]){
							pushup(dp[cur^1][x1][x2],dp[cur][x1][x2]);
							pushup(dp[cur^1][x1][x2],dp[cur][x1][x2+1]);
							pushup(dp[cur^1][x1][x2],dp[cur][x1-1][x2]);
							pushup(dp[cur^1][x1][x2],dp[cur][x1-1][x2+1]);
						}
					}
				}
			}
		}
		cur^=1;
	}
	for (int i=1;i<=n;i++){
		pushup(ans,dp[cur][i][i]);
	}
	printf("%d\n",ans);
}
int main(){
	init();
	solve();
	return 0;
}
```

---

## 作者：AbsMatt (赞：1)

## [题目传送器](https://www.luogu.com.cn/problem/P3126)
## [更爽的阅读体验](https://yaohaoyou.blog.luogu.org/solution-p3126)

# 题意
从 $(1,1)$ 到 $(n,n)$，每次只能向下或向右，求使路过的路径为回文串的路径数。

# 思路
$0 \le n \le 500$ 的数据可以看出这是一道 dp 题，接下来就是只要思考如何设计 dp 了。

### 状态定义
$dp_{s,i,j}$ 为从中点出发，走了 $s$ 步后，左上的点的横坐标为 $i$，右下的点横坐标为 $j$ 的回文路径数。

左上角：$(x,s+2-x)$，右下角：$(x,n \times 2-s-x)$。

### 状态转移方程
$dp_{s,i,j}$ 会从相邻的位置转移过去，也就是 $dp_{s-1,i-1,j}$、$dp_{s-1,i,j+1}$、$dp_{s-1,i-1,j+1}$、$dp_{s-1,i,j}$,所以转移方程就是：
$dp_{s,i,j}=dp_{s-1,i-1,j}+dp_{s-1,i,j+1}+dp_{s-1,i-1,j+1}+dp_{s-1,i,j}$。

**注：转移方程当两个点的位置相等时成立。**

### 初始化
$dp_{1,1,n}=1$，即左上角为 $(1,1)$，右下角为 $(n,n)$ 时有 $1$ 条路径。

### 优化
直接 dp 的话空间复杂度将是 $O(n^3)$，会 MLE，所以这里可以用滚动数组和倒序搜索，我使用的是滚动数组，空间复杂度就是 $O(n^2)$。

### 总结
这道题的 dp 思路和状态转移比较复杂，导致我赛时 $21$ 分，推出方程后就比较简单了。不开 ```long long``` 见祖宗，时间复杂度为 $O(n^3)$。

## AC Code
```cpp
#include <bits/stdc++.h>  // 开始了
#define int long long  // 开 long long
using namespace std;
const int maxn = 510, mod = 1e9 + 7;
int n, ans, dp[2][maxn][maxn];  // 滚动数组
string ss[maxn];
signed main()
{
	// IO
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> ss[i];
    }
    if (ss[1][0] == ss[n][n - 1])  // 特判，如果起点不等于终点就输出 0
        dp[0][1][n] = 1;
    else
    {
        cout << 0;
        return 0;
    }
    for (int i = 1; i < n; i++)
    {  // dp 转移
        for (int nx = 1; nx <= i + 1; nx++)
        {
            int ny = i + 2 - nx;
            for (int tx = n - i; tx <= n; tx++)
            {
                int ty = n * 2 - i - tx;
                if (ss[nx][ny - 1] == ss[tx][ty - 1])
                    dp[i & 1][nx][tx] = dp[(i - 1) & 1][nx - 1][tx] +
                                        dp[(i - 1) & 1][nx][tx + 1] +
                                        dp[(i - 1) & 1][nx - 1][tx + 1] +
                                        dp[(i - 1) & 1][nx][tx];
                else
                    dp[i & 1][nx][tx] = 0;
                dp[i & 1][nx][tx] %= mod;
            }
        }
    }
    for (int i = 1; i <= n; i++) ans += dp[(n-1) & 1][i][i], ans %= mod;
    cout << ans;
}
```


---

## 作者：Epworth (赞：1)

$1.$从$(1,1)$出发行走$k$步后落点的轨迹为以$(1,1)$为左上顶点，边长为$k+1$的正方形的对角线。

$2.$行走$k$步后落点横纵坐标之和为$k+1$，回文序列中对称两点横纵坐标之和的和为$2\times n+2$。

$3.$从对角线上的点出发，每次向左上方和右下方字符相同的点行走，最终得到的序列一定是回文序列。

为了方便，我们令从对角线出发，向左上方扩展的点为$A(a,b)$，右下方为$B(c,d)$。

定义$f[k][a][c]$为$A$的横纵坐标之和为$k$，$A$的横坐标为$a$，$B$的横坐标为$c$。

则$A$的纵坐标为$b=k-a$，$B$的纵坐标为$d=2\times n+2-a-b-c$。

由对角线向两个顶点转移。

初始化$f[n+1][i][i]=1 \ \ \ i\in[1,n]$

如果$ch(a,b)==ch(c,d)$，则存在$4$种转移的方案：

$(a+1,b)->(a,b)\ \ \ \ (c-1,d)->(c,d)$

$(a+1,b)->(a,b)\ \ \ \ (c,d-1)->(c,d)$

$(a,b+1)->(a,b)\ \ \ \ (c-1,d)->(c,d)$

$(a,b+1)->(a,b)\ \ \ \ (c,d-1)->(c,d)$

那么转移方程就很显然了：

$f[k][a][c]+=f[k+1][a+1][c-1]$

$f[k][a][c]+=f[k+1][a+1][c]$

$f[k][a][c]+=f[k+1][a][c-1]$

$f[k][a][c]+=f[k+1][a][c]$

最后$f[2][1][n]$即为答案。

时间复杂度$O(n^3)$，空间复杂度$O(过不了)$

$n^3$的空间太大了开不了怎么搞$？$

滚了它$!$

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mod 1000000007
#define maxn 505
using namespace std;
inline int read(){
	char ch=getchar();int s=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=(s<<1)+(s<<3)+ch-48;ch=getchar();}
	return s*w;
}
int n;
char xx[maxn][maxn];
ll f[2][maxn][maxn];
int main(){
	freopen("path.in","r",stdin);
	freopen("path.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>xx[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		f[(n+1)&1][i][i]=1;
	}
	for(int K=n;K>=2;K--){
		int k=K&1;
		memset(f[k],0,sizeof(f[k]));
		for(int a=1;a<=n;a++){
			int b=K-a;
			if(b<=0) continue;
			for(int c=1;c<=n;c++){
				int d=2*n+2-a-b-c;
				if(d<=0||d>n) continue;
				if(xx[a][b]==xx[c][d]){
					f[k][a][c]+=f[k^1][a+1][c-1];
					f[k][a][c]+=f[k^1][a+1][c];
					f[k][a][c]+=f[k^1][a][c-1];
					f[k][a][c]+=f[k^1][a][c];
					f[k][a][c]%=mod;	
				}	
			}
		}
	}
	printf("%lld\n",f[0][1][n]);
	return 0;
}
```



---

## 作者：CYZZ (赞：1)

# [Palindromic Paths G](https://www.luogu.com.cn/problem/P3126)
首先看到 $n \le 500$ 双向搜索会炸，自然想到 DP。
## 题意
求从 $(1,1)$ 走到 $(n,n)$ 的所有路径中回文串的个数，每步只能向右或向下。

因为是回文串，所以可以把题目转化为：两人从 $(1,1)$ 和 $(n,n)$ 分别出发，在图中某点相遇，两条路径构成的字符串相同，求走法个数。
## 状态设计
可以暴力的设 $dp_{i,j,p,q}$ 为第一个人走到 $(i,j)$，第二个人走到 $(p,q)$ 的方法数，但是四维的状态肯定时空爆炸。

我们发现只要步数和横坐标确定了，纵坐标也就确定了。所以可以把状态压缩为 $dp_{step,i,p}$ 表示走了 $step$ 步，第一和第二个人的横坐标分别为 $i$ 和 $p$。则易得 $j=step-i$ 且 $q=2 \times n-step-p$。
## 转移方程
状态转移方程就很好想了。$i$ 和 $p$ 分别可以从 $4$ 个方向上转移过来，条件是 $map_{i,j}=map_{p,q}$。
$$dp_{step,i,p}=dp_{step-1,i-1,p}+dp_{step-1,i,p+1}+dp_{step-1,i-1,p+1}+dp_{step-1,i,p}$$
## 细节处理
初始值：$dp_{1,1,n}=1$。

答案：易知两点相遇的位置总是在矩形的对角线上。

优化：$dp$ 数组的空间 $500^3=125000000$ 还是会 MLE。我们发现每一步的枚举只需要上一步的答案，所以可以用滚动数组优化。当然倒序枚举优化也可以。
## 代码（倒序枚举）
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,ans,dp[505][505];
char s[505][505];
signed main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
    {
        getchar();
        for(int j=1;j<=n;j++)
        {
            s[i][j]=getchar();
        }
    }
    if(s[1][1]!=s[n][n])//小特判
    {
        printf("0");
        return 0;
    }
    dp[1][n]=1;//初始化
    for(int k=1;k<n;k++)
    {
        for(int i=k+1;i;i--)//倒序枚举
        {
            for(int p=n-k;p<=n;p++)//倒序枚举
            {
                int j=k+2-i,q=2*n-k-p;
                if(s[i][j]==s[p][q])
                    dp[i][p]=(dp[i-1][p]+dp[i][p+1]+dp[i-1][p+1]+dp[i][p])%1000000007;
                else
                    dp[i][p]=0;//倒序枚举的细节处理
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        ans=(ans+dp[i][i])%1000000007;
    }
    printf("%lld",ans);
}
```
## 代码（滚动数组）
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,ans,now=1,dp[2][505][505];
char s[505][505];
signed main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
    {
        getchar();
        for(int j=1;j<=n;j++)
        {
            s[i][j]=getchar();
        }
    }
    if(s[1][1]!=s[n][n])//小特判
    {
        printf("0");
        return 0;
    }
    dp[1][1][n]=1;//初始化
    for(int k=1;k<n;k++)
    {
        now^=1;//滚动 
        memset(dp[now],0,sizeof dp[now]);//记得清空 
        for(int i=1;i<=k+1;i++)
        {
            for(int p=n;p>=n-k;p--)
            {
                int j=k+2-i,q=2*n-k-p;
                if(s[i][j]==s[p][q])
                    dp[now][i][p]=(dp[now^1][i-1][p]+dp[now^1][i][p+1]+dp[now^1][i-1][p+1]+dp[now^1][i][p])%1000000007;//转移 
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        ans=(ans+dp[now][i][i])%1000000007;
    }
    printf("%lld",ans);
}

```

希望本篇题解可以帮到大家！！！

---

## 作者：yhy2024 (赞：0)

考虑 dp，设 $f_{x1,y1,x2,y2}$ 表示从左上角和右下角分别走到 $(x1,y1),(x2,y2)$ 两点的回文路径方案数。

枚举 $x1,y1,x2,y2$，显然有：

当 $c_{x1,y1}=c_{x2,y2}$ 时：

$f_{x1,y1,x2,y2}=f_{x1,y1,x2,y2}+f_{x1-1,y1,x2+1,y2}+f_{x1-1,y1,x2,y2+1}+f_{x1,y1-1,x2+1,y2}+f_{x1,y1-1,x2,y2+1}$

否则：

$f_{x1,y1,x2,y2}=0$

时空都是 $O(n^4)$，显然不行，考虑优化。

设走了 $k$ 步，注意到 $x1+y1-1=k,(n-x2)+(n-y2)-1=k$。

优化状态 $f_{k,x1,x2}$ 表示走了 $k$ 步，两点纵坐标分别为 $x1,x2$ 的回文路径方案数。

当 $c_{x1,y1}=c_{x2,y2}$ 时：

$f_{k,x1,x2}=f_{k,x1,x2}+f_{k-1,x1-1,x2}+f_{k-1,x1,x2+1}+f_{k,x1-1,x2+1}$

否则：

$f_{k,x1,x2}=0$

时空都是 $O(n^3)$, 空间不行，使用滚动数组优化。

最后时间是 $O(n^3)$，空间是 $O(n^2)$。

---

## 作者：Eterna (赞：0)

[Link1](https://www.luogu.com.cn/problem/P3126)/[Link2](https://www.luogu.com.cn/problem/CF570E)

每一步都有两种不同的方向，一条路径长 $n+m-1$，所以搜索复杂度是 $O(2^{n+m})$，双向搜索可以做到 $O(2^n)$，但是不可过。

回文串有一个优良的性质，就是从左数第 $i$ 个数与从右数第 $i$ 个数相同，这是定义。同理，想象一下，有两个人分别站在点 $(1,1)$ 和点 $(n,m)$，第一个人每次可以向右或向下走，第二个人每次可以向左或向上，两人每次同时走，两人走了一共走了 $(n+m-1)$ 步自然就不能走了，而两人相遇时就形成一条从 $(1,1)$ 到 $(n,m)$ 的路径。

回文的限制就是要求两人每一步格子上的元素是相等的。不难设计出 dp 的状态 $f_{x,y,u,v}$ 为第一个人走到 $(x,y)$，第二个人走到 $(u,v)$ 的可行路径数。

但是时空都不太行，考虑一个更强大的状态。

因为第一个人每次只能向右或向下，第二个人每次只能向左或向上，如果知道他们走一个方向的次数和总的次数就可以知道他们的坐标，又因为他们是同时走的，所以总的次数是相等的。于是我们将状态简化为 $f_{x,u,t}$，$x,u$ 表示他们的纵坐标，$t$ 表示每个人走的步数。

容易得到转移：$f_{x,u,t}=f_{x,u,t-1}+f_{x+1,u,t-1}+f_{x,u-1,t-1}+f_{x+1,u-1,t-1}(a_{x,y}=a_{u,v})$。

但是空间 $O(n^3)$ 过不了。但是我们发现转移方程只和 $t$ 和 $t-1$ 的情况有关，于是可以滚动，空间就 $O(n^2)$ 了！！！

答案枚举他们相遇的位置求和即可。

---

## 作者：Antiluna (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P3126)

众所周知，回文串有一个性质：反转串与原串相等。

其实可以引申到二维地图中的回文串：从 $(1,1)$ 出发和从 $(n,m)$ 出发走该回文串，相遇后，两个串是相等的。

于是可以想到 $dp_{i,j,k,l}$ 表示第一个人走到 $(i,j)$ 第二个人走到 $(k,l)$ 时相等的方案数，此时不难转移。

但是空间会爆，所以考虑进行优化，容易发现两人走的步数是相等的，而通过步数和 x 坐标可以求出 y 坐标，于是又可以得出 $dp(s,i,k)$ 表示走了 $s$ 步，第一个人走到 $(i,s-i+1)$ 第二个人走到 $(k,n+m-s-k+1)$ 时相等的方案数。

需要注意的是因为我们要求相遇时的方案数，所以在 $n+m$ 为奇数时要算两种情况。

代码：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,dp[3][510][510],a[510][510],b[510][510],mod=1000000007,ans;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	m=n;
	for(int i=1;i<=n;i++)
	{
		string s;
		cin>>s;
		for(int j=1;j<=m;j++)a[i][j]=s[j-1]-65;
	}
	if(a[1][1]!=a[n][m])
	{
		cout<<0;
		return 0;
	}
	dp[1][1][n]=1;
	int i=1;
	for(int step=2;step<=(n+m)/2;step++)
	{
		i=i^1;
		memset(dp[i],0,sizeof(dp[i]));
		for(int x1=1;x1<=min(step,n);x1++)
		{
			for(int p=n;p>=max(n-step,i);p--)
			{
				int x2=step-x1+1,q=n+m-step-p+1;
				if(a[x1][x2]==a[p][q])dp[i][x1][p]=(dp[i^1][x1-1][p]+dp[i^1][x1-1][p+1]+dp[i^1][x1][p]+dp[i^1][x1][p+1])%mod; 
			}
		}
	}
	if((n+m)&1)for(int j=1;j<=n;j++)ans=(ans+dp[i][j][j]+dp[i][j][j+1])%mod; 
	else for(int j=1;j<=n;j++)ans=(ans+dp[i][j][j])%mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：freeplume (赞：0)

容易想到将问题转化为：让两个点从两个角落出发，所走的路径相同的方案数。

那么我们设 $f_{i,j,k,l}$ 表示两点分别走到 $(i,j),(k,l)$，所走的路径相同的方案数，容易写出转移方程 $f_{i,j,k,l}=f_{i-1,j,k+1,l}+f_{i-1,j,k,l+1}+f_{i,j-1,k,l+1}+f_{i,j-1,k+1,l}.$

这样的时空复杂度均为 $O(n^4)$，无法接受，考虑优化。

注意到路径相同必有长度相同，即 $(i,j)$ 到 $(1,1)$ 的距离必然等于 $(k,l)$ 到 $(n,n)$ 的距离，确定其中三个数即可唯一地确定第四个数，因此我们可以将第四维优化掉。

我们考虑一种更好看的表示方式，即令 $f_{i,j,k}$ 表示，路径长度为 $i$，两个点一个横坐标为 $j$，另一个为 $k$，此时路径相同的方案数。

状态转移方程如下:

当 $ch_{j,i+2-j} = ch_{k,2 \times n-i-k}$，$f_{i,j,k}=f_{i-1,j,k}+f_{i-1,j-1,k}+f_{i-1,j,k+1}+f_{i-1,j-1,k+1}$，否则 $f_{i,j,k}=0.$

接下来还要解决空间问题，使用滚动数组压一维，倒序枚举 $j$，正顺枚举 $k$ 即可（可以手推理解）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=505,mod=1e9+7;
int n,ans;
char ch[maxn][maxn];
int f[maxn][maxn];

inline int rd(){
    int s=0,f=1;
    char ch=getchar();
    while(ch>'9'||ch<'0'){
        if(ch=='-') f=-1;
        ch=getchar(); 
    }
    while(ch>='0'&&ch<='9'){
        s=s*10+ch-'0';
        ch=getchar();
    }
    return s*f;
}

int main(){
    n=rd();
    for(int i=1;i<=n;i++){
        scanf("%s",ch[i]+1); 
    }
    if(ch[1][1]!=ch[n][n]){
        printf("0");
        return 0; 
    }
    f[1][n]=1;
    for(int i=1;i<n;i++){
         for(int j=i+1;j;j--){
             for(int k=n-i;k<=n;k++){
                 if(ch[j][i+2-j]!=ch[k][n*2-i-k]) f[j][k]=0;
                 else f[j][k]=((f[j][k]+f[j-1][k+1])%mod+(f[j-1][k]+f[j][k+1])%mod)%mod;
             }
         }
    }
    for(int i=1;i<=n;i++){
        ans=(ans+f[i][i])%mod;
    }
    printf("%d",ans);
    return 0;
}
```


---

## 作者：Yizhixiaoyun (赞：0)

看到回文，首先想到可以从起点和终点同时开始跳，这样就有一个四维 $\text{dp}$，即 $dp_{i,j,k,l}$ 表示从起点开始跳的点当前在坐标 $(i,j)$，另一个点在 $(k,l)$，但很显然时间爆表。

注意到只可以往下或右跳，那么一旦我们知道当前跳的步数 $stp$ 以及所在的行数 $i$，自然也可以求出所在的列数 $j$。

这时候就简化为一个三维 $\text{dp}$，$dp_{i,j,stp}$ 表示第一个点在 $i$ 行，第二个点在 $j$ 行，它们跳了 $stp$ 步。

则有:

$$dp_{i,j,stp}=dp_{i-1,j,stp-1}+dp_{i,j+1,stp-1}+dp_{i-1,j+1,stp-1}+dp_{i,j,stp-1}$$

接着发现第三维 $stp$ 永远只和 $stp-1$ 有关系，那么滚动数组压掉一维，结束。

```cpp
#include<bits/stdc++.h>
#define int long long
#define debug puts("Shiina_Mashiro_kawaii")
#define ok puts("Yes")
#define no puts("0")
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-48;
		c=getchar();
	}
	return x*f;
}
const int mod=1e9+7;
const int maxn=510;
const int maxm=10;
int n;
int lst,now,ans;
int dp[maxn][maxn][2];
string s[maxn];
// void dfs(int x,int y){
// 	
// }
inline void init(){
	n=read();now=1;
	for(register int i=1;i<=n;++i){
		cin>>s[i];s[i]=" "+s[i];
	}
	if(s[1][1]!=s[n][n]) no,exit(0);
	dp[1][n][0]=1;
}
signed main(){
	init();
	for(register int stp=2;stp<=n;++stp){
		for(register int i=1;i<=n;++i){
			if(stp<i) break;
			for(register int j=n;j>=i;--j){
				if(s[i][stp-i+1]!=s[j][2*n-stp-j+1]) dp[i][j][now]=0;
				else{
					dp[i][j][now]=dp[i-1][j][lst]+dp[i][j+1][lst]+dp[i-1][j+1][lst]+dp[i][j][lst];
					dp[i][j][now]%=mod;
				}
			}
		}
		swap(lst,now);
	}
	for(register int i=1;i<=n;++i){
		ans+=dp[i][i][lst];ans%=mod;
	}
	printf("%lld",ans);
}
```


---

## 作者：_Flame_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P3126)

## 思路

回文串直接处理会比较麻烦，所以考虑从起点终点两边同时向中间走。

最暴力的做法是定义一个五维 dp，其中 $dp_{i,j,k,l,s}$ 表示现在走了 $s$ 步，两端分别走到点 $a_{i,j}$ 与点 $a_{k,l}$，转移很简单，但五维无论在时间还是空间上都过不了，所以考虑如何优化。

稍微思考一下可以发现，当你知道当时走的步数与当前点的横坐标是，纵坐标也可以通过计算得出，因为两端的点同时动，所以步数也是一样的，所以所以我们可以定义一个三维状态 $dp_{s,i,j}$，其中 $s$ 表示当时步数，$i$ 为左上点的横坐标，$j$ 表示另外一点的横坐标，此时左上的点为 $a_{i,s-i}$，右下点为 $a_{j,n-(s-(n-j))}=a_{j,n\times2-s-j}$，当两点字母相同时，转移为 $dp_{s,i,j}=dp_{s-1,i-1,j}+dp_{s-1,i,j+1}+dp_{s-1,i-1,j+1}+dp_{s-1,i,j}$，若不相同，则为零。

这样时间复杂度变为 $O(n^3)$，可以过，但空间复杂度也是 $O(n^3)$，所以再来优化空间，最容易想到的是滚动数组，这里提供另外一种思路，$i$ 和 $j$ 都从后往前搜，这样步数的那一维就可以压掉，变成二维。此时转移方程为 $dp_{i,j}=dp_{i,j}+dp_{i-1,j}+dp_{i-1,j-1}+dp_{i,j-1}$，空间复杂度 $O(n^2)$，时间复杂度 $O(n^3)$，可以通过此题。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define _int __int128
#define y1 _
using namespace std;

static char buf[1000000],*p1=buf,*p2=buf;

inline int read(){
	char c=getchar();
	int res=0,f=1;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res*f;
}

inline void write(int x){
	static char buf[20];
	static int len=-1;
	if(x<0){
		putchar('-');
		x=-x;
	}
	do{
		buf[++len]=x%10;
		x/=10;
	}
	while(x);
	while(len>=0){
		putchar(buf[len--]+48);
	}
}

const int maxn=510;
const int maxm=110;
const int yinhee=1e9+7;
const int inf=1145141919810;

int n;
char a[maxn][maxn];
int f[maxn][maxn];

void solve(){
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>a[i][j];
		}
	}
	if(a[1][1]!=a[n][n]){
		write(0);
		return ;
	}
	f[1][1]=1;
	for(int s=3;s<=n+1;s++){
		for(int i=s-1;i>=1;i--){
			for(int j=s-1;j>=1;j--){
				int x=i,y=s-i,x1=n-s+j+1,y1=n-j+1;
				if(a[x][y]==a[x1][y1]) f[i][j]+=(f[i-1][j]+f[i-1][j-1]+f[i][j-1])%yinhee,f[i][j]=f[i][j]%yinhee;
				else f[i][j]=0;
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		ans+=f[i][i]%yinhee;
		ans=ans%yinhee;
	}
	write(ans%yinhee); 
	return ;
}

signed main(){
	int T=1;
	while(T--){
		solve();
	}
	return 0;
}
```

---

## 作者：lnwhl (赞：0)

## Solution
首先，我们考虑如何判断回文串。不难想到从 $(1,1)$ 和 $(n,n)$ 分别向中间走，每次走的格子上的字母相同，到中间汇合时统计一下方案数即可。

考虑 dp，状态需要记录哪些量？暴力的 dp 肯定是记录两边分别走到哪了，但这样复杂度是 $O(n^4)$ 的，无法通过本题。发现只要知道了当前走了几步就可以由横纵坐标中的一个推出另一个，因此我们可以让 $f_{i,j,k}$ 表示走了 $i$ 步，两点的横坐标分别为 $j$ 和 $k$ 的方案数。但还是会超空间，可以用滚动数组压一维。

转移方程：
$$f_{j,k}=f_{j,k}+f_{j-1,k}+f_{j,k+1}+f_{j-1,k+1}$$
时间复杂度 $O(n^3)$，空间复杂度 $O(n^2)$，可以通过。
## Code
```cpp
#include <bits/stdc++.h>
#define ll long long 
#define Rint register int 
using namespace std;
const int N=505,mod=1e9+7;
int n;
ll f[N][N];
char c[N][N];
int main()
{
	cin>>n;
	for(Rint i=1;i<=n;++i)
	{
		for(Rint j=1;j<=n;++j)
		{
			cin>>c[i][j];
		}
	}
	if(c[1][1]!=c[n][n])
	{
		cout<<0;return 0;
	}
	f[1][n]=1;
	for(Rint i=3;i<=n+1;++i)
	{
		for(Rint x1=i-1;x1>=1;--x1)
		{
			for(Rint x2=n+2-i;x2<=n;++x2)
			{
				int y1=i-x1,y2=n+n+2-i-x2;
				if(c[x1][y1]!=c[x2][y2])
				{
					f[x1][x2]=0;
					continue;
				}
                f[x1][x2]=f[x1][x2]+f[x1-1][x2]+f[x1][x2+1]+f[x1-1][x2+1];
                f[x1][x2]%=mod;
			}
		}
	}
	ll ans=0;
	for(Rint i=1;i<=n;++i)
		ans+=f[i][i],ans%=mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

思路：由于会问，可以考虑从两端遍历，每次遍历到相等的字符，如果可以到达同一个点，就是一种方案。

定义 $dp_{i,a,x}$ 表示已经走了 $i$ 步，$(1,1)$ 横向走了 $a$ 步，$(n,n)$ 横向走了 $x$ 步，这样我们可以确定两个点的横坐标和纵坐标。

初始状态：
$dp_{n-1,i,j}=1(1\le i\le n,1\le j\le n)$（终点是一种方案），目标状态 $dp_{0,1,n}$（起点）。

时空复杂度 $O(n^3)$，空间会被卡。

然后，容易想到滚动数组优化 dp，将空间复杂度优化到 $O(n^2)$。
```cpp
#include<bits/stdc++.h>
#define int long long
#define dp(a,b,c) dp[a&1][b][c] 
using namespace std;
const int mod=1e9+7;
int n,dp[2][505][505];
char s[505][505];
signed main(){
	cin>>n;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			cin>>s[i][j];
	for(int i=1;i<=n;++i)
		dp(n-1,i,i)=1;
	for(int i=n-1;i;--i){
		for(int a=1;a-1<=i;++a)
			for(int x=n;n-x<=i;--x){
				int b=i-a+2,y=2*n-i-x;
				if(b-1>=1&&y+1<=n&&s[a][b-1]==s[x][y+1])
					dp(i-1,a,x)=(dp(i-1,a,x)+dp(i,a,x))%mod;
				if(a-1>=1&&y+1<=n&&s[a-1][b]==s[x][y+1])
					dp(i-1,a-1,x)=(dp(i-1,a-1,x)+dp(i,a,x))%mod;
				if(b-1>=1&&x+1<=n&&s[a][b-1]==s[x+1][y])
					dp(i-1,a,x+1)=(dp(i-1,a,x+1)+dp(i,a,x));
				if(a-1>=1&&x+1<=n&&s[a-1][b]==s[x+1][y])
					dp(i-1,a-1,x+1)=(dp(i-1,a-1,x+1)+dp(i,a,x))%mod;
			}
		memset(dp[i&1],0,sizeof(dp[i&1]));
	}
    printf("%lld\n",dp(0,1,n));
    return 0;
}
```

---

## 作者：破忆 (赞：0)

## 【题目大意】

从左上到右下，只能往右或往下，求路径是回文串的方案数

## 【分析】

求方案数的题，不难看出是DP

回文串可以看成2个指针，分别从左上和右下出发，要求每一步走到的点的字母都一样

那么定义f[x][y][xx][yy]

表示从左上角走到（x，y），从右下角走到（xx，yy）能构成回文串的方案数

转移的时候，可以对

f[x-1][y][xx+1][yy],

f[x-1][y][xx][yy+1]，

f[x][y-1][xx+1][yy]，

f[x][y-1][xx][yy+1]

求和

转移的条件是（x，y）与（xx，yy）上的字母相同

最裸的DP就完成了，然而时空复杂度都是O（n^4）~~时空两爆炸~~

### 考虑如何优化

从左上出发的指针，每次只能走一步，要么行号+1，要么列号+1

另一个指针也类似

那么通过坐标就可以算出步数及对角线号，很显然步数不同的状态对答案没有贡献

所以上一个算法做了很多无用的计算

通过以上的推导可以发现，所有能同时走到的点对，对角线号之和相同

那么可以先枚举对角线号及步数，再枚举2个指针的横坐标，算出纵坐标

f[k][x][xx]表示左上的点走到k号对角线，2个指针横坐标分别是x与xx的方案数

转移方程与之前类似

成功把复杂度削减至O（n^3）
## 【代码】
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=505,TT=1e9+7,p[4][2]={{0,0},{0,1},{-1,0},{-1,1}};
int n;
char mp[maxn][maxn];
int f[maxn][maxn][maxn],ans;
int main(){
// 	freopen("P3126.in","r",stdin);
// 	freopen("P3126.out","w",stdout);
	scanf("%d",&n); 
	for(int i=1;i<=n;i++) scanf("%s",mp[i]+1);
	if(mp[1][1]!=mp[n][n]){
		printf("0\n");
		return 0;
	}
	f[1][1][n]=1;
	for(int k=1;k<=n;k++)
	for(int x=1;x<=k;x++){
		int y=k+1-x;
		for(int j=1;j<=k;j++){
			int xx=n-j+1,yy=2*n-k-xx+1;
			if(mp[x][y]!=mp[xx][yy]) continue;
			for(int i=0;i<4;i++)
			f[k][x][xx]=(f[k][x][xx]+f[k-1][x+p[i][0]][xx+p[i][1]])%TT; 
		}
	}
	for(int i=1;i<=n;i++) ans=(ans+f[n][i][i])%TT;
	printf("%d\n",ans);
	return 0;
}
```
如果交了这份代码，恭喜你获得了32分~~的好成绩~~

MLE的原因是f数组 505×505×505×4/1024/1024≈491MB

怎么办？

由于当前对角线只受相邻对角线影响

没错，这个数组是可以滚动的

稍微修改一下代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=505,TT=1e9+7,p[4][2]={{0,0},{0,1},{-1,0},{-1,1}};
int n;
char mp[maxn][maxn];
int f[2][maxn][maxn],ans;
int main(){
// 	freopen("P3126.in","r",stdin);
// 	freopen("P3126.out","w",stdout);
	scanf("%d",&n); 
	for(int i=1;i<=n;i++) scanf("%s",mp[i]+1);
	if(mp[1][1]!=mp[n][n]){
		printf("0\n");
		return 0;
	}
	f[0][1][n]=1;
	for(int k=1;k<=n;k++){
		memset(f[k&1],0,sizeof f[k&1]);
		for(int x=1;x<=k;x++){
			int y=k+1-x;
			for(int j=1;j<=k;j++){
				int xx=n-j+1,yy=2*n-k-xx+1;
				if(mp[x][y]!=mp[xx][yy]) continue;
				for(int i=0;i<4;i++)
				f[k&1][x][xx]=(f[k&1][x][xx]+f[1-k&1][x+p[i][0]][xx+p[i][1]])%TT; 
			}
		}
	}
	for(int i=1;i<=n;i++) ans=(ans+f[n&1][i][i])%TT;
	printf("%d\n",ans);
	return 0;
}
```
~~然而从MLE变成了TLE~~

因为500^3≈10^8已经是强弩之末了

由于滚动过程中大量k&1与1-k&1的冗余计算，转移的过程中也多次%，常数很大

所以会TLE

把这几个东西开成变量减少计算再进行一些优化~~然后吸口氧~~即可
```cpp
#include<bits/stdc++.h>
#define RE register
#define LL long long
using namespace std;
const int maxn=505,TT=1e9+7,p[4][2]={{0,0},{0,1},{-1,0},{-1,1}};
int n;
char mp[maxn][maxn];
LL f[2][maxn][maxn],ans;
int main(){
//	freopen("P3126.in","r",stdin);
//	freopen("P3126.out","w",stdout);
	scanf("%d",&n); 
	for(int i=1;i<=n;i++) scanf("%s",mp[i]+1);
	if(mp[1][1]!=mp[n][n]){
		printf("0\n");
		return 0;
	}
	f[0][1][n]=1;
	for(RE int k=1;k<=n;k++){
		RE int now=k&1,lst=1-now; 
		memset(f[now],0,sizeof f[now]);
		for(RE int x=1;x<=k;x++){
			RE int y=k+1-x;
			for(RE int j=1;j<=k;j++){
				RE int xx=n-j+1,yy=2*n-k-xx+1;
				if(mp[x][y]!=mp[xx][yy]) continue;
				for(RE int i=0;i<4;i++)
				f[now][x][xx]+=f[lst][x+p[i][0]][xx+p[i][1]];
				f[now][x][xx]%=TT;
			}
		}
	}
	for(RE int i=1;i<=n;i++) ans=(ans+f[n&1][i][i])%TT;
	printf("%lld\n",ans);
//	printf("%d\n",clock());
	return 0;
}
```

---

