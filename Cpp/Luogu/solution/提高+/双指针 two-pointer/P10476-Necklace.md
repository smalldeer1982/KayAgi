# Necklace

## 题目描述

有一天，袁同学绵了一条价值连城宝石项链，但是，一个严重的问题是，他竟然忘记了项链的主人是谁！在得知此事后，很多人向同学发来了很多邮件，都说项链是自己的，要求他归还（显然其中最多只有一个人说了真话）。袁同学要求每个人都写了一段关于自己项链的描述：

项链上的宝石用数字 $0$ 至 $9$ 来表示。一个对于项链的表示就是从项链的某个宝石开始：顺指针绕一圈，沿途记下经过的宝石，比如如下项链：

![](https://cdn.luogu.com.cn/upload/image_hosting/57501u19.png)

它的可能的四种表示是 $0123$、$1230$、$2301$、$3012$。

袁同学现在心急如焚，于是他找到了你，希望你能够编一个程序，判断两个给定的描述是否代表同一个项链（注意，项链是不会翻转的）。

## 说明/提示

设 $L =$ 项链长度，则 $1\leq L \leq 1000000$。

## 样例 #1

### 输入

```
2234342423 
2423223434```

### 输出

```
Yes
2234342423```

# 题解

## 作者：CSPAK_Zhangxiuqi0011 (赞：9)

**前言**  
这道题其实是老师上课的时候讲的思路。过了一百万个世纪以后由于我还是太垃圾了，还是觉得本题思路不太好理解，所以赶来写了个题解，可能图画的不怎么好，讲解可能也没这么清楚，请谅解。  


------------
**题目大意**  
给定两个字符串，判断两个字符串是否同构，如果是就输出字符串的最小表示法。

-------
**做法详解**  
首先，我们确定了本题其实就是**字符串的同构问题**。那么什么叫做同构呢？通俗易懂的说就是像题目中说的那样，**把一个字符串顺时针（当然逆时针也可以）写到环上面，则无论从哪一个地方断开按照原顺序读，这两个字符串在按照同一顺序写在环上面以后是一样的**。具体见下图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/o7cfhw94.png)  
那么反过来，**如果两个字符串按照顺时针填到两个环上面，这两个环经过旋转后相同，那么就说这两个字符串同构**。   
那么，我们就可以得出一种做法：先将其中一个字符串破环为链（就是将原字符串在后面复制一遍，这样可以做到以每一个点为起点往后扫描的字符串都可以在这个字符串中顺序找到）再事先开一个存储答案的字符串存储最小的字典序字符串，接着枚举刚才破环为链的字符串的所有表示方法。如果其中一个表示法和另一个字符串相等，就输出刚才的答案字符串。可是显然，设原字符串长度是 $L$，则**这种方法的时间复杂度是 $O(L ^ 2)$ 级别的，在 $1 \le L \le 10 ^ 6$ 的情况下会超时**。所以我们需要找更优的方法。  
那么我们可以想一想：如果两个字符串同构，他们不管怎么表示，一定有一个什么东西是相同的呢？没错，就是**最小表示法**。顾名思义，就是**在这个字符串所有表示法中字典序最小的那一个**。那么这个问题就瞬间转化成了一个求字符串的最小表示法的问题。  
现在问题就在于怎么求了。~~暴力枚举是个不错的选择~~我们显然不能暴力枚举，那么这时候就要用到双指针了。具体操作如下:  
1. 我们需要两个指针，在操作中需要保证其中的一个指针是目前扫描到所有字符串中最小的，我们把它称为答案指针。  
2. 将一个指针赋成 $1$，另一个赋成 $2$。  
3. 进入循环，每一次向后截取，如果当前两个位置相同，则继续，否则跳出。注意：这里最多取 $L$ 个位置。
4. 对于每一次截取完成之后，如果此时当前非答案指针所代表的字符串更优，交换答案指针和非答案指针，否则不交换。然后将非答案指针设成刚才更劣字符串扫到最后一个位置的后面一个位置。为什么呢？我们看这个例子：  
![](https://cdn.luogu.com.cn/upload/image_hosting/ce7qhyb9.png)  
我们假设答案指针 $i$ 指在前面，非答案指针 $j$ 指在后面，现在扫的字符串长度 $k = 5$，那么对于每一个字符串的开始位置 $j+h(0 \le h < k)$，都肯定能会有 $i+h$，使得以 $i+h$ 作为开始位置的字符串比以 $j+h$ 作为开始位置的字符串更优。例如图中当 $h = 2$ 时就是如此。故可以直接将 $j$ 挪到 $j+k$ 的位置（注意字符串长度是 $k$，实际上最后一个位置是 $j+k-1$ 哦）。  
5. 出循环之后，最小表示法字符串即是从答案指针开始向后取一个长度为 $L$ 的字符串。  
我们可以分析一下这种做法的时间复杂度，因为指针不可能回退，所以时间复杂度是 $O(L)$ 级别的。
---------
**代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define INT_MAX LONG_LONG_MAX
#define INT_MIN LONG_LONG_MIN
string a,b,ansa,ansb;
int n;
string minstring(string s) {
	int i,k;
	i = 1;
	for(int j = 2; i<=n && j<=n;) { //不是i(j)<=2*n，因为要给后面留n个空间截取字符串
		int k;
		for(k = 0; k<n && s[i+k] == s[j+k]; k++); //向后找
		if(s[i+k]>s[j+k]) {
			swap(i,j);
		}
		j = j+k+1;
		if(i == j) {
			j++;
		}
	}
	return s.substr(i,n);//意思是从i开始向后截取，取一个长度为n的字符串 
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>a>>b;
	n = a.size();
	a = " "+a+a;
	b = " "+b+b;
	ansa = minstring(a);
	ansb = minstring(b);
	if(ansa == ansb) {
		cout<<"Yes\n"<<ansa;
	} else {
		cout<<"No";
	}
	cout<<"\n";
	return 0;
}
```

---

## 作者：Officer (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/P10476)

# 前置芝士

[最小表示法](https://blog.csdn.net/tianyuhang123/article/details/54919715)

# 正文

好，我们来看一下题，这题很明显要先用两个第一串拼起来，也就是破环为链，再从中找第二串，找到了则输出 Yes 和字典序最小的表示，反之输出 No。

看一下代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b,c,d;
string ind(string s)
{
	int l=1,r=2,n=s.size();
	s=" "+s+s;
	while(r<=n)
	{
		int k=0;
		while(k<n&&s[k+l]==s[k+r])
		{
			k++;
		}
		if(k==n)
		{
			break;
		}
		if(s[k+l]>s[k+r])
		{
			l+=k+1;
		}
		else
		{
			r+=k+1;
		}
		if(l==r)
		{
			r++;
		}
		if(l>r)
		{
			swap(l,r);
		}
	}
	return s.substr(l,n);
}
int main()
{
	cin>>a>>b;
	c=ind(a);
	d=ind(b);
	if(c!=d)
	{
		cout<<"No\n";
	}
	else
	{
		cout<<"Yes"<<endl<<c<<endl;
	}
 	return 0;
}
/*
*/
```

---

## 作者：xiaoyunhao (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P10476)
# 题目大意
[求最小表示法](https://blog.csdn.net/m0_61409183/article/details/127490185)
# 正文
我们可以先把两个字符串破环为链，也就是分别把两个字符串的末尾再加上相同的字符串，再求出最小表示法，如果两个字符串的最小表示法相同，输出 Yes，否则输出 No。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b,c,d;
int main() {
	getline(cin,a);
	getline(cin,b);
	int len=a.size();
	a="#"+a+a;
	int l=1,r=2,k;
	while(r<=len){
		k=0;
		while(k<len&&a[l+k]==a[r+k])k++;
		if(k==len){
			break;
		}
		if(a[l+k]>a[r+k]) l+=k+1;
		else r+=k+1;
		if(l==r) r++;
		else if(l>r) swap(l,r);
	}
	c=a.substr(l,len);
	len=b.size();
	b="#"+b+b;
	l=1;r=2;k=0;
	while(r<=len){
		k=0;
		while(k<len&&b[l+k]==b[r+k])k++;
		if(k==len){
			break;
		}
		if(b[l+k]>b[r+k]) l+=k+1;
		else r+=k+1;
		if(l==r) r++;
		else if(l>r) swap(l,r);
	}
	d=b.substr(l,len);
	if(c==d){
		cout<<"Yes"<<endl;
		cout<<c;
	}else{
		cout<<"No";
	}
	return 0;
}

```

---

## 作者：Charles_with_wkc (赞：4)

## 前言：
这道题描述很长，其实很简单，考察我们两个知识点分别是，字符串中的**同构**和**双指针**法。
### 字符串中的同构：
求同构字符串的方法，其实很简单。我们可以想象成一个圆圈，**不停寻找开头**，就形成了 $ n $ 个**同构串** $ n $ 这里表示字符串的长度。我们同时也可以换一种想法，用字符串的**拼接**来完成。

### 双指针：
这道题目其实很明显是**同向**的 $ i $ 和 $ j $ 指针。这道题目不难从求**最小表示法**中看出 $ i $ 和 $ j $ 指针同向。这里还有两个注意点 $ i $ 和 $ j $ 的位置不可以相同和 $ j $ 一定要在 $ i $ 的后面。这里我们要特判一下找完了，就要跳出循环。

### 核心代码：
```cpp
int l=s.size();
s=" "+s+s;//下表1开始，方便计算
int i=1,j=2;
while(j<=l){
	int k=0;
	while(k<l&&s[i+k]==s[j+k]){
		k++;
	}
	if(k==l){
		break;
	}
	if(s[i+k]>s[j+k]){
		i+=k+1;
	}
	else{
		j+=k+1;
	}//如果是s[i+k]>s[j+k]我们就把i划到i+k+1的位置，否则将j划到j+k+1的位置
	if(i==j){
		j++;
	}
	if(i>j){
		swap(i,j);
	}
}
return s.substr(i,l);
```

---

## 作者：Shq_likes_AC (赞：3)

## [背景知识：最小表示法](https://oi-wiki.org/string/minimal-string/)
对两个字符串破环成链，比较它们的最小表示法，相同输出 `Yes`，否则输出 `No`。
```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b,ans;
string fun (string a)
{
	int n=a.size(),i=0,j=1,k=0;
	a+=a;
	while(j-i+1<=n&&j<a.size())
	{
		k=0;
		while(a[i+k]==a[j+k]) k++;
		if(k==n)
			break;
		if(a[i+k]>a[j+k])
			i+=k+1;
		else
			j+=k+1;
		if(i==j)
			j++;
		if(i>j)
			swap(i,j);
	}
	return a.substr(i,n);
}
int main()
{
	cin>>a>>b;
	ans=fun(a);
	if(fun(b)==ans)
		cout<<"Yes\n"<<ans;
	else
		cout<<"No"; 
}
``````

---

## 作者：MoonCake2011 (赞：3)

乱跑两次最小表示法。

$O(n)$ 较小常数水过。

首先，我们想到，将两个字符串变为循环同构串字典序最小的。

但这样是 $O(n^2)$ 的，过不了。

首先，断环为链。

复制一倍在后面。

继续，选择优化暴力。

现在对比分别以 $i,j$ 为开头的循环同构串比较。

如果 $[i,i+k-1],[j,j+k-1]$ 一样的话。

$i+k$ 与 $j+k$ 比较，$i+k$ 更小的话。

按暴力算法，会 `j++`，把 $i$ 当为 $ans$，然后继续比较。

但是，我会 `j+=k+1`，再去比较。

因为，对于 $[j,j+k]$ 开头的循环同构串，有更小的串 $[i,i+k]$ 在等着，故不用比较。

$i+k$ 与 $j+k$ 比较，$j+k$ 更小的话。

交换 $i,j$。

如果这样，使 $i=j$ 的话，说明以 $i$ 来匹配，匹配完了。

所以 `j++`。

初值是 $i=1,j=2$。

最后 $\min(i,j)$ 为最优答案。

因为每次比较遍历 $k$ 次，而排除了 $k$ 个状态。

两个指针一共遍历 $2n$ 次。

故时间复杂度 $O(n)$，剩余很简单了吧。

先把 P1368 切了吧。

代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[2000010],b[2000010];
vector<int>p,q;
int main() {
	char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) a[++n]=ch-'0',ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) b[++m]=ch-'0',ch=getchar();
	for(int i=1;i<=n;i++) a[i+n]=a[i];
	for(int i=1;i<=n;i++) b[i+n]=b[i];
	int i=1,j=2,k=0;
	while(i<=n && j<=n){
		for(k=0;k<n && a[i+k]==a[j+k];k++);
		if(k==n) break;
		if(a[i+k]>a[j+k]){
			i+=k+1;
			if(i==j) i++;
		}
		else{
			j+=k+1;
			if(i==j) j++;
		}
	}
	for(int k=min(i,j),u=1;u<=n;u++,k++) p.push_back(a[k]);
	i=1,j=2,k=0;
	while(i<=n && j<=n){
		for(k=0;k<n && b[i+k]==b[j+k];k++);
		if(k==n) break;
		if(b[i+k]>b[j+k]){
			i+=k+1;
			if(i==j) i++;
		}
		else{
			j+=k+1;
			if(i==j) j++;
		}
	}
	for(int k=min(i,j),u=1;u<=n;u++,k++) q.push_back(b[k]);
	if(p==q){
		cout<<"Yes\n";
		for(int k=min(i,j),u=1;u<=n;u++,k++) cout<<b[k];
	}
	else cout<<"No\n";
	return 0;
}
```

---

## 作者：Tonymcmcmc (赞：2)

# 前言
~~本蒟蒻的第一篇题解，求过~~

[题目传送门](https://www.luogu.com.cn/problem/P10476)
# 正文
这一题考察两个知识点——循环同构、双指针。
### 循环同构
设想一下，把一个字符串里的每个字符展开，围成一个圆。那么从任意一个点开始，以同样的方向读取，得到的字符串与原字符串“循环同构”。

而代码中的 ```getmin()``` 函数，则是循环同构+字典序最小查找。
### 双指针
具体可以看看代码中的 $i,j$。
# 代码
### 核心代码
```c++
string getmin(string s){
	int n=(int)s.size();
	s="#"+s+s;//"#"是特殊标记符，不用管它
	int i=1,j=2;
	while(j<=n){
		int k=0;
		while(k<n&&s[i+k]==s[j+k])k++;
		if(s[i+k]>s[j+k])i+=k+1;
		else j+=k+1;
		if(i==j)j++;
		if(i>j)swap(i,j);
   		//同向指针，保证j>i
	}
	return s.substr(i,n);
}
```
### 完整代码
```c++
#include <bits/stdc++.h>
using namespace std;
string getmin(string s){
	int n=(int)s.size();
	s="#"+s+s;
	int i=1,j=2;
	while(j<=n){
		int k=0;
		while(k<n&&s[i+k]==s[j+k])k++;
		if(s[i+k]>s[j+k])i+=k+1;
		else j+=k+1;
		if(i==j)j++;
		if(i>j)swap(i,j);
	}
	return s.substr(i,n);
}
int main(){
  	//简单的主函数
	string a,b,da,db;
	cin>>a>>b;
	da=getmin(a);
	db=getmin(b);
	if(da!=db)cout<<"No"<<endl;
	else cout<<"Yes\n"<<da<<endl;
	return 0;
}
```
==========END==========

---

## 作者：Jorisy (赞：0)

最小表示法板子。

对一个字符串求最小表示时用 $i,j$ 表示两个指针来进行向后的暴力匹配。遇到不同的则字典序更大的以及其后面的都不可能作为最小表示。然后跳指针继续暴力匹配即可。

至于 $s,t$ 是否循环同构我们只要分别求出最小表示比较是否相等即可。
```cpp
#include<bits/stdc++.h>
using namespace std;

