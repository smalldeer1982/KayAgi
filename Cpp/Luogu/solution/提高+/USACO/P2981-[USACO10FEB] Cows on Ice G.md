# [USACO10FEB] Cows on Ice G

## 题目描述

Bessie is ice skating on a large frozen lake modelled as a 2-dimensional grid with coordinates in the range -1,000,000,000..1,000,000,000. N (1 <= N <= 20,000) of the lake's grid cells contain rocks

(conveniently numbered 1..N). The other cells contain slippery ice.

Since Bessie is not a very good skater, she traverses the lake's cells by pushing herself away from her current position near a rock and sliding continuously in the same direction until she hits another rock (stopping in the square before she hits the rock, of course). Never good with complicated angles, Bessie can push herself only straight north, east, south, or west. She can't push herself through the rock, of course, and thus generally has only three possible directions to move.

Sliding is not without risks. Bessie must hit a rock or might end up sliding for a very long time. She must aim her pushes carefully.

Consider the situation depicted below; Bessie wants to get to

location (x=5,y=1), which is east of her current location (. = ice, \* = rock, B = Bessie, G = goal). If she slides directly to the east, she will slide past the location since she can stop only by

encountering a rock head on. One way to get to (5,1) is the following:

(a)              (b)             (c)              (d) 

4 .....\*.         .....\*.         .....\*.          .....\*.

3 ..\*....  slide  ..\*....  slide  ..\*....   slide  ..\*....

2 ......\*  north  ..B...\*  east   .....B\*   south  ......\*

1 .\*B..G. ------> .\*...G. ------> .\*...G.  ------> .\*...B.

0 \*....\*.         \*....\*.         \*....\*.          \*....\*.

0123456

Bessie could slide north, east, or south in situation (a), but only north has a rock for stopping. For situation (b), she can slide only east for the same reason.

For the input, rock i is located at cell X\_i,Y\_i (-1,000,000,000 <= X\_i <= 1,000,000,000; -1,000,000,000 <= Y\_i <= 1,000,000,000), and no two rocks occupy the same position. Bessie starts at Bx,By (which is next to a rock) (-1,000,000,000 <= Bx <= 1,000,000,000; -1,000,000,000 <= By <= 1,000,000,000). Bessie's goal is Gx,Gy (-1,000,000,000 <= Gx <= 1,000,000,000; -1,000,000,000 <= Gy <= 1,000,000,000). Bessie can always reach the goal one way or another.

Bessie doesn't mind sliding. However, pushing herself away from a rock is very tiring. To prepare her, FJ would like to know the minimum number of pushes Bessie needs to do.

Bessie 在一个冰封的湖面上游泳，湖面可以表示为二维的平面，坐标范围是-1,000,000,000..1,000,000,000。湖面上的N(1 <= N <= 20,000)个位置有石块(编号分别为1到N)，其它位置是冰面。由于Bessie滑冰技术不够好，她通过推动自己旁边的石块，依靠反作用力向某一个方向前进，在碰到一个新的石块之前，Bessie是不会停下来的。(当然，最后会停留在某块石块的前一个格子里)由于Bessie无法计算复杂的角度，她只能够向东南西北四个方向前进。

很显然，Bessie不能够穿越石块，因此，Bessie仅仅可以向三个方向滑。 滑冰不是没有风险，Bessie滑向某个方向后必须能碰到某个石块，因此她必须很小心。考虑下面的一个情况，Bessie希望到达在她东面的目标位置(x=5,y=1)，(…


## 样例 #1

### 输入

```
6 2 1 5 1 
5 4 
2 3 
1 1 
6 2 
5 0 
0 0 
```

### 输出

```
3 
```

# 题解

## 作者：鹭天 (赞：5)

### [题目传送门](https://www.luogu.org/problemnew/show/P2981)
## 题目描述：
Bessie 在一个冰封的湖面上游泳，湖面可以表示为二维的平面，坐标范围是-1,000,000,000..1,000,000,000。

湖面上的N(1 <= N <= 20,000)个位置有石块(编号分别为1到N)，其它位置是冰面。

由于Bessie滑冰技术不够好，她通过推动自己旁边的石块，依靠反作用力向某一个方向前进，在碰到一个新的石块之前，Bessie是不会停下来的。(当然，最后会停留在某块石块的前一个格子里)由于Bessie无法计算复杂的角度，她只能够向东南西北四个方向前进。

很显然，Bessie不能够穿越石块，因此，Bessie仅仅可以向三个方向滑。
滑冰不是没有风险，Bessie滑向某个方向后必须能碰到某个石块，因此她必须很小心。

  考虑下面的一个情况，Bessie希望到达在她东面的目标位置(x=5,y=1)，(. = 冰块,* = 石头, B = Bessie, G = 目的位置)如果她直接向东滑，那么她会滑过目标位置，因为她通过撞上某块石头来停下来，一个能够到达目标位置的方案是这样的：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190330152944387.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2h1YW5nX2tlX2hhaQ==,size_16,color_FFFFFF,t_70)
