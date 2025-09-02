# [USACO15OPEN] Trapped in the Haybales G

## 题目描述

Farmer John 收到了一批 $N$ 个大型干草捆（$1 \le N \le 100,000$），并将它们放置在他通往谷仓的道路上的不同位置。不幸的是，他完全忘记了奶牛 Bessie 正在这条路上吃草，她现在可能被困在这些干草捆之间了！每个干草捆 $j$ 有一个大小 $S_j$ 和一个位置 $P_j$，表示它在这条一维道路上的位置。Bessie 可以在道路上自由移动，甚至可以移动到干草捆所在的位置，但她无法穿过这个位置。唯一的例外是，如果她朝同一方向连续移动 $D$ 单位的距离，她将获得足够的速度，能够突破并永久消除任何大小严格小于 $D$ 的干草捆。当然，在突破之后，她可能会打开更多的空间，从而有机会突破其他干草捆，并继续消除它们。

如果 Bessie 最终能够突破最左侧或最右侧的干草捆，她就可以成功逃脱。请计算道路中所有无法逃脱的实数起始位置的总面积。

## 样例 #1

### 输入

```
5
8 1
1 4
8 8
7 15
4 20```

### 输出

```
14```

# 题解

## 作者：littleming (赞：5)

https://li-mi.github.io/2017/06/03/Usaco2015-Open-Gold-Trapped-in-the-Haybales/

题目好绕啊。。

大概就是求Bessie站在哪里逃不出去。。

当然可以暴力。。100000，显然只能用O(nlogn)，官方的标程也是用这个复杂度的。

假如Bessie从一个很低的区间一直往外冲，结果撞在了很高的一个区间的干草堆上。如果从低区间往高区间求解，不是很亏吗。。于是从高区间向低区间求解↓

先把干草堆的高度排递减序，将每个高度值插入set，在set里面二分找它左右相邻的干草堆，

如果这个区间正好能把Bessie拦住，就把这个区间内的干草堆标记一下，以后就不用再标记了。

这里采用左闭右开，将左边的干草堆标记，右边的不标记。

还有一点，数据达到1e9，要离散化。（lz用map）

