# [USACO2.3] 最长前缀 Longest Prefix

## 题目描述

在生物学中，一些生物的结构是用包含其要素的大写字母序列来表示的。生物学家对于把长的序列分解成较短的序列（即元素）很感兴趣。

如果一个集合 $P$ 中的元素可以串起来（元素可以重复使用）组成一个序列 $s$ ，那么我们认为序列 $s$ 可以分解为 $P$ 中的元素。元素不一定要全部出现（如下例中 `BBC` 就没有出现）。举个例子，序列 `ABABACABAAB` 可以分解为下面集合中的元素：`{A,AB,BA,CA,BBC}`

序列 $s$ 的前面 $k$ 个字符称作 $s$ 中长度为 $k$ 的前缀。设计一个程序，输入一个元素集合以及一个大写字母序列  ，设 $s'$ 是序列 $s$ 的最长前缀，使其可以分解为给出的集合 $P$ 中的元素，求 $s'$ 的长度 $k$。


## 说明/提示

**【数据范围】**

对于 $100\%$ 的数据，$1\le \text{card}(P) \le 200$，$1\le |S| \le 2\times 10^5$，$P$ 中的元素长度均不超过 $10$。

翻译来自NOCOW

USACO 2.3


## 样例 #1

### 输入

```
A AB BA CA BBC
.
ABABACABAABC
```

### 输出

```
11
```

# 题解

## 作者：hhjtutuhe (赞：112)

### 这是一道DP的题目
#### 分析

在样例中，S能够组成的P中的元素的最长前缀为11个字符，即为A+BA+BA+CA+BA+AB.用f[i]表示前i个字符是否可以分解为集合中的字符，如钩可以就为真，不可以就为假。则很容易看出：f[i]的充要（充分必要）条件是：存在一个比i小的j，满足f[i]=true且从第j+1到第i是p中的一个元素。

伪代码如下所示：
```cpp
if(f[j]=true && s[j+1...i]为集合P中的一个字符串（j从i~1 到 1~10 枚举）
  f[i]=true
else f[i]=false; 
```

参考代码如下所示：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
string P[201],S=" ";
bool f[200001]= {1};
bool Check(int p)
{
  for(int i=0;i<n;i++)
  {
  	int t=P[i].size();
  	if(p>=t && f[p-t] && P[i]==S.substr(p-t+1,t))
  	{
      ans=p;
      return true;
	}
  }
  return false;
}
int main()
{
  for(string s;cin>>s,s!=".";P[n++]=s);
  for(srting s;cin>>s;S+=s);
  for(int i=1;i<=S.size();i++)
    f[i]=Check(i);
  printf("%d\n",ans);
  return 0;
}
```
上面的参考代码中可以优化的算法是判断某段字符串是否是集合中某元素时，如果逐一与集合中的元素比较，有可能超时。。。。。。

有能力的巨佬可以尝试使用二分法或者STL中的set容器优化代码。写那么多不容易，点个赞再走呗TWT

---

## 作者：momo5440 (赞：85)

正如前辈们所说的，这是道dp题，dp的是状态，如果当前的字符串从后往前截了有一段集合中的串且截去这段串后的字串是合法的话那么当前串也是合法的，之前的大佬已说过了，所以我再次介绍一种优化方法（经过我的老师提醒），那就是用STL中的set(集合~~感觉题目中已经提示了~~），我们没有必要把子串与所有集合里的串作比较，只有比较跟他长度相等的就行了,set里面是一棵平衡树只需logn的时间就可以找到要求的东西
说了这么多，上代码，代码里也有注释。
```cpp
#include <iostream>
#include <set>
#include <cstring>
using namespace std;
int dp[200005],m;
set<string> s[20];
int main(){
	string tp;
	while (cin>>tp){
		if (tp==".") break;
		s[tp.size()].insert(tp);//存到他大小的集合中 
		m=max(m,int(tp.size()));
	}
	int i,ans=0;
	dp[0]=1;//初始化 
	string n;
	n=" ";
	while (cin>>tp){
		n=n+tp;//将所有的串合成一个 
	}
	for (i=1;i<n.size();i++){//枚举子串 
		for (int j=min(i,m);j>=1;j--){
			string tt=n.substr(i-j+1,j);//截除子串 
			if (s[tt.size()].count(tt)==1&&dp[i-j]==1){//如果合法 
				ans=i;//必定是最大的 
				dp[i]=1;//本身也合法 
				break;//没必要搜下去了 
			}
		}
	}
	cout<<ans;
}
```

---

## 作者：风羽跃 (赞：44)

我提供一种好想的思路：KMP + dp

### 1.用KMP标记每个元素在s串中出现的位置。

如果不了解KMP 【一种在一个字符串（称为目标串）中查找另一个字符串（称为模式串）的 O(n) 算法】的，可以去看 P3375。

这里有一点，我们标记的是每个元素在s的每个位置上是否出现。

### 2.用dp判断每个前缀是否合法

f [ i ] 表示 s 串中前 i 个字符构成的前缀是否合法。
通过枚举每个元素（相当于决策了），确定 f [ i ] 。

不难得出状态转移方程：

f [ i ] = f [ i ] | |  f [ i - m [ j ] ]

其中j是枚举的元素下标，m数组记录每个元素的长度。

边界条件 f [ 0 ] = true ;

### 3.找到合法的最长前缀，输出

AC代码：

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>

#define maxm 11
#define maxc 202
//这里要多开一位，因为后面"."也被读入了 
#define maxn 200001

using namespace std;

int c,n,m[maxc],pre[maxc][maxm];
//pre为最长公共真前缀后缀长度 
bool pl[maxc][maxn];
//pl[i][j]=true表示第i个字符串末尾位置在j出现过 
string s,p[maxc];

bool f[maxn];

inline void get_pre(int c,string p)
//求最长公共真前缀后缀 
{
	int j=0;
	pre[c][1]=0;
	for(int i=1;i<m[c];i++){
		while(j>0&&p[i+1]!=p[j+1]) j=pre[c][j];
		if(p[i+1]==p[j+1]) j++;
		pre[c][i+1]=j;
	}
}

inline void KMP(string s,int c,string p)
{
	int j=0;
	for(int i=0;i<n;i++){
		while(j>0&&s[i+1]!=p[j+1]) j=pre[c][j];
		if(s[i+1]==p[j+1]) j++;
		if(j==m[c]){
			pl[c][i+1]=true;//记录位置 
			j=pre[c][j];
		}
	}
}

int main()
{
	while(cin>>p[++c]&&p[c]!="."){
		m[c]=p[c].length();
		p[c]='#'+p[c];//为了使字符串从1开始 
	}
	c--;//"."不算 
	string x;
	while(cin>>x) s+=x;//注意可能不止一行 
	n=s.length();
	s='#'+s;
	for(int i=1;i<=c;i++){
		get_pre(i,p[i]);
		KMP(s,i,p[i]);
	}
	f[0]=true;//给个true要不然会爆 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=c;j++){
			if(pl[j][i]) f[i]=f[i]||f[i-m[j]];
		}
	}
	for(int i=n;i>=0;i--){
		if(f[i]){
			cout<<i<<endl;
			return 0;
		}
	}
	return 0;
}
```


