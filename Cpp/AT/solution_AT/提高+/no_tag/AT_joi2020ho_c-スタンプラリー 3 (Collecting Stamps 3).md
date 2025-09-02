# スタンプラリー 3 (Collecting Stamps 3)

## 题目描述

JOI 君生活的 IOI 国有一个著名的湖泊，今天一场集邮大会在湖边举行。

绕湖一圈总共有 $N$ 种邮票可以收集，编号分别为 $1...N$ ，收集点绕湖顺时针排列。湖的周长为 $L$，第 $i$ 张邮票 $(1\le i\le N)$ 的收集点在距离出发点顺时针走 $X_i$ 米的位置。

参赛者在比赛开始的时候要站在出发点的位置，当大会开始时，参赛者可以绕湖顺时针或者逆时针移动，参赛者能够得到第 $i$ 张邮票 $(1\le i\le N)$ 当且仅当他到达收集点的时间在比赛开始时的 $T_i$ 秒以内（含）。

JOI 君也是集邮大会的参与者。他的移动速度是每秒钟 $1$ 米，你可以认为只有移动才会消耗时间。

请你计算他最多能收集到多少种邮票。

## 说明/提示

对于 $100\%$ 的数据，保证 $1\le N\le200,2\le L\le10^9,1\le X_i<L,X_i<X_{i+1},0\le T_i\le10^9$ 。

|子任务编号|分值|特殊限制|
|:-:|:-:|:-:|
|$1$|$5$|$N\le12,L\le200,T_i\le200$|
|$2$|$10$|$N\le15$|
|$3$|$10$|$L\le200,T_i\le200$|
|$4$|$75$|无|

## 样例 #1

### 输入

```
6 25
3 4 7 17 21 23
11 7 17 10 8 10```

### 输出

```
4```

## 样例 #2

### 输入

```
5 20
4 5 8 13 17
18 23 15 7 10```

### 输出

```
5```

## 样例 #3

### 输入

```
4 19
3 7 12 14
2 0 5 4```

### 输出

```
0```

## 样例 #4

### 输入

```
10 87
9 23 33 38 42 44 45 62 67 78
15 91 7 27 31 53 12 91 89 46```

### 输出

```
5```

# 题解

## 作者：__2009 (赞：1)

### Topic
第一行三个正整数，$n,L$ 。  
接下来一行 $n$ 个数，分别为 $X_1,X_2 , _\cdots ,X_n$ 表示各种类邮票的收集位置。

接下来一行 $n$ 个数，分别为 $T_1,T_2 , _\cdots ,T_n$ 表示各种类邮票的最晚可收集时间。  
他每秒能走一米，问最多能收集到多少种种类的邮票。  

### Solution
首先看到数据范围 $n\leq200$ 说明可以跑 $O(n^3)$ 。根据这个思维导向,以及题目中路线的成环,我们可以考虑拆环成链的区间dp思维。  
考虑状态 $f[i][j][k][0/1]$ 表示左边跑到第 $i$ 个集票点，右边跑到第 $j$ 个集票点，已经集到了 $k$ 个，现在往左/右。

这里有一个转化很关键,可以发现k是我们最后需要求的,但却放在了状态里,原因是时间比较大,如果把时间作为维度需要离散化,且转移麻烦,而数量k范围 小,变化也容易计算。  

那么转移也不难想:  
对于最后在左端点停留的情况,记 $tmp=f[l][r][k][0]$ ,位置数组为 $a[ ]$。  

原本停在左端点,这次继续往左边走,显然走到新的物品需要花费 $tmp+a[n-l+1]-a[n-l]$ ,  
原本停在左端点,这次往右边走,显然走到新的物品需要花费 $tmp+L-a[n-l+1]+a[r+l]$ 。 

对于最后在右端点停留的情况,记 $tmp=f[l][r][k][1]$ ,位置数组为 $a[ ]$。 

原本停在右端点,这次继续往右边走,显然走到新的物品需要花费 $tmp+a[r+1]-a[r]$ ,  
原本停在右端点,这次往左边走,显然走到新的物品需要花费 $tmp+L-a[n-l]+a[r]$ 。

然后就可以推出答案了，为 $f[i][j][k][0/1]$ 中 $f[i][j][k][0/1]$ 不为 $INF$ 的中的 $k$ 的最大值

