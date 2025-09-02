# Jackets and Packets

## 题目描述

Pak Chanek has $ N $ jackets that are stored in a wardrobe. Pak Chanek's wardrobe has enough room for two stacks of jackets, namely the left stack and the right stack. Initially, all $ N $ jackets are in the left stack, while the right stack is empty. Initially, the $ i $ -th jacket from the top of the left stack has colour $ C_i $ .

Pak Chanek wants to pack all of those jackets into some packets, such that the jackets in the same packet has the same colour. However, it is possible for two jackets with the same colour to be in different packets.

Pak Chanek can do two kinds of operations:

- Pak Chanek can pick any number of jackets from the top from one stack as long as the colour is the same, then take those jackets out of the stack and pack them into a packet. This packing operation takes $ X $ minutes, no matter how many jackets are packed.
- Pak Chanek can move one topmost jacket from one stack to the top of the other stack (possibly right to left or left to right). This moving operation takes $ Y $ minutes.

Determine the minimum time to pack all jackets!

## 说明/提示

Let's denote the contents of the two stacks using arrays that represent the colours of the jackets in the stack from top to bottom. Initially, the two stacks form $ [4, 4, 2, 4, 1, 2, 2, 1] $ and $ [] $ .

Pak Chanek can do the following sequence of operations:

1. Movement from left to right. The two stacks become $ [4, 2, 4, 1, 2, 2, 1] $ and $ [4] $ .
2. Movement from left to right. The two stacks become $ [2, 4, 1, 2, 2, 1] $ and $ [4, 4] $ .
3. Packing for $ 1 $ jacket from the top of the left stack. The two stacks become $ [4, 1, 2, 2, 1] $ and $ [4, 4] $ .
4. Movement from left to right. The two stacks become $ [1, 2, 2, 1] $ and $ [4, 4, 4] $ .
5. Movement from left to right. The two stacks become $ [2, 2, 1] $ and $ [1, 4, 4, 4] $ .
6. Packing for $ 2 $ jackets from the top of the left stack. The two stacks become $ [1] $ and $ [1, 4, 4, 4] $ .
7. Movement from right to left. The two stacks become $ [1, 1] $ and $ [4, 4, 4] $ .
8. Packing for $ 3 $ jackets from the top of the right stack. The two stacks become $ [1, 1] $ and $ [] $ .
9. Packing for $ 2 $ jackets from the top of the left stack. The two stacks become $ [] $ and $ [] $ .

In total, it requires a time of $ 2+2+7+2+2+7+2+7+7=38 $ minutes to pack all jackets. It can be proven that there are no other ways that are faster.

## 样例 #1

### 输入

```
8 7 2
4 4 2 4 1 2 2 1```

### 输出

```
38```

# 题解

## 作者：zhongpeilin (赞：6)

## 题目大意：
有两个栈，初始一个栈为空，并且有以下两次操作，问吧所有数删掉最小代价是多少。  
1. 将某一个栈顶的第一个数移到另一个栈栈顶。  
2. 将某一个栈顶的一个极大相同的数全删掉。  
## 解题思路：
我们分析一下样例的解释，会发现一下几点性质：
1. a 数组中每一个极大连通块都是在同一个栈里且一起被删除的。  
2. 每一个数顶多从第一个栈移到第二个栈再移到第一个栈，且那时下一步一定是删掉。  
3. 每次删完之后和之前的拼在一起，一定是一段区间。  

