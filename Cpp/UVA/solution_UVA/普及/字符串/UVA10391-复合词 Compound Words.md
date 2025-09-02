# 复合词 Compound Words

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1332

[PDF](https://uva.onlinejudge.org/external/103/p10391.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10391/c08e8f7cb6ab0d8672dfe8d32dd1d605dbe69332.png)

## 样例 #1

### 输入

```
a
alien
born
less
lien
never
nevertheless
new
newborn
the
zebra```

### 输出

```
alien
newborn```

# 题解

## 作者：imTars (赞：5)

### 这道题是紫书STL那一章推荐的，所以要用STL。
首先我们要用一个能快速查询的容器装字符串，想到了set。如果我们两两枚举所有字符串的化，时间复杂度是n^2, 毫无疑问会T掉。 那么我们反着想，枚举set中每个元素s，将其分成两个字串sa和sb,如果sa和sb属于set，那么输出s。

Code
```cpp
#include <bits/stdc++.h>
#define SIS ios::sync_with_stdio(false)

using namespace std;

int main() {
    SIS;
    string s;
    set<string> u;
    while(cin>>s) u.insert(s);
 
    for(auto x:u) {
        int len = x.length();
        for(int i = 1; i < len; i++) {
            if( u.count(x.substr(0, i))&&u.count(x.substr(i)) ) {
                cout << x << endl;
                break;
            }
        }
    }
    return 0;
}
```


---

## 作者：Shunpower (赞：3)

提示：萌新不会写substr，所以本篇是适合新手阅读的题解。

## PART 01 读入
我们可以利用C++语言的特性，把字符串读入写入循环条件里：
```cpp
for( ; cin>>s[cnt] ; ){ //C++语言特性
	cnt++;
}
```
为了避免变量重名，也为了为字符串数组提供指针，用 cnt 表示目前读入的下标，**而最终的 cnt 就是字符串的数量。**

## PART 02 算法
### 2.1：字符串匹配
我们知道判断一个字符串是否是复合串的方法就是将其分成两半，然后再分别判断分出来的两个字符串是否存在。**因此我们可以使用 map 来存储字符串是否存在过**。
```cpp
map <string,bool> p;
for( ; cin>>s[cnt] ; ){
	p[s[cnt]] = true; //如果该字符串存在了，map 值变为 true
	cnt++;
}
```
### 2.2：隔板法
如果我们想要把一个字符串分成两个部分，可以理解为将一个整体用一块隔板将其分开。**所以不妨用一个循环变量当做隔板进行字符串分割。**
```cpp
for(int j = 1 ; j < s[i].length() ; j++){ // j 作为隔板分割字符串
		for(int k = 0 ; k < j ; k++){
			a += s[i][k]; // j 前面的字符都变成前半部分的串（a）
		}
		for(int k = j ; k < s[i].length() ; k++){
			b += s[i][k]; // j 后面的字符都变成后半部分的串（b）
		}
}
```
注意，有些同学认为当存在两个相同的串时，也认为其中一个是复合串，**但其实这样的串也属于普通串的范畴**。因此，**我们可以发现 b 串至少可以取到最后一个字符，排除了有相同串的情况**。

### 2.3：判断情况

这里便可以体现出 map 的作用。

只要得到了 a 串与 b 串我们就可以往循环里面加入判断，即通过 map 的布尔值来判断是否存在过。

```cpp
for(int j = 1 ; j < s[i].length() ; j++){
		for(int k = 0 ; k < j ; k++){
			a += s[i][k];
		}
		for(int k = j ; k < s[i].length() ; k++){
			b += s[i][k];
		}
		if(p[a] && p[b]){
			cout<< s[i] <<endl;
			break; //就是这里，如果不加就会WA掉，因为可能一个串有多种分割办法。
		}
}
```
值得一提的是，为了防止拼法有多种导致多种输出，有必要在判断完后进行 break 。

最后要记住，清空 A 串与 B 串以供下次使用。

## AC代码

[AC记录](https://www.luogu.com.cn/record/51148816)


```
#include <bits/stdc++.h>
using namespace std;
map <string,bool> p;
string s[120030],a,b;
int cnt;
int main(){
	for( ; cin>>s[cnt] ; ){
		p[s[cnt]] = true;
		cnt++;
	}
	for(int i = 0 ; i < cnt ; i++){
		for(int j = 1 ; j < s[i].length() ; j++){
			a = "";
			b = "";
			for(int k = 0 ; k < j ; k++){
				a+=s[i][k];
			}
			for(int k = j ; k < s[i].length() ; k++){
				b+=s[i][k];
			}
			if(p[a] && p[b]){
				cout<< s[i] <<endl;
				break;
			}
		}
	}
	return 0;
}
```


---

## 作者：mcDinic (赞：2)

本题很多大神用了 count 函数及一些高深方法，本蒟蒻表示不会，就写了篇 **方便入门者理解** 的题解。

## 方法：

题目中说，一个两字复合词是指字典中的一个词，是字典中另外两个词的连词（当然，这个翻译并不严谨，后面详解），而这两个词的长度，就一定小于该复合词的长度。所以，只要它们被 map 标记过，就能得出该词为复合词。

怎样让这些单词中，长度短的先被标记，长的后被标记呢？显然，用 sort 排下序就行了。至于输入的字符串用 vector 存，标记的用 map 存，不断枚举形成的第一个单词，接下来再用个 vector 存答案，去下重，就没有难点了。

## 坑点：

刚刚说的翻译不严谨就在此，复合词可以 **由相同的一个词用两遍组成**。

不过，这样反而能使我们的代码简单，说这个坑点是为了仔细的同学别聪明反被聪明误。

## Code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;//n 没用。
vector<string>a;//存字符串。
vector<string>ans;//存答案字符串。
map<string,int>mp;//标记该字符串是否已有，帮助形成答案。
map<string,int>mp2;//标记答案字符串是否有重复，我不会 unique，就用这个了。
signed cmp(string x,string y){
	if(x.size()==y.size()){
		for(int i=0;i<x.size();i++){
			if(x[i]!=y[i])return x[i]<y[i];
		}
        return 0;
	}
	return x.size()<y.size();
}//自定义排序。
signed main(){
	a.clear();
	mp.clear();
	ans.clear();
	string kli;
	while(cin>>kli){
		a.resize(a.size()+1);
		a.push_back(kli);
	}//输入。
	sort(a.begin(),a.end(),cmp);//排序。
	for(int i=0;i<a.size();i++){
		int oi=a[i].size()-1;
		string noi;//枚举形成该字符串的第一个单词。
		noi.clear();
		for(int j=0;j<oi;j++){
			noi+=a[i][j];
			if(mp[noi]){
				string akioi;akioi.clear();//若第一个单词可行，看看第二个行不行。
				for(int k=j+1;k<=oi;k++){
					akioi+=a[i][k];
				}
				if(mp[akioi]){
					ans.resize(ans.size()+1);
					ans.push_back(a[i]);//要不要 break 随你，反正时间充裕的很。
				}
			}
		}
		mp[a[i]]++;
	}
	sort(ans.begin(),ans.end());
	for(int i=0;i<ans.size();i++){
		if(ans[i][0]>='a'&&ans[i][0]<='z'&&!mp2[ans[i]]){
			cout<<ans[i]<<endl;
			mp2[ans[i]]=1;
		}//不会去重函数，就这么搞了。
	}
    return 0;	
}
```


---

## 作者：D2T1 (赞：1)

[$\color{blue}{\text {pwp }~{\to\textbf{My blog}\gets}}~\text{qwq}$](https://www.luogu.com.cn/blog/390770/blogcenter)

## 题解

首先可以想到：每次从集合中选出两个字符串，判断它们拼在一起是否在集合中。但是这样做的复杂度是 $O(n^2)$ 的，显然过不了。

于是考虑是否可以从一个字符串进行拆分。步骤如下：

- 读入所有字符串，放入一个集合中。

- 枚举每个字符串，再枚举分割处，把字符串分成两个子串，在集合中查找是否都存在。如果有一种分割方式能够满足题意，输出该字符串。

- `return 0;`

------------

这里集合使用 `STL set`，枚举集合元素（字符串）可以使用 `iterator`，示例：

`for(set<string>::iterator it=s.begin(); it!=s.end(); ++it)`

使用该字符串只用 `(*it)` 即可。

------------

分割字符串可以用 `substr`，用法如下：

`substr(<开始地址>，<截取长度>);`

当然不写长度也是可以的，默认截取到末尾。

------------

在集合中查找有两种方式：`find` 和 `count`。因为 `count` 返回的是 $0$ 或 $1$，更方便，所以使用 `count`。

## 代码

```cpp
//UVA10391
#include <iostream>
#include <cstring>
#include <set>
using namespace std;

set<string> s;
string str;

int main(){
	while(cin >> str) s.insert(str);
	
	for(set<string>::iterator it=s.begin(); it!=s.end(); ++it){
		string k=*it; int l=k.size();
		for(int i=1; i<l; ++i){
			if(s.count(k.substr(0,i))&&s.count(k.substr(i))){
				cout << k << '\n';
				break;
			}
		}
	}
	
	return 0;
}
```


---

## 作者：StayAlone (赞：1)

### 题意

给定一个词典，找出其中所有的复合词。复合词是指恰好由两个词典中的单词连接而成的单词。每行输入是一个由小写字母组成的单词。输入按照字典序从小到大排列，且单词数量不超过 $120000$ 个。请输出词典中所有的复合词，并且按字典序从小到大排列。

小坑：可以是两个**相同的单词**组成的复合词。

### 思路

#### 思路 1
比较好想：直接双重循环枚举词典中所有单词的配对情况，
拼接之后再循环判断是否在词典中。这种方法得出的结果不一定是按照字典序出现的，因此还需要拿一个数组存储答案，排序后输出。慢得可以，$O(n^3)$，没交，便再拿 $\texttt{map}$ 进行优化，故复杂度为 $O(n^2)$，光荣 TLE。

```cpp
#include <bits/stdc++.h>
using namespace std;
string s[120010], ans[60010]; int idx, ani;
map <string, bool>vis;
int main()
{
	while (cin >> s[++idx]) vis[s[idx-1]] = true; idx--;
	for (int i = 1; i <= idx; ++i)
		for (int j = i; j <= idx; ++j)
		{
			if (vis[s[i] + s[j]]) ans[ani++] = s[i] + s[j];
			if (vis[s[j] + s[i]]) ans[ani++] = s[j] + s[i];
			// 这里当时还小优化一下，直接两种都判断了。 
		}
	sort(ans, ans + ani);
	for (int i = 0; i < ani; ++i) cout << ans[i] << endl; 
	return 0;
}
```

#### 思路 2
紧接着便转换思路：把**两个拼成一个转化成一个拆成两个**，每一次枚举拆的字符串和拆出来的前一个字符串的长度。  

枚举出长度便可以知道前一个字符串和后一个字符串，同样使用 $\texttt{map}$ 来表示是否存在。如果**前后两个都存在**，就放入答案数组。时间复杂度为 $O(nlen)$，其中 $len$ 表示字符串的长度~~题目没给啊~~。莫名 WA 掉。
```cpp
#include <bits/stdc++.h>
using namespace std;
string s[120010], ans[60010]; int idx, ani;
map <string, bool>vis;
int main()
{
	while (cin >> s[++idx]) vis[s[idx-1]] = true; idx--;
	for (int i = 1; i <= idx; ++i)
	{
		int len = s[i].length();
		for (int l = 1; l < len; ++l)
			if (vis[s[i].substr(0, l)] && vis[s[i].substr(l, len - l)]) ans[ani++] = s[i];
	}
	for (int i = 0; i < ani; ++i) cout << ans[i] << endl;
	return 0;
}
```
仔细审视后，发现输出后要 $\texttt{break}$ 掉循环，否则有多种拼法的字符串会被多次输出。同时发现**输入时就是字典序**了，这样写不需要拿数组，直接输出即可。  


这里再说一下 $\texttt{substr}$ 的用法。

``str.substr(idx, len);``

该行代码有 $\texttt{string}$ 类型返回值，返回的值是字符串 $str$ 中下标为 $idx$ 开始的长度为 $len$ 的字符串。

故枚举长度时，前一段的字符串长度为 $l$，则：

- 前一段字符串为 ``s[i].substr(0, l)``；
- 后一段字符串为 ``s[i].substr(l, len - l)``。

[AC code记录](https://www.luogu.com.cn/record/51131845)
```cpp
#include <bits/stdc++.h>
using namespace std;
string s[120010], ans[60010]; int idx, ani;
map <string, bool>vis;
int main()
{
	while (cin >> s[++idx]) vis[s[idx-1]] = true;
	idx--;
	for (int i = 1; i <= idx; ++i)
	{
		int len = s[i].length();
		for (int l = 1; l < len; ++l)
			if (vis[s[i].substr(0, l)] && vis[s[i].substr(l, len - l)])
			{
				cout << s[i] << endl;
				break;
			}
	}
	return 0;
}
```

---

## 作者：HNFMS_Zbr (赞：1)

# 蒟蒻代码
看着没题解,自己发一个,详见注释
```cpp
#include<iostream>
#include<string>
#include<map>
using namespace std;
map <string, int> A;	//记录单词是否出现
string S[16868];		//记录单词
int t;					//字符串数组指针 
int main(){
	while(cin >> S[++t])
		A[S[t]] = 1;
	for(int i=1;i<=t;i++)
		for(int j=1;j<=S[i].size();j++){
			string s1 = S[i].substr(0, j);	//取出S[i]的前部分并检查
			if(A[s1]){
				string s2 = S[i].substr(j);	//取出S[i]的后部分并检查
				if(A[s2]){
					cout << S[i] << endl;	//若都符合条件,输出 
					break;
				}
			} 
		}
	return 0;
} 

```

---

## 作者：linxuanrui (赞：0)

### 写在前面

这个题解适合会哈希的人。

不过你也可以了解思路然后用 `unordered_map`（ `map` 也行），因为它的底层机制就是哈希。

### 题目大意

定义一个单词为复合词当且仅当这个单词可以由两个单词拼接而成。

给定若干个按照字典序排列的单词，求共有多少个复合词。

### 题解

接下来有两种做法：

1. 枚举可以拼成的单词

枚举每一对单词，如果拼成的单词出现过，那么就输出这个单词。

时间复杂度为 $O(n^2)$，考虑优化。

2. 枚举可以拆成的单词

既然不能枚举可以拼成的单词，那我们可以反着想。

枚举每一个单词，将其拆成两端，如果这两段都出现过，那么就输出这个单词。

时间复杂度为 $O(n \times len)$，其中 $len$ 为单词的长度。

这样子就可以 AC 这一题了。

我的代码是用 `substr` 来获取字串，其中 `s.substr(a,b)` 表示从字符串 s 中截取一个从下标 a 开始，长度为 b 的字串。 

### 注意事项

一个单词可能有多种拆分方式，因此如果有一种情况满足就可以输出了。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
string s[120002],t;
int cnt;
const int mod = 1000007;
vector<string> v[mod];
int getnum(string s){//获取哈希值，我用的是这个字符串的所有字符的 ASCII 码总和模 1000007
	int ans = 0;
	for(int i = 0;i < s.size();i++)ans = (ans + s[i]) % mod;
	return ans;
}
void insert(string s){
	v[getnum(s)].push_back(s);
}
bool find(string s){
	int tmp = getnum(s);
	for(int i = 0;i < v[tmp].size();i++){
		if(v[tmp][i] == s)return true;
	}
	return false;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	while(cin >> t)s[++cnt] = t,insert(t);
	for(int i = 1;i <= cnt;i++){
		for(int j = 1;j < s[i].size() - 1;j++){//枚举每种拆分情况
			if(find(s[i].substr(0,j)) && find(s[i].substr(j,s[i].size() - j + 1))){
				cout << s[i] << endl;
				break;//一定要 break，不然一个单词会被输出多次
			}
		}
	}	
}
```

---

## 作者：Swiftie_wyc22 (赞：0)

**超短代码！**

此题很简单。注意单词只分成两部分，那么只能是从最左开始一段，剩下的一段。

~~很疑惑题解为什么都写那么长~~

先用 map 标记所有单词，再逐个枚举每个单词，把单词分为左右两段，判断是不是都在 map 里事先保存好了，如果有一个，就是复合词。


```cpp
#include <bits/stdc++.h>
using namespace std;
map<string, bool>mp;
string str[100010], ss;
int idx = 1;
int main()
{
	while (cin >> ss) { // 输入并标记
		mp[ss] = true;
		str[idx] = ss;
		idx++;
	}
	for (int i = 1; i < idx; i++) { // 枚举每一个单词
		bool flag = false;
		for (int k = 1; k < (int)str[i].size(); k++) {
        // 划分左右两部分，划分不能划分到单词本身
			if (mp[str[i].substr(0, k)] && mp[str[i].substr(k, str[i].size() - k)]) {
				flag = true;
                //可以break
			}
		}
		if (flag)
			cout << str[i] << endl;
	}
	
    return 0;
}
```




---

## 作者：BobXia (赞：0)

这道题我调了很久。若一个组合词 AB， 我的思路是先判断 A 是否 match，然后判断 B，我的代码是这样的
```c++
string sub1;
int pos = 0;
for ( int i = 1; i <= (*it).length(); i++){
    sub1 = (*it).substr(0,i);
    if ( dictionary.count(sub1) ){
        pos = i;
        break;
    }
}   
if ( pos ){
    string sub2;
    sub2 = (*it).substr(pos);
    if ( dictionary.count(sub2) )
        cout << *it << endl;
} 
```
在我的程序中，A 一旦匹配，就会判断 B 是否匹配，然而有可能会有多个 A B，比如说一个本应该输出的复合词 xxyy，x 先匹配到了，但是 xyy 没有匹配到，这个时候就不会输出，然而并没有考虑 xx 也有可能可以匹配的情况，所以应该把 B match 拿到 for 循环里面，然后把这个 break 写到 cout 后面就对了.

以下是 AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define SUBMIT
set<string> dictionary;
int main()
{
#ifndef SUBMIT
    freopen("out.txt", "w", stdout);
    freopen("in.txt", "r", stdin);
#endif
    string word;
    while ( cin >> word)
        dictionary.insert(word);
    for ( set<string>::iterator it = dictionary.begin(); it != dictionary.end(); it++){
        string sub1;
        int pos = 0;
        for ( int i = 1; i <= (*it).length(); i++){
            sub1 = (*it).substr(0,i);
            if ( dictionary.count(sub1) ){
                pos = i;
            }
            if ( pos ){
                string sub2;
                sub2 = (*it).substr(pos);
                if ( dictionary.count(sub2) ){
                    cout << *it << endl;
                    break;
                }
            }
        }   
                
    }    
#ifndef SUBMIT
    fclose(stdout);
    fclose(stdin);
#endif
    return 0;
}
```


---

## 作者：baiABC (赞：0)

### **整体思路：枚举每个 ```string``` 看是否是复合词。**
可以用 ```vector```。

只是 ```vector``` 的 ```find``` 时间复杂度是 $\Theta(n)$ 显然会被T掉。（~~我是试了才知道~~

由于输入保证字典序，**考虑二分。**

只要 ```lower_bound``` 和 ```upper_bound``` 返回的值不同就说明该元素在此 ```vector``` 内。

最后说一个巨坑：复合词**不一定**是由两个不同单词拼接而成。(可能是我想的太多了？WA了好几次。）

例如：

**输入**：
```
a
aa
```
**输出**：
```
aa

```

*代码:*
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    vector <string> v;
    string s;
    while(cin >> s)
        v.push_back(s);
    for(int i = 0; i < v.size(); i++)
        for(int j = 1; j < v[i].size(); j++)
        {
            string s1 = v[i].substr(0, j), s2 = v[i].substr(j);
            if(lower_bound(v.begin(), v.end(), s1) != upper_bound(v.begin(), v.end(), s1)
            && lower_bound(v.begin(), v.end(), s2) != upper_bound(v.begin(), v.end(), s2)) // 如果不会STL请自行百度。
            {
                cout << v[i] << endl;
                break;
            }
        }
    return 0;
}
```

---

