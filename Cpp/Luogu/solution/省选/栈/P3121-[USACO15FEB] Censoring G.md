# [USACO15FEB] Censoring G

## 题目描述

FJ 把杂志上所有的文章摘抄了下来并把它变成了一个长度不超过 $10^5$ 的字符串 $s$。他有一个包含 $n$ 个单词的列表，列表里的 $n$ 个单词记为 $t_1 \cdots t_n$。他希望从 $s$ 中删除这些单词。

FJ 每次在 $s$ 中找到最早出现的列表中的单词（最早出现指该单词的开始位置最小），然后从 $s$ 中删除这个单词。他重复这个操作直到 $s$ 中没有列表里的单词为止。注意删除一个单词后可能会导致 $s$ 中出现另一个列表中的单词。

FJ 注意到列表中的单词不会出现一个单词是另一个单词子串的情况，这意味着每个列表中的单词在 $s$ 中出现的开始位置是互不相同的。

请帮助 FJ 完成这些操作并输出最后的 $s$。

## 说明/提示

#### 数据规模与约定

对于全部的测试点，保证：

- $1 \leq |s|, \sum\limits_{i = 1}^n |t_i|, n \leq 10^5$。
- 字符串均只含小写字母。
- 操作结束后 $s$ 不会被删成空串。
- 对于所有的 $i \neq j$，$t_i$ 不是 $t_j$ 的子串。

其中对于一个字符串 $x$，约定 $|x|$ 表示 $x$ 的长度。

---

#### 提示

操作过程中 $s$ 有可能某一个前缀子串被完全删除，请格外注意这一点。


## 样例 #1

### 输入

```
begintheescapexecutionatthebreakofdawn 
2 
escape 
execution 
```

### 输出

```
beginthatthebreakofdawn 
```

# 题解

## 作者：Treeloveswater (赞：53)

既然没人搞题解，那我就来份题解吧。

这个题实际上是用栈+AC自动机实现O（n）效率的。

再次吐槽一下数据，纯暴力都能过93分，数据水的不要不要的。

两种做法：

##法1：栈+AC自动机

开两个栈，一个记录当前节点扫到AC自动机的哪个地方了，一个记录当然栈内合法的字符，每当发现一个能删去的字符串的时候，只需要把两个栈都减去字符串长度即可，把now修改一下，继续往后扫即可，最后输出第二个栈即可。

##法2：暴力玄学AC自动机

不用栈，sign记录当前节点扫到AC自动机的哪个地方，我们开一个next数组和pre数组，记录当前这个点的后面那个点是几号、前面那个点是几号，每当发现一个能删去的字符串的时候，暴力跳到字符串头上的pre，将其的next修改为字符串尾的next，修改一下now，继续扫就行，这样也能A。因为要O（n）预处理一下next和pre，所以会比法1稍微慢一丢丢。（鬼知道我为啥玄学的法2卡评测机的比法1跑的快几毫秒）

##法1代码：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
char s[100001],ori[100001];
int n,tot,w,top;
int trie[100001][26],fail[100001],heap[100001],sign[100001];
int isend[100001];
void insert(char *s){
    int now=0,len=strlen(s);
    for(int i=0;i<len;i++){
        int x=s[i]-'a';
        if(!trie[now][x])trie[now][x]=++tot;
        now=trie[now][x];
    }
    isend[now]=len;
}
void makefail(){
    queue<int> q;
    for(int i=0;i<26;i++)
    if(trie[0][i])q.push(trie[0][i]);
    while(!q.empty()){
        int now=q.front();q.pop();
        for(int i=0;i<26;i++){
            if(!trie[now][i]){
                trie[now][i]=trie[fail[now]][i];
                continue;
            }        
            fail[trie[now][i]]=trie[fail[now]][i];
            q.push(trie[now][i]);
        }
    }
}
void solve(char *s){
    int now=0,len=strlen(s),i=0;
    w=0;
    while(i<len){
        int x=s[i]-'a';
        now=trie[now][x];
        sign[++top]=now;
        heap[top]=i;
        if(isend[now]){
            top-=isend[now];
            if(!top) now=0;
            else now=sign[top];
        }
        i++;
    }
}
int main()
{
    scanf("%s",s);
    scanf("%d",&n);
    int len=strlen(s);
    for(int i=1;i<=n;i++){
        scanf("%s",ori);
        insert(ori);
    }
    makefail();
    solve(s);
    for(int i=1;i<=top;i++)
    printf("%c",s[heap[i]]);
    return 0;
}
```

---

## 作者：w43322 (赞：24)

实测本题数据很水 自然溢出哈希可以过 又没看到有人发哈希的题解 所以来发一篇...（其实是因为本菜鸡调不出AC自动机）

首先扫描单词的时候把每个单词的Hash值预处理出来 然后跟它的长度一起存在结构体里，把结构体按照单词长度排序，然后在最后在栈里模拟的时候一个一个把原串中的字符推到栈里，只要大于最小的单词长度就可以开始哈希匹配，如果匹配成功就把这一段出栈。

总体的时间复杂度是O(n*串长) ，跑不满就是了......下面上代码。

```cpp
// luogu-judger-enable-o2
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn=100000+10;
const ll b=131;
ll Hash[maxn],Pow[maxn]={1};
char str[maxn],u[maxn],tmp[maxn];
struct Tmp
{
    int len;
    ll Hash;
}t[maxn];//结构体存单词
bool cmp(const Tmp & a,const Tmp & b)
{
    return a.len<b.len;
}
int ptr;
inline ll GetHash(int j,int i)
{
    return Hash[i]-Hash[j-1]*Pow[i-j+1];
}//计算子串哈希值
int main()
{
    scanf("%s",str+1);
    int n=strlen(str+1),m;
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%s",tmp+1);
        t[i].len=strlen(tmp+1);
        for(int j=1;j<=t[i].len;++j)
            t[i].Hash=t[i].Hash*b+tmp[j];
    }
    sort(t+1,t+1+m,cmp);
    for(int i=1;i<=n;++i)
        Pow[i]=(Pow[i-1]*b);
    for(int i=1;i<=n;++i)
    {
        u[++ptr]=str[i],Hash[ptr]=Hash[ptr-1]*b+u[ptr];
        while(ptr<t[1].len&&i<n)u[++ptr]=str[++i],Hash[ptr]=Hash[ptr-1]*b+u[ptr];
        //确保栈中字符数量大于最小的单词长度
        for(int j=1;j<=m&&ptr;++j)
            if(ptr-t[j].len+1>=1&&GetHash(ptr-t[j].len+1,ptr)==t[j].Hash){ptr-=t[j].len;}
            //匹配操作，若匹配则出栈
    }
    for(int i=1;i<=ptr;++i)
        putchar(u[i]);
    puts("");
    return 0;
}