---

## 作者：saxiy (赞：15)

为什么不用 $AC\text{自动机}$ 呢？

~~其实后面有dalao讲AC自动机，但不是很详细。~~

我来胡扯一下。。

#### 题目分析：

简意是求在字符串$S$中，最长能被匹配的前缀长度，多模式串匹配，不就是AC自动机的板子嘛。。

同样要设状态 $ok[i]$ 表示前$i$位能否被匹配，容易得出转移方程：

$$ok[i]=\sum_{P_j\text{匹配}S_{[i-len(P_j)+1,i]}}ok[i-len(p_j)]$$

上式的$\sum$表示 **逻辑或** 运算。

边界条件是 $ok[0]=true$ ，即匹配前0位是一定可以的。

- 在匹配的过程我们使用AC自动机，节点的结束标记可以直接存模式串长度，整个数组就干净了许多，匹配时就暴力跳$fail$边，匹配到串就根据长度转移状态。

#### 代码实现(21ms in total)：

```cpp
#include <bits/stdc++.h>
#define N 2010
#define M 200005
using namespace std;

char str[M], msc[N];
int trie[N][26], ed[N], p[N], cnt = 2;
bool ok[M];

void insert(const char* str) {
	int now = 1, len = strlen(str);
	for(int i = 0;i < len;i++) {
		int ch = str[i] - 'A';
		if(!trie[now][ch]) trie[now][ch] = cnt++;
		now = trie[now][ch];
	}
	ed[now] = len;//结束标记 记长度。
}

void pre() {//AC自动机基本操作所以没注释
	for(int ch = 0;ch < 26;ch++)
		trie[0][ch] = 1;
	queue <int> q;
	q.push(1);
	while(q.size()) {
		int now = q.front(); q.pop();
		for(int ch = 0;ch < 26;ch++) {
			if(trie[now][ch]) {
				q.push(trie[now][ch]);
				p[trie[now][ch]] = trie[p[now]][ch];
			} else trie[now][ch] = trie[p[now]][ch];
		}
	}
}

void AC_run(const char* str) {
	*ok = 1;//边界条件
	int now = 1, len = strlen(str + 1);
	for(int i = 1;i <= len;i++) {
		now = trie[now][str[i] - 'A'];
		for(int j = now;j && !ok[i];j = p[j])//暴力跳fail
			if(ed[j]) ok[i] |= ok[i - ed[j]];
			//ok[i]为真就可以break。
	}
	for(int i = len;~i;i--)//找最大匹配位
		if(ok[i]) { printf("%d", i); return; }
}

int main() {
	while(1) {
		scanf("%s", msc);
		if(*msc == '.') break;
		insert(msc);
	}
	pre();
	char *p = str + 1, c;
	//从下标1开始读方便搞边界
	while((c = getchar()) != EOF)
		if('A' <= c && c <= 'Z') *p++ = c;
	*p = '\0';//读入的换行特判^^^^^^^^^^^
	AC_run(str);
	return 0;
}
```

#### 后记：

这是一道AC自动机板子题。

---

## 作者：a13518354766 (赞：12)

			首先看题，题目要求我们求最长匹配的长度，我们不妨如下思考：

​	对于字符串S，我们从第y位开始搜索（**保证前y-1位一定可以是匹配**）

​	从第y位开始生成字符串，若此时生成的字符串在P中出现过，则证明

​	此时的字符串可以被匹配到y+i的位置，我们再从y+i+1开始搜索便好了！

​	**而问题的答案就是我们已到达的最大的一个y。**

			那么问题来了，如果按照上述说法搜索，复杂度不稳定，但一定会

​	**超时**的，有木有什么优化呢？

			答案是有的（不然我写这个题解干什么呢?），我们注意到，如果

​	对于此时的y，我们曾经到达过，虽然到达的方式不同，但我们到达过，**后**

​	**面我们进行搜索的过程与结果肯定是一样的**，所以，我们就**跳过**就好啦！

​	而总的复杂度最高位O(n)(n为S串的长度)，一下便是完整代码（加了点小优

​	化):

    #include<bits/stdc++.h>
    using namespace std;
    map<string,bool>s;//一个map解千愁~就是<u>**速度慢了点**</u>，大佬请自行打**hash**
    int x;
    int ans=0;
    int ams=0;
    string l;
    bool F=0;
    bool come[200001];
    inline void to_search(int now){	
        if(come[now]){//如果曾经搜索过此时的‘y’
            return;//退出
        }
        come[now]=1;//标记搜索过此时的‘y’
        if(now==x){
            return;
        }
        string qu="";
        for(int i=now;i<x;++i){
            if(i-now>=ams){//如果现在加的元素大于了最长元素，之后一定不可能成立，于是跳过（虽然是小优化，也很强大有不有~）
                return;
            }
            qu+=l[i];
            if(s[qu]){//如果P集合中有此时的元素
                F=1;//判断成立
                if(i>ans){//记录答案
                    ans=i;
                }
                to_search(i+1);//从下一个y开始搜索
            }
        }
    }
    int main(){
        int e=1;
        while(cin>>l){
            if(l=="."){
                break;
            }
            s[l]=1;//标记元素存在
            if(l.size()>ams){
                ams=l.size();//记录最长元素（小优化第一步）
            } 
        }
        string yu="";
        while(cin>>l){//输入字符串S
            yu+=l;//将字符串S整合
        }
        l=yu;
        x=l.size();//得到S的长度
        to_search(0);//从第一个字符开始搜索
        if(!F){//注意判断是否搜索过，第一个点的坑QWQ
            printf("0");
            return 0;
        }
        printf("%d",ans+1);//输出答案（记得加一，因为是从0开始搜的）
        return 0;
    }


