# [PA 2014] Parking

## 题目描述

你的老板命令你将停车场里的车移动成他想要的样子。

停车场是一个长条矩形，宽度为 $w$。我们以其左下角顶点为原点，坐标轴平行于矩形的边，建立直角坐标系。停车场很长，我们可以认为它一直向右边伸展到无穷远处。

车都是边平行于坐标轴的矩形，大小可能不同。你可以将车任意地平移（但不能旋转），只要他们不超出停车场的边界，且不能互相碰撞，但紧挨着是允许的（即任意时刻任两辆车的重叠面积为 $0$）。

你知道目前各辆车的摆放位置，以及老板心中所想的位置。你需要判断是否可以办到老板的任务。

![](https://cdn.luogu.com.cn/upload/image_hosting/xyv3nn7o.png)

## 说明/提示

对于 $100\%$ 的数据，$1\le t\le 20$，$1\le n\le 5\times 10^4$，$1\le w\le 10^9$，$0\le x_1,x_2\le 10^9$，$0\le y_1,y_2\le w$。

## 样例 #1

### 输入

```
2
3 3
0 0 2 2
2 1 4 3
4 0 6 1
0 0 2 2
2 1 4 3
0 2 2 3
3 3
0 0 2 2
2 1 4 3
4 0 6 1
2 1 4 3
0 0 2 2
4 0 6 1```

### 输出

```
TAK
NIE```

# 题解

## 作者：huanyue (赞：4)

这么前面的题目竟然没有题解,赶紧来占个位

~~这道题看上去很裸,实际上也很裸~~

把车车看成矩形

 首先使这些矩形不相交

就是一个矩形接一个矩形串起来(羊肉串)

假如两个矩形需要调换的话，那么必须保证,两个矩形的宽相加$\leq w$
如果都能满足就是合法的,否则不合法

然后就~~随便维护~~一下就行了(树状数组/线段树)

 摆放顺序的话那么最右是最后一个放的，没有任何障碍，

因此可以采用倒推,从大到小枚举位置,用树状数组维护前缀最值就可以了。 



如题解所述,代码也奇短无比



```cpp
/*
 * @Author: Huanyue 
 * @Date: 2020-02-13 10:42:52 
 * @Last Modified by: Huanyue
 * @Last Modified time: 2020-02-13 11:10:53
 */

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>
#define rgi register
typedef long long ll;
using namespace std;

const int N = 5e4 + 10;
const int inf = 0x3f3f3f3f;

inline void write(register int x)
{
    if (x < 0)
    {
        putchar('-'), x = -x;
    }
    if (x >= 10)
    {
        write(x / 10);
    }
    putchar('0' + x % 10);
}

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = ((x << 3) + (x << 1) + (ch ^ 48));
        ch = getchar();
    }
    return x * f;
}

struct mat
{
    int x1, y1, x2, y2, width, id;
    friend bool operator<(const mat &a, const mat &b)
    {
        if (a.x1 == b.x1)
            return a.x2 < b.x2;
        return a.x1 < b.x1;
    }
} initial[N], target[N];

int n, w, rk[N];
//树状数组
int tree[N];
inline int lowbit(int x)
{
    return x & (-x);
}
inline void modify(int x, int v)
{
    for (rgi int i = x; i <= n; i += lowbit(i))
        tree[i] = max(tree[i], v);//维护前缀最大值
}
inline int query(int x)
{
    int ret = 0;
    for (int i = x; i; i -= lowbit(i))
        ret = max(ret, tree[i]);
    return ret;
}

int main()
{
    int T = read();
    while (T--)
    {
        memset(tree, 0, sizeof(tree));
        memset(rk, 0, sizeof(rk)); //多组数据,接的memset
        n = read(), w = read();
        for (rgi int i = 1; i <= n; i++)
        {
            initial[i].x1 = read();
            initial[2].y1 = read();
            initial[i].x2 = read();
            initial[i].y2 = read();
            if (initial[i].x1 > initial[i].x2)
                swap(initial[i].x1, initial[i].x2);
            if (initial[i].y1 > initial[i].y2)
                swap(initial[i].y1, initial[i].y2);

            initial[i].id = i;
            initial[i].width = initial[i].y2 - initial[i].y1; //计算宽度
        }
        for (rgi int i = 1; i <= n; i++)
        {
            target[i].x1 = read(), target[i].y1 = read(), target[i].x2 = read(), target[i].y2 = read();
            if (target[i].x1 > target[i].x2)
                swap(target[i].x1, target[i].x2);
            if (target[i].y1 > target[i].y2)
                swap(target[i].y1, target[i].y2);
            target[i].id = i;
            target[i].width = target[i].y2 - target[i].y1;
        }

        sort(initial + 1, initial + n + 1);
        sort(target + 1, target + n + 1);

        for (int i = 1; i <= n; i++)
            rk[initial[i].id] = i;
        
        bool flag = true;//答案标记

        for (rgi int i = n; i; i--)
        {
            if (query(rk[target[i].id]) + target[i].width > w)
                flag = false;
            if (!flag)
                break;
            modify(rk[target[i].id], target[i].width);
        }
        if (flag)
            puts("TAK");
        else
            puts("NIE");
    }
    return 0;
}
```



---

## 作者：FishZe (赞：2)

这一题似乎题解比较少，蒟蒻我说两句。

由于第一次投题解不了解规范，没有按照要求，目前已修改。

------------
### 核心信息：

停车场是一个长条矩形，宽度为 $ w $ 。我们以其左下角顶点为原点，坐标轴平行于矩形的边，建立直角坐标系。停车场很长，我们可以认为它一直向右边伸展到无穷远处。

车都是边平行于坐标轴的矩形，大小可能不同。你可以将车**任意地平移**（但不能旋转），只要他们不超出停车场的边界，且不能互相碰撞，但紧挨着是允许的（即任意时刻任两辆车的重叠面积为   $ 0 $ ） 。


------------
### get 到的信息：


#### 0 、初始位置和目标位置都是合法情况，也就是没有重叠


#### 1 、我们需要做的是平移到目标位置，过程中不能有重叠

想一下，一条窄窄的巷子里面已经塞了一个大胖子（无意冒犯），只留下了一条空隙，如果有人想经过他，就一定要比这个空隙瘦才行。

这一题也是一样的，对于某一辆车而言，从他的起始位置到目标位置的路径上，不能有**比他留下的空隙还要胖的车车**，即  $w_{i} + w_{j} ≤ W$  。

 ~~车车，好快的车车~~

两辆车要擦肩而过，无非就是意味着**两车的路径有交集**

同学们可以自己在纸上画一下探讨一下什么情况才会相交

我们先来看辆张图片：

![](https://web-files-1257015149.file.myqcloud.com/img/pic/luogu/p1728-1.png)

在上图中，绿目标位置比黄大，绿初始位置比黄小，会相交

在下图中，绿目标位置比黄大，初始位置比黄大。

同学们可以自己画一下，可以总结出来，**目标位置大的，初始位置小，就会相交**。



 **所以我们只需要维护目标位置比他大的车中，初始位置比他小的车的宽度最大值。**

更具体的，我们按照初始位置由**小到大升序编号**，按照目标位置由**大到小遍历**，设当前车为 $ i $，如果有一辆车 $ j $，编号比他小且 $ w_{i} + w_{j} ≥ W $ ，则不合法。

获得比他编号小的所有数字中的最大值，**树状数组**是最好的方案。





------------
### 代码实现：
首先是结构体，储存每一个车的起始位置和目标位置，因为要输入两次，所以把输入写到结构体中是一个好办法，另外我们还需要重载操作符：

```cpp
struct node{
    int id, w, x[2], y[2];
    bool operator < (const node other) const {
        if(x[0] == other.x[0]){
            return x[1] < other.x[1];
        }
        return x[0] < other.x[0];
    };
    void read(){
        cin >> x[0] >> y[0] >> x[1] >> y[1];
        if(x[0] > x[1]){
            swap(x[1], x[0]);
        }
        w = abs(y[1] - y[0]);
    }
    //id为这辆车是第几辆，方便把初始位置和目标位置联系起来
};
```
用 $ s $ 和 $ t $ 来表示初始位置和目标位置，输入并排序，没什么好说的。

用数组 $ r $ 来记录每一个车的编号。

然后进行倒序对目标车辆遍历，如果树状数组中编号比他小的车中最大值和这辆车的宽度之和大于 $ w $ ，即 $ w_{max} + w_{i} ≥ w $ 则不合法.

```cpp
	sort(s + 1, s + n + 1);
        sort(t + 1, t + n + 1);
        for(int i = 1; i <= n; i++){
            r[s[i].id] = i;
        }
        for(int i = n; i >= 1; i--){
            if(get(r[t[i].id]) + t[i].w > w){
                cout << "NIE" << endl;
                goto over;
            }
            update(r[t[i].id], t[i].w);
        }
        cout << "TAK" << endl;
        over:;
```

至此，解决。

### 全部代码：

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;


const int MAXN = 5e4 + 5;

struct node{
    int id, w, x[2], y[2];
    bool operator < (const node other) const {
        if(x[0] == other.x[0]){
            return x[1] < other.x[1];
        }
        return x[0] < other.x[0];
    };
    void read(){
        cin >> x[0] >> y[0] >> x[1] >> y[1];
        if(x[0] > x[1]){
            swap(x[1], x[0]);
        }
        w = abs(y[1] - y[0]);
    }
};

int n, w;
int c[MAXN], r[MAXN];
node s[MAXN], t[MAXN];

int lowbit(int x){
    return x & (-x);
}

int get(int x){
    int res = 0;
    for(; x; x -= lowbit(x)){
        res = max(res, c[x]);
    }
    return res;
}

void update(int x, int v){
    for(; x <= n; x += lowbit(x)) {
        c[x] = max(c[x], v);
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while(T--){
        memset(c, 0, sizeof(c));
        cin >> n >> w;
        for(int i = 1; i <= n; i++){
            s[i].id = i;
            s[i].read();
        }
        for(int i = 1; i <= n; i++){
            t[i].id = i;
            t[i].read();
        }
        sort(s + 1, s + n + 1);
        sort(t + 1, t + n + 1);
        for(int i = 1; i <= n; i++){
            r[s[i].id] = i;
        }
        for(int i = n; i >= 1; i--){
            if(get(r[t[i].id]) + t[i].w > w){
                cout << "NIE" << endl;
                goto over;
            }
            update(r[t[i].id], t[i].w);
        }
        cout << "TAK" << endl;
        over:;
    }
    
    return 0;
}
```









---

## 作者：Needna (赞：1)

非常有意思的一道题！

题目分析：发现车子之间会相互移动，高度有限但宽度无限。类似一条线。接着对于一个车思考，它会穿过一些车，到达另一侧，而且只有需要穿过的车可能不满足要求，思路较为清楚了。现在思考一个车具体需要穿过（或被穿过）的车，就是开始在他前面，但结尾在他后面的车。

思路有了，所以先读入，然后排序，然后处理，发现与要处理单点修改和区间查询最大值，用树状数组即可。

判断逻辑：

```cpp
for(int i=n;i>=1;i--){
	if(sc(a[e[i].id])+abs(e[i].Y-e[i].y)>w){
		cout<<"NIE\n";f=0;break;
	}
	upd(a[e[i].id],abs(e[i].Y-e[i].y));
}if(f) cout<<"TAK\n";
```
AC code:
```cpp
#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
using namespace std;
const int N=5e4+10;
int T,n,w,a[N],tr[N];
struct Car{
	int id,x,y,X,Y;
}s[N],e[N];
int sc(int x){int ans=0;while(x>0){ans=max(tr[x],ans);x-=lowbit(x);}return ans;}
void upd(int x,int k){while(x<=n){tr[x]=max(tr[x],k);x+=lowbit(x);}}
bool c(Car a,Car b){return a.x<b.x;}
void init(Car s[]){
	for(int i=1;i<=n;++i){
		int x,y,X,Y;
		cin>>x>>y>>X>>Y;
		if(x>X)swap(x,X),swap(y,Y);
		s[i]={i,x,y,X,Y};
	}
}
int main(){
	std::ios::sync_with_stdio(false);
	cin>>T;
	while(T--){
		memset(tr,0,sizeof(tr));
		cin>>n>>w;int f=1;
		init(s);init(e);
		sort(s+1,s+1+n,c);sort(e+1,e+1+n,c);
		for(int i=1;i<=n;++i)a[s[i].id]=i;
		for(int i=n;i>=1;i--){
			if(sc(a[e[i].id])+abs(e[i].Y-e[i].y)>w){
				cout<<"NIE\n";f=0;break;
			}
			upd(a[e[i].id],abs(e[i].Y-e[i].y));
		}if(f) cout<<"TAK\n";
	}
	
	return 0;
} 
```

---

## 作者：ZHONGZIJIE0608 (赞：0)

**题意简述**

有一个长条状矩形空间，宽度为 $w$。以其左下角的顶点为原点，边平行于坐标轴。这个空间向右无限延伸。

在这个矩形内有 $N$ 个滑块。每个滑块为一个矩形，大小可能不同。你可以将滑块任意平移（但是不能旋转），但是要保证任意时刻滑块不超出停车场边界而且不互相碰撞（简单地说就是任意两个滑块的重叠面积为 $0$）。

现在给定 $N$ 个矩形的起始位置和目标位置。问你是否存在一种方案使得这 $N$ 个矩形可以到达目标位置。存在输出 ```TAK```，不存在输出 ```NIE```。

矩形位置的给定方法是给定矩形对角线两端的顶点。

**算法分析**

显然，有一些矩形的位置可能发生了交换。

如果矩形 $A$ 的初始位置和目标位置在 矩形 $B$ 两侧则矩形 $A$ 和矩形 $B$ 发生位置交换。易得只有发生了交换的矩形才可能相交。设 $W_A$ 为矩形 $A$ 的宽度，$W_B$ 为矩形 $B$ 的宽度。那么对于两个有位置交换的矩形，他们的宽度之和应该小于等于 $W$，即 $W_A+W_B \le W$。

先对于初始位置和目标位置中的每个矩形位置从左到右排序。

记录初始的每个矩形在排序后的初始位置中的编号。

考虑到最右边的矩形是没有限制的（因为是最后一个放置的），我们倒序枚举每个矩形。发现对于一个矩形，它右边的编号比它小的所有矩形都会与之交换（要从左边去右边）。所以倒着枚举时判断前缀最大值与当前矩形的宽度和是否小于等于 $W$ 就好。如果大于就直接输出 ```NIE```。

前缀最大值很好维护。这里使用了线段树。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
using namespace std;
const int N=50050;
int n,w,a[N],t[N<<2];
struct Car{
	int id,x,y,X,Y;//x 在左 X 在右 
	bool operator <(const Car &a)const{return x==a.x?X<a.X:x<a.x;}
}s[N],e[N];
void pushup(int x){t[x]=max(t[ls(x)],t[rs(x)]);}
void build(int x,int L=1,int R=n){
	t[x]=0;if(L==R)return;
	int mid=(L+R)>>1;build(ls(x),L,mid);build(rs(x),mid+1,R);pushup(x); 
}
void upd(int x,int pos,int val,int L=1,int R=n){
	if(L==R&&L==pos){t[x]=val;return;}
	int mid=(L+R)>>1;
	if(pos<=mid)upd(ls(x),pos,val,L,mid);
	else upd(rs(x),pos,val,mid+1,R);
	pushup(x);
}
int qry(int x,int l,int r,int L=1,int R=n){
	if(l<=L&&R<=r)return t[x];
	int mid=(L+R)>>1,res=-1e17;
	if(l<=mid)res=max(res,qry(ls(x),l,r,L,mid));
	if(mid<r)res=max(res,qry(rs(x),l,r,mid+1,R));
	return res;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	int T;cin>>T;while(T--){
		cin>>n>>w;
		for(int i=1;i<=n;++i){
			int x,y,X,Y;
			cin>>x>>y>>X>>Y;
			if(x>X)swap(x,X),swap(y,Y);
			s[i]={i,x,y,X,Y};
		}
		for(int i=1;i<=n;++i){
			int x,y,X,Y;
			cin>>x>>y>>X>>Y;
			if(x>X)swap(x,X),swap(y,Y);
			e[i]={i,x,y,X,Y};
		}
		sort(s+1,s+1+n);sort(e+1,e+1+n);
		for(int i=1;i<=n;++i)a[s[i].id]=i;
		bool f=1;build(1);
		for(int i=n;i;--i){
			if(qry(1,1,a[e[i].id])+abs(e[i].Y-e[i].y)>w){
				cout<<"NIE\n";f=0;break;
			}
			upd(1,a[e[i].id],abs(e[i].Y-e[i].y));
		}
		if(f)cout<<"TAK\n";
	}
	return 0; 
}
```

---

## 作者：CoderXL (赞：0)

### 蒟蒻第一次投题解，好紧张。。。。

------------

读完题，我们可以发现，在一些情况下，两辆车不能互相经过。即两辆车的宽度 $w_i+w_j > w$ 的时候。

那么我们只需要检查一下初始状态和结束状态中，哪几辆车经过了对方，然后判断他们的宽度之和是否超出了界限。

更多地，我们说两辆车**经过**了对方，就是说一辆车的「起始位置」在另外一辆左边，「结束位置」在另外一辆右边。即从移动前 $l_a\le l_b$ 变为移动后 $l_a'\ge l_b'$。（这里要求题目数据一定合法，数据中不存在矩形重叠的情况）

那么我们可以把车按起始位置从小到大排序，依次加入进来，然后维护一个下标是「结束位置」的数组 $s$，里面记录每辆车的宽度。对于每个新加入的车，检查数组 $s$ 中「结束位置」比他大的车，依次比较这些车的宽度，判断是否超界即可。

注意到我们实际上只需要和宽度最大的车比一下，省去了不少比较。

那么这里相当于查找后缀最大值，可以倒过来用树状数组维护前缀最大值。

最后别忘了，由于结束位置的值域达到 $10^9$，需要离散化一下。

------------

上 AC 代码：（读入优化+吸氧才能过）
```cpp
//
//  main.cpp
//  P1728
//
//  Created by Leo Xia on 2023/10/9.
//

#include <bits/stdc++.h>
#define iabs(x) ((x)>0?(x):-(x))
#define lb(x) ((x)&-(x))
#define N 50010
using namespace std;
int T,n,w;
struct Car
{
    int l1,r1,l2,r2,w,nl1,nr1,nl2,nr2;
}car[N];
int tmp[N<<2],cnt;
int s1[N<<2],s2[N<<2];
void add(int i,int x,int mx[])
{
    i=cnt-i+1;
    while(i<=cnt)
    {
        mx[i]=max(mx[i],x);
        i+=lb(i);
    }
}
int q(int i,int mx[])
{
    i=cnt-i+1;
    int ret=0;
    while(i>=1)
    {
        ret=max(ret,mx[i]);
        i-=lb(i);
    }
    return ret;
}
bool cmp(Car x,Car y)
{
    return x.l1<y.l1;
}
void init()
{
    cnt=0;
}
int main()
{
    ios::sync_with_stdio(0);
    cin>>T;
    int x1,x2,y1,y2;
    bool brk=false;
    while(T--)
    {
        cin>>n>>w;
        init();
        brk=false;
        for(int i=1;i<=n;i++)
        {
            cin>>x1>>y1>>x2>>y2;
            car[i]=(Car){min(x1,x2),max(x1,x2),0,0,iabs(y2-y1),0,0,0,0};
            tmp[++cnt]=car[i].l1;
            tmp[++cnt]=car[i].r1;
            s1[cnt]=s1[cnt-1]=s2[cnt]=s2[cnt-1]=0;//有时不用 memset 会更快
        }
        for(int i=1;i<=n;i++)
        {
            cin>>x1>>y1>>x2>>y2;
            car[i].l2=min(x1,x2);
            car[i].r2=max(x1,x2);
            tmp[++cnt]=car[i].l2;
            tmp[++cnt]=car[i].r2;
            s1[cnt]=s1[cnt-1]=s2[cnt]=s2[cnt-1]=0;
            if(iabs(y2-y1)!=car[i].w)
            {
                cout<<"NIE\n";
                brk=true;
                break;
            }
        }
        if(brk)continue;
        sort(tmp+1,tmp+cnt+1);
        cnt=unique(tmp+1,tmp+cnt+1)-tmp-1;
        for(int i=1;i<=n;i++)
        {
            car[i].nl1=lower_bound(tmp+1,tmp+cnt+1,car[i].l1)-tmp;
            car[i].nl2=lower_bound(tmp+1,tmp+cnt+1,car[i].l2)-tmp;
            car[i].nr1=lower_bound(tmp+1,tmp+cnt+1,car[i].r1)-tmp;
            car[i].nr2=lower_bound(tmp+1,tmp+cnt+1,car[i].r2)-tmp;
        }
        sort(car+1,car+n+1,cmp);
        for(int i=1;i<=n;i++)
        {
            if(car[i].w+q(car[i].nl1+1,s1)>w||car[i].w+q(car[i].nl2+1,s2)>w)
            {
                cout<<"NIE\n";
                brk=true;
                break;
            }
            add(car[i].nr1,car[i].w,s1);
            add(car[i].nr2,car[i].w,s2);
        }
        if(brk)continue;
        cout<<"TAK\n";
    }
    return 0;
}

```

最后才发现自己的离散化写多余了，不过不想改了，想要代码更简洁请移步其他大佬的题解。

---

