# Painting Pebbles

## 题目描述

There are $ n $ piles of pebbles on the table, the $ i $ -th pile contains $ a_{i} $ pebbles. Your task is to paint each pebble using one of the $ k $ given colors so that for each color $ c $ and any two piles $ i $ and $ j $ the difference between the number of pebbles of color $ c $ in pile $ i $ and number of pebbles of color $ c $ in pile $ j $ is at most one.

In other words, let's say that $ b_{i,c} $ is the number of pebbles of color $ c $ in the $ i $ -th pile. Then for any $ 1<=c<=k $ , $ 1<=i,j<=n $ the following condition must be satisfied $ |b_{i,c}-b_{j,c}|<=1 $ . It isn't necessary to use all $ k $ colors: if color $ c $ hasn't been used in pile $ i $ , then $ b_{i,c} $ is considered to be zero.

## 样例 #1

### 输入

```
4 4
1 2 3 4
```

### 输出

```
YES
1
1 4
1 2 4
1 2 3 4
```

## 样例 #2

### 输入

```
5 2
3 2 4 1 3
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
5 4
3 2 4 3 5
```

### 输出

```
YES
1 2 3
1 3
1 2 3 4
1 3 4
1 1 2 3 4
```

# 题解

## 作者：yu__xuan (赞：5)

