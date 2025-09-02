# オレンジの出荷 (Oranges)

## 题目描述

CXR决定将收获的$n$个橙子分装进一些箱子内。在NXY的工厂中，橙子排列在输送带上，依次编号为$1...n$。橙子$i(1\leq i\leq n$)的大小为$A_i$。由于分拣不方便，同一个箱子内，橙子的编号必须连续。

一个箱子内最多可以装$m$个橙子。在一个箱子内装一些橙子的成本为$k+s\times (a-b)$。$k$是箱子本身的成本，所有箱子的成本一样。$s$是该箱子中橙子的数目。 $a$是该箱子中最大橙子的大小，$b$是该箱子中最小橙子的大小。

求包装这$n$个橙子所需的最小成本。

## 说明/提示

- 1≤N≤20 000
- 1≤M≤1 000
- 0≤K≤1 000 000 000
- 1≤A_i≤1 000 000 000 (1≤i≤N)
- M≤N

本题：JOI 2016 Final T1「オレンジの出荷」

## 样例 #1

### 输入

```
6 3 6
1
2
3
1
2
1```

### 输出

```
21```

## 样例 #2

### 输入

```
16 4 12
3
10
13
10
19
9
12
16
11
2
19
9
13
2
13
19```

### 输出

```
164```

## 样例 #3

### 输入

```
16 6 14
19
7
2
15
17
7
14
12
3
14
5
10
17
20
19
12```

### 输出

```
177```

## 样例 #4

### 输入

```
10 1 1000000000
1
1
1
1
1
1
1
1
1
1```

### 输出

```
10000000000```

# 题解

## 作者：神秘番茄厂长 (赞：3)

##### 动态规划

$f[i]$表示将前$i$个数装进箱子的最小花费，由于最多装$m$个数，则$f[i]$可以从$(i-m)$~$i$这些点转移而来，同时记得加上当前这个箱子的花费。

### 代码：
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N=2e4+10;
int n,m,K,A[N],maxn=-1,minn=1e9+10;
ll f[N];

int main()
{
	cin>>n>>m>>K;
	for(int i=1;i<=n;++i)
	scanf("%d",&A[i]);
	memset(f,0x7f,sizeof(f));
	f[0]=0;
	for(int i=1;i<=n;++i)
	{
		int un=max(0,i-m);
		maxn=-1,minn=1e9+10;
		for(int j=i;j>un;--j)
		{
			maxn=max(maxn,A[j]);
			minn=min(minn,A[j]);
			f[i]=min(f[i],f[j-1]+1ll*K+(i-j+1ll)*(maxn-minn));
		}
	}
	cout<<f[n]<<"\n"; return 0;
}
```

---

## 作者：微香玉烛暗 (赞：2)

看题面就知道，是**动态规划**。

题目说，编号连续，所以一维$DP$；     
题目说，$N≤20000$ ，$M≤1000$，所以两层循环暴力；    
题目说，$a_i≤1000000000$，所以开$long long$。   

。。。就没了。

上代码：
```cpp
# include <cstdio>
# include <iostream>
# include <algorithm>
# define int long long
using namespace std;
const int N=20005;
int n,m,k,a[N],f[N];

int mx (int x,int y) {
	return x>y?x:y;
}

int mn (int x,int y) {
	return x<y?x:y;
}

signed main () {
	scanf ("%lld%lld%lld",&n,&m,&k);
	for (int i=1;i<=n;i++)
		scanf ("%lld",&a[i]);
	f[0]=0;
	for (int i=1;i<=n;i++) {
		f[i]=1e18;
        //以上初始化
		int x=-1e18,y=1e18; 
		for (int j=i;i-j<m&&j>0;j--) {
			x=mx(x,a[j]);
			y=mn(y,a[j]);
            //内层循环更新维护最大最小值
			f[i]=mn(f[i],f[j-1]+k+(i-j+1)*(x-y));
            //依照题意，就这样转移即可
		}
	} 
	printf ("%lld\n",f[n]);
	return 0;
    //完结撒花
}
//By苍空的蓝耀

```


---

## 作者：_•́へ•́╬_ (赞：1)

凭直觉，是$^D_P$

设$f(i)$表示前$i$个橙子需要最小价钱

转移很简单，见代码

```cpp
#include<stdio.h>
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define N 20001
int n,m,k,a[N];long long ans[N];
main()
{
	scanf("%d%d%d",&n,&m,&k);for(register int i=1;i<=n;++i)scanf("%d",a+i);//输入
	for(register int i=1;i<=n;++i)
	{
		ans[i]=1ll<<60;
		for(register int j=i-1,minn=a[i],maxn=a[i];j>=0&&i-j<=m;--j)//循环，同时维护最小值和最大值
		{
			ans[i]=min(ans[i],ans[j]+k+1ll*(i-j)*(maxn-minn));//更新答案（取j+1到i，j恰好不取）
			minn=min(minn,a[j]);maxn=max(maxn,a[j]);//维护最小值和最大值
		}
	}
	printf("%lld\n",ans[n]);//输出
}/**/
```



---

