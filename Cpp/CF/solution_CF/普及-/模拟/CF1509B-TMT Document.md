# TMT Document

## 题目描述

The student council has a shared document file. Every day, some members of the student council write the sequence TMT (short for Towa Maji Tenshi) in it.

However, one day, the members somehow entered the sequence into the document at the same time, creating a jumbled mess. Therefore, it is Suguru Doujima's task to figure out whether the document has malfunctioned. Specifically, he is given a string of length $ n $ whose characters are all either T or M, and he wants to figure out if it is possible to partition it into some number of disjoint subsequences, all of which are equal to TMT. That is, each character of the string should belong to exactly one of the subsequences.

A string $ a $ is a subsequence of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero) characters.

## 说明/提示

In the first test case, the string itself is already a sequence equal to TMT.

In the third test case, we may partition the string into the subsequences TMTMTT. Both the bolded and the non-bolded subsequences are equal to TMT.

## 样例 #1

### 输入

```
5
3
TMT
3
MTT
6
TMTMTT
6
TMTTTT
6
TTMMTT```

### 输出

```
YES
NO
YES
NO
YES```

# 题解

## 作者：Daidly (赞：16)

用 $numT,numM$ 分别表示 $T,M$ 的个数。

先从前往后遍历：

- 若在某一时刻 $T$ 的个数小于 $M$ 的个数，则完不成匹配，$f=0$。

再从后往前遍历：

- 若在某一时刻 $T$ 的个数小于 $M$ 的个数，则完不成匹配，$f=0$。

最后判断 $f$ 是否为 $0$（是否能完成匹配），且 $T$ 的个数是否是 $M$ 的 $2$ 倍。

输出 `YES` 或 `NO` 即可。

注意 $numT,numM,f$ 每次初始化。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,numT,numM,f=1;
string a;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>a;a=" "+a;
		for(int i=1;i<=n;++i){
			if(a[i]=='T')numT++;
			if(a[i]=='M')numM++;
			if(numT<numM){f=0;break;}
		}numT=0,numM=0;
		for(int i=n;i>=1;--i){
			if(a[i]=='T')numT++;
			if(a[i]=='M')numM++;
			if(numT<numM){f=0;break;}
		}
		if(f==0||numT!=numM*2)puts("NO");
		else puts("YES");
	    numT=0,numM=0,f=1;
	}
	return 0;
}
```

---

## 作者：Night_sea_64 (赞：3)

~~终于有一道我会的题能交题解了。~~

题目大意见[原题](https://www.luogu.com.cn/problem/CF1509B)

很多人可能一开始想的就是统计个数就行了。但是第二组样例能让这种思路 WA 掉，因为 $\texttt{M}$ 前面没有 $\texttt{T}$。很显然，光统计个数是不行的。

我们发现，在从左到右第 $x$ 个 $\texttt{M}$，前面一定至少有 $x$ 个 $\texttt{T}$。因为在对于所有为 $\texttt{TMT}$ 的子序列，$\texttt{TMT}$ 所有的 $\texttt{M}$ 都在一个 $\texttt{T}$ 后面。所以如果不满足上面的要求，一定是错的。

同理可证在从右到左第 $x$ 个 $\texttt{M}$，后面一定也至少有 $x$ 个 $\texttt{T}$。

但是直接在每次循环里都统计一遍肯定是不行的。我们可以用前缀和来维护字符串里 $\texttt{T}$ 的个数。用总个数减去 $\texttt{T}$ 的个数，当然就是 $\texttt{M}$ 的个数。判断到这里的 $\texttt{M}$ 是否成立，只用判断一下前面和后面的个数就行了。

#### AC Code：

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int a[100010];//前缀和数组
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        bool flag=1;
        string s;
        cin>>n>>s;
        for(int i=0;i<n;i++)
            a[i+1]=a[i]+(s[i]=='T');//记录前缀和。如果等于 T 就加上 1 个。
        for(int i=0;i<n;i++)
            if(s[i]=='M')
                if(a[i+1]<i+1-a[i+1]||a[n]-a[i]<n-i-a[n]+a[i])
                {
                    flag=0;
                    break;
                }
        		//a[i+1] 是前面 T 的个数，a[n]-a[i] 是后面 T 的个数。
                //i+1-a[i+1] 是前面的 M 的个数，n-i-a[n]+a[i] 是后面的 M 的个数。
        if(flag&&(n-a[n])*2==a[n])cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
        //n-a[n] 是 M 的总个数，a[n] 是 T 的总个数。
    }
    return 0;
}
```


