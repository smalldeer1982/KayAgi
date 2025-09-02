# Misha and Permutations Summation

## 题目描述

现在有两个$n$的排列$n$的排列是由0 1 2 ... n − 1
这$n$的数字组成的。对于一个排列$p$，$Order(p)$表示$p$是字典序第$Order(p)$小的排列（从0开始计数）。对于小于 $n!$ 的非负数$x$,$P erm(x)$表示字典序第$x$小的排列。
现在，求两个排列的和。两个排列$p$和$q$的和为$sum =Perm((Order(p) + Order(q))$$%$n!)$

## 样例 #1

### 输入

```
2
0 1
0 1
```

### 输出

```
0 1
```

## 样例 #2

### 输入

```
2
0 1
1 0
```

### 输出

```
1 0
```

## 样例 #3

### 输入

```
3
1 2 0
2 1 0
```

### 输出

```
1 0 2
```

# 题解

## 作者：Karry5307 (赞：4)

[安利一下我的博客](https://karry5307.github.io/)
### 题意
设$P$是一个长度为$n$的排列，定义$\operatorname{ord}P$为$P$在所有排列中的名次。

给定两个长度为$n$的排列$P_1,P_2$，求第$\operatorname{ord}P_1+\operatorname{ord}P_2 \bmod n!$小的排列。
### 前置技能
[康托展开](https://karry5307.github.io/2018/11/18/%E3%80%8CUVa-11525%E3%80%8DPermutation/)

这里讲从排列映射到数的过程，还是假设这个排列长度为$n$。

对于第$i$次操作，统计这个数后面有多少个比它小的数，记为$a_i$

那么答案是$\sum_{i=1}^{n}a_i(n-i)!$
### 题解
这一个题和[UVa 11525](https://www.luogu.org/problemnew/show/UVA11525)很像，不会做的可以参考一下[本蒟蒻的题解](https://karry5307.github.io/2018/11/18/%E3%80%8CUVa-11525%E3%80%8DPermutation/)，做法就是用一颗权值线段树维护全局没被放进排列中的第$k$小，所以做这个题可以先把它转化为上面那个题。

首先把两个排列映射到整数，这里要统计后面有多少个比第$i$个数$a_i$小的数。如果暴力找的话是$O(n^2)$的。但是，可以发现排列是由$0,1\cdots n-1$组成的，那么**排列里比这个数小的数的个数就是这个数**。

这句话不是很好懂，但是很重要。因为排列里比这个数$x$小的只有$0,1\cdots x-1$，共有$x$个，所以有$x$个数比$x$小。

所以可以显然推出后面比$a_i$小的数的个$=$总共比$a_i$小的数$-$在$a_i$前面比$a_i$小的数。而排在前面比$a_i$小的数可以用树状数组维护。

用一个树状数组维护第$i$个数是否出现过。对于当前的数，统计$1$到当前数$-1$中的和，就是在这个数前面比它小的数。

所以说，可以用$O(n\log n)$的时间复杂度把$a_{P_1,i}$和$a_{P_2,i}$（$a$指的是前置技能里的$a$数组）求出来，记$S_i=a_{P_1,i}+a_{P_2,i}$。

接下来化简$S$，由于$(x+1)\cdot x!=(x+1)!$，于是可以用这个性质化简$S_i$，使得$0\leq S_i\leq n-i$。

具体方法是，对于$S_i$，$S_{i+1}+=S_i \% n-i,S_i\%=n-i$就可以简化$S$数组了。

最后我们就把问题转化为上面的那个题了，用那个题的方法做就可以了qwq。

时间复杂度$O(n\log n)$，常数不大~~除了权值线段树~~，跑了$2270$ms，拿了最优解qwq。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
const ll MAXN=2e5+51;
struct BIT{
	ll size;
	ll num[MAXN];
	inline ll lowbit(ll x)
	{
		return x&-x;
	}
	inline void add(ll pos,ll val)
	{
		for(;pos<=size;pos+=lowbit(pos))
		{
			num[pos]+=val;
		}
	}
	inline ll queryPrefix(ll pos)
	{
		ll res=0;
		for(;pos;pos-=lowbit(pos))
		{
			res+=num[pos];
		}
		return res;
	}
};
struct SegmentTree{
	ll l,r,size;
};
BIT bit,bit2;
SegmentTree tree[MAXN<<2];
ll cnt,num;
ll perm[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline void update(ll node)
{
	tree[node].size=tree[node<<1].size+tree[(node<<1)|1].size;
}
inline void create(ll l,ll r,ll node)
{
	tree[node].l=l,tree[node].r=r;
	if(l==r)
	{
		tree[node].size=1;
		return;
	}
	ll mid=(l+r)>>1;
	create(l,mid,node<<1);
	create(mid+1,r,(node<<1)|1);
	update(node);
}
inline ll findVal(ll rk,ll node)
{
	if(tree[node].l==tree[node].r)
	{
		tree[node].size=0;
		return tree[node].l;	
	}	
	ll res=0;
	if(rk<=tree[node<<1].size)
	{
		res=findVal(rk,node<<1);
	}
	else
	{
		res=findVal(rk-tree[node<<1].size,(node<<1)|1);
	} 
	update(node);
	return res;
}
int main()
{
	bit.size=bit2.size=cnt=read();
	for(register int i=1;i<=cnt;i++)
	{
		num=read();
		perm[i]=num-bit.queryPrefix(num),bit.add(num+1,1);
	}
	for(register int i=1;i<=cnt;i++)
	{
		num=read();
		perm[i]+=num-bit2.queryPrefix(num),bit2.add(num+1,1);
	}
	for(register int i=cnt,j=0;i;i--,j++)
	{
		perm[i-1]+=perm[i]/(j+1),perm[i]%=(j+1);
	}
	create(1,cnt,1);
	for(register int i=1;i<=cnt;i++)
	{
		printf("%d ",findVal(perm[i]+1,1)-1);
	} 
} 
```

---

## 作者：star_eternal (赞：2)

这道题是裸的康托展开
一种很容易的想法是直接把a和b求出来，然后计算(a+b)modn!的值并直接求对应的排列，但是由于n的范围(n≤200000)

直接求值显然不可行。

因此，考虑全排列的康托展开(Cantor expansion) 任意一种排列在全排列中对应的序号为

∑i=1nai×i!

于是，将输入的两个排列分别写成这种形式，然后遍历n相加，由于结果需要对n!取模，因此从最低位开始逐项将ai加到ai+1上去，最后将最高位的an模掉n即可。之后，只要拟用康托展开即可求出对应的排列。

在实现过程中，由于需要维护"当前还没有使用过的第k大的数"，因此可以用树状数组BIT维护。恢复排列时用树状数组＋二分即可。

复杂度O(n(logn)^2)
```cpp
#include<cstdio>
#include<cstring>
#define read(num) scanf("%d",&num)
using namespace std;
const int Maxn = 200000+10;
int n,a[Maxn],b[Maxn],f[Maxn];

{
int c[Maxn];
#define lowbit(x) (x & -x)
void upd(int x,int val){
	for(int i = x; i <= n; i += lowbit(i))c[i] += val;
}
int sum(int x){
	int ret = 0;
	for(int i = x;i;i -= lowbit(i))ret += c[i];
	return ret;
}
void init(){
	memset(c,0,sizeof(c));
	for(int i = 1;i <= n;i++)upd(i,1);
}
}

int main()
{
	read(n);
	for(int i = 1;i <= n;i++){read(a[i]);a[i] ++;}
	for(int i = 1;i <= n;i++){read(b[i]);b[i] ++;}
	init();
	for(int i = 1;i < n;i++){
		int les = sum(a[i] - 1);
		f[n - i] += les;
		upd(a[i],-1); 
	}
	init();
	for(int i = 1;i < n;i++){
		int les = sum(b[i] - 1);
		f[n - i] += les;
		upd(b[i],-1); 
	}
	for(int i = 1;i < n;i++){
		f[i+1] += f[i] / (i+1);
		f[i] = f[i] % (i+1);
	}
	init();
	int sml = 1;
	for(int i = n-1; i >= 1;i--){
		int l = 1,r = n,mid,tmp,ans = -1;
		while( l <= r){
			mid = (l + r) >> 1;
			tmp = sum(mid - 1);
			if(tmp <= f[i]){
				l = mid + 1;
				ans = mid;
			}
			else r = mid -1;
		}
		if(ans == -1)ans = sml;
		printf("%d ", ans - 1);
		upd(ans,-1);
		while(!c[sml])sml ++;
	}
	for(int i=1; i<=n; i++)    
        if(c[i]){
            printf("%d\n", i-1);  
            break;  
        } 
    return 0;  
}
```

---

## 作者：naroto2022 (赞：1)

# CF501D 题解

###### 这题应该不止绿吧……

### 题面

[原题传送门](https://www.luogu.com.cn/problem/CF501D)

[原题传送门（CF）](https://codeforces.com/problemset/problem/501/D)

### 思路

相信大家都学过[康托展开](https://www.luogu.com.cn/problem/P5367)了吧，应该都知道康托展开的排名为 $\begin{aligned}\sum_{i=1}^n s_i\times(n-i)!\end{aligned}$，其中 $\begin{aligned}s_i\gets\sum_{j=i+1}^n [a_j<a_i]\end{aligned}$。

把两个序列的排名都求出来显然是不现实的，可以考虑先求出两个序列的 $s$，记为 $s1,s2$，在合并 $s$，最后再用[这题](https://www.luogu.com.cn/problem/UVA11525)的方法来解题，可以参考[同样是我写的题解](https://www.luogu.com.cn/article/l6s89pqv)。

那么，该怎么正确的合并呢？直接相加显然是错误的，考虑到 $s_i\leqslant n-i$，所以可以从后往前加，多余的部分是可以进位到上一个字符的，对于第一位直接模 $n$ 即可。

形式化的有：

- $i\geqslant2,s_{i-1}\gets s_{i-1}+\lfloor\frac{s_i+s1_i+s2_i}{n-i+1}\rfloor,s_i\gets(s1_i+s2_i)\bmod (n-i+1)$
- $i=1,s_1\gets(s_1+s1_i+s2_i)\bmod n$

形象点，可以把这个过程理解成我们的竖式加法，因为同样的都是可以进位的，十进制逢十进一，这里是只要大于等于 $n-i+1$ 就要进位。

最后就可以得出 $s$，然后正常逆向康托即可。

这个很好办，用树状数组加二分，我们可以从前往后一个一个确定 $a$。

$S_i$ 就为比 $i$ 小并且未被确定的数的个数。

在逐步确定 $a$ 过程中，对于每个 $i\in\{1,2,\cdots,n\}$，比 $i$ 小并且未被确定的数的个数满足单调性，于是就可以二分求 $a_i$，然后标上 $a_i$ 已被标记（在树状数组中把 $a_i$ 位置减一）。

时间复杂度为 $O(n\log^2 n)$，用线段树上二分可以优化到 $O(n\log n)$，但是笔者太懒（菜）了，只打了树状数组（反正能过就行）。

### 代码

[提交记录](https://codeforces.com/problemset/submission/501/296793334)

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;
const int MN=2e5+5;
ll n,a[MN],s1[MN],s2[MN],s[MN],t[MN];
void write(ll n){if(n<0){putchar('-');write(-n);return;}if(n>9)write(n/10);putchar(n%10+'0');}
ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
ll lowbit(ll x){return x&-x;}
void change(ll x, ll v){while(x<=n){t[x]+=v;x+=lowbit(x);}}
ll query(ll x){ll res=0;while(x){res+=t[x];x-=lowbit(x);}return res;}
ll get(ll x){
    ll l=1,r=n+1,res;
    while(l<r){
        ll mid=l+r>>1,num=query(mid-1);
        if(num>x) r=mid;
        else l=mid+1;
    }
    return l-1;
}
int main(){
    n=read();
    for(int i=1; i<=n; i++) a[i]=read()+1,change(i,1);
    for(int i=1; i<=n; i++){s1[i]=query(a[i]-1);change(a[i],-1);}
    for(int i=1; i<=n; i++) a[i]=read()+1,change(i,1);
    for(int i=1; i<=n; i++){s2[i]=query(a[i]-1);change(a[i],-1);}
    for(int i=n-1; i>=2; i--){
        s[i]+=s1[i]+s2[i];
        if(s[i]>=n-i+1){
            s[i-1]+=s[i]/(n-i+1);
            s[i]%=(n-i+1);
        }
    }
    (s[1]+=s1[1]+s2[1])%=n;
    for(int i=1; i<=n; i++) change(i,1);
    for(int i=1; i<=n; i++){
        a[i]=get(s[i]);
        change(a[i],-1);
    }
    for(int i=1; i<=n; i++) write(a[i]-1),putchar(' ');putchar('\n');
    return 0;
}
```

---

## 作者：DengDuck (赞：1)

# 如何合并数组

首先，我们需要使用康托展开的思想，康托展开是这样的，对于一个没有重复元素的数组，它的字典序排名为：

$$
sum=\sum_{i=1}^nS(i)\times (n-i)!
$$

其中 $S(i)$ 表示第 $i$ 项后面有多少项比它小。

那么根据这个式子，我们合并两个数组就简单多了，用树状数组维护出两个数组的 $S(i)$ 相加即可。

# 如何处理模数

字符串的排名需要 $\bmod n!$，这个真的求出来显然不现实，我们注意到两点：

- $n!$ 恰好是所有排列的方案数。 
- 任意 $S(i)$ 不可能大于 $n-i+1$。

既然 $n!$ 是总方案数，那么大于 $n!$ 的排名一定不合法，我们考虑进位。

这里进位不多赘述了，可以参考代码。

最后，所有数字汇聚在 $S(1)$，由于 $S(1)$ 的系数为 $(n-1)!$，因此我们直接 $S(1)\gets S(1)\bmod n$ 即可。

# 如何转换为数组

思路很简单，从前往后，对于每个数字，它在剩下数字中的排名就是后面比它小的数字的数量加上 $1$。

那么对应的，剩下的数字中从小到大排序，对应排名的数字就是这个位置的数字，我们删除这个数字即可。

这个过程用平衡树很好维护，我写了一个 FHQ Treap，实现没有什么难点。

好吧，事实上，这一段就是我[这个题解](https://www.luogu.com.cn/blog/DengDuck/solution-uva11525)。

# 代码实现

没啥难点，树状数组和 FHQ Treap 也是经典的模样，没有什么需要修改的地方。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=4e5;
LL a[N],cnt[N],b[N],n,tot,rt,x;
LL lowbit(LL x)//树状数组
{
	return x&-x;
}
LL query(LL x)
{
	LL ans=0;
	while(x)
	{
		ans+=b[x];
		x-=lowbit(x);
	} 
	return ans;
}
void update(LL x,LL y)
{
	while(x<=n)
	{
		b[x]+=y; 
		x+=lowbit(x);
	}
}
struct node//平衡树
{
	LL l,r,val,pri,sz;
}t[N];
void pushup(LL x)
{
	LL l=t[x].l,r=t[x].r;
	if(x)t[x].sz=t[l].sz+t[r].sz+1;
}
void split(LL rt,LL &lrt,LL &rrt,LL x)
{
	LL l=t[rt].l,r=t[rt].r;
	if(rt==0)lrt=0,rrt=0;
	else if(t[rt].val<=x)lrt=rt,split(t[rt].r,t[rt].r,rrt,x);
	else rrt=rt,split(t[rt].l,lrt,t[rt].l,x);
	pushup(rt); 
} 
void merge(LL &rt,LL lrt,LL rrt)
{
	LL l=t[rt].l,r=t[rt].r;
	if(lrt==0||rrt==0)rt=lrt+rrt;
	else if(t[lrt].pri<t[rrt].pri)rt=lrt,merge(t[rt].r,t[rt].r,rrt);
	else rt=rrt,merge(t[rt].l,lrt,t[rt].l);
	pushup(rt);
}
void ins(LL &rt,LL x)
{
	t[++tot]={0,0,x,rand(),1};
	LL rt1,rt2;
	split(rt,rt1,rt2,x);
	merge(rt1,rt1,tot),merge(rt,rt1,rt2); 
}
void del(LL &rt,LL x)
{
	LL rt1,rt2,k;
	split(rt,rt1,rt2,x),split(rt1,rt1,k,x-1);
	merge(k,t[k].l,t[k].r),merge(rt1,rt1,k),merge(rt,rt1,rt2);
}
LL kth(LL rt,LL x)
{
	LL l=t[rt].l,r=t[rt].r;
	if(x<=t[l].sz)return kth(l,x);
	if(t[l].sz+1==x)return t[rt].val;
	return kth(r,x-t[l].sz-1);
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	for(int i=n;i>=1;i--)
	{
		update(a[i]+1,1);
		cnt[i]+=query(a[i]);
	}	
	memset(b,0,sizeof(b));
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	for(int i=n;i>=1;i--)
	{
		update(a[i]+1,1);
		cnt[i]+=query(a[i]);//处理S数组，存在cnt数组
	}	
	for(int i=n;i>=1;i--)
	{
		cnt[i-1]+=cnt[i]/(n-i+1),cnt[i]%=(n-i+1);//进位
	}
	for(int i=0;i<n;i++)ins(rt,i);
	for(int i=1;i<=n;i++)
	{
		LL k=kth(rt,cnt[i]+1);
		printf("%lld ",k);//转换成数组
		del(rt,k);
	}
}
```

---

## 作者：OIer_ACMer (赞：0)

# 题目解析：

本题，根据英文题目，我们可以发现，本题就是给你两个长度为 $n$ 的排列，他们分别是 $ n$ 的第 $a$ 个和第 $b$ 个全排列。输出 $n$ 的第 $a + b$ 再对 $n$ 的阶乘取模的对应的全排列。

因此，我们可以考虑[康托展开](https://baike.baidu.com/item/%E5%BA%B7%E6%89%98%E5%B1%95%E5%BC%80/7968428?fr=ge_ala)来思考，根据康拓展开，任意一个全排列在其所有全排列的序号是：

$$\sum_{i=1}^{n}{a}_{i}\times i!$$

那么，我们可以将输入进去的两个排列分别携程这个形式，再遍历 $n$ 并相加，最终，结果要对 $n!$ 取模，因为，我们要从最低位一项一项地将 $a_i$ 加到 $a_i + 1$ 上去，最后将最高位的 $a_n$ 取模消掉多加的部分即可。

在实现过程中，由于需要维护“当前还没有使用过的第k大的数”，因此可以用树状数组维护。恢复排列时用树状数组和二分即可。

# 代码如下：

```

#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int N = 200010;
const int bit_maxn = N;
int la[N], lb[N], a[N], b[N], f[N], s[N];
typedef int bit_type;
int n;
int ff[N];
bit_type tree[bit_maxn];
inline int lowbit(int x)
{
    return x & (-x);
}
void add(int x, int d)
{
    x++;
    while (x <= n)
    {
        tree[x] += d;
        x += lowbit(x);
    }
}
bit_type sum(int x)
{
    x++;
    bit_type ans = 0;
    while (x)
    {
        ans += tree[x];
        x -= lowbit(x);
    }
    return ans;
}
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> la[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> lb[i];
    }
    memset(tree, 0, sizeof(tree));
    for (int i = 0; i < n; i++)
    {
        add(i, 1);
    }
    for (int i = 0; i < n; i++)
    {
        a[i] = sum(la[i] - 1);
        add(la[i], -1);
    }
    memset(tree, 0, sizeof(tree));
    for (int i = 0; i < n; i++)
    {
        add(i, 1);
    }
    for (int i = 0; i < n; i++)
    {
        b[i] = sum(lb[i] - 1);
        add(lb[i], -1);
        s[i] = a[i] + b[i];
    }
    memset(tree, 0, sizeof(tree));
    for (int i = 0; i < n; i++)
    {
        add(i, 1);
        ff[i] = 1;
    }
    for (int i = n - 1; i > 0; i--)
    {
        s[i - 1] += s[i] / (n - i);
        s[i] %= (n - i);
    }
    s[0] %= n;
    int rr = n - 1;
    for (int i = 0; i < n; i++)
    {
        int r = rr;
        int l = 0;
        while (l < r)
        {
            int mid = l + (r - l + 1) / 2;
            int t = sum(mid - 1);
            if (t <= s[i])
            {
                l = mid;
            }
            else
            {
                r = mid - 1;
            }
        }
        add(l, -1);
        ff[l] = 0;
        if (!i)
        {
            cout << l;
        }
        else
        {
            cout << ' ' << l << endl;
        }
        while (!ff[rr])
        {
            rr--;
        }
    }
    return 0;
}

```

---

## 作者：FChang (赞：0)

不会**康托展开**的出门右转[康托展开](https://www.luogu.com.cn/problem/P5367)。

康托展开的基本公式：$$W=k_1\times n-1!+k_2\times n-2!+…+k_n\times 0!$$。

这道题暴力康托展开，由于没有模数，会直接爆炸，所以考虑每一个 $k_i$ 将 $a$ 和 $b$ 数组的 $k_i$ 算出来后相加再考虑一下进位，最后用二分求出每一位的值就行了（第 $i$ 位为没有出现过的、第 $k_i+1$ 小的数）。

[link](https://codeforces.com/problemset/submission/501/276906327)。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;

int n;

int a[N], b[N];

struct BIT {
	int d[N];
#define lowbit(x) (x&-x)
	void init() {
		for (int i = 0; i <= n; ++i) d[i] = 0;
		return ;
	}
	void add(int x, int k) {
		while (x <= n) d[x] += k, x += lowbit(x);
		return ;
	}
	int query(int x) {
		int res = 0;
		while (x) res += d[x], x -= lowbit(x);
		return res;
	}
} T;

int k[N];

void Cantor_merge(int a[N], int b[N]) {
	T.init();
	for (int i = 1; i < n; ++i) {
		k[i] = a[i] - 1 - T.query(a[i] - 1);
		T.add(a[i], 1);
	}
	T.init();
	for (int i = 1; i < n; ++i) {
		k[i] += b[i] - 1 - T.query(b[i] - 1);
		T.add(b[i], 1);
	}
	for (int i = n; i >= 1; --i) {
		k[i - 1] += (k[i] / max(0LL, n - i + 1));
		k[i] %= max(0LL, n - i + 1);
	}
	T.init();
	for (int i = 1; i <= n; ++i) T.add(i, 1); // 差分 a[i] = sum{a[1]+……+a[i-1]}
	for (int i = 1; i <= n; ++i) {
		k[i]++;//求第k[i]大从1开始，所以整体+1
		int l = 1, r = n, mid, res;
		while (l <= r) {
			mid = (l + r) >> 1;
			if (T.query(mid) <= k[i]) res = mid, l = mid + 1;
			else r = mid - 1;
		}
		// 二分出来的答案一定是T.query(mid)=k[i]且是最右边的那一个
		T.add(res + 1, -1); // 差分修改（这样可以让a[res+1]=a[res]）又因为取的是最右边的那一个所以一定去的是a[res+1],如果a[res+1]也被操作过了那么取得也一定是没有被操作过的（即最右边的）
		cout << (res - 1LL) << " ";
	}
	return void(cout << "\n");
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i], a[i]++;
	for (int i = 1; i <= n; ++i) cin >> b[i], b[i]++;
	Cantor_merge(a, b);
	return 0;
}

/*
3
1 3 2  2
1 3 2  2
*/
```

---

## 作者：Zkl21 (赞：0)

### [CF501D](https://www.luogu.com.cn/problem/CF501D)

如果你还不会**康托展开**，或者想要更好的用户体验，欢迎莅临本蒟蒻的[博客](https://www.cnblogs.com/week-end/articles/17572096.html)，如果你还不会**平板电视**，也可以参考一下[蒟蒻的博客](https://www.cnblogs.com/week-end/articles/17575966.html)。

#### 思路
本题也是一道需要对康托展开的式子比较熟悉才能做出来的题目，不难看出这个 $n!$ 很恶心，同时 $n\le 2\times10^5$ 的数据范围也不允许我们直接计算结果。因此，对于本题我们需要做一下转换。

借用上一题题目给出的式子:
$$
\sum_{i=1}^KS_i\times(K-i)!
$$
可以发现，对于本题来说仍然有效。

我们下标从 $1$ 开始，假设第一个排列为 $a$，第二个排列为 $b$，我们要求的排列为 $c$，我们就可以得到：
$$
\sum_{i=1}^nc_i\times(n-i)!=\sum_{i=1}^na_i\times(n-i)!+b_i\times(n-i)!
=\sum_{i=1}^n(a_i+b_i)\times(n-i)!
$$
因此 $c_i=a_i+b_i$，我们就可以通过简单的加和得到 $c_i$。

接下来我们再来处理 $n!$，显然我们会因为庞大的数据范围而无法直接计算。但是我们发现**对于 $n$ 个数的排列，最多也只有 $n!$ 种**。因此如果一种方案超出 $n!$，说明它一定是**不合法**的，某些数超出了我们设定的范围。因此我们可以通过**进位**的方式来解决，这种方式及其巧妙，使得我们可以不用算出 $n!$ 的大小就可以解决问题（~~蒟蒻当时就是因为没想到应该怎么转化才没做出来这题~~）。

最后就是简单的逆康托展开求出排列了，特别的，本题的排列是从 $0$ 开始的，因此处理的时候边界问题可能会有些繁琐。

#### 代码实现

还是老套路，~~只用码量小的平板电视和树状数组~~，注释应该比较清楚，这里就不再解释啦。
```cpp
#include<iostream>
using namespace std;
//———————————————————————————————————————平板电视红黑树的命名start
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>rbt;
//———————————————————————————————————————平板电视红黑树的命名end
typedef long long ll;
const int N=2e5+10;
int n,a[N],b[N];//a存储输入的两个数组,b存储新数组
//———————————————————————————————————————树状数组start
ll t[N];
#define lowbit(x) ((x)&-(x))
void add(int a,int x)
{
    for(int i=a;i<=n;i+=lowbit(i))t[i]+=x;
}
ll query(int a)
{
    ll res=0;
    for(int i=a;i;i-=lowbit(i))res+=t[i];
    return res;
}
//———————————————————————————————————————树状数组end
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=n;i;i--)
    {
        add(a[i]+1,1);//注意将下标+1，否则会引发数组越界
        b[i]=query(a[i]);//存储查询结果
    }
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)add(i,-1);//恢复树状数组
    for(int i=n;i;i--)
    {
        add(a[i]+1,1);
        b[i]+=query(a[i]);
    }
    for(int i=n;i;i--)
	{
		b[i-1]+=b[i]/(n-i+1);//借鉴了DengDuck大佬的代码思路
		b[i]%=(n-i+1);//处理进位问题
	}
    for(int i=0;i<n;i++)rbt.insert(i);//先将所有元素加入红黑树中
    for(int i=1;i<=n;i++)
    {
        auto it=rbt.find_by_order(b[i]);//找第b[i]大的元素
        cout<<*it<<' ';
        rbt.erase(it);
    }
    return 0;
}
```

---

