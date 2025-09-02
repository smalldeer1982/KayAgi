# 「QFOI R1」贴贴

## 题目描述

小 R 是一个可爱的女孩子，她希望通过给洛谷题目写题解的方式跟出题人贴贴。

她发现，如果从题解界面点击“提交题解”按钮，博客中会自动生成 URL 标识符，也就是文章的链接。

其中，标识符的生成规则如下：

- 将题号的所有大写字母转为小写。
- 将上一步结果的所有下划线转为减号。
- 在上一步结果前面加上 `solution-`。

她准备给一道题目写题解，已知这道题的题号，你能求出 URL 标识符吗？

## 说明/提示

**样例 $3$ 解释**

根据生成规则：

- 将题号的所有大写字母转为小写：`at_abc312_h`。
- 将上一步结果的所有下划线转为减号：`at-abc312-h`。
- 在上一步结果前面加上 `solution-`：`solution-at-abc312-h`。

---

**数据范围**

本题共 $10$ 个测试点，每个测试点 $10$ 分。

对于全部数据，保证题号仅包含大写字母（ASCII $65\sim 90$）、小写字母（ASCII $97\sim 122$）、数字（ASCII $48\sim 57$）、下划线（ASCII $95$），且长度不超过 $20$。

对于全部数据，答案中应当仅包含小写字母（ASCII $97\sim 122$）、数字（ASCII $48\sim 57$）、减号（ASCII $45$）。

- 对于测试点 $1$：保证为主题库题目。
- 对于测试点 $2$：保证为入门与面试题目。
- 对于测试点 $3\sim 4$：保证为 CodeForces 题目。
- 对于测试点 $5\sim 6$：保证为 SPOJ 题目。
- 对于测试点 $7\sim 8$：保证为 AtCoder 题目。
- 对于测试点 $9\sim 10$：保证为 UVA 题目。

## 样例 #1

### 输入

```
P9202```

### 输出

```
solution-p9202```

## 样例 #2

### 输入

```
CF1797F```

### 输出

```
solution-cf1797f```

## 样例 #3

### 输入

```
AT_abc312_h```

### 输出

```
solution-at-abc312-h```

# 题解

## 作者：LegendaryGrandmaster (赞：11)

1. 输出  `solution-`。

2. 将字符串扫一遍，当为下划线时转化为减号。

3. `tolower` 可把所有字母转小写。 

最终输出字符串即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

signed main()
{
    string st;
    cin>>st;
    cout<<"solution-";
    for(int i=0;i<st.size();i++){
    	if(st[i]=='_')st[i]='-';
    	st[i]=tolower(st[i]);
    }
    cout<<st;
}
```

---

## 作者：rui_er (赞：8)

这里是官方题解。

简单模拟题。

首先输出无论如何都要输出的 `solution-`，然后枚举题号的每个字符 $c$：如果 $c$ 是大写字母，就转为小写字母输出；如果 $c$ 是下划线，就输出减号；否则，原样输出即可。

时间复杂度 $O(|s|)$。

```cpp
// Problem: T361845 贴贴
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T361845
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

int main() {
    string s;
    cin >> s;
    printf("solution-");
    for(char c : s) {
        if(isupper(c)) putchar(tolower(c));
        else if(c == '_') putchar('-');
        else putchar(c);
    }
    return 0;
}
```

---

## 作者：nightwatch.ryan (赞：3)

## 思路
首先读入题目编号，先输出 `solution-`。接下来枚举字符串，如果枚举到的字符是大写字母，就转成小写字母，如果枚举到的字符是下划线，就把这个字符改成减号。最后输出更改好的字符串。
## 代码
```cpp
#include<iostream>
int main(){
	std::string str;
	std::cin>>str;
	std::cout<<"solution-";
	for(int i=0;i<str.size();i++){
		if(str[i]>='A' and str[i]<='Z'){//判断是否是大写字母
			str[i]+=32;//大写字母的ascii码+32就是小写字母
		}
		if(str[i]=='_'){//判断是否是下划线
			str[i]='-';//更改成减号
		}
	} 
	for(int i=0;i<str.size();i++){
		std::cout<<str[i];
	}
}
```

---

## 作者：Hulless_barley (赞：2)

## 题目大意：
输入一个字符串，把所有的大写字母改成小写字母，把所有的`_`改成`-`，并且在前面加上`solution-`
## 解法分析
1. 处理大写字母
```cpp
if(str[top]>='A'&&str[top]<='Z')//判断是否是大写字母
	str[top]=str[top]-'A'+'a';//改成小写字母
