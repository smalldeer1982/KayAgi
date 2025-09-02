# [USACO11MAR] Bovine Bridge Battle S

## 题目描述

Farmer John 的每头牛（共 $N$ 头，$4 \le N \le 1,000$）都耐心地在主牧场等待，其中第 $i$ 头牛位于整数坐标 $(X_i, Y_i)$ 上（$-1,000,000,000 \le X_i \le 1,000,000,000$，$-1,000,000,000 \le Y_i \le 1,000,000,000$）。

这些牛希望组成四个一组，以便玩他们的新宠卡牌游戏「桥牌」。每组必须满足一个重要的约束条件：如果且仅如果在平面上存在某个点 $X$（并且不与潜在四牛组的任何四个点重合），使得围绕该点 $X$ 将组内任意一头牛旋转 $180$ 度后得到组内的另一头牛的位置，四头牛才可以组队。

请帮助这些牛确定可以组成桥牌组的四牛组合的数量。

例如，假设有八头牛分别站在八个点上：

|
f\*
```cpp
|             a = (-3, 1)    e = (-1, 1) 
b*     |             b = (-2, 2)    f = ( 0, 3) 
a      e  |             c = (-3, 0)    g = ( 2, 0) 
*     *  |             d = (-2, 0)    h = ( 3, 0) 
```
c  d     |     g  h
---------\*--\*-----+-----\*--\*---------

|
那么，三个合法的四牛组合是 {a, b, e, d}（它们围绕点 $(-2, 1)$ 旋转），{b, c, e, f}（围绕点 $(-1.5, 1.5)$），以及 {c, d, g, h}（围绕点 $(0,0)$）。

提供的牛的位置都是不同的，尽管它们的顺序没有特定的规则。此外，答案将适合一个有符号的 32 位整数。


## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
8 
-3 0 
-2 0 
-1 1 
0 3 
2 0 
-3 1 
3 0 
-2 2 
```

### 输出

```
3 
```

# 题解

## 作者：feecle6418 (赞：4)

**UPD1:增加了一种解法**

**UPD2:增加了另一种解法**

---

这么简单的题竟然没有题解？我来发一个吧。

首先，四个点关于某点中心对称，显然就形成了一个广义的平行四边形（共线也算）。因此这四个点一定满足 $x_1+x_2=x_3+x_4,y_1+y_2=y_3+y_4$。因此我们把所有的 $x_1+x_2,y_1+y_2$ 合成一个 $pair$，再插入一个map或是哈希表内，即可通过扫描得到答案。注意每一个平行四边形都要被算两次，因此答案要除以二。

代码：
```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
int n,ans,x[1005],y[1005];
map<pair<int,int>,int>p;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&x[i],&y[i]);
	}
	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++){
			p[make_pair(x[i]+x[j],y[i]+y[j])]++;
		}
	}
	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++){
			ans+=p[make_pair(x[i]+x[j],y[i]+y[j])]-1;
		}
	}
	printf("%d\n",ans/2);
	return 0;
}
```

---

扩展：

本校OJ上时间只有500ms，上面方法TLE，如何做？

【优化1】

可以观察到pair是STL，非常慢。我们完全可以用**一个数**来表示坐标。具体地说，由于坐标值和范围为 $[-2e9,2e9]$，我们可以用 **一种略大于 $2e9$ 的进制** 来把两个数压成一个数，比如 $2147400000$ 进制。

【优化2】

$map$ 的时间复杂度是一个 $\log$ 的，总时间复杂度为 $O(n^2\log n)$（因为 $O(\log n^2)=O(2\log n)=O(\log n)$。）我们完全可以省掉这个 $\log$：只需把 $map$ 换为哈希表即可。为了省事，你可以直接用STL，比如 $\mathrm{unordered\_map,gp\_hash\_table,cc\_hash\_table}$ 等（**第一个需要选C++11，后面两个是 $pb\_ds$，需要引用相应头文件**），把时间复杂度优化到 $O(n^2)$。

【优化3】

手写 Hash 表。直接卡到最优解qwq

【时间对比】

- [优化前：](https://www.luogu.org/record/23193683) 用时**2.42s**
- [优化后（STL的Hash）：](https://www.luogu.org/record/23196705) 用时**445ms**
- [优化后（手写Hash）：](https://www.luogu.org/record/23200175) 用时**272ms**

可以看到，优化的效果非常明显。为了防止抄袭，这里就不放最优解的代码了 ~~（实际上是不想被挤下去qwq）~~ 

非最优代码（使用gp_hash_table）：
```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#include<ext/pb_ds/trie_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
using namespace std;
int n,ans,x[1005],y[1005];
gp_hash_table<long long,int>p;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&x[i],&y[i]);
	}
	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++){
			p[((long long)x[i]+x[j])*2147400000ll+(y[i]+y[j])]++;
		}
	}
	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++){
			ans+=p[((long long)x[i]+x[j])*2147400000ll+(y[i]+y[j])]-1;
		}
	}
	printf("%d\n",ans/2);
	return 0;
}
```

---

## 作者：Nuyoah_awa (赞：2)

### 题目大意
给定 $n$ 个点，从中选取 $4$ 个点使其可以组成平行四边形，求取点的方案数。
### 题目分析
首先想到暴力，每回枚举 $4$ 个点，判断它们是否能组成平行四边形。

时间复杂度是 $\mathcal O(n ^ 4)$ 的，肯定会 TLE。

然后我们来观察如图矩形：
![](https://s1.ax1x.com/2023/04/08/ppHncE4.png)

我们设四个顶点分别为：$A(x_a, y_a), B(x_b, y_b), C(x_c, y_c), D(x_d, y_d)$。

我们做矩形 ABCD 的对角线交点 E，过 E 点垂直于 x 轴的直线可以表示为 $x = \dfrac{x_a + x_c}{2}$，同时也可以表示为 $x = \dfrac{x_b + x_d}{2}$。所以 $x_a + x_c = x_b + x_d$。同理，过 E 点垂直于 y 轴的直线可以表示为 $y = \dfrac{y_a + y_c}{2}$，同时也可以表示为 $x = \dfrac{y_b + y_d}{2}$。所以 $y_a + y_c = y_b + y_d$。

反之，如果四个点满足 $x_a + x_c = x_b + x_d$， $y_a + y_c = y_b + y_d$ 那么，这四个点组成的图形一定是一个广义平行四边形。

于是，我们可以将两个点的 ${x_1 + x_2, y_1 + y_2}$ 作为这个点的哈希值，如果有两对点的哈希值一样，就说明这两对点组成的图形为平行四边形。

于是，运用哈希，我们每回枚举两个点，求出哈希值，再求出有多少对点的哈希值一样。

最后的时间复杂度是 $\mathcal O(n ^ 2)$ 的，但是要开 O2 才能过，否则会 TLE 一个点。

### code
```cpp
#include <iostream>
#include <cstdio>
#include <map>

using namespace std;

struct node{
	int a, b;
};
int n, ans, x[1005], y[1005];
map <pair <int, int>, int> Hash;

