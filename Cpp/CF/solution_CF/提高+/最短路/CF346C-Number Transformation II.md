# Number Transformation II

## 题目描述

给定 $n$ 个正整数 $x_i$ 和两个非负整数 $a$ 、 $b$ ，（ $b\leq a$ ），你每次可以进行以下两操作中任一个：
1. $a=a-1$
2. $a=a-a\ mod\ x_i(1\leq i\leq n)$   

问要使 $a$ 变成 $b$ 至少需要多少次操作

## 样例 #1

### 输入

```
3
3 4 5
30 17
```

### 输出

```
6
```

## 样例 #2

### 输入

```
3
5 6 7
1000 200
```

### 输出

```
206
```

# 题解

## 作者：a___ (赞：4)

update 2020/2/17：规范了一下格式，更新了一些有关复杂度的问题。

---

首先 %%%[@AK新手村](https://www.luogu.com.cn/user/221955) dalao，做法比我快 $2^{2+}$ 倍。Orz   

简略提一下他的思路：对于 $a \le b \le c$ ，且 $c-c\bmod x=a$ ，一定有 $b - b\bmod x=a$ ，故 **当前一次可得的最小的数** 一定能转到 **之后一次可得的最小的数** ，所以每次贪心找 **可以得到的最小的数** 即可。  

上次被鸽掉的复杂度证明来了：   
结论：$\mathbf O(m\log n+m)$ （$m$ 含义见下）。  
证明：   
1. 根据调和级数，易知对于所有 $x_i(1\leq i\leq n)$ 的 $[b,a]$ 范围内的倍数，共有约 $mlogn$ 个倍数（具体证明见下）。   
2. 可以发现每次`2`操作后都会得到某个 $x_i$ 的整数倍。
3. 又因为每次最优操作都是找最小的，所以对于任意 $x_i$ 一定刚好得到 $x_i$ 的整数倍或与原来的数之间至少有一个 $x_i$ 的整数倍。
4. 而之后的操作一定不会再得到这些整数倍数了（会不断变小），之前的也不可能得到过。
5. 所以每次至少使 $n$ 个 $x_i$ 的倍数不再出现。
6. 显然，约 $m\log n/n $ 次便不再出现任何 $x_i$ 的倍数，而每次要枚举所有 $n$ 个 $x_i$，所以这一部分复杂度为 $\mathbf O(m\log n)$。
7. 对于之后的`1`操作，至多执行 $m$ 次，复杂度 $\mathbf O(m)$；而对于之前的`1`操作，只有当前数是所有数整数倍时才会出现，这一部分复杂度为 $\mathbf O(\frac{nm}{\Pi_{i=1}^nx_i})$ ，由于 $x_i \geq 2$，得 $\frac{n}{\Pi_{i=1}^nx_i}<1$ ，太小，忽略不计。
8. 得证。   

-------
以下是我的做法。记 $m=a-b+1$ ，复杂度为 $\mathbf O(n\log n+m\log n+m\log m)$。

1. - 考虑每一个 $x_i$ ，容易发现对于每一个 $x_i|c$ （整除）的整数 $c$，都可以由 $[c+1,c+x_i-1]$ 一步得到。   
   - 所以我们对每一个 $b \leq c \leq a$ ，都找到其 **最大可被整除** 的 $x$，即 $g_c=\max\limits_{i=1}^n\{x_i [ x_i | c ]\}$ （记为 $g_c$ ），也就是找到了其可以 **被一步转移到** 的数的范围 $[c+1,c+x-1]$ 。   
   - $g_{1\dots n}$ 求法：对于每一个 $x_i$ ，直接枚举 $[b,a]$ 所有的 $x_i$ 的倍数，用 $\max\{g_{j\cdot x_i},x_i\}$ 更新。单次枚举复杂度是 $\mathbf \Theta(m / x_i)$ ，总复杂度为 $\mathbf O(\sum_{i=1}^n\frac{m}{x_i})\Rightarrow \mathbf O(m\sum_{i=1}^n\frac{1}{x_i})\Rightarrow \mathbf O(m\log n)$ 。  
   - 复杂度证明： $\sum_{i=1}^n\frac{1}{i}$ 叫做调和级数，有一个定理是调和级数是 $\mathbf O(\log n)$ 的。因为有 $\sum\limits_{i=1}^n\frac{1}{i}=\sum\limits_{i=0}^{log_2^n}\sum\limits_{j=2^i}^{2^{i+1}-1}\frac{1}{j}$，而 $\sum_{j=2^i}^{2^{i+1}-1}\frac{1}{j}\leq 1$。   
     这是因为 $\frac{1}{2^i+j}=\frac{1}{2^{i+1}+2j}+\frac{1}{2^{i+1}+2j} > \frac{1}{2^{i+1}+2j}+\frac{1}{2^{i+1}+2j+1}$ ，所以$1=\sum\limits_{j=2^0}^{2^{0+1}-1}\frac{1}{j}>\dots>\sum\limits_{j=2^i}^{2^{i+1}-1}\frac{1}{j}> \sum\limits_{j=2^{i+1}}^{2^{i+2}-1}\frac{1}{j}$ ，故$\sum_{j=2^i}^{2^{i+1}-1}\frac{1}{j}\leq 1$。  
     所以调和级数是 $\mathbf O(\log n)$ 的。   
     而当 $x_i$ 互不相等时，有 $\sum_{i=1}^n\frac{1}{x_i}\leq\sum_{i=1}^n\frac{1}{i}$ ，故枚举复杂度是 $\mathbf O(\log n)$ 的。

2. 由于已经得到了 $g_{1\dots n}$ （也就是其可以 **被一步转移到** 的数的范围），而可以发现这个范围内的 **所有数都比当前数大** ，故可以考虑由 $a$ 至 $b$ dp。   
   记 $f_i$ 为由 $a$ 到 $i$ 的最少转移次数。我们由 $a$ 向 $b$ 枚举每一个数，用所有可以转移到 $i$ 的数的 $f$ 的最小值，即 $\min\limits_{j=i+1}^{i+g_i}\{f_j\}$ 更新 $f_i$ 。   
   可以发现所有可以转移到 $i$ 的数组成一个 **连续整数区间** ，所以我们可以使用一个线段树来找最小值，单次复杂度 $\mathbf O(\log m)$ 。总复杂度 $\mathbf O(m\log m)$ 。

3. 最后答案为$f_b$ 。

一些具体的小细节请看代码（当初写代码时把$a$ $b$ 搞反了）。   

---
```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int N=1e5+10,M=1e6+10;
int mn[M<<2];//segment_tree
inline int min(int a,int b){return a<b?a:b;}
void update(int rt,int l,int r,int p,int x)
{
    if(l==r){mn[rt]=x;return;}
    int m=(l+r)>>1;
    if(p<=m)update(rt<<1,l,m,p,x);
    else update(rt<<1|1,m+1,r,p,x);
    mn[rt]=min(mn[rt<<1],mn[rt<<1|1]);
}
int query(int rt,int l,int r,int ql,int qr)
{
    if(ql<=l&&r<=qr)return mn[rt];
    int m=(l+r)>>1,lans=1e9,rans=1e9;
    if(ql<=m)lans=query(rt<<1,l,m,ql,qr);
    if(qr>m)rans=query(rt<<1|1,m+1,r,ql,qr);
    return min(lans,rans);
}
int n,x[N],a,b,f[M],g[M];
int main()
{
    int i,j,m;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    scanf("%d",&x[i]);
    scanf("%d%d",&b,&a);//注意：这里a,b与题面是反的
    sort(x+1,x+1+n);
    n=unique(x+1,x+1+n)-x-1;
    //注意去重！！！注意去重！！！注意去重！！！
    //当初T了几次，才发现没去重。不去重就不能用调和级数证了，因为出题人可以用n个2把你卡成O(nm)
    m=b-a+1;
    for(i=1;i<=n;i++)//以i-a+1来代替i
    for(j=ceil(a*1.0/x[i])*x[i];j<=b;j+=x[i])
    if(g[j-a+1]<x[i])g[j-a+1]=x[i];
    for(i=1;i<=m;i++)
    if(g[i])--g[i];else ++g[i];
    for(i=m-1;i;i--)
    f[i]=query(1,1,m,i+1,min(i+g[i],m))+1,
    update(1,1,m,i,f[i]);
    printf("%d\n",f[1]);
    return 0;
}
```

---

## 作者：panyf (赞：4)

首先，此题可以贪心。每次将所有数枚举一遍，使得 $a$ 尽量小，同时必须保证 $a \geq b$ 。

简要说明正确性：

如果 $a$ 不取最小值，那么下一步 $a$ 的最小值不可能比 $a$ 这一步就取最小值的情况更小，因此最终步数也不会更少。

不过直接这样模拟会超时，需要优化。

优化1：由于 $a$ 的值只会变小，因此如果某一个 $x$ 当前就不能选择（会使得 $a < b$ )，那么以后这个 $x$ 一定也不能选择，我们便可以删掉这个 $x$ ，用双向链表就能实现 $O(1)$ 删除。