在(a)中，Bessie 只能朝向北，东，或者南三个方向，但是只有在北面能撞上石头从而停下来，在(b)中，类似地，她只能向东走。

对于输入，石头 i位于坐标为X_i,Y_i的位置，(-1,000,000,000<= X_i <= 1,000,000,000; -1,000,000,000 <= Y_i <= 1,000,000,000)，没有任何两块石头位于同一个位置，Bessie从Bx,By的位置出发(出发点一定与某个石头相邻)，Bessie的目标位置是Gx,Gy(-1,000,000,000 <= Gx <= 1,000,000,000; -1,000,000,000 <= Gy <=1,000,000,000).

Bessie 并不介意长时间滑冰，但是，不停地推石头依靠反作用力前进很累。FJ 非常关心Bessie的健康，因此他希望知道Bessie最少要推多少次石头才能到达终点。
***
## 分析：
这题的最主要思路就是找到每一行每一列的石头个数，只要能找到石头，我们就能确定滑动后到达的位置。那么，这个时候，我们就可以写**12个二分**来解决这个问题（当然是假的。。），不过12个二分代码量有点大，我们考虑如何改进。

其实可以用 $set$ 和 $map$ 优化

$set$是将每一行所对应石头的坐标进行存储
$map$是将每一个set所对应的步数记录下来

其实就是一个$map$ 套 $set$ 的过程

我们用了stl之后，二分的内容便可以省略，因为stl之中是自带二分的。

* 如何在 $set$ 和 $map$ 中进行二分查找呢？
1、 对诸如set、map这种关键字唯一的集合而言，lower_bound、upper_bound返回迭代器是相同，关键字val在集合中不存在，二者返回结果一样，都是按照集合实例化时给定的Compare比较，不在val之前的第一个元素（亦即之后或者等于，如果按照默认的比较类型less，函数返回的是≥val的最小的元素）；
2. 如果关键在val在集合中存在，lower_bound返回val关键字本身的迭代器，upper_bound返回关键字val下一个元素迭代器。
3. 按照关键字后面一个关键字在集合中出现的次数可分为：关键字val出现在集合中，但是是唯一的，这种情况和set、map情况类似；
4. 关键字val出现在集合中，出现多次，这种情况下lower_bound返回第一个出现关键字val对应的迭代器，upper_bound返回位于关键字val对应位置后第一个不是val的位置的迭代器；关键字val不在集合中，这种情况下与set、map一致。

**综合一下：lower_bound、upper_bound函数不管在什么情况下，以下条件均成立：
Iterator(val)≤Iterator(lower_bound)≤Iterator(upper_bound)
也就是lower_bound、upper_bound构成的上下限的区间总是表示一个有效的迭代器区间（equal_range返回值），该迭代区间的长度表示关键字val在集合中出现的次数。**

好，下面开始正式分析：
因为题目给的坐标大小非常大，但是石头却最多只有20000个，所以我们可以从石头入手。
用map建立一个映射关系，来进行离散化石头的坐标即可。

而set中的集合是默认从小到大排序，所以这样也复合了二分查找的性质，我们也可以用系统自带的二分查找来查询最近的石头即可。

* 如何寻找石头的位置？？
这里给一个往上查找的例子：

