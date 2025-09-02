# [USACO16FEB] Circular Barn G

## 题目背景

*本题与 [银组同名题目](/problem/P3137) 在题意上一致，唯一的差别是数据范围。*

## 题目描述

作为当代建筑的爱好者，Farmer John 建造了一个圆形新谷仓，谷仓内部 $n$ 个房间排成环形（$3 \leq n \leq 10^5$），按顺时针顺序编号为 $1\ldots n$，每个房间都有通往与其相邻的左右房间的门，还有一扇门通往外面。

现在 FJ 有 $n$ 头奶牛，他的目标是让每个房间恰好有一头奶牛。然而不幸的是，现在奶牛们随意呆在某个房间里，第 $i$ 个房间里有 $c_i$ 头奶牛。保证 $\sum c_i =n$。

FJ 决定采用这样的方法来解决这个问题：让某些奶牛**顺时针**穿过某些房间到达指定的位置。如果一头奶牛穿过了 $d$ 扇门，他消耗的能量为 $d^2$。你需要帮 FJ 算出所有奶牛消耗的能量和最小值是多少。

## 样例 #1

### 输入

```
10
1
0
0
2
0
0
1
2
2
2```

### 输出

```
33```

# 题解

## 作者：Zelotz (赞：14)

[题目链接](https://www.luogu.com.cn/problem/P3137)

本蒟蒻的第一篇题解，写得不好请指出，蟹蟹。

### 题意：
有 $n$ 头奶牛，分布在一些房间，某些房间可能有多头牛，要让这些牛按顺时针移动，求使每一个房间刚好有一个奶牛的最小花费。

花费计算：如果一头奶牛穿过了 $d$ 扇门，他消耗的能量为 $d^2$。

### 分析：
先把这个环看成一条链

首先说一个东西：如果有 $1$ 头奶牛在 $a$ 点，$1$头奶牛在 $b$ 点，还有一个没有奶牛的 $c$ 点，且 $c>b>a$，要想有一头奶牛在 $b$ 点，一头奶牛在 $c$ 点，方案 $a \to b,b \to c$ 比方案 $a \to c$ 好。

很容易知道这是对的，可以设 $x=b-a,y=c-b$，而 $c-a=y+x$，所以 $(x+y)^2=x^2+y^2+2xy>x^2+y^2$。

也就是说在如果一个房间的奶牛的移动算一个移动过程，移动过程中一头奶牛不要越过另一头没有移动的奶牛。

所以可以直接从一个起点开始，如果这个房间里有超过$1$头奶牛，就把这些奶牛移到依次后面每一个的房间的末尾，直到没有多余的奶牛可以移动为止。

留下房间里最后一头奶牛，也就是上一次最后一头牛，每一个房间都这么处理。

为了好写代码，可以留下最后一头牛，把这个房间里多余的奶牛移动到下一个房间，下一个房间再做处理。

问题是起点如何选择。

当一个起点是合法时，$\sum\limits_{i=1}^{n}c_{i} \geqslant i$。

不知道就枚举呗，反正 $n$ 不超过 $1000$。

窝语文不好，只能描述成这样惹。

### 代码：
为每一个奶牛编号，为 $1 \sim n$。

用 $d_i$ 来表示编号为 $i$ 的奶牛走过的距离。

用 $\texttt{vector}$ 来存每一个房间里的奶牛。

$\texttt{push\_back}$ 把元素 $\texttt{push}$ 到末尾，所以留下最后一个，其他的往下一个房间移动。

然后注意下一个房间 $\bmod n$ 就行了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
#define reg register int
#define msz(a) memset(a, 0, sizeof a);
#define rep1(i, j, n) for (reg i = j; i <= n; ++i)
#define rep2(i, j, n) for (reg i = j; i >= n; --i)
typedef long long LL;
typedef pair <int, int> PII;
const int INF1 = 0x3f3f3f3f, INF2 = 0x7fffffff;
int n, d[1005], ans, nowid, result = INF2;
vector <int> a[1005], b[1005];
bool vis[1005];
int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        for (int j = 1; j <= x; ++j) a[i].push_back(++nowid), b[i].push_back(nowid); //编号
    }
    for (int start = 1; start <= n; ++start) {
    	// 枚举起点进行模拟
        for (int now = start; ; ++now) {
            if (now > n) now %= n;
            if (now == start && flg == 0) break;
            if (a[now].empty()) continue;
            flg = 0;
            int sz = a[now].size();
            int p = now + 1;
            if (p > n) p %= n;
            for (int i = 0; i < sz - 1; ++i) {
                a[p].push_back(a[now][i]);
                d[a[now][i]]++;
            }
            int endnum = a[now][sz - 1];
            a[now].clear();
            a[now].push_back(endnum);
        }
        for (int i = 1; i <= n; ++i) {
            if (a[i].size() != 1) { ans = -1; break; } //是否合法
            ans += d[i] * d[i]; //计算
        }
        if (ans ^ -1) result = min(result, ans);
        msz(d); msz(vis); ans = 0;
        for (int i = 1; i <= n; ++i) a[i].clear();
        for (int i = 1; i <= n; ++i)
            for (int j = 0; j < (int)b[i].size(); ++j)
                a[i].push_back(b[i][j]); //还原
    }
    printf("%d", result);
    return 0;
}
```

 $n^2$ 算法可以通过 $1000$ 的数据，那么 $100000$ 的数据怎么办呢。

可以发现枚举 $start$ 会出现许多没用的枚举，那哪个一个 $start$ 可以确保不会出现非法情况呢。

可以大概猜出是最密集的那个地方的开头吧。

就是说最大字段和。

因为全部奶牛的和为 $n$，所以所有 $c_i$ 的和一定是最大子段和
所以要把每一个 $c_i$ 与 $1$ 做差，可以清晰看出最大的字段，再求出最大子段和的起点。

证明也很简单：

设最大子段和的值为 $x$，如果最大子段和不合法，那么在最大子段和之后必然有一个字段的值 $\leqslant -x-1$，由于所有数的和为 $0$，那么在这个字段之后，剩下的那个字段和 $\geqslant 1$。

所以最大子段和的值不为 $x$，矛盾。

这个证明有点。。充分显示出我的菜。

然后就是环状最大子段和惹。

环状最大子段和好像可以用单调队列，但是我用了另一种方法。

分两种情况讨论：

$1$.这个字段没有包含 $c_1$和 $c_n$，那么就是本来的最大子段和。

$2$.字段包含了 $c_1$和 $c_n$，那就是整个和减去全部的最小字段和。

最小字段和可以把所有元素取反，求最大子段和。

把两种情况取最大值即为答。

这样可以通过加强版的数据了。

### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long //不开longlong见祖宗
#define mp make_pair
#define reg register int
#define msz(a) memset(a, 0, sizeof a);
#define rep1(i, j, n) for (reg i = j; i <= n; ++i)
#define rep2(i, j, n) for (reg i = j; i >= n; --i)
typedef long long LL;
typedef pair <int, int> PII;
const int INF1 = 0x3f3f3f3f, INF2 = 0x7fffffff;
const int N = 1e5 + 5;
int n, d[N], ans, nowid, result = INF2, maxn, start, f[N], b[N];
vector <int> a[N];
bool vis[N];
signed main() {
    // freopen("P6170_7.in", "r", stdin);
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%lld", &x);
        b[i] = x - 1;
        for (int j = 1; j <= x; ++j) a[i].push_back(++nowid);
    }
    bool flg = 1;
    int m1 = 0, m2 = 0, sum = 0, bg1, st1, st2;
    for (int i = 1; i <= n; ++i) {
        if (f[i - 1] > 0) f[i] = f[i - 1] + b[i];
        else f[i] = b[i], bg1 = i;
        if (f[i] > m1) m1 = f[i], st1 = bg1;
        sum += b[i];
        b[i] = -b[i];
    }
    for (int i = 1; i <= n; ++i) {
        if (f[i - 1] > 0) f[i] = f[i - 1] + b[i];
        else f[i] = b[i];
        if (f[i] > m2) m2 = f[i], st2 = i + 1;
    }
    m2 = sum + m2;
    if (m1 > m2) start = st1;
    else start = st2;
    // 分类讨论最大子段和
    for (int now = start; ; ++now) {
        if (now > n) now %= n;
        if (now == start && flg == 0) break;
        if (a[now].empty()) continue;
        flg = 0;
        int sz = a[now].size();
        int p = now + 1;
        if (p > n) p %= n;
        for (int i = 0; i < sz - 1; ++i) {
            a[p].push_back(a[now][i]);
            d[a[now][i]]++;
        }
        int endnum = a[now][sz - 1];
        a[now].clear();
        a[now].push_back(endnum);
    }
    for (int i = 1; i <= n; ++i) 
        ans += d[i] * d[i];
    printf("%lld", ans);
    return 0;
}
```