优化2：如果 $x$ 中有很多相同，上述做法仍然会超时，考虑将 $x$ 去重。

代码如下：

```cpp
#include<cstdio>
#include<algorithm>
int a[100009],pr[100009],ne[100009];
int main(){
	int n,i,p,q,j,k,s=0;
	scanf("%d",&n);
	for(i=1;i<=n;++i)scanf("%d",a+i);
	std::sort(a+1,a+n+1),n=std::unique(a+1,a+n+1)-a-1;//去重
	scanf("%d%d",&p,&q),pr[n+1]=n,ne[0]=1;
	for(i=1;i<=n;++i)pr[i]=i-1,ne[i]=i+1;
	while(p>q){
		j=1;
		for(i=ne[0];i<=n;i=ne[i]){
			k=p%a[i];
			if(p-k<q)pr[ne[i]]=pr[i],ne[pr[i]]=ne[i];//删除一个数
			else if(k>j)j=k;
		}
		p-=j,++s;
	}
	printf("%d",s);
	return 0;
}
```


---

## 作者：gan1234 (赞：0)

## 前置知识
- 模运算
- 调和级数
- 线段树
- 动态规划

## 分析

首先我们要知道 $a\bmod b = a-b\times\lfloor \frac{a}{b}\rfloor$

因此操作二 $a=a-a\bmod x_i$ 相当于 $a=b\times\lfloor \frac{a} {b}\rfloor$，也就是让 $a$ 变成 $x_i$ 的一个倍数，且这个倍数是小于 $x$ 的最大的倍数。

