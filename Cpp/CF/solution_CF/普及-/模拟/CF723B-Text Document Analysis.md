# Text Document Analysis

## 题目描述

Modern text editors usually show some information regarding the document being edited. For example, the number of words, the number of pages, or the number of characters.

In this problem you should implement the similar functionality.

You are given a string which only consists of:

- uppercase and lowercase English letters,
- underscore symbols (they are used as separators),
- parentheses (both opening and closing).

It is guaranteed that each opening parenthesis has a succeeding closing parenthesis. Similarly, each closing parentheses has a preceding opening parentheses matching it. For each pair of matching parentheses there are no other parenthesis between them. In other words, each parenthesis in the string belongs to a matching "opening-closing" pair, and such pairs can't be nested.

For example, the following string is valid: "\_Hello\_Vasya(and\_Petya)\_\_bye\_(and\_OK)".

Word is a maximal sequence of consecutive letters, i.e. such sequence that the first character to the left and the first character to the right of it is an underscore, a parenthesis, or it just does not exist. For example, the string above consists of seven words: "Hello", "Vasya", "and", "Petya", "bye", "and" and "OK". Write a program that finds:

- the length of the longest word outside the parentheses (print 0, if there is no word outside the parentheses),
- the number of words inside the parentheses (print 0, if there is no word inside the parentheses).

## 说明/提示

In the first sample, the words "Hello", "Vasya" and "bye" are outside any of the parentheses, and the words "and", "Petya", "and" and "OK" are inside. Note, that the word "and" is given twice and you should count it twice in the answer.

## 样例 #1

### 输入

```
37
_Hello_Vasya(and_Petya)__bye_(and_OK)
```

### 输出

```
5 4```

## 样例 #2

### 输入

```
37
_a_(_b___c)__de_f(g_)__h__i(j_k_l)m__
```

### 输出

```
2 6```

## 样例 #3

### 输入

```
27
(LoooonG)__shOrt__(LoooonG)
```

### 输出

```
5 2```

## 样例 #4

### 输入

```
5
(___)
```

### 输出

```
0 0
```

# 题解

## 作者：TLMPEX (赞：2)

这题就是简单的模拟，思路详见代码：

```c
#include<bits/stdc++.h>
using namespace std;
string k;
int main(){
	int n,i,a=0,s=0,x=0,y=0;
	cin>>n;
	getchar();
	getline(cin,k);
	for(i=0;i<n;i++){
		if(a<1&&k[i]!='_'&&k[i]!='(')s++;
		else if(a<1&&(k[i]=='_'||k[i]=='(')){
			x=max(x,s);
			s=0;
		}
		if(a&&k[i]!=')'){
			if(k[i]=='_'&&k[i-1]!='_'&&k[i-1]!='(')
				y++;
			if(k[i]!='_'&&k[i+1]==')')y++;
		}
		if(k[i]=='(')a=1;
		if(k[i]==')')a=0;
	}
	if(s)x=max(x,s);
	cout<<x<<" "<<y;
}
```


---

## 作者：wwwwwza (赞：0)

这道题是一道模拟题，按着题目要求简单判断一下就可以了。  
我们先要枚举字符串的每个字符。  
如果字符为字母，将记录单词长度的变量加一。如果不是字母，则这个单词结束了（记录单词长度的变量大于等于一时才可进行下一步操作）。  
判断这个单词是否在括号内，如果在，将记录括号内单词数量的变量加一。否则去判断此单词的长度是否为之前单词长度最长的一个，如果是，则改变存储最长单词长度的变量改成记录单词长度的变量。  
最后输出存储最长单词长度的变量和记录括号内单词数量的变量。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;
int n,len=0,sum=0,cnt=0;
string s;
int flag=0;//注意括号套括号的情况 
signed main(){
	cin >>n>>s;//输入 
	for(int i=0;i<n;i++){
		if(s[i]>='a'&&s[i]<='z'||s[i]>='A'&&s[i]<='Z'){//字母 
			cnt++;//单词长度增加 
		}else{
			if(flag&&cnt)sum++;//只有字母且长度大于0的才算单词
			else len=max(len,cnt);
			if(s[i]=='(')flag++;
			if(s[i]==')')flag--;
			cnt=0;
		}	
	}
	len=max(len,cnt);
	cout <<len<<" "<<sum;//输出 
	return 0;
}