这个方法有点麻烦，比其他大佬的方法菜，不过我也是因为看不懂才来写的。

---

## 作者：Saliеri (赞：12)

写一篇稍微清楚点的，自己看的时候蒙了半天……

___

有一个显然的贪心方式：

- 每一个位置都由逆时针方向最近的有牛的位置填充。

证明：若微扰这个方案——用次近的位置填充，因为 $\forall x,y\in N^*,(x+y)^2>x^2+y^2$，所以必然导致答案增加。

这个贪心可以使用队列来实现。（用最前面的空闲的牛填这个牛棚，将这个位置上的牛留给后面的牛棚减少代价）。

现在问题变成了以哪个位置作为起点开始填充。

朴素的做法是枚举每一个位置作为起点,然后断环为链。这个 $O(n^2)$ 的屑做法只能通过 Silver 的数据。

首先断环为链，复制一份原数组在末尾，则每个方案可以表示为 i~i+n-1 这个区间的方案。

考虑删除一些无用的方案。

手画几个样例会发现，有很大一部分情况会因为前面的牛不够多而宣告不合法，我们可以由这个性质尝试跳过一部分起点。
___
设$b_i = c_i-1$,$c_i$ 表示在第i个牛棚中牛的头数。则 这个方案合法等价于**任意 b 的前缀和非负**。

