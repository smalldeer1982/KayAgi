# [USACO13JAN] Square Overlap S

## 题目描述

Farmer John is planning to build N (2 <= N <= 50,000) square fenced-in pastures on his farm, each of size exactly K x K (1 <= K <= 1,000,000). Pasture i is centered at point (x\_i, y\_i) with integer coordinates in the range -1,000,000...1,000,000.  However, in his haste to complete his plans, FJ realizes that he may have accidentally placed two pastures in locations that overlap (by overlap, this means the two pastures share a positive area in common).  No two pastures share the exact same center point.

Given the locations of each of the planned square pastures, please help FJ compute the area shared by the two overlapping pastures.  Output zero if no two squares overlap, and -1 if overlap occurs between more than a single pair of pastures.

在一个直角坐标系中，有N个边长为K的正方形。

给出每一个正方形的中心，请判断所有的正方形是否有重叠。

输入数据保证每一个正方形的中心不重合


## 样例 #1

### 输入

```
4 6
0 0
8 4
-2 1
0 7```

### 输出

```
20```

# 题解

## 作者：zhzh2001 (赞：17)

## 思路


### 整体


首先，我们可以知道，要满足题意，两个正方形的坐标$(x_i,y_i)(x_j,y_j)$必须满足$|x_i-x_j|<k$并且$|y_i-y_j|<k$。如果有且仅有一组正方形满足条件，那么重叠部分的面积$ans=|k-(x_i-x_j)|\times|k-(y_i-y_j)|$。

最简单的方法是直接暴力扫描，时间复杂度为$O(n^2)$。


我本来打算写一个二维线段树的，但好像有些大材小用了，难度才提高啊。


