# [USACO15FEB] Censoring S

## 题目描述

Farmer John 为他的奶牛订阅了《Good Hooveskeeping》杂志，但最新一期包含了一篇不恰当的牛排烹饪文章。为此，FJ 需要将杂志文字组成的字符串 $S$（长度不超过 $10^6$）中所有出现的子串 $T$ 进行删除处理。

删除规则如下：反复找到当前 $S$ 中第一个出现的子串 $T$ 并删除，直到 $S$ 中不再包含 $T$。注意，删除操作可能产生新的 $T$ 子串。

请输出最终处理完成的字符串 $S$。

## 样例 #1

### 输入

```
whatthemomooofun
moo```

### 输出

```
whatthefun```

# 题解

## 作者：hovny (赞：74)


$\mathtt{Update\ 2019.11.08}$

## [题面](https://www.luogu.org/problemnew/show/P4824)

在字符串 $A$ 中，如果字符串 $B$ 是 $A$ 的子串，那么就删除在 $A$ 中第一个出现的 $B$，然后拼接在一起，一直重复上述步骤直到 $B$ 不再是 $A$ 的子串

|A|$\le 10^6$

## 解题思路

**KMP+栈**

### 分析

1、字符串匹配的问题，想到 $KMP$

2、在匹配过程中，如果匹配成功了，就将子串 $B$ 删除，可以证明，对之前不会产生影响

3、删了再加入，类似栈的操作，因此用栈维护上述操作过程中的字串即可

### 过程

1、$KMP$ 板子跑一遍

2、在 $KMP$ 过程中，把遍历到的 $i$（不是字符，而是下标）入栈，当匹配上 $B$ 时，就把匹配的部分出栈，然后 $j$ 从栈顶的 $i$ 所能**匹配到的最大的位置**开始（就是 `f[i]` 记录的值），继续做 $KMP$

时间复杂度：$B$ 自身匹配一次 $+A$ 与 $B$ 匹配一次$+A$ 中最多每个字符进出栈一次，为 $O(|A|)$

## Code

```cpp
#include<bits/stdc++.h>
#define N 1000010
using namespace std;
int la,lb,res;
char a[N],b[N];
int p[N],f[N];//分别表示B串自身匹配的结果、A串与B串匹配的结果
int St[N],top;
int main()
{
	int i,j;
	scanf("%s",a+1);
	scanf("%s",b+1);
	la=strlen(a+1);
	lb=strlen(b+1);
	for(i=2,j=0;i<=lb;i++) {//自身匹配
		while(j&&b[i]!=b[j+1])
			j=p[j];
		if(b[i]==b[j+1])
			j++;
		p[i]=j;
	}
	for(i=1,j=0;i<=la;i++) {//A与B匹配
		while(j&&a[i]!=b[j+1])
			j=p[j];
		if(a[i]==b[j+1])
			j++;
		f[i]=j;//记录结果
		St[++top]=i;//入栈
		if(j==lb)//如果匹配成功，弹出，并更新j值
			top-=lb,j=f[St[top]];
	}
	for(i=1;i<=top;i++)//大功率输出
		printf("%c",a[St[i]]);
	return 0;
}
```