```
2. 处理下划线
```cpp
if(str[top]=='_')//判断是否是下划线
	str[top]='-';//改为减号
```
3. 加上`solution-`
直接`"solution-"+str`就行了
## 完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
string s;
inline string read(){
    string str;
    cin>>str;//读入字符串
    int top=0;
    while(top<str.size()){
        if(str[top]>='A'&&str[top]<='Z')//判断是否是大写字母
            str[top]=str[top]-'A'+'a';//改成小写字母
        if(str[top]=='_')//判断是否是下划线
            str[top]='-';//改为减号
        top++;
    }
    return "solution-"+str;
}
signed main(){
    s=read();
    cout<<s;
    return 0;//养成好习惯
}
```

---

## 作者：Lemon_zqp (赞：2)

### 思路
这题就把字符串里的大写全部转成小写，然后就喜提八十分的好成绩，仔细一看会发现，字符串里的下划线要改成一条横杠，直接一位一位判断即可。
### 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
	string s;
	cin >> s;
	for(int i = 0; i < s.size(); i++){
		if(s[i] >= 'A' && s[i] <= 'Z'){
			s[i] += 32;
		}
		else if(s[i] == '_'){
			s[i] = '-';
		}
	}
	cout << "solution-" << s;
	return 0;
}
```


---

## 作者：FurippuWRY (赞：1)

一共就三点要求：
- 将题号的所有大写字母转为小写（可以使用 `tolower()` 函数）。
- 将上一步结果的所有下划线转为减号。
- 在上一步结果前面加上 `solution-`。

完成这三点就可以了。

```cpp
#include <bits/stdc++.h>

using namespace std;

string a;

int main() {
	
	cin >> a;
	for (int i = 0; i < a.size(); ++i) {
		a[i] = tolower (a[i]);
		if(a[i] == '_') a[i] = '-';
	}
	cout << "solution-" << a;
    return 0;
}
```

---

## 作者：zbzbzzb (赞：1)

这题非常简单，就是把字符串枚举一遍，碰到大写字母就把他转为小写字母，或者遇到下划线就改成减号，最后输出时前面加上 `solution-` 就行了。

AC CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main(){
	cin>>s;
	int len=s.size();
	for(int i=0;i<len;i++){
		if(s[i]>='A'&&s[i]<='Z'){
			s[i]+=32;
		}else if(s[i]=='_'){
			s[i]='-';
		}
	}printf("solution-");
	cout<<s;
	return 0;
}
```

---

## 作者：suyi1111 (赞：1)

模拟题，先输出```solution-```

接下来判断如果是大写字母，输出对应的小写

如果是下划线，输出```-```

否则原样输出

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
string k; 
signed main()
{
	cin>>k;
	cout<<"solution-";
	for(int i=0;i<k.size();i++){
		if(k[i]>='A'&&k[i]<='Z')cout<<(char)(k[i]+('z'-'Z'));
		else if(k[i]=='_')cout<<"-";
		else cout<<k[i]; 
	}
    return 0;
}
```

---

## 作者：ICU152_lowa_IS8 (赞：1)

本题是一道基础的字符串题。

遍历一遍，将大写全部转换成小写，下划线全部转换成减号，输出前缀加上即可。

代码：

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	string s;
	cin>>s;
	int len=s.length();
	for(int i=0;i<len;i++){
		if(s[i]=='_'){
			s[i]='-';
		}
		if(s[i]>='A'&&s[i]<='Z'){
			s[i]+=32;
		}
	}
	cout<<"solution-"<<s;
	return 0;
}
```


---

## 作者：Miyamizu_Mitsuha (赞：1)

按照题意模拟即可。一个小技巧就是判断大写以及转化可以用 `isupper` 以及 `tolower`。

