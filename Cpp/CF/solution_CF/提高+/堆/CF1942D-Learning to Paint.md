# Learning to Paint

## 题目描述

[Pristine Beat - Touhou](https://soundcloud.com/jackaltroy/sets/primordial-beat-pristine-beat)

⠀



Elsie is learning how to paint. She has a canvas of $ n $ cells numbered from $ 1 $ to $ n $ and can paint any (potentially empty) subset of cells.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1942D/3277b406102b440ccbe0c485777db99ec89618eb.png)Elsie has a 2D array $ a $ which she will use to evaluate paintings. Let the maximal contiguous intervals of painted cells in a painting be $ [l_1,r_1],[l_2,r_2],\ldots,[l_x,r_x] $ . The beauty of the painting is the sum of $ a_{l_i,r_i} $ over all $ 1 \le i \le x $ . In the image above, the maximal contiguous intervals of painted cells are $ [2,4],[6,6],[8,9] $ and the beauty of the painting is $ a_{2,4}+a_{6,6}+a_{8,9} $ .

There are $ 2^n $ ways to paint the strip. Help Elsie find the $ k $ largest possible values of the beauty of a painting she can obtain, among all these ways. Note that these $ k $ values do not necessarily have to be distinct. It is guaranteed that there are at least $ k $ different ways to paint the canvas.

## 说明/提示

In the first test case, Elsie can either paint the only cell or not paint it. If she paints the only cell, the beauty of the painting is $ -5 $ . If she chooses not to paint it, the beauty of the painting is $ 0 $ . Thus, the largest beauty she can obtain is $ 0 $ and the second largest beauty she can obtain is $ -5 $ .

Below is an illustration of the third test case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1942D/3d3d08bddad77d78ec4518a724cf3c2c6ce9ab10.png)

## 样例 #1

### 输入

```
4
1 2
-5
2 4
2 -3
-1
3 8
2 4 3
1 3
5
6 20
0 -6 -3 0 -6 -2
-7 -5 -2 -3 -4
7 0 -9 -4
2 -1 1
1 -2
-6```

### 输出

```
0 -5 
2 0 -1 -3 
7 5 4 3 3 2 1 0 
8 8 7 7 5 5 2 2 1 1 1 1 1 1 0 0 0 0 0 -1```

# 题解

## 作者：Drind (赞：5)

这个题一看就很像动态规划，但是有一个前 $k$ 大，我们不是很好处理，所以我们考虑设 $f_i$ 为前 $i$ 格能获得的前 $k$ 大权值，也就是每个状态是一个数组。

我们设计方程，$f_i$ 肯定是从前 $i-1$ 项中，每项的前 $k$ 大权值中来转移的，但是这么直接转移要枚举 $nk$ 项，总复杂度 $n^2k$，接受不了。

因为我们只需要选出 $k$ 大，不需要把 $nk$ 项全选出来，这个问题就变成给你 $n$ 个有序数组，长度均为 $k$，要从其中找出前 $k$ 大。

我们很容易发现我们先把每个数组的第一个塞进一个大根堆里，然后每次取堆顶，弹出，把堆顶元素在数组中的下一个加进来，重复 $k$ 次。堆内只有 $n$ 个元素，共操作 $k$ 次，复杂度为 $k\log n$。

所以直接套用进这道题，将暴力 dp 优化成 $nk\log n$，一看还给了 4.5s 时限，完全可以通过。

---

## 作者：Luzhuoyuan (赞：2)