```cpp
node go_up(node k){
    set<int> y=rock_x[k.fi];//找到相应的列
    it=y.upper_bound (k.se) ;//找到石头
    if (it==y.end()||(*it)-k.se<=1) return b;//不符合情况
    return node(k.fi,(*it)-1);//返回
}
```

bfs其实就是裸的bfs，主要是查找麻烦。

***
# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
typedef pair<int , int > node; 
int n;
map < int , set < int > > rock_x;
map < int , set < int > > rock_y;
queue < node > q;
map < node , int > dis;
node b,g;
set < int > :: iterator it;//表示是复制的来的 
node go_up(node k){
    set<int> y=rock_x[k.fi];
    it=y.upper_bound (k.se) ;
    if (it==y.end()||(*it)-k.se<=1) return b;
    return node(k.fi,(*it)-1);
}//往上查找
node go_down(node k){
    set<int> y=rock_x[k.fi];
    it=y.upper_bound (k.se) ;
    if (it==y.begin()||(k.se-(*(--it))<=1)) return b;
    return node(k.fi,(*it)+1);
}//往下查找
node go_left(node k){
    set<int> x=rock_y[k.se];
    it=x.upper_bound (k.fi) ;
    if (it==x.begin()||(k.fi-(*(--it))<=1)) return b;
    return node((*it)+1,k.se);
}//往左查找
node go_right(node k){
    set<int> x=rock_y[k.se];
    it=x.upper_bound (k.fi) ;
    if (it==x.end()||((*it)-k.fi<=1)) return b;
    return node((*it)-1,k.se);
}//往右查找
int main(){
	freopen("ice..in","r",stdin);
	freopen("ice..out","w",stdout);
	scanf("%d %d %d %d %d",&n,&b.fi,&b.se,&g.fi,&g.se);
    for (int i=1,x,y;i<=n;i++)
      scanf("%d %d",&x,&y),rock_x[x].insert(y),rock_y[y].insert(x);//建立每一个石头的行列的索引
    q.push(b);
    dis[b]=0;
    while (!q.empty()){
	    node x=q.front();
	    q.pop();
	    node xx;
	    xx=go_up(x);
	    if (xx!=b&&!dis[xx]) q.push(xx),dis[xx]=dis[x]+1;
	    xx=go_down(x);
	    if (xx!=b&&!dis[xx]) q.push(xx),dis[xx]=dis[x]+1;
	    xx=go_left(x);
	    if (xx!=b&&!dis[xx]) q.push(xx),dis[xx]=dis[x]+1;
	    xx=go_right(x);
	    if (xx!=b&&!dis[xx]) q.push(xx),dis[xx]=dis[x]+1;
	    if (dis[g]) break;
	}//bfs查找过程
	printf("%d",dis[g]);//输出
	fclose(stdin);
	fclose(stdout);
	return 0;
}

