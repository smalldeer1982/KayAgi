# Scarborough Fair

## 题目描述

Are you going to Scarborough Fair?Parsley, sage, rosemary and thyme.

Remember me to one who lives there.

He once was the true love of mine.





Willem is taking the girl to the highest building in island No.28, however, neither of them knows how to get there.

Willem asks his friend, Grick for directions, Grick helped them, and gave them a task.

Although the girl wants to help, Willem insists on doing it by himself.

Grick gave Willem a string of length $ n $ .

Willem needs to do $ m $ operations, each operation has four parameters $ l,r,c_{1},c_{2} $ , which means that all symbols $ c_{1} $ in range $ [l,r] $ (from $ l $ -th to $ r $ -th, including $ l $ and $ r $ ) are changed into $ c_{2} $ . String is 1-indexed.

Grick wants to know the final string after all the $ m $ operations.

## 说明/提示

For the second example:

After the first operation, the string is wxxak.

After the second operation, the string is waaak.

After the third operation, the string is gaaak.

## 样例 #1

### 输入

```
3 1
ioi
1 1 i n
```

### 输出

```
noi```

## 样例 #2

### 输入

```
5 3
wxhak
3 3 h x
1 5 x a
1 3 w g
```

### 输出

```
gaaak```

# 题解

## 作者：loi_hjh (赞：5)

简简单单的字符串做法

请忽略用来好看的头文件 

# 我wangjz就是无聊死，也不会多打一个头文件

## 真好玩

附上代码：

```cpp
#include<map> 
#include<list>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,m,l,r;
char p,q;
char a[10001];
void gg(){
	scanf("%d%d",&l,&r);//本次变化的范围 
	cin>>p>>q;//懒得用字符串了，不然会读进空格 
	for(int i=l;i<=r;i++)
		if(a[i]==p) a[i]=q;//找到p就变q 
	return;
}
int main(){
	scanf("%d%d",&n,&m);//并不知道长度有什么用 
	scanf("%s",a+1); 
	for(int i=1;i<=m;i++)
		gg();//看起来比较整齐
	printf("%s",a+1); 
	return ~~(0-0);//卖个萌求通过 
}
```

---

## 作者：TianLuen (赞：4)

# CF897A C++题解
## 题目大意
- 有一个长度为 $n$ 的字符串 $s$ 。
- 有 $m$ 次操作。
- 对于每一次操作，将 $\left(l,r\right)$ 区间所有所有的 $c1$ 字符都改为 $c2$。
- 求的是修改后的字符串 $s$
## 题意分析
这道题，完全就是模拟，不需要高深的算法。

只要根据每次读到的数据，逐一判断是否为 $c1$，如果是，修改；否则忽略。

由于数据范围极小，不毒瘤，以 $O(mn)$ 的时间复杂度可以轻松通过，于是可以直接写代码了。

有一点需要注意，每次读入 $4$ 个参数时最好用`scanf`读入两个字符，这样不次读入 $4$ 个参数时最好用`scanf`读入两个字符，这样不bits/stdc++.h容易错。`scanf`包含在`stdio.h`头文件中，不过CF不会报错，很神奇。
## 代码
```cpp
#include<bits/stdc++.h>	//万能头走天下
using namespace std;
char a[100000],c1,c2;	//按照题面开变量，我个人喜欢全局变量
int n,m,l,r;
int main()
{
    cin>>n>>m;
    cin>>a;	//友情提示，千万不要用gets
    for(int i=0;i<m;i++)
    {
        scanf("%d %d %c %c",&l,&r,&c1,&c2);//scanf读入
        for(l--;l<r;l++)	//循环遍历，我喜欢数组第一个元素是0，所以先要l--
            if(a[l]==c1)
                a[l]=c2;
    }
    for(int i=0;i<n;i++)	//输出
        cout<<a[i];
    return 0;
}
```
## The end

---

## 作者：封禁用户 (赞：3)

### 前言

