# [ARC014B] あの日したしりとりの結果を僕達はまだ知らない。

## 题目描述

高桥君会分身之术。

今天高桥君想做个单词接龙，但是不巧附近没有朋友，所以决定分身出一个自己来陪自己完。

为了方便起见，高桥君将原本就存在的高桥君称为高桥君。

那么，高桥君和高桥分身君充分享受了单词接龙的乐趣，可悲的是，因为他们不知道单词接龙的规则，所以无法分出胜负。

可是这样的事怎么能忍?

于是高桥君们决定录下自己的发言以得到说过的单词的清单。

单词接龙的规则极其简单。只是遵循以下条件说单词:

1.当前词的开头字母是上一个词的结尾字母。(第一个单词不限)

2.不能使用曾经使用过的单词。

先违反这个规则的一方就输了,所以请你帮高桥君们来判定比赛的胜负。

# 题解

## 作者：BlueDone (赞：8)

~~这题其实并不难~~

>致管理员和之前看过该题解的人 :
>
>对不起,我上次的代码有点问题 , 没有考虑now变量的-1 , 本次代码已经修复错误 , 请放心食用 .
>
>另外 , 求过审QwQ

#### 提示:

> 输出一定要换行!!!
>
> 输出一定要换行!!!
>
> 输出一定要换行!!!

