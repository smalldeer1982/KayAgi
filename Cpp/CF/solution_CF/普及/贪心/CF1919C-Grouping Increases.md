# Grouping Increases

## 题目描述

You are given an array $ a $ of size $ n $ . You will do the following process to calculate your penalty:

1. Split array $ a $ into two (possibly empty) subsequences $ ^\dagger $ $ s $ and $ t $ such that every element of $ a $ is either in $ s $ or $ t^\ddagger $ .
2. For an array $ b $ of size $ m $ , define the penalty $ p(b) $ of an array $ b $ as the number of indices $ i $ between $ 1 $ and $ m - 1 $ where $ b_i < b_{i + 1} $ .
3. The total penalty you will receive is $ p(s) + p(t) $ .

If you perform the above process optimally, find the minimum possible penalty you will receive.

 $ ^\dagger $ A sequence $ x $ is a subsequence of a sequence $ y $ if $ x $ can be obtained from $ y $ by the deletion of several (possibly, zero or all) elements.

 $ ^\ddagger $ Some valid ways to split array $ a=[3,1,4,1,5] $ into $ (s,t) $ are $ ([3,4,1,5],[1]) $ , $ ([1,1],[3,4,5]) $ and $ ([\,],[3,1,4,1,5]) $ while some invalid ways to split $ a $ are $ ([3,4,5],[1]) $ , $ ([3,1,4,1],[1,5]) $ and $ ([1,3,4],[5,1]) $ .

## 说明/提示

In the first test case, a possible way to split $ a $ is $ s=[2,4,5] $ and $ t=[1,3] $ . The penalty is $ p(s)+p(t)=2 + 1 =3 $ .

In the second test case, a possible way to split $ a $ is $ s=[8,3,1] $ and $ t=[2,1,7,4,3] $ . The penalty is $ p(s)+p(t)=0 + 1 =1 $ .

In the third test case, a possible way to split $ a $ is $ s=[\,] $ and $ t=[3,3,3,3,3] $ . The penalty is $ p(s)+p(t)=0 + 0 =0 $ .

## 样例 #1

### 输入

```
5
5
1 2 3 4 5
8
8 2 3 1 1 7 4 3
5
3 3 3 3 3
1
1
2
2 1```

### 输出

```
3
1
0
0
0```

# 题解

## 作者：2huk (赞：5)

