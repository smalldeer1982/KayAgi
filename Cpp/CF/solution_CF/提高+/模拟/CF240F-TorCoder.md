# TorCoder

## 题目描述

A boy named Leo doesn't miss a single TorCoder contest round. On the last TorCoder round number 100666 Leo stumbled over the following problem. He was given a string $ s $ , consisting of $ n $ lowercase English letters, and $ m $ queries. Each query is characterised by a pair of integers $ l_{i},r_{i} $ $ (1<=l_{i}<=r_{i}<=n) $ .

We'll consider the letters in the string numbered from 1 to $ n $ from left to right, that is, $ s=s_{1}s_{2}...\ s_{n} $ .

After each query he must swap letters with indexes from $ l_{i} $ to $ r_{i} $ inclusive in string $ s $ so as to make substring $ (l_{i},r_{i}) $ a palindrome. If there are multiple such letter permutations, you should choose the one where string $ (l_{i},r_{i}) $ will be lexicographically minimum. If no such permutation exists, you should ignore the query (that is, not change string $ s $ ).

Everybody knows that on TorCoder rounds input line and array size limits never exceed $ 60 $ , so Leo solved this problem easily. Your task is to solve the problem on a little bit larger limits. Given string $ s $ and $ m $ queries, print the string that results after applying all $ m $ queries to string $ s $ .

## 说明/提示

A substring $ (l_{i},r_{i}) $ $ 1<=l_{i}<=r_{i}<=n) $ of string $ s=s_{1}s_{2}...\ s_{n} $ of length $ n $ is a sequence of characters $ s_{li}s_{li+1}...s_{ri} $ .

A string is a palindrome, if it reads the same from left to right and from right to left.

String $ x_{1}x_{2}...\ x_{p} $ is lexicographically smaller than string $ y_{1}y_{2}...\ y_{q} $ , if either $ p&lt;q $ and $ x_{1}=y_{1},x_{2}=y_{2},...\ ,x_{p}=y_{p} $ , or exists such number $ r $ $ (r&lt;p,r&lt;q) $ , that $ x_{1}=y_{1},x_{2}=y_{2},...\ ,x_{r}=y_{r} $ and $ x_{r+1}&lt;y_{r+1} $ .

## 样例 #1

### 输入

```
7 2
aabcbaa
1 3
5 7
```

### 输出

```
abacaba
```

## 样例 #2

### 输入

```
3 2
abc
1 2
2 3
```

### 输出

```
abc
```

# 题解

## 作者：henrytb (赞：20)

