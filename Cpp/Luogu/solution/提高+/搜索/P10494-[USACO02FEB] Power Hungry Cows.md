# [USACO02FEB] Power Hungry Cows

## 题目描述

FJ 的奶牛们希望能够快速计算整数幂 $P$（$1 \leq P \leq 20000$），但她们需要你的帮助。因为她们将要计算非常大的数的幂，所以她们只能保留两个工作变量来存储中间结果。

这两个工作变量中的第一个被初始化为正在计算幂的数字（表示为 $x$）；另一个被初始化为 $1$。奶牛们可以对任意一对工作变量进行乘法和除法运算，并将结果存储在任意一个工作变量中，但所有结果都存储为整数。

例如，如果她们想要计算 $x^{31}$，一种进行计算的方法是：

![](https://cdn.luogu.com.cn/upload/image_hosting/bfbznh12.png)

因此，$x^{31}$ 可以在六次操作中计算出来。给定要计算的幂和工作变量的数量，找出计算该幂所需的最少操作数。

## 样例 #1

### 输入

```
31```

### 输出

```
6```

# 题解

## 作者：wangbinfeng (赞：8)

已被打回两次，烦请告知具体不合规的位置，以便作者进行修改。

---


[![](https://img.shields.io/badge/题目-P10494_[USACO02FEB]_Power_Hungry_Cows-yellow)
![](https://img.shields.io/badge/难度-提高+/省选−-blue)
![](https://img.shields.io/badge/考点-搜索（BFS）-red)
![](https://img.shields.io/badge/题型-传统题-green)](https://www.luogu.com.cn/problem/P10494)
[![](https://img.shields.io/badge/作者-wangbinfeng(387009)-purple)](https://www.luogu.com.cn/user/387009)

------------
- 题解意义：这道题的原题空间限制是 30000KiB，所以必须用 ID-DFS。但是 luogu 里这道题的空间限制是 512.00MiB，所以用 BFS 的空间复杂度是没有问题的。鉴于这道题可以被作为是 ID-DFS 的模板题，建议还是跟着其他题解学一下 ID-DFS。那么为什么会有这个题解呢？因为我为了验证 BFS 可以通过本题，尝试了长达 $20$ 天，所以本题解分享方法，以免后来人重复浪费时间。
- 题意简述：有两个变量，其初值分别为 $x$ 和 $1$，请问这两个变量最少经过多少次乘或除操作，使得至少一个变量的值成为 $x^P$。
- 必备公式：$x^a\times x^b=x^{a+b},\frac{x^a}{x^b}=x^{a-b},x^0=1$。

------------

首先可以发现变量 $x$ 其实没啥用，因为乘除操作完全可以转换为对其指数加减操作，所以题目可以转化为两个数 $0,1$ 经过任意多操作得到 $P$。因为 $P\le2\times 10^4$，所以搜索即可。
对于状态 $(x,y)$，可以转移到 $
\begin{cases}
(x,x+x)\\(x,y+y)\\(x+x,y)\\(y+y,y)\\(x,x+y)\\(x+y,y)\\(x,\lvert x-y\rvert)\\(\lvert x-y\rvert,y)
\end{cases}$ 共计 $8$ 种状态，搜索一下。

设答案为 $ans$，则时间复杂度约为 $8^{ans}$，经测试 $ans\le20$，跑所有状态显然不可能完成。容易想到记忆化，不幸的是还是超时。

考虑到令 $A=\gcd(x,y)$，则 $x=\lambda_1A,y=\lambda_2 A$，那么他们凑出来的数将一定也只能是 $A$ 的倍数（也可以把 $\lambda$ 搞成零然后再找，但显然更劣）。那么如果发现若 $P\bmod\gcd(x,y)\neq0$，那么就可以直接剪枝。

现在 ID-DFS 已经可以 $\colorbox{green}{\color{white}{AC}}$ 了，但是 BFS 还是**有可能**会 $\colorbox{black}{\color{white}{TLE}}$，考虑继续卡常。由于每个人卡常的方法不尽相同，这里仅介绍我本人的卡常方法：
1. 手写队列，不要用 STL 的 `queue`，经测试可以节省 300 ms。
2. 手写 `gcd`，不要用 STL 的 `__gcd`。
3. 用 `bitset` 或 `bool` 数组，不要用 STL 的 `map/unordered_map`。

总结一下就是少用或不用 STL。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int p, cnt;
const int maxp = 2e4 + 9;
bitset<maxp * maxp * 5> vis;
const int M = 4e7 + 5, P = 4e7;
struct Node
{
    unsigned short x, y, dep;
} v[M];

int l = 1, r = 0;
#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)
#define ctz __builtin_ctz
int az, bz, z, t;
inline int gcd(int a, int b)
{
    if (!a || !b)
        return 0;
    az = ctz(a), bz = ctz(b), z = (az > bz) ? bz : az, t;
    b >>= bz;
    while (a)
        a >>= az, t = a - b, az = ctz(t), b = min(a, b), a = t < 0 ? -t : t;
    return b << z;
}
int x, y, dep;
inline int bfs()
{
    Node now = {1, 0, 0};
    for (v[++r] = now, (r == P) && (r = 0); 1; l++, (l == P + 1) && (l = 1))
    {
        cnt++;
        x = max(v[l].x, v[l].y), y = min(v[l].x, v[l].y), dep = v[l].dep;
        if (x == p || y == p)
        {
            cout << dep;
            return dep;
        }
        if (x > p * 2)
            continue;
        if (vis[x * p * 2 + y])
            continue;
        if (gcd(x, y) && p % gcd(x, y))
            continue;
        vis[x * p * 2 + y] = true;
        now.x = x * 2, now.y = y, now.dep = dep + 1, v[++r] = now, (r == P) && (r = 0);
        now.x = x * 2, now.y = x, now.dep = dep + 1, v[++r] = now, (r == P) && (r = 0);
        now.x = x, now.y = y * 2, now.dep = dep + 1, v[++r] = now, (r == P) && (r = 0);
        now.x = y, now.y = y * 2, now.dep = dep + 1, v[++r] = now, (r == P) && (r = 0);
        now.x = x + y, now.y = x, now.dep = dep + 1, v[++r] = now, (r == P) && (r = 0);
        now.x = x + y, now.y = y, now.dep = dep + 1, v[++r] = now, (r == P) && (r = 0);
        now.x = x - y, now.y = x, now.dep = dep + 1, v[++r] = now, (r == P) && (r = 0);
        now.x = x - y, now.y = y, now.dep = dep + 1, v[++r] = now, (r == P) && (r = 0);
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> p;
    bfs();
}
```

---

- 后记：
~~经过我本人的测试，其实 ID-DFS 和 BFS 的遍历节点数相近，为同一个数量级，且 BFS 遍历的节点数甚至会更小~~（UPD：经过第二次测试，发现结果与第一次测试结论不符，等待最终确定结果），不清楚为什么经过卡常的 BFS 算法会比 ID-DFS 慢了 $\frac{835ms}{18ms}\approx46.3$ 倍（对于第 #11 个测试点），希望有大佬可以告知原因。
- 鸣谢：感谢 [@C20252323tzy](https://www.luogu.com.cn/user/770611) 帮我卡常，题解中的代码也是这位大佬修改的，在此表示万分的感谢。
- 附录：关于代码运行时间的测试（[在这个链接进行测试，仅供参考](https://www.luogu.com.cn/problem/U463032)）：


|测试点|#1|#2|#3|#4|#5|#6|#7|#8|#9|#10|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|输入数据 $P$|1|2|5|10|100|1000|10000|11451|19997|20000|
|输出答案|0|1|3|4|8|12|16|17|18|17|
|ID-DFS 访问节点数量|1|3|12|14|356|51927|3139830|1408618|1764168|8069256|
|ID-DFS 代码运行时长|3ms|3ms|4ms|4ms|3ms|4ms|17ms|15ms|19ms|38ms|
|BFS 访问节点数量|1|2|44|102|2790|129328|6321222|10676462|24174998|16792582|
|BFS 代码运行时长|3ms|3ms|3ms|3ms|3ms|6ms|149ms|308ms|766ms|422ms|

---

## 作者：_ckx_ (赞：8)

## 题目大意
给定一个目标 $x^p$，一个初始 $x$（记为 $n$，方便后面描述），求最少进行多少次操作能得到目标。

定义一次操作为：将当前 $n^m$ 乘或除以之前已出现过的 $n^k$,使其变成 $n^{m+k}$ 或 $n^{m-k}$。

## 分析
先必须知道一个公式：
$$
n^x \cdot n^y=n^{x+y}
$$
接下来介绍一下 **IDDFS**。

其实就是给传统 DFS 加上一个深度限制，搜索时超过深度限制就立即停止搜索，适用于搜索树很大而答案在一个比较小的深度内。

显然，本题刚好符合这个条件。

很容易想到可以用一个数组来存下已出现过的 $n$ 的次方，再加一个剪枝。

## code1
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int p;
int mxdep;
const int P = 20010;
int a[P];

bool dfs(int x ,int dep)
{
	if (dep > mxdep) //如果超过就直接停止 
	{
		return false;
	}
	if (x == p) //搜到了，返回true 
	{
		return true;
	}
	if (x << (mxdep - dep) < p) //可行性剪枝：如果最快的倍增(mxdep - dep)次都到不了，那么直接返回false 
	{
		return false;
	}
	a[dep] = x; //记录下当前x的次方 
	for (int i = 0;i <= dep;i++)
	{
		if (dfs(x + a[i] ,dep + 1)) //乘上x^a[i] 
		{
			return true;
		}
		if (dfs(abs(x - a[i]) ,dep + 1)) //除以x^a[i]，注意要加绝对值，不然有可能会成负数 
		{
			return true;
		}
	}
	return false;
}

int main()
{
	scanf("%d",&p);
	
	while (!dfs(1 ,0))
	{
		mxdep++; //当前深度限制下搜不到结果，深度限制+1 
	}
	
	printf("%d\n",mxdep); //第一个满足的深度限制就是最小的答案 
	
	return 0;
}
```

结果发现愉快超时了，还要更优。

## 优化
我们可以省略掉数组 $a$，把记录次方的参数变成两个，记为 $x$ 和 $y$，然后搜下一层时对 $x$ 和 $y$ 多讨论几种情况（例如 $x$ 变为 $x+y$，就相当于 $n^x \cdot n^y$），也可以做到和数组同样的效果。

当然，这样做并不只是为了省空间，还有一个重要的剪枝：

当 $p \bmod \gcd(x,y) \ne 0$ 时，**可以直接返回 `false`**，为什么呢？

令 $a=\gcd(x,y)$，$x=a \cdot m_1$，$y=a \cdot m_2$，则 $x+y=a \cdot (m_1+m_2)$，$x-y=a \cdot (m_1-m_2)$，$x$ 和 $y$ 无论怎么加减，都有因数 $a$，而 $p$ 没有因数 $a$，所以永远不可能得到 $p$。

最后就是一些细节问题了（具体简单代码）。

## AC code
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int p;
int mxdep;

bool dfs(int x ,int y ,int dep)
{
	if (x < y) //防止后面x-y出现负数 
	{
		swap(x ,y);
	}
	if (dep >= mxdep)
	{
		if (x == p || y == p) //x和y有一个等于p就行了 
		{
			return true;
		}
		return false;
	}
	if (x << (mxdep - dep) < p) //剪枝1 
	{
		return false;
	}
	if (__gcd(x ,y) > 0 && p % __gcd(x ,y) != 0) //剪枝2 
	{
		return false;
	}
	
	//讨论多种情况 
	//乘 
	if (dfs(x * 2 ,y ,dep + 1)) return true;
	if (dfs(x * 2 ,x ,dep + 1)) return true;
	if (dfs(x ,y * 2 ,dep + 1)) return true;
	if (dfs(y ,y * 2 ,dep + 1)) return true;
	if (dfs(x + y ,x ,dep + 1)) return true;
	if (dfs(x + y ,y ,dep + 1)) return true;
	//除 
	if (dfs(x - y ,x ,dep + 1)) return true;
	if (dfs(x - y ,y ,dep + 1)) return true;
	return false;
}

int main()
{
	scanf("%d",&p);
	
	//和之前一样 
	while (!dfs(1 ,0 ,0))
	{
		mxdep++;
	}
	
	printf("%d\n",mxdep);
	
	return 0;
}
```

---

## 作者：PeppaPig_qwq (赞：6)

这道题可以用搜索来实现，我用的是迭代加深，也可以用 bfs 等算法。主要考虑剪枝。

- 首先，可以发现 $wv_1,wv_2$ 在 $k$ 轮操作后最大值就是 $wv_1$ 一直翻倍，最大值为 $2^{k}  \times{wv_1}$，因为只有 $wv_1$ 是 1，所以可以判断搜索时 $2^{lim-dep}$ 是否大于 $P$，小于的话就停止搜索。
- 还有，$wv_1 + wv_2, wv_1 - wv_2, wv_1 \times{wv_2},wv_1 \div 2,wv_2 \times{2},wv_2 \div 2,wv_1 \times{2}, wv_1 \div 2$ 都整除 $\gcd(wv_1,wv_2)$，所以可以判断 $\gcd(wv_1, wv_2)$ 是否为 $P$ 的因数。否的话退出搜索。

下面是代码：
```
#include <bits/stdc++.h>
using namespace std;

int lim, p, _pow[31];
bool flag = 0;

void dfs(int dep, int x, int y) {
    if (x < y)
        swap(x, y);
    if (dep == lim + 1) {
        if (x == p or y == p) {
            cout << dep - 1 << endl;
            exit(0);
        }
        return ;
    }
    if (gcd(x, y) and p % gcd(x, y) != 0)
        return ;
    if (x * _pow[lim - dep + 1] < p)
        return ;
    dep++;
    dfs(dep, x, y + x);
    dfs(dep, y + x, y);
    dfs(dep, x, x - y);
    dfs(dep, x - y, y);
    dfs(dep, x, x + x);
    dfs(dep, x + x, y);
    dfs(dep, x, y + y);
    dfs(dep, y + y, y);
}

int main() {
    _pow[0] = 1;
    for (int i = 1; i < 32; i++)
        _pow[i] = _pow[i - 1] * 2;
    cin >> p;
    for (lim = 0; !flag; lim++)
        dfs(1, 1, 0);
    return 0;
}
```

---

## 作者：Frielen (赞：3)

## 思路
读完题，我们不难发现此题中的 $x$ 是障眼法，我们其实只需要考虑两个数的幂之间的运算即可。因此，该题的题意等价于：**给定两个数 $1$ 和 $0$，两个数可以互相加减，最少计算多少次可以得到 $p$。**

为什么是加减呢？我们知道：

$$ x^n \times x^m = x^{n+m} $$

$$ x^n \div x^m = x^{n-m} $$

而我们计算的是幂，当然是加减啦。


## 代码分析
本题是一道显然的搜索。但使用 dfs 会由于深度太大而 TLE，使用 bfs 则会 MLE（如果你用了 bitset 就当我没说）。即使卡过此题评测，其效率也不够优秀。那么，我们能否将两者结合呢？这种算法就是著名的 IDDFS。

IDDFS 就是给定一个深度，然后在该深度内进行 dfs，既有 dfs 空间小的优点，又结合了 bfs 速度快的优点，用来解决此题是非常合适的。

但是此题如果只使用 IDDFS 而不优化的话，还是会导致 TLE。因此，我们要对 IDDFS 进行剪枝。

接下来，我们称两幂中较大的一项为 $x$，较小的一项为 $y$。IDDFS 限制的操作最大次数为 $Maxdep$，当前操作次数为 $dep$。



**优化 1：** 如果 $x^{Maxdep-dep} < p$，那么无需继续 IDDFS。

证明：容易证明，$x$ 最快增长的方式是倍增。连最快的增长方式都无法得到 $p$，就无需继续了。

**优化 2：** 如果 $ \gcd(x,y) \nmid p$，那么无需继续 IDDFS。

证明：感性理解应该不难接受，如果希望获得严谨的证明，请右转 [P4549 题解区](https://www.luogu.com.cn/problem/solution/P4549)。

于是我们可以开开心心的开始 IDDFS 了。

**AC Code 1**

```cpp
#include<bits/stdc++.h>
using namespace std;
int ansdep,p;
bool IDA(int x,int y,int dep){
	if(x<y) swap(x,y); //保证x不小于y
	if(dep==ansdep){ //到达设置深度
		if(x==p||y==p) return 1; //返回有解
		else return 0;
	}
	if(x<<(ansdep-dep)<p) return 0; //剪枝1
	if(__gcd(x,y)>0&&p%__gcd(x,y)>0) return 0; //剪枝2
	if(IDA(x*2,y,dep+1)) return 1;
	if(IDA(x*2,x,dep+1)) return 1;
	if(IDA(x-y,y,dep+1)) return 1;
	if(IDA(x+y,y,dep+1)) return 1;
	if(IDA(x-y,x,dep+1)) return 1;
	if(IDA(x,y*2,dep+1)) return 1;
	if(IDA(x,y+x,dep+1)) return 1;
	if(IDA(y,y*2,dep+1)) return 1; //枚举所有情况。由于x不小于y，因此不考虑x-y。
	return 0;
}
int main(){
	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
	cin>>p;
	while(!IDA(1,0,0)) //枚举最大深度
		++ansdep;
	cout<<ansdep;
	return 0;
}
```


再看一眼数据，诶，好像可以打表！

于是：

**[Code 2](https://www.luogu.com.cn/paste/nejc2kd3)（由于代码长度限制无法 AC，仅供娱乐！）**

注 1：为什么 IDDFS 每次增加深度都不保存上一层的结论，效率仍然优秀？因为每一次增加深度，新的节点数量会远超上一层的节点。就像此题，每层的 $1$ 个节点将拓展为 $8$ 个节点，即使有剪枝，也仍然远超上一层的节点数。因此，不记录结果对 IDDFS 影响不大，并且，IDDFS 还有自己独有的剪枝（即本题中的剪枝1），完全可以抵消了。

注 2：第一份代码通过了讨论区的 hack。

---

## 作者：ny_jerry2 (赞：1)

很显然爆搜不可行，所以这里采用迭代加深搜索。

迭代加深其实就是限制了搜索树的深度。因为有可能答案在右子树上较浅的位置，但你先搜索的左子树，导致半天都搜不出来，所以限制深度可以起到减少时间的作用。

搜索代码：
```
bool dfs(int u,int depth){
	if(depth>dep||u<0){
		return 0;
	}
	if(u==x){
		return 1;
	}
	if(u<<(dep-depth)<x){
		return 0;
	}
	if(u>>(dep-depth)>x){
		return 0;
	}
	a[depth]=u;//记录遍历到的次方
	for(int i=depth;~i;i--){
		if(dfs(u+a[i],depth+1)||dfs(u-a[i],depth+1)){
			return 1;
		}
	}//枚举
	return 0;
}
```

里面有三个剪枝：  

- 可行性剪枝 $1$
```
if(u<<(dep-depth)<x){
		return 0;
}//如果最快的倍增法都没办法达到，那不可能搜出答案
```
-  可行性剪枝 $2$
```
if(u>>(dep-depth)>x){
		return 0;
	}
```

- 玄学剪枝
```
for(int i=depth;~i;i--){
		if(dfs(u+a[i],depth+1)||dfs(u-a[i],depth+1)){
			return 1;
		}
	}//倒序枚举，具体为什么我也不知道
```

---

## 作者：AK_400 (赞：1)

首先：
$$
a^x\times a^y=a^{x+y}\\\frac{a^x}{a^y}=a^{x-y}
$$
于是题意转化为两个变量最初为 $0$ 和 $1$，问最少几加减操作可以得到 $P$。

可以使用迭代加深搜索，注意剪枝。

**声明：下文中 $mx$ 为最大深度，$dp$ 为当前深度， $x$ 和 $y$ 为两个变量。**

首先写个估价函数：最快的反复乘二也达不到 $P$ 时就可以直接返回。

即 $y\times 2^{mx-dp}<P$ 。 

其次，你发现 
$$
\gcd(x,y)\mid x+y\\
\gcd(x,y)\mid x-y\\
\gcd(x,y)\mid x+x
$$ 
于是如果  $\gcd(x,y)\nmid P$ 就可以返回。
# code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
bool got=0;
int gcd(int x,int y){
    return y?gcd(y,x%y):x;
}
void dfs(int x,int y,int mx,int dp){
    if(dp>=mx){
        if(x==n||y==n)got=1;
        return;
    }
    if(x<y)swap(x,y);
    if(x==y&&x==0)return;
    if(n%gcd(x,y))return;
    if((max(x,y)<<mx-dp)<n)return;
    dfs(x+y,y,mx,dp+1);
    if(got)return;
    dfs(x,x+y,mx,dp+1);
    if(got)return;
    dfs(x+x,y,mx,dp+1);
    if(got)return;
    dfs(x,x+x,mx,dp+1);
    if(got)return;
    dfs(x,y+y,mx,dp+1);
    if(got)return;
    dfs(y+y,y,mx,dp+1);
    if(got)return;
    dfs(x-y,y,mx,dp+1);
    if(got)return;
    dfs(x,x-y,mx,dp+1);
    return;
}
signed main(){
    cin>>n;
    for(int i=0;i<=n;i++){
        dfs(1,0,i,0);
        if(got){
            cout<<i;
            return 0;
        }
    }
    return 0;
}
```

---

## 作者：weilycoder (赞：1)

# 思路

题目描述让我们联想到快速幂，但显然套快速幂连样例都过不去。

推式子不好推，于是考虑搜索。

原题的空间限制只有 30000K（洛谷空间开大了），BFS 的状态可能存不下，我们考虑迭代加深。

每个状态显然不能直接存数，我们将指数存下即可，初始值变为 $(0,1)$。

> 注意到这实际上是在求 [$P$ 的最短加减链长度](https://oeis.org/A128998)

# 剪枝

裸的 IDFS 基本不可能过，考虑如何剪枝。

设当前变量为 $a,b(a\le b)$。

容易想到：

1. $(a,a)$ 一定不比 $(a,b)$ 优；
2. 除了 $(0,1)$，$(0,b)$ 一定不比 $(a,b)$ 优；
3. $a<0$ 时不优；
4. $b>2P$ 时不优。

另外，我们容易写出估价函数：

$$g(a,b)=\min\{k|2^k\cdot b\ge P\},$$

记当前深度为 $s$，$s+g(a,b)>limit$ 时回溯。

此外，由裴蜀定理，$(a,b)\nmid P$ 时无解。

最后，还有几个小优化：

+ 剪枝的第 4 条可以改成 $b>2^{\lfloor\log_2 P+1\rfloor}$ 时不优；
+ 使用 $g(0,1)$ 作为 $limit$ 的初值；
+ 使用快速幂计算次数做迭代加深的上界。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int p, mx ,step_max;

int gcd(int a, int b) {
  return b? gcd(b, a % b): a;
}

int qp(int b) {
  int cnt = 0;
  for (; b; b >>= 1) {
    if (b & 1) ++cnt;
    ++cnt;
  }
  return cnt;
}

bool dfs(int a, int b, int step) {
  if (a == p || b == p) return true;
  if (a == b) return false;
  if (a < b) swap(a, b); // a > b;
  if (b == 0 && a > 1) return false;
  if (p % gcd(a, b)) return false;
  if (a > mx) return false;
  if (step == step_max) return false;
  if (a << step_max - step < p) return false;
  if (dfs(a + a, b, step + 1)) return true;
  if (dfs(a + a, a, step + 1)) return true;
  if (dfs(a + b, b, step + 1)) return true;
  if (dfs(a + b, a, step + 1)) return true;
  if (dfs(b + b, b, step + 1)) return true;
  if (dfs(b + b, a, step + 1)) return true;
  if (dfs(a - b, b, step + 1)) return true;
  if (dfs(a - b, a, step + 1)) return true;
  return false;
}

int main() {
  cin >> p;
  mx = 1 << (32 - __builtin_clz(p));
  int r = qp(p);
  for (step_max = (31 - __builtin_clz(p)); step_max < r; ++step_max) {
    if (dfs(1, 0, 0)) {
      cout << step_max << "\n";
      return 0;
    }
  }
  cout << r << "\n";
  return 0;
}
```

---

## 作者：xixisuper (赞：1)

# P10494 [USACO02FEB] Power Hungry Cows 题解

一道好玩的搜索题。

本题解使用 **IDA*** 算法。

## 思路

前置芝士：乘方的基本运算，

$$a^x ⋅ a^y = a^{x+y}$$

其中 $x,y \in \mathbb{R}$。

所以我们只需要把指数存下来，对指数进行加减运算，那么我们就可以欢快的把它套入 bfs 的模板。

**但是**，这样做我们就会发现它超空间限制了。为什么会超空间限制呢？

我们把一个状态记为一个二元组 $( first , second )$。假设存在一个二元组 $(a,b)$，且满足 $a<b$，那么由这个状态进行一次操作后，可能会出现 $(a,b+b)$、$(b+b,b)$、$(a+a,b)$、$(a,a+a)$、$(a+b,b)$、$(a,a+b)$、$(b-a,b)$、$(a,b-a)$ 八种不同的转移情况，单次操作产生的情况数过多，导致将状态入队时队列过长，从而导致了 MLE 的发生。

如何解决这个问题？**IDdfs** （又称迭代加深）应运而生。我们不去使用 bfs 来搜索，而是使用 dfs，不过，我们要**限制搜索的深度，即搜到一定深度后不去再继续搜**。像这种限定搜索深度的 dfs 我们称其为 IDdfs。

详细的，我们最开始时限定搜索深度为 $1$，然后进行一次 dfs。**如果有解，就输出当前限定的深度；如果无解，那就把限定的深度加一，再进行一次 dfs。重复上述操作，直至有解为止**。

**但是**，这样做我们就会发现它超时了。我们考虑去给这个 dfs 进行剪枝或优化。

#### 优化一：将 IDdfs 改为 IDA* 算法。

所谓 A* 算法就是**把原搜索加上一个估价函数**，IDA* 就是把 IDdfs 上加一个估价函数。**估价函数是用于估计当前状态到目标状态的花费的估计值（该估计值一定小于实际值）**。

放在本题中，我们可以将状态 $(a,b)$ 的估价函数设计为满足 $P \leq b \times 2^k$ 的 $k$ 的最小非负整数值，因要使其增速最快，需要让其成指数倍增加。

#### 优化二：当且仅当 $\gcd(a,b) \mid P$ 时，才能通过二元组 $(a,b)$ 拓展到 $P$。

根据基础数论知识，有不定方程 $ax+by=P$ 有整数解时，当且仅当 $\gcd(a,b) \mid P$，而题目中的操作无非就是使多个 $a,b$ 相加减，与上述不定方程等效。

加上这两个优化后，本题就可以被愉快的 A 掉了。

## 代码

```cpp
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
ll mob;
inline ll gcd(ll a,ll b){
	if(!a&&!b) return 0;
	if(!b) return a;
	return gcd(b,a%b);
}
ll tims[60000];
void init(){
	for(ll i=1;i<60000;i++){
		ll ret=i,cnt=0;
		while(ret<mob) ret<<=1,cnt++;
		tims[i]=cnt;
	}
}
inline bool dfs(ll mner,ll mxer,ll step,ll dep){
	if(mob%gcd(mxer,mner)!=0) return 0;
	if(mxer+mner>=60000) return 0;
	if(step+tims[mxer]>dep) return 0;
	if(step>dep) return 0;
	if(mner==mob||mxer==mob) return 1;
	bool flag=0;
	ll tx,na,nb;
	//1
	tx=mxer+mner;
	
	na=min(mner,tx),nb=max(mner,tx);
	if(na!=mner||nb!=mxer) flag=dfs(na,nb,step+1,dep);
	if(flag) return 1;
	
	na=min(mxer,tx),nb=max(mxer,tx);
	if(na!=mner||nb!=mxer) flag=dfs(na,nb,step+1,dep);
	if(flag) return 1;
	//2
	tx=mxer+mxer;
	
	na=min(mner,tx),nb=max(mner,tx);
	if(na!=mner||nb!=mxer) flag=dfs(na,nb,step+1,dep);
	if(flag) return 1;
	
	na=min(mxer,tx),nb=max(mxer,tx);
	if(na!=mner||nb!=mxer) flag=dfs(na,nb,step+1,dep);
	if(flag) return 1;
	//3
	tx=mxer-mner;
	
	na=min(mner,tx),nb=max(mner,tx);
	if(na!=mner||nb!=mxer) flag=dfs(na,nb,step+1,dep);
	if(flag) return 1;
	
	na=min(mxer,tx),nb=max(mxer,tx);
	if(na!=mner||nb!=mxer) flag=dfs(na,nb,step+1,dep);
	if(flag) return 1;
	//4
	tx=mner+mner;
	
	na=min(mner,tx),nb=max(mner,tx);
	if(na!=mner||nb!=mxer) flag=dfs(na,nb,step+1,dep);
	if(flag) return 1;
	
	na=min(mxer,tx),nb=max(mxer,tx);
	if(na!=mner||nb!=mxer) flag=dfs(na,nb,step+1,dep);
	if(flag) return 1;
	return 0;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>mob;
	init();
	if(mob==0||mob==1){cout<<"0";return 0;}
	for(ll i=1;i<=31;i++){
		if(dfs(1,2,1,i)){
			cout<<i;
			return 0;
		}
	}
	return 0;
} 
```

2024.5.23 upd：根据审核意见修改 $\LaTeX$。

---

## 作者：xiao7_Mr_10_ (赞：0)

好的如你所见，这道很像快速幂的题实际上可以显然的暴力搜索，具体的分类讨论乘以还是除以哪个工作变量，把结果存在哪个工作变量。

显然上述情况都有两种分支，所以一共有八种不同方案。

注意到如果一直搜索的话会陷入死胡同里面，考虑迭代加深搜索。实际上就是枚举搜索最低深度，超过该深度就直接不进行搜索。

显然这玩意会超时，然后考虑剪枝。

显然可以可行性剪枝，按照最快的倍增扩展速度都扩展不了就没有必要搜索了。然后我们可以优化初始化，一开始按最优秀的倍增所得的答案为最深深度进行搜索，会省掉很多无用搜索。

然后再考虑数论的方向剪枝，显然当 $\gcd(x,y)$ 不是 $P$ 的因子时就不进行搜索，证明很好想，如果不是因子就凑不出来 $P$ 了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 
int n,dep;
inline void dfs(int x,int y,int step){
	if(x<y)swap(x,y);
	if (step >= dep){
		if (x == n||y == n){
			cout << step;
			exit(0);
		}
		return;
	}
	if(x<<(dep-step)<n)return;
	if(__gcd(x,y)&&n%__gcd(x,y)!=0)return;
	dfs(x*2ll,y,step+1);
	dfs(x*2ll,x,step+1);
	dfs(x,y*2ll,step+1);
	dfs(y,y*2ll,step+1);
	dfs(x+y,y,step+1);
	dfs(x+y,x,step+1);
	dfs(x-y,y,step+1);
	dfs(x-y,x,step+1);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	dep=max(0ll,(int)log2(n));
	for(;;dep++)dfs(1,0,0);
	return 0;
}
```

---

