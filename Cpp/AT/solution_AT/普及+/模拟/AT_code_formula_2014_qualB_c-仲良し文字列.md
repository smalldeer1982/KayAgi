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

# 题解

## 作者：RioBlu (赞：1)

翻译：
```
有两个字符串A,B

请对A字符串进行3次交换操作

1次交换操作是指：

* 选定2个下标i,j保证i≠j且0≤i,j<|A|（i,j小于A的长度）

* swap(A[i],A[j])（A[i]与A[j]交换）

请问在交换操作后，如果A可以变成B，那么输出YES

否则输出NO

其中|A|=|B|,|A|<=1000
```
___
其实，本题可以进行优化：如果$|A|>6$时

我们可以统计$A$与$B$不同的内容，放入$C,D$（参考代码）

如果不同串$C,D$的长度大于$6$，那么肯定怎么样都交换不出来

如果不同串$C,D$的长度小于$6$，那么直到$C,D$的长度等于$6$时一直在$C,D$末尾放$A$

> 那为什么要放A呢？

> 其实举个例子就知道了：$abcdef$ 和 $bacdef$

> $C="ab",D="ba"$

> 这样无法完成，C无法交换成D，但原数据是可以的，所以要不断加A
___
```
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

---

