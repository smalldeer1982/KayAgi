# 题目信息

# E-mail Addresses

## 题目描述

One of the most important products of the R1 company is a popular @r1.com mail service. The R1 mailboxes receive and send millions of emails every day.

Today, the online news thundered with terrible information. The R1 database crashed and almost no data could be saved except for one big string. The developers assume that the string contains the letters of some users of the R1 mail. Recovering letters is a tedious mostly manual work. So before you start this process, it was decided to estimate the difficulty of recovering. Namely, we need to calculate the number of different substrings of the saved string that form correct e-mail addresses.

We assume that valid addresses are only the e-mail addresses which meet the following criteria:

- the address should begin with a non-empty sequence of letters, numbers, characters '\_', starting with a letter;
- then must go character '@';
- then must go a non-empty sequence of letters or numbers;
- then must go character '.';
- the address must end with a non-empty sequence of letters.

You got lucky again and the job was entrusted to you! Please note that the substring is several consecutive characters in a string. Two substrings, one consisting of the characters of the string with numbers $ l_{1},l_{1}+1,l_{1}+2,...,r_{1} $ and the other one consisting of the characters of the string with numbers $ l_{2},l_{2}+1,l_{2}+2,...,r_{2} $ , are considered distinct if $ l_{1}≠l_{2} $ or $ r_{1}≠r_{2} $ .

## 说明/提示

In the first test case all the substrings that are correct e-mail addresses begin from one of the letters of the word agapov and end in one of the letters of the word com.

In the second test case note that the e-mail x@x.x is considered twice in the answer. Note that in this example the e-mail entries overlap inside the string.

## 样例 #1

### 输入

```
gerald.agapov1991@gmail.com
```

### 输出

```
18
```

## 样例 #2

### 输入

```
x@x.x@x.x_e_@r1.com
```

### 输出

```
8
```

## 样例 #3

### 输入

```
a___@1.r
```

### 输出

```
1
```

## 样例 #4

### 输入

```
.asd123__..@
```

### 输出

```
0
```

# AI分析结果

### 题目内容
#### E-mail地址

#### 题目描述
R1公司最重要的产品之一是广受欢迎的@r1.com邮件服务。R1邮箱每天接收和发送数百万封电子邮件。

今天，网络新闻爆出了可怕的消息。R1数据库崩溃了，除了一个长字符串外，几乎没有数据被保存下来。开发人员认为这个字符串包含了一些R1邮件用户的信息。恢复数据是一项繁琐且主要靠人工的工作。所以在开始这个过程之前，决定先评估恢复的难度。具体来说，我们需要计算保存的字符串中能构成正确电子邮件地址的不同子串的数量。

我们认为有效的地址仅指满足以下标准的电子邮件地址：
- 地址应以非空的字母、数字、字符'\_'序列开头，且以字母开头；
- 接着必须是字符'@'；
- 然后必须是一个非空的字母或数字序列；
- 接着必须是字符'.'；
- 地址必须以一个非空的字母序列结尾。

你又很幸运，这项工作委托给了你！请注意，子串是字符串中几个连续的字符。两个子串，一个由字符串中编号为$ l_{1},l_{1}+1,l_{1}+2,\cdots,r_{1} $的字符组成，另一个由字符串中编号为$ l_{2},l_{2}+1,l_{2}+2,\cdots,r_{2} $的字符组成，如果$ l_{1}≠l_{2} $或$ r_{1}≠r_{2} $，则认为它们是不同的。

#### 说明/提示
在第一个测试用例中，所有正确的电子邮件地址子串都以agapov这个词的某个字母开头，并以com这个词的某个字母结尾。

在第二个测试用例中，请注意电子邮件x@x.x在答案中被计算了两次。注意，在这个例子中，电子邮件条目在字符串内部有重叠。

#### 样例 #1
**输入**
```
gerald.agapov1991@gmail.com
```
**输出**
```
18
```

#### 样例 #2
**输入**
```
x@x.x@x.x_e_@r1.com
```
**输出**
```
8
```

#### 样例 #3
**输入**
```
a___@1.r
```
**输出**
```
1
```

#### 样例 #4
**输入**
```
.asd123__..@
```
**输出**
```
0
```

### 算法分类
字符串

### 题解综合分析与结论
所有题解都围绕在给定字符串中寻找符合特定格式的邮箱地址子串数量这一核心任务。思路上，均利用邮箱地址包含“@”和“.”这一特点，通过定位这些特殊字符，再分别检查其前后子串是否符合规则来计数。主要难点在于准确判断各部分子串的合法性，包括开头字符要求、中间字符集限制等。不同题解在具体实现细节和代码风格上有所差异，比如有的直接暴力扩展前后缀，有的先预处理再判断相邻三段。

