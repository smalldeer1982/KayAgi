# [POI 2014] KAR-Cards

## 题目描述

There are $n$ cards arranged on a table in a certain order.

Two integers are written on each card, one per side: the obverse and the reverse.

Initially all cards lie with the averse facing up.

Byteasar, The Great Illusionist, intends to perform (multiple times!) his signature    Binary Search Card Manipulation.  However, to present it, he needs the sequence of numbers    as seen on the cards to be non-decreasing.

Thus, Byteasar may have to turn over some cards so that the numbers on their reverse sides    become visible.

Furthermore, the illusion requires a participant from the audience.

Alas, some of the volunteers are deployed by Byteasar's competitors who want him to fail.

Each such supposititious volunteer, upon entering the scene, would swap two cards on the table in a lightning move of a hand.  After each such swap, Byteasar can again turn over any cards he desires but nevertheless, he may not be able to perform his great illusion.

If that were to happen, he would be forced to turn to traditional illusions, such as pulling a rabbit out of a hat.

Write a program that determines, after each card swap, if Byteasar can perform his great illusion.

有一些卡牌，正反各有一个数，你可以任意翻转，每次操作会将两张卡牌的位置调换，你需要在每次操作后回答以现在的卡牌顺序能否通过反转形成一个单调不降的序列


## 说明/提示

有一些卡牌，正反各有一个数，你可以任意翻转，每次操作会将两张卡牌的位置调换，你需要在每次操作后回答以现在的卡牌顺序能否通过反转形成一个单调不降的序列


## 样例 #1

### 输入

```
4
2 5
3 4
6 3
2 7
2
3 4
1 3
```

### 输出

```
NIE
TAK
```

# 题解

## 作者：Energy_Making (赞：6)

