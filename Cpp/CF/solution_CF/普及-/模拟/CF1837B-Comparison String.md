# Comparison String

## 题目描述

You are given a string $ s $ of length $ n $ , where each character is either &lt; or &gt;.

An array $ a $ consisting of $ n+1 $ elements is compatible with the string $ s $ if, for every $ i $ from $ 1 $ to $ n $ , the character $ s_i $ represents the result of comparing $ a_i $ and $ a_{i+1} $ , i. e.:

- $ s_i $ is &lt; if and only if $ a_i < a_{i+1} $ ;
- $ s_i $ is &gt; if and only if $ a_i > a_{i+1} $ .

For example, the array $ [1, 2, 5, 4, 2] $ is compatible with the string &lt;&lt;&gt;&gt;. There are other arrays with are compatible with that string, for example, $ [13, 37, 42, 37, 13] $ .

The cost of the array is the number of different elements in it. For example, the cost of $ [1, 2, 5, 4, 2] $ is $ 4 $ ; the cost of $ [13, 37, 42, 37, 13] $ is $ 3 $ .

You have to calculate the minimum cost among all arrays which are compatible with the given string $ s $ .

## 说明/提示

In the first test case of the example, the array can be $ [13, 37, 42, 37, 13] $ .

In the second test case of the example, the array can be $ [42, 37, 13, 37, 42] $ .

## 样例 #1

### 输入

```
4
4
<<>>
4
>><<
5
>>>>>
7
<><><><
```

### 输出

```
3
3
6
2```

# 题解

## 作者：__Dist__ (赞：2)

### 题目翻译

~~洛谷上的翻译有点啰嗦~~， 简单来说就是 $ T $ 组数据，对于每组数据，给定 $ n $ 并给定一个长度是 $ n $ 字符串 $ s $，其中 "```&lt;```" 是 " &lt; "，"```&gt;```" 是 "&gt;"。

要求构造一个长度是 $ n+1 $ 序列，但不必输出，就输出序列中最少有几个不同的元素即可。

### 题目讲解

首先分析样例：

第一组样例是 ```< < > >```，容易填出 $ a \lt b \lt c \gt b \gt a $，故答案是 $ 3 $。

第二组和第一组差不多，第三组也容易想到，所以看一下第四组：```< > < > < > <```。直接写出 $ a \lt b \gt a \lt b \gt a \lt b \gt a \lt b $ 也不是很难。

分析过样例就不难得出：我们只要求出最长的连续相同符号 $ +1 $ 即为答案。

### 代码环节

```cpp
#include<iostream>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<iomanip>
#include<cstdio>
#include<stack>
#include<queue>
#include<map>
#include<vector>
using namespace std;
int T;
char s[105];
int n;
int main() {
	cin >> T;
	while (T--) {
		cin >> n;
		cin >> s;
		int maxn = 0; //储存最长的连续相同符号
		int sum = 1; //当前连续符号的长度
		char now = s[0]; //判断是否与上个符号相同
		for (int i = 1; i < n; i++) {
			if (s[i] == now) sum++;
			else {
				maxn = max(maxn, sum); //取最大值
				sum = 1; //当前长度归1
				now = s[i]; //更新now
			}
		}
		maxn = max(maxn, sum); //这里还要取一次最大值
		cout << maxn + 1 << endl;
	}
	return 0;
}
```

---

## 作者：YCSluogu (赞：2)

## CF1837B Comparison String 题解

## 翻译

给定一个长度为 $n$ 且只包含 ">" "<" 的字符串 $s$ ，要求构造一个数列，满足第 $i$ 与第 $i + 1$ 个数之间的大小关系满足 $s_i$ 的符号，求至少用几个不同的数来构造这个数列。

## 题解

这道题就是求一个最长的子串，中间字符全部相同。

我这里给出一个相对好理解的解释方法：

看到这道题我第一反应就是无根树。

将大于号小于号视作有向边，然后将每一个数视作一个树上的点，那么父子关系就是每个数之间的大小关系。如：">><<" 就是下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/5d2jx09q.png)

用这种方式构图，会发现这是一个无根树，而越底下的点数越小。

手玩几组，会发现最后的图都是张这样的：一段连续递减、一段连续递增。画成图就是下面这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/nohg9ob6.png)

