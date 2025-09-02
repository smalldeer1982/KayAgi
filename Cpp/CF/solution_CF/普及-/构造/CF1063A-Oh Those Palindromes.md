# Oh Those Palindromes

## 题目描述

一个非空字符串叫做回文串。如果它从左到右，从右到左读相同，那么它就是回文串。
例如，“ABCBA”,“A”和“ABBA”都是回文串，而“ABAB”和“XY”则不是。




如果可以通过从字符串的开头和结尾删除一些（可能为零）字符来从该字符串获得新字符串，
则新字符串叫做另一个字符串的子字符串。
例如，“ABC”、“AB”和“C”是字符串“ABC”的子串，而“AC”和“D”不是。


我们把字符串的“回文计数”定义为回文的子串个数。
例如，字符串“aaa”的回文计数是6，因为它的所有子字符串都是回文，
而字符串“abc”的回文计数是3，因为只有长度为1的子字符串是回文。


给你一个字符串S。你可以任意地重新排列它的字符，求它的回文计数最大值。

## 说明/提示

在第一个例子中，字符串“ololo”有9个9回文子串：
"o","l","o","l","o","olo","lol","olo","oloo"

注意，即使某些子串重合，它们也会在生成的字符串中计入多次。




在第二个例子中，字符串“abccbaghghghgdfd”的回文计数为29。

## 样例 #1

### 输入

```
5
oolol
```

### 输出

```
ololo
```

## 样例 #2

### 输入

```
16
gagadbcgghhchbdf
```

### 输出

```
abccbaghghghgdfd
```

# 题解

## 作者：communist (赞：9)

### 考虑在一个部分串中加入字符使得最终构造的串回文子串最多的方案

考虑简单情况，对于只含一种元素的串，我们要插入其他元素

记原有元素为$a$，新加元素为$b$

考虑$b$的最优插入位置

原串$aaaa...aa$，插入$b$

设$b$在串中的插入位置为$pos$，插入后，原本的回文串$[pos-i,pos+j](i!=j)$会因此不匹配

所以这样不会使得原串匹配结果变多

所以我们要让各个元素独立才是最优方案

```
#include<iostream>
#include<cstdio>
using namespace std;
string s;
char ans[100010];
int l,cnt[100010],cnts;
int main()
{
	cin>>l>>s;
	for(int i=0;i<l;i++)
		cnt[s[i]-'a']++;
	for(int i=0;i<26;i++)
		for(int j=1;j<=cnt[i];j++)
			ans[cnts++]=i+'a';
	printf("%s\n",ans);
	return 0;
}
```

---

## 作者：cff_0102 (赞：2)

明显的，要让相同的字符聚在一起答案更大。怎么让相同的数字聚在一起？排序即可。

别忘了把第一行那个没用的 $n$ 读入进来。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	int _;cin>>_;
	string s;
	cin>>s;
	sort(s.begin(),s.end());
	cout<<s;
	return 0;
}
```

---

## 作者：XKqwq (赞：2)

一道构造题。

首先举几个例子理解题意：

| 输入 | 答案 |
| :----------: | :----------: |
| $\texttt{adabccc}$    |  $\texttt{aabcccd}$  |
|$\texttt{abcade}$ | $\texttt{aabcde}$  |
|$\texttt{abc}$ | $\texttt{abc}$  |

可以看出想使得回文计数值最大，需要将相同的字母放在一起。

很容易想到可以排序后直接输出。

因为有多种情况，所以原题有 spj ，不需要考虑排序方式。


 ### $\texttt{Code}$
 
 ```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int n;
