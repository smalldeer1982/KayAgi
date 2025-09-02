# [USACO14FEB] Auto-complete S

## 题目描述

有 $w$ 个由小写字符构成的字典和 $n$ 个询问。每个询问由一个字符串 $s$ 和一个整数 $k$ 构成，求在字典序排序下字典内由 $s$ 为前缀的第 $k$ 字符串在输入字典的位置。若不存在，则输出 $-1$

## 说明/提示

对于 $100\%$ 的数据，$w \le 30000$，$1\le n \le 1000$，字典内每个字符串的长度均小于等于 $1000$，且字典的单词总长不超过 $10 ^ 6$。

样例解释：

对于第 $1$ 个询问，含义为在字典中找到以 ```a``` 为前缀且按字典序排序后第 $4$ 个字符串，而字典中以 ```a``` 为前缀且按字典序排序后为 $\{$  ```aa```，```aaa```，```aab```，```ab```，```abc```，```ac``` $\}$，第 $4$ 个是 ```ab```，其在输入中为第 $3$ 个，故输出为 $3$

同理，对于第 $2$ 个和第 $3$ 个询问是在字典中找到以 ```da``` 为前缀且按字典序排序后的第 $2$ 和第 $4$ 个字符串。而以 ```da``` 为前缀的字符串按字典序排序后为 $\{$```daa```，```dab```，```dadba``` $\}$，故第 $2$ 个为 ```dab``` ，其在输入中为第 $1$ 个，故第 $2$ 个输出为 $1$，而该序列中没有第 $4$ 个，故第 $3$ 个询问无解，输出 $-1$

来源：USACO 2014 Feburary Contest Silver

翻译：@[zymooll](/user/289296)

## 样例 #1

### 输入

```
10 3
dab
ba
ab
daa
aa
aaa
aab
abc
ac
dadba
4 a
2 da
4 da```

### 输出

```
3
1
-1```

# 题解

## 作者：Expecto (赞：11)

先把字典排个序，之后lower\_bound 下前缀的位置，加上k就好了

```cpp
#include<bits/stdc++.h>
using namespace std;
pair<string ,int> a[90030];
bool match(string x,string y){
    if (y.length()>x.length()) return 0;
    return x.substr(0,y.size())==y;
}
int main(){
    int w,n;
    cin>>w>>n;
    for (int i=0;i<w;i++){
        cin>>a[i].first;
        a[i].second=i;
    }
    sort(a,a+w);
    while (n--){
        string pre;
        int k;
        cin>>k>>pre;
        int pos=k-1+lower_bound(a,a+w,make_pair(pre,0))-a;
        if (pos>=w || !match(a[pos].first,pre)) {
            cout<<"-1\n";
            continue;
        }
        cout<<a[pos].second+1<<'\n';
    }
    return 0;
}
```

---

## 作者：Zhou_SY (赞：4)

本题思路很简单：排序$O(m log m)$+查找$O(nlogm)$=$O((n+m)log m)$

极限数据$O((n+m)logm)=O(31000×16)≈O(500000)$

1. 按字典序升序排列（降序当然也可以）
2. 在$a$数组中二分查找读入的前缀
3. 向左和向右寻找，确定区间$[l,r]$
4. 输出答案
- 若$r-l+1<k$，即以该字符串为前缀的元素不足$k$个，输出$-1$无解
- 若$r-l+1>=k$，则输出这个区间中第$k$个元素的位置，即$a[l+k-1]$

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	string s;
	int num;
}a[30010];
int n,m,k;
string s;

