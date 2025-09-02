# Bender Problem

## 题目描述

Robot Bender decided to make Fray a birthday present. He drove $ n $ nails and numbered them from $ 1 $ to $ n $ in some order. Bender decided to make a picture using metal rods. The picture is a closed polyline, which vertices should be nails (in the given order). The segments of the polyline should be parallel to the coordinate axes. Polyline is allowed to have self-intersections. Bender can take a rod and fold it exactly once in any place to form an angle of 90 degrees. Then he can attach the place of the fold to some unoccupied nail and attach two ends of this rod to adjacent nails. A nail is considered unoccupied if there is no rod attached to it (neither by it's end nor the by the fold place). No rod could be used twice. It is not required to use all the rods.

Help Bender to solve this difficult task.

## 样例 #1

### 输入

```
4 2
0 0
0 2
2 2
2 0
4 4
```

### 输出

```
YES
1 -1 2 -1 
```

## 样例 #2

### 输入

```
6 3
0 0
1 0
1 1
2 1
2 2
0 2
3 2 3
```

### 输出

```
YES
1 -1 2 -1 3 -1 
```

## 样例 #3

### 输入

```
6 3
0 0
1 0
1 1
2 1
2 2
0 2
2 2 3
```

### 输出

```
NO
```

# 题解

## 作者：SSqwq_ (赞：3)

题意极难理解（对我来说）

## 题意：

有 $n$ 个钉子，从 $1$ 到 $n$ 编号，有 $m$ 条铁棒，要求用这些铁棒和钉子围成封闭图形。铁棒不与要用完，但是必须平行于坐标轴。现在把铁棒弯成直角，中间的折叠点一个钉子，两头各一个钉子，要求折叠的这颗钉子必须没有与别的铁棒相连，问选铁棒的方案，棒不能重复。

## 思路：

我们应该枚举折线上弯折处的点的位置，因为每段会有三个钉子，弯折处的钉子决定了三个连续钉子的位置。若折叠点是第 $k$ 个钉子，那么它的两旁就是编号 $k-1$ 和 $k+1$ 的钉子，这样这三个点的**最短折线距离**就是需要的铁棒的长，所以直接枚举就可以了。

# AC代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,t;
struct Node
{
   int x,y;
}a[10001];
int len[10001];
int used[10001];
int ans[10001];
bool check(int i,int j)
{
    return len[j]==((abs(a[i-1].x-a[i].x)+abs(a[i-1].y-a[i].y))+(abs(a[i+1].x-a[i].x)+abs(a[i+1].y-a[i].y)));
}
void yuchuli()
{
	a[0].x=a[n].x;
    a[0].y=a[n].y;
    a[n+1].x=a[1].x;
    a[n+1].y=a[1].y;
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y;
    for(int i=1;i<=m;i++)cin>>len[i];
    yuchuli();
    for(int i=1;i<=n;i+=2)
  	{
        int akioi=0;
        for(int j=1;j<=m;j++)
        {
            if(used[j]==false&&check(i,j)==true)
            {
                akioi=1;
                used[j]=1;
                ans[i]=j;
                break;
            }
        }
        if(akioi==false)
        {
            t=1;
            break;
        }
    }
    if(t==false)
    {
    	printf("YES\n");
        for(int lxl=1;lxl<=n;lxl++)
  		{
     	  	if(lxl==1)printf("%d",(ans[lxl]?ans[lxl]:-1));
    	   	else printf(" %d",(ans[lxl]?ans[lxl]:-1));
   		}
    }
    else
    {
        memset(used,0,sizeof(used));
        memset(ans,0,sizeof(ans));
        for(int i=2;i<=n;i+=2)
        {
            int akioi=0;
            for(int j=1;j<=m;j++)
  			{
           		if(used[j]==false&&check(i,j)==true)
  				{
                    akioi=1;
                    used[j]=1;
                    ans[i]=j;
                    break;
                }
            }
            if(akioi==false)
 			{
                printf("NO\n");
                return 0;
            }
        }
        printf("YES\n");
   		for(int lxl=1;lxl<=n;lxl++)
  		{
       		if(lxl==1)printf("%d",(ans[lxl]?ans[lxl]:-1));
      	  	else printf(" %d",(ans[lxl]?ans[lxl]:-1));
   		}
    }
    return 0;
}
```


---

## 作者：Fubaogege (赞：2)

分析：

- 有 $n$ 个钉子，从 $1 \sim n$ 编号，有 $m$ 条铁棒。
- 要求用这些铁棒和钉子围成一个封闭的折线。
- 要求铁棒不一定全部用完，铁棒必须平行于坐标轴。
- 现在他要把铁棒弯成直角，这样中间的折叠点一个钉子，两头各一个钉子，要求折叠的这颗钉子之前必须是没有别的棒连接的（也就是空钉子）。
- 棒只能用一次。
- 问怎么选棒。

因为每次选棒会占用三个钉子，所以我们重点看弯折的钉子，看着看着就会发现，他是需要被枚举的。

找下规律：

- 折叠点：$1$，下个折叠点：$3$。
- 折叠点：$3$，下个折叠点：$5$。
- 折叠点：$5$，下个折叠点：$7$。
- 折叠点：$2$，下个折叠点：$4$。
- 折叠点：$4$，下个折叠点：$6$。
- 折叠点：$6$，下个折叠点：$8$。

枚举：

- 从 $1$ 开始一直枚举。

如果没有则没有答案，反之则有，输出就行。

---

## 作者：Frather_ (赞：2)

# **题意**

有 $n$ 个钉子，从 $1 \sim n$ 编号，有 $m$ 条铁棒，要求用这些铁棒和钉子围成一个封闭的折线。要求铁棒**不一定全部用完**，铁棒必须平行于坐标轴。

现在他要把铁棒弯成直角，这样中间的折叠点一个钉子，两头各一个钉子，要求折叠的这颗钉子之前必须是没有别的棒连接的（也就是空钉子），问怎么选棒，棒只能用一次。

如果无法解决 Bender 的问题，请输出 `NO` 。否则，在第一行中输出 `YES` ，在第二行中输出 $n$ 个数字，其中第 $i$ 个数表示杆的数量，该折叠位置固定在第 $i$ 个钉上；如果没有这样的杆，则输出 $-1$ 。

# **思路**

用铁棒把钉子框起来，每个铁棒只能折叠一次。

由题意我们可以得出，如果一个铁棒在第 $i$ 个钉子处折叠，那么第 $i+1$ 个就一定不是折叠的。

题目中钉子按顺序给出，所以我们只需要枚举每个钉子，判断是奇数或者偶数点，看是否满足即可。

注意初始条件。

# **CODE**

```cpp
/*

Name: CF28A Bender Problem

Solution: 瞎搞
   

By Frather_

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#define ll long long
#define InF 0x3f3f3f3f
#define kMax 10e5
#define kMin -10e5
#define kMod 998244353
using namespace std;
/*==================================================快读*/
inline int read()
{
    int X = 0, F = 1;
    char CH = getchar();
    while (CH < '0' || CH > '9')
    {
        if (CH == '-')
            F = -1;
        CH = getchar();
    }
    while (CH >= '0' && CH <= '9')
    {
        X = (X << 3) + (X << 1) + (CH ^ 48);
        CH = getchar();
    }
    return X * F;
}
/*===============================================定义变量*/
int n, m;

const int _ = 10010;

int x[_], y[_], rod[_], ans[_];
bool vis[_];
bool flag;
/*=============================================自定义函数*/
int Calc(int i, int j)
{
    int x_ = abs(x[j] - x[(j + n - 1) % n]);
    int y_ = abs(y[j] - y[(j + n - 1) % n]);
    int _x = abs(x[j] - x[(j + 1) % n]);
    int _y = abs(y[j] - y[(j + 1) % n]);
    return x_ + y_ + _x + _y;
}

void prepare()
{
    memset(ans, -1, sizeof(ans)); //判断是否折叠
    memset(vis, false, sizeof(vis));
    flag = true;
}
/*=================================================主函数*/
signed main()
{
    n = read();
    m = read();
    for (int i = 0; i < n; i++)
    {
        x[i] = read();
        y[i] = read();
    }
    for (int i = 0; i < m; i++)
        rod[i] = read();

    for (int i = 0; i < 2; i++)
    {
        prepare();

        for (int j = i; j < n; j += 2)
        {
            int dis = Calc(i, j); //当前钉子与前一个或后一个的距离

            for (int k = 0; k < m; k++)
            {
                if (!vis[k] && rod[k] == dis)
                {
                    vis[k] = true;
                    ans[j] = k + 1;
                    break;
                }
            }

            if (ans[j] == -1)
            {
                flag = false;
                break;
            }
        }
        if (flag)
            break;
    }
    if (flag)
    {
        printf("YES\n%d", ans[0]);

        for (int i = 1; i < n; i++)
            printf(" %d", ans[i]);
        puts("");
    }
    else
        printf("NO\n");
    return 0;
}
```


---

## 作者：vsidssa (赞：1)

## 分析：
- 每根必须弯折直角。
- 允许重叠。
- 弯折位置和两端都需要有钉子。
- 弯折位置的钉子上不能有别的棒。

## 思路：
理解题意后发现数据范围不大，直接暴力。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int x[100005], y[100005], mp[100005], v[100005], dact[100005], dafl, n, m;
int caf(int i, int j) {
	return abs(x[i] - x[j]) + abs(y[i] - y[j]);
}
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++ i) {
		cin >> x[i] >> y[i];
	}
	for (int i = 1; i <= m; ++ i) {
		cin >> mp[i];
	}
	x[n + 1] = x[1], y[n + 1] = y[1];
	x[0] = x[n], y[0] = y[n];
	for (int t = 1; t <= 2; ++ t) {
		memset(v, 0, sizeof v);
		memset(dact, -1, sizeof dact);
		dafl = 0;
		for (int i = t; i <= n; i += 2) {
			int csl = caf(i, i - 1) + caf(i, i + 1);
			for (int j = 1; j <= m; j++) { //遍历所有金属棒
				if (v[j] == 0 && mp[j] == csl) {
					v[j] = 1;
					dact[i] = j;
					break;
				}
			}
			if (dact[i] == -1) dafl = 1;
		}
		if (dafl == 0) {
			cout << "YES\n";
			for (int i = 1; i <= n; ++ i) cout << dact[i] << ends;
			return 0;
		}
	}
	cout << "NO";
}

```


---

## 作者：Peter20122012 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF28A)

## 思路
由于要按顺序使用钉子，且钉子都得用，所以只要确定了中间钉子就可以知道另两根钉子的编号。那么可以从 $1$ 和 $2$ 分别开始枚举，每隔一个钉子枚举一个弯折点，再枚举铁棒，如果弯折钉子与端点钉子的距离和与这个铁棒的长度相等且这个铁棒没有用过就可以在这里弯折。

## AC Code
```cpp
/*
from:CF-28A
difficulty:1600
*/
#include<bits/stdc++.h>
using namespace std;

#define MAX(x, y) (((x) >= (y)) ?(x) :(y))
#define MIN(x, y) (((x) <= (y)) ?(x) :(y))
#define ABS(x) (((x) >= 0) ?(x) :(-x))
#define FOR(st, ed, i, stp) for (int i = (st); i <= (ed); i += stp)
#define RFOR(st, ed, i) for (int i = (ed); i >= (st); --i)
#define fir first
#define sec second

// #define debug

typedef long long ll;
typedef double db;
typedef pair<int, int> pii;

struct Node {
    int x, y;
};

const int maxn = 5e2 + 10;
const int maxm = 5e2 + 10;

int n, m;
Node a[maxn];
int len[maxm];

bool used[maxm];
int ans[maxn];
bool findans (int st) {
	memset(ans, 0xff, sizeof(ans));

    FOR (st, n, i, 2) {
		int need = abs(a[i].x - a[((i - 1 == 0) ?(n) :(i - 1))].x) + abs(a[i].y - a[((i - 1 == 0) ?(n) :(i - 1))].y) + abs(a[i].x - a[((i + 1 == n + 1) ?(1) :(i + 1))].x) + abs(a[i].y - a[((i + 1 == n + 1) ?(1) :(i + 1))].y);
		FOR (1, m, j, 1) {
			if (!used[j] && len[j] == need) {
				used[j] = true;
				ans[i] = j;
				break;
			}
		}
		
		if (ans[i] == -1) {
//			printf("%i %i %i %i\n", i, ((i - 1 == 0) ?(n) :(i - 1)), ((i + 1 == n + 1) ?(1) :(i + 1)), need);
			return true;
		}
	}
	
	printf("YES\n");
	FOR (1, n, i, 1) {
		printf("%i ", ans[i]);
	}
	printf("\n");
	return false;
}

int main () {
    scanf("%i%i", &n, &m);
    FOR (1, n, i, 1) {
        scanf("%i%i", &a[i].x, &a[i].y);
    }
    FOR (1, m, i, 1) {
        scanf("%i", &len[i]);
    }
	
	if (findans(1) && findans(2)) {
		printf("NO\n");
	}
    return 0;
}
```

---

## 作者：_zhaosihan_qwq_ (赞：0)

# 题解：CF28A Bender Problem
## 题目大意：
有 $n$ 个钉子，从 $1-n$ 编号，有 $m$ 条铁棒，要求用这些铁棒和钉子围成一个封闭的折线。要求铁棒不一定全部用完，铁棒必须平行于坐标轴。现在他要把铁棒弯成直角，这样中间的折叠点一个钉子，两头各一个钉子，要求折叠的这颗钉子之前必须是没有别的棒连接的（也就是空钉子），问怎么选棒，棒只能用一次。
## 思路：
那么我们直接可以判断出，只要在这一个钉子的位置可以让铁棒弯曲，那么下一个钉子的位置的铁棒**一定不能弯曲**，蔗糖的解法才是最优解且合理。所以我们只需要判断当前钉子的位置奇偶性就行了。

---

## 作者：Jin_Yichen (赞：0)

看到题目：~~看不懂思密达~~ 完蛋了！~

看到数据：$N\le500$，我活了！！！

## PART1 题目大意
有 $n$ 个钉子，从 $1$ 到 $n$ 编号，有 $m$ 条铁棒，要求用这些铁棒和钉子围成一个封闭的折线。铁棒不一定全部用完，且必须平行于坐标轴。现在他要把铁棒弯成直角，这样中间的折叠点一个钉子，两头各一个钉子，要求折叠的这颗钉子之前必须是没有别的棒连接的（也就是空钉子），问怎么选棒，棒只能用一次。

## PART2 思路
每个铁棒占用三个钉子，枚举中间的钉子，也就是弯折处的钉子。假设弯折处的钉子为 $i$ 号钉子，那么与他相邻的两个钉子就分别是 $i+1$ 号钉子和 $i-1$ 号钉子。这样三个钉子中，$i-1$ 号钉子和 $i$ 号钉子的曼哈顿距离与 $i$ 号钉子和 $i+1$ 号钉子的曼哈顿距离和为铁棒的长度。先枚举弯折点，再计算距离和，看看有没有相同长度的铁棒即可。

## PART3 如何枚举弯折点
如果弯折点为 $i$ 号，那么相邻的钉子为 $i-1$ 号和 $i+1$ 号，下一个弯折点就在 $i+2$ 号。我们可以从 $1$ 开始枚举，如果不行就从 $2$ 号开始枚举，如果都不行，就说明没有答案，否则就输出答案。

## PART4 ~~你们最喜欢的东西~~ 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,len[505],vis[505],ans[505];
bool flag=false,t=false;
struct node{
	int x,y;
}a[505];
int ifcheck(int x,int y){
	int chax=abs(a[x-1].x-a[x].x)+abs(a[x+1].x-a[x].x);
	int chay=abs(a[x-1].y-a[x].y)+abs(a[x+1].y-a[x].y);
	return len[y]==chax+chay;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d%d",&a[i].x,&a[i].y);
	for(int i=1;i<=m;i++)scanf("%d",&len[i]);
	a[0].x=a[n].x,a[0].y=a[n].y;
	a[n+1].x=a[1].x,a[n+1].y=a[1].y;
	for(int i=1;i<=n;i+=2){
		flag=false;
		for(int j=1;j<=m;j++){
			if(vis[j]==false&&ifcheck(i,j)){
				flag=true,vis[j]=true,ans[i]=j;
				break;
			}
		}if(flag==false){t=true;break;}
	}
	if(t==false){
		printf("YES\n");
		for(int i=1;i<=n;i++){
			if(ans[i]==0)printf("-1 ");
			else printf("%d ",ans[i]);
		}
	} else {
		memset(vis,false,sizeof vis);
		memset(ans,0,sizeof ans);
		for(int i=2;i<=n;i+=2){
			flag=false;
			for(int j=1;j<=m;j++){
				if(vis[j]==false&&ifcheck(i,j)){
					flag=true,vis[j]=true,ans[i]=j;
					break;
				}
			}
		}if(flag==false){printf("NO");return 0;}
		printf("YES\n");
		for(int i=1;i<=n;i++){
			if(ans[i]==0)printf("-1 ");
			else printf("%d ",ans[i]);
		}
	}
	return 0;
}
```


---

