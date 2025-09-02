# The Walkway

## 题目描述

There are $ n $ benches near the Main Walkway in Summer Infomatics School. These benches are numbered by integers from $ 1 $ to $ n $ in order they follow. Also there are $ m $ cookie sellers near the Walkway. The $ i $ -th ( $ 1 \le i \le m $ ) cookie sellers is located near the $ s_i $ -th bench.

Petya is standing in the beginning of the Walkway. He will pass near all benches starting from the $ 1 $ -st bench and ending with the $ n $ -th bench. Petya passes the distance between two consecutive benches in $ 1 $ minute. He has a knapsack with an infinite amount of cookies. Petya is going to eat cookies from his knapsack and buy them from cookie sellers during the walk.

Petya eats cookies only near the benches according to the following rule: he will eat the cookie near the $ i $ -th ( $ 1 \le i \le n $ ) bench if and only if at least one of the following conditions holds:

- There is a cookie seller near the $ i $ -th bench. Then Petya will buy a cookie from cookie seller and eat it immediately.
- Petya has not yet eaten a cookie. Then Petya will take a cookie from his knapsack and eat it immediately.
- At least $ d $ minutes passed since Petya ate the previous cookie. In other words, Petya has not eaten a cookie near the benches $ i-1, i-2, \ldots, \max(i-d+1, 1) $ . Then Petya will take a cookie from his knapsack and eat it immediately.

You may assume that Petya eats cookies instantly. Petya will not eat two or more cookies near the same bench.

You want to minimize the number of cookies Petya will eat during his walk. In order to do this, you will ask the administration of the Summer Informatics School to remove exactly one cookie seller from the Walkway before Petya starts his walk.

Please determine the minimum possible number of cookies Petya can eat after removing exactly one cookie seller. Also determine the number of cookie sellers, such that if you remove one of them, Petya will eat the minimum possible number of cookies.

## 说明/提示

In the first test case $ n=6 $ , $ m=2 $ , $ d=2 $ and $ s=[2, 5] $ . If no cookie seller is removed, then Petya will eat $ 4 $ cookies during his walk (note that you have to remove exactly one cookie seller; this case is explained only to show how Petya decides whether to eat a cookie):

- Petya will eat a cookie near the $ 1 $ -st bench since he has not yet eaten a cookie.
- Petya will eat a cookie near the $ 2 $ -nd bench since there is a cookie seller near this bench.
- Petya will not eat a cookie near the $ 3 $ -rd bench since only $ 1<d $ minute passed since he ate a cookie.
- Petya will eat a cookie near the $ 4 $ -th bench since $ 2\ge d $ minutes passed since he ate a cookie.
- Petya will eat a cookie near the $ 5 $ -th bench since there is a cookie seller near this bench.
- Petya will not eat a cookie near the $ 6 $ -th bench since only $ 1<d $ minute passed since he ate a cookie.

If the $ 1 $ -st cookie seller is removed, Petya will eat $ 3 $ cookies (near the benches $ 1 $ , $ 3 $ and $ 5 $ ). If the $ 2 $ -nd cookie seller is removed, Petya will eat $ 4 $ cookies (near the benches $ 1 $ , $ 2 $ , $ 4 $ and $ 6 $ ).

Thus, the minimum number of cookies Petya will eat is $ 3 $ ; there is only one cookie seller such that removing it results in minimizing the number of cookies Petya will eat.

In the second test case

- the removal of the $ 1 $ -st or the $ 2 $ -nd cookie seller results in Petya eating $ 5 $ cookies near the benches $ 1 $ , $ 3 $ , $ 5 $ , $ 7 $ , $ 8 $ ;
- the removal of the $ 3 $ -rd cookie seller results in Petya eating $ 4 $ cookies near the benches $ 1 $ , $ 3 $ , $ 5 $ , $ 7 $ .

Note that the second integer you should output is the number of (that is, amount) cookie sellers, not the index of a cookie seller to remove. Thus, the answer to the second test case is 4 1 because there is only one cookie seller such that removing it results in Petya eating four cookies, which is the minimum possible.

In the third test case Petya will eat $ 4 $ cookies no matter what cookie seller is removed.

Note that Petya is not interested in minimizing the number of cookies he will eat, so he eats cookies whenever it is possible under the rule from the statement.

## 样例 #1

### 输入

