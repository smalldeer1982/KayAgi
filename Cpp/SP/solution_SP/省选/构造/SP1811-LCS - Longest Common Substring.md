# LCS - Longest Common Substring

## 题目描述

A string is finite sequence of characters over a non-empty finite set Σ.

In this problem, Σ is the set of lowercase letters.

Substring, also called factor, is a consecutive sequence of characters occurrences at least once in a string.

Now your task is simple, for two given strings, find the length of the longest common substring of them.

Here common substring means a substring of two or more strings.

## 样例 #1

### 输入

```
alsdfkjfjkdsal
fdjskalajfkdsla```

### 输出

```
3```

# 题解

## 作者：bztMinamoto (赞：15)

思路和楼上那位差不多

对第一个字符串建SAM，然后第二个字符串一个一个匹配过去

设p=1，len=0（SAM的root为1）

1.p有si的转移，直接跳下去，len++

2.p没有转移，在parent树上往上跳，直到有这个转移为止，并len=len（p）+1，再跳下去

3.跳到头还是没有转移，令p=1，len=0重新开始

顺带一提，蒟蒻实在看不懂楼上大佬的代码……
```
#include<cstdio>
#include<cctype>
#include<cstring>
#define N 500050
#define max(a,b) (a>b)?a:b
using namespace std;
char s[N],t[N];
int n1,n2;
int len=0,ans=0;
struct SuffixAutoMaton{
	int last,cnt;int ch[N][26],fa[N<<1],l[N<<1];
    SuffixAutoMaton(){cnt=last=1;}
    void ins(int c){
        int p=last,np=++cnt;last=np,l[np]=l[p]+1;
        for(;p&&!ch[p][c];p=fa[p]) ch[p][c]=np;
        if(!p) fa[np]=1;
        else{
            int q=ch[p][c];
            if(l[q]==l[p]+1) fa[np]=q;
            else{
                int nq=++cnt;l[nq]=l[p]+1;
                memcpy(ch[nq],ch[q],sizeof(ch[q]));
                fa[nq]=fa[q];fa[q]=fa[np]=nq;
                for(;ch[p][c]==q;p=fa[p]) ch[p][c]=nq;
            }
        }
    }
	void build(int n){
		for(int i=1;i<=n;i++)
		ins(s[i]-'a');
	}
	void calc(int n){
		int p=1;
		for(int i=1;i<=n;i++){
			int c=t[i]-'a';
			if(ch[p][c]) len++,p=ch[p][c];
			else{
				for(;p&&!ch[p][c];p=fa[p]);
				if(p) len=l[p]+1,p=ch[p][c];
				else len=0,p=1;
			}
			ans=max(ans,len);
		}
	}
}sam;
int main(){
	scanf("%s%s",s+1,t+1);
	n1=strlen(s+1),n2=strlen(t+1);
	sam.build(n1);
	sam.calc(n2);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：a1co0av5ce5az1cz0ap_ (赞：7)

~~其它 SA 题解怎么都被 hack 了~~

看到这道题我们发现是求最长公共子串，也就是要求连续。

因为子串是后缀的前缀，所以可以考虑使用后缀数组，这样就是一些后缀和另一些后缀之间的最长公共前缀的问题了。

首先要把两个串放在一起后缀排序，这个就直接把两个串拼起来再在中间随便塞一个字符即可。

接下来考虑使用 height 数组。

因为我们要找的是最长公共前缀的最大值，根据 $\text{LCP}(s_{sa_i},s_{sa_j})=\min\limits_{k=i+1}^{j}h_k$（$s_i$ 表示第 $i$ 个字符开头的后缀，$h_i$ 即 height 数组），容易想到只检查排名相邻的字符串，这一定是不劣的。

判断一个后缀是在第一个串还是第二个串是容易的，因此直接对于任意两个排名相邻的后缀检查这两个后缀是否属于不同的串，在所有符合条件的相邻的串的 height 中取最大值即为答案。

```cpp
string s,t;
int n,sa[500005],rk[500005],tmp[500005],ht[500005];
void build(string s){// 这里采用的是 n log^2 n 的后缀排序
	n=s.size()-1;
	for(int i=1;i<=n;i++)sa[i]=i,rk[i]=s[i];
	for(int l=1;l<n;l<<=1){
		sort(sa+1,sa+n+1,[&](int x,int y){return rk[x]==rk[y]?rk[x+l]<rk[y+l]:rk[x]<rk[y];});
		for(int i=1,p=0;i<=n;i++)tmp[sa[i]]=rk[sa[i-1]]==rk[sa[i]]&&rk[sa[i-1]+l]==rk[sa[i]+l]?p:++p;
		memcpy(rk+1,tmp+1,n<<2);
	}
	for(int i=1,k=0;i<=n;i++){
		if(rk[i]==1)k=ht[1]=0;
		else{
			if(k)--k;
			for(int j=sa[rk[i]-1];i+k<=n&&j+k<=n&&s[i+k]==s[j+k];++k);
			ht[rk[i]]=k;
		}
	}
}

