# [USACO13JAN] 刷墙 Painting the Fence S

## 题目描述

Farmer John 已经设计了一种方法来装饰谷仓旁边的长栅栏（把栅栏认为是一根一维的线）。他把一只画刷绑在他最喜爱的奶牛 Bessie 身上，之后就去喝一杯冰水，而 Bessie 隔着栅栏来回走，当她走过某个地方，这里的一段栅栏就被刷上了涂料。

Bessie 从栅栏上的位置 $0$ 开始，并且遵循着一个 $N$ 次移动的次序（$1\le N\le10^5$）。例如 `10 L` 表示 Bessie 向左移动了 $10$ 个单位长度，`15 R` 表示 Bessie 向右移动了 $15$ 个单位长度。现给出 Bessie 所有移动的列表，Farmer John 想要知道哪些区域的栅栏至少涂了两层涂料（只涂一层涂料的区域可能在大雨中被洗掉）。Bessie 在她的行走中最远到达距起始点 $10^9$ 个单位长度。

## 说明/提示

【样例解释】

Bessie 从位置 $0$ 开始，向右移动 $2$ 个单位长度，向左移动 $6$ 个单位长度，向右移动 $1$ 个单位长度，向左移动 $8$ 个单位长度，最后向右移动 $3$ 个单位长度。

$6$ 个单位区域至少被涂了两层涂料，是 $[-11,-8],[-4,-3],[0,2]$ 这些区域。

## 样例 #1

### 输入

```
6
2 R
6 L
1 R
8 L
1 R
2 R```

### 输出

```
6```

# 题解

## 作者：kradcigam (赞：24)

## 前言