Links: [[Codeforces]](https://codeforces.com/contest/1942/problem/D) [[Luogu]](https://www.luogu.com.cn/problem/CF1942D)

### 题意简述

有 $n$ 个格子，编号为 $1\sim n$，初始时都是无色的，你可以对其中一些格子进行染色。给定一个 $n\times n$ 的矩阵 $a_{i,j}$ 中 $i\le j$ 的部分，一个染色方案的权值定义为：若该染色方案中被染色的块编号的集合等于 $\displaystyle\bigcup_{i=1}^{m} [l_i,r_i]$，其中 $l_m\le r_m,\forall 1\le i<m,l_i\le r_i<l_{i+1}-1$，则该方案的权值为 $\displaystyle\sum_{i=1}^{m} a_{l_i,r_i}$。求所有 $2^n$ 种染色方案中权值前 $k$ 大的值。每个测试点 $t$ 组测试用例。

- $1\le t\le 10^3;$
- $1\le n,\sum n\le 10^3;$
- $1\le k\le \min(2^n,5\cdot 10^3);$
- $1\le\sum k\le 5\cdot 10^3;$
- $|a_{i,j}|\le 10^6$。

### 思路

由于最后要求前 $k$ 大，我们在设计状态时，如果同种状态转移中每个状态元素增加的贡献是一样的，那么对于每个状态显然只要保存前 $k$ 优的值就行了。

我们考虑设 $f_i$ 表示最后一个染色块的位置不大于 $i$ 的权值前 $k$ 大的值组成的优先队列，其中队头是最大值。之后我们枚举本次要加上哪个区间。定义 $a_{i,i-1}=0$，我们对于 $-1\le j\le i-1$，把最大的 $k$ 个 $top(f_j)+a_{j+2,i}$ 塞进 $f_i$。其中 $top(q)$ 表示 $q$ 的队头，$j=-1$ 是为了处理填 $[1,i]$ 的情况，特判即可。

实现中，我们可以先把每个 $top(f_j)+a_{j+2,i}$ 塞进一个优先队列 $q$，之后进行 $k$ 次，每次把 $q$ 的队头取出并压入 $f_i$，然后如果本次 $q$ 队头对应位置的 $f_j$ 非空，那么再把 $top(f_j)+a_{j+2,i}$ 加进 $q$ 中。每次我们要取出 $top(f_j)$ 时可以先将其塞进一个队列 $tmp_j$ 中再弹出，等 $f_i$ 处理完后再塞回去即可（即代码中 `getv(j)` 对应的过程）。最后的答案就是 $f_n$ 中的值。

复杂度 $O(nk\log k)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005,M=5005;
int T,n,m,a[N][N];
priority_queue<int> f[N];
struct node{int x,v;bool operator<(node x)const{return v<x.v;}};
priority_queue<node> q;
queue<int> tmp[N];
inline int getv(int x){int v=f[x].top();f[x].pop(),tmp[x].push(v);return v;}
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
signed main(){
	T=read();
	while(T--){
		n=read(),m=read();
		for(int i=1;i<=n;i++)for(int j=i;j<=n;j++)a[i][j]=read();
		f[0].push(0);
		for(int i=1;i<=n;i++){
			q.push({-1,a[1][i]});
			for(int j=0;j<i;j++)if(!f[j].empty())q.push({j,getv(j)+a[j+2][i]});
			for(int j=1;j<=m&&!q.empty();j++){
				node p=q.top();q.pop();f[i].push(p.v);
				if(~p.x)if(!f[p.x].empty())q.push({p.x,getv(p.x)+a[p.x+2][i]});
			}
			priority_queue<node>().swap(q);
			for(int j=0;j<i;j++)while(!tmp[j].empty())f[j].push(tmp[j].front()),tmp[j].pop();
		}
		for(int i=1;i<=m;i++)printf("%d ",f[n].top()),f[n].pop();
		puts("");
		for(int i=0;i<=n;i++)priority_queue<int>().swap(f[i]);
	}
	return 0;
}
```

（逃

---

## 作者：MrPython (赞：0)

若无特殊说明，下标默认从 $0$ 开始标号。

---

优先队列优化太好玩了！

建议先完成：[P1631](https://www.luogu.com-cn/problem/P1631)，[
UVA11997](https://www.luogu.com.cn/problem/UVA11997)。

---

容易设计线性 DP 状态：$f_{i}$ 表示考虑仅前 $i$ 个数时，所有方案权值从大到小排序的数组。对于初始状态 $f_0$，仅有填涂 $[0,0]$（权值为 $a_{0,0}$）与什么都不画（权值为 $0$）两种情况。对于 $f_i$，情况可分为几种：
- 不填涂第 $i$ 格：$r_i=f_{i-1}$。
- 填涂了 $[p,i]$（$p=0或1$）：此时其他的格子都没法填充。$s_i=[a_{0,i},a_{1,i}]$。
- 填涂了 $[p,i]$（$p>1$）：此时第 $p-1$ 格无法填涂，需要从 $f_{i-2}$ 开始转移。$t_i={\bigcup_{p=2}^{i-1}[f_{p-2,0}+a_{p,i},f_{p-2,1}+a_{p,i},\dots]}$，其中 $\cup$ 在这里表示拼接两个数组。

将上述三种情况合并起来：$f_i=\operatorname{toSorted}(r_i\cup s_i\cup t_i)$ ,其中 $\cup$ 定义同上，$\operatorname{toSorted}$ 表示将参数中的数组排序返回。实现中，题目仅求前 $k$ 大，因此每个状态仅需保留前 $k$ 项即可。

这样进行动态规划，求 $t_i$ 的时间复杂度为 $O(ki)$。总复杂度为 $O(n^2k)$。

---

我们还可以继续优化求 $t_i$ 的速度。我们保证了 $\forall x,f_x$ 为降序有序数组，因此 $t_{i}$ 的最大值应该只可能从 $f_{p,0}(0\le p<i-2)$ 转移而来。选择了某个元素，就将其删除，让次大值成为最大。实践中不需要真正地删除，记录下当前的首元素是第几个就可以。整个过程使用优先队列维护，每次从队列中取出最大值，若其不是最后一项就将下一项入队。

受不了了。写的太抽象了，还是看 [代码](https://codeforces.com/contest/1942/submission/261640935) 吧！

---

## 作者：N1K_J (赞：0)

# CF1942D Learning to Paint

## 题面

有 $n​$ 个格子，编号为 $1\sim n​$，初始时都是无色的，你可以对其中一些格子进行染色。给定一个 $n\times n​$ 的矩阵 $a_{i,j}​$ 中 $i\le j​$ 的部分，一个染色方案的权值定义为：若该染色方案中被染色的块编号的集合等于 $\displaystyle\bigcup_{i=1}^{m} [l_i,r_i]​$，其中 $l_m\le r_m,\forall 1\le i<m,l_i\le r_i<l_{i+1}-1​$，则该方案的权值为 $\displaystyle\sum_{i=1}^{m} a_{l_i,r_i}​$。求所有 $2^n​$ 种染色方案中权值前 $k​$ 大的值。每个测试点 $t​$ 组测试用例。

- $1\le t\le 10^3;$
- $1\le n,\sum n\le 10^3;$
- $1\le k\le \min(2^n,5\cdot 10^3);$
- $1\le\sum k\le 5\cdot 10^3;$
- $|a_{i,j}|\le 10^6$。

Translated by [Luzhuoyuan](https://www.luogu.com.cn/user/388940).

## SOL

被这东西搞了一个小时，我也是若至。

首先，注意到显然可以用一个 $dp[i]$ 来统计结尾在 $i$ 之前，也就是 $r_n \le i$ 的所有结果。

然后，用 $dp[1],dp[2],\cdots,dp[i-1]$ 来计算 $dp[i]$。

应当注意到 $dp[i]$ 只用保留 $k$ 位，并且从大到小。

朴素转移是 $O(nk \cdot n)=O(n^2k)$ 的。

注意到每次可以只取前面每一个位置上最大的，，然而 $dp[]$ 容易被维护到有序，所以可以：

```cpp
dp[0] = {0};
for(ll i = 1; i <= n; i++){
	while(!q.empty()) q.pop();
	for(ll j = i-1; j >= -1; j--) q.push({a[j+2][i]+(j<0?0:dp[j][0]),j,0});
	while(!q.empty()&&dp[i].size()<k){
		auto [val,pos,ptr] = q.top();q.pop();
		dp[i].push_back(val);
		if(pos<0||ptr+1==dp[pos].size()) continue;
		q.push({dp[pos][ptr+1]+a[pos+2][i],pos,ptr+1});
	}
}
```

用 $q$ 维护前面所有 $dp[]$ 中没有取到的最大值，每次把 $dp[pos]$ 中的第 $ptr$ 转移到 $dp[i]$ 后，把 $dp[pos]$ 的第 $ptr+1$ 项加入 $q$。

这里 $j$ 枚举了前一组 $[l,r]$ 的 $r$，$j=i-1$ 表示 $i$ 没有被染色，$j=-1$ 表示 $r=i$ 就是第一组 $[l,r]$ 的 $r$。

这样一来转移就是 $O(k)$ 的。

整体 $O(nk \log n)$。

[Code](https://codeforces.com/contest/1942/submission/259696385)。

---

## 作者：A2_Zenith (赞：0)

VP 到这个题，感觉不如 C2。

你注意到这个题让你求前 $k$ 优解。我们弱化一下，考虑如何做最优解。

不妨设 $f_{i,0/1}$ 为考虑前 $i$ 个格子，且第 $i$ 个格子不涂色/涂色的最大价值。初始状态是 $dp_{0,0}=0,dp_{1,0}=+\infty$。

容易写出 DP 方程：

$$
\begin{cases}
dp_{i,0}=\max(dp_{i-1,0},dp_{i-1,1})\\
dp_{i,1}=\max\limits_{0\leq j<i}(dp_{j,0}+a_{j+1,i})
\end{cases}
$$

接下来我们不妨再设一维 $r$，令 $f_{i,0/1,r}$ 表示考虑前 $i$ 个格子，且第 $i$ 个格子不涂色/涂色的第 $r$ 优解。

如果你做过[多人背包](https://www.luogu.com.cn/problem/P1858)这道题，不难发现，对于 $dp_{i,0}$ 的转移，本质上是在做 $\{dp_{i-1,0,r}\}$ 与 $\{dp_{i-1,1,r}\}$ 两个单调不增的有序数组的合并再取前 $k$ 项。于是我们便解决了 $dp_{i,0}$ 的转移。这是 $\mathcal{O}(k)$ 的。

不妨再考虑 $dp_{i,1}$ 的转移。其实是一样的，只不过从两个队列合并变成了 $\{dp_{j,0,r}+a_{j+1,i}\}$ 这 $i$ 个序列的合并。但是这是 $\mathcal{O}(nk)$ 的过不了。

我们考虑这 $i$ 个序列合并的本质：在这 $i$ 个队列（这么看待这个数组会更好理解）的队头中找到最大值，然后对那个最大值的队列弹一下队头。

简化一下：找最大值，删最大值，加入新的数。

不难联想到堆，这一步转移就被我们优化到了 $\mathcal{O}(k\log k)$。

总的复杂度就是 $\mathcal{O}(nk\log k)$。考虑到 STL 队列（vector）与堆的巨大常数与 $nk=5 \times 10^6$ 的数据范围可能略显颓态，但是 4.5s 的实现给了我们充足的自信。

赛时代码，实现略丑：


```cpp
#include<bits/stdc++.h>
#define int long long
#define PII pair<int,int>
#define fir first
#define sec second
#define mp make_pair
using namespace std;
const int maxn=1e3+7;
vector<int> dp[maxn][2];
int n,k;
int a[maxn][maxn];
vector<int> MG(vector<int> A,vector<int> B){
    int cnt=0;
    int AC=0,BC=0;
    vector<int> ret;ret.clear();
    while(cnt<k){
        if(AC==A.size()&&BC==B.size())break;
        if((AC<A.size())&&(BC==B.size())){
            cnt++;
            ret.push_back(A[AC]);
            AC++;
            continue;
        }
        if((AC==A.size())&&(BC<B.size())){
            cnt++;
            ret.push_back(B[BC]);
            BC++;
            continue;
        }
        if(A[AC]>=B[BC]){
            cnt++;
            ret.push_back(A[AC]);
            AC++;
            continue;
        }
        if(A[AC]<B[BC]){
            cnt++;
            ret.push_back(B[BC]);
            BC++;
            continue;
        }
    }
    return ret;
}
int L[maxn];
priority_queue<PII> q;
inline void slv(){
    cin>>n>>k;
    for(int i=1;i<=n;i++)for(int j=i;j<=n;j++)cin>>a[i][j];
    for(int i=0;i<=n;i++)for(int j=0;j<=1;j++)dp[i][j].clear();
    dp[0][0].push_back(0);
    for(int i=1;i<=n;i++){
        dp[i][0]=MG(dp[i-1][0],dp[i-1][1]);
        while(!q.empty())q.pop();
        for(int j=0;j<i;j++)L[j]=0;
        for(int j=0;j<i;j++)q.push(mp(dp[j][0][L[j]]+a[j+1][i],j));
        while(!q.empty()&&dp[i][1].size()<k){
            PII P=q.top();q.pop();
            int val=P.fir,pos=P.sec;
            L[pos]++;
            if(L[pos]<dp[pos][0].size())q.push(mp(dp[pos][0][L[pos]]+a[pos+1][i],pos));
            dp[i][1].push_back(val);
        }
    }
    vector<int> ret=MG(dp[n][0],dp[n][1]);
    for(int i=0;i<k;i++)cout<<ret[i]<<" ";
    cout<<endl;
}
signed main(){
    int T;
    cin>>T;
    while(T--)slv();
}
```

---