```
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;
    for (int i = 0; i < s.length(); i++) {
        if (isupper(s[i])) {
            s[i] = tolower(s[i]);
        }
    }

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '_') {
            s[i] = '-';
        }
    }

    s = "solution-" + s;

    cout << s << endl;

    return 0;
}
```


---

## 作者：York佑佑 (赞：1)

## 题意
输入一个字符串，将其进行以下操作：
- 将字符串的所有大写字母转为小写

- 将上一步结果的所有下划线转为减号

- 在上一步结果前面加上 `solution-`

## 分析
先输出 `solution-`，再读入字符串按照题意模拟即可。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	string str;
	cin >> str;
	cout << "solution-";//先输出solution-
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '_')//"_"转"-"
			cout << "-";
		else if (str[i] >= 'A' && str[i] <= 'Z')//大写转小写
			cout << char(str[i] + 32);
		else
			cout << str[i];
	}
	return 0;
}
```


---

## 作者：Soul_Seeker (赞：1)

# P9712 题解

[题目传送门](https://www.luogu.com.cn/problem/P9712)

考察点：简单字符串。

# 思路阐述

按照题意模拟即可。

# 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	string s;
	cin>>s;
	for(int i=0;i<s.size();i++){
		if(s[i]>='A'&&s[i]<='Z')s[i]+=32;//转换大小写
		if(s[i]=='_')s[i]='-';//转换下划线
	}
	cout<<"solution-"<<s;//输出前加 solution-
	return 0;
}
```

---

## 作者：Yzmddsw (赞：1)

# P9712

## 实现

读入字符串，三步处理。

首先循环判断字符是否为大写字母，是大写字母就转小写，实现方法很多，例如 `s[i]=s[i]+32;` 或 `s[i]=s[i]-'A'+'a';`。

然后判断字符是否为下划线，是下划线转减号。

最后输出时在前面加上 `solution-` 即可。

## 代码

```cpp
#include <iostream>
#include <string>
#define FOR(i, m, n) for (long long i = m; i <= n; i++)
#define ll long long
using namespace std;
int main(){
    string s;
    cin>>s;
    FOR(i,0,s.length()-1){
        if(s[i]>='A'&&s[i]<='Z')s[i]=s[i]-'A'+'a';//大小写转换，也可以用另一种
        else if(s[i]=='_')s[i]='-';//下换线变减号
    }
    cout<<"solution-"<<s;//输出前面加solution-
    return 0;
}
```



---

## 作者：littleqwq (赞：1)

# P9712 「QFOI R1」贴贴题解

### 题目意思：

大概就是给一个字符串把其中的下划线 ```_```，改成减号 ```-```，把大写字母全都改成小写字母，然后在最前面加上 ```solution-```。

### 大致思路：

输入一个字符串 $s$，数据类型最好用 ```string```，先输出 ```solution-```，然后一位一位去判断，如果是大写字母，那么就把它改成小写字母，如果是下划线 ```_```，那么就把它改成减号 ```-```，剩余的就直接输出。

### 代码实现：

```
#include<bits/stdc++.h>//可食用头文件
using namespace std;
string s;
int main()
{
	cin>>s;
	cout<<"solution-";//先输出哦
	for(int i=0;i<s.size();i++){//一定要从0开始，到长度减一结束
		if(s[i]>='A'&&s[i]<='Z'){//判断是否为大写字母
			s[i]=s[i]+32;//把它变成小写字母
			cout<<s[i];
		}else if(s[i]=='_'){//判断是否为下划线
			cout<<'-';//满足条件把他改成减号
		}else{
			cout<<s[i];//不满足任何条件，直接输出
		}
	}
	
	cout<<endl;//随意可加可不加，不影响结果
	return 0;//结束
}
```

这样，又完成一道题！

---

## 作者：zsh_haha (赞：1)

### 解题思路

我们可以现读入字符串，然后处理一个字符输出一个字符。

这里我们把每个字符分成三类：

