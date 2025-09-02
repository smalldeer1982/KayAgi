# Correct Placement

## 题目描述

Polycarp has invited $ n $ friends to celebrate the New Year. During the celebration, he decided to take a group photo of all his friends. Each friend can stand or lie on the side.

Each friend is characterized by two values $ h_i $ (their height) and $ w_i $ (their width). On the photo the $ i $ -th friend will occupy a rectangle $ h_i \times w_i $ (if they are standing) or $ w_i \times h_i $ (if they are lying on the side).

The $ j $ -th friend can be placed in front of the $ i $ -th friend on the photo if his rectangle is lower and narrower than the rectangle of the $ i $ -th friend. Formally, at least one of the following conditions must be fulfilled:

- $ h_j < h_i $ and $ w_j < w_i $ (both friends are standing or both are lying);
- $ w_j < h_i $ and $ h_j < w_i $ (one of the friends is standing and the other is lying).

For example, if $ n = 3 $ , $ h=[3,5,3] $ and $ w=[4,4,3] $ , then:

- the first friend can be placed in front of the second: $ w_1 < h_2 $ and $ h_1 < w_2 $ (one of the them is standing and the other one is lying);
- the third friend can be placed in front of the second: $ h_3 < h_2 $ and $ w_3 < w_2 $ (both friends are standing or both are lying).

In other cases, the person in the foreground will overlap the person in the background.

Help Polycarp for each $ i $ find any $ j $ , such that the $ j $ -th friend can be located in front of the $ i $ -th friend (i.e. at least one of the conditions above is fulfilled).

Please note that you do not need to find the arrangement of all people for a group photo. You just need to find for each friend $ i $ any other friend $ j $ who can be located in front of him. Think about it as you need to solve $ n $ separate independent subproblems.

## 说明/提示

The first test case is described in the statement.

In the third test case, the following answers are also correct:

- $ [-1, -1, 1, 2] $ ;
- $ [-1, -1, 1, 1] $ ;
- $ [-1, -1, 2, 1] $ .

## 样例 #1

### 输入

```
4
3
3 4
5 4
3 3
3
1 3
2 2
3 1
4
2 2
3 1
6 3
5 4
4
2 2
2 3
1 1
4 4```

### 输出

```
-1 3 -1 
-1 -1 -1 
-1 -1 2 2 
3 3 -1 3```

# 题解

## 作者：胖头鱼学员 (赞：5)

# CF1472E

## [CF传送门](http://codeforces.com/problemset/problem/1472/E)
## [洛谷传送门](https://www.luogu.com.cn/problem/CF1472E)

## $QuestionMeaning$

$Polycarp$想要给他的朋友们拍一张照片，他的朋友们都有$h$（身高）、$w$（宽度）两个数值，当一个人$A$的身高比另外一个人$B$的身高矮，且宽度比他小时，$A$可以站在$B$的前面，或者当$A$身高比$B$宽度小时，且宽度比$B$身高小时，$A$可以躺在$B$前面（小，意为严格小于）。

现在$Polycarp$想知道每个人是否有对应的人可以站或躺在他的前面，如果有，则输出那个人的编号，若有多个，则输出任意一个，如果没有则输出$-1$。

## $Solution$

考虑贪心：

设对于任意一个$i$（$1 \leq i \leq n$）$w > h$

设有下标为$i$、$j$的两个小朋友，且两个小朋友的$h$和$w$满足$1$式时：
$$
w_i < w_j
$$
此时多了一个下标为$k$小朋友，且与下标为$j$的小朋友的$h$、$w$满足$2$式时：
$$
w_j < w_k
$$
那么三个小朋友一定满足$3$式：
$$
w_i < w_j < w_k
$$
由此可得，若有一个满足了$1$式的情况下，若满足$2$式，那么$i$就可以匹配$j$，$j$就可以匹配$k$。

则将其排序后处理即可。

