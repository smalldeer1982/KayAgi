# Dima and Staircase

## 题目描述

Dima's got a staircase that consists of $ n $ stairs. The first stair is at height $ a_{1} $ , the second one is at $ a_{2} $ , the last one is at $ a_{n} $ ( $ 1<=a_{1}<=a_{2}<=...<=a_{n} $ ).

Dima decided to play with the staircase, so he is throwing rectangular boxes at the staircase from above. The $ i $ -th box has width $ w_{i} $ and height $ h_{i} $ . Dima throws each box vertically down on the first $ w_{i} $ stairs of the staircase, that is, the box covers stairs with numbers $ 1,2,...,w_{i} $ . Each thrown box flies vertically down until at least one of the two following events happen:

- the bottom of the box touches the top of a stair;
- the bottom of the box touches the top of a box, thrown earlier.

We only consider touching of the horizontal sides of stairs and boxes, at that touching with the corners isn't taken into consideration. Specifically, that implies that a box with width $ w_{i} $ cannot touch the stair number $ w_{i}+1 $ .

You are given the description of the staircase and the sequence in which Dima threw the boxes at it. For each box, determine how high the bottom of the box after landing will be. Consider a box to fall after the previous one lands.

## 说明/提示

The first sample are shown on the picture.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF272C/141a6409b5823a4a8bdecfcecc6a55967701b504.png)

## 样例 #1

### 输入

```
5
1 2 3 6 6
4
1 1
3 1
1 1
4 3
```

### 输出

```
1
3
4
6
```

## 样例 #2

### 输入

```
3
1 2 3
2
1 1
3 1
```

### 输出

```
1
3
```

## 样例 #3

### 输入

```
1
1
5
1 2
1 10
1 10
1 10
1 10
```

### 输出

```
1
3
13
23
33
```

# 题解

## 作者：_Haoomff_ (赞：2)

个人认为难度在橙左右吧。算模拟又不太算模拟的一道题。

**题意**：有 $n$ 级台阶和 $m$ 个箱子，将这 $m$ 个箱子抛出后，请你求出每个箱子的停放高度。若一个箱子碰到了台阶或碰到了其它箱子，它就会水平停在那个高度，~~科学不存在了~~。

**思路**：当前宽度为 $w_i$ 的箱子，要么碰到第 $w_i$ 级台阶停下，要么碰到之前抛下的箱子然后停下。因为保证楼梯不下降，所以每次记录最高点即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,a[100005],m,res; 
inline ll max(ll a,ll b){
	return a>b?a:b;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i];
	cin>>m;
	for(int w,h;m--;){
		cin>>w>>h;
		res=max(res,a[w]);
		cout<<res<<"\n";
		res+=h; 
	}
	return 0;
}
```

---

## 作者：Lagibol (赞：2)

### ~~这道题居然在我的线段树考试中~~

题意：

Dima有一个楼梯，由n阶台阶组成。台阶从左到右的高度依次为a1,a2,…an（保证不下降）。Dima将宽度为wi，高度为hi的箱子对齐楼梯左上角垂直放下，箱子会掉到楼梯上。箱子掉落在楼梯上的位置规定如下：
箱子底部碰到楼梯或是其他箱子顶部就会水平停放在该位置。

Dima连续将m个箱子抛出后，求每个箱子的停放高度。

思路：
**宽度为wi的箱子，要么会在第wi级阶梯处被卡住，要么会被提前扔的箱子卡住**

然后就暴力了qwq
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
long long h[100002];
long long lmax(long long xx,long long yy)
{
  if (xx<yy)
    return yy;
  return xx;
}
int main( )
{
//  freopen("louti.in","r",stdin);
//  freopen("louti.out","w",stdout);
  long long n,i,j,m,w,hi,maxx=0;
  cin>>n;
  for (i=1;i<=n;++i)
    scanf("%lld",&h[i]);
  cin>>m;
  for (i=1;i<=m;++i)
    {
      scanf("%lld%lld",&w,&hi);
      maxx=lmax(maxx,h[w]);
      cout<<maxx<<endl;
      maxx+=hi;
	}
  return 0;
}
```


---

## 作者：Adam1101 (赞：0)

### [题目传送门](problem/CF272C)

