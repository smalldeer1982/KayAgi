# [ABC285F] Substring of Sorted String

## 题目描述

给定一个由小写英文字母组成、长度为 $N$ 的字符串 $S$，以及 $Q$ 个查询。请依次处理这些查询。

查询有以下两种类型：

- `1 x c` ：将 $S$ 的第 $x$ 个字符替换为字符 $c$。
- `2 l r` ：将 $S$ 按照字符的升序排列得到字符串 $T$。如果 $S$ 的第 $l$ 个字符到第 $r$ 个字符组成的子串是 $T$ 的子串，则输出 `Yes`，否则输出 `No`。

什么是子串？$S$ 的**子串**是指从 $S$ 的开头删除 $0$ 个或多个字符、从末尾删除 $0$ 个或多个字符后得到的字符串。例如，`ab` 是 `abc` 的子串，但 `ac` 不是 `abc` 的子串。

## 说明/提示

### 限制条件

- $1 \leq N \leq 10^5$
- $S$ 是由小写英文字母组成的长度为 $N$ 的字符串
- $1 \leq Q \leq 10^5$
- 对于第 1 种类型的查询，$1 \leq x \leq N$
- 对于第 1 种类型的查询，$c$ 是小写英文字母
- 对于第 2 种类型的查询，$1 \leq l \leq r \leq N$

### 样例解释 1

- 对于第 1 个查询，将 $S$ 按字符升序排列得到的字符串 $T$ 是 `abccdf`。$S$ 的第 $1$ 到第 $3$ 个字符组成的字符串是 `abc`，它是 $T$ 的子串，因此输出 `Yes`。
- 对于第 2 个查询，将 $S$ 按字符升序排列得到的字符串 $T$ 是 `abccdf`。$S$ 的第 $2$ 到第 $6$ 个字符组成的字符串是 `bcdcf`，它不是 $T$ 的子串，因此输出 `No`。
- 第 3 个查询将 $S$ 的第 $5$ 个字符替换为 `e`，此时 $S$ 变为 `abcdef`。
- 对于第 4 个查询，将 $S$ 按字符升序排列得到的字符串 $T$ 是 `abcdef`。$S$ 的第 $2$ 到第 $6$ 个字符组成的字符串是 `bcdef`，它是 $T$ 的子串，因此输出 `Yes`。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
abcdcf
4
2 1 3
2 2 6
1 5 e
2 2 6```

### 输出

```
Yes
No
Yes```

# 题解

## 作者：TKXZ133 (赞：11)

[Substring of Sorted String](https://www.luogu.com.cn/problem/AT_abc285_f)

写篇题解纪念一下蒟蒻第一次赛时切出的 F 题。

### 题目简述

对一个字符串进行单点修改，区间判断操作。

修改操作为将一个字符修改为另一个，判断操作为判断区间是否是整个字符串升序排序后的字串。

### 思路分析

蒟蒻第一眼线段树，但刚开始没仔细看题，以为是判断区间是否升序排序，所以很快得到做法：

对于每个线段树上的节点，保存三个信息：区间最左端的字符 $\text{lz}$，区间最右端的字符 $\text{rz}$，区间是否升序排序 $\text{is}$。

合并时,我们按照如下方法合并：（记整个区间的编号为 $\text{p}$，左区间的编号为 $\text{lson}$，右区间的编号为 $\text{rson}$。）

```
lz[p]=lz[lson]
rz[p]=rz[rson]
is[p]=is[lson]&&is[rson]&&(rz[lson]<=ls[rson])
```

至于为什么这样合并是显然的。

但在蒟蒻写完交了一发后，发现 WA 了，仔细看题后发现是判断区间是否是整个字符串是否是整个字符串升序排序后的字串。

但在思考后，蒟蒻得到了一个做法：

在每个节点上额外维护一个数组 $\text{cnt}$，$\text{cnt}[i]$ 表示在这个整个区间内第 $i$ 个小写字母出现的个数，合并时只需要对于枚举每一个字符相加就行。

在判断时，我们在升序排序的基础上，判断这个区间内除了最左端字符和最右端字符之外的字符出现次数是否等于整个字符串的该字符出现次数就可以了，这样是可以保证没有问题的。

时间复杂度为 $O(26q\log n)$，虽然常数比 $\log$ 还大，但不影响正确性。

### 注意事项

单点修改后记得将之前的位置清零。

注意下标的同步。

### 代码

放上丑陋的赛时代码：

```
#include <bits/stdc++.h>
using namespace std;
const int N=100100;

int n,q,op,in1,in3;
char inp[N];//整个字符串
char in2[2];//输入的操作类型

struct STn{int l,r,is;char lz,rz;int cnt[30];};//线段树的节点
void merge(STn &res,STn a,STn b){//合并区间
    res.lz=a.lz;
    res.rz=b.rz;
    res.is=(a.is&&b.is)&&(a.rz<=b.lz);//更新
    for(int i=1;i<=26;i++)
        res.cnt[i]=a.cnt[i]+b.cnt[i];//相加
}
struct ST{
    STn a[N<<2];
    void build(int p,int l,int r){
        a[p].l=l;a[p].r=r;
        if(a[p].l==a[p].r){a[p].lz=a[p].rz=inp[a[p].l];a[p].is=1;a[p].cnt[inp[a[p].l]-'a'+1]=1;return ;}//初始化
        int mid=(a[p].l+a[p].r)>>1;
        build(p<<1,l,mid);build(p<<1|1,mid+1,r);
        merge(a[p],a[p<<1],a[p<<1|1]);return ;
    }
    void change(int p,int x,char k){
        if(a[p].l==a[p].r){a[p].cnt[a[p].lz-'a'+1]=0;a[p].lz=a[p].rz=k;a[p].cnt[k-'a'+1]=1;return ;}//单点修改后重置
        int mid=(a[p].l+a[p].r)>>1;
        if(x<=mid) change(p<<1,x,k);else change(p<<1|1,x,k);
        merge(a[p],a[p<<1],a[p<<1|1]);return ;
    }
    STn ask(int p,int l,int r){
        if(l<=a[p].l&&a[p].r<=r) return a[p];
        int mid=(a[p].l+a[p].r)>>1;
        if(r<=mid) return ask(p<<1,l,r);
        if(l>mid) return ask(p<<1|1,l,r);
        STn res;merge(res,ask(p<<1,l,r),ask(p<<1|1,l,r));//询问合并
        return res;
    }
}tree;

