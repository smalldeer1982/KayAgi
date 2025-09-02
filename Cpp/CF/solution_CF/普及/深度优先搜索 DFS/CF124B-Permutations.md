# Permutations

## 题目描述

给你 $n$ 个 $k$ 位数,您需要重新排列整数中的各位数字，使得最大数和最小数的差最小。所有整数的重排规则应该都相同。

## 说明/提示

在样例$1$中，我们将数字重新排列为$(3,1,4,2)$，则第 $2$ 个和第 $4$ 个数字将分别等于 $5237$ 和 $2537$ （它们是用该顺序调换后最大和最小的数字）。

在第二个示例中，我们交换第二个数字和第一个数字，我们会得到整数 $100$ 、$99$ 和 $102$ 。

## 样例 #1

### 输入

```
6 4
5237
2753
7523
5723
5327
2537
```

### 输出

```
2700
```

## 样例 #2

### 输入

```
3 3
010
909
012
```

### 输出

```
3
```

## 样例 #3

### 输入

```
7 5
50808
36603
37198
44911
29994
42543
50156
```

### 输出

```
20522
```

# 题解

## 作者：junyu33 (赞：2)

**这个题有next_permutation就简单了**

输入用字符串，用个f函数和permut数组（存数字所在位数）把其转换成整型。

m个数过一遍f后用**next_permutation**重置permut数组

以上过程进行n!遍后得出最小值

注意pow最好用数组,用内部可能WA。

```cpp
#include<bits/stdc++.h>
using namespace std;
char num[10][10];
int range[10][10];
int permut[10];
int m,n;
int fac[]={1,1,2,6,24,120,720,5040,40320,362880};
int poww[]={1,10,100,1000,10000,100000,1000000,10000000,100000000};
int f(int a)
{
	int t=0;
	for(int i=n; i>=1; i--) t+=range[a][i]*poww[10,permut[i]-1];
	return t;
}
int main()
{
	cin>>m>>n;
	for(int i=1;i<=n;i++) permut[i]=i;
	for(int i=1; i<=m; i++)
		scanf("%s",num[i]+1);
	for(int i=1; i<=m; i++)
		for(int j=1; j<=n; j++)
			range[i][j]=num[i][j]-'0';
	int cha=2e9;		
	for(int i=1; i<=fac[n]; i++)
	{
		int maxn=0,minn=2e9;
		for(int j=1; j<=m; j++)
		{
			maxn=max(f(j),maxn);
			minn=min(f(j),minn);
		}
		cha=min(cha,maxn-minn);
		next_permutation(permut+1,permut+n+1);
	}
	cout<<cha;
	return 0;
}

```


---

## 作者：Fur_Zes (赞：0)

本题是一道很裸的暴力，拿来练习回溯和字符串很不错。

具体思路以下：我们可以先把这 $k$ 位数的全排列求出来并存入数组 $a_i$ 中，每完成一次全排列的生成就将这 $n$ 个 $k$ 位的数字（我们不妨设为字符串 $s_i$），对应着数组 $a_i$ 中的排列顺序求和并存入数组 $b_i$ 中，表示这次排列之后 $s_i$ 中的元素变化成什么样：

```cpp
b[i]+=(s[i][a[j]]-'0')*pow(10,j);
```

其中 $1 \le i \le n$，$0 \le j \le k$。

显然，我们每把 $b_i$ 数组生成完一遍之后就可以 sort 一遍然后取 $mins= \min \{mins ,b_n - b_1\}$，最后输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,use[10],a[10],b[10],mins=INT_MAX;
string s[10];
void udt()	//更新最小值
{
	memset(b,0,sizeof(b));
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<k;j++)
		b[i]+=(s[i][a[j]]-'0')*pow(10,j);	//核心
	}
	sort(b+1,b+n+1);
	mins=min(mins,b[n]-b[1]);
}
void dfs(int t)	//全排列
{
	if(t==k)
	{
		udt();
		return;
	}
	for(int i=0;i<k;i++)
	{
		if(!use[i])
		{
			use[i]=1;
			a[t]=i;
			dfs(t+1);
			use[i]=0;
		}
	}
}
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	cin>>s[i];
	dfs(0);
	cout<<mins;
	return 0;
}
```

当然，在STL库中还有一句很神奇的 
```cpp
next_permutation
```

，他可以方便的生成全排列，具体的可以看第一篇题解，这里就不放代码了，但本人还是建议打回溯，作为一道回溯的练习题，对以后搜索等算法有很大帮助。

完结撒花。

---

