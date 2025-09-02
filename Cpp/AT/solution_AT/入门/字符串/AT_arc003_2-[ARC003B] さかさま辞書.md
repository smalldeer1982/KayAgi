# [ARC003B] さかさま辞書

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc003/tasks/arc003_2

高橋君は友達とチャットで逆さしりとりをすることにしました。  
 逆さしりとりとは、前の人が言った単語の頭文字で終わる単語を答えるしりとりです。  
 しかし、高橋君は英単語に自信がないのでこっそり「さかさま辞書」を使うことにしました。  
  
 普通の辞書は単語の先頭の文字がABC順になるように並べられており、同じ文字同士の場合はその次の文字がABC順になるように並べられます。  
 先頭から見ていく普通の辞書順に対して、「さかさま辞書」は後ろの文字から見ていきます。  
 例えば apple, bee, card は、普通の辞書なら apple → bee → card の順になります。  
 しかし、「さかさま辞書」では d で終わる card が $ 1 $ 番、apple とbee は同じ e で終わるのでその $ 1 $ つ前が e である bee が $ 2 $ 番、l であるapple が $ 3 $ 番の順になります。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc003_2/3b080c0561a840fa2991f0f7f5be6d4cfe660742.png)図(a)：普通の辞書順に並べた例 図(b)：さかさま辞書順に並べた例

 

   
 高橋君の代わりに「さかさま辞書」を作成し、与えられた単語を「さかさま辞書」順に並べてください。 入力は以下の形式で標準入力から与えられる。 > $ N $ $ s_{1} $ $ s_{2} $ : : $ s_{N} $

- $ 1 $ 行目は、並べる単語数を表す整数 $ N\ (1\ ≦\ N\ ≦\ 100) $ が与えられる。
- $ 2 $ 行目から $ N $ 行は、並べる単語を表す文字列が $ 1 $ 行に $ 1 $ つずつ与えられる。
- $ i+1 $ 行目の文字列 $ s_i $ の長さは $ 1 $ 文字以上 $ 20 $ 文字以下で、含まれる文字はアルファベットの小文字のみ(`a`-`z`)です。
- なお、重複する単語が与えられることはありません。
 
 入力として与えられた単語を、さかさま辞書順に標準出力に $ 1 $ 行ずつ出力せよ。  
 なお、最後には改行を出力せよ。 ```
<pre class="prettyprint linenums">
5
chokudai
kensho
imos
yuichirw
ao
```

 ```
<pre class="prettyprint linenums">
chokudai
ao
kensho
imos
yuichirw
```

- まず、それぞれの一番後ろの文字は、chokudai、kensho、imos、yuichirw、aoなのでABC順に並べると、i,o,s,wの順になります。
- しかしkenshoとaoの $ 2 $ 人が同じ o なので、この $ 2 $ 人に関してはその $ 1 $ つ前の文字の順で並べます。
- kenshoの後ろから $ 2 $ つ目の文字は h、ao の後ろから $ 2 $ つ目の文字は a なので、ao, kensho の順になります。
- よって、chokudai, ao, kensho, imos, yuichirw の順が答えになります。
 
```
<pre class="prettyprint linenums">
2
dart
art
```

 ```
<pre class="prettyprint linenums">
art
dart
```

- 後ろから $ 1,2,3 $ 番目とも同じ文字なので、後ろから $ 4 $ 番目の文字を比較します。
- しかし、art の後ろから $ 4 $ 番目の文字はありません。
- 無い場合は、a よりも早いので、art, dart の順になります。

# 题解

## 作者：btng_smith666 (赞：21)

# 前言：

