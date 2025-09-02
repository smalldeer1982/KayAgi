# [ABC103D] Islands War

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc103/tasks/abc103_d

東西一列に並んだ $ N $ 個の島と $ N-1 $ 本の橋があります。

$ i $ 番目の橋は、西から $ i $ 番目の島と西から $ i+1 $ 番目の島を接続しています。

ある日、いくつかの島同士で争いが起こり、島の住人たちから $ M $ 個の要望がありました。

要望 $ i $: 西から $ a_i $ 番目の島と西から $ b_i $ 番目の島の間で争いが起こったために、これらの島をいくつかの橋を渡って行き来できないようにしてほしい

あなたは橋をいくつか取り除くことでこれら $ M $ 個の要望全てを叶えることにしました。

取り除く必要のある橋の本数の最小値を求めてください。

## 说明/提示

### 制約

- 入力は全て整数である
- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 10^5 $
- $ 1\ \leq\ a_i $
- 組 $ (a_i,\ b_i) $ は全て異なる

### Sample Explanation 1

西から $ 2 $ 番目の島と $ 3 $ 番目の島を接続する橋を取り除くことで達成できます。

## 样例 #1

### 输入

```
5 2
1 4
2 5```

### 输出

```
1```

## 样例 #2

### 输入

```
9 5
1 8
2 7
3 5
4 6
7 9```

### 输出

```
2```

## 样例 #3

### 输入

```
5 10
1 2
1 3
1 4
1 5
2 3
2 4
2 5
3 4
3 5
4 5```

### 输出

```
4```

# 题解

## 作者：xiaoyuchenp (赞：4)

__题目算法__

贪心 $+$ 模拟（废话）。

__数学模型__

显而易见，就是在 $m$ 个区间 $(u_i,v_i)$ 中，找到不重叠的 $k$ 个部分， $k$ 即为所求。

__算法实现__

先把区间按右端点快排（从小到大），排完后定义一个变量 $maxn$ 记录最大值。若有 $maxn \le$ 区间的左端点，则判定为出现一次不重叠的情况，则计数器加一并将 $maxn$ 更新为该区间的左端点。

代码如下（已AC，请放心食用）：

```cpp
#include<bits/stdc++.h>
#define MAXN 100005
using namespace std;
struct edge{
	int u,v;
};
edge graph[MAXN];
int n,m,maxn=1,ans;
bool cmp(edge a,edge b){
	return a.v<b.v;
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++)cin>>graph[i].u>>graph[i].v;
	sort(graph+1,graph+m+1,cmp);
	for(int i=1;i<=m;i++)
		if(graph[i].u>=maxn)
			maxn=graph[i].v,ans++;//本蒟蒻第一次交题解，管理大大支持一下吧qwq
	cout<<ans;
	return 0;
} 
```



---

## 作者：that_summer (赞：3)

## 题意分析

有 $n$ 个小岛排成一列，每相邻两个小岛有一条路径相连，给出 $m$ 组战争关系，由一组 $(x,y)$ 组成，现要让 $(x,y)$ 两点不相通，请求出最少需要拆除的路径数。

