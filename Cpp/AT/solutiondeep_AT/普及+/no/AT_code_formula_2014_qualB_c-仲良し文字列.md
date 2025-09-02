# 题目信息

# 仲良し文字列

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-formula-2014-qualb/tasks/code_formula_2014_qualB_c

(21:13 追記) |A|=|B|=1のケースがテスト中に一つ含まれていましたので、リジャッジを行います。なお、このケースで`NO`を出力するプログラムに影響はありません。

文字列 $ A $ の文字をちょうど $ 3 $ 回スワップすることにより、文字列 $ B $ に変換できるとき、二つの文字列 $ A $, $ B $ を、仲良し文字列と呼ぶことにします。

スワップとは、文字列に含まれる $ 2 $ つの文字を、入れ替えることを指します。 例えば、`abc`という文字列であれば、`a`と`c`を入れ替えて、`cba`のように変換することが出来ます。

`aa`のような文字列に対し、 $ 1 $ 文字目の`a`と、 $ 2 $ 文字目の`a`を入れ替えることは許されていますが、同じ場所の文字を指定することはできません。

文字列 $ A $, $ B $ が与えられるので、仲良し文字列になっているかどうかを判定しなさい。

## 说明/提示

### Sample Explanation 1

まず、文字列 $ A $ の`abcdef`の`a`と`f`をスワップし、`fbcdea`とします。 次に、`b`と`e`をスワップし、`fecdba`とします。 最後に、`c`と`d`をスワップし、`fedcba`とすると、文字列 $ B $ と一致します。 よって、この $ 2 $ つの文字列は、仲良し文字列となるため、`YES`と出力します。

### Sample Explanation 2

使っている文字数が同じでも、 $ 3 $ 回のスワップでは同じ文字列にできないパターンも存在します。

### Sample Explanation 3

スワップの仕方が $ 1 $ 通りしかなく、 $ 3 $ 回のスワップを繰り返すと、`tn`になってしまいます。 よって、同じ $ 2 $ つの文字列ですが、仲良し文字列ではありません。

### Sample Explanation 4

まず、 $ 1 $ 番目の文字と $ 2 $ 番目の文字を入れ替え、`qpqq`とします。 次に、 $ 3 $ 番目の文字と $ 4 $ 番目の文字を入れ替え、`qpqq`とします。この際、同じ文字を選んでいますが、場所が違うので問題ありません。 最後に、$ 1 $番目の文字と、$ 2 $番目の文字を入れ替え、`pqqq`とします。

### Sample Explanation 5

長い文字列が与えらえれることがあることにも注意してください。

## 样例 #1

### 输入

```
abcdef

fedcba```

### 输出

```
YES```

## 样例 #2

### 输入

```
abababab

babababa```

### 输出

```
NO```

## 样例 #3

### 输入

```
nt

nt```

### 输出

```
NO```

## 样例 #4

### 输入

```
pqqq

pqqq```

### 输出

```
YES```

## 样例 #5

### 输入

```
abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvxyzw

abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz```

### 输出

```
YES```

## 样例 #6

### 输入

```
abcdef

ghijkl```

### 输出

```
NO```

# AI分析结果

### 题目内容重写

#### 仲良し文字列

**题目描述**

(21:13 追记) |A|=|B|=1的ケースがテスト中に一つ含まれていましたので、リジャッジを行います。なお、このケースで`NO`を出力するプログラムに影響はありません。

字符串 $ A $ 的字符恰好通过 $ 3 $ 次交换操作可以转换为字符串 $ B $ 时，我们称这两个字符串 $ A $ 和 $ B $ 为仲良し字符串。

交换操作指的是将字符串中的两个字符进行交换。例如，对于字符串 `abc`，可以将 `a` 和 `c` 交换，得到 `cba`。

对于像 `aa` 这样的字符串，允许交换第一个 `a` 和第二个 `a`，但不能选择同一个位置的字符进行交换。

给定字符串 $ A $ 和 $ B $，请判断它们是否是仲良し字符串。

**说明/提示**

### 样例解释 1

