# [ABC290G] Edge Elimination

## 题目描述

给定一颗满 $K$ 叉树，深度为 $D$，即整棵树有 $1+K+K^2+\dots+K^D$ 个节点。

现在你可以选定若干条边并将其删除（也可以选择不删）。删除后将得到一个森林。求使森林中存在一棵树的节点数为 $X$ 的最小删除边数。

## 样例 #1

### 输入

```
11
2 2 1
2 2 2
2 2 3
2 2 4
2 2 5
2 2 6
2 2 7
1 999999999999999999 1
1 999999999999999999 2
1 999999999999999999 999999999999999999
1 999999999999999999 1000000000000000000```

### 输出

```
1
2
1
1
2
1
0
1
999999999999999998
1
0```

# 题解

## 作者：sndd (赞：5)

原题链接->[ABC290G](https://www.luogu.com.cn/problem/AT_abc290_g)

## 题意简析

给定深度为 $D$ 的满 $K$ 叉树，使其减掉若干条边后变为大小为 $X$ 的连通分量，求需减掉的最小边数。

# 分治+贪心

因为是满 $K$ 叉树，很容易想到**分治**向下**贪心**。

当 $X$ 能刚好完全覆盖某颗子树时，只需要砍断子树根连着的链，显然这种情况是最优的。

由此拓展，当 $X$ 完全覆盖某颗子树后还剩下节点，这些节点有两种可能：
* 以子树根节点的父亲为联通分量的 $lca$，向下贪心。
* 继续向上查找最优解。

 于是我们可以向上枚举 $lca$，查找最优解。

 现在讨论找到 $lca$ 后如何贪心。
 
 由上述情况可知，砍掉其完整子树也是最优解。

 所以我们应当砍掉所有能砍掉的子树，将剩下的节点向下递归，将这个问题分成子问题，不断砍掉子树并统计答案。

 具体做法：
 * 从子节点向上查找 $X$ 能覆盖的最大子树。
 * 向上枚举 $lca$。
 * 从 $lca$ 向下递归，不断砍掉能砍掉的子树，统计答案。

注：在枚举到 $lca$ 后，若改点不是根节点，还需额外砍断该节点与其父亲相连的链。

## 计算

不难看出深度为 $1$ 的满 $K$ 叉树大小 $siz_1=K+1$,由此拓展可知深度为 $D$ 的树大小 $siz_D=K \times siz_{D-1}+1$。

子树大小最好预处理一下不然会卡……

## 完整代码
~~有点丑陋就是了~~

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=65;

int T,D,K,X;
int siz[N];
int ans,tmp;

void dfs(int d,int x){				//分治  
	tmp+=((siz[d]-x)/siz[d-1]);		//统计答案 
	x-=((x-1)/siz[d-1])*siz[d-1]+1;	//减去已经处理过的节点，注意要减掉lca 
	if(x) dfs(d-1,x);				//向下贪心
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--){
		cin>>D>>K>>X;
		siz[0]=1;
		for(int i=1;i<=D;i++){			//预处理子节点数量 
			siz[i]=siz[i-1]*K+1;
		}
		if(X==1){						//特判一下只砍一个叶子 
			cout<<1<<'\n';
			continue;
		}
		ans=1e18;
		for(int i=1;i<=D;i++){			//枚举lca 
			if(siz[i]>=X){
				int x=X;				//*复制变量，一定要设不然后续操作修改会影响 
				tmp=0;
				tmp+=(i==D)^1;
				tmp+=(siz[i]-X)/siz[i-1];
				x-=((X-1)/siz[i-1])*siz[i-1]+1;
				if(x) dfs(i-1,x);
				ans=min(ans,tmp);		//贪心 
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：DaydreamWarrior (赞：5)

[或许更好的阅读体验？](https://rainlycoris.github.io/?#/post/7)

## 题意简述

有一颗深度为 $D$ 的满 $K$ 叉树，你需要剪掉一些边使其存在大小为 $X$ 的联通分量，求最少剪掉的边的条数。

## 分析

考虑选择 __所有__ 大小大于等于 $X$ 的一颗深度为 $d$ 的满 $K$ 叉树，在剪掉后大小仍超过 $X$ 的情况下剪掉所有与根直接相连的边，也就是剪掉若干个深度为 $d-1$ 的满 $K$ 叉树，再递归处理深度 $d-1$ 的满 $K$ 叉树。注意如果 $d \ne D$，在树根与树根父节点的连边也要剪掉。

感性理解一下，考虑为什么是对的。在原树上的任意一棵子树都可以看成一棵树，树的根节点往上有一条链。先不考虑链，原问题变成了有一颗满 $K$ 叉树，剪掉一些边使得 __包含根节点__ 的联通分量大小为 $x$，求剪掉的边的最少条数。这个问题贪心地剪若干个最大的子树再递归下去显然是对的。上面的做发选择所有大小大于等于 $X$ 的子树就实现了枚举链的长度，所以原贪心也是对的。

复杂度 $O(D^2)$。因为 $1 \leq \displaystyle\sum_{i=0}^D{K^i} \leq 10^{18}$，所以 $D \leq 60$，复杂度足以通过。

## 代码
```cpp
const int N = 70;
int a[N];
int D,K,X;

signed main(){
    int t;
    cin >> t;
    while(t--){
        cin >> D >> K >> X;
        a[0] = 1;
        for(int k=1;k<=D;k++)
            a[k] = a[k-1]*K+1;
        int ans = 1e18;
        for(int k=0;k<=D;k++){
            if(a[k]>=X){
                int tmpans = !(k==D);
                int x = a[k]-X,j = k-1;
                while(x&&~j){
                    tmpans += x/a[j];
                    x %= a[j];
                    j--;
                }
                ans = min(ans,tmpans);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

## 闲话

考场写了个只选择最小的大小大于等于 $X$ 的满 $K$ 叉树，WA 了一发，然后在不知道为啥的情况下写了这个过了。

---

## 作者：SlyCharlotte (赞：4)

UPD：添加更好的阅读体验？

[更好的阅读体验？](https://zhuanlan.zhihu.com/p/609918483)


## 题意描述

给定一颗满 $K$ 叉树，深度为 $D$，即整棵有 $1+K+K^2+\dots+K^D$ 个节点。

现在你可以选定若干条边并将其删除（也可以选择不删），删除后将得到一个森林，求使森林中存在一棵树的节点数为 $X$ 的最小删除边数。

## 简要分析

删去某一条边可以转化为删去某一颗子树。

因为所给出的树是一颗满 $K$ 叉树，**所以一次操作即为删去 $\frac {k^{x + 1} -1} {k-1}$ 个点**（等比数列求和公式），其中 $x$ 为所删去子树的深度。

所以我们要删去 $n - x$ 个点，其中 $n$ 为树的节点总数，即 $n = \frac {k ^{d+1}-1}  {k-1}$。

不难发现，**每次操作可以删去一个可以删去的最大子树的所有等价子树**。

例如：

![满二叉树 的图像结果](https://tse3-mm.cn.bing.net/th/id/OIP-C.SYTRoncSaG0VC04vMUF8fwHaDt?w=339&h=175&c=7&r=0&o=5&dpr=2&pid=1.7)

如果想要得到一个节点数为 $5$ 的树，也就是需要删除 $10$ 个点，那么可以先删去以 $2$ 为根的树，剩余 $8$ 个点。

随后再删去以 $6$ 为根的子树，即可得到答案 $2$。



### Bug 1

**事实上，这种贪心策略是错误的，在删去一颗子树时，事实上是分离出这颗子树，这个子树仍然有可能对答案产生贡献**。

我们只需在递归时加上一处特判即可。



### Bug 2

对于刚开始执行操作时，我们仍有漏洞尚未处理。



仍是看上面的图，我想要得到一颗节点数为 $2$ 的子树，按照上述策略我们删除的过程是这样的：

1. 删去以 $2$ 为根的子树，剩余节点数为 $8$。
2. 删去以 $6,7$ 为根的子树，剩余节点数为 $2$。

操作次数为 $3$，然而我们可以先删去以 $7$ 为根的子树，最后把目光放到以 $7$ 为根的子树当中，删去以 $14$ 为根的子树，即可得到更优的答案 $2$。

**注意改变目光时的剩余节点数的变化**。



因此，在初次调用递归函数时，我们可以从能包容下 $x$ 个点的最小子树开始递归。



### Optimisation 1

不难发现，递归函数的执行次数为 $O(2 ^ {ans})$，其中 $ans$ 为最终答案。

所以我们需要剪枝。

不难想到，使用最优性剪枝，记录得到的最优答案，如果当前操作数大于得到的最优答案时直接停止递归即可。



于是我们就得到了一个 $O(ans)$ 的做法，最慢的点跑了 $11\operatorname{ms}$，平均每个点在 $2\operatorname{ms}$ 左右。


## 代码实现

```c++
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <queue>
#include <set>

using namespace std;

typedef __int128 ll;
//typedef long long ll;
const ll maxn = 1e5 + 7;
const ll INF = 1e9 + 7, MOD = 998244353;

inline ll read() {
    char cCc;
    ll xXx = 0, wWw = 1;
    while (cCc < '0' || cCc > '9')
        (cCc == '-') && (wWw = -wWw), cCc = getchar();
    while (cCc >= '0' && cCc <= '9')
        xXx = (xXx << 1) + (xXx << 3) + (cCc ^ '0'), cCc = getchar();
    xXx *= wWw;
    return xXx;
}

inline void write(ll xXx) {
    if (xXx < 0)
        putchar('-'), xXx = -xXx;
    if (xXx > 9ll)
        write(xXx / 10ll);
    putchar(xXx % 10ll + '0');
}

ll d, k, x, ans, n;

ll kissme(ll di, ll zhi) {
    if (zhi == 0)return 1ll;
    ll _x = kissme(di, zhi >> 1);
    if (zhi & 1)return _x * _x * di;
    return _x * _x;
}

ll finalfind(ll x, ll opt) {
    ll l = 0, r = d + 1;
    while (l <= r) {
        ll mid = (l + r) >> 1;
        ll jie = kissme(k, mid + 1);
        ll jie2 = jie * k;
        jie--, jie2--;
        jie /= (k - 1), jie2 /= (k - 1);
        if (jie <= x && x < jie2)return mid + opt;
        else if (jie > x)r = mid - 1;
        else l = mid + 1;
    }
}

ll dfs(ll _x, ll step) {
    if (!_x)return step;
    if (step > ans)return 1e18;
    ll a = finalfind(_x, 0);
    if (a == 0)
        return step + _x;
    ll cur = (kissme(k, a + 1) - 1) / (k - 1);

    if (cur >= x)
        return min(dfs(cur - x, step + 1), dfs(_x % cur, step + (_x / cur)));
    return dfs(_x % cur, step + (_x / cur));
}

void solve() {
    d = read(), k = read(), x = read();
    ans = 1e18;
    n = (kissme(k, d + 1) - 1) / (k - 1);
    ll a = finalfind(x, 0), a2 = finalfind(n - x, 0);
    if (x == 0 || x == n)cout << "0\n";
//    else if (x == 1 || (n - x) == 1)cout << "1\n";
    else if ((kissme(k, a + 1) - 1) / (k - 1) == x || (kissme(k, a2 + 1) - 1) / (k - 1) == (n - x)) cout << "1\n";
    else {
//        cout << min(dfs(n - x, 0), dfs(x, 0)) << '\n';
//        write(min(dfs(n - x, 0), dfs(x, 0)));
        ll a1 = finalfind(x, 1);
        ll cur = (kissme(k, a1 + 1) - 1) / (k - 1);
        if (cur >= x) {
            ans = dfs(cur - x, 1);
            write(min(ans, dfs(n - x, 0)));
        } else write(ans = dfs(n - x, 0));
        putchar('\n');
    }
}

int main() {
//    freopen("test.in","r",stdin);
//    freopen("test.out","w",stdout);
    ll T = read();
    while (T--)solve();
    return 0;
}
```



---

## 作者：MadokaKaname (赞：1)

[更好的阅读体验](https://www.cnblogs.com/monster-hunter/p/17851738.html)

## 前言

似乎洛谷上的题解和 AT 官方都给的 $O(TD^2)$ 算法？

这里给出~~乱搞搞出的~~一种 $O(TD)$ 算法。

## 题解

首先发现 $D$ 虽然没给出固定上界，但显然不超过 $\log_2 10^{18}=60$。

再接下来可以发现删边等价于先选一颗子树，再删掉这颗子树内部的子树。

先纸上瞎画两下，发现子树内部全保留或全删除一定比有些保留有些删除优。

因此我们先猜测答案一定是非常左偏的，例如这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/981plpea.png)

（图中外框深色的即为被选中的）

所以我们可以胡出一种看起来很对的做法：预处理所有深度子树的大小，找到比要求节点数大的最深子树，然后在上面拆。

但是很显然这个结论是不对的~~那你讲它干嘛~~

考虑对于这种构造方案的 hack，一颗深度是 4 的满二叉树，选 5 个点。

![](https://cdn.luogu.com.cn/upload/image_hosting/qrzp01vd.png)

选择方案显然并不是选子树，因为到根节点可以少掉整颗树根往上的边，因此先选一条从根到底部的路径，再选子树更优。

因此我们对这两种情况分讨取 $\min$ 即可。

时间复杂度 $O(TD)$，所有的点都可以在 1ms 内通过。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define LL long long
LL n,i,j,k,m,t;
LL val[1005];
int main() {
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld%lld",&m,&n,&k);
		LL sum=1;
		memset(val,0,sizeof(val));
		val[0]=1;
		for(i=1;i<=m;i++){
			sum*=n;
			val[i]=val[i-1]+sum;
		}
		bool flag=false;
		for(i=m;i>=0;i--)
		  if(k==val[i]){
		  	flag=true;
		  	if(i==m) printf("0\n"); 
		  	else printf("1\n");
		  	break;
		  }
		if(flag==true) continue;
		LL ans=0,tmp=0,num=k;
		for(i=m;i>=0;i--)
		  if(k/val[i]>0){
		  	tmp=i;
		  	break;
		  }
		k--;
		if(tmp!=m-1)ans++;
		for(i=tmp;i>=0;i--){
			LL num1=k/val[i];
			k-=num1*1ll*val[i];
			ans+=(n-num1-1);
			if(k==0){
				ans++;
				break;
			}
			else k--;
		}
		if(num-(m-tmp)<=val[tmp]) tmp--;
		if(tmp<0){
			printf("%lld\n",ans);
			continue;
		}
		num-=(m-tmp);
		LL ans1=(n-1)*(m-tmp-1);
		for(i=tmp;i>=0;i--){
			LL num1=num/val[i];
			num-=num1*1ll*val[i];
			ans1+=(n-num1-1);
			if(num==0){
				ans1++;
				break;
			}
			else num--;
		} 
		printf("%lld\n",min(ans,ans1));
	}
	return 0;
}

```



---

## 作者：JWRuixi (赞：1)

~~/bx /bx /bx ?~~

### 题意

给定一颗深度为 $D$ 为的满 $K$ 叉树，求删除若干条边使森林中存在一颗节点数为 $x$ 的树的最小删边数。多组询问。

$T \le 100,\sum_{i=0}^D K^i \le 10^{18}$。

### 分析

我们先研究一个子问题：假设我们找到了这样的一颗节点数为 $x$ 的树 $T$，我们最小要删几条边才能把它从原树中扣出来呢？我们不妨从节点度数下手，显然每删一条边都会使树整体度数减 $1$；最终的度数和为 $2(x-1)$，那最小删边数就是 $\sum_{i \in T} deg_i - 2(x-1)$，于是这个子问题相当于最小化总度数。

有这个性质我们就能将原问题转换成：找到一个度数最小的连通块，大小为 $x$。

我们研究一下原树的度数性质：

1. 根：度数 $k$；
2. 叶子：度数 $1$；
3. 非根非叶子：度数 $k+1$。

显然根只有一个，那选不选根可以直接分类讨论；那我们现在的问题就是最大化大小为 $x$ 的连通块内叶子的数量。

这个问题不好解决，但是考虑给定 $L$，求最小的连通块包含至少 $L$ 个叶子是 trivial 的，那这个问题就可以用二分解决了。

总复杂度 $\mathcal O(TD\log L)$，显然这就是 $\mathcal O(TD^2)$，其中 $D \le 60$，可过。

### Code

提交记录：<https://atcoder.jp/contests/abc290/submissions/43519046>。



---

## 作者：xcyyyyyy (赞：0)

### [ABC290G] Edge Elimination

兜兜转转，自己想出来了？

只有 $D$ 很小，时间复杂度只能和 $D$ 挂钩。

转化题目意思为保留 $x$ 个点，使得他们出边最少。

考虑节点的度数，每个非叶子节点向下有 $K$ 条出边，除了最上面的点，每个点可以使得他父亲的出边减 $1$，那么我们肯定需要**先保证叶子节点数量最多**，然后贪心使得这些点到达顶点。

$x$ 越大，最小情况下能成为叶子节点一定更多，所以我们的问题就变成了：找到一个叶子节点数量，使得他往上面尽量合并，直到合并到只有一个节点，**这些节点的总数比 $x$ 小**。很明显叶子数量在贪心的前提下可以二分。

最后还要考虑我们能否到达 $1$ 因为这样可以少一条出边，这个东西同样可以贪心从下往上合并。

时间复杂度 $O(\log_2K^DD)$。

有什么不懂的可以直接看代码，很好理解的。

其实也不是一上来就观察到的，我是先看到了连通块问题考虑暴力 `dp` 合并，把 `dp` 式子写出来后就发现了叶子节点的特殊性，后面的东西都能顺理成章地想出来了。

[code](https://atcoder.jp/contests/abc290/submissions/52240223)

---

## 作者：Zhao_daodao (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc290_g)
# 题目描述
对于一颗深度为 $D$ 的满 $K$ 叉树，计算将树分成多个子树，其中有一棵子树有 $x$ 个节点的最小删边个数。

# 题目分析

考虑连通块的点的 `lca` 位于哪一层，枚举 `lca` 所在层为第 $i$ 层。

如果是第 $0$ 层，不用切断，如果是第 `1` 层到第 $d$ 层，需要先切断一条边。


只考虑第 $i$ 层为根的这棵子树，若这棵子树不足 $x$ 个点，可以直接跳过。否则，当前这棵子树总的点数一定大于 $x$（等于 $x$ 的情况直接 `break` 即可。）

计当前还需要删的点的个数为 $sum$，当前删掉的边数为 $cnt$，子树当前层的点为根及以下层点的总数为 $tot$，子树下一层的点为根及以下层的点数为 $w$。

此刻，一定是优先断开靠上的边。靠上的一条边能直接削掉大小为 $w$ 的一棵子树。通过下取整确定削几棵，余数在下一层里考虑。直到要删的点为 `0` 或考虑到最后一层即可。

# 参考代码
```cpp
//已做防抄处理 [滑稽]
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e7+5;
int t,d,k,x;
int a[MAXN];
int s[MAXN];
int cnt;
signed main(){
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	while(t--){
		cin>>d>>k>>x;
		a[0]=1;
		s[0]=1;cnt=0;
		for(int i=1;i<=d;++i){
			a[i]=1ll*a[i-1]*k;
			s[i]=s[i-1]+a[i];
		}
		int ans=s[d];
		for(int i=0;i<=d;++i){
			int  sum=s[i]-x,tot=s[i],cnt=(i<d);
			if(sum<0)continue;
			while(sum>0){
				int w=(tot-1)/k;
				cnt+=sum/w;
				sum%=w;
				tot=w;
			}
			ans=min(ans,cnt);
		}
		cout<<ans<<'\n';
	}
}

```

---

