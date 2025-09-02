# [ABC049D] 連結

## 题目描述

有$N$个城市，$K$条道路（指地面上的道路）和$L$条地铁。道路和地铁都是无向的。对于每个点，请你求出它只通过道路**和**只通过地铁都能到达的点的个数。道路和地铁之间不能换乘，你只能**完全**通过地铁到达某个点，或者**完全**通过道路到达某个点。

## 样例 #1

### 输入

```
4 3 1
1 2
2 3
3 4
2 3```

### 输出

```
1 2 2 1```

## 样例 #2

### 输入

```
4 2 2
1 2
2 3
1 4
2 3```

### 输出

```
1 2 2 1```

## 样例 #3

### 输入

```
7 4 4
1 2
2 3
2 5
6 7
3 5
4 5
3 4
6 7```

### 输出

```
1 1 2 1 2 2 2```

# 题解

## 作者：LightningUZ (赞：4)

原题链接：

[洛谷](https://www.luogu.org/problemnew/show/AT2159)

[AT](https://abc049.contest.atcoder.jp/tasks/arc065_b)
### 题意简述 &数据
这题在洛咕上的翻译是我交的。但是我要说明一点，题面里请把"或"改成"和"理解。（共有两处。如果已经更新过了，那么请忽略。我在讨论区里@管理了。。。）

### 思路
这题是STL的应用题，也是非常考思维的一个题目。首先，如果只有一种线路的话，就非常水了，并查集维护集合大小就珂以做了。

那么我们有两条线路，还要取交集，怎么办呢。。。

我们知道，并查集里面判定在同一个集合的方法是根据祖先判断。如果祖先相同，那就在一个集合里面，否则就不在。此时我们珂能会闪过一个念头：用一个数组（不妨叫$R$）记录两个线路的祖先。具体的说，设维护地铁线路的并查集叫$D1$，维护地面路径的并查集叫$D2$，此时$R[i][j]$表示：有多少个点满足在$D1$中的祖先是$i$，在$D2$中的祖先是$j$。那么，对于一个点$u$，它走两条线路都能到的点数量就是```R[D1.find(i)][D2.find(i)]```（其中$find$是查找祖先的函数）。记录这个数组的方法也很简单，就是对于每个点，```R[D1.find(i)][D2.find(i)]++```。

这个方法看起来很完美，珂是。。。空间？

$BOOM！！！$

如何优化？

```map<pair<int,int>,int>```。观察到，对于每个点，我们只会把这个数组的一个位置$+1$。所以说，真正有用的位置，顶多只有$n$个。那么我们用```map<pair<int,int>,int>```代替一个二维数组，就珂以省下很多空间。如果您不会这个操作，请看引用部分的说明。

> 说明：
> 我们还是设这个东西叫$R$。也就是我们定义```map<pair<int,int>,int> R```。
> 然后，对于$(x,y)$位置加上$v$的操作就是：```R[make_pair(x,y)]+=v```
> 对于位置$(x,y)$的值就是：```R[make_pair(x,y)]```

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Flandle_Scarlet
{
    #define N 200100
    class DSU
    {
        public:
            int Father[N],Cnt[N];
            void Init()
            {
                for(int i=0;i<N;i++)
                {
                    Father[i]=i;
                    Cnt[i]=1;
                }
            }
            int Find(int x)
            {
                return (x==Father[x])?x:(Father[x]=Find(Father[x]));
            }
            void Merge(int x,int y)
            {
                int ax=Find(x),ay=Find(y);
                if (Cnt[ax]<Cnt[ay])
                {
                    Cnt[ay]+=Cnt[ax];
                    Father[ax]=ay;
                }
                else
                {
                    Cnt[ax]+=Cnt[ay];
                    Father[ay]=ax;
                }
            }
    }D1,D2;
    int n,k,l;
    void R1(int &x)
    {
        x=0;char c=getchar();int f=1;
        while(c<'0' or c>'9') f=(c=='-')?-1:1,c=getchar();
        while(c>='0' and c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
        x=(f==1)?x:-x;
    }
    void Input()
    {
        R1(n),R1(k),R1(l);
        D1.Init();
        D2.Init();
        for(int i=1;i<=k;++i)
        {
            int a,b;
            R1(a),R1(b);
            D1.Merge(a,b);
        }
        for(int i=1;i<=l;++i)
        {
            int a,b;
            R1(a),R1(b);
            D2.Merge(a,b);
        }
    }
    #define pii pair<int,int>
    #define _1 first
    #define _2 second
    map<pii,int> rec;
    void Soviet()
    {
        for(int i=1;i<=n;++i)
        {
            int an1=D1.Find(i),an2=D2.Find(i);
            rec[make_pair(an1,an2)]++;
        }
        for(int i=1;i<=n;++i)
        {
            int an1=D1.Find(i),an2=D2.Find(i);
            printf("%d ",rec[make_pair(an1,an2)]);
        }
    }
    void IsMyWife()
    {
        if (0)
        {
            freopen("","r",stdin);
            freopen("","w",stdout);
        }
        Input();
        Soviet();
    }
};
int main()
{
    Flandle_Scarlet::IsMyWife();
    return 0;
}
```

---

## 作者：sprinkles (赞：3)

并查集的板子，再加上map和pair优化一下就轻松水过
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=200000+10;
const int INF=10000000;
int p1[N],p2[N];
map<pair<int,int>,int>m;
int find(int x,int *p)
{
    return p[x]==x?p[x]:p[x]=find(p[x],p);
}
void cha(int x,int y,int *p)
{
    int px=find(x,p);
    int py=find(y,p);
    if(px!=py)
    {
        p[px]=py;
    }
}
int main()
{
    int n,k,l;
    cin>>n>>k>>l;
    for(int i=1;i<=n;i++)
        p1[i]=i,p2[i]=i;
    for(int i=1;i<=k;i++)
    {
        int x,y;
        scanf("%d%d,",&x,&y);
        cha(x,y,p1);
    }
    for(int i=1;i<=l;i++)
    {
        int x,y;
        scanf("%d%d,",&x,&y);
        cha(x,y,p2);
    }
    for(int i=1;i<=n;i++)
    {
        find(i,p1);
        find(i,p2);
    }
    for(int i=1;i<=n;i++)
        m[make_pair(p1[i],p2[i])]++;
    for(int i=1;i<=n;i++)
        printf("%d ",m[make_pair(p1[i],p2[i])]);
    return 0;
}
```

---

## 作者：diqiuyi (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT2159)

**思路**

这题是一道并查集的裸题。但是题目要求的这个东西让人很费解。 $\therefore$ 我们要想办法把两种路线联系在一起。于是不难想到设一个数组 $f_{i,j}$ 表示在两种方式下与 $i$ 和 $j$ 分别联通的城市共有多少个。那么查找操作不变，合并 $u$ 和 $v$ 的操作就是 $f_{find1(u),find2(u)} \gets f_{find1(u),find2(u)}+f_{find1(v),find2(v)}$。对于城市 $u$ 来讲，最终答案就是 $f_{find1(u),find2(u)}$。如此一来，问题就得到了解决。

然后你就会发现空间复杂度是 $O(n^2)$，直接炸掉。

所以我们又需要优化了。

首先你要知道下面这 $2$ 个好东西。

[pair](https://blog.csdn.net/zycxnanwang/article/details/52403330)
[map](https://blog.csdn.net/weixin_43699840/article/details/105392453)

既然知道了这 $2$ 个好东西，那么我们就可以强行把 $f$ 数组变成一个形如
```cpp
map<pair<int,int>,int>
```
的结构，这样就可以把空间复杂度变成 $O(n)$ 了。此时的时间复杂度为 $O(n\log{n})$ 乘上一个很奇怪的且时间复杂度可以看做 $O(1)$ 的函数。具体可以参考下面这个东西。

[并查集的时间复杂度](https://blog.csdn.net/yuzhiqiang666/article/details/80721436)

**CODE**
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,l,f1[200005],f2[200005],p,q;
map<pair<int,int>,int> mp;//其实就是 f
int find(int x,int *f){
    return f[x]==x?x:f[x]=find(f[x],f);
} 
void hb(int x,int y,int *f){
    f[find(x,f)]=f[find(y,f)];
}
//并查集的基本操作
int main(){
    scanf("%d%d%d",&n,&k,&l);
    for(int i=1;i<=n;i++)
        f1[i]=i,f2[i]=i;
    for(int i=1;i<=k;i++){
        scanf("%d%d",&p,&q);
        hb(p,q,f1);
    }
    for(int i=1;i<=l;i++){
        scanf("%d%d",&p,&q);
        hb(p,q,f2);
    }
    for(int i=1;i<=n;i++)
        mp[make_pair(find(i,f1),find(i,f2))]++;
    for(int i=1;i<=n;i++)
        printf("%d ",mp[make_pair(find(i,f1),find(i,f2))]);
    putchar(10);
	return 0;
}
```

总的来说这是一道考察 STL 以及并查集的题。

---

## 作者：迟暮天复明 (赞：0)

[题面](https://atcoder.jp/contests/abc049/tasks/arc065_b)

[没说更好的阅读体验](https://www.cnblogs.com/1358id/p/16267895.html)

Description:

有 $n$ 个点，两张无向图。第一张图中有 $k$ 条边，第二张图中有 $l$ 条边。问对于每个 $i$，在两张图中均可达的点对 $(i,j)$ 的数量。

-----
不用 map 的做法。

首先因为要做连通性，明显要用并查集。我们可以记录一下在第一张图中每个点属于哪个集合。

因为两点在两张图中均可达，等价于两个点在两张图中所在的集合相同，所以我们在已知第一张图的情况下，计算第二张图中每个点的归属。接下来，对于第二个图中的每个集合，我们可以开个桶计算出在它之中所有点在第一个图中的归属。这样，我们就计算出了该集合中哪些点在第一张图中也属于同一集合。那么这个题就做完了，时间复杂度 $O(n)$。

[代码](https://paste.ubuntu.com/p/z6yJKBHWht/)

---