int main(){
	cin>>n>>s;
	sort(s.begin(),s.end());
	cout<<s;
	return 0;
}
```







---

## 作者：冽酒灬忄 (赞：2)

**题目大意**：让你将原字符串适当交换位置，使新生成的字符串中的回文串最多



------------
这个题只需要将原字符串按Ascii码的顺序从大到小排一遍序然后输出就行了~~（史上最水紫题）~~

```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
string s;
int n,a[50];
int main(){
	cin>>n>>s;
	for(int i=0;i<n;i++)
		a[s[i]-'a']++;//统计该字符出现了几次
	for(int i=0;i<=30;i++){//按照顺序输出
		char x=i+'a';
		if(a[i]!=0)
		for(int j=1;j<=a[i];j++)
			cout<<x;
	}
		
}
```

---

## 作者：刘健铭 (赞：1)

# Oh Those Palindromes

思路：~~水题~~基础题一道，将原字符串排完序后的字符串的回文子串的数量一定比原字符串的回文子串的数量大，所以 sort 排序就行了。
 
代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	string s;
	cin>>n>>s;
	sort(s.begin(),s.end());
	cout<<s<<endl;
	return 0;
}
```


---

## 作者：人间凡人 (赞：1)

这道题其实是一道**字符串贪心**题。

~~大家千万不要看样例。这是用来误导我们这些OIer的。~~

请注意：如果有多个答案相同的字符串，输出它们中的任何一个即可。

**思路**：

	先假设有abcabcc这七个字符。最多的方案为：aabbccc。
   
   再多模拟一些例子后 就可以知道 最多的方案有很多 但必有一种
   为原先字符集按$ASCII$码从小到大排完序后的序列。
   
   故可得结论是:使每一个字符尽量独立所得到的解才是最优的。
 
所以只用将输入的**从小到大**或**从大到小**排一遍序即可。

话不多说,上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f[26];		
char x;
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		cin>>x;
		f[x-'a']++;		//统计该字符出现了几次
	}					
	for(int i=0;i<26;i++)
		for(int j=1;j<=f[i];j++)
        printf("%c",i+'a');		//计数排序
	printf("\n");
	return 0;
}
```



---

## 作者：oceanfish (赞：0)

## 题目大意
可以自行看题目，不是很难理解。
### [原题传送门](https://www.luogu.com.cn/problem/CF1063A)


------------

## 分析思路
由于题目拥有 SPJ，也就是一个测试点多种答案，这就给了我们~~钻空子的~~机会：我们设想有一个字符串 `abaacb`，为了使其回文子串最多，我们很容易想到这样一种方案：让串中相同的字符**集中至一块**，这样，这个全都是一种字符的串中的回文子串**最多**，足足有 $\sum _ {i = 1} ^ n i$ 个！

那么怎么将字符集中至一块呢？很简单，只需要对字符串进行**排序**，考虑到 $1 \leq n \leq 10^6$，使用 $O(n^2)$ 的排序算法过于慢了，我们可以使用库函数 `sort()` 进行排序。


------------
## 代码实现
```cpp
#include <bits/stdc++.h>//万能库，不用火车头
using namespace std;
int n;//n只是过个场合
string s;
int main() {
	cin >> n >> s;//输入
	sort(s.begin(), s.end());//sort排序字符串的方式:sort(str.begin(),str.end(),cmp);此处可不用cmp
	cout << s;//输出
	return 0;//非0会RE
}
```


---

## 作者：Terry2011 (赞：0)

# 题目分析

- 首先，这道题目要使回文计数的可能值最大。我们来想一想，怎么才能使其最大呢？显然，我们应当将相同的字母放在一起。比如：字符串 $aaa$ 中，四个 $a$ 分别为一个回文，两个 $aa$ 又是回文，$aaa$ 自己又是回文。
- 知道了这个，怎么才能实现呢？字典序排序！用一个 sort 排序，一切都简单了，这样，字典序靠前的字母就会统一排到前面。同理，字典序靠后的字母就会统一排到后面，实现了相同的字母放在一起。

# Code
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main(){
    string s;//定义字符串
    int n;
    cin>>n>>s;//输入
    sort(s.begin(),s.end());//字典序排序（其中s.begin()和s.end()是sting中自带的函数，分别提取开头结尾）
    cout<<s;//输出
    return 0;
}
```

---