```

第一次发题解求过...谢谢了

---

## 作者：warzone (赞：15)

写这一题之前先看这一题,

[P4824 [USACO15FEB]Censoring (Silver) 审查(银)](https://www.luogu.org/problem/P4824)

刚刚那道题的AC思路是这样的：

- KMP扫描字符串S,用栈存下扫过的部分,

    及当时字符串T匹配到的位置id

- 如果匹配成功,则在栈中删除串T,同时id更新为栈顶的id

   ####     原因:删除子串后出现的新子串只会在接合处产生
    
- 匹配完后输出栈即可,时间复杂度O(n)

既然刚才单模式串我们是用KMP+栈完成的,

那么当前的多模式串我们可用**AC自动机+栈**O(n)轻松完成,做法相同

### AC代码(318ms,15.93MB)

```cpp
#include<cstdio>
using namespace std;
inline unsigned int read(){
    register char c=getchar();
    while('0'>c||c>'9')c=getchar();
    register unsigned int a=0;
    while('0'<=c&&c<='9'){
        a=a*10+c-'0';
        c=getchar(); 
    }
    return a;
}//快读(尽管基本没用) 
/*************队列和栈******************/
template<typename type>class queue{
    private:
        type *all;
        unsigned int head,tail,length;
    public:
        queue(const unsigned int size){
            all=new type[size];
            length=size;
            head=1;
            tail=0;
        }
        ~queue(){delete[] all;}
        inline void push(type read){
            tail++;
            if(tail==length) tail=0;
            all[tail]=read;
        }
        inline void pop(){
            head++;
            if(head==length) head=0;
        }
        inline bool empty(){return head==tail+1;}
        inline type front(){return all[head];}
};
template<typename type>class stack{
    public:
        unsigned int size;
        type *t;
        stack(const unsigned int&length){
            t=new type[length+1];
            size=0;
        }
        ~stack(){delete[] t;}
        inline void push(type infor){
            size++;
            t[size]=infor;
        }
        inline void pop(const unsigned int&length){
        	size-=length;
        }
        inline bool empty(){return size==0;}
        inline type top(){return t[size];}
};
/***************************************/
struct pair{
    char c;
    unsigned int id;
}pa;//栈存入的数据 
#define maxn 131072
char *q;
#define readstring(q)    \
    do{	\
        q=new char[maxn];	\
        scanf("%s",q);	\
    }while(0);

/*******************字典树Trie***********************/ 
class Trie{
    private:
        struct point{
            unsigned int next[26],nxt,floor;
            bool b;
            point(){
                for(register int i=0;i<26;i++)
                    next[i]=0;
                b=0;
            }
        }*all;
        int size;
    public:
        Trie(const int&length){
            all=new point[length+1];
            size=0;
            all[0].nxt=0;
            all[0].floor=0;
        }
        ~Trie(){delete[] all;} 
        inline void read(){//读入模式串T并建立字典树 
            register unsigned int p=0;
            register char c=getchar();
            while('a'>c||c>'z') c=getchar();
            for(;'a'<=c&&c<='z';c=getchar()){
                c-='a';
                if(all[p].next[c]==0){
                    size++;
                    all[p].next[c]=size;
                    all[size].floor=all[p].floor+1;
                }
                p=all[p].next[c];
            }
            all[p].b=1;
        }
        inline void getnxt(){//构造失配指针,转化为Trie图 
            queue<unsigned int>q(size+2);
            for(register char i=0;i<26;i++){
                if(all[0].next[i]){
                    all[all[0].next[i]].nxt=0;
                    q.push(all[0].next[i]);
                }
            }
            register int p=q.front(),nextnxt;
            for(;!q.empty();p=q.front()){
                q.pop();
                for(register int i=0;i<26;i++){
                    nextnxt=all[all[p].nxt].next[i];
                    if(all[p].next[i]!=0){
                    all[all[p].next[i]].nxt=nextnxt;
                        q.push(all[p].next[i]);
                    }
                    else all[p].next[i]=nextnxt;
                }
            }
        }
        inline void AC_auto(){//匹配 
            stack<pair> s(maxn);
            pa.id=0;
            register int i;
            for(i=0;'a'<=q[i]&&q[i]<='z';i++){
                pa.c=q[i]-'a';
                pa.id=all[pa.id].next[pa.c];//匹配下行 
                s.push(pa);//把匹配的位置存入栈 
                if(all[pa.id].b){
                    s.pop(all[pa.id].floor);
                    if(s.empty()) pa.id=0;
                    else pa=s.top();
                }//匹配成功,弹出栈 
            }
            delete q;
            for(i=1;i<=s.size;i++)
            	putchar(s.t[i].c+'a');//输出 
            putchar('\n');
            //注意输出时一定要换行,不然只有93!!!!!!!!!!! 
        }
}; 
/******************************************************/
int main(){
    readstring(q);//输入模式串S 
    const unsigned int n=read();
    Trie tree(maxn);
    for(register unsigned int i=0;i<n;i++) tree.read();
    tree.getnxt();
    tree.AC_auto();
    return 0;
}
```
最后再强调最重要的一点:

## 输出时一定要换行,不然第7个点会WA,只有93!!!

因为这个原因调了三个月QAQ

---

## 作者：yingjz (赞：13)

蒟蒻我又开始写题解了

欢迎访问我的博客 <https://yjzoier.gitee.io/hexo>

---

首先这道题有一个明显的特征:**多模式串匹配**, 所以我们可以建出 **Trie图**(也就是 **AC自动机**)

那么这道题唯一的难点就是所谓的拼合过程, 比如说样例, 匹配过程是这样的:

> beginthe**escape**xecutionatthebreakofdawn 

> beginth**execution**atthebreakofdawn 

> beginthatthebreakofdawn 

其实我们发现, 我们只需要记录在某个点的时候在 **Trie图** 上匹配的位置就可以了, 匹配成功某个单词后, 只需要跳到这个单词的前一个字符的位置即可.

但是我们需要维护一个删除字符串中某一段并且计算位置的操作, 其实我们不需要维护删除操作, 这样会比较复杂, 可以把每一个字符依次压入栈, 删除的时候逐个删除就可以了, 由于每一个字符只会删除一次, 时间就是 $O(n)$

```c++
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 100007;

