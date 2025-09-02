# Doggo Recoloring

## 题目描述

Panic is rising in the committee for doggo standardization — the puppies of the new brood have been born multi-colored! In total there are 26 possible colors of puppies in the nature and they are denoted by letters from 'a' to 'z' inclusive.

The committee rules strictly prohibit even the smallest diversity between doggos and hence all the puppies should be of the same color. Thus Slava, the committee employee, has been assigned the task to recolor some puppies into other colors in order to eliminate the difference and make all the puppies have one common color.

Unfortunately, due to bureaucratic reasons and restricted budget, there's only one operation Slava can perform: he can choose a color $ x $ such that there are currently at least two puppies of color $ x $ and recolor all puppies of the color $ x $ into some arbitrary color $ y $ . Luckily, this operation can be applied multiple times (including zero).

For example, if the number of puppies is $ 7 $ and their colors are represented as the string "abababc", then in one operation Slava can get the results "zbzbzbc", "bbbbbbc", "aaaaaac", "acacacc" and others. However, if the current color sequence is "abababc", then he can't choose $ x $ ='c' right now, because currently only one puppy has the color 'c'.

Help Slava and the committee determine whether it is possible to standardize all the puppies, i.e. after Slava's operations all the puppies should have the same color.

## 说明/提示

In the first example Slava can perform the following steps:

1. take all puppies of color 'a' (a total of two) and recolor them into 'b';
2. take all puppies of color 'd' (a total of two) and recolor them into 'c';
3. take all puppies of color 'b' (three puppies for now) and recolor them into 'c'.

In the second example it's impossible to recolor any of the puppies.

In the third example all the puppies' colors are the same; thus there's no need to recolor anything.

## 样例 #1

### 输入

```
6
aabddc
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
3
abc
```

### 输出

```
No
```

## 样例 #3

### 输入

```
3
jjj
```

### 输出

```
Yes
```

# 题解

## 作者：封禁用户 (赞：1)

