# Kalindrome Array

## 题目描述

An array $ [b_1, b_2, \ldots, b_m] $ is a palindrome, if $ b_i = b_{m+1-i} $ for each $ i $ from $ 1 $ to $ m $ . Empty array is also a palindrome.

An array is called kalindrome, if the following condition holds:

- It's possible to select some integer $ x $ and delete some of the elements of the array equal to $ x $ , so that the remaining array (after gluing together the remaining parts) is a palindrome.

Note that you don't have to delete all elements equal to $ x $ , and you don't have to delete at least one element equal to $ x $ .

For example :

- $ [1, 2, 1] $ is kalindrome because you can simply not delete a single element.
- $ [3, 1, 2, 3, 1] $ is kalindrome because you can choose $ x = 3 $ and delete both elements equal to $ 3 $ , obtaining array $ [1, 2, 1] $ , which is a palindrome.
- $ [1, 2, 3] $ is not kalindrome.

You are given an array $ [a_1, a_2, \ldots, a_n] $ . Determine if $ a $ is kalindrome or not.

## 说明/提示

In the first test case, array $ [1] $ is already a palindrome, so it's a kalindrome as well.

In the second test case, we can choose $ x = 2 $ , delete the second element, and obtain array $ [1] $ , which is a palindrome.

In the third test case, it's impossible to obtain a palindrome.

In the fourth test case, you can choose $ x = 4 $ and delete the fifth element, obtaining $ [1, 4, 4, 1] $ . You also can choose $ x = 1 $ , delete the first and the fourth elements, and obtain $ [4, 4, 4] $ .

## 样例 #1

### 输入

```
4
1
1
2
1 2
3
1 2 3
5
1 4 4 1 4```

### 输出

```
YES
YES
NO
YES```

# 题解

## 作者：_Starlit__Sky_ (赞：4)

# 洛谷 CF1610B 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1610B)

## 题目算法

for 循环 枚举

## 题目思路

- 若输入的列表本身回文，则输出 `YES` 。
```python
    if raw_lst[::-1] == raw_lst: # 若原始序列本身回文    则输出 'YES'
        print('YES')
        continue
```
- 若输入的列表不回文，则遍历该列表每一个与自己回文位不相同的元素（$b_i ≠ b_{m-i+1}$）然后判断删除该项元素后整个列表是否回文。
```python
flag = False # 删除该项元素后整个列表是否回文
    for i in range(int(length ** 0.5)):
        if lst[i] != lst[length - i - 1]: # 遍历 每一个与回文位不相同的元素
            lst.remove(lst[i]) # 判断删除该元素后整个列表是否回文
            if lst[::-1] == lst: # 如果回文
                print('YES')
                flag = True
                break
            lst = raw_lst.copy() # 回溯
    if not flag: print('NO')
```


## 代码

```python
t = int(input()) # 输入
for i in range(t):
    length = int(input()) # 输入长度
    raw_lst = list(map(int,input().split())) # 输入原始序列
    if raw_lst[::-1] == raw_lst: # 若原始序列本身回文    则输出 'YES'
        print('YES')
        continue
    lst = raw_lst.copy()
    flag = False # 删除该项元素后整个列表是否回文
    for i in range(int(length ** 0.5)):
        if lst[i] != lst[length - i - 1]: # 遍历 每一个与回文位不相同的元素
            lst.remove(lst[i]) # 判断删除该元素后整个列表是否回文
            if lst[::-1] == lst: # 如果回文
                print('YES')
                flag = True
                break
            lst = raw_lst.copy() # 回溯
    if not flag: print('NO')
```


---

## 作者：Implicit (赞：1)

不难发现，长度为 $n$ 的序列 $a$ 是 *回文的*，当且仅当
$$\forall i: a_i=a_{n-i+1}$$

数列本身回文直接输出 `Yes`，若不然：

我们扫一遍判是否有 $a_i=a_{n-i+1}$，如果不满足了，就说明要删数了，此时不需要搞花里胡哨的，直接把 $a_i,a_{n-i+1}$ 拉过去模拟判断就完了 .

呐，就这样
```cpp
using namespace std;
typedef long long ll;
const int N = 1145141;
int T, n, a[N], b[N];
bool isp(int n)
{
	for (int i=1; i<=n; i++)
		if (b[i] != b[n-i+1]) return false;
	return true;
}
bool _(int k)
{
	int r = 0;
	for (int i=1; i<=n; i++)
		if (a[i] != k) b[++r] = a[i];
	return isp(r);
}
int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		for (int i=1; i<=n; i++) scanf("%d", a+i), b[i] = a[i];
		if (isp(n)){puts("Yes"); continue;}
		int lptr = 1, rptr = n, X, Y;
		while (lptr <= rptr)
		{
			if (a[lptr] != a[rptr]){X = a[lptr]; Y = a[rptr]; break;}
			++lptr; --rptr;
		}
		if (_(X) || _(Y)) puts("Yes");
		else puts("No");
	}
	return 0;
}
```