**结论1** ： 若现在以 i 为起始点，走到 j 时宣告不合法，**则 i,j 之间的起点一定也不合法**。

证明：因为 i~j-1 中任意前缀和大于 0，移除前面一部分和非负的前缀后 ，后面的前缀和不会变大，必然也会在 j 或 j 之前宣告不合法。
___
**结论2** ：只要找到方案，必然是最优方案。

~~看起来好像很玄学。~~

证明：若我们已经找到了一个合法方案 st~st+n-1，整个合法方案的总前缀和必然为0，而后面的方案的生成方式是**剪切一段前缀，复制在末尾**。

只有剪切一段前缀和为 0 的前缀才可以使生成的方案合法，因为若剪切了前缀和为正的的，必定使新方案中 st+n-1 这个位置的前缀和小于0。

然而每一段前缀为0的前缀的剪切不会对答案有影响——因为前缀和为0，**内部的贡献是独立于外的**。

所以所有的合法方案答案必然相同。找到方案就是最优方案，输出即可。

___

时间复杂度 $O(n)$,每一个位置最多访问一次。

代码：

```cpp
#include <queue>
#include <cstdio>
const int maxn = 1e5+5;
int n,c[maxn<<1];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",&c[i]),c[i+n] = c[i];
	for(int i=1;i<=n;++i){
		long long nowans=0;
		std :: queue <int> q;
		for(int j=i;j<i+n;++j){
			while(c[j])--c[j],q.push(j);
			if(!c[j]){
				if(q.empty()){
					nowans = -1;
					break;
				}
				int pos = q.front();
				q.pop();
				nowans = nowans + (long long)(j-pos)*(j-pos);
			}
		}
		if(nowans != -1)return printf("%lld",nowans),0;
	}
	return 0;
}
```


---

## 作者：Kreado (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/P3137)

