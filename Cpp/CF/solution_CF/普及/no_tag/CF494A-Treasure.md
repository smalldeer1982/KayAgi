# Treasure

## 题目描述

Malek has recently found a treasure map. While he was looking for a treasure he found a locked door. There was a string $ s $ written on the door consisting of characters '(', ')' and '\#'. Below there was a manual on how to open the door. After spending a long time Malek managed to decode the manual and found out that the goal is to replace each '\#' with one or more ')' characters so that the final string becomes beautiful.

Below there was also written that a string is called beautiful if for each $ i $ ( $ 1<=i<=|s| $ ) there are no more ')' characters than '(' characters among the first $ i $ characters of $ s $ and also the total number of '(' characters is equal to the total number of ')' characters.

Help Malek open the door by telling him for each '\#' character how many ')' characters he must replace it with.

## 说明/提示

 $ |s| $ denotes the length of the string $ s $ .

## 样例 #1

### 输入

```
(((#)((#)
```

### 输出

```
1
2
```

## 样例 #2

### 输入

```
()((#((#(#()
```

### 输出

```
2
2
1```

## 样例 #3

### 输入

```
#
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
(#)
```

### 输出

```
-1
```

# 题解

## 作者：回青绝影 (赞：5)

事实证明，我只会写水题题解，哎）~~为了赚分（误）~~

就是用最通用的方法，前面的$#$都是1，最后一个填坑。

但是有一说一在统计的时候计算是否合法对我来说实在是太难了，哎，所以就又扫了一遍。

```cpp
#include <bits/stdc++.h>
using namespace std;
char s[100001];
int n,k=0,cnt=0,m=0,t,cn=0;
int main(){
//	scanf("%d",&n);
	scanf("%s",s);
	n=strlen(s);
	for(int i=0;i<n;i++){
		if (s[i]=='(') k++;
		if (s[i]==')') k--;
		if (s[i]=='#') cnt++,k--,t=i;
		if (k<0){puts("-1");return 0;}
	}
	for (int i=t+1;i<=n;i++){
		if (s[i]=='(') cn++;
		if (s[i]==')') cn--;
		cn=max(cn,0);
	}if (cn>0){puts("-1");return 0;}
	for (int i=1;i<cnt;i++) puts("1");printf("%d",k+1);
	return 0;
}
```


---

## 作者：xiaoxiaoxia (赞：4)

# Part 1 题意介绍
题意是要把 `#` 替换成 $1$ 个以上的右括号，使得左括号和右括号的个数相等，且对于 $s$ 的任意一个前缀，右括号的个数不大于左括号的个数。因为个数相等，所以分配给 `#` 的右括号的个数之和是确定的。
# Part 2 思路分析
我们可以把最后一个 `#`之前的 `#` 的取值都是 $1$，最后一个 `#` 则将所有还没有匹配的左括号匹配。
# Part 3 代码部分
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5+10;
char s[N];//存字符串 
int ans[N];//记录答案 
int main()
{
	scanf("%s",s);
	int n=strlen(s);//记录长度 
	int a=0, flag=1, k=0;//a记录左括号的数量，flag记录能否成功匹配，k记录#数量 
	for(int i=0;i<n;i++)
	{
		if(s[i]=='(')//是左括号 
		{
			a++;
		}
		else if(s[i]==')')//是右括号  
		{
			if(a>0)//成功匹配一个 
			{
				a--;
			} 
			else//没有左括号，匹配失败，后面不用看 
			{
				flag=0;
				break;
			}
		}
		else if(s[i]=='#')//#的情况 
		{
			if(a>0)//如果还有左括号 
			{
				ans[++k]=1;//根据思路里的复制唯为一 
				a--;//这样就减掉了一个 
			}
			else//当前没有左括号，无法匹配 
			{
				flag=0;
				break;
			}
		}
	}
	if(a>0&&k==0)//如果这个字符串还有没有匹配的左括号并且没有出现#就失败了。 
	{
		flag=0;
	}
	if(flag)//检验字符串是否匹配成功 
	{
		ans[k]+=a;
		a=0;
		k=0;
		for(int i=0;i<n;i++) 
		{
			if(s[i]=='(') 
			{
				a++;
			}
			else if(s[i]==')')
			{
				if(a>0) 
				{
					a--;
				}
				else 
				{
					flag=0;
					break;
				}
			}
			else if(s[i]=='#')
			{
				if(a<ans[++k])//如果左括号数量太少了，也失败了 
				{
					flag=0;
					break;
				}
				else//有匹配了那么多 
				{
					a=a-ans[k];
				}
			}
		}
		if(a!=0) 
		{
			flag=0;
		}
	}
	if(flag==0) 
	{
		printf("-1");	
	}
	else
	{
		for(int i=1;i<=k;i++)
		{
			printf("%d\n",ans[i]);//输出答案 
		}
	}
    return 0;
}
```


---

## 作者：Gaochenxi103_QWQ (赞：2)

## 题目分析
这个题目是一道 Special Judge 的题目，所以可以有很多种灵活的方案。我觉得，最简单直接的方法就是，统计需要加多少右括号，然后统计一下有多少个井号，并且让前面的井号都加一个，**剩下的都加到最后一个身上**。

**注意：如果与要加的括号少于井号的话就直接特判。**

所以直接可以写出代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int cnt,num; 
signed main() {
	ios::sync_with_stdio(0);
	cout.tie(0);
	cin.tie(0);
	string item;
	cin>>item;
	for(int i=0;i<item.size();i++)
	{
		if(item[i]=='(') cnt++;
		if(item[i]==')') cnt--;
		if(item[i]=='#') num++;
 	}
 	if(cnt<=0 or cnt<num) cout<<-1;
 	else
 	{
 		for(int i=1;i<=num;i++)
 		{
 			if(i!=num) cout<<1<<"\n",cnt--;
 			else cout<<cnt;
		}
	}
	return 0;
}


```


