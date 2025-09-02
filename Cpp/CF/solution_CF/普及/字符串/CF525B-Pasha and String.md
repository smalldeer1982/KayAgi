# Pasha and String

## 题目描述

Pasha got a very beautiful string $ s $ for his birthday, the string consists of lowercase Latin letters. The letters in the string are numbered from 1 to $ |s| $ from left to right, where $ |s| $ is the length of the given string.

Pasha didn't like his present very much so he decided to change it. After his birthday Pasha spent $ m $ days performing the following transformations on his string — each day he chose integer $ a_{i} $ and reversed a piece of string (a segment) from position $ a_{i} $ to position $ |s|-a_{i}+1 $ . It is guaranteed that $ 2·a_{i}<=|s| $ .

You face the following task: determine what Pasha's string will look like after $ m $ days.

## 样例 #1

### 输入

```
abcdef
1
2
```

### 输出

```
aedcbf
```

## 样例 #2

### 输入

```
vwxyz
2
2 2
```

### 输出

```
vwxyz
```

## 样例 #3

### 输入

```
abcdef
3
1 2 3
```

### 输出

```
fbdcea
```

# 题解

## 作者：luoguwyc12345 (赞：4)

逛了下题解发现有许多大佬用差分做，但本蒟蒻想不到差分，于是只能纯模拟了 qwq

## 题目大意：

给定一个字符串 $s$，对其进行 $m$ 次操作，第 $i$ 次操作给一个数字 $a_i$，表示将字符串 $s$ 的第 $x$ 个位置到第 $len - x + 1$ 这段字翻转，求 $m$ 次操作后的结果。

## 思路与实现：

本题要求从 $x$ 到 $len - x + 1$ 的位置调换，那我们可以分别处理前半部分和后半部分：每读入一个 $a_i$ 就判断这个 $a_i$ 是在字符串的前半部分还是后半部分，如果是后半部分就从字符串的一半开始模拟，否则就从字符串的开头开始模拟，每次判断如果 $a_i > j$ 就交换 $a_i$ 和 $a_{len-i+1}$ 的位置，最后输出得到的字符串即可。

具体而言，实现时可以按照以下步骤进行：

读入字符串 $s$ 和操作次数 $m$；

对于每次操作，读入数字 $a_i$，并根据其在前半部分还是后半部分进行模拟；
 
对于每次模拟，从头或尾开始遍历字符串 $s$，对于位置 $i$，如果 $i \le j$，则直接跳过；

否则，交换 $s_i$ 和 $s_{len-i+1}$ 的位置；重复步骤 $2$-$3$，直到进行完 $m$ 次操作；输出最终得到的字符串。

这里就不放全部代码了，只放模拟前半部分的函数了：

## 部分代码
```cpp
void str_ans1(){
	for(int i=0;i<b;i++){
		for(int j=0;j<=c;j++){
			if(a[i]-1<=j){//因为题目中是按第一个字母是a[1]来作为输入参照的，但字符串输入默认是从a[0]开始，所以判断时要-1
				swap(q[j],q[d-j+1]);
			}
		}
	}
	return;
}
//在上述代码中：q是输入也是目标字符串，b为操作次数，a[i]为每一次操作需要翻转的位置，d是字符串q的长度，c=d/2
```


---

## 作者：XXh0919 (赞：1)

好久没写题解了，来水一波。

### 解法

这个题其实很简单。我们可以将这个字符串看成一个 $01$ 串，如果输入中要对这个位置进行修改，就把这个位置赋值成 $1$。通过找规律，在修改的时候我们只需要看需要修改的这个位置的前一个位置是否是 $1$，是的话就跳过，否则就修改。

因为修改的是对称的，所以我们遍历前半个字符串就行了。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
#define pi pair<int,int>
#define mkp(a,b) make_pair((a),(b)) 
#define IOS cin.tie(0)->sync_with_stdio(0)
using namespace std;
const int N = 1e6 + 15;

char s[N];
int t;
int a[N];

