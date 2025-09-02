# [ABC157E] Simple String Queries

## 题目描述

给定长度为n的原字符串与q次操作或询问。其格式如下:

①1 i c: 将第i位字符改为c(c也是字符)。

②2 l r: 询问区间[l,r]内不同字符的个数。



感谢ducati小蒟蒻的翻译

## 样例 #1

### 输入

```
7
abcdbbd
6
2 3 6
1 5 z
2 1 1
1 4 a
1 7 d
2 1 7```

### 输出

```
3
1
5```

# 题解

## 作者：Grisses (赞：6)

[题面](https://www.luogu.com.cn/problem/AT5323)

这题就一个线段树的题。

我们用一个 bitset 存储每一个区间中 26 个字母出现的情况，其余的与普通线段树无区别。对于 1 操作，单点修改就可以了。2 操作的话，就是区间查询。

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
struct ST{//线段树
	struct Node{
		int l,r;
		bitset<26>m;//bitset存储
	}c[2000005];
	void Build(int q,int l,int r){//递归建树
		c[q].l=l,c[q].r=r;
		if(l==r)return;
		int mid=l+r>>1;
		Build(q<<1,l,mid);
		Build(q<<1|1,mid+1,r);
	}
	void Add(int q,int x,char s){
		if(c[q].l==c[q].r){
			c[q].m.reset();//修改叶子区间
			c[q].m[s-'a']=1;
			return;
		}
		int mid=c[q].l+c[q].r>>1;
		if(x<=mid)Add(q<<1,x,s);
		else Add(q<<1|1,x,s);
		c[q].m=c[q<<1].m|c[q<<1|1].m;//修改大区间
	}
	bitset<26> Getsum(int q,int l,int r){//区间查询
		if(l<=c[q].l&&c[q].r<=r)return c[q].m;
		int mid=c[q].l+c[q].r>>1;
		bitset<26>s;
		if(l<=mid)s|=Getsum(q<<1,l,r);
		if(mid<r)s|=Getsum(q<<1|1,l,r);
		return s;
	}
}T;
char c;
int op,l,r;
int main()
{
	scanf("%d\n",&n);
	T.Build(1,1,n);
	for(int i=1;i<=n;i++){
		scanf("%c",&c);
		T.Add(1,i,c);
	}
	scanf("%d",&q);
	cerr<<q<<endl;
	for(int i=1;i<=q;i++){
		scanf("%d%d",&op,&l);
		if(op==1){
			scanf(" %c",&c);
			T.Add(1,l,c);//单点修改
		}
		else{
			scanf("%d",&r);
			printf("%d\n",T.Getsum(1,l,r).count());//输出T.Getsum(1,l,r)返回值中1的个数，即出现了多少不同的字母
		}
	}
	return 0;
}
```

---

## 作者：徐晨轩✅ (赞：5)

# $ \mathtt{Description} $

>给定长度为 $ n $ 的字符串（只有小写英文字母）与 $ q $ 次操作或询问。格式如下:
>
>* $ 1 $ $ i $ $ c $: 将第 $ i $ 位字符改为 $ c $($ c $ 也是字符)。
>
>* $ 2 $ $ l $ $ r $: 询问区间 $ [l,r] $ 内不同字符的个数。

# $ \mathtt{Solution} $

标签：树状数组（$ \mathtt{BIT} $）

难度：普及+/提高（$ \mathtt{Green} $）

分析：这题看上去好像是树状数组的题目，但他要求的是不同字符个数，不是求和。所以需要开 $ 26 $ 个独立的树状数组，每一个存放该字母出现的位置。这样，在询问的时候，直接查询每一个树状数组的 $ [l,r] $ 的和，如果这个和 $ >0 $，那么就把 $ \mathtt{ans} $ 加 $ 1 $，最后输出 $ \mathtt{ans} $ 即可。（[AC记录](https://www.luogu.com.cn/record/55523564)）

（附赠BIT模板，见代码 $ \mathtt{class} $ $ \mathtt{BIT} $ 部分）

# $ \mathtt{Code} $

```cpp
#include<iostream>
#include<vector>
#include<string>
#define int long long
using namespace std; 
template <typename tp>
class BIT {
	private :
		vector<tp> c; // from 1 to N
		unsigned sz;
		tp lowbit(tp x) {
			return x & (-x);
		}

	public :
		BIT() {
		}
		BIT(unsigned _sz) {
			c = vector<tp> (_sz + 1);
			sz= _sz;
		}
		tp getsum(unsigned dx) { // return sum of [1..dx] 
			tp ret = 0;
			while(dx) {
				ret += c[dx];
				dx -= lowbit(dx);
			}
			return ret;
		}
		tp sum(unsigned l,unsigned r) { // return sum of [l..r]
			return getsum(r) - getsum(l - 1);
		}
		tp get(unsigned dx) { // return value[dx]
			return sum(dx,dx);
		}
		tp add(unsigned dx,tp val) { // return after add
			unsigned tmp = dx;
			while(dx <= sz) {
				c[dx] += val;
				dx += lowbit(dx);
			}
			return c[tmp];
		}
		tp change(unsigned dx,tp val) { // return after change
			return add(dx,val - get(dx));
		}
};
int n,m,t,l,r,ans;char c;
string s;BIT<int>bit[26];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);cout.tie(NULL);
	cin >> n >> s >> m;
	s=" "+s; // 使得字符串下标从1开始
	for(int i=0;i<26;i++)bit[i]=BIT<int>(5e5+1); // 使用自定义构造函数初始化BIT
	for(int i=1;i<=n;i++)bit[s[i]-'a'].add(i,1); // 将字符串原始信息写在BIT中
	while(m--) // m组操作/询问
	{
		cin >> t; // 第几种询问
		if(t==1) // 修改s[l]->c
		{
			cin >> l >> c;
			bit[s[l]-'a'].add(l,-1);
			s[l]=c; // 修改
			bit[s[l]-'a'].add(l,1);
		}
		else // 询问区间[l,r]不同字符个数
		{
			ans=0;
			cin >> l >> r;
			for(int i=0;i<26;i++)
				if(bit[i].sum(l,r)) // 如果有这个字符，答案+1
					ans++;
			cout << ans << endl;
		}
	}
	return 0;
}
```


---

## 作者：Awlgot (赞：3)

## 提供一种莫队的做法（挺好想的）

可能是前几周刚学过吧 ... 我看到这题就想到了带修莫队，看到没人写就来写一发。

~~这不就是 P1903 弱化版。。。~~

时间复杂度是 $\mathcal O(n\sqrt{n})$

带修莫队的话，就是在基础莫队上加了个时间轴，分别以 $l$,$r$,$t$ 为第 ``1``,``2``,``3`` 关键字排序。

这里就不细讲了，可以去看 [OIWIKI](https://oi-wiki.org/misc/modifiable-mo-algo/) 。

因为这题不强制在线，所以可做。如果因为 TLE  没法过的话可以调一下块长~

## 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,m,top1,top2,sq,l=1,r=0,ans,now;
char a[N];
int cnt[27],bl[N],Ans[N];
struct node{
	int l,r,t,id;
}e[N]; 
struct edge{
	int p;
	char col;
}ch[N];
bool cmp(node a,node b){
	if(bl[a.l]!=bl[b.l]) return bl[a.l]<bl[b.l];
	if(bl[a.r]!=bl[b.r]) return bl[a.r]<bl[b.r];
	return a.t<b.t;
}
void add(int x){
	cnt[x]++;
	if(cnt[x]==1) ans++;
}
void del(int x){
	cnt[x]--;
	if(cnt[x]==0) ans--;
}
void change(int i,int j){
	if(ch[j].p>=e[i].l&&ch[j].p<=e[i].r){
		del(a[ch[j].p]-'a');
		add(ch[j].col-'a');
	}
	swap(a[ch[j].p],ch[j].col);
}
signed main(){
	std::ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    sq=pow(n,0.666666);
    for(int i=1;i<=n;i++) cin>>a[i],bl[i]=i/sq;
    cin>>m;
    for(int i=1,op,x;i<=m;i++){
    	cin>>op>>x;
    	if(op==2){
    		int y;
    		cin>>y;
    		e[++top1].l=x;
    		e[top1].r=y;
    		e[top1].t=top2;
    		e[top1].id=top1;
		}
		else{
			char y;
			cin>>y;
			ch[++top2].p=x;
			ch[top2].col=y;
		}
	}
	sort(e+1,e+top1+1,cmp);
	for(int i=1;i<=top1;i++){
		while(l<e[i].l) del(a[l++]-'a');
		while(l>e[i].l) add(a[--l]-'a');
		while(r<e[i].r) add(a[++r]-'a');
		while(r>e[i].r) del(a[r--]-'a');
		while(now<e[i].t) change(i,++now);
		while(now>e[i].t) change(i,now--);
		Ans[e[i].id]=ans;
	}
	for(int i=1;i<=top1;i++) cout<<Ans[i]<<"\n";
}

```