## $Code$
```
#include <algorithm>
#include <iostream>

using namespace std;

const int kMaxN = 2e5 + 1;

struct E {
  int h, w, p;
} e[kMaxN];
int l[kMaxN];

int t, n, p;

int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> e[i].h >> e[i].w;
      if (e[i].h > e[i].w) {
        swap(e[i].h, e[i].w);
      }
      l[i] = i;
    }
    sort(l + 1, l + 1 + n, [](int i, int j) { return e[i].h < e[j].h || (e[i].h == e[j].h && e[i].w > e[j].w); });
    p = l[1];
    for (int i = 1; i <= n; i++) {
      if (e[l[i]].w > e[p].w) {
        e[l[i]].p = p;
      } else {
        e[l[i]].p = -1;
        p = l[i];
      }
    }
    for (int i = 1; i <= n; i++) {
      cout << e[i].p << " ";
    }
    cout << endl;
  }
  return 0;
}
```

---

## 作者：二gou子 (赞：5)

~~排序+贪心水题~~

## 思路

首先你先要想明白这个题到底啥意思。说白了，就是对于两个二元组$(x1,y1)$和$(x2,y2)$，如果第一个二元组中的最大值大于第二个二元组中的最大值，第一个二元组中的最小值大于第二个二元组中的最小值，那么就符合条件。

想到这里，这个题其实已经切了。首先把$maxx$和$minn$存到结构体里，按照身高排序。这样我们正着循环的时候会发现，对于第$x$个人，符合条件的人（能站到他前面的人）只可能在他前面。这样我们维护一个最小值，代表每个二元组中**较小的那个值**得最小值。一边循环一边更新，这样就可以在循环到第$x$个人的时候，保存之前的次小值，和当前二元组的次小值比较即可。（因为前面的人较大值一定都小于第$x$个人的较大值）。

## Code
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<algorithm>
#include<cstring>
#include<set>
#include<queue>
using namespace std;
const int N=200005,INF=2147483647;
int T,n,numm,maxn,minx;
int ans[N];
struct People{
	int maxx,minn,num;
}peo[N];
bool cmp(People a,People b){
	return a.maxx<b.maxx;
}
bool cmp2(People a,People b){
	return a.num<b.num;
}
int main()
{
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			ans[i]=-1;
		}
		for(int i=1,a,b;i<=n;i++){
			scanf("%d%d",&a,&b);
			peo[i].maxx=max(a,b);
			peo[i].minn=min(a,b);
			peo[i].num=i;
		}
		sort(peo+1,peo+1+n,cmp);
		
