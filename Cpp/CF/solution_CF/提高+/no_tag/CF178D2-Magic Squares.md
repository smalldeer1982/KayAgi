# Magic Squares

## 题目描述

一只来自ABBYY的河狸喜欢智力游戏。他最喜欢的智力游戏之一是 “奇幻正方形” 。他想写一个程序来自动完成这个智力游戏。河狸决定让ABBYY杯的参赛者来帮他写这个程序。

 “奇幻正方形” 是一个 $n \times n$ 的矩阵，这个矩阵里面是整数。矩阵每行,每列和主对角线的数之和都等于 $s$ 。下面是一些例子：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF178D1/df1aa6f903a3e44e4322a8498e9c3054e6afd786.png)

给出 $n^2$ 个数 $(a_1 \sim a_{n^2})$ ，要求把这些数放入一个大小为 $n \times n$ 的矩阵中，使它们形成一个 “奇幻正方形” 。注意，每个数必须在矩阵和原始数列中出现相同的次数。

保证输入数据有解。

## 说明/提示

对于 $20\%$ 的数据，保证 $1 \leq n \leq 3$ ；

对于 $50\%$ 的数据，保证 $1 \leq n \leq 4$ 且给出的 $n^2$ 个数中最多有 $9$ 个互不相同的数；

对于 $100\%$ 的数据，保证 $1 \leq n \leq 4$ 且 $-10^8 \leq a_i \leq 10^8$ ；

## 样例 #1

### 输入

```
3
1 2 3 4 5 6 7 8 9
```

### 输出

```
15
2 7 6
9 5 1
4 3 8
```

## 样例 #2

### 输入

```
3
1 0 -1 0 2 -1 -2 0 1
```

### 输出

```
0
1 0 -1
-2 0 2
1 0 -1
```

## 样例 #3

### 输入

```
2
5 5 5 5
```

### 输出

```
10
5 5
5 5
```

# 题解

## 作者：Milthm (赞：1)

## CF178D2 题解

### 前置知识

- 搜索

### 题目解法

本题很明显是搜索，但是直接爆搜肯定过不了，所以考虑剪枝。

比较好想的剪枝有这几个：

- 明显，$s=\frac{\sum{a_i}}{n}$，因为所有元素加起来刚好是 $n$ 个 $s$。

- 如果搜到一行、一列或一个对角线的末尾，发现这一行、列或对角线上面的元素之和不等于 $s$，那么肯定错了，就不要往下搜了。这个和可以用数组来维护。

但是如果你只写了这两个剪枝，只能通过本题的第一个难度。在这题（第二个难度）就会 TLE 在第 $18$ 个点，所以考虑其它更多的剪枝：

- 首先，我们加个火车头，但是评测结果没有发生太多改变，仍然 TLE 在第 $18$ 个点。

- 考虑填上这个地方后，如果这一行、列或对角线还有 $x$ 个元素没有填，序列的最大值是 $p$，最小值是 $q$，这个地方要填的数是 $b$。如果 $b+xp\le s$ 或 $b+xq\ge s$，说明如果填了这个肯定是错的，去枚举下一个数即可。

这样写仍然还会 TLE 在第 $18$ 个点，于是我就去原站上看测试点是什么，发现这个测试点专卡顺序搜索，于是我改成了倒着枚举元素，但是仍然 TLE 在第 $21$ 个点。

但是思路已经有了，我就再想了一下，怎么安排顺序能使得搜索最快，于是就有了最重要的一条剪枝：

- 因为一行里面肯定是有大的也有小的，所以我们把数组第一个放最小的，第二个放最大的，第三个放第二小的，第四个放第二大的……这样，搜索的时候排列就会有大有小，自然就会减少很多不必要的搜索。

加上这个剪枝后，连这题的第三个难度都可以通过了。

### AC 代码

```cpp
#include<iostream>
#include<algorithm>
//这里原本有个火车头，不过不加也能过，我就把它删了
using namespace std;
int n,b[105],a[15][15],vis[105],maxn=-1e9,minn=1e9,c[105]; 
long long sum,s,sum1[15],sum2[15],sum3,sum4; 
void dfs(int x,int y){
	//cout<<x<<" "<<y<<'\n';
	if(x>n){//如果搜索完了就输出
		cout<<s<<'\n';
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				cout<<a[i][j]<<" ";
			}
			cout<<'\n';
		}
		exit(0);
	}
	for(int i=n*n;i>=1;--i){
		if(!vis[i]){
			int cnt=b[i]+sum1[y];//有关列的剪枝
			if(x==n&&cnt!=s)continue; 
			if(cnt+(n-x)*maxn<s)continue;
			if(cnt+(n-x)*minn>s)continue;
			cnt=b[i]+sum2[x];
			if(y==n&&cnt!=s)continue;//有关行的剪枝
			if(cnt+(n-y)*maxn<s)continue;
			if(cnt+(n-y)*minn>s)continue;
			if(x==y){//有关对角线的剪枝
				cnt=b[i]+sum3;	
				if(x==n&&cnt!=s)continue;
				if(cnt+(n-x)*maxn<s)continue;
				if(cnt+(n-x)*minn>s)continue;
			}
			if(x+y==n+1){//同上
				cnt=b[i]+sum4;
				//for(int j=1;j<x;++j){
				//	cnt+=a[j][n+1-j];
				//}
				if(x==n&&cnt!=s)continue;
				if(cnt+(n-x)*maxn<s)continue;
				if(cnt+(n-x)*minn>s)continue;
			}
			a[x][y]=b[i];//记录答案
			vis[i]=1;//标记
			sum1[y]+=b[i];
			sum2[x]+=b[i];
			if(x==y)sum3+=b[i];
			if(x+y==n+1)sum4+=b[i];
			if(y==n)dfs(x+1,1);
			else dfs(x,y+1);
			sum1[y]-=b[i];//回溯
			sum2[x]-=b[i];
			if(x==y)sum3-=b[i];
			if(x+y==n+1)sum4-=b[i];
			vis[i]=0;
			a[x][y]=0;
		}
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n*n;++i)cin>>b[i],sum+=b[i],maxn=max(maxn,b[i]),minn=min(minn,b[i]);
	sort(b+1,b+n*n+1);//先排序
	for(int i=1;i<=n*n;++i){
		if(i&1)c[i]=b[(i+1)/2];//最后一条剪枝
		else c[i]=b[n*n-(i-2)/2];
	}
	for(int i=1;i<=n*n;++i)b[i]=c[i];
	s=sum/n;
	dfs(1,1);
	return 0;
}

```



---