---

## 作者：lzyqwq (赞：2)

# AT5323
这题其实是要维护多棵树状数组，我们给每一个字母都用一棵树状数组维护。我使用的是结构体。

```cpp
struct BIT
{
	int c[N];
	int lowbit(int x){return x&-x;}
	void update(int x,int y){while(x<=n)c[x]+=y,x+=lowbit(x);}
	int query(int x){int s=0;while(x)s+=c[x],x-=lowbit(x);return s;}
}t[27];
```

修改操作就是把原来的字母加上 $-1$，并把修改后的字母加上 $1$。

```cpp
if(q==1)
{
	int k;char c;scanf("%d %c",&k,&c);
	t[s[k]-'a'+1].update(k,-1);//先把原来的减掉
   t[c-'a'+1].update(k,1);//再把新来的加上
	s[k]=c;//把当前字符改成 c
}
```

查询操作就是枚举 $26$ 个字母查询 $\texttt{a...z}$ 在 $l$ 至 $r$ 之间的个数。我们可以采用前缀和的思想，用 `query(r)` 减去 `query(l-1)`。如果所得结果不为 $0$，则说明区间内有该字母，`ans++`。

```cpp
else
{
	int l,r,sum=0;
	scanf("%d%d",&l,&r);
	for(int i=1;i<=26;i++)
		if(t[i].query(r)-t[i].query(l-1))sum++;
			printf("%d\n",sum);
}
```

