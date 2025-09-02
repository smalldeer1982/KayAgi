# [ABC018C] 菱型カウント

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc018/tasks/abc018_3

縦 $ R $ 行、横 $ C $ 列の長方形領域がある。上から $ i\ (1\ ≦\ i\ ≦\ R) $ 行目、左から $ j\ (1\ ≦\ j\ ≦\ C) $ 列目にあるマスをマス ($ i $, $ j $) と呼ぶことにする。これらのマスのうちいくつかのマスは黒く、他のマスは白く塗られている。

また、ある整数 $ K $ が定められている。

ここで、以下の条件を満たすように新たに緑色を塗ることを考える。この操作は1 回だけ行う。

- ある整数 の組 $ x\ (K\ ≦\ x\ ≦\ R\ -\ K\ +\ 1) $, $ y\ (K\ ≦\ y\ ≦\ C\ -\ K\ +\ 1) $ に対して、|$ i-x $|+|$ j-y $|$ ≦\ K\ -\ 1 $ を満たすすべてのマス ($ i $,$ j $) について、マス ($ i $,$ j $) は元々白いマスで、かつ、この操作で緑色に塗られる。さらに、|$ i-x $|+|$ j-y $|$ ≧\ K $ を満たすすべてのマスについて、そのマスは緑色に塗らない。

このような色の塗り方の総数はいくらか。ただし、ここでいう塗り方とは、どのマスがどの色になったかという組み合わせのことで、色の塗る順番は考慮しないものとする。

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- $ R\ ≦\ 50 $ かつ $ C\ ≦\ 50 $ を満たすデータセット $ 1 $ に正解した場合は、$ 30 $ 点が与えられる。

### Sample Explanation 1

以下の $ 3 $ 通りが考えられます (`o` は白いマス、`x` は黒いマス、`\*` は緑色のマスを表します)。 x\\\*ooo\\\*\\\*\\\*oxo\\\*ooooxxoo xo\\\*ooo\\\*\\\*\\\*xoo\\\*oooxxoo xooooooo\\\*xoo\\\*\\\*\\\*oxx\\\*o

## 样例 #1

### 输入

```
4 5 2
xoooo
oooox
ooooo
oxxoo```

### 输出

```
3```

## 样例 #2

### 输入

```
4 5 2
ooooo
oxoox
oooox
oxxoo```

### 输出

```
0```

## 样例 #3

### 输入

```
8 6 3
oooooo
oooooo
oooooo
oooooo
oxoooo
oooooo
oooooo
oooooo```

### 输出

```
4```

# 题解

## 作者：Rigel (赞：18)

## 思路

考虑旋图。

将 $(i,j)$ 旋转至 $(i+j-1,n-i+j)$。稍做处理后，统计前缀和即可。