## 作者：Epi4any (赞：0)

个人建议：加上贪心标签（读者忽略）。

一眼看穿：又是构造题。

先给结论：假如我们把相同的字符都堆在一起，那我们就能获得尽可能多的回文子串。

原因：两个相同的字符最多可以产生一个以他们为头和尾的回文子串，于是我们想**最大化利用这样相同的字符**，也就是**把他们放在一起**，这样可以让三个放在一起的相同字符对答案产生两个两对字符的效果。

具体实现见代码：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

int n, len;
char s[100005];

int main() {
	n = read();
	scanf("%s", s + 1); //这种输入很好用，可以从下标1开始输入字符串
	sort(s + 1, s + n + 1); //排序 
	printf("%s", s + 1); //输出一定不要忘记下标问题！ 
	return 0;
}
```


---

## 作者：alex_liu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1063A)

# 题意：

改变原字符串的任意字符组成新的字符串使新字符串的回文子串数量最多。

# 思路：

先想一下：
1. 每一个字符都是一个回文子串

2. 随意的两个字符都是一个回文子串

------------

那我们设一个字符串为：“ aaba ”

将字符串排完序以后就变成了 ：“ aaab ”

那么这样的字符串难道不是比原字符串的回文子串数量要大吗？

所以说，将原字符串排完序后的字符串的回文子串的数量一定比原字符串的回文子串的数量大

排序用 $sort$ 就好了

# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
		int n;//字符串长度
		string s;//字符串
		cin>>n>>s;//读入
		sort(s.begin(),s.end());//排序（默认从小到大）
		cout<<s<<endl;//输出
		return 0;
}
```


---

## 作者：ForeverCC (赞：0)

这题要求把字符串重新排列之后回文串的最多数量。

为了使方案最优，让各个字符独立。

因为在类似 `aaa` 的字符串中插入一个 `b`，为了不减少回文串的数量，把 `b` 放在最左边或最右边。

先统计每个字符出现的次数，再把同一个字符同一输出即可。

代码：

~~~
#include<bits/stdc++.h>
using namespace std;
int n,t[30];      
char s[100005];
int main(){
    scanf("%d%s",&n,s);
    for(int i=0;s[i];i++)
        t[s[i]-'a']++;
    for(int i=0;i<26;i++)
        for(int j=1;j<=t[i];j++)
            printf("%c",'a'+i);
    return 0;
}
~~~

---

## 作者：happybob (赞：0)

贪心题目，要想回文子串最多，排一下序。

我们想一下，对于每一个字符，都是回文的没错吧？

那么，`abab` 这个字符串排序（从小到大）就是 `aabb`，或者从大到小，`bbaa`，相同的字符都在一起，这些字符和前面其他的一些字符一样，相同的字母的子串，那么从左往右和从右往左不一样吗？

给代码（没有用 `sort` 的吗）：

```cpp
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
	string s;
	cin >> s >> s;
	sort(s.begin(), s.end());
	cout << s << endl;
	//system("pause");
	return 0;
}
```


---

## 作者：QGCY (赞：0)

###### 求管理通过，为社区做贡献，谢谢！！！
####   题目大意：将输入的字符串交换位置，让现在的字符串里面回文字符串最多
   分析：首先这道题不要看样例，可以和样例不一样，别被迷惑了。
   总体思路：将每个字符出现的顺序记录下来，最后找一遍，如果有这个字符就输出；   
     代码：
   ```cpp
#include<bits/stdc++.h> //万能头 
using namespace std;
string s;
int n,sum[50];
int main(){
	cin>>n>>s;
	for(int i=0;i<n;i++)
		sum[s[i]-'a']++; //统计每个字符出现的顺序 
	for(int i=0;i<=30;i++){
		char x=i+'a'; 
		if(sum[i]!=0) //如果有这个字符 
		for(int w=1;w<=sum[i];w++)//输出 
			cout<<x;
	}
	return 0;//完美结束!!! 
}
```


---

