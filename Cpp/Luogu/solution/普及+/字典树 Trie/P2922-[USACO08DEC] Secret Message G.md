# [USACO08DEC] Secret Message G

## 题目描述

Bessie is leading the cows in an attempt to escape! To do this, the cows are sending secret binary messages to each other.

Ever the clever counterspy, Farmer John has intercepted the first $b_i$ ($1 \le b_i \le 10,000$) bits of each of $M$ ($1 \le M \le 50,000$) of these secret binary messages.

He has compiled a list of $N$ ($1 \le N \le 50,000$) partial codewords that he thinks the cows are using. Sadly, he only knows the first $c_j$ ($1 \le c_j \le 10,000$) bits of codeword $j$.

For each codeword $j$, he wants to know how many of the intercepted messages match that codeword (i.e., for codeword $j$, how many times does a message and the codeword have the same initial bits). Your job is to compute this number.

The total number of bits in the input (i.e., the sum of the $b_i$ and the $c_j$) will not exceed  $500,000$.

贝茜正在领导奶牛们逃跑．为了联络，奶牛们互相发送秘密信息．

信息是二进制的，共有 $M$（$1 \le M \le 50000$）条，反间谍能力很强的约翰已经部分拦截了这些信息，知道了第  $i$ 条二进制信息的前 $b_i$（$1 \le b_i \le 10000$）位，他同时知道，奶牛使用 $N$（$1 \le N \le 50000$）条暗号．但是，他仅仅知道第 $j$ 条暗号的前 $c_j$（$1 \le c_j \le 10000$）位。

对于每条暗号 $j$，他想知道有多少截得的信息能够和它匹配。也就是说，有多少信息和这条暗号有着相同的前缀。当然，这个前缀长度必须等于暗号和那条信息长度的较小者。

在输入文件中，位的总数（即 $\sum b_i + \sum c_i$）不会超过 $500000$。

## 说明/提示

Four messages; five codewords. 

The intercepted messages start with 010, 1, 100, and 110.

The possible codewords start with 0, 1, 01, 01001, and 11.


0 matches only 010: 1 match

1 matches 1, 100, and 110: 3 matches

01 matches only 010: 1 match

01001 matches 010: 1 match

11 matches 1 and 110: 2 matches


## 样例 #1

### 输入

```
4 5 
3 0 1 0 
1 1 
3 1 0 0 
3 1 1 0 
1 0 
1 1 
2 0 1 
5 0 1 0 0 1 
2 1 1 
```

### 输出

```
1 
3 
1 
1 
2 
```

# 题解

## 作者：户山香澄 (赞：89)

典型的字典树统计题。

首先是读入。这道题全部采用2进制，也就是说只有0和1两个字符/数字，那么我们直接把它们当成字符用好了。

然后建树，也是一般的字典树建树法，只是把字母换成了0和1而已，这里不多讲。

一边建树，一边在这串数列中走过的路径中的sum+1，sum代表有sum个单词（？）经过这个节点。

当一个单词（？）插完以后，在当前节点（即该单词的最后一个数字）的end上+1，end代表有end个单词（？）在这个节点终结。

注意可能会有重复的信息，也就是说可能会有多条信息在同一个节点终结，所以这里的end是数字而不是布尔型。

然后读入待查询的信息，就像普通字典树查询一样地往下走，一边走一边把沿途的end值加起来。

循环结束，有两种情况：一是该信息全部走完，二是再往下走没有与该信息相符的节点了。

第一种情况，当前的答案要减去当前节点的end值再加上当前节点的sum值（想一想，为什么）。

第二种情况，直接输出答案。

显然比待查询的信息长的信息，如果与待查询信息有相同前缀的话，一定会经过待查询信息终结的节点。

如果待查询信息无法终结，说明没有比该信息长且前缀是该信息的信息，所以不能加上sum。

如果信息终结，那么当前节点的sum值所包含的信息一定与其有相同前缀，但sum所包含的信息有可能刚好在该节点终结，

所以要减去end值。

···C++




    
    
```cpp
#include<bits/stdc++.h>
using namespace std;
struct cow{
    int nex[2],sum,end;
}t[500001];
int a[10001];
inline int read()
{
    int data=0,w=1; char ch=0;
    while(ch!='-' && (ch<'0' || ch>'9')) ch=getchar();
    if(ch=='-') w=-1,ch=getchar();
    while(ch>='0' && ch<='9') data=data*10+ch-'0',ch=getchar();
    return data*w;
}
int main()
{
    ios::sync_with_stdio(false);
    int n,m,js=1;
    memset(t,0,sizeof(t));
    m=read();n=read();
    for (int i=1;i<=m;i++)
    {
        int len;
        len=read();
        for (int j=1;j<=len;j++) a[j]=read();
        int now=1;
        for (int j=1;j<=len;j++) 
        {
            if (t[now].nex[a[j]]!=0) now=t[now].nex[a[j]];
            else
            {
                js++;
                t[now].nex[a[j]]=js;
                t[js].nex[1]=t[js].nex[0]=0;
                now=js;
            }
            t[now].sum++;
        }
        t[now].end++;
    }
    for (int i=1;i<=n;i++)
    {
        int len;
        len=read();
        for (int j=1;j<=len;j++) a[j]=read();
        int now=1,ans=0;
        bool flag=true;
        for (int j=1;j<=len;j++)
        {
            if (t[now].nex[a[j]]!=0) now=t[now].nex[a[j]];
            else 
            {
                flag=false;
                break;
            }
            ans+=t[now].end;
        }
        if (!flag) cout<<ans<<endl;
        else cout<<ans+t[now].sum-t[now].end<<endl;
    } 
    return 0;
} 
···
```

---

## 作者：yue__z (赞：68)

题意

给出m个字符串，n个要查找的字符串，

输出n行，表示在 每个给出的字符串中 找到 与要查找的字符串前缀相同的个数

枚举会TLE，这里可以用 字典树

因为输入的只有0和1，所以可以用bool做

首先，定义一个bool数组，把给出的字符串一条条插在字典树里
再定义一个find 函数，一条一条查找

### 字典树的构建

