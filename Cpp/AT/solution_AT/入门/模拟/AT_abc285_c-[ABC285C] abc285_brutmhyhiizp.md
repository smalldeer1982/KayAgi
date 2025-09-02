# [ABC285C] abc285_brutmhyhiizp

## 题目描述

在另一个世界的 AtCoder 举办的 AtCoder Big Contest 中，一次性会出 $10^{16}$ 道题目。  
题目的 ID 从第 $1$ 题开始依次为 `A`、`B`、...、`Z`、`AA`、`AB`、...、`ZZ`、`AAA`、... 这样排列。

也就是说，ID 的分配顺序如下：

- 按照字典序排列的所有长度为 $1$ 的大写英文字母字符串
- 按照字典序排列的所有长度为 $2$ 的大写英文字母字符串
- 按照字典序排列的所有长度为 $3$ 的大写英文字母字符串
- $...$

现在给定一个属于本次比赛的题目 ID 字符串 $S$，请你回答它是第几道题。

## 说明/提示

## 限制

- $S$ 是 AtCoder Big Contest 中合法的题目 ID

## 样例解释 1

ID 为 `AB` 的题目是 AtCoder Big Contest 的第 $28$ 题。

## 样例解释 2

ID 为 `C` 的题目是 AtCoder Big Contest 的第 $3$ 题。

## 样例解释 3

ID 为 `BRUTMHYHIIZP` 的题目是 AtCoder Big Contest 的第 $10^{16}$ 题，也就是最后一题。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
AB```

### 输出

```
28```

## 样例 #2

### 输入

```
C```

### 输出

```
3```

## 样例 #3

### 输入

```
BRUTMHYHIIZP```

### 输出

```
10000000000000000```

# 题解

## 作者：lwx20211103 (赞：4)

## 题目大意

给你一个字符串 $S$，求这个字符串在字典中的排列。

如果不明白这是什么意思，可以看这张图
![](https://cdn.luogu.com.cn/upload/image_hosting/zdbnxx83.png)

就是求字符串在 excel 表格里面在单元格列的字母编号的第几个位置，但如果位置过大，超过了 $10^{16}$ 就输出 $10^{16}$。比如 `AB` 就是第 $28$ 列，`C` 就是第 $3$ 列。我们理解题意之后，就可以做了。

后来根本不用去判断是否超过 $10^{16}$，数据挺水的，一样能过。

## 题目分析

我们看到这个，就可以想，能不能把字符串看作一种数字，$26$ 进制的数字？

对的，于是第一种稍微复杂的做法，模拟进制转换，就有了。我们可以把整个求解的过程看作 $26$ 进制的数字转换成 $10$ 进制的数字。

我从 $0$ 开始索引字符串，记字符串长度 $|S|$ 为 $L$ 那么**从后往前**遍历字符串到 $i$ 时，从后往前进制转换，指数就是 $L - i - 1$，这样我们就能推出公式：

$$ans = {S_i \times 26^{L - i - 1}}$$

当然要注意的是，我们要把字符串转换为数组，$A=1,B=2...$ 这样转换。

```cpp
for (int i = 0; i < len; i++)//len:the size of S
{                      
     nums[i] = s[i] - 'A'+ 1;
}
```

这样，代码就可以出来了。

```cpp
#include <bits/stdc++.h> //I AK IOI.
using namespace std;

int nums[1 << 21];

long long qpow(long long a, long long b)
{
	long long ans = 1;
	while (b)
	{
		if (b & 1)
		{
			ans *= a;
			b--;
		}
		else
		{
			b >>= 1;
			a *= a;
		}
	}
	return ans;
}

long long sum;

int main()
{
	string s;
	cin >> s;
	int len = s.size();
	for (int i = 0; i < len; i++)
	{
		nums[i] = s[i] - 'A' + 1;
	}
	for (int i = len - 1;i >= 0;i--)
	{
		sum += 1ll * nums[i] * qpow(26, len - i - 1);
		if (sum >= (long long)(1e16))
		{
			cout << (long long)(1e16);
			return 0;
		}
	}
	//cout << "\n";
	cout << sum;
	return 0;
}
```

这是第一种解法，通过这个，我们可以 AC 本题目了，但是在赛后，一位大佬告诉了更简单的算法。原理也是进制转换。因为我们知道，写快读的时候，代码差不多是这样，`x = x * 10 + c - '0'`，这样使读入的字符串组合起来变成我们想要的数字，那么因为这是字母，我们就可以写成 `x = x * 26 + c - 'A' + 1`，于是，代码就出来了。

```cpp
#include <bits/stdc++.h> //I AK IOI.
using namespace std;