int main(){
    scanf("%d",&n);
    scanf("%s",inp+1);
    scanf("%d",&q);
    tree.build(1,1,n);
    while(q--){
        scanf("%d",&op);
        if(op==1){scanf("%d%s",&in1,in2+1);tree.change(1,in1,in2[1]);}
        if(op==2){
            scanf("%d%d",&in1,&in3);
            STn res=tree.ask(1,in1,in3);
            if(res.is){//前提是区间升序排序
                int f=1;
                for(int i=res.lz+1;i<=res.rz-1;i++)
                    if(res.cnt[i-'a'+1]!=tree.a[1].cnt[i-'a'+1]){//tree.a[1]就是整个字符串
                        f=0;break;
                    } //判断字符出现次数
                puts(f?"Yes":"No");
            }
            else puts("No");
        }
    }
    return 0;
}
```

---

## 作者：cancan123456 (赞：4)

考虑什么时候 $s_{l\sim r}$ 是 $T$ 的子串，统计出 $T$ 中字符的出现次数和 $s_{l\sim r}$ 中字符的出现次数和其中最小的字符 $c_1$ 和最大的字符 $c_2$，显然可以发现当且仅当 $s_{l\sim r}$ 中 $c_1,c_2$ 出现的次数小于等于 $T$ 中出现次数、$s_{l\sim r}$ 中 $c_1+1\sim c_2-1$ 出现次数等于 $T$ 中出现次数、$s_{l\sim r}$ 递增时 $s_{l\sim r}$ 是 $T$ 的子串，线段树维护即可，时间复杂度 $O(|\Sigma|n\log n)$。

---

## 作者：FL_sleake (赞：3)

**目前题解区唯一一篇未使用树状数组/线段树的题解。**

### 题目大意

给定一个长度为 $N$ 的字符串 $S$，下标从 $1$ 开始，有以下两种操作：

- `1 x c`：将字符串 $S$ 中的第 $x$ 个字符替换为 $c$。
- `2 l r`：将 $S$ 中的字符按升序排列，得到新字符串 $T$，询问串 $S_{l,l+1,\cdots,r}$ 是否为 $T$ 的子串。

对于每个操作 $2$，输出 `Yes` 或者 `No` 表示结果。

### 解题思路

先来考虑 $S_{l,l+1,\cdots,r}$ 什么时候是 $T$ 的子串。设 $S_{l,l+1,\cdots,r}$ 中最大的字符为 $Max$，最小的字符为 $Min$，则当且仅当对于所有的满足 $Min+1 \leq c \leq Max-1$ 的字符 $c$，它在 $S_{l,l+1,\cdots,r}$ 中出现的次数等于它在 $T$ 中出现的次数，且 $S_{l,l+1,\cdots,r}$ 中字符单调不降时，$S_{l,l+1,\cdots,r}$ 是 $T$ 的子串。

于是很多题解开始用树状数组和线段树开始维护，但是实际上我们可以用 set 来维护这个玩意儿。用一个 set 维护所有 $s_i<s_{i-1}$ 的 $i$，再用 $26$ 个 set 维护每种字符的出现位置。对于每次询问，先找出区间内的最大最小字符，再按照上面说的进行判断即可。代码中有注释。

### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,q;
string s;
set<int> x,id[30];
signed main(){
	cin>>n>>s>>q;
	s=" "+s;
	for(int i=2;i<s.size();i++) if(s[i]<s[i-1]) x.insert(i);//用于检查区间是否单调不降
	for(int i=1;i<s.size();i++) id[s[i]-'a'].insert(i);
	while(q--){
		int op,l,r;
		char c;
		cin>>op;
		if(op==1){
			cin>>l>>c;
			if(l!=1) if(s[l]<s[l-1]) x.erase(l);
			if(l!=s.size()-1) if(s[l+1]<s[l]) x.erase(l+1);
			id[s[l]-'a'].erase(l);
          //维护修改这一位字符造成的影响
			s[l]=c;//修改
          //维护修改这一位字符造成的影响
			id[s[l]-'a'].insert(l);
			if(l!=s.size()-1) if(s[l+1]<s[l]) x.insert(l+1);
			if(l!=1) if(s[l]<s[l-1]) x.insert(l);
		}else{
			int flg=1;
			cin>>l>>r;
			char Min='z',Max='a';
          //找到区间中出现的最大最小字符
			for(char ck='a';ck<='z';ck++){
				auto it=id[ck-'a'].lower_bound(l);
				if(it!=id[ck-'a'].end()&&*it<=r){
					if(ck<Min) Min=ck;
					if(ck>Max) Max=ck;
				}
			}
          //判断其余字符出现次数是否等于总出现次数
          //不等于则答案为 No
			for(char ck=Min+1;ck<=Max-1;ck++){
				if(id[ck-'a'].empty()) continue;
				if((l<=*id[ck-'a'].begin()&&*id[ck-'a'].rbegin()<=r)) continue;
				flg=0;
			}
			auto it=x.upper_bound(l);
			if(it!=x.end()&&*it<=r) flg=0;
          //区间不单调不降则答案为 No
			cout<<(flg?"Yes":"No")<<endl;
		}
	}
	return 0;
}
```

---

## 作者：incra (赞：3)

### [题目链接](https://atcoder.jp/contests/abc285/tasks/abc285_f)
### 题解（树状数组）
我们维护两个树状数组，一个记录 $1\sim i$ 中 $s_i>s_{i+1}$ 的数量，即逆序对数量，另一个记录 $1\sim i$ 中 $26$ 个字母的数量。

在修改时很好维护，先把原来的字母数量减 $1$，再新的字母数加 $1$，逆序对以类似方式维护。

重点在查询，一个区间 $[l,r]$ 被包含在排序后的字符串中，当且仅当这个区间里没有逆序对（即统计逆序对数量的树状数组 $[l,r-1]$，注意，右端点是 $r-1$，如果右端点是 $r$ 会统计到 $s_r > s_{r+1}$，不符合我们要求），且除了最头上的字母外中间的字母（大于第一个字母小于最后一个字母）应和所有的字符数量相同（要包含排好序的字符串中连续字符一定要选上，如果 $[l,r]$ 区间的字符串包含了大于第一个字母小于最后一个字母的字母，那么中间的所有字母应包含整个字符串中的字母，也就是说，这个子串中中间的字母应和整个字符串中的字母数相同）。
### 代码
```cpp
#include <iostream>
using namespace std;
const int N = 100010;
int n,q;
string s;
int c[N];
int cnt[26][N];
int lowbit (int x) {
	return x & -x;
}
void modify (int c[],int x,int d) {
	for (int i = x;i <= n;i += lowbit (i)) c[i] += d;
}
int query (int c[],int x) {
	int ans = 0;
	for (int i = x;i;i -= lowbit (i)) ans += c[i];
	return ans;
}
int main () {
	cin >> n >> s >> q;
	s = ' ' + s;
	for (int i = 1;i <= n;i++) modify (cnt[s[i] - 'a'],i,1);
	for (int i = 1;i < n;i++) {
		if (s[i] > s[i + 1]) modify (c,i,1);
	}
	while (q--) {
		int op;
		cin >> op;
		if (op == 1) {
			int x;
			char ch;
			cin >> x >> ch;
//			if (x + 1 <= n && s[x] > s[x + 1] && ch <= s[x + 1]) modify (c,x,-1);
//			else if (x + 1 <= n && s[x] <= s[x + 1] && ch > s[x + 1]) modify (c,x,1);
//			if (x - 1 >= 1 && s[x - 1] > s[x] && ch >= s[x - 1]) modify (c,x - 1,-1);
//			else if (x - 1 >= 1 && s[x - 1] <= s[x] && ch < s[x - 1]) modify (c,x - 1,1);
			modify (cnt[s[x] - 'a'],x,-1),modify (cnt[ch - 'a'],x,1);
			if (x - 1 >= 1 && s[x - 1] > s[x]) modify (c,x - 1,-1);
			if (x + 1 <= n && s[x] > s[x + 1]) modify (c,x,-1);
			s[x] = ch;
			if (x - 1 >= 1 && s[x - 1] > s[x]) modify (c,x - 1,1);
			if (x + 1 <= n && s[x] > s[x + 1]) modify (c,x,1);
		}
		else {
			int l,r;
			cin >> l >> r;
			bool ans = true;
			for (int i = s[l] - 'a' + 1;i <= s[r] - 'a' - 1;i++) ans &= query (cnt[i],r) - query (cnt[i],l - 1) == query (cnt[i],n);
			if (ans && query (c,r - 1) - query (c,l - 1) == 0) puts ("Yes");
			else puts ("No");
		}
	}
	return 0;
}
```

---

## 作者：Resolute_Faith (赞：2)

一道比较简单好想的数据结构。

我们不妨先分析 $T$ 串的性质，由题意得 $T$ 的字母是递增的，那意味着我询问的子串也应该递增的。

