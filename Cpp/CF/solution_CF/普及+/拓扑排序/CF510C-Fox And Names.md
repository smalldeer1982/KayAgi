# Fox And Names

## 题目描述

Fox Ciel is going to publish a paper on FOCS (Foxes Operated Computer Systems, pronounce: "Fox"). She heard a rumor: the authors list on the paper is always sorted in the lexicographical order.

After checking some examples, she found out that sometimes it wasn't true. On some papers authors' names weren't sorted in lexicographical order in normal sense. But it was always true that after some modification of the order of letters in alphabet, the order of authors becomes lexicographical!

She wants to know, if there exists an order of letters in Latin alphabet such that the names on the paper she is submitting are following in the lexicographical order. If so, you should find out any such order.

Lexicographical order is defined in following way. When we compare $ s $ and $ t $ , first we find the leftmost position with differing characters: $ s_{i}≠t_{i} $ . If there is no such position (i. e. $ s $ is a prefix of $ t $ or vice versa) the shortest string is less. Otherwise, we compare characters $ s_{i} $ and $ t_{i} $ according to their order in alphabet.

## 样例 #1

### 输入

```
3
rivest
shamir
adleman
```

### 输出

```
bcdefghijklmnopqrsatuvwxyz
```

## 样例 #2

### 输入

```
10
tourist
petr
wjmzbmr
yeputons
vepifanov
scottwu
oooooooooooooooo
subscriber
rowdark
tankengineer
```

### 输出

```
Impossible
```

## 样例 #3

### 输入

```
10
petr
egor
endagorion
feferivan
ilovetanyaromanova
kostka
dmitriyh
maratsnowbear
bredorjaguarturnik
cgyforever
```

### 输出

```
aghjlnopefikdmbcqrstuvwxyz
```

## 样例 #4

### 输入

```
7
car
care
careful
carefully
becarefuldontforgetsomething
otherwiseyouwillbehacked
goodluck
```

### 输出

```
acbdefhijklmnogpqrstuvwxyz
```

# 题解

## 作者：杨誉yy (赞：10)

~~其实就是板子题（引起众怒）~~  
u1s1，难度虚高。

前置芝士：拓扑排序
  
题目大意：给出排列好的$n$个字符串，求合法的重构字典序。  

就是把字母表打乱了，给出按新字母表顺序排列的字符串，让你求可能的字母表。

有关先后顺序，易想到拓扑排序。  

那么考虑如何建图。

对于相邻的两个字符串，取其长度最小值$len$，方便遍历。

从左往右扫，找到第一个不相同的字符，由先来的向后到的连一条边，即由字典序在前的向在后的连一条边。

添加一个**特判**。

题目强调字典序的判定方法，若字符串$s1$为$s2$的前缀且$s1!=s2$，那么$s1$应在$s2$前面。

于是我们求$len$的良苦用心有用了。

循环从$0$开始，到$len$结束，而不是$len-1$。这样可以在保证$s1$与$s2$呈包含关系时进行特判，即$i==len$时特判。

贴代码：
```cpp
cin>>pas;
for(i=2;i<=n;i++)
{
	cin>>now;
	int len=min(pas.length(),now.length());
	for(j=0;j<=len;j++)
	{
		if(j==len)
		{
			if(pas.length()>now.length())
			{
				printf("Impossible");
				return 0;
			}
			break;//
		}
		if(pas[j]!=now[j])
		{
			int up=pas[j]-'a';
			int down=now[j]-'a'; 
			l[up][++cnt[up]]=down;
			num[down]++;
			break;	
		}		
	}
	pas=now;
}
```
由于建图的操作只和相邻的字符串有关，所以只需要设两个变量。

~~不要问这些优化有什么用，问就是骚操作。~~

注意有斜杠的那一行的break不要漏掉。

接下来直接拓扑排序。

要判断是否凑足了26个字母；如果没有，说明有环，输出Impossible。

完整代码（稍有注释）：
```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<queue>
using namespace std;
string pas,now;
queue <long long> q;
int ct,n,i,j;
int ans[1000],num[1000],l[1000][1000],cnt[1000];
bool v[1000];
int main()
{
	scanf("%d",&n);
	cin>>pas;
	for(i=2;i<=n;i++)
	{
		cin>>now;
		int len=min(pas.length(),now.length());
		for(j=0;j<=len;j++)//是<=
		{
			if(j==len)
			{
				if(pas.length()>now.length())
				{
					printf("Impossible");
					return 0;
				}
				break;//不要漏了
			}
			if(pas[j]!=now[j])
			{
				int up=pas[j]-'a';//ASCII码转化
				int down=now[j]-'a'; 
				l[up][++cnt[up]]=down;
				num[down]++;
				break;	
			}		
		}
		pas=now;
	}
	for(i=0;i<=25;i++)//从零开始
	{
		if(num[i]==0)
		{
			q.push(i);
		}
	}
	while(!q.empty())
	{
		int head=q.front();
		ans[ct]=head;
		ct++;
		q.pop();
		for(i=1;i<=cnt[head];i++)
		{
			num[l[head][i]]--;
			if(num[l[head][i]]==0)
			{
				q.push(l[head][i]);
			}
		}		
	}
	if(ct==26)//检查是否有环
	{
		for(i=0;i<=25;i++)
		{
			printf("%c",ans[i]+'a');//记得转化回来
		}
	}
	else
	{
		printf("Impossible");
	}
}
```

