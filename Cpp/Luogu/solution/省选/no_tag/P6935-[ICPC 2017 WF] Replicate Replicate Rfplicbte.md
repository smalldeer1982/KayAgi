# [ICPC 2017 WF] Replicate Replicate Rfplicbte

## 题目描述

自动化蜂窝制造公司的所有者刚刚为一种生产相同零件的新工艺申请了专利。她的方法使用了一个二维的两态单元格网格，每个单元格要么是“空的”，要么是“填充的”。具体细节当然是专有的。

最初，网格中的一组单元格被填充为要复制的零件的副本。在一系列离散步骤中，网格中的每个单元格通过检查自身状态及其八个周围邻居的状态来同时更新其状态。如果这九个单元格中有奇数个是填充的，则该单元格在下一个时间步的状态将是填充的，否则将是空的。图 G.1 显示了一个由三个填充单元格组成的简单图案的复制过程中的几个步骤。

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/14639/1.png)

图 G.1：复制过程。

然而，过程出现了一个错误。在每次更新步骤之后，网格中的一个单元格可能会自发地翻转其状态。例如，图 G.2 显示了如果一个单元格在第一次时间步后翻转其状态，另一个在第三次时间步后翻转其状态可能会发生的情况。

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/14639/2.png)

图 G.2：复制过程中的错误。此图对应于样例输入 $1$。

不幸的是，原始图案丢失了，只剩下（可能被破坏的）复制结果。你能编写一个程序来确定可能导致给定最终图案的最小可能非空初始图案吗？

## 说明/提示

时间限制：3 秒，内存限制：512 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
10 10
.#...#...#
##..##..##
##.#.##...
##.#.##...
.#...#####
...##..#.#
......###.
##.#.##...
#..#..#..#
##..##..##
```

### 输出

```
.#
##
```

## 样例 #2

### 输入

```
8 8
##..#.##
#.####.#
.#.#.#..
.##.#.##
.#.#.#..
.##.#.##
#..#.###
##.#.##.
```

### 输出

```
####
#..#
#.##
###.
```

## 样例 #3

### 输入

```
5 4
#....
..###
..###
..###
```

### 输出

```
#
```

# 题解

## 作者：xtx1092515503 (赞：5)

一道烦人、烦人、除此之外没了的题。

------------

首先一个观察是，经过一步，原本图样的边界必然会向四个方向各扩张一格。就算有 `bug` 存在，四个方向上每边都至少有两个格子，仍然会保证边界扩张。

进而，回溯一步，图样的边界必然会四个方向各收缩一格。

首先忽略 `bug` 的存在。此时，我们尝试从后继态推回初态。手动推推即可得到 $g_{i,j}=\bigotimes\limits_{u=0}^2\bigotimes\limits_{v=0}^2g_{i-u,j-v}$ 的 DP 式，其中 $g_{i,j}$ 初始即为后继态的值，不在范围内的态视作 $0$。这样之后，矩阵左上角 $(n-2)\times(m-2)$ 的矩阵即为初态。

假如没有 `bug`，则矩阵的最右两列和最下两行应该全为 $0$。但是因为 `bug`，最右两列和最下两行中可能会出现 `1`。

但是，我们可以根据这些 `1` 的分布反推出出 `bug` 的位置。具体而言，某个位置如果出 `bug`，其影响到的是以之为左上角的形如

```
1101101101..
1101101101..
0000000000..
1101101101..
1101101101..
0000000000..
1101101101..
..........
```

的部分。根据最右两列和最下两行中的 `1`，我们可以唯一确定该位置，或者判定其不合法。确定出锅的位置后，只需撤回其影响即可。这样，我们便实现了反推。

不断反推，直到判定无法反推，或者剩余部分的长或宽已经不大于 $2$，无法反推了。这样把四边压缩压缩就可以输出了。

复杂度 $\min(n,m)nm$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
char s[310][310];
bool f[310][310],g[310][310];
int main(){
	scanf("%d%d",&m,&n);
	for(int i=0;i<n;i++)scanf("%s",s[i]);
	for(int i=0;i<n;i++)for(int j=0;j<m;j++)f[i][j]=(s[i][j]=='#');
	while(n>=3&&m>=3){
		for(int i=0;i<n;i++)for(int j=0;j<m;j++){
			g[i][j]=0;
			for(int p=0;p<3;p++)for(int q=0;q<3;q++)if(i>=p&&j>=q)g[i][j]^=g[i-p][j-q];
			g[i][j]^=f[i][j];
		}
//		for(int i=0;i<n;i++,puts(""))for(int j=0;j<m;j++)printf("%d",f[i][j]);puts("");
//		for(int i=0;i<n;i++,puts(""))for(int j=0;j<m;j++)printf("%d",g[i][j]);puts("");
		bool fd=false;
		for(int i=0;i<3;i++)for(int j=0;j<3;j++){
			bool ok=true;
			int x,y;
//			printf("QWQ:%d,%d\n",i,j);
			for(int p=n+1-i,sta=true;ok;p-=3){
//				printf("%d,%d\n",p,sta);
				if(p<0&&sta)sta=false,x=p+3;
				if(sta)for(int u=0;u<3;u++)for(int v=0;v<2;v++)
					if(p+u>=0&&p+u<n&&g[p+u][m-2+v]!=(u!=2&&(j+v)%3!=2))sta=false,x=p+3;
				if(!sta)for(int u=0;u<3;u++)for(int v=0;v<2;v++)
					if(p+u>=0&&p+u<n&&g[p+u][m-2+v])ok=false;
				if(p<0)break;
			}
			if(!ok)continue;
			for(int q=m+1-j,sta=true;ok;q-=3){
//				printf("%d,%d\n",q,sta);
				if(q<0&&sta)sta=false,y=q+3;
				if(sta)for(int u=0;u<2;u++)for(int v=0;v<3;v++)
					if(q+v>=0&&q+v<m&&g[n-2+u][q+v]!=((i+u)%3!=2&&v!=2))sta=false,y=q+3;
				if(!sta)for(int u=0;u<2;u++)for(int v=0;v<3;v++)
					if(q+v>=0&&q+v<m&&g[n-2+u][q+v])ok=false;
				if(q<0)break;
			}
			if(!ok)continue;
//			printf("QQQ:%d,%d\n",x,y);
			for(int p=x;p<n;p++)for(int q=y;q<m;q++)if((p-x)%3!=2&&(q-y)%3!=2)g[p][q]^=1;
			fd=true;break;
		}
		if(!fd)break;
		n-=2,m-=2;
		for(int i=0;i<n;i++)for(int j=0;j<m;j++)f[i][j]=g[i][j];
	}
	int L=0,R=n-1,U=m-1,D=0;
	while(L<R){bool ok=true;for(int t=D;t<=U;t++)if(f[L][t]){ok=false;break;}if(!ok)break;L++;}
	while(L<R){bool ok=true;for(int t=D;t<=U;t++)if(f[R][t]){ok=false;break;}if(!ok)break;R--;}
	while(D<U){bool ok=true;for(int t=L;t<=R;t++)if(f[t][D]){ok=false;break;}if(!ok)break;D++;}
	while(D<U){bool ok=true;for(int t=L;t<=R;t++)if(f[t][U]){ok=false;break;}if(!ok)break;U--;}
	if(L==R&&U==D){puts("#");return 0;}
	for(int i=L;i<=R;i++,putchar('\n'))for(int j=D;j<=U;j++)putchar(f[i][j]?'#':'.');
	return 0;
}
```



---

