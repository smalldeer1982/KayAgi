# [USACO10FEB] Covering the Corral G

## 题目描述

The cows are so modest they want Farmer John to install covers around the circular corral where they occasionally gather. The corral has circumference C (1 <= C <= 1,000,000,000), and FJ can choose from a set of M (1 <= M <= 100,000) covers that have fixed starting points and sizes. At least one set of covers can surround the entire corral.

Cover i can be installed at integer location x\_i (distance from starting point around corral) (0 <= x\_i < C) and has integer length l\_i (1 <= l\_i <= C).

FJ wants to minimize the number of segments he must install. What is the minimum number of segments required to cover the entire circumference of the corral?

Consider a corral of circumference 5, shown below as a pair of connected line segments where both '0's are the same point on the corral (as are both 1's, 2's, and 3's).

Three potential covering segments are available for installation:

Start   Length

i     x\_i     l\_i

1      0       1

2      1       2

3      3       3

0   1   2   3   4   0   1   2   3  ...

corral: +---+---+---+---+--:+---+---+---+- ...

11111               1111

22222222            22222222

333333333333

|..................| 
As shown, installing segments 2 and 3 cover an extent of (at least) five units around the circumference. FJ has no trouble with the overlap, so don't worry about that.

奶牛们非常羞涩，他们要求Farmer John在他们的圆形牛棚周围建造围栏。牛棚的周长为c(1 <= C <= 1,000,000,000)，现在，FJ希望从一些有固定起点和终点的栏杆的集合里选出一些栏杆。 栏杆i 的起点可以被建造在一个整数位置 x\_i(相距围栏起点i个长度) (0 <= x\_i < C),并且，这个栏杆有一个整数长度l\_i(1 <= l\_i <= C)。 FJ 希望最小化栏杆的数量，从而达到覆盖整个牛棚的外圈。


## 样例 #1

### 输入

```
5 3 
0 1 
1 2 
3 3 
```

### 输出

```
2 
```

# 题解

## 作者：gyfer (赞：4)

这是一道~~模拟题~~
思路：排序优化，模拟放置。


------------

HINT：先把被别人覆盖的丢掉。环？复制一遍当做序列来做。对每个壁纸求出能接在它后面的右端点最大的。（怎么求？）那之后咋办啊（掀桌）
我会！枚举作为起点的牛，然后不断地往后跑直到覆盖一整圈！
......n元环了解一下？
把牛看作点，每个点有且只有一条出边...基环内向树！
点权为壁纸长度，边权为增加的有效长度。
只要起点点权+各边权和>=C就好了。
类似于two pointer，随着起点往后跳，终点也随着往后跳。
可惜的是不管是正向还是反向复杂度都好像是错的。。
。

首先把被完全覆盖的围栏去掉，剩下的按左端点升序排序。那么右端点肯定也是升序的了。。然后计算出每段围栏，它接下去一段围栏可达到的最远距离。枚举起点，贪心地一段一段接下去就可得到该起点的最优解。

直接这样做显然会T。。

------------
**正解**

换个方向...考虑某个答案啥时候会被计算到。
显然不管是啥答案，肯定有条跨过环的边。
枚举那条边...然后呢？总不能直接跑吧对每个点x预处理出f[x],pos[x]：以x为起点，一直跳到 即将跨环
(再走一步就跨环了)的时候，走了几条边，停在哪里。枚举跨环的初始边(x,y)，之后y直接跑到pos[y]，然后稍微判断一下。

 _AC代码_ 
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N=200001;
const int INF=0x3f3f3f;
struct node{
    int l,r;
}a[N];
int nxt[N],pos[N],jump[N],tmpcos[N];
int i,j,L,n,m,ans,k;
bool cmp(node x,node y){
    return x.l==y.l?x.r>y.r:x.l<y.l;//排序了解一下
}
void get(int x){//得到当前牛所能到达的最远点
    if(jump[x]) return;

    if(a[x].r>=L){
        jump[x]=x;
        tmpcos[x]=0;
    }else{
        get(nxt[x]);
        jump[x]=jump[nxt[x]];
        tmpcos[x]=tmpcos[nxt[x]]+1;
    }
}
int main(){
    cin>>L>>n;
    for(int i=1;i<=n;i++) cin>>a[i].l>>a[i].r,a[i].r+=a[i].l;
    sort(a+1,a+n+1,cmp);
    int mx=-1,tmp=0;
    for(int i=1;i<=n;i++)//缩牛操作
      if(a[i].r>mx) {
          a[++tmp]=a[i];
          mx=a[i].r;
      }
    n=tmp;
    tmp=0;
    for(int i=1;i<=n;i++){//计算pos
        nxt[i]=nxt[i-1];
        for(;tmp<n&&a[tmp+1].l<=a[i].r;tmp++);
        if(tmp==i) nxt[i]=0;
        else{
            nxt[i]=tmp;
            pos[i]=a[tmp].r;
        }
        //cout<<nxt[i]<<endl;
    }
    int tmpsum,now;//tmpsum:计算牛的总数
    ans=INF;
    for(int i=1;i<=n;i++){
        if(!jump[i]) get(i);
        tmpsum=tmpcos[i]+1;
        now=jump[i];
        while(nxt[now]&&a[now].r<a[i].l+L&&tmpsum<ans){
            now=nxt[now];
            tmpsum++;
        }
        if(a[now].r>=a[i].l+L&&tmpsum<ans) ans=tmpsum;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：H_D_NULL (赞：2)

### ~~不是我说，还是外国的题出得简单一些~~


------------

首先分析题面，第一眼觉得是一个贪心。然后仔细看了一下，居然是一个环！太不好贪心了。还有段与段之间还有包含关系，不能支持简单的贪心。最后总体分析了一下，得出本题最大的难点：~~那是什么鬼图啊？！~~

经过以上分析，我们不难得出本题的做法：~~**贪心**~~。

------------

**大体贪心策略：** 管他是不是环，对于当前已选的，只要找到一类围栏，使其起始端点在已选围栏的包含范围之内（或刚好能接上），然后在这些围栏里，找延伸得最远的（及右端点的值越大的）。正确性不难证明，只是复杂度暂时有些问题。枚举要选的第一个围栏，然后如上述策略贪心地加围栏，直到形成一个环。

**进一步优化：** 策略是没得优化了，关键就看能不能用更少的时间。大多数的人的做法（特指某篇题解）是只预处理对于选了某一条边的情况，下一次贪心选的边，这样做完全没有问题，~~但是没有逼格~~ 。而有些人（特指另一篇）给我们提供了更优的思路——**倍增** 。用类似找LCA的方法，可以快速找到从一段围栏出发，到结束所用的最少围栏数。~~P.S. 似乎加了倍增优化和暴力跳边实际的时间差距不大？~~

*Talk is cheap, show me the code.*

```cpp
#include<bits/stdc++.h>
#define re register
#define Maxm 100005
using namespace std;

int C,M,Ans=Maxm,tot;

inline int read(){
	re int ret=0;
	re char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') ret=(ret<<1)+(ret<<3)+c-'0',c=getchar();
	return ret;
}

struct dr{
	int L,R;
	int Nxt[20];
} t1[Maxm],t[Maxm<<1];

inline bool cmp(dr x,dr y){
	return x.L<y.L;
}

int main(){
	C=read();
	M=read();
	for(re int i=1;i<=M;i++){
		t1[i].L=read();
		t1[i].R=t1[i].L+read();
	}
	sort(t1+1,t1+1+M,cmp);
	for(re int i=1;i<=M;i++){ //去重（目测有大用）
		if(t1[i].R>t[tot].R){
			t[++tot]=t1[i];
		}
	}
	M=tot;
	for(re int i=1;i<=M;i++){
		t[i+M].L=t[i].L+C;
		t[i+M].R=t[i].R+C;
	}
	re int tmp=1;
	for(re int i=1;i<=M<<1;i++){
		t[i].Nxt[0]=t[i-1].Nxt[0];
		for(;tmp<=M<<1&&t[tmp].L<=t[i].R;tmp++){ //贪心：找直接接在自己后面的那条围栏
			if(t[tmp].R>t[t[i].Nxt[0]].R) t[i].Nxt[0]=tmp;
		}
	}
	for(re int i=M<<1;i;i--){ //预处理倍增数组
		for(re int j=1;j<=18&&t[t[i].Nxt[j-1]].Nxt[j-1];j++){
			t[i].Nxt[j]=t[t[i].Nxt[j-1]].Nxt[j-1];
		}
	}
	for(re int i=1,sum,now;i<=M;i++){
		sum=1; now=i;
		for(re int j=18;j>=0;j--){ //倍增从大往小找
			if(t[now].Nxt[j]&&t[t[now].Nxt[j]].R-t[i].L<C){
				now=t[now].Nxt[j];
				sum+=1<<j;
			}
		}
		if(t[now].Nxt[0]&&t[now].R-t[i].L<C){
			sum++; now=t[now].Nxt[0];
		}
		if(t[now].R-t[i].L>=C) Ans=min(Ans,sum);
	}
	printf("%d",Ans);
	return 0;
}
```


---