int minshow(string s,int n)
{
	int i=0,j=1,k=0;
	while(i<n&&j<n&&k<n)
	{
		while(s[(i+k)%n]==s[(j+k)%n]) k++;
		if(s[(i+k)%n]>s[(j+k)%n]) i+=k+1;
		else j+=k+1;
		if(i==j) i++;
		k=0; 
	}
	return min(i,j);
}

int main()
{
	string s,t; 
	int n;
	cin>>s>>t;
	n=s.size();
	int x=minshow(s,n),y=minshow(t,n);
	string p=s.substr(x)+s.substr(0,x),q=t.substr(y)+t.substr(0,y);
	if(p==q)
	{
		puts("Yes");
		cout<<p;
	}
	else puts("No");
	return 0;
}
```

---

## 作者：xiao7_Mr_10_ (赞：0)

好的如你所见，这道题为循环同构算法。

具体的，找到两个字典序最小循环同构串，判断下一不一样就行了。

$O(n^2)$ 非常~~优秀~~。

考虑使用双指针进行优化，先断环为链基操一波，然后考虑维护双指针 $i , j$ 的循环同构串。然后维护一个值 $k$，当然没有必要一个一个加，一次加上 $k+1$ 即可，这样均摊下来复杂度为 $O(n)$。

```cpp
string work(string x){
	n=x.size();
	x=" "+x+x;
	int l = 1,r = 2;
	while(r<=n){
		int tlh = 0;//tlh,他_了 
		while(tlh<n&&x[l+tlh]==x[r+tlh])tlh++;
		if(x[l+tlh]>x[r+tlh])l+=tlh+1;
		else r+=tlh+1;
		if(l==r)r++;
		if(l>r)swap(l,r);
	}
	return x.substr(l,n);
}
```

---

