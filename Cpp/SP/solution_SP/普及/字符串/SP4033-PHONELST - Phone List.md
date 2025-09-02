# PHONELST - Phone List

## 题目描述

**【题目来源】**

	Poj3630

**【问题描述】**

	给定n个长度不超过10的数字串，问其中是否存在两个数字串S，T，使得S是T的前缀。有多组数据，数据组数不超过40。n<=10000。

## 样例 #1

### 输入

```
2
3
911
97625999
91125426
5
113
12340
123440
12345
98346```

### 输出

```
NO
YES```

# 题解

## 作者：塔罗兰 (赞：7)

trie树模板题，调到死

UVA那里有一道一模一样的题目，但因为听说UVA炸了所以来这边刷（QAQ后来发现是因为UVA不支持万能头）

做这题建议先去[某篇洛谷日报](https://www.luogu.org/blog/sdlang/Trie-study-text)满足前置知识
```cpp
#include<cstdio>
#include<cstring>//双倍经验后不想改回万能头
#define MAX 100005//数组一定要开大！我这里RE了③次
int cnt;
int trie[MAX][15],end[MAX];
inline void clean()
{
	memset(trie,0,sizeof(trie));
	memset(end,0,sizeof(end));
}//清空
inline int trie_tree()
{
	char s[20];
	scanf("%s",s);//直接输入
	int u(0),l(strlen(s)),r(1);
	for(int j(0);j<l;++j)
	{
		int v(s[j]-'0');
		if(!trie[u][v])
		trie[u][v]=++cnt,r=0;
		u=trie[u][v];
		if(end[u])
		return 1;//之前有一个字符串是此字符串前缀
	}
	end[u]=1;//标记一个字符串的末尾
	if(r)
	return 1;//此字符串是之前一个字符串的前缀
	return 0;
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n,b(0);
		scanf("%d",&n);
		getchar();//读掉回车
		cnt=0;
		for(int i(0);i<n;++i)
		if(trie_tree())
		b=1;
		if(b)
		printf("NO\n");//只有我想吐槽符合条件输出NO吗？
		else
		printf("YES\n");
		clean();//记得清空数组！
	}
}
```
最后：外OJ评测好麻烦啊

---

## 作者：龙翔凤翥 (赞：5)

#### 蒟蒻新学Trie树，本题为Trie树板子题．`
边建立Trie树的时候边判断答案，
1. 若当前串插入后没有任何新建节点，则该串肯定是之前插入的某个串的前缀，
1. 若在插入的时候，有某个经过的节点带有某串结尾的标记，则之前插入的某个串是当前串的前缀．
#####   (详细见注释）
 

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
#define RN register int
const int N=1e5+5;
const int Z=10;
int T,n,tot;
int ch[N][Z];//表示该节点的字符指针指向的节点,若为０，则无子节点
bool bo[N];
char s[20];
inline bool insert(char *s)//插入串，并判断．
{
	int len=strlen(s);
	int u=1;
	bool flag=false;
	for(RN i=0;i<len;i++)
		{
			int c=s[i]-'0';
			if(!ch[u][c])//如果当前这个节点u没有指向c的指针，则建立一个
				ch[u][c]=++tot;
			else if(i==len-1)//如果搜完了，没有插入任何的新节点，则说明该串出现过，第１种情况
				flag=true;
			u=ch[u][c];
			if(bo[u])//如果经过某个有标记的节点，属于第２种情况
				flag=true;
		}
	bo[u]=true;
	return flag;
}
int main()
{

	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		tot=1;//新建一个Trie树，其根节点为１
		memset(ch,0,sizeof(ch));
		memset(bo,false,sizeof(bo));//每次都要初始化
		bool ans=false;
		for(RN i=1;i<=n;i++)
		{
			scanf("%s",s);
			if(insert(s))
				ans=true;
			
		}
		if(!ans)//注意不要写反
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}

```

---

## 作者：xixike (赞：5)

这道题基本上是trie树的模板，trie[i][j]的第一维表示编号为i的点，第二维表示当前数字串的第j个数的值，trie[i][j]存的值是第j个数字的下一个数字。num[i]表示以数字串str[i]为前缀的数字串的个数（**包括它本身**），如果$num[i]=1$，则输出YES, 否则输出NO。

insert函数是插入一个字符串。

find是计算一个字符串在所有字符串中作为前缀的个数
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define N 100010

using namespace std;

int trie[N][20],num[N];
int tot;                            //记录数字的编号
char str[N][20];

void insert(char str[]){            //插入数字串，类似于递归的过程
	int c=0;                        //c表示当前数字串的第几位
	int len=strlen(str);
	for(int i=0;i<len;i++){
		int n=str[i]-'0';
		if(!trie[c][n]) trie[c][n]=++tot;
		c=trie[c][n];
		num[c]++;
	}
}

int find(char str[]){                //顾名思义，查找函数，找以数字串str为前缀的数字串的个数，与上面没什么区别
	int c=0;
	int len=strlen(str);
	for(int i=0;i<len;i++){
		int n=str[i]-'0';
		if(!trie[c][n]) return 0;   //这里判断如果第n个数字的下一位没有，就表示str不是当前数字串的前缀
		c=trie[c][n];
	}
	return num[c];
}

int main(){
	int t,n,flag;
	scanf("%d",&t); 
	while(t--){
		memset(trie,0,sizeof(trie));
		memset(num,0,sizeof(num));
		tot=0;
		flag=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%s",str[i]);
			insert(str[i]);
		}
		for(int i=1;i<=n;i++){
			int x=find(str[i]);
			if(x>1){            //str自己也是自己的前缀
				flag=1;
			}
		}
		if(flag) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
```


---

## 作者：yuzhechuan (赞：4)

### 有陷阱的trie树模板题

- 我有几个优化点:

1. 用结构体

1. 边插入边判断

- 要注意：

1. 结构体也可以直接memset清0

1. **满足**条件输`NO`，**不满足**才输`YES`

- 判断方面有两种情况，代码里会再讲

1. 串2是串1的前缀
```cpp
123
12
```
2. 串1是串2的前缀
```cpp
12
123
```

---

```cpp
#include <iostream>
#include <cstdio>
#include <cstring> //没打万能头是因为我先在poj交的，你懂的。。。
using namespace std;
int t,n,tot;
bool flag;
struct node{ //trie树节点
	int go[10];
	bool end;
}a[100005];
inline void ins(char *s){
	if(flag) return ; //flag=1表示有符合条件的情况且已被找到所以可以尽管跳过
	int x=0,l=strlen(s+1);
	for(int i=1;i<=l;i++){ //遍历每个数字
		int k=s[i]-'0';
		if(!a[x].go[k]) a[x].go[k]=++tot;
		else if(i==l) flag=1; //第一种情况判断：如果1个串的末尾在trie树中已被定义，则它定是前面某个串的前缀
		x=a[x].go[k];
		if(a[x].end) flag=1; //第二种情况判断：如果1个串中的某个字符是前面某个串结尾点，则前面定有一个串是它的前缀
	}
	a[x].end=1;//标记末尾节点
}
int main(){
	scanf("%d",&t);
	while(t--){
		flag=tot=0;
		memset(a,0,sizeof a); //全部清0
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			char c[15];
			scanf("%s",c+1); //我习惯从下标1开始存
			ins(c); //插入trie树
		}
		if(flag) puts("NO"); //注意反着输
		else puts("YES");
	}
}
```

---

这道题还是我lg上A的第1k道题QuQ

---

## 作者：Jelly_Goat (赞：2)

水一发trie板子~  

先说这个题怎么套上板子  
首先我们判断是否有前缀可以边插入边判断  
当我们经过了一个完整的字符串（即当前节点到了一个有标记的节点上）  
就是有前缀  
我们当然也可以无脑先判断一发（比如我这个）  
然后无脑插入就是  
减少了一定的编程难度  

------

然后我~~丧心病狂异想天开~~写了一发动态的trie  
~~指针警告~~  
好处是内存省下来了  
当然删除的时间上来说是省不下来了  
具体看代码（~~代码向预警~~）  

```cpp
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;
//字典集合大小 
const int Z=10;
struct trie{
	//Z个子节点 
    trie *ch[Z];
    //是否存在字符串的标记挂载 
    bool vst;
}rt,*root=&rt;//根节点 
//输入用的字符串 
string input;

void insert(string str)
{
    if (str.size()<1)return ;//空字符串返回 
    trie *now=root;//从根节点开始向下插入 
    for (register int i=0;i<str.size();i++)
    {
        int num=str[i]-'0';//子节点下标 
        if (now->ch[num]==NULL)//需要开一个新的节点 
        {
            now->ch[num]=new trie();//纳新 
            //初始化节点（也可以写到构造函数里 
            for (register int j=0;j<Z;j++)
            {
                now->ch[num]->ch[j]=NULL;//设置成空 
                now->ch[num]->vst=false;//设置不存在当前子节点表示的字符串 
            }
            now=now->ch[num];//向下一个节点移动 
        }
        else now=now->ch[num];//向下一个节点移动 
    }
    now->vst=true;//挂载当前字符串 
}

bool find(string str)
{
    if (str.size()<1)return true;//空字符串走人 
    trie *now=root;//从根节点开始 
    for (register int i=0;i<str.size();i++)
    {
        int num=str[i]-'0';//下标 
        //如果存在没有插入的节点，而且没有经过任何一个完整的字符串，
		//一定是不存在任何一个字符串与其为前缀关系 
        if (now->ch[num]==NULL)return false;
        else
        {
        	//经过一个完整的字符串，即经过的这个字符串
			//是str的前缀 
        	if (now->ch[num]->vst)return true;
        	now=now->ch[num];//向下一个节点移动 
		}
    }
    //存在另一个字符串包含这个字符串
	//即有另一个字符串使得这个字符串是其前缀 
    return true;
}
//无脑删除，回收空间 
void dfs(trie *now)
{
	for (register int i=0;i<10;i++)
	{
		if (now->ch[i]!=NULL)
			dfs(now->ch[i]);
	}
	if (now!=root)delete now; 
}
//重新建树 
void build()
{
	dfs(root);
	for (register int i=0;i<10;i++)
	{
		root->ch[i]=NULL;
	}
	root->vst=false;
}

int main()
{
    int T,n;
    cin>>T;
    while (T--)
    {
    	bool flag=false;
    	//先重新建空树 
    	build();
    	cin>>n;
    	while (n--)
    	{
    		cin>>input;
    		//只要是存在前缀关系就行 
    		flag=find(input)||flag;
    		insert(input);
		}
		//存在即NO 
		puts(flag?"NO":"YES");
	}
    return 0;
}
```

---

## 作者：Beyond616 (赞：1)

不知为何题解里写的都很麻烦，蒟蒻有个新方法，斗胆写下

```
#include<cstdio>
#include<cstring>
#define N 100007
struct node
{
	int head;
	int data;
}e[N];
int tot=0,cnt[N];
void add(int h,int dt)
{
	e[++tot].head=cnt[h];
	e[tot].data=dt;
	cnt[h]=tot;
}
void trie(int n)
{
	char c[102];
	bool ans=false;
    //ans指是否找到一个符合题意的答案
	memset(e,0,sizeof(e));
	memset(cnt,0,sizeof(cnt));
	for (int i=1;i<=n;i++)
	{
		scanf("%s",c);
		if (ans) continue;
		int len=strlen(c),now=0,p=0,zip=true;//zip（名字有点奇怪）是指整个Trie树里该字符串是否与其他串产生前缀关系
      //p指当前跳到的点的编号，now指当前判断到几号字符
		while (now<=len-1)//判断每个字符
		{
			bool op=false;//op是该字典树里是否有该字符
			for (int j=cnt[p];j;j=e[j].head)
			{
				if (e[j].data==c[now])//Trie树里找到字符
				{//jump！
					op=true;
					p=j;
					break;
				}
			}
			if (!op)
			{
				if (cnt[p]||i==1) zip=false;
//大家可以画个图方便理解，当该字符串走到非叶子节点时将要开辟新分支，那它一定不与之前的任何一个字符串产生前缀关系
//假如它走到了叶子节点并往下开辟分支，那么一定有前缀关系
				add(p,c[now]);
				p=tot;
			}
			now++;
		}
		if (zip)
		{
			ans=true;
			printf("NO\n");
		}
	}
	if (!ans) printf("YES\n");
}
int main()
{
	int t,n;
	scanf("%d",&t);
	while (t--)
	{
	    tot=0;//一定记得清零！我改了一天[笑哭]
		scanf("%d",&n);
		trie(n);
	}
	return 0;
}
```


---

## 作者：AFOier (赞：1)

刚学OI的蒟蒻来水一发题解~

算法：$Trie$

前面的题解都是直接边插入边判断的，所以还要在每个串的末尾加上一个标记，~~一点都不麻烦~~。而因为题目中要求S为T的前缀，所以length(S)<=length(T)。

从而我们可以先将输入的字符串按从长到短排序，在进行插入操作。这样就可以避免在串的末尾加标记的操作，而直接判断插入字符串时是否需要新建节点。

我知道这样很慢，但是$40*10000*log(10000)$跑起来也是能过的。。。

注意：如果存在两个数字串S，T，使得S是T的前缀，那么输出**NO**，否则输出**YES**

```
#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
int T,n,tot;
bool suc,success;
string b[10001];
struct trie{
	int son[10];
}a[1000001];
void insert(string l,int w,int now){
	if(w>=l.size())return;
	int num=l[w]-'0';
	if(!a[now].son[num]){
		a[now].son[num]=++tot;
		suc=false;
	}
	insert(l,w+1,a[now].son[num]);
}
bool cmp(string p1,string p2){
	return p1.size()>p2.size();
}
int main(){
	scanf("%d",&T);
	for(int t=1;t<=T;t++){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)cin>>b[i];
		sort(b+1,b+n+1,cmp);
		tot=0;success=false;
		for(int i=1;i<=n;i++){
			suc=true;
			insert(b[i],0,0);
			if(suc==true){cout<<"NO"<<endl;success=true;break;}
		}
		if(success==false)cout<<"YES"<<endl;
		for(int i=0;i<=tot;i++){
			for(int j=0;j<10;j++)
			a[i].son[j]=0;
		}
	}
}
```


---

## 作者：Nartsam (赞：1)

### Trie树板子题

边插入边判断即可

一些小的注意事项：

1. 对于每组数据，不要忘了初始化
2. 空间要开大一些
3. 可以把Trie树写到一个结构体里，方便操作
4. 在修改前一定要判断下标是否小于0，我一开始没有注意这一点RE了好几次。。。

代码如下：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cctype>
using namespace std;
const int MAXN=10000+7;
char s[MAXN][13];
struct Trie{  //Trie树结构体
	int num[MAXN*100],t[MAXN*100][13],tot;
	void init(){  //初始化
		tot=0;
		memset(t,0,sizeof(t));
		memset(num,0,sizeof(num));
	}
    //以下为插入，传地址进去可以避免数组的复制
	void Insert(char *str){
    	int len=strlen(str),poi=0;
    	for(int i=0;i<len;++i){
    	    int ch=str[i]-'0';
    	    if(!t[poi][ch]){
    	    	t[poi][ch]=++tot;
			}
    	    poi=t[poi][ch]; ++num[poi];
    	}
    }
    //以下为查找
    int Find(char *str){
    	int len=strlen(str),poi=0;
    	for(int i=0;i<len;++i){
    	    int ch=str[i]-'0';
    	    if(poi<0) continue; //一定要判断是否小于0！！！
			poi=t[poi][ch];
    	    if(num[poi]==1) return 0;
		}
		return 1;
	}
}trie;
int T,n;    //T为数据组数
int main(){
    scanf("%d",&T);
    while(T--){
        trie.init();   //不要忘记初始化
        scanf("%d",&n);
        for(int i=1;i<=n;++i){
            scanf("%s",s[i]); trie.Insert(s[i]);
        }
        bool flag=0;
        for(int i=1;i<=n;++i){
            if(trie.Find(s[i])){  //如果是前缀，直接退出
                flag=1; break;
            }
        }
        if(!flag) puts("YES");
		else puts("NO");
    }
    return 0;
}
```


---

## 作者：冒泡ioa (赞：1)

虽然我很想说这是一道字典树模板题，但是还是有点技巧的。  
对于每组输入，我们先把它存入字典树，然后再来查找（也就是所谓的离线）   
为了说明方便，用表格说明一下变量吧  

| 变量名 | 变量作用 |
| ------ | ------ |
| $st$ | 保存读入的字符串，用于离线 |
| $word$ | 保存字典树每条边被覆盖的次数，遍历时为1说明不是前缀 |
| $ch$ | 字典树，第一维是编号，第二维是哪条边，值为指向的点 |
| $sz$ | 用来编号，类似于链式前向星里的$tot$ |
关键是遍历的时候，只要word为1就返回0（就是它自己啊），能顺利的走下来就返回1  
欢迎来我[博客](https://bubbleioa.github.io/2018/08/22/[UVA11362]Phone%20List/)玩~
## 代码
```c++
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAX = 1e5 + 10;
int t,n;
char st[10100][10];
int word[MAX],ch[MAX][10],sz;

void reset(){//每组数据需要重置
   sz = 1;
   memset(ch[0],0,sizeof(ch[0]));
   memset(word,0,sizeof(word));
}

void insert(char *s){//插入进字典树
    int nl = strlen(s),u = 0;
    for(int i = 0 ; i < nl ;i++){
        int c = s[i] - '0';
        if(! ch[u][c]){
          memset(ch[sz],0,sizeof(ch[sz]));
            ch[u][c] = sz++;
        }
        u = ch[u][c];
        word[u]++;
    }
}

int find(char *s){//是否是前缀
   int nl = strlen(s),u = 0;
   for(int i = 0; i < nl; i++){
        int c = s[i] - '0';
        u = ch[u][c];
        if(word[u] == 1) return 0;
   }
   return 1;
}

int main(){
    cin>>t;
    while(t--){
        reset();
        scanf("%d",&n);
        for(int i = 1 ; i <= n; i++){
            scanf("%s",st[i]);
            insert(st[i]);
        }
        int ok = 1;
        for(int i = 1 ; i <= n; i++)
            if(find(st[i])){
                ok = 0;
                break;
            }
        if(ok) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
```

---

## 作者：Lalenture (赞：1)

一个字典树--

	include <bits/stdc++.h>

	define N 400010

	using namespace std;

	int T,n,ch[N][11],tot,pre[N],ove[N];//数字只有十个顾第二维开到11

	bool bo[N],flag;

	char s[20];

	void insert(char *s) {

	int len = strlen(s);//字符串的长度
	int u = 1;//根节点
	for(int i = 0; i < len ; i++) 
	{
   	 int c = s[i] - '0';
    	if(!ch[u][c])//如果这个数字不在字典树内，就加入
    	{
       	 ch[u][c] = ++tot;
	    }
 	   u = ch[u][c];//更新节点
  	  pre[u]++;
    	if(ove[u])  {flag = 1 ;return;}
   	 if(bo[u])   flag = true;//经过某跟被标记的节点 
	}
	ove[u] = 1;
	if(pre[u] > 1)
	{
 	   flag = true;
 	   return;
	}
	}

	int main() {

	scanf("%d",&T);
	while(T--)
	{
    scanf("%d",&n);
    tot = 1;
    flag = false;
    memset(ch,0,sizeof(ch));
    memset(pre,0,sizeof(pre));
    memset(ove,0,sizeof(ove));
    bool ans = false;
    for(int i = 1; i <= n ;i++) 
    {
        scanf("%s",s);
        if(flag == false)
        insert(s);
    }
    if(flag)    puts("NO");
    else puts("YES");
	} 
	return 0;
	}

---

## 作者：QiFeng233 (赞：0)

这是 Trie 树的一道很简单的练手题。~~双倍经验~~  
# 思路
把所有字符串插入 Trie 树中，标记一下某个节点是不是某个字符串的结尾，然后对 Trie 树做一次 Dfs ，如果某一个节点是结尾，并且之前已经找到过某个字符串的结尾，那么就输出 NO ，否则输出 YES 。
# 代码
```cpp
#include<cstdio>
#include<cstring>
namespace QiFeng233{
	const int maxn=1e4+10;
	int trie[maxn*10][10],ind=1;
	int t,n;
	char str[15];
	bool end[maxn*10];
	void insert(char* str){
		int len=strlen(str),p=1;
		for(int i=0;i<len;++i){
			int ch=str[i]-'0';
			if(trie[p][ch]==0)trie[p][ch]=++ind;
			p=trie[p][ch];
		}
		end[p]=1;
	}
	bool dfs(int p,bool pre){
		bool ans=false,ed=pre|end[p];
		if(pre&&end[p])return true;
		for(int i=0;i<=9;++i){
			if(trie[p][i]==0)continue;
			ans|=dfs(trie[p][i],ed);
		}
		return ans;
	}
	void solve(){
		scanf("%d",&t);
		while(t--){
			memset(trie,0,sizeof(trie));
			memset(end,0,sizeof(end));
			ind=1;
			scanf("%d",&n);
			for(int i=1;i<=n;++i){
				scanf("%s",str);
				insert(str);
			}
			printf("%s\n",dfs(1,0)?"NO":"YES");
		}
	}
}
signed main(){
	QiFeng233::solve();
	return 0;
}
```

---

## 作者：andyli (赞：0)

考虑将所有的字符串构成一棵$Trie$，在构建过程中可以顺便判断答案。若当前串插入后没有新建任何结点，则当前串肯定是之前插入的某个串的前缀；若插入过程中，有某个经过的结点带有串结尾标记，则之前插入的某个串是当前串的前缀。依据上面两种情况判断结果。  
代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100005;

struct Trie
{
    int ch[maxn][10], cnt;
    bool vis[maxn];
    int idx(char ch) { return ch - '0'; }
    bool insert(char* s)
    {
        int u = 0, n = strlen(s);
        bool flag = false;
        for (int i = 0; i < n; i++)
        {
            int c = idx(s[i]);
            if (!ch[u][c])
                ch[u][c] = ++cnt;
            else if (i == n - 1)
                flag = true;
            u = ch[u][c];
            if (vis[u])
                flag = true;
        }
        vis[u] = true;
        return flag;
    }
    void clear()
    {
        cnt = 0;
        memset(ch, 0, sizeof(ch));
        memset(vis, 0, sizeof(vis));
    }
} trie;
char s[20];
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n;
        scanf("%d", &n);
		trie.clear();
        bool ans = false;
        for (int i = 1; i <= n; i++)
            scanf("%s", s), ans |= trie.insert(s);
        printf("%s\n", ans ? "NO" : "YES");
    }
    return 0;
}
```

---

## 作者：wanghanjun (赞：0)

水一发题解~~~

这应该算是一道比较裸的trie吧。。。

插入和正常的trie一样，查询时直接dfs一遍，如果出现一个结点既是一个单词的结束还有子节点，那么就存在一个字符串是另一个的前缀。

然后就是有输出NO，没有输出YES。但如果认真读题就问题不大。

这里是一份完(chou)美(lou)无(wu)缺(bi)的代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=102113;
struct node{
	int next[11];
	int end;
}t[MAXN];
int n,m,cnt;
char a[1021];
//1021是真理！！！

bool dfs(int id){
	bool ans=0,x=0;
	if(t[id].end){
		for(int i=0;i<=9;i++){
			if(t[id].next[i])
			    return 1;
		}
	}//如果存在上述情况返回1
	for(int i=0;i<=9;i++){
		if(t[id].next[i]){
			ans=(ans|dfs(t[id].next[i]));
		}
	}//任意一子树成立则成立
	return ans;
}//查询

int main(){
	scanf("%d",&m);
	for(int k=1;k<=m;k++){
		memset(t,0,sizeof(t));
		cnt=1;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%s",&a);
			int id=1;
			for(int j=0;a[j];j++){
				if(!t[id].next[a[j]-'0']){
					cnt++;
					t[id].next[a[j]-'0']=cnt;
				}
				id=t[id].next[a[j]-'0'];
			}
			t[id].end++;
		}//插入
		if(dfs(1)==0) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

---

