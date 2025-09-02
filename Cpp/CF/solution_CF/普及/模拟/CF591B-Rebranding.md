# Rebranding

## 题目描述

The name of one small but proud corporation consists of $ n $ lowercase English letters. The Corporation has decided to try rebranding — an active marketing strategy, that includes a set of measures to change either the brand (both for the company and the goods it produces) or its components: the name, the logo, the slogan. They decided to start with the name.

For this purpose the corporation has consecutively hired $ m $ designers. Once a company hires the $ i $ -th designer, he immediately contributes to the creation of a new corporation name as follows: he takes the newest version of the name and replaces all the letters $ x_{i} $ by $ y_{i} $ , and all the letters $ y_{i} $ by $ x_{i} $ . This results in the new version. It is possible that some of these letters do no occur in the string. It may also happen that $ x_{i} $ coincides with $ y_{i} $ . The version of the name received after the work of the last designer becomes the new name of the corporation.

Manager Arkady has recently got a job in this company, but is already soaked in the spirit of teamwork and is very worried about the success of the rebranding. Naturally, he can't wait to find out what is the new name the Corporation will receive.

Satisfy Arkady's curiosity and tell him the final version of the name.

## 说明/提示

In the second sample the name of the corporation consecutively changes as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/b0c9599f7e4282de011e545b3b2138ce054cf709.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/b503b89dff83c09912a9706615e9f382f03f5909.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/e277cc6136141b35244d23f5857e2b4088822639.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/cfe2461ca78ee24244102008b38c52289020e201.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/c06bdcdcec7417c4f543399c6c3d126f67ecf0a6.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/e46b37134536ad3b6c864840e66c2932fc25c838.png)

## 样例 #1

### 输入

```
6 1
police
p m
```

### 输出

```
molice
```

## 样例 #2

### 输入

```
11 6
abacabadaba
a b
b c
a d
e g
f a
b b
```

### 输出

```
cdcbcdcfcdc
```

# 题解

## 作者：qian_shang (赞：8)

 模拟水题。。

题意：呃呃，就不说了，自己翻译（~~什么？叫我来翻译，好吧~~）

一个小而骄傲的公司的名字由N小写的英文字母组成。该公司已决定尝试重新品牌化-一个积极的营销策略，其中包括一系列措施来改变品牌（无论是对公司和其生产的产品）或其组成部分：名称，标志，口号。他们决定以这个名字开头。

为此，公司先后聘请了M设计人员。一旦一个公司雇佣了第i个设计师，他立即为创建一个新的公司名称做出贡献：他取名字的最新版本并替换所有的字母x【i】变为y【i】,y【i】变为x【i】

…在最后一个设计师的工作之后，名字的版本变成了公司的新名称。

Arkady经理最近在这家公司找到了一份工作，但是他已经沉浸在团队合作精神中，并且非常担心品牌重塑的成功。自然而然地，他迫不及待地想知道公司会收到什么新名称。

满足Arkady的好奇心，告诉他名字的最终版本。

（~~大概就是这样了，翻译过后，吐了一口老血~~）

------------

 是不是很简单，很轻松，想着暴力模拟做出来

 那你就昏头了，看数据范围没有？(1<=n,m<=200000) 
**如果你纯模拟的话，要用好多好多（~~我不是算不来，给你们点机会，自己算~~）的时间**

 所以我们的优化就来了

**反正都是换，你一直换，和最后换没什么区别，是不是听起来很有道理 **

**所以，干脆创一个数组来存贮每个字母最后的变化 **

**这样就把O（n*m）的算法，变成了O（n+m），是不是很神奇？**

