# Tanks

## 题目描述

Petya sometimes has to water his field. To water the field, Petya needs a tank with exactly $ V $ ml of water.

Petya has got $ N $ tanks, $ i $ -th of them initially containing $ a_{i} $ ml of water. The tanks are really large, any of them can contain any amount of water (no matter how large this amount is).

Also Petya has got a scoop that can contain up to $ K $ ml of water (initially the scoop is empty). This scoop can be used to get some water from some tank, and after that pour it all into some other tank (it is impossible to get water from multiple tanks without pouring it, or leave some water in the scoop when pouring it). When Petya tries to get some water from a tank, he gets $ min(v,K) $ water, where $ v $ is the current volume of water in the tank.

Is it possible to obtain a tank with exactly $ V $ ml of water using these operations? If it is possible, print a sequence of operations that allows to do it. If there are multiple ways to obtain needed amount of water in some tank, print any of them.

## 样例 #1

### 输入

```
2 3 5
2 3
```

### 输出

```
YES
1 2 1
```

## 样例 #2

### 输入

```
2 3 4
2 3
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
5 2 0
1 3 5 7 9
```

### 输出

```
YES
2 2 1
3 3 1
4 4 1
5 5 1
```

# 题解

## 作者：Error_Eric (赞：2)

### 前言

降智构造题。

![跋山涉水AC路.jpg](https://cdn.luogu.com.cn/upload/image_hosting/6ocanxpm.png)

### 正文

记原来的水槽集合为 $S_0$ 。

考虑找到一个水槽集合 $S'$ ,使得 $\sum S'_i \equiv V(\mod k)$ 。

我们将这些水槽的水倒入这个集合的第一个水槽中，记这个水槽为 $S'_1$。显然 $S'_1\equiv V(\mod k)$

我们将 $S_0 \setminus S$ 中所有水槽中的水倒入这个集合的第一个水槽中,记这个水槽为 $S''_1$。

- 如果 $S'_1\ge V$ :可以从这个水槽中向外倒水 $\dfrac{S'_1-V}{k}$ 次。

- 如果 $S'_1<V$:可以从 $S''_1$ 中向这个水槽倒水 $\dfrac{V-S'_1}{k}$ 次。

但是如果 $S'_1+S''_1<V$，(换言之，对于最初状态的 $S_0$, $\sum S_{0_i}<V$) 显然不存在解。

那么，找不到合法的 $S'$ 怎么办？

这种情况可以证明为无解。因为既然不存在这样一个 $S'$ ，显然也不存在其他的集合，使得其总水量 $sum$ 满足 $sum\equiv V(\mod k)$ ，那么显然不存在答案了。

