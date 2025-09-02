# Do You Love Your Hero and His Two-Hit Multi-Target Attacks?

## 题目描述

Akito 决定学习一个强大的新咒语。由于这个咒语拥有无可估量的力量，它必然需要大量空间和精心准备。为此，Akito 来到了一片空地。我们将这片空地表示为一个笛卡尔坐标系。

为了施展咒语，Akito 需要在空地的不同整数坐标处放置 $0 \le n \le 500$ 根法杖，使得恰好存在 $k$ 对 $(i, j)$ 满足 $1 \le i < j \le n$ 且 $\rho(i, j) = d(i, j)$。

这里，对于两个整数坐标点 $a = (x_a, y_a)$ 和 $b = (x_b, y_b)$，定义 $\rho(a, b) = \sqrt{(x_a - x_b)^2 + (y_a - y_b)^2}$ 且 $d(a, b) = |x_a - x_b| + |y_a - y_b|$。

## 样例 #1

### 输入

```
3
0
2
5```

### 输出

```
6
69 52
4 20
789 9308706
1337 1337
-1234 -5678
23456178 707
10
-236 -346262358
273568 6435267
2365437 31441367
246574 -45642372
-236 56
4743623 -192892 
10408080 -8173135
-237415357 31441367
-78125638 278
56 143231
5
1 1
2 1
1 5
3 5
1 10```

# 题解

## 作者：gesong (赞：13)