## 1.前置知识
[线段树](https://oi-wiki.org/ds/seg/)
## 2.解法
这道题是一道线段树的连通性问题。而我们要维护的信息则也跟连通性有关——$l$ 分别取正背面，$r$ 能取到正面还是背面。

具体而言，我们把数字较小的一面记为 $a$，较大的一面记为 $b$。线段树中维护的信息即为 $va$：$l$ 取 $a$ 出发时 $r$ 的最小值（显而易见的贪心思想）与 $vb$：$l$ 取 $b$ 出发时 $r$ 的最小值。那么难点就在于维护 $va$ 与 $vb$。这里放出 $va$ 作为参考。

```cpp
int mid=(l+r)>>1;
if(a[mid+1]>=node[p<<1].va)node[p].va=node[p<<1|1].va;
else if(b[mid+1]>=node[p<<1].va)node[p].va=node[p<<1|1].vb;
else node[p].va=inf;
```
![ahhh](https://cdn.luogu.com.cn/upload/image_hosting/opwam6qa.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

首先我们都讨论了```node[p<<1].va```是因为 $p$ 与 $p$ 的左儿子起点 $a$ 相同。

然后我们讨论```a[mid+1]```与```b[mid+1]```是因为要满足不下降的条件，注意先讨论较小的一项是因为要满足贪心原则（一个位置上的数合法时越小越有可能成功），如果两个都不行则用极大值标记为此路不通。

最后的 change 操作就将有改变的地方交换重新建树即可。

## 3.代码
```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;
const int inf=0x3f3f3f3f;
int n,m;
int a[200005],b[200005];
struct seg
{
	int l,r,va,vb;
	seg()
	{
		va=vb=inf;
	}
};
seg node[1000005];
void merge(int p,int l,int r)//精华所在
{
	int mid=(l+r)>>1;
	if(a[mid+1]>=node[p<<1].va)node[p].va=node[p<<1|1].va;
	else if(b[mid+1]>=node[p<<1].va)node[p].va=node[p<<1|1].vb;
	else node[p].va=inf;
	if(a[mid+1]>=node[p<<1].vb)node[p].vb=node[p<<1|1].va;
	else if(b[mid+1]>=node[p<<1].vb)node[p].vb=node[p<<1|1].vb;
	else node[p].vb=inf;
   	//vb操作与va同理。
}
void build(int p,int l,int r)//常规操作
{
	node[p].l=l;
	node[p].r=r;
	if(l==r)
	{
		node[p].va=a[l];
		node[p].vb=b[l];
		return;
	}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	merge(p,l,r);
}
void change(int p,int l,int r,int x)//相比于build，只是没有赋l与r的值，再加了个范围判断。
{
	if(l==r)
	{
		node[p].va=a[l];
		node[p].vb=b[l];
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)change(p<<1,l,mid,x);
	else change(p<<1|1,mid+1,r,x);
	merge(p,l,r);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		a[i]=min(x,y);
		b[i]=max(x,y);
	}
	build(1,1,n);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		swap(a[x],a[y]);
		swap(b[x],b[y]);
		change(1,1,n,x);
		change(1,1,n,y);
		if(node[1].va==inf&&node[1].vb==inf)printf("NIE\n");
		else printf("TAK\n");
	}
	return 0;
}
```

---

## 作者：清远学会 (赞：5)

**如果看到这题没有思路，不妨先想想如果卡牌只有一面的情况：**

首先，既然有修改，不妨用线段树来做；

那么对于卡牌只有一面的线段树怎么维护呢？

现在，假设我们已经维护好$tr[l,mid]$与$tr[mid+1,r]$,问题在于如何合并，其实到此，对于$tr[l,mid]$与$tr[mid+1,r]$，只要$a[mid]$小于等于$a[mid+1]$即可完成转移，我们也不用考虑中间的情况；

对此，我们递归求解即可；

**进阶：卡牌可翻转**

对上面的问题扩充到二维，我们可以以上面的思路来解决

也就是说，我们仍可维护$tr[l,mid]$与$tr[mid+1,r]$以左区间的右端点与右区间的左端点来判定是否可以更新区间$[l,r]$

换成人话就是：**多开一维(手动滑稽)**

咳咳，其实是在多维护一个$2 * 2$的数组：$res[2][2]$

**具体怎么食用呢：**

不妨设区间$[l,r]$的左端点为$l[0/1]$,右端点为$r[0/1]$，表左端点我选上面还是下面，右端点选上面或下面；

那么$res[i][j]$就表示当我选$l[i]$和$r[j]$时，是$_1$或否$_0$

那么，在线段树的每个区间都维护这样的一个值，就可以很好地转移啦：
```cpp
inline void Update(int k) {
    tr[k].l[0] = tr[k << 1].l[0]; tr[k].r[0] = tr[k << 1 | 1].r[0];
    tr[k].l[1] = tr[k << 1].l[1]; tr[k].r[1] = tr[k << 1 | 1].r[1];
    tr[k].res[0][0] = tr[k].res[1][1] = tr[k].res[0][1] = tr[k].res[1][0] = 0;
    if(tr[k << 1].r[0] <= tr[k << 1 | 1].l[0]) {
        tr[k].res[1][1] = tr[k].res[1][1] | (tr[k << 1].res[1][0] & tr[k << 1 | 1].res[0][1]);
        tr[k].res[1][0] = tr[k].res[1][0] | (tr[k << 1].res[1][0] & tr[k << 1 | 1].res[0][0]);
        tr[k].res[0][1] = tr[k].res[0][1] | (tr[k << 1].res[0][0] & tr[k << 1 | 1].res[0][1]);
        tr[k].res[0][0] = tr[k].res[0][0] | (tr[k << 1].res[0][0] & tr[k << 1 | 1].res[0][0]);
    }
    if(tr[k << 1].r[1] <= tr[k << 1 | 1].l[0]) {
        tr[k].res[1][1] = tr[k].res[1][1] | (tr[k << 1].res[1][1] & tr[k << 1 | 1].res[0][1]);
        tr[k].res[1][0] = tr[k].res[1][0] | (tr[k << 1].res[1][1] & tr[k << 1 | 1].res[0][0]);
        tr[k].res[0][1] = tr[k].res[0][1] | (tr[k << 1].res[0][1] & tr[k << 1 | 1].res[0][1]);
        tr[k].res[0][0] = tr[k].res[0][0] | (tr[k << 1].res[0][1] & tr[k << 1 | 1].res[0][0]);
    }
    if(tr[k << 1].r[0] <= tr[k << 1 | 1].l[1]) {
        tr[k].res[1][1] = tr[k].res[1][1] | (tr[k << 1].res[1][0] & tr[k << 1 | 1].res[1][1]);
        tr[k].res[1][0] = tr[k].res[1][0] | (tr[k << 1].res[1][0] & tr[k << 1 | 1].res[1][0]);
        tr[k].res[0][1] = tr[k].res[0][1] | (tr[k << 1].res[0][0] & tr[k << 1 | 1].res[1][1]);
        tr[k].res[0][0] = tr[k].res[0][0] | (tr[k << 1].res[0][0] & tr[k << 1 | 1].res[1][0]);
    }
    if(tr[k << 1].r[1] <= tr[k << 1 | 1].l[1]) {
        tr[k].res[1][1] = tr[k].res[1][1] | (tr[k << 1].res[1][1] & tr[k << 1 | 1].res[1][1]);
        tr[k].res[1][0] = tr[k].res[1][0] | (tr[k << 1].res[1][1] & tr[k << 1 | 1].res[1][0]);
        tr[k].res[0][1] = tr[k].res[0][1] | (tr[k << 1].res[0][1] & tr[k << 1 | 1].res[1][1]);
        tr[k].res[0][0] = tr[k].res[0][0] | (tr[k << 1].res[0][1] & tr[k << 1 | 1].res[1][0]);
    }
}
```

应该很好懂，其实可以写成for循环，但我觉得的直接粘比较快……

**对于修改与查询：**

修改的话就是两次单点修改，讲双方的值交换后在赋值即可；

查询咧，就是看根节点$tr[1]$的$res[2][2]$数组中是否为一，只要在$[0][0],[0][1],[1][0],[1][1]$中有一个为真，则表示可以构成，否则GG

具体实现是酱：
```cpp
inline void Change(int k,int l,int r,int a,int b,int c) {
    if(l == r) {
        tr[k].l[0] = tr[k].r[0] = b;
        tr[k].l[1] = tr[k].r[1] = c;
        return ;
    }
    int mid = (l + r) >> 1;
    if(a <= mid) Change(k << 1,l,mid,a,b,c);
    if(a > mid) Change(k << 1 | 1,mid + 1,r,a,b,c);
    Update(k);
}

//主函数这样：
for(int i = 1;i <= m;i ++) {
        int u = read(),v = read();
        swap(a[u][0],a[v][0]),swap(a[u][1],a[v][1]);
        Change(1,1,n,u,a[u][0],a[u][1]); Change(1,1,n,v,a[v][0],a[v][1]);
        if(tr[1].res[1][1] || tr[1].res[1][0] || tr[1].res[0][1] || tr[1].res[0][0])
            printf("TAK\n");
        else 
            printf("NIE\n");
    }
    
```

**额，再放完整代码之前，因为此题时限过严，导致只有90（开O2轻松跑过，或者你会大力卡常）**

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#define N 200500
using namespace std;

inline int read() {
    int x = 0,f = 1; char s = getchar();
    while(s < '0' || s > '9') {if(s == '-') f = -1; s = getchar();}
    while(s >= '0' && s <= '9') {x = x * 10 + s - '0'; s = getchar();}
    return x * f;
}

int n,m;
int a[N][2];
struct node {
    int l[2],r[2];
    int res[2][2];
}tr[N * 4];

inline void Update(int k) {
    tr[k].l[0] = tr[k << 1].l[0]; tr[k].r[0] = tr[k << 1 | 1].r[0];
    tr[k].l[1] = tr[k << 1].l[1]; tr[k].r[1] = tr[k << 1 | 1].r[1];
    tr[k].res[0][0] = tr[k].res[1][1] = tr[k].res[0][1] = tr[k].res[1][0] = 0;
    if(tr[k << 1].r[0] <= tr[k << 1 | 1].l[0]) {
        tr[k].res[1][1] = tr[k].res[1][1] | (tr[k << 1].res[1][0] & tr[k << 1 | 1].res[0][1]);
        tr[k].res[1][0] = tr[k].res[1][0] | (tr[k << 1].res[1][0] & tr[k << 1 | 1].res[0][0]);
        tr[k].res[0][1] = tr[k].res[0][1] | (tr[k << 1].res[0][0] & tr[k << 1 | 1].res[0][1]);
        tr[k].res[0][0] = tr[k].res[0][0] | (tr[k << 1].res[0][0] & tr[k << 1 | 1].res[0][0]);
    }
    if(tr[k << 1].r[1] <= tr[k << 1 | 1].l[0]) {
        tr[k].res[1][1] = tr[k].res[1][1] | (tr[k << 1].res[1][1] & tr[k << 1 | 1].res[0][1]);
        tr[k].res[1][0] = tr[k].res[1][0] | (tr[k << 1].res[1][1] & tr[k << 1 | 1].res[0][0]);
        tr[k].res[0][1] = tr[k].res[0][1] | (tr[k << 1].res[0][1] & tr[k << 1 | 1].res[0][1]);
        tr[k].res[0][0] = tr[k].res[0][0] | (tr[k << 1].res[0][1] & tr[k << 1 | 1].res[0][0]);
    }
    if(tr[k << 1].r[0] <= tr[k << 1 | 1].l[1]) {
        tr[k].res[1][1] = tr[k].res[1][1] | (tr[k << 1].res[1][0] & tr[k << 1 | 1].res[1][1]);
        tr[k].res[1][0] = tr[k].res[1][0] | (tr[k << 1].res[1][0] & tr[k << 1 | 1].res[1][0]);
        tr[k].res[0][1] = tr[k].res[0][1] | (tr[k << 1].res[0][0] & tr[k << 1 | 1].res[1][1]);
        tr[k].res[0][0] = tr[k].res[0][0] | (tr[k << 1].res[0][0] & tr[k << 1 | 1].res[1][0]);
    }
    if(tr[k << 1].r[1] <= tr[k << 1 | 1].l[1]) {
        tr[k].res[1][1] = tr[k].res[1][1] | (tr[k << 1].res[1][1] & tr[k << 1 | 1].res[1][1]);
        tr[k].res[1][0] = tr[k].res[1][0] | (tr[k << 1].res[1][1] & tr[k << 1 | 1].res[1][0]);
        tr[k].res[0][1] = tr[k].res[0][1] | (tr[k << 1].res[0][1] & tr[k << 1 | 1].res[1][1]);
        tr[k].res[0][0] = tr[k].res[0][0] | (tr[k << 1].res[0][1] & tr[k << 1 | 1].res[1][0]);
    }
}

inline void Built(int k,int l,int r) {
    if(l == r) {
        tr[k].l[0] = tr[k].r[0] = a[l][0];
        tr[k].l[1] = tr[k].r[1] = a[l][1];
        tr[k].res[0][0] = tr[k].res[1][1] = 1;
        return ;
    }
    int mid = (l + r) >> 1;
    Built(k << 1,l,mid); 
    Built(k << 1 | 1,mid + 1,r);
    Update(k);
}

inline void Change(int k,int l,int r,int a,int b,int c) {
    if(l == r) {
        tr[k].l[0] = tr[k].r[0] = b;
        tr[k].l[1] = tr[k].r[1] = c;
        return ;
    }
    int mid = (l + r) >> 1;
    if(a <= mid) Change(k << 1,l,mid,a,b,c);
    if(a > mid) Change(k << 1 | 1,mid + 1,r,a,b,c);
    Update(k);
}

int main() {
    n = read();
    for(int i = 1;i <= n;i ++) a[i][0] = read(),a[i][1] = read();
    Built(1,1,n); m = read();
    for(int i = 1;i <= m;i ++) {
        int u = read(),v = read();
        swap(a[u][0],a[v][0]),swap(a[u][1],a[v][1]);
        Change(1,1,n,u,a[u][0],a[u][1]); Change(1,1,n,v,a[v][0],a[v][1]);
        if(tr[1].res[1][1] || tr[1].res[1][0] || tr[1].res[0][1] || tr[1].res[0][0])
            printf("TAK\n");
        else 
            printf("NIE\n");
    }
    return 0;
}

```

---

## 作者：朝夕晨曦_L (赞：4)

题目链接：[P3569 [POI2014] KAR-Cards](https://www.luogu.com.cn/problem/P3569)

来自同机房大佬 @[L_ndyz](https://www.luogu.com.cn/user/358791) 的奇特想法。

首先，这道题目询问能否构成一个不下降序列，这显然可以设计一个状态转移方程，如果符合不下降，就给数组加上一，这实际上是在统计转移的次数，最终只需要询问下标为 $n$ 的数组，若小于 $n$ 说明无法满足整个序列都满足不下降。

这题又添加了一张卡牌有正反面，就需要分情况了。

定义 $f$ 数组第一维存牌的标号，第二维存正面或者反面朝上。

代码如下：
```cpp
    f[i][0] = max(f[i - 1][0] + (a[i] >= a[i-1]), f[i - 1][0] + (a[i] >= b[i-1])); 
    f[i][1] = max(f[i - 1][1] + (b[i] >= a[i-1]), f[i - 1][1] + (b[i] >= b[i-1]));
```

我们发现，每张牌都只有可能被他由一张牌转移，不难想到用矩阵加速。

怎么构建矩阵呢？构建什么矩阵呢？

下面给出转移矩阵：
```cpp
    for(int i = 2; i <= n; i++){
        s[i].st[0][0] = (a[i] >= a[i-1]);
        s[i].st[1][0] = (a[i] >= b[i-1]);
        s[i].st[0][1] = (b[i] >= a[i-1]);
        s[i].st[1][1] = (b[i] >= b[i-1]);
    }
```

然后自定义矩阵运算为取最大值，岂不是完美完成了上面的转移操作啦？

现在考虑更换两张卡片，对于转移矩阵，会对谁有影响？不难想到，只会对更换的这两张和每一张的后面一张（总共四张）卡片有影响，这些我们就重新构造一下转移矩阵就好了。然后用线段树进行计算，求值。经过这些优化（再吸个氧），上面的暴力做法就变得非常华丽啦，收工！

见代码：

```cpp
#include<cmath>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<queue>
using namespace std;
struct pp{
    int st[2][2];//矩阵
    pp(){ memset(st,0,sizeof(st));}
    pp operator*(pp a){
        pp c;
        for(int i = 0;i < 2; i++){
            for(int j = 0;j < 2; j++){
                for(int k = 0;k < 2; k++){
                    c.st[i][j] = max(c.st[i][j],st[i][k] + a.st[k][j]);//广义矩阵乘法
                }
            }
        }
        return c;
    }
};
int n,m;
int a[200100],b[200100];
pp s[200100];
void change_point(int i){//改点值
    if(i == 1) return ;//初始矩阵不用改
    s[i].st[0][0] = (a[i] >= a[i - 1]); s[i].st[1][0] = (a[i] >= b[i - 1]);
    s[i].st[0][1] = (b[i] >= a[i - 1]); s[i].st[1][1] = (b[i] >= b[i - 1]);
}
struct tree{ int l,r; pp sum; }t[800100];
void build(int p,int L,int R){
    t[p].l = L;  t[p].r = R;
    if(L == R){ t[p].sum = s[L];return ;}
    int mid = (L + R) >> 1;
    build(p * 2,L,mid);build(p * 2 + 1,mid + 1,R);
    t[p].sum = t[p * 2].sum * t[p * 2 + 1].sum;
}
void change_tree(int p,int x){
    if(t[p].l == t[p].r){
        t[p].sum = s[t[p].l]; return ;
    }
    int mid = (t[p].l + t[p].r) >> 1;
    if(x <= mid) change_tree(p * 2,x);
    else change_tree(p * 2 + 1,x);
    t[p].sum = t[p*2].sum * t[p * 2 + 1].sum;
}
inline int read(){
	int x = 0,f = 1; char ch=getchar();
	while (ch < '0' || ch > '9'){if (ch == '-') f = -1;ch = getchar();}
	while (ch >= '0'&&ch <= '9'){x = x * 10 + ch - 48; ch = getchar();}
	return x * f;
}
void swap(int &x,int &y){
    int t=x; x=y; y=t;
}
signed main(){
    cin>>n;
    for(int i = 1; i <= n; i++){
        a[i] = read();b[i] = read();
    }
    s[1].st[0][0]=1;s[1].st[0][1]=1;//构造初始状态矩阵
    for(int i = 2; i <= n; i++){//根据转移方式构造每一步的矩阵
        s[i].st[0][0] = (a[i] >= a[i-1]);
        s[i].st[1][0] = (a[i] >= b[i-1]);
        s[i].st[0][1] = (b[i] >= a[i-1]);
        s[i].st[1][1] = (b[i] >= b[i-1]);
    }
    build(1,1,n);//建线段树
    cin>>m;
    for(int i = 1; i <= m; i++){
        int x, y;  x = read();  y = read();
        swap(a[x],a[y]);  swap(b[x],b[y]);
        //更换两张卡，这两张卡只会对 x，x+1，y，y+1的矩阵有影响  
        if(x != 1)     change_point(x),    change_tree(1,x);
        if(x + 1 <= n) change_point(x + 1),change_tree(1,x + 1);
        if(y != 1)     change_point(y),    change_tree(1,y);
        if(y + 1 <= n) change_point(y + 1),change_tree(1,y + 1);
        pp ans = t[1].sum;
        if(ans.st[0][0] < n && ans.st[0][1] < n) puts("NIE");//无法构成长度为 n 的不下降序列
        else puts("TAK");
    }
	return 0;
}
```

---

## 作者：VitrelosTia (赞：3)

以此题解记录我第一道在考场上无限接近 AC 的紫题。

首先考虑一个简单的情况，假如正反面是一样的，那么这些牌就是一个序列。换牌的操作其实可以转化成单点修改，然后区间维护一个单调性，这个线段树非常好做。

```cpp
struct Info {
	int lv, rv;
	bool slv;
};
Info operator + (const Info &l, const Info &r) { // 这个就是 pushup
	Info res;
	res.lv = l.lv; res.rv = r.rv;
	res.slv = (l.slv && l.rv <= r.lv && r.slv);
	return res;
}
```

然后我们回到原题，我们还是考虑按照差不多的思路来做，大力讨论所有的区间两端选择正反是否能有单调性，同时记录区间左右的正反值，然后合并区间信息就还是大力分讨，有点麻烦，具体看代码吧。

```cpp
struct Info {
	int lvx, lvy, rvx, rvy;
	bool xx, xy, yx, yy;
};
Info operator + (const Info &l, const Info &r) {
	Info res;
	res = {l.lvx, l.lvy, r.rvx, r.rvy, false, false, false, false};
	if (l.xx && l.rvx <= r.lvx && r.xx) res.xx = true;
	if (l.xx && l.rvx <= r.lvx && r.xy) res.xy = true;
	if (l.xx && l.rvx <= r.lvy && r.yx) res.xx = true;
	if (l.xx && l.rvx <= r.lvy && r.yy) res.xy = true;
	if (l.xy && l.rvy <= r.lvx && r.xx) res.xx = true;
	if (l.xy && l.rvy <= r.lvx && r.xy) res.xy = true;
	if (l.xy && l.rvy <= r.lvy && r.yx) res.xx = true;
	if (l.xy && l.rvy <= r.lvy && r.yy) res.xy = true;
	if (l.yy && l.rvy <= r.lvy && r.yy) res.yy = true;
	if (l.yy && l.rvy <= r.lvy && r.yx) res.yx = true;
	if (l.yy && l.rvy <= r.lvx && r.xy) res.yy = true;
	if (l.yy && l.rvy <= r.lvx && r.xx) res.yx = true;
	if (l.yx && l.rvx <= r.lvy && r.yy) res.yy = true;
	if (l.yx && l.rvx <= r.lvy && r.yx) res.yx = true;
	if (l.yx && l.rvx <= r.lvx && r.xy) res.yy = true;
	if (l.yx && l.rvx <= r.lvx && r.xx) res.yx = true;
	return res;
}
```

我觉得这个东西其实非常好写，就是把所有区间能单调的情况全部列出来。

最后是一个坑点，也是我考场上没能过题的原因：区间长度为 1 时，区间两端正反不同的情况是不行的！

然后其它就是板子了。

[完整代码](https://www.luogu.com.cn/paste/0ig4w5zt)。

---

## 作者：Treaker (赞：3)

$$\color{cornflowerblue}{\mathcal{Treaker}}$$
# 线段树
正解是线段树

![](https://cdn.luogu.com.cn/upload/image_hosting/ur0ocnuo.png)

什么？线段树？一脸懵逼。

其实仔细观察还是可以发现端倪的~~抱歉，我没看出来~~。

我们对于线段树，维护这个区间能否构成单调不减的序列，维护一个左端点和右端点是背面还是正面，$tr[0/1][0/1]$，表示左端点是正面或背面，右端点是正面或背面能否构成单调不减的序列。分16种情况转移

```cpp
inline void up() {tr[0][0] = tr[1][0] = tr[0][1] = tr[1][1] = 0; for(R int i = 0;i < 2;++ i) for(R int j = 0;j < 2;++ j) for(R int k = 0;k < 2;++ k) for(R int l = 0;l < 2;++ l) tr[i][j] = tr[i][j] | (ls -> tr[i][k] && rs -> tr[l][j] && a[ls -> r][k] <= a[rs -> l][l]);}
```
~~码风清新靓丽~~


完整代码如下：
```cpp
#include <cstdio>
#include <iostream>
#define R register
const int N = 200002;
inline int read()
{
    int x = 0 , f = 1;  char ch = getchar();
    while(ch < '0' || ch > '9') {if(ch == '-')  f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();}
    return x * f;
}
int n , m , t;
int a[N][2];
inline void swap(R int &a,R int &b) {t = a; a = b; b = t;}
struct Segment_Tree
{
	#define mid ((p -> l + p -> r) >> 1)
	struct node
	{
		node *ls , *rs;
		int l , r , tr[2][2];
		node(R int l = 0,R int r = 0) : l(l) , r(r) {ls = rs = NULL;tr[0][0] = tr[0][1] = tr[1][0] = tr[1][1] = 0;}
		inline bool ok() {return tr[0][0] || tr[0][1] || tr[1][0] || tr[1][1];}
		inline void up() {tr[0][0] = tr[1][0] = tr[0][1] = tr[1][1] = 0; for(R int i = 0;i < 2;++ i) for(R int j = 0;j < 2;++ j) for(R int k = 0;k < 2;++ k) for(R int l = 0;l < 2;++ l) tr[i][j] = tr[i][j] | (ls -> tr[i][k] && rs -> tr[l][j] && a[ls -> r][k] <= a[rs -> l][l]);}
	}*root , *tail , pool[N << 2];
	Segment_Tree() {tail = pool;}
	void build(R node *&p,R int l,R int r)
	{
		p = new (tail ++)node(l,r);
		if(l == r) return (void)(p -> tr[0][0] = p -> tr[1][1] = 1);
		build(p -> ls,l,mid); build(p -> rs,mid + 1,r);
		p -> up();
	}
	void chenge(R node *p,R int x)
	{
		if(p -> l == p -> r) return;
		if(x <= mid) chenge(p -> ls,x);
		else chenge(p -> rs,x);
		p -> up();
	}
	inline void LOL()
	{
		n = read();
		for(R int i = 1;i <= n;++ i) a[i][0] = read() , a[i][1] = read();
		build(root,1,n);
		m = read();
		for(R int i = 1 , x , y;i <= m;++ i)
		{
			x = read(); y = read();
			swap(a[x][0],a[y][0]); swap(a[x][1],a[y][1]);
			chenge(root,x); chenge(root,y);
			puts(root -> ok() ? "TAK" : "NIE");
		}
	}
}CF;
int main()
{
	CF.LOL();
	return 0;
}
```


---

## 作者：灼眼的夏娜 (赞：2)

今天模拟赛t2，暴力可以水过60分（开心）

然而当老师说这题正解是线段树时一脸懵逼（思维僵化的太狠了）

不过在讲完之后这题还是很好写的

思路：

先考虑每个位置只有一个数字你会不会做，很简单吧，只要看看交换完的两个

值是否会对前后两个造成影响，那么线段树直接维护出区间是否能构成不下降

的序列，每次合并的时候只需要判断 可不可以，同时判断是否大于等于三者如

果同时满足就OK了那么现在一个位置有两个数字，一个非常朴素的想法就是直

接维护一下左端点取哪个数字，右端点取那个数字就行的时候是否可行。转移

基本同上，现在我们有了两种取值，$a[0],a[1]$，那就把线段树开成$[0/1]$

类型的，0代表选了反面，1代表选了正面即$T[i][0/1][0/1]$，因为要维护左

右端点的所以是两个$[0/1]$，那$update$时候大力讨论一下就完了

具体操作请见代码：

## code
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define R register
#define LL k<<1
#define RR k<<1|1

using namespace std;
const int N = 2e5+5;
int n, m, a[N][2];
int T[N<<2][2][2];

inline void update(int k, int l, int r) {//比较恶心的update
	R int mid = (l + r) >> 1;
	T[k][1][1] = T[k][0][0] = T[k][1][0] = T[k][0][1] = 0;
	for(R int i = 0;i < 2;++ i)
		for(R int j = 0;j < 2;++ j) {//讨论l右端点与r左端点的大小情况
			if(a[mid][0] <= a[mid + 1][0])
				T[k][i][j] |= T[LL][i][0] & T[RR][0][j];
			if(a[mid][1] <= a[mid + 1][0])
				T[k][i][j] |= T[LL][i][1] & T[RR][0][j];
			if(a[mid][0] <= a[mid + 1][1])
				T[k][i][j] |= T[LL][i][0] & T[RR][1][j];
			if(a[mid][1] <= a[mid + 1][1])
				T[k][i][j] |= T[LL][i][1] & T[RR][1][j];
		}
}

inline void build(int k, int l, int r) {
	while(l == r) {//叶子节点，因为只有一个，[1][0]，[0][1]是不会出现的
		T[k][1][1] = T[k][0][0] = 1;//能够成合法序列将其赋成1
		return;
	}
	R int mid = (l + r) >> 1;
	build(LL, l, mid);
	build(RR, mid + 1, r);
	update(k, l, r);
}

void change(int k, int l, int r, int pos, int vi, int vc) {
	if(l == r) {
		a[l][0] = vi, a[l][1] = vc;//简单的交换
		return;
	}
	R int mid = (l + r) >> 1;
	if(pos <= mid) change(LL, l, mid, pos, vi, vc);
	else change(RR, mid + 1, r, pos, vi, vc);
	update(k, l, r);
}

int main() {
//	freopen("b.in","r",stdin);
//	freopen("b.out","w",stdout);
	scanf("%d",&n);
	for(R int i = 1;i <= n;++ i) scanf("%d%d",&a[i][0], &a[i][1]);
	scanf("%d",&m);
	build(1, 1, n);
	for(R int i = 1, c ,d;i <= m;++ i) {
		scanf("%d%d",&c, &d);
		R int x = a[c][0], y = a[c][1], xx = a[d][0], yy = a[d][1];
		change(1, 1, n, c, xx, yy), change(1, 1, n, d, x, y);
        //最终答案归结到T[1]上，四种情况中只要有一种合法即可
		if(T[1][1][1] + T[1][0][0] + T[1][1][0] + T[1][0][1] >= 1) puts("TAK");
		else puts("NIE");
	}
	fclose(stdin);fclose(stdout);
	return 0;
}
```
2

---

## 作者：daniEl_lElE (赞：1)

考虑如何 $O(n)$ 判断一个区间是否合法，考虑 $dp_{i,0/1}$，表示看到 $i$ 位，选择的是 $x_i/y_i$，是否有一种方案可以让前 $i$ 个单调不降。转移时朴素的。

有了修改操作，$O(nq)$ 的做法显然过不去。考虑动态 dp，将上述 $dp_{i,0/1}$ 的转移用矩阵表示。每次交换本质上就是单点修改。总复杂度 $O((n+q)\log nV^3)$，其中 $V$ 是矩阵大小，本题中为 $2$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define min(i,j) ((i<j)?i:j)
#define mid ((l+r)>>1)
using namespace std;
struct node{
	int lnum[2],rnum[2];
	bool ok[2][2];
}ept;
node merge(node x,node y){
	node z=ept;
	z.lnum[0]=x.lnum[0];
	z.lnum[1]=x.lnum[1];
	z.rnum[0]=y.rnum[0];
	z.rnum[1]=y.rnum[1];
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			for(int k=0;k<2;k++){
				for(int l=0;l<2;l++){
					if(x.rnum[j]<=y.lnum[k]){
						z.ok[i][l]|=(x.ok[i][j]&y.ok[k][l]);
					}
				}
			}
		}
	}
	return z;
}
pair<int,int> a[1000005];
struct sgt{
	node f[1000005];
	void build(int i,int l,int r){
		if(l==r){
			f[i].lnum[0]=f[i].rnum[0]=a[l].first;
			f[i].lnum[1]=f[i].rnum[1]=a[l].second;
			f[i].ok[0][0]=f[i].ok[1][1]=1;
			return ;
		}
		build(i*2,l,mid),build(i*2+1,mid+1,r);
		f[i]=merge(f[i*2],f[i*2+1]);
	}
	void change(int i,int l,int r,int pos){
		if(l==r){
			f[i].lnum[0]=f[i].rnum[0]=a[l].first;
			f[i].lnum[1]=f[i].rnum[1]=a[l].second;
			f[i].ok[0][0]=f[i].ok[1][1]=1;
			return ;
		}
		if(pos<=mid) change(i*2,l,mid,pos);
		else change(i*2+1,mid+1,r,pos);
		f[i]=merge(f[i*2],f[i*2+1]);
	}
}tree;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	int n; cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].first>>a[i].second;
	tree.build(1,1,n);
	int m; cin>>m;
	for(int i=1;i<=m;i++){
		int x,y; cin>>x>>y;
		swap(a[x],a[y]);
		tree.change(1,1,n,x);
		tree.change(1,1,n,y);
		node tmp=tree.f[1];
		if(tmp.ok[0][0]|tmp.ok[0][1]|tmp.ok[1][0]|tmp.ok[1][1]) cout<<"TAK\n";
		else cout<<"NIE\n";
	} 
	return 0;
}
```

---

## 作者：Kevin_Mamba (赞：1)

又是一篇线段树，但又不完全是线段树。

在这里先推荐个板子题目，算法与本题类似。

[$Maze \space 2D$](https://www.luogu.com.cn/problem/CF413E)

## 题意

~~感觉翻译不是很负责，最后句号都没打。~~

有 $n$ 张卡牌，每张都有两个面，每面有一个数。

有 $m$ 此操作，给定 $x,y$，交换第 $x$ 张卡牌和第 $y$ 张卡牌。每次**按操作后当前卡牌顺序**，随意翻牌，判断有没有一种翻牌策略能使**所有卡牌正面朝上的数字**组成一个**不下降序列**。

## $Solution$


虽然一个卡牌序列中间可能出现的情况有很多种，具体一点就是 $2^n$ 种。

但是因为只需要**判断**能不能组成不下降序列，所以可以取**最优**方案，每张卡牌尽量取数字比较小的一面，实在不行取大的一面，康康能否“坚持到最后”。

复杂度 $\mathcal{O(nm)}$ 。

```cpp
#include<bits/stdc++.h>
#define il inline
#define re register
using namespace std;

