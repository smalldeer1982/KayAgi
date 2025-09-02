# Reverse

## 题目描述

You are given two positive integers $ x $ and $ y $ . You can perform the following operation with $ x $ : write it in its binary form without leading zeros, add $ 0 $ or $ 1 $ to the right of it, reverse the binary form and turn it into a decimal number which is assigned as the new value of $ x $ .

For example:

- $ 34 $ can be turned into $ 81 $ via one operation: the binary form of $ 34 $ is $ 100010 $ , if you add $ 1 $ , reverse it and remove leading zeros, you will get $ 1010001 $ , which is the binary form of $ 81 $ .
- $ 34 $ can be turned into $ 17 $ via one operation: the binary form of $ 34 $ is $ 100010 $ , if you add $ 0 $ , reverse it and remove leading zeros, you will get $ 10001 $ , which is the binary form of $ 17 $ .
- $ 81 $ can be turned into $ 69 $ via one operation: the binary form of $ 81 $ is $ 1010001 $ , if you add $ 0 $ , reverse it and remove leading zeros, you will get $ 1000101 $ , which is the binary form of $ 69 $ .
- $ 34 $ can be turned into $ 69 $ via two operations: first you turn $ 34 $ into $ 81 $ and then $ 81 $ into $ 69 $ .

Your task is to find out whether $ x $ can be turned into $ y $ after a certain number of operations (possibly zero).

## 说明/提示

In the first example, you don't even need to do anything.

The fourth example is described in the statement.

## 样例 #1

### 输入

```
3 3```

### 输出

```
YES```

## 样例 #2

### 输入

```
7 4```

### 输出

```
NO```

## 样例 #3

### 输入

```
2 8```

### 输出

```
NO```

## 样例 #4

### 输入

```
34 69```

### 输出

```
YES```

## 样例 #5

### 输入

```
8935891487501725 71487131900013807```

### 输出

```
YES```

# 题解

## 作者：ShmilyTY (赞：6)

先将 $x$ 和 $y$ 转成二进制，现在假设 $x\neq y$

由于一次反转之后会去掉所有前导 $0$，也就是原数本来后面的 $0$. 所以每次在 $x$ 末尾加 $0$ 再反转的操作可以理解为直接反转。

另一方面，假如 $y$ 的末尾有 $0$，显然是不可能被得到的。

对于 $x$ 初始时末尾的 $0$，有两种处理方法，全部去掉或者全部留下（在末尾加一个 $1$ 再反转）

那么只需要判断 $x$ 能否通过在最前面和最后面加 $1$ 以及反转两种操作能否到达 $y$ 即可。

这并不难，求出 $x,y$ 的前缀后缀连续 $1$ 的长度 $L_x,R_x,L_y,R_y$，要满足 $L_x\le L_y \& R_x\le R_y$，且去掉这些 $1$ 后的两个部分相同。接着把 $y$ 进行反转再判断一次。

---

## 作者：Fishmaster (赞：2)

### 前言

