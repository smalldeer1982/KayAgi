# 天下一魔力発電

## 题目描述

## 题目翻译：天下一魔力发电

天下一魔力发电厂能够通过神奇的魔法生成电力。

用于魔力发电的燃料是一串由字符 `(` 和 `)` 组成的字符串 $S$，并且字符串的长度是偶数。

当我们将字符串 $S$ 转换成“匹配的括号字符串”时，魔力发电就会成功。

所谓的“匹配的括号字符串”满足以下条件：

- `()` 是一个匹配的括号字符串。
- 如果 $T$ 是一个匹配的括号字符串，那么 `(T)` 也是一个匹配的括号字符串。
- 如果 $T$ 和 $U$ 都是匹配的括号字符串，那么 $TU$ 也是匹配的括号字符串。

天下一魔力发电厂的文本处理器提供了四种操作方式：

1. 将光标向右移动（如果光标已经指向最后一个字符，则无法继续右移）。
2. 将光标向左移动（如果光标已经指向第一个字符，则无法继续左移）。
3. 如果光标指向的字符是 `(`，可以将其改为 `)`。
4. 如果光标指向的字符是 `)`，可以将其改为 `(`。

例如，给定字符串 $S$ 为：

```
())(()))
```

通过适当的第 1 和第 4 种操作，可以将其转换为：

```
(()(()))
```

这时，字符串变成了一个匹配的括号字符串。

作为发电厂的负责人，Fude-kun 想要通过最少的操作次数将字符串 $S$ 转换为匹配的括号字符串。

请你计算出将字符串 $S$ 转换为匹配的括号字符串所需的最少操作次数。

## 说明/提示

- 字符串 $S$ 的长度 $|S|$ 是偶数。
- $2 \leq |S| \leq 100$

## 样例 #1

### 输入

```
())(()))```

### 输出

```
2```

## 样例 #2

### 输入

```
((((```

### 输出

```
5```

## 样例 #3

### 输入

```
)))(((```

### 输出

```
9```

# 题解

## 作者：wandereman (赞：3)

[快速传送](https://www.luogu.com.cn/problem/AT_tenka1_2016_qualB_b)

## 思路
1.先遍历整个字符串。  
2.把左括号记录下来。  
3.把右括号和最近的做括号匹配，如果没有，就改成右括号。   
4.最后处理剩下的左括号，输出即可。

## AC code
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll top,h = 1,t,ans,la = 1,stk[1005],q[1005];
char a[1005];
int main(){
	cin>>a + 1;
	ll len = strlen(a+1);
	for (ll i = 1;i <= len;i++){
		if (a[i]=='(') stk[++top]=i;
		else{
			q[++t] = i;
			top--; 
			if (top < 0){
				la = q[h++];
				top+=2;
				ans++;
			}
		} 	
	}
	ans+=la - 1;
	ans+=max(stk[top] - la,0ll) + top/2;
	cout<<ans;
	return 0;
}
//AT_tenka1_2016_qualB_b
```

---

## 作者：yuantc (赞：2)

# 分析
这道题遍历一遍基本上就完了。有一个括号就扫一遍周围对应的括号，然后进行匹配。不行的话就把它改成相反的括号，留到最后处理。
###  AC code

```cpp
#include<bits/stdc++.h>
#define yuantc 1145
using namespace std;
char a[yuantc];
long long t1,x=1,t2,a1,a2=1,k2[yuantc],s[yuantc];
int main()
{
	cin>>a+1;
	long long len=strlen(a+1);
	for(long long k=1;k<=len;k++) { if (a[k]=='(') { k2[++t1]=k; } else{ s[++t2]=k; t1--; if(t1<0) { a2=s[x++]; t1+=2; a1++;} } }
	a1+=a2-1;a1+=max(k2[t1]-a2,0ll)+t1/2;
	cout<<a1<<endl;
	return 0;
}
```

---

## 作者：zyen11451425 (赞：1)

[AT_tenka1_2016_qualB_b](https://www.luogu.com.cn/problem/AT_tenka1_2016_qualB_b)

## 简明题意

题目描述太复杂了，实际就是不断更改括号使字符串变为合法的字符串（匹配的括号字符串）。

发现使用 STL 中的栈最适合解决此问题。

## 解题思路

发现 [P1944](https://www.luogu.com.cn/problem/P1944) 好像很像这道题目，但此题需解决修改的问题。

首先遍历字符串，遇到左括号就将其位置入栈。凡是遇到右括号就查询最近的未被匹配的左括号，并进行匹配，否则将这个右括号改为左括号。最后处理所有剩余左括号。

注意移动位置也计入操作次数。

---

## 作者：chengjindong (赞：0)

[题目](https://www.luogu.com.cn/problem/AT_tenka1_2016_qualB_b)

遍历整个字符串。

- 只要遇到左括号就记录下来。
- 只要遇到右括号就去找最近的且没有被匹配的左括号，匹配掉，如果没有，就把这个右括号改成左括号。

最后处理剩下的左括号，输出即可。

---

## 作者：kinglf (赞：0)

~~第一次遇到这种题，兴奋坏了，写篇题解纪念第一道黑题~~
### [题意描述](https://www.luogu.com.cn/problem/AT_tenka1_2016_qualB_b)
懂的都懂，故不再赘述。
### 核心思想
首先将原字符数组遍历一遍。在这个过程中，凡是遇到左括号就将其位置记录下来。凡是遇到右括号就查询最近的未被匹配的左括号，并进行匹配，否则将这个右括号改为左括号。最后处理剩下的左括号即可。（具体见代码）  
**警钟觉蓝：最后记得换行！！！**
## AC 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll top,h=1,t,ans,last=1,stk[222],q[222];
char a[222];
int main(){
	scanf ("%s",a+1);
	ll len=strlen(a+1);
	for (ll i=1;i<=len;i++){
		if (a[i]=='(') stk[++top]=i;//记录左括号和位置 
		else{
			q[++t]=i;//记录右括号的位置 
			top--;//括号匹配 
			if (top<0){
				last=q[h++];
				top+=2;
				ans++;//计算答案 
			}
		} 	
	}
	ans+=last-1;
	ans+=max(stk[top]-last,0ll)+top/2;//计算答案
	printf ("%lld\n",ans);
	return 0;
} 
```

---

