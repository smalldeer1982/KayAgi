# [USACO12DEC] Crazy Fences S

## 题目描述

After visiting a modern art museum, Farmer John decides to re-design his farm by moving all of the N (1 <= N <= 1000) fences between his pastures! Each fence is describe by a line segment in the 2D plane.  If two fences meet, they do so only at their endpoints.  Each fence touches exactly two other fences, one at both endpoints.

FJ has C cows (1 <= C <= 1000) on his farm.  Each cow resides at a point in the 2D plane that is not on any fence, and no two cows reside at the same point.  Two cows are said to be in the same community if one could walk to the other without touching any fences.  Please help FJ determine the size of the largest community.

 
在访问了一个现代美术馆后，约翰农夫决定移动n个在他的牧场之间的栅栏来


重新设计他的农场。每个栅栏用一个2D平面的线段来描述。两个栅栏只有在他们的端点才会相遇。每个栅栏在两个端点接触其他的两个栅栏。


约翰农夫有c头牛在他的农场。每头牛住在2D平面的不在任何栅栏的一个点，并且没有两头牛在同一个点。如果两头牛可以不接触任何栅栏地走到一起，他们就是在同一个社区。请确定最大的社区的牛的数量。


## 说明/提示

There are 10 fences and 4 cows.  The fences form a square containing two triangles.


Cows #2 and #4 belong to the same community.  Cows #1 and #3 are each members of a community of size 1.


感谢@kczno1 提供翻译


## 样例 #1

### 输入

```
10 4 
0 0 10 0 
10 0 10 10 
0 0 0 10 
10 10 0 10 
8 8 9 8 
9 8 8 9 
8 9 8 8 
2 7 3 2 
3 2 7 5 
7 5 2 7 
15 3 
1 4 
4 5 
7 1 
```

### 输出

```
2 
```

# 题解

## 作者：pocafup (赞：4)