struct AC{
	int c[N][26], fail[N], val[N], top;
	queue<int> q;
	void ins(char *ch){
		int len = strlen(ch), now = 0;
		for (int i = 0; i < len; ++i){
			int v = ch[i] - 'a';
			if (!c[now][v]) c[now][v] = ++top;
			now = c[now][v];
		}
		val[now] = len;
	}
	void build(){
		for (int i = 0; i < 26; ++i)
			if (c[0][i]){
				q.push(c[0][i]);
				fail[c[0][i]] = 0;
			}
		while (!q.empty()){
			int u = q.front(); q.pop();
			for (int i = 0; i < 26; ++i)
				if (c[u][i]){
					fail[c[u][i]] = c[fail[u]][i];
					q.push(c[u][i]);
				} else c[u][i] = c[fail[u]][i];
		}			
	}
} ac;

int n, top, loc[N], ans[N];
char p[N], s[N];

int main(){
	scanf("%s", s);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i){
		scanf("%s", p);
		ac.ins(p);
	}
	ac.build();
	int len = strlen(s), now = 0;
	for (int i = 0; i < len; ++i){
		loc[i] = now = ac.c[now][s[i] - 'a'];
		ans[++top] = i;
		if (ac.val[now]) {
			top -= ac.val[now];
			now = loc[ans[top]];
		}
	}
	for (int i = 1; i <= top; ++i)
		putchar(s[ans[i]]);
	putchar('\n');
	return 0;
}
```



---

## 作者：KokiNiwa (赞：9)

# [USACO15FEB]Censoring G（AC自动机，可持久化）

## 题目叙述

给你一个文本串，和一大堆模式串，现在进行如下操作：

+ 找到出现位置最靠前的模式串。
+ 删掉它。

保证没有任何一个字符串是另一个字符串的子串。

## 题解

建立`AC`自动机，把文本串放进去匹配。匹配到一个出现过的字符串，把它删掉。具体如何删？搞一个并查集，我们要做的就是区间赋零，并查集里维护下一个是1的点即可。删掉之后，我们发现要走到以前的节点上（其实就是撤销操作。。。），于是考虑用栈可持久化一下以前走到的地方就可以了。然后会发现并不需要并查集，因为只要在栈里记录走到每个字符时，走到了树上的哪个点。最后栈的样子就是答案。

## 代码

+ **`AC`自动机初始化深度时，要给根节点的儿子初始化！！！**
+ **退回的时候注意是否把栈都退完了，如果退完了，则需`now=1`**

```cpp
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
const int maxLen = 1e5 + 5;
struct AcAutomation {
	int tot, ch[maxLen][26], fail[maxLen], dep[maxLen];
	bool tag[maxLen];
	AcAutomation() : tot(1) {}
	void Insert(char *str) {
		int now = 1, len = strlen(str + 1);
		for (int pos = 1; pos <= len; ++pos) {
			if (!ch[now][str[pos] - 'a'])
				ch[now][str[pos] - 'a'] = ++tot;
			now = ch[now][str[pos] - 'a'];
		}
		tag[now] = 1;
	}
	void BuildFail() {
		queue<int> Q;
		while (!Q.empty()) Q.pop();
		fail[1] = 1;
		for (int son = 0; son < 26; ++son) {
			if (ch[1][son]) {
				fail[ch[1][son]] = 1;
				dep[ch[1][son]] = 1;
				Q.push(ch[1][son]);
			} else
				ch[1][son] = 1;
		}
		while (!Q.empty()) {
			int now = Q.front();
			Q.pop();
			for (int son = 0; son < 26; ++son) {
				if (ch[now][son]) {
					fail[ch[now][son]] = ch[fail[now]][son];
					Q.push(ch[now][son]);
					dep[ch[now][son]] = dep[now] + 1;
				} else
					ch[now][son] = ch[fail[now]][son];
			}
		}
	}
	void Check() {
		for (int i = 1; i <= tot; ++i) {
			printf("i : %d fail : %d\n", i, fail[i]);
			for (int son = 0; son < 26; ++son)
				printf("	son : %d node id : %d\n", son, ch[i][son]);
		}
	}
} ac;
int nbSml, top;
char big[maxLen], sml[maxLen];
struct Node {
	int node;
	char ch;
	Node(int p, char c) : node(p), ch(c) {}
	Node() : node(0), ch(0) {}
} stk[maxLen];
int main() {
	scanf("%s%d", big + 1, &nbSml);
	for (int i = 1; i <= nbSml; ++i) {
		scanf("%s", sml + 1);
		ac.Insert(sml);
	}
	ac.BuildFail();
	int bigLen = strlen(big + 1);
	int now = 1;
	for (int pos = 1; pos <= bigLen; ++pos) {
		now = ac.ch[now][big[pos] - 'a'];
		stk[++top] = Node(now, big[pos]);
		if (ac.tag[now]) {
			top -= ac.dep[now];
			if (top) now = stk[top].node;
			else now = 1;
		}
	}
	for (int i = 1; i <= top; ++i) printf("%c", stk[i].ch);
	printf("\n");
	return 0;
}
```

## 知识点

+ 简陋的可持久化可以用栈实现（同样的东西还有，可撤销并查集。。。）。

---

## 作者：huangjinxiu (赞：7)

已知的 hash 题解的复杂度都是假的,蒟蒻来一篇复杂度正确的 hash 做法，复杂度 $O(|s|\sqrt n)$。

将列表中的单词 $t_i$ 按照长度从大到小排序（长度长的起点更靠前），然后
仿照弱化版 [P4824](https://www.luogu.com.cn/problem/P4824) 的做法，每次加入一个 s 中的字符用 hash 依次判断列表中的单词是否出现过。这样的时间复杂度是 $O(|s|n)$。

考虑优化上述做法，根据经典结论，记 $t_i$ 的长度为 $cnt_i$。 则 $cnt_i$ 的种类数不超过 $\sqrt{ \sum |t_i|}$ 。我们开一个数组存下那些长度出现过，然后依次判断对应长度的 $t_i$ 是否出现过即可。细节在代码注释里。

```cpp
#include<bits/stdc++.h>
#define ull unsigned long long 
using namespace std;
const ull B=131;
unordered_map<ull,bool> mp;//判断对应hash值是否出现 
const int N=100005;
int n,m,len,tot,top,numlen[N];
//numlen记录出现过的长度，top是关于其的指针
//len是关于hs的指针
//tot是关于ans的指针 
string tmp,s;char ans[N];ull hs[N],pw[N];
void make_hash(string &s){
	int n=s.length();
	ull res=0;
	numlen[++top]=n;
	for(int i=0;i<n;++i)
		res=res*B+s[i]-'a'+1; 
	mp[res]=1;//记录此hash值出现过 
}
void check(int k){
	if(k>len)return;//如果长度不够直接返回 
	ull hash=hs[len]-hs[len-k]*pw[k];//这一段的hash值 
	if(!mp.count(hash))return;//判断是否出现 
	tot-=k,len-=k;//出现过则删除这段 
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>tmp>>n;while(n--){cin>>s;make_hash(s);}
	m=tmp.length();tmp=" "+tmp;pw[0]=1;
	for(int i=1;i<=m;++i)pw[i]=pw[i-1]*B;
	sort(numlen+1,numlen+1+top); 
	top=unique(numlen+1,numlen+1+top)-numlen-1;//去重 
	for(int i=1;i<=m;++i){
		ans[++tot]=tmp[i];++len;
		hs[len]=hs[len-1]*B+tmp[i]-'a'+1;
		for(int j=top;j>=1;--j)
			check(numlen[j]);//从长到短依次check 
	}
	for(int i=1;i<=tot;++i)putchar(ans[i]);
	return 0;
}
```

---

## 作者：Stella_Yan (赞：6)

为什么楼下奆佬都用栈啊QwQ

这题用链表也可以啊

先把单词建成ac机，然后把文章放进去跑一遍，删除的时候用链表标记就可以了。

**但是这里有个问题：**

删除完之后，$i$还要继续增加，但是$u$（自动机中的节点）还是现在的，所以要把$u$还原到删除之前的状态。

以样例为例：

```
begintheescapexecutionatthebreakofdawn 
2 
escape 
execution 

