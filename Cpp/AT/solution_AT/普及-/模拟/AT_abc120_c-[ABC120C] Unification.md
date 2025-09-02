# [ABC120C] Unification

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc120/tasks/abc120_c

机の上に $ N $ 個のキューブが縦に積まれています。長さ $ N $ の文字列 $ S $ が与えられます。

下から $ i $ 番目のキューブの色は、$ S $ の $ i $ 文字目が `0` のとき赤色、`1` のとき青色です。

あなたは、赤色のキューブと青色のキューブが隣り合っているような部分を選んで、それら $ 2 $ 個のキューブを取り除く操作を何度でも行えます。

このとき、取り除いたキューブの上にあったキューブは真下の物体の上に落下します。

最大で何個のキューブを取り除けるでしょうか。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ |S|\ =\ N $
- $ S $ の各文字は `0` または `1` である。

### Sample Explanation 1

以下の順に操作を行うと $ 4 $ 個全てのキューブを取り除けます。 - 下から $ 2 $ 番目のキューブと $ 3 $ 番目のキューブを取り除きます。その結果、下から $ 4 $ 番目のキューブが下から $ 1 $ 番目のキューブの上に落下します。 - 下から $ 1 $ 番目のキューブと $ 2 $ 番目のキューブを取り除きます。

## 样例 #1

### 输入

```
0011```

### 输出

```
4```

## 样例 #2

### 输入

```
11011010001011```

### 输出

```
12```

## 样例 #3

### 输入

```
0```

### 输出

```
0```

# 题解

## 作者：_lzy_ (赞：2)

## 思路
这一题它要求我们判断 $1$ 和 $0$ 可以删多少个。

那么我们可以这样
1. 先去统计 $1$ 和 $0$ 的数量分别有多少个。
2. 然后可以再去求出两个数的数量最小值，再将最小值 $\times$  $2$ 。

如果你不理解第 $2$ 条，请看我下面的解释

因为题目要我们求的是两个数能抵消多少，所以输出的答案一定是成双成对的。所以在我们求出最小之后需要 $\times$ $2$。你有可能有疑惑 $:$ 为什么要求最小值呢 $?$ 而不是最大值呢 $?$ 因为我们将最小值 $\times$ $2$ 才不会改变 $0$ 和 $1$ 的总数大小。如果我们把最大值 $\times$ $2$ 就会导致这两个数的总数变大。

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[110000];
int x,y;
int main()
{
	cin>>s;
	int l=strlen(s);
	for(int i=0;i<l;i++)if(s[i]=='0')x++;else y++;//统计0和1的数量。
	if(x>y)cout<<y*2;//求完最大值并且输出。
	else cout<<x*2;
	return 0;
}

```


---

## 作者：XKqwq (赞：0)

此题较为简单，建议评红。


### $\texttt{0.Translation}$

给出一个只由 $\texttt{0,1}$ 组成的字符串，可以删除相邻且不同的两个字符，求可以删除的位数。

---

### $\texttt{1.Key }$

每次删除一对 $\texttt{0,1}$ ，字符串中 $\texttt{0}$ 和 $\texttt{1}$ 的个数便分别减少 $1$ 。


要使得字符串不能删除，字符串只能含有一种字符。


即 $\texttt{0000} \cdots \texttt{0}$ 
 或 $\texttt{1111} \cdots \texttt{1}$ 。
 
或者可以这么说：

定义 $cnt0$ 表示字符串中 $\texttt{0}$ 出现的次数，定义 $cnt1$ 表示字符串中 $\texttt{1}$ 出现的次数。

每操作一次 $cnt0$ 和 $cnt1$ 都自减 $1$。

当 $cnt0 = 0$ 或 $cnt1 = 0$ 时，便不能操作了。


显然可以得出答案：



$$ans=2 \times \min( cnt0 , cnt1)$$



---


那么我们可以：

1. 统计 $\texttt{0}$ 和 $\texttt{1}$ 在字符串中出现的个数。

2. 套公式即可。

### $\texttt{2.Code }$

具体见注释，如有不懂得地方或建议请评论。

```cpp
#include <bits/stdc++.h>
using namespace std;

string s;
int cnt[2]; 
int main(){
	cin>>s;
	int l=s.size();
	for(int i=0;i<l;i++) cnt[s[i]-'0']++; //这里用桶排，可以不写判断。
	printf("%d\n", 2* min(cnt[0],cnt[1]) ); // 这里套公式。
	return 0;
}
```



---

## 作者：_空白_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT4318)

[类似题目](https://www.luogu.com.cn/problem/CF556A)

### 题意：

给定一个长度任意、仅有 $0$ 和 $1$ 的字符串，使得相邻的不同数字不停消除，直到不能消除为止，问最多消除多少个数字。

### 分析：

这是一道数学题。

我们分类讨论一下：

1. 两种数字都有：

   此时，由于串中数字只能是 $0$ 或 $1$ ，因而只要有不同数字就必然有至少一处地方有相邻的不同数字可以消除，即一定可以消除。

2. 只有一种 $/$ 全没了：

   显然，这种串无论如何都不能消除。

由于进行消除后，新串仍可以继续消除，因此，无论一开始的串是怎样的，都会被消除成第 $2$ 种串。

令串中 $1$ 的个数为 $numo$，$0$ 的个数为 $numz$，则：

每个串都能且只能消除 $\min(numo,numz)$ 次（因为其中一种数用完了整个串就变成了第二种串，不能再消除了）。

由于每次消除都要消除 $2$ 个数，所以最终答案是：

$2\times\min(numo,numz)$

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[100010]; 
int main()
{
    int n,sumo=0,sumz=0;
    cin>>s;
    int len=strlen(s);
    for(int i=0;i<=len-1;i++)
    {
        if(s[i]=='1') 
            sumo++;
        if(s[i]=='0') 
            sumz++;
    }
    cout<<min(sumo,sumz)*2<<endl;
    return 0;
}
```