一道很好的数论题。

### 题意：
有 $n$ 头奶牛，分布在一些房间，某些房间可能有多头牛，要让这些牛按顺时针移动，使每一个房间恰好有一个奶牛的最小花费。

花费计算：如果一头奶牛穿过了 $d$ 扇门，他消耗的能量为 $d^2$ 。

### 思路:
对于这道题，我可以直说，用**暴力**就行了，~~根本不需要其他的技巧~~。

首先说一个东西：如果有 $1$ 头奶牛在 $a$ 点，$1$ 头奶牛在 $b$ 点，还有一个没有奶牛的 $c$ 点，且 $c>b>a$，要想有一头奶牛在 $b$ 点，一头奶牛在 $c$ 点，方案 $a \to b,b \to c$ 比方案 $a \to c$ 好。

因为 $\sum c_i = n$，且要使得 $\forall c_i = 1$，每头奶牛走的步数最少，所以可以直接从第 $1$ 个房间开始遍历，如果 $c_i > 1$ ，就把这个房间的 $ (c_i-1)$ 头奶牛移到后面的一个房间，留在这个房间里的奶牛一定是步数走的最多的，所以不用判断每头奶牛的新旧，以此类推，直到满足 $\forall c_i =1$，循环结束。

比如说:

样例数据 : `10 1 0 0 2 0 0 1 2 2 2`.

明显最优的方案是：
$4\to5,4\to6,1\to4,10\to3,10\to2,9\to1,9\to10,8\to9$ 。

如果一个一个走的话，时间复杂度是 $O(n^2)$，不会爆。

但是如果全部走的话，时间复杂度是 $O(n)$，刚好。