---

## 作者：XZYQvQ (赞：11)

楼下luobobo大佬%%%%%

楼下进益求精以程序快为快乐。

而本蒟蒻只能以代码短为快乐了。

其实没必要用trie树，暴力匹配也是可以的。

用记忆化非递归式深搜就可以了。

记录状态$i$（即前$i$个字符都匹配成功）是否达到过，达到过则直接return。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,subl[205],strl;
bool book[200005];
char sub[205][15],str[200005];
void dfs(int k)
{
    if(book[k])return;book[k]=1;
    for(int i=1,f=0;i<=n;i++,f=0)
    {
        for(int j=0;j<subl[i];j++)if(sub[i][j]!=str[k+j]||k+j>=strl){f=1;break;}
        if(!f)dfs(k+subl[i]);
    }
}
int main()
{
    while(scanf("%s",sub[++n]),strcmp(sub[n],".")!=0)subl[n]=strlen(sub[n]);
    do{str[strl]=getchar();if(isupper(str[strl]))strl++;}while(str[strl]!=EOF);
    dfs(0);
    for(int i=strl;i>=0;i--)if(book[i]){printf("%d\n",i);return 0;}
}
```

---

## 作者：「QQ红包」 (赞：10)

题解by：redbag

题解地址：http://redbag.duapp.com/?p=1343

方法同楼下。感觉这是一种最不需要智力的方法？NOCOW上的都看不太懂，被读入坑了很久。

元素似乎不止200个，开大点会好些？

```cpp
/*
ID: ylx14274
PROG: prefix
LANG: C++     
*/
#include<set>  
#include<map>  
#include<list>  
#include<queue>  
#include<stack>  
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>    
#include<string.h>  
#include<algorithm> 
#define LL unsigned long long   
using namespace std;
string s,ss,c[251];
int n,i,j,m;//n:元素个数
int a[251];//元素长度 
int f[200000];
int main() 
{
    freopen("prefix.in","r",stdin);
    freopen("prefix.out","w",stdout); 
    while (true)
    {
        m++;//计数器+1 
        cin>>c[m];//读入 
        if (c[m].size()-1]=='.')//结束 
        {
            m--;//计数器多算了
            break; //退出 
        }
        a[m]=c[m].size(); //记位数 
    }
    while (cin>>ss)//读入 
    {
        s+=ss; //连起来 
    }
    n=s.size();//存s的长度 
    s=' '+s;//每一位都往后挪一位，方便操作 
    f[0]=1;//初始值 
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++)
        if (i-a[j]>=0)//因为f数组没有负数下标，所以判断 
        {
            if (f[i-a[j]]==1)//i-a[j]位能由该集合的元素组成
            if (s.substr(i+1-a[j],a[j])==c[j]) 
            //i+1-a[j]~i位由c[j]组成 
            f[i]=1;//标记 
        } 
    for (i=n;i>=0;i--)
    if (f[i]==1)
    {
        printf("%d\n",i); //输出最大的 
         return 0;
    }
}
```

---

## 作者：yagyagyag (赞：8)

练KMP来的

有许多大佬用DP，我觉得这是一道暴力+KMP吧。有几位童鞋也是用KMP，但好像不是那么容易懂（对初学者来说，~~比如我~~）

所以我在这里最简单的KMP模板来写

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
string A,B[205],T;
int p[1005],n,m[205],ans=0;
bool visit[MAXN];//visit表示当前位置是否被覆盖 
void pre(int x)//板子 
{
	int j=0;
	p[1]=0;
	for (int i=1;i<m[x];i++){
		while (j>0 && B[x][j+1]!=B[x][i+1]) j=p[j];
		if (B[x][j+1]==B[x][i+1]) j++;
		p[i+1]=j;
	}
	return;
}
int kmp(int x)//板子 
{
	int j=0,ans=0;
	for (int i=0;i<n;i++){
		while (j>0 && B[x][j+1]!=A[i+1]) j=p[j];
		if (B[x][j+1]==A[i+1]) j++;
		if (j==m[x]){
			for (int k=i+1-m[x]+1;k<=i+1;k++)//当发现找到时，在首字母的位置到结束，visit[]标记为1 
				visit[k]=1;
			j=0;//这里要注意：因为单词不能重叠覆盖，所以不能是j=p[j] 
		}
	}
	return ans;
}
void check()
{
	for (int i=1;i<=n;i++)
		if (visit[i]) ans++;//只要当前被覆盖，长度就+1 
		else break;
	return; 
}
int main()
{
	int len=1;//输入就不说了 
	while (1){
		cin>>B[len];
		B[len]='&'+B[len];//同第54行 
		m[len]=B[len].size()-1;
		if (B[len]=="&."){
			len--;
			break;
		}
		len++;
	}
	while (cin>>T){//因为是多好，可以每次读入然后加起来 
		A+=T;
	}
	A='&'+A;//在最前面加一个锤子，就是从下标为1开始 
	n=A.size()-1;
	for (int i=1;i<=len;i++)//每个card跑一遍P数组的预处理 
		pre(i);
	memset(visit,0,sizeof visit);
	for (int i=1;i<=len;i++)//每个单词去配对一遍，能覆盖的都覆盖 
		kmp(i);
	check();//统计 
	cout<<ans<<endl;//拜拜 
	return 0;
 } 
```


---

## 作者：pmt2018 (赞：8)

~~显然~~，这道题可以用字符串hash做

我们对每一个字符串得到一个hash值。

然后就可以O(1)的时间内判断两段字符是否相同，以此来优化dp。

code：

