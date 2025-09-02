# A Story of One Country (Easy)

## 题目描述

本题与下一题仅在约束条件上有所不同。

Petya 决定在暑假期间访问 Byteland。结果发现，这个国家的历史非常独特。

最初，在现在的 Berland 这片土地上有 $n$ 个不同的国家。每个国家都有自己的领土，在地图上表示为一个矩形。矩形的边平行于坐标轴，顶点的坐标均为整数。任意两个国家的领土没有重叠，但可能会相互接触。随着时间的推移，有时两个国家会合并成一个国家。只有当它们的领土并集仍然是一个矩形时，才能合并。最终只剩下一个国家——Byteland。

最初，每个国家的领土内都有一座矩形城堡。城堡的边平行于坐标轴，顶点的坐标均为整数。有些城堡可能与对应国家的边界、边或其他城堡相接触。奇迹般地，在所有合并之后，这些城堡依然完好无损。不幸的是，我们现在仅能通过这些城堡的位置来还原最初各国的领土。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1181E1/f468812bfa112254fc0a226123d17950651543de.png) Byteland 的可能形成过程。蓝色部分为城堡。Petya 很好奇为什么没有留下关于最初各国的任何信息。他怀疑整个故事是假的。有人向他推荐了你，认为你很聪明。请你判断是否存在一种可能的初始领土划分，使得这个故事成立。

## 说明/提示

下图展示了第一个和第二个样例中的城堡。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1181E1/65c05eff44019e46877011da23e6739903c4b116.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1181E1/13651d9028d4dc1ad40258518684f2d9fe9c5d09.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
0 0 1 2
0 2 1 3
1 0 2 1
1 1 2 3
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4
0 0 2 1
1 2 3 3
2 0 3 2
0 1 1 3
```

### 输出

```
NO
```

# 题解

## 作者：xkcdjerry (赞：6)

经典思路，可惜我没想出来

如果从最初矩形开始的话不光需要考虑边界还需要考虑 `merge` 顺序，考虑正难则反：从最终矩形开始，每次把一个矩形拆成两个，最终使得每个矩形恰好包含一个城堡。

考虑一个含有多个城堡的矩形，一个切割可行当且仅当它不穿过任何一个城堡。又由于纵切/横切均只受城堡在 $x$ 坐标或 $y$ 坐标上的范围影响，可以将其转化为将一系列线段分为两部分的问题。而对于每个切出来的部分递归分治即可解决。  
伪代码：
```
solve(castles)
    sort castles according to x1
    for i in 1,n-1
        if max(castles[1~i].x2)<=castles[i+1].x1 && solve(castles[1~i])&&solve(castles[i+1~n])
            return true
    
    sort castles according to y1
    for i in 1,n-1
        if max(castles[1~i].y2)<=castles[i+1].y1 && solve(castles[1~i])&&solve(castles[i+1~n])
            return true

    return false