### 题目
[CF509B Painting Pebbles](https://www.luogu.org/problem/CF509B)

### 思路
贪心。题目要求使任意两堆石头中相同颜色的石头的数量之差小于等于 $1$ 。
* 很显然我们对每一堆石头尽量涂相同的颜色即可。

* 因为每一堆石头数量不同我们要使每一堆石头的相同数量的颜色相同这样才可以给后面留出更大的空间

贪心策略：设$mina = \min a[i]$，然后将每堆的前 $mina + 1$ 个石子染成1，后面的石子按顺序染颜色 $2 \sim k$ 即可。当石头数量最多的那一堆的数量 $maxx$  大于 $k + mina + 1$ 时无解。

### $Code$
```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<algorithm>
#define MAXN 101

inline void read(int &T) {
	int x=0;bool f=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=!f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	T=f?-x:x;
}

int n,k,a[MAXN],b[MAXN];

int main() {
	read(n),read(k);
	int minn=0x7fffffff,maxx=0;
	for(int i=1;i<=n;++i) {
		read(a[i]);
		if(a[i]>maxx) maxx=a[i];
		if(a[i]<minn) minn=a[i];
	}
	if(maxx-minn>k) {
		puts("NO");
		return 0;
	}
	puts("YES");
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=a[i];++j) {
			if(j<=minn+1) printf("1 ");
			else printf("%d ",j-minn);
		}
		puts("");
	}
	return 0;
}
```
讲得不好请感性理解。

---

## 作者：damage (赞：5)

# 题解

这题本质上其实就是[**贪心**]

1. 考虑到求出最小的一堆石子数量，设为```mina```，即其中$mina=\min\limits_{1\leq{i}\leq{n}}\{a[i]\}$。

2. 然后将每堆的前```mina+1```个石子（能染多少是多少）染成$1$（方便起见）颜色。

3. 后面的石子按顺序染颜色$2$~$k$即可。

例如[样例$3$]：

1. 先求出$mina=\min\{3,2,4,3,5\}=2$

2. 然后按照[步骤$2$]将每堆的前三颗石子染成$1$颜色，结果如下：

 ```
 1 1 1
 1 1
 1 1 1 ?
 1 1 1
 1 1 1 ? ?
 ```
 其中```?```表示还未染色的石子

3. 然后按照[步骤$3$]染即可，就成功了（注意此题```SPJ```）

 ``` 
 1 1 1
 1 1
 1 1 1 2
 1 1 1
 1 1 1 2 3
 ```
 
不可能的情况也很简单，仔细想想就知道当且仅当任意一堆染得石子数量不足本队石子总数（即```mina+k+1<a[i]```），才输出```NO```。

---

# 代码

```cpp
#include<stdio.h>
int n,k,a[110],mina=233333333,times,used[110],res[110][110]; //其中used[i]表示第i堆石子已经染了used[i]颗石子
void paint(int num,int id)
{
	for(register int i=1;i<=n;++i)
	{
		times=num; //倒计时染色石子颗数
		for(;used[i]<a[i]&&times;++used[i],--times) res[i][used[i]+1]=id; //注意染的数量的限制（used[i]<a[i]）
	}
	return ;
}
int main()
{
	scanf("%d%d",&n,&k);
	for(register int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		if(a[i]<mina) mina=a[i]; //求mina
	}
	paint(mina+1,1); //步骤2
	for(register int i=2;i<=k;++i) paint(1,i); //步骤3
	for(register int i=1;i<=n;++i) //若任意一堆染得石子数量不足本队石子总数，就输出NO
	{
		if(used[i]!=a[i]) //同理
		{
			printf("NO\n");
			return 0;
		}
	}
	printf("YES\n"); //记得输出YES
	for(register int i=1;i<=n;++i)
	{
		for(register int j=1;j<=a[i];++j) printf("%d ",res[i][j]); //输出染色结果
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：12345678hzx (赞：1)

## 思路
本题是贪心。

思路就是能染同一种颜色就染同一种颜色。设 $minn$ 为所有石子堆中最少的那一堆，我们就将每一堆的前 $\min(a_i,minn)$ 个石子染成颜色 $1$。然后所有的后面的石子依次染成 $2$ 至 $k$，当颜色不够则无解。

---

## 作者：Purple_Circle (赞：1)

题目要求任意两堆石子中相同颜色的石头的数量之差小于等于 $1$。

也就是说对每一堆石头尽量涂相同的颜色。

因为每一堆石头数量是不同的，而每次尽量涂相同的颜色才能为后面的染色提供更多策略与选择，这样才能保证尽量有解。
 
### 策略如下：

设 $minn=\min\limits_{i=1}^na_i, maxn=\max\limits_{i=1}^na_i$，则当 $maxn-minn>k$ 时即为无解。

在同一堆石子中，前 $minn+1$ 染成 $1$，后面的石子依次染成 $2\sim k$ 即可。

代码如下：
```cpp
#include<bits/stdc++.h>
#define rd read()
using namespace std;
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * f;
}
const int inf=0x3f3f3f3f;
int minn=inf,maxn=-inf;
int n,k,a[100];
int main() {
	n=rd,k=rd;
	for(int i=1;i<=n;i++) {
		a[i]=rd;
		maxn=max(maxn,a[i]);
		minn=min(minn,a[i]);
	}
	if(maxn-minn>k) {
		cout<<"NO\n";
		return 0;
	}
	cout<<"YES\n";
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=a[i];j++){
			cout<<(j-1<=minn?1:j-minn)<<" ";
		}
		endl(cout);
	}
	return 0;
}
```

---

## 作者：lucktains (赞：0)

先分析题目：

要使差小于等于一。

设最小长度为 $min$，最大为 $max$

就先将每一堆的 $1\sim {min+1}$ 都填上 ```1```。

这可以保证每一个间只差一。

再将 $min+2 \sim max$ 填上 $2\sim k$。

如果还没有填到 $max$ 就无解 （就是 $min+k<max$）。

## AC Code
```cpp

#include <bits/stdc++.h>

using namespace std;
    int minn=INT_MAX,maxx=-1;
int main()
{
    int n,k;
    cin>>n>>k;
    vector<int>a(n);
    for(int &i:a){
        cin>>i;
        minn=min(minn,i);
        maxx=max(maxx,i);
    }
 //   sort(a.begin(),a.end());

    if(minn+k<maxx){
        cout<<"NO";
        return 0;
    }
    cout<<"YES\n";
    for(int i:a){
        for(int j=1;j<=i;j++){
            if(j<=minn)cout<<1<<" ";
            else cout<<j-minn<<" ";
        }
        cout<<'\n';
    }
   return 0;
}
```

---

