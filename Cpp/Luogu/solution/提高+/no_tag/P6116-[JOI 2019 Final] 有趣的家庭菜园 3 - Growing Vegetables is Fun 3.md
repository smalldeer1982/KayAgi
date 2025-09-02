# [JOI 2019 Final] 有趣的家庭菜园 3 / Growing Vegetables is Fun 3

## 题目背景

JOI 2019 Final T3

由于数据点较多，本题只评测其中的部分数据。

## 题目描述

家庭菜园专家 JOI 先生在他的家庭菜园中种植了一种叫 Joy 草的植物。在他的菜园里，有 $N$ 个花盆自东向西摆放，第 $i$ 个编号为 $i$。每个花盆中有一株 Joy 草。

春天到了，JOI 先生注意到 Joy 草如他期望地长出了各种颜色的叶子，但他也发现 Joy 草的生长速度没有他期望的那么快。他查阅了书籍，找到了草的以下特点：

 - Joy 草有三种品种，分别会长出红色、绿色和黄色的叶子。

 - 如果两株同一颜色的 Joy 草紧密相邻，它们的生长速度就会减慢。

因此，JOI 先生决定重新摆放花盆，使得没有两株相邻的 Joy 草颜色相同。

花盆非常沉重，因此 JOI 先生每次只能交换相邻的两个花盆。形式化的说，JOI 先生每次操作可以选择一个 $i$，然后交换花盆 $i$ 和花盆 $i+1$。

请编写一个程序，计算最少的交换次数。

## 说明/提示

样例解释 $1$:  

一种合法的方案是：
  
第一步：交换第三个花盆和第四个花盆。 
 
第二步：交换第二个花盆和第三个花盆。 
 
可以证明，不存在次数更少的方案 

样例解释 $2$：  

可以证明，无论如何移动，均不可达到目标。  

对于 $5\%$ 的数据，$N\le 15$。

对于 $60\%$ 的数据，$N\le 60$。

另有 $15\%$ 的数据，字符串仅包含 `R`,`G`。

对于 $100\%$ 的数据，$N\le 400$。

## 样例 #1

### 输入

```
5
RRGYY```

### 输出

```
2```

## 样例 #2

### 输入

```
6
RRRRRG```

### 输出

```
-1```

## 样例 #3

### 输入

```
20
YYGYYYGGGGRGYYGRGRYG```

### 输出

```
8```

# 题解

## 作者：ISYRHH (赞：14)

## P6116 [JOI 2019 Final] たのしいたのしいたのしい家庭菜園

------

这是蒟蒻 ISYRHH 错过的一次考试的考试题……考试结束后发现思想和正解不太一样，实现了一下，过了样例后本着找点 debug 的心态交上去，结果一遍过了，发表这篇题解给后人提供一种新的思路。

------

## 题意分析

题意为通过尽可能少次数的交换相邻两个数的操作使任何两个相邻的数互不相同。

------

## 解法

### 首先先考虑什么样的情况会使方案无法实现：

当且仅当有一种颜色的数量超过一半时，无法通过其他颜色插空使该颜色被隔开，因此方案不可能实现。

否则一定可以通过较少两种颜色交叉排列，和使较多的颜色插空或与第二多的颜色交叉实现至少一种方案。

### 然后考虑方案的实现：

显然有一个小的贪心策略：交换两个相同颜色是没有意义的，这并不会对要求的相邻颜色互不相同产生贡献，还会产生更多的交换次数。

所以开始时的某种颜色内部的顺序就是最终状态中该种颜色内部的顺序。

另外颜色交换的过程可以理解为将原序列变成一个新的序列，对新序列的每一位顺序考虑。

#### 考虑之前决策的哪些内容会对之后的决策产生影响：

1.新序列当前最后一位的颜色关系到下一位能选什么颜色，不能选什么颜色，会对之后产生影响。

2.新序列中已经使用过哪些数，还没用过那些数，会对之后决策产生影响（剩下数的顺序无关紧要，因为要么是还未被动过，要么是可以通过调整顺序放到任意位置）。

由于数的顺序是一定的，所以只需要记录已使用每种颜色的个数就能记录使用过的数。

将这两项作为动态规划的状态。

用一个四维数组 $dp_{i,j,k,u}$ 表示新序列中已有 $i$ 个 R，$j$ 个 G，$k$ 个 Y，且最后一位是 $u$ 时花费的交换次数。

( $\mathtt{' R'}=0,\mathtt{'G'}=1,\mathtt{'Y'}=2$ )

然后考虑转移

首先从原序列的每一位开始考虑，如果只对原序列的前 $i$ 位操作，新序列中最多会有会有 $cn_0$ 个 R，$cn_1$ 个 G，$cn_2$ 个 Y。

（$cn_i$ 表示处理到当前 $i$ 的出现次数）

若要往新序列添加原序列第 $i$ 位上的 R，这个 R 的前面可以有任意合法数量的 G 和 Y，但是此时新序列必然已经放置了原序列前面所有的 R。

用 $now$ 表示当前一位原序列的字符（假设为 R）。

这次放置 R 可以表示为 $dp_{cn_{now},j,k,now}$ 从 $\mathtt{min}\left(dp_{cn_{now-1},j,k,u}\right)$ 转移而来。

（其中 $j\in\left[0,cn_1\right]$，$k\in\left[0,cn_2\right]$，$u\in\left\{1,2\right\}$）

考虑将 R 移动到新序列的位置，之前的操作中不可能会动这个 R，所以它还在原位置 $i$。

新序列现在的长度为 $cn_{now}+j+k-1$，应放到第 $cn_{now}+j+k$ 位。

即将其从第 $i$ 位移到第 $cn_{now}+j+k$ 位。

移动的次数为 $i-cn_{now}-j-k$。

即 $dp_{cn_{now},j,k,now}=\mathtt{min}\left(dp_{cn_{now-1},j,k,u}\right)+\left(i-cn_{now}-j-k\right)$。

这样就有了一个转移式。

然后发现不对，对于原序列中连续的两个相同的数，我们移动后 $cn_0,cn_1,cn_2$ 有可能不能被满足，然后答案没法统计。

卡了一会后发现：

对于其他的情况我们会把没用过的一些部分咕掉暂时放到 $i$ 和 $cn_{now}+i+j$ 中间。

我们还可以通过调换之前移动的顺序使任何一个数位于 $i$ 和 $cn_{now}+i+j$ 中间的任何一个位置。

所以在第一种转移后，还可以在后面补上一个不与最后一位相同的数，这步的操作数为 $0$。

转移：$dp_{cn_{now},j+1,k,1}=\mathtt{min}\left(dp_{cn_{now},j+1,k,1},dp_{cn_{now},j,k,now}\right)$。