``` cpp
#include<bits/stdc++.h>
#define mp make_pair
#define pb push_back
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int > vi;
typedef pair<int ,int > pii;
typedef vector<pii> vii;
const int inf=0x3f3f3f3f, maxn=100007, mod=1e9+7;
const ll linf=0x3f3f3f3f3f3f3f3fLL;

ull h[207][18],z[200007];
ull hs[200007];
string s;
int l[207];
string ss="";

const int P=137;//这个是字符串hash的乘数,我用的unsigned long long 自然溢出，所以没有模数 

int cnt;
void initZ(){
	z[0]=1;
	for(int i=1;i<=200000;i++)z[i]=z[i-1]*P;//预处理出P的乘方 
}
void initHash(ull rt[],string s){//预处理出一个string的hash值 
	int len=s.length();
	rt[0]=0;
	for(int i=1;i<=len;i++)rt[i]=rt[i-1]*P+s[i-1],cout<<rt[i]<<endl;
}
ull hash(ull rt[],int l,int r){//判断两段string是否相同 
	return rt[r]-rt[l-1]*z[r-l+1];
}
bool dp[200007];
int main(){
	initZ();
	while(cin>>s){
		if(s[0]=='.')break;
		initHash(h[++cnt],s);
		l[cnt]=s.length();
	}
	while(cin>>s)ss=ss+s;//读入ss，注意读入可能有多行，不要忘记换行 
	initHash(hs,ss);
	for(int i=1;i<=ss.length();i++){
		cout<<hs[i]<<endl;
	} 
	for(int i=0;i<ss.length();i++){//dp转移,这个有很多人讲过了我就不重复一遍了 
		if(i==0||dp[i-1]){//如果前i-1位可以转移 
			for(int j=1;j<=cnt;j++){
				if(l[j]+i>ss.length())continue;
				if(hash(hs,i+1,i+l[j])==hash(h[j],1,l[j])){//判断从第i位开始的文本串和第j个字符串是否相同 
					dp[i+l[j]-1]=true;//那么s[0~i+l[j]-1]也是它的一个前缀 
				}
			}
		}
	}
	for(int i=ss.length()-1;i>=0;i--){
		if(dp[i]){
			cout<<i+1<<endl;//我从零开始 ，要加1； 
			return 0;
		}
	}
	cout<<0<<endl;//若没有前缀 则输出0 
	return 0;
}
```




---

## 作者：Rocket_Ruaccoon (赞：8)

map大法好






```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<map>
using namespace std;
string S;
int L,F[200005];
map<string,bool> M;
void Init(){
    string s;
    while(cin>>s&&s!=".")
        M[s]=true;
    while(cin>>s)
        S+=s;
    L=S.length();
}
void DP(){
    int i=1,j;
    while(!M[S.substr(0,i)]&&i<=L)
        i++;
    if(i>L){
        printf("0\n");
        return;
    }
    F[i-1]=true;
    for(;i<L;i++)
        for(j=i-1;j>=max(0,i-10);j--)
            if(F[j]&&M[S.substr(j+1,i-j)]){
                F[i]=true;
                break;
            }
    for(i=L-1;i>=0;i--)
        if(F[i]){
            printf("%d\n",i+1);
            return;
        }
}
int main(){
    Init();
    DP();
    return 0;
}
```

---

## 作者：NoobYlh (赞：6)

（~~反正题解没人看 就提供个思路吧~~）

Trie+DFS 每搜到一个节点看它是不是一个单词的终点，是就加一个搜索路径，不是就按照Trie的Find()模板进行DFS.
优化：记得加vis数组进行记忆化搜索，不然会有重复情况会TLE。

上代码


------------

```cpp
#include <iostream>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<queue>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int maxn=5050;
const int INF = 0x3f3f3f3f;
int tree[maxn][30];
bool vis[2020][200020];
int ed[maxn];
char que[200020];
char ch[20];
int n,cnt,Len;
int ans=0;
int newnode(){
	for(int i=0;i<=26;i++){
		tree[cnt][i]=-1;
	}
	ed[cnt]=0;
	return cnt++;
}
void init(){
	cnt=0;
	newnode();
}
void insert(){
	int len=strlen(ch);
	int root=0;
	for(int i=0;i<len;i++){
		int x=ch[i]-'A';
		if(tree[root][x]<=0){
			tree[root][x]=newnode();
		}
		root=tree[root][x];
	}
	ed[root]=1;
}
void dfs(int pos,int len){
	if(vis[pos][len]) return;
	vis[pos][len]=1;
	int x=que[len]-'A';
	if(ed[pos]){
		ans=max(ans,len);
	}
	if(len==Len){
		return;
	}
	if(tree[pos][x]!=-1){
		dfs(tree[pos][x],len+1);
	}if(ed[pos]){
		dfs(0,len);
	}
}
int main(){
	init();
	while(scanf("%s",ch)&&strcmp(ch,".")){
		insert();
	}
	Len=0;
	while(scanf("%s",que+Len)!=EOF){
		Len=strlen(que);
	}
	dfs(0,0);
	printf("%d\n",ans);
}

 
```


---

## 作者：resftlmuttmotw (赞：6)

# 最易懂的题解

### 题目描述

