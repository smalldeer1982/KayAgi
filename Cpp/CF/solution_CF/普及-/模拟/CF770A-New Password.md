# New Password

## 题目描述

Innokentiy decides to change the password in the social net "Contact!", but he is too lazy to invent a new password by himself. That is why he needs your help.

Innokentiy decides that new password should satisfy the following conditions:

- the length of the password must be equal to $ n $ ,
- the password should consist only of lowercase Latin letters,
- the number of distinct symbols in the password must be equal to $ k $ ,
- any two consecutive symbols in the password must be distinct.

Your task is to help Innokentiy and to invent a new password which will satisfy all given conditions.

## 说明/提示

In the first test there is one of the appropriate new passwords — java, because its length is equal to $ 4 $ and $ 3 $ distinct lowercase letters a, j and v are used in it.

In the second test there is one of the appropriate new passwords — python, because its length is equal to $ 6 $ and it consists of $ 6 $ distinct lowercase letters.

In the third test there is one of the appropriate new passwords — phphp, because its length is equal to $ 5 $ and $ 2 $ distinct lowercase letters p and h are used in it.

Pay attention the condition that no two identical symbols are consecutive is correct for all appropriate passwords in tests.

## 样例 #1

### 输入

```
4 3
```

### 输出

```
java
```

## 样例 #2

### 输入

```
6 6
```

### 输出

```
python
```

## 样例 #3

### 输入

```
5 2
```

### 输出

```
phphp
```

# 题解

## 作者：幻之陨梦 (赞：7)

$Solution:$

首先我们需要明确一点那就是 **这道题是有spj的，如果你的输出与样例输出不同，是没有关系的**，接下来我们切入正题。

**第一种方法：** 开一个string类型的数组，将26个字母打表进去，然后循环n次，每次输出 $str[i\%k]$ 这个原因是只能有k个不同的字符，所以用取余就可以来完美地完成这一点。

**第二种方法：** 这次不用打表了，其实本质上和第一种方法没有什么区别，因为要输出字符所以你首先要先加上一个字符 $'a'$ 然后再加上 $i\%k$ ，原理与第一种方法相同，最后输出的结果和第一种方法输出的一模一样。

$code:$

~~讲得这么清楚了就不用贴代码了吧qwq~~

如果这篇文章给予了你帮助，那你就点个赞再走吧，Thanks♪(･ω･)ﾉ

---

## 作者：Andysun06 (赞：3)

## CF770A 题解
这个题目居然还没有 pascal 的题解，那我就来一篇吧。

### 解答疑惑：
相信大家在测样例的时候都很迷惑，居然和样例的不一样。我也遇到了这个问题，但我多次检查后，发现程序没有问题，于是斗胆提交了，发现其实是可以过的，所以不必为过不了样例而烦恼。

### 题目分析：
这题的题目意思较为明显，也没有特意挖坑，就是让你输出 $n$ 个由 $k$ 个不同小写字母组成字符串并且相邻的字符都不同。

### 题目难度：
大致难度应该在 `入门` 左右，思维难度较低。

### 做法分析：
这题需要我们运用到 ASCII 码，也就是需要把一个 ASCLL 码转换为字符，对于 C++ 来说，这是再简单不过的事，直接输出就可以，但 Pascal 就不一样了，需要用到 chr 函数，这个函数的作用就是把一个 ASCII 码转换为相应的字符，然后，我们就要思考了：如何让每相邻两个字符都不相同呢？

经过思考，可能第一个想到的都是一个个枚举，有重复的就删掉，但可以不用这么麻烦，仔细推理一下，很容易就可以发现，在 $i\ mod\ k$ 后，相邻的字符都不一样，然后，我们就可以写代码了。

### 完整代码：
```pas
var n,m,i:longint; //定义
    ch:char;
begin
    read(n,m);  //输入
    for i:=0 to n-1 do  //注意，是从 0 开始，到 n-1 结束，否则第一个点就 WA
    begin
        ch:=chr(i mod m+97);  //核心代码，可以把一个 ASCII 码转换为相应的字符
        write(ch);  //输出
    end;
end. //最后一个 end 要用英文句号
```

希望本题解对大家有帮助，也感谢管理员百忙之中为我审核题解，谢谢！！！

---

## 作者：Aw顿顿 (赞：2)

