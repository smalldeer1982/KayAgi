# Chtholly Nota Seniorious

## 题目背景

经查，本题是原题，非常抱歉。

大样例下发链接: https://pan.baidu.com/s/1nuVpRS1 密码: sfxg

**こんなにも、たくさんの幸せをあの人に分けてもらった**

**だから、きっと**

**今の、私は**

**谁が何と言おうと**

##世界一、幸せな女の子だ

![](https://cdn.luogu.com.cn/upload/pic/9193.png)


## 题目描述

——“假如……我是说假如喔。

万一我再过五天就会死，你能不能对我温柔一点？”

巨大的六号兽五天后将袭击浮游大陆。

无数次计算得到的残酷数据表明，只有圣剑瑟尼欧尼斯的适格精灵——珂朵莉·诺塔·瑟尼欧尼斯(Chtholly Nota Seniorious)开启妖精乡之门，才可以以生命为代价守住浮游岛。

 ![](https://cdn.luogu.com.cn/upload/pic/9228.png) 

“至少，我也希望自己不用消失，也想让别人记住。我也想留下羁绊啊。”

留给妖精少女珂朵莉的时间似乎已经不多了。

 ![](https://cdn.luogu.com.cn/upload/pic/9229.png) 

年轻的二等技官，妖精仓库的管理员，世界上最后一个人类——威廉·克梅**修**，数百年前曾经是一名准勇者，掌握着成为一名勇者所需要的所有知识。

大战在即，调整圣剑的状态成为了一项重要的任务。

```cpp
瑟尼欧里斯（セニオリス）
圣剑的其中之一，在现存的遗迹兵装中，拥有最强大的力量。
拥有非常特殊的资质，只有极少一部分的人才能使用。
由四十一个护符组成。能将所有事物包含不死者都回归「死亡」。
```
威廉需要调整圣剑的状态，因此他将瑟尼欧尼斯拆分护符，组成了一个$n$行$m$列的矩阵。

每一个护符都有自己的魔力值。现在为了测试圣剑，你需要将这些护符分成 A,B两部分。

要求如下：

1.  圣剑的所有护符，恰好都属于两部分中的一部分。

2.  每个部分内部的方块之间，可以通过上下左右相互到达，而且每个内部的方块之间互相到达，最多允许拐一次弯。

例如
```cpp
ＡＡＡＡＡ　　ＡＡＡＡＡ　　ＡＡＡＡＡ
ＡＡＢＡＡ　　ＢａＡＡＡ　　ＡＡＡＢＢ
ＡＢＢＢＡ　　ＢＢＡＡＡ　　ＡＡＡＢＢ
ＡＡＢＡＡ　　ＢａＡＡＡ　　ＡＢＢＢＢ
ＡＡＡＡＡ　　ＡＡＡＡＡ　　ＢＢＢＢＢ

　　(1)　　　　　(2)　　　　　(3)　　　　　　
```
其中(1)(2)是不允许的分法，(3)是允许的分法。在(2)中，a属于A区域，这两个a元素之间互相到达，没有办法最多只拐一次弯。

现在要问，所有合法的分法中，A区域的极差与B区域的极差 中间较大的一个的 **最小值** 是多少？

好心而可爱的在一旁默默观察奈芙莲悄悄地告诉你，极差就是区域内最大值减去最小值。

 ![](https://cdn.luogu.com.cn/upload/pic/9230.png) 

夜晚的风吹拂着，68号岛上的景色竟与地上的森林无异。转念又想，黄金妖精本身就是与森林之中出现，成长，消亡的神秘存在啊。

时间不早了，早上训练中落败的珂朵莉即将回来了。您要尽快和威廉一起调整好圣剑，千万不能迟哟。


## 说明/提示

样例解释

```cpp
1  12 6        11
11 4  2        14
10 1  9        20
4        17 13 10
```
分法不唯一，如图是一种合法的分法。左边部分极差12-1=11，右边一块极差20-10=10，所以答案取这两个中较大者11。没有别的分法，可以使答案更小。


**数据范围与约定**


测试点　　|n　　　　|m　　　　
-|-|-
#1-2      |$\le 10$ |$\le 10$
#3-4      |1        |$\le 2000$
#5-7      |$\le 200$|$\le 200$
#8-10     |$\le 2000$|$\le 2000$

对于所有的权值$1\le A_{i,j} \le 10^9$


《末日时在做什么？有没有空？可以来拯救吗？》

![](https://cdn.luogu.com.cn/upload/pic/9235.png)


## 样例 #1

### 输入

```
4 4
1 12 6 11
11 4 2 14
10 1 9 20
4 17 13 10```

### 输出

```
11```

# 题解

## 作者：Anoxiacxy (赞：20)

对于这种最优化问题，我们可以二分答案啊，显然，最大值和最小值一定不被划分到一个区域里，那么我们假定最大值在矩形的上三角里，对于那些大于最大值减去我们二分的答案的数，都是符合要求的，然后判断不在当前区域的数，是不是都小于最小值加上我们二分的答案，由于最大值，最小值的位置不确定，所以我们可以把矩阵旋转四次，分别判断即可，只要有一种满足条件即可


## 以下为英语短文填空裸题，后附参考答案


```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#define inf int(2e9)
#define nl NULL
using namespace std;
int ___,____;int ______________=0,_____________=inf;
int _________________[4][2017][2017],_______________=3;
bool __________________[2017][2017];
void ________(int ___________________,int ____________________){
    for(int _=1;_<=___;_++)
        for(int __=1;__<=____;__++)
            _________________[____________________][__][___-_ + 1]=_________________[___________________][_][__];
    swap(____ ,___);
}
bool _________(int ________________){
    int ____________=____;
    memset(__________________,0,sizeof(__________________));
    for(int _=1;_<=___;_++)
        for(int __=1;__<=____________;__++)
            if(_________________[_______________][_][__]+________________<______________){
                ____________=__-1;break;
            }else __________________[_][__] = true;
    for(int _=___;_; _--)
        for(int __=____; __; __--)
            if(__________________[_][__])break;
            else if(_________________[_______________][_][__]-________________>_____________)return false;
    return true;
}
void ___________(){swap(___,____);_______________=(_______________+1)%4;}
bool __________(int ________________){
    if(_________(________________)) return true; ___________();
    if(_________(________________)) return true; ___________();
    if(_________(________________)) return true; ___________();
    if(_________(________________)) return true; ___________();
    return false;        
}
int main(){
    scanf("%d%d",&___,&____);
    for(int _=1;_<=___;_++)for(int __=1;__<=____;__++){
        scanf("%d",&_________________[0][_][__]);
        ______________=max(______________,_________________[0][_][__]);
        _____________=min(_____________,_________________[0][_][__]);
    }
    ________(0,1);________(1,2);________(2,3);
    int _____=0,______=______________-_____________;
    while(_____<______){
        int _______=_____+______ >> 1;
        if(__________(_______))______=_______;
        else _____=_______+1;
    }
    printf("%d",_____);
}
```
## 参考答案




```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#define inf int(2e9)
#define nl NULL
using namespace std;
int n,m;int maxv = 0, minv = inf;
int a[4][2017][2017], coc = 3;
bool f[2017][2017];
void rotate(int s,int t){
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            a[t][j][n - i + 1] = a[s][i][j];
    swap(m ,n);
}
bool deal(int ans){
    int p = m;
    memset(f, 0, sizeof(f));
    for(int i = 1; i<= n; i++)
        for(int j = 1; j <= p; j++)
            if(a[coc][i][j] + ans < maxv){
                p = j - 1; break;
            }else f[i][j] = true;
    for(int i = n; i; i--)
        for(int j = m; j; j--)
            if(f[i][j]) break;
            else if(a[coc][i][j] - ans > minv) return false;
    return true;
}
void nxt() {swap(n, m); coc = (coc + 1) % 4; }
bool check(int ans){
    if(deal(ans)) return true;nxt();
    if(deal(ans)) return true;nxt();
    if(deal(ans)) return true;nxt();
    if(deal(ans)) return true;nxt();
    return false;        
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
        scanf("%d",&a[0][i][j]);
        maxv = max(maxv, a[0][i][j]);
        minv = min(minv, a[0][i][j]);
    }
    rotate(0, 1); rotate(1, 2); rotate(2, 3);
    int l = 0, r = maxv - minv;
    while(l < r){
        int mid = l + r >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    printf("%d", l);
}

```

---

## 作者：石榴 (赞：6)

看见没人写题解，我发一篇？

首先，作为一位买了八连测的人，我顺利地听到了will老师的讲解并知道了怎么做这道题。

考完试后1a了。

感觉自己的做法与题解有一点点小小的不同？

其实就是贪心时候可能大概应该是有点不同吧……大体思路还是按着题解的思路来的。

首先这是一道二分。

我们先求出数组中的最大值和最小值，其差为二分右端点。

二分左端点当然是萌萌哒的0了0^0。

然后就是二分。

我们还要进行三次旋转分别二分，二分里面就是贪心。

贪心策略如下：

假设贪心之后的两部分分别为红和蓝，发现只要知道红色的地域是哪些，蓝色的地域也就确定了。

我们从左上角开始选红色区域。

由于题目的某个奇奇怪怪的限制，我们不难发现红色区域和蓝色区域各自在行列上都是连续的。

我们分别假定红色区域包含最大值和包含最小值。

假定红色区域包含最大值时，我们从左上角逐行扫荡，每行的红色区域方格数不超过上一行的（不用考虑每行方格数不少于上一行的这种情况，因为还要旋转啊OvO）

只要这个方格与最大值的差不超过当前二分中点mid就选它，只要不符合就跳转到下一行。

无需证明，感性理解即可。

选中的红色区域的have值记为1，蓝色是0；

然后这样贪心完毕之后，根据每个方格的have值来判断贪心之后的状态是否符合题意。

红色区域包含最小值的情况也是类似的。

这样，这道题就可以A掉了。

具体可以看看我的程序（加了一点注释以便理解）。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<queue>
#include<map>
#define ll long long
#define rg register
#define db double
#define N 2017
using namespace std;
int a[N][N],n,m,minn,maxn; 
int tmp[N][N];
bool have[N][N];
inline int rd()
{
    int xaa=0,f=1;
    char ch=getchar();
    while(ch<'0'|ch>'9'){if(ch=='-') f*=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){xaa=(xaa<<3)+(xaa<<1)+ch-'0';ch=getchar();}
    return xaa*f;
}
inline int mam(int x,int y){return x>y?x:y;}
inline int mim(int x,int y){return x<y?x:y;}
void xzz()//旋转
{
    memset(tmp,0,sizeof tmp);
    for(rg int i=1;i<=n;i++){
        for(rg int j=1;j<=m;j++){
            tmp[i][j]=a[i][j];
        }
    }
    memset(a,0,sizeof a);
    for(rg int i=1;i<=m;i++){
        for(rg int j=1;j<=n;j++){
            a[i][j]=tmp[n-j+1][i];
        }
    }
    swap(n,m);
}
bool find(int x)//看贪心之后的状态是否符合
{
    int minl=0x3f3f3f3f,minr=0x3f3f3f3f,maxl=0,maxr=0;
    for(rg int i=1;i<=n;i++){
        for(rg int j=1;j<=m;j++){
            int t1=a[i][j];
            if(have[i][j]){
                minl=mim(minl,t1),maxl=mam(maxl,t1);
            }
            else {
                minr=mim(minr,t1),maxr=mam(maxr,t1);
            }
        }
    }
    if(maxl-minl<=x&&maxr-minr<=x) return 1;
    return 0;
}
bool work(int x)//check
{
    memset(have,0,sizeof have);
    int now=m;
    for(rg int i=1;i<=n;i++){
        for(rg int j=1;j<=m;j++){
            if(j>now) break;
            if(x+a[i][j]>=maxn) have[i][j]=1;
            else {now=j-1;break;}
        }
    }
    if(find(x)) return 1;
    memset(have,0,sizeof have);
    now=m;
    for(rg int i=1;i<=n;i++){
        for(rg int j=1;j<=m;j++){
            if(j>now)break;
            if(a[i][j]<=minn+x)have[i][j]=1;
            else {now=j-1;break;}
        }
    }
    if(find(x)) return 1;
    return 0;
}
int ef()//二分
{
    minn=0x3f3f3f3f,maxn=0;
    for(rg int i=1;i<=n;i++){
        for(rg int j=1;j<=m;j++){
            maxn=mam(maxn,a[i][j]);
            minn=mim(minn,a[i][j]);
        }
    }
    int l=0,r=maxn-minn,tans;
    while(l<=r)
    {
        int mid=l+r>>1;
        if(work(mid)){
            tans=mid;
            r=mid-1;
        }
        else l=mid+1;
    }
    return tans;
}
int main(void)
{
    cin>>n>>m;
    int ans=0x3f3f3f3f;
    for(rg int i=1;i<=n;i++){
        for(rg int j=1;j<=m;j++){
            a[i][j]=rd();
        }
    }
    ans=mim(ans,ef());
    xzz();
    ans=mim(ans,ef());
    xzz();
    ans=mim(ans,ef());
    xzz();
    ans=mim(ans,ef());
    cout<<ans<<endl;
    return 0;
}

```

---

## 作者：半仙胡小桃 (赞：4)

[传送门](https://www.luogu.org/problem/show?pid=3933)

不能转两次弯说明什么？

把图分成两个部分其实就相当于画一条单调的线。

如下图![这里写图片描述](http://images2017.cnblogs.com/blog/997624/201710/997624-20171021200728740-1992445521.png)

如果我们分蓝色的，以上面那一行为最大，那么下面的蓝色的终点是不可以超过上面那行的。

但是蓝色既可以左右延伸，也可以上下延伸。

可以从4个方向出发。

但是写4个分色有些麻烦。

我们可以用从左开始，向右延伸的方法，然后分别把图选择90,180,270.

就可以得到所有的情况了。

得到了图该怎样做？

二分答案。

我们首先得到最大值与最小值。

答案肯定小于最大值-最小值。

假定最大值在蓝色，最小值在红色。

二分一个答案，用最大值-元素>=ans为条件去构造蓝色块。

然后再去判断红色块中的元素是不是都满足条件即可。


```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int inf=1e9;
int n,m,a[2010][2010],ans=inf,maxx=-inf,minx=inf;
void turn90()//对调
{
    for(int i=1;i<=n;i++)
     for(int j=1;j<=m/2;j++)
      swap(a[i][j],a[i][m-j+1]);
}
void turnd()//选择
{
    for(int i=1;i<=n/2;i++)
     for(int j=1;j<=m;j++)
      swap(a[i][j],a[n-i+1][j]);
}
bool check(int mid)
{
    int p=m+1;
    for(int i=1;i<=n;i++)
    {
        int t=0;
        for(int j=1;j<=min(p,m);j++)
         if(maxx-a[i][j]<=mid) t=max(t,j);//找i行的最大延伸
         else break;
        p=t;
        for(int j=t+1;j<=m;j++)
         if(a[i][j]-minx>mid) return 0;//满不满足条件
    }
    return 1;
}
int get_ans()
{
    int l=0,r=maxx-minx+1;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(check(mid)) r=mid-1;
        else l=mid+1;
    }
    return l;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
     for(int j=1;j<=m;j++)
      scanf("%d",&a[i][j]),maxx=max(a[i][j],maxx),minx=min(a[i][j],minx);
    ans=min(ans,get_ans());
    turn90();
    ans=min(ans,get_ans());
    turnd();
    ans=min(ans,get_ans());
    turn90();
    ans=min(ans,get_ans());//枚举4种情况
    printf("%d\n",ans);
}
```

---

## 作者：Atri_Lobato (赞：3)

## 前言
这个题解将提供一个不用二分的贪心方法。~~为可爱的珂朵莉贡献一份力量！！！珂朵莉真的太可爱了喵！！！~~
## 题目大意
不能出现需要拐两次弯的情况，也就是说形如：

``` cpp
a b a
a a a
```
的“凹”字型结构不能出现，同时“凸”字型结构会导致另外一块的“凹”字型结构。借用另一篇题解的概括性结论：

**分开两块的分割线为单调的阶梯状的线**

然后所求答案的意思很简单就不解释了。

## 解决策略

考虑贪心。

自认为思路会比较自然，但是会遇上许多细节问题，实现也会比较繁琐。

### 核心思路

从单个角落的单个点作为其中一块开始扩张。每次扩张会吞掉剩下部分的最值。因为**只有改变最值的分布才能影响答案**。

又因为**同时吞噬最大值与最小值等价于获得了另外一块的极差，不影响答案，没有意义**，所以在每一轮扩张时，统一吞噬最大或最小值即可。

另外，要镜像再吞噬一遍，原因不多赘述。

以上贪心策略便保证了能不漏地遍历所有有效解，同时吞噬过程中必然以整个覆盖角落的矩形进行吞噬，最坏吞噬 $nm$ 次，保证每次吞噬操作的维护为 $O(1)$ 即可。

如果文字表述不清，有如下图解：

``` cpp
//1、0分别表示两块，2表示最值位置。

Before:
1 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 2 0 0 0
0 0 0 0 0 0

After：
1 1 1 0 0 0
1 1 1 0 2 0
1 1 1 0 0 0
1 1 1 0 0 0
0 0 0 0 0 0

After：
1 1 1 1 1 0
1 1 1 1 1 0
1 1 1 0 0 0
1 1 1 0 0 0
0 0 0 0 0 0
```

### 实现细节
根据上述，我们需要 $O(1)$ 查询未被吞噬的部分的最值的位置。**因此做一个 $O(nm\log nm )$ 排序预处理出所有未被排序元素**。


为知道某点是否已被吞噬，**用一个数组表示覆盖记录**。

``` cpp
1 1 1 1 0
1 1 1 0 0
1 0 0 0 0
1 0 0 0 0
可记录为：
4
3
1
1
表示每一行被吞噬了几列。
```

由于分割线的单调性，这个数组一定是**单调不增**的。这时我们进行标记的时候只需要从下往上枚举更新标记，直到第一个大于等于的就可以停止了（因为**重复覆盖没有意义**）。分析复杂度总的为 $O(mn)$ 均摊下来就是 $O(1)$，可以接受。

每次更新答案需要维护吞噬、未被吞噬的最值。对于吞噬的，做一个二维前缀和预处理；对于未被吞噬的，从排序数组的最小、最大合法元素可获得。

进一步以及其他细节在代码中给出。

## 代码

``` cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m;
int a[2005][2005];//原始数据 
int tmp[2005][2005];//镜像暂用 
int pre1[2005][2005];//最大值前缀和 
int pre2[2005][2005];//最小值前缀和 
int pf,pb;//排序数组的前、后指针
          //指向最小、最大的合法元素 
int ans; 
int r1,r2;//吞噬块、被吞噬块的极差 
int minn,maxn;//吞噬块最值 
int used[2005];//标记数组 
struct P
{
	int x,y;
	int v;
}b[4000006];//排序数组 
bool cmp(P a,P b)
{
	return a.v<b.v;
}
void usel(int x,int y)//更新标记数组 
{
	int i=y;
	while(i>=1)
	{
		if(used[i]<=x) 
		{
			used[i]=x;
		}
		else
		break;
		i--;
	}
}
void update()
{
	//弹出不合法元素,即被标记的元素 
	while(b[pf].x<=used[b[pf].y]&&pf<=pb) 
	pf++;
	while(b[pb].x<=used[b[pb].y]&&pf<=pb)
	pb--;
}
void solve1()
{
	pf=1,pb=0;
	memset(pre1,0,sizeof(pre1));
	memset(pre2,127,sizeof(pre2));
	for(int i=1;i<=n;i++)
	{
		for(int q=1;q<=m;q++)
		{
			pre1[i][q]=max(a[i][q],max(pre1[i-1][q],pre1[i][q-1]));
			pre2[i][q]=min(a[i][q],min(pre2[i-1][q],pre2[i][q-1]));
			if(!(i==1&&q==1))//（1,1）属于吞噬块 
			{
				pb++;
				b[pb].v=a[i][q];
				b[pb].y=i;
				b[pb].x=q;
			}
		}
	}
	sort(b+pf,b+pb+1,cmp);
	memset(used,0,sizeof(used));
	used[1]=1;
	bool flag=1;
	update();
	P maxp=b[pb],minp=b[pf]; 
	maxn=minn=a[1][1];
	r2=maxp.v-minp.v;
	r1=maxn-minn;
	ans=min(ans,max(r1,r2));
	while(flag)//吞小点
	{
		flag=0;
		if(!(maxp.x<=minp.x&&maxp.y<=minp.y))//保证吞噬最小值的同时不能吞噬最大值 
		{
			flag=1;
			usel(minp.x,minp.y);
			maxn=max(maxn,pre1[minp.y][minp.x]);
			minn=min(minn,pre2[minp.y][minp.x]);
		}
		update();
		maxp=b[pb],minp=b[pf];
		r2=maxp.v-minp.v;
		r1=maxn-minn;
		ans=min(ans,max(r1,r2));
	}
	pf=1;
	memset(used,0,sizeof(used));
	used[1]=1;
	flag=1;
	update();
	maxp=b[pb],minp=b[pf];
	maxn=minn=a[1][1];
	r2=maxp.v-minp.v;
	r1=maxn-minn;
	ans=min(ans,max(r1,r2));
	while(flag)//吞大点，同理其上 
	{
		flag=0;
		if(!(maxp.x>=minp.x&&maxp.y>=minp.y))
		{
			flag=1;
			usel(maxp.x,maxp.y);
			maxn=max(maxn,pre1[maxp.y][maxp.x]);
			minn=min(minn,pre2[maxp.y][maxp.x]);
		}
		update();
		maxp=b[pb],minp=b[pf];
		r2=maxp.v-minp.v;
		r1=maxn-minn;
		ans=min(ans,max(r1,r2));
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	ans=0x3f3f3f3f;
	solve1();
	for(int i=1;i<=n;i++)//镜像 
	{
		for(int q=1;q<=m;q++)
		{
			tmp[i][q]=a[i][q];
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int q=1;q<=m;q++)
		{
			a[i][q]=tmp[n+1-i][q];
		}
	}
	solve1();
	printf("%d",ans);
	return 0;
}
```

## 结语
这么个方法其实复杂度只有 $O(nm\log nm)$，瓶颈在排序。理论上是比二分的 $\log V$ 更优的，但是蒟蒻猫猫我猫傻常数大，实现繁琐，所以跑了 $3s$ QAQ。希望路过大佬能优化我的算法 awa。

那么本篇题解就到这里了，有解释的不清楚的请多多指教哦。**喵哇~~**

---

## 作者：_Diu_ (赞：3)

### 题目大意

给处一个矩阵，你能把它分成两个部分，分割线要是阶梯状，求使得两个部分极差（最大值减去最小值）的最大值的最小值。

### 二分答案

看到最大值最小，想到二分答案。

~~合情合理~~。

我们考虑二分一个答案 $x$，如何判断这个 $x$ 合不合法。

首先如果我们想要这个值尽量小，我们最好吧全局最大值和最小值分开。

设最大值为 $mx$，最小值为 $mn$。

假设我们考虑这样的分法：

![](https://cdn.luogu.com.cn/upload/image_hosting/yh6dxcud.png)

并且我们先把左上角的地方框出来，然后看看右下角的合不合法。

那么，对于每个左上角的数 $a$，需要满足 $a\ge mx-x$。

并且为了保证分割线是阶梯状的，我们把每列的边界都提前赋成前一列的。

我们应该尽量框出最大的一块，然后判断右下角是否全部满足条件 $a\le mn+x$。

每次判断 $O(n^2)$，二分 $O(\log a)$。

因为最大值不一定在左上角，也有可能是右上角，右下角，左下角，

我们可以选择每一边都写一次，也可以每一次旋转一下矩阵，然后继续统计。

~~最多也就常数乘以 $4$~~。

总时间复杂度 $O(n^2\log a)$，能过。

### code

顺便提一句，我是二分完再旋转，也可以再每次 `check` 的时候旋转，但是好像预处理出旋转矩阵更优。

~~因为我懒，所以就不管了~~。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2010;
int n,m,a[N][N],b[N][N],mx,mn=1e9+7,ans;
void change(){
	swap(a,b);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[j][i]=b[n-i+1][j];
		}
	}
	swap(n,m);
}
bool check(int x){
	for(int j=1,r=n;j<=m;j++){
		for(int i=1;i<=r;i++)if(a[i][j]<mx-x)r=i-1;
		for(int i=r+1;i<=n;i++)if(a[i][j]>mn+x)return false;
	}
	return true;
}
void work(){
	int l=-1,r=ans+1;
	while(l+1<r){
		int mid=l+r>>1;
		if(check(mid))r=mid;
		else l=mid;
	}
	ans=min(ans,r);
}
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&a[i][j]);
			mx=max(mx,a[i][j]);
			mn=min(mn,a[i][j]);
		}
	}
	ans=mx-mn;
	work();change();
	work();change();
	work();change();
	work();
	printf("%d\n",ans);
}
```

---

## 作者：Shiota_Nagisa (赞：2)

第一篇珂学相关题解~~

首先读题，观察到所谓拐一个转弯，意味着对于一个矩阵的每一行，定是一段从一开始的连续区间属于A，且每一行属于A的区间长度不升。对于矩阵的四个方向，旋转后当做四个矩阵处理即可。

然后看到“最大值最小”，考虑二分，将问题转化为判定性问题。我们不妨钦定最大值在A里，最小值在B里，按意模拟判定就可以了。时间复杂度 $4 \times n \times m \times \log Maxx$ ，空间复杂度 $4 \times n \times m$。

顺便给一下旋转公式 $a[k][j][n-i+1]=a[k-1][i][j]$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2011,inf=1e9;//这题开long long爆空间
int n,m,a[5][N][N],now,willem,chtholly;//小心数组越界
int ans;	
bool goa[N][N]; 
bool check(int x){	
	int fa=m; 
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) goa[i][j]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=fa;j++){
			if(x+a[now][i][j]>=willem) goa[i][j]=1;
			else{
				fa=j-1;
				break;
			}
		}
	}
	for(int i=n;i>0;i--){
		for(int j=m;j>0;j--){
			if(!goa[i][j]&&a[now][i][j]-x>chtholly) return 0;
			else if(goa[i][j]) break;
		}
	}
	return 1;
}
int twofen(){
	int l=0,r=willem-chtholly,mid,ret=inf;
	while(l<=r){
		mid=(l+r)/2;
		if(check(mid)){
			ret=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	return ret;
}
signed main(){
	cin>>n>>m;
	chtholly=inf;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[0][i][j];
			willem=max(a[0][i][j],willem);
			chtholly=min(a[0][i][j],chtholly);
		}
	}
	ans=willem-chtholly;
	for(int T=0;T<4;T++){
		ans=min(ans,twofen());
		now++;
		for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)	a[now][j][n-i+1]=a[now-1][i][j];
		swap(n,m);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Peter0701 (赞：2)

感觉前面的题解要不太简略，要不有冗余，我决定写一个大小适中的小清新题解！

给定 $H \times W$ 的网格，每个小格（ $1 \times 1$ 的网格）都有一个权值。

现在要将其分为两部分，一个为阶梯型（从上往下每行长度单调递增）、另一个为倒阶梯型（从下往上每行长度单调递增）。请合理地划分这个网格使得两边极差（该部分最大值 $-$ 最小值）较大的一个最小。输出较大的极差。

注意关键词。“较大的一个最小” $\rightarrow$ “最大值最小”！

二分答案，出来吧！

显然，我们二分那个较大的极差，二分左边界是 $0$ ，右边界是全局最大值 $maxn$ 与全局最小值 $minn$ 的差。那么 $check()$ 函数怎么写呢？

假设当前二分到的答案是 $mid$ 。显然我们可以钦定全局最大值在左边一部分，全局最小值在右边一部分。那么将所有符合 $mid$ 极差（即 $maxn-x \leqslant mid$ ）的数 $x$ 全都分到左边，注意保留倒阶梯型（左边部分每行的长度依次递减）；而右边的数 $x$ 只要不符合 $mid$ 极差（即 $x-minn \leqslant mid$ ）答案就显然不成立。

当然，钦定全局最大值在左边一部分，全局最小值在右边一部分的答案不一定是最优的。我们还应当将原图 $90 \degree $ 旋转 $3$ 次分别按上面的步骤解答一次，更新答案。

整个过程就是这样，如果还没明白或者觉得需要证明的，评论区见！感谢您的耐心阅读！

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int ret=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		ret=(ret<<1)+(ret<<3)+ch-'0';
		ch=getchar();
	}
	return ret*f;
}
const int inf=1<<30;
int h,w,a[2005][2005],minn=inf,maxn=-inf,ans=inf;
inline bool ck(int mid)
{
	int f=w+1;
	for(register int i=1;i<=h;i++)
	{
		int t=0;
		for(register int j=1;j<=min(f,w);j++)
		{
			if(maxn-a[i][j]<=mid)
				t=max(t,j);
			else
				break;
		}
		f=t;
		for(register int j=t+1;j<=w;j++)
			if(a[i][j]-minn>mid)
				return 0;
	}
	return 1;
}
inline int work()
{
	int l=0,r=maxn-minn+1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(ck(mid))
			r=mid-1;
		else
			l=mid+1;
	}
	return l;
}
inline void turn1()
{
	for(register int i=1;i<=h;i++)
		for(register int j=1;j<=w/2;j++)
			swap(a[i][j],a[i][w-j+1]);
}
inline void turn2()
{
	for(register int i=1;i<=h/2;i++)
		for(register int j=1;j<=w;j++)
			swap(a[i][j],a[h-i+1][j]);
}
int main()
{
	h=read();
	w=read();
	for(register int i=1;i<=h;i++)
	{
		for(register int j=1;j<=w;j++)
		{
			a[i][j]=read();
			maxn=max(maxn,a[i][j]);
			minn=min(minn,a[i][j]);
		}
	}
	ans=min(ans,work());
	turn1();
	ans=min(ans,work());
	turn2();
	ans=min(ans,work());
	turn1();
	ans=min(ans,work());
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：XL4453 (赞：1)

     至少，我也希望自己不用消失，也想让别人记住。我也想留下羁绊啊。
     


------------
解题思路：

首先是题目中:

	每个部分内部的方块之间，可以通过上下左右相互到达，而且每个内部的方块之间互相到达，最多允许拐一次弯。
    
这一段话的理解。其实仅允许拐一次弯也就意味着不存在有一个异色块挡住的情况，也就是：

	AA
    BA
    AA

那么上一段其实不就是说这是一个每一种颜色在每一行或每一列上单调增或减嘛。

其实也就是“阶梯型”。

回到原题，发现答案的大小是单调的，即所有更大的答案一定“兼容”所有小的答案，在小一点的答案里可以找到满足的一组解一定适用于更大的一个，这就意味着可以使用二分答案的方法来解题。

然后就考虑二分极差，然后利用贪心的思想进行判断。也就是在优先保证满足最大差值小于 $mid$ 的前提下使得阶梯尽可能向右延伸，挺显然的，不多说。

------------
代码：

```cpp
#include<cstdio>
using namespace std;
int map[2005][2005],n,m,maxn=-2147483647,minx=2147483647,ans=2147483647;
int max(int a,int b){if(a>b)return a;return b;}
int min(int a,int b){if(a<b)return a;return b;}
void swap(int &x,int &y){x^=y;y^=x;x^=y;}
void t1(){
	for(int i=1;i<=n/2;i++)
	for(int j=1;j<=m;j++)
	swap(map[i][j],map[n-i+1][j]);
}
void t2(){
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m/2;j++)
	swap(map[i][j],map[i][m-j+1]);
}
bool check(int mid){
	int cut=m+1,now;
	for(int i=1;i<=n;i++){
		for(now=1;now<=min(m,cut);now++)
		if(maxn-map[i][now]>mid)break;
		
		cut=min(cut,now);
		
		for(;now<=m;now++)
		if(map[i][now]-minx>mid)return 0;
	}
	return 1;
}
int work(){
	int l=0,r=maxn-minx+1,mid;//二分差值
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid))r=mid-1;
		else l=mid+1;
	} 
	return l;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		scanf("%d",&map[i][j]);
		maxn=max(maxn,map[i][j]);
		minx=min(minx,map[i][j]);
	}
	ans=min(ans,work());t2();
	ans=min(ans,work());t1();
	ans=min(ans,work());t2();
	ans=min(ans,work());
	printf("%d",ans);
	return 0;
}
```


---

## 作者：_Flame_ (赞：0)

### solution

首先，我们发现最大值最小值一定不会在同一个块里，我们钦定其中的最大值在某一个角上。

考虑二分答案，对于每一个答案，把最大值分到一个角上，最小值分到另一个块里，判断是否合法。

对于每一个和最大值在同一块里的数，我们要保证 $mx-mid\le a_{i,j}$，我们在满足条件的情况下框出最大的一块，判断最小值所在的一块是否合法即可。

我们可以找到最大值的位置，再进行二分，但这样略显麻烦，所以我们把矩阵旋转 $4$ 次，把所有情况都做一遍即可。

### code

```cpp
int n,m;

int a[maxn][maxn],mn=inf,mx=-inf;

int b[maxn][maxn];

bool check(int x){
	for(int i=1,r=n;i<=m;i++){
		for(int j=1;j<=r;j++){
			if(a[j][i]<mx-x){
				r=j-1;
			}	
		}
		for(int j=r+1;j<=n;j++){
			if(a[j][i]>mn+x){
				return 0;
			}
		}
	}
	return 1;
}

void solve(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=read();
			mn=min(mn,a[i][j]);
			mx=max(mx,a[i][j]);
		}
	}
	int ans=mx-mn;
	int l=0,r=mx-mn,res=r;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)){
			r=mid-1;
			res=mid;
		}
		else{
			l=mid+1;
		}
	}
	ans=min(ans,res);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			swap(b[j][i],a[n-i+1][j]);
		}
	}
	swap(a,b);
	swap(n,m);
	l=0,r=mx-mn,res=r;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)){
			r=mid-1;
			res=mid;
		}
		else{
			l=mid+1;
		}
	}
	ans=min(ans,res);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			swap(b[j][i],a[n-i+1][j]);
		}
	}
	swap(a,b);
	swap(n,m);
	l=0,r=mx-mn,res=r;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)){
			r=mid-1;
			res=mid;
		}
		else{
			l=mid+1;
		}
	}
	ans=min(ans,res);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			swap(b[j][i],a[n-i+1][j]);
		}
	}
	swap(a,b);
	swap(n,m);
	l=0,r=mx-mn,res=r;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)){
			r=mid-1;
			res=mid;
		}
		else{
			l=mid+1;
		}
	}
	ans=min(ans,res);
	write(ans);
	puts("");
	return ;
}
```

---

## 作者：s4CRIF1CbUbbL3AtIAly (赞：0)

题意：用一条阶梯状的线将矩阵分成两部分，使得两部分内部的极差的最大值最小。

首先看到最大值最小考虑二分答案。假设现在我们要判断是否能划分出两部分极差都不超过 $k$ 的方案。

于是随便选择一个最小值 $\min$，将所有超过 $\min+k$ 的点都找出来。

对于这样一个点集，假设把它们都划进 B 中。显然 A 中不会出现这些点，所以无论如何 A 都是合法的，因此我们只需要让 B 尽量合法。

容易发现 B 尽量小的时候会更优，因此我们肯定希望分割线尽量贴在点集的边缘。

![pFjprB8.png](https://s21.ax1x.com/2024/04/12/pFjprB8.png)

容易发现实际上只有左上（蓝）、右上（绿）、左下（红）、右下（黄）四种可能的分割线最优。图中故意把一些线移到了方格内部，是为了避免线段遮挡。

于是这里指考虑蓝色线，另外三种同理。

容易发现，这些点都是最靠左靠上的。于是考虑从左往右扫描，记录一下当前这一列的分界线位置。对于每一列从上到下逐个计算，如果发现了一个位置属于点集就把分界线上移。

这样我们就分出了每个位置属于 A 还是 B，就可以 $O(nm)$ 再扫描一遍整个判断是否合法。

实际上我们根本不需要考虑 $\min$ 的位置，因为只要我们把四种情况都判断一遍即可。

时间复杂度 $O(4nm\log V)$。

```cpp
int n,m,mnx,mny;
vector<vector<int>>a;
bool check(int k){
	int mx1=-INF,mn1=INF,mx2=-INF,mn2=INF;// 分别表示集合 A 和 B 的两个最值
	for(int j=1,cur=n;j<=m;j++){
		for(int i=1;i<=cur;i++)if(a[i][j]>a[mnx][mny]+k)cur=i-1;// 上移分界线
		else mx1=max(mx1,a[i][j]),mn1=min(mn1,a[i][j]);
		for(int i=cur+1;i<=n;i++)mx2=max(mx2,a[i][j]),mn2=min(mn2,a[i][j]);
	}
	if(mx1-mn1<=k&&mx2-mn2<=k)return 1;// 判断是否合法
	mx1=-INF,mn1=INF,mx2=-INF,mn2=INF;// 接下来三种同理
	for(int j=m,cur=1;j;j--){
		for(int i=n;i>=cur;i--)if(a[i][j]>a[mnx][mny]+k)cur=i+1;
		else mx1=max(mx1,a[i][j]),mn1=min(mn1,a[i][j]);
		for(int i=cur-1;i;i--)mx2=max(mx2,a[i][j]),mn2=min(mn2,a[i][j]);
	}
	if(mx1-mn1<=k&&mx2-mn2<=k)return 1;
	mx1=-INF,mn1=INF,mx2=-INF,mn2=INF;
	for(int j=1,cur=1;j<=m;j++){
		for(int i=n;i>=cur;i--)if(a[i][j]>a[mnx][mny]+k)cur=i+1;
		else mx1=max(mx1,a[i][j]),mn1=min(mn1,a[i][j]);
		for(int i=cur-1;i;i--)mx2=max(mx2,a[i][j]),mn2=min(mn2,a[i][j]);
	}
	if(mx1-mn1<=k&&mx2-mn2<=k)return 1;
	mx1=-INF,mn1=INF,mx2=-INF,mn2=INF;
	for(int j=m,cur=n;j;j--){
		for(int i=1;i<=cur;i++)if(a[i][j]>a[mnx][mny]+k)cur=i-1;
		else mx1=max(mx1,a[i][j]),mn1=min(mn1,a[i][j]);
		for(int i=cur+1;i<=n;i++)mx2=max(mx2,a[i][j]),mn2=min(mn2,a[i][j]);
	}
	if(mx1-mn1<=k&&mx2-mn2<=k)return 1;
	return 0;// 如果都不合法就是 0
}

void __INIT__(){ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
void __SOLVE__(int _case){
	cin>>n>>m;
	a.resize(n+1);
	a[0].resize(1),a[0][0]=INF;
	for(int i=1;i<=n;i++){
		a[i].resize(m+1);
		for(int j=1;j<=m;j++)cin>>a[i][j],a[i][j]<a[mnx][mny]&&(mnx=i,mny=j);// 记录最小值
	}
	ll l=0,r=2e9,mid,ans=-1;// 记得开 ll
	while(l<=r){
		mid=l+r>>1;
		if(check(mid))r=mid-1,ans=mid;
		else l=mid+1;
	}
	cout<<ans<<"\n";
}
```

---

