# String Equivalence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/panasonic2020/tasks/panasonic2020_d

この問題では、英小文字からなる文字列のみを考えます。

文字列 $ s,\ t $ は以下の条件を満たすとき **同型** であるといいます。

- $ |s|\ =\ |t| $ である。
- 任意の $ i,\ j $ に対し次のいずれかが成立する。
  - $ s_i\ =\ s_j $ かつ $ t_i\ =\ t_j $
  - $ s_i\ \neq\ s_j $ かつ $ t_i\ \neq\ t_j $

たとえば、`abcac` と `zyxzx` は同型ですが、`abcac` と `ppppp` は同型ではありません。

文字列 $ s $ は以下の条件を満たすとき **標準形** であるといいます。

- 任意の $ s $ と同型な文字列 $ t $ に対し、$ s\ \leq\ t $ が成立する。ただしここで $ \leq $ は辞書順での比較を表す。

たとえば、`abcac` は標準形ですが、`zyxzx` はそれより辞書順で小さい `abcac` と同型のため標準形ではありません。

整数 $ N $ が与えられます。 長さ $ N $ の標準形の文字列を全て、辞書順で昇順で出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10 $
- 入力は全て整数である。

## 样例 #1

### 输入

```
1```

### 输出

```
a```

## 样例 #2

### 输入

```
2```

### 输出

```
aa
ab```

# 题解

## 作者：Catalan1906 (赞：4)

考虑一个字符串怎么样才是一个满足 normal form 的字符串。

这里给出结论：第 $i$ 个字符不能大于前 $i-1$ 个字符的最大值 $+1$。

因为如果第 $i$ 个字符大于前 $i-1$ 个字符的最大值 $+1$ 的话，第 $i$ 个字符就可以替换成前 $i-1$ 个字符的最大值 $+1$，替换过后的字符串的字典序显然会小于原字符串，此时这个字符串就不是一个满足 normal form 的字符串。

用 dfs 搜索出所有满足 normal form 的字符串即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

int cnt, n;

void dfs(int depth, int pm, string t) {
// 当前是第 depth 个字符，前 (depth - 1) 个字符的最大值为 pm，当前字符串为 t。
	if(depth == 1) { // 第一个字符必定填 'a'。
		dfs(depth + 1, pm + 1, "a");
		return ;
	}
	if(depth == n + 1) { // 填完了 n 个字符，输出。
                cout << t << endl;
		return ; 
	}
	for(register char i = 'a'; i < 'a' + pm; i++) { 
    		// 枚举第 depth 个字符不大于前 (depth - 1) 个字符的最大值的情况
		dfs(depth + 1, pm, t + i);
	}
	dfs(depth + 1, pm + 1, t + (char)('a' + pm));
   	// 第 depth 个字符大于前 (depth - 1) 个字符的最大值的情况
}

int main() {
	cin >> n;
	dfs(1, 0, ""); 
   	// 从第 1 个字符开始填，前面字符的最大值为 0 （因为没有字符），初始时是空串
	return 0;
}
```


---

## 作者：红黑树 (赞：4)

### 题意：

让你生成一个长度为 $n$ 的字母排列，满足 $s_0$ 是 $'a'$ 并且 $s_i =$ $'a'$ 到 目前选择的字符串中最大元素的下一个字母

---

### 分析：
暴力枚举每一位的所有可能性，~~或者打表~~

---

那么直接放代码

```c++
#include <iostream> // 提供cin 和 cout 还有 puts
#include <algorithm> // 提供 max_element

using namespace std;

char choose[11] = {'a'}; // 把结果数组的第一位设为要求的 'a'
int n;

inline void dfs(int idx) { // 搜索：idx 表示当前正在枚举第 idx 位的所有可能性
    if (idx == n) { // 如果长度达到了 n
        puts(choose); // 输出答案数组
        // 顺便说一句 puts() 函数输出完后会自动换行
        return; // 终止
    }
    for (int i = 'a'; i <= *max_element(choose, choose + idx) + 1; i++) { // 枚举第 idx 位的可能，i = 'a' 到 choose 中 最大因素 + 1
        // 介绍一下 max_element 函数返回 给定位置中最大元素的地址，所以调用是要查找它的地址中的内容（也就是*max_element）
        choose[idx] = i; // 把选择的数的值给 choose[idx]
        dfs(idx + 1); // 继续搜索下一个位置
    }
}

int main() {
    cin >> n;
    dfs(1); // 从第二位开始枚举，由于第一位固定为'a'
    return 0;
}
```

---

## 作者：Waaifu_D (赞：2)

## 题意简述

~~翻译看不懂~~

给定我们一个 $n$ ，要求输出所有满足
“标准型”的字符串

## 思路

研究了一会样例，我们发现这些字符串的开头都是 ```
a```
 ，我手头模拟了一下 $n=3$ 的情况

```
aaa
aab
aba
abb
abc
```

怎么感觉和全排列这么像？

然后我照着全排列的思想，打出了如下代码

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int n;
string s="a";
inline void work(int k,char a)
{
    if(k==n){cout<<s<<endl;return;}
    else
    {
        string now;
        now=s;
        for(char i='a';i<=a+1;i++)
        {
            s=now+i;
            work(k+1,max(a,i));//全排列的搜索
        }
        s=now;//全排列的回溯
    }
}
int main()
{
    cin>>n;
    work(1,'a');
    return 0;
}

```
然后就AC了？？

## 正题

来正常分析一下这道题，不难发现，一个满足题意的字符串一般具有如下性质

-  1.第一位一定为 ```a``` 。


- 2. 后面的 $n-1$ 位要么与前面的字符中任意一个字符相同，要么是前面所有字符中ASCII码最大的一个字符+1（比如 ```aaaa``` 后面接个 ```b``` ）。