```
第一次匹配到$escape$，此时$i$在$13$（也就是字符$p$的位置），前面与后面接在一起了，要匹配$execution$，但此时$u$还是在匹配完$escape$（也就是$i$在$p$的位置）时的位置，不能继续匹配，需要调到$execution$的开头时的位置才可以继续匹配，所以需要再开一个$bk$数组存储当匹配到第$i$位时，$u$的位置。

code:
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char wz[5200010];//文章
char dc[5200010];//单词
int ch[5200010][30];//Trie树,ch[u][i]表示u号节点的转移边i连接的节点
int bo[5200010];//结尾标记
int ans[5200010];
int T;
int n,m;
int tot=1;//节点个数
bool bs=0;//开头的处理（如果单词出现在开头的话就会出锅，要单独处理）
int que[5200010];
int nxt[5200010];//失配指针
int f[5200010];
int pre[5200010];//链表的下一个（这里nxt用掉了只能用pre，由于英文不好搞反了，本来应该是上一个的）
int per[5200010];//上一个
int bk[5200010];//bk
int ff(char c){//把字符转换为数字
	return c-'a';
}
void insert(char *s){//插入
	int u=1;
	int len=strlen(s);
	for(int i=0;i<len;i++){
		int c=ff(s[i]);
		if(!ch[u][c]){
			ch[u][c]=++tot;
		}
		u=ch[u][c];
	}
	bo[u]++;
	f[u]=len;
}
void bfs(){//构建失配边
	nxt[1]=0;
	for(int i=0;i<26;i++){
		ch[0][i]=1;
	}
	que[1]=1;
	for(int head=1,tail=1;head<=tail;head++){
		int u=que[head];
		for(int i=0;i<26;i++){
			if(!ch[u][i]){
				ch[u][i]=ch[nxt[u]][i];
			}
			else{
				que[++tail]=ch[u][i];
				nxt[ch[u][i]]=ch[nxt[u]][i];
			}
		}
	}
}
void query(){//查询
	int u=1;
	int len=strlen(wz);
	for(int i=0;i<len;i++){
		pre[i]=i+1;
		per[i]=i-1;
	}//初始化
	for(int i=0;i<len;i=pre[i]){
		int c=ff(wz[i]);
		u=ch[u][c];
		bk[i]=u;//标记
		if(bo[u]){//如果匹配到了
			int pr=i;//pr代表i往前跳m个位置（也就是找到单词时单词开头的位置）
			for(int k=1;k<=f[u];k++){
				pr=per[pr];
			}
			if(pr<0){//注意！如果往前跳m位时pr<0，就说明在开头时就发现了单词
				pr=0;
				bs=1;
			}
			int now=pre[i];
			pre[pr]=now;
			per[now]=pr;//把中间一段删掉
			u=bk[pr];
		}
	}
}
int main() {
	tot=1;
	scanf("%s",wz);
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%s",dc);
		insert(dc);//插入
	}
	bfs();
	query();
	int len=strlen(wz);
	for(int i=0;i<len;i=pre[i]){
		if(i==0 && bs) continue;//如果有开头标记说明开始那一段已经删掉了，要跳过
        				//不然就会多输出一个字符
		printf("%c",wz[i]);
	}
	printf("\n");//第七个点有坑，要换行...
	return 0;
}

```

---

## 作者：FourteenObsidian (赞：6)