最后奉上我的 AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
char s[N];
int n,m;
struct BIT
{
	int c[N];
	int lowbit(int x){return x&-x;}
	void update(int x,int y){while(x<=n)c[x]+=y,x+=lowbit(x);}
	int query(int x){int s=0;while(x)s+=c[x],x-=lowbit(x);return s;}
}t[27];
int main()
{
	scanf("%d%s%d",&n,s+1,&m);//我把字符串当成字符数组来读
	for(int i=1;i<=n;i++)t[s[i]-'a'+1].update(i,1);//初始化，当前位置上有该字母
	for(int i=1,q;i<=m;i++)
	{
		scanf("%d",&q);
		if(q==1)
		{
			int k;char c;scanf("%d %c",&k,&c);
			t[s[k]-'a'+1].update(k,-1);t[c-'a'+1].update(k,1);
			s[k]=c;
		}
		else
		{
			int l,r,sum=0;
			scanf("%d%d",&l,&r);
			for(int i=1;i<=26;i++)
				if(t[i].query(r)-t[i].query(l-1))sum++;
			printf("%d\n",sum);
		}
	}
	return 0;
}
```

谢谢大家。

---

## 作者：CaiXY06 (赞：2)

我们考虑用线段树维护一段区间内 $26$ 个小写字母的存在情况，然后您就 AC 了这道题。

坑点：

- **push_up,建树,更新** 的时候要记得清空该节点，不然抱铃

- 线段树空间开 $4$ 倍，不然 RE

附上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct SGT{
	bitset<26>c;//用bitset优化常数
}tr[2000010];
int n,ans,q;
char s[500010];
inline void push_up(int p){
	tr[p].c=tr[p<<1].c|tr[p<<1|1].c;
}
inline void build(int p,int l,int r){//建树
	if(l>=r){
		tr[p].c.reset();
		tr[p].c[s[l]-'a']=1;
		return;
	}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	push_up(p);
}
inline void update(int p,int l,int r,int pos,char k){//更新节点信息
	if(l>=r){
		tr[p].c.reset();
		tr[p].c[k-'a']=1;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)update(p<<1,l,mid,pos,k);
	else update(p<<1|1,mid+1,r,pos,k);
	push_up(p);
}
inline SGT query(int p,int l,int r,int L,int R){//询问
	if(l>=L&&r<=R)return tr[p];
	int mid=(l+r)>>1;
	SGT res;res.c.reset();
	if(L<=mid)res.c|=query(p<<1,l,mid,L,R).c;
	if(R>mid)res.c|=query(p<<1|1,mid+1,r,L,R).c;
	return res;
}
int main(){
	scanf("%d%s",&n,s+1);
	build(1,1,n);
	scanf("%d",&q);
	while(q--){
		int opt,x,y;
		char c;
		scanf("%d",&opt);
		if(opt==1){
			scanf("%d",&x);cin>>c;
			update(1,1,n,x,c);
		}
		else{
			scanf("%d%d",&x,&y);
			SGT res=query(1,1,n,x,y);
			ans=0;
			for(int i=0;i<26;i++)if(res.c[i])ans++;
			printf("%d\n",ans);
		}
	}
	return 0;
}
```
然后就获得了最优解。

