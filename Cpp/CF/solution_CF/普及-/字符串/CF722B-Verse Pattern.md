# Verse Pattern

## 题目描述

You are given a text consisting of $ n $ lines. Each line contains some space-separated words, consisting of lowercase English letters.

We define a syllable as a string that contains exactly one vowel and any arbitrary number (possibly none) of consonants. In English alphabet following letters are considered to be vowels: 'a', 'e', 'i', 'o', 'u' and 'y'.

Each word of the text that contains at least one vowel can be divided into syllables. Each character should be a part of exactly one syllable. For example, the word "mamma" can be divided into syllables as "ma" and "mma", "mam" and "ma", and "mamm" and "a". Words that consist of only consonants should be ignored.

The verse patterns for the given text is a sequence of $ n $ integers $ p_{1},p_{2},...,p_{n} $ . Text matches the given verse pattern if for each $ i $ from $ 1 $ to $ n $ one can divide words of the $ i $ -th line in syllables in such a way that the total number of syllables is equal to $ p_{i} $ .

You are given the text and the verse pattern. Check, if the given text matches the given verse pattern.

## 说明/提示

In the first sample, one can split words into syllables in the following way:

`in-tel<br></br>co-de<br></br>ch al-len-ge<br></br>`Since the word "ch" in the third line doesn't contain vowels, we can ignore it. As the result we get $ 2 $ syllabels in first two lines and $ 3 $ syllables in the third one.

## 样例 #1

### 输入

```
3
2 2 3
intel
code
ch allenge
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4
1 2 3 1
a
bcdefghi
jklmnopqrstu
vwxyz
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
4
13 11 15 15
to be or not to be that is the question
whether tis nobler in the mind to suffer
the slings and arrows of outrageous fortune
or to take arms against a sea of troubles
```

### 输出

```
YES
```

# 题解

## 作者：zhang_kevin (赞：8)

$\verb!UPD on 2022-8-24:!$ 修改一些 $\LaTeX$，美化文章。
 
[题目传送门](https://www.luogu.com.cn/problem/CF722B)

## 题意简述
给定 $n$ 句话，判断每句话是否都含有正确个数的元音。

## 做题思路
每次都暴力枚举，得到元音个数，判断是否符合要求即可。

问题在于字符串的读入，正常的 `cin` 会因为空格而停止，所以要使用 `getline(cin, str)` 进行**带空格读入**，它每次**遇到换行符才停止读入**。其中 $\verb!str!$ 为希望读入的字符串。

## AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001], n, ans;
string s;
int main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
	}
	getchar();//不能省，吸收掉换行
	for(int i = 1; i <= n; i++){
		getline(cin, s);//getline输入
		ans = 0;
		int len = s.length();
		for(int j = 0; j <= len - 1; j++){
			if(s[j]=='a'||s[j]=='e'||s[j]=='i'||s[j]=='o'||s[j]=='u'||s[j]=='y'){
				ans++;//是元音个数就加1
			}
		}
		if(ans != a[i]){//有一个不相同就输出 NO
			cout << "NO" << endl;
			return 0;//拜拜程序
		}
	}
	cout << "YES" << endl;
	return 0;
}
```

---

## 作者：liangbowen (赞：4)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF722B)

[更好的阅读体验？](https://www.luogu.com.cn/blog/liangbowen/solution-cf722b)

这是一道简单的字符串练手题。

## 思路

每次暴力计数，是否为元音。最后判断是否满足题意即可。

重点是字符串读入问题。

由于字符串读入部分**含有空格**，因此使用 `getline(cin, str)` 读入，其中 $\texttt{str}$ 是字符串。

我们把 `getline(cin, s)` 称为**整行读入**。它遇到换行符就会停止。

但是，我们发现 `cin` 是不会读入换行符的。所以，如果我们要连用 `cin` 和 `getline`，需要先把换行符吃掉。

具体如下：

```cpp
int n;
string s;
cin >> n;  //读入 n。
getline(cin, s); //把换行符吃掉。
getline(cin, s); //实际上，这里才会读入到 s 字符串。
```

那么，这道题的代码就呼之欲出了。

## 代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
void fastio()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}
int a[105], num[105];
int main()
{
    fastio();
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> num[i];
    string s;
    getline(cin, s); //把换行符吃掉先。
    for (int i = 1; i <= n; i++)
    {
        getline(cin, s);
        int len = s.length(), cnt = 0;
        for (int j = 0; j < len; j++) cnt += (s[j] == 'a' || s[j] == 'e' || s[j] == 'i' || s[j] == 'o' || s[j] == 'u' || s[j] == 'y');
        if (cnt != num[i]) //按题意判断。
        {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";
    return 0;
}
```

