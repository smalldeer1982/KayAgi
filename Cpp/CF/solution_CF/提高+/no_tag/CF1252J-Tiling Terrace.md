# Tiling Terrace

## 题目描述

Talia 在雅加达郊区新买了一栋废弃房子，这里有个漂亮而悠长的院子，可以用 $1 \times N$ 的一维网格来表示，其中一共有 $N$ 个单元格。为了让房子更美观，Talia 打算在院子里铺设瓷砖建造一个露台。院子里的每个单元格要么是土壤（用字符 '.' 表示），要么是岩石（用字符 '#' 表示），其中不超过 50 个单元格是岩石。

由于 Talia 相信迷信，她希望用有驱赶鬼魂能力的神秘瓷砖来装点露台。这些瓷砖有三种类型：

- Type-1：覆盖 $1 \times 1$ 的单元格，只能放在土壤单元格上（"."）。
- Type-2：覆盖 $1 \times 2$ 的单元格，只能放在两个相邻的土壤单元格上（".."）。
- Type-3：覆盖 $1 \times 3$ 的单元格，只能放在相邻的土壤-岩石-土壤单元格上（".#."）。

每种类型的瓷砖都有其独特的驱鬼能力：Type-1 每天可以驱赶 $G_1$ 个鬼魂，Type-2 可以驱赶 $G_2$ 个，Type-3 可以驱赶 $G_3$ 个。此外，必须遵循以下规则以确保瓷砖的效果：

1. 瓷砖之间不能重叠，即每个单元格最多只能被一块瓷砖覆盖。
2. Type-1 瓷砖最多只能使用 $K$ 块，而 Type-2 和 Type-3 的使用数量没有限制。

Talia 对鬼非常恐惧，所以她希望露台上的瓷砖能够驱赶尽可能多的鬼魂。请帮助她找到露台最大驱鬼能力，即每天能驱赶的最大鬼魂数量。注意，Talia 并不需要铺满所有的单元格，只需要让驱赶的鬼魂数量最大即可。

## 说明/提示

### 示例说明 1

设 "A" 为 Type-1 瓷砖，"BB" 为 Type-2 瓷砖，"CCC" 为 Type-3 瓷砖。在这种情况下，铺设模式 "ACCCBB" 可以让露台每天驱赶最多的鬼魂，总计为 $10 + 40 + 25 = 75$。

### 示例说明 2

这个示例与前一个示例中的院子相同，但每块 Type-2 瓷砖每天可驱赶的鬼魂更多。通过 "BB#BBA" 或 "BB#ABB" 的铺设模式，每天可以驱赶 $100 + 100 + 10 = 210$ 个鬼魂。注意这里第三个单元格没有被瓷砖覆盖。

### 示例说明 3

通过 "ACCCA.#"、"ACCC.A#" 或 ".CCCAA#" 的铺设，可以每天驱赶最多 $30 + 100 + 30 = 160$ 个鬼魂。注意，最后一个单元格无法覆盖。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
6 4 10 25 40
..#...
```

### 输出

```
75
```

## 样例 #2

### 输入

```
6 4 10 100 40
..#...
```

### 输出

```
210
```

## 样例 #3

### 输入

```
7 2 30 10 100
..#...#
```

### 输出

```
160
```

# 题解

## 作者：gyh20 (赞：4)

发现自己比现有的题解做法更好来写一篇题解。

观察到题目中的不超过 $K$ 这一条件不方便处理，可以进行如下转化：

若固定方案 $3$ 的数量，求出**最多**可使用的 $2$ 操作数量。

由于一个 $2$ 操作在任意情况下都可以转化为两个 $1$ 操作，所以这样做是足够的。可以在求出最多 $2$ 操作之后进行贪心或者分类讨论部分转化为 $1$ 操作。

一个朴素的 DP 可以设 $f_{i,j}$ 表示前 $i$ 个位置，有 $j$ 个 $3$ 操作，最多的 $2$ 操作个数，令 $d$ 为 $#$ 的个数，时间复杂度 $O(nd)$，已经足够通过本题。

一个更优的方法是对于整段直接转移，因为一段连续的 $.$ 可以直接变为 $len/2$ 个操作，记录 $f_{i,j,0/1}$ 表示前 $i$ 段，选了 $j$ 个操作，最后一个位置选/未选，时间复杂度 $O(n+d^2)$。

AC 代码（注意对 -inf 的处理）：

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,m,f[52][52][2],g1,g2,g3,p[100002],ans,tot;
char s[100002];
inline int calc(re int x){if(x>=0)return x>>1;else return -1000000000;}
int main(){
	n=read(),m=read(),g1=read(),g2=read(),g3=read(),scanf("%s",s+1);
	for(re int i=1;i<=n;++i)if(s[i]=='#')p[++tot]=i;
	p[++tot]=n+1,memset(f,-0x3f,sizeof(f)),f[0][0][0]=0;
	for(re int i=1;i<=tot;++i)
		for(re int j=0;j<=i;++j){
			f[i][j][0]=max(f[i-1][j][0]+calc(p[i]-p[i-1]-1),f[i-1][j][1]+calc(p[i]-p[i-1]-2));
			if(j)f[i][j][1]=max(f[i-1][j-1][0]+calc(p[i]-p[i-1]-2),f[i-1][j-1][1]+calc(p[i]-p[i-1]-3));
			f[i][j][0]=max(f[i][j][0],-1000000000),f[i][j][1]=max(f[i][j][1],-1000000000);
		}
	for(re int i=0;i<=tot;++i)
	if(f[tot][i][0]>=0){
		re int x=f[tot][i][0],y=n-tot+1-i*2-(x<<1);
		y=min(y,m);
		if(g1*2>g2){
			re int tmp=min(m-y>>1,x);
			x-=tmp,y+=tmp<<1;
			if(x&&y!=m&&g1>g2)--x,++y;
		}
		ans=max(ans,i*g3+x*g2+y*g1);
	}
	printf("%d",ans);
}

```