最后，贴代码

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int n,m;
char f1[27],f2[27],s[200000],a,b;
int main()
{
    scanf("%d%d",&n,&m);
    scanf("%s",s);//读入
    for(int i=0;i<26;i++)
        f1[i]=i+'a';
    while(m--)
    {
        scanf(" %c %c",&a,&b);
        swap(f1[a-'a'],f1[b-'a']);//交换交换字母的值
    }
    for(int i=0;i<26;i++)
        f2[f1[i]-'a']=i+'a';//替换
    for(int i=0;i<n;i++)
        printf("%c",f2[s[i]-'a']);//输出
    return 0;//完美的结束
}
```
**(~~短小精干对不对？~~）**

---

## 作者：wanggk (赞：4)

题意：多次操作，每次操作将字母 $x$ 变 $y$ , $y$ 变 $x$ .

（注意： $1≤n,m≤200000$ ）

## 首先我们想到暴力：

$m$ 次操作，每次操作遍历长度为 $n$  的字符串，复杂度 $O(mn)$ 肯定行不通。

## 怎么优化呢？

$x$ —> $y$ ， $y$ —> $z$ 其实等同于 $x$ —> $z$

- 得出结论：记录每个字母在若干次辗转更替后，最终变为了哪个字符

- 到了最后再去遍历初始字符串。

- 时间复杂度约 $O(26m)$ （ $26$ 是因为有 $26$ 个字母）

## 具体思路：

- Step 1：`map<char,char> mp` **（ $mp[i]$ 代表字符 $i$ 被替换成了 $mp[i]$ ）**

- Step 2：初始化`mp[i]=i;` **（初始的时候每个字符都是被替换成它本身的，即未替换）**

- Step 3：替换，$i$ 原本是替换为 $a$ 的，但是现在 $a$ 又要换成 $b$ ，所以其实就相当于把 $i$ 替换为 $b$ ，即 $mp[i]=b$ ;

```cpp
	if(mp[i]==a) mp[i]=b;
	else if(mp[i]==b) mp[i]=a;
```

- Step 4: 最后遍历整个字符串，将 $s[i]$ 替换为 $mp[s[i]]$ .

## 完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
char a,b;
string s;
map<char,char> mp;
int main()
{
	for(char i='a';i<='z';i++) mp[i]=i;//初始化自己被换成自己
	cin>>n>>m;
	cin>>s;
	while(m--)
	{
		cin>>a>>b;
		for(char i='a';i<='z';i++)
		{
			if(mp[i]==a) mp[i]=b;
			else if(mp[i]==b) mp[i]=a;
		}
	}
	for(int i=0;i<s.size();i++) s[i]=mp[s[i]];
	cout<<s<<endl;
	return 0;
}
```


---

## 作者：xhhhh36 (赞：3)

直接用一个数组来存字母的下标，再拿一个数组来存字母现在的值。每次交换两个字母的下标和值。最后再输出交换后的字符串即可。
```cpp
#include <bits/stdc++.h>

using namespace std;
int n,m,t[30],x[30];
string s;
int c(char x)
{
	return x-'a';
}
int main()
{
	cin>>n>>m;
	cin>>s;
	for (int i=0;i<26;i++)
	{
		x[i]=t[i]=i;
	}
	while (m--)
	{
		char a,b;
		cin>>a>>b;
		swap(x[c(a)],x[c(b)]);
		swap(t[x[c(a)]],t[x[c(b)]]);
	}
	for (int i=0;i<n;i++)
	{
		cout<<char(t[c(s[i])]+'a');
	}
	return 0;
}
```


---

## 作者：nightwatch.ryan (赞：1)

## 思路
+ 暴力不可能过，注意数据范围：$1≤n,m≤200000$，复杂度是 $O(mn)$。
+ $a→b,b→c$ 其实也就是 $a→c$，所以最后换和一直换是一样的。那么我们用数组 tmp 存每一次发生的变化，求每个字母最后变成的字母，替换掉就可以了。

## 代码
```cpp
#include<bits/stdc++.h>
#ifndef ONLINE_JUDGE//ONLINE_JUDGE宏
	freopen("Rebranding.in","r",stdin);
	freopen("Rebranding.out","w",stdout);
#endif
using namespace std;
int n,m;
char tmp[30],ans[30];//一个存每次的变化，一个存答案
string str;
int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m 
    cin>>str;
    for(int i=0;i<26;i++)//初始化
    {
    	tmp[i]=i+97;
	}
	char r1,r2;//被替换（Replaced），替换（replacement）
    while(m--)
	{
    	cin>>r1>>r2;
        swap(tmp[r1-97],tmp[r2-97]);//交换字母的序号
	}
    for(int i=0;i<26;i++)//把答案数组全部转换成字母
	{
    	ans[tmp[i]-97]=i+97;
	}
    for(int i=0;i<n;i++)
	{
    	cout<<ans[str[i]-97];
	}
	return 0;
}
```