```
8
6 2 2
2 5
8 3 2
3 5 8
10 4 9
2 8 9 10
30 5 8
6 8 15 24 29
30 5 8
6 8 12 20 27
8 8 3
1 2 3 4 5 6 7 8
2 2 2
1 2
1000000000 3 20000000
57008429 66778899 837653445```

### 输出

```
3 1
4 1
4 4
6 4
5 2
7 7
1 1
51 1```

# 题解

## 作者：SunnyYuan (赞：18)

## 思路

**注意：所有变量名与原题面相同。**

因为 $1$ 号点必须吃一块饼干，所以我们可以在 $1$ 立一个不可删除的商店，记为 $s_0$。

**注意：如果 $1$ 号附近本身就有一个商店，那就不用立。**

然后我们可以在 $n + 1$ 的位置立一个不可删除的商店，作为一个结束标志，记为 $s_{m + 1}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/3t4jiu3o.png)

---

然后我们可以进行分段分为 $m + 1$ 段，即 $[s_0,s_1),[s_1, s_2),[s_2, s_3),\dots,[s_{m - 1},s_m),[s_m, s_{m + 1})$，**注意是左闭右开区间**。

![](https://cdn.luogu.com.cn/upload/image_hosting/3hijwmij.png)

对于区间 $[l, r)$，我们要吃多少饼干呢？画一画就可以知道要吃 ${\left\lceil\frac{r - l}{d}\right\rceil}$ 。

利用这个公式，我们可以求出不删除商店要吃饼干的数量 $\text{init}$，就是把每一段吃的饼干加起来。

即计算 $\text{init} = \sum\limits_{i = [s_1 = 1]}^{m}\left\lceil\frac{s_{i + 1} - s_i}{d}\right\rceil$。

---

实际上，如果要删掉 $x$ 商店，

那么只要拿最初的 $\text{init}$ 删除 $[s_{x - 1}, s_x)$ 和 $[s_x, s_{x + 1})$ 吃的饼干，这是在清除原有数据。

再加上 $[s_{x - 1}, s_{x + 1})$ ，这是在计算删除商店后这一段会吃掉的饼干。

即 $ans = \text{init} -  \left\lceil\frac{s_x - s_{x - 1}}{d}\right\rceil - \left\lceil\frac{s_{x + 1} - s_x}{d}\right\rceil + \left\lceil\frac{s_{x + 1} - s_{x - 1}}{d}\right\rceil$，就是删掉 $x$ 商店要吃的饼干了。

![](https://cdn.luogu.com.cn/upload/image_hosting/za1oembc.png)

最后我们求出所有 $ans$ 的最小值并统计一下数量 $cnt$ 就可以了。

---

同时，我们要注意，如果 $1$ 号点附近本身就有一个商店，那么删掉该商店以后，答案还是 $\text{init}$，也要参与统计。

## 代码

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 200010;

int n, m, d;
int s[N];

inline int cnt(int l, int r) {
	int sz = r - l;
	if (sz % d == 0) return sz / d;
	return sz / d + 1;
}

void solve() {
	cin >> n >> m >> d;
	for (int i = 1; i <= m; i++) cin >> s[i];
	bool flag = true;
	if (s[1] != 1) {
		flag = false;
		m++;
		for (int i = m; i >= 2; i--) s[i] = s[i - 1];
		s[1] = 1;
	}
	m++;
	s[m] = n + 1;
	
	int init = 0;
	for (int i = 2; i <= m; i++) init += cnt(s[i - 1], s[i]);
	
	int minn = 0x3f3f3f3f3f3f3f3f, ans = 0;
	for (int i = 2; i < m; i++) {
		int g = init - cnt(s[i - 1], s[i]) - cnt(s[i], s[i + 1]) + cnt(s[i - 1], s[i + 1]);
		if (g < minn) {
			minn = g;
			ans = 1;
		}
		else if (g == minn) ans++;
	}
	if (init < minn && flag) minn = init, ans = 1;
	else if (init == minn && flag) minn = init, ans++;
	cout << minn << ' ' << ans << '\n';
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int T;
	cin >> T;
	while (T--) solve();
	
	return 0;
}
```

---

## 作者：I_am_kunzi (赞：11)

# CF1858B 题解

### 题目翻译

有 $ n $ 个长椅和 $ m $ 个曲奇售卖点和一个距离 $ d$。Petya 会按照以下三种规则吃曲奇：

1. 如果没有吃任何一块曲奇，那就从一个有无限曲奇的背包中拿出一块曲奇并立刻吃掉；

1. 在每一个曲奇售卖点，买一块曲奇并立刻吃掉；

1. 在连续走过 $ d $ 个长椅且在此途中没有吃过一块曲奇，那就从一个有无限曲奇的背包中拿出一块曲奇并立刻吃掉；

1. Petya 不会在任何一个长椅上吃多于一块曲奇。

现在你必须删除一个曲奇售卖点，输出 Petya 能吃到的最小曲奇数量和满足吃到最小曲奇数能删除的曲奇售卖点个数。

### 题目思路

先考虑如何求出不删除时吃掉的曲奇数。我们计算出两个曲奇售卖点之间的距离，但考虑到如果这个距离可以被 $ d $ 整除，那这个计算结果也会包括上在下一个曲奇售卖点吃的那一块曲奇，所以我们需要计算的是两个曲奇售卖点之间距离减 $ 1 $ 后除以 $ d $ 的结果，最后加上在每个曲奇售卖点吃掉的曲奇和在第一个长椅上吃掉的曲奇即可。公式为 $ \sum_{i = 1} ^ m \left \lfloor \frac {cookie_{i + 1} - cookie_i - 1} d \right \rfloor$。

继续来考虑删除一个卖点后的曲奇数。我们可以发现此时需要删去的是前一个曲奇售卖点到这个曲奇售卖点途中吃的曲奇、在这个曲奇售卖点吃掉的曲奇和这个曲奇售卖点到下一个曲奇售卖点途中吃的曲奇；取而代之的是上一个曲奇售卖点到这个曲奇售卖点之间吃掉的曲奇（不过因为每次都减去这个曲奇售卖点吃掉的曲奇过于麻烦，所以代码中将这一部分移动到了计算并输出答案处，具体可以查看代码注释）。我们在这两部分的差值中寻找一个最小的，也就是吃到最少曲奇的地方；用一个 ``` vector < int > possible_minn; ``` 记录下满足吃到最小曲奇数能删除的曲奇售卖点个数，当有更小的答案时就更新最小值、清空数组并将这种情况加入答案；如果和最小值一样就直接加入答案。最后统计出最小值加上不删除时吃掉的曲奇数再减 $ 1$（减 $ 1 $ 的缘故在前文已经申明）和数组大小即可。

### 题目代码

```cpp
#include<iostream>
#include<vector>
using namespace std;
signed main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int n , m , d;
		cin >> n >> m >> d;
		vector < int > cookie(m); 
		for(int i = 0 ; i < m ; i++)
		{
			cin >> cookie[i];
		}
		cookie.insert(cookie.begin() , 1 - d); // 为方便操作，插入一个不影响答案的位置
		cookie.push_back(n + 1); // 理由同上
		int minn = INT_MAX;
		vector < int > possible_minn; 
		for(int i = 1 ; i <= m ; i++)
		{
			int z1 = cookie[i] - cookie[i - 1] - 1; // 这一个曲奇售卖点到前一个曲奇售卖点的距离 - 1
			int z2 = cookie[i + 1] - cookie[i] - 1; // 下一个曲奇售卖点到这一个曲奇售卖点的距离 - 1
			int z3 = cookie[i + 1] - cookie[i - 1] - 1; // 下一个曲奇售卖点到前一个曲奇售卖点的距离 - 1
			int z4 = z3 / d - z1 / d - z2 / d; // 为方便操作，减去在第 i 个曲奇售卖点吃掉的曲奇一部分放到输出答案处
			if(z4 < minn) // 更优解，此时记录并清空
			{
				minn = z4;
				possible_minn.clear();
			}
			if(z4 == minn) // 若原来 z4 < minn，则现在 z4 == minn，故不影响答案
			{
				possible_minn.push_back(i);
			}
		}
		int ans = 0; // 计算不删除时吃掉的曲奇数
		for(int i = 1 ; i <= m + 1 ; i++)
		{
			ans += (cookie[i] - cookie[i - 1] - 1) / d; 
		}
		ans += m;
		cout << minn + ans - 1 << ' ' << possible_minn.size() << endl; // 最小值 + 不删除时吃掉的曲奇数 - 1 和数组大小
	}
    return 0;
}
```

---

## 作者：信息向阳花木 (赞：6)

观察可以发现，每移除一个卖饼的人，最多只会对答案产生 $-1$ 的贡献。

这就好做了。我们算出 Petya 本来吃饼的数量 $sum$，再枚举每一个卖饼的人的位置 $a_i$，考虑 $a_{i-1}$ 到 $a_{i+1}$ 之间 Petya 吃饼的数量，以及移除 $a_i$ 后 $a_{i-1}$ 到 $a_{i+1}$ 之间 Petya 吃饼的数量。如果有减少，方案数 $cnt$ 就增加。如果最后一个方案都没有，就说明无论怎么移动，吃饼的数量都不会减少，方案数为 $m$，吃饼数量为 $sum$。否则方案数为 $cnt$，吃饼数量为 $sum - 1$。

注意最后一个卖饼的人需要特判，因为位置 $n$ 不是必须吃饼。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 100010;

int t, n, m, d;
int a[N];

int main()
{
	scanf("%d", &t);
	while (t -- )
	{
		scanf("%d%d%d", &n, &m, &d);
		for (int i = 1; i <= m; i ++ ) scanf("%d", &a[i]);
		
		sort(a + 1, a + m + 1);
		
		int sum = 1, cnt = 0;
		a[0] = 1; a[m + 1] = n;
		for (int i = 1; i <= m; i ++ )
		{
			if(i < m)
			{
				int x = (a[i + 1] - a[i - 1] + d - 1) / d;
				int y = (a[i + 1] - a[i] + d - 1) / d + (a[i] - a[i - 1] + d - 1) / d;
				if(x < y) cnt ++;
			}
			sum += (a[i] - a[i - 1] + d - 1) / d;
		}
		sum += (n -a[m]) / d;
		int x = (n - a[m - 1]) / d;
		int y = (a[m] - a[m - 1] + d - 1) / d + (n - a[m]) / d;
		if(x < y) cnt ++;
		if(!cnt) printf("%d %d\n", sum, m);
		else printf("%d %d\n", sum - 1, cnt);
		
	}
	return 0;
}
```