[题目描述](https://www.luogu.org/problemnew/show/P1470)


------------


### 做题时的垂死挣扎
最先看到这道题，非常开心。哈哈一笑，~~暴力~~，然后~~快乐~~TLE

请大家以我为戒，做题前先看标签。

然后在看到DP后，我傻眼了。（我打的就是dp啊，怎么会错一个点）

我盯着电脑，看着题，想了50多分钟无关的事后。。。我终于开始了打代码


------------

### 思路

读入时需要注意一下字符串的技巧。

然后你就~~暴力循环~~dp

我最开始TLE一个点是因为，我顺便把连成长度为 K 的前缀的方法总数也顺便求了一下

### 具体方法

每向后移一个字母，就循环一下元素，看看当前元素是否与这序列 从当前位置向前遍

历所的串相等

```cpp
for(k = i;k > i - a[j].k[11];k--)
{
    it--;
    if(a2[k] != a[j].k[it])
	{
        able = 1;
    	break;
    }
}
```

且

```cpp 
dp[k - 元素.size()] == 1
```

才将
```cpp

dp[k] = 1;
```

最后再在一些地方适当优化就可以AC了

我的方法

------------
```cpp
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 200002
#define N 202
#define max(a,b) a >= b? a:b//手写max
using namespace std;
int ans,len1,i,j,len2 = 1;
char a2[M];
bool dp[M];
struct node
{
	char k[12];
}a[N];//主要是定义成结构体，看着好看一些，可以定成二维

int main()
{
    scanf("%s",a[len2].k);
    a[len2].k[11] = strlen(a[len2].k);//最大长度10,11存长度
    while(a[len2].k[0] != '.')//不能写成a[len2].k !=  "."
	{
        len2++;
        scanf("%s",a[len2].k);
        a[len2].k[11] = strlen(a[len2].k);
    }
    len2--;
    char x = getchar();//去掉'.'后的换行符
    
    while(~scanf("%c",&x))
        if(x <= 'Z'&&x >= 'A')
		{
            len1++;
            a2[len1] = x;
        }
    //至此，读入环节结束
    dp[0] = 1;
    for(i = 1;i <= len1;i++)
	{
        int k;
        for(j = 1;j <= len2;j++)
		{
            if(i < a[j].k[11]) continue;//i < 长度，肯定不行的啦
            bool able = 0;
            int it = a[j].k[11];//因为下面--
            for(k = i;k > i - a[j].k[11];k--)
			{
                it--;
                if(a2[k] != a[j].k[it])
				{
                    able = 1;
                    break;
                }
            }
            if(!able)
			{
                dp[i] += dp[i - a[j].k[11]];//就这里，顺便求了下连成长度为 K 的前缀的方法总数
                
                if(dp[i])
                {
                	ans = max(ans,i);
                	break;//必须加，不然会TLE一个点
				}
            }
        }
    }
    printf("%d",ans);
    return 0;
}

```

### 总结

时间复杂度能减则减

---

## 作者：Celebrate (赞：4)

这一道题用dp就可以解了，换行输入用while（!=EOF)就好了

然后从头到尾每一个位置DP一遍

代码如下：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cstdlib>
using namespace std;
struct node
{
	int len;
	char ss[21];
}a[210];int n,len;
char st[210000],s[110];
bool f[210000];
inline int cmp(const void *xx,const void *yy)//快排代码 
{
	node x=*(node*)xx;
	node y=*(node*)yy;
	if(x.len>y.len) return 1;
	if(x.len<y.len) return -1;
	return 0;
}
int main()
{
	int i,j,k,t;
	while(1)//输入单词 
	{
		n++;
		scanf("%s",a[n].ss+1);a[n].len=strlen(a[n].ss+1);
		if(a[n].len==1 && a[n].ss[1]=='.')//遇到“.”就退出 
		{
			n--;break;
		}
	}
	qsort(a+1,n,sizeof(node),cmp);//把单词的长度排一遍序 
	while(scanf("%s",s+1)!=EOF)//输入字符串 
	{
		for(i=1;i<=strlen(s+1);i++){len++;st[len]=s[i];}
	}
	memset(f,false,sizeof(f));f[0]=true;//f[i]表示第i位是否能到达，初始化0是可以到达的 
	for(i=1;i<=len;i++)//枚举长度 
	{
		for(j=1;j<=n;j++)//枚举单词 
		{
			if(i<a[j].len) break;//如果单词的长度超过了字符当前的长度，就退出 
			if(f[i-a[j].len]==false) continue;//如果前面的都不行，就不管这个单词 
			bool bk=true;t=a[j].len;//判断这个单词是否符合要求 
			for(k=i;k>=i-a[j].len+1;k--)
			{
				if(st[k]!=a[j].ss[t])//如果不匹配 
				{
					bk=false;break;
				}
				t--;
			}
			if(bk==true)//如果能成功的匹配了 
			{
				f[i]=true;break;
			}
		}
	}
	for(i=len;i>=0;i--) //找最长的前缀 
	{
		if(f[i]==true)
		{
			printf("%d\n",i);
			break;
		}
	}
	return 0;
}
```

---

## 作者：Rocket_raccoon_ (赞：4)

用f[i]表示前i个字符是否可以分解为集合中的字符，如果可以
则为真，不可以则为假，于是很容易看出：f[i]为真的重要条
件是：存在一个比i小的j，满足f[j]=true且从第j+1到底i是P
中的一个元素。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
string a[201],str;
bool f[200001];
int len=0,n=0;

bool IsChar(char c){//判断是否字符
    if(c>='A'&&c<='Z'){
        return true;
    }
    return false;
}

bool check(int p){//查找集合中匹配的串
    int t;
    for(int i=1;i<=n;i++){
        t=a[i].length();
        if(p>=t){
            if(a[i]==str.substr(p-t+1,t)){
                if(f[p-t]){
                    return true;
                }
            }
        }
    }
    return false;
}

int main(){
    string s;
    while(cin>>s,s!="."){//读入P集合
        n++;
        a[n]=s;
    }
    int x1,x2;
    str='.';
    while(cin>>s){//读入字符串的特殊处理
        x1=0;x2=s.length()-1;
        while(!IsChar(s[x1])){
            x1++;
        }
        while(!IsChar(s[x2])){
            x2--;
        }
        str+=s.substr(x1,x2-x1+1);
        len+=x2-x1+1;
    }
    memset(f,false,sizeof(f));
    f[0]=true;
    for(int i=1;i<=len;i++){
        if(check(i)){
            f[i]=true;
        }
        else f[i]=false;
    }
    for(int i=len;i>=0;i--){
        if(f[i]){
            cout<<i<<endl;
            break;
        }
    }
    
    return 0;
}
```

---

## 作者：wzh1120 (赞：3)

题意：给出一个集合，一个字符串，找出这个字符串的最长前缀，使得前缀可以划分为这个集合中的元素（集合中的元素可以不全部使用）。

解题思路：从字符串下表为0的位置开始匹配集合中的元素，匹配时最大长度为当前位置+该元素的长度，然后下表后移一位，继续往后找。。。最后得到的长度就是所求。