所以，我们在把 a 的每一个极大连通块缩成一个二元组存数值和个数后。  
**注：以下说的 a 是缩完连通块时候的数组，b 表示 a 出现的个数**。  
设 $dp_{l, r}$ 表示 $l \sim r$ 的区间全部删除的最小花费。  
我们考虑一下 $a_{l}$ 是和谁在一起最后删掉的，但他们可能是 **一些** 数字，就比如下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/i3s4s9d5.png)
他们可能是很多段，假设选出的数的下标为 $id_{1}, id_{2}, \dots id_{k}$，那么考虑会有两种方案去将他们合到一起：
1. 首先将 $id_{1}, id_{2}, \dots id_{k-1}$ 移到右边，然后由于 $id_{k}$ 的集合过大，又将 $id_{1}, id_{2}, \dots id_{k-1}$ 移回左侧，直接删掉，代价是 $2 \times \sum_{i=1}^{k-1}b_{id_{i}} + X + \sum_{i=1}^{k-1}dp_{id_{i} + 1, id_{i+1}-1}$。
2. 那么还有一种可能，就是 $b_{id_{k}}$ 没有那么大，所以是将 $id_{k}$ 移到右边后，直接删掉，代价为 $\sum_{i=1}^{k}b_{id_{i}} + X + \sum_{i=1}^{k-1}dp_{id_{i} + 1, id_{i+1}-1}$。  

通过上面的式子，合起来后发现会有 min 的符号，那么考虑分别考虑，设 $f_{l, r}$ 表示 $l \sim r$ 的第一种情况答案，$g_{l, r}$ 表示 $l \sim r$ 的第二种情况答案。  
因为我们 dp 调用时，是保证 $a_{l} = a_{id_{k}}$ 的，所以我们的 $f,g$ 都可以强制 $l$ 和 $r$ 都被选。  
考虑转移 $f$，那么枚举 $id_{k-1}$，因为 $id_{k} = r$，就有：
$$f_{l,r} = \min_{a_{pos} = a_{l}} f_{l, pos} + dp_{pos+1,r}+2 \times b_{r}$$
当然，在给 dp 更新答案时记得减去 $2 \times b_{r}$。  
g 数组同理：
$$g_{l,r} = \min_{a_{pos} = a_{l}} g_{l, pos} + dp_{pos+1,r}+b_{r}$$
dp 数组就是枚举 $id_{k}$ 的位置：
$$dp_{l, r} = \min_{a_{l} = a_{pos}} \min(f_{l, pos} - 2 \times b_{pos}, g_{l, pos}) + dp_{pos + 1, r} + X$$
显然易见，$O(n^3)$。  
~~创作不易，点个赞吧 QWQ~~！
## CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
int m, X, Y, n, a[405];
long long b[405], dp[405][405], g[405][405], f[405][405];
int main(){
	scanf("%d%d%d", &m, &X, &Y);
	for(int i = 1; i <= m; i++){
		int x;
		scanf("%d", &x);
		if(a[n] == x) b[n]++;
		else a[++n] = x, b[n] = 1;
	}
	for(int i = 1; i <= n; i++) b[i] *= Y; //为了方便
	memset(dp, 0x3f, sizeof(dp));
	memset(f, 0x3f, sizeof(f));
	memset(g, 0x3f, sizeof(g));
	
	for(int i = 1; i <= n; i++){
		dp[i][i] = X, f[i][i] = 2 * b[i], g[i][i] = b[i];//边界
	}
	for(int i = 1; i <= n + 1; i++){
		dp[i][i - 1] = f[i][i - 1] = g[i][i - 1] = 0; //边界
	}
	
	for(int len = 2; len <= n; len++){
		for(int l = 1; l + len - 1 <= n; l++){
			int r = l + len - 1;
			if(a[r] == a[l]){ //条件
				for(int pos = l; pos < r; pos++){ //f
					if(a[pos] == a[l]){
						f[l][r] = min(f[l][r], f[l][pos] + dp[pos + 1][r - 1] + b[r] * 2);
					}
				}
				for(int pos = l; pos < r; pos++){ //g
					if(a[pos] == a[l]){
						g[l][r] = min(g[l][r], g[l][pos] + dp[pos + 1][r - 1] + b[r]);
					}
				}
			}
			for(int pos = l; pos <= r; pos++){
				if(a[pos] == a[l]){
					dp[l][r] = min(dp[l][r], min(f[l][pos] - 2 * b[pos], g[l][pos]) + dp[pos + 1][r] + X);
				}
			}
		}
	}
	printf("%lld", dp[1][n]);
	return 0;
}

