# Recover the String

## 题目描述

For each string $ s $ consisting of characters '0' and '1' one can define four integers $ a_{00} $ , $ a_{01} $ , $ a_{10} $ and $ a_{11} $ , where $ a_{xy} $ is the number of subsequences of length $ 2 $ of the string $ s $ equal to the sequence $ {x,y} $ .

In these problem you are given four integers $ a_{00} $ , $ a_{01} $ , $ a_{10} $ , $ a_{11} $ and have to find any non-empty string $ s $ that matches them, or determine that there is no such string. One can prove that if at least one answer exists, there exists an answer of length no more than $ 1000000 $ .

## 样例 #1

### 输入

```
1 2 3 4
```

### 输出

```
Impossible
```

## 样例 #2

### 输入

```
1 2 2 1
```

### 输出

```
0110
```

# 题解

## 作者：CaiXY06 (赞：2)

由于知晓了 $00$ 和 $11$ 的对数，所以我们可以很轻易根据等差数列求和的柿子的变形 $n_0\times (n_0-1)=2\times a_{00}$（$1$ 类似） 的得到 $0$ 和 $1$，然后判断无解的情况。

判断无解是用 $\sqrt{n\times (n-1)}+1$ 求出的值（其间需判断是否无 $0$ 或无 $1$ 去去掉多加的 $1$）去验证是否符合条件，即 $n_0\times n_1=a_{01}+a_{10}$。

然后我们考虑怎么构造。我们直接考虑 $0$ 或 $1$ 的摆放位置，比如考虑 $0$ 的位置。

我们已经知道保证有解，所以只要关心是否符合 $a_{01}$ 即可。因为每个 $0$ 的贡献就是其后的 $1$ 的数量，所以我们可以暴力枚举每一个位判断是否能放 $0$ 否则放 $1$，然后输出方案即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,A,B,C,D;
int main(){
	scanf("%d%d%d%d",&A,&B,&C,&D);
	n=sqrt(A<<1)+1,m=sqrt(D<<1)+1;
	(n<m?n:m)-=(!B&&!C);
	if(n*(n-1)!=A+A||m*(m-1)!=D+D||n*m!=B+C)return puts("Impossible"),0;
	for(int i=n+m;i;i--)
	if(B>=m)putchar('0'),B-=m;
	else putchar('1'),m--;
	return 0;
}
```


---

## 作者：liuyifan (赞：0)

## 构造+模拟
已知00,11串的数目可以知道0,1的数量 

然后利用x*(x-1)=a快速求得正整数解然后相乘验证一下是否有解。

关于01串和10串的数量，假设0全在左边，1全在右边，得出01串的数目就是cnt1*cnt2(该题有SPJ)

code:
```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define reg register
#define ll long long
using namespace std;
int num[1000010],a,b,c,d,h;
int main()
{
	cin>>a>>b>>c>>d;
	reg int cnt1=sqrt(2*a)+1;
	reg int cnt2=sqrt(2*d)+1;//前面的多项式 
	if(cnt1*(cnt1-1)!=2*a||cnt2*(cnt2-1)!=2*d)return puts("Impossible"),0;//直接结束 
	if(a+b+c+d==0)return puts("0"),0;
	if(a+b+c==0)
	{
		for(reg int i=1;i<=cnt2;i++)printf("1");
		return 0;
	}
	if(a&&b+c+d==0)
	{
		for(reg int i=1;i<=cnt1;i++)printf("0");
		return 0;
	}//构造 
	if(cnt1*cnt2!=b+c)return puts("Impossible"),0;//直接结束
	while(c)
	{
		if(c>=cnt1)
		{
			c-=cnt1;
			num[++h]=1;
		}
		else
		{
			num[++h+cnt1-c]=1;
			c=0;
			break;
		}
	}
	for(reg int i=1;i<=cnt2-h;i++)num[cnt1+cnt2+1-i]=1;
	for(reg int i=1;i<=cnt1+cnt2;i++)printf("%d",num[i]);//构造 
	return 0;//圆满结束 
}
```

---