---

## 作者：_byta (赞：1)

看到题解里有一篇树状数组的，我来补一发线段树

思路： 

由于只有小写字母，我们可以考虑对于每一个字母开一颗线段树

查询时暴力枚举每一种字母，如果在当前位置的线段树上有字母，就把

答案加一，修改时同理，对于当前结点，把输入字符对于的线段树标记为一

其余标记为零，此题空间限制为一千MB，稳过，不用担心超内存

代码：
```cpp
#include <bits/stdc++.h>
#define ll(x) ((x) << 1)
#define rr(x) ((x) << 1 | 1)
using namespace std;

const int T = 31, N = 500010;
int n, t, m, laz[T][N << 2], sum[T][N << 2], a[N];

void pushup(int i, int x) { sum[i][x] = sum[i][ll(x)] + sum[i][rr(x)]; }

void build(int i, int x, int l, int r) {
    if (l == r) {
        sum[i][x];
        return;
    }
    int mid = l + r >> 1;
    build(i, ll(x), l, mid);
    build(i, rr(x), mid + 1, r);
    pushup(i, x);
}

void pushdown(int i, int x) {
    if (laz[i][x] == -1) {
        sum[i][ll(x)] = sum[i][rr(x)] = 0;
        laz[i][ll(x)] = laz[i][rr(x)] = -1;
    } else {
        sum[i][ll(x)] = sum[i][rr(x)] = laz[i][x];
        laz[i][ll(x)] = laz[i][rr(x)] = laz[i][x];
    }
    laz[i][x] = 0;
}

void change(int i, int x, int l, int r, int ls, int rs, int v) {
    if (l > rs || r < ls)
        return;
    if (l >= ls && r <= rs) {
        sum[i][x] = v;
        if (v == 0)
            laz[i][x] = -1;
        else
            laz[i][x] = v;
        return;
    }
    if (laz[i][x])
        pushdown(i, x);
    int mid = l + r >> 1;
    if (ls <= mid)
        change(i, ll(x), l, mid, ls, rs, v);
    if (rs > mid)
        change(i, rr(x), mid + 1, r, ls, rs, v);
    pushup(i, x);
}

int ask(int i, int x, int l, int r, int ls, int rs) {
    if (l > rs || r < ls)
        return 0;
    if (l >= ls && r <= rs)
        return sum[i][x];
    if (laz[i][x])
        pushdown(i, x);
    int mid = l + r >> 1;
    return ask(i, ll(x), l, mid, ls, rs) + ask(i, rr(x), mid + 1, r, ls, rs);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        char ch;
        cin >> ch;
        a[i] = int(ch) - 96;
        change(a[i], 1, 1, n, i, i, 1);
    }
    int s;
    int l, r, v;
    cin >> m;
    for (int i = 1; i <= m; i++) {
        char ch;
        cin >> s;
        if (s == 1) {
            cin >> l;
            cin >> ch;
            int v = int(ch) - 96;
            for (int k = 1; k <= 26; k++) {
                if (k != v)
                    change(k, 1, 1, n, l, l, 0);
                else
                    change(k, 1, 1, n, l, l, 1);
            }
        } else {
            cin >> l >> r;
            if (l > r)
                swap(l, r);
            int ans = 0;
            for (int k = 1; k <= 26; k++) {
                if (ask(k, 1, 1, n, l, r))
                    ans++;
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}

```