---

## 作者：tder (赞：1)

[$\Large\color{black}\textbf{CF1610b Kalindrome Array}$](https://www.luogu.com.cn/problem/CF1610B) $\Large\textbf{题解}$

[$\textbf{题目传送门}$](https://www.luogu.com.cn/problem/CF1610B)

[$\textbf{更好的阅读体验}$](https://www.luogu.com.cn/blog/tder/solution-cf1610b)

`upd on 2023/10/4 23:03 将思路中提到的 check(x) 函数改为代码块。`

~~小小的模拟~~

---

$$\large\textbf{思路}$$

对于每一个序列 $b$：

- 如果 $b$ 本身回文，则一定为 `YES`。

- 否则如果 $b$ 本身不回文，则遍历序列 $b$，找出第 $1$ 组互为回文位且对应数字不同的下标 $x,y$。分别尝试将序列中的所有 $x,y$ 删除，判断是否回文即可。

注：长度为 $n$ 的下标从 $1$ 开始的序列中，第 $i$ 个数的回文位为 $n-i+1$。

总结起来，所有判断回文的功能可以通过一个函数 `check(x)` 表示将序列中所有值为 $x$ 的数字删除后是否回文。可以不进行删除操作，而是遍历到 $x$ 时跳过即可。

---

$$\large\textbf{代码}$$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int t, n, a[N];
bool check(int x = -1) { // 1 <= ai <= n 所以 x = -1 时即不删
	for(int p = 1, q = n; p < q; p++, q--) { 
		while(a[p] == x && p < q) p++; // 跳过值为 x 的数
		while(a[q] == x && p < q) q--; 
		if(a[p] != a[q]) return 0; // 不回文	
	}
	return 1; // 回文
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>t;
	while(t--) {
		cin>>n;
		for(int i = 1; i <= n; i++) cin>>a[i];
		if(check()) cout<<"YES"<<endl; // 本身回文则直接输入 YES
		else {
			for(int i = 1; i <= n / 2; i++)
				if(a[i] != a[n - i + 1]) { // 第一个不同的数
					if(check(a[i]) || check(a[n - i + 1])) 
						cout<<"YES"<<endl;
					else cout<<"NO"<<endl;
					break;
				}
		}
	} 
	return 0;
}
```

---

## 作者：Terraria (赞：1)

## $\text{Introduction}$

给定一个长度为 $n$ 的数列，如果这个数列满足：

- 本身就是回文数列；

- 删去一个特定的数字后成为回文数列。

二者之一，则称这个数列是「可爱的」。

现在求这个数列是否可爱。

## $\text{Solution}$

判断一个数列是否为回文数列，我们只需要双指针从左、右分别开始扫描一位一位比较即可。

那么，我们先对数列进行扫描，则扫描结果可能为

- 数列本身就是一个回文数列。

那么我们可以直接输出 `YES`；

- 第一次扫到了 $a_l \neq a_r$。

考虑到我们要求删去一个数后就成为回文数列，那么如果不删去这个两个数中的其中一个数，那么这个数列一定不会是回文数列。

所以，如果这个可爱的数列是由删去数得到的，那么一定是删去 $a_l$ 或者 $a_r$ 之间的一个数。

删去哪个数呢？不知道没关系，都试一下就好了：两个数分别删去，将得到的新数列判断是否为回文数列，如果其中有一种情况是回文数列则输出 `YES`，否则输出 `NO`。

## $\text{Code}$

~~有点长，但是易懂。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int a[200009];
int b[200009],cnt1;//存放删去a[l]后的数列
int c[200009],cnt2;//存放删去a[r]后的数列
void solve(){
	cnt1=cnt2=0;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	int l=1,r=n;
	while(l<=r){
		if(a[l]!=a[r]) break;
		l++;
		r--;
	}
	if(l>=r){//l>=r则说明这个数列已经是回文数列了
		cout<<"YES"<<endl;
		return;
	}
	for(int i=1;i<=n;i++){//存放删去a[l]后的数列
		if(a[i]!=a[l]) b[++cnt1]=a[i];
	}
	for(int i=1;i<=n;i++){//存放删去a[r]后的数列
		if(a[i]!=a[r]) c[++cnt2]=a[i];
	}
    //两种情况一一判断
	l=1,r=cnt1;
	while(l<=r){
		if(b[l]!=b[r]) break;
		l++;
		r--;
	}
	if(l>=r){
		cout<<"YES"<<endl;
		return;
	}
	l=1,r=cnt2;
	while(l<=r){
		if(c[l]!=c[r]) break;
		l++;
		r--;
	}
	if(l>=r){
		cout<<"YES"<<endl;
		return;
	}
	cout<<"NO"<<endl;
	return;
}
int main(){
	cin>>t;
	while(t--) solve();
}
```


---

## 作者：yhx0322 (赞：0)

## 题目简述
给你一个数列 $a$，有这两种情况，这个数列是「可爱的」。
- 它本身就是回文的。
- 定义变量 $x$，满足：序列 $a$ 中所有值等于 $x$ 的元素删除之后，它是回文的。

## 思路
首先考虑暴力。暴力枚举数组中的每一个数，当作变量 $x$，然后进行回文检验。

时间复杂度 $O(n^2)$，严重超时。

然后考虑如何优化。

根据回文判断的方法，我们很容易想到：**双指针的优化。**

设变量 $l$ 和 $r$，初始值分别为 $1$ 和 $n$。如果扫描到 `a[l] != a[r]` 的情况，用两个变量记录一下它们的值，然后停止循环。


然后删除 $a$ 数组中值为 $a_l$ 或者是 $a_r$ 的数字，看看删除之后是否满足回文的条件。

## 代码
```c++
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;
int t, n, a[N], tmp[N];

bool ishuiwen(int n, int b[]) { // 是否是回文
	for (int i = 1; i <= n; i++) {
		if (b[i] != b[n - i + 1]) return false;
	}
	return true;
}

bool check(int x) { // 检验删除值为x的情况下是否满足回文
	int idx = 0;
	for (int i = 1; i <= n; i++) {
		if (a[i] != x) tmp[++idx] = a[i];
	}
	return ishuiwen(idx, tmp);
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		if (ishuiwen(n, a)) { // 本身就满足条件
			printf("YES\n");
			continue;
		}
		int l = 1, r = n, x, y;
		while (l <= r) {
			if (a[l] != a[r]) { // 不满足，删数字
				x = a[l], y = a[r];
				break;
			} else l++, r--;
		}
		if (check(x) || check(y)) printf("YES\n"); // 只要一个满足条件就可以
		else printf("NO\n");
	}
	return 0;
}
```

---

## 作者：ACtheQ (赞：0)

### 思路

不难发现，有个暴力的做法枚举每个数当 $x$ 的情况，和 $x = \infty$。

这种算法复杂度 $O(n^2)$。

显然是不行滴！

正解，很简单。

我们定义两个变量。

$i$ 从 $1$ 开始，$j$ 从 $n$ 开始。

分别代表左端点和右端点。

如果两个数不一样则退出循环。

那么考虑删除 $a_i$ 或 $a_j$。

最后判断是否为回文串就行！

判断回文串代码：

```c++
int check(int x)
{
	int i=1;
	int j=n;
    while(true) 
	{
		if(i>j) return true;
		if(a[i]==x)
		{
			i++;
			continue;
		}
		if(a[j]==x)
		{
			j--;
			continue;
		}
		if(a[i]==a[j])
		{
			i++;
			j--;
			continue;
		}
		return false;
	}
	return false;
}
```

寻找要删除的数的代码：

```c++
int i=1;
int j=n;
while(i<=j) 
{
	if(a[i]!=a[j]) break;
	i++;
	j--;
 }
 if(i>j) cout<<"YES"<<endl;
else if(check(a[i])||check(a[j])) cout<<"YES"<<endl;
else cout<<"NO"<<endl;
 ```

---

## 作者：expecto__patronum (赞：0)

## 题目大意：
以回文顺序遍历整个序列，可以删除不对称的元素，但只能删一种元素的任意个，问能不能删除一种元素的任意个使序列变成回文序列.

## 思路：
以回文顺序遍历序列的时候，不对称的元素必然成对出现，所以只需枚举一下这两个元素即可，具体细节见代码。

Code：
```
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 2e5+10;
int a[N];
int n;
bool check(int x)
{
    int i=0,j=n-1;
    bool ok=true;
    while(i<=j&&ok)
    {
        ok=false;
        if(a[i]==x) i++,ok=true;
        if(a[j]==x) j--,ok=true;
        if(a[i]==a[j]) i++,j--,ok=true;
    }
    if(i>j) return true;
    return false;
}
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        cin>>n;
        for(int i=0;i<n;i++) cin>>a[i];
        
        int i=0,j=n-1;
        while(a[i]==a[j]&&i<=j) i++,j--;
        
        if(i>j) {puts("YES");continue;}
        
        if(check(a[i])||check(a[j])) puts("YES");
        else
        puts("NO");
    }
    return 0;
}
```


---

## 作者：filletoto (赞：0)

## 思路
先判断长度为 $m$ 的序列 $b$ 是否是回文的，可以用双指针的方法。

具体方法是定义变量 $l$ 和 $r$，初始化 $l=1$ 和 $r=m$，在循环 `while(l<=r)` 将 $l+1$ 并且 $r-1$，判断 $b_l$ 是否与 $b_r$ 相等。如果不相等，直接将 $flag$ 设为 $0$，退出循环。

如果 $flag=1$，则序列回文，输出 `YES`。
否则分别尝试将 $b_l$ 和 $b_r$ 删除，用双指针判断删除后的序列是否回文。

## 代码
~~~cpp
#include <iostream>
using namespace std;
#define MAXN 200005
//快读优化
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-f;
		ch=getchar();
	}	
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
int T,a[MAXN],b[MAXN],c[MAXN],n;
int main()
{
	ios::sync_with_stdio(false);
	T=read();
	while(T--)
	{
		n=read();
		for(int i=1;i<=n;i++)
		{
			a[i]=read();
		}
		int l=1,r=n;
		int flag=1;
		while(l<=r)
		{
			if(a[l]!=a[r]) {flag=0;break;}
			l++;
			r--;
		}
		if(flag) 
		{
			puts("YES");
			continue;
		}
		int n1=0,n2=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]!=a[l]) n1++,b[n1]=a[i];
		}
		for(int i=1;i<=n;i++) 
		{
			if(a[i]!=a[r]) n2++,c[n2]=a[i];
		}
		l=1;
		r=n1;
		flag=1;
		while(l<=r)
		{
			if(b[l]!=b[r]) {flag=0;break;}
			l++;
			r--;
		}
		if(flag) 
		{
			puts("YES");
			continue;
		}
		l=1;
		r=n2;
		flag=1;
		while(l<=r)
		{
			if(c[l]!=c[r]) {flag=0;break;}
			l++;
			r--;
		}
		if(flag) 
		{
			puts("YES");
			continue;
		}
		puts("NO");
	}



	return 0;
}
~~~