用哈希做的，自认为码量较小：

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[10000001],t[10000001],u[10000001];
unsigned long long ha[10000001],hash[100000001],powe[10000001];
int n,t_len[100000001];
int base=2333333;
int main(){
	powe[0]=1;
	hash[0]=0;
	scanf("%s%d",s+1,&n);
	int cnt=0,s_len=strlen(s+1);
	for(int i=1;i<=n;i++){
		scanf("%s",t+1);
		t_len[i]=strlen(t+1);
	for(int j=1;j<=t_len[i];j++){
		if(!powe[j])
			powe[j]=powe[j-1]*base;
		ha[i]*=base;//求各个单词的哈希值
		ha[i]+=(unsigned long long)t[j];
	}
	}
	for(int i=1;i<=s_len;i++){
		u[++cnt]=s[i];
		hash[cnt]=hash[cnt-1]*base+(unsigned long long)s[i];
		for(int j=1;j<=n;j++){
		if(ha[j]==hash[cnt]-hash[cnt-t_len[j]]*powe[t_len[j]])//比较
                                                        //哈希值是否相等
			cnt-=t_len[j];//栈顶指针下压，弹出此单词
		}
		
	}
	for(int i=1;i<=cnt;i++)
		printf("%c",u[i]);
	printf("\n");//一定要换行！！！
	return 0;
}
```

---

## 作者：crashed (赞：5)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/P3121)看题目。 
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;建议先去把孪生题[[USACO15FEB]Censoring (Silver) 审查(银)](https://www.luogu.org/problem/P4824)给~~水过去~~做了。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后考虑写这一道题。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;看到一个文本串，多个模式串的题，不难想到$AC$自动机。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后考虑如何对$AC$自动机魔改之后做这一道题。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑用一个指针$p$存下来$Trie$上面的位置。如果加入一个字符之后，$p$指向了一个带有终止标记的节点，我们显然就要把指向的这个节点所代表的模式串从文本串中删除。考虑这个操作的实际含义。实际上，我们相当于进行了一步回溯——假如当前位于$T_i$，当前需要删除的长度为$l$，我们就相当于重新走到了这个单词的$i-l$的位置，并且我们下一步就会直接加入字符$i+1$，而不是$i-l+1$了。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;不难想到用一个数组$tp[i]$，表示走到$T_i$时候$p$的位置，这样回溯的时候就可以直接套用原来的信息了。
# 代码
```cpp
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXS = 1e5 + 5, MAXL = 1e5 + 5;

template<typename _T>
void read( _T &x )
{
    x = 0;char s = getchar();int f = 1;
    while( s < '0' || '9' < s ){ if( s == '-' ) f = -1; s = getchar(); }
    while( '0' <= s && s <= '9' ){ x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar(); }
    x *= f;
}

template<typename _T>
void write( _T x )
{
    if( x < 0 ){ x = -x, putchar( '-' ); }
    if( 9 < x ){ write( x / 10 ); }
    putchar( x % 10 + '0' );
}

queue<int> q;

int trie[MAXL][26], fail[MAXL], dep[MAXL];
//dep用于回溯时候得到字符串的长度 
int tmp[MAXS];
char S[MAXS], str[MAXL], ans[MAXS];
int N, siz = 1;
bool ending[MAXL];

void insert( const char *s )
{
	int len = strlen( s + 1 ), p = 1, indx;
	for( int i = 1 ; i <= len ; i ++ )
	{
		indx = s[i] - 'a';
		if( ! trie[p][indx] ) trie[p][indx] = ++ siz, dep[trie[p][indx]] = dep[p] + 1;
		p = trie[p][indx];
	}
	ending[p] = true;
}

void init()
{
	while( ! q.empty() ) q.pop();
	fail[1] = 0, q.push( 1 );
	int u, v;
	while( ! q.empty() )
	{
		u = q.front(); q.pop();
		for( int i = 0 ; i < 26 ; i ++ )
		{
			if( ! trie[u][i] ) { trie[u][i] = trie[fail[u]][i]; continue; }
			v = fail[u];
			while( v && ! trie[v][i] ) v = fail[v];
			if( trie[v][i] ) fail[trie[u][i]] = trie[v][i];
			else fail[trie[u][i]] = 0;
			q.push( trie[u][i] );
			//由于题目保证了不会有一个串是另一个的子串，所以不用对结尾标记进行转移 
		}
	}
}