---

## 作者：SamHJD (赞：3)

## [CF1858B The Walkway](https://www.luogu.com.cn/problem/CF1858B)

**题意**

在一条长度为 $n$ 街道上有 $m$ 个曲奇店，第 $i$ 个曲奇店的位置为 $s_i$，Petya 有很多个曲奇，他想从街道的头走到尾，他会在如下几种情况会吃一个曲奇。

* 如果当前还没有吃一个曲奇，他会吃一个。

* 如果当前经过了一个曲奇店，他会吃一个。

* 如果经过上次吃曲奇 $d$ 分钟，他会吃一个。

Petya 不能在同一个地方吃多个曲奇。

若关闭一家曲奇店，Petya 最少能吃多少曲奇？在吃曲奇最少的情况下，有多少种关闭的方案？

**暴力解法**

循环每一个曲奇店并关闭，按照题意模拟即可。

**正解**

还是先循环每一个曲奇店关闭，考虑对从头到尾模拟进行优化。

关闭了店 $i$ 后只有店 $i-1$ 到店 $i+1$ 这段路的吃曲奇数量可能发生改变。因此我们只需要对这段进行计算即可。

具体的，设 $cost_i$ 表示 $s_i \dots s_{i+1}-1$ 吃曲奇的数量，计算方式为：

