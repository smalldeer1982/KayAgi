# [USACO16OPEN] Landscaping P

## 题目背景

*本题与 [2012 年 3 月月赛银组同名题目](/problem/P3049) 在题意上一致，唯一的差别是数据范围。*

## 题目描述

Farmer John 打算修建一座花园，他需要移动不少泥土。

花园由 $N$ 个花坛组成（$1 \leq N \leq 10^5$），其中花坛 $i$ 包含 $A_i$ 单位的泥土。FJ 希望花坛 $i$ 包含 $B_i$ 单位的泥土，保证 $0 \leq A_i,B_i \leq 10$。

为了达到这个目标，他可以做这几件事情：

- 购买一单位的泥土，放在指定的花坛中，费用为 $X$。
- 从任意一个花坛中移走一单位泥土，费用为 $Y$。
- 从花坛 $i$ 运送一单位泥土到花坛 $j$，费用为 $Z|i-j|$。

请你帮 FJ 计算移动泥土的最小开销。

## 说明/提示

按下面的方案，最小花费为 $210$，可以证明不存在开销更小的方案。

- 移除 $4$ 号花坛的一单位泥土，花费 $200$。
- 将 $4$ 号花坛的三单位泥土移到 $1$ 号花坛，花费 $3 \times 3=9$。
- 将 $3$ 号花坛的一单位泥土移到 $2$ 号花坛，花费 $1 \times 1=1$。

## 样例 #1

### 输入

```
4 100 200 1
1 4
2 3
3 2
4 0```

### 输出

```
210```

# 题解

## 作者：lytqwq (赞：15)

因为$A_i,B_i$很小，我们把每单位泥土分开看。

对于**每单位**泥土在第$i$个位置上，设处理该**单位**泥土花费$Vi$费用：


$V_i:$

1. 如果是少了泥土，可以花费$X$费用来解决，所以$V_i=X$，还可以向前面要泥土，要泥土一定向之前多泥土的地方要，要花费$Z|i-j|$费用，但之前的泥土我们已经考虑了它的贡献了，所以之前的泥土的贡献就要再减去（即之前的那个泥土多了，但是不需要处理了，后面少了的那个泥土直接要过来了），总的费用为$Z|i-j|-V_j$，所以$V_i=\min(X,Z|i-j|-V_j)$

1. 如果是多了泥土，可以花费$Y$费用来解决，所以$V_i=Y$。还可以往前面送泥土，送泥土一点向之前少泥土的地方送。同理，总的费用为$Z|i-j|-V_j$，所以$V_i=\min(Y,Z|i-j|-V_j)$


