# Immediate Decodability

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=8&page=show_problem&problem=585

[PDF](https://uva.onlinejudge.org/external/6/p644.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA644/ef8ec58ea23c0b0f28ccca6a9cb8b526b259834f.png)

## 样例 #1

### 输入

```
01
10
0010
0000
9
01
10
010
0000
9```

### 输出

```
Set 1 is immediately decodable
Set 2 is not immediately decodable```

# 题解

## 作者：Goodrage (赞：7)

## 无trie之trie在哪里？？？

好啊，不会trie树的我，就不用trie树！

#### 解题思路
直接一个暴力：排序，然后看看一个字符串后面的包不包括他自己就可以了。

#### 难点

1.输入：没有数据组数，必须等输入一个 $9$ 才可以停止输入。所以这里用了一个 $setcnts$ 来记录一共几组数据，每遇到一个 $9$ 就++；用 $strcnts$ 去记录当前一组数据一共有多少个，每遇到一个不是 $9$ 的字符串就++。其他事情，等遇到 $9$ 后再做处理。

2.变量清空：~~十年OI一场空，多组不清见祖宗！~~ 多组数据后，变量一定要清！我就因为变量没清空WA了好几次。每次出现 $9$ 时必须把 $strcnts$ ， $getstr$ 清空！用来存储数据的 $str$ 数组就不用清空了，因为 $strcnt$ 重新循环，会覆盖掉原来的数据；而之前后面多出来的不会被扫描到。

#### 上代码
```cpp
//勿抄
#include<bits/stdc++.h>
using namespace std;
string str[101010];//存数据
string temp; //临时变量，用来存输入，判断是不是⑨。
int setcnts;//一共几组数据
int main()
{
    bool getstr=0;//有没有是前缀的字符串，后面用到。
    int strcnts=0;//本组有几个字符串。
    while(cin>>temp)
    {
    	if(temp=="9")//一组输入结束。
    	{
    		setcnts++;//查组数
			sort(str+1,str+strcnts+1);//排序
	        for(int i=1;i<strcnts;i++)
	        {
	            if(str[i+1].find(str[i],0)==0)//发现前缀
	            {
	                printf("Set %d is not immediately decodable\n",setcnts);
	                getstr=1;//标记有前缀
	                break;
	            }
	        }
	        if(getstr==1)//有前缀
	        {
	        		strcnts=0;//清空！清空！我被这个坑了好几回了。
					getstr=0;//同上
					continue;
	        }
			else
       {
        	 printf("Set %d is immediately decodable\n",setcnts);//没前缀
			strcnts=0;//清空！清空！我被这个坑了好几回了。
			getstr=0;//同上
    	}
    	else//是数据，这一组还没结束。
    	{
    		strcnts++;//这组多了一个数据。
    		str[strcnts]=temp;//放入数组
    	}
    }
    return 0;
} 

```
#### 结果
[我没有UVA，所以在LOJ上交了。](https://loj.ac/s/1038290)

~~过不过都没事，只是分享做法而已~~

---

## 作者：AKakA (赞：3)

# 这道题是典型的字典树的模板题
字典树构造思路：

依次处理n个单词，对于每个单词，从根节点出发按照单词中字符出现的顺序走边。如果边不存在，就新建边和孩子节点。

```cpp
int tot, ch[L][R], b[L];
char s[N][M];          
//tot:树中节点总数，节点编号 0-tot，0是根节点
//ch[L][M] 表示编号为i的节点是否有字符j代表的边连向孩子，若存在 ch[i][j] = 孩子编号，否则 ch[i][j] = 0
//b[i]表示编号i的节点是否对应一个单词。

for (int i=0;i<n;++i)
{
    int u=0;              //从根出发
    int len=strlen(s[i]);
    for (int j=0; j<len;++j)
	{
        int c = s[i][j] - 'a';
        if (!ch[u][c])
		{  
            ch[u][c]=++tot;        //边不存在，新建边和节点
        }
        u=ch[u][c];
    }
    b[u]=1;             //每个单词结尾字符对应的节点的b[i] = true

}
```
**AC代码（思路见代码）**
```cpp
#include<bits/stdc++.h>
using namespace std; 

char s[101][101];  //s[第几个字符串][字符串里第几个字符]
int ch[101][2];    //见上
bool b[101];       //见上
int p,t=0,flag,tot;    //p为第几组数据，t是每组数据字符串的个数，flag记录，tot见上

bool find(int x)               //查找函数，x为每组数据字符串的编号
{
	int u=0;                  //从根节点找
	int len=strlen(s[x]);     
	for(int i=0;i<len-1;i++)    //必须为len-1，因为每个字符串最后的b都为1
	{
		int c=s[x][i]-'0';    
		u=ch[u][c];           //记录孩子
		if(b[u]) return true;   //判断
	}
	return false;
}

int main()
{
	while(scanf("%s",s[t])!=EOF)    
	{
		if(s[t][0]=='9')
		{
			p++;          //记录第几组
			if(flag)       //有前缀才是is not，不是才是is
			{
				cout<<"Set "<<p<<" "<<"is not immediately decodable"<<endl;
			}
			else
			{
				cout<<"Set "<<p<<" "<<"is immediately decodable"<<endl;
			}
			memset(b,0,sizeof(b));
			memset(ch,0,sizeof(ch));
			tot=0;
			flag=0;
			t=0;            //以上清空
			continue;      //字符9不做操作
		}
		int u=0;           //从根节点开始
		int len=strlen(s[t]);
		for(int i=0;i<len;i++)
		{
			int c=s[t][i]-'0';
			if(!ch[u][c]) ch[u][c]=++tot;   //新建边和孩子节点
			u=ch[u][c];                       
		}
		b[u]=1;                    //字符结尾标记
		for(int i=0;i<=t;i++)     
		{
			if(find(i))
			{
				flag=1;
				break;
			}
		}
		t++;         记录第几个字符串
	}
	return 0;
}
```
[双倍经验 UVAPhone List](https://www.luogu.com.cn/problem/UVA11362)

---

## 作者：CeLaMbDa (赞：1)

对于每一个子数据, 读入一个插入一个, 如果读入的是$9$, 输出答案$\&$清空  
而对于答案的统计也并不是那么的麻烦, 设置一个结尾标签$end$, 那么有两种情况
- 插入最后一个字符的时候没有新建节点, 那么答案为真
- 如果发现下一个字符处有结尾标签, 那么答案为真  

对于读入$\&$输出请看代码
```cpp
#include<stdio.h>
#include<memory.h>
#define N 1005

int t[N][2], end[N], cnt, ans;
inline void clean() { // 清空
	cnt = 0, ans = false;
	memset(t, 0, sizeof t);
	memset(end, 0, sizeof end);
}

inline void insert(char* s) {
	int cur = 0;
	for(int i = 0;s[i];cur = t[cur][s[i] - '0'], i++) {
		if(!t[cur][s[i] - '0']) t[cur][s[i] - '0'] = ++cnt;
		else if(!s[i + 1]) ans = true; //情况1
		if(end[t[cur][s[i] - '0']]) ans = true; //情况2
	}
	end[cur] = true; //结尾标签
}


int main(int argc, char** args) {
	int p = 1;
	char s[1005] = {'\0'};
	while(~scanf("%s", s)) {
		if(s[0] == '9') {
			if(ans) printf("Set %d is not immediately decodable\n", p++);
			else printf("Set %d is immediately decodable\n", p++);
			clean();
			continue;
		}
		insert(s);
	}
}
```


---

## 作者：Social_Zhao (赞：1)

思路：$Trie$树

我们可以在插入的时候顺便判断一下是否为前缀，~~增大常数的同时~~减少期望时间复杂度

如何解决$UVA$的坑输入：我们首先把每个 9 之前的串读进一个数组里，遇到 9 在把他们一起处理掉。

如何判断前缀：

如果这个串 $s_1$ 都插入完了，还没有增加新节点，则必然有一 $s_2$ 的前缀就是 $s_1$ ，这个 $s_2$ 就是沿着当前路径一直走下去。

如果 $s_1$ 在插入的过程中遇到了 $s_2$ 的末尾节点，则 $s_2$ 必为 $s_1$ 的前缀。

代码实现如下

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int MaxN=1e3+5;
const int MaxS=150;

int n,tot;
int ch[MaxN][MaxS];
bool e[MaxN];
char s[55][150];

inline void init()
{
	memset(ch,0,sizeof(ch));
	memset(e,0,sizeof(e));
	memset(s,0,sizeof(s));
}

inline bool insert(char *s) //魔改Trie版子
{
	int len=strlen(s);
	int u=1;
	bool flag=0; //判断有没有前缀
	for(register int i=0;i<len;i++) {
		int c=s[i]-'0';
		if(!ch[u][c]) ch[u][c]=++tot;
		else if(i==len-1) flag=1; //如果没有增加节点，且本串已插完，本串即为某一串的前缀
		u=ch[u][c];
		if(e[u]) flag=1; //走到了末尾节点，则该串是本串的前缀
	}
	e[u]=1;
	return flag;
}

inline void solve(int n,int t)
{
	tot=1;
	bool ans=0;
	for(register int i=1;i<=n;i++) {
		if(insert(s[i])) ans=1; //插入时发现了前缀
	}
	if(!ans) printf("Set %d is immediately decodable\n",t); //输出答案
	else printf("Set %d is not immediately decodable\n",t); //输出答案
}

int main()
{
	int T=0;
	int n=1;
	while(scanf("%s",s[n])!=EOF) { //还能读
		if(s[n][0]=='9') { //如果是9，这个子任务结束了
			T++; //数据组数++
			solve(n,T); //求第T组（共n个串）数据的答案
			n=0; //n清零
			init(); //初始化数组
		}
		n++; 
	}
	return 0;
 } 
```

---

## 作者：唔啊唔 (赞：1)

这是一道典型的trie树，思想上与代码实现上都没有太大的难度，因此就直接上代码了。
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[1000];
int node[1000][30],c=1,cnt[1000],f=0,care=1;
inline void tree(){
	int u=1,len=strlen(a);
	for(register int i=0;i<len;i++){
		if(node[u][a[i]-'0']==0){
			c++;
			node[u][a[i]-'0']=c;
			u=c;
		}
		else u=node[u][a[i]-'0'];
	}
	cnt[u]=1;
	return;
}
inline void trie(){
	int u=1,len=strlen(a);
	for(register int i=0;i<len;i++){
		if(node[u][a[i]-'0']==0){
			if(cnt[u]==1)f=1;
			return;
		}
		else{
			u=node[u][a[i]-'0'];
		}
	}
	f=1;
	return;
}
int main(){
	while(cin>>a){
		if(a[0]=='9'){
			if(f==0){
				cout<<"Set "<<care<<" is immediately decodable"<<endl;
			}
			else cout<<"Set "<<care<<" is not immediately decodable"<<endl;
			care++;
			f=0;
			memset(node,0,sizeof(node));
			memset(cnt,0,sizeof(cnt));
			c=1;
			continue;
		}
		else{
			trie();
			tree();
		}
	}	
}
```
做完后推荐蒟蒻们做一下[这道水题](https://www.luogu.org/problemnew/show/P2580)!

谢谢观看！

---

## 作者：hyfhaha (赞：1)

# 双倍经验（UVA11362 Phone List）
## Immediate Decodability
题目：[Immediate Decodability](https://www.luogu.org/problemnew/show/UVA644)

这道题和上面[这道题](https://www.luogu.org/problemnew/show/UVA11362)一模一样，不过输入比较恶心，而且数据范围也比较小，n很小，数组不用开很大，这里要注意。

[上面那道题的题解](https://www.luogu.org/blog/juruohyfhaha/solution-uva11362)，具体思路看这里。

这里的输入就是不断输入字符串S，然后将字符串S插入到Trie中，直到S='9'为止。

到了S='9'，就将之前的S都像上面的一样查询一边，输出答案，然后清0。

还是输入比较恶心，其他就没什么了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct kkk{
    int son[11],sum;
    bool flag;
    void clear(){memset(son,0,sizeof(son));sum=0;flag=0;}
}trie[2001];
int n,T,num,t;
string S[400001];
void insert(string s){
    int len=s.size(),u=0;
    for(int i=0;i<len;i++){
        int v=s[i]-'0';
        if(!trie[u].son[v])
        trie[u].son[v]=++num;
        trie[u].sum++;
        u=trie[u].son[v];
    }
    trie[u].flag=true;
}
int find(string s){
    int len=s.size(),u=0;
    for(int i=0;i<len;i++){
        int v=s[i]-'0';
        if(!trie[u].son[v])return 0;
        u=trie[u].son[v];
    }
    if(trie[u].sum==0)return 0;
    return 1;
}
void solve(){               //解决之前的字符串
    bool ans=false;
    for(int i=1;i<=n;i++){
        int res=find(S[i]);
        if(res==1){ans=true;break;}
    }
    if(ans==true)printf("Set %d is not immediately decodable\n",t);
    else printf("Set %d is immediately decodable\n",t);
}
int main(){n=1;
    while(cin>>S[n]){
        if(S[n]=="9"){
            t++;
            solve();            //解决之前的问题
            memset(trie,0,sizeof(trie));    //清0
            num=0;n=1;continue; //清0
        }
        insert(S[n]);n++;       //如果不是‘9’就插入
    }
}
```

---

## 作者：桃夭 (赞：1)

### 这道题目一眼就能看出是Trie树的模板题啊
### ~~但我就是不用Trie树做~~
**首先我们要先掌握C++中三个与字符串有关的函数**
1. **strstr(s1,s2);这个函数的意思是：判断字符串str2是否为str1的子串，如果是，则该函数返回str2在str1中首次出现的地址；否则，返回NULL。[这里说的比较详细](https://blog.csdn.net/yunzhongguwu005/article/details/9184351)**
1. **strcmp(s1,s2);这个函数的意思是：比较参数1和参数，若参数1>参数2，返回正数；若参数1<参数2，返回负数；若参数1=参数2，返回0。[同样附上一个详细解释](https://blog.csdn.net/wangrenbao123/article/details/54963047/)**
1. **strcpy(s1,s2);这个函数的意思是：把从str地址开始且含有NULL结束符的字符串复制到以buffer开始的地址空间，buffer地址空间中必须有足够的空间来容纳str的字符串。[不理解的点这里qwq](https://blog.csdn.net/wangrenbao123/article/details/54965179)**

**（划重点）然后就可以开始这一题了，很容易看出，先判断两字符串是否存在子串，注意如果两串相等也算是子串，所以要再判断其是否相等，就可以了，那么利用上述三个函数，这道题就很容易解出来了。~~（根本不要用Trie树嘛qwq）~~**

# 附上代码
```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
char s[110][110];
char ss[110];
int t=1,b,len=0;
int read()
{
    char chr;
    int f=1;
    while (((chr=getchar())<'0')||(chr>'9'))
    {
        if (chr=='-')
        {
            f=-1;
        }
    }
    int res=chr-'0';
    while (((chr=getchar())>='0')&&(chr<='9'))
    {
        res=res*10+chr-'0';
    }
    return res*f;
}
int main()
{
	while (cin>>ss)
	{
		b=0;
		if (ss[0]=='9')
		{
			for (int i=0;i<len;++i)
			{
				for (int j=0;j<len;++j)
				{
					if (i!=j)
					{
						if ((strstr(s[j],s[i])!=NULL)&&(strcmp(strstr(s[j],s[i]),s[j])==0))//判断两字符串是否为子串
						{
							b=1;
							break;
						}
						if (strcmp(s[i],s[j])==0)//比较字符串是否相等
						{
							b=1;
							break;
						}
					}
				}
			}
			if (b)
			{
				cout<<"Set "<<t<<" is not immediately decodable\n";
				t++;
			}
			else
			{
				cout<<"Set "<<t<<" is immediately decodable\n";
				t++;
			}
			len=0;
		}
		else
		{
			strcpy(s[len],ss);
			len++;
		}
	}
	return 0;
}
```

---

## 作者：船医 (赞：1)

## 这道题选择用DFS做一个深搜。
思路很简单，无非就是输入恶心，我们只需要用while输入，遇9停止就行。
（[双倍经验](https://www.luogu.com.cn/problem/UVA11362)）

~~（能水的经验蒟蒻绝对不会放弃！）~~
改输入就可ac~~

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105;//好看
char s[N];
int ch[N][2];
bool b[N];
int tot,n,ccase,x;//ccase用来存组数
void find(int k) {
	if(ch[k][1]!=0) {
		if(b[k]==1) {
			x=1;
			return;
		}
		find(ch[k][1]);
	}
	if(ch[k][0]!=0) {
		if(b[k]==1) {
			x=1;
			return;
		}
		find(ch[k][0]);
	}
}//递归深搜。为什么不叫dfs？我乐意。
int main() {
	while(cin>>s) {
		memset(ch,0,sizeof(ch));
		memset(b,0,sizeof(b));
		tot=0;
		while(s[0]!='9') {
			n=strlen(s);
			int u=0;
			for(int i=0; i<n; i++) {
				if(ch[u][s[i]-'0']==0)ch[u][s[i]-'0']=++tot;
				u=ch[u][s[i]-'0'];
			}
			b[u]=1;
			cin>>s;
		}
		x=0;
		find(0);
		if(x==1)
			cout<<"Set "<<++ccase<<" is not immediately decodable"<<endl;//++ccase，数据组数++
		else
			cout<<"Set "<<++ccase<<" is immediately decodable"<<endl;//同上
	}
	return 0;//好习惯
}//AC！！！！！！！！！！
```
就这样。
大家加油

---

## 作者：Celtic (赞：0)

题意：判断数字串编码是否合法。合法的编码不允许出现一个编码是另一个编码的前缀。 


$Trie$树模板题。

注意输出格式和输入格式。

不会$Trie$树的同学[点击这里](https://www.luogu.com.cn/blog/176990/solution-uva11362)

代码

```cpp
#include<bits/stdc++.h>
#define eps 1e-7
#define re register
#define N 1005
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
	re ll cnt=0;
	while(scanf("%s",s+1)!=EOF)
	{
		tot=0;
		ans=0;
		memset(trie,0,sizeof(trie));
		memset(b,0,sizeof(b));
		insert();
		while(true)
		{
			scanf("%s",s+1);
			if(strlen(s+1)==1&&s[1]=='9')
				break;
			insert();
		}
		if(ans)
			printf("Set %lld is not immediately decodable\n",++cnt);
		else
			printf("Set %lld is immediately decodable\n",++cnt);
	}
	exit(0);
}
```


---

## 作者：香风智乃 (赞：0)

**Trie**

Trie模板题（评成蓝题真的不误导新手吗）

难度几乎相等的题 [P2580 于是他错误的点名开始了](https://www.luogu.org/problemnew/show/P2580)（黄题*1）

Trie是以每个字母为节点的一棵树，也就是字典树。这里不详细介绍（右转baidu）

对于每组数据都清空树太浪费时间，所以我们只要在需要新点时**预先把新点原有的数据清空**即可。

剩下除了一些细节要注意，没啥要说的了
###### [juruo's blog](https://www.cnblogs.com/kafuuchino/p/9612477.html)
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
struct data{
    int nxt[2]; bool end;
    void clear() {nxt[0]=nxt[1]=0; end=0;}
}a[5000001]; //对于每个节点，存储它的下一个字母，以及是否是某个字母的结束符
char q[2000001];
int cnt; //节点编号
bool ok;
inline void insert(){ 
    int u=0,len=strlen(q); bool ins=0;  //ins:是否插入新节点
    for(int i=0;i<len;++i){
        int p=q[i]-'0';
        if(!a[u].nxt[p]){ //如果之前没有这个节点就插入
            a[++cnt].clear();
            a[u].nxt[p]=cnt; ins=1;
        }
        if(a[u].end) ok=1; //如果某个在它之前插入的单词是它的前缀
        u=a[u].nxt[p]; //跳转到下一个
    }
    if(!ins) ok=1; //如果它是某个在它之前插入的单词的前缀
    a[u].end=1;
}
int main(){
    int t=0;
    while(cin>>q){
        if(q[0]=='9') { //一组数据的结束
            printf("Set %d is ",++t);
            if(ok) printf("not ");
            printf("immediately decodable\n");
            cnt=0; ok=0; a[0].clear(); //注意树根0也要清空
        }else insert();
    }
    return 0;
}
```

---

## 作者：珈乐唯毒 (赞：0)

## 本题字典树模版

字典树是一种用于前缀检索的特殊树形结构，也被称为前缀树或trie

字典树基于若干”单词”(字符串)创建，树中所有边都代表一个字符，从根节点到其他节点的路径对应一个字符串。

如图是一个由{ abcd,abc,abd,b,bcd,efg,hij }创建的字典树，可以发现，字典树中的节点分为两类，红色的点代表存在对应单词，白色代表不存在对应单词，根到它的路径只是某个单词的前缀。

![](https://cdn.luogu.com.cn/upload/image_hosting/c8rmmr9r.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

建完树后，每一次查找采用深搜的形式，如果在叶子节点钱搜到了红点，代表存在前缀

AC代码如下
```
#include<bits/stdc++.h>
using namespace std;
string s;
int ch[15][2];
bool b[15];
int tot,n,l,x;
void dfs(int k){
	if(ch[k][1]!=0){
		if(b[k]==1){
			x=1;
			return;
		}
		dfs(ch[k][1]);
	}
	if(ch[k][0]!=0){
		if(b[k]==1){
			x=1;
			return;
		}
		dfs(ch[k][0]);
	}
}
int main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
	while(cin>>s){
		memset(ch,0,sizeof(ch));
		memset(b,0,sizeof(b));
		tot=0;
		while(s[0]!='9'){
			n=s.size();
			int u=0;
			for(int i=0;i<n;i++){
				if(ch[u][s[i]-'0']==0)ch[u][s[i]-'0']=++tot;
				u=ch[u][s[i]-'0'];
			}
			b[u]=1;
			cin>>s;
		}
		x=0;
		dfs(0);
		if(x==1)printf("Set %d is not immediately decodable\n",++l);
		else printf("Set %d is immediately decodable\n",++l);
	}
	return 0;
} 
```


---

