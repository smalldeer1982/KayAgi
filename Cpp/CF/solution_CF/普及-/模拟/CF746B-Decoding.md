# Decoding

## 题目描述

## **题目大意**
Polycarp很想编码，这就是他编写Sveta编码信息的原因。他把中间字母称为单词中间的字母。如果单词的长度是偶数，则中间字母是两个中间字母的左边。在以下示例中，中间字母突出显示：con**t** est，i**n**fo。如果单词由单个字母组成，则根据上面的定义，这个字母是中间字母。

Polycarp以下列方式对每个单词进行编码：他写下单词的中间字母，然后将其删除并重复该过程，直到没有字母为止。例如，他将volga编码为logva。

你得到一个编码，你的任务是进行译码。

## 样例 #1

### 输入

```
5
logva
```

### 输出

```
volga
```

## 样例 #2

### 输入

```
2
no
```

### 输出

```
no
```

## 样例 #3

### 输入

```
4
abba
```

### 输出

```
baba
```

# 题解

## 作者：CGDGAD (赞：2)

### 这道题是个解密题。
----

### 原题大意：

加密方式：不断把一个字符串最中间的那个字符取出来直到取完，所有取出的字符按顺序就是加密后的字符串。

现在题目给你一个被加密的字符串和它的长度，让你解密。

### 思路：

既然是解密，那么我们得研究怎么加密。

以第一个样例的 `volga` 和 `logva` 为例。

`volga` 是怎么变成 `logva` 的？

```text
volga 取出第三个字符 l -> voga
voga 取出第二个字符 o -> vga
vga 取出第二个字符 g -> va
va 取出第一个字符 v -> a
a 取出第一个字符 a -> （空串，结束。）
```

那么，怎么加密就应该怎么解密。把上述的解密方式倒过来看。

```text
空串 插入 a -> a
a 插入 v -> va
va 插入 g -> vga
vga 插入 o -> voga
voga 插入 l -> volga
volga 就是原字符串。
```
（这里依次插入的a、v、g、o、l就是被加密后的字符串倒过来。）

那么插入在哪个地方？有规律吗？再详细研究一下：

```text
空串 插入 a -> a
a 插入 v -> va （原来的字符串a长度为1，v被插入到了第0个位置）
va 插入 g -> vga（原来的字符串va长度为2，g被插入到了第1个位置）
vga 插入 o -> voga（原来的字符串vga长度为3，o被插入到了第1个位置）
voga 插入 l -> volga（原来的字符串voga长度为4，v被插入到了第2个位置）
volga 就是原字符串。
```

那么，这不是显而易见了吗？每次插入到第 `字符串长度 ÷ 2`（向下取整） 个位置上。

**完整的思路：**

事先定义好一个char数组 `decoded`。

每次取出被加密的字符串的最后一个，插入到 `decoded` 数组的第 `decoded.length / 2` 个位置，直到被加密字符串被取完。`decoded` 字符串就是答案。

### 实现方式

使用 `vector<char>`。

举个例子，往一个叫做 `v` 的 `vector<char>` 在第 `index` 个位置处插入值 `'a'`：`v.insert(v.begin() + index, 'a')`

### 代码（不足20行）

```cpp
#include <cstdio>
#include <vector>
using namespace std;
int cnt;
vector<char> decoded; // 被解密的字符串
char encoded[10001]; // 被加密的字符串
int main() {
	scanf("%d%s", &cnt, encoded); // 输入
	decoded.push_back(encoded[cnt - 1]); // 将被加密字符串的最后一个push进vector
	for (int i = cnt - 2; i >= 0; i -= 1) { // 从倒数第二个字符开始倒序遍历encoded字符串
		int index = decoded.size() / 2; // 插入在第 size ÷ 2 个位置
		decoded.insert(decoded.begin() + index, encoded[i]); // 使用insert()插入
	}
	for (int i = 0; i < decoded.size(); i += 1) {
		printf("%c", decoded[i]); // 输出
	}
	return 0;
}
```


---

## 作者：OMITW (赞：1)

# 前言
这是一个很~~难~~的橙色的推导题。做对后看了看其他题解。发现都是多用了一些东西来存储。太~~复杂~~了，我的评价是不如直接输出简单且高效。

# 思路推导
首先我们仔细阅读题面。其实就是把一个长度为 $ n $ 字符串 $ s $ 进行操作后得到字符串 $ da $。每次都是把 $ s $ 的 $ \lfloor \frac{n}{2} \rfloor $ 位加入 $ da $，然后删去。

