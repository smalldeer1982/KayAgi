# Code For 1

## 题目描述

Jon fought bravely to rescue the wildlings who were attacked by the white-walkers at Hardhome. On his arrival, Sam tells him that he wants to go to Oldtown to train at the Citadel to become a maester, so he can return and take the deceased Aemon's place as maester of Castle Black. Jon agrees to Sam's proposal and Sam sets off his journey to the Citadel. However becoming a trainee at the Citadel is not a cakewalk and hence the maesters at the Citadel gave Sam a problem to test his eligibility.

Initially Sam has a list with a single element $ n $ . Then he has to perform certain operations on this list. In each operation Sam must remove any element $ x $ , such that $ x&gt;1 $ , from the list and insert at the same position ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF768B/465cdad41298994952ff82579429cb3d1de6dea4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF768B/42f87a6d55a7d4b8ea353aaf2fcb56c13744febb.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF768B/465cdad41298994952ff82579429cb3d1de6dea4.png) sequentially. He must continue with these operations until all the elements in the list are either $ 0 $ or $ 1 $ .

Now the masters want the total number of $ 1 $ s in the range $ l $ to $ r $ ( $ 1 $ -indexed). Sam wants to become a maester but unfortunately he cannot solve this problem. Can you help Sam to pass the eligibility test?

## 说明/提示

Consider first example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF768B/e9c535e642142fa233499539a19c390315a69ecc.png)

Elements on positions from $ 2 $ -nd to $ 5 $ -th in list is $ [1,1,1,1] $ . The number of ones is $ 4 $ .

For the second example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF768B/a34639e1edfe488c7c83f3ed3854d0edf4f7db1f.png)

Elements on positions from $ 3 $ -rd to $ 10 $ -th in list is $ [1,1,1,0,1,0,1,0] $ . The number of ones is $ 5 $ .

## 样例 #1

### 输入

```
7 2 5
```

### 输出

```
4
```

## 样例 #2

### 输入

```
10 3 10
```

### 输出

```
5
```

# 题解

## 作者：SBofGaySchool (赞：11)

我来一个特别特别暴力的递归吧，没有任何预处理或者优化，直接暴力干的那种。

### 1. 暴力思路的产生

观察题目可以发现 $0 \le r-l \le 10^5$，我们完全可以遍历 $l$ 到 $r$ 中的每一个数，求出其是不是 $1$，然后把答案加起来即可。

### 2. 递归实现暴力思路

我们可以编写一个函数 $f(x,p)$，表示初始的数为 $x$ 时序列中第 $p$ 个数是否是 $1$。由

$x$ 产生的数列分三部分：

- 由 $\lfloor x/2 \rfloor$ 产生的数列；
- 一个数，$x \bmod 2$；
- 由 $\lfloor x/2 \rfloor$ 产生的数列；

如果 $p$ 正好在这个序列的正中间，那么 $x \bmod 2$ 即为所求。

正中间的位置是什么？由 $x$ 产生的数列有多长？设由 $x$ 产生的数列长度为 $l(x)$，则 $l(x)=2 \times l(\lfloor x/2 \rfloor)+1$，观察或推导（这实际上是个简单的等比数列求和）即可发现 $l(x)=2^{k+1}-1$，其中 $k=x$ 在二进制下的位数，即 $k=\lfloor \log_2 x \rfloor$。由 $x$ 产生的数列中间的位置正好为 $2^{k}$。

如果 $p$ 不在这个序列的正中间，那么它一定是由 $\lfloor x/2 \rfloor$ 产生的数列中的某个数，递归求解即可。

由于对每个 $x$ 都需要求出 $k$，因此直接实现暴力算法的时间复杂度为 $N \log ^2N$。事实上我们不难将其优化为 $N log N$，只需要先处理出 $N$ 的 $k$ 值，然后在递归的过程中带上这一参数即可。

### 3. 暴力算法的直接代码实现