---

## 作者：JackF (赞：4)

#### 题意

给定两个栈，其中一个栈中有 $n$ 个数，自栈顶至栈底依次为 $C_1,C_2,\ldots,C_{n}$，另一个栈初始为空。你可以通过以下两种操作来消除所有数：

+ 消去某个栈中栈顶的若干个数，满足这些数都相同，代价为 $X$。

+ 将其中一个栈的栈顶的数移动到另一个栈的栈顶，代价为 $Y$。

你需要最小化消完所有数的代价。

$1\le n\le 400,1\le X,Y\le 10^9,1\le C_i\le n$。

#### 题解

首先容易观察到，一操作一定是消去栈顶的一个极长相同连续段，二操作一定是移动一个极长相同连续段。前者显然，后者假设移动的不是一个极长相同连续段，那么移动后两个栈的栈顶都是同一种数，此时使用一操作消显然不如不移动直接消来得优。

同时注意到，如果移动一个极长相同连续段比直接消除它更优，那么一定是当前这个连续段和后面同种数的另一些连续段合并了。

考虑先将极长相同连续段缩起来，以二元组 $(u,c)$ 表示连续段，$u$ 表示数，$c$ 表示长度。此时消除该连续段的代价为 $X$，移动连续段的代价为 $Y\cdot c$。

假设缩完后的栈的状态是 $(u_1,c_1),(u_2,c_2),\ldots,(u_m,c_m)$。

一种方案是直接花费 $X$ 的代价消除 $(u_1,c_1)$，然后考虑消去 $[2,m]$。

另一种方案是将 $(u_1,c_1)$ 和后面若干 $u_{i}=u_{1}$ 的连续段一起消去，假设消去的是 $i_{0}=1<i_{1}<i_{2}<\cdots<i_{k}\le n$。那么夹在两个选择的连续段之间的部分就变成了一个子问题。此时总代价为消去 $[i_0+1,i_1-1],[i_1+1,i_2-1],\ldots,[i_{k-1}+1,i_{k}-1],[i_k+1,m]$ 这些区间的代价之和加上选择的连续段移动的代价加上消除的代价 $X$。移动的代价是 $Y\cdot\sum\limits_{j=0}^{k-1} c_{i_j}+\min(Y\cdot\sum\limits_{j=0}^{k-1} c_{i_j},Y\cdot c_{i_k})$，取决于最后一次移动是移动 $i_0,i_1,\ldots,i_{k-1}$ 还是移动 $i_k$。

不难发现，以上步骤可以用区间 dp 解决，在区间 dp 的时候 dp 出和 $u_{l}$ 一起消除的位置中最靠后的是 $u_{j}$ 的最小代价，注意到移动代价中有取 $\min$，将其当作 $\min(Y\cdot2\sum\limits_{j=0}^{k-1} c_{i_j},Y\cdot\sum\limits_{j=0}^{k} c_{i_j})$ 对两种分开来 dp 即可。这块的复杂度为 $\sum\limits_{i\ge 1}\sum\limits_{j\ge i}\sum\limits_{i\le k<j}[u_i=u_j=u_k]\le O(n^3)$。

总时间复杂度为 $O(n^3)$。

#### 代码

