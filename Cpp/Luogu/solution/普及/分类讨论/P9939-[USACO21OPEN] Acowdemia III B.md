# [USACO21OPEN] Acowdemia III B

## 题目描述

Bessie 是一位忙碌的计算机科学研究生。然而，即使是研究生也需要交友。因此，Farmer John 开设了一片草地，目的是为了帮助 Bessie 与其他奶牛建立持久的友谊。

Farmer John 的草地可以被看做是由正方形方格组成的巨大二维方阵（想象一个巨大的棋盘）。每个方格用如下字符标记：

 - `C`，如果这个方格中有一头奶牛。
 - `G`，如果这个方格中有草。
 - `.`，如果这个方格既没有奶牛也没有草。

对于两头想要成为朋友的奶牛，她们必须选择在一个与她们均水平或竖直方向上相邻的有草方格见面。在这个过程中，她们会在这个有草方格中吃草，所以之后的奶牛不能再使用这个方格作为见面地点。一头奶牛可以与多头其他奶牛成为朋友，但是同一对奶牛不能见面并成为朋友多于一次。

Farmer John 希望有许多奶牛可以见面并成为朋友。请求出当这一活动结束时在奶牛之间可以建立的朋友关系的最大数量。 

## 说明/提示

### 样例解释 1

如果我们用坐标 $(i,j)$ 标记第 $i$ 行第 $j$ 列的奶牛，则在这个样例中于 $(1,2)$、$(1,5)$、$(2,2)$、$(2,4)$、$(3,1)$、$(3,3)$、$(4,2)$、$(4,3)$ 以及 $(4,5)$ 
存在奶牛。一种使四对奶牛成为朋友的方式如下：

 - 位于 $(2,2)$ 和 $(3,3)$ 的奶牛于 $(3,2)$ 一起吃草。
 - 位于 $(2,2)$ 和 $(2,4)$ 的奶牛于 $(2,3)$ 一起吃草。
 - 位于 $(2,4)$ 和 $(3,3)$ 的奶牛于 $(3,4)$ 一起吃草。
 - 位于 $(2,4)$ 和 $(1,5)$ 的奶牛于 $(2,5)$ 一起吃草。


### 测试点性质

 - 测试点 $2-4$ 满足 $N=2$。
 - 测试点 $5-12$ 没有额外限制。

## 样例 #1

### 输入

```
4 5
.CGGC
.CGCG
CGCG.
.CC.C```

### 输出

```
4```

# 题解

## 作者：hyxgg (赞：3)

### [题目](https://www.luogu.com.cn/problem/P9939)
我们考虑两只奶牛吃一格草的形式，
显然大体可以分为两类：

$1$：