传送门：[AT163 さかさま辞書](https://www.luogu.com.cn/problem/AT163)

本蒟蒻最近估值哗哗往下掉，所以今天来发一篇题解QwQ（不过话说这道题怎么这么多重复题解啊）

[博客原文食用更佳](https://www.luogu.com.cn/blog/X-SSS-Tng/solution-at163)

简洁的题目翻译：

> 给定 N 个字符串，将其倒置后按字典序排序，再按顺序输出其原字符串

此题普遍做法就是用 $STL$ 库里的 $reverse$ 函数来实现倒置，然后用 $sort$ 来实现字典序排序，那窝今天就来发一个不用 $reverse$ 的代码

# 代码 + 主要思路：
```cpp
//by btng_smith666 juruo
/*
思路：两次处理 
第一次倒置：将每个字符串的所有字符翻转
第二次排序：将每个字符串字典序排序输出 
*/
#include<bits/stdc++.h>//万能头不解释 
#include<iostream>
#include<cstdio>
#include<string>// string 头文件 
using namespace std;//不用 reverse 代码 
int n;//孤单的 n 不解释 
struct node{//结构体 ，存字符串 
	string st,str;//输入输出中的字符串和第一次倒置后的字符串 
}s[201];//结构体数组 
bool cmp(node x,node y){return x.str<y.str;}//降序 sort 自动跳过 
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		cin>>s[i].st;//string 用输入输出流不解释 
	for(int i=1;i<=n;i++)//这里是此代码的关键，主要就是将输入的字符串倒置存入 str 中 
	{
		int len=s[i].st.size();//长度 
		for(int j=len-1;j>=0;j--)//倒序 
			s[i].str+=s[i].st[j];//加入 
	}
	/*注意上面 str 存的是倒序的 st 
	如果还不明白实现过程可以先看看这两个字符串，效果是这样的：（参考后面的样例 #1 ） 
	for(int i=1;i<=n;i++)
		cout<<s[i].str<<endl<<s[i].st<<endl<<endl;
	elppa     //str
	apple     //st
	
	eeb
	bee
	
	drac
	card
	*/
	sort(s+1,s+n+1,cmp);//将结构体中每个字符串字典序排序 
	for(int i=1;i<=n;i++)//两次处理后的字符串 
		cout<<s[i].st<<endl;
	return 0;
}//不建议直接抄袭 
```

# 提供几组样例：

#1 :（题面里的）

$in$ :
```
3
apple
bee
card
```
$out$ :
```
3
card
bee
apple
```
#2 :（正常的）

$in$ :
```
3
bb
ba
aa
```
$out$ :
```
aa
ba
bb
```
#3 :（仅作参考，别打窝）

$in$ :
```
6
kkk
yyy
ddd
cz
sf
lxl
```
$out$ :
```
ddd
sf
kkk
lxl
yyy
cz
```
呼呼呼，在第 99 行求个赞
qwq

---

## 作者：_Int_ (赞：9)

c++ STL大法好！！！
string 轻松搞定，cmp有点烦


------------

``````cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
string a[105];                   //string数组
int n;                           //个数
bool cmp(string a,string b){     //重、难点（要求背诵~~~）
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());  //翻转
	int AC=a<b;                  //记录
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());  //转回去
	return AC;                   //注意不能在上面直接return a<b;就翻不回来了
}
int main(){                      //7行主程序
	cin>>n;
	for(int i=0;i<n;i++)cin>>a[i];         //get
	sort(a,a+n,cmp);                       //sort
	for(int i=0;i<n;i++)cout<<a[i]<<endl;  //put
	return 0;                              //拜拜
}
``````


------------
 _**~~管理员求过~~**_ 

---

## 作者：Cambridge (赞：2)


小学生又来发题解了！

这道题十分简单，我们先读入当前字符串，再反转当前字符串，后将n个字符串按字典序排序，最后再次翻转并输出即可。至于字典序是如何排序，请读者们翻阅相关资料或上网查询，本蒟蒻在此不做解释。

    #include<iostream>
    #include<cstring>
    #include<cstdio>
    #include<cmath>
    #include<string>
    #include<fstream>
    #include<algorithm>//文件头不解释
    using namespace std;
    string a[100000];
    long long n;//定义变量
    int main()
    {
        cin>>n;//读入n
        for(int i=1; i<=n; i++)
        {
            cin>>a[i];//读入字符串
            reverse(a[i].begin(),a[i].end());//反转当前字符串
        }
        sort(a+1,a+1+n);//字典序排序
        for(int i=1; i<=n; i++)
        {
            reverse(a[i].begin(),a[i].end());//再反转回来
            cout<<a[i]<<endl;//输出字符串
        }
        return 0;//要有好习惯
    }