```c++
#include <iostream>
#include <cstdio>
using namespace std;
long long n, l, r;
long long ans;
long long calc(long long x, long long p)
{
    long long y = x, mid = 1;
    // 直接计算中间的数的位置，即2^k 
    while (y >> 1)
        y >>= 1, mid <<= 1;
    // 如果p落在左半部分，递归求解之 
    if (p < mid)
        return calc(x >> 1, p);
    // 右半部分同理 
    else if (p > mid)
        return calc(x >> 1, p - mid);
    // 否则即为中间的数，返回x mod 2 
    return x & 1;
}
int main()
{
    scanf("%lld %lld %lld", &n, &l, &r);
    // 暴力遍历每一个数，计算其是否为1 
    for (long long i = l; i <= r; i++)
        ans += calc(n, i);
    printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：Zeng_Yi_Hang (赞：7)

# 前言

古诗学习：

一头犁牛半块田，收也凭天，荒也凭天。

粗茶淡饭饱三餐，早也香甜，晚也香甜。

布衣得暖胜丝绵，长也可穿，短也可穿。

草屋茅舍有几间，行也安然，睡也安然。

雨过天晴驾小船，鱼在一边，酒在一边。

日上三竿犹在眠，不是神仙，胜是神仙。

# 省流：纯数学推公式

## 复杂度 $O( \log n)$

## 引理

本题要求我们拆出 $\lfloor\frac{n}{2}\rfloor,n\bmod 2,\lfloor\frac{n}{2}\rfloor$ 三个数，因为 $\lfloor\frac{n}{2}\rfloor=\lfloor\frac{n}{2}\rfloor$ 所以我们不难看出本题生成的答案树具有**对称性**，所以兄弟节点的**答案相同**。因此我们可以吧这个二叉树压缩为一个链，把 $n\bmod 2$ 装入链中。

## 图例

我们用 $n=7$ 举例

1. **我们先画出 $n=7$ 所生成的二叉树**

![](https://cdn.luogu.com.cn/upload/image_hosting/j88y5dtg.png)

2. **然后把它压缩为一个链进行存储**

![](https://cdn.luogu.com.cn/upload/image_hosting/i2bojhz8.png)

3. **我们把 $a_1$，$a_2$ 挪到 $a_3$ 层**

![](https://cdn.luogu.com.cn/upload/image_hosting/lkc43f60.png)

这时我们很容易看出 $[l,r]$ 内的 $1$ 的数量要**分层讨论**，因为不同层数的模数并不相同。所以**分层讨论**是有必要的。

---

# 位置分析

由于 $l,r$ 与当层节点的相对位置会对答案有影响，故接下来对它们的位置关系进行~~逆天~~分析。

## 引理

$l,r$ 的位置只会影响它们之间包含的当层节点个数，故 $l$ 的位置与 $l$ 右侧第一个节点（若 $l$ 与当层某个节点重合，则 $l$ 也需取到）是**等效**的。同时我们需要知道 $l$ 和 $r$ 的**相对距离**是不变的，所以 $l$ 左移的长度和 $r$ 是相同的。

## 位置处理如下

由于只需要考虑 $r$ 与 $l$ 右侧第一个节点（若 $l$ 与当层某个节点重合，则 $l$ 也需取到）的相对位置，故可视作当层 $l$ 右侧第一个节点左侧全部被删除。

现已知需要**整体左移**一部分，那么需要**左移**多少呢？

首先，当层左端第一个节点的左侧会存在一些空槽位（若为最底层则没有），通过观察我们不难看出，这些空槽位的数目与层数是有一定关系的。假设最下层的层数是 $1$，总层数是 $cnt$，由下往上正在处理第 $i$ 层，则当层前置空槽位的数目为 $2^{i-1}-1$，所以我们先把这部分删去，即整体左移 $2^{i-1}-1$ 个槽位。

然后此时当层就是以一个节点为开头的了，那么 $l$ 左侧会有整数个循环区间，那么当层的循环区间长度为 $2^i$，那么左移长度是不是就等于

$$
\lceil \frac{l-2^{i-1}+1}{2^i} \rceil \times 2^i
$$

错！！！

如果此时 $l$ 刚好与当层某一个节点**重合**的话，它向上取整后则会**多删去一个区间**，所以我们做一点小调整：

把 $l-1$ 之后再去做这个算式是不是就正确了？

所以这个时候左移的**总位数**即是

$$
\lceil \frac{l-2^{i-1}}{2^i} \rceil \times 2^i+2^{i-1}-1
$$

所以更新后的**区间长度**即为

$$
r-\lceil \frac{l-2^{i-1}}{2^i} \rceil \times 2^i-2^{i-1}+1
$$

那这个时候如果你已经完全理解上述意思的话，我们是不是就可以看这个区间里有多少个循环区间？（注意：不完全取到的区间也要算上，因为只算区间头部的那一个节点，所以我们**向上取整**）

所以我们的最终答案为

$$
ans=\sum^{cnt}_{i=1}{ \lceil \frac{r-\lceil \frac{l-2^{i-1}}{2^i} \rceil \times 2^i-2^{i-1}+1}{2^i} \rceil \times a_{cnt-i+1}}
$$

（由于 $a$ 数组是**自上而下**存储的，所以求和的时候应该是 $a_{cnt-i+1}$）

## 最后附上 AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,l,r,a[105],cnt;
signed main()
{
	cin>>n>>l>>r;
	while(n)
	{
		a[++cnt]=n%2;
		n/=2;
	}
	int ans=0;
	int d=1;
	for(int i=cnt;i>=1;i--)
	{
		d*=2;
		int a1=ceil(double((l-d/2)*1.0/d))*d;
		int a2=ceil(double((r-d/2+1-a1)*1.0/d));
		ans+=a2*a[i];
	}
	cout<<ans;
	return 0;
}
```

