# Math Test

## 题目描述

Petya is a math teacher. $ n $ of his students has written a test consisting of $ m $ questions. For each student, it is known which questions he has answered correctly and which he has not.

If the student answers the $ j $ -th question correctly, he gets $ p_j $ points (otherwise, he gets $ 0 $ points). Moreover, the points for the questions are distributed in such a way that the array $ p $ is a permutation of numbers from $ 1 $ to $ m $ .

For the $ i $ -th student, Petya knows that he expects to get $ x_i $ points for the test. Petya wonders how unexpected the results could be. Petya believes that the surprise value of the results for students is equal to $ \sum\limits_{i=1}^{n} |x_i - r_i| $ , where $ r_i $ is the number of points that the $ i $ -th student has got for the test.

Your task is to help Petya find such a permutation $ p $ for which the surprise value of the results is maximum possible. If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
3
4 3
5 1 2 2
110
100
101
100
4 4
6 2 0 10
1001
0010
0110
0101
3 6
20 3 15
010110
000101
111111```

### 输出

```
3 1 2 
2 3 4 1 
3 1 4 5 2 6```

# 题解

## 作者：I_am_Accepted (赞：7)

### Analysis

初中数学告诉我们，遇到绝对值要分类。

考虑最终答案中每一个人的贡献是 $x_i-r_i$ 还是 $r_i-x_i$，发现这可以状压解决。

对于一种，记 $c_1,c_2,\dots,c_n(c_i\in\{-1,1\})$ 表示第 $i$ 名学生的贡献为 $c_i(x_i-r_i)$。

则惊喜值为（其中 $a_1,\dots,a_m$ 表示最终每题的分值，为未知量）：

$$\begin{aligned}
S&=\sum\limits_{i=1}^nc_i(x_i-r_i)
\\&=\sum\limits_{i=1}^nc_ix_i-\sum\limits_{i=1}^nc_ir_i
\\&=\sum\limits_{i=1}^nc_ix_i-\sum\limits_{i=1}^nc_i\sum\limits_{j=1}^ma_jp_{i.j}
\\&=\sum\limits_{i=1}^nc_ix_i-\sum\limits_{i=1}^nc_i\sum\limits_{j=1}^ma_jp_{i.j}
\\&=\sum\limits_{i=1}^nc_ix_i-\sum\limits_{j=1}^m\left(\sum\limits_{i=1}^nc_ip_{i.j}\right)a_j
\end{aligned}$$

记（表示第 $j$ 题在最终答案中的系数）：

$$d_j=\sum\limits_{i=1}^nc_ip_{i.j}$$

得：

$$S=\sum\limits_{i=1}^nc_ix_i-\sum\limits_{i=1}^md_ia_i$$

由于 $\{a\}$ 是一个 $1\to m$ 的排列，将 $d_i$ 更小的 $a_i$ 赋更大的值将使 $S$ 最大。（[排序不等式](https://baike.baidu.com/item/%E6%8E%92%E5%BA%8F%E4%B8%8D%E7%AD%89%E5%BC%8F/7775728)）

对于每一种 $\{c\}$（状压），求出答案后取 $\max$ 即可。

### Detail

细心的小可爱们肯定发现了问题：**会把错解算进去啊。**

具体地，有可能最终某些人的贡献 $c_i(x_i-r_i)<0$（类比于绝对值 $|x|$ 分类 $x>0$ 后解得 $x=-2$ 一样矛盾）。

但是**一定有正解把错解刷掉**。

具体地，对于下标集合 $W=\{i\ |\ c_i(x_i-r_i)<0\}$，我们在枚举 $\{c\}$ 时枚举到 $W$ 中的 $c_i$ 全部取反（相反数）时，答案一定比这种情况要优。

### Code

时间 $O(nm2^n)$。（跑 $10^8$ 能过，CF 机子快)

[Link](https://codeforces.com/contest/1622/submission/142377050)

---

## 作者：Tyyyyyy (赞：3)

# CF1622E
### 题意简述
有 $n$ 个人做 $m$ 道题，知道每个人做题的对错情况。每个人有一个预期得分 $x_i$ 和实际得分 $r_i$。$x_i$ 给定，而 $r_i$ 是该人做对题目的分数之和。定义 “惊喜度” 为 $\displaystyle\sum_{i=1}^n|x_i-r_i|$。请你构造出一个每道题的分数方案，使得：

- 分数是一个 $1\sim m$ 的排列。
- 在所有的方案中，该方案的 “惊喜度” 最大。

如果有多种可能的答案，你只要输出其中一组即可。

$1\leq n\leq 10,1\leq m\leq 10^4,0\leq x_i\leq \frac{m(m-1)}{2}$。

### 题目分析
注意到惊喜度是以绝对值定义的，我们考虑将绝对值拆开。因为 $n$ 很小，我们考虑状压枚举哪些人的贡献是 $x_i-r_i$，哪些人的贡献是 $r_i-x_i$。

接下来我们可以计算出每道题的分数在答案中的贡献了。具体地说，我们记录一个权值数组，表示该题得分在答案中的**系数**是多少，并与该题的编号绑定。

又因为我们知道所有的 $x_i$ 且枚举了 $x_i$ 的正负，因此我们可以计算出所有 $x_i$ 对答案的贡献。

接着，因为题目的分数是一个 $1\sim m$ 的排列，设我们的权值数组为 $a$，则我们要重排 $a$ 数组，使 $\displaystyle\sum_{i=1}^m i\times a_i$ 最大。

显然，最优重排方案是从小到大排序。证明简单，这里略过。

这样，我们就计算出了对于当前的正负情况，最大的惊喜度是多少。我们只要拿当前的答案和其比较，就可以知道哪个更优，并更新答案了。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,x[20],res[10010];
char s[20][10010];
struct node
{
	int v,id;
	bool operator < (node b) const
	{
		return v<b.v;
	}
}a[10010];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int ans=-1;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)scanf("%d",&x[i]);
		for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
		for(int msk=0;msk<(1<<n);msk++)
		{
			int sum=0;
			for(int i=1;i<=n;i++)sum+=(msk&(1<<i-1))?x[i]:-x[i];
			for(int i=1;i<=m;i++)
			{
				a[i].id=i,a[i].v=0;
				for(int j=1;j<=n;j++)
					if(s[j][i]=='1')a[i].v+=(msk&(1<<j-1))?-1:1;
			}
			sort(a+1,a+m+1);
			for(int i=1;i<=m;i++)sum+=i*a[i].v;
			if(ans<sum)
			{
				ans=sum;
				for(int i=1;i<=m;i++)res[a[i].id]=i;
			}
		} 
		for(int i=1;i<=m;i++)printf("%d ",res[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2200}$
---
### 解题思路：

直接用绝对值的话不是特别好处理，发现人数 $n$ 很小，考虑直接暴力枚举出所有的人的实际分数与理想分数的大小关系，以确定绝对值 $x_i$ 贡献的正负情况。

处理完之后直接分摊到每一道题目的贡献，每道题的分数是一个排列，直接排序贪心就行了。

实际处理的时候，其实并不需要检验到底是不是符合之前枚举出来的大小关系，因为正确的答案一定在其中，不正确的不排除也不会有问题。

总复杂度：$O(2^nnm)$。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct str{
	int id,mark,cnt;
	bool operator <(str a){
		return cnt<a.cnt;
	}
}ans[10005],cur[10005];
bool cmp(str a,str b){
	return a.id<b.id;
}
int T,n,m,x[15],cor[15][10005],v[15],res,mark[15],flag,res_e;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)scanf("%d",&x[i]);
		for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		scanf("%1d",&cor[i][j]);
		res_e=-1;
		for(int i=0;i<=(1<<n);i++){
			for(int j=0;j<n;j++){
				if(((i>>j)&1)==1)v[j+1]=1;
				else v[j+1]=-1;
			}
			for(int j=1;j<=m;j++){
				cur[j].id=j;
				cur[j].mark=0;
				cur[j].cnt=0;
			}
			for(int j=1;j<=n;j++)
			for(int k=1;k<=m;k++)
			if(cor[j][k]==1)cur[k].cnt+=v[j];
			sort(cur+1,cur+m+1);
			for(int j=1;j<=m;j++)cur[j].mark=j;
			sort(cur+1,cur+m+1,cmp);
			for(int j=1;j<=n;j++)mark[j]=0;
			for(int j=1;j<=n;j++)
			for(int k=1;k<=m;k++)
			if(cor[j][k]==1)mark[j]+=cur[k].mark;
			res=0;
			for(int j=1;j<=n;j++)res+=abs(x[j]-mark[j]);
			if(res>res_e){
				res_e=res;
				for(int j=1;j<=m;j++)
				ans[j]=cur[j];
			}
		}
//		printf("*%d\n",res_e);
		sort(ans+1,ans+m+1,cmp);
		for(int i=1;i<=m;i++)
		printf("%d ",ans[i].mark);
		printf("\n");
	}
	return 0;
}
/*
1
4 4
6 2 0 10
1001
0010
0110
0101
---
ans:2 3 4 1


1
4 5
9 8 11 4
01011
10111
10000
10110
---
ans:4 1 5 3 2

*/
```


---

