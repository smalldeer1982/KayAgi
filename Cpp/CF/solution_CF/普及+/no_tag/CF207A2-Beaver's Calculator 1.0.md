# Beaver's Calculator 1.0

## 题目描述

The Smart Beaver from ABBYY has once again surprised us! He has developed a new calculating device, which he called the "Beaver's Calculator $ 1.0 $ ". It is very peculiar and it is planned to be used in a variety of scientific problems.

To test it, the Smart Beaver invited $ n $ scientists, numbered from $ 1 $ to $ n $ . The $ i $ -th scientist brought $ k_{i} $ calculating problems for the device developed by the Smart Beaver from ABBYY. The problems of the $ i $ -th scientist are numbered from $ 1 $ to $ k_{i} $ , and they must be calculated sequentially in the described order, since calculating each problem heavily depends on the results of calculating of the previous ones.

Each problem of each of the $ n $ scientists is described by one integer $ a_{i,j} $ , where $ i $ ( $ 1<=i<=n $ ) is the number of the scientist, $ j $ ( $ 1<=j<=k_{i} $ ) is the number of the problem, and $ a_{i,j} $ is the number of resource units the calculating device needs to solve this problem.

The calculating device that is developed by the Smart Beaver is pretty unusual. It solves problems sequentially, one after another. After some problem is solved and before the next one is considered, the calculating device allocates or frees resources.

The most expensive operation for the calculating device is freeing resources, which works much slower than allocating them. It is therefore desirable that each next problem for the calculating device requires no less resources than the previous one.

You are given the information about the problems the scientists offered for the testing. You need to arrange these problems in such an order that the number of adjacent "bad" pairs of problems in this list is minimum possible. We will call two consecutive problems in this list a "bad pair" if the problem that is performed first requires more resources than the one that goes after it. Do not forget that the problems of the same scientist must be solved in a fixed order.

## 说明/提示

In the first sample $ n=2 $ , $ k_{1}=2 $ , $ a_{1,1}=1 $ , $ a_{1,2}=2 $ , $ k_{2}=2 $ , $ a_{2,1}=3 $ , $ a_{2,2}=4 $ . We've got two scientists, each of them has two calculating problems. The problems of the first scientist require $ 1 $ and $ 2 $ resource units, the problems of the second one require $ 3 $ and $ 4 $ resource units. Let's list all possible variants of the calculating order (each problem is characterized only by the number of resource units it requires): $ (1,2,3,4) $ , $ (1,3,2,4) $ , $ (3,1,2,4) $ , $ (1,3,4,2) $ , $ (3,4,1,2) $ , $ (3,1,4,2) $ .

Sequence of problems $ (1,3,2,4) $ has one "bad" pair ( $ 3 $ and $ 2 $ ), $ (3,1,4,2) $ has two "bad" pairs ( $ 3 $ and $ 1 $ , $ 4 $ and $ 2 $ ), and $ (1,2,3,4) $ has no "bad" pairs.

## 样例 #1

### 输入

```
2
2 1 1 1 10
2 3 1 1 10
```

### 输出

```
0
1 1
2 1
3 2
4 2
```

## 样例 #2

### 输入

```
2
3 10 2 3 1000
3 100 1 999 1000
```

### 输出

```
2
10 1
23 1
49 1
100 2
99 2
98 2
```

# 题解

## 作者：_Weslie_ (赞：0)

这是可以通过 A2 和 A3 的正解做法。

我们把 $a$ 序列分成 $cnt$ 个不下降的子段。

例如：$a=\{1,1,4,5,1,4,1,9,1,9,8,1\}$，则分成 $\{1,1,4,5\},\{1,4\},\{1,9\},\{1,9\},\{8\},\{1\}$ 共 $6$ 个子段。

$b$ 序列同理。

很显然，如果有 $k$（这里 $k=2$）个不下降序列，它们一定可以通过归并变成不下降的子序列，如果要从小到大取，这个过程中只会取到每个序列的头部元素。

证明一下：如果取到了元素 $i$，那么 $i-1$ 号元素一定比它小，更靠前。所以从每个序列的头部取最好。

我们也可以忽视这个取头部元素的要求，直接使用一个优先队列去维护。

注意到优先队列默认是大根堆，所以我们可以把元素值取反扔进一个 `pair` 里，大大降低了细节量。

