# Polycarp's Masterpiece

## 题目描述

Inspired by success of Joanne Rowling and her fantasy series of Harry Potter, Polycarp decided to create his own masterpiece. He has already picked a name for his future bestseller — string $ s $ .

Polycarp faced a number of difficulties while he was working on the main story of his book so he decided to become Malevich in a literature and create his own "Black Square".

Chapters of his masterpiece were written by Polycarp in $ n $ days. He started from writing down the string $ s $ . Every day (during the following $ n $ days) he did the following procedure: on the $ i $ -th day he added to the right of current text $ t $ its $ k_{i} $ -th circular shift. It means that every day content of his masterpiece doubled in size.

Circular shift of a string $ r $ is defined as a string resulted after movement of the last character of $ r $ to the first position in the string. As an example: circular shift of «masterpiece» is «emasterpiec». The $ i $ -th circular shift of a string $ r $ is defined as a string resulted after applying $ i $ subsequent circular shifts of the string $ r $ (e.g., the third circular shift of «masterpiece» is «ecemasterpi»).

After $ n $ days of tedious work Polycarp managed to write a very long text deserving the efforts made. However, text of his masterpiece was so long that it was nearly impossible to do any analysis of its content.

Help Polycarp to answer $ m $ requests about his masterpiece: for the $ j $ -th request you will need to find how many times a letter $ c_{j} $ is contained in a substring of his masterpiece starting from position $ l_{j} $ and ending at $ r_{j} $ inclusively.

## 样例 #1

### 输入

```
masterpiece
1 3
3
1 22 m
9 14 e
8 15 p
```

### 输出

```
2
4
0
```

## 样例 #2

### 输入

```
polycarp
1 2
0
2 15 p
1 16 p
```

### 输出

```
2
4
```

# 题解

## 作者：cyffff (赞：4)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF589C)
## 题意
给你一个字符串 $s$，有 $n$ 次操作，每次操作将当前字符串 $s$ 复制，并将后 $k_i$ 个字符放到字符串最前面，接到当前字符串之后，接下来 $m$ 次查询，每次查询问最终字符串 $[l,r]$ 区间中有多少个字符 $c$。

$|s|,k_i\le100,1\le n,m\le 10^5,1\le l\le r\le 10^{18}$
## 思路
校内模拟赛 $\text C$ 题，赛时做出来了！

不知道为什么这场 $\text{CF}$ 好像被删了，交上去会 $\text{UKE}$。