[**更好的阅读体验**](https://blog.henrytb.ml/2021/01/%E9%A2%98%E8%A7%A3-CF240F-TorCoder/)

考虑开 26 棵线段树。每棵线段树维护它对应的字母在这个字符串中的出现情况。

然后我们考虑，什么样的区间能转换成一个回文串呢？

这个区间中，出现的任何字母的出现次数**要么都为偶数，要么只有一个奇数，其余都是偶数**时，这个区间可以通过字母重排变为一个回文串。所以每棵线段树都需要支持区间求和以查询区间中特定字母的出现次数。

如果可以转换，怎么让这个区间重排之后字典序最小？

思想：字典序越小的字母，我们优先把它放前面就可以了。

具体来说，如果字母的出现次数中有一个奇数，那么先把出现了奇数次的这个字母单拎出来扔到中间。然后，为了保证字典序最小，我们从 $a$ 到 $z$ ，从两边到中间放即可。对于每个字母，一边放一半。因此我们的每棵线段树需要支持区间赋值的操作。

具体见代码：

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int N=1e5+5;
struct Segment{
    int l,r;
    int sum,tag;
}t[26][N<<2];
int n,m;
char s[N];
void pushup(int tr,int p) {
    t[tr][p].sum=t[tr][p<<1].sum+t[tr][p<<1|1].sum;
}
void pushdown(int tr,int p) {
    if(t[tr][p].tag!=-1) {
        t[tr][p<<1].tag=t[tr][p].tag;
        t[tr][p<<1|1].tag=t[tr][p].tag;
        t[tr][p<<1].sum=(t[tr][p<<1].r-t[tr][p<<1].l+1)*t[tr][p].tag;
        t[tr][p<<1|1].sum=(t[tr][p<<1|1].r-t[tr][p<<1|1].l+1)*t[tr][p].tag;
        t[tr][p].tag=-1;
    }
}
void build(int tr,int p,int l,int r) {
    t[tr][p].l=l;t[tr][p].r=r;
    t[tr][p].sum=0;t[tr][p].tag=-1;
    if(l==r) {
        t[tr][p].sum=(s[l]-'a')==tr;
        return ;
    }
    int mid=(l+r)>>1;
    build(tr,p<<1,l,mid);
    build(tr,p<<1|1,mid+1,r);
    pushup(tr,p);
}
void modify(int tr,int p,int l,int r,int val) {
    if(l<=t[tr][p].l&&t[tr][p].r<=r) {
        t[tr][p].tag=val;
        t[tr][p].sum=(t[tr][p].r-t[tr][p].l+1)*val;
        return ;
    }
    pushdown(tr,p);
    int mid=(t[tr][p].l+t[tr][p].r)>>1;
    if(l<=mid) modify(tr,p<<1,l,r,val);
    if(mid<r) modify(tr,p<<1|1,l,r,val);
    pushup(tr,p);
}
int query(int tr,int p,int l,int r) {
    if(l<=t[tr][p].l&&t[tr][p].r<=r) return t[tr][p].sum;
    pushdown(tr,p);
    int mid=(t[tr][p].l+t[tr][p].r)>>1,ans=0;
    if(l<=mid) ans+=query(tr,p<<1,l,r);
    if(mid<r) ans+=query(tr,p<<1|1,l,r);
    return ans;
}
int main() {
    #ifdef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    scanf("%d%d%s",&n,&m,s+1);
    rep(i,0,25) build(i,1,1,n);
    rep(i,1,m) {
        int l,r;
        scanf("%d%d",&l,&r);
        int tim[26],odd=0;
        int nedod=-1;
        rep(j,0,25) tim[j]=query(j,1,l,r);
        rep(j,0,25) if(tim[j]&1) ++odd,nedod=j;
        if(odd>1) continue;
        rep(j,0,25) modify(j,1,l,r,0);
        if(odd) --tim[nedod],modify(nedod,1,(l+r)>>1,(l+r)>>1,1);
        int nl=l,nr=r;
        rep(j,0,25) if(tim[j]) { // 从两边向中间放，一边放一半
            modify(j,1,nl,nl+tim[j]/2-1,1);
            nl+=tim[j]/2;
            modify(j,1,nr-tim[j]/2+1,nr,1);
            nr-=tim[j]/2;
        }
    }
    rep(i,1,n) {
        rep(j,0,25) if(query(j,1,i,i)) {
            printf("%c",j+'a');
        }
    }
    return 0;
}
```

---

## 作者：Zvelig1205 (赞：9)

# CF240F TorCoder

由于我是个蒟蒻，只会打暴力，所以我用分块水掉了这个题。

## 思路

考虑几个性质：

1. 能构成回文串的字符串，出现次数为奇数次的字母 **（下文简称奇字母）** 至多 1 个。

	比如，`aaabbb` 这个字符串，奇字母有 2 个，显然不能构成回文串。

2. 满足性质 1 且含奇字母的字符串，必有一个奇字母要放在回文串的中间。

	这个应该很好理解。

3. 满足性质 1 且含奇字母的字符串长度必为奇数。

	除了奇字母，每个字母出现次数都是偶数，再加上奇字母的次数。

	$\text{偶}+\text{奇}=\text{奇}$。

	~~好像并不是很有用。~~

根据以上三个性质，基本思路就很好写了。

首先统计区间 $[l,r]$ 之间每个字母的出现次数，然后判断一下是否满足性质 1。

如果不满足，说明不能构成回文串，本次操作结束。

否则，可以构成回文串，先将奇字母放在中间（没有则不放），然后两边向中间推平。

因为要保证字典序最小，所以就贪心的，遍历一遍桶，依次推平原序列

举个例子，比如要将 `a a h z z` 构成回文串。

假设回文串初始状态是这样：`_ _ _ _ _`；

先将 `h` 放在中间：`_ _ h _ _`；

然后将 `aa` 分别放在 **最两端**：`a _ h _ a`；

再将 `zz` 放在 **次两端**：`a z h z a`；

显然，对桶求和必然与区间长度相等，所以不会出现奇怪的错误。

不过，对于推平操作，还有一个更加简单的维护方法：

还是以上边的 `a a h z z` 为例，

先将 `a` 推平：`a a a a a`；

然后将 `z` 推平：`a z z z a`；

最后将 `h` 放在中间：`a z h z a`；

注意，这里的奇字母的处理绝对要放在最后！

至于原因，仔细想想，应该很好理解。

最后，代码：

```cpp
const int inf=1e5+7;
int n,m,len;
char s[inf];
int a[inf],T[400][30];
int bel[inf],L[400],R[400],tag[400];
int cnt[30],odd,mid;
void pushdown(int in)
{//下放懒标
	if(tag[in]==0)return;
	for(int i=L[in];i<=R[in];i++)
		a[i]=tag[in];
	tag[in]=0;
}
void tongji(int l,int r)
{//统计出现次数
	int lin=bel[l],rin=bel[r];
	memset(cnt,0,sizeof(cnt));
	if(lin==rin)
	{
		pushdown(lin);
		for(int i=l;i<=r;i++)
			cnt[a[i]]++;
		return;
	}
	pushdown(lin);pushdown(rin);
	for(int i=l;i<=R[lin];i++)
		cnt[a[i]]++;
	for(int i=L[rin];i<=r;i++)
		cnt[a[i]]++;
	for(int i=lin+1;i<rin;i++)
		for(int k=1;k<=26;k++)
			cnt[k]+=T[i][k];
}
void baoli(int l,int r,int k)
{//零散块暴力
	int in=bel[l];
	pushdown(in);
	for(int i=l;i<=r;i++)
		T[in][a[i]]--,a[i]=k,T[in][k]++;
}
void assign(int l,int r,int k)
{
	int lin=bel[l],rin=bel[r];
	if(lin==rin){baoli(l,r,k);return;}
	baoli(l,R[lin],k);baoli(L[rin],r,k);
	for(int i=lin+1;i<rin;i++)
	{//整块维护
		memset(T[i],0,sizeof(T[i]));
		T[i][k]=R[i]-L[i]+1;tag[i]=k;
	}
}
void judge(int l,int r)
{//判断是否能构成回文串
	odd=0,mid=0;
	for(int i=1;i<=26;i++)
		if(cnt[i]&1)odd++,mid=i;
	if(odd>1)return;//不满足性质 1
	for(int i=1;i<=26;i++)
	{
		int len=cnt[i]>>1;
		if(len==0)continue;
		assign(l,r,i);//推平
		l+=len,r-=len;
	}
	if(odd==1)
	{//处理奇字母
		int ls=(l+r)>>1;
		baoli(ls,ls,mid);
		//对于奇字母的处理，不要只是单纯的修改，记得先下放懒标！！！
	}
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	n=re();m=re();len=sqrt(n);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)
		a[i]=s[i]-'a'+1;
	for(int i=1;i<=len;i++)//分块
		L[i]=R[i-1]+1,R[i]=L[i]+len-1;
	R[len]=n;
	for(int i=1;i<=len;i++)//分块
		for(int j=L[i];j<=R[i];j++)
			bel[j]=i,T[i][a[j]]++;
	for(int i=1;i<=m;i++)
	{
		int l=re(),r=re();
		tongji(l,r),judge(l,r);
	}
	for(int i=1;i<=len;i++)
	{
		pushdown(i);//输出时也不要忘记下放懒标
		for(int j=L[i];j<=R[i];j++)
			putchar(a[j]+'a'-1);
	}
	return 0;
}
```


---

## 作者：Mobius127 (赞：6)

DS 事好文明，字符串是坏文明！！1

[题目传送门](https://www.luogu.com.cn/problem/CF240F)

题目大意：给出一个字符串 $S$ ，每次给定一个区间 $[l,\ r]$ ，把该区间的字符串修改成回文串且新的回文串在所有可形成的串里面字典序最小，求 $m$ 次操作后的字符串 $S'$ 。

~~口胡一分钟，代码一小时~~

首先珂以意识到， 每次是需要重排一整个区间的（即区间推平 / 赋值操作），我们想到线段树。

再回头，我们如何判断区间 $[l,\ r]$ 形成串 $Z$ 能重排成一个回文串？

十分容易，我们只需按如下分类讨论即可：

- 若 $|Z|$ 为偶数，则 $Z$ 内各种字母的出现次数均为偶数；
- 若 $|Z|$ 为奇数，则 $Z$ 内有且仅有一种字母出现次数为奇数。

解决完这个问题，我们来到下一个问题：如何排成回文串？

这个简单，因为回文串是对称的，我们只需在 $|Z|$ 为奇数的时候把多出的那一个放进 $[l,\ r]$ 的中间部分后，其他相同的两两一组放到未填充的边界（最左和最右）即可形成回文串。

此时我们还剩一个问题：如何使字典序最小？

**这个我会！！1**把最小的字母先放前面不就好了。

到这里我们总结一下上面的步骤：

1. 查询区间内各种字母的个数，判断是否能排；$O(n)$
1. 若 $|Z|$  为奇数，则先将多出的一个放入 $Z$ 的中间；$O(1)$
1. 将字母从小到大对称放置。$O(n)$

这整波操作是 $O(mn)$ 的，直接爆炸。

回到我们开始的线段树，发现操作 1 的个数统计，线段树珂以加速成 $O(log_2n)$ 。

同理，操作 2/3 都是区间赋值操作，同样可以拿线段树维护。

这题我懒不想打一颗线段树，就拿了空间换。~~反正卡不掉~~

那么时间就降至了 $O(mlog_2n)$ 。至此，本题得到完美解决。

说句闲话：窝 add 没给初值调了 $0.5h$ 。

### Code

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <vector>
#define N 100005
using namespace std;
typedef long long ll;
const int INF=0x3f3f3f3f;
inline int read(){
	char ch=getchar();int x=0, f=1;
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
int n, m;
char c[N];
struct Sedgment_Tree{
	#define ls k<<1
	#define rs k<<1|1
	#define mid (l+r>>1)
	char key;
	int sum[N*4], tag[N*4];
	int siz[N*4]; 
	//tag表示这个区间的字母是否被推平(1)/赋值(2)
	void pushup(int k){sum[k]=sum[ls]+sum[rs];return ;}
	void upd(int k, int tg){
		tag[k]=tg;
		if(tg==1) sum[k]=0;
		else sum[k]=siz[k];
		return ;
	}
	void pushdown(int k){
		if(!tag[k]) return ;
		upd(ls, tag[k]);upd(rs, tag[k]);tag[k]=0;
		return ;
	}
	void build(int k, int l, int r){
		siz[k]=r-l+1;
		if(l==r){sum[k]=c[l&r]==key; return;}
		build(ls, l, mid);build(rs, mid+1, r);
		return pushup(k);
	}
	void change(int k, int l, int r, int x, int y, int flg){
		if(x<=l&&r<=y) return upd(k, flg);pushdown(k);
		if(x<=mid) change(ls, l, mid, x, y, flg);
		if(mid<y) change(rs, mid+1, r, x, y, flg);
		pushup(k);
	}
	int query(int k, int l, int r, int x, int y){
		if(x<=l&&r<=y) return sum[k];pushdown(k);int ret=0;
		if(x<=mid) ret+=query(ls, l, mid, x, y);
		if(mid<y) ret+=query(rs, mid+1, r, x, y);
		return ret;
	}
	void pushall(int k, int l, int r){
		if(siz[k]==1){sum[k]?c[l&r]=key:0;return ;}
		pushdown(k);
		pushall(ls, l, mid);pushall(rs, mid+1, r);
	}
}seg[26];
void modify(int *cnti, int fl, int fr, int rl, int rr){
	//将cnt内的字母按照最小字典序回文串的方式摆放
	for(int i=0; i<26; i++){
		if(!cnti[i]) continue;
		int len=cnti[i]/2;
		seg[i].change(1, 1, n, fl, fl+len-1, 2);
		seg[i].change(1, 1, n, rr-len+1, rr, 2);
		fl=fl+len;
		rr=rr-len;
	} 
	return ;
}
int cnt[30], st;
signed main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d", &n, &m);
	scanf("%s", c+1);
	for(int i=0; i<26; i++){
		seg[i].key=i+'a';
		seg[i].build(1, 1, n);
	}
	for(int i=1, x, y; i<=m; i++){
		scanf("%d%d", &x, &y);
		int len=y-x+1, add=0;
		for(int i=0; i<26; i++) 
			cnt[i]=seg[i].query(1, 1, n, x, y), add+=cnt[i]&1, cnt[i]&1?st=i:0;
		if(add>2||(!(len&1) && add)) continue;
		for(int i=0; i<26; i++)
			seg[i].change(1, 1, n, x, y, 1);
			//这个操作必须放在特判之后 
		if(len&1){
			cnt[st]--;
			seg[st].change(1, 1, n, (x+y>>1), (x+y>>1), 2);
		}
		modify(cnt, x, ((x+y)>>1)-(len&1), ((x+y)>>1)+(len&1), y);
	}
	for(int i=0; i<26; i++) seg[i].pushall(1, 1, n);
	printf("%s\n", c+1);
	return 0;
}

```

