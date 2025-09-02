# Vasiliy's Multiset

## 题目描述

Author has gone out of the stories about Vasiliy, so here is just a formal task description.

You are given $ q $ queries and a multiset $ A $ , initially containing only integer $ 0 $ . There are three types of queries:

1. "+ x" — add integer $ x $ to multiset $ A $ .
2. "- x" — erase one occurrence of integer $ x $ from multiset $ A $ . It's guaranteed that at least one $ x $ is present in the multiset $ A $ before this query.
3. "? x" — you are given integer $ x $ and need to compute the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/728a3690d3a76b81fb1ccb07b4c04b8d10b1870d.png), i.e. the maximum value of bitwise exclusive OR (also know as XOR) of integer $ x $ and some integer $ y $ from the multiset $ A $ .

Multiset is a set, where equal elements are allowed.

## 说明/提示

After first five operations multiset $ A $ contains integers $ 0 $ , $ 8 $ , $ 9 $ , $ 11 $ , $ 6 $ and $ 1 $ .

The answer for the sixth query is integer ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/4b442d72cf0f109da9eae35430cf9dc9dfa35fdf.png) — maximum among integers ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/c712973b7cb6a6b393c3b423fc78dda636ebb034.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/e9b3f94b7acd1861f4b82fb60d691b2bd163374e.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/1bf5d0b4ff98720973629f7915ae529e790539ba.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/9023c8bab139f08429005ae47d2d497f5795be9b.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/e21b15be88af70287d01c0b8f13ae0d351197a9c.png).

## 样例 #1

### 输入

```
10
+ 8
+ 9
+ 11
+ 6
+ 1
? 3
- 8
? 3
? 8
? 11
```

### 输出

```
11
10
14
13
```

# 题解

## 作者：npqenqpve (赞：25)

题意：维护可重集，支持插入，删除，查询 $x$ 与集合内某数异或的最大值。

做法：一眼建 Trie 树，插入就正常插入，删除时把路径上的出现次数都减 $1$，然后查询时走 Trie 就行。


---

## 作者：黑影洞人 (赞：13)

 01Trie 模板题

题意：支持插入，删除，求任意两个数的最大异或值。

第一眼想到了线性基，但是发现线性基不支持指定两个数。

于是我们想到了 01Trie 来维护。

插入操作：

获取到每一位的情况后，依次往下找，如果那个点被选过了，那么往下走，否则就新开一个节点，每个节点用计数器统计一下覆盖的次数，方便后面的删除操作。

如果完全插入了，那么就在最后的节点标记一下值，避免反复查找。

```
void insert(int x){
	int u=1;
	for(int i=M;i>=0;i--){
		int v=x>>i&1ll;
		if(!ch[u][v])ch[u][v]=++cnt;
		u=ch[u][v];	
		num[u]++;
	}
	val[u]=x;
}
```

删除操作：

按位依次往下走，然后把点经过的次数减去 $1$ 即可。
```
void del(int x){
	int u=1;
	for(int i=M;i>=0;i--){
		int v=x>>i&1ll;
		u=ch[u][v];	
		num[u]--;
	}
}
```

查询操作：

按位向下找，如果能取反就取反，否则才取正。

```
int querymax(int x){
	int u=1;
	for(int i=M;i>=0;i--){
		int v=x>>i&1ll;
		if(ch[u][v^1]&&num[ch[u][v^1]])u=ch[u][v^1];
		else u=ch[u][v];
	}
	return x^val[u];
}
```
完整代码：

```cpp
#include<cstdio>
#include<algorithm>
#define N 114514
#define M 63
#define int long long
using namespace std;
int n;
struct trie{
	int ch[N*M][2],cnt=1,num[N*M],val[N*M];
	void insert(int x){
		int u=1;
		for(int i=M;i>=0;i--){
			int v=x>>i&1ll;
			if(!ch[u][v])ch[u][v]=++cnt;
			u=ch[u][v];	
			num[u]++;
		}
		val[u]=x;
	}
	void del(int x){
		int u=1;
		for(int i=M;i>=0;i--){
			int v=x>>i&1ll;
			u=ch[u][v];	
			num[u]--;
		}
	}
	int querymax(int x){
		int u=1;
		for(int i=M;i>=0;i--){
			int v=x>>i&1ll;
			if(ch[u][v^1]&&num[ch[u][v^1]])u=ch[u][v^1];
			else u=ch[u][v];
		}
		return x^val[u];
	}
}st;
signed main(){
	scanf("%lld",&n);
	st.insert(0);
	while(n--){
		char s[12];
		int a;
		scanf("%s%lld",s,&a);
		if(s[0]=='+')st.insert(a);
		else if(s[0]=='-')st.del(a);
		else printf("%lld\n",st.querymax(a));
	}
	return 0;
}



```