时间复杂度为 $\mathcal{O}(n^2)$，拿下此题最优解。[link](https://www.luogu.com.cn/record/list?pid=AT_abc018_3&orderBy=1&status=&page=1)。

## 代码

```cpp
#include<bits/stdc++.h>
#define maxn 510
#define maxN 1010
using namespace std;
int n,m,k,mx,N,a[maxn][maxn],b[maxN][maxN],f[maxN][maxN],vis[maxN][maxN],ans;
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')ret=ret*10+(ch&15),ch=getchar();
	return ret*f;
}
signed main(){
	n=read(),m=read(),k=read()-1;
	mx=max(n,m),N=(mx<<1)-1;
	for(int i=1;i<=mx;i++)for(int j=1;j<=mx;j++)a[i][j]=1;
	for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)b[i][j]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char ch=getchar();
			while(ch!='x'&&ch!='o')ch=getchar();
			a[i][j]=(ch=='x');
		}
	}
	for(int i=1;i<=mx;i++)for(int j=1;j<=mx;j++)b[i+j-1][n-i+j]=a[i][j],vis[i+j-1][n-i+j]=1;
	for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)if(vis[i-1][j]&&vis[i][j-1]&&vis[i+1][j]&&vis[i][j+1])b[i][j]=0; 
	for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)f[i][j]=f[i-1][j]+f[i][j-1]-f[i-1][j-1]+b[i][j];
	for(int i=k+1;i<=N-k;i++){
		for(int j=k+1;j<=N-k;j++){
			if(!vis[i][j])continue;
			int w=f[i+k][j+k]-f[i-k-1][j+k]-f[i+k][j-k-1]+f[i-k-1][j-k-1];
			if(!w)ans++;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：xxgirlxx (赞：4)

## 题意理解

给定一个 $R$ 行 $C$ 列的字符矩阵，求有多少个字符 $(x,y)$ 满足以下要求：

1、$k \le x \le R-k+1$。

2、$k \le y \le C-k+1$。

3、设别的点到这个点的曼哈顿距离为 $d$，则所有 $d \le K-1$ 的点都是 $o$。

## 前置芝士：曼哈顿距离

首先，我们要搞清楚：什么是**曼哈顿距离**？

很简单，就是两个点的横坐标之差的绝对值加上纵坐标之差的绝对值，如果设两个点分别为 $(x_{1},y_{1})$ 和 $(x_{2},y_{2})$，那么式子就是：

$$|x_{1}-x_{2}|+|y_{1}-y_{2}|$$

用 c++ 则为：

`abs(1x-2x)+abs(1y-2y)`

其中，`abs` 为绝对值函数，如果你想手写，你可以这么写：

```cpp
int abs(int x){
  if(x<0)return (-x);
  return x;
```

用三目运算符化简为：

```cpp
int abs(int x){
  return (x<0?(-x):x);
}
```

知道了曼哈顿距离是什么，我们就可以做题了。

## 题目思路

我想了一种容易被卡的方法，但是它却真真实实地过了这道题：记录下所有 $x$ 点在哪里，然后再一个一个地跟 $k \le x \le R-k+1$ 且 $k \le y \le C-k+1$ 里的 $o$ 点进行运算，如果有一个 $x$ 点与这个 $o$ 点的曼哈顿距离 $\le K-1$，那么这个点就不会产生任何贡献，否则答案 $+1$。这样的话，复杂度有可能被卡到 $O(RCK^2)$，但是这种方法最长的一个测试点用了 $1.78s$，并没有超时（~~喜提最劣解~~）。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,x,y,ans,flag,a[510][510],blackx[250010],blacky[250010],num;
char opt;
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>opt;
			if(opt=='o')a[i][j]=0;
			else a[i][j]=1,blackx[++num]=i,blacky[num]=j;
		}
	}
	for(int i=k;i<=n-k+1;i++){
		for(int j=k;j<=m-k+1;j++){
			flag=0;
			if(a[i][j]==1)continue;
			for(int l=1;l<=num;l++)if(abs(blackx[l]-i)+abs(blacky[l]-j)<k){flag=1;break;}
			if(!flag)ans++;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：shiyihang (赞：2)

### 题意

- 给出 $R$ 行 $C$ 列的字符矩阵。
- 求在中心 $R - 2\times K$ 行 $C - 2\times K$ 列中
满足和最近的 `x` 字符的曼哈顿距离超过 $K$ 的位置个数。
- 对于 $30$ 分的数据，$3 \le R,C \le 50$。
- 对于全部的数据，$3 \le R,C \le 500$ 且 $2 \le K \le 500$。

### 做法分析

#### 部分分

首先考虑部分分做法。显然，可以对于每个在中心 $R - 2\times K$ 行 $C - 2\times K$ 列的字符都进行搜索，查找周围 $K - 1$ 格曼哈顿距离内是否有 `x` 字符，若无则对答案产生贡献。

该做法时间复杂度为 $O(RCK^2)$，可以拿到 $30$ 分的部分分。  
代码实现较为容易，故不再展开。

#### 正解

搜索算法效率不足以通过全部数据，考虑是否可以以空间换时间。

对于矩阵中的每一个点，我们可以统计其上方和下方有多少 `o` 字符。  
假设一个点可以对答案产生贡献，则需要在以该点为中心的、半径为 $K - 1$ 的菱形范围内都为 `o` 字符。  
显然，我们可以从左向右依次遍历我们统计的数组，如果有一个位置上方或下方 `o` 字符数量不足该位置应有的量，则该点无法对答案产生贡献，可以直接跳过。

该做法时间复杂度为 $O(RCK)$，即使常数较大也仍能通过全部数据。

另外，需要注意此题距离范围为 $1$ 至 $K - 1$，并非常见的 $1$ 至 $K$。

AC 代码如下：

```cpp
#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
int r, c;
int k;
char mp[505][505];
int s[505][505][2]; 
// s[i][j][0]表示第i行第j列位置上方（包括自己）有几个o
// s[i][j][1]表示第i行第j列位置下方（包括自己）有几个o
int ans;
int main()
{
    cin >> r >> c >> k;
    for (int i = 1; i <= r; ++i) {
        cin >> (mp[i] + 1);
    }
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            s[i][j][0] = mp[i][j] == 'o' ? s[i - 1][j][0] + 1 : 0;
        }
    }
    for (int i = r; i >= 1; --i) {
        for (int j = 1; j <= c; ++j) {
            s[i][j][1] = mp[i][j] == 'o' ? s[i + 1][j][1] + 1 : 0;
        }
    }
    for (int i = k; i <= r - k + 1; ++i) {
        for (int j = k; j <= c - k + 1; ++j) {
            int flg = 1; 
            // flg表示当前位置是否对答案产生贡献
            for (int l = j - k + 1, cnt = 0; l < j + k; ++l) { 
                // cnt表示在l这一列上向上和向下至少应该有几个o
                if (l <= j) {
                    ++cnt;
                }
                else {
                    --cnt;
                }
                if (s[i][l][0] < cnt || s[i][l][1] < cnt) {
                    flg = 0;
                    break;
                }
            }
            ans += flg;
        }
    }
    cout << ans << endl;
    return 0;
}

```

PS：此题综合难度较易，建议降黄。

---