源代码：

   
```cpp
#include <iostream>  
#include <fstream>  
#include <string.h>  
using namespace std;  
char assemble[210][15];  
string str;  
int main() {  
    ofstream fout ("prefix.out");  
    ifstream fin ("prefix.in");  
    int count=0,Max=0;  
    while(cin>>assemble[count]&&assemble[count++][0]!='.');  
    str="";  
    string s;  
    while(cin>>s)  
      str+=s;  
    for(int i=0;i<str.length();i++)  
    {  
       for(int j=0;j<count;j++)  
       {  
         if(i+strlen(assemble[j])<=str.length())  
         {  
           bool judge=true;  
           for(int k=0;k<strlen(assemble[j]);k++)  
                if(str[i+k]!=assemble[j][k])  
                    {  
                     judge=false;break;  
                     }  
         if(judge)  
           if(Max<i+strlen(assemble[j]))  
         Max=i+strlen(assemble[j]);  
         }  
       }  
       if(i+1>Max)  
        break;  
    }  
    cout<<Max;  
    return 0;  
}
```

---

## 作者：Mint_Flipped (赞：2)

虽然是DP题 但蒟蒻 ~~TCL~~ 看不出来是DP

我的思路是：KMP + DFS + 剪枝

开个vector记录下子集合中的元素在 S 中首尾出现的位置，用KMP来实现。（~~数据较大，KMP不会超时~~）

然后用DFS从第一个位置往后走,直到走不通，比较记录路程的最大值。

如果不剪枝，最后一个点会T，为什么会T？ 因为走了重复的位置，所以
我们开一个vis[maxn] , 记录下去的位置走没走过 ，避免走重复的路。

代码如下：
```cpp
#include <bits/stdc++.h>
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define fo1(a,b) for(int a=0;a<b;++a)
#define fo2(a,b) for(int a=1;a<=b;++a)
#define inf 0x3f3f3f3f
using namespace std;
const int maxn=2e5+5;
const int mod=1e9+7;
int nxt[15];
vector <int> v[maxn]; //首尾位置
bool vis[maxn]; 
int ans=0;
void getnxt(string s2,int l2){  
    int i=0,j=1;
    while(j<l2){
        if(s2[i]==s2[j])
            nxt[j++]=++i;
        else if(!i)
            nxt[j++]=0;
        else
            i=nxt[i-1];
    }
}
void KMP(string s1,string s2,int l1,int l2){
    int i=0,j=0;
    while(i<l1){
        if(s1[i]==s2[j])
            i++,j++;
        else if(!j)
            i++;
        else
            j=nxt[j-1];
        if(j==l2){
        v[i-j].push_back(i-j-1+l2); //记录首尾位置
        j=nxt[j-1];
        }
    }
}
void dfs(int x){

    int len=v[x].size();
    if(len==0){
        ans=max(ans,x);
    }
    fo1(i,len){
        if(!vis[v[x][i]+1]){  //看看要去的点走没走过
        vis[v[x][i]+1]=1;
        dfs(v[x][i]+1);
        }
    }
}
int main()
{
    string s1,s2[205];
    int l=0;
    while(cin>>s2[++l]){
        if(s2[l]==".")
        break;
    }
    string t;
    while(cin>>t)
    s1+=t;
    int l1=s1.size();
    fo2(i,l-1){
    int l2=s2[i].size();
    mem(nxt,0);
    getnxt(s2[i],l2);
    KMP(s1,s2[i],l1,l2);
    }
    mem(vis,0);
    dfs(0);
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：LeeCarry (赞：2)

这道题就是类似完全背包和N^2的LIS的思想，如果连背包和LIS都没学过的可以百度DD大牛的背包9讲和LIS，都是很经典的DP模型，再回来看这题应该就能迎刃而解了。  

然后再掌握了基本背包思想后回到来看这一题的思路，就是先把所以的模式串P都存起来，之后我们逐个对i位置尝试该位置能不能放任意一个模式串，能的话就把dp[i]标记为1，当然还要先查看dp[i-模式串长度]为不为1，如果你前面都匹配不上了，后面这里匹配上了也没有用，毕竟要找的是最长连续能匹配的。  

前面也有很多大佬把思路讲的很好了，这里就是随便再写写，代码也自认还算清晰，然后主要发这篇文章的原因是想提醒大家注意两个坑点，第一个就是边界问题，这里i的边界是需要<=而不是<字符串长度的,第一次习惯性没加=然后一个数据WA了（这里自行思考一下为什么，应该是很简单的）。  

第二个坑点跟这题无关，算C++方面的，就是size_type类型跟int类型做运算后要强制类型转换，不如会出现奇怪的BUG，例如我第一次没做强制类型转换就发现if怎么样都能进去，输出又是正确的（因为输出时的%d也算做了转换）
![](![](https://img-blog.csdnimg.cn/20190521204122240.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzE5ODk1Nzg5,size_16,color_FFFFFF,t_70))

最后附一下AC代码  

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<set> 
using namespace std;
set<string> p;
int dp[200005]={0};
int main()
{
	ios::sync_with_stdio(false);
	string pi;
	while(cin>>pi&&pi!=".")
	{
		p.insert(pi);
	}
	string s;
	while(cin>>pi)
	{
		s+=pi;
	}
	dp[0]=1;
	//注意i的边界是<=size() 
	for(int i=1;i<=s.size();i++)//理论上来说这里的size()最好也先取出来，一是省常数时间，二是避免玄学BUG 
	{
		for(set<string>::iterator it=p.begin();it!=p.end();it++)
		{
			string tmp=(*it);	
			if((int)(i-tmp.size())>=0)//size_type类型做运算要强制转换，以免出现玄学BUG 
			{
				if(dp[i-tmp.size()]&&tmp==s.substr(i-tmp.size(),tmp.size()))//类完全背包思想 
				{
					dp[i]=1;
				}
			}
		}
	}
	//注意i的边界是=size() 
	for(int i=s.size();i>=0;i--)
	{
		if(dp[i])
		{
			printf("%d",i);
			return 0;
		}
			
	}
	return 0;
}
```


---

## 作者：nbqdd_2003 (赞：2)

假设这个字符串中的前缀可以达到第i位，而最后一位在集合中的字符串为后面j位，那么也就是说字符串的第一位到第i-j位都可以分解成集合中的元素。我们就可以用一个Boolean的数组记录可以达到的前缀的数位为true，如果b[i-j]为true，而字符串中j+1位到i位为集合中的元素，那么b[i]也为true。这样就成了动态规划了。

[/color][codep ]

