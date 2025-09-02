# Ela Sorting Books

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737A/56ed0d2349bc5e2f6cd6bfba1e2e6140ddd296a6.png)Ela loves reading a lot, just like her new co-workers in DTL! On her first day after becoming an engineer in DTL, she is challenged by a co-worker to sort a heap of books into different compartments on the shelf. $ n $ books must be split into $ k $ compartments on the bookshelf ( $ n $ is divisible by $ k $ ). Each book is represented by a lowercase Latin letter from 'a' to 'y' inclusively, which is the beginning letter in the title of the book.

Ela must stack exactly $ \frac{n}{k} $ books in each compartment. After the books are stacked, for each compartment indexed from $ 1 $ to $ k $ , she takes the minimum excluded (MEX) letter of the multiset of letters formed by letters representing all books in that compartment, then combines the resulting letters into a string. The first letter of the resulting string is the MEX letter of the multiset of letters formed by the first compartment, the second letter of the resulting string is the MEX letter of the multiset of letters formed by the second compartment, ... and so on. Please note, under the constraint of this problem, MEX letter can always be determined for any multiset found in this problem because 'z' is not used.

What is the lexicographically greatest resulting string possible that Ela can create?

A string $ a $ is lexicographically greater than a string $ b $ if and only if one of the following holds:

- $ b $ is a prefix of $ a $ , but $ b \ne a $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears later in the alphabet than the corresponding letter in $ b $ .

The minimum excluded (MEX) letter of a multiset of letters is the letter that appears earliest in the alphabet and is not contained in the multiset. For example, if a multiset of letters contains $ 7 $ letters 'b', 'a', 'b', 'c', 'e', 'c', 'f' respectively, then the MEX letter of this compartment is 'd', because 'd' is not included in the multiset, and all letters comes before 'd' in the alphabet, namely 'a', 'b' and 'c', are included in the multiset.

## 说明/提示

In the first test case, the books can be divided into $ 3 $ compartments as below:

- the first compartment contains the books with indices $ 1, 2, 3, 7 $ : $ multiset_1 = \{ $ 'c', 'a', 'b', 'd' $ \} $ $ \rightarrow $ $ MEX(multiset_1) = $ 'e'
- the second compartment contains the books with indices $ 4, 5, 6, 9 $ : $ multiset_2 = \{ $ 'c', 'c', 'a', 'b' $ \} $ $ \rightarrow $ $ MEX(multiset_2) = $ 'd'
- the third compartment contains the remaining books $ 8, 10, 11, 12 $ : $ multiset_3 = \{ $ 'a', 'a', 'a', 'c' $ \} $ $ \rightarrow $ $ MEX(multiset_3) = $ 'b'

Therefore, the answer is 'edb'. It can be proven that there is no way that Ela can arrange the books so that it results in a lexicographically greater string.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737A/407eef03cdf4780f728db3b04f21cd023d792a00.png)

## 样例 #1

### 输入

```
5
12 3
cabccadabaac
12 6
cabccadabaac
12 12
cabccadabaac
25 1
abcdefghijklmnopqrstuvwxy
10 5
bcdxedbcfg```

### 输出

```
edb
ccbbba
bbbbbaaaaaaa
z
aaaaa```

# 题解

## 作者：Little_x_starTYJ (赞：6)

### 题意大意
给你一个字符串 $s$ 将其重新排列后，分为 $k$ 个段，使得每段中未出现的最小字母构成的序列的字典序最大。

### 思路

既然题目要求代表字符最大，就得尽可能满足该段为从 $a$ 开始的连续的子串的。

然后我们只需要用一个数组 $a$ 记录每个字母的出现次数，然后遍历 $a$，每次找到目前 $a$ 中的最小值，输出 $a_i$，$a$ 数组里面所有不为 $0$ 的数都减去 $a_i$。

如果没有找到合适的答案，就输出 $k + 1$ 个字母即可。

---

