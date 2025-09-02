# [NAPC-#1] Stage2 - Darkness

## 题目背景

> ![](https://cdn.luogu.com.cn/upload/image_hosting/y68eurqf.png)

## 题目描述

有 $n$ 支军队分布在各地，可以看作在一个平面直角坐标系内。他们都受 kid 的统一指挥，kid 共发出 $m$ 条命令。

命令有如下几种：

- `1 p q` 表示把**每支**军队的位置从 $(x_i,y_i)$ 移到 $(x_i+p,y_i+q)$。
- `2 i`，表示**第 $i$ 支军队**的位置对直线 $y=x$ 作轴对称变换（即交换 $x_i$ 与 $y_i$ 的值）。
- `3 i`，表示查询第 $i$ 支军队现在所处的位置（即输出此时的 $x_i$ 与 $y_i$）。

**请注意 `1` 与 `2` 命令的操作对象不同，前者为全体军队，后者为单支军队。**

本来 kid 可以直接拿望远镜看的，但是天太黑了，只能拜托你编写一个程序告诉他了。

## 说明/提示

### 【数据范围】
该题共有 $10$ 个测试点，每个测试点等分。

- 对于 $20\%$ 的数据，$n,m\leqslant 1000$。
- 对于另外 $30\%$ 的数据，保证没有 `2` 命令。

对于 $100\%$ 的数据，$1\leqslant n\leqslant 10^5$，$1\leqslant m\leqslant 5\times10^5$，$|a_i|,|b_i|,|p|,|q|\leqslant 10^3$，$1\leqslant i\leqslant n$，$op\in\{1,2,3\}$。

### 【样例解释】
| 时间 | $(x_1,y_1)$ | $(x_2,y_2)$ | $(x_3,y_3)$ |
|  :-:  |  :-:  |  :-:  |  :-:  |
| 初始时 | $(1,2)$ | $(2,5)$ | $(6,2)$ |
| 第 $2$ 次命令后 | $(2,6)$ | $(3,9)$ | $(7,6)$ |
| 第 $4$ 次命令后 | $(2,6)$ | $(3,9)$ | $(6,7)$ |
| 第 $6$ 次命令后 | $(-7,5)$ | $(-6,8)$ | $(-3,6)$ |

## 样例 #1

### 输入

```
3 7
1 2
2 5
6 2
3 2
1 1 4
3 3
2 3
3 1
1 -9 -1
3 3```

### 输出

```
2 5
7 6
2 6
-3 6```

# 题解

## 作者：Peaceful_Evening (赞：4)

这道题看上去挺简单，做起来细节点还挺多的。

### $20 pts$ 做法：

对于操作一，每次操作循环 $m$ 次改变所有军队的坐标。

对于操作二，直接将第 $i$ 支军队的 $(x,y)$ 坐标交换。

对于操作三，则输出第 $i$ 支军队的所在坐标。

#### 代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1000001],b[1000001];//数组要开大一点
int main() {
	int n,m;
	cin>>n>>m;
	for(int i=1; i<=n; i++) {
        cin>>a[i]>>b[i];//输入第i支军队的坐标位置
	}
	for(int i=1;i<=m;i++){
		int op;
		cin>>op;
		if(op==1){//第一种操作
			int x,y;
			cin>>x>>y;
			for(int j=1;j<=n;j++){
				a[j]=a[j]+x;
				b[j]=b[j]+y;
			}
		}
		if(op==2){//第二种操作
			int p;
			cin>>p;
			swap(a[p],b[p]);//交换军队的x,y坐标
		}
		if(op==3){//第三种操作
			int q;
			cin>>q;
			cout<<a[q]<<" "<<b[q]<<endl;
		}
	}
	return 0;
}
```
### $100 pts$ 做法：

对于操作一，设置全局变量 $k,g$，在每次操作时 $(x,y)$ 变成 $(x+k,y+g)$，每次操作时更改 $k,g$ 的值即可。

对于操作二，将第 $i$ 支军队的 $(x,y)$ 坐标交换后减去 $k,g$，再赋值给数组。

对于操作三，则输出 $(x+k,y+g)$。

#### 代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1000001],b[1000001];
int k,g;//上文所说的两个全局变量
int main() {
	int n,m;
	cin>>n>>m;
	for(int i=1; i<=n; i++) {
        cin>>a[i]>>b[i];//最开始的军队坐标
	}
	for(int i=1;i<=m;i++){
		int op;
		cin>>op;
		if(op==1){//操作一
			int x,y;
			cin>>x>>y;
			k+=x,g+=y;//更改全局变量
		}
		if(op==2){//操作二
			int p;
			cin>>p;
         int t=a[p]+k,s=b[p]+g;//更改后的军队坐标
			 swap(t,s);//交换
         a[p]=t-k,b[p]=s-g;//赋值给x,y
		}
		if(op==3){//操作三
			int q;
			cin>>q;
			cout<<a[q]+k<<" "<<b[q]+g<<endl;
		}
	}
	return 0;
}
```
这是本人第一次写题解，经验不足。如果有什么问题，欢迎在评论区里留言哦~

---

## 作者：STARSczy (赞：3)

以前一篇主题库的题解都没写过……来陶冶一下我的情操吧……

提供两种做法。
## 线段树：
第一种是线段树（直接套模板，分别使用区间修改、单点修改、单点访问解决）。特点：代码长，效率相对来说低，复制模板的话手打部分不长。总时间复杂度为 $\Theta(N+M\log N)$。

## 普通思路：
定义标记 $addx$ 和 $addy$，初始值为 $0$，具体作用马上讲。

#### 对于操作 $1$：
因为所有坐标都要加，因此直接 $addx=addx+p$，$addy=addy+q$，时间复杂度 $\Theta(1)$。

#### 对于操作 $2$：
因为初始值要加上标记才是实际值，因此我们要维护区间整体，故操作大致为先还原后交换，横坐标修改为 $y_i+addy-addx$，纵坐标修改为 $x_i+addx-addy$，时间复杂度 $\Theta(1)$。

#### 对于操作 $3$：
直接输出 $x_i+addx$ 和 $y_i+addy$，时间复杂度 $\Theta(1)$。

综上，总时间复杂度为 $\Theta(N+M)$，完全能过。特点：效率相对较高，整体码量小。

# 代码：
#### 普通做法
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int maxn=2e5+10;
int n,m,addx,addy,a[maxn],b[maxn];

signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i) scanf("%lld%lld",a+i,b+i);
	while(m--){
		int opt;
		scanf("%lld",&opt);
		switch(opt){
			case(1):{
				int p,q;
				scanf("%lld%lld",&p,&q);
				addx+=p,addy+=q;//直接加上去
				break;
			}
			case(2):{
				int k;
				scanf("%lld",&k);
				a[k]+=addx,b[k]+=addy;//还原
				swap(a[k],b[k]);//交换
				a[k]-=addx,b[k]-=addy;//维护
				break;
			}
			case(3):{
				int k;
				scanf("%lld",&k);
				printf("%lld %lld\n",a[k]+addx,b[k]+addy);//还原
				break;
			}
		}
	}
	return 0;
}
```

#### 线段树做法：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int maxn=2e5+10;
int n,m,a[maxn],b[maxn];
class tree{
	protected:
		struct node{
			int l,r;
			int data,lazy;
		}a[maxn*4];
	public:
		void init(int id,int l,int r,int *p){
			a[id].l=l,a[id].r=r;
			if(l>=r){
				a[id].data=*(p+l);
				return;
			}
			int mid=(l+r)>>1;
			init(id<<1,l,mid,p);
			init(id<<1|1,mid+1,r,p);
			a[id].data=a[id<<1].data+a[id<<1|1].data;
		}
		void down(int id){
			if(!a[id].lazy) return;
			a[id].data=a[id].data+a[id].lazy*(a[id].r-a[id].l+1);
			a[id<<1].lazy=a[id<<1].lazy+a[id].lazy;
			a[id<<1|1].lazy=a[id<<1|1].lazy+a[id].lazy;
			a[id].lazy=0;
		}
		void update(int id){
			a[id].data=
			a[id<<1].data+a[id<<1].lazy*(a[id<<1].r-a[id<<1].l+1)+
			a[id<<1|1].data+a[id<<1|1].lazy*(a[id<<1|1].r-a[id<<1|1].l+1);
		}
		void change(int id,int l,int r,int add){
			if(a[id].l==l&&a[id].r==r){
				a[id].lazy=a[id].lazy+add;
				return;
			}
			down(id);
			if(a[id<<1].r<l) change(id<<1|1,l,r,add);
			else if(a[id<<1|1].l>r) change(id<<1,l,r,add);
			else{
				change(id<<1,l,a[id<<1].r,add);
				change(id<<1|1,a[id<<1|1].l,r,add);
			}
			update(id);
		}
		int sum(int id,int l,int r){
			if(a[id].l==l&&a[id].r==r){
				return a[id].data+a[id].lazy*(a[id].r-a[id].l+1);
			}
			down(id);
			if(a[id<<1|1].l>r) return sum(id<<1,l,r);
			if(a[id<<1].r<l) return sum(id<<1|1,l,r);
			return sum(id<<1,l,a[id<<1].r)+sum(id<<1|1,a[id<<1|1].l,r);
		}
};//模板好又秒
tree t[2];

signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i) scanf("%lld%lld",a+i,b+i);
	t[0].init(1,1,n,a);
	t[1].init(1,1,n,b);
	while(m--){
		int opt;
		scanf("%lld",&opt);
		switch(opt){
			case(1):{
				int p,q;
				scanf("%lld%lld",&p,&q);
				t[0].change(1,1,n,p);
				t[1].change(1,1,n,q);
				break;
			}
			case(2):{
				int k;
				scanf("%lld",&k);
				int l=t[0].sum(1,k,k),r=t[1].sum(1,k,k);
				t[0].change(1,k,k,r-l);
				t[1].change(1,k,k,l-r);
				break;
			}
			case(3):{
				int k;
				scanf("%lld",&k);
				printf("%lld %lld\n",t[0].sum(1,k,k),t[1].sum(1,k,k));
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：添哥 (赞：2)

看到题面就直接开敲树状数组了（幸好放我过了。/fad

线段树也可以哦。

维护两个序列 $x_i$ 和 $y_i$，支持三种操作：

- `1 p q`：将 $x_i$ 都加上 $p$，将 $y_i$ 都加上 $q$。

- `2 i`：交换 $x_i$ 和 $y_i$ 的值。

- `3 i`：求 $x_i$ 和 $y_i$ 的值。

然后您会发现如果把两个序列差分一下就变成了：

- `1 p q`：将 $x_1$ 加上 $p$，将 $y_1$ 加上 $q$。

- `2 i`：将 $x_{i+1}$ 加上 $x_i-y_i$，将 $y_{i+1}$ 加上 $y_i-x_i(i<n)$，并交换 $x_i$ 和 $y_i$ 的值。

- `3 i`：求 $\displaystyle \sum_{j=1}^ix_j$ 和 $\displaystyle \sum_{j=1}^iy_j$ 的值。

单点修改+区间查询。。。用树状数组即可：

```cpp
#include<iostream>
using namespace std;
int a[100005],b[100005],treea[100005],treeb[100005];
int n,m;
inline int lowbit(int x)
{
	return x&-x;
}
void build()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j+=lowbit(j))
		{
			treea[j]+=a[i];
			treeb[j]+=b[i];
		}
	}
}
void adda(int x,int s)//单点修改，下同
{
	for(int i=x;i<=n;i+=lowbit(i))
	{
		treea[i]+=s;
	}
}
void addb(int x,int s)
{
	for(int i=x;i<=n;i+=lowbit(i))
	{
		treeb[i]+=s;
	}
}
int aska(int x)//查询1~x的前缀和，下同
{
	int sum=0;
	while(x)
	{
		sum+=treea[x];
		x-=lowbit(x);
	}
	return sum;
}
int askb(int x)
{
	int sum=0;
	while(x)
	{
		sum+=treeb[x];
		x-=lowbit(x);
	}
	return sum;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i]>>b[i];
	}
	for(int i=n;i>=1;i--)//差分
	{
		a[i]-=a[i-1];
		b[i]-=b[i-1];
	}
	build();
	while(m--)
	{
		int opt,x,y;
		cin>>opt>>x;
		if(opt==1)
		{
			cin>>y;
			adda(1,x);
			addb(1,y);
		}
		if(opt==2)
		{
			int ta=aska(x),tb=askb(x);
			adda(x,tb-ta);
			addb(x,ta-tb);
			if(x!=n)
			{
				adda(x+1,ta-tb);
				addb(x+1,tb-ta);
			}
		}
		if(opt==3)
		{
			cout<<aska(x)<<' '<<askb(x)<<endl;
		}
	}
	return 0;
}
```


---

## 作者：251Sec (赞：2)

没打比赛，比赛结束之后随便打开了一道题，然后觉得怎么这么简单是不是我想假了，然后写了一发，过了。/cf

考虑维护全局变量 $gx,gy$，表示存储坐标为 $(x_i,y_i)$ 的点坐标实际上是 $(x_i+gx,y_i+gy)$。于是操作一，直接更改这个全局变量即可。

操作二，我们可以先求出需要修改的点的实际坐标，然后对称，然后再减去 $(gx,gy)$，再存储为 $(x_i,y_i)$ 即可。

操作三，直接输出 $(x_i+gx,y_i+gy)$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m;
int x[100005], y[100005];
int gx, gy;
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d%d", x + i, y + i);
    while (m--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int p, q;
            scanf("%d%d", &p, &q);
            gx += p; gy += q;
        }
        else if (op == 2) {
            int i;
            scanf("%d", &i);
            int tx = x[i], ty = y[i];
            x[i] = ty + gy - gx; y[i] = tx + gx - gy;
        }
        else {
            int i;
            scanf("%d", &i);
            printf("%d %d\n", x[i] + gx, y[i] + gy);
        }
    }
    return 0;
}
```