希望能帮助到大家！

---

## 作者：BlanketRice (赞：1)

这道题其实非常简单，但难就难在一个小陷阱上。

我们先将基本思路，这道题的意思是：你现在有 $ n $ 句话，还有他们分别对应的应有的元音个数，现在要你判断每句话是否都含有正确的元音 $ a,e,i,o,u $ 个数。

基本思路是输入 $ n $ 和 $ n $ 个数 $ ai $，再输入 $ n $ 个字符串，依次记录每个字符串原因的个数，最后判断即可。

但是这里有一个陷阱，` cin ` 和 ` scanf ` 读入不会多读，即读到空格就会停止，但是样例给出的字符串可以包含空格，所以我们要用 ` getline ` 来读入。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int a[1000005];
inline bool check (char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}
signed main () {
    int n;
    cin >> n;
    for (register int i = 1;i <= n;++ i) cin >> a[i];
    getchar ();
    for (register int i = 1;i <= n;++ i) {
        getline (cin, s);
        int ans = 0;
        for (register int j = 0;j < s.length ();++ j) ans += check (s[j]);
        if (ans != a[i]) {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
    return 0;
}
```

非常简单的一道题啊。。。

---

## 作者：OoXiao_QioO (赞：1)

# 题目描述

你现在有 $n$ 句话，还有他们分别对应的应有的元音个数，现在要你判断每句话是否都含有正确的元音（$\verb!a,e,i,o,u,y!$）个数。

# 思路

$y$ 竟然是元音？我一开始没有看到 $y$ 是元音，所以被坑了十分钟，我好菜。。。。

这道题比其他字符串的题要简单点，不过这输入却挺难搞，卡了我五六分钟。

可以看到样例一的第三组数组 $\verb!ch allenge!$，中间有一个空格，所以我们不能用普通的读入字符串方式 ```scanf``` 或者 ```cin```，因为 ```scanf``` 和 ```cin``` 是不读空格和回车的（必须牢记这一点，下文中还会出现！），所以我们只能用一种新的读入方式（话说以前是不是可以用 ```gets```啊，挺好用的，只可惜现在已经移除了，不然这道题直接可以去红题玩了）。看其他大佬用了 ```getline``` 来读入空格，蒟蒻的方法和他们不一样，我是用 ```getchar()``` 来读入的，直到读进空格为止。

每读入一个字符都来判断一下是不是元音（注意 $y$！！！）,如果是元音，计数器 $\verb!cnt!$ $+1$，最后判断一下是否满足条件就行了。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
bool pd(char x)//判断是否为元音函数，是，返回 1，否则返回 0. 
{
	return (x=='a'||x=='e'||x=='i'||x=='o'||x=='u'||x=='y');
}
int main()
{
	//定义
	
	int n,a[101],i,j,cnt;// cnt 用来统计每个句子中元音出现的次数。 
	char c;
	
	//输入 
	
	cin>>n;
	for(i=1;i<=n;i++)
		cin>>a[i];
	getchar();//大大大大大坑点！！cin 是不读回车的，这意味着我们输入完 a 数组后，后面打的那个回车会进入到下面的读入环节，从而产生读入错误的大麻烦！我们一定要读掉后面的回车程序才能正常运行！！ 
	
	//处理 
	
	for(i=1;i<=n;i++)
	{
		cnt = 0;//到新的句子，cnt 清空。 
		while((c = getchar())!='\n')//重复执行直到读进换行为止。 
		{
			if(pd(c))//判断一下字符 c 是否为元音。 
				cnt++;//是的话，计数器 +1。 
		}
		if(cnt!=a[i])//如果不符合条件 
			return printf("NO\n"),0;//直接输出 NO，程序结束。 
	}
	printf("YES\n");//否则全部满足条件，输出 YES。 
	return 0;
}
```


---

## 作者：shipeiqian (赞：1)

# 思路

这道题主要是利用 ```getline``` 无视空格的特点来读入，然后记录元音字母出现次数并判断的原理来解题的。

# AC CODE
```cpp
#include <iostream>
#include <string>
using namespace std;
int main(){
	int n,a[105];
	cin >>n;
	for(int i=1;i<=n;i++){
		cin >>a[i];//读入各行元音数量
	}
	getchar();//吞掉换行符
	for(int i=1;i<=n;i++){
		string s;
		int cnt=0;//计数器
		getline(cin,s);//利用getline读入
		for(int j=0;j<s.size();j++){
			if(s[j]=='a'||s[j]=='e'||s[j]=='i'||s[j]=='o'||s[j]=='u'||s[j]=='y'){
				cnt++;//发现是元音字母，计数器就增加
			}
		}
		if(cnt!=a[i]){
			cout <<"NO";
			return 0;//如果发现不对，就直接结束程序
		}
	}
	cout <<"YES";//如果前面没被判断到，就输出“YES”
	return 0;
}

```

---

## 作者：ivyjiao (赞：0)

## 题意

给定 $n$ 句话，判断每个第 $i$ 句话是否含有 $a_i$ 个数的元音。

## 做法

先输入每个 $a_i$，再输入每一句话，判断是否合法即可。

注意：

1. 正常的 `cin` 会因为空格而停止，所以我们要用 `getline` 来做。它每次遇到换行符才停止读入，**我们要消掉第一个换行符。**

2. 字符串下标是从 `0` 开始的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000001],n;
string str;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    getline(cin,str);//消掉换行符
    for(int i=1;i<=n;i++){
        int cnt=0;
        getline(cin,str);
        for(int j=0;j<str.length();j++) //从0开始！！！
        	if(str[j]=='a'||str[j]=='e'||str[j]=='i'||str[j]=='o'||str[j]=='u'||str[j]=='y') cnt++;
        if(cnt!=a[i]){//如果不匹配
            cout<<"NO";
            return 0;
        }
    }
    cout<<"YES";
}
```


---

## 作者：zbk233 (赞：0)

# 题意简述

给定 $n$ 句话，判断每句话是否都含有正确的元音个数。

# 解题思路

这道题本身不难，但是有很多要注意的细节。

1. 这道题输入的字符串是带空格的，也就是说一定要使用能输入空格的输入方式，例如 ```getline``` 或 ```gets```，我这里选择了 ```gets```。

2. 题中规定的元音字母不要忘了除 a,e,i,o,u 以外还有 y。

数据范围小，二重循环就行了。

```cpp
#include <cstring>
#include <iostream>
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, a[105], sum;
	bool flag = 1;
	char s[105];
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++)
	{
		gets(s);
		sum = 0;
		for (int j = 0; j < strlen(s); j++)
		{
			if (s[j] == 'a' || s[j] == 'e' || s[j] == 'i' || s[j] == 'o' || s[j] == 'u' || s[j] == 'y')
			{
				sum++;
			}
		}
		if (sum != a[i])
		{
			flag = 0;
			break;
		}
	}
	flag ? cout << "YES" : cout << "NO";
	return 0;
}
```


---

## 作者：MLCabc (赞：0)

**一些dalao认为此题是水题，蒟蒻却认为这是一道好题。**

# 前言
在 CCF 使用 C++ 14 标准后，gets 被禁用的情况下，对于字符串的读入，不可避免地需要使用 getline 等输入方法，而这题便是很好的练手题。

# 分析
### 1.大致题意
输入 $n$ 个字符串，统计里面  **a,e,i,o,u,y** 的个数是否符合给出的个数

### 2.输入格式
此题具有多种方式均可输入，我主要测试了一下几种

- getchar：用这种方式需要一个一个输入字符，要注意换行符等，代码实现较为繁琐，但可以 AC。

- fgets：这种方式可以用 char 的类型稳定地输入每行数据，但相较于 getline 还是略微繁琐（平时用的不多，也容易出锅），依然可以 AC。

- gets：**绝对不要使用！原因见前言。**

- getline：推荐使用，可以输入一行的 string 字符串，忽略空格且在换行时停止输入。**注意：此题输入时需要先将上一行的换行读入，否则会出锅。**

### 3.输出格式
注意大小写，最好在输出“NO”后直接结束
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int num[100005];
int main(){
	string s;
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>num[i];		
	}
	getchar();
	for(int i=1;i<=n;i++){
		int cnt=0;
		getline(cin,s);
		for(int j=0;j<=s.size()-1;j++){
			if(s[j]=='a'||s[j]=='e'||s[j]=='i'||s[j]=='o'||s[j]=='u'||s[j]=='y'){
				cnt++;				
			}
		}  
		if(cnt!=num[i]){
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES";
	return 0; 
}
```