### 题意简述
在一个很神奇的每级不一定一样高的台阶上，有人把 $ m $ 个宽度为 $ w_i $，高度为 $ h_i $ 的箱子对齐左上角扔下，箱子底部碰到其他箱子或阶梯就会停下来，求每个箱子停放的高度。

### 思路
每个箱子掉下后都会把 $ 1 $ 至 $ w_i $ 的台阶的高度变成 $ a_{w_i} + h_i $，所以每次记录前 $ w_i $ 级台阶的最高高度，当前箱子一定会落在这个高度，直接输出即可。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int a[100010];

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	cin >> m;
	int max_height = -1; //前 w_i 级台阶的最高高度。
	while (m--) {
		int w, h;
		cin >> w >> h;
		max_height = max(max_height, a[w]); //与第 w_i 级台阶取最大值，原因是 a_i 单调不降，a_wi 一定是前 w_i 个中最大的。
		cout << max_height << "\n";
		max_height += h; //别忘了加上当前箱子的高度哟。
	}
	return 0;
}
```

---

## 作者：xujingyu (赞：0)

## 题意

有一段楼梯，现从左上角丢一个 $w_i\times h_i$ 的积木下来，积木在碰到楼梯或别的积木后停下，求其高度。

## 解法

就是像那个积木游戏，暴力很容易想，模拟即可，由于是左上角，那么对于每个 $w_i$ 和 $h_i$，该积木会掉在 $\max\limits_{j=1}^{w_i}a_j$ 的位置。掉下去后，循环从 $1$ 到 $w_i$ 更新 $a$ 数组。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,m,a[100001],w,h,big;

signed main()
{
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",&a[i]);
	scanf("%d",&m);
	while(m--)
	{
		scanf("%d%d",&w,&h);
		big = -1;
		for(int i = 1;i <= w;i++) big = max(big,a[i]);
		printf("%d\n",big);
		for(int i = 1;i <= w;i++) a[i] = big + h;
	}
	return 0;
}
```
然后 TLE 了，因为 $m,w\leq10^5$，需要减少一个循环。

* 考虑楼梯是**不下降**的，所以取 $\max$ 那个循环可以直接改为 `big=a[w]`；
* 再看第二个内循环，可以想到不需要更新每个 $a$，因为是从左上角下来，所以放上一个积木后再放就一定在该积木上面，所以直接将 $big+h_i$ 即可；
* 此时，`big=a[w]` 又需要改为 `big=max(big,a[w])`，因为可能在该地方的积木很高，别的积木放了好些个上去还是不如之高。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n,m,a[100001],w,h,big;

signed main()
{
	scanf("%lld",&n);
	for(int i = 1;i <= n;i++) scanf("%lld",&a[i]);
	scanf("%lld",&m);
	while(m--)
	{
		scanf("%lld%lld",&w,&h);
		big = max(big,a[w]);//修改1、3
		printf("%lld\n",big);
		big += h;//修改2
	}
	return 0;
}
```

---

## 作者：Gao_l (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF272C)

## 题意

有一个长度为 $n$ 的台阶，有 $m$ 个箱子，要把 $m$ 个箱子自左上角抛出后每个箱子停放的高度。如果一个箱子接触到了在它前面抛出的箱子或台阶，就会停下。

## 思路

由于箱子要么接触到之前的箱子，要么碰到台阶。所以用 $ans$ 记录最高点，与 $w_i$ 位的台阶取最大值(台阶单调不减)记录即可

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long //十年OI一场空，不开LongLong见祖宗
const int N=1e5+5;
int n,a[N],q,ans=0;
signed main(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    cin >> q;
    while(q--){
        int x,y;
        cin >> x >> y;
        ans=max(ans,a[x]);
        cout << ans << "\n";
        ans+=y;
    }
    return 0;
}
```

