# Phone List

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=25&page=show_problem&problem=2347

[PDF](https://uva.onlinejudge.org/external/113/p11362.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11362/86a9ad22547794c86c707c6301a3959ca76cfd43.png)

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

## 作者：doyo (赞：50)

其实这道题不用trie树也行

快排：“劳资除了能排数字，也能排字符串！”

再加上一点小小的字符串函数 

就有了这种做法
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;
string s[10001];
int main()
{
    int k,n;
	scanf("%d",&k);
    while(k--)
    {
        bool flag=false;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            cin>>s[i];//这里不知道怎么用标准输入输出，汗 
        sort(s+1,s+n+1);//快排神通，将字符串排序
        for(int i=1;i<=n-1;i++)
        {
            if(s[i+1].find(s[i],0)==0)// find函数判断是不是前缀 
            {
                flag=true;
                break;
            }
        }
        if(flag) printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}
```
怎么样，很简单吧。

本人第一次写题解，请多多关照

---

## 作者：Adaxy (赞：8)

看到这道Trie水题
蒟蒻决定写蒻生第一篇题解

直接上代码

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
//某坑人(pia,对大佬不敬)oj无法使用万能库 
using namespace std;
int n,trie[100005][10],tot=1,endd[100005],t,flag,vis[100005];
//数组不要太大 ，详情见下方 
void insert(char* a)
{
	int len=strlen(a),p=1;
	for(int k=0;k<len;k++)
	{
		int ch=a[k]-'0';
		if(!trie[p][ch]) 
		{
			trie[p][ch]=++tot;
			vis[p]=1;
		}
		if(endd[p])	//如果此节点为之前某字符串终点，说明此前字符串是此次字符串的子串 
		{
		    flag=0;return ;
		}
		p=trie[p][ch];
	}
	if(vis[p]) flag=0;//如果此次字符串最终所在位置已被访问，说明这是之前某字符串的子集  
	endd[p]=1; //标记终点位置 
	return ;
}

int main()
{
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{
		tot=1;flag=1;
		memset(trie,0,sizeof(trie));
		memset(endd,0,sizeof(endd));
		memset(vis,0,sizeof(vis)); //如果开太大，直接TLE 
		scanf("%d",&n);
		//重置 
		for(int j=1;j<=n;j++)
		{
			char a[12];
			scanf("%s",a);
			if(flag) insert(a); //如之前出现不符合，就直接跳过 
		
		}
		if(flag) puts("YES");   //puts特效，自动“\n” 
		else puts("NO");
	
	}
	return 0;
}
```




---

## 作者：swiftc (赞：5)

一道很简单的字典树模版题

__字典树是什么?__

简单的说，字典树就是把很多个字符串合并在一起，如下图一样的树，详细建立的方法可以看我的代码
![https://s2.ax1x.com/2019/06/15/VIwGuR.png](https://s2.ax1x.com/2019/06/15/VIwGuR.png)

我们把所有的电话号码建成一颗字典书，在插入的过程住如果发现有结束标记，或者结束时发现这个节点还有儿子，就输出$NO$，如果没有发现这种情况就输出$YES$

__代码：__

```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt;
struct trie{
	int son[10],end=0;
}a[1000001];
int main(){
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++){
		memset(a,0,sizeof(a));
		int n;
		cnt=0;
		scanf("%d",&n);
		bool flag=0;
		for(int j=1;j<=n;j++){
			string s;
			cin>>s;
			int now=0;
			for(int k=1;k<=s.length();k++){
				if(a[now].son[s[k-1]-'0']){
				now=a[now].son[s[k-1]-'0'];	
				}
				else{
				a[now].son[s[k-1]-'0']=++cnt;
				now=cnt;
				}
				if(a[now].end==1){
					flag=1;
				}
				if(k==s.length()){
					for(int i=0;i<=9;i++){
						if(a[now].son[i])flag=1;
					}
					a[now].end=1;
				}
			}
		}
		if(flag){
			puts("NO");
		}
		else{
		puts("YES");
		}
	}
	return 0;
}
```


---

## 作者：谦谦君子 (赞：4)

这题其实就是一个trie的板子，蒟蒻竟然~~手打一遍过~~了!!!（[题目链接poj3630](http://poj.org/problem?id=3630)) 

## 思路：
**我们可以考虑把每一个字符串都构成一棵trie树，在构建过程中判断答案。**
# 结果判断：
**若当前的串插入后没有新建结点，则当前串一定是之前某个串的前缀，若插入过程中，若某个经过的结点带有串结尾标记则之前插入的某个串是当前串的前缀。**

# 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const int Z=10;
int T,n,tot;
int ch[N][Z];						//储存trie树
bool bo[N];
char s[20];
bool insert(char *s)					//插入字符串
{
	int len=strlen(s);
	int u=1;
	bool flag=false;
	for (int i=0;i<len;++i)
	{
		int c=s[i]-'0';
		if (!ch[u][c])
		{
			ch[u][c]=++tot;
		}
		else if (i==len-1)
		{
			flag=true;			//没有插入任何新结点
			return flag;
		}
		u=ch[u][c];
		if (bo[u])
		{
			flag=true;			//经过某个有标记的结点
			return flag;
		}
	}
	bo[u]=true;
	return flag;
}
int mian()						//咳咳，自行发现
{
	cin>>T;
	while (T--)
	{
		cin>>n;
		tot=1;
		memset(ch,0,sizeof(ch));
		memset(bo,false,sizeof(bo));
		bool ans=false;
		for (int i=1;i<=n;++i)
		{
			cin>>s;
			if (insert(s))
			{
				ans=true;
			}
		}
		if (!ans)
		{
			puts("YES");
		}
		else
		{
			puts("NO");
		}
	}
	return 0;
}
```


---

## 作者：Celtic (赞：3)

### 之前的题解有bug，现已修复

- $Trie$树即字典树。

- 每个节点表示一个字符串（的前缀）。其字符集大小为$∑$，则每个节点有$∑$个儿子指针，指向代表在这个节点后添加某字符得到字符串的节点。

下图就是一棵$Trie$树。
![](https://cdn.luogu.com.cn/upload/image_hosting/cga4onqg.png)

- 构造$Trie$的方法十分简单，从根节点开始，按顺序遍历串的每个字符，若该节点代表该字符的指针无儿子节点，则新建，然后指针移动到这个儿子节点即可。

- 构造出多个串的$Trie$后，还可以查询对于一个给定串为多少个已知串的前缀，给定串与所有已知串的最长公共前缀等。

这道题就是模板题。

代码
```cpp
#include<bits/stdc++.h>
#define eps 1e-7
#define re register
#define N 100101
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
ll n,trie[N][15],tot,t;
char s[N];
bool b[N];
ll ans;
inline void insert()
{
	re ll len=strlen(s+1),p=0;
	bool flag=false;
	for(re int i=1;i<=len;i++)
	{
		re ll c=(s[i]^48);
		if(!trie[p][c])
			trie[p][c]=++tot;
		else if(i==len)
			flag=true;
		ans+=b[p];
		p=trie[p][c];
	}
	b[p]=true;
	ans+=flag;
	return;
} 
int main()
{
	read(t);
	while(t--)
	{
		tot=0;
		ans=0;
		memset(trie,0,sizeof(trie));
		memset(b,0,sizeof(b));
		read(n);
		while(n--)
		{
			scanf("%s",s+1);
			insert();
		}
		printf("%s\n",ans?"NO":"YES");
	}
	exit(0);
}
```




---

## 作者：唔啊唔 (赞：3)

此题个人认为难度应该算不上紫题，差不多是一道模板吧。

不多做解释上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,node[1000000][30],cnt[1000000],c=1;
char a[1000000];
inline void tree(){
	int u=1,len=strlen(a);
	for(register int i=0;i<len;i++){
		if(node[u][a[i]-'0']==0){
			c++;
			node[u][a[i]-'0']=c;
			u=c;
		}
		else{
			u=node[u][a[i]-'0'];
		}
	}
	cnt[u]=1;	//这是关键,判断之前的是自己的前缀 
	return;
}
inline int trie(){
	int u=1;
	for(register int i=0;i<strlen(a);i++){
		if(node[u][a[i]-'0']!=0){
			u=node[u][a[i]-'0'];
		}
		else{
			if(cnt[u]==1)return 1;//找完了,前面的是自己的前缀 
			return 0;
		}
	}
	return 1;
}
int main(){
	int t,q;
	cin>>t;
	for(register int k=1;k<=t;k++){
		q=0,c=1;
		memset(node,0,sizeof(node));
		memset(cnt,0,sizeof(cnt));
		cin>>n;
		for(register int i=1;i<=n;i++){
			scanf("%s",&a);
			if(trie()==1){
				q=1;
			}
			tree();
		}
		if(q==1)cout<<"NO"<<endl;
		else cout<<"YES"<<endl;
	}
	return 0;	
}
```
本人话少，仔细体会。

---

## 作者：Celebrate (赞：3)

这一题的字典树就不详细解释了

我们在建立字典树的时候顺便查找：

(1)当前搜索到某一个字符串的结束点；

(2)你的结束点已经被找过了：

这一就可以直接判断了，代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
using namespace std;
int tot,trie[110000][11];
int root;
bool end[110000],flag;
bool vis[110000];
char a[15];
void bt(){
    int x=root,len=strlen(a+1);
    for(int i=1;i<=len;i++){
        int y=a[i]-'0';
        if(trie[x][y]==-1)trie[x][y]=++tot;
        x=trie[x][y];
        if(vis[x]==true&&i==len){flag=1;return;}
        vis[x]=true;
        if(end[x]){flag=1;return;}
    }
    end[x]=true;
}
int main(){
    int tt;scanf("%d",&tt);
    while(tt--){
        tot=1;root=1;flag=0;
        memset(trie,-1,sizeof(trie));
        memset(end,false,sizeof(end));
        memset(vis,false,sizeof(vis));
        int t;scanf("%d",&t);
        while(t--){
            scanf("%s",a+1);
            if(!flag)bt();
        }
        if(flag)printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}
```

---

## 作者：da32s1da (赞：1)

注意到，这里都是数字！

于是！~~用什么字典树~~

用**map**解决。

我们读入一个数字$x$，然后
```
while(x>0)do sth,x/=10;
```
没错，我们取出了$x$所有的前缀。

每次去map中查找有没有即可。

----

但这样是AC不了的。

因为可能**后面的数是前面的数的前缀**。

**排序**即可。

----

这样还不行，有**前导零**。

我们在每个数前面放一个$1$，不会影响答案。

```
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<unordered_map>
using namespace std;
typedef long long LL;
const int N=1e4+50;
int t,n,len;
LL x,a[N];
char S[15];
unordered_map<LL,int>s;
int main(){
	for(scanf("%d",&t);t;t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%s",S);
			a[i]=1;
            //解决前导零：数前面放一个1
			len=strlen(S);
			for(int j=0;j<len;j++)a[i]=a[i]*10+S[j]-48;
		}
		sort(a+1,a+n+1);
        //从小到大排序，同时位数肯定递增。
        //这样保证后面的数不可能是前面数的前缀
		for(int i=1;i<=n;i++){
			x=a[i];
			while(x>0){
				if(s.find(x)!=s.end())x=-1;
				else x/=10;
                //每次查找x的前缀
			}
			if(x==-1)break;
			s[a[i]]=1;
            //自己插到map中
		}
		if(x==-1)puts("NO");
		else puts("YES");
		s.clear();
        //清空map
	}
}
```

---

## 作者：hyfhaha (赞：1)

## phone list
题目：[Phone list](https://www.luogu.org/problemnew/show/UVA11362)

前置技能：[Trie](https://www.luogu.org/blog/juruohyfhaha/trie-xue-xi-zong-jie)

题目意思十分明确，求有没有一个字符串是其他字符串的前缀，如果有就返回"NO"，没有返回"YES"。

这题和前面讲的Trie的作用一模一样，可以快速判断一个字符串是不是已插入的字符串中的前缀。

那么这道题就很简单了，我们先将全部字符串都插入到Trie中。

然后查找每一个字符串，如果字符串下有儿子，那么就代表当前字符串是某个字符串的前缀，直接返回。

代码实现也很简单，可以算是Trie的模板题。
```cpp
#include<bits/stdc++.h>
using namespace std;
struct kkk{
    int son[11],sum;
    bool flag;
    void clear(){memset(son,0,sizeof(son));sum=0;flag=0;}   //清0
}trie[400001];
int n,T,num;
string S[400001];
void insert(string s){
    int len=s.size(),u=0;
    for(int i=0;i<len;i++){
        int v=s[i]-'0';
        if(!trie[u].son[v])
        trie[u].son[v]=++num;
        trie[u].sum++;          //表示u有多少个儿子
        u=trie[u].son[v];
    }
    trie[u].flag=true;
}
int find(string s){
    int len=s.size(),u=0;
    for(int i=0;i<len;i++){
        int v=s[i]-'0';
        if(!trie[u].son[v])return 0;        //找不到字符串就返回
        u=trie[u].son[v];
    }
    if(trie[u].sum==0)return 0; //如果没有儿子就代表不是前缀
    return 1;           //否则就是前缀
}
int main(){
    scanf("%d",&T);
    while(T--){
        num=0;      //记得清0
        for(int i=0;i<=400000;i++)trie[i].clear();  //记得清0
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            cin>>S[i];
            insert(S[i]);       //一个一个插入
        }
        bool ans=false;
        for(int i=1;i<=n;i++){
            int res=find(S[i]); //查询
            if(res==1){ans=true;break;} //判断是不是前缀
        }
        if(ans==true)printf("NO\n");    //输出
        else printf("YES\n");
    }
}
```

# 双倍经验（UVA644 Immediate Decodability）
题解：[题解 UVA644 【Immediate Decodability】](https://www.luogu.org/blog/juruohyfhaha/solution-uva644)

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

## 作者：mol_low (赞：0)

看着题面中的"前缀"，我们很容易就想到了与前缀相关的数据结构:字典树(Trie)树(不懂者详见[我的博客](https://www.luogu.org/blog/23j/zi-dian-trie-shu)或[~~一个蒟蒻~~的博客](https://www.luogu.org/blog/deng-feng-chui-lai/trie-shu))。

对于包含关系(即题目中的前缀关系)，我们可以发现：在建树过程中，若一个字符串$s$的末位元素还有子节点，显然存在包含关系，我们只需要建树时对每个字符串的末位节点打上标记，然后对于每个字符串跑一遍即可。因为$|s|<=10$，所以常数可以忽略不计，时间复杂度$O(n)$。

$Code:$
```cpp
#include <cstdio>
#include <cstring>
#define N 10000

int T , n , tot;
char s[N + 2][11];
int tree[N * 10 + 2][10];
int son[N * 10 + 2];
bool color[N * 10 + 2];

void insert(char c[]) {
	int root = 1;
	int len = strlen(c);
	for(int i = 0; i < len; i ++) {
		int x = c[i] - '0';
		if(!tree[root][x]) tree[root][x] = ++ tot , son[root] ++;
		root = tree[root][x];
	}
	color[root] = 1;
}

bool check(char c[]) {
	int len = strlen(c);
	int root = 1;
	for(int i = 0; i < len; i ++) {
		int x = c[i] - '0';
		root = tree[root][x];
	}
	if(color[root] and son[root]) return  1;
	return 0;
}

int main() {
	scanf("%d", &T);
	while(T --) {
		tot = 1;
		memset(tree , 0 , sizeof(tree));
		memset(son , 0 , sizeof(son));
		memset(color , 0 , sizeof(color));
		scanf("%d", &n);
		for(int i = 1; i <= n; i ++) {
			scanf("%s", s[i]);
			insert(s[i]);
		}
		bool flag = 0;
		for(int i = 1; i <= n; i ++)
			if(check(s[i])) {
				printf("NO\n");
				flag = 1;
				break;
			}
		if(!flag) printf("YES\n");
	}
	return 0;
}
```


---

## 作者：反班长者 (赞：0)

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

const int M=10;

int kkk,n,tot;

int chsh[N][M];//数组存储Trie树

bool zhechen[N];

char kao[20];

void clear()//这是一个初始化的函数
{
    memset(chsh,0,sizeof(chsh));
    
    memset(zhechen,false,sizeof(zhechen));
}
bool insert(char *kao)//插入一个字符串，同时判断答案
{
    int len=strlen(kao);
    
    int u=1;
    
    bool flag=false;
    
    for(int i=0;i<len;i++)
    {
        int c=kao[i]-48;
          
          if(!chsh[u][c])
          
          chsh[u][c]=++tot;
          
          else if(i==len-1)
          
          flag=true;//木有插入任何节点
         
          u=chsh[u][c];
          
          if(zhechen[u])flag=true;//经过某个有标记的节点
    }
    zhechen[u]=true;
    
    return flag;
}
int main()
{
    scanf("%d",&kkk);
    
    while(kkk--)
    {
        
        scanf("%d",&n);
        
        tot=1;//表示新建一个空节点作为Trie树的根
        
        clear();
       
        bool ans=false;
        
        for(int i=1;i<=n;i++)
        {
            scanf("%s",kao);
            
            if(insert(kao))ans=true;
        }
        if(!ans)cout<<"YES\n";
       
       else cout<<"NO\n";//愉快地输出答案
    }
    return 0;
}
//蒟蒻第一次写题解，管理大大求过！！！
```

---

## 作者：风火 (赞：0)

```cpp
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=100024;
int n,flag,cnt=1,t;
int tree[maxn][11],ove[maxn],pre[maxn];
char s[maxn];
void get_in(char* str)
{
	int len=strlen(str),p=1;
	for(int i=0;i<len;i++)
	{
		int c=str[i]-'0';
		if(tree[p][c]==0) tree[p][c]=++cnt;
		p=tree[p][c];
		pre[p]++;
		if(ove[p])
		{
			flag=1;
			return ;
		}
	}
	ove[p]=1;
	if(pre[p]>1)
	{
		flag=1;
		return ;
	}
}
/*思路：
整体可以用一个字典树来解决
~~~~~~~~~~~~~~~~~~~~~
用一个ove数组标记以当前节点结尾的数
用一个pre数组来记录路径，表示走过当前节点的字符串有多少条
最后在每次将字符串加入到字典树里面去的时候，判断当前节点是否曾经有过字符串以此节点结尾，若有那么之前的字符串就是当前字符串的子串，就可以结束
最后再判断当前字符串的结束节点的路径有多少条，若超过一条，那么当前字符串就是之前出现的字符串的子串
注意：数组不能开太大
over~~~~~~
*/
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		memset(ove,0,sizeof(ove));
		memset(pre,0,sizeof(pre));
		memset(tree,0,sizeof(tree)); 
		flag=0; cnt=1;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%s",s);
			if(flag==0)
				get_in(s);
		}
		if(flag) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
```

---