---

## 作者：Lemansky (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF591B)

## 简化题意

一个长度为 $n$ 的字符串，$m$ 次操作，每次将字符 $x$ 和字符 $y$ 交换。

## 解题方法

直接枚举显然是不可能的，时间复杂度 $\max O(nm)=4\times10^{10}$，无法承受……

但是观察样例可以发现，每个相同字母经过若干次变化后仍然相同！

那么我们就可以用数组 $a$ 存每次变化（覆盖），只需考虑每个字母最后变成的字母，替换输出即可。

- 数组下标字母转换数字太麻烦，直接用字母做下标。

## 重点

每次进行操作的时候，不能直接交换 $a_x$ 和 $a_y$！

看一个简单的例子：

```
3 2
xyz
x y
y z
```

第一次操作，交换 $a_x,a_y$，变为 `yxz`；

第二次操作，交换 $a_y,a_z$，变为 `yzx`？

不可行，因为**要交换的是字母，而非下标**。那怎么解决呢？

- 再开一个数组 $pos$，存每个字符所在下标位置，初始字母等于下标。

- 每次交换 $a_{pos_x}$ 和 $a_{pos_y}$，然后更新。

## ~~你们期待的~~ 极简代码

```
#include<bits/stdc++.h>
using namespace std;
char a[130],pos[130],x,y;
int main(){
    int n,m; string s; cin>>n>>m>>s;//输入
    for(int i='a';i<='z';i++) a[i]=i,pos[i]=i;//初始化
    while(m--) cin>>x>>y,swap(a[pos[x]],a[pos[y]]),swap(pos[x],pos[y]);//操作和更新
    for(int i=0;i<n;i++) cout<<a[s[i]];//输出
    return 0;
}
```

时间复杂度 $O(n+m)$ 。



---

## 作者：zfw100 (赞：0)

# CF591B Rebranding 题解

## 思路

看到这题，很容易想到暴力，但是算一下时间复杂度，又看了眼数据范围，发现肯定会超时，那么肯定需要优化。

不难发现， $a$ 变成 $b$，$b$ 变成 $c$ 可以转化为 $a$ 变成 $c$，那么这样我们就可以定义一个数组先存储变化，最后再一起变字母。

代码不放了。

---

## 作者：封禁用户 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF591B)

# First 题意

给你一个字符串，有 $m$ 次更改，每次都要把字符串中的 $u$ 字符改成 $v$ 字符，$v$ 字符改成 $u$ 字符，求最后的字符串。

# Second 暴力

首先是暴力，很简单，每次询问就模拟一边，暴力修改字符，时间复杂度 $O(nm)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
char s[200005], u, v;
ll n, m;
int main(){
	scanf ("%lld %lld", &n, &m);
	scanf ("%s", s + 1);
	while (m--){
		cin >> u >> v;
		for (int i = 1; i <= n; i++)
			if (s[i] == u) s[i] = v;
			else if (s[i] == v) s[i] = u;
	}
	for (int i = 1; i <= n; i++) cout << (char)s[i]; 
	return 0;
}
```

但显然，对于 $n,m \le 200000$ 的情况来说，这个时间复杂度是接受不了的。

# Third 优化

可以发现，我们没必要去遍历整个字符串，因为相同的字符在相同的操作后，结果是一样的，所以我们只需要存一下每个字符最后会变成什么。

那这个怎么推导呢？显然，如果 $a$ 字符变成了 $b$ 字符，$b$ 字符又变成了 $c$ 字符，那么 $a$ 字符就会变成 $c$ 字符。

所以，我们可以枚举每个字符，只要 $i$ 字符要变成 $u$ 字符，那么改成 $v$ 字符，$v$ 字符同理。

最后输出字符串，时间复杂度 $O(m+n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
char s[200005], u, v;
ll n, m, geng[131]; 
int main(){
	scanf ("%lld %lld", &n, &m);
	scanf ("%s", s + 1);
	for (int i = 'a'; i <= 'z'; i++) geng[i] = i; 
	while (m--){
		cin >> u >> v;
		for (int i = 'a'; i <= 'z'; i++){
			if (geng[i] == u) geng[i] = v;
			else if (geng[i] == v) geng[i] = u;
		}
	}
	for (int i = 1; i <= n; i++) cout << (char)geng[s[i]];
	return 0;
}

```