完结撒花！！！

---

## 作者：皎月半洒花 (赞：7)

个人 vp 或者打休闲场的习惯都是先开 B 抢一血~~但是没抢
到过~~然后再做别的。发现这题没题解正好水个经验。

不难发现最后会构成一棵共有 $2^k$ 个节点的分治树，其中 $k=\lceil\log_2 n\rceil$ 。但是这其中有很多部分是重复的。随便画一下图可以发现对于区间内所有的奇数位置都会是一样的结果，取决于最后 $n$ 不断除以 $2$ 下取整是 $0$ 还是 $1$ 。而对于偶数位置则是某些 $n'\mod 2$ 。发现这些偶数位置的深度可能会有不同，同一深度结果相同。于是就可以预处理出每个深度的答案。最终复杂度 $O((r-l)\log n)$ 。

```cpp

int cnt ;
int ans ;
int res1 ;
int hmf[N] ;
ll posv[N] ;
ll base[N] ;
ll n, l, r ;
 
int main(){
    cin >> n >> l >> r ;
    if (n == 1) return puts("1"), 0 ;
    ll m = n ; hmf[++ cnt] = m % 2 ;
    while (m / 2 > 1)
        m /= 2, hmf[++ cnt] = m % 2 ;
//    debug(hmf, 1, cnt) ;
    reverse(hmf + 1, hmf + cnt + 1) ;
    for (int i = 0 ; i <= 60 ; ++ i)
        posv[i] = 1ll << i ; res1 = m / 2 ;
    for (ll i = l ; i <= r ; ++ i){
        if (i & 1) ans += res1 ;
        else
            for (int j = cnt ; j ; -- j)
                if (i % posv[j] == 0) { ans += hmf[j] ; break ; }
//        debug(i, ' '), debug(ans) ;
    }
    cout << ans << '\n' ;
    return 0 ;
}
 
```

---

## 作者：Erotate (赞：3)

提供一种新的思路。

我们发现如果不考虑中间那个数，那么最后构成的分治树是一棵二叉树，而且对于每一个节点它的左右子树都是完全相同的，也就是具有对称性。