观察数据范围，发现虽然 $a$ 和 $b$ 都是 $10^9$ 级别的，但是 $a-b$ 却只有 $10^6$ 级别。

因此我们可以考虑在 $a-b$ 这个区间里 DP。

令 $f_i$ 表示从 $a$ 变成 $i$ 最少的操作数。初始状态为 $f_a=0$，答案为 $f_b$。（实际实现中把下标要下移 $b$）

操作一转移为 $f_i\gets f_{i+1}+1$。

考虑操作二如何转移，发现对于一个能整除 $i$ 的 $x_t$，所有 $ i<j< i+x_t$ 的 $j$ 都能通过一次操作二转移到 $i$。

令 $r_i$ 表示 $\max{i+x_t}$，其中 $x_t \mid i$。

那么转移也就是 $f_i \gets \min^{r_i}_{j=i+1} f_{j}+1$，这是区间最值问题，可以线段树解决。

那么如何求 $r_i$？

令 $m=a-b$。

首先对于相同的 $x_i$，我们没必要重复考虑，直接去重。（保证了复杂度，很重要！）

我们可以直接对于每个 $x_i$，枚举一下 $[a,b]$ 之间的倍数，对于每个倍数更新一次 $r_i$。

而这个东西不难发现最坏枚举次数为 $\sum^n_{i=1}\frac{m}{i}$，根据调和级数结论，复杂度约为 $O(m\log m)$。

线段树复杂度为 $O(m\log m)$，预处理 $r_i$ 复杂度 $O(m\log m)$，因此总复杂度 $O(m\log m)$。
## 代码
```cpp
#include<bits/stdc++.h>
#define MAXN 100005
#define P pair<int,int>
using namespace std;
int n;
int t[MAXN],f[MAXN*10],R[MAXN*10];
struct Seg_Tree{
	int l,r,mn;
}dat[(MAXN*10)<<2];
void build(int l,int r,int k){
	dat[k].l=l;dat[k].r=r;dat[k].mn=1e9;
	if(l==r)return ;
	int m=(l+r)/2;
	build(l,m,k+k);
	build(m+1,r,k+k+1);
}
void update(int x,int z,int k){
	if(dat[k].l==x&&dat[k].r==x){
		dat[k].mn=z;
		return ;
	}
	int m=(dat[k].l+dat[k].r)/2;
	if(x<=m)update(x,z,k+k);
	else update(x,z,k+k+1);
	dat[k].mn=min(dat[k+k].mn,dat[k+k+1].mn);
}
int query(int x,int y,int k){
	if(dat[k].l==x&&dat[k].r==y)return dat[k].mn;
	int m=(dat[k].l+dat[k].r)/2;
	if(y<=m)return query(x,y,k+k);
	else if(x>m)return query(x,y,k+k+1);
	else return min(query(x,m,k+k),query(m+1,y,k+k+1));
}
int a,b;
signed main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;n>=i;i++)cin>>t[i];
	sort(t+1,t+n+1);
	n=unique(t+1,t+n+1)-t-1;
	cin>>a>>b;
	f[a-b]=0;
	for(int i=1;n>=i;i++){
		for(int j=((b+t[i]-1)/t[i])*t[i];j<=a;j+=t[i])
			R[j-b]=max(R[j-b],min(((j+t[i])/t[i])*t[i]-b,a-b+1));
	build(1,a-b+1,1);
	update(a-b+1,0,1);
	for(int i=a-1;i>=b;i--){
		f[i-b]=f[i+1-b]+1;
		R[i-b]=max(R[i-b],i+2-b);
		f[i-b]=min(f[i-b],query(i+2-b,R[i-b],1)+1);
		update(i-b+1,f[i-b],1);
	}
	
	cout<<f[0]<<endl;
	return 0;
}
```

