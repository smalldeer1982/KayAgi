# Two TVs

## 题目描述

Polycarp 很喜欢看电视。

他写下了他今天所有感兴趣的共   $n\,(1 \le n \le 2 \times 10^5)$ 个电视节目。其中第   $i$ 个电视节目在   $l_i$ 时开始，  $r_i$ 时结束。  $\,(0 \le l_i, r_i \le 10^9)$

Polycarp 有两个电视。他可以同时在两台电视上看两种不同的节目，但他不能在一台电视上同时看两个不同的节目。如果一个节目结束时另一个节目刚好开始，则他不能在一台电视上看这两个节目。他想看完这   $n$ 个节目，请问两台电视足够吗？

## 样例 #1

### 输入

```
3
1 2
2 3
4 5
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4
1 2
2 3
2 3
1 2
```

### 输出

```
NO
```

# 题解

## 作者：4526_ (赞：13)

[题目链接](https://www.luogu.org/problemnew/show/CF845C)

之前有dalao发了代码差不多的，然而个人感觉讲得不够清楚，于是来一发侧重分析题目的，代码里也加了一些注意事项

#### 主要思想：模拟（不知道为什么之前的dalao写的是贪心）

大致思路：

1、因为只有两个电视，直接用变量比较方便，我们就开两个变量代表电视（如果电视数量比较多，一般就用数组存储），模拟两个电视收看节目的过程

2、每个节目能不能被收看，取决于**它开始播放时有没有电视可以立即收看它**，只需要记录每个电视什么时候看完之前的节目，即该电视可以开始收看下一个节目的时间

3、根据生活经验，我们看节目单会按照时间从前往后看，然而题面没说从小到大输入，一般不会这么好心按时间顺序给出数据，还需要**对输入数据进行排序**，由2可知按**开始时间从早到晚**（即从小到大）更方便解题，为了防止同时开始的特殊情况，加入特判，如果同时开始就按结束时间，因为**结束时间对结果没有影响**，这里可以随意选取排序方式，如果都相同，同样不影响结果

4、如果某个节目的开始时间早于两个电视的空闲时间，那么它开始的时候两个电视都在收看其他节目，这个节目就**无法被收看**，由于题目不要求无法被收看的节目数量，后面的节目能否被收看已经对结果无影响，为了减少运行时间可以直接结束程序

5、如果某个节目的开始时间晚于某个电视的空闲时间，那么它**可以被这个电视收看**，更新相应变量存储的值即可

6、因为之前的排序方法，后面的节目开始时间都不会早于之前的，如果节目A开始时间早于节目B，用电视1收看A后电视1和电视2都不能收看B，那么用1收看B会导致1和2都不能收看A，所以**用哪个电视收看之前的节目不会影响结果**

AC代码：

```cpp
#include<cmath> 
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n,tv1,tv2;//大于tv1,tv2的节目可以被收看 
struct dat{
    int l,r;
};
dat pros[200010];//program,电视节目 

bool cmp(dat a,dat b){
    if(a.l!=b.l) return a.l<b.l;
    return a.r<b.r;//注意特殊情况 
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        scanf("%d %d",&pros[i].l,&pros[i].r);
    }
    sort(pros+1,pros+1+n,cmp);//注意输入乱序 
    tv1=tv2=-1;//开始时间可能是0，所以初始空闲时间从-1计算 
    for(int i=1;i<=n;++i){
        if(pros[i].l<=tv1&&pros[i].l<=tv2){
            printf("NO");//注意大写 
            return 0;
        }
        if(pros[i].l>tv1) tv1=pros[i].r;
        else if(pros[i].l>tv2) tv2=pros[i].r;
    }
    printf("YES");//注意大写 
    return 0;
}
```

欢迎来[我的blog](https://www.luogu.org/blog/4526-Au/#)看看

---

## 作者：Dawn_Chase (赞：8)

~~为什么看到楼下的聚聚们用了我不会的算法[可怜]~~

让本蒟蒻来一发简介易懂的代码

## 接下来是正题
看到这道题,想必大家的第一反应是贪心.

因为只有两台电视可以同时工作,所以我们用now1,now2来表示当前电视的**最早可以没事干的时间**.

但是这样的话,我们要保证节目的时间是**有序**的,这样才能处理**最早可以没事干的时间**

~~由于我的语言能力过差~~

想必大家还没有听懂我这一句话的意思...

那我们根据样例来解释一下我这句话的意思

### (假装是样例1)
3

1 2

2 3

4 5

~~我们发现了这个样例是有序的,所以我们可以先不用排序~~

然后我们发现第一个节目是1~2,然后这个时候两台电视都是空着的,所以我们~~假装~~现在第一台电视在放第一个节目,然后这样的话就可以不用管,所以**当前的now1=2**.

接下来我们发现第二个节目是2~3,然后由于题意,我们不能在某一个瞬间切换节目,所以说我们需要使用第二台电视,所以**当前的now2=3**.

最后我们发现第三个节目是4~5,我们可以发现,第一台电视已经结束第一个节目播放了(即a[i].l>now1)!那么我们可以发现,~~用第一台电视就可以了对吧~~.所以所以**当前的now1=5**

最后发现这整个过程中都没有出现不合法的时候

## 然后我们这道题就做完啦!

接下来是代码(码风极丑):
```
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int n,now1,now2;
struct node
{
	int l,r;
}
a[200010];
bool cmp(node x,node y)
{
	return x.l<y.l||(x.l==y.l&&x.r<y.r); //这里的话就是我们的排序,由于我太蒻不喜欢三目运算符...
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d%d",&a[i].l,&a[i].r);
	sort(a+1,a+n+1,cmp);
	now1=-1;now2=-1; //如果初始赋为0的话,会咕,本人就在这里咕了一次(逃)
	for (int i=1;i<=n;i++)
	{
		if (a[i].l>now1) //这里的话是第一个判断,毕竟我们多用用第一台电视是没有问题的对吧
			now1=a[i].r;
		else
		if (a[i].l<=now1) 
			if (a[i].l>now2)
				now2=a[i].r;
			else
			{
				printf("NO\n"); //这里的话是出现不合法的瞬间,我们直接判掉就可以了
				return 0;
			}
	}
	printf("YES\n");
	return 0;
} 
```

---

## 作者：Minecraft万岁 (赞：4)

看到这题我的第一印象是贪心 但是我~~觉得太复杂太烦了~~不会写 所以我们还是分析一下为什么可以为什么不可以  
画出一条数轴 用两点之间的间隔作为时间点 注意题目中 
### 如果一个节目结束的瞬间另一个节目开始的话 他不能在同一个电视上看这两个节目  
也就是说如果有两个电视节目分别为 $l_1$ $r_1$ 和 $l_2$ $r_2$ 当 $r_1=l_2$ 时 两个电视是不可以在一个电视上看的 


------------
第一个样例的图
![](https://cdn.luogu.com.cn/upload/image_hosting/a9m5rvgr.png) 
这个是可以的 输出 $YES$  


------------

第二个样例的图 
![](https://cdn.luogu.com.cn/upload/image_hosting/l9glcrn2.png)  
这个是不可以的 输出$NO$   
~~发现了什么$?$~~  
### 如果有超过$2$条线段包含同一个时间点这个数据一定是$NO$否则$YES$  
再看一眼数据  $l_i r_i$ 非常大 我们可以用离散化计算每一个点的重复次数 或者说最多的重复次数一定会出现 只要不超过 $2$ 就一定可以 否则不可以  
给出我用离散化写的代码 
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
struct node
{
	int p;
	int val;
}a[400005];//离散化数组开2*n 
int n,hp;
int l,r;
int tmp;
bool ok;//标志 true:NO false:YES 
inline void read(int &x)//快读 
{
	int f;char c;
	for (f=1,c=getchar();c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for (x=0;c<='9'&&c>='0';c=getchar()) x=x*10+(c&15);x*=f;
}
inline bool cmp(node x,node y)//排序 
{
	if(x.p!=y.p) return x.p<y.p;
	else return x.val<y.val;//离散化先减后加 
}
int main()
{
	read(n);//读入 
	for(int i=1;i<=n;i++)
	{
		read(l);read(r);//再读入 
		a[++hp].p=l;//标准离散化*1 
		a[hp].val=1;
		a[++hp].p=r+1;
		a[hp].val=-1;
	}
	sort(a+1,a+hp+1,cmp);//标准离散化*2
	for(int i=1;i<=hp;i++)
	{
		tmp+=a[i].val;//标准离散化*3 
		if(tmp>2)//如果最多超过2 那么不可以 如果最多没超过2 那么可以 
		{
			ok=true;//打个标记 
			break;//直接跳出不做了 
		}
	}
	if(ok) puts("NO");//根据标记输出 
	else puts("YES");
	return 0;
}


```


---

## 作者：寒冰大大 (赞：2)

~~智商不够线段树来凑~~

虽然是一个差分的裸题，但是线段树也是可以过的。

原来题解有篇动态开点的线段树，不过这道题直接离散化然后用线段树做区间修改即可。

对了，stl是个好东西，用对了代码短50行不是问题。
另外说一下，去重后不是在$[1,n]$中排，而是对问题的不同区间端点排序。


```cpp
#include<touwenjian.h>// 由于每次都卡我头文件，所以我不打了

#define lson i<<1,l,mid
#define rson i<<1|1,mid+1,r
#define ls i<<1
#define rs i<<1|1

using namespace std;
int n,m;

struct tree{
	int mmx,add;
}t[2001000];

struct que{
	int l,r;
}q[200200];
int bj[400400],bt=0;

struct orztree{
	//线段树没有什么好讲的，结构体美观大方
	inline void pushup(int i)
	{
		t[i].mmx=max(t[ls].mmx,t[rs].mmx);
		return ;
	}
	
	inline void pushdown(int i)
	{
		t[ls].add+=t[i].add;
		t[rs].add+=t[i].add;
		t[ls].mmx+=t[i].add;
		t[rs].mmx+=t[i].add;
		t[i].add=0;
	}
	
	void change_tree(int i,int l,int r,int x,int y,int tar)
	{
		if(l>=x&&r<=y)
		{
			t[i].add+=tar;
			t[i].mmx+=tar;
			return ;
		}
		pushdown(i);
		int mid=(l+r)/2;
		if(x<=mid) change_tree(lson,x,y,tar);
		if(y>mid) change_tree(rson,x,y,tar);
		pushup(i);
		return ;
	}
}st;

int main()
{
	ios::sync_with_stdio(false);
	register int i,j;
	cin>>n;
	m=n;  //这里原来以为是读入n，m，结果看了题才发现只有m
	int t1,t2;
	for(i=1;i<=m;i++)
	{
		cin>>t1>>t2;
		bj[++bt]=t1;
		bj[++bt]=t2;
		q[i].l=t1;
		q[i].r=t2;
	}
	sort(bj+1,bj+bt+1);
    //一定要注意-1
	bt=unique(bj+1,bj+bt+1)-bj-1;
	for(i=1;i<=m;i++)
	{
		int t1=lower_bound(bj+1,bj+bt+1,q[i].l)-bj;
		int t2=lower_bound(bj+1,bj+bt+1,q[i].r)-bj;
		st.change_tree(1,1,bt,t1,t2,1);
	}
 	//t[1].mmx即为整个区间同时要看的电视的数量最大值
	if(t[1].mmx>2) cout<<"NO";
	else cout<<"YES";
	return 0;
}
```


---

## 作者：SaoFish (赞：0)

好像是第一次写动态开点线段树（滑稽），感觉通过这道题涨了姿势

~~我是个什么都不会的蒟蒻~~

看到数据范围，就想到了**离散化区间**或者**动态开点线段树**，**区间加1**，然后**区间询问最大值**，每次修改后判断**最大值是否大于2**，因为就只能用两个电视。

还有动态开点线段树应该开多大的数组，求教

完结撒花

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=210000;
int n,root,opt,Max[N<<6],lson[N<<6],rson[N<<6],lazy[N<<6];
void pushdown(int k,int l,int r){
	if (!lazy[k]) return;
	if (l!=r){
		if (!lson[k]) lson[k]=++opt;
		if (!rson[k]) rson[k]=++opt;
		lazy[lson[k]]+=lazy[k];
		lazy[rson[k]]+=lazy[k];
		Max[lson[k]]+=lazy[k];
		Max[rson[k]]+=lazy[k];
	}
	lazy[k]=0;
}
void insert(int &k,int l,int r,int L,int R){
	if (l>R||r<L) return;
	if (!k) k=++opt;
	if (l>=L&&r<=R) return (void) (Max[k]++,lazy[k]++);
	pushdown(k,l,r);
	int mid=l+r>>1;
	if (L<=mid) insert(lson[k],l,mid,L,R);
	if (R>mid) insert(rson[k],mid+1,r,L,R);
	Max[k]=max(Max[lson[k]],Max[rson[k]]);
}
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		int x,y; scanf("%d%d",&x,&y);
		insert(root,0,1000000000,x,y);
		if (Max[1]>2) return puts("NO"),0;
	}
	puts("YES");
	return 0;
}
```

---

