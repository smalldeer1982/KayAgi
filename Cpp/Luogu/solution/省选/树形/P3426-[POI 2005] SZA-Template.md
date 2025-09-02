# [POI 2005] SZA-Template

## 题目描述

你打算在纸上印一串字母。

为了完成这项工作，你决定刻一个印章。印章每使用一次，就会将印章上的**所有**字母印到纸上。

同一个位置的相同字符可以印多次。例如：用 `aba` 这个印章可以完成印制 `ababa` 的工作（中间的 `a` 被印了两次）。但是，因为印上去的东西不能被抹掉，在同一位置上印不同字符是不允许的。例如：用 `aba` 这个印章不可以完成印制 `abcba` 的工作。

因为刻印章是一个不太容易的工作，你希望印章的字符串长度尽可能小。

## 说明/提示

印章为 `ababbaba`。

印制过程如下：

```plain
ababbababbabababbabababbababbaba
ababbaba
     ababbaba
            ababbaba
                   ababbaba
                        ababbaba
```

## 样例 #1

### 输入

```
ababbababbabababbabababbababbaba```

### 输出

```
8```

# 题解

## 作者：i207M (赞：137)

发这篇题解完全是因为题解里的方法都好麻烦啊...~~好像是我们暑假考试的题~~

我们肯定是要KMP求出next数组（以下可能简称nx），然后想办法DP。

我们直接设$f[i]$表示前缀i的答案。

然后我们考虑，$f[i]$只有2种取值：$i,f[nx[i]]$，原因很简单，想覆盖i起码要覆盖$nx[i]$。

什么时候答案才能为$f[nx[i]]$呢，因为前缀i的最后几个字符为$nx[i]$，所以我们最多在后面接上$nx[i]$这么长的字符串，也就是充要条件为存在一个j，使得$f[j]=f[nx[i]],i-nx[i]\le j$

具体实现的话开一个桶即可。

```cpp
#define N 500005
int n;
int nx[N];
int f[N],h[N];
char s[N];
signed main()
{
#ifdef M207
	freopen("in.in","r",stdin);
	// freopen("out.out","w",stdout);
#endif
	scanf("%s",s+1); n=strlen(s+1);
	nx[0]=-1;
	for(ri i=2,j=0; i<=n; ++i)
	{
		while(j!=-1&&s[j+1]!=s[i]) j=nx[j];
		nx[i]=++j;
	}
	f[1]=1;
	for(ri i=2; i<=n; ++i)
	{
		f[i]=i;
		if(h[f[nx[i]]]>=i-nx[i]) f[i]=f[nx[i]];
		h[f[i]]=i;
	}
	out(f[n]);
	return 0;
}
```

---

## 作者：wtgrz (赞：96)

由题意可知这个模式串$p$（印章）一定是主串的公共前后缀之一。

一个暴力的想法就是枚举不同的公共前后缀然后做kmp，判断每次完全匹配的位置之差是否大于其长度，就是说要完全覆盖不能有露出的地方。

然后优化可以采用dp的思想。这个不太好想，我们利用$dp[i]$代表到以字符$s[i]$结尾的前缀的最短印章长度。然后考虑怎么转移。

首先说对于一些情况，比如最长公共前后缀为0（$nxt[i] = 0$）的情况，那么只能让$dp[i]=i$才能全部覆盖。

对于别的情况，我们根据开始所说的性质，这个模式串$p$一定是主串的公共前后缀之一，所以我们感觉应该是与$dp[nxt[i]]$有关，其实当满足某种条件下， $dp[i]=dp[nxt[i]]$是成立的。接下来来说明这一点。

我们知道答案肯定是属于所有的公共前后缀里面的，也就是说答案的集合的范围可以确定了，如果我们考虑另一点$j$，那么$dp[j]$，那么虽然$dp[j]$可能是答案，但是它并不符合我们上面所说的，因为以$j$为结尾的公共前后缀集合和以$i$结尾的公共前后缀集合未必相同。

