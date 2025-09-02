# Colorful Stones (Simplified Edition)

## 题目描述

There is a sequence of colorful stones. The color of each stone is one of red, green, or blue. You are given a string $ s $ . The $ i $ -th (1-based) character of $ s $ represents the color of the $ i $ -th stone. If the character is "R", "G", or "B", the color of the corresponding stone is red, green, or blue, respectively.

Initially Squirrel Liss is standing on the first stone. You perform instructions one or more times.

Each instruction is one of the three types: "RED", "GREEN", or "BLUE". After an instruction $ c $ , if Liss is standing on a stone whose colors is $ c $ , Liss will move one stone forward, else she will not move.

You are given a string $ t $ . The number of instructions is equal to the length of $ t $ , and the $ i $ -th character of $ t $ represents the $ i $ -th instruction.

Calculate the final position of Liss (the number of the stone she is going to stand on in the end) after performing all the instructions, and print its 1-based position. It is guaranteed that Liss don't move out of the sequence.

## 样例 #1

### 输入

```
RGB
RRR
```

### 输出

```
2
```

## 样例 #2

### 输入

```
RRRBGBRBBB
BBBRR
```

### 输出

```
3
```

## 样例 #3

### 输入

```
BRRBGBRGRBGRGRRGGBGBGBRGBRGRGGGRBRRRBRBBBGRRRGGBBB
BBRBGGRGRGBBBRBGRBRBBBBRBRRRBGBBGBBRRBBGGRBRRBRGRB
```

### 输出

```
15
```

# 题解

## 作者：_QrSn_ (赞：5)

# 题意
给出两个字符串 $s$ 和 $t$，其中的 $R,G,B$ 分别代表石头的三种颜色，松鼠站在 $s$ 的第一位上，如果 $s_{i}$ 等于 $t_{i}$ ,就向前跳一步，最后输出松鼠当前的位置。

# 分析
### 第一种做法
直接模拟即可，先定义一个变量 $ans$,来记录松鼠的位置，然后用一个双重循环来枚举 $t_{j}$ 和 $s_{i}$ 来进行判断，如果相同，将 $ans$ 和 $i$ 加一。

注意：在执行完内部的循环（也就是枚举完 $t_{j}$ ）后要及时退出循环输出答案。
### 代码：
```cpp 
#include<bits/stdc++.h>
using namespace std;
string s,t;
int ans=1;
int main(){
	cin>>s>>t;
	for(int i=0;i<s.size();i++)
	{
		for(int j=0;j<t.size();j++)
		{
			if(s[i]==t[j])
			{
			   ans++;
			   i++; 
			}
		}
		break;
	}
	cout<<ans;
	return 0;
}
```
### 第二种做法
双重循环未必有点繁琐，其实我们可以直接用一个循环来求出最后的答案，因为 $ans$ 和 $i$ 都是同时加一，所以我们可以得出最后 $i$ 和 $ans$ 相等，可直接将 $i$ 代替为 $ans$。