## 贴贴代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
struct node{ll N,S,W;}a[101000];
// N 当前房间的下一个房间
// S 当前房间还有多少头牛
// W 当前房间还有多少头牛
ll n,ans,p=1;
int main(){
	cin>>n;
	for(ll i=1;i<=n;i++) cin>>a[i].S;
	for(ll i=1;i<=n;i++)
		a[i].N=i+1;
	a[n].N=1;
    // 记录当前房间的下一个房间的编号
	for(ll i=1;i<=2*n;i++){
		if(a[p].S>1){
			a[a[p].N].S+=a[p].S-1;
			a[a[p].N].W+=a[p].S-1;
			a[p].S=1;
		}
		p=a[p].N;
	}
	for(ll i=1;i<=n;i++) ans+=(a[i].W*a[i].W);
	printf("%lld",ans);
	return 0;
}
```
时间复杂度还挺低 , $O(n)$。

~~这样你就能一下 A 两道题啦~~

---

## 作者：woshiren (赞：6)

update:修改了证明中不准确的部分，重新修改代码使之更加高效可读。

首先确认一点，奶牛行走的路径中不能有其他奶牛的终点，否则一定不是最优，可以从$\forall x,y \in N^*\quad x^2+y^2<(x+y)^2$ 来理解。

很容易想到一种暴力的方法，把环处理成链，枚举起始点，遇到牛就存入队列之中，遇到空位即就把队头的牛放进去，这样就能保证不会出现交叉，一旦发现奶牛数不足以填补空位，意味着必然出现交叉，此时这个起点就可以舍弃了。
这种做法的时间复杂度是$O(n^2)$的。

暴力的做法可以过简化版的题目，但是却不能过本题，那么应该怎么做呢？
猜想这样一种性质：当$i$和$j$之间在j处第一次出现奶牛数不足以填补空位时，$i$和$j$及其之间的点均不能作为起点。

证明如下：
假设$i$和$j$之间在$j$处第一次出现奶牛数不足以填补空位，也就是前缀和为负数（前缀和为$sum[i]=sum[i-1]+(a[i]-1)$，可以思考一下为什么要减一），位置多于总和，然后可以发现每次$i$前移一位，$j$不变的情况下，奶牛数$-a[i]$，位置数$-1$。

考虑两种情况，一种$a[i]>=1$，此时显然仍然是不可取的。

一种$a[i]=0$,此时总和不变，位置$-1$。在这个情况下$a[i]=0$，其实在$j=i$时已经出现了负数，所以仍然是不可取的。

综上所述，当$i$到$j$的前缀和出现在$j$处第一次出现负数时，$i$和$i,j$之间的位置均不能作为起点。

根据这个性质就可以剪掉大部分不需要的枚举了，具体使用在代码中有体现。

```
#include <cstdio>
#include <queue>
using namespace std;
int n, c[200005];
long long nowans;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &c[i]);
    for (int i = 1; i <= n; i++)
        c[i + n] = c[i];
    for (int i = 1; i <= n; i++)
    {
        nowans = 0;
        queue<int> que;
        for (int j = i; j < i + n; j++)
        {
            while (c[j] > 0)
            {
                que.push(j);
                c[j]--;
            }
            //这里是优化，不需要恢复c[j]的值
            //如果当前枚举的情况为最优解，恢复c[j]没有意义，因为后面的不会再优于当前情况
            //如果当前枚举的情况不是最优解，那么i和j及其之间都不可能是合法起点，c[j]的值也没有意义。
            if (c[j] == 0)
            {
                if (que.empty())
                {
                    nowans = -1;
                    i = j; 
                    //优化，直接跳过去
                    break;
                }
                int now = que.front();
                que.pop();
                nowans += (j - now) * (j - now);
            }
        }
        if (nowans != -1)
        {
            printf("%lld", nowans);
            return 0;
        }
    }
    return 0;
}
```

---

## 作者：llooser (赞：3)

```
1.这是个环，可以把环打开，变成一个序列。
2.无论是哪一种方案，在环里设定一个起点，这样就可以也变成一个序列。
3.把序列的前头移到末尾还是原来的环。
``` 

```
1.令包含零并且左右边界都是零的区间为A，把A右边的全部移到左边去，得到一个可行的方案。
2.那么，把前头的移到末尾可以生成新的方案，易得只要移的房间的奶牛数量不是1，新方案就不成立。
3.易得移动的房间的奶牛数是1对答案不影响。
4.综上，只要找到方案并采取最优的移动方法就是最优方案。
```
```
最优的移动方法。
1.u号房间距离m号房间x个单位，m号房间距离v号房间y个单位，u号房间奶牛数为2，m号房间奶牛数为1，v号房间奶牛数为0，最优移动方案是从m号房间移动1只奶牛到v号房间，从u号房间移动1只奶牛到m号房间。
2.上述情况要移动1只奶牛，上述方案消耗的能量为x^2+y^2，直接从u号房间移动到v号房间消耗的能量为(x+y)^2，因为x,y都是整数，易得x^2+y^2<(x+y)^2
3.易得最优移法是每次都移距离空房间最近的房间的奶牛来填补。
```

### 切记，有时不开long long见祖宗。~~（233）~~
```cpp
#include <algorithm>
#include <cstdio>
#include <queue>

using namespace std;

const int maxn = 1e5+7;

