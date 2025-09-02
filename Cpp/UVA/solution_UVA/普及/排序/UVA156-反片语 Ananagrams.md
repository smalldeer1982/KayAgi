# 反片语 Ananagrams

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=92

[PDF](https://uva.onlinejudge.org/external/1/p156.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA156/dc6cdcbb36579acf2629ae204167ab408bdaa20f.png)

## 样例 #1

### 输入

```
ladder came tape soon leader acme RIDE lone Dreis peat
ScAlE orb eye Rides dealer NotE derail LaCeS drIed
noel dire Disk mace Rob dries
#```

### 输出

```
Disk
NotE
derail
drIed
eye
ladder
soon```

# 题解

## 作者：sss7020 (赞：19)

刘汝佳大佬的代码（源于紫书），由于代码注释不多，所以吾只是来添加注释的。

```cpp
#include<iostream>
#include<map>
#include<cctype>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
map<string,int>cnt;//这里的string是单词，int是出现了几次。
vector<string>words;//把所有单词全部压入动态数组
string repr(const string& s){
	string ans=s;//由于是&（不引用还要再复制一个），所以不能随意乱改字符串（尤其是const）
	for(int i=0;i<ans.length();i++){
		ans[i]=tolower(ans[i]);//把大写字母变成小写字母
	}
	sort(ans.begin(),ans.end());//快速排序
	return ans;
}//此函数将单词标准化，全部转成小写字母再排序。
int main(){
	int n=0;
	string s;
	while(cin>>s){
		if(s[0]=='#')break;//函数跳出条件
		words.push_back(s);//储存单词
		string r=repr(s);
		if(!cnt.count(r))cnt[r]=0;
        //如果这个单词还没有出现过，就把个数存为0
		cnt[r]++;//不管怎样都要将数值加1
	}//本循环将原单词存入words中，把标准化的单词存入cnt中
	vector<string>ans;//答案
	for(int i=0;i<words.size();i++){
		if(cnt[repr(words[i])]==1)ans.push_back(words[i]);
	}//本循环将只出现一次的标准化单词存入ans中
	sort(ans.begin(),ans.end());//快速排序
	for(int i=0;i<ans.size();i++){
		cout<<ans[i]<<endl;
	}
	return 0;
} 
```
程序将单词标准化，并且存入map中，实在是太妙了！

---

## 作者：WanderingTrader (赞：4)

看到这道题的人，多半是紫书的读者吧。  
方法很多，这里介绍两种。
### 解法一：标准化(by 刘汝佳)
输入字符串后，把字符全部转成小写，然后排序，这样符合条件的字符串(比如zyx和XYZ)就会得到同样的串了。
```cpp
string repr(const string& s){
	string ans = s;
	for(int i = 0;i < ans.length();i++)
		ans[i] = tolower(ans[i]);
	sort(ans.begin(),ans.end());
	return ans;
}
```
用一个map来保存处理后的字符串出现的次数，当然也要用一个vector来放输入的字符串。
```cpp
#include<iostream>
#include<map>
#include<cctype>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
map<string,int> cnt;
vector<string> words;
string repr(const string& s){
	string ans = s;
	for(int i = 0;i < ans.length();i++)
		ans[i] = tolower(ans[i]);
	sort(ans.begin(),ans.end());
	return ans;
}
int main(){
	int n = 0;
	string s;
	while(cin >> s){
		if(s[0] == '#')break;
		words.push_back(s);
		string r = repr(s);
		if(!cnt.count(r))cnt[r] = 0;
		cnt[r] ++;
	}
} 
```
再开一个vector存放答案，如果一个串处理后只出现了一次，那就放入这个vector。  
最后给它排序输出即可。  
```cpp
vector<string> ans;
for(int i = 0;i < words.size();i++)
	if(cnt[repr(words[i])] == 1)ans.push_back(words[i]);
sort(ans.begin(),ans.end());
for(int i = 0;i < ans.size();i++)
	cout << ans[i] << endl;
```
全部代码：
```cpp
#include<iostream>
#include<map>
#include<cctype>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
map<string,int> cnt;
vector<string> words;
string repr(const string& s){
	string ans = s;
	for(int i = 0;i < ans.length();i++)
		ans[i] = tolower(ans[i]);
	sort(ans.begin(),ans.end());
	return ans;
}
int main(){
	int n = 0;
	string s;
	while(cin >> s){
		if(s[0] == '#')break;
		words.push_back(s);
		string r = repr(s);
		if(!cnt.count(r))cnt[r] = 0;
		cnt[r] ++;
	}
	vector<string> ans;
	for(int i = 0;i < words.size();i++)
		if(cnt[repr(words[i])] == 1)ans.push_back(words[i]);
	sort(ans.begin(),ans.end());
	for(int i = 0;i < ans.size();i++)
		cout << ans[i] << endl;
	return 0;
} 
```
这份代码的巧妙之处就在于将字符串排序这一操作，不得不佩服刘汝佳老师的智慧。  
### 解法2：哈希(by zycany)
如果你不知道什么是哈希，那么下面的介绍说不定可以帮到你。 

---
例：输入两个个字符串$a,b$，求$b$在$a$中出现了几次。$(1\le |b|\le|a|\le10^6)$（kkcoding第175题：字符串匹配）  
如果暴力枚举判相等，$O(|a|\times|b|)$肯定超时。  
我们可以采用哈希算法，即将字符串通过某种特定的公式转换成一个整数，然后通过整数判相等来求解。  
定义一个 $\mathrm{BASE}$ 表示基准值（通常采用超过100的质数，如311），那么字符串$S$的哈希值即为：
$$
\sum\limits_{i=1}^{|S|}S[i]\times \mathrm{BASE}^i
$$
这样就可以高效的求出答案了。  
大家可以自行尝试写出代码，提交在kk上。  
也许有人会问：万一哈希值冲突了怎么办？  
要知道，这种按进制位生成的哈希值，是基本不可能冲突的。就算出题老师想故意造数据来卡你的哈希，他也非常困难，因为他连你取的BASE都不知道是几。所以冲突问题不必担心。  

---
下面言归正传，如何运用哈希来解决本题？  
很简单了。把a~z映射成$1$至$\mathrm{BASE}^{25}$存入数组H，然后也不用按进制了，直接求
$$
\sum\limits_{i=1}^{|S|}H[tolower(S[i])-‘a’]
$$
即可。  
```cpp
ull Hash(const string& str)
{
	string s = str;
	ull ans = 0;
	int len = str.length();
	for(int i = 0;i < len;++ i)
	{
		s[i]=tolower(s[i])-'a';
		ans += H[s[i]];
	}
	return ans;
}
```
又有一个问题。如果ull溢出了怎么办？  
其实溢出就溢出呗，溢出后从0开始，没什么关系。  
那么我们用一个map来储存一个哈希值对应的字符串，以及这个哈希值已经出现了几次。记录一下即可。  
```cpp
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
#define BASE 311
#define ull unsigned long long
#define p pair<string,int>
map <ull,p> m;
vector <string> ans;
ull H[30]={1};
ull Hash(const string& str)
{
	string s = str;
	ull ans = 0;
	int len = str.length();
	for(int i = 0;i < len;++ i)
	{
		s[i]=tolower(s[i])-'a';
		ans += H[s[i]];
	}
	return ans;
}
int main()
{
	string str;
	for(int i = 1;i < 26;++i)
		H[i] = BASE*H[i-1];
	while(cin >> str && str != "#")
	{
		ull x = Hash(str);
		if(!m[x].second) 
			m[x].first = str;
		++m[x].second;
	}
	return 0;
}
```
别忘了把H[0]设成1，否则整个进制位都是0，哈希法失效。  
然后遍历整个map，如果某个哈希值只出现了一次，那么就把它对应的字符串放入一个vector，最后对vector进行排序，输出。  
```cpp
map <ull,p> ::iterator it;
for(it=m.begin();it != m.end();++it)
	if(it->second.second == 1)
		ans.push_back(it->second.first);
sort(ans.begin(),ans.end());
for(int i = 0;i < ans.size();++i)
	cout << ans[i] << endl;
```
全部代码：
```cpp
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
#define BASE 311
#define ull unsigned long long
#define p pair<string,int>
map <ull,p> m;
vector <string> ans;
ull H[30]={1};
ull Hash(const string& str)
{
	string s = str;
	ull ans = 0;
	int len = str.length();
	for(int i = 0;i < len;++ i)
	{
		s[i]=tolower(s[i])-'a';
		ans += H[s[i]];
	}
	return ans;
}
int main()
{
	string str;
	for(int i = 1;i < 26;++i)
		H[i] = BASE*H[i-1];
	while(cin >> str && str != "#")
	{
		ull x = Hash(str);
		if(!m[x].second) 
			m[x].first = str;
		++m[x].second;
	}
	map <ull,p> ::iterator it;
	for(it=m.begin();it != m.end();++it)
		if(it->second.second == 1)
			ans.push_back(it->second.first);
	sort(ans.begin(),ans.end());
	for(int i = 0;i < ans.size();++i)
		cout << ans[i] << endl;
	return 0;
}
```
比刘汝佳老师的代码长了一些，但还是相当高效的。很多字符串问题都可以通过哈希算法来加速。  

$\mathrm{The\ End.}$

---

## 作者：L_Y_T (赞：4)

### 这道题我没有用map也没用数据结构,开了一个结构体记录了原串和排序之后的串,然后按照排序后的拍一遍序即可

下面放个代码,相信大家都可以看懂

```cpp
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#define maxn 1100
using namespace std ;
string ans[maxn] ;
string s ;
int cnt , num ;
bool state[maxn] ;
struct dy{
	string ss ;
	string st ;
	bool state ;
}t[maxn] ;
int cmp(dy x , dy y) {
	return x.st < y.st ;
}
int tt ;
int main() {
	cin >> s ;
	while(s != "#") {
		data.push_back(s) ;
		string op = "";
		for(int i = 0 ; i < s.size() ; i ++) {
		 	if(s[i] >= 'A' && s[i] <= 'Z') {
				op += s[i] + 32 ;
			}else op += s[i] ;
		}sort(op.begin(),op.end()) ;
		t[++tt].ss = s ;
		t[tt].st = op ;
		cin >> s ;
	}
	sort(t+1,t+1+tt,cmp) ;
	for(int i = 1 ; i <= tt ; i ++){
		if(t[i].st == t[i+1].st) {
			t[i].state = 1 ;
			t[i+1].state = 1 ;
		}
	}int hah = 0 ;
	for(int i = 1 ; i <= tt ; i ++) {
		if(!t[i].state) ans[++hah] = t[i].ss ;
	} 
	sort(ans+1,ans+1+hah) ;
	//cout << hah << endl ; 
	for(int i = 1 ; i <= hah ; i ++) {
		cout << ans[i] <<endl ;
	}
	return 0 ;
}
```
至于如何排序,当然是按照小写的字典序辣!

____
#### 这道题的代码我调试了一辈子.....

看了看题解们,好像我的做法十分的冗杂但是**十分的好想好调**~~(但我还是调试了半天)~~ ;

闲话不多说,上代码

>主要思路是这样的:因为他会忽略大小写进行排序重组,所以我们不妨把他们全部换成大写或者小写进行一个从大到小或者从小到大的排序,然后在扫一遍找出顺序只有一个的,进行排序输出

```cpp
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#define maxn 1100
using namespace std ;
vector<string>data ;//记录原数据
map<string,int>vis ;//用来记录当前状态共有几个
vector<string>ans ;//记录答案
string s ;
int cnt , num ;
bool state[maxn] ;//事实证明没什么用
int main() {
	cin >> s ;
	while(s != "#") {//如果不是结束的标志
		data.push_back(s) ;//有效数据,加入
		string op = "";
		for(int i = 0 ; i < s.size() ; i ++) {//把大写转为小写
		 	if(s[i] >= 'A' && s[i] <= 'Z') {
				op += s[i] + 32 ;
			}else op += s[i] ;
		}sort(op.begin(),op.end()) ;
		if(vis[op]) state[cnt] = 1 ;//没用
		vis[op] ++ ;//当前状态++
		cnt ++ ;//记录数据个数(事实证明data.size()效果更好)
		cin >> s ;
	}
	for(int i = 0 ; i < cnt ; i ++) {
		if(!state[i]) {
			string op = "";
			for(int j = 0 ; j < data[i].size() ; j ++) {//再进行一次大写转小写
		 		if(data[i][j] >= 'A' && data[i][j] <= 'Z') {
					op += data[i][j] + 32 ;
				}else op += data[i][j] ;
			}sort(op.begin(),op.end()) ;
			if(vis[op] == 1) ans.push_back(data[i]) ;//如果改状态只出现了一次,那么就加入答案数组
		}
	}
	sort(ans.begin() , ans.end()) ;//小排序
	for(int i = 0 ; i < ans.size() ; i ++) {输出
		cout << ans[i] << endl ;
	}
	return 0 ;
}
```

---

## 作者：凛凛LinLin (赞：2)

分析题目：

1.字母重排  sort

2.不能和文本另一个单词重复  先读入全部单词

3.不分大小写  tolower/toupper

4.字典序排列  set/sort

分析完毕


```cpp
#include <set>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

string stolow(string s) {                 //将一个字符串都转为小写的函数
    string s1;
    for (size_t i = 0; i < s.length(); i++) s1 += tolower(s[i]);
    return s1;
}

int main() {
    int len = 0;
    string s;
    string ss[999];
    string tmp[999];
    set <string> sss;
    
    while (cin >> s && s != "#") ss[len++] = s;     //读入全部单词
    
    for (int i = 0; i < len; i++) {
    	tmp[i] = stolow(ss[i]);
        sort(tmp[i].begin(),tmp[i].end());          //将全部字母转为小写，并把每个单词排序
    } 
    
    for (int i = 0; i < len; i++)
    	if (count(tmp, tmp + len, tmp[i]) == 1)     
        	sss.insert(ss[i]);         //若一个单词出现一次以上，则说明该单词字母重排之后得到了文本中的另一个单词
            
    for (auto x : sss) cout << x << endl;           //基于范围的for循环，遍历set容器，输出答案
    
    return 0;
}

```



---

## 作者：warzone (赞：2)

楼上都用stl啊...蒟蒻不才，自己写的数据结构
1. 要求存起来，按字典序输出，很容易想到字典树，这里要注意是先看大小写，再看字母表中的顺序
1. 去掉字母重排相同的。由于怎样排都可以，所以只要记个数，但也不要傻傻地一个一个看也建一个树，将个数与对应的单词连边即可，连两个及以上的边便重复，去掉
1. 最后输出，依序遍历就行，与个数连了一条边的便是单词，注意根节点不要输出
### 上代码——

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
char c,s[81];
struct point{
	point *next[81],*leave;
}hword,hnum,*p,*q;
inline void down(short c){
	if(p->next[c]==NULL){//建树
		p->next[c]=new point;
		for(register short i=0;i<81;i++) p->next[c]->next[i]=NULL;
		p->next[c]->leave=NULL;
	}
	p=p->next[c];//下行
}
inline void out(point *p,short step){
	if(p->leave!=NULL){
		for(register short i=0;i<step;i++){
			if(s[i]<26)putchar(s[i]+'A');
			else putchar(s[i]-26+'a');
		}//输出（大小写分开）
		if(step!=0)putchar('\n');//不输出根节点
	}
	for(s[step]=0;s[step]<52;s[step]++){
    	//下行的同时存好输出
		if(p->next[s[step]]!=NULL)		
        	out(p->next[s[step]],step+1);
	}
}
int main(){
	hword.leave=NULL;
	hnum.leave=NULL;
	for(register short i=0;i<81;i++){
		hword.next[i]=NULL;
		hnum.next[i]=NULL;
	}
	p=&hword;
    //初始化
	do{
		c=getchar();
		if('A'<=c&&c<='Z'){//大小写分开
			c-='A';
			s[c]++;
			down(c);
		}
		else if('a'<=c&&c<='z'){
			c-='a';
			s[c]++;
			down(c+26);
		}
		else{
			q=p;
			p=&hnum;
			for(short i=0;i<26;i++)down(s[i]);//个数建树
			if(p->leave!=&hword){
            	//即重复的单词的个数地址，勿喷
				if(p->leave==NULL){//连边
					p->leave=q;
					q->leave=p;
				}
				else{//重复单词
					p->leave->leave=NULL;
                    //将单词从字典树上删除
					p->leave=&hword;//同时个数树记录为重复
				}
			}
			p=&hword;
			memset(s,0,80);
            //归0
		}
	}while(c!='#');
	out(&hword,0);
	return 0;
}
```

---

## 作者：Suiseiseki (赞：2)

注意本题的一句话

**通过字母重排**

但我们肯定不会真的重排，太浪费时间。

我们把每一个单词按照字母字典序（或任何你指定的顺序）排序，用map统计一下，输出时先将所有单词按字典序排序，然后再判断，可以轻松的解决这题。

下面看代码吧：
```cpp
#include <cstdio>
#include <map>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
map<string,int> mp;//map映射
char s[25];
string word[1005];
int main(){
	string now;
	cin>>now;
	int len=0;
	while(now!="#"){
		for(int i=0;i<now.size();i++){
			s[i]=now[i];
			if(s[i]>='a'&&s[i]<='z'){
				s[i]=s[i]-'a'+'A';
			}
		}
		word[++len]=now;
		sort(s,s+now.size());
		now="";
		for(int i=0;i<word[len].size();i++){
			now+=s[i];
		}
		if(mp.count(now)==0){
			mp.insert(pair<string,int>(now,0));
		}//单词字典序排序
		mp[now]++;
		cin>>now;
	}
	sort(word+1,word+1+len);
	for(int i=1;i<=len;i++){
		now=word[i];
		for(int j=0;j<now.size();j++){
			s[j]=now[j];
			if(s[j]>='a'&&s[j]<='z'){
				s[j]=s[j]-'a'+'A';
			}
		}
		sort(s,s+now.size());
		now="";
		for(int j=0;j<word[i].size();j++){
			now+=s[j];
		}
		if(mp[now]==1){//如果只有它一个，那么就输出
			cout<<word[i]<<endl;
		}
	}
	return 0;
} 

```
其实可以在mao里面用迭代器遍历，再一个个查找，但复杂度差不多，这里就不放代码了（~~其实是我没写~~）

---

## 作者：封禁用户 (赞：1)

用$\text{while}$读入每个字符串，先把字符串的每个字符都转成小写，再排序。建一个结构体，存入原字符串和现字符串，把现字符串存到$\text{map}$中统计。读入完毕后建一个优先队列，遍历结构体，如果一个结构体中的排过序后的字符串再$\text{map}$中只统计过一次，那么把它的原字符串存入队列。最后挨个从队列中输出每一个字符串。

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	string now,ss;
}
a[100005];
string s;
int n;
priority_queue<string,vector<string>,greater<string> >q;
map<string,int>asdf;
int main()
{
	while(cin>>s)
	{
		if(s=="#")
			break;
		string s1=s;//s1为原字符串
		for(int i=0;i<s.length();i++)
			s[i]=tolower(s[i]);//转小写
		sort(s.begin(),s.end());//排序
		a[++n].ss=s1;
		a[n].now=s;//存入结构体
		asdf[s]++;//放入map种统计
	}
	for(int i=1;i<=n;i++)
	{
		if(asdf[a[i].now]==1)//只有过一次
			q.push(a[i].ss);//插入优先队列
	}
	while(!q.empty())
	{
		cout<<q.top()<<endl;
		q.pop();
	}
	return 0;
}
```

---

## 作者：PandaChang (赞：1)

自认为稍微比紫书代码好理解一些，可能有点慢，但对我这样的蒟蒻友好很多。
和紫书比较大的区别主要在我用map对应的是标准化字符串和输入的字符串
```cpp
//Uva 156 
#include<iostream>
#include<map>
#include<string>
#include<algorithm>
using namespace std;
string dc[1010];

void zh(string& znow)	//将字符串标准化 
{
	int len=znow.size();
	for(int i=0;i<len;i++)
	{
		if(znow[i]<='Z'&&znow[i]>='A') 
			znow[i]+=32;
	} 
	sort(znow.begin(),znow.end());
}

int main()
{
	map<string,string>smap;		//将字符串映射到标准化的字符串 
	string now;
	cin>>now;
	while(now!="#")
	{
		string znow=now;
		zh(znow);
		if(smap.count(znow)==0)		//map里没有标准化字符串，添加 
		{
			smap[znow]=now;
		}
		else		//map里已有标准化字符串，删除（变为*） 
		{
			smap[znow]="*";		
		}
		cin>>now;
	}
	
	int a=0;	
	map<string,string>::iterator iter;
	for(iter=smap.begin();iter!=smap.end();iter++)
	{
		if(iter->second!="*")	//只出现过一次的标准化字符串 
			dc[a++]=iter->second;		 
	}
	
	sort(dc,dc+a);		//排序 
	for(int j=0;j<a;j++)
			cout<<dc[j]<<endl;
	return 0;
}
```

---

## 作者：李至擎 (赞：0)

[点我看题](https://www.luogu.com.cn/problem/UVA156)

思路：可以将所有的输入存一份小写形式（大写形式也可以），然后将其按字母表顺序排序、标记。最后只需要依次判断是否出现过不止一次即可。

方法（以输入一个字符串为例）：

- $1.$ 输入字符串；

- $2.$ 把输入的字符串转换一份统一形式（要保留原串）；

- $3.$ 将其按字母表顺序进行排序；

- $4.$ 给排序后的字符串打上标记；

细节：

- 在执行二至四步操作时，是对转换成统一形式后的字符串进行操作，但同时也要保留原串。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
map<string,int>vis;//vis用来打标记 
vector<string>W,ans,W1;//W是输入的原串，ans是符合条件的答案串，W1是原串的统一形式 
string w;//w是输入时的临时字符串 
string f(string s)//f函数是统一转换成小写的函数 
{
	string S=s;//S是要进行处理的字符串 
	for(int i=0;i<S.size();i++)
	{
		if(S[i]>='A'&&S[i]<='Z')//如果是大写 
		{
			S[i]=S[i]-'A'+'a';//转成小写 
		}
	}
	sort(S.begin(),S.end());//按字典序排序 
	return S;//返回答案 
}
int main()
{
	while(cin>>w&&w!="#")//如果读到#，就结束读入 
	{
		W.push_back(w);//压入vector 
		string p=f(w);//p用来存转换后的字符串 
		W1.push_back(p);//压入vector  
		vis[p]++;//打上标记 
	}
	for(int i=0;i<W.size();i++)
	{
		if(vis[W1[i]]==1)//如果只出现过一次 
		{
			ans.push_back(W[i]);//压入答案
		}
	}
	sort(ans.begin(),ans.end());//按字典序排序  
	for(int i=0;i<ans.size();i++)//输出答案 
	{
		cout<<ans[i]<<endl;
	}
    return 0;//结束程序 
}
```

---

## 作者：d0j1a_1701 (赞：0)

奇妙的方法
使用一个map和一个multimap
先使用multimap存下所有排序后相同的字符串
遍历multimap，如果当前这个排序后序列只有一个对应的原字符串，将它的原序列加入另一个map桶排输出

```cpp
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;
typedef multimap<string,string>::iterator miter;
string buf;
map<string,string> b2a;
multimap<string,string> a2b;
int main(){
	while(cin>>buf&&buf!="#"){
		string backup = buf;
		for(int i=0;i<buf.size();i++){
			buf[i] = tolower(buf[i]);
		}
		sort(buf.begin(),buf.end());
		a2b.insert(make_pair(buf,backup));
	}
	for(miter iter=a2b.begin();iter!=a2b.end();){
		pair<miter,miter> er = a2b.equal_range(iter->first);
		if(distance(er.first,er.second)==1)
			b2a[iter->second] = iter->first;
		iter = er.second;
	}
	for(map<string,string>::iterator iter=b2a.begin();iter!=b2a.end();iter++){
		cout << iter->first << endl;
	}
	return 0;
}
```


---

## 作者：AveMarina (赞：0)

## 提供一个Trie树的题解
因为我想~~水~~写一篇题解但是却没有UVa账号所以特意跑去注册了一个 ~~，结果发现你谷并不能很好的绑定账号所以~~ 这个题我是直接在UVa上交的

![AC记录](![](https://cdn.luogu.com.cn/upload/image_hosting/lqyb4npq.png))

~~第一个WA是因为没打最后一个换号~~

# 正题
## map解
话说昨天看紫书的时候正好看到了这个题，~~当初连去重都不会的我看了还是很震惊的~~，我的做法和紫书里的类型，只不过省去了第二次排序，因为题解里有很多大佬都是类似的思路所以这里就不再赘述了。
```cpp
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

// 紫书上给出了一种排序两次的做法，这里把排序后的字符串和排序前的字符串对应起来了
// 免去了一次排序...

// 另外这个题应该可以用Trie树做，我认为这是好的，没有任何坏处 

map<string, int > mp;
map<string, string > pm;
vector<string > vec, res;
string solve(string str) {
	int sLen = str.size();
	for (int i = 0; i < sLen; i++) str[i] = tolower(str[i]);
	sort(str.begin(), str.end());
	return str;
}
int main() {
	string str, temp;
	while (cin >> str) {
		if (str == "#") break;
		temp = solve(str);
		mp[temp]++;
     // 省去第二次排序的里技：直接多开个map把排序后的字符和原字符对应就行
		pm[str] = temp;
		vec.push_back(str); 
	}
	int vLen = vec.size();
	for (int i = 0; i < vLen; i++) {
    // 通过原字符取到排序字符，再通过排序字符询问这个字符出现次数
		if (mp[pm[vec[i]]] != 1) continue;
		res.push_back(vec[i]); 
	}
	sort(res.begin(), res.end());
	int rLen = res.size();
	for (int i = 0; i < rLen; i++) {
		cout << res[i] << endl;
		//if (i != rLen - 1) cout << endl;
	}
	return 0;
} 
```
## Trie树解
相信大家都知道Trie树是干嘛的，这里就不多介绍了。这个题利用的就是Trie树的一个特点：__快速查找某个字符串是否出现过。__ 于是根据map解的思路，我们可以把 __排序+格式化的字符串映射到Trie树里，然后再查找某个字符串出现的次数就行。__

另外相对于上一个map解来说，这个解 __还优化了输出__，众所周知，STL里的map默认会按Key值进行排序，根据这个特点，我们就可以省去最后输出答案的时候的排序了。
```cpp
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

// Trie树写法：同样需要把原字符串和排序后的字符对应，用来省去一次排序
// 做法就是把所有排序过的字符存到树里，然后统计这个字符串出现的次数
// 出现一次就是无法被组成的字符串 

// 无脑开大空间，RE了就划不来了
const int N = 1e5 + 10;
int son[N][26], cnt[N], id = 0;
map<string, string > mp;
// Trie树板子 
string getStr(string str) {
	int sLen = str.size();
	for (int i = 0; i < sLen; i++) str[i] = tolower(str[i]);
	return str;
}
void add(string str) {
	int p = 0, sLen = str.size();
	for (int i = 0; i < sLen; i++) {
		int cur = str[i] - 'a';
		if (!son[p][cur]) son[p][cur] = ++id;
		p = son[p][cur];
	}
	cnt[p]++;
}
bool fd(string str) {
	int p = 0, sLen = str.size();
	for (int i = 0; i < sLen; i++) {
		int cur = str[i] - 'a';
		// 这里可有可无，准确来说出现非法字符串的可能性为0% 
		// if (!son[p][cur]) return false;
		p = son[p][cur];
	}
	// 判断下这个字符串是否只出现了一次 
	return cnt[p] == 1;
}
int main() {
	string str, temp;
	while (cin >> str) {
		if (str == "#") break;
		temp = getStr(str);
		sort(temp.begin(), temp.end());
		// 将排序后的字符串和原字符串进行映射，这样可以省去一次排序 
		mp[str] = temp;
		add(temp);
	}
	// 压行什么的完全没必要啊 
	for (map<string, string >::iterator it = mp.begin(); it != mp.end(); it++) {
		// 如果key字符串的排序形式（value）只出现过一次，那么这个字符串就是唯一的 
		if (fd(it->second)) cout << it->first << endl;
	}
	return 0;
} 
```
~~好了，这个蒟蒻要去摸线代了~~


---

## 作者：Snowlanuck (赞：0)

我看了题解的代码,都挺长的

既然题目说要按字典顺序输出,我就想到了set,以及提到了重排,又想到了用map判断,

于是,整道题的思路就出来了,先用set集合读入数据,然后遍历set集合,用map判断集合内是否有能重排的(二重循环判断),如果没有就输出即可.

我第一次的做法是有能重排的就删除掉,发现并不能...

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;

//判断两个字符串能否重排
bool isSame(string a, string b)
{
	map<char, int> m1, m2;
	for (size_t i = 0; i < a.length(); i++)
		m1[tolower(a[i])]++;
	for (size_t i = 0; i < b.length(); i++)
		m2[tolower(b[i])]++;
	return (m1 == m2);
}

int main()
{
	string input;
	set<string> s;
	while (cin >> input)
	{//读入数据
		if (input == "#") { break; }
		s.insert(input);
	}

	for (set<string>::iterator i = s.begin(); i != s.end(); i++)
	{
		bool Flag = true;
		for (set<string>::iterator j = s.begin(); j != s.end(); j++)
		{
			if (i == j) { continue; }
			if (isSame(*i, *j)) { Flag = false; }
		}
		if (Flag) { cout << *i << endl; }
	}

	return 0;
}
```


---

## 作者：张良敏 (赞：0)

**这题用了一会儿，主要涉及两点，攻破了，就知道了怎么解题，首先我们需要解决字典序，然后再去重处理，字典序呢，jdk给我们提供了排序的集合，我们首先要把字符统一下（解决去重），统一大写还是小写，这里我统一小写，然后过滤下就可以，怎么过滤呢，可以用hash过滤，那么还是jdk提供的HashTree,直接得到去重结果集，然后两层循环啊，判断字符在原来的集合中出现几次，1次就记录（因为是去重结果集里面取，所以不存在等于0的情况），然后最后在字典序一下，正确答案就出来了**
```java
public class D1 {

    public static void main(String[] args){
        Scanner cin = new Scanner(System.in);
        List<String > sList=new ArrayList<>();
        while (cin.hasNextLine()){
            String s = cin.nextLine();
            if (s.equals("#")){
                break;
            }
            if (s.contains(" ")){
                //去掉多余的空格
                while ((s=s.replaceAll("  "," " )).contains("  ")){}
                String[] s1 = s.split(" ");

                Arrays.asList(s1).stream()
                        .filter(e->!e.equals("")).
                        forEach(e->sList.add(e));
            }else {
                sList.add(s);
            }
        }
        //去重
        Set<String> strings=new HashSet<>();
        sList.stream().forEach(e->strings.add(sort(e)));
        //结果
        TreeSet<String> results=new TreeSet<>();
        for (String s : strings) {
            String result="";
            int count=0;
            for (String s1 : sList) {
                if (s.equals(sort(s1))){
                    result=s1;
                    if (++count>1){
                        break;
                    }
                }
            }
            if (count==1){
                results.add(result);
            }
        }
        results.stream().forEach(e->System.out.println(e));
    }

    /**
     * 得到字符串的字典序，并把他变小写
     * @param s
     * @return
     */
    public static String sort(String s){
        String s1 = s.toLowerCase();
        List<Character> characters = new ArrayList<>();
        for (int i = 0; i <s1.length() ; i++) {
            characters.add(s1.charAt(i));
        }
        //排序，ascll码排序
        Collections.sort(characters, (o1, o2) -> o1-o2);
        s1="";
        for (Character character : characters) {
            s1+=character;
        }
        return s1;
    }
}
 


```


---

