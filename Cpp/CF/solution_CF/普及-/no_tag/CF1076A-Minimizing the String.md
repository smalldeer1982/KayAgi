# Minimizing the String

## 题目描述

You are given a string $ s $ consisting of $ n $ lowercase Latin letters.

You have to remove at most one (i.e. zero or one) character of this string in such a way that the string you obtain will be lexicographically smallest among all strings that can be obtained using this operation.

String $ s = s_1 s_2 \dots s_n $ is lexicographically smaller than string $ t = t_1 t_2 \dots t_m $ if $ n < m $ and $ s_1 = t_1, s_2 = t_2, \dots, s_n = t_n $ or there exists a number $ p $ such that $ p \le n $ and $ s_1 = t_1, s_2 = t_2, \dots, s_{p-1} = t_{p-1} $ and $ s_p < t_p $ .

For example, "aaa" is smaller than "aaaa", "abb" is smaller than "abc", "pqr" is smaller than "z".

## 说明/提示

In the first example you can remove any character of $ s $ to obtain the string "aa".

In the second example "abca" < "abcd" < "abcda" < "abda" < "acda" < "bcda".

## 样例 #1

### 输入

```
3
aaa
```

### 输出

```
aa
```

## 样例 #2

### 输入

```
5
abcda
```

### 输出

```
abca
```

# 题解

## 作者：Dream_weavers (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1076A)

## 题意

有一个长度为 $n$ 的字符串 $s$，求该字符串在删除 $1$ 个字符后的**最小字典序**。

## 思路

这是一道经典的贪心题。