signed main () {
	scanf ("%s", s + 1);
	cin >> t;
	int len = strlen (s + 1);
	while (t --) {
		int x;
		cin >> x;
		a[x] ^= 1;
	}
	rep (i, 1, len/2) {
		a[i] ^= a[i-1];
		if (a[i]) swap (s[i], s[len - i + 1]);
	}
	rep (i, 1, len) cout << s[i];
	return 0;
}
```

---

## 作者：jzjr (赞：1)

## 题目翻译：

给你一个字符串 $s$，每次输入一个数 $x$，然后将 $x\sim(|s|-x+1)$ 的字符反转，操作共 $m$ 次。$|s|,m\leq10^5$。

## 前置知识：

* 线段树。
* 位运算。

## 思路：

反转 $x\sim(|s|-x+1)$ 这个操作应该是本题的解法来源，从这方向下手。

发现如果 $x\sim(|s|-x+1)$ 被反转了，等价于 $(x+1)\sim(|s|-(x+1)+1)$ 反转和 $x,|s|-s+1$ 两个字符被反转。

记 $l=\lfloor\frac{|s|}{2}\rfloor$，$A_i$ 表示 $i,(|s|-i+1)$ 有无被反转，则每次的操作等价于将 $A_x\sim A_l$ 反转。

这个操作可以由线段树来维护。

## 实现：

线段树维护以下元素。

- 区间 $1$ 个数。
- 区间是否被反转。

建树初始全部为 $0$ 即可。

#### 下放 & 修改操作：

显然，两次反转等价于没有反转。

将区间 $1$ 个数取反即可。

```cpp
inline void push(int p){
	if(!t[p].tag)return ;
	t[p<<1].sum=t[p<<1].len-t[p<<1].sum;
	t[p<<1|1].sum=t[p<<1|1].len-t[p<<1|1].sum;
	t[p<<1].tag^=1;t[p<<1|1].tag^=1;t[p].tag=0;
}
inline change(int l,int r,int p){
	if(t[p].l>=l&&t[p].r<=r){
		t[p].sum=t[p].len-t[p].sum;t[p].tag^=1;
		return ;
	}
	else if(t[p].r<l||t[p].l>r)return ;
	else {
		push(p);
		change(l,r,p<<1);
		change(l,r,p<<1|1);
		t[p].sum=t[p<<1].sum+t[p<<1|1].sum;
	} 
}
```

其他的操作都是模版。

最后单点查询某一对有无反转，输出即可。

## code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+5;
string s;
int n,m,l;
struct segtree{
	int l,r,len,sum,tag;
}t[N<<2];
inline void build(int l,int r,int p){
	t[p].l=l;t[p].r=r;t[p].len=r-l+1;
	if(l==r)return ;
	int mid=(l+r)>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
}
inline void push(int p){
	if(!t[p].tag)return ;
	t[p<<1].sum=t[p<<1].len-t[p<<1].sum;
	t[p<<1|1].sum=t[p<<1|1].len-t[p<<1|1].sum;
	t[p<<1].tag^=1;t[p<<1|1].tag^=1;t[p].tag=0;
}
inline void change(int l,int r,int p){
	if(t[p].l>=l&&t[p].r<=r){
		t[p].sum=t[p].len-t[p].sum;
		t[p].tag^=1;
		return ;
	}
	else if(t[p].r<l||t[p].l>r)return ;
	else {
		push(p);
		change(l,r,p<<1);
		change(l,r,p<<1|1);
		t[p].sum=t[p<<1].sum+t[p<<1|1].sum;
	} 
}
inline int ask(int x,int p){
	if(t[p].len==1)return t[p].sum;
	push(p);
	int mid=(t[p].l+t[p].r)>>1;
	if(x<=mid)return ask(x,p<<1);
	else return ask(x,p<<1|1);
}
int main (){
	ios::sync_with_stdio(0);
	cout.tie(0);cin.tie(0);
	cin>>s;
	n=s.size();l=n/2;
	cin>>m;
	build(1,l,1);
	while(m--){
		int x;cin>>x;
		change(x,l,1);
	}
	for(int i=1;i<=l;i++){
		if(ask(i,1))swap(s[i-1],s[n-i]);
	}
	cout<<s<<'\n';
	return 0;
}
```

---

## 作者：q_hacker_p (赞：1)

### 前言
打开算法标签就能发现，这道题本来是一道线段树的题，但本蒟蒻只想到了差分。总不能用线段树维护差分吧，树状数组都懒得写。