但是子串递增并不意味着他是 $T$ 的子串，因为排序后可能会有其他的字母插入进来。举个例子：

$$
\begin{aligned}
S=\tt{aaaaaabbbbddyyyyzzzffbaaaz}\\
T=\tt{aaaaaaaaabbbbbddffyyyyzzzz}
\end{aligned}
$$

假设我们现在查询 $\tt{aabbbbddyy}$ 这个子串是否是 $T$ 的一个子串。

我们不难发现将 $S$ 串排序后发生了以下几个事情：

1. $\tt a$ 和 $\tt z$ 被归位了，看上去并不影响我们的查询。
2. $\tt b$ 被塞了一个进去。
3. $\tt f$ 被塞了两个进去，但是我们原本的子串并没有 $\tt f$。

所以经过简单的分析，我们得到如下结论：

1. 在 $S_l+1$ 到 $S_r-1$ 的所有字母中，其在子串中的出现次数应当等于全串的出现次数。
2. 跟 $S_l$ 和 $S_r$ 相同的字母不影响查询。
3. 区间要递增。

看上去“区间递增”是最好做的，不妨想一下如何用数据结构维护。

- 如果 $S_i\geqslant S_{i-1}$，那么我们令 $a_i:=1$，否则 $a_i:=-1$。

那么一个区间 $[l,r]$ 递增的条件可以转化为 $\sum\limits_{l+1}^r a_i=r-l$。开一个线段树维护即可，每次询问都要检查如上条件，修改时考虑新的字符与其前后的关系，**要更改两处线段树的值。**

“出现次数”这个条件就十分简单了，不难发现值域只有 $26$，可以考虑开 $26$ 个线段树或者树状数组（我知道大家懒得写所以还是写树状数组吧）。每一个树状数组维护一个值，如果串中 $S_i=p$，那么 $tr_{p,i}=1$，累加起来即可得到出现次数。

```cpp
//F
#include<bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define fir first
#define sec second
#define lowbit(i) (i&(-i))
using namespace std;
const int N=5e5+5;
const int inf=1e18;
struct edge{int to,nxt,l;};
inline int read(){
    char op=getchar();
    int w=0,s=1;
    while(op<'0'||op>'9'){
        if(op=='-') s=-1;
        op=getchar();
    }
    while(op>='0'&&op<='9'){
        w=(w<<1)+(w<<3)+op-'0';
        op=getchar();
    }
    return w*s;
}
int a[N],n;
char s[N];
void change(int p,int l,int r,int x,int k){
    if(l==x&&r==x){
        a[p]=k;
        return;
    }
    if(x<=mid) change(p<<1,l,mid,x,k);
    else change(p<<1|1,mid+1,r,x,k);
    a[p]=a[p<<1]+a[p<<1|1];
}
int ask(int p,int l,int r,int x,int y){
    int ans=0;
    if(x<=l&&r<=y){
        ans+=a[p];
        return ans;
    }
    if(x<=mid) ans+=ask(p<<1,l,mid,x,y);
    if(y>mid) ans+=ask(p<<1|1,mid+1,r,x,y);
    return ans;
}
struct bit_tree{
    int a[N];
    void change(int x,int k){
        for(register int i=x;i<=n;i+=lowbit(i)) a[i]+=k;
        return;
    }
    int ask(int x){
        int ans=0;
        for(register int i=x;i>=1;i-=lowbit(i)) ans+=a[i];
        return ans;
    }
}st[28];
signed main(){
    n=read();
    scanf("%s",s+1);
    for(register int i=1;i<=n;i++){
        if(i>=2){
            if(s[i]>=s[i-1]) change(1,1,n,i,1);
            else change(1,1,n,i,-1);
        }
        st[s[i]-'a'+1].change(i,1);
    }
    int q=read();
    while(q--){
        int op=read();
        if(op==2){
            int l=read(),r=read();
            if(ask(1,1,n,l+1,r)!=r-l){
                printf("No\n");
                continue;
            }
            bool p=true;
            for(register int i=s[l]+1;i<=s[r]-1;i++){
                if(st[i-'a'+1].ask(r)-st[i-'a'+1].ask(l-1)!=st[i-'a'+1].ask(n)){
                    printf("No\n");
                    p=false;
                    break;
                }
            }
            if(p){
                printf("Yes\n");
                continue;
            }
        }else{
            int x=read();
            char ch=getchar();
            while(ch>'z'||ch<'a') ch=getchar();
            if(ch>=s[x-1]) change(1,1,n,x,1);
            else change(1,1,n,x,-1);
            if(x<n){
                if(s[x+1]>=ch) change(1,1,n,x+1,1);
                else change(1,1,n,x+1,-1);
            }
            st[s[x]-'a'+1].change(x,-1);
            st[ch-'a'+1].change(x,1);
            s[x]=ch;
        }
    }
}
```

---

## 作者：C_liar (赞：1)

数据结构题。

### 题目大意

给定一个长度为 $N$ 的字符串 $S$，下标从 $1$ 开始，有以下两种操作：

- `1 x c`：将字符串 $S$ 中的第 $x$ 个字符替换为 $c$。
- `2 l r`：将 $S$ 中的字符按升序排列，得到新字符串 $T$，询问串 $S_{l,l+1,...,r}$ 是否为 $T$ 的子串。

对于每个操作 $2$，输出 `Yes` 或者 `No` 表示结果。

数据范围：$1\leq N,Q\leq 10^5$，字符均为小写字母。

### 题解

首先，容易得出，$T$ 中的任意子串都是单调不降的。

所以，得出第一条结论，如果 $S_{l...r}$ 为 $T$ 的子串，那么 $S_{l...r}$ 一定单调不降。

但是，考虑这样一个例子：

$S=\texttt{babc},\ l=2,\ r=4.$

此时 $T=\texttt{abbc}$，虽然 $\texttt{abc}$ 满足单调不降性质，但不是 $T$ 的子串。

设字符 $i$ 在 $S_{l...r}$ 中出现的次数为 $C_i$，在整个 $S$ 串中出现的次数为 $D_i$。

观察得出第二条结论，若 $S_{l...r}$ 中 共有 $K$ 个不同的字符，按 `ASCII` 码从小到大排列为 $a_1,a_2,...,a_K$，那么有：

- $C_{a_i}=D_{a_i},\ i=2,3,...,K-1$

举个例子：

```
aaaabbbccdeefffafaf
 ^          ^
 l          r
```

则，`b,c,d,e` 在 $S_{l...r}$ 中出现的次数需要等于在整个 $S$ 串中出现的次数。

因为若 $S$ 串中其他部分有这些字符，那么 $T$ 串中间的部分就会更长些，$S_{l...r}$ 也就不是 $T$ 的子串了。

至于两端的字符，可以不用管，总是能对齐的。

那么，我们已经把问题抽象成了：

1. 单点修改；
2. 区间询问是否满足结论一和结论二。

考虑线段树解决。

判断结论一，可以对每个线段树结点维护一个 `bool` 值，一个区间中最小字符，一个最大字符。`bool` 值记录当前结点是否单调不降，结点合并时用到两个区间中字符最值。

判断结论二，可以对每个线段数结点维护 $26$ 个字符出现的次数，再维护一个全局字符出现的次数，进行比较即可。

具体实现详见代码，时间复杂度 $O\big(\Sigma\times(N+Q\log N)\big)$，$\Sigma$ 为字符集。

### 代码