//		for(int i=1;i<=n;i++){
//			printf("maxx=%d minn=%d num=%d\n",peo[i].maxx,peo[i].minn,peo[i].num);
//		}
		minx=INF;
		for(int i=1,t=i+1;i<=n;i=t){
			while(peo[i].maxx==peo[t].maxx&&t<=n) t++;//提前把较大值相等的二元组都处理出来，这样可以保证前面维护的次小值的最小值所代表的人（有点绕）的较大值一定小于当前人的较大值
			for(int j=i;j<=t-1;j++){		
				if(peo[j].minn>minx){
					ans[peo[j].num]=numm;
				}
			}
			for(int j=i;j<=t-1;j++){
				if(peo[j].minn<minx){
					minx=peo[j].minn;
					numm=peo[j].num;
				}
			}
		}
		sort(peo+1,peo+1+n,cmp2);
		for(int i=1;i<=n;i++){
			printf("%d ",ans[i]);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：EC75 (赞：3)

这是一篇 Python 题解。准确地说，是一篇 pypy3 题解。

### 思路

我们先对所有人进行排序。

现在让我们遍历所有的人，在排序后的数组中查找人的位置（通过二分查找）。显然，只有排好序的数组中比被找到的人晚的人才能站在我们面前（他们的身高都严格低于我们的身高）。

在所有这些人中，我们选择最瘦的人。为了快速找到这样的人，我们可以为排序数组的每个后缀找到一个最瘦的人。

为了处理一个人躺着的情况，我们需要交换宽度和高度并重复上面的算法。

### 代码

本来不想放代码的，为了过审，还是放上吧
```python
import sys,io,os
input=sys.stdin.readline
from collections import *
import bisect,math
def inp(): return input()
def inpu(): return int(inp())
def sep(): return map(int,input().split())
def strsep(): return map(str,input().split())
def lis(): return list(sep())
def stringlis(): return list(strsep())
def main():
    how_much_noob_I_am = 1
    how_much_noob_I_am = inpu()
    for i in range(how_much_noob_I_am):
        n=inpu()
        l=[]
        m=[]
        d=defaultdict(int)
        pp=[]
        for i in range(n):
            a,b=sep()
            l.append([a,b])
            m.append([a,b])
            d[(a,b)] = i+1
            pp.append([a,b])
        l.sort(key=lambda x:(x[0],x[1]))
        m.sort(key=lambda x:(x[0],x[1]))
        mm=[]
        ll=[]
        for i in l:
            ll.append(i[1])
        for i in m:
            mm.append(i[1])
        p=[]
        ans=float("inf")
        for i in mm:
            ans=min(ans,i)
            p.append(ans)
        ans=float("inf")
        r=[]
        for i in ll:
            ans=min(ans,i)
            r.append(ans)
        ans=[-1]*(n)
        for i in range(n):
            if ans[i]!=-1:
                continue
            lo=0
            hi=n-1
            ans2=-1
            while(lo<=hi):
                mid=(lo+hi)//2
                if r[mid]<pp[i][1]:
                    hi=mid-1
                    ans2=mid
                else:
                    lo=mid+1
            if ans2==-1:
                continue
            if l[ans2][0]<pp[i][0] and l[ans2][1]<pp[i][1]:
                ans[i] = d[tuple(l[ans2])]
        for i in range(n):
            if ans[i]!=-1:
                continue
            lo=0
            hi=n-1
            ans2=-1
            while(lo<=hi):
                mid=(lo+hi)//2
                if p[mid]<pp[i][0]:
                    hi=mid-1
                    ans2=mid
                else:
                    lo=mid+1
            if ans2==-1:
                continue
            if m[ans2][0]<pp[i][1] and m[ans2][1]<pp[i][0]:
                ans[i] = d[tuple(m[ans2])]
        print(*ans)
if __name__ == '__main__':
    main()
```

---

## 作者：洛璟 (赞：2)

## 原题翻译：

Polycarp 想要给他的朋友们拍一张照片，他的朋友们都有h（身高）、w（宽度）两个数值，当一个人 $A$ 的身高比另外一个人 $B$ 的身高矮，且宽度比他小时， $A$ 可以站在 $B$ 的前面，或者当 $A$ 身高比 $B$ 宽度小时，且宽度比 $B$ 身高小时，$A$ 可以躺在 $B$ 前面（小，意为严格小于）。

现在 Polycarp 想知道**每个人**是否有对应的人可以站或躺在他的前面，如果有，则输出那个人的编号，若有多个，则输出**任意一个**，如果没有则输出-1。
## Solution：
这道CF1700分的题目卡了我好几天（

难度估计为绿题或者黄题？

那么我们一开始最简单的方法，也许大家都会想到一个一个去比较，时间复杂度为$O(N^2)$，当场爆炸。

于是我们想到先给其中一个关键字排序，再去维护另外一个关键字，然而最粗暴的比较还是$O(N^2)$。

于是我们想要优化这个比较过程，怎么办？

我们发现，在排序过后，我们只需要找排在当前这个数前面的数就行了，同时，由于输出的是任意一个，所以我们可以发现，符合当前这个数的答案，也有可能是下一个数的答案，因此我们只要找出在这个数之前的的尽可能小的数，然后不断更新最小数，并判断此数是否符合答案即可。看不懂的同学还可以看看代码中的注释。

~~时间复杂度比较玄学，我自己也无法计算（悲~~

```cpp
//洛璟の代码( •̀ ω •́ )✧
#include<bits/stdc++.h> 
using namespace std;
int ans[1919810];
struct cccp
{
    int h, w;
}a[1919810];
int t, n;
inline int read()//快读
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ '0');
        c = getchar();
    }
    return x * f;
}
bool cmp(cccp a, cccp b)
{
    return a.h < b.h;
}
int main()
{
    t = read();
    while (t--)
    {

        n = read();
        vector<cccp> v(n);
        for (int i = 0;i < n;i++)
        {
            ans[i] = -2;
            a[i].h = read();
            a[i].w = read();
            if (a[i].h > a[i].w) swap(a[i].h, a[i].w);//保证h序列为小的数（但是用大的进行比较也行，但一定是两个中最小或最大
            v[i] = cccp{ a[i].h,i };
        }
        sort(v.begin(), v.end(), cmp);//从小到大排序，只维护另外一个无序的序列
        int j = 0, qwq = -1;//qwq用于存储当前次数符合要求的最小的数的序号
        for (int i = 0;i < n;i++)
        {
            int nw = v[i].w;//当前数字的序号
            while (a[nw].h > v[j].h)//找出在这个数之前（不一定符合要求）的最小数，同时由于为严格小于，所以当遍历到当前数组时while循环便会结束
            {
                if (qwq == -1 || a[qwq].w > a[v[j].w].w) qwq = v[j].w;
                j++;
            }
            if (qwq != -1 && a[nw].w > a[qwq].w) ans[nw] = qwq;//若符合要求则加入答案中
        }
        for (int i = 0;i < n;i++)
        {
            printf("%d ", ans[i] + 1);
        }
        printf("\n");
    }
    return 0;
}
```


---

## 作者：Fairicle (赞：2)

感觉我的做法比较麻烦？

看到题目给出两种条件，考虑合并这两种条件，不然分别计算需要容斥。

容易观察出，只有 $\max(w_i,h_i)>\max(w_j,h_j)$ 且 $\min(w_i,h_i)>\min(w_j,h_j)$ 时 $j$ 能站到 $i$ 前面。

那么我们令 $A_i=max(w_i,h_i),B_i=min(w_i,h_i)$，那么问题就转化成了一个二维偏序问题。

~~于是我就跟个 SB 一样敲了个数点~~

这题并不是求个数，而是任意输出一个能站在 $i$ 前面的人。

于是更简单了，把 $A$ 排序（套路），然后维护 $B$ 的最小值的那个人就行了。

其实还要离散化一下，相等的数也要判一下，~~真麻烦~~

code：
```cpp
#include"bits/stdc++.h"
using namespace std;
#define ri register int
#define ll long long
#define N 300010
int t,n,m,pre[N],s[N<<1],top,ans[N];
inline ll rd(){
    ll x=0;
    char ch=getchar();
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch)) {x=x*10+(ch^48);ch=getchar();}
    return x;
}
struct node{
    int h,w,a,b;
    int idx;
}a[N];
inline bool cmp1(node a,node b){return a.a<b.a;}
int main(){
    t=rd();
    while(t--){
        for(ri i=1;i<=n;++i) pre[i]=c[i]=0;top=0;
        n=rd();
        for(ri i=1;i<=n;++i) a[i].h=rd(),a[i].w=rd(),a[i].idx=i,s[++top]=a[i].h,s[++top]=a[i].w;
        sort(s+1,s+1+top);
        int len=unique(s+1,s+1+top)-s-1;
        for(ri i=1;i<=n;++i) a[i].h=lower_bound(s+1,s+1+len,a[i].h)-s,a[i].w=lower_bound(s+1,s+1+len,a[i].w)-s;
        for(ri i=1;i<=n;++i) a[i].a=max(a[i].h,a[i].w),a[i].b=min(a[i].h,a[i].w);sort(a+1,a+1+n,cmp1);
        for(ri i=1;i<=n;++i) if(a[i-1].a==a[i].a) pre[i]=pre[i-1];else pre[i]=i-1;a[n+1].a=-1;int mn=0x3f3f3f3f,pos=-1;
        for(ri i=1;i<=n;++i){
            if(a[i].a!=a[i+1].a){
                for(ri j=pre[i]+1;j<=i;++j) ans[a[j].idx]=(a[j].b-1>=mn)?pos:-1;
                for(ri j=pre[i]+1;j<=i;++j) if(mn>a[j].b) pos=a[j].idx,mn=min(a[j].b,mn);
            }
        }
        for(ri i=1;i<=n;++i) cout<<ans[i]<<" ";cout<<endl;
    }
    return 0;
}
```


---

## 作者：guanyf (赞：1)

### 题意

- 有 $n$ 个人，当一个人的长和宽都小于另一个人时，则他可以站在另一个人的前面。你也可以将一个人翻转过来，即长和宽交换。求每个人是否都有一个人站在他面前，有则输出能站在他前面的任意一个人的编号。

- $1\le n \le 2 \cdot 10 ^ 5$

### 思路
**一眼就可以看出来一道贪心题目**。

先讲一遍**错误**思路：对于每个人来说，如果他的长大于宽，则将长宽反转。接着按照长为第一关键字排序。显然，最前面的就是最小的，因此我们可以判断第一个人是否站在当前这个人的前面，能则输出。

上述思路主要的问题就在：我们可以保证前面元素的长一定是小于等于当前元素的长，但并不保证宽小于等于当前元素的宽，举个例子：

```latex
1
3
1 10
2 1
100 10
```

第三个人明显可以选择第二个人，但我们却选择了第一个人。为了尽可能的保证选择的人的宽度小于当前元素的宽度，我们可以记下来所有**长度小于当前元的**所有元素中宽度最小的元素，如果这个元素的宽度依然大于等于当前元素，则记为 $-1$，否则为最小的元素。

时间复杂度：$\operatorname{O}(n \log n)$。

#### 代码
```cpp
#include <bits/stdc++.h>
#define Pii pair<int, int>
#define int long long
using namespace std;
const int MAXN = 2e5 + 5;
struct node {
  int x, y, id;
  bool operator<(const node &t) const { return x == t.x ? y < t.y : x < t.x; }
} a[MAXN];
int T, n, v1[2], v2[2], ans[MAXN];
Pii change(Pii x, Pii y) {
  if (x.first > y.first) x.second = y.second, x.first = y.first;
  return x;
}
signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> T; T--;) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i].x >> a[i].y, a[i].id = i, ans[i] = -1;
      if (a[i].x > a[i].y) swap(a[i].x, a[i].y);
    }
    sort(a + 1, a + 1 + n);
    v1[0] = v2[0] = INT_MAX, v1[1] = v2[1] = 0;
    for (int i = 1; i <= n; i++) {
      Pii t;
      if (a[i - 1].x < a[i].x) {
        t = change({v1[0], v1[1]}, {v2[0], v2[1]});
        v1[0] = t.first, v1[1] = t.second, v2[0] = INT_MAX, v2[1] = 0;
        if (a[i].y > v1[0]) ans[a[i].id] = v1[1];
        t = change({v2[0], v2[1]}, {a[i].y, a[i].id});
        v2[0] = t.first, v2[1] = t.second;
      } else {
        if (a[i].y > v1[0]) ans[a[i].id] = v1[1];
        t = change({v2[0], v2[1]}, {a[i].y, a[i].id});
        v2[0] = t.first, v2[1] = t.second;
      }
    }
    for (int i = 1; i <= n; i++) {
      cout << ans[i] << ' ';
    }
    cout << '\n';
  }
  return 0;
}
```


---

## 作者：Φρανκ (赞：0)

题意：给定 $n$ 个长方形，对每个长方形求另一长方形使后者长宽均小于前者。

核心思想：排序

解：

容易发现每个长方形都是由“长”（较长边）与“宽”（较短边）确定的。

因此可以想到将所有长方形按长为第一关键字，宽为第二关键字排序，然后对每个长方形分配前面长方形中宽最短的。但是这样长相等的长方形可能会对彼此造成干扰。

改为按宽逆序排列可以解决这个问题：这样可以保证一个长方形之前的宽小于它的长方形的长一定也小于它。

因此先编号再排序，完成后再按编号输出即可。

代码：
```
#include <bits/stdc++.h>
using namespace std;
long long t, n, temp;
struct ppl
{
	long long h, w, i, res;
}a[200001];//长方形
bool cmp(ppl x, ppl y)
{
	if(x.h!=y.h)
		return x.h<y.h;
	else
		return x.w>y.w;
}//排序
bool rec(ppl x, ppl y)
{
	return x.i<y.i;
}//排回原形式
int main()
{
	cin>>t;
	for(int i=1; i<=200000; i++)
		a[i].i=i;//预编号
	for(int i=1; i<=t; i++)
	{
		cin>>n;
		for(int j=1; j<=n; j++)
			cin>>a[j].h>>a[j].w;
		for(int j=1; j<=n; j++)
			if(a[j].h<a[j].w)
				swap(a[j].h, a[j].w);
		for(int j=1; j<=n; j++)
			a[j].res=-1;//初始化
		sort(a+1, a+n+1, cmp);
		temp=1;
		for(int j=1; j<=n; j++)
			if(a[j].w>a[temp].w)
				a[j].res=a[temp].i;
			else
				temp=j;//依次分配，维护最小值
		sort(a+1, a+n+1, rec);
		for(int j=1; j<=n; j++)
			cout<<a[j].res<<" ";
		cout<<endl;//输出
	}
	return 0;
}

```

---

## 作者：Inui_Sana (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1472E)

解题思路：贪心

根据题意，我们可以知道，如果 $i$ 能站或躺在 $j$ 前面，那么 $\min(h_i,w_i)<\min(h_j,w_j) \land \max(h_i,w_i)<\max(h_j,w_j)$，否则易证这是不可能的。所以不妨将一个二元组中小元素的放前面，大元素的放后面。然后排序一遍，根据贪心，对于每一个二元组，看看它之前第一关键字比它小的有没有第二关键字比它小的即可。这可以通过维护一个最小值来实现。

值得注意的是，因为题目中提到的都是严格小于，所以等于是不行的，需要在处理最小值时做一些处理。

code：

```cpp
int n,b,ans[maxn];
vector<int> vec;
struct node{
	int a,b,id;
	bool operator<(const node &x)const{return a<x.a;}
}d[maxn];
void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&d[i].a,&d[i].b);
		if(d[i].a>d[i].b)swap(d[i].a,d[i].b);
		d[i].id=i;
	}
	sort(d+1,d+n+1);
	int minx=-1;
	memset(ans,-1,sizeof ans);
	for(int i=1;i<=n;i++){
		vec.pb(i);
		if(~minx&&d[i].b>d[minx].b)ans[d[i].id]=d[minx].id;
		if(d[i].a!=d[i+1].a){
			for(int i=0;i<vec.size();i++){
				if(minx==-1||d[vec[i]].b<d[minx].b)minx=vec[i];
			}
			vec.clear();
		}
	}
	vec.clear();//因为是多组数据，所以最后也要清空。
	for(int i=1;i<=n;i++)printf("%d ",ans[i]);
	puts("");
}
signed main(){
	int t=1;
	scanf("%d",&t);
	while(t--)solve();
}


---

