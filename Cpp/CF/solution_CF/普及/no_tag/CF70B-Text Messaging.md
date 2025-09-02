# Text Messaging

## 题目描述

Fangy the little walrus, as all the modern walruses, loves to communicate via text messaging. One day he faced the following problem: When he sends large texts, they are split into parts each containing $ n $ characters (which is the size of one text message). Thus, whole sentences and words get split!

Fangy did not like it, so he faced the task of breaking the text into minimal messages on his own so that no sentence were broken into pieces when it is sent and the number of text messages to be sent would be minimal. If two consecutive sentences are in different messages, the space between them can be ignored (Fangy does not write this space).

The little walrus's text looks in the following manner:

```
TEXT ::= SENTENCE | SENTENCE SPACE TEXT
SENTENCE ::= WORD SPACE SENTENCE | WORD END
END ::= {'.', '?', '!'}
WORD ::= LETTER | LETTER WORD
LETTER ::= {'a'..'z', 'A'..'Z'}
SPACE ::= ' '
```

SPACE stands for the symbol of a space.

So, how many messages did Fangy send?

## 说明/提示

Let's take a look at the third sample. The text will be split into three messages: "Hello!", "Do you like fish?" and "Why?".

## 样例 #1

### 输入

```
25
Hello. I am a little walrus.
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
How are you?
```

### 输出

```
Impossible
```

## 样例 #3

### 输入

```
19
Hello! Do you like fish? Why?
```

### 输出

```
3
```

# 题解

## 作者：_ouhsnaijgnat_ (赞：3)

## 思路

我们可以将要发的消息输入进来，如果遇到标点符号，就用一个字符串数组存下来，表示一句话。

$x$ 表示有多少句。我们可以遍历这 $x$ 句话，如果长度大于 $n$ 就输出无解。

如果发现两句话可以一起发，肯定要一起发。

最后在看共有多少句话，输出。

---

## 作者：Eason_AC (赞：2)

## Content
有一个短信软件最多只能够上传长度为 $n$ 的消息。现在你有一段话，但不一定能够一次发出。这段话由若干句话组成，以 ``.``、``?`` 或者 ``!`` 为结尾。你不能够将一句话拆开来发，但是如果容量允许，你可以将几句话合并起来发送。求最少需要发送几次。

请注意，**同时发送多句话时句与句之间要加上一个空格**。

**数据范围：$2\leqslant n\leqslant 255$。**
## Solution
我们将每句话分开来存储，然后一个一个加进去，碰到有一句话超过了 $n$ 就肯定不可能了，否则放进去尽量多的句子，直到不能够再加进去再一次记录答案。
## Code
```cpp
int n, cnt = 1, iee, ans;
string all;
struct sentences {
	int len;
	string s;
}a[257];

int main() {
	getint(n);
	getline(cin, all);
	int alllen = all.size();
	_for(i, 0, alllen - 1) {
		if((all[i] == '.' || all[i] == '?' || all[i] == '!') && i != alllen - 1)	a[cnt++].s += all[i++];
		else	a[cnt].s += all[i];
	}
	_for(i, 1, cnt)	{
		a[i].len = a[i].s.size();
		if(iee + a[i].len + (iee ? 1 : 0) > n) {
			if(!iee || a[i].len > n)	return printf("Impossible"), 0;
			else	ans++, iee = 0;
		} 
		iee += a[i].len + (iee ? 1 : 0);
	}
	printf("%d", ans + 1);
	return 0;
}
```

---

## 作者：wkjwkj (赞：2)


