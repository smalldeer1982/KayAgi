# Alphabetic Removals

## 题目描述

You are given a string $ s $ consisting of $ n $ lowercase Latin letters. Polycarp wants to remove exactly $ k $ characters ( $ k \le n $ ) from the string $ s $ . Polycarp uses the following algorithm $ k $ times:

- if there is at least one letter 'a', remove the leftmost occurrence and stop the algorithm, otherwise go to next item;
- if there is at least one letter 'b', remove the leftmost occurrence and stop the algorithm, otherwise go to next item;
- ...
- remove the leftmost occurrence of the letter 'z' and stop the algorithm.

This algorithm removes a single letter from the string. Polycarp performs this algorithm exactly $ k $ times, thus removing exactly $ k $ characters.

Help Polycarp find the resulting string.

## 样例 #1

### 输入

```
15 3
cccaabababaccbc
```

### 输出

```
cccbbabaccbc
```

## 样例 #2

### 输入

```
15 9
cccaabababaccbc
```

### 输出

```
cccccc
```

## 样例 #3

### 输入

```
1 1
u
```

### 输出

```
```

# 题解

## 作者：Eason_AC (赞：4)

## Content
给定一个长度为 $n$ 的仅含小写字母的字符串，执行 $k$ 次如下操作：
- 如果字符串中有 `a` 这个字母，删除从左往右第一个 `a`，并结束操作，否则继续操作；
- 如果字符串中有 `b` 这个字母，删除从左往右第一个 `b`，并结束操作，否则继续操作；
- 以此类推，如果所有字母都按照如上方式删除完了，那么结束操作。

现在请你求出操作后的字符串。

**数据范围：$1\leqslant n,k\leqslant 4\times 10^5$。**
## Solution
直接从左往右扫过去，按照上面的方式删除每个字母，直到删除完 $k$ 个字符为止即可。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstring>
using namespace std;

string s;
int n, k, vis[400007];
char cur = 'a';

int main() {
	scanf("%d%d", &n, &k);
	cin >> s;
	while(1) {
		int flag = 1;
		for(int i = 0; i < n; ++i)
			if(s[i] == cur) {
				vis[i] = 1;
				k--;
				if(!k) {flag = 0; break;}
			}
		if(!flag) break;
		cur++;
	}
	for(int i = 0; i < n; ++i)
		if(!vis[i]) printf("%c", s[i]);
	return 0;
}
```

---

## 作者：良知 (赞：4)

#### 题目大意：n为字符串长度，m为删除字符个数，要按照字母表顺序从前往后删除字符.

例如：6 3 bbcabc   就是说长度为6的字符串，要求删去3个。

首先删字典序最小的a---->bbcbc

然后删除两个当前字典序最小的——b，从后向前删除，答案就是cbc。

由于~~我太懒~~方便，我是用了两个map。mp表示作为下标的字符有几个，mp1表示作为下标的字符要删多少.

最后从前往后扫，遇到一个字符，如果mp1==0就不用删了，输出；否则就continue，mp1[i]--.

代码显而易见：

```
#include<bits/stdc++.h>
using namespace std;
map<char , int> mp,mp1;
char str[400005];//这里选择用字符数组处理输入
int main() {
	int n,m;
	scanf("%d%d",&n,&m);
	scanf("%s",str+1);
	
	for(int i=1;i<=n;++i){//存储字符个数
		mp[str[i]]++;
	}
	for(char c='a';c<='z';c++){//模拟删字母过程
		if(mp[c]>m){//如果当前字母数量比还要删的数量多，删去m个该字母，跳出循环
			mp1[c]=m;break;
		}
		else{
			mp1[c]=mp[c];//有几个删几个
			m-=mp1[c];//更新现在的m
		}
	}
	
	for(int i=1;i<=n;i++){
		if(mp1[str[i]]==0)printf("%c",str[i]);
		else mp1[str[i]]--;//由题目分析得
	}
	printf("\n");
	return 0;
}