**[题目链接：CF1618F Reverse](https://www.luogu.com.cn/problem/CF1618F)**

$\text{Difficulty : 2000}$。

个人认为这道题在难度为 $2000$ 的题里面算水的吧。

### 思路

这道题我想了将近 $20$ $\text{min}$，想出来了才发现做法如此的无脑。

首先，如果 $x = y$，那么方案肯定是可行的，因为不用操作就是答案。

然后，我们来研究以下题目的性质。

如果二进制串的末位是 $1$，那么加上 $0$ 再翻转等于没加（因为会被当作前导 $0$ 而被废除）。

而如果二进制串的末尾有若干个 $0$，那么可以再加上一个 $1$ 来满足上一条，或翻转再翻转以去掉末尾的 $0$ 来满足上一条。

由于翻转两次后又可以转回来，所以题目便可以转化为如下的样子（我们令操作前的 $01$ 串为 $s$，$y$ 转化为二进制后得到的 $01$ 串为 $q$）：

给定两个 $01$ 串 $s,q$，一次操作可以给 $s$ 的首位前或末位后加上一个 $1$，问能否经过若干次操作将 $s$ 变成 $q$。

我们设 $x'$ 为 $x$ 转化为二进制后得到的串，则我们有以下可能的 $s$：

- 将 $x'$ 的末位后加上 $1$ 的 $01$ 串；
- 在上一条的基础上，加上翻转的 $01$ 串；
- 将 $x'$ 末尾的所有 $0$ 去除后的 $01$ 串；
- 在上一条的基础上，加上翻转的 $01$ 串。

将以上四种 $s$ 依次进行操作，若有至少一个 $s$ 可以变成 $q$，则证明方案是可行的，否则证明方案是不可行的。

### 代码

冗长的考场代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll x,y;
string s1="",s2="",s3="",s4="",q;
bool ans=0;
string bin(ll x){
    ll k=x;
    string res="";
    while(k){
        if(k&1)res+="1";
        else res+="0";
        k>>=1;
    }
    reverse(res.begin(),res.end());
    return res;
}
void solve(string s){
    int len=s.size(),lenq=q.size();
    for(int i=0;i<lenq-len+1;i++){
        if(q.substr(i,len)!=s)continue;
        bool flag=1;
        for(int j=0;j<i;j++)
			if(q[j]=='0')flag=0;
		for(int j=lenq-1;j>i+len-1;j--)
			if(q[j]=='0')flag=0;
		ans|=flag;
	}
}
int main(){
    cin>>x>>y;
    if(x==y)ans=1;
    s1=bin(x)+"1";
    s2=s1;reverse(s2.begin(),s2.end());
    while(!(x&1))x>>=1;
    s3=bin(x);
    s4=s3;reverse(s4.begin(),s4.end());
    q=bin(y);
    solve(s1);solve(s2);solve(s3);solve(s4);
    if(ans)cout<<"YES";
    else cout<<"NO";
    return 0;
}
```

---

## 作者：XL4453 (赞：2)

### $\text{Difficulty : 2000}$
---
### 解题思路：

添加 $0$ 和没添加直接翻转一个样，而每一次添加 $1$ 之后再翻转就一定能扩大一倍以上，而且可以发现可能的拓展状态是 $\log n$ 级别的。

直接搜索出所有的可能的拓展状态就行了，不需要弄多复杂。反正可能的情况少，随便上什么东西判个重就行了，我在代码中使用的是 $\text{map}$。

要注意的是，当翻转超过一次之后如果当前值比目标值大两倍以上就一定没有办法拓展到目标状态，直接退出即可。但是一开始是有可能有较多的后缀 $0$ 的，一开始就从翻转和未翻转两个状态搜就行了。

---
### 代码：

```cpp
#include<cstdio>
#include<map>
using namespace std;
#define int unsigned long long
int x,y,len,num[100],flag;
map <int,bool> m;
int rev(int now){
	len=0;
	while(now){
		num[++len]=now%2;
		now/=2;
	}
	for(int i=1;i<=len;i++)
	now=now*2+num[i];
	return now;
}
void dfs(int now){
	if(m[now]==1)return;
	m[now]=1;
	if(now==y)flag=1;
	if(now>y*2)return;
	dfs(rev(now));
	now=now<<1;now+=1;
	dfs(rev(now));
}
signed main(){
	scanf("%I64d%I64d",&x,&y);
	dfs(x);dfs(rev(x));
	if(flag)printf("YES\n");
	else printf("NO\n");
	return 0;
}
```


---

## 作者：蒟蒻丁 (赞：2)

考虑两种操作的结果。  
如果添加了 0 ，那么数字两端都不会再有 0 ，也就是说数字的两端都会是一个 1 。  
进一步地，添加了一次 0 之后，再次添加 0 的操作都只是会把原数字翻转。  
如果添加 1 ，那么和第一次添加 0 一样，其结果也是使得数字的两端都是 1 。  
只要我们执行完第一步，无论如何数字的两端都会是 1 ，结合操作 0 的后果 2 ，我们可以发现我们可以随意地在数字两端添加 1 。（把数字翻转，添加1，再次翻转即可在数字前面添加 1 ）  
这个时候我们就有了想法 1 ：把目标串的 1 都脱去，查看是否与原串等价。（把首末连续 1 的个数删至 1 ）  
进一步思考，我们想到，随意脱去原串和目标串的 1 ，不会影响结果，所以我们就把两个串都进行变换，直接比对即可。  
```c++11
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
ll n,m,a[10001],b[10001],xx,yy;
bool pool(1);

void clearA(ll goal){
	while(a[n]==1&&a[n-1]==1)n--;
	reverse(a+1,a+n+1);
	if(goal==0)clearA(1);
}

void clearB(ll goal){
	while(b[m]==1&&b[m-1]==1)m--;
	reverse(b+1,b+1+m);
	if(goal==0)clearB(1);
}

bool work(ll x,ll y){
	if(x==y)return 1;
	n=m=0;
	while(x)a[++n]=x%2,x>>=1;
	while(y)b[++m]=y%2,y>>=1;
	// if(n>m)return 0;
	reverse(a+1,a+1+n);
	while(a[n]==0)n--;
	if(n>m)return 0;
	clearA(0);
	clearB(0);
	if(n!=m)return 0;
	for(ll i=1;i<=n;i++){
		if(a[i]!=b[i]){
			pool=0;
			break;
		}
	}
	if(!pool){
		reverse(1+a,1+a+n);
		for(ll i=1;i<=n;i++)
			if(a[i]!=b[i])return 0;
	}
	return 1;
}

int main(){
	cin>>xx>>yy;
	if(work(xx,yy)||work(xx<<1|1,yy))cout<<"YES";
	else cout<<"NO";
	return 0;
}
```

---

## 作者：Tachibana27 (赞：0)

比较水的位运算


------------

注意到在 $x$ 后加 $0$ 相当于直接翻转一次，因为前导 $0$ 会自动去除。如果当前状态是目标状态 $y$ 的 $2$ 倍以上，就说明无法通过继续反转达到，进行剪枝。考虑到初始状态 $x$ 后面有 $0$，所以正反都搜一遍。

随后爆搜出所有可能，达到目标状态输出并结束程序即可。考虑到数据较大，建议使用 `map` 或 `unordered_map` 作 $vis$ 数组。

code:

```cpp

#include<iostream>
#include<map>
#include<unordered_map>
using namespace std;
#define int unsigned long long
int x,y;
int xx;
unordered_map<int,bool>mp;//比map少个log
int kkk[100086];
int point;
int rever(int x){//反转函数
    point=0;
    while(x){
        kkk[++point]=x&1;//kkk保存反转的x的二进制
        x>>=1;
    }
    for(int i=1;i<=point;i++)
        x=(x<<1)+kkk[i];//算出反转后的10进制
    return x;
}
void dfs(int x){
	if(x==y){//达到目标状态输出并结束
        puts("YES");
        exit(0);
    }
	if(mp[x] or x>(y<<1))//到目标状态的2倍以上
        return;
    mp[x]=true;//mp相当于vis
    dfs(rever(x));//在后面加0等于直接反转
	x<<=1;//在后面补1并反转
    x++;
    dfs(rever(x));
}
signed main(){
    cin>>x>>y;
    if(x==y){//如果相等直接输出即可
        puts("YES");
        exit(0);
    }
    dfs(x);
    dfs(rever(x));//正反都搜一遍
    puts("NO");//还没结束程序就是NO
    return 0;//撒花
}

```

~~让我们一起膜拜最优解也是我的同学 [SUPER_ZJC](https://www.luogu.com.cn/user/556676)~~

---