- 大写字母：转成小写字母输出；
- 下划线（`_`）：输出减号（`-`）；
- 其他字符：直接输出。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[21];
int main(){
	cin>>a+1;//小技巧，这样字符串的下标就从 1 开始
	int n=strlen(a+1);
	cout<<"solution-";
	for(int i=1;i<=n;i++){
		if(a[i]>='A'&&a[i]<='Z'){//大写字母
			cout<<char(a[i]-'A'+'a');//转成小写字母输出
		}else if(a[i]=='_'){//下划线
			cout<<'-';//输出减号
		}else{//其他字符
			cout<<a[i];//直接输出
		}
	}
	return 0;
}
```

---

## 作者：zhang_Jimmy (赞：1)

# 思路：


我们可以先输出 `solution-`。


然后，对于每个字符，我们分几种情况讨论：

- 如果是大写字母，输出其对应的小写字母。

- 如果是 `_`，输出 `-`。

- 其他情况输出它原来的字符即可。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

string s;

int main(){
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	cin >> s;
	cout << "solution-";
	for(int i = 0; s[i]; i ++){
		if(s[i] >= 'A' && s[i] <= 'Z')
			cout << (char)(s[i] + 32);
		else if(s[i] == '_')
			cout << "-";
		else cout << s[i];
	}
	return 0;
}

```

---

## 作者：XRRRRcode (赞：1)

## 题解
没什么好说的，模拟题一道。我建议用 string 而不是字符数组，可以直接用加号增加字符。定义 $2$ 个 string 变量，一个是读入的字符串，另一个是输出的答案。读入字符串后把整个字符串遍历一遍，根据题目给出的规定增加到另一个字符串中，最后输出答案就好了。时间复杂度显而易见为 $O(k)$，其中 $k$ 表示读入字符串的长度。
## 代码
```cpp
#include<iostream>
#include<string>
using namespace std;
int main()
{
    string s1,s2="solution-";
    int i,k;
    cin>>s1;
    k=s1.size();
    for(i=0;i<k;i++)
    {
        if(s1[i]>='A'&&s1[i]<='Z')
            s2+=s1[i]-'A'+'a';
        else if(s1[i]=='_')
            s2+='-';
        else
            s2+=s1[i];
    }
    cout<<s2<<endl;
    return 0;
}
```


---

## 作者：Loser_Syx (赞：0)

暴力枚举 $s_i$ 的类别是什么进行对应更改即可。

```cpp
#include <iostream>
int main(){
	std::string s;
	std::cin >> s;
	std::cout << "solution-";
	for (auto&i:s) {
		if (i>='A'&&i<='Z')i+=32;
		if(i=='_')i='-';
		std::cout << i;
	}
}
```

---

## 作者：Crasole (赞：0)

## 思路

遍历输入的字符串,考虑如下三种情况，令 $x = s_i$。

- 当 $x$ 是大写字符时，改为小写：

```cpp
if(x >= 'A' && x <= 'Z')
	n_PID += x - 65 + 97;
```

- 当 $x$ 是下划线的时候，改为 $-$:

```cpp
if(x == '_')
	n_PID += '-';
```

- 否则不做修改。

## 代码

```
#include <iostream>
#include <string>
using namespace std;
string PID;
string down(string PID) {
	string n_PID;
	for(auto& x : PID)
		if(x >= 'A' && x <= 'Z')
			n_PID += x - 65 + 97;
		else if(x == '_')
			n_PID += '-';
		else 
			n_PID += x;
	return n_PID;
}
int main() {
	cin >> PID;
	cout << "solution-" << down(PID);
	return 0;
}
```

---

## 作者：C202301 (赞：0)

### 题意简述
给一个字符串，将所有大写字母变成小写，下划线变减号，前面加一个 ```solution-```。
### 解题思路
所有大写字母变成小写操作和下划线变减号操作互不影响，直接在循环中变化即可，最后再加 ```solution-```。直接贴代码：
```
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string uvd;
	cin>>uvd;//输入 
	for(int i=0;i<uvd.size();i++)
	{
		if(uvd[i]>='A'&&uvd[i]<='Z')//如果是大写字母 
		uvd[i]+=32;//变小写 
		if(uvd[i]=='_')//如果是下划线 
		uvd[i]='-';//变减号 
	}
	uvd="solution-"+uvd;//加 solution-
	cout<<uvd;
	return 0;
}
```

---