我们可以记录以每一层的节点为根节点的子树代表的序列所包含的数的个数以及 $1$ 的个数，不妨设为 $siz$ 和 $ans$，由于对称性，只需要记录一个子树即可。

```cpp
void dfs(int u,int dp){// u 为当前的数，dp 为当前的层数
	if(!u) return;
	if(u==1){
		siz[dp]=ans[dp]=1;
		dep=max(dp,dep);
		return;
	}
	dfs(u/2,dp+1);
	siz[dp]=siz[dp+1]*2+1;//中间的那个数也要统计
	ans[dp]=ans[dp+1]*2+u%2;
}
```

然后我们把查询拆成 $[1,l-1]$ 和 $[1,r]$ 两个部分，相减即答案。我们可以用一种类似于平衡树查询排名为第几的数的思想来统计前缀和，如果当前要查询的位置大于左子树的 $sz$，那就减掉 $sz$ 并加上左子树的答案 $ans$，去右子树里查询，否则的话就就到左子树去查询即可。

```cpp
int gtans(int x,int u){//x 为要查询的位置，u 为当前的数
	if(x==0) return 0;
	int res=0;
	for(int i=2;i<=dep;++i){//因为左右子树其实是相同的，所以这里可以直接用 for 实现，不用递归。dep 为最大的层数。
		if(x>siz[i]){
			res+=ans[i]+u%2;
			x-=siz[i]+1;//因为中间还有一个数，所以要加 1
			if(!x) return res;
		}
		if(i==dep) res++;
		u/=2;
	}
	return res;
}
```

---

## 作者：Erica_N_Contina (赞：2)

## 思路

作为一道华而不实的水题，我们现在来考虑我们怎么样去解决它。

首先假设 $n=2^{50}$，我们按照题目的操作可以画出一颗二叉树（忽略中间的 $n\bmod2$ 时）。那么我们可以发现这颗二叉树的深度最多不超过 $51$ 层。所以我们可以认为求出序列中某个特定位置的复杂度为 $O(\log n)$。那么现在好办了，$l,r$ 满足 $0\le r - l\le10^5$，我们可以暴力去查询序列中第 $q,q\in [l,r]$ 个位置的值，时间复杂度为 $O(n\log n)$。

**实现**

我们写有`dfs(int x,int p)`表示为计算数字 $x$ 分裂后的序列的第 $p$ 项的值。那么我们就可以这样设计我们的函数。

由于一个数可以分成 $3$ 个部分——$dfs(\lfloor\frac n2\rfloor),x\bmod 2,dfs(\lfloor\frac n2\rfloor)$。在这里我们需要找到的只有 $dfs(x/2)$ 生成的序列的长度。那么问题就变成了我们计算数字 $x$ 分裂后的序列的长度。

这里我们不用推式子，我们模拟一下分裂的过程。已知 $x→\lfloor\frac n2\rfloor$ 时序列长度会由 $l$ 变成 $2l+1$，那么我们就可以用一个 while 循环求出 $x$ 对应的 $l$ 了。

故 dfs 代码如下。



```C++
int dfs(int x,int p){
	int mid=1,t=x;
	while(t>>1){
		t>>=1;mid<<=1;
	}
	if(p<mid)return dfs(x>>1,p);
	else if(p==mid)return x%2;
	return dfs(x>>1,p-mid);
}
```


## 代码

```C++
/*////////ACACACACACACAC///////////
       . Code  by  Ntsc .
       . Earn knowledge .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define int long long
#define db double
#define rtn return
using namespace std;

const int N=1e5+5;
const int M=1e5;
const int Mod=1e5;
const int INF=1e5;

int n,m,p,q,T,s[N],l,r,ans;
int dfs(int x,int p){
	int mid=1,t=x;
	while(t>>1){
		t>>=1;mid<<=1;
	}
	if(p<mid)return dfs(x>>1,p);
	else if(p==mid)return x%2;
	return dfs(x>>1,p-mid);
}
signed main(){
	cin>>n>>l>>r;
	for(int i=l;i<=r;i++){
		ans+=dfs(n,i);
	}
	
	cout<<ans<<endl;
	return 0;
}


```