### 所选的题解
#### wxzzzz（5星）
- **关键亮点**：思路清晰简洁，直接遍历字符串，遇到“@”时，分别向前后扩展判断合法性，通过巧妙设置计数器和边界条件判断，代码实现高效且可读性强。
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, ans, now, cntl, cntr;
char s[1000005];
int main() {
    scanf("%s", s + 1), n = strlen(s + 1);

    for (long long i = 1; i <= n; i++) {
        if (s[i]!= '@')
            continue;

        now = i, cntl = cntr = 0;

        while (s[now - 1]!= '.' && s[now - 1]!= '@' && now > 1)
            now--, cntl++;

        for (long long j = now; j < i; j++)
            if (s[j] < 'a' || s[j] > 'z')
                cntl--;

        now = i;

        if (s[now + 1] == '.')
            continue;

        while (s[now]!= '.' && s[now + 1]!= '@' && s[now + 1]!= '_' && now < n)
            now++;

        if (s[now + 1] == '@' || s[now + 1] == '_')
            continue;

        while ((s[now + 1] >= 'a' && s[now + 1] <= 'z') && now < n)
            now++, cntr++;

        ans += cntl * cntr;
    }

    cout << ans;
    return 0;
}
```
核心实现思想：遍历字符串，遇到“@”时，先向左扩展前缀，统计合法前缀长度`cntl`，再向右找到“.”并扩展后缀，统计合法后缀长度`cntr`，最后将两者乘积累加到答案`ans`。

#### AKPC（4星）
- **关键亮点**：同样采用暴力模拟思路，逻辑直接易懂，对前缀、后缀扩展过程描述清晰，代码简洁明了。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,ans;
string a;
signed main(){
	cin>>a,n=a.length();
	for (int i=0;i<n;i++)
		if (a[i]=='@'){
			int x=0,y=0;
			for (int j=i-1;j>=0&&a[j]!='.'&&a[j]!='@';j--) if (a[j]<='z'&&a[j]>='a') x++;
			for (int j=i+1;j<n&&a[j]!='.'&&a[j]!='@'&&a[j]!='_';j++) y++;
			if (y==0) continue;
			if (a[i+y+1]!='.') continue;
			int z=0;
			for (int j=i+y+2;j<n&&a[j]<='z'&&a[j]>='a';j++) z++;
			ans+=x*z;
		}
	cout<<ans;
	return 0;
}
```
核心实现思想：遍历字符串，找到“@”后，向左统计以字母开头的前缀长度`x`，向右统计到“.”之前的长度`y`，若“.”存在且位置合法，再统计“.”后合法后缀长度`z`，将`x`与`z`乘积累加到答案`ans`。

#### AutumnQ（4星）
- **关键亮点**：代码注释详细，对每一步操作解释清晰，先定位“@”，然后分别向左右扩展子串，按规则判断合法性，便于理解。
```cpp
#include<bits/stdc++.h>
using namespace std;
 
string s;
int SIZE;
int ans;

signed main(){
	getline(cin,s);
	SIZE=s.size();
	s=" "+s;
	for(int i=1;i<=SIZE;i++){
		if(s[i]!='@')continue;
		int l=i-1,r=i+1;
		int times1=0,times2=0;
		while((isalpha(s[l]) || isdigit(s[l]) || s[l]=='_') && l>=0){
			if(isalpha(s[l]))times1++;
			l--;
		}
		bool flg=false;
		if(s[r]=='.')continue;
		while((isalpha(s[r]) || isdigit(s[r]) || s[r]=='.') && r<=SIZE){
			if(s[r]=='.'){
				flg=true;
				r++;
				break;
			}
			r++;
		}
		if(!flg)continue;
		while(isalpha(s[r]) && r<=SIZE+1){
			r++;
			times2++;
		}
		ans+=times1*times2;
	}
	cout<<ans;
	return 0;
}
```
核心实现思想：遍历字符串找“@”，向左扩展前缀统计字母个数`times1`，向右找“.”并判断中间子串合法性，若找到“.”则继续统计“.”后合法后缀字母个数`times2`，将两者乘积累加到答案`ans`。

### 最优关键思路或技巧
利用邮箱地址固定格式，以“@”和“.”为关键分隔点，通过线性遍历字符串，分别向前后扩展子串并依据规则判断合法性，利用乘法原理统计符合要求的子串数量。这种方法避免了复杂的数据结构和算法，直接针对题目特点进行高效求解。

### 可拓展思路
此类题目属于字符串匹配与计数问题，类似套路是先确定关键分隔字符，再根据规则对各部分子串进行合法性判断。同类型题可涉及不同格式的字符串匹配，如IP地址匹配、特定格式的电话号码匹配等，解题思路类似，需根据具体规则调整判断条件。

### 洛谷推荐题目
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：统计给定单词在字符串中出现的次数，涉及字符串查找与匹配。
- [P2010 回文日期](https://www.luogu.com.cn/problem/P2010)：判断日期是否为回文，对日期字符串按特定格式进行处理和判断。
- [P1593 因子和阶乘](https://www.luogu.com.cn/problem/P1593)：涉及对数字的字符串形式进行处理，计算因子相关问题，与本题处理字符串特定部分信息类似。 

---
处理用时：96.42秒