![](https://cdn.luogu.com.cn/upload/image_hosting/lekbul3y.png)

如上图，两只牛一个横向移动，另一个纵向移动。

$2$：

![](https://cdn.luogu.com.cn/upload/image_hosting/w4w440ez.png)

如上图，俩牛都横向或纵向移动。

易发现，第二种情况下，两只牛不可能在其他草地发生关系，第一种情况中两只牛则可能有两快草地供选择

采取贪心的策略，先将所有情况二的奶牛对和草地处理掉，再考虑第一种情况。

可以发现如果一块草地周围如果有两对以上的情况一的奶牛对，就一定会形成情况二，而情况二的草地已经被处理过了。所以现在每块草地的周围至多有一对情况一中的奶牛对。

此时我们只需要找到所有周围有草地的形如情况一的奶牛对，再加上它们的个数就行了。

```
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
ll n,m,cd[1005][1005];
int main(){
    scanf("%lld%lld",&n,&m);
    char c;
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=m;j++){
            cin>>c;
            cd[i][j]=(c=='G')?1:((c=='C')?2:0);
        }
    }
    ll ans=0;
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=m;j++){
            if(cd[i][j]==1){
                if(i>1&&i<n){
                    if(cd[i-1][j]==2&&cd[i+1][j]==2){
                        ans++,cd[i][j]=0;
                        continue;
                    }
                }
                if(j>1&&j<m){
                    if(cd[i][j-1]==2&&cd[i][j+1]==2){
                        ans++,cd[i][j]=0;
                    }
                }
                    
            }
        }
    }//情况一
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=m;j++){
            if(i>1&&j>1){
                if(cd[i-1][j]==2&&cd[i][j-1]==2){
                    if(cd[i-1][j-1]==1||cd[i][j]==1){
                        ans++;
                    }
                }
            }
            if(i>1&&j<m){
                if(cd[i-1][j]==2&&cd[i][j+1]==2){
                    
                    if(cd[i-1][j+1]==1||cd[i][j]==1){
                        ans++;
                    }
                }
            }
        }
    }//情况二
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：I_Upgraded_Alone_Wzq (赞：2)

**P9939 [USACO21OPEN] Acowdemia III B 题解**

这是一道 USACO 铜组的数据结构黄题。

1. 题目不难理解，就是问在一片草地中，找出一共有多少对牛往上下左右四个方向走，能吃到同一棵草。

2. 总体思路就是先找到一棵草，看上下左右有没有牛。

3. 如果有多于两只牛，肯定能成为一对。

4. 如果正好有两头牛，用数据结构记录这一对牛，如果重复就不记录。

5. 否则，跳过。

###### 话不多说，思路在 C + + 代码里。
```cpp
#include<bits/stdc++.h>
using namespace std;
int Map[1005][1005];    //地图。
int N, M, Ans = 0;
map<vector<pair<int, int> >, int> v;    //用来存储一对一对的奶牛。
int main() {
    memset(Map, -1, sizeof(Map));    //初始状态不为草也不为奶牛。
    //输入。
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            char ch;
            cin >> ch;
            if (ch == 'G') Map[i][j] = 0; //当前变量为草。
            if (ch == 'C') Map[i][j] = 1; //当前变量为牛。
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (Map[i][j] == 0) {    //当前变量为草。
                int Cow_Count = 0;    //草附近有多少奶牛。
                vector<pair<int, int> > cows;
                if (i + 1 <= N && Map[i + 1][j] == 1) { Cow_Count++; cows.push_back({i + 1, j}); }    //往下看。
                if (j + 1 <= M && Map[i][j + 1] == 1) { Cow_Count++; cows.push_back({i, j + 1}); }    //往右看。
                if (i - 1 >= 1 && Map[i - 1][j] == 1) { Cow_Count++; cows.push_back({i - 1, j}); }    //往上看。
                if (j - 1 >= 1 && Map[i][j - 1] == 1) { Cow_Count++; cows.push_back({i, j - 1}); }    //往左看。
                if (Cow_Count > 2) Ans++; // 当旁边有多于两头牛。
				else if (Cow_Count == 2) { // 当旁边正好有两头牛。
                    sort(cows.begin(), cows.end());
                    v[cows]++; //记录每对奶牛。
                }
            }
        }
    }
    cout << Ans+v.size() << '\n'; // 旁边多于两只牛的草的个数加一共有多少对牛。
    return 0;
}
```

---

## 作者：Rannio (赞：2)

### 题意
题目说的还算清楚就不翻译了。

### 思路
奶牛的朋友关系尽可能多就代表我们要利用尽可能多的草。

一格草能被利用有以下两种情况：
- 上下或左右各有一头牛
- 上或下有一头牛且左或右有一头牛

对于第一种情况，我们枚举草的位置，如果某格草上下或左右各有一头牛，我们就将这个草删除并将答案加 $1$。

对于第二种情况，我们枚举其中一头牛的位置，设它的在数组中的位置为 $(x,y)$：
- 当 $(x+1,y-1)$ 为牛且 $(x+1,y)$ 或 $(x,y-1)$ 为草时，将其中一个草删除并将答案加 $1$。
- 当 $(x+1,y+1)$ 为牛且 $(x+1,y)$ 或 $(x,y+1)$ 为草时，将其中一个草删除并将答案加 $1$。

注意到我们是先处理第一种情况，因为这样可以避免类似于下方数据的数据对答案产生影响：
```
.C.
CGC
.CG
```
在上方数据中，如果先处理第二种情况，可能会将 $(2,2)$ 的草删除，从而使得 $(2,1)$ 和 $(2,3)$ 或 $(1,2)$ 和 $(3,2)$ 的奶牛无法形成朋友关系。

时间复杂度 $\Theta(nm)$。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int ans;
int cr[1005][1005];
signed main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char op;
            cin>>op;
            cr[i][j]=op=='C'?1:op=='G'?2:0;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(cr[i][j]==2){
                if(cr[i-1][j]==1&&cr[i+1][j]==1||cr[i][j-1]==1&&cr[i][j+1]==1) cr[i][j]=0,ans++;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(cr[i][j]==1&&cr[i+1][j-1]==1){
                if(cr[i][j-1]==2) cr[i][j-1]=0,ans++;
                else if(cr[i+1][j]==2) cr[i+1][j]=0,ans++;
            }
            if(cr[i][j]==1&&cr[i+1][j+1]==1){
                if(cr[i][j+1]==2) cr[i][j+1]=0,ans++;
                else if(cr[i+1][j]==2) cr[i+1][j]=0,ans++;
            } 
        }
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：cly312 (赞：1)

考虑贪心。

遍历每只奶牛：
- 如果它最多与一头奶牛相邻，那么什么都不会发生。 
- 如果它与两头以上的奶牛相邻，那么它与两侧的两头奶牛相邻。将答案递增 $1$。 
- 否则，如果正好有两头相邻的奶牛，我们就把它们配对。也就是说，将这对奶牛插入一组。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,ans;
char a[1010][1010];
const int dx[]={-1,0,1,0},dy[]={0,-1,0,1};
int main(){
    scanf("%d%d",&n,&m);
    map<vector<pair<int,int>>,int> p;
    for(int i=1;i<=n;i++)scanf("%s",a[i]+1);
    for(int i=1;i<=n;i++){
    	for(int j=1;j<=m;j++){
            if(a[i][j]!='G') continue;
            vector<pair<int,int>>v;
            for(int d=0;d<4;d++){
                int x=i+dx[d],y=j+dy[d];
                if(a[x][y]=='C')v.push_back({x, y});
            }
            if(v.size()<2)continue;
            if(v.size()>2)ans++;
            if(v.size()==2){
                if(v[0]>v[1])swap(v[0],v[1]);
                p[v]=1;
            }
        }
	}
    printf("%d",ans+p.size());
    return 0;
}

```

