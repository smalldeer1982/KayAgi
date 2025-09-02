# Amusing Joke

## 题目描述

So, the New Year holidays are over. Santa Claus and his colleagues can take a rest and have guests at last. When two "New Year and Christmas Men" meet, thear assistants cut out of cardboard the letters from the guest's name and the host's name in honor of this event. Then the hung the letters above the main entrance. One night, when everyone went to bed, someone took all the letters of our characters' names. Then he may have shuffled the letters and put them in one pile in front of the door.

The next morning it was impossible to find the culprit who had made the disorder. But everybody wondered whether it is possible to restore the names of the host and his guests from the letters lying at the door? That is, we need to verify that there are no extra letters, and that nobody will need to cut more letters.

Help the "New Year and Christmas Men" and their friends to cope with this problem. You are given both inscriptions that hung over the front door the previous night, and a pile of letters that were found at the front door next morning.

## 说明/提示

In the first sample the letters written in the last line can be used to write the names and there won't be any extra letters left.

In the second sample letter "P" is missing from the pile and there's an extra letter "L".

In the third sample there's an extra letter "L".

## 样例 #1

### 输入

```
SANTACLAUS
DEDMOROZ
SANTAMOROZDEDCLAUS
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
PAPAINOEL
JOULUPUKKI
JOULNAPAOILELUPUKKI
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
BABBONATALE
FATHERCHRISTMAS
BABCHRISTMASBONATALLEFATHER
```

### 输出

```
NO
```

# 题解

## 作者：Tune_ (赞：5)

这题呢，可以用两个桶，记录每个字符的个数，一个是记录拼接前的一个，一个是记录拆开后的两个。最后比较两个桶中每个字母的数量是否相同，一碰上不同的就输出“NO”并return，最后输出“YES”。

附上我~~简洁的~~代码：
```
#include<bits/stdc++.h>
using namespace std;
int a[30],b[30];
int main()
{
	string s1,s2,s3;
	cin>>s1>>s2>>s3;
	for(int i=0;i<s1.size();i++)a[s1[i]-64]++;//放进桶
	for(int i=0;i<s2.size();i++)a[s2[i]-64]++;
	for(int i=0;i<s3.size();i++)b[s3[i]-64]++;
	for(int i=1;i<=26;i++)//判断是否数量相同
	{
		if(a[i]!=b[i])
		{
			cout<<"NO";//直接输出，结束
			return 0;
		}
	}
	cout<<"YES";//没毛病
	return 0;//拜了个拜
}
```
走过路过，给本蒟蒻点个赞鸭~

---

## 作者：hensier (赞：4)

我们可以令三个字符串为$s1,s2,s3$。假如$s1,s2$中的所有字母和$s3$中的相同，则满足题意，输出`YES`，否则输出`NO`。我们可以用一个数组保存并实现之。

`C++`代码（下面用$a,b,c$来代替三个字符串）：

```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b,c;
int letter1[26],letter2[26];//letter1保存a,b中的字母，letter2保存c中的
int main()
{
    cin>>a>>b>>c;
    for(int i=0;a[i];i++)letter1[a[i]-'A']++;
    for(int i=0;b[i];i++)letter1[b[i]-'A']++;
    for(int i=0;c[i];i++)letter2[c[i]-'A']++;
    for(int i=0;i<26;i++)
    {
        if(letter1[i]!=letter2[i])//一个元素不同就输出NO
        {
            printf("NO");
            return 0;
        }
    }
    printf("YES");
    return 0;
}
```

接下来我们来看一下`Python`的写法。由于`Python`没有字符的类型，所以我们只能用字符串对应数字。具体写法是：

```python
list = {a1: b1, a2: b2,..., an: bn}
# 上述中的a1,b1,a2,b2,...,an,bn可以是任何一种类型，则等同于赋值list[a1]=b1,list[a2]=b2,...,list[an]=bn
```

但是在`Python`中无法循环赋值，而总共有$26$个字母，所以不如用`C++`打个表来节省时间：

```cpp
for(char c='A';c<='Z';c++)printf("'%c': %d,",c,c-'A');
```

我们把上述输出结果中最后一个逗号去掉之后，放入上述的大括号中，就得到了对应关系。