观察这张图，很显然，对于一条链上的数是一定不可能相同。那么最后数列中不同的数个数取决于链的长度了。

转化到字符串上，那么就是求连续相同字符的最长长度了，因为只有字符全部相同才能构成一条链。

## 代码：

``` cpp
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void solve() {
  int n;
  std::string str;
  cin >> n >> str;
  int tot = 1;
  int ans = 1;
  for (int i = 1; i < str.size(); i++) {
    tot = str[i] == str[i - 1] ? tot + 1 : 1;
    ans = std::max(ans, tot);
  }
  cout << ans + 1 << endl; // 加一的原因不难想吧？
}

int main() {
  int t;
  cin >> t;
  while (t--) solve();
  return 0;
}
```


---

## 作者：Czy_Lemon (赞：1)

### 先来解释一下题意：

- 给你一个长度为 $n$ 的由 &lt; 和 &gt; 构成的字符串 $s$，如果一个数列 $a$ 能满足将字符串 $s$ 的所有大于号和小于号按顺序填入后满足大小关系，则 $a$ 数列和 $s$ 字符串是“相容的”。
- 定义一个数列的花费是这个数列中不同元素的数量。
- 已知字符串 $s$，让你求出与 $s$ 相容的所有数列中花费最小的数列的花费。


### 然后我们进行分析：

首先我们注意到，当出现像 $a_{i}$ &lt; $a_{i+1}$ &gt; $a_{i+2}$ 的时候，$a_{i}$ 和 $a_{i+2}$ 一定可以取成同一个数，从而减少花费。出现 $a_{i}$ &gt; $a_{i+1}$ &lt; $a_{i+2}$ 的时候也是同理。然后我们试图将这两种情况连接起来，就可以得到类似于 &lt; &gt; &lt; &gt; &lt; &gt; &lt; 这样的情况，也就是题目中的第四个样例，只需要 $2$ 的花费就可以。 **也就是说对于任意长度的没有连续的 &lt; 和 &gt; 的字符串来说，只需要 $2$ 的花费即可，中间一个花费，两边一个花费。**

接下来我们考虑有连续的 &lt; 或连续的 &gt; 的情况，注意到，比如说一个连续的关系为 $a_{i}$ &lt; $a_{i+1}$ &lt; $a_{i+2}$ &lt; $a_{i+3}$，其中四个数都要不同，然后我们把这种情况套进上面分析的例子中：$a_{i}$ &lt; $a_{i+1}$ &lt; $a_{i+2}$ &lt; $a_{i+3}$ &gt; $a_{i+4}$，我发现 $a_{i}$ 和 $a_{i+4}$ 又可以取成一样的了， **也就是说中间连续的小于关系我们可以看作一个整体，也就是上面说的中间，然后左右两个数看作上面说的两边，那么整个的花费就是两边一共一个加上中间一堆。**

所以最后我们得到贪心策略：寻找字符串中最长连续的 &lt; 或 &gt;，计算长度 $l$，$l+1$ 就是最终的答案。

