# yyy loves physics IV

## 题目背景

“颤抖吧，实验室！”

yyy再一次来到了那个惨遭蹂躏的实验室。


## 题目描述

这次，在 Round1 里几乎壮烈牺牲的电路君又被翻了出来。一共有 $N$（$1 \le N \le 26$）个元件。

物理学霸 yyy 用一堆导线将他们连了起来，串联，并联，各种联……

但由于 yyy 的操作太不规范，导致每个元件都有损坏的风险，yyy 用他那天才的脑子算出元件 $i$ 损坏而断开的概率是 $p_i$（$0 \le p_i \le 1$），因为电路太复杂，yyy 请你帮忙算出电路断路的概率。

电路连接方式：

- 一个元件是最小的电路，用 $A$ 表示元件 $1$，$B$ 表示元件 $2$，以此类推。

- $K$ 个电路组成的串联电路表示为电路 $1,2,\dots,K$。

- $K$ 个电路组成的并联电路表示为（电路 $1$）（电路 $2$）......（电路 $K$）。

## 样例 #1

### 输入

```
5                            
(A,B)((C)(D),E)
0.2
0.3
0.4
0.5
0.6```

### 输出

```
0.2992```

# 题解

## 作者：BitByBit (赞：7)

[AC记录](https://www.luogu.com.cn/record/209344965)
### 题意
给你一个电路，电路中的元件有一个损坏的概率，求整个电路断路的概率。
### 分析
令 $P$ 为整个电路断路的概率，$P_1,P_2$ 分别为 $R_1,R_2$ 断路的概率。
![](https://cdn.luogu.com.cn/upload/image_hosting/iph38t36.png)
如图，对于一个串联的电路，$R_1$ 和 $R_2$ 中只要有一个损坏了，整个电路就断路了。所以只有两个元件都不损坏才能使整个电路不损坏。所以根据乘法原理 $P=1-(1-P_1)\times (1-P_2)$。
![](https://cdn.luogu.com.cn/upload/image_hosting/sdz9mvxs.png)
同理，对于并联电路，只有两个原件断路，整个电路才断路。所以 $P=P_1 \times P_2$。

于是就把题目变成了表达式求值。

首先应匹配括号。用一个栈，每次遇到左括号就压入，遇到右括号就让栈顶括号匹配当前括号。
```cpp
#define ll long long
...
stack<ll>q;
...
for(ll i=1;i<=m;i++)
    if(s[i]=='(')q.push(i);
  	else if(s[i]==')')
  	{
  		f[q.top()]=i;
  		q.pop();
  	}
```
然后分治处理表达式。
```cpp
double dfs(ll x,ll y)//处理s[x..y]
{
	if(f[x]==y)//如果x和y匹配就把括号去掉
	{
		x++;y--;
	}
	if(x==y&&isalpha(s[x]))return a[s[x]-64];
//如果只有一个元件就返回其损坏概率
	ll k=0;
	for(ll i=x;i<=y;i++)
	{
		if(s[i]=='(')k++;
		else if(s[i]==')')k--;
		if(k==0&&s[i]==',')return 1-(1-dfs(x,i-1))*(1-dfs(i+1,y));
//找到串联的地方，分治解决两边
	}
	for(ll i=x;i<=y;i++)
	{
		if(s[i]=='(')k++;
		else if(s[i]==')')k--;
		if(k==0&&s[i]==')'&&s[i+1]=='('&&i!=y)return dfs(x+1,i-1)*dfs(i+1,y);
//找并联的地方
	}
	return 1;
}
```
所求就是 `dfs(1,n)`。
### 完整程序
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=100010;
ll n,m;
ll f[N];
double a[N];
string s;
stack<ll>q;
double dfs(ll x,ll y)
{
	if(f[x]==y)
	{
		x++;y--;
	}
	if(x==y&&isalpha(s[x]))return a[s[x]-64];
	ll k=0;
	for(ll i=x;i<=y;i++)
	{
		if(s[i]=='(')k++;
		else if(s[i]==')')k--;
		if(k==0&&s[i]==',')return 1-(1-dfs(x,i-1))*(1-dfs(i+1,y));
	}
	for(ll i=x;i<=y;i++)
	{
		if(s[i]=='(')k++;
		else if(s[i]==')')k--;
		if(k==0&&s[i]==')'&&s[i+1]=='('&&i!=y)return dfs(x+1,i-1)*dfs(i+1,y);
	}
	return 1;
}
int main()
{
	scanf("%lld",&n);
	cin>>s;
	s=" "+s;
	m=s.size()-1;
	for(ll i=1;i<=n;i++)
		scanf("%lf",&a[i]);
	for(ll i=1;i<=m;i++)
		if(s[i]=='(')q.push(i);
		else if(s[i]==')')
		{
			f[q.top()]=i;
			q.pop();
		}
	printf("%.4f",dfs(1,m));
}
```

---

## 作者：Lyx8058 (赞：7)

# 思路来源：
沪粤版九年级上册物理书。
# 题意：
探究串并联电路的断路概率。
# 串并联损耗情况：
- 并联：

![并联电路](https://cdn.luogu.com.cn/upload/image_hosting/6venz9xq.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如图所示，该图像为一个典型且最简单的并联电路，其中已给定定值电阻 $R_1$ 、 $R_2$ 的损耗概率为 $P_2$ 、 $P_2$ 。

若要使该电路**整体**断路，则要使**每一条路线**都断路，则该电路的损耗概率为 $P_1P_2$ 。

同理可得，当有 $n$ 个并联的定值电阻时，整体电路的损耗率为： $\prod_{i=1}^n{P_i}$ 。

- 串联：

![串联电路](https://cdn.luogu.com.cn/upload/image_hosting/p0qp5a8d.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如图所示为一个基础的串联电路，其中给定定值电阻 $R_1$ 、 $R_2$ 的损耗概率为 $P_1$ 、 $P_2$ 。

若要使该电路断路，则任意一个定值电阻断路即可。

那么，不妨使用一个数组 $F$ ， $F_i$ = $1-P_i$ 。设共有 $n$ 个定值电阻串联，则该电路中若要保持不断路，则安全概率为： $\prod_{i=1}^n{F_i}$ 

 $=\prod_{i=1}^n{1-P_i}$ 。

则该电路的不安全概率即**断路概率**为： $1-\prod_{i=1}^n({1-P_i})$ 。

# 总体思路：
已经由上可得串并联电路损耗率转换关系，且知道每个定值电阻的损耗概率，那么可以直接将题目转换为表达式求值了。

（在此不展示代码，因为本人的字符串表达式求值太菜了。）

- 小建议：

写代码的时候先理清楚思路再下手，不然就会像我一样 MLE 。

注意本题输出要保留四位小数，不然会 WA 。

---

## 作者：E_firework (赞：3)

~~水蓝一道~~

公式参考了楼下。

---

我们可以发现，题目对电路的描述是递归的，所以很容易就能想到用递归函数求解。

我们考虑用 `solve(l,r)` 表示原字符串中 $[l,r]$ 这个子串所表示的电路短路的概率。显然当 $l=r$ 时，`solve(l,r)` 等于电子元件短路的概率。
如果 $l \not= r$，接下来我们需要判断这个电路是串联还是并联。根据题意我们可以发现，如果该子串中有逗号不在任何一对匹配的括号中，那么这个电路是串联电路，否则是并联电路。

由乘法原理，一个串联电路短路的概率是组成这个串联电路的小电路的短路概率的积，而一个并联电路短路的概率是 $100\%$ 减去组成这个并联电路的小电路不短路的概率的积。设由 $n$ 个电路组成了一个电路，每个电路短路的概率为 $p_i$，整个电路短路的概率为 $P$。则有：

对于串联电路：

$$
P=\prod\limits_{i=1}^np_i
$$

对于并联电路：

$$
P=100\%-\prod\limits_{i=1}^n(100\%-p_i)
$$

---
实现细节见代码（原谅我的马蜂）：

```cpp
#include <bits/stdc++.h>
#define LL long long
#define max(i, j) (i > j ? i : j)
#define min(i, j) (i < j ? i : j)
#define mes(s, x) memset(s, x, sizeof(s))
using namespace std;
char a[105];
double b[105];
int c[105], nxt[105];//c数组为括号匹配的栈,nxt[i]表示与a[i]匹配的左括号的位置（若a[i]不是右括号，则为0
double solve(int l, int r){
	if(l == r) return b[a[l] - 'A'];
	double tot = 1.0;
	int k = 0, t;//k表示当前未匹配的左括号数 
	bool flag = 1;
	for(int i = l; i <= r; i++){
		if(a[i] == '(') k++;
		else if(a[i] == ')') k--;
		else if(a[i] == ',' && k == 0){
			flag = 0;
			break;
		}
	}
	if(flag){//并联 
		t = r;
		while(t > l){
			tot *= solve(nxt[t] + 1, t - 1);
			t = nxt[t] - 1;
		}
		return tot;
	}else{//串联 
		k = 0;
		t = l;
		for(int i = l; i <= r; i++){
			if(a[i] == '(') k++;
			else if(a[i] == ')') k--;
			else if(a[i] == ',' && k == 0){
				tot *= (1 - solve(t, i - 1));
				t = i + 1;
			}
		}
		tot *= (1 - solve(t, r));
		return 1 - tot;
	} 
}
int main(){
	int n;
	scanf("%d\n%s", &n, a);
	for(int i = 0; i < n; i++){
		scanf("%lf", &b[i]);
	}
	int len = strlen(a), s = 0;
	for(int i = 0; i < len; i++){//括号匹配 
		if(a[i] == '('){
			c[++s] = i; 
		}else if(a[i] == ')'){
			nxt[i] = c[s--];
		}
	}
	printf("%.4lf", solve(0, len - 1));
	return 0;
}
```

---

## 作者：Alarm5854 (赞：2)

这道题目就一篇题解，而且有一个地方貌似讲错了，我就来发一篇题解。

--------

设一段电路断路的概率为 $P$，第 $i$ 个元件断路的概率为 $p(i)$，对于一个串联电路来说，要所有的元件都不断路才能保证这一段不断路，所以由 $n$ 个元件串联的电路断路的概率为：  

$$P=1-\prod_{i=1}^{n}(1-p(i))$$

而对于一段并联电路来说，要所有的元件都断路，这一段电路才会断路，所以由 $n$ 个元件并联的电路断路的概率为：

$$P=\prod_{i=1}^{n}p(i)$$

这样，就可以算出这些串联电路和并联电路的断路概率了。

--------

如何实现呢？拿样例来说，电路 `(A,B)((C)(D),E)` 其实可以把它分为 `A,B` 和 `(C)(D),E` 这两个子电路并联，`A,B` 又可以看成 `A` 和 `B` 这两个子电路串联，`(C)(D),E` 可以看成 `(C)(D)` 和 `E` 这两个子电路串联，最后 `(C)(D)` 可以看成 `C` 和 `D` 这两个子电路并联。所以，先找有没有括号，如果没有的话，这个电路就只有以逗号分隔的元件了，算出这些元件串联起来发生断路的概率即可；否则，找是否有逗号，如果没有的话，就以**该层**每个匹配的括号作为子电路计算下去；否则，找到逗号，就把前面的电路分隔出来串联。这样，就可以算出来整个电路断路的概率了，[代码在此](https://www.luogu.com.cn/paste/0lwlv90w)，请勿抄袭。

--------

这一道题目告诉我们，如果正着算比较难算，那就反过来算，这样也许就会容易一些。



---

## 作者：Tiphereth_A (赞：2)

前往 [我的 Blog](https://blog.tifa-233.com/archives/luogu-p2413/#%E8%A7%A3%E9%A2%98%E6%80%9D%E8%B7%AF) 以获取更好的阅读体验。

---

设 $P(A_{i}),i=1,2,...,n$ 分别为元件1，元件2，……，元件n 断路的概率，则：

- $n$ 个串联元件/电路断路的概率为：

  $$
  P\left(\bigcup_{i=1}^{n} A_{i}\right)=1-\prod_{i=1}^n(1-P(A_i))
  $$

- $n$ 个并联元件/电路断路的概率为：

  $$
  P\left(\bigcap_{i=1}^{n} A_{i}\right)=\prod_{i=1}^nP(A_i)
  $$

于是这个问题就转换成只含有 `+ * ( )` 及数字的表达式求值问题了。


---

## 作者：foglake (赞：1)

## P2413
这题还真是和它的颜色匹配呢（^_^）。

### 题目简述
给一串电路和各元件的损坏概率，求短路概率。
### 解析
根据~~幼儿园~~初中物理可得：**串联一断全断，并联一断不全断，串联一短不全短，并联一短全短**。其中后面这句话没什么用。结合题意，前面这句话解释一下就是：**串联电路中一个元件组断路（损坏），则该电路断路；除非并联电路中所有元件组断路，否则该电路不断路。**

所以显然，并联电路短路概率为：$\displaystyle\prod _{i=1}^n p_i$，其中 $p_i$ 为第 $i$ 个元件组， $n$ 为串联电路的元件组个数。

不过串联电路似乎不是那么好想，我们很难直接推出公式。

既然直接来不行，那我们**间接**来不就行了？容易想到，串联电路通路的概率为 $\displaystyle\prod _{i=1}^n (1 - p_i)$，那么串联电路断路概率为 1 减去通路概率，即 $1 - \displaystyle\prod _{i=1}^n (1 - p_i)$。

### 代码实现
注意到电路的给出方式类似括号序列。所以用递归处理出每个元件组的断路概率。而对于一个元件组，其必由一个若干并联元件组串联组成（当然也可以由一个并联元件组组成，不过为了方便处理，将其视作由一个元件组组成的串联电路）。所以，递归处理出每个元件组的断路概率后，用串联电路公式合并概率。
#### 代码

```cpp
#include <cstdio>
#include <cstring>
using namespace std;
char c[100];
double p[30];
double solve(int l, int r) {
	int deep = 0, cnt = 0, L = l;
	double P[30];
	for (int i = 0; i <= 30; i++) P[i] = 1;//初始化概率
	for (int i = l; i <= r; i++) {
		if (c[i] == '(') deep++;
		if (c[i] == ')') deep--;
		if (c[i] == '(' && deep == 1) L = i; //找并联元件组中电路们的起点
		if (!deep) { 
			if (c[i] == ')') P[cnt] *= solve(L + 1, i - 1);//到达并联元件组中一条电路的终点
			if (c[i] >= 'A' && c[i] <= 'Z') P[cnt] *= p[c[i] - 'A'];//特判
			if (c[i] == ',') cnt ++;//该并联元件组处理完毕
		}
	}
	for (int i = 0; i <= cnt; i++) P[cnt + 1] *= (1 - P[i]);//合并概率
	return (1 - P[cnt + 1]);
}
int main() {
	int n;
	scanf("%d %s", &n, c);
	for (int i = 0; i < n; i++) scanf("%lf", p + i);
	printf("%.4f", solve(0, strlen(c) - 1));
}
```

---

## 作者：RAY091016 (赞：0)

### 1. 题目解释

给出一个电路及各元件断路的概率，求整个电路断路的概率。

### 2. 思路

发现题目给出电路的方式是递归的，所以考虑用递归处理。

考虑用函数 $f(l,r)$ 表示从 $l$ 到 $r$ 一段电路断路的概率，显然，当 $l=r$ 时表示一个元件断路的概率。

然后就是对串并联的判断。

发现如果字符串中有未被括号包括的逗号，那么它就是串联的，否则是并联的。

然后就是找分隔符，算每一段电路的概率了。

接下来就是如何算一条电路断路的概率了。

科普：串联电路只要一个元件断路，整个电路都会断路；并联电路只有全部元件断路，整个电路才会断路。

因而一条串联电路断路的概率为 $1-\prod\limits_{i=1}^n(1-p_i)$，一条并联电路断路的概率为 $\prod\limits_{i=1}^np_i$。

套公式就行了。

### 3. 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
string s;
double p[30];
double f(int l,int r){
	double ans=1.0;
	if(l==r) return p[s[l]-'A'];
	int cnt=0,flag=0;
	for(int i=l;i<=r;i++){
		if(s[i]=='('){
			cnt++;
		}
		if(s[i]==')'){
			cnt--;
		}
		if(s[i]==','&&cnt==0){
			flag=1;
			break;
		}
	}
	if(flag){
		int p=l;
		for(int i=l;i<=r;i++){
			if(s[i]=='('){
				cnt++;
			}
			if(s[i]==')'){
				cnt--;
			}
			if(s[i]==','&&cnt==0){
				ans=ans*(1-f(p,i-1));
				p=i+1; 
			}
		}
		ans=ans*(1-f(p,r));
		return 1-ans;
	}
	else{
		cnt=0;
		int p=l+1;
		for(int i=l;i<=r;i++){
			if(s[i]=='('){
				cnt++;
			}
			if(s[i]==')'){
				cnt--;
				if(cnt==0){
					ans=ans*f(p,i-1);
					p=i+2;
				}
			}
		}
		return ans;
	}
}
signed main(){
	cin>>n>>s;
	for(int i=0;i<n;i++){
		cin>>p[i];
	}
	printf("%0.4lf",f(0,s.size()-1));
	return 0;
}
```

---