void __INIT__(){ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
void __SOLVE__(int _case){
	cin>>s>>t;
	build(" "+s+" "+t);
	int ans=0;
	for(int i=1;i<=n;i++)
    	if(i<=s.size()&&sa[rk[i]-1]>s.size()+1||i>s.size()+1&&sa[rk[i]-1]<=s.size())// 在起点两个串中
        	ans=max(ans,ht[rk[i]]);
	cout<<ans<<"\n";
}
```

---

## 作者：chihik (赞：3)


一道后缀自动机的板题。

我们从根结点开始匹配，如果有转移就将$cnt++$

不然就顺着后缀链接向上跳，直到找到有转移的点，用 $Maxlen$ 继续匹配。(后缀链接一定是它的子串，也能被匹配)。

如果没有跳到合适的点就从根重新匹配。

最后选取最大的$cnt$就可以了。

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 2 * 250000 , MAXC = 26;
struct Suffix_Automaton {
	int Size , Last , Maxlen[ MAXN + 5 ];
	int Trans[ MAXN + 5 ][ MAXC + 5 ] , Link[ MAXN + 5 ];
	
	Suffix_Automaton( ) { Size = Last = 1; }
	
	void Copy( int u , int v ) {
		for( int i = 1 ; i <= MAXC ; i ++ )
			Trans[ u ][ i ] = Trans[ v ][ i ];
	}
	void Extend( int chr ) {
		int Newnode = ++ Size , u = Last;
		Maxlen[ Newnode ] = Maxlen[ u ] + 1;
		
		for( ; u && !Trans[ u ][ chr ] ; u = Link[ u ] )
			Trans[ u ][ chr ] = Newnode;
		
		if( !u ) Link[ Newnode ] = 1;
		else {
			int v = Trans[ u ][ chr ];
			
			if( Maxlen[ v ] == Maxlen[ u ] + 1 ) Link[ Newnode ] = v;
			else {
				int w = ++ Size;
				Copy( w , v ); Maxlen[ w ] = Maxlen[ u ] + 1;
				for( ; u && Trans[ u ][ chr ] == v ; u = Link[ u ] ) Trans[ u ][ chr ] = w;
				Link[ w ] = Link[ v ];
				Link[ v ] = Link[ Newnode ] = w;	
			}
		}
		Last = Newnode;
	}
	
	void Build( char *str ) {
		int len = strlen( str );
		for( int i = 0 ; i < len ; i ++ )
			Extend( str[ i ] - 'a' + 1 );
	}
	int Calc( char *str ) {
		int len = strlen( str );
		int Ans = 0 , tot = 0 , u = 1;
		for( int i = 0 ; i < len ; i ++ ) {
			int chr = str[ i ] - 'a' + 1;
			if( Trans[ u ][ chr ] ) {
				tot ++;
				u = Trans[ u ][ chr ];
			}
			else {
				for( ; u && !Trans[ u ][ chr ] ; u = Link[ u ] );
				if( !u ) tot = 0 , u = 1;
				else {
					tot = Maxlen[ u ] + 1;
					u = Trans[ u ][ chr ];
				}
			}
			Ans = max( Ans , tot ); 
		}
		return Ans;
	}
}SAM;

char str[ 3 ][ MAXN + 5 ];
int main( ) {
	for( int i = 1 ; i <= 2 ; i ++ )
		scanf("%s",str[ i ]);
	SAM.Build( str[ 1 ] );
	printf("%d", SAM.Calc( str[ 2 ] ) );
	return 0;
}
```


---

## 作者：Last炫神丶 (赞：3)

呃，看了一圈没有发现广义 SAM 的写法啊。。为啥大火都喜欢在 SAM 上匹配啊。。不麻烦吗。。

### 分析
广义 SAM 裸题，对于一个节点，如果他在两个串上都有 endpos（即 siz[x][0]&&siz[x][1]），那么它就是两个串上的公共子串。

然后就是建 SAM，dfs 算 endpos，同时统计答案就行了。。

我把[P3181 [HAOI2016]找相同字符](https://www.luogu.com.cn/problem/P3181)的代码调大数组，改了一行算 ans 的就 A 了。。

### code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+7;
char s1[N],s2[N];
struct suffixautomaton{
	int sz=1;
	int last=1;
	int trans[2*N][27],link[2*N],siz[2*N][2],lst[2*N];
	int head[2*N],nxt[2*N],ver[2*N],tot=1;
	int ans=0;
	inline void add(int x,int y){
		ver[++tot]=y,nxt[tot]=head[x],head[x]=tot;
	}
	void insert(int val,int o){
		int now=++sz;
		lst[now]=lst[last]+1;
		int p=last;
		siz[now][o]++;
		while(!trans[p][val]){
			trans[p][val]=now;
			p=link[p];
		}
		if(p==0){
			link[last=now]=1;
			return;
		}
		int q=trans[p][val];
		if(lst[q]==lst[p]+1){
			link[now]=q;
		}
		else {
			int clone=++sz;
			lst[clone]=lst[p]+1;
			link[clone]=link[q];
			memcpy(trans[clone],trans[q],sizeof(trans[q]));
			while(trans[p][val]==q){
				trans[p][val]=clone;
				p=link[p];
			}
			link[now]=link[q]=clone;
		}
		last=now;
	}
	inline void build(){
		for(int i=2;i<=sz;i++)
			add(link[i],i);
	}
	void dfs(int x){
		for(int i=head[x];i;i=nxt[i]){
			int y=ver[i];
			dfs(y);
			siz[x][0]+=siz[y][0],siz[x][1]+=siz[y][1];
		}
		if(siz[x][0]&&siz[x][1]) ans=max(ans,lst[x]);
	}
}sam;
int main(){
	scanf("%s",s1);
	scanf("%s",s2);	
	int len1=strlen(s1),len2=strlen(s2);
	for(int i=0;i<len1;i++)
		sam.insert(s1[i]-'a',0);
	sam.insert(26,0);
	for(int i=0;i<len2;i++)
		sam.insert(s2[i]-'a',1);
	sam.build();
	sam.dfs(1);
	printf("%d\n",sam.ans);
}
```

---

## 作者：teafrogsf (赞：3)

怎么没有人给这~~SB~~题写题解啊......  
直接用第一个串建$SAM$，然后第二串放在上面暴力匹配每一位：
如果当前有这个字符的转移就直接转移，如果没有就沿着$parent$边上跳，直到有这个转移为止。  
有几个小问题要注意一下：找到转移后你不能直接把当前答案设为$len[nex[p][x]]$而是$len[p]+1$，因为$len$表示的是最大长度；如果一开始就找到转移只能$++now$，因为这时你的这个转移并不保证长度是当前节点的最大长度。 
```cpp
#include<cstdio>
#include<cstring>
#define neko 1000010
#define chkmax(a,b) ((a)>(b)?(a):(b))
#define f(i,a,b) for(register int i=(a);i<=(b);i=-(~(i)))
typedef int arr[neko];
arr len,link;
int nex[neko][26];
namespace SAM
{
    int ans=0,slen,cur,last,cnt=0;
    void extend(char *s)
    {
        link[0]=-1;
        slen=strlen(s)-1;
        int p,q,clone,x;
        f(i,0,slen)
        {
            len[cur=++cnt]=len[last]+1,x=s[i]-'a';
            for(p=last;p!=-1&&(!nex[p][x]);p=link[p])nex[p][x]=cur;
            if(p==-1)link[cur]=0;
            else
            {
                q=nex[p][x];
                if(len[q]==len[p]+1)link[cur]=q;
                else
                {
                    clone=++cnt;
                    len[clone]=len[p]+1;
                    link[clone]=link[q];
                    memcpy(nex[clone],nex[q],sizeof(nex[q]));
                    for(;p!=-1&&(nex[p][x]==q);p=link[p])nex[p][x]=clone;
                    link[cur]=link[q]=clone;
                }
            }
            last=cur;
        }
    }
    void solve(char *s)
    {
        slen=strlen(s)-1;
        int p=0,x,now=0;
        f(i,0,slen)
        {
            x=s[i]-'a';
            //printf("%d %c %d %d\n",i,s[i],nex[p][x],len[nex[p][x]]);
            if(nex[p][x])++now,p=nex[p][x];
            else
            {
                for(;p!=-1&&(!nex[p][x]);p=link[p]);
                if(p==-1)p=0,now=0;
                else now=len[p]+1,p=nex[p][x];
            }ans=chkmax(ans,now);
        }printf("%d\n",ans);
    }
}
char s[neko];
int main()
{
    scanf("%s",s);
    SAM::extend(s);
    getchar();
    scanf("%s",s);
    SAM::solve(s);
}
```

---

## 作者：Rainybunny (赞：2)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[$luogu$](https://www.luogu.org/problem/SP1811).
# 题解
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这道题作为了后缀自动机 ( $SAM$ ) 的板子, 正解复杂度应该是$O(n)$的, 大家不妨看一看.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;对于$SAM$的基础知识, 其实我也没有完全吸收$qwq$, 所以就不献丑了, 推荐一篇[$blog$](http://www.cnblogs.com/GBRgbr/p/3236451.html). 再者, 由于板子十分不熟悉, 导致大小驼峰交错, 风格鬼畜, ( 我其实是打大驼峰的$w$, ) 望见谅.

---
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;进入正题.  
## 整体思路
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;首先, 我们应该了解到, $SAM$的本质是把一个母串$S$的所有后缀暴力建出一颗$Trie$树, 再~~xjb~~简化这颗$Trie$树所得到的. 所以, 正如原来的那颗$Trie$树一样, 我们从$SAM$的根节点出发, 走到任意结点停止, 路径上的字符所构成的串一定是$S$的字串.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;就这样, 我们对于第一个串 ( 令为$S$ ) 构造出$SAM$, 尝试把第二个串 ( 令为$T$ ) 放在自动机里进行特殊的匹配, 以求得最终的答案.  
## 匹配方式
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;在这之前, 先约定一些变量的意义 ( 因为我的板子可能长得和大众版不一样. )  
```cpp
struct Node {
	int mx; // 该结点能够表示的最长字符串长度. 类似于其它板子里的"len".
	Node *fa, *ch[26]; // fa: 后缀链接 ( 或者说前缀树 ) 的父节点指针. ch: DAWG中孩子们的指针.
};
```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;匹配开始! 我们尝试把$T$从左到右按顺序加入, 我们现在所在结点的指针为$p$, 当前字符为$c$, 分类讨论:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$a)$  $p \text{->} ch[c] \not= NULL$, 即当前匹配的串末尾接上$c$, 仍能匹配, 就把目前匹配串的长度$++$, $p$指向$ch[c]$.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$b)$ 否则, 就相当于$c$加入后, 当前串失配了. 我们就让$p$沿着前缀树向父亲跳, 一直跳到$p$为$NULL$或$p$满足$a)$. 对于前者, 当然直接把目前答案置零, $p$回到根节点; 对于后者, 取从根到$p$最长的串 ( 这一段仍是匹配的 ) 长度$+1$, 成为现在的答案, 再让$p$走向$ch[c]$, 继续匹配即可.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;每次加入$c$, 记得用当前答案更新最后答案.
## 代码
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~~指针警告~~! ~~鬼畜码风警告!~~ ~~懒得删调试信息 ( 雾 ) 警告!~~
```cpp
#include <cstdio>
#include <cstring>

#define Int register int
//#define _DEBUG "Tianyi bless me!"

class Suffix_Automaton {
private:
	struct Node {
		int mx; // 该结点能够表示的最长字符串长度. 类似于其它板子里的"len".
		Node *fa, *ch[26]; // fa: 后缀链接 ( 或者说前缀树 ) 的父节点指针. ch: DAWG中孩子们的指针.
		Node () {}
		Node ( const int _mx ) {
			mx = _mx, fa = NULL;
			for ( Int i = 0; i ^ 26; ++ i ) ch[i] = NULL;
		}
	};
	Node *rt = new Node ( 0 ), *lst = rt;
#ifdef _DEBUG
	inline bool IsNULL ( Node *p ) { return p == NULL; }
#define _chk( p ) puts ( IsNULL ( p ) ? #p" is null." : #p" isn't null." )
#endif

public:
	inline Node* NewNode () {
		Node *p = new Node ( 0 );
		return p;
	}
	inline void Extend ( const int c ) {
		Node *cur = NewNode (), *p = lst;
		cur -> mx = lst -> mx + 1, lst = cur;
		while ( p != NULL && p -> ch[c] == NULL ) p -> ch[c] = cur, p = p -> fa;
		if ( p == NULL ) cur -> fa = rt;
		else {
			Node *q = p -> ch[c];
//			_chk ( p ), _chk ( q );
			if ( q -> mx == p -> mx + 1 ) {
				cur -> fa = q;
			}
			else {
				Node *r = NewNode ();
				*r = *q, r -> mx = p -> mx + 1;
				cur -> fa = q -> fa = r;
				while ( p != NULL && p -> ch[c] == q ) p -> ch[c] = r, p = p -> fa;
			}
		}
	}
	inline void Build ( char *S ) {
		int l = strlen ( S );
		for ( Int i = 0; i ^ l; ++ i ) Extend ( S[i] - 'a' );
	}
	inline int Calc ( char *T ) {
		int ret = 0, now = 0;
		Node *p = rt;
		int l = strlen ( T );
		for ( Int i = 0; i ^ l; ++ i ) {
			int c = T[i] - 'a';
			if ( p -> ch[c] != NULL ) ++ now, p = p -> ch[c];
			else {
				for ( ; p != NULL && p -> ch[c] == NULL; p = p -> fa );
				if ( p != NULL ) now = p -> mx + 1, p = p -> ch[c];
				else now = 0, p = rt;
			}
			ret = ret > now ? ret : now;
		}
		return ret;
	}
};

const int MAXL = 250000;
char S[MAXL + 5] = {}, T[MAXL + 5] = {};
Suffix_Automaton SAM;

inline void Work () {
	scanf ( "%s %s", S, T );
	SAM.Build ( S );
	printf ( "%d\n", SAM.Calc ( T ) );
}

int main () {
	Work ();
	return 0;
}
```

---

## 作者：温词 (赞：1)

### 首先安利一下自己的blog https://www.cnblogs.com/wenci/p/10432932.html
#### 后缀自动机的一大用处就是求最长公共子串了这道题的话题意就是给你两个字符串，求最长公共子串做法的话是先使用一个字符串建立SAM，然后让另一个串在上面进行匹配匹配的策略是优先匹配当前节点的下一个字符，如果没有可以匹配的，就沿着parent树向上跳，如果到根了，就重新初始化重新开始搜，如果不是根就往下跳，把len更新为node[p].len+1（这个是因为我只是比p节点的串长1，而不是完全匹配选一个节点的最长长度）具体的解释放在代码中吧
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int w=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        w=(w<<3)+(w<<1)+ch-48;
        ch=getchar();
    }
    return w*f;
}
int n,m,lst=1,tot=1;
int l1,l2;
long long size[2000010];
struct Node{
    int len,fa;
　　 map<int,int> ch;//因为有的题字符集可能比较大，开个map其实还是比较舒服的
}node[2000010];
inline void extend(int now){//这个建SAM的过程是常规操作
    int p=lst;tot++;lst=tot;int np=tot;
    node[np].len=node[p].len+1;
    while(p&&!node[p].ch[now]){
        node[p].ch[now] = np;
        p = node[p].fa;
    }
    if(!p) node[np].fa = 1;
    else{
        int q = node[p].ch[now];
        if(node[q].len == node[p].len + 1){
            node[np].fa=q;
        }
        else{
            int nq=++tot;
            node[nq]=node[q];
            node[nq].len=node[p].len+1;
            node[np].fa = node[q].fa = nq;
            while(p && node[p].ch[now] == q){
                node[p].ch[now] = nq;
                p = node[p].fa;
            }
        }
    }
}
char s[2000010],t[2000010];int ans=0;
int main(){
    scanf("%s%s",s+1,t+1);int i,j,k;
    l1=strlen(s+1),l2=strlen(t+1);
    for(i=1;i<=l1;i++){
        extend(s[i]-'a'+1);
    }//建出第一个串的SAM
    int p=1;int len=0;//初始化，让当前指针到根，长度设为0
    for(i=1;i<=l2;i++){
        int now=t[i]-'a'+1;
        if(node[p].ch[now]){//匹配策略见我上面的注释
            p=node[p].ch[now];len++;
        }
        else{
            while(p&&!node[p].ch[now]){
                p=node[p].fa;
            }
            if(!p){
                p=1;len=0;
            }
            else{
                len=node[p].len+1;p=node[p].ch[now];
            }
        }
        ans=max(ans,len);
    }
    cout<<ans<<endl;
    return 0;
}
```

---