~~一看这题目，不是裸的线段树吗？(看来真的是线段树做多了~~

一道红题怎么会有线段树出来呢？

### 分析

题意就是说，有一个字符串，然后让你维护，按照格式在 l 和 r 之间的 c1 的字符都变为 c2 ，然后输出这个字符串。

明摆着是一道模拟题，按照格式维护并且输出就可以了。

### Code

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
string s1;
int n,m;
//头文件以及定义变量
signed main()//signed 等同于 int。
{
   scanf("%d %d",&n,&m);
   cin>>s1;
   //读入，字符串用 cin 读入比较方便，并且它也不卡常数。
   for (int i=1;i<=m;i++)//开始处理
   {
        int l=0,r=0;
        char ch1=' ',ch2=' ';
        //定义变量，局部变量最好清零，否则会有野值。
        scanf("%d %d %c %c",&l,&r,&ch1,&ch2);//读入 cin 也可以。
        l--;r--;//注意！由于字符串 cin 读入是从下标 0 开始的！所以要 -1 
         for (int j=l;j<=r;j++)
            {
                if (s1[j]==ch1) s1[j]=ch2;//如果比对成功了，那么证明这是要换掉的字符。
            }
   }
   cout<<s1<<endl;
   //输出。
   return 0;
}
```

### 写在后面的话

我这篇题解如果有错误，那么请在评论区里留言，我将会很感谢反映的人。

**谢谢观赏！**

---

## 作者：Frank_R_Z (赞：3)

###
~~啊哈，又一道（char）水题~~，诸位大佬擅长用string，但其实我觉得还是char一个一个字符输入最简单了，（~~下标随便控制~~）
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m,l,r;
	char x[1002],c1,c2;//根据题意开数组
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>x[i];//逐个输入
	}
	for(int i=1;i<=m;i++)
	{
		cin>>l>>r;
		cin>>c1>>c2;
		for(int j=l;j<=r;j++)
		{
			if(x[j]==c1)x[j]=c2;//迭代，判断
		}
	}
	for(int i=1;i<=n;i++)
	{
		cout<<x[i];//输出改变后的string
	}
	cout<<endl;
	return 0;
}
//求过

```
##
其实用string也可以。

---

## 作者：PC_DOS (赞：3)

这是一道字符串模拟题，只需要按照题意顺次读入指令然后替换需要替换的字符即可。

唯一需要注意的地方是:这里字符串的第一个字符索引为1。

代码:
```
#include <iostream>
#include <string>
#include <cstring>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	int iLength, nOperation, iStart, iEnd,i,j; //iLength-字符串长度，nOperation-指令个数，iStart-起点，iEnd-终点，i、j-循环计数器
	char chrOrig, chrReplace; //chrOrig-被替换的字符，chrReplace-替换用的字符
	string sString; //待处理的字符串
	cin >> iLength >> nOperation; //输入长度和指令个数
	getline(cin, sString); //读取掉不需要的东西
	getline(cin, sString); //读入字符串
	for (i = 1; i <= nOperation; ++i){ //循环读取指令
		cin >> iStart >> iEnd >> chrOrig >> chrReplace; //读入指令
		for (j = iStart - 1; j <= iEnd - 1; ++j){ //从iStart-1到iEnd-1(字符串的第一个字符索引为1，而string第一个字符的索引为0，因此头尾都减1)走一遍字符串
			if (sString[j] == chrOrig){ //如果发现需要被替换的内容
				sString[j] = chrReplace; //替换
			}
		}
	}
	cout << sString; //输出处理过后的字符串
	return 0; //结束
}
```

---

## 作者：u55545554 (赞：2)

```cpp
/*一个长度为n的字符串，需要做m个操作，每个操作有四个参数l,r,c1,c2，这意味着在(l,r)的范围中所有的符号c1(从l到r，包括l和r)都变成了c2。
第一行包含两个整数n和m (1<=n,m<=100)。
第二行包含一个长度为n的字符串，由小写的英文字母组成。
每个m行包含四个参数l,r,c1,c2(1<=l<=r<= n,c1和c2是小写英文字母),四个参数中间是隔开的空间。
执行上述操作后输出字符串s。*/
/*意味着在(l,r)的范围中所有的符号c1(从l到r，包括l和r)都变成了c2。*/
#include<iostream>
#include<cstring>
using namespace std;
int main(){
    int n,m;int l,r;string s;
    cin>>n>>m>>s;
    char a[n+1];
    strncpy(a,s.c_str(),s.length());//a[0]=a a[1]=b a[2]=c a[3]=d
    
    for(int i=1;i<=m;i++){
        int l,r;cin>>l>>r;
        char c1,c2;cin>>c1>>c2;
        for(int j=l;j<=r;j++){
            if(a[j-1]==c1)a[j-1]=c2;
        }
    }
    for(int i=0;i<n;i++){
        cout<<a[i];
    }
    return 0;
}
```

---

## 作者：hinatakaho (赞：2)

这是一道字符串的模拟题，直接上代码
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
char a[100001]; //数组尽可能开在外面
int main(){
    int n,m;
    scanf("%d%d",&n,&m); 
    scanf("%s",a); 
    int l,r;
    char x,y;
    for(int i=0;i<m;i++){
        scanf("%d%d %c %c",&l,&r,&x,&y); //x与y的占位符前要有空格以跳过换行符
        for(int j=l-1;j<=r-1;j++){ //从l-1开始一直到r-1
            if(a[j]==x){
                a[j]=y; //是x就换成y
            }
        }
    }
    printf("%s",a);//输出
    return 0;结束qwq
}
```

---

