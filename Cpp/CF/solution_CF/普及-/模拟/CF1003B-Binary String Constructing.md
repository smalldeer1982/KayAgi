# Binary String Constructing

## 题目描述

给你 $3$ 个整数 $a$ ,$b$ ,$x$ ，让你求出一个包含了 $a$ 个 $0$，$b$ 个 $1$ 的二进制串 $s$。要求其中 $s_i\not =s_{i+1}$ 的对数正好等于 $x$。

## 样例 #1

### 输入

```
2 2 1
```

### 输出

```
1100
```

## 样例 #2

### 输入

```
3 3 3
```

### 输出

```
101100
```

## 样例 #3

### 输入

```
5 3 6
```

### 输出

```
01010100
```

# 题解

## 作者：promise_ (赞：1)

题目给定了三个整数 $a$,$b$,$x$，表示有 $a$ 个 $0$，$b$ 个 $1$，且有 $x$ 对相邻不同的位。

假设我们构造了字符串 $s$，初始化为空字符串。

当 $a>0$ 并且 $b>0$，我们将字符串 $s$ 的末尾拼接 $0$ 或
$1$，然后将 $a$ 或 $b$ 的计数器减去 $1$。

当 $x>0$ 时，我们将当前字符串的最后两个字符拼接相反的位，然后将
 $x$的计数器减去 $1$。
 
重复两个操作，直到所有的计数器都为 $0$。
这种解法能保证 $s_i≠s_{i+1}$。

$s_i=s_{i+1}$ 的对数一定满足 $x$ 的要求。因为我们每次构造字符串的时候，都会在当前字符串的末尾拼接一个相反的位，所以必然满足相邻位不同的要求。另外，每个 $1$ 或 $0$ 都和相邻的位不同。

时间复杂度为 $O(n)$。

---

## 作者：NaOHqwq (赞：1)

## 题意

给你 $3$ 个整数 $a,b,x$，让你求出一个包含了 $a$ 个 `0`，$b$ 个 `1` 的二进制串 $s$。要求其中 $s_i\not =s_{i+1}$ 的对数正好等于 $x$。

二进制串其实就是 `01` 串了，题面简化一下就是要求一个包含 $a$ 个 `1` 和 $b$ 个 `0` 的 `01` 串，并且要让相邻两个字符不相同的对数恰好为 $x$。

## 思路

整体可以分为两种情况，分别为 `0` 比 `1` 多和 `1` 比 `0` 多。

当 `0` 比 `1` 多即 $a>b$ 时，我们需要 $x/2$ 个 `01` 串，即循环 $x/2$ 次。这时，如果 $x$ 为奇数，就要先输出 `0` 再输出 `1`。

当然只有在 `0` 较多时才能先输出 `01`，反之则先输出 `10`。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a, b, x, qwq, qaq;
    cin >> a >> b >> x;
    if(a < b){
		qwq = 1;
		qaq = 0;
		swap(a, b);
    }else{
		qwq = 0;
		qaq = 1;
	}
    for(int i = 1;i <= x/2;i++){
		cout << qwq << qaq;
		a--, b--;
	}
    if(x%2 == 0){
        for(int i = 1;i <= b;i++){
        	cout << qaq;
		}
        for(int i = 1;i <= a;i++){
        	cout << qwq;
		}
    }else{
        for(int i = 1;i <= a;i++){
        	cout << qwq;
		}
        for(int i = 1;i <= b;i++){
        	cout << qaq;
		}
    }
    return 0;
}
```

---

## 作者：qjxqjx (赞：1)

## 题目大意：
给顶一个 01 字串，再给出 1 的个数 a ，和 0 的个数 b ，要求相邻的两个字符不同数为 x ，输出这个字串。

## 思路:

题目主要思路：****找规律****

先判段 1 和 0 的个数更大，再决定是从 a 入手还是从 b 入手。

如果 $a>b$：

那么定义的 x 就至少需要 $x/2$ 个 01 字串。当 x 奇数时，肯定需要 01 后加一个 0 ，我们输出完 0 ，就再输出 1 。这样就可以满足题目中的条件相邻的两个字符不同，因为我们是循环 $x/2$ 次，所以题意条件满足。

当 x 为奇数时，同前，要 01 后加上个 0 ，输出完 0 后，再输出 1 ，达到题目条件。

****注意****：只有当判断结果为 0 较多时才能输出 01 （拥有前导零），否则的话就是 10 了。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,x;
int af,bf;
int main(){
    cin>>a>>b>>x;
    if(a<b){
		af=1;
		bf=0;
		swap(a,b);
    }else{
		af=0;
		bf=1;
	}
    for(int i=1;i<=x/2;i++){
		cout<<af<<bf;
		a--;
		b--;
	}
    if(x%2==0){
        for(int p=1;p<=b;p++){
        	cout<<bf;
		}
        for(int p=1;p<=a;p++){
        	cout<<af;
		}
    }else{
        for(int p=1;p<=a;p++){
        	cout<<af;
		}
        for(int p=1;p<=b;p++){
        	cout<<bf;
		}
    }
    return 0;
}
```
亲测能过......

