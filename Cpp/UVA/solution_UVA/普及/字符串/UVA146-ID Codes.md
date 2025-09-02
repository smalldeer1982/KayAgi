# ID Codes

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=82

[PDF](https://uva.onlinejudge.org/external/1/p146.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA146/0a26c57498e3107538df966221b8da23281e007c.png)

## 样例 #1

### 输入

```
abaacb
cbbaa
#```

### 输出

```
ababac
No Successor```

# 题解

## 作者：Brian_WBY (赞：4)

### 并不需要转数字，直接生成排列即可

个人还是比较倾向于用字符数组（因为快啊，速度是第一生产力），再加上STL提供的next_permutation，总体上还是比较容易的（STL大法好！！！）。

PS:具体细节见代码注释。

压行版代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
char s[62];//读入
int main()
{
    while (~scanf("%s",s+1))//字符数组可以从第1位开始读入，比较方便
    {
        if  (s[1]=='#') return 0;//结束条件
        puts(next_permutation(s+1,s+strlen(s+1)+1)?s+1:"No Successor");
        //可以生成排列就直接输出，不能就输出No Successor，puts自带换行
    }
    return 0;
}
```

---

## 作者：ahwhQZY (赞：1)

题目大意：

给你一个序列（字符串），求它的下一个排列。

解题思路：
	
   next_permutation（STL大法真香）。
   
   大家会很惊奇，next_permutation不是用来生成数字排列的吗？本人实测了一下，next_permutation也可以生成字符排列。
   
所以直接上代码吧：
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[100];//习惯用的字符数组
int main(){
    while(scanf("%s",s+1)){//最好是从1开始，方便
        if(s[1]=='#')return 0;//结束条件
        if(next_permutation(s+1,s+strlen(s+1)+1))printf("%s\n",s+1);//生成排列
	else printf("No Successor\n");//生成不了了
    }
}
```

---

## 作者：gongbangrui (赞：1)


分析
------------
这道题要求生成给出字符串的下一个字典序字符串，首先我们先判断是否存在这样的一个字符串，如果一个字符串的前一个字符总是比后一个字符大的话，那么是不存在下一个字典序的。我们从后面开始查找，直到找到一个前面的字符比后面的小，然后在找到的这个字符到字符串结尾的区间做变换从后往前，首字符和比它大的字符做交换，交换的最后结果是找到了比首字符大一点的字符，然后将该区间内除首字符的其他字符按字典序排序。即找到这个区间内下一个首字符的最小字典序。

AC代码
------------
不用库函数的写法：

```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>

char s[60];

int cmp( const void *_p, const void *_q)
{
    char *p, *q;
    p = (char *)_p;
    q = (char *)_q;
    return *p - *q;
}

int main()
{
    int k;
    while( true)
    {
        scanf( "%s", s);
        if( s[0] == '#') break;
        int len = strlen( s);
        for( k = len - 1; k > 0; k --)
            if( s[ k] > s[ k - 1])
                break;
        if( k == 0)
        {
            printf( "No Successor\n");
            continue;
        }
        for( int i = len - 1; i >= k; i --)
        if( s[i] > s[k - 1])
        {
            char temp = s[i];
            s[i] = s[k - 1];
            s[k - 1] = temp;
            break;
        }
        qsort( s + k, len - k, sizeof( char), cmp);
        printf( "%s\n", s);
    }
    return 0;
}

```
 

------------


然后用了C++的next_permutation函数写了下：


```cpp
```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

char s[60];
int main()
{
    int k;
    while( true)
    {
        scanf( "%s", s);
        if( s[0] == '#') break;
        int len = strlen( s);
        for( k = len - 1; k > 0; k --)
            if( s[ k] > s[ k - 1])
                break;
        if( k == 0)
        {
            printf( "No Successor\n");
            continue;
        }
        next_permutation( s, s + len);
        printf( "%s\n", s);
    }
    return 0;
}
```


---

## 作者：szkzyc (赞：0)

这道题是给定你多个字符串，求它的下一个排列。

本来按照常理来说是要写搜索的，但是谁料我们用的是 C++——STL 大法好！

所以说，本题只需要利用 C++ 中的 STL 库里一个求排列的函数 `next_permutation `  即可。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF INT_MAX
using namespace std;
char str[100];//定义字符数组 
int main(){
	while(cin >> str){//多组数据 
		if(!isalpha(str[0])) break;//如果这个字符串的第一位不是字母，那么退出 
		else{
			if(!next_permutation(str, str + strlen(str))) cout << "No Successor" << endl;//如果这个字符串没有下一个排列，输出No SUccessor 
			else{
				cout << str << endl;//否则就输出这个字符串 
			}
		}
	}
	return 0;
}

```


---

## 作者：cyrxdzj (赞：0)

### 一、思路

本题其实是求一个只包含小写字母的字符串，求这个字符串的字典序的下一个字符串。

使用 `STL` 库中的 `next_permutation` 即可。

### 二、完整代码

```cpp
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int main()
{
	string input;
	while(cin>>input&&input!="#")
	{
		if(next_permutation(input.begin(),input.end()))
		{
			cout<<input<<endl;//有解输出。
		}
		else
		{
			cout<<"No Successor"<<endl;//无解输出。
		}
	}
	return 0;//完结撒花！
}

```

### 三、后记

记录：<https://www.luogu.com.cn/record/52127054>。

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

如果可以生成排列，就输出字符串，否则输出那一串英文。

所以，我们可以用到 `next_permutation` 函数，这就轻松多了。而且，这个函数会自动帮你改一下那个字符串，输出时不用二次修改。

### 2 代码与记录

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main(){
    while(true){
        char s[100];
        scanf("%s",s);
        if(s[0]=='#'){
            break;
        }
        if(next_permutation(s,s+strlen(s))){//STL大法好！
            cout<<s<<endl;
        }
        else{
            cout<<"No Successor\n";
        }
    }
    return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/51763595)

By **dengziyue**

---

## 作者：Asdonel (赞：0)

## 题目简意
- 给定若干个字符串
- 输出此字符串的下一排列
- 如没有下一个排列，输出 $“No Successor$”（不包括引号）。

## 解题思路
这道题不需要多讲。
输出下一个排列，**可以考虑使用STL的 next_permutation 函数**。   

不知道的萌新 [请看这里](https://blog.csdn.net/qian2213762498/article/details/79683905)      

所以就可以利用这一点，输出。

**注：建议以1开始输入，不然很难操作！**

## CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[100];
int main()
{
    while(scanf("%s",s+1))
    {
        if(s[1]=='#')return 0;
        if(next_permutation(s+1,s+strlen(s+1)+1))printf("%s\n",s+1);
		else printf("No Successor\n");
    }
    return 0;
}
```
## 感谢观看

---

## 作者：Argon_Cube (赞：0)

- **【题目链接】**

[Link:UVA146](https://www.luogu.com.cn/problem/UVA146)

- **【解题思路】**

**1.总结题意：**

给定一个字符串，生成这个字符串的下一个排列，如果已是最后一个排列输出“No Successor”。

**2.想想如何实现。**

既然是生成下一个排列，那肯定是用$next\_permutation$了。

- **【代码】**
```cpp
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
int main(int argc,char *argv[],char *env[])
{
        string str;
        cin>>str;
        while(str[0]!='#')
        {
            if(next_permutation(str.begin(),str.end()))//把str设为下一个排列
                cout<<str;
            else
                cout<<"No Successor";
            endl(cout);
            cin>>str;
        }
        return 0;
}

```

---

## 作者：cryozwq (赞：0)

STL 大法好啊！

ALANDQQ 大佬说:
```
直接生成下一排列应该也可以过（不转化为数字），我蒻
懒(又假又强)，不想试~~
```
所以我就发一个直接生成的好了。
### 分析
求一个字符串的下一个排列，没有输出 $0$。

~~简单！清楚！好！~~

这个问题可以直接用 STL 的 next_permutation 函数解决。

它的作用是求一个数组的下一个排列，有就把数组变成下一个排列，没有下一个排列返回 $0$。

next_permutation 函数使用格式与 sort 类似。
 
那这道题简直变成红题有没有？（~~C 党 P 党流下了悔恨的泪水~~）

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string b;
	while(1)
	{
		char a[60];
		cin>>b;//先输入字符串
		if(b=="#")
		return 0;//输入#停止
		for(int i=0;i<b.size();i++)
		a[i]=b[i];//字符串转字符数组
		a[b.size()]=0;//玄学操作
		if(next_permutation(a,a+b.size()))
		{
			puts(a); //如果能生成，就输出
		} 
		else
		cout<<"No Successor"<<endl; //否则没有
	}
	return 0;
}
```

---

## 作者：ALANDQQ (赞：0)

蒟蒻的题解~~~  
本人~~超弱~~懒，只想用这种方法  
STL可以直接过
放代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;//存每次输入的字符串
int a[10000001];
int main()
{
    while(cin>>s&&s!="#")//输入，当s为'#'时终止循环
    {
        for(int i=0;i<s.size();i++) a[i]=s[i]-'a';//转为数字，存入数组
        if(next_permutation(a,a+s.size()))//生成下一个排列，STL库函数(可用此过全排列)
        //next_permutation函数有返回值，true或false
        //如果可以生成下一个排列
        {
            for(int i=0;i<s.size();i++) printf("%c",a[i]+'a');//再次转换为字母，输出下一个排列
            printf("\n");
        }
        else puts("No Successor");//不能生成
    }
    return 0;//功德圆满
}
```  
直接生成下一排列应该也可以过（不转化为数字），我~~蒻~~懒，不想试~~     
求过~~~

---