```cpp
#include<cstdio>
#include<algorithm>
const int _=1e5+10;
using namespace std;

int n;
char s[_];

struct SegTree{
    struct st{
        int l,r;
        int lch,rch,is,cnt[26];
    }t[_<<2];
    #define T int lc(p<<1),rc(p<<1|1)
    #define update(p) t[p]=t[lc]+t[rc]
    friend st operator +(const st& l,const st& r){
        st tmp;
        for(int i=0;i<26;i++) tmp.cnt[i]=l.cnt[i]+r.cnt[i];
        tmp.lch=min(l.lch,r.lch);
        tmp.rch=max(l.rch,r.rch);
        tmp.l=l.l;
        tmp.r=r.r;
        tmp.is=l.is&&r.is&&l.rch<=r.lch;
        return tmp;
    }
    void build(int p=1,int lf=1,int rt=n){
        t[p].l=lf,t[p].r=rt;
        if(lf==rt){
            t[p].lch=t[p].rch=s[lf]-'a';
            t[p].cnt[s[lf]-'a']=1;
            t[p].is=1;
            return;
        }
        T,mid=(lf+rt)>>1;
        build(lc,lf,mid);
        build(rc,mid+1,rt);
        update(p);
    }
    void modify(int pos,int x,int p=1){
        if(t[p].l==t[p].r){
            t[p].cnt[t[p].lch]=0;
            t[p].lch=t[p].rch=x;
            t[p].cnt[x]=1;
            return;
        }
        T;
        if(pos<=t[lc].r){
            modify(pos,x,lc);
        }
        else modify(pos,x,rc);
        update(p);
    }
    st query(int lf,int rt,int p=1){
        if(lf<=t[p].l&&t[p].r<=rt){
            return t[p];
        }
        T;
        if(lf<=t[lc].r){
            if(t[rc].l<=rt){
                return query(lf,rt,lc)+query(lf,rt,rc);
            }
            else return query(lf,rt,lc);
        }
        else return query(lf,rt,rc);
    }
}t;

int cnt[26];

int main(){
    scanf("%d%s",&n,s+1);
    for(int i=1;i<=n;i++) cnt[s[i]-'a']++;
    t.build();
    int q;scanf("%d",&q);
    for(int i=1;i<=q;i++){
        int op,l,r;
        char x;
        scanf("%d%d",&op,&l);
        if(op==1){
            do{x=getchar();}while('a'>x||'z'<x);
            t.modify(l,x-'a');
            cnt[s[l]-'a']--;
            cnt[x-'a']++;
            s[l]=x;
        }
        else{
            scanf("%d",&r);
            SegTree::st tmp=t.query(l,r);
            if(!tmp.is) {
                puts("No");
                continue;
            }
            for(int i=tmp.lch+1;i<=tmp.rch-1;i++){
                if(cnt[i]!=tmp.cnt[i]){
                    puts("No");
                    goto ed;
                }
            }
            puts("Yes");
            ed:{}
        }
    }
    return 0;
}
```

---

## 作者：CarroT1212 (赞：1)

#### 题目大意

给定一个长度为 $N$ 的仅含小写字母的字符串 $S$ 和 $Q$ 次操作。操作有两种：

+ `1 x c`：将 $S_x$ 替换为小写字母 $c$。
+ `2 l r`：设 $T$ 为将 $S$ 中字符从小到大排序后得到的字符串。问从 $S$ 中截取出的从第 $l$ 位开始，第 $r$ 位结束的字符串是否为 $T$ 的子串。

数据范围：$1 \le N \le 10^5$，$1 \le Q \le 10^5$。

#### 解法分析

容易发现第二种操作可以转化为：

> 问从 $S$ 中截取出的从第 $l$ 位开始，第 $r$ 位结束的字符串是否满足下列条件：
> 
> + 字符串中所有字符都为升序排列。
> + 大于 $S_l$、小于 $S_r$ 的字符，在截取的字符串中出现的次数，都等于在整个 $S$ 中出现的次数。

转化之后就很好做了。我赛时由于把第二个条件给转化错了所以没写出来。

用一个整数序列 $A$ 对应 $S$。比如当 $S$ 为 `abcdcf` 时，$A$ 就为 $\{1,2,3,4,3,6\}$。

设 $c_{i}$ 为 $|a_i-a_{i-1}|$，其中 $a_0=0$。若 $c_{l+1},c_{l+2},\cdots,c_{r}$ 之和等于 $a_r-a_l$，则第一个条件满足。可以使用树状数组来维护 $c$。

判断第二个条件是否满足也可以开 $26$ 个树状数组维护对应字母的区间个数和。

#### 代码

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pll pair<ll,ll>
using namespace std;
const int N=1e5+7;
int n,q,a[N],c[37][N];
char str[N];
int lbit(int x) { return x&-x; }
void add(int x,int y,int z) { for (;x<=n;x+=lbit(x)) c[z][x]+=y; }
int qry(int x,int y) { int ret=0; for (;x;x-=lbit(x)) ret+=c[y][x]; return ret; }
int main() {
	scanf("%d%s%d",&n,str+1,&q);
	for (int i=1;i<=n;i++) a[i]=str[i]-'a'+1;
	for (int i=1;i<=n;i++) add(i,abs(a[i]-a[i-1]),0),add(i,1,a[i]);
	for (int op;q--;) {
		scanf("%d",&op);
		if (op==1) {
			int x; char inp[2],ch;
			scanf("%d%s",&x,inp),ch=inp[0];
			add(x,-abs(a[x]-a[x-1]),0),add(x+1,-abs(a[x+1]-a[x]),0),add(x,-1,a[x]),
			a[x]=ch-'a'+1,
			add(x,abs(a[x]-a[x-1]),0),add(x+1,abs(a[x+1]-a[x]),0),add(x,1,a[x]);
		}
		else {
			int l,r,flg=1;
			scanf("%d%d",&l,&r);
			if (qry(r,0)-qry(l,0)!=a[r]-a[l]) printf("No\n");
			else {
				for (int i=a[l]+1;i<a[r];i++)
					if (qry(r,i)-qry(l-1,i)!=qry(n,i)) { flg=0; break; }
				printf(flg?"Yes\n":"No\n");
			}
		}
	}
	return 0;
}
```

---

## 作者：wcyQwQ (赞：1)

[题目传送门](https://atcoder.jp/contests/abc285/tasks/abc285_f)

[可能更好的阅读体验](https://chenyu-w.github.io./2023/01/16/ABC285F/)

## 前言

写篇题解纪念这道赛时让我心态炸裂的 F。

## 分析

首先让我们来研究一下什么样的字符串 $A$ 可以作为 $T$ 串的子串。（为了方便说明，设 $A$ 中字典序最小字符的为 $c_1$, 字典序最大的字符为 $c_2$）。

1. 字符单调不减，且在 $S$ 内连续（即不存在 $c \in [c_1, c_2], c \in S, c\notin A$）
2. 除 $c_1, c_2$ 外，其余字符出现次数与 $S$ 中该字符出现次数相等。

不难发现满足以上两个条件即可判断子串，所以我们可以考虑对每个字符都开一棵线段树，维护它在每个位置是否出现，判断字符单调不减就可以直接通过查询区间和来做到(具体见代码)，而剩下条件也直接查区间和判断即可。

## 代码

(赛时写的，很丑)

```c++
#include <bits/stdc++.h>
 
using namespace std;
const int N = 2e5 + 10;
struct Sgt {
	int l, r, sum;
} t[26][N << 2];
char s[N];
 
inline void build(Sgt t[], int p, int l, int r, int c) {
	t[p].l = l, t[p].r = r;
	if (l == r) {
		t[p].sum = s[l] == c + 'a';
		return;
	}
	int mid = (l + r) >> 1;
	build(t, p << 1, l, mid, c), build(t, p << 1 | 1, mid + 1, r, c);
	t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
}
 