PS：拓扑序列不止一种，对比样例只需要对比几个关键字符的位置就可以了。

---

## 作者：Juanzhang (赞：6)

~~这么破烂肯定过不去~~

**思路：**

- **dfs** topo sorting

同**@Qi_XingZhi**，以字母为节点，**建图**，**拓扑排序**，判环。

可以直接$dfs$每一个字母，顺便判环。

~~热爱dfs短代码~~

**代码：**

``` cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 30;
char str[110][110];
int n, now, a[maxn], vis[maxn];

vector <int> e[maxn];

bool dfs(int u) {
	if (vis[u]) {
		return vis[u] > 1;
	}
	vis[u] = 1;
	for (int v : e[u]) {
		if (!dfs(v)) {
			return 0;
		}
	}
	a[++now] = u;
	vis[u] = 2;
	return 1;
}

int main() {
	scanf("%d", &n);
	gets(str[0]);
	for (int i = 1; i <= n; i++) {
		gets(str[i]);
	}
	for (int i = 1; i < n; i++) {
		int j = 0, l1 = strlen(str[i]), l2 = strlen(str[i + 1]);
		for (; j < min(l1, l2) && str[i][j] == str[i + 1][j]; j++);
		if (j == l2) {
			return puts("Impossible"), 0;
		}
		if (j < l1) {
		    e[str[i][j] - 'a'].push_back(str[i + 1][j] - 'a');
		}
	}
	for (int i = 0; i < 26; i++) {
		if (!dfs(i)) {
			return puts("Impossible"), 0;
		}
	}
	for (int i = 26; i; i--) {
		putchar(a[i] + 'a');
	}
	return 0;
}
```

---

## 作者：山田リョウ (赞：5)

一道拓扑排序裸题。

对于字典序前后相邻的两个字符串 $a$ 和 $b$，$b$ 肯定不能是 $a$ 的前缀，不然的话这个字典序就是错的，要输出 $\text{Impossible}$。

如果 $a$ 不是 $b$ 的前缀的话，那么 $a$ 和 $b$ 第一个不相同的字符我们分别称之为 $c$ 和 $d$，$c$ 的优先级肯定是要比 $d$ 高的，也就是 $c$ 在答案中出现的位置一定是要比 $d$ 靠前的。

看到这里你想到了什么？拓扑排序！没错，我们要在图中连一条从 $d$ 到 $c$ 的有向边，最后输出这张图的拓扑排序就好了，如果图有环就输出 $\text{Impossible}$。