------------
这道题目其实难度没有那么高。

---

## 作者：chenziqian (赞：2)

这道题就是括号匹配的加强版，思路是一样的。
让前几个#当1个)，最后一个#挑大梁，差多少 ' ) ' 补多少 ' ) ' 。
好了，上代码！
```cpp
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<stack>
#include<queue>
#include<set>
#include<map>
#include<ctime>
#include<climits>
#include<vector>
using namespace std;
string s;
int main()
{
	cin>>s;
	int a=0,w=0;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]=='(') a++;
		if(s[i]==')') a--;
		if(s[i]=='#') a--,w++;
		if(a<0)
		{
			cout<<"-1";
			return 0;//特判
		}
	}
	int p=0,t=0;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]=='#')
		{
			t++;
			if(t==w) p-=a;
			p--;
		}
		if(s[i]=='(') p++;
		if(s[i]==')') p--;
		if(p<0)
		{
			cout<<"-1";
			return 0;//特判
		}
	}
	for(int i=1;i<w;i++) cout<<"1"<<endl;
	cout<<a+1;
	return 0;
}

```

---

## 作者：封禁用户 (赞：2)

# **前言：感谢各位大佬的支持**

# [@Guoyh](https://www.luogu.org/space/show?uid=88449)

## 二话不说，放代码：
````
# include <queue>
# include <stack>
# include <cstdio>
# include <vector>
# include <cstring>
# include <algorithm>
# define F(i, a, b) for (int i = a; i < b; i++)//宏定义不说了
using namespace std;
char s[10000050];//字符串
int main(){

   
        scanf("%s", &s);
        int l = strlen(s), now = 0, num = 0, t = 0, n = 0;//初步定义
        F(i, 0, l){
                if (s[i] == '(') now++;//以now来表示括号数匹配
                if (s[i] == ')') now--;
                if (s[i] == '#'){
                        now--;
                        num++;//抵消，#number++；
                }
                if (now < 0){
                        printf("-1\n");
                        return 0;//不符合要求直接输出-1
                }
        }
        F(i, 0, l){
                if (s[i] == '(') n++;
                if (s[i] == ')') n--;
                if (s[i] == '#'){
                        t++;
                        if (t == num) n -= now;
                        n--;//计算过程
               }
                if (n < 0){
                        printf("-1\n");//不符合要求直接输出-1
                        return 0;
                }
        }
        F(i, 0, num - 1) printf("1\n");输出括号字符串匹配
        printf("%d\n", now + 1);//最后在输出数量
        return 0;
}
```
# **拒绝抄袭，从我做起**
## [推销团队](https://www.luogu.org/team/show?teamid=12607)

---

## 作者：lby_commandBlock (赞：1)

## 思路

其实拿道题第一时间想到的是 DP，但是后来理解题意后发现，在前面 $cnt-1$ 个可以都设置为一个 `#`，然后将这些欠的直接拖到最后一个即可。

