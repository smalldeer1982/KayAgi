# [POI 2006] TET-Tetris 3D

## 题目描述

最近，有人发明了一种三维版的俄罗斯方块。和二维版本类似，一些立方体按照一定的顺序掉落，直到碰到别的方块或是地面才会停止掉落。立方体停止掉落后会一直保持掉落时的位置，直到游戏结束。

你的朋友决定以这个新版本的俄罗斯方块为背景，出一道题。给出每个立方体的掉落顺序和其掉落的轨迹，在所有方块完成掉落后求出最高方块的高度。在这个游戏中，方块均垂直下落，且方块不会旋转或翻转。为了方便描述，我们会建立一个空间直角坐标系，该坐标系的原点为地面的一角，并且坐标轴与地面边缘平行。

现在轮到你解决这个问题了。

## 说明/提示

$1 \leq N \leq 20\,000$，$1 \leq D,S \leq 1\,000$，$d_i,s_i \geq 1$，$1 \leq w_i \leq 100\,000$，$0 \leq x_i,d_i+x_i \leq D$，$0 \leq y_i,s_i+y_i \leq S$。

## 样例 #1

### 输入

```
7 5 4
4 3 2 0 0
3 3 1 3 0
7 1 2 0 3
2 3 3 2 2```

### 输出

```
6```

# 题解

## 作者：ButterflyDew (赞：22)