推荐网站[https://blog.csdn.net/jiutianhe/article/details/8076835]

假设我要查询的单词是abcd，那么在他前面的单词中，以b，c，d，f之类开头的我显然不必考虑。而只要找以a开头的中是否存在abcd就可以了。同样的，在以a开头中的单词中，我们只要考虑以b作为第二个字母的，一次次缩小范围和提高针对性，这样一个树的模型就渐渐清晰了。

好比假设有b，abc，abd，bcd，abcd，efg，hii 这6个单词，我们构建的树就是如下图这样的：

![](https://cdn.luogu.com.cn/upload/pic/38484.png)
 
ok，如上图所示，对于每一个节点，从根遍历到他的过程就是一个单词，如果这个节点被标记为红色，就表示这个单词存在，否则不存在。

那么，对于一个单词，我只要顺着他从根走到对应的节点，再看这个节点是否被标记为红色就可以知道它是否出现过了。把这个节点标记为红色，就相当于插入了这个单词。
插入的平均时间复杂度亦为O（logN）

这个红的点表示一个完整的字符串，用bo  数组记录。

因为此题是算前缀相同的个数，所以，我们定义一个sum数组记录该节点有多少字符串经过

![](https://cdn.luogu.com.cn/upload/pic/38485.png)
 
以样例为例，查找的字符串为0 1，箭头所指的位置，但前缀相同但长度更长的字符串也要加进去

例如0 1 0这个字符串，这时，个数为原来的ans + sum(经过这个节点的字符串个数) - bo(以当前这个节点为结束点的字符串个数)

下放代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,ch[500001][3],tot=1,bo[500001],sum[500001],x;
bool p[500001];
///ch[u][i]表示节点u的i字符指针指向的节点，若值为0，表示没有这个节点
inline int read(){
    int data=0,w=1; char ch=0;
    while(ch!='-' && (ch<'0' || ch>'9')) ch=getchar();
    if(ch=='-') w=-1,ch=getchar();
    while(ch>='0' && ch<='9') data=data*10+ch-'0',ch=getchar();
    return data*w;
}///快读

void add(bool p[]) {//插入字符串
	int u=1;
	for(int i=1; i<=k; i++) {
		int c=p[i];
		if(ch[u][c]==-1)ch[u][c]=++tot;
		u=ch[u][c];///它指向它的子节点
		sum[u]++;///经过该节点字符串个数
	}
	bo[u]++;///该字符串以u结尾
}

int find(bool p[]) {
	int u=1;
	int res=0;
	for(int i=1; i<=k; i++) {
		int c=p[i];
		if(ch[u][c]==-1)return res;
		u=ch[u][c];
		res+=bo[u];///加上与当前节点为结束的个数
	}
	return res-bo[u]+sum[u];//加上前缀相同且长度比它长的字符串个数
}

int main() {
	int x;
	m=read();
	n=read();
	memset(ch,-1,sizeof ch);//因为输入为0或1，所以初始值为-1
	for(int i=1; i<=m; i++) {
		k=read();
		for(int j=1; j<=k; j++) {
			p[j]=read();
		}
		add(p);
	}
	for(int i=1; i<=n; i++) {
		k=read();
		for(int j=1; j<=k; j++) {
			p[j]=read();
		}
		printf("%d\n",find(p));
	}
}
````

第一次发题解，谢谢dalao们的观看orz

---

## 作者：奔波儿霸 (赞：26)

这是我的第一篇题解，莫名的有点小鸡冻\\(≧▽≦)/

安利一下**[蒟蒻自己的blog](http://www.cnblogs.com/bljfy/)**

欢迎大家前来翻牌子哦^_^

### 题目大意

约翰拦截到了奶牛的密码，并且他有一个密码本，里面不完全的记录了奶牛逃跑用的密码，他要从里面比对出密码。

密码都是二进制的，为$0$或$1$。

### 解题思路

首先我们从样例里面就能分析出这个题的坑点。

看样例中第二组的第5个二进制串``5 0 1 0 0 1`` ，很显然它比$trie$树中的二进制串都要长，如果按照一般的$trie$来写，是找不出它的前缀的。

所以我们要在结构体中添加一个成员$sign$。

那么$sign$是干什么的呢？

它是用来标记这个二进制串是否是一个完整的串。注意要用$int$形的变量。因为可能用完全相同的串出现在树中。

而我们只需要在$insert$操作时加上后面这一句:``rt->sign++;``

还需要进行的改动就是在查询的函数中统计一下$sign$的值。再者就是要考虑$sign$大于一的情况

### 完整代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

struct node{
    int count;
    node *next[5];
    int sign;
}*root;
int n, m, len;
char s[10008];

node *build() {
    node *k = new(node);
    k->count = 0;
    k->sign = 0;
    memset(k->next, NULL, sizeof(k->next));
    return k;
}

inline int read()
{
    int data=0,w=1; char ch=0;
    while(ch!='-' && (ch<'0' || ch>'9')) ch=getchar();
    if(ch=='-') w=-1,ch=getchar();
    while(ch>='0' && ch<='9') data=data*10+ch-'0',ch=getchar();
    return data*w;
}

inline void insert(char *s) {
    node *rt = root;
    for(register int i=0; i<len; i++) {
        int id = s[i]-'0';
        if(rt->next[id] == NULL) {
            rt->next[id] = build();
        }
        rt = rt->next[id];
        rt->count++;
    }
    rt->sign++;
}

inline int find(char *s) {
    node *rt = root;
    int k = 0;
    bool mark = false;
    for(register int i=0; i<len; i++) {
        int id = s[i]-'0';
        if(rt->next[id] == NULL) {
            mark = true;
            break;
        }
        rt = rt->next[id];
        k += rt->sign;
    }
    if(mark == false) k+=rt->count-rt->sign;
    return k;
}

int k;

int main() {
    root = build();
    n = read(), m = read();
    for(register int i=1; i<=n; i++) {
        memset(s, NULL, sizeof(s));
        len = read();
        for(register int j=0; j<len; j++) {
            k = read();
            if(k == 0) s[j] = '0';
            if(k == 1) s[j] = '1';
        }
        insert(s);
    }
    for(register int i=1; i<=m; i++) {
        memset(s, NULL, sizeof(s));
        len = read();
        for(register int j=0; j<len; j++) {
            k = read();
            if(k == 0) s[j] = '0';
            if(k == 1) s[j] = '1';
        }
        int ans = find(s);
        printf("%d\n", ans);
    }
}
```

求管理大大给个通过吧QAQ
笔芯❤

---

## 作者：LB_tq (赞：11)

 蒟蒻刚刚学字典树，发篇题解巩固一下。
 
 所谓字典树，就是利用好每一个字符串与其他字符串的公共前缀构建出一棵树，在每个字符串结束的节点处打上标记，提高查询的效率。
 
 这道题求的是每条密码与几条信息有公共前缀，那么我们可以用信息构建出一颗Trie树，把每条密码当作查询的字符串。
 
 但由于比密码长的信息也要计数，所以我一开始用的递归查找这一层下的单词数。但这样会超时。。。
 
 考虑字典树的构建过程：如果该单词结尾处下还有字符串，那么下面的字符串肯定也与该密码有着相同前缀。于是我们可以在构建过程中记录下经过每个节点的单词数，直接计算即可。
 
 下面是代码
 ```
#include<iostream>
#include<cstdio>
using namespace std;
int n,m,t=1;//t是节点数
int b[500010],a[10010],d[500010];//b存储字符串结尾标记，d存储经过该节点的字符串数
int c[500010][2];//c存储Trie树
void tire(int x,int a[]){
	int u=1;
	for(int i=1;i<=x;i++){
		if(c[u][a[i]]==0)
			c[u][a[i]]=++t;
		u=c[u][a[i]];
		d[u]++;//记录经过此点的字符串数量
	}
	b[u]++;//此处要注意：有可能存在相同的信息，所以b数组要++而不是=1（否则只有7分。。。）
	return;
}//构建
int tai(int x,int a[]){//查询
	int u=1,ans=0,f=0;
	for(int i=1;i<=x;i++){
		if(c[u][a[i]]!=0)
			u=c[u][a[i]];
		else{
			f=1;//f记录是否循环完密码长度
			break;
		}
		if(b[u]!=0)
			ans+=b[u];
	}
	if(f==0){
		ans+=d[u];
		if(b[u]!=0)
			ans-=b[u];//如果当前u处有单词结尾，那么多加了一次，减去
	}
	return ans;
}
int main(){
	cin>>m>>n;
	int x;
	for(int i=1;i<=m;i++){
		cin>>x;
		for(int j=1;j<=x;j++)
			cin>>a[j];//读入信息
		tire(x,a);
	}
	for(int i=1;i<=n;i++){
		cin>>x;
		for(int j=1;j<=x;j++)
			cin>>a[j];//读入密码
		cout<<tai(x,a)<<endl;
	}
	return 0;
}
```
//求过~


---

## 作者：kevin_y (赞：7)

本篇思路比较简单，适合刚刚学习trie的同学看看，dalao勿喷
代码一共分为三部分：
1. trie的建树，不说
2. 计算每一个节点u之后还有几个节点，当然不包括点u。算是一个预处理
3. 开始查询，本串结束或者字符不在字典树出现就退出循环

先上代码，旁边会有详细批注
```cpp
#include<iostream>
#include<cstring>
using namespace std;
int n,m,cnt=1,trie[500001][2],b[500001],end[500001],len,s[500001];
void build(){//建树
	cin>>len;
	for(int i=0;i<len;i++)cin>>s[i];
	int u=1;
	for(int i=0;i<len;i++){
		int c=s[i];
		if(!trie[u][c])trie[u][c]=++cnt;
		u=trie[u][c];
	}
	b[u]++;
	return;
}
void search(){//搜索
	cin>>len;
	for(int i=0;i<len;i++)cin>>s[i];
	int u=1,sum=0;
	for(int i=0;i<len;i++){
		int c=s[i];
		if(trie[u][c])u=trie[u][c];
		else{cout<<sum<<endl;return;}//这里不能+end[u] 不懂的话可以手推一遍
		sum+=b[u];
	}
	cout<<sum+end[u]<<endl;
	return;
}
int make(int u){
	int k1=0,k2=0;
	if(trie[u][0])k1=make(trie[u][0]);//如果左边还有节点就继续找
	if(trie[u][1])k2=make(trie[u][1]);//如果右边还有节点就继续找
	end[u]=k1+k2; //节点u之后还有k1+k2个节点，（不包括点u。
	return b[u]+end[u]; 
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)build();
	end[1]=make(1);
	for(int i=1;i<=m;i++)search();
	return 0;
}
```

---

## 作者：key_rA9 (赞：5)

- ### 简洁题意
    相当于给出一个词典D，有一些询问字符串，每个询问求D中与它有前缀关系(某个字符串是它的前缀或它是某个字符串的前缀)的字符有多少个
- ### 算法描述
    建字典树的同时，用`v`数组记录有多少个词这个节点为结尾，`cnt`数组记录有多少个此经过这个节点(不包括这个词的结尾)。  
    `cnt`不包括一个词最后一个字母是因为当两个字符串相同时~~我也不知道有没有其他情况)~~，同一个节点会被`v`和`cnt`各加一次，那当然不对啦~~(你不会不相信我并没有在这不被坑吧poi)~~。  
    那么查找完后：  
    `v`即它有多少前缀的词  
    `cnt`即它是多少词的前缀  
    所以对于每次询问，答案为路径上所有`v`值加上结束节点的`cnt`值。  
```cpp
1 #include<cstdio>
2 #include<cstring>
3 using namespace std;
4 inline int qr()
5 {
6     int x=0,f=1;char c=getchar();
7     while(c<'0'||'9'<c){c=='-'?f=-1:1;c=getchar();}
8     while('0'<=c&&c<='9'){x=x*10+(c&15);c=getchar();}
9     return x*f;
10 }
11 void qw(int x)
12 {
13 	if(x>9)qw(x/10);
14 	putchar(x%10+'0');
15 }
16 int n,m;
17 int tot,ch[500005][2];
18 int cnt[500005];//有多少信息"经过"此节点 
19 int v[500005];//以此节点为结尾的信息数
20 int main()
21 {
22 	n=qr();m=qr();
23 	tot=1;
24 	int now,t,x;
25 	while(n--)//build trie tree
26 	{
27 		now=1;t=qr();
28		while(t--)
29 		{
30			x=qr();
31			if(!ch[now][x])ch[now][x]=++tot;
32			now=ch[now][x];
33			cnt[now]++;
34		}
35		v[now]++;
36		cnt[now]--;//为了查找时方便不重复
37	}
38	int s;
39	while(m--)//Q^Q
40	{
41		now=1;s=0;
42		t=qr();
43		while(t--)
44		{
45			x=qr();
46			now=ch[now][x];//这里不存在的话会变为0，而以0为下标的各种数组依然是〇，并不影响结果，也不会出现玄学错误
47			s+=v[now];
48		}
49		s+=cnt[now];
50		qw(s);puts("");
51  }
52  return 0;
53 }
```
为了~~懒~~不那么复杂，我字典树就不用函数，而是直接输入时操作。

---

## 作者：zhaoyifan (赞：5)

~~切水题真开心~~

一开始想的是后缀数组，但是每个字符就两种，容易被卡，而且处理起来比较困难。

我们发现对于密码短的情况，可以把信息trie，在上面取标记和，那么对于密码短的情况，显然可能统计入答案的必须在密码对应的trie节点的下方。

然后用trie维护一下儿子数并且统计一下经过的单词即可

```c
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<cstring>
#include<cmath> 
#include<algorithm>
using namespace std;
const int maxn=5e5+7;
int m,n,t[maxn][2],son[maxn],rt=1,cnt=1,poi[maxn],a[maxn];
void Insert(int &x,int now,int len)
{
	if(!x) x=++cnt;son[x]++;
	if(now==len+1) poi[x]++;
	else Insert(t[x][a[now]],now+1,len);
}
int my_find(int x,int now,int len)
{
	if(now==len+1||!x) return son[x];
	return my_find(t[x][a[now]],now+1,len)+poi[x]; 
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		int x;scanf("%d",&x);
		for(int j=1;j<=x;++j)
		scanf("%d",&a[j]);
		Insert(rt,1,x);
	}
	for(int i=1;i<=m;++i)
	{
		int x;scanf("%d",&x);
		for(int j=1;j<=x;++j)
		scanf("%d",&a[j]);
		printf("%d\n",my_find(rt,1,x));
	}
	return 0;
}
```

---

## 作者：chuzhitairan (赞：5)

~~在连续用STL水过了[P3879 阅读理解](https://www.luogu.com.cn/problem/P3879)和[P5149 会议座位](https://www.luogu.com.cn/problem/P5149)后决定好好用字典树做道题(～￣▽￣)～~~

------

### 什么是字典树？

&nbsp;　　在处理字符串问题时，有两个基础操作：存储和查询。而一个字串(单词)在只包含26个英文字母(不区分大小写)的情况下，与其它字串经常会出现重叠部分。如果能把这些重叠部分集中起来去重，既可以节省空间，也可以缩短查询时间(不用每出现一次都比对一次)。于是，就有不知是谁想到了树这个结构。 

&nbsp;　　我们来看一个例子：要依次添加三个字串aab,aac,bac  
&nbsp;　　首先，我们将第一个字串以链的形式存起来  

![](https://cdn.luogu.com.cn/upload/image_hosting/urppeaja.png)  

&nbsp;　　接着我们看第二个字串aac，发现它和第一个字串有公共前缀aa，于是我们可以直接在第二个a后插入一个c,而不需要把重叠部分再存一遍。此时，这个图就变成了一棵树  

![](https://cdn.luogu.com.cn/upload/image_hosting/jph9ovmd.png)  

&nbsp;　　可插入第三个字串时问题来了，它与第二个字串有公共部分ac，难道我们要在第二个a前插入一个新前缀b吗？显然不行，因为那样我们维护的就不是一棵树了；具体地说，我们插入新字串的方法其实是从根节点开始一个一个比对寻找与之前字串的公共前缀，直到不再有公共部分时就将后面的新添加成一条分支。那此时完全没有公共前缀，不是要新建一棵树吗？其实，我们可以在最前段放置一个空的根节点，以便统一成一棵树  

![](https://cdn.luogu.com.cn/upload/image_hosting/xrwpgf3k.png)

&nbsp;　　于是一颗字典树就建成了。  
&nbsp;　　查询方法很类似，也是从根节点开始一一比对，先不再多说。
***
&nbsp;　　回到本题，一看到公共前缀，显然就是针对字典树的，而且它还没有26个字母，只有0和1两个数字。存一颗字典树的方法有很多，大佬们喜欢用指针、结构体什么的，这道题我就使用相对简单的数组来存。  

&nbsp;　　这题的意思其实就是给一个新的字串，求已知字串中以新字串为前缀，或是新字串的前缀的有多少。我们用$book_i$记录经过节点$i$的字串数，$end_i$记录以$i$为结尾的字串数，则在字典树中查询新字串时加上沿途的$end$，最后再加上$book_i$-$end_i$即可。  
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int m,n,l,x,trie[500005][2],book[500005],end[500005],tot,now,cnt,flag;
//trie存储字典树，trie[i][x](x=0或1)表示节点i的后继为x的节点编号 
int main()
{
	scanf("%d%d",&m,&n);
	memset(trie,-1,sizeof(trie));
	//trie[i][x]==-1则表示节点i没有后继x 
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&l);now=0;
		//now表示当前节点，每次从根节点开始 
		for(int j=1;j<=l;j++) 
		{
			scanf("%d",&x);
			if(trie[now][x]==-1) trie[now][x]=++tot;
			//如果节点i没有后继x，则新插入节点i的后继x，编号为tot 
			now=trie[now][x];
			if(j==l) end[now]++; 
			book[now]++;
		}
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&l);now=cnt=flag=0;
		for(int j=1;j<=l;j++)
		{
			scanf("%d",&x);
			if(flag) continue;
			if(trie[now][x]==-1)
			{
				printf("%d\n",cnt);
				flag=1;continue;
				//如果从now开始不再有公共部分了就可以直接输出，并且绝没有以这个新字串为前缀的已知字串 
			}
			now=trie[now][x];
			//不然继续往下 
			cnt+=end[now];
			if(j==l) printf("%d\n",cnt+book[now]-end[now]);
			//如果全部都比对上了，说明新字串是某些已知字串的前缀 
		}
	}
	return 0;
}
```




---

## 作者：LengChu (赞：4)

翻了一下 感觉我的代码比较简单？

题意看了半天 意思是给m个串 用n个串去匹配 求这n个串每个串能匹配的数量

如果用i表示待匹配的串，j表示去匹配他的串，匹配的意思是i是j的前缀或j是i的前缀

对于字典树的每个节点 记录经过这个节点的串的数目和在这个节点结束的串的数目 

统计答案时 对于去匹配他们的串 经过每个点都在答案上累加在这个结点结束的串的数量（i是j的前缀） 到了最后一个结点就累加经过这个结点的串的数量（j是i的前缀）

当然一个串不可能在一个结点又经过又结束

正确性显然了

```cpp
#include<bits/stdc++.h>
using namespace std;
int m,n,k;
int a[100010],len;
struct node
{
	int ch[2];
	int pass;//经过这个点的 
	int end;//在这个点结束的 
}tree[1234567];
void build()
{
	int id=0;
	for(int i=1;i<=len;i++)
	{
		if(tree[id].ch[a[i]]==0) tree[id].ch[a[i]]=++k;
		if(id) tree[id].pass++;
		id=tree[id].ch[a[i]];
	}
	tree[id].end++;
}
int find()
{
	int id=0,sum=0;
	for(int i=1;i<=len;i++)
	{
		if(tree[id].ch[a[i]]==0) return sum;
		id=tree[id].ch[a[i]]; sum+=tree[id].end;
	}
	sum+=tree[id].pass;
	return sum;
}
int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&len);
		for(int j=1;j<=len;j++) scanf("%d",&a[j]);
		build();
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&len);
		for(int j=1;j<=len;j++) scanf("%d",&a[j]);
		printf("%d\n",find());
	}
	return 0;
}
```

---

## 作者：the_same_prayers (赞：3)

# 开始前我先讲个笑话：我用gets()在luogu AC了（？）
作为蒟蒻，本来不敢发题解。でも，众所周知：
### luogu是过不了gets()的
可我在有生之年居然用gets()AC！
震惊之余，我赶快拿起我半年未碰过的博客题解~~水了一篇上去~~，目的是让OIER们知道这个可怕的bug（不过话说回来,本来luogu用gets()过不了才是个bug）

那么言归正传：
## 这是一道典型的 trie ~~裸题~~
（学过字典树的同学们可自行往后跳）

trie,即通常意义上的字典树。字典树即: 将单词以树的方式存储，将字符存于树枝边上，就像查字典单词一样，前缀相同的单词都在前缀对应的子树上，从根节点到每个树枝节点都**必然有一个不同的单词**。 **我们用一个数组trie[N][C]存储，含义为：第N号节点以字符C为边通向的节点，例如：**(图片摘录，侵删)
![](https://img-blog.csdn.net/20140403014117515?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcHlhbmcxOTg5/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

除此之外有些比较小的单词例如 **air** 必然是包含于单词 **airport** 中的，为了便于辨别，我们使用数组 **vis[i]** 表示以从根节点到i号节点经过的字符可以构成一个单词。

每次我们若想插入一个单词，只需从单词第一位开始访问，若trie[p][c]！=0，（p即节点位置，c即查询字符），即已构建树，则查询下一个字符。结合上图理解：假设我们已有ab，e构成的字典树，插入abc。

首先，我们找到首字符a，查询根节点1是否有一条trie[1][a]的道路。找到后来到trie[1][a]通往的2节点（ab）继续查找，成立。当查到c时，发现不存在trie[3][c]，则建树trie[3][c]=++cnt;然后单词查完，vis[3]++；以此类推。若查找也只需从根节点查找。


------------

对于这道题，我们分析可知，若单词a是b的前缀，则b查找过程中必定经过a，即a一定在b通往根节点的路上。所以构完树查找时：
1. 一旦遇到一个非空vis节点，代表肯定包含了另vis个单词（可能有重复），就让ans加上vis值；
1. 若单词结束仍然在字典树内，则代表其一定在某一或几单词内，是这个/些单词前缀。只需要在建树时加一个pre[p]数组，表示多少个单词经过了p这个节点，所以**从根节点到p构成的单词肯定为pre[p]个单词的前缀**；返回ans+=pre[p];
1. 若超出构建的字典树，匹配失败，则只包含情况一，直接返回ans即可；  
- 这时候会出现一个问题：如果遇到相同的单词，即又满足1又满足2，就会重复。所以特判一下。
 
  _AC代码如下_ 
  
```cpp
#include<bits/stdc++.h>
#define N 500025
using namespace std;
char l[N];int pre[N],cnt=1,vis[N],n,k,trie[N][50];//cnt需要从一开始（根节点位置）
inline void in(char a[],int m)
{
	int p=1;
	for(int i=0;i<m*2;i+=2)//gets会读入空格，只需从0开始每次后移两位即可（开始读长度时多读了一个空格）
	{
		int c=a[i]-'0';
		if(!trie[p][c])trie[p][c]=++cnt;
		p=trie[p][c];//p值更新
		pre[p]++; 
	}
	vis[p]++;
}
inline int cheak(char a[],int m)
{
	int p=1,ans=0;
	for(int i=0;i<m*2;i+=2)
	{
		int c=a[i]-'0';
		if(!trie[p][c])return ans;
		p=trie[p][c];
		if(vis[p]&&i!=m*2-2)ans+=vis[p];//特判
	}
	return ans+=pre[p];
}
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		int s;
		scanf("%d ",&s);
		gets(l);//本代码最重要的部分，关键与核心！没有这条语句，这个代码终归平庸，它让这个代码独一无二，得到升华！（滑稽）
		in(l,s);
	}
	for(int i=1;i<=k;i++)
	{
		int s;
		scanf("%d ",&s);
		gets(l);//再次升华，请集体起立，吟唱“gets()带来了希望、生机与光明！”
		printf("%d\n",cheak(l,s));
	}
	
}

```


---

## 作者：lemir3 (赞：2)

[*获得更好的阅读体验*](https://www.cnblogs.com/Lemir3/p/11176156.html)

[*题面*](https://www.luogu.org/problemnew/show/P2922)

##题目分析

很容易看出来是一个$Trie$计数问题.

和一般的$Trie$计数不同,在这道题的题意中,文本串是可以作为模式串的前缀的.

比如说文本串是$0001$,而模式串是$00010000000$,这种情况也要算上.

区别于一般的$Trie$中给一个文本串的末尾的结点做一个标记,同志们得把这个标记改成计数器.

当模式串在$Trie$树上跑,如果遇到了计数器,就累加入答案.表明有文本串在中途夭折了.

模式串匹配到尾时,加上该结点被多少个文本串经过的计数器.

理一下两个计数器的作用:

+ 第一个计数器的作用是作为模式串前缀的文本串累加上去,在文本串的末尾结点累加,在模式串匹配的过程中统计.

+ 第二个计数器表示有多少个文本串的前缀中有模式串,在文本串的每一个结点上都要累加,在模式串匹配完之后统计.

##代码

*为了减小一点常数,我把Trie过程写在了循环里,边读入边做,请各位同志谅解.*

```cpp

#include "cstdio"
#include "cstring"
#include "algorithm"
#include "iostream"

#define debug(x) printf("debug:%d\n",x)
#define I_copy_this_anwser return

using namespace std;

int m,n,tot=1,ans;
int trie[500010][3],CharCnt[500010],EndCnt[500010];
bool end[500010];

int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;i++)
    {
        int p=1,num,len;
        scanf("%d",&len);
        for(int j=1;j<=len;j++)
        {
            scanf("%d",&num);
            if(trie[p][num]==0)
            {
                trie[p][num]=++tot;
            }
            p=trie[p][num];
            if(j!=len)//这里注意一下,两个计数器不能加重复了
            {
                CharCnt[p]++;//记录文本串前缀的计数器
            }
        }
        EndCnt[p]++;//记录文本串末尾的计数器
    }
    for(int i=1;i<=n;i++)
    {
        int p=1,cnt=0,num,len;
        scanf("%d",&len);
        bool flag=false;
        for(int j=1;j<=len;j++)
        {
            scanf("%d",&num);
            if(flag==true)
            {
                continue;
            }
            p=trie[p][num];
            if(EndCnt[p])
            {
                cnt+=EndCnt[p];
            }
            if(p==0)//后面再也没有能够匹配该模式串的文本串了,输出能够作为文本串前缀的模式串个数即可(科技为了我)
            {
                flag=true;
                printf("%d\n",cnt);
            }
        }
        if(flag==false)
        {
            cnt+=CharCnt[p];//统计模式串可以作为多少个文本串的前缀
            printf("%d\n",cnt);
        }
    }
return 0;
}

```

---

## 作者：圣光天子 (赞：2)

可以用字典树做。

首先将n条信息建树。建树时加了两个变量point和sum，point指在该节点结束的信息数量，sum指下方更长的信息数量(在该节点结束的字符串是多少个信息的前缀)。

接着读入m条密码，每条密码跑一遍字典树。当经过一个节点时，累加其point，表示该信息为该条密码的前缀。密码读入完后，将当前位置的sum累加入ans，表示该密码是下方sum条信息的后缀(记得减去当前位置的point以免重复累加)。但当密码跑字典树时，如果无法继续向下，那么不能累加sum，因为它不会是任何信息的前缀。

代码
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define N 50050
#define W 500050

typedef struct {
	int lchild,rchild,point,sum;
} tree;

int n,m,t,i,j,b;
int x,coume;
int ls,now,ans;
tree trime[W];

int main()
{
	scanf("%d%d",&n,&m);
	
	ans=0; coume=0;
	memset(trime,0,sizeof(trime));
	//建树 
	for (int i=1; i<=n; i++)
	{
		scanf("%d",&t);
		now=0;
		for (j=1; j<=t; j++)
		{
			scanf("%d",&ls);	
			if (ls==0)
			{
				if (trime[now].lchild==0) 
				{
					coume++;
					trime[now].lchild=coume;
				}
				now=trime[now].lchild;
				trime[now].sum++;
			}
			else
			{
				if (trime[now].rchild==0)
				{
					coume++;
					trime[now].rchild=coume;
				}
				now=trime[now].rchild;
				trime[now].sum++;
			}	
		}
		trime[now].point++;
	}
	
	for (int i=1; i<=m; i++)
	{
		scanf("%d",&t); ans=0;
		now=0; 
		b=1;//用b表示是否累加sum 
		for (j=1; j<=t; j++)
		{
			scanf("%d",&ls);
			if (ls==0)
			{
				if (trime[now].lchild==0)
					b=0;
				else now=trime[now].lchild;
			}
			else 
			{ 
				if (trime[now].rchild==0)
					b=0;
				else now=trime[now].rchild;
			}
			if (b)
			ans=ans+trime[now].point;
		}
		if (b) ans+=trime[now].sum-trime[now].point;//记得减去point 
		printf("%d\n",ans);//记得换行(老是忘QwQ) 
	}
}
```

---

## 作者：chihik (赞：1)

~~这道题还是$Trie$树的板题~~，先将$n$个信息插入字典树中，对于查询的密码，在字典树中查询即可。

插入很好办，我们现在来讨论查询操作。我们记$s_1$为任意一个信息，$s_2$是待匹配的密码。$tot[u]$表示有多少个字符串经过点$u$，$fin[u]$表示有多少个字符串以点$u$结尾。

那么会出现三种情况：

1.$s_1$是$s_2$的前缀，累加路径上所有的$fin[u]$即可。

2.$s_1=s_2$。其实就是情况1，$s_1$结束时的点一定与$s_2$结束时的点相同，也就包含在$fin$中。

3.$s_2$是$s_1$的前缀，如果单词最后一个字符所在节点为$v$，我们很容易看出$tot[v]$就代表该单词是多少字符串的前缀。那么我们只需要加上$tot[v]$就好了。

但是，$tot[v]$会包含以$v$节点结尾的单词数，所以结果须减去$fin[v]$。

那么，一道~~难~~蓝题就被我们解决了，附上代码：


```cpp
#include <cstdio>
#include <cstring>

const int MAXN = 500000;
int n,m,len;
int Trie[ MAXN + 5 ][ 2 ] , cnt;
int tot[ MAXN + 5 ] , fin[ MAXN + 5 ];

void Insert( char *str , int len ) {
    int u = 0;
    for( int i = 0 ; i < len ; i ++ ) {
        int num = str[ i ] - '0';
        if( !Trie[ u ][ num ] ) 
            Trie[ u ][ num ] = ++ cnt;
        u = Trie[ u ][ num ];
        tot[ u ] ++;
    }
    fin[ u ] ++;
}
int Find( char *str , int len ) {
    int u = 0 , Ans = 0;
    for( int i = 0 ; i < len ; i ++ ) {
        int num = str[ i ] -'0';
        if( !Trie[ u ][ num ] )
        	return Ans;
        u = Trie[ u ][ num ];
        Ans += fin[ u ];
    }
    return Ans - fin[ u ] + tot[ u ];
}

int s1;
char s[ 10005 ];
int main( ) {
	scanf("%d %d",&m,&n);
	for( int i = 1 ; i <= m ; i ++ ) {
		scanf("%d",&len);
		for( int j = 0 ; j < len ; j ++ ) {
			scanf("%d",&s1);
			s[ j ] = s1 + '0';
		}
		Insert( s , len );
	}
	for( int i = 1 ; i <= n ; i ++ ) {
		scanf("%d",&len);
		for( int j = 0 ; j < len ; j ++ ) {
			scanf("%d",&s1);
			s[ j ] = s1 + '0';
		}
		printf("%d\n",Find( s , len ));
	}
	return 0;
}
```


---

## 作者：水库中的水库 (赞：1)

问题可转换为：对于每一个串，计算与其有相同前缀的串的个数和以其为前缀的串的个数和

那么相当于我们要计算两个值

对于第一个值，可以简单的在构建Trie树的时候记一个val值，在Search操作的时候累加即可

因为有重复串，所以该val值应为int类型，Insert的时候++

对于第二个值，答案其实是以该串的结尾节点为根的所有子树的val值和

所以我们可以做一个类似线段树的Push_up操作，在所有Insert操作完成后对于每一个节点计算以它为根的所有子树的val值和

这样这个问题就解决了

```cpp
// luogu-judger-enable-o2
/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2019年05月13日 星期一 10时28分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 50000010;

struct node
{
	int next[2], val, sum;
} Trie[maxn];

int tot = 1, n, m, ans, a[maxn], num;

inline void INIT(int x)
{
	Trie[x].next[0] = Trie[x].next[1] = Trie[x].val = Trie[x].sum = 0;
}

inline void Push_up(int x)
{
	if ( Trie[x].next[0] ) Push_up(Trie[x].next[0]);
	if ( Trie[x].next[1] ) Push_up(Trie[x].next[1]);
	Trie[x].sum = Trie[x].val;
	Trie[x].sum += Trie[Trie[x].next[0]].sum + Trie[Trie[x].next[1]].sum;
}

inline void Insert()
{
	int p = 1;
	REP(i, 1, num)
	{
		if ( !Trie[p].next[a[i]] ) 
		{
			Trie[p].next[a[i]] = ++ tot;
			INIT(tot);
		}
		p = Trie[p].next[a[i]];
	}
	Trie[p].val ++; 
}

inline void Search()
{
	int p = 1;
	REP(i, 1, num)
	{
		if ( !Trie[p].next[a[i]] ) return ;
		p = Trie[p].next[a[i]];
		ans += Trie[p].val;
	}
	ans -= Trie[p].val;
	ans += Trie[p].sum;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	INIT(tot);
	REP(i, 1, n)
	{
		scanf("%d", &num);
		REP(j, 1, num) scanf("%d", &a[j]);
		Insert();
	}
	Push_up(1);
	REP(i, 1, m)
	{
		scanf("%d", &num); ans = 0;
		REP(j, 1, num) scanf("%d", &a[j]);
		Search();
		printf("%d\n", ans);
	}
    return 0;
}
```

---

## 作者：Baihua (赞：1)

### 【题解】P2922 [USACO08DEC]秘密消息Secret Message

[个人博客地址](https://www.cnblogs.com/bj2002/p/10595092.html)

* #### $\text{Tags}$

  * 字典树，统计

---

* #### 题意：

  * 给出两组$\text{0/1}$串$\text{A,B}$，求解 $\text{A}$中某串是$\text{B}$中某串的前缀，和$\text{B}$中某串是$\text{A}$中某串的前缀的数量之和。

* #### 分析：

  * 对于$\text{A}$建立字典树。另外附加两个数组：
  * $\text{int Son[i]}$表示节点 $\text{i}$ 点$\text{Son[i]}$儿子。
  * $\text{int End[i]}$表示有$\text{End[i]}$个字符串终结于$\text{i}$。
  * 对于每个询问，沿着字典树向下走，累加沿途的$\text{End[i]}$ 。
  * 如果不能匹配，返回累加值。
  * 如果整个询问都匹配成功，还要加上最后一个节点的儿子数量。

* #### 参考代码：

  * ```
    #include <stdio.h>
    #include <string.h>
    #define re register
    #define GC getchar()
    #define Clean(X,K) memset(X,K,sizeof(X))
    int Qread () {
    	int X = 0 ;
    	char C = GC ;
    	while (C > '9' || C < '0') C = GC ;
    	while (C >='0' && C <='9') {
    		X = X  * 10 + C - '0' ;
    		C = GC ;
    	}
    	return X ;
    }
    const int Maxn = 500005 , Base = 2;
    int T[Maxn][Base] , Tot = 0 , M , N , End[Maxn] , Son[Maxn] , A[Maxn];
    void Add (int Now) {
    	int P = 0 ;
    	for (re int i =  0 ; i < Now ; ++ i) {
    		if (!T[P][A[i]]) T[P][A[i]] = ++ Tot;
    		++ Son[P] ;
    		P = T[P][A[i]] ;
    	}
    	++ End[P] ;
    }
    int Ask (int Now) {
    	int P = 0 , Ans = 0;
    	for (re int i = 0 ; i < Now ; ++ i) {
    		if (!T[P][A[i]]) return Ans ;
    		P = T[P][A[i]] ;
    		Ans += End[P] ;
    	}
    	return Ans + Son[P] ;
    }
    int main () {
    	M = Qread () , N = Qread () ;
    	Clean(T , 0) , Clean(End , 0) , Clean (Son , 0) ;
    	for (re int i = 1 ; i <= M; ++ i) {
    		int Now = Qread () ;
    		for (re int j = 0 ; j < Now ; ++ j) A[j] = Qread () ;
    		Add (Now) ;
    	}
    	for (re int i = 1 ; i <= N; ++ i) {
    		int Now = Qread () ;
    		for (re int j = 0 ; j < Now ; ++ j) A[j] = Qread () ;
    		printf ("%d\n" , Ask (Now)) ;
    	}
    	fclose (stdin) , fclose (stdout) ;
    	return 0 ;
    }
    ```

#### Thanks!

---

## 作者：HDWR (赞：1)

本文同步发布于[Handwer's Blog](https://blog.handwer-std.top/)

# 解题思路
查询前缀的题很容易想到 Trie

---

维护两个信息 `pass` 和 `lasts`

`pass` 表示当前节点有多少条信息经过， `lasts` 表示有多少以当前节点结尾的信息（不一定没有相同的串）

插入就不说了，说说查询

---

查询的时候，记一下路径上`lasts`的和（也就是拿原信息去匹配查询信息）

首先对于每一条查询信息，都分两种情况
1. 这条信息被完美的查询完了
2. 这条信息查到一半断开了

对于第二种情况，什么都不用管，输出统计的`lasts`的和就行

对于第一种情况，则需要减去**查询信息**的最后一个节点的`lasts`值，加上`pass`值再输出

为什么呢？

---

***这里建议画图理解***

首先，如果查到一半断开了，那么答案就是**用原信息去匹配查询信息**的匹配数，也就是`lasts`的和

```
比如下面的例子
查询信息：
kk_kel_dk
原始信息：
kk
kk_kel
kk_kel_jk（这个也是没法匹配的，后几个字符不同）
那么匹配数就是2，即为答案
```

如果查询完了，那么说明**存在能匹配查询信息的原信息**，所以「用原信息去匹配查询信息的匹配数」还不够，要再加上「用查询信息去匹配原信息的匹配数」，也就是`lasts的总和 + pass`

有这么一种情况，就是**原信息与查询信息相同**，那么它在当前节点的`lasts`里面算了一次，在当前节点的`pass`又算了一次！所以要减去当前节点的`lasts`

```
比如下面的例子
查询信息：
kk_kel_dk
原始信息：
kk_kel_dk_tql_wsl
kk_kel_dk
答案是啥？2

注意到dk这里k的 pass 是2，把两条信息都算上了
但同时dk这里k的 lasts 也是1啊！！！
这不就重了吗，所以要减去 lasts
```

~~我觉得我说的已经够通俗易懂了吧~~
![kel](https://s2.ax1x.com/2019/03/23/AJ3jc8.png)

# 代码实现
```cpp
#include <iostream>
#include <cstring>

#define FILE_IN(__fname) freopen(__fname, "r", stdin)
#define FILE_OUT(__fname) freopen(__fname, "w", stdout)
#define IMPROVE_IO() std::ios::sync_with_stdio(false)

using std::cin;
using std::cout;
using std::endl;

const int MAXN = 500000 + 10;

struct Trie {
    struct Node {
        int pass, lasts;
        int next[2 + 1];
        
        Node() {
            pass = lasts = 0;
            memset(next, 0, sizeof next);
        }
    } node[MAXN];
    
    int cnt;
    
    Trie() {
        cnt = 0;
    }
    
    void SwitchTo(int &now, bool data) {
        if (node[now].next[data] == 0) {
            node[now].next[data] = ++cnt;
        }
        now = node[now].next[data];
    }
    bool switchTo(int &now, bool data) {
        if (node[now].next[data] == 0) return false;
        now = node[now].next[data];
        return true;
    }
} t;
// 一个挺正常的字典树实现

int m, n;

int main() {
    IMPROVE_IO();
    cin >> m >> n;
    for (int i = 1; i <= m; ++i) {
        int f = 0, pos = 0;
        cin >> f;
        for (int j = 1; j <= f; ++j) {
            int nf = 0;
            cin >> nf;
            t.SwitchTo(pos, nf);
            ++t.node[pos].pass;
        }
        ++t.node[pos].lasts;
    }
    for (int i = 1; i <= n; ++i) {
        int f = 0, pos = 0, ans = 0;
        cin >> f;
        bool cont = true;
        for (int i = 1; i <= f; ++i) {
            int nf = 0;
            cin >> nf;
            if (cont && t.switchTo(pos, nf)) {
                ans += t.node[pos].lasts; // 沿途记录lasts的和
            } else cont = false; // 判断当前查询信息是否断掉了
        }
        if (cont) ans = ans - t.node[pos].lasts + t.node[pos].pass;
        cout << ans << endl;
    }
    return 0;
}


```


---

## 作者：ljc20020730 (赞：1)

## [USACO08DEC]秘密消息solution

- tag： 一道水水的蓝题

字典树不用多说(Trie_Tree)然后维护标记的话就是维护

- sum表示路径上有几个字符串

- val表示路径到此为止有几个字符串恰好终结

每一次insert操作要维护这两个的值(注意千万不要忘记结尾！)

每一次的find操作通过走在字典树上的路径把所有的val累加起来（注意千万不要忘记结尾！）

然后分两种情况讨论

- 沿着这条路径走完 ： ans=ans-val[u]+sum[u]

- 没有沿着这条路径走完 ： ans

why？ 

我们考虑一条存储信息S和待查询信息T

如果|S|<|T|我们只要在字典树中找出所有的S对应的val值就行了(一定有val标识)

如果 |S|>|T| 

1. S无法终结，T终结 当前节点包含的信息一定有包含T的的前缀，但是sum和val是包含关系我加了sum就必须减去val才能不重复

2. S无法终结，T没有终结，那么就不进行任何操作直接return


code：看到非指针的代码都写。。我还是贴一下自己咕咕的代码吧

```
# include<bits/stdc++.h>
using namespace std;
const int MAXN=500005;
string s;
inline int read()
{
	int X=0,w=0; char c=0;
	while (!(c>='0'&&c<='9')) w|=c=='-',c=getchar();
	while (c>='0'&&c<='9') X=(X<<1)+(X<<3)+(c^48),c=getchar();
	return w?-X:X;
}
struct Trie_Tree{
	int ch[MAXN][3],size;
	int val[MAXN],sum[MAXN];
	Trie_Tree(){
		memset(sum,0,sizeof(sum));//有多少字符串经过这个点 
		memset(val,0,sizeof(val));//有多少字符串在这个点终结 
		memset(ch,0,sizeof(ch)); 
		size=1;
	}
	int idx(char a) { return a-'0';}
	void insert() {
		int len=s.length();
		int u=0;
		for (int i=0;i<len;i++) {
			int c=idx(s[i]);
			if (!ch[u][c]) ch[u][c]=++size;
			sum[u]++;
			u=ch[u][c];
		} 
		val[u]++; sum[u]++;
	}
	int find() {
		int len=s.length();
		int u=0,ans=0;
		for (int i=0;i<len;i++) {
			int c=idx(s[i]);
			ans+=val[u];
			if (!ch[u][c]) goto exit;
			u=ch[u][c];
		}
		ans+=val[u];
		return ans-val[u]+sum[u];
		exit:return ans;
	}
}Tree;
int main()
{
	int n,m;
	n=read();m=read();
	while (n--) {
		int len=read(); s="";
		while (len--) s+=read()+'0';
		Tree.insert(); 
	}
	while (m--) {
		int len=read();s="";
		while (len--) s+=read()+'0';
		int ans=Tree.find();
		printf("%d\n",ans); 
	}
	return  0;
 } 
```

---

## 作者：Angora (赞：1)

匹配路上的所有结束字符串都要加上,经过最后一个位置的字符串也要加上注意计算顺序就好...
``` c++
#include<iostream>
#include<cstdio> 
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#define rep(i,x,y) for(register int i=x;i<=y;++i)
#define repd(i,x,y) for(register int i=x;i>=y;--i)
#define long long
using namespace std;
const int N=5e5+7;
int tr[N<<2][2],nm[N],sum[N<<2],n,m,cnt=1,end[N];
inline void add(int *a,int len){
	int p=1;
	rep(i,1,len){
		if(!tr[p][a[i]])tr[p][a[i]]=++cnt;
		sum[tr[p][a[i]]]++;p=tr[p][a[i]];
	}
	end[p]++;
}
inline int query(int *a,int len){
	int p=1,ans=0;
	rep(i,1,len){
		if(!tr[p][a[i]])return ans;
		p=tr[p][a[i]];
		if(p)ans+=end[p];
	}
	return ans+sum[p]-end[p];
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d%d",&n,&m);
	rep(i,1,n){
		int x;scanf("%d",&x);
		rep(j,1,x)scanf("%d",&nm[j]);
		add(nm,x);
	}
	rep(i,1,m){
		int x;scanf("%d",&x);
		rep(j,1,x)scanf("%d",&nm[j]);
		printf("%d\n",query(nm,x));
	}
	return 0;
}
```

---

## 作者：chauchat (赞：1)

刚接触字典树，这是一道字典树的统计

对于信息的前缀，统计路径上的单词个数，

对于大于信息长度的部分，统计子树上的单词数的总和。

那要怎么做呢？当然是选择模拟啦Orz


size表示子树和，exist表示这个节点作为结尾的次数（题目的信息是可重复的）。

建树的时候统计出exist，然后用一个pushup函数统计出每个子树的和；

最后就用上面说的规则算出答案就行啦。




```cpp
#include<iostream>
using namespace std;
#include<cstdio>
#include<cstring>
int n,m,ans;
struct node{
    int son[2],size,exist;
}trie[500010]; int ptr;
void build(string temp,int pc,int now){
    if(pc >= temp.length()){
        trie[now].exist++; return ;
```
}//到结尾啦

```cpp
    for(int i = 0;i <= 1;i++)
        if(trie[now].son[i] && i == temp[pc]-'0'){
            build(temp,pc+1,trie[now].son[i]);
            return ;
        }
        //新建一个节点
    ptr++;
    trie[now].son[temp[pc]-'0'] = ptr;
    build(temp,pc+1,ptr);
}
int init(int now){
    int ans = trie[now].exist;
    for(int i = 0;i <= 1;i++) if(trie[now].son[i]) ans += init(trie[now].son[i]);
    trie[now].size = ans;
    return ans;
}
void find(string temp,int pc,int now){
    if(pc >= temp.length()){
        ans += trie[now].size; return ;//子树的和
    }
    ans += trie[now].exist;//路径上的和
    for(int i = 0;i <= 1;i++) 
        if(trie[now].son[i] && i == temp[pc]-'0')
            find(temp,pc+1,trie[now].son[i]);
}
int main(){
    cin>>m>>n;
    for(int i = 1;i <= m;i++){
        string t; int l; scanf("%d",&l);
        for(int j = 1;j <= l;j++){
            int temp; scanf("%d",&temp); t += temp+'0';
```
}//先把数字换成字符串。
```cpp
        build(t,0,0);
    }
    init(0);
    for(int i = 1;i <= n;i++){
        string t; int l; ans = 0; scanf("%d",&l);
        for(int j = 1;j <= l;j++){
            int temp; scanf("%d",&temp); t += temp+'0';
        }
        find(t,0,0); printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：Celtic (赞：0)

[博客食用](https://www.luogu.com.cn/blog/176990/solution-p2922)

[$AcCoders$传送门](http://www.accoders.com/problem.php?cid=2332&pid=5)

[$Loj$传送门](https://loj.ac/problem/10054)

[$bzoj$传送门](https://www.lydsy.com/JudgeOnline/problem.php?id=1590)

一道$AC$自动机模板题。

这里给一个$Trie$树的做法。

- 把信息建出$Trie$树

- 设$sum[i]$表示有多少个串经过节点$i$，$end[i]$表示有多少个串以节点$i$为结尾。

- 然后沿着$Trie$扫一遍暗号，$ans+=end[i]$

- 最后$ans-end[p]+sum[p]$就是答案。

为什么呢？

因为如果这个串是其他串的前缀，那么其他的串一定经过这个串的结尾，总数量为$sum[i]$

如果其他串是这个串的前缀，那么这个串一定经过其他串的结尾标记，所以把沿路的结尾标记加起来。

但是这样的话相匹配的串算了两次，所以要减去一个。

代码

```cpp
#include<bits/stdc++.h>
#define eps 1e-7
#define re register
#define N 500101
#define MAX 2001
#define PI 3.1415927
#define inf 1e18
using namespace std;
typedef long long ll;
typedef double db;
inline void read(re ll &ret)
{
    ret=0;re ll pd=0;re char c=getchar();
    while(!isdigit(c)){pd|=c=='-';c=getchar();}
    while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c&15);c=getchar();}
    ret=pd?-ret:ret;
    return;
}
ll n,m,a[N],num[N],trie[N][2],tot,f[N],sum[N];
inline void insert(re ll i)
{
	re ll p=0;
	for(re int j=1;j<=num[i];j++)	
	{
		re ll c=a[j];
		if(!trie[p][c])
			trie[p][c]=++tot;
		p=trie[p][c];
		sum[p]++;
	}
	f[p]++;
	return;
}
inline ll query(re ll i)
{
	re ll p=0,ret=0;
	for(re int j=1;j<=num[i];j++)
	{
		re ll c=a[j];
		if(!trie[p][c])
			return ret;
		p=trie[p][c];
		ret+=f[p];
	}
	return ret-f[p]+sum[p];
}
int main()
{
	read(n);
	read(m);
	for(re int i=1;i<=n;i++)
	{
		read(num[i]);
		for(re int j=1;j<=num[i];j++)
			read(a[j]);
		insert(i);
	}
	for(re int i=1;i<=m;i++)
	{
		read(num[i]);
		for(re int j=1;j<=num[i];j++)
			read(a[j]);
		printf("%lld\n",query(i));
	}
	exit(0);
}
```



---

## 作者：crashed (赞：0)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/P2922)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;利用$Trie$来统计答案的题。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;原题的答案可以分为两种——信息是密码前缀的和密码是信息前缀的。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑第一种情况。我们按照密码在$Trie$上面遍历。在遍历过程中，记录经过了几个消息（利用节点上面的统计标记求出来）；如果遍历过程中，走到了$Trie$上面不存在的节点，那么就返回当前的已有的答案（之后肯定不会有新的答案了）。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑第二种情况。假如我们在遍历过程中，成功地将密码遍历完了，我们就可以开始记录第二种情况的答案了。这个时候，我们需要用在当前节点的子树上的消息的数量（这个可以在插入消息的时候求出来），减去当前节点上消息的数量去重（也是节点上面的统计标记），于是这一部分就结束了。~~好快~~  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;把两个部分的答案加起来就是最后的答案啦！时间是$O(\sum b+\sum c)$。  
# 代码
```cpp
#include <cstdio>

const int MAXN = 500005;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar(); int f = 1;
	while( s < '0' || '9' < s ){ f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ){ x = ( x << 3 ) + ( x << 1 ) + s - '0', s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ), x = -x; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

int message[MAXN];
int trie[MAXN][2], cnt[MAXN], ending[MAXN];
int N, M;
int siz = 1;

void insert( const int *str, const int len )
{
	int p = 1, indx;
	for( int i = 1 ; i <= len ; i ++ )
	{
		indx = str[i];
		if( ! trie[p][indx] ) trie[p][indx] = ++ siz;
		p = trie[p][indx], cnt[p] ++;
	}
	ending[p] ++;
}

int query( const int *str, const int len )
{
	int p = 1, indx, res = 0;
	for( int i = 1 ; i <= len ; i ++ )
	{
		indx = str[i];
		if( ! trie[p][indx] ) return res;
		p = trie[p][indx], res += ending[p]; 
	}
	return res + cnt[p] - ending[p]; 
}

int main()
{
	int l;
	read( M ), read( N );
	for( int i = 1 ; i <= M ; i ++ )
	{
		read( l );
		for( int j = 1 ; j <= l ; j ++ ) read( message[j] );
		insert( message, l );
	}
	for( int i = 1 ; i <= N ; i ++ )
	{
		read( l );
		for( int j = 1 ; j <= l ; j ++ ) read( message[j] );
		write( query( message, l ) ), putchar( '\n' );
	}
	return 0;
}
```

---

## 作者：弦巻こころ (赞：0)



题意还是挺好懂的，就是翻译太坑了！！！不把样例解释和输入格式翻译一下。蒟蒻看了好久才看明白。

大意:给定几个模式串和几个文本串，对于一个文本串让你求文本串完全包含模式串，或模式串完全包含文本串，加起来的个数。

可能解释的还不是太明白。我把样例解释下。

一共有$4$个模式串 $5$个文本串 

分别为
```
0 1 0 
1 
1 0 0 
1 1 0 

0 
1 
0 1 
0 1 0 0 1 
1 1 
```


对于第一个文本串 $0$   第$1$个模式串 $010$ 完全包含它 故输出$1$

对于第二个文本串$1$   第$2,3,4$个模式串包含它 故输出$3$

对于第三个文本串 $01$   第$1$个模式串 $010$ 完全包含它 故输出$1$

对于第四个文本串$1$   它包含了第$1$个模式串$010$ 故输出$1$

对于第五个文本串$11$   它包含了第$2$个模式串，并被第$4$个模式串包含故输出$2$

看到这里你大概对题意有些了解了，即：

#### 对于每个文本串它的答案为：它完全包含的模式串+完全包含它的模式串

对于模式串和文本串分别建$trie$树，并分别跑一遍求和？

### $NO$

太麻烦，我们有更简便的做法，在建$trie$的同时我们对于每个$now$都储存一下出现次数（$num$），对于每个串尾也储存一下出现次数（$vis$）。这两个要分开储存。

在爆搜时，每当我们枚举到一个点($now$) 时无论它是否是叶节点都要加上$vis$（因为$vis$默认为$0$,如果它不是叶节点也没什么影响）。在搜完时（搜完了所有点或无法继续匹配）加上 $num$[$now$]就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int trie[500005][2],tot,n,m,num[500005],vis[500005],fa;
int s[10005],ans;
void make_trie(int s[10005],int len)//建trie树
{
	int now=0;
	for(int i=1;i<=len;i++)//因为我是从1开始的所以i要从1开始枚举
	{
		int next=s[i];
		if(!trie[now][next])
		{
			trie[now][next]=++tot;
		}
		now=trie[now][next];
		num[now]++;//每个点的出现次数
	}
	vis[now]++;//记录根节点
}
void dfs(int now,int x)
{
	
	if(x==fa+1||now==0&&x!=1)//如果搜完了的话
	{
		ans+=num[now];//如果有模式串包含它
		return ;
	}
	ans+=vis[now];//如果它包含了模式串
	dfs(trie[now][s[x]],x+1);	
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		int ai;
		scanf("%d",&ai);
		for(int j=1;j<=ai;j++)
		{
			scanf("%d",&s[j]);
		}
		make_trie(s,ai);//建树
	}
	for(int i=1;i<=m;i++)
	{
		ans=0;
		memset(s,0,sizeof(s));//这里写不写无所谓
		
		scanf("%d",&fa);
		for(int j=1;j<=fa;j++)
		{
			scanf("%d",&s[j]);
		}
		dfs(0,1);//因为我是从1开始的所以x也要从1开始枚举
		printf("%d\n",ans);
	}
}
```


---

## 作者：Thosaka_Forest (赞：0)

既然是读入字符串然后与之前的字符串进行匹配，那么肯定是对之前的字符串建立Trie树，这点毋庸置疑。

那么就是统计有多个字符串作为他的前缀出现以及该字符串是多少个字符串的前缀，那么就与电话簿一题类似了。

我记录经过该点的字符串数量以及以该点作为结束点的数量，那么最后答案就是这条路径上结束点的数量之和+经过最后点的字符串数量（注意我的pass记录的不包括最后一个字符，最后一个打的是end标记）

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+10;
const int LEN=1e4+10;

int n,q;
int siz,k,a[LEN];
struct Trie{
	int pass,end;
	int son[2];
}tr[MAXN];

int Read(){
	int i=0,f=1;
	char c;
	for(c=getchar();(c>'9'||c<'0')&&c!='-';c=getchar());
	if(c=='-')
	  f=-1,c=getchar();
	for(;c>='0'&&c<='9';c=getchar())
	  i=(i<<3)+(i<<1)+c-'0';
	return i*f;
}

void insert(){             //插入操作 
	for(int i=1;i<=k;++i){
		a[i]=Read();
	}
	int last=0;
	for(int i=1;i<=k;++i){
		tr[last].pass++;  //把经过的点标记 
		if(!tr[last].son[a[i]]){
			tr[last].son[a[i]]=++siz;
			memset(tr[siz].son,0,sizeof(tr[siz].son));
		}
		last=tr[last].son[a[i]];
	}
	tr[last].end++;       //结束点标记 
}

int query(){
	int ret=0;
	for(int i=1;i<=k;++i){
		a[i]=Read();
	}
	int last=0;
	for(int i=1;i<=k;++i){
		ret+=tr[last].end;
		if(!tr[last].son[a[i]]){
			return ret;
		}
		last=tr[last].son[a[i]];
	}
	ret+=tr[last].pass+tr[last].end;//统计最后一个点作为结束点以及经过最后一个点的字符串数量 
	return ret;
}

int main(){
	n=Read(),q=Read();
	for(int i=1;i<=n;++i){
		k=Read();
		insert();
	}
	for(int i=1;i<=q;++i){
		k=Read();
		cout<<query()<<'\n';
	}
	return 0;
}
```

---

## 作者：Drifterming (赞：0)

```
//01 Trie

//记录经过该路径的信息条数cnt（不在这儿结束，不与该路径相同）,以及在这儿结束的信息条数sum（与该路径相同的信息条数） 
//那么，在query的时候，
//ans+=沿线路径各点的sum 
//如果密码能匹配成功，就让ans+=root->cnt
//也就是加上与该密码前缀相同的信息条数
//如果密码不能匹配成功 
//就直接返回ans就可以了 

#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

const int N=5e5+5;

int n,m,len;
struct TREE
{
	int num;
	int cnt,sum;
	TREE *son[2];
}tree[N];

typedef TREE* Tree;
Tree Root,now_node,null;

inline int read()
{
	char c=getchar();int num=0;
	for(;!isdigit(c);c=getchar());
	for(;isdigit(c);c=getchar())
		num=num*10+c-'0';
	return num;
}

void init()
{
	Root=now_node=null=tree;
	null->son[1]=null->son[0]=null;
}

inline Tree new_node(int num)
{
	++now_node;
	now_node->num=num;
	now_node->son[0]=now_node->son[1]=null;
	return now_node;
}

void insert(Tree root)		//插入信息 
{
	for(int i=1,a;i<=len;++i)
	{
		a=read();
		if(root->son[a]==null)
			root->son[a]=new_node(a);
		root=root->son[a];
		++(root->cnt);		//经过该路径的信息条数+1 
	}
	--(root->cnt);		//减去完全一样的 
	++(root->sum);		//该条信息+1 
}

int query(Tree root)
{
	int ans=0;
	bool ok=1;
	for(int i=1,a;i<=len;++i)
	{
		a=read();
		if(ok==0||root->son[a]==null)	//不要提前return，因为密码还没读完 
		{
			ok=0;
			continue;
		}
		root=root->son[a];
		ans+=root->sum;		//加上比密码短的信息条数，他们完全包含在密码里或者与密码相同 
	}
	if(ok)	//密码匹配成功 
		return ans+root->cnt;		//加上与密码前缀相同的信息条数 
	return ans;
}

int main()
{
//	freopen("testdata.in","r",stdin);
//	freopen("233.out","w",stdout);
	init();
	m=read(),n=read();
	for(int i=1;i<=m;++i)
	{
		len=read();
		insert(Root);
	}
	for(int i=1;i<=n;++i)
	{
		len=read();
		printf("%d\n",query(Root));
	}
	return 0;
}
```

---

## 作者：wzj423 (赞：0)

观察题目可以发现,这是一道典型的Trie树题目(废话)

所做的步骤只有三个:

1:建树

2:查找比密码短或等于密码的信息

3:查找比密码长的信息


0:读入优化

```cpp
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
```
1:建树

建树就是建一颗二进制的Trie数

1.1:这里完全可以一边建树一边读取,不用储存

```cpp
void addMsg(int length,int id=0)
{
    if(!length)
    {
        ++T[id].leave;
        return;
    }
    int t=read();
    //scanf("%d",&t);
    if(T[id].child[t]==0)
        T[id].child[t]=Tsize++;
    addMsg(length-1,T[id].child[t]);
    ++T[id].downNodeCnt;
}
```
2:查找比密码短或等于密码的信息

没设么好说的,Trie树基本操作,一边按照密码读入一边累积叶节点数量

```cpp
int searchMsg(int length,int id=0)
{
    int t,ans=0;
    if(T[id].leave!=0)
        ans+=T[id].leave;
    if(length==0)
        return T[id].downNodeCnt+ans;
    //scanf("%d",&t);
    t=read();
    if(T[id].child[t]!=0)
        return ans+searchMsg(length-1,T[id].child[t]);
    else
    {
        --length;
        while((length--)>0)
            read();
        return ans;
    }
}
```
3:查找比密码长的信息

3.1 直接的想法是搜索到头后重新DFS一波

没错TLE了

3.2 后来发现搜索出来的就是叶子节点的数量,而叶子节点的数量是可以在#1时预处理的!

已经在上面了不过还是发一下

```cpp
    ++T[id].downNodeCnt;
```

4全部代码

```cpp
/**
Luogu P2922
Secret Message
*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cmath>
#include <cctype>
#include <string>
#include <cstring>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
struct Node
{
    int leave;
    int downNodeCnt;
    int child[2];
} T[1000100];//!Trie树定义
int Tsize=1;
inline int read()//读入优化
{
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void addMsg(int length,int id=0)
{
    if(!length)
    {
        ++T[id].leave;
        return;
    }
    int t=read();
    //scanf("%d",&t);
    if(T[id].child[t]==0)
        T[id].child[t]=Tsize++;
    addMsg(length-1,T[id].child[t]);
    ++T[id].downNodeCnt;//预处理
}

int searchMsg(int length,int id=0)
{
    int t,ans=0;
    if(T[id].leave!=0)
        ans+=T[id].leave;
    if(length==0)
        return T[id].downNodeCnt+ans;
    //scanf("%d",&t);
    t=read();
    if(T[id].child[t]!=0)
        return ans+searchMsg(length-1,T[id].child[t]);
    else
    {
        --length;
        while((length--)>0)
            read();
        return ans;
    }

}

int M,N;
int main()
{
    M=read();
    N=read();
    int len;
    for(int i=1; i<=M; ++i)
    {
        len=read();
        addMsg(len);
    }
    for(int i=1; i<=N; ++i)
    {
        len=read();
        printf("%d\n",searchMsg(len));
    }
    return 0;
}
```

5 结果

大牛分站 O2 170ms

主站              230ms

拿到当前#1


PS 本题第一篇题解有点小激动

管理员大佬给过啊~


---

