# Polo the Penguin and Strings

## 题目描述

```
CF288A
题目大意：
找到一个字符串，满足以下条件：
1、长度为n，且字符串中包含k种小写字母；
2、相邻的字符不相等；
3、在满足1、2两条件的所有字符串中字典序最小。

## 样例 #1

### 输入

```
7 4
```

### 输出

```
ababacd
```

## 样例 #2

### 输入

```
4 7
```

### 输出

```
-1
```

# 题解

## 作者：SH___int (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/CF288A)

## 1.思路

首先，我在阅读了样例和题目后，发现这就是一道模拟题目，在一般情况下，答案肯定是 $ababa$ 开头的字符串。所以将它枚举出来就可以啦！

## 2.普及小知识点
1. $a$ 的 ASCII 码为 $97$，往后以此类推。（其实很简单）。
2. 这道题只涉及小写字母，所以按字典序来排的话，就是 $a$ 开头的排在前面，如果都是 $a$ 开头，就看第二位，是 $a$ 的排在前面，以此类推。（大写字母同理）。

接下来到了激动人心的代码时间啦！
## 3.代码

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,k;//定义长度和小写字母种类数 
	cin>>n>>k;
	if(n<k||(k==1&&n>1)) cout<<"-1";//特判一下，如果种类数大于字符串长度或者种类数等于1，并且字符串长度大于1 (说明相邻的字符一定相同)的话，直接输出-1 
	else if(n==k)//继续特判种类数等于字符串长度的情况 
	{
		for(int i=97;i<97+k;i++)//直接从 a开始输 k个不同且顺序的小写字母 
		{
			char a=i;//因为要输出字符，所以要强制转换一下变量类型 
			cout<<a;
		}
	}
	else//最后剩下 n>k的情况 
	{
		n-=k-2;//a,b在下面已经枚举过，所以要把 a,b的种类数减去，n再减去 k，剩下的就是应该输出的 a,b数量 
		for(int i=0;i<n;i++)
		{
			if(i%2==0) cout<<'a';//a,b交替输出 
			else cout<<'b';
		}
		for(int i=99;i<=97+k-1;i++)//再把剩下的 c,d,e等小写字母排出来 （ c的ASCLL码为99） 
		{
			char a=i;
			cout<<a;
		}
	}
	return 0;
}
```
~~码风很烂，不喜勿喷QWQ~~

## 4.总结
我再说一下为什么要 ababa 这样开头。因为字典序的最优序列是 aaaaa 开头，但题目中说，连续两个字符要不相同，所以这道题的最优解就是 ababa 作为开头。

我写的题解不多，经验不丰富，有什么不足或想给出建议的，可以评论出来，感谢阅读 qwq！



---

## 作者：a1a2a3a4a5 (赞：1)

##### [题目：](https://www.luogu.com.cn/problem/CF288A)
-  题意：
1. 找出一个长度为  ` n `  且字符串中包含  ` k `  种小写字母。
1. 相邻的字符不相等。
1. 在满足  1  、  2  两条件的所有字符串中字典序最小的那一个。


- 思路
1. 条件  1  很简单：可以重复  `n`  次随意顺序输出  `k`  种小写字母。
1. 条件  2  只需要在条件  1  的基础上：按顺序输出。
1. 条件   3   ，看到这个条件，我们必须要知道字母字典序相对大小，  ASCII  码上给出了详细大小：![](https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fimg.doc.docsou.com%2Fpic%2F4d8c5f9a49406d95b4647265%2F1-728-jpg_6_0_______-715-0-0-715.jpg&refer=http%3A%2F%2Fimg.doc.docsou.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1668596538&t=3e9c5d364a76feb5e778add62d9ea9cd)

   可以看到  $ a $  的  ASCII  的值是最小的，也就是它的字典序最小，  $ b $  其次……  $ z $  的字典序最大。那么解决方式就显而易见了：一直输出 $  a b a b a b a  $ ……在最后  ` k `  -  2  个字符顺序输出除  $ a $  、  $ b $  外的字符。