对于 G，Y 的转移同理。

## 代码

```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
using namespace std;
int n,cn[3],now,ans=0x7f7f7f7f,tot[3];
char opt[3]={'R','G','Y'};
string s;
int minn(int x,int y)
{
    return x<=y?x:y;
}
int main()
{
    // freopen("b.in","r",stdin);
    // freopen("b.out","w",stdout);
    scanf("%d",&n);
    cin>>s;
    for(int i=0;i<n;i++)for(int j=0;j<3;j++){if(s[i]==opt[j])tot[j]++;}
    for(int j=0;j<3;j++)if(tot[j]>((n+1)>>1)){printf("-1");return 0;}
    int dp[tot[0]+1][tot[1]+1][tot[2]+1][3];
    memset(dp,0x3f,sizeof(dp));memset(dp[0][0][0],0,sizeof(dp[0][0][0]));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<3;j++)if(s[i]==opt[j])now=j;
        if(now==0)
        {
            for(int j=cn[1];j>=0;j--)
            {
                for(int k=cn[2];k>=0;k--)
                {
                    dp[cn[now]+1][j][k][0]=minn(dp[cn[now]+1][j][k][0],minn(dp[cn[now]][j][k][1],dp[cn[now]][j][k][2])+(i-cn[now]-j-k));
                    if(j<cn[1])dp[cn[now]+1][j+1][k][1]=minn(dp[cn[now]+1][j+1][k][1],dp[cn[now]+1][j][k][0]);
                    if(k<cn[2])dp[cn[now]+1][j][k+1][2]=minn(dp[cn[now]+1][j][k+1][2],dp[cn[now]+1][j][k][0]);
                    // printf("1");
                }
            }
            cn[0]++;
        }
        if(now==1)
        {
            for(int j=cn[0];j>=0;j--)
            {
                for(int k=cn[2];k>=0;k--)
                {
                    // printf("1");
                    dp[j][cn[now]+1][k][1]=minn(dp[j][cn[now]+1][k][1],minn(dp[j][cn[now]][k][0],dp[j][cn[now]][k][2])+(i-cn[now]-j-k));
                    if(j<cn[0])dp[j+1][cn[now]+1][k][0]=minn(dp[j+1][cn[now]+1][k][0],dp[j][cn[now]+1][k][1]);
                    if(k<cn[2])dp[j][cn[now]+1][k+1][2]=minn(dp[j][cn[now]+1][k+1][2],dp[j][cn[now]+1][k][1]);
                    // printf("1");
                }
            }
            cn[1]++;
        }
        if(now==2)
        {
            for(int j=cn[0];j>=0;j--)
            {
                for(int k=cn[1];k>=0;k--)
                {
                    // printf("1");
                    dp[j][k][cn[now]+1][2]=minn(dp[j][k][cn[now]+1][2],minn(dp[j][k][cn[now]][0],dp[j][k][cn[now]][1])+(i-cn[now]-j-k));
                    if(j<cn[0])dp[j+1][k][cn[now]+1][0]=minn(dp[j+1][k][cn[now]+1][0],dp[j][k][cn[now]+1][2]);
                    if(k<cn[1])dp[j][k+1][cn[now]+1][1]=minn(dp[j][k+1][cn[now]+1][1],dp[j][k][cn[now]+1][2]);
                    // printf("1");
                }
            }
            cn[2]++;
        }
    }
    for(int i=0;i<3;i++)ans=minn(ans,dp[cn[0]][cn[1]][cn[2]][i]);
    printf("%d",ans);
    // fclose(stdin);fclose(stdout);
    return 0;
}

```

## **end**


------------

update 7.22：

修改了 for 循环顺序问题，倒序保证不会连续两次在新序列末尾加上同样颜色，（debug 的时候只改了一个 for，不过数据太水没被卡掉。）

---

## 作者：tytyty (赞：13)

CYJian 学长的 NOIP2020 模拟赛题，只有题面被魔改了（不过也是搬花盆）。但是蒟蒻考场只会做特殊性质 QwQ。

### 题意

给定一个由 `R`,`G`,`Y` 组成的，长度为 $n$ 的字符串，每次只能交换相邻两个字符，问最少操作几次，能使相邻两个字符不同。若无解，输出 `-1`。

### Solution

$15pts$：

$N\leq 15$ 枚举末状态即可。

$20pts$：

考虑特殊性质的末状态只有两种：`RGRGRG` 和 `GRGRGR`。可以发现规律：答案为所有不在最终位置上的 `R` 与最近的不在位置上的 `G` 中间间隔数 $+1$ 之和。

$80pts$：

$N\leq 60$ 不能再枚举了考虑，dp。

首先，能发现性质：

1. 当一种颜色的数量大于 $\frac{n}{2}$ 时无解。

2. 交换同种颜色无意义。

3. **假设按原字符串给每个字符编号，相同字符的内部顺序不变。**

令 $R\to0,G\to1,Y\to2$。

设 $f_{i,j,k,l,0/1/2}$ 表示前 $i$ 位中有 $j$ 个 $0$、$k$ 个 $1$、$l$ 个 $2$ 且第 $i$ 位为 $0/1/2$ 的最小交换次数。

以 $f_{i,j,k,l,0}$ 为例，由性质 3 可知，第 $i$ 位上的这个 $0$ 一定是原串的第 $j$ 个 $0$ 移过来的，如果我们能算出**此时**原串的第 $j$ 个 $0$ 的位置 $w$，那么转移就是 $f_{i,j,k,l,0}=\max(f_{i-1,j-1,k,l,1},f_{i-1,j-1,k,l,2})+(w-i)$。

考虑 $w$ 怎么求，首先找到原串中第 $j$ 个 $0$ 的位置 $p$，在状态 $f_{i,j,k,l,0}$ 时，共有 $k$ 个 $1$，$l$ 个 $2$，若 $p$ 之前有足够的 $1,2$ 那么第 $j$ 个 $0$ 的位置是不会变的，否则则需要把 $p$ 之后的 $1,2$ 前移，第 $j$ 个 $0$ 会被挤到更靠后的位置（可能要理解一下）。

我们记前 $i$ 位中有 $sum_{i,1}$ 个 $1$，$sum_{i,2} $ 个 $2$，则 $w=p+\max(0,k-sum_{p,1})+\max(0,l-sum_{p,2})$。

$100pts$：

$N\leq 400$，上面的状态是 $O(n^4)$ 的，考虑优化：$l=i-j-k$ 可以优化掉一维，然后滚动数组可以滚掉一维。

✿ヽ(°▽°)ノ✿完结撒花啦！