int main()
{
	scanf( "%s", S + 1 );
	read( N );
	for( int i = 0 ; i < 26 ; i ++ ) trie[0][i] = 1; ending[0] = false, fail[0] = 0;
	for( int i = 1 ; i <= N ; i ++ ) scanf( "%s", str + 1 ), insert( str );
	init();
	int p = 1, r = 0, L = strlen( S + 1 );
	tmp[0] = 1;
	for( int i = 1, indx ; i <= L ; i ++ )
	{
		indx = S[i] - 'a';
		while( p && ! trie[p][indx] ) p = fail[p];
		if( trie[p][indx] ) p = trie[p][indx];
		r ++;
 		if( ending[p] ) p = tmp[r -= dep[p]];
 		//进行回溯 
		else ans[r] = S[i], tmp[r] = p;
		//向答案加入字符（但并不是最终的答案，之后可能还会删除一些） 
	}
	for( int i = 1 ; i <= r ; i ++ ) putchar( ans[i] );
	puts( "" );
	return 0;
}
```

---

## 作者：FREEH (赞：4)

### P3121总结

### 【题目大意】
- 给出一个字符串和n个字典单词，一旦发现一个字典单词就删除，先输入字典单词优先删除，每次删除后可能再次出现字典单词。求最终的字符串。

### 【解题思路】
1. 明显地，需要先制造一个AC自动机。

2. 把字符串放入AC自动机里跑，如果发现有一个节点是字典单词的结尾，那么就把这段字符串“删除”。如何“删除”呢？总不能用erase吧？！其实可以用一个栈来表示答案：每加入一个字符，就压入栈；每删除一段，就把栈顶直接下拉至这段字符串前，这样就可以表示删除了！

3. 一旦删除了一段字符串，AC自动机里的节点也应该要向上跳。于是又可以建造一个栈表示前一个栈的第i个字符对应的AC自动机节点。那么AC自动机节点应该跳往第二个栈的删除字符串的前一位的节点。

4. 最终答案就是第一个栈。

### 【参考程序】

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
char st[100005],s[100005];
int fail[100005],n,top,heap[100005],sign[100005],L;
struct TRIE{
	int son[27],val;
}trie[100005];
void Fill_in(char *st)
{
	int len=strlen(st),u=0;
	for (int i=0;i<strlen(st);i++)
	{
		int v=st[i]-'a';
		if (!trie[u].son[v])
			trie[u].son[v]=++L;
		u=trie[u].son[v];
	}
	trie[u].val=len;
}
void Build()
{
	queue <int> q;
	for (int i=0;i<26;i++)
		if (trie[0].son[i])
		{
			q.push(trie[0].son[i]);
			fail[trie[0].son[i]]=0;
		}
	while (!q.empty())
	{
		int u=q.front();
		q.pop();
		for (int i=0;i<26;i++)
			if (trie[u].son[i])
			{
				fail[trie[u].son[i]]=trie[fail[u]].son[i];
				q.push(trie[u].son[i]);
			}else
			trie[u].son[i]=trie[fail[u]].son[i];
	}
}
void Check(char *st)
{
	int len=strlen(st),u=0;
	for (int i=0;i<len;i++)
	{
		int v=st[i]-'a';
		u=trie[u].son[v];
		heap[++top]=i;
		sign[top]=u;
		if (trie[u].val)
		{
			top-=trie[u].val;
			if (top <=0) u=0;else
			u=sign[top];
		}
	}
}
int main()
{
	scanf("%s%d",&st,&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%s",s);
		Fill_in(s);
	}
	Build();
	Check(st);
	for (int i=1;i<=top;i++)
		printf("%c",st[heap[i]]);
	return 0;
}

---

## 作者：Refun (赞：4)

一开始的确没啥思路……一看到有栈这个标签就明了了……

果然我还是水平太菜啊

不过一看到栈这个题就没什么思考难度了……就基本全靠细节了

首先把自动机建出来……话说我这几天才发现原来自己建的一直叫trie图

然后一位一位放到自动机上跑。

分两种情况：

1、栈空

   判断是否是根节点的一个儿子即可(即判断是否是单词的第一位)
   
2、栈不为空

   判断当前位能否和上一位匹配，如果不能的话就清空栈(因为有这一位挡着就已经前功尽弃了)
   
然后当当前位匹配到某一位的末尾后，就将这个单词从栈中清空(因为题目说了越靠前出现的越早清空) 

清空栈的时候输出一下就好了(除了匹配到的单词不输出) 

[代码](http://www.cnblogs.com/refun/p/8685682.html)


---

## 作者：Honor誉 (赞：3)

# 双栈+AC自动机
这题其实跟一道KMP算法的题有一些渊源,它就是这道题的简单板。

Clear:
给你两个串A,B，每次在B串中从左到右找串A，并将该子串删除，直到找不到为止，问你能删几次。

样例输入：
abc

abcabcabaabcbccc

样例输出：
5

思路：
开一个栈，每次放入被匹配字符串的一个字符。如果当前栈中字符数量大于等于匹配串的长度，开始匹配，如果有一个单词匹配失败，break掉，继续放字符。
```cpp
#include<bits/stdc++.h>
using namespace std;
int lc,lb,cnt,flag,ans;
char a[10000001];
string b,c;
int main()
{
	cin>>b>>c;
	lb=b.size();
	lc=c.size();
	for(int i=0;i<lc;i++)
	{
		a[++cnt]=c[i];
		if(cnt<b.size())
		{
			continue;
		}
		if(a[cnt]!=b[lb-1])
		{
			continue;
		}
		flag=0;
		for(int i=cnt-lb+1,j=0;i<cnt;i++,j++)//匹配
		{
			if(a[i]!=b[j])
			{
				flag=1;//发现目标串，标记。
				break;
			}
		}
		if(!flag)
		{
			ans++;
			cnt-=lb;//减长度
		}
	}
	printf("%d\n",ans);//输出
	return 0;
}
```
那么经过这题的思考之后，加强版（就是这题）的思路也应该油然而生了——我们同样用栈做，一个栈命名为s2，用来表示当前节点跑到了AC自动机中的trie树哪里了，另一个栈s3，用来表示最后的字符串留下了原字符串的哪些位上的字符。

如果发现当前这一个栈中的字符的后缀是单词，直接减去单词的长度（所以isword要存的是长度）。

剩下就是输出了。

提一件事，末尾记得putchar（"\n"）,否则第7个点玄学WA。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt,s2[100010],s3[100010],n,wei,top;//s2是存root，s3是存剩下的。
string s1,s;
queue<int>q;
struct data
{
    int b[26],fail,isword;//isword用来存s.size。
}a[1000001];
void build(string t)//建trie树
{
    int root=0;
    for(int i=0;t[i];i++)
    {
        int x=t[i]-'a';
        if(!a[root].b[x])a[root].b[x]=++cnt;
        root=a[root].b[x];
    }
    a[root].isword=t.size();
}
int main()
{
    cin>>s;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        cin>>s1;
        build(s1);
    }
    for(int i=0;i<26;i++)
    {
        if(a[0].b[i])
        {
            q.push(a[0].b[i]);
        }
    }
    while(!q.empty())
    {
        int k=q.front();
        q.pop();
        for(int i=0;i<26;i++)
        {
            if(a[k].b[i])
            {
                a[a[k].b[i]].fail=a[a[k].fail].b[i];
                q.push(a[k].b[i]);	
            }else{
            	a[k].b[i]=a[a[k].fail].b[i];
            } 
        }
    }
    int root=0;
    //双栈走起
    while(wei<s.size())
    {
    	int x=s[wei]-'a';
    	root=a[root].b[x];
    	s2[++top]=root;
    	s3[top]=wei;
    	if(a[root].isword)
    	{
    		top-=a[root].isword;
    		if(top==0)
    		{
    			root=top;
    		}else{
    			root=s2[top];
    		}
    	}
    	wei++;
    }
    for(int i=1;i<=top;i++)
    {
    	cout<<s[s3[i]];
    }
    putchar('\n');
    return 0;
}
```
QAQAQAQ