[$ZHK$私人博客体验更佳](http://www.zhaohaikun.cn/2020/02/10/ti-jie-p2070-shua-qiang/)

这道题目，$n<=10^5$，显然在暗示我们使用$n \log n$的做法，我就是用了一个简单的贪心，通过了此题。

## 正文

在这道题中，我们发现，可以把 $Bessie$ 每次走的路看成是对序列的一段区间染色。

```cpp
for(int i=1;i<=n;i++){
	int x;char y;
	read(x);cin>>y;
	a[i].l=position;
	if(y=='L')position-=x;//Bessie往左走
	else position+=x;//Bessie往右走
	a[i].r=position;
	if(a[i].l>a[i].r)swap(a[i].l,a[i].r);
}
```
这里的 $a$数组是一个结构体——$node$
```cpp
const int MAXN=1e5+10;
struct node{
	int l,r;//每次染色的左端点和右端点
	bool operator<(const node&b)const{
		return l<b.l;//按左端点从小到大排序
	}
}a[MAXN];
```
之后，我们就要说真正的思路了，我们对于 $a$ 序列排序后，会有这样一个画面。

![](https://i.loli.net/2020/02/10/yELKiHaF1QPTD3m.png)

我们定义两个变量——$lft$和$rgt$，记录可能区间的左端点和右端点。

这里面我们记录的是**有可能和下面相交的区间**，什么意思？比如那张图，我们标一下号

![](https://i.loli.net/2020/02/10/ZBfRq9P2JwOVjIy.png)

当我么扫描第 $1$ 个区间时，我们发现，之后有可能被覆盖到的区间是 $lft=0,rgt=15$。

当我们继续扫描，到第 $2$ 个区间时，我们发现，之后可能被覆盖到的区间是 $lft=15,rgt=18$。

可能有人会问，$5$~$15$ 这段消失，我们还能理解，但是为什么 $0$~$5$ 这段也没了呢，因为第 $2$ 个区间的$l$都大约 $0$ 了，之后的区间肯定就更大于 $0$ 了，我们是按 $l$ 从小到大排序的啊。

所以，我可以放一下代码了：
```cpp
for(int i=2;i<=n;i++)
	if(a[i].r>lft){//如果跟可能被覆盖到的区间有交
		a[i].l=max(a[i].l,lft);//这里是使得之后的代码可以少写一点，因为显然，a[i].l<lft，a[i].l~lft这1段也没有用了
		if(a[i].r>rgt){//比之前的右端点大
			ans+=rgt-a[i].l;//从rgt到a[i].l
			lft=rgt;//之前的右端点显然就是左端点，显然，新的可能被覆盖到的区间就是之前的rgt~a[i].r
			rgt=a[i].r;//更新右端点
		}else{//比之前的右端点小
			ans+=a[i].r-a[i].l;//从a[i].r到a[i].l
			lft=a[i].r;//更新左端点
		}
	}
```
## 总结

我们先来看一下完整的代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(T &FF){
    T RR=1;FF=0;char CH=getchar();
    for(;!isdigit(CH);CH=getchar())if(CH=='-')RR=-1;
    for(;isdigit(CH);CH=getchar())FF=(FF<<1)+(FF<<3)+(CH^48);
    FF*=RR;
}//快读
template<typename T>void write(T x){
    if(x<0)putchar('-'),x*=-1;
    if(x>9)write(x/10);
    putchar(x%10+48);
}//快写
const int MAXN=1e5+10;
struct node{
	int l,r;//每次染色的左端点和右端点
	bool operator<(const node&b)const{
		return l<b.l;//按左端点从小到大排序
	}
}a[MAXN];
int position,ans,lft,rgt,n;
int main(){
	read(n);
	for(int i=1;i<=n;i++){
		int x;char y;
		read(x);cin>>y;
		a[i].l=position;
		if(y=='L')position-=x;//Bessie往左走
		else position+=x;//Bessie往右走
		a[i].r=position;
		if(a[i].l>a[i].r)swap(a[i].l,a[i].r);
	}sort(a+1,a+n+1);//排序
	lft=a[1].l;rgt=a[1].r;//给lft和rgt赋上初值
	for(int i=2;i<=n;i++)
		if(a[i].r>lft){//如果跟可能被覆盖到的区间有交
			a[i].l=max(a[i].l,lft);//这里是使得之后的代码可以少写一点，因为显然，a[i].l<lft，a[i].l~lft这1段也没有用了
			if(a[i].r>rgt){//比之前的右端点大
				ans+=rgt-a[i].l;//从rgt到a[i].l
				lft=rgt;//之前的右端点显然就是左端点，显然，新的可能被覆盖到的区间就是之前的rgt~a[i].r
				rgt=a[i].r;//更新右端点
			}else{//比之前的右端点小
				ans+=a[i].r-a[i].l;//从a[i].r到a[i].l
				lft=a[i].r;//更新左端点
			}
		}
	write(ans);//输出
	return 0;
}
```
补充一下正确性证明：

实际上作者想到这个方法的时候觉得显然是对的

其实主要就是为什么要 $lft=a[i].r$ 可能有人对此有点问题，我来解释一下
> $\therefore$ 我们是按从小到大对 $a$ 数组进行排序，也就是 $a[i+1].l \geq a[i].l$，而 $a[i].l>lft$

> $\because$ $a[i+1].l>lft$。

---

## 作者：wkdwswxy (赞：12)

关于这道题，第一眼看到应该想到的是暴力吧，暴力很简单，读入后一个个打标记，最后统计一下从哪里到哪里经过的次数大于2次，再输出就好了。

但是，当我们再细细看题的时候： **Bessie在她的行走中最远到达距起始点1,000,000,000个单位长度。**

我的天！！！这个天才Bessie走这么远，我们要是乖乖开数组的话空间会不够的！！！这时我们又可以从什么方向入手呢？

我们回到我们一开始进行模拟的步骤，如果我们进行以下的移动的话会很简单： 3 R   2 L    3 R

| 0 | 1 | 2 | 3 | 4 |  
| -----------: | -----------: | -----------: | -----------: | -----------: |
| 1 | 2 | 2 | 2 | 1 |

（第一行是位置，第二行是经过次数）

但如果变成这样会很麻烦： 1000000 R 500000 L 1000000 R

。。。这个要是要写表格的话会死人的吧；但是这简单来写的话是不是这样呢？
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 1 | 1 | 3 | 3 | 3 | 3 | 1 | 1 | 0 | 0 |

要是再简单点呢?
| 0 | 1 | 2 | 3 |
| -----------: | -----------: | -----------: | -----------: |
| 1 | 3 | 3 | 1 |

这时，一个熟悉的操作浮现在我们脑海中！！！

**离散化**！！！

如果我们用离散化，不正好符合刚刚我们~~偷懒~~的过程吗？这里1就代表了500000,2代表了1000000，3代表了1500000！！！~~妈妈再也不用担心我的空间不够了！！！~~

这时，我们就高高兴兴地写代码去啦，但是，写着写着，发现有什么不太对，我们这样做标记，岂不是要一个一个点的去判断？我的天，这太麻烦了，我们写代码的，不是要代码越简单越好吗？~~（其实就懒）~~ 我们又想了想这个步骤，欸等等，这不正是我们学习差分的时候，老师说过的区间遍历这种类型吗！！！哈哈，没错就决定是你了！**差分**！

所以这道题我们用了两种技巧，一个是离散化，一个是差分，都是很实用的技巧呢！

最关键的一步来了！上代码！
```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;

int n,a[2000010],b[2000010],c[2000010],now=0,ans=0,ok=0;
char A;

void deal(int last,int next){
	int v1 = lower_bound(b,b+1+n,last) - b;
	int v2 = lower_bound(b,b+1+n,next) - b;
	c[min(v1,v2)]++;c[max(v1,v2)]--;//差分的步骤 
}

int main(){
	cin>>n;
	a[0]=b[0]=c[0]=0;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>A;
		if(A == 'L') a[i]*= -1;
		b[i]=b[i-1]+a[i];
	}
	sort(b,b+1+n);
	int m=unique(b,b+1+n) - b;//b数组就是用来离散化的   unique是去重函数 
	for(int i=1;i<=n;i++){
		deal(now,now+a[i]);
		now+=a[i];
	}
	ok=c[0];
	for(int i=1;i<m;i++){
		if(ok > 1) ans+=b[i]-b[i-1];
		ok+=c[i]; //差分后前缀和，标准步骤了吧 
	}
	cout<<ans<<endl;
	return 0;
}
```
本蒟蒻没写过几次代码，希望大家喜欢 orzorzorz

---

## 作者：licone (赞：9)

前缀和~

记录下每次行走的位置，以及在这个位置上的加减。例如，牛走过了[3,5]这个区域，就记录下a[cnt].x=3,a[cnt].num=1;a[cnt+1].x=5,a[cnt+1].num=-1，然后按x值排序，从最左面循环到最右面，大于等于2的时候就加上面积，最后输出就可以了~






```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,x,ans,now;
char s[10];
struct node{
    int x,num;
}a[200001];
bool cmp(node u,node v)
{
    return u.x<v.x;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%s",&x,s);
        if(s[0]=='L')
        {
            a[i*2-1].x=now-x;a[i*2-1].num=1;
            a[i*2].x=now;a[i*2].num=-1;
            now-=x;
        }
        else
        {
            a[i*2-1].x=now;a[i*2-1].num=1;
            a[i*2].x=now+x;a[i*2].num=-1;
            now+=x;
        }
    }
    sort(a+1,a+2*n+1,cmp);
    now=a[1].num;
    for(int i=2;i<=2*n;i++)
    {
        if(now>1) ans+=a[i].x-a[i-1].x;
        now+=a[i].num;
    } 
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：夏色祭 (赞：7)

##转C艹后的第一篇题解

##为什么栏杆会有这么长（雾

因为栏杆太长，所以我们按校门外的树[戳这里](https://www.luogu.org/problemnew/show/1047)那样做显然不但会TLE还会MLE。。。

我们可以把每次刷墙看成是一个区间。。。

被刷两次及以上的墙那其实就是重合的区间总长。。。

那么其实这个问题就转化成了类似于区间合并[戳这里](https://www.luogu.org/problemnew/show/2082)的题目。。。

我们用两个变量last和x分别记录重合的区间最后的位置和合并到当前区间之前合并最右端的端点。

那么如果当前区间和之前区间有交集，则去判断当前区间是否有之前没统计过的重合的区间。

丑陋的代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct edge {
    int l,r;
}a[100001];
int n,x;
char c;
bool operator < (const edge &a,const edge &b)
{
    return a.l < b.l;
}
int main() {
    scanf("%d",&n);
    int y=0;
    for (int i=1;i<=n;i++) {
        scanf("%d %c",&x,&c);
        if (c=='L') {a[i].r=y,a[i].l=y-x;y-=x;}
          else {a[i].l=y,a[i].r=y+x;y+=x;}
```
}//读入
```cpp
    sort(a+1,a+1+n);//按区间的左端点排序
    int last=-2000000000,ans=0;
    x=a[1].r;
    for (int i=2;i<=n;i++) 
      if (x>=a[i].l) {
          if (min(a[i].r,x)-max(last,a[i].l)>0) {
              ans+=min(a[i].r,x)-max(last,a[i].l);
             // cout << min(a[i].r,x) << " " << max(last,a[i].l) << endl;
              last=min(a[i].r,x);
        }
        x=max(x,a[i].r);
      }
      else x=max(x,a[i].r);//last和x同上面
    cout << ans;
    return 0;
}

```

---

## 作者：Loser_King (赞：3)

USACO 的离散化入门题。

## 题意

> 有一个点在数轴上多次向左或向右移动若干单位距离，求被它经过两次及以上的区间长度。

## 做法

可以把每一次移动抽象地看成是一条线段，答案就是求被线段覆盖大于等于两次的区间长度。

比如样例就可以抽象成这样：（数字表示位置的个位数，0旁边的符号表示正负）

```
1 0 9 8 7 6 5 4 3 2 1-0+1 2 操作次数
                      |==>| 1
              |<==========| 2
              |>|           3
|<==============|           4
|>|                         5
  |==>|                     6
 2 2 2 1 1 1 1 3 1 1 1 2 2 厚度
```

进一步的，我们可以把一条线段拆分成两个事件，称为左端点事件和右端点事件（这里借用lrj的说法）。

我们可以观察到，在经历左端点事件时，当前涂料厚度加一；

同样的，在经历右端点事件时，当前涂料厚度减一。

所以我们只要先标记这些事件，将这 $2n$ 个事件排序，然后从左向右处理即可。

细节见代码。

## 代码

```c++
// P2070 AC Code
// written by Loster_King (159686)
// 88 ms / 2.75 MB / 535B C++ O2
#include<bits/stdc++.h>
using namespace std;
int n,cur,ans;
pair<int,int>evt[233333];
//事件，注意要开两倍数组
//pair的first表示事件的位置，second表示事件所带来的的厚度差
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		int x;char op;
		scanf("%d %c",&x,&op);
		if(op=='L'){
			evt[i<<1]=make_pair(cur-x,1); //左端点事件，厚度加一，下同
			evt[i<<1|1]=make_pair(cur,-1);//右端点事件，厚度减一，下同
			cur-=x;
		}else{
			evt[i<<1]=make_pair(cur,1);
			evt[i<<1|1]=make_pair(cur+x,-1);
			cur+=x;
		}
	}
	sort(evt,evt+n*2);cur=0;
	for(int i=0;i<n*2;i++){
		if(cur>1)ans+=evt[i].first-evt[i-1].first;
		cur+=evt[i].second;
        //注意这里两个操作的顺序不能反
        //因为判断操作是判该事件前面的区间的
        //如果先修改cur就会覆盖掉
	}
	printf("%d\n",ans);
}
```



---

## 作者：OldVagrant (赞：2)

## 题意
[题意传送门](https://www.luogu.com.cn/problem/P2070)
## Solution
显而易见暴力根本过不去（移动的范围最多能到 $10^9$），这个移动范围提醒我们要离散化（~~其实标签也有离散化~~），同时稍加思考我们可以想到用差分来维护每个段被覆盖的次数。   
对于每次移动，计算出移动后 Bessie 的位置，将这些位置排序并离散化后，把所有相邻的两个位置看做一个区间，区间的左端点和右端点就是这两个位置。   
然后建一个差分数组 $c$，每次区间修改就在 $c$ 里相应地修改。最后遍历一遍 $c$，设一个变量 $sum$ 记录下差分数组的前缀和，$sum$ 累加到差分数组的第 $i$ 个位置时，对应的就是第 $i$ 个区间被覆盖的次数。然后在累加过程中判断,如果 $sum\geq 2$ 就更新答案。
## Code     

```c
#include <bits/stdc++.h>
using namespace std;
int n,a[100001],now,tmp,b[100001],ans,x,y,cnt,cf[100001],sum,k; 
char ch;
const int LEN=32768;
char BUF[LEN],*Pin,*Pin_last,PUF[LEN],*Pout=PUF,*Pout_last=PUF+LEN-1;
char gc(){
	return Pin==Pin_last&&(Pin_last=(Pin=BUF)+fread(BUF,1,LEN,stdin),Pin==Pin_last)?EOF:*Pin++;
}
int read(){
	int x=0;
	char c=gc();
	while(c>57||c<48) c=gc();
	while(c>47&&c<58) x=x*10+c-48,c=gc();
	return x;
}//上面的是快读，可以不管
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		tmp=read(),ch=gc();
		while(ch!='L'&&ch!='R') ch=gc();
		ch=='L'?now-=tmp:now+=tmp,a[i]=b[i]=now;//直接记录每次移动后的位置
	}sort(b,b+n+1);//注意这里一定要把b[0]放进去，因为牛最开始是在位置0。
	for(int i=0;i<=n;i++) a[i]=lower_bound(b,b+n+1,a[i])-b;//离散化
	for(int i=0;i<n;i++) a[i]>a[i+1]?(++cf[a[i+1]],--cf[a[i]]):(++cf[a[i]],--cf[a[i+1]]);//在差分数组上修改
	for(int i=0;i<n;i++){
		sum+=cf[i];//这里的sum就是离散化后的这个点被覆盖了几次。
		if(sum>1) ans+=b[i+1]-b[i];
	}printf("%d",ans);
	return 0;
}
```

---

## 作者：DPair (赞：2)

提供一种类似扫描线的做法。

## 【思路】
首先看到区间覆盖两次。

区间覆盖两次？

有些眼熟，然后我突然意识到这和一道扫描线题目很像。

值域较大，我们考虑用动态开点线段树维护。

对于每一个节点维护三个值：

1、当前区间被 **完全覆盖** 的次数 `t`，注意这里不下传。

2、当前区间被至少覆盖一次的总长度 `len1`

3、当前区间被至少覆盖两次的总长度 `len2`

因为要动态开点顺便记录一下左右儿子 `lc, rc`

我们考虑怎么合并。

首先我们讨论一个区间被 **完全覆盖** 过几次。

1、0次

对于这种情况，这个节点本身对覆盖一次还是两次没有任何贡献，直接 `len1[rt]=len1[lc[rt]]+len1[rc[rt]]`，`len2[rt]=len2[lc[rt]]+len2[rc[rt]]`即可。

2、1次

首先显然这个区间被至少覆盖一次的长度为区间长度`len1[rt]=r-l+1`，然后对于它的子区间，只要至少被覆盖过一次，到这个节点也是被覆盖过两次，那么`len2[rt] = len1[lc[rt]] + len1[rc[rt]]`

3、2次

这个也很简单，直接`len1[rt] = len1[lc[rt]] + len1[rc[rt]]`，`len2[rt] = len2[lc[rt]] + len2[rc[rt]]` 即可。

然后对于 `l==r` 的情况特判一下就好了。

最后放一下完整的代码实现。

## 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar() printf("I am a cheater!I AK IOI!%c", 10)
#define MAXN 100005
int t[MAXN * 33], len1[MAXN * 33], len2[MAXN * 33], tot;
int lc[MAXN * 33], rc[MAXN * 33];
#define LSON lc[rt], l, mid
#define RSON rc[rt], mid + 1, r
inline void pushup(int rt, int l, int r){
    if(t[rt]) len1[rt] = r - l + 1;
    else len1[rt] = len1[lc[rt]] + len1[rc[rt]];

    if(t[rt] > 1) len2[rt] = r - l + 1;
    else if(l == r) len2[rt] = 0;
    else if(t[rt] == 1) len2[rt] = len1[lc[rt]] + len1[rc[rt]];
    else len2[rt] = len2[lc[rt]] + len2[rc[rt]];
}

void modify(int &rt, int l, int r, int x, int y){
    if(!rt) rt = ++ tot;
    if(x <= l && r <= y){
        t[rt] ++;
        pushup(rt, l, r);
        return ;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) modify(LSON, x, y);
    if(y > mid) modify(RSON, x, y);
    pushup(rt, l, r);
}
int n, pos = 0, root;
int INF = 1000000000;
int main(){
    scanf("%d", &n);
    while(n --){
        int x;char ch[3];
        scanf("%d %s", &x, ch);
        if(ch[0] == 'L') modify(root, -INF, INF, pos - x, pos - 1), pos -= x;
        else modify(root, -INF, INF, pos, pos + x - 1), pos += x;
    }
    printf("%d\n", len2[root]);
}
```

---

## 作者：lnwhl (赞：1)

# P2070 刷墙 题解
- $\text{Upd on 2022.2.8}$ 修改了格式，增加了扫描线的做法。

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P2070)