---

## 作者：SoyTony (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1610B)

[前排广告](https://www.luogu.com.cn/blog/Tony-ZhuJialiang/#)

# 题意
判断一个串 $S$ 是否满足如下条件中的一个

- $S$ 本身是回文串
- $S$ 在删去**一种**任意数量的字符后是回文串

# 思路
判断回文串的方法非常简单循环即可，那么有一个结论：从外到内遍历时，第一个不满足回文串的字符是要求修改的字符。

给出证明：考虑把 $S$ 分为三份 $[1,l-1],[l,r],[r+1,n]$，根据题意得到 $[1,l-1]$ 与 $[r+1,n]$ 满足一一对应的回文关系且 $S[l]\neq S[r]$那么如果不修改 $S[l]$ 或 $S[r]$ 的话，将 $S[l+1,r-1]$ 部分为回文串，那么当且仅当同时删除 $S[l]$ 和 $S[r]$ 时，才满足条件，而这与 $S[l]\neq S[r]$ 相矛盾。

那么既然删除 $S[l]$ 或 $S[r]$，又该删除多少？

其实全部删除与删除部分在正确性是等价的，原因如下：

考虑保留的字符在 $S[l,r]$ 中一定是一一对应的，全部删去没有影响，而如果恰好在正中央位置，删去也没有影响，所以如果序列合法，全部删去一定是合法的。

# 代码
有了以上的思路代码就很好实现了，只需要记录下要删除的，并在判断时跳过即可。
```cpp
inline bool check(int pos){
    int l=1,r=n;
    while(l<=n&&r>=1){
        while(a[l]==a[pos]&&l<=n){
            l++;
        }
        while(a[r]==a[pos]&&r>=1){
            r--;
        }
        if(l>n||r<1) return true;
        if(a[l]!=a[r]) return false;
        l++,r--;
    }
    return true;
}
int main(){
    t=read();
    while(t--){
        n=read();
        for(int i=1;i<=n;i++){
            a[i]=read();
        }
        a[0]=a[n+1]=0;
        int difmark=0;
        for(int i=1;i<=n;i++){
            if(a[i]!=a[n-i+1]){
                difmark=i;
            }
        }
        if(!difmark) printf("YES\n");
        else{
            if(check(difmark)) printf("YES\n");
            else if(check(n-difmark+1)) printf("YES\n");
            else printf("NO\n");
        }
    }
    return 0;
}
```

---

## 作者：XL4453 (赞：0)

### 解题思路：

由于这个被删的数只有一个，那么不妨先找出这个可能的被删的数，然后删去判断回文。

考虑直接对整个串进行回文匹配，一旦出现不合法，那么可能的删数选择一定在这个不合法的数对中，否则若删除其他的数，这一对一定不满足（显然这两个数还是配对的）。

虽然题目中说可以不删去，但是显而易见，若存在一种不完全的删数方法，那么所有的数全都删掉也一定是可以的，这样就可以简化判断了。

总复杂度 $O(n)$。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
int T,n,a[200005];
bool check(int num){
	int now1=1,now2=n;
	while(now1<=n&&now2>=1){
		while(a[now1]==num&&now1<=n)now1++;
		while(a[now2]==num&&now2>=1)now2--;
		if(now1>n||now2<1)return 1;
		if(a[now1]!=a[now2])return 0;
		now1++;now2--;
	}
	return 1;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=0;i<=n+1;i++)a[i]=0;
		for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
		int del1=-1,del2=-1;
		for(int i=1;i<=n;i++){
			if(a[i]!=a[n-i+1]){
				del1=a[i];
				del2=a[n-i+1];
				break;
			}
		}
		if(check(del1)||check(del2))printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

---

## 作者：include_BM (赞：0)

题意：

给定一个长度为 $n$ 的数列 $\{a_i\}$，询问是否可以通过删除数列中某一些相等的数（可以不删），使得数列构成一个回文串。

从左往右找到第一个 $a_i\not=a_{n+i-1}$，例如：

```text
1 2 3 4 3 2 2 1
    ^     ^
```

若要构成回文串，这两个数必须相等，则这两个位置必须删去一个，而其他位上不相等的数可能通过这两个数的删除变得合法，例如上面的序列删除 2 后变为：

```text
1 3 4 3 1
```

分别删去这两个数，判断得到的数列是否回文即可。

```cpp
for(int T=read();T;--T){
	n=read();
	for(int i=1;i<=n;++i) a[i]=read();
	for(l=1,r=n;l<=r&&a[l]==a[r];++l,--r);
	if(l>r){puts("YES");continue;}//不删也是回文串
	
	cnt=0;
	for(int i=1;i<=n;++i) if(a[i]!=a[l]) b[++cnt]=a[i];
	for(ll=1,rr=cnt;ll<=rr&&b[ll]==b[rr];++ll,--rr);
	if(ll>rr){puts("YES");continue;}//删了左边的数后是回文串
	
	cnt=0;
	for(int i=1;i<=n;++i) if(a[i]!=a[r]) b[++cnt]=a[i];
	for(ll=1,rr=cnt;ll<=rr&&b[ll]==b[rr];++ll,--rr);
	if(ll>rr){puts("YES");continue;}//删了右边的数后是回文串
	
	puts("NO");
}
```

---

## 作者：ArrogHie (赞：0)

### 结论
从两端开始同时向内扫描，第一次扫描到的两个不相同的数，删除的数一定是这两个数其中一个，分别判断即可



------------


假设下标 ( 从 $1$ 开始 ) 为 $i,j$ 的两个数不同，而且对于任意 $k < i$ 一定满足 $a_k=a_{n-k+1}$ ，即 $a_i,a_j$ 是不相同的一对数中最外面的一对，则删除能使数列满足条件的数一定是 $a_i$ 或者 $a_j$ 。

因为若删除 $a_i$ ，对于任意 $k<i,a_k=a_i$ 虽然也被删除，但 $a_{n-k+1}$ 也会被删除。即对于任意 $k<i$ ， $a_k$ 所对应的数 $a_{n-k+1}$ 是没有改变的，所以删除 $a_i$ 不会使 $a_i,a_j$ 外面是否是回文状态产生变化。同样的，若删除的数不是 $a_i$ 或 $a_j$ 则 $a_i$ 与 $a_j$ 的对应状态不会发生变化，即数列不可能回文。所以只需要分别判断删除这两个数能否使数列变回文，若都不能则数列不可能变为回文

---

