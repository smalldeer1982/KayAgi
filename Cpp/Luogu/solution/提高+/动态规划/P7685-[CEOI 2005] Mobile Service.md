# [CEOI 2005] Mobile Service

## 题目描述

一家公司为其位于不同城镇的合作伙伴提供服务。公司现有流动服务人员 $3$ 名。如果服务请求发生在某个位置，服务人员必须从他当前的位置移动到请求的位置（如果没有员工在那里）以满足请求。任何时候只有一名员工可以移动。他们只能应要求移动，并且不允许多名员工在同一位置。将员工从位置 $p$ 移动到位置 $q$ 会产生一定的成本 $C(p,q)$。成本计算不一定是对等的，但不动代价为 $0$，即 $C(p,p)=0$。公司必须以严格按照先请求先得服务的原则满足收到的要求。  
请您编写一个程序，该程序决定服务人员中的哪位员工要为每个请求移动，以便为给定的请求列表提供服务的总成本尽可能小。

## 说明/提示

#### 数据规模与约定  
对于 $100 \%$ 的数据，$3 \leq L \leq 200$，$1 \leq N \leq 1000$，$C(i,j) <2000$。  
#### 题目说明  
来源于 CENTRAL-EUROPEAN OLYMPIAD IN INFORMATICS 2005 的 Mobile  Service。  
由 @[求学的企鹅](/user/271784) 翻译整理。  
Special Judge 感谢 @[Cat_shao](/user/234011)。

## 样例 #1

### 输入

```
5 9
0 1 1 1 1
1 0 2 3 2
1 1 0 4 1
2 1 5 0 1
4 2 3 4 0
4 2 4 1 5 4 3 2 1```

### 输出

```
5
1 2 1 2 2 1 3 1 3 ```

# 题解

## 作者：lemondinosaur (赞：12)