```python
let = {'A': 0,'B': 1,'C': 2,'D': 3,'E': 4,'F': 5,'G': 6,'H': 7,'I': 8,'J': 9,'K': 10,'L': 11,'M': 12,'N': 13,'O': 14,'P': 15,'Q': 16,'R': 17,'S': 18,'T': 19,'U': 20,'V': 21,'W': 22,'X': 23,'Y': 24,'Z': 25} # 赋值
list1 = [0 for i in range(26)] # 建立list1并全部赋值为0，保存str1,str2的字母
list2 = [0 for i in range(26)] # 建立list2并全部赋值为0，保存str3的字母
str1 = str(input())
str2 = str(input())
str3 = str(input()) # 输入str1,str2,str3
for letter in str1: # Python中可以通过这种方式来获得字符串中的字母
    list1[let[letter]] += 1 # 累加
for letter in str2:
    list1[let[letter]] += 1
for letter in str3:
    list2[let[letter]] += 1
if list1 == list2: # Python可以直接比较list
    print('YES')
else:
    print("NO")
```

---

## 作者：小豆子范德萨 (赞：3)

把前两个字符串拼接后排序，并且把第三个字符串也排序，最后比较排序后的字符串是否相等即可

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
	string s1,s2,s3;
	cin>>s1>>s2>>s3;
	string t = s1+s2;
	sort(t.begin(),t.end());
	sort(s3.begin(),s3.end());
	if(s3==t) printf("YES\n");
	else printf("NO\n");
	return 0;
}
```


---

## 作者：SKTelecomT1_Faker (赞：1)

一道不算太难的题。

主要考察string的用法（至少我认为是这样）

首先输入三个字符串a,b,c,再利用string奇妙的功能直接定义数组ab使得ab等于a与b拼起来的形式！！！

之后再定义两个数组a1,a2,把每个字符串里对应字母的出现
次数分别转变为数组中该位的数加上一，最后比较两个相应的数组是否相同就可以了。

Code↓
```cpp
#include<bits/stdc++.h>//我懒——万能头直接上qwq
using namespace std;
signed main()//我无聊
{
    string a,b,c;
    cin>>a>>b>>c;
    int a1[10086],a2[10086];//定义数组
    string ab=a+b;
    if(ab.size()!=c.size())//减少时间，优化，先比较长度不一样直接输出NO返回
    {
        cout<<"NO";
        exit(0);
    }
    for(register int i=0;i<ab.size();i++) a1[ab[i]]++,a2[c[i]]++;//转为数组中数的形式
    for(register int i=0;i<=1000;i++)
    {
        if(a1[i]!=a2[i])//比较两个数组是否完全相同
        {
            cout<<"NO"<<endl;//不是直接输出NO并返回
            exit(0);
        }
    }
    cout<<"YES"<<endl;是的话输出YES
    exit(0);//好习惯伴我们一生
}
```

既然这篇文章提到了string，我们不妨来介绍一下它的用法：

string是C++、java、VB等编程语言中的字符串，字符串是一个特殊的对象，属于引用类型。 C++标准库中string类以类型的形式对字符串进行封装，且包含了字符序列的处理操作。在c++中头文件是#include<cstring>（string或string.h均可qaq）
  
int capacity()const; //返回当前容量（即string中不必增加内存即可存放的元素个数）
 
int max_size()const; //返回string对象中可存放的最大字符串的长度
 
int size()const; //返回当前字符串的大小
 
int length()const; //返回当前字符串的长度
 
bool empty()const; //当前字符串是否为空
 
void resize(int len,char c);//把字符串当前大小置为len，并用字符c填充不足的部分

 这些都是一些常用技巧，string类长度用size求，为string(你自己设的未知量）.size(),读入用cin或scanf（记住是%s），输出用cout或printf（记住也是%s）相加后直接把两个拼在一起等。
  
希望对大家有帮助qwq。

---

## 作者：codemap (赞：1)

这道题挺简单的

主要方法:

用一个数组表示26个字母,遍历一遍将c中的字母++

再遍历两遍分别将ab中的字母--

最后再遍历一遍,如果有一位不是0输出NO,否则输出YES

上代码
```cpp
#include<iostream>
using namespace std;
int main()
{
    string a,b,c;
    int i,d[27]={};//全都赋0
    cin>>a>>b>>c;
    for(i=0;i<c.size();i++)
        d[c[i]-'A'+1]++;//转化成数字++,d下标从1开始,所以+1
    for(i=0;i<a.size();i++)
        d[a[i]-'A'+1]--;//转化成数字--
    for(i=0;i<b.size();i++)
        d[b[i]-'A'+1]--;//转化成数字--
    for(i=1;i<=26;i++)
        if(d[i]!=0)//如果任意一位不是0
        {
            cout<<"NO";//输出NO
            return 0;
        }
    cout<<"YES";//否则输出YES
    return 0;//完美结束
}
```
# 请勿抄袭


---

## 作者：ZolaWatle (赞：0)

### CF141A 题解

题目上说，**将第三个字符串中的每个字符剪下来**。每个字符都能拆，那这就是一道水题了。

------------

### 思路：

- 开两个数组，分别存前两个字符串以及第三个字符串**每个字符的数量**，比较这两个数组是否相同即可。

- 在每个字符串里字符数量累加完毕之后，从数组下标A到Z（当然是ASCII码值）逐个比较同一下标的数是否相等。

- 如果不等**直接输出**NO，循环完了之后还没有找到不同之处，就说明可以拼出来了，输出YES.

------------

这里就有一个细节需要注意，请看官先比较一下这两个代码段：

```cpp
for(re i=0;i<l;i++)
    	can[int(ipt[i])]++;
