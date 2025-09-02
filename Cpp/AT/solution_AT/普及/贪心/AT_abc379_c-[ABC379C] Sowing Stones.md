# [ABC379C] Sowing Stones

## 题目描述

给你两个数 $n$，$m$。

表示现在有 $n$ 个格子，再给你 $m$ 组数据，表示在第 $X_i$ 个格子上有 $A_i$ 个石头。

有以下操作（可以不移动）。

- 对于第 $i$ 个格子，如果这个格子上有石头 ，可以将这个格子的一个石头移动到第 $i+1$ 个格子上。

求使得每个格子上恰好有一个石头的最小移动次数，如果无法满足条件输出 $-1$。


- 第一行：$N$ $M$ 

- 第二行：$X_1$ $X_2$ $\ldots$ $X_M$

- 第三行：$A_1$ $A_2$ $\ldots$ $A_M$

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^{9} $
- $ 1\ \leq\ M\ \leq\ 2\ \times\ 10^{5} $
- $ M\ \leq\ N $
- $ 1\ \leq\ X_i\ \leq\ N $ $ (1\ \leq\ i\ \leq\ M) $
- $ X_i\ \neq\ X_j $ $ (1\ \leq\ i\ <\ j\ \leq\ M) $
- $ 1\ \leq\ A_i\ \leq\ 2\ \times\ 10^{9} $ $ (1\ \leq\ i\ \leq\ M) $
- 输入为整数
 
### Sample Explanation 1

可以通过如下 $4$ 次操作使条件满足，且没有比 $4$ 次更小的次数。

初始条件：第一个格子上有 $3$ 个石头，第四个格子上有 $2$ 个石头。

- 移动一个石头从格子 $1$ 到格子 $2$。

- 再移动一个石头从格子 $1$ 到格子 $2$。 

- 移动一个石头从格子 $2$ 到格子 $3$。

- 移动一个石头从格子 $4$ 到格子 $5$。

操作完成后每个格子上都有一个石头。

### Sample Explanation 2

这个数据中无论如何移动一定无法使每个格子上有一个石头。

## 样例 #1

### 输入

```
5 2
1 4
3 2```

### 输出

```
4```

## 样例 #2

### 输入

```
10 3
1 4 8
4 2 4```

### 输出

```
-1```

# 题解

## 作者：Po7ed (赞：4)

细节有亿点多。赛时硬控我 30+ min，必须写篇题解纪念一下。

做法就类似于 generals.io，如果你玩过肯定马上会了。

先以 $x_i$ 为关键字排序。排序后 $x_1$ 必须为 $1$，否则 $[1,x_1)$ 无法填上石子。

我们将 $a_i$ 均递减 $1$，表示留在 $x_i$ 一个石子。

```cpp
#define NS return puts("-1"),0

for(int i=1;i<=m;i++)
{
	cin>>a[i].x;
}
for(int i=1;i<=m;i++)
{
	cin>>a[i].a;
	a[i].a--;
}
std::sort(a+1,a+m+1);
if(a[1].x!=1)NS;
```

没有石子的位置为：$(x_1,x_2),(x_2,x_3),\cdots,(x_m,n+1)$，我们算出这些区间的长度，并模拟移动。

```cpp
a[m+1].x=n+1; // 新建节点，方便统计 (x_m,n+1)
ll ans=0,tmp;
for(int i=1;i<=m;i++)
{
	tmp=a[i+1].x-a[i].x-1; // 无石子区间长度
	if(a[i].a<tmp)NS; // 石子不够，无解
	a[i].a-=tmp; // 将石子均摊到无石子区间
	ans+=(tmp*(tmp+1)/2); // 计算操作数
	a[i+1].a+=a[i].a; // 将剩下石子移动到下一个位置
	ans+=(tmp+1)*a[i].a; // 计算移动操作数
}
if(a[m+1].a>0)NS; // 如果有剩下的石子，无解
printf("%lld",ans);
```