$$cost_i=\left\lceil\dfrac{s_{i+1}-s_i}{d}\right\rceil$$

注意这里是向上取整，因为我们是在每一长度为 $d$ 的区间的头吃曲奇。这个计算方式也包括了再曲奇店吃一个曲奇的要求。令 $tot=\sum cost_i$，这便是不关曲奇店所需的曲奇数。

关闭店 $i$ 后，先将 $tot$ 减去 $s_{i-1}\dots s_{i},s_i\dots s_{i+1}$ 的吃曲奇数量，再加上 $s_{i-1}\dots s_{i+1}$ 这段的曲奇数即可。

为了方便，写一个 ```calc(x,y)``` 函数计算 $s_x\dots s_y-1$ 的吃曲奇数量。

对于第一个要求，也就是第一个位置必须吃一个曲奇，我们可以将第一个位置当作一个曲奇店，转化为要求 $2$，但是如果这里真的有曲奇店还得将其删去。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int T,n,m,d,s[N],cost[N]; 
int calc(int x,int y){
	int num=ceil(1.0*(s[y]-s[x])/d);
	return max(num,1);
}
int main(){
	scanf("%d",&T);
	while(T--){
		int ans=1e9,ans1=0,tot=0;;
		scanf("%d%d%d",&n,&m,&d);
		for(int i=1;i<=m;++i) scanf("%d",&s[i]);
		s[0]=1;s[m+1]=n+1;cost[0]=0;
		int fir=0;if(s[1]==1) fir=1;
        //如果1位置有曲奇店，不计算店0的cost
		for(int i=fir;i<=m;++i) cost[i]=calc(i,i+1),tot+=cost[i];
		for(int i=1;i<=m;++i) ans=min(ans,tot-cost[i-1]-cost[i]+calc(i-1,i+1));//第一个循环计算最小值
		for(int i=1;i<=m;++i) if(ans==tot-cost[i-1]-cost[i]+calc(i-1,i+1)) ans1++;//第二个循环计算方案数
		printf("%d %d\n",ans,ans1);
	}
	return 0;
}
```

---

## 作者：Wf_yjqd (赞：2)

这么简单一道题调了 $1$ 个小时，真掉大分辣。

------------

思路也很简单，考虑删除一个摊对他前面和后面区间的答案没有影响，于是考虑预处理一个前缀答案和后缀答案。

枚举删除的摊，贡献的答案为前面和后面答案的和加上前一个摊和后一个摊中间有多少个 $d$。

更新最小值和最小值个数即可。

细节很多，注意处理 $1$ 位置上必须吃的情况，还有求两点之间 $d$ 的个数的方法。

复杂度 $\operatorname{O}(n)$。

------------

真的好恶心这场 CF。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+84;
int T,n,m,d,b,p[maxn],qzans[maxn],hzans[maxn],ans,cnt;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d%d",&n,&m,&d,&p[1]);
        b=0;
        if(p[1]!=1){
            b=1;
            m++;
            p[2]=p[1];
            p[1]=1;
        }
        for(int i=(b?3:2);i<=m;i++)
            scanf("%d",&p[i]);
        qzans[1]=1;
        for(int i=2;i<=m;i++)
            qzans[i]=qzans[i-1]+(p[i]-p[i-1]-1)/d+1;
        hzans[m]=(n-p[m])/d+1;
        for(int i=m-1;i>=1;i--)
            hzans[i]=hzans[i+1]+(p[i+1]-p[i]-1)/d+1;
        ans=0x7f7f7f7f;
        p[m+1]=n+1;
        cnt=0;
        if(!b){
            ans=qzans[m]+(n+1-p[m]-1)/d;
            cnt=1;
        }
        hzans[m+1]=0;
        for(int i=2;i<=m;i++){
            if(qzans[i-1]+hzans[i+1]+(p[i+1]-p[i-1]-1)/d<ans){
                ans=qzans[i-1]+hzans[i+1]+(p[i+1]-p[i-1]-1)/d;
                cnt=1;
            }
            else if(qzans[i-1]+hzans[i+1]+(p[i+1]-p[i-1]-1)/d==ans)
                cnt++;
        }
        printf("%d %d\n",ans,cnt);
    }
    return 0;
}
```