const int N=2e5+10;

int n,a[N],b[N],m;

int main()
{
	scanf("%d",&n);
	for(re int i=1;i<=n;i++) 
	{
		scanf("%d%d",&a[i],&b[i]);	
		if(a[i]>b[i]) swap(a[i],b[i]);
	}
	scanf("%d",&m);	
	for(re int i=1;i<=m;i++)
	{
		re int x,y;
		scanf("%d%d",&x,&y);
		swap(a[x],a[y]); swap(b[x],b[y]);
		bool f=true;
		int last=a[1];
		for(re int j=2;j<=n;j++)
		{
			if(a[j]>=last) last=a[j];
			else if(b[j]>=last) last=b[j];
			else {
				f=false;
				break;
			}
		}
		puts(f?"TAK":"NIE");
	}
	return 0;
} 
```


~~紫题会就这~~ 但是对于 $n\le2\times10^5,m\le 10^6$ 来说肯定不行，考虑优化。

### 正解

> $Maze\space 2D$ 算法，简称“妹子”算法，是用线段树来维护四个点的连通的算法。

有点抽象，我们需要**感性的理解**。

不同的序列有很多种，但对于子序列 $[l,r]$，**第 $l$ 张卡牌和第 $r$ 张卡牌的不同排列至多有四种**：正正，正反，反正，反反。判断每种能不能组成不下降子序列。

只要每次维护这四个值（判断），再用线段树 $pushup$ 即可。

维护比较简单，这里重点讲怎么 $pushup$。

![](https://cdn.luogu.com.cn/upload/image_hosting/b2vidy0r.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

如图，对于区间 $[L,R]$，要由 $[l_1,r_1],[l_2,r_2]$ 转移得来。

带红色的点的卡片是作为起点和终点的卡片，左边的 $2$ 张红卡要向右边的 $2$ 张红卡连线，共 $4$ 条。蓝色线为已知 $[l_1,r_1],[l_2,r_2]$ 分别维护的四个值。

我们发现图好像不连通，中间没有“关节”。于是转移时需要**加“关节”并且判断是否能行**。“关节”指 $r_1,l_2$ 两卡之间的连线。下面举一个转移的例子。

![](https://cdn.luogu.com.cn/upload/image_hosting/2za1q4v2.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

图中的绿线就是一个“关节”，但是成立的条件是 $r_{1_\text正}\le l_{2_\text 反}$。这样才可能是不下降的。这样红卡 $L_\text 正,R_\text反$ 就连通了。判断转移如下。

$$up_L\rightarrow down_R=up_{l_1}\rightarrow up_{r_1}\And up_{r_1}\le up_{l_2} \And up_{l_2}\rightarrow up_{r_2}$$

注：$up$ 指正面，$down$ 指反面，如图上位置。

当然，这只是一个转移，具体见代码。注意代码中对变量名义的注释，帮助理解。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define il inline
#define re register
using namespace std;

const int N=2e5+10;

int n,a[N],b[N],m;

struct path { bool p1,p2,p3,p4; };
// up->up; up->down; down->up; down->down
// up 正 ; down 反 

struct Tree{ int l,r; path S; } t[N<<2];

il void print(re path p){ cerr<<p.p1<<" "<<p.p2<<" "<<p.p3<<" "<<p.p4<<endl; }

il void pushup(re int p)
{
	re int mid=(t[p].l+t[p].r)>>1,ls=p<<1,rs=p<<1|1;
	// mid 关节处 ; ls,rs 左、右儿子 
	
	// 转移，可以自己推一推 
	
	t[p].S.p1 	
	=  t[ls].S.p1 && a[mid]<=a[mid+1] && t[rs].S.p1 
	|| t[ls].S.p1 && a[mid]<=b[mid+1] && t[rs].S.p3
	|| t[ls].S.p2 && b[mid]<=a[mid+1] && t[rs].S.p1 
	|| t[ls].S.p2 && b[mid]<=b[mid+1] && t[rs].S.p3 ;
		
	t[p].S.p2
	=  t[ls].S.p1 && a[mid]<=a[mid+1] && t[rs].S.p2 
	|| t[ls].S.p1 && a[mid]<=b[mid+1] && t[rs].S.p4
	|| t[ls].S.p2 && b[mid]<=a[mid+1] && t[rs].S.p2
	|| t[ls].S.p2 && b[mid]<=b[mid+1] && t[rs].S.p4 ;
	
	
	t[p].S.p3
	=  t[ls].S.p3 && a[mid]<=a[mid+1] && t[rs].S.p1
	|| t[ls].S.p3 && a[mid]<=b[mid+1] && t[rs].S.p3
	|| t[ls].S.p4 && b[mid]<=a[mid+1] && t[rs].S.p1
	|| t[ls].S.p4 && b[mid]<=b[mid+1] && t[rs].S.p3 ;
		
	t[p].S.p4
	=  t[ls].S.p3 && a[mid]<=a[mid+1] && t[rs].S.p2 
	|| t[ls].S.p3 && a[mid]<=b[mid+1] && t[rs].S.p4 
	|| t[ls].S.p4 && b[mid]<=a[mid+1] && t[rs].S.p2
	|| t[ls].S.p4 && b[mid]<=b[mid+1] && t[rs].S.p4 ;
	
	// 以上使用变量名是高频错处，注意检查  
			
}

il void build(re int p,re int l,re int r)
{
	t[p].l=l,t[p].r=r;
	if(l==r)
		return t[p].S=(path){true,true,false,true},void();
	re int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	pushup(p);
}

il void modify(re int p,re int x)
{
	if(t[p].l==t[p].r) return ;
	re int mid=(t[p].l+t[p].r)>>1;
	if(x<=mid) modify(p<<1,x);
	else modify(p<<1|1,x);
	pushup(p); 
}

int main()
{
	scanf("%d",&n);
	for(re int i=1;i<=n;i++) 
	{
		scanf("%d%d",&a[i],&b[i]);	
		if(a[i]>b[i]) swap(a[i],b[i]); 
		// 正反等级一样，按顺序对于操作比较方便 
	}
	build(1,1,n);
	scanf("%d",&m);	
	for(re int i=1;i<=m;i++)
	{
		re int x,y;
		scanf("%d%d",&x,&y);
		swap(a[x],a[y]); swap(b[x],b[y]);
		// 记得换 
		modify(1,x); modify(1,y);
		puts(t[1].S.p1||t[1].S.p2||t[1].S.p3||t[1].S.p4?"TAK":"NIE");
	}
	return 0;
} 
```