```cpp
var
  s:array[1..300]of string;
  a:array[1..300]of longint;
  b:array[-10..200000]of boolean;
  ss,z:ansistring;
  c:char;
  n,m,i,j:longint;
procedure init;//输入时采用字符输入而非字符串比较省时间。
begin
  m:=1; 
  c:='a';
  while c<>'.' do
    begin
      read(c);
      if c in ['A'..'Z'] then
        s[m]:=s[m]+c
      else
        inc(m);
    end;
  ss:='';
  while not eof do
    begin
      readln(z);
      ss:=ss+z;
    end;
  n:=length(ss); 
  b[0]:=true;
  for i:=1 to m do
    a[i]:=length(s[i]);
end;
procedure work;
begin
  for i:=1 to n do
    for j:=1 to m do
      if b[i-a[j]] then
        if copy(ss,i-a[j]+1,a[j])=s[j] then
          begin
            b[i]:=true;
            break;
          end;
  for i:=n downto 0 do//最后输出Boolean数组中最大的一位。
    if b[i] then
      begin
        writeln(i);
        exit;
      end;
end;
begin
  init;
  work;
end.
```
[/codep ]
本程序参考过他人的程序。。


---

## 作者：洛谷Onlinejudge (赞：1)

首先来一句：

大佬们都用高级字符串算法碾压我，我一个题解都没看懂……

好了，步入正轨（~~接下来讲的都是邪门歪道~~）：

bool动态规划相信各位都想到了，它的方程是：

### **F[i]=F[j]&Word(j+1,i)     //(j<i)**

F是一个bool数组，F[i]表示从1到是否是合法前缀，若是合法前缀则为True,Word(j+1,i)表示j+1到i这一段是否是一个给出的集合，是则为True；

这里有一个小细节：若F[i]本身为True就不用再用数组推，因为本身为True的F[i]可能会被后面推出的False改成False；

现在重要的问题是，如何快速地判断出Word(j+1,i)是一个给出的集合？

### **这就需要用到Trie**

Trie是什么？——

（下面是来自@henry_y的一张图）