---

## 作者：Dawn_cx (赞：1)

## 题意
有个哥们在数轴上从 $1$ 向 $n$ 走，数轴上有 $m$ 个卖饼干的，哥们在路上会吃饼干，你可以删除一个饼干贩子，问哥们最少吃几个饼干。

哥们吃饼干的规则如下：

- 在点 $1$ 吃一个饼干
- 在有饼干贩子的点吃一个
- 对于当前走到的点 $i$ ，如果 $i>d$ 并且上次吃饼干的位置是 $i-d$ ，吃一个（即隔 $d$ 个吃一个）

给你 $n$，$m$，$d$，以及 $m$ 个饼干贩子的位置，求这哥们最少吃的饼干数，以及有多少种情况可以让哥们吃的饼干数最少。

## 思路
记录一个前缀 $fr[i]$ 代表在点 $i$ 之前要吃多少块饼干，记录一个后缀 $bk[i]$ 代表在点 $i$ 之后要吃多少块饼干，则对于删除每一个点 $i$ ，其答案贡献为 $now=fr[i-1]+bk[i+1]+s(loc[i-1]+1,loc[i+1]-1)$。

其中 $s(l,r)$ 代表 $l$ 到 $r$ 区间要没有饼干贩子要吃多少块饼干， $loc[i]$ 代表第 $i$ 个饼干贩子的位置。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
const int mod = 998244353;
inline void read(int &x){
	int s=0,w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=(s<<3)+(s<<1)+(ch&15);ch=getchar();}
	x=s*w;
}
int T,n,m,d,fr[maxn],bk[maxn],loc[maxn];
inline int s(int r, int k){//1-r mod d =k number
	k%=d;
	if(r<k)return 0;
	return (r-k)/d+1;
}
int main(){
	read(T);
	while(T--){
		read(n),read(m),read(d);
		for(int i=0;i<=m+1;i++)fr[i]=bk[i]=0;
		for(int i=1;i<=m;i++)read(loc[i]);

		fr[1]=s(loc[1]-1,1)+1;
		for(int i=2;i<=m;i++)fr[i]=fr[i-1]+s(loc[i]-1,loc[i-1]%d)-s(loc[i-1],loc[i-1]%d)+1;

		bk[m]=s(n,loc[m]%d)-s(loc[m]-1,loc[m]%d);
		for(int i=m-1;i;i--)bk[i]=bk[i+1]-s(loc[i]-1,loc[i]%d)+s(loc[i+1]-1,loc[i]%d);

		int ans=fr[m-1]+s(n,loc[m-1]%d)-s(loc[m-1],loc[m-1]%d),num=1,now;
		for(int i=m-1;i>1;i--){
			now=fr[i-1]+bk[i+1];
			now+=s(loc[i+1]-1,loc[i-1]%d)-s(loc[i-1],loc[i-1]%d);
			if(now<ans)ans=now,num=1;
			else if(now==ans)num++;
		}
		now=bk[2]+s(loc[2]-1,1);
		if(now<ans)ans=now,num=1;
		else if(now==ans)num++;
		printf("%d %d\n",ans,num);
	}
}
/*
1
8 3 2
3 5 8
*/
```


---

## 作者：仁和_童博扬 (赞：0)

# CF1858B The Walkway

## 题意
有一条长度为 $ n $ 的步行街，上面有 $ m $ 个饼干摊位，符合以下任意条件时吃一次饼干：

- 这个位置有饼干摊位
- 还没吃过饼干（即，如果位置 $ 1 $ 上没有饼干摊位，那么在位置 $ 1 $ 上吃一次饼干）
- 距离上次吃饼干已经过去了 $ d $ 的距离

给定 $ m $ 个饼干摊位的位置 $ s_i $，你最多可以去掉其中一个摊位，求最少吃几次饼干，以及有几种去掉摊位的方法可以达到这个最少吃饼干次数。

## 分析

由题意可知，去掉一个摊位最多可以少吃一次饼干。因为两段区间各自剩下的不足 $ d $ 的距离加起来也不可能达到 $ 2 \times d $。

如果不去掉第 $ i $ 个摊位，那么第 $ i - 1 $ 个摊位到第 $ i $ 个摊位之间会吃 $ \frac{s_i - s_{i-1} - 1}{d} $ 次饼干，在第 $ i $ 个摊位上会吃第 $ 1 $ 次饼干，第 $ i $ 个摊位到第 $ i + 1 $ 个摊位之间会吃 $ \frac{s_{i+1} - s_i - 1}{d} $ 次饼干；

如果去掉第 $ i $ 个摊位，那么那么第 $ i - 1 $ 个摊位到第 $ i + 1 $ 个摊位之间会吃 $ \frac{s_{i+1} - s_{i-1} - 1}{d} $ 次饼干。

于是，我们得出删除该摊位是否可以减少一次吃饼干次数的基本判定条件：
 $$ \frac{s_{i+1} - s_{i-1} - 1}{d} < \frac{s_i - s_{i-1} - 1}{d} + 1 + \frac{s_{i+1} - s_i - 1}{d} $$ 

每次这个条件成立就计数一次，统计有几种去掉摊位的方法。

接下来考虑边界情况和特殊情况。

由于最后一个摊位后一直到步行街结束，都会继续吃饼干，所以我们可以将 $ s_{m+1} $ 设置为 $ n + 1 $。

如果位置 $ 1 $ 上没有饼干摊位，那么在位置 $ 1 $ 上吃一次饼干。所以我们可以将 $ s_0 $ 设置为 $ 1 $，将答案的初始值设置为 $ 1 $。但需要注意，如果位置 $ 1 $ 上有饼干摊位，则我们需要将 $ s_0 $ 设置为 $ 0 $，将答案的初始值设置为 $ 0 $。

最后，需要注意可能去掉任何一个摊位都不能减少一次吃饼干次数，所以需要进行特判。

时间复杂度为 $ O(m) $，可以通过本题。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
const int M = 1e5 + 5;
long long d, n, m;
long long s[M];
int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		scanf("%lld%lld%lld",&n,&m,&d);
		for(int i = 1; i <= m; i++)
			scanf("%lld",&s[i]);
		long long ans = 1, ansi = 0;
		s[0] = 1;
		if(s[1] == 1)	ans = 0, s[0] = 0;
		s[m+1] = n + 1;
		for(int i = 1; i <= m; i++)
		{
			ans += (s[i]-s[i-1]-1) / d + 1;
			if((s[i+1]-s[i-1]-1)/d<(s[i]-s[i-1]-1)/d+(s[i+1]-s[i]-1)/d+1)
			{
				if(i == 1 && s[1] == 1)	continue;
				ansi++;
			}
		}
		ans += (n - s[m]) / d;
		if(ansi)	ans--;//去掉其中某个摊位可以使得答案-1，且ansi就是方案数 
		else	ansi = m;//去掉任何一个摊位都不能让答案-1，因此去掉每个摊位都是最佳方案，方案数为m 
		printf("%lld %lld\n",ans,ansi);
	}
	return 0;
}
```