题目传送门：[CF2072E](https://www.luogu.com.cn/problem/CF2072E)。
# 思路
首先 $p(a,b)=d(a,b)$ 当且仅当 $x_a=x_b$ 或 $y_a=y_b$。

我们发现如果一个行有 $x$ 个点，那么就有 $\frac{x(x-1)}{2}$ 个满足题目要求配对。

我们按照上述性质按行构造，我们定义 $a_i=\frac{i(i-1)}{2}$ 那么我们对于题目要求的 $k$ 从倒序枚举 $a_i$，我们根据贪心思想如果可以就开一行 $i$ 个点。

根据暴力可得，我们可以在 $500$ 个点之内完成这个构造。

记得在每一行不要构造出相同列的节点，具体的可以查看代码。
# 代码
```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
int n=500;
int a[1000];
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
#define pii pair<int,int>
vector<pii>anss;
int cnt1=-1e9;
inline void print(int x,int y){
	for (int i=1;i<=y;i++) anss.push_back({x,cnt1++});
}
inline void solve(){
	cnt1=-1e9;
	int k=read();anss.clear();
	int cnt=0; 
	for (int i=n;i>=2;i--)
		while(k>=a[i]) print(++cnt,i),k-=a[i];
	printf("%lld\n",anss.size());
	for (auto i:anss) printf("%lld %lld\n",i.first,i.second);
}
main(){
	for (int i=2;i<=n;i++)  a[i]=i*(i-1)/2;
	int T=read();
	while(T--) solve();
    return 0;
}
//Codeforces Round 1006 RP++
//Codeforces Round 1006 RP++
//Codeforces Round 1006 RP++
//Codeforces Round 1006 RP++
//Codeforces Round 1006 RP++
```

---

## 作者：wmrqwq (赞：3)

这是一篇视频题解。

![](bilibili:BV1fHP3ewES9?t=2)

[代码链接](https://codeforces.com/contest/2072/submission/307825569)

---

## 作者：_O_v_O_ (赞：1)

把条件转化为在同一行或者同一列。那么我们不妨让所有点自成一列，然后就只需要决定横坐标即可。

我们注意到对于 $k$ 个点在同一行，贡献为 $\frac{n\times (n-1)}2$，那么我们枚举每一次的最大的可以选的 $k$ 即可，只有 $\sqrt n$ 个。

code：<https://codeforces.com/contest/2072/submission/309463264>

---

## 作者：QWVnbGVzZWVrZXI3D (赞：1)

既然曼哈顿距离 $=$ 欧几里得距离，那么他们必须在同一行或列中。方便起见，我们仅仅考虑同一行的情况。

设一行中有 $x$ 个点，那么其产生的贡献为
$a_x=\dfrac{(x-1)(x)}{2}$。

考虑贪心，每次选择不大于 $k$ 的 $a_x$，令 $k-a_x$，直到 $k=0$。
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 600;
int tn[N], ans[N];

void init()
{
    for (int i = 2; i < N; i++)
        tn[i] = tn[i - 1] + i - 1;
}

void solve()
{
    int k, len = 0, tot = 0;
    cin >> k;
    while (k)
    {
        int pos = lower_bound(tn + 1, tn + N, k) - tn;
        if (tn[pos] != k) pos--;
        ans[++len] = pos;
        tot += pos;
        k -= tn[pos];
    }
    int x = 0, y = 0;
    cout << tot << "\n";
    for (int i = 1; i <= len; i++)
    {
        for (int j = 1; j <= ans[i]; j++)
            cout << x << " " << y++ << "\n";
        x++;
    }
}

int main()
{
    init();
    int T;
    cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}
```

---

## 作者：cwxcplh (赞：1)

很水的一道题，~~那我就水一点的讲吧。~~

题目简化：你可以最多放 $500$ 根法杖，要求这些法杖中任意两根满足 $|x_a-x_b|+|y_a-y_b|=\sqrt{(x_a-x_b)^2+(y_a-y_b)^2}$ 的数量为 $k$，求这些法杖的坐标。

其实不难发现：上面的那个公式就是要两个点坐标的直线距离等于横纵坐标之差的和，相当于一个直角三角形要求两直角边的和等于斜边长度。那因为三角形中任意两边长之和一定大于第三边，所以这肯定不是一个三角形，只能是一条平行于 $x$ 轴或 $y$ 轴的直线。

那我们就有一种偷懒的想法：

![](https://cdn.luogu.com.cn/upload/image_hosting/pa31oq4d.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

这样每次就只会增加一条边，更好控制。

但题目也不是吃素的，题中给了 $n\le500$，而 $k\le10^5$，所以这个方法明显不行。

但我们可以在上面的方法基础上改良一下：我们只需要把一些点放在同一行，那么就会少很多的点，那我们每在一行上多放一个点，就会多多少个满足条件的答案呢？很明显，就是当前这一行上的点的数量，到这，这道题就被我们完美解决了。

AC 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,cnt,n,tt;
signed main()
{
    cin>>t;
    while(t--)
    {
        cin>>n;
        vector<pair<int,int>>v;
        tt=cnt=0;
        for(int i=-1e9,j=-1e9;cnt<n;j++)
        {
            if(cnt+tt<=n)//防止加上这个点后比预计的数量多了
            {
                v.push_back(make_pair(i,j));
                cnt+=tt;
                tt++;
            }
            else//多了就新开一行来算
            {
                i++;
                v.push_back(make_pair(i,j));
                tt=1;
            }
        }
        cout<<v.size()<<endl;
        for(auto i:v)
        {
            cout<<i.first<<" "<<i.second<<endl;
        }
    }
    return 0;
}
```

---

## 作者：tzzl3035 (赞：1)

### CF2072E

#### 大致思路

把题目翻译成人话，搞不多于 $500$ 个法杖，使得正好有 $k$ 对法杖在同一行或者同一列，没有不同的两个法杖在同一个地方。这样看就简单了，每一个法杖都自成一列，然后通过判断哪几个法杖在同一行就能解决了。这样肯定是在满足条件下在同一行放更多个更优。

#### 代码详解

```cpp
#include <bits/stdc++.h>

int main() {
  int t; std::cin >> t;
  for(; t; --t) {
    int k; std::cin >> k; // 输入
    std::vector<std::pair<int, int>> ans;
    int j = -1000, cnt = 0, sum = 0;
// 分别是当前的行，当前这一行有几个法杖，目前有几对满足条件
    for(int i = -1000; sum < k; ++i) { // 枚举列
      if(sum + cnt <= k) { // 当前行加一个会不会超额
        ans.push_back({i, j});
        sum += cnt, ++cnt; // 当前行多一个，多 cnt 对
      }
      else {
        ++j; ans.push_back({i, j});
        cnt = 1; // 重新开一行算
      }
    }
// 输出
    std::cout << ans.size() << '\n';
    for(auto &[u, v]: ans) 
      std::cout << u << ' ' << v << '\n';
  }
}
```

#### [RESULT](https://codeforces.com/contest/2072/submission/309298847)

---

