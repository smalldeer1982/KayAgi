# Little Elephant and Elections

## 题目描述

There have recently been elections in the zoo. Overall there were $ 7 $ main political parties: one of them is the Little Elephant Political Party, $ 6 $ other parties have less catchy names.

Political parties find their number in the ballot highly important. Overall there are $ m $ possible numbers: $ 1,2,...,m $ . Each of these $ 7 $ parties is going to be assigned in some way to exactly one number, at that, two distinct parties cannot receive the same number.

The Little Elephant Political Party members believe in the lucky digits $ 4 $ and $ 7 $ . They want to evaluate their chances in the elections. For that, they need to find out, how many correct assignments are there, such that the number of lucky digits in the Little Elephant Political Party ballot number is strictly larger than the total number of lucky digits in the ballot numbers of 6 other parties.

Help the Little Elephant Political Party, calculate this number. As the answer can be rather large, print the remainder from dividing it by $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
7
```

### 输出

```
0
```

## 样例 #2

### 输入

```
8
```

### 输出

```
1440
```

# 题解

## 作者：畿王 (赞：5)

### 题意

7个人在[1,m]区间内取数，求第一个人选的数的4和7的个数大于其他人的4和7个数总和的方案数。

$m \in [1,1e9] $

### 思路1

我们首先考虑处理出对应4和7个数的总数，因为位数很小人也只有7个，所以处理完之后直接dfs求解即可。现在就是想着如何求出这个cnt数组，考虑数位dp，$dp[i][j]$表示有i位，有j个数是4或7的种数。当然这还是不够的，因为要把区间缩小到m以内，所以可以先将m的位数分离出来，从高位开始循环，假设从len开始，循环到i位时，前面len到i+1位已经取好（就是原数），设第i位为$a[i]$，则在区间$[0,a[i])$内枚举数，再借助原来预处理的dp数组，计算剩下的i-1位即可，同时注意细节。

### 代码1

```c++
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL mod=1e9+7;
int m;
LL dp[11][11],cnt[10],ans=0;
void Add(LL &x,LL y){
	x+=y;
	if(x>=mod)x-=mod;
}
void Init() {
	int a[11],len=0,t=m,c=0;
	while(t)a[++len]=t%10,t/=10;
	dp[1][0]=8,dp[1][1]=2;
	for(int i=2;i<=len;i++)
		for(int j=0;j<=i;j++){//预处理dp数组
			if(j)Add(dp[i][j],dp[i-1][j-1]*2);
			Add(dp[i][j],dp[i-1][j]*8);
		}
	for(int i=len;i>=1;i--){//从高位一位位枚举下来
		for(int j=0;j<a[i];j++){
			int f=(j==4||j==7);
			for(int q=0;q+c+f<10;q++)Add(cnt[q+c+f],dp[i-1][q]);
			if(i==1)cnt[f+c]++;//注意枚举到最后一位时的细节
		}
		c+=(a[i]==4||a[i]==7);
	}
	cnt[c]++,cnt[0]--;//加上m，减去0
}
LL dfs(int sum,int d) {//dfs暴搜求解
	if(d==7)return 1;
	LL res=0;
	for(int i=0; i<sum; i++)
		if(cnt[i]) {//注意不能取重
			cnt[i]--;
			res=(res+(cnt[i]+1)*dfs(sum-i,d+1)%mod)%mod;
			cnt[i]++;
		}
	return res;
}
int main() {
	scanf("%d",&m);
	Init();
	for(int i=1; i<=9; i++)
		if(cnt[i])ans=(ans+dfs(i,1)*cnt[i]%mod)%mod;
	printf("%lld\n",ans);
	return 0;
}
```

### 思路2

一个大佬想出的奇葩预处理方法——分块。直接处理出$[0,99999]$内各种cnt的个数，现在只需枚举高位i，就可以很快算出$i*100000+[0,99999]$内各种cnt的个数了，预处理代码如下。

### 代码2

```c++
int calc(int x) {
	int c=0;
	while(x) {
		int k=x%10;
		c+=(k==4||k==7);
		x/=10;
	}
	return c;
}
void Init() {
	int i;
	for(i=0; i<=min(99999,m); i++)cnt1[calc(i)]++;
	for(i=0; i<10; i++)cnt[i]=cnt1[i]-(i==0);
	for(i=1; i*100000LL+99999<=m; i++) {
		int r=calc(i);
		for(int j=0; j+r<10; j++)
			cnt[j+r]+=cnt1[j];
	}
	for(i=i*100000; i<=m; i++)cnt[calc(i)]++;
}
```



---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF258B)

### 题目大意
有 $7$ 个人在 $[1,m]$ 中选 $7$ 个数字，求第一个人选的数字中 $4$ 和 $7$ 的个数严格大于其他所有人的 $4$ 和 $7$ 的个数之和的方案数。

### 解题思路
本题的关键在于求出 $[1,m]$ 中有 $x$ 个 $4$ 和 $7$ 的数分别有多少个。我们先考虑没有限制的情况，假设 $f_{i,j}$ 表示 $j$ 位数中有 $i$ 个 $4$ 和 $7$ 的数的个数，那么显然有：
$$
f_{i,j}=2 \times f_{i-1,j-1}+8 \times f_{i,j-1}
$$
再看有限制的情况，我们依次枚举有 $i$ 个 $4$ 和 $7$ 的数有多少个，再枚举从 $j$ 位开始与 $m$ 不同，记录下之前已经有了多少个 $4$ 和 $7$，再枚举 $j$ 位上取的数是 $k$，如果 $k$ 是 $4$ 或 $7$，那么 $cnt_i$ 加上 $f_{i-x-1,j}$，否则 $cnt_i$ 加上 $f_{i-x,j}$，$x$ 为之前碰到 $4$ 和 $7$ 的个数。

处理出来这个，由于只有 $7$ 个人，直接深搜就可以了。

---