---

## 作者：洛璟 (赞：1)

虽然写树状数组的大佬说写线段树没有必要，但是

我觉得很有必要，而且线段树也是非常好的一个玩意。

前置芝士：线段树。

## Solution:

看到多次查询、单点修改，区间查询，很快啊，线段树是能够想到的。

那么关键在于如何维护这个区间内不同字符的个数。那么我们可以思考，统计区间的字符出现个数是否可行 ~~（显然可行）~~ 。

同时也得注意，我们单点修改的时候，由于需要统计每一个字符的个数，因此我们也得把左右端点均为 $1$ 的区间的字符给记下来，接下来只需要统计区间字符个数，并且暴力判重即可。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m;
struct cccp
{
    int fg[50];
    char c;
}t[2000010];
bool fg[50];
char c[500010];
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c>'9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ '0');
        c = getchar();
    }
    return x * f;
}
inline void build(int x, int l, int r)
{
    if (l == r)
    {
        t[x].fg[c[l] - 'a']++;
        t[x].c = c[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
    for (int i = 0;i < 26;++i)
    {
        t[x].fg[i] = t[x * 2].fg[i] + t[x * 2 + 1].fg[i];
    }
}
inline int query(int x, int el, int er, int l, int r)//区间查询
{
    int ans = 0;
    if (l >= el && r <= er)
    {
        for (int i = 0;i < 26;++i)//暴力判断是否出现过
        {
            if (t[x].fg[i] != 0 && fg[i] == 0)//若没出现过并且这个区间包含了这个字符
            {
                fg[i] = 1;
                ans++;
            }
        }
        return ans;
    }
    int mid = (l + r) >> 1;
    if (el <= mid)
    {
        ans += query(x * 2, el, er, l, mid);
    }
    if (er > mid)
    {
        ans += query(x * 2 + 1, el, er, mid + 1, r);
    }
    return ans;
}
inline void modify(int x, int e, int l, int r, char k)//修改
{
    if (l == e && r == e)
    {
        t[x].fg[k - 'a']++;//修改后的字符个数加一
        t[x].fg[t[x].c - 'a']--;//原来的字符个数减一
        t[x].c = k;//修改单点字符
        return;
    }
    int mid = (l + r) >> 1;
    if (e <= mid)
    {
        modify(x * 2, e, l, mid, k);
    }
    if (e > mid)
    {
        modify(x * 2 + 1, e, mid + 1, r, k);
    }
    for (int i = 0;i < 26;++i)
    {
        t[x].fg[i] = t[x * 2].fg[i] + t[x * 2 + 1].fg[i];//更新区间和
    }
}
int main()
{
    n = read();
    char ch = getchar();
    while (ch < 'a' || ch>'z')
    {
        ch = getchar();
    }
    for (int i = 1;i <= n;++i)
    {
        c[i] = ch;
        ch = getchar();
    }
    build(1, 1, n);
    m = read();
    while (m--)
    {
        int t = read();
        if (t == 2)
        {
            memset(fg, 0, sizeof(fg));
            int x = read(), y = read();
            printf("%d\n", query(1, x, y, 1, n));
        }
        else
        {
            int x = read();
            char ch;
            cin >> ch;
            modify(1, x, 1, n, ch);
        }
    }
    return 0;
}
```


---

## 作者：pandaSTT (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT5323)

[更好的阅读体验？](https://www.luogu.com.cn/blog/cathyqwq/at5323-abc157e-simple-string-queries-ti-xie)

## 前置知识

**树状数组的单点修改，区间查询**

建议先完成[这道题](https://www.luogu.com.cn/problem/P3374)

## 分析

题目要进行操作或询问，应该立刻联想到数据结构。

题目要询问区间 $ [l,r] $ 内不同字符的个数，首先想到**树状数组离线操作**，但观察题目发现题目中字符一共只有 26 种，因此可以**用 26 个树状数组维护区间内每种字符的出现情况**。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define lowbit(x) x&(-x)
using namespace std;
int n,c[500005][35];
int q,p;
string s;
void add(int x,int y,int p){//p 表示当前维护的是哪种字符
	for(;x<=n;x+=lowbit(x)){
		c[x][p]+=y;
	}
	return;
}
int ask(int x,int p){// p 的意义同上
	int sum=0;
	for(;x;x-=lowbit(x)){
		sum+=c[x][p];
	}
	return sum;
}
//以上为线段树模板
signed main(){
	cin>>n>>s>>q;
	s=' '+s;
	for(int i=1;i<=n;i++){
		add(i,1,s[i]-'a'+1);
	}
	while(q--){
		cin>>p;
		if(p==1){
			int x;
			char y;
			cin>>x>>y;
			if(s[x]==y){
				continue;
			}
			add(x,-1,s[x]-'a'+1);
			s[x]=y;
			add(x,1,s[x]-'a'+1);//树状数组的单点修改
		}
		else{
			int x,y,ans=0;
			cin>>x>>y;
			for(int i=1;i<=26;i++){
				ans+=bool(ask(y,i)-ask(x-1,i));//区间查询，查询每种字符的出现情况
			}
			cout<<ans<<endl;
		}
	}
	return 0;
}
```

## 总结



|分析 |   难度 |
| :-----------: | -----------: |
| **思维难度** | **绿** |
| **代码难度** | **橙** |
| **算法难度** | **黄** |
| **分析难度** | **橙** |
| **综合评估** | **黄** |

---

## 作者：Unnamed114514 (赞：1)

本题训练时没想出来，真是一种莫大的遗憾。
### 思路
首先，看到这道题，我首先想到的是 [HH的项链](https://www.luogu.com.cn/problem/P1972)。但是我们可以发现，那道题是因为没有修改，才能实现离线操作的。所以，本题是在线操作的。

但是，本题还有一个性质，就是我们可以发现：小写字母只有 $26$ 个！

其实，这个策略是非常重要的，我们想到了这儿，就可以用 $26$ 棵树状数组来维护每个字符的数量，这样我们就可以实现在线操作。

然后，就可以用树状数组维护：$num_{i,j}$ 表示 $[1,i]$ 中第 $j$ 个字符出现的次数。修改 $s_i$ 为 $j$ 时，我们就直接 $num_{i,s_i}\gets num_{i,s_i}-1$，同理 $num_{i,j}\gets num_{i,j}+1$。

注意预处理，时间复杂度 $O(n\log n)$，空间复杂度 $O(30\times n)$。
### AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+5;
int n,m,num[maxn][26];
char s[maxn];
namespace Tree{
	#define lowbit(x) x&-x
	inline void Add(int x,int y,int z){
		for(;x<=n;x+=lowbit(x))
			num[x][y]+=z;
	}
	inline int Query(int x,int y){
		int ans=0;
		for(;x;x-=lowbit(x))
			ans+=num[x][y];
		return ans;
	}
}
using namespace Tree;//树状数组模板
int main(){
	scanf("%d\n%s",&n,s+1);
	for(int i=1;i<=n;++i)
		Add(i,s[i]-'a',1);//初始化
	scanf("%d",&m);
	for(int i=1,a,b;i<=m;++i){
		scanf("%d%d",&a,&b);
		if(a^1){
			int c,ans=0;
			scanf("%d",&c);
			for(int i=0;i<26;++i)
				ans+=(Query(c,i)-Query(b-1,i))>0;//查询 ch 是否在 [a,b] 中出现过
			printf("%d\n",ans);
		} else{
			char ch;
			cin>>ch;
			if(s[b]!=ch){
				Add(b,s[b]-'a',-1);
				Add(b,ch-'a',1);//直接在线修改
				s[b]=ch;
			}
		}
	}
	return 0;
} 
```

---

## 作者：FReQuenter (赞：0)

## 思路

考虑开 $26$ 棵树状数组维护 $s_l$ 到 $s_r$ 中每一个字符各有多少，正好单点修改 $s_i$ 对应的那个字母，区间查询 $s_l$ 至 $s_r$ 的每一个字母数量是否大于 $0$。时间复杂度 $O(n \log n)$。

## 代码

```cpp
#include<iostream>
#define lowbit(x) ((x)&(-x))
using namespace std;
int a[500005],c[26][500005];//26棵
void update(int c[],int x,int v){
    for(int i=x;i<=500000;i+=lowbit(i)) c[i]+=v;
}
int getsum(int c[],int x){
    int sum=0;
    for(int i=x;i>=1;i-=lowbit(i)) sum+=c[i];
    return sum;
}
//树状数组
int main(){
    int n,q;
    cin>>n;
    string a;
    cin>>a;
    a='#'+a;
    for(int i=1;i<=n;i++) update(c[a[i]-'a'],i,1);//初始化
    cin>>q;
    while(q--){
        int op;
        cin>>op;
        if(op==1){
            int l;
            string x;
            cin>>l>>x;
            char cc=x[0];
            update(c[a[l]-'a'],l,-1);
            update(c[cc-'a'],l,1);
            a[l]=cc;//单点修改对应的字母
        }
        if(op==2){
            int l,r,ans=0;
            cin>>l>>r;
            for(int i=0;i<26;i++) if(getsum(c[i],r)-getsum(c[i],l-1)) ans++;//区间查询每一个字母
            cout<<ans<<'\n';
        }
    }
}
```

---

## 作者：Hagasei (赞：0)

简单分块。每一块打个桶即可。也没什么细节。

代码有点冗长，将就看罢。

```cpp
#include<bits/stdc++.h>
inline void wr(int s){if(s>9)wr(s/10);putchar((s%10)^48);}
inline void qr(int&x){
  x=0;char ch;
  while(ch=getchar(),ch<'0'||ch>'9');
  while(ch>='0'&&ch<='9')x=x*10+(ch^48),ch=getchar();
}
using namespace std;
inline char gc(){
	char ch;
	while(ch=getchar(),ch==' '||ch=='\n');return ch;
}
int bit[500005],n,m,ton[750][26],s,L[750],R[750],idx[500005],kk[26];
char a[500005];
signed main(){
	s=707;
	cin>>n>>a+1>>m;
	for(int i=1,b=1;i<=n;i+=s,++b){
		L[b]=i;
		R[b]=min(n,i+s-1);
		for(int j=L[b];j<=R[b];++j){
			idx[j]=b;
			ton[b][a[j]-'a']++;
		}
	} 
	for(int p=1;p<=m;++p){
		int op;
		qr(op);
		if(op==1){//简单修改
			int x;char c;
			qr(x),c=gc();
			--ton[idx[x]][a[x]-'a'];
			++ton[idx[x]][c-'a'];
			a[x]=c;
		}
		else{
			int l,r;
			qr(l),qr(r);
			int t=0;
			memset(kk,0,sizeof kk);
			if(idx[l]!=idx[r]){
				for(int i=idx[l]+1;i<idx[r];++i){//整块
					for(int j=0;j<26;++j){
						if(ton[i][j]&&!kk[j]){
							++t;
							kk[j]=1;
						}
					}
				}
				for(int i=l;i<=R[idx[l]];++i){//左散块
					if(kk[a[i]-'a']==0){
						kk[a[i]-'a']=1;
						++t;
					}
				}
				for(int i=L[idx[r]];i<=r;++i){//右散块
					if(kk[a[i]-'a']==0){
						kk[a[i]-'a']=1;
						++t;
					}
				}
			} 
			else{
				for(int i=l;i<=r;++i){//散块
					if(kk[a[i]-'a']==0){
						kk[a[i]-'a']=1;
						++t;
					}
				}
			}
			wr(t);
			putchar('\n');
		}
	}
}
```

---

## 作者：cqbzjyh (赞：0)

分块好像不会被卡。

### Solution.
我们可以用一个 $b$ 数组来记录该块的每种字母的数量。
在每次查询的时候，我们可以新建一个桶，根据分块的基本思想，如果 $l$ 和 $r$ 在同一块，就直接将 $l \sim r$ 之间的字母加入桶。否则就把 $l$ 和 $r$ 之间的块中的字母加入桶。最后枚举一下桶中有多少个不同的字母即可。

时间复杂度 $O(26 × n \sqrt{n})$


### Code.

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;
const int maxn = 1e6 + 5;
int n, q;
char s[maxn];
int op, l, r;
int pos[maxn], L[maxn], R[maxn];
int b[maxn][301];
int len, tot;
void init() {//分块
	len = sqrt(n);
	for (int i = 1; i + len <= n; i += len) {
		L[++tot] = i;
		R[tot] = i + len - 1;
	}
	if (R[tot] < n) {
		tot++;
		L[tot] = R[tot - 1] + 1;
		R[tot] = n;
	}
	for (int i = 1; i <= tot; i++) {
		for (int j = L[i]; j <= R[i]; j++) {
			pos[j] = i;
			b[i][s[j]]++;
		}
	}
}
void updata(int x, char c) {//单点修改
	b[pos[x]][s[x]]--;	
	s[x] = c;
	b[pos[x]][c]++; 
} 
bool p[301];
int ask(int l, int r) {
	int t1 = pos[l], t2 = pos[r], ans = 0;
	if (t1 == t2) {//如果在同一块
		memset(p, 0, sizeof(p));
		for (int i = l; i <= r; i++) {//直接将 l-r 加入
			if (!p[s[i]]) {
				p[s[i]] = true;
				ans++;
			}
		}
	} else {
		memset(p, 0, sizeof(p));
		for (int i = l; i <= R[t1]; i++) {
			if (!p[s[i]]) {
				p[s[i]] = true;
				ans++;
			}
		}
		for (int i = t1 + 1; i <= t2 - 1; i++) {//将块中的字母加入桶
			for (int j = 'a'; j <= 'z'; j++) {
				if (b[i][j] != 0) {
					if (!p[j]) {
						ans++;
						p[j] = true;
					}
				}
			}
		}
		for (int i = L[t2]; i <= r; i++) {
			if (!p[s[i]]) {
				p[s[i]] = true;
				ans++;
			}
		}
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> s[i];
	init();
	cin >> q;
	while (q--) {
		cin >> op;
		if (op == 1) {
			char c;
			cin >> l >> c;
			updata(l, c);
		} else if (op == 2) {
			cin >> l >> r;
			printf("%d\n", ask(l, r));
		}
	}
	return 0;
} 
```

---

## 作者：TulipeNoire (赞：0)

这道题求区间元素种数，转化一下，就是把每种元素是否出现记录下来，然后求和。可以发现元素只有 $26$ 种，用 $int$ 类型的二进制表示就可以存储。

再看，题目要求单点修改，区间修改，这不就是线段树吗？一个线段树用一个整数存二十六种字符是否出现过，那么用位运算中的 `|` 与 `<<` 运算就可以实现这个操作。

时间复杂度 $O(n\log n)$,空间复杂度 $O(4\times n)$。

**code**:

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 500005;
int n, q;
char a[N];
int val[4 * N];
inline void pushup(int p) {
    val[p] = val[p << 1] | val[p << 1 ^ 1];
    return;
}
void build(int p, int l, int r) {
    if (l == r) {
        val[p] = 1 << (a[l] - 'a');
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 ^ 1, mid + 1, r);
    pushup(p);
    return;
}
void upd(int p, int l, int r, int x, int d) {
    if (l == r) {
        val[p] = 1 << d;
        return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid)
        upd(p << 1, l, mid, x, d);
    if (x > mid)
        upd(p << 1 ^ 1, mid + 1, r, x, d);
    pushup(p);
    return;
}
int get(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return val[p];
    }
    int mid = (l + r) >> 1, res = 0;
    if (L <= mid)
        res |= get(p << 1, l, mid, L, R);
    if (R > mid)
        res |= get(p << 1 ^ 1, mid + 1, r, L, R);
    return res;
}
int main() {
    scanf("%d", &n);
    scanf("%s", a + 1);
    build(1, 1, n);
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int opt;
        int l, r, x;
        char c;
        scanf("%d", &opt);
        if (opt & 1) {
            scanf("%d %c", &x, &c);
            upd(1, 1, n, x, c - 'a');
        } else {
            scanf("%d %d", &l, &r);
            int res = get(1, 1, n, l, r), cnt = 0;
            while (res) {
                cnt += res & 1;
                res >>= 1;
            }
            printf("%d\n", cnt);
        }
    }
    return 0;
}
```

---

