# Chat room

## 题目描述

Vasya has recently learned to type and log on to the Internet. He immediately entered a chat room and decided to say hello to everybody. Vasya typed the word $ s $ . It is considered that Vasya managed to say hello if several letters can be deleted from the typed word so that it resulted in the word "hello". For example, if Vasya types the word "ahhellllloou", it will be considered that he said hello, and if he types "hlelo", it will be considered that Vasya got misunderstood and he didn't manage to say hello. Determine whether Vasya managed to say hello by the given word $ s $ .

## 样例 #1

### 输入

```
ahhellllloou
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
hlelo
```

### 输出

```
NO
```

# 题解

## 作者：Anguei (赞：19)

这道题的题意大概是：给定一个字符串，如果删掉这个字符串的一些字母之后是"hello"，输出"YES"，否则输出"NO"。

因为我们不需要关心删掉的字母是什么，所以最简单的方法，莫过于写一个**正则表达式**了：
$$ \texttt{.*h.*e.*l.*l.*o.*} $$
（`.*`在正则表达式中用于模糊匹配）。

代码：

```cpp
#include <regex> // C++11 的正则表达式库
#include <string>
#include <iostream>

int main() {
    std::string s;
    std::cin >> s;
    std::regex pat(".*h.*e.*l.*l.*o.*"); // 定义正则表达式
    if (std::regex_search(s, pat)) // 如果匹配成功
        std::cout << "YES" << std::endl;
    else
        std::cout << "NO" << std::endl;
    return 0;
}
```

---

## 作者：char32_t (赞：16)

# 题解 CF58A 【Chat room】

------------

题目大意：在一个序列中判断它是否包含子序列**"hello"**


那么我们可以将"h" "e" "l" "l" "o"依次放入队列（需要包含头文件`<queue>`），利用队列先进先出（FIFO）的原则，每当从序列中扫到队首元素时，就将队首元素出队。那么当序列扫完时，如果队列为空，则可以完成要求，输出"YES"；

如果队列不空，则不能完成要求，输出"NO"。


```cpp
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
char ch[110];
queue<char> que;//建队
int main() {
    que.push('h');
    que.push('e');
    que.push('l');
    que.push('l');
    que.push('o');//将子序列放入队列
    scanf("%s", ch);//读入序列
    int len=strlen(ch);//获得序列长度
    for(int i=0; i<len; i++)//扫描序列
    if(ch[i]==que.front()) que.pop();//如果此时序列元素为队首元素，则弹出队首元素
    if(que.empty()) printf("YES");//如果队列为空，输出"YES"
    else printf("NO");//否则输出"NO"
    return 0;
}
```

---

## 作者：EthanWu (赞：8)

# 这是一道很水的题

### 然而蒟蒻的我要用五重循环搞定

简单粗暴！就是枚举，如果h后面有e，e后面有l，l后面有l，l后面有o（不用相邻），就说明可以删除一些字母形成”hello“，否则就不能。

### 代码

~~听说抄题解会CE

```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<string>
#include<cstring>
#include<queue>
#include<stack>
#include<map>
#include<list>
#include<deque>
#include<climits>
#include<algorithm>
#include<cstdlib>
using namespace std;

string a；

int mian()
{
	cin>>a;
	int len=a.length();
	for(int i=0;i<=len-4;i++)
	{
		for(int j=i+1;j<=len-3;j++)
		{
			for(int k=j+1;k<=len-2;k++)
			{
				for(int ii=k+1;ii<=len-1;ii++)
				{
					for(int jj=ii+1;jj<=len;jj++)
					{
						if(a[i]=='h'&&a[j]=='e'&&a[k]=='l'&&a[ii]=='l'&&a[jj]=='o')
						{
							cout<<"YES"<<endl;
							return 0;
						}
					}
				}
			}
		}
	}
	cout<<"NO"<<endl;
	return 0;
}
```

## 啦啦啦

---

## 作者：Rocket_raccoon_ (赞：4)

应该可以说是较短且易懂的代码了......  
这里用了一个比较巧妙的方法，先用字符数组把需要的字符串存起来，然后每发现一个字符ans所表示的字符相等，就将ans的值+1。这样就可以很省代码的判定是否满足条件，最后只需根据ans的大小判断是否符合条件即可

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
char r[6]={"hello"}//预处理需要的字符串;

int main(){
	int i,ans=0;
	char s;
	
	while (cin>>s){//如果读入一个字符
		if (s==r[ans]) ans++;//判断是否符合条件
	}
	if (ans>=5) cout<<"YES";
	else cout<<"NO";
	
	
	return 0;
}
```

---

## 作者：Randyhoads (赞：4)

这道题大意就是

给定一个字符串使删除这个字符串的一些字符是他变成“hello”


具体做法就是先设一个数组存储hello，第一次先匹配‘h’,如果一样在匹配‘e’……


代码很简单就不加注释了


```cpp
#include<bits/stdc++.h>

