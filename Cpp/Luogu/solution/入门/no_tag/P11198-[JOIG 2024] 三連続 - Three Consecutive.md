# [JOIG 2024] 三連続 / Three Consecutive

## 题目描述

给定长度为 $N$ 的字符串 $S$，$S$ 中的每个字符都是 `o` 或 `x`。

判断 $S$ 中是否包含**连续**的 $3$ 个 `o`。

## 说明/提示

#### 【样例解释 #1】

$S$ 中第 $3\sim 5$ 个字符是连续的 $3$ 个 `o`。

该样例满足子任务 $1,2$ 的限制。

#### 【样例解释 #2】

$S$ 中不存在连续的 $3$ 个 `o`。

该样例满足子任务 $1,2$ 的限制。

#### 【样例解释 #3】

$S$ 中不存在连续的 $3$ 个 `o`。

该样例满足子任务 $2$ 的限制。

#### 【样例解释 #4】

$S$ 中第 $1\sim 3$ 个字符是连续的 $3$ 个 `o`。

注意，$3$ 个连续的 `o` 旁边可能有其他的 `o`。

该样例满足子任务 $2$ 的限制。

#### 【样例解释 #5】

该样例满足子任务 $2$ 的限制。

#### 【样例解释 #6】

该样例满足子任务 $2$ 的限制。

#### 【数据范围】

- $1\le N\le 10^5$；
- $S$ 是长度为 $N$ 且仅包含小写字符 `o` 和 `x` 的字符串。

#### 【子任务】

1. （$40$ 分）$N=5$；
2. （$60$ 分）无附加限制。

## 样例 #1

### 输入

```
5
oxooo```

### 输出

```
Yes```

## 样例 #2

### 输入

```
5
xooxo```

### 输出

```
No```

## 样例 #3

### 输入

```
1
o```

### 输出

```
No```

## 样例 #4

### 输入

```
10
oooooooooo```

### 输出

```
Yes```

## 样例 #5

### 输入

```
20
xooxxoooxoxooxooxoox```

### 输出

```
Yes```

## 样例 #6

### 输入

```
20
xooxxxooxoxooxooxoox```

### 输出

```
No```

# 题解

## 作者：banglee (赞：10)

