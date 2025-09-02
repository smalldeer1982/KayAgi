# Frequency of String

## 题目描述

给你一个字符串 $s$，你要回答 $n$ 个问题，第 $i$ 个询问包含两个参数，一个整数 $k_i$ 和一个字符串 $m_i$，你需要回答从 $s$ 中选出一个它的连续子串 $t$ 使得 $m_i$ 作为 $t$ 的子串出现了至少 $k_i$ 次，$t$ 的长度的最小值。

保证两个询问的 $m_i$ 不同。

## 样例 #1

### 输入

```
aaaaa
5
3 a
3 aa
2 aaa
3 aaaa
1 aaaaa
```

### 输出

```
3
4
4
-1
5
```

## 样例 #2

### 输入

```
abbb
7
4 b
1 ab
3 bb
1 abb
2 bbb
1 a
2 abbb
```

### 输出

```
-1
2
-1
3
-1
1
-1
```

# 题解

## 作者：唐一文 (赞：13)

首先考虑最朴素的暴力，把每个串出现过的下标找出来，然后滑动区间跑一遍答案，复杂度 $O(n|S|)$。

考虑根号分治。令 $B=\sum|m_i|$，长度大于 $B$ 的串不超过 $\dfrac{\sum|m_i|}{B}$ 个，直接跑暴力。复杂度 $O\left(\dfrac{\sum|m_i|}{B}|S|\right)$

长度不大于 $B$ 的串可以将 $S$ 中长度为 $1\sim B$ 的子串都找出来，然后丢到对应的询问里面，对每个询问跑一遍滑动区间。因为这些子串有 $B|S|$ 个，所以复杂度 $O(B|S|)$。

总复杂度 $O\left(\dfrac{\sum|m_i|}{B}|S|+B|S|\right)$，当 $B=\sqrt{\sum|m_i|}$ 时最优。

