# The Smallest String Concatenation

## 题目描述

给定 $n$ 个字符串，第 $i$ 个字符串为 $a_i$。求出一种依次连接这 $n$ 个字符串的顺序，使连接而成的字符串满足字典序最小。

## 样例 #1

### 输入

```
4
abba
abacaba
bcd
er
```

### 输出

```
abacabaabbabcder
```

## 样例 #2

### 输入

```
5
x
xx
xxa
xxaa
xxaaa
```

### 输出

```
xxaaaxxaaxxaxxx
```

## 样例 #3

### 输入

```
3
c
cb
cba
```

### 输出

```
cbacbc
```

# 题解

## 作者：pokefunc (赞：2)

### 题意

给定一些字符串，求出一种依次连接这些字符串的顺序，使连接而成的字符串满足字典序最小。

### 思路

~~STL大法好！！~~

看了一圈题解都没解释为什么这个`cmp`函数

```cpp
bool cmp(string a,string b){return a+b<b+a;}
```

可以使字典序最小，于是决定发一篇题解解释。

众所周知，`string`类型是可以相加的，其效果是把两个字符串拼在一起。

那么对于`string a,b`，`a+b` 就是把`b`拼到`a`后面。

这句话的意思是：比较是把`b`拼到`a`后面还是把`a`排在`b`后面字典序更小。

考虑三个按上述规则排序的字符串`a,b,c`。

如果把`a`和`b`拼成一个串，显然维持原顺序不变，即`(a+b)+c<c+(a+b)`。

我们用这个比较函数把整个序列排好之后，令此序列为 $s_1,s_2,...,s_n$ ，则 $\forall i \in [1..n),s_i+s_{i+1}<s_{i+1}+s_{i}$。

那么我们得出结论：把此序列的前若干项按顺序拼起来再排序，结果不变。（递推可得）

因此这个方法可以求出题目所求的最小字典序序列。

### Code

```cpp
#include<cstdio>
#include<string>
#include<iostream>
#include<algorithm>
using std::cin;
using std::cout;
using std::string;
inline int read(){int x(0),op(0);char ch=getchar();while(ch<'0'||ch>'9')op|=(ch==45),ch=getchar();while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();return op?-x:x;}
bool cmp(string a,string b){return a+b<b+a;}
string str[50005];
int main(){
    int n=read();
    for(int i=1;i<=n;++i)cin>>str[i];
    std::sort(str+1,str+n+1,cmp);
    for(int i=1;i<=n;++i)cout<<str[i];
    return 0;
}
```



---

## 作者：丧黑福造 (赞：1)

**C++string大法好**

思路：定义string类型的数组，将其排序

$code:$

```cpp

#include<cstring>
#include<iostream>
using namespace std;
string s[50005];
bool cmp(string a,string b) {
	return a+b < b+a;//string类型是可以相加的
    /*例：a='123',b='45';
    a+b='12345';*/
}
main() {
	int n;
	cin >> n;
	for (register int i = 1; i <= n; i ++) cin >> s[i];
	sort (s+1, s+n+1, cmp);//排序
	for (register int i = 1; i <= n; i++) cout << s[i];
	return 0 ;
}

---

## 作者：sandwave114514 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF632C)

题目大意

给定 $n$ 个字符串，求出一种依次连接这 $n$ 个字符串的顺序，使连接而成的字符串满足字典序最小。

解题思路

这道题疑似恶评，非常水，我们只要用 `sort` 把所有字符串按字典序排序，不过我们需要写 `cmp` 函数，由于 `string` 类型可以相加，所以我们把它们相加一下，按字典序排序，输出就可以了。

代码如下


```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
long long read(){
	long long x=0,sgn=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')sgn=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch&15);ch=getchar();}
	return x*sgn;
}//快读 
long long n;
string st[1000010]; 
bool cmp(string x,string y){return x+y<y+x;}//按字典序，让字典序变小，return a+b<b+a; 这句的意思是如果a 的字典序小于b的字典序，就把a放在前面，否则放在后面。这样能让字典序最小。
int main(){
	n=read();
	for(int i=1;i<=n;i++)cin>>st[i];
	sort(st+1,st+n+1,cmp); 
	for(int i=1;i<=n;i++)cout<<st[i];
	return 0;//完结撒花 
}

```


---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF632C)

水，还是绿题。

这道题其实我们只需要把那 $n$ 个字符串按字典序从小到大排序，然后再从第 $1$ 个输出到第 $n$ 个就行了。

# CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string a[50010];
inline bool cmp(string x,string y)
{
	return x+y<y+x;
}
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1,cmp);
	for(register int i=1;i<=n;i++) cout<<a[i];
	return 0;
}
```

---

## 作者：Anonymous__user (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF632C)。

**题目大意** ：给定 $n$ 个字符串，第 $i$ 个字符串为          $a_i$ 。求出一种依次连接这 $n$ 个字符串的顺序，使连接而成的字符串满足字典序最小。

**思路讲解** ：先用  ```string```  类型定义字符串，将这些字符串按字典序进行 ```sort``` 排序。排序完成用字典序顺序输出。

**注意点** ：因为 ```string```  类型是可以相加的，比如 ``` '567' ```  +  ``` '890 '``` =   ```  '567890'  ```   ，所以我们写了一个    ```cmp```   函数帮助排序。

**代码** ：
```c
#include<bits/stdc++.h>
using namespace std;
long long n;
string str[50020];
bool cmp(string u,string v){
	return u+v<v+u;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>str[i];
	sort(str+1,str+n+1,cmp);
	for(int i=1;i<=n;i++)cout<<str[i];
	return 0;
}
```



---