这样可以直接$O(100n^2)$计算了，可以解决此题的弱化版：[https://www.luogu.com.cn/problem/P3049](https://www.luogu.com.cn/problem/P3049)

但是对于此题，我们需要更快的方法：


拆开$V_i$的计算：

$V_i=\min(X,Z|i-j|-V_j)\space(i>j)$

$=\min(X,iZ-jZ-V_j)\space(i>j)$

$=\min(X,iZ+(-jZ-V_j))\space(i>j)$

所以，$V_i$的计算和前面的$j$有关的只有$(-jZ-V_j)$，要让当前的$V_i$最小，我们需要让$(-jZ-V_j)$最小。

为什么我们需要让$V_i$最小呢？为什么不把这个$j$留给后面的$V$呢？
 
前面的$(-jZ-V_j)$肯定是向后找最近的最好啊，越往后拖，$i$越大，$V_i$就有可能被$X$决定，还有可能出现距离更近的来更新。
 


开两个小根堆，一个存本来少了泥土的单位泥土的$(-jZ-V_j)$，可以用来更新现在多了泥土的地方。

另一个存本来多了泥土的单位泥土的$(-jZ-V_j)$，可以用来更新现在少了泥土的地方。

得到处理当前泥土的费用后把$(-iZ-V_i)$存进堆里，供后面的答案更新。



可以理解为后悔的贪心，把前面的费用给减去。
 
时间复杂度：$O(10nlog(10n))$
 
AC情况：[https://www.luogu.com.cn/record/42168237](https://www.luogu.com.cn/record/42168237)
 
代码如下：
 
 ```cpp
#include<bits/stdc++.h>
using namespace std;
const long long int N=100001;
long long int n,a[N],b[N],x,y,z;
long long int V[N];
long long int ans;
priority_queue<long long int,vector<long long int>,greater<long long int> > ovo,ovo2;
int main(){
	scanf("%lld%lld%lld%lld",&n,&x,&y,&z);
	for(long long int i=1;i<=n;i++){
		scanf("%lld%lld",&a[i],&b[i]);
		for(long long int o=1;o<=a[i]-b[i];o++){
			V[i]=y;
			if(!ovo.empty()){
				V[i]=min(V[i],i*z+ovo.top());
				ovo.pop();
			}
			ovo2.push(-V[i]-i*z);
			ans+=V[i];
		}
		for(long long int o=1;o<=b[i]-a[i];o++){
			V[i]=x;
			if(!ovo2.empty()){
				V[i]=min(V[i],i*z+ovo2.top());
				ovo2.pop();
			}
			ovo.push(-V[i]-i*z);
			ans+=V[i];
		}
	}
	printf("%lld\n",ans);
}

```





---

## 作者：Usada_Pekora (赞：12)

题意：给出数组 $a$，每次可以花费 $x$ 让一个数减去 $1$ ，花费 $y$ 让一个数加上 $1$，或者花费 $ z\left|i-j\right| $ 让 $a_i$ 减去 $1$ ，$a_j$ 加上 $1$ 。求让 $u$ 变成 $v$ 的最小花费。

如果我们扫到一个 $i$ ，且前面没有其他数可以操作，那就只能给它加上/减去了。如果后面遇到一个 $j$ ，且加减是和 $i$ 相反的，那就有了多种选择了: 继续给 $j$ 补上，花费 $x$ 或 $y$  ;  把前面的某一个 $i$ 给换过来（只换多余的部分），花费 $ z \left| i-j \right| - cost_i$ ，$cost_i$ 是 $i$ 已经的多余部分花费过的价值， 注意， 以上的操作建立在 $\left| u - v\right| = 1$ 的前提上， 也就是值的相差只有一的情况，那么运用时直接调用 $\left|u - v \right| $ 次就好了 。

$ z\left | i - j \right| - cost_i = zj - zi - v = zj - (zi + cost_i)$  把 $zj+cost_i$ 扔进大根堆， 每次减去最大。就可以确保这一步加上去的最小了。


```cpp
#include <iostream>
#include <queue>
#include <cmath>
#define int long long
using namespace std;
priority_queue<int> q[2];
int c[2], n, z, ans;
signed main() {
	ios::sync_with_stdio(false);
	cin >> n >> c[1] >> c[0] >> z;
	for (int i = 1, a, b, f; i <= n; i++) {
		cin >> a >> b;
		if (a == b) continue;
		f = a > b; //加上或减去
		for (int j = 1; j <= abs(a - b); j++) 
        if (q[f ^ 1].empty() || i * z - q[f ^ 1].top() > c[f ^ 1]) ans += c[f ^ 1], q[f].push(i * z + c[f ^ 1]);
            else ans += i * z - q[f ^ 1].top(), q[f].push(i * z + i * z - q[f ^ 1].top()), q[f ^ 1].pop();
    }
    cout << ans;
    return 0;
}
```


---

## 作者：AuCloud (赞：7)

# 贪心

考虑每一个花盆的泥土跟前面更新后，后面也许会被更优的方案影响，因此dp假了

于是想如何将这个“后效性”弥补：

假设只有三盆泥土$i,j,k$，其中$i$少了，$j$多了，$k$少了

为了方便，我们设他们与标准相差的都是1

对于i，我们花费$x$元购买1单位土

那么，对于$j$，我们可以：

- 移除1单位土，对答案贡献为y
- 向i盆内转移1单位土，贡献为$(j-i)\times z - x$

到$j$时，对答案贡献即为
$$
min(y,(j-i)\times z - x)
$$

设上面那个式子等于$v$

这时，$k$来了，同样少了一盆土

同样的，我们有两个选择：

- 买1单位土，对答案贡献为x
- 在$j$盆拿1单位土，对答案贡献为$(k-j)\times z-v$

······

考虑在转移$j$时，

$$
(j-i)\times z-x
$$
$$
= j\times z - i\times z - x
$$
$$
= j\times z - (i \times z + x)
$$
而在转移k时，这个$x$换成了$v$，即要更改的状态对答案的贡献

要想让这个东西最小，就要$(i \times z + x)$（或者说$(i \times z + v)$）最大

很容易想到大根堆维护

发现这个东西跟$j$没有关系，于是在每次处理当前点时把这个东西扔到大根堆里维护即可

### 注意：

1.缺土的花盆跟多土的花盆不能放在同一个大根堆里，要开两个分别存

2.在更改之前的操作时，“v”的意义会变化——当前操作的贡献

所以放在大根堆里的东西是`当前操作的贡献+i*z`

设$d$为当前大根堆堆顶

则在更改操作时，当前贡献为$i\times z - d$，再加上$i\times z$才是放在堆中的数据，即$2\times i\times z - d$

最后是代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
priority_queue<int>q1;
priority_queue<int>q2;
signed main()
{
    int ans = 0;
    int n, x, y, z;
    cin >> n >> x >> y >> z;
    for(int i = 1; i <= n; i++)
    {
        int a, b;
        cin >> a >> b;
//        if(a == b) continue;
        if(a < b)
        {
            for(int j = 1; j <= b - a; j++)
            {
                if(!q1.size() || i * z - q1.top() >= x)
                {
                    ans += x;
                    q2.push(i * z + x);
                }
                else
                {
                    int v = q1.top();
                    q1.pop();
                    ans += i * z - v;
                    q2.push(i * z * 2 - v);
                }
            }
        }
        else
        {
            for(int j = 1; j <= a - b; j++)
            {
                if(!q2.size() || i * z - q2.top() >= y)
                {
                    ans += y;
                    q1.push(i * z + y);
                }
                else
                {
                    int v = q2.top();
                    q2.pop();
                    ans += i * z - v;
                    q1.push(i * z * 2 - v);
                }
            }
        }
    }
    cout << ans;
}

```

---

## 作者：hzlqwq (赞：3)

由于加土删土移土的操作都是基于单个单位的泥土进行的，而且泥土范围 $1\leq A_{i},B_{i}\leq 10$ 非常小，我们简化问题，单独考虑每一个泥土单位：

对于第 $i$ 个花坛，如果它现在缺土（$A_{i}<B_{i}$），则：可以直接购进一个单位的泥土，花费为 $x$；若第 $j<i$ 个花坛多了土，可以从它那里拿一份过来，花费为 $z\lvert i-j\rvert -v$，其中 $v$ 是花坛 $j$ 那份土的花费，需要减掉避免算多（反悔）；最终花费为 $\min(x,z\lvert i-j\rvert -v)$；

同理，若第 $i$ 个花坛现在多土 ($A_{i}>B_{i}$)，则：可以直接删除一个单位的泥土，花费为 $y$；若第 $j<i$ 个花坛缺了土，可以移一份给它，花费为 $z\lvert i-j\rvert -v$；最终花费为 $\min(y,z\lvert i-j\rvert -v)$。

我们考虑化简移土花费：

$$
\begin{aligned}
&z\lvert i-j\rvert -v\text{ }(i>j)\\
=&zi-zj-v\\
=&zi-(zj+v)
\end{aligned}
$$

注意到 $zj+v$ 是只关于之前位置泥土的信息，且 $zj+v$ 越大，总花费越小；所以我们可以给多的泥土和少的泥土分别开一个大根堆记录这个信息，每次遍历到新泥土时比较是直接买删还是和之前的泥土移动便宜，本质上是 dp + 堆反悔贪心，时间复杂度 $O(n\log n)$。

具体考虑插入堆中的信息是什么：如果当前决定直接买卖，则花费 $v=x$ 或 $y$，插入 $zi+x$ 或 $zi+y$；如果当前决定反悔，则花费 $v=zi-(zj+v)=zi-heap.top()$，插入 $zi+(zi-heap.top())=2zi-heap.top()$。

更多细节见代码，简明易懂，有部分注释。

```cpp
#include <iostream>
#include <queue>

using namespace std;

const int N = 1e5 + 10;

long long n, x, y, z;
int a[N], b[N];
priority_queue<long long> mre, lss;
long long ans;

inline void speedup()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

int main()
{
    speedup();
    cin >> n >> x >> y >> z;
    for (int i = 1; i <= n; i++)
        cin >> a[i] >> b[i];
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= b[i] - a[i]; j++) // 少了
        {
            if (mre.size() && z * i - mre.top() < x) // 移土反悔
                ans += z * i - mre.top(), lss.push(2 * z * i - mre.top()), mre.pop();
            else // 直接购买
                ans += x, lss.push(z * i + x);
        }
        for (int j = 1; j <= a[i] - b[i]; j++) // 多了
        {
            if (lss.size() && z * i - lss.top() < y) // 移土反悔
                ans += z * i - lss.top(), mre.push(2 * z * i - lss.top()), lss.pop();
            else // 直接铲除
                ans += y, mre.push(z * i + y);
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：analysis (赞：2)

## Landscaping P 题解

求最优解问题我们会想什么？

贪心、动态规划、~~暴力~~。

这是一道反悔贪心的板题。

### 观察数据

发现 $A_i$、$B_i$ 都很小，所以可以考虑复杂度重心向它们倾斜。

具体来说，我们可以一单位一单位处理泥土。

### 初步思考

这道题考虑贪心。

先划分子问题：我们可以考虑一部分一部分满足。

这个一部分显然不应是任意区间，否则区间的枚举的复杂度都达到了 $O(n^2)$。

我们考虑特化这个区间的概念，即将区间改为前缀。

前缀数量少（仅 $O(n)$），转移方便（每次扩展一）。

由于前缀特殊的扩展方式，我们对每个前缀操作时，只需要考虑最后一堆泥土即可。

### 进一步

进一步，我们需要思考何时使用更改类操作，何时使用转移类操作。

显然，满足下式时使用转移（当前第 $i$ 堆）：

$$
z \times (i - j) \leq (x + y)
$$

套路的，我们应当区分未知部与已知部。

$$
zi - zj \leq (x + y)
$$

然后分类讨论

对于之前已经贪心处理过的 $j$，要向 $i$ 转移。

#### 当此堆需增加时：

本次转移的代价：

$$
zi - zj
$$

但是，由于之前处理过 $j$ ，已经计算出了当时的贪心最优解。

我们就可以消掉之前的代价。

所以，本次转移的真实代价：

$$
zi - zj - x = zi - (zj + x)
$$

然后，使用更改类操作代替转移，代价：

$$
x+y-x = y
$$

显然，我们要维护 $(zj + x)$。

所以一个大根堆维护即可。

所以对于此堆需增加的情况，我们使用以下策略（事实上，这里的策略还不完整）：

当 $zi - (zj + x) \leq y$ 时：

- 记录并删除大根堆顶。

- 利用公式计算答案。

当 $zi - (zj + x) > y$ 时：

- 直接更新答案。

#### 当此堆需减少时：

类似推导，得到两种情况的代价：

$$
zi - (zj + y)
$$

$$
x
$$

类似的比较。

另开一个大根堆。

推导完这种情况，我们就可以得出一个完整的策略：

即在前面策略下，互相维护两个大根堆。

具体看代码。

然后就没了。

这道题的核心思想就是通过“反悔”来使部分最优的贪心求出总体最优。

$q2$ 维护 $(zj + y)$（即减少）。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
priority_queue<int> q1, q2;
int n;
int a, b, x, y, z;
int ans;
signed main() {
    cin >> n >> x >> y >> z;
    for (int i = 1; i <= n; i++) {
        cin >> a >> b;
        if (a > b) {
            for (int j = 1; j <= a - b; j++) {
                if (q1.empty() || z * i - q1.top() > y) {
                    ans += y;
                    q2.push(z * i + y);
                } else {
                    int v = q1.top();
                    q1.pop();
                    //实质上就是反悔掉之前的操作，使用更优的操作
                    ans += z * i - v;
                    q2.push(2 * z * i - v);
                    //2 * z * i - v ： z*i + (z*i - v)
                    //此时(z*i - v)即为代价
                }
            }
        } else {
            for (int j = 1; j <= b - a; j++) {
                if (q2.empty() || z * i - q2.top() > x) {
                    ans += x;
                    q1.push(z * i + x);
                } else {
                    int v = q2.top();
                    q2.pop();
                    ans += z * i - v;
                    q1.push(2 * z * i - v);
                }
            }
        }
    }
    cout << ans;
}
```

---

## 作者：Cuxhin (赞：1)

# P2748 [USACO16OPEN] Landscaping P 思路推导题解

观察题目，为获得移动泥土的最小开销，我们需要同时考虑：移动泥土/增添泥土 两种策略。

观察数据范围，每个花坛的泥土不超过 10，而花坛数最多仅 100，这么小的数据启示我们一块块泥土处理，这是思路重要突破口，如果将几个泥土变成整体处理也可以，但是会比较麻烦。

如果只增添泥土，增添一块泥土代价显然是 $X$ 或者 $Y$。

难点在移动泥土，因为移动既可以往左边移动也可以向右边移动，我们最好可以单向遍历来处理泥土。

如果单向处理，例如从左到右，观察到：缺少泥土的花坛可以向左边多泥土的花坛拿泥土，多了泥土的花坛可以向左边缺泥土的花坛送泥土。

> 从花坛 $i$ 运送一单位泥土到花坛 $j$，费用为 $Z|i-j|$。

观察此处，得出移动一块泥土的代价为 $Z|i-j|$。

但是移动泥土跟增添泥土两个操作是冲突的。仅考虑一个操作都不是最优策略，我们需要同时考虑，进入反悔贪心。

只考虑增添泥土，我们可以得出处理一块泥土的价值。

考虑上移动泥土，如果第 $j$ 块花坛缺泥土，需要从前面拿泥土过来，那么去找删泥土的花坛，如果从第 $i$ 块花坛移动某一块泥土更优，令第 $i$ 块花坛的这块泥土所用的代价为 $w$。

$$\begin{array}{c}
Z(j-i)-w\le X\\
Zj-(w+Zi)\le X
\end{array}$$
把泥土拿走的式子是一样的。

> 注意这里用 $w$，而不是 $X$ 或 $Y$，是因为可能再次反悔，后面可能需要移动这个位置的泥土。

观察式子，$w+Zi$ 可以统一起来存储维护。

为了使反悔得到的结果最优，我们需要找最大的 $w+Zi$ 来减掉，来与 $X$ 比较获得更优策略。于是需要开大根堆来处理 $w+Zi$。

至此思路已经清晰，整理一下：
1. 从左到右遍历每个花坛的每块泥土。
2. 先用增减泥土的策略，即 $X$ 或者 $Y$。然后考虑移动泥土的策略，如果 $Zj - (w+Zi)$ 更优，就移动泥土。
3. 将 $(w+Zj)$ 存入堆维护，用来后面移动泥土策略使用。

另外，我们需要维护两个堆，分别存放 多余的泥土，缺少的泥土。
# 代码

注意开 `long long`

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
typedef long long ll;
inline int read(){
	int res=0,flag=1;
	char ch=getchar();
	while(!isdigit(ch))
		flag=(ch=='-')?-1:1,
		ch=getchar();
	while(isdigit(ch))
		res=(res<<3)+(res<<1)+(ch^48),
		ch=getchar();
	return res*flag;
}
inline void write(ll x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
ll n,x,y,z,a,b;
ll ans;
//vacancy_pq代表a<b花坛里面缺少的泥土
//surplus_pq代表a>b花坛里面盈余的泥土
priority_queue<ll> vacancy_pq,surplus_pq;
signed main(){
//	freopen("landscaping.in","r",stdin);
//	freopen("landscaping.out","w",stdout);
	n=read(),x=read(),y=read(),z=read();
	for(int i=1;i<=n;i++){
		a=read(),b=read();
		if(a>b)
			for(int j=1;j<=a-b;j++){
				//初始的代价
				int val=y;
				//比较移动代价
				if(!vacancy_pq.empty() and i*z-vacancy_pq.top()<val){
					val=i*z-vacancy_pq.top();
					vacancy_pq.pop();
				}
				//存放 w+zi
				surplus_pq.push(val+i*z);
				//统计答案
				ans+=val;
			}
		else
			for(int j=1;j<=b-a;j++){
				//初始的代价			
				int val=x;
				//比较移动代价
				if(!surplus_pq.empty() and i*z-surplus_pq.top()<val){
					val=i*z-surplus_pq.top();
					surplus_pq.pop();
				}
				//存放 w+zi
				vacancy_pq.push(val+i*z);
				//统计答案
				ans+=val;
			}
	}
	write(ans);//谢幕
	return 0;
}
/*
4
1
1
1
2
*/
```

---

## 作者：FeelGood (赞：1)

这是一道反悔贪心题。

先考虑只差一个单位泥土的做法。发现对于第三种操作比较难直接计算，我们可以假设 $i \ge j$，这样可以把 $Z|i - j|$ 变成 $Zi - Zj$，更方便计算。

我们开两个大根堆 $h_1$ 和 $h_2$，分别处理多泥土的情况和少泥土的情况。设 $h_1$ 的堆顶元素为 $v_1$，$h_2$ 的堆顶元素为 $v_2$。

如果多了 $1$ 个单位的泥土，我们可以花费 $Y$ 的代价把多的泥土移走，但我们未来有可能把多的泥土移到后面，那么我们就要在 $h_1$ 中插入反悔的代价 $Zi + Y$。

如果我们把这里多的泥土移到前面，并且希望代价尽可能小，我们可以从 $h_2$ 中选最大的值。那当前的代价就是 $Zi - v_2$。同时未来有可能会反悔当前的操作，所以我们要往 $h_1$ 中插入 $2Zi - v_2$。

我们在这两种情况中选代价较小的一个即可。

如果少了 $1$ 个泥土也是同理，我们可以花费 $X$ 的代价买入泥土，但我们可能从后面运送泥土过来，所以我们要在 $h_2$ 的堆中插入 $Zi + X$。

如果我们选择把前面多的泥土运到这里，那我们的代价就是 $Zi - v_1$。未来可能反悔，所以在 $h_2$ 中插入 $2Zi - v_1$。

同样的我们在这两种情况中选较小代价的一个即可。

对于差了多个泥土的情况，我们发现 $A_i$ 和 $B_i$ 的范围很小，所以我们可以直接暴力枚举，然后转化成差一个泥土的情况即可。

下面是代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define lll __int128

namespace FastRead
{
    void read() {}

    template <typename T1, typename ...T2>
    void read(T1 &n, T2 &...m)
    {
        T1 op = 1;
        char c;
        while (isdigit(c = getchar()) == false)
            if (c == '-') op = -1;
        n = c - '0';
        while (isdigit(c = getchar()))
            n = (n << 1) + (n << 3) + c - '0';
        n *= op;
        read(m...);
    }
}

using FastRead::read;

namespace Solve
{
    const int MaxN = 1e5;
    
    priority_queue<ll> q[2];
    
    void Sol()
    {
        int n, c[2], z;
        read(n, c[0], c[1], z);
        ll ans = 0;
        for (int i = 1; i <= n; ++i)
        {
            int a, b;
            read(a, b);
            int sd = a > b, len = abs(a - b);
            for (int j = 1; j <= len; ++j)
            {
                if (q[sd ^ 1].empty() == false && i * z - q[sd ^ 1].top() <= c[sd])
                    ans += i * z - q[sd ^ 1].top(), q[sd].emplace(i * z * 2 - q[sd ^ 1].top()), q[sd ^ 1].pop();
                else
                    ans += c[sd], q[sd].emplace(i * z + c[sd]);
            }
        }
        printf("%lld\n", ans);
    }
}

using Solve::Sol;

int main()
{
    Sol();
    return 0;
}
```

---

## 作者：cforrest (赞：0)

设 $f(i,v)$ 为处理完前 $i$ 堆泥土且结余 $v$ 单位泥土的最小成本。问题的答案就是 $f(n,0)$。

可以写出状态转移方程：

$$
f(i,v) = \min_w f(i-1,w)+|w|Z+h((b_i-a_i)-(w-v)),
$$

其中，

$$
h(\delta) = \max\{\delta,0\}X+\max\{-\delta,0\}Y
$$

是用于补足第 $i$ 堆泥土的亏空（或盈余）（即 $(b_i-a_i)-(w-v)$）的成本，而 $|w|Z$ 是将前一次剩余（或缺少）的土方搬到当前位置的新增成本。

方程只涉及分段线性的凸函数，因此考虑使用 slope trick。

在 $f(i-1,w)$ 的基础上：

-   加 $|w|Z$ 相当于在原点左侧的斜率都减去 $Z$，在原点右侧的斜率都加上 $Z$；
-   不考虑 $(b_i-a_i)$ 项，后面就是 $h(v-w)$，将它与 $f(i-1,w)+|w|Z$ 的和取 $w$ 的最小值，相当于做 Minkowski 和，结果就是将 $f(i-1,w)+|w|Z$ 的所有斜率（即差分）与 $-Y$ 取最大值，与 $X$ 取最小值；
-   最后，在得到的函数的基础上再加上 $b_i-a_i$ 项相当于将它向左平移 $b_i-a_i$ 的单位。

基于这些分析，只需要维护原点左右两侧离原点最近的几个斜率的值即可，事实上只需要两个栈。整体的操作用懒标记，左右移动只需要将栈顶的元素移动一下。

因为更远处的斜率一定为 $-Y$ 或 $X$，所以不必记录，当左侧或右侧的栈空了的时候直接补相应的值即可。

最后的答案是 $0$ 处的取值，所以在左右移动时需要更新答案。

复杂度是 $O(n\max\{a,b\})$ 的。

核心代码如下：

```cpp
int main() {
    int n;
    long long x, y, z;
    std::cin >> n >> x >> y >> z;
    std::stack<long long> neg, pos;
    long long lt = 0, rt = 0;
    long long res = 0;
    for (; n; --n) {
        int a, b;
        std::cin >> a >> b;
        lt -= z;
        rt += z;
        for (; b < a; ++b) {
            auto l = -y;
            if (!neg.empty()) {
                l = std::max(l, neg.top() + lt);
                neg.pop();
            }
            pos.emplace(l - rt);
            res -= l;
        }
        for (; b > a; --b) {
            auto r = x;
            if (!pos.empty()) {
                r = std::min(r, pos.top() + rt);
                pos.pop();
            }
            neg.emplace(r - lt);
            res += r;
        }
    }
    std::cout << res;
    return 0;
}
```

---

## 作者：wangliu (赞：0)

# 题目大意

调整 $n$ 个花坛中的土块数量，可以选择增减土块或者移动土块，对应不同的代价，计算最小的代价和。

# 题目思路

由于土块数极小，我们可以对每一块土块进行讨论，是选择增添还是从别的地方移动。但是移动土块会产生后效性，所以我们选择 **反悔贪心**。

反悔贪心：顾名思义，后面的贪心操作可能会覆盖前面的贪心操作。

在这道题里，我们可以从第 $1$ 个花坛开始讨论，对于第 $i$ 个花坛，假设缺少土块，可选的策略有两种：
- 直接买土块，此时代价为 $X$。
- 从之前的多出土块的花坛移动土块，代价为 $Z|i-j|$，同时应该撤回先前操作的代价 $V_j$，故总代价为 $Z|i-j|-V_j$。

显然 $i > j$，故最优解 $V_i = \min(X,Z(i-j)-V_j) = \min(X,iZ-(jZ+V_j))$。观察式子，其中和 $j$ 相关的只有 $jZ+V_j$。同理，对于多出土块的花坛，结论相同。

知道这个之后，后面就简单了。可以开两个大根堆分别维护缺少土块和多出土块的花坛的 $jZ+V_j$。

注意：计算缺少土块的花坛的代价需要从多出土块的大根堆中获取最大的 $jZ+V_j$，计算出的 $iZ+V_i$ 则需要存到缺少土块的大根堆中。

~~蒟蒻卡在这里了，代码根本没法调试，找了半天问题。~~

代码如下
```cpp
//洛谷非常重视学术诚信。抄袭、复制题解和代码，以达到刷 AC 率/AC 数量或其他目的的行为，在洛谷是严格禁止的，这将会导致您成为作弊者。
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n,x,y,z,ans;
priority_queue<int> more,les;

inline int read(){//快读
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}return x*f;
}

inline void print(int x){//快写
	if(x<0) {putchar('-');x=-x;}
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}

signed main(){
	n=read();x=read();y=read();z=read();
	for(int T=1;T<=n;T++){
		int a=read(),b=read();
		if(a>b){
			for(int i=1;i<=a-b;i++){//多出土块的情况
				int val=y;
				if(!les.empty() and z*T-les.top()<val){//判断两种决策哪种更优
					val=z*T-les.top();
					les.pop();
				}
				more.push(z*T+val);//把当前的决策存下来，留给后面做判断
				ans+=val;
			}
		}
		else{
			for(int i=1;i<=b-a;i++){//缺少土块的情况
				int val=x;
				if(!more.empty() and z*T-more.top()<val){
					val=z*T-more.top();
					more.pop();
				}
				les.push(z*T+val);
				ans+=val;
			}
		}
	}
	print(ans);
	return 0;
}
```

---