然后这就是一个以 ```a``` 开头的字符全排列

但是也不完全是全排列，比如

```
abb abc
```


这组字符，需要满足后面的字符比前面的大，所以不能出现 ```acb``` 这种情况




---

## 作者：eEfiuys (赞：1)

题目：[AT5807](https://www.luogu.com.cn/problem/AT5807)
- 第 $1$ 位字符为 $'a'$;
- 第 $2$ 位到第 $n$ 位字符要么与前面的任意一位字符相同，要么为最大字符 $+1$。

**使用 dfs 搜索所有满足以上条件的字符串。**

- 从第 $1$ 位到第 $i-1$ 位包括从 $'a'$ 到最大字符的所有字符，因此**直接从 $'a'$ 枚举到最大字符 $+1$**;
- 长度到 $n$ 就输出字符串并回溯。

------------

**AC 代码如下：**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
void dfs(int step,char ch,string s) //step字符串长度，ch最大字符，s字符串。
{
    	if(step==n) //长度够了，输出。
    	{
        	cout<<s<<endl;
        	return; //回溯。
    	}
    	for(char i='a';i<=ch+1;i++) //从'a'枚举到最大字符+1。
        	dfs(step+1,max(i,ch),s+i); //长度+1，更新最大字符，字符串加上 i 。
}
int main()
{
    	cin>>n;
    	dfs(1,'a',"a"); //初始长度为1，初始最大字符为'a'，初始字符串为a。
    	return 0;
}
```

---

## 作者：_ajthreac_ (赞：1)

这道题目的数据范围和输出要求显然是让我们搜索的。  
考虑一个字符串如何才能成为**标准型**：如果最后一个字符大于倒数第二个字符 $+1$，那么它不是标准型。  
例：`abda` 不是标准型，和它对应的标准型是 `abca`。  
所以，我们在搜索时记录之前的最大值，然后枚举到最大值 $+1$ 即可。
核心代码：
```cpp
int n;string s="a";
void DFS(int now,int lst){
  if(now==n){
    cout<<s<<endl;
    return;
  }
  for(rg int i=97;i<=lst+1;i++){
    s+=(char)i,DFS(now+1,max(lst,i));
    s=s.substr(0,s.size()-1);//注意回溯
  }
}
int main(){
  Read(n);
  DFS(1,97);
  return 0;
}
```

---

## 作者：Loser_King (赞：1)

题目链接（AtCoder）：[link](https://atcoder.jp/contests/panasonic2020/tasks/panasonic2020_d)

这题比赛时来不及写了，比赛结束后就写完了awa。

--------

### 题意：

若等长的字符串 s,t 满足以下条件，则称 s,t **同构**：

> 对于两个数$i,j(1\le i,j\le n,i\not=j),$
如果 $s_i\not=s_j$ 则 $t_i\not=t_j$。如果 $s_i=s_j$ 则 $t_i=t_j$ 。

定义 **标准型** 字符串为

> 对于所有字典序小于它的字符串都不与它同构。

求长度为 $n(1\le n\le 10)$ 的所有 **标准型** 字符串。

### 思路：

显然，字符串的第一位一定是 $\texttt{a}$ 。

对于后面的每一位，他只有两种选择：

- 和之前的某一位相同 
- 和之前的任何一位都不相同

使用 dfs , 生成每一位即可。

### 代码：

```c++
#include<bits/stdc++.h>
using namespace std;
int n;
void dfs(string s,char pre){
	if(s.length()==n)cout<<s<<endl;//长度足够，输出
	else for(char i=97;i<=pre;i++)dfs(s+i,pre+(i==pre));
             //长度不足，继续枚举
             //注意，一定要从a枚举到最后，否则无法做到字典序
}
int main(){
	cin>>n;
	dfs("",97);//第一位为a
}
```

---

## 作者：xh39 (赞：0)

我们现在想要找出一个新的标准型字符串满足要求,那么我们要尽量插空,如果这个字符串的某个字符为前面的所有字符的最大值+2或更大,那么我们可以找出一个新字符串,将这个字符替换成最大值+1,后面的(最大值+1)替换成(这个字符)就行了。

如果不满足上面的性质则不可以插空,输出这个字符串。

当然,第一位如果不是a,那么也不行。

ac.code:

```cpp
#include<iostream>
using namespace std;
string s="a";
int n;
void dfs(int step,char $){ //$表示上限,最多枚举到多少,不会CE。
    if(step==n){
        cout<<s<<endl;
        return;
    }
    string t=s;
    char i;
    for(i='a';i<=$+1;i++){ //可以枚举到最大值+1。
    	s=t+i;
    	dfs(step+1,max($,i)); //如果i大就更新最大值。
	}
	s=t; //回溯。
}
int main(){
    cin>>n;
    dfs(1,'a');
    return 0;
}
```

---

## 作者：gyh20 (赞：0)

可以发现，第一个字符必须是 $\text a$。

然后，之后每一个字符不能大于之前出现的字符 $+1$。

可以使用反证法，如果大于最大值 $+1$ 那么可以用最大值代替。

综上，直接 dfs 一次得出答案即可。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;
	re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0'){
		t=(t<<3)+(t<<1)+v-48;
		v=getchar();
	}
	return t;
}
long long a;
char s[12];
inline void dfs(re int x,re char c){
	if(x==a+1){
		printf("%s\n",s+1);
		return;
	}
	for(re int i='a';i<=min(c,'z');++i){
		s[x]=i;
		if(i!=c)dfs(x+1,c);
		else dfs(x+1,c+1);
	}
}
int main(){
	a=read();
	dfs(1,'a');
}


```


---