```
# [请大家支持我](https://blog.csdn.net/huang_ke_hai)


---

## 作者：pocafup (赞：2)

楼上的思路都是从一个石头找跳到另一个石头的路径,但其实这题可以对于上下左右四个方向分别做一个虚拟节点,然后只需要找虚拟节点左边的虚拟节点就行了

问题是:不会用set怎么办???

其实可以发现用vector二分可以实现同样的操作(~~虽然长得不行而且还各种wa~~)

vector存图的方法:

分别存下x和y方向的石头,然后用vec_x和vec_y存四个方向的虚拟节点

作为一个懒人,负数是最大的折磨.将每个点加上1e9能有效避免负数

然后,对每个方向判断一次左边最多能走到多远.这里是往上的判断

```cpp
long long find_up(long long x, long long y){
  string going = to_string(x);
  if (!mp_horizontal[going].size()) return -1; //这里面没东西
  if (!sorted_hori[going]) {sort(mp_horizontal[going].begin(),mp_horizontal[going].end());sorted_hori[going] = true;}//先把他排序才能二分
  long long le = 0, ri = mp_horizontal[going].size()-1;
  while(le<ri-1){
    long long mid = (le+ri)/2;
    if (mp_horizontal[going][mid]<=y) le = mid;
    else ri = mid;
  }//裸的二分
  if (mp_horizontal[going][le]>y && !between_y(mp_horizontal[going][le],y,going)) return mp_horizontal[going][le];
  if (mp_horizontal[going][ri]>y && !between_y(mp_horizontal[going][ri],y,going)) return mp_horizontal[going][ri];
  return -1;//between_y是查找两点之间是否有石头
}
```
现在来讲讲between_y.between_y的意义是确认虚拟节点之间不会有石头.这里我们同样用二分实现
以下是between_y,between_x同理
```cpp
bool between_y(long long l, long long r, string ptr){
  string going = ptr;
  if (!stone_x[going].size()) return false;//没东西
  if (l>r) swap(l,r);
  if (!sorted_x[going]) {sort(stone_x[going].begin(),stone_x[going].end());sorted_x[going] = true;}
  long long le = 0, ri = stone_x[going].size()-1;

  while(le<ri-1){
    long long mid = (le+ri)/2;

    if (between(l,r,stone_x[going][mid])) return true;
    if (r>stone_x[going][mid]) le = mid;//二分
    else ri = mid;
  }
  return between(l,r,stone_x[going][le])||between(l,r,stone_x[going][ri]);//between定义为比left大且比right小
}
```

注意这题由于是map和vector存图,unordered_map也是一个不错的选择

完整代码:
```cpp
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
#define pp pair<long long,long long>
#define f first
#define s second
long long n,sx,sy,ex,ey;
vector<int> vec_x,vec_y,st_x,st_y;
unordered_map<string, bool> sorted_x,sorted_y,sorted_hori,sorted_vert;
unordered_map<string,vector<long long> > mp_vertical,mp_horizontal,stone_x,stone_y;
unordered_map<string,long long> vis;
bool between(long long x, long long y, long long ptr){
  return x<=ptr && y>=ptr;
}//就是懒得每次都这么打
bool between_x(long long l, long long r, string ptr){
  string going = ptr;
  if (!stone_y[going].size()) return false;
  if (l>r) swap(l,r);
  if (!sorted_y[going]) {sort(stone_y[going].begin(),stone_y[going].end());sorted_y[going] = true;}
  long long le = 0, ri = stone_y[going].size()-1;
  while(le<ri-1){
    long long mid = (le+ri)/2;
    if (between(l,r,stone_y[going][mid])) return true;
    if (r<stone_y[going][mid]) ri = mid;
    else le = mid;
  }
  return between(l,r,stone_y[going][le])||between(l,r,stone_y[going][ri]);
}//注意between_x是指y不变,所以这里要用stone_y.
bool between_y(long long l, long long r, string ptr){
  string going = ptr;
  if (!stone_x[going].size()) return false;
  if (l>r) swap(l,r);
  if (!sorted_x[going]) {sort(stone_x[going].begin(),stone_x[going].end());sorted_x[going] = true;}
  long long le = 0, ri = stone_x[going].size()-1;

  while(le<ri-1){
    long long mid = (le+ri)/2;

    if (between(l,r,stone_x[going][mid])) return true;
    if (r>stone_x[going][mid]) le = mid;
    else ri = mid;
  }
  return between(l,r,stone_x[going][le])||between(l,r,stone_x[going][ri]);
}//y方向查找
long long find_up(long long x, long long y){
  string going = to_string(x);
  if (!mp_horizontal[going].size()) return -1;
  if (!sorted_hori[going]) {sort(mp_horizontal[going].begin(),mp_horizontal[going].end());sorted_hori[going] = true;}
  long long le = 0, ri = mp_horizontal[going].size()-1;
  while(le<ri-1){
    long long mid = (le+ri)/2;
    if (mp_horizontal[going][mid]<=y) le = mid;
    else ri = mid;
  }
  if (mp_horizontal[going][le]>y && !between_y(mp_horizontal[going][le],y,going)) return mp_horizontal[going][le];
  if (mp_horizontal[going][ri]>y && !between_y(mp_horizontal[going][ri],y,going)) return mp_horizontal[going][ri];
  return -1;
}//往上
long long find_down(long long x, long long y){
  string going = to_string(x);
  if (!mp_horizontal[going].size()) return -1;
  if (!sorted_hori[going]) {sort(mp_horizontal[going].begin(),mp_horizontal[going].end());sorted_hori[going] = true;}
  long long le = 0, ri = mp_horizontal[going].size()-1;
  while(le<ri-1){
    long long mid = (le+ri)/2;
    if (mp_horizontal[going][mid]>=y) ri = mid;
    else le = mid;
  }
  if (mp_horizontal[going][ri]< y && !between_y(mp_horizontal[going][ri],y,going)) return mp_horizontal[going][ri];
  if (mp_horizontal[going][le]<y  && !between_y(mp_horizontal[going][le],y,going)) return mp_horizontal[going][le];
  return -1;
}//往下
long long find_left(long long x, long long y){
  string going = to_string(y);
  if (!mp_vertical[going].size()) return -1;
  if (!sorted_vert[going]) {sort(mp_vertical[going].begin(),mp_vertical[going].end());sorted_vert[going] = true;}
  long long le = 0, ri = mp_vertical[going].size()-1;
  while(le<ri-1){
    long long mid = (le+ri)/2;
    if (mp_vertical[going][mid]>=x) ri = mid;
    else le = mid;
  }
  if (mp_vertical[going][ri]<x && !between_x(x,mp_vertical[going][ri],going)) return mp_vertical[going][ri];
  if (mp_vertical[going][le]<x && !between_x(x,mp_vertical[going][le],going)) return mp_vertical[going][le];
  return -1;
}//往左
long long find_right(long long x, long long y){
  string going = to_string(y);
  if (!mp_vertical[going].size()) return -1;
  if (!sorted_vert[going]) {sort(mp_vertical[going].begin(),mp_vertical[going].end());sorted_vert[going] = true;}
  long long le = 0, ri = mp_vertical[going].size()-1;
  while(le<ri-1){
    long long mid = (le+ri)/2;
    if (mp_vertical[going][mid]<=x) le = mid;
    else ri = mid;
  }
  if (mp_vertical[going][le]>x && !between_x(x,mp_vertical[going][le],going)) return mp_vertical[going][le];
  if (mp_vertical[going][ri]>x && !between_x(x,mp_vertical[going][ri],going)) return mp_vertical[going][ri];
  return -1;
}//往右
void find_all(int x ,int y){
  cout << find_up(x,y) << " " << find_down(x,y) << " " << find_left(x,y) << " " << find_right(x,y) << endl;
}//这是我自己用来测试的程序
int main(){
  scanf("%lld%lld%lld%lld%lld",&n,&sx,&sy,&ex,&ey);
  sx+=1e9;sy+=1e9;ex+=1e9;ey+=1e9;
  for (long long i=0;i<n;i++){
    long long a,b;scanf("%lld%lld",&a,&b);
    a+=1e9;b+=1e9;
    stone_x[to_string(a)].push_back(b);
    stone_y[to_string(b)].push_back(a);//将石头的状态分别计入map中
    if (a-1>=0) mp_vertical[to_string(b)].push_back(a-1);
    mp_vertical[to_string(b)].push_back(a+1);vec_x.push_back(a+1);
    if (b-1>=0) mp_horizontal[to_string(a)].push_back(b-1);
    mp_horizontal[to_string(a)].push_back(b+1);
    //建立虚拟节点(其实a-1这些不要都无所谓了)
  }
  queue<pp> q;
  q.push(make_pair(sx,sy));
  vis[to_string(sx)+"?"+to_string(sy)] = 0;
  while(!q.empty()){
    long long qf = q.front().f, qs = q.front().s; q.pop();
    long long prev = vis[to_string(qf)+"?"+to_string(qs)];
    if (qf==ex && qs==ey) {cout << prev;return 0;}
    long long le = find_left(qf,qs), ri = find_right(qf,qs), up = find_up(qf,qs), down = find_down(qf,qs);
    if (le!=-1){
      if (!vis[to_string(le)+"?"+to_string(qs)] && (le!=sx || qs!=sy)){
        vis[to_string(le)+"?"+to_string(qs)] = prev+1;
        q.push(make_pair(le,qs));
      }//能往左并且左边的点没拿过
    }
    if (ri!=-1){
      if (!vis[to_string(ri)+"?"+to_string(qs)] && (ri!=sx || qs!=sy)){
        vis[to_string(ri)+"?"+to_string(qs)] = prev+1;
        q.push(make_pair(ri,qs));
      }//能往右并且右边的点没拿过
    }
    if (up!=-1){
      if (!vis[to_string(qf)+"?"+to_string(up)] && (qf!=sx || up!=sy)){
        vis[to_string(qf)+"?"+to_string(up)] = prev+1;
        q.push(make_pair(qf,up));
      }//能往上并且上边的点没拿过
    }
    if (down!=-1){
      if (!vis[to_string(qf)+"?"+to_string(down)] && (qf!=sx || down!=sy)){
        vis[to_string(qf)+"?"+to_string(down)] = prev+1;
        q.push(make_pair(qf,down));
      }//能往下并且下面的点没拿过
    }
  }
}
```

其实这个代码意义不算很大(毕竟确实又臭又长).这就是一个参考,如果会用set建议使用楼上的方法.

顺便留下一组毒瘤数据造福后人

```cpp
/*
9
0 0 -2 -3
-3 0
-2 -2
-3 -3
-1 -3
-1 -4
-2 -4
-3 -4
-2 -5
0 -3*/
```
p.s这组数据无解(虽然原题不会出现,但可以测试一下)


---

## 作者：小周猪猪 (赞：2)

## Problem
题目描述
Bessie 在一个冰封的湖面上游泳，湖面可以表示为二维的平面，坐标范围是-1,000,000,000..1,000,000,000。

湖面上的N(1 <= N <= 20,000)个位置有石块(编号分别为1到N)，其它位置是冰面。

由于Bessie滑冰技术不够好，她通过推动自己旁边的石块，依靠反作用力向某一个方向前进，在碰到一个新的石块之前，Bessie是不会停下来的。(当然，最后会停留在某块石块的前一个格子里)由于Bessie无法计算复杂的角度，她只能够向东南西北四个方向前进。

很显然，Bessie不能够穿越石块，因此，Bessie仅仅可以向三个方向滑。

滑冰不是没有风险，Bessie滑向某个方向后必须能碰到某个石块，因此她必须很小心。

考虑下面的一个情况，Bessie希望到达在她东面的目标位置(x=5,y=1)，(. = 冰块,* = 石头, B = Bessie, G = 目的位置)如果她直接向东滑，那么她会滑过目标位置，因为她通过撞上某块石头来停下来，一个能够到达目标位置的方案是这样的：


   (a)              (b)             (c)              (d)

4 .....*.         .....*.         .....*.          .....*.

3 ..*....  slide  ..*....  slide  ..*....   slide  ..*....

2 ......*  north  ..B...*  east   .....B*   south  ......*

1 .*B..G. ------> .*...G. ------> .*...G.  ------> .*...B.

0 *....*.         *....*.         *....*.          *....*.

0123456
在(a)中，Bessie 只能朝向北，东，或者南三个方向，但是只有在北面能撞上石头从而停下来，在(b)中，类似地，她只能向东走。

对于输入，石头 i位于坐标为X_i,Y_i的位置，(-1,000,000,000<= X_i <= 1,000,000,000; -1,000,000,000 <= Y_i <= 1,000,000,000)，没有任何两块石头位于同一个位置，Bessie从Bx,By的位置出发(出发点一定与某个石头相邻)，Bessie的目标位置是Gx,Gy(-1,000,000,000 <= Gx <= 1,000,000,000; -1,000,000,000 <= Gy <=1,000,000,000).

Bessie 并不介意长时间滑冰，但是，不停地推石头依靠反作用力前进很累。FJ 非常关心Bessie的健康，因此他希望知道Bessie最少要推多少次石头才能到达终点。

## 题目大意
奶牛要从起点到终点，每次要在某一个石头附近朝上下左右的某一个方向走到另外的一个石头附近。求拐弯方向-1。

## Solution
广搜是十分容易想到的，我们需要根据每一个节点进行扩展。

这一道题的难点就是如何找到某一个坐标上下左右离它最近的石头：
- 上：在y坐标相等，且小于当前x坐标的情况下，有x坐标最大所对应的点。
- 下：在y坐标相等，且大于当前x坐标的情况下，有x坐标最小所对应的点。
- 左：在x坐标相等，且小于当前y坐标的情况下，有y坐标最大所对应的点。
- 右：在x坐标相等，且大于当前y坐标的情况下，有y坐标最小所对应的点。

这需要二分查找，为了方便计算我们可以使用STL的set和map来解决。

由于坐标比较大，我们可以使用map来建立映射关系，对于行，定义一份集合set来存储这一行的所有纵坐标；同理，对于每一列，存储所有的横坐标；然后我们在找的时候，直接在set上进行二分查找即可。

在二分查找的时候注意判断是否有解。

代码比较长，但是思路还是很清晰的。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <map>
#include <set>
#include <cmath>
#include <limits.h>
#include <queue>

#define pos pair<int,int>
#define x first
#define y second

using namespace std;

int n,bx,by,gx,gy;
struct node
{
	int x,y,v;
};
map < pos, bool > v;
map < int, set<int> > map_x,map_y;
set <int> ::iterator it;
pos no_ans;
queue< node > q;

pos find_up(pos now)
{
	set <int> temp=map_y[now.y];
	it=temp.lower_bound(now.x);
	if (it==temp.begin()) return no_ans;
	it--;
	if (abs(*it-now.x)<=1) return no_ans;
	return pos{*it+1,now.y};
}
//查找点now上面的点
//纵坐标相同 横坐标小于now_x

pos find_down(pos now)
{
	set <int> temp=map_y[now.y];
	it=temp.upper_bound(now.x);
	if (it==temp.end()) return no_ans;
	if (abs(*it-now.x)<=1) return no_ans;
	return pos{*it-1,now.y};
} 
//查找点now下面的点
//纵坐标相同 横坐标大于now_y 

pos find_left(pos now)
{
    set <int> temp=map_x[now.x];
	it=temp.lower_bound(now.y);
	if (it==temp.begin()) return no_ans;
	it--;
	if (abs(*it-now.y)<=1) return no_ans;
	return pos{now.x,*it+1};	
}
//查找点now左边的点
//横坐标相同 纵坐标小于now_y 

pos find_right(pos now)
{
	set <int> temp=map_x[now.x];
	it=temp.upper_bound(now.y);
	if (it==temp.end()) return no_ans;
	if (abs(*it-now.y)<=1) return no_ans;
	return pos{now.x,*it-1}; 
} 
//查找点now右边的点
//纵坐标相同 横坐标大于now_x
 
int main(void)
{
	freopen("ice..in","r",stdin);
	freopen("ice..out","w",stdout);
	cin>>n>>bx>>by>>gx>>gy;
	for (int i=1;i<=n;++i)
	{
		int x,y;
		cin>>x>>y;
		map_x[x].insert(y);
		//map_x表示第x行对应的所有y坐标 
		map_y[y].insert(x);
		//map_y表示第y行对应的所有x坐标 
	}
	no_ans=pos{INT_MAX,-INT_MAX};//无解状态 
	q.push(node{bx,by,0});
	pos st;
	st=pos{bx,by};
	v[st]=1;
	while (q.size())
	{
		node top=q.front();
		q.pop();
		if (top.x==gx && top.y==gy) 
		    return cout<<top.v,0; 
		//到达终点 
		pos now;
		//初始化和边界
		now=find_up(pos{top.x,top.y});
		if (!v[now] && now!=no_ans)
		{
			v[now]^=1;
			q.push(node{now.x,now.y,top.v+1});
		}
		//向上搜索
		now=find_down(pos{top.x,top.y});
		if (!v[now] && now!=no_ans)
		{
			v[now]^=1;
			q.push(node{now.x,now.y,top.v+1});
		}
		//向下搜索
		now=find_left(pos{top.x,top.y});
		if (!v[now] && now!=no_ans)
		{
			v[now]^=1;
			q.push(node{now.x,now.y,top.v+1});
		}
		//向左搜索
		now=find_right(pos{top.x,top.y});
		if (!v[now] && now!=no_ans)
		{
			v[now]^=1;
			q.push(node{now.x,now.y,top.v+1});
		} 
		//向右搜索
	} 
	return 0;
}
```


---