拜拜~

---

## 作者：Dilute (赞：5)

[$$\color{darkblue}\huge\texttt{在本人blog食用更佳}$$](https://dilute.xyz/2019/06/03/Solutions/Solution-CF240F/)

### 线段树乱搞

考虑如果要重排一段区间使得它是回文的是可行的

首先对这段区间的长度分类讨论

<!--more-->

如果它的长度是奇数，那么在这个区间的数肯定满足以下条件：

- 有一个字母出现了奇数次（这个放在最中间）
- 其他的出现了偶数次（放在旁边）

如果它的长度是偶数，那么这个区间内出现过的数肯定都出现过了偶数次

再考虑如何构造

- 如果长度是奇数，把那个出现了奇数次的数放一个在最中间
- 枚举A~Z，从最左和最右分别开始一直放（因为需要保证字典序最小）

容易发现这只需要线段树维护区间每个字母的出现次数就行了（也可以理解成26棵线段树）

### 代码

```cpp
#include<bits/stdc++.h>

#define ll long long
#define INF 2147483647
#define lc(a) ((a) << 1)
#define rc(a) ((a) << 1 | 1)

int inp(){
    char c = getchar();
    while(c < '0' || c > '9')
        c = getchar();
    int sum = 0;
    while(c >= '0' && c <= '9'){
        sum = sum * 10 + c - '0';
        c = getchar();
    }
    return sum;
}

struct SEG{
    int l;
    int r;
    int sum[30];
    int lazy;

    void clear(){
        memset(sum, 0, sizeof(sum));
    }
};
int cnt[30];

char s[100010];

SEG operator + (SEG a, SEG b){
    if(a.l == -1)
        return b;
    if(b.l == -1)
        return a;
    SEG ret;
    ret.l = a.l;
    ret.r = b.r;
    for(int i = 0; i < 26; i++)
        ret.sum[i] = a.sum[i] + b.sum[i];
    return ret;
}

struct SEG_Tree{
    SEG t[800010];
    
    void push_up(int cur){
        for(int i = 0; i < 26; i++)
            t[cur].sum[i] = t[lc(cur)].sum[i] + t[rc(cur)].sum[i];
    }

    void build(int cur, int l, int r){
        t[cur].lazy = -1;
        t[cur].l = l;
        t[cur].r = r;
        if(l == r){
            t[cur].clear();
            t[cur].sum[s[l] - 'a'] = 1;
            return ;
        }
        int mid = (l + r) >> 1;
        build(lc(cur), l, mid);
        build(rc(cur), mid + 1, r);
        push_up(cur);
    }

    void push_down(int cur){
        if(t[cur].lazy != -1){
            t[lc(cur)].clear();
            t[rc(cur)].clear();
            t[lc(cur)].sum[t[cur].lazy] = t[lc(cur)].r - t[lc(cur)].l + 1;
            t[rc(cur)].sum[t[cur].lazy] = t[rc(cur)].r - t[rc(cur)].l + 1;
            t[lc(cur)].lazy = t[rc(cur)].lazy = t[cur].lazy;
        }
        t[cur].lazy = -1;
    }

    void query(int cur, int l, int r){
        SEG nul;
        nul.l = -1;
        if(t[cur].l > r || t[cur].r < l)
            return ;
        push_down(cur);
        if(t[cur].l >= l && t[cur].r <= r){
            for(int i = 0; i < 26; i++)
                cnt[i] += t[cur].sum[i];
            return ;
        }
        query(lc(cur), l, r);
        query(rc(cur), l, r);
    }

    void modify(int cur, int l, int r, int c){
        if(t[cur].l > r || t[cur].r < l)
            return ;
        if(t[cur].l >= l && t[cur].r <= r){
            t[cur].clear();
            t[cur].sum[c] = t[cur].r - t[cur].l + 1;
            t[cur].lazy = c;
            return ;
        }
        push_down(cur);
        modify(lc(cur), l, r, c);
        modify(rc(cur), l, r, c);
        push_up(cur);
    }

    void print(int cur){
        if(t[cur].l == t[cur].r){
            for(int i = 0; i < 26; i++)
                if(t[cur].sum[i])
                    putchar('a' + i);
            return ;
        }
        push_down(cur);
        print(lc(cur));
        print(rc(cur));
    }
}t;

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n = inp();
    int q = inp();
    scanf("%s", s + 1);
    t.build(1, 1, n);
    while(q--){
        int l = inp();
        int r = inp();
        memset(cnt, 0, sizeof(cnt));
        t.query(1, l, r);
        if((r - l + 1) & 1){
            int cs = 0, num;
            for(int i = 0; i < 26; i++)
                if(cnt[i] & 1){
                    cs++;
                    num = i;
                }
            if(cs == 1){
                int mid = (l + r) >> 1;
                t.modify(1, mid, mid, num);
                int cc = 0;
                for(int i = 0; i < 26; i++){
                    if(cnt[i] <= 1)
                        continue;
                    int c2 = cc + (cnt[i] >> 1);
                    t.modify(1, l + cc, l + c2 - 1, i);
                    t.modify(1, r - c2 + 1, r - cc, i);
                    cc = c2;
                }
            }
        } else {
            int cs = 0, num = -1;
            for(int i = 0; i < 26; i++)
                if(cnt[i] & 1){
                    cs++;
                    num = i;
                }
            if(cs == 0){
                int cc = 0;
                for(int i = 0; i < 26; i++){
                    if(cnt[i] == 0)
                        continue;
                    int c2 = cc + (cnt[i] >> 1);
                    t.modify(1, l + cc, l + c2 - 1, i);
                    t.modify(1, r - c2 + 1, r - cc, i);
                    cc = c2;
                }
            }
        }
    }
    t.print(1);
    putchar('\n');
}
```



---

## 作者：APJifengc (赞：2)

# 题目大意

给定一个仅包含小写字母的字符串 $S$，有 $m$ 次修改，每次修改会将子串 $S[l..r]$ 中的所有字母重排成一个新的字符串，满足新字符串是回文串且字典序最小，如果无法满足就忽略本次修改，求 $m$ 次修改后的字符串。

# 题解

首先我们思考什么时候可以修改，什么时候不能修改。

发现回文串有一个性质：如果回文串长度为奇数，那么肯定有且仅有一个字母出现了奇数次，而如果回文串长度为偶数，肯定不会有字符出现奇数次。

如果满足上面的条件，那么一定能构造出一个回文串。

我们可以先考虑统计每一个字符的数量：发现字符集只有 $26$，所以我们可以直接暴力使用 $26$ 个某种数据结构统计一段区间内有多少个这个字符。

那么统计出来数量之后，如何构造？

我们分别来考虑偶数长度和奇数长度：

偶数长度比较简单，我们需要满足字典序最小，那么我们可以先填前一半，直接从 $a$ 开始填，一直填到 $z$，然后后一半直接对应的填过去，这样就可以满足字典序最小。

奇数长度的话，我们需要记录一下出现了奇数次的那一个字符在哪里。我们首先单独拿出来一个这个字符，放在最中间，然后剩下的还按照偶数长度的进行构造就可以。

发现这样构造正好也会使得同一个字符所在的位置是一个区间，所以我们直接进行区间修改即可。

回顾一下，我们需要一个数据结构，满足：

- 区间求和
- 区间赋值

所以直接线段树维护就可以了。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
int n, m;
struct SegmentTree {
    struct Node {
        int sum, set;
    }t[MAXN << 2];
    #define lc (i << 1)
    #define rc (i << 1 | 1)
    void pushUp(int i) {
        t[i].sum = t[lc].sum + t[rc].sum;
    }
    void pushDown(int i, int l, int r) {
        if (t[i].set != -1) {
            int mid = (l + r) >> 1;
            t[lc].sum = (mid - l + 1) * t[i].set;
            t[rc].sum = (r - mid) * t[i].set;
            t[lc].set = t[i].set;
            t[rc].set = t[i].set;
            t[i].set = -1;
        }
    }
    void build(int i = 1, int l = 1, int r = n) {
        if (l == r) {
            t[i].set = -1;
            return;
        }
        int mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        t[i].set = -1;
    }
    void set(int a, int b, int v, int i = 1, int l = 1, int r = n) {
        if (l > r) return;
        if (a <= l && r <= b) {
            t[i].set = v;
            t[i].sum = (r - l + 1) * v;
            return;
        }
        pushDown(i, l, r);
        int mid = (l + r) >> 1;
        if (a <= mid) set(a, b, v, lc, l, mid);
        if (b > mid) set(a, b, v, rc, mid + 1, r);
        pushUp(i);
    }
    int query(int a, int b, int i = 1, int l = 1, int r = n) {
        if (a <= l && r <= b) {
            return t[i].sum;
        }
        pushDown(i, l, r);
        int mid = (l + r) >> 1;
        int ans = 0;
        if (a <= mid) ans += query(a, b, lc, l, mid);
        if (b > mid) ans += query(a, b, rc, mid + 1, r);
        return ans;
    }
}st[26];
char ch[MAXN];
int cnt[26];
int main() {
    scanf("%d%d%s", &n, &m, ch + 1);
    for (int i = 0; i < 26; i++) st[i].build();
    for (int i = 1; i <= n; i++) {
        st[ch[i] - 'a'].set(i, i, 1);
    }
    while (m--) {
        int l, r; scanf("%d%d", &l, &r);
        for (int i = 0; i < 26; i++) cnt[i] = st[i].query(l, r);
        int odd = -1;
        bool flag = false;
        for (int i = 0; i < 26; i++) {
            if (cnt[i] & 1) { // 出现奇数次
                if ((r - l + 1) & 1) { // 奇数回文串
                    if (odd != -1) { // 存在两个出现奇数次的字符，无解
                        flag = true;
                        break;
                    } else {
                        odd = i;
                    }
                } else { // 偶数回文串，无解
                    flag = true;
                    break;
                }
            }
        }
        if (flag) continue;
        int cc = 0;
        if (odd != -1) {
            st[odd].set(l, r, 0);
            int mid = (l + r) >> 1;
            st[odd].set(mid, mid, 1);
        }
        for (int i = 0; i < 26; i++) {
            cnt[i] /= 2;
            if (cnt[i] == 0) continue;
            if (i != odd) st[i].set(l, r, 0);
            st[i].set(l + cc, l + cc + cnt[i] - 1, 1);
            st[i].set(r - cc - cnt[i] + 1, r - cc, 1);
            cc += cnt[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 26; j++) {
            if (st[j].query(i, i) == 1) {
                printf("%c", 'a' + j);
                break;
            }
        }
    }
    return 0;
}
```

# 后记

~~应该不会有人和我一样把出现奇数次的字符全部放在最中间，然后 WA 调半天吧~~

---

## 作者：Terac (赞：2)

## 题意

给定一个由 $\texttt{a}$ 至 $\texttt{z}$ 组成的字符串，支持：
+ 重构区间 $\left[l,r\right]$ 使其构成一个字典序最小的回文串。
+ 最后整体查询。  

## 题解  

让重构的回文串字典序最小，就要让字典序小的排到更接近 $l,r$ 的位置，所以字典序小的字母优先计算。  

对于每个字母，开棵线段树，维护该字母在区间内出现的次数，每次重构操作就推平，按字典序从小到大填满整个区间，这个很容易实现。  

构造时区间长度会影响判断无解。  

+ 当区间长度为奇数时，至少有一类字母出现次数为奇数，把这类字母放一个到回文中心。如果出现次数为奇数的字母数大于 $1$，显然回文串构造不出来，无解。  

+ 当区间长度为偶数时，若存在某类字母出现了奇数，显然就构造不出，且每次会出现至少 $2$ 类，所以可以和第一类一起判了。  

按字典序从 $\texttt{a}$ 到 $\texttt{z}$ 依次推平重构即可满足构成字典序最小的字符串。  

时间复杂度为 $O(n\log n)$，再乘个字符集的常数 $O(\Sigma)$，$\Sigma=26$。  

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, Sigma = 26;
int n, m;
char s[N];
int a[N];
struct SegmentTree {
	int tag, sum, l, r;
} t[Sigma][N << 2];
#define ls x << 1
#define rs x << 1 | 1
void pushup(int num, int x) { t[num][x].sum = t[num][ls].sum + t[num][rs].sum; }
void pushdown(int num, int x) {
	if(~t[num][x].tag) {
		t[num][ls].tag = t[num][rs].tag = t[num][x].tag;
		t[num][ls].sum = (t[num][ls].r - t[num][ls].l + 1) * t[num][ls].tag;
		t[num][rs].sum = (t[num][rs].r - t[num][rs].l + 1) * t[num][rs].tag;
		t[num][x].tag = -1;
	}
}
void build(int num, int x, int l, int r) {
	t[num][x].l = l, t[num][x].r = r, t[num][x].tag = -1;
	if(l == r) {
		t[num][x].sum = a[l] == num;
		return;
	}
	int mid = (l + r) >> 1;
	build(num, ls, l, mid);
	build(num, rs, mid + 1, r);
	pushup(num, x);
}
void update(int num, int x, int l, int r, int val) {
	if(l <= t[num][x].l && t[num][x].r <= r) {
		t[num][x].tag = val;
		t[num][x].sum = (t[num][x].r - t[num][x].l + 1) * val;
		return;
	}
	pushdown(num, x);
	if(l <= t[num][ls].r) update(num, ls, l, r, val);
	if(t[num][rs].l <= r) update(num, rs, l, r, val);
	pushup(num, x);
}
int query(int num, int x, int l, int r) {
	if(l <= t[num][x].l && t[num][x].r <= r)
		return t[num][x].sum;
	pushdown(num, x);
	int res = 0;
	if(l <= t[num][ls].r) res += query(num, ls, l, r);
	if(t[num][rs].l <= r) res += query(num, rs, l, r);
	return res;
}
int cnt[Sigma], num, tot, curl, curr;
bool check;
int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d%s", &n, &m, s + 1);
	for(int i = 1; i <= n; i++)
		a[i] = s[i] - 'a';
	for(int i = 0; i < Sigma; i++)
		build(i, 1, 1, n);
	while(m--) {
		int l, r;
		tot = num = 0;
		scanf("%d%d", &l, &r);
		curl = l, curr = r;
		check = false;
		for(int i = 0; i < Sigma; i++) {
			cnt[i] = query(i, 1, l, r);
			if(cnt[i] & 1)
				tot++, num = i;
			if(tot > 1) {
				check = true;
				break;
			}	
		}
		if(check) continue;
		for(int i = 0; i < Sigma; i++)
			update(i, 1, l, r, 0);
		if((r - l + 1) & 1)
			cnt[num]--;
		for(int i = 0; i < Sigma; i++)
			if(cnt[i]) {
				update(i, 1, curl, curl + (cnt[i] >> 1) - 1, 1);
				update(i, 1, curr - (cnt[i] >> 1) + 1, curr, 1);
				curl += (cnt[i] >> 1), curr -= (cnt[i] >> 1);
			}
		if((r - l + 1) & 1)
			update(num, 1, (l + r) >> 1, (l + r) >> 1, 1);
	}
	for(int i = 1; i <= n; i++)
		for(int j = 0; j < Sigma; j++)
			if(query(j, 1, i, i)) {
				printf("%c", j + 'a');
				break;
			}
	return 0;
}
```

---

## 作者：Code_星云 (赞：1)

开 26 棵线段树，每棵树维护一种字母。每次的区间重排可看作区间修改。我们用 0 表示没有该字母，用 1 表示存在。  

分析回文的性质。回文有两种：长度为奇数，即有一种字母出现的次数为奇数；长度为偶数，则所有字母的出现次数为偶数。统计出现次数可以用线段树维护。如果不满足条件 continue 即可，否则修改。  

由于题目要求按字典序从小到大排序，即回文左半边要从小到大排。从 $a$ 开始枚举即可。对于每个字母，若其出现了 $k$ 次，则在回文的左边将某个长度为 $\dfrac{k}{2}$ 的该字母线段树的区间赋值为 1。特殊的，若该字母出现奇数次，则把该字母线段树的区间中点位置修改为 1。需要注意的是，如果要执行修改操作，要记得先把每个字母该区间都修改为 0。
```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 100005
using namespace std;
int read(){
	int x=0,flag=1;char c;
	while((c=getchar())<'0'||c>'9') if(c=='-') flag=-1;
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*flag;
}
struct trees{
	struct segtree{
		int l,r,sum,add;
		#define l(x) tree[x].l
		#define r(x) tree[x].r
		#define sum(x) tree[x].sum
		#define add(x) tree[x].add
	}tree[4*N];
	void pushdown(int x){
		sum(x<<1)=add(x)*(r(x<<1)-l(x<<1)+1);
		sum(x<<1|1)=add(x)*(r(x<<1|1)-l(x<<1|1)+1);
		add(x<<1)=add(x<<1|1)=add(x); add(x)=-1;
	}
	void build(int x,int l,int r){
		l(x)=l; r(x)=r; int mid=(l+r)>>1;
		if(l==r){sum(x)=0;add(x)=-1;return;}
		build(x<<1,l,mid); build(x<<1|1,mid+1,r);
	}
	int query(int x,int l,int r){
		if(l<=l(x)&&r(x)<=r) return sum(x);
		if(add(x)!=-1)pushdown(x); int mid=(l(x)+r(x))>>1,res=0;
		if(l<=mid) res+=query(x<<1,l,r); if(r>mid) res+=query(x<<1|1,l,r);
		return res;
	}
	void modify(int x,int l,int r,int val){
		if(l<=l(x)&&r(x)<=r){sum(x)=val*(r(x)-l(x)+1);add(x)=val;return;}
		if(add(x)!=-1)pushdown(x); int mid=(l(x)+r(x))>>1;
		if(l<=mid) modify(x<<1,l,r,val); if(r>mid) modify(x<<1|1,l,r,val);
		sum(x)=sum(x<<1)+sum(x<<1|1);
	}
}t[30];
char s[N];
int n,m,bar[30],sum1=0,sum2=0;
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	n=read(); m=read(); scanf("%s",s+1);
	for(int i=1;i<=26;i++) t[i].build(1,1,n);
	for(int i=1;i<=n;i++){
		int tmp=s[i]-'a'+1;
		t[tmp].modify(1,i,i,1);
	}
	while(m--){
		sum1=0; sum2=0;
		int l,r; scanf("%d%d",&l,&r);
		for(int i=1;i<=26;i++){
			bar[i]=t[i].query(1,l,r);
			if(bar[i]&&bar[i]%2==0) sum2++;
			else if(bar[i]%2==1) sum1++;
		}
		if((r-l+1)%2==0&&sum1) continue;
		if((r-l+1)%2==1&&sum1!=1) continue;
		for(int i=1;i<=26;i++) t[i].modify(1,l,r,0);
		int sl=l,sr=r;
		for(int i=1;i<=26;i++){
			if(bar[i]%2==1){t[i].modify(1,(l+r)>>1,(l+r)>>1,1);bar[i]--;}
			if(!bar[i]) continue;
			t[i].modify(1,sl,sl+bar[i]/2-1,1);
			t[i].modify(1,sr-bar[i]/2+1,sr,1);
			sl+=bar[i]/2; sr-=bar[i]/2;
		}
	}
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=26;j++) if(t[j].query(1,i,i)==1) cout<<(char)('a'+j-1);
	puts(""); return 0;
}
```


---

## 作者：Jsxts_ (赞：1)

提供一种分块做法。

首先，如果区间内每种字符出现次数中奇数大于一个，显然不能构成回文串。

否则最优方法就是按 $a\sim z$ 的顺序，从外往内依次填数，这样可以保证字典序最小。如果有一种字符出现次数为奇数，就把它填在中间。

那么，我们现在要支持两个操作：区间赋值和查询区间内每种字母出现了多少次。

对于分块，可以维护一个块内每种字母出现次数，区间赋值整块就打标记，散块暴力，修改查询时再下传就好了。一定要注意细节，我因为一个小细节调了半个小时。。。

代码（最优解，跑得飞快）：

```cpp
#include <bits/stdc++.h>
using namespace std;
char s[100010];
int belong[100010];
int a[100010];
int st[400],ed[400],ct[400][26];
int n,m,block;
int tag[400];
int gs[26];
void build() {
	block = sqrt(n);
	int cnt = 0;
	for (int i = 1;i <= n;i ++ ) {
		belong[i] = (i-1) / block + 1;
		ct[belong[i]][a[i]] ++;
	}
	for (int i = 1;i <= n;i += block) {
		st[++cnt] = i,ed[cnt] = min(i+block-1,n), tag[cnt] = -1;
	}
}
void pushdown(int x) {//修改、查询时下传 
	if (tag[x] < 0) return;
	for (int i = st[x];i <= ed[x];i ++ ) {
		a[i] = tag[x];
	}
	for (int i = 0;i < 26;i ++ ) ct[x][i] = 0;
	ct[x][tag[x]] = ed[x]-st[x]+1;
	tag[x] = -1;
}
void modify(int x,int y,int k) {
	if (x > y) return; 
	int l = belong[x],r = belong[y];
	if (l == r) {
		pushdown(l);
		for (int i = x;i <= y;i ++ ) {
			ct[l][a[i]] --;
			ct[l][k] ++;
			a[i] = k;
		}
		return;
	}
	modify(x,ed[l],k), modify(st[r],y,k);
	for (int i = l+1;i < r;i ++ ) tag[i] = k;//整块打tag 
}
void _sort(int x,int y) {//统计个数 
	if (x > y) return; 
	int l = belong[x],r = belong[y];
	if (l == r) {
		pushdown(l);
		for (int i = x;i <= y;i ++ ) {
			gs[a[i]] ++;
		}
		return;
	}
	_sort(x,ed[l]), _sort(st[r],y);
	for (int i = l+1;i < r;i ++ ) {
		if (tag[i] >= 0) gs[tag[i]] += ed[i]-st[i]+1;
		else
			for (int j = 0;j < 26;j ++ ) gs[j] += ct[i][j];
	}
}
int read() {
	int s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
	while (isdigit(ch)) s = s * 10 + ch - '0', ch = getchar();
	return s*f;
}
int main() {
	freopen("input.txt","r",stdin);//别忘了文件输入输出 
	freopen("output.txt","w",stdout);
	n = read(),m = read();
	scanf("%s",s+1);
	for (int i = 1;i <= n;i ++ ) a[i] = s[i] - 'a';
	build();
	while (m -- ) {
		int l = read(),r = read();
		_sort(l,r);
		int fl = 0,id = -1;
		for (int i = 0;i < 26;i ++ ) {
			if (gs[i] % 2) id = i, fl ++;//找出现次数为奇数 
		}
		if (fl > 1) {
			memset(gs,0,sizeof gs);//注意这里也要清0 
			continue;
		}
		int t1 = l,t2 = r;
		for (int i = 0;i < 26;i ++ ) {
			modify(t1,t1+gs[i]/2-1,i), t1 += gs[i]/2;
			modify(t2-gs[i]/2+1,t2,i), t2 -= gs[i]/2;
			gs[i] = 0;//清0 
		}
		if (id >= 0) modify(t1,t1,id);//填中间的数 
	}
	for (int i = 1;i <= block;i ++ ) pushdown(i);//最后还要全部pushdown一次！ 
	for (int i = 1;i <= n;i ++ ) putchar(a[i] + 'a');
	return 0;
}
```


---

## 作者：5k_sync_closer (赞：0)

基本就是 CF558E。

注意到字符集很小，考虑维护出区间每个字母出现次数，然后直接重排。

显然，若出现奇数次的字母 $>1$ 个，则无法操作。

按字典序依次重排，如果剩下一个出现奇数次的字母就放在中间。

区间覆盖区间查询，线段树维护。

```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#define G int m = s + t >> 1
#define C(x) memset(x, 0, sizeof x)
#define F for(int i = 0;i < 26;++i)
inline int R()
{
    int r = 0;char c = getchar();while(!isdigit(c)) c = getchar();
    while(isdigit(c)) r = r * 10 + c - '0', c = getchar();return r;
}
inline char I() {char c = getchar();while(!islower(c)) c = getchar();return c;}
struct T
{
    T *l, *r;int s, t, x, v[26];T(int p, int q) : l(0), r(0), s(p), t(q), x(-1)
    {C(v);}void u() {F v[i] = l->v[i] + r->v[i];}void d() {if(~x) {G;C(l->v);
    l->v[x] = m - s + 1;C(r->v);r->v[x] = t - m;l->x = x;r->x = x;x = -1;}}
}*r;
void B(int s, int t, T *&p)
{
    p = new T(s, t);if(s == t) {p->v[I() - 'a'] = 1;
    return;}G;B(s, m, p->l);B(m + 1, t, p->r);p->u();
}
void M(int l, int r, int x, int s, int t, T *p)
{
    if(l <= r) {if(l <= s && t <= r) {C(p->v);p->v[x] = t - s + 1;p->x = x;return;}p->
    d();G;if(l <= m) M(l, r, x, s, m, p->l);if(r > m) M(l, r, x, m + 1, t, p->r);p->u();}
}
int Q(int l, int r, int x, int s, int t, T *p)
{
    if(l <= r) {if(l <= s && t <= r) return p->v[x];p->d();G;int q = 0;if(l <= m)
    q += Q(l, r, x, s, m, p->l);if(r > m) q += Q(l, r, x, m + 1, t, p->r);return q;}
}
void P(int s, int t, T *p) {if(s == t) {F if(p->v[i]) {putchar
(i + 'a');return;}}p->d();G;P(s, m, p->l);P(m + 1, t, p->r);}
int n, m, x, y, k, q[26];
int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
    n = R();m = R();B(1, n, r);while(m--)
    {
        x = R();y = R();C(q);k = 0;
		F k += (q[i] = Q(x, y, i, 1, n, r)) & 1;
		if(k > 1) continue;
		F
		{
			M(x, x + (q[i] >> 1) - 1, i, 1, n, r);
			M(y - (q[i] >> 1) + 1, y, i, 1, n, r);
			x += q[i] >> 1;y -= q[i] >> 1;q[i] &= 1;
		}
		F if(q[i]) M(x, y, i, 1, n, r);
    }
    return P(1, n, r), 0;
}
```


---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF240F)
## 思路
套路题，首先我们需要开 $26$ 颗线段树来维护每一种字母出现的次数。

不妨设我们当前 $\verb!update!$ 的区间是区间 ${l,r}$，那么，如果 $r-l+1$ 是个奇数，显然我们需要一个数出现奇数次，若是个偶数，显然任意一个数都不能出现奇数次，这样枚举 $26$ 个字母，暴力统计，就可以判断出修改是否是合法的。

接下来考虑如何修改，从小到大枚举字母，设一个字母出现的次数是 $k$ 次。如果它是个奇数，由于前面已经判过了，所以一定合法，所以可以把 $1$ 个字母放在最中间，剩下的 $\frac{k}{2}$ 个字母放在两边。是个偶数则直接放在两边即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int const N=1e5+10;int k[27];
struct Segment_Tree{
    #define ls (x<<1)
    #define rs (x<<1|1)
    #define mid ((l+r)>>1)
    int c[N<<2],lazy[N<<2];
    inline void pushdown(int x,int l,int r){
        if (!lazy[x]) return;
        c[ls]=(lazy[x]-1)*(mid-l+1);
        c[rs]=(lazy[x]-1)*(r-(mid+1)+1);
        lazy[ls]=lazy[x];
        lazy[rs]=lazy[x];
        c[x]=c[ls]+c[rs];
        lazy[x]=0;
    }
    inline void update(int x,int l,int r,int ll,int rr,int v){
        if (ll<=l && r<=rr){c[x]=v*(r-l+1);lazy[x]=v+1;return;}
        pushdown(x,l,r);
        if (ll<=mid) update(ls,l,mid,ll,rr,v);
        if (mid<rr) update(rs,mid+1,r,ll,rr,v);
        c[x]=c[ls]+c[rs];
    }
    inline int query(int x,int l,int r,int ll,int rr){
        if (ll<=l && r<=rr) return c[x];
        int res=0;
        pushdown(x,l,r);
        if (ll<=mid) res+=query(ls,l,mid,ll,rr);
        if (mid<rr) res+=query(rs,mid+1,r,ll,rr);
        c[x]=c[ls]+c[rs];
        return res;
    }
}T[27];//常规操作
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,m;cin>>n>>m;
    string s;cin>>s;s=" "+s;
    for (int i=1;i<=n;++i) T[s[i]-'a'].update(1,1,n,i,i,1);
    while (m--){
        int l,r,flag=0;cin>>l>>r;
        for (int i=0;i<26;++i){
            k[i]=T[i].query(1,1,n,l,r);
            if (k[i]&1) ++flag;
        }
        if (flag>1 || (!((r-l+1)&1) && flag)) continue;
        for (int i=0;i<26;++i) T[i].update(1,1,n,l,r,0);
        int la=l;
        for (int i=0;i<26;++i){
            if (!k[i]) continue;
            if (k[i]&1){
                T[i].update(1,1,n,(l+r)/2,(l+r)/2,1);
            }
            if (k[i]>1){
                T[i].update(1,1,n,la,la+(k[i]/2)-1,1),
                T[i].update(1,1,n,r-(la-l)-(k[i]/2)+1,r-(la-l),1),
                la+=(k[i]/2);            
            }
        }
    }
    for (int i=1;i<=n;++i){
        int tag=0;
        for (int j=0;j<26;++j) if (T[j].query(1,1,n,i,i)){tag=j;break;}
        cout<<char('a'+tag);
    }
    cout<<'\n';
    return 0;
} 