- 特判
1. 当  ` n `   $ = $  ` k `  时，可以直接顺序输出从  $ a $  到  $ a $  +  ` k `  的字符。
1. 当  ` n `  $ > $  ` k `  时，就是正常情况，请见思路 3 。
1. 当  ` n `  $ < $  ` k `  时，那么字符串装不下  ` k `  个字符，所以无解。
1. 当  ` k `  $ = $  1  时，则无法且   ` n `  $ > $  1 时，则无法遵守条件 2  ，无解。
- 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int main()
{
		cin>>n>>k;
		if(n==k) for(int i=0;i<k;i++) cout<<(char)(i+'a');
		//特判n=k的情况。
		else if(k==1||n<k) cout<<-1;
		//特判无解的情况。
		else
		{
			for(int i=0;i<n-k+2;i++) cout<<(i%2==0?"a":"b");
			for(int i=0;i<k-2;i++) cout<<(char)(i+'a'+2);
		}
		//不懂请见上面思路3。
		return 0;
}
```

---

## 作者：kbzcz (赞：0)

## 题目大意

输入 $n,k$,让你用 $k$ 种小写字母组成一个长度为 $n$ 的字符串，使得这个字符串的字典序尽可能的小。

字典序的解释在百度上有，不懂的可以去搜一下。

## 思路

通过字典序的定义和题目样例可以看出，放在字符串前面的要尽可能小，但相邻两个字符要不一样，所以字符串前面就 $\verb!abababab!$ 循环，使得字典序最小。但题目要求要包含 $k$ 种字符，所以当只剩下 $k-2$ 个字符位时，就要从 $c$ 开始，顺序的往下填到最后，既保证了字典序最小，又有 $k$ 个字符。

当 $k>n$ 或当 $k=1$ 时并且 $n>1$ 时，就是无解的。（应该都懂吧）

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int n,k;
	scanf("%d%d",&n,&k);
	if((n>1&&k==1)||n<k) {
		printf("-1");
		return 0;
	}
	int t=n-(k-2);
	char a[1100005];
	for(int i=1;i<=t;i++) a[i]='a'+(i+1)%2;
	for(int i=t+1;i<=n;i++) a[i]='b'+i-t;
	for(int i=1;i<=n;i++) printf("%c",a[i]);
	return 0;
}
```



---

## 作者：qczrz6v4nhp6u (赞：0)

## 题意
构造一个长度为 $n$ 且相邻两位互不相同的字符串，使得字符串内含有 $k$ 个不同字母且字典序最小。
## 做法
无解情况：  
$1.\,k>n$  
$2.\,n>1$ 且 $k=1$

接下来考虑贪心构造。

首先不难得到答案字符串肯定含有 $\verb!abcd...!$ （一共 $k$ 个）  
而要使字典序最小，我们可以把 $\verb!abcd...!$ 移到最后面，在前面交替输出 ```a``` 和 ```b```

下面是具体化的做法：

先交替输出 $n-k$ 个 $\verb!a!$ 和 $\verb!b!$  
然后输出字符串 $\verb!abcd...!$ （长度为 $k$ ）  
注意到答案的第 $n-k$ 位有可能为 $\verb!a!$ ，直接输出 $\verb!abcd...!$ 会导致 WA  
将 $\verb!abcd...!$ 开头的 $\verb!a!$ 和 $\verb!b!$ 交换即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int main(){
    scanf("%d%d",&n,&k);
    if(k>n||(n>1&&k==1)){//无解
        puts("-1");
        return 0;
    }
    bool f=0;
    for(int i=1;i<=n-k;i++){//输出ababab...
        putchar('a'+f);
        f=!f;
    }
    if(f==0){//第n-k位为b（不需交换）
        for(int i=0;i<k;i++)
            putchar('a'+i);
    }
    else{//第n-k位为a（需要交换）
        putchar('b'),putchar('a');
        for(int i=2;i<k;i++)
            putchar('a'+i);
    }
    return 0;
}
```


---

## 作者：JustinXiaoJunyang (赞：0)

思路分析：

一个 $n$ 位长的字符串，要含有 $k$ 个字符。若 $k>n$ 或 $n>1$ 并 $k=1$，可以推出无解。能找到就要找字典序最小的，前 $n-k+2$ 位交替输出 $a$ 和 $b$。从第 $n-k+3$ 位到最后就由 $c$ 开始。因为计算了会变成整数，这里可以强转成字符。

参考代码：

```cpp
#include <iostream>
using namespace std;

