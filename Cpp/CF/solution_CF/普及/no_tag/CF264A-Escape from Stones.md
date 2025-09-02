# Escape from Stones

## 题目描述

Squirrel Liss lived in a forest peacefully, but unexpected trouble happens. Stones fall from a mountain. Initially Squirrel Liss occupies an interval $ [0,1] $ . Next, $ n $ stones will fall and Liss will escape from the stones. The stones are numbered from 1 to $ n $ in order.

The stones always fall to the center of Liss's interval. When Liss occupies the interval $ [k-d,k+d] $ and a stone falls to $ k $ , she will escape to the left or to the right. If she escapes to the left, her new interval will be $ [k-d,k] $ . If she escapes to the right, her new interval will be $ [k,k+d] $ .

You are given a string $ s $ of length $ n $ . If the $ i $ -th character of $ s $ is "l" or "r", when the $ i $ -th stone falls Liss will escape to the left or to the right, respectively. Find the sequence of stones' numbers from left to right after all the $ n $ stones falls.

## 说明/提示

In the first example, the positions of stones 1, 2, 3, 4, 5 will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF264A/c25aff142a5735311a4288820a328b17b4aeb12a.png), respectively. So you should print the sequence: 3, 5, 4, 2, 1.

## 样例 #1

### 输入

```
llrlr
```

### 输出

```
3
5
4
2
1
```

## 样例 #2

### 输入

```
rrlll
```

### 输出

```
1
2
5
4
3
```

## 样例 #3

### 输入

```
lrlrr
```

### 输出

```
2
4
5
3
1
```

# 题解

## 作者：是个汉子 (赞：4)

### 题意

松鼠bored在看小马，现在他要逃避掉下来的石头，石头总是落在bored所在的区间的中间。他有两种选择，一种是向左'l'，使区间右端点变为原来的区间中间，一种是向右'r'，使区间左端点变为原来的区间中间。bored已经想好了自己的行动路线，为了让他可以继续看小马，请你告诉他下落石头从左到右的编号。

### Solution

我们考虑，当石头下落到区间的中间时，松鼠如果向左移动，那么石头就在现在区间的右端点，接下来不管怎么移动，剩下的石头都会在这个石头的左边。松鼠如果向右移动，那么石头就这现在区间的左端点，因为松鼠只能在这个石头的右面移动，所以剩下的石头都在这个石头的右边，可以直接输出。

然后想一下向左移动时的石头咋办，发现向左时掉落的石头，掉的越早，位置越往后即输出的时间越晚，所以我们可以拿 $dfs$ 模拟过程，或者拿栈存储向左掉落的石头，或者拿双端队列存储所有石头。

### 代码

#### 栈

```c++
#include<bits/stdc++.h>

using namespace std;
const int N=1e6+10;
char a[N];

int main(){
    scanf("%s",a+1);
    int len=strlen(a+1);
    stack<int> rk;
    for(int i=1;i<=len;i++){
        if(a[i]=='l') rk.push(i);
        else printf("%d\n",i);
    }
    while(!rk.empty()){
        printf("%d\n",rk.top());
        rk.pop();
    }
    return 0;
}
```

#### dfs

```c++
#include<bits/stdc++.h>

using namespace std;
const int N=1e6+10;
char a[N];
int n;

void dfs(int st){
    if(st==n) return ;
    if(a[st]=='l'){
        dfs(st+1);printf("%d\n",st+1);
    }
    if(a[st]=='r'){
        printf("%d\n",st+1);dfs(st+1);
    }
}

int main(){
    while(scanf("%s",a)!=EOF){
        n=strlen(a);
        dfs(0);
    }
    return 0;
}
```

#### 双端队列

```C++
#include<bits/stdc++.h>

using namespace std;
const int N=1e6+10;
int dq[N];
char a[N];

int main(){
    scanf("%s",a+1);
    int len=strlen(a+1);
    int st=1,ed=len;
    for(int i=1;i<=len;i++){
        if(a[i]=='l'){
            dq[st]=i;
            st++;
        }
        if(a[i]=='r'){
            dq[ed]=i;
            ed--;
        }
    }
    for(int i=len;i>=1;i--)
        printf("%d\n",dq[i]);
}
```



---

## 作者：nightwatch.ryan (赞：3)