我们可以将每一组 $(x,y)$ 看做一个区间，想让每组 $(x,y)$ 都不相连，就需要求出共有多少组 $(x,y)$ 重叠（在重叠的区间拆除路径可以一次使两组及以上不相连）。可以使用贪心 $+$ 模拟求出答案。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct war{
	int l,r;
}e[100010];
bool cmp(war x,war y){	//对每一组战争的右端点排序
	return x.r<y.r;
}
int main(){
	ios::sync_with_stdio(0);	//解除 cin,cout 与 scanf,printf 的捆绑，可以使输入以及输出速度更快
	cin.tie(0);
	cout.tie(0);
	int n,m,ans=0,maxn=1;	//初始化 maxn=1，从第一位开始
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>e[i].l>>e[i].r;
	}sort(e+1,e+m+1,cmp);
	for(int i=1;i<=m;i++){
		if(e[i].l>=maxn){	//当 maxn 的位置已经不能再使两组关系不相连时，增加拆除总数
			maxn=e[i].r,ans++;
		}
	}cout<<ans;
	return 0;
}
```


---

## 作者：Keids (赞：1)

一道贪心。

考虑要尽量选取覆盖最多的点。

假设我们选取了一段大区间。

如果存在一段区间的 $l$ 和 $r$ 都处于这段大区间内，那么我们就可以缩小取点的范围。

如此，我们每次缩小就可以得到最优的一些点。

那么具体该如何实现缩小区间的操作呢？

假设每次开战的分别为区间的左右端点。

首先将全部区间按左端点排序，取右端点。

遍历每一个区间，如果遍历到的区间包含在当前的区间内，则按照 $r$ 的大小缩小边界，

如果遍历到的区间的左端点已经不在当前区间内了，则跳到下一段，并且 $ans+1$。

具体实现看代码:
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+10;
int n,m;
struct node{
	int l,r;
}a[N];
bool cmp(node x,node y){
	return x.l<y.l;//排序
}
int ans=1;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)scanf("%d%d",&a[i].l,&a[i].r);
	sort(a+1,a+1+m,cmp);
	int r=a[1].r;//枚举的大区间的的端点
	for(int i=2;i<=m;i++){
		if(a[i].l>=r){
			ans++;
			r=a[i].r;//进入下一段枚举的大区间
			continue;
		}
		r=min(a[i].r,r);//缩小范围，否则无法取到当前r较小的区间
	}
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：Nightingale_OI (赞：1)

### 大意

有 $ n $ 个岛，被 $ n - 1 $ 条边链接，第 $ i $ 条边双向链接 $ i $ 岛和 $ i + 1 $ 岛。

问至少删掉多少边使得 $ m $ 组岛两两无法到达，这 $ m $ 组岛表示为数对 $ (a_i,b_i) $ 。

### 思路

考虑到在两个岛中间删掉任意一条边即可符合要求，每次贪心地删除一条边使得满足最多的靠左的数对即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
struct xy{
    int x,y;
}a[101010];
bool cmp(xy a,xy b){
    return a.x>b.x;
}
int main(){
    cin>>n>>m;
    f(i,1,m)scanf("%d %d",&a[i].x,&a[i].y);
    sort(a+1,a+m+1,cmp);
    f(i,1,n){
        if(l<i && m)l=n;
        while(m && a[m].x<=i)l=min(l,a[m--].y-1);
        if(l==i)++s;
    }
    printf("%d\n",s);
    return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc103_d)

## 思路

这道题是一道贪心题，并且需要我们用到结构体和结构体排序来解决。

我们可以把题目中所说的 $A_i$ 和 $B_i$ 看成是一个桥的左端点和右端点，于是题意就可以理解为——找到数量最多的一组互不重叠的桥梁。

输入每个 $A_i$ 和 $B_i$ 之后按照右端点从小到大进行结构体排序。排序之后，定义一个变量 $tmp$，用来存上一个大桥右端点的位置，循环往下找距离 $tmp$ 最近且不重叠的大桥的左端点，再把 $tmp$ 更新为这个大桥的右端点，结果 $+1$。如此循环往复直到找到最后的一个桥。

- 别忘最后输出换行。

## 代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
    int l,r;
};node a[100010];
int n,m,tmp=-1e9,ans;
bool cmp(node a,node b){return a.r<b.r;}
int main(){
    cin>>m>>n;
    for(int i=1;i<=n;++i)cin>>a[i].l>>a[i].r;
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;++i){
        if(a[i].l>=tmp){
            tmp=a[i].r;
            ++ans;
        }
    }
    cout<<ans<<endl;
    return 0;
}

~~~
[已 AC](https://www.luogu.com.cn/record/96033612)

---

## 作者：Back_Stuff (赞：0)

这题其实就是[P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)。
一道easy的与区间有关的贪心题。

## 思路

题目给的 $n$，其实根本没有用。

我们首先按照尾端点排序，首端点排不排都没关系。

定义一个 $f$ 来记录。如果 $f \leq$ 当前首端点，将 $f$ 更新为当前尾端点，要拆除的桥梁数加 $1$。否则，$f$ 不变。

最后输出要拆除的桥梁数即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)//优化
using namespace std;
int n,m,cnt,f=-0x3f3f3f3f,k;
struct NODE{ int s,e; }a[100001];
bool cmp(NODE a,NODE b){ return a.e<b.e; }尾端点排序
int main(){
    IOS;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a[i].s>>a[i].e;
	}
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=m;i++){
		if(a[i].s>=f){
            f=a[i].e;
            k++;
        }
	}
	cout<<k;
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：0)

一道很简单的贪心，其实只要找最多个互不重叠的战争点就可以了。

这道题和[P1803 线段覆盖](https://www.luogu.com.cn/problem/P1803)的做法是一样的，以第二岛屿排一下序，能找到当前不重叠的就更新最后战争地点就好啦！

## AC code
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
#define ll long long
const int MAXN=1e5+5;
int n,m;
int last=0;
int ans=0;
struct war{
	int a,b;
}w[MAXN];
bool cmp(war x,war y){
	return x.b<y.b;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		cin>>w[i].a>>w[i].b;
	sort(w+1,w+m+1,cmp);
	for(int i=1;i<=m;i++)
		if(w[i].a>=last){
			last=w[i].b;
			ans++;
		}
	cout<<ans;
}
```


---