## CF1025A Doggo Recoloring
[原题链接](https://www.luogu.com.cn/problem/CF1025A)

## 分析

一字符串中个数大于等于 2 的字母可以全部变成另一字母，不限次数。

不难发现，只要字符串中有两个及以上相同字母，一定可以将其转化为同一字母。
## 思路
字符串只由 26 个小写字母组成，桶排统计即可。

首先想到了 STL 中的 map 函数，以 int 类型入桶，可以省去字符串转换步骤。

**注意：字符串长度为 1 时需特判。**

## Code
```cpp
#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
map<int,char>a; //建立映射关系 
int k[27]; //开桶 
int main(){
	int m;cin>>m;
    for(int i=1;i<=m;i++){
    	cin>>a[i];k[a[i]]++; //读入，入桶统计 
    	if(k[a[i]]>=2){ //判出现次数 
		cout<<"Yes";return 0; //end 
		}
    }
    if(m==1){ //特判 m=1 
	cout<<"Yes";
   return 0; //end
	}
    cout<<"No";
    return 0; //循环完毕 无字母>=2 end 
}
```


---

## 作者：BotDand (赞：0)

修改：

$\text{2.20:}$ 增加了空格。

$\text{2.21:}$ 修改了代码的高亮。

# $\text{Problems}$
给定一个长度为 $n$ 的小写字母串。你可以将出现次数大于等于 $2$ 的字母全部变成另一个小写字母。问你最后能否将该小写字母串的所有字母变成同一个字母。如果可以，输出 $\texttt{"Yes"}$ ,否则输出 $\texttt{"No"}$ 。
# $\text{Answer}$
很简单。

如果有一个字母出现的次数大于 $2$，那么这个字母一定能转成另一个字母，另一个字母同理也能转成另一个字母。

即三个字母 $\text{A,B,C}$ ，若 $\text{A}$ 出现的次数大于等于 $2$ （假设为 $2$ ），那么一定能转换为 $\text{BB}$ ，加上原来的 $\text{B}$ ，即 $\text{BBB}$ ，同理 $\text{BBB}$ 可转化为 $\text{CCC}$ ，加上原来的 $\text{C}$ ，即 $\text{CCCC}$ 。

最后还需特判$\text{n=1}$的情况。
# $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char ch;
int a[32];
int main()
{
    cin>>n;
    if(n==1) return puts("Yes"),0;
    for(int i=0;i<n;++i) {cin>>ch;a[ch-97]++;}
    for(int i=0;i<26;++i) if(a[i]>=2) return puts("Yes"),0;
    puts("No");
    return 0;
}
```


---

## 作者：skym (赞：0)

## 分析

第一眼看到题目我想到的是强行模拟。   

但是仔细寻找一下规律发现，只要有一个字母数量大于等于2，最终就能变成同一个字母。   

比如这样一个字符串：

```
abcdea   

把 a 变成 b    

bbcdeb

把 b 变成 c   

cccdec

把 c 变成 d  

dddded

把 d 变成 e   

eeeeee

```

这个题还需要特判字符串长度为1的情况，长度为1时显然应该输出“Yes”。   

另外，用桶排可以实现 **O(n)** 的复杂度，完全没必要用两层循环，毕竟只有26个字母，也不会炸空间。   

## 代码
```cpp
#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
using namespace std;
string s;
int n,t[27];
int main(){ 
	scanf("%d",&n);
	cin>>s;
	if(n==1){//特判长度为1的情况
		printf("Yes");
		return 0;
	}
	for(int i=0;i<n;i++){
		t[s[i]-'a']++;
	}
	for(int i=0;i<26;i++){
		if(t[i]>=2){//有一个字母出现了两次或两次以上
			printf("Yes");
			return 0;
		}
	}
	printf("No");//上面两种情况都不成立的话就不行，输出“No”
	return 0;
} 
```

### ~~人生第一篇题解~~

---

## 作者：Keep_RAD (赞：0)

第一遍看：哦？强模拟？不行不行，换一题；

第二遍看：哦！原来是这样！让我们来模拟一下，找一个规律：

首先是这样一个串:

```
 jsdslkhv
```

如果按感觉说，那么多不一样的，应该是做不到，但说这句话的人看一看下面的过程：

```
jsdslkhv

把s改成d：

jdddlkhv

把d改成l：

jllllkhv

把l换成k

jkkkkkhv

把k换成h

jhhhhhhv

把h换成j

jjjjjjjv

把j换成v

vvvvvvvv
```
发现了吗？
只要发扬愚公移山的精神，能改一个，剩下的经过不停的“传染”就可以把串统一了

而出现次数$k>=2$就可以改，那么代码来了：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string a;
int main()
{
	cin>>n>>a;
	if(a.size()==1) //长度为一它本身就是一个全都一样的串
	{
		puts("Yes");
		return 0;
	}
   int s=a.size(); 
   for(int i=0;i<s;++i) //数据量不大，完全可以一个一个枚举，相比于桶还省空间
    {
		for(int j=i+1;j<s;++j)
       {
			if(a[i]==a[j])
        {
				puts("Yes");
				return 0;
			}
		}
	}
	puts("No");
	return 0;
}
```
我们已经知道了这一题的做法，

那么这道题如果用桶，该怎么做呢？

很简单，可以读入之后判断是否出现过，没有就标记一下，出现过表明已经出现一次了，加上这个的这一次，超过了两次，输出`Yes`,`return 0`,结束；

到最后仍没有跳转，说明没有出现两次的字符，输出`No`,结束

附上桶的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int b[30]; //开桶
int main()
{
	int n;
	string a;
	cin>>n>>a;
	int s=a.size();
	if(a.size()==1) //同上
	{
		puts("Yes");
		return 0;
	}
	for(int i=0;i<s;i++)
	    if(b[s[i]-'a']) 
        {
        	puts("Yes");//出现过
        	return 0;
        }
	puts("No");
	return 0;
}
```

---

## 作者：BeetyX (赞：0)


分析：虽然题目很简单，但是简单里有一些花里胡哨。我们读完题后可以先来看看样例：

```
6
aabddc
```
第一个n自然不用解释，我们来看看下面这个字符串：

```
aabddc
```
①既然要最终转换为同一个字母，那么我们就尽可能地要多创造一些形如“aa”“bbb”“cccc”这种的单字母字符串（长度大于1）。很容易我们就找到了形如此类的第一个字符串：aa。

②可是我们也不能乱变，我们的最终目的是转换为同一个字母，字符串中肯定有其他的单个的字母，我们只要把这个单字母字符串，转换为这个字母，就能实现①中所要实现的那个目的。还是拿那个样例举例，找到"aa"后就可以看到后面的单个字母"b"，那我们就把"aa"变成"b"，最终就会变成：

```
bbddc
```
③以此类推，后面也是同样的步骤，只要找到一个单字母字符串，一切都好办，下面是完整的样例分析：

aabddc→bbddc→ddddc→cc→（任意一个字母即可）

总结：以上所有的步骤，都是归根于“找到一个单字母的字符串”的前提下，只要有了单字母字符串，我们就能不断循环，去创造单字母字符串，最终化多合一。所以我们的解题思路也有了：在最初的字符串中寻找单字母字符串，用for循环枚举两个变量，如果相同，那么就能判断这个字符串是单字母字符串，也就能输出“Yes”。

代码如下
------------
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s;					//定义字符串
    int n;					//个人觉得这个n挺鸡肋的
    cin>>n>>s;
    int len=s.length();		                //定义字符串长度，方便后面循环
    if(len==1)                                  //特判，因为题目中说了（n>=2）
    {
        cout<<"Yes"<<endl;
        return 0;                               //记得写return 0
    }
    for(int i=0;i<len;i++)                      //第一个循环，枚举第一个变量
    {
        for(int j=i+1;j<len;j++)	        //第二个循环
        {
            if(s[i]==s[j])                      //如果次数出现了两次，就能判断这个长字符串中包含单字母的字符串
            {
                cout<<"Yes"<<endl;              //也就可以直接写Yes，程序结束
                return 0;
            }
        }      
    }
    cout<<"No"<<endl;                           //循环了一圈也没有发现单字母字符串，输出No
    return 0;
}
```


---

## 作者：thomas_zjl (赞：0)

首先我们来看一看样例是如何通过一些奇妙的变换来得到我们想要的结果。

输入。
```
6
aabddc

```
首先我们看到有$2$个$a$于是就可以换成下面的样子。
```
bbbddc
```
这样我们就有$3$个$b$了，可以在进行变换，就成了下面的样子。
```
dddddc
```
我们有$5$个相同的字符了，在进行变换就可以得到下面的样子。
```
cccccc
```
这样我们就可以完成题目给我们的任务了。

同时我们也知道。

> 只要这个字符里面有$2$个相同的字符就可以完成操作了。

**还要注意特判$n$为$1$的结果**

接下来就是代码了。

```
#include<bits/stdc++.h>
using namespace std;
int a[26]={0};
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		char s;
		cin>>s;
		a[s-'a']++;//类似于桶排序，把一个数组分为0~26，对应字母a~z。
	}
	for(int i=0;i<26;i++)
	{
		if(a[i]>1)//如果这个数字的出现次数大于1。
		{
			cout<<"Yes";//直接输出Yes。
			return 0;
		}
	}
	if(n==1)//特判n=1。
	{
		cout<<"Yes";//那一定要输出Yes。
	}
	else
	{
		cout<<"No";//其他的输出No。
	}
	return 0;
}

```



---

## 作者：happybob (赞：0)

水题！

STL大法好！

先来分析一下，可以得知，只要有一种字符出现过两次以上，就可以和别的字符合并，就是Yes，注意字符串长度为1也是Yes

那怎么统计呢？对了，map！！！

代码如下（char[]和unordered_map和string都有哦）:

```cpp
#include <iostream>
#include <cstring>
#include <unordered_map>
using namespace std;

unordered_map <char, int> mp;

string a;

int b;

int main()
{
    cin >> b >> a;
    int x = a.length();
    for(int i = 0; i <= x - 1; i++)
    {
        mp[a[i]]++;
    }
    for(unordered_map <char, int>::iterator it = mp.begin(); it != mp.end(); ++it)
    {
        if(it -> second >= 2)
        {
            cout << "Yes\n";
            return 0;
        }
    }
    cout << (x == 1 ? "Yes" : "No") << endl;
    return 0;
}
```

以上是string+unordered_map

```cpp
#include <iostream>
#include <cstring>
#include <map>
using namespace std;

map <char, int> mp;

string a;

int b;

int main()
{
    cin >> b >> a;
    int x = a.length();
    for(int i = 0; i <= x - 1; i++)
    {
        mp[a[i]]++;
    }
    for(map <char, int>::iterator it = mp.begin(); it != mp.end(); ++it)
    {
        if(it -> second >= 2)
        {
            cout << "Yes\n";
            return 0;
        }
    }
    cout << (x == 1 ? "Yes" : "No") << endl;
    return 0;
}
```
map+string的

```cpp
#include <iostream>
#include <cstring>
#include <map>
using namespace std;

map <char, int> mp;

char a[100005];

int b;

int main()
{
    cin >> b >> a;
    int x = strlen(a);
    for(int i = 0; i <= x - 1; i++)
    {
        mp[a[i]]++;
    }
    for(map <char, int>::iterator it = mp.begin(); it != mp.end(); ++it)
    {
        if(it -> second >= 2)
        {
            cout << "Yes\n";
            return 0;
        }
    }
    cout << (x == 1 ? "Yes" : "No") << endl;
    return 0;
}
```
char+map

```
#include <iostream>
#include <cstring>
#include <unordered_map>
using namespace std;

unordered_map <char, int> mp;

char a[100005];

int b;

int main()
{
    cin >> b >> a;
    int x = strlen(a);
    for(int i = 0; i <= x - 1; i++)
    {
        mp[a[i]]++;
    }
    for(unordered_map <char, int>::iterator it = mp.begin(); it != mp.end(); ++it)
    {
        if(it -> second >= 2)
        {
            cout << "Yes\n";
            return 0;
        }
    }
    cout << (x == 1 ? "Yes" : "No") << endl;
    return 0;
}
```
char+unordered_map

速度最快484ms，后来评测慢一些500多600ms的样子，unordered_map用hash的可能比map快一些，c++11的

---

## 作者：KagurazakaKano (赞：0)

## UPDATE:2018.8.31 更正了复杂度

思路：容易发现，只要某个字符出现了大于等于两次，那么这个肯定是有解的（假设某个字符出现了两次，其余字符出现了0次或1次，那么根据题意我们可以把出现两次的转换为某个出现1次的，这样就减少了一个不同的字符，不断重复，我们必定可以拿到只有一个字符的结果），具体统计我们可以使用桶排的思想。

于是模拟写出了代码：
```
#include <bits/stdc++.h>

using namespace std;

char f[100005];

int a[30];

int main(){
    int n;
    scanf("%d",&n);
    scanf("%s",f);  //读入
    for(int i = 0; i < strlen(f); i++){
        a[f[i] - 'a' + 1]++; //类似于桶排的统计
    }
    for(int i = 1; i <= 26; i++){
        if(a[i] >= 2){  //如果某个字符出现了两次以上
            printf("Yes\n");
            return 0;
        }
    }
    printf("No\n");  //如果还在运行程序说明是无解
    return 0;
}
```

啥玩意？第四个点是WA？吓得我赶紧打开CF看了下提交记录，发现了一个~~坑~~自己没想到的情况：
```
如果 n = 1 那么肯定是可行的，这点我没有考虑到。
```

于是修改下，再次提交：
```
#include <bits/stdc++.h>

using namespace std;

char f[100005];

int a[30];

int main(){
    int n;
    scanf("%d",&n);
    scanf("%s",f);
    for(int i = 0; i < strlen(f); i++){
        a[f[i] - 'a' + 1]++;
    }
    if(n == 1){  //特判n = 1的情况
        printf("Yes\n");
        return 0;
    } else {
        for(int i = 1; i <= 26; i++){
            if(a[i] >= 2){
                printf("Yes\n");
                return 0;
            }
        }
    }
    printf("No\n");
    return 0;
}
```
![TLE](https://cdn.luogu.com.cn/upload/pic/30368.png)

发现是玄学TLE。是因为**strlen一次的时间是$\Theta (n)$**的，因此就是完全退化成$\Theta(n^2)$了/

于是考虑在线做加一点优化，修改了下代码：
```
#include <bits/stdc++.h>

using namespace std;

char f[100005];

int a[30];

int main(){
	int n;
	scanf("%d",&n);
	if(n == 1){  //先判断，省点时间owo
		printf("Yes\n");
		return 0;
	}
	scanf("%s",f);
    int qwq = strlen(f);
	for(int i = 0; i < qwq; i++){
		a[f[i] - 'a' + 1]++;  //桶排思想统计
		if(a[f[i] - 'a' + 1] == 2){  //放在循环里面判断，可以省点时间
			printf("Yes\n");
			return 0;
		}
	}
	printf("No\n");
	return 0;
}
```

---