---

## 作者：fish_gugu (赞：0)

# 题意
输入一个长度为 $n$ 的字符串，并进行 $m$ 次操作，每次操作将字符 $a$ 和 字符 $b$ 的位置交换。
# 思路
首先我们会想到暴力，但注意数据范围，$1 \le  n,m \le 200000$ ，时间复杂度 $O(nm)$ 肯定会超时。
### 优化
我们每次都要换太浪费时间了，还不如**把每次变化存到数组里**，到****最后再处理****。

# 代码
```
#include <iostream>
#include <string>
using namespace std;
char a1[27],a2[27];
int main()
{
    int n,m;
    string s;
    char a,b;
    cin >> n >> m >> s;
    for(int i = 0;i < 26;i++) a1[i] = i + 97; //初始化
    for(int i = 0;i < m;i++)
    {
        cin >> a >> b;
        swap(a1[a - 97],a1[b - 97]); //交换字母的序号
    }
    for(int i = 0;i < 26;i++) a2[a1[i] - 97] = i + 97; //再转换为字母
    for(int i = 0;i < n;i++) cout << a2[s[i] - 97];
    return 0;  
}
```


# 坑点
存变化的 `char a1[27],a2[27]` 这两个数组千万不能用 `string` 类型替代，因为 `swap` 处理不了 `string` 类型。

---

## 作者：liukangyi (赞：0)

# 题目大意
给你一个字符串并给定你操作次数 $m$，每次操作会给你 $x$ 和 $y$ 两个字符，你需将字符串中的 $x$ 字符变为 $y$ 字符，将 $y$ 字符变为 $x$ 字符。

---
# 分析
每次遍历一遍替换即可。

---
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
string s;
char x,y;
void Change(char x,char y){
	for(int i=0;i<s.size();i++){
		if(s[i]==x)
			s[i]=y;
		else if(s[i]==y)
			s[i]=y;
	}
}
int main(){
	cin>>n>>m>>s;
	while(m--){
		cin>>x>>y;
		Change(x,y);
	}
	cout<<s;
	return 0;
} 
```


---

## 作者：zwye (赞：0)

### 题意
多次操作，每次操作将字母 $x$ 变 $y$，$y$ 变 $x$。
### 暴力
首先看见题目就想到——暴力。

暴力，很简单，每次询问就模拟一边，修改字符，时间复杂度 $O(nm)$。

代码：
```c
#include<bits/stdc++.h>
using namespace std;
char s[100010],u,v;
long long n,m;
int main(){
	scanf("%lld %lld",&n,&m);
	scanf("%s",s+1);
	while(m--)
	{
		cin>>u>>v;
		for(int i=1;i<=n;i++)
		{
			if(s[i]==u)s[i]=v;
			else if(s[i]==v)s[i]=u;
		}
	}
	for(int i=1;i<=n;i++)cout<<(char)s[i]; 
	return 0;
}
```

### 那怎么优化呢
但数据的大小 $1≤n,m≤200000$ 与时间复杂度 $O(nm)$ 让暴力的方法只能拿一些分。

暴力的方法是不行了，那就要思考怎么优化。

我们可以发现，没必要去遍历整个字符串，因为相同的字符在相同的操作后，结果是一样的，所以我们只需要存一下每个字符最后会变成什么。

那就把每次变化存到数组里，到最后再处理，就行了。

代码：
```c
#include<bits/stdc++.h>
using namespace std;
char a,b,r[27],e[27];
int n,m;
string s;
int main()
{
    cin>>n>>m>>s;
    for(int i=0;i<26;i++)
		r[i]=i+97;
    for(int i=0;i<m;i++)
    {
        cin>>a>>b;
        swap(r[a-97],r[b-97]);
    }
    for(int i=0;i<26;i++)
		e[r[i]-97]=i+97;
    for(int i=0;i<n;i++)
		cout<<e[s[i]-97];
    return 0;  
}
```


---