using namespace std;

char s[1001];

char goal[5]={'h','e','l','l','o'};

int top=0;

int main()
{
    scanf("%s",s);
    for(int i=0;i<strlen(s);i++)
    {
        if(s[i]==goal[top])
        {
            top++;
        }
        if(top==5)
        {
            break;
        }
    }
    if(top==5)
    {
        cout<<"YES"<<endl;
    }
    else cout<<"NO"<<endl;
}

```

---

## 作者：zoezoykit (赞：3)

先来康康题目大意：

给定一个字符串s，询问能否通过删除一些字母使其变为"hello"；

如果可以输出"YES"，否则输出"NO"。

思路很简单：

先定义一个与 char 数组“hello”相对应的 **bool** 类型数组，类似 **hash table** 的原理，一个元素一个元素**映射**。

本题的关键就是字符的顺序，所以这里要判断一下，当符合【**此字符与值已经变为 true 的连续映射元素的末尾元素的下一个元素的对应字符相同**】（中括号里的话有点难懂，要多理解几遍）时，才能让此对应字符的映射元素的值变为 **true**，而不能只是双层循环判断是不是有某个字符，否则判断不了顺序是否正确。

最后只有每个元素的值都为 **true**，才能输出"YES"。

下面是泥萌最喜欢的完整AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

char word[6]={"hello"};
int pd;					//pd变量是循环里的判断值 
bool k[6];				//k数组为word数组的映射 
string hello;				//"hello"字符串为Vasya输入的字符s 

int main()
{
	getline(cin,hello);			//这样输入字符串方便测试 
	for(int i=0;i<hello.length();i++)
	{
		pd=0;
		for(int j=1;j<=5;j++)
		{
			if(k[j]==1)		//这里是上文所述的判断 
			{
				pd++;
			}
			else break;
		}
		if(hello[i]==word[pd]) 
		{
			k[pd+1]=true;
		}
    }
	if(k[1]&&k[2]&&k[3]&&k[4]&&k[5])
	{
		cout<<"YES";
	}
    else 
	{
		cout<<"NO";
	}

    return 0;
}
```

蒟蒻的第一篇题解，望多支持！

---

## 作者：HAO233 (赞：1)