inline void modify(Sgt t[], int p, int x, int v) {
	if (t[p].l == t[p].r) {
		t[p].sum = v;
		return;
	}
	int mid = (t[p].l + t[p].r) >> 1;
	if (x <= mid) modify(t, p << 1, x, v);
	else modify(t, p << 1 | 1, x, v);
	t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
}
 
inline int query(Sgt t[], int p, int l, int r) {
	if (l <= t[p].l && t[p].r <= r) return t[p].sum;
	int mid = (t[p].l + t[p].r) >> 1, res = 0;
	if (l <= mid) res += query(t, p << 1, l, r);
	if (r > mid) res += query(t, p << 1 | 1, l, r);
	return res;
}
 
int main() {
	int n;
	cin >> n;
	cin >> s + 1;
	for (int i = 0; i < 26; i++)
		build(t[i], 1, 1, n, i);
	int m;
	cin >> m;
	while (m--) {
		int op;
		cin >> op;
		if (op == 1) {
			int x;
			char c;
			cin >> x >> c;
			modify(t[s[x] - 'a'], 1, x, 0);
			modify(t[c - 'a'], 1, x, 1);
			s[x] = c;
		}
		else {
			int l, r;
			cin >> l >> r;
			bool flg = 0;
			int now = l;
			int firs = 30, last = -1;
			for (int i = 0; i < 26; i++)
				if (query(t[i], 1, l, r))
					firs = min(firs, i), last = max(last, i);
			for (int i = 0; i < 26; i++) {
				if (flg) break;
				if (!query(t[i], 1, l, r) && (i >= firs && i <= last) && query(t[i], 1, 1, n)) flg = 1;
				if (!query(t[i], 1, l, r)) continue;
				int cnt1;
				if (i == firs || i == last) cnt1 = query(t[i], 1, l, r);
				else cnt1 = query(t[i], 1, 1, n);
				int cnt2 = query(t[i], 1, now, now + cnt1 - 1);
				now += cnt1;
				if (cnt1 != cnt2) flg = 1;
			}
			puts(flg ? "No" : "Yes");
		}
	}
	return 0;
}
```



---

## 作者：MuRongzhang (赞：0)

## 前言

《关于比赛时提交 WA，比赛刚结束我就调出了 bug 并且提交 AC 这件事》

《论 $\ge0$ 与 $>0$ 的区别》

## 尝试简化题意

记 $S_i$ 为 $S$ 的第 $i$ 个字符，$N$ 为 $S$ 的长度，$S[l,r](l \le r)$ 为 $S_lS_{l+1}\cdots S_r$，$T$ 为字符串 $S$ 中的所有字符按照字典序排列之后得到的字符串。

定义字典序在前面的字母比字典序在后面的字母小。

以 $T=$ `aabbcccde` 为例，我们先观察它有什么特点。

首先，根据定义，$A$ 的字符单调不降，那么它的子串一定单调不降。在满足单调不降的条件之后，我们并不关心每个位置的字符是什么，而是关心某种字符的数量。

如果我们提取出 $T$ 的一个子串，我们可以发现如下性质：

- $T$ 是 $T$ 的子串。
- 如果删去字典序最小或者最大的一个或多个字符之后该字符串非空，那么它仍然是 $T$ 的子串。例如： `aabbcccde -> aabbcccd -> abbcccd`。
- 如果删去的字符的字典序不是最小，也不是最大，那么它就不再是 $T$ 的子串。例如： `aabbcccd -> aabbccd`。

由于 $S[l,r]$ 是 $S$ 的子串，$S[l,r]$ 中某种字符的数量一定不会超过 $T$ 中某种字符的数量。

所以，假设构成 $S[l,r]$ 的字符为 $l_1,l_2,\cdots,l_k(l_1<l_2<\cdots <l_k, k \ge 1)$，如果对于所有的 $1 < i < k$， $S[l,r]$ 中 $l_i$ 的数量等于 $T$ 中 $l_i$ 的数量，或者 $k \le 2$，那么 $S[l,r]$ 一定是 $T$ 的子串。

因此，我们维护的信息有两个：

- 区间内某种字符的数量。

- 子字符串是否单调不降。

## 算法实现

维护区间内某种字符的数量我们可以使用前缀和等工具，但是由于题目要求修改，所以我们使用树状数组或者线段树。我们可以对每种字符都建立一个树状数组，之后将操作：

- 将 $S_x$ 改成 $c$。

变为：

- 将原来的 $S_x$ 所代表的树状数组在 $x$ 处减去 $1$，将 $c$ 所代表的树状数组在 $x$ 处加上 $1$。

之后查询 $S[l,r]$ 时对于每个字符查询 $[l,r]$ 的区间和以求出该种字符的数量，再根据上文判断是否符合条件即可。

直接维护子字符串是否单调是一项比较困难的任务，我们可以考虑什么时候子字符串不满足单调不降。容易想到，能找到一个字符（不是第一个字符）的字典序比它前面的字符小即可。

所以，我们定义一个长度为 $N$ 的序列 $b_i$ 的值为：
$$
\left\{\begin{matrix}
0, i=1 \text{ 或 } S_{i-1}>S_i
\\
1, i>1 \text{ 且 } S_{i-1}\le S_i
\end{matrix}\right.
$$

接着对序列 $b$ 建立树状数组维护区间和，并且根据 $S_{x-1}$，$S_x$，$S_{x+1}$ 和 $c$ 的大小关系更新即可。每次查询 $S[l,r]$ 时改为查询 $b$ 在 $[l+1,r]$ 的区间和是否为 $0$ 即可。

## 代码

（你可以根据前言康康这份代码是怎么出锅的qwq）

```cpp
#include<iostream>
#include<cstdio>

int n,q;
char S[100005];
int x,l,r;
char ch[5],c;
int tot[26];
int goal[26];
int res;
int L,R;
bool ans;

int lowbit(int x) {return x&(-x);}

int mylog2(int x)
{
	int res=-1;
	if(x) {x>>=1; res++;}
	return res;
}

int tree[27][100005];

void add(int id,int x,int k)
{
	while(x<=n)
	{
		tree[id][x]+=k;
		x+=lowbit(x);
	}
}

int query(int id,int x)
{
	int res=0;
	while(x)
	{
		res+=tree[id][x];
		x-=lowbit(x);
	}
	return res;
}