[题目传送门](https://www.luogu.com.cn/problem/P7685)

---
自然想到设 $dp[i][x][y][z]$ 表示第 $i$ 次服务后三人所在的位置。

易证存在最优方案使得每次服务后三人所在位置互不相同。

考虑到有一个位置肯定为 $a_i$，那么将这一维舍去。

重新设方程就是 $dp[i][x][y]$ 表示第 $i$ 次服务后不在 $a_i$ 位置的剩下两个人所处位置分别为 $x,y$

若由 $dp[i-1][x][y]$ 转移到下一次服务。分三种情况讨论：

如果 $a_{i-1}$ 转移到 $a_i$，那么

$dp[i][x][y]=\min\left\{dp[i-1][x][y]+C[a_{i-1}][a_i]\right\}$

如果 $x$ 转移到 $a_i$，那么

$dp[i][a_{i-1}][y]=\min\left\{dp[i-1][x][y]+C[x][a_i]\right\}$

如果 $y$ 转移到 $a_i$，那么

$dp[i][x][a_{i-1}]=\min\left\{dp[i-1][x][y]+C[y][a_i]\right\}$

第二、三种情况会交换服务员的编号。

---
那如何输出方案呢？

交换编号和当前的 $x,y$ 都要记录，但是如果内存限制很小那就无能为力了。

如果每一次服务的 $x,y$ 都能知道，那么交换编号就可以正序遍历求出。

再看上面三种情况，第一种 $x,y$ 都没有改变。

第二种 $a_{i-1}$ 改变为 $x$，第三种 $a_{i-1}$ 改变为 $y$。

那么在第二种或第三种情况记录 $x$ 或 $y$。

如果被记录，就把 $a_{i-1}$ 替换成 $x$ 或 $y$。

为什么可以直接替换，因为 $x,y$ 相同不会使答案更优，

所以 $dp[i][a_{i-1}][a_{i-1}]$ 的情况可以被忽略掉。

然后记录下每次 $x,y$ 正序遍历出答案即可。

记录一个编号直接用 unsigned char 即可，内存为 42MB 左右。

---
```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
using namespace std;
const int N=1011,M=211; unsigned char pos[N][M][M];
int m,n,f[2][M][M],res[N],a[N],cost[M][M],X[N],Y[N];
int iut(){
    int ans=0; char c=getchar();
    while (!isdigit(c)) c=getchar();
    while (isdigit(c)) ans=ans*10+c-48,c=getchar();
    return ans;
}
int main(){
    m=iut(); n=iut();
    for (int i=1;i<=m;++i)
	for (int j=1;j<=m;++j) cost[i][j]=iut();
    memset(f[0],0x3f,sizeof(f[0]));
    f[0][1][2]=0,a[0]=3,X[0]=1,Y[0]=2;
    for (int i=1;i<=n;++i) a[i]=iut();
    for (int i=1;i<=n;++i){
    	memset(f[i&1],0x3f,sizeof(f[i&1]));
    	for (int j=1;j<=m;++j)
		for (int k=1;k<=m;++k) if (j!=k)
		if (f[(i&1)^1][j][k]<f[0][0][0]){
    	    if (j!=a[i]&&k!=a[i]){
    	 	    int t=f[(i&1)^1][j][k]+cost[a[i-1]][a[i]];
    		    if (f[i&1][j][k]>t)	f[i&1][j][k]=t,pos[i][j][k]=0;
		    }
		    if (a[i-1]!=a[i]&&k!=a[i]){
		    	int t=f[(i&1)^1][j][k]+cost[j][a[i]];
		    	if (f[i&1][a[i-1]][k]>t)
		    		f[i&1][a[i-1]][k]=t,pos[i][a[i-1]][k]=j;
			}
			if (a[i-1]!=a[i]&&j!=a[i]){
				int t=f[(i&1)^1][j][k]+cost[k][a[i]];
				if (f[i&1][j][a[i-1]]>t)
					f[i&1][j][a[i-1]]=t,pos[i][j][a[i-1]]=k;
			}
		}
	}
	int ans=f[0][0][0],mij,mik,F=1,G=2;
	for (int j=1;j<=m;++j)
	for (int k=1;k<=m;++k)
	if (j!=k&&f[n&1][j][k]<ans)
	    ans=f[n&1][j][k],mij=j,mik=k;
	printf("%d\n",ans);
	for (int i=n;i>=1;--i){
		int t=pos[i][mij][mik]; X[i]=mij,Y[i]=mik;
		if (t) (mik==a[i-1])?(mik=t):(mij=t);
	}
	for (int i=1;i<=n;++i){
		if (X[i]==a[i-1]) F=6-F-G;
		    else if (Y[i]==a[i-1]) G=6-F-G;
		printf("%d ",6-F-G);
	}
    return 0;
}
```

---

## 作者：Cat_shao (赞：11)

首先我建议大家先去完成一下这个题的[简化版](https://www.acwing.com/problem/content/276/)，其中这道题和简化版思路差不多。

本题解没有使用状压等技巧，非常朴素（~~因为笔者不会（~~

## 简化版

[链接](https://www.acwing.com/problem/content/276/)

这道题的简化版作为例题在李煜东的《算法竞赛进阶指南》上出现，无论是书还是李煜东的视频将得都非常明白，这里我再简单地提一下。

定义状态 `f[i][x][y][z]` 为解决了前 `i` 个需求，并且三个服务员的位置分别在 `x, y, z`。我们发现三个服务员必然又一个在 `a[i]` 上，所以可以省去一维，变成`f[i][x][y]`，其中 `x, y` 为不在 `a[i]` 上两个服务员的位置。


## 90pts的做法

这道题的难点在于只给了我们64MB的空间，使用计算器我们可知数组`f[1000][200][200]`将直接消耗掉100多MB的空间。这个题`f[i]`的转义只跟`f[i - 1]` 有关，所以我们可以用滚动数组，这样的话`f`数组只占用0.3MB。

记录路径时也可以用滚动数组，定义一个结点如下：

```cpp
class node {
public:
    node *prev;
    short pos[3]; // 服务员
};
```

我们只需要用指针记录下上一个状态，而不需要知道上一个状态确切的位置。

但是这个其实属于掩耳盗铃，使用的空间和开一个`[1000][200][200]`差不多。怎么办呢？我们可以考虑**先跑一次不记录路径，得到最小总成本，跑第二次时用最小总成本剪掉一些一定不行的情况**。


这样我们就得到了MLE2个点，90分的做法：
```cpp
//
// Created by Cat-shao on 2021/9/13.
//

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <climits>
#include <vector>
#include <queue>
using namespace std;

const int MAX_L = 210, MAX_N = 1010;

int l, n, graph[MAX_L][MAX_L], a[MAX_N], f[2][MAX_L][MAX_L], ans;

inline int c(int i, int j)
{
    return graph[i][j];
}

int basicMain()
{
    for (int j = 0; j < l + 2; ++j) {
        for (int k = 0; k < l + 2; ++k) {
            f[0][j][k] = INT_MAX;
        }
    }
    a[0] = 3;
    f[0][1][2] = 0;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < l + 2; ++j) {
            for (int k = 0; k < l + 2; ++k) {
                f[((i + 1) & 1)][j][k] = INT_MAX;
            }
        }
        for (int j = 1; j <= l; ++j) {
            for (int k = 1; k <= l; ++k) {
                if (f[(i & 1)][j][k] == INT_MAX) {
                    continue;
                }
                if (a[i] == j || a[i] == k || j == k) {
                    continue;
                }
                f[((i + 1) & 1)][j][k] = min(f[((i + 1) & 1)][j][k], f[(i & 1)][j][k] + c(a[i], a[i + 1]));
                f[((i + 1) & 1)][a[i]][k] = min(f[((i + 1) & 1)][a[i]][k], f[(i & 1)][j][k] + c(j, a[i + 1]));
                f[((i + 1) & 1)][j][a[i]] = min(f[((i + 1) & 1)][j][a[i]], f[(i & 1)][j][k] + c(k, a[i + 1]));
            }
        }
    }

    int minValue = INT_MAX;
    for (int j = 1; j <= l; ++j) {
        for (int k = 1; k <= l; ++k) {
            if (a[n] == j || a[n] == k || j == k) {
                continue;
            }
            minValue = min(minValue, f[(n & 1)][j][k]);
        }
    }
    return minValue;
}


class node {
public:
    node *prev;
    short pos[3]; // 服务员
};

const int MAX_MEM = 20 * MAX_N * MAX_L;

node memoryPool[MAX_MEM];
node *leastNode;

node *newNode(int p1, int p2, int p3, node *pr) {
    node *current;
    current = leastNode ++;
    current->prev = pr;
    current->pos[0] = p1;
    current->pos[1] = p2;
    current->pos[2] = p3;
}

void init() {
    scanf("%d%d", &l, &n);
    for (int i = 1; i <= l; ++i) {
        for (int j = 1; j <= l; ++j) {
            scanf("%d", &graph[i][j]);
        }
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    leastNode = memoryPool;
}

node *p[2][MAX_L][MAX_L];

void print(node *current, int i) {
    if (current == NULL || i == 0) {
        return;
    }
    print(current->prev, i - 1);
    if (a[i] == current->pos[0]) {
        printf("1 ");
    } else if (a[i] == current->pos[1]) {
        printf("2 ");
    } else {
        printf("3 ");
    }
}

int main()
{
    int temp;

    init();
    ans = basicMain();
    memset(f, 0, sizeof(f));
    for (int j = 0; j < l + 2; ++j) {
        for (int k = 0; k < l + 2; ++k) {
            f[0][j][k] = INT_MAX;
        }
    }
    memset(p, 0, sizeof(p));
    a[0] = 3;
    f[0][1][2] = 0;
    p[0][1][2] = newNode(1, 2, 3, NULL);
    for (int i = 0; i <= n; ++i) {
        if (i != 0) {
            for (int j = 1; j <= l; ++j) {
                for (int k = 1; k <= l; ++k) {
                    if (f[(i & 1)][j][k] == INT_MAX) {
                        continue;
                    }
                    if (f[(i & 1)][j][k] > ans) { // 剪掉
                        f[(i & 1)][j][k] = INT_MAX;
                        continue;
                    }
                    if (a[i] == j || a[i] == k || j == k) {
                        f[(i & 1)][j][k] = INT_MAX;
                        continue;
                    }
                    p[(i & 1)][j][k] = newNode(p[(i & 1)][j][k]->pos[0], p[(i & 1)][j][k]->pos[1], p[(i & 1)][j][k]->pos[2], p[(i & 1)][j][k]);
                    for (int x = 0; x < 3; ++x) {
                        if (!(p[(i & 1)][j][k]->pos[x] == j || p[(i & 1)][j][k]->pos[x] == k || p[(i & 1)][j][k]->pos[x] == a[i])) {
                            p[(i & 1)][j][k]->pos[x] = a[i];
                            break;
                        }
                    }
                }
            }
        }

//        for (int j = 1; j <= l; ++j) {
//            for (int k = 1; k <= l; ++k) {
//                if (p[(i & 1)][j][k] == NULL) {
//                    printf("NUL ");
//                } else {
//                    printf("%d ", f[(i & 1)][j][k]);
//                }
//            }
//            printf("\n");
//        }
//        printf("\n");

        for (int j = 0; j < l + 2; ++j) {
            for (int k = 0; k < l + 2; ++k) {
                f[((i + 1) & 1)][j][k] = INT_MAX;
                p[((i + 1) & 1)][j][k] = NULL;
            }
        }
        for (int j = 1; j <= l; ++j) {
            for (int k = 1; k <= l; ++k) {
                if (f[(i & 1)][j][k] == INT_MAX) {
                    continue;
                }
                if (a[i] == j || a[i] == k || j == k) {
                    continue;
                }
                temp = f[(i & 1)][j][k] + c(a[i], a[i + 1]);
                if (temp < f[((i + 1) & 1)][j][k]) {
                    f[((i + 1) & 1)][j][k] = temp;
                    p[((i + 1) & 1)][j][k] = p[(i & 1)][j][k];
                }

                temp = f[(i & 1)][j][k] + c(j, a[i + 1]);
                if (temp < f[((i + 1) & 1)][a[i]][k]) {
                    f[((i + 1) & 1)][a[i]][k] = temp;
                    p[((i + 1) & 1)][a[i]][k] = p[(i & 1)][j][k];
                }

                temp = f[(i & 1)][j][k] + c(k, a[i + 1]);
                if (temp < f[((i + 1) & 1)][j][a[i]]) {
                    f[((i + 1) & 1)][j][a[i]] = temp;
                    p[((i + 1) & 1)][j][a[i]] = p[(i & 1)][j][k];
                }
            }
        }
    }

    int minValue = INT_MAX;
    node *pOfMin = NULL;
    for (int j = 1; j <= l; ++j) {
        for (int k = 1; k <= l; ++k) {
            if (a[n] == j || a[n] == k || j == k) {
                continue;
            }
            if (minValue > f[(n & 1)][j][k]) {
                minValue = f[(n & 1)][j][k];
                pOfMin = p[(n & 1)][j][k];
            }
        }
    }
    printf("%d\n", minValue);
    print(pOfMin, n);
    return 0;
}
```


## 100pts 但不正确的做法

为什么会MLE呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/hkywaf9q.png)

例如上图，很多状态无用但是没有被剪到。

一个做法是定时重构，定期将所有结点拿出来然后撇掉没用的，但是笔者不会写（雾


另一种方式就是加大剪枝力度，我们可以在第一次跑的过程中记录下`f[i][][]`中的最小值，然后根据这个最小值剪。

```
if (f[(i & 1)][j][k] > min(ans[n], ans[i] + 10000)) { // 剪掉
    f[(i & 1)][j][k] = INT_MAX;
    continue;
}
```

可以使用 `ans[i] + 常数`，不能直接用`ans[i]`因为存在一些反例使得刚开始大到后来值就没什么变化。


```cpp
//
// Created by Cat-shao on 2021/9/13.
//

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <climits>
#include <vector>
#include <queue>
using namespace std;

const int MAX_L = 210, MAX_N = 1010;

int l, n, graph[MAX_L][MAX_L], a[MAX_N], f[2][MAX_L][MAX_L], ans[MAX_N];

inline int c(int i, int j)
{
    return graph[i][j];
}

int basicMain()
{
    for (int j = 0; j < l + 2; ++j) {
        for (int k = 0; k < l + 2; ++k) {
            f[0][j][k] = INT_MAX;
        }
    }
    a[0] = 3;
    f[0][1][2] = 0;
    for (int i = 0; i <= n; ++i) {
        int minValue = INT_MAX;
        for (int j = 1; j <= l; ++j) {
            for (int k = 1; k <= l; ++k) {
                if (a[i] == j || a[i] == k || j == k) {
                    continue;
                }
                minValue = min(minValue, f[(i & 1)][j][k]);
            }
        }
        ans[i] = minValue;
        for (int j = 0; j < l + 2; ++j) {
            for (int k = 0; k < l + 2; ++k) {
                f[((i + 1) & 1)][j][k] = INT_MAX;
            }
        }
        for (int j = 1; j <= l; ++j) {
            for (int k = 1; k <= l; ++k) {
                if (f[(i & 1)][j][k] == INT_MAX) {
                    continue;
                }
                if (a[i] == j || a[i] == k || j == k) {
                    continue;
                }
                f[((i + 1) & 1)][j][k] = min(f[((i + 1) & 1)][j][k], f[(i & 1)][j][k] + c(a[i], a[i + 1]));
                f[((i + 1) & 1)][a[i]][k] = min(f[((i + 1) & 1)][a[i]][k], f[(i & 1)][j][k] + c(j, a[i + 1]));
                f[((i + 1) & 1)][j][a[i]] = min(f[((i + 1) & 1)][j][a[i]], f[(i & 1)][j][k] + c(k, a[i + 1]));
            }
        }
    }
}


class node {
public:
    node *prev;
    short pos[3]; // 服务员
};

const int MAX_MEM = 20 * MAX_N * MAX_L;

node memoryPool[MAX_MEM];
node *leastNode;

node *newNode(int p1, int p2, int p3, node *pr) {
    node *current;
    current = leastNode ++;
    current->prev = pr;
    current->pos[0] = p1;
    current->pos[1] = p2;
    current->pos[2] = p3;
}

void init() {
    scanf("%d%d", &l, &n);
    for (int i = 1; i <= l; ++i) {
        for (int j = 1; j <= l; ++j) {
            scanf("%d", &graph[i][j]);
        }
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    leastNode = memoryPool;
}

node *p[2][MAX_L][MAX_L];

void print(node *current, int i) {
    if (current == NULL || i == 0) {
        return;
    }
    print(current->prev, i - 1);
    if (a[i] == current->pos[0]) {
        printf("1 ");
    } else if (a[i] == current->pos[1]) {
        printf("2 ");
    } else {
        printf("3 ");
    }
}

int main()
{
    int temp;

    init();
    basicMain();
    memset(f, 0, sizeof(f));
    for (int j = 0; j < l + 2; ++j) {
        for (int k = 0; k < l + 2; ++k) {
            f[0][j][k] = INT_MAX;
        }
    }
    memset(p, 0, sizeof(p));
    a[0] = 3;
    f[0][1][2] = 0;
    p[0][1][2] = newNode(1, 2, 3, NULL);
    for (int i = 0; i <= n; ++i) {
        if (i != 0) {
            for (int j = 1; j <= l; ++j) {
                for (int k = 1; k <= l; ++k) {
                    if (f[(i & 1)][j][k] == INT_MAX) {
                        continue;
                    }
                    if (f[(i & 1)][j][k] > min(ans[n], ans[i] + 10000)) { // 剪掉
                        f[(i & 1)][j][k] = INT_MAX;
                        continue;
                    }
                    if (a[i] == j || a[i] == k || j == k) {
                        f[(i & 1)][j][k] = INT_MAX;
                        continue;
                    }
                    p[(i & 1)][j][k] = newNode(p[(i & 1)][j][k]->pos[0], p[(i & 1)][j][k]->pos[1], p[(i & 1)][j][k]->pos[2], p[(i & 1)][j][k]);
                    for (int x = 0; x < 3; ++x) {
                        if (!(p[(i & 1)][j][k]->pos[x] == j || p[(i & 1)][j][k]->pos[x] == k || p[(i & 1)][j][k]->pos[x] == a[i])) {
                            p[(i & 1)][j][k]->pos[x] = a[i];
                            break;
                        }
                    }
                }
            }
        }

//        for (int j = 1; j <= l; ++j) {
//            for (int k = 1; k <= l; ++k) {
//                if (p[(i & 1)][j][k] == NULL) {
//                    printf("NUL ");
//                } else {
//                    printf("%d ", f[(i & 1)][j][k]);
//                }
//            }
//            printf("\n");
//        }
//        printf("\n");

        for (int j = 0; j < l + 2; ++j) {
            for (int k = 0; k < l + 2; ++k) {
                f[((i + 1) & 1)][j][k] = INT_MAX;
                p[((i + 1) & 1)][j][k] = NULL;
            }
        }
        for (int j = 1; j <= l; ++j) {
            for (int k = 1; k <= l; ++k) {
                if (f[(i & 1)][j][k] == INT_MAX) {
                    continue;
                }
                if (a[i] == j || a[i] == k || j == k) {
                    continue;
                }
                temp = f[(i & 1)][j][k] + c(a[i], a[i + 1]);
                if (temp < f[((i + 1) & 1)][j][k]) {
                    f[((i + 1) & 1)][j][k] = temp;
                    p[((i + 1) & 1)][j][k] = p[(i & 1)][j][k];
                }

                temp = f[(i & 1)][j][k] + c(j, a[i + 1]);
                if (temp < f[((i + 1) & 1)][a[i]][k]) {
                    f[((i + 1) & 1)][a[i]][k] = temp;
                    p[((i + 1) & 1)][a[i]][k] = p[(i & 1)][j][k];
                }

                temp = f[(i & 1)][j][k] + c(k, a[i + 1]);
                if (temp < f[((i + 1) & 1)][j][a[i]]) {
                    f[((i + 1) & 1)][j][a[i]] = temp;
                    p[((i + 1) & 1)][j][a[i]] = p[(i & 1)][j][k];
                }
            }
        }
    }

    int minValue = INT_MAX;
    node *pOfMin = NULL;
    for (int j = 1; j <= l; ++j) {
        for (int k = 1; k <= l; ++k) {
            if (a[n] == j || a[n] == k || j == k) {
                continue;
            }
            if (minValue > f[(n & 1)][j][k]) {
                minValue = f[(n & 1)][j][k];
                pOfMin = p[(n & 1)][j][k];
            }
        }
    }
    printf("%d\n", minValue);
    print(pOfMin, n);
    return 0;
}
```

--------------------------

这道题在有SPJ之前很难AC，因为会存在多种情况。因为供题者采用了CEOI2005的数据而且没有自己造数据所以可以在网上找到[这道题的全部数据](http://ceoi.inf.elte.hu/ceoi2005/download/tests/servicetest.zip)，大家可以对照数据来调调自己的程序。


---

## 作者：spider_oyster (赞：5)

~~一道蓝题竟然应为输出路径调到了黑？是什么样的毒瘤题卡空间？究竟是人性的扭曲还是道德的沦丧？~~

## 状态设计和状态转移

请求是线性的，又和三个服务人员的位置有关，一个直接的想法是定义状态 $f_{i,j,k,l}$ 为考虑到了第 $i$ 个请求，一号，二号，三号服务人员分别在 $j,k,l$ 位置时的最小成本。然而这时候时间复杂度是 $O(nL^3)$ 的，直接爆炸。

进一步考虑优化，我们发现完成第 $i$ 个请求后，去完成这个服务的人员必定在$p_{i}$ 这个位置上，于是我们只需记录剩余两个服务员的位置即可。故状态为 $f_{i,j,k}$。

接下来考虑转移。首先根据题意，不允许多名员工在同一位置，所以当有两个员工在同一位置时候，我们直接跳过。对于当前请求，我们有三种情况：移动 $j$ 或 $k$ 或 $p_{i-1}$，于是得状态转移方程：

$f_{i,j,k}=min(f_{i,j,k},f_{i-1,j,k}+c_{p_{i-1},p_{i}})$，此时移动 $p_{i-1}$ 到 $p_{i}$。

$f_{i,p_{i-1},k}=min(f_{i,p_{i-1},k},f_{i-1,j,k}+c_{j,p_{i}})$，此时移动 $j$ 到 $p_{i}$。 

$f_{i,j,p_{i-1}}=min(f_{i,j,p_{i-1}},f_{i-1,j,k}+c_{k,p_{i}})$，此时移动 $k$ 到 $p_{i}$。

初始我们默认 $f_{0,1,2}=0,p_{0}=3$。最终 $ans=minf_{n,j,k}$。

于是这道题的 $dp$ 部分就完成了！

## 记载路径和优化空间

**这才是本题最难的部分。**

当你记完路径提交上这道（简单）的黑题，发现：哇，MLE了！

对于 $dp$ 部分，很显然可以用滚动数组优化空间。我用的是异或来滚动。$0 xor 1=1,1xor1=0$。据此，我们记一个变量 $t$ ，每滚动一次 $t$ 异或 $1$，这样就实现滚动了。

然后输出路径，最朴素的是开 $path_{i,j,k}$ 数组记录当前三个员工位置。此时空间为 $456MB$ ，直接爆炸。

接着我考虑：可以将三个 $int$ 压缩为一个 $int$ 来记录，现在空间来到了 $154MB$。

可这样内存还是爆炸，我们思考是否可以只记录一个员工的信息，从而推出其他信息。因为 $3\leq L \leq200$，我们用 $unsigned$ $char$ 来记录，内存为 $38MB$ 左右，不会爆炸，但多开一点就会爆炸。

我们假设三个员工 $x,y,z$，他们始终是 $z$ 在服务。首先他们编号之和是 $6$，则 $z=6-x-y$，如果 $x$ 去服务了，$x$ 就变成了 $z$，而 $z$ 变成了 $x$，$x=6-x-y$；$y$ 则同理，如果 $y$ 去服务了，$y=6-x-y$。这样，我们就用了一个很骚的 $trick$ 简化了路径。

一开始，我们默认是 $x=1,y=2,z=3$，也就是之前初始化 $f_{0,1,2}=0,p_{0}=3$，对于每一次转移，我们记录它之前的 $j$ 或 $k$，也就是记录 $x$ 或者 $y$ 是否发生变化。

对于 $f_{i,j,k}=min(f_{i,j,k},f_{i-1,j,k}+c_{p_{i-1},p_{i}})$ 的转移，记录为 $path_{i,j,k}=0$，因为此时服务的人员没有变化。

对于 $f_{i,p_{i-1},k}=min(f_{i,p_{i-1},k},f_{i-1,j,k}+c_{j,p_{i}})$ 的转移，记录为 $path_{i,p_{i-1},k}=j$，因为此时是 $j$ 去服务，$x$ 发生变化，而我们也同样记录了 $f_{i,p_{i-1},k}$ 是从 $f_{i-1,j,k}$ 转移过来的。

对于 $f_{i,j,p_{i-1}}$ 同理。

记录了 $path$，我们从 $ans$ 出发逆序推出 $x_{i},y_{i}$，也就是第 $i$ 次 $x,y$ 的变化情况。正序输出时，我们判断其中一个是否等于 $p_{i-1}$，便得知 $x,y$ 的变化情况。

------------
附上当前最优解：

```cpp
#include<bits/stdc++.h>
#define F(i,s,t) for(register int i=(s);i<=(t);++i) 
#define R(i,s,t) for(register int i=(s);i>=(t);--i)
#define ll long long
using namespace std;

const int N=201;
const int INF=0x3f3f3f3f;
int n,L,pre,now;
int p[1001],f[2][N][N],c[N][N],x[1001],y[1001];
unsigned char path[1001][N][N];

inline int read()
{
	int x=0;char c=getchar();
	for(;!isdigit(c);c=getchar());
	for(; isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	return x;
}

int main()
{
	L=read(),n=read();
	F(i,1,L) F(j,1,L) c[i][j]=read();
	F(i,1,n) p[i]=read();
	F(i,0,L) F(j,0,L) f[0][i][j]=INF;
	f[0][1][2]=0,p[0]=3;
	int t=0;
	F(i,1,n)
	{
		t^=1;
		pre=p[i-1],now=p[i];
		F(j,0,L) F(k,0,L) f[t][j][k]=INF;//滚动数组每滚动一次初始化一次 
		F(j,1,L) F(k,1,L)
		{
			//去掉非法情况 
			if(j==pre||k==pre||j==k||f[t^1][j][k]==INF) continue;
			int y=f[t^1][j][k],x;
			x=y+c[pre][now];
			if(x<f[t][j][k])
			{
				f[t][j][k]=x;
				path[i][j][k]=0;
			}
			x=y+c[j][now];
			if(x<f[t][pre][k])
			{
				f[t][pre][k]=x;
				path[i][pre][k]=j;
			}
			x=y+c[k][now];
			if(x<f[t][j][pre])
			{
				f[t][j][pre]=x;
				path[i][j][pre]=k;
			}
		}
	}
	int ans=1e9,nowj,nowk,fir=1,sec=2; 
	F(j,1,L) F(k,1,L) if(j!=k&&f[t][j][k]<ans) ans=f[t][j][k],nowj=j,nowk=k;
	printf("%d\n",ans);
	R(i,n,1)
	{
		//path=0,j,k不变化
		//f[i][p[i-1]][k]=min(f[i-1][j][k]),nowj=p[i-1],下一次nowj=j=path[i][p[i-1]][k] 
		//f[i][j][p[i-1]]=min(f[i-1][j][k]),nowk=p[i-1],下一次nowk=k=path[i][j][p[i-1]] 
		int tmp=path[i][nowj][nowk];
		x[i]=nowj,y[i]=nowk;
		if(tmp) (nowj==p[i-1])?(nowj=tmp):(nowk=tmp);
	}
	F(i,1,n)
	{
		//x 变化了,x=6-x-y 
		if(x[i]==p[i-1]) fir=6-fir-sec;
		//y 变化了,y=6-x-y 
		else if(y[i]==p[i-1]) sec=6-fir-sec; 
		///输出我们定义始终在服务的 z=6-x-y 
		printf("%d ",6-fir-sec);
	}
	return 0;
}
```


---

## 作者：linyuhuai (赞：4)

upd:2023/06/30：完善文章内容。

没做过的建议先做 [SP703](https://www.luogu.com.cn/problem/solution/SP703)。此题与 [P7685](https://www.luogu.com.cn/problem/P7685) 总体思路基本一致。

考虑从 DP 入手，设当前已经处理过的服务数量为 $i-1$，发现一定有一个人处于 $a_{i-1}$ 位置，设另外 $2$ 个员工的位置分别为 $x,y$，则推出转移方程：

$$f[i][x][y]=\min(f[i-1][x][y]+C(a[i-1],a[i]))$$

$$f[i][x][a[i-1]]=\min(f[i-1][x][y]+C(y,a[i]))$$

$$f[i][a[i-1]][y]=\min(f[i-1][x][y]+C(x,a[i]))$$ 

发现我们只需要知道 $f[i-1]$ 所存的数，并不关心 $f[i-2]$ 之前存的数字，因此我们可以采用滚动数组的方式来存储数组。

以上 DP 求解最小成本。

在转移 DP 的时候，因为滚动数组的存在导致数据的丢失，无法更好的求出每个点所服务的服务员是哪位。


遇到这种情况，我们需要记录下来每个状态的“最优解”是从何处转移而来的。最终，求出最优解后，用过一次递归，沿着记录的每一步“转移来源”回到初态，即可得出答案。


我们发现每次转移 DP 时数组所差别的数据有三种情况，分别为：

- $y$ 变为 $a_{i-1},y$ 进入 dp 隐藏维度；
- $x$ 变为 $a_{i-1},x$ 进入 dp 隐藏维度；
- 不变；

于是可以把这些进入 DP 隐藏维度的服务员前一个状态存下来。DP 结束后，根据所存储的数字进行反推。

设 $path$ 为 DP 在相应状态时存储下来的隐藏维度的服务员服务的前一个位置，但当那个服务员之前服务的位置是 $a_{i-1}$ 时，则说明那个隐藏维度的服务员的编号不变，所以将 $path$ 再改为 $0$ （便于后期回溯）。$mx,my$ 初始值为答案所在数组的二三维。



```cpp
for(int i=n; i>=1; i--) {
	x_[i]=mx,y_[i]=my;
	if(path[i][mx][my])a[i-1]==mx?mx=path[i][mx][my]:my=path[i][mx][my];
}
 ```
 
不难发现，$3$ 个服务员一定有一个服务员的位置在 $a_{i-1}$，DP 机制使得 $a_{i}$ 一直处于隐藏维度。倒推回去时，如果发现 $mx$ 或 $ my$ 是 $a_{i-1}$ 则说明 $mx$ 或 $my$ 在 $i-1$ 状态时是处于隐藏维度的，再根据 $path$ 倒推回去即可。


遍历结束后再来一次正序遍历即可求出答案。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define debug puts("sto Cbrx orz");
#define MAX_L 201
#define MAX_N 1001
const int INF = 0x7fffffff;

using namespace std;
int f[2][MAX_L][MAX_L];
int a[MAX_N],c[MAX_L][MAX_L],l,n,ans,X[MAX_N],Y[MAX_N];
unsigned char path[MAX_N][MAX_L][MAX_L];

int C(int x,int y);
void clean(int i);

int main() {
	scanf("%d%d",&l,&n);
	for(int i=1; i<=l; i++) {
		for(int k=1; k<=l; k++) {
			scanf("%d",&c[i][k]);
		}
	}

	for(int x=0; x<=l; x++)
		for(int y=0; y<=l; y++)
			f[0][x][y]=0x3f3f3f3f;

	a[0]=3,f[0][1][2]=0,X[0]=1,Y[0]=2;

	for(int i=1; i<=n; i++)scanf("%d",&a[i]);

	for(int i=1; i<=n; i++) {
		clean(i);
		for(int x=1; x<=l; x++) {
			for(int y=1; y<=l; y++) {
				if(f[i&1^1][x][y]!=0x3f3f3f3f&&x!=y) {
					int z=a[i-1];
					if(x!=a[i]&&y!=a[i]) {
						if(f[i&1][x][y]>f[i&1^1][x][y]+C(z,a[i])) {
							f[i&1][x][y]=f[i&1^1][x][y]+C(z,a[i]),path[i][x][y]=0;
						}
					}
					if(x!=a[i]&&z!=a[i]) {
						if(f[i&1][x][z]>f[i&1^1][x][y]+C(y,a[i])) {
							f[i&1][x][z]=f[i&1^1][x][y]+C(y,a[i]),path[i][x][z]=y;
						}
					}
					if(y!=a[i]&&z!=a[i]) {
						if(f[i&1][z][y]>f[i&1^1][x][y]+C(x,a[i])) {
							f[i&1][z][y]=f[i&1^1][x][y]+C(x,a[i]),path[i][z][y]=x;//z要放在第一个，不能放在第二个，因为z是代替x的。 
						}
					}
				}
			}
		}
	}
	ans=0x7fffffff;
	int mx,my;
	for(int x=1; x<=l; x++) {
		for(int y=1; y<=l; y++) {
			if(f[n&1][x][y]<ans)mx=x,my=y,ans=f[n&1][x][y];
		}
	}
	a[0]=3;
	printf("%d\n",ans);
	for(int i=n; i>=1; i--) {
		X[i]=mx,Y[i]=my;//一定有一个等于a_{i-1}的
		//printf("%d %d\n",mx,my);
		if(path[i][mx][my])(a[i-1]==mx)?(mx=path[i][mx][my]):(my=path[i][mx][my]);
	}
	int num_x=1,num_y=2;
	for(int i=1;i<=n;i++){
		if(X[i]==a[i-1])num_x= num_x==1?(num_y==2?3:2):(num_x==2?(num_y==3?1:3):(num_y==1?2:1));//因为x[i]==a[i-1]所以X[i]会被转移到f数组隐藏的那个纬度。 
		else if(Y[i]==a[i-1])num_y= num_x==1?(num_y==2?3:2):(num_x==2?(num_y==3?1:3):(num_y==1?2:1));
		printf("%d ",num_x==1?(num_y==2?3:2):(num_x==2?(num_y==3?1:3):(num_y==1?2:1)));
	} 
}
int C(int x,int y) {
	return c[x][y];
}
void clean(int i) {
	for(int k=0; k<=l; k++) {
		for(int j=0; j<=l; j++) {
			f[i&1][k][j]=0x3f3f3f3f;
		}
	}
}
```

---

## 作者：Kelier_pkl (赞：3)

## 题意

在一个有 $L$ 个位置有 $3$ 个员工，他们的起始位置分别为 $1,2,3$。员工从位置 $p$ 移动到位置 $q$ 会产生一定成本 $C(p,q)$。

现在有 $N$ 个请求，每一个请求必须要派出一个人到请求的位置。

求最小的成本以及方案。

## 问题解决

#### 最小成本：

同[SP703](https://www.luogu.com.cn/problem/SP703)，我们可以用 DP 来做。

- 阶段的划分：

	已经完成的请求数量。

- 状态的表示（最朴素的想法）：
	
	$dp_{i,x,y,z}$ 表示完成前 $i$ 个请求三个员工分别位于 $x,y,z$。
    
- 状态的转移（最朴素的想法）：

	```cpp
	dp[i][ask[i]][y][z]=min(dp[i][ask[i]][y][z],dp[i-1][x][y][z]+c[x][ask[i]])
	dp[i][x][ask[i]][z]=min(dp[i][x][ask[i]][z],dp[i-1][x][y][z]+c[y][ask[i]])
	dp[i][x][y][ask[i]]=min(dp[i][x][y][ask[i]],dp[i-1][x][y][z]+c[z][ask[i]])
	```

另外有一点要注意：一个位置不能同时出现两个员工。

草草的算一下复杂度：

1. 时间复杂程度：$O(N \times L^3)$。

2. 空间复杂程度：$1000 \times 200^3$。

那么接下来就是优化：

我们再仔细看看题目，可以知道在完成前 $i$ 个请求的时候，一定有一个员工在 $ask_i$，所以我们只需要表示另外两个员工的位置。

- 阶段的划分

	已经完成的请求数量。
    
- 状态的表示（优化）：

	$dp_{i,x,y}$ 表示完成前 $i$ 个请求后，另外两个员工分别位于 $x,y$。
    
- 状态的转移（优化）：

	```cpp
	dp[i][x][y]=min(dp[i][x][y],dp[i-1][x][y]+c[ask[i-1]][ask[i]]);
	dp[i][ask[i-1]][y]=min(dp[i][ask[i-1]][y],dp[i-1][x][y]+c[x][ask[i]]);
	dp[i][x][ask[i-1]]=min(dp[i][x][ask[i-1]],dp[i-1][x][y]+c[y][ask[i]]);
	```

- 边界条件：
	
	```cpp
	ask[i]=3
	dp[0][1][2]=0
	```

- 目标：

	`dp[n][?][?]`

#### 方案：

分析：我们在状态转移后会取最优解，然而方案也是基于最优解之上的，所以我们可以在状态转移的时候对方案进行一些操作。

如果每一次服务的 $x,y$ 都能知道，那么交换编号就可以正序遍历求出。

接着我们来看一下三种状态转移对 $x,y$ 的影响：

1. 第一种：$x,y$ 都没有变。

2. 第二种：$ask_{i-1}$ 变为 $x$。

3. 第三种：$ask_{i-1}$ 变为 $y$。

那么我们只需要在第二种和第三种情况下记录 $x,y$。

如果被记录的话:

1. 把 $ask_{i-1}$ 替换成 $x$。

2. 把 $ask_{i-1}$ 替换成 $y$。

如果 $x,y$ 相同的话，$dp_{i,x,y}$ 不会使答案更优，所以我们就不用特判 $x=y$ 的情况了。

另外，我们还可以用滚动数组优化一下代码。

## Code

```cpp
//the code is from pkl
#include <bits/stdc++.h>
using namespace std;
#define MAXN 1005
#define MAXL 205
int m,n,ans=INT_MAX;
int xx,yy;//表示2个员工在最优解完成最后一次请求的位置 
int ax=1,ay=2;
int ask[MAXN],c[MAXL][MAXL];
int px[MAXN],py[MAXN];//表示2个员工完成第i个请求后的位置
unsigned char pos[MAXN][MAXL][MAXL];//表示第i次请求后，另外一个员工的位置 
int dp[2][MAXL][MAXL];
int main(){
    scanf("%d%d",&m,&n);
    for (int i=1;i<=m;i++){
    	for (int j=1;j<=m;j++){
			scanf("%d",&c[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&ask[i]);
	}
    memset(dp[0],0x3f,sizeof(dp[0]));
    ask[0]=3;
	px[0]=1,py[0]=2;//表示2个员工的初始位置
	dp[0][1][2]=0;
    for(int i=1;i<=n;++i){
    	memset(dp[i&1],0x3f,sizeof(dp[i&1]));//滚动数组初始化 
    	for(int x=1;x<=m;x++){
    		for(int y=1;y<=m;y++){
    			if (x!=y){
					if(dp[(i&1)^1][x][y]<dp[0][0][0]){//第一种状态转移 
    	    			if(x!=ask[i]&&y!=ask[i]){
							int t=dp[(i&1)^1][x][y]+c[ask[i-1]][ask[i]];
    		    			if (dp[i&1][x][y]>t){
    		    				dp[i&1][x][y]=t;
								pos[i][x][y]=0;
							}
		    			}
		    			if(ask[i]!=ask[i-1]&&y!=ask[i]){//第二种状态转移 
		    				int t=dp[(i&1)^1][x][y]+c[x][ask[i]];
		    				if(dp[i&1][ask[i-1]][y]>t){
		    					dp[i&1][ask[i-1]][y]=t;
								pos[i][ask[i-1]][y]=x;
							}
						}
						if(ask[i]!=ask[i-1]&&x!=ask[i]){//第三种状态转移 
							int t=dp[(i&1)^1][x][y]+c[y][ask[i]];
							if (dp[i&1][x][ask[i-1]]>t){
								dp[i&1][x][ask[i-1]]=t;
								pos[i][x][ask[i-1]]=y;
							}	
						}
					}
				}
			}
		}
	}
	for(int i=1;i<=m;i++){
		for (int j=1;j<=m;j++){
			if (i!=j&&dp[n&1][i][j]<ans){//ans取最大值 
				ans=dp[n&1][i][j];
				xx=i,yy=j;
			}
		}
	}
	printf("%d\n",ans);
	for(int i=n;i>=1;i--){
		int t=pos[i][xx][yy];
		px[i]=xx,py[i]=yy;
		if(t){
			(yy==ask[i-1])?(yy=t):(xx=t);
		}
	}
	for(int i=1;i<=n;i++){//对员工标识符进行转换 
		if(px[i]==ask[i-1]){
			ax=6-ax-ay;
		} 
		if(py[i]==ask[i-1]){
			ay=6-ax-ay;
		}
		printf("%d ",6-ax-ay);
	}
}
```

---

## 作者：Petit_Souris (赞：2)

截至题解发布时，本题解代码空间优于所有非完隐提交（最大消耗 7.05MB），空间复杂度优于所有现有题解。

dp 是简单的：首先暴力是 $\mathcal O(LN^3)$ 的，记录三个人目前的位置。进一步发现一定有一个人在当前需要服务的点上，所以实际上是 $\mathcal O(LN^2)$ 的。但是题目要求输出转移路径，这导致我们如果直接记录 $\mathcal O(LN^2)$ 个转移空间可能会不够用。其他题解采用的方法是利用 $N\le 200$，使用 `unsigned char` 记录，这里介绍一种更优的方法。

我们发现，我们实际上只关心每层转移路径中的一个点。由于第 $i$ 层的转移路径只和第 $i-1$ 层的 dp 值有关，于是我们想到可以把 dp 值全都记下来，这样记录路径就不需要太多空间了。然而把 dp 值全都记下来的空间复杂度也是 $\mathcal O(LN^2)$。

这时候你突然意识到，我们能不能记录一部分 dp 值，剩下的等到要用的时候再计算出来，算完转移路径之后直接当场扔掉？

考虑分块，每 $B$ 层转移分一块。做两次 dp，第一次 dp 求出最优解，并记录 $B,2B,\dots $ 处的 dp 数组。第二遍 dp 整体倒过来做，每个块内正着做，记录块内每层的转移路径，倒过来构造。时间复杂度还是 $\mathcal O(LN^2)$（因为每层依旧只转移一次），空间复杂度为 $\mathcal O(BN^2+\frac{L}{B}N^2)$，取 $B=\sqrt L$ 得到 $\mathcal O(\sqrt LN^2)$，这样即使所有变量全都开 `long long` 都可以通过。

实际上 dp 数组可以开 `int`，转移路径数组可以开 `unsigned char`，最终大概可以压到 7MB。~~建议把空间限制缩小到 8MB。~~

```cpp
#include<bits/stdc++.h>
typedef int ll;
using namespace std;
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
bool Mbe;
ll read(){
	char ch=getchar();ll x=0,f=1;
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return x*f;
}
void write(ll x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
const ll N=202,B=33,INF=1e9;
ll n,L,dp[2][N][N],cur,mid[B][N][N];
short C[N][N];
unsigned char a[N*5],trans[B][N][N],X[N*5],Y[N*5];
bool Med;
int main(){
	cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
	n=read(),L=read();
	rep(i,1,n){
		rep(j,1,n)C[i][j]=read();
	}
	rep(i,0,1){
		rep(j,1,n){
			rep(k,1,n)dp[i][j][k]=mid[0][j][k]=INF;
		}
	}
	rep(i,1,L)a[i]=read();
	a[0]=3;
	dp[0][1][2]=0;
	mid[0][1][2]=0;
	rep(i,1,L){
		rep(j,1,n){
			rep(k,1,n)dp[cur^1][j][k]=INF;
		}
		rep(j,1,n){
			rep(k,1,n){
				if(j==k)continue;
				if(dp[cur][j][k]==INF)continue;
				ll lst=a[i-1],v=dp[cur][j][k];
				if(j!=a[i]&&k!=a[i])dp[cur^1][j][k]=min(dp[cur^1][j][k],v+C[lst][a[i]]);
				if(lst!=a[i]&&k!=a[i])dp[cur^1][lst][k]=min(dp[cur^1][lst][k],v+C[j][a[i]]);
				if(lst!=a[i]&&j!=a[i])dp[cur^1][j][lst]=min(dp[cur^1][j][lst],v+C[k][a[i]]);
			}
		}
		cur^=1;
		if(!(i&31)){
			rep(j,1,n){
				rep(k,1,n)mid[i>>5][j][k]=dp[cur][j][k];
			}
		}
	}
	ll bj=1,bk=2,ans=INF;
	rep(j,1,n){
		rep(k,1,n){
			if(j!=k&&dp[cur][j][k]<ans){
				ans=dp[cur][j][k];
				bj=j,bk=k;
			}
		}
	}
	write(ans),putchar('\n');
	per(blk,(L>>5),0){
		ll pl=blk<<5,pr=min(pl+32,L);
		rep(i,0,1){
			rep(j,1,n){
				rep(k,1,n)dp[i][j][k]=INF;
			}
		}
		rep(j,1,n){
			rep(k,1,n)dp[0][j][k]=mid[blk][j][k];
		}
		cur=0;
		rep(i,pl+1,pr){
			rep(j,1,n){
				rep(k,1,n)dp[cur^1][j][k]=INF;
			}
			rep(j,1,n){
				rep(k,1,n){
					if(j==k)continue;
					if(dp[cur][j][k]==INF)continue;
					ll lst=a[i-1],v=dp[cur][j][k];
					if(j!=a[i]&&k!=a[i]){
						if(dp[cur^1][j][k]>v+C[lst][a[i]]){
							dp[cur^1][j][k]=v+C[lst][a[i]];
							trans[i-pl][j][k]=0;
						}
					}
					if(lst!=a[i]&&k!=a[i]){
						if(dp[cur^1][lst][k]>v+C[j][a[i]]){
							dp[cur^1][lst][k]=v+C[j][a[i]];
							trans[i-pl][lst][k]=j;
						}
					}
					if(lst!=a[i]&&j!=a[i]){
						if(dp[cur^1][j][lst]>v+C[k][a[i]]){
							dp[cur^1][j][lst]=v+C[k][a[i]];
							trans[i-pl][j][lst]=k;
						}
					}
				}
			}
			cur^=1;
		}
		per(i,pr,pl+1){
			ll tr=trans[i-pl][bj][bk];
			X[i]=bj,Y[i]=bk;
			if(tr){
				if(bk==a[i-1])bk=tr;
				else bj=tr;
			}
		}
	}
	ll u=1,v=2;
	rep(i,1,L){
		if(X[i]==a[i-1])u=6-u-v;
		else if(Y[i]==a[i-1])v=6-u-v;
		write(6-u-v),putchar(' ');
	}
	cerr<<clock()*1.0/CLOCKS_PER_SEC<<"ms\n";
	return 0;
}
```

---

## 作者：233L (赞：2)

题目中的 $L$ 记作 $n$，$N$ 记作 $m$，$C(i,j)$ 记作 $a_{i,j}$，请求列表记作 $b_i$。

## Task1 求最小花费


[SP703](https://www.luogu.com.cn/problem/SP703) 就是这个问题。（可以发现它只是蓝）

最朴素的想法，记 $f_{i,u,v,w}$ 表示考虑到第 $i$ 个请求，3 个服务员的位置分别是 $u,v,w$（根据题意，$u,v,w$ **互不相同**）的最小成本。

注意到时空限制 ```3s,64MB```，直接开肯定不行，需要压维。$i$ 这一维可以用滚动数组压掉（但是下文中为了方便，我会用一般的方法表示）。接着注意到 $u,v,w$ 中有且仅有一个元素与 $b_i$ 相等，知道的东西就不用存了，所以再压掉一维。

进化后的状态：$f_{i,u,v}$ 表示考虑到第 $i$ 个请求，$1$ 个服务员在 $b_i$，另外两个服务员的位置分别为 $u,v$，此时的最小成本。所用的空间是 $2 \times 200 \times 200 \times 4 \div 1024 \div 1024 \approx 0$ MB。~~真就忽略不计~~

考虑从 $i$ 往 $i+1$ 转移。（不是正规的转移方程ww）下文的“更新”就是取 $\min$。

**情况1**：如果 $b_{i+1}$ 是 $b_i,u,v$ 中的其中一个，这意味着我们不用动。(也不能动）

当 $b_{i+1}=b_i$ 时，$f_{i,u,v}$ 更新 $f_{i+1,u,v}$。

当 $b_{i+1}=u$ 时，$f_{i,u,v}$ 更新 $f_{i+1,b_i,v}$。注意到被我们藏起来的维度发生了变化，$b_i$ 现身了，原来的 $u$ 变成 $b_{i+1}$ 且隐身了。

当 $b_{i+1}=v$ 时，同理。

**情况2**：反之，从$b_i,u,v$ 中的任意一个走到 $b_{i+1}$。

从 $b_i$ 走到 $b_{i+1}$：$f_{i,u,v}+a_{b_i,b_{i+1}}$ 更新 $f_{i+1,u,v}$。

从 $u$ 走到 $b_{i+1}$：$f_{i,u,v}+a_{u,b_{i+1}}$ 更新 $f_{i+1,b_{i},v}$。这里同样经历了现身和隐身。

从 $v$ 走到 $b_{i+1}$：同理。（$v$：是我不配）

最后对 $f_m,u,v$ 枚举 $u,v$ 取 $\min$ 即可。滚动过程中记得初始化。最开始的初始化可以是 $f_{0,2,3}=0$，其他都是 $+\infty$。

## Task2 求出任意一种方案

一般来说，通过辅助数组一步步往前回溯，途中记下方案再倒序输出就解决了。~~于是就切了这道黑题~~

但是别忘了空间限制！辅助数组不能用滚动数组压维，如果直接开数组妥妥的 ```MLE```。这题的难点也就在这。

回顾前面的转移过程，一种情况是 $u,v$ 都不变，另一种是 $u,v$ 其中一个变成 $b_i$。在第二种情况中，因为 $b_i$ 覆盖导致丢失了信息，我们只需要记录这个 $b_i$ 所覆盖的 $u$ 或 $v$，就能一步步往前回溯了。

记 $g_{i,u,v}$ 为转移到这个状态所丢失的信息（若没有，则为 $0$）。空间问题呢？注意到 $u,v \in[1,200]$，一个字节就可以存下，所以用 ```unsigned char``` 存储 ```g``` 数组，所用的空间是 $1000 \times 200 \times 200 \div 1024 \div 1024 \approx 38$ MB，刚刚好。

记最后成为 $ans$ 的状态为 $f_{m,u,v}$，那么这三个服务员的位置就是 $b_m,u,v$，如果 $u=b_{m-1}$，就令 $u'=g_{m,u,v}$，于是就回溯到了前一个状态 $f_{m-1,u',v}$。$v$ 同理。

我们实现了回溯，但是方案呢？记 $c_1,c_2,c_3$ 分别是隐藏位（一开始是 $b_m$），$u$ 维度，$v$ 维度对应的服务员的编号。
不妨先钦定 $c_1=1,c_2=2,c_3=3$，如果 $u=b_{m-1}$，那么交换 $c_1,c_2$（根据前面的现身隐身带来的位置交换）；如果 $v=b_{m-1}$，那么交换 $c_1,c_3$（如果都不满足就啥都不用干）。每次将 $c_1$ 加入答案栈，再进行上面的交换。

~~这样就做好了~~ 我们一开始任意钦定了服务员的编号，所以方案不一定是正确的，可能需要进行映射（例如 $1$ 都变成 $2,2$ 都变成 $1$）。假如最后的 $c$ 数组恰好就是 $\{1,2,3\}$，那么就已经满足了要求。（因为初始化时 $f_{0,2,3}=0,b_0=1$，对应的就是 $\{1,2,3\}$）如果不是呢？假如 $c$ 数组是 $\{2,3,1\}$ 呢？这意味着我们的 $2$ 应该变成 $1,3$ 应该变成 $2,1$ 应该变成 $3$，$c$ 就被映射成 $\{1,2,3\}$。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define uc unsigned char
#define inf 1061109567
#define N 204
#define M 1004
using namespace std;
int n,m,ans=1e9;
int a[N][N];
int b[M],stk[M],c[4],d[4];
int f[2][N][N];
uc g[M][N][N];

void init(){
	memset(f[0],63,sizeof(f[0]));
	b[0]=1,f[0][2][3]=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	for(int i=1;i<=m;i++)scanf("%d",&b[i]);
}
inline void getmin(int &u,int v,uc &x,uc y){
	if(v<u)u=v,x=y;
}
inline void work(int x){
	int ij;
	uc cc;
	bool op=x&1;
	memset(f[!op],63,sizeof(f[!op]));//记得初始化
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			ij=f[op][i][j],cc=g[x][i][j];
			if(ij==inf)continue;
			if(b[x+1]==b[x])getmin(f[!op][i][j],ij,g[x+1][i][j],0);
			else if(b[x+1]==i)getmin(f[!op][b[x]][j],ij,g[x+1][b[x]][j],i);
			else if(b[x+1]==j)getmin(f[!op][i][b[x]],ij,g[x+1][i][b[x]],j);
			else{
				getmin(f[!op][i][j],ij+a[b[x]][b[x+1]],g[x+1][i][j],0);
				getmin(f[!op][b[x]][j],ij+a[i][b[x+1]],g[x+1][b[x]][j],i);
				getmin(f[!op][i][b[x]],ij+a[j][b[x+1]],g[x+1][i][b[x]],j);
			}
		}
}
int main(){
	init();
	
	for(int i=0;i<m;i++)work(i);
	
	int pos,u,v;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(f[m&1][i][j]<ans)
				ans=f[m&1][i][j],pos=g[m][i][j],u=i,v=j;
	
    printf("%d\n",ans);
	c[1]=1,c[2]=2,c[3]=3;
	for(int i=m;i;i--){
		stk[i]=c[1];
		if(u==b[i-1])u=g[i][u][v],swap(c[1],c[2]);
		else if(v==b[i-1])v=g[i][u][v],swap(c[1],c[3]);
	}
	
	d[c[1]]=1,d[c[2]]=2,d[c[3]]=3;//进行映射
	for(int i=1;i<=m;i++)
		printf("%d ",d[stk[i]]);//映射
}
```



---

## 作者：0xyz (赞：1)

这题空间有点变态。

首先，由常见套路，令 $f_{i,j,k}$ 表示考虑前 $i$ 个货物，不负责送第 $i$ 个货物的两人此时分别在的位置是 $j,k$ 时的最小总成本。对于转移，我们分类讨论第 $i-1$ 个货物是由谁运输即可。考虑递推，$f_{i-1},j,k$ 的转移，对于 $j,k,p_i$ 互不相同的情况，
$$\begin{cases}f_{i,j,k}\leftarrow \min\{f_{i,j,k},f_{i-1,j,k}+d_{p_{i-1},p_i}\}\\f_{i,p_{i-1},k}\leftarrow \min\{f_{i,p_{i-1},k},f_{i-1,j,k}+d_{j,p_i}\}\\f_{i,j,p_{i-1}}\leftarrow \min\{f_{i,j,p_{i-1}},f_{i-1,j,k}+d_{k,p_i}\}\end{cases}$$

答案就是所有 $f_{m,*,*}$ 的最小值。$i$ 这一维可以滚动。

接下来考虑怎么找到方案，主要是要记录每个状态由谁转移而来。因为绝大部分转移都是 $f_{i,j,k}\leftarrow f_{i-1,j,k}+d_{p_{i-1},p_i}$，所以我们只记录第二、三类转移。用 $g_{i,k}=j$ 表示 $f_{i,p_{i-1},k}$ 从 $f_{i-1,j,k}$ 转移来，$h_{i,j}=k$ 表示 $f_{i,j,p_{i-1}}$ 从 $f_{i-1,j,k}$ 转移来。那么我们转移的路径就很清楚了。对于输出方案的部分，我们可以利用 dfs，用 $\{X,Y,Z\}=\{1,2,3\}$ 表示运输第 $i$ 个货物的是 $X$，搬运 $f$ 中第二、三维代表的货物的分别是 $Y,Z$，从 $i=m$ 开始搜，当 $i=0$ 时令 $X=1,Y=2,Z=3$，回溯时如果是第二类转移就交换 $X,Y$，第三类就交换 $X,Z$，输出每一层的 $X$ 即可。

时间复杂度 $O(n^2m)$，空间复杂度 $O(n^2+nm)$，[0.996MB](https://www.luogu.com.cn/record/188643365)。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int T,n,m,x,y,X=1,Y=2,Z=3,f[201][201],s=1e9;
short p[1001],d[201][201];
unsigned char g[1001][201],h[1001][201];
void sol(int o,unsigned char x,unsigned char y){
	if(!o)return;
	if(x==p[o-1]){
		if(g[o][y])sol(o-1,g[o][y],y),swap(X,Y);
		else sol(o-1,x,y);
	}else if(y==p[o-1]){
		if(h[o][x])sol(o-1,x,h[o][x]),swap(X,Z);
		else sol(o-1,x,y);
	}else sol(o-1,x,y);
	cout<<X<<' ';
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)cin>>d[i][j];
	for(int i=1;i<=m;i++)cin>>p[i];
	memset(f,63,sizeof(f));
	p[0]=1;f[2][3]=0;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++)f[p[i-1]][j]=f[j][p[i-1]]=s;
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
				if(j!=k&&j!=p[i-1]&&k!=p[i-1]){
					if(f[p[i-1]][k]>f[j][k]+d[j][p[i]])f[p[i-1]][k]=f[j][k]+d[j][p[i]],g[i][k]=j;
					if(f[j][p[i-1]]>f[j][k]+d[k][p[i]])f[j][p[i-1]]=f[j][k]+d[k][p[i]],h[i][j]=k;
				}
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
				if(j!=k&&j!=p[i-1]&&k!=p[i-1])f[j][k]+=d[p[i-1]][p[i]];
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(i!=j&&f[i][j]<s)s=f[i][j],x=i,y=j;
	cout<<s<<'\n';sol(m,x,y);
	return 0;
}
```

---

## 作者：xiezheyuan (赞：1)

**吊打其他题解（和现在我能看到的所有最优解）的空间的做法，你也值得拥有！让卡空间成为时代的眼泪！**

## 简要题意

有一个 $n$ 个点的有向完全图（其邻接矩阵为 $C$），边有边权。有三个人，初始时他们分别位于 $1,2,3$。要求在任意时刻，一个点上不得有多于一个人。

依次进行了 $m$ 次请求，每次请求给定一个点 $x_i$，要求派遣一个人经过一条边到达这个点，代价为这条边的边权。

你需要最小化代价总和，输出这个最小值和一组合法的方案。

$1\leq n\leq 200,1\leq m\leq 10^3$。空间限制 $64$ MB。

## 思路

首先有一个比较显然的 dp，设 $f(i,a,b,c)$ 表示第 $i$ 次请求，三个人分别位于 $a,b,c$ 的最小代价和，转移容易，时间复杂度 $O(mn^3)$，空间复杂度 $O(n^3)$ 难以通过本题。

我们发现 $a,b,c$ 中至少存在一个点恰好为 $x_i$，尝试将这个给它去掉，由于每个时刻每个点上至多只有一个人，所以我们假如我们求出了每个状态是从哪个状态转移过来最优，就可以从小到大枚举 $i$ 还原出到底派了哪个人（具体方法后面会说）。

设 $f(i,a,b)$ 表示第 $i$ 次请求，不在 $x_i$ 的两个人分别在 $a,b$ 两点的最小代价和（$a,b$ 可以互换）。

考虑如何转移，首先我们必定有 $f(i,a,b)\leftarrow f(i-1,a,b)+C(x_{i-1}, x_i)$ 表示我们让原先应付第 $i-1$ 次请求的人去应付第 $i$ 次请求。

然后有 $f(i,x_{i-1},a)\leftarrow f(i-1,c,a)+C(c, x_i)$ 表示让另一个人 $k$ 去应付第 $i$ 次请求。同样交换 $x_{i-1},a$ 也是一种转移。

时间复杂度 $O(mn^2)$，空间可以滚动数组优化到 $O(n^2)$，可以应付本题。

考虑如何输出方案，不难想到对于每个状态 $f(i,a,b)$，记录一个 $p(i,a,b)$ 表示从哪个状态转移过来更优。这需要 $O(mn^2)$ 的空间，然后我就被卡了。

考虑如何优化空间，我们发现对于 $a\neq b\neq x_{i-1}$ 的 $f(i,a,b)$，一定是从 $f(i-1,a,b)$ 转移过来，而 $a,b$ 也可以交换，所以我们可以砍掉，只需要记录 $p(i,a)$ 表示 $f(i-1,x_{i-1},a)$ 从哪个状态转移过来更优（也就是上述转移中的那个 $k$）。

然后考虑如何从最优转移点还原成方案，首先可以从最终的转移出发倒推出每个在最优策略中的转移，然后正推输出方案，维护一个桶表示每个人在哪，那么不在状态里的哪个人一定在应付请求，输出即可。

时间复杂度 $O(mn^2)$，空间复杂度优化到了惊人的 $O(nm+n^2)$，实测消耗的空间小于 $1.2$ MB，相对其他题解的 $42$ MB 来说是一个极大的进步。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 201, M = 1e3 + 1;
int f[2][N][N];
unsigned short pre[M][N], x[M], g[N][N], n, m, mp[4];
pair<unsigned short, unsigned short> ret[M];

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin >> g[i][j];
            f[0][i][j] = f[1][i][j] = 0x3f3f3f3f;
        }
    }
    for(int i=1;i<=m;i++) cin >> x[i];
    f[1][1][2] = f[1][2][1] = g[3][x[1]];
    f[1][2][3] = f[1][3][2] = g[1][x[1]];
    f[1][1][3] = f[1][3][1] = g[2][x[1]];
    for(int i=2;i<=m;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=n;k++){
                f[i & 1][j][k] = INT_MAX;
                if(x[i] == j || x[i] == k || x[i - 1] == j || x[i - 1] == k || j == k) continue;
                f[i & 1][j][k] = f[(i & 1) ^ 1][j][k] + g[x[i - 1]][x[i]];
            }
        }
        for(int j=1;j<=n;j++){
            for(int k=1;k<=n;k++){
                if(x[i - 1] == j || x[i - 1] == k || j == k) continue;
                f[i & 1][x[i - 1]][j] = min(f[i & 1][x[i - 1]][j], f[(i & 1) ^ 1][j][k] + g[k][x[i]]);
                if(f[i & 1][x[i - 1]][j] == (f[(i & 1) ^ 1][j][k] + g[k][x[i]])) pre[i][j] = k;
                f[i & 1][j][x[i - 1]] = f[i & 1][x[i - 1]][j];
            }
        }
    }
    int ans = INT_MAX, posi = 0, posj = 0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            ans = min(ans, f[m & 1][i][j]);
            if(ans == f[m & 1][i][j]) posi = i, posj = j;
        }
    }
    cout << ans << '\n';
    ret[m] = {posi, posj};
    for(int i=m;i>1;i--){
        if(posi != x[i - 1] && posj != x[i - 1]) ret[i - 1] = {posi, posj};
        else{
            int tmp = posi == x[i - 1] ? posj : posi;
            int nxt = pre[i][tmp];
            ret[i - 1] = {tmp, nxt}, posi = tmp, posj = nxt;
        }
    }
    mp[1] = 1, mp[2] = 2, mp[3] = 3;
    int cur = 0;
    for(int i=1;i<=m;i++){
        cur++;
        int rc = 0;
        for(int x=1;x<=3;x++){
            int y = mp[x];
            if(y != ret[i].first && y != ret[i].second){
                cout << x << ' ';
                rc = x;
                break;
            }
        }
        mp[rc] = x[cur];
    }
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：Last_Flame (赞：1)

[problem](https://www.luogu.com.cn/problem/P7685)

考场上想出来的一个人类智慧方法，方法不优甚至很劣，而且贼难写（不过我们这边还有一个大佬写了更长的分块做法，真的强），但是大抵可以扩宽一下思路罢。

# 思路

看到空间限制就知道这题不简单。看题面，明显是动态规划，考虑设计状态。

$ dp_{i,j,k,h} $ 表示处理完第 $i$ 个请求，其中员工 $1,2,3$ 分别在位置 $j,k,h$。

然而这样空间复杂度为 $N \times L^{3}$，明显超过空间限制，考虑优化状态。

设 $i$ 时刻请求位置为 $b_{i}$。对于第 $i$ 时刻，都必定有一个员工位置在 $b_{i}$，所以状态可优化为 $dp_{i,j,k}$ 表示处理完第 $i$ 个请求，三个员工位置为 $j,k,b_{i}$。

由于每次转移我们只在意上一时刻的所有状态，所以考虑使用滚动数组，再优化一维，状态优化为 $dp_{i,j}$ 表示该时刻三名员工位置为 $i,j,b_{now}$。这时空间复杂度为 $L^{2}$，时间复杂度为 $O(N \times L^{2})$，可以通过。

但是由于题目要求输出方案，滚动数组无法记录，所以我产生了一个人类智慧的神秘想法：我们知道结果后，再反向进行一次 dp。

### 反向转移

**(设 $i$ 时刻请求位置为 $b_{i}$，同时为方便理解，将状态加上一个时间维)**

我们知道正向转移为（当前时刻为 $t$，转移到 $t+1$ 时刻）：

- $dp_{t+1,i,j}=\min(dp_{t,i,j}+C_{b_{t},b_{t+1}})$

- $dp_{t+1,i,b_{t+1}}=\min(dp_{t,i,j}+C_{j,b_{t+1}})$

那么反向转移为（当前时刻为 $t$，转移到 $t-1$ 时刻）：

- $dp_{t-1,i,j} = \max(dp_{t,i,j}-C_{b_{t-1},b_{t}})$

- $\text{对任意的 }$ $k\in[1,L],k \ne i,k \ne b_{t-1},\text{有 }$ $dp_{t-1,i,k}$ = $\max(dp_{t,i,b_{t-1}}-C_{k,b_{t}})$

### 证明

虽然我们希望通过反向 dp 还原正向 dp 时的状态，但是正向时取 $\min$，反向时取 $\max$，显然会有信息遗漏。但我们知道有些状态对答案（最优解）是没有贡献的，只要对答案有贡献的所有状态可以还原即可。

**如果反向 dp 时某状态的值等于正向 dp 时同时刻该状态的值，我们称反向 dp 时该状态的值是真实的，同时称正向 dp 时该状态的值为真实值。**

假设我们知道了第 $t$ 时刻所有对答案有贡献的状态，我们希望还原第 $t-1$ 时刻所有对答案有贡献的状态。

若正向 dp 时 $dp_{t-1,i,j}$ 对 $dp_{t,k,h}$ 有贡献，且它们均对答案有贡献，那么一定有

$$dp_{t-1,i,j}=dp_{t,k,h}-C$$

但是假如我们还原的 $t$ 时刻的某个状态要大于它的真实值，则不一定可以实现这个转移。换句话说，假如我们能证明反向 dp 得到的所有时刻的所有状态的值，都要小于等于该状态的真实值，那么就能够还原所有对答案有贡献的状态。

若正向 dp 时 $dp_{t-1,i,j}$ 对 $dp_{t,k,h}$ 有贡献，且反向 dp 时 $dp_{t,k,h}$ 的值是真实的，$t$ 时刻的所有状态的值小于等于真实值，则反向转移后 $dp_{t-1,i,j}$ 的值是真实的，因为不可能存在使 $dp_{t-1,i,j}$ 的值比真实值更大的反向转移。

若正向 dp 时 $dp_{t-1,i,j}$ 不对 $t$ 时刻的任何状态做贡献，且反向 dp 时所有状态的值小于等于真实值，则反向转移后 $dp_{t-1,i,j}$ 的值小于真实值，理由同上。

由于 $N$ 时刻所有状态的值均为真实值，所以反向 dp 得到的所有状态的值均小于等于真实值，所以所有对答案有贡献的状态均可以通过反向 dp 还原。

### 细节

但是还有一些细节问题，比如枚举 $k$ 的时候（详见上文反向转移方程），要保证 $k$ 是合法的，即对于时刻 $t$，$k$ 必须在 $b_{1}$~$b_{t-1}$ 中出现过，或 $k$ 为 $1,2,3$。

同时反向 dp 得到的对答案有贡献的状态也有一些是不合法的，它们的值要小于真实值，需要加上特判。

# code

我的码风十分神秘，观感不好非常抱歉！

其中部分是为了保证 $dp_{i,j}$ 中 $i < j$ 的重复代码。

同时由于负责题目的同学改了体面，有些变量名字有区别：

位置个数：$n$

请求数：$t$

移动成本：$a$

移动请求：$b$

~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int mn=110,inf=2147483647,pmax=2000000;
vector<int> ldp[2],ndp[2],l[10*mn][2];
int n,t,a[2*mn][2*mn],b[10*mn];
int dp[2*mn][2*mn],dp2[2*mn][2*mn];
int num[2*mn];
int p1,p2,p3,pt;
int ans,ansp;
bool isin[2*mn][2*mn];

void move1(){
	for(int i=1;i<=n;i++){
		for(int i1=i;i1<=n;i1++){
			if(dp2[i][i1]<=pmax) dp[i][i1]=dp2[i][i1];
			else dp[i][i1]=0;
			dp2[i][i1]=inf;
		}
	}
	return;
}

void move2(){
	for(int i=1;i<=n;i++){
		for(int i1=i;i1<=n;i1++){
			dp[i][i1]=dp2[i][i1];
			dp2[i][i1]=0;
			isin[i][i1]=false;
		}
	}
	ldp[0]=ndp[0],ldp[1]=ndp[1];
	ndp[0].clear(),ndp[1].clear();
	return;
}

int main(){
	cin>>n>>t;
	for(int i=1;i<=n;i++) for(int i1=1;i1<=n;i1++) cin>>a[i][i1];
	for(int i=1;i<=t;i++) cin>>b[i];
	
	for(int i=1;i<=n;i++) for(int i1=i;i1<=n;i1++) dp2[i][i1]=inf;
	dp[1][2]=a[3][b[1]]+1,dp[1][3]=a[2][b[1]]+1,dp[2][3]=a[1][b[1]]+1;
	num[b[1]]++,num[1]++,num[2]++,num[3]++;
	//正向转移 
	for(int i=2;i<=t;i++){
		num[b[i]]++;
		for(int i1=1;i1<=n;i1++){
			for(int i2=i1+1;i2<=n;i2++) if(dp[i1][i2]>0){
				if(i1!=b[i] && i2!=b[i]) dp2[i1][i2]=min(dp2[i1][i2],dp[i1][i2]+a[b[i-1]][b[i]]);
				if(i2!=b[i] && b[i-1]!=b[i]) dp2[min(i2,b[i-1])][max(i2,b[i-1])]=min(dp2[min(i2,b[i-1])][max(i2,b[i-1])],dp[i1][i2]+a[i1][b[i]]);
				if(i1!=b[i] && b[i-1]!=b[i]) dp2[min(i1,b[i-1])][max(i1,b[i-1])]=min(dp2[min(i1,b[i-1])][max(i1,b[i-1])],dp[i1][i2]+a[i2][b[i]]);
			}
		}
		move1();
	}
	
	ans=inf;
	ldp[0].push_back(114514),ldp[1].push_back(1919810);
	for(int i=1;i<=n;i++){
		for(int i1=i+1;i1<=n;i1++) if(dp[i][i1]>0 && dp[i][i1]<ans){
			ans=dp[i][i1];
			ldp[0][0]=i,ldp[1][0]=i1;
		}
	}
	ans--,num[b[t]]--;
	
	/* 
	反向dp
	考虑正向dp(t,i,j)->dp(t+1,i,j),dp(t+1,i,b[t]),dp(t+1,j,b[t]) 
	反向则是特殊判断dp(i,j)中i,j是否等于b[t-1],同时转移时要取max 
	若等于，枚举所有情况转移:dp(t,i,b[t-1])->dp(t,i,1~n) 
	若不等于，则直接转移dp(t,i,j)->dp(t-1,i,j) 
	*/
	for(int i=1;i<=n;i++) for(int i1=i;i1<=n;i1++) dp2[i][i1]=0;
	for(int i=t-1;i>=1;i--){
		num[b[i]]--;
		for(int i1=1;i1<=n;i1++){
			for(int i2=i1+1;i2<=n;i2++) if(!isin[i1][i2] && i1!=b[i] && i2!=b[i] && dp[i1][i2]>0 && num[i1]>0 && num[i2]>0){
				dp2[i1][i2]=max(dp2[i1][i2],dp[i1][i2]-a[b[i]][b[i+1]]);
			}
		}
		for(int i1=b[i]+1;i1<=n;i1++) if(!isin[b[i]][i1] && dp[b[i]][i1]>0){
			for(int i2=1;i2<i1;i2++) if(i2!=b[i] && num[i2]>0) dp2[i2][i1]=max(dp2[i2][i1],dp[b[i]][i1]-a[i2][b[i+1]]);
			for(int i2=i1+1;i2<=n;i2++) if(i2!=b[i] && num[i2]>0) dp2[i1][i2]=max(dp2[i1][i2],dp[b[i]][i1]-a[i2][b[i+1]]);
		}
		for(int i1=1;i1<b[i];i1++) if(!isin[i1][b[i]] && dp[i1][b[i]]>0){
			for(int i2=1;i2<i1;i2++) if(i2!=b[i] && num[i2]>0) dp2[i2][i1]=max(dp2[i2][i1],dp[i1][b[i]]-a[i2][b[i+1]]);
			for(int i2=i1+1;i2<=n;i2++) if(i2!=b[i] && num[i2]>0) dp2[i1][i2]=max(dp2[i1][i2],dp[i1][b[i]]-a[i2][b[i+1]]);
		}
		
		for(int i1=0;i1<ldp[0].size();i1++){
			if(ldp[0][i1]!=b[i] && ldp[1][i1]!=b[i]){
				if(dp2[ldp[0][i1]][ldp[1][i1]]<=dp[ldp[0][i1]][ldp[1][i1]]-a[b[i]][b[i+1]]){
					dp2[ldp[0][i1]][ldp[1][i1]]=dp[ldp[0][i1]][ldp[1][i1]]-a[b[i]][b[i+1]];
					if(!isin[ldp[0][i1]][ldp[1][i1]]){
						ndp[0].push_back(ldp[0][i1]);
						ndp[1].push_back(ldp[1][i1]);
						isin[ldp[0][i1]][ldp[1][i1]]=true;
						l[i][0].push_back(i1);
						l[i][1].push_back(b[i]);
					}
				}
			}
			else if(ldp[0][i1]==b[i]){
				for(int i2=1;i2<ldp[1][i1];i2++){
					if(i2!=b[i] && num[i2]>0 && dp2[i2][ldp[1][i1]]<=dp[ldp[0][i1]][ldp[1][i1]]-a[i2][b[i+1]]){
						dp2[i2][ldp[1][i1]]=dp[ldp[0][i1]][ldp[1][i1]]-a[i2][b[i+1]];
						if(!isin[i2][ldp[1][i1]]){
							ndp[0].push_back(i2);
							ndp[1].push_back(ldp[1][i1]);
							isin[i2][ldp[1][i1]]=true;
							l[i][0].push_back(i1);
							l[i][1].push_back(i2);
						}
					}
				}
				for(int i2=ldp[1][i1]+1;i2<=n;i2++){
					if(i2!=b[i] && num[i2]>0 && dp2[ldp[1][i1]][i2]<=dp[ldp[0][i1]][ldp[1][i1]]-a[i2][b[i+1]]){
						dp2[ldp[1][i1]][i2]=dp[ldp[0][i1]][ldp[1][i1]]-a[i2][b[i+1]];
						if(!isin[ldp[1][i1]][i2]){
							ndp[0].push_back(ldp[1][i1]);
							ndp[1].push_back(i2);
							isin[ldp[1][i1]][i2]=true;
							l[i][0].push_back(i1);
							l[i][1].push_back(i2);
						}
					}
				}
			}
			else{
				for(int i2=1;i2<ldp[0][i1];i2++){
					if(i2!=b[i] && num[i2]>0 && dp2[i2][ldp[0][i1]]<=dp[ldp[0][i1]][ldp[1][i1]]-a[i2][b[i+1]]){
						dp2[i2][ldp[0][i1]]=dp[ldp[0][i1]][ldp[1][i1]]-a[i2][b[i+1]];
						if(!isin[i2][ldp[0][i1]]){
							ndp[0].push_back(i2);
							ndp[1].push_back(ldp[0][i1]);
							isin[i2][ldp[0][i1]]=true;
							l[i][0].push_back(i1);
							l[i][1].push_back(i2);
						}
					} 
				}
				for(int i2=ldp[0][i1]+1;i2<=n;i2++){
					if(i2!=b[i] && num[i2]>0 && dp2[ldp[0][i1]][i2]<=dp[ldp[0][i1]][ldp[1][i1]]-a[i2][b[i+1]]){
						dp2[ldp[0][i1]][i2]=dp[ldp[0][i1]][ldp[1][i1]]-a[i2][b[i+1]];
						if(!isin[ldp[0][i1]][i2]){
							ndp[0].push_back(ldp[0][i1]);
							ndp[1].push_back(i2);
							isin[ldp[0][i1]][i2]=true;
							l[i][0].push_back(i1);
							l[i][1].push_back(i2);
						}
					}
				}
			}
			
		}
		
		move2();
	}
	
	cout<<ans<<endl;
	
	p1=1,p2=2,p3=3,pt=0;
	while(true){
		if(ldp[0][pt]==1 && ldp[1][pt]==2){
			if(dp[ldp[0][pt]][ldp[1][pt]]!=a[3][b[1]]+1) pt++;
			else{
				cout<<"3 ";
				p3=b[1];
				break;
			}
		}
		else if(ldp[0][pt]==1 && ldp[1][pt]==3){
			if(dp[ldp[0][pt]][ldp[1][pt]]!=a[2][b[1]]+1) pt++;
			else{
				cout<<"2 ";
				p2=b[1];
				break;
			}
		}
		else{
			if(dp[ldp[0][pt]][ldp[1][pt]]!=a[1][b[1]]+1) pt++;
			else{
				cout<<"1 ";
				p1=b[1];
				break;
			}
		}
	}
	
	for(int i=1;i<t;i++){
		if(p1==l[i][1][pt]){
			cout<<"1 ";
			p1=b[i+1];
		}
		else if(p2==l[i][1][pt]){
			cout<<"2 ";
			p2=b[i+1];
		}
		else{
			cout<<"3 ";
			p3=b[i+1];
		}
		pt=l[i][0][pt];
	}
	cout<<endl;
	
	return 0;
}
~~~

---

## 作者：Soh_paramEEMS (赞：0)

本题解把 SP703 和洛谷 P7685 写在一起，便于循序渐进地做题。

## 题意
一个公司有三个移动服务员。如果某个地方有一个请求，某个服务员必须赶到那个地方去（那个地方没有其他服务员），某一时刻只有一个服务员能移动。被请求后，他才能移动，不允许在同样的位置出现两个服务员。从 $p$ 到 $q$ 移动一个服务员，需要花费 $c(p,q)$，$c(p,p)=0$。公司必须满足所有的请求，目标是最小化公司花费，并输出每次请求提供服务的服务员编号 $1,2,3$。

共有 $m$ 个地方，$n$ 个请求。

$\forall c(p,q)\in[0,2000]$。

SP703：多测组数$T$，大小不详，较小；无输出编号需求。

洛谷P7685：$3\le m\le 200,1\le n\le 1000,64\rm MB$。

下文将提供洛谷 P7685 数据要求的题解，其他数据范围敬请自行修改。

## 思路
最朴素的状态设法，设 $f_{i,x,y,z}$ 表示完成第 $i$ 个请求后，三个服务员各自在 $x,y,z$。

但是看到空间限制无比的小，因此状态下标那么多，肯定开不下。

我们发现，每个请求之后，三个服务员中，肯定有一个服务员在请求位置 $a_i$，因此我们尝试从这里下手，缩减状态。

令 $f_{i,x,y}$ 表示，三个服务员一个去到了 $a_i$ ，剩下两个在位置 $x,y$ 的最小代价，不妨令 $z=a_{i-1}$ ，那么显然的有：
$$f_{i,x,y}=\min \{f_{i-1,x,y}+c(z,a_i)\}$$

$$f_{i,x,z}=\min \{f_{i-1,x,y}+c(y,a_i)\}$$

$$f_{i,y,z}=\min \{f_{i-1,x,y}+c(x,a_i)\}$$

记得判断三个位置相互不同。

还想缩减空间，那就滚动数组吧。

```cpp
memset(f,inf,sizeof(f));
f[0][1][2]=0;
a[0]=3;
for(int i=1;i<=n;i++)
{
	ll now=i&1,las=now^1;
	memset(f[now],inf,sizeof(f[now]));
	for(int x=1;x<=m;x++)
	{
		for(int y=1;y<=m;y++)
		{
			ll z=a[i-1];
			if(x==y||y==z||z==x)continue;
			if(!(x==y||y==a[i]||a[i]==x))f[now][x][y]=min(f[now][x][y],f[las][x][y]+c[z][a[i]]);
			if(!(x==z||z==a[i]||a[i]==x))f[now][x][z]=min(f[now][x][z],f[las][x][y]+c[y][a[i]]);
			if(!(y==z||z==a[i]||a[i]==y))f[now][y][z]=min(f[now][y][z],f[las][x][y]+c[x][a[i]]);
		}
	}
}
```

不过写完代码之后，发现交在 SP703 被无脑卡常。我的原因是对 $x,y$ 两状态循环的时候，两个全枚举了 $1\sim n$，那么尝试缩减，通过保证两个状态 $x<y$ 可以实现缩减状态枚举量（虽然只是除以二）。具体实现见代码。

## 代码（SP703）
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int M=202,N=1002,inf=0x3f3f3f3f;
int T,m,n,c[M][M],a[N];
ll f[2][M][M];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&m,&n);
		for(int i=1;i<=m;i++)
		for(int j=1;j<=m;j++)
		scanf("%d",&c[i][j]);
		for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
		memset(f,inf,sizeof(f));
		f[0][1][2]=0;
		a[0]=3;
		for(int i=1;i<=n;i++)
		{
			int now=i&1,las=now^1;
			memset(f[now],inf,sizeof(f[now]));
			for(int x=1;x<=m;x++)
			{
				for(int y=x+1;y<=m;y++)
				{
					int z=a[i-1];
					if(x==y||y==z||z==x)continue;
					if(!(x==y||y==a[i]||a[i]==x))f[now][x][y]=min(f[now][x][y],f[las][x][y]+c[z][a[i]]);
					if(!(x==z||z==a[i]||a[i]==x))f[now][min(x,z)][max(x,z)]=min(f[now][min(x,z)][max(x,z)],f[las][x][y]+c[y][a[i]]);
					if(!(y==z||z==a[i]||a[i]==y))f[now][min(y,z)][max(y,z)]=min(f[now][min(y,z)][max(y,z)],f[las][x][y]+c[x][a[i]]);
				}
			}
		}
		ll ret=inf;
		for(int x=1;x<=m;x++)
		{
			for(int y=1;y<=m;y++)
			{
				if(x==y)continue;
				ret=min(ret,f[n&1][x][y]);
			}
		}
		printf("%lld\n",ret);
	}
	return 0;
}
```

那么怎么才能找到前往服务的服务员编号呢？那就要在 dp 的时候作处理了。

我们记 $pos_{i,x,y}$ 表示，遍历到第 $i$ 个请求时，“处理请求 $a_i$ 的并非在位置 $x,y$ 的服务员”这一情况是否改变，如果不改变则为 $0$，否则就是前往 $a_i$ 的服务员的前继位置。

找最小代价的时候，把最终最小代价所处的状态 ${\rm ans}=f_{n,x,y}$ 的 $x,y$ 记为 $minx=x,miny=y$ ，即其中一个服务员处理完请求 $a_n$ 之后，其他两个服务员所在的位置。

令 $X_i,Y_i$ 表示处理第 $i$ 个请求时，其中一个服务员处理请求 $a_i$ ，其他两个服务员所在的位置。那就可以考 $\rm pos$ 数组反推了：

初始状态 $X_n=minx,Y_n=miny$，考虑倒序枚举 $i:n\rightarrow1$，每次更新$minx,miny$ 从而更新 $X_i,Y_i$。

如果上文的“情况”不改变，那么 $X_i,Y_i$ 相应不变，不更新 $minx,miny$；否则将等于 $a_{i-1}$ 的 $minx$ 或者 $miny$ 置为 $pos_{i,X_i,Y_i}$。

```cpp
for(int i=n;i>=1;i--)
{
	x[i]=minx,y[i]=miny;
	int tem=pos[i][x[i]][y[i]];
	if(tem)
	{
		if(minx==a[i-1])minx=tem;
		else miny=tem;
	}
}
```

得到了 $X,Y$ 数组，就可以输出答案了。由于编号 $1\sim 3$ 有一个很好的性质，就是和为 $6$，知道了其中两个编号，那么另外一个就是唯一的。而我们正要通过 $X,Y$ 数组更新对应编号：即记 $A,B$ 表示当前没有前往请求 $a_i$ 的服务员编号，初始不妨设为 $A=1,B=2$ （反正是 Special Judge）。

具体及细节见代码。

## 代码（洛谷P7685）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define uc unsigned char
const int M=202,N=1002,inf=0x3f3f3f3f;
int m,n,c[M][M],a[N];
ll f[2][M][M];
int x[N],y[N];
uc pos[N][M][M];
int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
	for(int j=1;j<=m;j++)
	scanf("%d",&c[i][j]);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	memset(f,inf,sizeof(f));
	f[0][1][2]=0;
	a[0]=3;
	x[0]=1,y[0]=2;
	for(int i=1;i<=n;i++)
	{
		int now=i&1,las=now^1;
		memset(f[now],inf,sizeof(f[now]));
		for(int x=1;x<=m;x++)
		{
			for(int y=1;y<=m;y++)
			{
				int z=a[i-1];
				if(x==y)continue;
				if(!(x==a[i]||y==a[i]))
				{
					ll tem=f[las][x][y]+c[z][a[i]];
					if(tem<f[now][x][y])
					{
						f[now][x][y]=tem;
						pos[i][x][y]=0;
					}
				}
				if(!(x==a[i]||z==a[i]))
				{
					ll tem=f[las][x][y]+c[y][a[i]];
					if(tem<f[now][x][z])
					{
						f[now][x][z]=tem;
						pos[i][x][z]=y;
					}
				}
				if(!(y==a[i]||z==a[i]))
				{
					ll tem=f[las][x][y]+c[x][a[i]];
					if(tem<f[now][z][y])//y上下对应 
					{
						f[now][z][y]=tem;
						pos[i][z][y]=x;
					}
				}
			}
		}
	}
	ll ret=inf;
	int minx=0,miny=0,A=1,B=2;
	for(int x=1;x<=m;x++)
	{
		for(int y=1;y<=m;y++)
		{
			if(f[n&1][x][y]<ret)
			{
				ret=f[n&1][x][y];
				minx=x,miny=y;
			}
		}
	}
	printf("%lld\n",ret);
	for(int i=n;i>=1;i--)
	{
		x[i]=minx,y[i]=miny;
		int tem=pos[i][x[i]][y[i]];
		if(tem)
		{
			if(minx==a[i-1])minx=tem;
			else miny=tem;
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(x[i]==a[i-1])A=6-A-B;//不变即继承
		else if(y[i]==a[i-1])B=6-A-B;
		printf("%d ",6-A-B);
	}
	return 0;
}
```

---

## 作者：makerli (赞：0)

[link](https://www.luogu.com.cn/problem/P7685)

~~非常好 Mobile Service，简单版卡了半个月，困难版卡了半年。~~

在做本题之前建议先做 [SP703](https://www.luogu.com.cn/problem/SP703)，是本题的简单版，本题解代码从 SP703 优化而来。

先解决第一问。设 $f_{cnt,i,j,k}$ 为第 $cnt$ 个请求时，三人的位置分别为 $i,j,k$ 的最小总成本。因此，我们需要 $4 \times 1000 \times 200 \times 200 \times 200 =3.2 \times 10^{10}B \approx 29.8GiB$ 的内存就可以存下整个 DP 数组啦！

这么大的空间肯定不行。因为每次请求三个人中有一个人会在请求的位置上（即 $x_{cnt}$），所以可以设 $f_{cnt,i,j}$ 为第 $cnt$ 个请求时，不提供服务的两人所在位置分别为 $i,j$ 的最小总成本。

该如何写状态转移方程？考虑以下三种情况：

1. $f_{cnt,x_{cnt-1},j}$ 由 $f_{cnt-1,i,j}$ 转移而来（即上一轮在 $i$ 位置的人提供服务）。此时的转移方程：$$f_{cnt,x_{cnt-1},j}=min(f_{cnt,x_{cnt-1},j},f_{cnt-1,i,j}+c_{i,x_{cnt}})$$

2. $f_{cnt,i,x_{cnt-1}}$ 由 $f_{cnt-1,i,j}$ 转移而来（即上一轮在 $j$ 位置的人提供服务）。此时的转移方程：$$f_{cnt,i,x_{cnt-1}}=min(f_{cnt,i,x_{cnt-1}},f_{cnt-1,i,j}+c_{j,x_{cnt}})$$

3. $f_{cnt,i,j}$ 由 $f_{cnt-1,i,j}$ 转移而来（即上一轮在 $x_{cnt-1}$ 位置的人提供服务）。此时的转移方程：$$f_{cnt,i,j}=min(f_{cnt,i,j},f_{cnt-1,i,j}+c_{x_{cnt-1},x_{cnt}})$$

最后的答案就是所有 $f_{n,i,j}$ 的最大值。~~（这其实就是 SP703 的题解）~~

但本题的空间限制卡的非常紧，如果按照刚刚的方法，DP 数组仍需要 $4 \times 1000 \times 200 \times 200=1.6 \times 10^8B \approx 152.6MiB$ 的空间。还能怎么压？

类似于滚动数组，这里的状态只与上一次请求的状态有关。所以我们只需要存储当前状态和上一次请求的状态就行了，这样又可以节省很多空间。优化后 DP 数组占用的空间为 $4 \times 2 \times 200 \times 200=3.2 \times 10^5B \approx 0.31MiB$，空间问题解决！

再来解决第二问。在转移过程中，第一和第二种情况的 $i,j$ 是有变化的。所以在转移过程中记录 $i,j$ 由谁转移而来。在最后回溯整个转移过程，在中途输出编号即可。

代码如下（用时 302ms，内存占用 2.39MB）：

```cpp
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
int c[201][201];
int f[2][201][201]; //滚动数组节省空间
int p[1001], q1[1001][201], q2[1001][201], X = 1, Y = 2, Z = 3;
void find(int now, int x, int y)
{
    if (now <= 0)
        return;
    if (x == p[now - 1])
        if (q1[now][y] != 0)
            find(now - 1, q1[now][y], y), swap(X, Z);    //对应第一种情况
        else
            find(now - 1, x, y);
    else if (y == p[now - 1])
        if (q2[now][x] != 0)
            find(now - 1, x, q2[now][x]), swap(Y, Z);    //对应第二种情况
        else
            find(now - 1, x, y);
    else
        find(now - 1, x, y);
    cout << Z << ' ';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int l, n, ans, x, y;
    cin >> l >> n;
    for (int i = 1; i <= l; i++)
        for (int j = 1; j <= l; j++)
            cin >> c[i][j];
    for (int i = 1; i <= n; i++)
        cin >> p[i];
    memset(f[0], 0X3F, sizeof(f[0]));
    f[0][1][2] = 0;
    p[0] = 3;
    for (int i = 0; i < n; i++) //cnt对应这里的i+1,cnt-1对应i
    {
        memset(f[(i + 1) % 2], 0X3F, sizeof(f[(i + 1) % 2]));   //滚动数组一定一定要记得初始化！
        for (int x = 1; x <= l; x++)
            for (int y = 1; y <= l; y++)
            {
                if (x == p[i] || x == y || y == p[i])
                    continue;
                if (f[(i + 1) % 2][p[i]][y] > f[i % 2][x][y] + c[x][p[i + 1]])  //第一种情况
                    f[(i + 1) % 2][p[i]][y] = min(f[(i + 1) % 2][p[i]][y], f[i % 2][x][y] + c[x][p[i + 1]]), q1[i + 1][y] = x;
                if (f[(i + 1) % 2][x][p[i]] > f[i % 2][x][y] + c[y][p[i + 1]])  //第二种情况
                    f[(i + 1) % 2][x][p[i]] = min(f[(i + 1) % 2][x][p[i]], f[i % 2][x][y] + c[y][p[i + 1]]), q2[i + 1][x] = y;
                if (f[(i + 1) % 2][x][y] > f[i % 2][x][y] + c[p[i]][p[i + 1]])  //第三种情况
                    f[(i + 1) % 2][x][y] = min(f[(i + 1) % 2][x][y], f[i % 2][x][y] + c[p[i]][p[i + 1]]);
            }
    }
    ans = 0x3f3f3f3f;
    for (int i = 1; i <= l; i++)
        for (int j = 1; j <= l; j++)
            if (ans > f[n % 2][i][j])
                ans = f[n % 2][i][j], x = i, y = j;
    cout << ans << endl;
    find(n, x, y);
    return 0;
}
```

---

## 作者：12345678hzx (赞：0)

一道很好的动态规划题。

这道题大家应该都能想到用 $f_{i,j,k,l}$ 表示处理完前 $i$ 个任务，此时第一个人在 $j$ 点，第二个人在 $k$ 点，第三个人在 $l$ 点的状态表示。

然后你就会发现空间炸了。考虑优化。

注意到我们状态设计的前提是处理完前 $i$ 个任务，所以此时必有一个人在 $A_i$ 这个位置，于是我们就可以在时间和空间上省掉一维。

由于此题 $f_i$ 的转移只与 $f_{i-1}$ 有关，所以就可以滚掉，在空间上又省了一维。

于是转移也很好写了，相信大家都会，在此不再赘述，但是由于运用了滚动数组，所以方案也会被滚掉，我们主要来讲一下如何保存方案。

这时我们就要用一个数组记录最优解是从哪里转移过来的，于是在输出路径时就可以递归求出方案。

考虑这个数组所记录的信息，由于在 DP 时有一个开头所介绍的隐藏维度，所以必定会有一个人处于 $A_i$ 的位置,我们只要根据这个性质就可以推出方案。

---

