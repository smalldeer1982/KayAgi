# Bicoloring

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=945

[PDF](https://uva.onlinejudge.org/external/100/p10004.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10004/09f718cb383e213e651b85dfd47bb80608f88609.png)

## 样例 #1

### 输入

```
3
3
0 1
1 2
2 0
3
2
0 1
1 2
9
8
0 1
0 2
0 3
0 4
0 5
0 6
0 7
0 8
0```

### 输出

```
NOT BICOLORABLE.
BICOLORABLE.
BICOLORABLE.```

# 题解

## 作者：_zhy (赞：4)

[link](https://www.luogu.com.cn/problem/UVA10004)。

## 题目大意

~~好像题目已经描述得够清楚了。~~

有一张 **有向图** ，我们要用两种不同颜色去给每个点染色。

问是否可以满足任意两个相邻点之间都有不同颜色。

## 思路

一看到数据范围：${2 \leq n \leq 199}$，我就想到这道题可以使用暴力进行求解。

本题是一道无向图的染色问题。

我们可以用搜索遍历每一个点，并给它们用数组 ${color}$ 记录颜色（${0}$ 和 ${1}$）。

最后枚举每个点的相邻点，若有相邻点颜色相同，则将 $flag$ 从 `true` 置为 `false`，并输出；若枚举完后，$flag$ 若还为 `true` 则输出有解。

先把这张图用邻接表（邻接矩阵）存下来，~~链式前向星没必要了吧~~，再进行搜索，因为是无向图所以要双向存边。

**注意：题目是多组数据，每次运算前一定要初始化。**

代码中附有注释。

## code
```cpp
#include <cstdio>
#include <vector>

const int N = 205;

using namespace std;

int n, m;
vector<int> G[N];
bool vis[N], color[N], flag;

inline void dfs(int now, int now_color) {
	color[now] = now_color;
	for (auto i : G[now])	//遍历当前结点 now 的相邻点。
		if (!vis[i])
			vis[i] = true, dfs(i, now_color ^ 1);	//异或（^）是精髓，0 ^ 1 为 1，1 ^ 0 为 0，正好达到了相邻点染不同颜色的目的。
}

int main() {
	while (scanf("%d", &n) && n) { 
		scanf("%d", &m);
		for (int i = 0; i < n; i++)
			G[i].clear(), vis[i] = false;	//color 数组没次都会在搜索中被赋值，所以不必初始化。 
		for (int i = 1, a, b; i <= m; i++)
			scanf("%d %d", &a, &b), G[a].push_back(b), G[b].push_back(a);
		vis[0] = true;
		dfs(0, 1);
		flag = true;
		for (int i = 0; i < n && flag; i++)
			for (auto it : G[i])
				if (color[i] == color[it]) {
					puts("NOT BICOLORABLE.");
					flag = false;
					break;
				}
		if (flag)
			puts("BICOLORABLE.");
	}
	return 0;
}
```

---

## 作者：mavic (赞：2)

#### 这道题就是一个简单的二分图染色~~就是个模板~~

什么是二分图呢？简单来讲就是如果将图中的所有点染成或黑或白两种颜色，若图中如果所有的边的两个端点颜色都不同，则称此图为二分图。

而对图的染色可以用dfs来实现：

```
#include<cstdio>
#include<iostream>
#include<vector>
#include<cstring>
#define maxn 206
using namespace std;
vector<int>g[maxn];//可变数组简单实现
int color[maxn];
int bipartite(int u){
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(color[v]==color[u])return 0;//如果已经有相邻两点颜色相同则返回false
		if(!color[v]){
			color[v]=3-color[u];//前一个颜色为1，则当前点颜色赋为2；前一个为2，当前则赋1
			if(!bipartite(v))return 0;//dfs
		}
	}
	return 1;//如果全图都符合二分图的定义则返回真
}
int main(){
	int n,m;
	while(1){
		memset(color,0,sizeof(color));
		memset(g,0,sizeof(g));
		cin>>n;
		if(!n)break;//判断结束
		cin>>m;
		for(int i=0;i<m;i++){
			int u,v;
			cin>>u>>v;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		color[0]=1;
		bipartite(0)==1?cout<<"BICOLORABLE.":cout<<"NOT BICOLORABLE.";
		cout<<endl;
	}	
	return 0;
}
```

---

## 作者：CQ_Bab (赞：1)

# 思路
一眼二分图，我们首先可以对于这个图进行染色法染色，然后判断一下相连边的两个点的颜色是否相同即可。

这里的染色法也是模板，没什么好讲的，若不会的人[请点击这里](https://www.luogu.com.cn/problem/B3605)，学习一下再来。

# 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
using namespace std ;
int n;
int m;
vector<int>v[1001000];
int vis[2001000];
int c[200100];
void dfs(int x,int co) {//模板，不讲
	c[x]=co;
	for(auto y:v[x]) {
		if(!vis[y]) {
			vis[y]=1;
			dfs(y,1-co);
		}
	}
}
signed main() {
	while(cin>>n,n) {
		cin>>m;
		rep(i,0,n-1) v[i].clear(),vis[i]=0;
		rep(i,1,m) {
			int x,y;
			cin>>x>>y;
			v[x].push_back(y);
			v[y].push_back(x);
		}
		vis[0]=1;
		dfs(0,1);
		bool f=1;
		rep(i,0,n-1) {
			if(!f) break;
			for(auto x:v[i]) {
				if(c[i]==c[x]) {//判断连边两点的颜色是否相同
					puts("NOT BICOLORABLE.");
					f=0;
					break;
				}
			}
		}
		if(f) puts("BICOLORABLE.");
	}
	return false;
}

```

---

## 作者：炎炎龙虾 (赞：1)

# 二分图的判定

Author: 炎炎龙虾
Created: Jul 26, 2020 3:13 PM

## 定义：

首先，什么是二分图？

百度百科上的定义是：“设$G=(V,E)$是一个无向图，如果顶点$V$可分割为两个互不相交的子集$(A,B)$，并且图中的每条边$(i，j)$所关联的两个顶点$i$和$j$分别属于这两个不同的顶点集$(i\in{A},j\in{B})$，则称图G为一个二分图。”

通俗点说，如果一个无向图所有的点可以分成两个部分，每个部分内部都没有边相连。

什么意思呢？举个例子吧。

![](https://www.notion.so/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2Fbe91ed78-2dd2-4289-8b9c-f495710d02b6%2Fgraph_(2).png?table=block&id=3af1e266-2cd5-4837-b1d1-11c02d2c8e37&width=2730&cache=v2)


上图就是一个典型的二分图，图可以分成两个部分，一个是$\{1,2,3\}$，另一个是$\{4,5,6\}$。这两个部分内部都没有边相连，$1,2$不连通，$2,3$不连通，$3,4$不连通，右半部分同理。

再举一个例子:

![](https://www.notion.so/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2Fa74168a8-fb37-4394-a9b1-f2bf71234179%2Fgraph_(3).png?table=block&id=2a16da3b-0f2f-4a31-bcd2-9b6579a64a37&width=2730&cache=v2)


这就不是一个二分图，大家可以自行枚举，至于它为什么不是二分图，马上就讲。

## 定理：

一个无向图是二分图的**充分必要条件**就是该图内的每一个环的长度都是偶数。

$①$先证明必要性。假设有一个环$C$长度为$s$，包含s个节点$\{v_1,v_2,v_3,...,v_s\}$。可以将这个环单独剖离出来，看做一个待判定的图（若一个图子图不是二分图，则该图也一定不是二分图）。可以采用摇摆法，不妨设该环可以分为$V_1$和$V_2$（注意大小写）两个内部互不相交的点集，$v_1\in{V_1}$。则必然$v_2\in{V_2}$。归纳一下，得到：

![](https://www.notion.so/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2Fec57c9f0-39b2-4fd3-a75a-97e60aa9637e%2FUntitled.png?table=block&id=ba177517-d906-4f6c-bbaa-29f6f4d63e6a&width=2730&cache=v2)

由此可以发现，若该环是二分图，则$s-1$一定是奇数，$s$一定是偶数，因此定理中的必要性得证。

$②$可以采用摇摆法加反证法。为了简化原问题并不影响结果，我们可以假设图$G$是一个连通图。假设该图内每一个环的长度都是偶数，因此我们可以定义该图的两个子集分别为$V_1$和$V_2$，对于任意的$v\in{V_1}$，$V_1\{v|v_i与v的距离为偶数\}，$$V_2$同理。为了证明$V_1$内部没有边相连接，就可以采用反证法。假设$v_i,v_j\in{V_1}$，且存在一条边$(v_i,v_j)$。由前面的假设可知，$v$与$v_i$之间的距离为偶数，$v$与$v_j$之间的距离也为偶数，而$v_i$与$v_j$之间的距离为$1$，因此，有$v$，$v_i$和$v_j$构成的环的长度就是奇数，与所给条件不符，因此假设不成立，因此必要性得证。

有了这个定理，再看看上面的那个图，会发现由$\{1,4,3,6,5\}$构成的环的长度为奇数，因此，那不是一个二分图。

好了，上面讲了这个定理，证明了这么久，有什么用吗？很抱歉地告诉你，并没有，但是你可以跟朋友秀一下“不打草稿肉眼判定二分图”，相信只会**染色法**的你的朋友一定会大吃一惊的。

## 实现：

刚刚提到了染色法，染色法是什么？

举个例子吧，可以自己体会一下。还是刚刚那个图：

![](https://www.notion.so/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2Fb47abbe4-44cc-4eed-aed3-7cec8c5560ab%2FUntitled.png?table=block&id=24690b10-8519-484c-9124-e2005a75f425&width=2730&cache=v2)

从一号节点开始，染上红色

![](https://www.notion.so/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2F75346a65-5685-422c-9561-2776e16aba9e%2FUntitled.png?table=block&id=2fac08af-4976-4f2e-b0ed-37b2ccadc8af&width=2730&cache=v2)

遍历所有与$1$相邻的节点，染上另一种颜色。

![](https://www.notion.so/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2Fefd7465a-d200-4295-832f-f23e5e5afc28%2FUntitled.png?table=block&id=72e1e4c6-c935-481d-bb87-b172b4fbc311&width=2730&cache=v2)

在遍历$4,5$，染色时发现出现了相邻的边染上了同种颜色的情况，因此判定它不是二分图。

由此，可知一个无向图是二分图的充要条件就是可二着色（可以用两种颜色染出来）。

还可以推广一下：一个无向图是$n$分图的充要条件就是可$n$着色（可以用$n$种颜色染出来）。

~~仿佛就是小学奥数里的染色问题。~~

UVA上有一道模板题：

[Online Judge](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=945)

[Bicoloring](https://www.luogu.com.cn/problem/UVA10004)

下面直接附上代码吧，就是深搜染色：

```cpp
//
// Created by admin on 2020/7/21.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,color[300];
vector<int> no[300];
bool h;
bool dfs(int x,int c)
{
    color[x]=c;
    for(int i=0;i<no[x].size();i++)
    {
        int y=no[x][i];
        if(color[y]==c)//相邻边染上了同种颜色
            return false;
        if(color[y]==0&&!(dfs(y,-c)))//只要有一个点无法染色，全部返回false
            return false;
    }
    return true;
}
int main()
{
    while (true)
    {
        h=false;
        memset(no,0,sizeof(no));
        memset(color,0,sizeof(color));
        cin>>n;
        if(n==0)
            break;
        cin>>m;
        int x,y;
        for(int i=1;i<=m;i++)
        {
            cin>>x>>y;
            no[x].push_back(y);
            no[y].push_back(x);
        }
        for(int i=1;i<=n;i++)
            if(color[i]==0)//没有染色（原图不一定连通，一次染色不一定能染上全部）
            {
                if(!dfs(i,1))
                {
                    h=true;
                    break;
                }
            }
        if(h)
            cout<<"NOT BICOLORABLE."<<endl;
        else
            cout<<"BICOLORABLE."<<endl;
    }
    return 0;
}
```

UVA上还有一题，近似于模板：

[Online Judge](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=17&page=show_problem&problem=1446)

[Montesco vs Capuleto](https://www.luogu.com.cn/problem/UVA10505)

再附上代码：

```cpp
//
// Created by admin on 2020/7/21.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,color[4000],tot,colored;
vector<int> no[4000];
bool b;
void dfs(int x,int c)
{
    color[x]=c;
    tot++;
    if (c==1)
        colored++;
    for(int i=0;i<no[x].size();i++)
    {
        int y=no[x][i];
        if (color[y]==0)
            dfs(y,-c);
        else
            if(color[y]==c)
                b=false;
    }
}
int main()
{
    int t;
    cin>>t;
    while (t--)
    {
        int ans=0;

        memset(no,0,sizeof(no));
        memset(color,0,sizeof(color));
        cin>>n;
        int x;
        for (int j = 1; j <=n; ++j)
        {
            cin>>m;
            for(int i=1;i<=m;i++)
            {
                cin>>x;
                if(x>n)
                    continue;
                no[j].push_back(x);
                no[x].push_back(j);
            }
        }
        for(int i=1;i<=n;i++)
            if(color[i]==0)
            {
                tot=colored=0;
                b=true;
                dfs(i,1);
                if(b)
                    ans+=max(colored,tot-colored);
            }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：Lovage (赞：1)

# ~~老师说的水题~~

很神奇的做法

~~充分体现了递归完全看不懂的精髓~~

解释一下第十五排-c：

因为这里只用两种颜色，因此我们可以用相反数使代码~~少写三排~~更加简洁

~~我永远不会说这是老师讲的~~


------------
```cpp
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
const int MAXN = 20005;
int n,m,k,ans,color[MAXN];
vector <int> a[MAXN]; //用邻接表存储要省空间
void push_ (int from,int to){//懒人函数
	a[from].push_back(to);
}
bool dfs (int x,int c){//神奇的函数 x表示点 c表示颜色
	color[x] = c;//存储颜色
	for(int i = 0;i < a[x].size();++i){
		if(color[a[x][i]] == c) return false; //如果相邻顶点颜色相同则不行
		if(color[a[x][i]] == 0 and !dfs(a[x][i],-c)) return false;
        //如果相邻顶点没有标记但用另一种颜色dfs返回为false也不行
	}
	return true;//清除完雷区安全通过
}
int main(){
	while(scanf("%d",&n)){//多组数据
		if(n == 0) break;
		memset(a,0,sizeof(a));//每回都要清空数组，不然爆零
		memset(color,0,sizeof color); 
		scanf("%d",&m);
		for(int i = 1;i <= m; ++i){
			int l,j;
			scanf("%d %d",&l,&j);
			push_(l,j);//由于是无向图，两端都要存储
			push_(j,l);
		}
		if(!dfs(0,1))  printf("NOT BICOLORABLE\n"); //因为只有两种颜色所以颜色不影响结果
		else printf("BICOLORABLE\n");
	}
	
	return 0;
} 
```


---

## 作者：Spiritsu (赞：1)

简单的判断二分图，不过数组开小的我果然还是蒟蒻.....
直接上程序...（虽然是学校dalao教的）
```
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int n,m;
struct Edge{
	int v,next;
};
Edge e[41000];
int h[41000];
int color[20500];
int cnt=0;
void add(int u,int v){
	e[++cnt]=(Edge){v,h[u]};
	h[u]=cnt;
}
int dfs(int u){
	for(int i=h[u];i;i=e[i].next){
		int v=e[i].v;
		if(color[v]==color[u]) return 0;
		if(!color[v]){
			color[v]=3-color[u];
			if(!dfs(v)) return 0;
		}
	}
	return 1;
}
int main(){
	while(scanf("%d",&n)==1&&n){
		memset(e,0,sizeof(e));
		memset(h,0,sizeof(h));
		memset(color,0,sizeof(color));
		scanf("%d",&m);
		for(int i=1;i<=m;i++){
			int x,y;
			scanf("%d%d",&x,&y);
			add(x,y);
			add(y,x);
		}
		color[0]=1;
		if(dfs(0)) printf("BICOLORABLE.\n");
		else printf("NOT BICOLORABLE.\n");
	}
	return 0;
}
```
其中dfs的返回值0是不是二分图，1是是二分图，
color数组的数值0是未染色，1是一种颜色，2是另一种颜色，所以可以3-color[u]来给v染色，剩下就是普通深搜2333

---

## 作者：SunnyYuan (赞：0)

~~随机跳到的。~~

## 思路

这个是一个二分图的判定的模板题。

主要思路就是判断图中是否有奇环。

我们主要是对图进行染色。

相邻的两个点采取不同的颜色。

像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/877yhebw.png)

如果染色染到中途发现点 $u$ 和 点 $v$ 之间右边相连且颜色相同，说明出现矛盾（就可以返回并输出 `NOT BICOLORABLE.`）。

如果到最后都没有遇到错误，那么输出 `BICOLORABLE.`。

## 代码

```cpp
/*******************************
| Author:  SunnyYuan
| Problem: In 1976 the \Four Color Map Theorem " was proven with the assistance of a computer. This theorem - states that every map can be colored using only four colors, in such a way that no region is colored
| Contest: UVa Online Judge
| URL:     https://onlinejudge.org/external/100/p10004.pdf
| When:    2023-09-06 15:41:13
| 
| Memory:  1024 MB
| Time:    1000 ms
*******************************/

#include <bits/stdc++.h>

using namespace std;

const int N = 210;

int n, m;
vector<int> e[N];
int color[N];

bool dfs(int u, int col) {
    color[u] = col;
    for (int to : e[u]) {
        if (!color[to]) {
            if (!dfs(to, 3 - col)) return false;
        }
        else {
            if (color[to] == color[u]) return false;
        }
    }
    return true;
}

void solve() {
    for (int i = 0; i < n; i++) {
        color[i] = 0;
        e[i].clear();
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }

    for (int i = 0; i < n; i++) {
        if (!color[i]) {
            if (!dfs(i, 1)) {
                cout << "NOT BICOLORABLE.\n";
                return;
            }
        }
    }

    cout << "BICOLORABLE.\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (cin >> n >> m, n) solve();
    return 0;
}
```

---

## 作者：信息学carryHarry (赞：0)



#### 此题就是二分图判定染色法
### 策略：
- 对于一个未染色的点，染上色 $color$，相邻点为 $3-color$，矛盾即不是二分图。
### 代码:

```cpp
#include<bits/stdc++.h>

using namespace std;
const int N=1005;
vector<int>nbr[N];
int n,m,color[N];//color[i]表示顶点i的颜色
bool dfs(int x,int c)
{
	color[x]=c; //染色
	for(int i=0;i<nbr[x].size();i++){
		int cur=nbr[x][i];
		if(color[cur]==c)//如果相邻的顶点同色，返回0 
			return 0;
		else if(color[cur]==0){
			if(dfs(cur,3-c)==0)//如果相邻的顶点没被染色，则染成3-c(或者-c) 
				return 0;
		}
	}
	return 1;
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		nbr[x].push_back(y);
		nbr[y].push_back(x);
	}
	for(int i=1;i<=n;i++)
	{
		if(color[i]!=0){
			continue;
		}
		if(dfs(i,1)==0){
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES";
	return 0;
}

```


---

## 作者：zyh888 (赞：0)

# 问题描述
给定一张图，可不可以在每个点上染上 $2$ 种颜色中的 $1$ 种，使得每条边所连接的点颜色都不一样。
# 思路
将两种不同颜色记为 $1$ 和 $2$。

先对选 $1$ 号点进行染色，再将所有与它相连的边染色。
 - 如果这个点没有被染过色，就把他染成相反的颜色
 - 如果这个点染了和与它相连的点一样的颜色，就有冲突

# code
```c
#include<bits/stdc++.h>
using namespace std;
int e[205][205],color[205];
int n,m,x,y;
bool f;
void dfs(int u,int c){
    color[u]=c; //把当前节点染颜色 
    for(int i=1;i<=n;i++){ //寻找有连边的点 
        if(!e[u][i]) continue;  
        if(color[u]==color[i]){ //颜色一样就标记冲突 
            f=false;
            return;
        }    
        if(!color[i]) dfs(i,3-c);  //把有连边的点染成相反的颜色
    }
}
int main(){
    while(scanf("%d",&n)==1&&n){  //碰到0就结束 
        memset(e,0,sizeof(e));
        memset(color,0,sizeof(color));
        f=true;
        scanf("%d",&m);
        for(int i=1;i<=m;i++){
            scanf("%d%d",&x,&y);
            x++,y++; 
            e[x][y]=1;
            e[y][x]=1;
        }  //用邻接矩阵存图 
        dfs(1,1);
        if(!f) puts("NOT BICOLORABLE.");
        else puts("BICOLORABLE.");
    }
    return 0;
}
```
其实这种图叫做二分图，判断一个图是否是二分图，还要看它是否联通，但是这题并没有非联通图的数据，非联通图就只需把每个点看成 $1$ 号点进行染色，如果有冲突就退出。

贴上非联通图的代码：
```c
#include<bits/stdc++.h>
using namespace std;
int e[205][205],color[205];
int n,m,x,y;
bool f;
void dfs(int u,int c){
    color[u]=c; //把当前节点染颜色 
    for(int i=1;i<=n;i++){ //寻找有连边的点 
        if(!e[u][i]) continue;  
        if(color[u]==color[i]){ //颜色一样就标记冲突 
            f=false;
            return;
        }    
        if(!color[i]) dfs(i,3-c);  //3-c:如果颜色是1，那么就把和它相邻的点染成3-1，反之染成2 
    }
}
int main(){
    while(scanf("%d",&n)==1&&n){  //碰到0就结束 
        memset(e,0,sizeof(e));
        memset(color,0,sizeof(color));
        f=true;
        scanf("%d",&m);
        for(int i=1;i<=m;i++){
            scanf("%d%d",&x,&y);
            x++,y++; 
            e[x][y]=1;
            e[y][x]=1;
        }  //用邻接矩阵存图 
        for(int i=1;i<=n&&f;i++){ //依次给每个点染色，发生冲突就退出 
            if(!color[i]){ 
                dfs(i,1);
            }
        }
        if(!f) puts("NOT BICOLORABLE.");
        else puts("BICOLORABLE.");
    }
    return 0;
}
```
下面这份代码比较通用，无论这张图联不联通都可以判断。


---

## 作者：BigJoker (赞：0)

# 0x00 前言

此题需要使用图论和搜索，算是图论的入门题目吧。

# 0x01 思路

首先使用邻接表将每一个点所连接的点存下来，然后用宽度优先搜索或者是深度优先搜索去判断，这里我用的是宽度优先搜索。

# 0x02 搜索

首先要用两个数组，一个用来存储每个点的颜色，如果尚未被染色标记成 -1，染上第一种颜色标记成 1，染上第二种颜色标记成 2，另一个用来标记当前点用过没有。然后让每个点入队，取队首元素，对这个点所连接的点进行染色，如果该点已经染色，并且和当前的元素颜色相同，那么不要犹豫，直接返回 $\texttt f \texttt a \texttt l \texttt s \texttt e$，然后如果颜色不相同就不管，然后没染色，染色就行了。

# 0x03 初始化

这题我被初始化坑了很久，题目里面明确说明了 n 的范围有 0，所以要从 0 开始初始化。

# 0x04 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int vis[205],n,m,flag[205];
struct node{
	int a[205],tot;
}d[205];
bool bfs(int b){
	queue<int>q;
	q.push(b);
	memset(vis,-1,sizeof(vis));
	memset(flag,0,sizeof(flag));
	vis[b]=0;
	flag[b]=1;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=1;i<=d[x].tot;i++){
			if(vis[d[x].a[i]]!=-1)
				if(vis[d[x].a[i]]==vis[x]) return 0;
			if(!flag[d[x].a[i]]){
				if(!vis[x]) vis[d[x].a[i]]=1;
				else vis[d[x].a[i]]=0;
				q.push(d[x].a[i]);
				flag[d[x].a[i]]=1;			
			}
		}
	}
	return 1;
}
int main(){
	while(cin>>n){
		if(n==0) return 0;
		cin>>m;
		for(int i=0;i<=205;i++){
			d[i].tot=0;
			memset(d[i].a,0,sizeof(d[i].a));
		}
		for(int i=1;i<=m;i++){
			int l,r;
			scanf("%d %d",&l,&r);
			d[l].a[++d[l].tot]=r;
			d[r].a[++d[r].tot]=l;
		}
		if(bfs(0)) puts("BICOLORABLE.");
		else puts("NOT BICOLORABLE.");
	}
	return 0;
}
```


---

## 作者：Liynw (赞：0)

### 题意简述

给定多个连通无向图，判断这些图是不是二分图。

***

### Step 1 建图

$2\le n\le 199$，邻接矩阵和邻接表大家都随意，根据自己的习惯来。我这里用的是 `vector` 实现邻接表。

另外，因为结点的编号是从 $0\sim n-1$，我不太习惯，于是在建图的时候就擅自每个结点的编号都 $+1$，把编号变成了 $1\sim n$。

```cpp
for(int i=1;i<=m;i++){
	scanf("%d %d",&u,&v);
	map1[u+1].push_back(v+1);
	map1[v+1].push_back(u+1);
}
```

***

### Step 2 发出开始染色的指令

~~（没错我在凑字数）~~

Tips：以下内容都把结点编号当成 $1\sim n$。

因为是连通图，所以我们从 $1$ 结点开始染色。

我们定义一个 $a$ 数组，$a_i$ 代表 $i$ 结点的颜色：$0$ 代表还没有染色，$1$ 和 $2$ 代表两种不同的颜色。$1$ 号结点随便染一个颜色。

函数里可以传一个参数（遍历到的结点编号），也可以传两个参数（遍历到的结点编号和这个结点染的颜色）。我传的是两个参数。

主函数的执行异常简单，用三目运算符可以压缩为一行：

```cpp
printf("%s",dfs(1,1)?"BICOLORABLE\n":"NOT BICOLORABLE\n");
```

***

### Step 3 染色

染色我们采用 dfs 来执行。其实 bfs 也可以实现，但是显然 dfs 码量比 bfs 少亿丶丶，而且 bfs 要开结构体队列，内存更大，所以我们就使用 dfs 了。

dfs 的思路和遍历图差不多。因为只有两个颜色，所以定了 $1$ 结点的颜色后，染色的方案是唯一的。我们先找到给定点的所有直接后继，然后一个一个看：

- 如果它的某个直接后继与它要求染的颜色相同，这个图就不是二分图，直接 `return false` 即可。

- 如果它的某个直接后继和他要求染的颜色不同，那么直！接！跳！过！

- 如果它的某个直接后继没有染色，那么就给这个直接后继染上与它不同的颜色，接着继续遍历这个刚被染色的直接后继的直接后继。如果此直接后继后面染色不成功，说明这个图不是二分图（因为方案唯一！），直接 `return false`。

如果遍历完了，就 `return true`。

```cpp
int f(int x){return (x==1)?2:1;} //取相反颜色
bool dfs(int x,int color){
	a[x]=color;
	for(int i=0;i<map1[x].size();i++){
		if(a[map1[x][i]]==color) return 0;
		if(a[map1[x][i]]==f(color)) continue;
		if(!dfs(map1[x][i],f(color))) return 0;
	}
	return 1;
}
```

***

### Step 4 其它

一定要初始化！一定要初始化！一定要初始化！

要初始化的是图和记录染色的数组。

```cpp
memset(map1,0,sizeof(map1)); //vector可以直接这么初始化
memset(a,0,sizeof(a));
```

另外这是邻接表的检查代码：

```cpp
for(int i=1;i<=n;i++){
	printf("%d: ",i);
	for(int j=0;j<map1[i].size();j++) printf("%d ",map1[i][j]);
	printf("\n");
}
```

***

### Code

最后双手献上 AC 代码：

```cpp
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
vector<int> map1[205];
int n,m,u,v,a[205];
int f(int x){return (x==1)?2:1;}
bool dfs(int x,int color){
	a[x]=color;
	for(int i=0;i<map1[x].size();i++){
		if(a[map1[x][i]]==color) return 0;
		if(a[map1[x][i]]==f(color)) continue;
		if(!dfs(map1[x][i],f(color))) return 0;
	}
	return 1;
}
int main(){
	while(10000000000000000000ull>9999999999999999999ull){
		memset(map1,0,sizeof(map1));
		memset(a,0,sizeof(a));
		scanf("%d",&n);
		if(!n) return 0;
		scanf("%d",&m);
		for(int i=1;i<=m;i++){
			scanf("%d %d",&u,&v);
			map1[u+1].push_back(v+1);
			map1[v+1].push_back(u+1);
		}
		/*for(int i=1;i<=n;i++){
			printf("%d: ",i);
			for(int j=0;j<map1[i].size();j++) printf("%d ",map1[i][j]);
			printf("\n");
		}*/
		printf("%s",dfs(1,1)?"BICOLORABLE.\n":"NOT BICOLORABLE.\n");
	}
	return 0;
}
```

提交记录：[Link](https://www.luogu.com.cn/record/55966469)（没错我 UVA 登上了）

---

## 作者：happy_dengziyue (赞：0)

### 1 题意

输入 $n$ 和 $m$ 代表点数和边数。

接下来 $m$ 行，输入 $2$ 个数字，表示这两个点有一条无向边相连接。

点从 $0$ 到 $n-1$ 编号。

问题：可不可以在每个点上染上 $2$ 种颜色中的 $1$ 种，使得每条边所连接的点颜色都不一样。

数据范围：$2\le n\le199$

### 2 思路

当然要输入好那些边，考虑到代码复杂度，这里用了**邻接矩阵**。

将 $0$ 号点的颜色定义为 $\color{red}1$。

然后，枚举每一个 $0\le i<n$ 的 $i$，如果它与 $0$ 号点有边相连，就把它的颜色涂成 $\color{blue}2$。

按照同样的方法，枚举每一个点，如果这个点已经被涂上了颜色，就枚举每一个与之相连的点，涂上相反的颜色。如果发现冲突，直接退出。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int max_n=200;
int n;
int m;
bool g[max_n+2][max_n+2];
int c[max_n+2];
bool ok;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("UVA10004_1.in","r",stdin);
	freopen("UVA10004_1.out","w",stdout);
	#endif
	while(true){
		scanf("%d",&n);
		if(n==0)break;
		scanf("%d",&m);
		memset(g,0,sizeof(g));
		for(int i=1,x,y;i<=m;++i){
			scanf("%d%d",&x,&y);
			g[x][y]=g[y][x]=true;
		}
		memset(c,0,sizeof(c));
		c[0]=1;
		ok=true;
		for(int i=0;i<n&&ok;++i){
			for(int j=0;j<n;++j){
				if(i==j)continue;
				if(g[i][j]&&c[i]>0){
					if(c[j]==0){
						c[j]=3-c[i];
					}
					else{
						if(c[i]==c[j]){
							ok=false;
							break;
						}
					}
				}
			}
		}
		if(!ok)printf("NOT ");
		printf("BICOLORABLE.\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/53045272)

By **dengziyue**

---