int main()
{
	scanf("%d", &n);
	for(int i = 1;i <= n;i++)
		scanf("%d %d", &x[i], &y[i]);
	for(int i = 1;i <= n;i++)
		for(int j = i + 1;j <= n;j++)
			Hash[{x[i] + x[j], y[i] + y[j]}]++;
	for(int i = 1;i <= n;i++)
		for(int j = i + 1;j <= n;j++)
			ans += Hash[{x[i] + x[j], y[i] + y[j]}] - 1;
	printf("%d", ans / 2);
	return 0;
}
```

---

## 作者：玉树临风英俊潇洒 (赞：1)

# 题目大意

给定 $n$ 个点，从中选取 $4$ 个点使其可以组成平行四边形，求方案数。

# 题目分析

1. 这四个点构成了一个广义的平行四边形，也就是说共线也可以。
2. 四点满足以下。$x_1 + x_2 = x_3 + x_4$，$y_1 + y_2 = y_3 + y_4$。

3. $x_1 + x_2 \times x_1 + x_2$，$y_1 + y_2 \times y_1 + y_2$。这几个合成一个 pair，插入一个 map 或者哈希表里再统计。
4. 这样做时间复杂度是二次方。

---

## 作者：xiaoyuchenp (赞：1)

较为简单的普及题。

**题面大意**

在一个平面坐标系中有 $n$ 个点，从中选 $4$ 个关于某点中心对称的点，求总方案数。

**思路**

选出的 $4$ 个点关于某点中心对称，很容易想到它们构成了一个广义的平行四边形（即共线也算的平行四边形）。由基础几何知识可知该四点一定满足 $x_1 + x_2 = x_3 + x_4$ 且 $y_1 + y_2 = y_3 + y_4$，具体证明这里就不赘述了。

接下来的思路就很明显了。把预处理出来的 $x_1 + x_2$ 与 $y_1 + y_2$ 作为该点的哈希值，如果有两对点的哈希值一样，则该两对点组成的图形为广义的平行四边形。

时间复杂度 $O(n^{2})$。

具体实现方式是将 $x_1 + x_2$ 与 $y_1 + y_2$ 合成一个 $\texttt{pair}$，插入一个 $\texttt{map}$ 或者哈希表里再统计，这里采用 $\texttt{map}$ 的实现方式。

最后注意一点：提交时需要开 O2 优化，否则会 TLE。

**code**

```cpp
#include<bits/stdc++.h>
#define MAXN 1005
using namespace std;
struct point{
	int x,y;
}g[MAXN];
int n,ans;
map<pair<int,int>,int>mp;

int main(){
	ios::sync_with_stdio(NULL);
	cin.tie(NULL);cout.tie(NULL);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>g[i].x>>g[i].y;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)mp[{g[i].x+g[j].x,g[i].y+g[j].y}]++;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)ans+=mp[{g[i].x+g[j].x,g[i].y+g[j].y}]-1;
	cout<<ans/2;
	return 0;
}
```

---

## 作者：小恐 (赞：1)

这么~~水~~难得题居然没多少人做

那么我只好来水一波了

那位大佬的题解说map和哈希表，天哪，本蒟蒻表示完全听不懂。

于是我就想了个别的方法。

首先说一下中心对称，其实四个点组成了广义的平行四边形，对面的两个点连接的线段的中点就是这个平行四边形的中心。

所以我们需要把每两个点连接的线段的中点坐标都记录下来，一共就不超过1000000，所以数组完全能存下。

然后排个序，看看有几组一样的中点，便是答案了。

上代码：
```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;
pair<double,double> cha[1000005];
int ans;//答案 
pair<int,int> a[1005];//pair是STL中的一个好东西，就是将两个变量打包 
int main()
{
	int n;
	scanf("%d",&n);
	int te=0;//记录目前最后一个中点的下标 
	for(int i=1;i<=n;++i)
		scanf("%d%d",&a[i].first,&a[i].second);//pair形变量第一个是.first,第二个是.second
	for(int i=1;i<n;++i)
		for(int j=i+1;j<=n;++j)//枚举每两个点 
		{
			++te;
			cha[te].first=(a[i].first+a[j].first)/2.0; 
			cha[te].second=(a[i].second+a[j].second)/2.0;//求出他们的中点，由于可能是小数，要除以2.0	
		}
	sort(cha+1,cha+te+1);//排序，pair自动比较大小（先第一个数，如一样再第二个数 ）
	pair<double,double> now=cha[1];//now记录现在的pair 
	int cnt=1;//记录now的个数 
	for(int i=2;i<=te;++i)
	{
		if(now==cha[i])//如果和now一样 
			++cnt;//now的个数+1 
		else
			ans+=cnt*(cnt-1)/2,cnt=1,now=cha[i];//根据上一个now的个数增加ans，设置新now 
	}
	printf("%d",ans); 
	return 0;
}
```
[AC凭证](https://www.luogu.com.cn/record/30489742)

珍爱生命，远离抄袭

---

## 作者：__Creeper__ (赞：0)

### 题意

给定 $n$ 个点，从中选 $4$ 个关于某点中心对称的点，求总方案数。

### 思路

设有四个点 $(x_{1},y_{1})$，$(x_{2},y_{2})$，$(x_{3},y_{3})$，$(x_{4},y_{4})$。若这四个点呈中心对称，那么其中必有两对点的中点重合，即：

- $\frac{x_{1} + x_{3}}{2} = \frac{x_{2} + x_{4}}{2}$ 且 $\frac{y_{1} + y_{3}}{2} = \frac{y_{2} + y_{4}}{2}$
- $x_{1} + x_{3} = x_{2} + x_{4}$ 且 $y_{1} + y_{3} = y_{2} + y_{4}$

这时这 $4$ 个点就是关于中点的中心对称点，然后要用一个 map 统计中点就可以了。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5;
int n, ans, x[N], y[N];
map<pair<int, int>, int> mp;

signed main()
{
	cin >> n;
	for ( int i = 1; i <= n; i++ ) cin >> x[i] >> y[i];
	for ( int i = 1; i <= n; i++ )
	{
		for ( int j = i + 1; j <= n; j++ ) mp[{x[i] + x[j], y[i] + y[j]}]++;
	}
	for ( int i = 1; i <= n; i++ )
	{
		for ( int j = i + 1; j <= n; j++ ) ans += mp[{x[i] + x[j], y[i] + y[j]}] - 1;
	}
	cout << ans / 2; // 会被重复算两次，要除以2
	return 0;
}
```