时间复杂度就是O(nlogn)，但由于用了map常数会大跑得慢。。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
inline int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
int n,pos[100008],l,r,ans;
struct node{
    int s,p;
}a[100008];
map<int,int> m;
set<int> s;
set<int>::iterator si;
bool vis[100008];
inline bool cmp(const int a,const int b){return a<b;}
inline bool cmp2(const node a,const node b){return a.s>b.s;}
int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        a[i].s=read();a[i].p=read();
        pos[i]=a[i].p;
    }
    sort(pos+1,pos+n+1,cmp);
    for(int i=1;i<=n;i++)    m[pos[i]]=i;
    sort(a+1,a+n+1,cmp2);
    s.insert(a[1].p);
    for(int i=2;i<=n;i++){
        if(*s.begin()<a[i].p){
            si=--s.upper_bound(a[i].p);
            l=m[*si];r=m[a[i].p];
            if(pos[r]-pos[l]<=a[i].s&&!vis[l]){
                for(int j=l;j<r;j++)    vis[j]=1;
            }
        }
        if(*--s.end()>a[i].p){
            si=s.upper_bound(a[i].p);
            l=m[a[i].p];r=m[*si];
            if(pos[r]-pos[l]<=a[i].s&&!vis[l]){
                for(int j=l;j<r;j++)    vis[j]=1;
            }
        }
        s.insert(a[i].p);
    }
    for(int i=1;i<n;i++){
        if(vis[i])    ans+=pos[i+1]-pos[i];
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：XY_ATOE (赞：4)

题目理解起来有点困难（反正对于我这样的英语渣渣是这样）


题目意思就是有n个干草包，将一条路分成了n-1段区间，把起点设在这n-1段的每一段中，判断从那里开始是否能够逃脱，输出所有不能逃脱的区间长度之和。


这样暴力就很好打了，对于每一段都暴力判断一下就行了，复杂度很高。

所以我们考虑优化。

可以想到对于一段区间A，模拟以区间A为起点并试图逃脱的过程，如果闯入了一段已经判断为可以逃脱的区间B，那么区间A也是可以逃脱的。

这样就开一个bool数组记录一下那些段可以逃脱就好了。

复杂度很玄学，仔细想想还是挺小的~~


```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
struct bao
{
    int x,d;
}b[101000];
int read()
{
    int f=1,p=0;
    char x=getchar();
    while(x<'0'||x>'9'){if(x=='-')f=-1;x=getchar();}
    while(x>='0'&&x<='9'){p=p*10+x-'0';x=getchar();}
    return f*p;
}
int n,s,l,r,ans;
bool f[101000];
bool cmp(const bao &a,const bao &b){return a.x<b.x;}
bool work(int t)
{
    s=b[t+1].x-b[t].x;
    l=t,r=t+1;
    while(1<=l&&r<=n)
    {
        bool kkk=0;
        if(s>b[l].d)
        {
            kkk=1,l--;
            if(f[l]){f[t]=1;return 1;}
            s+=(b[l+1].x-b[l].x); 
        }
        if(s>b[r].d)
        {
            kkk=1,r++;
            if(f[r-1]){f[t]=1;return 1;}
            s+=(b[r].x-b[r-1].x);
        }
        if(!kkk)return 0;
    }
}
int main()
{
    n=read();
    for(int i=1;i<=n;i++)b[i].d=read(),b[i].x=read();
    sort(b+1,b+n+1,cmp);
    f[0]=1,f[n]=1;
    for(int i=1;i<n;i++)
        if(!work(i))ans+=b[i+1].x-b[i].x;
    cout<<ans;
    return 0;
}

```

---

## 作者：Schwarzkopf_Henkal (赞：2)

加了翻译之后好受多了……

第一篇题解，仍有生疏请关照。

其实这一题远远没有标签上写的那么难，暴力加优化就能过。首先朴素地思考一下，这题的位置范围一直到$10^9$，一个点一个点来绝对是不可能的，而对于一个两个相邻草堆围成的区间，要是其中一个点能够跑出去，那么这个区间内的其他点也能跑出去。单个区间内的加速值等于该区间的长度，一旦到达另一个区间，这一次逃脱的加速值就最大为原加速值+该区间的长度。

这样我们就得到了最简单最简单，最暴力最暴力的算法，一个区间一个区间判断，如果能够跑出去就让ans加上该区间的长度。复杂度显然是$n^2$，会TLE66分。然后我们往上叠一个很简单的优化。

如果在向左右猪突的过程中进入了一个原本就能跑出去的区间，由于是从旁边的区间进入该区间，所以这时的加速值一定比原本在该区间开始时大，而原本的加速值就足以跑出去，那么这时绝对也能跑出去。我们只需要用一个数组记录下能够跑出去的区间，或者用一个变量记录下最右边的能跑出去的区间的编号，一旦进入该区间就更新该变量（不过这点空间还没到用不起的地步）。

这题的数据强度显然不足，上面的本质还是$n^2$算法，一旦设置一个全部都跑不出去的数据点就能卡洗你，官方的正解也要求用$nlogn$算法，仍然推荐研究一下。以下为参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;;
long long n,ans;
bool mk[100005];
struct grass{
    long long s,p;//大小与位置 
}gra[100005];
bool cmp(grass a,grass b){
    return a.p<b.p;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>gra[i].s>>gra[i].p;
    sort(gra+1,gra+n+1,cmp);//使草堆按照位置排序 
    for(int i=1;i<n;i++){//枚举起始点为第i个草堆的区间 
        int now=gra[i+1].p-gra[i].p,l=i,r=i+1;
        bool flag=1;
        while(1){
            bool done=1;
            if(gra[l].s<now&&l>=0){//向左猪突 
                done=0;
                now+=gra[l--].p-gra[l].p;
            }
            if(gra[r].s<now&&r<=n+1){//向右猪突 
                done=0;
                now+=gra[r+1].p-gra[r++].p;
            }
            if(r==n+1||l==0||mk[l]==1){//到达边界或者向左猪突到了一个本身就能出去的区间 
                flag=0;
                break;
            }
            if(done)
                break;//在能够打破草堆的情况下一直尝试向左右猪突 
        }
        if(flag)
            ans+=gra[i+1].p-gra[i].p;
        else mk[i]=1;//flag==0该区间能够跑出去，记录下来。 
    }
    cout<<ans;
}
```
I'm Schwarzkopf Henkal.

---

## 作者：kuikuidadi (赞：1)

# 思路

首先按照坐标排序，然后我们从前往后处理每一个点，并把这个点设为起点 $st$，然后尽量左左右右左左扩展出最大的空间，如果到头了说明可行，否则说明 $st\to r$ 这个区间的每个点都不可能走出去，用并查集维护向左的第一个可行的点，并且将路径上的标记传递一下。

# code


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,flag[100001],fa[10001];
struct node{
	int s,l;
}a[100001];
bool cmp(node a,node b){
	return a.l<b.l;
}
int find(int x){
	if(fa[x]!=x){
		fa[x]=find(fa[x]);
		if(flag[x]==1) flag[fa[x]]=1;
	}
	return fa[x];
}
bool check(int x){
	int l=x,r=x+1;
	while(l&&r<=n){
		if(a[r].l-a[l].l>a[l].s){
			fa[l]=find(l-1);
			l=find(l-1);
		}else if(a[r].l-a[l].l>a[r].s) r++;
		else break;
		if(flag[l]==1) return 1;	
	}
	if(l<1||r>n) return 1;
	for(int i=x;i<r;i++){
		flag[i]=-1;
		fa[i]=l;
	}
	return 0;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].s>>a[i].l;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<n;i++){
		if(flag[i]==-1){
			ans+=a[i+1].l-a[i].l;
			continue;
		}
		if(!check(i)) ans+=a[i+1].l-a[i].l;
		else flag[find(i)]=1;
	}
	cout<<ans;
}
```

---

## 作者：大眼仔Happy (赞：0)

[Kevinx 提醒我加的题目传送门](https://www.luogu.com.cn/problem/P3127)

~~目前还算不出来时间复杂度，但是反正他就是 AC 了（也可能只是数据太水）。~~

考虑找一些性质：

- 如果从 $x$ 出发能逃出去，那么若从 $y$ 出发，中途可以到 $x$，说明从 $y$ 出发也可以逃出去。

- 如果从 $x$ 出发不能逃出去，而最后拓展的区间是 $[l,r]$，那么这里的所有点都不能逃出去。

从左边扫到右边，我们考虑如果从 $x$ 出发，向左向右拓展，要优先向左，因为我们是从左边扫过来的，如果向左找到一个可以逃出的点，那么就直接逃出了。如果不能拓展了，那么这一段区间都可以不用算了，直接全部不行（性质 2）。

因为优先向左，可以且有必要用一个并查集路径压缩一下？（这就对应标签了吧）向右就不行了，因为没有性质 1 的这一种传递性。

观察这种写法，往左跳完之后，下一步只能是往右跳，不然左边可以一次跳到更远的点（路径压缩）。而且这样的话，往左跳是 $O(n)$ 次，往右跳是？？？（如果被卡的话往右就用一个 $\log$ 二分着跳，直接跳到最远的能跳到的点，总没有问题的吧）

![](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGkAAAA9CAYAAACunUfbAAAAAXNSR0IArs4c6QAAAARnQU1BAACxjwv8YQUAAAAJcEhZcwAADsMAAA7DAcdvqGQAAAQXSURBVHhe7Zo9bxQxEIavQaRMRwqQUlAhiogqdNdRIaWhoolERRfR0FLQ5wdQXI/Ej+AXpEG0KUCKFAlO4UMXCSVG72onsXO72fHszK5950eyxH3s6/G8nrEPZeIKyVNMyoBiUgYUkzKgmJQBSZt0/vGTmz+duh/3HyYxzp49ryMbliRNujw/rxLy581bd/Hte/3u+Px89GQU45I0afFh5v6+e1+/ShsYd3l2Vr+yITmTqMVdnJ7W76TNvy9fK6NQUVZmJWNSqi2OC5mFDYaNpkkyJuXU4m4DGwwbTfOsGt0kLAYHMHZhLi2Og2YLHM0kOnuwmFWFWmDfW+DgJuV+9kiBWdKqGtykVTl7YkFV/XrxUmTUoCbldr3WRmrUICYhqHVscU34v6u4mJsEg7B7EFzhGlwmuJiahPaGHVMMWiYJk0p7ux3/at51RpmZFLNT1hnOZaKYlABdRrFNggiVZxeYbJX/J8ECGNWW2+hK6qqQcpuT05ZbVZOKQf0wMWk+n7udnR03mUyq8fneA/f4zt2r100D38dzhWVMTELCj46Oqn9zzyF8f3Nzs9FAGtBdLBb1E+uDqklUPUg20P7RenBw4A4PD+tX6wGOibZNLjKJzAEWP1pPTk6qOba3t91sNqvfHQdUtN/Su4ZFO48yCZPDJGpxoK1ENTg+Pnb7+/tXix+jBaKiUdlckJvpdKpqVGUSRCkRbWBSfM83ZcjfQ2O0QFQxqhmVHYO2UUElwagmyCBMDlPor2F+v3o92HWbWmDXZtIA68UcqGJUswRNo1gmIWBqcRZ/DRNLW5wa+BuyL9DAxkL++pgVrHZjY6Ox7zclxfIs6gIL77NomNBUkVj77u6uikE+0MNc0ktQkP22vt9kEtoejJIOXDml0A7te/u7ua7YS0IMdAnCBokliBJ9f2trq351DZKRIrTwmxXBhUyiMwjGx14ShmCpRJqqJnWQXNEOrdcKg7RbnCYrYZIUWmvqa16Kru+hnAu4JMAcDKw5ZZZMokOZFtBnSFrQUOCSgBhzII8oDcAFqZiUMGjn1C1yIOkoqW1Kxm3s7e1Vbb3re6kQRHlzodxhhVSb+xznkoTPY3/g+rnpM4glk2KRPMNFqs19jnNJwuexv6HwXF98jUBNIq4RUBtSbcuYOGjM72sEahJxy4RItS1j4qAxv68RqEnELRMi1baMiYPG/L5GoCYRt0yIVNsyJg4a8/sagZpE3DIhUm3LmDhozO9rBGoSccuESLUtY+KgMb+vEahJxC0TItW2jImDxvy+RqAmEbdMiFTbMiYOGvP7GoGaRNwyIVJty5g4aMzvawRqEnHLhEi1LWPioDG/rxGo4QPJsKJpLu4YE435fY1xV7OiFJMyAAnWGEQxKQOKSRlQTEoe5/4DZAc2YEu61s8AAAAASUVORK5CYII=)

这个代码没用二分。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int inline read()
{
	int num=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=(num<<3)+(num<<1)+(ch^48);ch=getchar();}
	return num*f;
}
int n,ans;
struct data{int siz,pos;}a[N];
bool cmp(data A,data B){return A.pos<B.pos;}
int fa[N],vis[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
bool check(int x)
{
	if(vis[x]==-1)return false;
	int l=x,r=x+1;
	while(l&&r<=n)
	{
		int dis=a[r].pos-a[l].pos;
		if(dis>a[l].siz)l=fa[l]=find(l-1);
		else if(dis>a[r].siz)r++;
		else break;
		if(vis[l]==1)return true;
	}
	if(!l||r>n)return true;
	fa[x]=l;
	for(int i=x;i<r;i++)vis[i]=-1;
	return false;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=(data){read(),read()};
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<n;i++)
	{
		if(!check(i))ans+=a[i+1].pos-a[i].pos;
		else vis[i]=1;
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：LiveZoom (赞：0)

## Description

给你 $n$ 个干草捆，把这条路分成了 $n-1$ 个区间，问你从多少个点开始走，能够成功逃脱。

## Solution

先按坐标排序，显然在两个干草捆之间的所有点要么都能逃脱，要么都不能逃脱，所以可以枚举区间然后暴力去跑，这样是 $O(n^2)$ 的，有 79 分的好成绩。

考虑优化，还是枚举区间，定义数组 $t$ 表示这个区间是否能逃出去。也就是说当 $t_i$ 等于 $1$ 时，代表这个区间可以逃出去，否则逃不出去。那么我们暴力跑到一个点 $x$ 时，如果 $t_x$ 已经被标记为 $1$ 了，那么就可以判断出可以跑出去，并把当前区间标记为 $1$。否则就一直暴力走，直到能够直接判断走不出去。大概是 $O(n\log n)$ 的。

## Code

```cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

#define db(x) cerr << #x << '=' << x << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define dbg debug("*** Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)

using namespace std;

const int kMaxN = 1e5 + 5;

struct Node {
  int s, p;

  friend bool operator < (const Node& n1, const Node& n2) {
    return n1.p < n2.p;
  }
} a[kMaxN];

int n, ans;
int s[kMaxN], p[kMaxN];
bool tra[kMaxN];

bool check(int x) {
  int l = x, r = x + 1;
  for (; l && r <= n; ) {
    int nw = p[r] - p[l];
    if (nw <= s[l] && nw <= s[r]) {
      return 0;
    }    
    if (nw > s[l]) {
      --l;
      if (!l || tra[l]) {
        return tra[x] = 1;
      }
    }
    if (nw > s[r]) {
      ++r;
      if (r > n || tra[r - 1]) {
        return tra[x] = 1;
      }
    }
  }
  return 0;
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i].s >> a[i].p;
  }
  sort(a + 1, a + 1 + n);
  for (int i = 1; i <= n; ++i) {
    s[i] = a[i].s, p[i] = a[i].p;
  }
  tra[0] = tra[n] = 1;
  for (int i = 1; i < n; ++i) {
    if (!check(i)) {
      ans += p[i + 1] - p[i];
    }
  }
  cout << ans << endl;
  return 0;
}
```

---