---

## 作者：bryce (赞：0)

### 传送门 [AT4318](https://www.luogu.com.cn/problem/AT4318)

这是一道很简单的题目，我们可以想如果有 $1$ 和 $0$ 时，它们必定会存在相邻关系，可以删除它们，但当只剩下 $1$ 或 $0$ 时，就不能再删除了。

这就很好办了，如果有 $1$ 或 $0$ 时，我们统计出现的次数，再取一个最小值乘上两倍就是结果了。

### 代码
```cpp
#include<iostream>

using namespace std;

int main(){
	string s;
	int cnt1 = 0, cnt2 = 0;
	cin >> s;
	for (int i = 0; i < s.size(); i++){//统计0、1出现次数
		if (s[i] == '1'){
			cnt1++;
		}else{
			cnt2++;
		}
	}
	if (cnt1 > cnt2){//比较大小
		cout << 2 * cnt2;
	}else{
		cout << 2 * cnt1;
	}
	return 0;
}
```

---

## 作者：Iron_Heart (赞：0)

## 思路

思考一下，要使无法删除，需要满足什么条件？对，要使字符串只剩下 `0` 或 `1`。

于是我们统计字符串中 `0` 和 `1` 出现的次数，取最小值再 $\times 2$ 即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define min(a, b) ((a) < (b) ? (a) : (b))

char s[100100];
int zero, one;

int main() {
    scanf("%s", s);
    int len = strlen(s);
    for (int i = 0; i < len; ++i) {
        if (s[i] == '1') {
            ++one;
        } else {
            ++zero;
        }
    }
    printf("%d\n", min(one, zero) * 2);
    return 0;
}
```


---

## 作者：fjy666 (赞：0)

### 0x00 题意
给你一个字符串，允许你删除相邻两个 $0$ 和 $1$ ，请问最多能删除多少个字符？  
~~CF556A双倍经验~~

------------
### 0x01 思路
要想要删除的字符最多，则剩下的字符串必由同一个字符组成。
- 为什么？
- 设剩下的**最短**字符串不由一个字符组成，令这个字符串为原串。  
则原串中必有 $1$ ，而原串中至少有一个 $1$ 和 $0$ 相邻，  
我们就可以把它们删除。  
令删除后的串为新串，  
由于新串的长度比原串少 $2$ ，所以原串不可能是最短的。  
反之（把 $1$ 换成 $0$ ，把 $0$ 换成 $1$）同理。

知道了这一点，我们就可以统计出 $0$ 的数量和 $1$ 的数量，再用 它们的最小值$\times 2$ 就行了。  
- 为什么是最小值呢？
- 因为当有一种字符数量为 $0$ 时就不能匹配了。

------------
### 0x02 代码
```cpp
#include <cstdio>
#include <cmath>
#define fo(i_,j_,k_) for(int i_=j_;i_<=k_;++i_)
#define fr(i_,j_,k_) for(int i_=j_;i_>=k_;--i_)
#define It(type_) type_::iterator
#define rg register
#define rtn return
#define il inline

typedef long long ll;

il char ReadChar(void)
{
	char chr = getchar();
	if(chr == EOF) rtn EOF;
	while(chr!='0'&&chr!='1')
	{
		chr=getchar();
		if(chr == EOF) rtn EOF;
	}
	rtn chr;
}
il int min(int a,int b)
{
	rtn a<b?a:b;
}

int main()
{
	int Cnt0 = 0,Cnt1 = 0;
	for(;;)
	{
		char chr = ReadChar();
		if(chr == EOF)break; 
		if(chr == '0')++Cnt0;
		else ++Cnt1;
	}
	printf("%d",min(Cnt0,Cnt1)*2);
	rtn 0;
}
```

---

## 作者：HYdroKomide (赞：0)

# **正文：**
## 题意：
怎么使这个字符串不能再删除下去？让这个字符串全都是 $0$ 或者全都是 $1$ 即可。我们就可以求出其中 $0$ 的数量与 $1$ 的数量，取这两数的较小值，就是我们删除字符的次数，一共删除的字符数量就是这个数 $\times 2$ 的结果。
## 简约代码：
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int ans0,ans1;
int main(){
    char a;
    while(cin>>a){           //C++中cin的特性
        if(a=='0')ans0++;     //判断字符并计数
        else      ans1++;
    }
    cout<<min(ans0,ans1)*2<<endl;//输出
    return 0;
}
```
# **THE END**

---

## 作者：Zirnc (赞：0)

[ChungZH's blog](https://chungzh.cn) · [ChungZH's portfolio](https://chungzh.cc)

题目：

> 给你一段只有 `0` 和 `1` 的字符串，如果两个相邻的字符不一样，那么就可以删掉这两个字符，其他字符不变。求一共可以删除掉多少个字符。

这个字符串里只要有不同的字符，就会存在相邻的情况。所以我们直接输出这个字符串里 `0` 和 `1` 各有多少个，然后将其中较小的数乘 2 即可。

```cpp
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;
int main()
{
    string s;
    cin >> s;

    const int slen = s.length();
    int cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < slen; i++)
    {
        if (s[i] == '0') cnt1++;
        else cnt2++;
    }

    cout << min(cnt1, cnt2)*2 << endl;
    return 0;
}
```

---