---

## 作者：_HLLY_ (赞：3)

啊，终于过了，

我的做法是ac自动机标准模板+栈+记忆化搜索

因为每个单词遵循后进先出的原则，并且每个字母在ac自动机查找的位置无后效性，所以可以记录每个字母在ac自动机上的位置，用栈维护当前句子；（注：第14个点无比友（dan）善（teng）， 由于每个相同位置插相同字母的结果是相同的，所以可以用记搜优化一下）


愚蠢巨慢的代码：







        
      
        


       
        
    
    
        
    

     
        
        
       
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#include<cstring>
struct ac {
    ac *fail; 
    ac * xia[26];
    int ci,ceng; 
   ac() { 
        fail = NULL;
        ci= 0;
        memset(xia, NULL, sizeof (xia));
    }
} *q[500001],*root;
int hehe,changdu[100001],i,huhu; 
char s1[100001];
int zhen1,zhen2; 
void insert(char *str, ac *root) {
    ac *p = root;
    int i = 0, zimu;
    while (str[i]) {
        zimu = str[i] - 'a';
        if (p->xia[zimu] == NULL)
        {
            p->xia[zimu] = new ac();
        }
        p = p->xia[zimu];
        i++;
    }
    p->ci=++hehe;
}
void shipei(ac *root) {
    int i;
    root->fail = NULL;
    q[zhen1++] = root;
    while (zhen1 != zhen2) {
        ac *now = q[zhen2++];
        ac *p = NULL;
        for (i = 0; i < 26; i++) {
            if (now->xia[i] != NULL) {
                if (now == root)
                    now->xia[i]->fail = root;
                else {
                    p = now->fail;
                    while (p != NULL) {
                        if (p->xia[i] != NULL) {
                            now->xia[i]->fail = p->xia[i];
                            break;
                        }
                        p = p->fail;
                    }
                    if (p == NULL)
                        now->xia[i]->fail = root;
                }
                q[zhen1++] = now->xia[i];
            }
        }
    }
}
ac *jisou[200001][27];
int zhan[100009],zhen;
char ystr[100005];
int zimu;
ac *tui(ac *now)
{      int jishu=0;
zimu = ystr[i] - 'a';
   if(zhan[zhen-1]>=0&&jisou[zhan[zhen-1]][zimu]!=NULL)return jisou[zhan[zhen-1]][zimu];
    while (now->xia[zimu] == NULL && now != root) now = now->fail,++jishu;
        now = now->xia[zimu];
        if(now==NULL)now=root;
       if(zhan[zhen-1]>=0) jisou[zhan[zhen-1]][zimu]=now;
        //if(jishu>2)cout<<i<<" "<<"gg";
        return now;
}
ac *f[100008];
void work()
{    //cout<<"ppp";
   // ac *shang=root;
    zhan[0]=100005;
    f[100005]=root;int fin=strlen(ystr);
    for(i=0;i<fin;i++)
    {
       zhan[++zhen]=i;
       f[i]=tui(f[zhan[zhen-1]]);
       if(f[i]->ci)
       {
           zhen-=changdu[f[i]->ci];
       }
    }
    for(i=1;i<=zhen;i++)
    {
        printf("%c",ystr[zhan[i]]);
    }
}
int main() {
//    freopen("censor.in","r",stdin);
//    freopen("censor.out","w",stdout);
    int n, t;
    scanf("%s", ystr);
        zhen1 = zhen2 = 0;
      root = new ac();
        scanf("%d", &n);
        for(i=1;i<=n;i++){
            scanf("%s",s1);
            insert(s1, root);
            changdu[i]=strlen(s1);
        }
     //   cout<<strlen(ystr)<<" ";
        shipei(root);
        //cout<<"pp";
      work();
    return 0;
}
```

---

## 作者：lahlah (赞：1)

这一题的思路就是手动模拟一个栈，然后用AC自动机匹配就可以了。

如果还是不太明白可以看一看[这道题](https://blog.csdn.net/qq_38944163/article/details/81014977)，现在这题就相当于那道的升级版。

嗯~
就是那个栈来模拟，然后用AC自动机加速匹配即可
太感动了，竟一次过~。

好了，上代码：
```
#include<bits/stdc++.h>
using namespace std;
const int N = 1000005;
const int C = 26;
int ch[N][C],cnt[N],tot,nxt[N],n,t,top,_[N];
char st[N],stt[N],sta[N];
void insert(int x){//AC自动机（字典树trie）的标准插入
	int p=0;
	for(int i=0;i<x;i++){
		if(!ch[p][st[i]-'a']) ch[p][st[i]-'a']=++tot;
		p=ch[p][st[i]-'a'];
	}
	cnt[p]=x;
}
void build(){//建树，不多说
	queue<int>q;
	int p=0;
	for(int i=0;i<C;i++){
		if(ch[p][i]) q.push(ch[p][i]);
	}
	while(!q.empty()){
		p=q.front();q.pop();
		for(int i=0;i<C;i++){
			if(ch[p][i]){
				q.push(ch[p][i]);
				nxt[ch[p][i]]=ch[nxt[p]][i];
			}else ch[p][i]=ch[nxt[p]][i];
		}
	}
}
void find(int x){//这里需要各位认真看看并理解清楚，这是关键
	int p=0,ret=0;
	for(int i=0;i<x;i++){ 
		sta[++top]=stt[i];//手动模拟栈
		p=ch[p][stt[i]-'a'];
		if(cnt[p]){//匹配到了，往回跳（弹栈)。
			top-=cnt[p];
			p=_[top];
		}else _[top]=p;/记录位置，看了上面那篇blog应该会比较清楚
	}
}
int main(){
	scanf("%s",stt);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",st);
		insert(strlen(st));
	} 
	build();
	find(strlen(stt));
	for(int i=1;i<=top;i++) printf("%c",sta[i]);//输出
	return 0;
}
```


---

## 作者：HenryHuang (赞：1)

~~被自己学校OJ的毒瘤测评姬卡到自闭~~

Hash+栈+优化暴力

其实思路也很简单，就是把单词存进一个结构体，记录其哈希值和长度，然后就可以开始匹配了

但是，理论复杂度很高，为$O(n*length)$~~虽然实际体验效果不错~~

所以，~~为了卡过自家学校的OJ~~，加了一点小优化

额外维护一个数组$num[i]$,记录以单词结尾字符的ascll码值为i的单词编号

这样的话，每次遍历的时候的元素个数，就会大大小于单词总个数，会比朴素算法快很多，~~虽然最坏复杂度还是~~~~$O(n*length)$~~

~~**不过还是祝愿我早日肝出AC自动机（我太菜了）**~~

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
#pragma GCC optimize(3)
#pragma G++ optimize(3)
using namespace std;
const int base=131;
char a[1000010],b[1000010];
typedef unsigned long long ull;
char ans[1000010];
int lena,lenb,cnt;
ull ba[1000010];
ull h[1000010];
struct cc{
	int len;
	ull has;
}w[100010];
int g[300][1000],tot[300];
int main()
{
    int n;
    scanf("%s",a+1);
    lena=strlen(a+1);
    scanf("%d",&n);
    for(register int i=1;i<=n;++i)
    {
    	scanf("%s",b+1);
    	w[i].len=strlen(b+1);
    	ba[0]=1;
    	for(register int j=1;j<=w[i].len;++j)
        	w[i].has=w[i].has*base+b[j];//求每个单词的哈希值
        ++tot[b[w[i].len]];
        g[b[w[i].len]][tot[b[w[i].len]]]=i;//统计单词
	}
	for(register int i=1;i<=100000;++i)
		ba[i]=ba[i-1]*base;
    for(register int i=1;i<=lena;++i)
    {
        ++cnt;
        ans[cnt]=a[i];
        h[cnt]=h[cnt-1]*base+a[i];
        int q=tot[a[i]];
        for(register int j=1;j<=q;++j)//优化暴力
        {
        	if(cnt-w[g[a[i]][j]].len>=0&&w[g[a[i]][j]].has==h[cnt]-h[cnt-w[g[a[i]][j]].len]*ba[w[g[a[i]][j]].len])
            	cnt-=w[g[a[i]][j]].len;
		}
    }    
    for(register int i=1;i<=cnt;++i)
	putchar(ans[i]);
	putchar("\n");
    return 0;
} 
```