[更好的阅读体验](https://www.cnblogs.com/2huk/p/18000885)。

> 给定一个长为 $n$ 的序列 $a$，你需要将该序列恰好分成两个子序列 $s,t$。定义一个长为 $m$ 的序列 $b$ 的代价为 $\displaystyle p(b)=\sum_{i=1}^{m-1}[b_i<b_{i+1}]$，求 $p(s)+p(t)$ 的最小值。每个测试点 $t$ 组测试用例。

思路贪心。

可以发现答案的贡献只与每相邻两个数有关，因此维护 $x, y$ 表示当前两个子序列的结尾数字。为了更一般性，令 $x \ge y$。

此时，对于一个新元素 $a_i$，我们要考虑将其放入哪个子序列后，而且我们希望**修改后 $x, y$ 的值尽量变大**，因为这会对后续造成更有利的影响。

此时共有三种情况：

- $a_i > x$：这意味着无论放在哪个子序列都会导致答案多一，但是显然将 $y \gets a_i$ 更优。因为这会使 $x, y$ 增大的尽量多。
- $a_i > y$：如果 $y \gets a_i$，那么答案会多一，显然不优。因此 $x \gets a_i$。
- $a_i \le y$：显然此时放在哪个子序列中答案都不会加一。但是这样修改后一定会让它们变小，所以我们选择 $y \gets a_i$，即让损失较小。

根据上述规则模拟即可。[代码](https://codeforces.com/contest/1919/submission/244344912)。

---

## 作者：juruo_zhanshen (赞：4)

# 明确题意
首先要注意这个词：**子序列**。

子序列：不连续。

字串 or 子数组：连续。

也就是说 $s$ 不一定是连续的一段。

# 代码框架
这是一个在线算法，对于每一个输入的 $x$，直接计算。

我们只需要考虑 $x$ 应该放在哪个子序列里。

- 定义两个整型变量 `last1` 和 `last2`，表示 $s$ 和 $t$ 的最后一项。

- 并且需要使 `last1` 始终小于 `last2`。在每次循环结束时都要判断。
- 在循环中，考虑 $x$ 应该放在哪里。

  + 如果 $x \le$ `last1` 则 $x$ 必定 $\le$ `last2`。那么需要考虑放在哪个里面。很显然不能放在 `last2` 里面，所以一定要放在 `last1` 里。
  + 如果 $x >$ `last2` 则 $x$ 必定 $>$ `last1`。还是要放在较小的 `last1` 里，因为这样一定是最优的，请读者自行思考。
  + 如果 `last1` $\le x \le$ `last2`，那么一定要放在较大的后面，这样可以减少一个。

经过具体分析，大概可以写出代码。

$\text{I }\color{green}{\text{Accepted}}$ $\text{This Water Problem. Did You Do It?}$

```cpp
#include <bits/stdc++.h>

using namespace std;
/*
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
    //freopen(".in", "r", stdin);
    //freopen(".out", "w", stdout);
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        int last1 = INT_MAX, last2 = INT_MAX;
        int ans = 0;
        for (int i = 1; i <= n; i++){
            int x;
            cin >> x;
            if (x <= last1)
                last1 = x;
            else if (x > last2)
                last1 = x, ans++;
            else
                last2 = x;
            if (last1 > last2) swap(last1, last2);
        }
        cout << ans << endl;
    }
    return 0;
}               /* ----------  end of function main  ---------- */
```

---

## 作者：panxz2009 (赞：3)

## 题意简述 

- 给定长度为 $n$ 的序列 $a$，你需要将该序列恰好分成两个子序列 $s,t$。
- 定义一个长为 $m$ 的序列 $b$ 的代价为 $\displaystyle p(b)=\sum_{i=1}^{m-1}[b_i<b_{i+1}]$。
- 求 $p(s)+p(t)$ 的最小值。

## 解题思路

因为要使得 $\displaystyle p(s)+p(t)=\sum_{i=1}^{lens-1}[s_i<s_{i+1}]+\sum_{i=1}^{lent-1}[t_i<t_{i+1}]$ 最小，所以要尽量使 $s$ 和 $t$ 呈单调不增，故**序列的最后一个数显然越大越好**（记住这句话），因为尾数越大，其他数能够加入此序列（且不产生任何代价）的机会就越多。

正因为要尽量使 $s$ 和 $t$ 变为一个具有单调性的序列，故事实上只需要记录两个子序列的最后一个数，这里不妨分别记为 $x$ 和 $y$，并设 $x \le y$，这样既减少了空间复杂度，代码编写也更加方便。

对于输入的 $a$，考虑对 $a$ 的大小进行分类讨论：

- 当 $a<x \le y$ 时，$a$ 应该放入 $s$ 序列中，这样不会带来任何代价。由上面的“**序列的最后一个数越大越好**”可知，$a$ 放入 $s$ 序列中相当于使 $s$ 序列的最后一个数变大，并且拉近两序列中最后一个数的距离。
- 当 $x<a \le y$ 时，$a$ 只能放入 $t$ 序列中，才不会带来任何代价。
- 当 $x \le y<a$ 时，$a$ 应该放入 $s$ 序列中，且**一定会带来代价**。同 $a<x \le y$ 时的情况一样，由“**序列的最后一个数越大越好**”可知，$a$ 放入 $s$ 序列中相当于保留住了 $t$ 序列的最后一个数（更大），这样一定更优。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f;
int n,x,y,a,res;
void solve() {
	scanf("%d",&n);
	x=y=INF;
	res=0;
	for(int i=1;i<=n;i++) {
		scanf("%d",&a);
		if(a<=x) x=a;
		else if(a<=y) y=a;
		else {
			x=a;
			res++;
			swap(x,y);
		}
	}
	printf("%d\n",res);
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--) solve();
	return 0;
}
```


---

## 作者：Shadow_T (赞：3)

### 题目大意

你需要把 $a$ 分成两个序列，使前面的小于后面的数量最小。

### 题目分析

超简单贪心，设两个变量 $s,t$ 表示 $s,t$ 序列的最后一个值。$s$ 始终大于 $t$。

对于每一个 $a_i$：

- 如果 $a_i \geq s,t$，那么把它给 $t$，因为 $t$ 比较小。把小的变大很明显比把大的变大更优，这样 $s,t$ 都会尽量大。

- 如果 $s\geq a_i>t$，那么只能把它给 $s$，才能避免一次代价。

- 如果 $s,t>a_i$，那么只能计算一次代价，且把它给比较小的 $t$。

- 对于每一次运算过后如果 $t>s$ 了，那么交换它们，保证正确性。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int a[maxn];
void solve()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	int s=1e9,t=1e9,z=0;
	for(int i=1;i<=n;i++)
	{
		if(t>=a[i]) t=a[i];
		else if(s>=a[i]) s=a[i];
		else t=a[i],z++;
		if(t>s) swap(s,t);
	}
	cout<<z<<"\n";
}
int main()
{
	int t;
	cin>>t;
	while(t--) solve();
}
```

---

## 作者：Shunpower (赞：2)

交个傻逼另解供后人唾弃。

上了一个多月 whk 跑回来打 CF，第一发正解写挂，愤怒重构掉大分。

## 思路

非常自然地，我们考虑 dp。

$f_{p,i,j}$ 表示目前只看 $a$ 序列第 $p$ 项及其前面，$s$ 序列最后一个数是 $a_i$，$t$ 序列最后一个数是 $a_j$ 的最小代价和。很明显这样定义状态非常浪费，因为 $i,j$ 总有一维等于 $p$，所以修改状态：

$f_{p,0/1,i}$ 表示目前只看 $a$ 序列第 $p$ 项及其前面，$0$ 表示 $a_p\in s$，$t$ 序列最后一个数是 $a_i$ 的最小代价和；$1$ 表示 $a_p\in t$，$s$ 序列最后一个数是 $a_i$ 的最小代价和。接下来考虑转移。

- 假设 $a_p$ 接在 $s$ 当中：
	- 如果 $a_{p-1}$ 也接在 $s$ 当中，那么 $f_{p,0,i}\gets \min\{f_{p-1,0,i}\}+[a_p>a_{p-1}]$。
   - 如果 $a_{p-1}$ 不接在 $s$ 当中，那么 $f_{p,0,p-1}\gets \min\{f_{p-1,1,i}+[a_p>a_i]\}$。
   
对于 $a_p$ 接在 $t$ 当中的转移几乎是一模一样的，只有 $0/1$ 上的区别。由于第二个转移出现了按照值域分段加 $1$ 转移的情况，所以我们还要修改状态，把第三维改为表示最后一个数，而非最后一个数的下标。于是最终的结果就是这样的：

$f_{p,0/1,i}$ 表示目前只看 $a$ 序列第 $p$ 项及其前面，$0$ 表示 $a_p\in s$，$t$ 序列最后一个数是 $i$ 的最小代价和；$1$ 表示 $a_p\in t$，$s$ 序列最后一个数是 $i$ 的最小代价和。

- 假设 $a_p$ 接在 $s$ 当中：
	- 如果 $a_{p-1}$ 也接在 $s$ 当中，那么 $f_{p,0,i}\gets \min\{f_{p-1,0,i}\}+[a_p>a_{p-1}]$。
   - 如果 $a_{p-1}$ 不接在 $s$ 当中，那么 $f_{p,0,a_{p-1}}\gets \min\limits_{i<a_p}\{f_{p-1,1,i}+1\}+\min\limits_{a_p\leqslant i}\{f_{p-1,1,i}\}$。
- 假设 $a_p$ 接在 $t$ 当中：
	- 如果 $a_{p-1}$ 也接在 $t$ 当中，那么 $f_{p,1,i}\gets \min\{f_{p-1,1,i}\}+[a_p>a_{p-1}]$。
   - 如果 $a_{p-1}$ 不接在 $t$ 当中，那么 $f_{p,1,a_{p-1}}\gets \min\limits_{i<a_p}\{f_{p-1,0,i}+1\}+\min\limits_{a_p\leqslant i}\{f_{p-1,0,i}\}$。
   
很明显可以先滚动数组，然后做线段树优化 dp。在线段树上维护区间 $\min$，支持全局加和单点修改即可。我写得比较蠢，直接支持了区间加，其实留个全局加标记应该就行了。

两棵线段树互相转移的时候需要注意先后覆盖的问题。

## 代码

```cpp
int n;
int a[N];
int dp1[N],dp2[N];
#define mid (l+r>>1)
struct Segment_Tree{
    int minn[N<<2],lzy[N<<2];
    il void pushup(int p,int l,int r){
        minn[p]=min(minn[p<<1],minn[p<<1|1]);
    }
    il void build(int p,int l,int r){
        minn[p]=0;
        lzy[p]=0;
        if(l==r){
            return;
        }
        build(p<<1,l,mid);
        build(p<<1|1,mid+1,r);
    }
    il void pushdown(int p,int l,int r){
        if(lzy[p]){
            minn[p<<1]+=lzy[p];
            minn[p<<1|1]+=lzy[p];
            lzy[p<<1]+=lzy[p];
            lzy[p<<1|1]+=lzy[p];
            lzy[p]=0;
        }
    }
    il void insert(int p,int l,int r,int d,int x){
        if(d<l||d>r){
            return;
        }
        if(l==r){
            minn[p]=min(minn[p],x);
            return;
        }
        pushdown(p,l,r);
        if(d<=mid) insert(p<<1,l,mid,d,x);
        else insert(p<<1|1,mid+1,r,d,x);
        pushup(p,l,r);
    }
    il void modify(int p,int l,int r,int ml,int mr,int x){
        if(ml<=l&&r<=mr){
            minn[p]+=x;
            lzy[p]+=x;
            return;
        }
        pushdown(p,l,r);
        if(ml<=mid) modify(p<<1,l,mid,ml,mr,x);
        if(mid<mr) modify(p<<1|1,mid+1,r,ml,mr,x);
        pushup(p,l,r);
    }
    il int query(int p,int l,int r,int ml,int mr){
        if(ml>mr){
            return 1e9;
        }
        if(ml<=l&&r<=mr){
            return minn[p];
        }
        pushdown(p,l,r);
        int ans=inf;
        if(ml<=mid) ans=min(ans,query(p<<1,l,mid,ml,mr));
        if(mid<mr) ans=min(ans,query(p<<1|1,mid+1,r,ml,mr));
        return ans;
    }
} T1,T2;
#undef mid
void solve(){
    cin>>n;
    fr1(i,1,n){
        cin>>a[i];
    }
    a[0]=inf;
    T1.build(1,1,n);
    T2.build(1,1,n);
    fr1(i,1,n){
        int x=T1.query(1,1,n,1,a[i]-1),y=T1.query(1,1,n,a[i],n);
        T1.modify(1,1,n,1,n,(a[i]>a[i-1]));
        int minn=min(T2.query(1,1,n,1,a[i]-1)+1,T2.query(1,1,n,a[i],n));
        T1.insert(1,1,n,a[i-1],minn);
        T2.modify(1,1,n,1,n,(a[i]>a[i-1]));
        minn=min(x+1,y);
        T2.insert(1,1,n,a[i-1],minn);
    }
    cout<<min(T1.query(1,1,n,1,n),T2.query(1,1,n,1,n))<<'\n';
}
```

[AC Record](https://codeforces.com/contest/1919/submission/240560272)

---

## 作者：Luzhuoyuan (赞：2)

### 题目链接

[[to Luogu]](https://www.luogu.com.cn/problem/CF1919C) [[to Codeforces]](https://codeforces.com/contest/1919/problem/C)

### 题意简述

给定一个长为 $n$ 的序列 $a$，你需要将该序列恰好分成两个子序列 $s,t$。定义一个长为 $m$ 的序列 $b$ 的代价为 $\displaystyle p(b)=\sum_{i=1}^{m-1}[b_i<b_{i+1}]$，求 $p(s)+p(t)$ 的最小值。每个测试点 $t$ 组测试用例。

$$1\le t\le 10^4;1\le n,\sum n\le 2\cdot 10^5;1\le a_i\le n$$

### 做法

考虑贪心。把 $a$ 中从左至右每一项加入 $s,t$，那么不会产生代价的前提是 $a_i$ 小于等于加入的子序列的末项，所以我们维护 $x,y$ 表示目前 $s,t$ 的最后一项的值，最初 $x,y$ 赋值为正无穷。我们钦定 $x\le y$，那么处理 $a_i$ 时会有以下情况：

- $a_i\le x$：此时 $a_i$ 可以接在 $x,y$ 的后面，由于 $x,y$ 会变化，我们希望接完的代价尽量小，即 $x,y$ 减小的值尽量小。所以我们贪心地将 $a_i$ 接在 $x$ 后面，更新 $x$ 的值。
- $x<a_i\le y$：此时要尽量避免产生代价，$a_i$ 只能接在 $y$ 后面。
- $a_i>y$：此时代价增加是不可避免的，我们希望让代价带来的利益最大化，也就是让 $x,y$ 增加的值尽量大。所以我们贪心地将 $a_i$ 接在 $x$ 后面，更新 $x$ 的值并交换 $x,y$，同时代价加一。

简单模拟过程即可。时间复杂度 $O(n)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int T,n,a;
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
signed main(){
	T=read();
	while(T--){
		n=read();
		int x=1e9,y=1e9,ans=0;
		for(int i=1;i<=n;i++){
			a=read();
			if(a<=x)x=a;
			else if(a<=y)y=a;
			else x=a,ans++,swap(x,y);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

（逃

---

## 作者：User_Unauthorized (赞：1)

考虑维护出当前的两个子序列，然后贪心的选择将当前元素放入哪个子序列中。

发现决策只与两个子序列的末尾元素和当前元素有关，不妨设两个子序列末尾元素分别为 $x, y$，并且有 $x \le y$。

- 若 $a_i \le x$，那么无论将 $a_i$ 放入哪个子序列，均不会产生代价，为了使得后续可以插入的元素范围更大，选择将 $a_i$ 放入 $x$ 所在的子序列中。

- 若 $y < a_i$，那么无论将 $a_i$ 放入哪个子序列，均会产生代价，为了使得后续可以插入的元素范围更大，选择将 $a_i$ 放入 $x$ 所在的子序列中。

- 若 $x \le a_i < y$，那么若将 $a_i$ 插入 $x$ 所在的子序列中，会产生代价，而将 $a_i$ 插入 $y$ 所在的子序列中不会产生代价。不妨假设我们在插入剩余 $a_{i + 1}, \cdots, a_n$ 的过程中均采取同一种决策，那么可以发现若插入 $x$ 所在的子序列中的方案优于插入 $y$ 所在的子序列中的方案，那么在插入该元素后，两个子序列的末尾元素相同。又因为在这之前插入 $x$ 所在的子序列中的方案多一点代价，因此无论如何插入 $y$ 所在的子序列中不劣于插入 $x$ 所在的子序列中的方案。因此，我们可以在插入 $a_i$ 时，选择将 $a_i$ 插入 $y$ 所在的子序列中。

---

## 作者：yhylivedream (赞：1)

## 题目描述

给定一个长为 $n$ 的序列 $a$，你需要将该序列恰好分成两个子序列 $s,t$。定义一个长为 $m$ 的序列 $b$ 的代价为 $\displaystyle p(b)=\sum_{i=1}^{m-1}[b_i<b_{i+1}]$，求 $p(s)+p(t)$ 的最小值。每个测试点 $t$ 组测试用例。

## 分析

考虑每加入一个数到 $s$ 或 $t$ 里，每个数的贡献只跟 $s$ 或 $t$ 里最后一个数有关，所以可以记录 $q,p$ 为 $s$ 的 $t$ 末尾。

接下来考虑贪心：

- 如果 $a_i > q$，且 $a_i > p$，此时无论如何贡献都得是 $1$，那么为了让后面数的贡献尽可能小，所以得插入到 $q,p$ 小的序列里。

- 如果 $a_i\le q$，且 $a_i\le p$，那么为了让后面数的贡献尽可能小，所以得插入到 $q,p$ 小的序列里，跟上面同理。

- 如果 $a_i$ 大于一方，小于等于另一方，那么则插到小于等于的序列里。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2 * 1e5 + 5;
int T, n, a[N], q, p, ans;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	for(cin >> T; T; T --){
		cin >> n;
		for(int i = 1; i <= n; i ++){
			cin >> a[i];
		}
		ans = 0, q = p = 1e9;
		for(int i = 1; i <= n; i ++){
			if(a[i] > q && a[i] > p){
				ans ++;
				(q < p ? q = a[i] : p = a[i]);
			}else if(a[i] <= q && a[i] <= p){
				(q < p ? q = a[i] : p = a[i]);
			}else{
				if(a[i] > q && a[i] <= p){
					p = a[i];
				}else{
					q = a[i];
				}
			}
		}
		cout << ans << "\n";
	}
	return 0;
}
```


---

## 作者：xz001 (赞：0)

~~由题目标签得需要贪心~~

这道题我们可以贪心。首先我们维护每个子序列的最后一个值，然后对于每个元素，如果这个元素小于等于任意一个子序列的最后一个值，就把其中小的设为这个元素，以减少损失。如果小于等于其中一个，那么肯定是把小于等于的设为这个元素。若都大于，则将两个子序列的末尾值中较小的设为这个值，以便抗击以后的元素，贡献加一。最后输出即可。

代码如下：

```cpp
/*
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
*/
#include<bits/stdc++.h>

using namespace std;

#define re			register
#define int			long long
#define fi			first
#define se			second
#define swap(a, b) 	a ^= b, b ^= a, a ^= b
#define pb 			push_back
#define all(x)		x.begin(), x.end()
#define max(a, b)	(a > b ? a : b)
#define min(a, b)	(a < b ? a : b)
#define il			inline
#define abs(x)		((x ^ (x >> 63)) - (x >> 63))

typedef pair<int, int> PII;

const int N = 1e6 + 10;
const int M = 1e6 + 10;
const int INF = 1e18, P = 998244353;
const double eps = 1e-6;

il int  read() { re int x = 0; re bool f = true; re char c = getchar(); while (c < 48 || c > 57) { if (c == '-') f = false; c = getchar(); } while (c >= 48 && c <= 57) x = (x << 3) + (x << 1) + c - 48, c = getchar(); return f ? x : -x; }
il void write(int x) { if (x < 0) putchar('-'), x = -x; if (x > 9) write(x / 10); putchar(x % 10 + 48); }
il void wel(int x) { write(x), putchar('\n'); }
il void wsp(int x) { write(x), putchar(' '); }

int t, n, a[N];

signed main() {
    cin >> t;
    while (t -- ) {
    	cin >> n;
    	for (int i = 1; i <= n; ++ i) cin >> a[i];
    	int l = 1e18, r = 1e18, cnt = 0;
    	for (int i = 1; i <= n; ++ i) {
    		if (a[i] <= l && a[i] <= r) {
    			if (l < r) l = a[i];
    			else r = a[i];
			} else if (a[i] <= l) {
				l = a[i];
			} else if (a[i] <= r) {
				r = a[i];
			} else {
				++ cnt;
				if (l < r) l = a[i];
				else r = a[i];
			}
		}
		cout << cnt << endl;
	}
    return 0;
}


```

---

## 作者：hh弟中弟 (赞：0)

我们考虑直接维护两个序列。  
扫描整个序列，不难发现我们每一步的贡献取决于当前的数和两个序列末尾的数。考虑贪心。  
设第一个序列末尾的数为 $x$，第二个序列末尾的数为 $y$，当前决策数为 $k$，有以下情况。
- 当 $k\le x$ 和 $k\le y$ 时，此时无论我们放入哪个序列，这一步的贡献都是 $0$，但是我们想要每个序列选择的余地最多，也就是让末尾的数尽量大，所以我们放入末尾数较小的那个序列中。
- 当 $x<k$ 和 $y<k$ 时，此时无论放入哪个序列，贡献都为 $1$，同理放入末尾数较小的序列中。
- 当 $y<k\le x$ 或 $x<k\le y$，也就是当前数位于两个末尾数之间时。我们选择插入没有贡献的序列。因为我们无论怎样插入，以后的情况都是一样的，所以需要这一步没有贡献。

直接拿两个栈维护即可，开始时第一个数先随便插入一个序列，然后将在另一个序列中插入一个无穷大即可，因为另一个序列为空，第一步一定没有贡献，所以相当于末尾是一个无穷大的数。  
代码如下：
```cpp
#include<bits/stdc++.h>
inline int read(){
	char ch=getchar();int x=0,f=1;
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
const int N=2e5+10;
int a[N];
std::stack<int>l,r;
int main(){
	// freopen("in.in","r",stdin);freopen("out.out","w",stdout);
	int T=read();
	while(T--){
		int n=read();int ans=0;
		for(int i=1;i<=n;++i)a[i]=read();
		l.push(a[1]);r.push(int(1e9));
		for(int i=2;i<=n;++i){
			int x=a[i];
			int ll=l.top(),rr=r.top();
			if(x<=ll&&x<=rr){
				if(ll<=rr)l.push(x);
				else r.push(x);
			}
			if(x<=ll&&x>rr)l.push(x);
			if(x>ll&&x<=rr)r.push(x);
			if(x>ll&&x>rr){
				if(ll<=rr)l.push(x);
				else r.push(x);
				ans++;
			}
		}
		std::cout<<ans<<'\n';
	}
}

```


---

## 作者：LYJ_B_O_Creation (赞：0)

## 题目思路：

显然可以用贪心。由于代价只会有相邻两个数产生，所以是无后效性的，保证当前状态最优即可。显然可以记录两个序列当前的最后一个数字，对于当前的数，只需考虑放到哪即可。

+ 如果一个能放一个不能放，那么放到能放的那里一定更有
+ 如果两个都能放，最后一个数字大的那个能延续的可能性更大（比它小的数更多），长远考虑，放较小的序列里。
+ 如果两个都不能放，与上面同理，也是放到最后一个数字较小的序列里，并把答案加 $1$。

## 题目代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n , x , ans = 0;
	int num1 = 0 , num2 = 0;
    int T;
    cin >> T;
    while(T--)
    {
        ans = 0;
        num1 = num2 = 2e5 + 10;
        cin >> n;
        for(int i = 1;i <= n;i++)
        {
            cin >> x;
            if(x <= num1 && x > num2) num1 = x;
            else if(x <= num2 && x > num1) num2 = x;
            else if(x <= num1 && x <= num2)
            {
                if(num1 < num2) num1 = x;
                else num2 = x;
            }
            else
            {
                ans++; 
                if(num1 < num2) num1 = x;
                else num2 = x;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```
特别感谢 @[zhangxiao666](https://www.luogu.com.cn/user/742017#main) 的帮助

---

## 作者：Cute__yhb (赞：0)

## 思路
看成两个栈，维护栈顶。

从数组 $a$ 中从前到后遍历元素。

- 如果 $a_{i}$ 不大于最小的栈顶，那么不会对答案产生贡献，贪心的放到栈顶较小的栈中。

- 如果 $a_{i}$ 大于最小的栈顶但不大于另一个，那么也不会对答案产生贡献，放到栈顶较大的栈中。

- 如果 $a_{i}$ 大于最大的栈顶，会对答案产生贡献，放到栈顶较小的栈中。

## 代码
```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
int t,n,a[200005],topa,topb;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		topa=INF;
		topb=INF;
		int ans=0;
		for(int i=1;i<=n;i++){
			if(a[i]<=min(topa,topb)){//第一种情况
				if(min(topa,topb)==topa){
					topa=a[i];
				}else{
					topb=a[i];
				}
			}
			else if(a[i]>min(topa,topb)&&a[i]<=max(topa,topb)){//第二种
				if(min(topa,topb)==topa){
					topb=a[i];
				}else{
					topa=a[i];
				}
			}else{//最后一种
				ans++;//计数
				if(min(topa,topb)==topa){
					topa=a[i];
				}else{
					topb=a[i];
				}
			}
		}
		cout<<ans<<endl;
	}
    return 0;
}
```


---

## 作者：yyrwlj (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1919C)

## 题意简述

把一个序列分成两个子序列，使两个子序列中前一个数小于后一个数的情况最少，求出这个最小值。

## 思路

可以想象成有两个栈，要加入一个新的数。

若两个栈的栈顶元素全部小于当前数，那最终答案就只能加一，然后将当前数放到栈顶元素更小的那个栈。

若只有一个栈的栈顶元素大于等于当前数，那就把数放到那个栈里。

若两个栈的栈顶元素都大于等于当前数，那肯定要放到栈顶元素更小的那个栈里。

### 证明为什么要放到栈顶元素更小的那个栈

设 $s1$ 是栈顶元素更小的栈的栈顶，$s2$ 是栈顶元素更大的栈的栈顶，当前数为 $a$，下一个数为 $b$。

按照上面第三种情况，有 $a \le s1 \le s2$。

若 $s1 < b \le s2$，那么只有放到 $s2$ 的后面才能使最终答案不加一。若当初 $a$ 替换了 $s2$，有 $a \le s1 < b$，无论放到哪个栈都会使最终答案加一。

## Code

```cpp
#include <iostream>
using namespace std;
const int N = 200005;
int a[N];
void work()
{
    int n;
    scanf("%d", &n);
    for (int i=1;i<=n;i++)
        scanf("%d", &a[i]);
    int s1 = a[1], s2 = 2e9, ans = 0;
    for (int i=2;i<=n;i++)
    {
        if (s1 > s2)
        {
            if (a[i] <= s2)
                s2 = a[i];
            else if (a[i] <= s1)
                s1 = a[i];
            else
            {
                ans ++;
                s2 = a[i];
            }
        }
        else
        {
            if (a[i] <= s1)
                s1 = a[i];
            else if (a[i] <= s2)
                s2 = a[i];
            else
            {
                ans ++;
                s1 = a[i];
            }
        }
    }
    printf("%d\n", ans);
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
        work();
    return 0;
}
```

---

## 作者：Cynops (赞：0)

我们贪心的想，
放在当前尾巴较小的序列尾端可以让后面能放的数字变多。

准备两个序列 $s,t$，从头开始一个一个放，当考虑到 $a_i$ 放在哪里时有 $2$ 种情况：（能放指的是不会增加贡献）

1. 两个都能/不能放

使用贪心策略。

2. 只能放一个

放在那个后面即可。

容易发现这是最优的，时间复杂度 $O(n)$，[代码](https://codeforces.com/contest/1919/submission/240551829)。

---

## 作者：kczw (赞：0)

# 题意简述
一共 $t$ 组数据。

对于每组数据，给定一个长为 $n$ 的序列 $a$，把它分成两个序列（元素的相对位置不变），最小化两个序列中**相邻**两数左边数比右边数小的情况的个数。

对于每组数据，输出最小的两个序列中相邻两数左边数比右边数小的情况的个数。
# 思路
这个很明显是贪心的思路。

首先，我们可以假定有两个序列。于是将原长为 $n$ 的 $a$ 序列分成两个序列的操作就可以转换为遍历 $a$ 并且每次把遍历到的元素放入其中一个序列中的操作了。

现在，需要思考的就仅仅是贪心的策略了。

令两个序列为 $Fir,Sec$，那么对于放置一个元素 $a_i$，要参考什么呢，或者说什么会影响答案呢？明显的，是放置的序列的最后一个数。因为题目中对最后答案产生贡献的情况只在相邻两数之间。

然后，我们来分类讨论一下放置 $a_i$ 的情况，为了方便，我们这里保证 $Fir_{last}\le Sec_{last}$。(last 最后的)

当 $Fir_{last}<a_i\le Sec_{last}$，这里只能放 $Sec$ 才能不对答案有贡献。

当 $Fir_{last}\le Sec_{last}<a_i$ 的时候，肯定对答案有贡献，定是放置在 $Fir$。序列尾数越大，就可以放置更大数而不对答案有贡献，意味着，序列尾数越大即越优。所以这里要保留较大的 $Sec$，然后把 $Fir$ 的尾数修改成更大的，这样的结果就是最优的，因为相对于把 $a_i$ 放置在 $Sec$ 我们有了一个更大的尾数。

当 $Fir_{last}>a_i$ 时，那么定有 $Sec_{last}\geq Fir_{last}>a_i$，所以肯定放在 $Fir$。同上文所言，这里放置 $a_i$，虽不对答案有贡献却定会让序列尾数变小，那我们一定是选择变小更小 $Fir_{last}$，保留一个更大的 $Sec_{last}$，这样定然更优。

所以策略就出来了：
- $Fir_{last}<a_i\le Sec_{last}$ 放 $Sec$
- $Fir_{last}\le Sec_{last}<a_i$ 放 $Fir$
- $Sec_{last}\ge Fir_{last}>a_i$ 放 $Fir$

最后记得每次放置后要维护 $Fir_{last}\le Sec_{last}$，因为这是策略的前提，如果不维护，会有点麻烦。
# 实现
```cpp
#include<iostream>
using namespace std;
int t,n,fir,sec,ans;
int main(){
	scanf("%d",&t);
	while(t--){
		fir=sec=0x3f3f3f3f;
		ans=0;
		scanf("%d",&n);
		for(int i=1,a;i<=n;i++){
			scanf("%d",&a);
			if(a<=fir)
				fir=a;
			else if(a<=sec)
				sec=a;
			else{
				fir=a;
				ans++;
			}
			if(fir>sec){
				fir^=sec;
				sec^=fir;
				fir^=sec;
			}
		}
		printf("%d\n",ans);
	}
}
```

---

