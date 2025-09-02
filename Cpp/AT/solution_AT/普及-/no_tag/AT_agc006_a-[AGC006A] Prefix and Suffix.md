# [AGC006A] Prefix and Suffix

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc006/tasks/agc006_a

すぬけ君は次の条件を満たす文字列に興味があります。

- 長さ $ N $ 以上である。
- 先頭 $ N $ 文字が文字列 $ s $ に一致する。
- 末尾 $ N $ 文字が文字列 $ t $ に一致する。

条件を満たす文字列のうち、最も短いものの長さを求めてください。

## 说明/提示

### 制約

- $ 1\ <\ =N\ <\ =100 $
- $ s $, $ t $ は長さ $ N $ である。
- $ s $, $ t $ は英小文字のみからなる。

### Sample Explanation 1

最も短い文字列は `abcde` です。

### Sample Explanation 2

最も短い文字列は `az` です。

### Sample Explanation 3

最も短い文字列は `expr` です。

## 样例 #1

### 输入

```
3
abc
cde```

### 输出

```
5```

## 样例 #2

### 输入

```
1
a
z```

### 输出

```
2```

## 样例 #3

### 输入

```
4
expr
expr```

### 输出

```
4```

# 题解

## 作者：Karry5307 (赞：4)

### 题意

给定两个长度为 $n$ 的字符串 $s,t$，求最短字符串的长度使得其前缀为 $s$ 且后缀为 $t$。

$\texttt{Data Range:}1\leq n\leq 100$

### 题解

没意思的小水题，可以加强到 $n=10^6$。（为什么任务计划给我推这个啊）

问题等价于求最长的字符串的长度使得其为 $s$ 的后缀且为 $t$ 的前缀。

但是暴力匹配是 $O(n^2)$ 的，考虑使用哈希优化。

记录 $s$ 每一个后缀的哈希值和 $t$ 每一个前缀的哈希值，枚举一下即可。

时间复杂度 $O(n)$。（如果在求后缀哈希值的时候用的快速幂就是 $O(n\log n)$ 的了）

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51,MOD=998244353;
ll length;
ll pw[MAXN],prefix[MAXN],suffix[MAXN];
char s[MAXN],t[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
int main()
{
	length=read(),scanf("%s%s",s,t),pw[0]=1,prefix[0]=t[0]-'a';
	for(register int i=1;i<length;i++)
	{
		pw[i]=(li)pw[i-1]*26%MOD;
		prefix[i]=(t[i]-'a'+(li)prefix[i-1]*26%MOD)%MOD;
	}
	for(register int i=length-1,j=0;i>=0;i--,j++)
	{
		suffix[i]=(suffix[i+1]+(li)pw[j]*(s[i]-'a')%MOD)%MOD;
	}
	for(register int i=0,j=length-1;i<length;i++,j--)
	{
		if(suffix[i]==prefix[j])
		{
			return printf("%d\n",(length<<1)-j-1),0;
		}
	}
	printf("%d\n",length<<1);
}
```

---

## 作者：Super_Cube (赞：1)

# 题目大意：

给你两个长度为 $n$ 的字符串 $x$ 和 $y$，现在希望你能构造出一个满足前缀是 $x$，后缀是 $y$ 的最短字符串长度。（关于判断前后缀是可以重合的）

---

# 思路：

首先，一个形如 $xy$ 的拼接字符串肯定是能够满足题目要求的，答案为 $2n$。

但这肯定不是最优的，如同样例一，两个字符串为`abc`和`cde`，直接构造的话应为`abccde`，可此时的最短字符串应为 `abcde` ，长度为 $5$。

你会惊奇地发现差距其实就在中间可以重合的部分是可以省略掉的！

所以这题的思路就出来啦，把 $x$ 字符串的后面部分和 $y$ 字符串的前面部分能重合在一起的地方统计一下，最后答案就是 $2n$ 减去重合部分的长啦。

至于怎么统计就看下方的代码吧，有注释。

时间复杂度: $O(n^2)$。

顺带一提那篇 $O(n)$ 的题解是错的哦，可以被 hack 掉，hack 样例已经有人评论了。

---

# Code：

```cpp
#include<stdio.h>
char a[105],b[105];
int n,t,i,j,k;
int main(){
	scanf("%d\n%s\n%s",&n,a,b);
	for(i=0;i<n;++i){
		k=i;j=0;
		while(k<n&&a[k]==b[j])++k,++j;//开始寻找重合部分
		if(k==n&&t<j)t=j;//能找到就更新最大值
	}printf("%d",(n<<1)-t);
	return 0;
}
```

---

## 作者：猜一猜我是谁 (赞：0)

# 思路
这题用简单的暴力其实就能过了。

我们只需计算出 $s$ 的末尾与 $t$ 的开头重合的地方，结果为 $2\times n-\text{重合部分长度}$。

而关键就在如何求出重合部分的长度。

我们可以枚举第一个字符串中的各位，如果发现 $s[i]=t[0]$，那么枚举第二个字符串，**如果从 $s[i]$ 到 $s[n-1]$ 一直与 $t[0]$ 到 $t[j-i]$ 重合，才可将重合长度设为 $n-i$。**

详细见代码。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,cnt=0;
    bool f;
    string s,t;
    cin>>n>>s>>t;
    for(int i=0;i<n;i++){
        f=1;
        if(s[i]==t[0]){//如果发现当前位置与 t 的首位相同
            for(int j=i+1;j<n;j++)//从 s[i+1] 到 s[n-1] 依次枚举
                if(s[j]!=t[j-i]) f=0;
	        if(!f) continue;//不满足条见就结束本次循环（不是退出）
	        cnt=n-i;
	        break;
        }
    }
    cout<<2*n-cnt;
}
```
完结撒花~~~

---

