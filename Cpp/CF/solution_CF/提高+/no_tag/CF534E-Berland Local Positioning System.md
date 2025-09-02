# Berland Local Positioning System

## 题目描述

在伯兰德的首都，有一辆公交车在主街上行驶。该街道从中心广场开始，看起来就像一条非常长的线段。街道上设有 $ n $ 个公交站，第 $ i $ 个车站距离中心广场的距离为 $ a_{i} $，所有车站之间的距离各不相同。车站按照距离从小到大的顺序编号，即对于每个 $ i $ 从 1 到 $ n-1 $ 有 $ a_{i} < a_{i+1} $。公交车从第一个车站出发，依次经过第 2、3 等车站，一直行驶到第 $ n $ 个车站，然后调头返回第一个车站，沿途按相反顺序经过所有中间车站。之后，它又朝着第 $ n $ 个车站行驶。公交车全天不停地在这条路线上往返。

公交车装配了伯兰德当地的定位系统。当公交车经过某个车站时，系统会记录下该车站的编号。

这个系统的一个重要功能是可以回答关于公交车在某些路径段上行驶距离的询问。系统模块会接收包含路径某段区间内车站集合的信息，每个车站编号出现的次数等同于公交车反复经过的次数。这个模块返回路径区间的行程距离（如果无法唯一确定行程距离，则返回 -1）。复杂性在于，请求中的车站编号并非以访问顺序排列，而是按非递减顺序排列。

例如，如果总共有 6 个车站，公交车某段路径从第 5 号站开始，结束于第 3 号站，并按以下顺序经过：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF534E/af31d14addb6c65568bda25f3a02c691a79c56de.png)，则这个路径的请求形式为：$ 3, 4, 5, 5, 6 $。如果在从第 5 号站到第 3 号站途中，公交车还经过了第 1 号站（即考虑它到达第 3 号站的第二次路程），请求形式则变为：$ 1, 2, 2, 3, 3, 4, 5, 5, 6 $。

您需要编写程序实现此功能。

## 说明/提示

第一个测试用例展示了题目中的第一个例子。

第二个测试用例展示了题目中的第二个例子。

在第三个样例中，存在两条可能的路径且长度不同，因此所求的路径长度无法确定。