```c++
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
#define eb emplace_back
#define mp make_pair
#define fi first
#define se second
typedef long long ll;
using namespace std;
constexpr int N=405;
constexpr ll inf=1e18;
struct node{int t,s;}p[N];
int n,m,X,Y,c[N];ll cost[N],f[N][N],g[N][N],dp[N][N];bool vis[N][N];
template<typename T>
inline void ckmin(T&x,const T y){if(y<x)x=y;}
inline ll solve(int l,int r){
	if(l>r)return 0;
	if(l==r)return X;
	if(~dp[l][r])return dp[l][r];
	dp[l][r]=X+solve(l+1,r);
	vector<int>pos;
	rep(i,l,r)if(p[i].t==p[l].t)pos.emplace_back(i);
	vis[l][l]=1;
	f[l][l]=cost[l]*2,g[l][l]=cost[l];
	int z=pos.size()-1;
	rep(i,1,z){
		if(!vis[l][pos[i]]){
			f[l][pos[i]]=g[l][pos[i]]=inf;
			rep(j,0,i-1){
				ll c=solve(pos[j]+1,pos[i]-1);
				ckmin(f[l][pos[i]],f[l][pos[j]]+c+cost[pos[i]]*2);
				ckmin(g[l][pos[i]],g[l][pos[j]]+c+cost[pos[i]]);
			}
			ckmin(dp[l][r],min(f[l][pos[i]]-cost[pos[i]]*2,g[l][pos[i]])+X+solve(pos[i]+1,r));
			vis[l][pos[i]]=1;
		}
		ckmin(dp[l][r],min(f[l][pos[i]]-cost[pos[i]]*2,g[l][pos[i]])+X+solve(pos[i]+1,r));
	}
	return dp[l][r];
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>X>>Y;
	memset(dp,-1,sizeof dp);
	rep(i,1,n){
		cin>>c[i];
		if(c[i]==c[i-1])++p[m].s;
		else p[++m].t=c[i],p[m].s=1;
	}
	rep(i,1,m)cost[i]=(ll)p[i].s*Y;
	return cout<<solve(1,m)<<'\n',0;
}
```



---

## 作者：Enoch006 (赞：3)

把相邻的相同元素合在并一起，显然他们一定是一起合并的。

注意到对于一个区间如果要删完和外界没有任何影响，所以考虑区间 DP。

考虑一次删除在原序列上是什么样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/bbiswyru.png)


对于删除红色颜色，有两种删除方案，其中 $L$ 和 $R$ 分别表示**前面所有组**的个数和**最后一组**的个数：

1. 花费 $L\cdot Y+R\cdot Y+X$，对应操作为着把所有组都移到第二个栈里删掉。
2. 花费 $L\cdot Y+L\cdot Y+X$，对应操作为着把前面的组移到第二个栈，在最后一组操作时又移回第一个栈里删掉。

因此一次删除的贡献为 $L\cdot Y+\min(L,R)\cdot Y+X$

考虑怎么 DP 这个贡献，naive 的方法是直接把 $L$ 记在状态里，这样总复杂度是 $\mathcal{O}(n^4)$ 的。

聪明的方法是直接开两个 DP 数组，一个先预存贡献为 $L\cdot Y+L\cdot Y$ 的答案；另一个只存 $L\cdot Y$，$R\cdot Y$ 合并时再管。

**方法的本质是拆开 $\min$ 的贡献**，从而计算答案，减少复杂度至 $\mathcal{O}(n^3)$。


代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define maxm 405
#define maxn 1005
#define inf 0x3f3f3f3f3f3f
#define mod 1000000007
#define msk cerr
using namespace std;
int T,n,N,m,X,Y,ans;
int a[maxm],b[maxm],c[maxm],A[maxm][maxm];
struct DP{
    int f[maxm],g[maxm],h[maxm];
    int l,vis[maxm],lst[maxm];
    void Init(int x){
        memset(g,0x3f,sizeof(g));
        memset(h,0x3f,sizeof(h));
        memset(f,0x3f,sizeof(f));
        l=x;g[x-1]=f[x-1]=h[x-1]=0;
    }
    void Add(int i){
        int p=vis[b[i]],cnt=c[i];
        g[i]=f[i-1]+2*cnt*Y;
        h[i]=f[i-1]+cnt*Y;
        f[i]=f[i-1]+X;
        while(p){
            g[i]=min(g[i],g[p]+A[p+1][i-1]+2*cnt*Y);
            h[i]=min(h[i],h[p]+A[p+1][i-1]+cnt*Y);
            f[i]=min(f[i],g[p]+A[p+1][i-1]+X);
            f[i]=min(f[i],h[p]+A[p+1][i-1]+X+cnt*Y);
            p=lst[p];
        }
        A[l][i]=f[i];
        lst[i]=vis[b[i]];
        vis[b[i]]=i;
    }
}t[maxm];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>n>>X>>Y;//X表示删，Y表示移动
    for(int i=1;i<=n;i++)cin>>a[i],b[i]=a[i];
    sort(b+1,b+n+1);N=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+N+1,a[i])-b;
    for(int i=1;i<=n;i++){
        if(b[m]==a[i])c[m]++;
        else b[++m]=a[i],c[m]=1;
    }
    for(int i=1;i<=m;i++)t[i].Init(i);
    for(int len=1;len<=m;len++){
        for(int l=1,r=l+len-1;r<=m;l++,r++){
            t[l].Add(r);
        }
    }
    cout<<A[1][m];
    return 0;
}