```

---

## 作者：mzy2006 (赞：2)

**话说这道题目不是特别难呢，不过挺考验~~英语水平~~读题能力的。读懂题目后哪里还是黄题，明明是红题QAQ。先上代码**
```cpp
#include<iostream>
using namespace std;
int main()
{
	char i,x,a[400010];//数组开大，防RE
	int j,n,m;
	cin>>n>>m;//n是字母个数，m是操作个数
	for(j=1;j<=n;j++)
	cin>>x,a[j]=x;
	for(i='a';i<='z';i++)
	for(j=1;j<=n;j++)//n<=400000,直接暴力，27*400000不会T
	{
		if(m>0)//当可以执行操作时，运行算法
		{
			if(i==a[j])//从左向右尝试
			a[j]='$',m--;//符合条件标记‘$’，等同于删去
		}
		if(m==0)//如果操作次数为0，输出
		{
			for(j=1;j<=n;j++)
			if(a[j]!='$')//即未删去
			cout<<a[j];
			return 0;
		}
	}
 } 
```

---

## 作者：MY_Lee (赞：1)

#### 闲聊：

> sort 大法吼啊。

---
#### 翻译:
你现在有一个长度为 $n$ 的只有小写字母的字符串 $s$。你要做 $k$ 次操作，每次需要：
- 如果有 $a$，那么将最左边的$a$删除。
- 如果没有 $a$，有 $b$，那么将最左边的$b$删除。
- 以此类推$\cdots\cdots$

输出 $k$ 次操作后的字符串。

$1\le k\le n\le 400000$

---
#### 思路：
首先发现有两个比较量:位置和字典序。于是我们很快想到使用**多条件排序**解决。我们可以定义一个 struct，一个存储当前的位置，一个存储字符。

重载一下小于号，按字典序排，相同字母按位置从小到大来排。
```cpp
bool cmp1(Str x,Str y){//Str是我定义的struct：c表示字符，pos表示位置
	return x.c<y.c||//字典序
		   x.c==y.c&&x.pos<y.pos;//如果一样则比较位置
}
```
---
然后直接把前$k$个~~扔~~了！

怎么扔？

很简$(qi)$单$(pa)$，输出的时候直接从 $k+1$ 开始输出。

注意：sort 要两遍，第一次搞定以后，$s$ 串的顺序还是乱滴，你总不会一个一个去找吧。

于是乎，我们再将它们按位置从小到大$sort$一遍。
```cpp
bool cmp2(Str x,Str y){
	return x.pos<y.pos;//按位置从小到大来
}
```
---
#### 代码：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
struct Str{
	int pos;//表示位置
	char c;//表示这个字符
};
Str s[400005];//存储字符串s
int n,k;
bool cmp1(Str x,Str y){//第一遍按字典序排
	return x.c<y.c||//字典序
		   x.c==y.c&&x.pos<y.pos;//一样则比较位置
}
bool cmp2(Str x,Str y){//第二遍按位置排
	return x.pos<y.pos;//位置
}
int main(){
	scanf("%d%d\n",&n,&k);//注意这里要把\n"吃"掉，不然它第一个字符是"\n",我在这里卡了一次。
	for(int i=1;i<=n;i++){
		s[i].pos=i;//初始化位置
		scanf("%c",&s[i].c);//输入
	}
	sort(s+1,s+n+1,cmp1);
	sort(s+1+k,s+n+1,cmp2);//Q:为什么从s[k+1]开始？ A:s[1]……s[k]都被"扔"掉了
	for(int i=k+1;i<=n;i++){//从不被扔掉的开始
		 printf("%c",s[i].c);//输出
	}
	printf("\n");//什么都没有输出空行
	return 0;
}
```
---
#### 番外：

sort 大法吼啊！

---

## 作者：RainFestival (赞：1)

这道题目用链表

首先统计一下a,b,c,d,……,z的数量与位置

然后把字符串建一个链表

删除时就可以O(n)了

然后就过啦





---

## 作者：yzy4090 (赞：0)

