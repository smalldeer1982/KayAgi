# Roman and Browser

## 题目描述

### 题目大意

给定一个长度为 $n$ 的只有 $1$ 和 $-1$ 的序列，选择一个位置 $b$，然后删掉位置为 $b+i\times k$ 的数（$i$ 为整数），求操作后 $1$ 和 $-1$ 数量之差的绝对值的最大值。

## 样例 #1

### 输入

```
4 2
1 1 -1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
14 3
-1 1 -1 -1 1 -1 -1 1 -1 -1 1 -1 -1 1
```

### 输出

```
9
```

# 题解

## 作者：AC机 (赞：4)

不得不说，暴力大法好啊。

这题暴力枚举b，然后标记b+i×k，再根据题意模拟，统计1为e和-1为s的个数，再将$|e-s|$与之前的答案取$\max$。记得初始化答案为最小值。

注意，为了方便起见，我们将-1在读入时全部视为0。

```cpp
#include<stdio.h>
#include<cctype>
#include<cstring>
using namespace std;
typedef unsigned long long ull;
typedef unsigned long int ul;
typedef long long ll;
int n,k;
const int N=100;
bool a[N+5];
bool flag[N+5];
int ans;
template <typename code>inline code abs(const code &a)
{
	return a>0?a:-a;
}
template <class code>inline code max(const code &a,const code &b)
{
	return a>b?a:b;
}
/*
abs和max手写会快一点。如果看不懂template的话，可以使用下面的替代，效果差不多。
inline int abs(const int &a)
{
	return a>0?a:-a;
}
inline int max(const int &a,const int &b)
{
	return a>b?a:b;
}
*/
int main ()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		if(x==1) a[i]=1;
	}
	for(int b=1;b<=n;b++)
	{
		memset(flag,0,sizeof(flag));
		for(int i=(1-b)/k;i<=(n-b)/k;i++)//将i的起始值和终止值代入，可得b+i*k最小值为1，最大值为n。
		{
			flag[b+i*k]=1;
		}
		int e=0,s=0;
		for(int i=1;i<=n;i++)
		{
			if(!flag[i])//flag是标记，如果flag[i]为1代表a[i]被删了，如果为0代表没有被删除。
			{
				if(a[i]) ++e;//e为1的个数。
				else ++s;//s为-1的个数
			}
		}
		ans=max(abs(e-s),ans);//更新答案。
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：decoqwq (赞：4)

给定一个序列，要么为$1$要么为$-1$，选定一个$l(1\leq l\leq k)$，对于所有$i(i\equiv l\pmod k)$，将$a_i$改为$0$，求序列绝对值最大值

直接枚举$l$，然后模拟求出答案，取最大值即可

不给代码啦

---

## 作者：floatery (赞：3)

给@Decoration的题解补充代码

```cpp
#include <stdio.h>
int a[101];
int main()
{
	int n,k,i,j,mx=0,ans=0,t;
	scanf("%d%d",&n,&k);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		ans+=a[i];
	}
	//if(ans<0) ans=-ans;
	for(i=1;i<=k;i++)
	{
		int l=ans;
		for(j=i;j<=n;j+=k)
		{
			l-=a[j];
		}
		if(l<0) l=-l;
		if(l>mx) mx=l;
		//t=l;
	}
	printf("%d\n",mx);
	return 0;
}
```

---

## 作者：Zouzhuoxuan (赞：1)

# CF1100A Roman and Browser 题解

## [题目传送门](https://www.luogu.com.cn/problem/CF1100A)


1. 题意简述

给一个长为 $n$ 的序列 $a$，$a_i\in \{1,-1\}$，可以选择一个整数 $b$，然后删除掉序列 $a$ 中的第 $b+ki$ 项，$i\in Z$。让序列中 $1$ 和 $-1$ 的个数的差值最大。

2. 算法分析

数据范围：$2\le k < n\le 100$，于是考虑模拟。

暴力枚举 $b$，因为 $i$ 为整数，所以 $b$ 的范围在 $1\sim k$（或者 $0\sim k-1$）。

然后开一个数组记录一下被删除的数即可。

3. 复杂度分析

时间复杂度：$O(n^2)$；

空间复杂度：$O(n)$。

4. 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[105];
bool del[105]; //被删除的数，true 为被删，false 反之。
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n,k,i,j,maxn=0;
    cin>>n>>k;
    for(i=1;i<=n;i++) cin>>a[i];
    for(i=1;i<=k;i++) //i 模拟 b。
    {
        memset(del,0,sizeof(del)); //数组清空。
        for(j=i;j<=n;j+=k) del[j]=1; //j 模拟 i。
        int t1=0,t2=0; //t1 为 1 的个数，t2 为 -1 的个数。
        for(j=1;j<=n;j++) if(!del[j]) (a[j]==1)?(t1++):(t2++); //记录 1 和 -1 个数。
        maxn=max(maxn,abs(t1-t2)); //更新最大值。
    }
    cout<<maxn<<endl;
	return 0;
}
```

---

## 作者：lizulong (赞：1)

## 题意
有一个序列，只包含 $-1$ 和 $1$。

选一个 $b$ 删掉位置 $b+1 \times k$ 的数，求数列中 $1$ 与 $-1$ 的数量差的最大值。
## 思路
直接暴力枚举 $b$ 再根据题意模拟，记录最大值。
## 代码实现
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[114514];
int n,k,ans=0;
int maxx=INT_MIN;//INT_MIN为int最小值 
signed main(){
	ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL);//优化cin cout
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i],ans+=a[i];//-1 与 1 会互相抵消 
	for(int i=1;i<=k;i++){//模拟 
		int ans2=ans;
		for(int b=i;b<=n;b+=k) ans2-=a[b];
		maxx=max(maxx,abs(ans2));
	}
	cout<<maxx<<"\n";
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/120302113)


---

## 作者：ly618x (赞：0)

算法：暴力枚举、模拟。

暴力枚举 $b$，模拟每一种操作的结果，取其中的最大值。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,k;
int a[105];
int ans=0;
bool f[105];
signed main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int b=1;b<=k;b++)//这里要注意
	{
		for(int i=1;i<=n;i++)f[i]=true;
		for(int =0;b+i*k<=n;i++)f[b+i*k]=false;//打上标记
		int fy=0,zy=0;//统计-1与1的数量
		for(int i=1;i<=n;i++)
		{
			if(f[i]==false)continue;
			if(a[i]==1)zy++;
			else fy++;
		}
		ans=max(ans,abs(fy-zy));//abs(x)表示x的绝对值
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Zhddd_ (赞：0)

## 分析

暴力枚举 $b$，然后在模拟删掉的操作即可。

时间复杂度： $O(n ^ 2)$，在 $n = 100$ 的情况下轻松通过。

具体细节请看代码。

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int n, k;
int a1[110], a2[110], d, ans;
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a1[i]);
	}
	for (int b = 1; b <= n; b++) { // 枚举要删的位置
		for (int i = 1; i <= n; i++) { // 把 a1 复制一份
			a2[i] = a1[i];
		}
		for (int i = 0; b - i * k >= 1; i++) { // 删掉位置 <= b 的数
			a2[b - i * k] = 0;
		}
		for (int i = 1; b + i * k <= n; i++) { // 删掉位置 > b 的数
			a2[b + i * k] = 0;
		}
		d = 0;
		for (int i = 1; i <= n; i++) { // 统计答案
			d += a2[i];
		}
		ans = max(abs(d), ans);
	}
	printf("%d", ans);
	return 0;
}
```

---