[题目原网站](https://arc014.contest.atcoder.jp/tasks/arc014_2)

### >这题是有关字符串的

首先 , 看到单词我们可以想到要用**字符串** . 同时因为游戏规则需要 , 我们要记录说过的所有单词 . ( 一是要判断本单词**是否重复** , 二是要看**本单词首字母和上一个单词末字母是否相同** ) . 所以 , **字符串数组闪亮登场** !

那么 , 开始 !

### >初始化

先让我们定义一个字符串数组 . 
```
string words[101];//其实原网站 N(1≦N≦100)
```
为了节省时间 , 我们输进来一个就处理一个 . 
```
for(int i=0;i<n;i++)
{
	cin>>words[i];
	//(对该单词进行处理)
}
```

### >判断合法与否

那么怎么处理呢 ? 
```
//个人偏爱函数
bool judge(int now,string word)//now表示回合减一
{
	if(now == 0)//如果这是刚刚开始
		return true;
	
	for(int i=0;i<now;i++)//从第一个单词开始,直到前一个单词
	{
		if(word == words[i])//是否重复
			return false;//如果重复那么这个单词的说出者违规了
	}
	//如果没有重复,循环正常结束

	if(words[now-1][words[now-1].size()-1] == word[0])//判断本单词首字母和上一个单词末字母是否相同
		return true;
	else
		return false;
}
```

没懂 ? 上解析 !

```
words[now-1]//上一个单词 .
words[now-1].size()//上一个单词的长度 .
//为什么要 -1 ? 因为字符串默认从下标0开始存 .
words[now-1].size()-1//上一个单词的末位置
words[now-1][words[now-1].size()-1]//上一个单词的末字母 .
```

### >决定胜负的回合数

yeah ! 就是这样 .

可是 ...... 我咋知道是高桥君违规了还是分身违规了

于是有了以下代码

```
if(!judge(i,words[i]))//i是当前回合数-1(i从0开始,回合数从1开始)
{
	(i+1)&1 ? printf("LOSE\n") : printf("WIN\n");
	return 0;
}
```

又没懂 ? 上解析x2

```
[逻辑表达式] ? [语句1] : [语句2] ;
//如果[逻辑表达式]的值是true,执行[语句1],
//否则(也就是[逻辑表达式]的值是false时)执行[语句2]
```
那么 ......
```
(i+1)&1

//'i'是当前回合数-1(i从0开始,回合数从1开始)
//'i+1'是当前回合数
//'&1'是跟1做位运算
//整句话的意思是判断当前回合数是不是奇数(奇数回合便是高桥君的回合)
```
啥 ? ' & ' 是啥 ?
```
1 & 1 == 1;
1 & 0 == 0;
0 & 0 == 1;
```
那么我们假设当前回合数是 3 .

于是 3 的[byte]二进制是 00000011 , 1 的[byte]二进制是 00000001.

开始位运算 !
```
3 & 1
//在二进制下等价于
00000011 & 00000001
```
让我们列个竖式 . 
```
  00000011
& 00000001
-----------
  00000001

```
所以奇数结果是 1 (true)

自己再列个竖式可得偶数的结果是 0 (false)
~~懒得写了~~

所以那句话的意思是
```
if(!judge(i,words[i]))
//将'回合数-1'和当前单词送去判断,如果答案违规进入if{}
{
	(i+1)&1 ? printf("LOSE\n") : printf("WIN\n");
	//如果是奇数回合违规,那便是高桥君输了
	//如果是偶数回合违规,自然是分身输了(高桥君赢了)
	return 0;//结束程序
}
```

### >万一比赛友好的结束了呢?

how about ... 平局 ?

```
for(int i=0;i<n;i++)
{
	cin>>words[i];
	if(!judge(i,words[i]))
	{
		(i+1)&1 ? printf("LOSE\n") : printf("WIN\n");
		return 0;
	}
}
//走出了循环,证明没有人违规
printf("DRAW\n");//自然而然的平局
return 0;

```

于是我们把程序写完啦~~~

✧*｡٩(ˊᗜˋ*)و✧*｡

#### AC代码附上(与本人提交的略代码不同)
```
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;

string words[101];
int n;

bool judge(int now,string word)
{
	if(now == 0)
		return true;
	
	for(int i=0;i<now;i++)
	{
		if(word == words[i])
			return false;
	}

	if(words[now-1][words[now-1].size()-1] == word[0])
		return true;
	else
		return false;
}

int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		cin>>words[i];
		if(!judge(i,words[i]))
		{
			(i+1)&1 ? printf("LOSE\n") : printf("WIN\n");
			return 0;
		}
	}
	printf("DRAW\n");
	return 0;
}
```

---

## 作者：666DHG (赞：3)

今天又来给水题写题解啦！

其实这题很简单，直接用一个
[```set集合```](http://www.cplusplus.com/reference/set/set/)
就可以解决了
（这一行中有
```Surprise```
）

那么，这题如何用
```set```
来AC呢？

首先我们要来认识
 ```set```
的基本操作：

定义集合：```std :: set <数据类型> 集合名称``` 

定义集合的迭代器： ```std :: set <数据类型> :: iterator 迭代器名称```

>注：此处定义了以下内容：

> 1. ```std :: set <int> Set```
  
> 2. ```std :: set <int> :: iterator it```
  

清空集合：```Set.clear()``` 

插入元素$n$：```Set.insert(n)```

>警告：假如```Set```集合之前已经包含了$n$，则这次插入无效！

删除元素$n$：（通过指定元素来删除）  ```Set.erase(n)```
   
删除元素$n$：（通过迭代器来删除）  ```Set.erase(it)```

查找元素$n$是否在此集合中： ```Set.find(n)```
  
> 如果$n$在此集合中，则其返回值不为```Set.end()```
  
> 所以判断是否在此集合应该这样：
>```cpp
if (Set.find(n) != Set.end()) //找到
else ///没找到
> ```

判断集合是否为空： ```Set.empty()```

获取集合元素总数： ```Set.size()```
  
[获取```set```实例](https://www.luogu.org/paste/2rq5hn72)
  
我的思路如下（伪代码）：

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
string now,last;
set <string> Say;

inline int Print(int i)
  {
  	/*判断输赢*/
  }

int main()
  {
  	/*读入 & 记录第一个词*/
  	for (int i=2;i<=n;i++)
  	  {
  	  	/*读入第 i 个词*/
  	  	if (/*单词没有接上*/) /*输出 & 结束*/
		if (/*这个单词已经被说过*/) /*输出 & 结束*/
		/*记录这个单词*/
		/*更新 last*/
	  }
	/*平局*/
	return 0;
  }
```

完整代码如下
                     
```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
string now,last;
set <string> Say;

inline int Print(int i)
  {
  	if (i%2) printf("LOSE\n");
  	else printf("WIN\n");
  	return 0;
  }

int main()
  {
  	scanf("%d\n",&n);
  	getline(cin,last);
  	Say.insert(last);
  	for (int i=2;i<=n;i++)
  	  {
  	  	getline(cin,now);
  	  	if (now[0]!=last[last.size()-1]) return Print(i);
		if (Say.find(now)!=Say.end()) return Print(i);
		Say.insert(now);
		last=now;
	  }
	printf("DRAW\n");
	return 0;
  }
```
点个赞再走吧QwQ                    

---

## 作者：soho_andy (赞：1)

这道题其实可以用 **map** 
```c
#include <iostream>
#include <cstdio>
#include <map>  //使用map需要这个头文件
using namespace std;
int n; //回合数
char c; //前一个词的结尾字母
string s; //每轮说的词

map<string, bool> m; //表示单词（string）是否使用过（bool）

int main() {
	scanf("%d", &n);
    
	for( int i=1; i<=n; i++ ) {
		cin >> s;
        
		if( i!=1&&c!=s[0] || m[s] ) {
	//不是第一个词 + 前一个词的结尾字母不等于当前单词的开头
	//或者，这个词被用过了
			if( i%2 ) printf("LOSE\n");
                      //因为高桥君第一个说，所以奇数局是他（共两人）
			else printf("WIN\n");
            
			return 0;
		}
        
		c = s[s.size()-1]; //更新
		m[s] = true; //表示：这个词用过了
	}    
	printf("DRAW\n");
    //没输没赢，就是平局
}
```


---

## 作者：02Ljh (赞：0)

## problem
高桥君和高桥分身君在单词接龙,规则是：

- 当前词的开头字母是上一个词的结尾字母(第一个单词不限)。

- 不能使用曾经使用过的单词。

第一个单词是高桥君说的,第二个单词是分身说的,依此类推。

如果高桥君先违反规则，输出 ```LOSE```。

如果高桥分身君先违反规则，输出 ```WIN```。

平局则输出 ```DRAW```。

## tips

对于这道题，我们需要记录上一个单词的末尾字符，与下一个单词的首字母进行比较，如果不一样直接输出，然后结束程序。同时，如果重复记录也是不合法的。

而在进行判重时，而在 STL 库中有一个判重利器就是

```unordered map < string , int > mapp``` 。

用法和 ```map``` 相同，第一个元素作为下标，第二个元素作为下标时赋的值（[更多介绍 link](https://oi-wiki.org/lang/csl/associative-container/)）。

我们可以将每一个输入的单词赋值为 $1$ ，当输入单词已经被标记时结束程序，即可判重。

输出时要注意：atcoder 的题一定要换行！！！

## code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
unordered_map <string,int> mapp;
int n;
void l() { cout<<"LOSE\n"; exit(0); }
void w() { cout<<"WIN\n"; exit(0); }
void d() { cout<<"DRAW\n"; exit(0); }
//exit(0) 结束全局程序
//atcoder 一定要换行！！！
int main()
{
	int n;
	cin>>n;
	int pe;
	string ss;
	char la;//上一个字符
	for(int i=1;i<=n;i++)
    {
        cin>>ss;
        if(i%2==1)//高桥君
        {
            if(mapp[ss]==19) l();//重复输 lose
            mapp[ss]=19;
            if(i==1) { la=ss[ss.size()-1]; continue; }//第一个单词跳过
            if(la==ss[0]) { la=ss[ss.size()-1]; continue; }//更新值
            else l();//不一样输 lose
        }
        if(i%2==0)//高桥君的分身
        {
            if(mapp[ss]==19) w();
            mapp[ss]=19;
            //if(i==1) { la=ss[ss.size()-1]; continue; }
            if(la==ss[0]) { la=ss[ss.size()-1]; continue; }
            else w();
        }
    }
    d();//其他情况输出平局
	return 0;
}

```

---

## 作者：happybob (赞：0)

暴力不香吗

对于每个字符串，在前面暴搜，搜到则为输的一方

还有一种可能，如果前面的最后一个和当前的第一个不一样，当前也为输

代码：
```cpp
#include <iostream>
#include <cstring>
using namespace std;

string s[105];

int main()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }
    for(int i = 2; i <= n; i++)
    {
        bool judge = true;
        if(s[i].front() != s[i - 1].back())
        {
            cout << (i % 2 == 0 ? "WIN" : "LOSE") << endl;
            return 0;
        }
        for(int j = 1; j <= i; j++)
        {
            if(i != j && s[i] == s[j]) //string可以直接互相比较
            {
                judge = false;
                break;
            }
        }
        if(!judge)
        {
            cout << (i % 2 == 0 ? "WIN" : "LOSE") << endl;
            return 0;
        }
    }
    cout << "DRAW" << endl;
    return 0;
}
```


---

## 作者：AveMarina (赞：0)

# set去重+字符串模拟
话说题目名字有点眼熟 ~~，找到你了，水题。~~

### 考虑下那几种情况会导致游戏结束
1. 某个字符串被重复使用
2. 当前字符串的第一个字符和上一个字符串的最后一个字符不同
3. 所有字符串都用完了（没有出现上面两种情况）

### 解决方案
对于1. 而言，我们使用STL里的set就可以方便的判重。

对于2. 而言，每次记录下上次的字符串是什么就行（当然也可以只记录上次字符串的最后一个字符，这里交给读者去做好了~~不是因为懒~~）。另外对于第一个字符串，要进行特殊处理，因为它前面没有字符串。

对于3. 而言，只要出现前两种情况就退出程序，如果整局游戏都没有出现前两种情况，那么3. 就是合法的。

### 如何判断是谁输了
我们假设高桥君的回合从1开始，分身回合从2开始，那么不难发现，如果当前回合数为奇数，就是高桥君输了，否则就是分身输了。

## 喜闻乐见的代码
__仅供参考，切勿抄袭__

```cpp
#include <iostream>
#include <set>
using namespace std;
set<string > sset;
int main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0); 
	int T;
	cin >> T;
	string pre = "1919810";
	string now;
	int cnt = 1;
	while (T--) {
		cin >> now;
		// 首先，对于第一个字符串要进行特判，因为它之前就没有别的字符串了，其次，如果某个字符串
		// 出现了多次，那么不管是否是合法的，都说明有人输了 
		if (now[0] != pre[pre.size() - 1] && pre != "1919810" || sset.count(now)) {
			cout << (cnt % 2 ? "LOSE" : "WIN") << endl;
			return 0;
		}
		// 更新字符串集合、前一个单词、回合数 
		sset.insert(now), pre = now, cnt++;
	}
	cout << "DRAW" << endl;
	return 0;
}
```

---

## 作者：Mr_WA的大号 (赞：0)

我心里只有个梦，想在洛谷成为红名大佬。小学生又来发题解了！

题号：AT509

难度：★★

算法：字符串，模拟

## 开课了！

这一题总体来讲还是比较容易的，直接按照题目的意思来模拟就可以AC了。先输入一个字符串，然后判断它的首字母是否与前一个字符串的尾字母相等。

相等的话，就继续往前找，看看这个字符串是否之前就存在。

如果字符串已经出现过或与前一个字符串的尾字母不相等，就看看是谁输了，之后直接return 0。循环结束后还没有return 0的话，就输出DRAW。

上代码：
```cpp
#include<iostream>
#include<fstream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<string.h>
#include<algorithm>
using namespace std;
int n,m;
string woods[200],wood;
int main()
{
	cin>>n;
	for(int i=1; i<=n; i++)
	{
		cin>>wood;
		for(int j=1; j<i; j++)
			if(woods[j]==wood)
				if(i%2==1)
				{
					cout<<"LOSE"<<endl;
					return 0;
				}
				else
				{
					cout<<"WIN"<<endl;
					return 0;
				}
		if(i>1)
			if(woods[i-1][woods[i-1].size()-1]!=wood[0])
				if(i%2==1)
				{
					cout<<"LOSE"<<endl;
					return 0;
				}
				else
				{
					cout<<"WIN"<<endl;
					return 0;
				}
		woods[i]=wood;
	}
	cout<<"DRAW"<<endl;
	return 0;
}
```
祝大家能AC！

---

## 作者：Misaka屮Mikoto (赞：0)

~~又来刷At的水题了~~
### 思路：
这道题其实可以用hash的做法去做。

- 将之前出现过的字符串的哈希值存成一个数组。

- 每次比对哈希值和首尾字符。

- 判断输赢。

[不知道哈希的点进来（不是本人的博客）](https://www.cnblogs.com/ktao/p/8714513.html)
### hash代码：
```cpp
int uhash()//hash好像是关键字
{
	int cnt=1;
	for(int i=0;k[i]!='\0';i++)
	{
		cnt*=k[i]*(i+1);
		cnt+=k[i]*(i+2);
		cnt%=modn;//modn是一个大质数
	}
	return cnt;
}
```
目的：生成字符串k的哈希值

### 代码部分：

```cpp
//#include<bits/stdc++.h>
#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<string.h>
#define modn 91815541//这可以放一个大质数（质数越大越好，防撞hash，本题数据范围这么大够了）
char k[30];
int ha[103],n,c;//ha是存hash值的数组
int uhash()//生成读入字符串的hash值
{
	int cnt=1;
	for(int i=0;k[i]!='\0';i++)
	{
		cnt*=k[i]*(i+1);
		cnt+=k[i]*(i+2);
		cnt%=modn;
	}
	return cnt;
}
char last;//接龙的末尾字符
int main()
{
	scanf("%d",&n);//读入n
	for(int i=0;i<n;i++)
	{
		scanf("%s",k);//读入字符串
		if(k[0]!=last&&i!=0)//如果这个字符串的开头和上一个字符串的末尾不同
		{
			if(i%2==0)printf("LOSE\n");//高橋君的回合
			else printf("WIN\n");//分身的回合
			return 0;//直接结束
		}
		int u=uhash();//生成k的哈希值
		for(int j=0;j<c;j++)//挨个对比哈希值
			if(u==ha[j])//如果出现过
			{
				if(i%2==0)printf("LOSE\n");//高橋君的回合
				else printf("WIN\n");//分身的回合
				return 0;
			}
		ha[c]=u;//将字符串的哈希值加入数组
		c++;
		last=k[strlen(k)-1];//last定义为这个字符串的尾字母
	}
	printf("DRAW\n");//双方都未违规
	return 0;
}

```

一定要加"\n"换行符



---