### Code

```
#include<bits/stdc++.h>
using namespace std;
const int N=405;
int n,id;
int pos[N][3],sum[N][3],c0,c1,c2;
int f[2][N][N][3];
char s[N];
int main()
{
	scanf("%d",&n);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++) {
		if(s[i]=='R') pos[++c0][0]=i;//第 c0 个 0 的位置
		if(s[i]=='G') pos[++c1][1]=i;
		if(s[i]=='Y') pos[++c2][2]=i;
		sum[i][0]=sum[i-1][0]+(s[i]=='R');//前 i 位 0 的数量
		sum[i][1]=sum[i-1][1]+(s[i]=='G');
		sum[i][2]=sum[i-1][2]+(s[i]=='Y');
	}
	memset(f,0x7f,sizeof(f));
	f[1][1][0][0]=pos[1][0]-1;
	f[1][0][1][1]=pos[1][1]-1;
	f[1][0][0][2]=pos[1][2]-1;
	for(int i=2;i<=n;i++) {
		id=(i&1)?1:0;
		for(int j=0;j<=c0;j++) {
			for(int k=0;k<=c1;k++) {
				if(i-j-k>c2) continue;
				if(j>0) {
					int p=pos[j][0];
					int w=p+max(0,k-sum[p][1])+max(0,i-j-k-sum[p][2]);
					f[id][j][k][0]=min(f[id^1][j-1][k][1],f[id^1][j-1][k][2])+w-i;
				}
				if(k>0) {
					int p=pos[k][1];
					int w=p+max(0,j-sum[p][0])+max(0,i-j-k-sum[p][2]);
					f[id][j][k][1]=min(f[id^1][j][k-1][0],f[id^1][j][k-1][2])+w-i;
				}
				if(i-j-k>0) {
					int p=pos[i-j-k][2];
					int w=p+max(0,j-sum[p][0])+max(0,k-sum[p][1]);
					f[id][j][k][2]=min(f[id^1][j][k][0],f[id^1][j][k][1])+w-i;
				}
			}
		}
		memset(f[id^1],0x7f,sizeof(f[id^1]));
	}
	if(n&1) {
		int ans=min(min(f[1][c0][c1][0],f[1][c0][c1][1]),f[1][c0][c1][2]);
		printf("%d",(ans<1e9)?ans:-1);
	}
	else {
		int ans=min(min(f[0][c0][c1][0],f[0][c0][c1][1]),f[0][c0][c1][2]);
		printf("%d",(ans<1e9)?ans:-1);
	}
	return 0;
}
```

---

## 作者：yyxmy (赞：3)

看上去贪心似乎不太可做， 数据范围也只有$400$, 所以可以考虑dp， 

有一个朴素状态$f[i][j][k][p][0/1/2]$表示前$i$个位置上$0,1,2$的个数分别为$j,k,p$，且第$i$位上的颜色为$0/1/2$的最小花费， 显然，$f[i][j][k][p]$是由$f[i - 1][j - 1][k][p]$, $f[i - 1][j][k - 1][p]$ 和 $f[i - 1][j][k][p - 1]$转移过来， 因为要求不能同色相邻，所以转移时$f[i]$ 和 $f[i - 1]$的最后一维$0/1/2$不能相同。

然后就是转移代价了。  
首先有一个比较显然的性质，即同种颜色的相对位置不会改变。  
假设当前的转移是  
$f[i][j - 1][k][p][1/2] --> f[i][j][k][p][0]$  
那么第$i$位上填的颜色为$0$, 该0显然由原序列上第j个0移动过来，我们可以
计算出当前该$0$的位置 $pos$, 花费代价即为$pos - i$。  
$k, p$的转移类似。
但是现在这个复杂度是$n^4$的， 需要优化。  

考虑优化， 因为$j + k + p = i$, 我们可以压缩一维， 变成 $f[i][j][k][0/1/2]$, 表示前$i$个位置$0,1,2$的个数分别为$j,k,i - j - k$, 第$i$位
为$0/1/2$的最小代价，转移类似，具体细节请康代码。
```cpp
#include<bits/stdc++.h>
#define reg register
#define maxn 405
using namespace std;
int n, sum[3][maxn], dp[2][maxn][maxn][3], R, G, Y, id[maxn], now, pos, ans, f[3][maxn];
char s[maxn];
int main() {
    cin >> n; scanf("%s", s + 1);
    for(int i = 1; i <= n; i++) {
        if(s[i] == 'R') sum[0][++R] = i; f[0][i] = f[0][i - 1] + (s[i] == 'R');
        if(s[i] == 'G') sum[1][++G] = i; f[1][i] = f[1][i - 1] + (s[i] == 'G');
        if(s[i] == 'Y') sum[2][++Y] = i; f[2][i] = f[2][i - 1] + (s[i] == 'Y');
        id[i] = id[i - 1] ^ 1;
    }
    memset(dp, 0x3f3f3f, sizeof dp);
    dp[1][1][0][0] = sum[0][1] - 1;
    dp[1][0][1][1] = sum[1][1] - 1;
    dp[1][0][0][2] = sum[2][1] - 1;
    for(int i = 2; i <= n; i++) {    
        for(int j = 0; j <= R; j++)
            for(int k = 0; k <= G; k++) {
                if(i - j - k > Y) continue;
                if(j) { 
                    pos = sum[0][j]; now = pos; now += max(0, k - f[1][pos]); now += max(0, i - j - k - f[2][pos]);  
                    dp[id[i]][j][k][0] = min(dp[id[i]][j][k][0], dp[id[i] ^ 1][j - 1][k][1] + now - i);
                    dp[id[i]][j][k][0] = min(dp[id[i]][j][k][0], dp[id[i] ^ 1][j - 1][k][2] + now - i);
                }
                if(k) {
                    pos = sum[1][k]; now = pos; now += max(0, j - f[0][pos]); now += max(0, i - j - k - f[2][pos]); 
                    dp[id[i]][j][k][1] = min(dp[id[i]][j][k][1], dp[id[i] ^ 1][j][k - 1][0] + now - i);
                    dp[id[i]][j][k][1] = min(dp[id[i]][j][k][1], dp[id[i] ^ 1][j][k - 1][2] + now - i);
                }
                    pos = sum[2][i - j - k]; now = pos; now += max(0, k - f[1][pos]); now += max(0, j - f[0][pos]);
                    dp[id[i]][j][k][2] = min(dp[id[i]][j][k][2], dp[id[i] ^ 1][j][k][0] + now - i);
                    dp[id[i]][j][k][2] = min(dp[id[i]][j][k][2], dp[id[i] ^ 1][j][k][1] + now - i);
            }
        memset(dp[id[i] ^ 1], 0x3f3f3f, sizeof dp[id[i] ^ 1]); 
    }
    ans = min(dp[id[n]][R][G][0], dp[id[n]][R][G][1]);
    ans = min(ans, dp[id[n]][R][G][2]); 
    if(ans >= 10000000) cout << -1 << endl;
    else cout << ans << endl;
}
```