bool cmp(node x,node y)
{
	return x.s<y.s;
}
string getstring(string s,int begin,int len)//截取字符串
{
	string tmp;
	for(int i=begin;i<begin+len;i++)
		tmp+=s[i];
	return tmp;
}
int erfen(string t)//二分查找
{
	int l=1,r=n;
	while(l<r)
	{
		int mid=l+r+1>>1;
		string qwq=getstring(a[mid].s,0,t.length());
		if(qwq==t)return mid;
		else if(qwq<t)l=mid+1;
		else r=mid-1;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)cin>>a[i].s,a[i].num=i;
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=m;i++)
	{
		cin>>k>>s;
		int point=erfen(s);
		int l,r;
		l=r=point;
		while(getstring(a[l-1].s,0,s.length())==s)l--;//左区间
		while(getstring(a[r+1].s,0,s.length())==s)r++;//右区间
		if(r-l+1<k)printf("-1\n");
		else printf("%d\n",a[l+k-1].num);
	}
	return 0;
}
```


---

## 作者：Hexarhy (赞：4)

## 不论怎样，能AC题目的都是好方法！

这道题目的做法可谓多种多样，性能也各不相同。

这里只讲一些简单的~~字典树什么的不会讲的看他人题解吧~~。

 _另外，这道题目评蓝题怕不是恶意评分评高了？_ 

------------

### 1.玄学暴力

就是排序之后，在遍历一遍字符串，遍历到第$k$个符合的就输出，否则遍历完没输出就$-1$。

**时间复杂度：$O(nw)$**（要加上substr()的复杂度~~大家自己算吧我不会~~）

显然暴力会超时，但开了O2就没有（玄学）。


O2前：![](https://cdn.luogu.com.cn/upload/pic/55379.png)

O2后：![](https://cdn.luogu.com.cn/upload/pic/55380.png)

程序简单易懂，注释不会太多：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
using namespace std;

const int MAXN=100005;
int w,n;
struct dictionary
{
	string st;
	int id;
	bool operator<(const dictionary& a)const
	{
		return st<a.st;
	}//相当于sort的cmp函数
}a[MAXN];
string s;
int k;

bool find(const string s)
{
	const int len=s.size();
	int t=0;
	for(register int i=1;i<=w;++i)//register优化常数
	{
		if(a[i].st.substr(0,len)==s)//很暴力了，通俗易懂
		 t++;
		if(t==k)//找到第k个就输出
		{
			printf("%d\n",a[i].id);
			return true;
		} 
	}
	printf("-1\n");//全部找完还没有就不存在
	return false;
}

void input(void)
{
	cin>>w>>n;
	for(int i=1;i<=w;i++)
	{
		a[i].id=i;
		cin>>a[i].st;
	}
	sort(a+1,a+1+w);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&k);
		cin>>s;
		find(s);
	}
}

int main()
{
	input();
	return 0;
}
```


------------

### 2.二分查找

既然遍历整个数组时间很不保险，那么自然而然会想到，都排序了，就二分吧。

**时间复杂度：$O(m\ logn)$**。绝对不会超时。

二分当然可以手打，注意区分上界下界就行。当然为了减少码量，使用`lower_bound()`。

如果对`lower_bound()`不熟的，特别是对于结构体，有几种方法。

**第一种**：再开一个string数组，方便我们二分，避开了结构体，注意这个string数组也要排序。

**第二种**：使用`pair<>`，因为它是默认优先级为第一关键字，因此我们就舍弃结构体，使用`pair<string,int>`。

**第三种**：硬要用结构体的话，那就**重载运算符**并写一个**构造函数**，因为`lower_bound(begin,end,key)`三个参数中的`key`是要跟数组一个类型的，并且进行比较。当然C++11可以参数列表初始化，避开构造函数。（此方法较为麻烦）

注意三种方法码量和运行内存都有比较大不同。

讲完了二分，那么该如何找第$k$个呢？

因为`lower_bound()`返回第一个大于等于值的特点，我们可以从直接往后移动$k$个并验证是否符合。不符合直接输出$-1$。

**方法1**用一个string数组的程序：
```cpp
#include<iostream>
#include<algorithm>
#include<string>
#include<cstdio>
using namespace std;

const int MAXN=30005;
int n,m;
struct dictionary
{
    string st;
    int id;
    bool operator<(const dictionary& a)const
    {
    	return st<a.st;
    }
}word[MAXN];
string tmp[MAXN];//就是word数组的st

void input(void)
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) 
    {
        cin>>word[i].st;
        tmp[i]=word[i].st;
        word[i].id=i;
    }
}

void binary(void)
{
    sort(word+1,word+1+n);
    sort(tmp+1,tmp+1+n);//别忘了两个都要排序
    for(int i=1;i<=m;i++)
    {
        int find_k;
        string find_st;
        scanf("%d",&find_k);
        cin>>find_st;
        const int j=lower_bound(tmp+1,tmp+1+n,find_st)-tmp;//二分找到第一个符合条件的
        if(word[j+find_k-1].st.substr(0,find_st.size())!=find_st)//直接跳到后面第k个，并用substr进行比较
         puts("-1");
        else
         printf("%d\n",word[j+find_k-1].id);
    }
}

int main()
{
    input();
    binary();
    return 0;
}
```

