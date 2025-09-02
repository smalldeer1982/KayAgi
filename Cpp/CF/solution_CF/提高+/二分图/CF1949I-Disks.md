# Disks

## 题目描述

# 圆盘


你在平面上有 $ n $ 个圆盘。每个圆盘的中心具有整数坐标，每个圆盘的半径为正整数。没有两个圆盘在一个正面积的区域重叠，但圆盘之间可能相切。

你的任务是确定是否可以改变圆盘的半径，使得：

- 原来相切的圆盘仍然相切。
- 没有两个圆盘在一个正面积的区域重叠。
- 所有半径的总和严格减小。

新的半径可以是任意正实数。不能改变圆盘的中心。

## 说明/提示

在第一个样例中，可以将第一个和第三个圆盘的半径减小 $ 0.5 $ ，将第二个圆盘的半径增加 $ 0.5 $ 。这样，所有半径的总和减小了 $ 0.5 $ 。改变半径前后的情况如下图所示。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1949I/1f564e55d56b152b57e25e4b9913f6abfe12e4f8.png) 第一个样例（左）和改变圆盘半径的有效方法（右）。在第二个样例中，如下图所示，无法按照要求改变圆盘的半径。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1949I/160a9b50ca0114a94aa27312025cf229be0abcc8.png) 第二个样例。

## 样例 #1

### 输入

```
5
0 2 1
0 0 1
4 -3 4
11 0 3
11 5 2```

### 输出

```
YES```

## 样例 #2

### 输入

```
4
2 2 2
7 2 3
7 7 2
2 7 3```

### 输出

```
NO```

# 题解

## 作者：江户川·萝卜 (赞：10)

两圆相切，有圆心距离等于两圆半径之和。

所以其中一圆的半径减 $x$ 后，另一圆的半径需加 $x$，反之亦然。

所以考虑把圆抽象成点，给所有相切的圆对连边，建出无向图。

考察每个连通块，把 $-x$ 的点染成黑，$+x$ 的点染成白，我们声称若黑白染色合法（即形成一个二分图）且黑点数量不等于白点数量，则此处存在一个合法方案。

若白点数量小于黑点，则总和减少；

若黑点数量小于白点数量则黑白反色，总和依然减少。

此处 $x$ 可以是任意正实数，取 $\varepsilon$ 即可保证不会有新圆相切甚至相交。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int maxn=1005;
int n,x[maxn],y[maxn],r[maxn];
vector<int> e[maxn];
inline ll sq(ll x){return x*x;}
int f,cnt[2],vis[maxn];
void dfs(int p,int w){
    if(~vis[p]) return f&=(vis[p]==w),void();
    vis[p]=w,cnt[w]++;
    for(auto x:e[p]) dfs(x,!w);
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n;for(int i=1;i<=n;i++) cin>>x[i]>>y[i]>>r[i];
    for(int i=1;i<=n;i++)
    for(int j=i+1;j<=n;j++){
        if(sq(x[i]-x[j])+sq(y[i]-y[j])<=sq(r[i]+r[j])){
            e[i].push_back(j);
            e[j].push_back(i);
        }
    }
    memset(vis,-1,sizeof vis);
    for(int i=1;i<=n;i++) if(!~vis[i]){
        f=1;cnt[0]=cnt[1]=0;
        dfs(i,0);
        if(f&&cnt[0]!=cnt[1]) return puts("YES"),0;
    }
    puts("NO");
    return 0;
}
```

---

## 作者：WuMin4 (赞：1)

## [CF1949I Disks](https://codeforces.com/contest/1949/problem/I)

## 题意

平面直角坐标系上有 $n\pod {1\le n\le 1000}$ 个圆。任意两个圆没有相交关系。请问能否改变一些圆的半径，使得没有圆有相交关系，原来相切的圆现在仍然相切，且半径之和减小。

## 思路

这题评蓝？

因为半径改变大小任意，所以只有相切的圆才会相互影响，于是我们将相切的圆连边，再对每个连通块单独考虑。

这里给出一个重要的结论：两个圆若圆心不变且相切，则半径之和等于圆心距离。于是对于相切的两个圆，若一个圆半径减小，另一个圆半径一定增大，且增减量相等。

于是我们可以将圆分为两类：半径减小的圆和半径增大的圆，也就是构造二分图。对于半径减小的圆，跟它有连边的圆一定为半径增大的圆，反之亦然。当出现矛盾时，则不能改变半径大小。

以上过程即为二分图判定过程。

构造出二分图后，任意一类点都可以成为半径减小的圆，我们考虑让点数更多的一类点成为半径减小的圆，这样可以使得减少量大于增加量。当点数相等时，该连通块增减量相等，也不能改变半径之和的大小。

于是我们将所有相切的圆连边，并对每个连通块判定二分图，若某个连通块为二分图且两类点数不相等，答案即为 `YES`，否则为 `NO`。

注意开 `long long`。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,col[1005],cc[2],ans;
struct node{
	int x,y,d;
}a[1005];
vector<int> t[1005];
bool is_cut(node x,node y){
	return (x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y)==(x.d+y.d)*(x.d+y.d);
}
void dfs(int x,int c){
	col[x]=c,cc[c]++;
	for(int v:t[x]){
		if(col[v]==-1)
			dfs(v,c^1);
		else if(col[v]!=(c^1))
			ans=0;
	}
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	memset(col,-1,sizeof(col));
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].x>>a[i].y>>a[i].d;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(is_cut(a[i],a[j]))
				t[i].push_back(j),t[j].push_back(i);
		}
	}
	for(int i=1;i<=n;i++){
		if(col[i]==-1){
			cc[0]=cc[1]=0;ans=1;dfs(i,0);
			if(ans&&cc[0]!=cc[1]){
				cout<<"YES"<<endl;
				return 0;
			}
		}
	}
	cout<<"NO"<<endl;
	return 0; 
}
```

---

