# 「SvR-1」Don't Mozheng. /oh

## 题目背景

**Problem Number:** $\textit{58}$

在 Guluo Academic 群中，大家正在魔怔。

![](https://cdn.luogu.com.cn/upload/image_hosting/iphmcxwz.png)

洛谷博客上的《魔怔导论》：<https://www.luogu.com.cn/blog/supervise/how-to-get-a-mz>。

需要《魔怔导论》（目前更新至 v1.1.1 版本）的 PDF 请于下方「**题目附件**」处下载。

## 题目描述

你得到了 $n$ 条信息，这些信息共有三种类型（注意 $\texttt<\textit{str}\texttt>$ 描述一个名为 $str$ 的字符串，**该字符串不含空格、字符 $\texttt:$ 与 $\texttt/$**，不含两边的尖角括号）：

1. 形如 $\texttt<\textit{str}\texttt{>:}$。意为**接下来一行的一条信息**是名为 $str$ 的用户发的。
2. 形如 $\texttt{/<}str\texttt>$。意为一条名称为 $str$ 的**表情信息**。
3. 形如 $\texttt<\textit{str}\texttt>$。意为一条内容为 $str$ 的文字信息。

你经过长期观察，发现名称为 $\texttt{oh}$ 和 $\texttt{hsh}$ 的**表情信息**具有魔怔的意味。

并且在一段对话中：

- 一个 $\texttt{oh}$ 表情会增加 $a$ 的魔怔值。
- 一个 $\texttt{hsh}$ 表情会增加 $b$ 的魔怔值。
- **其他的任何信息都不会影响魔怔值，魔怔值初始为 $0$**。

现在你需要对于这些信息，计算出总的魔怔值。

## 说明/提示

#### 样例 1 说明

![](https://cdn.luogu.com.cn/upload/image_hosting/mbfgnv8i.png)

如图所示。

#### 数据规模与约定

**本题采用捆绑测试。**

记 $l$ 表示输入中单行信息的最大长度。

$$
\newcommand{\arraystretch}{1.5}
\begin{array}{c|c|c|c}\hline\hline
\textbf{Subtask} & \bm{n\le} & \textbf{特殊性质} & \textbf{分值} \\\hline
\textsf{1} & \le 10 & - & 20 \\\hline
\textsf{2} & \le 100 & - & 20 \\\hline
\textsf{3} & \text{无特殊限制} & \text A & 20 \\\hline
\textsf{4} & \text{无特殊限制} & - & 40 \\\hline\hline
\end{array}
$$

- 特殊性质 $\text{A}$：输入不含有第 3 类信息。

对于 $100\%$ 的数据，有 $1\le n\le 10^4$，$1\le l\le 50$，$1\le a,b\le 10^3$。

## 样例 #1

### 输入

```
7 1 2020
wop:
/yueliang
eoq:
wop_loushang
wop:
eoq_npy_when
eoq:
/oh
dek:
/oh
rif:
NOI2022_rp_++
rif:
/hsh```

### 输出

```
2022```

# 题解

## 作者：封禁用户 (赞：16)

[题目传送门](https://www.luogu.com.cn/problem/P8410)

其实题目是一道让你筛选重要信息题，重要信息如下：

>**该字符串不含空格、字符 $\texttt:$ 与 $\texttt/$**，不含两边的尖角括号

>- 一个 $\texttt{oh}$ 表情会增加 $a$ 的魔怔值。
>- 一个 $\texttt{hsh}$ 表情会增加 $b$ 的魔怔值。
>- **其他的任何信息都不会影响魔怔值，魔怔值初始为 $0$**。


~~这道良心题甚至可以只开 `int` 和 `string`。~~

命名变量： `int n,a,b,ans=0;` 和 `string s;` .这里需要注意的是 `ans` 也就是魔怔值总和初始值为 $0$ ，题目里有，但还是要强调一下。

由题意，首先输入 $n$ , $a$ , $b$ 。

然后题目中写到“如果你的 `getline` 无法正常运作”言下之意就是不能用 `getline` ，所以这里应该用 `while(cin>>s)` 。

接下去就是判断里面有没有包含 $\texttt{/oh}$ 和 $\texttt{/hsh}$ ，有前者增加 $a$ 的魔怔值，有后者增加 $b$ 的魔怔值。

最后 `cout<<ans<<endl;` ，不加 endl 虽然也能过，但它是个好习惯。

代码如下：

```
#include <bits/stdc++.h>
using namespace std;
int n,a,b,ans=0;
string s;
int main()
{
    cin>>n>>a>>b;
    while(cin>>s)
    {
        if (s=="/oh") ans+=a;
        if (s=="/hsh") ans+=b;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：TheCliffSwallow (赞：7)

#### 题意简述
有 $n$ 条消息，如果消息是表情且为 $\texttt {/oh}$，魔怔值加 $a$，如果表情为 $\texttt {/hsh}$，魔怔值加 $b$，魔怔值初始为 $0$，求最后总的魔怔值。
#### 思路
不要想复杂，仔细读题，由题意可得，其他的**任何信息都不会影响魔怔值**且**一行只有一条消息**，所以我们只需要考虑 $str$ 是否等于 $\texttt{/oh}$ 或者 $\texttt{/hsh}$ 并相加对应魔怔值即可。
### AC CODE
```cpp
#include<iostream>
#include<cstring>
#include<string>
using namespace std;
int n,a,b,ans;
string str;
int main(){
	std::ios::sync_with_stdio(false);//取消cin于stdin的同步，加速cin
	cin>>n>>a>>b;
	for(int i=1;i<=2*n;i++){//有2n行
		cin>>str;//输入名字或消息
		if(str=="/oh")	ans+=a;//如果是oh表情就加a魔怔值
		if(str=="/hsh")	ans+=b;//如果是hsh表情就加b魔怔值
	}
	cout<<ans;
	return 0;
}
```
最后再说几句：

魔怔人是不幸的，也是不争的，我们要断绝魔怔思想，反对魔怔思潮。

---

## 作者：wimg6_ (赞：5)

## 「SvR-1」Don't Mozheng. /oh 题解

### 解法

> 没有思路怎么办？读题！

发现题目中只有三种情况，且描述清晰，直接模拟即可，时间复杂度 $O(n)$，可以通过本题。

同时，我们可以在读入时直接操作，不需要用数组存储。

对于第一类信息，对答案无贡献，故可以不考虑。而在输入数据中，除开 $n$，$a$，$b$ 的读入外，行数不能被 $2$ 整除的即为第一类信息。故直接跳过。

```
if(i%2==1) continue;
```

接下来再进行判断行数能被 $2$ 整除的行内信息。

若该信息为 `/oh`，则 $s=s+a$。

若该信息为 `/hsh`，则 $s=s+b$。

```
if(str=="/oh") s+=a;
else if(str=="/hsh") s+=b;
```

### 启发

请读者自主思考以下问题，若想不出来则可以看提示。

1. 什么情况下可以模拟？

2. 什么情况下可以边读入边操作？

3. 遇到冗余信息怎么办？

回答：

1. 事实上，几乎所有题目都可以进行模拟。模拟即按题目所给步骤，在程序中按步骤分步处理。在考试中，保证时间复杂度的情况下，对题目进行模拟能有效地获得分数。通常，难题所给部分分也为模拟分。

2. 每一条需要模拟的信息与上下的信息无关联性时，即可边读入边操作，可以有效节省空间复杂度。对于初学者遇到的题目，可能不会卡空间复杂度，但是遇到省选及以上题目会出现卡空间复杂度的情况。

3. 遇到冗余信息，直接跳过不处理即可。

---

## 作者：CSP_Sept (赞：4)

Official Editorial.

## 题解

考虑到第一类信息是没用的，并且在 $2\cdot n$ 条题解中全部位于第奇数条。

于是循环 $n$ 次，每次读入两个字符串后迅速丢弃第一个。

剩下一个，经过仔细读题后发现只有单独的 $\texttt{/oh},\texttt{/hsh}$ 才能被计算上。

于是直接用 string 类的相等功能比较即可。

当然没有空格，所以可以随便读入。

注意到 $10^4\times 10^3=10^7<10^9$，所以不需要 long long。

然后 Subtask 1~3 是为了部分分而部分分，有什么 $O(n^w)(w>1)$ 做法欢迎分享。

## 题外

极个别题解指出魔怔是有害的，我非常反对。

正如我在 **[魔怔导论](https://www.luogu.com.cn/blog/supervise/how-to-get-a-mz)** 中提到的，「真正的魔怔背后必定有其原因」，无法走入他人世界就随便评价的，未免有些不好。

## 代码

```cpp
// One possible method.
while(n--){
	cin >> s; cin >> s;
	if(s == "/oh") sum += a;
	if(s == "/hsh") sum += b;
}

// Another possible method.
while(n--){
	getline(cin, s); getline(cin, s);
	if(s == "/oh") sum += a;
	if(s == "/hsh") sum += b;
}
```

---

## 作者：幸存者 (赞：3)

## 思路
定义一个变量 $ans$ 存储魔怔值，检测到表情 $\text{oh}$ 就将 $ans$ 加上 $a$，检测到表情 $\text{hsh}$ 就将 $ans$ 加上 $b$ 即可。

第一类信息没有任何作用，可以直接忽略。

注意：表情前面是正斜杠而不是反斜杠。
## $\text{AC Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n, a, b, ans = 0;
    cin >> n >> a >> b;
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s >> s;
        if (s == "/oh") ans += a;
        else if (s == "/hsh") ans += b;
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：伟大的王夫子 (赞：2)

根据题意模拟即可。

由题，先读入 $n, a, b$。然后我们读入 $2n$ 个字符串，统计其中有多少个消息是表情  $\text{oh}$ 或 $\text{hsh}$ 即可。即判断字符串是否等于 $\text{/oh}$ 或者 $\text{/hsh}$。可以用 string 读入并进行统计。

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, A, B;
int main() {
    cin >> n >> A >> B;
    int ans(0);
    for (int i = 1; i <= 2 * n; ++i) {
        string s;
        cin >> s;
        if (s == "/oh") ans += A;
        if (s == "/hsh") ans += B;
    }
    cout << ans;
}
```

---

## 作者：skyskyCCC (赞：1)

**前言。**

题意：[题意传送门](https://www.luogu.com.cn/problem/P8410)。

做法：字符串。

**分析。**

注：本题将提供 $2$ 种解题思路。

- 做法一：比较麻烦，建议使用第二种方法。

思路：

既然是字符串裸题，那么就用**字符**来做！

详细思路见代码。

代码如下，仅供参考：
```
#include<iostream>
#include<cstring>
using namespace std;
int n,a,b,ans;
char str[20005];//定义
int main(){
    cin>>n>>a>>b;
    for (int i=1;i<=n*2;i++){
        cin>>str;//输入字符
        int len=strlen(str);//找str的长度，strlen()函数在#include<cstring>里
        if(str[len]!=':'&&str[0]=='/'){//如果最后一个字符不是：且第一个是/时，是一个表情符号
            for (int j=0;j<len;j++){
                if(str[j]=='/'&&str[j+1]=='o'&&str[j+2]=='h'){//找到/oh
                    if(j+3==len||str[j+3]=='/') ans+=a;
                }//上边的代码表示如果找到的字符串是最后的字符或者下一个不是多余字符，说明是/oh的表情信息，防止如/ohh的非魔怔表情符号
                if(str[j]=='/'&&str[j+1]=='h'&&str[j+2]=='s'&&str[j+3]=='h'){//找到/hsh
                    if(j+4==len||str[j+4]=='/') ans+=b;
                }//上边的代码表示如果找到的字符串是最后的字符或者下一个不是多余字符，说明是/hsh的表情信息，防止如/hshh的非魔怔表情符号
            }
        }
    }
    cout<<ans<<"\n";//输出
    return 0;
}
```
后记：

注意只有 ```/oh``` 和 ```/hsh``` 才是魔怔表情符号，其余的都不是，比如 ```/ohh``` 之类的。

其次，字符串第一个字符的下标为 $0$ 这点一定要注意！

- 方法二：推荐方法。

思路：

输入字符串，然后判断符合的字符串，输出答案。

没有什么思维难度，模拟即可。

代码如下，仅供参考：
```
#include<iostream>
#include<cstring>
using namespace std;
int n,a,b,ans;
int main(){
    cin>>n>>a>>b;
    for (int i=1;i<=n;i++) {
        string s;
        cin>>s;//输入用户名，只是占个位置，并没有什么用
        cin>>s;//输入信息
        if (s=="/oh"){
            ans+=a;//是'/oh'，魔怔值+a
        }
        if (s=="/hsh"){
            ans+=b;//是'/hsh'，魔怔值+b
        }
    }
    cout<<ans<<"\n";
    return 0;
}
```
后记：

思路二代码实现难度较小，也比较好理解吧。

**后记。**

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：xhabc66 (赞：1)

# 思路
直接处理字符串即可。

一条消息为两行：发送人和消息。

发送人不用管，对于消息内容，判断是否为 $\tt /oh$ 或 $\tt /hsh$ 即可。
# AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,a,b,ans=0;
	cin>>n>>a>>b;
	
	while(n--)//省略写法，等价于for(int i=0;i<n;i++)
	{
		string s;
		cin>>s;//“无用”的发送人
		cin>>s;
		if(s[0]!='/')continue;
		if(s=="/oh")ans+=a;
		else if(s=="/hsh")ans+=b;
	}
	cout<<ans;
	return 0;
 } 
```


---

## 作者：ztrztr (赞：1)

## 前言
这道题是一道很简单的字符串处理，但题目稍稍有一点水，我建议以后可以把难度往上提一点，希望以后的月赛越做越好！加油！
## 思路
废话不多说，这道题的知识点在前言说过了，是字符串处理。这道题有几个重点：
1. 判断是不是表情。我们在读入这个字符串后，可以判断第一个字符是不是 ```'/'``` 来解决这个问题。
2. 判断是不是规定表情。我们直接看字符串是不是符合要求就行了。

## 实现
理论知识讲完了，我们来实现一下吧。

实现分为几个步骤：
### 输入
第一步，先输入 $n,a,b$，定义见题目。
```cpp
int n, a, b;
cin >> n >> a >> b;
for (int i = 1; i <= n * 2; i++) {//注意是n * 2
}
```
### 字符串处理
这里还可以再分两步去算：
#### 输入加判断是否是表情
如何判断前面说过了，直接上代码。
```cpp
cin >> s;
if (s[0] != '/') continue;
```
#### 判断是否合法
判断方法前面也说过了，还是上代码。
```cpp
if (s == "/oh") sum += a;
else if (s == "/hsh") sum += b;
```
## 整体代码
讲了那么多，现在我把整体代码放上来，大家千万不要抄袭呀！
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	ios::sync_with_stdio(false);
	int n, a, b, sum = 0;
	string s;
	cin >> n >> a >> b;
	for (int i = 1; i <= n * 2; i++) {
		cin >> s;
		if (s[0] != '/') continue;
		if (s == "/oh") sum += a;
		else if (s == "/hsh") sum += b;
	}
	cout << sum;
	return 0;
}
```

---

## 作者：accomplishment (赞：1)

[传送门](https://www.luogu.com.cn/problem/P8410)

~~一道大水题。~~

发的所有信息形式一定是（注意是遍历 $2 \times n$ 次）：

> $\texttt{<}\textit{str}\texttt{>:}$
> 
> $\texttt{/<}\textit{str}\texttt{>}$ 或 $\texttt{<}\textit{str}\texttt{>}$
> 
> $\texttt{<}\textit{str}\texttt{>:}$
> 
> $\texttt{/<}\textit{str}\texttt{>}$ 或 $\texttt{<}\textit{str}\texttt{>}$
> 
> $\texttt{<}\textit{str}\texttt{>:}$
> 
> $\texttt{/<}\textit{str}\texttt{>}$ 或 $\texttt{<}\textit{str}\texttt{>}$
> 
> $\dots$

所以我们只要**忽略索引为奇数**的字符串（即用户名字）即可。

```cpp
if (i & 1) {
	continue;
}
```

注：```if (i & 1)``` 与 ```if (i % 2 == 1)``` 等价。

即只**读取并判断索引为偶数**的字符串（即文字信息或表情信息）是否为 ```/oh``` 或 ```/hsh```，如果字符串为 ```/oh```，魔怔值 $+ a$；如果字符串为 ```/hsh```，魔怔值 $+ b$（注：这里我用 ```res``` 表示魔怔值）。

```cpp
if (s == "/oh") {
	res += a;
}
		
else if (s == "/hsh") {
	res += b;
}
```

完整 $Code$：

```cpp
// Problem: T237777 Don't Mozheng. /oh
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T237777?contestId=50000
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

/*
 * Author: guzheran @YYXX
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef vector<int> vi;
typedef pair<int, int> pii;

#define fi first
#define se second
#define register rg
#define mp make_pair
#define pb push_back
#define pf push_front

#define rep(i, s, t) for (int i = s; i <= t; i++)
#define per(i, s, t) for (int i = t; i >= s; i--)

namespace IO {
	
	template <typename type>
	inline void Read (type &theNum) {
	
		char theChar = 0;
		int negative = 0; 
		
		theNum = 0;
		theChar = getchar();
		negative = 1;
		
		while (theChar < '0' || theChar > '9') {
			if (theChar == '-') {
				negative = -1;
			}
			
			theChar = getchar();
		}
		
		theNum = theChar ^ 48;
		
		while ((theChar = getchar()) > '0' - 1 && theChar < '9' + 1) {
			theNum = (theNum << 3) + (theNum << 1) + (theChar ^ 48);
		}
		
		theNum *= negative;
		
	}
	
	template <typename type>
	inline void RecursionWrite (type theNum) {
		
		if (theNum) {
			RecursionWrite(theNum / 10);
			putchar(theNum % 10 + 48);
		}
		
	}
	
	template <typename type1, typename type2>
	inline void Write (type1 theNum, type2 endChar) {
		
		if (!theNum) {
			putchar('0');
		}
		
		if (theNum < 0) {
			putchar('-');
			theNum *= -1;
		}
		
		if (theNum) {
			RecursionWrite(theNum / 10);
			putchar(theNum % 10 + 48);
		}
		
		putchar(endChar);
		
	}
	
}

using namespace IO;

/* template ends here */

int main () {
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	int n, a, b, res = 0;
	string s;
   
	cin >> n >> a >> b;
   
	rep (i, 1, 2 * n) {
		cin >> s;
		
		if (i & 1) {
			continue;
		}
		
		if (s == "/oh") {
			res += a;
		}
		
		else if (s == "/hsh") {
			res += b;
		}
	}
	
	cout << res << '\n';
	
	return 0;
	
}
```

---

## 作者：XKqwq (赞：1)

### 思路：

1. 输入 $n$ , $a$ , $b$ 。

2.  $n$ 次循环，每次 输入两个字符串：用户名和消息，如果消息是表情 $\texttt{/hsh}$ 或 $\texttt{/oh}$ ，魔怔值加 $a$ 或 $b$ 。

3. 输出魔怔值。

梳理过程后，我们发现用户名并没有用，所以我们可以输入两次消息，判断后面的就行，这样就可以不定义一个单独的字符串来输入了。

### 代码：

```cpp
#include <bits/stdc++.h>
#define ri register int
#define ll long long
using namespace std;

int n,a,b;
string s;
ll ans=0;

int main(){
	scanf("%d%d%d",&n,&a,&b);
	for(ri i=0;i<n;i++){
		cin>>s>>s;
		if(s=="/oh") ans+=a;
		if(s=="/hsh") ans+=b;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：_JF_ (赞：1)

## 「SvR-1」Don't Mozheng. /oh

**模拟字符串练手题**

思路：如果要满足 `/oh` 或者 `/hsh`,必须要字符的长度是等于 $3$ 或者等于 $4$ 才可以。先用两个字符串把 `/oh` 和 `/hsh` 加入进去，然后边输入边进行匹配，可以使用计数器统计吻合个数，如果完全重合，就加上相应的 $a$ 或者 $b$ 即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline long long read()
{
    register long long x=0,f=0;
    register char t=getchar();
    while(t<'0'||t>'9')f^=(t=='-'),t=getchar();
    while(t>='0'&&t<='9')x=(x<<3)+(x<<1)+(t^48),t=getchar();
    return f?-x:x;
}
signed main()
{
	string oh,hsh;
	oh[0]='/',oh[1]='o',oh[2]='h';
	hsh[0]='/',hsh[1]='h',hsh[2]='s',hsh[3]='h'; 
	int n,a,b;
	n=read(),a=read(),b=read();
	int ans1=0;
	for(int i=1;i<=2*n;i++)
	{
		int sum=0,ans=0;
		string k;
		cin>>k;
		if(k.length()==3)
		{
			for(int j=0;j<=k.length()-1;j++)
				if(k[j]==oh[j])
					sum++;
			if(sum==3)
				ans1+=a;
		}
		else if(k.length()==4)
		{
			for(int j=0;j<=k.length()-1;j++)
				if(k[j]==hsh[j])
					ans++;
			if(ans==4)
				ans1+=b;
		}
	}
	cout<<ans1<<endl;
 } 
```


---

## 作者：_acat_ (赞：1)

~~You can mozheng！~~![](https://xn--9zr.tk/oh)![](https://xn--9zr.tk/hsh)
### 前言

赞美良心出题人！!1

### 思路

本题是个模拟题。

当输入的信息是 $\tt/oh$ 时，$ans$ 加上 $a$ 的魔怔值，如果输入的信息是 $\tt /hsh$ 时，$ans$ 加上 $b$ 的魔怔值即可。

### AC code

```cpp
#include<iostream>
using namespace std;
int n,x,y;
int ans=0;
string s;
int main()
{
	cin>>n>>x>>y;
	for(int i=1;i<=2*n;++i)
	{
	    cin>>s;
	    if(s=="/oh")
            ans+=x;
	    if(s=="/hsh")
            ans+=y;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Awhale_tauntingcat (赞：0)

#### 题意分析

本题是一道模拟题，在题目给出的 $n$ 条信息中，如果有 `\oh` 字样，魔怔值 $ans$ 增加 $a$ ，如果有 `\hsh` 字样，魔怔值增加 $b$ 。
最后输出 $ans$ 即可。

#### 代码

```cpp
#include<iostream>
#define mian main
using namespace std;
int n,a,b,ans;
string s;
int mian(){
	cin>>n>>a>>b;
	for(int i=1;i<=2*n;i++){
		cin>>s;
		if(s=="/oh"){
		ans+=a;
		 }		
		if(s=="/hsh"){
		ans+=b;
		 }
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Nygglatho (赞：0)

首先，类似于 $\texttt{/<oh>/<oh>}$ 或是 $\texttt <str\texttt>\texttt{/<hsh>}$ 这种肯定不合法，因为没有出现在题面的三种情况（即 $\texttt <str\texttt >\tt:$ 、$\texttt <str\texttt >$ 、$\tt/\texttt <\mathit{str}\texttt >$ 之内）

而类似于 $\texttt{/<oh/oh>}$ 也不合法，因为题面给出条件：$str$ 不含空格，`:`，`/`，所以我们只需判断是否为 $\tt /oh$ 或是 $\tt /hsh$ 即可，此外，由于没有空格，所以使用 `cin` 即可。
  
Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int s;
string str;
int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, a, b;
    cin >> n >> a >> b;
    for (int i = 1; i <= 2 * n; ++i) {
        cin >> str;
        if (str == "/oh") s += a;
        if (str == "/hsh") s += b;
    }
    cout << s;
}
```

---

## 作者：jimmyfj (赞：0)

思路 : 首先找到 $\texttt{/oh}$ 和 $\texttt{/hsh}$ 这两个子串的随便其中一个 , 并加上相对应的魔怔值 , 要注意 , $\texttt{/oh}$ 或 $\texttt{/hsh}$  必须是完整的, 如果只是 $\texttt{/oh}$ 和 $\texttt{/hsh}$ 这样的话 , 会有部分点过不了 , 最后输出总魔怔值就完事啦

代码参考 : 

```cpp
#include <bits/stdc++.h>
#include <cstring>
using namespace std;

string str;

int x, y, n;
int sum = 0;//初始魔怔值

int main()
{
    cin >> n >> x >> y;
    
    for(int i = 1; i <= 2 * n; i ++)
    {
        cin >> str;
        
        if(str == "/oh") sum += x;
        if(str == "/hsh") sum += y;
    }
    
    cout << sum;
    
    return 0;
}
```


---

## 作者：Jorisy (赞：0)

/oh /hsh

---

简单模拟题。

可以看出，每一次输入的第一行无用，可以忽略。

然后我们只要判断第二行文本，为 `/oh` 则加 $a$，`/hsh` 则加 $b$。

AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int n,a,b,ans=0;
	string x,y;
	cin>>n>>a>>b;
	while(n--)
	{
		cin>>x>>y;
		if(y=="/oh") ans+=a;//判断为 /oh
		if(y=="/hsh") ans+=b;//判断为 /hsh
	}
	cout<<ans;
 	return 0;
}
```

---

## 作者：Cure_Wing (赞：0)

### Solution
统计字符串为 $\texttt{/oh}$ 和 $\texttt{/hsh}$ 的数量，并乘以相应的魔怔值即可。  
其他的数据直接略过不理。  
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,sr;
string s;
int main(){
	scanf("%d%d%d",&n,&a,&b);
	for(int i=1;i<=n;++i){
		cin>>s;
		cin>>s;
		if(s=="/oh") sr+=a;
		else if(s=="/hsh") sr+=b;
	}
	printf("%d\n",sr);
	return 0;
} 
```

---

## 作者：KAqwq (赞：0)

# P8410	
这是一道水题。
# 思路
题目中乱七八糟的东西我们都不要管，简化题意后就是说当这个字符串为`/oh`时，让一个变量加上 $a$，而当这个字符串为`/hsh`时，我们将这个变量加上 $b$，清楚思路后，实现代码就成了一件简单的事。
# AC code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,cnt,sum;
string s,q;
signed main(){
    scanf("%lld %lld %lld",&T,&n,&cnt);
    while(T--){
        cin>>s>>q;//由于getline会被卡，scanf无法读入，故使用cin
        if(q=="/oh") sum+=n;
        if(q=="/hsh") sum+=cnt;
    }   
    printf("%lld",sum);
    return 0;
}
```
### ——The End

---

## 作者：Asimplename (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P8410)

## 思路

我们可以循环 $2n$ 次（因为每条消息包含一个人名和一条信息），每次读入一个字符串，然后判断这个字符串是不是 ``/oh`` 或 ``/hsh``，如果是，加上 $a$ 或 $b$ 即可。

## 代码

```cpp
#include<iostream>
using namespace std; 
int n = 0;
int a = 0;
int b = 0; 
int ans = 0;
string str;
int main () {
	cin >> n >> a >> b;
	for(int i = 1; i <= n * 2; i ++){
		cin >> str;
		if(str == "/oh"){
			ans += a;
		}
		else if(str == "/hsh"){
			ans += b;
		}
	}
	cout << ans;
	return 0;
}

---

## 作者：lyhqwq (赞：0)

### 前言

太良心了！！！赞美良心出题人！！！

### 思路

一道模拟题

每次读入一条信息，判断是信息是否为 $\texttt{/oh}$ 或 $\texttt{/hsh}$ 即可。

注意信息的形式有可能为 $\texttt{/ohh}$ 。

所以我们需要判断信息的长度和内容

### ACcode

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
#define il inline
using namespace std;
int n,a,b; 
ll sum;
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d%d%d ",&n,&a,&b);
	for(int i=1;i<=n;i++){
		string name,mess;
		cin>>name>>mess;
		if(mess[0]=='/'){
			if(mess[1]=='o'&&mess[2]=='h'&&mess.size()==3) sum+=a;
			else if(mess[1]=='h'&&mess[2]=='s'&&mess[3]=='h'&&mess.size()==4) sum+=b;
		}
	}
	printf("%lld\n",sum);
	return 0;
}

```


---

## 作者：Joker_1212 (赞：0)

# P8410「SvR-1」Don't Mozheng. /oh 题解

[原题传送门](https://www.luogu.com.cn/problem/P8410)

## 题意理解

每个人会发一句话或一个表情，其中表情以 `/` 开头。每个`/oh` 会贡献 $a$ 个魔怔值，每个 `/hsh` 会贡献 $b$ 个魔怔值。计算魔怔值总数。（只有严格等于 `/oh` 和 `/hsh` 的表情才计算魔怔值）。

## 题目分析

由于每个人的留言都是以用户名作为第一行，因此可以直接一次读两行，只判断第二行即可。

第二行如果不以 `/` 开头或者总长度大于 $4$，直接 `continue` 即可。

接下来判断表情是否符合。只要满足 `"/oh\0"` 或 `"/hsh\0"` 即可（因为 `scanf` 读取一行会在最后留一个 `\0`，不用刻意清空字符串）。

## 编程实现

```cpp
#include <bits/stdc++.h>
using namespace std;

char l[60];

int main()
{
    int n, a, b, ans = 0;
    scanf("%d%d%d", &n, &a, &b);
    while (n--)
    {
        // 一次读两行
        scanf("%s", l);
        scanf("%s", l);
        if (l[0] == '/')
        {
            if (strlen(l) > 4)
                continue;
            if (l[1] == 'o' && l[2] == 'h' && l[3] == 0) // /oh
                ans += a;
            if (l[1] == 'h' && l[2] == 's' && l[3] =='h' && l[4] == 0) // /hsh
                ans += b;
        }
    }
    printf("%d\n", ans);
    return 0;
}
```

---

