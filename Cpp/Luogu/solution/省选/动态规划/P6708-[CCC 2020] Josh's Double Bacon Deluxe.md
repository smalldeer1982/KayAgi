# [CCC 2020] Josh's Double Bacon Deluxe

## 题目背景

Josh 和 $N-1$ 个人去吃汉堡。

## 题目描述

这个汉堡店共有 $M$ 种汉堡。

第 $i$ 个人最喜欢吃的汉堡为第 $b_i$ 种汉堡。

这 $N$ 个人都会选他最喜欢吃的汉堡。

现在，这 $N$ 个人排队去取汉堡，不幸的是，第一个人忘记了他最喜欢的汉堡，于是他随便拿了一个汉堡。

接下来的 $N-2$ 个人会按如下规则拿汉堡：
- 如果有他最喜欢的汉堡，就直接拿走。
- 否则，他会随便拿一个。

您需要求出，**排在最后**的 Josh 拿到他最喜欢汉堡的概率。

## 说明/提示

#### 样例 1 解释
| 第一个人的选择 | 第二个人的选择 | Josh 的选择 | 概率 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $2$ | $3$ | $\frac{1}{3}$ |
| $2$ | $1$ | $3$ | $\frac{1}{3}\times \frac{1}{2}=\frac{1}{6}$ |
| $2$ | $3$ | $1$ | $\frac{1}{6}$ |
| $3$ | $2$ | $1$ | $\frac{1}{3}$ |

Josh 拿到他最喜欢汉堡的概率为 $\frac{1}{3}+\frac{1}{6}=\frac{1}{2}$。

#### SPJ 计分标准
设正确答案为 $C$，你的答案为 $P$，若 $\lvert P-C\rvert <10^{-6}$，则您得该测试点的满分，否则，您得零分。

#### 子任务
**本题采用捆绑测试，且本题的 Subtask 分数有微调。**
- Subtask 1（$27$ 分）：保证 $N\le 10^5$，$M\le 10^3$。
- Subtask 2（$33$ 分）：保证 $M\le 10^3$。
- Subtask 3（$40$ 分）：无特殊限制。

对于 $100\%$ 的数据，保证 $3\le N\le 10^6$，$1\le b_i\le M\le 5\times 10^5$。

#### 说明
本题译自 [Canadian Computing Competition](https://cemc.uwaterloo.ca/resources/past-contests?contest_category=29) [2020 Senior](https://cemc.uwaterloo.ca/sites/default/files/documents/2020/seniorEF.pdf) T5 Josh's Double Bacon Deluxe。

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
0.5```

## 样例 #2

### 输入

```
7
1 2 3 1 1 2 3```

### 输出

```
0.57142857```

# 题解

## 作者：Y25t (赞：1)

我们考虑第一个乱选的人，如果他选到的是他本来喜欢的汉堡（$b_1$），那么后面的人一定都能选到自己喜欢的汉堡。

若不然，假设他选到的汉堡是 $x$，那么下一次选不到自己喜欢的汉堡的人一定是喜欢 $x$ 的人中排在最后的那个（记作 $r_x$）。此时，剩下的汉堡为 $b_1,b_{r_x+1},\ldots,b_n$。并且第 $r_x$ 个人开始乱选。这就相当于原问题一个子问题。

记 $f_x$ 为从第 $r_x$ 个人开始乱选，剩余的汉堡为 $b_1,b_{r_x+1},\ldots,b_n$ 时 Josh 拿到他喜欢的汉堡的概率，特别地，$f_{b_1}=1$。记 $f_0$ 为答案，$r_0=1$。记 $s_{i,x}$ 为 $b_i,\ldots,b_n$ 中 $x$ 的个数，那么：

$$f_x=\sum_{y\neq x}\frac{s_{r_x+1,y}+[y=b_1]}{n-r_x+1}*f_y$$

我们就可以得到一个 $O(M^2+N)$ 的做法。

稍加观察我们发现，若把 $b_{r_x}$ 当作 $b_1$，那么 $f_x$ 就等于 $i$ 从 $r_x$ 到 $n$ 的 $f_{b_i}$ 的加权平均。

从后往前遍历所有 $r_x$，记录下 $f_{b_i}$ 的后缀和，就可以 $O(N)$ 得到答案了。

代码（因为对 $r_i$ 进行了排序，所以此代码复杂度为 $O(N+M\log M)$）：

```cpp
#include<cstdio>
#include<algorithm>
#define N 1000005
#define M 500005
#define lf double

int n,a[N];

int m,r[M],pos[M];

lf f[M],sum;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		r[a[i]]=i;
		m=std::max(m,a[i]);
	}
	if(a[1]==a[n]){
		puts("1");
		return 0;
	}
	std::sort(r+1,r+m+1);
	for(int i=1;i<=m;i++)
		pos[a[r[i]]]=i;
	r[0]=1;
	sum=1;
	for(int i=m-1,j=n;i>=0;i--){
		if(r[i]==0)
			continue;
		while(j>r[i]){
			sum+=(a[j]==a[1]?1:f[pos[a[j]]]);
			j--;
		}
		f[i]=sum/(n-r[i]+1);
	}
	printf("%.15lf\n",f[0]);
} 
```


---

