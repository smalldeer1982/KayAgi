# Fibonacci Number

## 题目描述

斐波那契数列对10^13取模的定义如下：

　　1、F0 = 0, F1 = 1
  
　　2、Fi = (Fi-1 + Fi-2) mod (10^13) （i >= 2）
　  
  输入一个数x，问x是否在斐波那契数列当中出现过，如果出现过，最早出现在哪个位置。

## 样例 #1

### 输入

```
13
```

### 输出

```
7
```

## 样例 #2

### 输入

```
377
```

### 输出

```
14
```

# 题解

## 作者：SDNetFriend (赞：1)

## CF193E Fibonacci Number 题解
### 题意不再赘述啦
[CF193E Fibonacci Number](https://www.luogu.com.cn/problem/CF193E)

### 打表结论

在模意义下的斐波那契数列，模数从 $10^3$ 开始，对于模数 $10^i$，其存在一个长度为 $1.5\times 10^i$ 的循环结。

### 利用结论

$m$ （即模数） $=10^i$ 时，相当于取出了结果的前 $i$ 位。那么当 $i$ 继续增加时，**如果**我们找到了当前所有 $i$ 位和所求数相同的情况，那么显然地我们考虑下一位的时候可以枚举加上当前位的步长的整数位，这样就可以保证低位一定是符合要求的。

举个例子，假设 $n=998244353777$ $m=10^5$，此时第 $22103,54314,127897$ 项均为 $53777$，那我们考虑当模数扩大时，如何操作能得到在 $m=10^6$ 时 $353777$ 的位置？

如果我们从 $22103$ 开始考虑，尝试每次加一个步长 $len=1.5\times 10^5$，那我们会得到： 
$$
fab(54314+0\times len)=853777,fab(54314+1\times len)=553777,fab(54314+2\times len)=253777...
$$
我们可以这样一直枚举直到最高位变成 $3$ 或者遇到循环结后找不到。

这说明了什么？我们发现，模数较小的时候，如果较低的位置都符合要求，那么较高的位置是不确定的，但是当模数变大时，如果每次都走较小的步长，较低的位置一定和模数较小的情况是相同的。

那最终的思路已经呼之欲出了。

### 算法流程

1. 暴力找到模数为 $10^5$ 时，最低的 $5$ 位和所求值相同的情况，并全部存下来。
2. 从模数为 $10^6$ 开始求，一直到 $10^{13}$，对于模数为 $10^i$ 的情况：
    1. 存下模数 $m=10^i$，上一步步长 $len=1.5\times 10^{i-1}$ 。
    2. 对上一步留下的所有合法情况，分别加上 $0\times len,1\times len ...$，判断对 $m$ 取模后与 $n$ 对 $m$ 取模后是否相同，如果相同则存下来，留给下一步用。
3. 遍历留下的 $m=10^{13}$ 的所有情况，取最小值返回答案。 

### 贴代码 

其实感觉讲的不是很好，主要多看下代码，上边就是矩阵快速幂斐波那契的板子不重要，重点看下 solve 函数。

```cpp
#include <bits/stdc++.h>
#define lint long long
#define rint register int
using namespace std;
inline lint read(){
	char c;lint f=1,res=0;
	while(c=getchar(),!isdigit(c))if(c=='-')f*=-1;
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res*f;
}
const lint N=1e5+5,md=1e13,inf=1e18;
struct mt{
	lint v[2][2];
	mt(){memset(v,0,sizeof v);}
	mt(lint v00,lint v01,lint v10,lint v11){
		v[0][0]=v00;v[0][1]=v01;
		v[1][0]=v10;v[1][1]=v11;
	}
}a,b,x;
inline lint mul(lint x,lint y){
	lint res=0;
	while(y){
		if(y&1)res=(res+x)%md;
		x=(x<<1)%md;y>>=1;
	}return res;
}
inline mt operator*(mt m1,mt m2){
	mt r;
	for(rint i=0;i<=1;++i)
		for(rint j=0;j<=1;++j)
			for(rint k=0;k<=1;++k)
				r.v[i][j]=(mul(m1.v[i][k],m2.v[k][j])+r.v[i][j])%md;
	return r;
}
inline mt qpow(mt x,lint y){
	mt res=mt(1,0,0,1);
	while(y){
		if(y&1)res=res*x;
		x=x*x;y>>=1;
	}return res;
}
inline void init(){
	a=mt(1,1,0,0);
	b=mt(1,1,1,0);
}
inline lint fab(lint x){
	mt res=a*qpow(b,x-2);
	return res.v[0][0];
}
//以下为核心代码部分
//上方的fab(x)是用来求斐波那契的第x项的值 
lint k,vis[N],_k,_vis[N];
inline lint solve(lint n){
	if(n==1)return 1;//注意特判，不然#4会WA
	k=0;
	lint x=1,y=1,z,t=2,m=1e5;
	while(!(x==0&&y==1)){
		if(x==n%m)vis[++k]=t;
		++t;z=(x+y)%m;
		y=x;x=z;
	}//暴力找到m=10^5时最低5位和所求数相同的情况
	for(rint i=6;i<=13;++i){
		m=pow(10,i);
		lint len=15*pow(10,i-2);
        //存下模数和步长
		for(rint j=1;j<=k;++j)//依次处理上一个模数的所有合法情况
			for(rint s=0;s<=9;++s)//枚举，超过9次的都会循环起来，所以只枚举0-9就可以了
				if(fab(vis[j]+s*len)%m==n%m)
					_vis[++_k]=vis[j]+s*len;//如果得到的数前i位和所求数相同
		for(rint j=1;j<=_k;++j)
			vis[j]=_vis[j];
		k=_k;_k=0;//最后复制下信息
	}
	if(!k)return -1;
	lint ans=inf;
	for(rint i=1;i<=k;++i)
		ans=min(ans,vis[i]);
	return ans;
}
//核心代码结束 
int main(){
	init();
	printf("%lld",solve(read()));
	return 0;
}

```



---