int n, c[maxn<<1];
int l, r, a[maxn];
long long ans;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &c[i]);
        c[i+n] = c[i];
    }

    for (int i = 1, t; i <= n; i++) {
        ans = 0; l = 1; r = 0;
        t = i;
        for (int j = i; j < i+n; j++, t = j) {
            for (int k = 1; k <= c[j]; k++) a[++r] = j;
            c[j] = 0;
            if (l > r) {
                ans = -1;
                break;
            } else {
                ans += (a[l]-j)*(a[l]-j);
                l++;
            }
        }
        if (ans > -1) break;
        i = t;
    }
    printf("%lld", ans);

    return 0;
}
```

---

## 作者：2020ywj (赞：2)

这是蒟蒻的第四篇题解，请神犇勿喷本题解。

考虑一下每一个奶牛按下标排序，那么最终的位置必然是连续的一串数，~~%10意义下~~

那么只需要确定好最终的位置，统计就可以了。

显然初始位置和排序数组中的下标之差最大的，最终位置就是当前位置，~~不需要移动~~

其余的按照这种排列移动即可。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long a[100001],n,x,b[100001],c[100001],maxx=-0x3f3f3f3f,p,cnt,ans;
int main()
{
    scanf("%d",&n);
    for(register int i=0i<=n;i++)//有误！防抄袭
    {
        scanf("%d",&x);
        while(x)
        {
            a[cnt++]=i;
            x--;
        }
    }
    for(register int i=0;i<n;i++) b[i]=a[i]-i;
    for(register int i=0;i<n;i++)
    if(b[i]>maxx) maxx=b[i],p=i;
    c[p]=a[p];
    for(register int i=p-1;i>=0;i--) c[i]=c[i+1]-1,c[i]%=n;
    for(register int i=p+1;i<n;i++) c[i]=c[i-1]+1,c[i]%=n;
    for(register int i=0;i<n;i++)
    {
        if(c[i]<a[i]) c[i]+=n;
        ans+=(c[i]-a[i])*(c[i]-a[i]);
    }
    printf("%lld\n",ans);
    return 0;
}
```
[P6170 [USACO16FEB]Circular Barn G题目传送门](https://www.luogu.com.cn/problem/P6170)


---

## 作者：Aw顿顿 (赞：1)

贡献是 $n^2$ 的形式，这是很值得思考的。

首先推论：奶牛走过的路径中，不能够存在其他奶牛的终点。用具体的例子来说，就是如果存在 $1\to 4$ 和 $2\to 3$ 的情况，那 $1\to 3$ 和 $2\to4$ 肯定是更优的。

为什么？我们考虑计算两者：$3^2+1^2=10$，$2^2+2^2=8<10$，因此后者更优。

如果用抽象的方式进行证明，可以理解为 $x^2+y^2$ 比 $(x+y)^2$ 来的小，这个结论是可以推广的。

显然恰当选择起点的方式，是通过 G 组这题的重要一点。如果一段区间的奶牛不够稠密，那么用它作为起点就不合理。什么叫不够稠密呢？我们可以理解为牛的数量不多于的数量。这也就是 @woshiren 题解中前缀和要减一的理由。

由于牛的数量等于 $n$，因此一定会出现大量的稀疏点以及少部分的稠密区域，因此，按照上述的思路进行枚举起点，可以减掉大量的奇怪而不必要的点。

实现可以看一下代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005 
using namespace std;
int n,c[N],cur;
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
    	scanf("%lld",&c[i]);
    	c[i+n]=c[i];//断环为链 
	}for(int i=1;i<=n;i++){
		cur=0;queue<int>q;
		for(int j=i;j<i+n;j++){
			while(c[j]>0)q.push(j),c[j]--;
			if(q.empty()){cur=-1;break;}
            if(!c[j])cur+=(j-q.front())*(j-q.front()),q.pop();
        }if(cur!=-1){printf("%lld\n",cur);return 0;}
    }return 0;
}
```



---

## 作者：zmnjkl (赞：0)

本人水的第一篇题解，写的较差请谅解~


------------
这题本质上和银组的 P3137 一致，除了不能用 $O(N^2)$ 来解。

### 题意：

有 $N$ 头奶牛顺时针经过一个环，环一共 $N$ 个位置，某些为空。奶牛能量消耗为走的路程平方，要求消耗最少能量填满所有空位。

### 分析：

- 为了让总能量值最少，要尽可能保证每头奶牛走的路程最短，因为能量消耗是距离平方。

- 要拿满分必须同时带着所有当前的奶牛走，不然会超时。

- 每头 “牵着走” 的奶牛得记录位置，让最早来的最先抵达空位。

- 保证循环数组。

### 思路：

- 记录之前多余的奶牛数量（假设一个格子大于 $1$ 头奶牛数量，则把剩下的奶牛 “牵着走”）。

- 用队列储存所有当前奶牛的下标（保证最早来的牛最先走）。

- 找到某个起点，保证这个起点开始往后能够填满所有空位。这里通过反向遍历求出 $sum$，并从 $sum$ 数组中找到最大的值作为起点。

- 把原先的数组乘以 $2$（起到数组循环作用，这样也不需要取模了）。

- **进行奶牛交换：** 如果当前位置不为空且手上有 “牵着走” 的奶牛时，用手上的奶牛和当前位置上的奶牛进行交换，保证下一次奶牛的能量值 “刷新”。


------------
### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long //别忘了开long long!
using namespace std;
int n,num[212345],sum[114514],c,idx,ans; //num储存2*原来的数组，idx为起点下标
signed main(){
	cin >> n;
	for(int i=0;i<n;i++)cin >> num[i];
	for(int i=n-1;i>=0;i--){//反向遍历求出sum中的值，用于求起点下标
		c+=num[i]-1;
		sum[i]=c;
	}c=0;
	for(int i=0;i<n;i++)//查询sum中的最大值下标设为起点
		if(sum[i]>c){
			idx=i;
			c=sum[i];
		}
	for(int i=n;i<n*2;i++)num[i]=num[i-n];//数组*2，保证循环
	queue<int>q;//队列存当前所有奶牛下标
	for(int i=idx;i<n+idx;i++)
		if(num[i]){
			if(!q.empty()){//如果数组不为空且手头有牵着的牛
				ans+=pow(i-q.front(),2);
				q.pop();//进行奶牛的交换，保证最小能量消耗并计算ans
				q.push(i);
			}
			for(int j=1;j<num[i];j++)q.push(i);//除了一头奶牛之外别的全部拿走
			num[i]=1;
		}else{
			ans+=pow(i-q.front(),2);//如果当前为空位，则拿出最早进队列的奶牛
			num[i]=1;
			q.pop();
		}
	cout << ans;
}

```