接下来看代码实现，细节有点多。

## 代码

```cpp
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int k, back, cnt;

string s;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> s;
	int n = s.size();
	s = " " + s;
	for (int i = 1; i <= n; i++) {
		if (s[i] == '(') {
			// 需要量加一
			k++;
		} else if (s[i] == ')') {
			// 需要量减一
			k--;
		} else {
			// 将当前字符假设为一个 ')'
			k--;
			cnt++;
			back = i;
			// 设置最后一次处理为 back
		}
		if (k < 0) {
			// 有太多的 #
			cout << -1 << endl;
			exit(0);
		}
	}
	// 判断匹配
	int pipei = 0;
	for (int i = back + 1; i <= n; i++) {
		if (s[i] == '(')
			pipei++;
		else {
			if (pipei > 0)
				pipei--;
		}
	}
	// 必须要等于 0 才算匹配
	if (pipei > 0) {
		cout << -1 << endl;
		exit(0);
	}
	// 前面 cnt - 1 个每个就 1 个 )
	for (int i = 1; i < cnt; i++)
		cout << 1 << endl;
	// 最后一个是 k + 1 个
	cout << k + 1 << endl;
	return 0;
}
```

---

## 作者：Super_dark (赞：1)

## 思路
乍一看就是括号匹配，但要考虑 `#`。

在这里我们用最常见的方法。既前面几个 `#` 只当一个右括号用，最后一个承担剩下的所有。

当然，我们要判断是否有解。一次看右括号是否比左括号多（`#` 只能变右括号），一次看是否有“错位”现象，如 `(#)(`。

## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int n,k,cnt,m,t,cn;
int main(){
	cin>>s;
	n=s.size();
	for(int i=0;i<n;i++){//小提示：字符要从0开始
		if (s[i]=='(') k++;
		if (s[i]==')') k--;
		if (s[i]=='#') cnt++,k--;
		if (k<0){
			printf("-1");
			return 0;
		}
	}
   //判断右括号是否比左括号多。
	for(int i=0;i<n;i++){
		if(s[i]=='#')
		{
			t++;
			if(t==cnt) 
				cn-=k;
			cn--;
		}
		if (s[i]=='(') 
            cn++;
        if (s[i]==')') 
            cn--;
        if(cn<0){
        //看是否有 “ 错位 ” 现象
            printf("-1");
            return 0;
        }
	}
	for (int i=1;i<cnt;i++) 
		printf("1\n");
	printf("%d",k+1);
	return 0;
}
```



---

## 作者：_xdd_ (赞：0)

萌新刚学 OI，CF 是训练 SPJ 的代码社区吗？

对于每一个 `#`，前面的就转化为正常的一个右括号，最后一个变成**没有被匹配的左括号的数量个**右括号，如果没有需要匹配的左括号则无解，看完这个解法全班都炸了。


```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define r0 return 0
#define inf (0x7fffffff)
#define maxn (  +5)
//#define int long long
using namespace std;
inline int read(){int x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
string str;
int last,num,len,cnt;
signed main(){
    cin >> str;
    str=' '+str;
    len=str.size();
    for(int i=1;i<=str.size();i++){
        if(str[i]=='('){
            num++;
        }else if(str[i]==')'){
            num--;
        }else if(str[i]=='#'){
            num--;
            last=i;
            cnt++;
        }
    }
    num++;
    if(num<=0){cout << -1;r0;}
    for(int i=1;i<cnt;i++){
        cout << 1 << endl;
    }
    cout << num;
    return 0;
}
```

---

## 作者：OIerZhang (赞：0)

# [CF494A Treasure](https://www.luogu.com.cn/problem/CF494A)

## 思路

乍一看，这题好像无从下手，如何成功地将符合要求的字符串构造出来呢？

我们不妨将前面的 `#` 都换成 $1$ 个 `)`，再把最后一个 `#` 换成剩余未匹配的左括号的数量。

于是这道题就很简单了，下面我来说一下要输出 `-1` 的几个地方。

1. 遇到 `)` 时如果其他括号都已匹配。
2. 遇到 `#` 时如果其他括号都已匹配。
3. 计算是否合法时有没匹配的括号。

那么，就开写吧！

## 代码

1. 初始化和输入。

```cpp
void end()
{
	cout << -1;
	exit(0);
}

string s;
int ans[100005];
int n, brk = 0, hst = 0; // brackets '(' , hashtag '#'
cin >> s;
n = s.size();
```

