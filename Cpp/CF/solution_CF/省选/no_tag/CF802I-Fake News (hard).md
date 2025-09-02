# Fake News (hard)

## 题目描述

Now that you have proposed a fake post for the HC $ ^{2} $ Facebook page, Heidi wants to measure the quality of the post before actually posting it. She recently came across a (possibly fake) article about the impact of fractal structure on multimedia messages and she is now trying to measure the self-similarity of the message, which is defined as

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF802I/cdbfdfc02921b55d94f8e9715364be36292f81c3.png)where the sum is over all nonempty strings $ p $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF802I/aea1d5f3b9f7520d94fcc0daea05a447b5429c82.png) is the number of occurences of $ p $ in $ s $ as a substring. (Note that the sum is infinite, but it only has a finite number of nonzero summands.)

Heidi refuses to do anything else until she knows how to calculate this self-similarity. Could you please help her? (If you would like to instead convince Heidi that a finite string cannot be a fractal anyway – do not bother, we have already tried.)

## 说明/提示

A string $ s $ contains another string $ p $ as a substring if $ p $ is a contiguous subsequence of $ s $ . For example, ab is a substring of cab but not of acb.

## 样例 #1

### 输入

```
4
aa
abcd
ccc
abcc
```

### 输出

```
5
10
14
12
```

# 题解

## 作者：hsfzLZH1 (赞：6)

## 题目大意

 $T$ 组数据，每组数据给定一个字符串 $s$ ，求 $\sum_p cnt(s,p)^2$ ，其中 $cnt(s,p)$ 表示 $p$ 在 $s$ 中出现的次数。

## 解题思路

对 $s$ 进行后缀排序。对字符串 $s$ 来说，其任意后缀的前缀都是其子串。对于每个子串，我们发现它对答案的贡献为 $2\times ($ 在这之前其出现的次数 $)+1$ 。

我们所求的答案为

$Ans=\sum_{i=1}^n \sum_{pre(sa_i)} 2\times($ 在这之前该子串出现的次数 $)+1$

$=\sum_{i=1}^n \sum_{pre(sa_i)} 1+2\times \sum_{i=1}^n \sum_{pre(sa_i)} ($ 在这之前该子串出现的次数 $)$

$=\frac {n\times(n+1)} 2+2\times \sum_{i=1}^n \sum_{pre(sa_i)} ($ 在这之前该子串出现的次数 $)$

观察最后这个结构，如果我们能求出对后缀排序中的一个后缀中一个前缀 $p$ 的答案，我们就能求出这个答案。我们发现，在这之前 $p$ 出现的次数即为之前连续的 $h$ 数组的值大于等于 $|p|$ 的长度。可以证明，所求答案为

$Ans=\frac {n\times(n+1)} 2+2\times \sum_{i=2}^n \sum_{j=2}^{i-1} rmqmin(j,i)$

$rmqmin(i,j)$ 即为 $\min\{h_i,h_{i+1},...,h_j\}$ 。

暴力计算显然太慢，我们用一个十分有技巧的单调栈维护这个问题。

单调栈中存的是右端点到当前值的连续最小值互不相同的几块。栈中的元素存储两个值，连续最小值和这个连续最小值出现的次数。

当我们要将当前右端点右移一位（当然不是位运算）时，弹出栈中所有值 ** 大于等于 ** $h_i$ 的值，因为它们在连续取 $\min$ 的过程中答案总是会变成 $h_i$ ，然后统计它们出现的次数和， ** 将一个新的元素加入栈中，其最小值为当前 $h_i$ ，出现次数为统计的次数和 $+1$ ** 。

在同时维护栈中元素的总和，即所有元素连续最小值和出现次数的乘积的和。将新元素加入栈中后，栈中元素的和即为当前位置的答案。

由于每次栈中最多压入一个新元素，弹出时只会弹出原来已经压入的元素，所以时间复杂度可以保证是 $O(n)$ 的。

这样，我们就在 $O(n\log_2 n)$ 的时间复杂度内求出这道题了。如果使用 DC3 法求后缀数组，可以在 $O(n)$ 内解决此题。

记得开 ```long long``` 。