那么对于$nxt[i]$这一点来说呢，很明显他的所有公共前后缀是包含在$i$中的，也就是$ans(dp[nxt[i]])\in ans(dp[i])$,但是这样还不完备，就是缺少了$nxt[i]$本身，因为$nxt[i]$的公共前后缀是不包括他自己的，如果观察我们的$dp$的转移过程，我们发现$dp[nxt[i]]$的答案集合也是包含了$nxt[i]$自身的，这样就完备了，也就是说**$dp[i]$答案的集合是与$dp[nxt[i]]$一致的**。

那么转移关系就明显了。即
$dp[i] = i\ or  \ dp[i] = dp[nxt[i]]$。

什么时候可以转移呢？
假定我们以$dp[nxt[i]]$作为印章长度，那么我们毫无疑问可以用其覆盖最后的一部分（因为印章也是后缀），但是我们需要知道在前面是否存在一个点$j$，使得到$j$点是可以被$dp[nxt[i]]$所代表的印章覆盖的并且能与最后我们要覆盖的后缀部分衔接上。画个图就清楚了。
![](https://img-blog.csdnimg.cn/20200626085508166.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzM1OTU2NQ==,size_16,color_FFFFFF,t_70#pic_center)
在上面的那种情况里绿色的部分是无法被覆盖到的。

所以我们还需要维护不同子串所能覆盖的最后位置，用一个桶来维护。
代码和最上面的题解差不多，就不贴了。

---

## 作者：kczno1 (赞：26)

考虑一个前缀i可以涂完意味着什么。

首先，他得是n的border。

并且，如果把所有border为它的点列出来，相邻差的max<=i。

对应到kmp的next构成的树上,

就是i在n到根的那条链上，并且把他子树的点列出来，相邻差的max<=i。

从根往n那边走，在删点的同时维护每个点的前驱后继，从而维护max，就可以了。

```cpp
#include<bits/stdc++.h>
using std::vector;

#define rep(i,l,r) for(int i=l;i<=r;++i)
#define pb push_back
void chmax(int &x,int y)
{
    if(x<y)x=y;
}
const int N=5e5+5;
char s[N];int n,next[N];
int to[N];
vector<int>son[N];

int pre[N],suf[N],mx;

void del(int x)
{
    if(x)
    {
        int p=pre[x],s=suf[x];
        chmax(mx,s-p);
        suf[p]=s;pre[s]=p;
    }
    for(vector<int>::iterator i=son[x].begin();i!=son[x].end();++i)
    if(*i!=to[x]) del(*i);
}

int main()
{
    freopen("1.in","r",stdin);
    scanf("%s",s+1);
    n=strlen(s+1);
    int j=0;
    rep(i,2,n)
    {
        while(j&&s[j+1]!=s[i])j=next[j];
        if(s[j+1]==s[i]) next[i]=++j;
    }
    
    rep(i,1,n)son[next[i]].pb(i);
    for(int i=n;i;i=next[i]) to[next[i]]=i;
    
    rep(i,1,n) {pre[i]=i-1;suf[i]=i+1;}
    del(0);
    int i=1;
    while(mx>i) { del(i);i=to[i]; }
    printf("%d\n",i);
}
```

---

## 作者：Erina (赞：21)

一只国家集训队巨佬强制向我传了邪教(

然后我就邪教了......

就是...... 利用国家集训队级别的芝士切紫题

我们老师找我们做题, 我们去找大佬寻找思路, 然后大佬就翻出了一些......

......

下面进入正题

我们使用了什么特殊性质呢?

我们定义, 一个字符串s, 它的border是**既是它的前缀又是它的后缀, 且不等于s本身**的串.

然后我们定义真border是所有border中的最长者.

那么有这么一个神仙性质, 就是所有长度大于$\lfloor|s|/2\rfloor$的border的长度形成一个等差数列, 并且这些串可以互相表达.

然后我们又有一个神仙性质, 就是一个串的所有border长度是`next[n], next[next[n]]......` 其中`next`就是KMP的数组......

是不是很神奇...... 证明比较复杂......

那么简单地证明一下......

设最大border长度是n-p, 另一个是n-q, 那么$\gcd{(p,q)}$是s的周期. 那么$n-\gcd(p,q)$也是一个border.

也就是说$\gcd(p,q)=p, p|q$ 证毕.

然后我们发现就是整个字串的匹配一定是它自己或者它的一个border.

既然这些串可以相互表达, 那么, 如果一个小串可以表达一个长串, 那么长串一定不优, 舍去.

然后我们发现每一次长度就会减半...... 也就是说只有$\lg{n}$种不同的border, 它们的长度每个比另一个大一倍以上......

然后我们考虑找到那个是最优的.

我们从最小的开始向上......

每一次找到一个目前最小切可行的, 然后匹配当前的, 如果不行, 那么将当前的置为最优.

但是怎么检验能否覆盖呢? 字符串蛤希啊!

然后...... 差不多就是这样吧......

可能有一些难懂, 但是代码还是蛮简洁的......

那么放一下代码吧...... 很多思想和细节都在代码里面......

```cpp
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
char huaji[500010];
int len, nex[500010];
unsigned long long haxi[500010], power[500010];
vector<int>borders;
int sum[500010];
int main() {
	gets(huaji + 1);
	len = strlen(huaji + 1);
	for (int i = 2; i <= len; i++) {
		nex[i] = nex[i - 1];
		while (nex[i] && huaji[nex[i] + 1] != huaji[i])nex[i] = nex[nex[i]];
		if (huaji[nex[i] + 1] == huaji[i])nex[i]++;
	}
	// 这一题并没有卡蛤希, 我们直接long long自然溢出就可以了
	power[0] = 1;
	for (int i = 1; i <= len; i++)power[i] = power[i - 1] * 19260817, haxi[i] = haxi[i - 1] * 19260817 + huaji[i];// 记住, 这是蛤希
	for (int i = len; i; i = nex[i])if (nex[i] * 2 < i)borders.emplace_back(i);// 这是一个**有用的**border
	reverse(borders.begin(), borders.end());
	int ans = borders[0];
	for (int i = 1; i <= borders.size() - 1; i++) {
		// 从小到大逐个比较, 尝试用当前最优的串去匹配当前串, 如果匹配失败, 那么舍弃之前的串, 使用现在的作为最优解(不是因为刺穿更优, 而是之前的串不行......)
		int cur = borders[i];
		memset(sum, 0, (cur + 10) * sizeof(int));
		sum[ans] = 1;
		for (int i = ans + 1; i <= cur; i++)sum[i] = sum[i - 1] + (haxi[i] - haxi[i - ans] * power[ans] == haxi[ans] && sum[i - 1] != sum[i - ans - 1]);
		// 使用蛤希匹配, 计算能否使用最优串匹配当前串
		if (sum[cur] == sum[cur - 1])ans = cur;
	}
	cout << ans;
}
```

跑的挺快的...... 其它题解没有见到, 所以这里简单地写一下......


---

## 作者：SamariumPhosphide (赞：15)

首先考虑，这个印章肯定是原串的一个 $\text{Border}$，因此一定在失配树上，根节点到编号为 $\text{len}$ 的节点的路径上的一点。

而怎么样的路径是合法的呢？对于 一个 $\text{Border}$，$\text{pre}(s,i)$ ，怎么样才能让它是合法的印章，显然它要通过连接拼出原串。而我们考虑每一个印章的结束位置，设这个结束位置为 $j$ 那么一定满足 $\text{pre}(s,i)$ 为 $\text{pre}(s,j)$ 的 $\text{Border}$，也就是在失配树中 $i$ 的子树中。

那么我们考虑每个这样的节点，如果有两个节点之间距离 $>i$ 那么就会发现这两个印章之间必然会出现空隙，不能拼接完成。而如果距离 $\leq i$ 那么一定可以拼成。

综上，我们总结出了这个印章串 $\text{pre}(s,i)$ 需要满足的性质：

+ $\text{pre}(s,i)$ 为字符串 $s$ 的 $\text{Border}$，即在失配树上的祖先节点。
+ 对于所有 $j$ 满足 $\text{pre}(s,i)$ 为 $\text{pre}(s,j)$ 的 $\text{Border}$，即在其子树中，经过排序后相邻的最大距离不能超过 $i$。

那么只需要维护最大距离即可。首先把从根节点到 $\text{len}$ 节点之间的路径打上标记。

考虑从根节点开始，每次把在**下一次统计的子树**以外的东西全部删掉，使用双向链表维护最大值即可，$\mathcal O(n)$。如果不能理解，可能参考代码更容易理解一些。

[Code Here](https://www.luogu.com.cn/paste/lr2dbas5)

---

## 作者：Orion545 (赞：10)

# 广告

[蒟蒻のblog](http://www.cnblogs.com/dedicatus545/p/8903324.html)

# 思路

首先，我们观察一下这个要求的“模板串”，发现它有如下性质：

1.一个模板串$A$是要求的文本串$B$的公共前后缀

2.如果一个模板串$A$有另一个模板串$B$（也就是$B$可以覆盖A），那么$B$是比$A$更优的一个解

3.如果模板串$A$可以完全覆盖文本串$B$，那么$A$在$B$中的匹配位置（按照开头算）之间的空格数不会超过$A$的长度

这三条性质都挺明显的是吧？接下来我们就看看我们能怎么利用它

### 如何利用性质一？

性质一告诉我们，我们可以把文本串的$next$数组（就是$KMP$里面那个）求出来，然后做这样的操作：

```cpp
i=n;//n=strlen(文本串)
while(i) s[++top]=i,i=next[i];
```

做完这个操作以后栈$s$中就存放了所有可能的模板串长度

### 如何利用性质二？

我们从小到大枚举$s$中的模板串，对于每个模板串，如果它满足性质三，就令这个长度为答案，否则就再增长一点

同时，我们有一个结论：能被/长度比较长的/符合性质一的/模板串（对于原串满足）/满足性质一的/一个前缀（这个前缀作为文本串满足）/，一定能和/长度比它短的/另一个模板串（此处也是作为文本串）/满足性质一（这句话意思比较绕）

### 如何利用性质三？

我们构建一个链表（双向的），只包含删除操作和求最大空隙操作，那么它的每个操作是$O\left(1\right)$的

那么我们一开始把文本串的所有位置插入链表，每一次更新上一个长度的模板串能满足性质一的、但是当前长度的模板串不能满足性质一的字符位置（也就是把那个点从链表里面删掉），维护最大空隙

当一个模板串满足性质三的时候，它就是答案了（因为我们是从小到大枚举的，而题目要求最短的那个）

### 还剩什么问题？

我们最后剩下一个问题：如何把匹配$s[i+1]$代表的模板串、但是不匹配$s[i]$代表的模板串的位置找出来？

这里我们要利用一个新的数据结构（可能不算？），就是$fail$树（也称$next$树）

$fail$树就是把$fail[i]$（为了方便，以后$next[i]$称作$fail[i]$）和$i$连起来形成的树，以0为根节点

$fail$树有这样的性质：

1.点$x$如果是点$y$的祖先，那么$y$代表的前缀的一个公共前后缀为$x$代表的前缀
 
2.不在同一子树内的两点代表的前缀不能互相满足性质一

那么，我们发现，这道题的问题，其实就是从根节点开始往n号节点走一条链，并且每次把当前节点的$fail$树子树中的所有节点标记，统计原串上的最大空隙，如果空隙小于当前节点代表的前缀的长度，就作为答案输出

所以实际上这是个fail树的题目

好像不用fail也能做？反正本蒟蒻是想不出来......

# Code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char a[500010];int n,cnt,maxgap,fail[500010],pre[500010],suc[500010],first[500010],ans[500010],tot;
struct edge{//fail树上的边
    int to,next;
}e[500010];
void add(int u,int v){
    e[++cnt]=(edge){v,first[u]};first[u]=cnt;
}
void getfail(){//求next数组（我的代码里叫fail）
    int i,j=0;
    for(i=1;i<n;i++){
        while(j&&(a[i]!=a[j])) j=fail[j];
        j+=(a[i]==a[j]);fail[i+1]=j;
    }
    for(i=1;i<=n;i++) add(fail[i],i);
}
void del(int x){//链表删除操作，O(1)
    suc[pre[x]]=suc[x];
    pre[suc[x]]=pre[x];
    maxgap=max(maxgap,suc[x]-pre[x]);suc[x]=pre[x]=0;
}
int q[500010];
void bfs(int s,int avoid){//s的子树中，避开avoid的子树，其余点全部从链表里面删掉
    int u,v,i,head=0,tail=1;q[0]=s;
    while(head<tail){
        u=q[head++];if(u==avoid) continue;
        del(u);
        for(i=first[u];~i;i=e[i].next){
            v=e[i].to;q[tail++]=v;
        }
    }
}
int main(){
    memset(first,-1,sizeof(first));memset(fail,0,sizeof(fail));int i,j;
    scanf("%s",a);n=strlen(a);
    getfail();
    for(i=n;i;i=fail[i]) ans[++tot]=i;ans[tot+1]=0;
    for(i=1;i<=n;i++) pre[i]=i-1,suc[i]=i+1;
    maxgap=1;
    for(i=tot;i>=1;i--){
        bfs(ans[i+1],ans[i]);
        if(maxgap<=ans[i]){
            printf("%d",ans[i]);return 0;
        }
    }
}
```

---

## 作者：oscar (赞：7)

【POI补全计划#10 POI2005 SZA】


鉴于我没看懂kczno1巨神的题解，我决定自己来写一个


看题立刻想到KMP，就先把next数组求出来


接下来发现模板串满足三个条件


1.一定是一个前缀


2.结束位置一定是最后一个字符一直沿着next数组走能到达的点


3.这个模板串在原串中的所有出现位置一定能覆盖整个串


于是我们从小到大枚举满足条件2的结束位置，每次判一下能不能覆盖整个串，然后就TLE了


然后猜到一个性质（貌似挺显然的）：


能被更短的前缀完全覆盖的前缀一定不是最短的模板串


这就好办了，只需要每次记录当前能覆盖到什么位置，然后每次枚举覆盖到的位置之后的、满足条件2的结束位置，每次判一下能覆盖到哪就做完了


~~然而我不会算这个复杂度，只知道跑得飞快~~


贴代码


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=500010;
char str[MAXN];
int fail[MAXN];
struct atom
{
    int num;
    atom *next;
}*h[MAXN],pool[MAXN];
int top;
int flag[MAXN],arr[MAXN];
int top2,minn;
int main()
{
    scanf("%s",str+1);
    int len=strlen(str+1),k=0;
    for(int i=2;i<=len;++i)
    {
        while(k!=0&&str[k+1]!=str[i])k=fail[k];
        if(str[k+1]==str[i])++k;
        fail[i]=k;
    }
    for(int i=len;i>=1;--i)
    {
        atom *tmp=&pool[++top];
        tmp->num=i;
        tmp->next=h[fail[i]];
        h[fail[i]]=tmp;
    }
    for(int k=len;k;k=fail[k])
    {
        flag[k]=1;
    }
    for(int i=1;i<=len;++i)
    {
        if(flag[i])
            arr[++top2]=i;
    }
    for(int k=1;k<=top2;++k)
    {
        if(arr[k]<=minn)continue;
        memset(flag,0,sizeof(flag));
        int last=arr[k];
        flag[arr[k]]=1;
        for(int i=arr[k];i<=len;++i)
        {
            if(flag[i])
            {
                for(atom *tmp=h[i];tmp;tmp=tmp->next)
                {
                    flag[tmp->num]=1;
                }
                last=i;
            }
            else if(i-last>=arr[k])break;
        }
        if(last==len)
        {
            printf("%d\n",arr[k]);
            return 0;
        }
        minn=last;
    }
    return 0;
}
```
update@17.10.26:minor bug fixes


---

## 作者：RPChe_ (赞：4)

翻了一下题解，发现大佬们都选择使用了kmp算法来做这道题，然而这里还有一种解法，使用~~非常冷门的~~exkmp算法。

如果想了解exkmp算法，可以先做一下这道题：[P5410 【模板】扩展KMP（Z 函数）](https://www.luogu.com.cn/problem/P5410)。

简单阐述一下，做这道题我们所要使用的是exkmp算法中的next数组，同样是一个失配指针。但它的定义和kmp算法中的next数组不一样。我们知道，exkmp算法求解的是模式串T与主串S的每一个后缀的最长公共前缀长度，那么相应的，这个next数组存的就是T和T本身的每一个后缀的最长公共前缀长度。

我们再康康这道题，就是要找到一个子串把母串打印完。那么这个子串必定是母串的前缀，是母串的后缀，因为题中提到“印章每使用一次，就会将印章上的所有字母印到纸上。”

对应到next数组，我们已经确定了它是母串的前缀，那么如果它的结尾到达了母串的结尾，它就还是母串的后缀，满足上面的条件，有可能是我们要找的子串。

然后我们就检查这个子串。具体的，首先排除掉next数组中所有小于这个子串长度的元素，因为它们太短了，不能被这个子串所打印。

然后，我们记录一下next数组剩下的元素中相邻元素排除前的下标，即它们所代表的串的起始位置，的差的最大值$maxlenth$，并和这个子串的长度比较一下。如果这个子串较长，就说明这个子串可以打印出母串，否则不行，因为如果maxlenth大于这个子串的长度，就说明在打印的过程中存在断点，无法打印。

上面的叙述有些抽象了，想看更直观的操作过程的话，下面是代码——

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#define rep(i,a,b) for(register int i=a;i<=b;i++)
#define inf 0x3f3f3f3f
#define maxn 50000005
using namespace std;

int les,nxt[maxn],ans=inf;
string s;

inline void exkmp() {
	les=s.size()-1;
	int j=0;
	nxt[0]=les+1;
	while(s[j]==s[1+j]&&j+1<=les) j++;
	nxt[1]=j;
	int maxp=1;
	rep(i,2,les) {
		if(i+nxt[i-maxp]<nxt[maxp]+maxp) nxt[i]=nxt[i-maxp];
		else {
			j=nxt[maxp]+maxp-i;
			j=max(j,0);
			while(s[j]==s[i+j]&&i+j<=les) j++;
			nxt[i]=j;
			maxp=i;
		}
	}
}//exkmp算法模板

void check() {
	rep(i,0,les) {//枚举所有子串
		if(i+nxt[i]==les+1) {//是母串的后缀
			int pre=0,flag=0;
			rep(j,0,les) {
				if(j-pre>nxt[i]) {把子串长度和maxlenth比较
					flag=1;
					break;
				}
				if(nxt[j]>=nxt[i]) pre=j;//保存上一个不被排除的元素的下标
			}
			if(!flag) ans=min(ans,nxt[i]);//更新答案
		}
	}
}//检查子串是否可以打印母串

int main() {
	ios::sync_with_stdio(false);
	cin>>s;
	exkmp();
	check();
	cout<<ans;
	return 0;
}
```

当然，这个解法很慢，时间复杂度上限$O(n^2)$，被各位大佬的kmp算法吊打，甚至还有可能被卡掉。~~果然窝太菜了QWQ~~

---

## 作者：Unnamed114514 (赞：4)

upd on 2024.11.17：发现讨论区有 [hack](https://www.luogu.com/discuss/414542)，经测试可以通过，当然也欢迎各位 hack。

先枚举 border 长度 $L$。

定义 $f_i$ 表示 $s_{1,i}$ 是否能被表示出来。

如果 $s_{1,L}=s_{i-L+1,L}$，那么我们可以在前面接，即 $f_i\gets\cup_{j=i-L}^{i-1} f_j$，其中 $\cup$ 表示逻辑或，这一步可以用前缀和优化到 $O(1)$ 的转移；否则因为 $s_i$ 一定不会被覆盖到，所以 $f_i\gets0$。

上述做法是 $O(n^2)$ 的，考虑剪枝。

注意到 $L$ 是定长，如果 $f$ 中出现了连续 $L$ 个 $0$，那么后面一定都是 $0$，因为转移只根前 $L$ 个有关。

这样就能过掉洛谷上的所有数据，但是仍然会存在 `hack`，如果我们是一车 `a` 后面跟了个 `b`，那么我们会找 `a`、`aa` 等，但是发现 `a` 一定强于 `aa`，所以**由一个 border 复制若干遍得到的 border 一定是不优的**。

但是这样也仍然有锅，如果我们复制若干遍 `ab`，最后接上个 `c`，会发现所有长度为奇数的串都会被查询！但是注意到 `ababa` 能表示的 `aba` 一定能表示。这样我们就得到一个比刚才更强的结论：**如果一个 border 能被其它 border 表示出来，那么它一定不优**。

实现方面就是如果 $f_i=1$，我们就给 $i$ 打上个标记，然后枚举到长度 $i$ 的时候就直接跳过。

这样做在洛谷目前的数据下非常优秀，最慢点仅 11ms。

---

## 作者：Eric20521 (赞：2)

https://www.luogu.com.cn/problem/P3426

首先应意识到印章是字符串的一个 boader

然后考虑怎样的 boarder 满足条件呢？即其匹配位置的 max_gap 应小于等于其 length

将这个条件进行一步转化：在失配树上考虑，其子树中的 max_gap 小于等于其 length 

这样考虑在失配树上实现，可以使用 set 配合维护 max_gap

在 dfs 时，由于首先提到的 答案是全串的 boader 所以候选节点在树上是一条链，只考虑这些点即可。每在链上深入一个节点前，先将其兄弟（的子树）都扒掉，即从 set 中删除这些节点，并维护 max_gap ，由于失配树性质，dfs 过程中遇到的第一个满足条件的节点就是答案。

代码：

```cpp
#include<iostream>
#include<cstring>
#define maxn 500005
#include<vector>
#include<set>

using namespace std;
string a;
int nxt[maxn];
int n;
int f[maxn];

vector<int> e[maxn];
set<int> s;
set<int> :: iterator it;

int gap=1;
void del(int x){
	
	it=s.find(x);
	if(it==s.begin()){
		s.erase(x);
		return ;
	} 
	
	++it;
	if(it==s.end()){
		s.erase(x);
		return ;
	}
	
	int r=*it;
	--it;--it;
	gap=max(gap,r-*it);
	s.erase(x);
	return ; 
}

void dfs(int u){
	if(f[u] && u>=gap){
		cout<<u<<endl;
		return ;
	}
	
	del(u);
	
	int v;
	for(int k=0;k<e[u].size();k++){
		v=e[u][k];
		if(!f[v]) dfs(v);
	}
	
	for(int k=0;k<e[u].size();k++){
		v=e[u][k];
		if(f[v]) dfs(v);
	}
	
	return ;
}

int main(){
	cin>>a;
	n=a.length();
	a="*"+a;
		
	int j=0;
	e[0].push_back(1);
	for(int i=2;i<=n;i++){
		while(j && a[j+1]!=a[i]) j=nxt[j];
		if(a[j+1]==a[i]) ++j;
		nxt[i]=j;
		e[nxt[i]].push_back(i);
	}
	
	int p=n;
	while(p){
		f[p]=1;
		p=nxt[p];
	}
	
	for(int i=0;i<=n;i++){
		s.insert(i);
	}
		
	dfs(0);
		
	return 0;
} 
```

---