## 作者：with_no_signal (赞：5)

# 题意简述

给定字符串 $s$ 将其重新排列后分为 $k$ 个段，使得每段中未出现的最小字母（下称“代表字符”）构成的序列的字典序最大。

输出这一序列。
## 思路

要求代表字符最大，则一定尽可能满足该段为从 a 开始的连续字串；

因为若无 a，该段的代表字符就是 a，同理，要求字串是连续的字母也是这个原因。

我们记录下原始串中每个字母的出现次数，每次取代表字符从第 $1$ 个字母遍历到第 $k$ 个字母并减一，直到出现第一个出现次数为 $0$ 的字母为止。输出这一字母。

若第 $1$ 个字母到第 $k$ 个字母中没有出现次数为 $0$ 的字母，输出第
$k+1$ 个字母即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n,k;
int cnt[31];
string str;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>t;
	while(t--)
	{
		memset(cnt,0,sizeof(cnt));
		cin>>n>>k>>str;
		for(int i=0; i<str.size(); i++)
		{
			cnt[str[i]-'a'+1]++;
		}
		for(int i=1; i<=k; i++)
		{
			bool flag=true;
			for(int j=1; j<=n/k; j++)
			{
				if(cnt[j]==0)
				{
					flag=false;
					cout<<(char)(j+'a'-1);
					break;
				}
				cnt[j]--;
			}
			if(flag)cout<<(char)(n/k+'a');
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：linbaicheng2022 (赞：1)

# Ela Sorting Books 题解

## 题意

[题目传送门](https://www.luogu.com.cn/problem/CF1737A)

有一个长度为 $n$ 的字符串，现将其等分为 $k$ 段，使得每段未出现的最小字符构成的字符串字典序最大，求这个字符串。

## 思路

不难发现，因为每一段长度相同，设这个长度为 $L$，那么这一段的 MEX 字母最差的情况也是第 $L + 1$ 个字母，不可能会更多，否则就说明长度为 $L$ 的字串中出现了 $L + 1$ 个不同的字符，显然是不成立的。

所以我们查找 $k$ 次，每次就遍历字母表中的前 $L$ 个字符，找到第一个出现次数为 $0$ 的字符并输出即可。

如果在前 $k$ 个字符中没有找到，则说明这个字串是前 $k$ 个字符的全排列，那么输出第 $k + 1$ 个字符即可。

## 代码

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 210;
int n, k, sum[N];
string str;

int main () {
	int T;
	cin >> T;
	while (T --) {
		memset (sum, 0, sizeof sum); //数组记得清零
		cin >> n >> k >> str;

		for (int i = 0; i < n; i ++) //统计每个字符出现的次数
			sum[str[i] - 'a' + 1] ++;

		for (int i = 1; i <= k; i ++) {
			int ok = 0;
			for (int j = 1; j <= n / k; j ++) { //遍历 L 个字符
				if (sum[j] == 0) { //如果这个字符没有出现过，就输出
					ok = 1;
					cout << char (j + 'a' - 1);
					break;
				}
				
				sum[j] --; //遍历过这个字符了，将这个字符出现次数减一
			}

			if (ok == 0) //如果前面没有找到，就输出第 L + 1 个字符
				cout << char (n / k + 'a'); 
		}

		cout << endl;
	}
	return 0;
}
```

---

## 作者：ask_silently (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF1737A)

# 题意
题目要求将一个字符串 $s$ 分成 **大小相等** 的 $k$ 份。并要求 $k$ 组中字典序第一个没有出现的字母组成的字符字典序最大。

# 思路
既然要第一个没有出现的字母最大，我们考虑让字典序前面的字母连续出现，这样才能保证第一个没有出现的字母最大。

我们考虑将字母出现次数统计出来，将字典序前 $k$ 个字母先选了，保证能取到的字母是连续的，如果前 $k$ 个字母都出现了，我们输出 $k+1$ 就行了。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,k;
int zimu[100];

string s;

inline int read(){
	int t=0,f=1;
	register char c=getchar();
	while(c<48||c>57) f=(c=='-')?(-1):(f),c=getchar();
	while(c>=48&&c<=57) t=(t<<3)+(t<<1)+(c^48),c=getchar();
	return t*f;
}

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	T=read();
	while(T--){
		memset(zimu,0,sizeof(zimu));
		n=read(),k=read();
		s="";
		cin>>s;
		for(int i=0;i<s.size();i++) zimu[s[i]-'a'+1]++;
		for(int i=1;i<=k;i++){
			bool pd=false;
			for(int j=1;j<=n/k;j++){
				if(!zimu[j]){
					pd=true;
					cout<<(char)(j+'a'-1);
					break;
				}
				zimu[j]--;
			}
			if(!pd) cout<<(char)(n/k+'a');
		}
		cout<<"\n";
	}
	return 0;
}

```


---

## 作者：Walrus (赞：0)

## 题意
一共 $t$ 组数据，每组数据有一个字符串，其长度为 $n$，再给你一个整数 $k$，并且保证 $k|n$，将这个字符串分成 $k$ 段，求将每一份的字符串的 MEX 合并成一个新字符串，求得到最大字典序的字符串。

- 这里的 **MEX** 的定义为：**每个字符串中最早不存在于这个字符串中的字符**。比如，字符串 **acdde** 中的 **MEX** 就是字符 **b**，因为字符 b 是此字符串中最早不存在于其中的字符。

## 分析
看到要求的字符串**字典序最大**，那就要合理安排每段的字符应该是有哪些。显然，我们的字符串要想 MEX 最大，那么要尽量多地出现字典序比较小的字符，这样才能使 MEX 尽可能大，而不是将大的分入这些字符串中，如果这样的话那么字典序较小的就不会出现，导致 MEX 偏小，所以我们的策略是：**尽量将字典序较小的字符先填进去，这样我们要求的字符串靠前的位置的字符的字典序就会更大，进而使整个字符串的字典序最大**。

从小到大枚举每位，先用字典序较小的填，如果没了就直接输出这个字符，要是这一段可以挨着填满每一个字符，那就输出最大字典序字符的下一位。

## 代码
这篇文章只用于解释说明，毕竟那些题解的代码几乎一模一样，那我就不放代码了。~~还是放一下吧，因为我的代码可好看了。~~
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e2 + 5;

char s[N];
int _, n, k, num[30], maxx;


int main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> _;
	while(_--) {
		maxx = 0;
		memset(num, 0, sizeof num);
		cin >> n >> k;
		cin >> (s + 1);
		for(int i = 1;i <= n;i++)
			num[s[i] - 'a' + 1]++;
		for(int i = 1;i <= k;i++) {
			bool flag = 1;
			for(int j = 1;j <= n / k;j++) {
				if(!num[j]) {
					flag = 0;
					cout << char(j + 96);
					break;
				}
				--num[j];
			}
			if(flag)
				cout << char(n / k + 97);
		}
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
又是一道喜闻乐见的日本字符串题。
## 分析。
要使拼接起来的字符串的字典序最大，那么我们就要尽量让每一个分成的子段都尽量以 $a$ 开头，使每一段中的第一个在字母表中的未出现的数比 $a$ 大，才能尽量使字典序最大。但是如果没有 $a$ 的话，我们只能让 $a$ 作为该子段的最大字符了。

即分成 $k$ 份，然后让每个子串的开头尽量为 $a$ 字符。如果没有 $a$ 那就用其它的补充，此时该子串的贡献就是一个 $a$ 字符。

然后我们遍历数组，用桶记录每一个字符的出现次数，每次都将遍历过的字母的桶数量减一，找到第一个数量为零的桶输出即可。

代码如下，仅供参考：
```
#include<iostream>
#include<cstring>
using namespace std;
int t1,n,k;
char ch;
int pd,t[205];
int main(){
	cin>>t1;
	while(t1--){
		for (int i=1;i<=30;i++) t[i]=0;
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			cin>>ch;
			t[ch-'a'+1]++;//用桶将26个字母分成26个桶。
		}
		for(int i=1;i<=k;i++){
			pd=0;
			for(int j=1;j<=n/k;j++){
				if(t[j]==0){
					pd=1;
					cout<<(char)(j+'a'-1);
					break;
				}//找到第一个未出现的字符。
				t[j]--;
			}
			if(!pd){
			    cout<<(char)(n/k+'a');
			}
		}
		cout<<"\n";
	}
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：wzt2012 (赞：0)

### 题目大意

[原题！](https://www.luogu.com.cn/problem/CF1737A)

有 $n$ 个字母，把它们分成 $k$ 份，每份找出其中没有出现过的**最小字母**，然后组成一个长度为 $k$ 的字符串，求字典序最大的字符串。

---

### 解题思路

求字典序最大的字符串，就要让**没出现过的最小字母最大**。

我们可以对于每份字母：

从最小的字母 $s$ 往上遍历，每个字母只放一个。**这样就能使没出现过的那个字母最大**，所以我们统计每个字母的次数，每一份从 $s$ 开始逐个让字母数量 $\texttt{-1}$，输出第一个遇到的数量为 $\texttt{0}$ 的字母。


---

## 作者：yutong_Seafloor (赞：0)

# [题目在这里 · CF1737A Ela Sorting Books](https://www.luogu.com.cn/problem/CF1737A) 

### 题目简要：
现在有一个字符串（保证字符为 `a` 到 `y` 中的字符），我们要分成 $k$ 份，然后在每一份字符里加入一个不存在于这个字符串中且在字母表出现最早的一个字母形成一个新的字符，我们现在要组合出字典序最大的字符串。

------------
### 题意分析
题目看似很绕，实际上就是先统计字母出现的个数，我们需要字典序最大的字符串，所以每一组最好从 $a$ 开始且最好还是连续的字符串，这样我们就可以尽可能快得用完字符，接着是暴力枚举 $\lfloor n / k \rfloor$ 个字母，每次都要把遍历过的字母自减，代表这个字母已经被用了，直到找到第一个数量是 $0$ 的字母，然后输出即可。

当然还有最坏的情况：如果我们没有找到，直接输出 $k+1$ 个字母就好了。

------------
## 代码 
```cpp 
#include <bits/stdc++.h>
using namespace std;
int k,n,t,dp,f[30],i,j,l,yt; 
char zf;
int main()
{
	cin>>t;
	for(i=1;i<=t;i++)
	{
		cin>>n>>k;
		yt=n/k;
		memset(f,0,sizeof(f));
		for(j=1;j<=n;j++)
		{
			cin>>zf;
			f[zf-'a'+1]++;
		}
		for(j=1;j<=k;j++)
		{
			dp=1;
			for(l=1;l<=yt;l++)
			if(f[l]==0)
			{
				dp=0;
				cout<<(char)(l+'a'-1);
				break;
			}
			f[l]--;
			if(dp)
			cout<<(char)(yt+'a');
		}
		cout<<"\n";
	}
	return 0;
}
```
------------

---

## 作者：FSHYLHX (赞：0)

# 题目大意
给定一个只有小写字母的字符串，要求分为 $k$ 段，使每段第一个未出现的字母（以下叫做“代表字符”）构成的字符串字典序最大。
# 思路分析
首先，尽量保证每一段都是从 $a$ 开始的连续子串。如果没有 $a$，则该段的代表字符就为 $a$。

接下来，我们只需要用一个数组记录下每个字母出现的字数，然后遍历记录数组，每次都将遍历过的字母数量减一，找到第一个数量为零的字母输出，便是最优解。

如果找到了最后都没有找到合适的答案，就直接输出  $k + 1$ 个字母即可。
# 代码实现
```c
#include<bits/stdc++.h>
using namespace std;
int i,j,k,m,n,ans,sum,t; 
char a[205];
int f[35];
int main(){
	scanf("%d",&t);
	while(t--){
		memset(f, 0, sizeof(f));
		scanf("%d%d",&n,&k);
		for(int i=1; i<=n; i++){
			cin >> a[i];
			f[a[i]-'a'+1]++;
		}
		for(int i=1; i<=k; i++){
			int flag = 0;
			for(int j=1; j<=n/k; j++){
				if(f[j] == 0){
					flag = 1;
					cout << (char)(j+'a'-1);
					break;
				}
				f[j]--;
			}
			if(!flag) cout << (char)(n/k+'a');
		}
		printf("\n");
	}
	return 0;
}

```


---

## 作者：zzy0618 (赞：0)

### 题目大意

给定字符串 $s$ 将其重新排列后平分为 $k$ 段，使得每段中未出现的最小字母构成的序列的字典序最大。

### 大体思路

如果一段中字符不是连续的，那么怎么排列都没有意义，所以使用贪心思想，尽力使得每一段**从** ```a``` **开始**尽可能连续，且满足“**越靠前越连续**”。

因为可以随意组合，且字符只有 ```a``` 至 ```z```，所以可以用一个桶记录。每次遍历从字符 ```a``` 向上爬，中途不断将字符个数减少 $1$，如果遭到阻断，也就是没有这个字符时输出。如果到了顶端且中途的字母不缺，直接输出 $k+1$ 个字符即可。

### 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, k, len, i, j, x, N;
int mp[30];//桶 
string s;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);//读入加速 
	cin >> t;
	while (t--) {
		memset(mp, 0, sizeof(mp));//清空桶 
		cin >> n >> k >> s;
		len = s.size();
		N =n / k;//用 N 记录 n/k 较快 
		for (i = 0; i < len; i++)mp[s[i] - 'a' + 1]++;//记录 
		for (i = 1; i <= k; i++) {
			x = 1;
			for (j = 1; j <= N; j++) {//不断向上爬 
				if (mp[j] == 0) {//如果中途没有字符了 
					x = 0;
					putchar(j + 'a' - 1);
					break;
				}
				mp[j]--;
			}
			if (x)putchar(N + 'a');//输出 k+1 个字符 
		}
		putchar('\n');
	}
	return 0;
}
```



---

## 作者：Erotate (赞：0)

### Solution

这里需要字典序最大，那么每一组应该尽量满足从 `a` 开始的连续字符串。注意，一定要从 `a` 开始，不然连续没有任何意义。

那么做法就是：

1. 记录下每一个字母出现的次数。

2. 枚举每一组，看一下在当前这组第一个没出现的字母是哪个。在找到之后不能结束，因为必须选够 $\dfrac{n}{k}$ 个字母才能结束。所以应该记录下这个字母，等到选够了再输出。如果发现选即使够了字母也是连续的，那就输出第 $k+1$ 个字母。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
int t,n,k,sum[30];
char ch[N];
signed main(){
	scanf("%d",&t);
	while(t--){
		memset(sum,0,sizeof(sum));
		scanf("%d%d",&n,&k);
		scanf("%s",ch+1);
		int l=n/k;
		for(int i=1;i<=n;++i) sum[ch[i]-'a']++;//记录字母出现的次数
		for(int i=1;i<=k;++i){
			int cnt=0,flag=-1;
			for(int j=0;j<26;++j){
				if(sum[j]){
					sum[j]--;
					cnt++;
					if(cnt==l){//如果选够了都是连续的，就输出第 k+1 个字母
						if(flag==-1) printf("%c",j+1+'a');
						break;
					}
				}else{//记录第一个没有出现的字母
					if(flag==-1) flag=j;
					continue;
				}
			}
			if(flag!=-1) printf("%c",flag+'a');
		}
		puts("");
	}
	return 0;
}
```


---