```

---

## 作者：I_AK_IOI_and_NOI (赞：0)

## 题目大意

有一篇由大小写字母，下划线和小括号组成的文档。保证左右括号完整匹配，且不会出现括号之间相互嵌套。一个单词是一串连续的字母，不含下划线和括号。请计算括号外的单词的最大长度，括号内的单词的数量。

-----------------------------------------
注释讲得很清楚了。

```
#include<bits/stdc++.h>
using namespace std;
int ans; //统计括号内的单词数量 
int ans2; //计算括号外的单词的最大长度
int len; //字符串长度 
bool tmp=0; //判断当前是否实在括号内
bool v=0; //判断上一个单词是否结束 
string a; //输入的字符串 
bool check(int i) //判断a[i]是不是字母 
{
	return (a[i]!='_' && a[i]!='(' && a[i]!=')');
	//不是下划线，也不是左括号和右括号，就是字母 
}
int main()
{
	int maxx=0;
	cin>>len;
	cin>>a;
	for(int i=0;i<len;i++) //枚举每一位 
	{
		if(a[i]=='(') tmp=1; //遇到了左括号，接下来是括号内的数 
		if(a[i]==')') tmp=0; //接下来不是括号内的数 
		if(tmp==1) //在括号里面 
		{
			if(check(i)) //如果这是字母 
			{
				if(v==0) //上一个单词已经结束了 
				{
					ans++; //答案+1 
					v=1; //标记还未结束 
				}
			}
			else v=0; //否则还是结束状态 
		} 
		else if(tmp==0)
		{
			if(check(i)) //遇到的字符是字母，累加长度
			{
				ans2++; 
			}
			else //否则比较清零 
			{
				maxx=max(ans2,maxx);
				ans2=0;
			}
		}
	}
	cout<<maxx<<" "<<ans; //输出结果，完结撒花~~ 
}
```


---

## 作者：CyaNgw_DyG (赞：0)

## 题意

- 给一个由**大小写字母**，**下划线**，**左右小括号**组成的字符串。

- 大小写字母组成的单词由**下划线或左/右小括号**隔开，左右小括号**必定匹配且不相交**。

- 求**括号外**的**单词的最大长度**以及**括号内**的**单词数量**。

## 思路&代码

- 输入字符串长度以及字符串。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n;
signed main(){
	cin>>n>>s;
}
```

- 我们考虑到**括号外**和**括号内**两种情况，所以我们只需要在**遇到左括号且还没有遇到右括号**时处理括号内，**遇到右括号**过后处理括号外就可以了。

- 所以我们在代码中拿一个 `flag` 来标记是否在括号内。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n;
int flag;
signed main(){
	cin>>n>>s;
	for(int i=0;i<n;i++){//按照字符串下标来循环
		if(s[i]=='(')flag=1;//进入括号内
		if(s[i]==')')flag=0;//进入括号外
	}
}
```
- 接下来我们针对 `flag` 来进行两种操作

1. `flag=1`，**括号内**，求**单词个数**，只要判断到每个单词的**首字母**即可知道这是一个单词，这个单词循环完了过后**自然会遇到下划线或者括号**，所以我们只需要标记一下当前单词首字母有没有遇到过。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n;
int cnt,flag,vis;//cnt来记录括号内单词个数，vis来标记是否是首字母
bool pd(int i){return (s[i]!='_' && s[i]!='(' && s[i]!=')');}//除了这三种字符，其他都是大小写字母了
signed main(){
	cin>>n>>s;
	for(int i=0;i<n;i++){
		if(s[i]=='(')flag=1;
		if(s[i]==')')flag=0;
		if(flag==1){
			if(pd(i)){if(vis==0)cnt++,vis=1;}//如果遇到首字母，就直接cnt++，vis标记一下当前单词首字母已经遇到过
			else vis=0; //若遇到下划线或括号（其实不会遇到括号），记录下一个单词
		}
	}
}
```

