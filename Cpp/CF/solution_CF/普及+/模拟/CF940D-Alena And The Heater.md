# Alena And The Heater

## 题目描述

"We've tried solitary confinement, waterboarding and listening to Just In Beaver, to no avail. We need something extreme."

"Little Alena got an array as a birthday present $ ... $ "

The array $ b $ of length $ n $ is obtained from the array $ a $ of length $ n $ and two integers $ l $ and $ r $ ( $ l<=r $ ) using the following procedure:

 $ b_{1}=b_{2}=b_{3}=b_{4}=0 $ .

For all $ 5<=i<=n $ :

- $ b_{i}=0 $ if $ a_{i},a_{i-1},a_{i-2},a_{i-3},a_{i-4}&gt;r $ and $ b_{i-1}=b_{i-2}=b_{i-3}=b_{i-4}=1 $
- $ b_{i}=1 $ if $ a_{i},a_{i-1},a_{i-2},a_{i-3},a_{i-4}&lt;l $ and $ b_{i-1}=b_{i-2}=b_{i-3}=b_{i-4}=0 $
- $ b_{i}=b_{i-1} $ otherwise

You are given arrays $ a $ and $ b' $ of the same length. Find two integers $ l $ and $ r $ ( $ l<=r $ ), such that applying the algorithm described above will yield an array $ b $ equal to $ b' $ .

It's guaranteed that the answer exists.

## 说明/提示

In the first test case any pair of $ l $ and $ r $ pair is valid, if $ 6<=l<=r<=10^{9} $ , in that case $ b_{5}=1 $ , because $ a_{1},...,a_{5}&lt;l $ .

## 样例 #1

### 输入

```
5
1 2 3 4 5
00001
```

### 输出

```
6 15
```

## 样例 #2

### 输入

```
10
-10 -9 -8 -7 -6 6 7 8 9 10
0000111110
```

### 输出

```
-5 5
```

# 题解

## 作者：流绪 (赞：2)

算是模拟?感觉把题目翻译成代码就好了
因为只要输出任意可能答案,那我们将 l 初始化为最小值 -1e9 , r 初始化为最大值 1e9,然后开始对 t 数组进行处理,为了让其下标和 a 数组的对应起来,我们在它前面加一位 0 .

怎么判断什么时候开始算 l,r 呢?

一开始没注意,直接以为必定是 00001 或 11110 的情况,就直接计算了

写题解的时候才意识到要判断前面四个相等才能开始算,可能是数据水?或者我英文没理解好....

下面是我认为的正确答案

```cpp
if(b[i-1]=='1'&&b[i-1]==b[i-2]&&b[i-2]==b[i-3]&&b[i-3]==b[i-4] && b[i]=='0')
			r=min(r,Min(a[i],a[i-1],a[i-2],a[i-3],a[i-4])-1);

```

然后计算 l,r 时,我们举例 l 的计算:

算出 a[i] 到 a[i-4] 的最大值,然后因为l大于它,且可以取任意可能的答案,那我们令 l 等于这个最大值 +1,这样既符合题意,又让答案的范围更大,避免出现后面算出了一个正确的 l 却因为前面的太大使得正确的 l 在取max 时被忽略的情况,r 的计算也是一样的道理

下面是AC代码
```cpp
#include<bits/stdc++.h>
#define inf 0x7f7f7f7f
#define Min(a,b,c,d,e) (min(a,min(b,min(c,min(d,e)))))
#define Max(a,b,c,d,e) (max(a,max(b,max(c,max(d,e)))))
using namespace std;
int a[100010];
string b;
int main()
{
    int n;
    cin >> n;
    for(int i=1;i<=n;i++) 
    	cin >> a[i];
    cin>>b;
    b="0"+b;
    int l=-1e9;
    int r=1e9;
    for(int i=5;i<=n;i++)
	{
        if(b[i]==b[i-1]) 
			continue;
        if(b[i-1]=='1' && b[i]=='0')
			r=min(r,Min(a[i],a[i-1],a[i-2],a[i-3],a[i-4])-1);
        else 
			l=max(l,Max(a[i],a[i-1],a[i-2],a[i-3],a[i-4])+1);
    }
 
    cout<< l << " "<< r;
}
```


---

## 作者：yydfj (赞：1)

**这是本蒟蒻第二十次写的题解，如有错误点请好心指出！**

## 问题简述

__这道题我们可以换另一种思路去看待它，就容易理解了：__

