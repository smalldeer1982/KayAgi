# Diverse Matrix

## 题目描述

对于一个r行c列的矩阵，我们可以求出它每一行，每一列的最大公约数（共r+c个数）。
输入r,c。要求输出一个矩阵，满足这r+c个数不同，且这r+c个数的最大值最小。

## 样例 #1

### 输入

```
2 2
```

### 输出

```
4 12
2 9```

## 样例 #2

### 输入

```
1 1
```

### 输出

```
0
```

# 题解

## 作者：流绪 (赞：8)

构造！

首先对于一个单行或单列的矩阵，结果很显然是相邻两项之差为 1，这样对于该行（列）gcd=1，对于列（行）gcd 为数本身，只要让第一个数大于 2，后面递增即可。

拓展到多行怎么做呢？同样按照上面思路，我们举一行拓展为多行的例子。

此时列数不变，即列的 gcd 可以同样按照上面的方法，行数增加了，我发现第一行 gcd=1，那我们直接给增加的每一行乘上一个系数不就好啦。这样每一行的 gcd= 系数 *1。

注意如果我们先算行的 gcd 的话，按上述方法此时已用的数是 1 到 r，所以列构造时 gcd 应从 r+1 开始。

下面是 AC 代码。
```cpp
#include<bits/stdc++.h>
#define int long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
#define ri register int
#define il inline
#define mod 1e9+9
#define db() cout << 1 << endl
#define eps 0.000001
using namespace std;
signed main()
{
	ios::sync_with_stdio(0);
	int r,c;
	cin >> r >> c;
	if(r==1||c==1)//特判单行单列情况
	{
		int p=2;
		if(r==c)
			cout << 0;
		else
			for(int i=1;i<=r;i++)
			{
				for(int j=1;j<=c;j++)
					cout << (p++) << " ";
				cout << endl;
			}
		return 0;
	}
	for(int i=1;i<=r;i++)//普通情况
	{
		for(int j=1;j<=c;j++)
			cout << (r+j)*i << " ";
		cout << endl;
	}
  	return 0;
}
```


---

## 作者：BqtMtsZDnlpsT (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF1266C)

一道 CF1400 的构造题，还是很符合难度评级的。


因为要最小化每行每列的最大公约数最大值，所以理论最好方法就是最大公约数分别为 $1,2,3...,r+c$。

然后我们就考虑做这么一张表：
- 每行的最大公约数分别为 $1,2,3...,r$。
- 每列的最大公约数分别为 $r+1,r+2...,r+c$。
- 因为每个数不仅要满足行，还要满足列，所以设当前行的最大公约数为 $x$，当前列的最大公约数为 $y$，当前值为 $xy$。

然后按照上面模拟即可。

一个注意点当列数为 $1$ 时：
- 每行的最大公约数分别为 $1,2,3...,c$。
- 列的最大公约数为 $c+1$。

因为如果按照之前方法构造，每行的最大公约数会乘上一个 $c+1$。

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<queue>
#include<set>
#include<algorithm>
#define int long long
using namespace std;
//char cc[1<<21],*uu=cc,*vv=cc;
//#define getchar() (uu==vv&&(vv=(uu=cc)+fread(cc,1,1<<21,stdin),uu==vv)?EOF:*uu++)
int t,p[1000005],q[1000005];
inline int read(){
	char ch=getchar();int X=0;bool fl=0;
	while(ch<'0'||ch>'9'){if(ch=='-')fl=1;ch=getchar();}
	while(ch>='0'&&ch<='9'){X=(X<<1)+(X<<3)+ch-'0';ch=getchar();}
	if(fl)return ~(X-1);
	return X;
}
int a[505][505];
signed main(){
	int n=read(),m=read();
	if(n==1&&m==1){puts("0");return 0;}
	if(n<m){//为了方便（其实也不方便），判 n 和 m 的关系。
		for(int i=1;i<=n;i++)
			for(int j=n+1;j<=m+n;j++)a[i][j-n]=i*j;
	}
	else{
		for(int i=m+1;i<=m+n;i++)
			for(int j=1;j<=m;j++)a[i-m][j]=i*j;
	}
	for(int i=1;i<=n;i++,puts(""))
		for(int j=1;j<=m;j++)cout<<a[i][j]<<' ';
}
```


---

## 作者：Michael1234 (赞：0)

- 本题是**构造**题：

- 我们把第 $i$ 行的最大公约数设为 $i$，第 $j$ 列的最大公约数设为 $r+j$。

- 接下来，第 $i$ 行 $j$ 列的数就是 $i\times (r+j)$。

- 当 $r$ 和 $c$ 的值都为 $1$，无解。

- 当 $r$ 和 $c$ 的值有一个为 $1$，则从 $2$ 到 $r$ 或 $c$ 进行输出。

## CODE

~~~cpp
#include<bits/stdc++.h>
using namespace std;
int r,c;
int main()
{
	cin>>r>>c;
	if(r==1&&c==1)
	{
		cout<<0;
		return 0;
	}//无解,都为1
	if(r==1)
	{
		for(int i=1;i<=c;i++)
		{
			cout<<i+1<<" ";
		}
		return 0;
	}//行为1
	if(c==1)
	{
		for(int i=1;i<=r;i++)
		{
			cout<<i+1<<"\n";
		}
		return 0;
	}//列为1
	for(int i=1;i<=r;i++)
	{
		for(int j=1;j<=c;j++)
		{
			cout<<i*(r+j)<<" ";//输出行列最大公约数之积
		}
		cout<<"\n";
	}
	return 0;
}

---

## 作者：wuyixiang (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1266C)

题意：输出 $r \times c$ 的矩阵，使得每行每列的最大公约数均不相同且最大的最小。

很显然只需要构造每行每列的最大值为 $r + c$ 就行了。这个很简单，只需要现将第 $i$ 行设为 $i$，再乘上第 $j + c$ 列即可。这样，每行最大公因数一定为 $i$，每列为 $j + c$，符合条件。另外，当 $r$ 或 $c$ 为 $1$ 时，记得特判，因为每一列（行）的最大公因数为本身，所以剩下的那一行（列）必须为它们的最大值加一。

注意这些细节之后，就可以畅快爆切了。

## AC Code:

```cpp
#include <iostream>
using namespace std;
int main()
{
    int r,c;
    cin >> r >> c;
    if(r == 1 && c == 1)cout << 0;
    else
        for(int i = 1;i <= r;i ++)
        {
            for(int j = 1;j <= c;j ++)
            {
                if(r == 1)cout << j + 1 << " ";//特判
                else if(c == 1)cout << i + 1 << " ";
                else cout << (i + c) * j << " " ;
            }
            cout << endl;
        }
}

---

