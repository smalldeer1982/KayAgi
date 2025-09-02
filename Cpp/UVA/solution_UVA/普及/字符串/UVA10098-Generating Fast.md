# Generating Fast

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=1039

[PDF](https://uva.onlinejudge.org/external/100/p10098.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10098/f90ae2e6e97ea26dff771e444046ad7a5afbfd41.png)

## 样例 #1

### 输入

```
3
ab
abc
bca```

### 输出

```
ab
ba

abc
acb
bac
bca
cab
cba

abc
acb
bac
bca
cab
cba```

# 题解

## 作者：Nightsky_Stars (赞：6)

题目大意：给定 $n$ 个字符串 $s_{i}$，让你字典序输出 $s_{i}$ 的全排列。

这道题很简单，用一下 STL 库中的 next_permutation 就行了。

这里我来介绍一下 next_permutation，将当前排列更改为全排列中的下一个排列。如果当前排列已经是全排列中的最后一个排列（元素完全从大到小排列），函数返回 false 并将排列更改为全排列中的第一个排列（元素完全从小到大排列）；否则，函数返回 true。
# CODE:
```
#include<bits/stdc++.h>
using namespace std;
char s[20];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		int l=strlen(s);
		sort(s,s+l);
		do{
			cout<<s<<"\n";
		}while(next_permutation(s,s+l));
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：WangRui (赞：3)

#### 【大致翻译】（机翻）

生成置换一直是计算机科学中的一个重要问题。在这个问题中，您必须按升序生成给定字符串的排列。请记住，您的算法必须是有效的。

Input

输入的第一行包含一个整数n，它指示要跟随多少字符串。下n行包含n个字符串。字符串将只包含alpha数字，而不包含任何空格。字符串的最大长度为10。

Output

对于每个输入字符串，按升序打印所有可能的排列。不应将字符串视为区分大小写的字符串，而不应重复进行排列。每个输出集后面应该有一个空行。

Sample Input

3

ab

abc

bca

Sample Output

ab

ba

#### //空一行

abc

acb

bac

bca

cab

cba

//空一行

abc

acb

bac

bca

cab

cba

//空一行

#### 【个人对题意的总结】

有n行，每行一个字符串s_i。要求输出s_i的全排列。//注意每一组结束后有一个空行。

#### 【方法1：stl】

```
#include<bits/stdc++.h>//万能头文件
//#include<cstdio>
//#include<algorithm>//用next_permutation（）的库函数
using namespace std;
char x[200];
int main(){
// 	freopen("1.in","r",stdin);//方便调试
//	freopen("UVA10098 Generating Fast.out","w",stdout);
//文件输入输出
	int t;
	scanf("%d",&t);
	while(t--){//循环组数
		scanf("%s",x+1);
        //这样可以使char的下标从~~（0开始的？世界）~~1开始
		int len=strlen(x+1);//计算从1开始
		sort(x+1,x+len+1);//sort排序
		for(register int i=1;i<=len;i++)//玄学加速
			printf("%c",x[i]);
            //先打出一个正常的，顺手将第一个变成最初的字典序：如样例的第3个数据
		printf("\n");
		while(next_permutation(x+1,x+len+1)){//stl核心下一个字典序排列
			for(register int i=1;i<=len;i++)
				printf("%c",x[i]);
			printf("\n");
		}
		printf("\n");
	}
//	fclose(stdin);	//	fclose(stdout);
	return 0;//别忘了这个
}
```
小技巧：ctrl+/	将此行变成注释；2，ctrl+d 删除此行。

#### 【方法2：p1706】

~~这道几乎是模板了，~~里面的方法，一个比一个精彩，都是大牛！~~（不像我，是个蒟蒻！）~~给出它的链接！[P1706 全排列问题](https://www.luogu.org/problemnew/solution/P1706)

其实很多国外题在结果后面要有一个空行，可能是一个坑点。~~（我也不知道为什么）~~

最后，码字不易，求赞~~（滑稽）~~。

---

## 作者：Tenshi (赞：2)

前置知识：

字符串基础知识（最基础的就够了）

STL库中的next_permutation 用法

还有呢？ 没了，已经可以A掉这题了（~~那你还WA~~，提醒后面的人记得看讨论区啊，样例输出是有问题的qwq）

下面就说一下 next_permutation()

next_permutation()将区间内容转化为下一种唯一的排序方式。对于字符串，字符串按照递增顺序进行。（转自网络）

也就是说，按照题意，对字符串sort一下，然后直接用next_permutation()搞就能够实现对目标字符串各个字符全排列

核心代码：
```cpp
int len=strlen(ch);
		sort(ch,ch+len);
		do{
			cout<<ch;
			cout<<endl;
		}while(next_permutation(ch,ch+len));
```
放AC code（超短的qwq）（头文件自己写）

```cpp
int n;//case个数
char ch[15];//存字符串
int main(){
	cin>>n;
	while(n--){
		cin>>ch;
		int len=strlen(ch); //取长度
		sort(ch,ch+len);   //对目标串进行排序
		do{
			cout<<ch;
			cout<<endl;
		}while(next_permutation(ch,ch+len));
		cout<<endl;//坑
	}
	return 0;//完美结束
}
```


---

## 作者：CCCloud (赞：1)

## 全排列问题  
#### 题目大意：将给出的字符串序列的全排列输出  
#### STL大法：使用next_permutation（）的库函数
#### 详细过程：先用sort排序，使得该字符串序列是按照字典序排好序；然后在利用用next_permutation（）的库函数，将该字符串序列的下一次序列输出
#### 注意：由于用next_permutation是将字符串序列的下一次序列输出，所以我们要用do-while，保证排好序的第一个序列能够输出


------------

### 代码实现如下：

```cpp
#include<bits/stdc++.h>//建议使用万能头文件
using namespace std;

int n,m;//定义整型变量，其中n是组数，m是当前字符串的长度
char s[15];//定义字符数组，相当于字符串的作用

int main()
{
	scanf("%d",&n);//读入组数
	for(int i=1;i<=n;i++)
    {
		scanf("%s",s);//读入字符串
        m=strlen(s);//strlen得出字符串的长度
        
		sort(s,s+m);//sort排序，使得字符串中的元素是按照字典序排序的
		
        do//确保有一次输出
        {
			printf("%s",s);//输出字符串，也可以一个一个元素输出
			puts("");//换行
		}while(next_permutation(s, s + m));//判断
        puts("");//每两个字符串之间换行
    }
    
    return 0;//完美的结束！
}
	
```

---

## 作者：shaozhehan (赞：0)

[原题链接](https://www.luogu.com.cn/problem/UVA10098)

[UVA 链接](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=1039)

首先给出 [PDF](https://onlinejudge.org/external/100/p10098.pdf) 中的样例。

输入：
```plain
3
ab
abc
bca
```
输出：
```plain
ab
ba

abc
acb
bac
bca
cab
cba

abc
acb
bac
bca
cab
cba

```

题目大意：

给定 $n$ 个字符串 $s_i$，让你输出 $s_i$ 的全排列，字典序从小到大。对于每一个字符串的输出结束，输出一个换行。

思路：

这道题我们可以使用 [```next_permutation```](https://oiwiki.org/lang/csl/algorithm/) 每次求出全排列，然后输出就行了。需要注意的是，使用 ```next_permutation``` 函数求出所有全排列时，我们需要使用 [```do-while```](https://oi-wiki.org/lang/loop/#dowhile-%E8%AF%AD%E5%8F%A5) 循环，避免初始情况没有处理。

坑点：
1. 一开始的字符串一定要排序，类似于 ```sort(s.begin(), s.end())```！（细节见代码）
2. 请注意：UVA 卡格式，对于每一个字符串的输出结束，输出一个换行！

上代码：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);// cin、cout 加速
    int n;
    cin >> n;
    while (n--){
        string s;
        cin >> s;
        sort(s.begin(), s.end());// 记得排序
        do {
            cout << s << "\n";
        } while (next_permutation(s.begin(), s.end()));// do-while 循环
        cout << "\n";
    }
    return 0;
}
```

---

## 作者：cmk666 (赞：0)

[题目链接](/problem/UVA10098)

题目大意：给定字符串 $s$，按字典序输出其全排列。

这题可以用 STL 的 `next_permutation` 函数解决。[cppreference link](//zh.cppreference.com/w/cpp/algorithm/next_permutation)

它的用法很像 `sort`，分别要传入第一个位置和最后一个之后的位置。它会把这段区间变成下一个排列，并返回 `true`。如果已经是最后一个排列，返回 `false`。

在用之前先 `sort` 一次，保证初始是最小的，这样 `next_permutation` 才能把所有的排序都枚举玩。

时间复杂度 $O(\lvert s\rvert\times\lvert s\rvert!)$。核心代码如下：
```cpp
int n, l; char s[19];
int main()
{
	read(n);
	For(i, 1, n)
	{
		scanf("%s", s + 1), l = strlen(s + 1), sort(s + 1, s + l + 1);
		do puts(s + 1); while ( next_permutation(s + 1, s + l + 1) );
		puts("");
	}
	return 0;
}
```

---

## 作者：myyyIisq2R (赞：0)

[UVA10098 Generating Fast](https://www.luogu.com.cn/problem/UVA10098)

### 题目大意
按照字典序输出输入字符串的全排列。
```cpp
#include <bits/stdc++.h> 
using namespace std;
int main()
{
	char s[110];
	int t = 0;
	cin >> t;
	getchar();
	while (t--)
	{
		cin >> s;
		int len = strlen(s);
		sort(s, s+len);
		do
		{
			cout << s << endl;
		}while (next_permutation(s, s+len));
		cout << endl;
	}
   return 0
}
```
做完这道题记得切 [UVA146](https://www.luogu.com.cn/problem/UVA146)~~（贴心~）~~。

---

## 作者：轻尘 (赞：0)

### 开垦无人荒地篇——UVA10098 【Generating Fast】


------------

# 样！例！有！错！
**正确输出如下**
```cpp
ab
ba

abc
acb
bac
bca
cab
cba

abc
acb
bac
bca
cab
cba

```
------------

	来自TCL Progrmming Contest,2001;
    
一道字典序组合的~~入门题~~。

**思路是利用字典序排列的规律不断下推后继排列。**

**Think twice , code once.**
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[15];
int l;
int get()
{
	int i=l-1;
	while(i>0&&s[i-1]>=s[i]) i--;
	if(!i) return 0;
	int m=i;
	for(int j=i+1;j<l;j++)
	{
		if(s[j]<=s[i-1]) continue;
		if(s[j]<s[m]) m=j;
	}
	swap(s[i-1],s[m]);
	sort(s+i,s+l);
	return 1;
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%s",s);
		l=strlen(s);
		sort(s,s+l);
		printf("%s\n",s);
		while(get()) printf("%s\n",s);
		printf("\n");
	}
	return 0;
}
```
安利个人博客  **：）**

[传送门](http://tchoi.club)

---