[MyBlog-我的题解小窝](https://www.luogu.com.cn/blog/AlanWalkerWilson/)

首先强调，此题带有 Special Judge，也就是说，你的程序只要给出的答案是符合其题目要求的，不一定和样例一样，也是可以 AC 的。

这时候，我们想一想，题目有哪些要求呢？

简单来说：

- 长度为 $n$，我们只需要一个变量为 $n$ 的 `while` 循环就可以解决。

- 由小写字母组成……有点棘手，放到后面再说。

- $k$ 中不同字符……只要每次的字符对 $k$ 取模就行了。

- 任意两个相同字符不能相连，那么我们循环每次对 $k$ 取模可以保证不相连。

这时候我们思考一下，如果每次 $n$ 减一，每次都输出小写字母 `a` 加上 $n$ 对 $k$ 取模的结果，是不是就成为了形如`abc……(a+k)abc……` 这样的数列？

对，这种方法的结果就是从 `a` 开始，持续 $k$ 个字母，然后再重新回到 `a`。

然后，我们来看一下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int main(){
    cin>>n>>k;
    while(n--){
        cout<<(char)('a'+n%k);
    }
    cout<<endl;
    return 0;
}
```
在输出的时候注意强制类型转换。

然后测样例不过没事，提交可以过，详见：

https://www.luogu.com.cn/record/32331995

好的，谢谢大家！

---

## 作者：锦瑟，华年 (赞：1)

我又来写水题题解啦。

恩，题目总结的很清楚，这个字符串满足：

1、长度必须是 $n$

2、必须是由小写字母组成

3、共有 $k$ 种不同的字符

4、任意两个相同字符不可以相连

1,2无需解释，我们这里详细讲 3,4 ，共有 $k$ 种不同的字符，为了方便，我们就用a,b,c,d,……,y,z 的顺序作为密码组成字符即可，而任意两字符不相连，则可以直接输出abcd abcd abcd …… 即可。

代码：

	#include<stdio.h>
	using namespace std;
	int main(){
	    int n,k,i;
   	    scanf("%d%d",&n,&k);//输入
  	    for(i=0;i<n;i++)printf("%c",'a'+i%k);//如上规则依次遍历，输出
        return 0;
	}   
好，拜拜~~

---

## 作者：Sora1336 (赞：1)

这道题是要输出$n$个由$k$个不同小写字母组成的相邻字符不同的字符串。

其他两个题解的做法和此大致相同，此题解或成本题最快解法。

核心代码仅一行，让我们对其进行分析；

```cpp
for(int i=0;i<n;i++) putchar('a'+i%k);
```

由$n$个字符组成，循环$n$次；

使用`putchar`直接输出从字符'a'后的第`i%k`项保证有$k$个不相同的字符，此处是用ASCII码的特性进行解题，使用`putchar`优化输出速度。

上代码。

```cpp
#include <iostream>
using namespace std;
int main(){
	int n,k;
	cin<<n<<k;
	for(int i=0;i<n;i++) putchar('a'+i%k);
} 
```

~~老规矩，谁抄谁CE~~

---

## 作者：xzllll07 (赞：0)

这道题，我们首先看四个条件：
```
1、长度必须是N
2、必须是由小写字母组成
3、共有K种不同的字符
4、任意两个相同字符不可以相连
```
第一项，长度必须是 $N$，很简单，定义一个空字符串 $s$ 作为结果，用循环放入 $N$ 个字符即可。

第二项，必须是由小写字母组成。用字符串存储全部的小写字母，需要时用下标调用。

第三项，共有 $K$ 种不同的字符。因为本题有 SPJ，所以只要字符不同，就可以。那么我们就可以想到，循环放入字符时，用 $i$ $mod$ $K$，结果一定在 $\text{0 - K-1}$ 之间，用这个结果作为下标调用存储小写字母的字符串，就可以保证共有 $K$ 种不同的字符。

与此同时，这种方式也同样满足了第四项要求，因为每次调用存储小写字母字符串的下标都相邻，所以相邻字符一定不同。

不太理解的可以看下表格：（例如 $N = 10$，$K = 4$）

![](https://cdn.luogu.com.cn/upload/image_hosting/2z94ah8o.png)

这样就可以保证符合四条条件。

下面看代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string c="abcdefghijklmnopqrstuvwxyz";
    int n,k;
    string s="";
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        s+=c[i%k];
    }
    cout<<s;
} 
```


---

## 作者：KazamiHina (赞：0)

题目分析：

现在假设$n=5$，$k=2$

那么构造一个长度为$5$的，有$2$种不同字母的序列即可

可以构造出 $ababa$ 等

当$n=8$，$k=3$时

可以构造出 $abcabcab$ 等

那么就可以找到规律了

即生成长度为$n$的序列，以字母表前$k$个为循环输出即可

这里可以先把$26$个字母的表打好

$code:$
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n,k;
string ans=" abcdefghijklmnopqrstuvwxyz";//打表

int main(){
	scanf("%d%d",&n,&k);
	for(int i=0;i<=n-1;i++){//构造长度为 n 的字符串
		putchar(ans[i%k+1]);//直接输出表中的第 i%k+1 项保证有 k 个不相同的字符
	}
	return 0;
}
```

$qwqwq$

---

## 作者：sysu_yzc (赞：0)

## 题意
只需要输出$n$个由$k$个不同小写字母组成的相邻字符不同的字符串就行了。
## 上代码
```cpp
#include<iostream>
using namespace std;
int main(){
    int n,k;
    cin>>n>>k;
    for(int i=0;i<n;i++) cout<<char('a'+i%k);
    return 0;
}
```

---