[代码](https://www.luogu.com.cn/paste/af071lw7)

---

## 作者：Clay_L (赞：2)

### 题意简述

现在有 $n$ 个按照某个被改变的字典序从小到大排序后的字符串，请求出改变后 $26$ 个字母的字典序。

### 算法分析

~~简单的~~拓扑排序板子题。

明显的，用拓扑排序。扫一遍输入的字符串，记录字典序大小。再扫字符串的过程中还需要判断后一个字符串是否为前一个字符串的前缀字符串（但不能等于前一个字符串。），因为一个字符串的前缀字符串的字典序一定小于等于这个字符串。如果后一个字符串为前一个字符串的前缀字符串的话就直接输出 `"Impossible"` 就行了。最后拓扑排序一遍，有环就输出 `"Impossible"`，否则把更新的字典序输出。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,in[1145],cnt,ans[1145];
string s1,s2;
vector<int>e[1145];
queue<int>q;
int main(){
	cin>>n>>s1;
	for(int i=1;i<n;i++){
		cin>>s2; 
		int m=min(s1.size(),s2.size()),j;
		for(j=0;j<m;j++){
			if(s1[j]!=s2[j]){
				int x=s1[j]-96,y=s2[j]-96;//为节省那微不足道的空间，这里给存进去的字符减去('a'-1)
				e[x].push_back(y);
				in[y]++;
				break;
			}
		}
		if(j>=m&&s2.size()<s1.size()){//记得特判
			printf("Impossible");
			return 0;
		}
		s1=s2;
	}
	for(int i=1;i<=26;i++) if(!in[i]) q.push(i);
	while(!q.empty()){//拓扑拓扑！
		int x=q.front();
		q.pop();
		ans[++cnt]=x;
		for(auto a:e[x]){
			in[a]--;
			if(!in[a]) q.push(a);
		}
	}
	if(cnt<26) printf("Impossible");
	else for(int i=1;i<=26;i++) printf("%c",ans[i]+96);//到最后记得把减掉的加回来
	return 0;
}
```

完结撒花。

---

## 作者：极寒神冰 (赞：2)

**思路**：暴力匹配每两个字符串，找到第一对相同的就连一条边，最后进行拓扑排序，如果字母数量达到26个就输出，否则就是有环直接impossible。

注意特判如果$S1_{len}>S2_{len}$，并且两个字符串没有相同部分。显然不符合题意直接impossible。
```
#include<bits/stdc++.h>
using namespace std;
const int N=1010;
int n;
int in[N],ret;
int head[N],cnt;
int vis[N][N];
char s[N][N],ans[N];
struct edge
{
	int nxt,to;
}e[N<<1];
inline void init()
{
	cnt=0;
	memset(head,-1,sizeof(head));
}
inline void toposort()
{
	queue<int>q;
	for(int i=1;i<=26;i++)
	{
		if(!in[i]) 
			q.push(i);
	}
	while(q.size()>0)
	{
		int u=q.front();
		q.pop();
		ans[++ret]=u+'a'-1;
		for(int i=head[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].to;
			--in[v];
			if(!in[v]) q.push(v);
		}
	}
	if(ret==26)
	{
		printf("%s",ans+1);
		return;
	}
	else puts("Impossible");
}
int main()
{	
	init();
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s[i]+1);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			int len1=strlen(s[i]+1),len2=strlen(s[j]+1),flag=0;
			int len=min(len1,len2);
			for(int k=1;k<=len;k++)
			{
				if(s[i][k]!=s[j][k])
				{
					flag=1;
					int u=s[i][k]-'a'+1,v=s[j][k]-'a'+1;
					if(!vis[u][v])
					{
						add_edge(u,v);
						vis[u][v]++;
						in[v]++;
					}
					break;
				}
			}
			if(!flag&&len1>len2) 
			{
				puts("Impossible");
				return 0;
			}
		}
	}
	toposort();
}
```


---

## 作者：JacoAquamarine (赞：1)

其实是一道板子题，~~建议评黄~~。

### 题意

求一种满足让$n$个字符串合法排列的字典序。

### 思路

不难想到使用拓扑排序。

具体地说，我们可以把字符串当作点，若有两个字符串 $s1,s2$ 且满足 $s1$ 的字典序小于 $s2$ ，则建一条从 $s1$ 到 $s2$ 的边。

注意到如果有两个字符串 $s2$ 为 $s1$ 前缀且 $s1$ 在 $s2$ 前面，那么无论如何改变字典序，同样的字符都是一样长的，而长的显然在后边，所以输出 `Impossible`。

又注意到图有环也显然不可能，所以所以有环也输出 `Impossible`。

最后放一段核心代码:
```cpp
for(int i=1;i<=26;i++)if(cnt[i]==0)q.push(i);
while(!q.empty()){
	int head=q.front();
	ans[sum]=head;
	sum++;
	q.pop();
	for(int i=1;i<=cnt[head];i++){
	cnt[a[head][i]]--;
	if(!cnt[a[head][i]])
		q.push(a[head][i]);
	}		
}
```

---

## 作者：_lxy_ (赞：1)

### 题意

求一种满足让 $n$ 个字符串按大小排列的字典序。

### 分析

首先根据输入的字符串建图：对于每一个字符串 $s_i$ ，枚举所有在它之前的字符串 $s_j$，刨去两个字符串相同的前缀后建立一条由 $s_i$ 第一个字符指向 $s_j$ 第一个字符的有向边。然后跑一遍拓扑，如果跑出来 topo 数组的大小正好是 $26$，说明有一条路径，否则无解。注意特判一个字符串是另一个字符串前缀的情况。

### 代码

```cpp
#include <bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
inline void qread(){}template<class T1,class ...T2>
inline void qread(T1 &a,T2&... b)
{
    register T1 x=0;register bool f=false;char ch=getchar();
    while(ch<'0') f|=(ch=='-'),ch=getchar();
    while(ch>='0') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    x=(f?-x:x);a=x;qread(b...);
}
template<class T1,class T2>inline T1 qmax(const T1 &x,const T2 &y){return x>y?x:y;}
template<class T1,class T2>inline T1 qmin(const T1 &x,const T2 &y){return x<y?x:y;}
const int MAXN=37;
int n,head[MAXN],in[MAXN];
char s[107][107];
struct Edge
{
    int to,nxt;
    Edge(){;}Edge(int _to,int _nxt):to(_to),nxt(_nxt){}
};vector<Edge>edge;
void add_edge(int u,int v){edge.push_back(Edge(v,head[u]));head[u]=edge.size()-1;}
vector<int>topo;
void topo_sort()
{
    topo.clear();queue<int>q;int i;
    for(i=0;i<26;i++) if(!in[i]) q.push(i);
    while(!q.empty())
    {
        int u=q.front();q.pop();topo.push_back(u);
        for(i=head[u];i!=-1;i=edge[i].nxt) if(!(--in[edge[i].to])) q.push(edge[i].to);
    }
}
int main()
{
    qread(n);int i,j;mem(head,-1);bool flag=true;
    for(i=0;i<n;i++) scanf("%s",s[i]);
    for(i=0;i<n;i++)
    {
        for(j=0;j<i;j++)
        {
            if(strlen(s[j])>strlen(s[i]))
            {
                bool f=true;
                for(int k=0;k<strlen(s[i]);k++)
                {
                    if(s[i][k]!=s[j][k])
                    {
                        f=false;
                        break;
                    }
                }
                if(f) // 如果后面的字符串是前面的前缀，说明无论是怎样的字典序都不能满足
                {
                    flag=false;
                    break;
                }
            }
            for(int k=0;k<qmin(strlen(s[i]),strlen(s[j]));k++)
            {
                if(s[i][k]!=s[j][k]) // 找出第一个不相等的字符，建边
                {
                    int u=s[j][k]-97,v=s[i][k]-97;
                    add_edge(u,v);in[v]++;
                    break;
                }
            }
        }
        if(!flag) break;
    }
    if(!flag) return printf("Impossible\n"),0;
    topo_sort();flag&=(topo.size()==26);
    if(!flag) return printf("Impossible\n"),0;
    for(auto i:topo) printf("%c",i+97);
    return 0;
}
```

---

## 作者：Enterpr1se (赞：1)

>~~没有图，就要创造图。~~  
~~——鲁迅~~

看到这题我首先想到的算法是Floyd【我们老师当时教的是如果需要比较多个数（1000 个以下），大概率是使用 Floyd】，但是算法标签并没有Floyd（尽管如此一会你们就会发现 Floyd 真的很有用），反倒是有一个“拓扑排序”。但是无论哪种算法都需要我们先建图，这下整道题的逻辑就基本清楚了。  
~~（秦风式战术停顿）~~  
但事实真的如此吗？  
其实字典序中有很多不容易被注意到的小细节，所以我们在开始做题之前，不妨先看看[字典序的定义](https://baike.baidu.com/item/%E5%AD%97%E5%85%B8%E5%BA%8F/7786229)。其中比较方法如下（至于我为啥要写这么基础的东西，看到后面就知道了）：
>对于两个长度分别为 $n$ 和 $m$ 的字符串 $a$ 和 $b$，
>+ 首先比较 $a_1$ 和 $b_1$，若 $a_1$ 在字母表中比 $b_1$ 更靠前，则 $a$ 比 $b$ 更靠前。
>+ 若 $a_1 = b_1 $，则比较字符串 $\{a_1,a_2,a_3,...,a_n\}$ 和字符串 $\{b_1,b_2,b_3,...,b_m\}$。  
>特判：  
>+ 若 $a=\{b_1,b_2,b_3,...,b_n\}$，则 $a$ 比 $b$ 更靠前。

反过来，我们就可以得到通过字典序求字母表的过程：  
>对于两个长度分别为 $n$ 和 $m$ 的字符串 $a$ 和 $b$，
>+ 首先比较 $a_1$ 和 $b_1$，若 $a$ 比 $b$ 更靠前，则 $a_1$ 在字母表中比 $b_1$ 更靠前。
>+ 若 $a_1 = b_1 $，则比较字符串 $\{a_1,a_2,a_3,...,a_n\}$ 和字符串 $\{b_1,b_2,b_3,...,b_m\}$。  

由此我们就可以得到第一段代码：求字母间关系：  
```cpp
void getrel(string a,string b){
	if(!a.length() || !b.length()) return;
	if(a[0]==b[0]){
		if(a.length()>1 && b.length()>1) getrel(a.substr(1),b.substr(1));
		return;
	}
	add(a[0],b[0]);
	return;
}
```


接着我们再来看~~骗分助手~~ `Impossible` 的成因，无非三种：  
+ Case 1：得出结论中字母 $letter_a$ 比 $letter_b$ 靠前，且 $letter_b$ 比 $letter_a$ 靠前。  
+ Case 2：得出结论中 $letter_a$ 比其本身更靠前。  
+ Case 3：字符串 `a.substr(0,x)` （$x<length(a)$）比字符串 `a` 更靠前。（这一点困扰了我这个蒟蒻将近半个小时）  

接下来整段代码的逻辑就出来了：  
1. 输入，判断是否存在 Case 3
2. 链式前向星上建图（上面已经贴了代码）  
3. 将链式前向星上的图转换到一个矩阵上（方便运行 Floyd） 并统计出度（方便运行拓扑排序） 
4. 通过Floyd找出所有可以推出的字母关系  
5. 在矩阵中判断是否有 Case 1 和 Case 2  
6. 运行拓扑排序，找到一组解  
完整代码：  
```cpp
//Luogu-CF510C Solution Version 题解版本 
//Luogu @W53729 (Userid 363523)
//@_Qijia (Userid 363524) AK IOI!
#include<iostream>
#include<string>
#include<queue>
#define regll register long long
#define regint register int
#define regshort register short
#define _Qijia using
#define AK namespace
#define IOI std
_Qijia AK IOI;//大佬保佑我AC（？ 
int n,last[300],rcnt,ind[300];
string name[105],ans;
bool rel[300][300];
char curr,targ;
queue<char> qu;
struct edge{
	char to;
	int prev;
} fig[10005];
void add(int s,int e){
	++rcnt;
	fig[rcnt]={e,last[s]};
	last[s]=rcnt;
}
void getrel(string a,string b){
	if(!a.length() || !b.length()) return;
	if(a[0]==b[0]){
		if(a.length()>1 && b.length()>1) getrel(a.substr(1),b.substr(1));
		return;
	}
	add(a[0],b[0]);
	return;
}
void trans(){
	for(char i='a';i<='z';++i)
		for(regint j=last[i];j;j=fig[j].prev){
			rel[i][fig[j].to]=true;
			++ind[fig[j].to];
		}
	return;
}
void floyd(){
	for(char k='a';k<='z';++k)
		for(char i='a';i<='z';++i)
			for(char j='a';j<='z';++j)
				if(rel[i][k] && rel[k][j]) rel[i][j]=true;
	return;
}
signed main(){
	ios::sync_with_stdio(false);//加速黑科技
	//Step 1 
	cin>>n;
	for(regint i=1;i<=n;++i) cin>>name[i];
	for(regint i=1;i<=n-1;++i){
		if(name[i].length()>name[i+1].length() && name[i+1]==name[i].substr(0,name[i+1].length())){
			cout<<"Impossible";
			return 0; 
		}
	}
	
	//Step 2
	for(regint i=1;i<=n;++i)
		for(regint j=i+1;j<=n;++j)
			getrel(name[i],name[j]);
	
	//Step 3
	trans();
	
	//Step 4
	floyd();
	
	//Step 5
	for(char i='a';i<='z';++i)
		for(char j=i+1;j<='z';++j)
			if(rel[i][j] && rel[j][i]){
				cout<<"Impossible";
				return 0;
			}
	for(char i='a';i<='z';++i)
		if(rel[i][i]){
			cout<<"Impossible";
			return 0;
		}
		
	//Step 6 
	for(char i='a';i<='z';++i)
		if(!ind[i]) qu.push(i);
	while(qu.size()){
		curr=qu.front(); 
		qu.pop();
		cout<<curr;
		for(regint j=last[curr];j;j=fig[j].prev){
			targ=fig[j].to;
			--ind[targ];
			if(!ind[targ]) qu.push(targ);
		}
	}
	return 0;
}
```


---

## 作者：DPseud (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF510C)

我们看一眼题目：排列、任意一组，可以想到一个看似和题目毫不相关的东西：拓扑排序。

但是这题难就难在如何转化，我们把字符串按字典序建图，然后拓扑排序，具体地说，有两个字符串 $a$ 和 $b$，如果 $a$ 的字典序小于 $b$，我们把 $a$ 连接到 $b$。

看起来很复杂，其实就是几行：

```cpp
for(int i=2;i<=n;i++)
{
	b=t[i];
	int l=min(a.length(),b.length());//实际上
	for(int j=0;j<=l;j++)
	{
		if(a[j]!=b[j])
		{
			int c=a[j]-97,d=b[j]-97;//97不用解释了，a 
			q[c].push_back(d);//常规建图操作
			y[d]++;
			break;	
		}		
	}
	a=b;//一个省a[i]和a[i-1]的方式
}
```

但是，我们漏了 $\texttt{Impossible}$ 的情况，具体地说，如果 $a$ 是 $b$ 的前缀：

```cpp
for(int i=2;i<=n;i++)
{
	int l=min(a.length(),b.length());
	for(int j=0;j<=l;j++)
	{
		if(j==l)//全部搜索完
		{
			if(a.length()>b.length())
			{
				cout<<"Impossible";
				return 0;
			}
		}
	}
}
```

至于拓扑排序本身，首先我们需要把元素全部插入队列，然后来一个循环直到队列为空，在循环中查找当前队首所有可以指向的点，加入队列就可以了，当然，你也可以选择用 dfs 来查找。

这个思路仍然拿不了满分，这是因为我们漏了环的存在，如果有环，我们一样要输出 $\texttt{Impossible}$。

[拓扑排序](https://www.luogu.com.cn/paste/w0os4ntd)在这。

---

## 作者：hank0402 (赞：0)

比较简单的拓扑排序题，模拟赛的时候无脑切了。qwq

### 题目大意

通过改变字典序来让 $n$ 个字符串大小递增。

### 题解

比较每两个字符串 $a$ 和 $b$ 如果 $b$ 是 $a$ 的前缀，那么肯定不可能，因为无论怎么改字典序，同样的字符一定是一样的，长的绝对在后面，不可能在前面，因此不可能。

记 $a$ 第一个与 $b$ 不同的字符为 $x$，$b$ 第一个与 $a$ 不同的字符为 $y$. 那么改变字典序后，$x$ 绝对在 $y$ 前面，在 $x$ 到 $y$ 建一条有向边。建完图后，跑拓扑排序，如果有环则不可能，否则记录拓扑序，在字母表里抠掉然后与字母表一起输出即可。

### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, in[105], out[105], ans, cnt;
string names[105], p;
vector<int> G[105];
bool vis[105];
bool topo() { //拓扑排序
	queue<int> q; //拓扑序列
	for(int i = 0; i < 26; ++i) {
		for(int j : G[i]) {
			in[j] ++;
			vis[i] = true;
			vis[j] = true;
		}
	}
	for(int i = 0; i < 26; ++i) {
		if(in[i] == 0 && vis[i]) {
			q.push(i);
			p = p + char(i + 'a');
			ans ++;
		}
	}
	while(!q.empty()) {
		int t = q.front(); q.pop();
		for(int i : G[t]) {
			in[i] --;
			if(in[i] == 0) {
				q.push(i);
				p = p + char(i + 'a');
				ans ++;
			}
		}
	}
	int nodes = 0;
	for(int i = 0; i < 26; ++i) {
		nodes += (vis[i] == true);
	}
	return ans == nodes; //判断是否有环
}
int main() {
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> names[i];
	for(int i = 1; i <= n; ++i) {
		for(int j = i + 1; j <= n; ++j) {
			int l1 = names[i].size(), l2 = names[j].size();
			bool flag = false;
			for(int k = 0; k < min(l1, l2); ++k) {
				if(names[i][k] != names[j][k]) {
					G[names[i][k] - 'a'].push_back(names[j][k] - 'a'); //建图
					flag = true;
					break;
				}
			}
			if(!flag && l1 > l2) { //如果b是a的前缀，不可能
				cout << "Impossible";
				return 0;
			}
		}
	}
	bool flg = topo(), visp[105];
	if(!flg) { //若存在环，不可能
		cout << "Impossible\n";
		return 0;
	}
	int pl = p.size();
	for(int i = 0; i < pl; ++i) {
		visp[p[i] - 'a'] = true;
	}
	for(int i = 0; i < 26; ++i) {
		if(vis[i] == false) cout << char('a' + i);
	}
	cout << p;
	return 0;
}
```