---

## 作者：4041nofoundGeoge (赞：0)

这就是一道数学题。

# 思路

题目中说：

> 给定 $N(4\le n\le 1000)$ 个整点的坐标 $(-10^9\le X_i,Y_i\le 10^9，X_i,Y_i\in Z)$ ，求$card\{\{(X_a,Y_a),(X_b,Y_b),(X_c,Y_c),(X_d,Y_d)\}|\text{四点呈中心对称}\}$。

我们可以理解成用四个点组成一个**平行四边形**，如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/h9hah5g5.png)

如何构造平行四边形呢？推到如下：

根据中点距离坐标公式 $(\frac{x_1+x_2}{2},\frac{y_1+y_2}{2})$ 可以列出来
$$\frac{x_a+x_c}{2}=\frac{x_b+x_d}{2}$$
两边同乘 $2$ 即 $x_a+x_c=x_b+x_d$，同理  $y_a+y_c=y_b+y_d$。

所以只要 $x_a+x_c=x_b+x_d$ 且 $y_a+y_c=y_b+y_d$，那么这个图形一定是平行四边形。

只要我们枚举就可以知道答案。或许你已经想到用哈希了。但这样构造会有一定缺陷，就是会有重复，所以最后计算时还要去重。不去重爆 $0$ 分，去重 $100$ 分。

# 代码

```cpp
#include <bits/stdc++.h>  
using namespace std;  
int n, ans, x[1005], y[1005];  
map<pair<int, int>, int> h;  
int main() {  
    scanf("%d", &n);  
    for (int i = 1; i <= n; i++) cin>>x[i]>>y[i];
    for (int i = 1; i <= n; i++)  
        for (int j = i + 1; j <= n; j++)  
            h[{x[i] + x[j], y[i] + y[j]}]++;  
    for (int i = 1; i <= n; i++)  
        for (int j = i + 1; j <= n; j++)  
            ans += h[{x[i] + x[j], y[i] + y[j]}] - 1;  
    cout<<ans/2;
    return 0;  
}
```