来[露迭月](https://www.cnblogs.com/ppprseter/p/9582277.html)的博客阅读获取船新体验


注意到这个矩形修改矩形查询最大值的所有位置上的值是非减的，否则我们没法使用二维线段树配合标记永久化完成。

------------
先考虑一维的情况，区间求最大值，区间赋值最大值加上某个正数

在线段树中维护一个$mx$和一个$tag$，分别表示区间最大值和修改后的值

对于修改操作，对路径上的每一个节点都用待修改的值尝试更新$mx$数组，因为这个节点一定包含这个小区间，所以可以更新

但$tag$操作只有区间完全被覆盖时才更新，不下传一直呆在这个区间

对于查询操作，对路径上的每一个节点都尝试使用$tag$数组更新答案，因为tag是对整个区间打的，所以子区间可以直接使用

在区间完全被覆盖的情况下，我们才可以用$mx$数组更新答案

这就是所谓的标记永久化

为什么要这样，因为第二维的树是没法使用子节点快速更新答案的，也不好下传

------------
再考虑第二维的情况，第二维的线段树每一个节点都放着两颗颗第一维线段树

一颗代表$mx$树，一颗代表$tag$树

然后剩下的就和第一维的情况非常相似了

------------
**Code:**
```cpp
#include <cstdio>
const int N=2050;
int n,m;
int max(int x,int y){return x>y?x:y;}
#define ls id<<1
#define rs id<<1|1
struct segy
{
    int mx[N],tag[N];
    void change(int id,int l,int r,int L,int R,int val)
    {
        mx[id]=max(mx[id],val);
        if(l==L&&r==R)
        {
            tag[id]=max(tag[id],val);
            return;
        }
        int Mid=L+R>>1;
        if(r<=Mid) change(ls,l,r,L,Mid,val);
        else if(l>Mid) change(rs,l,r,Mid+1,R,val);
        else change(ls,l,Mid,L,Mid,val),change(rs,Mid+1,r,Mid+1,R,val);
    }
    int query(int id,int l,int r,int L,int R)
    {
        if(l==L&&r==R)
            return mx[id];
        int ans=tag[id],Mid=L+R>>1;
        if(r<=Mid) ans=max(ans,query(ls,l,r,L,Mid));
        else if(l>Mid) ans=max(ans,query(rs,l,r,Mid+1,R));
        else ans=max(ans,max(query(ls,l,Mid,L,Mid),query(rs,Mid+1,r,Mid+1,R)));
        return ans;
    }
};
struct segx
{
    segy mx[N],tag[N];
    void change(int id,int l,int r,int L,int R,int ll,int rr,int val)
    {
        mx[id].change(1,ll,rr,1,m,val);
        if(l==L&&r==R)
        {
            tag[id].change(1,ll,rr,1,m,val);
            return;
        }
        int Mid=L+R>>1;
        if(r<=Mid) change(ls,l,r,L,Mid,ll,rr,val);
        else if(l>Mid) change(rs,l,r,Mid+1,R,ll,rr,val);
        else change(ls,l,Mid,L,Mid,ll,rr,val),change(rs,Mid+1,r,Mid+1,R,ll,rr,val);
    }
    int query(int id,int l,int r,int L,int R,int ll,int rr)
    {
        if(l==L&&r==R)
            return mx[id].query(1,ll,rr,1,m);
        int ans=tag[id].query(1,ll,rr,1,m),Mid=L+R>>1;
        if(r<=Mid) ans=max(ans,query(ls,l,r,L,Mid,ll,rr));
        else if(l>Mid) ans=max(ans,query(rs,l,r,Mid+1,R,ll,rr));
        else ans=max(ans,max(query(ls,l,Mid,L,Mid,ll,rr),query(rs,Mid+1,r,Mid+1,R,ll,rr)));
        return ans;
    }
}t;
int main()
{
    int d,s,h,x,y,k;
    scanf("%d%d%d",&n,&m,&k);
    while(k--)
    {
        scanf("%d%d%d%d%d",&d,&s,&h,&x,&y),++x,++y;
        t.change(1,x,x+d-1,1,n,y,y+s-1,t.query(1,x,x+d-1,1,n,y,y+s-1)+h);
    }
    printf("%d\n",t.query(1,1,n,1,n,1,m));
    return 0;
}

```


---

## 作者：Methylene_Blue (赞：20)

# 这是一篇二维线段树的题解(简介)
首先题意就不分析了,无非是二维区间修改,二维区间查询

前置知识:

1.一维线段树(因为接下来要进行类比讲解)

2.线段树染色操作(对应题目里的修改)~~废话真多~~

---

## 一.什么是二维线段树(四叉树)
一维的线段树也叫区间树(二叉树),顾名思义也就是一个结点维护一个区间,像是长成这样

![](https://cdn.luogu.com.cn/upload/pic/66651.png)

那二维自然是加一个维度,也就是说我们每个结点维护一个矩阵,它长成这个样子(实在画不好我就去网上找了一张图)
![](https://cdn.luogu.com.cn/upload/pic/66652.png)

#### 也就是每个结点有四个元素$[l,r,u,d]$~~left,right,up,down~~
#### 分别表示这个结点维护的是横向$[l,r]$和纵向$[u,d]$这一段矩阵的信息
#### 比如上图最大的那个矩阵就是$[1,4,1,3]$,右边紫灰一起的小结点就是$[3,4,3,3]$

## 二.二维线段树的各个儿子
由上图我们能看出来,如果两个维度分别取个一半的话,那我们有些情况下是四个儿子,有些情况是两个,那么具体应该怎么去寻找根节点的每个儿子呢

一维的线段树里面估计很多人都是习惯最上面一个根节点从1编号,这样正好符合二叉树的性质

但是二维的里面我们要改一改,对于每个结点如果最上面的根节点从0开始编号,就会正好满足一个性质

即:
```cpp
#define son_left_up ((o<<2)+1)
#define son_right_up ((o<<2)+2)
#define son_left_down ((o<<2)+3)
#define son_right_down ((o<<2)+4)
```
~~请不要吐槽我绘图丑QAQ~~
![](https://cdn.luogu.com.cn/upload/pic/66656.png)

---

## 二~~点五~~.讲解下面代码里的参数含义 
1. $honoka(a,b)$即返回$a,b$的最大值

2. $l,r,u,d$为每个结点维护的区间信息

3. 左上的儿子(一号儿子)是$slu$,右上为$sru$,左下为$sld$,右下为$srd$

4. $ql,qr,qu,qr$是查询的区间,即$query\_l,query\_r$

5. $midx,midy$分别为横向和纵向上的区间中点

---

## 三.建树操作(下面先贴代码再配合讲解)
### 此处是维护最大值的建树
```cpp
inline void buildtree(int l,int r,int u,int d,int o)
{
  tree[o].lazy=0;//初始化lazytag
  
  if(l==r && u==d)//递归到单个矩阵元素
  {
    tree[o].maxx=0;
    return;
  }
  int midx,midy;
  midx=(l+r)>>1;
  midy=(u+d)>>1;//求出两个维度上的中点
  
  buildtree(l,midx,u,midy,slu);
  tree[o].maxx=honoka(tree[o].maxx,tree[slu].maxx);//先递归左上角的儿子
  
  if(l!=r)//判断右上角的儿子是否存在
  {
    buildtree(midx+1,r,u,midy,sru);
    tree[o].maxx=honoka(tree[o].maxx,tree[sru].maxx);
  }
  
  if(u!=d)//左下角
  {
    buildtree(l,midx,midy+1,d,sld);
    tree[o].maxx=honoka(tree[o].maxx,tree[sld].maxx);
  }
  
  if(l!=r && u!=d)//右下角
  {
    buildtree(midx+1,r,midy+1,d,srd);
    tree[o].maxx=honoka(tree[o].maxx,tree[srd].maxx);
  }
  return;
}
```

刚开始和一维一样,只不过递归中止条件是两个维度的

然后就是和一维不太一样的切分区间

一维里面我们只需要一个方向切一半就好

二维则需要两个方向

然后对于一个结点就会被切成四块,左上角的儿子是一定会有的,所以先递归一次左上方

然后去判断右上角的儿子是否存在(即现在的矩阵是否是如下的样子)

![](https://cdn.luogu.com.cn/upload/pic/66665.png)

若不是这个样子$l!=r$就直接递归,如果是这样$l==r$那说明没有右上方的儿子

---

然后去判断左下角的儿子是否存在(即现在的矩阵是否是如下的样子)
![](https://cdn.luogu.com.cn/upload/pic/66667.png)

若不是这个样子$u!=d$就直接递归,如果是这样$u==d$那说明没有左下方的儿子

最后一个$l!=r$和$u!=d$判断的则是右下方的儿子

然后对于四个儿子的区间我们也用图来解释一下

![](https://cdn.luogu.com.cn/upload/pic/66668.png)

$slu [l,midx,u,midy]$

$sru [midx+1,r,u,midy]$

$sld [l,midx,midy+1,d]$

$srd [mix+1,r,midy+1,d]$

### 然后建树就完成了,这一段认真理解了下面就很方便了

---

## 四.pushdown函数(染色类的pushdown)
```cpp
inline void pushdown(int l,int r,int u,int d,int o)
{
  tree[slu].maxx=tree[o].lazy;
  tree[slu].lazy=tree[o].lazy;//slu
  
  if(l!=r)//sru
  {
    tree[sru].maxx=tree[o].lazy;
    tree[sru].lazy=tree[o].lazy;
  }
  
  if(o!=d)//sld
  {
    tree[sld].maxx=tree[o].lazy;
    tree[sld].lazy=tree[o].lazy;
  }
  
  if(l!=r && o!=d)//srd
  {
    tree[srd].maxx=tree[o].lazy;
    tree[srd].lazy=tree[o].lazy;
  }
  
  tree[o].lazy=0;
  return;
}
```
左上角的儿子直接下放,其他三个和建树一样判断,不做过多赘述

---

## 五.修改操作
```cpp
inline void update(int ql,int qr,int qu,int qd,int l,int r,int u,int d,int o,int add)
{
  if(l>=ql && r<=qr && u>=qu && d<=qd)
  {
    tree[o].maxx=add;
    tree[o].lazy=add;
    return;
  }
  pushdown(l,r,u,d,o);
    
  int midx,midy;
  midx=(l+r)>>1;
  midy=(u+d)>>1;
    
  if(ql<=midx && qu<=midy)//左上角
  {
    update(ql,qr,qu,qd,l,midx,u,midy,slu,add);
    tree[o].maxx=honoka(tree[slu].maxx,tree[o].maxx);
  }
    
  if(qr>midx && qu<=midy && l!=r)//右上角
  {
    update(ql,qr,qu,qd,midx+1,r,u,midy,sru,add);
    tree[o].maxx=honoka(tree[sru].maxx,tree[o].maxx);
  }
    
  if(ql<=midx && qd>midy && u!=d)//左下角
  {
    update(ql,qr,qu,qd,l,midx,midy+1,d,sld,add);
    tree[o].maxx=honoka(tree[sld].maxx,tree[o].maxx);
  }
    
  if(qr>midx && qd>midy && l!=r && o!=d)//右下角
  {
    update(ql,qr,qu,qd,midx+1,r,midy+1,d,srd,add);
    tree[o].maxx=honoka(tree[srd].maxx,tree[o].maxx);
  }
  return;
}
```
一维的线段树里面区间被完全包括的情况是$l>=ql$且$r<=qr$

那二维的就是两个维度上面包括就行了$l>=ql,r<=qr,u>=qu,d<=qd$

然后就是递归子树

首先先看最后的$l,r,u,d$的判断,那是判断子树是否存在的

这个时候会存在一个问题就是比如竖条的矩阵$l==r$,这个时候$midx+1$已经超过了$r$的范围

但是没有影响啊,因为在子树判断里面这种子矩阵没有右上角的儿子,他会被ban掉的

然后四个方向类比一维去递归修改即可

比如第一个如果$ql<=midx,qu<=midy$就是左上角

第二个$qr>midx,qu<=midy$就是右上角

这样四个方向搞完修改也完成了

---

## 六.查询
```cpp
inline int query(int ql,int qr,int qu,int qd,int l,int r,int u,int d,int o)
{
  if(l>=ql && r<=qr && u>=qu && d<=qd)return tree[o].maxx;
  pushdown(l,r,u,d,o);
  int ans=-1;
    
  int midx,midy;
  midx=(l+r)>>1;
  midy=(u+d)>>1;
    
  if(ql<=midx && qu<=midy)//左上
  ans=honoka(query(ql,qr,qu,qd,l,midx,u,midy,slu),ans);
    
  if(qr>midx && qu<=midy && l!=r)//右上
  ans=honoka(query(ql,qr,qu,qd,midx+1,r,u,midy,sru),ans);
    
  if(ql<=midx && qd>midy && u!=d)//左下
  ans=honoka(query(ql,qr,qu,qd,l,midx,midy+1,d,sld),ans);
    
  if(qr>midx && qd>midy && l!=r && u!=d)//右下
  ans=honoka(query(ql,qr,qu,qd,midx+1,r,midy+1,d,srd),ans);
  return ans;
}
```

递归方向,具体操作和上面很像了,这里就不做过多赘述

---

## 七.主函数接口
```cpp
int main()
{
  int D,S,N;
  maki(D),maki(S),maki(N);
  buildtree(1,D,1,S,0);
  while(N--)
  {
    int d,s,h,x,y;
    maki(d),maki(s),maki(h),maki(x),maki(y);
    int add=query(x+1,x+d,y+1,y+s,1,D,1,S,0);
    add+=h;
    update(x+1,x+d,y+1,y+s,1,D,1,S,0,add);
  }
  printf("%d\n",query(1,D,1,S,1,D,1,S,0));
  return 0;
}
```

对应题面里面的修改,我们先查询出最大值,然后加上h再给修改回去就好

---

## 八.杂谈
### 首先
这个二维线段树,空间复杂度是$O(n^2)$的

建树的复杂度是$O(n^2)$

在这题里面肯定吃不消,事实上很多地方碍于二维线段树的高时间复杂度和空间复杂度,并不会去使用

但是洛谷上面没找到二维线段树的模板题,这一题稍微像一点,咱就稍微硬卡一下,顺便把二维线段树写清楚(网上详细的介绍还是很少的,还有一部分很不友好的指针类代码)

在这一题里面,我们注意到刚开始所有值都是0,也就是说可以不建树,从而省时间(全局数组默认为0)

### 其次

就是inline~~的心理作用~~,快速读入~~我姬赛高~~,氧气优化~~来,爽一口~~

即使这样我们依旧有可以优化的地方

中间的子树判断,根本没必要那么多的判断,可以适当地写在不同的判断里面

优化判断结构来优化时间(有效果的)

### 第三

就是$define$增加可读性

所以最后写出来了的版本并不是上面的版本(里面有判断结构的优化和define,但是具体的逻辑结构是一样的)

下面贴完整代码,希望对各位有帮助

---

## 九.完整代码和几次不同的提交情况

差点忘了还有个数组偏移

题目给的不是0开始的嘛,我们全部加1就好了

~~虽说建树可以不写,但是我还是觉得加上比较好,善始善终~~
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define maxn 1010
#define slu ((o<<2)+1)
#define sru ((o<<2)+2)
#define sld ((o<<2)+3)
#define srd ((o<<2)+4)
#define midx ((l+r)>>1)
#define midy ((u+d)>>1)
using namespace std;


struct segtree{
  int maxx,lazy;
}tree[(maxn<<2)*(maxn<<2)];


inline void maki(int &s)
{
  s=0;char c=getchar();while(c>'9' || c<'0') c=getchar();
  while(c<='9' && c>='0')s*=10,s+=c-'0',c=getchar();return;
}
inline int honoka(int a,int b)
{return a>b?a:b;}


inline void buildtree(int l,int r,int u,int d,int o)
{
  tree[o].lazy=0;
  
  if(l==r && u==d)
  {
    tree[o].maxx=0;
    return;
  }
  
  buildtree(l,midx,u,midy,slu);
  tree[o].maxx=honoka(tree[o].maxx,tree[slu].maxx);
  
  if(l!=r)
  {
    buildtree(midx+1,r,u,midy,sru);
    tree[o].maxx=honoka(tree[o].maxx,tree[sru].maxx);
    
    if(u!=d)//此处隐含了l!=r这个条件
    {
      buildtree(midx+1,r,midy+1,d,srd);
      tree[o].maxx=honoka(tree[o].maxx,tree[srd].maxx);
    }
  }
  
  if(u!=d)
  {
    buildtree(l,midx,midy+1,d,sld);
    tree[o].maxx=honoka(tree[o].maxx,tree[sld].maxx);
  }
  return;
}


inline void pushdown(int l,int r,int u,int d,int o)
{
  if(tree[o].lazy==0)
  return;
  
  tree[slu].maxx=tree[o].lazy;
  tree[slu].lazy=tree[o].lazy;
  
  if(l!=r)
  {
    tree[sru].maxx=tree[o].lazy;
    tree[sru].lazy=tree[o].lazy;
      
    if(u!=d)//同建树里面的结构优化
    {
      tree[srd].maxx=tree[o].lazy;
      tree[srd].lazy=tree[o].lazy;
    }
  }
  
  if(u!=d)
  {
    tree[sld].maxx=tree[o].lazy;
    tree[sld].lazy=tree[o].lazy;
  }
  tree[o].lazy=0;
  return;
}


inline void update(int ql,int qr,int qu,int qd,int l,int r,int u,int d,int o,int add)
{
  if(l>=ql && r<=qr && u>=qu && d<=qd)
  {
    tree[o].maxx=add;
    tree[o].lazy=add;
    return;
  }
    
  pushdown(l,r,u,d,o);
    
  if(ql<=midx)
  {
    if(qu<=midy)
    {
      update(ql,qr,qu,qd,l,midx,u,midy,slu,add);
      tree[o].maxx=honoka(tree[slu].maxx,tree[o].maxx);
    }
      
    if(qd>midy && u!=d)
    {
      update(ql,qr,qu,qd,l,midx,midy+1,d,sld,add);
      tree[o].maxx=honoka(tree[sld].maxx,tree[o].maxx);
    }
  }
    
  if(qr>midx && l!=r)
  {
    if(qu<=midy)
    {
      update(ql,qr,qu,qd,midx+1,r,u,midy,sru,add);
      tree[o].maxx=honoka(tree[sru].maxx,tree[o].maxx);
    }
      
    if(qd>midy && u!=d)
    {
      update(ql,qr,qu,qd,midx+1,r,midy+1,d,srd,add);
      tree[o].maxx=honoka(tree[srd].maxx,tree[o].maxx);
    }
  }
  return;
}


inline int query(int ql,int qr,int qu,int qd,int l,int r,int u,int d,int o)
{
  if(l>=ql && r<=qr && u>=qu && d<=qd)return tree[o].maxx;
  pushdown(l,r,u,d,o);
  int ans=-1;
    
  if(ql<=midx)
  {
    if(qu<=midy)
    ans=honoka(query(ql,qr,qu,qd,l,midx,u,midy,slu),ans);
      
    if(qd>midy && u!=d)
    ans=honoka(query(ql,qr,qu,qd,l,midx,midy+1,d,sld),ans);
  }
    
  if(qr>midx)
  {
    if(l!=r)
    {
      if(qu<=midy)
        ans=honoka(query(ql,qr,qu,qd,midx+1,r,u,midy,sru),ans);
        
        if(qd>midy && u!=d)
        ans=honoka(query(ql,qr,qu,qd,midx+1,r,midy+1,d,srd),ans);
    }
  }
    return ans;
}


int main()
{
  int D,S,N;
  maki(D),maki(S),maki(N);
  while(N--)
  {
    int d,s,h,x,y;
    maki(d),maki(s),maki(h),maki(x),maki(y);
    int add=query(x+1,x+d,y+1,y+s,1,D,1,S,0);
    add+=h;
    update(x+1,x+d,y+1,y+s,1,D,1,S,0,add);
  }
  printf("%d\n",query(1,D,1,S,1,D,1,S,0));
  return 0;
}
```

空行主要是想把不同逻辑的代码块分隔开

两格缩进党~~你谷博客吃掉了我部分缩进啊QAQ~~

![](https://cdn.luogu.com.cn/upload/pic/66674.png)
![](https://cdn.luogu.com.cn/upload/pic/66675.png)
![](https://cdn.luogu.com.cn/upload/pic/66676.png)

我又去各个群里面问了一下这些个情况是为什么(指同一份代码多次提交结果不同)

然后dalao的回答是测评误差,正常现象~~也就是说我是卡着时限过的XD~~

~~据说你谷的测评姬出了名的波动~~

嘛重点也不是为了卡过这道题~~过了肯定更好~~

主要是想介绍一下二维线段树的情况~~已经有那么多人写树套树的题解了QAQ~~


~~由于排版和错字情况多交了几次QAQ,ごめんなさい!~~

~~其实那一份过了的代码是在手机上把buildtree注释掉之后交上去一下过掉的2333333~~

---

下面和题目无关(主要是我想再试试人品)

#### 果然

#### ~~测评姬用这份AC给了我最好的晚安XD~~
![](https://cdn.luogu.com.cn/upload/pic/66678.png)

---

## 作者：Alex_Wei (赞：9)

> *[P3437 [POI2006]TET-Tetris 3D](https://www.luogu.com.cn/problem/P3437)
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/POI.html)。

对于一般的区间取 $\max$ 区间查询 $\max$，我们可以用普通带 `lazytag` 的线段树完成。但若要求**不能下传标记**（否则空间炸），**不能 `pushup`**（否则时间炸，因为一次 `pushup` 要进行大小为 $V$ 的线段树合并），那就有些棘手了。

一个想法是标记永久化，在更新路径上将维护的区间 $\max$ $val_i$ 对修改值 $v$ 取 $\max$，在所有拆分区间处将懒标记 $laz_i$ 对 $v$ 取 $\max$。查询时求递归路径上所有懒标记的最大值，再与拆分区间处维护的区间 $\max$ 取最大值。

实际意义：$val_i$ 表示维护的区间 $\max$，而 $laz_i$ 表示**没有被下传的修改值**的 $\max$，所以区间 $[l_i,r_i]$ 的最大值为 **$val_i$ 与 $i$ 到线段树的根上所有结点的 $laz_i$ 的最大值**。因此查询时需要整个递归路径的 $\max laz_i$。时空复杂度 $\mathcal{O}(n\log S\log D)$。

```cpp
const int N = 1e3 + 5;
int n, D, S;
namespace ST {
	int node, val[N << 11], laz[N << 11], ls[N << 11], rs[N << 11];
	void modify(int l, int r, int ql, int qr, int &x, int v) {
		if(!x) x = ++node; cmax(laz[x], v);
		if(ql <= l && r <= qr) return cmax(val[x], v), void();
		int m = l + r >> 1;
		if(ql <= m) modify(l, m, ql, qr, ls[x], v);
		if(m < qr) modify(m + 1, r, ql, qr, rs[x], v);
	}
	int query(int l, int r, int ql, int qr, int x) {
		if(!x) return 0;
		if(ql <= l && r <= qr) return max(laz[x], val[x]);
		int m = l + r >> 1, ans = val[x];
		if(ql <= m) cmax(ans, query(l, m, ql, qr, ls[x]));
		if(m < qr) cmax(ans, query(m + 1, r, ql, qr, rs[x]));
		return ans;
	}
}

int laz[N << 2], val[N << 2];
void modify(int l, int r, int ql, int qr, int u, int d, int x, int v) {
	ST :: modify(1, S, u, d, laz[x], v);
	if(ql <= l && r <= qr) return ST :: modify(1, S, u, d, val[x], v), void();
	int m = l + r >> 1;
	if(ql <= m) modify(l, m, ql, qr, u, d, x << 1, v);
	if(m < qr) modify(m + 1, r, ql, qr, u, d, x << 1 | 1, v);
}
int query(int l, int r, int ql, int qr, int u, int d, int x) {
	int ans = ST :: query(1, S, u, d, val[x]);
	if(ql <= l && r <= qr) return max(ans, ST :: query(1, S, u, d, laz[x]));
	int m = l + r >> 1;
	if(ql <= m) cmax(ans, query(l, m, ql, qr, u, d, x << 1));
	if(m < qr) cmax(ans, query(m + 1, r, ql, qr, u, d, x << 1 | 1));
	return ans;
}

int main(){
	cin >> D >> S >> n;
	for(int i = 1; i <= n; i++) {
		int d, s, w, x, y; cin >> d >> s >> w >> x >> y;
		int ht = query(1, D, x + 1, x + d, y + 1, y + s, 1);
		modify(1, D, x + 1, x + d, y + 1, y + s, 1, ht + w);
	} cout << query(1, D, 1, D, 1, S, 1) << endl;
	return 0;
}
```

---

## 作者：Sol1 (赞：6)

来水篇二维线段树的题解~

## Analysis:

首先我们来看一下这个问题，一个立方体掉落，停留的那个高度肯定是最先碰到的那个方块的高度，其实就是底面内的最大高度 $h=\max\limits_{x\leq i<x+d,y\leq j<y+s}a_{i,j}$；

落下之后，整个立方体不会散架，所以在底面区域之内的高度都会变成 $h+w_i$。

所以这个东西实际上就是个矩形赋值矩形 RMQ，且保证任意位置的高度单调不减。

## Solution 1:

可以直接写一个四分树维护这个平面，复杂度是 $O(nq)\approx O(2\times 10^7)$ 的，卡卡常应该能过，这里不做详细介绍。

## Solution 2:

可以使用线段树套线段树的方式维护。

先考虑一维，转变成区间赋值区间 RMQ，考虑使用线段树+标记永久化。在修改操作中我们可以直接把一个区间打上 tag，查询时直接在路径上取 tag 的最大值。因为任意位置的高度单调不减，所以直接取最大值一定是正确的。

然后我们扩展到二维，这时的 tag 可以表示为一个序列，每次在这个序列上面进行一次区间 RMQ 来取出需要的值，每次打 tag 的时候相当于在这个序列上面进行一次区间赋值。

所以用一个线段树来维护一下 tag，剩下的就和第一维的情况一样了~

这个的复杂度是 $O(n\log d\log s)\approx O(2\times 10^6)$ 的，可以随便过。

上代码~

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

inline int Abs(const int& x) {return (x > 0 ? x : -x);}
inline int Max(const int& x, const int& y) {return (x > y ? x : y);}
inline int Min(const int& x, const int& y) {return (x < y ? x : y);}

int d, s, n;

struct Segy {
	int tag[3505], val[3505];
	inline void Modify(int p, int pl, int pr, int l, int r, int v) {
		val[p] = Max(val[p], v);
		if (pl == l && pr == r) {
			tag[p] = Max(tag[p], v);
			return;
		}
		register int mid = pl + pr >> 1;
		if (mid >= r) Modify(p << 1, pl, mid, l, r, v);
		else if (mid + 1 <= l) Modify(p << 1 | 1, mid + 1, pr, l, r, v);
		else {
			Modify(p << 1, pl, mid, l, mid, v);
			Modify(p << 1 | 1, mid + 1, pr, mid + 1, r, v);
		}
	}
	inline int Query(int p, int pl, int pr, int l, int r) {
		if (pl == l && pr == r) return val[p];
		register int mid = pl + pr >> 1;
		if (mid >= r) return Max(Query(p << 1, pl, mid, l, r), tag[p]);
		else if (mid + 1 <= l) return Max(Query(p << 1 | 1, mid + 1, pr, l, r), tag[p]);
		else return Max(Max(Query(p << 1, pl, mid, l, mid), Query(p << 1 | 1, mid + 1, pr, mid + 1, r)), tag[p]);
	}
};
struct Segx {
	Segy tag[3505], val[3505];
	inline void Modify(int p, int pl, int pr, int l, int r, int _y0, int _y1, int v) {
		val[p].Modify(1, 1, s, _y0, _y1, v);
		if (pl == l && pr == r) {
			tag[p].Modify(1, 1, s, _y0, _y1, v);
			return;
		}
		register int mid = pl + pr >> 1;
		if (mid >= r) Modify(p << 1, pl, mid, l, r, _y0, _y1, v);
		else if (mid + 1 <= l) Modify(p << 1 | 1, mid + 1, pr, l, r, _y0, _y1, v);
		else {
			Modify(p << 1, pl, mid, l, mid, _y0, _y1, v);
			Modify(p << 1 | 1, mid + 1, pr, mid + 1, r, _y0, _y1, v);
		}
	}
	inline int Query(int p, int pl, int pr, int l, int r, int _y0, int _y1) {
		if (pl == l && pr == r) return val[p].Query(1, 1, s, _y0, _y1);
		register int mid = pl + pr >> 1, tmpv = tag[p].Query(1, 1, s, _y0, _y1);
		if (mid >= r) return Max(tmpv, Query(p << 1, pl, mid, l, r, _y0, _y1));
		else if (mid + 1 <= l) return Max(tmpv, Query(p << 1 | 1, mid + 1, pr, l, r, _y0, _y1));
		else return Max(Max(Query(p << 1, pl, mid, l, mid, _y0, _y1), Query(p << 1 | 1, mid + 1, pr, mid + 1, r, _y0, _y1)), tmpv);
	}
};

Segx sgt;

inline void Solve() {
	d = qread(); s = qread(); n = qread();
	while (n--) {
		register int _d = qread(), _s = qread(), _w = qread(), _x = qread(), _y = qread();
		register int val = sgt.Query(1, 1, d, _x + 1, _x + _d, _y + 1, _y + _s);
		sgt.Modify(1, 1, d, _x + 1, _x + _d, _y + 1, _y + _s, val + _w);
	}
	printf("%d", sgt.Query(1, 1, d, 1, d, 1, s));
}

int main() {
	Solve();
	#ifndef ONLINE_JUDGE
	while (1);
	#endif
	return 0;
}
```

---

## 作者：xzyxzy (赞：6)

主要内容在代码后方的注释里

主要对该题的流程进行一个梳理并对有争议的地方进行解释

并提供一个算好懂的代码吧。
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
int read()
{
	char ch=getchar();int h=0,t=1;
	while(ch!='-'&&(ch>'9'||ch<'0'))ch=getchar();
	if(ch=='-')t=-1,ch=getchar();
	while(ch>='0'&&ch<='9'){h=h*10+ch-'0';ch=getchar();}
	return h*t;	
}
const int MAXN=1010;
int N,M,TT;
struct Seg1//内层线段树，维护y轴
{
	int t[MAXN<<2],tag[MAXN<<2];
	int Query(int now,int l,int r,int gl,int gr)
		{
			if(l>gr||r<gl) return -1e9;
			if(l>=gl&&r<=gr) return max(t[now],tag[now]);//取max
			int mid=(l+r)>>1,Tag=tag[now];
			return max(Tag,max(Query(now<<1,l,mid,gl,gr),//标记永久化后要和祖先的tag取max
							   Query(now<<1|1,mid+1,r,gl,gr)));
		}
	void Replace(int now,int l,int r,int gl,int gr,int k)
		{
			if(l>gr||r<gl) return;
			t[now]=max(t[now],k);//为了方便都取max
			if(l>=gl&&r<=gr) {tag[now]=max(tag[now],k);return;}
			int mid=(l+r)>>1;
			Replace(now<<1,l,mid,gl,gr,k);
			Replace(now<<1|1,mid+1,r,gl,gr,k);
		}
};
struct Seg2//外层线段树，维护x轴
{
	Seg1 t[MAXN<<2],tag[MAXN<<2];
	int Query(int now,int l,int r,int gl,int gr,int dn,int up)
		{
			if(l>gr||r<gl) return -1e9;
			if(l>=gl&&r<=gr) return t[now].Query(1,1,M,dn,up);//打标记的时候已经取了max，所以不用和tag取max了
			int mid=(l+r)>>1,Tag=tag[now].Query(1,1,M,dn,up);
			return max(Tag,max(Query(now<<1,l,mid,gl,gr,dn,up),//要和祖先的tag取max
								Query(now<<1|1,mid+1,r,gl,gr,dn,up)));
		}
	void Replace(int now,int l,int r,int gl,int gr,int dn,int up,int k)
		{
			if(l>gr||r<gl) return;
			t[now].Replace(1,1,M,dn,up,k);//要把祖先的tag也更新
			if(l>=gl&&r<=gr) {tag[now].Replace(1,1,M,dn,up,k);return;}
			int mid=(l+r)>>1;
			Replace(now<<1,l,mid,gl,gr,dn,up,k);
			Replace(now<<1|1,mid+1,r,gl,gr,dn,up,k);
		}
}T;
int main()
{
	N=read(),M=read(),TT=read();
	while(TT--)
	{
		int d=read(),s=read(),h=read(),x=read()+1,y=read()+1;
		h+=T.Query(1,1,N,x,x+d-1,y,y+s-1);
		T.Replace(1,1,N,x,x+d-1,y,y+s-1,h);
	}
	printf("%d\n",T.Query(1,1,N,1,N,1,M));
	return 0;
}
/*
  理解线段树套线段树
  首先这题肯定会想到用区间覆盖标记
  外层线段树表示x轴，其中每个节点又代表一棵内层线段树，内层表示y轴
  为了方便，要标记永久化（你不知道下放的位置）
  流程就是：
  St1 区间覆盖的时候要把所有的母区间的value树更新
  
  这样可以不用pushup，value树中的value和tag都是取max
  在value树中的tag处取max这个地方纠结了很久
  比如说修改x轴上[3,5]的[4,6]为1
  但是已经修改过[7,9]的[4,6]为8
  那么在修改[1,10]的[4,6]区间时，tag已经为8了
  那么不能将它改成1
  因为询问是把区间卡死的，如果会询问到[1,10]中的[4,6]的tag
  就说明一定会取到8这个最大值，所以都要取max

  St2 然后再把卡死的区间tag树更新

  tag树的value和tag都是直接赋值而不是取max
  但是这道题能够保证一个地方的值只会不断增大，所以为了节省代码量就和上面的操作一并写了
  也就是因为这个性质，才让我以为value树中的tag也是不断增大然后删掉maxWA一片

  St1 区间询问的时候不断和这个区间的Tag取最值

  这样就可以过了，在取不取max上纠结了一个下午 TOT
 */
```

---

## 作者：Adove (赞：6)

时隔多日蒟蒻我终于弄懂了啥叫标记永久化（~~并且hack掉了一片题解的代码~~

在这里提供两种思路

1.标记永久化的矩形四分思想

顾名思义就是把一大块矩形沿对边中点连线切开，然后分治。

复杂度应该是O(n^2 log^2 n)的，但是**自带四倍常数！！**

吸氧92分代码实现如下↓
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;

int d,s,n,a,b,c,x,y;
int maxn[2048][2048],all[2048][2048];

void cchg(int x,int k1,int k2,int lx,int ly,int rx,int ry,int x1,int y1,int x2,int y2){
	
	if(x1<=lx&&y1<=ly&&rx<=x2&&ry<=y2){
		maxn[k1][k2]=x;
		all[k1][k2]=x;
		return;
	}
	
	int i1=k1<<1,i2=k2<<1,xmid=(lx+rx)>>1,ymid=(ly+ry)>>1,maxx=0;
	
	if(x1<=xmid){
		if(y1<=ymid) cchg(x,i1,i2,lx,ly,xmid,ymid,x1,y1,x2,y2);
		if(ymid<y2) cchg(x,i1,i2|1,lx,ymid+1,xmid,ry,x1,y1,x2,y2);
	}if(xmid<x2){
		if(y1<=ymid) cchg(x,i1|1,i2,xmid+1,ly,rx,ymid,x1,y1,x2,y2);
		if(ymid<y2) cchg(x,i1|1,i2|1,xmid+1,ymid+1,rx,ry,x1,y1,x2,y2);
	}
	
	maxn[k1][k2]=max(maxn[k1][k2],x);
}
int ask(int x,int k1,int k2,int lx,int ly,int rx,int ry,int x1,int y1,int x2,int y2){
	
	if(x1<=lx&&y1<=ly&&rx<=x2&&ry<=y2) return max(x,maxn[k1][k2]);
	
	int i1=k1<<1,i2=k2<<1,xmid=(lx+rx)>>1,ymid=(ly+ry)>>1,maxx=0,q=max(x,all[k1][k2]);
	
	if(x1<=xmid){
		if(y1<=ymid) maxx=max(maxx,ask(q,i1,i2,lx,ly,xmid,ymid,x1,y1,x2,y2));
		if(ymid<y2) maxx=max(maxx,ask(q,i1,i2|1,lx,ymid+1,xmid,ry,x1,y1,x2,y2));
	}if(xmid<x2){
		if(y1<=ymid) maxx=max(maxx,ask(q,i1|1,i2,xmid+1,ly,rx,ymid,x1,y1,x2,y2));
		if(ymid<y2) maxx=max(maxx,ask(q,i1|1,i2|1,xmid+1,ymid+1,rx,ry,x1,y1,x2,y2));
	}
	return maxx;
}

int main(){
	scanf("%d%d%d",&d,&s,&n);
	while(n--){
		scanf("%d%d%d%d%d",&a,&b,&c,&x,&y);
		cchg(ask(0,1,1,1,1,d,s,x+1,y+1,x+a,y+b)+c,1,1,1,1,d,s,x+1,y+1,x+a,y+b);
	}
	printf("%d",maxn[1][1]);
	return 0;
}
```

于是我们思考一种**不带四倍常数**的方法

AC代码如下

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;

int d,s,n,a,b,c,x,y;
struct treey{
	int maxn[1<<11],all[1<<11];
	void cchg(int x,int k,int ly,int ry,int y1,int y2){
		maxn[k]=max(maxn[k],x);
		if(y1<=ly&&ry<=y2){
			all[k]=max(all[k],x);
			return;
		}
		int i=k<<1,ymid=(ly+ry)>>1,maxx=0;
		
		if(y1<=ymid) cchg(x,i,ly,ymid,y1,y2);
		if(ymid<y2) cchg(x,i|1,ymid+1,ry,y1,y2);
	}
	int ask(int k,int ly,int ry,int y1,int y2){
		if(y1<=ly&&ry<=y2) return maxn[k];
		
		int i=k<<1,ymid=(ly+ry)>>1,maxx=all[k];
		
		if(y1<=ymid) maxx=max(maxx,ask(i,ly,ymid,y1,y2));
		if(ymid<y2) maxx=max(maxx,ask(i|1,ymid+1,ry,y1,y2));
		return maxx;
	}
};
struct treex{
	treey maxn[1<<11],all[1<<11];
	void cchg(int x,int k,int lx,int rx,int x1,int x2){
		maxn[k].cchg(x,1,1,s,y+1,y+b);
		if(x1<=lx&&rx<=x2){
			all[k].cchg(x,1,1,s,y+1,y+b);
			return;
		}
		int i=k<<1,xmid=(lx+rx)>>1,maxx=0;
		
		if(x1<=xmid) cchg(x,i,lx,xmid,x1,x2);
		if(xmid<x2) cchg(x,i|1,xmid+1,rx,x1,x2);
	}
	int ask(int k,int lx,int rx,int x1,int x2){
		if(x1<=lx&&rx<=x2) return maxn[k].ask(1,1,s,y+1,y+b);
		
		int i=k<<1,xmid=(lx+rx)>>1,maxx=all[k].ask(1,1,s,y+1,y+b);
		
		if(x1<=xmid) maxx=max(maxx,ask(i,lx,xmid,x1,x2));
		if(xmid<x2) maxx=max(maxx,ask(i|1,xmid+1,rx,x1,x2));
		return maxx;
	}
}Tree;

int main(){
	scanf("%d%d%d",&d,&s,&n);
	while(n--){
		scanf("%d%d%d%d%d",&a,&b,&c,&x,&y);
		Tree.cchg(Tree.ask(1,1,d,x+1,x+a)+c,1,1,d,x+1,x+a);
	}
	printf("%d",Tree.maxn[1].maxn[1]);
	return 0;
}
```

吸氧最优解前十，效率还不错。

---

## 作者：AubRain (赞：5)

$n*m(n,m\le1000)$ 的矩形，支持以下两种操作：

1、子矩形最大值

2、子矩形赋值

二维线段树裸题。

二维线段树：

好像并不是想象中的线段树套线段树，而是一种 **四叉树**

每个节点有四个儿子，把一个矩形分成四份。

然后写一个区间类，就可以像一维线段树一样操作了。

空间复杂度 $O(n^2)$ ，每次操作时间复杂度 $O(log^2n)$

需要卡常，一个小剪枝就是如果当前区间的最大值 $\le$ 已经查询的最大值，就直接 $return$  。

因为 $tag$ 标记单调不减，每次不用下放，直接取个 $max$ 就行了。好像叫做标记永久化。

```cpp
#include<bits/stdc++.h>
#define N 1005
#define M N*N<<2
#define son(x) ((p<<2)+(x-2))
using namespace std;

inline void rd(int &x){
    x=0;char ch=0;
    while(!isdigit(ch)) ch=getchar();
    while( isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
}

int n,m,q,V;
int mx[M],tag[M];
struct nd{
    int l,r;
    inline nd(int L,int R){l=L;r=R;}
    inline int mid(){return (l+r)>>1;}
    inline nd r1(){return (nd){ l ,mid()};}
    inline nd r2(){return (nd){mid()+1,r};}
};
void ask(int p,nd X,nd Y,nd x=nd(1,n),nd y=nd(1,m)){
    if(x.r<X.l or x.l>X.r or y.r<Y.l or y.l>Y.r or mx[p]<=V) return ;
    if(X.l<=x.l and x.r<=X.r and Y.l<=y.l and y.r<=Y.r) 
        return (void)(V=max(V,mx[p]));
    V=max(V,tag[p]);
    ask(son(0),X,Y,x.r1(),y.r1());
    ask(son(1),X,Y,x.r1(),y.r2());
    ask(son(2),X,Y,x.r2(),y.r1());
    ask(son(3),X,Y,x.r2(),y.r2());
}
void change(int p,int v,nd X,nd Y,nd x=nd(1,n),nd y=nd(1,m)){
    if(x.r<X.l or x.l>X.r or y.r<Y.l or y.l>Y.r) return ;
    if(X.l<=x.l and x.r<=X.r and Y.l<=y.l and y.r<=Y.r) 
        {mx[p]=tag[p]=v;return ;}
    change(son(0),v,X,Y,x.r1(),y.r1());
    change(son(1),v,X,Y,x.r1(),y.r2());
    change(son(2),v,X,Y,x.r2(),y.r1());
    change(son(3),v,X,Y,x.r2(),y.r2());
    for(int i=0;i<4;i++) mx[p]=max(mx[p],mx[son(i)]);
}
signed main(){
    rd(n);rd(m);rd(q);
    while(q--){
        int x,y,lx,ly,h;V=0;
        rd(lx);rd(ly);rd(h);rd(x);rd(y);x++;y++;
        ask(1,nd(x,x+lx-1),nd(y,y+ly-1));
        change(1,V+h,nd(x,x+lx-1),nd(y,y+ly-1));
    }
    printf("%d",mx[1]);
}
```

---

## 作者：liujiaxi123456 (赞：4)

## 前言 & 概述

看到所有的题解都是树套树/四分树/K-d tree，其中树套树卡空间，四分树卡时间，K-d tree 根本没卡过，于是想写一篇**不用卡常，不用卡空间，好写好调的二维分块做法。**

## 二维分块

众所周知，分块的复杂度是根号级别的，所以如果直接在第一维的基础上对第二维分块，时间复杂度是根号的平方，也就是 $O(n)$，所以平时不常使用，但是此题由于数据范围较小，完全可以通过。

P.S. 还有另外一种二维分块是可以做到根号的，但是需要一些条件，且非常复杂，在此不提，有兴趣的话，可以做做[此题](https://www.luogu.com.cn/problem/P7711)。

## 此题

先概括一下模型：

- 多次操作。

- 每次矩形查询最大值与矩形覆盖。

- P.S. 每次覆盖的值一定比之前的大。

显然需要二维数据结构，我们这里考虑二维分块：

- 先考虑查询需要的答案：

  - 散-散、散-整、整-散、整-整。
 
  - 所以我们需要四个基本数组分别表示这样的答案（分别为 $a, g, h, f$）。
 
- 考虑修改对这些答案的影响：

  - 散-散：$a$ 数组。
 
    - 最简单，把 $a,g,h,f$ 四个数组都更新一下即可。
   
  - 散-整：$g$ 数组。
 
    - 直接更新 $g,f$ 数组。
   
    - 发现由于需要更新 $a,h$ 数组有根号个，不能直接枚举后更新，考虑懒标记：
   
      - 对于 $a$ 数组，直接记录 $tag_g$ 即可。
     
        - 这意味着在询问单点值，即 $a$ 的值时，需要考虑 $tag$ 的贡献。
       
        - 下面有 $tag$ 的同样要在查询时收集 $tag$ 贡献。
       
      - 对于 $h$ 数组，所有与它相交的 $tag_g$ 都要收集。
     
        - 于是令 $tagmax_g$ 表示一个块内的 $tag_g$ 的 $\max$。
       
      - 在更新时把这两个数组一同更新。
     
  - 整-散：$h$ 数组。
   
    - 与 $g$ 数组一样的处理方式。
     
  - 整-整：$f$ 数组。
 
    - 更新 $f$ 数组。
   
    - 对于 $a,g,h$ 数组，显然仍然不能直接更新，仍然考虑懒标记：
   
      - 记录 $tag_f$ 即可。
     
- 处理掉修改后的查询：

  - $a = \max(a, tag_f, tag_g, tag_h) $
 
  - $g = \max(g, tag_f, tagmax_h) $
 
  - $h = \max(h, tag_f, tagmax_g) $
 
  - $f = f $
 
## 注意点：

- 本题输入的是点坐标，不是格子坐标，所以实际查询/修改的是：$[x+1, x+d][y+1, y+s]$。

- 为了区分整散块，建议可以用 $i$ 表示第一维整块，$j$ 表示第一维散块，$p,q$ 同理表示第二维。

- 更多细节见代码。
 
## Code：

最后献上我的代码（本来以为要卡常导致码风有点丑，后来发现发现跑得飞快（lg rank 5），但是懒得改了，如果对细节有困惑的话可以参考我注释掉的 `A,G,H,F` 函数）。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn = 1005, Sqrt = 50;
// const int Maxn = 1005, Sqrt = 1005;

class DataStructure {
private:
	int N, M, num1, num2, B1, B2, f[Sqrt][Sqrt], g[Maxn][Sqrt], h[Sqrt][Maxn], a[Maxn][Maxn];
	int st1[Sqrt], ed1[Sqrt], st2[Sqrt], ed2[Sqrt], bel1[Maxn], bel2[Maxn];
	int tag_f[Sqrt][Sqrt], tag_g[Maxn][Sqrt], tag_h[Sqrt][Maxn], tag_g_max[Sqrt][Sqrt], tag_h_max[Sqrt][Sqrt];
	inline void chkmax(int &a, int b) { a<b ?(a=b) : 0; }
	// inline int A(int j, int q) { return max({a[j][q], tag_f[bel1[j]][bel2[q]], tag_g[j][bel2[q]], tag_h[bel1[j]][q]}); }
	// inline int G(int j, int p) { return max({g[j][p], tag_f[bel1[j]][p], tag_h_max[bel1[j]][p]}); }
	// inline int H(int i, int q) { return max({h[i][q], tag_f[i][bel2[q]], tag_g_max[i][bel2[q]]}); }
	// inline int F(int i, int p) { return f[i][p]; }
public:
	inline void init(int n, int m) {
		// N = n, M = m;
		B1 = sqrt(n), B2 = sqrt(m);
		// num1 = (N+B1-1)/B1, num2 = (M+B2-1)/B2;
		// for(int i=1; i<=num1; i++) {
		// 	st1[i] = ed1[i-1]+1, ed1[i] = min(N, i*B1);
		// 	for(int j=st1[i]; j<=ed1[i]; j++)	bel1[j] = i, printf("bel1[%d]:%d\n", j, bel1[j]);
		// }
		// for(int i=1; i<=num2; i++) {
		// 	st2[i] = ed2[i-1]+1, ed2[i] = min(M, i*B2);
		// 	for(int j=st2[i]; j<=ed2[i]; j++)	bel2[j] = i, printf("bel2[%d]:%d\n", j, bel1[j]);
		// }
	}
	inline int Query(int l1, int r1, int l2, int r2) {
		int res = 0;
		int x1 = (l1+B1-1)/B1+1, y1 = (r1)/B1, x2 = (l2+B2-1)/B2+1, y2 = (r2)/B2;
		// printf("Query::(l1:%d, r1:%d, l2:%d, r2:%d, x1:%d, y1:%d, x2:%d, y2:%d)\n", l1, r1, l2, r2, x1, y1, x2, y2);
		if(x1 > y1 and x2 > y2) {
			for(int j=l1; j<=r1; j++) for(int q=l2; q<=r2; q++) res = max({res, a[j][q], tag_f[x1-1][x2-1], tag_g[j][x2-1], tag_h[x1-1][q]});
		} else if(x1 > y1) {
			for(int j=l1; j<=r1; j++) {
				for(int q=l2; q<=x2*B2-B2; q++)	res = max({res, a[j][q], tag_f[x1-1][x2-1], tag_g[j][x2-1], tag_h[x1-1][q]});
				for(int p=x2; p<=y2; p++)	res = max({res, g[j][p], tag_f[x1-1][p], tag_h_max[x1-1][p]});
				for(int q=y2*B2+1; q<=r2; q++)	res = max({res, a[j][q], tag_f[x1-1][y2+1], tag_g[j][y2+1], tag_h[x1-1][q]});
			}
		} else if(x2 > y2) {
			for(int j=l1; j<=x1*B1-B1; j++) for(int q=l2; q<=r2; q++) res = max({res, a[j][q], tag_f[x1-1][x2-1], tag_g[j][x2-1], tag_h[x1-1][q]});
			for(int i=x1; i<=y1; i++) for(int q=l2; q<=r2; q++) res = max({res, h[i][q], tag_f[i][x2-1], tag_g_max[i][x2-1]});
			for(int j=y1*B1+1; j<=r1; j++) for(int q=l2; q<=r2; q++) res = max({res, a[j][q], tag_f[y1+1][x2-1], tag_g[j][x2-1], tag_h[y1+1][q]});
		} else {
			for(int j=l1; j<=x1*B1-B1; j++) {
				for(int q=l2; q<=x2*B2-B2; q++)	res = max({res, a[j][q], tag_f[x1-1][x2-1], tag_g[j][x2-1], tag_h[x1-1][q]});
				for(int p=x2; p<=y2; p++)	res = max({res, g[j][p], tag_f[x1-1][p], tag_h_max[x1-1][p]});
				for(int q=y2*B2+1; q<=r2; q++)	res = max({res, a[j][q], tag_f[x1-1][y2+1], tag_g[j][y2+1], tag_h[x1-1][q]});
			}
			for(int i=x1; i<=y1; i++) {
				for(int q=l2; q<=x2*B2-B2; q++)	res = max({res, h[i][q], tag_f[i][x2-1], tag_g_max[i][x2-1]});
				for(int p=x2; p<=y2; p++)	res = max(res, f[i][p]);
				for(int q=y2*B2+1; q<=r2; q++)	res = max({res, h[i][q], tag_f[i][y2+1], tag_g_max[i][y2+1]});
			}
			for(int j=y1*B1+1; j<=r1; j++) {
				for(int q=l2; q<=x2*B2-B2; q++)	res = max({res, a[j][q], tag_f[y1+1][x2-1], tag_g[j][x2-1], tag_h[y1+1][q]});
				for(int p=x2; p<=y2; p++)	res = max({res, g[j][p], tag_f[y1+1][p], tag_h_max[y1+1][p]});
				for(int q=y2*B2+1; q<=r2; q++)	res = max({res, a[j][q], tag_f[y1+1][y2+1], tag_g[j][y2+1], tag_h[y1+1][q]});
			}
		}
		return res;
	}
	inline void Cover(int l1, int r1, int l2, int r2, int k) {
		int x1 = (l1+B1-1)/B1+1, y1 = (r1)/B1, x2 = (l2+B2-1)/B2+1, y2 = (r2)/B2;
		if(x1 > y1 and x2 > y2) {
			// puts("type 1");
			for(int j=l1; j<=r1; j++) for(int q=l2; q<=r2; q++) chkmax(f[x1-1][x2-1], k), chkmax(g[j][x2-1], k), chkmax(h[x1-1][q], k), chkmax(a[j][q], k);
		} else if(x1 > y1) {
			// puts("type 2");
			for(int j=l1; j<=r1; j++) {
				for(int q=l2; q<=x2*B2-B2; q++)	chkmax(f[x1-1][x2-1], k), chkmax(g[j][x2-1], k), chkmax(h[x1-1][q], k), chkmax(a[j][q], k);
				for(int p=x2; p<=y2; p++)	chkmax(f[x1-1][p], k), chkmax(g[j][p], k), chkmax(tag_g_max[x1-1][p], k), chkmax(tag_g[j][p], k);
				for(int q=y2*B2+1; q<=r2; q++)	chkmax(f[x1-1][y2+1], k), chkmax(g[j][y2+1], k), chkmax(h[x1-1][q], k), chkmax(a[j][q], k);
			}
		} else if(x2 > y2) {
			// puts("type 3");
			for(int j=l1; j<=x1*B1-B1; j++) for(int q=l2; q<=r2; q++) chkmax(f[x1-1][x2-1], k), chkmax(g[j][x2-1], k), chkmax(h[x1-1][q], k), chkmax(a[j][q], k);
			for(int i=x1; i<=y1; i++) for(int q=l2; q<=r2; q++) chkmax(f[i][x2-1], k), chkmax(h[i][q], k), chkmax(tag_h_max[i][x2-1], k), chkmax(tag_h[i][q], k);
			for(int j=y1*B1+1; j<=r1; j++) for(int q=l2; q<=r2; q++) chkmax(f[y1+1][x2-1], k), chkmax(g[j][x2-1], k), chkmax(h[y1+1][q], k), chkmax(a[j][q], k);
		} else {
			// puts("type 4");
			for(int j=l1; j<=x1*B1-B1; j++) {
				for(int q=l2; q<=x2*B2-B2; q++)	chkmax(f[x1-1][x2-1], k), chkmax(g[j][x2-1], k), chkmax(h[x1-1][q], k), chkmax(a[j][q], k);
				for(int p=x2; p<=y2; p++)	chkmax(f[x1-1][p], k), chkmax(g[j][p], k), chkmax(tag_g_max[x1-1][p], k), chkmax(tag_g[j][p], k);
				for(int q=y2*B2+1; q<=r2; q++)	chkmax(f[x1-1][y2+1], k), chkmax(g[j][y2+1], k), chkmax(h[x1-1][q], k), chkmax(a[j][q], k);
			}
			for(int i=x1; i<=y1; i++) {
				for(int q=l2; q<=x2*B2-B2; q++)	chkmax(f[i][x2-1], k), chkmax(h[i][q], k), chkmax(tag_h_max[i][x2-1], k), chkmax(tag_h[i][q], k);
				for(int p=x2; p<=y2; p++)	chkmax(f[i][p], k), chkmax(tag_f[i][p], k);
				for(int q=y2*B2+1; q<=r2; q++)	chkmax(f[i][y2+1], k), chkmax(h[i][q], k), chkmax(tag_h_max[i][y2+1], k), chkmax(tag_h[i][q], k);
			}
			for(int j=y1*B1+1; j<=r1; j++) {
				for(int q=l2; q<=x2*B2-B2; q++)	chkmax(f[y1+1][x2-1], k), chkmax(g[j][x2-1], k), chkmax(h[y1+1][q], k), chkmax(a[j][q], k);
				for(int p=x2; p<=y2; p++)	chkmax(f[y1+1][p], k), chkmax(g[j][p], k), chkmax(tag_g_max[y1+1][p], k), chkmax(tag_g[j][p], k);
				for(int q=y2*B2+1; q<=r2; q++)	chkmax(f[y1+1][y2+1], k), chkmax(g[j][y2+1], k), chkmax(h[y1+1][q], k), chkmax(a[j][q], k);
			}
		} 
	}
} ds;

namespace Josh_zmf {
	
	int Q, N, M;

	inline int main() {
		cin>> N>> M>> Q, ds.init(N, M);
		for(int d, s, w, x, y; Q--; ) {
			cin>> d>> s>> w>> x>> y;
			int h = ds.Query(x+1, x+d, y+1, y+s);
			// printf("h:%d\n", h);
			ds.Cover(x+1, x+d, y+1, y+s, h+w);
		}
		cout<< ds.Query(1, N, 1, M)<< '\n';
		return 0;
	}

}

int main() {
	Josh_zmf::main();
	return 0;
}
```
## 结语：

都看到这里了，点个赞再走吧！

---

## 作者：zac2010 (赞：3)

注意到这道题本质就是一个矩形求和矩形赋值的操作。其中满足：对于任意一个点，每次赋予的权值是单调递增的。

这看起但就像是一个二维线段树能做的范畴。但是众所周知，二维线段树的外层无法进行标记上传操作（无法 `pushup`），故而这题我们考虑标记永久化。同时，为了简化问题，我们先关心一维的情况。

我们考虑对于每个点，记录两个权值：$mx$ 和 $tg$。前者为当前区间的最大值，后者为标记值。

* 对于修改操作。沿用常规的懒标记线段树的方法，更新那些被当前区间完全包含的极大区间的 $tg$ 值。同时，更新修改过程中遍历到过的所有节点的 $mx$。
* 对于询问操作，进行标记永久化的查询。同时，对于那些被当前区间完全包含的极大区间，我们也拿它的 $mx$ 值区更新答案。

二维情况类似。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); i++)
#define FR(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
int D, S, N;
namespace T{
	struct SGTx{
		int mx[2050], tg[2050];
		void Upd(int p, int l, int r, int x, int y, int v){
			mx[p] = max(mx[p], v);
			if(x <= l && r <= y){tg[p] = max(tg[p], v); return;}
			int mid = l + r >> 1;
			if(x <= mid) Upd(p << 1, l, mid, x, y, v);
			if(mid < y) Upd(p << 1 | 1, mid + 1, r, x, y, v);
		}
		int Qry(int p, int l, int r, int x, int y){
			if(x <= l && r <= y) return mx[p];
			int mid = l + r >> 1, ret = tg[p];
			if(x <= mid) ret = max(ret, Qry(p << 1, l, mid, x, y));
			if(mid < y) ret = max(ret, Qry(p << 1 | 1, mid + 1, r, x, y));
			return ret;
		}
	} mx[2050], tg[2050];
	void Upd(int p, int l, int r, int x1, int y1, int x2, int y2, int v){
		mx[p].Upd(1, 1, S, x2, y2, v);
		if(x1 <= l && r <= y1){tg[p].Upd(1, 1, S, x2, y2, v); return;}
		int mid = l + r >> 1;
		if(x1 <= mid) Upd(p << 1, l, mid, x1, y1, x2, y2, v);
		if(mid < y1) Upd(p << 1 | 1, mid + 1, r, x1, y1, x2, y2, v);
	}
	int Qry(int p, int l, int r, int x1, int y1, int x2, int y2){
		if(x1 <= l && r <= y1) return mx[p].Qry(1, 1, S, x2, y2);
		int mid = l + r >> 1, ret = tg[p].Qry(1, 1, S, x2, y2);
		if(x1 <= mid) ret = max(ret, Qry(p << 1, l, mid, x1, y1, x2, y2));
		if(mid < y1) ret = max(ret, Qry(p << 1 | 1, mid + 1, r, x1, y1, x2, y2));
		return ret;
	}
}
int main(){
	scanf("%d%d%d", &D, &S, &N), D++, S++;
	FL(i, 1, N){
		int d, s, w, x, y, h;
		scanf("%d%d%d%d%d", &d, &s, &w, &x, &y), x++, y++;
		h = T::Qry(1, 1, D, x, x + d - 1, y, y + s - 1);
		T::Upd(1, 1, D, x, x + d - 1, y, y + s - 1, h + w);
	}
	printf("%d\n", T::Qry(1, 1, D, 1, D, 1, S));
	return 0;
}
```


---

## 作者：Emertyst (赞：3)

# 简要题意

给定一个矩阵，初始时每个位置上的数都是 $0$，每次查询一个子矩阵的最大值，并将这个子矩阵的所有数修改为最大值加 $w$，输出最后整个矩阵的最大值。

# 思路

使用线段树套线段树解决。外层线段树维护行，每个结点维护一棵线段树，一个区间为 $[l, r]$ 的结点维护的线段树为矩阵第 $l$ 行到第 $r$ 行的最大值。因为需要区间修改，还需要维护懒标记。值得注意的是，外层线段树的标记是一棵线段树。

由于外层线段树更新结点信息和下传标记都相当于两棵线段树合并，所以使用传统的方法会 T 飞，因此我们需要使用标记永久化。

## 标记永久化

我们可以利用一维线段树来帮助理解标记永久化。假如我们需要实现维护序列的区间加、区间求和，我们在更新的过程中便修改经过结点的权值，然后对被完全覆盖的区间打标记；在查询时，我们记录经过结点的标记之和，对于被完全覆盖的区间，这个区间实际的和为记录的和加上区间长度乘标记。对应的代码是这样的（代码中 $l$ 和 $r$ 表示当前结点维护的区间为 $[l, r]$，$L$ 和 $R$ 表示查询/修改的区间为 $[L, R]$）：

```cpp
void update(int pos, int l, int r, int L, int R, int val) {
    sum[pos] += (R - L + 1) * val;
    if (L == l && R == r) {
        tag[pos] += val;
        return;
    }
    int mid = (l + r) / 2;
    if (L <= mid)
        update(ls[pos], l, mid, L, min(R, mid), val);
    if (R > mid)
        update(rs[pos], mid + 1, r, max(L, mid + 1), R, val);
}
int query(int pos, int l, int r, int L, int R, int val) {
    if (L <= l && R >= r)
        return sum[pos] + (r - l + 1) * val;
    val += tag[pos];
    int mid = (l + r) / 2;
    if (R <= mid)
        return query(ls[pos], l, mid, L, R, val);
    if (L > MID)
        return query(rs[pos], mid + 1, r, L, R, val);
    return query(ls[pos], l, mid, L, R, val) + query(rs[pos], mid + 1, r, L, R, val);
}
```

对于线段树套线段树的区间永久化，和一维线段树类似，只不过外层维护的最大值和懒标记都是一个一维线段树。

~~容易看出~~ 经过亿些思考，可以发现有一些信息是不能用标记永久化维护的。因为传统的写法中一个结点维护的信息是通过子区间的信息合并得来，而标记永久化是在更新的时候计算对有关结点信息的改变。如果是随机的区间修改与区间求最大值是不能用标记永久化维护的，因为当一个位置的值缩小时，我们无法在更新的过程中得知经过结点信息应该如何变化。

这道题的特殊之处在于区间修改的值比修改前的最大值要大，因此对经过结点的影响是可以计算的，具体来说就是在更新过程中对结点维护的信息取最大。

# 代码

```cpp
#include <iostream>
#define LP pos << 1
#define RP LP | 1
#define MID (l + r >> 1)
#define LS l, MID
#define RS MID + 1, r
#define THIS pos, l, r
using namespace std;
const int MAXN = 2e4 + 5;
int n, m, q, tot, ls[MAXN * 100], rs[MAXN * 100], num[MAXN * 100], tag[MAXN * 100];
class SegmentTree1D {
private:
    int root;
    void update(int &pos, int l, int r, int L, int R, int val) {
        if (!pos)
            pos = ++tot;
        num[pos] = max(num[pos], val);
        if (L <= l && R >= r)
            return tag[pos] = max(tag[pos], val), void(); // 这里
        if (L <= MID)
            update(ls[pos], LS, L, R, val);
        if (R > MID)
            update(rs[pos], RS, L, R, val);
    }
    int query(int pos, int l, int r, int L, int R, int val) {
        if (L <= l && R >= r)
            return max(num[pos], val);
        val = max(val, tag[pos]);
        if (R <= MID)
            return query(ls[pos], LS, L, R, val);
        if (L > MID)
            return query(rs[pos], RS, L, R, val);
        return max(query(ls[pos], LS, L, R, val), query(rs[pos], RS, L, R, val));
    }

public:
    void update(int l, int r, int x) { update(root, 1, m, l, r, x); }
    int query(int l, int r) { return query(root, 1, m, l, r, 0); }
};
class SegmentTree2D {
private:
    SegmentTree1D num[MAXN * 4], tag[MAXN * 4];
    void update(int pos, int l, int r, int L, int R, int a, int b, int val) {
        num[pos].update(a, b, val);
        if (L <= l && R >= r)
            return tag[pos].update(a, b, val);
        if (L <= MID)
            update(LP, LS, L, R, a, b, val);
        if (R > MID)
            update(RP, RS, L, R, a, b, val);
    }
    int query(int pos, int l, int r, int L, int R, int a, int b, int val) {
        if (L <= l && R >= r)
            return max(num[pos].query(a, b), val);
        val = max(val, tag[pos].query(a, b));
        if (R <= MID)
            return query(LP, LS, L, R, a, b, val);
        if (L > MID)
            return query(RP, RS, L, R, a, b, val);
        return max(query(LP, LS, L, R, a, b, val), query(RP, RS, L, R, a, b, val));
    }

public:
    void update(int l, int r, int a, int b, int x) { update(1, 1, n, l, r, a, b, x); }
    int query(int l, int r, int a, int b) { return query(1, 1, n, l, r, a, b, 0); }
} t;
int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n >> m >> q;
    for (int i = 1, d, s, w, x, y; i <= q; ++i)
        cin >> d >> s >> w >> x >> y, t.update(x + 1, x + d, y + 1, y + s, t.query(x + 1, x + d, y + 1, y + s) + w);
    cout << t.query(1, n, 1, m) << "\n";
}
```

## 关于内层线段树的标记为什么是取最大值而不是直接赋值

代码中的注释处是内层线段树的标记，这里必须写成取最大值。对于外层线段树，在更新过程中对经过结点维护的线段树的更新的含义是取最大值，而不是区间修改。同时，因为这道题对于区间修改的特殊性，区间修改相当于区间中的所有数对一个数取最大值。因此内层线段树的标记必须是取最大值。（~~我们可以类比一下~~ 代码中的注释处上数第二行写成 `num[pos] = val;` 对于一维线段树的影响，相当于注释处写成赋值对二维线段树的影响）

---

## 作者：chenzida (赞：2)

四分树卡常差点没把我人卡死。。。

大概就是每个点有 $4$ 个儿子，然后直接仿照普通线段树就好了。

转移的判断有一些恶心，反正我写了 $4K+$。

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int NR=1005;
int max(int a,int b){return (a>b)?a:b;}
void Max(int& x,int y){x=max(x,y);}
int mmax(int a,int b,int c,int d){
	return max(max(a,b),max(c,d));
}
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int D,S,n,mx;
struct Segment
{
	int tr[NR<<2][NR<<2],lz[NR<<2][NR<<2];
	void update(int rt1,int rt2){
		tr[rt1][rt2]=mmax(tr[rt1<<1][rt2<<1],tr[rt1<<1|1][rt2<<1|1]
					,tr[rt1<<1|1][rt2<<1],tr[rt1<<1][rt2<<1|1]);
	}
	void push_down(int rt1,int rt2)
	{
		if(!lz[rt1][rt2])return;
		Max(lz[rt1<<1][rt2<<1],lz[rt1][rt2]);
		Max(lz[rt1<<1|1][rt2<<1],lz[rt1][rt2]);
		Max(lz[rt1<<1][rt2<<1|1],lz[rt1][rt2]);
		Max(lz[rt1<<1|1][rt2<<1|1],lz[rt1][rt2]);
		Max(tr[rt1<<1][rt2<<1],lz[rt1][rt2]);
		Max(tr[rt1<<1|1][rt2<<1],lz[rt1][rt2]);
		Max(tr[rt1<<1][rt2<<1|1],lz[rt1][rt2]);
		Max(tr[rt1<<1|1][rt2<<1|1],lz[rt1][rt2]);
		lz[rt1][rt2]=0;
	}
	void change(int rt1,int rt2,int l1,int l2,int r1,int r2,int L1,int L2,int R1,int R2,int v)
	{
		if(l1==L1&&l2==L2&&r1==R1&&r2==R2){Max(tr[rt1][rt2],v),Max(lz[rt1][rt2],v);return;}
		int mid1=(l1+r1)>>1,mid2=(l2+r2)>>1;push_down(rt1,rt2);
		if(R1<=mid1){
			if(R2<=mid2)change(rt1<<1,rt2<<1,l1,l2,mid1,mid2,L1,L2,R1,R2,v);
			else if(L2>mid2)change(rt1<<1,rt2<<1|1,l1,mid2+1,mid1,r2,L1,L2,R1,R2,v);
			else change(rt1<<1,rt2<<1,l1,l2,mid1,mid2,L1,L2,R1,mid2,v),
				 change(rt1<<1,rt2<<1|1,l1,mid2+1,mid1,r2,L1,mid2+1,R1,R2,v);
		}
		else if(L1>mid1){
			if(R2<=mid2)change(rt1<<1|1,rt2<<1,mid1+1,l2,r1,mid2,L1,L2,R1,R2,v);
			else if(L2>mid2)change(rt1<<1|1,rt2<<1|1,mid1+1,mid2+1,r1,r2,L1,L2,R1,R2,v);
			else change(rt1<<1|1,rt2<<1,mid1+1,l2,r1,mid2,L1,L2,R1,mid2,v),
				 change(rt1<<1|1,rt2<<1|1,mid1+1,mid2+1,r1,r2,L1,mid2+1,R1,R2,v);
		}
		else{
			if(R2<=mid2)change(rt1<<1,rt2<<1,l1,l2,mid1,mid2,L1,L2,mid1,R2,v),
						change(rt1<<1|1,rt2<<1,mid1+1,l2,r1,mid2,mid1+1,L2,R1,R2,v);
			else if(L2>mid2)change(rt1<<1,rt2<<1|1,l1,mid2+1,mid1,r2,L1,L2,mid1,R2,v),
							change(rt1<<1|1,rt2<<1|1,mid1+1,mid2+1,r1,r2,mid1+1,L2,R1,R2,v);
			else change(rt1<<1,rt2<<1,l1,l2,mid1,mid2,L1,L2,mid1,mid2,v),
				 change(rt1<<1,rt2<<1|1,l1,mid2+1,mid1,r2,L1,mid2+1,mid1,R2,v),
				 change(rt1<<1|1,rt2<<1,mid1+1,l2,r1,mid2,mid1+1,L2,R1,mid2,v),
				 change(rt1<<1|1,rt2<<1|1,mid1+1,mid2+1,r1,r2,mid1+1,mid2+1,R1,R2,v);
		}
		update(rt1,rt2);
	}
	void query(int rt1,int rt2,int l1,int l2,int r1,int r2,int L1,int L2,int R1,int R2)
	{
		if(tr[rt1][rt2]<=mx)return;
		if(l1==L1&&l2==L2&&r1==R1&&r2==R2){Max(mx,tr[rt1][rt2]);return;}
		int mid1=(l1+r1)>>1,mid2=(l2+r2)>>1;push_down(rt1,rt2);
		if(R1<=mid1){
			if(R2<=mid2)return query(rt1<<1,rt2<<1,l1,l2,mid1,mid2,L1,L2,R1,R2);
			else if(L2>mid2)return query(rt1<<1,rt2<<1|1,l1,mid2+1,mid1,r2,L1,L2,R1,R2);
			else return query(rt1<<1,rt2<<1,l1,l2,mid1,mid2,L1,L2,R1,mid2),
				  query(rt1<<1,rt2<<1|1,l1,mid2+1,mid1,r2,L1,mid2+1,R1,R2);
		}
		else if(L1>mid1){
			if(R2<=mid2)return query(rt1<<1|1,rt2<<1,mid1+1,l2,r1,mid2,L1,L2,R1,R2);
			else if(L2>mid2)return query(rt1<<1|1,rt2<<1|1,mid1+1,mid2+1,r1,r2,L1,L2,R1,R2);
			else return query(rt1<<1|1,rt2<<1,mid1+1,l2,r1,mid2,L1,L2,R1,mid2),
				  query(rt1<<1|1,rt2<<1|1,mid1+1,mid2+1,r1,r2,L1,mid2+1,R1,R2);
		}
		else{
			if(R2<=mid2)return query(rt1<<1,rt2<<1,l1,l2,mid1,mid2,L1,L2,mid1,R2),
						 query(rt1<<1|1,rt2<<1,mid1+1,l2,r1,mid2,mid1+1,L2,R1,R2);
			else if(L2>mid2)return query(rt1<<1,rt2<<1|1,l1,mid2+1,mid1,r2,L1,L2,mid1,R2),
							query(rt1<<1|1,rt2<<1|1,mid1+1,mid2+1,r1,r2,mid1+1,L2,R1,R2);
			else return query(rt1<<1,rt2<<1,l1,l2,mid1,mid2,L1,L2,mid1,mid2),
				query(rt1<<1,rt2<<1|1,l1,mid2+1,mid1,r2,L1,mid2+1,mid1,R2),
				query(rt1<<1|1,rt2<<1,mid1+1,l2,r1,mid2,mid1+1,L2,R1,mid2),
				query(rt1<<1|1,rt2<<1|1,mid1+1,mid2+1,r1,r2,mid1+1,mid2+1,R1,R2);
		}
	}
}T;
int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	D=read()+1,S=read()+1,n=read();
	for(int i=1;i<=n;i++){
		int d=read(),s=read(),w=read(),x=read()+1,y=read()+1;mx=0;
		T.query(1,1,1,1,D,S,x,y,x+d-1,y+s-1);
		T.change(1,1,1,1,D,S,x,y,x+d-1,y+s-1,mx+w);
	}mx=0,T.query(1,1,1,1,D,S,1,1,D,S);printf("%d\n",mx);
	return 0;
}
```

开O2能艹过去

---

## 作者：AmamiyaUmi (赞：2)

http://www.neptuuz.com/wordpress/?p=129

这道题对空间限制特别严格，仅仅128M！

所以需要将空间开的尽可能小，每颗线段树堆结构在最多用O(2^(⌈logn⌉+1))的空间，所以数组只用开2048

其余之外就是二维线段树的模版题，注意要用标签永久化的更新方式了

```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;

int D, S, N;

struct segy {
    int v[2048], tag[2048];
    
    void change(int p, int l, int r, int ll, int rr, int d) {
        v[p] = max(v[p], d);
        if (ll <= l && r <= rr) {
            tag[p] = max(tag[p], d);
            return;
        }
        int mid = (l+r)/2;
        if (ll < mid) change(p<<1, l, mid, ll, rr, d);
        if (rr > mid) change(p<<1|1, mid, r, ll, rr, d);
    }
    
    int query(int p, int l, int r, int ll, int rr) {
        if (ll <= l && r <= rr) {
            return v[p];
        }
        int mid = (l+r)>>1, ans = tag[p];
        if (ll < mid) ans = max(ans, query(p<<1, l, mid, ll, rr));
        if (rr > mid) ans = max(ans, query(p<<1|1, mid, r, ll, rr));
        return ans;
    }
};

struct segx {
    segy v[2048], tag[2048];
    
    void change(int p, int l, int r, int ll, int rr, int y1, int y2, int d) {
        v[p].change(1, 1, S, y1, y2, d);
        if (ll <= l && r <= rr) {
            tag[p].change(1, 1, S, y1, y2, d);
            return;
        }
        int mid = (l+r)/2;
        if (ll < mid) change(p<<1, l, mid, ll, rr, y1, y2, d);
        if (rr > mid) change(p<<1|1, mid, r, ll, rr, y1, y2, d);
    }
    
    int query(int p, int l, int r, int ll, int rr, int y1, int y2) {
        if (ll <= l && r <= rr) {
            return v[p].query(1, 1, S, y1, y2);
        }
        int mid = (l+r)>>1, ans = tag[p].query(1, 1, S, y1, y2);
        if (ll < mid) ans = max(ans, query(p<<1, l, mid, ll, rr, y1, y2));
        if (rr > mid) ans = max(ans, query(p<<1|1, mid, r, ll, rr, y1, y2));
        return ans;
    }
} T;

int main() {
    scanf("%d%d%d", &D, &S, &N);
    for (int i = 1, d, s, w, x, y, now; i <= N; ++i) {
        scanf("%d%d%d%d%d", &d, &s, &w, &x, &y);
        int t = T.query(1, 0, D, x, x+d, y, y+s);
        T.change(1, 0, D, x, x+d, y, y+s, t+w);
    }
    printf("%d\n", T.query(1, 0, D, 0, D, 0, S));
    return 0;
}
```

---

## 作者：oscar (赞：2)

【POI补全计划#21 POI2006 TET】

无智商选手oscar又来写题解啦！

这道题看起来像是一个裸的二维线段树，然而写到一半发现二维线段树上发不了lazy

于是我去请教了h*****5巨神，他说可以用四叉树做，就是不知道O(nq)能不能跑过，于是我就写了一棵四叉树！

代码：<http://paste.ubuntu.com/25659343/>

然而TLE了...

于是我又去请教o********d巨神，他说可以标记永久化....

故事部分完了，我们来分析一下这个“标记永久化”是个啥

画外音：就是不发lazy（

那么**整体思路就是建一棵树套树，外层节点的lazy和maxx信息用一棵内层树维护，这样就可以正常地修改和查询了。。**

**修改时更新路径上所有节点的maxx信息，更新最下层节点的lazy信息**

**查询时用路径上所有节点的lazy信息和最下层节点的maxx信息来更新答案**

**正确性请读者自己思考（逃）**

于是我们又写了一课指针版的树套树，代码：<http://paste.ubuntu.com/25659399/>

然而MLE了...

于是我就去请教了o***r蒟蒻，决定去掉节点内部的l和r信息，因为访问到节点的时候一定是从上层节点下来的，所以l和r可以通过父节点计算出来

代码：<http://paste.ubuntu.com/25659376/>

然而还是MLE...

于是我又去请教了o***r蒟蒻，决定改为**堆式存储**，于是就愉快地AC了！

（貌似多开了一个毫无用处的数组）

最终AC代码：<http://paste.ubuntu.com/25659418/>

**太长不看版：上面的加粗字**


---

## 作者：kczno1 (赞：1)

直接把矩阵所有的点拿出来建kd-tree。

维护max和加法tag。

复杂度是N\*log^2(D\*S)

但是过不了。。

```cpp
#include<bits/stdc++.h>
using std::max;
using std::nth_element;

#define rep(i,l,r) for(int i=l;i<=r;++i)
#define gc (c=getchar())
int read()
{
    char c;
    while(gc<'0');
    int x=c-'0';
    while(gc>='0')x=x*10+c-'0';
    return x;
}
void chmax(int &x,int y)
{
    if(x<y)x=y;
}
void chmin(int &x,int y)
{
    if(x>y)x=y;
}
void chmax(short &x,short y)
{
    if(x<y)x=y;
}
void chmin(short &x,short y)
{
    if(x>y)x=y;
}

const int N=1e6+5;
short px[N],py[N];
int id[N];
int c[N][2];short mxx[N],mnx[N],mxy[N],mny[N];
int w[N],same[N],mxw[N];

int nw;short x1,Y1,x2,y2;
int ans;

#define in(x) (mnx[x]>=x1&&mxx[x]<=x2&&mny[x]>=Y1&&mxy[x]<=y2)
#define _in(x) (px[x]>=x1&&px[x]<=x2&&py[x]>=Y1&&py[x]<=y2)
#define out(x) (mnx[x]>x2||mxx[x]<x1||mny[x]>y2||mxy[x]<Y1)

void make_same(int x,int nw)
{
    same[x]=w[x]=mxw[x]=nw;
}
#define up(x) {mxw[x]=max(w[x],max(mxw[c[x][0]],mxw[c[x][1]]));}
void down(int x)
{
    if(same[x])
    {
        if(c[x][0])make_same(c[x][0],same[x]);
        if(c[x][1])make_same(c[x][1],same[x]);
        same[x]=0;
    }
}
void qiu(int x)
{
    if(out(x)||mxw[x]<ans) return ;
    if(in(x)) {ans=mxw[x];return ;}
    
    if(_in(x)) chmax(ans,w[x]);
    down(x);
    qiu(c[x][0]);qiu(c[x][1]);
}
void make_same(int x)
{
    if(out(x)) return ;
    if(in(x)) 
    {
        make_same(x,nw);
        return ;
    }
    
    if(_in(x)) w[x]=nw;
    down(x);
    make_same(c[x][0]);make_same(c[x][1]);
    up(x);
}

void sc(int y,int x,bool d)
{
    c[y][d]=x;
    chmax(mxx[y],mxx[x]);
    chmax(mxy[y],mxy[x]);
    chmin(mnx[y],mnx[x]);
    chmin(mny[y],mny[x]);
}
bool px_xiao(int x,int y)
{
    return px[x]<px[y];
}
bool py_xiao(int x,int y)
{
    return py[x]<py[y];
}
int build(int l,int r,bool d)
{
    int mid=l+r>>1;
    nth_element(id+l,id+mid,id+r+1,d?px_xiao:py_xiao);
    
    int rt=id[mid];
    mxx[rt]=mnx[rt]=px[rt];
    mxy[rt]=mny[rt]=py[rt];
    
    if(l!=mid)sc(rt,build(l,mid-1,!d),0);
    if(r!=mid)sc(rt,build(mid+1,r,!d),1);
    return rt;
}

int main()
{
    int n=read(),m=read(),q=read();
    
    int tot=0;
    rep(i,1,n)
    rep(j,1,m)
    {
        px[++tot]=i;
        py[tot]=j;
    }
    rep(i,1,tot)id[i]=i;
    int rt=build(1,tot,0);
    
    while(q--)
    {
        short dx=read(),dy=read();
        nw=read();x1=read();Y1=read();
        x2=x1+dx;y2=Y1+dy;
        ++x1;++Y1;
        
        ans=0;
        qiu(rt);
        nw+=ans;
        make_same(rt);
    }
    
    printf("%d\n",mxw[rt]);
}
```

---

## 作者：pokefunc (赞：0)

### Description

一块 $D \times S$ 的地面，最开始什么也没有，现在从上面往下面放 $N$ 个立方体。

立方体会竖直下落直到碰到地面或者已放置的立方体时停止掉落，从此保持在这个位置不动。

问所有立方体放置完毕之后的最高高度。

$N \le 20000, D,S \le 1000$

### Solution

~~双倍经验：SP1741（话说为什么一个蓝一个紫）~~

标记永久化线段树套线段树。

显然，立方体最终停留的位置的最高高度是其平面上的投影形成的矩形当中的最大高度加上其本身的高度。

于是我们需要实现一个支持二维区间修改和二维RMQ的数据结构。

很容易想到~~四分树~~线段树套线段树。

具体的，外层线段树维护 $x$ 轴，内层线段树维护 $y$ 轴。

对于一个外层线段树的结点，设它表示的区间为 $[L,R]$，则这个结点上维护的就是第 $L$ 列到第 $R$ 列之间的最大值。

由于此处标记不方便下传（若外层树下传标记将会导致整个区间被赋值），因此考虑标记永久化。

另外这道题维护的是平面上的面不是点，因此所有坐标 $+1$（正好规避了这道题的坐标 $=0$ 的情况）。

时间复杂度 $\Theta(n \log D \log S)$。

### Code

```cpp
#include<cstdio>
#include<algorithm>
const int M=1e3+5;
inline int read(){int x(0),op(0);char ch=getchar();while(ch<'0'||ch>'9')op|=(ch==45),ch=getchar();while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();return op?-x:x;}
int n,m,q;
namespace SGTinSGT{
    #define ls (p<<1)
    #define rs ((p<<1)|1)
    #define mid ((s+t)>>1)
    struct SGT{//内层线段树
        int T[M<<2],tag[M<<2];
        void modify(int l,int r,int x,int p=1,int s=1,int t=m){//虽然这里打成n也能过，但是要养成好习惯（滑稽
            T[p]=std::max(T[p],x);
            if(l<=s&&t<=r){
                tag[p]=std::max(x,tag[p]);
                return;
            }
            if(l<=mid)modify(l,r,x,ls,s,mid);
            if(r>mid)modify(l,r,x,rs,mid+1,t);
        }
        int query(int l,int r,int p=1,int s=1,int t=m){
            if(l<=s&&t<=r)return T[p];
            int ans=tag[p];
            if(l<=mid)ans=std::max(query(l,r,ls,s,mid),ans);
            if(r>mid)ans=std::max(query(l,r,rs,mid+1,t),ans);
            return ans;
        }
    }T[M<<2],tag[M<<2];
    //外层线段树
    void modify(int l,int r,int d,int u,int x,int p=1,int s=1,int t=n){
        T[p].modify(d,u,x);
        if(l<=s&&t<=r){
            tag[p].modify(d,u,x);
            return;
        }
        if(l<=mid)modify(l,r,d,u,x,ls,s,mid);
        if(r>mid)modify(l,r,d,u,x,rs,mid+1,t);
    }
    int query(int l,int r,int d,int u,int p=1,int s=1,int t=n){
        if(l<=s&&t<=r)return T[p].query(d,u);
        int ans=tag[p].query(d,u);
        if(l<=mid)ans=std::max(query(l,r,d,u,ls,s,mid),ans);
        if(r>mid)ans=std::max(query(l,r,d,u,rs,mid+1,t),ans);
        return ans;
    }
}
int main(){
    n=read(),m=read(),q=read();
    while(q--){
        int d=read(),s=read(),w=read(),x=read(),y=read();
        int add=SGTinSGT::query(x+1,x+d,y+1,y+s)+w;
        SGTinSGT::modify(x+1,x+d,y+1,y+s,add);
    }
    printf("%d\n",SGTinSGT::T[1].query(1,n));
    return 0;
}
```



---

