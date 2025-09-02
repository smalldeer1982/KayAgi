# Message Transmission Error (hard version)

## 题目描述

这是一个难度较高的问题。它与简单版的区别仅在于约束条件不同。

在伯兰州立大学，服务器之间的本地网络并非总是运行无误。当连续传输两条相同的信息时，可能会发生错误，导致两条信息合并为一条。在这种合并中，第一条信息的结尾与第二条信息的开头重合。当然，合并只能发生在相同字符处。合并的长度必须是一个小于信息文本长度的正数。

例如，当连续传送两条信息```abrakadabra```时，可能会出现所述类型的错误、导致出现类似```abrakadabrakadabra```或```abrakadabrakadabra```的信息(前者在一个字符处发生合并，后者在四个字符处发生合并)。

给定接收到的报文 ```t``` ，判断这是否可能是本地网络运行中出现所述类型错误的结果，如果是，请确定可能的值 ```s``` 。

两个报文完全重叠的情况不应视为错误。例如，如果收到的报文是```abcd```，则应认为其中没有错误。同样，简单地在一条信息后附加另一条信息也不是错误的标志。例如，如果收到的信息是 ```abcabc```，也应认为其中没有错误。

## 样例 #1

### 输入

```
abrakadabrabrakadabra```

### 输出

```
YES
abrakadabra```

## 样例 #2

### 输入

```
acacacaca```

### 输出

```
YES
acacaca```

## 样例 #3

### 输入

```
abcabc```

### 输出

```
NO```

## 样例 #4

### 输入

```
abababab```

### 输出

```
YES
ababab```

## 样例 #5

### 输入

```
tatbt```

### 输出

```
NO```

# 题解

## 作者：2023nsty04 (赞：2)

## 题意
给定一个字符串 $s$。求是否存在字符串 $t$ 既是 $s$ 的前缀又是 $s$ 的后缀，且 $t$ 的长度大于 $s$ 的一半。

## 思路

我们可以建一个 $next$ 数组，记 $next_{i}$ 为字符串前 $i$ 个字符的最长公共前后缀，最后将 $next_{k}$ 与 $k/2$ 进行比较就可以了（$k$ 是字符串的长度）。

对于 $next$ 数组，我们可以采用类似于动态规划的思想。

- 若当前字符与之前匹配上的前缀下一位匹配，则 $next_{i}=next_{i-1}+1$ 

- 若当前字符与之前匹配上的前缀下一位失配了，则至少要往前跳多少步，才可能重新匹配得上。

- 
## 为什么？

因为记 $next_{i}$ 为字符串前 $i$ 个字符的最长公共前后缀，那么 $next_{k}$ 就是整个字符串最长公共前后缀，若 $next_{k}$ 大于 $k/2$，就说明 $t$ 的长度大于 $s$ 的一半，符合题意。


## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
int n[400010]={0};
int main()
{
	cin>>a;
	int ak=a.size();
	for(int i=1,len=0;i<ak;i++)
	{
		while(len&&a[i]!=a[len])len=n[len-1];
		if(a[len]==a[i])len++;
		n[i]=len;
	}
	if(n[ak-1]>ak/2)
	{
		cout<<"YES"<<endl;
		string s(a,0,n[ak-1]);
		cout<<s;
	}
	else cout<<"NO";
	return 0;
 } 
```

---

## 作者：cly312 (赞：2)

先用 KMP 求出 $t$ 的最长公共前后缀长度，设 $t$ 的最长公共前后缀长度为 $k$，如果 $2\cdot k$ 大于 $t$ 的长度，那么 $t$ 中就有错误，原串就是从 $t$ 的最长公共前后缀。

证明：如果 $2\cdot k$ 大于 $t$ 的长度，那么就说明 $t$ 的最长公共前后缀有相交的部分，那么相交处就为原串发生合并的地方，原串也就是从 $t$ 的最长公共前后缀。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int nxt[400000];
int main(){
	int n,i,j;
	cin>>s;
	n=s.length();
	nxt[0]=0;
	j=0;
	for(i=1;i<n;i++){
		while(j>0&&s[i]!=s[j])j=nxt[j-1];
		if(s[i]==s[j])j++;
		nxt[i]=j;
	}
	if(nxt[n-1]*2>n)
		cout<<"YES\n"<<s.substr(0,nxt[n-1])<<'\n';
	else cout<<"NO\n";
	return 0;
}
```

---

## 作者：Super_Cube (赞：2)

# Solution

枚举重合长度 $i\in[1,n)$，原串长应为 $m=\dfrac{n+i}{2}$，取出给定串的区间 $[1,m]$ 与区间 $[n-m+1,n]$ 进行比较，若相等则 $[1,m]$ 就是原串。找不到则无解。

利用哈希判断字符串相等，注意自然溢出会被 hack。

---

## 作者：wawatime1 (赞：1)

### 思路
可以暴力枚举，但时间复杂度 $O(n^2)$，超时。

先求出 $s$ 的最长公共前后缀长度，记作 $t$，如果 $k \times 2 > s$ 的长度，原串就是从 $s$ 的最长公共前后缀。

### 为什么？
当 $2 \times t > s$ 串的长度时，那么就说明 $s$ 的最长公共前后缀有相交的部分，相交处就为原串发生合并的地方，原串也就是从 $s$ 的最长公共前后缀。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, d, ans, a[100005];
int main() {
	scanf ("%d%d", &n, &d);
	for (int i = 1; i <= n; i++) scanf ("%d", &a[i]);
	for (int i = 1; i <= n; i++) {
		int l = lower_bound (a + 1, a + 1 + n, a[i] - d) - a, r = upper_bound (a + 1, a + 1 + n, a[i] + d) - a - 1;
		ans += (3 * i - 2 * l - r + 1) * (r - i) / 2;
	}
	printf ("%d\n", ans);
	return 0;
}
```

---

## 作者：SuyctidohanQ (赞：0)

### 题目分析

暴力枚举为 $O(n ^ 2)$，显然超时。

首先求出 $s$ 的最长公共前后缀长度，在这里我们令变量 $a$ 为 $s$ 的最长公共前后缀长度。

如果 $2 \times a$ 这个数值大于 $s$ 的长度，那么原串就是从 $s$ 的最长公共前后缀。

### 代码实现

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll MAXN = 4e5 + 10;
string s;
ll shu[MAXN] = {0}, len, cun = 0;
int main () {
	cin >> s;
	len = s.size ();
	for (ll i = 1; i <= len - 1; i ++) {
		while (cun > 0 && s[i] != s[cun]) cun = shu[cun - 1];
		if (s[i] == s[cun]) cun ++;
		shu[i] = cun;
	}
	if (shu[len - 1] * 2 > len) cout << "YES" << endl << s.substr (0, shu[len - 1]) << endl;
	else cout << "NO" << endl;
	return 0;
}
```

---

## 作者：abc1856896 (赞：0)

水题。建议降橙。

# Solution

显然可以直接暴力字符串的长度，再判断前后是否相等。但这样的时间复杂度是 $O(n^2)$。

瓶颈在判断相等，上哈希判断即可。

---

