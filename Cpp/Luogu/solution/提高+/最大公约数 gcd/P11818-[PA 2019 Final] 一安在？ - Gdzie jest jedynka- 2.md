# [PA 2019 Final] 一安在？ / Gdzie jest jedynka? 2

## 题目背景

**请使用 C++14 或者更高的版本提交，否则不保证可以编译成功。**



本题数据为自造。交互库疑似有点弱，欢迎加强。

- std: KanameMadoka & Wuyanru；
- interactor：KanameMadoka & Starrykiller；
- validator & generator：Starrykiller；
- special thanks to FFTotoro。

**本题 $\texttt{\#2}\sim\texttt{\#7}$ 为长度为 $3\sim 8$ 的全排列，在这几个测试点中交互库是不自适应的。**


## 题目描述

**这是一道交互题。** 本题中，**交互库是自适应的**。

有一个**隐藏的** $0\sim n-1$ 的排列 $p_0,p_1,\cdots,p_{n-1}$。

你可以询问至多 $\lceil\frac{5n}{2}\rceil$ 次：每次询问给定 $i,j$（$i\neq j$），交互库会返回 $\gcd(p_{i},p_j)$ 的值。特别地，定义 $\gcd(0,a)=\gcd(a,0)=a$。

找到这个排列中 $1$ 的位置。也就是，找到 $j$，使得 $p_j=1$。

### 实现细节

**本题单个测试点内有多组测试数据。**


你不需要，也不应该实现 `main` 函数。

你需要在文件头加入以下内容：

```cpp
int ask(int, int);
```

你应该实现以下的函数：

- `int solve(int n)`：处理一组排列长度为 $n$ 的数据。
    - 返回一个非负整数 $j$ 满足 $p_j=1$。你需要保证 $0\le j\lt n$，且 $p_j=1$。

实际测评时将会多次调用 `solve` 函数。

你可以调用以下的函数：

- `int ask(int i, int j)`：询问 $\gcd(p_i,p_j)$。
	- 你需要保证 $0\le i,j\lt n$，且 $i\neq j$。

需要注意的是，**交互库是自适应的**，也就是，交互库会根据你的询问（在不矛盾的前提下）动态调整答案。


## 说明/提示



### 样例交互

设原序列为 $[4,2,0,3,1]$。

| 交互库 | 选手程序 |
| :--: | :--: |
| 调用 $\operatorname{solve}(5)$ | |
| 返回 $\gcd(p_1,p_4)=1$ | 调用 $\operatorname{ask}(1,4)$ |
| 返回 $\gcd(p_1,p_0)=2$ | 调用 $\operatorname{ask}(1,0)$ |
| 返回 $\gcd(p_2,p_3)=3$ | 调用 $\operatorname{ask}(2,3)$ |
| $p_4=1$，判定为 Accepted | 返回 $4$ |

需要注意的是，**样例交互仅为交互格式示意，不代表根据这些信息能唯一确定答案。** 交互库是自适应的。

---

### 数据范围

- $3\le n,\sum n\le 5\times 10^5$。

再次提醒，**交互库是自适应的**。

## 样例 #1

### 输入

```
1
5

1

2

3```

### 输出

```


? 1 4

? 1 0

? 2 3

! 3```

# 题解

## 作者：Starrykiller (赞：4)

组题人的口胡题解。

问 $\gcd(p_0,p_1),\gcd(p_0,p_2),\ldots,\gcd(p_0,p_{n-1})$，记答案数列为 $a_1\sim a_{n-1}$。

如果 $a$ 数列全部是 $1$，显然 $p_0=1$。

如果 $a$ 数列是 $1\sim n-1$ 的排列，显然 $p_0=0$。

以上两种情况平凡。否则，$2\le p_0\lt n$。

考虑核心的性质：$\gcd(a,0)=a$。注意到，$\gcd(p_0,p_i)\le p_0$ 当且仅当 $p_0\mid p_i$ 时取到等号。那么，我们将 $a_i$ 取到最大值的位置拿出来递归地做这样的过程。

最终一定会得到 $0$ 的位置。到此询问次数最坏是 $n+n/2+n/4+...=2n$ 的，当每一步都取到 $2,4,8,...$ 时得到最劣解。

最后用 $0$ 再问一遍序列（只需要问不是 $p_0$ 倍数的位置）得到答案。这样最坏卡到 $2.5n$。

---

## 作者：__ZyC__ (赞：1)

### 这是一个严格小等于 2n 的做法

一个非常显然的结论。

若 $\gcd(a,b) = \gcd(a,c)$ 则，$ \gcd(b,c) \ge \gcd(a,b)$ 。

证明：因为 $\gcd(a,b) \mid b,\gcd(a,c) \mid c$，所以 $\gcd(a,b)$ 显然是 $\gcd(b,c)$ 的一个因子。

我们又发现，$0$ 和其他数的 $\gcd$ 就是他的 $\gcd$ 最大值，于是不难注意到如果构造一种方法能找到某种意义下的 $\gcd$ 最大值则它必然是某个数和 $0$ 进行的一次 $\gcd$。

考虑这样一种方法。定义两个指针 $l,r$ 表示当前找到的两个数的下标使得其 $\gcd$ 的值某种意义下最大。接下来枚举一个 $i$，进行分类讨论。

1. $\gcd(a_l,a_i) > \gcd(a_l,a_r)$

把 $r$ 赋为 $i$ 。

2. $\gcd(a_l,a_i) < \gcd(a_l,a_r)$

$l,r$ 保持不变，继续枚举。

3. $\gcd(a_l,a_i) = \gcd(a_l,a_r)$

将 $l$ 赋为 $r$ ，然后将 $r$ 赋为 $i$。

其实这样并不能求出最大的 $\gcd$ 值，但可以保证 $l,r$ 其中一个是 $0$。读者自证。最后我们先用 $l$ 求一遍所有数的 $gcd$，如果出现了两个 $1$，则用 $r$ 求。


但是我们发现每次情况 $3$ 都会再 $ask$ 一遍 $\gcd(a_r,a_i)$ ，复杂的无法保证。于是我们在求 $l,r$ 时加一点操作：

1. 若 $\gcd(a_l,a_i) = 1$ 则不执行 $3$ 操作。
2. 若出现一对 $i,j$ 被 $ask$ 过，且其 $ask$ 的值 $>1$ 则标记 $i,j$，使其在最后求 $1$ 的位置时直接跳过。

正确性显然，同时若 $\gcd(a_l,a_i) > 1$ 才有可能会执行 $3$ 操作，多一次 $ask$，但是 $a_i$ 也会被标记，少一次 $ask$，所以总次数严格小于等于 $2n$。

### AC code

```cpp
#include <bits/stdc++.h>
using namespace std;
int ask(int, int);
int solve(int n){
    bool f1 = true,ep = false,en[500010];
    int cnt = 0;//这个是用来验证正确性的
    for(int i = 0;i < n;i++)
        en[i] = true;
    int l = 0,r = 1,vl = ask(l,r);
    cnt++;
    if(vl > 1)en[r] = false,f1 = false;
    for(int i = 2;i < n;i++){
        int vi = ask(l,i);
        cnt++;
        if(vi == 1)continue;
        f1 = false,en[i] = false;
        if(vi == vl)l = r,r = i,vl = ask(l,r),cnt++;
        else if(vi > vl)r = i,vl = vi;
    }
    if(cnt >= 2 * n)exit(0);
    if(f1)return 0;
    int i1 = -1;
    for(int i = 1;i < n;i++){
        if(!en[i])continue;
        if(ep){
            int vi = ask(r,i);
            cnt++;
            if(cnt >= 2 * n)exit(0);
            if(vi == 1)return i;
        }
        else {
            int vi = ask(l,i);
            cnt++;
            if(cnt > 2 * n)exit(0);
            if(vi != 1)continue;
            if(i1 == -1)i1 = i;
            else {
                ep = true;
                int ax = ask(r,i1);
                cnt++;
                if(cnt >= 2 * n)exit(0);
                if(ax == 1)return i1;
                ax = ask(r,i);
                cnt++;
                if(cnt >= 2 * n)exit(0);
                if(ax == 1)return i;
            }
        }
    }
    if(cnt >= 2 * n)exit(0);
    return i1;
}
```

---

## 作者：Jorisy (赞：1)

小糖题，然后有个小糖人挂了五发。

如果我们找到了 $0$ 的位置，就可以枚举其他位置和 $0$ 查询 gcd，最坏 $n-1$ 次确定出 $1$。

考虑如何在 $\left\lceil\dfrac32n\right\rceil +1$ 次内找到 $0$。

我们先钦定出排列 $p$ 的第一个数 $p_0$，查询出 $a_i=\gcd\{p_0,p_i\}(i\in[1,n-1])$。

考虑到如果 $p_0=0$，那么 $a_i$ 应当互不相同，即 $a_i=p_i$，这显然是充要的。

若 $p_0\neq 0$，那么 $\max\{a_i\}=p_0$，因为 $\gcd\{p_0,x\}\le p_0$，并且 $\exists p_i\ s.t.\ \gcd\{p_0,p_i=0\}=p_0$。

把 $a_i=p_0$ 的 $p_i$ 全部拿出来作为新的序列 $p'$，显然**要么**这些数是 $p_0$ 的非负整数倍，**要么** $p_0=0$。

然后钦定出 $p'_1$，查询出 $a'_i=\gcd\{p'_1,p'_i\}(i\in[2,n-1])$，然后类似地操作，取出 $\max\{a'_i\}$ 对应的 $p'_i$，构成出序列 $p''$，显然**要么**这些数是 $p'_1$ 的非负整数倍，**要么** $p'_1=0$。

以此类推，最后序列中会剩下**两个数** $x,y$，其中**必然有一个为 $\textbf 0$**。

以上的操作花费了最多 $\dfrac nB+\dfrac{n}{B^2}+\dfrac{n}{B^3}+\cdots=\dfrac{n}{B-1}$ 次询问。其中 $B$ 为序列中最小的正整数。

考虑我们如何利用 $x,y$ 确定出 $1$ 的位置。

首先我们对于那些被加进去过新的序列的数可以直接排除，这样我们就只剩下 $n-\dfrac nB$ 个数。

如果我们用了一个 $0$ 去匹配 $p_i$，那么最后只有一个 $p_i=1$ 满足 $\gcd\{p_i,0\}=1$。

但是如果我们使用了其他正整数，会出现若干个 $1$。当然了，真正的 $1$ 必然在其中。

我们先钦定用 $x$ 去匹配验证，若出现了第二个 $1$，我们可以断定 $y=0$。此时，我们后面未验证的数可以直接用 $0$ 验证。而剩下的前两个数，我们只要另外多匹配一次即可。

这样的话，我们的总查询次数就是 $(n-1)+\dfrac n{B-1}+\left(n-\dfrac nB+1\right)=2n+\dfrac n{B-1}-\dfrac nB$，最坏是 $B=2$，恰好为 $\dfrac 52n$。并且由于中途一些重复的查询可以记忆化，因此就在题目要求的范围内。

```cpp
#include<bits/stdc++.h>
#define N 500005
using namespace std;

int ask(int,int);

map<pair<int,int>,int>mp;
int vis[N],a[N];
vector<int>v;

int qry(int x,int y)
{
    if(x>y) swap(x,y);
    auto &p=mp[{x,y}];
    return !p?p=ask(x,y):p;
}

int solve(int n)
{
    v.clear();
    fill(vis,vis+n,0);
    mp.clear();
    int maxs=0;
    for(int i=1;i<n;i++) maxs=max(maxs,a[i]=qry(0,i));
    if(maxs==1) return 0;//p[0]=1
    if(maxs==n-1)//p[0,n-1]=0,n-1 or p[0,n-1]=n-1,0
    {
        int c=0;
        for(int i=1;i<n;i++)
        {
            if(a[i]==1)
            {
                if(!c) c=i;
                else goto lab;
            }
        }
        return c;
        lab:;
    }
    v.push_back(0);
    vis[0]=1;
    for(int i=1;i<n;i++)
    {
        if(a[i]^maxs) continue;
        v.push_back(i);
        vis[i]=1;
    }
    while(v.size()>2)
    {
        int m=v.size()-1,lst=maxs;
        maxs=0;
        for(int i=2;i<=m;i++) maxs=max(maxs,a[i]=qry(v[1],v[i]));
        vector<int>vec;
        vec.push_back(v[1]);
        for(int i=2;i<=m;i++)
        {
            if(a[i]^maxs) continue;
            vec.push_back(v[i]);
        }
        v=vec;
    }
    int p0=v[0];
    // cerr<<"Pos of 0: "<<v[0]<<" or "<<v[1]<<'\n';
    int res=0;
    for(int i=0;i<n;i++)
    {
        if(vis[i]) continue;
        if(qry(p0,i)==1)
        {
            if(p0==v[1]) return i;
            if(res)
            {
                p0=v[1];
                if(qry(p0,i)==1) return i;
            }
            else res=i;
        }
    }
    return res;
}

// int n,p[N],c=0;
// int ask(int x,int y){c++;return __gcd(p[x],p[y]);}

// int main()
// {
//     cin>>n;
//     for(int i=1;i<=n;i++) cin>>p[i];
//     int ans=solve(n);
//     cout<<"ans = "<<ans<<"\ncount = "<<c;
//     return 0;
// }
```

---

## 作者：XZhuRen (赞：0)

注意到确定了 $0$ 的位置 $pos0$ 后答案为 $i$ 的充要条件即 $ask(pos0,i)=1$。

考虑找 $0$ 的位置。

直接钦定一个位置 $x$，把这个数对其他数都询问一遍，则根据得到的结果序列 $a$，有以下即种情况：

1. $\forall{i},a_i=1$，则 $a_x=1$。

2. 若 $a_x=0$，$\max\{a\}$ 有且仅有一个，为剩下的数的最大值。

3. $a_x\not= 0$，$\max\{a\}$ 等于 $a_x$，剩下的数包含 $a_x$ 的倍数和 $0$。

发现我们每次操作至少晒掉一半的数，则递归处理：

每次取出最大值的集合，删掉当前数，重复这些操作，直到边界情况：

1. $cntmax=1$，这时无法确定 $a_x=0$ 还是 $ask(a_y,a_x)=\max\{a\},a_y=1$，把这两个数$x,y$ 都取出来当作 $0$。

2. $\forall{i},a_i=1$，返回 $x$。
 
对于剩下的，没有被放入最大值集合过的数，挨个询问对于 $x,y$ 的值：

1. 如果 $ask(i,x)\not=1$，不用询问 $ask(i,y)$。

2. 如果 $ask(i,x)=1$ 且 $ask(i,y)=1$，直接返回 $i$。

3. 如果 $ask(i,x)=1$ 且 $ask(i,y)\not=1$，注意到 $0$ 的限制一定宽于 $a_y$，则此时 $x$ 一定不是 $0$。

经检验最大询问次数一定合法。

```cpp

#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int ask(int, int);
int a[N];
int tots=0;
bool vis[N];
int allin[N],tota=0;
int tmp[N],ta=0;
int solve(int n){
	for(int i=0;i<n;i++)vis[i]=0;
	int mx=0;
	tota=0;
	for(int i=0;i<n;i++)allin[++tota]=i;
	while(tota>2){
		int ao=allin[1];
		ta=0;mx=0;
		for(int nw=2;nw<=tota;nw++){
			int i=allin[nw];
			a[i]=ask(ao,i);
			if(a[i]==mx)tmp[++ta]=i;
			else if(a[i]>mx)mx=a[i],tmp[ta=1]=i;
		}
		if(mx==1)return ao;//特判倍数为 1
		tota=ta;
		for(int i=1;i<=tota;i++)allin[i]=tmp[i],vis[allin[i]]=1;
		if(tota==1)allin[++tota]=ao;
		//这里只有一个最大值，则当前选定的为 0 或最大值
		vis[ao]=1;
	}
	for(int i=0;i<n;i++){
		if(vis[i])continue;
		if(tota==1){
			if(ask(i,allin[1])==1)return i;
		}else{
			int x=ask(i,allin[1]);
			if(x!=1)continue;
			int y=ask(i,allin[2]);
			if(y==1)return i;
			allin[1]=allin[2],tota=1;
		}
	}
	return 0;
}

```

---

## 作者：Wei_Han (赞：0)

头一回写交互，这题倒是不难。

考虑到 $0$ 的特殊性质，只要找到了 $0$ 那么我们自然可以逐个找到 $1$，我们先随机抓一个数出来，把他跟所有数询问一遍，显然，如果当前数是 $1$，那么答案全是 $1$，如果是 $0$，那么答案是 $[1,n-1]$ 的排列，这两种直接判掉就好了。

否则，得到的答案中最大的数就是当前数的原始值（因为存在 $0$），我们把答案为最大数的位置都取出来，显然他们要么是 $0$ 要么是这个数的倍数，对这些数再重复上述操作，能够发现，取出来的数可能为 $0$，那么操作完只会剩下 $0$ 和另一个最大数，反过来，如果我们取了最大值，那么剩下的也会是 $0$ 和最大值，所以我们并不能确定 $0$ 的位置，每一次也不能删除我们一开始取来使用的数字。

经过很多轮这样的做法后，我们就会剩下不超过 $2$ 个数，剩下一个的话显然就是 $0$，对于剩 $2$ 个数，我们并不关系哪个是 $0$，只要找 $1$ 就好了，将他们与我们第一次操作剔除的数进行询问，如果与第一个数得到的答案不是 $1$，那么当前数就肯定不是 $1$，否则再与第二个数询问，如果为 $1$，那么当前数显然为 $1$（因为 $0$）,否则第二个数就肯定是 $0$，直接拿第二个数继续做就好了。

分析一下询问次数，最开始我们需要 $n$ 次询问，后面每一次的最坏情况是询问到 $2$ 的倍数，每次只能剔除一半的数，最后一步进行的询问数就是最开始剔除的数的个数，也就是 $\left \lceil \frac{n}{2} \right\rceil$ 次，所以最坏询问次数 $\left \lceil \frac{n}{2}\right \rceil + \sum_{i=0}^{\log_2 n} \left \lfloor \frac{n}{2^i} \right \rfloor \leq \left\lceil \frac{5n}{2}\right \rceil$，可以通过。

```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int N=2e6+5;
int a[N];
int ask(int,int);
int solve(int n)
{
	for(int i=0;i<=n;++i) a[i]=0; 
	for(int i=1;i<n;++i) a[i]=ask(0,i);vector<int> P,P1;
	int flag=1;for(int i=1;i<n;++i) if(a[i]!=1) flag=0;else P1.pb(i);
	if(flag) return 0;flag=1;int maxn=0;
	for(int i=1;i<n;++i) maxn=max(maxn,a[i]);
	P.pb(0);for(int i=1;i<n;++i) if(a[i]==maxn) P.pb(i);
	while(P.size()>2)
	{
		vector<int> E;int m=P.size(),maxn=0;
		for(int i=2;i<m;++i)
		{
			a[i]=ask(P[1],P[i]);
			if(a[i]>maxn) maxn=a[i],E.clear(),E.pb(P[i]);
			else if(a[i]==maxn) E.pb(P[i]);
		}
		int t=P[1];P.clear();P.pb(t);
		for(int i:E) P.pb(i);
	}
	if(P.size()==1) for(int i:P1) if(ask(P[0],i)==1) return i;
	for(int i=0;i<P1.size();++i) if(ask(P[0],P1[i])==1) for(int j=i;j<P1.size();++j) if(ask(P[1],P1[j])==1) return P1[j];
}
``````

---

## 作者：Nephren_Sakura (赞：0)

有点意思的交互题。

我们首先考虑分析 $1$ 的性质，$1$ 和任何数的最大公约数都是 $1$。

然后我们发现这个性质并不好用，因为我们无法弄出来两两之间的最大公约数。

于是我们再来找一个比较有性质的数。观察到题目里给的排列值域不是正常的 $[1,n]$ 而是 $[0,n-1]$，于是我们考虑 $0$ 的性质。

对于 $0$，题目给出了定义：对于任意一个 $x$，$\gcd(0,x)=x$。

然后我们又知道一个很有意思的点：对于任意 $x>0,y>0$，有 $\gcd(x,y)\le x$。

于是我们考虑随便选一个位置，然后和其他所有位置取最大公约数。特判掉这个位置是 $1$ 的情况，那么这些最大公约数最大的位置的**真实取值**必然是这个位置的**真实取值**的倍数。于是只留下这些位置重复此操作，最后一定会留下至多两个位置，其中一个是 $0$。

那么考虑怎么去找哪个位置是 $0$，但是这个东西并不好找。我们不妨转化思想，我们必须知道哪个位置是 $0$ 吗？

很显然是不必要的，我们只需要用这两个位置判断当前位置是否是 $1$。

于是我们遍历第一次找最大公约数的时候就是 $1$ 的那些位置，如果第一个数与当前数**不互质**，那么当前数必定不是 $1$。如果互质考虑第二个数，如果也互质那么当前数就是 $1$（因为这两个数中间必然有一个是 $0$），否则那么 $0$ 肯定是第二个数，只用第二个数继续往下跑就好。

现在我们来分析操作次数。因为我们每次剩下的数都至少减半，操作次数是 $n+\frac{n}{2}+\frac{n}{4}+\dots=2 \times n$，并且这个上界是在第一次取到 $2$ 的时候才能达到，如果第一次不是 $2$ 这一段的值会大大减小。而第一次取到 $2$ 的时候剩余数的个数不会超过 $\frac{n}{2}$，所以刚好卡在了 $\frac{5}{2}\times n$ 级别。

下面是代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,b[1000005];
int ask(int, int);
int a[1000005];
vector<int> v,V,ve;
int solve(int n){
	v.clear(),V.clear();
	for(int i=1; i<n; i++) a[i]=ask(0,i);
	bool f=false;
	for(int i=1; i<n; i++) if(a[i]!=1) f=true;else V.push_back(i);
	if(!f) return 0ll;
	int maxi=0;
	for(int i=1; i<n; i++) maxi=max(maxi,a[i]);
	v.push_back(0);
	for(int i=1; i<n; i++) if(maxi==a[i]) v.push_back(i);
	// for(int x:v) cout<<x<<' ';
	// cout<<"addd"<<'\n';
	while(v.size()>2){
	// for(int x:v) cout<<x<<' ';
	// cout<<"addd"<<'\n';
		ve.clear();
		int maxi=0;
		for(int i=2; i<v.size(); i++){
			int val=ask(v[i],v[1]);
			if(maxi<val) maxi=val,ve.clear(),ve.push_back(v[i]);
			else if(maxi==val) ve.push_back(v[i]);
		}
		int val=v[1];
		v.clear();
		v.push_back(val);
		for(int x:ve) v.push_back(x);
	}
	if(v.size()==1) for(int x:V) if(ask(v[0],x)==1) return x;
	// cout<<v[0]<<' '<<v[1]<<'\n';
	f=false;
	int nw=v[0];
	for(int i=0; i<V.size(); i++) if(ask(nw,V[i])==1){
		if(!f) nw=v[1];
		if(ask(nw,V[i])==1) return V[i];
	}
}
```

---

## 作者：Erine (赞：0)

首先 $n=3$ 先判掉，两两暴力即可。

询问 $b_i=\gcd(a_1,a_i)\quad (2\le i\le n)$。

若 $b_i$ 构成 $[1,n-1]$ 排列，说明 $a_1=0$，那么找到 $b_i=1$ 的位置即可。

否则，考虑 $b_i$ 的最大值一定是 $a_1$，并且存在 $b_i=a_1$ 有 $a_i=0$。记最大值个数为 $p$，若 $p=n-1$ 说明我们直接找到了 $1$。若 $p=1$ 说明我们直接找到了 $0$。于是这两种情况得以解决。

那么接下来有 $p\le \dfrac n2$。考虑把所有最大值的位置拎下来记作 $\{pos_i\}$。

考虑询问 $b'_i=\gcd(a_{pos_1},a_{pos_i})\quad (2\le  i\le p)$。如果 $b_i$ 构成了 $a_1\times [2,3,4,\dots,p]$ 的排列，说明找到了 $0$，赢。如果只有一个最大值，那么同理也能找到 $0$，赢。否则我们继续将集合减半，递归上述过程。

如果递归到 $n=2$ 的子问题，我们先询问其中一个。如果询问两次之后发现答案相同，那么我们得到了 $0$，否则可以确定另一个是 $0$。

分析询问次数。仍假设第一步中最大值个数为 $p$。那么我们最终知道 $0$ 询问 $1$ 只需要询问那些不是最大值的位置，也就是不超过 $n-p$ 个位置。询问次数为：

$$(n-1)+(p-1)+(\le \dfrac{p}2)+(\le \dfrac p4)+(\le \dfrac p8)+\dots +n-p$$

也就是 $\le 2n+p\le 2.5n$，可以通过。

---