int main()
{
	scanf("%d",&n);
	scanf("%s",S+1);
	scanf("%d",&q);
	for(int i=1;i<=n;i++)
	{
		add(S[i]-'a',i,1);
		if(i>1 && S[i]<S[i-1]) add(26,i,1);
	}
	while(q--)
	{
		scanf("%d",&x);
		if(x==1)
		{
			scanf("%d%s",&l,ch);
			c=ch[0];
			add(c-'a',l,1);
			add(S[l]-'a',l,-1);
			if(l>1)
			{
				if(S[l-1]<=S[l] && S[l-1]>c) add(26,l,1);
				if(S[l-1]>S[l]  && S[l-1]<=c) add(26,l,-1);
			}
			if(l<n)
			{
				if(S[l]<=S[l+1] && c>S[l+1]) add(26,l+1,1);
				if(S[l]>S[l+1]  && c<=S[l+1]) add(26,l+1,-1);
			}
			S[l]=c;
		}
		else if(x==2)
		{
			scanf("%d%d",&l,&r);
			ans=true;
			res=query(26,r)-query(26,l);
			if(res)
			{
				//printf("res=%d\n",res);
				ans=false;
			}
			else
			{
				for(int i=0;i<26;i++)
				{
					goal[i]=query(i,n);
					tot[i]=query(i,r)-query(i,l-1);
					//printf("%c: %d/%d\n",i+'a',tot[i],goal[i]);
				}
				for(int i=0;i<26;i++)
				{
					L=i;
					if(tot[i]) break;
				}
				for(int i=25;i>0;i--)
				{
					R=i;
					if(tot[i]) break;
				}
				for(int i=L+1;i<R;i++)
				{	
					if(tot[i]<goal[i]) {ans=false;break;}
				}
			}
			printf("%s\n",ans?"Yes":"No");
		}
	}
    return 0;
}
```

---

## 作者：Lyu_echo (赞：0)

## 题目大意

给定长度为 $n$ 的由小写英文字母组成的字符串 $S$。

定义字符串 $T$ 为字符串 $S$ 按字典序排序后的字符串。$T$ 应当随 $S$ 改变而改变。

给定 $q$ 组操作，每组操作如下：

- `1 x c`，将 $S_x$ 赋值为 $c$，即 $S_x = c$；
- `2 l r`，询问 $S_{l,r}$ 是否为 $T$ 的子串。

其中：$S_i$ 表示字符串 $S$ 从左往右第 $i$ 个字；$S_{l,r}$ 表示字符串 $S$ 的子串区间 $S_l, S_{l+1}, \dots, S_{r-1}, S_r $。

## 解题思路

令 $S_{l,r} = A$。

若字符串 $A$ 是字符串 $T$ 的子串，不难发现满足以下要求：

- $A$ 按字典序升序排序；
- $A$ 中除首字母和尾字母外，其余的字母出现次数等同于 $S$ 中该字母的出现次数。

因此，我们可以为每个字符创建一个线段树或树状数组用来记录每个字符在某个区间出现的次数。

对于每一次询问：

令 $a$ 为询问区间的首字母，$b$ 为询问区间的尾字母。

判断字符 $a + 1$ 到 $b-1$ 是否全部都在询问区间中。

再求得每个字母对应区间，判断该区间是否全部是该字母。

上文中，$a+1$ 表示字符 $a$ 在字典序上 $+1$ 后的对应字符。如，$a = $ `A`，则 $a + 1$ = `B`。

## 代码实现

这里用的树状数组。

```cpp
int n, q;
char s[100010];
struct BIT {
   	int tree[100010];
    int lowbit(int x) {
        return x & (-x);
    }
    void add(int i, int x) {
        for (; i <= n; i += lowbit(i)) tree[i] += x;
    }
    int ask(int i) {
        int sum = 0;
        for (; i; i -= lowbit(i)) sum += tree[i];
        return sum;
    }
    int query(int l, int r) {
        return ask(r) - ask(l-1);
    }
}c[27];
void solve() {
    cin >> n;
    cin >> (s+1);
    for (int i = 1; i <= n; i++) {
        c[s[i] - 'a' + 1].add(i, 1);
    }
    cin >> q;

    while (q--) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int i;
            char x;
            cin >> i;
            cin >> x;
            c[s[i] - 'a' + 1].add(i, -1);
            c[x - 'a' + 1].add(i, 1);
            s[i] = x;
        }
        if (opt == 2) {
           	int l, r, a = 27, b = 0, k;
            cin >> l >> r;
            k = l;
            for (int i = 1; i <= 26; i++) {
                if (c[i].query(l, r) > 0) {
                    a = min(a, i);
                    b = max(b, i);
                }
            }
            bool flag = true;
            for (int i = a; i <= b; i++) {
                int tmp = c[i].query(l, r);
                if (c[i].query(k, k + tmp - 1) != tmp) {
                    flag = false;
                    break ;
                }
                if (i != a && i != b && c[i].query(1, n) > tmp) {
                    flag = false;
                    break ;
                }
            	k += tmp;
            }
            if (flag) cout << "Yes" << endl;
            else cout << "No" << endl;
        }
    }
    return ;
}
```



## 后记/一些小技巧

AtCoder 有一些库，会提供相当多的模板。赛时可以直接使用这些库，节省打模板的时间。

具体见[AtCoder官方Github页面]([GitHub - atcoder/ac-library: AtCoder Library](https://github.com/atcoder/ac-library))。



---

## 作者：DaiRuiChen007 (赞：0)

# ABC285F 题解

## 思路分析

用 $26$ 棵树状数组分别统计每个字母在特定区间中出现的次数。

每次回答询问时先得到区间中的最小字母 $lo$ 和最大字母 $hi$，先判断字母 $lo+1\sim hi-1$ 中的每个字母是不是都全部在 $[l,r]$ 中，然后简单模拟得到在每个字母对应的区间再判断这个区间是否全是该字母即可。

时间复杂度 $\Theta(|\Sigma|\times n\log n)$，$\Sigma$ 为字符集。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+1;
int n,q;
struct BitTree {
	int tree[MAXN];
	inline int lowbit(int x) { return x&-x; }
	inline void Modify(int x,int v) {
		for(;x<=n;x+=lowbit(x)) tree[x]+=v;
	}
	inline int q(int x) {
		int ret=0;
		for(;x;x-=lowbit(x)) ret+=tree[x];
		return ret;
	}
	inline int Query(int l,int r) {
		return q(r)-q(l-1);
	}
}	A[26];
char str[MAXN];
signed main() {
	scanf("%d%s%d",&n,str+1,&q);
	for(int i=1;i<=n;++i) {
		A[str[i]-'a'].Modify(i,1);
	}
	while(q--) {
		int op;
		scanf("%d",&op);
		if(op==1) {
			int x; char c;
			scanf("%d %c",&x,&c);
			A[str[x]-'a'].Modify(x,-1);
			str[x]=c;
			A[str[x]-'a'].Modify(x,1);
		} else {
			bool ok=true;
			int l,r;
			scanf("%d%d",&l,&r);
			int lo=26,hi=0;
			for(int i=0;i<26;++i) {
				if(A[i].Query(l,r)>0) {
					lo=min(lo,i),hi=max(hi,i);
				}
			}
			int x=l;
			for(int i=lo;i<=hi;++i) {
				int k=A[i].Query(l,r);
				if(lo<i&&i<hi) if(k<A[i].Query(1,n)) ok=false;
				if(A[i].Query(x,x+k-1)!=k) ok=false;
				x+=k;
			}
			puts(ok?"Yes":"No");
		}
	}
}
```

---

## 作者：Strelitzia_ (赞：0)

## 题目大意

给定一个字符串 $S$，要求支持以下两种操作：

- `1 x c`：把 $S_x$ 换成字符 $c$。
- `2 l r`：设 $T$ 为 $S$ 排序后的字符串，询问 $S_{l\cdots r}$ 是否为 $T$ 的字串。

------------
## 思路

先考虑怎样的情况下 $S_{l\cdots r}$ 是 $T$ 的子串。

- 因为 $T$ 有序，所以 $S_{l\cdots r}$ 一定有序；
- 因为是字串，所以除去与 $S_l$ 和 $S_r$ 相同的字母后，剩余的字母在 $S_{l\cdots r}$ 中出现的次数一定与这些字母在 $S$ 中出现的次数相等。

而如果 $S_{l\cdots r}$ 满足上述条件，也一定是 $T$ 的子串。因为如果不是，那么要么 $T$ 无序，要么 $S$ 中出现了不应该出现的字符，所以我们得到了 $S_{l\cdots r}$ 满足条件的充要条件。

------------
接下来我们考虑如何快速维护我们上面说到的两个数据。

首先维护 $S_{l\cdots r}$ 中每个字母出现的次数。因为小写字母只有 $26$ 个，所以我们开 $26$ 棵线段树分别维护即可。

