# Clique Problem

## 题目描述

数轴上有 $n$ 个点，第 $i$ 个点的坐标为 $x_i$，权值为  $w_i$。两个点 $i,j$ 之间存在一条边当且仅当 $abs(x_i-x_j)\geq w_i+w_j$ 。 你需要求出这张图的最大团的点数。

团的定义：两两之间有边的顶点集合。

## 样例 #1

### 输入

```
4
2 3
3 1
6 1
0 2
```

### 输出

```
3
```

# 题解

## 作者：NaCly_Fish (赞：27)

这题的解法分为三步进行，

Step 1：读懂题意  
对于两个点 $i,j$，如果 $|x_i-x_j| \geq w_i+w_j$，就连一条从 $i$ 到 $j$ 的边。     
然后要求出**最大团**中点的数量。注意这里**团**的定义是两两点之间都有边的顶点集合，也就是每一对点之间都有边。
****
Step 2：分析原式   
由于连边是双向的，所以每一对点我们只用考虑一次。所以这里我们设 $x_i \geq x_j$，然后原式就可以写为 $x_i-w_i \geq x_j+w_j$。  

对于一个点 $i$，我们再给它加上两个属性：$l$ 和 $r$。其中 $l_i = x_i-w_i$，$r_i=x_i+w_i$。   
然后再回头看看刚才推出来的式子，就变成了 $l_i \geq r_j$。 
****
Step 3：转化问题    
     
由此我们可以联想到什么？没错，就是线段覆盖。  

我们可以把每个点都看成是 $[l,r]$ 区间上的一条线段，如果满足刚才的那个式子，就说明两条线段不重叠（因为一个的最左端在另一个最右端的右侧，肯定不重叠），所以任意两条互不重叠的线段之间都会相连。

所以题目中给的问题，实际上就是从数轴上的一些线段中取尽可能多，使其互不重叠，也就是线段覆盖问题。这个经典问题贪心就可以解决，原题目可以看 [P1803](https://www.luogu.org/problemnew/show/P1803)，在这里就不多做讲解了。  

参考代码：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#include<queue>
#define ll long long
#define inf 0x3f3f3f3f
#define N 200003
using namespace std;

struct node{ 
	//定义结构体，存储一个点
    int l,r;
    node(int l=0,int r=0):l(l),r(r){}
    bool operator < (const node& nd) const{
    	//重载运算符，线段覆盖排序用。以r为第一关键字，
        //l为第二关键字，从小到大排序
        if(r!=nd.r) return r < nd.r;
        return l < nd.l;
    }
};

int n;
node a[N];

inline void read(int &x){
	//喜闻乐见的快读
    x = 0;
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)){
        x = (x<<3)+(x<<1)+c-'0';
        c = getchar();
    }
}