int main()
{
	int n, k;
	cin >> n >> k;
	if (n < k || n > 1 && k == 1)
	{
		cout << "-1" << endl;
		return 0; 
	}
	for (int i = 1; i <= min(n, n - k + 2); i++)
	{
		if (i % 2 == 1) cout << "a";
		else cout << "b";
	}
	for (int i = n - k + 3; i <= n; i++)
	{
		cout << char('c' + i - n + k - 3);
	}
	return 0;
}
```

---

## 作者：hyc1026 (赞：0)

有一个 $n$ 位长的字符串，含有 $k$ 个不同的字符。

无解情况：
1. $k>n$
1. $n>1$ 且 $k=1$

以上两种情况无解，输出 $-1$ 即可。

如果能找到，就找字典序最小的，所以前 $n-k+2$ 位只需交替输出 $\texttt{a,b}$ 即可。

从第 $n-k+3$ 到第 $n$ 位，就由字母 $\texttt{c}$ 开始，一直输出到第 $n$ 个字母即可。

AC CODE:

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n,k;
	cin >> n >> k;
	if(n < k || (n > 1 && k == 1)) //判断无解，这里错有可能会有 Wrong answer on test 26.
	{
		cout << -1 << endl;
		return 0; //记得直接结束
	}
	int w = min(n-k+2,n); //注意这里有个大坑点！有时 n 小于 n-k+2，一般错在这里也会有 Wrong answer on test 26.
	for(int i=1; i<=w; i++)
	{
		if(i % 2 == 1) cout << "a"; //先输出a
		else cout << "b";
	}
	for(int i=n-k+3; i<=n; i++) cout << (char)('c' + i-n+k-3); //输出后面的
	return 0;
}
```

---

## 作者：yinhy09 (赞：0)

## 思路讲解：

本题思路主要是贪心算法。

有 $n$ 位长的字符串，需要含有 $k$ 个字符。如果 $k > n$，或是 $n>1$ 且 $k==1$，那么就是找不到这样的字符串的，输出 $-1$ 即可。

如果能找到，因为找的是字典序最小的，所以前 $n-k+2$ 位只需交替输出 $a,b$ 即可。（$a$ 在前 $b$ 在后，这样字典序小）从第 $n-k+3$ 到第 $n$ 位，就由字母 $c$ 开始，一直输出到第 $n$ 个字母即可。

鉴于以上策略很好想（其他题解也说了），我就重点说一下易错部分：

首先，$n-k+2$ 是有可能大于 $n$的，所以需要特殊判断，方法有两种：

1. 循环时不用 `i<=n-k+2`，而用 `i<=min(n,n-k+2)`，先将 $n$ 与 $n-k+2$ 取最大值，再循环。

1. 直接 `i<=n`，在循环内判断此时的 $i$ 与 $n-k+2$ 的大小关系。

其次，本题要对字符进行运算，所以推荐使用 `printf("%c")` 进行输出。

说了这么多，上代码~

## AC CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,k;
	cin>>n>>k;
	if(n<k||n>1&&k==1)//无法构成
	{
		cout<<"-1";
		return 0; 
	}
	for(int i=1;i<=min(n,n-k+2);i++)//本人采用了上面两种方法的第一种。
	{
		if(i%2==1)cout<<'a';//特别注意是模2余1输出a，不是余0
		else cout<<'b';
	}
	for(int i=n-k+3;i<=n;i++)//这里就不用特判了，因为本身终止条件就是小于等于n
	{
		printf("%c",'c'+i-n+k-3);
	}
	return 0;
}

谢谢观看~

```


---

## 作者：封禁用户 (赞：0)

题目传送门：[CF288A Polo the Penguin and Strings](https://www.luogu.com.cn/problem/CF288A)

**解法：** 贪心。

**思路：** 题目既然说要字典序最小，有说要相邻的字符不一样，所以在$1$至 $n+2-k$ 都输出$ab$，剩余的从$c$开始输出即可。

**无解的情况：** 

   1. 当$n<k$，则不能满足条件$1$。
   1. 当$n>1$ && $k==1$，是不能满足条件$2$的。 

```cpp
#include<cstdio>
using namespace std;
int n,k;
int main()
{
    scanf("%d%d",&n,&k);
    if(n<k || n>1 && k==1){
        printf("-1");
        return 0;
    }
    for(int i=1;i<=n;i++)
        if(i<=n+2-k){
            if(i%2)printf("a");
            else printf("b");
        }
        else printf("%c",'a'+i+k-n-1);
    return 0;
}
```


---

## 作者：ztxtjz (赞：0)

## 【思路】
算法：**贪心**

根据样例一，我们可以得到一些启示：前面不断重复输出$ab$，最后几个字母输出$cdef$等。手算可知，从$1$到$n+2-k$输出$ab$串，从$n+3-k$到$n$顺序输出$b$以后字母。

不存在满足条件的字符串有两种情况

①$n<k$，无法满足条件$1$

②$n>1$且$k==1$，无法满足条件$2$
## 【代码】
```cpp
#include <cstdio>
int n,k;
int main()
{
	scanf("%d%d",&n,&k);
	if(n<k||n>1&&k==1)
	{
		printf("-1");
		return 0;
	}
	for(int i=1;i<=n;i++)
		if(i<=n+2-k) printf("%c",'a'+!(i&1));
		else printf("%c",'a'+i+k-n-1);
	return 0;
}
```


---