---

## 作者：Drind (赞：0)

这题题面很复杂，简要概述一下就是一条路有 $n$ 个点，其中有 $m$ 个点上有卖饼干，一个人从 1 号点走到 $n$ 号点，对于每个点，如果从开始到现在他还没吃过饼干，或者已经走了 $d$ 个点他还没吃饼干，或者这个点在卖饼干，他都会吃一个饼干。问如果你能正好删去一个卖饼干的地方，这个人最少吃多少饼干，并求出方案数。

我们考虑初始化每两个卖饼干的摊之间的距离，那么从这个摊走到下一个摊就需要吃 $\left\lfloor\frac{len}{d}\right\rfloor$ 个饼干。接下来枚举删掉哪个摊即可。

这题实现上细节很多，详情见注释吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=2e6+10;

long long len[N],a[N];
void fake_main(){
	long long n,m,d,ans=0,mx=1e15,flag=0,cnt=0; cin>>n>>m>>d;
	cin>>a[1]; if(a[1]==1){//首先，在第一个点是必须要吃饼干的，所以如果第一个点不卖饼干，我们就强制他卖饼干
		for(long long i=2;i<=m;i++) cin>>a[i];
	}else{
		a[2]=a[1]; a[1]=1;
		for(long long i=3;i<=m+1;i++) cin>>a[i];
		m++; flag=1;
	}
	a[m+1]=n+1;//再加上一个点n+1方便统计距离
	for(long long i=1;i<=m;i++){
		len[i]=a[i+1]-a[i]-1;
		ans+=len[i]/d;
	}
	ans+=m;//ans是不删摊情况下需要吃的饼干数
	for(long long i=2;i<=m;i++){
		long long tot=ans;
		tot--;//减去删掉摊吃的1个饼干
		tot-=len[i]/d;
		tot-=len[i-1]/d;//减去左右两个区间吃的饼干
		tot+=(len[i]+len[i-1]+1)/d;//加上合并后一个区间吃的饼干
		if(tot==mx) cnt++;//统计次数
		if(tot<mx){
			cnt=1;
			mx=tot;
		}
	}
	if(flag==0&&ans==mx) cnt++;//考虑如果第一个点卖饼干且删除第一个点的情况
	if(m==1){//考场上wa on #2写的特判，实际上不需要，因为m>=2
		cout<<(n-1)/d+1<<" "<<1<<endl;
	}
	else cout<<mx<<" "<<cnt<<endl;
}

signed main(){
	long long t;
	cin>>t;
	while(t--) fake_main();
}

```

---