根据[官方题解](http://www.usaco.org/current/data/sol\_squares.html)，先对所有点排序，然后维护与当前点横坐标差值小于k的所有点的集合，每次查找点集中纵坐标最接近当前点的点，更新答案即可。


如何维护所有满足条件的点呢？因为点是有序的，满足$x_i\le x_{i+1}$，每次只需将无效的点删除即可。


### 具体实现


使用`set`维护点集比较方便，删除和插入操作均为log级的。其中`set::insert`会返回一个`pair<iterator,bool>`，第一个为插入后的迭代器，第二个为插入是否成功。(参考http://en.cppreference.com/w/cpp/container/set/insert)


> cppreference是一个不错的C++参考网站

另外，答案应该用64位整数保存。


## 代码清单


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=50005;
typedef pair<int,int> pii;
pii p[N];
int main()
{
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++)
        cin>>p[i].first>>p[i].second;
  //first表示横坐标 second表示纵坐标
    sort(p+1,p+n+1);
  //横坐标为第一关键字 纵坐标为第二关键字排序
    set<pii> S;
  //first表示纵坐标 second表示点的标号 其实只保存点的标号也可以 但必须自定义比较函数了
    long long ans=0;
    for(int i=1,j=1;i<=n;i++)
    {
        for(;j<i&&p[i].first-p[j].first>=k;j++)
            S.erase(make_pair(p[j].second,j));
      //删除不满足条件的点
        set<pii>::iterator it1=S.insert(make_pair(p[i].second,i)).first,it2=it1;
      //it1和it2均为当前点的迭代器
        if(it1--!=S.begin()&&p[i].second-it1->first<k)
            if(!ans)
                ans=(long long)(k-abs(p[i].first-p[it1->second].first))*(k-(p[i].second-it1->first));
            else
                ans=-1;
        if(++it2!=S.end()&&it2->first-p[i].second<k)
            if(!ans)
                ans=(long long)(k-abs(p[i].first-p[it2->second].first))*(k-(it2->first-p[i].second));
            else
                ans=-1;
      //注意set::iterator只能进行自增自减 不能进行+1/-1
    }
    cout<<ans<<endl;
    return 0;
}
```

时间复杂度为$O(n\log n)$



---

## 作者：Ezio__Auditore (赞：9)

## P2202 [USACO13JAN]Square Overlap S 
### & Hack fake solution
[[Statment]](https://www.luogu.com.cn/problem/P2202)

$Date:\ Dec.\ 25th$

---
#### 题意：
&emsp;&emsp;给定 $n$ 个边长为 $k$ 的正方形，若两两之间没有不相交，输出 $0$。 若恰好只有两个正方形相交，输出**相交面积**。 若有多于两个正方形相交输出 $-1$。

---
##### 先表达一波感想：
&emsp;&emsp;作为一道平衡树的题目，题解里却只有一篇正经的使用 set 的做法，其余的大都是“暴力”。我感到非常气愤。 ~~但是平衡树最后还跑不过"暴力"。~~ 一开始我分析了一波还让为暴力算法是正确的，**不过最后还是将其 Hack 掉了， 这个我们稍后再谈**。

---
#### 题解
&emsp;&emsp;先说一下严格 $O(nlogn)$ 的平衡树做法。 

###### 一些解题基础结论：

&emsp;&emsp;设两个正方形中心为 $a$ , $b$, **两个正方形相交当且仅当 $|a.x - b.x| < k$ 且 $|a.y - b.y| < k$**。 这很好理解， 想象每个中心点向外拓展 $\frac{k}2$ 的长度，两个正方形最多能拓展出 $k$, 所以两个正方形相交需要满足横纵之差均小于 $k$。

&emsp;&emsp;两个相交的正方形相交面积为:
$$
S = (k - |a.x - b.x|) \times (k - |a.y - b.y|)
$$
&emsp;&emsp;即相交部分的**长$\times$宽**。

###### 具体实现：
&emsp;&emsp;知道了这一点之后就可以在直到两个中心位置的情况下求面积了。
但是直接枚举是 $n^2$ 的显然过不了， 考虑对 $x$ 进行排序后进行双指针 $l$, $r$ 扫描。 
	
&emsp;&emsp;记根据 $x$ 排序后的中心序列为 $p$, 对于确定的尾指针 $r$, 我们维护满足 $p_r.x - p_l.x \lt k$ 的最大区间 $[l, r]$。具体维护的方法类似于[P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886), 不过我们要知道的不是滑动窗口中的最值，而是在 $[l, r - 1]$ 中 **$|p_i.y - p_r.y|$ 最小的 $p_i$**。

&emsp;&emsp;那如何得到 $|p_i.y - p_r.y|$ 最小的 $p_i$ 呢？可以在 $[l, r - 1]$ 中找出最大的 $p_j.y \le p_r.y$， 和最小的 $p_k.y \ge p_r.y$，这不就是平衡树上求一个 $p_r$ 关于 $y$ 的**前驱**和**后继**吗？

&emsp;&emsp;然后你就可以用任意一种你会写的平衡树，或者直接使用std::set的lower_bound函数获得前驱后继。 

（P.S. 这里的前驱后继和传统意义上的略有不同， **若 $p_i.y = p_r.y$，也把 $p_i$ 视为前驱和后继**）

之后分类讨论：

- 若 $p_j$ 和 $p_k$ 都于 $p_r$ 相交, 或者之前已经有其他的正方形存在相交， 可以直接输出 $-1$。
- 否则记录下与 $p_j$ 或 $p_k$ 与 $p_r$ 相交的面积。
- 如果一直没有相交，记录的相交面积为 $0$, 最后也会输出 $0$ 不用特判。

双指针扫描每个数入队一次出队一次，复杂度为 $O(n)$，平衡树上修改查询均为 $O(logn)$, 总复杂度 $O(nlogn)$ 。

然后你就可以在排序后双指针 + 平衡树 AC 此题。

---
###### 一个笔者之前的疑惑：
	
&emsp;&emsp;在我第一次写的时候， 对于每一个 $p_r$, 查出了两个前驱(即前驱的前驱)和两个后继再统计答案，担心出现 $p_r$ 与两个前驱或后继相交两次，漏判 $-1$ 的情况， 但其实没有这个必要。 以前驱为例，如果存在 $p_r$ 与两个前驱同时相交的情况，那这两个前驱本身也一定相交，在之前已经被统计过了，不会漏判 $-1$。**所以只要个搜出一个前驱和一个后继就可以了**。 虽然这不影响总复杂度，但是常数小跑的快总是好的。

---
#### Code : 
这里我选择了 Splay 作为平衡树。 由于代码较长 Splay 部分就放在本文的最后，这里只给出核心代码(~~好像还是蛮长的~~)。
```cpp
#include <bits/stdc++.h>
template<class _Tp = int> _Tp read() {
  _Tp w = 0;
  bool f = 0;
  char ch = getchar();
  while (!isdigit(ch)) f |= ch == '-', ch = getchar();
  while (isdigit(ch)) w = (w << 3) + (w << 1) + (ch ^ 48), ch = getchar();
  return f ? -w : w;
}

const int kMaxN = 5e4 + 5;
const int INF = 0x3f3f3f3f;
typedef long long ll;
int n;
ll k, square; // square 记录面积答案
struct point {
  int x, y;
  bool operator < (point o) const {
    return (y < o.y || (y == o.y && x < o.x));
  } // 在平衡树中根据 y 排序，为了方便直接重载小于号
  // 注意 y 相等时返回 x 的大小关系，否则平衡树内会认为两个 y 相同 x 不同的点是同一个点
  // 同时这也保证了在查前驱后继的时候会查到 y 和当前相同的点， 而不会被跳过
  point() {};
  point(int x_, int y_) : x(x_), y(y_) {}
} p[kMaxN];

ll intersect(point a, point b) { // 算相交面积
  ll r = 0, c = 0;
  if (std::abs(b.x - a.x) < k) r = k - std::abs(b.x - a.x);
  if (std::abs(b.y - a.y) < k) c = k - std::abs(b.y - a.y);
  return r * c;
}
void check(point a, point b) { // 检查 a, b 是否有交， 且之前是否有其他正方形有交
  ll tmp = intersect(a, b);
  if (tmp != 0) {
    if (square != 0) puts("-1"), exit(0); // 之前有正方形有交，找到两个直接退出。
    else square = tmp;
  }
}

Splay<point> set;
int main() {
  Splay<int> s(std::greater<int>());
  set.insert(point(0, -INF)), set.insert(point(0, INF)); // 插入两个极大极小值防止查不到前驱后继
  n = read(), k = read();
  for (int i = 1; i <= n; i++)
    p[i].x = read(), p[i].y = read();
  std::sort(p + 1, p + n + 1, [](point a, point b)->bool{ return a.x < b.x; }); // 根据 x 排序
  set.insert(p[1]);
  for (int l = 1, r = 2; r <= n; r++) {
    while (l < r && p[r].x - p[l].x >= k) set.erase(p[l++]); // 将与当前点 x 距离大于 k, 不可能相交的正方形从平衡树中删除
    point pre = set.pre(p[r]);
    if (pre.y != -INF) { // 存在前驱
      check(pre, p[r]);
    }
    point next = set.next(p[r]);
    if (next.y != INF) { // 存在后继
      check(next, p[r]);
    }
    set.insert(p[r]); // 将当前点插入平衡树
  }
  printf("%lld\n", square);
  return 0;
}
```
--- 
#### 关于 Hack 暴力：
&emsp;&emsp;接下来再谈谈"暴力"为什么能通过此题而没有被卡， 以及如何将其卡掉。

&emsp;&emsp;"暴力"的大致做法是对 $x$ 进行排序后， 枚举尾结点 $r$, 暴力向前搜索 $l$, 直到 $p_r.x - p_l.x \ge k$ 后退出。 同时若搜索到两个以上的正方形相交， 直接输出 $-1$ 后退出。
由于本题数据相当随机(~~以至于我之前的对 $x$ 排序只判相邻两个是否相交的假算法都能拿到 50pts~~) 所以暴力轻松通过此题，甚至跑的比平衡树还要快。

&emsp;&emsp;考虑如何构造一种数据使得该做法复杂度达到最劣:

- 1. 不能有 2 对或以上的正方形相交，否则该算法会在搜索到后直接结束。
- 2. $x$ 尽量接近，使得每一个末尾 $r$ 向前扫描的距离尽量长。

为了满足第一个要求， 我们让正方形从上到下，竖直方向上相切， 即两个中心点的 $y$ 之差为 $k$。

为了满足第二个要求， 一开始我想让 $x$ 每次 +1， 但这样就需要平衡水平和竖直方向上正方形边长的限制，导致只能让 $k$ 为 $\sqrt x_{max} = 1000$ 级别，无法将其卡掉。 
索性我们直接让 $x$ 相等且 $k = 2$， 这样该暴力就会达到 $O(n^2)$ 级别。

hack 数据生成器：
```cpp
int main() {
  int n = 5e4, k = 2;
  printf("%d %d\n", n, k);
  for (int i = 1; i <= n; i++)
    printf("%d %d\n", 0, 2 * i); // x = 0, y 递增
  return 0;
}
```
还有另一种有技巧的暴力根据 $x + y$ 来排序， 之后再判断是否同时满足 $|a.x - b.x| < k$ 且 $|a.y - b.y| < k$ 的限制， 可以构造 $x + y$ 相等且 $k = 2$ 的情况卡成 $O(n^2)$，最简单的方法就是让 (x, y) 在二四象限平分线上：
```cpp
  for (int i = 1; i <= n; i++)
    printf("%d %d\n", -i * 2, i * 2); // x + y = 0
```

至此，除了复杂度正确使用了set的题解，其他的暴力乱搞算法都TLE了。

---
~~好像 [Dpair](https://www.luogu.com.cn/user/66511) 在看到我在 hack 暴力之后，又搞了个[多次排序的申必暴力](https://www.luogu.com.cn/record/44204061)写法， 暂时不会卡 。~~ 

不过现有的错误题解全都被 hack 了

---
最后：支持自定义比较函数和结构体以及动态内存的~~大常数~~指针 Splay 代码。
```cpp
// multi set using splay
template<class _Tp> class Splay {
  std::function<bool(_Tp, _Tp)> less;
  bool greater(const _Tp& x, const _Tp& y) { return less(y, x); }
  bool equal(const _Tp& x, const _Tp& y) { return (!less(x, y)) && (!greater(x, y)); }
  struct node {
    _Tp key;
    int times, size;
    node *ls, *rs, *fa;
    void update() { size = times + ls->size + rs->size; }
    bool get() { return fa->rs == this; }
    node* &son(bool d) { return !d ? ls : rs; }
    node(_Tp key_, node* null_, int times_ = 1) 
         : key(key_), times(times_), size(times_), ls(null_), rs(null_), fa(null_) {}
  } fall_back, *null = &fall_back, *root = null;
  void rotate(node* x) {
    node *y = x->fa, *z = y->fa;
    bool d = x->get(), d2 = y->get();
    y->son(d) = x->son(!d);
    if (y->son(d) != null) y->son(d)->fa = y;
    x->son(!d) = y;
    y->fa = x; x->fa = z;
    if (z != null) z->son(d2) = x;
    y->update(), x->update();
  }
  void splay(node* now) {
    for (node* fa = null; (fa = now->fa) != null; rotate(now))
      if (fa->fa != null) rotate((fa->get() == now->get()) ? fa : now);
    root = now;
  }
  node* pre() {  node* now = root->ls; while (now->rs != null) now = now->rs; return now; }
  node* next() { node* now = root->rs; while (now->ls != null) now = now->ls; return now; }
 public:
  int rank(_Tp key) {
    int ret = 0; node* now = root;
    while (now != null) {
      if (now->ls != null && less(key, now->key)) now = now->ls;
      else {
        ret += now->ls->size;
        if (equal(key, now->key)) return splay(now), ret + 1;
        else ret += now->times, now = now->rs;
      }
    } return 0;
  }
  void insert(_Tp key) {
    node *now = root, *fa = null;
    while (now != null) {
      if (equal(key, now->key)) 
        return ++(now->times), splay(now);
      fa = now;
      now = now->son(greater(key, now->key));
    }
    now = new node(key, null), now->fa = fa;
    if (fa != null) fa->son(greater(key, fa->key)) = now;
    return splay(now);
  }
  bool erase(_Tp key) {
    if (!rank(key)) return (false);
    --(root->times), root->update();
    if (!root->times) {
      node* newrt, *oldrt = root;
      if ((newrt = pre()) != null) {
        splay(newrt);
        root->rs = oldrt->rs;
        if (root->rs != null) root->rs->fa = root;
        root->update();
      } else if ((newrt = next()) != null) {
        splay(newrt);
        root->ls = oldrt->ls;
        if (root->ls != null) root->ls->fa = root;
        root->update();
      } else root = null;
      delete oldrt;
    }
    return (true);
  }
  _Tp pre(_Tp key) {
    insert(key);
    _Tp ret = pre()->key;
    erase(key);
    return ret;
  }
  _Tp next(_Tp key) {
    insert(key);
    _Tp ret = next()->key;
    erase(key);
    return ret;
  }
  _Tp kth(int k) {
    node* now = root;
    while (now != null) {
      if (now->ls != null && (k <= now->ls->size)) now = now->ls;
      else {
        k -= now->ls->size;
        if (k <= now->times) return spaly(now), now->key;
        k -= now->times;
        now = now->rs;
      }
    } return now->key;
  }
  Splay(_Tp fall_back_) : fall_back(node(fall_back_, &fall_back, 0)), less(std::less<_Tp>()) {}
  Splay(std::function<bool(_Tp, _Tp)> compare_function = std::less<_Tp>()) : fall_back(node(_Tp(), &fall_back, 0)), less(compare_function) {}
  Splay(_Tp fall_back_, std::function<bool(_Tp, _Tp)> compare_function = std::less<_Tp>()) : fall_back(node(fall_back_, &fall_back, 0)), less(compare_function) {}
};
```
---
##### 结语：还是多想想复杂度正确的算法，不过也要有理想。
---
Update: 之前 hack 忘记 $k$ 是偶数了, 不过令 $k = 2$ , $(x, y)$ 扩大两倍之后仍然可以 $hack$ 。

Update: fix: Splay 中查寻第 k 大之后没有将结果 splay 到根, 虽然与此题无关，但还是修复一下。

---

## 作者：封禁用户 (赞：6)

我的思路比较~~简单~~（愚蠢） 就是分别以x和y标准对1~n的点集进行排序，然后分别从1~n-1向i+1到n找会重叠的正方形进行统计。。。用时216ms

复杂度很逊 可能被卡到n^2 然而良心出题人没卡

然后自我感觉细节多到爆炸。贡献7WA

```cpp
#include<bits/stdc++.h>
#define debug printf("%d %s\n",__LINE__,__FUNCTION__)
#define PP system("pause")
#define N 1000010
#define NN 2010
#define NNN 310
#define eps 1e-9
#define inf 0x3f3f3f3f
using namespace std;
namespace program
{
    template<class T>
    T read()
    {
        T s=0;
        int ch,flag=0;
        do
            flag|=(ch=='-');
        while(!isdigit(ch=getchar()));
        do
            s=s*10+ch-'0';
        while(isdigit(ch=getchar()));
        return flag?-s:s;
    }
    template <class T>
    void write(T x)
    {
        static int Buf[100];
        int top=0;
        do
            Buf[top++]=(int)(x%10)+'0';
        while(x/=10);
        while(top)
            putchar(Buf[--top]);
        putchar(' ');
    }
    template<class T>
    void writeln(T x)
    {
        write(x);
        putchar('\n');
    }
    int n,k,ans=0,res=0;
    struct node{int x,y;}a[N];
    inline bool cmp1(node A,node B){if(A.x==B.x)return A.y<B.y;else return A.x<B.x;}
    inline bool cmp2(node A,node B){if(A.y==B.y)return A.x<B.x;else return A.y<B.y;}
    inline void work()
    {
      n=read<int>();
      k=read<int>();
      for(int i=1;i<=n;i++)
      {
        a[i].x=read<int>();
        a[i].y=read<int>();
      }
      sort(a+1,a+n+1,cmp1);//第一遍统计
      for(int i=1;i<n;i++)
      {
        int j=i+1;
        //细节1：判断中间要用or
        while((abs(a[j].x-a[i].x)<k||abs(a[j].y-a[i].y)<k)&&j<=n)//辣鸡复杂度可能被卡到n^2
        {
         //细节2：这里要用and
          if(abs(a[j].x-a[i].x)<k&&abs(a[j].y-a[i].y)<k)
            if(ans!=0){exit(puts("-1")&0);}
            else ans=(k-abs(a[j].x-a[i].x))*(k-abs(a[j].y-a[i].y));
          j+=1;
        }
      }
      sort(a+1,a+n+1,cmp2); //第二遍统计
      for(int i=1;i<n;i++)
      {
        int j=i+1;
        //细节3：j要判边界（被坑飞起来的我瑟瑟发抖）
        while((abs(a[j].x-a[i].x)<k||abs(a[j].y-a[i].y)<k)&&j<=n)
        {
          if(abs(a[j].x-a[i].x)<k&&abs(a[j].y-a[i].y)<k)
            if(res!=0)exit(puts("-1")&0);
            else res=(k-abs(a[j].x-a[i].x))*(k-abs(a[j].y-a[i].y));
          j+=1;
        }
      }
      //细节4：ans和res要非0
      if(ans!=0&&res!=0&&ans!=res)
        puts("-1");
      else
        if(ans!=0)writeln(ans);
        else if(res!=0)writeln(res);
        else puts("0");
    }
}
int main()
{
    program::work();
    return 0;
}

```

---

## 作者：奈芙莲 (赞：6)

好像只有一篇题解。。那我来再发一篇。。。

判定正方形是否重叠和计算正方形重叠面积楼下都已经说过了。。我就不重复了。

我的思路和楼下不大一样。。

1）对于一个正方形（a, b） 和另一个正方形（c, d），如果 |a - c|+|b - d| > 2 \* k 的话，是肯定无解的。（想一想为什么。）
然而这样子还是不是很好处理啊。。。所以我就扩大了一下范围。。。直接把绝对值脱去。。。这样子的话至少不会漏解。。（再想想为什么）。即原来的范围是 |a - c|+|b - d| <= 2\*k 可能有解，现在变成了 a + b - c - d <= 2 \* k 可能有解。前一种情况是后一种情况的子集。所以可以保证不会漏解。。然后就可以按照横坐标加纵坐标排序。。然后再枚举判定是否合意。。。
还有就是。。重叠个数大于一时及时跳出循环。。可以快很多。。

代码如下：

```cpp
#include<bits/stdc++.h>
#define read(a) a=getint()
using namespace std;
const int getint() {int x=0, f=1, c=getchar();for(;c<'0'||c>'9';c=getchar())if(c=='-') f=-1;for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-48;return x*f;}
int n, k, ans, f;
struct node{int x, y;}a[50001];
bool cmp(node a,node b)
{return a.x+a.y<b.x+b.y;}
bool jud(node a,node b){
    return abs(a.x-b.x)<k && abs(a.y-b.y)<k;
}
int main() {
    read(n);read(k);
    for(int i=1;i<=n;++i) read(a[i].x),read(a[i].y);
    sort(a+1,a+n+1,cmp);
    for(int i=1; i<n; ++i) {
        int p = i + 1;
        while(a[i].x+a[i].y  + 2*k >= a[p].x+a[p].y && ans < 2 && p<=n) {
            if(jud(a[i],a[p])) ans ++, f = (k-abs(a[i].x-a[p].x))*(k-abs(a[i].y-a[p].y));
            p++;
        }
        if(ans>1) {puts("-1");return 0;}
    }
    if(ans) printf("%d\n",f);else puts("0");
    return 0;
}
```

---

## 作者：45dino (赞：4)

蓝题吗？可能不那么难。

首先可以想到对于点 $i$ 和 $l$ ，如果 $abs(l_x-i_x)<k$ 并且 $abs(l_y-i_y)<k$ ，这两个矩形就会有重叠，重叠面积为 $abs(k-abs(i_x-l_x))\times abs(k-abs(i_y-l_y))$ 。

对于其他情况，计算重叠的次数特判即可。

此时复杂度为 $O(n^2)$ ，不![](https://cdn.luogu.com.cn/upload/image_hosting/51d80tin.png)才怪。

考虑利用单调性，按 $x$ 值排序，对于点 $i$ ，枚举点 $l$ ，此时复杂度为 $O(nlog_2n)$ 。

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x,y;
} pos[50001];
int n,k,num,ans;
bool cmp(node x,node y)
{
	return x.x<=y.x;
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&pos[i].x,&pos[i].y);
	sort(pos+1,pos+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		int l=i+1;
		while(l<=n&&abs(pos[l].x-pos[i].x)<k)
		{
			if(abs(pos[l].y-pos[i].y)<k)
			{
				num++;
				if(num==2)
				{
					puts("-1");
					return 0;
				}
				ans=abs(k-abs(pos[i].x-pos[l].x))*abs(k-abs(pos[i].y-pos[l].y));
			}
			l++;
		}
	}
	if(num)
		cout<<ans;
	if(num==0)
		puts("0");
	return 0;
}
```


---

## 作者：CodingJellyfish (赞：3)

大家好，我是水母哥，今天我为大家带来 P2202 的一篇严格线性时间复杂度的题解。

据前面的大佬们所说，这道题的正解大概是这样的：将每个坐标按 x 排序，然后找到 x 在范围内的区间，再找到这段区间中找到 y 最近的坐标，最终判断是否重合。

现在需要一个这样的数据结构：能快速删除过时（与目前 x 距离 >= k）节点；能快速添加新节点；能快速找到离该节点最近的节点。

然而“找到最近”这个操作大多数人用 set 或 手写平衡树实现。个人十分厌恶 STL，且很懒，不想写平衡树。所以我苦思冥想，想到了一个实现简单的、复杂度更优秀的数据结构。

考虑维护一个链表，若加入新结点就在表末尾添加。这样由于添加时间是单调的，删除过时节点的操作就可以通过删除最前连续的一段实现。

第三种操作的话，考虑将链表分块，一块大小为 k，用邻接表的方式实现分块，head 表示块的编号。假如两个节点在一块中，那么二者一定合法（差值 < k）；两个节点在相邻的块中，那么二者可能合法；若不是以上两者，那么一定不会合法（中间至少隔了一个长度为 k 的块），那么在搜索一个节点对应的合法节点，只需要查找本身所在块于相邻两个块。

接下来是线性复杂度的证明：

每个节点删除后不会再添加，所以只会被删除一次，n 个节点删除 n 次，链表删除是 $\Theta(1)$ 的，所以这一部分是$\Theta(n)$的。

对于未删除的节点，一个块中不会出现 3 个以上节点，所以搜索一个块中所有未删除的点是 $\Theta(1)$ 的。搜索一个节点时遍历了 3 个块，总共遍历 n 次，所以遍历未删除节点是$\Theta(n)$的。

这个数据结构大概长这样：
![](https://cdn.luogu.com.cn/upload/image_hosting/2l0vvr03.png)

只剩下排序了。由于是数值排序，基数排序即可。基数排序是线性的。

综上，这个算法是线性的。

由于是线性的，这个算法毫无压力地拿到了 2021 年 10 月 16 日的最优解（67ms,加上快读达到了惊人的 39ms)。

前面说得有亿些晦涩难懂，所以看一下代码吧。

```c
#include <stdio.h>
#include <string.h>

// Consts

#define RN 50005

// Defs

typedef struct
{
    int x, y, nxt;
}
Dots;

// Utility

#define ABS(x) ((x) > 0 ? (x) : -(x))

// Sort

unsigned _bu[256];

#define SORTBYTE(TYPE, PART, FR, TO, BIT, LEN, NEG) \
{ \
    memset(_bu, 0, sizeof(_bu)); \
    \
    for (TYPE *it = (FR) + (LEN); it != (FR); it--) \
    { \
        ++_bu[((it[-1]PART >> BIT) + (NEG ? 128 : 0)) & 255]; \
    } \
    for (unsigned *it = _bu; it != _bu + 255; it++) \
    { \
        it[1] += it[0]; \
    } \
    for (TYPE *it = (FR) + (LEN); it != (FR); it--) \
    { \
        (TO)[--_bu[((it[-1]PART >> BIT) + (NEG ? 128 : 0)) & 255]] = it[-1]; \
    } \
}
// 基数排序模板，可以通过 WC 2017 挑战。
// 全部宏定义是为了实现泛型。

Dots all[RN], all2[RN];

// Main

int head[2000005];
int n, k;

static inline int getblock(int x)
{ // x 对应块编号。
    return (x + 1000000) / k + 1;
}

int main(void)
{
    scanf("%d%d", &n, &k);
    
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &all[i].x, &all[i].y);
    }
    // 不要害怕，这是排序
    SORTBYTE(Dots, .x, all + 1, all2 + 1, 0, n, 0);
    SORTBYTE(Dots, .x, all2 + 1, all + 1, 8, n, 0);
    SORTBYTE(Dots, .x, all + 1, all2 + 1, 16, n, 0);
    SORTBYTE(Dots, .x, all2 + 1, all + 1, 24, n, 1);
    
    int flag = 0;
    long long ans;
    
    for (int i = 1; i <= n; i++)
    {
        int bl = getblock(all[i].y);
        
        for (int bi = bl - 1; bi <= bl + 1; bi++)
        { // 遍历前一个块、自身所在块与后一个块。
            for (int j = head[bi], pre = 0; j; pre = j, j = all[j].nxt)
            {
                if (all[j].x + k <= all[i].x)
                { // 删除过时正方形。
                    if (pre)
                        all[pre].nxt = all[j].nxt;
                    else
                        head[bi] = all[j].nxt;
                    continue;
                }
                if (ABS(all[j].y - all[i].y) < k)
                { // 找到合法正方形。
                    if (flag)
                    {
                        printf("-1\n");
                        return 0;
                    }
                    flag = 1;
                    ans = 1ll * (k - ABS(all[i].x - all[j].x))
                              * (k - ABS(all[i].y - all[j].y));
                }
                if (bi == bl)
                { // 添加本身。
                    all[j].nxt = i;
                    break;
                }
            }
        }
        if (!head[bl])
        { // 添加本身
            head[bl] = i;
        }
    }
    
    if (flag)
    {
        printf("%lld\n", ans);
    }
    else
    {
        printf("0\n");
    }
    return 0;
}
```

---

## 作者：I_am_Accepted (赞：2)

### Preface

简洁易懂的 $O(n)$ 解法！（最慢点 81ms）

思路类似于 [P7883 平面最近点对（加强加强版）](https://www.luogu.com.cn/problem/P7883)，可以先做一下。

### Analysis

两个正方形重叠 $\iff$ 两个中心的切比雪夫距离 $<K$。

我们将整个平面划分成 $K\times K$ 的无数个（实际用到的最多 $n$ 个）正方形，称为 Block。

对于一个正方形（其中心在 Block x），与她重叠的正方形必然满足中心 Block 为 Block x 周围的 $9$ 个 Block 中。

考虑将中心点一个一个放入平面对应的 Block 中，并遍历周围 $9$ 个 Block 中的中心点，判断是否重叠即可。

时间复杂度的证明：

前面 Block 标号用 Hash，所以不带 $\log$。（我用的 `unordered_map` 可能较慢）

由于我们遇到 $\ge2$ 对重叠时就停止算法，所以在任意时刻最多有一对重叠的正方形。显然每个点判断时 $9$ 个 Block 里中心点的个数是 $O(1)$ 的，于是总时间 $O(n)$。

### Details

记得读入时将坐标偏移一下，以免负数除法的问题。

对于暂时没有中心点存入的 Block，暂时不标号，节省空间。

### Code

[Link](https://www.luogu.com.cn/record/67669477)

头文件 + 快读比较长，其实主体还短的。

```cpp
//Said no more counting dollars. We'll be counting stars.
#include<bits/stdc++.h>
using namespace std;
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define gc getchar
#define pc putchar
inline int read(){
	int x=0;char c=gc();bool f=0;
	while(!isdigit(c)){if(c=='-')f=1;c=gc();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+c-48;c=gc();}
	if(f)x=-x;return x;
}
#define N 50500
#define base 3000000
#define B 13331
#define ll long long
#define ull unsigned long long

const int dx[9]={1,1,1,0,0,0,-1,-1,-1},dy[9]={-1,0,1,-1,0,1,-1,0,1}; 
int n,m,tot=0,cnt=0;
pair<int,int> a[N],ans;
vector<int> b[N];
unordered_map<ull,int> mp;
inline int block(int x,int y,bool build){
	ull xx=x/m,yy=y/m;
	int tmp=xx*B+yy;
	if(build && mp[tmp]==0) mp[tmp]=++tot;
	return mp[tmp];
}
inline bool check(int x,int y){return abs(a[x].fir-a[y].fir)<m && abs(a[x].sec-a[y].sec)<m;}
void see(int x,int y){
	if(x==0) return ;
	for(int i:b[x]) if(check(i,y)){
		cnt++;
		ans=mkp(i,y);
		if(cnt>1) return ;
	}
}
void work(int t){
	int x,y;
	For(i,0,8){
		x=a[t].fir+m*dx[i];
		y=a[t].sec+m*dy[i];
		see(block(x,y,0),t);
		if(cnt>1) return ;
	}
}
signed main(){
	n=read(),m=read();
	For(i,1,n) a[i].fir=read()+base,a[i].sec=read()+base;
	For(i,1,n){
		work(i);
		if(cnt>1){
			puts("-1");
			return 0;
		}
		b[block(a[i].fir,a[i].sec,1)].pb(i);
	}
	if(cnt==0){
		puts("0");
		return 0;
	}
	int x=m-abs(a[ans.fir].fir-a[ans.sec].fir);
	int y=m-abs(a[ans.fir].sec-a[ans.sec].sec);
	printf("%lld\n",(ll)x*y);
return 0;}
```

---

## 作者：xfrvq (赞：2)

[[USACO13JAN] Square Overlap S](/problem/P2202)

---

### 弱化版本

假如给定 $n$ 条长度为 $k$ 的线段，问有几组重叠，怎么做？

排序，枚举 $1\cdots n$，对于第 $i$ 位，看 $i$ 与 $i+1$，$i$ 与 $i-1$ 构不构成重叠，最后答案 ${}\div 2$（因为每一对都会被算两次）。

这个思路如果应用到二维，就会出现问题：点 $i+1$ 的 $x$ 坐标与点 $i$ 的 $x$ 坐标相等，但是 $y$ 坐标相差很大，这样就不行了。

---
### 正解

看标签，考虑平衡树。还是先排序，对于 $y$ 坐标建平衡树，第 $i$ 轮，放入所有单看 $x$ 坐标可能与 $i$ 的正方形重叠的点的 $y$ 坐标，查找点 $i$ 的 $y$ 坐标在平衡树里的前驱，后继。每一对点都会被查找 $2$ 次，最后判断的时候要注意。

那如何把这些点放进平衡树呢？不难发现每次要放进平衡树的点是一段连续的区间，而区间的左端点、右端点每一轮都是递增的，可以记录为 $l,r$ 放在循环外面，因为它们只会从 $1\cdots n$，因此复杂度是 **均摊 $\mathcal O(1)$**。

---

### 正确性证明

为什么只用查 $1$ 次前驱、后继呢？设点 $i$ 的后继是 $j$，点 $k$ 的正方形会与点 $i$ 的正方形重叠，但 $k$ 不是 $i$ 的后继。

此时程序会查找到点对 $(i,j),(k,i)$，以及 $(j,i)$ （如果 $k$ 的 $y$ 坐标比 $i$ 离 $j$ 更近，会查找到 $(j,k)$）

那么，会找到 $3$ 对点。$2$ 对点可以说明有一个符合的点对，而 $3\gt 2$，说明至少有两个符合的点对。

---

### 代码

平衡树，好像有些人用 `set`，我写的是 FHQ-Treap。

如果确定两组正方形有重叠，重叠面积 $=\operatorname{abs}(k-\operatorname{abs}(x_1-x_2))\times\operatorname{abs}(k-\operatorname{abs}(y_1-y_2))$

```cpp
// author: One_Zzz
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
const int maxn = 5e5 + 1;
const int inf = 0x7F114514;
const int& min2(const int& a,const int& b){
	return a < b ? a : b;
}
inline int abs2(int x){ // 手写玄学提速
	return x > 0 ? x : -x;
}
int lc[maxn],rc[maxn],val[maxn],valx[maxn],heap[maxn],siz[maxn],cnt = 0,rt; 
// FHQ-Treap，val记录y坐标，valx是x坐标（平衡树里不用，但是求前驱后继时要用
int new_node(int x,int y){
	siz[++cnt] = 1;
	val[cnt] = y;
	valx[cnt] = x; // 一并记录x坐标
	heap[cnt] = rand();
	return cnt;
} 
void push_up(int i){
	siz[i] = 1 + siz[lc[i]] + siz[rc[i]];
}
int merge(int x,int y){
	if(!x || !y) return x + y;
	if(heap[x] < heap[y]){
		rc[x] = merge(rc[x],y);
		push_up(x);
		return x;
	} else {
		lc[y] = merge(x,lc[y]);
		push_up(y);
		return y;
	}
}
void split(int i,int k,int& x,int& y){
	if(!i) x = y = 0;
	else {
		if(val[i] <= k){
			x = i;
			split(rc[i],k,rc[i],y);
		} else {
			y = i;
			split(lc[i],k,x,lc[i]);
		}
		push_up(i);
	}
}
int kth(int i,int k){
	for(;;){
		if(k <= siz[lc[i]]) i = lc[i];
		else if(k == siz[lc[i]] + 1) return i;
		else {
			k -= siz[lc[i]] + 1;
			i = rc[i];
		}
	}
}
void insert(int px,int py){
	int x,y;
	split(rt,py,x,y);// 用的是y，但是要记录x
	rt = merge(merge(x,new_node(px,py)),y); 
}
void erase(int n){
	int x,y,z;
	split(rt,n,x,z);
	split(x,n - 1,x,y);
	y = merge(lc[y],rc[y]);
	rt = merge(merge(x,y),z);
}
int prv(int n){
	int x,y;
	split(rt,n - 1,x,y);
	int ret = kth(x,siz[x]); // 返回的是下标，因为同时要知道y坐标离点i最近的点的x和y坐标
	rt = merge(x,y);
	return ret; // 返回下标可以用valx[prv(n)]知道n的前驱的x坐标
}
int nxt(int n){
	int x,y;
	split(rt,n,x,y);
	int ret = kth(y,1); // Cu prv
	rt = merge(x,y);
	return ret;
}
struct point{
	int x,y;
	bool operator<(const point& p) const{
		return x != p.x ? x < p.x : y < p.y;// 排序。x为第一关键字，y为第二关键字
	} 
} q[maxn];
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i = 1;i <= n;++i) scanf("%d%d",&q[i].x,&q[i].y);
	std::sort(q + 1,q + n + 1);
	insert(-inf,-inf); // 先加两个点，避免查询前驱后继时出错
	insert(inf,inf); 
	int l = 1,r = 0,num = 0,ans;
	for(int i = 1;i <= n;++i){
		int lx = q[i].x - k,rx = q[i].x + k;
		for(;q[r + 1].x < rx && r + 1 <= n;++r) insert(q[r + 1].x,q[r + 1].y); // 添加从上一次的r到这次的右边界
		for(;q[l].x <= lx && l <= n;++l) erase(q[l].y); // 删除从上一次的l到这次的左边界
		// 删除->添加 顺序不能乱
		int pv = prv(q[i].y),nx = nxt(q[i].y);
		if(abs2(q[i].y - val[pv]) < k && abs2(q[i].x - valx[pv]) < k){ // 看前驱
			++num; // 出现次数加一
			ans = abs2(k - abs2(q[i].x - valx[pv])) * abs2(k - abs2(q[i].y - val[pv]));
		}
		if(abs2(q[i].y - val[nx]) < k && abs2(q[i].x - valx[nx]) < k){ // 看后继
			++num;
			ans = abs2(k - abs2(q[i].x - valx[nx])) * abs2(k - abs2(q[i].y - val[nx]));
		}
		if(num >= 4) break; // 要乘2
	}
	if(num == 0) printf("0\n");
	else if(num == 2) printf("%d\n",ans); // 都要乘2
	else printf("-1\n"); 
	return 0;
}
```

---

## 作者：windows250 (赞：2)

其实可以不用那么复杂的数据结构...

首先我们要知道的是两个正方形A,B出现重叠，当且仅当:

##|Xa-Xb|<K && |Ya-Yb|<K##
此时重叠部分的面积

##S=(K-|Xa-Xb|)\*(K-|Ya-Yb|)##
得到上述结论后很容易想到两两枚举所有的中心,时间复杂度是**O(n^2)**,而Nmax=50000,显然是会TLE的

因此我们考虑优化:

\* 用一个bool变量have记录之前是否已经找到重叠正方形

\* 对于第一个中心i:对横坐标从小到大进行排序后再按横坐标从小到大枚举

\* 对于第二个中心j:枚举范围为[1,i-1],并且**从后往前进行枚举**,我们设一个变量temp为点j到点i的距离,那么当temp>=K时就直接跳出对j的枚举过程。如果temp<K 并且满足 |Yi-Yj|<K 且 have=false 就更新ans并标记have , 否则have=true直接输出-1即可。

详细见代码:

```cpp
#include<bits/stdc++.h>
#define MAXN 50001
#define in(x) x=read()

using namespace std;

typedef long long ll;

inline int read()
{
    int X=0,w=1;
    char ch=getchar();
    while(ch>'9' || ch<'0') {if(ch=='-') w=-1;ch=getchar();}
    while(ch<='9' && ch>='0') X=(X<<3)+(X<<1)+ch-'0',ch=getchar();
    return X*w;
}//读入优化,可忽略 

struct data
{
    ll x,y;
}s[MAXN];//中心坐标 
int N,K;
ll ans=0;
bool have;

inline bool mcomp(const data &a,const data &b)
{
    return a.x<b.x;
}

int main()
{
    in(N);in(K);
    for(int i=1;i<=N;i++)
        in(s[i].x),in(s[i].y);
    sort(s+1,s+N+1,mcomp);
    for(int i=2;i<=N;i++)//按横坐标从小到大枚举中心 
    {
        int tmp=0;
        for(int j=i-1;j>=1;j--)//依次判断第i到i-1,i-2...的距离是否小于k 
        {
            tmp+=(s[j+1].x-s[j].x);
            if(tmp>=K) break;//如果距离大于k继续枚举显然是没有必要的 
            if(abs(s[i].y-s[j].y)<K)
            {
                if(have) {printf("-1\n");return 0;}//之前已经找到过重叠正方形,直接输出-1 
                have=true;ans=(K-tmp)*(K-abs(s[i].y-s[j].y));
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}
//By windows250
```

---

## 作者：P7GAB (赞：1)

### 分析
如果想让以 $(x_i,y_i)$ 和 $(x_j,y_j)$ 为中心的两个正方形重叠，那么显而易见 $|x_i-x_j|<k$ 且 $|y_i-y_j|<k$。

由于 $n \le 5 \times 10^4$，所以 $O(n^2)$ 的暴力显然过不去，$n \le 5 \times 10^4$ 放的很宽，根号科技及以下都可以通过，这里提供一个比较暴力的平衡树做法。

将每个点的坐标以横坐标为键值插入 FHQ 后，将原序列按横坐标为关键字从小到大排序。这样就可以直接去 FHQ 里查询后继，如果 $|x_i-x_j|<k$ 就去比对 $y_i$ 和 $y_j$，之后再判断那三种重叠情况即可。

不知道是不是人傻常数大的缘故，加了从 [${\color{black}D}{\color{red}arling\_zero\_two}$](https://www.luogu.com.cn/user/754502) 那里薅来的快读快写跟 `inline` 等一系列优化才过掉的。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+12;
const int inf=0x3f3f3f3f;
//这个不是Darling_zero_two的快读，是从timedrop那里薅来的
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
template<typename T>inline void read(T& t) {
	int c=getchar(),f=1;
	t=0;
	while(!isdigit(c)) {
		if(c=='-')f=-1;
		c=getchar();
	}
	while(isdigit(c))t=t*10+c-48,c=getchar();
	t*=f;
}
template<typename T,typename ...Args>inline void read(T& t,Args&... args) {
	read(t),read(args...);
}
int cnt=0,root=0,rnkx,rnky;
struct noed {
	int l,r;
	int numx,numy,pri;
	int size;
} t[maxn];
struct pos {
	int x,y;
} a[maxn];

inline bool cmp(pos x,pos y) {
	return x.x<y.x;
}
inline void build(int x,int y) {
	cnt++;
	t[cnt].size=1;
	t[cnt].l=t[cnt].r=0;
	t[cnt].numx=x;
	t[cnt].numy=y;
	t[cnt].pri=rand();
}
inline void split(int p,int x,int &l,int &r) {
	if(p==0) {
		l=r=0;
		return ;
	}
	if(t[p].numx<=x) {
		l=p;
		split(t[p].r,x,t[p].r,r);
	} else {
		r=p;
		split(t[p].l,x,l,t[p].l);
	}
	t[p].size=t[t[p].l].size+t[t[p].r].size+1;
}
inline int merge(int l,int r) {
	if(l==0 or r==0)
		return l+r;
	if(t[l].pri>t[r].pri) {
		t[l].r=merge(t[l].r,r);
		t[l].size=t[t[l].l].size+t[t[l].r].size+1;
		return l;
	} else {
		t[r].l=merge(l,t[r].l);
		t[r].size=t[t[r].l].size+t[t[r].r].size+1;
		return r;
	}
}
inline void insert(int x,int y) {
	int l,r;
	split(root,x,l,r);
	build(x,y);
	int p=merge(l,cnt);
	root=merge(p,r);
}
inline int kp(int p,int x) {
	int num=t[t[p].l].size;
	if(x==num+1)
		return p;
	if(x<=num)
		return kp(t[p].l,x);
	if(x>num)
		return kp(t[p].r,x-t[t[p].l].size-1);
}
inline void nerv(int x) {
	int l,r;
	split(root,x,l,r);
	int o=kp(r,1);
	rnkx=t[o].numx;
	rnky=t[o].numy;
	root=merge(l,r);
	//cout<<" o "<<o<<" x "<<rnkx<<" y "<<rnky<<endl;
}
inline void write(int x) {
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
int main() {
	int i,n,k;
	read(n,k);
	insert(inf,inf),insert(-inf,-inf);
	for(i=1; i<=n; i++) {
		read(a[i].x,a[i].y);
		insert(a[i].x,a[i].y);
	}
	sort(a+1,a+n+1,cmp);
	int ans=0;
	for(i=1; i<=n; i++) {
		nerv(a[i].x);
		while(rnkx-a[i].x<k) {
			if(abs(rnky-a[i].y)<k) {
				if(ans) {
					cout<<-1<<endl;
					return 0;
				}
				ans=abs(k-abs(rnkx-a[i].x))*abs(k-abs(rnky-a[i].y));
			}
			nerv(rnkx);
		}
	}
	cout<<ans;

	return 0;
}
```

### 备注

- 是从 ${\color{black}t}{\color{red}imedrop}$ [这篇文章](https://www.cnblogs.com/12103h/p/16882637.html)薅来的快读

- 从 [${\color{black}D}{\color{red}arling\_zero\_two}$](https://www.luogu.com.cn/user/754502) 这里得到了一些启发以及第一次的快读快写。

- 我个人认为 [${\color{black}E}{\color{red}zio\_Auditore}$](https://www.luogu.com.cn/user/87329) 的分析不错，卡了大部分的暴力。

---

## 作者：_AyachiNene (赞：1)

一种比较暴力的平衡树做法。

# 思路：
把一个点的坐标作为权值存入平衡树，并按横坐标查找。把原序列排序，这样横坐标就是按升序的。一直用平衡树去查找当前点横坐标的后继，一直到后继的横坐标减 $k$ 大于等于当前点的横坐标，表示在横坐标上是重合了的。对于每个后继再判断纵坐标就行了。
```cpp
for(int i=1;i<=n;i++)
{
	int nx=a[i].x,ny=a[i].y;
	nxt(nx,nx,ny);
	while(nx-a[i].x<k)
	{		
		if(abs(ny-a[i].y)<k)
		{	
//			cout<<i<<" "<<nx<<" "<<ny<<endl;
			if(ans)
			{
				cout<<-1;
				return 0;
			}
			ans=abs(k-abs(a[i].x-nx))*abs(k-abs(a[i].y-ny));
		}
		nxt(nx,nx,ny);
	}
}
```
但是这么做会有两个点超时，卡下常就过了。
# Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
/* --------------- fast io --------------- */ // begin
namespace Fread
{
	const int SIZE=1<<21;
	char buf[SIZE],*S,*T;
	inline char getchar()
	{
		if(S==T)
		{
			T=(S=buf)+fread(buf,1,SIZE,stdin);
			if(S==T) 
				return EOF;
		}
		return *S++;
	}
}
namespace Fwrite
{
	const int SIZE=1<<21;
	char buf[SIZE],*S=buf,*T=buf+SIZE;
	inline void flush()
	{
		fwrite(buf,1,S-buf,stdout);
		S=buf;
	}
	inline void putchar(char c)
	{
		*S++=c;
		if(S==T)
			flush();
	}
	struct NTR
	{
		~NTR()
		{
			flush();
		}
	}ztr;
}
#define getchar Fread::getchar
#define putchar Fwrite::putchar
namespace Fastio
{
	struct Reader
	{
		template<typename T>
		Reader& operator >> (T&x)
		{
			char c=getchar();
			T f=1;
			while(c<'0'||c>'9')
			{
				if(c=='-')
					f=-1;
				c=getchar();
			}
			x=0;
			while(c>='0'&&c<='9')
			{
				x=x*10+(c - '0');
				c=getchar();
			}
			x*=f;
			return *this;
		}
		Reader& operator >> (char& c)
		{
			c=getchar();
			while(c=='\n'||c==' ') 
				c=getchar();
			return *this;
		}
		Reader& operator >> (char* str)
		{
			int len=0;
			char c=getchar();
			while(c=='\n'||c==' ')
				c=getchar();
			while(c!='\n'&&c!=' ')
			{
				str[len++]=c;
				c=getchar();
			}
			str[len]='\0';
			return *this;
		}
		Reader(){}
	}cin;
	const char endl='\n';
	struct Writer
	{
		template<typename T>
		Writer& operator << (T x)
		{
			if(x==0) 
			{
				putchar('0');
				return *this;
			}
			if(x<0)
			{
				putchar('-');
				x=-x;
			}
			static int sta[45];
			int top=0;
			while(x)
			{
				sta[++top]=x%10;
				x/=10;
			}
			while(top)
			{
				putchar(sta[top]+'0');
				--top;
			}
			return *this;
		}
		Writer& operator << (char c)
		{
			putchar(c);
			return *this;
		}
		Writer& operator << (char* str)
		{
			int cur = 0;
			while(str[cur]) 
				putchar(str[cur++]);
			return *this;
		}
		Writer& operator << (const char* str)
		{
			int cur = 0;
			while(str[cur])
				putchar(str[cur++]);
			return *this;
		}
		Writer(){}
	}cout;
}
#define cin Fastio :: cin
#define cout Fastio :: cout
#define endl Fastio :: endl
/* --------------- fast io --------------- */ // end
struct node
{
	int l,r,rnd,size;
	int valx,valy;
}t[114514];
int root,cnt;
inline int New(int x,int y)
{
	t[++cnt].valx=x;
	t[cnt].valy=y;
	t[cnt].rnd=rand();
	t[cnt].size=1;
	return cnt;
}
inline void update(int p)
{
	t[p].size=t[t[p].l].size+t[t[p].r].size+1;
}
inline int merge(int x,int y)
{
	if(!x||!y)
		return x|y;
	if(t[x].rnd<t[y].rnd)
	{
		t[x].r=merge(t[x].r,y);
		update(x);
		return x;
	}
	else
	{
		t[y].l=merge(x,t[y].l);
		update(y);
		return y;
	}
}
inline void split(int p,int val,int &x,int &y)
{
	if(!p)
		x=y=0;
	else
	{
		if(t[p].valx<=val)
		{
			x=p;
			split(t[p].r,val,t[p].r,y);
		}
		else
		{
			y=p;
			split(t[p].l,val,x,t[p].l);
		}
		update(p);
	}
}
inline void insert(int x,int y)
{
	int a,b;
	split(root,x,a,b);
	root=merge(merge(a,New(x,y)),b);
}
inline void nxt(int x,int &nx,int &ny)
{
	int a,b;
	split(root,x,a,b);
	int p=b;
	while(p)
		nx=t[p].valx,ny=t[p].valy,p=t[p].l;
	merge(a,b);
}
struct Node
{
	int x,y;
}a[114514];
bool cmp(Node x,Node y)
{
	return x.x<y.x;
}
int n,k;
int ans;
int main()
{
	cin>>n>>k;
	insert(1145141919,1145141919);
	insert(-1145141919,-1145141919);
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].x>>a[i].y;
		insert(a[i].x,a[i].y);
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		int nx=a[i].x,ny=a[i].y;
		nxt(nx,nx,ny);
		while(nx-a[i].x<k)
		{		
			if(abs(ny-a[i].y)<k)
			{	
//				cout<<i<<" "<<nx<<" "<<ny<<endl;
				if(ans)
				{
					cout<<-1;
					return 0;
				}
				ans=abs(k-abs(a[i].x-nx))*abs(k-abs(a[i].y-ny));
			}
			nxt(nx,nx,ny);
		}
	}
	cout<<ans;
}
```
快读超时零点零几秒，所以用的 fastio，开了 O2 后 c++14 最慢的点 $994ms$。

---

## 作者：快斗游鹿 (赞：1)

## 思路

首先我们要知道，若两个正方形重叠，则两个正方形的坐标 $(x_i,y_i),(x_j,y_j)$ 满足 $|x_i-x_j|<k$ 且 $|y_i-y_j|<k$，重叠的面积为 $|k-(x_i-x_j)|\times|k-(y_i-y_j)|$。

瞅了眼标签，发现有平衡树，我们考虑如何运用。显然，我们应当先对 $x$ 坐标进行排序，再根据 $y$ 坐标建平衡树。接下来对于第 $i$ 轮，我们都插入只看 $x$ 坐标有可能与点 $i$ 所在正方形重叠的正方形的 $y$ 坐标，接下来就查找点 $i$ 的 $y$ 坐标在平衡树里的前驱和后继。

那么如何将点插入平衡树呢？对 $x$ 坐标排序后，数列是单调不降的，也就是说，每次需要插入的都是一段连续的区间，且左端点和右端点都会递增。每轮都暴力插入一次复杂度显然不够优秀，那么我们可以将每次的左端点和右端点记为 $l,r$，每次只需要删掉不满足条件的点，再插入当前点。这有点类似于单调队列，这样每个点都只会被插入 $1$ 次。

## 代码

这里我用的是伸展树。

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5000000;
struct Node{
	ll x,y;
	ll ch[2];
	ll f,cnt,son,val;
}a[N],t[N];
ll n,k,tot,ans,root,final,l=1;
inline void read(ll &x) {
    x=0;
    register ll f=1;
    register char c=getchar();
    while(c<'0'||c>'9') {
        if(c=='-') f=-1;
        c=getchar();
    }
    while (c>='0'&&c<='9')
        x=(x<<3)+(x<<1)+c-'0',c=getchar();
    x*=f;
}
void push_up(ll x){
	t[x].son=t[t[x].ch[0]].son+t[t[x].ch[1]].son+t[x].cnt;
}
void rotate(ll x){
	ll y=t[x].f;
	ll z=t[y].f;
	ll k=(t[y].ch[1]==x);
	t[z].ch[t[z].ch[1]==y]=x;t[x].f=z;
	t[y].ch[k]=t[x].ch[k^1];t[t[x].ch[k^1]].f=y;
	t[x].ch[k^1]=y;t[y].f=x;
	push_up(y);push_up(x);
}
void Splay(ll x,ll goal){
	if(x==goal)return;
	while(t[x].f!=goal){
		ll y=t[x].f;
		ll z=t[y].f;
		if(z!=goal){
			(t[z].ch[0]==y)^(t[y].ch[0]==x)?rotate(x):rotate(y);
		}
		rotate(x);
	}
	if(!goal){
		root=x;
	}
}
void insert(ll x){
	ll u=root,ff=0;
	while(u&&t[u].val!=x){
		ff=u;
		u=t[u].ch[t[u].val<x];
	}
	if(u){
		t[u].cnt++;
	}
	else{
		u=++tot;
		if(ff){
			t[ff].ch[t[ff].val<x]=u;
		}
		t[u].son=t[u].cnt=1;
		t[u].f=ff;t[u].val=x;
	}
	Splay(u,0);
}
void find(ll x){
	ll u=root;
	if(!u)return;
	while(t[u].val!=x&&t[u].ch[t[u].val<x]){
		u=t[u].ch[t[u].val<x];
	}
	Splay(u,0);
}
ll next(ll x,ll f){
	find(x);
	ll u=root;
	if(t[x].cnt>1)return root;
	u=t[u].ch[f];
	while(t[u].ch[f^1])u=t[u].ch[f^1];
	return u;
}
void _delete(ll x){
	ll first=next(x,0);
	ll last=next(x,1);
	Splay(first,0);Splay(last,first);
	ll del=t[last].ch[0];
	if(t[del].cnt>1){
		t[del].cnt--;Splay(del,0);
	}
	else{
		t[last].ch[0]=0;
	}
}
bool cmp(Node x,Node y){
	if(x.x!=y.x)return x.x<y.x;
	return x.y<y.y;
}
int main(){
	//freopen("P2202_2.in","r",stdin);
	read(n);read(k);
	insert(-1145141999);
	insert(1145141999);//插入虚节点
	for(int i=1;i<=n;i++)read(a[i].x),read(a[i].y);
	sort(a+1,a+1+n,cmp);
	insert(a[1].y);
	for(int r=2;r<=n;r++){
		while(l<r&&a[r].x-a[l].x>=k){
			_delete(a[l].y);
			l++;
		}
		insert(a[r].y);
		ll first=next(a[r].y,0)-2;
		ll last=next(a[r].y,1)-2;
	//	_delete(a[r].y);
		//cout<<first<<" "<<a[r].y<<" "<<last<<endl;
		if(first>0&&abs(a[first].y-a[r].y)<k){
			ans++;
			if(ans==2){
				puts("-1");return 0;
			}
			else if(ans==1){
				final=abs(k-abs(a[first].x-a[r].x))*abs(k-abs(a[first].y-a[r].y));
			}
		}
		if(last>0&&abs(a[last].y-a[r].y)<k){
			ans++;
			if(ans==2){
				puts("-1");return 0;
			}
			else if(ans==1){
				final=abs(k-abs(a[last].x-a[r].x))*abs(k-abs(a[last].y-a[r].y));
			}
		}
		//cout<<final<<" "<<a[r].y<<endl;
	}
	printf("%lld\n",final);
	return 0;
}
```


---

## 作者：liangbowen (赞：1)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/P2202)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/17522453.html)

提供一个平衡树做法，虽然和 `std::set` 一个道理就是了。（那你为啥不写 set！！！！）

## 前置知识

如何判断两个点对应的正方形相交？正方形的边长是 $k$，中心距离四条边就是 $\dfrac k2$ 了。中心要相隔严格小于两段 $\dfrac k2$，显然只需满足：

$$|X_p-X_q|, |Y_p-Y_q|< k$$

类似地，重叠部分的面积就是 $(k - |X_p - X_q|) \times (k - |Y_p - Y_q|)$。

## 思路

很容易想到对 $x$ 这一维排序，然后写个指针扫一遍，把 $a_r - a_l \ge k$ 的丢掉即可。

接着加入 $a_r$。与之重复面积最大的，必然是它在 $\text{value}$ 意义上的前驱与后继。

很容易想到平衡树。（`std::set`：？？？？）以 $y$ 为第一关键字建立平衡树即可。

显然 $O(n\log n)$。

## 代码

看起来很恐怖，替罪羊树那一部分不用管就简单了，很板子的。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 2e5 + 5;

int n, k;
struct Poi {int x, y;} a[N];
bool cmp(Poi p, Poi q) {return p.x < q.x;}
bool chk(Poi p, Poi q) {return abs(p.x - q.x) < k && abs(p.y - q.y) < k;}
long long ans;
void update(Poi p, Poi q)
{
	if (!chk(p, q)) return;
	if (ans) puts("-1"), exit(0); //有两个了，寄 
	ans = 1ll * (k - abs(p.x - q.x)) * (k - abs(p.y - q.y));
}
bool operator < (Poi p, Poi q) {if (p.y != q.y) return p.y < q.y; return p.x < q.x;}
bool operator == (Poi p, Poi q) {return p.x == q.x && p.y == q.y;}
bool operator <= (Poi p, Poi q) {return p < q || p == q;}

struct ScapegoatTree { //替罪羊树板子
	#define ls tr[pos].l
	#define rs tr[pos].r
	#define tmp (tr[ls].siz + (!tr[pos].del))
	
	const double T = 0.7; const int inf = 2147483647;
	struct Node {int l, r, tot, siz; Poi val; bool del; void clear() {l = r = del = 0, siz = tot = 1;}} tr[N];
	int root, stk[N], top, order[N], cnt;
	ScapegoatTree() {for (int i = N - 1; i; i--) stk[++top] = i;}
	void pushup(int pos) {tr[pos].siz = tr[ls].siz + tr[rs].siz + 1, tr[pos].tot = tr[ls].tot + tr[rs].tot + 1;}
	void inorder(int pos) {if (!pos) return; inorder(ls); tr[pos].del ? stk[++top] = pos : order[++cnt] = pos; inorder(rs);}
	void build(int l, int r, int &pos) {if (l > r) return pos = 0, void(); int mid = (l + r) >> 1; pos = order[mid]; if (l == r) return tr[pos].clear(); build(l, mid - 1, ls), build(mid + 1, r, rs); pushup(pos);}
	void rebuild(int &pos) {cnt = 0, inorder(pos); build(1, cnt, pos);}
	int getrnk(int pos, Poi val) {if (!pos) return 0; if (val <= tr[pos].val) return getrnk(ls, val); else return tmp + getrnk(rs, val);} int getrnk(Poi val) {return getrnk(root, val) + 1;}
	Poi getval(int pos, int k) {if (!pos) return (Poi){-inf, -inf}; if (!tr[pos].del && tmp == k) return tr[pos].val; if (k <= tmp) return getval(ls, k); else return getval(rs, k - tmp);} Poi getval(int k) {return getval(root, k);}
	void insert(int &pos, Poi val) {if (!pos) return pos = stk[top--], tr[pos].val = val, tr[pos].clear(); tr[pos].siz++, tr[pos].tot++; if (val <= tr[pos].val) insert(ls, val); else insert(rs, val); if (T * tr[pos].siz <= max(tr[ls].siz, tr[rs].siz)) rebuild(pos);} void insert(Poi val) {insert(root, val);}
	void delett(int &pos, int k) {tr[pos].siz--; if (!tr[pos].del && tmp == k) return tr[pos].del = true, void(); if (k <= tmp) delett(ls, k); else delett(rs, k - tmp);} void delett(Poi val) {delett(root, getrnk(val)); if (T * tr[root].tot >= tr[root].siz) rebuild(root);}
	Poi getpre(Poi val) {Poi t = getval(getrnk(val) - 1); return (t.x == -inf ? (Poi){-inf, -inf} : t);} Poi getsuf(Poi val) {Poi t = getval(getrnk((Poi){val.x + 1, val.y})); return (t.x == -inf ? (Poi){inf, inf} : t);}
	
	#undef ls
	#undef rs
} T;
int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y);
	sort(a + 1, a + n + 1, cmp);
	for (int l = 1, r = 1; r <= n; r++)
	{
		while (l < r && a[r].x - a[l].x >= k) T.delett(a[l++]);
		Poi pre = T.getpre(a[r]), suf = T.getsuf(a[r]);
		if (pre.x != -T.inf) update(a[r], pre);
		if (suf.y != T.inf) update(a[r], suf);
		T.insert(a[r]);
	}
	cout << ans << '\n';
	return 0;
}
```

希望能帮助到大家！

---

## 作者：曹老师 (赞：1)

## Sol ##

[blog食用](http://www.caolaoshi.men/index.php/archives/usaco13jan-so.html)

这个题没什么技巧，跟着题目做就能过，主要是式子推的比较麻烦。两个地方需要推式子来算，就是判断是否重叠和计算重叠面积的时候。我们按照横坐标排序，每一次只取出可能与该点有重叠的矩形(左边界比当前矩形的右边界小的矩形)，确定了横坐标再确定纵坐标，纵坐标分两种情况：右上方和右下方。自己根据两种情况手推出式子来，就能求解了。

## Code ##

```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

struct Node {
    int x , y;
    bool operator < (const Node &a) const {
        return x < a.x;
    }
};
Node map[50005];
int n , k , cnt , top = 2 , ans;

int myabs(int a) {
    return a>0?a:(-a);
}

int jud(int x , int y) {
    if(map[y].y > map[x].y && map[y].y-k/2<map[x].y+k/2)
        return 1;
    if(map[y].y < map[x].y && map[y].y+k/2>map[x].y-k/2)
        return 1;
    return 0;
}

int qarea(int x , int y) {
    if(map[x].y > map[y].y) {
        int len1 = map[y].y-map[x].y+k , len2 = map[x].x-map[y].x+k;
        return len1*len2;
    }
    if(map[x].y < map[y].y) {
        int len1 = map[x].y-map[y].y+k , len2 = map[x].x-map[y].x+k;
        return len1*len2;
    }
}

int main() {
    scanf("%d%d",&n,&k);
    for(int i=1; i<=n; i++)
        scanf("%d%d",&map[i].x,&map[i].y);
    sort(map+1 , map+n+1);
    for(int i=1; i<=n; i++)
        for(int j=i+1; j<=n; j++) {
            if(map[j].x-k/2 >= map[i].x+k/2)
                break;
            if(i != j && jud(i , j)) {
                cnt++;
                if(cnt > 1) {
                    printf("-1");
                    return 0;
                }
                ans = qarea(i , j);
            }
        }
    if(!cnt)
        printf("0");
    else
        printf("%d",ans);
    return 0;
}
```


  [1]: https://www.luogu.org/problemnew/show/P2202

---

## 作者：封禁用户 (赞：1)

来一发Pascal题解（吐槽一下难度确实不合理）

本题主要考察得是线（暴）性（力）扫（枚）描（举）（>\_>）的思想

对于N个正方形，可以知道当正方形A、B的坐标为（x1,y1）(x2,y2)时，abs（x1-x2）<k 且abs（y1-y2）<k正方形会出现重叠

对于50000个正方形，枚举显然是可以过的，于是上代码





```cpp
var i,j,k,l,n,num,ans,r:longint;
    x,y:array[1..500000] of longint;
procedure sort(l,r:longint);
var i,j,t,m:longint;
begin
  i:=l;j:=r;m:=x[(i+j) div 2];
  repeat
    while x[i]<m do inc(i);
    while x[j]>m do dec(j);
    if not(i>j) then begin
      t:=x[i];x[i]:=x[j];x[j]:=t;
      t:=y[i];y[i]:=y[j];y[j]:=t;
      inc(i);dec(j);end;
  until i>j;
  if l<j then sort(l,j);
  if i<r then sort(i,r);
end;
begin
  readln(n,k);
  for i:=1 to n do read(x[i],y[i]);
  sort(1,n);//按坐标排序，便于枚举
  ans:=0;
  for l:=1 to n-1 do
   begin
     r:=l+1;   num:=0;//按1到n-1枚举l个正方形，则判断R=l+1个正方形的坐标
     while (x[r]-x[l]<k)and(r<=n) do
       begin
         if (abs(y[r]-y[l])<k) then//如果有重叠，计算面积为ans
         if ans=0 then
           ans:=(k-abs(x[r]-x[l]))*(k-abs(y[r]-y[l]))
         else begin ans:=-1;   break;end;
         if ans=-1 then break;inc(r);//线性扫描的精髓，若当前的r满足与l重叠，则向右扩张，否则break跳出循环，l想做推进
        end;
     if ans=-1 then break;//如果完全无重叠则返回-1
  end;
  writeln(ans);
end.

```

---

## 作者：strlen_s_ (赞：0)

写一波平衡树题解。

## 分析

将所有正方形按 $x$ 轴排序，从左到右加入。

对于一个正在加入并统计答案的正方形，删除与他在 $x$ 轴上距离大于 $k$ 的，这样可以保证在处理这个正方形时未被删除的正方形都在 $x$ 轴上与它“重回”。

这一步可以使用双指针维护，我用的是用 vector 存要删除的正方形。

现在考虑如何统计是否重合。

开两颗平衡树，一个维护正方形的上边界，一个维护正方形的下边界。

在平衡树中寻找当前正方形上边界的后继，寻找下边界的前驱，并算出距离。

若两个距离都小于 $k$ ，说明这个正方形上面重回了一个，下面也重回了一个，那么就输出 $-1$,否则就直接统计答案。

### code

```
 #include<bits/stdc++.h>
#define in inline
#define re register
//#define int long long
using namespace std;
in int read(){
	int x=0,f=1;
	char c;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
const int N=1e5+10,inf=1e9,M=1e6+10;
struct sqare{
	int x,y,id;
}s[N];
int n,k;
int ans;
struct Treap{
	pair<int,int>v[N];
	int rd[N],son[N][2],top,root,id[N];
	int flip(int k,bool d){
		int s=son[k][d^1];
		son[k][d^1]=son[s][d];
		son[s][d]=k;
		return s;
	}
	int insert(int k,int z,int h){
		if(!k){k=++top,v[k]=make_pair(z,h),rd[k]=rand();return k;}
		if(v[k].first==z){return k;}
		bool d=(v[k].first<z);
		son[k][d]=insert(son[k][d],z,h);
		if(rd[k]<rd[son[k][d]])k=flip(k,d^1);
		return k;
	}
	void ins(int z,int h){root=insert(root,z,h);}
	int delet(int k,int z){
		if(!k)return 0;
		if(z<v[k].first)son[k][0]=delet(son[k][0],z);
		else if(z>v[k].first)son[k][1]=delet(son[k][1],z);
		else{
			if(!son[k][0]&&!son[k][1]){
				k=0;
			}
			else if(son[k][0]&&!son[k][1]){
				k=flip(k,1);
				son[k][1]=delet(son[k][1],z);
			}
			else if(!son[k][0]&&son[k][1]){
				k=flip(k,0);
				son[k][0]=delet(son[k][0],z);
			}
			else{
				bool d=(rd[son[k][0]]>rd[son[k][1]]);
				k=flip(k,d);
				son[k][d]=delet(son[k][d],z);
			}
		}
		return k;
	}
	void del(double z){root=delet(root,z);}
	pair<int,int> prefix(int k,int x){
		if(!k)return make_pair(-inf,0);
		else if(v[k].first>=x)return prefix(son[k][0],x);
		else {
			pair<int,int>g=prefix(son[k][1],x);
			if(v[k].first>g.first)return v[k];
			else return g;
		}
	}
	pair<int,int> suffix(int k,int z){
		if(!k)return make_pair(inf,0);
		if(v[k].first<=z)return suffix(son[k][1],z);
		else{
			pair<int,int>g=suffix(son[k][0],z);
			if(v[k].first<g.first)return v[k];
			else return g;
		}
	}
	pair<int,int> suf(int z){return suffix(root,z);}
	pair<int,int> pre(int z){return prefix(root,z);}		//普通Treap。 
}T1,T2;
bool cmp(sqare a,sqare b){return a.x<b.x;}
void ins(sqare a){
	int l2=a.y-k,r2=a.y+k;
	T1.ins(l2,a.id),T2.ins(r2,a.id);
}
void del(sqare a){
	int l2=a.y-k,r2=a.y+k;
	T1.del(l2),T2.del(r2);
}
vector<int>v[N];
int t[N];
void dl(int x){
	for(int i=0;i<v[x].size();i++)del(s[v[x][i]]);
	v[x].clear();
}
signed main(){
	n=read(),k=read()/2;
	for(int i=1;i<=n;i++)s[i].x=read(),s[i].y=read();
	sort(s+1,s+1+n,cmp);
	for(int i=1;i<=n;i++)t[i]=s[i].x;
	t[n+1]=inf;
	for(int i=1;i<=n;i++){
		int x=lower_bound(t+1,t+1+n+1,t[i]+k+k)-t;
		s[i].id=i;
		v[x].push_back(i);				//vector 加入删除节点。 
	}
	T2.ins(-inf,0),T2.ins(inf,0),T1.ins(-inf,0),T1.ins(inf,0);
	for(int i=1;i<=n;i++){
		dl(i);
		int l1=s[i].x-k,l2=s[i].y-k,r2=s[i].y+k;
		pair<int,int>g1=T1.pre(l2+1),g2=T2.suf(r2-1);			//为了统计答案还要返回编号。 
		int prel2=g1.first,sufr2=g2.first,idl2=s[g1.second].x+k,idr2=s[g2.second].x+k;
		ins(s[i]);
		int x=l2-prel2,y=sufr2-r2,zl2=idl2-l1,zr2=idr2-l1;
		if(x==0&&y==0){
			if(ans){
				puts("-1");
				return 0;
			}
			ans=k*2*zl2;
		}
		if(x<k+k&&y<k+k){
			puts("-1");
			return 0;
		}
		if(x<k+k){
			if(ans){
				puts("-1");
				return 0;
			}
			ans=(k+k-x)*zl2;
		}
		if(y<k+k){
			if(ans){
				puts("-1");
				return 0;
			}
			ans=(k+k-y)*zr2;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```


---

