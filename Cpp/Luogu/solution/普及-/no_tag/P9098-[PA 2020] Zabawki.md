# [PA 2020] Zabawki

## 题目描述

**题目译自 [PA 2020](https://sio2.mimuw.edu.pl/c/pa-2020-1/dashboard/) Runda 2 [Zabawki](https://sio2.mimuw.edu.pl/c/pa-2020-1/zab/)**

你可能不知道，Bitie 和 Bytie 兄弟有相当令人印象深刻的玩具收藏品！他们每个人都拥有 $n$ 个玩具，每个玩具都是 $26$ 种类型中的一种。为方便起见，兄弟俩给每种类型的玩具都贴上了从 $\texttt a$ 到 $\texttt z$ 的英文字母标签。

在今天的游戏中，Bitie 拿出了他的玩具并按从左到右的顺序排列。因此，Bitie 可以用一个有 $n$ 个英文字母的序列来描述他的玩具的排列；这个序列的第 $i$ 个字符表示 Bitie 的序列中从左起的第 $i$ 个玩具。同时 Bytie 也拿出了他的玩具并按从左到右的顺序排列。现在 Bitie 想变得更像 Bytie——他想把自己的玩具按 Bytie 的玩具的顺序排列。

在游戏过程中，Bitie 可以通过翻转来改变他的玩具的顺序，一次翻转可以取奇数个连续的玩具并颠倒其顺序。因此，如果字符串 $\texttt{abcdea}$ 描述了 Bitie 的玩具顺序，那么在一次翻转中，Bitie 可以产生例如 $\texttt{adcbea}$（通过颠倒从第二个到第四个玩具的顺序）或 $\texttt{edcbaa}$（通过颠倒从第一个到第五个玩具的顺序）的序列。然而，他不能在一次翻转之后得到序列 $\texttt{bacdea}$。

Bitie 能够通过翻转得到和 Bytie 的玩具序列一样的序列吗？

## 说明/提示

#### 样例 1 解释

对于第一组样例，Bitie 可以通过三次翻转操作得到和 Bytie 一样的玩具序列。

![](https://cdn.luogu.com.cn/upload/image_hosting/vexaj3z8.png)

------------

#### 数据范围

**本题采用捆绑测试**

对于一些子任务，满足如果这组数据的答案是 `TAK`，那么 Bitie 最多只需进行一次交换就可以得到和 Bytie 一样的序列。

此外，大约一半的子任务满足 $n\le 2\times 10^3$。

对于 $100\%$ 的数据：

- 保证 $1\le n\le 3\times 10^5$。
- 保证字符串中只出现小写英文字母（$\texttt a$ 到 $\texttt z$）。

## 样例 #1

### 输入

```
7
abcdefg
edgbcfa```

### 输出

```
TAK```

## 样例 #2

### 输入

```
5
abcde
fghhh```

### 输出

```
NIE```

# 题解

## 作者：David_yang (赞：6)

[传送门](https://www.luogu.com.cn/problem/P9098)

第五篇题解，如有不妥请~~忽视~~指出。

## 题目大意：

给定两个字符串，求第一个字符串能否经过翻转得到第二个字符串（每次翻转的长度必须为奇数）。

## 算法：

字符串（其实算不上算法）。

## 解析：

首先拿到题，我觉得题目太长，懒得看。撇了一眼样例解释，原来是要通过翻转使两个字符串相同，可是我忽略了一个重要信息：**每次翻转的长度必须为奇数！！！**

于是，我天真地把代码交上去，还觉得这题太简单，难度介于澄和红之间。交上去一看，首先被 $246$ 个测试点所惊艳，然后一看，怎么会有 WA？而且对了那么多，只错了几个，由于捆绑测试，我获得了 $1000000000 \bmod 1000$ 分的好成绩。代码就不展示了……

我还没发现错误，只觉得某个地方没想到，加了点东西交上去绿的多了一点，但依然获得了 $1000000000 \bmod 1000$ 分的好成绩。改进后的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[30],b[30];
string s,t;
int main()
{
	scanf("%d",&n);
	cin>>s>>t;
	for(int i=0;i<n;i++)
	{
		a[s[i]-'a']++;        		//我发现我忘记计算里面的个数，个数一样才能TAK。为什么把错误代码摆出来，是因为这一段加上奇偶判断就是AC代码中的最重要部分。
	}
	for(int i=0;i<n;i++)
	{
		b[t[i]-'a']++;
	}
	for(int i=0;i<=26;i++)
	{
		if(a[i]!=b[i])
		{
			printf("NIE");
			return 0;
		}
	}
	for(int i=0;i<n;i++)
	{
		if(t.find(s[i])==string::npos)
		{
			printf("NIE");
			return 0;
		}
	}
	printf("TAK");
	return 0;
}
```

我只好仔细读题，才注意到那一个很重要的点。每次只能翻转奇数个，所以**翻转前后每字母所在位的奇偶性是一样的**。

这次对的多了点，还拿了个 $10$ 分。

我实在没办法了，去看了一下仅有的一篇题解（感谢 heaksicn 让我突然明白过来）。当看到“只要要求每个字母在相同奇偶的位置上的数量相同即可”时我恍然大悟：哪还用去看有没有重复，直接算出各个字母在奇数位上的有多少个，比较一下，偶数位上有多少个，再比较一下，只要都相等就行了。

明白了这个，这道题基本上就可以说已经 AC 了。

## AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,tt;
string s,t;
struct d
{
	int ji,ou;
}a[30],b[30];
int main()
{
	scanf("%d",&n);
	cin>>s>>t;
	for(int i=0;i<n;i++)
	{
		if(i&1)
		{
			a[s[i]-'a'].ji++;
			b[t[i]-'a'].ji++;						//在奇数位上的字母有多少。
		}
		else
		{
			a[s[i]-'a'].ou++;
			b[t[i]-'a'].ou++;						//在偶数位上的有多少。
		}											//如我前面所说，只要加上判断奇偶，就是代码中最重要的部分。
	}
	for(int i=0;i<=26;i++)
	{
		if(a[i].ji!=b[i].ji || a[i].ou!=b[i].ou)	//比较，只要相等即可。
		{
			printf("NIE");
			return 0;
		}
	}
	printf("TAK");
	return 0;
}
```

$246$ 个测试点，绿起来挺好看的。

最后，浏览过看过也要赞过！

---

## 作者：lzbzl (赞：4)

## P9098 题解
### 题目大意
给出两个字符串，若一个字符串能经过若干次反转变成另一个字符串输出 `TAK`，否则输出 `TIE`。

### 思路
题目允许我们可以进行以下一个操作：

- 选取一段区间 $i∼i+a−1$（$a$ 为奇数）并将它们反转。

举个栗子，反转字符串 `abcd` 四位后变成 `dcba`。

不难发现，每一次反转时处在位置 $j$ 的字符都会到 $2×i+k−1−j$ 的位置去，那么就应该讨论一下奇偶性。我们发现，无论怎么反转，$2×i+k−1$ 的奇偶性总是不变，所以反转过后也不变，那么只要比较同个字母在奇和偶两个位置的数量就行了。

代码双手奉上。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string a,b;
int vis[27][2],siv[27][2];//运用桶排，方便又快！
int main()
{
    cin>>n>>a>>b;
	for(int i=0;i<n;i++)
	{
		vis[a[i]-'a'][i%2]++;
		siv[b[i]-'a'][i%2]++;
     //这两行都在讨论同一个字母所在位置的奇偶性。
	}
	for(int i=0;i<=25;i++)
	{
		if(vis[i][0]!=siv[i][0] || vis[i][1]!=siv[i][1])//判断两种位置的字母数量是否相等。
		{
			cout<<"NIE";
			return 0;//不相等就可以直接退出了。
		}
	}
	cout<<"TAK";
    return 0;//QWQ
}
```
感谢管理员审核。

---

## 作者：封禁用户 (赞：2)

# 题意
从前有两个字符串，他们由小写字母组成。现在我们可以对第一个字符串做若干次操作，最后使两个字符串相等。如果可行输出 ``TAK``，不行输出 ``NIE``。

对于每一次操作：
- 我们选取一个区间 $i \sim i+k-1$，满足 $k$ 为奇数。
- 将这个区间内的数前后翻转。

举例：
字符串 ``abcdefg``，翻转 $1 \sim 5$ 的区间，即变成 ``edcbafg``。

![](https://cdn.luogu.com.cn/upload/image_hosting/hnc0f9x9.png)

# 思路
我们思考每一次操作：

对于一次翻转区间 $i \sim i+k-1$ 的操作，

对于在 $x$ 位置上的字符，（$i \le x \le i+k-1$），会被交换至 
$$2 \times i+k-1-x$$
的位置。

讨论奇偶性，$i \times 2$ 为偶数，$k$ 为奇数，偶加奇减奇等于偶，所以奇偶性不变。

那对于一个字符串，我们拿两个桶，记录分别在奇数下标的位置的某个字母和偶数下标的某个字母的数量，比较两个字符串的某个字母奇或偶的数量是否相同即可。
## AC code
```cpp
#include<bits/stdc++.h>
#define f(i,j,n) for(int i=j;i<=n;i++)
#define int long long 
using namespace std;
int n;
string a,b;
int a1[130][3];
int b1[130][3];
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n>>a>>b;
	for(int i=0;i<a.size();i++){
		a1[a[i]][i&1]++;
	}
	for(int i=0;i<b.size();i++){
		b1[b[i]][i&1]++;
	}
	for(int i='a';i<='z';i++){
//			cout<<aa[i]<<" "<<bb[i]<<endl; 
		if((a1[i][1]!=b1[i][1])||(a1[i][0]!=b1[i][0])){
			cout<<"NIE";
			return 0;
		}
	}
	cout<<"TAK";
	return 0;
}
```

---

## 作者：heaksicn (赞：2)

## 1 description

有两个长度都为 $n$，由小写字母构成的序列 $s$ 和 $t$。

对于 $s$ 可以进行若干次操作，每次操作可以选择其中一个长度为奇数的字段进行翻转。

问能不能对 $s$ 进行若干次操作是的 $s$ 与 $t$ 相同。

## 2 solution

注意到题目说的翻转要求**翻转字段的长度为奇数**，很显然可以发现，在子段中的每个字母在翻转前后位置的奇偶性不变。

那么只要要求每个字母在相同奇偶的位置上的数量相同即可。

时间复杂度 $O(n)$。

## 3 code

```
//Man always remember love because of romance only!
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
char s[300001],t[300001];
int a[26][2][2];
signed main(){
	int n=read();
	cin>>s+1>>t+1;
	for(int i=1;i<=n;i++){
		a[s[i]-'a'][i%2][0]++;
		a[t[i]-'a'][i%2][1]++;
	}
	bool flag=1;
	for(int i=0;i<26;i++){
		if(a[i][0][0]!=a[i][0][1]||a[i][1][0]!=a[i][1][1]){
			flag=0;
			break;
		}
	}
	puts(flag?"TAK":"NIE");
	return 0;
}
```


---

## 作者：T_TLucas_Yin (赞：1)

这道题第一眼看起来感觉很难做，操作似乎没有规律。

但注意到题目说每次翻转一定要选择**奇数**长度的区间。反转奇数长度的区间，则一定是将这个区间两侧的元素**以区间中间的元素为中心**反转。设中间的元素位置为 $k$，则要反转的区间内第 $k+i$ 个元素会移动至第 $k-i$ 个位置，相当于位置 $-2k$，因此反转后元素位置的奇偶不变。

也就是说，一个在奇数位置上的元素不能到偶数位置上，偶数位置上的元素不能到奇数位置上。而一个元素一定可以换到所有与其同奇偶的位置上，最简单的方法就是每次移动 $-2$ 或 $+2$。

这样问题就很好解决了。我们先统计出两个字符串内每种字符在奇数和偶数位置上分别出现的次数，然后依次进行比较。如果某种字符在两个字符串内奇偶位置上出现的次数不一致，则该字符无法通过反转完全对应，此时输出 `NIE`。否则输出 `TAK` 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s1,s2;
int n,a[105][2],b[105][2];
int main(){
    cin>>n>>s1>>s2;
    for(int i=0;i<n;i++) a[s1[i]-'a'][i%2]++;
    for(int i=0;i<n;i++) b[s2[i]-'a'][i%2]++;
    for(int i=0;i<26;i++){
        if(a[i][0]!=b[i][0]||a[i][1]!=b[i][1]){
            cout<<"NIE";
            return 0;
        }
    }
    cout<<"TAK";
    return 0;
}
```

---

## 作者：ss520 (赞：0)

## 题目分析
假设第 $n$ 个数在一次操作中被翻转。
| 是否翻转 | $n$ 为奇数时 | $n$ 为偶数时 |
| :----------: | :----------: | :----------: |
| 未翻转 | $n$ 为奇数 | $n$ 为偶数 |
| 已翻转 | $n$ 为奇数 | $n$ 为偶数 |

综上，翻转不会改变 $n$ 的奇偶性。
## 解题思路
因为翻转不会改变奇偶性，所以只需判断两个序列奇数位和偶数位是否完全相同。
## 解题代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
bool check(string g,string v){//check函数判断奇位偶位的玩具是否完全相同
	int s1[150000][1],s2[150000][1];
	for(int i=0;i<g.size();i++){
		s1[g[i]-'a'][i%2]++;
	}
	for(int i=0;i<v.size();i++){
		s2[v[i]-'a'][i%2]++;
	}
	for(int i=0;i<26;i++){
		if(s1[i][0]!=s2[i][0] || s1[i][1]!=s2[i][1]) return 0;
	}return 1;
}
int main(){
	int n;cin>>n;
	getline(cin,a);//读取空行
	getline(cin,a);
	getline(cin,b);
	if(check(a,b)==0){
		cout<<"NIE";
		return 0;
	}else{
		cout<<"TAK";
		return 0;//结束
	}
}
```

---

## 作者：ttq012 (赞：0)

考虑根据奇偶性来分析。容易发现只能在奇数位之间、偶数位之间互相交换字符，但是这些位之间是可以任意交换字符的。

所以把每一个字符串奇数位、偶数位的字符全部存储下来，判断是否可以做到一样即可。

时间复杂度为 $O(n)$。

```cpp
void $() {
    int n;
    string a, b;
    cin >> n >> a >> b;
    vector<char> v1, v2, v3, v4;
    F(i, 0, n - 1) {
        if (i & 1) {
            v2.pb(a[i]), v4.pb(b[i]);
        } else {
            v1.pb(a[i]), v3.pb(b[i]);
        }
    }
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    sort(v3.begin(), v3.end());
    sort(v4.begin(), v4.end());
    if (v1 == v3 && v2 == v4) {
        cout << "TAK\n";
    } else {
        cout << "NIE\n";
    }
}

signed main() { $(); } 
```

---

## 作者：zhengpie (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9098)

### 1.思路

注意到题目说“一次翻转可以取**奇数**个连续的玩具”，于是考虑区间 $[i,i + len - 1]$，其中 $len$ 是一个奇数。

那么对于 $k \in [i,i + len - 1]$，有 $k$ 变换后的位置是 $2i + len - k - 1$。因为 $2i$ 肯定是偶数，又 $len$ 是一个奇数，所以 $len - 1$ 是偶数，因此，$2i + len - 1$ 是偶数。

偶数减一个数，得到的数的奇偶性不变。于是，交换前后的下标的奇偶性不变。

因此，分别记录字符串的下标的奇偶性即可。

### 2.代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int d1[26][2],d2[26][2],n;//桶的第二维记录奇偶性
string a,b;
signed main() 
{
	ios::sync_with_stdio(0);
  	cin>>n>>a>>b;
	for(int i = 0;i < a.size();i++) 
	{
		d1[a[i] - 97][i % 2]++;
		d2[b[i] - 97][i % 2]++;
	}
	for(int i = 0;i < 26;i++)
		if(d1[i][1] != d2[i][1] || d1[i][0] != d2[i][0]) //如果哪个字母的下标的奇偶性的数量下标的奇偶性不相等就无法变相同
		{
			cout<<"NIE";//如果有哪个字母的下标的奇偶性的数量不同就直接结束程序
			return 0;
		}
	cout<<"TAK";//否则不存在哪个字母的下标的奇偶性的数量，那么肯定可以变换成相同的序列
	return 0;
}

```

---

## 作者：lyh4 (赞：0)

# 题解：P9098 [PA2020] Zabawki

### [题目传送门](https://www.luogu.com.cn/problem/P9098)

### 思路：
调换 $i \sim i + j - 1$，则在原字符串中位置为 $k$ 的字符会到 $i + j - 1 - (k - i)$，即 $2 \times i + j - k - 1$。$2 \times i$ 为偶数，$j$ 为奇数，则 $2 \times i + j - k - 1$ 的奇偶性同 $2 \times r - k$，则 $2 \times k$ 同于 $2 \times r$。则在原字符串中位置为 $k$ 的字符转换后回到奇偶性同 $k$ 的位置。由此，可比较奇数下标与偶数下标的字符是否相同即可。

### 上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

string a,b;
int n,word1[30][5],word2[30][5];
int main()
{
    cin >>n;
    cin >>a>>b;
    for(int i = 0; i < n; i++)
    {
        word1[a[i]-'a'][i%2]++;
        word2[b[i]-'a'][i%2]++;
    }
    for (int i = 0; i < 26; i++) {
		if ((word1[i][1] != word2[i][1]) || (word1[i][0] != word2[i][0]))
        {
			cout << "NIE";
			return 0;
		}
	}
	cout << "TAK";
}
```

---

## 作者：Seqfrel (赞：0)

# P9098 [PA2020] Zabawki 题解

## 题目大意

给定两个长度相等的字符串，每次变换可以将一个长度为奇数的子串翻转，求第二个字符串是否可以变换为第一个字符串。

## 解题思路

![](https://cdn.luogu.com.cn/upload/image_hosting/eep8wvss.png)

通过这张图不难发现，红色线所连接的翻转前后的对应数字的位置编号同为奇数，蓝色线所连接的翻转前后的对应数字的位置编号同为偶数。

换句话说，一个字符在翻转前后其位置的奇偶性不变。

不过我们还可以用奇偶性分析推导一下。设字符串长度为 $n$，一个字符的起始位置为 $i$，那么这个字符在变换结束后的位置即为 $n-i+1$。因为 $n$ 为奇数，所以当 $i$ 为奇数时，$n-i$ 为偶数，$n-i+1$ 即为奇数；当 $i$ 为偶数时，$n-i$ 为奇数，$n-i+1$ 即为偶数。

有了这个结论，代码就很好写了。分别记录两个字符串中每个字符在奇数位置的出现次数和在偶数位置的出现次数，如果两个字符串中对应字符所出现的次数全部相等，那么就一定可以通过变换互相转化。

记录每个元素的出现次数需要用到桶数组，因为玩具只有 $26$ 种，所以桶数组大小开到 $26$ 即可。

## 代码实现

```cpp
#include<iostream>
#include<string>
using namespace std;
int n,t1[30],t2[30],t3[30],t4[30];//四个桶数组分别记录两个字符串中奇数位和偶数位 
bool flag;//标记变量记录是否完全相等 
string a,b;
int main(){
	cin>>n;
	cin>>a>>b;
	for(int i=0;i<n;i++){
		if(i%2==0){//奇数位置 
			t1[a[i]-'a']++;t3[b[i]-'a']++;
		}else{//偶数位置 
			t2[a[i]-'a']++;t4[b[i]-'a']++;
		}
	}
	flag=1;
	for(int i=0;i<26;i++){
		if(t1[i]!=t3[i]||t2[i]!=t4[i]){
			flag=0;break;//如果不等于就可以直接跳出 
		} 
	}
	if(flag) cout<<"TAK";
	else cout<<"NIE";
	return 0;
} 
```

---

## 作者：danb123 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9098)

首先要分析一下题目，明白这道题的主要解决的问题是什么。

给定两个字符串，通过操作判断这两个字符串是否能变成一样的序列。

而关键点在于它只能把**连续的奇数个位翻转**，所以它翻转过后，每一位的位置奇偶性不变，所以奇数位的字符可以移动到任意奇数位上，偶数位的字符可以移动到任意偶数位上。

### 所以只要奇数位和偶数位上的字符数量相同，无论多少次操作，总能变成一样的字符。

通过以上分析，我们已经总结出了要完成的两个判断条件：

1. 两个字符串的字符数量是否一致。

1. 两个字符串的奇数位与偶数位上的字符数量是否一致。

```cpp
#include<bits/stdc++.h>
using namespace std;
int len,a[26],b[26];
char n[1000001],m[1000001];
int main() {
	cin>>len>>n>>m;
	for(int i=0; i<len; i++) 
		a[n[i]-'a']++,b[m[i]-'a']++;
	for(int i=0; i<26; i++) {
		if(a[i]!=b[i]) {
			cout<<"NIE";
			return 0;
		}
	}
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	for(int i=0; i<len; i+=2)a[n[i]-'a']++,b[m[i]-'a']++;
	for(int i=0; i<26; i++) {
		if(a[i]!=b[i]) {
			cout<<"NIE";
			return 0;
		}
	}
	cout<<"TAK";
	return 0;
}
```
审核员辛苦了！

---

## 作者：ymyctsz (赞：0)

[题目](https://www.luogu.com.cn/problem/P9098)

模拟题。

## 概要题意：

将两字符串取其一，并可以无数次取长度为奇数（这个很重要）的子串颠倒其顺序，看其能否经过若干次操作与另一个字符串相同。

#### 举例是最好的试金石

![screenshot-1709866622219.png](https://s2.loli.net/2024/03/08/EqYzZxlU73Sg1jN.png)

样例。

但在做题时我会想到 [NOIP2023 词典 ](https://www.luogu.com.cn/problem/P9868) 这题：样例解释与正解无关，因为可以无数次交换，那么只要比较字符串中的字母个数就行了。

本题异曲同工之妙（废话结束）。

## Idea

### Part1

因为只能取长度为奇数的子串进行颠倒其顺序，由此发现位于奇数位置颠倒后仍然在奇数位置，偶数位置颠倒后仍然在偶数位置（结合 Part2）。

### Part2

再试着手玩些例子：

发现当取 3 长度时，这样就实现头尾位置互换（b 与 e）。

![screenshot-1709866544579.png](https://s2.loli.net/2024/03/08/F9SrH8WEYgkOhZx.png)

发现当取 5 长度时，（b 与 e）（a 与 f）发生了互换，为了不打乱序列，因此可以进行上面取 3 长度的操作，这样就实现（a 与 f）互换。

![screenshot-1709866383354.png](https://s2.loli.net/2024/03/08/kRcBSJOtp97TnxV.png)

若要实现更长距离的交换，只要同上思想即可。

### Part3

结合 Part1 和 Part2 ：只要两个字符串的每种出现的字母的个数、字母位置的奇数个数和偶数个数相同就可以使一字符串经过若干次颠倒操作后与另一个字符串相同。

下面用样例理解一下：

![screenshot-1709891256864.png](https://s2.loli.net/2024/03/08/QbA9G2gEWvktcdN.png)

![screenshot-1709891280506.png](https://s2.loli.net/2024/03/08/I7CL3rw9zUgisan.png)

### Code
```
#include<bits/stdc++.h>
#define intt register int
using namespace std;
string s1,s2;
int n,l1,l2,t;
struct t1{int x,y;}f1[26];
struct t2{int x,y;}f2[26];
int main()
{
	cin>>n>>s1>>s2;
	l1=s1.size();l2=s2.size();
	for(intt i=0;i<l1;i++)
	  if(i%2) f1[s1[i]-'a'].x++;
	  else    f1[s1[i]-'a'].y++;
	for(intt i=0;i<l2;i++)
	  if(i%2) f2[s2[i]-'a'].x++;
	  else    f2[s2[i]-'a'].y++;
	for(intt i=0;i<26;i++) 
	  if(f1[i].x!=f2[i].x||f1[i].y!=f2[i].y) t=1;//可以少判断一个每种出现的字母的个数。
	if(t)cout<<"NIE";
	else cout<<"TAK";
	return 0;
}
```

完结。

---