/*
7 3 1
2 1 2 2 2 1 2  

13
*/
```

---

## 作者：daniEl_lElE (赞：2)

考虑区间 dp，设 $dp_{l,r,0}$ 表示消除 $[l,r]$ 区间的最小花费。

首先有显然转移 $dp_{l,r,0}\leftarrow dp_{l,k,0}+dp_{k+1,r,0}$。边界条件为直接消除每个极长区间。

考虑第二个栈的用途，容易想到可以将一些东西扔到另一个栈等待消除。设 $dp_{l,r,1}$ 表示 $[l,r]$ 区间在另一个栈中存了 $a_l$ 和 $a_r$（及若干个其他的），且 $a_l=a_r$。显然有转移：

* $dp_{l,r,1}\leftarrow dp_{l+1,r-1,0}+2y$；
* $dp_{l,r,1}\leftarrow dp_{l,k-1,1}+dp_{k,r-1,0}+y$，其中 $a_l=a_{k-1}$；
* $dp_{l,r,0}\leftarrow dp_{l,r,1}+x$；

然而，这样并不充足。有一种情况是将一些东西暂时存到另一个栈，然后取回来跟这个栈后面连续的进行操作。设 $dp_{l,r,2}$ 表示 $[l,r]$ 区间在另一个栈中存了 $a_l$ 和 $a_r$（及若干其他的），最后要放回来，且 $a_l=a_r$。转移与 $dp_{l,r,1}$ 类似：

* $dp_{l,r,2}\leftarrow dp_{l+1,r-1,0}+4y$；
* $dp_{l,r,2}\leftarrow dp_{l,k-1,2}+dp_{k,r-1,0}+2y$，其中 $a_l=a_{k-1}$；

转移回 $dp_{l,r,0}$ 的情况，枚举一个后缀保留，则 $dp_{l,r,0}\leftarrow dp_{l,k,2}-2y+x$，其中 $a_k\sim a_r$ 均相等。

总复杂度 $O(n^3)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
int pre[405][405],a[405];
int dp[405][405][3];
signed main(){
	int n,x,y; cin>>n>>x>>y; for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		pre[i][i]=x;
		for(int j=i+1;j<=n;j++){
			pre[i][j]=pre[i][j-1]+(a[j]!=a[j-1])*x;
		}
	}
	memset(dp,1,sizeof(dp));
	for(int i=1;i<=n;i++) dp[i][i-1][0]=0;
	for(int len=1;len<=n;len++){
		for(int l=1,r=len;r<=n;l++,r++){
//			cout<<l<<" "<<r<<"\n";
			dp[l][r][0]=pre[l][r];
			for(int k=l;k<r;k++) dp[l][r][0]=min(dp[l][r][0],dp[l][k][0]+dp[k+1][r][0]);
			if(len>=2&&a[l]==a[r]){
				dp[l][r][1]=dp[l+1][r-1][0]+2*y;
				dp[l][r][2]=dp[l+1][r-1][0]+4*y;
				if(len>=3){
					for(int k=l+2;k<=r;k++){
						if(a[l]==a[k-1]) dp[l][r][1]=min(dp[l][r][1],dp[l][k-1][1]+dp[k][r-1][0]+y);
						if(a[l]==a[k-1]) dp[l][r][2]=min(dp[l][r][2],dp[l][k-1][2]+dp[k][r-1][0]+2*y);
					}
				}
				dp[l][r][0]=min(dp[l][r][0],dp[l][r][1]+x);
				for(int k=r;k>=l;k--){
					if(a[r]!=a[k]) break;
					dp[l][r][0]=min(dp[l][r][0],dp[l][k][2]-2*y+x);
				}
			}
		}
	}
	cout<<dp[1][n][0];
	return 0;
}
```