---

## 作者：nofind (赞：1)

题意：https://www.luogu.org/problemnew/show/P3569

这道题我们用线段树维护整个序列。

对于每个节点,我们维护w0和w1,表示区间开头选较大的(1)/较小的(0)/无解(-1),在右端点从哪里出来。

转移时贪心转移。

见代码。

code:
```
#include<bits/stdc++.h>
using namespace std;
#define ls(p) (p<<1)
#define rs(p) (p<<1|1)
#define w0(p) (tree[p].w0)
#define w1(p) (tree[p].w1)
const int maxn=3*1e5+10;
int n,m;
int a[maxn][2];//0->较小的,1->较大的 
struct seg
{
    int w0,w1;
}tree[maxn<<2];
void up(int p,int l,int r)
{
    int mid=(l+r)>>1,t;
    if((t=w0(ls(p)))==-1) w0(p)=-1;//如果左儿子就到不了右节点,那么直接-1 
    else
    {
        t=a[mid][t];
        if(t<=a[mid+1][0]) w0(p)=w0(rs(p));//贪心接右儿子左端最小值 
        else if(t<=a[mid+1][1]) w0(p)=w1(rs(p));//否则就接最大值 
        else w0(p)=-1;//-1
    }
    //同理 
    if((t=w1(ls(p)))==-1) w1(p)=-1;
    else
    {
        t=a[mid][t];
        if(t<=a[mid+1][0]) w1(p)=w0(rs(p));
        else if(t<=a[mid+1][1]) w1(p)=w1(rs(p));
        else w1(p)=-1;
    }
}
void build(int p,int l,int r)
{
    if(l==r)
    {
        w0(p)=0;w1(p)=1;return;
    }
    int mid=(l+r)>>1;
    build(ls(p),l,mid);build(rs(p),mid+1,r);
    up(p,l,r);
}
void change(int p,int l,int r,int pos)
{
    if(l==r) return;
    int mid=(l+r)>>1;
    if(pos<=mid) change(ls(p),l,mid,pos);
    else change(rs(p),mid+1,r,pos);
    up(p,l,r);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&a[i][0],&a[i][1]);
        if(a[i][0]>a[i][1]) swap(a[i][0],a[i][1]);
    }
    build(1,1,n);
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        int x,y;scanf("%d%d",&x,&y);
        swap(a[x][0],a[y][0]);swap(a[x][1],a[y][1]);//交换两点 
        change(1,1,n,x);change(1,1,n,y);//更新 
        puts(w0(1)==-1?"NIE":"TAK");
    }
    return 0;
}
```