---

## 作者：Zvelig1205 (赞：4)

# 带删 Trie 树

[题目传送门](https://www.luogu.com.cn/problem/CF706D)

题解翻了一圈，没看到递归实现 Trie 的，是递归不配了吗 qwq？

~~我才不会告诉你是因为我不会用迭代。~~

其实对初学者来说，还是递归比较好理解。

关于插入和查询，此处不再多提，有兴趣的可以看看我的 [这篇题解](https://413020.blog.luogu.org/solution-cf282e)，一个比较标新立异的 01Trie 写法。

虽然查询操作不怎么一样，但是网上的 01Trie 大多和这个题所需要的查询相同。

代码：

```cpp
void insert(int &i,int k,int dep)
{
	if(i==0)i=++cnt;
	T[i].siz++;
	if(dep==31)return;
	insert(T[i].ch[k&1],k>>1,dep+1);
}
int ask(int i,int k,int dep,int sum)
{
	if(dep==31)return sum;
	if(!T[i].ch[(k&1)^1])return ask(T[i].ch[k&1],k>>1,dep+1,sum<<1);
	else return ask(T[i].ch[(k&1)^1],k>>1,dep+1,sum<<1|1);
}
```

至于删除操作，通过观察上述代码可以发现，在这里我们维护一个 `siz` 表示以当前节点为根的子树中包含的数的个数。

插入一个数的时候，路径上的节点 `siz++`。

而删除的时候，其路径上的节点 `siz--`，那么回溯时，如果当前节点的 `siz` 为 0，就可以直接删除此节点。

代码实现就是这样：

```cpp
void remove(int &i,int k,int dep)
{
	T[i].siz--;
	if(dep==31)
	{
		if(!T[i].siz)i=0;
		return;
	}
	remove(T[i].ch[k&1],k>>1,dep+1);
	if(!T[i].siz)i=0;
}
```

不过，动态开点的话，删除节点会导致很多用不到的空节点占用空间，所以我们选择弄一个垃圾场。

就是用一个栈将删除的节点储存下来，然后动态开点的时候从栈里拿点，栈空则新建节点。

其实，带删除的动态开点数据结构都能构建垃圾场（比如 Fhq_Treap）。

只多加一个 `push`：

```cpp
stack<int>bin;
void remove(int &i,int k,int dep)
{
	T[i].siz--;
	if(dep==31)
	{
		if(!T[i].siz)bin.push(i),i=0;
		return;
	}
	remove(T[i].ch[k&1],k>>1,dep+1);
	if(!T[i].siz)bin.push(i),i=0;
}
```

最后，题干上有这么一句话：

>开始时集合中只有一个数 0

所以还要先插入一个 0。

AC Code:

```cpp
const int inf=2e5+7;
int n;
char op[2];
struct Tire01{
	int ch[2],siz;
}T[inf*40];
int cnt,rot;
int chuli(int k)
{//从高位插入，所以要先将整个数高低位翻转
	int s=0,dep=0;
	while(k)s=s<<1|(k&1),k>>=1,dep++;
	while(dep<31)s<<=1,dep++;
	return s;
}
stack<int>bin;//垃圾场
void insert(int &i,int k,int dep)
{
	if(i==0)
	{
		if(bin.empty())i=++cnt;
		else i=bin.top(),bin.pop();
	}
	T[i].siz++;
	if(dep==31)return;
	insert(T[i].ch[k&1],k>>1,dep+1);
}
void remove(int &i,int k,int dep)
{
	T[i].siz--;
	if(dep==31)
	{
		if(!T[i].siz)bin.push(i),i=0;
		return;
	}
	remove(T[i].ch[k&1],k>>1,dep+1);
	if(!T[i].siz)bin.push(i),i=0;
}
int ask(int i,int k,int dep,int sum)
{
	if(dep==31)return sum;
	if(!T[i].ch[(k&1)^1])return ask(T[i].ch[k&1],k>>1,dep+1,sum<<1);
	else return ask(T[i].ch[(k&1)^1],k>>1,dep+1,sum<<1|1);
}
int main()
{
	n=re();insert(rot,0,0);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",op);
		int k=re();k=chuli(k);
		if(op[0]=='+')insert(rot,k,0);
		if(op[0]=='-')remove(rot,k,0);
		if(op[0]=='?')wr(ask(rot,k,0,0)),putchar('\n');
	}
	return 0;
}
```

## 广告

本人的 [Trie 一轮复习](https://www.cnblogs.com/Zvelig1205/p/16703063.html)。

本人的 [Blog](https://www.cnblogs.com/Zvelig1205)。

---

## 作者：堇墨浮华 (赞：4)

### 还没人发题解那本蒟蒻就来发一波啦~（不过这题好像也没几个人做QwQ）
这道题十分~~毒瘤~~ emmm。。。适合**dalao们**练手，像我这样的蒟蒻就是自寻死路了orz，6个小时啊……qwq

首先**dalao们**看到~~这种经典的~~题目，就**一定**能想到字典树。
把读入的数二进制化，那么我们就可以用l表示子结点为0，r表示子结点为1，ul和ur分别表示这个结点包含的（~~无法用语言描述~~）个数。

最后在计算答案的时候，尽量走和当前结点不同的子结点，也就是现在是1，则尽量走0；现在是0，则尽量走1，ans=(ans<<1)+1。如果上述子结点所含个数==0，则必须走和当前相同的子结点，这时ans不必+1。

详见代码(内含注释)：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#define ll long long
#define INF 1<<30
using namespace std;
const int N=200000;
int q,x,w,ans;
ll d[40]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216,33554432,67108864,134217728,268435456,536870912,1073741824};//手动打2的方幂表
struct Node{
    int t,l,r;
    int ul,ur;
};//结构体
char c;
vector <Node> l;//奇怪的vector式存储
int main(){
    l.push_back((Node){0,0,0,0,0});
    w=0;
    for (int i=29;i>=0;i--){//最深达29层
        l[w].ul=INF;
        l[w].l=l.size();//开始时没有为1的子结点，所以只需处理为0的子结点即可
        w=l[w].l;
        l.push_back((Node){0,0,0,0,0});
    }
    l[w].t=INF;//以上为初始化
    scanf ("%d",&q);
    while (q--){
        scanf ("\n");
        scanf ("%c%d",&c,&x);
        if (c=='+'){//新加入一个数
            w=0;
            for (int i=29;i>=0;i--)
                if (x>=d[i]){//走为1的子结点
                    x-=d[i];
                    if (l[w].ur) l[w].ur++,w=l[w].r;//原来这个子结点便存在，则直接把个数+1，w继续往下
                    else{
                        l[w].ur=1;
                        l[w].r=l.size();
                        w=l[w].r;
                        l.push_back((Node){0,0,0,0,0});//原来这个子结点并不存在，则新加入进去
                    }
                }
                else{//走为0的子结点
                    if (l[w].ul) l[w].ul++,w=l[w].l;
                    else{
                        l[w].ul=1;
                        l[w].l=l.size();
                        w=l[w].l;
                        l.push_back((Node){0,0,0,0,0});
                    }//同理，话不多说
                }
            l[w].t++;//这个好像也没什么用，加上去保持队形(huaji)
        }
        else if (c=='-'){//从树中去掉一个数
            w=0;
            for (int i=29;i>=0;i--){
                if (x>=d[i]){
                    x-=d[i];
                    l[w].ur--;
                    w=l[w].r;
                }
                else{
                    l[w].ul--;
                    w=l[w].l;
                }//个数-1，w继续往下
            }
            l[w].t--;//保持队形。。。
        }
        else{//终于到了计算答案的时候了！
            w=0;
            ans=0;
            for (int i=29;i>=0;i--){
                if (x>=d[i]){
                    x-=d[i];
                    if (l[w].ul) ans=(ans<<1)+1,w=l[w].l;//如果现在的结点为1，则尽量走不同的结点，也就是0(如果这个结点上是的个数>0的话)
                    else if (l[w].ur) ans=(ans<<1),w=l[w].r;//迫不得已必须走相同结点，则ans无须+1
                }
                else{
                    if (l[w].ur) ans=(ans<<1)+1,w=l[w].r;
                    else if (l[w].ul) ans=(ans<<1),w=l[w].l;
                }//同理，话不多说
            }
            printf ("%d\n",ans);
        }
    }
    return 0;
}
```

---

## 作者：☯☯枫☯☯ (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF706D)

**算法分析：Trie 树**

题目中唯一的运算是按位异或，我们可以考虑按位异或的本质。既然是一位一位异或，那么我们直接把 $x$ 转化成一个二进制数不就好了吗？

在插入时，我们可以先将 $x$ 转化为一个**32**位二进制数，然后**从高位到低位**插入 Trie 树，并对每个树上每个节点 $p$ 记录一个 $rec_p$ 表示这个节点被 $rec_p$ 个数字使用过。

在查找时，优先沿着**相反的边**向下移动指针，并累加答案即可。

在删除时，对沿途节点的 $rec_p$ 减1即可。

---

**注意**

- 数字必须从高位到低位插入 Trie 树，否则会引起冲突。

- 与一般 Trie 树不同的地方是，本题中不需要打结尾标记（显然每个数都是32位），但是需要额外记录每一个节点被几个数使用。

- 数组记得开大一点，否则容易 RE。

---

下面是~~喜闻乐见的~~代码：
```cpp
#include<bits/stdc++.h>
#define reg register
#define F(i,a,b) for(reg int i=(a);i<=(b);i++)
using namespace std;
inline char get_char(); 
const int N=3e6+10;
int T,n,cnt=1;
int c[40],trie[N][3];
int rec[N];
inline void change(long long x) {
	memset(c,0,sizeof(c));
	int ct=0;
	while(x)c[++ct]=x&1,x>>=1;
}
inline int reply(){
	int p=1,s=0;
	for(reg int i=33;i>=1;i--){
		int &k=c[i];
		s<<=1;
		if(!trie[p][k^1] or !rec[trie[p][k^1]])p=trie[p][k];
		//相反的边走不通 
		else p=trie[p][k^1],s|=1;//走相反的边 
	}
	return s;
}
inline void insert(){//插入 
	int p=1;
	for(reg int i=33;i>=1;i--){
		int &k=c[i];
		if(!trie[p][k])trie[p][k]=++cnt;
		p=trie[p][k],rec[p]++;//记录该节点被几个数用过 
	}
}
inline void _delete(){//删除 
	int p=1;
	for(reg int i=33;i>=1;i--){
		int &k=c[i];
		p=trie[p][k];
		rec[p]--;//减去这个数的贡献 
	}
}
int main() {
	scanf("%d",&n);
	insert();//插入开始时的0 
	while(n--){
		static char c;
		static int x;
		c=get_char();
		scanf("%d",&x);
		change(x);//将x变成二进制数 
		if(c=='?')printf("%d\n",reply());
		else if(c=='+')insert();
		else _delete();
	}
	return 0;
}
inline char get_char(){//读入字符 
	reg char c=getchar();
	while(c!='+' and c!='-' and c!='?')c=getchar();
	return c;
} 
```

[AC](https://www.luogu.com.cn/record/48796683)

欢迎交流讨论，请点个赞哦~

---

## 作者：ironmt (赞：2)

### 蒟蒻第零次发题解
因为要求最大的异或值，所以高位更重要，将每个加进来的数用二进制从高位向低位建trie，每次询问时每位都尽量取不同的二进制数就可以得到最大异或值。其他细节代码里有注释。
```cpp
#include <cstdio>

const int maxi = 200000 * 32 + 7;

int t[maxi][2];
int sum[maxi], qwq[maxi];
int sz = 1; //如果初始成0会wa可以自己感性理解一下
int n;

inline int read()
{
    int s = 0, r = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9')
    {
        s = (s << 3) + (s << 1) + (ch ^ 48);
        ch = getchar();
    }
    return s * r;
}

int main()
{
    n = read();
    char op;
    int num;
    int tmp, p;
    for (int i = 0; i <= n; ++i)
    {
        tmp = 1;
        if (i)
        {
            scanf("\n%c", &op);
            num = read();
        }
        else
        {
            //根据题意先加一个0进去
            op = '+';
            num = 0;
        }
        if (op == '+')
        {
            for (int j = 29; j >= 0; --j)
            {
                //判断当前位是0还是1
                p = 0;
                if ((1 << j) & num)
                    p = 1;
                if (! t[tmp][p])
                    t[tmp][p] = ++sz;
                tmp = t[tmp][p];
                ++sum[tmp];
                //因为可以删除所以有可能只有节点没有值记录前缀
            }
            qwq[tmp] = num; //记录值
        }
        if (op == '-')
            for (int j = 29; j >= 0; --j)
            {
                p = 0;
                if ((1 << j) & num)
                    p = 1;
                tmp = t[tmp][p];
                --sum[tmp];
            }
        if (op == '?')
        {
            for (int j = 29; j >= 0; --j)
            {
                p = 0;
                if ((1 << j) & num)
                    p = 1;
                if (sum[t[tmp][p ^ 1]]) //异或一下就可以1变0，0变1
                    tmp = t[tmp][p ^ 1];
                else
                    tmp = t[tmp][p];
            }
            printf("%d\n", qwq[tmp] ^ num);
        }
    }
    return 0;
}

```

---

## 作者：StupidSeven (赞：1)

## Subject
[题目传送门](https://www.luogu.com.cn/problem/CF706D)

最近学了点01Trie树，来写一篇题解

## Analysis
插入和查询操作是很模板的，查询的原理就是贪心，每次走不一样的，这样异或值可以最大。删除也只需要每次把贡献减掉就好了，总的来说算是一道板子，很适合拿来练手

## Code
```cpp
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define M 200010
#define Maxbit 32
#define int long long
inline int Readint(void){
    int s=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){s=s*10+c-48;c=getchar();}
    return s*f;
}
char opt;
int T,x,num[M*Maxbit],val[M*Maxbit];
int tree[M*Maxbit][2],cnt=1;
void Insert(int x){
	int root=1;
	for(int i=Maxbit;i>=0;i--){
		int idx=x>>i&1;
		if(!tree[root][idx])
			tree[root][idx]=++cnt;
		root=tree[root][idx];
		num[root]++;
	}
	val[root]=x;
	return;
}
void Delete(int x){
	int root=1;
	for(int i=Maxbit;i>=0;i--){
		int idx=x>>i&1;
		root=tree[root][idx];
		num[root]--;
	}
	return;
}
int Query(int x){
	int root=1;
	for(int i=Maxbit;i>=0;i--){
		int idx=x>>i&1;
		if(tree[root][idx^1]&&num[tree[root][idx^1]])
			root=tree[root][idx^1];
		else root=tree[root][idx];
	}
	return x^val[root];
}
signed main(void){
	T=Readint();
	Insert(0);
	while(T--){
		cin>>opt;
		x=Readint();
		if(opt=='+')
			Insert(x);
		if(opt=='-')
			Delete(x);
		if(opt=='?')
			printf("%lld\n",Query(x));
	}
	return 0;
}
```

---

## 作者：Neil_Qian (赞：0)

# Vasiliy's Multiset 题解
一道字典树的模板题。

要维护一颗字典树，使得它可以插入、查询和删除。

**注意：一开始集合中有一个元素 $0$，不要忽视！**

普通的字典树的儿子是字母或数字，而这道题是 $0$ 和 $1$，有一个好处是：在做异或的时候，我们希望选的数的每一位尽量和它的那一位取反。当然，优先满足更高位。如果相反的数没有，则选择另一条路。插入很简单，建议看此类型的模板题，询问代码如下：

```cpp
inline int qry(const int x){
	u=0,res=0;//初始化
	for(int i=30;i>=0;i--){//枚举每一位
		idx=(x&(1<<i))==0?1:0;//获取当前的数值
		if(!ch[u][idx])idx=!idx;//不能最优，选另一个
		else res+=(1<<i);//可以最优，统计答案
		u=ch[u][idx];
	}
	return res;
}
```

但是难点在于删除。在字典树中，我们知道对于一个节点，当它无法匹配插入的数值时，会新开一个点，再插入后面的。我们只需要将节点和下面的节点断开连接，那么那个节点及其儿子节点就不可能被访问到，实现了删除，代码如下：

```cpp
inline void era(const int x){
	u=0;
	for(int i=30;i>=0;i--){
		idx=(x&(1<<i))==0?0:1,t=u;//获取节点的方向
		u=ch[u][idx],tag[u]--;//减少数量
		if(tag[u]==0){ch[t][idx]=0;return;}//这下面只有这一个元素的贡献了，全部删了
	}
}
```

最后，提供完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;const int N=2e5+2;char k;
int Q,x,ch[N*30][3],t,u,idx,res,cnt,tag[N*30];
inline void ins(const int x){
	u=0;
	for(int i=30;i>=0;i--){
		idx=(x&(1<<i))==0?0:1;
		if(!ch[u][idx])ch[u][idx]=++cnt;
		u=ch[u][idx],tag[u]++;
	}
}
inline void era(const int x){
	u=0;
	for(int i=30;i>=0;i--){
		idx=(x&(1<<i))==0?0:1,t=u;
		u=ch[u][idx],tag[u]--;
		if(tag[u]==0){ch[t][idx]=0;return;}
	}
}
inline int qry(const int x){
	u=0,res=0;
	for(int i=30;i>=0;i--){
		idx=(x&(1<<i))==0?1:0;
		if(!ch[u][idx])idx=!idx;
		else res+=(1<<i);
		u=ch[u][idx];
	}
	return res;
}
int main(){
	scanf("%d",&Q),ins(0);
	while(Q--){
		scanf(" %c%d",&k,&x);
		if(k=='+')ins(x);
		else if(k=='-')era(x);
		else printf("%d\n",qry(x));
	}
	return 0;
}
```

感谢您的观看！

---

## 作者：orz_z (赞：0)

### 题目大意

有 $q$ 次操作和一个集合 $A$，开始时集合中只有一个数 $0$，下面有三种类型的操作：

* `+ x`，把 $x$ 插入集合 $A$。
* `- x`，把 $x$ 从集合 $A$ 中删去，保证 $x$ 已存在于集合 $A$ 中。
* `? x`，给一个数 $x$ 在集合 `A` 中找一个 $y$ 使得 $x \operatorname{xor} y$ 最大，并求出这个值。


对于 $100\%$ 的数据，$1\leq q\leq 200000,1\leq x_i\leq10^9$。

### 解题思路

看到异或和一些添加删除操作，首先可以想到是 `01 trie`。

对于询问，要使得异或值最大，可以二进制位从大到小贪心选不同的。

另外，由于 $x$ 是在线给出的，且要输出一个值，也就是说不能简单地判断。

考虑对每一个数在 `trie` 上弄标记，并在结尾处记录这个数的位置。

每次删除只需要删标记，跳的时候看一下有没有标记即可。

注意数组大小。

### CODE

```cpp
#include <bits/stdc++.h> 
using namespace std;

const int _ = 200007;

#define int long long

inline int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while(c < '0' || c > '9')
	{
		if(c == '-') f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}

char opt;

int T, x, num[27 * _], val[27 * _];

int cnt = 1, tr[27 * _][2];

void Insert(int x)
{
	int p = 1;
	for(int i = 32; i >= 0; --i)
	{
		int v = x >> i & 1;
		if(!tr[p][v])
			tr[p][v] = ++cnt;
		p = tr[p][v];
		num[p]++;
	}
	val[p] = x;
}

void Delete(int x)
{
	int p = 1;
	for(int i = 32; i >= 0; --i)
	{
		int v = x >> i & 1;
		p = tr[p][v];
		num[p]--;
	}
}

int Query(int x)
{
	int p = 1;
	for(int i = 32; i >= 0; --i)
	{
		int v = x >> i & 1;
		if(tr[p][v ^ 1] && num[tr[p][v ^ 1]])
			p = tr[p][v ^ 1];
		else 
			p = tr[p][v];
	}
	return x ^ val[p];
}

signed main()
{
	T = read();
	Insert(0);
	while(T--)
	{
		cin >> opt;
		x = read();
		if(opt == '+')
			Insert(x);
		if(opt == '-')
			Delete(x);
		if(opt == '?')
			printf("%lld\n", Query(x));
	}
	return 0;
}
```





---

