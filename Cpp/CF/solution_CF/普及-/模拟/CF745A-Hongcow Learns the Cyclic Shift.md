# Hongcow Learns the Cyclic Shift

## 题目描述

Hongcow正在学习拼写单词！这天，他（他？）的老师给了他一个需要拼写的单词。作为一个好学生，他很快就学会了如何拼写。  
Hongcow决定搞个大新闻。他从刚学会拼写的单词开始，每次把最后一个字符移到单词开头。他称此为一次变换。他可以进行多次变换，例如：单词"abracadabra"可以变成"aabracadabr"、"raabracadab"等等  
现在，他想知道通过变换能变成几个不同的单词，包括初始单词

## 样例 #1

### 输入

```
abcd
```

### 输出

```
4
```

## 样例 #2

### 输入

```
bbb
```

### 输出

```
1
```

## 样例 #3

### 输入

```
yzyz
```

### 输出

```
2
```

# 题解

## 作者：FuriousC (赞：16)

[题目传送门](https://www.luogu.com.cn/problem/CF745A)

### 思路

其实不用一个一个枚举，这里给出一种比较巧的方法

### 举个栗子：

对于`abaa`这个字符串，我们将这个字符串重复一遍，变成`abaaabaa`

从第二个字符`b`开始查找：

`b`$\Rightarrow$`a`，continue

`a`$\Rightarrow$`b`，continue

`a`$\Rightarrow$`a`，break

则此时答案为跳出循环时查找的最后一个字符`a`的下标$3$

通过验算发现：`abaa`能变成`baaa`，`aaba`，`aaab`，答案正确

此时不用循环，直接用`string`库里的`find`函数即可

[不知道find的戳我](https://blog.csdn.net/shujh_sysu/article/details/52026108)

### 证明:

本题题意是求变换后不与原字符串重合的字符串的个数

先讲一种朴素方法：

还是沿用上面的例子，先将`abaa`首位的`a`移至末尾，得到`baaa`，判断首位的`b`和原字符串首位的`a`不相等

此时的操作就等于上文中的“将第二个字符`b`与原字符串的第一个字符`a`比较”

同理，第二种情况，将`baaa`首位的`b`移至末尾，变成`aaab`，再比较首位的`a`与原字符串首位的`a`，就等于上文中的“将第三个字符`a`与原字符串的第二个字符`b`比较”

这时，这种朴素方法得到的结果是$2$，而此时查找到的字符`a`在原字符串中的下标也是$2$，故上文所述的算法正确

因此，两种方法得到的结果是一样的

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string str,str1;
int main(){
    cin>>str;
    str1=str+str;//重复一遍 
    cout<<str1.find(str,1);//从下标为一的字符开始找 
    return 0;
}
```

---

## 作者：Moon_Lighter (赞：7)

## 解题思路
将每个新字符串存入 $set$ 中，因为它可以字符串序列进行去重。最后判断存入了多少个就行了。

**小技巧**

这道题可以把原字符串再抄一遍加在后面，用循环从第一个字符到原字符串最后一个字符每次往后截取原字符串的长度，这样就能得到每个新字符串。


---

### [$\color{#52C41A}\texttt{AC CODE}$](https://www.luogu.com.cn/record/51373888)



```cpp
#include<bits/stdc++.h>//万能头文件...
using namespace std;
set<string>s;//set是用来存字符串的。
int main()
{
    string a;
    int n;
    cin>>a;
    n=a.size();
    a=a+a;
    for(int i=0;i<n;i++)//从第一个字符到原字符串最后一个字符每次往后截取。
    {
        string b;//生成一个空字符串b。
        for(int j=0;j<n;j++)
       	{
            b+=a[i+j];
        }
            s.insert(b);//insert将指定对象插入到列表中的指定位置。
        }
            printf("%d\n",s.size());
    return 0;//结束。
}
```

---

## 作者：__main__ (赞：3)

将原字符串复制一遍，然后用循环每次向后移一位，相当于每次将第一个字母移到最后。将生成的每个字符串丢到`set`里去重，答案就是`set`的长度。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	set<string> s;
	char str[105];
	scanf("%s", str);
	int len = strlen(str);
	for (int i = 0; i < len; ++i)
		str[len + i] = str[i];
	for (int i = 0; i < len; ++i)
		s.insert(string(str + i, str + len + i));
	printf("%d\n", s.size());
	return 0;
} 
```

---

## 作者：miraculously (赞：2)

分析：

本题其实只要保证变换后的字符串不与最初的字符串重复，那就是新的字符串，否则就循环，后面都不用计入答案。到这里思路就清楚了，只要把原字符串重复一遍，找到第一个与原字符串相同的字符串的位置输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string c,s;
	cin>>c;
	s=c+c;
	cout<<s.find(c,1);//从下标1开始找，避免直接找到自己
}
```


---

## 作者：joy2010WonderMaker (赞：1)

### 题目分析

我们可以从任意一个位置开始取，取到末尾再从头开始取，再将组合成的字符串压进一个集合，防止重复。

### AC Code

```cpp
#include<iostream>
#include<set>
using namespace std;
int ans;
bool f[26];
set<string> sm;
int main(){
    string s;
    cin>>s;
    for(int i=0;i<s.size();i++){
        string temp="";//取出字符串
        for(int j=i;j<s.size();j++){
            temp+=s[j];
        }
        for(int j=0;j<i;j++){
            temp+=s[j];
        }
        sm.insert(temp);//压进集合
    }
    cout<<sm.size()<<endl;
    return 0;
}
```


---

## 作者：jxbe6666 (赞：0)

作为一个重度 STL 依赖患者，做题也必须得用 STL。  

**题目分析：** 众所众知，STL 库里总会给我们一些惊喜。这一道题也可以用 STL 来完成。思路是：先把原字符串重复一次，然后再到新字符串中，从 1 开始寻找原字符串，原字符串的起始位置，就是不同单词的个数，也就是答案。

Code：
```cpp
#include <bits/stdc++.h>
#define I return
#define AK 0
#define IOI ;
using namespace std;
string s1,s2;
int main()
{
    cin>>s1;
    s2=s1+s1;
    cout<<s2.find(s1,1);//一定要从1的位置开始找
    I AK IOI
}

```


---

## 作者：封禁用户 (赞：0)

### 题目链接：[CF754A](http://codeforces.com/contest/754/problem/A)
分析：求前缀和; 看看 $pre_n$ 等于多少:  $pre_n$ 不为0。则直接整个数组全部输出。 如果 $pre_n$ 为0 则在前面找一个 $pre_i$ 不为0。如果找到了则输出    $a_1$  , $a_2$ ,..., $a_i$ 和 $a_{i+1}$  ,..., $a_n$ 贪心吧。

下面给出AC代码：


```cpp
#include<iostream>
using namespace std;
int n,a[101],i,s,b;
int main()
{
    cin>>n;
    for(i=1;i<=n;i++)
    {
         cin>>a[i];
         s+=a[i];
         if(a[i])
            b=i;
     }//贪心
     if(b==0)
        cout<<"NO\n";
     else if(s)
        cout<<"YES\n1\n"<<1<<" "<<n<<"\n";
     else
        cout<<"YES\n2\n"<<1<<" "<<b-1<<"\n"<<b<<" "<<n<<"\n";
     return 0;
 }
```


---

## 作者：Misaka_Mik0t0 (赞：0)

看数据，$|s|\leq50$。果然是红题，暴力即可。

首先，将数列的 $|s|$ 种排列列出来。时间复杂度 $O(n^2)$。

之后，遍历每两个排列。如果两个排列相同，删除其中一个。时间复杂度 $O(n^3)$。

最后，统计一共有多少序列。此时，每两个数列肯定都不相同，序列数量就是答案。

---

## 作者：happybob (赞：0)

最开始的思路其实就是枚举，模拟，因为 $s$ 的长度最多只有 $20$，我重复 $50$ 遍肯定够了吧？用到了 `substr` 和 `unordered_set`，速度比 `set` 快不少。

代码：

```cpp
#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

unordered_set<string> st;

int main()
{
	string s;
	ios::sync_with_stdio(false);
	cin >> s;
	st.insert(s);
	int len = s.length() - 1;
	for (register int i = 1; i <= 50; i++)
	{
		string xx = s.substr(0, len), u = "";
		u += s.back();
		string x = u + xx;
		s = x;
		st.insert(s);
	}
	cout << st.size() << endl;
	return 0;
}
```


---

