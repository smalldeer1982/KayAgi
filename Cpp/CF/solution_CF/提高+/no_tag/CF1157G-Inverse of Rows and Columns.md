# Inverse of Rows and Columns

## 题目描述

给定一个大小为 $n \times m$ 的二进制矩阵 $a$。二进制矩阵是指每个元素都是 $0$ 或 $1$ 的矩阵。

你可以对该矩阵进行若干次（也可以不进行）如下操作：每次操作可以反转矩阵的一行或一列。具体来说，反转一行就是将该行的所有值取反（$0$ 变为 $1$，$1$ 变为 $0$）；反转一列同理。

你的任务是通过某种操作序列将初始矩阵变为有序矩阵。矩阵被认为是有序的，当数组 $[a_{1, 1}, a_{1, 2}, \dots, a_{1, m}, a_{2, 1}, a_{2, 2}, \dots, a_{2, m}, \dots, a_{n, m - 1}, a_{n, m}]$ 按非递减顺序排列时，即视为有序。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 2
1 1
0 1
```

### 输出

```
YES
00
10
```

## 样例 #2

### 输入

```
3 4
0 0 0 1
0 0 0 0
1 1 1 1
```

### 输出

```
YES
010
0000
```

## 样例 #3

### 输入

```
3 3
0 0 0
1 0 1
1 1 0
```

### 输出

```
NO
```

# 题解

## 作者：zhimao (赞：3)

一道很有意思的题，思路清奇古怪。

我的做法是 $O(n\times m)$ 的 , 比楼上（或楼下）优秀 。

首先我们做完的矩阵一定是这样的：

```
0000...000
0000...000
.
.
.
0...01...1    0...01...1    0000...000
1111...111    1111...111    0000...000
.             .             .
.             .             .
.             .             .
1111...111 或 1111...111 或 0...01...1
```
这是升序，每一行都反一下就是降序 。所以我们可以发现，首尾两行必有一行全为 1 或 0 ，而为零或为一都无所谓，因为行换一下就好了，这里我们假设为 0，那么我们求出列的操作后，操作一下，此时每一行只能一起变换 ，所以我们只要判断一下：同时有 0 和 1 的行只能有一行，并且这一行只能长这样：

```
0...01...1 或 1...10...0
```
 这时候我们只要把前面都为了 1 的操作成 0，后面为 0 的操作成 1 。这一行是第二种的反一下就好了（想降序的也行）。
 
 于是本题得到了解决。
 
 代码
 
 ```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1000][1000],b[1000][1000],c[1000],bb[1000][1000],cc[1000];