[原题链接](https://www.luogu.com.cn/problem/CF999C)
 
本题要求将给定的字符串按如下方式处理：  
1. 若字符串中存在 $\tt a$，则删除下标最小的 $\tt a$，否则转至 2；
2. 若字符串中存在 $\tt b$，则删除下标最小的 $\tt b$，否则转至 3；  
...  

累计删除 $k$ 个字符后终止处理。输出处理后的字符串。  

思路：模拟处理方式。使用 `vst[]` 数组标记，相当于删除。代码如下：  
```cpp
#include<iostream>
#include<cstring>
using namespace std;
int i,n,want;
char str[400005];
bool vst[400005];
int main() {
	scanf("%d%d%s",&n,&want,str);
	for(char a='a'; a<='z'; ++a) {
		i=0;
		while(i<n) {
			if(str[i]==a)
				vst[i]=true,--want;
			if(!want)break;
			++i;
		}
		if(!want)break;
	}
	for(i=0; i<n; ++i)
		if(!vst[i])
			putchar(str[i]);
	return 0;
}
```

---

## 作者：Paris_Bentley (赞：0)

一篇橙色题题解来了~~~

题目简单翻译：有一个字符串共有n个小写字母，现在需要删除m个字母。
这m个字母的删除规律是，从前到后，从a开始删除，然后删除b，以此类推，直到最后删除字母数为m,输出剩下的字符。

题目的做法比较多元，这里使用的是桶的方法解题：

1.输入后用桶记录每个字母的出现次数。

2.从字母a到z，从前到后找前k个桶的数量是否>m，如果大于，就保留第一个k的位置。也就是说字母序为k以前的字母都不要，字母序为k的字母标记，不一定用不用。

3,输出，k以前的数字不输出，k以后的数字都输出，k对应的数字

4.注意特判，如果输入的数字都不要怎么办，所以k的初始值不能是首字母，而应该是字母的末端。

具体做法可以参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
string str;
int n,m;
int a[30];
int main()
{
	scanf("%d%d",&n,&m);
	cin>>str;
	memset(del,false,sizeof(del));
	memset(a,0,sizeof(a));
	for (int i=0;i<str.length();i++)
		a[str[i]-'a']++; //桶 
	int s=0;//记录已经删除数字 
	int k=26; //可能全部删除 
	for (int i=0;i<26;i++)
	{
		if (s+a[i]>m)
		{
			k=i;//k以前的数字都不要，从后往前删除k
			break;//剩下m-s个需要删除 
		} 
		s+=a[i]; 
	}
	for (int i=0;i<str.length();i++)
	{
		if (str[i]-'a'<k)//必须删除 
			continue;	
		if (str[i]-'a'==k&&s<m)//部分数字需要删除 
		{
			s++;
			continue;
		}
		printf("%c",str[i]);
	}
	cout<<endl;
	return 0;
}
```


。

---

## 作者：Jsxts_ (赞：0)

# 题解 CF999C

[传送门](https://www.luogu.com.cn/problem/CF999C)

# 题意

给你一个长度为 n 的字符串，要求删除 k 个字符，输出删除后的字符串。

删除字符的规则如下：

1、如果字符串里还有至少一个 a ，就删除最左边的 a，直到删完所有的 a；
    
2、如果字符串里还有至少一个 b ，就删除最左边的 b，直到删完所有的 b；

以此类推......直到删完 k 个字母或删完字符串。

# 题解

按题意模拟，在 k 不等于 0 的情况下，一直从左到右删除 a，如果 a 删完了再重新从左边开始删除 b，以此类推。每删除一个字母 k 就减一，直到删完字符串或 k 为 0。

剩下细节在注释中说明。

## Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[27],vis[400010];
char s[400010];
int main() {
	int n,k;
	scanf("%d%d\n",&n,&k);
	scanf("%s",s);//scanf读入，亲测比cin快1秒多 
	int l = strlen(s);
	for (int i = 0;i < l;i ++ ) {
		a[s[i] - 'a' + 1] ++;//记录每种字符出现了几次 
	}
	char ch = 'a';//按题意，从a开始删 
	while (k) {//还需要删时继续做 
		for (int i = 0;i < l && k;i ++ ) { // 同上 
			while (!a[ch - 'a' + 1]) ch ++; //没出现的字符不用考虑 
			if (s[i] == ch) {//要删 
				k --;//删的个数减一 
				vis[i] = 1;//这个字符标记为被删 
				a[s[i] - 'a' + 1] --;//个数减减 
				if (!a[s[i] - 'a' + 1]) break;//删完就退出 
			}
		}
	}
	for (int i = 0;i < l;i ++ ) {
		if (!vis[i]) printf("%c",s[i]);//没被删的就输出 
	}
	return 0;
}
```

用时：1.23s

### 这个做法拿到了最优解，比第二名快接近1秒。

---

## 作者：YuanZhizheng (赞：0)

这题呢，也就是要按照'a'、'b'、'c'...’z'这个字典序，在字符串中删除k个字符，我用变量m代替变量k（个人习惯）。

如果不考虑时间，最容易想到的做法应该是先记录每个字母的数量，然后，按26个字母的顺序，最多遍历26次字符串，依次删除字母，如果m==0就中止即可。

```
#include<bits/stdc++.h>
using namespace std;
char s[400005];
int num[150];
int main()
{
    int i,n,m;
    scanf("%d%d%s",&n,&m,s+1);
    for(i=1;i<=n;i++)
    {
        num[(int)s[i]]++;//计数
    }
    int j;
    while(m)
    {
        for(i=97;i<=122;i++)//每种字母找完了就重新遍历找下一个字母//97和122对应a和z的ASCⅡ码
        {
            for(j=1;j<=n;j++)//遍历
            {
                if(s[j]==i)
                {
                    s[j]='A';//改变成其他字符也行，不是小写字母就行了
                    num[i]--;
                    m--;
                }
                if(m==0||num[i]==0)break;
            }
            if(m==0)break;
        }
    }
    for(i=1;i<=n;i++)
        if(s[i]!='A')printf("%c",s[i]);
    return 0;
}
```
如果没用num数组，进去遍历也是可以的。也就26种字母嘛。

我们再看看，上面的做法，我们删了一个a以后，如果字符串的a没有删完，那么我们要遍历地去寻找下一个a，我们删了一个b以后，如果字符串中b没有删完，那么我们要遍历地去寻找下有一个b...一直重复下去。

那么我们可以想想，有没有什么办法，当我们删除当前这个a以后，可以直接跳到下一个a，而不需要遍历下去呢？

当然是可以的，我们有一种做法叫做链式前向星。

首先，我们应该创建一个head数组，**head['a']保存的是最后一次出现a的位置，head['b']保存的是最后一次出现b的位置，其他字母同理**。

当然，我们可以再创建一个数组next，然后可以得到一个式子:

**next[ i ]=head[ s [ i ] ];**

它所保存的，是当前这个位置的字母上一次出现的地方。

这样，我们接收字符串以后，遍历一次数组，利用head数组，就可以把每个同种字母连接起来。

之后在删除的时候应该怎么删呢？

具体仔细看代码哦！

```
#include<bits/stdc++.h>
using namespace std;
char s[400005];
int Next[400005];
int head[200];
int main()
{
    int i,n,m;
    scanf("%d%d%s",&n,&m,s+1);
    for(i=n;i>=1;i--)/*从后面开始遍历，这样head[]记录的是字母最早出现的位置*/
    {
        Next[i]=head[s[i]];
        head[s[i]]=i;
    }
    int j;
    while(m)
    {
        for(i=97;i<=122;i++)//和上面的做法其实类似，改变的是找字母的方法
        {
            for(j=head[i];j;j=Next[j])//通过Next数组衔接
            {
                s[j]='A';
                m--;
                if(m==0)break;
            }
            if(m==0)break;
        }
        if(m==0)break;
    }
    for(i=1;i<=n;i++)
        if(s[i]!='A')
            printf("%c",s[i]);
    return 0;
}
```
链式前向星的head和next还多用于最短路的SPFA算法，用来保存相同起点的边！

如果直接next数组会编译错误，还是用Next或者nxt这些作为数组变量名吧！


---