做完发现居然没有大神发题解，那么本大(ju)神(ruo）大胆来发布一篇。

# 
这道题的思想是首先我们找到所有的栅栏围成的空间，然后求每一只奶牛在哪几个栅栏空间之中，最后比较他们在的所有栅栏空间-----如果奶牛a和b同时在空间c，d和e内，那么他们一定在同一群中。
# 
测试围栏的方法：对于每个栅栏，如果没有被查过，就将其放入队列。然后根据这个数把所有有相同点的栅栏放入队列并将visited设成true。
# 
测试每一只牛所在的空间的方法：对于牛B和栅栏组C，如果从B往下走碰到了奇数次栅栏，那么B一定在栅栏C的空间内。（第一次发题解实在不知道怎么发图请见谅）
# 
测试牛是否碰到栅栏组中某一栅栏的方法：对于牛B和栅栏组C中的栅栏D，如果牛B的x坐标在栅栏D的坐标之间，且牛B的Y值大于栅栏D在牛B的x坐标这个点上的时候的Y值，那么牛B一定在栅栏D之上
# 
测试栅栏D在牛B的x坐标的Y值：对于栅栏D，斜率等于(y2-y1)/(x2-x1)，在x时的坐标为 【斜率*（牛B的x值-栅栏D的第一个点的x值）+栅栏D的第一个点的y值】，也就是说： cowy>=slope*(cowx-x1)+y1
# 
求两头牛是否在同一族群：现在我们有了每一头牛所在的族群（我将它放在vec里面）。求两头牛是否在同一族群的方法是如果两头牛所在的族群的数量和编号都相同，那么这两头牛在同一族群内
#
上代码
#
*****注：本蒟蒻非常反感抄袭。因为这些抄袭者是完全一字不改的抄下来，这个是在我看来不可行的。所以我特地在中间抽掉了一行（非常简单的一行）。我相信想做这题的人对于补全这行不会有问题。对于造成的不便，敬请谅解
#
```cpp

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>
using namespace std;
bool visited[1001];
bool vis[1001];
pair< pair<int,int>, pair<int,int> > pos[1001]; //所有fence的起始点和结束点
pair<int,int> cows[1001];//奶牛的地点
bool check(pair< pair<int,int>, pair<int,int> > fir, pair< pair<int,int>, pair<int,int> > sec){
  return ((fir.first.first == sec.first.first && fir.first.second == sec.first.second) ||
          (fir.second.first == sec.first.first && fir.second.second == sec.first.second)||
          (fir.first.first == sec.second.first && fir.first.second == sec.second.second) ||
          (fir.second.first == sec.second.first && fir.second.second == sec.second.second));
}//测试两个fence有没有共同点
int main(){
  vector<pair< pair<int,int>, pair<int,int> > > vec[1000];//记录有几个群
  int a,b; cin >> a >> b;
  for (int i=0;i<a;i++) cin >> pos[i].first.first >> pos[i].first.second >> pos[i].second.first >> pos[i].second.second;
  for (int i=0;i<b;i++)cin >> cows[i].first >> cows[i].second;
  int zz = 0;
  queue<int> q;
  //visited找没有经过的地点放进队列
  //如果遇到没有经过并且有相同点的地方就放入队列，并将visited改成true
  for (int i=0;i<a;i++){//测试每个点
    if (!visited[i]){
      visited[i] = true;
      vec[zz].push_back(pos[i]);
      q.push(i);
      while(!q.empty()){//当队列中有东西
        pair< pair<int,int>, pair<int,int> > temp1 = pos[q.front()];
        for (int j=0;j<a;j++){
          pair< pair<int,int>, pair<int,int> > temp2 = pos[j];
          if (!visited[j]){
            if (check(temp1,temp2)){//测试是否有共同点
                  q.push(j);
                  visited[j] = true;
                  vec[zz].push_back(pos[j]);
                }
            }
          }
          //这里我拿掉了一行程序（反抄袭请谅解）
          //如果想填请认真看while里面缺什么。我相信会做这题的人都可以写的出来这行
      }
      zz++;//群数+1
    }
  }
  vector<int> myvec[1001];
  for (int i=0;i<b;i++){
    for (int j=0;j<zz;j++){
      int edge = 0; //设置碰到的边缘的数量为0
      for (int k=0;k<vec[j].size();k++){
        double x1 = vec[j][k].first.first;
        double y1 = vec[j][k].first.second;
        double x2 = vec[j][k].second.first;
        double y2 = vec[j][k].second.second;
        //这四行是为了找栅栏的起始点和终点
        double cowx = cows[i].first;
        double cowy = cows[i].second;
        //奶牛的位置
        double slope = (y2-y1) / (x2-x1);//斜率
        bool cond1 = x1<=cowx && cowx<x2;
        bool cond2 = x2<=cowx && cowx<x1;
        //测试奶牛位置是否在两个栅栏的中间
        bool above1 = (cowy >= slope * (cowx-x1) + y1); //测试奶牛是否在栅栏之上
        if ((cond1^cond2) && above1) edge++;//如果奶牛位置在两栅栏之间，并且在栅栏之上，证明奶牛会碰到这个栅栏
      }
      if (edge % 2 !=0){
        myvec[i].push_back(j);//如果是奇数，说明奶牛在这个栅栏内
      }
    }
  }
  int ans = 1;//最小可能每只牛都是独立的
  for (int i=0;i<b;i++){//每只牛测试
    int num = 1;
    if (vis[i]) continue;
    vis[i] = true;
    for (int j=i;j<b;j++){
      if (myvec[i].size() == myvec[j].size() && i!=j &&!vis[j]){
        bool n = true;
        for (int k=0;k<myvec[i].size();k++) if (myvec[i][k]!=myvec[j][k]) n = false;
        if (n){
          num++;//如果两个奶牛在的族群数量相同，那么他们在同一族群内
          vis[j]=true;
        }
      }
    }
    ans = max(ans,num);//最大奶牛数
  }
  cout << ans;
}




---

## 作者：Pretharp (赞：1)

## 题意

给定平⾯中多个不相交的简单多边形和⼀些点，求分割出的区域中包含的最多点数。

## 思路

由于给出的是⼀些⽆序线段，所以要先找到多边形。考虑到线段数量很少，所以可以每次从⼀个没有访问过的线段开始，不断枚举找相邻的线段，直到得到完整的多边形。这样就能找到所有的多边形。

然后需要知道多边形中包含了哪些点，可以使⽤射线法，让点发出的射线和多边形的每个线段求交，根据交点的奇偶性就能判断是否在多边形中。

但是我们不能知道找到包含点数最多的多边形，因为多边形中还有可能包含多边形，导致区域被进⼀步划分。对于两个点，只有包含这两个点的多边形集合完全相同，才能确保两个点在⼀个区域中。

为此，可以将点按照包含点的集合排序，再进⾏校验即可。

## 复杂度

### 时间

寻找多边形，边数 $O(N)$，寻找邻边 $O(N)$，总共 $O(N^2)$。
判断点和多边形线段交 $O(NC)$。
点⽐较 $O(N)$，排序 $O(NC\ \log\ C)$。
总时间复杂度为 $O(N^2+NC\ \log\ C)$。

### 空间

记录点线段交的情况 $O(NC)$。

## 代码

```cpp
#include <algorithm>
#include <array>
#include <fstream>

using namespace std;
using Pii = pair<int, int>;

const int kMaxN = 1001;
const Pii kP = {1, 1e6 + 1};

ifstream fin("crazy.in");
ofstream fout("crazy.out");

Pii operator-(const Pii &x, const Pii &y) { return {x.first - y.first, x.second - y.second}; }  // 向量减法

int operator*(const Pii &x, const Pii &y) {                           // 向量乘法
  long long v = 1LL * x.first * y.second - 1LL * x.second * y.first;  // 向量叉乘取正负
  return v < 0 ? -1 : v > 0;
}

struct E {     // 线段
  bool b;      // 处理标记
  Pii p0, p1;  // 端点
} e[kMaxN];

struct C {                                                // 点
  Pii p;                                                  // 坐标
  array<bool, kMaxN> b;                                   // 被多边形包含的标记
  bool operator<(const C &_c) const { return b < _c.b; }  // 按照包含标记排序
} c[kMaxN];

int n, m, ans;

bool C(Pii x, Pii y, Pii p, Pii q) {  // 判断xy和pq是否有交
  return ((y - x) * (p - x)) * ((y - x) * (q - x)) < 0 && ((q - p) * (x - p)) * ((q - p) * (y - p)) < 0;
}

int F(int x) {  // 寻找x接着的线段
  for (int i = 1; i <= n; i++) {
    if (i != x) {                // 不能接自己
      if (e[x].p1 == e[i].p1) {  // 交点在p1
        swap(e[i].p0, e[i].p1);  // 交换到p0
      }
      if (e[x].p1 == e[i].p0) {  // 有交点
        return i;                // 返回
      }
    }
  }
  return 0;
}

void W(int s) {                                      // 处理s开始的多边形
  for (int i = s; !e[i].b; i = F(i)) {               // 遍历每条边
    e[i].b = 1;                                      // 标记线段已处理
    for (int j = 1; j <= m; j++) {                   // 计算线段与所有点的交
      c[j].b[s] ^= C(c[j].p, kP, e[i].p0, e[i].p1);  // 有交点则切换奇偶性
    }
  }
}

int main() {
  fin >> n >> m;
  for (int i = 1; i <= n; i++) {
    fin >> e[i].p0.first >> e[i].p0.second >> e[i].p1.first >> e[i].p1.second;
  }
  for (int i = 1; i <= m; i++) {
    fin >> c[i].p.first >> c[i].p.second;
  }
  for (int i = 1; i <= n; i++) {  // 寻找多边形
    if (!e[i].b) {                // 新的多边形
      W(i);
    }
  }
  sort(c + 1, c + 1 + m);
  for (int i = 2, s = 1; i <= m; i++) {    // 遍历所有点
    s = c[i].b == c[i - 1].b ? s + 1 : 1;  // 包含标记相同则在同一个多边形中
    ans = max(ans, s);
  }
  fout << ans;
  return 0;
}
```

---

## 作者：Lovesaint_lym2010 (赞：0)

事实上这是一道数学题，看了题解区大佬的题解后也是会了，写一篇题解详细讲一下......
## $Part 0$ 前置知识
### $Part$ $ 0.1$ 两平面向量是否有交点
求两个平面向量 $( \{ x_1, y_1 \}, \{x_2, y_2 \})$ 和 $( \{ x_3, y_3 \}, \{x_4, y_4 \})$ 是否有交点。

方便起见，记两个向量为 $（A, B）$ 和 $(C, D)$。

两个平面向量的充分必要条件就是，$A, B$ 在 $(C, D)$ 所在直线 两侧 而且 $C, D$ 在 $(A, B)$ 所在直线的两侧。

举例说明：分辨 $C$ 与直线 $AB$ 的位置关系，首先计算叉乘
$$\vec{AB} \times \vec{AC} = (x_1 - x_3) \times (y_2 - y_3) - (x_2 - x_3) \times (y_2 - y_3)$$
记这个值为 $x$
- $x > 0$，$C$ 在直线 $AB$ 一侧
- $x < 0$，$C$ 在直线 $AB$ 另一侧
- $x = 0$，$C$ 在直线 $AB$ 上

所以若 $C$ 和 $D$ 所求出的 $x$ 符号相反，则说明它们在 $AB$ 两侧。
### $Part$ $0.2$ 如何求一个点是否在多边形内
- 射线法，对于一个点，引一条不通过任何一个顶点的射线，若这条射线与多边形形成偶数个交点，那么此点在多边形外，否则在多边形中。

因为数据不是特别强，我们并不需要真的弄出一条射线使得不通过任何一个顶点，事实上，可以设一个无穷远的点 $(1, inf)$ 即可。
## $Part$ $1$ 找出图中的多边形
注意到 **两个栅栏只有在他们的端点才会相遇。每个栅栏在两个端点接触其他的两个栅栏。**，那么我们可以 $O(n ^ 2)$ 枚举每一个栅栏与哪个栅栏在端点相交，用一个标记记录这个栅栏是否已经属于某一个多边形。
### $Part$ $1.1$ 记录一个新的多边形
假如现在我们找到了一个不属于任何一个多边形的栅栏，那么就从这个栅栏开始构造新的多边形，每次找到与它顶点相连的栅栏，找到之后只需要求每个点引的射线与多边形的交点奇偶性并把这个栅栏的标记改为已属于一个多边形即可。这时候我们可以单写一个函数来找与它相连的栅栏。
### $Part$ $1.2$ 寻找与一个栅栏相连的栅栏
其实这个部分没有什么难的，有两个魔鬼细节需要注意。

我们每次寻找与之相连的栅栏需要找前一个栅栏的后一个端点，不然可能会出现一个栅栏后面接了两个不同的栅栏。那么这和时候需要注意如果一个栅栏的后一个端点和另一个不属于任何一个多边形的栅栏的后一个端点一样时，需要将另外一个栅栏翻转（方便之后的操作）
## $Part$ $2$ 判断一个多边形中的点的个数
一个很显然的点，就是 **在同一个多边形中的点，引的射线到与所有多边形的交点的奇偶性是一样的**，所以对于每个点，我们可以开一个数组记录其引的射线的所有多边形的交点的奇偶性
### $Part$ $2.1$ 求交点的奇偶性
在新建一个多边形的过程中，我们就可以求出它引的射线与当前边是否有交点，有的话奇偶性取反就好了。
### $Part$ $2.2$ 排序
这个排序是非常重要的，以为它并不是按照一个常规的方式排序，它按照对每个多边形的交点的奇偶性排序，因为
> 在同一个多边形中的点，引的射线到与所有多边形的交点的奇偶性是一样的

那么这道题就做完了
## $Part$ $3$ 代码
```cpp
#include <iostream>
#include <algorithm>
#include <array>
#define Pii pair<int, int>
using namespace std;
const int NR = 1010;
struct Node 
{
	bool flag;
	Pii p0, p1;
} a[NR];
struct Point
{
	Pii p;
	array<bool, NR> vis;
	bool operator < (const Point & pp) const { return vis < pp.vis; }
} p[NR];
int n, m, ans;
Pii operator - (const Pii &a, const Pii &b) { return {a.first - b.first, a.second - b.second}; } 
int operator * (const Pii &a, const Pii &b) 
{
	long long v = 1LL * a.first * b.second - 1LL * a.second * b.first;
	if (v > 0) return 1;
	else if (v == 0) return 0;
	else return -1;
}
bool is_Foc(Pii a, Pii b, Pii c, Pii d)
{
	return ((b - a) * (c - a)) * ((b - a) * (d - a)) < 0 &&
		     ((d - c) * (a - c)) * ((d - c) * (b - c)) < 0;
}

int find(int x)
{
    for (int i = 1; i <= n; i++)
	{
    	if (i == x) continue;
            if (a[x].p1 == a[i].p1 || a[x].p1 == a[i].p0)
			{
				if (a[x].p1 == a[i].p1) swap(a[i].p0, a[i].p1);
				return i;
			}
    }
    return 0;
}

void make_new(int s)
{
	for (int i = s; !a[i].flag; i = find(i))
	{
		a[i].flag = true;
		for (int j = 1; j <= m; j++)
			p[j].vis[s] ^= is_Foc(p[j].p, {1, 1e9}, a[i].p0, a[i].p1);
	}
//	cout << '\n';
}
int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> a[i].p0.first >> a[i].p0.second >> a[i].p1.first >> a[i].p1.second;
	for (int i = 1; i <= m; i++)
		cin >> p[i].p.first >> p[i].p.second;
	int cnt = 0;
	for (int i = 1; i <= n; i++)
		if (!a[i].flag) make_new(i), cnt++;
//	cout << cnt << '\n';
	sort(p + 1, p + m + 1);
	int sum = 1;
	for (int i = 2; i <= m; i++)
	{
		if (p[i].vis == p[i - 1].vis) sum++; 
		else sum = 1;
		ans = max(ans, sum);
	}
//	for (int i = 1; i <= n; i++)
//	{
//		for (int j = 1; j <= m; j++)
//			cout << p[i].vis[j] << ' ';
//		cout << '\n';
//	}
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：syLph (赞：0)

### [USACO12DEC] Crazy Fences S

[题目传送门](https://www.luogu.com.cn/problem/P3061)

题意：在二维平面上有 $n$ 条线段，他们构成了若干个封闭区域和一个开放区域（线段不相交）。给定 $m$ 个点，求一个区域内最多有几个点。

解法：首先先求出所有的多边形，用线段表示，存在一个数组里。因为所有的线段全都是和其他线段首尾相连的，所以容易求出所有的多边形。

```c
void get_poly(){
    while(1){
        //v[i]表示边i已经被用过,a[i]存线段的具体数据，poly存tot个多边形组成的线段
        int p=1,t=1;
        while(v[p])p++; //找到最后一个没有标记过的边
        if(p>n)break;else v[p] = 1; //如果最后一个没有被标记过的边已经>n说明所有的多边形全部找完
        poi crt = a[p].b;//第一个点
        tot+=1,poly[tot][siz[tot]++] = a[p]; //把第一条边加入poly[tot]中
        while(1){
            t = 1;
            for(int i = p+1 ; i <= n ; i ++){
                if((a[i].a.x==crt.x&&a[i].a.y==crt.y)&&!v[i]) { //此时注意新找的边不能被取
                    v[i]=1,poly[tot][siz[tot]++]=a[i],crt=a[i].b,t++;break; //找一个相同的点，更新线段的端点
                }else if((a[i].b.x==crt.x&&a[i].b.y==crt.y)&&!v[i]) {
                    v[i]=1,poly[tot][siz[tot]++]=a[i],crt=a[i].a,t++;break;
                }
            }
            if(t==1)break;//如果t没有变化，说明没有找的新的边，目前这个多边形的边已经全部找完
        }
    }
}
```

然后，求出所有的 $m$ 个点在哪些多边形中。

这时直接用射线法求解即可。（从一个点往随便一个方向作一条射线，如果与多边形的交点个数是偶数，则在形外，如果是奇数则在形内。）

将所有的包含情况记录在 io 数组里面

```c
	for(int i = 1 ; i <= m ; i ++) {
        scanf("%d%d",&inp[i].x,&inp[i].y); //输入所有的点
    }
    for(int i = 1 ; i <= m ; i ++){
        for(int j = 1 ; j <= tot ; j ++){
            //直线为x = inp[i].x;方向向上
            int lx = inp[i].x,res=0;//res为交点个数
            for(int k = 0 ; k < siz[j] ; k ++){
                seg c = poly[j][k]; //多边形的边
                poi x1 = c.a,x2 = c.b;
                if(x1.x>x2.x)swap(x1,x2);//保证x1<x2
                if(x1.x==x2.x) continue;//特判，由于此题点不会在线段上，所以三点共线是直接判定在形外
                if(x1.x<=lx&&lx<x2.x){//当x1<=x<=x2时才可能相交
                    if(area(x1,inp[i],x2)) { //叉乘判断该点是否在线段的下面，如果交点在线段下面，则在多边形内（注意射线方向向上
                        res += 1; //不开LL见祖宗！
                    }
                }
            }
            if(res%2==1) {
                io[i][d[i]++] = j;//点i在多边形j中
            }
        }
    }
```

最后，求出所有的集合后，因为在同一个封闭区域中的点被多边形所包含的顺序相等，直接暴力比较一下，并查集将在同一个封闭区域内的点合并，计算一下元素个数最多的集合即可。

```c
int get(int x){
    if(x==fa[x])return x;
    return fa[x] = get(fa[x]);
}
void merge(int x,int y){
    x = get(x),y = get(y);
    if(x==y)return;
    fa[x] = y,sie[y] += sie[x];
}
//并查集板子，sie为子树大小

bool cmp(int x,int y){
    if(d[x]!=d[y]) return false;
    for(int i = 0 ; i < d[x] ; i ++){
        if(io[x][i] != io[y][i]) return false;
    } 
    return true;
}

//暴力比较

for(int i = 1 ; i < m ; i ++){
    for(int j = i + 1; j <= m ; j ++){
        if(cmp(i,j)) {
            merge(i,j);
        }
    }
}


//最后统计答案即可
```

附一组数据，答案是 4。

```
10 9
2 9 0 7
0 7 4 3
4 3 8 7
8 7 6 8
6 8 4 7
4 7 2 9
0 3 0 0
0 0 3 0
3 0 3 3 
3 3 0 3
2 7
4 5
6 7
1 1
1 2
2 1
2 2
-100 0
-91 0
```



---