2. `flag=0`，即找出**括号外最长的单词的长度**，对于每次找到单词**首字母**，开始累加长度，一旦遇到下划线或者括号，**立即结算当前单词长度**，与**当前最大值**作比较，然后**清零**累加。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n;
int len,maxx;//括号外
int cnt,flag,vis;//括号内
bool pd(int i){return (s[i]!='_' && s[i]!='(' && s[i]!=')');}
signed main(){
	cin>>n>>s;
	for(int i=0;i<n;i++){
		if(s[i]=='(')flag=1;
		if(s[i]==')')flag=0;
		if(flag==1){
			if(pd(i)){if(vis==0)cnt++,vis=1;}
			else vis=0; 
		}
		if(flag==0){
			if(pd(i))len++;//遇到首字母，累加长度
			else maxx=max(len,maxx),len=0;//立即结算，清零累加
		}
	}
}
```

3. 最后输出 `maxx,cnt` 就行了。


---

## 作者：千年陈皮精 (赞：0)

### 思路
逐个输入判断。遇到左括号就把 $s$ 标记为 $1$，表示在括号里，遇到右括号就把 $s$ 标记为 $0$，表示不在括号里；是字母就用 $sum$ 累加，不是字母就清零并判断现在是否在括号内，是就判断单词长度，大于 $0$ 就说明括号里有单词的，用累加器累加（详细解释看代码）。
### 代码
```c++
#include<bits/stdc++.h>
using namespace std;
int n,s,sum,ans,x;
char a;
int main(){
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>a;
		if((a>='a'&&a<='z')||(a>='A'&&a<='Z'))sum++;//是字母就用累机器累加长度 
		else//否则 
		{
			if(s==1&&sum>0)x++;//括号内且字母长度1及以上且在括号里 
			sum=0;//累机器归零（不要放在前面）
		}
		if(a=='(')s=1;//左括号标记为1 
		if(a==')')s--;//右括号清零
		if(s==0)ans=max(sum,ans);//如果在括号外字母长度取最大值 
	}
	cout<<ans<<' '<<x;//输出 
    return 0;//完结撒花 
}
```
# 莫抄袭

---

## 作者：过氧化氢_syq0057 (赞：0)

### 前言

不得不说这题还是挺神奇的（

我觉得我写的是对的

第一次提交 #6WA 了，第二次交 #11WA 了，然后第三次过了（

---

### 正解

一道不错的模拟题/yun

题意就是 ```_``` 分割单词，让你找括号外单词的最长长度和括号内单词的数量~~（别看反了/xyx~~

用一个 ```flag``` 表示当前在不在括号里，然后一个 ```cnt``` 表示一个单词的长度，每次分类：

如果是 ```_``` ，就往后找一个单词，更新答案；如果当前是在括号里且有单词就 ```ans2++``` ，否则 ```ans1``` 取 $\max(ans1,cnt)$

如果是 ```(``` ，就打上标记往后找一个，更新答案；如果有单词 ```ans2++```

如果是 ```)``` ，就把 ```flag``` 置 $0$；

注意有可能刚开始直接是单词，不是 ```_``` 或 ```(``` 。

最后输出就完啦

### Code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <map>
using namespace std;
const int N = 100005;
const int M = 200005;
#define ll long long
const int INF = 0x3f3f3f3f;
const int mod = 1000000007;
int len;
string s;
int ans1, ans2;
bool isok(int x) {
	return (s[x] >= 'A' && s[x] <= 'Z') || (s[x] >= 'a' && s[x] <= 'z');
}
int main() {
	cin >> len;
	getchar();
	getline(cin, s);
	bool flag = 0;//在不在括号里 
	int cnt = 0;//一个单词的长度 
	for (int i=0; i<len; i++) {
		if (isok(i)) {//注意有开头直接是单词的情况 
			i++;
			cnt = 1;
			while (isok(i)) {
				cnt++;
				i++;
			}
			ans1 = max(ans1, cnt);
		}
		if (s[i] == '_') {//情况1 
			i++;
			cnt = 0;
			while (isok(i)) {
				cnt++;
				i++;
			}//一直往后找找到非字母跳出 
			i--;//这里因为for循环还有一个i++，所以要-1 
			if (flag && cnt) ans2++;//如果在括号里并且是一个单词 
			else if (!flag) ans1 = max(ans1, cnt);//不在括号里就更新最大长度 
		}
		else if (s[i] == '(') {//情况2 
			flag = 1;
			i++;
			cnt = 0;
			while (isok(i)) {
				cnt++;
				i++;
			}
			i--;
			if (cnt) ans2++;
		}
		if (s[i] == ')') flag = 0;
		//如果出了括号flag置零（这里注意如果是情况1有可能会判完了直接走不管右括号了） 
	}
	printf("%d %d", ans1, ans2);
	return 0;
}
```

~~（很多注释是我自己写的时候犯的错，可以不用管~~

感觉有点麻烦了呢/yun

完啦qaq

---

## 作者：TheRealJTC (赞：0)

一道练模拟的好题~

对于第一个问，可以创建一个数组 b 和指针 k 和最长单词长度 maxx，再遍历字符串。如果遍历到下划线，或者遍历到两个相邻的括号里的字符，就 b[k++]=i。 最后用 maxx 来存 b 数组里每相邻两个元素的差减一（其实就是一个单词的长度）的最大值。

注意特判如果第一个字符或最后一个字符是字母的情况！

对于第二个问，还是遍历。如果遍历到了一个括号里一个字母后跟一个非字母的配合，单词数量就加一。

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
int b[258];
int main(){
	int n,k=1,maxx=0,word_cnt=0;
	bool flag=1;
	string s;
	scanf("%d",&n);
	cin>>s;
	for(int i=0;i<n;i++){
		if(s[i]=='('){ //遍历括号
			b[k++]=i;
			while(s[i]!=')'){
				i++;
				b[k++]=i;
				if(s[i-1]!='_'&&s[i-1]!='('&&(s[i]=='_'||s[i]==')')){
					word_cnt++;
				}
			}
		}
		if(s[i]=='_'){
			b[k++]=i;
		}
	}
	b[0]=-1,b[k]=n; //特判
	for(int i=1;i<=k+1;i++){
		maxx=max(maxx,b[i]-b[i-1]);
	}
	printf("%d %d",maxx-1,word_cnt);
	return 0;
}
```


---

## 作者：流绪 (赞：0)

模拟，感觉处理各种情况有点麻烦...

我们先定义 maxx 记录最长的单词长度，len记录当前单词长度，cnt记录括号内单词数量。

我们开始模拟，首先当然是最简单的：如果当前位置是字母，len++

然后我先处理括号，我觉得括号两个不一样比较好弄，当然先处理下划线也是可以的，如果第i个是 "(" 且下一个是字母，那就肯定有一个单词了，先 cnt++ ，然后从 i+1 开始循环直到发现 ")",这里注意括号里可能有下划线,那么如果第 j 个位置是下划线,且 j+1 是字母,那么这里肯定也有一个单词,cnt++，遇到 ")"就退出循环,然后令 i=j,因为 j 与 j 前面的都找过了。  

除了循环我们就到了找下划线分开的单词的时候了，如果当前 i 位置是下划线且下一个是字母那么初始化 len=0，我们要开始找了！然后从 i+1 开始循环到不是字母的位置，每次 len++，找完了令 i=j-1，退出循环，然后比较 maxx 与 len，更新答案

下面是 AC 代码，细节注释在代码里了
```cpp
#include<bits/stdc++.h>
#include<cstring>
#define ll long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	char s[1000];
	cin >> s;
	int maxx=-1,len = 0,cnt=0;
	for(int i=0;i<n;i++)
	{
		if(isalpha(s[i]))
			len++;
		if(s[i] == '(')
		{
			if(isalpha(s[i+1]))
				cnt++;
			int j=i+1;
			while(s[j]!=')'&&j<n)//注意 j<n,方式超过长度了
			{
				if(s[j] == '_'&&isalpha(s[j+1]))
					cnt++;
				j++;
			}
			i=j;
		}
		if((s[i]=='_'||s[i]==')')&&isalpha(s[i+1]))
		{
			len = 0;
			int j=i+1;
			while(isalpha(s[j])&&j<n)//注意 j<n,方式超过长度了
			{
				len++;
				j++;
			}
			i=j-1;	//本来是 i=j 但是这里接下来会有第一重循环结束
		}			//会有 i++,所以我们让他先 -1
		maxx = max(len,maxx);
	}
	cout << maxx << " " << cnt;
	return 0; 
}  
```


---