---

## 作者：Adove (赞：0)

AC自动机在预处理fail的时候预处理下节点对应的匹配串的长度

这样复杂度就是严格$\Theta(n)$的

只需要一个栈，在trie图上跑就可以了

```cpp
#include"cstdio"
#include"cstring"
#include"iostream"
#include"algorithm"
using namespace std;

const int MAXN=1e5+5;
const int siz=26;

int n,cnt;
int q[MAXN],id[MAXN];
char s[MAXN],ch[MAXN],stk[MAXN];
struct Trie{
	int vis,fail,dep,val;
	int sn[siz];
}T[MAXN];

void ins(char *ch)
{
	int ln=strlen(ch+1),nw=0;
	for(int i=1;i<=ln;++i){
		if(!T[nw].sn[ch[i]-'a']) T[nw].sn[ch[i]-'a']=++cnt,T[cnt].dep=T[nw].dep+1;
		nw=T[nw].sn[ch[i]-'a'];
	}++T[nw].vis,T[nw].val=T[nw].dep;
	return;
}

void Getfail()
{
	int hd=1,tl=0;
	for(int i=0;i<siz;++i) if(T[0].sn[i]) q[++tl]=T[0].sn[i];
	while(hd<=tl){
		int nw=q[hd++];
		T[nw].val=max(T[nw].val,T[T[nw].fail].val);
		for(int i=0;i<siz;++i){
			if(T[nw].sn[i]){
				T[T[nw].sn[i]].fail=T[T[nw].fail].sn[i];
				q[++tl]=T[nw].sn[i];
			}else T[nw].sn[i]=T[T[nw].fail].sn[i];
		}
	}return;
}

void slv(char *ch)
{
	int ln=strlen(ch+1),ct=0;
	for(int i=1;i<=ln;++i){
		stk[++ct]=ch[i];
		id[ct]=T[id[ct-1]].sn[ch[i]-'a'];
		ct-=T[id[ct]].val;
	}for(int i=1;i<=ct;++i) putchar(stk[i]);
	puts("");
	return;
}

int main()
{
	scanf("%s",s+1);
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%s",ch+1),ins(ch);
	Getfail();slv(s);
	return 0;
}
```

---

## 作者：大菜鸡fks (赞：0)

时隔一年再次写这题。

思路很裸。就是 建个trie图乱跑，每次弹栈记个位置。弹出一串就跳到栈顶字符对应的trie图节点上。
听说直接自动机会被卡？trie图貌似比较优美

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
struct node{
	int tran[26],fail;
}a[maxn];
char S[maxn],s[maxn];
int top,Stack[maxn],pos[maxn],dep[maxn],n,tot,end[maxn];
inline void insert(){
	int len=strlen(S+1),x=0;
	for (int i=1;i<=len;i++){
		int c=S[i]-'a';
		if (!a[x].tran[c]) a[x].tran[c]=++tot;	
		x=a[x].tran[c];
	}
	end[x]=1; dep[x]=len;
}
inline void init(){
	scanf("%s",s+1); scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%s",S+1),insert();
}
int h,t,q[maxn];
inline void Fail(){
	for (int i=0;i<26;i++) if (a[0].tran[i]) q[++t]=a[0].tran[i];
	while (h<t){
		int x=q[++h];
		for (int i=0;i<26;i++)
			if (!a[x].tran[i]) a[x].tran[i]=a[a[x].fail].tran[i];
				else a[a[x].tran[i]].fail=a[a[x].fail].tran[i],q[++t]=a[x].tran[i];
	}
}
inline void run(){
	int len=strlen(s+1),x=0; 
	for (int i=1;i<=len;i++){
		int c=s[i]-'a'; Stack[++top]=i; x=a[x].tran[c]; pos[top]=x;
		if (end[x]) top-=dep[x],x=pos[top];
	}
	for (int i=1;i<=top;i++) putchar(s[Stack[i]]);
}
int main(){
	init(); Fail(); run();
	return 0;
}
```

---