状态转移有点长，就不打了，看我代码吧。
### Code
```cpp
#include<iostream>
#include<string.h>
using namespace std;
const int maxn=400;
long long f[maxn][maxn][maxn][2];
int x[maxn],t[maxn];
int n,l;
int ans;
int mt;
int main(){
	cin>>n>>l;
	for(int i=1;i<=n;i++)cin>>x[i];x[n+1]=l;
	for(int i=1;i<=n;i++)cin>>t[i],mt=max(mt,t[i]);
	memset(f,0x3f,sizeof f);
	f[0][0][0][0]=f[0][0][0][1]=0;
	for(int ll=0;ll<n;ll++){
		for(int i=0,j=ll;i<=ll;i++,j--){
			for(int k=0;k<=i+j;k++){
//其实：https://atcoder.jp/contests/joi2020ho/submissions/52140276
				f[i+1][j][k+(f[i][j][k][0]+(x[i+1]-x[i])<=t[i+1])][0]=min(f[i+1][j][k+(f[i][j][k][0]+(x[i+1]-x[i])<=t[i+1])][0],f[i][j][k][0]+(x[i+1]-x[i]));
				f[i][j+1][k+(f[i][j][k][0]+(l+x[i]-x[n-j])<=t[n-j])][1]=min(f[i][j+1][k+(f[i][j][k][0]+(l+x[i]-x[n-j])<=t[n-j])][1],f[i][j][k][0]+(l+x[i]-x[n-j]));
				f[i+1][j][k+(f[i][j][k][1]+(l+x[i+1]-x[n-j+1])<=t[i+1])][0]=min(f[i+1][j][k+(f[i][j][k][1]+(l+x[i+1]-x[n-j+1])<=t[i+1])][0],f[i][j][k][1]+(l+x[i+1]-x[n-j+1]));
				f[i][j+1][k+(f[i][j][k][1]+(x[n-j+1]-x[n-j])<=t[n-j])][1]=min(f[i][j+1][k+(f[i][j][k][1]+(x[n-j+1]-x[n-j])<=t[n-j])][1],f[i][j][k][1]+(x[n-j+1]-x[n-j]));
			}
		}
	}
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			for(int k=0;k<=n;k++){
				if(min(f[i][j][k][0],f[i][j][k][1])<=mt){
					ans=max(ans,k);
				}
			}
		}
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

断环成链，$f_{l,r,i,0/1}$ 表示选择了 $[l,r]$，选了 $i$ 个点的最小时间。转移是枚举往左转移或者往右转移（扩展 $1$ 个，视情况看能否增加选择点数），转移部分是简单的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 405, inf = 0x3f3f3f3f;
int n, m, a[N], f[2][N][205][2], t[N], ans, val, L;
inline void chkmin(int &x, int y){
    if(x > y) x = y;
}
inline void chkmax(int &x, int y){
    if(x < y) x = y;
}
int main(){
    // freopen("data.in", "r", stdin);
    // freopen("code.out", "w", stdout);
    memset(f, 0x3f, sizeof(f));
    scanf("%d%d", &n, &L);
    for(int i = n + 1; i <= n * 2; i++){
        scanf("%d", &a[i]);
    }
    for(int i = n + 1; i <= n * 2; i++){
        scanf("%d", &t[i]);
    }
    for(int i = n - 1; ~i; i--){
        a[i] = a[n + i + 1] - L;
        t[i] = t[n + i + 1];
    }
    // for(int i = 0; i <= 2 * n; i++){
    //     printf("%d %d\n", a[i], t[i]);
    // }
    m = 2 * n;
    f[0][n][0][0] = f[0][n][0][1] = 0;
    for(int i = 0; i < n; i++){
        for(int l = 0, r = l + i; l <= n; l++, r++){
            for(int j = 0, pos, nj; j <= n; j++){
                for(int p : {0, 1}){
                    if((val = f[0][l][j][p]) == inf) continue ;
                    pos = !p ? a[l] : a[r];
                    nj = j + (t[l - 1] >= val + pos - a[l - 1]);
                    chkmin(f[1][l - 1][nj][0], val + pos - a[l - 1]);
                    nj = j + (t[r + 1] >= val + a[r + 1] - pos);
                    chkmin(f[1][l][nj][1], val + a[r + 1] - pos);
                }
            }
        }
        for(int l = 0, r = i + 1; l <= n; l++, r++){
            for(int j = 0; j <= n; j++){
                for(int p : {0, 1}){
                    f[0][l][j][p] = f[1][l][j][p];
                    if(f[1][l][j][p] ^ inf){
                        chkmax(ans, j);
                        // printf("f[%d][%d][%d][%d] = %d\n", l, r, j, p, f[1][l][j][p]);
                    }
                    f[1][l][j][p] = inf;
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
```

---