[Code](https://www.luogu.com.cn/paste/21vc53ff)

---

## 作者：George_Plover (赞：7)

## <center>【CF963D】Frequency of String （AC自动机）</center>

​		前段时间重新学习了AC自动机（以前听同学讲，只写了个假模板，就再也没接触过了），练了几道题目，算是掌握了AC自动机的基础了。并且写了一个自己能用的模板。

​		昨天刷了这道题，打算写一个题解。

------

##### 【题目描述】

​		给出一个字符串$s$ $(|s|\leq 10^5)$，有$n$ $(n\leq10^5)$个询问，第$i$个询问包含一个整数$k_i$ $(1 \leq k_i\leq |s|)$和一个字符串$m_i$ $(\sum m_i \leq 10^5)$。对于每个询问，要求找到一个字符串$t$，满足$t$是$s$的字串，且在字符串$t$中，串$m_i$的全匹配恰好出现了$k_i$次。你只需要对每个询问输出对应字符串$t$的最小长度就可以了。如果没有满足要求的字符串$t$，请输出$-1$。（保证$m_i$互不相同）

​		时限 1.5s  空限 500Mb

------

##### 【AC自动机】		

​		先来拆分一下AC自动机，整理一些特性：字典树，fail值，fail树



​		**字典树：**

​		AC自动机是建立在一棵字典树上的。字典树上的每个节点都是一个状态，代表着一个前缀（即从根节点一直到达该节点的路径组成的字符串，这一定是字典树中某些单词的前缀）。



​		**fail值：**

​		每个节点都具有一个fail值。fail值具有重要意义。我们已经知道了，每个节点代表一个前缀，也就是一个字符串。而节点的fail值是另一个节点的编号，也就是说，指向了另一个前缀，也就是另一个字符串。不妨令当前节点代表的字符串为$s$，其fail指向节点代表的字符串为$t$，根据AC自动机的性质，这两个字符串满足：

​		（1）$t$是$s$的后缀。

​		（2）$|t|<|s|$。

​		（3）在该自动机中所有满足前两个性质字符串中，$|t|$是最大的。

​		

​		**匹配过程：**

​		匹配时，从根节点开始，根据输入的字符串的字符顺序，在AC自动机中匹配，遇到无法匹配时，则将当前状态移动到fail值所指状态上，继续尝试匹配，重复这个过程直到匹配成功（在我的模板中，根节点是一个万配点，所以一定会匹配成功）。



​		**fail树：**

​		由于根的fail值是空，其他每个点必有一个fail值，因此把fail值视为一条边，AC自动机上的点可以根据fail值构造出一棵树，称为fail树。fail树意义重大，如果没有考虑到它的特性，相当于是学了假的AC自动机。

​		fail树上祖先和子孙的关系：祖先节点代表的串，是子孙节点代表的串的一个真后缀，AC自动机的使用大多基于这个特性。

------

##### 参考解题思路：

​		如果我们能够知道每个串$m_i$在$s$中完成全匹配的结束位置，通过链式结构将这些位置储存起来，就能够通过一遍扫描求出$t$的最短长度。

> 比如，$m_i$完成全匹配的位置为：2,4,7,8,9,10，且$k_i=3$
>
> 那么我们扫描过程中发现“7，8，9”这三个连续位置的长度最小，由此得到$t$的最短长度$|t|_{min}=9-7+|m_i|$

​		那么我们想到一个朴素直接的方法，用AC自动机跑出这些全匹配的位置。

​		首先，根据所有的串$m_i$建立AC自动机，然后拿串$s$去匹配，匹配过程中会经历$|s|$个状态。当某个状态匹配成功时，其在fail树上的所有祖先节点也将匹配成功。但注意，并不是所有祖先节点都对应于某个串$m_i$，有的节点只代表某个前缀。我们可以遍历当前状态以及所有祖先状态，如果遍历到的这个状态对应于某个串$m_i$，我们就跑出了这个串的一个全匹配的位置，于是记录下来。

​		这个算法能够不遗漏的找出每个$m_i$的全匹配位置，正确性有保证，但是如何保证效率呢？

​		注意，fail树上只有部分节点是对应于某个串$m_i$的，我们称这些节点是有效的，其余节点是无效的，如果我们在fail树上提前dfs一遍，就能预处理出每个点最近的一个有效祖先，从而跳过那些无效祖先，节省时间。

​		实际上加上这个优化，就可以通过了。但是我们需要明白为什么。

​		该算法时间复杂性$\rm O(n\sqrt n)$，下面是分析：



​		**结论**: fail树上，任何一个节点的有效祖先数量最大为$\rm O( \sqrt{\sum m_i})$

​		**证明**：假设某个节点的有效祖先数量为$k$个，那么，这些祖先节点代表着$k$个字符串，而根据fail树的性质，每个字符串的长度都不相等，因此这些有效串的长度之和的下界为$\frac{k(k+1)}{2}$。根据题意，所有有效串的和$\sum m_i\geq \frac{k(k+1)}{2}$，因此$k$的数量最大为$\rm O(\sqrt {\sum m_i})$

​		

​		所以说，在$|s|$个状态中，每个状态的有效祖先数目最大为$\rm O(\sqrt {\sum m_i})$，因此，所有目标串的全匹配的位置总数目最大为$\rm O(|s|\sqrt {\sum m_i})$，因为$|s|,\sum m_i$和$n$同数量级，所以全匹配位置总数目最大为$\rm O(n\sqrt n)$。

​		

​		最后扫描链式结构复杂性也是$\rm O(n\sqrt n)$，总复杂性$\rm O(n\sqrt n)$。



​		这道题还有一个很坑的地方，因为$n\leq 10^5$，所以$n\sqrt n$可达$3\times 10^7$，如果你使用链表来扫描，可能会被卡常数。

​		为什么呢？遍历链式结构有什么慢的呢？手写链表还会被卡常吗？然而亲身试法，的确TLE了。

​		链表结构的遍历常数来自于寻址，在遍历的过程中，以不确定的顺序去访问大量的地址，这是非常缓慢的。我们需要使用**vector**。vector中遍历的地址是连续的，在访问同样数量的地址的情况下，会比链表快很多。

​		但是vector插入慢啊！（是的没错，但是能过这道题……可能和数据特征有关？）

​		看来这道题的瓶颈应该在于最后的遍历。

​		最后这个点很有意思，但是我了解的并不多，还有待深入挖掘。

-------

##### 【参考代码】

```cpp
#define George_Plover
#include <list>
#include <queue>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <algorithm>
#define MAXM 100101
#define MAXN 100101
#define MAXL (100101*430)
#define LL long long
#define RG register
using namespace std;
vector<int>vec[MAXN];
struct ACM{
    const static int None = 0;
    int fail[MAXM];
    int siz,root;
    queue<int>q;
    struct node{
        int son[26];
        int cnt;
        void init(){
            cnt=0;memset(son,0,sizeof(son));
        }
    }tr[MAXM];
    struct Fail_Tree{
        int tot,pre[MAXM],to[MAXM],lin[MAXM],top[MAXM];
        bool vis[MAXM];
        void init()
        {
            tot=0;
            memset(pre,0,sizeof(pre));
            memset(vis,0,sizeof(vis));
        }
        void add(int x,int y)
        {
            tot++;lin[tot]=pre[x];pre[x]=tot;to[tot]=y;
        }
        void dfs(int x,int fa)
        {
            if(vis[fa])
                top[x]=fa;
            else
                top[x]=top[fa];
            for(int i=pre[x];i;i=lin[i])
            {
                int v=to[i];
                dfs(v,x);
            }
        }
    }tree;
    void init()
    {
        for(int i=1;i<=siz;i++)
            tr[i].init();
        tree.init();
        siz=1;root=1;fail[root]=None;tree.top[None]=None;
        for(int i=0;i<26;i++)
            tr[None].son[i]=root;
    }
    ACM(){init();}
    void add(char *s)
    {
        static int CNT=0;
        int tmp=root;
        for(int i=0;s[i];i++)
        {
            if(!tr[tmp].son[s[i]-'a'])
                tr[tmp].son[s[i]-'a']=++siz;
            tmp=tr[tmp].son[s[i]-'a'];
        }
        tr[tmp].cnt=++CNT;
        tree.vis[tmp]=1;
    }
    void get_fail()
    {
        q.push(root);
        while(!q.empty())
        {
            int u=q.front();q.pop();
            for(int i=0;i<26;i++)
            {
                int v=tr[u].son[i];
                if(!v)
                    continue;
                int tmp=fail[u];
                while(tmp!=None&&!tr[tmp].son[i])
                    tmp=fail[tmp];
                fail[v]=tr[tmp].son[i];
                tree.add(tr[tmp].son[i], v);
                q.push(v);
            }
        }
        tree.dfs(root,None);
    }
    void work(char *s)
    {
        int tmp=root;
        for(int i=0;s[i];i++)
        {
            while(tmp!=None&&!tr[tmp].son[s[i]-'a'])
                tmp=fail[tmp];
            tmp=tr[tmp].son[s[i]-'a'];
            int p=tmp;
            
            while(p!=None)
            {
                if(tree.vis[p]){
                    vec[tr[p].cnt].push_back(i);
                }
                p=tree.top[p];
            }
             
        }
    }
}acm;
int n,a[MAXN],len[MAXN];
char T[MAXM],S[MAXM];

int main()
{
    scanf("%s",T);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%s",&a[i],S);
        acm.add(S);
        len[i]=(int)strlen(S);
    }
    acm.get_fail();
    acm.work(T);
    for(int i=1;i<=n;i++)
    {
        int ans=MAXL;
        if(vec[i].size()<a[i])
            printf("-1\n");
        else
        {
            for(int j=0;j+a[i]-1<vec[i].size();j++)
                ans=min(ans,vec[i][j+a[i]-1]-vec[i][j]+len[i]);
            printf("%d\n",ans);
        }
    }
    return 0;
}
```






		















​		

---

## 作者：CDFLS_mao_zx (赞：6)

## $\text{CF963D}$

### 思路：

多模式匹配，看到这个应该先想一想单模式怎么做。

$\text{KMP}$ 的过程中，记录一下每一次出现的起始位置，第 $x$ 次出现的时候，假设末尾位置为 $i$，那么答案向 $i-pos[x-k]+1$ 取 $\text{min}$ ，因为我们需要让子串长度尽可能小，所以一定让它出现的次数最小。

考虑拓展到多模式的情况，在已经建立的 $AC$ 自动机上跑，跑到一个节点则检查哪些串已经出现过了，暴力跳 $fail$ 树，像单模式匹配一样处理答案 。这样的复杂度是 $O(n^2)$ 的，因为 $fail$ 树的树高是 $O(n)$ 的。

我们希望降低 $fail$ 树的树高。

$fail$ 树树高严格小于最长串的长度。因为保证了总长度，这个时候我们应该考虑进行根号分治。

对于询问长度大于 $\sqrt n$ 的 $\sqrt{n}$ 个串，我们暴力进行单模式匹配，复杂度 $O(n * \sqrt{n})$。

对于其它的串，我们将它们扔进 $\text{AC}$ 自动机里暴力跑就可以了，因为树高不超过 $\sqrt{n}$ 所以每一次访问的复杂度是 $O(\sqrt{n})$ 的，总复杂度 $O(n * \sqrt{n})$ 。可以通过本题。

使用 $\text{vector}$ 记录每个串的出现位置，空间是 $O(n * \sqrt{n})$ 的，没有问题。

注意题目保证了不存在相同的串，所以没必要特殊处理。**AC自动机的题目往往需要特殊处理相同的串。**

### 代码实现和细节

这种写法的代码相当简洁。

其实没什么好说的，看代码吧。

```cpp
#include<bits/stdc++.h>
#define y1 y3647
#define LL long long
#define next nxt
using namespace std;
inline void read(int &x)
{
	x=0;int f=1;char ch=getchar();
	while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
	if(ch=='-'){f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	x*=f;
}
int i,j,k,m,n,s,t,l,cnt,now;
const int N=1e5+10,P=300;
int son[N][26],fail[N],len[N],ans[N],rak[N],next[N],le[N];
int op[N],pos[N];
char ch[N],c[N];
queue<int> q;
vector<int> lst[N];
void add(int x,int u)
{
	if(x==l+1)
	{
		rak[u]=i;
		return;
	}
	if(son[u][ch[x]-'a']==0)
	son[u][ch[x]-'a']=++t;
	add(x+1,son[u][ch[x]-'a']);
}
void build()
{
	for(i=0;i<26;i++)
	if(son[0][i])
	q.push(son[0][i]);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(i=0;i<26;i++)
		if(son[u][i])
		fail[son[u][i]]=son[fail[u]][i],q.push(son[u][i]);
		else
		son[u][i]=son[fail[u]][i];
	}
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//freopen(".ans","w",stdout);
	memset(ans,1,sizeof(ans));
	scanf("%s",c+1);
	n=strlen(c+1);
	read(m);
	for(i=1;i<=m;i++)
	{	
		read(op[i]);
		scanf("%s",ch+1);
		le[i]=l=strlen(ch+1);
		if(l<P)
		add(1,0);
		else
		{
			memset(next,0,sizeof(next));//记得清空
			k=-1,next[0]=-1;
			for(j=1;j<=l;j++)
			{
				while(k!=-1&&ch[k+1]!=ch[j])
				k=next[k];
				k++;
				next[j]=k;
			}
			cnt=k=0;
			for(j=1;j<=n;j++)
			{
				while(k!=-1&&ch[k+1]!=c[j])
				k=next[k];
				k++;
				if(k==l)
				{
					pos[++cnt]=j-l+1;
					if(cnt>=op[i])
					ans[i]=min(ans[i],j-pos[cnt-op[i]+1]+1);
				}
			}
		}
	}
	build(),now=0;
	for(i=1;i<=n;i++)
	{
		now=son[now][c[i]-'a'];
		int u=now;
		while(u)
		{
			if(rak[u])
			{
				int to=rak[u];//你需要的并不是当前节点的标号，而是当前节点到底是哪个询问
				lst[to].push_back(i-le[to]+1);
				if(lst[to].size()>=op[to])
				ans[to]=min(ans[to],i-lst[to][lst[to].size()-op[to]]+1);
			}
			u=fail[u];
		}
	}
	for(i=1;i<=m;i++)
	{
		if(ans[i]<1e6)//-1
		printf("%d\n",ans[i]);
		else
		puts("-1");
	}
	return 0;
}
```



---

## 作者：L_G_J (赞：5)

需要发现一个重要性质：对于 $n$ 个互不相同的模式串 $t_i$ ，他们在文本串 $s$ 中的出现次数之和（即 endpos 大小之和）是 $O(|s|\sqrt {\sum |t_i|})$  的。

证明考虑把模式串按长度分类，那么对于长度为 $l_i$ 的一些模式串，他们在 $s$ 中出现的次数之和至多是 $|s|-l_i+1$ 。由于 $\sum l_i \leq \sum |t_i|$ 且 $l_i$ 互不相同，不同的 $l_i$ 至多有 $\sqrt{\sum{|t_i|}}$ 种，所以总的个数是 $O(|s|\sqrt {\sum |t_i|})$。

所以我们可以对于每个模式串 $t_i$ 维护出它在 $s$ 中的 endpos 集合大小。可以 SAM+线段树合并，这里使用类似于 [CF914F](https://www.luogu.com.cn/problem/CF914F) 的手法利用 `bitset` 维护 endpos 集合即可。即对于字符集中的每一个字母用 `bitset` 维护出它在 $s$ 中的出现位置集合。对于一个模式串，维护一个初始全为 1 的 `bitset`，依次处理模式串中的字符，通过简单的左移或右移减小这个 `bitset` 的规模，从而得到最后模式串的所有 endpos，复杂度是 $O(\dfrac {|s|\sum |t _i| }{ \omega})$。

这样我们获得了一个用 `bitset` 维护的 endpos 集合，那么直接遍历 `bitset` 中的每一个 1，对于连续的 $k$ 个 1 代表的区间长度求最小值即可，遍历每个 1 可以使用函数 `_Find_first()` 以及 `_Find_next(x)` ，其作用分别为返回 `bitset` 中的第一个 1 的位置（以数值表示）以及当前的下一个 1 的位置，这样就可以在 $O(\dfrac {n |s|}{ \omega}+|s|\sqrt {\sum |t_i|})$ 的复杂度内完成统计。

总复杂度 $O(\dfrac {|s|(\sum |t _i|+n) }{ \omega} + |s|\sqrt {\sum |t_i|})$。

**代码**

```cpp
const int N=2e5+50;
int n,m,q,k;
vector<int> vec;
bitset<N> bit[26],cur;
char s[N],t[N];
int main(void)
{
	scanf("%s",s+1),n=strlen(s+1),q=read();
	fr(i,0,25) bit[i].reset();
	fr(i,1,n) bit[s[i]-'a'].flip(i);
	fr(i,1,q)
	{
		k=read(),scanf("%s",t+1),m=strlen(t+1),cur.set(),vec.clear();
		fr(j,1,m) cur&=(bit[t[j]-'a']<<(m-j));
		for(int pos=cur._Find_first();pos!=N;pos=cur._Find_next(pos)) vec.emplace_back(pos);
		int sz=vec.size(),ans=inf;
		fr(j,k-1,sz-1) ans=min(ans,vec[j]-vec[j-k+1]+m);
		(ans==inf)?writeln(-1):writeln(ans); 
	}
	return 0;
}
```


---

## 作者：Freopen (赞：5)

首先有个结论：$m$个不同的（长度之和为$n$的）串在$S(|S| =n)$中的$endpos$集合大小之和为$O(n \sqrt n)$

证明：

对于所有长度都为$k$的串他们的$right$集合大小之和为$O(n)$。
串不相同代表着只有$O(\sqrt n)$种不同的长度。

如果我们得到了一个询问的$m$的$endpos$集合，只需要将这个集合排好序，中间连续任意的$k$个再往左扩展$|m|$的长度即为我们可能需要的$t$，求$|t|$的最小值可以$O(|endpos|)$计算，因为上面的结论，这部分复杂度为$O(n \sqrt n)$

关于求这$n$个串的$endpos$集合有三种思路：

1.后缀自动机上线段树合并，但是这样复杂度会变成$O(n \sqrt n \log n + n \log n)$，写$O(n \log ^2n)$的启发式合并就还是$O(n \sqrt n)$的。

2.离线建出$m_i$的$AC$自动机，拿$s$在自动机上跑，对于 $s$的前缀所在的节点我们需要更新所有它的后缀的$m$的$right$集合，新开一个数组$fa$表示沿着$fail$链跑下一个是$m$中的一个的节点，因为$right$集合大小是$O(n \sqrt n)$，每次暴力爬$fa$也是$O(n \sqrt n)$的。

3.[众所周知，$bitset$可以在$O(\frac{ST}{32})$的复杂度内计算出$T$在$S$中出现的$endpos$集合。](https://www.luogu.com.cn/problem/CF914F)

代码：
```cpp
#include<bits/stdc++.h>
#define maxn 100005
#define rep(i,j,k) for(int i=(j),LIM=(k);i<=LIM;i++)
using namespace std;

char s[maxn],m[maxn];
int n,q,K;
bitset<maxn>C[26];

int main(){
	scanf("%s",s);
	n = strlen(s);
	rep(i,0,n-1) C[s[i] - 'a'][i] = 1;
	scanf("%d",&q);
	for(;q--;){
		scanf("%d%s",&K,m);
		int L = strlen(m);
		static bitset<maxn>ans;
		ans.set();
		rep(i,0,L-1) ans &= C[m[i] - 'a'] >> i;
		vector<int>a;
		for(int i=ans._Find_first();i!=ans.size();i=ans._Find_next(i))
			a.push_back(i);
		if(a.size() < K) puts("-1");
		else{
			int ret = 0x3f3f3f3f;
			rep(i,K-1,a.size()-1) ret = min(ret , a[i] - a[i-K+1] + L); 
			printf("%d\n",ret);
		}
	}
}
```



---

## 作者：Mirasycle (赞：4)

观察到时限宽裕，我们可以直接 bitset 乱搞过去（从 Alex_Wei 大佬博客学的）。

具体来说，我们可以通过 bitset 移位来维护一个模式串在文本串中终止位置的集合，然后暴力访问即可。

这里访问所有的 $1$ 需要用到两个函数，_Find_first() 和 _Find_next()，功能分别是寻找第一个 $1$ 和下一个 $1$。这样我们就可以实现查找所有出现位置的功能了。然后记录下每个出现位置，更新答案即可。

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<bitset>
using namespace std;
const int maxn=1e5+10;
const int maxs=30;
char s[maxn],t[maxn];
bitset<maxn> c[maxs],b;
int pos[maxn],n,q,k,m,tot,ans;
int main(){
	cin>>(s+1)>>q; n=strlen(s+1);
	for(int i=1;i<=n;i++) c[s[i]-'a'][i]=1;
	for(int i=1;i<=q;i++){
		cin>>k>>(t+1);  m=strlen(t+1); tot=0; ans=1e9; b.set();
		for(int i=1;i<=m;i++) b=b&(c[t[i]-'a']<<(m-i));
		for(int it=b._Find_first();it!=maxn;it=b._Find_next(it)) pos[++tot]=it;
		for(int i=k;i<=tot;i++) ans=min(ans,pos[i]-pos[i-k+1]+m);
		ans=(ans==1e9)?-1:ans; 
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：lfxxx (赞：1)

下文视字符串长度之和为 $n$，考虑到不同模式串在同一个文本串中的出现次数之和是 $O(n \sqrt n)$ 的。

考虑把所有模式串按照长度分类，长度相同时由于互不相同，所以在 $O(n)$ 个出现位置上至多一个字符串被匹配，又因为不同长度之和为 $n$，所以长度种类数只有 $O(\sqrt n)$ 种，因此出现次数之和为 $O(n \sqrt n)$ 次。

考虑将文本串和询问串丢到广义 SAM 上，那么出现位置即为 $endpos$ 集合，考虑在 parent 树上进行树上启发式合并维护出一个点的 $endpos$ 有序集合，查询时直接枚举集合中所有排名距离为 $k$ 的出现位置之差的最小值，由于出现次数之和为 $O(n \sqrt n)$ 所以枚举的复杂度也是 $O(n \sqrt n)$。

算上树上启发式合并，复杂度一共是 $O(n \log^2 n + n \sqrt n)$。

由于常数有点差所以使用了火车头。

```cpp
#include<bits/stdc++.h>
#pragma GCC target("avx")
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
using namespace std;
const int maxn = 4e5+114;
struct SAM{
	int len,fa;
	int son[26];
}nd[maxn]; 
int tot,lst,q;
int val[maxn];
void ins(char c){
    if(nd[lst].son[c-'a']!=0){
    	int q=nd[lst].son[c-'a'],v=lst;
        if(nd[q].len==nd[v].len+1){
        	lst=q;
        	return ;	
		}
        int nq=++tot;
        lst=nq;
        nd[nq]=nd[q];
        nd[nq].len=nd[v].len+1;
        nd[q].fa=nq;
        while(v!=0&&nd[v].son[c-'a']==q) nd[v].son[c-'a']=nq,v=nd[v].fa;
        return ;
    }
    int u=++tot,v=lst;
	nd[u].len=nd[lst].len+1;
  	lst=u;
	while(v!=0&&nd[v].son[c-'a']==0) nd[v].son[c-'a']=u,v=nd[v].fa;
	if(v==0){
        nd[u].fa=1;
        return ;
    }else{
        int q=nd[v].son[c-'a'];
        if(nd[v].len+1==nd[q].len){
            nd[u].fa=q;
            return ;
        }else{
            int nq=++tot;
            nd[nq]=nd[q];
            nd[nq].len=nd[v].len+1;
            nd[u].fa=nq;
            nd[q].fa=nq;
            while(v!=0&&nd[v].son[c-'a']==q) nd[v].son[c-'a']=nq,v=nd[v].fa;
            return ;
        }
    }
    return ;
}
vector<int> E[maxn];
void init(){
    for(int i=2;i<=tot;i++) E[nd[i].fa].push_back(i);
    return ;
}
int answer[maxn];
struct Query{
    int id,k,len;
    Query(int ID=0,int K=0,int LEN=0){
        id=ID,k=K,len=LEN;
    }
};
vector<Query> ask[maxn];
set<int> S;
int sz[maxn],son[maxn],L[maxn],R[maxn],dfncnt,node[maxn];
void dfs1(int u){
    sz[u]=1;
    for(int v:E[u]){
        dfs1(v);
        sz[u]+=sz[v];
        if(sz[u]>sz[son[u]]) son[u]=v;
    }
    return ;
}
void dfs2(int u){
    L[u]=++dfncnt;
    node[dfncnt]=u;
    if(son[u]!=0) dfs2(son[u]);
    for(int v:E[u]){
        if(v!=son[u]) dfs2(v);
    }
    R[u]=dfncnt;
    return ;
}
void dfs3(int u,bool keep){
    for(int v:E[u]){
        if(v!=son[u]) dfs3(v,false);
    }
    if(son[u]!=0) dfs3(son[u],true);
    for(int v:E[u]){
        if(v!=son[u]){
            for(int i=L[v];i<=R[v];i++){
                if(val[node[i]]!=0) S.insert(val[node[i]]);
            }
        }
    }
    if(val[u]!=0) S.insert(val[u]);
    for(Query now:ask[u]){
        vector<int> vec;
        for(int x:S) vec.push_back(x);
        if(vec.size()<now.k) answer[now.id]=-1;
        else{
            answer[now.id]=INT_MAX;
            for(int i=0;i+now.k-1<vec.size();i++){
                answer[now.id]=min(answer[now.id],vec[i+now.k-1]-vec[i]+1+(now.len-1));
            }
        }
    }
    if(keep==false){
        for(int i=L[u];i<=R[u];i++) if(val[node[i]]!=0) S.erase(val[node[i]]);
    }
    return ;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    lst=++tot;
    string s;
    cin>>s;
    int len=s.size();
    lst=1;
    for(int i=1;i<=len;i++){
        ins(s[i-1]);
        val[lst]=i;
    }
    cin>>q;
    for(int i=1;i<=q;i++){
        int k;
        string m;
        cin>>k>>m;
        lst=1;
        for(char x:m) ins(x);
        ask[lst].push_back(Query(i,k,m.size()));
    }
    init();
    dfs1(1);
    dfs2(1);
    dfs3(1,false);
    for(int i=1;i<=q;i++) cout<<answer[i]<<'\n';
    return 0;
}
```


---

## 作者：MiniLong (赞：1)

考虑单次询问，即给出 $s,k,m$，要求 $s$ 的子串最短 $t$ 的长度使得 $t$ 中至少出现了 $k$ 次 $m$。

这个东西是很平凡的，哈希一下找出每个 $t$ 在 $s$ 中的位置然后对每 $k$ 个相邻出现位置的下标差取个最小就行。

然后再想多次询问，因为字符串总和是 $\sum |m_i| = 10^5$，可以考虑根号分治。

设 $m$ 为当前询问的字符串和阈值 $B$。

- 若 $|m| > B$，这样的询问一共之后出现 $O(\dfrac{\sum |m_i|}{B})$ 次，每次可以暴力 $O(|s| +|m|)$ 使用上述方法解决。

- 若 $|m| \le B$，可以将 $m$ 插入字典树中，记录当前的 $k$。将所有这类情况插入完后，可以对 $s$ 的每个长度小于等于 $B$ 的子串找到字典树上对应的询问，并且将这个子串的结尾处在 $s$ 中下标加到对应询问的出现位置集合中，再用上述方法解决即可。时间复杂度 $O(|s| B)$。

总复杂度为 $O(\dfrac{(\sum |m_i|) \times(|s|+ |m|)}{B} + |s|B)$，可以通过。

---

## 作者：int_R (赞：0)

[Frequency of String](https://www.luogu.com.cn/problem/CF963D)

[更好的阅读体验](https://www.cnblogs.com/int-R/p/CF963D.html)

莪怺逺禧歡仳特噻特。

记每次询问中的字符串为 $t_i$。约定字符串下标从 $1$ 开始。

发现 $\sum |t_i|$ 与 $|s|$ 和 $q$ 同阶，考虑使用 `bitset` 进行字符串匹配。

我们对于每一种字符 $c$ 开一个 `bitset` $b_c$，然后预处理将 $b_{s_i}$ 的第 $i$ 位设置为 $1$，也就是对于每种字符记录出它在 $s$ 中所有的出现位置。

对于一个字符串 $t$，与 $s$ 进行字符串匹配。我们开一个记录答案的 `bitset` $ans$，意义是每一个为 $1$ 的位都是 $t$ 在 $s$ 中的**起始位置**(有些写法是结束位置)。初始时将 $ans$ 每一位都赋值为 $1$。

$s:abcdabacd$

$t:abcd$

$ans:1\ 1\ 1\ 1\ 1\ 1\ 1\ 1\ 1$

我们遍历 $t$ 的每一位，使 $ans\gets ans\operatorname{bitand} (b_{y_i}\operatorname{>>}(i-1))$（字符串向左移，但是 `bitset` 中是右移）。

$s:\ \ \ \ {\color{red} a}\ b\ c\ d\ {\color{red} a}\ b\ {\color{red} a}\ c\ d$

$ans:1\ 0\ 0\ 0\ 1\ 0\ 1\ 0\ 0$

$s:\ \ \ \ {\color{red} b}\ c\ d\ a\ {\color{red} b}\ a\ c\ d$

$ans:1\ 0\ 0\ 0\ 1\ 0\ 0\ 0\ 0$

$\cdots $

最后得到的就是所有起始位置，匹配的时间复杂度是 $O(\dfrac{|s|\sum |t_i|}{\omega})$。

考虑怎样快速统计答案，直接遍历显然单次 $O(|s|)$，可以通过 `bitset` 的函数 `_Find_first()` 和 `_Find_next(x)` 找到 `bitset` 中第一个为 $1$ 的位置和 $x$ 之后第一个为 $1$ 的位置。就可以直接遍历所有为 $1$ 的位置。直接统计就可以了。

为什么这样的时间复杂度是正确的，因为 $t_i$ 互不相同，所以所有 $t_i$ 在 $s$ 中总出现次数不超过 $|s|\sqrt{\sum |t_i|}$。所以这里时间复杂度是 $O(|s|\sqrt{\sum |t_i|})$。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string>
#include<bitset>
using namespace std;
const int MAXN=1e5+10;
string s,t;int n,q,k,ANS;
bitset <MAXN> b[300],ans;
int main()
{
#ifdef ONLINE_JUDGE
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
#endif
    cin>>s>>q;n=s.size();s=' '+s;
    for(register int i=1;i<=n;++i) b[s[i]].set(i);
    for(register int i=1;i<=q;++i)
    {
        cin>>k>>t;ans.set(),ANS=MAXN;
        for(register int i=0;i<t.size();++i) ans&=b[t[i]]>>i;
        int l=ans._Find_first(),r=l;
        for(register int i=1;r<=n&&i<k;++i) r=ans._Find_next(r);
        while(r<=n)
        {
            ANS=min(ANS,r+(int)t.size()-l);
            l=ans._Find_next(l),r=ans._Find_next(r);
        }
        cout<<(ANS==MAXN?-1:ANS)<<'\n';
    }
    return 0;
}
```

---

## 作者：王熙文 (赞：0)

## 题解

（注：文中默认 $|s|,n,\sum|m_i|$ 为一个量级，均表示为 $n$）

首先考虑如果只有一次询问怎么做。

可以在 $s$ 串中找到这一次询问的串的若干出现位置，排序之后答案即为所有连续 $k$ 个位置组成的字符串的长度。

有一个结论：在这道题当中所有询问出现位置的数量总和为 $\mathcal O(n\sqrt{n})$ 量级。

证明：考虑使用根号分治的思想。

* 当询问的字符串长度 $|m_i| \le \sqrt{n}$ 时，考虑每一个询问的字符串匹配上的位置一定是 $s$ 的某个前缀的长度为 $|m_i|$ 的后缀。整体来看，一共有 $n$ 个前缀，每个前缀的后缀个数最多为 $\sqrt{n}$ 个（因为 $|m_i| \le \sqrt{n}$），所以一共匹配上的位置共有 $\mathcal O(n\sqrt{n})$ 个。

* 当询问的字符串长度 $|m_i| > \sqrt{n}$ 时，因为所有询问的字符串长度总和为 $n$，所以一共最多会有 $\mathcal O(\sqrt{n})$ 个这样的串，每个串最差匹配 $\mathcal O(n)$ 次，一共匹配上的位置也只有 $\mathcal O(n\sqrt{n})$ 个。

那么此时就有了一个根号分治的方法：

* 对于每一个 $|m_i| > \sqrt{n}$ 的查询暴力用哈希匹配求出答案。

* 对于所有 $|m_i| \le \sqrt{n}$ 的字符串构建 ACAM（AC 自动机），因为 $|m_i| \le \sqrt{n}$，所以树高 $\le \sqrt{n}$，每一次跳 fail 的时候最多会跳 $\mathcal O(\sqrt{n})$ 次，暴力跳即可。

但是可以发现这样写太麻烦了，有没有好写的做法呢？

如果我们对所有串都建 ACAM，但是每一次跳 fail 都会恰好更新答案，则时间复杂度就会降为所有询问出现位置的数量总和 $\mathcal O(n\sqrt{n})$。

考虑在跳 fail 的时候下手脚：我们在建树的时候记录一个 $lst$ 数组，$lst_i$ 表示跳 fail 的时候在向根的路径上第一次遇到需要更新字符串的地方。如果求出来了这个数组，则每一次跳 fail 的时候就不再是 `j=fail[j]`，而是 `j=lst[j]` 了。显然这个数组可以在求 fail 的时候就求出来：

* 如果当前指向的 fail 的位置就有字符串，需要更新答案，则 $lst_i = fail_i$。

* 如果当前指向的 fail 的位置没有字符串，则 $lst_i=lst_{fail_i}$。

求出来这个 $lst$ 数组后，时间复杂度便降下来了。

具体细节参考代码。

## 参考代码

```cpp
// 以下是写代码前写的注释，可以参考
// 考虑单次询问，可以找到查询的字符串在原串的几个位置，排序后答案即为连续的 k 个位置的右-左最小
// 口胡可知，若干次询问的位置数量总和 <=nsqrt(n)，具体方法可以用根号分治的思想证明
// 证明：当查询的字符串长度 <=sqrt(n) 的时候，我们将这些串一起匹配。这些串的位置肯定是原串一个前缀的后缀
// 前缀的个数有 n 个，后缀的个数有 O(sqrt(n)) 个，又因为每个串互不相同，所以最差把前缀的 O(sqrt(n)) 个后缀匹配满，共有 O(nsqrt(n)) 个
// 当查询的字符串长度 >sqrt(n) 的时候，通过查询的字符串长度总和可知这样的字符串 <=sqrt(n) 个，暴力对于每个串哈希或者 KMP 即可
// 于是可以使用根号分治做，<=sqrt(n) 的建 ACAM，>sqrt(n) 的暴力
// 但是如果能快速找到答案，就不需要根号分治（因为答案总数已经证明了最多 O(nsqrt(n)) 个
// 考虑对所有查询的字符串建 ACAM，记录 lst 表示对于每一个节点 fail 向根的路径上上一次有字符串的地方的位置，可以在建 fail 边的时候求出
// 那么每一次跳就都能找到需要更新答案的地方，即可 O(nsqrt(n)) 完成
#include<bits/stdc++.h>
using namespace std;

int m;

string s;

struct query
{
	string t;
	int k;
} q[100010];

int now=0,son[100010][26],fail[100010],lst[100010],qwz[100010]; // qwz[i] 表示当前位置是哪个查询的字符串（如果没有，=0）

void insert(string t,int id)
{
	int wz=0;
	for(int i=0; i<t.size(); ++i)
	{
		if(!son[wz][t[i]-'a']) son[wz][t[i]-'a']=++now;
		wz=son[wz][t[i]-'a'];
	}
	qwz[wz]=id;
}

queue<int> qq;

void get_fail()
{
	for(int i=0; i<26; ++i)
	{
		if(son[0][i])
		{
			qq.push(son[0][i]);
			fail[son[0][i]]=0;
		}
	}
	while(!qq.empty())
	{
		int frn=qq.front(); qq.pop();
		for(int i=0; i<26; ++i)
		{
			int now=son[frn][i];
			if(now)
			{
				qq.push(now);
				fail[now]=son[fail[frn]][i];
				lst[now]=qwz[fail[now]]?fail[now]:lst[fail[now]]; // 这里是求 lst 的地方，如果 qwz[fail[now]]!=0 说明那里需要更新 vector
			}
			else son[frn][i]=son[fail[frn]][i];
		}
	}
}

vector<int> twz[100010]; // 记录每个查询的匹配位置右端点

int main()
{
	cin>>s;
	cin>>m;
	for(int i=1; i<=m; ++i)
	{
		cin>>q[i].k>>q[i].t;
		insert(q[i].t,i);
	}
	get_fail();
	int wz=0;
	for(int i=0; i<s.size(); ++i)
	{
		wz=son[wz][s[i]-'a'];
		for(int j=wz; j; j=lst[j])
		{
			if(qwz[j]) twz[qwz[j]].push_back(i);
		}
	}
	for(int i=1; i<=m; ++i)
	{
		int ans=1e9;
		for(int j=0; j<(int)twz[i].size()-q[i].k+1; ++j)
		{
			ans=min(ans,twz[i][j+q[i].k-1]-twz[i][j]+(int)q[i].t.size());
		}
		cout<<(ans==1e9?-1:ans)<<'\n';
	}
	return 0;
}
```

---

## 作者：神之右大臣 (赞：0)

我看到了有一篇AC自动机的题解了
但是字符串题不用SAM真的好吗？明明SAM那么简单的说。

首先，你可以建出SAM，并预处理每个节点的endpos集合。
（这个部分都是模板，就不多说了）

然后把需要用到的关键点的endpos集合排序。
这里关键点指的是在某个询问中endpos集合包含那个串的点。

我们知道选取的一段子串一定是在endpos集合中连续的一段。否则长度不是最优。因此枚举选取的段的左端点。区间长度便是询问中给的出现的次数，所有区间的答案取个min就好了。

很简单吧，~~比AC自动机好想好写多了~~。


```cpp
#include <bits/stdc++.h>
#define inc(i,a,b) for(register int i=a;i<=b;i++)
using namespace std;
class node{
	public:
	int ch[27],len;
	int link;
}sam[400010];
int last=1,sizze=1,judge[400010];
void add(int to,int pos){
	int cur=++sizze,u=last; judge[cur]=pos;
	sam[cur].len=sam[u].len+1;
	for(;u&&!sam[u].ch[to];u=sam[u].link) sam[u].ch[to]=cur;
	if(!u) sam[cur].link=1;
	else{
		int q=sam[u].ch[to];
		if(sam[q].len==sam[u].len+1) sam[cur].link=q;
		else{
			int neww=++sizze;
			sam[neww]=sam[q];
			sam[neww].len=sam[u].len+1;
			for(;u&&sam[u].ch[to]==q;u=sam[u].link) sam[u].ch[to]=neww;
			sam[cur].link=neww; sam[q].link=neww;
		}
	}
	last=cur;
}
char s[100010],t[100010];
int n,q;
int head[400010],cnt;
class littlestar{
	public:
	int to,nxt;
	void add(int u,int v){
		to=v; nxt=head[u];
		head[u]=cnt;
	}
}star[400010];
int pos[400010],tot;
void dfs(int u){
	if(judge[u]) pos[++tot]=judge[u];
	for(int i=head[u];i;i=star[i].nxt){
		int v=star[i].to;
		dfs(v);
	}
}
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	inc(i,1,n) add(s[i]-'a',i);
	inc(i,2,sizze) star[++cnt].add(sam[i].link,i);
	cin>>q;
	inc(i,1,q){
		tot=0;
		int x; scanf("%d",&x);
		scanf("%s",t+1);
		int u=1,m=strlen(t+1),bo=0;
		inc(j,1,m){
			int to=t[j]-'a';
			u=sam[u].ch[to];
			if(!u){
				bo=1; break;
			}
		}
		if(bo){
			printf("-1\n");
			continue;
		}
		dfs(u);
		sort(pos+1,pos+1+tot);
		int ans=INT_MAX;
		inc(j,x,tot){
			ans=min(ans,pos[j]-(pos[j-x+1]-m+1)+1);
		}
		if(ans==INT_MAX){
			printf("-1\n");
			continue;
		}
		printf("%d\n",ans);
	}
}
/*
aaaaa
5
3 a
3 aa
2 aaa
3 aaaa
1 aaaaa
*/
```


---

