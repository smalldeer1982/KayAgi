# [USACO12NOV] Clumsy Cows S

## 题目描述

Bessie the cow is trying to type a balanced string of parentheses into her new laptop, but she is sufficiently clumsy (due to her large hooves) that she keeps mis-typing characters.  Please help her by computing the minimum number of characters in the string that one must reverse (e.g., changing a left parenthesis to a right parenthesis, or vice versa) so that the string would become balanced.

There are several ways to define what it means for a string of parentheses to be "balanced".  Perhaps the simplest definition is that there must be the same total number of ('s and )'s, and for any prefix of the string, there must be at least as many ('s as )'s.  For example, the following strings are all balanced:

() 
(()) 
()(()()) 

while these are not:

)( 
())( 
((()))) 

给出一个偶数长度的括号序列，问最少修改多少个括号可以使其平衡。


## 说明/提示

The last parenthesis must be toggled, and so must one of the two middle right parentheses.



## 样例 #1

### 输入

```
())( 
```

### 输出

```
2 
```

# 题解

## 作者：A_Big_Jiong (赞：41)

~~我实在想不明白，为什么这个题会和前缀和有关系，肯定是本蒟蒻太弱了，根本想不出来。~~

------------

我的思路其实也十分简单，但由于太弱，优化是不可能优化的
~~（绝对不会真香警告）~~，主要就是通过模拟栈顶，来记录有多少的括号是需修改的，具体我还是在代码中说吧。
```cpp
#include<cstdio>
#include<cstring>//便于使用strlen();
using namespace std;
const int maxn=100010;
char str[maxn];//我也不知道用const开数组的习惯从何而来，先这样吧
int ans,ls,num;//ans即answer,ls即str字符串的长度,num就是个假栈顶,说明现在已经有num个括号未匹配成功
int main(){
	scanf("%s",&str);
	ls=strlen(str);//记录str的长度，不要问我为什么不用STL
	for(int i=0;i<ls;i++){
		if(str[i]=='(')  num++;//等待匹配右括号
		else if(str[i]==')'&&num==0){//num==0即为现在str[i]之前所有括号都能匹配，凭空出现个右括号,ans自加,并将该括号转为左括号等待匹配
			ans++;num++;
		}else num--;//匹配成功后要减少一个待匹配的数量
	}
	ans+=num/2;//还有num个左括号没有匹配,便将其中的一半转为右括号
	if(num%2!=0)  ans++;//如果num是单数,则有一个括号必须进行一次删除修改
    //值得一提的是，楼上的dalao用的ans+=(num+1)/2;和此思路一致，也更加巧妙，我太弱所以没想到
	printf("%d",ans);
	return 0;
}
```
------------

这次话比较多，代码被挤得很不美观~~(虽然我这人毫无美学观念)~~，还请各位大佬多多包涵，同时，也欢迎提出新解法让我观摩。

------------

# **请勿抄袭，谢谢！！！**

---

## 作者：Berlin_Jacor (赞：34)

其实这道题并不需要用栈，只要模拟栈的算法原理就可以了，浅显易懂。跑的也不算慢，贴代码：
```
#include <bits/stdc++.h>
using namespace std;
int ans,sum,i;
string s;
int main(){
	cin>>s;
	int lens=s.size();//这样快 
	for(;i<lens;++i){
		if(s[i]=='(')sum++;//模拟栈 
		else{
			if(sum)--sum;//抵消一个左括号 
			else ++ans,++sum;//变成了左括号 
		}
	}
	ans+=sum>>1;//剩下的都是左括号的情况 ，要有一半变成右括号 
	cout<<ans; 
	return 0;
}
```

---

## 作者：Garrison (赞：12)

看到这道~~水题~~难题的第一眼我就想到了这是一道数据结构的好题，什么数据结构？那就是**stack栈**。

栈是一种先进后出的数据结构，不会的自学~~（逃）~~

栈最基础的实现有两种，一种是STLstack另一种是数组手写的，因为本蒟蒻实在太弱了，为了方便，我就用了STL

那如何用呢？
```
stack<类型> S;
S.push();将元素压入栈
S.pop();将栈顶元素弹出
S.empty();判断栈是否为空
等等
```
除了stack，我还用了string类。
```
string c;
c.size();求出c串的长度（从下标0开始）
              |    |    | 
             )_)  )_)  )_) 
            )___))___))___)\ 
           )____)____)_____)\\ 
         _____|____|____|____\\\__ 
---------\                   /--------- 
  ^^^^^ ^^^^^ ^^^^  ^^^^^^^  ^^^^^    ^^^ 
```
## 核心代码讲解：
```
for(int i=0;i<c.size();++i){
	if(Q.size()>0){
		if(c[i]=='(')
			Q.push(c[i]);
		else{
			if(Q.top()=='(')
				Q.pop();
			else ++ans,Q.push('(');
		}
	}else{
		if(c[i]==')')
			++ans;
		Q.push('(');
	}
}
```
将c字符串枚举就不用说了，对于栈，我们要分两种情况讨论：

1、栈为空。    2、栈不为空。

当为空时我们直接将‘（’入栈就好了，当然，如果此时的c[i]不是‘（’那么我们就将方案数+1。

不为空时：
《1》 如果c[i]是左括号的话，直接入栈
《2》 如果c[i]是右括号并且此时栈顶是左括号的话，栈顶元素弹出。
《3》 如果c[i]是右括号并且此时栈顶也不是左括号的话，方案数累加1并且将‘（’入栈。

#### 但是，这就完了吗？

还没完，最好还要判断栈是否为空，如果不为空，还要加上此时栈中元素个数/2
```
if(!Q.empty())
	ans+=(Q.size()+1)/2;
```
最后完美输出。
## CODE：
```
#include<string>
#include<stack>
#include<iostream>
int ans;
std::stack<char> Q;
std::string c;
int main(){
	std::cin>>c;
	for(int i=0;i<c.size();++i){
		if(Q.size()>0){
			if(c[i]=='(')
				Q.push(c[i]);
			else{
				if(Q.top()=='(')
					Q.pop();
				else ++ans,Q.push('(');
			}
		}else{
			if(c[i]==')')
				++ans;
			Q.push('(');
		}
	}
	if(!Q.empty())
		ans+=(Q.size()+1)/2;
	std::cout<<ans<<std::endl;
	return 0;
}//++i比i++快
```



---

## 作者：微露点滴 (赞：9)

## 蒟蒻的第一篇题解

对于本题我们可以采用贪心的思想：题目要求最后所有括号平衡，那么我们可以先预处理整个字符串，将相邻的平衡括号全都删去，然后留给我们的就只剩下单身的括号们啦。

接下来我们可以再运用一次贪心的思想：从头开始将相邻的单身括号两两
匹配，不难发现，对于下标为奇数的 ' ( ' ，应变为 ' ) ' ,从而与前一个 ' ( '匹配；对于下标为偶数的 ' ) '，应变为 ' ( ' ，从而与后一个 ' ) ' 匹配。最后就可以愉快地统计 ans 啦(●ˇ∀ˇ●)

此处代码：
```cpp
for(int i = 0;i < st.size();i++)
		if( (i % 2 == 1 && st[i] == '(' ) || ( i % 2 == 0 && st[i] == ')' ) ) ans++;
```
完整的代码蒟蒻偷个懒就不贴啦，相信机智的同学们一定能AC (ง •_•)ง

2018/7/29

---

## 作者：cellur925 (赞：3)

学了栈数据结构，这题是括号匹配的升级版。

本来76分程序是先判断了一下括号是否匹配，但是~~并没有什么必要~~。反而会too many or too few lines.


方法和判括号是否匹配一样。

遇到左括号就进栈，若遇到右括号且栈不为空，就弹出；若遇到右括号且栈空，就改为左括号。


由于保证在栈里的东西都是左括号，所以
最后如果栈不空，结果再加栈中元素数除以2。


上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
char hd[200000];
int fix,len;
stack<int>s;
int main()
{
	//freopen("test.in","r",stdin);
	//freopen("text.out","w",stdout);
	scanf("%s",hd);
	len=strlen(hd);
    for(int i=0;i<=len-1;i++)
	{
		if(hd[i]=='(') s.push(hd[i]);
		if(hd[i]==')')
		{
			if(s.empty())
			{
				s.push('(');
				fix++;
			}
			else s.pop();
		}
	}
	if(!s.empty()) fix+=s.size()/2;
	
	printf("%d",fix);
	return 0;
}
```





~~橙人做橙题会不会掉蓝啊（跑~~

---

## 作者：ResidualNight (赞：2)

获得更好的阅读体验？[blog传送门](https://residualnight.github.io/2019/03/03/P3056%20笨牛Clumsy%20Cows%20题解/)

明显，这是一道用栈解决的~~水~~题。但是除了栈，还有另外一种简单一点的方法。

切入正题：

# 1.栈(stack)

运用**STL**中的`#include<stack>`

```cpp
stack<类型> st;
压栈 st.push(元素);
出栈 st.pop();
获取栈顶元素 st.top();
栈的大小(元素个数) st.size();
判断栈是否为空(栈空输出true，反之亦然) st.empty();
```

## 例：判断括号是否匹配

```cpp
bool check(string s)
{
    stack<char> st;
    for(int i=0; i<s.size(); i++){
        if(s[i]=='(') st.push(s[i]); //左括号进栈
        else{ //不是左括号就是右括号
            if(st.empty()) return 0; //如果当前栈空，莫名其妙来一个右括号即为不匹配
            else st.pop(); //说明栈里有待匹配的左括号，弹出一个（配对成功）
        }
    }
    return 1;
}
```

## 上代码

真是喜闻乐见的一个环节呢

```cpp
int ans=0;
string s;
stack<char> st;
int main()
{
    cin>>s;
    for(int i=0; i<s.size(); i++){
        if(s[i]=='(') st.push(s[i]); //左括号进栈
        else{ //不是左括号就是右括号
            if(st.empty()){st.push('('); ans++;} //注意。如果不匹配就说明需要括号反转，因此反转括号，ans++
            else st.pop();
        }
    }
    if(!st.empty()) ans+=st.size()/2; //如果剩下一堆左括号，说明需要反转一半的才能配对成功
    cout<<ans<<endl;
    return 0;
}
```

# 2.加减计数法

和栈的原理差不多，只不过简单易懂，不用掌握栈。时间的话~~让我们大声喊出：STL NB!~~

左括号+1，右括号-1。如果匹配的话就是0了。

当然也有反例：`())(`单纯判断最终结果是否为0会出错WA

因此，我们可以发现：如果当前为0(栈空)再加入一个右括号那就需要反转了

```cpp
string s;
int ans=0,p=0;
int main()
{
    cin>>s;
    for(int i=0; i<s.size(); i++){
        if(s[i]=='(') p++; //类似进栈
        else{ //不是左括号就是右括号
            if(p) p--; //有一个左括号等待配对，那就配对
            else ans++,p++; //反转
        }
    }
    ans+=p/2; //道理同栈
    cout<<ans<<endl;
    return 0;
}
```

结尾小声bb：~~感觉题目背景尽是扯淡2333~~

---

## 作者：Snow_Dreams (赞：2)

这道题可以先使用一个筛选的想法

第一步：先读入，在读入的时候运用一个数据结构：栈

这个数据结构在stl的头文件stack中，用using namspace std即可使用

#### 这个数据结构的特点是先进后出

按一下方法处理：

将左括号视为压入，右括号视为弹出。如果在某个时间节点右括号的总数大于左括号，就cnt++，如果以后再出现左括号，就先判断cnt是否大于0，如果cnt>0,就cnt--，如果cnt=0，就再将左括号压入

注：压入左括号指压入元素1，不需要压入字符

接着就进行输出：

如果cnt>0 就输出cnt

如果cnt=0，就定义ans，当stack中有元素的时候就不断弹出，弹出一个ans就+1，最后输出ans即可

---

## 作者：ljc20020730 (赞：2)

好久没刷水题了，水一篇博客。

看到题解区那么鱼龙混杂的题解，我还是先抛砖引玉，讲一个最简单的也最容易理解的题解吧。

首先，我们贪心的想将足够多的()括号匹配掉。这可可以使用栈来实现，如何当前元素为(那么直接插入栈，如果为)那么如果栈顶元素为(那么弹栈找到一组合法匹配，否则插入栈顶。

最终栈中元素必然是$cnt1$个`(`和$cnt2$个`)`组成的，所以将两个(部分和)部分分开考虑，在每一个相同符号的区域内，先间隔地把符号取反，然后最终可能会剩余一个`)(`然后再加`2`即可。

综上所述，如果$cnt_1 $和$cnt_2$的都是偶数直接输出$(cnt_1 + cnt_2)/2$否则输出$(cnt_1 + cnt_2)/2 + 2$

你懂了么。


```cpp
# include<bits/stdc++.h>
using namespace std;
stack<char>t;
char s[100010];
int main()
{
	scanf("%s",s+1); int len=strlen(s+1);
	for (int i=1;i<=len;i++) {
		if (s[i]=='(') t.push('(');
		else {
			if (t.size()&&t.top()=='(') t.pop();
			else t.push(')');
		}
	}
	int cnt1=0,cnt2=0;
	while (t.size()) {
		 if (t.top()==')') cnt1++;
		 else cnt2++;
		 t.pop();
	}
	if (cnt1%2==0&&cnt2%2==0) printf("%d\n",(cnt1>>1)+(cnt2>>1));
	else printf("%d\n",(cnt1>>1)+(cnt2>>1)+2);
	return 0;
}
```

---