2. 构造 + 判断 1、2。

```cpp
for (int i = 0; i < n; i++)
{
    if (s[i] == '(')
        brk++;
    else if (s[i] == ')')
    {
        if (brk)
            brk--;
        else // 判断 1
            end();
    }
    else if (s[i] == '#')
    {
        if (brk)
            ans[++hst] = 1, brk--;
        else // 判断 2
            end();
    }
}
ans[hst] += brk;
```

3. 判断是否合法 + 判断 3。

```cpp
brk = 0, hst = 0;
for (int i = 0; i < n; i++)
{
    if (s[i] == '(')
        brk++;
    else if (s[i] == ')')
    {
        if (brk)
            brk--;
        else
            end();
    }
    else if (s[i] == '#')
    {
        if (brk >= ans[++hst])
            brk -= ans[hst];
        else
            end();
    }
}
if (brk) // 判断 3
    end();
```

4. 输出结果。

```cpp
for (int i = 1; i <= hst; i++)
    cout << ans[i] << endl;
```

**[AC！](https://www.luogu.com.cn/record/148264856)**

---

## 作者：National_Studying (赞：0)

一眼贪心。

从 `#` 的个数入手，假设有 $n$ 个 `#`。

一开始考虑统计未匹配的左括号的个数，然后用 `#` 在这之前补齐即可，但是 `(#)` 就出问题了。

接着就考虑 $1$ 到 $n - 1$ 个 `#` 变成一个 `)`，那么第 $n$ 个 `#` 就可以变成剩余需要的 `)`。

然后最后的情况为 `(` 个数与 `)` 个数相等且在任意位置 `(` 的个数大于等于 `)` 的个数。

---

## 作者：CaoSheng_zzz (赞：0)

### 题意：

给出一个序列 $s$，序列上有 `(`、`)`、`#` 三个字符，现在题目想要知道有没有一种方案使每个 `#` 号变成 $1 \sim \infty$ 个 `)` 使该序列所有 `(` 都能匹配一个 `)`，匹配条件是 `)` 的位置在 `(` 的位置后面，且每个括号只能匹配一次。

### 思路：

不难发现本题可以用贪心完成。

假设有 $n$ 个 `#`，我们将 $1 \sim n - 1$ 个 `#` 变成 $1$ 个 `)` 那么第 $n$ 个 `#` 就可以变成还需要的 `)` 个数个 `)`。

然后有解的情况为 `(` 个数与 `)` 个数相等且对于任意一个位置 `(` 的个数大于等于 `)` 的个数。

Code：
```cpp
void Solve() {
    scanf("%s", s + 1) ;
    int len = strlen(s + 1) ;
    for(int i=1 ; i<=len ; i++) {
        if(s[i] == '(') ++ a ;
        if(s[i] == ')') ++ b ;
        if(s[i] == '#') ans[++ cnt2] = 1, ++ b ;
    }
    ans[cnt2] += a - b ;
    if(ans[cnt2] <= 0) puts("-1") ;
    else {
        bool flag = true ;
        a = b = 0 ;
        for(int i=1 ; i<=len ; i++) {
            if(s[i] == '(') ++ a ;
            if(s[i] == ')') ++ b ;
            if(s[i] == '#') b += ans[++ cnt1] ;
            if(b > a) { puts("-1") ; return ;}
        }
        if(a != b) puts("-1") ;
        else for(int i=1 ; i<=cnt2 ; i++) output(ans[i]), ent ;
    }
    return ;
}
```

---

## 作者：wrongaaa (赞：0)

## 思路
这是一道很水的题，读入 $s$ 之后预处理出 $sum$，且处理好 $put$ 数组，处理方法为：遇到 `#` 就 `put[++point] = 1` 并且 `sum -= 1`，是左括号就 `sum += 1`，右括号就 `sum -= 1`。说人话就是：把所有 `#` 设为 `1`，最后一个来填坑。处理结束后，判断 $sum$，再对 $put$ 做一次处理。重置 $sum$ 与 $point$，再处理一遍，此时再判断一遍 $sum$ 就可以输出了。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

string s;
int len,sum,point,put[114514];

int main() {
	cin >> s;
	len = s.size();
	for (int i = 0; i < len; i++) {
		if (s[i] == '(')
			sum += 1;
		else {
			if (s[i] == ')')
				sum -= 1;
			else {
				put[++point] = 1;
				sum -= 1;
			}
		}
	}
	if (sum > 0)
		put[point] += sum;
	sum = 0,point = 0;
	for (int i = 0; i < len; i++) {
		if (s[i] == '(')
			sum += 1;
		else {
			if (s[i] == ')')
				sum -= 1;
			else 
				if (s[i] == '#')
					sum -= put[++point];
		}
	}
	if (sum != 0)
		cout << -1 << endl;
	else 
		for (int i = 1; i <= point; i++)
			cout << put[i] << endl;
	return 0;
}
```
## 错误原因
但是如果你交了这个代码之后就会惊奇的发现：**没过**。\
设妨想一下：当文件为 `((#)())#(`，坑是填上了，但是错位了，导致不可行。\
所以在第二次判别时，应每次循环时判断 $sum \le 0$，这样就可以了。
## 真．代码
```cpp
#include <bits/stdc++.h>
using namespace std;

string s;
int len,sum,point,put[114514];

int main() {
	cin >> s;
	len = s.size();
	for (int i = 0; i < len; i++) {
		if (s[i] == '(')
			sum += 1;
		else {
			if (s[i] == ')')
				sum -= 1;
			else {
				put[++point] = 1;
				sum -= 1;
			}
		}
	}
	if (sum > 0)
		put[point] += sum;
	sum = 0,point = 0;
	for (int i = 0; i < len; i++) {
		if (s[i] == '(')
			sum += 1;
		else {
			if (s[i] == ')')
				sum -= 1;
			else 
				if (s[i] == '#') {
					sum -= put[++point];
				}
			if (sum < 0) {
				cout << -1 << endl;
				return 0;
			}
		}
	}
	if (sum != 0)
		cout << -1 << endl;
	else 
		for (int i = 1; i <= point; i++)
			cout << put[i] << endl;
	return 0;
}
```

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF494A)

一道贪心题。

贪心策略是除了最后一个 `#` 其他的都变成 $1$ 个 `)`，这样前面的 `)` 就尽可能的少，最后的 `#` 变成的 `)` 数量加上前面的 `)` 数量等于 `(` 的数量，这样在最后所有的括号都会匹配。最后检查一下合不合法。

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
string s, tmp;
int sum1, sum2, sum3, sum4, cnt, last; // sum1 和 sum2 用来判断最后一个 # 要变成多少个 )
signed main() {
    ios :: sync_with_stdio(0);
    cin >> s;
    if (s.size() == 1) {
        cout << -1;
        return 0;
    } // 如果只有 1 个字符必然无解
    for (int i = s.size() - 1; i >= 0; i--) {
        if (s[i] == '#') {
            cnt++;
            last = i;
            break;
        }
    }
    for (int i = 0; i < s.size(); i++) {
        if (i == last) continue; // 最后一个 # 先不处理
        if (s[i] == '(') sum1++; 
        else if (s[i] == ')') sum2++;
        else {
            cnt++;
            s[i] = ')';
            sum2++;
        }
    }
    if (sum1 == sum2) {
        cout << -1;
        return 0;
    } // 必然无解，因为 # 必须变成 1 个以上的 )
    for (int i = 1; i <= sum1 - sum2; i++) tmp += ')';
    s.replace(last, 1, tmp);
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') sum3++;    
        if (s[i] == ')') sum4++;
        if (sum4 > sum3) {
            cout << "-1";
            return 0;
        }
    } // 判断是否合法
    for (int i = 1; i <= cnt; i++) {
        if (i == cnt) cout << sum1 - sum2;
        else cout << 1 << "\n"; 
    } // 贪心策略
    return 0;
}
```


---

## 作者：_ayaka_ (赞：0)

### 思路

刚入手想到统计未匹配左括号的个数，每个 `#` 把前面的补上。然而遇到 `(#)` 这种就报废了。

遂想到一个左括号只要能匹配就行，无论远近，可将所有 `#` 设为 $1$，由最后一个填坑，并随时判断对于每个 `#`，前面可匹配的左括号是否小于 $1$ 即可。

### 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int k, cnt, m, last, l, r;
int main() {
	cin >> s;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '(') k++;
		if (s[i] == ')') k--;
		if (s[i] == '#') cnt++;
	}
	if (k <= 0 || k < cnt) {
		cout << "-1";
		return 0;
	}
	for (int i = 1; i <= cnt - 1; i++) cout << "1\n";
	cout << k + 1 << "\n";
	return 0;
}
```

---