然后维护这段序列是否有序。一种思路是合并区间信息，即记录每个区间最左的字母、最右的字母、该区间是否有序。显然长度为 $1$ 的区间必然有序，对于更长的区间需要满足：

- 两个子区间分别有序；
- 左子区间的最右侧元素小于等于右子区间最左侧元素。

这两者线段树都很好维护。给出这种维护方式的合并区间信息的代码：

```cpp
iss[p].lft = iss[p << 1].lft, iss[p].rt = iss[p << 1 | 1].rt;
iss[p].is = iss[p << 1].is && iss[p << 1 | 1].is && (iss[p << 1].rt <= iss[p << 1 | 1].lft);
```

------------
当然还有别的方法。例如我们做一个差分，那么如果原序列有序，差分完之后所有元素必定都大于等于 $0$，于是我们用线段树维护差分数组的区间最小值即可。注意这里在查询时只需要查询 $[l+1,r]$ 的最小值即可。

总复杂度 $O(\omega n\log n)$，其中 $\omega =26$。

代码如下：

```cpp
struct T1 {
	int l, r, sum;
} t[N << 2][27];//第一棵线段树：维护区间字母的出现次数
struct T2 {
	int l, r, mn;
} iss[N << 2];//第二棵线段树：维护差分数组
char ch[N], c;
int n, m, cnt[27], dis[N];
void build1(int p, int l, int r) {
	for (int i = 0; i <= 26; i++) t[p][i].l = l, t[p][i].r = r;
	if (l == r) {
		t[p][ch[l] - 'a'].sum++;
		return;
	}
	build1(p << 1, l, (l + r) >> 1), build1(p << 1 | 1, ((l + r) >> 1) + 1, r);
	for (int i = 0; i <= 26; i++) t[p][i].sum = t[p << 1][i].sum + t[p << 1 | 1][i].sum;
}
void build2(int p, int l, int r) {
	iss[p].l = l, iss[p].r = r;
	if (l == r) {
		iss[p].mn = dis[l];
		return;
	}
	build2(p << 1, l, (l + r) >> 1), build2(p << 1 | 1, ((l + r) >> 1) + 1, r);
	iss[p].mn = min(iss[p << 1].mn, iss[p << 1 | 1].mn);
}
void change1(int p, int l, int r, int x, int nowx) {
	if (t[p][x].l >= l && t[p][x].r <= r) {
		t[p][x].sum++, t[p][nowx].sum--;
		return ;
	}
	int mid = (t[p][x].l + t[p][x].r) >> 1;
	if (l <= mid) change1(p << 1, l, r, x, nowx);
	if (r > mid) change1(p << 1 | 1, l, r, x, nowx);
	for (int i = 0; i <= 26; i++) t[p][i].sum = t[p << 1][i].sum + t[p << 1 | 1][i].sum;
}
void change2(int p, int l, int r, int x) {
	if (iss[p].l >= l && iss[p].r <= r) {
		iss[p].mn = x;
		return ;
	}
	int mid = (iss[p].l + iss[p].r) >> 1;
	if (l <= mid) change2(p << 1, l, r, x);
	if (r > mid) change2(p << 1 | 1, l, r, x);
	iss[p].mn = min(iss[p << 1].mn, iss[p << 1 | 1].mn);
}
int assk1(int p, int l, int r, int x) {
	if (t[p][x].l >= l && t[p][x].r <= r) return t[p][x].sum;
	int res = 0, mid = (t[p][x].l + t[p][x].r) >> 1;
	if (l <= mid) res = assk1(p << 1, l, r, x);
	return r > mid ? res + assk1(p << 1 | 1, l, r, x) : res;
}
int assk2(int p, int l, int r) {
	if (iss[p].l >= l && iss[p].r <= r) return iss[p].mn;
	int res = 0, mid = (iss[p].l + iss[p].r) >> 1;
	if (l <= mid) res = min(res, assk2(p << 1, l, r));
	return r > mid ? min(res, assk2(p << 1 | 1, l, r)) : res;
}
signed main() {
	n = read();
	scanf("%s", ch + 1);
	for (int i = 1; i <= n; i++) cnt[ch[i] - 'a']++, dis[i] = ch[i] - ch[i - 1];
	build1(1, 1, n), build2(1, 1, n);
	m = read();
	for (int nowt = 1; nowt <= m; nowt++) {
		int type = read();
		if (type == 1) {
			int id = read();
			scanf("%c", &c);
			change1(1, id, id, c - 'a', ch[id] - 'a');
			change2(1, id, id, c - ch[id - 1]);//差分修改
			if (id != n) change2(1, id + 1, id + 1, ch[id + 1] - c);//特判防止越界
			cnt[ch[id] - 'a']--, cnt[c - 'a']++;
			ch[id] = c;
		} else {
			int l = read(), r = read();
			if (l == r) {
				puts("Yes");
				continue;
			}//特判
			int nowmn = assk2(1, l + 1, r);
			if (nowmn < 0) {
				puts("No");
				continue;
			}//情况 1 不符合
			if (ch[l] == ch[r]) {
				puts("Yes");
				continue;
			}
//			check1();
			bool hasans = 1;
			for (int i = ch[l] - 'a' + 1; i < ch[r] - 'a'; i++)
				if (assk1(1, l, r, i) != cnt[i]) {
					hasans = 0;
					break;
				}
			puts(hasans ? "Yes" : "No");
		}
	}
	return Strelitzia_;
}
```

---

## 作者：happybob (赞：0)

考虑什么样的区间可能满足要求。

满足要求的区间即一个是 $S$ 按照升序排序后的子串，那么显然这个子串也升序排序。

所以我们可以发现第一个要求是：区间 $S_l, S_{l+1}, \cdots, S_r$ 升序排序。

但是区间就算升序排序，也不一定满足要求。比如 $S$ 为 $\texttt{abdpc}$。询问区间 $[1,4]$，虽然 $[1,4]$ 是递增的，但是排序后 $\texttt{c}$ 会排在 $\texttt{b,d}$ 之间，不满足要求。

于是可以发现，当区间升序排序，设 $x=S_l+1$，$y = S_r - 1$。那么 $S$ 中所有属于区间 $[x,y]$ 的数的个数应该和第 $l$ 到 $r$ 中属于区间 $[x,y]$ 的数相同。这样排序后这些数一定在一起。

线段树维护即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5, INF = 2e9, MOD = 1e9 + 7;

