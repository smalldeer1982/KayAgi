# 题目信息

# [USACO05OPEN] Landscaping G

## 题目描述

农夫约翰正在做一次艰难的转型，从养山羊改成养奶牛，他的农场，由于是为养山羊而设计的所以有太多的山，为了养牛就必须将它整平。但是，将山整平是件很花钱的工作，所以他要移走尽可能少的土。

由于农场很细长，所以可以用一个 $n$ 和 $n$ 个整数（范围 $[1,10^6]$）组成的二维的数组来表示，如：

```
1 2 3 3 3 2 1 3 2 2 1 2
```

上述农场的侧面图是这样的：

```
    * * *     *
  * * * * *   * * *   *
* * * * * * * * * * * *
1 2 3 3 3 2 1 3 2 2 1 2
```

一个或是一些连续等高的地面，如果它左边或是右边的海拔都比它低的话，就被称为山顶，上面的例子就有三个山顶。 确定如果要使地图上仅有 $k$ 个山顶，至少要移走多少体积的土（每块地面减少一单位海拔需移走一单位的土）。注意，地面的海拔只能被降低不能被升高。 对于例子，如果要减少到只有 $1$ 个山顶，这需要移走 $2+1+1+1=5$ 个单位的土（`-` 表示移走的土）：

```
    * * *     -
  * * * * *   - - -   -
* * * * * * * * * * * *
1 2 3 3 3 2 1 3 2 2 1 2
```

## 说明/提示

对于 $100\%$ 的数据，$1 \leq n \leq 10^3$，$1 \leq k \leq 25$。

## 样例 #1

### 输入

```
12 1
1
2
3
3
3
2
1
3
2
2
1
2
```

### 输出

```
5```

# AI分析结果

### 算法分类
动态规划

### 综合分析与结论
题目要求通过移除最少的土来将山顶数量减少到指定数量，核心问题可以转化为如何在保持山顶数量限制的前提下，最小化移除的土量。两位作者分别提供了不同的解决方案：

1. **Hog_Dawa_IOI** 的题解通过将问题转化为树型动态规划，利用单调栈构建树的层次结构，并通过树型 DP 求解最小移除量。该解法思路清晰，时间复杂度为 $O(n \times k)$，适合大规模数据处理。
2. **Frozen_Ladybug** 的题解采用暴力搜索和贪心策略，每次移除代价最小的山顶，并在每次移除后重新计算山顶信息。该解法实现简单，但时间复杂度较高，适合小规模数据。

### 所选题解
#### Hog_Dawa_IOI 的题解
- **星级**: 5星
- **关键亮点**: 利用单调栈构建树结构，将问题转化为树型动态规划，思路清晰且优化程度高。
- **个人心得**: 作者提到在实现过程中遇到了一些细节问题，如树的构建顺序和转移顺序，最终通过从低到高遍历坐标解决了问题。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long siz[1005],f[1005][30],ans;
int n,k,s[1005],poi[1005],tot;
int fir[1005],num,pre[1005],nxt[1005],id[1005],sta[1005],top;
struct ss{int ed,nxt;}bia[1005];
void dfs(int wh)
{
	ans+=siz[wh];for(int i=0;i<=k;i++) f[wh][i]=siz[wh];
	for(int i=fir[wh];i;i=bia[i].nxt)
	{
		dfs(bia[i].ed);
		for(int j=k;j>=1;j--) for(int w=j-1;w>=0;w--)
		f[wh][j]=max(f[wh][j],f[bia[i].ed][j-w]+f[wh][w]);
	}
}bool c(int a,int b){return s[a]<s[b]||s[a]==s[b]&&a<b;}
int main()
{
    scanf("%d%d",&n,&k),sta[top=1]=0;
	for(int i=1;i<=n;id[i]=i,i++) scanf("%d",&s[i]);
	sort(id+1,id+n+1,c);for(int i=1;i<=n;i++)
	{
		while(top>=1&&s[sta[top]]>s[i]) top--;
		pre[i]=sta[top],sta[++top]=i;
	}sta[top=1]=n+1;for(int i=n;i>=1;i--)
	{
		while(top>=1&&s[sta[top]]>=s[i]) top--;
		nxt[i]=sta[top],sta[++top]=i;
	}for(int ii=1,i=id[ii];ii<=n;ii++,i=id[ii])
	{
		int wh=(s[pre[i]]>=s[nxt[i]])?pre[i]:nxt[i];
		if(s[pre[i]]==s[i]) {poi[i]=poi[pre[i]];continue;}
		siz[poi[i]=++tot]=1ll*(nxt[i]-pre[i]-1)*(s[i]-s[wh]),
		bia[++num].ed=tot,bia[num].nxt=fir[poi[wh]],fir[poi[wh]]=num;
	}dfs(1),printf("%lld",ans-f[1][k]);
}
```

### 最优关键思路或技巧
- **单调栈构建树结构**: 通过单调栈找到每个点的前驱和后继，构建树的层次结构。
- **树型动态规划**: 利用树型 DP 求解在保持山顶数量限制下的最小移除量。

### 可拓展之处
类似的问题可以转化为树型动态规划，如最小生成树、最大独立集等问题。

### 推荐题目
1. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)
2. [P2014 选课](https://www.luogu.com.cn/problem/P2014)
3. [P1273 有线电视网](https://www.luogu.com.cn/problem/P1273)

---
处理用时：23.00秒