首先，将字符串 $ A $ 的 `abcdef` 中的 `a` 和 `f` 交换，得到 `fbcdea`。接着，将 `b` 和 `e` 交换，得到 `fecdba`。最后，将 `c` 和 `d` 交换，得到 `fedcba`，与字符串 $ B $ 一致。因此，这两个字符串是仲良し字符串，输出 `YES`。

### 样例解释 2

即使使用的字符数相同，也存在无法通过 $ 3 $ 次交换操作得到相同字符串的情况。

### 样例解释 3

交换方式只有一种，经过 $ 3 $ 次交换后，字符串变为 `tn`。因此，虽然这两个字符串相同，但它们不是仲良し字符串。

### 样例解释 4

首先，交换第一个字符和第二个字符，得到 `qpqq`。接着，交换第三个字符和第四个字符，得到 `qpqq`。最后，交换第一个字符和第二个字符，得到 `pqqq`。

### 样例解释 5

注意，可能会给出较长的字符串。

### 样例 #1

**输入**

```
abcdef

fedcba
```

**输出**

```
YES
```

### 样例 #2

**输入**

```
abababab

babababa
```

**输出**

```
NO
```

### 样例 #3

**输入**

```
nt

nt
```

**输出**

```
NO
```

### 样例 #4

**输入**

```
pqqq

pqqq
```

**输出**

```
YES
```

### 样例 #5

**输入**

```
abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvxyzw

abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz
```

**输出**

```
YES
```

### 样例 #6

**输入**

```
abcdef

ghijkl
```

**输出**

```
NO
```

### 算法分类
字符串

### 题解分析与结论

题解的核心思路是通过枚举所有可能的交换组合来判断是否可以通过3次交换将字符串A转换为字符串B。对于较长的字符串，题解进行了优化，只考虑字符不同的部分，并通过填充字符来减少枚举的复杂度。

### 所选题解

#### 题解作者：RioBlu (赞：1)

**星级：4星**

**关键亮点：**
1. 对长字符串进行了优化，只处理字符不同的部分，减少了枚举的复杂度。
2. 通过填充字符确保了枚举的完整性，避免了遗漏情况。

**核心代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b,c,d,k;
int main()
{
	cin>>a>>b;
	if(a.size()>6)
	{
		for(int s=0;s<a.size();s++)
		{
			if(a[s]!=b[s])
			{
				c+=a[s];
				d+=b[s];
			}
		}
		if(c.size()>6)
		{
			puts("NO");
			return 0;
		}
		while(c.size()<6)
		{
			c+="A";
			d+="A";
		}
	}
	else
	c=a,d=b;
	for(int a1=0;a1<c.size();a1++)
	{
		for(int a2=0;a2<c.size();a2++)
		{
			for(int a3=0;a3<c.size();a3++)
			{
				for(int a4=0;a4<c.size();a4++)
				{
					for(int a5=0;a5<c.size();a5++)
					{
						for(int a6=0;a6<c.size();a6++)
						{
							if(a1==a2||a3==a4||a5==a6)continue;
							k=c;
							swap(k[a1],k[a2]);
							swap(k[a3],k[a4]);
							swap(k[a5],k[a6]);
							if(k==d)
							{
								puts("YES");
								return 0;
							}
						}
					}
				}
			}
		}
	}
	puts("NO");
	return 0; 
}
```

### 最优关键思路或技巧
1. **优化枚举**：对于长字符串，只处理字符不同的部分，并通过填充字符来减少枚举的复杂度。
2. **完整性保证**：通过填充字符确保了枚举的完整性，避免了遗漏情况。

### 可拓展之处
类似的问题可以通过枚举所有可能的交换组合来解决，尤其是在交换次数有限的情况下。对于更复杂的字符串变换问题，可以考虑使用动态规划或图论中的最短路径算法。

### 推荐题目
1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P3370 【模板】字符串哈希](https://www.luogu.com.cn/problem/P3370)
3. [P3371 【模板】最小表示法](https://www.luogu.com.cn/problem/P3371)

---
处理用时：38.88秒