本蒟蒻就讲到这里，希望对读者有所帮助。
    

---

## 作者：_Qer (赞：1)

题意：给定N个字符串，将其倒置后按字典序排序，再按顺序输出其原字符串。

C++中提供了一个reverse函数，作用是将字符串倒置，我们可以利用这个函数，结合sort快速排序，很快解决掉这个问题。

按照题目要求输入后，将每一个字符串都倒置过来，然后进行一遍排序，最后输出时再反转回来就好了。

字符串的存储有点烦，我不会用string的数组（二维），所以用struct定义一个结构体，来充当数组使用，自定义结构体访问时用 . 这个东西来搞

```cpp
#include<bits/stdc++.h>
using namespace std;
struct sss{//不熟string类型的数组，所以这样用，有点小麻烦
    string s;
}ss[101];
//调取时使用：ss[i].s
int n;
bool com(sss a,sss b){//结构体的排序必须自己手写一个判断大小函数
    return a.s<b.s;//注意这里是大于还是等于
}
int main(){
    cin>>n;
    for(int i=0;i<n;++i){
        cin>>ss[i].s;
        reverse(ss[i].s.begin(),ss[i].s.end());
        //输入同时反转
    }
    sort(ss,ss+n,com);
    //sort可以使用3个参数，第三个可以是自己写的比较大小函数
    for(int i=0;i<n;++i){
        reverse(ss[i].s.begin(),ss[i].s.end());
        //输出时记得反转回来
        cout<<ss[i].s<<endl;
    }
    return 0;
}
```

---

## 作者：5加1 (赞：0)

# 先来分析一下

1. 我们先读入当前字符串
2. 再反转当前字符串，然后将 $n$ 个字符串按字典序排序
3. 最后再次翻转并输出即可。

对于反转字符串，可以用```reverse()```轻松搞定。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main(){
    int n;
    cin>>n;
    string a[105];
    for(int i=0;i<n;i++){
        cin>>a[i];
        reverse(a[i].begin(),a[i].end());
    }
    sort(a,a+n);
    for(int i=0;i<n;i++){
        reverse(a[i].begin(),a[i].end());
        cout<<a[i]<<endl;
    }
    return 0;
}
```

---

## 作者：hensier (赞：0)

本题可以使用——$STL$大法之$sort,reverse$。

$sort$不用多说，而$reverse$用法如下：

例如：$string$ $s=$"$1234872319$"$;$

进行$reverse(s.begin(),s.end());$的操作之后（$void$），s的值将变为"$9132784321$"。

$AC$代码：

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n,i;
int main()
{
    cin>>n;
    string s[n];//不能定义过多，否则sort会空
    for(;i<n;i++)cin>>s[i],reverse(s[i].begin(),s[i].end());//边输入边反转
    sort(s,s+n);//快排
    for(i=0;i<n;i++)reverse(s[i].begin(),s[i].end()),cout<<s[i]<<endl;//反转之后输出
}
```

---

## 作者：逆战争锋 (赞：0)

题意：给定N个字符串，将其倒置后按字典序排序，再按顺序输出其原字符串。

其实这道题就是sort与reverse的结合而已啦！

下面上代码
杜绝抄袭

```
#include <bits/stdc++.h>//万能头文件 
using namespace std;
string s[110];//string里面的数组，二维 
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>s[i];
		reverse(s[i].begin(),s[i].end());//颠倒 
	}
	sort(s,s+n);//字典序排序 
	for(int i=0;i<n;i++)
	{
		reverse(s[i].begin(),s[i].end());//颠倒 
		cout<<s[i]<<endl;
	}

	return 0;//完美结束 
}
```


---

## 作者：tgs9311 (赞：0)