给你一个正整数 $n$ 和两个长度为 $n$ 的数组 $a$ 和数组 $b$，其中当 $b[i]$ 等于 $1$ 且不等于 $b[i-1]$ 时，$l>max(a[i],a[i-1],a[i-2],a[i-3],a[i-4])$；当 $b[i]$ 等于 $0$ 且不等于 $b[i-1]$ 时，$r<\min(a[i],a[i-1],a[i-2],a[i-3],a[i-4])$，问通过上述条件，$l$ 和 $r$ 分别为多少。

## 解法综述

按上述直接模拟可能会得出答案，但是需要注意以下 $3$ 点：

1. 由于数组 $b$ 在输入元素时之间没有空格，不妨将数组 $b$ 定义为字符数组，否则输入 $b$ 数组时还需要经过相对复杂的处理。

2. 由于 ${-10}^9 \leq l \leq r \leq 10^9$，为保证后面操作 $l$ 和 $r$ 有效，我们需要在开头初始化 $l$ 为 ${-10}^9$，$r$ 为 $10^9$。

3. 当遍历数组 $b$ 时，要注意在操作时可能要用到 $a[i-4]$，为保证数组不越界，我们需要使 $i$ 从 $b$ 数组第 $5$ 个元素开始遍历。


## 代码描述
```cpp
#include<cstdio>
#include<cstring>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
int n,a[100005],l=-1e9,r=1e9;//初始化l和r
char b[100005];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	scanf("%s",b+1);
	int len=strlen(b+1);
	for(int i=5;i<=len;i++)//为保证操作时a[i-4]不越界，i应从5开始遍历
	if(b[i]!=b[i-1])
	{
		if(b[i]=='1') l=max(l,max(a[i],max(a[i-1],max(a[i-2],max(a[i-3],a[i-4])))));
		if(b[i]=='0') r=min(r,min(a[i],min(a[i-1],min(a[i-2],min(a[i-3],a[i-4])))));
	}
	printf("%d %d",l+1,r-1);
	//因为l要大于符合操作的a[i]的最大值且为整数，所以最后输出l+1
	//因为r要小于符合操作的a[i]的最小值且为整数，所以最后输出r-1
	return 0;
}
```

---

## 作者：xiaozeyu (赞：1)

[CF940D Alena And The Heater](https://www.luogu.com.cn/problem/CF940D)

一道水题，不用什么算法，只要你会读题就行。

会给出两个个数组，第一个为数字，第二个为零一串。

对于第二个数组而言，如果 $b_{i}=1,b_{i-1}=b_{i-2}=b_{i-3}=b{i-4}=0$，则要满足 $a_{i},a_{i-1},a_{i-2},a_{i-3},a_{i-4}>r$。

如果 $b_{i}=0,b_{i-1}=b_{i-2}=b_{i-3}=b{i-4}=1$，则要满足 $a_{i},a_{i-1},a_{i-2},a_{i-3},a_{i-4}<l$。

其他部分都满足 $b_{i}=b_{i-1}$。

那这其实蛮简单了。

只要从第五个开始枚举，每次按照前两条规则判断第二个数组的状况，满足时改变答案即可。

因为只要满足条件的都行，那么答案的初值可以设为为左右边界。

这其实还能简化。

我们知道一旦满足前两条中的一条就不会满足最后一条，那我们其实每次只要先判断一下是否相同再判断数字类型就可以了，而不用逐一比较。

其实当数据再大很多的话可以先预处理。

代码如下。

---

c++代码。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
int read()
{
	char c=getchar();int x=0;bool f=0;
	while(!isdigit(c))f^=!(c^45),c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f)x=-x;return x;
}
const int maxn=100010;
char s[maxn];
int n,a[maxn];
int l=-1e9,r=1e9;
int main()
{
	scanf("%d",&n);
	For(i,1,n)scanf("%d",&a[i]);
	scanf("%s",s+1);
	For(i,5,n)
		if((s[i]!=s[i-1])&&(s[i-1]==s[i-2]&&s[i-3]==s[i-4]&&s[i-2]==s[i-3]))
			if(s[i]=='1')
				For(j,i-4,i) l=max(l,a[j]+1);
			else 
				For(j,i-4,i) r=min(r,a[j]-1);
	printf("%d %d",l,r);
}
```

---

python3。

```python
n = int(input())
a = list(map(int, input().split()))
b = input()
r = 1000000000
l = -r
for i in range(4, n):
  if b[i - 1] != b[i]:
    if b[i] == '0':
      r = min(r, min(a[i - 4: i + 1]) - 1)
    else:
      l = max(l, max(a[i - 4: i + 1]) + 1)
print(l, r)

```


感谢管理员的审核

---