---

## 作者：爬行者小郑 (赞：0)

## 这题一定要注意吸收换行
楼上的同学解释得有点问题。。。之所以在循环查找每一个字符串之前还要有一个getline，是因为要吸收上一行输入数组之后的换行，要不然就会带着字符串一起输入进去。
```cpp
#include <iostream>
#include <cstring>//后面要用到strlen
using namespace std;
int n,p[105];//p就是题目里面说的p数组
char x[105][1005];//这里其实不太需要2维的，但是每个字符串都不是很大，就这样了
int main()
{
	cin>>n;//输入n
	for(int i=1;i<=n;i++)cin>>p[i];//输入p数组
	getchar();//一定要吸收掉一个换行
	for(int i=1;i<=n;i++)//每个都遍历一遍
	{
		cin.getline(x[i],1000);//getline输入可以把整行都放进去
		int len=strlen(x[i]);//len一定不能放在循环的地方，要不然每次都会执行一遍strlen操作，就慢到姥姥家了
		int ans=0;//统计实际的元音个数
		for(int j=0;j<len;j++)//逐位遍历字符串
		{
			if(x[i][j]=='a'||x[i][j]=='e'||x[i][j]=='i'||x[i][j]=='o'||x[i][j]=='u'||x[i][j]=='y')//判断此位是否为“元音”字母
			{
				ans++;//统计个数+1
			}
		}
		if(ans!=p[i])//如果没有对上，不用继续执行，直接退出
		{
			cout<<"NO"<<endl;//输出NO
			return 0;//退出程序
		}
	}
	cout<<"YES"<<endl;//输出YES
	return 0;//养成好习惯，竞赛中没有这个直接爆零，虽然洛谷中没有关系
}
```
这道题虽然思路简单，很水，但是还是考察一些细节的