---

## 作者：ran_qwq (赞：1)

有修改，考虑线段树维护。

设 $a_{i,0}$ 为正面，$a_{i,1}$ 为反面。

设 $val_{id,0/1,0/1}$ 为编号为 $id$ 的区间 $[l,r]$，$a_l$ 是正 / 反面，$a_r$ 是正 / 反面，有没有单调不降的方案。 因为合并区间只和左右端点有关，所以只需要维护左右端点情况。

建树时 $val_{id,0,0}=val_{id,1,1}=1$（注意不能同一个位置既是正面也是反面）。

合并 $[l,mid]$ 和 $[mid+1,r]$ 两个区间时，枚举左儿子右端点正反面 $i$ 和右儿子左端点正反面 $j$。如果 $a_{mid,i}\le a_{mid+1,j}$，则再枚举左儿子左端点正反面 $k$ 和右儿子右端点正反面 $p$。那么 $val_{id,k,p}\leftarrow val_{id,k,p}\operatorname{or}(val_{ls,k,i}\operatorname{and}val_{rs,j,p})$（$ls$ 表示左儿子，$rs$ 表示右儿子）。

修改就是平凡的线段树修改，查询就是判断 $val_{1,i,j}(i,j\in\{0,1\})$ 有没有 $1$。

---

