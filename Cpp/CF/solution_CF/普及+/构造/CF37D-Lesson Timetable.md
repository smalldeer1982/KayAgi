# Lesson Timetable

## 题目描述

## 题目大意


P某人所在的大学有 $ m $ 间教室， $ n $ 个小组，对于第 $ i $ 间教室，初始时有  $ x_i $ 组在这个教室，且这个教室最多可以供 $ y_i $ 组同时上课。

每组学生第一次上课的教室的编号小于等于第二次上课的教室的编号。

P某人想为这些小组制定时间表，时间表有 $ 2n $ 个数，对于每个组，求第一节课和第二节课的教室标号。

你只需要求出共有多少种分组方法，不需求出具体方案。

由于答案可能很大，输出取模  $ 10^9+7 $

## 样例 #1

### 输入

```
3
1 1 1
1 2 3
```

### 输出

```
36
```

## 样例 #2

### 输入

```
3
1 1 1
1 1 1
```

### 输出

```
6
```

# 题解

## 作者：2018ty43 (赞：1)

 **题目大意：** 有 $m$ 间教室，$n$ 个有标号的人，分别安排每个人第一节课与第二节课教室，要求每个人第一节课教室编号小于等于第二节课教室编号。教室 $i$ 在第一节课人数强制要求 $x_i$ 人，第二节课有人数上限 $y_i$ 人，问有多少种安排方案。

### 思路
首先先考虑第一节课，从前往后依次放入 $x_i$ 人，共有 $
\prod_{i=1}^m\binom{\sum_{j=i}^mx_j}{x_i}
$ 种方案。

再考虑第二节课，设 $sum_i$ 表示 $\sum_{j=1}^ix_j$，$f_{i,j}$ 表示前 $i$ 个教室有 $j$ 个人上课的方案数，则有转移方程
$$
f_{i,j}=\sum_{k=0}^{\min(y_i,j)}f_{i-1,j-k}\times\binom{sum_i-j+k}{k}$$
$k$ 意为该课室有 $k$ 个人使用。  
最后 $f_{m,{sum_m}}$ 即为第二节课的方案数。

第一第二节课的方案数相乘即为答案。

### AC代码
```cpp
#include<cstdio>
#define C(a,b) (jc[a]*inv[b]%mod*inv[a-b]%mod)
#define mod 1000000007ll
long long f[109][1009];
int m,x[1009],y[1009];
int sum[1009];
long long jc[1009],jjc[1009];
long long inv[1009];
inline long long fpow(long long a,int b)
{
	long long res(1);
	while(b)
	{
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
long long ans(1),ss;
int main()
{
	f[0][0]=1;
	jc[0]=jjc[0]=inv[0]=1;
	for(int i(1);i<=1000;++i)jc[i]=jc[i-1]*i%mod,jjc[i]=jjc[i-1]*jc[i]%mod;
	for(int i(1000),j(fpow(jjc[1000],mod-2));i>0;--i)
	{
		inv[i]=jjc[i-1]*j%mod;
		j=j*jc[i]%mod;
	}
	scanf("%d",&m);
	for(int i(1);i<=m;++i)scanf("%d",x+i),sum[i]=sum[i-1]+x[i];
	ss=sum[m];
	for(int i(1);i<=m;++i)ans=ans*C(ss,x[i])%mod,ss-=x[i];//求第一节课的方案数
	for(int i(1);i<=m;++i)scanf("%d",y+i);
	//求第二节课的方案数
	for(int i(1);i<=m;++i)
	{
		for(int j(0);j<=sum[i-1];++j)
		{
			for(int k(0);k<=y[i]&&j+k<=sum[i];++k)
			{
				f[i][j+k]=(f[i][j+k]+f[i-1][j]*C(sum[i]-j,k))%mod;
			}
		}
	}
	printf("%d\n",ans*f[m][sum[m]]%mod);
}
```


---