用类似的单调栈技巧，也可以解决 [P4248 \[AHOI2013\]差异](https://www.luogu.org/problemnew/show/P4248) ， [P3181 \[HAOI2016\]找相同字符](https://www.luogu.org/problemnew/show/P3181) 两个问题。

## 代码展示

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack>
using namespace std;
const int maxn=100010;
const int maxsiz=130;
typedef long long ll;
ll T,n,m,sa[maxn],x[maxn],y[maxn],c[maxn],rnk[maxn],h[maxn],ans,tot,cnt;
char s[maxn];
struct node{ll v,cnt;};
stack<node>st;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
    	scanf("%s",s+1);
    	n=strlen(s+1);m=maxsiz-1;
    	for(int i=1;i<=n;i++)x[i]=s[i];
    	for(int i=0;i<=m;i++)c[i]=0;
    	for(int i=1;i<=n;i++)c[x[i]]++;
    	for(int i=1;i<=m;i++)c[i]+=c[i-1];
    	for(int i=n;i>=1;i--)sa[c[x[i]]--]=i;
    	for(int k=1,cur;k<=n;k<<=1)
    	{
        	cur=0;
        	for(int i=n;i>n-k;i--)y[++cur]=i;
        	for(int i=1;i<=n;i++)if(sa[i]>k)y[++cur]=sa[i]-k;
        	for(int i=0;i<=m;i++)c[i]=0;
        	for(int i=1;i<=n;i++)c[x[i]]++;
        	for(int i=1;i<=m;i++)c[i]+=c[i-1];
        	for(int i=n;i>=1;i--)sa[c[x[y[i]]]--]=y[i];
        	cur=y[sa[1]]=1;
        	for(int i=2;i<=n;i++)
        	{
        	    int a,b;
        	    a=sa[i]+k>n?-1:x[sa[i]+k];
				b=sa[i-1]+k>n?-1:x[sa[i-1]+k];
				y[sa[i]]=(x[sa[i]]==x[sa[i-1]])&&(a==b)?cur:(++cur);
        	}
        	swap(x,y);
        	if(cur>=n)break;
        	m=cur;
    	}
    	for(int i=1;i<=n;i++)rnk[sa[i]]=i;
    	int nww=0;
    	for(int i=1;i<=n;i++)
    	{
        	if(rnk[i]==1)continue;
        	if(nww)nww--;
        	while(i+nww<=n&&sa[rnk[i]-1]+nww<=n&&s[i+nww]==s[sa[rnk[i]-1]+nww])nww++;
        	h[rnk[i]]=nww;
    	}
    	ans=n*(n+1)/2;
		for(int i=1;i<=n;i++)
    	{
        	cnt=0;
        	while(!st.empty()&&st.top().v>=h[i])
        	cnt+=st.top().cnt,
        	tot-=st.top().v*st.top().cnt,
    	    st.pop();
	        st.push({h[i],cnt+1});tot+=h[i]*(cnt+1);
    	    ans+=2*tot; 
    	}
    	printf("%lld\n",ans);
	}
    return 0;
}
```

---

## 作者：Alex_Wei (赞：4)

> XIV. [CF802I Fake News (hard)](https://www.luogu.com.cn/problem/CF802I)

> 题意简述：给出 $s$，求所有 $s$ 的子串 $p$ 在 $s$ 中的出现次数平方和，重复的子串只算一次。

本文节选自 [我的 SAM 刷题笔记](https://www.cnblogs.com/alex-wei/p/Suffix_Automaton_Involution.html)，编号为 XIV。

---

这是什么板子题？

对 $s$ 建出 SAM 可以自动去重，考虑每个状态 $p$，它所表示的字串个数为 $len(p)-len(link(p))$，出现次数为 $p$ 在 $link$ 树上的子树所包含的终止节点个数（终止节点是 $s$ 所有前缀在 SAM 上表示的状态），记为 $ed_p$。那么答案为 $\sum_{i=1}^{cnt} ed^2_p\times (len(p)-len(link(p)))$。

时间复杂度线性。

```cpp
/*
	Powered by C++11.
	Author : Alex_Wei.
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define mem(x,v) memset(x,v,sizeof(x))

const int N=2e5+5;
const int S=26;

int cnt,las,son[N][S],ed[N],fa[N],len[N],buc[N],id[N];
void clear(){
	mem(son,0),mem(ed,0),mem(fa,0),mem(len,0),mem(buc,0);
	cnt=las=1;
} void ins(char s){
	int p=las,cur=++cnt,it=s-'a';
	len[cur]=len[p]+1,las=cur,ed[cur]=1;
	while(!son[p][it])son[p][it]=cur,p=fa[p];
	if(!p)return fa[cur]=1,void();
	int q=son[p][it];
	if(len[p]+1==len[q])return fa[cur]=q,void();
	int cl=++cnt;
	fa[cl]=fa[q],fa[q]=fa[cur]=cl,len[cl]=len[p]+1;
	memcpy(son[cl],son[q],sizeof(son[q]));
	while(son[p][it]==q)son[p][it]=cl,p=fa[p];
} ll build(char *s){
	int n=strlen(s+1); clear();
	for(int i=1;i<=n;i++)ins(s[i]);
	for(int i=1;i<=cnt;i++)buc[len[i]]++;
	for(int i=1;i<=n;i++)buc[i]+=buc[i-1];
	for(int i=cnt;i;i--)id[buc[len[i]]--]=i;
	for(int i=cnt;i;i--)ed[fa[id[i]]]+=ed[id[i]];
	ll ans=0;
	for(int i=1;i<=cnt;i++)ans+=1ll*ed[i]*ed[i]*(len[i]-len[fa[i]]);
	return ans;
}

int n;
char s[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%s",s+1),cout<<build(s)<<endl; 
	return 0;
}
```

---

## 作者：MoonPie (赞：4)

# Sulotion - CF802I

[题目链接](https://www.luogu.com.cn/problem/CF802I)

## 题意

$T$ 组数据，每次给你一个字符串 $S$ ，请你输出其所有子串出现次数的平方和。

## 题解

看到题解区都是用 SA+单调栈的做法，这里分享一种 SA+并查集的做法，个人认为比较好理解。

子串相关，我们先SA一遍并求出height数组。

考虑到每个后缀的前缀就是子串，而height数组的意义是两个后缀的LCP，如果我们按照height**从大到小**排序，并且**从大到小**枚举重复出现的子串的长度。然后用一个指针，如果当前的height $\ge$ 枚举的长度，就把两个相邻的后缀合并。用 $sum$ 维护当前长度的子串出现次数的平方和。

显然，前面合并的两个后缀不会分开来，所以就计算得到了答案。

最后不要忘记统计只出现了 $1$ 次的子串！

## 代码

```cpp
const int N=1e5+5;
char s[N];
int n,m,sa[N],rnk[N],tax[N],tp[N],hei[N];
void Sort()
{
	for(int i=1;i<=m;++i) tax[i]=0;
	for(int i=1;i<=n;++i) tax[rnk[i]]++;
	for(int i=1;i<=m;++i) tax[i] += tax[i-1];
	for(int i=n;i>=1;--i) sa[tax[rnk[tp[i]]]--] = tp[i];
}
void SuffixSort()
{
	m = 128;
	for(int i=1;i<=n;++i) rnk[i]=s[i]-'0'+1,tp[i]=i;
	Sort();
	for(int p=0,w=1; p<n; w<<=1,m=p)
	{
		p = 0;
		for(int i=1;i<=w;++i) tp[++p] = n-w+i;
		for(int i=1;i<=n;++i) if(sa[i] > w) tp[++p] = sa[i]-w;
		Sort();
		memcpy(tp,rnk,sizeof(rnk));
		p = rnk[sa[1]] = 1;
		for(int i=2;i<=n;++i) 
			rnk[sa[i]] = (tp[sa[i]]==tp[sa[i-1]]&&tp[sa[i]+w]==tp[sa[i-1]+w])? p: ++p;
	}
	int j,k=0;
	for(int i=1;i<=n;++i) {
		if(k) --k;
		j = sa[rnk[i]-1];
		while(s[i+k] == s[j+k]) ++k;
		hei[rnk[i]] = k;
	}
}
int siz[N],far[N],t[N],lsth[N];
bool cmp(int x,int y) {return hei[x]>hei[y];}
int getf(int x) {return far[x]==x? x: far[x]=getf(far[x]); }
signed main()
{
	int T;
	cin >> T;
	while(T --> 0)
	{
		scanf("%s",s+1);
		n = strlen(s+1);
		SuffixSort();

		memset(lsth,0,sizeof(lsth));
		for(int i=1;i<=n;++i) 
		{
			siz[i] = 1;
			t[i] = far[i] = i;
		}
		sort(t+1,t+n+1,cmp);

		ll sum = 0, ans = 0;
		for(int u,v,pos=1,h=n;h>=1;--h)
		{
			sum++;
			while(pos<=n && hei[t[pos]] >= h)
			{
				u = sa[t[pos]];
				v = sa[t[pos]-1];
				u = getf(u); v = getf(v);
				sum -= 1ll*siz[u]*siz[u];
				sum -= 1ll*siz[v]*siz[v];
				siz[v] += siz[u];
				far[u] = v;
				sum += 1ll*siz[v]*siz[v];
				pos++;
			}
			ans += sum;
		}
		cout << ans <<"\n";
	}
	return 0;
}
```

---

## 作者：KiDDOwithTopTree (赞：2)

题目在这：[传送门](https://www.luogu.com.cn/problem/CF802I)。

题解区一大堆神奇的 $\text {SA}$ 做法，可惜我不会…

于是我用的是 $\text {SAM}$。

首先我们建出来 $\text {parent tree}$。

我们可以知道，$\text {parent tree}$ 上的每一个节点都代表了一个等价类。

我们设 $maxlen_x$ 是 $x$ 等价类的最长子串，$maxlen_x$ 是 $x$ 等价类的最短子串，显然点 $u$ 等价类子串的数量是 $maxlen_u-minlen_u+1$。因为自动机一般只存 $maxlen$，所以我们要把 $minlen_u$ 转换成为 $maxlen_{fa_u}+1$。那么式子就可以等价类子串数量的式子就可以转换成为 $maxlen_u-(maxlen_{fa_u}+1)+1=maxlen_u-maxlen{fa_u}$

那么这个东东是干甚么的？

我们康康要求些甚么东西。

$\sum_p cnt(s,p)^2$。

我们先把范围缩小到一个等价类 $x$ 中。那么我们可以把它改变一下，变成 等价类 $x$ 的子串数量 $\times$ 等价类 $x$ 的子串出现的次数。

等价类 $x$ 的子串数量 我们已经求出来了，那怎么计算 等价类 $x$ 的子串出现的次数呢？

我们可以发现，一个等价类 $x$ 的出现次数就是 $x$ 的 $\text {endpos}$ 的数量。

那么怎么求 $\text {endpos}$ 的数量呢？

通过大眼观察法，我们可以发现：在 $\text {parent tree}$ 上，一个节点的 $\text {endpos}$ 数量其实就是它的儿子的 $\text {endpos}$ 数量的总和。叶节点的 $\text {endpos}$ 数量为1。

那么就只用建出 $\text {parent tree}$ 后在上边 dfs 一下就阔以了。

记得要开 long long 哦。

```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int N=1e6+10;
struct suffix_automaton{
	int last,tot;
	int ch[N][26];
	int size[N];
	int len[N];
	int fa[N];
	suffix_automaton(){
		last=tot=1;
	}
	void add(int c){
		int p=last;
		int np=last=++tot;
		size[np]=1;//在这里新增的节点为叶节点，size为1
		len[np]=len[p]+1;
		while(p&&!ch[p][c]){
			ch[p][c]=np;
			p=fa[p];
		}
		if(!p)
			fa[np]=1;
		else{
			int q=ch[p][c];
			if(len[q]==len[p]+1)
				fa[np]=q;
			else{
				int nq=++tot;
				fa[nq]=fa[q];
				for(int i=0;i<26;i++)
					ch[nq][i]=ch[q][i];
				len[nq]=len[p]+1;
				fa[q]=fa[np]=nq;
				while(p&&ch[p][c]==q){
					ch[p][c]=nq;
					p=fa[p];
				}
			}
		}
	}
	inline void clear(){
		memset(size,0,sizeof size);
		memset(ch,0,sizeof ch);
		memset(len,0,sizeof len);
		memset(fa,0,sizeof fa);
		last=tot=1;
	}
};
struct edge{
	int from,to;
	int nxt;
};
suffix_automaton sam;
edge e[N];
string s;
int last[N];
int tot;
long long ans;//不开long long见祖宗
void clear(){
	sam.clear();
	memset(e,0,sizeof e);
	memset(last,0,sizeof last);
	tot=ans=0;
}
inline void add(int from,int to){
	tot++;
	e[tot].from=from;
	e[tot].to=to;
	e[tot].nxt=last[from];
	last[from]=tot;
}
void dfs(int u){
	for(int i=last[u];i;i=e[i].nxt){
		int v=e[i].to;
		dfs(v);
		sam.size[u]+=sam.size[v];
	}
	ans+=(long long)(sam.len[u]-sam.len[sam.fa[u]])*sam.size[u]*sam.size[u];
}
int main(){
	int t;
	cin>>t;
	while(t--){
		clear();//每一次重新计算都要要清空
		cin>>s;
		int l=s.size();
		for(int i=0;i<l;i++)
			sam.add(s[i]-'a');
		for(int i=2;i<=sam.tot;i++)
			add(sam.fa[i],i);//建出parent tree
		dfs(1);//dfs计算答案
		cout<<ans<<'\n';
	}
}
```

---

## 作者：qiyue7 (赞：1)

一道很水的SAM题目，题目要求所有不同子串的出现次数的平方和

则SAM上每个点的ans为(cnt)^2*(r-l),for循环跑一遍就好，写起来比后缀数组的代码优雅多了~
```java
import java.math.BigInteger;
import java.util.*;
import java.io.*;

public class Main {

    public static InputReader in = new InputReader(System.in);
    public static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));

    public static void main(String[] args)
    {
        int a;
        String s;
        SAM part=new SAM();
        a=in.nextInt();
        while (a--!=0)
        {
            s=in.next();
            part.init(2*s.length()+2,26);
            for(int i=0;i<s.length();++i)
                part.insert(s.charAt(i)-'a');
            long ans=0;
            part.topo();
            SAM_node part2=part.root;
            for(int i=0;i<s.length();++i)
            {
                part2=part2.next[s.charAt(i)-'a'];
                part2.cnt=1;
            }
            for(int i=part.cur-1;i>0;--i)
                part.pool[i].pre.cnt+=part.pool[i].cnt;
            for(int i=part.cur-1;i>0;--i)
                ans+=(long)part.pool[i].cnt*(long)part.pool[i].cnt*((long)part.pool[i].step-(long)part.pool[i].pre.step);
            out.println(ans);
        }
        out.flush();
        out.close();
    }
}
class SAM_node
{
    SAM_node pre,next[];
    int step,cnt;
    SAM_node(int sigma)
    {
        next=new SAM_node[sigma];
        Arrays.fill(next,null);
        step=0;
        cnt=0;
        pre=null;
    }
}
class SAM
{
    SAM_node SAM_pool[],root,last;
    int d[];
    SAM_node pool[];
    int cur;
    int sigma;
    void topo() {
        int cnt = cur;
        int maxVal = 0;
        Arrays.fill(d, 0);
        for (int i = 1; i < cnt; i++) {
            maxVal = Math.max(maxVal, SAM_pool[i].step);

        d[SAM_pool[i].step]++;
    }
        for (int i = 1; i <= maxVal; i++)
            d[i] += d[i - 1];
        for (int i = 1; i < cnt; i++)
            pool[d[SAM_pool[i].step]--] = SAM_pool[i];
        pool[0] = root;
    }
    void init(int a,int b)
    {
        d=new int[a];
        pool=new SAM_node[a];
        SAM_pool=new SAM_node[a];
        SAM_pool[0]=new SAM_node(b);
        sigma=b;
        root=last=SAM_pool[0];
        cur=1;
    }
    void insert(int w)
    {
        SAM_node p=last;
        SAM_pool[cur]=new SAM_node(sigma);
        SAM_node np=SAM_pool[cur];
        last=np;
        cur++;
        np.step=p.step+1;
        while (p!=null && p.next[w]==null)
        {
            p.next[w]=np;
            p = p.pre;
        }
        if(p==null)
        {
            np.pre=root;
        }
        else
        {
            SAM_node q=p.next[w];
            if(p.step+1==q.step)
                np.pre=q;
            else {
                SAM_node nq = SAM_pool[cur++] = new SAM_node(sigma);
                nq.next = Arrays.copyOf(q.next, sigma);
                nq.cnt = q.cnt;
                nq.step = p.step + 1;
                nq.pre = q.pre;
                q.pre = nq;
                np.pre = nq;
                while (p != null && p.next[w]==(q)) {
                    p.next[w] = nq;
                    p = p.pre;
                }
            }
        }
    }
}
class InputReader{
    private final static int BUF_SZ = 65536;
    BufferedReader in;
    StringTokenizer tokenizer;
    public InputReader(InputStream in) {
        super();
        this.in = new BufferedReader(new InputStreamReader(in),BUF_SZ);
        tokenizer = new StringTokenizer("");
    }
    public String next() {
        while (!tokenizer.hasMoreTokens()) {
            try {
                tokenizer = new StringTokenizer(in.readLine());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        return tokenizer.nextToken();
    }
    public int nextInt() {
        return Integer.parseInt(next());
    }
    public long nextLong()
    {
        return Long.parseLong(next());
    }
}
```


---

## 作者：happybob (赞：0)

什么板子能评 $2300$。

建完 SAM，对于每一个点，其表示字符串个数为 $len_u - len_{fa_u}$，出现次数可以通过 $\operatorname{link}$ 边，即后缀链接线性求出，也是套路了。

然后算贡献就没了，复杂度线性。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

const int N = 2e5 + 5;

int tot, last;
int f[N];
long long ans = 0;
int q;
vector<int> G[N];

struct Node
{
	int son[26], len, fa;
}g[N];

void extend(int c)
{
	int p = last;
	int np = last = ++tot;
	g[np].len = g[p].len + 1;
	f[np] = 1;
	for (; p && g[p].son[c] == 0; p = g[p].fa) g[p].son[c] = np;
	if (!p) g[np].fa = 1;
	else
	{
		int q = g[p].son[c];
		if (g[q].len == g[p].len + 1) g[np].fa = q;
		else
		{
			int nq = ++tot;
			g[nq] = g[q];
			g[nq].len = g[p].len + 1;
			g[q].fa = g[np].fa = nq;
			for (; p && g[p].son[c] == q; p = g[p].fa) g[p].son[c] = nq;
		}
	}
}

void dfs1(int u)
{
	for (int j : G[u])
	{
		dfs1(j);
		f[u] += f[j];
	}
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cin >> q;
	while (q--)
	{
		for (int i = 1; i <= tot; i++) 
		{
			f[i] = 0;
			g[i].len = g[i].fa = 0;
			for (int j = 0; j < 26; j++) g[i].son[j] = 0;
			G[i].clear();
		}
		tot = last = 1;
		string s;
		cin >> s;
		for (auto i : s)
		{
			extend(i - 'a');
		}
		for (int i = 2; i <= tot; i++) G[g[i].fa].emplace_back(i);
		ans = 0;
		dfs1(1);
		for (int i = 2; i <= tot; i++)
		{
			ans += f[i] * 1LL * f[i] * (g[i].len * 1LL - g[g[i].fa].len);
		}
		cout << ans << "\n";
	}
	return 0;
}
```


---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF802I)

## 思路

这个题其实是 $\rm SA$ 板子。

初看似乎没什么思路，不过可以拆一下柿子。

假设我们枚举到的串是 $(i,j)$，$(i,j)$ 已经出现过 $x$ 次，那么显然现在的次数变成了 $x+1$ 次，那么串 $(i,j)$ 的贡献就是 $(x+1)^2-x^2=2x+1$。

后面的这个 $1$ 的贡献显然是数对 $(i,j)$ 的总数，显然等于 $\dfrac{(n+1) \times n}{2}$。

而对于前面的这个 $2x$ 的贡献我们可以把 $2$ 提出，现在问题就变成了计算 $x$ 的总和。

假设我们当前枚举的后缀的排名是 $i$，如何计算它与前面的 $j$ 的贡献呢？

设总贡献表示当前 $i$ 的总贡献。

若这两个后缀的最长公共前缀长度为 $l$，则它会令串 $(i,i+1)...(i,i+l)$ 的贡献加 $1$，也就是会令总贡献加 $l$。

那么对于每个 $i$，我们只需要统计所有 $l$ 值的和即可，接下来就是经典套路，直接单调栈。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face will be alive
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=1e5+10;
int rk[N],oldrk[N],sa[N],height[N],n,w=1;
char k[N];string s;
inline bool cmp(int x,int y){return rk[x]==rk[y]?rk[x+w]<rk[y+w]:rk[x]<rk[y];}
inline void SA(){
	for (int i=1;i<=n;++i) k[i]=s[i];sort(k+1,k+n+1);
	sort(k+1,k+n+1);
	for (int i=1;i<=n;++i) rk[i]=lower_bound(k+1,k+n+1,s[i])-k,sa[i]=i;
	for (w=1;w<n;w<<=1){
		sort(sa+1,sa+n+1,cmp);
		memcpy(oldrk,rk,sizeof(oldrk));
		for (int p=0,i=1;i<=n;++i)
			if (oldrk[sa[i]]==oldrk[sa[i-1]] && oldrk[sa[i]+w]==oldrk[sa[i-1]+w]) rk[sa[i]]=p;
			else rk[sa[i]]=++p;
	}
	for (int i=1;i<=n;++i) rk[sa[i]]=i;
	int k=0;
	for (int i=1;i<=n;++i){
		if (k) --k;int j=sa[rk[i]-1];
		while (j+k<=n && i+k<=n && s[i+k]==s[j+k]) ++k;
		height[rk[i]]=k;
	}
}
inline void solve(){
	cin>>s;n=s.length();
	s=" "+s;SA();int ans=n*(n+1)/2;
	stack< pair<int,int> >s;
	s.push({0,0});
	for (int i=1;i<=n;++i){
		while (height[i]<height[s.top().first]) s.pop();
		s.push({i,s.top().second+(i-s.top().first)*height[i]});
		ans+=2*s.top().second;
	}
	cout<<ans<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t;cin>>t;
	while (t--) solve();
	return 0;
}
```

---

## 作者：huayucaiji (赞：0)

这个题和 CF123D 很像，代码只有一点点不同。

首先看到子串的问题容易想到后缀数组，所以我们可以先对字符串求一遍后缀数组以及 `height` 数组。

接下来怎么做？我们其实可以想得到单调栈。我们可以考虑对于 `height` 数组维护一个单调递增的栈。一旦我们要弹出栈顶元素时，我们就知道他一定会对答案做出新贡献，即 $cnt(s,p)>1$。我们只需要把这些有新贡献的串的个数算出来，然后把其他只出现过一次的串的数量统计出来，答案就算出来了。

时间复杂度 $O(n\log n+n)$。

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int MAXN=1e5+10; 

int n,m;
int sa[MAXN],rnk[MAXN],height[MAXN],tmp[MAXN],a[MAXN],b[MAXN],cnt[MAXN],calc[MAXN];
char s[MAXN];

void bucket_sort(int v[]) {
	fill(cnt,cnt+m+1,0);
	for(int i=1;i<=n;i++) {
		cnt[v[i]+1]++;
	}
	for(int i=1;i<=m;i++) {
		cnt[i]+=cnt[i-1];
	}
	for(int i=1;i<=n;i++) {
		tmp[++cnt[v[sa[i]]]]=sa[i];
	}
	for(int i=1;i<=n;i++) {
		sa[i]=tmp[i];
	}
}

void get_sa() {
	for(int i=1;i<=n;i++) {
		rnk[i]=tmp[i]=s[i];
		sa[i]=i;
	}
	sort(tmp+1,tmp+n+1);
	m=unique(tmp+1,tmp+n+1)-tmp-1;
	for(int i=1;i<=n;i++) {
		rnk[i]=lower_bound(tmp+1,tmp+m+1,rnk[i])-tmp;
	}
	
	for(int l=1;l<n;l<<=1) {
		for(int i=1;i<=n;i++) {
			a[i]=rnk[i];
			b[i]=(i+l<=n? rnk[i+l]:0);
		}
		bucket_sort(b);
		bucket_sort(a);
		
		m=0;
		for(int i=1;i<=n;i++) {
			if(a[sa[i]]!=a[sa[i-1]]||b[sa[i]]!=b[sa[i-1]]) {
				m++;
			}
			rnk[sa[i]]=m;
		}
	}
}

void get_height() {
	int h=0;
	for(int i=1;i<=n;i++) {
		if(h) {
			h--;
		}
		if(rnk[i]==1) {
			continue;
		}
		
		int p=i+h;
		int q=sa[rnk[i]-1]+h;
		
		while(p<=n&&q<=n&&s[p]==s[q]) {
			p++;
			q++;
			h++;
		}
		height[rnk[i]]=h;
	}
}

int solve() {
	int ans=n*(n+1)/2;
	stack<int> stk;
	for(int i=2;i<=n+1;i++) {
		while(!stk.empty()&&height[stk.top()]>height[i]) {
			int y=height[stk.top()];
			int x=height[i];
			stk.pop();
			int z=(stk.empty()? 0:height[stk.top()]);
			int len=i-(stk.empty()? 1:stk.top());
			ans+=(y-max(x,z))*(len*len-len);
		}
		stk.push(i);
	}
	return ans;
}

signed main() {
	int t=read();
	
	while(t--) {
		scanf("%s",s+1);
		n=strlen(s+1);
		
		get_sa();
		get_height();
		
		printf("%lld\n",solve());
	} 
	return 0;
}

```

**对于单调栈的思考，我有一个小技巧，可以通过画柱形图来帮助思考，这样会很直观**

---

## 作者：「QQ红包」 (赞：0)

先用SA求出 $height$。

这个的话就是模板。

不知道你们那些单调栈的技巧，于是写了一个线段树。

然后根据排名，对于还存在的子串，用线段树维护区间平方和，区间和。

如果这个子串在之后不存在了，就直接加进答案。

这种写法思维难度就为0了，实现起来没细节。

```cpp
/*
 * Author: ylx
 * Lang: c++
 * Prog: 802I
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
void qmax(int &x, int y)
{
    if (x < y)
        x = y;
}
void qmin(int &x, int y)
{
    if (x > y)
        x = y;
}
inline ll read()
{
    char s;
    ll k = 0, base = 1;
    while ((s = getchar()) != '-' && s != EOF && !(isdigit(s)))
        ;
    if (s == EOF)
        exit(0);
    if (s == '-')
        base = -1, s = getchar();
    while (isdigit(s))
        k = k * 10 + (s ^ '0'), s = getchar();
    return k * base;
}
inline void write(ll x)
{
    static char cnt, num[20];
    cnt = 0;
    if (!x)
    {
        putchar('0');
        return;
    }
    for (; x; x /= 10)
        num[++cnt] = x % 10;
    for (; cnt; putchar(num[cnt--] + 48))
        ;
}
const int maxn = 1e5 + 10;
int n;
char ch[maxn];
namespace ST
{
ll t[maxn << 2], s[maxn << 2], tag[maxn << 2], f[maxn << 2];
void update(int d)
{
    t[d] = t[d << 1] + t[d << 1 | 1];
    s[d] = s[d << 1] + s[d << 1 | 1];
}
void pushdown(int d, int l, int r)
{
    int mid = (l + r) >> 1;
    if (f[d] == 2)
    {
        s[d << 1] = t[d << 1] = 0;
        s[d << 1 | 1] = t[d << 1 | 1] = 0;
        f[d << 1] = f[d << 1 | 1] = 2;
        tag[d << 1] = tag[d << 1 | 1] = 0;
        f[d] = 0;
    }
    if (tag[d])
    {
        t[d << 1] = t[d << 1] + 2 * tag[d] * s[d << 1] + (mid - l + 1) * tag[d] * tag[d];
        t[d << 1 | 1] = t[d << 1 | 1] + 2 * tag[d] * s[d << 1 | 1] + (r - mid) * tag[d] * tag[d];
        s[d << 1] += tag[d] * (mid - l + 1);
        s[d << 1 | 1] += tag[d] * (r - mid);
        tag[d << 1] += tag[d];
        tag[d << 1 | 1] += tag[d];
        tag[d] = 0;
    }
}
void add(int x, int y, int d, int l, int r)
{
    if (l <= x && y <= r)
    {
        t[d] = t[d] + 2 * s[d] + (y - x + 1);
        s[d] += y - x + 1;
        tag[d]++;
        return;
    }
    int mid = (x + y) >> 1;
    pushdown(d, x, y);
    if (l <= mid)
        add(x, mid, d << 1, l, r);
    if (r > mid)
        add(mid + 1, y, d << 1 | 1, l, r);
    update(d);
}
ll query(int x, int y, int d, int l, int r)
{
    if (l <= x && y <= r)
    {
        ll z = t[d];
        t[d] = s[d] = tag[d] = 0;
        f[d] = 2;
        return z;
    }
    ll sum = 0;
    int mid = (x + y) >> 1;
    pushdown(d, x, y);
    if (l <= mid)
        sum += query(x, mid, d << 1, l, r);
    if (r > mid)
        sum += query(mid + 1, y, d << 1 | 1, l, r);
    update(d);
    return sum;
}
} // namespace ST
namespace SA
{
int m;
int x[maxn + maxn], y[maxn + maxn], s[maxn], c[maxn], rk[maxn], h[maxn];
void init()
{
    memset(c, 0, sizeof(c));
    m = 0;
    for (int i = 1; i <= n; i++)
        c[x[i] = ch[i] - 'a' + 1]++, qmax(m, x[i]);
    for (int i = 2; i <= m; i++)
        c[i] += c[i - 1];
    for (int i = 1; i <= n; i++)
        s[c[x[i]]--] = i;
    for (int k = 1, p; k < n; k <<= 1)
    {
        p = 0;
        for (int i = n - k + 1; i <= n; i++)
            y[++p] = i;
        for (int i = 1; i <= n; i++)
            if (s[i] > k)
                y[++p] = s[i] - k;
        for (int i = 1; i <= m; i++)
            c[i] = 0;
        for (int i = 1; i <= n; i++)
            c[x[y[i]]]++;
        for (int i = 2; i <= m; i++)
            c[i] += c[i - 1];
        for (int i = n; i >= 1; i--)
        {
            s[c[x[y[i]]]--] = y[i];
        }
        memcpy(y, x, sizeof(y));
        x[s[1]] = p = 1;
        ++p;
        for (int i = 2; i <= n; i++)
            x[s[i]] = (y[s[i]] == y[s[i - 1]] && y[s[i] + k] == y[s[i - 1] + k]) ? p - 1 : p++;
        m = p;
    }
    for (int i = 1; i <= n; i++)
        rk[s[i]] = i;
    for (int i = 1, k = 0, j; i <= n; i++)
    {
        if (k)
            k--;
        j = s[rk[i] - 1];
        while (ch[i + k] == ch[j + k])
            k++;
        h[rk[i]] = k;
    }
}
void work()
{
    ll ans = 0,L=0;
    m = 0;
    int lst = 0;
    for (int i = 1, x; i <= n; i++)
    {
        if (h[i] < m)
            ans += ST::query(1, n, 1, h[i] + 1, m);
        x = s[i];
        ST::add(1, n, 1, 1, n - x + 1);
        lst = n - x + 1;
        m = n - x + 1;
        L=ans;
    }
    ans += ST::query(1, n, 1, 1, m);
    ST::query(1, n, 1, 1, n);
    printf("%lld\n", ans);
}
} // namespace SA
int main()
{
#ifdef ylx
    freopen("802I.in", "r", stdin);
    freopen("802I.out", "w", stdout);
#endif
    int T = read();
    while (T--)
    {
        scanf("%s", ch + 1);
        n = strlen(ch + 1);
        SA::init();
        SA::work();
    }
    return 0;
}
//2019年 06月 19日 星期三 19:02:44 CST
```

---