## 作者：huyufeifei (赞：1)

首先考虑不带修，一个贪心就好了对吧。

那么带修呢？我们肯定不能每次都重新贪心，所以考虑维护一段区间贪心出来的结果，每次只修改若干区间，用几个子区间的值组合成一个大区间的值。

考虑线段树。因为一个区间的贪心出来的值只与开头元素的取值有关，所以维护第一个元素取a/b时此区间最后元素的最小取值即可。

然后合并的时候顺便考虑一下无解的情况，回答询问时只要看线段树的根节点是否无解即可。

具体实现看代码
(注意常数优化，我一开始常数有点大，TLE了一个点....)
```cpp
#include <cstdio>
#include <algorithm>

inline void read(int &x) {
	 x = 0;
	 char c = getchar();
	 while(c < '0' || c > '9') {
		c = getchar();
	 }
	 while(c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	 }
	 return;
}

const int N = 200010, INF = 0x3f3f3f3f;

int high_l[N << 2], a[N], b[N], high_s[N << 2];

inline void pushup(int l, int r, int o) {
	int ls = o << 1;
	int rs = ls | 1;
	int mid = (l + r) >> 1;
	// high_small[o] 
	if(high_s[ls] == -1) {
		high_s[o] = -1;
	}
	else {
		if(a[mid + 1] >= high_s[ls]) {
			high_s[o] = high_s[rs];
		}
		else if(b[mid + 1] >= high_s[ls]) {
			high_s[o] = high_l[rs];
		}
		else {
			high_s[o] = -1;
		}
	}
	// high_large[o]
	if(high_l[ls] == -1) {
		high_l[o] = -1;
	}
	else {
		if(a[mid + 1] >= high_l[ls]) {
			high_l[o] = high_s[rs];
		}
		else if(b[mid + 1] >= high_l[ls]) {
			high_l[o] = high_l[rs];
		}
		else {
			high_l[o] = -1;
		}
	}
	
	return;
}

inline void build(int l, int r, int o) {
	if(l == r) {
		high_s[o] = small(r);
		high_l[o] = large(r);
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, o << 1);
	build(mid + 1, r, o << 1 | 1);
	pushup(l, r, o);
	return;
}

inline void update(int p, int l, int r, int o) {
	if(l == r) {
		high_s[o] = small(r);
		high_l[o] = large(r);
		return;
	}
	int mid = (l + r) >> 1;
	if(p <= mid) {
		update(p, l, mid, o << 1);
	}
	else {
		update(p, mid + 1, r, o << 1 | 1);
	}
	pushup(l, r, o);
	return;
}

int main() {
	int n;
	read(n);
	for(int i = 1; i <= n; i++) {
		read(a[i]);
		read(b[i]);
		if(a[i] > b[i]) {
			std::swap(a[i], b[i]);
		}
	}
	build(1, n, 1);
	int m;
	read(m);
	for(int i = 1, x, y; i <= m; i++) {
		read(x);
		read(y);
		if(x > y) {
			std::swap(x, y);
		}
		std::swap(a[x], a[y]);
		std::swap(b[x], b[y]);
		update(x, 1, n, 1);
		update(y, 1, n, 1);
		if(high_l[1] != -1 || high_s[1] != -1) {
			printf("TAK\n");
		}
		else {
			printf("NIE\n");
		}
	}
	　
	
	return 0;
}

```

---

## 作者：Night_sea_64 (赞：0)

很显然的贪心：每个位置肯定选能选的尽量小的值。比如第一个位置是 $2,5$，第二个位置是 $3,4$，后面还有一些值。那么为了更容易形成一个单调不降的序列，第一个位置肯定选 $2$，第二个位置选 $3$。

考虑线段树。线段树中每个区间记录两个答案。一个是左端点选择较小值时，右端点能取得的最小值。另一个是左端点选择较大值时，右端点能取得的最小值。如果无解的话记录为 $-1$。

两个相邻区间的答案合并时，遵循这个贪心的原则。如果左区间答案比右区间的左端点的较大值还要大那么就无解，否则贪心地选右区间的左端点值尽可能小的方案。