感觉可以根据段长度奇偶性分类讨论然后直接贪心选做到 $O(n)$，但还没有仔细想，~~留给读者作为作业~~。

---

## 作者：傅思维666 (赞：1)


## 题解：

[博客食用口味更佳](https://www.cnblogs.com/fusiwei/p/11791446.html)

非常容易判断是一道$DP$的题目。

联想一下这道题目：[CF358D Dima and Hares]( https://www.cnblogs.com/fusiwei/p/11715530.html )

那么我们分方式决策，可以看出：第一种和第二种的选择都仅包含"."，只有第三种选择有"#"，那么我们可以考虑分段进行决策：将整个序列分成以"#"相隔开的段，并用$a[i]$数组保存$i$段中"."的个数。

那么我们设置状态$dp[i][j][0/1]$表示前$j$段用了$i$次方式$1$，后面的$0/1$表示最后的"#"有没有用方式$3$所获得的最大价值。

那么我们转移的时候就只需要考虑方式二的使用次数。

转移方程需要分类讨论。另外地，还有一种情况是不选择完这$n$个字符。这个东西可以在枚举方式1的时候用除以二自动取整来实现。

可以结合代码理解：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;
const int maxn=1e5+10;
int n,k,g1,g2,g3,tot,ans;
char s[maxn];
int a[maxn],dp[60][maxn][5];
//dp[i][j][0/1]表示前j段使用i次方式1，最后一个"#"是否选用方式3所得的最大利益。
signed main()
{
    scanf("%I64d%I64d%I64d%I64d%I64d",&n,&k,&g1,&g2,&g3);
    scanf("%s",s+1);
    tot=1;
    for(int i=1;i<=n;i++)
    {
        if(s[i]=='#')
            tot++;
        else
            a[tot]++;
    }
    while(tot && !a[tot])
        tot--;
    if(!tot)
    {
        puts("0");
        return 0;
    }
    memset(dp,0xcf,sizeof(dp));
    dp[0][0][0]=0;
    for(int i=1;i<=tot;i++)
        for(int j=0;j<=k;j++)
        {
            int t=min(a[i],j);
            for(int l=0;l<=t;l++)
            {
                if(l<=a[i])
                    dp[i][j][0]=max(dp[i][j][0],dp[i-1][j-l][0]+(a[i]-l)/2*g2+l*g1);
                if(l<=a[i]-1)
                {
                    dp[i][j][0]=max(dp[i][j][0],dp[i-1][j-l][1]+(a[i]-l-1)/2*g2+g3+l*g1);
                    dp[i][j][1]=max(dp[i][j][1],dp[i-1][j-l][0]+(a[i]-l-1)/2*g2+l*g1);
                }
                if(l<=a[i]-2)
                    dp[i][j][1]=max(dp[i][j][1],dp[i-1][j-l][1]+(a[i]-l-2)/2*g2+g3+l*g1);
            }
        }
    for(int i=0;i<=k;i++)
        ans=max(ans,dp[tot][i][0]);
    printf("%I64d",ans);
    return 0;
}
```



---