咳咳，言归正传
### Step 1:分析题目
```markdown
abcdefgh
2
2 3
```
就看上面这一组样例，我们可以维护一个数组，表示它需要翻转多少次，最后如果是奇数就进行反转，偶数不翻转。
#### 时间复杂度分析
但是我们发现了一个问题，如果采用循环的话。题目中 $m$ 的范围是 $2 \times 10^{5}$，字符串 $s$ 的范围没有给出。我们不妨猜测 $\left| s \right| = 2 \times 10^{5}$ 这样的话 $O(m\left| s \right|)$ 的时间复杂度就会 TLE。
#### 算法选择
那么我们需要一种 $O(1)$ 时间复杂度的算法来进行区间修改。于是，差分登场了。
### Step 2:代码实现
#### 修改差分数组
我们对于每个需要翻转的下标 $x$，对差分数组 $D_{x - 1} $ 让其加一，因为我的字符串的下标是从 $0 \sim \left| s \right| - 1$，又因为它是对称的，所以你只需要知道前 $\left| s \right| \div 2$ 的数组元素值。

Code:

```cpp
for(int i = 1; i <= m; i++)
{
	cin >> x;
	d[x - 1]++;//修改差分数组
}
```
#### 计算答案
首先，把差分数组前 $\left| s \right| \div 2$ 个元素还原。然后判断 $D_i$ 是不是奇数，进行修改。
## Code
因为避免抄题解，等原因本题解只展示代码框架与部分代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
string s;
ll m, x;
ll d[200002];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);     cout.tie(0);
	cin >> s;
	cin >> m;
	for(int i = 1; i <= m; i++)
	{
		cin >> x;
		d[x - 1]++;
	}
	for (int i = 0; i < s.size() / 2; i++)
	{
                //请读者思考，自行填写代码
	}
	cout << s;
	return 0;
}
```

---

## 作者：2022_37_yzyUUU (赞：1)

# CF525B
## 题意简述 
[题目传送门](https://www.luogu.com.cn/problem/CF525B)

给定一个字符串 $s$ 和一个 $m$，然后 $m$ 行，每行一个 $a$，让 $s[i]$ 到 $s[len-i+1]$ 的区间内字符交换。
## 思路
可以使用暴力，但可能会超时，所以可以找规律。
发现
```
a b c d e f
0 1 1 1 1 0
(1代表反转，0则不反）
得：
a e d c b f

```
又因为本题翻转是轴对称的，所以只需要判断一边即可
## AC Code
```
#include<bits/stdc++.h>
using namespace std;
char s[200005];
int f[200005],n,a,len;
int main(){
	cin>>s+1;
	len=strlen(s+1);
	cin>>n;
	while(n--){
		cin>>a;
		f[a]^=1;
	}
	for(int i=1;i<=len/2;i++){
		f[i]^=f[i-1];
		if(f[i])swap(s[i],s[len-i+1]);
	}
	for (int i=1;i<=len;i++)cout<<s[i];
	return 0;
}
```
管理员大大给个通过呗~

---

## 作者：Echoternity (赞：1)

稍微看看这道题的题意，可以总结一下：

> 给定一个字符串 $s$ ，每次操作翻转区间 $[l,len-l+1]$ ，求出最后的字符串。

然后显然地，就发现，这不就文艺平衡树咩。

~~直接贺过来模板~~。

结果这是道 B 题，逛了圈题解区也发现似乎有一种简单的差分做法，可惜蒟蒻只会简简单单的数据结构，想不到高深的差分，就暴力平衡树怼过去惹。qwq

介绍简单的 Fhq-Treap ，通过 Treap 的思路，维护随机值的堆性质以达到随机平衡，并用分裂合并操作维护二叉搜索树的性质以达到左右平衡。容易理解，而且板子比 Splay 好背，强烈推荐。

对于 Fhq-Treap 的区间操作，需要在分裂时按排名分裂。每一次将整棵平衡树按照排名 $[1,l-1],[l,r],[r+1,len]$ 分为三段，然后把中间的区间打上翻转标记即可。

对于序列翻转问题的解法，左转[文艺平衡树](https://www.luogu.com.cn/problem/P3391)，其他的话，就没有什么需要注意的地方了。

推荐一下蒟蒻的博客，[三种常见平衡树不太详解](https://violeteternal.github.io/Eternity/%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0/OI/balanced-tree/)

AC Code:

``` c++
const int MAXN=2e5+10;
char Str[MAXN];
int N,Q;
struct BT
{
    int Idx=0,Rt=0,x,y,z;
    struct Fhq
    {
        int siz,val,rd,rev,chi[2];
    }Tr[MAXN];
    #define ls(p) Tr[p].chi[0]
    #define rs(p) Tr[p].chi[1]
    inline void upDate(int p)
    {
        Tr[p].siz=Tr[ls(p)].siz+Tr[rs(p)].siz+1;
    }
    inline int newNode(int v)
    {
        Tr[++Idx]={0,v,rand()};
        return Idx;
    }
    inline void reverse(int p)
    {
        if(!Tr[p].rev) return ;
        std::swap(ls(p),rs(p));
        if(ls(p)) Tr[ls(p)].rev^=1;
        if(rs(p)) Tr[rs(p)].rev^=1;
        Tr[p].rev=0;
    }
    void split(int p,int k,int &u,int &v)
    {
        if(!p) u=v=0;
        else
        {
            if(Tr[p].rev) reverse(p);
            if(Tr[ls(p)].siz<k) u=p,split(rs(u),k-Tr[ls(p)].siz-1,rs(u),v);
            else v=p,split(ls(v),k,u,ls(v));
            upDate(p);
        }
        return ;
    }
    int merge(int u,int v)
    {
        if(!u||!v) return u+v;
        if(Tr[u].rd<Tr[v].rd)
        {
            if(Tr[u].rev) reverse(u);
            rs(u)=merge(rs(u),v);
            upDate(u);return u;
        }
        else
        {
            if(Tr[v].rev) reverse(v);
            ls(v)=merge(u,ls(v));
            upDate(v);return v;
        }
    }
    inline void insert(int v)
    {
        split(Rt,v-1,x,y);
        Rt=merge(merge(x,newNode(v)),y);
    }
    inline void reverse(int l,int r)
    {
        split(Rt,l-1,x,y),split(y,r-l+1,y,z);
        Tr[y].rev^=1;
        Rt=merge(merge(x,y),z);
    }
    inline void print(int p)
    {
        if(!p) return ;
        if(Tr[p].rev) reverse(p);
        print(ls(p));
        write(Str[Tr[p].val]);
        print(rs(p));
    }
}Tree;
int main()
{
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    scanf("%s",Str+1);
    N=strlen(Str+1);
    for(int i=1;i<=N;++i) Tree.insert(i);
    read(Q);
    for(int ql;Q--;)
    {
        read(ql);int qr=N-ql+1;
        Tree.reverse(ql,qr);
    }
    Tree.print(Tree.Rt);
    return 0;
}
/*
abcdef
1
2
*/
```

---

## 作者：The_foolishest_OIer (赞：0)

应该没人像我一样用线段树。

设这个字符在字符串 $s$ 的位置是 $w$，字符串长度为 $n$，则这个字符如果进行了 $2k+1$ 次操作，位置就在 $n-x+1$，否则就在 $x$。

于是这个问题就变成了区间异或。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 2e5 + 10;
string s;
int n,m;
int sum[N << 2],lzy[N << 2];
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void pushup (int o){
	sum[o] = sum[o << 1] + sum[o << 1 | 1];
}
void maketag (int o,int l,int r){
	lzy[o] ^= 1;
	sum[o] = r - l + 1 - sum[o];
}
void pushdown (int o,int l,int r){
	if (!lzy[o]) return;
	int mid = (l + r) >> 1;
	maketag(o << 1,l,mid);
	maketag(o << 1 | 1,mid + 1,r);
	lzy[o] = 0;
}
void update (int o,int l,int r,int ql,int qr){
	if (ql <= l && r <= qr){
		maketag(o,l,r);
		return;
	}
	pushdown(o,l,r);
	int mid = (l + r) >> 1;
	if (ql <= mid) update(o << 1,l,mid,ql,qr);
	if (qr > mid) update(o << 1 | 1,mid + 1,r,ql,qr);
	pushup(o); 
}
int query (int o,int l,int r,int x){
	if (l == r)
		return sum[o];
	pushdown(o,l,r);
	int mid = (l + r) >> 1;
	if (x <= mid) return query(o << 1,l,mid,x);
	else return query(o << 1 | 1,mid + 1,r,x);
}
// 线段树
signed main(){
	close();
	cin >> s;
	int n = s.size();
	cin >> m;
	for (int i = 1 ; i <= m ; i++){
		int x;
		cin >> x;
		update(1,1,n,x,n - x + 1); // 区间操作
	}
	for (int i = 1 ; i <= n / 2 ; i++)
		if (query(1,1,n,i)) // 如果这个字符进行了奇数次操作，就要与位置在 n - i + 1 的字符交换
			swap(s[i - 1],s[n - i]);
	cout << s;
	return 0;
}
```

---

## 作者：Fuxh_18 (赞：0)

## 题意
有一个字符串 $s$，操作 $m$ 次，每次操作把第 $x$ 个到第 $l-x+1$ 个反转。求最后的结果。
## 思路
直接模拟。把第 $x$ 个到第 $l-x+1$ 中的第 $i$ 个和第 $l-i+1$ 个交换。操作完，就直接输出交换后的 $s$。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int m,l;
int main(){
	cin>>s>>m;
	l=s.size(); //存储 s 的长度 
	for(int i=1;i<=m;i++){ //m 次操作 
		int x;
		cin>>x;
		for(int j=x;;j++){ //操作内容 
			int h=l-j+1;
			if(h<=j){ //换不了，就不换了 
				break;
			}
			swap(s[j-1],s[h-1]); //交换 
		}
	}
	for(int i=0;i<l;i++){
		cout<<s[i]; //输出 
	}
	return 0;
}
```

---

## 作者：XL4453 (赞：0)

### 解题思路：

本题的一种较为简单实现方法是差分，但一般情况下，翻转问题是使用高级数据结构（如平衡树）来求解的，本题能够差分实现是有其特殊性的。

由于每一次的翻转都是以最中间的那一个点为中心的，所以将整个字符串砍掉一半，对于某一个位置若左边若需要翻则右边一定要翻。

这样问题就转化为在左边（或者右边）每一次翻转从某一个位置一直到最后一个位置翻转，显然可以根据奇偶性差分。

---
### 代码：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
char s[200005];
int n,m,l,r,d[200005],now;
int main(){
	cin>>s+1;
	n=strlen(s+1);
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d",&l);
		d[l]^=1;d[n-l+2]^=1;
	}
	for(int i=1;i<=n;i++){
		now^=d[i];
		if(now==0)printf("%c",s[i]);
		else printf("%c",s[n-i+1]);
	}
	return 0;
}
```


---

## 作者：Fearliciz (赞：0)

~~差分yyds！~~

做这道题就需要学会差分。


所以我们先要了解以下[差分和前缀和](https://oi-wiki.org/basic/prefix-sum/)。


注：修改区间用差分，查询区间用前缀和。

而这道题用到了修改操作，所以使用差分。

#### 步骤：

（用样例 $1$ 举例）

首先将字符串从中间一分为二。

![](https://cdn.luogu.com.cn/upload/image_hosting/l9v145a4.png?x-oss-process=image)

接下来将第一个要旋转的字符的后面的所有字符的旋转次数加 $1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/9eyhbrsm.png?x-oss-process=image)

最后遍历前半部分的旋转次数，如果为偶数不变，如果为奇数交换。

注意：不用像普通的差分处理后面，因为我们只用遍历前半部分，这为程序省了时间。

所以代码就比较简单了：

```cpp
#include <bits/stdc++.h>
using namespace std;
char s[200001];
int n, x;
int a[200001];

int main() {
	cin >> s + 1;

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> x;
		a[x]++;
	}
	int len = strlen(s + 1);
	for (int i = 1; i <= len / 2; i++) {
		a[i] += a[i - 1];
		if (a[i] % 2 == 1)
			swap(s[i], s[len - i + 1]);
	}
	for (int i = 1; i <= len; i++)
		cout << s[i];
	return 0;
}
```


---

## 作者：开始新的记忆 (赞：0)

题目大意：给你一串字符串，有m次操作，每次操作一个数ai，翻转位置ai到s-ai+1之间的字符串，输出最后的字符串。

思路：比较玄学，就是先用一个hh数组记录每段（类似差分，记录在两头）的变换情况，然后从头往后扫，每次当一个位置交换了奇数次就改变f，一旦交换了奇数次（f==1）就与对应位置的字符交换，反之则不变。


```cpp
#include<cstdio>
#include<string>
#include<iostream>
using namespace std;
string ss;
bool hh[100010]={0},f=false;
int main()
{
    int c,cc,stl,t,t1;
    cin>>ss;
    cin>>c;
    t=ss.size()/2;
    stl=ss.size();
    for(int i=1;i<=c;i++)
    {
        cin>>cc;
        cc--;
        if(hh[cc])
            hh[cc]=0;
        else
            hh[cc]=1;
    }
    for(int i=0;i<t;i++)
    {
        if(hh[i])
        {
            if(!f)
                f=1;
            else
                f=0;
        }
        if(f)
            swap(ss[i],ss[stl-i-1]);
    }
    cout<<ss;
    return 0;
}

```


---

## 作者：Oscar12345 (赞：0)

[原题链接](http://codeforces.com/problemset/problem/525/B)

样例：
input：
abcdef 
1 
2 

output：
aedcbf 

input：
vwxyz 
2 
2 2 

output：
vwxyz 

input：
abcdef 
3 
1 2 3 

output：
fbdcea

题意：给定一个串，每次翻转区间[L, |s| - L + 1]的字符。问你最后的字符串。

思路：
显然当某个位置处理次数为奇数时才需要变化，我们从左向右扫描一遍，发现奇数则将变化加到右边，最后只需判断某个位置变化次数的奇偶性。

代码：
```
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <iostream>
#include <cmath>
#include <queue>
#include <stack>
#define ll o<<1
#define rr o<<1|1
#define CLR(a, b) memset(a, (b), sizeof(a))
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
const int INF = 0x3f3f3f3f;
const int MAXN = 1e6 + 10;
char str[MAXN];
int use[MAXN];
int main()
{
    while(scanf("%s", str+1) != EOF) {
        int len = strlen(str+1);
        CLR(use, 0);
        int m; scanf("%d", &m);
        for(int i = 1; i <= m; i++) {
            int p; scanf("%d", &p);
            use[p]++;
        }
        for(int i = 2; i <= len/2; i++) {
            if(use[i-1] & 1) use[i]++;
        }
        for(int i = 1; i <= len; i++) {
            //cout << use[i] << endl;
            if(use[i] & 1) {
                swap(str[i], str[len-i+1]);
                //use[i+1]++;
            }
        }
        printf("%s\n", str+1);
    }
    return 0;
}
```

---

## 作者：rEdWhitE_uMbrElla (赞：0)

$$\large\text{线段树罢。。虽然应该还有更简洁的方法}$$~~毕竟是B题~~

$\small\text{然后就发现这就是线段树区间翻转的一道版题。。上代码}$

```
#include<bits/stdc++.h>
#define maxn 200005 
using namespace std; 
int L[maxn],R[maxn],S[maxn],K[maxn],IP; 
bool Turn[maxn];
int ANS[maxn],ANSIP;
void PushDown(int rt){
	if(Turn[rt]){
		Turn[L[rt]]^=1;Turn[R[rt]]^=1;
		swap(L[rt],R[rt]);
		Turn[rt]=0;
	}
}
void zig(int &rt){
	PushDown(rt);PushDown(R[rt]);
	int t=R[rt];R[rt]=L[t];L[t]=rt;
	S[t]=S[rt];S[rt]=1+S[L[rt]]+S[R[rt]];rt=t; 
}
void zag(int &rt){
	PushDown(rt);PushDown(L[rt]);
	int t=L[rt];L[rt]=R[t];R[t]=rt;
	S[t]=S[rt];S[rt]=1+S[L[rt]]+S[R[rt]];rt=t;
}
int n,m;
void Build(int &rt,int A,int B){
	int M=(A+B)>>1;
	rt=++IP;
	L[rt]=R[rt]=0;
	S[rt]=B-A+1;
	K[rt]=ANS[M];
	if(A < M) Build(L[rt],A,M-1);
	if(B > M) Build(R[rt],M+1,B);
}
void Show(int &rt){
	PushDown(rt);
	if(L[rt]) Show(L[rt]);
	ANS[ANSIP++]=K[rt];
	if(R[rt]) Show(R[rt]);
}
void SetRootTo(int &rt,int k){
	PushDown(rt);
	if(S[L[rt]]+1==k) return;
	if(S[L[rt]]>=k){SetRootTo(L[rt],k);zag(rt);return;}
	else {SetRootTo(R[rt],k-S[L[rt]]-1);zig(rt);return;}
}
void Reverse(int &rt,int Left,int Right){
	SetRootTo(rt,Right+2);SetRootTo(L[rt],Left);
	Turn[R[L[rt]]]^=1;
}
int main(){
	string s;
	cin>>s;
	n=s.size();
	for(int i=1;i<=n;++i) ANS[i]=s[i-1];
	int rt=0;IP=0;
	Build(rt,0,n+1);
	scanf("%d",&m);
	for(int i=0;i<m;++i){
	 	int Left,Right;scanf("%d",&Left);
	 	Right=n-Left+1;
	 	Reverse(rt,Left,Right);
	 }
	 ANSIP=0;
	 Show(rt);
	 for(int i=1;i<=n;++i){
	 	printf("%c",ANS[i]);
	 }
    return 0;
}
```

---