在第四个样例中，尽管存在两条不同的路径对应于请求，但它们的长度相同，因此路径长度是唯一确定的。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
6
2 3 5 7 11 13
5
3 4 5 5 6
```

### 输出

```
10
```

## 样例 #2

### 输入

```
6
2 3 5 7 11 13
9
1 2 2 3 3 4 5 5 6
```

### 输出

```
16
```

## 样例 #3

### 输入

```
3
10 200 300
4
1 2 2 3
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
3
1 2 3
4
1 2 2 3
```

### 输出

```
3
```

# 题解

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2400}$
---
### 解题思路：

首先统计出每一个位置被经过的次数。由于端点的特殊性，将每一个端点的经过次数乘 $2$，方便处理。认为在端点之外有一个特殊点，遇到这个点时转向，并且不会产生距离。

对于起点和终点不同的平凡情况，整个路径的情况其实非常清晰，此时有且仅有两种数值出现。一种情况是从两段开始的若干长度经过次数比中间的若干多，此时是从一个变化点向靠近的一端走到另一个变化点。另一种则相反，是从一个变化点走到距离较远的那一个端点返回或者直接没有经过端点。

换言之，就是一条路径的经过次数恰好等于连个端点中经过次数较少的那一个。

---
特殊的，如果起点和终点一样，此时路径无法被确定，表现为每一个位置上的经过次数都相等。由于有且仅有一条路径被经过的次数比别的少一次，一般情况下应当输出 $-1$，但如果所有的路径的长度都相等，也是可以确定路径长度的。

---
注意开 $\text{long long}$。

---

就这也 $\text{2400}$？

---
### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
int n,m,p[200005],x,a[200005],dis[200005],ans;
bool check(int *c){
	for(int i=2;i<=n;i++)
	if(c[i]!=c[i-1])
	return 0;
	return 1;
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		dis[i]=a[i]-a[i-1];
	}
	dis[1]=dis[2];
	scanf("%lld",&m);
	for(int i=1;i<=m;i++){
		scanf("%lld",&x);
		p[x]++;
	}
	p[1]*=2;p[n]*=2;
	if(check(p)){
		if(check(dis))printf("%lld\n",p[1]*(n-1)*dis[1]-dis[1]);
		else printf("-1\n");
		return 0;
	}
	for(int i=2;i<=n;i++)
	ans+=dis[i]*min(p[i-1],p[i]);
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：SIGSEGV (赞：0)

假设车从点1向右（位置递增的方向）开出，行驶了$m$个站点后停止。记录每个位置的到达次数$c$。如果$b$与输入的询问序列中每个数字出现的次数$c$相同，则本次车程的距离珂以成为答案。

用两个指针$l$，$r$代表一次车程的起点和终点。每次计算完当前车程后，就将$l$，$r$各自往对应的方向挪一步并进行相关信息的更新。时间复杂度$O(N)$
```cpp
int n, m, a[N], cnt, b[N], c[N];
struct Pos
{
    int p, d;
};
void move(Pos &p)
{
    if (p.p == 1 && p.d == -1)
        p.d = 1;
    if (p.p == n && p.d == 1)
        p.d = -1;
    p.p += p.d;
}
int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    ll cur = 0;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    int t1;
    cin >> m;
    for (int i = 1; i <= m; i++)
        cin >> t1, ++b[t1];
    Pos l{1, 1}, r{1, 1};
    ++c[1];
    for (int i = 1; i <= m - 1; i++)
    {
        int last = r.p;
        move(r);
        ++c[r.p];
        cur += abs(a[last] - a[r.p]);
    }
    for (int i = 1; i <= n; i++)
        if (b[i] != c[i])
            ++cnt;
    ll ans = -1;
    for (int i = 1; i <= n * 2; i++)
    {
        if (!cnt)
        {
            if (ans == -1 || ans == cur)
                ans = cur;
            else
            {
                cout << -1 << endl;
                return 0;
            }
        }
        if (--c[l.p] == b[l.p])
            --cnt;
        else if (c[l.p] + 1 == b[l.p])
            ++cnt;
        int ll = l.p, rr = r.p;
        move(l);
        move(r);
        cur -= abs(a[l.p] - a[ll]);
        cur += abs(a[r.p] - a[rr]);
        if (++c[r.p] == b[r.p])
            --cnt;
        else if (c[r.p] - 1 == b[r.p])
            ++cnt;
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：sunben (赞：0)

思路：

题目保证一定有路径了,令每个点经过的次数为bi,特别的:首尾端点是读入的两倍 

那么连接i,j的边的经过次数就是min(bi,bj)

我们发现,当且仅当首尾都存在时，并且边权不是两两相同时才会是-1 

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read()
{
	ll s=0; bool f=0; char ch=' ';
	while(!isdigit(ch)) {f|=(ch=='-'); ch=getchar();}
	while(isdigit(ch)) {s=(s<<3)+(s<<1)+(ch^48); ch=getchar();}
	return (f)?(-s):(s);
}
#define R(x) x=read()
inline void write(ll x)
{
	if(x<0) {putchar('-'); x=-x;}
	if(x<10) {putchar(x+'0'); return;}
	write(x/10); putchar((x%10)+'0');
}
#define W(x) write(x),putchar(' ')
#define Wl(x) write(x),putchar('\n')
const int N=200005;
int n,m,a[N],dis[N],b[N];
int main()
{
	int i,x; bool limit=1,flg; ll jyl=0;
	R(n); a[0]=0; for(i=1;i<=n;i++) R(a[i]),dis[i]=a[i]-a[i-1];
	R(m); for(i=1;i<=m;i++) R(x),b[x]++,b[x]+=(x==1||x==n)?1:0;
	for(i=2;i<=n;i++) limit&=(b[i]==b[i-1]);
	if(limit)
	{
		flg=1;
		for(i=2;i<=n-1&&flg;i++) flg&=(dis[i]==dis[i+1]);
		jyl=(ll)(1ll*(a[n]-a[1])*b[1]-dis[2]);
		Wl((flg)?jyl:-1);
	}
	else
	{
		for(i=2;i<=n;i++) jyl=1ll*(jyl+1ll*dis[i]*min(b[i],b[i-1]));
		Wl(jyl);
	}
	return 0;
}
```


---