---

## 作者：Leasier (赞：1)

~~为啥赛时 J 的通过人数大于 E 啊 /yiw~~

------------

首先可以将同值连续段缩起来——它们一定会被放在一起消除。

考虑在初始情况下，我们将怎样消除栈顶 $C_1$。

一个自然的想法是：

- 选取 $1 \leq i_1 < i_2 < \cdots < i_k \leq n$，使得 $C_{i_1} = C_{i_2} = \cdots = C_{i_k}$。
- 删去 $\forall j \in [1, k), (i_j, i_{j + 1})$。
- 将所有 $C_{i_j}$ 移至同一侧删除。

具体地说，当 $k > 1$，我们需要：

- 将 $C_{i_1}$ 移入另一栈中，删去原来的 $(i_1, i_2)$。
- 将 $C_{i_2}$ 移入另一栈中，删去原来的 $(i_2, i_3)$。
- $\cdots$
- 将 $C_{i_{k - 1}}$ 移入另一栈中，删去原来的 $(i_{k - 1}, i_k)$。
- 将 $C_{i_{1 \sim k - 1}}$ 移回原栈或将 $C_{i_k}$ 移入另一栈中，删除所有 $C_{i_j}$。

可以发现在每个“删去原来的某个子区间”的子问题中，我们所需处理的仍是从栈顶开始连续的一段。

于是考虑区间 dp，设 $f_{l, r}$ 表示 $l$ 为栈顶时，删去 $[l, r]$ 所需代价。

其中一种转移是分割区间（即 $i_k < n$）的情况，不难解决；而另一种转移是直接删完（$i_k = n$）的情况。

此时涉及到最后将 $C_{i_{1 \sim k - 1}}$ 移回原栈还是将 $C_{i_k}$ 移入另一栈中的决策，再设 $g_{l, r}, h_{l, r}$ 表示两种情况，最后进行决策即可。

时间复杂度为 $O(n^3)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

int c[407];
ll dp1[407][407], dp2[407][407], dp3[407][407];

inline ll min(ll a, ll b){
	return a < b ? a : b;
}

int main(){
	int n, x, y;
	scanf("%d %d %d", &n, &x, &y);
	for (int i = 1; i <= n; i++){
		scanf("%d", &c[i]);
	}
	for (int i = n; i >= 1; i--){
		bool flag = true;
		for (int j = i; j <= n; j++){
			flag &= c[i] == c[j];
			dp1[i][j] = 0x7fffffffffffffffll;
			for (int k = i; k < j; k++){
				dp1[i][j] = min(dp1[i][j], dp1[i][k] + dp1[k + 1][j]);
			}
			if (c[i] == c[j]){
				if (flag){
					dp2[i][j] = x;
					dp3[i][j] = x + (ll)y * (j - i + 1);
				} else {
					dp2[i][j] = dp3[i][j] = 0x7fffffffffffffffll;
					for (int k = i + 1; k <= j; k++){
						if (c[i] == c[k]){
							dp2[i][j] = min(dp2[i][j], dp1[i + 1][k - 1] + dp2[k][j] + y * 2);
							dp3[i][j] = min(dp3[i][j], dp1[i + 1][k - 1] + dp3[k][j] + y);
						}
					}
				}
				dp1[i][j] = min(dp1[i][j], min(dp2[i][j], dp3[i][j]));
			}
		}
	}
	printf("%lld", dp1[1][n]);
	return 0;
}
```

---