## 思路
这道题我们需要找规律，下面的图片以样例一作示例。
![](https://cdn.luogu.com.cn/upload/image_hosting/g0d53a7z.png)
我们发现：如果输入是 $r$，则就按输入的顺序把下标输出，如果输入 $l$，则倒序输出所有输入为 $l$ 的下标。
## 坑点
- 字符数组要开到 $10^5$。
- 要用 scanf 和 printf。

## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char s[1000000];
int main(){
	scanf("%s",s);
	int len=strlen(s);
	for(int i=0;i<len;i++){
		if(s[i]=='r'){
			printf("%d\n",i+1);
		}
	}
	for(int i=len-1;i>=0;i--){
		if(s[i]=='l'){
			printf("%d\n",i+1);
		}
	}
	return 0;
}
```


---

## 作者：分离性漫游 (赞：3)

这道题其实是规律题。

拿样例一来举例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/cnl87fxx.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们观察之后可以发现这样一件事情：

![](https://cdn.luogu.com.cn/upload/image_hosting/i6z8k2hl.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们不难发现：

输出的规律是**如果他的输入是 $ r $ ，那么就按先输入的顺序将他们的下标输出，如果他的输入是 $ l $ ，那么就将所有输入为 $ l $ 的下标倒序输出**。

用同样的规律推 $ 2 $ 和 $ 3 $ 的输出，发现这个规律是可行的。

由此这道题就变得简单了起来。

当然这道题也有坑。

在 $ for $ 循环里不能直接用 $ strlen $ ，否则他每循环一次就执行一次，然后就炸掉了，以及要使用  $ scanf $ 和 $ printf $。

下面附上代码：
```cpp
#include<bits/stdc++.h>
const int MAXN=1e6+5;
using namespace std;
char s[MAXN];
int main()
{
	scanf("%s",s);
	int len=strlen(s);
	for(int i=0;i<len;i++)
	    if(s[i]=='r') printf("%d\n",i+1);
	for(int i=len-1;i>=0;i--)
	    if(s[i]=='l') printf("%d\n",i+1);
	return 0;
}
```


---

## 作者：Speech_less (赞：1)

# CF264A Escape from Stones 题解
## 题目大意
题目原翻译根本看不懂，自己看英文在发现原来是怎么个意思：

有一只仓鼠，原来的位置在区间 $[0,1]$ 中，每一颗石头都会落在区间 $[x,y]$ 中的点 $\frac{x+y}{2}$ 上。每一轮，仓鼠都会往左或右躲，每次闪躲都会是区间 $[x,y]$ 的 $x$ 或 $y$ 变成 $\frac{x+y}{2}$，即将区间的左（右）端点变成区间的中点。
### 主要思路
其实这是一道规律题，观察样例，就可以发现规律，规律大概是这样的：

建造一个数组 $x$ 为：

| 序号 | $-1$ | $-2$  |  $-3$  |  $-4$ |  $-5$  |  $0$  |  $1$  |  $2$  |  $3$  |  $4$ |  $5$  |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 元素 |  $0$ | $0$| $0$ | $0$ | $0$ | $0$| $0$ | $0$| $0$ | $0$ | $0$|

每一次将石头砸下的次序填入表中。如果是向左躲避，则填入 $0$ 左边区间最后一个未填入过元素的空中；反之，则填入右边。

如样例一，`llrlr`。

第一次变换，操作为 `l` 则放在序号为零左边的第一个空的元素，即 $-5$，变换为：

| 序号 | $-1$ | $-2$  |  $-3$  |  $-4$ |  $-5$  |  $0$  |  $1$  |  $2$  |  $3$  |  $4$ |  $5$  |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 元素 |  $0$ | $0$| $0$ | $0$ | $1$ | $0$| $0$ | $0$| $0$ | $0$ | $0$|

同理第二次变换，操作为 `l` 则放在序号为零左边的第一个空的元素，即 $-4$，变换为：

| 序号 | $-1$ | $-2$  |  $-3$  |  $-4$ |  $-5$  |  $0$  |  $1$  |  $2$  |  $3$  |  $4$ |  $5$  |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 元素 |  $0$ | $0$| $0$ | $2$ | $1$ | $0$| $0$ | $0$| $0$ | $0$ | $0$|

第三次变换，操作为 `r` 则放在序号为零右边的第一个空的元素，即 $1$，变换为：

| 序号 | $-1$ | $-2$  |  $-3$  |  $-4$ |  $-5$  |  $0$  |  $1$  |  $2$  |  $3$  |  $4$ |  $5$  |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 元素 |  $0$ | $0$| $0$ | $2$ | $1$ | $0$| $3$ | $0$| $0$ | $0$ | $0$|

以此类推可得到最后的数组为：

| 序号 | $-1$ | $-2$  |  $-3$  |  $-4$ |  $-5$  |  $0$  |  $1$  |  $2$  |  $3$  |  $4$ |  $5$  |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 元素 |  $0$ | $0$| $4$ | $2$ | $1$ | $0$| $3$ | $5$| $0$ | $0$ | $0$|

然后，将负数区间中的所有元素的序号，加个绝对值，移到右边，$x$ 就变为：

| 序号 | $-1$ | $-2$  |  $-3$  |  $-4$ |  $-5$  |  $0$  |  $1$  |  $2$  |  $3$  |  $4$ |  $5$  |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 元素 |  $0$ | $0$| $0$ | $0$ | $0$ | $0$| $3$ | $5$| $4$ | $2$ | $1$|

是不是发现就求出来了？但是，数组的位置不能是负数，所以我们要找其他方法，思考一下。

3，2，1。

时间到，其实很简单，直接在正数区间内进行操作，就像一个双端队列。如果是向左躲避，则填入区间最后一个未填入过元素的空中；反之，则填入右边。直接拿下这道黄题。

------------

### AC 代码上交

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int a[N];
signed main(){
	string s;
	cin>>s;
	int n=s.length();
	int l=1,r=n;
	for(int i=0;i<n;i++){
		if(s[i]=='l') a[r]=i+1,r--;
		else a[l]=i+1,l++;
	}
	for(int i=1;i<=n;i++){
		printf("%d\n",a[i]);
	}
	return 0;
}
```

\* 注：切记勿抄袭，抄袭马上变棕名。

---

## 作者：All_Wrong_Answer (赞：0)

[CF 题目传送门](https://codeforces.com/problemset/problem/264/A)

[luogu 题目传送门](https://www.luogu.com.cn/problem/CF264A)

### 前言：
作者模拟了 $n$ 遍一直 WA#11 终于开始找规律了。

## 找规律：

因为 ```l``` 使区间左移，```r``` 使区间右移，所以 ```l``` 后的所有石头都在当前石头左边，```r``` 后所有石头都在当前石头右边。

接下来观察样例：
```
llrlr
35421
```
把 ```l``` 和 ```r``` 拆出来：


```
ll l
35 2
  r r
  4 1
```
发现 ```l``` 输出顺序单调递减，```r``` 则是单调递增。

再多套几组样例，自己再手搓几组数据，发现也都符合这个规律，那么就很好写啦。

## 完整代码:


```cpp
#include <bits/stdc++.h>
using namespace std;
char x[1000005];
int r[1000005],l[1000005];
int rs=0,ls=0;
int main(){
	cin>>x;
	int s=strlen(x);
	for(int i=0;i<s;i++){
		if(x[i]=='r') r[++rs]=i;
		else l[++ls]=i;
	}
	for(int i=1;i<=rs;i++) cout<<r[i]+1<<"\n";//r则升序 
	for(int i=ls;i>=1;i--) cout<<l[i]+1<<"\n";//l则降序 
	return 0;
}
```

当然，也可以用 DFS 实现，但比较慢：


```cpp
#include <bits/stdc++.h>
using namespace std;
char x[1000005];
int u;
struct node{
	int bh;
	long double wz;
}m[1000005];
void dfs(long double l,long double r,int s){
	if(s==u) return ;
	m[s].bh=s;
	long double mid=(l+r)/2;
	m[s].wz=mid;
	if(x[s]=='l'){
		dfs(l,mid,s+1);
		cout<<s+1<<endl;
	} 
	else{
		cout<<s+1<<endl;
		dfs(mid,r,s+1);
	}
}
int main(){ 
	cin>>x;
	u=strlen(x);
	dfs(-LONG_LONG_MAX,LONG_LONG_MAX,0);
	return 0;
}
```


[CF 通过记录](https://codeforces.com/contest/264/submission/302181276)

---

## 作者：int_stl (赞：0)

这道题的思路如下：
- 设置左边界 $left$ 和右边界 $right$。
- 如果行动路线为 $l$，那么缩小右边界，记录当前石头编号。
- 如果行动路线为 $r$，那么扩大左边界，记录当前石头编号。
- 得出石头从左到右掉落的顺序，并输出。

坑点：不用 `printf` 函数会TLE。  
![](https://cdn.luogu.com.cn/upload/image_hosting/m1mculw9.png)
由此可以得出代码：
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;

    int n = s.length();
    vector<int> stones(n);
    int left = 1, right = n;//设置左边界和右边界

    for (int i = 0; i < n; ++i) {
        if (s[i] == 'l') {
            stones[right - 1] = i + 1;//缩小右边界，记录
            right--;
        }
        else {
            stones[left - 1] = i + 1;//扩大左边界，记录
            left++;
        }
    }

    for (int stone : stones) {
        printf("%d\n", stone);
    }

    return 0;
}

```

---

## 作者：bj12z_donglinxi (赞：0)

## [传送门](https://www.luogu.com.cn/problem/CF264A)

## 题意简述

给出一个字符串，每个字符为 $l$ 或 $r$。字符串的第 $i$ 个字符表示第 $i$ 个石头落下时松鼠向左躲避或者向右躲避，求石头从左到右的编号。

## 分析

这道题我们可以找到一些规律，具体如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/d8smskuq.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

让我们来分析一下：

首先看 $r$，当输入是 $r$ 时，输出和下标是对应的（输出：1 2，下标：1 2），因此可得：

#### 如果输入是 $r$，那么就按输入顺序将下标输出。

然后是 $l$，当输入是 $l$ 时，输出和下标是反着的（输出：5 4 3， 下标：3 4 5），因此可得:

#### 如果输入是 $l$，那么就按输入顺序将下标倒序输出。

那么我们来读一下题中的这个部分：“他有两种选择，一种是向左'l'，使区间右端点变为原来的区间中间，一种是向右'r'，使区间左端点变为原来的区间中间。”很明显，当输入为 $l$ 时是从右向左，也就是倒序；当输入是 $r$ 时是从左向右，也就是正序。因此，我们的结论是正确的。

#### 所以，我们在写代码时，要写两层循环，一层正序一层倒序，具体见代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

string s;//用string类型会比较方便

int main() {
	scanf("%s", &s);//比cin快
	for (int i = 0 ; i < s.size();  i++) {//r情况下的正序输出
		if (s[i] == 'r') {//当输入是r
			printf("%d\n", i + 1);//i+1是下标
		} 
	} 
	for (int i = s.size() - 1 ; i >= 0 ; i--) {//l情况下的倒序输出
		if (s[i] == 'l') {//当输入是l
		    printf("%d\n", i + 1);	
		}
	}  
	return 0;
}
//拒绝抄袭题解，共创和谐洛谷
```

~~我知道做法可能重复了，但看在我解释得这么详细的份上就过了吧~~

---

## 作者：AstaSunch_ (赞：0)

# $\mathsf{0x00}$ 前言
蒟蒻的第 $\color{red}{\mathbf{18}}$ 篇题解。
# $\mathsf{0x01}$ 题意简述
给定一个字符串 $s$，每个字符为 `l` 或 `r`。字符串的第 $i$ 个字符表示第 $i$ 个石头落下时松鼠向左还是向右躲避。求石头从左到右的编号顺序。

# $\mathsf{0x02}$ 题目思路
时间复杂度，$\text{DFS}$。~~（蒟蒻也只会用DFS了）~~

模拟过程如下：

1. 初始化一个空数组 $t$，用于存储石头的顺序。

2. 不难定义一个 $\text{DFS}$ 函数 $\text{dfs(idx,dep,s)}$，三个参数分别是当前石头的编号 $idx$、当前深度 $dep$ 和当前字符串 $s$。在 $\text{DFS}$ 函数中，执行以下操作：

   - 如果 $idx$ 等于字符串的长度，则返回。

   - 如果字符串的第 $idx$ 个字符为 `l`，则向左递归。调用 `dfs(idx+1, dep+1, s)`。

   - 如果字符串的第 $idx$ 个字符为 `r`，则向右递归。调用 `dfs(idx+1, dep+1, s)`。

   - 将当前石头的编号 $dep$ 添加到 $t$ 数组中。

3. 调用 $\text{dfs}$ 函数，传入初始参数 `dfs(0, 1, s)`。

4. 输出 $a$ 中的石头顺序。


------------


还有更简单的写法吗？肯定有。

设 $len$ 为字符串长度，就能写出以下~~清晰明了的~~程序，时间复杂度 $\Theta(|s|)$，其中 $|s|$ 为字符串长度： 
```cpp
void dfs(int dep){
    if(dep==len) return;
    //直接返回
    if(t[dep]=='l'){
        dfs(dep+1);
        cout<<dep+1<<endl;
        /*注意这里dfs函数中的参数不能写 dep++，否则参数传不进去*/
        /*还用两行不能写反顺序*/
    }
    if(t[dep]=='r'){
        cout<<dep+1<<endl;
        dfs(dep+1);
    }
}
```
# $\mathsf{0x03}$ Code
~~核心代码和模拟过程已经给出来了，就不用完整代码了罢……~~

---

## 作者：Yang_OIer (赞：0)

## 分析
这是一道规律题，但规律有点隐蔽，需要细心查找。
### 规律
如果他的输入是 `r`，那么就按先输入的顺序将他们的下标输出，如果他的输入是 `l` ，那么就将所有输入为 `l` 的下标倒序输出。

建议使用"string 类"方便输入，且可以和数组一样使用。

## 代码
```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
string s;//string类 
int main(){
	cin>>s; 
	int len=s.size();//录取长度
	for(int i=0;i<len;i++)//先正序输出为r的下标 
	    if(s[i]=='r')
		cout<<i+1<<endl;
	for(int i=len-1;i>=0;i--)//再倒序输出为l的下标
	    if(s[i]=='l') 
		cout<<i+1<<endl;
	return 0;
}
```


---

## 作者：WinterRain208 (赞：0)

CF264A 【Escape from Stones】

题意：

啥也不是，我自己完全没有看懂，这个时候看样例理解题意。

啥也不是，样例也没看懂。

题意完整翻译：

松鼠初始在区间$[0,1]$，每次落下一个石头，在区间的中间，比如，如果区间是$[k-d,k+d]$，那么石头落在$k$上，松鼠会选择向左躲或向右，向右可以将区间修改为$[k,k+d]$，左就是$[k-d,k]$。现在给你每次躲避记录，下落的石头按位置排列，从左到右输出。

然后样例就看懂啦。

这题直接分析不好做，还是找规律王道，可以发现向右躲时先输出，顺序，向左躲时后输出，倒序。

于是这题就解决了。码风丑陋，请见谅。

### $CODE$

```cpp
#include<bits/stdc++.h>
#define F(i,j,r) for(int i=j;i<=r;++i)

using namespace std;
const int N=1e5+5;

string a;
int main(){
	cin>>a;
	F(i,0,a.size()-1)
		if(a[i]=='r')cout<<i+1<<endl;
	for(int i=a.size()-1;i>=0;--i)
		if(a[i]!='r')cout<<i+1<<endl; 
    return 0;
}

```


---

## 作者：Hutao__ (赞：0)

~~一道 dfs 水题。~~

## 思路

观察样例我们不难知道，当是 $\texttt{l}$ 的时候倒序输出下标，是 $\texttt{r}$ 时直接输出下标。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int len;
void dfs(int n){
    if(n==len)return;
    if(s[n]=='l'){
        dfs(n+1);
        cout<<n+1<<'\n';//下标从0开始
        //是l时先dfs在输出，起到一个倒序的作用
    }else{
        cout<<n+1<<'\n';
        dfs(n+1);
        //是r时直接输出，再dfs
    }
}
int main(){
    cin>>s;
    len=s.size();
    dfs(0);
    return 0; 
}
```

---

## 作者：zhanghx0219 (赞：0)

先来理解一下题意：松鼠 bored 在看小马，现在他要逃避掉下来的石头，石头总是落在 bored 所在的区间的中间。他有两种选择，一种是向左 $l$，使区间右端点变为原来的区间中间，一种是向右 $r$，使区间左端点变为原来的区间中间。 bored 已经想好了自己的行动路线，为了让他可以继续看小马，请你告诉他下落石头从左到右的编号。

我们先找一下规律，不难发现，如果当前输入的字符为 $l$，就将输入字符为 $l$ 的下标倒序输出；如果当前输入的字符为 $r$，就将输入字符为 $r$ 的顺序输出。

有了思路，代码就很简单了。

下面附上代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){f=(c=='-'?-1:1);c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f
    ;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>10)write(x/10);
    putchar(char('0'+x%10));
}
const int N = 1e6+39+7;
string s;int n;
void dfs(int x){
    if(x==n)return;
    if(s[x]=='l'){
        dfs(x+1);
        cout<<x+1<<'\n';
    }else{
        cout<<x+1<<'\n';
        dfs(x+1);
    }
}
int main(){
    while(cin>>s){
        n=s.length();
        dfs(0);
    }
    return 0;
}
```


---