---

## 作者：离散小波变换° (赞：0)

卡常给我卡麻了。

## 题解

容易想到一个显然的贪心，那就是每次选择使 $a$ 在不小于 $b$ 的情况下最小的 $x$ 肯定是不劣的。具体可以用动态规划的转移式感性证明。

我们设 $f_i$ 表示从 $i$ 到 $b$ 的最小步数，那么 $f_i$ 可以从一些合法的 $f_j$ 转移过来。随着 $i$ 的增大，合法的 $j$ 的集合里，一些更小的 $j$ 会被移出集合，而一些更大的 $j$ 会被加入集合。也就是说，这样的 $j$ 满足某种「单调性」。记 $i$ 的所有合法转移来的 $j$ 里面，最小的 $j$ 为 $g_i$，容易发现 $g_i$ 单调不减。

接着考虑应用归纳法。假设 $f_b\le f_{b+1}\le \cdots \le f_{b+k}$ 成立，此时一定会有 $f_i=f_{g_i}+1$。那么对于 $f_{b+k+1}$，它的最优的转移点肯定是 $g_{b+k+1}$，而 $g_b\le g_{b+1}\le \cdots \le g_{b+k+1}$，且 $g_{b+k+1}\le b+k$，所以一定有 $f_b\le f_{b+1}\le \cdots \le f_{b+k}\le f_{b+k+1}$。

现在考虑对于每个 $i\in [b, a]$，维护这个最小的 $j$。从 $x$ 出发，对于 $[x,2x)$ 里的 $i$，决策点会包含 $x$；对于 $[2x,3x)$ 里的 $i$，决策点会包含 $2x$；对于 $[kx,(k+1)x)$ 里的 $i$，决策点会包含 $kx$……我们可以偷懒地维护这些决策点，开一个 $\text{multiset}$ 来维护决策点的最小值，当 $i$ 枚举到 $kx$ 的时候就从这个 $\text{multiset}$ 里移除一个 $(k-1)x$，再加进来一个 $x$。

容易发现这些插入删除操作的总次数是 $\mathcal O\left(\dfrac{a-b+1}{x}\right)$ 的。首先可以对 $x$ 去重，对于剩下来的 $x$，插入删除的总次数应该不超过：

$$\sum_{i=1}^{n}\mathcal O\left(\dfrac{a-b+1}{i}\right)=\mathcal O(m\log m)$$

其中 $m=a-b+1$。

但是用一个 $\text{multiset}$ 维护最小值的话，复杂度会多一只 $\log$。不过由于值域很小，而且最小值是单调不减的，所以可以直接开一个桶来维护。这样就可以去掉因为 $\text{multiset}$ 而产生的 $\log$。

然后如果你用 $\text{vector}$ 存储在每个 $i$ 处有哪些 $x$ 要被移出去、移进来，就会莫名其妙常数太大爆掉，同时这样空间复杂度也是 $\mathcal O(m\log m)$ 很不优美。有一个懒惰的方法就是将 $i$ 位置的 $x$ 加入后再往 $i+x$ 位置放哪些 $x$ 要被加进来，空间复杂度就降到了 $\mathcal O(n)$，时间常数莫名其妙能过了。

## 参考代码

```cpp
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 2147483647;
const int MAXN= 1e5 + 3;
const int MAXM= 1e6 + 3;
int F[MAXM], a, b, n, p, A[MAXN], H[MAXM], o = 1e6;
map<int, bool> M;
vector <int> V[MAXM];
int qread(){
    int w = 1, c, ret;
    while((c = getchar()) >  '9' || c <  '0') w = (c == '-' ? -1 : 1); ret = c - '0';
    while((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + c - '0';
    return ret * w;
}
int main(){
    n = qread();
    up(1, n, i) A[i] = qread(), M[A[i]] = true;
    sort(A + 1, A + 1 + n);
    b = qread(), a = qread();
    int c = 0;
    up(1, n, i) if(A[i] != A[i - 1]){
        int l = a / A[i] * A[i];
        int r = b / A[i] * A[i];
        if(l < a) l += A[i];
        if(l - a <= o) V[l - a].push_back(A[i]);
    }
    p = a;
    up(a, b, i){
        for(auto &x : V[i - a]){
            if(i - x - a >= 0) -- H[i - x - a];
            H[i - a] ++;
            if(i + x - a <= o) V[i + x - a].push_back(x);
        }
        V[i - a].clear();
        V[i - a].shrink_to_fit();
        while(H[p - a] == 0 && p < i) ++ p;
        if(i == a) F[i - a] = 0; else {
            if(p == i) F[i - a] = F[p - a - 1] + 1;
            else       F[i - a] = F[p - a    ] + 1;
        }
    }
    printf("%d\n", F[b - a]);
    return 0;
}
```

---