可怜的奶牛 Bessie 刷围墙。刷 $n$ 段。每段是连续的一段栅栏。最后求刷了 $2$ 次的栅栏数。

其实无非就是区间修改问题，很容易想到 **差分**。但这道题的数据范围还是很大的，所以需要 **离散化**。


## 解法
### $\text{Part 0}$ 暴力模拟
要解这道题，首先可以把题目抽象成用点来覆盖数轴。
可是题目输入的是移动方向和距离啊。我们可以用一个结构体记录每条线段的左右端点。变量 ```place``` 记录奶牛当前位置。

如果移动方向向右，线段的左端点就是 ```place```，```place``` 再加上移动距离，线段的右端点就是改变后的 ```place``` 了！如果移动方向向左也是同样的道理。之后只要模拟一下就可以了。

**注意：下标可能为负数！！！** 所以我们得把每条线段的左右端点进行偏移，也就是都加上一个较大的数。~~（水了一个Part）~~


### $\text{Part 0.5}$ 差分优化
其实就是把 **区间修改** 转变为了两个 **单点修改**。差分不懂的可以右转 BDFS。

这样，你就能得到 $60$ 分了，$\textcolor{purple}{\text{RE}}$ 了四个点。数据范围太大了以至于数组开不下，所以我们要进行优化。