## P11198 [JOIG 2024 Open] 三連続 / Three Consecutive 题解
[题目传送门](https://www.luogu.com.cn/problem/P11198)

## 正文
这是一道非常基础的题目，建议新手多刷一点这样类型的题目。

对于本题而言，如果字符串 $s$ 第 $i$ 位为 `o`，那么计数器加 $1$。否则，判断计数器的数量是否符合条件，如果符合，那么输出 `Yes`。

如果是符合条件的话，那么在 `for` 循环里就已经输出 `Yes` 了，在 `for` 循环外面就不需要在判断一次了。

## Code
```cpp
s+='x';//设定一个哨兵
for(int i=0;i<=s.size();i++) {//正常是i<s.size()，但是可以用一个哨兵，使代码最后进入else部分
	if(s[i]=='o') t++;
	else {
		if(t>=3) {cout<<"Yes"; return 0;} //符合条件就退出
		t=0;
	}
}
cout<<"No";
```

---

## 作者：songhongying (赞：4)

## 题目大意：
给定长度为 $N$ 的字符串 $S$，$S$ 中的每个字符都是 `o` 或 `x`。判断 $S$ 中是否包含连续的 $3$ 个 `o`。

## 解题思路：
使用查找函数，找出 $S$ 中是否出现连续的 $3$ 个 `o` 即可。查找函数：如果 $S$ 中是否出现连续的 $3$ 个 `o` 则返回 $-1$，否则返回第一个字符出现的位置。

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
int main(){
    
    cin>>n>>s;//输入
    if(s.find("ooo")!=-1)   cout<<"Yes";//如果返回值不为-1，则输出Yes
    else  cout<<"No";//否则输出No
    
	return 0;
}
```

---

## 作者：Kratos_Charger (赞：3)

## P11198 [JOIG 2024 Open] 三連続 / Three Consecutive 题解

### 题目大意

非常水的一道题，如果字符串里面有连续 $3$ 个及以上的 `o`，输出 `Yes`，否则输出 `No`。

### 思路

只需在遍历字符串的同时，统计有几个连续的 `o`，如果为 `x` 就判断计数器是否已经大于等于 $3$，如果大于等于 $3$，输出 `Yes`，反之计数器清零。

### 注意事项

记得在循环外在判断一次计数器是否大于等于 $3$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt;
string s;
int main() {
    cin>>n>>s;
    for(int i=0;i<n;i++){
    	if(s[i]=='o') cnt++;//统计有几个连续的o
    	else{
    		if(cnt>=3){
    			cout<<"Yes";//如果已经有连续的3个，输出Yes
    			return 0;
    		}
    		cnt=0;//计数器清零
    	}
    }
    if(cnt>=3) cout<<"Yes";//外面再判断一次
    else cout<<"No";
    return 0; 
}

```

---

## 作者：Love_Star (赞：2)

# P11198 [JOIG 2024 Open] 三連続 / Three Consecutive 题解
## 题意分析
这道题让我们输入 $N$ 和一个字符串，在这个字符串中找有没有三个连续的 `o` ,有的话输出 `Yes` ,否则输出 `No`。
## 重点解法
以样例一为例子:
```
5 
oxooo
```
循环查找第一个 `o`, 他的左边没有，右边是 `x`,所以不符合条件。\
循环查找第二个 `x`, 不符合条件。\
循环查找第三个 `o`, 他的左边是 `x`，右边是 `o`, 所以不符合条件。\
循环查找第四个 `o`, 他的左边是 `o`，右边也是 `o`, 所以符合条件。\
循环查找第五个 `o`, 他的左边是 `o`，右边没有, 所以不符合条件。\
这里有第四个满足条件，所以输出 `Yes`
## 数据规模
可以看到这题的数据范围的 $N \le 10^5$,所以这题我们开 `int` 够了
## 代码示范

```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
string s; //定义 N 和 字符串 S

int main(){
	cin >> n >> s; //输入
	for(int i = 0;i < s.size();i++){ //字符串专用循环
		if(s[i] == 'o' && s[i - 1] == 'o' && s[i + 1] == 'o'){
            //如果 s[i] 是 o,并且 s[i - 1] 也是 o,并且 s[i + 1] 也是 o
			cout << "Yes"; //条件正确输出Yes
			return 0;//直接结束程序
		}
	}
	cout << "No";//条件不满足输出No
	return 0;
} 
```

---

## 作者：_Douglas_MacArthur (赞：2)

这是一道不折不扣的水题。
# 解析 #
我们直接在字符串的第三个开始搜，如果自己、自己前面的、自己前面的前面都是 `o` 则直接输出 `Yes` 一直搜不到则输出 `No` 。

# 完整代码 #

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
int main(){
	cin>>n;
	cin>>s;
	for(int i=2;i<s.size();i++){//要从 2 开始搜，否则RE等着你
		if(s[i]=='o'&&s[i-1]=='o'&&s[i-2]=='o'){
			cout<<"Yes";
			return 0;//直接结束程序
		}
	}
	cout<<"No";//找不到
	return 0;
}
```

---

## 作者：yangdezuo (赞：1)

# 思路
如果当字符串 $s$ 中有出现连续当三个 `o` 时，就输出 ```Yes```，否则输出 ```No```。

我们可以定义一个变量 $x$，来统计连续 `o` 的个数,当有三个时就可以直接输出 ```Yes```。

因为 $1\leqslant n\leqslant 10^5$，所以直接模拟一遍字符串 $s$ 即可。

# 参考代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x;
string s;
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>s;//读入 
	for(int i=0;i<n;i++){
		if(s[i]=='o') x++;//统计连续 o 的个数 
		else x=0;
		if(x==3){//当连续三个时直接输出即可 
			cout<<"Yes";
			return 0;
		}
	}
	cout<<"No";//没有连续的三个 o 
} 
```

---

## 作者：_dbq_ (赞：1)

## 前言

还没有读题的同学可以点击[这里](https://www.luogu.com.cn/problem/P11198)读题。

知识点：字符串处理、模拟。

## 思路

读入字符串 $S$，从第一个开始扫，用 $cnt$ 记录当前有多少个连续的 `o` 。遇到 `o` 就将 $cnt$ 增加 $1$；遇到 `x` 将 $cnt$ 置零。在循环中判断 $cnt \ge 3$ 是否成立，成立则输出 `Yes`，否则输出 `No`。

## 代码

```cpp
#include<iostream>
#include<iomanip>
#include<string>
#include<cstring>
#define cint const int 
#define LL long long 
using namespace std;
inline LL read(){
    LL x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void solve()
{
    cint n=read();
    string s;
    cin>>s;
    int cnt=0;
    for(int i=0;i<s.size();i++){
    	if(s[i]=='o') cnt++;
    	else cnt=0;
    	if(cnt==3){
    		cout<<"Yes";
    		return ;
		}
	} 
	cout<<"No";
    return ;
}
int main()
{
    solve();
    return 0;
}
```

---

## 作者：zhang_Jimmy (赞：1)

我们可以使用 find 函数解决这个问题。

find 函数是用于在 string 中查找一段连续的字符串存不存在，如果这个字符串不存在，会返回 `string::npos`，否则会返回这个字符串第一个出现的位置。

使用方法：`s.find(c)`，其中 s 是你对进行查找的那个字符串，c 是需要查找的字符串。

对于此题，我们可以使用 `s.find("ooo")` 函数，如果返回了 `string::npos`，就输出 No，否则输出 Yes。

代码如下：


```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    string s;
    int n;
    cin >> n >> s;
    if(s.find("ooo") != string::npos) cout << "Yes";
    else cout << "No";
    return 0;
}
```

---

## 作者：wuyouawa (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P11198)

### 思路

此题很水，直接模拟即可，判断每一个位置和它的后两个位置是否都是```o```即可，不需要判断边界条件，因为最后一个字符后面的都是空的，也不会满足条件，注意在查到输出```Yes```后要结束，如果没结束就是没找到，输出```No```。

### CODE


```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
int main(){
    cin>>n>>s;
    for(int i=0;i<n;i++)
    {
        if(s[i]=='o'&&s[i+1]=='o'&&s[i+2]=='o')
        {
            cout<<"Yes";
            return 0;//结束
        }
    }
    cout<<"No";
    return 0;
}
```

---

## 作者：ykzzldz (赞：1)

快来感受切水题的乐趣！

把字符串读入，然后枚举最后一个位置，看其及前面两个是否为 ```o``` 即可。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
char s[N];
int n;
signed main(){
	cin>>n>>s+1;
	for(int i=3;i<=n;i++){
		if(s[i-2]=='o'&&s[i-1]=='o'&&s[i]=='o'){
			cout<<"Yes";
			return 0;
		}
	}
	cout<<"No";
	return 0;
}
```

---

## 作者：MingRi_Doctor (赞：1)

## 思路：
定义一个变量 $t$，从 $s_0,s_1,s_2,\cdots,s_{n-1}$。如果 $s_i$ 为 `o`，则将 $t$ 加 $1$。 否则，如果 $t$ 大于 $3$ ，输出 `Yes`并结束，$t$ 要清零。如果到最后一位 $t$ 还没有大于 $3$，则输出 `No`。

**注：最后还要多判断一次，因为有可能 $s_{n-1}$ 为 $0$。**

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;
string s;
int main(){
	cin>>n>>s;
	for(int i=0;i<n+1;i++)
	{
		if(s[i]=='o') t++;
		else
		{
			if(t>=3) {cout<<"Yes"; return 0;}
			t=0;
		}
	}
	cout<<"No";
	return 0;
}  
```

---

## 作者：Eason_cyx (赞：0)

简单题，根据题意，直接 $\Theta(n)$ 枚举所有 $3 \le i \le n$ 的 $i$，然后判断是否有 $s_i=s_{i-1}=s_{i-2}=$ `o`。

```cpp
#include <bits/stdc++.h>
using namespace std;
char c[100005];
int main() {
    int n; cin >> n; 
    for(int i = 1;i <= n;i++) {
        cin >> c[i];
    }
    for(int i = 3;i <= n;i++) {
        if(c[i] == c[i-1] && c[i-1] == c[i-2] && c[i-2] == 'o') {
            cout << "Yes"; return 0;
        }
    }
    cout << "No";
	return 0;
}
```

---

## 作者：篮网总冠军 (赞：0)

本题是一道基础的语法题。

读入 $n$ 和字符串 $s$，枚举每个位置 $i$ 是否满足 $s_i,s_{i+1},s_{i+2}$ 是否均为 ``o`` 即可。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int n;
	cin>>n;
	string s;
	cin>>s;
	for(int i=0;i<n-2;i++){
		if (s[i]=='o'&&s[i+1]=='o'&&s[i+2]=='o') {
			cout<<"Yes"<<endl; 
			return 0;
		}
	}
	cout<<"No"<<endl;
	return 0;
}
```

---

## 作者：songzhixin (赞：0)

### 题目大意

判断是否有连续三个 `o`。

### 解题思路

这道题直接从第二个数枚举到倒数第二个数，如果这个 $s_{i-1}$、$s_i$ 和 $s_{i+1}$ 都是 `o`，那么就有连续三个 `o`。

时间复杂度 $O(n)$。

注意自己 $S$ 数组下标是从几开始的。

### 正确代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
string a;
int n;
int main(){
	scanf("%d",&n);
	cin>>a;
	for(int i=1;i<n-1;i++){
		if(a[i-1]=='o'&&a[i+1]=='o'&&a[i]=='o'){//判断是否有连续三个o
			printf("Yes\n");
			return 0;
		}
	}
	printf("No\n");
	return 0;
}
```

---

## 作者：ny_jerry2 (赞：0)

## 思路
这道题非常水，实际上直接对一个序列扫描一遍就好了。  
具体的话其实就是类似有一个长度为 $3$ 的窗口，然后在字符串上扫描，从前往后查找有没有满足条件的字符串。

时间复杂度：$O(n)$。

## 代码
```cpp
#include<iostream>
using namespace std;
int main(){
	int n;
	string s;
	cin>>n>>s;
	for(int i=0;i<n-2;i++){
		if(s[i]==s[i+1]&&s[i+1]==s[i+2]&s[i]=='o'){
			cout<<"Yes";
			return 0;
		}
	}
	cout<<"No";
}
```

---