此题与[P8082](https://www.luogu.com.cn/problem/P808)比较相似（[附我P8082题解](https://www.luogu.com.cn/blog/572482/solution-p8082)）。

### 分析

为了让字符串字典序最小，就要让**尽量小**的字母排在前面，最先删除**靠前并较大**的字母。

比如字符串 $s$ 为 `abcabc`。若删除第一个 `c`，则变成 `ababc`；若删除第二个 `c`，则变成 `abcab`。很明显可以看出 `ababc` 更小。

在代码中，我们建立一个数组或 stl 容器，边输入边判断：若 $s_{i-1}>s_i$，则删除 $s_{i-1}$，插入 $s_i$，并标记不让以后再删除字母。最后输出整个数组或容器。

时间复杂度 $O(n)$。

### 注意

如果最后没有字母被删除（比如 `abcde`，出现**不下降**字符串），就删除末尾的字母。

## 代码

我这里用的是 stl 的 vector。

```cpp
#include<iostream>
#include<vector>
using namespace std;
vector <char> v;
char ch;
int n,tmp;
int main(){
    ios::sync_with_stdio(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>ch;//输入字母
        if(i!=1&&ch<v.back()&&tmp==0){//判断是否小于前一个字母和是否被标记过
            v.pop_back();//删除字母
            v.push_back(ch);//插入字母
            tmp=1;//标记
        }
        else v.push_back(ch);
    }
    if(tmp==0){//若没有字母被删除过
        v.pop_back();//则删除末尾字母
    }
    vector <char>::iterator it;
    for(it=v.begin();it!=v.end();it++){//遍历输出
        cout<<*it;
    }
    return 0;
}
```

---

## 作者：hank0402 (赞：2)

一道贪心题。

显然，根据字符串的字典序规则，越在字符串前端的字母对字典序影响最大，于是我们可以从左到右遍历整个字符串，采用贪心策略，如果后一个字符的字典序比当前字符的字典序小，就标记一下，并退出循环，如果没有这样的字符，将最后一个字符去掉，并输出，否则，将标记的字符删掉，并把其余的字符串输出即可。

贪心策略的证明显而易见，如果后一个比前一个的字典序小，如果不删去前一个的话，那么如果要删去另一个个的话，肯定没有删去更优，因为我们是从左往右遍历的，越往前影响越大。

**Code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main() {
	int n;
	cin>>n;
	cin>>s;
	char ch = s[0];
	int x = 0;
	for(int i = 0; i < n; i ++) {
		if(s[i + 1] < s[i]) { //贪心策略
			x = i;
			break;
		}
	}
	if(x == 0) {
		cout<<s.substr(1, n - 1); //特殊情况，删去最后一个
		return 0;
	}
	else {
		for(int i = 0; i < n; i ++) {
			if(i != x) cout<<s[i]; //删除标记为x的字符
		}
	}
}
```

---

## 作者：Otue (赞：1)

前置知识：[相似题](https://atcoder.jp/contests/arc133/tasks/arc133_a)
## 题目大意
删去一个字符或不删，使得字符串的字典序尽可能小。
## 解法
有题意可知，删除一个字符后字典序绝对更优。

那么现在删哪一个字符呢？稍微看看样例可以知道：当当前字符比下一个字符大的时候，就要删除当前字符。

---

正确性怎么证明？

假如有一个序列：$a_1\ a_2 \ a_3...a_{k} \ a_{k+1}...a_n$，每当一个 $a_k$ 比 $a_{k+1}$ 大的时候 $(1\leq k\leq n-1)$，我们就执行以下操作：

删除 $a_k$ 之后有：
$a_1 \ a_2 \ a_3...a_{k-1} \ a_{k+1}...a_n$，   
原序列为$ \  \ \  \ \ \  \ \ \ : \  \ a_1\ a_2 \ a_3...a_{k} \  \  \ a_{k+1}...a_n$

对比以下，想要字典序最小，那么 $a_{k-1}$ 一定比 $a_k$ 小，这是显然成立的（因为我们每一次都要执行以上操作，一旦满足，就会退出，但是现在已经进行到第 $k$ 步了，所以上一步一定不满足）

所以说这种方式下一定是最小字典序！

**坑点：万一找不到 $a_k$ 比 $a_{k+1}$ 大怎么办？那就删除最后一个！**

## 代码
```c++
#include <iostream>
#include <cstring>
#include <algorithm>
 
using namespace std;
 
char c[200005];
int id, lenc;
 
int main()
{
    cin >> lenc;
    cin >> c;
    c[lenc] = char(1);
    for (int i = 0; i < lenc; i++) {
        if (c[i] > c[i + 1]) {
            id = i;
            break;
        }
    }
    for (int i = 0; i < lenc; i++) {
        if (i != id) cout << c[i];
    }
}
```

---

## 作者：StudyingFather (赞：1)

一种比较明智的贪心方法是：从左向右检查字符串中的每一个字符，如果它比后面一个字符大，那么就把这个字符删除，然后输出答案。特别地，如果不存在这样的字符，就删除最后一个字符。

```cpp
#include <stdio.h>
char s[200005];
int main()
{
 int n;
 scanf("%d",&n);
 scanf("%s",s);
 for(int i=0;i<n-1;i++)
  if(s[i]>s[i+1])
  {
   for(int j=0;j<n;j++)
    if(j!=i)putchar(s[j]);
   return 0;
  }
 for(int i=0;i<n-1;i++)
  putchar(s[i]);
 return 0;
}
```

---

## 作者：alex_liu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1076A)

## 题意：
删除一个字符或不删除，使得字符串的字典序最小

优先级为：

1. 从左往右第一个不同字符的 ASCII 值的大小关系
2. 字符串长度

## 思路：
一道非常明显的贪心题

当找到字符串里某一位使它后面的一位大时，就可以删除这一位（字典序就变小了）

如果没找到，则删除末位（因为不删除比删除末位的字典序大，从优先级的第二点可以看出）

那这样就很容易得到代码了 [doge]

## AC Code：
```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std;//命名空间 
string s;//定义子字符串 
int res=-1,n;//res 为删除字符的地址，n 为字符串长度 
int main(){
	cin>>n>>s;//输入 
	for(int i=0;i<n-1;i++){//从第一位到倒数第二位枚举是否有最优解 
		if(s[i]>s[i+1]){//找到最优解 
			res=i;//记录地址 
			break;//跳出循环 
		}
	}
	if(res==-1)res=n-1;//没有最优解，则删除末位（思路已经解释过了） 
	for(int i=0;i<n;i++){//输出字符 
		if(res!=i)cout<<s[i];//不是要删除的字符，则输出 
	}
	return 0;//完美结束 
}
```

---

## 作者：DreamBuilder (赞：0)

这是一道典型的贪心题，由于要让它的字典序最小，所以要让前面的尽量小，如 $\texttt{a c b d}$ ，只要删掉 $\texttt{c}$  就可以了，也就是说，要删掉一个字符，这个字符比它后一个字符大。但是，如果这个字符串按照升序排列， 如 $\texttt{a b c d}$ ，只能删掉最后一个字符，也就是 $\texttt{d}$ ，如果你删掉除了$\texttt{d}$ 以外的字符，字典序都会比前面大。 

Code
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[1000000];
int main(){
	int n, flag = -1;//把flag赋初值 
	cin >> n >> a;
	if(n <= 2 && a[0] < a[1]){//特判一下 
		cout << a[0];
		return 0;
	}
	for(int i = 0; i < n - 1; ++i)
		if(a[i] > a[i + 1]){//寻找第一个比上一个大的如果找到了，就退出循环 
			flag = i;
			break;
		}
	if(flag == -1)
		flag = n - 1;//如果没有，就删掉最后一个 
	for(int i = 0;i < n; ++i)
		if(i != flag)//判断是否是要删掉的，如果是，就不输出 
			cout << a[i];
	return 0;
}
```

---

## 作者：Jekyll_Y (赞：0)

## 题意
一个长为$n$的字符串删去一字符或不删，使得到的字符串字典序最小。
## 思路
仔细想一下，不难看出只有删去一个字符才能找到答案。   
现在的问题是删哪个字符，                           
如:$abcaca$,删去前面的$c$,比删去后面的$c$字典序更小。删去后分别为$abaca$和$abcaa$。               
所以我们只需要找到第一次出现后面的字符比前面的字符小的字符把它删去就好了，当出现**不下降**的字符串删去最后一个字符明显是最优解。
## 代码
```c
#include<cstdio>
#include<iostream>
#include<string>
using namespace std;
int k;
string n;
int main()
{
	cin>>k>>n;
	for(int i=0;i<n.size()-1;i++)
	{
		if(n[i]>n[i+1])
		{
			for(int j=0;j<i;j++)cout<<n[j]; 
			for(int j=i+1;j<n.size();j++)cout<<n[j]; 
			return 0;
		}
	}
	for(int i=0;i<n.size()-1;i++)cout<<n[i];
	return 0; 
}

```
### 完结撒花



---

## 作者：lu_run_ting (赞：0)

这道题有很明显的贪心特征，于是我们就用贪心做（有啥特征啊 

题意：    
给你一个字符串，可以删掉一个或不删一个字符，使得字典序最小

基础知识（大佬们可以跳过不看）：  
这道题的题目中的字典序最小是什么意思？我们可以把一个字符给哈希了，比如$abc=a*131^2+b*131+c=98*131^2+99*131+100=1694847$,而$bcd=b*131^2+c*131+d=99*131^2+100*131+101=1712140$，然后我们会发现abc的哈希值比bcd小，也就是说abc的字典序比bcd小   

我们可以发现，越靠前面的字符占的权值越大，所以说想要让字典序最小，就要删最前面的，而我们当然要删既靠前面又比后面大的。为什么？想一想，前面如果比后面大，那么删掉之后当前的这个数所占的权值就会比原来的小，哈希值也就变小了，字典序也就相应的变小了。   

还有一种特殊情况：如果所有的都不比后面大该怎么办呢？（也就是单调队列）题目中说可以不删，大家可不要被骗，无论怎样，删总是比不删的字典序靠前的，因为少了一项嘛，所以我们还是要删的，可是删哪个呢？最后一个，因为我们保证了这个序列是单调的，所以后面一定比前面大。

然后我们就可以开心地开始写代码了：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1000005;
string s; int n;
int main(){
	cin>>n>>s;
	int flag=n-1;//flag代表的是要删哪一个，如果flag=-1的话就代表是特殊情况（如上文所说）
	for(int i=0;i<n-1;i++)
		if(s[i]>s[i+1]){
			flag=i;
			break;
		}
	for(int i=0;i<n;i++) if(flag!=i) cout<<s[i];
	return 0; 
} 
//完美结束
```


---