---

## 作者：Hog_Dawa_IOI (赞：0)

题目大意：给定 $n(4 \le n \le 1000)$ 个整点的坐标 $(-10^9 \le x_i,y_i \le 10^9,x_i,y_i \in Z)$，问有多少组点，使得这组点有四个点，且四个点呈中心对称。   
首先我们可以通过样例解释推出知道一个性质：如果四个点呈中心对称，那么这四个点可以被分成两对，使得每对点的横坐标之和相等，纵坐标之和也相等。事实上，这个横坐标之和就是那个中心对称点的横坐标的两倍，纵坐标同理。   
事实上这源于一个坐标系上平行四边形的性质：平面直角坐标系中，平行四边形两组相对顶点的横坐标之和相等，纵坐标之和也相等。证明可以参照[这篇文章](https://mp.weixin.qq.com/s?__biz=MzU4MDc5Njc4Mg==&mid=2247489190&idx=1&sn=232ffcade90fe9db136d4605fe8be6e1&chksm=fd503ea7ca27b7b19f6863a7f9f624421d838aef587853d96627b61be75ba0cc2b5d9c2a667b&scene=27)。       
只要推出了这个性质，整道题便会迎刃而解了。对于每两个点，把它们的横坐标之和与纵坐标之和做成一个 pair，丢进一个 map 里面。然后统计每一种 pair 有多少对，这个数量便是可以和这一对点中心对称的点对的数量。    
但因为每一组点会被计算两次，所以要除以二。
```cpp
#include<map>
#include<cstdio>
using namespace std;
int n,x[1005],y[1005],ans;
map<pair<int,int>,int>dygx;
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld%lld",&x[i],&y[i]);
    for(int i=1;i<n;i++) for(int j=i+1;j<=n;j++) dygx[make_pair(x[i]+x[j],y[i]+y[j])]++;
    for(int i=1;i<n;i++) for(int j=i+1;j<=n;j++) ans+=dygx[make_pair(x[i]+x[j],y[i]+y[j])]-1;
    printf("%d",ans/2);
}
```
令人卑微的是有人手写哈希来代替 map 和 pair，跑得飞快，蒟蒻只有膜拜的份。

---

## 作者：TheCliffSwallow (赞：0)

#### 题意
给定 $n$ 个点，求有几种方案使得其中四个点中心对称。
#### 思路
若这四个点呈中心对称，那么其中必有两对点的中点重合，所以只需求出这 $n$ 个点每两个点的中点，再算重合的点有几对即可，答案就是 $\sum {C_{k}^{2}}$（$k$ 为每个点出现的个数）。
#### Code
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<map>
#include<algorithm>
#include<cmath>
#include<string>
#include<cstring>
#define ll long long
using namespace std;
int n,ans,di;
struct Node{
	int x;
	int y;
}a[1005],s[1000005];
bool cmp(Node x,Node y){
	if(x.x!=y.x)return x.x<y.x;
	return x.y<y.y;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
		a[i].x*=2,a[i].y*=2;//乘 2 是防止之后除出现小数，不过这里不乘后面不除也可以
	}
	sort(a+1,a+n+1,cmp);//将点按从左到右的顺序排序
	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++){
			s[++di].x=(a[i].x+a[j].x)/2;
			s[di].y=(a[i].y+a[j].y)/2;//计算两点的中点
		}
	}
	sort(s+1,s+n*(n-1)/2+1,cmp);//排序中点，之后好计算重复点个数
	for(int i=1;i<=n*(n-1)/2;i++){
		int sum=1;
		while(s[i].x==s[i+1].x&&s[i].y==s[i+1].y)i++,sum++;//计算这个点与他重合的有几个
		ans+=sum*(sum-1)/2;//C(sum,2)
	}
	cout<<ans<<endl;
	return 0;
}
```

---