```
#include<bits/stdc++.h>
using namespace std;
int n;
int k[3];
long long x,y,a[3][200005],m;
int duan[3][200005],cnt[200005],now[200005];
int pan(long long a,long long b){
	if(a>=b)return 0;
	return 1;
}
//int cnt=0;
priority_queue<pair<long long,int> >q;
signed main(){
	cin>>n;
	cin>>k[1]>>a[1][1]>>x>>y>>m;
	for(int i=2;i<=k[1];i++){
		a[1][i]=(a[1][i-1]*x+y)%m;
		if(a[1][i]<a[1][i-1]){
			duan[1][++cnt[1]]=i-1;
		}
	}
	cin>>k[2]>>a[2][1]>>x>>y>>m;
	for(int i=2;i<=k[2];i++){
		a[2][i]=(a[2][i-1]*x+y)%m;
		if(a[2][i]<a[2][i-1]){
			duan[2][++cnt[2]]=i-1;
		}
	}
	duan[1][++cnt[1]]=k[1];
	duan[2][++cnt[2]]=k[2];
	cout<<max(cnt[1],cnt[2])-1<<endl;
	if(k[1]+k[2]>200000)return 0;
	for(int i=1;i<=n;i++)now[i]=1;
	for(int i=1;i<=max(cnt[1],cnt[2]);i++){
		for(int j=1;j<=n;j++){
			if(cnt[j]<i)continue;
			for(;now[j]<=duan[j][i];now[j]++){
				pair<long long,int>ans;
				ans.first=-a[j][now[j]];
				ans.second=j;
				q.push(ans);
			}
		}
		while(!q.empty()){
			cout<<-q.top().first<<' '<<q.top().second<<endl;
			q.pop();
		}
	}
	return 0;
}

```

A1 题更改数据范围即可，A3 题此代码会 MLE。

---

## 作者：Confringo (赞：0)

[可能更差的阅读体验](https://www.luogu.com.cn/blog/Confringo/solution-cf207a)

### 题意

现在给定 $n$ 个序列，每组序列由 $k,t,x,y,m$ 生成。具体地说，$a_1=t$，$a_{i+1}=(xa_i+y)\bmod m\left(1\leqslant i\lt k\right)$。你每次可以取走任意序列的第一个数并加入最终序列，直到所有序列里的所有数都被取完。设该最终序列为 $r$，求 $\sum^n_{i=2}\left[r_i\lt r_{i-1}\right]$ 的最小值。

例如，若两序列 $a,b$ 满足 $a=\{1,3\},b=\{2,4\}$，则可以取到的最小值为 $0$。

### 限制与约定

- 对于 A1 题，保证 $n=2,1\leqslant k_i\leqslant 2000$；  
- 对于 A2 题，保证 $n=2,1\leqslant k_i\leqslant 2\times10^5$；
- 对于 A3 题，保证 $1\leqslant n,k\leqslant 5000$。
- 对于全部三题，保证 $0\leqslant t_i\lt m_i\leqslant 10^9,1\leqslant x_i,y_i\leqslant 10^9$。

### 思路

观察数据范围，发现可以使用 $O(nk)$ 的算法解决。

取走一个序列的某个前缀所需要的递增子段最小值永远是单调不降的，这是显然的。

先考虑次数的下界。显然该值不会小于取走单独一个序列需要连续子段的最小值的最大值。例如 $a=\{114,514,191,9810\}$。此时想要取空 $a$，就必须使用至少 $2$ 个递增子段，分别包含 $\{114,514\}$ 和 $\{191,9810\}$。

再考虑次数的上界。我们是否可以先取走需要 $1$ 个递增子段的元素，再取走 $2$ 个的，再取走 $3$ 个的，以此类推？一定是可以的。

考虑某个序列中需要 $1$ 个递增子段才能取走的元素，在单独的序列中它们一定是单调不降的。那么每次选走每个序列中第一个需要 $1$ 个递增子段才能取走的元素的最小值，以此类推，最终一定会取完所有元素。读者可以以归并排序感性理解。

那么，次数的上界也是取走单独一个序列需要连续子段的最小值的最大值。既然上界等于下界，答案就等于它。

暴力计算该值需要 $O(\sum k)$，也就是 $O(nk)$ 的时间复杂度，可以接受。

### 实现

鉴于该算法的实现比较简单，方法较多，这里介绍一种我的写法，可能比较冗长。读者可以选择不使用这种写法，也可以完成本题。

- 读入所有数据，计算 $\sum k$。
- 如果 $\sum k\leqslant 2\times10^5$，则生成序列后**按照下述顺序**把每个数的三个属性进行保存，分别是：取走这个数和它前面的数需要的连续子段的最小值（该值可以通过保存变量 cnt，每次遇到后面数小于前面数的情况时 $+1$ 维护）、大小和属于的序列编号进行保存。最后进行 sort 即可。使用 `tuple<int,int,int>` 可以不手写 cmp 函数排序，非常推荐。
- 如果 $\sum k\gt 2\times10^5$，那就不用存了，直接按照上面的方法计算答案就行。

如果还有问题，可以通过 [这个链接](https://codeforces.com/contest/207/submission/238201837) 看我的提交记录。

---