---

## 作者：badFlamesへ (赞：3)

### $\mathtt{"Overthrow\;the\;dictator!"}$
### $\mathtt{"Long\;live\;revolution!"}$
题意：给定一个由字符 $T$ 和字符 $M$ 构成的、长度为 $n$ 的字符串 $s$，你要把它划分成若干个不相交的子序列，使得所有子序列都等于 $TMT$。判断是否有解，有解输出 YES，无解输出 NO。$T$ 组数据。

那么，显然对于每一个 $M$ ，它的左右都要有足够的 $T$ 来使它组成一个 $TMT$。

那究竟需要多少 $T$ 才满足当前 $M$ 满足 $TMT$ 呢？

看几个样例：
```
9
TTMMTTTMT
YES
3
MTT
NO
```
样例1的总 $M$ 个数为 $3$ ，第 $1$ 个 $M$ 的左边至少需要 $1$ 个 $T$， 右边至少需要 $3$ 个 $T$， 而第 $2$ 个左边至少需要 $2$ 个 $T$， 右边至少需要 $2$ 个 $T$，以此类推。

而样例 $2$ 中的 $M$ 左侧的 $T$ 数量不足，所以不能组成 $TMT$。

因为每一个 $TMT$ 中的 $M$ 都需要左右各至少一个 $T$ ，所以得到结论：对于从左往右的第 $i$ 个 $T$ 来说，它的左边必须要有 $i$ 个 $T$， 右边必须要有 $n-i+1$ 个 $T$ 。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
 
int t, n;
string s;
int cnt_t, cnt_m, len;//T的个数，M的个数，字符串长度
 
inline bool check() {//检查字符串的函数
	cnt_t = cnt_m = 0;
	for(int i = 0; i < len; i++) {//正着统计T与M的实时关系
		if(s[i] == 'T') cnt_t++;
		if(s[i] == 'M') cnt_m++;
		if(cnt_t < cnt_m) return false;//发现不符合上述关系就直接false
	}
	if(cnt_t != 2 * cnt_m) return false;//T与M的数量不匹配也直接false
	cnt_t = cnt_m = 0;
	for(int i = n - 1; i >= 0; i--) {//反着来一遍
		if(s[i] == 'T') cnt_t++;
		if(s[i] == 'M') cnt_m++;
		if(cnt_t < cnt_m) return false;
	}
	return true;//返回true
}
 
signed main() {
	cin >> t;
	while(t--) {
		cin >> n >> s;
		len = s.length();
		if(check()) puts("YES");//输出结果
		else puts("NO");
	}
}
```

QWQWQ


---

## 作者：___cjy__ (赞：2)

# CF1509B TMT Document 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1509B)

[更好的阅读体验](https://www.luogu.com.cn/blog/chengjiayi666/solution-cf1509b)



### 题目大意：

给定一个由 ```T``` 和 ```M``` 组成的字符串，把它划分成若干个不相交的子序列，使得所有子序列都等于 ```TMT``` 是否有解。

### 正文：

显然，对于任何 $i(i \le n)$，$s_{1 \sim i}$ 与 $s_{i \sim n}$ 中，```T``` 的个数始终大于 ```M``` 的个数。并且 $s$ 中 ```T``` 的个数是 ```M``` 的个数的 $2$ 倍。因此我们可以根据这两点特性来判断是否有解。

同时，需要注意的是，```TMT``` 这个串具有对称性，也就说明无论从前还是后遍历串 $s$，这两点特性都成立。

### AC Code：

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 114514
#define INF 0x7fffffff

using namespace std;

int T, n, flag, t, m;
string s;

signed main(){
	cin >> T;
	
	while(T--){
		flag = t = m = 0;
		cin >> n >> s;
		
		for(int i=0; i<n; i++){//正序遍历 
			if(s[i] == 'T') t ++;
 			if(s[i] == 'M') m ++;
 			if(m > t){
 				flag = 1;
 				break;
			}
		}
		
		t = m = 0;
		for(int i=n-1; i>=0; i--){//逆序遍历 
			if(s[i] == 'T') t ++;
 			if(s[i] == 'M') m ++;
 			if(m > t){
 				flag = 1;
 				break;
			}
		}
		if(!flag && t == 2 * m) cout << "YES\n";
		else cout << "NO\n";
	}
	
	return 0;
}
```