---

## 作者：_zexal_ (赞：0)

## 思路
转换题意，对于第 $i$ 个牛棚来说，有多少个牛经过就等于前面还有多少个牛棚没填满。假设存在一牛棚有 $i$ 头牛走过，那么由于最后每个牛棚只能站一头牛，所以，他前面必定有 $i-1$ 个牛棚为空，这样，我们就转换了题意，把他变成一个环，然后模拟即可，如果有多余的牛，我们就往前走，如果我们每一个点都有了牛，就可以结束了。最后算出对于任意一个牛棚牛的经过次数，然后直接计算即可。对于正确性的保障，也很好说，最先到必定花费最小。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int walk,next,num;
}a[100005];
int n;
long long ans,ans1;
bool book[100005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].num;
		a[i].next=i%n+1; //变成环 
	}
	int post=1;
	while(ans1!=n){
		if(a[post].num>1){前走 
			a[a[post].next].num+=a[post].num-1;
			a[a[post].next].walk+=a[post].num-1;
			a[post].num=1;
		}
		if(a[post].num==1&&book[post]==0){
			book[post]=1;
			ans1++; 
		}
		post=a[post].next;
	}
	for(int i=1;i<=n;i++) ans+=a[i].walk*a[i].walk;
	cout<<ans;
	return 0;
} 
```


---

## 作者：Supor__Shoep (赞：0)

首先一看到题目我就想到了逆推。。

按照题目要求，让目前每一个牛回到自己的房间，也就是每个房间只允许有一只牛，那么我们就可以用数组假定第 $i$ 头牛的初始房间编号。

接着，我们定义一个队列，这个队列是可以妙用的！！

从一个房间开始，按照逆向遍历完所有的房间，用定义的队列存放每一个空着的房间编号。遍历完之后，此时队列的首位一定是顺时针方向最优的一间。我们把这里多余的牛搬到队列首位的房间去，也就是原本的奶牛数必须要在 $1$ 以上才可以进行此操作。

即为：

    while(a[i]>0&&!que.empty())
    {
        a[i]--;
        a[que.front()]++;
        s[que.front()]=s[i];
        que.pop();
    }
    
#### 这个时候有人要问了：为什么队列首位的房间一定是最优房间呢？

因为这样可以让后面奶牛的移动能量尽量小。不信你试试。。

进行完操作之后，特殊来看队列是有可能还有元素的。这个时候我们进行重复的操作，继续把队列里剩下的元素全部用完，更好达到最优解。

最后就是统计答案了。

这个没有什么说的，按照走过的 $d$ 个房间往答案上增加 $d^2$ 。

此时你以为可以对了

但是别忘记把数据范围看一下（懂的都懂）。

代码如下：

```cpp