---

## 作者：Zq_water (赞：2)

一道分治题。

令 $f(x,k)$ 为以初始数为 $x$ 的结果第 $k$ 为是 $0$ 还是 $1$。

那么，$f$ 函数怎么计算呢。

我们发现当 $k$ 正好在数列的中间时，那么结果就是 $x \bmod 2$，否则就看 $k$ 在左边还是右边，接着递归左边或右边。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,l,r,ans;
int f(int x,int k){
	int t=x,mid=1;
	while(t>>1) t>>=1,mid<<=1;
	if(k<mid) return f(x>>1,k);
	if(k>mid) return f(x>>1,k-mid);
	return x%2==1;
}
signed main(){
	cin>>n>>l>>r;
	for(int i=l;i<=r;i++) ans+=f(n,i);
	cout<<ans;
	return 0;
}
```

---

## 作者：Escapism (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF768B)

一个有趣的，类似线段树的东西。

# 题意

将一个数 $n$，递归分拆为三个数 $\left\lfloor\dfrac{n}{2}\right\rfloor,n
\mod 2,\left\lfloor\dfrac{n}{2}\right\rfloor$，对于 $0$ 和 $1$ 不再向下递归分拆。

最后会形成一个 01 序列，问这个 01 序列的 $[l,r]$ 中有多少个 $1$。

# 思路

用类似线段树的方法做。

首先我们可以发现对于 $n$，它产生的序列长度为 $2^{f(n)+1}-1$，其中 $f(n)$ 是 $n$ 在二进制下的位数。

如果将整个向下递归分拆的过程看做一棵树，每个节点的三个儿子分别是 $\left\lfloor\dfrac{n}{2}\right\rfloor,n\mod 2,\left\lfloor\dfrac{n}{2}\right\rfloor$，然后我们就发现对于每一个节点，它都代表的是**它的子树中 $1$ 节点的个数**。这个东西和线段树十分相似，用类似的方法做就可以了，唯一的不同就是这棵树是从上往下构造的。

对于一个最终产生序列中 $[l,r]$ 位的节点，它的三个儿子分别代表最终产生的序列中的下标中的 $[l,\dfrac{l+r}{2}-1],\dfrac{l+r}{2},[\dfrac{l+r}{2}+1,r]$。中间的节点由于一定是 $0$ 或 $1$，不会再向下拓展，所以只代表一位。

当要查询的区间中包含左子节点的区间，那么向左递归；中间节点、右节点同理。如果某个节点恰好递归到这个节点所代表的的区间，直接返回这个节点的值。

# 代码

代码细节很多。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
 
long long n,l,r,x = 1,ans = 0;
void Solve(int tree,int l,int r,int lastl,int lastr,int d){
    long long l1 = lastl,mid = (lastl + lastr) / 2,r1 = lastr;
    if (l == l1 && r == r1){ //区间如果恰好匹配
        ans += tree;
        return;
    }
    if (l1 == r1){ //递归到了 01 节点，不在向下递归
        ans += tree % 2;
        return;
    }
    if(tree == 0) return; //子树大小为 0，不再递归
    if (l <= mid && mid <= r) ans += tree % 2; //加入中间节点
    long long nextree; //子节点的子树大小
    if (tree % 2 == 0) nextree = tree / 2; //子树大小要分类讨论
    else nextree = (tree - 1) / 2;
    if (l < mid) Solve(nextree,l,min(mid - 1,r),l1,mid - 1,d + 1); //包含左子树中的节点，向左子树递归
    if (r > mid) Solve(nextree,max(l,mid + 1),r,mid + 1,r1,d + 1); //包含右子树中的节点，向右子树递归
}
signed main(){
    cin>>n>>l>>r;
    long long x = 1;
    for (int i = 0;i <= 52;i++){
        if (n < x) break;
        x *= 2;
    }
    x--; //计算产生的序列中有多少位
    Solve(n,l,r,1,x,1);
    cout<<ans<<endl;
    return 0;
}
 
```