---

## 作者：Jr_Zlw (赞：0)

### 这是一道很水的题

其实哪怕是二重循环都能过，考点估计就是getline了

但不过不知道为什么，getline和gets都要在循环外申明，不然竟然不能输入（我因此卡了好久）

为了能够A掉这道灰题（显然应该成为红题），我们应该有如下步骤：

```
1、依次输入字符串

2、从头到尾统计元音数量（if里面打个表）

3、如果已经统计到超过答案的元音数量,直接跳出，（其实这一步加不加没啥所谓，如果数据量太大不加更好）

4、最后把统计的数量与答案对比，（因为它要5、求全部都相等才输出YES，所以如果不相等，直接输出NO并跳出程序（return 0真好！！）

5、于是最最重要的部分就出来了
```
那么我就再调了一下getline就满屏绿色了（CF的题做完了真爽）

那么，双手奉上AC代码，预祝本题能跳出灰题，变成红题：

```
#include<bits/stdc++.h>
#define r(a,b,c) for(int c=a;c<=b;++c)
using namespace std;
int a[100001],n,ans;
string m;
int main()
{
	cin>>n;
	r(1,n,i)cin>>a[i];
	getline(cin,m);//申明！一定要注意
	r(1,n,i)//define真好，相当于for(int i=1;i<=n;++i)
	{
		getline(cin,m);ans=0;
		int len=m.length();
//		cout<<len<<' ';你可以用来调试什么的
		r(0,len-1,j)
		{
			if(m[j]=='a'||m[j]=='e'||m[j]=='i'||m[j]=='o'||m[j]=='u'||m[j]=='y')ans++;//一个用if打的表，比用数组打表快一点
		}
//		cout<<ans<<endl;
		if(ans!=a[i])
		{
			cout<<"NO";
			return 0;//跳出程序，减少时间，时间珍贵！
		}
	}
	cout<<"YES";
	return 0;
}
```

