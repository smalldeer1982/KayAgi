# Captain Flint and a Long Voyage

## 题目描述

若有一个 $n$ 位正整数 $x$，定义 $k$ 的值为将 $x$ 的每一位上的数字转换为二进制（不含前导 $0$）。比如 $x=729$ 时，$k=111101001$。将 $k$ 的后 $n$ 位截去得到 $r$。比如 $x=729$ 时，$r=111101$。

现在给定 $n$，你需要找到 $r$ 最大时 $x$ 的最小值。

## 说明/提示

$1\le t\le1000$，$1\le n\le 10^5$。

数据保证所有数据中的 $n$ 之和不超过 $2\times10^5$。

Translated by [cmll02](https://www.luogu.com.cn/user/171487).

## 样例 #1

### 输入

```
2
1
3```

### 输出

```
8
998```

# 题解

## 作者：LRL65 (赞：1)

~~我感觉B貌似比A简单一点？~~

~~考场上很快就过了这题。~~


------------
大概内容：

有一个 $n$ 位的数，将它每一位转换成二进制再组合在一起，如：$729$，就转化为 $111101001(7=111,2=10,9=1001)$。

然后再截去最后n位，最后要使得这个数最大。求满足条件最小的 $n$ 位数。

就比如 $729$，转化为 $111101001$ 后，截去 $3$ 位，就是 $111101$，所以729最后就会变为 $111101$。



------------
思路：

要想最大，**那么数位首先得最多**。$9$ 二进制为 $1001$，$8$ 二进制为 $1000$，$7$ 二进制为 $111$ ……从 $7$ 开始就是 $3$ 位了，所以应该从 $9$ 和 $8$ 中选。

题目中要求最小的，**所以应该尽量多用 $8$**。那么什么时候可以用 $8$ 呢？当这 $4$ 位中的最后一位被截去时，它们就变成一样的了，都变成了 $100$。**所以截去几个最后一位，就用几个 $8$**。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;
int main(){
    cin>>t;
    while(t--) {
        cin>>n;
        for(int i=1;i<=n-(n-1)/4-1;i++)cout<<9;//一个奇怪的式子，大家举例理解一下，其中(n-1)/4+1是8的个数
        for(int i=1;i<=(n-1)/4+1;i++)cout<<8;
        cout<<endl;
    }
    return 0;
}
```





---

## 作者：fls233666 (赞：1)

题意简述：

给出正整数 $n$ ,求一个最小的 $n$ 位数字，要求这个数字转化成二进制并删掉最后 $n$ 位时，得到的二进制数最大。

--------

考虑到要让最后得到的二进制数最大，显然，**剩下的二进制数的数位越多越好**。

那么，观察 $1$ 到 $9$ 这些数字，我们发现二进制位数最多的数字只有 $8$ 和 $9$，它们的二进制形式分别为 $1000$ 和 $1001$。

进一步考虑如何填这 $n$ 位数字。我们发现，**为了让二进制结果最大，我们可以在不用被删掉的数位上填 $9$。又为了让这个数字最小，我们可以在要被删掉的数位上填 $8$** 。于是我们就填完了这 $n$ 位数字，得到了答案。

最后要注意，一个 $8$ 会占掉 $4$ 个二进制位，实现代码时要注意一些细节问题。

下面是本题的代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define rgt register int
using namespace std;
const int mxn = 2e5+5;
int n,g;
char ans[mxn];
int main(){
	int test;
	scanf("%d",&test);
	while(test--){
		scanf("%d",&n);
		g=n/4;  //计算要被删掉的数位
		memset(ans,'8',sizeof(ans));  //先全部默认填8
		for(rgt i=1;i<=n-g;i++)
			ans[i]='9';   //把不用被删的数位填9
		if(n%4)
			ans[n-g]='8';  //根据余数处理细节
		for(rgt i=1;i<=n;i++)
			printf("%c",ans[i]);   //得到答案
		printf("\n");
	}
	return 0;
}
```


---

## 作者：HC20050615 (赞：0)

# 题意分析
求一个最小的n位数字，使其转化成二进制并删掉最后n位时最小
# 思路
让一个数越大，首先要使其最长。在数字中只有8、9表示为2进制后为四位，所以本题这个n位数字上的每一位我们只考虑8、9.

那什么时候是8，什么时候是9呢？

因为我们知道8=1000、9=1001，当8、9删去末尾一位及以上时，两者的大小是相等的。所以我们使会被删到的位数上填8（使x尽可能小），不会删到的填9（使r尽可能大）

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin>>T;
	for(int t=1;t<=T;t++)
	{
		int n;
		cin>>n;
		int cnt=(n+3)/4;
		for(int i=1;i<=n-cnt;i++)
		{
			cout<<9;
		}
		for(int i=1;i<=cnt;i++)
		{
			cout<<8;
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：白鲟 (赞：0)

## 前言
安利自己首场 CF 的[游记](https://www.luogu.com.cn/blog/PsephurusGladius-zdx/codeforces-round-660-div-2-post)（其实啥也没写）。

## 题目分析
跟 A 题难度差不多，感觉放在 B 题会让人做 C 题的时候心态爆炸（比如我）。  

题目是把一个 $n$ 位数的每一位的二进制表示连起来作为新数，然后删掉这个数的后 $n$ 位，问删去后的数最大时原数的最小值。由于原数每一位只能是一位整数，且仅有 $8,9$ 的二进制表示占四位，又有位数更多的数一定更大，容易得知原数中仅有 $8,9$ 两种数字。  

若没有删去这一操作，原数一定只由 $9$ 组成。会出现 $8$ 是由于它在删去末尾 $n$ 位后在一些时候与 $9$ 是等价的。更具体地，对于每四位二进制数，当它的末位被删去时，它对应 $8$ 或 $9$ 是等价的，这时我们就将这一位取为 $8$。计算出有多少个这样的情况，就能知道 $8$ 与 $9$ 分别的个数了。

## 代码
```cpp
#include<cstdio>
using namespace std;
int T,n;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		int num_8=n/4+(n%4>0);
		for(int i=1;i<=n-num_8;++i)
			putchar('9');
		for(int i=1;i<=num_8;++i)
			putchar('8');
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：KSToki (赞：0)

首先为了让最后的$r$最大，那么就应让$r$最长。~~（这不废话么）~~

一位数的二进制中，仅有$9$的二进制$1001$和$8$的二进制$1000$是四位，所以很自然想到用$9$和$8$来构造$x$，且在构造时$r$不变的情况下用的$8$尽量多。

因为最后会去掉结尾的$n$位，那么最后$n$位的$1$越少越好，即用$8$填充，所以我们最后的输出是$999…98…888$。

接下来只需要推一波$8$的个数与$n$与$4$的关系的关系即可。~~（好绕啊）~~

代码很简单啦：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(register int i=1;i<=n-(n-1)/4-1;++i)
		    printf("9");
		for(register int i=1;i<=(n-1)/4+1;++i)
		    printf("8");
		printf("\n");
	}
	return 0;
}
```


---

## 作者：do_while_true (赞：0)

显然 $9,8$ 是最优的两个数（二进制 $1001,1000$ )，初始全 $9$，看 $n$ 能覆盖到几个 $9$ 的最后一位，能覆盖就说明这个 $9$ 是不必要的，改成 $8$ 更优，把那些改为 $8$ 即可。

具体多少可以自己手推。


[$\mathcal{Code}$](https://codeforces.com/contest/1388/submission/88460406)
```cpp
#include<iostream>
#include<cstdio>
int T,n;
int main()
{
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		for(int i=1;i<=n-(n-1)/4-1;i++)
			printf("9");
		for(int i=1;i<=(n-1)/4+1;i++)
			printf("8");
		puts("") ;
	}
}
```

---

## 作者：wmy_goes_to_thu (赞：0)

只有 $9$ 和 $8$ 位数多，是 $4$ 位，剩下的都很小，故不选，只选 $8$ 和 $9$。

$8$ 和 $9$ 唯一的区别是最后一位，所以去掉后边任意为都无区别。所以如果这一个数会被去掉几位，那么就选 $8$，否则选 $9$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		int r=(n-1)/4+1;
		for(int i=1;i<=n-r;i++)printf("9");
		for(int i=1;i<=r;i++)printf("8");
		puts("");
	}
	return 0;
}
```

---

## 作者：MyukiyoMekya (赞：0)

9 的二进制是 `1001` ，8 的二进制是 `1000` ，到了 7 就变成 `111`，为了让新数字更大，肯定只能用9和8

然后会发现如果把最后的 k 位覆盖掉，那么就是原数字的后 $\lceil \frac k4 \rceil$ 位的后面会有一些位数“失效”，然后只要 `1001` “失效”了后任意位，那就和 `1000` 一样了，因为要使得原数字最小，我们要让前 $n-\lceil \frac n4 \rceil$ 位数字弄成 `9` ，后面的都弄成 8 即可

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
using namespace std;
template <class t> inline void read(t &s)
{
	s=0;
	reg int f=1;
	reg char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(isdigit(c))
		s=(s<<3)+(s<<1)+(c^48),c=getchar();
	s*=f;
	return;
}
inline void work()
{
	int n;cin>>n;
	int g=(n/4)+(((n%4)>0)?1:0);
	for(int i=1;i<=n-g;++i)
		putchar('9');
	for(int i=1;i<=g;++i)
		putchar('8');
	puts("");
	return;
}
signed main(void)
{
	int t;cin>>t;
	while(t--)
		work();
	return 0;
}
```



---