```


---

## 作者：_lxy_ (赞：0)

[博客食用效果更佳](https://www.cnblogs.com/lxy-2022/p/CF2600-zuo-ti-ji-lu.html)

#### 题意

一个长度为 $n$ 的小写字母串，$m$ 次操作，每次将子串 $[l,r]$ 重排使其成为字典序最小的回文串（若无法重排成回文串则跳过）。求最后的字符串。

#### 分析

开 $26$ 棵线段树维护每种字母在区间中出现次数。首先可以发现一次操作可以完成当且仅当该区间内每种字母出现次数最多有一个是奇数。重排成字典序最小的回文串就可以从小到大放每种字母，前面接着放一半，后面接着放一半，如果有的字母有奇数个就把一个放中间剩下的和偶数个的字母一起放。

发现修改其实就是将一段连续的位置放上某同种字母，查询也只需查询连续区间的字母数，因此可以用线段树求区间和，并支持区间赋值，然后按上面的策略模拟即可。

#### 核心代码

```cpp
scanf("%d%d%s",&n,&m,s+1);int i,j;for(i=1;i<=26;i++) st[i].build(1,1,n);
for(i=1;i<=n;i++) st[s[i]-'a'+1].upd(1,1,n,i,i,1);
while(m--){
    int l,r;scanf("%d%d",&l,&r);int c=0,cnt=0,p;
    for(i=1;i<=26;i++){
        int tmp=st[i].que(1,1,n,l,r);
        c+=(tmp&1);cnt+=tmp;if(tmp&1) p=i;
    }if(c>1) continue;int nl=l,nr=r;
    for(i=1;i<=26;i++){
        int tmp=st[i].que(1,1,n,l,r);if(!tmp) continue;
        st[i].upd(1,1,n,l,r,0);
        if(tmp&1) st[i].upd(1,1,n,(l+r)>>1,(l+r)>>1,1),tmp--;
        st[i].upd(1,1,n,nl,nl+(tmp>>1)-1,1);nl+=(tmp>>1);
        st[i].upd(1,1,n,nr-(tmp>>1)+1,nr,1);nr-=(tmp>>1);
    }
}for(i=1;i<=n;i++){
    for(j=1;j<=26;j++){
        if(st[j].que(1,1,n,i,i)>0){
            ans[i]=j+'a'-1;break;
        }
    }
}printf("%s\n",ans+1);
```

[record](https://codeforc.es/problemset/submission/240/171678284)



---

## 作者：Arghariza (赞：0)

$\large\color{white}\text{分块天下第一！！！11}$

数据范围 $10^5$ ，显然可以使用分块。

显然构成回文串的字符串必须要满足**每种字符都要出现偶数次或者只有一种字符出现奇数次**。

如果能构成回文串，最优方案就是**从外到内以 $a\to z$** 的顺序插入，如果有出现次数为奇数的字符，那么把它填在中间。

所以实际上我们只要维护两个操作：

- 区间赋值
- 查询区间内每种字母出现次数

于是使用分块，开一个桶维护一个块内字母出现次数，区间赋值就把 $\mathtt{tag}$ 打上去，边角暴力修改。

查询的时候把 $\mathtt{tag}$ 给 $\mathtt{pushdown}$ 下传即可。

常数较小，比线段树不知道小到那里去了。

```cpp
#include <bits/stdc++.h>
namespace mystd {
    inline int read() {
        int w = 1, q = 0;
        char ch = ' ';
        while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
        if (ch == '-') w = -1, ch = getchar();
        while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
        return w * q;
    }
    inline void write(int ls) {
        if (ls < 0) {
            ls = ~(ls - 1);
            putchar('-');
        }
        if (ls > 9) write(ls / 10);
        putchar(ls % 10 + '0');
    }
}
using namespace std;
using namespace mystd;

