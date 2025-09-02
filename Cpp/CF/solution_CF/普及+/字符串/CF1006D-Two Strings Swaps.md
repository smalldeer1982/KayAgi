# Two Strings Swaps

## 题目描述

**题目大意：**
有两个长度为$n$的字符串a,b，现有三种操作

- 交换$a_i,b_i$
- 交换$a_i,a_{n-i+1}$
- 交换$b_i,b_{n-i+1}$

可以发现$a$不一定能通过这些交换变成$b$

现在你还有一种操作，在交换字符之前，你可以把$a$中某个位置字符变成任意一个字符

问要使$a==b$最少要用**操作四**多少次

## 样例 #1

### 输入

```
7
abacaba
bacabaa
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
zcabd
dbacz
```

### 输出

```
0
```

# 题解

## 作者：E1_de5truct0r (赞：2)

## 思路

首先发现一个~~奇怪的~~ 性质：$a_i,a_{n-i+1},b_i,b_{n-i+1}$ 是相互连通的。

因此，我们只需要判断这四个中是否存在两两对应。如果存在，那么一定不需要修改就可以；如果不存在，$a$ 数组应该把和 $b$ 数组不一样的改成 $b$ 数组对应的值。这个复杂度显然是 $O(n \cdot k)$ （其中 $k$ 为常数，视写法在 $8$ 至 $26$ 之间不等）。我的做法是先把这几个字符排序，然后就可以很方便的判断了。时间复杂度大约是 $O(n)$。

## 代码

其实虽然看着分讨挺长的，但是其实是重复。

```cpp
#include <bits/stdc++.h>
using namespace std;
char a[100005],b[100005];
char t[6];
int main()
{
	int n; scanf("%d",&n);
	scanf("%s%s",a+1,b+1);
	int ans=0;
	for(int i=1;i<=n>>1;i++)
	{
		int j=n-i+1;
		t[1]=a[i],t[2]=a[j],t[3]=b[i],t[4]=b[j];
		sort(t+1,t+5); // 排序（懒得用 swap 的屑）
		if(t[1]==t[2] && t[3]==t[4]) continue; // 如果符合了就不加
		else if(t[1]==t[2]) // 否则判断是否存在相同的，如果存在其实理论上有一定概率可以少改一个。
			if(b[i]==t[1] || b[j]==t[1]) ans++;
			else ans+=2;
		else if(t[2]==t[3])
			if(b[i]==t[2] || b[j]==t[2]) ans++;
			else ans+=2;
		else if(t[3]==t[4])
			if(b[i]==t[3] || b[j]==t[3]) ans++;
			else ans+=2;
		else ans+=2; // 如果一个都没有相同的，那么两个都要改。
	}
	if((n&1) && a[n+1>>1]!=b[n+1>>1]) ans++; // 特判 n 是奇数的时候中间两位。
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Argon_Cube (赞：2)

* **【题目链接】**

[Link:CF1006D](https://www.luogu.com.cn/problem/CF1006D)

* **【解题思路】**

不难发现，可以按
$$
\{a_i,a_{n-i+1},b_i,b_{n-i+1}\}(i\in[1,\lceil\frac{a\!\operatorname{.size()}}{2}\rceil])
$$ 
分组。

可能有点难以理解，就拿样例 $1$ 来说（其中同颜色的字符是一组）：
$$
\begin{matrix}
\color{red}a\color{orange}b\color{purple}a\color{green}c\color{purple}a\color{orange}b\color{red}a\\
\color{red}b\color{orange}a\color{purple}c\color{green}a\color{purple}b\color{orange}a\color{red}a
\end{matrix}
$$
我们可以发现，用操作 $1\sim 3$ 可以在 $3$ 步之内让同一组中的任意两个字符互换，且不可能让不同组的两个字符互换。

那么，我们只要让同一组的字符可以平均分配到两个字符串就行了。

也就是说，可以让这一组里有两种字符，每种两个，也可以有 $4$ 个同样的字符。

现在考虑如何修改。

请注意，题目中有一句极为重要的话：

**在（第一次）交换字符之前**，你可以**把** $\textbf a$ **中**某个位置字符变成任意一个字符。

这使得样例 $1$ 的答案为 $4$ 而不是 $3$。

如果没有限定在第一次交换字符之前，或只能在 $a$ 中替换，那么样例 $1$ 答案将为 $3$。原因请自己模拟，这并不难。

回归如何修改这个问题上。

首先，每一组显然可以单独考虑。

可以统计字符类数，也可以统计只出现过一次的字符的个数。我选择后者。

现在分类讨论：

1. 如果在一组中只出现过一次的字符只有 $1$ 个，那么：

	* 如果这个字符在 $a$ 中，可以把这个字符改成与其它字符一样（ 即$4$ 个同样的字符），需要改动 $1$ 个字符。
   * 如果这个字符在 $b$ 中，可以改动 $a$ 中的一个字符与之对应。
   
   因此，这种情况只需用 $1$ 次操作 $4$。
   
2. 如果在一组中只出现过一次的字符只有 $2$ 个，那么：

	* 如果这两个字符均在 $a$ 中，可以改动 $1$ 个字符，让两个字符相等，需要改动 $1$ 个字符。
   * 如果这两个字符均在 $b$ 中，需要改动 $a$ 中的 $2$ 个字符与之对应。
   * 如果这两个字符一个在 $a$ 中一个在 $b$ 中，那么可以改动 $a$ 中的那个字符使之与 $b$ 对应。
	
3. 如果这一组中 $4$ 个字符均不同，那么需要改动 $2$ 个字符。

现在，问题解决了。

* **【实现细节】**

等等，似乎还有什么问题。

如果字符串长度是奇数（样例 $1$），那么中间一组每个字符会被计算两次，导致错误的结果。

我采用的方法是在中间插入两个一样的字符。

```string::insert(size_t pos,size_t n,_CharT c)```在下标为```pos```的地方插入```n```个字符```c```。

* **【代码实现】**

```cpp
#include <iostream>
#include <string>