---

## 作者：y1朵小寒 (赞：1)

此题另外一种思路就是分堆插入法

思路：
先将出现次数最多的数排成一序列Li

将出现次数最少的数分成ceil($\frac{x*1.0}{2}$)堆,

插入得分即可.

e.g

$5 \ 4 \  6$

0出现次数最多，所以把所有0排成一列得：$00000$

1出现次数最少，分堆 $11,1,1$

插入得分 $011010100$



代码如下：
```cpp
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

int a,b,x,neednum,pos;

int main(){

    string str ="" ,sa = "0",sb = "1";
    cin >> a >> b >> x;

        if(a < b){  swap(a,b);  sa = "1",sb = "0";  }

        for(int i = 0 ; i < a ;i++){
            str = sa +str;
        }
        neednum = x/2;
        if(x % 2 != 0) {pos = 0;}
        else{ pos = 1; neednum--;}
        while(b - neednum > 0){
                str.insert(pos,sb);
                pos++,b--;
              }
        pos += 1;

        for(int i = pos, num = 0 ;num < neednum ; num++,i += 2){
            str.insert(i,sb);
        }

    cout << str << endl;
}

```

---

## 作者：ciwomuli (赞：1)

题目大意为构造01串使先后两个字符不同的个数为x个

很明显这题纯模拟

先构造出x-1个间隔，最后再把剩余的写上就行了

两个细节

1：注意x分奇偶讨论

2:a>b与b>a分开讨论，比赛时为此一直WA

上代码

```
#include <iostream>
using namespace std;
int main(){
    int a[2],x,now;
    cin>>a[0]>>a[1]>>x;
    if(a[0]>a[1]){
        if(x%2==0){
            now = 0;
        }else {
            now = 1;
        }
        for (int i=0;i<x;i++){
            cout<<now;
            a[now]--;
            now ^= 1;
        }
        for (int i=0;i<a[1];i++){
            cout << 1;
        }   
        for (int i=0;i<a[0];i++){
            cout << 0;
        }
    }else{
        if(x%2==0){
            now = 1;
        }else {
            now = 0;
        }
        for (int i=0;i<x;i++){
            cout<<now;
            a[now]--;
            now ^= 1;
        }
        for (int i=0;i<a[0];i++){
            cout << 0;
        }   
        for (int i=0;i<a[1];i++){
            cout << 1;
        }
    }
}
```

---

## 作者：GoodLuckCat (赞：0)

## 思路