---

## 作者：paramecium_ (赞：0)

# 好题！

题意很清晰了，不过多解释了。

## 思路

两头牛要想成为朋友，共需考虑三种情况:

1. 两头牛在斜对角（如图所示）

![](https://cdn.luogu.com.cn/upload/image_hosting/ji0xue6o.png)

2. 两头牛在同一直线上（如图所示）

![](https://cdn.luogu.com.cn/upload/image_hosting/vp73tleo.png)

3. 两头牛在同一竖线上（如图所示）

![](https://cdn.luogu.com.cn/upload/image_hosting/nozyna9v.png)

对于情况 $2$ 和 $3$，直接特判即可，对于情况 $1$，只需要判断每个草有没有两头不在同一条线的牛吃就可以了。

但是值得注意的是，情况 $1$ 可能会有重复判的情况,只需特判减掉即可（情况如图所示）

![](https://cdn.luogu.com.cn/upload/image_hosting/h3bqbtsm.png)

## code

```cpp
#include<bits/stdc++.h>

using namespace std;
const int N = 1005;

char a[N][N];
int n, m;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int main(){
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		cin >> (a[i] + 1);
	}
	int ans = 0;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(a[i][j] == 'G' && a[i + 1][j] == 'C' && a[i - 1][j] == 'C'){//一条直线
				a[i][j] = '.';
				ans++;
			}
			if(a[i][j] == 'G' && a[i][j + 1] == 'C' && a[i][j - 1] == 'C'){//一条竖线
				a[i][j] = '.';
				ans++;
			}
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(a[i][j] == 'G'){//斜对角
				int cnt = 0;
				for(int g = 0; g < 4; g++){
					int x = dx[g] + i;
					int y = dy[g] + j;	
					if(a[x][y] == 'C'){
						cnt++;
					}
				}
				if(cnt >= 2){
					ans++;
				}
			}
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){//特判重复算
			if(a[i][j] == 'C' && a[i][j + 1] == 'G' && a[i + 1][j] == 'G' && a[i + 1][j + 1] == 'C') ans--;
			if(a[i][j] == 'G' && a[i][j + 1] == 'C' && a[i + 1][j] == 'C' && a[i + 1][j + 1] == 'G') ans--;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：44i11 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9939)

## 题目分析

若牛 $x$ 能与牛 $y$ 成为朋友，仅当牛 $x$ 的位置和牛 $y$ 的位置满足下面 $2$ 种情况。

1. 牛 $x$ 和 牛 $y$ 在同一行或同一列且 $x$ 和 $y$ 之间有且仅有一格草，如下图所示：
![](https://cdn.luogu.com.cn/upload/image_hosting/q9ra281i.png)
2. 草在其中一头牛的上边或下边，并在另一头牛的左边或右边，如下图所示：
![](https://cdn.luogu.com.cn/upload/image_hosting/1d8pj0uv.png)

## 解题思路

可枚举一个点 $(x,y)$ 。

* 判断 $(x,y + 1)$ 是否为草且 $(x,y + 2)$ 为牛，若满足，则答案 $ + 1$；
* 判断 $(x + 1,y)$ 是否为草且 $(x + 2,y)$ 为牛，若满足，则答案 $ + 1$；
* 判断 $(x,y - 1)$ 是否为草且 $(x + 1,y - 1)$ 为牛，若满足，则答案 $ + 1$；
* 判断 $(x + 1,y)$ 是否为草且 $(x + 1,y - 1)$ 为牛，若满足，则答案 $ + 1$；
* 判断 $(x,y + 1)$ 是否为草且 $(x + 1,y + 1)$ 为牛，若满足，则答案 $ + 1$；
* 判断 $(x + 1,y)$ 是否为草且 $(x + 1,y + 1)$ 为牛，若满足，则答案 $ + 1$；

## 代码

```cpp
#include<bits/stdc++.h>
#include<map>
using namespace std;
typedef long long ll;
const ll N = 1e3 + 5;
ll n, m, ans, dd[3][2] = {{2, 0}, {0, 2}};
char c[N][N];
bool check(ll x, ll y){
	return x >= 1 && y >= 1 && x <= n && y <= m;//判断是否越界
}
int main(){
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			cin >> c[i][j];
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(c[i][j] != 'C'){
				continue;
			}			
			for(int k = 0; k < 2; k++){//第一种情况
				ll ii = dd[k][0] + i;
				ll jj = dd[k][1] + j;
				if(check(ii, jj) && c[ii][jj] == 'C'){
					if(k == 0){
						if(c[ii - 1][jj] == 'G'){
							c[ii - 1][jj] = '.';//牛吃完草了
							ans++;
						}
					}
					if(k == 1){
						if(c[ii][jj - 1] == 'G'){
							c[ii][jj - 1] = '.';
							ans++;
						}
					}
				}
			}
			for(int k = -1; k <= 1; k += 2){//第二种情况
				ll ii = i + 1;
				ll jj = j + k;
				if(check(ii, jj) && c[ii][jj] == 'C'){
					if(c[i][jj] == 'G'){
						ans++;
						c[i][jj] = '.';
					}else if(c[ii][j] == 'G'){
						ans++;
						c[ii][j] = '.';
					}
				}
			}
		}
	}
	cout << ans;
	return 0;
}
```

---