void check1()
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			bb[i][j]^=a[n][j];
	int bo=0;
	for(int i=1;i<=n;i++)
	{
		int t=0;
		for(int j=1;j<=m;j++) t+=bb[i][j];
		if(t!=0&&t!=m) ++bo;
		cc[i]=t;
	}
	if(bo>1) return;
	if(bo==0)
	{
		puts("YES");
		for(int i=1;i<=n;i++) printf("%d",int(cc[i]==m));
		printf("\n");
		for(int i=1;i<=m;i++) printf("%d",a[n][i]);
		exit(0);
	}
	int i,j;
	for(i=1;i<=n;i++) if(cc[i]!=0&&cc[i]!=m) break;
	for(j=2;j<=m;j++) if(bb[i][j]!=bb[i][j-1]) break;
	for(int k=j+1;k<=m;k++)
		if(bb[i][k]!=bb[i][k-1]) return;
	puts("YES");
	for(int k=1;k<i;k++) printf("%d",int(cc[k]==m));
	printf("%d",bb[i][1]);
	for(int k=i+1;k<=n;k++) printf("%d",int(cc[k]==0));
	printf("\n");
	for(int ii=1;ii<=m;ii++) printf("%d",a[n][ii]);
	exit(0);
}
void check2()
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			b[i][j]^=a[1][j];
	int bo=0;
	for(int i=1;i<=n;i++)
	{
		int t=0;
		for(int j=1;j<=m;j++) t+=b[i][j];
		if(t!=0&&t!=m) ++bo;
		c[i]=t;
	}
	if(bo>1) return;
	if(bo==0)
	{
		puts("YES");
		for(int i=1;i<=n;i++) printf("%d",int(c[i]==m));
		printf("\n");
		for(int i=1;i<=m;i++) printf("%d",a[1][i]);
		exit(0);
	}
	int i,j;
	for(i=1;i<=n;i++) if(c[i]!=0&&c[i]!=m) break;
	for(j=2;j<=m;j++) if(b[i][j]!=b[i][j-1]) break;
	for(int k=j+1;k<=m;k++)
		if(b[i][k]!=b[i][k-1]) return;
	puts("YES");
	for(int k=1;k<i;k++) printf("%d",int(c[k]==m));
	printf("%d",b[i][1]);
	for(int k=i+1;k<=n;k++) printf("%d",int(c[k]==0));
	printf("\n");
	for(int ii=1;ii<=m;ii++) printf("%d",a[1][ii]);
	exit(0);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) scanf("%d",&a[i][j]),b[i][j]=bb[i][j]=a[i][j];
	check1();
	check2();
	puts("NO");
}
```


---

## 作者：Itst (赞：3)

考虑：如果第一行存在$1$，那么一定是一段后缀存在$1$。那么合法的第一行状态只有$M+1$种。

而如果我们确定了第一行最终的状态和第一行是否翻转，那么为了满足第一行的要求，所有列是否翻转就确定了。

那么在列翻转之后，如果第一行存在$1$，意味着$2$到$N$行每一行都是全$0$或全$1$；如果第一行没有$1$，则至多存在一行由一段$0$和一段$1$构成，其余行全$0$或全$1$。

按照上面的方式模拟，并在判断的过程中记录一下每一行、每一列是否翻转即可。复杂度$O(M^2N)$

所以这道题真的有2800 Difficulty么，还是我的算法有误……

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<iomanip>
using namespace std;

inline int read(){
    int a = 0;
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)){
        a = a * 10 + c - 48;
        c = getchar();
    }
    return a;
}

int arr[203][203] , rot[203][203] , N , M;
bool h[203] , l[203];

signed main(){
    N = read(); M = read();
    for(int i = 1 ; i <= N ; ++i)
        for(int j = 1 ; j <= M ; ++j)
            arr[i][j] = read();
    for(int i = 1 ; i <= M ; ++i)
        for(int j = 0 ; j <= 1 ; ++j){
            memset(h , 0 , sizeof(h)); memset(l , 0 , sizeof(l));
            memcpy(rot , arr , sizeof(arr));
            if(h[1] = j)
                for(int k = 1 ; k <= M ; ++k)
                    rot[1][k] ^= 1;
            for(int k = 1 ; k <= M ; ++k)
                if((k < M - i + 1 && rot[1][k]) || (k >= M - i + 1 && !rot[1][k])){
                    l[k] = 1;
                    for(int j = 1 ; j <= N ; ++j)
                        rot[j][k] ^= 1;
                }
            bool flg = 1;
            for(int k = 2 ; flg && k <= N ; ++k){
                h[k] = 1 ^ rot[k][1];
                for(int l = 2 ; flg && l <= M ; ++l)
                    flg = rot[k][1] == rot[k][l];
            }
            if(flg){
                puts("YES");
                for(int i = 1 ; i <= N ; ++i)
                    putchar('0' + h[i]);
                putchar('\n');
                for(int i = 1 ; i <= M ; ++i)
                    putchar('0' + l[i]);
                return 0;
            }
        }
    for(int j = 0 ; j <= 1 ; ++j){
        memset(h , 0 , sizeof(h)); memset(l , 0 , sizeof(l));
        memcpy(rot , arr , sizeof(arr));
        if(h[1] = j)
            for(int k = 1 ; k <= M ; ++k)
                rot[1][k] ^= 1;
        for(int k = 1 ; k <= M ; ++k)
            if(rot[1][k]){
                l[k] = 1;
                for(int j = 1 ; j <= N ; ++j)
                    rot[j][k] ^= 1;
            }
        bool flg = 1 , have = 0;
        for(int k = 2 ; flg && k <= N ; ++k){
            bool f = rot[k][1] == rot[k][M];
            if(!f)
                if(have) flg = 0;
                else{
                    have = 1; h[k] = rot[k][1];
                    bool cng = 0;
                    for(int l = 2 ; flg && l < M ; ++l)
                        if(rot[k][l] != rot[k][cng ? M : 1])
                            if(cng) flg = 0;
                            else cng = 1;
                }
            else{
                h[k] = have ^ rot[k][1];
                for(int j = 2 ; flg && j <= M ; ++j)
                    if(rot[k][1] != rot[k][j]) flg = 0;
            }
        }
        if(flg){
            puts("YES");
            for(int i = 1 ; i <= N ; ++i)
                putchar('0' + h[i]);
            putchar('\n');
            for(int i = 1 ; i <= M ; ++i)
                putchar('0' + l[i]);
            return 0;
        }
    }
    puts("NO");
    return 0;
}

```

---

## 作者：mango2011 (赞：0)

来一发比较无脑的题解。

首先观察最终的形式，发现：如果得到的序列是有序的，那么存在一个 $i$，使得前 $1\sim i-1$ 都是 $0$；后 $i+1\sim n$ 都是 $1$，并且存在一个 $j$，使得 $a_{i,1}=a_{i,2}=\dots=a_{i,j}=0,a_{i,j+1}=a_{i,j+2}=\dots=a_{i,m}=1$。

于是，我们可以尝试枚举这个 $i$，那么 $i$ 的“上面”（全部都是 $0$ 的部分）与“下面”（全部都是 $1$ 的部分）都是可以确定的。于是，我们可以转化为一个 2-sat 问题进行暴力求解。

首先判掉无解的情形。

容易发现当 $n>1$ 的时候，选取的行、列是相对固定的，于是最终第 $i$ 行有两种情形可能有解：

$0\dots01\dots1$ 或 $1\dots10\dots0$。

于是，我们只需要检查在执行能够使其余部分满足条件的操作之后该行是否为上面两种形式中的一种即可。

$n=1$ 的情形是平凡的，可以将全部的 $a_{1,i}$ 变成 $0$（$1$ 也可以），反正随便处理。

于是，我们就完整地解决了这个问题，总的复杂度是 $O(n^2m)$，由于 $n,m$ 同阶，因此复杂度就是 $O(n^3)$，常数不小。

[评测记录](https://codeforces.com/contest/1157/submission/276747373)

---