[完整代码](https://atcoder.jp/contests/abc379/submissions/59619178)。

赛时吃了 5 发罚时，这告诉我们遇到细节多的题一定要冷静分析。

---

## 作者：I_Love_DS (赞：4)

## 闲话

为什么翻译要把 石头 翻译成 结石 呢？？/yiw

哦，是 格子 翻译成 细胞 了。。

## 思路

鉴定为模拟 + 小贪心。

注意到题面要求最后达到**每个格子恰好一个石头**的状态。所以我们可以考虑从后往前填。

记最后一个填上的位置为 $r$，那么每一次我们应该从 $r-1$ 开始往前填。

如果填到了 $x_i$，$a_i$ 还为正，因为石头只能往后移，所以无解。

填到最后如果 $r \neq 1$ 说明石头少了没填完，无解。

对了，每一次操作的贡献就是 $[(r-1-x_i)+(r-a_i-x_i) ]\times a_i \div 2$。这就是每一次将一个石头移到当前 $r-1$ 的位置的贡献和。可以看出是一个等差数列。

注意开 `long long`！

时间复杂度 $O(m \log m)$，排序的时间复杂度。

## 代码

```cpp
#include <bits/stdc++.h>

#define ll long long

using namespace std;

const int N = 2e5 + 50;

ll n, m;
ll ans = 0;

struct node {
	ll x, c;
	friend bool operator < (const node &x, const node &y) {
		return x.x > y.x;
	}
} a[N];

int main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%lld", &a[i].x);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%lld", &a[i].c);
	}
	int r = n + 1;
	sort(a + 1, a + m + 1); // 排序，从后往前填石头
	for (int i = 1; i <= m; i++) {
		if (r - a[i].x < a[i].c) { // 石头过多，无解
			printf("-1\n");
			return 0;
		}
		ans += ((r - a[i].c - a[i].x) +
        (r - 1 - a[i].x)) * a[i].c / 2; // 算贡献，如上文
		r -= a[i].c; // 别忘了填完要把 r 更新一下
	}
	if (r != 1) printf("-1\n");
	else printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：kairuigg (赞：2)

# [原题传送门](https://www.luogu.com.cn/problem/AT_abc379_c)
 ## 题目大意
 有 $N$ 个单元格，最初有 $M$ 个单元格中包含棋子，其中第 $X_i$ 个单元格中包含 $A_i$ 个棋子。可以执行任意次操作（操作次数可以为 $0$），每次操作可以将第 $i$ $(1\leq i\leq N-1)$ 个格子里的一个棋子移动到第 $i+1$ 个格子中。 问最少执行几次操作可以使每个格子有且仅有一个棋子，若不能则输出 -1。
 ## 思路
 我们可以考虑三种情况
 
1.  如果当前格子 $X_i$ 内的数正好使 $X_i\to X_{i+1}$ 内所有的格子被填满，并且每个格子内只有一个棋子，那么这一段的贡献就是由只由最初棋子数为 0 的格子提供。
2.  如果当前格子 $X_i$ 内的数不够使 $X_i\to X_{i+1}$ 内的所有格子被填满，一定不满足题意，输出 -1。
3.  如果当前格子 $X_i$ 内的数足够使 $X_i\to X_{i+1}$ 内的格子被填满，并且填满之后第 $X_i$ 个格子内剩余的棋子数大于 1。我们可以考虑讲第 $X_i$ 个格子剩余的棋子移动到第 $X_{i+1}$ 中。那么最后的贡献就来自最初棋子数为 0 的格子和第 $X_i$ 个格子中剩余的棋子数提供。 

    那这样就会有人问：如果第 $X_n$ 个格子中有剩余怎么办呢？我们可以再搞一个第 $X_{n+1}$ 个格子，将第 $X_n$ 个格子内的剩余移动到第 $X_{n+1}$ 个格子中就好了。这样我们只需要在最后判断第 $X_{n+1}$ 中有没有剩余的棋子就好了，有就输出 -1，没有就正常输出答案。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+5;
struct node{
    int x,a;
}q[maxn];
bool cmp(node x,node y){//既然题目没保证X有序就排一下序吧
    return x.x<y.x;
}
signed main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>q[i].x;
    }
    q[m+1].x=n+1;//建第m+1个点来存第m个点剩下的
    for(int i=1;i<=m;i++){
        cin>>q[i].a;
    }
    sort(q+1,q+m+1,cmp);
    if(q[1].x!=1){//如果第一个存在棋子的点不在1的位置，那么他前面的点的棋子数就一定的0，直接输出-1
        cout<<-1;
        return 0;
    }
    int ans=0;
    for(int i=1;i<=m;i++){
        if(q[i+1].x-q[i].x==q[i].a){//对应第一种情况
            ans+=(q[i+1].x-q[i].x-1)*(q[i+1].x-q[i].x)/2;//总贡献=贡献为0的点的贡献（利用等差数列求出这一段的贡献，下同）
        }
        else if(q[i+1].x-q[i].x<q[i].a){//对应第三种情况
            q[i+1].a+=q[i].a-q[i+1].x+q[i].x;//将第多出的棋子移动到下一个位置
            ans+=(q[i+1].x-q[i].x-1)*(q[i+1].x-q[i].x)/2+(q[i].a-q[i+1].x+q[i].x)*(q[i+1].x-q[i].x);//总贡献=为0的点的贡献+移动多余棋子的贡献
        }
        else{//对应第二种情况
            cout<<-1;
            return 0;
        }
    }
    if(q[m+1].a){//如果第m+1个点还有剩余就不满足有且仅有一个棋子
        cout<<-1;
        return 0;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Cosine_Func (赞：2)

非常好想的一道贪心。

题意不再赘述。首先要以坐标为关键字对包含棋子的单元格排序，并判断无解的情况。在以下两种条件中的任意一个成立时，应直接输出 `-1`：

- $\sum_{i=1}^M X_i\ne N$

- $\min X\ne 1$

接下来按一下的贪心策略操作：

- 将 $A_i$ 减一
- 计算当前单元格与下一个包含棋子的单元格的距离，设这个距离为 $D$
  - 若 $A_i<D$，问题无解
  - 若 $A_i=D$，将移动棋子的花费计入答案。容易发现花费是一个等差数列，由求和公式可知花费为 $\frac{(1+D)\times D}{2}$
  - 若 $A_i>D$，先按第二条计算，再把未用完的棋子转移到下一个包含棋子的单元格中，注意不要忘记将花费计入答案

在初始化时，要额外设置一个包含棋子的单元格并令其坐标为 $N+1$。

这一算法的时间复杂度是 $O(M\times \log M)$，足够通过此题。

[参考代码](https://atcoder.jp/contests/abc379/submissions/59614019)

---

## 作者：fzark (赞：1)

看了一下题解，好像没有优先队列的做法，这里介绍一个新的优先队列思路。
## 题意

[原题链接](https://www.luogu.com.cn/problem/AT_abc379_c)

有 $n$ 个单元格，$m$ 个单元格中有棋子。第 $x_i$ 个单元格有 $a_i$ 个棋子。现有操作如下：

- 选择 $1\le i \lt n$ 包含棋子的单元格，将该单元格中的一个棋子移动到 $i+1$ 处。

求每个单元格**只能**包含 $1$ 个棋子的最小操作数。

## 思路
由于数据范围 $n$ 很大，考虑将所有的有棋子的单元格离散化。对于每一个有棋子的单元格，我们先贪心考虑将它补满到下一个有棋子的单元格，如果有剩余，我们将它压入到大根堆，用于后续给补不满的提供棋子。

## 证明
现在考虑证明这个思路的复杂度。首先我们离散化并排序了有棋子的单元格，这样的话就不需要遍历 $n$ 了，时间复杂度是 $O(m)$ 的。

然后证明一下优先队列为什么可行：对于一个棋子，如果它需要补充，肯定是从后面有多的棋子拿取，然后我们使用优先队列的话，就可以以 $\log m$ 的复杂度去拿，并且很简单，只要堆里有，我们就拿即可。复杂度得证。

并且我们用大根堆和小根堆都没有关系，因为到最后肯定要用完堆中的棋子，有剩余就无解了。

总的下来，复杂度为 $O(m\log m)$，可以通过本题。

## 代码

```python
import heapq
# 等差数列计算费用
def calc(w):
    return (1 + w) * w // 2
def solve():
    n, m = map(int, input().split())
    a = [[0,0,0] for i in range(m)]
    li = list(map(int,input().split()))
    for i in range(len(li)):
        a[i][0] = li[i]
    li = list(map(int,input().split()))
    for i in range(len(li)):
        a[i][1] = li[i] - 1
    # 按照坐标从小到大排序
    a.sort()
    # 如果第一个不是1，显然无解
    if a[0][0] != 1:return -1
    ans = 0
    for i in range(len(a)- 1):
        a[i][2] = a[i + 1][0] - a[i][0]
    # 计算最后一个有棋子的单元格和n的差距
    a[-1][2] = n - a[-1][0] + 1
    h = []
    for u,v,w in a:
        # 如果有多余的，压入大根堆
        if v >= w:
            heapq.heappush(h,[-u,v - (w - 1)])
            ans += calc(w - 1)
        elif v == w - 1:
            ans += calc(w - 1)
        else:
            cnt = w - v - 1
            while h and cnt > 0:
                cur = min(cnt,h[0][1])
                h[0][1] -= cur
                cnt -= cur
                ans += cur * (u - abs(h[0][0]))
                if h[0][1] == 0:heapq.heappop(h)
            if cnt > 0:return -1
            ans += calc(w - 1)
    # 关键：题目要求每个单元格 正好 有一个，如果多出来了显然无解
    if len(h) > 0:return -1
    return ans

print(solve())

```

---

## 作者：zhangzirui66 (赞：1)

比较简单，但细节较多，吃了不少罚时。

思路简单来说可以想象成一个有棋子的格子到下一个有棋子之间的格子全部填充，花费次数是一个首项是 $1$，公差是 $1$，末项是长度 $-1$ 的等差数列的和。

然后把多余的扔到下一个有棋子的格子处理。

处理边界就行了，等差数列的值是 $m^2$ 级别的，要开 `long long`。

---
## 丰富注释版代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, m, sum, ans, flag;//flag 判无解
struct node{
	long long a, b;
}x[200005];
bool cmp(node x, node y){
	return x.a < y.a;
}
int main(){
	cin >> n >> m;
	for(long long i = 1; i <= m; i ++) cin >> x[i].a;
	for(long long i = 1; i <= m; i ++) cin >> x[i].b, sum += x[i].b;
	if(sum != n) flag = 1;//数量不合适
	sort(x + 1, x + m + 1, cmp);//按位置排序
	for(long long i = 1; i < m; i ++){
		if(x[i + 1].a - x[i].a > x[i].b) flag = 1;//不够放满
		ans += (x[i + 1].a - x[i].a) * (x[i + 1].a - x[i].a - 1) / 2LL;//上面的等差数列
		ans += (x[i].b - 1 - (x[i + 1].a - x[i].a - 1)) * (x[i + 1].a - x[i].a);//扔到下一次处理
		x[i + 1].b += (x[i].b - 1 - (x[i + 1].a - x[i].a - 1));//下一次获得到的棋子
	}
	if(x[1].a != 1) flag = 1;//第一个地方没有
	if(!flag) cout << ans + (x[m].b - 1) * x[m].b / 2LL;//最后面还有一个等差数列
	else cout << -1;
	return 0;
}
```
---
## 纯净版代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, m, sum, ans, flag;
struct node{
	long long a, b;
}x[200005];
bool cmp(node x, node y){
	return x.a < y.a;
}
int main(){
	cin >> n >> m;
	for(long long i = 1; i <= m; i ++) cin >> x[i].a;
	for(long long i = 1; i <= m; i ++) cin >> x[i].b, sum += x[i].b;
	if(sum != n) flag = 1;
	sort(x + 1, x + m + 1, cmp);
	for(long long i = 1; i < m; i ++){
		if(x[i + 1].a - x[i].a > x[i].b) flag = 1;
		ans += (x[i + 1].a - x[i].a) * (x[i + 1].a - x[i].a - 1) / 2LL;
		ans += (x[i].b - 1 - (x[i + 1].a - x[i].a - 1)) * (x[i + 1].a - x[i].a);
		x[i + 1].b += (x[i].b - 1 - (x[i + 1].a - x[i].a - 1));
	}
	if(x[1].a != 1) flag = 1;
	if(!flag) cout << ans + (x[m].b - 1) * x[m].b / 2LL;
	else cout << -1;
	return 0;
}
```

---

## 作者：CaoSheng_zzz (赞：1)

考虑根据有石子的点去做，我们首先按 $x$ 将 $a$ 排序，然后假设 $x_1 = s, x_2 = t$，那么如果要完成题目的要求我们至少需要 $s$ 这个位置上有 $t - s$ 个石子，如果没有这么多那就没有满足要求的答案。

如果有这么多石子，那么石子要走到 $s + 1, s + 2, \dots, t - 1$ 然后因为是从 $s$ 出发所以步数为 $1, 2, \dots, t - x - 1$ 然后求和公式 $(t - x - 1) \times (t - x) \div 2$。

如果有多的石子那么还需要的步数为多的石子个数乘上 $t - x$。

思路说完了接下来是一些细节问题。

- 如果没有石子位于 $1$ 这个位置那么没有答案。

- 如果没有石子位于 $n$ 这个位置那么我们需要添加一个 $x_{m + 1} = n, a_{m + 1} = 0$ 的位置。

- 如果将石子总数加起来不等于 $n$ 那么也没有答案。

Code：
```cpp
const int maxm = 2e5 + 2 ;
struct node {
    ll x, a ;
    bool operator < (const node &y) { return x < y.x ;}
} d[maxm] ;
int n, m ;
ll ans = 0, sum = 0 ;

signed main() {
    n = read(), m = read() ;
    for(int i=1 ; i<=m ; i++) d[i].x = read() ;
    for(int i=1 ; i<=m ; i++) d[i].a = read(), sum += d[i].a ;
    std::sort(d + 1, d + m + 1) ;
    if(d[1].x != 1) { puts("-1") ; return 0 ;}
    if(d[m].x != n) d[++ m].x = n ;
    if(sum != n) { puts("-1") ; return 0 ;}
    for(int i=2 ; i<=m ; i++) {
        if(d[i - 1].a < d[i].x - d[i - 1].x) { puts("-1") ; return 0 ;}
        ans += (d[i].x - d[i - 1].x) * (d[i].x - d[i - 1].x - 1) / 2 ;
        d[i - 1].a -= d[i].x - d[i - 1].x ;
        if(d[i - 1].a > 0) ans += d[i - 1].a * (d[i].x - d[i - 1].x), d[i].a += d[i - 1].a ;
    }
    return output(ans), 0 ;
}
```

---

## 作者：OIer_Tan (赞：0)

怎么这场 C 这么多人过不去啊，简单小贪心。

## 题意

在一行中有 $N$ 个格子，编号从 $1$ 到 $N$。最初，仅 $M$ 个格子中含有棋子，而第 $X_i$ 个格子中含有 $A_i$ 个棋子 $(1 \leq i \leq M)$。

您可以执行以下任意次数（可能为零）的操作：

- 如果单元格 $i$（$1 \leq i \leq N-1$）包含一个棋子，则将一个棋子从单元格 $i$ 移动到单元格 $i+1$。

求达到每个 $N$ 单元格中正好有一块棋子的状态所需的最少操作次数。如果不可能，请打印 $-1$。

## 思路

首先考虑如果总旗子个数不为 $N$ 个，这显然无法满足。

接下来，由于石子只能往右挪，往左是不行的，因为显然优先用最靠左的总距离更小，所以我们维护一个下标，表示下一个需要石子的位置，这样就可以简单计算答案。

## 代码

```cpp
#include <bits/stdc++.h>

#ifndef CRT
#define endl '\n'
#endif

using namespace std ;

typedef long long ll ;
typedef unsigned long long ull ;
typedef long double ld ;

const ll N = 2e5 + 5 ;

ll n , m ;

pair <ll,ll> p [N] ;

int main ()
{
	ios::sync_with_stdio ( 0 ) ;
	cin.tie ( 0 ) ;
	cout.tie ( 0 ) ;
	cin >> n >> m ;
	ll sum = 0 ;
	for ( ll i = 1 ; i <= m ; i ++ )
	{
		cin >> p [i].first ;
	}
	for ( ll i = 1 ; i <= m ; i ++ )
	{
		cin >> p [i].second ;
		sum += p [i].second ;
	}
	if ( sum != n )
	{
		cout << -1 << endl ;
		exit ( 0 ) ;
	}
	sort ( p + 1 , p + 1 + m ) ;
	ll last = 1 , ans = 0 ;
	for ( ll i = 1 ; i <= m ; i ++ )
	{
		if ( last < p [i].first )
		{
			cout << -1 << endl ;
			exit ( 0 ) ;
		}
		ans += ( last - p [i].first ) * p [i].second + ( p [i].second - 1 ) * p [i].second / 2 ;
		last += p [i].second ;
	}
	if ( last != n + 1 )
	{
		cout << -1 << endl ;
		exit ( 0 ) ;
	}
	cout << ans << endl ;
	return 0 ;
}
```

---

## 作者：IGA_Indigo (赞：0)

## 题目大意
有一个从 $1$ 到 $n$ 的网格，一开始第 $x_i$ 个网格里都有 $a_i$ 个石头，每个网格只能向后运石头，问所有 $n$ 个格子里都有且仅有一个石头的最小操作数。

如果不能做到输出 $-1$。
## 大体思路
首先先按照 $x_i$ 大小给 $x_i$ 和 $a_i$ 排序（没说给出的是有序的，一定注意）。

我们先来说说两个 $-1$ 的判定条件。

- 第一个是所有 $a_i$ 加起来不等于 $n$，无论怎么放也不能每个格子放一颗石头。

- 第二个是在从 $1$ 到 $m$ 遍历的过程中，如果之前的所有石头加起来（记录一个变量 $sumall$ 存储）不能填满当前格子之前的所有格子，由于不能往前放，所以这种情况也不行。
```cpp
if(sumall<sz[i].x-1){
  puts("-1");
  return 0;
}
```
然后我们推一个式子，用等差数列来求解。

正如样例所说的：
```cpp
5 2
1 4
3 2
```
我们画一个图来看一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/s1ww9089.png)

如果 $sum$ 代表 $x_{i-1}$ 现在有的石头数，可以明显的得到等差数列的大项是 $sum-1$，小项是 $sum-x_i+x_{i-1}$，项数是 $x_i-x_{i-1}$。

$$
ans=ans+(sum-1+sum-x_i+x_{i-1})\times (x_i-x{i-1})\div 2;
$$

此时我们的 $sum=sumall-x_i+1$。

不会出现小项小于零的情况，因为我们前面有"判定 $-1$ 的第二个条件"。

如果感觉不够明显，我们可以在前面多放一个石头在模拟一遍。

有一点注意的是，$x_1$ 不能够这样处理，$sum-1$ 会变成负数，直接跳过不操作即可。

在最后的时候，我们处理 $x_m$ 到 $n$ 的答案即可。

$$
ans=ans+sum\times (n-x_m)\div 2;
$$
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long read(){
	long long x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			f=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
void write(unsigned long long x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9){
		write(x/10);
	}
	putchar(x%10+'0');
	return ;
}
struct node{
	unsigned long long x,a;
}sz[200005];
bool cmp(node aa,node bb){
	return aa.x<bb.x;//按照 x 的大小排序
}
int main(){
	unsigned long long n=read(),m=read();
	unsigned long long sum=0;
	for(int i=1;i<=m;i++){
		sz[i].x=read(); 
	}
	for(int i=1;i<=m;i++){
		sz[i].a=read();
		sum+=sz[i].a;
	}
	sort(sz+1,sz+1+m,cmp);//注意一定要排序 
	if(sum!=n){//判断 -1 的第一个条件 
		puts("-1");
		return 0;
	}
	sum=0;
	unsigned long long sumall=0;
	unsigned long long ans=0;
	for(int i=1;i<=m;i++){
		if(sumall<sz[i].x-1){//判断 -1 的第二个条件 
			puts("-1");
			return 0;
		}
		if(i!=1){
			ans+=(sum-1+sum-sz[i].x+sz[i-1].x)*(sz[i].x-sz[i-1].x)/2;
		}//第一个不进行操作 
		sumall+=sz[i].a;//判断条件的工具 
		sum=sumall-sz[i].x+1;//sum 的改变 
	}
	ans+=sum*(n-sz[m].x)/2;//最后处理 sz[m].x 到 n 的答案 
	write(ans);//输出即可 
	return 0;
}
```

---

## 作者：lucasincyber (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc379_c)
## 思路
考虑贪心。我们会发现，每一颗石子只能往右移动，不能往左移动。因为恰好需要 $n$ 颗石子，那如果有的石子不为 $n$ 则一定无解。如果第一个位置没有石子也一定无解（无法通过操作将石头移动过来）。

我们发现，对于每一个有石子的位置，若有 $x$ 颗石子，则一定会将剩下 $x-1$ 颗石子向右移。设相邻两个有石子的位置分别为 $a_i$ 和 $a_{i+1}$，设 $dis = a_{i+1} - a_i$，我们来分类讨论：

1. 若 $x - 1 < dis$，则这些石子无法将这一区间覆盖，则无解；
2. 否则，需要移动 $dis - 1$ 颗石子。每一个石子需要 $1$、$2$、...、$dis-1$。那这一部分的总操作数为 $\displaystyle \frac{dis \times (dis - 1)}{2}$。剩下的 $x - dis$ 颗石子可以直接移动到下一节点，在下一节点进行处理。那这一部分的总操作数为 $(x - dis) \times dis$。最后求和即可。
## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;

struct node
{
	int id, x;
} a[N];

int n, m, sum, ans;
int x[N];

bool cmp(node x, node y)
{
	return x.id < y.id;
}

int calc(int x)
{
	return (x * (x - 1) / 2);
}

signed main()
{
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= m; i++)
		scanf("%lld", &x[i]);
	for (int i = 1, y; i <= m; i++)
	{
		scanf("%lld", &y);
		sum += y;
		a[i] = {x[i], y};
	}
	if (sum != n)
	{
		printf("-1\n");
		return 0;
	}
	sort(a + 1, a + m + 1, cmp);
	a[m + 1] = {n + 1, 0};
	if (a[1].id != 1)
	{
		printf("-1\n");
		return 0;
	}
	for (int i = 1; i <= m; i++)
	{
		int num = a[i + 1].id - a[i].id;
		if (a[i].x < num)
		{
			printf("-1\n");
			return 0;
		}
		ans += calc(num);
		ans += (a[i].x - num) * num;
		a[i + 1].x += (a[i].x - num);
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