这道题和[CF802G](https://www.luogu.org/problem/CF802G)简直一模一样，唯一的区别就是上一题要求的是`heidi`而本题是`hello`。   
注意到区别了吗？本题的字符串是有两个字符连在一起的！  

上一题可以直接用$s.find()$嵌套判断每个字符是否在合适的位置，然而我们知道，$find(char, pos)$是从$pos$开始寻找**第一个** $char$出现的位置。然而本题的字符串是有两个`l`连着的，如果使用上一题的代码，那么使用$find()$函数的时候，只会返回第一个`l`出现的位置。~~这就是我WA了多次的原因~~  

于是我们就可以对程序进行改进，把搜索第一次出现的位置改成第一次未被搜索到的位置，这样就可以搜索到两个`l`。  
为此我们需要一个标记数组$vis$，大小为$100$。然后我们只需要写一个函数$found(char, pos)$，用法和之前的$find()$一样。只不过这个函数需要我们在判断一次是否为第一次被查找，如果是，那么就标记并返回。  

还有一些细节我写在注释里了,以下为代码,应该很好理解:
```cpp
#include <bits/stdc++.h>
using namespace std;

string s;
int vis[100];//用于标记的数组

//求c在字符串中第一个未被查找的位置
int found (char c, int pos) {
    if (pos == -1) return -1;//如果上一个没有找到，那么直接返回-1
    for (int i = pos; i < s.length(); i ++) {//开始寻找
        if (s[i] == c && !vis[i]) {//如果当前字符为c且未被标记过
            vis[i] = 1;//标记
            return i;
        }
    }
    return -1;//如果找不到，返回-1
}

int main() {
    cin >> s;//读入
    //逆序嵌套搜索函数，只要其中一个没有查找到就会返回-1，只需要判断最后的结果是否为-1就好了
    if (found('o',found('l',found('l',found('e',found('h',0))))) == -1) cout << "NO";//如果为-1,那么输出NO
    else cout << "YES";//如果不为-1,那么输出YES
    return 0;
}
```




---

## 作者：HOIer_9_42 (赞：1)

  这又是一段悲伤的故事——

/*

被和谐部分

*/

最终，我~~在自己将近十次的提交中~~终于A掉了这道题。

   不得不说，这道题的细节非常多，个人认为这道题难度应该在【普及-】的范围。

  好了，话归整体。下面我们来讲讲这道题的思路。我认为，这道题可以练一练我们的标记法——用bool型变量标记判断顺序与记录存在与否。
  
  这就有点像是if语句中的通行证，被标记成符合条件的才能执行判断语句中的程序。也正因为如此，我们必须得确保判断语句的正确性与严密性。

这道题可以类比CF，CF的代码如下——

```cpp
#pragma GCC optimize(3)
#pragma GCC optimize("inline")
#pragma once
#include<bits/stdc++.h>
#define q register
typedef long long ll;
using namespace std;
string s;
ll tag1,tag2,tot;
bool ans;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>s;
    for(q ll i=0;i<s.length();i++){
        if((s[i]=='C')&&(!ans)){
			ans=true;  
        }
        if(s[i]=='F'){
            if(ans){
                puts("Yes");
                return 0;
            }
        }
    }
    puts("No");
    return 0;
}
```

下面是这道题的AC代码，下面注释较少，主要是希望大家自己理解。

```cpp
#pragma GCC optimize(3)
#pragma GCC optimize("inline")
#pragma once
#include<bits/stdc++.h>
#define q register
typedef long long ll;
using namespace std;
ll tagh,tage,tagl,tago,tot;

//tot是l的数量，这道题的难点就
//主要集中在l的判定上
bool judh,jude,judl,judo;
string s;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>s;
	for(q ll i=0;i<s.length();i++){
		if(s[i]=='h'&&!judh){
			tagh=i;   judh=true;
		}
		if(s[i]=='e'&&judh&&!jude){
			tage=i;   jude=true;
		//第一个h出现了
        }
		if(s[i]=='l'&&judh&&jude){
			tot++;   judl=true;
		//h和e都出现过
        }
		if(s[i]=='o'&&judl&&!judo){
			tago=i;   judo=true;
		//l也出现过了
        }
	}
	if(tagh<tage&&tot>=2&&tage<tago){
		puts("YES"); 
		   return 0;
	}
	puts("NO");
	return 0;
}
```
方法不才，大佬勿喷！~   ^_^

---

## 作者：梦里调音 (赞：1)

### ~~还是我的题解最通俗易懂。。。~~咳咳

好好好，废话少说。

思路是：把字符串遍历一次，用sum计数，按“hello”五个字母的顺序判断。即“h” “e” “l” “l” “o”。

不仅字母要有，还要符合顺序。就利用sum加以判断即可。

可能时间复杂度比较大，但。。。通俗易懂鸭~~（手动滑稽）~~

~~PS：输出时的“\n”是用来换行的，不必在意~~

奉上代码~~~

```cpp
#include <iostream>//100%头文件鸭
using namespace std;
int main(){
	string s;
	cin>>s;
	int i,j,k,sum=0;
	for(i=0;i<s.length();i++){//循环里挨个判断
		if(s[i]=='h'&&sum==0)sum++;//如想加速还可利用continue哟
		if(s[i]=='e'&&sum==1)sum++;
		if(s[i]=='l'&&(sum==2||sum==3))sum++;
		if(s[i]=='o'&&sum==4)sum++;
		if(sum==5){
			cout<<"YES\n";//满足条件直接输出白白
			return 0;
		}
	}
	cout<<"NO\n";//不满足才会来到这里
}
```

---

## 作者：_lyc233 (赞：1)

大佬们都太强啦，本蒟蒻只能用自己的暴力方法AC。

------------
分析题意，也就是要在字符串中寻找有没有“$hello$”，有输出$YES$，没有输出$NO$。

------------

我的思路是这样的：

1.读入字符串

2.判断存不存在$h$

3.不存在，输出$NO$

4.存在，判断$h$后面存不存在$e$

5.不存在，输出$NO$

6.存在，判断$e$后面存不存在$l$

......

......

------------
是不是很像while呢？

代码：
```pascal
var
  st:ansistring;  //这个要开超长字符串
begin
  readln(st);
  if pos('h',st)>0 then delete(st,1,pos('h',st))
                   else begin writeln('NO');halt; end;
  if pos('e',st)>0 then delete(st,1,pos('e',st))
                   else begin writeln('NO');halt; end;
  if pos('l',st)>0 then delete(st,1,pos('l',st))
                   else begin writeln('NO');halt; end;
  if pos('l',st)>0 then delete(st,1,pos('l',st))
                   else begin writeln('NO');halt; end;  //以上步骤即为：判断h、e、l、l是否存在，不存在直接halt
  if pos('o',st)>0 then writeln('YES')  //输出yes
                   else writeln('NO');  //输出no
end.
```

------------
附：其实这个代码确实可以用whlie循环做，将hello存入数组，通过对i的调用，判断存不存在

---

## 作者：TangLongbin (赞：0)

直接一个一个字符去读
然后看是否存在按顺序排列的h，e，l，l，o；
有就YES
没有就NO
看代码QAQ

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char s;
int ans;
int main(){
  
	while(cin>>s){
		if(s=='h'&&ans==0){
			ans++;
		}
		if(s=='e'&&ans==1){
			ans++;
		}
		if(s=='l'&&(ans==2||ans==3)){
			ans++;
		}
		if(s=='o'&&ans==4){
			cout<<"YES";
			return 0;
		}
	}
	cout<<"NO";
	return 0;
}
```

---

## 作者：return先生 (赞：0)

看到各位大佬的题解都很简洁，~~但是作为蒟蒻的我，看不懂啊~~

所以，蒟蒻的方法只有暴力了！疯狂的暴力（~~谁让数据那么水呢哈哈哈哈哈~~）

代码：

```cpp
#include<iostream>
using namespace std;
int main()
{
	string a;
	cin>>a;
	for(int i=0;i<a.size();i++)
	{
		if(a[i]=='h')
		{
			for(int j=i+1;j<a.size()-3;j++)
			{
				if(a[j]=='e')
				{
					for(int k=j+1;k<a.size()-2;k++)
					{
						if(a[k]=='l')
						{
							for(int q=k+1;q<a.size()-1;q++)
							{
								if(a[q]=='l')
								{
									for(int w=q+1;w<a.size();w++)
									{
										if(a[w]=='o')
										{
											cout<<"YES"<<endl;
											return 0;
										} 
									}
								}
							}
						}
					}
				}
			}
		}
	}
	cout<<"NO"<<endl;
	return 0;
} 
```

蒟蒻写的代码，难看，对不住大家了……

---

## 作者：meyi (赞：0)

## 终于知道为什么没有用string.find的题解了
## 本人交了五六遍才过，数据很坑~~（或许是我太蒻了吧）~~
## 思路：挨个找字符，如果没找到立即输出NO并退出程序
## 上代码：
```cpp
#include<cstdlib>
#include<iostream>
using namespace std;
string s;
inline int sf(char ch){
	int sfch=s.find(ch);
	return sfch<0?(cout<<"NO",exit(0),string::npos):sfch;
}
inline int sf(char ch,int st){
	int sfch=s.find(ch,st);
	return sfch<0?(cout<<"NO",exit(0),string::npos):sfch;
}
//上面的三目运算符是为了没找到字符立即输出NO并退出程序。
main(){
    cin>>s;
    cout<<(sf('o',sf('l',sf('l',sf('e',sf('h')))+1))==string::npos?"NO":"YES");
    /*注意，这里要加一，因为有两个l字符，而题目中要求一个在另一个后面，
      如果不加一，程序会将一个l字符误判成两个（例：输入helo，输出YES）。*/
}
```

---

## 作者：rill4474 (赞：0)

## 思路：找到一个字母后继续在这个字母后找另一个字母（如果这个字母在下一个字母后面也会自动输出no)
# 本题与‘CF802G’思路相同（不过我那题的题解没过）
```pascal
var
 i,j,k:longint;
 s:string;
function a(s:string):string;
begin
for i:=1 to length(s) do if s[i]='h' then begin k:=1;break;end;//找h
if k=0 then exit('NO');//如果没就输出no
k:=0;//清零
for j:=i+1 to length(s) do if s[j]='e' then begin k:=1;break;end;//注意，要从上一个字母开始找e
if k=0 then exit('NO');//同上
k:=0;//同上
for i:=j+1 to length(s) do if s[i]='i' then begin k:=1;break;end;
if k=0 then exit('NO');
k:=0;
for j:=i+1 to length(s) do if s[j]='d' then begin k:=1;break;end;
if k=0 then exit('NO');
k:=0;
for i:=j+1 to length(s) do if s[i]='i' then begin k:=1;break;end;
if k=0 then exit('NO');
exit('YES');//层层筛选之后的yes
end;
begin
read(s);//输入s
write(a(s));//函数调用
end.
```

---

## 作者：zhylj (赞：0)

不必一个一个判断，只需要有一个数组记录要判断的字符（"hello"）
然后扫一遍字符串即可。

和CF802G很像

（代码有坑请勿直接复制）
```cpp
#include<bits/stdc++.h>
using namespace std;
char p[6]="hello",c[1005];
int mian()
{
    int x=0;  //前面x个已经找到了
    gets(c);  //读入
    for(int i=0;i<strlen(c);i++)
        if(c[i]==p[x]) x++;  //若又找到一个，继续找下一个
    if(x>=5) cout<<"YES"<<endl;  //如果每一个都找到了就输出yes
    else cout<<"NO"<<endl;  //否则输出No
    return 0;
}
```

---