注意：由于字符串从 $0$ 开始，所以要将 $ans$ 初始化为 $0$,最后输出再加一。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t;
int ans=0;
int main(){
	cin>>s>>t;
	for(int j=0;j<t.size();j++)
	{
		if(s[ans]==t[j])
		{
		   ans++;
		}
	}
	cout<<ans+1;
	return 0;
}
```


---

## 作者：_acat_ (赞：2)

难度：$\color{#FE4C61}\text{入门}$

标签：$\color{#0E90D2} \text{字符串 模拟}$

## 题目描述

给你一个字符串 $s$，再给一个字符串 $t$，这两个字符串仅包含 `R` 和 `G` 和 `B`， 代表石头的 $3$ 种颜色。起初，松鼠利斯站在第一块石头上。对于 $t$ 中的每一个字符 $t_i$，如果 $t_i$ 的字符和当前石头的颜色相等，则松鼠利斯就向前走 $1$ 步，否则就原地不动。

## Sol

首先遍历一遍字符串 $t$ ，找到与 $s_{cnt}$ 相等的 $t_i$ 时，则 $cnt+1$。

注：如果数组下标从零开始，那么输出的时候要 $+1$，否则所有的答案都会差 $1$。

## AC 代码
```cpp
#include<iostream>
#include<cstring>
using namespace std;
int cnt=0;
int main()
{
	char t[51],s[51];
	cin>>t>>s;
	long long len=strlen(s);
	for(int i=0;i<len;i++)
		if(s[i]==t[cnt])
			cnt++;
	cout<<cnt+1;
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

建议评级入门。

就是一道简单的字符串+循环题。

先建一个变量 a 表示跳到了第 a 块石头上，这个a也是最后的答案；

当找到与 $t[a]$ 相等的 $s[i]$ 块石头上时， a++ ；

建议用 for 循环。

注意， a 最开始为 0 （我一开始没设 0 就 WA 了）

最后是你们最喜欢的代码环节:

```cpp
#include<bits/stdc++.h>
using namespace std;
int a=0;
string t,s;
int main(){
    cin>>t>>s;
    int s_len=s.length();
    for(int i=0;i<s_len;i++){
        if(s[i]==t[a]){
            a++;
        }
    }
    cout<<a+1; //一定要加1
    return 0;
}
```


---

## 作者：JoseTony (赞：1)

# 思路
这道题只需要简单模拟即可。首先根据题意，我们先定义两个字符串 $s$ 和 $t$ 作为输入。然后定义一个可以改变的变量来记录当前位置，如果字符串 $s$ 中的当前一个等于现在的位置，那么就像前走一，也就是当前位置自增。最后我们要输出的是松鼠现在的位置，需要注意一下如果数组下标从零开始，那么输出的时候位置要加一，否则所有的答案都会差一。
# 代码
```cpp
#include<iostream>
#define ll long long
using namespace std;
int ans;//位置变量
int main(){
	string t,s;
	cin >> t >> s;
	ll len=s.length();//遍历到字符串最后一位
	for(int i=0;i<len;i++){
		if(s[i]==t[ans]){
			ans++;//向前跳1，位置加一
		}
	}
	cout << ans+1 << endl;//输出要加一
	return 0;
}
```


---

## 作者：Jason12 (赞：0)

## 题目：
[传送门](https://www.luogu.com.cn/problem/CF265A)
## 思路：
  **模拟**，用变量 $t$ 表示松鼠当前所在的位置，循环遍历第二个字符串 $b$，若 $a_t = b_i$，则 $t+1$，直到字符串 $a$ 或 $b$ 被遍历完为止。**注意：** 如果字符串从 $0$ 开始输入，则答案需 $+1$，因为题目中松鼠是从第一块石头开始跳的。
## 代码：
```cpp
#include <bits/stdc++.h>
  using namespace std;
int n,m,t,i;
char c[55],d[55];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>c+1>>d+1;//从 1 开始输入，输出时不用 +1。 
	n=strlen(c+1);
	m=strlen(d+1);
	t=1;
	for (i=1;i<=m;i++)//循环遍历。 
	{
		if (c[t]==d[i]) t++;
		if (t==n+1) break;//如果字符串 a 遍历到底就退出循环。 
	}
	cout<<t<<endl;
	return 0;
}

```


---

## 作者：little_rubbish (赞：0)

## 思路
模拟。

用一个计数器来记录“松鼠利斯”所在石头的下标，循环一遍 $t$ 数组，如果与“松鼠利斯”所在石头的下标的颜色相同的话，“松鼠利斯”向前跳一步，否则不变。
## 代码
```cpp
#include<bits/stdc++.h>
#define ll unsigned long long
using namespace std; 
int ans;
string t,s;
int main(){
	cin>>s>>t;
	int len=t.length();
	for(int i=0;i<len;i++){
		if(t[i]==s[ans]){
			ans++;
		}
	}
	cout<<ans+1<<endl;//由于字符串的首位下标为0，所以答案要加一
	return 0;
}
```

---

## 作者：hyc1026 (赞：0)

### 题意简化

给定两个字符串 $s,t$，松鼠在 $s$ 的第一个字符上，遍历 $t$，如果 $t_i$ 的字符和松鼠脚下的字符相同，那么松鼠向前 $1$ 步。直到遍历完 $t$。

### 思路

显而易见，这题模拟即可。通过循环来遍历判断字符是否相同。

### AC Code:

配合注释理解更佳！

要注意字符串下标是从 $0$ 开始的，所以最后的编号要加 $1$。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s,t;
    cin >> s >> t;
    int cur = 0;                  //cur用于定义松鼠目前脚下的石头编号（字符串的下标）
    for(int i=0; i<t.size(); i++) //遍历t，t.size()求出t的长度，注意从零开始到t.size()-1结束
    {
        if(t[i] == s[cur]) cur++; //如果相等，向前走一步
    }
    cout << cur + 1;              //此时的cur相当于是松鼠走的步数，问编号的话要加1
}
```

---

## 作者：Fr0sTy (赞：0)

### 题意简述

其实就是比较两个字符串 $s$ 和 $t$ 的每个字母。

对于 $t$ 中的每一个字符 $t_i$，如果 $t_i$ 的字符和当前石头的颜色相等，则松鼠就向前跳 $1$ 步，否则就原地不动。

### 解题思路

一道简单的字符串模拟。

循环遍历每个 $t$ 中的字符，设现在松鼠的位置为 $site$。

当 $s_{site} = t_i$ 时，松鼠向前移动一格，否则不移动。

### 代码实现

``` cpp
#include<bits/stdc++.h>
using namespace std;
int site; string s,t;
int main() {
	cin>>s>>t;
	for(int i=0;i<t.size();i++) if(t[i]==s[site]) site++;
	printf("%d",site+1);
	return 0;
}
//code by TheCedar
```

---

## 作者：ForeverCC (赞：0)

先输入 $s$ 和 $t$，用一个变量 $ans$ 表示当前跳到了第 $ans$ 块石上（也就是最后的答案）。遍历字符串 $t$ ，找到与 $s_{ans}$ 相等的 $t_i$ 时，$ans+1$ 。最后输出答案。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[105],t[105];
int ans; 
int main() {
	scanf("%s%s",s,t);
	for(int i=0;t[i];i++)
		if(t[i]==s[ans])//判断是否相等 
			ans++;
	printf("%d\n",ans+1);//输出时加上1 
	return 0;
}
```


---

## 作者：GuoWil (赞：0)

## 题目大意：
- 如果字符串的每一个字符的颜色和当前石头的颜色相等，则松鼠就向前跳 $1$ 步，否则就原地不动。

- **需要执行字符串 $t$ 的长度这么多次判断。**

为了更好地理解，比方说第二个样例：字符串前三个的颜色是蓝色，而第一个石头是红色，所以不往前跳。字符串的最后两位都是红色，正好对应前两块石头的颜色，往前跳 $2$ 块。所以最后松鼠站在第 $3$ 块石头上。

**注意：石头的编号是从 $1$ 开始，但是数组下标从 $0$ 开始。所以在判断的时候需要统一。**
```cpp
#include <bits/stdc++.h>
using namespace std;
char s[55],t[55];
int main(){
	int n=1;//石头最开始编号是第一块。
	cin >> s >> t;
	for(int i=0;i<strlen(t);i++){
	   if(t[i]==s[n-1]){//统一石头编号和字符串。
	     n++;
	   }else{
	     continue;
	   }
	}
	cout << n;//最后直接输出跳到的那块石头上。
}
```


---

## 作者：B_lhx (赞：0)

[CF265A Colorful Stones (Simplified Edition)](https://www.luogu.com.cn/problem/CF265A)
====
题目翻译
---
有一序列五颜六色的石头，每一颗石头是红色($R$)、绿色($G$)或蓝色($B$)；输入两个字符串$S$与$T$,分别表示石头序列与指令。一只松鼠Liss站在第一块石头上，第$i$项指令（$T_i$）表示如果在同样颜色的石头上，向前一步，否则下一项指令。输出做完全部指令Liss在第几块石头上。（下标从$1$开始）

思路：模拟
--
首先：定义字符串
```
string s,t;//表示石子序列与指令
```
其次：定义$step$表示$Liss$到哪里了

```
int step=0;
```
最后循环就好啦！
```
#include <bits/stdc++.h>//头文件
using namespace std;
int main(){
	string s,t;//定义字符串S和T，分别表示石头序列与指令
	int step=0;//定义位置
	cin>>s>>t;//输入
	for(int i = 0;i<t.size();i++){//指令查看，执行t.size()次
		if(t[i]==s[step]){//如果指令对应站的石头上
			step++;//走一步++
		}
	}
	cout<<step+1;//输出下标step+1
   return 0;
}
```
本题比较简单，建议红题

---

## 作者：inoichi_lim (赞：0)

### 这题的翻译很简单，大意如下：
- 给两个字符串 $s$ 和 $t$ ， 字符串里的字符 ```R,G,B```表示石头的三种颜色。
- 起初，松鼠利斯站在**第一块石头上**。对于 $t$ 里的每一个字符 $t_i$ ， 如果和松鼠利斯目前的位置 $s_now$ 字符（颜色） 相同，则往前**进一步**，否则**原地不动**。
- 最后输出松鼠利斯在执行完 $t$ 里面任务时的位置 $now$ 。
### 因为$|t|\leq 50$，所以直接简单模拟即可。
- 在翻译后，玄学英语题->小学模拟题。

$code:$
```cpp
#include<bits/stdc++.h>
#define ns "-1"
#define fs(i,x,y,z) for(ll i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(ll i=x;i>=y;i+=z)
#define ll long long
using namespace std;
const int N=100001,inf=0x7f7f7f7f;
int l1,l2,now;
char s[N],t[N];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>s>>t;
    l1=strlen(s),l2=strlen(t);
    fs(i,0,l2-1,1){
        if(s[now]==t[i]) now++;
    }
    cout<<now+1;
    return 0;
}

```

---