这应该是到目前为止这道题的第三种做法，另外两种做法可以参考 @[ezoiHQM](https://www.luogu.com.cn/user/49097) 的可持久化 $\text{FHQ}$ 和 @[dqstz](https://www.luogu.com.cn/user/203623) 的可持久化线段树。

这里我提供一种比较好想、好写，但是依赖于 $k$ 的范围的做法。

我们知道，经过 $i$ 次操作，$s$ 的长度就会变为 $l\times 2^i$（$l$ 为 $s$ 的初始长度），进行 $10^5$ 次操作是完全没有意义的，因为查询只到 $10^{18}$，所以进行 $60$ 次操作就完全够了（$2^{60}>10^{18}$）。

首先思考如何求出位置 $p$ 的字符。考虑一次操作之后的字符串长这样：

![getchar](https://cdn.luogu.com.cn/upload/image_hosting/c8ljvyms.png?x-oss-process=image)

考虑设计函数 $\text{getch}(p,d)$ 表示求第 $p$ 位置的字符，当前正处理第 $d$ 次操作。

- 若 $d=0$，则直接返回 $s_p$；
- 若 $d\ne0$，
	- 若 $p$ 落在区间 $[A,B]$ 之间，则调用 $\text{getch}(p,d-1)$ 进行递归处理。
   - 若 $p$ 落在区间 $B'$ 中，找到其在 $B$ 中对应的位置，递归即可。考虑 $B'$ 的结束位置为 $y=l\times2^{d-1}+k_d$，则调用函数 $\text{getch}(l\times2^{d-1}-y+p,d-1)$；
   - 若 $p$ 落在区间 $A'$ 中，找到其在 $A$ 中对应的位置，递归即可。考虑 $B'$ 的结束位置为 $y=l\times2^{d-1}+k_d$，则调用函数 $\text{getch}(p-y,d-1)$。

每次递归都会将 $d$ 减 $1$，由于 $d=O(\log p)$，所以一次 $\text{getch}(p,d)$ 的调用消费为 $O(\log p)$。

考虑将每次询问差分成 $r$ 的前缀和减去 $l-1$ 的前缀和，对于一次前缀和询问，记其为 $\text{ask}(r,d,x)$ 表示询问 $[1,r]$ 区间中 $x$ 的出现次数，当前正在处理第 $d$ 次操作。还是那张图：

![ask](https://cdn.luogu.com.cn/upload/image_hosting/c8ljvyms.png?x-oss-process=image)

- 若 $d=0$，考虑预处理出原字符串中每个字符出现次数的前缀和，则可以 $O(1)$ 查询；
- 若 $d\ne0$，
	- 若 $r$ 落在区间 $[A,B]$ 之间，则返回 $\text{ask}(r,d-1,x)$；
   - 若 $r$ 落在区间 $B'$ 中，贡献分为 $[A,B]$、$[B'_l,r]$ 两部分，其中第一部分贡献可以通过预处理 $s$ 中每个字母的出现次数 $O(1)$ 计算，对于第二部分，由于 $k$ 很小，可以通过预处理每次的 $B$ 部分的字母出现次数的前缀和 $O(1)$ 计算，直接返回；
   - 若 $r$ 落在区间 $A'$ 中，贡献分为 $[A,B]$、$B'$ 和 $[A'_l,r]$ 三部分，前两部分直接按照上一种情况处理，对于第三部分，找到其在 $A$ 中对应的位置，递归询问即可。考虑 $B'$ 的结束位置为 $y=l\times2^{d-1}+k_d$，则返回前两部分的答案和加上 $\text{ask}(r-y,d-1,x)$。

同样，由于 $d=O(\log r)$，调用一次 $\text{ask}(r,d,x)$ 的调用消费为 $O(\log r)$。

总时间复杂度为 $O(\sum k\log r(\log r+|\sum|)+m\log r)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int N=1e5+10;
char str[110];
int l,n,m;
int pr[26][110],k[N],pre[26][70][110];
/*
pre[i][j][k]=第 j 天后 k_j 个字符中前 k 个字符中有多少个 i 
由于询问区间知道 10^18，则只需开 26x\log2(10^18)x100 的数组即可
对于 1 天，将其分为三段：左半段，循环段，平移段，分类讨论 r 落在哪段 
O(m\log r)
*/
vector<ll>s,t;
inline int getch(ll p,int d){
	if(d==0)
		return str[p]-'a';
	if(p<s[d])
		return getch(p,d-1);
	ll yiw=s[d]+k[d]-1;
	if(p<=yiw)
		return getch(t[d-1]-yiw+p,d-1);
	return getch(p-yiw,d-1); 
}
inline ll ask(ll r,int d,int x){
	if(d==0)
		return pr[x][r];
	if(s[d]>r)
		return ask(r,d-1,x);
	ll yiw=s[d]+k[d]-1;
	ll ad=(1ll<<d-1)*pr[x][l];
	if(r<=yiw)
		return pre[x][d][r-t[d-1]]+ad;
	return ask(r-yiw,d-1,x)+pre[x][d][k[d]]+ad;
}
inline ll ask(ll r,int x){
	if(r==0)
		return 0;
	int i;
	for(i=0;t[i]<r;i++);
	return ask(r,i,x);
}
int main(){
//	freopen("data_C1.in","r",stdin);
//	freopen("data_C1.out","w",stdout);
	l=readstr(str);
	n=read(),m=read();
	for(int i=1;i<=l;i++)
		for(int j=0;j<26;j++)
			pr[j][i]=pr[j][i-1]+(str[i]==(j+'a'));
	s.push_back(1),t.push_back(l);
	for(int i=1;i<=n;i++)
		k[i]=read();
	for(int i=1;t.back()<1e18&&i<=60;i++){
		ll x=t.back();
		s.push_back(x+1),t.push_back(x*2);
	}
	for(int i=1;i<=60&&i<t.size();i++){
		k[i]%=t[i-1];
		for(int j=1;j<=k[i];j++){
			int ch=getch(t[i-1]-k[i]+j,i-1); 
			for(int c=0;c<26;c++)
				pre[c][i][j]=pre[c][i][j-1]+(c==ch);
		}
	}
	while(m--){
		ll l=read(),r=read(),x=getc()-'a';
		write(ask(r,x)-ask(l-1,x)),putc('\n');
	}
	flush();
}
```
再见 qwq~

---

## 作者：critnos (赞：1)

magic！科学的可持久化！


可持久化平衡树，他好吗？他不好！

考虑魔改可持久化线段树！

我们先对原序列建一棵线段树，支持求区间某字符出现次数。

然后我们要支持 $\log v$ 次 copy 操作，$v=10^{18}$。之所以是 $\log v$ 是因为 $\log v$ 次操作后的元素位置 $\ge v$，不在 $[l,r]$ 内。

每次 copy 是把后 $k$ 个元素放到序列最后，再把前面的元素放到序列最后。

众所周知线段树会把一个区间分成 $\log n$ 个子段，而可持久化的意义在于共用重复信息。

所以，我们把要 copy 的区间分成子段，排成一个序列，然后在他们上面建树！

设序列长为 $5$，$k=1$，友情供图：

![](https://cdn.luogu.com.cn/upload/image_hosting/5qtfj0i3.png)

相信你看了图之后就会了！

一些实现细节：

线段树比较臃肿，换成非 leafy tree（相当于把线段树换成一棵完美的平衡树）会快些。

这个线段树不方便维护区间左右端点（你写了自然知道），所以不妨维护每个节点的 $size$，即区间长度。因此一个询问 $[l,r]$ 要拆成 $[1,r]-[1,l-1]$。

另外，维护 $size$ 后功能变弱，对于 copy 的元素，前/后的要分别考虑。因此，遗憾的，我们无法支持 copy 任意区间的操作。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
char s[105];
int cnt,ncnt;
struct seg
{
	ll size;
	int s[2];
	ll cnt[26];
}t[1000005];
#define ls t[w].s[0]
#define rs t[w].s[1]
int nd[100005];
int build(int l,int r)
{
	int w=++cnt,i,mid=l+r>>1;
	t[w].size=r-l+1;
	for(i=l;i<=r;i++)
		t[w].cnt[s[i]-'a']++;
	if(l<r)
		ls=build(l,mid),
		rs=build(mid+1,r);
	return w;
}
void pushup(int w)
{
	for(int i=0;i<26;i++)
		t[w].cnt[i]=t[ls].cnt[i]+t[rs].cnt[i];
	t[w].size=t[ls].size+t[rs].size;
}
void getp(int w,ll x)
{
	if(t[w].size==1)
	{
		if(x) nd[++ncnt]=w;
	}
	else if(x>t[ls].size)
		nd[++ncnt]=ls,getp(rs,x-t[ls].size);
	else
		getp(ls,x);
}
void getn(int w,ll x)
{
	if(t[w].size==1)
	{
		if(x) nd[++ncnt]=w;
	}
	else if(x>t[rs].size)
		getn(ls,x-t[rs].size),nd[++ncnt]=rs;
	else
		getn(rs,x);
}
int build2(int l,int r)
{
	if(l==r) return nd[l];
	int w=++cnt,mid=l+r>>1;
	ls=build2(l,mid),
	rs=build2(mid+1,r);
	pushup(w);
	return w;
}
ll ask(int w,ll x,int c)
{
	if(t[w].size==1)
		return x*t[w].cnt[c];
	if(x>t[ls].size)
		return ask(rs,x-t[ls].size,c)+t[ls].cnt[c];
	return ask(ls,x,c);
}
int main()
{
	int n,m,rt,k,ne;
	ll len,l,r;
	char c[3];
	scanf("%s%d%d",s+1,&n,&m);
	rt=build(1,len=strlen(s+1));
	while(n--)
	{
		scanf("%d",&k);
		if(len>1e18) continue;
		k%=len;
		ncnt=0;
		getn(rt,k),getp(rt,len-k);	
		ne=++cnt;
		t[ne].s[0]=rt,
		t[ne].s[1]=build2(1,ncnt);
		pushup(rt=ne);
		len*=2;
	}
	while(m--)
	{
		scanf("%lld%lld%s",&l,&r,c);
		printf("%lld\n",ask(rt,r,*c-'a')-ask(rt,l-1,*c-'a'));
	}
}
```


---

## 作者：ezoiHQM (赞：1)

貌似有分治+DP的做法，但是我太弱了，只会写写可持久化平衡树的模板。	
这道题如果想到了这种做法，其实就是几个可持久化平衡树的基本操作。	
我们设$len$为当前字符串的长度，我们会发现，我们进行$k$次循环移位，其实就是将原串从右往左$k\space mod\space len$个位置分裂，然后合并到最左边，再与原串合并。	
于是就是很明显的可持久化平衡树了。	
查询的话，每个节点存储一下当前子树内所表达的串所含的每个字符的数量，然后就不难了，具体看看代码吧。	
时间复杂度的话，首先我们会发现我们最多只需要进行60次操作，这个串的长度就会乘2，所以最多只需要$log\space r$次操作就可以完成，更新节点信息需要更新26个字符的数量。每次询问的复杂度是$log\space r$，所以总时间复杂度是$O(26log^2r+qlog\space r)$，顺利通过本题。	
如果有误请在评论区说一声哦！	
代码：
```cpp
#include<cstdio>
#include<cctype>
#include<cstring>
#include<cstdlib>
typedef long long ll;
int n,m,len,cnt,ban,rt[70],ch[200010][2],val[200010];
ll siz[200010][27],k[200010];
char s[100010];
const ll maxn=1e18;
void maintain(int o){
	for(int i=0;i<=26;i++)
		siz[o][i]=siz[ch[o][0]][i]+siz[ch[o][1]][i]+(val[o]==i||i==26);
	return;
}
void build(int &o,int l,int r){
	if(l>r)
		return;
	o=++cnt;
	int mid=(l+r)>>1;
	val[o]=s[mid]-'a';
	build(ch[o][0],l,mid-1);
	build(ch[o][1],mid+1,r);
	maintain(o);
	return;
}
int cpy(int o){
	val[++cnt]=val[o];
	memcpy(siz[cnt],siz[o],sizeof(siz[o]));
	ch[cnt][0]=ch[o][0];
	ch[cnt][1]=ch[o][1];
	return cnt;
}
void split(int o,ll k,int &a,int &b){
	if(!o){
		a=b=0;
		return;
	}
	if(!k){
		a=o,b=0;
		return;
	}
	if(k==siz[o][26]){
		a=0,b=o;
		return;
	}
	int p=cpy(o);
	if(k<=siz[ch[o][1]][26]){
		a=p;
		split(ch[p][1],k,ch[a][1],b);
	}
	else{
		b=p;
		split(ch[p][0],k-siz[ch[o][1]][26]-1,a,ch[b][0]);
	}
	maintain(p);
	return;
}
int merge(int a,int b){
	if(!a||!b)
		return a|b;
	int p;
	if((((ll)rand()<<45ll)|((ll)rand()<<30ll)|((ll)rand()<<15ll)|(ll)rand())%(siz[a][26]+siz[b][26])<=siz[a][26]){
		p=cpy(a);
		ch[p][1]=merge(ch[p][1],b);
	}
	else{
		p=cpy(b);
		ch[p][0]=merge(a,ch[p][0]);
	}
	maintain(p);
	return p;
}
ll query(int o,ll k,int c){
	if(!o||!k)
		return 0;
	if(k==siz[o][26])
		return siz[o][c];
	if(k<=siz[ch[o][0]][26])
		return query(ch[o][0],k,c);
	return query(ch[o][1],k-siz[ch[o][0]][26]-1,c)+siz[ch[o][0]][c]+(val[o]==c);
}
ll rd(){
	ll x=0;
	char c;
	do c=getchar();
	while(!isdigit(c));
	do{
		x=(x<<1ll)+(x<<3ll)+(c^48);
		c=getchar();
	}while(isdigit(c));
	return x;
}
int main(){
	scanf("%s",s+1);
	len=strlen(s+1);
	n=rd(),m=rd();
	for(int i=1;i<=n;i++)
		k[i]=rd();
	build(rt[0],1,len);
	for(ban=1;ban<=n&&siz[rt[ban-1]][26]<maxn;ban++){
		k[ban]%=siz[rt[ban-1]][26];
		int a,b;
		split(rt[ban-1],k[ban],a,b);
		rt[ban]=merge(rt[ban-1],merge(b,a));
	}
	ban--;
	while(m--){
		ll l=rd(),r=rd();
		char c;
		do c=getchar();
		while(!islower(c));
		printf("%I64d\n",query(rt[ban],r,c-'a')-query(rt[ban],l-1,c-'a'));
	}
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

## 思路

题意：输入一个字符串 $s$，有 $n$ 次操作，每次操作将当前字符串 $s$ 复制一份为 $s'$，并将 $s'$ 的后 $k_i$ 个字符放到字符串 $s'$ 最前面，将 $s$ 变成 $s+s'$（$+$ 表示连接字符串操作）。接下来 $m$ 次查询，每次查询询问最终的字符串的 $[l,r]$ 区间单位内有多少个字符 $c$。

---

我们考虑将这道题分成两个部分——修改和查询。首先确定算法，那么肯定是根据查询来定的。

看看查询，是查询询问最终的字符串的 $[l,r]$ 区间单位内有多少个字符 $c$，那么很显然我们可以使用线段树或者平衡树来首先。这里我们选择用平衡树来实现，实际上线段树也大同小异了。细节上就是在平衡树的每一个节点维护当前节点代表的序列区间含有的每个字母的分别的个数。注意每一个节点可能会维护多个区间（具体看下面的**修改**部分），只不过这个平衡树也不需要维护区间的端点。

假设我们维护好了这颗平衡树，那么查询就很简单了，这里不再赘述。

下面我们考虑如何应对**修改**。那么我们很显然可以发现是将当前平衡树 $s$ 复制一份为 $s'$，然后找到需要分裂的那个位置 $k_i$（这里的 $k_i$ 并不是平衡树上的位置，而是序列上的位置。考虑平衡树的性质，找到这个位置的时间复杂度不超过 $O(\log_2 r_{\text{max}})$，因为超过 $r_{\text{max}}$ 的我们根本用不到），分裂平衡树为 $a,b$，然后按顺序合并平衡树 $s,b,a$。

但是我们发现，如果仅仅是这样，我们明显会爆空间。那么怎么办呢？我们发现我们所需要合并的 $a,b$ 在 $s$ 中都存在，那么实际上我们只需要在 $s$ 中找到 $a,b$ 并指向 $s$ 树根即可。这一点很像可持久化线段树，只不过不需要额外加点了。

---

代码和前面大佬大同小异，不放了，没有额外的意义。



---