再扔道题 [Luogu P3121 [USACO15FEB]审查（黄金）Censoring (Gold)](https://www.luogu.org/problemnew/show/P3121)

---

## 作者：AlanSP (赞：26)

## KMP的删除操作

#### **Description：**

> 在字符串$S$中，重复删除同一个字串$T$。直到$T$不再是$S$的字串为止
>
>  $|S|\le10^6$

---

第一眼可能没什么思路，但我想到了开栈。

最初的想法是开一个栈，把$S$中的每个字符依次扔进去。

再同时跑kmp，如果匹配上，就弹出长度为$|T|$的元素。

栈中剩下的就是要保留的元素。

但这个做法没过样例~~还是很良心的qwq~~。



很显然，这样没法处理删除后产生的新串。

所以我们开一个辅助数组**pos**，**pos[i]表示S的第i位匹配到的T的长度。**

举个例子：whatthemomooofun中第9位pos[9]=2，匹配了mo。

这样我们每次在成功匹配退栈后可以让j跳向栈顶的pos，表示从栈顶继续匹配。

这样就解决了连续的问题????*★,°*:.☆(￣▽￣)/$:*.°★* 。

---

#### **Code：**

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e6+9;
char s1[N],s2[N];
int stk[N],top,nxt[N],pos[N];
int main()
{
	scanf("%s%s",s1+1,s2+1);
	int len1=strlen(s1+1),len2=strlen(s2+1);
	nxt[0]=-1,nxt[1]=0;
	int j;
	for(int i=2;i<=len2;i++)
	{
		j=nxt[i-1];
		while(~j&&s2[j+1]!=s2[i]) j=nxt[j];
		nxt[i]=j+1;
	}
	j=0;
	for(int i=1;i<=len1;i++)
	{
		stk[++top]=i;
		while(~j&&s2[j+1]!=s1[i]) j=nxt[j];
		j++;
		pos[i]=j;
		if(j==len2)
		{
			int t=len2;
			top-=t;
			j=pos[stk[top]];
			// printf("%d\n",j);
		}
	}
	for(int i=1;i<=top;i++) printf("%c",s1[stk[i]]);
	return 0;
}
```



---

## 作者：ywy_c_asm (赞：22)

~~**线段树大法好。**~~

~~突然发现我好像除了线段树爆搞就啥都不会了qaq~~

首先我们发现如果删完一个子串，可能剩下的两段会拼接成一段会在拼接的这个地方又出现一个等于$T$的子串，这是这个题比较麻烦的地方。那么我们就直接按照题意从“合并”的角度入手。

于是我就想到了线段树维护$Hash$，这个可以通过$O(logn)$的区间查询来进行匹配，具体来说就是这样的，我们知道字符串$Hash$一般有两种写法：

1.$hsh_i=hsh_{i-1}+str_i*k^i$

2.$hsh_i=hsh_{i-1}*k+str_i$

第一种是支持前缀和的$Hash$，第二种比较无脑，但是我们可以在线段树上用这种方式进行区间内$Hash$的合并：

$hsh_{[l,r]}=hsh_{[l,mid]}*k^{r-mid}+hsh_{mid+1,r}$

好那么问题来了，如何动态删除一段区间的字符串呢？

这个直观看上去可能需要把线段树换成个$Splay$维护，不过我们发现上面的式子中左区间的$Hash$乘的$k^{r-mid}$是因为右区间的长度是$r-mid$，那么我们维护一下区间内的实际长度$len$（换句话说就是这段区间内剩下了多少个字符，相当于跳过空位把他们合并起来）不就行了？于是合并操作就变成了这样：

$hsh_{[l,r]}=hsh_{[l,mid]}*k^{len_{[mid+1,r]}}+hsh_{mid+1,r}$

我们对区间内的字符串进行删除的时候，把他的$hsh$与$len$都设为0（别忘了打上清除标记），于是我们就能在不断往上合并的时候跳过它了，从而达到了我们“删完后合并起来”的效果，于是我们从左到右枚举子串的中点然后在线段树上操作就行了，为了找到以$i$结尾的这个长度为$|T|$的子串的真正起点我们还要配合维护的区间真实长度在线段树上进行一个查排名的操作。

最后输出字符串的时候我们把整棵线段树dfs一遍把所有标记下传到叶子上，然后我们就能知道这个地方的字符是不是已经被删除了。

总而言之这方法非常暴力，~~不过我开始的时候以为这题数据范围$1e5$然后就写了个常数巨大的$O(nlogn)$线段树然后居然$A$了……但是不管是时间还是空间都是最差解……比第二差解还要慢5000ms……~~

上代码~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define p1 998244353
#define p2 1000000007
#define dk1 233
#define dk2 10003//要记得开双进制双模数hash哦~不然会WA的比jfca还要惨~（膜你赛的惨痛经历……） 
#define ls(_o) (_o<<1)
#define rs(_o) ((_o<<1)|1)
using namespace std;
char s1[1000001],s2[1000001];//两个串 
ll ldk1[1000001],ldk2[1000001];//进制的幂 
typedef struct _n {//封装线段树上维护信息的结构体 
	ll hsh1;
	ll hsh2;//hash值 
	int data;//区间的真实长度 
	void reset() {//对这两个hash取模 
		hsh1%=p1;
		hsh2%=p2;
	} _n() {//构造函数 
		hsh1=0;
		hsh2=0;
		data=0;
	}
	friend _n operator +(const _n &a,const _n &b) {//合并操作 
		_n c;
		c.data=a.data+b.data;
		c.hsh1=a.hsh1*ldk1[b.data]+b.hsh1;//这东西见最后一个式子 
		c.hsh2=a.hsh2*ldk2[b.data]+b.hsh2;
		c.reset();
		return(c);
	}
} node;
node data[4000001];
unsigned char clear[4000001];//区间的清除标记 
inline void up(int tree) {//上放 
	data[tree]=data[ls(tree)]+data[rs(tree)];
}
inline void down(int tree) {//标记下传 
	if(clear[tree]) {
		clear[tree]=0;
		clear[ls(tree)]=1;
		clear[rs(tree)]=1;
		data[ls(tree)]=data[rs(tree)]=_n();//把子树的hash都清空 
	}
}
void build(int l,int r,int tree) {//建树 
	if(l==r) {
		data[tree].data=1;
		data[tree].hsh1=data[tree].hsh2=s1[l];
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,ls(tree));
	build(mid+1,r,rs(tree));
	up(tree);
}
void clr(int rl,int rr,int l,int r,int tree) {//区间清空 
	if(clear[tree]||data[tree].data==0)return;
	if(rl==l&&rr==r) {
		clear[tree]=1;
		data[tree]=_n();
		return;
	}
	int mid=(l+r)>>1;
	down(tree);
	if(rl>mid)clr(rl,rr,mid+1,r,rs(tree));
	else {
		if(rr<=mid)clr(rl,rr,l,mid,ls(tree));
		else {
			clr(rl,mid,l,mid,ls(tree));
			clr(mid+1,rr,mid+1,r,rs(tree));
		}
	}
	up(tree);
}
node query(int rl,int rr,int l,int r,int tree) {//区间查询 
	if(data[tree].data==0)return(_n());
	if(rl==l&&rr==r)return(data[tree]);
	int mid=(l+r)>>1;
	down(tree);
	if(rl>mid)return(query(rl,rr,mid+1,r,rs(tree)));
	if(rr<=mid)return(query(rl,rr,l,mid,ls(tree)));
	return(query(rl,mid,l,mid,ls(tree))+query(mid+1,rr,mid+1,r,rs(tree)));
}
int rankof(int l,int r,int tree,int rk) {//区间查排名，用于找这个长度|T|的子串的开头 
	int mid=(l+r)>>1;
	if(l==r)return(l);
	if(data[ls(tree)].data>=rk)return(rankof(l,mid,ls(tree),rk));
	return(rankof(mid+1,r,rs(tree),rk-data[ls(tree)].data));
}
inline int get(char *str) {//并没有什么用的快读 
	char c;
	register int ptr=1;
	while((c=getchar())||23333)if(c>='a'&&c<='z')break;
	str[ptr]=c,ptr++;
	while((c=getchar())||23333) {
		if(c>='a'&&c<='z')str[ptr]=c,ptr++;
		else return(ptr-1);
	}
}
unsigned char cnt[1000001];
void tui(int l,int r,int tree) {//把整棵线段树dfs一遍往下推标记，推到叶子的cnt数组内 
	if(l==r) {
		cnt[l]=data[tree].data;
		return;
	}
	int mid=(l+r)>>1;
	down(tree);
	tui(l,mid,ls(tree));
	tui(mid+1,r,rs(tree));
}
int main() {
	int n=get(s1),m=get(s2);
	ldk1[0]=ldk2[0]=1;
	for(register int i=1; i<=n; i++) {//预处理出进制的幂 
		ldk1[i]=(ldk1[i-1]*dk1)%p1;
		ldk2[i]=(ldk2[i-1]*dk2)%p2;
	}
	build(1,n,1);
	ll hsh1=0,hsh2=0;
	for(register int i=1; i<=m; i++) {//把T的hash值搞出来 
		hsh1=(hsh1*dk1+s2[i])%p1;
		hsh2=(hsh2*dk2+s2[i])%p2;
	}
	for(register int i=1; i<=n; i++) {
		node qz=query(1,i,1,n,1);//前缀的真实长度
		if(qz.data<m)continue; 
		int pos=rankof(1,n,1,qz.data-m+1);//在线段树上查排名找以当前为结尾的子串的开头 
		node ans=query(pos,i,1,n,1)； 
		if(ans.hsh1==hsh1&&ans.hsh2==hsh2) {
			clr(pos,i,1,n,1);//找到一个能匹配的子串把他删除 
		}
	}
	tui(1,n,1);//dfs 
	for(register int i=1; i<=n; i++) {//输出答案 
		if(cnt[i])putchar(s1[i]);
	}
	return(0);
}
```

---

## 作者：songhongxi (赞：18)

额……竟然有位大佬说用AC自动机+栈
看上去好难的样子
为啥我用哈希+栈就a了……
也许你程序跑的比我快吧，不过我这种方法代码真的好短好短
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

typedef unsigned long long ull;
const ull prm=233317,N=1e6+5;
ull pwr[N]={1},hb,h[N],len,la,lb;
char a[N],b[N],ans[N];
//ans就相当于一个栈，len就是top
int main()	
{
	scanf("%s%s",a+1,b+1);
	la=strlen(1+a);lb=strlen(b+1);
	for(int i=1;i<=lb;i++)
	{
		pwr[i]=pwr[i-1]*prm;
		hb=hb*prm+b[i];
	}//哈希预处理
	for(int i=1;i<=la;i++)
	{
		ans[++len]=a[i];
		h[len]=h[len-1]*prm+a[i];
        //先入栈
		if(hb==h[len]-h[len-lb]*pwr[lb])//判断一下，如果相等（没学过哈希的先学一下。。。）
			len-=lb;//那这一段就不要了
	}
	for(int i=1;i<=len;i++)
		putchar(ans[i]);//华丽的输出
	return 0;
}

```

---

## 作者：anda (赞：7)

看到写哈希的人很少，大多用的高超做法，其实没那么可怕，来写一篇哈希的题解。

首先先把模数的所有次方求出来，这里的模数自己定，然后算出前缀和哈希值，这里我们也可以使用无符号整型自然溢出，相当于模一个质数，常数会变得更好。

然后开一个栈，每次将栈中加入一个字母，并将栈顶与子串调到同一位置后比较，看看哈希值调整后是否相等，若相等根据题意弹栈即可，他的时间复杂度大概是线性的。
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#define int long long
using namespace std;
int ahs[1000001],ctop,bhs,p=1e9+7,mod=998244353,q[1000001];
char a[1000001],b[1000001],c[1000001];
signed main(){
   scanf("%s%s",a,b);int atop=strlen(a),btop=strlen(b);q[0]=1;
   for(int i=1;i<=atop;i++)q[i]=q[i-1]*p%mod;//预处理次方
   for(int i=atop;i>=1;i--)a[i]=a[i-1];//预处理字符串
   for(int i=btop;i>=1;i--)b[i]=b[i-1];
   for(int i=1;i<=btop;i++)bhs=(bhs+b[i]*q[i]%mod)%mod;//求出子串哈希值
   for(int i=1;i<=atop;i++){
   	   c[++ctop]=a[i];//入栈
   	   ahs[ctop]=(ahs[ctop-1]+a[i]*q[ctop]%mod)%mod;//调整
   	   if(ctop>=btop&&(ahs[ctop]-ahs[ctop-btop]+mod)%mod==q[ctop-btop]*bhs%mod)ctop-=btop;
   }//栈操作
   for(int i=1;i<=ctop;i++)cout<<c[i];
}
```


---

## 作者：water_mi (赞：7)

这一题改一改$KMP$算法就可以过了，但是你需要对KMP有足够的了解。

先膜一波$AC$自动机和字符串$Hash$的大佬。

$O(n)$开了$O_2$优化后进了第三（截至目前），跑的还是挺快的。

---

$KMP$问题的核心在于数组$next$(或者$pre$/$fail$，各种叫法)，几乎所有的此类型题都是需要计算$next$的。

这里解释一波$next$:即满足字符子串$s[1...k]=s[j-k+1...j]$的最大$k$。比如说：

字符串$abaca$的$next[5]$就是$1$，因为只有$s[1]=s[5]$。

而字符串$abcab$的$next[5]$就是2，同理，$s[1...2]=s[4...5]$。

弄清楚了这一点，来看题目，显然，这道题的难点在于删除字符后有可能对前面已经匹配完了的字符产生新一次的匹配，因为后面新加入的字符可能对前面的字符有贡献。

既然这样，我们不妨设一下四个变量:$i,j,k,l$（所有字符串从$0$开始）。

其中$i,l$表示当前需要将$S_i$加入到$U_l$中，$j$表示当前匹配到了$T_j$，$k$表示当前已经匹配到$U_k$。

- 如果当$k==l$时，代表前$k-1$个字符已经匹配完，添加新字符。
- 接下来就是调整$next$和判断是否匹配，同普通$KMP$算法 。
- ！！重点：当$j==lenT$即已经匹配完了，则将$j$归零，将$l$减去$lenT$示删去了$lenT$个字符，因为$l$就是新串的长度，接下来，我们直接将$k$减去$lenT\times 2$因为前面最多会有$lenT-1$个字符与$T$匹配，特判一下当$k<0$时将$k$置为$0$就可以了。

---

```cpp
#include <cstdio>
#include <cstring>

const int Len = 1e6 + 10;
char S[Len], T[Len], U[Len];
int lenS, lenT, nxt[Len];

void init () {
	for (int i = 1, j = 0; i < lenT; ++i) {
		while (j && T[i] != T[j]) j = nxt[j];
		j += (T[i] == T[j]), nxt[i + 1] = j;
	}
} 

int main () {
	scanf ("%s%s", S, T);
	lenS = strlen (S), lenT = strlen(T);
	init ();
	int l = 0, k = 0, i = 0, j = 0;
	while (i < lenS) {
		if (k == l)	U[l++] = S[i++];
		while (j && U[k] != T[j]) j = nxt[j];
		j += (U[k] == T[j]);
		if (j == lenT) {
			j = 0, l -= lenT;
			k -= lenT << 1;
		}
		if (k < 0) k = 0;
		else ++k;
	}
	for (int i = 0; i < l; ++i)
		putchar (U[i]);
	return 0;
} 
```



---

## 作者：香风智乃 (赞：5)

**AC自动机+栈**

~~还好内存没炸~~

本题强化版[P3121](https://www.luogu.org/problemnew/show/P3121)双倍经验（大雾）

**attention：数组要比P3121大10倍**

（如果不会AC自动机的话就跳转到下一篇吧qwq）

字符串匹配--->AC自动机

删除单词的特性--->栈

所以我们先打个AC自动机模板

然后搞2个栈维护：

- AC自动机目前跑到字典树上的哪个点

- 已经跑过且没被删除的字符（答案栈）

每次碰到有结尾标记的点，就让2个栈弹出**这个点所对应的单词的长度 **

最后输出第二个栈就行了

[juruo's blog](https://www.cnblogs.com/kafuuchino/p/9622034.html)

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
struct data{
    int nxt[26],fail/*,last*/,end;
}a[1000005];
int n,cnt,top,stk1[1000005],stk2[1000005];
char g[1000005],q[1000005];
inline void Trie_build(){
    scanf("%s",q);
    int u=0,len=strlen(q);
    for(int i=0;i<len;++i){
        int p=q[i]-'a';
        if(!a[u].nxt[p]) a[u].nxt[p]=++cnt;
        u=a[u].nxt[p];
    }a[u].end=len;
}
void AC_build(){
    queue <int> h;
    for(int i=0;i<26;++i) if(a[0].nxt[i]) h.push(a[0].nxt[i]);
    while(!h.empty()){
        int x=h.front(); h.pop();
        for(int i=0;i<26;++i){
            int &to=a[x].nxt[i];
            if(to){
                a[to].fail=a[a[x].fail].nxt[i];
                //a[to].last= a[a[to].fail].end ? a[to].fail:a[a[to].fail].last;
                h.push(to);
            }else to=a[a[x].fail].nxt[i];
        }
    }
}
//---------以上裸AC自动机------------
void query(){
    int u=0,len=strlen(g);
    for(int i=0;i<len;++i){
        u=a[u].nxt[g[i]-'a'];
        stk1[++top]=u; //栈1存当前点在字典树中的位置
        stk2[top]=i; //栈2存字符（答案）在主串中所在的位置
        while(a[u].end) top-=a[u].end,u= top ? stk1[top]:0; //删除操作
    }
    for(int i=1;i<=top;++i) putchar(g[stk2[i]]);
    putchar('\n'); //不换行就蜜汁爆炸（大雾）
}
int main(){
    scanf("%s",g);
    Trie_build();
    AC_build();
    query();
    return 0;
}
```

---

## 作者：Strelitzia (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P4824)

---

字符串匹配，应该是可以用 $\text{KMP}$，主要是匹配之后，它又可能组成 $\operatorname{T}$，这就很恶心了。

但是，对于一个没有匹配成功的字母，它对应的目标字符串的位置是不会改变的。

所以我们可以用一个 $\operatorname{f}$ 数组记录这个字符匹配的对应位置。

用一个栈记录没匹配成功的数，匹配成功就把这部分移出。

代码很简单

```cpp
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>void read(T &x) {
    T f = 1;x = 0;char s = getchar();
    while(s < '0' || s > '9') {if(s == '-')f = -1;s = getchar();}
    while(s >= '0' && s <= '9') {x = x * 10 + s - '0';s = getchar();}
    x *= f;
}
template<typename T>void print(T x) {
    if(x < 0) putchar('-'),x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

const int maxn = 1000005;

char a[maxn],b[maxn];
int lena,lenb,f[maxn];

int pre[maxn],s[maxn],top;

void make_pre(char b[],int lenb) {
	pre[1] = 0;
	int j = 0;
	for (int i = 2 ; i <= lenb ; ++ i) {
		while (j && b[i] != b[j + 1]) j = pre[j];
		if (b[i] == b[j + 1]) j ++;
		pre[i] = j;
	}
}

void KMP(char a[],char b[],int lena,int lenb) {
	int j = 0;
	for (int i = 1 ; i <= lena ; ++ i) {
		while (j && a[i] != b[j + 1]) j = pre[j];
		if (a[i] == b[j + 1]) j ++;
		f[i] = j;s[++ top] = i;
		if (j == lenb) {
			top = top - lenb;
			j = f[s[top]];
		}
	}
}

int main () {
	scanf ("%s",a + 1);
	scanf ("%s",b + 1);
	lena = strlen(a + 1);
	lenb = strlen(b + 1);
	make_pre(b,lenb);
	KMP(a,b,lena,lenb);
	for (int i = 1 ; i <= top ; ++ i) {
		printf("%c",a[s[i]]);
	} 
	return 0;
}
```

---

## 作者：localhost (赞：1)

//这里提供简单的栈+hash做法,~~因为太菜没想到可以用kmp~~

删除完这个字符串后面的就接到前面

我们可以想到用栈解决

然后判断剩下的串当前位置是否和目标字符串匹配我们可以用hash来解决

不会的话可以看代码解释

```cpp
#include<bits/stdc++.h>
namespace ZDY{
    #pragma GCC optimize(3)
    #define il __inline__ __attribute__ ((always_inline))
    #define rg register
    #define ll long long
    #define ull unsigned long long
    #define db double
    #define sht short
    #define MB template <class T>il
    #define Fur(i,x,y) for(int i(x);i<=y;++i)
    #define Fdr(i,x,y) for(int i(x);i>=y;--i)
    #define fl(i,x) for(int i(head[x]),to;to=e[i].to,i;i=e[i].nxt)
    #define clr(x,y) memset(x,y,sizeof(x))
    #define cpy(x,y) memcpy(x,y,sizeof(x))
    #define fin(s) freopen(s".in","r",stdin)
    #define fout(s) freopen(s".out","w",stdout)
    #define fcin ios::sync_with_stdio(false)
    #define l2(n) ((int)(log2(n)))
    #define inf 2122219134
    MB T ABS(T x){return x>0?x:-x;}
    MB T MAX(T x,T y){return x>y?x:y;}
    MB T MIN(T x,T y){return x<y?x:y;}
    MB T GCD(T x,T y){return y?GCD(y,x%y):x;}
    MB void SWAP(T &x,T &y){T t=x;x=y;y=t;}
}using namespace ZDY;using namespace std;
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(string &ch){ch.clear();if(__)return;rg char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)__=1;}il void in(char &ch){if(__)return;rg char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;rg char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;rg char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}il void out(string s){for(int i=0;s[i];i++)pt(s[i]);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
//快读
#define N 1000011
#define base 1331
int n,q[N],tp=0,m;
char a[N],s[N];
ull h[N],pw[N],sta=0;
int main(){
    in(a+1);
    in(s+1);
    n=strlen(a+1);
    m=strlen(s+1);
    pw[0]=1;
    Fur(i,1,n)
        pw[i]=pw[i-1]*base;
    Fur(i,1,m)sta=sta*base+s[i];//目标串状态
    Fur(i,1,n){
        q[++tp]=i;
        h[tp]=h[tp-1]*base+a[i];
        if(tp>=m&&h[tp]-h[tp-m]*pw[m]==sta)tp-=m;//如果符合就跳到前面的位置
    }
    Fur(i,1,tp)pt(a[q[i]]);
    flush();
}
```


---