把它分成两段。前面的应该是 1 和 0 间隔（分 $a<b$ 和 $a\ge b$ 两种情况处理，$a$ 和 $b$ 的大小关系决定了第一个字符是什么），不会有相邻位置上相同的。后面可以直接连续输出 1 或 0，也要分情况讨论：$x$ 为偶数时要先输出 $t2$，否则先输出 $t1$。输出个数由 $a$ 和 $b$ 决定。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a,b,x,t1=0,t2=1;
    cin>>a>>b>>x;
    if(a<b)
    {
        swap(a,b);
        swap(t1,t2);
    }
    for(int i=1;i<=x/2;i++)cout<<t1<<t2;
    a-=x/2;
    b-=x/2;
    if(x%2==0)for(int i=1;i<=b;i++)cout<<t2;
    for(int i=1;i<=a;i++)cout<<t1;
    if(x%2==1)for(int i=1;i<=b;i++)cout<<t2;
}
```

---

## 作者：caotianhao (赞：0)

# 题外话
感觉题解区dalao讲得有点不清楚，所以我来~~水~~写题解
# 题目大意
[传送门](https://www.luogu.com.cn/problem/CF1003B)  
简单来说就是求一个满足以下条件的 $01$ 串：  
1. 其中有 $a$ 个 $0$，$b$ 个 $1$；
2. 相邻两个数不同的对数（一开始cth成功地看成了 $\log$）为 $x$；
# 解题思路
## I
看上去没什么思路啊，先看眼样例：  

样例 $1$：$0$ 个 $10$，$2$ 个 $1$，$2$ 个 $0$；   
样例 $2$：$1$ 个 $10$，$2$ 个 $1$，$2$ 个 $0$；  
样例 $3$：$3$ 个 $01$，$2$ 个 $0$，$0$ 个 $1$；

发现了吗，每个样例输出都是 $n$ 个 $10$（或 $01$），$m$ 个 $1$（或 $0$），$l$ 个 $0$（或 $1$）。也就是说，我们只需要求出 $n$，$m$，$l$，并知道先输出 $01$ 还是 $10$，问题就迎刃而解了。
## II
我们继续推，发现一件事情：只要知道 $n$，那么 $\begin{cases}m=a-n\\l=b-n\end{cases}$ 或 $\begin{cases}m=b-n\\l=a-n\end{cases}$ 。这个结论的正确性显而易见，于是乎，我们的目标转为求 $n$。
## III
我们发现 $n$ 个 $10$（或 $01$）对 $x$ 的贡献为 $2n-1$，而后面 $m$ 个 $1$（或 $0$），$l$ 个 $0$（或 $1$）最多只能给出 $2$ 的贡献，因此 $n$ 应该是 $\lfloor x\div2 \rfloor$ ，接下来我们只要知道先输出 $10$ 还是 $01$，就能切掉这道水题。
## IV
很明显，$a$ 和 $b$ 的大小直接决定了先输出的串，~~（你 $b$ 都比 $a$ 小了还先输出 $10$ 不纯纯找死吗）~~ 所以，我们分为 $a>b$ 和 $a\le b$ 两种情况讨论。
## V
接下来再思考一个问题：输出完一堆 $01$ 或 $10$ 后是先输出 $0$ 还是 $1$。还记得前面说过：  
`后面 m 个 1（或 0），l个0（或1）最多只能给出 2 的贡献。`  
实际上，后面 $m$ 个 $1$（或 $0$），$l$ 个 $0$（或 $1$）只能给出 $1$ 或 $2$ 的贡献，那么我们就需要分类讨论 $x$ 的奇偶 $\begin{cases}x\mod 2=0,&\text{先输出前面 }01\text{ 串中后出现的}\\x\mod 2=1,&\text{先输出前面 }01\text{ 串中先出现的}\end{cases}$
# ACcode
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,x;
int main(){
	cin>>a>>b>>x;
	if(a>b){
		for(int i=1;i<=x/2;i++){
			cout<<"01";
			a--;
			b--;
		}
		if(x%2==0){
			for(int i=1;i<=b;i++){
				cout<<"1";
			}
			for(int i=1;i<=a;i++){
				cout<<"0";
			}
		}else{
			for(int i=1;i<=a;i++){
				cout<<"0";
			}
			for(int i=1;i<=b;i++){
				cout<<"1";
			}
		}	
	}else{
		for(int i=1;i<=x/2;i++){
			cout<<"10";
			a--;
			b--;
		}
		if(x%2==0){
			for(int i=1;i<=a;i++){
				cout<<"0";
			}
			for(int i=1;i<=b;i++){
				cout<<"1";
			}
		}else{
			for(int i=1;i<=b;i++){
				cout<<"1";
			}
			for(int i=1;i<=a;i++){
				cout<<"0";
			}
		}
	}
	return 0;
} 
```

---

## 作者：gaoleng_luogu_name (赞：0)

