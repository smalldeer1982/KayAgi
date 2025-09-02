# Blackboard Fibonacci

## 题目描述

Fibonacci numbers are the sequence of integers: $ f_{0}=0 $ , $ f_{1}=1 $ , $ f_{2}=1 $ , $ f_{3}=2 $ , $ f_{4}=3 $ , $ f_{5}=5 $ , $ ... $ , $ f_{n}=f_{n-2}+f_{n-1} $ . So every next number is the sum of the previous two.

Bajtek has developed a nice way to compute Fibonacci numbers on a blackboard. First, he writes a 0. Then, below it, he writes a 1. Then he performs the following two operations:

- operation "T": replace the top number with the sum of both numbers;
- operation "B": replace the bottom number with the sum of both numbers.

If he performs $ n $ operations, starting with "T" and then choosing operations alternately (so that the sequence of operations looks like "TBTBTBTB $ ... $ "), the last number written will be equal to $ f_{n+1} $ .

Unfortunately, Bajtek sometimes makes mistakes and repeats an operation two or more times in a row. For example, if Bajtek wanted to compute $ f_{7} $ , then he would want to do $ n=6 $ operations: "TBTBTB". If he instead performs the sequence of operations "TTTBBT", then he will have made 3 mistakes, and he will incorrectly compute that the seventh Fibonacci number is 10. The number of mistakes in the sequence of operations is the number of neighbouring equal operations («TT» or «BB»).

You are given the number $ n $ of operations that Bajtek has made in an attempt to compute $ f_{n+1} $ and the number $ r $ that is the result of his computations (that is last written number). Find the minimum possible number of mistakes that Bajtek must have made and any possible sequence of $ n $ operations resulting in $ r $ with that number of mistakes.

Assume that Bajtek always correctly starts with operation "T".

## 样例 #1

### 输入

```
6 10
```

### 输出

```
2
TBBTTB
```

## 样例 #2

### 输入

```
4 5
```

### 输出

```
0
TBTB
```

## 样例 #3

### 输入

```
2 1
```

### 输出

```
IMPOSSIBLE
```

# 题解

## 作者：Feyn (赞：1)

[link](https://www.luogu.com.cn/problem/CF217B)

考虑如果逆向实现这个过程会是什么样子的。当前有两个数 $x,y$，执行一次 top 操作，然后就会得到 $x+y,y$。显然第一个数会比第二个数大，而 bottom 操作也是一样的，换句话说，执行一次操作之后我们看哪个数大就可以知道上一次到底操作的是哪个数。而大的数是唯一的，所以假如我们知道了最后剩下了哪两个数就可以通过这样的方法逆推出整个过程（简单来说就是找到当前的较大数，减去较小数）。至于最后两个数到底是什么，由于已经确定了一个数了，另一个数只需要枚举就可以了。

大致框架如此，有许多细节需要注意一下。

会发现这个过程本质上是一个辗转相减法，可以用辗转相除法做到 $O(\log N)$，这样可以快速去掉很多不合法的数。另外就是在保存方案的时候尽量不要用 string，会卡爆（也有可能是我不会用）。其它还有一些细节可以对着 CF 的数据调。

```cpp
#include<bits/stdc++.h>
//#define feyn
const int N=1000010;
using namespace std;
inline void read(int &wh){
	wh=0;char w=getchar();int f=1;
	while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
	while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
	wh*=f;return;
}
inline void swap(int &s1,int &s2){
	int s3=s1;s1=s2;s2=s3;return;
}

int m,n,ans=1e9;
char now[N],out[N];
inline bool check(int x){
	int y=n,an=0,nowx=x;
	while(true){
		if(x<y)swap(x,y);
		if(y==0)break;
		an+=x/y;x%=y;
	}
	return x==1&&an==m;
}
void work(int x){
	if(check(x)==false)return;
	int y=n,nowx=x,cnt=m+1;now[cnt]='\0';
	while(x>1||y>1){
		if(x>y)x-=y,now[--cnt]='T';
		else y-=x,now[--cnt]='B';
	}
	if(now[2]=='T')for(int i=2;i<=m;i++)now[i]='B'+'T'-now[i];
	now[1]='T';int num=0;
	for(int i=2;i<=m;i++)num+=now[i]==now[i-1];
	if(num<ans){
		ans=num;
		for(int i=1;i<=m+1;i++)out[i]=now[i];
	}
}

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);read(n);
	for(int i=1;i<=n;i++)work(i);
	if(ans>m)printf("IMPOSSIBLE\n");
	else printf("%d\n%s\n",ans,out+1);
	
	return 0;
}
```

---