蒟蒻不会写什么cmp，只好写结构体了
# 题意：
### 给定N个字符串，将其倒置后按字典序排序，再按顺序输出其原字符串。
# 解析
### 其实这道题目用结构体是很适合的，只需要两个string类型的变量，一个储存翻转后的，一个储存一开始的字符串就行了，然后sort翻转后的字符串，最后按顺序输出一开始的字符串就OK了！
下面是代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
//结构体定义：
struct a   
{
    string y,f;//y是原来，f是翻转后的
};             
int n;                           
bool cmp(a b,a c)//cmp函数
{ 
    return b.f<c.f;//cmp默认返回小的条件
}
int main()
{                     
    a b[105];    
	cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>b[i].y;//输入
        b[i].f=b[i].y;//给翻转后的先赋值
        reverse(b[i].f.begin(),b[i].f.end());//stl翻转函数
    }
    sort(b,b+n,cmp);//sort快排                       
    for(int i=0;i<n;i++)
    {
        cout<<b[i].y<<endl;  //直接输出即可
    }      
    return 0;
}
```

---

## 作者：不到前10不改名 (赞：0)

//今天这两题真的是贼坑，创下最近除模拟赛外最低刷题记录
```
#include<stdio.h>
#include<string.h>
char srx[1001][1001],t[1001];                   
int n,i,j,k;                           
int cmp(char a[],char b[])//知不知道对于一个纯粹C语言的oier来说：
//没有sort，没有stl是多么痛苦！（所以我评了一个pj-）
{     
    int t=strlen(a);
    char c;
    for(k=0;k<t/2;k++)//只用一半的原因是最前最后交换到中点是后边已交换过了
    {c=a[k];
    a[k]=a[t-k-1];//注意要-1因为字符数组是从0开始
    a[t-k-1]=c;}//这里是一个字符数组模拟反转，也没什么好说的，只有我这种顽冥不灵的人才用了吧~
    t=strlen(b);
    for(k=0;k<t/2;k++)
    {c=b[k];
    b[k]=b[t-k-1];
    b[t-k-1]=c;}//前半部分模拟交换
    int sry=strcmp(a,b);//这里是一个比较函数,会有负数,就不能直接返回了 
    t=strlen(a);
    for(k=0;k<t/2;k++)//这个部分也是一样
    {c=a[k];
    a[k]=a[t-k-1];
    a[t-k-1]=c;}
    t=strlen(b);
    for(k=0;k<t/2;k++)
    {c=b[k];
    b[k]=b[t-k-1];
    b[t-k-1]=c;}//再换回去
    if(sry>=0)//真麻烦，纯c的无奈QAQ
    return 0;
    return 1;
}
int main()
{                      
    scanf("%d",&n);
    for(i=0;i<n;i++)
    scanf("%s",srx[i]);    
    for(i=0;i<n;i++)
    for(j=i+1;j<n;j++)//冒泡233...
    if(!cmp(srx[i],srx[j]))//这个函数cmp的名字纯属乱编的
    {strcpy(t,srx[i]);
    strcpy(srx[i],srx[j]);
    strcpy(srx[j],t);}//交换也没有直接换或swap，真是可怜呢~（哭）
    for(i=0;i<n;i++)
    printf("%s\n",srx[i]);  
    return 0;                              
}
```

---

## 作者：lsyx0918 (赞：0)

这次，我作为C/C++党来给大家发这个题解。

这道题就是字符串排序，但是排序中的字符串要**反转字符串，然后再反转**

话不多说，开发题解：
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
//在这里还可以直接用#include<bits/stdc++.h>来替代
using namespace std;
string a[105];//定义字符串
int n;//定义字符串个数
bool cmp(string a,string b)//个人喜欢把函数放主函数后面，先声明一下
int main()
{
	cin>>n;
	for(int i=0;i<n;i++) cin>>a[i];//输入
	sort(a,a+n,cmp);//排序
	for(int i=0;i<n;i++) cout<<a[i]<<endl;//输出
	return 0;
}
bool cmp(string a,string b)
{
	reverse(a.begin(),a.end());//反转字符串a
	reverse(b.begin(),b.end());//反转字符串b
	int AC=a<b;//设定返回值（如果现在直接写return的话，就无法反转回去了）
	reverse(a.begin(),a.end());//反转回原来的字符串a
	reverse(b.begin(),b.end());//反转回原来的字符串b
	return AC; //返回值
}
```
OK，大功告成！

---