### 题意
[见题目](https://www.luogu.com.cn/problem/CF1003B)，很好理解。
### 思路
主要分为两种情况讨论。
我们先判断 $1$ 和 $0$ 的数量哪个更多，即 $a$ 和 $b$ 谁更多。
当 $a$ 比 $b$ 多的时候，我们就至少需要 $x \div 2$ 个 $01$ 串。说白了就是循环 $x \div 2$ 次。这是，如果 $x$ 为奇，就要先输出 $0$ 再输出 $1$。

如果 $1$ 比 $0$ 多，同理。
### 代码
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int a,b,x;
int i1=0,i2=1;
int main()
{
	cin>>a>>b>>x;
	if(a<b) swap(i1,i2),swap(a,b);
	for(int i=1;i<=x/2;i++)
	{
		cout<<i1<<i2;
		a--,b--;
	}
	if(x%2==0)
	{
		for(int i=1;i<=b;i++)
		{
			cout<<i2;
		}
		for(int i=1;i<=a;i++)
		{
			cout<<i1;
		}
	}
	else
	{
		for(int i=1;i<=a;i++)
		{
			cout<<i1;
		}
		for(int i=1;i<=b;i++)
		{
			cout<<i2;
		}
	}
	return 0;
}
```
[AC记录](https://codeforces.com/contest/1003/submission/223220301)

---

## 作者：Otue (赞：0)

假如说 $0$ 的数量比 $1$ 多。

那么我们可以假想有一个序列，里面全是 $a$ 个 $0$。此时我们只需要插入 $b$ 个 $1$ 满足题目所述条件。有以下三种情况：

* 将 $1$ 插入到两个 $0$ 中间，例如 `010`，贡献多 $2$。
* 将 $1$ 插入到最后，且前一位是 $0$，例如 `001`，贡献多 $1$。
* 将 $1$ 插入到已有 $1$ 的后面，没有任何贡献。例如由 `0110` 变为 `01110`。

那么我们考虑题目的 $x$，首先把足量的 $1$ 插入到两个 $0$ 之间，使得 $x$ 达到最小。通俗来讲，若 $x$ 为偶数，$x$ 能达到最小值为 $0$。若 $x$ 为奇数，$x$ 能达到最小值为 $1$。

若 $1$ 还有剩余，且 $x$ 为偶数，则将剩余所有 $1$ 放到已有 $1$ 的后面。如果 $x$ 为奇数，则将剩余所有 $1$ 放到最后。

如果 $1$ 的数量比 $0$ 多，同理。

```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 2e5 + 5;

int a, b, x;

signed main() {
	cin >> a >> b >> x;
	if (a >= b) {
		int t = x / 2;
		for (int i = 1; i <= a - t; i++) cout << "0";
		for (int i = 1; i <= t; i++) {
			if (x % 2 == 0 && i == 1) for (int j = 1; j <= b - t; j++) cout << "1"; // 把所有1放到已有1的后面
			cout << "10"; 
		}
		if (x % 2 == 1) for (int j = 1; j <= b - t; j++) cout << "1";
	}
	if (a < b) {
		int t = x / 2;
		for (int i = 1; i <= b - t; i++) cout << "1";
		for (int i = 1; i <= t; i++) {
			if (x % 2 == 0 && i == 1) for (int j = 1; j <= a - t; j++) cout << "0";
			cout << "01"; 
		}
		if (x % 2 == 1) for (int j = 1; j <= a - t; j++) cout << "0";
	}
}
```
洛谷 BOT 能不能别审核题解？

---

## 作者：kdy20100729 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1003B)  
### 题意简述：  
给定一个由字符 ```0``` 和 字符 ```1``` 组成的字符串 $s$，再给出 ```0``` 的个数 $a$ 和 ```1``` 的个数 $b$，要求 $s_i \neq s_{i+1}$ 的对数正好为 $x$，输出这个字符串。  
### 思路：  
先看 ```1``` 和 ```0``` 的个数哪个更多，再去决定是从 $a$ 入手还是从 $b$ 入手。  
如果 $a > b$，那么就至少需要 $x \div 2$ 个 01字符串。当 $x$ 为奇数时，那我们就先输出 ```0``` 再输出 ```1```。  
**注意**：只有当判断结果为 ```0``` 较多时才能输出 ```01``` （拥有前导零），否则就要输出 ```10```。  
### 奉上代码：  
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,x;
char c1='0',c2='1';
int main()
{
	cin >> a >> b >> x;
	if (a<b)
	{
		swap(a,b);
		swap(c1,c2);
	}
	for(int i=1; i<=x; i++)
	{
		if (i%2==1)
		{
			a--;
			cout << c1;
		}
		else
		{
			b--;
			cout << c2;
		}
	}
	if (x%2==1)
	{
		while(a>0)
		{
			cout << c1;
			a--;
		}
		while(b>0)
		{
			cout << c2;
			b--;
		}
	}
	else
	{
		while(b>0)
		{
			cout << c2;
			b--;
		}
		while(a>0)
		{
			cout << c1;
			a--;
		}
	}
	return 0;
}
```

---