using namespace std;

int main(int argc,char *argv[],char *envp[])
{
	int strsize;
	string a,b;
	cin>>strsize>>a>>b;
	if(strsize%2)//字符串长度是奇数的处理
		a.insert(strsize/2,1,'I'),b.insert(strsize/2,1,'I'),strsize++;
	pair<char,int> cnt[4];//计算每组中每个字符的出现次数
	int tmp,sum=0;
	for(int i=0;i<strsize/2;i++)
	{
		tmp=0;
		for(int j=0;j<4;j++)
			cnt[j]=make_pair('\0',0);
		//下面4个for是用来统计的
		for(int j=0;j<4;j++)
		{
			if(cnt[j].first=='\0')
				cnt[j].first=a[i],cnt[j].second++;
			else if(cnt[j].first==a[i])
				cnt[j].second++;
			else
				continue;
			break;
		}
		for(int j=0;j<4;j++)
		{
			if(cnt[j].first=='\0')
				cnt[j].first=b[i],cnt[j].second++;
			else if(cnt[j].first==b[i])
				cnt[j].second++;
			else
				continue;
			break;
		}
		for(int j=0;j<4;j++)
		{
			if(cnt[j].first=='\0')
				cnt[j].first=a[strsize-i-1],cnt[j].second++;
			else if(cnt[j].first==a[strsize-i-1])
				cnt[j].second++;
			else
				continue;
			break;
		}
		for(int j=0;j<4;j++)
		{
			if(cnt[j].first=='\0')
				cnt[j].first=b[strsize-i-1],cnt[j].second++;
			else if(cnt[j].first==b[strsize-i-1])
				cnt[j].second++;
			else
				continue;
			break;
		}
		for(int j=0;j<4;j++)
			if(cnt[j].second==1)//统计只出现过一次的字符的个数
				tmp++;
		switch(tmp)//处理修改次数
		{
			case 4:
				sum+=2;
				break;
			case 1:
				sum++;
				break;
			case 2:
				if(a[i]==a[strsize-i-1]||b[i]==b[strsize-i-1])
					sum+=2;
				else
					sum++;
		}
	}
	cout<<sum;
 	return 0;
}

