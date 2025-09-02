# World Evil

## 题目描述

As a result of Pinky and Brain's mysterious experiments in the Large Hadron Collider some portals or black holes opened to the parallel dimension. And the World Evil has crept to the veil between their world and ours. Brain quickly evaluated the situation and he understood that the more evil tentacles creep out and become free, the higher is the possibility that Brain will rule the world.

The collider's constriction is a rectangular grid rolled into a cylinder and consisting of $ n $ rows and $ m $ columns such as is shown in the picture below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF62E/da353d4ab03d1db9b5705495271eeba00d802297.png)In this example $ n=4 $ , $ m=5 $ . Dotted lines are corridores that close each column to a ring, i. e. connect the $ n $ -th and the $ 1 $ -th rows of the grid.

In the leftmost column of the grid the portals are situated and the tentacles of the World Evil are ready to creep out from there. In the rightmost column the exit doors are located. The tentacles can only get out through those doors. The segments joining the nodes of the grid are corridors.

Brain would be glad to let all the tentacles out but he faces a problem: the infinite number of tentacles can creep out of the portals, every tentacle possesses infinite length and some width and the volume of the corridors are, unfortunately, quite limited. Brain could approximately evaluate the maximal number of tentacles that will be able to crawl through every corridor.

Now help the mice to determine the maximal number of tentacles of the World Evil that will crawl out of the Large Hadron Collider.

## 样例 #1

### 输入

```
3 4
4 4 4
1 1 5
5 5 3
4 1 2
1 3 1
3 5 4
1 4 3
```

### 输出

```
7
```

## 样例 #2

### 输入

```
2 2
9 2
2 3
6 1
```

### 输出

```
11
```

# 题解

## 作者：cmll02 (赞：3)

ABC205 的 F 场上原地升天，于是恶补网络流。

这题直接跑网络流显然是不行的。

注意到最大流和最小割是相等的，于是我们去求最小割。

看到这个 $n\le 5$ 就知道应该要对列进行状态压缩。

于是可以 dp。

设 $dp_j$ 表示若 $j$ 的二进制表示第 $k$ 位为 $1$ 则当前第 $k$ 行已经被阻断的最小花费。

同时如果一行被阻断，我们需要维护好切割竖线，防止这行从外面绕过来而通。

这样就可以 $O(nm2^n)$ 完成。

代码（码风比较诡异，建议画图理解）

```cpp
// Problem: CF62E World Evil
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF62E
// Memory Limit: 250 MB
// Time Limit: 5000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//lost in rain
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <stdio.h>
#include <string.h> 
#include <algorithm>
#include <bitset>
#define oldl(x) printf("%lld\n",x)
#define rg(x) for(int i=1;i<=(x);i++){
#define rj(j,y,x) for(int j=(y);j<=(x);j++){
#define gr }
#define int long long
inline int read()
{
	int num=0,f=1;char c=getchar();
	while(c<48||c>57){if(c=='-')f=-1;c=getchar();}
	while(c>47&&c<58)num=num*10+(c^48),c=getchar();
	return num*f;
}
inline int re1d()
{
	char c=getchar();
	while(c<48||c>49)c=getchar();
	return c&1;
}
inline int min(int a,int b){return a>b?b:a;}
inline int max(int a,int b){return a<b?b:a;}
int r[5][100005],c[5][100005],dp[32];
signed main()
{
	int n=read(),m=read();
	rg(m-1)rj(j,1,n)r[j-1][i]=read();gr gr
	rg(m)rj(j,1,n)c[j-1][i]=read();gr gr
	memset(dp,0x3f,sizeof(dp));dp[0]=0;
	rg(m-1)
    	rj(j,0,(1<<n)-1)
        	rj(k,0,n-1)
				dp[j^(1<<k)]=min(dp[j^(1<<k)],dp[j]+r[k][i]);
            }
        }
		rj(j,0,(1<<n)-1)
        	rj(k,0,n-1)
            	if(((j>>k)&1)^((j>>((k+1)%n))&1))
                	dp[j]+=c[k][i+1];
            }
        }
    }
    oldl(dp[(1<<n)-1]);
	return 0;
}


```

---