```

发现对于 $x$ 和 $y$ 均可能递归若干次，复杂度无明确上界。（感觉如果记忆化的话可以 $n$ 的若干次方）

考虑三个可以被任意分割的城堡群 $A,B,C$，那么显然先分出哪一个对答案并无影响，且将这三个两两分开后一定不会使得情况变劣。（即不会出现本来可以完全分割的局面变得无法完全分割的局面）  
由此，我们可以在遇到第一个可以分割的点时直接返回 `solve(L) && solve(R)`。  

考虑复杂度：每层排序花 $O(l \log l)$ 时间，遍历花 $O(l)$ 时间。复杂度 $f$ 满足：  
$$f(n)=f(n-x)+f(x)+O(n \log n)$$
在 $x=1$ 的情况下取到极大值 $f(n)=O(n^2 \log n)$，能够通过本题 $n=1000$ 的数据范围。

代码：
```c++
#include <cstdio>
#include <vector>
#include <algorithm>
#define N 1010
#define inf 0x3f3f3f3f
using std::sort;
using std::vector;
struct rect {int x1,x2,y1,y2;};
inline int max(int x,int y) {return x>y?x:y;}
void swap(int &x,int &y) {int t=x; x=y; y=t;}
bool judge(vector<rect> v)
{
	int n=v.size();
	if(n<=1) return true;
	for(int XY=0;XY<2;XY++)
	{
		sort(v.begin(),v.end(),[&](rect x,rect y){return x.x1<y.x1;});
		int mxx=-inf; for(int i=0;i<n-1;i++)
		{
			mxx=max(mxx,v[i].x2);
			if(mxx<=v[i+1].x1)
			{
				vector<rect> L,R;
				for(int j=0;j<=i;j++) L.push_back(v[j]);
				for(int j=i+1;j<n;j++) R.push_back(v[j]);
				return judge(L)&&judge(R);
			}
		}
		for(auto &i:v) swap(i.x1,i.y1),swap(i.x2,i.y2);
	}
	return false;
}
int main()
{
	int n; vector<rect> v;
	scanf("%d",&n); for(int i=0;i<n;i++)
	{
		int x1,x2,y1,y2;
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		v.push_back({x1,x2,y1,y2});
	}
	puts(judge(v)?"YES":"NO");
}
```

---

## 作者：__kd (赞：3)

个人觉得这题没什么思维难度。

首先会发现最后分割出来的“王国”经过 $n-1$ 次合并可以合成整个网格，且只要是合法分割方案，怎么合并都是可以的。

我们把它反过来，也就是说，在分割过程中，能分就分，对答案合法性是没有影响的。

模拟每次分割即可，时间复杂度 $O(n^2\log n)$。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N=1e5+5;
int n;
struct mt{
	int x1,y1,x2,y2;
}p[N];
inline bool cmpx(mt x,mt y){return x.x1<y.x1;}
inline bool cmpy(mt x,mt y){return x.y1<y.y1;}
inline int read(){
    register int x=0,t=0;
    static char ch=getchar();
    while(!isdigit(ch)) t|=(ch=='-'),ch=getchar();
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return t?-x:x;
}
inline bool solve(int l,int r){
	if(l==r) return 1;
	sort(p+l,p+1+r,cmpx);
	int maxn=p[l].x2;
	for(register int i=l+1;i<=r;i++){
		if(maxn<=p[i].x1) return solve(l,i-1)&solve(i,r);
		else maxn=max(maxn,p[i].x2);
	}
	
	sort(p+l,p+1+r,cmpy);
	maxn=p[l].y2;
	for(register int i=l+1;i<=r;i++){
		if(maxn<=p[i].y1) return solve(l,i-1)&solve(i,r);
		else maxn=max(maxn,p[i].y2);
	}
	return 0;
}
signed main(){
	n=read();
	for(register int i=1;i<=n;i++){
		p[i].x1=read();
		p[i].y1=read();
		p[i].x2=read();
		p[i].y2=read();
	}
	cout<<(solve(1,n)?"YES":"NO");
	return 0;
}
```

---

## 作者：wxzzzz (赞：2)

### 前置

为方便表述，令矩形 $i$ 的最左、最右、最下、最上的值分别为 $l(i),r(i),d(i),u(i)$。

### 思路

贪心地考虑，能分就分肯定不劣。

现在考虑对于一段区间 $[l,r]$ 中的矩形，如何将其在横坐标上分为若干个区间。

首先按矩形的最右端排序，顺序枚举 $i=l\sim r$。

若 $\displaystyle\min_{j=i+1}^r l(j)\ge r(i)$，则可在 $r(i)$ 处将区间 $[l,r]$ 划分为 $[l,i],[i+1,r]$。

在在纵坐标上划分同理。

上述过程可以递归去做，递归到的每一层只进行横坐标或纵坐标的划分，能划分哪种就划分哪种，若都不能就代表该区间不合法。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, t[1005];
struct sq {
    int l, r, d, u;
} a[1005];
bool cmp1(sq s1, sq s2) {
    return s1.r < s2.r;
}
bool cmp2(sq s1, sq s2) {
    return s1.u < s2.u;
}
bool solve(int ql, int qr) {
    if (ql == qr)
        return 1;

    bool ck = 1, flag = 0;
    sort(a + ql, a + qr + 1, cmp1);
    t[qr] = a[qr].l;

    for (int i = qr - 1; i >= ql; i--)
        t[i] = min(t[i + 1], a[i].l);

    for (int i = ql, lst = ql; i <= qr; i++) {
        if (i == qr || t[i + 1] >= a[i].r) {
            if (lst == ql && i == qr)
                continue;

            ck &= solve(lst, i);
            lst = i + 1;
            flag = 1;
        }
    }

    if (flag)
        return ck;

    flag = 0;
    sort(a + ql, a + qr + 1, cmp2);
    t[qr] = a[qr].d;

    for (int i = qr - 1; i >= ql; i--)
        t[i] = min(t[i + 1], a[i].d);

    for (int i = ql, lst = ql; i <= qr; i++) {
        if (i == qr || t[i + 1] >= a[i].u) {
            if (lst == ql && i == qr)
                continue;

            ck &= solve(lst, i);
            lst = i + 1;
            flag = 1;
        }
    }

    if (!flag)
        return 0;

    return ck;
}
int main() {
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> a[i].l >> a[i].d >> a[i].r >> a[i].u;

    if (solve(1, n))
        cout << "YES";
    else
        cout << "NO";

    return 0;
}
```

---