### 大功告成

---

## 作者：开始新的记忆 (赞：0)

题目大意：你现在有n句话，还有他们分别对应的应有的元音个数，现在要你判断每句话是否都含有正确的元音（**a,e,i,o,u,y**）个数。

思路：暴力模拟
注意点：1.元音不止aeiou，还有个y（我第一次wa就因为这）。2.每个句子之间有空格，所以要用getline或者gets输入。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans[100010],flag=1;
string a;

int main()
{	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>ans[i];
	getline(cin,a);
	for(int i=1;i<=n;++i)
	{
		int sum=0;
		getline(cin,a);
		for(int j=a.size()-1;j>=0;--j)
		    if(a[j]=='a' || a[j]=='e' || a[j]=='i' || a[j]=='o' || a[j]=='u' || a[j]=='y')
		    	sum++;
		if(sum!=ans[i])
			flag=0;
	}
	if(flag)
		cout<<"YES"<<endl;
	else
		cout<<"NO"<<endl;
	return 0; 
}
```


---

## 作者：Tobiichi_Origami (赞：0)

**这道题其实很简单，只不过需要很细心。**

**大体思路**

用 $\texttt{getline}$ 输入字符串，然后判断是否为元音字母，**切记元音字母是** $\texttt{a e i o u y}$。如果输入的元音字母个数与实际的元音字母相等，输出 $\texttt{YES}$，否则输出 $\texttt{NO}$。

可是！$\texttt{getline}$ 必须要上一行换行才能正常使用，所以还要加上一个 $\texttt{getline}$ 才能 $\texttt{AC}$。

**贴代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000010];
string s;
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];//输入
    getline(cin,s);//切记消掉换行符！
    for(int i=1;i<=n;i++)
    {
        int cnt=0;//初始化
        getline(cin,s);//输入
        for(int j=0;j<s.length();j++)
            if(s[j]=='a'||s[j]=='e'||s[j]=='i'||s[j]=='o'||s[j]=='u'||s[j]=='y'){
            //判断是否为元音字母
                cnt++;//计数器+1
            }
        if(cnt!=a[i])//数量不符
        {
            cout<<"NO"<<endl;//输出
            return 0;//直接结束
        }
    }
    cout<<"YES"<<endl;
    return 0;
}
```


---

## 作者：EwunebopR (赞：0)

# 大致题意
如果题目给出的 $n$ 句话都有**数量符合**的*元音*， 那么输出 `YES`，否则输出 `NO`。

# 思路分析
这一道题**唯一**的难点就是输入文件的每一句话里*可能*含有空格，因此需要使用**换行结束**的 `getline(cin, s)` 或者 `gets(s)`，这里我选择 `getline`，但是由于 `cin` 默认不会将输入流中的 `\n` 删除，所以应该在输入字符串之前先在 `getline` 一下将换行符删除。那么答案就呼之欲出了，下面是完整代码。

# 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;  // 先导一个库^_^
string s;  // 每一行的话
int n, vowel[110];  // 话的句数和每句话应有的元音个数
bool flag = true;
bool isVowel(char _c) {
    // 定义一个判断字符是否为元音的函数
    if (_c == 'a' || _c == 'e' || _c == 'i' || _c == 'o' || _c == 'u' 
    || _c == 'y') return true;
    return false;
}
int main() {
    cin >> n;  // 读入行数
    for (int i = 1; i <= n; i++) {  // 循环读入每句话应有的元音个数
        cin >> vowel[i];
    }
    getline(cin, s);
    for (int i = 1; i <= n; i++) {
        getline(cin, s);
        int cnt = 0;  // 计数s中的元音
        for (int j = 0; j < s.size(); j++) {
            // 循环遍历s查询元音个数
            if (isVowel(s[j]))
                cnt++;
        }
        if (cnt != vowel[i]) {
            // 如果数量不符直接退出输出NO
            flag = false;
            break;
        }
    }
    cout << (flag ? "YES" : "NO") << endl;
    return 0;
}
```

---