inline int read()
{
	int op = 1, x = 0;
	char ch = getchar();
	while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
	while (ch == '-')
	{
		op = -op;
		ch = getchar();
	}
	while (ch >= '0' and ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * op;
}

inline void write(int x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

int n, q;
string s;
int a[N];
bool a1[N], a2[N];

class SegmentTree
{
public:
	struct Node
	{
		int l, r, ll, rr;
		bool is_as;
		friend Node operator+(const Node& x, const Node& y)
		{
			Node c;
			c.ll = x.ll;
			c.rr = y.rr;
			c.is_as = x.is_as && y.is_as && (x.rr <= y.ll);
			return c;
		}
	}tr[N << 2];
	void pushup(int u)
	{
		tr[u].ll = tr[u << 1].ll;
		tr[u].rr = tr[u << 1 | 1].rr;
		tr[u].is_as = tr[u << 1].is_as && tr[u << 1 | 1].is_as && (tr[u << 1].rr <= tr[u << 1 | 1].ll);
	}
	void build(int u, int l, int r)
	{
		tr[u] = { l, r, a[l], a[l], 1 };
		if (l == r) return;
		int mid = l + r >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
		pushup(u);
	}
	void update(int u, int x, int v)
	{
		if (tr[u].l == tr[u].r)
		{
			tr[u].ll = tr[u].rr = v;
			return;
		}
		int mid = tr[u].l + tr[u].r >> 1;
		if (x <= mid) update(u << 1, x, v);
		else update(u << 1 | 1, x, v);
		pushup(u);
	}
	Node query(int u, int l, int r)
	{
		if (tr[u].l >= l and tr[u].r <= r) return tr[u];
		int mid = tr[u].l + tr[u].r >> 1;
		Node ans;
		ans.ll = -1;
		if (l <= mid) ans = query(u << 1, l, r);
		if (r > mid)
		{
			if (ans.ll == -1) ans = query(u << 1 | 1, l, r);
			else ans = ans + query(u << 1 | 1, l, r);
		}
		return ans;
	}
}t;

class Bit
{
public:
	long long tr[N];
	void add(int x, int v)
	{
		while (x < N)
		{
			tr[x] += 1LL * v;
			x += x & -x;
		}
	}
	long long query(int x)
	{
		long long ans = 0;
		while (x)
		{
			ans += tr[x];
			x -= x & -x;
		}
		return ans;
	}
}t2;

int cnt;

int main()
{
	// freopen("*.in", "r", stdin);
	// freopen("*.out", "w", stdout);
	//ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> s >> q;
	for (int i = 1; i <= n; i++)
	{
		a[i] = s[i - 1];
		t2.add(a[i], 1);
	}
	t.build(1, 1, n);
	for (int i = 1; i <= q; i++)
	{
		int op;
		cin >> op;
		if (op == 1)
		{
			int x;
			char c;
			cin >> x >> c;
			t.update(1, x, c);
			t2.add(a[x], -1);
			a[x] = c;
			t2.add(a[x], 1);
		}
		else
		{
			int l, r;
			cin >> l >> r;
			cnt++;
			a1[cnt] = t.query(1, l, r).is_as;
			if (!a1[cnt])
			{
				cout << "No\n";
				continue;
			}
			int ll = a[l] + 1;
			int rr = a[r] - 1;
			if (ll > rr) a2[cnt] = 1;
			else
			{
				int cnts = t2.query(rr) - t2.query(ll - 1);
				int lll = upper_bound(a + l, a + r + 1, a[l]) - a;
				int rrr = lower_bound(a + l, a + r + 1, a[r]) - 1 - a;
				if (cnts > rrr - lll + 1) a2[cnt] = 0;
				else a2[cnt] = 1;
			}
			if (a2[cnt] && a1[cnt]) cout << "Yes\n";
			else cout << "No\n";
		}
	}
	return 0;
}
```


---

## 作者：_Imaginary_ (赞：0)

### 前言

我和官方题解思路类似，但用了一种和官方题解不太相同的实现方法，不过码量高达四千。

## 问题

一道数据结构题。给你一个字符串，支持两个操作：

1. 单点修改；

2. 查询字符串的某一段是否是把整个字符串按升序排列后，新的数组的子串。

关键在于第二个操作。我们发现它可以转化成以下两个条件的叠加：

- 字符串的这一段是不降排列的；

- 不妨假设这一段涉及到了 $\texttt{f,g,...,m,n}$ 这些字母，那么要求 $\texttt{g,h,...,l,m}$ 这些字母只出现在字符串的这一段里。

## 实现

对于处理字母出现的次数，且支持单点修改区间查询，很容易想到开 $26$ 个树状数组或线段树，维护每一个字母。

对于字符串是升序排列的，我联想到了数组的最长不降子序列类似的问题。所以我维护了：

- $f[i]$ 表示 $i$ 位置所在的最长不降子序列的开头；

- $b[i]$ 表示 $i$ 位置所在的最长不降子序列的结尾。

这样，查询操作就被轻松搞定了。因为，假设我们要查询 $[l,r]$ 是否是不降的，等价于 $b[l]\ge r$。

最后，处理单点修改。这也是比较搞的一点，但是处理只有一句关键的话。

假如是 $x$ 位置，原来字符是 $p$，新的字符是 $c$，那么**维护 $x$ 所在的最长不降子序列**。

很简单。通过 $S[x-1]\le c$ 和 $S[x+1]\ge c$ 是否成立，我们可以判断新的最长不降子序列的长度。

不过，如果 $S[x-1]>c$，说明 $x-1$ 所在的子序列的末端被在 $x-1$ 处截断了，即 $[f[x-1],x-1]$ 上的点的 $b$ 数组全部重置为 $x-1$。

对于 $x+1$ 类似讨论。

我们发现这个数据结构只需要维护：

1. 区间覆盖同一个值；

2. 单点查询（即，查询某一个 $f[x]$ 或 $b[x]$）。

用两个线段树分别维护 $f$ 数组和 $b$ 数组即可。

代码比较冗长，只放主函数部分。其中 $t[i]$ 代表字符 $\texttt{a}+i-1$ 对应的线段树，$f,b$ 上面解释过了。

```cpp
#define F(i) F.a[i]
#define B(i) B.a[i]
int lnds[N];
int u[N];
int main()
{
	scanf("%d%s",&n,s+1);
	for(int i=1;i<=n;i++) a[i]=s[i]-'a'+1;
	for(int i=1;i<=n;i++) t[a[i]].u(i,i,1);
	lnds[n]=1;
	for(int i=n-1;i>=1;i--)
	{
		if(s[i+1]>=s[i]) lnds[i]=lnds[i+1]+1;
		else lnds[i]=1;
	}
	int cur=1;
	for(int i=1;i<=n;i++)
	{
		if(lnds[i-1]==1)
		{
			cur=i;
			F(i)=i;
		}
		else F(i)=cur;
	}
	cur=n;
	for(int i=n;i>=1;i--)
	{
		if(lnds[i]==1)
		{
			cur=i;
			B(i)=i;
		}
		else B(i)=cur;
	}
	F.build(1,1,n); B.build(1,1,n);
	int qwq;
	int ta,x,p,c,l,r;
	char ch[2];
	scanf("%d",&qwq);
	while(qwq--)
	{
		scanf("%d",&ta);
		if(ta==1)
		{
			scanf("%d%s",&x,ch);
			c=ch[0]-'a'+1;
			p=a[x];
			if(p==c) continue;
			t[p].u(x,x,-1);
			t[c].u(x,x,1);
			a[x]=c;
				int l1=x,r1=x;
				if(x!=1)
				{
					if(a[x-1]<=p&&a[x-1]>c)
						B.u(F.q(x-1,x-1),x-1,x-1);
					if(a[x-1]<=c)
						l1=F.q(x-1,x-1);
				}
				if(x!=n)
				{
					if(a[x+1]>=p&&a[x+1]<c)
						F.u(x+1,B.q(x+1,x+1),x+1);
					if(a[x+1]>=c)
						r1=B.q(x+1,x+1);
				}
				F.u(l1,r1,l1);
				B.u(l1,r1,r1);
		}
		if(ta==2)
		{
			scanf("%d%d",&l,&r);
			if(B.q(l,l)<r)
			{
				printf("No\n");
				continue;
			}
			int u[27];
			int L,R;
			for(int i=1;i<=26;i++)
			{u[i]=t[i].q(l,r);
			}
			for(int i=1;i<=26;i++)
			{
				if(u[i]!=0)
				{
					L=i;
					break;
				}
			}
			for(int i=26;i>=1;i--)
			{
				if(u[i]!=0)
				{
					R=i;
					break;
				}
			}
			for(int i=L+1;i<=R-1;i++)
			{
				if(u[i]!=t[i].val[1])
				{
					printf("No\n");
					goto end;
				}
			}
			printf("Yes\n");
		}
		end:;
	}
	return 0;
}
```

---