long long ans;

int main()
{
	string s;
	cin >> s;
	for (auto &&i : s)
	{
		ans = ans * 26 + (i - 'A' + 1);
	}
	cout << ans;
	return 0;
}

```

谢谢观看！

---

## 作者：Lyu_echo (赞：2)

## 题目大意

有一些字符串，其字典序如下：

`A`, `B`, ..., `Z`, `AA`, `AB`, ..., `ZZ`, `AAA`, ...

(和 Excel 横行的字母顺序一致。)

给定其中一个字符串，问其字典序。

## 解题思路

可以理解为 26 进制数转 10 进制。

- 当当前位没有字符时，为 0
- 否则，当前位为单个字符在 `A-Z` 中的字典序，从 1 开始

再转换为 10 进制即可。

## 代码实现

``` cpp
void solve() {
    string s;
    int ans = 0;
    cin >> s;
    int t[s.length()] = {0};
    
   	for (int i = 0; i < s.length(); i++) {
        t[i] = s[i] - 'A' + 1; //转换为 26 进制数
    }
    for (int i = 0 ; i < s.length(); i++) {
        ans = ans * 26 + t[i];  //再转换为 10 进制数
    }
    cout << ans << endl;
    
    return ;
}
```





---

## 作者：Kingna (赞：1)

## 题目大意
一串序列 `A`, `B`, ..., `Z`, `AA`, `AB`, ..., `ZZ`, `AAA`,... 给定一个字符串求在序列中的排名（保证存在）
## 思路
将每个 `A` 看作 $1$，`B` 看作 $2$，....，`Z` 看作 $26$。

那么就可以看作为一个 $26$ 进制的数，将其转化为 $10$ 进制即可。

举个例子：字符串 `AB`，转化为 $26$ 进制数 $12$，转化为 $10$ 进制答案就为 $2\times 26^0+1\times 26^1=28$。
## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 2e5 + 5;
int n, res, t;
char  s[N];

signed main() {
    cin >> (s + 1);
    int lens = strlen(s + 1);
    t = 1;
    for (int i = lens; i; i--) {
        res += t * (s[i] - 'A' + 1);
        t *= 26;
    }
    cout << res;
}
```

---

## 作者：VitrelosTia (赞：0)

题链：[AT](https://atcoder.jp/contests/abc285/tasks/abc285_c)/[Luogu](https://www.luogu.com.cn/problem/AT_abc285_c)

### 题意
给你一个由大小写字母组成的字符串，A 对应 $1$，B 对应 2，C 对应 $3$，以此类推。最后将字符串看作一个二十六进制的整数，如 ABC 看作 $(123)_ {26}$，求这个数在十进制中对应的数。

### 思路
模拟人算。从后往前遍历字符串，每次计算出当前的位数，以求出当前位的进制基数，用进制基数乘上当前位的数即可。

记得开`long long`。

### code
```
#include <bits/stdc++.h>
 
using namespace std;
 
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;i++)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;i--)
#define ll long long
#define endl putchar('\n')
 
const int M=1e5+5,INF=1e9;
int n,a[M];
 
ll ppow(int x,int y){//自带的pow函数会有精度问题，手写乘方
	ll ans=1;
	for(int i=1;i<=y;i++) ans*=x;
	return ans;
}
 
void solve(){
	string s;
	cin>>s;
	ll ans=0,cnt=0;//结果，当前位数
	dn(s.size()-1,0,i){
		ll base=ppow(26,cnt);//进制基数
		cnt++;
		if(s[i]>='A'&&s[i]<='Z') ans+=1ll*base*(s[i]-'A'+1);
		// printf("base = %lld , ans = %lld , cnt = %lld\n",base,ans,cnt);
	}
	printf("%lld\n",ans);
}
 
int main(){
	int t;
 	//scanf("%d",&t);
	t=1;
	while(t--) solve();
	return 0;
}
```

---