此时可以用背包问题的解法找到合法的 $S'$。（我们只需要考虑总价值对于 $k$ 取模的结果。因为 $k$ 比较小，所以数组可以开的下。）

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;
#define il inline 
#define rei register int
il void readln(int &I){
    I=0;char C=getchar();
    while(!isdigit(C))C=getchar();
    while( isdigit(C))I=I*10+C-'0',C=getchar();
}
const int size=5005;
int n,k,v,a[size],u[size],su,f1,f2;
bool f[size]={1,0},g[size],all0=1;
int l[size][size];
#define mer(x,y) ((a[x])?(printf("%d %d %d\n",a[x]/k+bool(a[x]%k),x,y),a[y]+=a[x],a[x]=0):0)
int main(){
	readln(n),readln(k),readln(v);
	for(rei i=1;i<=n;i++)readln(a[i]),u[i]=a[i]%k,a[0]+=a[i];
	if(a[0]<v)return puts("NO"),0;
	for(rei i=1;i<=n;i++){
		for(rei j=0;j<=k;j++)
			if(f[j])g[j]=g[(j+u[i])%k]=1,l[i][j]=l[i][(j+u[i])%k]=j;
		for(rei j=0;j<=k;j++)f[j]=g[j];
	}
	if(v%k==0){
		puts("YES");
		for(rei i=2;i<=n;i++)mer(i,1);if(v/k)printf("%d 1 2",v/k);
	}
	else if(f[su=v%k]){
		puts("YES");
		for(rei i=n;i>0;i--)u[i]=(su!=l[i][su]),su=l[i][su];
		for(rei i=1;i<=n;i++)if(a[i])u[i]?(f1?mer(i,f1):(f1=i)):(f2?mer(i,f2):(f2=i));
		if(f1==0)return 0;
		if(a[f1]>v)printf("%d %d %d",(a[f1]-v)/k,f1,f1%n+1);
		else if(a[f1]<v)printf("%d %d %d",(v-a[f1])/k,f2,f1);
	}
	else return puts("NO"),0;
}
```


---

## 作者：yybyyb (赞：1)

恩

这题有毒

$CF$比赛的时候只有$30$多个人切

考完我自己改已经写死了我自己。。。细节很多

大致思路不是很难嗷。。

首先考虑所有的和是否能够满足条件

如果所有的和都小于要求，一定不可行

接下来考虑关于$K$的余数

做一个背包

算出哪些关于$K$的余数的体积是能够得到的

如果$V\%K$可行，在上面的的基础上一定能够构建出解

所以，先计算出选哪些水槽构建出$V\%K$

然后把这些水槽的水全部倒在一起

把剩下的水槽的水全部倒在一起

现在剩下的就是$K$的若干倍了

枚举之后看是倒进来还是倒出去就好了

记住，如果容量为$0$就不要倒

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#include<queue>
using namespace std;
#define ll long long
#define RG register
#define MAX 5010
inline int read()
{
    RG int x=0,t=1;RG char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}
ll sum;
int n,K,V,a[MAX],b[MAX];
bool f[MAX][MAX];
int g[MAX][MAX],gg[MAX][MAX];
bool vis[MAX];
int main()
{
	n=read();K=read();V=read();
	for(int i=1;i<=n;++i)sum+=a[i]=read();
	if(sum<V){puts("NO");return 0;}
	for(int i=1;i<=n;++i)b[i]=a[i]%K;
	f[0][0]=1;
	memset(g,-1,sizeof(g));
	for(int i=1;i<=n;++i)
	{
		f[i][b[i]]=1;g[i][b[i]]=0;gg[i][b[i]]=1;
		for(int j=0;j<K;++j)
		{
			if(i!=1||j!=0)if(f[i-1][j])f[i][j]=1;
			if(f[i-1][j])
			{
				f[i][(j+b[i])%K]=1;
				g[i][(j+b[i])%K]=j;
			}
		}
	}
	if(V%K==0)
	{
		puts("YES");
		for(int i=2;i<=n;++i)if(a[i])printf("%d %d %d\n",(a[i]-1)/K+1,i,1);
		if(V!=0)printf("%d %d %d\n",V/K,1,2);
		return 0;
	}
	if(!f[n][V%K]){puts("NO");return 0;}
	puts("YES");
	int now=V%K,fst,ns;
	for(int i=n;i>=1;--i)
		if(g[i][now]!=-1)vis[i]=true,now=g[i][now],fst=i;
		else ns=i;
	for(int i=1;i<=n;++i)
		if(i!=fst)
		{
			if(!a[i])continue;
			if(vis[i])printf("%d %d %d\n",(a[i]-1)/K+1,i,fst);
			else
			{
				if(i!=ns)printf("%d %d %d\n",(a[i]-1)/K+1,i,ns);
				sum-=a[i];
			}
		}
	int nt=fst+1;if(nt==n+1)nt=fst-1;
	if(sum-V>=K)cout<<(sum-V)/K<<' '<<fst<<' '<<nt<<endl;
	else if(sum<V)
	{
		int tt=(V-sum)/K;
		cout<<tt<<' '<<ns<<' '<<fst<<endl;
	}
	return 0;
}

```


---