**方法2**用pair程序：
```cpp
#include<iostream>
#include<algorithm>
#include<string>
#include<cstdio>
using namespace std;

const int MAXN=30005;
int n,m;
pair<string,int>a[MAXN];//直接省去结构体

void input(void)
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) 
    {
        cin>>a[i].first;
        a[i].second=i;
    }
}

void binary(void)
{
    sort(a+1,a+1+n);//默认有限比较first
    for(int i=1;i<=m;i++)
    {
        int num;
        string key;
        cin>>num>>key;
        const int j=lower_bound(a+1,a+1+n,make_pair(key,0))-a;//make_pair让查找值与数组类型相同
        if(a[j+num-1].first.substr(0,key.size())!=key)//也是直接跳到后面第k个
         puts("-1");
        else
         printf("%d\n",a[j+num-1].second);
    }
}

int main()
{
    input();
    binary();
    return 0;
}
```

受篇幅影响，方法3的程序不再给出，毕竟只是一点点改动，可以上网百度。

 _注：码风不同是因为由机房好友提供的思路与程序，我只是小结。_ 

------------

下面几种方法的性能比较：
![](https://cdn.luogu.com.cn/upload/pic/55383.png)

码量、时间、运行内存什么的自己仔细看，附上[link](https://www.luogu.org/recordnew/lists?uid=80049&pid=2237&status=&sort=undefined)。

字典树的码量就不言而喻，时间也是很优秀的。

### 不论怎样，能AC题目的都是好方法！
 

---

## 作者：一只野生蒟蒻 (赞：2)

看到dalao们的各种二分、字典树算法，只会暴力的我只能躲在角落里瑟瑟发抖~

我在这里就提供一种不需要o2就可以AC的暴力算法

思路很简单，就是读入后排好序，然后预处理出以‘a’~‘z’每个字母开头的单词的起止序号（这是主要的优化手段），再对于每个询问串都遍历一遍，遍历到第k个就输出编号，没找到就输出-1。

下面直接上代码：
```
#include <bits/stdc++.h> 
using namespace std;
int w,n,k;
string s;
struct node
{
	int id,l,r;
	string st;
}a[30004];
inline int read()//快读 
{
	int f=1;
	char c;
	while ((c=getchar())<'0'||c>'9')
		if (c=='-') f=-1;
	int x=c-'0';
	while ((c=getchar())>='0'&&c<='9')
		x=x*10+c-'0';
	return x*f;
}
inline bool cmp(node x,node y)
{
	return x.st<y.st;
}
inline int f()
{
    int l=s.size(),t=0;
    for (int i=a[s[0]-'a'].l;i<=a[s[0]-'a'].r;i++)//直接从开始编号循环到结束编号 
    {
      	int j1=0,j2=0;
      	while (1)//逐个字符比较，应该比substr快（用substr在洛谷上可以过，其它OJ会超时）
      	{
      		if (j2==l)//如果是前缀就累加 
			{
				t++;
				break;	
			} 
      		if (a[i].st[j1]!=s[j2]) break;//当有一个字符不相同就可以退出 
      		j1++; j2++;
		}
		if (t>0&&j2<l) return -1;//虽然找到了相同前缀，但没有k个 
		if (t==k) return a[i].id;//如果有第k个 
    }
    return -1;
}
int main()
{
    w=read(); n=read();
    for (int i=1;i<=w;i++)
    {
        cin>>a[i].st;
        a[i].id=i;//记录编号 
    }
    sort(a+1,a+1+w,cmp);//排序 
    char bj='z'+1;
    a[w+1].st[0]='z'+1;//注意要到w+1，这样最后一个开头字母的结束序号才记得住
    for (int i=1;i<=w+1;i++)//记录每种字母开头的单词的起止序号 
    	if (bj!=a[i].st[0])
    	{
    		a[bj-'a'].r=i-1;
    		bj=a[i].st[0];
    		a[bj-'a'].l=i;
		}
  	for (int i=1;i<=n;i++) 
    {
        k=read();
        cin>>s;
        printf("%d\n",f());
        //查找询问串 
    }
    return 0;
}
```
最后吐槽一句，这题的数据是真的水，一开始用的substr在洛谷上过了，在别的OJ上T了不知道多少次（也许是我太弱了，不会用substr），最后才想到逐个字符比较，过了所有点。

---

## 作者：曹老师 (赞：2)

## Sol ##

[blog食用](http://www.caolaoshi.men/index.php/archives/usaco14feb-auto.html)

貌似有写贪心+二分的，我就偏写字典树。

对于每一个单词，都把它插入到字典树上，深搜一遍维护出每个结点的（包括）的子树中一共有多少个单词的结尾，根据你要找的单词的字典序的排名，就能确定出你要找的是字典树上的哪一个点，在插入的时候同时维护出该单词的序号，这样找到直接$O(1)$，还是很好打的，就是查询的时候一定要注意！

## Code ##

```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int L = 1000005;
short vis[L];
int n , m , tree[L][30] , tot = 0 , val[L] , size[L] , num[L];

void build(string s , int cnt) {
	int len = s.length() , now = 0;
	for(int i=0; i<len; i++) {
		int id = s[i] - 'a';
		if(!tree[now][id])
			tree[now][id] = ++tot;
		now = tree[now][id];
	}
	val[now] = -1;
	size[now] = 1;
	num[now] = cnt;
}

void dfs(int x) {
	vis[x] = 1;
	for(int i=0; i<26; i++)
		if(tree[x][i]) {
			dfs(tree[x][i]);
			size[x] += size[tree[x][i]];
		}
}

int find(int x , string s) {
	int len = s.length() , now = 0 , ans = 0;
	for(int i=0; i<len; i++) {
		int id = s[i] - 'a';
		if(!tree[now][id])
			return -1;
		now = tree[now][id];
	}
	if(size[now] < x)
		return -1;
	if(val[now] == -1)
		x--;
	for(int i=0; i<26; i++) {
		if(!x && val[now] == -1)
			return num[now];
		if(size[tree[now][i]] < x)
			x -= size[tree[now][i]];
		else {
			if(tree[now][i]) {
				now = tree[now][i];
				i = -1;
			if(val[now] == -1)
				x--;
			}
		}
	}
}

int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++) {
		string s;
		cin>>s;
		build(s , i);
	}
	for(int i=1; i<=tot; i++)
		if(!vis[i])
			dfs(i);
	for(int i=1; i<=m; i++) {
		int x;
		string s;
		cin>>x>>s;
		printf("%d\n",find(x , s));
	}
	return 0;
}
```


  [1]: http://usaco.org/index.php?page=viewproblem2&cpid=397
  [2]: https://www.luogu.org/problemnew/show/P2237
  [3]: https://www.lydsy.com/JudgeOnline/problem.php?id=3448

---

## 作者：羚羊WANG (赞：1)

相信大家看到这里的时候，都已经理解了题目意思

我们发现，如果先排一边序之后，所有前缀相同的串都会在一起

所以我们可以考虑先排一边序，这里要注意一下排序之前要记录一下编号

我们可以先用$lower-bound$求出第一个前缀为给定串

然后就可以加上给定的排名，最后判断前缀是否符合即可

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
pair<string,int> a[90100];
inline bool check(string x,string y){  //判断是否为前缀
	if(y.length()>x.length())
		return false;
	return x.substr(0,y.length())==y;
}
int w,n;
signed main(){
	w=read();
	n=read();
	for(register int i=0;i<w;++i)
		{
			cin>>a[i].first;
			a[i].second=i;
		}
	sort(a,a+w);
	while(n--)
		{
			string x;
			int k;
			k=read();
			cin>>x;
			int sum=k-1+lower_bound(a,a+w,make_pair(x,0))-a;//查找第一个前缀的位置
			if(sum>=w || !check(a[sum].first,x))	
				{
					write(-1);	
					puts("");
					continue;
				}
			write(a[sum].second+1);
			puts("");
		}
	return 0;
}

```


---

## 作者：RiverHamster (赞：1)

## 这题其实还有一种排序贪心做法


这道题和[P2969 Music Notes](https://www.luogu.org/problemnew/show/P2969)思路非常类似，只是操作的对象由`int`变成了`string`而已，用`std::string`完成还是很方便的。

贪心`O(n)` 排序`O(nlogn)` 总时间复杂度`O(n)`

参见楼下大佬思路，对于每个询问，只需要找到字典序最小与它匹配的单词，并且加k后检查，如果匹配就有解

考虑**对单词、询问进行排序**，并且记录原来的顺序`id`(方便还原询问顺序输出和查询单词原序），此时就可以开**双指针贪心**了，代码基本就**普及+难度**

*贪心思路*：两个指针一个记录单词的位置，一个记录询问的位置，上份伪代码

```
if(单词 匹配 询问):
	检查+k后的匹配:
    	答案为[单词+k].id -> 当匹配时
        答案为-1         -> 当不匹配时
else if(单词>询问) 询问++
else 单词++
```

完整cpp代码：
```cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
bool Pre(string &s,string &pre){ //检查是否为前缀
	if(pre.size()>s.size()) return false;
	return pre==s.substr(0,pre.size());
}
struct Word{ //单词和id
	string s;
	int id;
}a[100005];
struct Query{ //询问的字符串，id，查到的答案和k值
	string s;
	int id,val,jmp;
}q[5005];
template<class T> bool cmps(T a,T b){return a.s<b.s;} //按字符串排序
template<class T> bool cmpid(T a,T b){return a.id<b.id;} //还原id原序
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i].s,a[i].id=i;
	sort(a+1,a+1+n,cmps<Word>);
	for(int i=1;i<=m;i++) cin>>q[i].jmp>>q[i].s,q[i].id=i;
	sort(q+1,q+1+m,cmps<Query>); //分别排序
	int pa=1,pq=1; //双指针
	while(pa<=n&&pq<=m){
		if(Pre(a[pa].s,q[pq].s)){ //如果匹配了
			if(Pre(a[pa+q[pq].jmp-1].s,q[pq].s)) q[pq].val=a[pa+q[pq].jmp-1].id; //检查+k后的匹配，注意k-1，成功就记录答案
			else q[pq].val=-1; //匹配不成功
			pq++; //下一个关键字
		}
		else if(a[pa].s>q[pq].s) pq++; //当前单词已经比要查的关键字大了，关键字++
		else pa++; //单词比关键字小，单词++
	}
	while(pq<=m) q[pq].val=-1; //没找到的关键字都是误解
	sort(q+1,q+1+m,cmpid<Query>); //还原询问顺序
	for(int i=1;i<=m;i++) cout<<q[i].val<<endl;
	return 0;
} 
```

---

## 作者：Sooke (赞：1)

## 这是一道练习 二分 的好题

可以发现以 字符串 t 为前缀的 字符串 s 必定 大于或**等于** 字符串 t，并且 字符串 s 比 字符串 t 加上 字符 '|' （一个比 'z' 要大的字符，凡是比 'z' 大可以任意制定）。因此，我们只要给 所有单词字符串 带上编号 以字典序 进行排序，用二分找出第一个满足条件的字符串的位置，再用二分找出最后一个满足条件的字符串的位置，里面一段区间的字符串都是符合条件的。找到第 k 个并且输出其编号或者 -1 便可以轻松解决一个询问。

本题比较难理解的 二分判断 应该用 大于 还是 大于等于。找 第一次 出现的应该用 大于，找 最后一次 出现的应该用 大于等于，如果加上等号可以排除 字符串 s 等于 前缀字符串 t 的情况，可自行思考。

楼下用了 STL 的 二分查找函数 %%%，那么本人还是手打便于大家观看并理解。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

struct stc{
    string s;
    int n;
}s[30001]; // 定义 单词字符串 结构体，s 为字符串，n 为编号

bool Cmp(stc x , stc y){
    return x.s < y.s;    
}

string t;
int p , n , k , l , r , m , resl , resr;

int main(){
    cin >> p >> n;
    for(int i = 1 ; i <= p ; i++)
        cin >> s[i].s , s[i].n = i;
    sort(s + 1 , s + p + 1 , Cmp); // 给 单词字符串 进行排序
    for(int i = 1 ; i <= n ; i++){
        cin >> k >> t;
        resl = 0 , resr = 0;
        l = 0 , r = p; // 保留 前缀 t，便于找出左边界。
        while(l <= r){
            m = (l + r) >> 1;
            if(t > s[m].s)
                l = m + 1 , resl = m;
            else
                r = m - 1;
        }
        l = 0 , r = p ; t = t + '|'; // 给 t 加上一个较大的字符，便于找出右边界。
        while(l <= r){
            m = (l + r) >> 1;
            if(t >= s[m].s)
                l = m + 1 , resr = m;
            else
                r = m - 1;
        }
        if(resl + k > resr)
            cout << -1 << endl;
        else
            cout << s[resl + k].n << endl; // 两次二分后获得可用字符串的区间，输出区间内 第 k 个的编号
    }
    return 0;
}
```

---

## 作者：UperFicial (赞：0)

$100$ 蓝，写篇题解纪念。

发现楼下均用的 $\text{lower\_bound}$ 啥的，这里考虑字典树，因为发现题目要求维护前缀的信息。

对每个字符串在 $\text{Trie}$ 中的终止节点打上标记，记录是原串的第几个。相应的求出每个子树的 $siz$，$siz_u$ 表示在以 $u$ 为根节点的子树内有多少标记。

对于查询，如果 $s$ 不在这棵 $\text{Trie}$ 上，直接输出 `-1`。

否则对于它的终止节点，找到哪棵子树里存在答案，方法是不断用 $k$ 减去 $siz$ 即可。

如此循环下去直到 $k$ 为 $0$ 并且找到一个打过标记的节点，这道题就做完了。

---

## 作者：Zenith_Yeh (赞：0)

首先我们将这些字符串按字典序排序，由于 $A$ 串是 $B$ 串的前缀的前提是 $B$ 的字典序大于 $A$ 的字典序。所以说我们排好序后，用神奇的 $STL$ 函数 $lower\_bound$ 二分查找即可。

**上菜：**

```
#include<bits/stdc++.h>
inline int read()
{	int x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c))f|=(c=='-'),c=getchar();
	while(isdigit(c))x=x*10+(c&15),c=getchar();
	return f?-x:x;
}
using namespace std;
struct bb
{	int id;
	string ss;
}s[1000005];
int w,n,l,r,L,R;
string mb;
inline bool cmp(bb a,bb b)//排序函数
{	return a.ss<b.ss;
}
inline bool pd(int x)//判断是否是前缀
{	if(s[x].ss.size()<mb.size())return 0;
	for(register int i=0;i<mb.size();++i)
		if(s[x].ss[i]!=mb[i])return 0;
	return 1;
}
int main()
{   w=read(),n=read();
	for(register int i=1;i<=w;++i)cin>>s[i].ss,s[i].id=i;
	sort(s+1,s+w+1,cmp);
	for(register int i=1;i<=n;++i)
	{	int num=read();
		cin>>mb;
		bb tmp;
		tmp.ss=mb;
		tmp.id=0;
		l=lower_bound(s+1,s+w+1,tmp,cmp)-s;
		if(pd(l+num-1))cout<<s[l+num-1].id<<endl;
		else cout<<-1<<endl;
	}
	return 0;
}
```


---

## 作者：qhy_ (赞：0)

### 思路
- 首先把字典排序，这样如果有相同的前缀会被排在一起。
- 然后找出前缀第一次出现的位置
- 最后找出如果存在目标的位置，再看看是否存在。
---
### $code$

```cpp
#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;

const int kMaxN = 1e6 + 1;

struct Q {  // 询问
  string s;
  int k, a;
} q[kMaxN];
string d[kMaxN];           // 字典
int dl[kMaxN], ql[kMaxN];  // 编号排序
int w, n;

int main() {
  cin >> w >> n;
  for (int i = 1; i <= w; i++) {
    cin >> d[i];
    dl[i] = i;  // 初始化编号
  }
  for (int i = 1; i <= n; i++) {
    cin >> q[i].k >> q[i].s;
    ql[i] = i;  // 初始化编号
  }
  // 字典序排序
  sort(dl + 1, dl + 1 + w, [](int i, int j) { return d[i] < d[j]; });
  sort(ql + 1, ql + 1 + n, [](int i, int j) { return q[i].s < q[j].s; });
  for (int i = 1, j = 1; i <= n; i++) {             // 枚举每个询问
    for (; j <= w && d[dl[j]] < q[ql[i]].s; j++) {  // 维护在字典中的位置
    }
    int k = j + q[ql[i]].k - 1;  // 答案的位置
    // 校验答案合法
    q[ql[i]].a = k > w || d[dl[k]].compare(0, q[ql[i]].s.length(), q[ql[i]].s) ? -1 : dl[k];
  }
  for (int i = 1; i <= n; i++) {
    cout << q[i].a << endl;
  }
  return 0;
}
```


---

## 作者：Great_Influence (赞：0)

字典树。

trie这么有用，为什么不用呢？(雾

基本就是模板了。时间复杂度$O(q|s|)$（|s|为答案串长）。空间有保证在1e6内。

代码：

```cpp
#include <bits/stdc++.h>
#define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
#define For(i, l, r) for(int i = (l), _end_ = (int)(r); i <= _end_; ++i)
#define Forward(i, r, l) for(int i = (r), _end_ = (int)(l); i >= _end_; --i)
#define Set(a, v) memset(a, v, sizeof(a))
using namespace std;

#define Chkmax(a,b) a=a>b?a:b
#define Chkmin(a,b) a=a<b?a:b
template<typename T>inline void read(T &x) {
	x=0;T fh=1;char ch=getchar();
    for (; !isdigit(ch); ch = getchar() ) if (ch == '-') fh = -1;
    for (; isdigit(ch); ch = getchar() ) x = (x<<1) + (x<<3) + (ch ^ '0');
    x*=fh;
}
inline void file()
{
#ifndef ONLINE_JUDGE
	freopen("2237.in","r",stdin);
	freopen("2237.out","w",stdout);
#endif
}
static int n,m;
const int MAXN=1e6+7;
static char s[MAXN];
static struct trie
{
	int nxt[30],ed,cnt;
}p[MAXN];
static int e=1;
inline void insert(char *q,int x)
{
	static int now;now=1;
	Rep(i,0,strlen(q)-1)
	{
		++p[now].cnt;
		if(!p[now].nxt[q[i]-'a'])p[now].nxt[q[i]-'a']=++e;
		now=p[now].nxt[q[i]-'a'];
	}++p[now].cnt;
	p[now].ed=x;
	//cerr<<p[now].ed<<' '<<now<<endl;
}
inline void init()
{
	read(n);read(m);
	Rep(i,1,n)scanf("%s",s),insert(s,i);
}
inline int query(char *q,int k)
{
	static int now;now=1;
	Rep(i,0,strlen(q)-1)
	{
		if(!p[now].nxt[q[i]-'a'])return -1;
		now=p[now].nxt[q[i]-'a'];
	}
	static int tt;
	while(k)
	{
		if(p[now].ed)--k;
		if(!k)break;
		//cerr<<k<<' '<<now<<' '<<p[now].ed<<endl;
		tt=now;
		Rep(i,0,25)
		{
			if(p[now].nxt[i]&&k<=p[p[now].nxt[i]].cnt){now=p[now].nxt[i];break;}
			else k-=p[p[now].nxt[i]].cnt;
		}
		if(now==tt)break;
		//cerr<<k<<' '<<now<<' '<<p[now].ed<<endl;
	}
	//cerr<<now<<' '<<p[now].ed<<endl;
	if(!now||k>0)return -1;
	else while(!p[now].ed)
	{
		Rep(i,0,25)if(p[now].nxt[i]){now=p[now].nxt[i];break;}
	}
	return p[now].ed;
}
inline void solve()
{
	static int k;
	Rep(i,1,m)
	{
		read(k);scanf("%s",s);
		printf("%d\n",query(s,k));
	}
}
int main () {
	file();
	init();
	solve();
    return 0;
}
```

---

