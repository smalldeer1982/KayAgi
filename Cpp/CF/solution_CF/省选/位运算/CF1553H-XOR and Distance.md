# XOR and Distance

## 题目描述

You are given an array $ a $ consisting of $ n $ distinct elements and an integer $ k $ . Each element in the array is a non-negative integer not exceeding $ 2^k-1 $ .

Let's define the XOR distance for a number $ x $ as the value of

 $ $$$f(x) = \min\limits_{i = 1}^{n} \min\limits_{j = i + 1}^{n} |(a_i \oplus x) - (a_j \oplus x)|, $ $ </p><p>where  $ \\oplus $  denotes <a href="https://en.wikipedia.org/wiki/Bitwise_operation#XOR">the bitwise XOR operation</a>.</p><p>For every integer  $ x $  from  $ 0 $  to  $ 2^k-1 $ , you have to calculate  $ f(x)$$$.

## 说明/提示

Consider the first example:

- for $ x = 0 $ , if we apply bitwise XOR to the elements of the array with $ x $ , we get the array $ [6, 0, 3] $ , and the minimum absolute difference of two elements is $ 3 $ ;
- for $ x = 1 $ , if we apply bitwise XOR to the elements of the array with $ x $ , we get the array $ [7, 1, 2] $ , and the minimum absolute difference of two elements is $ 1 $ ;
- for $ x = 2 $ , if we apply bitwise XOR to the elements of the array with $ x $ , we get the array $ [4, 2, 1] $ , and the minimum absolute difference of two elements is $ 1 $ ;
- for $ x = 3 $ , if we apply bitwise XOR to the elements of the array with $ x $ , we get the array $ [5, 3, 0] $ , and the minimum absolute difference of two elements is $ 2 $ ;
- for $ x = 4 $ , if we apply bitwise XOR to the elements of the array with $ x $ , we get the array $ [2, 4, 7] $ , and the minimum absolute difference of two elements is $ 2 $ ;
- for $ x = 5 $ , if we apply bitwise XOR to the elements of the array with $ x $ , we get the array $ [3, 5, 6] $ , and the minimum absolute difference of two elements is $ 1 $ ;
- for $ x = 6 $ , if we apply bitwise XOR to the elements of the array with $ x $ , we get the array $ [0, 6, 5] $ , and the minimum absolute difference of two elements is $ 1 $ ;
- for $ x = 7 $ , if we apply bitwise XOR to the elements of the array with $ x $ , we get the array $ [1, 7, 4] $ , and the minimum absolute difference of two elements is $ 3 $ .

## 样例 #1

### 输入

```
3 3
6 0 3```

### 输出

```
3 1 1 2 2 1 1 3```

## 样例 #2

### 输入

```
3 4
13 4 2```

### 输出

```
2 2 6 6 3 1 2 2 2 2 1 3 6 6 2 2```

# 题解

## 作者：x义x (赞：28)