#include<bits/stdc++.h>
using namespace std;
int a[100005];
int s[100005];
long long ans;
int main()
{
	queue<int> que;
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	for(int i=0;i<n;i++)
	{
		s[i]=i;
	}
	for(int i=n-1;i>=0;i--)
	{
		while(a[i]>0&&!que.empty())
		{
			a[i]--;
			a[que.front()]++;
			s[que.front()]=s[i];
			que.pop();
		}
		if(a[i]==0)
		{
			que.push(i);
		}
	}
	int i=-1;
	while(!que.empty())
	{
		i=(i+n)%n;
		while(a[i]>0&&!que.empty())
		{
			a[i]--;
			a[que.front()]++;
			s[que.front()]=s[i];
			que.pop();
		}
		if(a[i]==0)
		{
			que.push(i);
		}
		i--;
	}
	for(int i=0;i<n;i++)
	{
		if(s[i]>i)
		{
			ans+=long((i+n-s[i])*(i+n-s[i]));
		}
		else
		{
			ans+=long((i-s[i])*(i-s[i]));
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：UperFicial (赞：0)

$\text{Upd 10.17}$ 将非公式的 $\LaTeX$ 换成了公式块。

问题看起来不太好做，不妨先想一想简单的问题。对于三个房间编号 $a,b,c$，且 $a<b<c$，如果 $a,b$ 均有一只奶牛，$c$ 没有奶牛，要想使得 $a$ 没有奶牛，$b,c$ 均有一只奶牛，最优策略应该是什么呢？

  - $a$ 直接到 $c$，这样的花费是 $(c-a)^2$。
  
  - $a$ 到 $b$，$b$ 也到 $c$，这样的花费是 $(b-a)^2+(c-b)^2$。
  
不妨设 $x=b-a,y=c-b$，则：

  - $a$ 直接到 $c$ 的花费为 $(x+y)^2$。
  
  - $a$ 到 $b$，$b$ 也到 $c$ 的花费为 $x^2+y^2=(x+y)^2-2xy<(x+y)^2$。
  
所以我们知道了，第二中方案比第一中方案更优。这个结论说明了什么？很显然，我们在移动牛的过程中，最优的移动方案是，移动的牛不能越过其它的牛。

所以说，我们可以选择一个起点 $s$，从这个起点 $s$ 开始，每一个房间都将多余的奶牛移动到下一个房间。

如果下一个房间还多出来奶牛再如同上述一样处理即可。

那么起点应该怎么选？那就直接枚举一个起点。

这样我们记录每个奶牛的路程 $d_i$，最后答案即为 $\sum_{i=1}^nd_i^2$。

为了方便，我们也要存一下每一个牧场里有哪些牛，直接存会炸掉，所以可以用 `vector` 来维护。

但这样做的复杂度是 $\mathcal{O}(n^2)$ 的，在 $n\le 10^5$ 之下难以承受。

考虑我们把时间浪费在什么地方，移动奶牛肯定是必须消耗一个 $\mathcal{O}(n)$ 的，而恰恰是找起始点的过程中消耗的时间太多，如果我们能通过预处理，得出真正的起点在哪里的话，是不是就能做到 $\mathcal{O}(n)$ 的了？

答案是肯定的。现在问题就是选择起点了。不妨猜一个结论：最大子段和的开头位置。

这个结论可以用反证法证明，读者自证不难（雾

然后就是要求环状的最大子段和，这个直接 $\mathcal{O}(n)$ 的 `dp` 就可以了。不过这里是环状的序列，需要断环成链的小技巧。

另外注意要开 $\text{long long}$。

复杂度 $\mathcal{O}(n)$。

---