因为他给我们的是经过操作后的序列，且是加入最后，所以我们从最后面开始考虑。那我们可以考虑长度为 $ 2 $ 的情况。$ 1 $ 的话没有意义，显然可得。

如果长度为 $ 2 $，那加入的肯定是第一个字符，再加入第二个。所以 $ s[0] $ 必定为 $ da[n-2] $，而 $ s[n-1] $ 必定为 $ da[n-1] $。

然后继续 $ 2 $ 个 $ 2 $ 个向前。因为 $ s $ 删去的是第 $ \lfloor \frac{n}{2} \rfloor $ 位。由此不难发现，$ da $ 优先加入的都是在 $ s $ 中间的。且位于 $ s $ 前面的都是 $ da $ 每两次循环时前面那个。而位于 $ s $ 后面的都是 $ da $ 每两次循环时后面那个。

综上所述。我们可以从 $ n-2 $ 开始循环，每次向前递减 $ 2 $ 输出。再正着来一次循环，每次向后递减 $ 2 $ 输出。下面是本蒟蒻的代码。仅仅只有 $ 11 $ 行。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
string s;
int main()
{
	cin>>n>>s;
	for(int i=n-2;i>=0;i-=2)cout<<s[i];
	for(int i=!(s.size()%2);i<n;i+=2)cout<<s[i];
	return 0;
}
```

---

## 作者：_SkyLine_ (赞：1)

找规律题，不过~~对我来说~~有点费脑子。
## 思路分析
题目中的编码过程可以理解为将原单词中的字母**按照特定的顺序**重排，这意味着我们如果知道这种特定的顺序就可以将被编码的单词逆向解码。

手动模拟一下三个样例，发现这个问题需要分题目中 $n$ 的奇偶性讨论排列方式。记被编码字符串为 $s$，字符从头到尾为 $s_1,\cdots s_n$；原字符串为 $ans$，字符从头到尾为 $ans_1,\cdots ans_n$；$mid$ 为该串第一个进行变换的位置，然后按照 $n$ 的奇偶性分类，我们有：

- $n$ 为奇数时，可知 $mid$ 的值应该为 $\frac{n}{2}+1$。从头到尾遍历字符串 $s$。当 $i$ 为 $1$ 时，$s_1$ 对应 $ans_{mid}$。当 $i$ 为 $2$ 时，$s_2$ 对应 $ans_{mid-1}$。以此类推。当 $i$ 为奇数时，$s_i$ 对应 $ans_{mid+len}$；当 $i$ 为偶数时，$s_i$ 对应 $ans_{mid-len}$。其中变量 $len$ 在 $i$ 为偶数时 $+1$，初始值为 $0$。

- $n$ 为偶数时，$mid$ 值为 $\frac{n}{2}$。采用同样的方式遍历 $s$。当 $i$ 为 $1$ 时，$s_1$ 对应 $ans_{mid}$。当 $i$ 为 $2$ 时，$s_2$ 对应 $ans_{mid+1}$。以此类推。当 $i$ 为奇数时，$s_i$ 对应 $ans_{mid-len}$；当 $i$ 为偶数时，$s_i$ 对应 $ans_{mid+len}$。其中变量 $len$ 在 $i$ 为偶数时 $+1$，初始值为 $0$。

变量 $len$ 的具体变化请参考代码，~~不明白的话请尝试手动模拟。~~

## $\textsf{Code:}$
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2001;
typedef long long ll;
char w[N],ans[N];
int len=0,n;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++)
    	cin >> w[i];
    if(n==1)
    {
    	cout<<w[1];
    	return 0;
	}
	int mid=n>>1;
	if(n&1)
	{
		mid++;
		ans[mid]=w[1];
		for(int i=2;i<=n;i++)
		{
			if(!(i&1))
			{
				len++;
				ans[mid-len]=w[i];
			}
			else
				ans[mid+len]=w[i];
		}
	}
	else
	{
		ans[mid]=w[1];
		for(int i=2;i<=n;i++)
		{
			if(!(i&1))
			{
				len++;
				ans[mid+len]=w[i];
			}
			else
				ans[mid-len]=w[i];
		}
	}
	for(int i=1;i<=n;i++)
		cout<<ans[i];
    return 0;
}
```

---

## 作者：_Spectator_ (赞：1)