### $\text{Part 1}$ 离散化
#### $\text{Part 1.0}$ 前置知识：离散化

~~正文刚刚开始/bs~~

离散化是什么？？？离散化，把无限空间中有限的个体映射到有限的空间中去，以此提高算法的时空效率。通俗的说，离散化是在不改变数据相对大小的条件下，对数据进行相应的缩小。
举个栗子吧：

- 原数据：$1$,$999$,$100000$,$15$；

	处理后：$1$,$3$,$4$,$2$；

- 原数据：{$100$,$200$}，{$20$,$50000$}，{$1$,$400$}；

	处理后：{$3$,$4$}，{$2$,$6$}，{$1$,$5$}；
 
其实，离散化就是缩小数据范围啊！

#### $\text{Part 1.1}$ 离散化具体过程
	
离散化的基本思路就是把线段的左右端点排一个序，将原来点的 **原始坐标** 用 **排序完的序号** 代替。
假设有这样两条线段（图丑勿喷）：

![](https://cdn.luogu.com.cn/upload/image_hosting/kx6x9dnk.png)

离散化之前两条线段的左右端点分别是 {$1$,$800$} 和 {$300$,$1000$}。离散化后用该点的 **排序后的序号** 代替该点的坐标，线段的左右端点就变成了 {$1$,$3$} 和 {$2$,$4$} 了。复杂度就降到了 $O(n)$。

（代码如下）
```
	sort(whl+1,whl+sr1*2+1,cmp);//将左右端点排序
	int cnt=unique(whl+1,whl+2*sr1+1)-whl-1;//求不重复的个数
	for(int i=1;i<=sr1;i++)//离散化
	{
		a[i].left=lower_bound(whl+1,whl+cnt+1,a[i].left)-whl;//将左端点用离散化后的序号表示
		a[i].right=lower_bound(whl+1,whl+cnt+1,a[i].right)-whl;//右端点
	}
```
其他的处理方法和之前一样。但还要注意，统计长度的时候要加上离散化之前的距离。这次可以 $\textcolor{green}{\text{AC}}$ 了。总体的时间复杂度是 $O(nlogn)$
的，来自快排。

#### $\text{Part 1.2}$ 代码
```
#include <iostream>
#include <algorithm>
using namespace std;
int place=0,sr1,ans=0;
int cf[200006]={},qian[200006],whl[200006];
struct data
{
	int left,right;
}a[100003];
bool cmp(int q,int w)
{
	return q<w;
}
int main()
{
	cin>>sr1;
	for(int i=1;i<=sr1;i++)
	{
		int x;
		char y;
		cin>>x>>y;
		if(y=='R')
		{
			a[i].left=place;
			place+=x;
			a[i].right=place;
		}
		else 
		{
			a[i].right=place;
			place-=x;
			a[i].left=place;
		}
		whl[2*i-1]=a[i].left;
		whl[2*i]=a[i].right;
	}
	sort(whl+1,whl+sr1*2+1,cmp);
	int cnt=unique(whl+1,whl+2*sr1+1)-whl-1;
	for(int i=1;i<=sr1;i++)
	{
		a[i].left=lower_bound(whl+1,whl+cnt+1,a[i].left)-whl;
		a[i].right=lower_bound(whl+1,whl+cnt+1,a[i].right)-whl;
	}
	for(int i=1;i<=sr1;i++)
	{
		cf[a[i].left]++;
		cf[a[i].right]--;
	}
	for(int i=1;i<=2*sr1;i++)
	{
		qian[i]=qian[i-1]+cf[i];
		if(qian[i]>=2)ans+=whl[i+1]-whl[i]; 
	}
	cout<<ans<<endl;
	return 0;
}
```

### $\text{Part 2}$ 扫描线
$\text{Upd on 2022.2.8}$ 
#### $\text{Part 2.1}$ 思路
扫描线也是一种常用的处理大数据的技巧。思想和离散化也很像。依旧是差分把每条线段拆分成前后两个端点，然后将每一个端点的位置从小到大排序，再用扫描线记录当前重合的数量，遇到起点就 $+1$，遇到终点就 $-1$，如果超过 $2$ 层，将距离累加到答案中。
#### $\text{Part 2.2}$ 代码
```
#include <bits/stdc++.h>
using namespace std;
int n;
struct node{int left,right;}a[200005];
bool cmp(node q,node w){return q.left<w.left;}
int main()
{
    cin>>n;
    int k=0,now=0;
    for(int i=1;i<=n;i++)
    {
        int len;char c;
        cin>>len>>c;
        if(c=='L')
        {
            a[++k]={now,-1};
            a[++k]={now-=len,1};
        }
        else
        {
            a[++k]={now,1};
            a[++k]={now+=len,-1};
        }
    }
    sort(a+1,a+k+1,cmp);
    int temp=a[1].right,ans=0;
    for(int i=2;i<=k;i++)
    {
        if(temp>=2)ans+=a[i].left-a[i-1].left;
        temp+=a[i].right;
    }
    cout<<ans;
    return 0;
}
```



## 后记

本题还有一个加强版 P2205，可以练手。



---

## 作者：木木！ (赞：1)

首先想法是利用并查集跳（类似[P4145 上帝造题的七分钟II](https://www.luogu.org/problemnew/show/P4145)），但是由于值范围为$10^9$，需要离散化。

一想到离散化，就想到转区间，~~就想到红孩儿坐在观音的莲花上面转的场面，去年下半年，中美合拍的西游记即将开机……算了直接开花~~。

既然已经变成一堆小区间了，就可以直接排序然后暴力扫一遍。

排序过后，记录一个`prel`和`prer`，表示只刷过一遍的区间。每次新扫一个更新维护。

正确性显然。并查集跳的复杂度为$\Theta(nlogn+n\alpha(n))$（瓶颈离散化），排序扫一遍的复杂度为$\Theta(nlogn+n)$。

为什么要排序呢？因为如果当前扫到的区间的左端点比`prel`大，如果排过序，就可以保证没有其他左端点更小的区间，可以直接把prel变成l。

附AC代码

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

#define int long long

struct inv
{
	int l;
	int r;
};

inv li[100005];

bool cmp(inv a,inv b)
{
	if(a.l != b.l)
	{
		return a.l < b.l;
	}
	return a.r < b.r;
}

signed main()
{
	int n;
	scanf("%lld",&n);
	
	int pos = 0;
	for(int i=1; i<=n; ++i)
	{
		char c;
		int d;
		scanf("%lld %c",&d,&c);
		
		if(c=='L')
		{
			li[i].l = pos-d;
			li[i].r = pos;
			pos -= d;
		}
		else
		{
			li[i].l = pos;
			li[i].r = pos+d;
			pos += d;
		}
	}
	
	sort(li+1,li+1+n,cmp);
	
	int ans = 0;
	int prel = 0x8000000000000000LL; //必须得足够小
	int prer = 0x8000000000000000LL;
	for(int i=1; i<=n; ++i)
	{
		if(li[i].l > prer)
		{
			prel = li[i].l;
			prer = li[i].r;
		}
		else if(li[i].r < prel)
		{
			continue;
		}
		else
		{
			if(li[i].r >= prer)
			{
				if(li[i].l >= prel)
				{
					ans += prer-li[i].l;
				}
				else
				{
					ans += prer-prel;
				}
				prel = prer;
				prer = li[i].r;
			}
			else
			{
				if(li[i].l >= prel)
				{
					ans += li[i].r-li[i].l;
				}
				else
				{
					ans += li[i].r-prel;
				}
				prel = li[i].r;
			}
		}
	}
	
	printf("%lld",ans);
}
```

---

## 作者：PinkieDeer (赞：0)

## solution

很容易想到，其实这只奶牛每次行走，都是走了一段区间。

于是我们只需要记录下这只奶牛每次行走走过的区间，用 $(l, r)$ 储存，然后问题就被转化成求被至少两个区间覆盖的面积了。

这里有个优化：可以把 Bessie 多次连走同一个方向，合并在一起。

如何求被至少两个区间覆盖的面积？

我们先对区间排序，按照 $l$ 从小到大排序，如果 $l$ 相等按照 $r$ 排序。

然后我们直接扫一遍数组，维护一个被大于等于 $2$ 个区间覆盖的最右点 $j$，和一个当前扫到区间中的最右点 $maxr$。

每次如果发现当前区间的 $l$ 小于 $maxr$，就说明区间 $[l, \min(r, maxr)]$，被覆盖了两次。

那么我们除去这个区间被计算过的部分，于是 $ans += \max(0LL, \min(maxr, r) - \max(l, j))$。

然后就是更新 $maxr$ 和 $j$。

一直扫完整个数组

最后输出答案

## code

```cpp
#include<iostream>
#include<algorithm>
using namespace std;

struct sec
{
	long long l, r;
};

sec sect[1000010];
long long n, m;

bool cmp(sec a, sec b)
{
	if(a.l == b.l)
	{
		return a.r < b.r;
	}
	return a.l < b.l;
}

int main()
{
	cin >> n;
	char lastd = '\0';
	long long nowl = 0, nowr = 0;
	for(long long i = 0; i < n; i++)
	{
		long long len;
		char d;
		cin >> len >> d;
		if(d != lastd && lastd != '\0')
		{
			sect[++m] = {nowl, nowr};
			if(d == 'R')
			{
				nowr = nowl;
			}
			else
			{
				nowl = nowr;
			}
		}
		if(d == 'R')
		{
			nowr += len;
		}
		else
		{
			nowl -= len;
		}
		lastd = d;
	}
	sect[++m] = {nowl, nowr};
	sort(sect + 1, sect + m + 1, cmp);
	long long ans = 0, maxr = -1000000000;
	for(long long i = 1, j = -1000000000; i <= m; i++)
	{
		if(sect[i].l <= maxr)
		{
			ans += max(0LL, min(maxr, sect[i].r) - max(sect[i].l, j));
		}
		j = max(j, min(maxr, sect[i].r));
		maxr = max(maxr, sect[i].r);
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：信守天下 (赞：0)

## 思路一：暴力模拟
但是题目的数据范围太大，模拟肯定会超时

~~事实上也真的超了~~

所以直接模拟肯定不行

## 思路二：差分
可以去模拟一下奶牛行走的路线，

就会发现奶牛行走的路是**连续的一段！**

那么我们就可以用差分来做

可以给每个序列排序后进行差分

还可以进行前缀和优化，但是没必要
## $code$
~~~cpp
#include <algorithm>
#include <iostream>
using namespace std;
const int kMaxN = 1e5 + 1;
struct S {
  int x, v;
  bool operator<(const S &s) const {
    return x < s.x;
  }
} s[2 * kMaxN];
int n, p, _p, l, ans;
char c;
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> l >> c;
    _p = p + (c == 'L' ? -l : l);
    s[i] = {min(p, _p), 1};
    s[i + n] = {max(p, _p), -1};
    p = _p;
  }
  sort(s + 1, s + 1 + 2 * n);
  for (int i = 2, c = s[1].v; i <= 2 * n; i++) {
    if (c >= 2) {
      ans += s[i].x - s[i - 1].x;
    }
    c += s[i].v;
  }
  cout << ans;
  return 0;
}
~~~

---

## 作者：Mogician (赞：0)

说明：由于牛可以移动的距离非常大，所以用10^9\*2的数组存储一段被刷过几次是不现实的，所以我们要利用前缀和。

我们可以把问题化简：把栅栏视为数轴，牛每一次移动就是在数轴上画线段。我们把线段左边端点所在位置+1，右端-1，把所有端点位置记录下来，按端点排序，再一遍扫过即可，只要20ms。

···
var qz,wz:array[0..1000000] of longint; //qz为前缀，wz为端点所在位置，数组记得开大

```cpp
    i,j,k,t,m,n,p:longint;
    c:char;
    f:boolean;
procedure sort(l,r: longint);
      var
         i,j,x,y: longint;
      begin
         i:=l;
         j:=r;
         x:=wz[(l+r) div 2];
         repeat
           while wz[i]<x do
            inc(i);
           while x<wz[j] do
            dec(j);
           if not(i>j) then
             begin
                y:=wz[i];
                wz[i]:=wz[j];
                wz[j]:=y;
                y:=qz[i];
                qz[i]:=qz[j];
                qz[j]:=y;
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
 {assign(input,'233.in');
 reset(input);}
 readln(n);
 for i:=2 to n+1 do
  begin
   read(k); read(c); read(c);
   if c='R' then begin inc(t,k); wz[i]:=t; dec(qz[i]); inc(qz[i-1]); end
    else begin dec(t,k); wz[i]:=t; inc(qz[i]); dec(qz[i-1]); end; //记录两端前缀
  end;
 sort(1,n+1); //快排
 k:=0; t:=0;
 for i:=1 to n do
  begin
   inc(t,qz[i]);
   if t>=2 then inc(k,wz[i+1]-wz[i]); //刷过两次以上的墙就累加
  end;
 writeln(k);
end.
···
```

---

