# Number Base Conversion

## 题目描述

编写一个程序，将一个进制中的数字转换为另一个进制中的数字。有 $62$ 个不同的数字：

${ 0\sim 9, A\sim Z,a\sim z }$

提示：如果你连续进行一系列的进制转换，将一个转换的输出作为下一个转换的输入，当你回到原始的进制时，你应该得到原始的数字。

## 样例 #1

### 输入

```
8
62 2 abcdefghiz
10 16 1234567890123456789012345678901234567890
16 35 3A0C92075C0DBF3B8ACBC5F96CE3F0AD2
35 23 333YMHOUE8JPLT7OX6K9FYCQ8A
23 49 946B9AA02MI37E3D3MMJ4G7BL2F05
49 61 1VbDkSIMJL3JjRgAdlUfcaWj
61 5 dl9MDSWqwHjDnToKcsWE1S
5 10 42104444441001414401221302402201233340311104212022133030```

### 输出

```
62 abcdefghiz
2 11011100000100010111110010010110011111001001100011010010001

10 1234567890123456789012345678901234567890
16 3A0C92075C0DBF3B8ACBC5F96CE3F0AD2

16 3A0C92075C0DBF3B8ACBC5F96CE3F0AD2
35 333YMHOUE8JPLT7OX6K9FYCQ8A

35 333YMHOUE8JPLT7OX6K9FYCQ8A
23 946B9AA02MI37E3D3MMJ4G7BL2F05

23 946B9AA02MI37E3D3MMJ4G7BL2F05
49 1VbDkSIMJL3JjRgAdlUfcaWj

49 1VbDkSIMJL3JjRgAdlUfcaWj
61 dl9MDSWqwHjDnToKcsWE1S

61 dl9MDSWqwHjDnToKcsWE1S
5 42104444441001414401221302402201233340311104212022133030

5 42104444441001414401221302402201233340311104212022133030
10 1234567890123456789012345678901234567890```

# 题解

## 作者：forever_nope (赞：5)

进制转换板子题，下面是前置知识，

### 任意进制转化为十进制

简单的，

$$
(\alpha_1\alpha_2\cdots\alpha_n)_k=\sum_{i=1}^n\alpha_ik^{n-i}
$$

算法实现，即秦九韶算法，

+ 顺序考虑原数每一位，记前 $i$ 位答案位 $e_i$，
+ $e_i=ke_{i-1}+\alpha_i$，迭代即可。

### 十进制转化为任意进制

短除法，

+ 原数，不断除以目标进制 $k$，所得商、余数：
+ 商，作为下一轮的被除数，
+ 余数，作为结果的一位。

不断进行上述操作，所得结果序列，逆序，即目标数。

### 任意进制之间的转化

假设我们要把 $p$ 进制数转化为 $q$ 进制数。

于是，我们可以把原数，在 $p$ 进制下除以 $q$。

不断迭代，类似上面的。

类比十进制下的除法，我们进位的时候需要乘上 $p$ 而不是 $10$，很显然。

具体做法：

+ 原数的每一位，加上上面的进位，除以 $q$，所得商、余数：
+ 商，作为下一轮的被除数的一部分，对于每一位，乘上 $p$ 记为进位。
+ 余数：作为结果中的一位。

然后就是模拟了，

```cpp
#include <bits/stdc++.h>

using namespace std;

int id(char c) {
	if (isdigit(c)) return c - '0';
	if (isupper(c)) return c - 'A' + 10;
	if (islower(c)) return c - 'a' + 10 + 26;
	exit(1);
}

char rnk(int k) {
	if (k < 10) return k + '0';
	if (k < 36) return k - 10 + 'A';
	if (k < 62) return k - 36 + 'a';
	exit(1);
}

void solev() {
	int k1, k2; string s; cin >> k1 >> k2 >> s;
	basic_string<int> n(s.size(), 0), r;
	for (int i = 0; i < s.size(); ++i) n[i] = id(s[i]);
	while (n.size()) {
		basic_string<int> e(n.size(), 0);
		int lt = 0;
		for (int i = 0; i < n.size(); ++i) {
			int c = n[i] + lt * k1;
			e[i] = c / k2, lt = c % k2;
		}
		n = e; r.push_back(lt);
		while (n.size() && n[0] == 0) n.erase(n.begin());
	}
	reverse(r.begin(), r.end());
	cout << k1 << " " << s << endl;
	cout << k2 << " ";
	for (int i : r) cout << rnk(i);
	cout << endl << endl;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int T; cin >> T;
	while (T--) solev();
	return 0;
}
```

---

## 作者：XT_HuangQuan (赞：0)