const int maxb = 440;
const int maxn = 1e5 + 100;

char ch[maxn];
int l[maxb], r[maxb], pos[maxn], tag[maxb], c[maxb][26];
int n, m, b, s[maxn], g[26];

void pushdown(int ls) {// 下传标记
    if (tag[ls] < 0) return;
    for (int i = l[ls]; i <= r[ls]; i++) s[i] = tag[ls];
    for (int i = 0; i < 26; i++) c[ls][i] = 0;
    c[ls][tag[ls]] = r[ls] - l[ls] + 1, tag[ls] = -1;
}

void update(int ls, int rs, int k) {// 更新
    if (ls > rs) return;
    int p = pos[ls], q = pos[rs];
    if (p == q) {
        pushdown(p);
        for (int i = ls; i <= rs; i++) c[p][s[i]]--, c[p][k]++, s[i] = k;
    } else {
        pushdown(p);
        pushdown(q);
        for (int i = ls; i <= r[p]; i++) c[p][s[i]]--, c[p][k]++, s[i] = k;
        for (int i = l[q]; i <= rs; i++) c[q][s[i]]--, c[q][k]++, s[i] = k;
        for (int i = p + 1; i <= q - 1; i++) tag[i] = k; 
    }
}

void work(int ls, int rs) { 
    if (ls > rs) return;
    int p = pos[ls], q = pos[rs];
    if (p == q) {
        pushdown(p);
        for (int i = ls; i <= rs; i++) g[s[i]]++;
    } else {
        pushdown(p);
        pushdown(q);
        for (int i = ls; i <= r[p]; i++) g[s[i]]++;
        for (int i = l[q]; i <= rs; i++) g[s[i]]++;
        for (int i = p + 1; i < q; i++) {
            if (tag[i] >= 0) g[tag[i]] += r[i] - l[i] + 1;
            else for (int j = 0; j < 26; j++) g[j] += c[i][j];
        }
    }
    
}