---

## 作者：OrinLoong (赞：2)

## 前言
个人认为讲解比大多数题解细致一些，更适合蒟蒻~~体质~~阅读。参考了[这篇](https://www.luogu.com.cn/article/kb4ul2os)和[这篇](https://www.luogu.com.cn/article/09dpzghp)，在此一并致谢。
## [原题链接](https://www.luogu.com.cn/problem/P6116)
## 题意简介
给定一个长为 $N$，由 `R`、`Y`、`G` 组成的字符串，一次操作可以交换两个相邻的字符，求解使字符串中每个字符都与异种字符相邻所需的最小操作次数，若无解，输出 `-1`。
## 做法
### 一些部分分
【暂略】
### 正解
看着是个区间或线性 DP。胡一个非常典的状态： $dp_{i,j,k,p}$ 表示考虑到第 $i$ 个位置，选了 $j$ 个 `R`， $k$ 个 `Y`（自然，`G` 选了 $l=i-j-k$ 个），第 $i$ 位为 $p$ 所需的最小操作数。转移方程……等会再说。  
来想想这道题的性质？观察可得：  
1. 当且仅当某种字符个数大于 $\frac{N}{2}$ 时题目无解。  
   充分性显然；必要性在于，指定任意两个字符换位而不影响到其它字符是可以做到的，因此只要某字符个数不大于 $\frac{N}{2}$ 就必然能把它打散。
3. 交换相同的字符没有意义。
4. 由性质2，最优解（若存在）里**同种字符中各字符相对位置不变**，因为这不必要，可以被免去。

不过这些性质有什么作用呢？**性质 3**——本题的关键——**直接赋予了我们用线性 DP 做这道题的正确性与转移的确定性！**  
怎么理解？因为各字符相对位置不变，所以以线性DP的视角，每次加入一个字符时，我们既然知道这是第几个此类字符，于是我们也知道了它在原序列中的位置，代价的计算就可以 $O(1)$ 完成！  
具体来说，以 $dp_{i,j,k,0}$ 的转移为例，它的代价就是 $\min(dp_{i-1,j-1,k,1},dp_{i-1,j-1,k,2})+d$。其中，$d=pos_{j,0}+\max(k-sum_{pos_{j,0},1},0)+\max(l-sum_{pos_{j,0},2},0)-i$ ，即第 $j$ 个 `R` 原来所处的位置加上它被换到前面的 `Y` 和 `G` 挤到后面去的一段距离减去当前坐标所得。  
余下的就是实现细节了，我们预处理各字符数量及每种字符的第 $x$ 个出现在哪里，初始化 $i=1$ 的 dp 值而其余设为正无穷；留意 $l$ 可能出现的非法值（因为它是被减出来的）……当然，还能拿滚动数组把 $i$ 这一维滚掉。
## 代码
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN=4e2+5,INF=0x3f3f3f3f;
int N,A[MAXN],sum[MAXN][3],pos[MAXN][3],dp[2][MAXN][MAXN][3],ans=INF;
char ch;
int main(){
	scanf("%d",&N);
	for(int i = 1;i <= N;i++){
		scanf(" %c",&ch);
		for(int j = 0;j < 3;j++)sum[i][j]=sum[i-1][j];
		if(ch=='R')A[i]=0;
		if(ch=='Y')A[i]=1;
		if(ch=='G')A[i]=2;
		sum[i][A[i]]++;pos[sum[i][A[i]]][A[i]]=i;
	}
	memset(dp,0x3f,sizeof(dp));
	dp[1][1][0][0]=pos[1][0]-1;
	dp[1][0][1][1]=pos[1][1]-1;
	dp[1][0][0][2]=pos[1][2]-1;
	for(int i = 2;i <= N;i++){
		int ri=i&1;
		for(int j = 0;j <= sum[N][0];j++){
			for(int k = 0;k <= sum[N][1];k++){
				int l=i-j-k;
				if(l>sum[N][2])continue;
				if(j){
					int d=pos[j][0]+max(k-sum[pos[j][0]][1],0)+max(l-sum[pos[j][0]][2],0)-i;
					dp[ri][j][k][0]=min(dp[ri^1][j-1][k][1],dp[ri^1][j-1][k][2])+d;
				}
				if(k){
					int d=pos[k][1]+max(j-sum[pos[k][1]][0],0)+max(l-sum[pos[k][1]][2],0)-i;
					dp[ri][j][k][1]=min(dp[ri^1][j][k-1][0],dp[ri^1][j][k-1][2])+d;
				}
				if(l>0){
					int d=pos[l][2]+max(j-sum[pos[l][2]][0],0)+max(k-sum[pos[l][2]][1],0)-i;
					dp[ri][j][k][2]=min(dp[ri^1][j][k][0],dp[ri^1][j][k][1])+d;
				}
			}
		}
		memset(dp[ri^1],0x3f,sizeof(dp[ri^1]));
	}
	for(int i = 0;i < 3;i++)ans=min(ans,dp[N&1][sum[N][0]][sum[N][1]][i]);
	if(ans==INF)ans=-1;
	printf("%d",ans);
	return 0;
}
```
## 复盘
### 长话
笔者考场上并没有出正解，而是将这道题当成了类似[括号序列](https://www.luogu.com.cn/problem/P7914)那样涉及合并的区间 DP 去想了，胡了一个这样的状态：  
> $dp_{i,j,k,l}$ 表示考虑 $[i,j]$ 区间，第 $i$ 位填 $k$、第 $j$ 位填 $l$ 需要的交换次数

然而，如果发现了这题上述的性质，就会发现线性 DP 就够了，没必要区间；否则，这题做不出来。（至少我暂时想不到别的方法）~~WHAT CAN I SAY?~~  
进一步思考这道题的本质。这道题实际上给定了 3 个字符集，并要求重新排序满足要求，因为集内字符相对顺序不换位是最优解（若存在）的充要条件，因此对于一个状态来说，转移只和给定已有的各字符数量有关系，因此可以线性 DP 。
### 短说
**几类字符要重排，集内顺序不变改；转移选择元素定，不用区间用线性。**

---

## 作者：_HCl_ (赞：2)

# P6116 题解

**题意简述**

给定一个由三个字母组成的字符串，每次操作可以交换相邻两项，询问最小的操作次数，使得字符串任意相邻的两项都不相同。

**思路引导**

首先注意到，如果我们想要将一个元素移动到另一个位置上，可以对它进行若干次交换，交换的次数就等于移动的距离。

接下来考虑 DP。设 $f_{i,j,k,R/G/Y}$ 表示前 $i$ 项已经合法，有 $j$ 个 R，$k$ 个 G，$i-j-k$ 个 Y（下文中记作 $l$）并且第 $i$ 项是 R/G/Y。不难列出转移方程（以第 $i$ 项为 R 为例，其它同理）：

$$
f_{i,j,k,R}=\min(f_{i-1,j-1,k,B},f_{i-1,j-1,k,Y})+d
$$

这里 $d$ 代表移动的距离。那么怎么计算 $d$ 呢？我们可以先计算当前状态下要被移过来的 R 的位置 $w$，这样就有 $d=w-i$。

考虑计算 $w$。首先，要被移动过来的这个 R 就是字符串中的第 $j$ 项。我们可以容易地计算出在原字符串中第 $j$ 个 $R$ 的位置 $pos$，然后考虑原本在这个 R 之后的 G 和 Y 被移动到这个 R 之前，会把这个 R 向后推，推的距离就是这些 G 和 Y 的个数。综上，设 $sum_{i,G}$ 和 $sum_{i,Y}$ 分别表示 $1$ 到 $i$ 项中 G 和 Y 的个数，可以列出：

$$
w=pos+\max(0,k-sum_{pos,G})+\max(0,l-sum_{pos,Y})
$$

另外，$f$ 的第一维可以进行滚动优化。

**代码**

代码写的比较答辩，仅供参考。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=401;
int n;
string str;
int sum[N][3],pos[N][3];
int f[2][N][N][3];
int main(){
	cin>>n;
	cin>>str;str=" "+str;
	for(int i=1;i<=n;++i){
		sum[i][0]=sum[i-1][0];
		sum[i][1]=sum[i-1][1];
		sum[i][2]=sum[i-1][2];
		if(str[i]=='R')sum[i][0]++,pos[sum[i][0]][0]=i;
		else if(str[i]=='G')sum[i][1]++,pos[sum[i][1]][1]=i;
		else sum[i][2]++,pos[sum[i][2]][2]=i;
	}
	memset(f,0x3f,sizeof(f));
	f[1][1][0][0]=pos[1][0]-1;
	f[1][0][1][1]=pos[1][1]-1;
	f[1][0][0][2]=pos[1][2]-1;
	for(int i=2;i<=n;++i){
		int c=i&1;
		for(int j=0;j<=sum[n][0];++j){
			for(int k=0;k<=sum[n][1];++k){
				int l=i-j-k;
				if(l>sum[n][2])continue;
				if(j){
					int w=pos[j][0]+max(k-sum[pos[j][0]][1],0)+max(l-sum[pos[j][0]][2],0);
					f[c][j][k][0]=min(f[c^1][j-1][k][1],f[c^1][j-1][k][2])+w-i;
				}
				if(k){
					int w=pos[k][1]+max(j-sum[pos[k][1]][0],0)+max(l-sum[pos[k][1]][2],0);
					f[c][j][k][1]=min(f[c^1][j][k-1][0],f[c^1][j][k-1][2])+w-i;
				}
				if(l>0){//注意l有可能是负数
					int w=pos[l][2]+max(j-sum[pos[l][2]][0],0)+max(k-sum[pos[l][2]][1],0);
					f[c][j][k][2]=min(f[c^1][j][k][0],f[c^1][j][k][1])+w-i;
				}
			}
		}
		memset(f[c^1],0x3f,sizeof(f[c^1]));
	}
	int ans=min(f[n&1][sum[n][0]][sum[n][1]][0],min(f[n&1][sum[n][0]][sum[n][1]][1],f[n&1][sum[n][0]][sum[n][1]][2]));
	if(ans>=1e9)cout<<"-1";
	else cout<<ans;
	return 0;
}
```

---

## 作者：masonpop (赞：2)

先考虑确定最终态的情况下如何最小化操作次数。

我们先把原序列编号 $1\sim n$，由于同色位置不会交换，因此可以求出最终态每个位置应该去哪里。这样就是一个冒泡排序次数问题，显然答案为逆序对数。

这样有点抽象，以样例为例：

`RRGYY` 编号 `12345`。

最终态为 `RYRGY` 时编号为 `14235`。逆序对数为 $2$，这就是最优方案。

那么就可以 DP 了。设 $f_{i,c_0,c_1,c_2,0/1/2}$ 表示当前考虑到第 $i$ 位，`R,G,Y` 分别填了 $c_0,c_1,c_2$ 个,最后一位是 $0/1/2$ 时逆序对数的最小值。转移使用刷表法。为了快速计算逆序对数的增长，可以预处理数组 $g_{0/1/2,i,j}$ 表示第 $0/1/2$ 种颜色前 $i$ 位编号有多少个 $>j$。并设 $h_{0/1/2,i}$ 表示颜色 $0/1/2$ 第 $i$ 个的编号。转移比较显然，建议自己写。

这样做是 $O(n^4)$ 的。但注意到 $c_0+c_1+c_2=i$，所以直接去掉第一维即可。

总复杂度 $O(n^3)$。[代码](https://www.luogu.com.cn/paste/cbpa4kh3)。

---

## 作者：DHeasy (赞：1)

考虑 dp，设 $dp_{i,j,k,0/1/2}$ 表示前 $i+j+k$ 个字符中，有 $i$ 个为 `R`，有 $j$ 个为 `Y`，有 $k$ 个为 `G`，且最后一个为 `R`/`Y`/`G` 的最小步数。

考虑如何转移，不妨设下一个选择的字符为 `R`，显然是将第 $i+1$ 个 `R` 移动到第 $i+j+k+1$ 位，即用 $\min(dp_{i,j,k,1},dp_{i,j,k,2})+w$，其中 $w$ 为转移的贡献。

计算贡献是简单的，手玩一下发现在一个字符之后的情况是不会影响该字符的答案。所以 $w$ 即为原字符串在该字符之前且没有确定位置的字符数量。形式化的，设当前字符前有 $a$ 个 `R`，$b$ 个 `Y`，$c$ 个 `G`，则上述转移方程的 $w=\max(0,a-i)+\max(0,b-j)+\max(0,c-k)$，注意到若当前字符为 `R`，第一项的值为 $0$，可以省略，其他也同理。

最后考虑初值，$dp_{0,0,0,0},dp_{0,0,0,1},dp_{0,0,0,2}$ 都为 $0$，其他都为 $\inf$。

于是就做完了，时空复杂度均为 $O(n^3)$，空间复杂度好像可以优化到 $O(n^2)$。

### 代码


```cpp
#include<bits/stdc++.h>
#define ll long long
#define re register
using namespace std;
inline ll read(){
	ll res=0ll,f=1;
	char c;
	for(;(c=getchar())<'0'||c>'9';c=='-'?f=-f:0);
	while(c>='0' && c<='9') res=(res<<1) + (res<<3) + c-'0',c=getchar();
	return res*f;
}
inline ll Max(re ll x,re ll y){return x>y?x:y;}
inline ll Min(re ll x,re ll y){return x<y?x:y;}
inline void cmax(re auto &x,re auto y){x=Max(x,y);}
inline void cmin(re auto &x,re auto y){x=Min(x,y);}
/*-----------------*/
const int N=410;
const int inf=1e9;
int n,dp[N][N][N][3];char s[N];
int x,a[N][3],y,b[N][3],z,c[N][3];
int main(){
	n=read();scanf("%s",s+1);
	for(re int i=1;i<=n;i++)
		if(s[i]=='R')
			a[++x][0]=i,a[x][1]=y,a[x][2]=z;
		else if(s[i]=='Y')
			b[++y][0]=i,b[y][1]=x,b[y][2]=z;
		else
			c[++z][0]=i,c[z][1]=x,c[z][2]=y;
	/*
	dp[i][j][k][0/1/2]
		选了 i 个 R，j 个 Y，k 个 G，最后一个是 R/Y/G 的最少步数
	*/
	for(re int i=0;i<=x;i++)
	for(re int j=0;j<=y;j++)
	for(re int k=0;k<=z;k++)
		dp[i][j][k][0]=dp[i][j][k][1]=dp[i][j][k][2]=inf;
	dp[0][0][0][0]=dp[0][0][0][1]=dp[0][0][0][2]=0;
	for(re int i=0;i<=x;i++)
	for(re int j=0;j<=y;j++)
	for(re int k=0;k<=z;k++)
		cmin(dp[i+1][j][k][0],dp[i][j][k][1]+Max(0,a[i+1][1]-j)+Max(0,a[i+1][2]-k)),
		cmin(dp[i+1][j][k][0],dp[i][j][k][2]+Max(0,a[i+1][1]-j)+Max(0,a[i+1][2]-k)),
		cmin(dp[i][j+1][k][1],dp[i][j][k][0]+Max(0,b[j+1][1]-i)+Max(0,b[j+1][2]-k)),
		cmin(dp[i][j+1][k][1],dp[i][j][k][2]+Max(0,b[j+1][1]-i)+Max(0,b[j+1][2]-k)),
		cmin(dp[i][j][k+1][2],dp[i][j][k][0]+Max(0,c[k+1][1]-i)+Max(0,c[k+1][2]-j)),
		cmin(dp[i][j][k+1][2],dp[i][j][k][1]+Max(0,c[k+1][1]-i)+Max(0,c[k+1][2]-j));
	int ans=Min(dp[x][y][z][0],Min(dp[x][y][z][1],dp[x][y][z][2]));
	return !printf("%d\n",ans==inf?-1:ans);
}
```

---

## 作者：随情英 (赞：1)

### 1. $n \leq 15$

范围很小， 考虑暴力。
最多只有 $3^{15}$ 状态，$bfs$ 可做

[bfs](https://www.luogu.com.cn/paste/vzk7eg2x)

### 2. 字符串仅包含 $R$ , $G$

末状态只有两种，红色为第一个或者绿色为第一个

两种相同颜色交换没有意义， 考虑先固定一种状态， 只维护一种颜色，贪心。当一种颜色归位， 另一种颜色也完成

设 $R$ 的个数为 $cntR$, G 的个数为 $cntG$, 若 $cntR - cntG > 1$, 无解

### 3. $n \leq 400$
显然不能枚举末状态。考虑
$dp$。

设 $0$ 表示 'R', $1$ 表示 'G', $2$ 表示 'Y', 

朴素状态 $f[i][j][k][l][0/1/2]$ 表示前 $i$ 个位置上 $0,1,2$ 的个数分别为 $j,k,l$，且第 $i$ 位上的颜色为 0/1/2 的逆序对数，显然最小移动步数等于逆序对数。

根据同色交换无意义， 可知交换后局面同色之间相对位置不变

如果第 $i$ 位是 $0$, 显然应从序列上第 $j$ 个 $0$ 转移过来。如果 $i$， 前面的 $1$ 或 $2$，不足 k/l 个，交换时需要后面交换过来。

因为 $j + k + l = i$, 可以优化状态，为$f[i][j][k][0/1/2]$。

```cpp
/*
 * @Autor: suiqingying
 * @Date: 2020-11-17 21:08:41
 * @LastEditors: suiqingying
 * @LastEditTime: 2020-11-18 11:19:43
 */
#include <bits/stdc++.h>
inline int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (isdigit(c)) {
        x = x * 10 + c - '0', c = getchar();
    }
    return x * f;
}
const int maxn = 401;
int n, cnt[3], w[3][maxn], sum[3][maxn];
int f[2][maxn][maxn][3];
inline int calc(int x, int y, int z, int c) {
    int pos,ans=0;
    if (c == 0)
        pos = w[0][x + 1],ans-=std::max(0, sum[0][pos-1] - x);
    if (c == 1)
        pos = w[1][y + 1],ans-=std::max(0, sum[1][pos-1] - y);
    if (c == 2)
        pos = w[2][z + 1],ans-=std::max(0, sum[2][pos-1] - z);
    pos--;
    ans += std::max(0, sum[0][pos] - x) + std::max(0, sum[1][pos] - y) + std::max(0, sum[2][pos] - z);
    return ans;
}
int main() {
    int n = read();
    for (int i = 1; i <= n; ++i) {
        char ch = getchar();
        while (ch != 'R' && ch != 'G' && ch != 'Y') {
            ch = getchar();
        }
        int c = ch == 'R' ? 0 : ch == 'G' ? 1 : 2;
        w[c][++cnt[c]] = i;
        sum[0][i] = sum[0][i - 1], sum[1][i] = sum[1][i - 1], sum[2][i] = sum[2][i - 1];
        sum[c][i]++;
    }
    if (cnt[0] > (n + 1) / 2 || cnt[1] > (n + 1) / 2 || cnt[2] > (n + 1) / 2) {
        puts("-1");
        return 0;
    }
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            f[1][i][j][0] = f[1][i][j][1] = f[1][i][j][2] = 0x3f3f3f3f;
            f[0][i][j][0] = f[0][i][j][1] = f[0][i][j][2] = 0x3f3f3f3f;
        }
    }
    if (cnt[0])
        f[1][1][0][0] = w[0][1] - 1;
    if (cnt[1])
        f[1][0][1][1] = w[1][1] - 1;
    if (cnt[2])
        f[1][0][0][2] = w[2][1] - 1;
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j <= std::min(i, cnt[0]); ++j) {
            for (int k = std::max(0, i - j - cnt[2]); j + k <= i && k <= cnt[1]; ++k) {
                if (j) {
                    f[i & 1][j][k][0] = std::min(f[i & 1 ^ 1][j - 1][k][1], f[i & 1 ^ 1][j - 1][k][2]) +
                                        calc(j - 1, k, i - j - k, 0);
                }
                if (k) {
                    f[i & 1][j][k][1] = std::min(f[i & 1 ^ 1][j][k - 1][0], f[i & 1 ^ 1][j][k - 1][2]) +
                                        calc(j, k - 1, i - j - k, 1);
                }
                if (i - j - k) {
                    f[i & 1][j][k][2] =
                        std::min(f[i & 1 ^ 1][j][k][0], f[i & 1 ^ 1][j][k][1]) + calc(j, k, i - j - k - 1, 2);
                }
            }
        }
    }
    int ans = std::min(std::min(f[n & 1][cnt[0]][cnt[1]][0], f[n & 1][cnt[0]][cnt[1]][1]),
                       f[n & 1][cnt[0]][cnt[1]][2]);
    printf("%d\n", ans);
    return 0;
}

---

## 作者：ivyjiao (赞：0)

校内模拟赛出了两遍了，来写一下。

双倍经验：P6116，AT_joi2019ho_c。

首先考虑什么时候无解：当一种颜色的数量大于 $\lceil \dfrac n 2\rceil$ 时无解（这个要注意不能写成 $\lfloor \dfrac n 2\rfloor$，不然洛谷的 P6116 能过，AT 上的原题会被 hack）。

然后发现性质 $1$：交换同种颜色无意义。

由性质 $1$ 可得性质 $2$：若按原字符串的顺序给每个字符从前到后编号，则相同字符的内部顺序不变。

模拟赛第二次出的时候把 $R,G,B$ 换成了 $0,1,2$，这里直接按 $0,1,2$ 讲。

发现数字只有三种，感觉像是[乌龟棋](https://www.luogu.com.cn/problem/P1541)模型（我自己起的名字），而且数据范围很小，考虑建一个高维 dp。

设 $dp_{i,j,k,l}$ 为枚举到 $i$ 位，有 $j$ 个 $0$，$k$ 个 $1$，$i-j-k$ 个 $2$，当前位更改后为 $l$ 的最小交换次数。

由性质 $2$ 可得：$dp_{i,j,k,0}$ 一定是从第 $j$ 个 $0$ 那里转来的，剩下两个数同理（这里可能需要思考一下）。

依题意，若此时的第 $j$ 个 $0$ 的位置为 $x$，可得转移式子：$dp_{i,j,k,0}=\max(dp_{i-1,j-1,k,1},dp_{i-1,j-1,k,2})+|x-i|$，仔细想想，其实绝对值可以去掉的。

考虑求出 $x$，先找到原串中的第 $j$ 个 $0$ 的位置 $y$（直接预处理就行），在状态 $dp_{i,j,k,0}$ 中，有 $k$ 个 $1$，$l$ 个 $2$，若原串中 $y$ 以前的 $1,2$ 数量足够多那就不用做任何事情，$x=y$，否则需要把 $y$ 之后的 $1,2$ 前移，第 $j$ 个 $0$ 会被往后挤，则 $x=y+\max(0,k-sum_{y,1})+\max(0,i-j-k-sum_{y,2})$，$sum_{i,l}$ 表示前 $i$ 个位置有多少个 $l$，直接预处理。

然后发现这两个式子是可以合并的，直接用后面这个就行。

然后就过了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=401;
int n,dp[2][N][N][3],a[N][3],sum[N][3],l1,l2,l3;
char s[N];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s[i];
        if(s[i]=='R') a[++l1][0]=i;
        if(s[i]=='G') a[++l2][1]=i;
        if(s[i]=='Y') a[++l3][2]=i;
        sum[i][0]=sum[i-1][0]+(s[i]=='R');
        sum[i][1]=sum[i-1][1]+(s[i]=='G');
        sum[i][2]=sum[i-1][2]+(s[i]=='Y');
    }
    if(max({l1,l2,l3})>(n+1)/2){
        cout<<-1;
        return 0;
    }
    memset(dp,0x3f,sizeof dp);
	dp[1][1][0][0]=a[1][0]-1;
	dp[1][0][1][1]=a[1][1]-1;
	dp[1][0][0][2]=a[1][2]-1;
    for(int i=2;i<=n;i++){
        for(int j=0;j<=l1;j++){
            for(int k=0;k<=l2;k++){
                int l=i-j-k;
                if(l>l3) continue;
                if(j) dp[i%2][j][k][0]=min(dp[(i-1)%2][j-1][k][1],dp[(i-1)%2][j-1][k][2])+a[j][0]+max(0,k-sum[a[j][0]][1])+max(0,l-sum[a[j][0]][2])-i;
                if(k) dp[i%2][j][k][1]=min(dp[(i-1)%2][j][k-1][0],dp[(i-1)%2][j][k-1][2])+a[k][1]+max(0,j-sum[a[k][1]][0])+max(0,l-sum[a[k][1]][2])-i;
                if(l) dp[i%2][j][k][2]=min(dp[(i-1)%2][j][k][0],dp[(i-1)%2][j][k][1])+a[l][2]+max(0,j-sum[a[l][2]][0])+max(0,k-sum[a[l][2]][1])-i;
            }
        }
    }
    cout<<min({dp[n%2][l1][l2][0],dp[n%2][l1][l2][1],dp[n%2][l1][l2][2]});
}
```

---

## 作者：Anonymely (赞：0)

思考一下最后的答案形态，一个显然且重要的结论是同种颜色内部相对顺序不变。

这启发我们按照序列顺序 dp，具体的设 $f_{i,j,k,0/1/2/3}$ 表示选了 $i$ 个 $0$，$j$ 个 $1$，$k$ 个 $2$，结尾是 $0/1/2$ 的最小代价，考虑从哪里转移来，以 $0$ 举例：枚举上一个是 $1$ 还是 $2$，从 $f_{i-1,j,k,1}$ 和 $f_{i-1,j,k,2}$ 转移而来。

问题在于转移代价如何计算，即第 $i$ 个 $0$ 应该移动多少。

假设原序列种第 $i$ 个 $0$ 在 $x$ 上，如果 $x$ 前面的 $1$ 足够了，即不小于 $j$，那么就不需考虑 $j$，否则需要将一些 $j$ 移动到 $x$ 前，代价即为 $j - cnt_j$，对于 $2$ 也是一样，这样贡献就可以快速算了。

复杂度 $O(n^3)$。


```cpp
	if (c[0]) f[1][0][0][0] = pos[1][0] - 1;
	if (c[1]) f[0][1][0][1] = pos[1][1] - 1;
	if (c[2]) f[0][0][1][2] = pos[1][2] - 1;
	for (int i = 0; i <= c[0]; i++) {
		for (int j = 0; j <= c[1]; j++) {
			for (int k = 0; k <= c[2]; k++) {
				int now = i + j + k;
				if (i) ckmin(f[i][j][k][0], min(f[i - 1][j][k][1], f[i - 1][j][k][2]) + (pos[i][0] + max(0, j - s[pos[i][0]][1]) + max(0, k - s[pos[i][0]][2]) - now));
				if (j) ckmin(f[i][j][k][1], min(f[i][j - 1][k][0], f[i][j - 1][k][2]) + (pos[j][1] + max(0, i - s[pos[j][1]][0]) + max(0, k - s[pos[j][1]][2]) - now));
				if (k) ckmin(f[i][j][k][2], min(f[i][j][k - 1][0], f[i][j][k - 1][1]) + (pos[k][2] + max(0, i - s[pos[k][2]][0]) + max(0, j - s[pos[k][2]][1]) - now));
			}
		}
	}
	int ans = min({f[c[0]][c[1]][c[2]][0], f[c[0]][c[1]][c[2]][1], f[c[0]][c[1]][c[2]][2]});
	if (ans >= 1e9) cout << -1 << '\n';
	else cout << ans << '\n';
```

---

## 作者：FutaRimeWoawaSete (赞：0)

**sol of P6116**

考虑若确定最终序列，怎么交换使得花费最小。

显然我们将最终序列的位置对照三个颜色的原本位置从小到大重新标号然后做冒泡排序是花费最小的，因为若不从小到大显然不优，冒泡排序已被证明是该操作下最小花费的一种方案。

考虑这样操作下任意颜色间的相对位置不会变化，因为交换相同颜色肯定浪费了操作。

设 $dp_{i,sm_0,sm_1,sm_2,op=0/1/2}$ 表示前 $i$ 个数有 $sm_0$ 个 $0$，$sm_1$ 个 $1$，$sm_2$ 个 $2$ 且第 $i$ 位是 $0/1/2$ 的最小花费。

冒泡排序时我们对于位置是从前往后依次填，所以在这里我们效仿冒泡排序即可。找到当前第 $sm_{op}$ 个 $op$ 的位置，显然在冒泡的过程中非钦定向前交换的数只会一直向后退，通过维护原本序列前缀 $0,1,2$ 个数，我们即可推算出当前第 $sm_{op}$ 个 $op$ 在当前序列的位置，设为 $now$。

设 $ano_{op,0},ano_{op,1}$ 表示非 $op$ 的另两种颜色。

则转移方程：

- $dp_{i,sm_0,sm_1,sm_2,op} \leftarrow dp_{i - 1,sm_0-[op == 0],sm_1 - [op == 1],sm_2 - [op == 2],ano_{op,0}}$

- $dp_{i,sm_0,sm_1,sm_2,op} \leftarrow dp_{i - 1,sm_0-[op == 0],sm_1 - [op == 1],sm_2 - [op == 2],ano_{op,1}}$

两者取最小值。

将 $sm2$ 表示成 $i - sm_0 - sm_1$，若还过不了就滚动数组，即可时间复杂度 $O(n ^ 3)$，空间复杂度 $O(n ^ 2)$ 通过此题。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 405;
int n,m,dp[2][Len][Len][3];//dp_{i,j,k,p,0/1/2}
char s[Len];int a[Len];
int pos[3][Len],num[3],sum[3][Len],ano[3][2];
inline int Iabs(int x){if(x < 0) x = -x;return x;}
int main()
{
	scanf("%d",&n);
	ano[0][0] = 1 , ano[0][1] = 2 , ano[1][0] = 0 , ano[1][1] = 2 , ano[2][0] = 0 , ano[2][1] = 1;
	scanf("%s",s + 1);
	for(int i = 1 ; i <= n ; i ++) 
	{
		if(s[i] == 'R') a[i] = 0;
		else if(s[i] == 'G') a[i] = 1;
		else if(s[i] == 'Y') a[i] = 2;
	}
	for(int i = 1 ; i <= n ; i ++) 
	{
		pos[a[i]][++ num[a[i]]] = i;
		for(int j = 0 ; j <= 2 ; j ++) sum[j][i] = sum[j][i - 1] + (a[i] == j);
	}
	if(max(num[0] , max(num[1] , num[2])) > (n + 1) / 2) return puts("-1") & 0;
	int ans = n * n + 1;
	for(int i = 0 ; i <= 1 ; i ++)
		for(int j = 0 ; j <= n ; j ++) 
			for(int k = 0 ; k <= n ; k ++)
				for(int op = 0 ; op <= 2 ; op ++) dp[i][j][k][op] = n * n + 1;
	dp[0][0][0][0] = dp[0][0][0][1] = dp[0][0][0][2] = 0;
	for(int i = 1 ; i <= n ; i ++) 
		for(int op = 0 ; op <= 2 ; op ++)
		{
			int sm[3];sm[0] = sm[1] = sm[2] = 0;
			for(sm[0] = 0 ; sm[0] <= num[0] && sm[0] <= i ; sm[0] ++)
				for(sm[1] = 0 ; sm[0] + sm[1] <= i && sm[1] <= num[1] ; sm[1] ++)
				{
					sm[2] = i - sm[0] - sm[1];
					if(sm[2] > num[2]) continue;
					if(!sm[op]) continue;
					int now = pos[op][sm[op]] , ad = 0;
					for(int j = 0 ; j <= 1 ; j ++) ad += max(0 , sm[ano[op][j]] - sum[ano[op][j]][now]);
					now += ad;
					dp[i & 1][sm[0]][sm[1]][op] = min(dp[(i - 1) & 1][sm[0] - (op == 0)][sm[1] - (op == 1)][ano[op][0]] , dp[(i - 1) & 1][sm[0] - (op == 0)][sm[1] - (op == 1)][ano[op][1]]) + Iabs(now - i); 
					if(i == n) ans = min(ans , dp[i & 1][sm[0]][sm[1]][op]);
				}
		}
	printf("%d\n",ans);
	return 0;
}
```

---

