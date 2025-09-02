# Shorten the Array

## 题目描述

一个长度为 $m$ 的数组 $b$ 的美观度定义为所有可能数对 $1 \le i \le j \le m$ 中 $b_i \oplus b_j$ 的最大值，其中 $x \oplus y$ 表示数字 $x$ 和 $y$ 的[按位异或](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。我们将数组 $b$ 的美观度记为 $f(b)$。

如果一个数组 $b$ 满足 $f(b) \ge k$，则称该数组是美观的。

最近，Kostya 从商店购买了一个长度为 $n$ 的数组 $a$。他认为这个数组太长了，因此计划从中截取一个美观的子数组。也就是说，他需要选择两个数字 $l$ 和 $r$（$1 \le l \le r \le n$），使得子数组 $a_{l \dots r}$ 是美观的。这样的子数组的长度为 $r - l + 1$。整个数组 $a$ 也被视为一个子数组（此时 $l = 1$ 且 $r = n$）。

你的任务是找出数组 $a$ 中最短美观子数组的长度。如果不存在美观的子数组，则输出 $-1$。

## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
6
5 0
1 2 3 4 5
5 7
1 2 3 4 5
5 8
1 2 3 4 5
5 7
3 5 1 4 2
5 3
3 5 1 4 2
6 71
26 56 12 45 60 27```

### 输出

```
1
2
-1
4
2
-1```

# 题解

## 作者：DengStar (赞：6)

套路性地想到用 01-Trie 维护二进制数来解决这类问题。具体而言有两种方法：

## 方法 I

这是官方题解的做法。

寻找两个整数，使得它们的异或和最大，这是经典问题。但在本题中，我们不需要异或和最大，而只需要不小于某个阈值 $k$。把 $\ge k$ 这个条件看作：存在某个位置 $i$，使得 $x \oplus y$ 和 $k$ 从最高位到第 $i + 1$ 位都相同，而 $x \oplus y$ 的第 $i$ 位大于 $k$ 的第 $i$ 位（显然 $k$ 的第 $i$ 位只能为 $0$）；或者 $x \oplus y = k$。

因此我们可以枚举 $i$ 来计算答案。具体而言，在 Trie 上维护每个节点的子树中元素编号的最大值。查询答案时，从高位到低位枚举 $i$，沿着 $x \oplus k$ 的路径走。如果 $k$ 的第 $i$ 位为 $0$，那么尝试更新答案。

记 $w = \max a_{i}$，时间复杂度 $O(n \log w)$。[AC 记录](https://codeforces.com/contest/2093/submission/314818569)

```cpp
int query(int x) {
    int u = 1, res = -1;
    for(int i = w; i >= 0; i--) {
        int x_bit = (x >> i) & 1;
        int k_bit = (k >> i) & 1;
        if(k_bit == 1) {
            if(!t[u][x_bit ^ 1]) {
                return res;
            }
            u = t[u][x_bit ^ 1];
        } else {
            if(t[u][x_bit ^ 1]) {
                res = max(res, mx[t[u][x_bit ^ 1]]);
            }
            if(!t[u][x_bit]) {
                return res;
            }
            u = t[u][x_bit];
        }
    }
    res = max(res, mx[u]);
    return res;
}
```

## 方法 II

这是 jiangly 的双指针做法。

为了方便，称满足 $a_i \oplus a_j \ge k$ 的二元组 $(i, j)$ 为“好的”。

逐个在 Trie 上加入 $a_i$，同时维护一个指针 $j$，初始为 $1$。在 Trie 上查询使得 $a_i \oplus y$ 最大的 $y$，如果 $a_i \oplus y \ge k$，则说明 $[j, i]$ 区间中有一个好的对，因此答案至多为 $i - j + 1$。然后在 Trie 上**删除** $a_j$，令 $j$ 右移一位，继续查询。重复这个过程直到 $j = i$ 或 $[j, i]$ 区间内不存在好的对为止。

```cpp
for(int i = 1, j = 1; i <= n; i++) {
    while(j <= i && tr.query(a[i]) >= k) {
        ans = min(ans, i - j + 1);
        tr.add(a[j], -1);
        j++;
    }
    tr.add(a[i], 1);
}
```

为什么这是正确的？如果 $(j, i)$ 是一个好的对，则答案至多为 $i - j + 1$。当 $i \gets i + 1$ 时，$[1, j]$ 中的元素到 $i$ 的距离都不小于 $i - j + 1$ 了，可以直接忽略。因此我们删除 $a_j$ 是正确的。

由于每个元素都被加入 Trie 一次，从 Trie 上删除至多一次，因此时间复杂度也是 $O(n \log w)$。[AC 记录](https://codeforces.com/contest/2093/submission/314760485)

---

## 作者：I_will_AKIOI (赞：2)

发现最优区间的两个端点的异或值肯定 $\ge k$，否则就可以通过缩小这个区间使答案更优。

因此我们从大到小枚举区间右端点 $r$，找到一个最大的 $l$，使得 $a_l\oplus a_r\ge k$。

我们知道求数组中两两异或最大值可以使用 01trie 维护。这个题也是一样，在枚举 $r$ 的过程中把 $a_r$ 加入到 01trie 中然后查询 $a_r$ 和谁异或 $\ge k$。

接着考虑如何查询。仿照求两两异或最大值的例子，我们从高位到低位枚举二进制位，记录当前异或结果 $res$，当前找到的最大的 $l$ 为 $maxx$。下文相同的一位定义为和 $a_r$ 二进制下第 $i$ 位相同，相反的一位反之。

+ 第 $i$ 位为叶子，直接返回答案。

+ 否则有地方可以走，我们首选和 $a_r$ 第 $i$ 位相反的。

  + 如果 $res+2^i<k$，那么走相反的一位肯定不劣。
 
  + 但是如果 $res+2^i\ge k$，那么我们可以选择走相反的一位，使得 $res\ge k$，满足要求。也可以选择走相同的一位，看看接下来有没有机会让答案更小。那么记录一下 $pos_{rt}$ 表示字典树以 $rt$ 为根的子树内被加入的数在 $a$ 数组中下标最大值。让 $maxx$ 和相反的一位的子树内的答案取 $\max$。接着走相同的一位尝试更小的答案。

+ 没有相反的儿子，只能走相同的。那么直接走就可以，对答案没有影响。
 
```cpp
#include<bits/stdc++.h>
#define N 200005
#define M 30
#pragma GCC optimize("O3")
using namespace std;
int n,m,ans,a[N];
struct Trie
{
	int t[N*M][2],pos[N*M],cnt;
	void clear()
	{
		for(int i=1;i<=cnt;i++) t[i][0]=t[i][1]=pos[i]=0;
		cnt=1;
		return;
	}
	void insert(int x,int y)//插入一个数，数值为 x，下标为 y
	{
		int rt=1;
		for(int i=M;i>=0;i--)
		{
			bool now=(x&(1<<i));
			if(!t[rt][now]) t[rt][now]=++cnt;
			rt=t[rt][now];
			pos[rt]=max(pos[rt],y);//子树内下标最大值
		}
		return;
	}
	int query(int x)//返回满足 a[l]^a[r]>=k 的最大的 l
	{
		int rt=1,res=0,maxx=-1;
		for(int i=M;i>=0;i--)
		{
			bool now=(x&(1<<i));
			if(t[rt][now^1])//可以走相反的一位
			{
				if((res+(1<<i))>=m) maxx=max(maxx,pos[t[rt][now^1]]),rt=t[rt][now];//能找到答案，走相同的一位
				else rt=t[rt][now^1],res+=(1<<i);//不能达到要求，走相同的一位
			}
			else if(t[rt][now]) rt=t[rt][now];//走不了相反的
			else break;//叶子结点
		}
		return maxx;
	}
}t;
void solve()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	if(m==0) {cout<<1<<"\n";return;}//特判
	ans=1e9;
	t.clear();
	for(int i=1;i<=n;i++)
	{
		t.insert(a[i],i);
		int res=t.query(a[i]);
		if(res!=-1) ans=min(ans,i-res+1);
	}
	if(ans==1e9) cout<<-1<<"\n";
	else cout<<ans<<"\n";
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：IGpig (赞：1)

## CF2093G

### Solution

参考了上面大佬的做法。

看到子串，想到双指针。因为求任意两个数异或的最大值是字典数的基本操作，比如[这道题](https://loj.ac/p/10050)就是一个 01 字典树的例子。

考虑做法：

- 每次把一个 $a_i$ 加入字典树。
- 记录一个左端点 $j$，每次加入时如果存在一个 $x$ 使 $(a_i \bigoplus x)$ 就把 $j$ 往右移，并且删掉 $a_j$。
- 在移动的过程中记录 $ans=\min(i-j+1)$。

可以发现如果 $a_j=x$ 后删掉 $a_j$ 就不能往前移了，而在删掉 $a_j$ 之后即使还有符合的也已经大于 $ans$，可以不要考虑。



### Code

~~~cpp
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
LL n,t,k,a[500005],ans;
struct trie{
	LL num=1,tr[5000005][2],cnt[5000005];
	inline LL node(){
		LL x=++num;
		tr[x][1]=tr[x][0]=cnt[x]=0;
		return x;
	}
	LL query(LL x){
		LL loc=1,res=0;
		for(int i=32;i>=0;i--){
			LL p=(x>>i)&1;
			if(cnt[tr[loc][p^1]]){
				p=p^1;
			}
			loc=tr[loc][p];
			res|=((p)<<i);
		}
		return res^x;
	}
	void add(LL x){
		LL loc= 1;
        for(int i = 32; i >= 0; i--) {
            LL p = (x >> i) & 1;
            if(!tr[loc][p]) {
                tr[loc][p] = node();
            }
            loc = tr[loc][p];
            cnt[loc]+=1;
        }
	}
	void del(LL x){
		LL loc= 1;
        for(int i = 32; i >= 0; i--) {
            LL p = (x >> i) & 1;
            if(!tr[loc][p]) {
                tr[loc][p] = node();
            }
            loc = tr[loc][p];
            cnt[loc]-=1;
        }
	}
}tree;
int main(){
	cin>>t;
	while(t--){
		ans=1e12;
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>a[i];
		if(k==0){
			cout<<"1\n";
			continue;
		}
		
		tree.num=0,tree.node();
		for(int i=1,j=1;i<=n;i++){
			while(i>=j&&tree.query(a[i])>=k){
				ans=min(ans,LL(i-j+1));
				tree.del(a[j++]);
			}
			tree.add(a[i]);
		}
		cout<<(ans<=n ? ans : -1)<<endl;
	}
	return 0;
}


~~~

---

## 作者：_xguagua_Firefly_ (赞：0)

### 分析

可持久化做法（对于一道绿题是不是太过了）。

我们先来证明一下单调性，只要一个数组满足给定的条件，那包含这个数组的数组一定满足，因为你加了数还是可以选满足条件的那一对。

所以我们可以枚举每个 $b _ {i}$ 作为右端点，然后二分左端点，使得左端点是满足条件的端点中最靠近右端点的。

我们需要求区间异或最大值，那直接上可持久化字典树，时间复杂度 $\Omicron(n \log n \log V)$，$V$ 表示值域大小，反正能过。

### Code

```cpp
#include <bits/extc++.h>
#define int long long
using namespace std;

constexpr int MAXN = 2e5 + 5,U = 30;
struct ARIS
{
    int ch[2];
    int val;
}tree[MAXN * 60];
#define son(rt,v) tree[rt].ch[v]
int cnt,root[MAXN];
inline int newNode()
{
    ++cnt;
    son(cnt,0) = son(cnt,1) = tree[cnt].val = 0;
    return cnt;
}
inline void insert(int rt,int o,int val)
{
    for(int i = U;i >= 0;i--)
    {
        tree[rt].val = tree[o].val + 1;
        if((val >> i) & 1)
        {
            if(!son(rt,1))
                son(rt,1) = newNode();
            son(rt,0) = son(o,0);
            rt = son(rt,1),o = son(o,1);
        }
        else
        {
            if(!son(rt,0))
                son(rt,0) = newNode();
            son(rt,1) = son(o,1);
            rt = son(rt,0),o = son(o,0);
        }
    }
    tree[rt].val = tree[o].val + 1;
}
inline int query(int u,int v,int val)
{
    int res = 0;
    for(int i = U;i >= 0;i--)
    {
        bool t = (val >> i) & 1;
        if(tree[son(v,!t)].val - tree[son(u,!t)].val)
        {
            res |= 1 << i;
            v = son(v,!t),u = son(u,!t);
        }
        else
            v = son(v,t),u = son(u,t);
    }
    return res;
}

int T;
int n,k,a[MAXN];
inline void Solve()
{
    cnt = 0;
    cin >> n >> k;
    for(int i = 1;i <= n;i++)
    {
        cin >> a[i];
        root[i] = newNode();
        insert(root[i],root[i - 1],a[i]);
    }
    int ans = 0x3f3f3f3f3f3f3f3f;
    for(int i = 1;i <= n;i++)
    {
        int l = 1,r = i,mid;
        while(l <= r)
        {
            mid = (l + r) >> 1;
            if(query(root[mid - 1],root[i],a[i]) >= k)
                l = mid + 1;
            else
                r = mid - 1;
        }
        if(l - 1)
            ans = min(ans,i - l + 2);
    }
    cout << ((ans == 0x3f3f3f3f3f3f3f3f) ? -1 : ans) << "\n";
}
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> T;
    while(T--)
       Solve();
}
```

---

## 作者：AK_400 (赞：0)

注意到这个题其实是让你找最近的 $i,j$ 使 $a_i\oplus a_j\ge k$。

使用类似扫描线的做法，从左往右扫，每次把当前数 $x$ 插到 trie 中，查询最大的 $i$ 使得 $a_i\oplus x\ge k$。

可以这样找：

按位从大到小考虑，如果 $k$ 这位是 $0$，那么把与 $x$ 当前位不同的子树记入答案，然后前往 $x$ 当前位相同的子树。

否则前往与 $x$ 当前位不同的子树。

如果可以找到一个位置 $i$ 使得 $a_i\oplus x=k$，那么把 $i$ 也记入答案。

复杂度 $O(n\log a_i)$。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
template<typename T>
inline void read(T &x){x=0;char c=getchar();bool neg=0;while(!isdigit(c)){if(c=='-')neg=1;c=getchar();}while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();if(neg)x=-x;}
#define read2(a,b) read(a),read(b)
#define read3(a,b,c) read2(a,b),read(c)
#define read4(a,b,c,d) read3(a,b,c),read(d)
#define read5(a,b,c,d,e) read4(a,b,c,d),read(e)
#define read6(a,b,c,d,e,f) read5(a,b,c,d,e),read(f)
int n,k,a[200005];
int ch[200005<<5][2],mx[200005<<5],tot;
void pu(int p){
    mx[p]=max(mx[ch[p][0]],mx[ch[p][1]]);
}
void ins(int x,int v){
    int p=0;
    for(int i=29;i>=0;i--){
        mx[p]=max(mx[p],v);
        if(!ch[p][x>>i&1])ch[p][x>>i&1]=++tot;
        p=ch[p][x>>i&1];
    }
    mx[p]=v;
}
int qu(int x,int k){
    int p=0,res=-2e9;;
    for(int i=29;i>=0;i--){
        if(k>>i&1){
            if(!ch[p][(x>>i&1)^1])return res;
            p=ch[p][(x>>i&1)^1];
        }
        else{
            if(ch[p][(x>>i&1)^1])res=max(res,mx[ch[p][(x>>i&1)^1]]);
            if(!ch[p][x>>i&1])return res;
            p=ch[p][x>>i&1];
        }
    }
    res=max(res,mx[p]);
    return res;
}
void slv(){
    for(int i=0;i<=tot;i++)ch[i][0]=ch[i][1]=0,mx[i]=-2e9;
    tot=0;
    read2(n,k);
    for(int i=1;i<=n;i++)read(a[i]);
    int ans=2e9;
    for(int i=1;i<=n;i++){
        ins(a[i],i);
        ans=min(ans,i-qu(a[i],k)+1);
    }
    cout<<(ans==2e9?-1:ans)<<endl;
    return;
}
signed main(){
    int T;read(T);while(T--)
    slv();
    return 0;
}
```

---