交换当单点修改来做。上述过程中可以看出要实时维护当前每个位置的两个值分别是什么。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,m,xiao[200010],da[200010];
struct segtree{int l,r,ans1,ans2;}a[800010];
void pushup(int x)
{
    if(a[x*2].ans1==-1)a[x].ans1=-1;
    else
    {
        if(a[x*2].ans1>da[a[x*2+1].l])a[x].ans1=-1;
        else if(a[x*2].ans1>xiao[a[x*2+1].l])
            a[x].ans1=a[x*2+1].ans2;
        else a[x].ans1=a[x*2+1].ans1;
    }
    if(a[x*2].ans2==-1)a[x].ans2=-1;
    else
    {
        if(a[x*2].ans2>da[a[x*2+1].l])a[x].ans2=-1;
        else if(a[x*2].ans2>xiao[a[x*2+1].l])
            a[x].ans2=a[x*2+1].ans2;
        else a[x].ans2=a[x*2+1].ans1;
    }
}
void build(int x,int l,int r)
{
    a[x].l=l,a[x].r=r;
    if(l==r)
    {
        a[x].ans1=xiao[l],a[x].ans2=da[l];
        return;
    }
    int mid=(l+r)/2;
    build(x*2,l,mid);
    build(x*2+1,mid+1,r);
    pushup(x);
}
void change(int x,int p,int k1,int k2)
{
    if(a[x].l==p&&a[x].r==p)
    {
        a[x].ans1=k1,a[x].ans2=k2;
        return;
    }
    int mid=(a[x].l+a[x].r)/2;
    if(p<=mid)change(x*2,p,k1,k2);
    else change(x*2+1,p,k1,k2);
    pushup(x);
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>xiao[i]>>da[i];
        if(xiao[i]>da[i])swap(xiao[i],da[i]);
    }
    build(1,1,n);
    cin>>m;
    while(m--)
    {
        int x,y;
        cin>>x>>y;
        swap(xiao[x],xiao[y]);
        swap(da[x],da[y]);
        change(1,x,xiao[x],da[x]);
        change(1,y,xiao[y],da[y]);
        //必须先 swap 再 change，因为 pushup 时会用到实际值
        if(a[1].ans1>-1)cout<<"TAK\n";
        else cout<<"NIE\n";
    }
    return 0;
}
```

---

## 作者：under_the_time (赞：0)

## 题意

> 有 $n$ 个元素，第 $i$ 个元素有两个权值 $a_i$ 和 $b_i$；有 $m$ 次操作，每次操作会交换两个元素的位置，且都需要回答：是否存在一种方案，使得每个元素各选择一个权值后，组成的序列从左到右单调不降。

## 解法

完全可以把交换操作看作两次单点修改，每次只需要考虑一个元素的变化对答案的影响即可。对于一个区间中的元素，显然开头的数越小，该区间能够单调不降的概率越大。不妨设 $a_i<b_i$，考虑线段树，对于区间 $[L,R]$ 我们维护两个值：

- 第 $L$ 个元素选择 $a_L$，第 $R$ 个元素尽量小的情况下，第 $R$ 个元素会选择 $a_R$，$b_R$ 或无解；
- 第 $L$ 个元素选择 $b_L$，第 $R$ 个元素尽量小的情况下，第 $R$ 个元素会选择 $a_R$，$b_R$​ 或无解。

合并两个相邻区间的信息时，我们枚举左区间 $[L,R]$ 选择 $a_L$ 或 $b_L$、右区间 $[L',R']$ 选择 $a_{L'}$ 或 $b_{L'}$，判断 $a_R<b_{L'}$ 是否成立（已经保证小区间内单调不降或无解）；最后贪心地让合并后的区间 $[L,R']$ 末尾选择的数尽可能小。总时间复杂度 $O(n+m\log n)$。

## 实现

开两个数组 $x,y$ 维护这两个值（直接存末尾卡牌选择的值）。在建树、修改的时候用子区间信息进行更新。令该区间为 $[l,r]$，两个子区间的编号为 $L,R$（以 $mid=\lfloor\cfrac{l+r}{2}\rfloor$ 为界），我们枚举用 $x[L]$ 还是 $y[L]$ 连接两个子区间、用 $x[R]$ 还是 $y[R]$ 作为结尾，并且优先考虑使用较小的 $x[R]$ 作为结尾。我们在修改的时候顺便更换 $a,b$ 数组，则只需判断 $x[L]$ 或者 $y[L]$ 是否不大于 $a[mid+1]$ 或者 $b[mid+1]$（共 $4$ 种）。最终该区间的末尾取决于 $R$ 子区间末尾的选择。注意处理好无解的情况。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
struct Card { int A,B; } a[maxn];
int x[maxn << 2], y[maxn << 2]; // x 第一张小，y 第一张大
#define lson l,mid,rt << 1
#define rson mid + 1,r,rt << 1 | 1
const int inf = 1e7 + 5;
void update(int l,int r,int rt) {
    int mid = l + r >> 1;
    int L = rt << 1, R = rt << 1 | 1; // 两个子区间的编号
    x[rt] = y[rt] = inf;
    // 分类讨论
    if (x[L] <= a[mid + 1].A) x[rt] = x[R];
    else if (x[L] <= a[mid + 1].B) x[rt] = y[R];
    if (y[L] <= a[mid + 1].A) y[rt] = x[R];
    else if (y[L] <= a[mid + 1].B) y[rt] = y[R];
}
void build(int l,int r,int rt) {
    if (l == r) return x[rt] = a[l].A, y[rt] = a[l].B, void(0);
    int mid = l + r >> 1;
    build(lson); build(rson); update(l,r,rt);
}
int now;
void modify(int l,int r,int rt,Card k) {
    if (l == r) return x[rt] = k.A, y[rt] = k.B, void(0);
    int mid = l + r >> 1;
    if (now <= mid) modify(lson,k);
    else modify(rson,k);
    update(l,r,rt);
}
int n,m;
int main() {
    scanf("%d",&n);
    for (int i = 1;i <= n;i ++) {
        scanf("%d%d",&a[i].A,&a[i].B);
        if (a[i].A > a[i].B)
            swap(a[i].A,a[i].B);
    }
    build(1,n,1);
    scanf("%d",&m);
    for (int i = 1,u,v;i <= m;i ++) {
        scanf("%d%d",&u,&v);
        swap(a[u],a[v]);
        now = u; modify(1,n,1,a[u]);
        now = v; modify(1,n,1,a[v]);
        puts(x[1] < inf || y[1] < inf ? "TAK" : "NIE");
    }
    return 0;
}
```

---

## 作者：未来姚班zyl (赞：0)

## 题目大意
给你 $n$ 个二元组序列 $(a_i,b_i)$，接下来会进行 $m$ 次操作，每次交换一对二元组，每次交换后请你判断，是否能从每个二元组中选择一个数，按顺序构成单调不增的序列。

## 题目分析

线段树板中板。

假如是一个普通的序列，我们可以建一颗线段树，只要左区间合法，右区间合法，并且左区间的右端点小于等于右区间的左端点，则当前区间也合法。交换则是两个单点修改。