题解区 LaTeX 炸了，请移步 [github pages](https://xyix.github.io/posts/?&sortby=id&postname=cf-1553-h) 或 [luogu 博客](https://www.luogu.com.cn/blog/zyxxs/solution-cf1553h) 观看。

> **题目大意.**
>
> 现在有一列在 $[0,2^k)$ 间的整数 $a_i$，你要对任意 $x\in[0,2^k)$ 求出
> $$\min_{i,j}|(a_i\oplus x)-(a_j\oplus x)|$$
> $k\le 19,n\le 2^k$。

官方正解十分恶心，但评论区一个[老哥](https://codeforces.com/profile/dragonslayerintraining)的解法着实很惊艳。

我们强制每个 $x$ 只能使用那些，与 $x$ 相比只有最低的 $d$ 位可能不同的元素。

设 $f(d,x)$ 为此时的答案，$\text{minv}(d,x)$ 为这些元素中与 $x$ 异或值的最小值，$\text{maxv}$​ 亦然。

---

现在从 $d$​ 转移到 $d+1$​，令 $x,y$​ 为两个仅第 $d+1$ 位不同的位置。（$x<y$）

$\text{minv},\text{maxv}$​​ 的维护相对显然：
$$
\text{minv}(d+1,x)=\min(\text{minv}(d,x),\text{minv}(d,y)+2^d\text)
$$
$$
\text{maxv}(d+1,x)=\max(\text{maxv}(d,x),\text{maxv}(d,y)+2^d\text)
$$

考虑 $f(d+1, x)$​​。元素对有三类：均处于 $(d,x)$​ 中，均处于 $(d,y)$​ 中，一个处于 $(d,x)$​ 一个处于 $(d,y)$​ 中。

- 对于第一类，直接使用 $f(d,x)$。
- 对于第二类，我们不难发现 $(a_i\oplus y)-(a_j\oplus y)=(a_i\oplus x)-(a_j\oplus x)$​​。直接使用 $f(d,y)$​。
- 对于第三类，不难发现 $(a_j\oplus x)=(a_j\oplus y)+2^d\ge 2^d>(a_i\oplus x)$​，故直接使用 $\text{minv}(d,y)$ 和 $\text{maxv}(d,x)$ 即可。

代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n, k;
const int maxn = 1 << 19;
const int inf = 0x3f3f3f3f;
int f[maxn], v0[maxn], v1[maxn];

int main() {
	scanf("%d%d", &n, &k);
	for (int x = 0; x < 1 << k; x++)
		f[x] = inf,
		v0[x] = inf, 
		v1[x] = -inf;
	while (n--) {
		int x; scanf("%d", &x);
		v0[x] = v1[x] = 0;
	}

	for (int i = 0; i < k; i++)
	for (int y = 0; y < 1 << k; y++) if ((y >> i) & 1) {
		int x = y ^ (1 << i);
		// printf("%d : %d %d\n", i, x, y);
		f[x] = f[y] = min(f[x], f[y]);
		f[x] = min(f[x], v0[y] - v1[x] + (1 << i));
		f[y] = min(f[y], v0[x] - v1[y] + (1 << i));
		int v0x = v0[x], v0y = v0[y], v1x = v1[x], v1y = v1[y];
		v0[x] = min(v0x, v0y + (1 << i));
		v0[y] = min(v0y, v0x + (1 << i));
		v1[x] = max(v1x, v1y + (1 << i));
		v1[y] = max(v1y, v1x + (1 << i));
	}

	for (int x = 0; x < 1 << k; x++) printf("%d ", f[x]);
}
```

---

## 作者：peppaking8 (赞：7)

### 简单题意

给定整数 $n,k$，其中 $k\le 19$。给你 $n$ 个数，你需要对每个 $x\in [0,2^k)$，求出所有数异或 $x$ 后两两之差（大减小）的最小值。

### 解法

~~算是一个比较面向新手的题解？~~

首先，对于这样的与异或密切相关的问题，都需要花一些时间想 01 Trie 能不能解决。所以说，先无脑把给定的 $n$ 个数拍到 01 Trie 上观察。

然后就会注意到，这样处理对于所有数异或 $x$ 的操作非常有利。如果 $x$ 的第 $k$ 位为 $1$，则遍历到第 $k$ 位时把 $0$ 当作 $1$，把 $1$ 当作 $0$ 即可，否则不变。

但如何查找两两之差的最小值呢？很容易想到，想要让两数差距更小，它们从高位到低位相同的位数是很多的，这点不会随 $x$ 的改变而变化。也就是说，我们需要找的答案，很多情况下是在 01 Trie 上同一路径的两个数。

但这样是不对的。很显然可以找到反例：$000,011,111$ 三个数（用二进制表示），异或上 $100$ 后，变为 $100,111,011$，显然 $100-011=001$ 是最小的，而不是 $111-100=011$。

然而，如果在 Trie 的这个节点走不同的路径（一个走 $0$ 一个走 $1$），答案显然是走 $1$ 路径的最小值减去走 $0$ 路径的最大值。因为走 $1$ 的数已经比另一个数大了，要让答案小，肯定是让大数尽量小，小数尽量大。

所以我们可以设计出这样一个算法：枚举 $x$，遍历 01 Trie，若走相同路径则递归，否则查子树的最小值最大值更新答案。这样，对于每个 $x$ 都需要遍历整个子树，时间复杂度 $O(2^k\times n\times k)$。显然超时了。

### 优化

这里需要学习的技巧来了！你会不会觉得，如果 $x,x'$ 仅有很少的位不同，那么遍历 $x$ 和 $x'$ 所做出的某些递归得出的答案是相同的，造成了时间的浪费。

如何解决这个问题？**将 $[0,2^k)$ 的数放在一起遍历 Trie 进行处理**。

还是一样，在 01 Trie 的节点上，我们需要处理两件事情：

1. 两个数这一位相同，即走相同路径。
2. 两个数这一位不同，即走不同路径。

第二种情况我们直接对于所有 $x$ 枚举一遍。第一种情况，如果两数在这一位不同，剩下的位都相同，则只需要递归一次即可。所以算法就是：

- 在 01 Trie 从低位到高位数第 $k$ 位的结点，我们将要处理 $[0,2^k)$ 的答案。更新第一种情况的答案时，我们递归到它的两个子节点，需要处理 $[0,2^{k-1})$ 的答案。递归完后，我们将 $x$ 的答案更新至 $x+2^{k-1}$ 的答案中（$0\le x<2^{k-1}$）。第二种情况，我们枚举 $x$ 更新答案即可。

这样的时间复杂度是多少呢？对于每个节点，如果我们需要处理 $[0,2^i)$ 的答案，时间复杂度消耗是 $O(2^i\times i)$ 的。而这样的结点最多有 $2^{k-i}$ 个，所以这一层的时间复杂度为 $O(2^k\times i)$，累加 $i$ 得到 $O(2^k\times k^2)$。

至此我们就解决了这个问题。

### 值得我们学习的地方

一道题的暴力往往是枚举。但如果我们可以推导出某些枚举得到的答案必定相同，就一定要想一下如何避免或减少重复计算，也许就得到了正解！

### 代码

```cpp
#include<bits/stdc++.h>
#define INF 2147483647
using namespace std;
const int N=2000005;
int n,k;
int a[N];
int ch[N][2],siz[N],tot=1;//建 01 Trie
int num[21];
int ans[N],nowans[N],now[N*10];
int dongtot=0;
bool Fa=false;
void Ins(int x){//在 01 Trie 中插入 x
	for(int i=20;i>=1;i--){
		num[i]=(x&1);
		x>>=1;
	}
	int now=1;
	siz[now]++;
	for(int i=1;i<=20;i++){
		if(!ch[now][num[i]]) ch[now][num[i]]=(++tot);
		now=ch[now][num[i]];
		siz[now]++;
	}
	if(siz[now]>=2){
		Fa=true;
	}
}
inline int Min(int A,int B){
	return (A>B)?B:A;
}
int Qmin(int posi,int x,int qian){//查询 posi 的子树的所有数，异或 x 后的最小值。这里 qian 是当前位，用于异或 x 判断该位是否为 1
	if(!qian) return 0;
	int topos=((x&qian)?1:0);
	if(ch[posi][topos]) return Qmin(ch[posi][topos],x,qian>>1);
	else return (qian)+Qmin(ch[posi][!topos],x,qian>>1);
}
int Qmax(int posi,int x,int qian){//查询最大值
	if(!qian) return 0;
	int topos=((x&qian)?1:0);
	if(ch[posi][!topos]) return (qian)+Qmax(ch[posi][!topos],x,qian>>1);
	else return Qmax(ch[posi][topos],x,qian>>1);
}
void Solve(int posi,int qian){//当前在 posi 结点，需要处理 [0,2^qian) 的答案
//这里，nowans[]记录上一次递归时求得的答案，用于更新
	if(siz[posi]<2){//如果子树中无法找到两个数，直接返回
		for(int i=0;i<qian;i++) nowans[i]=INF;
		return ;
	}
	int _qian=(qian>>1);
	int L=dongtot+1;dongtot+=qian;
        //now[] 用于记录当前递归的答案。为了不导致地址重复，这里的 dongtot 用于分配 now 的空间
	for(int i=0;i<qian;i++) now[L+i]=INF;
	Solve(ch[posi][0],_qian);//解决左子树
	for(int i=0;i<(_qian);i++){//更新答案
		now[L+i]=Min(now[L+i],nowans[i]);
		now[L+i+(_qian)]=Min(now[L+i+(_qian)],nowans[i]);
	}
	Solve(ch[posi][1],_qian);//解决右子树
	for(int i=0;i<(_qian);i++){
		now[L+i]=Min(now[L+i],nowans[i]);
		now[L+i+(_qian)]=Min(now[L+i+(_qian)],nowans[i]);
	}
	if(!ch[posi][0] || !ch[posi][1]){//如果有一个子树不存在，不用求第二种情况了
		for(int i=0;i<qian;i++){
			nowans[i]=now[L+i];
			ans[i]=Min(ans[i],nowans[i]);
		}
		return ;	
	}
	for(int i=0;i<(_qian);i++){//第二种情况
		int Md1=Qmin(ch[posi][1],i,_qian>>1);
		int Md2=Qmax(ch[posi][0],i,_qian>>1);
		now[L+i]=Min(now[L+i],Md1-Md2+(_qian));
	}
	for(int i=(_qian);i<qian;i++){
		int Md1=Qmin(ch[posi][0],i^(_qian),_qian>>1);
		int Md2=Qmax(ch[posi][1],i^(_qian),_qian>>1);
		now[L+i]=Min(now[L+i],Md1-Md2+(_qian));
	}
	for(int i=0;i<qian;i++){//把 now 的答案放到 nowans 中，并更新最终答案 ans，返回
		nowans[i]=now[L+i];
		ans[i]=Min(ans[i],nowans[i]);
	}
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		Ins(a[i]);
	}
	if(Fa){
		for(int i=0;i<(1<<k);i++) printf("0 ");
		return 0;
	}
	for(int i=0;i<(1<<k);i++) ans[i]=INF;
	Solve(1,(1<<20));
	for(int i=0;i<(1<<k);i++) printf("%d ",ans[i]);
}
```

---

## 作者：Miko35 (赞：5)

尝试一句话题解。

- 异或第 $i$ 个二进制位相当于交换 trie 树上深度为 $i$ 的儿子（共 $O(2^i)$ 个）；
- 从低位到高位 DFS 答案，每次暴力交换该交换的所有儿子，易发现总交换次数 $O(n\log n)$；
- DFS 下一位时由于需交换的是上一层的子树，故考虑将子树合并至一个数据结构，而只需要知道该子树内的最大值、最小值、最小差值即可 $O(1)$ 合并。

做完了，时间复杂度 $O(n \log n)$。[Code](https://www.luogu.com.cn/record/75420513)


---

## 作者：feecle6418 (赞：4)

大暴力题

首先考虑一个真暴力，要求异或 $x$ 之后的最小差，我们就建出原序列的 Trie 树，遍历整棵 Trie。对于每个分叉点（即，有两个儿子的点），我们在与 $x$ 这一位相同的那一边查询异或最大值 $mx$，不同的那一边查询异或最小值 $mi$，再用 $2^d+mi-mx$ 更新答案（$d$ 是当前这条边在 Trie 上的深度）。

继续观察这个暴力，发现我们用来查询最大最小异或的 $x$，在递归到 Trie 上面某个深度时（设为 $d$），其实等效于 $x\ \mathrm{and}\ (2^{K-d}-1)$。这也容易理解，递归到这层查询的时候，上面的位异或起来已经一定相同了，再考虑它们没有意义。

假如我们对每个深度为 $d$ 的分叉点，都从 $0\sim 2^{K-d}-1$ 枚举所有可能查询的 $x$，并把所有分叉点中查询结果中最小值记为 $f(d,x)$，预处理出 $f(d,x)$，则询问就可以 $O(K)$ 回答了！（枚举在哪个深度得到答案，答案就是 $f(d,x\ \mathrm{and}\ (2^{K-d}-1))$）

那如何预处理 $f$ 呢？**暴力**预处理。Trie 树上深度为 $d$ 的节点最多有 $2^d$ 个，每个点有 $2^{K-d}$ 次可能的询问，查询一个数的复杂度 $O(K)$，这样总复杂度为：

$$O(\sum_d2^d2^{K-d}K)=O(2^KK^2) $$

可以接受。其实可以利用儿子的 $f$ 已经计算过了的事实做到 $O(2^KK)$（好像正解与这个优化后的方法本质相同），但当前数据范围没必要。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,K,a[530005],c[10600005][2],rt=1,tot=1,mn[21][530005];
void Insert(int p){
	int x=rt,m[24]={0};
	while(p)m[++m[0]]=p%2,p/=2;
	for(int i=K;i>=1;i--){
		if(!c[x][m[i]])c[x][m[i]]=++tot;
		x=c[x][m[i]];
	}
}
int Qmi(int p,int x,int dep){
	if(dep==K)return 0;
	if(c[p][(x>>K-dep-1)&1])return Qmi(c[p][(x>>K-dep-1)&1],x,dep+1);
	if(c[p][((x>>K-dep-1)&1)^1])return Qmi(c[p][((x>>K-dep-1)&1)^1],x,dep+1)+(1<<K-dep-1);
	return assert(0),0;
}
int Qmx(int p,int x,int dep){
	if(dep==K)return 0;
	if(c[p][((x>>K-dep-1)&1)^1])return Qmx(c[p][((x>>K-dep-1)&1)^1],x,dep+1)+(1<<K-dep-1);
	if(c[p][(x>>K-dep-1)&1])return Qmx(c[p][(x>>K-dep-1)&1],x,dep+1);
	return assert(0),0;
}
void dfs(int x,int dep){
	if(!x)return ;
	if(c[x][0]&&c[x][1]){
		for(int i=0;i<(1<<K-dep);i++){
			int w=(i>>K-dep-1)&1;
			mn[dep][i]=min(mn[dep][i],Qmi(c[x][w^1],i,dep+1)-Qmx(c[x][w],i,dep+1)+(1<<K-dep-1));
			//cout<<"MN:"<<dep<<' '<<i<<' '<<mn[dep][i]<<'\n';
		}
	}
	dfs(c[x][0],dep+1),dfs(c[x][1],dep+1);
}
int main(){
	scanf("%d%d",&n,&K),memset(mn,0x3f,sizeof(mn));
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),Insert(a[i]);
	dfs(rt,0);
	for(int i=0;i<(1<<K);i++){
		int ans=1e9;
		for(int j=0;j<K;j++)ans=min(ans,mn[j][i&((1<<K-j)-1)]);
		cout<<ans<<' ';
	}
}

```

---

## 作者：Alex_Wei (赞：4)

> [题目传送门](https://www.luogu.com.cn/problem/CF1553H)。
>
> 题意简述：给出 $n$ 个互不相同的 $a_i\in [0,2^k)$，对于每个 $x\in[0,2^k)$，求 $\min_{i=1}^n\min_{j=i+1}^n|(a_i\oplus x)-(a_j\oplus x)|$。

看到异或，想到维护一个 01-Trie。

首先考虑 $x=0$ 的情况：为了查询最近的两个数之间的距离，我们对于每个节点 $p$，我们**首先想到维护落在该节点所表示区间的所有数**的最小值和最大值，更新答案的方法显然。

但是，在 $x$ 的变化过程中，我们需要翻转某一位（不妨设为第 $i$ 位；位数从左到右从 $k-1$ 到 $0$ 标号）的值：由 $0$ 变为 $1$ 或者相反。对应到 Trie 上就是**交换第 $k-1-i$ 层所有节点的左右儿子**（根节点为第 $0$ 层）。但是，在交换左右儿子的时候，**它们对应的最小值和最大值也会改变，这就意味着我们需要更新左右儿子的整颗子树所存储的信息**，四舍五入相当于**重构了整棵树**：每一层的所有节点的信息都需要更新。这显然是无法承受的。

因此，现在需要一个更加高明的手段，使得交换左右子树时所有子节点信息不变，但仍能推出答案。方法已经呼之欲出了：不妨设节点 $p$ 所表示的区间为 $[l_p,r_p]$，那么我们仅维护**落在该区间的数距离 $l_p$ 的最小值和最大值即可，即将原来的最小值和最大值减去 $l_p$**。不难发现，在交换左右子树时，其内部节点的信息**完全没有变化**。此外，我们还需要记录每个节点所表示的区间长度 $len_p=r_p-l_p+1$，方便更新信息。通过上述方法，我们可以将翻转第 $i$ 位的时间复杂度降低到 $2^{k-i}$。

但这还是不够，因为 **$x$ 从 $0$ 枚举到 $2^k-1$ 的过程中，第 $i$ 位需要翻转 $2^{k-i}$ 次**，那么第 $i$ 位的总时间复杂度就是 $4^{k-i}$，无法承受。可是我们完全不需要这样枚举：**将第 $i$ 位看成第 $k-i-1$ 位**！也就是从 $0$ 到 $2^k-1$ 枚举 $x'$，那么真正的 $x$ 就是 **$x'$ 在二进制下翻转后的十进制的值**。这样一来，我们优化了 $x$ 的枚举顺序，第 $i$ 位仅需要翻转 $2^i$ 次，从而使得第 $i$ 位的时间复杂度就是 $2^{k-i}\times 2^i=2^k$。一共有 $k$ 位，那么最终的总时间复杂度即为 $\mathcal{O}(2^k\times k)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define mem(x,v) memset(x,v,sizeof(x))

const int M=1<<21;

int n,k,R,node,ls[M],rs[M],mi[M],mx[M],len[M],ans[M],res[M];
void push(int x){
	mi[x]=min(mi[ls[x]],mi[rs[x]]+len[x]/2);
	mx[x]=max(mx[ls[x]],mx[rs[x]]+len[x]/2);
	ans[x]=min(min(ans[ls[x]],ans[rs[x]]),mi[rs[x]]+len[x]/2-mx[ls[x]]);
}
void ins(int val,int bit,int &x){
	if(!x)len[x=++node]=1<<bit;
	if(!bit)return mi[x]=mx[x]=0,void();
	ins(val,bit-1,(val>>bit-1&1)?rs[x]:ls[x]),push(x);
}
void flip(int bit,int cur,int x){
	if(cur>bit)flip(bit,cur-1,ls[x]),flip(bit,cur-1,rs[x]),push(x);
	else swap(ls[x],rs[x]),push(x);
	
}
int main(){
	cin>>n>>k,mem(ans,0x3f),mem(mi,0x3f),mem(mx,0xcf);
	for(int i=1,a;i<=n;i++)cin>>a,ins(a,k,R); cout<<ans[R]<<" ";
	for(int i=1;i<1<<k;i++){
		int id=0;
		for(int j=0;j<k;j++){
			if((i-1>>k-j-1&1)!=(i>>k-j-1&1))flip(j,k-1,R);
			id+=(i>>j&1)<<(k-j-1);
		} res[id]=ans[R];
	} for(int i=1;i<1<<k;i++)cout<<res[i]<<" ";
	return 0;
}
```



---

## 作者：huangzirui (赞：2)

题意：

给定 $k$ 和序列 $\{a_i\}$，满足 $a_i< 2^k$。

求对于 $x \in [0,2^k)$，

$$
\min_{i=1}^n\min_{j=i+1}^n|(a_i\oplus x)-(a_j\oplus x)|
$$

$2 \leqslant x\leqslant 2^k \leqslant 2^{19}$

---

魔幻二进制题。

考虑两个数字 $a,b$ 产生的贡献，那么对于它们高于 $lcp(a,b)$ 的位置是没有意义的。

那么设 $dp_{i,j}$ 表示令 $x=i$，只统计与 $x$ 的 $lcp$ 长度大于等于 $j$ 的数字的答案。

考虑转移，举个例子：

$x=\texttt{100010}$

此时计算 $dp_{x,3}$，那么形如 $\texttt{100100},\texttt{100011}$ 的数字都是可以产生贡献的。

现在递推至 $dp_{x,2}$，也就是需要计算 $\texttt{101***}$ 的贡献。

容易发现 $\texttt{101***}$ 内部的答案就是 $dp_{x\oplus2^{k-3},3}$。

考虑计算 $\texttt{101***}$ 与 $\texttt{100***}$ 之间的贡献，容易发现只有两侧的最小值和最大值之间可能产生贡献，于是也易于计算。

$O(n\log n)$。

---

## 作者：Jr_Zlw (赞：0)

## 01-Trie 上状压 dp

首先可以发现，如果两个数的二进制前面  $B$  位相等，那么这  $B$  位数无论  $x$  为多少都无法产生贡献。

然后还可以发现，第一个不相等的位可以确定两个数的大小。


考虑把  $a$  序列插到  01-Trie  里面，这样从顶点到某个点的路径代表这棵子树中的值前面的位数都相等，接下来只需考虑这棵子树里的贡献就好了。

先假设  $x=0$，此时  Trie  里面的所有点都是原来的值。

考虑如果从一个点的  $0$  子树选一个数  $p$，$1$  子树选一个数  $q$，很显然  $p<q$，答案是  $q-p$。所以想要  $p$  尽量大，$q$  尽量小。

而如果两个数都在同一棵子树中，由于包括这一位前面位数相等，所以直接递推到子树考虑即可。

所以可以记  $mn\{u\},mx\{u\},rs\{u\}$  分别表示  $u$  子树能取到的最小最大值和最小差值就可以转移了。

再考虑把  $x$  的限制加上，实际上相当于给某些曾的儿子进行了翻转，而对某一个子树  $u$  的答案的影响仅限于  $u$  以下的层。

所以每一个节点只需要记录它子树内的每一种翻转情况的答案即可。

可以发现  Trie  上深度为  $i$  的点最多有  $2^i$  个，而状态数最多有  $2^{n-i}$  个，每一层乘起来刚好就是  $2^n$，所以直接搞就行了。

时空复杂度  $O(k2^k)$，有点费空间。

代码：

```cpp
#include<cstdio>
#define rep(a,b,c) for(int c(a);c<=(b);++c)
inline int read()
{
	int res=0;char ch=getchar();while(ch<'0'||ch>'9')ch=getchar();
	while(ch<='9'&&ch>='0')res=res*10+(ch^48),ch=getchar();return res;
}
template<typename T> inline T min(const T&x,const T&y){return x<y?x:y;}
template<typename T> inline T max(const T&x,const T&y){return x<y?y:x;}
const int INF=0x3f3f3f3f,N=5e7+10,NN=3e7+10;
int DP[50332000],*mx[1048576],*mn[1048576],*rs[1048576],*buf=DP,ch[1048576][2],n,cnt=1;
inline bool ins(int k)
{
	int p=1;bool flag=0;for(int i=n-1;~i;--i)
	{
		int &x=ch[p][k>>i&1];
		if(!x)flag=true,p=x=++cnt;else p=x;
	}
	return flag;
}
inline void dfs(int p,int B,bool v)
{
	if(!p)return;rs[p]=buf;buf+=(1<<B);if(p!=1){++B;mx[p]=buf;buf+=1<<B;mn[p]=buf;buf+=1<<B;--B;}
	if(!B){mx[p][0]=mn[p][0]=v;mx[p][1]=mn[p][1]=v^1;rs[p][0]=INF;return;} dfs(ch[p][0],B-1,0);dfs(ch[p][1],B-1,1);
	if(ch[p][0]&&ch[p][1])for(int S=0;S<(1<<B);++S)
	{ 
		if(S>>(B-1))
		{
			int T=S^(1<<(B-1));rs[p][S]=min(min(rs[ch[p][0]][T],rs[ch[p][1]][T]),mn[ch[p][0]][S]-mx[ch[p][1]][S]);
			if(p!=1)
			{
				mn[p][S]=mn[ch[p][1]][S]|(v<<B);
				mx[p][S]=mx[ch[p][0]][S]|(v<<B);
				mn[p][S^(1<<B)]=mn[ch[p][1]][S]|((v^1)<<B);
				mx[p][S^(1<<B)]=mx[ch[p][0]][S]|((v^1)<<B);
			}
		}
		else
		{
			rs[p][S]=min(min(rs[ch[p][0]][S],rs[ch[p][1]][S]),mn[ch[p][1]][S]-mx[ch[p][0]][S]);
			if(p!=1)
			{
				mn[p][S]=mn[ch[p][0]][S]|(v<<B);
				mx[p][S]=mx[ch[p][1]][S]|(v<<B);
				mn[p][S^(1<<B)]=mn[ch[p][0]][S]|((v^1)<<B);
				mx[p][S^(1<<B)]=mx[ch[p][1]][S]|((v^1)<<B);
			}
		}
	}
	else
	{
		int c=ch[p][0]|ch[p][1]; for(int S=0;S<(1<<B);++S)
		{
			if(S>>(B-1)){int T=S^(1<<(B-1));rs[p][S]=rs[c][T];} else {rs[p][S]=rs[c][S];}
			if(p!=1)
			{
				mn[p][S]=mn[c][S]|(v<<B);
				mx[p][S]=mx[c][S]|(v<<B);
				mn[p][S^(1<<B)]=mn[c][S]|((v^1)<<B);
				mx[p][S^(1<<B)]=mx[c][S]|((v^1)<<B);
			}
		}
	}
}
int main()
{
	int Q=read();n=read();while(Q--)if(!ins(read())){n=1<<n;while(n--)putchar('0'),putchar(' ');return 0;}
	dfs(1,n,0);for(int S=0;S<(1<<n);++S)printf("%d ",rs[1][S]);putchar('\n');return 0;
}
```


---

## 作者：XyzL (赞：0)

## 题意：

给定一个长度为 $n$ 的数组（ $2≤n≤2^k, 1≤n≤19$ ），

求：$f(x) = \min\limits_{i = 1}^{n} \min\limits_{j = i + 1}^{n} |(a_i \oplus x) - (a_j \oplus x)|, $

## 分析：

对于一道与异或有关的题目，我们通常考虑将题目放在 $01-tire$ 上，是否可以解决题目。

可以想象，在 $x$ 的变化过程中，每当我们将二进制下数字的一位翻转，对应到 $01-tire$ 树上，就相当于将下一层的左右儿子节点交换。我们需要更新左右儿子的所在子树中所存储的最大值，最小值以及子树答案，通过类线段树的思想，问题即可迎刃而解。

## 代码：

```cpp
#include <bits/stdc++.h>

typedef long long LL;

using namespace std;

const int MAXL = 1 << 22;
char i_str[MAXL], o_str[MAXL], *i_s, *i_t;
int o_t;
#define Flush fwrite(o_str,1,o_t,stdout),o_t=0
#define space pc(' ')
#define enter pc('\n')
inline char gc() {
    if (i_s == i_t) {
        i_s = i_str;
        i_t = i_s + fread(i_str, 1, MAXL, stdin);
        return i_s == i_t ? EOF : *i_s++;
    } else
        return *i_s++;
}

inline LL read() {
    LL x = 0, f = 0;
    char ch = gc();
    for (; ch < '0' || ch > '9'; ch = gc())
        if (ch == '-')
            f = 1;
    for (; ch >= '0' && ch <= '9'; ch = gc())
        x = x * 10 + (ch ^ 48);
    return f ? -x : x;
}

inline void pc(char x) {
    o_str[o_t++] = x;
    if (o_t == MAXL)
        Flush;
}

void write(LL x) {
    if (x < 0)
        pc('-'), x = -x;
    if (x > 9)
        write(x / 10);
    pc(x % 10 ^ 48);
}

const int N = 1 << 21;

int n, k, root, tot, lson[N], rson[N], mini[N], maxi[N], len[N], ans[N], res[N];

inline void Pushup(register int x) {
    mini[x] = min(mini[lson[x]], mini[rson[x]] + (len[x] >> 1));
    maxi[x] = max(maxi[lson[x]], maxi[rson[x]] + (len[x] >> 1));
    ans[x] = min(min(ans[lson[x]], ans[rson[x]]), mini[rson[x]] + (len[x] >> 1) - maxi[lson[x]]);
    return ;
}

void Insert(int val, int s, int &x) {
    if (!x)
        len[x = ++tot] = 1 << s;
    if (!s) {
    	mini[x] = maxi[x] = 0;
    	return ;
	}
    Insert(val, s - 1, (val >> s - 1 & 1) ? rson[x] : lson[x]), Pushup(x);
    return ;
}

void Query(int s, int cur, int x) {
    if (cur > s)
        Query(s, cur - 1, lson[x]), Query(s, cur - 1, rson[x]), Pushup(x);
    else
        swap(lson[x], rson[x]), Pushup(x);
}

signed main() {
    memset(ans, 0x3f, sizeof ans);
    memset(mini, 0x3f, sizeof mini);
    memset(maxi, 0xcf, sizeof maxi);
    n = read(), k = read();
    int K = 1 << k;
    for (register int i = 1, a; i <= n; ++i)
        a = read(), Insert(a, k, root);
    write(ans[root]), pc(' ');
    for (register int i = 1; i < K; ++i) {
        int id = 0;
        for (register int j = 0; j < k; ++j) {
            if ((i - 1 >> k - j - 1 & 1) != (i >> k - j - 1 & 1))
                Query(j, k - 1, root);
            id += (i >> j & 1) << (k - j - 1);
        }
        res[id] = ans[root];
    }
    for (register int i = 1; i < K; ++i)
        write(res[i]), pc(' ');
    enter, Flush;
    return 0;
}
```

---