![](https://gss2.bdstatic.com/9fo3dSag_xI4khGkpoWK1HF6hhy/baike/w%3D268/sign=3b8ccc85354e251fe2f7e3fe9f87c9c2/dcc451da81cb39dbcc4509e9d5160924aa183083.jpg)

若有一个单词叫ten,你就可以通过t->e->n的方式分别储存在每个不同的节点中，从根节点（设为空）到叶节点（这里是n）的路径就是整个单词的名称；

因此我们就可以发现，每次判断Word的所耗时间就是扫一遍字符串的时间，很省事；

在本题中，将要用到Trie的最主要的两种操作：搭建和储存；

### **关于搭建：**

我也不知道该如何解释，还是放代码好——
```
void Build(string Name){
	int Len=Name.size(),From=0;
    //Len表示字符串的长度
    //From是字符串在树中一路经过的点
	for(register int i=0;i<Len;i++){
		int To=AC(Name[i]);//缩小ASCLL码
		if(Tree[From][To]==0)
			Tree[From][To]=(++Num);
            //Num是每个节点独一无二的编号
        //若原数中改点没有这个字符的儿子
        //就给它加一个
		From=Tree[From][To];
        //继续向下扫
	}
	Val[Num]=true;
    //表示从根到该节点的路径上的字符组成的字符串是一个合法集合
	return;
}
```

### **关于查找**

我还是不知道该如何解释，上代码——
```
bool Search(string Name){
	int Len=Name.size(),From=0,BB=0;
	for(register int i=0;i<Len;i++){
    	//沿着刚才的路径一路搜索
		if(Tree[From][AC(Name[i])]==0)
			return false;
        //如果中间就断掉了那肯定是非法的
		if(i==Len-1)
			BB=Tree[From][AC(Name[i])];
		From=Tree[From][AC(Name[i])];
	}
	if(Val[BB]==true)
		return true;
    //这里要注意，一定要是构成给出的集合才算合法
	return false;
}
```
最后是代码：

```
#include "bits/stdc++.h"
using namespace std;

int Tree[9920][31],Num,N;
bool F[220000],Val[9920];
string BigS,Add,In;

int AC(char Name){
	return Name-'A';
}

void Build(string Name){
	int Len=Name.size(),From=0;
	for(register int i=0;i<Len;i++){
		int To=AC(Name[i]);
		if(Tree[From][To]==0)
			Tree[From][To]=(++Num);
		From=Tree[From][To];
	}
	Val[Num]=true;
	return;
}

bool Search(string Name){
	int Len=Name.size(),From=0,BB=0;
	for(register int i=0;i<Len;i++){
		if(Tree[From][AC(Name[i])]==0)
			return false;
		if(i==Len-1)
			BB=Tree[From][AC(Name[i])];
		From=Tree[From][AC(Name[i])];
	}
	if(Val[BB]==true)
		return true;
	return false;
}

int main(void){
	cin>>In;
	while(In!="."){
		Build(In);//搭Trie 
		cin>>In;
	}
	BigS=" ";
	while(cin>>Add)
		BigS=BigS+Add;
	//古怪的输入 
	N=BigS.size();
	F[0]=true;
	for(register int i=1;i<N;i++)
		for(int j=0;j<=9&&(i-j-1)>=0;j++)
			if(F[i]==false)
				F[i]=Search(BigS.substr(i-j,j+1))&F[i-j-1];
	//推出方程 
	for(register int i=N-1;i>=0;i--){
		if(F[i]==true){
			cout<<i<<endl;
			return 0;
		}
	}//从后往前找出最大的答案 
	return 0;
}
```


---

## 作者：maorui_cow (赞：1)

这道题我使用了动规加记忆化搜索，确保不会炸，动规是个好东西下面请看代码

```
#include<bits/stdc++.h>
using namespace std;
struct node
{
	char hh[101];//每种方案
	int cd;//方案长度
} a[1010];
char b[200005];//需合成的数组
char tmp[200005];
int f[200005];//记忆化数组
int m;
int l;
int ans=0;
int cmp(node x,node y)//按长度排序
{
	return x.cd<y.cd;
}
int dp(int cd,char* qs)
{
	if(f[cd])//记忆化搜索动规方法
	{
		return f[cd];
	}
	int i;
	for(i=0; i<m; i++)//枚举每个方案
	{
		char* t=strstr(qs,a[i].hh);//这里如果不懂的话可以去这里看看
		if(cd+a[i].cd<=l&&t==qs)//如果满足条件
		{
			dp(cd+a[i].cd,t+a[i].cd);//继续往下走
		}
	}
	if(ans<cd)//记下结果
	{
		ans=cd;
	}
	f[cd]=cd;//记忆
	return cd;
}
int main()
{
	int i,j,k;
	while(1)
	{
		cin>>a[m].hh;
		a[m].cd=strlen(a[m].hh);
		if(a[m].cd==1&&a[m].hh[0]=='.')
		{
			break;
		}
		m++;
	}
	sort(a,a+m,cmp);
	while(cin>>tmp)//这里是根据输入的返回判断的
	{
		strcat(b,tmp);
	}
	l=strlen(b);
	dp(0,b);
	printf("%d\n",ans);
	return 0;
}

```

//strstr看不懂的可以来[这里](https://www.cnblogs.com/xzxl/p/7243490.html)

---

## 作者：Nuclear_Missile (赞：0)

#### 看到大佬们都用dp, 本人弱弱的发一发字典树的题解吧 因为刚做完p2292, 这俩题差不多, 但是交上去发现不对, ~~仔细看题后发现此题是**大写字母**~~
字典树长这个样子, 可以看成26叉树. 每个叶子节点有26个元素的数组, 代表子节点的值. 从根节点到每个叶子节点的链代表一个单词, 查询很方便

![字典树](https://gss0.bdstatic.com/-4o3dSag_xI4khGkpoWK1HF6hhy/baike/c0%3Dbaike80%2C5%2C5%2C80%2C26/sign=27e168080fb30f242197e451a9fcba26/d62a6059252dd42a745cc2c2033b5bb5c9eab806.jpg)

然后就可以从根节点开始查询, 用on数组表示此点是否能够匹配. 比如这样:
```cpp
	for (char *i = str; *i; ++i) {
		p = trie[p][*i - 'A'];
		if (!p) //0说明字典中没有这个单词
			break;
		if (end[p]) //结束代表单词
			on[i - str] = 1; //待会在这个位置往后接着上树查询
	}
```
如果能匹配, 再从这个点重新上树查询. 比如这样:
```cpp
	for (int t = 0; str[t]; ++t)
		if (on[t]) {
			ans = t + 1;
			p = 0; //初始化p
			for (char *i = str + ans; *i; ++i) {
				p = trie[p][*i - 'A'];
				if (!p) //0说明字典中没有这个单词
					break;
				if (end[p]) //结束代表单词
					on[i - str] = 1; //待会在这个位置往后接着上树查询
			}
		}
```
这样就可以保证多次查询, 匹配多个单词了

ac代码:
```cpp
#include <stdio.h>
#include <string.h>
#define DIC_NUM 205
#define DIC_LEN 15
#define TEXT_LEN 200010
short trie[DIC_LEN * DIC_NUM * 2 + 5][26], now = 1; //字典树 trie[i][j]表示i节点, 第j个字母
bool end[DIC_LEN * DIC_NUM * 2 + 5]; //这个点是否有结束的单词
inline void insert(char *str) {
	short p = 0; //当前节点位置  0:根节点
	for (char *i = str; *i; ++i) {
		short &check = trie[p][*i - 'A'];
		if (!check) //如果这个字母没有
			check = now++; //分配内存
		p = check;
	}
	end[p] = 1;
}
bool on[TEXT_LEN]; //上树查询的位置 完整匹配的位置
inline int find(char *str) {
	int ans = 0;
	short p = 0;
	for (char *i = str; *i; ++i) {
		p = trie[p][*i - 'A'];
		if (!p) //0说明字典中没有这个单词
			break;
		if (end[p]) //结束代表单词
			on[i - str] = 1; //待会在这个位置往后接着上树查询
	}
	for (int t = 0; str[t]; ++t)
		if (on[t]) {
			ans = t + 1; //由于字符串从0开始, 这里 + 1
			p = 0; //初始化p
			for (char *i = str + ans; *i; ++i) {
				p = trie[p][*i - 'A'];
				if (!p) //0说明字典中没有这个单词
					break;
				if (end[p]) //结束代表单词
					on[i - str] = 1; //待会在这个位置往后接着上树查询
			}
		}
	return ans;
}
char str[TEXT_LEN];
int main() {
	char buffer[100] = { 0 };
	scanf("%s", buffer);
	while (buffer[0] != '.')
		insert(buffer), scanf("%s", buffer);
	while (scanf("%s", buffer) == 1)
		strcat(str, buffer); //连接字符串
	printf("%d\n", find(str));
	return 0;
}

```



---

## 作者：litble (赞：0)

%%%%%%楼下xzy大佬玄学做法5msAC%%%%%%

为了追逐大佬的脚步，我重新做了一遍此题。

将原来二叉的trie树变成了一般的，这样就会快一些，不过相对的，空间消耗更大。

然后就44ms了。

可惜与大佬还是无法相提并论。

```cpp
#include<iostream>
#include<cstdio>
#include<climits>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
using namespace std;
char s[77],ss[200005];
int a[20005][28],tot,ans,ll;
bool f[200005],val[2005];
void tri(){
    int i,j,l=strlen(s),from=0,sum;
    for(i=0;i<l;i++){//建立trie树
        sum=s[i]-'A'+1;
        if(a[from][sum])from=a[from][sum];
        else {tot++;a[from][sum]=tot;from=tot;}
    }
    val[from]=1;
}
void init(int x){//进去找单词
    int i,j,from=0,sum;
    for(i=x;i<ll;i++){
        sum=ss[i]-'A'+1;
        if(a[from][sum])from=a[from][sum];
        else break;
        if(val[from])f[i]=1;
    }
}
int main()
{
    int i,j;
    while(1){scanf("%s",s);if(s[0]=='.')break;tri();}
    while(scanf("%s",s)!=EOF)strcat(ss,s);
    ll=strlen(ss);init(0);
    for(i=1;i<ll;i++)if(f[i-1]){init(i);ans=i;}
    if(f[ll-1])ans=ll;//注意不要掉了这一句。
    printf("%d",ans);
    return 0;
}
```

---