[可能更好的阅读体验](https://mywkj.github.io/2020/03/30/cf70b-ti-jie/)

[原题链接](https://codeforces.ml/problemset/problem/70/B)

- 首先，由于题目中的字符串出现了空格，所以我们就不能使用```scanf```或是```cin```了，因为它们遇到空格就会自动停止，所以这里就要介绍一个函数```getline```。

  使用方法为:

  ```cpp
  string h;
  getline(cin,h);
  ```

  这样我们便可以读入一整行。

- 解决了输入问题，我们来看一下题面。题目中要求**最少要发几条短信**，并且每一句话**不能割断**,所以我们便可以得出一个非常简单的策略，不停的将每一句话累加到一条短信中，直到超过了短信的最大容量。此时我们便新建一条短信，把使短信超容量的那句话放到新短信内，同时将刚才的短信发出(即```ans++;```)，如果一条短信内只有一句话并且超容量，则输出``` Impossible```.

- 接下来还有一个问题要解决，就是如果一句话单独发出,比如样例一中

  ```php
  Hello. I am a little walrus.
  如果一条信息发出则为:Hello. I am a little walrus.
  如果以两条信息发出则为:Hello.
                        I am a little walrus.
  ```

  可以看出第二种发出方式会少一个空格。

  如果不处理的话，遇到这组样例便会WA

  ```php
  21
  Hello. I am a little walrus.
  正确输出:
  2
  错误输出:
  Impossible
  ```

现在我们来看一下代码吧：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string txt;
int end[10005];
int m=0;
int ans=0;
int main()
{
	scanf("%d\n",&n);
	int now=0;
	getline(cin,txt);
	int len=txt.length();
	int leng=0;
	int first=0;//特判第一句话开头没空格
	for(int i=0;i<=len-1;i++)
	{
		if(txt[i]!='.'&&txt[i]!=','&&txt[i]!='?'&&txt[i]!='!'){
			leng++;
			continue;
		}//leng搜索的就是每一句话的长度
		leng++;
		if(leng-first>n){
			puts("Impossible");
			return 0;
		}
		if(now==0)now+=leng-first,leng=0,first=1;//注意空格
		else{
			if(now+leng>n){
				ans++;
				now=leng-1;
				leng=0;
			}
			else now+=leng,leng=0;//一起发句首空格无需过滤
		}
	}
	ans++;//将最后一条短信累加如答案中
	printf("%d\n",ans);
}
```



---

## 作者：CHENRUIJIE (赞：2)

思路很简单：处理出每一句话，在进行贪心——每一句话不断叠加。		
下面附上代码：		
```
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+5;
char c[N];
int n,m=1,ans;
vector<int>v;
inline bool _end(char h){return (h=='?'||h=='.'||h=='!');}
int main()
{
	cin>>n;
	gets(c);
	gets(c);
	for(int i=0;i<strlen(c);i++)
	{
		if(!_end(c[i]))m++;
		else{
			v.push_back(m);
			if(m>n)
			{
				cout<<"Impossible\n";
				return 0;
			}
			m=0;
		}
	}
	for(int i=0;i<v.size();i++)
	{
		if(m+v[i]+1<=n&&m>0)m+=v[i]+1;
		else{
			m=0;
			ans++;
			m=v[i];
		}
	}
	cout<<ans;
}
```

---

## 作者：feiji_code (赞：1)

# 个人理解：
一道贪心题目，设一次发送的字符数为 $n$ 在不拆分任意一个句子的情况下让发送次数最少，如果不可能发送则输出 ```Impossible```。

遍历字符串 $a$ 如果 $a_i$ 等于 ```!``` 、```.``` 或 ```?``` 检查长度是否大于 $n$，如果大于 $n$ （装不下了）那么就下一次发送（单句大于 $n$ 输出 ```Impossible```），否则装下个句子。
###### 为什么有人用 ```vector```。

## AC 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
string a;int b[10000],n,ju,tot=1;
bool pd(char c){if(c=='!'||c=='?'||c=='.')return 1;else return 0;}
int main() {
	scanf("%d",&n);cin.get();//吃换行
	getline(cin,a);
	int len=a.size();
	int ans=0,cnt=0,temp=n;
    for(int i=0;i<len;){
    	ans=0;
    	while(!pd(a[i])) ans++,i++;
		ans++;i++;
  		if (temp == n) temp -= ans;
		else {
			if (temp >= ans) temp -= ans;//装的下
			else temp=n-ans+1,tot++;
		}
		if (temp < 0){
			puts("Impossible");
			return 0;
		}
		
	}
	cout<<tot<<'\n';
    return 0;
}
```


---

## 作者：Jerrywang09 (赞：1)

### 先说几句

感谢楼上 李嘉欢 提出修改意见！

这题其实只是一道简单的模拟。我觉得难度最好是 普及-。 

### 解题思路

先是输入数据。想说一点：

输入整数后，如果下面要 getline 输入字符串，要用
```cpp
cin.get();
```
把换行符吃掉。

建立一个动态数组/链表/ vector $a$，存放每个句子的长度。具体的处理就是，碰到标点符号这个句子就结束了。特别要注意过滤两个句子中的空格。

遍历一遍 $a$。如果出现长度已经大于短信容量 $n$ 的句子长度，直接结束程序，有且仅有这种情况，应该输出 "Impossible"。

现在，我们令变量 $cnt$ 为当前短信的总长度，$ans$ 为最终的答案（短信数量）。先让 $cnt$ 为第一句话的长度，则 $ans$ 的初始值应设为 $1$。

让下标 $i$ 继续向后遍历。如果不需要换行，则
```cpp
cnt+=a[i]+1;
```
否则另起一条短信：
```cpp
ans++;
cnt=a[i];
```
至于为什么第一种情况要有一个 "+1"，只是因为题目中有详细的要求：

 _**注：每两句话叠加在一起要多一个空格**_ 
 
最后输出 $ans$，就大功告成了！

### 奉上代码

千万不要抄，小心棕名！
```cpp
// 70B Text Messaging 
#include <bits/stdc++.h>
#define var long long
using namespace std;

bool isDigit(char c) 
{
	return c=='.' || c=='?' || c=='!';
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n; cin>>n;
	cin.get();
	string s; 
	getline(cin, s);
	//cout<<s;
	int cnt=0;
	vector<int> a;
	for(int i=0; i<s.size(); i++)
	{
		if(s[i]==' ')
		{
			if(i>0 && isDigit(s[i-1]))
				continue;
		}
		cnt++;
		if(isDigit(s[i]))
		{
			a.push_back(cnt);
			cnt=0;
		}
	}
	
	/*
	for(int i=0; i<a.size(); i++)
		cout<<a[i]<<" ";
	cout<<endl;
	*/
	
	for(int i=0; i<a.size(); i++)
		if(a[i]>n)
		{
			cout<<"Impossible"；
			return 0;
		}
	
	cnt=a[0];
	int ans=1;
	for(int i=1; i<a.size(); i++)
	{
		if(cnt+a[i]+1<=n)
			cnt+=a[i]+1;
		else
		{
			ans++;
			cnt=a[i];
		}
	}
	cout<<ans;	

    return 0;
}

```


---

## 作者：codeLJH114514 (赞：1)

### 题目大意

给你一段话，一个人要把这段话发出去。他一次只能发$\ n\ $个字符，且必须是几个连续的句子。求最少要发几次?（以 `!` `?` `.`结尾的就是一句，消息中两个句子必须以一个空格隔开）

无解输出 $\texttt{Impossible}$ (首字母大写)

### 数据范围

$2 \leqslant n \leqslant 255$

字符串长度 $\leqslant 10 ^ 4$

### 解题思路

先把每个句子从字符串中分离出来。

如果有任何一个句子的长度 $>n$ 则无解。

可以用一个贪心的思想，每一次发送都尽可能的叠加。

(贪心时不需要使用原字符串，所以分离时可以直接存长度。)

注意输入时有空格，所以不能用 cin / scanf，要用 getline。

```cpp
getline(cin, string_name); // 读入一行数据，存在string_name中。
```

坑：贪心前必须在数组里加入一个超长的字符串，否则最后一次发送不会被算。

### 代码

```cpp
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
string a;
int n, sz, ans, nw;
string now;
vector<int> s;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    cin.get();
    getline(cin, a);
    sz = a.size();// 分离所有句子
    for (int i = 0; i < sz; i++) {
        char c = a[i];
        if (c == '.' or c == '!' or c == '?') {
            i += 1; // 跳过句子后的空格
            s.push_back(now.size() + 1); // 直接存长度，+1是算标点
            now.clear();
        } else
            now += c;
    }
    for (auto i : s) // 判断无解
        if (i > n)
            goto impossible;// 断定无解
    nw = -1;
    s.push_back(n + 1);
    for (auto i : s) // 贪心处理
        if (nw + i + 1 > n) {
            nw = i;
            ans += 1;
        } else
            nw += i + 1;
    cout << ans << "\n";
    exit(0);
    impossible:
    cout << "Impossible\n";
    return 0;
}
```

### 时间复杂度

最多只有一重循环，时间复杂度 $O(n)$ 。 (或者说 $O(a.\operatorname{size}())$)

实际用时 $120ms$，实际空间 $40kb$

---

## 作者：BLuemoon_ (赞：0)

[link](https://www.luogu.com.cn/problem/CF70B)

## 题意

告诉你一句话的最大容量 $n$ 和一个字符串 $s$，$s$ 是短信内容。现在要发短信，在这个字符串中每出现 `.` 或 `!` 或 `?` 就代表一句话的末尾。问最少要发几条短信。若无解，输出 `Impossible` 。

## 思路

贪心思想，如果这一句话可以接在上一句后面，那就接上去。否则新建一个消息。

无论如何，一个句子一条消息，只要每个句子的长度都小于 $n$，那就肯定有解。所以无解情况只有可能是某一个句子长度大于 $n$。这个可以和贪心一起判断。

## 易错点

单词和单词中间有空格，用 `cin` 只能读到一个单词，所以字符串要用 `getline` 来读。不会 `getline` 的同学看[这里](https://blog.csdn.net/m0_52824954/article/details/128194817)。

读 $n$ 时，`cin` 遇到换行或空格会直接停止输入，不会把换行读掉，所以要 `getline` 两次。第一次读掉第一行的换行，第二次读取消息字符串。

## ~~你们最想看的~~代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, sz, tot = 1, c; // tot是最终答案，c是目前这个消息还剩余多少字符可以发
string s;
bool chk(char c) { //判断句子是否结束
  return (c == '.' || c == '?' || c == '!');
}
int main() {
  cin >> n;
  getline(cin, s); //cin不会把第一行的换行读掉，所以要getline两次
  getline(cin, s);
  sz = s.size();
  s = ' ' + s; //骚操作，让字符串可以从1到n遍历
  c = n; //初始化c
  for (int i = 1; i <= sz; ) { //遍历字符串
    int t = 0; //t是目前句子长度
    while (!chk(s[i])) { //如果句子还没有结束
      i++, t++; //下一个字符，句子长度加1
    }
    i++, t++; //前进到下一个句子
    if (c != n) { //如果目前这条消息已经有字符了
      if (c >= t) { //如果还放得下这个句子
        c -= t;
      } else { //否则新建一条消息
        tot++;
        c = n - t + 1;
      }
    } else { //如果目前这条消息还一个字符都没有
      c -= t; //加入句子
    }
    if (c < 0) { //如果加上这条消息后发不出去了那就无解
      cout << "Impossible\n";
      return 0;
    }
  }
  cout << tot << '\n';
  return 0;
}
```

---

## 作者：Po7ed (赞：0)

**[题目传送门](https://www.luogu.com.cn/problem/CF70B)**

### 题意简介
有以下递归定义：
```
消息 = 句子 or 句子 空格 消息
句子 = 单词 空格 句子 or 单词 结尾
结尾 = {'.', '?', '!'}
单词 = 字母 or 字母 单词
字母 = {'a'..'z', 'A'..'Z'}
空格 = ' '
（结尾为句子结尾。）
```
现在有一个字符串 $s$，问最少将 $s$ 拆分成多少个**长度不超过 $n$ 的消息**发出。
### 解法
#### 思路
首先 $s$ 中的句子明显**不可以调换顺序**，所以只有**相邻**的句子能合并成一个消息。

具体地说，如果两个相邻的句子或消息 $a$ 和 $b$，若 $|a|+1+|b|\le n$，则可合并为 $a+b$。当然，合并后的消息也**可以再次合并**。

**注意：两个长度相加要再加 $1$，因为消息的定义之一为 `消息 = 句子 空格 消息`，空格也占一个长度。**

所有句子的内容在本题中并不重要，只需知道它们的长度即可。
#### 算法流程
- 首先读入 $n,s$，处理出 $s$ 中每个句子的长度。
- 将第一个句子的长度存入 vector 中。
- 若还有句子，则尝试合并。
  - 如果两个相邻的句子或消息的长度相加**再加 $1$** 小于等于 $n$，则合并。
- 继续合并。

#### 代码
有注释。

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define c s[i]
int main()
{
	int n;
	scanf("%d\n",&n);//一定要读入回车，否则 getline 会出错
	string s;
	getline(cin,s);//读入一整行
	int len=0,siz=s.size();//len:当前句子长度 siz:整个字符串长度
	vector<int> mes;
	for(int i=0;i<siz;i++)
	{
		if(c=='.'||c=='?'||c=='!')//如果句子结束
		{
			len++;
			if(len>n)//如果超限，输出不可能
			{
				puts("Impossible");
				return 0;
			}
			if(!mes.empty()&&mes.back()+len+1<=n)//能合并
			{
				mes.back()+=(len+1);//就合并
			}
			else
			{
				mes.push_back(len);//创建新消息
			}
			// printf("%d\n",len);
			i++;//跳过空格
			len=0;
		}
		else
		{
			len++;//否则长度加 1
		}
	}
	printf("%d\n",mes.size());//输出消息数量
	return 0;
}
```

---

## 作者：Link_Cut_Y (赞：0)

首先思路很明确：由于句子不能断开，所以当这句话能乘这个短句的时候就放在这句话里发送，否则放在下一句。

然后题意稍微有点不明确。忽略两句话之间的空格是指：原本每两个短句之间都有空格。但是分成若干个句子后，每个句子开头的空格可以去掉。

唯一需要注意的一点是字符串需要整行读。用 `getline()` 读入即可。

不知道题解中的代码为什么长得这么奇怪。甚至还用到了 `STL::vector`。

```cpp
int main() {
	cin >> n; getchar();
	getline(cin, s);
	int len = s.size(); 
	s = ' ' + s;
	int tmp = n, ans = 1;
	for (int i = 1; i <= len; ) {
		int cnt = 0;
		while (s[i] != '.' and s[i] != '!' and s[i] != '?')
			i ++ , cnt ++ ;
		cnt ++ ; i ++ ;
		if (tmp == n) tmp -= cnt;
		else {
			if (tmp >= cnt) tmp -= cnt;
			else tmp = n - cnt + 1, ans ++ ;
		}
		if (tmp < 0)
			return puts("Impossible"), 0;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF70B)

## 思路

一道字符串模拟题，用 getline 读入后循环遍历判断每个句子。定义一个变量记录每句话的长度，注意删去空格。如果当前所有的话的长度大于 $n$，就输出 ``Impossible``。

- 由于 getline 读入时会把换行符也算一句，所以要连续 getline 两遍。

## 代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n,ans,len,start,now;
int main(){
    cin>>n;
    getline(cin,s);
    getline(cin,s);
    for(int i=0;i<s.length();++i){
        if(s[i]!='.'&&s[i]!='?'&&s[i]!=','&&s[i]!='!'){
            len++;
            continue;
        }
        len++;
        if(len-start>n){
            cout<<"Impossible\n";
            return 0;
        }
        if(!now){
            now=len-start;
            len=0;
            start=1;
        }
        else{
            if(now+len>n){
                ++ans;
                now=len-1;
                len=0;
            }
            else{
                now+=len;
                len=0;
            }
        }
    }
    cout<<ans+1<<endl;
    return 0;
}
~~~

[已 AC](https://www.luogu.com.cn/record/97084513)

---

## 作者：Back_Stuff (赞：0)

本蒟蒻又来写~~水题~~题解了！

## 解法：字符串模拟+贪心

首先题目给出每条短信的最大容量 $n$，
和所有的短信组成的字符串 $s$，注意这里要用`getline`。

我们可以遍历字符串，遇到标点就截取这句话，用`substr`函数。

题目说不可截断短信，所以我们就用贪心。

1. 能装进一条短信就装。

2. 装不下就新建一条短信，短信个数加一。

最后将短信个数输出就行了，结合上文写出代码。

AC代码就不给了。

---

## 作者：FwbAway (赞：0)

把每一句话都单独列出来，进行贪心处理，不断往上叠加。

题目说至少能发几条，并且不能隔断，所以我们把所有字都放入一条短信，直到这条短信没法再放为止，就放入下一条短信。

提示一下：输入因为他说有空格，所以最好的方法用```
getline```函数.

这样我们可以读入带空格的一整行了。

设一个下标 $i$，让 $i$ 往后去遍历，直到不能输入了为止。

代码略。

---

