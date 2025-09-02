# Playing with Permutations

## 题目描述

现在你有一个长为 $n$ 的序列 $q$ 以及另外一个长度为 $n$ 的序列 $p$ 。其中 $p$ 序列初始化为 $1,2,3,....n$ 

定义两种操作：

$1.p[q[i]]=p[i]$

$2.p[i]=p[q[i]]$

给出步骤数 $k$ 和目标序列 $s$ ，问你能否在恰好 $k$ 个操作后实现从 $p$ 序列到 $s$ 序列的转换？

输出"YES"或者"NO"(不含引号)来表示你的结果。

要求：在 $k$ 步以前的过程中不能让 $p=s$ ，否则视作失败，哪怕是刚开始 $p=s$ 也不行。

## 样例 #1

### 输入

```
4 1
2 3 4 1
1 2 3 4
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
4 1
4 3 1 2
3 4 2 1
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
4 3
4 3 1 2
3 4 2 1
```

### 输出

```
YES
```

## 样例 #4

### 输入

```
4 2
4 3 1 2
2 1 4 3
```

### 输出

```
YES
```

## 样例 #5

### 输入

```
4 1
4 3 1 2
2 1 4 3
```

### 输出

```
NO
```

# 题解

## 作者：XL4453 (赞：0)

### $\text{Diffficulty : 1800}$

---
### 解题思路：

特别地，当 $s$为 $1,2,3,4...$ 的时候，一定无解。

---

首先不考虑恰好 $k$ 次，而只考虑能否达到。可以发现给出的两次操作其实是互为逆元的（换句话说，在进行了操作一后进行操作二就相当于啥都没做），所以最后的答案一定是重复操作一或者操作二若干次而不可能同时出现操作一和操作二。

在已经进行了 $m$ 次操作的前提下，可以通过在两个操作中反复横跳的方法解决任意为偶数的剩下次数。

---
还需要考虑中途恰好不得不相等的情况，也就是两个操作效果一样的时候，如果中途出现了恰好相等的情况即使最后能相等也是是不可行的。

最后的总复杂度为 $O(n^2)$，可以接受。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
int n,k,p[105],s[105],p2[105],now[105],flag,now2[105];
void sp(){
	for(int i=1;i<k;i++){
		for(int j=1;j<=n;j++)now2[j]=now[p[j]];
		for(int j=1;j<=n;j++)now[j]=now2[j];
		flag=1;
		for(int j=1;j<=k;j++)
		if(now[j]!=s[j])flag=0;
		if(flag){printf("NO\n");return;}
	}
	for(int j=1;j<=n;j++)now2[j]=now[p[j]];
	for(int j=1;j<=n;j++)now[j]=now2[j];
	flag=1;
	for(int j=1;j<=k;j++)
	if(now[j]!=s[j])flag=0;
	if(flag==0){printf("NO\n");return;}
	printf("YES\n");
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d",&p[i]);
	for(int i=1;i<=n;i++)scanf("%d",&s[i]);
	for(int i=1;i<=n;i++)p2[p[i]]=i;
	for(int i=1;i<=n;i++)now[i]=i;
	
	flag=1;
	for(int i=1;i<=n;i++)
	if(s[i]!=now[i])flag=0;
	if(flag){
		printf("NO\n");
		return 0;
	}
	
	flag=1;
	for(int i=1;i<=n;i++)
	if(p[i]!=p2[i])flag=0;
	if(flag){
		sp();//SSR is ok too.
		return 0;
	}
	
	for(int i=1;i<=n;i++)now[i]=i;
	for(int i=1;i<=k;i++){
		for(int j=1;j<=n;j++)now2[j]=now[p[j]];
		for(int j=1;j<=n;j++)now[j]=now2[j];
		flag=1;
		for(int j=1;j<=k;j++)
		if(now[j]!=s[j])flag=0;
		if(flag&&(k-i)%2==0){printf("YES\n");return 0;}		
	}
	
	for(int i=1;i<=n;i++)now[i]=i;
	for(int i=1;i<=k;i++){
		for(int j=1;j<=n;j++)now2[j]=now[p2[j]];
		for(int j=1;j<=n;j++)now[j]=now2[j];
		flag=1;
		for(int j=1;j<=k;j++)
		if(now[j]!=s[j])flag=0;
		if(flag&&(k-i)%2==0){printf("YES\n");return 0;}		
	}
	printf("NO\n");
	return 0;
}
```


---