---

## 作者：OoXiao_QioO (赞：1)

看到数据大小，瞬间原地去世，这么大的数据，暴力在想啥？

提供一种 $O(TN)$ 的方法。

首先我们看看 $\verb!TMT!$ 能不能找到一些规律。

发现这种字符串属于两面包夹芝士，$T$ 的个数是 $M$ 的个数的 $2$ 倍，所以第一版程序出炉了。

[第一版代码](https://www.luogu.com.cn/paste/eqp4iupo)


不用提交都能知道铁定是错误的，因为如果有一个字符串 $\verb!TTM!$，这个程序就爆了，那么怎么解决这个问题呢？我们可以进行更进一步的探讨。

进一步的研究 $\verb!TMT!$，发现在累计 $T$ 和 $M$ 出现的次数时，$T$ 出现的的次数总是 $\ge$ $M$ 的，所以我们可以进一步的优化。

[第二版代码](https://www.luogu.com.cn/paste/sb9ghdht)

那么问题又来了，如果字符串是 $\verb!TTTMTMTTM!$ 呢？很容易地发现，最后一个 $M$ 的后面没有任何东西，肯定是输出 $\verb!NO!$，但是我们的程序却输出了 $\verb!YES!$，所以要继续更改代码。

我们可以换个角度来思考，我正着判断不可以，那我反着来判断呢？这种情况不就能解决了吗？于是我们可以写出下面的代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	//定义
	
	int n,i,t,cntT,cntM,f;// f 表示从前往后和从后往前 cntT 是否一直 > cntM，也是输出的关键。 
	char s[500001];
	
	//输入
	 
	cin>>t;
	
	//操作
	
	while(t--)
	{
		cin>>n;
		scanf("%s",s);
		cntT = cntM = 0;//计数器先清零。 
		f = 1;//假设一开始可以成立。 
		
		//正着扫一遍 
		
		for(i=0;i<n;i++)
		{
			if(s[i]=='M') 
				cntM++;
			else
				cntT++;
			if(cntM>cntT)//如果 cntM > cntT，即使是一秒，我们都要 break，因为这样的字符串无论如何都不能满足要求。 
			{
				f = 0;//把旗子扳倒。 
				break;//果断 break。 
			}
		}
		
		
		//反着扫一遍 
		
		cntT = cntM = 0;//无论如何，两个计数器都要清零。 
		for(i=n-1;i>=0;i--)//倒着扫 
		{
			if(s[i]=='M')
				cntM++;
			else
				cntT++;
			if(cntM>cntT)//和正着扫原理一致，这里不做过多解释。 
			{
				f = 0;
				break;
			}
		}
		printf("%s\n",(cntT==cntM*2&&f)?"YES":"NO");//根据我们最早找出的规律，和关于前扫后扫的规律全都满足才能输出 YES，否则输出 NO。 
	}
	return 0;
}
```
提交一看，果然 $\verb!AC!$ 了，所以我们做题要从多个方面去找出问题的所在，希望大家能够早日 $\verb!AC!$ 此题。

---

## 作者：Sora1336 (赞：1)

这题我的思路可能略有复杂。

检查每一个 `M` 前面的 `T` 和后面的 `T` 的个数，分别存到 front 和 back 数组里。

然后看看对于每一个 `M` ，前面是否都有一个未被匹配到的 `T`。我在这里用的是 lost 来检查是否有匹配的，看看代码就会明白的。

然后再把字符串反向以上述方式扫描一遍，最后看看是不是所有的 `T` 都被匹配到了。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <stack>
using namespace std;
const int maxn = 2 * 1e5 + 5;
void solve() {
	string a;
	int n, tnum = 0, lost = 0;
	bool flg = 1;
	cin >> n >> a;
	a = '?' + a;
	int f[100005], b[100005];
	for(int i = 1; i <= n; i ++) {
		if(a[i] == 'T') tnum ++;
		if(a[i] == 'M') f[i] = tnum;
	} tnum = 0;
	for(int i = n; i >= 1; i --) {
		if(a[i] == 'T') tnum ++;
		if(a[i] == 'M') b[i] = tnum;
	} 
	for(int i = 1; i <= n; i ++) {
		if(a[i] == 'M') {
			if(f[i] - lost != 0) {
				lost ++;
			} else {
				flg = 0;
				break;
			}
		}
	} int check = lost; lost = 0;
	for(int i = n; i >= 1; i --) {
		if(a[i] == 'M') {
			if(b[i] - lost != 0) {
				lost ++;
			} else {
				flg = 0;
				break;
			}
		}
	} if(lost + check != tnum) flg = 0;
	if(flg) puts("YES");
	else puts("NO");
}
int main() {
	int t;
	cin >> t;
	while(t --) solve();
}
```

---

## 作者：james1BadCreeper (赞：1)

乍看之下没什么思路，观察所要求的字符串 `TMT`，可以发现这个字符串很有特点，`M` 在中间，`T` 在两边。那么是否可以把着 `M` 来匹配呢？

匹配的思路：对于每一个 `M`，在它左边要有一个和它对应的 `T`，右边也需要有一个。但是选哪一个呢？    
注意到我们的选择不能影响其它 `M` 的选择，比如字符串 $S=\text{TMTMTT}$，那么（从 $0$ 编号）$S_1$ 如果匹配了 $S_0$ 和 $S_2$，那么 $S_3$ 就无法进行正常匹配了，所以 $S_1$ 应匹配 $S_0$ 和 $S_5$。   
那么显然，对于一个 `M`，原字符串最左边的 `T` 一定是它左边需要的 `T` 最好的匹配选择。   
到这，这题的答案已经呼之欲出了。大不了我们先从左往右匹配一次，在从右往左匹配一次呗？   

然而这么做还是太复杂了。注意对于一个 `M`，原字符串最右边的 `T` 可不一定一定是它右边需要的 `T` 最好的匹配选择。因为这样可能会导致接下来的 `M` 无法正常匹配。也就是说，我们接下来的任务是思考 `M` 右边的 `T` 如何进行匹配。

首先我们假定 `T` 的个数是 `M` 的二倍，这很显然（否则必定无解）。

定义：

```cpp
vector <int> M, T;
for (int i = 0; i < n; ++i)
    if (s[i] == 'M') M.push_back(i);
    else T.push_back(i);
```

$T$ 的前半段会被用于匹配 $M$ 左边的 $T$， 后半段匹配右边。

为什么可以这样做？因为你想匹配 `M` 左边的 `T`， 肯定这些 `T` 是越往前匹配成功的可能性越大。而想匹配右边的，自然是这个 `T` 越往后越好。

接下来：

```cpp
int flag = 1;
for (int i = 0; i < M.size(); ++i)
{
    if (T[i] > M[i] || T[i + M.size()] < M[i])
    {
        puts("NO");
        flag = 0;
        break;
    }
}
if (flag) puts("YES");
```

`T[i] > M[i]` 是用来判断左半边能否匹配的，`T[i + M.size()] < M[i]` 是右半边。这段代码用来实现上文所说的“$T$ 的前半段会被用于匹配 $M$ 左边的 $T$， 后半段匹配右边”。

所以最后放出完整代码：

```cpp
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
 
using namespace std;
 
int n;
string s;
vector <int> M, T;
 
int main(void)
{
    int op;
    cin >> op;
    while (op--)
    {
        cin >> n >> s;
        if (n % 3 != 0) puts("NO");
        else
        {
            M.clear();
            T.clear();
            for (int i = 0; i < n; ++i)
                if (s[i] == 'M') M.push_back(i);
                else T.push_back(i);
 
            if (T.size() != M.size() * 2) puts("NO");
            else
            {
                int flag = 1;
                for (int i = 0; i < M.size(); ++i)
                {
                    if (T[i] > M[i] || T[i + M.size()] < M[i])
                    {
                        puts("NO");
                        flag = 0;
                        break;
                    }
                }
                if (flag) puts("YES");
            }
        }
    }
    return 0;
}
```

---

## 作者：__Dist__ (赞：0)

### 题目描述
[原题](https://www.luogu.com.cn/problem/CF1509B)
### 思路分析

~~做了一半暴力突然发现数据有点大。~~

言归正传。此题思路并不难，我们先假设有 $ a $ 个 ``` M ``` 和 $ b $ 个 ```T```。我研究了一下数据，发现如果有解，则 $ a $ 和 $ b $ 必须满足以下条件：

1. 从前往后看到第 $ i $ 个字符时，$ a \le b $。

2. 从后往前看到第 $ i $ 个字符时，$ a \le b $。

3. 最终计算答案时， $ b=2 \times a $。

这样题目就非常简单了。

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
int main(){
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		string s;
		cin>>s;
		bool f=1;//记录条件是否成立
		int a=0;//记录M的数量
		int b=0;//记录T的数量
		for(int i=0;i<n;i++){//正着看
			if(s[i]=='T') b++;
			else a++;
			if(a>b){//不符合条件直接break
				f=0;
				break;
			}
		}
		a=b=0;//清空
		if(f){//如果符合条件1
			for(int i=n-1;i>=0;i--){//反着看
				if(s[i]=='T') b++;
				else a++;
				if(a>b){//不符合条件直接break
					f=0;
					break;
				}
			}
		}
		if(f && a*2==b) puts("YES");
		else puts("NO");
	}
	return 0;
}
```


---

## 作者：CheZiHe929 (赞：0)

# CF1509B 题解

## 原题链接
[**洛谷CF1509B**](https://www.luogu.com.cn/problem/CF1509B)

## 思路分析
一看到这么大的数据，那么暴力肯定是过不了的，所以我们自然会想到 $O(TN)$ 的做法，我们通过理解题意并观察样例不难发现，如果有解那么一定满足以下条件：
1. 正着看，无论何时 $M$ 的数量都要 $\leq T$ 的数量。
2. 反过来看也要满足第一个条件。
3. 在整个字符串中，$T$ 的数量一定是 $M$ 的 $2$ 倍。

有了这三个条件，这道题自然就简单了。前两个条件可以用一个 $f$ 来维护是否成立，而第三个条件我们可以在输出时与 $f$ 一起判断。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[500005]; 
signed main(){
	int n,T,t,m;
	//T为测试组数，t和m分别代表字符串中t和m的数量
	cin>>T;
	while(T--){
		cin>>n;
		cin>>s;
		t=m=0;//计数器清零
		bool f=1;//先假设成立
		for(int i=0;i<n;i++){//判断是否满足条件一 
			if(s[i]=='M')m++;
			else t++;
			if(m>t){//不满足条件一 
				f=0;
				break; 
			} 
		}
		t=m=0;//同上，计数器清零 
		for(int i=n-1;i>=0;i--){//判断是否满足条件二 
			if(s[i]=='M')m++;
			else t++;
			if(m>t){//不满足条件二 
				f=0;
				break;
			} 
		}
		if(f==1&&m*2==t)//如果三个条件都满足 
			cout<<"YES"<<endl;
		else  cout<<"NO"<<endl;//只要有一个不满足 
	}
	return 0; 
}
```

**无注释版的我放到了[这里](https://www.luogu.com.cn/paste/384niibp)**

## [AC记录](https://www.luogu.com.cn/record/110610482)

**THE END.**

**THANK YOU.**

---

## 作者：TainityAnle (赞：0)

**题目大意：**

给定一个长度为 $n$ 的串，问能否将其分割成若干（$n/3$）个 `TMT`。

****

先看数据范围：

$1\leq T\leq5\times10^3$

$3\leq n<10^5$

那么必须用 $O(n)$ 的算法。

我们就要知道什么样的字符串可以满足这样的要求，并且遍历字符串就能判断。

题目所述的“分割”就是可以在任意位置开始拿出连续任意个的任意字符，但是不能改变顺序。

当任意一个 `M` 前后各有一个 `T` 的时候，条件就成立。不用管中间是否有其它东西。

比如样例中的 `TMTMTT`，如果先取前面的 `TMT`，后面的 `MTT` 就不行了，但是如果取前两个 `TM` 与最后的 `T`，就可以成立。

通过这个我们又能得到一条结论：我们不需要考虑某一 `M` 前后是否有能与其配对的 `T`，我们只需要考虑个数。

**代码思路：**

现在题目变成了找是否存在对于任何一个 `M`，其前面都存在数量大于其前面 `M` 的数量的 `T`。

只需要两个变量 $m$ 和 $t$，分别储存 $S_i$ 前的 `M` 的数量和 `T` 的数量。完事按照前面说的，要是一旦 $m>t$ 了就不行。

正着遍历以判断前面有，反着遍历以判断后面有。

还需要注意一个点，`T` 和 `M` 是有对应关系的，即 $t=2m$。

[AC Code](https://codeforces.com/problemset/submission/1509/196361324)

---

## 作者：Hooch (赞：0)

我们发现判断是否有解，可以直接转化为**对于每一个 `M` 都能找到它前面的一个 `T` 和后面的一个 `T`**。

而且对于一个序列，**`M` 的数量一定是 $\frac{n}{3}$, `T` 的数量一定是 $\frac{2n}{3}$**，否则就无法全部配对。

用这个样例来模拟：

```
TMTMTT
```

我们找到 $i=2$ 的 `M`，找到了前面 $i=1$ 的 `T`，和最后 $i=6$ 的 `T`。

则 $i=4$ 的 `M`，只需要与剩下的 `T` 配对即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n; string s;
main() {
	ios::sync_with_stdio(0);
	cin >> t;
	while (t--) {
		cin >> n >> s; int cntt = 0, ns = 0; bool flg = 0;
		for (int i(0); i < n; ++i) {
			if (s[i] == 'T') ++cntt;
			else {
				++ns;
				if (cntt < ns) flg = 1;
			}
		} ns = cntt = 0; //看前面有没有T配对
		for (int i(n - 1); ~i; --i) {
			if (s[i] == 'T') ++cntt;
			else {
				++ns;
				if (cntt < ns) flg = 1;
			}
		} //看后面有没有T配对
		puts(flg || (cntt != 2 * ns) ? "NO" : "YES");
	}
}
```





---

## 作者：Little09 (赞：0)

发现 `TMT` 对称，我们把题目转化成找到每个 `M` 在它左右两边各划掉一个 `T`。所以我们只要从左往右扫一遍，再从右往左扫一遍，如果某时 `T` 的个数不足 `M` 的个数，那么显然无法完成匹配了。要是到最后仍然满足条件，那么显然可以完成了。

场上做了我 10 min/ll

部分代码：

```cpp
void work()
{
	n=read();
	for (int i=1;i<=n;i++) 
	{
		char x;
		cin >> x;
		if (x=='M') a[i]=1;
		else a[i]=0;
	}
	for (int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
	if (s[n]!=n/3) 
	{
		puts("NO");
		return; 
	}
	for (int i=1;i<=n;i++)
	{
		if (a[i]==1&&(i-1-s[i-1]<=s[i-1])) 
		{
			puts("NO");
			return; 	
		}
	}
	s[n+1]=0;
	for (int i=n;i>=1;i--) s[i]=s[i+1]+a[i];
	for (int i=1;i<=n;i++)
	{
		if (a[i]==1&&(n-i-s[i+1]<=s[i+1])) 
		{
			puts("NO");
			return; 	
		}
	}
	puts("YES");
	return;
}
```

代码写得比较复杂，事实上不需要 $s$ 数组记录前缀和，可以用变量直接记录并比较。

---

## 作者：jiangtaizhe001 (赞：0)

题目翻译：给出一个序列，只包含 `T` 和 `M` ，问是否能将这个字符串分割成若干个不重合的字串，让每个串都是 `TMT` 。  
我们发现当且仅当满足一下条件的序列才可能是满足题意的：
1. `T` 的数量是 `M` 的数量的两倍  
1. 对于每个字符串的前缀， `T` 的数量一定大于等于 `M` 的数量  
1. 对于每个字符串的后缀， `T` 的数量一定大于等于 `M` 的数量  

我们只需要检验每个前缀和后缀就可以了，也就是扫两次，算法复杂度 $O\left(N\right)$  
代码：
```cpp
#include<cstdio>
#include<iostream>
#define maxn 100039
using namespace std;
//#define debug
typedef int Type;
inline Type read(){
	Type sum=0;
	int flag=0;
	char c=getchar();
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-') c=getchar(),flag=1;
	while('0'<=c&&c<='9'){
		sum=(sum<<1)+(sum<<3)+(c^48);
		c=getchar();
	}
	if(flag) return -sum;
	return sum;
}
char s[maxn];
int T,n;
int check1(){
	int cnt1,cnt2;
	cnt1=cnt2=0;
	for(int i=1;i<=n;i++)
	    if(s[i]=='T')
	        cnt1++;
	    else{
	    	cnt2++;
	    	if(cnt1<cnt2) return 0;
		}
	if(cnt1==cnt2*2) return 1;
	else return 0;
}
int check2(){
	int cnt1,cnt2;
	cnt1=cnt2=0;
	for(int i=n;i>=1;i--)
	    if(s[i]=='T')
	        cnt1++;
	    else{
	    	cnt2++;
	    	if(cnt1<cnt2) return 0;
		}
	return 1;
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
    T=read();
    while(T--){
    	n=read();
    	scanf("%s",s+1);
    	if(check1()&&check2()) puts("YES");
    	else puts("NO");
	}
	return 0;
}

```

---

## 作者：RedreamMer (赞：0)

[$\huge\texttt{CF1509B}$](https://www.luogu.com.cn/problem/CF1509B)

标签：贪心

## 题意

给定一个仅包含 `T` 和 `M` 的字符串，求能不能把其不重复分割成若干个 `TMT` 的子序列且无剩余。

## 思路

贪心地想，首先对于每个 `M`，我们要先保证其左边能选一个 `T`，可以从左到右顺序遍历，判断每个前缀中 `T` 的个数是否大于等于M的个数（也可以理解为遇到 `T` 将 `T` 的个数 $+1$ 遇到 `M` 将 `T` 的个数 $-1$，实际是一样的），这样做使得每个 `M` 必然能在左边找到属于它的唯一的 `T`。

但对于判断每个 `M` 是否能选一个右边的`T` 是和上一部分中哪些 `T` 被选择是有关的，也是贪心地想，因为越右边的 `M` 选择的数量越少，我们要保证右边的 `T` 足够多，所以我们让第一次选择的 `T` 尽量靠左，再顺序判断每个后缀没选择的 `T` 的数量是否大于等于 `M` 的数量即可。

记得判 `T` 未被选择完的情况。

## 代码

去除了冗杂的码头。

```cpp
int a, t;
char s[N];
bool vis[N];
queue<int> tmp;

signed main() {
	// freopen("in1.in", "r", stdin);
	t = read();
	while (t--) {
		a = read();
		rep(i, 1, a) vis[i] = 0;
		scanf("%s", s + 1);
		bool ans = 0;
		while(siz(tmp)) tmp.pop();
		rep(i, 1, a) {
			if (s[i] == 'T') tmp.push(i);
			if (s[i] == 'M') {
				if (!siz(tmp)) {
					puts("NO");
					ans = 1;
					break;
				}
				vis[tmp.front()] = 1;
				tmp.pop();
			}
		}
		if (ans) continue;
		while(siz(tmp)) tmp.pop();
		per(i, a, 1) {
			if (s[i] == 'T' && !vis[i]) tmp.push(i);
			if (s[i] == 'M') {
				if (!siz(tmp)) {
					puts("NO");
					ans = 1;
					break;
				}
				vis[tmp.front()] = 1;
				tmp.pop();
			}
		}
		if (ans) continue;
		rep(i, 1, a) if (s[i] == 'T' && !vis[i]) {
			puts("NO");
			ans = 1;
			break;
		}
		if (!ans) puts("YES");
	}
	return 0;
}
```

---