[可能更好的食用体验](/blog/523641/CF746B) $|$ 
[题目传送门](/problem/CF746B) $|$ 
[我的其他题解](/blog/523641/#type=题解)

------------

${\large\color{#00CD00}\text{主要思路}}$

不难看出，构成原码和编码的字母并没有发生改变，只是字母的位置变了。只需要想办法把字母的位置对应起来，就不难还原出原码了。

具体实现方法：

- 使用`vector<int>p;`存储位置。
- 每次求出中间位置 $pos$。
- 此时 $i$ 对应的位置就是 $p[pos]$，还原对应位置的字母。
- 删除 $p$ 的中间位置。

恕我表述不清，不明白的再看看代码吧。

------------

${\large\color{#00CD00}\text{完整代码}}$

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
char s[2005],st[2005];
vector<int>p;
int main()
{　
	cin>>n>>s;
	for(int i=0;i<n;i++)
		p.push_back(i);//存入位置 
	for(int i=0;i<n;i++)
	{　
        int pos=(n-i+1)/2-1;//找到中间位置 
		st[p[pos]]=s[i];//对应位置，还原原码 
		p.erase(p.begin()+pos);//删除中间位置 
	}　
	cout<<st;
	return 0;
}　
```

**[${\color{Black}\textbf{xt\_\_}}$](/user/523641) 温馨提示：**


${\large\color{White}\text\colorbox{#AD8800}{题解千万条，理解第一条。直接粘题解，棕名两行泪。}} $

---

## 作者：qfpjm (赞：1)

# 题目大意

- 给出一个用题目中的方法魔改过得字符串，让你将原串输出。

# 题解

- 题目中说：单词的长度是偶数，则中间字母是两个中间字母的左边。奇数则是中间。

- 那么，我们很容易得出，对于魔改后字符串后的每一位，如果是奇数位，那么这个字符在原串的右边，偶数位则左边。

# 代码

- 根据上面的描述，我们很容易可以得出代码。

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, i;
string ch, ans = "";

int main()
{
	cin >> n >> ch;
	for (int i = 0 ; i < ch.size() ; i ++)
	{
		if (ans.size() % 2 == 0)
		{
			ans = ch[i] + ans; 
		}
        else
		{
			ans = ans + ch[i];
		}
	}
	cout << ans;
	return 0;
}

```

# 后记

- ~~第一次写题解后记~~

- 其实，字符串的 ```size```函数的时间复杂度是 $O(n)$ 的，所以总的复杂度是 $O(n^2)$，如果数据出得大一点，就会 TLE，其他题解中有用一个标记来处理，复杂度可以将至 $O(n)$。


---

## 作者：JamesZhan (赞：0)

# $\texttt{CF746B}$ 题解
## 原题链接
[洛谷原题链接](https://www.luogu.com.cn/problem/CF746B)

[CF原题链接](https://codeforces.com/problemset/problem/746/B)
## 题目思路

这道题我们可以先准备一个字符数组，用于存储答案。首先，我们稍微分类一下，第一类就是总长度为偶数，第二类则为奇数。

为什么这样分类呢？因为这两种情况解决问题的方式不一样。

**第一种情况**

因为总长度为偶数，所以原字符串加密时写下的顺序，分别是从中间开始往左、往右，~~再往左、再往右~~，如此来回。

所以我们可以建一个 $mid$ 变量，用来存储整个数组的最中间的位置(注意可能存在小数)。

如下图，$n = 6$，此时 $mid$ 为 $3.5$。

![](https://i.postimg.cc/g2qfhQP7/2023-08-09-103607.png)



接下来，我们遍历一下 $mid$ 往左和往右所有可能的值，每次在循环内都将字符数组按顺序存入原字符串下标为 $mid - i$ 和 $mid + i$ 的字符。如此，第一种情况就完成啦！

第一种情况代码：
```
float mid=(n+1)*1.0/2;
int cnt=1;
for(float i=0.5;i<=n/2-0.5;i++){//此时n为偶数，最中心有0.5
	c[int(mid-i)]=s[cnt];//c为存储答案的字符数组
	cnt++;
	c[int(mid+i)]=s[cnt];//下标必须为整数所以要强制转换
	cnt++;
}
```
**第二种情况**

相信大家看了第一种情况的思路，肯定就想到了第二种的方法吧！

没错，第二种甚至更简单。同样是从最中间开始，不过此时下标中间值为正数，只需在循环开始前存入即可。

```
int mid=n/2+1;
int cnt=2;
c[mid]=s[1];
for(int i=1;i<=n/2;i++){
	c[mid-i]=s[cnt];
	cnt++;
	c[mid+i]=s[cnt];
	cnt++;
}
```

## 完整代码
```
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
char c[2005];
int main(){
	cin>>n>>s;
	s='a'+s;//在字符串前加一个字符，这样更容易计算下标
	if(n%2==1){//第二种情况
		int mid=n/2+1;
		int cnt=2;
		c[mid]=s[1];
		for(int i=1;i<=n/2;i++){
			c[mid-i]=s[cnt];
			cnt++;
			c[mid+i]=s[cnt];
			cnt++;
		}
	}
	else{//第一种情况
		float mid=(n+1)*1.0/2;//注意mid为浮点数
		int cnt=1;
		for(float i=0.5;i<=n/2-0.5;i++){
			c[int(mid-i)]=s[cnt];//注意强制转换
			cnt++;
			c[int(mid+i)]=s[cnt];
			cnt++;
		}
	}
	for(int i=1;i<=n;i++){//输出
		cout<<c[i];
	}
	cout<<endl;
	return 0;//好习惯
}
```
感谢观看，审核大大辛苦了。

---

## 作者：blsya23a2 (赞：0)

## 分析
把加密后的字符串解密只需要找到正确的对应顺序，可以由加密过程推出。
### 加密
由题知，当 $n\bmod2=0$ 时，加密后第一个数是中心靠前的数，第二个数是中心靠后的数，后面以此类推。而当 $n\bmod2=0$ 时，只需要把中心的数先取出就能转化为 $n\bmod2=0$ 的情况。
### 解密
创建一个长度为 $n$ 的列表。由加密过程知，当 $n\bmod2=0$ 时，列表中心靠前的元素赋值为加密后的字符串的第一个数，列表中心靠后的元素赋值为加密后的字符串的第二个数，后面以此类推。循环输出列表元素就得到了原字符串。而当 $n\bmod2=1$ 时，只需要把加密后的字符串的第一个数赋值为列表中心的数就能转化为 $n\bmod2=0$ 的情况。
## 代码
```python
a,b = int(input()),list(input())
c,d = [' ' for d in range(a)],a//2
if a%2 == 1:
    c[d] = b[0]
    for e in range(d):
        c[d-e-1] = b[2*e+1]
        c[d+e+1] = b[2*e+2]
else:
    for f in range(d):
        c[d-f-1] = b[2*f]
        c[d+f] = b[2*f+1]
for g in c:
    print(g,end='')
```

---

## 作者：封禁用户 (赞：0)

# 题意

给出一个修改过得字符串，让你将原串输出。

# 思路

其实这道题用了**反推**的方法。

首先先定义一个变量 `ans`。

通过题目样例，我们不难发现以下结论：

情况一，当字符串的长度是偶数：

如果字符的下标是奇数时，在 `ans` 的末尾加上这个字符；否则在 `ans` 的字符串头加上这个字符。

情况二，当字符串的长度是奇数：

如果字符的下标是偶数时，在 `ans` 的末尾加上这个字符；否则在 `ans` 的字符串头加上这个字符。

最后输出 `ans` 就行啦。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
string s,k;
int main()
{
	cin>>n>>s;
	if(n%2==0) //情况一
	{
		for(int i=0; i<s.size(); i++)
		{
			if(i%2==1) k+=s[i];
			else k=s[i]+k;
		}
	}
	else //情况二
	{
		for(int i=0; i<s.size(); i++)
		{
			if(i%2==0) k+=s[i];
			else k=s[i]+k;
		}
	}
	cout<<k;
	return 0;
}
```

---

## 作者：YuanZihan1225 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF746B)

# 题目大意

已知一种加密方案，给出一个加密后的字符串，字符串。

加密方案如下：

1.如果当前字符串长度为奇数，则取出正中间的字符。

2.否则就取出正中间两个字符中靠左的那一个。

# 思路分析

因为是要倒着求，所以我们要倒推，显然要对字符串的长度进行分类讨论：

1.当当前字符串的长度为奇数时，由倒推可得当前字符串的第一个字符一定是在答案字符串的右边，所以将其加到右边。

2.当长度为偶数的时候，同理可得应加在左边，顺次枚举一遍即可。

3.再教大家一个小技巧：看样例分析答案法。

具体有一些细节，详见代码。

# 代码见下

```cpp
#include<bits/stdc++.h>
using namespace std;
string s, ans;
int len;
signed main()
{
	cin >> len >> s;
	if(len & 1)//分类讨论，蒟蒻没想出来怎么优化
	{
		for(int i = 0; i < len; i++)
		if(i % 2 == 0)
			ans = ans + s[i];//字符串可以直接拼接
		else
			ans = s[i] + ans;
	}
	else
	{
		for(int i = 0; i < len; i++)//同理
		if(i % 2 == 0)
			ans = s[i] + ans;
		else
			ans = ans + s[i];
	}
	cout << ans;
	return 0;
}//完美地结束QWQ
```

---

## 作者：lrmlrm_ (赞：0)

# 题意

  给出一个长度为 $ n $ 的加密后的字符串 $ s $ $ , $ 求原字符串 $ 。 $
  
# 思路

此题是一解密题。根据样例不难发现以下规律 $ : $

$ 1 . $ 当 $ n $ 为奇数时 $ ( $ 以样例 $ 1 $ 为例 $ ) $ $ : $ 
 
$\ \ \ $ $ s $ 是 $ logva $ $ , $ $ ans $ 串为空

$\ \ \ $ $ s $ 的第 $ 1 $ 个字符是 $ l $ $ , $ 拼接到 $ ans $ 串的右边 $ , $  $ ans $ 串变成 $ l $

$\ \ \ $ $ s $ 的第 $ 2 $ 个字符是 $ o $ $ , $ 拼接到 $ ans $ 串的左边 $ , $  $ ans $ 串变成 $ ol $

$\ \ \ $ $ s $ 的第 $ 3 $ 个字符是 $ g $ $ , $ 拼接到 $ ans $ 串的左边 $ , $  $ ans $ 串变成 $ olg $

$\ \ \ $ $ s $ 的第 $ 4 $ 个字符是 $ v $ $ , $ 拼接到 $ ans $ 串的左边 $ , $  $ ans $ 串变成 $ volg $

$\ \ \ $ $ s $ 的第 $ 5 $ 个字符是 $ a $ $ , $ 拼接到 $ ans $ 串的左边 $ , $  $ ans $ 串变成 $ volga $

$ 2 . $ 当 $ n $ 为偶数时 $ ( $ 以样例 $ 3 $ 为例 $ ) $ $ : $

$\ \ \ $ $ s $ 是 $ abba $ $ , $ $ ans $ 串为空

$\ \ \ $ $ s $ 的第一个字符是 $ a $ $ , $ 拼接到 $ ans $ 串左边 $ , $ $ ans $ 串变成 $ a $

$\ \ \ $ $ s $ 的第二个字符是 $ b $ $ , $ 拼接到 $ ans $ 串右边 $ , $ $ ans $ 串变成 $ ab $ 

$\ \ \ $ $ s $ 的第三个字符是 $ b $ $ , $ 拼接到 $ ans $ 串左边 $ , $ $ ans $ 串变成 $ bab $

$\ \ \ $ $ s $ 的第四个字符是 $ a $ $ , $ 拼接到 $ ans $ 串右边 $ , $ $ ans $ 串变成 $ baba $

不难发现规律就是 $ : $ **根据 $ n $ 的奇偶性 $ , $ 往 $ ans $ 串两端交替拼接字符 。**

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string st,ans;
int main(){
	scanf("%d",&n);
	cin>>st;
	if(n%2==0)for(int i=0;i<st.size();i++)i%2==1?ans=ans+st[i]:ans=st[i]+ans;
	else for(int i=0;i<st.size();i++)i%2==0?ans=ans+st[i]:ans=st[i]+ans;
	cout<<ans;
	return 0;
}
```
~~只有c++可以写出如此简洁的代码~~

---

## 作者：used_to_be (赞：0)

这题还是挺简单的，只需输入一个字符串，输出解密后的结果即可。

这种题一般都有一些规律。我们先来观察一下第一个样例，输入 ```logva```  ，输出 ```volga``` ，不妨推导一下按输出输入的顺序，发现是 $4$ $2$ $1$ $3$ $5$ ，即 $v$ 对应 $4$ ， $o$ 对应 $2$ ， $l$ 对应 $1$ ， $g$ 对应 $3$ ， $a$ 对应 $5$ 。

如果规律还不是很明显的话，再拿出第二个样例，输入```no```，输出```no```。顺序是 $1$ $2$ 。

第三个样例输入 ```abba``` ，输出 ```baba``` 。顺序就是 $3$ $1$ $2$ $4$ 。

推导到这儿，我们发现了一点规律，即如果输入串的长度是偶数，输出串从 $n-1$ 开始到 $1$ ，每次减 $2$ ，再从 $2$ 开始到 $n$ ，每次加 $2$ 。如果输入串的长度是奇数，输出串从 $n-1$ 开始到 $2$ ，每次减 $2$ ，再从 $1$ 开始到 $n$ ，每次加 $2$ 。

代码见下：

```cpp
#include<iostream>
using namespace std;
int n;
string a;
int main()
{
	cin>>n;
	cin>>a;
	a=' '+a;
	if(n%2)//判断一下长度
	{
		for(int i=n-1;i>=2;i-=2)//上面说过了
		{
			cout<<a[i];
		}
		for(int i=1;i<=n;i+=2)
		{
			cout<<a[i];
		}
	}
	else
	{
		for(int i=n-1;i>=1;i-=2)
		{
			cout<<a[i];
		}
		for(int i=2;i<=n;i+=2)
		{
			cout<<a[i];
		}
	}
	return 0;
}
```

---

## 作者：YYen (赞：0)

### 思路：模拟
根据样例看出来规律：

①、字符串长度为奇数。

$ s $ 串为 ``` logva ``` ， $ ans $ 串为空串。

$ s $ 串第 $ 1 $ 个字符拼接到 $ ans $ 右边，得到 ``` l ```

$ s $ 串第 $ 2 $ 个字符拼接到 $ ans $ 左边，得到 ``` ol ```

$ s $ 串第 $ 3 $ 个字符拼接到 $ ans $ 右边，得到 ``` olg ```

$ s $ 串第 $ 4 $ 个字符拼接到 $ ans $ 左边，得到 ``` volg ```

$ s $ 串第 $ 5 $ 个字符拼接到 $ ans $ 右边，得到 ``` volga ```

②、字符串长度为偶数。

$ s $ 串为 ``` abba ``` ， $ ans $ 串为空串。

$ s $ 串第 $ 1 $ 个字符拼接到 $ ans $ 左边，得到 ``` a ```

$ s $ 串第 $ 2 $ 个字符拼接到 $ ans $ 右边，得到 ``` ab ```

$ s $ 串第 $ 3 $ 个字符拼接到 $ ans $ 左边，得到 ``` bab ```

$ s $ 串第 $ 4 $ 个字符拼接到 $ ans $ 右边，得到 ``` baba ```

所以结论就是，**根据 $ s $ 串长度的奇偶性，往 $ ans $ 串两端交替拼接字符**。

### 代码
```cpp
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int n;
    bool flag;
    string s, ans = "";
    cin >> n >> s;
    if (n & 1) flag = false; // 奇数长度 
    else flag = true; // 偶数长度 
    for (int i = 0; i < s.size(); i++)
    {
        if (flag) ans = s[i] + ans; // 拼接在左边 
        else ans = ans + s[i]; // 拼接在右边 
        flag = !flag;
    }
    cout << ans << endl;
    return 0;
}
```


---

## 作者：codemap (赞：0)

这道题还是比较简单的,我是用分类n的就来做的

做法:

记录一个p,开始时为(n+1)/2-1(字符串中间一个)(字符串是从0开始的,所以要-1)

若n是奇数,在(i+1)(+1原因同上)为奇数时p-=i+1,偶数时p+=i+1

若n是偶数,在(i+1)(+1原因同上)为奇数时p+=i+1,偶数时p-=i+1

可以自行想一想为什么p这样变动

每次棉花之前用一个数组记录一下,最后输出就行了

上代码
```cpp
#include<iostream>
using namespace std;
int main()
{
	int n,i,p;
	string a;
	char b[2001];
	cin>>n>>a;
	p=(n+1)/2-1;//赋初值
	if(n%2==1)//n为奇数
		for(i=0;i<n;i++)
		{
			b[p]=a[i];//记录
			if((i+1)%2==1)//如果(i+1)为奇数
				p-=i+1;
			else//如果(i+1)为偶数
				p+=i+1;
		}
	else
		for(i=0;i<n;i++)
		{
			b[p]=a[i];//记录
			if((i+1)%2==1)//如果(i+1)为奇数
				p+=i+1;
			else//如果(i+1)为偶数
				p-=i+1;
		}
	for(i=0;i<n;i++)
		cout<<b[i];//输出
	return 0;//完美结束
}
```
# 请勿抄袭

---