int main() {
    freopen("input.txt", "r", stdin); 
    freopen("output.txt", "w", stdout);
    n = read();
    m = read();
    scanf("%s", ch + 1);
    for (int i = 1; i <= n; i++) s[i] = ch[i] - 'a';
    b = sqrt(n);
    int cnt = 0;
    for (int i = 1; i <= n; i++) pos[i] = (i - 1) / b + 1, c[pos[i]][s[i]]++;
    for (int i = 1; i <= n; i += b) l[++cnt] = i, r[cnt] = min(i + b - 1, n), tag[cnt] = -1;
    for (int i = 1, p, q, fl = 0, id = -1; i <= m; i++, fl = 0, id = -1) {
        p = read();
        q = read();
        work(p, q);
        for (int i = 0; i < 26; i++) if (g[i] & 1) id = i, fl++;
        if (fl > 1) {
            memset(g, 0, sizeof(g));
            continue;
        }
        int t1 = p, t2 = q;
        for (int i = 0; i < 26; i++) {
            update(t1, t1 + g[i] / 2 - 1, i), t1 += g[i] / 2;
            update(t2 - g[i] / 2 + 1, t2, i), t2 -= g[i] / 2;
            g[i] = 0;
        }
        if (id >= 0) update(t1, t1, id);
    }
    for (int i = 1; i <= b; i++) pushdown(i);
    for (int i = 1; i <= n; i++) putchar(s[i] + 'a');
    return 0;
}
```

---