### 以下是代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
char s[5010];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		scanf("%s",&s);
		int cnt1=0,cnt2=0;
		int sum1=0,sum2=0;
		for(int i=0;i<n;i++){
			if(s[i]=='>'){
				cnt2=max(cnt2,sum2);
				sum2=0;
				sum1++;
			}
			else if(s[i]=='<'){
				cnt1=max(cnt1,sum1);	
				sum1=0;
				sum2++;
			}
		}
		cnt1=max(cnt1,sum1);
		cnt2=max(cnt2,sum2);
		printf("%d\n",max(cnt1,cnt2)+1);
	}
	return 0;
}
```

### 后记

如果对题解的内容有建议或者指正，请在在评论区里说或者私信我.

---

## 作者：skyskyCCC (赞：0)

## 前言。
找规律题。
## 分析。
题意就是让我们在一个字符串中填充数据，从而使这个表达式成立。

因为我们要使得填充的数最少，所以要尽可能地多的填充相同的数字。  
我们观察下面几组数据：

1. ```<>```  
要使这个表达式成立，那中间的数就要大于两边的数，我们可以填充为 ```a<b>a``` 的形式，这样可以使填充的数最少，为 $2$ 个。

2. ```<<>><>>```  
我们首先在最左边填充，这样因为有两个小于号，则我们要至少填充 $3$ 个数，同时满足三个大小关系，后面的两个大于号就可以将前面填充的数倒过来。再看后面，我们又可以找到一个由两个大于号组成的子串，可以和前面一样填充三个数，此时也满足前面的小于关系，即填充后为 ```a<b<c>b>a<c>b>a``` 的形式，答案为 $3$ 个。

通过分析，我们可以发现，在最前填充 $a$ 后，为了使满足的关系式最多，我们可以在后面的一个相反的符号上填充 $a$ 从而达到时填充的数最少的目的。

换句话说，就是如果有一个小于号（或大于号）且前面已经有过了一个大于号（或小于号），即前后符号相反，我们就可以填充同一个数。

那我们可以推断，只要找到一个最长的连续相同符号的子串，就可以求得所需数的总个数。因为一个符号需要有两个数据才能成立，所以这个总个数就是这个子串的长度加一。

但是有一个特殊情况，就是所有符号相同，此时没有办法填充同一个数，则答案为 $n+1$ 个。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
using namespace std;
int t,n,maxx,ans;
char s[105];
int main(){
    cin>>t;
    while(t--){
        maxx=0;
        ans=1;//注意清空。
        cin>>n>>s;
        char jl=s[0];
        for (int i=1;i<n;i++){
            if(s[i]==jl){
                ans++;
            }
            else{
                maxx=max(maxx,ans);
                ans=1;//找到目前的最大长度子串，重新统计。
                jl=s[i];
            }
        }
        maxx=max(maxx,ans);//判断特殊情况。
        cout<<maxx+1<<"\n";
    }
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：CheZiHe929 (赞：0)

# CF1837B 题解

## 原题链接

[**Codeforces**](https://codeforces.com/contest/1837/problem/B)

[**洛谷**](https://www.luogu.com.cn/problem/CF1837B)

## 题目大意
有 $T$ 组测试样例，每组会给你一个长度为 $n$ 的由 &gt; 和 &lt; 构成的字符串（在本题输入中，`&gt;` 代表 &gt;，`&lt;` 代表 &lt;）。同时，你要将 $n + 1$ 个数填充到两个符号之间，保证关系式成立，问你填充的数最少有几个（相同的数算作一个数）。

## 思路分析
因为我们要是的填充的数最少，所以我们要尽可能地多的填充相同的数字。

我们来看下面这几组数据：

- `<>`

我们可以填充其为 `a<b>a`，所以说答案为 $2$。

- `><<>`

可以填充为 `a>b<a<c>b` ，所以答案为 $3$。

- `>><`

可以填充为 `a>b>c<b`，所以答案为 $3$。

通过以上样例我们可以发现：只要前面有了 &gt; 或 &lt;，我们就可以在前面填充 $a$，那么在后面有相反的比较符号时我们就可填充为 $a$。也就是说，如果有一个大于号（或小于号）且前面已经有过了一个小于号（或大于号），我们就可以将其抵消，也就是只填充一个数。

综上所述，总结出来答案的规律就是：**最长的连续大于或小于串的长度 $+ 1$。**

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,T;
char s[105];
signed main(){
	cin>>T;
	while(T--){
		cin>>n;
		cin>>s;//字符数组可以直接输入 
		int maxn=0,sum=1;
		//maxn为当前最长的连续大于或小于串的长度
		//sum为每次枚举时大于或小于串的长度 ，注意定值为1 
		char now=s[0];//当前值now，为了判断是否和上一个符号一致 
		for(int i=1;i<n;i++){//从1开始，<n 
			if(s[i]==now)sum++;//长度+1 
			else {
				maxn=max(maxn,sum);//取最大值 
				sum=1;//长度归1 
				now=s[i];//更新现在的符号 
			}
		maxn=max(maxn,sum);//最后要再取一下最大值，因为有可能全是同一种符号 
		cout<<maxn+1<<endl;//不要忘记+1 
	}
	return 0;
}
```

无注释版的我放到了 [**这里**](https://www.luogu.com.cn/paste/z6iayyn2)。

## [AC 记录](https://codeforces.com/contest/1837/submission/207367971)

**THE END.**

**THANK YOU.**

---