```

```cpp
for(re i=0;i<l;i++)
    	can['ipt[i]']++;
```

注意，用第二种方式来累加数量会导致程序**停止工作**。被单引号包含的必须是一个单一字符，而不能是一个char型的变量。

如果要把一个**字符型转换成一个整型**（本质上是字符型的ASCII码值），可以加上这么一个括号：int( )，轻松加愉快。

------------

### Code：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define re register int
using namespace std;

string ipt;
int l,cnt[201],can[201];  //cnt存前两个字符串，can存前两个字符串 

int main()
{	
	for(re i=1;i<=2;i++)
	{
		std::cin>>ipt;
		l=ipt.length();  //用string库里的函数计算长度
		for(re i=0;i<l;i++)
			cnt[int(ipt[i])]++;  //这个字符的出现次数+1 
	}//前两个字符串 
	
	std::cin>>ipt;
	l=ipt.length();  //还是计算长度
	for(re i=0;i<l;i++)
		can[int(ipt[i])]++;  //这个字符的出现次数+1 ，记住要使用int( )
	//要拆的字符串 
		
	for(re i='A';i<='Z';i++)  //因为题中只有大写字母，所以只需从A到Z就可以了 
	//注意要加单引号转换成ASCII码值	
        if(can[i]!=cnt[i])
		{
			std::printf("NO");  //不一样直接输出
			return 0;
		}
	
	std::printf("YES");
	return 0;
}
```


---

## 作者：return先生 (赞：0)

这题可以将string的优势充分的体现出来（其实不用string也可以的）

具体代码：

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	string a,b,c;//定义string类型
	cin>>a>>b>>c;//输入
	int QAQ[10086],QCQ[10086];//QAQ用来记录A和B的出现的个数，QCQ用来记录C中出现的个数
	memset(QAQ,0,sizeof(QAQ));//初始化，如果不初始化的话后面作比较就不太好做了……
	memset(QCQ,0,sizeof(QCQ));
	string ab=a+b;//string的优势，那就是可以直接的相加（甚至可以直接对比）比如a='abc',b='def',那么a+b就是'abcdef'了！
	if(ab.size()!=c.size())//如果c的长度和a+b的长度不相等的话，直接输出NO，然后return 0；
	{
		cout<<"NO";
		return 0;
	}
	for(int i=0;i<=ab.size();i++)//将QAQ和QCQ中的ab[i]和c[i]的地方相加，可以用于统计个数。
	{
		QAQ[ab[i]]++;
		QCQ[c[i]]++;
	}
	for(int i=0;i<=300;i++)//判断是否是每个字符出现次数都相等
	{
		if(QAQ[i]!=QCQ[i])//只要发现不相等，然后就输出NO，return 0；
		{
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES";//没有发现出现次数不相等的字符，那么输出YES。
	return 0;//结束
}
```



---

