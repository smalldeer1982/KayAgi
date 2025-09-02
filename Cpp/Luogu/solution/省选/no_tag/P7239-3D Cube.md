# 3D Cube

## 题目背景

**此题数据纯手造，并有手玩验证。**

idea & data：[zrmpaul](/user/226760)  
tester：[Hilarious_Reality](/user/80049)

--------

小 Z 喜欢三维模型，并从不同角度进行细致的观察。

## 题目描述

小 Z 拿到了一个二维矩阵。底面可以看作一个 $n \times m$ 的方格纸。

在每一个格子上，可以放任意个方块。由于有地心引力，方块不会悬空，且不会用胶水粘住。

他给出了这个三维矩阵的三视图，请你构造一个方块组，满足以下条件：

对于每一行、每一列，最多只有一个“**峰**”出现。特别地，底层矩阵的周围的高度被视为 $0$。如 `12321` 是一个“峰”，而 `13231` 有两个“峰”。

再举一些例子：

|方块排列|“峰”的数量|
|:----:|:----:|
|$\texttt{123}$|$1$|
|$\texttt{212}$|$2$|
|$\texttt{122221}$|$1$|
|$\texttt{00011000}$|$1$|
|$\texttt{10010101}$|$4$|

求出需要**最少**方块的矩阵。如果无解，请输出 `-1`。

## 说明/提示

### 数据范围

**本题各部分测试点采用捆绑测试。**

对于 $20\%$ 的数据：给出输入文件，程序打表输出答案，见附件 `easy.zip`。

对于 $100\%$ 的数据：$n\times m\leq25$。在俯视图中每个格子上最多有 $7\times10^8$ 个方块，且在俯视图中 `1` 的个数 $\leq20$。

## 样例 #1

### 输入

```
3 3
2 2 2
2 2 2
0 1 0
1 1 1
0 1 0```

### 输出

```
0 2 0 
2 2 2 
0 2 0 ```

# 题解

## 作者：世末OIer (赞：5)

~~这是出题人的小号，拉出来溜溜~~


首先是20pts的部分分。由于数据开放下载，所以手玩即可。 

---

接下来是正解。

看到格子数很小，所以我们就可以枚举哪一些必须不能被削平（即为峰）。这一步可以用dfs解决。

然后进行dp。（类似于floyd）

```cpp

	for(int k=1;k<=n*m;++k) for(int i=1;i<=n;++i) for(int j=1;j<=m;++j){  //由于一个格子带来的收益可能会改变整个棋盘，所以需要跑n*m次 
		if(cnnt[i][j]) continue;
		else if(c[i][j]) c[i][j]=max(1,min(c[i][j],min(min(c[i-1][j],c[i][j-1]),min(c[i+1][j],c[i][j+1]))));//取min是为了最小和保证不出现额外的峰，与1取max是为了保证有 
		else c[i][j]=0;
	}
``` 
最后判断是不是满足条件即可。 

details:

1.你需要满足正视图和左视图。每行每列至少有一个点不能被削掉。贪心的想每行每列只有一个点。 

2.判断是否满足有点复杂难写。 

总结：

最难想的是这个dp。想到了，你还得需要码力。 

[Code](https://www.luogu.com.cn/paste/7rwquigg)

---

## 作者：破壁人罗辑 (赞：0)

### 题意简述

求出一个各行各列元素之和最少的矩阵，使得每一行的最大值和每一列的最大值满足给定的要求、矩阵中有且只有给定的位置元素非零且每一行和每一列的序列前后各加上一个 $0$ 后最多只有一个峰。

### 解题思路

$n\times m\leq25$，数据范围很小，并且可以发现 $n^m+m^n<10^5$，能够直接 $O(n^m+m^n)$ 暴力枚举每一行的最大值位置和每一列的最大值位置，然后再用 $O(mn)$ 求出答案并判断是否合法，再和当前最优解比较和的大小，如果更小就替换当前最优解。时间复杂度 $O(mn(n^m+m^n))$，估算起来小于 $10^6$，能过。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int mt[25][25],ans[25][25],dp[25][25],x[25],y[25],n,m,top[26];
long long tot;
int check(int i,int j){//求解元素(i,j)的值
	if(dp[i][j]||!mt[i][j])return dp[i][j];
	dp[i][j]=1;//防止无限递归
	return dp[i][j]=max(mt[i][j],
		max(i<top[n+j]?i?check(i-1,j):0:i==n-1?0:check(i+1,j),
			j<top[i]?j?check(i,j-1):0:j==m-1?0:check(i,j+1)));
}
void dfs(){
	while(1){
		for(int h=n+m-1;top[h]>=(h<n?m:n);top[--h]++){
			if(!h)return;//如果枚举完成就return
			top[h]=0;
		}
		for(int i=0;i<n;i++)for(int j=0;j<m;j++)dp[i][j]=0;
		long long tots=0;
		for(int i=0;i<n;i++){
			if(x[i]&&!mt[i][top[i]])goto nxt;
      //不满足条件，跳到下一个状态
			dp[i][top[i]]=x[i];
		}
		for(int j=0;j<m;j++){
			if(y[j]&&!mt[top[n+j]][j])goto nxt;
      //不满足条件，跳到下一个状态
			dp[top[n+j]][j]=max(dp[top[n+j]][j],y[j]);
		}
		for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(mt[i][j])
			if((tots+=check(i,j))>=tot||dp[i][j]>x[i]||dp[i][j]>y[j])goto nxt;
            //不是最优解或不满足条件，跳到下一个状态
		for(int i=1;i<n-1&&tots<1e17;i++)for(int j=0;j<m;j++)
			if(dp[i-1][j]>dp[i][j]&&dp[i+1][j]>dp[i][j])goto nxt;
            //不满足条件，跳到下一个状态
		for(int i=0;i<n&&tots<1e17;i++)for(int j=1;j<m-1;j++)
			if(dp[i][j-1]>dp[i][j]&&dp[i][j+1]>dp[i][j])goto nxt;
            //不满足条件，跳到下一个状态
		for(int i=0;i<n;i++)for(int j=0;j<m;j++)ans[i][j]=dp[i][j];
		tot=tots;
		nxt:
		top[n+m-1]++;//枚举下一个状态
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)scanf("%d",x+i);
	for(int i=0;i<m;i++)scanf("%d",y+i);
	for(int i=0;i<n;i++)for(int j=0;j<m;j++)scanf("%d",&mt[i][j]);

//初步判断是否条件
	for(int i=0;i<n;i++){
		bool has=mt[i][0];
		for(int j=1;j<m;j++){
			if(has&&j+1<m&&mt[i][j+1]&&!mt[i][j]){puts("-1");return 0;}
			has=has||mt[i][j];
		}
		if(has!=(x[i]!=0)){puts("-1");return 0;}
	}
	for(int j=0;j<m;j++){
		bool has=mt[j][0];
		for(int i=0;i<n;i++){
			if(has&&i+1<n&&mt[i+1][j]&&!mt[i][j]){puts("-1");return 0;}
			has=has||mt[i][j];
		}
		if(has!=(y[j]!=0)){puts("-1");return 0;}
	}

	tot=1e18;dfs();
	for(int i=0;i<n;i++)for(int j=0;j<m;j++)
      if(mt[i][j]!=(ans[i][j]!=0)){puts("-1");return 0;}//判断ans是否满足条件
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++)printf("%d ",ans[i][j]);
		putchar('\n');
	}
	return 0;
}
```

---