---

## 作者：wangbinfeng (赞：1)

![](https://img.shields.io/badge/题目-P9430-green)
![](https://img.shields.io/badge/难度-普及—-orange)
![](https://img.shields.io/badge/考点-转换思想-blue)
![](https://img.shields.io/badge/题型-传统-yellow)
![](https://img.shields.io/badge/作者-wangbinfeng(387009)-purple)

------------
容易想到暴力思路，就不详细说明。

观察数据范围（$1\leqslant n\leqslant 10^5$，$1\leqslant m\leqslant 5\times10^5$），发现暴力的时间复杂度为 $O(nm)$，显然无法通过本题。

继续分析易得，时间复杂度过大主要由`操作1`造成。因此考虑提高`操作1`（修改所有军队）的速度。

考虑引入两个新变量 $m_x,m_y$ 记录总偏移量。每次执行`操作1`时，$m_x=m_x+p,m_y=m_y+q$，而执行`操作3`时输出 $x_i+m_x,y_i+m_y$（可以发现将操作一的时间复杂度由 $O(n)$ 降至 $O(1)$）。

`操作2`要求交换单个军队的横纵坐标，修改时应先将原坐标 $x_i,y_i$ 分别加偏移量 $m_x,m_y$ 求出现在坐标，再将现在坐标的 $x,y$ 交换。不要忘记交换完需要再减掉偏移量。

最终时间复杂度：$O(n+m)$。

------------

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long mx,my,n,m;
inline int read(){
    char c;
    int ret=0,f=1;
    for(c=getchar();c<'0'||c>'9';c=getchar())if(c=='-')f=-f;
    for(;c>='0'&&c<='9';c=getchar())ret=ret*10+c-'0';
    return ret*f;
}                                               //快读模板（本题读入数据有点多，快读可以加速）
class NODE{                                     //军队类
public:                                         //类中元素默认私有，需改变为公有（结构体不需要这句）
	int x,y;                                    //坐标
	void swap(){
		int t=x+mx-my;
		x=y+my-mx;
		y=t;
	}                                           //交换横纵坐标
	void print(){printf("%d %d\n",x+mx,y+my);}  //输出
}node[100009];
int main() {
	n=read(),m=read();
	for(int i=1;i<=n;i++)node[i].x=read(),node[i].y=read();
	while(m--)
		switch(read()){
			case 1:                             //操作一
				mx+=read(),my+=read();          //修改偏移量
				break;                          //勿忘
			case 2:                             //操作二
				node[read()].swap();            //交换横纵坐标（调用类中的函数）
				break;                          //勿忘
			case 3:                             //操作三
				node[read()].print();           //输出横纵坐标
		}
}
```

---

## 作者：y_kx_b (赞：0)

## Stage2 - Darkness

预计难度：~~\*1500~~ \*1200 左右，橙？。

upd at 2023/9/7：我之前写的都是啥答辩啊。& 修了咕到现在（）的询问为操作 `4` 的锅。

这题 idea 来自 [P2129 L 国的战斗续之多路出击](https://www.luogu.com.cn/problem/P2129)，感兴趣的同学可以去补下原题，简单版的（）。

---

首先没有 `2` 操作的话我们显然可以维护全局向量 $v=(dx, dy)$ 表示 $1$ 操作总共让所有军队在横纵坐标上位移了多少，然后询问时直接输出军队原来的位置加上当前的 $v$ 即可。
```cpp
int dx = 0, dy = 0;
while(m--) {
    int op = read(), i = read();
    if(op == 1) dx += i, dy += read();
    else if(op == 3) printf("%d %d\n", x[i] + dx, y[i] + dy);
}
```

那么如果加上 `2` 操作怎么做呢？我们可以先来一次单点查询，然后我们就知道这支军队翻到哪里去了（单点修改）。不过最后要还原回去，为了下次单点查询我们把坐标加上 $v$ 之后得到的现在的正确坐标。
```cpp
	if(op == 2) {
		x[i] += dx, y[i] += dy;
		swap(x[i], y[i]);
		x[i] -= dx, y[i] -= dy;
	}
```
总时间复杂度为 $O(n+q)$。\

当然题目简单，可能存在有多种做法，比如直接上线段树（）。

当然也可以像原 std 一样记录上次单点翻转的时间戳，然后单点查询的时候加上从时间戳到现在的 $v$ 即可，不过比较麻烦，码长被大家吊打了（

完结撒花！

---

## 作者：InversionShadow (赞：0)

## P9430 [NAPC-#1] Stage2 - Darkness 题解

维护两个全局变量 $px,py$，表示	`1` 操作后的 $\sum x$ 与 $\sum y$。

`1` 操作：直接将 $px$ 加上 $p$，$py$ 加上 $q$。

`2` 操作：


改变 $x_i$ 与 $y_i$，我们令当前的 $x_i$ 为 $p$，那么改变后的 $x_i = p + py - px$。$py - px$ 为 $\sum x - y$，改变 $x_i,y_i$，那么 $x_i = p + \sum (x - y)$，同样的，$y_i = $ 当前的 $y_i + \sum (y - x)$。

`3` 操作：输出 $x_i - px$ 与 $y_i - py$ 即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 114514;

struct Node{
  int x, y;
} a[MAXN];

int n, m, sumx, sumy, px, py; 

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].x >> a[i].y;
  }
  for (int i = 1; i <= m; i++) {
    int op;
    cin >> op;
    if (op == 1) {
      int xx, y;
      cin >> xx >> y;
      px += xx;
      py += y;
      sumx += xx;
      sumy += y;
    } else if (op == 3) {
      int xx;
      cin >> xx;
      cout << a[xx].x + sumx << ' ' << a[xx].y + sumy << endl;
    } else {
      int xx;
      cin >> xx;
      int tx = a[xx].x, ty = a[xx].y;
      a[xx].x = ty + sumy - sumx;
      a[xx].y = tx + sumx - sumy;
    }
  }
  return 0;
}
```

---

## 作者：Vct14 (赞：0)

对于第一个命令，由于是全体军队，遍历太慢，考虑用两个变量 $u,v$（可以为负数）来记录所有军队离原来的位置 $(x_i,y_i)$ 的偏移量。即第 $i$ 支军队的位置为 $(x_i+u,y_i+v)$。

对于第二个命令，军队会变到 $(y_i+v,x_i+u)$ 的位置，而为了方便输出，我们还是存储 $(y_i+v-u,x_i+u-v)$。

对于第三个命令，直接输出军队的位置为 $(x_i+u,y_i+v)$ 即可。

```c++
#include<bits/stdc++.h>
using namespace std;

int x[100002];
int y[100002];

int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1; i<=n; i++) cin>>x[i]>>y[i];
    int u=0,v=0;
    while(m--){
        int o;
        cin>>o;
        if(o==1){
            int p,q;
            cin>>p>>q;
            u+=p,v+=q;//更新偏移量
        }
        if(o==2){
            int i;
            cin>>i;
            x[i]+=u,y[i]+=v;
            swap(x[i],y[i]);//交换
            x[i]-=u,y[i]-=v;//存储
        }
        if(o==3){
            int i;
            cin>>i;
            cout<<x[i]+u<<" "<<y[i]+v<<endl;
        }
    }
    return 0;
}
```

---

## 作者：zymooll (赞：0)

### 题目大意

给定一组坐标 $(x,y)$，对于这组坐标有以下三种操作：

- 将所有坐标的 $x$ 平移 $p$，$y$ 平移 $q$.

- 将某一坐标的 $x$ 和 $y$ 交换.

- 查询某一坐标的 $x$ 和 $y$.

### 主要思路

考虑建立线段树.

对于每次整体平移操作即是在根节点打上平移量的懒标记；对于每次交换操作即是递归到根节点下传懒标记后交换 $x$ 和 $y$；对于每次查询操作，同样也是递归到根节点下传懒标记后输出 $x$ 和 $y$.

### 参考代码

```cpp
// Author:zymooll

#include<bits/stdc++.h>
#define getchar getchar_unlocked
#define putchar putchar_unlocked
using namespace std;
int read(){
	int s=0,w=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')w=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		s=s*10+c-'0';
		c=getchar();
	}
	return s*w;
}
void print(int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>=10)print(x/10);
	putchar(x%10+'0');
	return;
}
void print(pair<int,int>aa){
    print(aa.first),putchar(' '),print(aa.second),putchar('\n');
}
const int NMax=1e5;
int n,m;
struct POS{
    int x,y;
}pp[NMax+10];
struct Segment_Tree{
    struct Node{
        int x,y,l,r;
    }t[2*NMax+10];
    int ncnt=1;
    void lzdown(int p,int L,int R,int mid){
        if(!t[p].l){
            t[p].l=++ncnt;
            if(L==mid)t[t[p].l].x=pp[L].x,t[t[p].l].y=pp[L].y;
        }
        if(!t[p].r){
            t[p].r=++ncnt;
            if(mid+1==R)t[t[p].r].x=pp[R].x,t[t[p].r].y=pp[R].y;
        }
        t[t[p].l].x+=t[p].x,t[t[p].r].x+=t[p].x;
        t[t[p].l].y+=t[p].y,t[t[p].r].y+=t[p].y;
        t[p].x=t[p].y=0;
        return;
    }
    void modify(int p,int L,int R,int x){
        if(L==R){
            swap(t[p].x,t[p].y);
            return;
        }
        int mid=(L+R)/2;
        lzdown(p,L,R,mid);
        if(x<=mid)modify(t[p].l,L,mid,x);
        else modify(t[p].r,mid+1,R,x);
        return;
    }
    pair<int,int> ask(int p,int L,int R,int x){
        if(L==R)return make_pair(t[p].x,t[p].y);
        int mid=(L+R)/2;
        lzdown(p,L,R,mid);
        if(x<=mid)return ask(t[p].l,L,mid,x);
        else return ask(t[p].r,mid+1,R,x);
    }
}T;
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(),m=read();
    for(int i=1;i<=n;i++){
        pp[i].x=read(),pp[i].y=read();
    }
    while(m--){
        int opt=read();
        if(opt==1){
            T.t[1].x+=read();
            T.t[1].y+=read();
        }
        else if(opt==2){
            int pos=read();
            T.modify(1,1,n,pos);
        }
        else{
            int pos=read();
            print(T.ask(1,1,n,pos));
        }
    }
	return 0;
}

```

### 后记

参考时间复杂度 $O(n \log n)$，实测 342 ms.

这个做法比较好想，但是码量大，时间也劣，给各位做个参考吧.

---