```

---

## 作者：小闸蟹 (赞：2)

```cpp
// 这一题要求对字符串a（第一个字符串）进行修改（注意看题，我在这里WA了几遍）
// 于是我们将a、b字符串中的每个字符分组，一头一尾分为一组
// 具体说来就是将{a(i), a(l - i - 1), b(i), b(l - i - 1)}合并成一组
// 然后统计每一组中不同的字符的个数，通过对不同字符个数进行分类讨论得出答案
#include <iostream>
#include <unordered_map>
#include <string>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int l;
    std::cin >> l;

    std::string Str1, Str2;
    std::cin >> Str1 >> Str2;

    int Ans = 0;
    for (int i = 0; i < l / 2; ++i)
    {
        std::unordered_map<char, int> Map;
        ++Map[Str1[i]];
        ++Map[Str2[i]];
        ++Map[Str1[l - i - 1]];
        ++Map[Str2[l - i - 1]];

        if (Map.size() == 2)    // 如果只有两个字符不同
        {
            if (Map[Str1[i]] != 2)  // 那就看看其中一个字符的个数是不是2，如果不是的话，证明一个字符是3，一个字符是1，则需要调整一个字符
            {
                ++Ans;
            }
        }
        else if (Map.size() == 3)   // 如果有三个字符不同
        {
            if (Str1[i] == Str1[l - i - 1]) // 看看a字符串头尾是否相等，是的话那么b字符串的头尾都得修改，就是2
            {
                Ans += 2;
            }
            else   // 如果a字符串头尾不相等，那么b字符串只需要修改一个字符即可
            {
                ++Ans;
            }
        }
        else if (Map.size() == 4)   // 如果四个字符都不想等，那就调两个字符出来修改，改成中心对称的形式
        {
            Ans += 2;
        }
    }

    if (l & 1)  // 如果字符串的长度是奇数，那么中间的一对字符需要特殊地拿出来看一下，因为组不成四个字符一组了
    {
        if (Str1[l / 2] != Str2[l / 2]) // 不相等，还得再调整一个字符
        {
            ++Ans;
        }
    }

    std::cout << Ans << std::endl;

    return 0;
}
```

---

## 作者：Morax2022 (赞：0)

# Solution
不难发现，当枚举到 $i$ 时，若 $a_i, b_i, a_{n - i + 1}, b_{n - i + 1}$ 能够通过交换两两匹配，$ans$ 就不用加。

也就是当不能两两匹配时，$ans$ 就一定会加，共有两种情况：

1. 能匹配一组，$ans$ 只需加 $1$。
2. 不能匹配任何一组，$ans$ 加 $2$。

但还有一种特殊情况，即 $n$ 为奇数时只有中间只有两个数，需特判。

具体细节可以看代码。

# Code
```cpp
#include <bits/stdc++.h>
#define debug cout << "CCF\n";
//#define int long long
using namespace std;
const int maxn = 2e5 + 5;
int n, ans;
char a[maxn], b[maxn], c[5];
main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n; cin >> a + 1 >> b + 1;
	ans = (a[n + 1 >> 1] != b[n + 1 >> 1]) * (n & 1);//奇数特判 
	for (int i = 1; i <= n / 2; i++){
		c[1] = a[i], c[2] = b[i], c[3] = a[n - i + 1], c[4] = b[n - i + 1];
		sort(c + 1, c + 5);
		if (c[1] == c[2] && c[3] == c[4]) continue;
		ans++;//至少要加一次 
		if (c[1] != c[2] && c[2] != c[3] && c[3] != c[4]) {ans++; continue;} //没有匹配一组的可能（两个相等） 
		/*两个字符相同，若有一个是b内的，ab有一边即可相通，只用加一次，反之，加两次*/
		if (c[1] == c[2] && b[i] != c[1] && b[n - i + 1] != c[2]) ans++;
		else if (c[2] == c[3] && b[i] != c[2] && b[n - i + 1] != c[3]) ans++;
		else if (c[3] == c[4] && b[i] != c[3] && b[n - i + 1] != c[4]) ans++;//必须加两次 
	}
	cout << ans;
}


```

---

## 作者：lightningZ (赞：0)

## 思路
读了题之后我们可以发现，首先你是要在操作之前就修改字符串，所以必须按照它给出的串来操作。其次，因为你既可以以中点交换 $a$ 串或 $b$ 内，也可以交换 $a$ 和 $b$ 之间相同位置的字母。所以我们需要考虑的有四个位置 $a_i,b_i,a_{n-i+1},b_{n-i+1}$然后分几种情况考虑。

$1:$ 有一个 $a$ 和一个 $b$ 相等，这时候如果另外两个也相等就可以不需要操作四，不然就 $ans\gets ans+1$。

$2:$ $a,b$ 互不相等，这时候如果 $a,b$ 内部相等，那就可以通过 $1-3$ 的一系列操作使得两个串互相相等，所以可以不考虑，否则就 $ans\gets ans+2$。

## 代码
（由于本蒟蒻的代码能力已经低到一定水平了，所以用了一堆判断，但是思路是一样的，所以各位大佬凑活着看吧。）

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans;
char a[100005],b[100005];
signed main()
{
	scanf("%lld%s%s",&n,a+1,b+1);
	for(int i=1;i<=n/2+1;i++)
	{
		if(n%2==1&&i*2==n+1)
		{
			if(a[i]!=b[i]) ans++;
			break;
		}
		if(n%2==0&&i==n/2+1) break;
		char xa=a[i],xb=b[i];
		char ya=a[n-i+1],yb=b[n-i+1];
		if(xa==xb)
		{
			if(ya==yb) continue;
			else ans++;
		}
		else if(xa==yb) 
		{
			if(ya==xb) continue;
			else ans++;
		}
		else
		{
			if(ya==yb||ya==xb) 
			{
				ans++;
				continue;
			}
			if(xb==yb)
			{
				if(xa==ya) continue;
				else ans++;
			}
			else ans+=2;
		}
	}
	printf("%lld",ans);
	return 0;
}
```


---