那这只是多了个元，那就记录左右端点分别取某个值时是否合法，再判两个端点的大小关系就行了。复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define L x<<1
#define R x<<1|1
#define mid (l+r>>1LL)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK l>=Ll&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned ll
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =2e5+5,M=1e6+5;
const ll llf=1e18,mod=998244353,bas=131;
const ui base=13331;
using namespace std;
int n=read(),m,a[N],b[N];
struct seg{
	bool f11,f12,f21,f22;
	int l1,l2,r1,r2;
}xd[N<<2];
inline seg getup(seg a,seg b){
	seg c;
	c={0,0,0,0,a.l1,a.l2,b.r1,b.r2};
	if(a.r1<=b.l1)c.f11|=a.f11&b.f11,c.f12|=a.f11&b.f12,c.f21|=a.f21&b.f11,c.f22|=a.f21&b.f12;
	if(a.r2<=b.l1)c.f11|=a.f12&b.f11,c.f12|=a.f12&b.f12,c.f21|=a.f22&b.f11,c.f22|=a.f22&b.f12;
	if(a.r1<=b.l2)c.f11|=a.f11&b.f21,c.f12|=a.f11&b.f22,c.f21|=a.f21&b.f21,c.f22|=a.f21&b.f22;
	if(a.r2<=b.l2)c.f11|=a.f12&b.f21,c.f12|=a.f12&b.f22,c.f21|=a.f22&b.f21,c.f22|=a.f22&b.f22;
	return c;
}
inline void build(int x,int l,int r){
	if(l==r){
		xd[x]={1,1,0,1,a[l],b[l],a[l],b[l]};
		if(a[l]==b[l])xd[x].f21=1;
		return;
	}
	build(lc),build(rc),xd[x]=getup(xd[L],xd[R]);
}
inline void modify(int x,int l,int r,int p){
	if(l==r){
		xd[x]={1,1,0,1,a[l],b[l],a[l],b[l]};
		if(a[l]==b[l])xd[x].f21=1;
		return;
	}
	if(p<=mid)modify(lc,p);
	else modify(rc,p);
	xd[x]=getup(xd[L],xd[R]);
}
int main(){
    rep(i,1,n){
		a[i]=read(),b[i]=read();
		if(a[i]>b[i])swap(a[i],b[i]);
	}
	build(Root);
	m=read();
	for(int i=1,x,y;i<=m;i++){
		x=read(),y=read();
		swap(a[x],a[y]),swap(b[x],b[y]);
		modify(Root,x),modify(Root,y);
		//cout <<xd[1].l1<<xd[1].l2<<xd[1].r1<<xd[1].r2<<'\n';
		printf("%s\n",(xd[1].f11|xd[1].f12|xd[1].f21|xd[1].f22)?"TAK":"NIE");
	}
	
	return 0;
}
```


---

## 作者：_maze (赞：0)

首先思考如何对给出的卡牌序列求解。由于序列是不降的，因此对当前卡牌 $p_i$ 的约束就是不能小于 $p_{i-1}$。考虑当 $p_{i-1}$ 越小时约束越宽松，因此我们希望在满足条件的情况下尽可能地减少 $p_{i-1}$。

于是考虑这样一个贪心：我们选择 $p_1$ 较小的一面，然后对于 $p_i$，我们判断较小的一面能否满足不降的条件，如果能则选择较小的一面，否则判断较大的一面能否满足不降的条件，如果能就选择较大的一面，否则无解。时间复杂度 $O(n)$，正确性上文有说明。

考虑优化。求解的算法已经很简洁了，于是考虑用数据结构加快修改过程。我们考虑如何把两个小区间的解拼成一个大区间的解，也就是向上传递的过程。

为了得到约束，我们维护数组 $mn_{0/1}$ 表示区间左端点为较小数或较大数时右端点最小值。存储为较大数的值是为了防止作为右区间合并时较小值不满足左区间的约束。合并区间时，我们类似暴力，判断右区间左端点较小值是否能满足约束，如果不能再判断较大值。

```cpp
void pu(int u, int r) {
  if (mn[ls(u)][0] == INF || mn[rs(u)][0] == INF) return mn[u][0] = mn[u][1] = INF, void();
  
  if (mn[ls(u)][0] <= a[r][0]) mn[u][0] = mn[rs(u)][0];
  else if (mn[rs(u)][1] != INF && mn[ls(u)][0] <= a[r][1]) mn[u][0] = mn[rs(u)][1];
  else mn[u][0] = INF;
  
  if (mn[ls(u)][1] <= a[r][0]) mn[u][1] = mn[rs(u)][0];
  else if (mn[rs(u)][1] != INF && mn[ls(u)][1] <= a[r][1]) mn[u][1] = mn[rs(u)][1];
  else mn[u][1] = INF;

}
```

代码中 $r$ 为右区间左端点。

实际上意义不明的交换操作可以视为两个单点修改，因此不用处理标记下放的问题。而且由于这种维护方式只需要一个数组而且操作简单，所以成为了本题的最优解。


```cpp
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
int read(int t = 0, bool f = 1, char c = 0) {
	while(!isdigit(c = getchar())) f = c^45;
	while(isdigit(c)) t = (t << 1) + (t << 3) + (c ^ 48), c = getchar();
	return f ? t: -t;
}
#define suc() cerr << "(*^_^*)" << endl
const int N = 2e5 + 5, INF = 2e9;
int n;
array<array<int, 2>, N> a;
array<array<int, 2>, (N << 2)> mn;
#define ls(u) (u<<1)
#define rs(u) ((u<<1)|1)
#define mid ((l+r)>>1)
void pu(int u, int r) {
  if (mn[ls(u)][0] == INF || mn[rs(u)][0] == INF) return mn[u][0] = mn[u][1] = INF, void();
  if (mn[ls(u)][0] <= a[r][0]) mn[u][0] = mn[rs(u)][0];
  else if (mn[rs(u)][1] != INF && mn[ls(u)][0] <= a[r][1]) mn[u][0] = mn[rs(u)][1];
  else mn[u][0] = INF;
  if (mn[ls(u)][1] <= a[r][0]) mn[u][1] = mn[rs(u)][0];
  else if (mn[rs(u)][1] != INF && mn[ls(u)][1] <= a[r][1]) mn[u][1] = mn[rs(u)][1];
  else mn[u][1] = INF;
}
void build(int l = 1, int r = n, int u = 1) {
  if (l == r) return mn[u] = a[l], void();
  build(l, mid, ls(u)), build(mid + 1, r, rs(u));
  pu(u, mid + 1);
}
void change(int fl, array<int, 2> p, int u = 1, int l = 1, int r = n) {
  if (l == r) return mn[u] = p, void();
  if (mid >= fl) change(fl, p, ls(u), l, mid);
  else change(fl, p, rs(u), mid + 1, r);
  pu(u, mid + 1);
}
signed main() {
  n = read();
  for (int i = 1; i <= n; ++i) a[i][0] = read(), a[i][1] = read();
  for (int i = 1; i <= n; ++i) if (a[i][0] > a[i][1]) swap(a[i][0], a[i][1]);
  build();
  int m;m = read();
  for (int i = 1; i <= m; ++i) {
    int u = read(), v = read();
    array<int, 2> p = a[u], q = a[v];
    swap(a[u], a[v]);
    change(u, q);
    change(v, p);
    if (mn[1][0] != INF) puts("TAK");
    else puts("NIE");
  }
  return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

## 思路

考虑如果不带修改怎么办。显然可以令 $dp_{i,j,0/1,0/1}$ 表示 $[i,j]$ 区间，左端点反/不反过来，右端点反/不反过来，能不能构成上升序列。

发现复杂度太高。所以可以用线段树~~简单粗暴的~~维护一下。令 $tr_{p,0/1,0/1}$ 表示线段树上编号为 $p$ 的节点，左端点反/不反过来、右端点反/不反过来的时候，能不能构成单调上升的序列。

转移就每次从中间转移，枚举 16 种情况。

静态的考虑完了，我们考虑动态的。结果发现交换操作显然对线段树来说直接变成两个修改操作即可，可以直接维护。

线段树上需要记录：

1. $tr_{p,0/1,0/1}$ 表示 $p$ 节点，左右端点分别是 $4$ 种组合的时候能不能构成单调上升。

2. $z_p$ 和 $f_p$，表示当前正面和反面上的数字。由于只有单点修改，为了方便 `push_up` 我们这里使用 $a_{i,0/1}$ 直接记录。

至此本题得解。复杂度 $O(n \log n)$，带 $2^4=16$ 的常数。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;
const int MAXN=200005;

int a[MAXN][2];

bool tr[MAXN<<2][2][2];

inline void push(int p,int l,int r){ // 上传
	memset(tr[p],0,sizeof(tr[p])); // 一定要 memset
	int mid=(l+r)>>1;
	for(int i=0;i<2;i++)
	for(int j=0;j<2;j++)
	for(int k=0;k<2;k++)
	for(int q=0;q<2;q++){
		if(a[mid][j]>a[mid+1][k]) continue; // 如果边界符合条件才进行转移
		tr[p][i][q]|=(tr[p<<1][i][j]&tr[p<<1|1][k][q]);
	}
}
void build(int p,int l,int r){ // 建树预处理 
	if(l==r){
		for(int i=0;i<2;i++) tr[p][i][i]=1;
		return;
	}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	push(p,l,r);
}
void upd(int p,int l,int r,int t){ // 修改 
	if(l==r) return;
	int mid=(l+r)>>1;
	if(t<=mid) upd(p<<1,l,mid,t);
	else upd(p<<1|1,mid+1,r,t);
	push(p,l,r);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int n; cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i][0]>>a[i][1];
	build(1,1,n);
	int q; cin>>q;
	while(q--){
		int x,y; cin>>x>>y;
		swap(a[x][0],a[y][0]);
		swap(a[x][1],a[y][1]);
		upd(1,1,n,x),upd(1,1,n,y);
		
		bool flag=0;
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				flag|=tr[1][i][j]; // 全局查询
		if(flag) puts("TAK");
		else puts("NIE");
	}
	return 0;
}

```

---