[AC记录](https://codeforces.com/contest/272/submission/273693823)

---

## 作者：minVan (赞：0)

**解题思路**

对于第 $i$ 个箱子，其停放高度要么是第 $w_i$ 个阶梯的高度，要么是之前的最高停放高度。两者取大为最终答案。

**AC 代码，请勿抄袭。**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5;
int n, m, a[N];
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	cin >> m;
	int ans = 0;
	while(m--) {
		int w, h;
		cin >> w >> h;
		ans = max(ans, a[w]);
		cout << ans << '\n';
		ans += h;
	}
	return 0;
}
```

---

## 作者：AstaSunch_ (赞：0)

# $\bf{0x00}$ 序

蒟蒻的第 $\bf\color{red}{31}$ 篇题解，复赛考挂了，写个题解纪念一下。

# $\bf{0x01}$ 题

$m$ 个宽度为 $w_i$、高度分别为 $h_i$ 的箱子被抛在了 $n$ 级楼梯上，箱子碰到楼梯台面或者其他箱子就会落在这个高度，求出这些高度。

# $\bf{0x02}$ 解

这些高度肯定是单调递增的，并且箱子要么会被碰到前一个箱子，要么会落到楼梯上。因此每次直接记录最高点就可以了。注意开 `long long`。

# $\bf{0x03}$ 文

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll lt[int(1e6+6)],n,m,w,h,MAX=0;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>lt[i];
	cin>>m;
	for(int i=1;i<=m;i++){
		cin>>w>>h;
		MAX=max(MAX,lt[w]);
		cout<<MAX<<endl;
		MAX+=h;
	}
}
```


---

## 作者：封禁用户 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF272C)

# First 题意

有 $n$ 级楼梯和 $m$ 个箱子，依次输入箱子的长宽，问最后箱子落在哪？

箱子在落下时只要有一格碰到了其他箱子或楼梯，就停止掉落，~~虽然这不科学~~。

# Second 思路

呃，这题就是模拟，但又不完全是，其实可以理解为在线处理。

每次记录最高点，因为楼梯是递增的，所以可以记录前几个的最高点。

# Third Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define max(x, y) x > y ? x : y
#define min(x, y) x < y ? x : y
il ll rd(){
	ll x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		x = (x << 3) + (x << 1) + ch - '0';
		ch = getchar();
	}
	return x * f;
}
il void wt(ll a){
	if (a < 0){
		a = -a;
		putchar('-');
	}
	if (a > 9) wt(a / 10);
	putchar (a % 10 + '0');
}
il void sp(){
	putchar(' ');
}
il void et(){
	putchar('\n');
}
ll n, m, high[100005], ans, w, h;
int main(){
	n = rd();
	for (int i = 1; i <= n; i++) high[i] = rd();
	m = rd();
	while (m--){
		w = rd(), h = rd();
		ans = max(ans, high[w]);
		wt(ans), et();
		ans += h;
	}
	return 0;
}

```

---

## 作者：York佑佑 (赞：0)

## 题意
一个楼梯由 $n$ 阶台阶组成。台阶从左到右的高度依次为 $a_1,a_2,…a_n$（保证不下降）。Dima 将宽度为 $w_i$，高度为 $h_i$ 的箱子对齐楼梯左上角垂直放下，箱子会掉到楼梯上。

箱子底部碰到楼梯或是其他箱子顶部就会水平停放在该位置。Dima 连续将 $m$ 个箱子抛出后，求每个箱子的停放高度。

**注：这里的高度从零开始**
## 分析
本题差不多定橙，难度在理解题意。
### 样例解释
```cpp
5
1 2 3 6 6
4
1 1
3 1
1 1
4 3
```
 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF272C/141a6409b5823a4a8bdecfcecc6a55967701b504.png)
 
第一个箱子放在高度为 $1$ 的位置，第二个箱子在高度为 $2$ 的位置放不下，故放在高度为 $3$ 的位置。第三个箱子搭在第二个箱子之上，故放在高度为 $4$ 的位置。最后一个箱子在高度为 $5$ 的位置上放不下， 故放在高度为 $6$ 的位置。

现在，思路很明显了吧！宽度为 $w_i$ 的箱子会有两种情况在高度为 $h_i$ 的位置放不下：
- 宽度超过第 $w_i$ 级阶梯。
- 这个高度在前面已经有箱子放置，导致这个箱子放不下。

如果在第 $i$ 层放不下这个箱子，则将 $i$ 加一。直到第 $i$ 层放得下这个箱子为止。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;//十年OI一场空，不开long long见祖宗 
ll a[1000010],n,m,w,h,maxx;
int main()
{
	cin>>n;
	for(ll i=1;i<=n;i++)	cin>>a[i];
	cin>>m;
	for(ll i=1;i<=m;i++)
	{
		cin>>w>>h;
		maxx=max(maxx,a[w]);//设置最大高度 
		cout<<maxx<<endl;//输出 
		maxx+=h;//高度加上h 
	}
	return 0;
}
```



---