int main(){
    int l,r,n,x,w,ans = 0;
    read(n);
    for(int i=1;i<=n;++i){
        read(x),read(w);
        a[i] = node(x-w,x+w);
        //x-w 和 x+w 对应上述的l和r
    }
    sort(a+1,a+1+n);
    //按照定义的规则排序
    r = -inf;
    //初始设当前右端点为 -inf，防止出现问题
    for(int i=1;i<=n;++i){
        if(a[i].l<r) continue; 
        //左端点比当前右端点小，肯定会重叠，跳过
        ++ans;
       	//不会重叠，答案++
        r = a[i].r;
        //更新右端点
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：Siyuan (赞：13)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io)

---

> 题目链接：[Codeforces 527D](https://codeforces.com/contest/527/problem/D)

数轴上有 $n$ 个点，第 $i$ 个点的坐标为 $x_i$，权值为 $w_i$。对于任意两个点 $i,j$ 之间存在一条边当且仅当 $|x_i-x_j|\geqslant w_i+w_j$。求出这张图的最大团的点数（团就是两两之间有边的顶点集合）。

数据范围：$1\leqslant n\leqslant 2\times 10^5$，$0\leqslant x_i\leqslant 10^9$，$1\leqslant w_i\leqslant 10^9$

------

## Solution

我们把每个点转化成线段 $[x_i-w_i,x_i+w_i]$，我们令 $l_i=x_i-w_i$，$r_i=x_i+w_i$。那么问题就转化为：对于任意两个点 $i,j$ 之间存在一条边当且仅当 $l_i\geqslant r_j$。我们以左端点为第一关键字，右端点为第二关键字进行排序，然后直接扫一遍求解就行了。

**时间复杂度**：$O(n\log n)$

------

## Code

```cpp
#include <cstdio>
#include <algorithm>

const int N=2e5+5;
int n,l[N],r[N],id[N];

bool cmp(int x,int y) {
    return r[x]==r[y]?l[x]<l[y]:r[x]<r[y];
}
int main() {
    scanf("%d",&n);
    for(int x,w,i=1;i<=n;++i) {
        scanf("%d%d",&x,&w);
        l[i]=x-w,r[i]=x+w,id[i]=i;
    }
    std::sort(id+1,id+n+1,cmp);
    int ans=0,las=-2e9;
    for(int i=1;i<=n;++i) if(las<=l[id[i]]) ++ans,las=r[id[i]];
    printf("%d\n",ans);
    return 0;
}
```



---

## 作者：Randyhoads (赞：10)

简单贪心

化简原式：就是找xi-wi>=xj-wj

那对于一个点i,设li=xi-wi,ri=xi+wi

把每一个点看作[li,ri]间的一条线段，只要表示两点的

线段不重叠，就有一条边，然后就是一道贪心了

CF里面的神奇思维题，难度没有那么大，提高难度比较适宜（恶意评分？）


```cpp

#include<bits/stdc++.h>

using namespace std;

int n;
struct node
{
	int l;
	int r;
	friend bool operator < (node a1,node a2)
	{
		if(a1.r!=a2.r) return a1.r<a2.r;
		else return a1.l<a2.l;
	}
} t[200000 + 10];

int ans=0;

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int a,b;
		cin>>a>>b;
		t[i].l=a-b;
		t[i].r=a+b;	
	}
	sort(t+1,t+n+1);
	int r= -(1<<30);
	for(int i=1;i<=n;i++)
	{
		if(t[i].l>=r)
		{
			ans++;
			r=t[i].r;
		} 
	}
	cout<<ans<<endl;
}
```

---

## 作者：DreamShadow (赞：10)

#### 愚人节？黑题？emm，虽然我被第14个点坑死了，不过总算好了，为此，我还和 
@夜刀神十香ღ 
#### 互怼了起来，最后惨败而归（（*/㉨＼*）捂脸）
#### 好了不说这个了（咳咳，清嗓子），这道题目，经过 夜刀神十香ღ 大佬介绍后，发现，其实也不是特别难，似乎有点愧对（黑题）了，详情见代码：
```pascal
var
  n,i,x,y,R,ans:longint;
  pt:array[1..200000,1..2]of longint;//因为是二维数组，别开的过分大，如果想节省空间，可以试试record
procedure sort(l,r:longint);//快排，不多说
var
  i,j,x,y: longint;
      begin
         i:=l;
         j:=r;
         x:=pt[(l+r) div 2,1];//注意，我们要以pt[i,1]作为标准来排序
         repeat
           while pt[i,1]<x do
            inc(i);
           while x<pt[j,1] do
            dec(j);
           if i<j then
             begin
                y:=pt[i,1];//一块换
                pt[i,1]:=pt[j,1];
                pt[j,1]:=y;
                y:=pt[i,2];
                pt[i,2]:=pt[j,2];
                pt[j,2]:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           sort(l,j);
         if i<r then
           sort(i,r);
      end;
 begin
   readln(n);
   for i:=1 to n do
   begin
     readln(x,y);//重点
     pt[i,1]:=x-y;//左端点为x-w
     pt[i,2]:=x+y;//右端点为x+w
   end;
   sort(1,n);
   ans:=0;
   R:=-maxlongint;
   for i:=1 to n do
   begin
     if pt[i,1]>=R then//枚举+处理
     begin
       ans:=ans+1;
       R:=pt[i,2];
     end;
   end;
   writeln(ans);//输出
 end.


```

---

## 作者：凉城無愛 (赞：6)

### 题意：

>数轴上有n 个点，第i 个点的坐标为xi，权值为wi。两个点i,j之间存在一条边当且仅当 abs(xi-xj)>=wi+wj。 你需要求出这张图的最大团的点数。（团就是两两之间有边的顶点集合）


### 分析

>当xi<xj时，若要xj-xi>=wi+wj,则xi+wi<=xj-wj，不妨令yi=xi-wi，再将其按从大到小排序。由公式可知，i若有连边，只能是与排序后的前几个相连，加上其的单调性，可用二分快速求出



### question

>Q1:若排序后xi<xj&&i<j呢，不是保证xi<xj上述公式才成立吗


>A1:若i<j,则yi>yj,也就是说xi-wi>xj-wj,则xj-xi<wj-wi，又w>0，所以xj-xi<wi+wj，又xi<xj,即abs(xi-xj)<wi+wj。综上所述，根本不存在排序后xi<xj&&i<j
                                               
### 连边之后的处理
                                                                                                   
>连边之后大概会成这样
  
  ![](https://cdn.luogu.com.cn/upload/image_hosting/lsg5yywv.png?x-oss-process=image/resize,m_lfit,h_170,w_225)                                                                                                                 

由图可以发现，若j连了i，那么j必定连了1，2，3……i-1，i。有以下的递推公式
  
```cpp
int sous(int x){
	//a[x].ans:二分查找到的下标最大的且满足条件的点
	//f[x]:以x为最后一个点的最大团的点数
	//maxx[x]：从1到x的最大的最大团的点数
	if(a[x].ans==-1){	//若无满足要求的点，则该团只有其一个点 
		f[x]=1;
	}
	else f[x]=maxx[a[x].ans]+1;
	//否则，就为所有满足条件的点中团最大的个数+1 
	return f[x];
}
//主函数中 
for(int i=1;i<=n;i++){
	sous(i);
	maxx[i]=max(maxx[i-1],f[i]);
}
//最后输出maxx[n]
```
                      
如果大家还是有点蒙的话，可以自己画图/结合上面的图，理解理解
                      
### 贴码
                      
```cpp
#include<bits/stdc++.h>
using namespace std;
int q,w,e,r,t,ans,f[200010],maxx[200010];
//ps：不要问我为什么会有q,w,e,r,t,那是以前养成的不好习惯（滑稽） 
//f[x]:以x为最后一个点的最大团的点数
//maxx[x]：从1到x的最大的最大团的点数
struct qqq{
	int x,w,y,ans;
//a[x].ans:二分查找到的下标最大的且满足条件的点
}a[200010];
int paix2(qqq s1,qqq s2){
	return s1.y>s2.y;
}
int sous(int x){
	if(a[x].ans==-1){	//若无满足要求的点，则该团只有其一个点 
		f[x]=1;
	}
	else f[x]=maxx[a[x].ans]+1;
	//否则，就为所有满足条件的点中团最大的个数+1 
	return f[x];
}
int main(){
	cin>>q;
	for(int i=1;i<=q;i++){
		scanf("%d%d",&a[i].x,&a[i].w);
		a[i].y=a[i].x-a[i].w;
	}
	sort(a+1,a+1+q,paix2);
	for(int i=1;i<=q;i++){
		int minn=1,maxx=i-1,mid;
		a[i].ans=-1;
		while(minn<=maxx){			//二分查找求出每一个a[i].ans 
			mid=(minn+maxx)>>1;
			if(a[i].x+a[i].w<=a[mid].y){
				minn=mid+1;
				a[i].ans=mid;
			}
			else maxx=mid-1;
		}
	}
	for(int i=1;i<=q;i++){		//递推求出maxx[q] 
		sous(i);
		maxx[i]=max(maxx[i-1],f[i]);
	}
	cout<<maxx[q];
	return 0;
}
```

### 完结
  撒花*★,°*:.☆\(￣▽￣)/$:*.°★*
  
  ps：若有疑问，可在讨论中提出，若有错误，请多多指教
  




---

## 作者：青鸟_Blue_Bird (赞：2)

发现题解区居然没有我这种写法，那么蒟蒻就来写一发吧！

### 前提

看懂这篇题解，您需要：

1、线段树基本操作

2、不错的$dp$能力

3、$STL$ 入门函数

### 题目分析

首先，题目中的关键点就是这个式子：
 $abs(x_i-x_j) \ge$ $w_i+w_j$。
 
 如果分别比较两个点间的距离和权值和，感觉是不可避免的$O(N^2)$枚举了（不排除是我太蒟了）那么，何不化简一下式子呢？
 
 在保证$x_i \ge x_j$的情况下，我们可以将不等式移项，变成$x_i - w_i \ge x_j + w_j$

那么，怎么保证 $x_i$ 一定大于 $x_j$ 呢？ 不妨将$x$从小到大排序。
这样，当我们枚举到$x_i$的时候，就可以保证$x_j (j ∈ [1,i-1])$一定小于$x$。

其次，由于题目中对于点的选择看似“无序”， 用$dp$应该会比较容易处理。

设 $dp_i$ 表示在第 $i$ 个点，我们可以得到的最大团。 那么，状态转移方程就很好写了：

$dp_i = max\{dp_j\} + 1 $其中 $j ∈ [1,i)$， 且 $j$ 合法。

但是，这题真的就一个一维$dp$就可以过吗？ 在考虑如何判断$j$合法的时候，发现我们还是得要枚举$j$, 复杂度始终下不来。

如何不枚举$j$就能判断合法性呢？

对于 $x_i - w_i$，我们是可以$O(1)$计算的。

那么，我们为何不用$STL$中的 lower_bound函数呢？ 

将所有的$x_i + w_i$存入一个数组中，然后将其从小到大排序。那么，如果我们对他从小到大排序，只需要在这个数组中对 $x_i - w_i$进行lower_bound或者 upper_bound 查询，我们就可以知道$x_i - w_i$在数组中的位置，那么在这个位置之前的数就肯定都是合法的啦！

最后一个问题：如何快速查找区间的最大值呢？

这时候，我们不妨将$dp$的定义稍微进行一下修改： $dp_i$表示在第$i$大的$x_i + w_i$上，可以得到的最大团的大小。

这样做，我们就可以使得$dp$数组的下标连续起来，然后考虑用线段树优化$dp$,快速查询区间最大值，复杂度就可以降到$O(NlogN)$啦。


来一波代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 200010
#define ll long long

template <class T>
inline void read(T& a){
	T x = 0, s = 1;
	char c = getchar();
	while(!isdigit(c)){ if(c == '-') s = -1; c = getchar(); }
	while(isdigit(c)){ x = x * 10 + (c ^ '0'); c = getchar(); }
	a = x * s;
	return ;
}


struct hehe{
	int maxn;
} ;

struct Segment_tree{  // 线段树板子 
	
	hehe e[N << 2]; 
	
	inline void pushup(int o){
		e[o].maxn = max(e[o << 1].maxn, e[o << 1 | 1].maxn);
		return ; 
	}

	void update(int o, int l, int r, int x, int k){
		if(l > x || r < x) return ;
		if(l == r && l == x){
			e[o].maxn = k;
			return ;
		}
		int mid = l + r >> 1;
		update(o << 1, l, mid, x, k);
		update(o << 1 | 1, mid + 1, r, x, k);
		pushup(o);
		return ;
	}	

	int query(int o, int l, int r, int in, int end){
		if(l > end || r < in) return 0;
		if(l >= in && r <= end) return e[o].maxn;
		int mid = l + r >> 1;
		return max(query(o << 1, l, mid, in, end), query(o << 1 | 1, mid + 1, r, in, end)); 
	}

} tree;


struct node{
	int x, w;
} t[N];
int temp[N];
int n, m;
int dp[N]; 

bool cmp(node a, node b){  // 按照 x 排序 
	return a.x < b.x; 
}

int main(){
//	freopen("clique.in", "r", stdin); freopen("clique.out", "w", stdout); 
	read(m);
	for(int i = 1; i <= m; i++){
		read(t[i].x), read(t[i].w);
		temp[i] = t[i].x + t[i].w; 
	}
	sort(temp + 1, temp + m + 1);
	sort(t + 1, t + m + 1, cmp); 
	
	n = unique(temp + 1, temp + m + 1) - temp - 1; // 记得去重 
	for(int j = 1; j <= m; j++){
		int pos = upper_bound(temp + 1, temp + n + 1, t[j].x - t[j].w) - temp - 1; // 第一个大于值的位置 
		int tmp = tree.query(1, 1, n, 1, pos); 
		pos = lower_bound(temp + 1, temp + n + 1, t[j].x + t[j].w) - temp - 1; // 第一个大于等于当前值的位置 
		pos++;  
		if(dp[pos] <= tmp + 1){
			dp[pos] = tmp + 1;
			tree.update(1, 1, n, pos, tmp + 1); 
		}
	}
	
	printf("%d\n", tree.query(1, 1, n, 1, n));
	return 0; 
}
```


---

## 作者：HDWR (赞：2)

先把式子推一下吧。

灵感来源：[@lcyz_lmy](https://www.luogu.org/space/show?uid=201982)

---

比如说有这么两个点

```
___(aj wj)____________(ai wi)___>（正方向）
a 表示坐标，w 表示权值
```

由题目可知，这两个点连边当且仅当`ai - aj >= wi + wj`

整理一下，得 `ai - wi >= aj + wj (1)`

---

考虑把每个点用区间的形式表示，则上面的两个点可以表示为 `[ai - wi, ai + wi] [aj - wj, aj + wj]`

对于两个区间，有这么两种关系：有交集和无交集，分别考虑一下

1. 有交集，则`ai - wi < aj + wj`，与(1)式显然矛盾，故这两个区间对应的点无法连边
2. 无交集，则`ai - wi > aj + wj`，与(1)式相同，故这两个区间对应的点有边。

所以两个点有边当且仅当两个点对应的区间无交集

---

想一想如何求最大团

考虑这样三个点

```
(ak wk)__(aj wj)___________(ai wi)___>
```

假设ai和aj，aj和ak都有边，那么ai和ak必定有边（想一想，为什么）

所以一个子图是团满足其中的点对应的区间两两不交

---

所以问题就转化为了一个**线段覆盖**问题：

给你一堆点，每个点都有对应的线段（即上面提到的区间形式），求最大的区间数使得区间两两不交

！！！！！！

---

代码实现：

（直接从线段覆盖那边粘过来改了一下

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

#define int long long

const int MAXN = 1000000 + 10;

struct Line {
    int left, right;
} line[MAXN];

bool stlCmp(Line x, Line y) {
    return x.right < y.right;
}

signed main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int x = 0, w = 0;
        cin >> x >> w;
        line[i].left = x - w;
        line[i].right = x + w;
        // 这个点对应的区间（线段）
    }
    sort(line + 1, line + 1 + n, stlCmp);
    int lastRight = INT_MIN, lines = 0;
    for (int i = 1; i <= n; ++i) {
        if (lastRight <= line[i].left) ++lines, lastRight = line[i].right;
    }
    cout << lines << endl;
    return 0;
}

```



---

## 作者：旭日临窗 (赞：1)

可以先从式子入手。$i,j$ 两点之间有边的条件是 $\left|x_i-x_j\right|\ge w_i+w_j$，然后考虑怎么把绝对值去掉，不妨设 $x_i \ge x_j$，然后式子就化简为了 $x_i-x_j \ge w_i+w_j$，遇到这种式子可以套路地把带有 $i$ 的项移到一边，带有 $j$ 的项移到另一边，所以式子就变成了:

$x_i-w_i \ge x_j+w_j$ 在数轴上表示如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/27hmdf1t.png)

容易发现如果把一个点看成一条左端点为 $x_k-w_k$，右端点为 $x_k+w_k$ 的线段，那么两个点之间有边当且仅当两条线段不重合，再根据团的定义：每两个点之间都有边。就转化为了任意两条线段都不重合，所以问题就变成了从 $n$ 条线段里选择尽可能多的线段，使得任意两条线段都不重合，也就是线段覆盖问题。这里有一道线段覆盖的[模板题](https://www.luogu.com.cn/problem/P1803)，可以先完成。

代码（可读性应该还可以吧）：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int n,ans;
struct node{
	int l,r;
	bool operator < (const node &w) const{return r < w.r;}
}a[maxn];
int main(){
	scanf("%d",&n);
	int x,y;
	for(int i = 1;i <= n;i++){
		scanf("%d%d",&x,&y);
		a[i] = node{x - y,x + y};
	}
	sort(a + 1,a + n + 1);
	int nr = -2e9;
	for(int i = 1;i <= n;i++)
	if(a[i].l >= nr) nr = a[i].r,ans++;
	printf("%d",ans);
	return 0;
}
```


---

## 作者：EarringYYR (赞：1)

这是一道神奇的贪心题
对于每一个点，你可以把它视为一条线段，**左端点为x-w，右端点为x+w**。这样对于每个abs(xi-xj)>=wi+wj，我们默认xi>=xj，那么就可以转化为xi-wi>=xj+wj，由此就可以退出由i号点构造出来的线段的左端点在由j号点构造出来的线段的右端点的右边，即这两条线段没有交点。因此这道题目就变成了：**求n条线段中最多能选出多少条不相交的线段**。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct node
{
    int l;
    int r;
}a[2000005];
bool comp(node c,node d)
{
    if(c.l<d.l)
        return 1;
    if(c.l>d.l)
        return 0;
    if(c.r<d.r)
        return 1;
    return 0;
}
int main()
{
    int n,ans=0;
    cin>>n;
    for(int i=1;i<=n;++i)
    {
        int x,w;
        scanf("%d%d",&x,&w);
        a[i].l=x-w;
        a[i].r=x+w;
    }
    sort(a+1,a+n+1,comp);
    for(int i=n;i>=1;--i)
    {
        int len=i;
        ans++;
        while(i-1<=n&&a[len].l<a[i-1].r)
            --i;
    } 
    cout<<ans;
    return 0;
}
```

---

## 作者：mcDinic (赞：0)

假设 $x_i \ge x_j $，可以将原先的式子转化为：$x_i-w_i \ge x_j+w_j$。

这样，把每一个点都当成一条线段：$[x_i-w_i,x_i+w_i]$，两条线段相交即两个点有边，原问题可化为：对于这些线段，每条可选可不选，要使它们互不相交，最多能选几条线段？

这就是一个贪心问题，按右端点排序后即可，详见代码。

## Code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,zhi=-0x3f3f3f3f,ans;
struct node{
	int l,r;
}a[200005]; 
bool cmp(node x,node y){return x.r==y.r?x.l<y.l:x.r<y.r;}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		int so1,so2;
		scanf("%lld%lld",&so1,&so2),a[i].l=so1-so2,a[i].r=so1+so2;
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++){
		if(zhi<=a[i].l)ans++,zhi=a[i].r;
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：hehelego (赞：0)

### statement
$n$个点,每个点给出$(x,w)$如果两个点满足$|x_i-x_j|\geq w_i+w_j$那么它们之间有边,求这个图的最大团(找一个子图,满足它是完全图,最大化子图中点的数量).  

### sol
首先取个补图,原图团对应补图独立集.  
为啥这么搞呢?因为$|a|\lt b$处理不需要分类,而$|a|\geq b$需要分类.
$$
\begin{aligned}
&(i,j)\in E\\
&\iff |x_i-x_j|\lt w_i+w_j\\
&\iff -(w_i+w_j)\lt x_i-x_j\lt w_i+w_j\\
&\iff (x_i+w_i\gt x_j-w_j)\&(x_i-w_i\lt x_j+w_j)\\
&\text{let }L_i=x_i-w_i,R_i=x_i+w_i\\
&\iff R_i\gt L_j\&L_i\lt R_j
\end{aligned}
$$

有一个几何意义$|a-b|=dis(a,b)$所以$|x_i-x_j|\lt w_i+w_j$尝试构造几何意义,每个点$i$覆盖$(x_i-w_i,x_i+w_i)$的范围,如果$(i,j)$的区间有交集,那么它们之间有边.  
当然这很玄学,真实无脑推导在上面,LuoguBlog LaTex可能渲染没法看,就这样吧. 

然后就是经典问题,选尽量多的线段不相交,做法是$[l,r]$按照$r$升序排列,从左到右,能选就选.


### code
```cpp
#include <bits/stdc++.h>
int read(){
	int x=0,f=1; char c;
	do{c=getchar();if(c=='-')f=-1;}while(!isdigit(c));
	do{x=x*10+c-'0';c=getchar();}while(isdigit(c));
	return x*f;
}
struct Interval{
	int l,r,id;
	Interval(int a,int b,int c):l(a),r(b),id(c){}
	bool operator<(const Interval&rhs)const{
		if(r==rhs.r){ return l>rhs.l; }
		return r<rhs.r;
	}
}; std::vector<Interval> v;
bool chk(const Interval&a,const Interval&b){
	return !(a.l>b.r||a.r<b.l);
}
int use[200000];
std::set<std::pair<int,int>> tr;
int main(){
	int n=read(),x=0,w=0;
	for(int i=0;i<n;i++){
		x=read(),w=read();
		v.push_back(Interval(x-w,x+w,i));
		tr.insert(std::make_pair(x-w,i));
	}
	std::sort(v.begin(),v.end());
	int ans=0,end=-int(1+2e9);
	for(auto p:v) if(!use[p.id]){
		ans++; use[p.id]=1;
		while(!tr.empty()&&tr.begin()->first<p.r){
			use[tr.begin()->second]=1;
			tr.erase(tr.begin());
		}
	}
	std::cout<<ans<<std::endl;
	return 0;
}
```

---

## 作者：t162 (赞：0)

>数轴上有n 个点，第i 个点的坐标为xi，权值为wi。两个点i,j之间存在一条边当且仅当 abs(xi-xj)>=wi+wj。 你需要求出这张图的最大团的点数。（团就是两两之间有边的顶点集合） 

什么鬼题目啊。。。看都看不懂。

别急，我们不妨把问题转换一下：

>数轴上有n 个区间，每个区间的范围是[xi-wi,xi+wi]。 求这个数轴上不相交区间（公用端点不算相交）的最大数量。

好眼熟啊。。。。。。等等，这不是线段覆盖问题吗（把区间当成线段处理）？

老套路，我们把每个线段按照右端点排序，再遍历一遍就好了。

代码：

```cpp
#include<bits/stdc++.h> //终于懒了一回
using namespace std;
struct point{
    int l,r;
    friend inline bool operator < (point x,point y){
        return x.r<y.r;
    }
}a[200001];
int n,ans=1;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        int x,w;
        scanf("%d%d",&x,&w);
        a[i].l=x-w;
        a[i].r=x+w;
    }
    sort(a+1,a+1+n);
    for(int i=2;i<=n;i++){
        if(a[i].l>=a[i-1].r)ans++;
    }
    printf("%d\n",ans);
    return 0;
}
```

交上去一看，WA！我们分析一下原因。明白了，上面代码的第二个循环的判断出了问题。拿一个例子：

```
-----     -----
------------
```

本来应该选择上面两条线段的，但是结果却是`1`。为什么呢？因为我们在判断的时候是和前一条线段的右端点进行比较的，正确的应该是和已经选择的最右边线段的右端点进行判断。我们开一个变量$R$，它的初值是（排序后）第一条线段的右端点。后面如果选择了一个线段，那么就更新$R$（更新成选择的线段的右端点）。

正解：

```cpp

#include<bits/stdc++.h> //终于懒了一回
using namespace std;
struct point{
    int l,r;
    friend inline bool operator < (point x,point y){
        return x.r<y.r;
    }
}a[200001];
int n,ans=1,r;	//这里的r就是描述中的R
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        int x,w;
        scanf("%d%d",&x,&w);
        a[i].l=x-w;
        a[i].r=x+w;
    }
    sort(a+1,a+1+n);
    r=a[1].r;	//给R赋初值
    for(int i=2;i<=n;i++){
        if(a[i].l>=r){
            r=a[i].r;	//更新R
            ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}
```

[$$\textbf{Blog}$$](https://bambusoideae.cn/)

---

## 作者：King_of_gamers (赞：0)

一开始看此题,发现没有什么思路,后面受到某些大佬的启发.

发现我们可以把原来的式子转化成xi-wi>=xj+wj,于是我们把一个点看作一段在[xi-wi,xi+wi]的线段,此题就顺利转化为了贪心了.

怎么贪心呢?发现只要两个线段没有交点(交在边界也行)便可以连边,并且选出的一连串不相交的边一定是可以两两连边的,所以符合题目给出的条件.

于是我们按照线段右端点排序后暴力取点就可以,时间复杂度O(nlogn).

~~吐槽一句,楼下大佬按左端点排序的,我一开始看题解非常迷......~~

再给出我的AC代码,跑的可慢了......
```pascal
type
        re=record
                l,r:longint;
        end;
var
        n,i,x,y,now,ans:longint;
        point:array[1..200000]of re;
procedure swap(var a,b:re);
var
        c:re;
begin
        c:=a;
        a:=b;
        b:=c;
end;
procedure sort(l,r:longint);
var
        i,j,mid:longint;
begin
        i:=l;
        j:=r;
        mid:=point[(l+r)>>1].r;
        repeat
                while point[i].r<mid do inc(i);
                while point[j].r>mid do dec(j);
                if i<=j then
                begin
                        swap(point[i],point[j]);
                        inc(i);
                        dec(j);
                end;
        until i>j;
        if i<r then sort(i,r);
        if l<j then sort(l,j);
end;
begin
        read(n);
        for i:=1 to n do
        begin
                read(x,y);
                point[i].l:=x-y;
                point[i].r:=x+y;
        end;
        sort(1,n);
        now:=-maxlongint;
        for i:=1 to n do
        if point[i].l>=now then 
        begin
                inc(ans);
                now:=point[i].r;
        end;
        writeln(ans);
end.
```

---