[AC Record](https://www.luogu.com.cn/record/119469807)

---

## 作者：pldzy (赞：1)

[传送门：B. Code For 1](https://codeforces.com/contest/768/problem/B)

像我这么菜的 Oier，考场上只想的出来类似模拟线段树的做法啦～

被暴力吊打（~~大哭~~）。此题解提供一种新做法做参考。

## Solution

### 1

首先我们发现一个给定的 $n$，我们是可以求出它最终化为的 01 串的长度。

设 $s_{lst}$ 为当前分解得到的串的长度，$x$ 为分解出的、用二进制表示的 01 “串”长度最大的一个数，$y$ 为长度最大的数的个数。

例如，当输入的 $n$ 为 10 时，二进制下表示为 1010，此时 $s_{lst}$ 为 4，$x$ 为 4, $y$ 为 1。

将 10 分解成 5，0，5，即二进制下的 101，0，101，此时 $s_{lst}$ 为 7，$x$ 为 3，$y$ 为 2。

进一步分解，2，1，2，0，2，1，2，即二进制下的 10，1，10，0，10，1，10，此时 $s_{lst}$ 为 11，$x$ 为 2，$y$ 为 4。

综上，我们可以得到：假设我们已有 $s_{lst},\ x,\ y$，想得到分解一次之后的状态的 $s_{now},\ x',\ y'$。

有：$s_{now}=((x-1)* 2+1) * y + (s_{lst}-x* y)$

其中 $((x-1)* 2+1)$ 是每一个长度为 $x$ 的数分解出来的新的三个数 二进制下 01 串拼起来的总长度。比如说 5（$(101)_2$）分解成 2，1，2，这三个数二进制下的 01 串拼起来就是 10110，长度为 5。

$(s_{lst}-x* y)$ 表示除去那些二进制表示下长度为 $x$ 的数，剩下的、值为 0 或 1 的数的个数。因为它们不会被再次分解，所以直接保留即可。

其余的：$x' \gets (x - 1),\ y' \gets (y * 2)$。这个不难理解。

一直计算出新的 $s$，直到 $x = 1$，说明此时每个数二进制表示下的长度都是 1 了，即每个数的值非 0 即 1，分解结束。

一顿操作下来，不会浪费多少时间（因为 $n$ 本身不超过 2 的 50 次方）。

### 2

建树部分。

我们现在有 $n=10$，把它分解后的状态拆成一个树：

节点编号：

````
  1
 / \
2   3
````

每个节点代表的权值：

````
  0
 / \
5   5
````

所代表的二进制下的数：

````
   0
 /   \
101  101
````

每个节点代表的（维护的）最终的 01 串的区间：

（10 分解到最后，01 串的长度为 15。）

````
     (1~15)
    /       \
（1～7） （9～15）
````

（8 去哪里了？1 号节点本身就代表着八号节点。）

在上面这么多图中，我们发现 2 号节点和 3 号节点其实是一模一样的，所以我们只需要建 2 号节点一个就可以了。

不难发现这颗树最后的深度就是 $n$ 在二进制表达下的 01 串的长度。

### 3

啊我们发现查询的最后结果就是该区间包含的数的总数量减去值为 0 的数的数量。

所以我们的树就是维护区间内值为 0 的数的数量。

查询的时候要注意如果查询范围包括了我们实际上没有建的右子树，我们要把它转化为查询左子树的对应区间。

## Code

注意特判 0！！！

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i, a, b) for(register int i = a; i <= b; ++i)
const int maxn = 55;
int n, tp;
int n2[maxn], tot;
int cnt;
int ans;
int x, y, s;
int ql, qr;
struct node{
	int l, r, val, num;
	int sum;
	int ch;
}t[10005];

inline int rd()
{
	int s = 0, x = 1;
	char ch = getchar();
	while(ch < '0' or ch > '9') {if(ch == '-') x = -1; ch = getchar();}
	while(ch >= '0' and ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return x * s;
}

inline int build(int l, int r)
{
	if(cnt == tot or l > r) return 0;
	int u = ++cnt;
	t[u].l = l, t[u].r = r;
	t[u].val = (n2[u] ? 0 : 1), t[u].num = l + r >> 1;
	t[u].ch = build(l, (l + r >> 1) - 1);
	t[u].sum = t[t[u].ch].sum * 2 + t[u].val;
	return u;
}

inline int query(int i, int l, int r)
{
	if(t[i].l >= l and t[i].r <= r) return t[i].sum;
	if(l > r) return 0;
	int ts = 0;
	if(t[i].num >= l and t[i].num <= r) ts = t[i].val;
	if(l < t[i].num) ts += query(t[i].ch, l, min(t[i].num - 1, r));
	if(r > t[i].num) 
	{
		int ll = max((long long)1, l - t[i].num), rr = r - t[i].num;
		ts += query(t[i].ch, ll, rr);
	}
	return ts;
}

signed main()
{
//	freopen("E:/in49.txt", "r", stdin);
	tp = n = rd();
	if(!n)
	{
		printf("0\n");
		return 0;
	}
	while(tp > 0) {n2[++tot] = tp % 2, tp /= 2;}
	s = x = tot, y = 1;
	while(x > 1) {s = ((x - 1) * 2 + 1) * y + s - x * y, x -= 1, y *= 2;}
	ql = rd(), qr = rd();
	build(1, s);
	ans = qr - ql + 1, ans -= query(1, ql, qr);
	printf("%lld\n", ans);
	return 0;
}
/*1125899906842624*/
```


------------
感谢阅读。

辛苦管理员审核，如有问题烦请指出。

---

## 作者：ys_kylin__ (赞：1)

这道题在考场上考了，当时没想出来，还去搞线段树。。发现根本没那么复杂。

我们可以考虑一种**分治**，也就是考虑左边，右边，与中间。分值的函数 $\operatorname{partition(x,i)}$ 代表初始值为 $x$ 时第 $i$ 个值为零还是为一，每一次判断左和右和中间，直到中间和 $i$ 相等为止。

贴上代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll partition(ll n,ll x){
    ll tmp=n,md=1;
    while(tmp/2>0) {
    	tmp/=2;
		md=md*2;//不断的操作
	}
    if(x<md) 
		return partition(n/2,x);//对于左边的考虑 
    if(x>md) 
		return partition(n/2,x-md);//对于右边的考虑 
    return n%2==1;
}
int main() {
	ll n=0,st=0,en=0,ans=0;
    scanf("%lld%lld%lld",&n,&st,&en);
    for(ll i=st;i<=en;i++)
		ans+=partition(n,i);
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Xhesika_Frost (赞：1)

题解好少我来一篇


这是一道分治的题，对于给出的数呢，它所能组成的长度是一定的，（上一位已经说的很清楚了）所以我们可以预先算出来后，在这个序列上进行分治（分成三部分）处理。我们只需要把他的左右两部分分开递归计算，然后把三部分的和加起来就行了


（我的做法区别在于并没有预处理，而是直接递归做的）

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
long long n,ans,l,r,lenght=1,a;
long long fz(long long ll ,long long rr,long long n){
	if(ll==rr)
	return n;
	long long mid=(ll+rr)>>1;
	long long anss=0;
	if(l<mid)
	anss+=fz(ll,mid-1,n>>1);
	if(r>mid)
	anss+=fz(mid+1,rr,n>>1);
	if(mid<=r&&mid>=l)
	anss+=(n%2);
	return anss;
}
int main(){
	cin>>n>>l>>r;
	long long k=log2(n)+1;
	long long temp=2;
	if(n>1)
	while(k){
		if(k%2)
		lenght*=temp;
		temp*=temp;
		k/=2;
	}
	else
	lenght=2;
	lenght--;
	cout<<fz(1,lenght,n);
	return 0;
}
```


---

## 作者：BreakPlus (赞：0)

[$\Large \text{CF768B Code For 1}$](https://www.luogu.com.cn/problem/CF768B)

### $\text{Describe}$

对于一个序列，每次将每个数 $x$ 分裂成 $\lfloor \dfrac{x}{2} \rfloor,x \bmod 2 ,\lfloor \dfrac{x}{2} \rfloor$ 直到序列中所有非负整数 $\le 1$，求 $l$ 和 $r$ 之间的 $1$ 的个数（$r-l\le10^5$）。

### $\text{Solution}$

写过线段树上二分的人都知道怎么做了吧……使用递归求解。

设 $f(n,x)$ 表示由 $n$ 这个数分裂后产生的第 $x$ 个数是多少。

设 $siz(x)$ 表示 $x$ 会分裂成多少个数，容易知道 $siz(x)=siz(\lfloor \dfrac{x}{2} \rfloor)\times 2+1$，并且 $x$ 被分裂成的第一个数和第三个数都会被分成 $siz(\lfloor \dfrac{x}{2} \rfloor)$ 个数。

讨论 $f(n,x)$。

1. 如果 $x \le siz(\lfloor \dfrac{x}{2} \rfloor)$ 则证明第 $x$ 个数是在第一个 $\lfloor \dfrac{x}{2} \rfloor$ 分裂而成的，$f(n,x)=f(\lfloor \dfrac{x}{2} \rfloor,x)$。
2. 如果 $x = siz(\lfloor \dfrac{x}{2} \rfloor)+1$ 则证明第 $x$ 个就是 $n \bmod 2$，因为正好在分裂的三个数的中间那个数，而且 $\le 1$ 。
3. 如果 $x > siz(\lfloor \dfrac{x}{2} \rfloor)+1$ 则证明第 $x$ 个数是在第三个 $\lfloor \dfrac{x}{2} \rfloor$ 分裂而成的，$x$ 需要减去前面 $x-siz(\lfloor \dfrac{x}{2} \rfloor)-1$ 个数。 $f(n,x)=f(\lfloor \dfrac{x}{2} \rfloor,x-siz(\lfloor \dfrac{x}{2} \rfloor)-1)$。

答案就是 $\sum \limits_{i=l}^r f(n,i)$ 。

时间复杂度： $\texttt{O}(n \log^2n)$



---

## 作者：hjfjwl (赞：0)

这道题我们会发现这个序列的所有奇数位都是 $1$，偶数位都是它的余数。我们先把基数为全部加起来后，计算一下整个序列的长度，在从中间开始向左右两边寻找的余数。

AC code:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int len;
int l,r;
int n;
int cal_len(int c)
{
    if(c / 2 <= 1)
    {
        return 3;
    }
    return cal_len(c >> 1) *2 + 1;
}//求他的长度
int calc(int num,int l,int r,int x)
{
    int mid = (l + r) / 2;
    if(mid == x)
    {
        return num % 2;
    }//如果目前是就返回余数
    if(mid > x)//在左边
    {
        return calc(num >> 1,l,mid - 1,x);
    }
    return calc(num >> 1,mid + 1,r,x);//在右边
}
signed main()
{
    scanf("%lld%lld%lld",&n,&l,&r);
    if(n == 0)//n等于0的情况
    {
        puts("0");
        return 0;
    }
    int tl = (l & 1 ? l :l + 1);
    int tr = (r & 1 ? r : r - 1);
    int ans = 0;
    for(int i = tl;i <= tr;i += 2)
    {
        ans++;
    }
    //奇数位
    len = cal_len(n);
    tl = (l & 1 ? l + 1 :l);
    tr = (r & 1 ? r - 1: r);
    for(int i = tl;i <= tr;i += 2)
    {
        ans += calc(n,1,len,i);
    }
    //偶数位
    printf("%d\n",ans);
    return 0;
}
```

---