---

## 作者：lym12321 (赞：0)

# CF510C Fox And Names

## 题意

给出 $n$ 个 **按照某种特定的字典序** 排列的单词，求出其字典序。 

- 若存在多组解，输出任意一组。  

- 若无解，输出 `Impossible`。  

数据范围：$1 \leq n \leq 100$，$1 \leq | name_i | \leq 100$。

## 题目分析

### 前置知识

- [拓扑排序](https://zhuanlan.zhihu.com/p/260112913)  

- [字典序](https://baike.baidu.com/item/%E5%AD%97%E5%85%B8%E5%BA%8F/7786229?fr=aladdin)

### Solve

看到这里，相信你已经对 **拓扑排序** 和 **字典序** 有过一些了解了。~~（不了解就先去学啦）~~

而它们，正是解决这个问题的关键！

首先，我们知道，拓扑排序是将一个有向图的顶点排成一个线性序列，且满足：

- 若存在一条边 $<u, v>$，则 $u$ 在线性序列中出现在 $v$ 之前。

为了使用 **拓扑排序** 求字典序，我们也应该建一个满足此性质的有向图。

- 对于 **字典序** 来说，“优先级”高的字母出现在前面。

- 对于输入的单词来说，先输入的单词总比后输入的单词“优先级”高。

由此，建图的方法也就显而易见了。设输入的 **相邻两个** 单词分别为 $s$ 和 $t$：

- 找到最小的 $i$ 使得 $s_i \not= t_i$。  

- 建立有向边 $<s_i, t_i>$。

通过这样的步骤，我们就可以建出符合要求的图。  

但仍有个不可忽略的常识：

> 若单词 $s_1$ 是另一个单词 $s_2$ 的前缀，则 $s_1$ 应出现在 $s_2$ 前面。

所以，在输入的时候需要加一个特判：

- 如果 **后输入的单词** 是 **先输入的单词** 的前缀，直接输出 `Impossible` 就好啦！

至此，我们可以写出完整的代码，具体代码分析见注释。

## Code

这里用 `priority_queue` 优先队列，可以求出字典序最小的字典序。（？套娃

（是指按正常字典序来说字典序最小的答案啦。）

```cpp
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn = 205;

// lenBef - 前一个字符串的长度
// lenNow - 这一个字符串的长度
// lenMin - 两个字符串中较短的长度
// po - 寻找第一个不相同字母时用的 pointer
// deg[i] - 第 i 个点的入度
// arr[i] - 拓扑排序出的答案
int n, lenBef, lenNow, lenMin, po, deg[30], arr[30];

// bef - 前一个字符串
// now - 这一个字符串
string bef, now;

// vector 存图，因为只有 26 个字母所以不需要开太多
vector <int> ch[30];

inline void inp(string &s, int &len){
    // 图省事写的 input 函数
    // 这里的 s 和 len 都是指针形式传入
    cin >> s;
    len = s.length();
}

int topoSort(){
    // 拓扑排序
    int cnt = 0;
    priority_queue <int> q;         // 其实可以用普通队列的，毕竟输出任意满足要求的字典序即可
    for(int i = 0; i < 26; i++){
        if(!deg[i]) q.push(-i);     // 大根堆加个负号当小根堆用
    }
    while(!q.empty()){
        int k = -q.top(); q.pop();  // 记得加负号
        arr[++cnt] = k;             // 记录答案
        for(auto to : ch[k]){
            deg[to]--;
            if(!deg[to]) q.push(-to);
        }
    }
    return cnt;                     // 返回答案的数量
}

int main(){
    // 祖传加速
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n;
    inp(bef, lenBef);               // 输入第一个字符串作为“前一个”
    for(int i = 2; i <= n; i++){
        inp(now, lenNow);           // 输入“这一个”字符串
        lenMin = min(lenBef, lenNow);
        for(po = 0; po < lenMin; po++) if(bef[po] != now[po]) break;
        if(po == lenMin && lenBef > lenNow){
            // 此时后一个字符串是前一个字符串的前缀
            cout << "Impossible";
            return 0;
        }
        if(po != lenMin){
            // 这里要注意判断一下，因为如果 po == lenMin 的话，两字符串是相等的。
            ch[bef[po] - 'a'].push_back(now[po] - 'a');
            deg[now[po] - 'a']++;
        }
        bef = now; lenBef = lenNow; // 将“这一个”字符串变成“前一个”字符串，进行下一轮比较
    }
    int cnt = topoSort();
    // 输出答案
    if(cnt == 26) for(int i = 1; i <= cnt; i++) cout << char(arr[i] + 'a');
    else cout << "Impossible";      // 没有合法答案的时候记得输出 Impossible
    return 0;
}
```

---

## 作者：kdy20100729 (赞：0)

### 题意简述：  
给定一个数 $n$，然后再给出 $n$ 个按某一种与我们平时不一样的字典序排列的字符串，让你输出这个字典序，如果不能，输出 ```Impossible```。  

### 思路：  
大家应该可以看得出来，这道题可以用拓扑排序。首先，我们可以将相邻的字符串找到第一个不同的字符，然后建边（第一个字符指向第二个字符）。再将入度为 $0$ 的字符入队，再去做模板拓扑，但每次都要将队顶元素加到 ans 数组的末尾。最后判断数组长度是否等于 $26$，如果等于则输出 $ans$ 数组，否则输出 ```Impossible```。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char ans[105];
string s[105];
queue<char> q;
int n,cnt,in[205];
vector<char> nbr[205];
signed main()
{
	cin >> n;
	for(int i=1; i<=n; i++)
	{
		cin >> s[i];
		if (i==1)
			continue;
		for(int j=0; j<min(s[i-1].size(),s[i].size()); j++)
		{
			char c1=s[i-1][j],c2=s[i][j];
			if (c1!=c2)
			{
				nbr[c1].push_back(c2);
				in[c2]++;
				break;
			}
		}
	}
	for(char i='a'; i<='z'; i++)
		if (in[i]==0)
			q.push(i);
	while(q.empty()==false)
	{
		char cur=q.front();
		q.pop();
		ans[++cnt]=cur;
		for(int i=0; i<nbr[cur].size(); i++)
		{
			char nxt=nbr[cur][i];
			in[nxt]--;
			if (in[nxt]==0)
				q.push(nxt);
		}
	}
	if (cnt==26)
		for(int i=1; i<=cnt; i++)
			cout << ans[i];
	else
		cout << "Impossible";
	return 0;
}
```  
乍一看是不是没有问题，但是，你会发现第 $13$ 个点神奇的 WA 了。我们先来看一下这一组样例：  
> abcdefg  
abc

很显然，这个样例应该输出 ```Impossible```，但是上面的代码并不会输出 ```Impossible```，因为我们没有特判后一个字符串是前一个字符串的子串并且前一个字符串的长度比后一个字符串的长度要长时的情况。  

最后奉上 AC 代码：  
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char ans[105];
string s[105];
queue<char> q;
int n,cnt,in[205];
vector<char> nbr[205];
signed main()
{
	cin >> n;
	for(int i=1; i<=n; i++)
	{
		cin >> s[i];
		if (i==1)
			continue;
		int j;
		for(j=0; j<min(s[i-1].size(),s[i].size()); j++)
		{
			char c1=s[i-1][j],c2=s[i][j];
			if (c1!=c2)
			{
				nbr[c1].push_back(c2);
				in[c2]++;
				break;
			}
		}
		if (j==min(s[i-1].size(),s[i].size())&&s[i-1].size()>s[i].size())
		{
			cout << "Impossible";
			return 0;
		}
	}
	for(char i='a'; i<='z'; i++)
		if (in[i]==0)
			q.push(i);
	while(q.empty()==false)
	{
		char cur=q.front();
		q.pop();
		ans[++cnt]=cur;
		for(int i=0; i<nbr[cur].size(); i++)
		{
			char nxt=nbr[cur][i];
			in[nxt]--;
			if (in[nxt]==0)
				q.push(nxt);
		}
	}
	if (cnt==26)
		for(int i=1; i<=cnt; i++)
			cout << ans[i];
	else
		cout << "Impossible";
	return 0;
}
```

---

## 作者：inexistent (赞：0)

详见我的[博客](https://www.cnblogs.com/qixingzhi/p/9299446.html)
----------------

思路分析：
       
要是把这道题联系到图上就很容易想了。

如何建图？由于最后要求名字满足字典序，所以不妨以字母为节点，然后按照题意的顺序从小的到大的连边。建图了又什么用？如果图存在环，那么也就意味着矛盾了——因为这比自己小的节点比自己大。因此是否存在一个合法的字典序的判断依据就是建的图是否存在环。

第二步，如何输出任意一个方案？这很简单，由于有可能有的字母根本没有参与建图，所以这些字母就不需要管了。对于在图里的字母，入度为0的点就是已知的应当最小的点——所以我们进行一次拓扑排序来得到序列。最后和其它字母拼合起来就好了。

代码注意点：
　　
注意有两个相同前缀的字符串时，如果前面的那个字符串比后面的还要长，那么一定不满足，直接输出impossible就好了。因为无论字典序如何，都不可能满足前面的字典序比后面的小。

```cpp
/** This Program is written by QiXingZhi **/
#include <cstdio>
#include <queue>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define  r  read()
#define  Max(a,b)  (((a)>(b)) ? (a) : (b))
#define  Min(a,b)  (((a)<(b)) ? (a) : (b))
using namespace std;
typedef long long ll;
const int N = 1010;
const int INF = 1061109567;
inline int read(){
    int x = 0; int w = 1; register int c = getchar();
    while(c ^ '-' && (c < '0' || c > '9')) c = getchar();
    if(c == '-') w = -1, c = getchar();
    while(c >= '0' && c <= '9') x = (x << 3) +(x << 1) + c - '0', c = getchar();
    return x * w;
}
string s[N];
queue <int> q;
vector <int> G[3000];
bool exist[N],vis[N],b[N],hh[N];
int rd[N],Q[N],ans_topo[N];
int n,len1,len2,flg,_cur,t,topo_num;
inline void AddEdge(int u, int v){
	exist[u] = 1;
	exist[v] = 1;
	G[u].push_back(v);
	++rd[v];
}
inline void ThrowOut(){
	printf("Impossible");
	exit(0);
}
inline bool BFS(int x){
    while(!q.empty()) q.pop();
    q.push(x);
    int cur,sz,to;
    while(!q.empty()){
        cur = q.front();
        q.pop();
        if(cur == _cur){
            if(flg == -1){
                ++flg;
            }
            else if(flg == 0){
                return 1;
            }
        }
        if(vis[cur]) continue;
        vis[cur] = 1;
        sz = G[cur].size();
        for(int i = 0; i < sz; ++i){
            to = G[cur][i];
            q.push(to);
        }
    }
    return 0;
}
inline bool Check_Circle(){
	for(int i = 'a'; i <= 'z'; ++i){
        memset(vis,0,sizeof(vis));
        if(exist[i]){
            _cur = i;
            flg = -1;
            if(BFS(_cur)) return 1;
        }
    }
    return 0;
}
int main(){
//	freopen(".in","r",stdin);
	cin >> n;
	for(int i = 1; i <= n; ++i){
		cin >> s[i];
	}
	for(int i = 2; i <= n; ++i){
		len1 = s[i-1].size();
		len2 = s[i].size();
		flg = 0;
		for(int j = 0; j < len2; ++j){
			if(j >= len1){
				flg = 1;
				break;
			}
			if(s[i-1][j] != s[i][j]){
				flg = 1;
				AddEdge(s[i-1][j],s[i][j]);
				break;
			}
		}
		if(flg == 0 && len1 > len2){
			ThrowOut();
		}
	}
	if(Check_Circle() == 1){
		ThrowOut();
	}
	int flg=0,sz;
    for(;;){
        flg = 0, t = 0;
        for(int i = 'a'; i <= 'z'; ++i){
            if(rd[i] == 0 && !b[i] && exist[i]){
                flg = 1;
                b[i] = 1;
                Q[++t] = i;
            }  
        }
        if(!flg) break;
        for(int i = 1; i <= t; ++i){
            int cur = Q[i];
            ans_topo[++topo_num] = cur;
            hh[cur] = 1;
            sz = G[cur].size();
            for(int j = 0; j < sz; ++j){
                --rd[G[cur][j]];
            }
        }
    }
    for(int i = 1; i <= topo_num; ++i){
    	printf("%c",ans_topo[i]);
	}
	for(int i = 'a'; i <= 'z'; ++i){
		if(!hh[i]){
			printf("%c",i);
		}
	}
	return 0;
}

```

---

## 作者：Mickey_snow (赞：0)

[CF510C](http://codeforces.com/contest/510/problem/C) _Fox And Names_ : 拓扑排序

题目大意：给定 $n$ 个字符串，求出一个字典是的这 $n$ 个字符串是已经按照字典序排好序了的。

如果我们有 $n$ 个字符串，我们至多可以得到 $n-1$ 个类似于字符 $s$ 小于字符 $t$ 的约束条件。假设第 $i$ 个字符串为 $a_i$ ，那么如果它们按照字典序排列好的话一定满足 $\forall a_i \leq a_{i+1}$ .模拟一下比较字典序的过程，要比较两个字符串字典序时我们可以创建两个指针一位位地往后面扫，在这里也一样，扫到第一个不相同的位置，就可以得到 $a_i[j] < a_{i+1}[j]$ .

之后，将26个字母当作结点，按照这些条件进行一次拓扑排序即可，如果无法排序则说明这样的字典不存在。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

vector<int> G[26];
int in[26] = {};
char pos[26], *nowAt = pos;

int main()
{
	int totStrings, it; cin >> totStrings;
	string a, b;

	if (totStrings == 1) {
		for (char it = 'a'; it <= 'z'; it++)cout << it;
		putchar('\n'); return 0;
	}

	cin >> b;
	for (int now = 1; now < totStrings; now++) {
		a = b; cin >> b;
		for (int i = 0; i < a.length(); i++) {
			if (i >= b.length()) { puts("Impossible");return 0; }
			if (a[i] != b[i]) {
				G[a[i] - 'a'].push_back(b[i] - 'a');
				in[b[i] - 'a']++;
				break;
			}
		}
	}

	queue<int> que;
	for (int i = 0; i < 26; i++)if (in[i] == 0)que.push(i);
	while (!que.empty()) {
		it = que.front(); que.pop();
		*nowAt++ = it;
		for (const auto &_it : G[it])
			if (--in[_it] == 0)
				que.push(_it);
	}

	if (nowAt != pos + 26)puts("Impossible");
	else for (int i = 0; i < 26; i++)putchar(pos[i] + 'a');
	putchar('\n');

	//system("pause");
	return 0;
}
```



---