[题目传送门。](https://www.luogu.com.cn/problem/P10462)

这个题目的主要思路就是如何再进制之间相互转换，我就简单讲一下思路：

假设我们要把一个 $n$ 进制数 $k$ 转化成一个 $m$ 进制数：

1. 用 $k$ 除以 $m$，记余数为 $a$，商为 $b_1$ 并存下来。
2. 用 $a$ 再次除以 $m$，再次把 $b_2$ 存下来。

......直到 $a=0$。

3. 把 $b$ 数组倒着存成一个数。

**就做完了**。

 **但是**：进位的时候**一定一定**要乘上 $m$ 而不是  **$10$**。~~别问我是怎么知道的，问就是改了半个小时才发现。~~

好啦，接下来就是愉快的代码环节。
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int T,n,m,f[128],ff[62];
char a[1005],stk[1005]; int sz=0;
int main()
{
#ifdef local
	freopen("pro.in","r",stdin);
#endif
	int cnt=0;
	for(int i='0';i<='9';i++)
	{
		f[i]=cnt;
		ff[cnt++]=i;
	}
	for(int i='A';i<='Z';i++)
	{
		f[i]=cnt;
		ff[cnt++]=i;
	}
	for(int i='a';i<='z';i++)
	{
		f[i]=cnt;
		ff[cnt++]=i;
	}
	scanf("%d",&T);
	while(T-->0)
	{
		scanf("%d%d%s",&n,&m,a);
		printf("%d %s\n%d ",n,a,m);
		int lena=strlen(a);
		reverse(a,a+lena);
		sz=0;
		while(lena)
		{
			int jw=0;
			for(int i=lena-1;i>=0;i--)
			{
				jw=jw*n+f[a[i]];
				a[i]=ff[jw/m];
				jw%=m;
			}
			stk[sz++]=ff[jw];
			while(lena&&a[lena-1]=='0') a[lena--]=0;
		//	printf("lena=%d %s\n",lena,a);
		}
		while(sz) putchar(stk[--sz]); puts("\n");
	}
	return 0;
}
```
## 有一些相关的练习题目：
- [10 进制转 $x$ 进制。](https://www.luogu.com.cn/problem/B3619)
- [$x$ 进制转 10 进制。](https://www.luogu.com.cn/problem/B3620)
- [进制位。](https://www.luogu.com.cn/problem/P1013)  
这道稍微难一点。
- [二进制。](https://www.luogu.com.cn/problem/P4428)  
这道仅献给 dalao。

大功告成！

题解仅供学习，请不要  ctrl+c，ctrl+v。

 部分灵感来源于[此处。](https://www.luogu.com.cn/article/77v1xpam)

---

## 作者：Norsuman371 (赞：0)

看见题目第一反应是转成 10 进制，但是这样时间复杂度还是 $O(n^{2})$，还很麻烦，就直接切换了吧。

## 思路

从该数的最高位开始，对该位上的数除以要**转换的进制基数**，得到商和余数，商取代原来该位上的数，下一位通过**余数乘以大数的进制基数加上该位的数**进行相同操作，直到所以位都除过一次，记录最后一位操作得到的余数，然后将上次的商作为除数，重复直到商为零。最后**逆序输出**每次记录的余数。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T, n, m, l[128], l2[62];
char a[1005], stk[1005];
int sz = 0;
int main() {
    int cnt = 0;
    for(int i = '0'; i <= '9'; i++) {
        l[i] = cnt;
        l2[cnt++] = i;
    }
    for(int i = 'A'; i <= 'Z'; i++) {
        l[i] = cnt;
        l2[cnt++] = i;
    }
    for(int i = 'a'; i <= 'z'; i++) {
        l[i] = cnt;
        l2[cnt++] = i;
    }
    scanf("%d", & T);
    while (T-- > 0) {
        scanf("%d%d%s", & n, & m, a);
        printf("%d %s\n%d ", n, a, m);
        int lena = strlen(a);
        reverse(a, a + lena);
        sz = 0;
        while (lena) {
            int jw = 0;
            for(int i = lena - 1; i >= 0; i--) {
                jw = jw * n + l[a[i]];
                a[i] = l2[jw / m];
                jw %= m;
            }
            stk[sz++] = l2[jw];
            while (lena && a[lena - 1] == '0') {
                a[lena--] = 0;
            }
        }
        while (sz) {
            putchar(stk[--sz]);
        }
        puts("\n");
    }
    return 0;
}
```

## 记录

<https://www.luogu.com.cn/record/159702452>

## 鸣谢

本题解部分参见 <https://www.cnblogs.com/happyZYM/p/11379608.html>

---

