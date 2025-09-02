# Update Queries

## 题目描述

Let's consider the following simple problem. You are given a string $ s $ of length $ n $ , consisting of lowercase Latin letters, as well as an array of indices $ ind $ of length $ m $ ( $ 1 \leq ind_i \leq n $ ) and a string $ c $ of length $ m $ , consisting of lowercase Latin letters. Then, in order, you perform the update operations, namely, during the $ i $ -th operation, you set $ s_{ind_i} = c_i $ . Note that you perform all $ m $ operations from the first to the last.

Of course, if you change the order of indices in the array $ ind $ and/or the order of letters in the string $ c $ , you can get different results. Find the lexicographically smallest string $ s $ that can be obtained after $ m $ update operations, if you can rearrange the indices in the array $ ind $ and the letters in the string $ c $ as you like.

A string $ a $ is lexicographically less than a string $ b $ if and only if one of the following conditions is met:

- $ a $ is a prefix of $ b $ , but $ a \neq b $ ;
- in the first position where $ a $ and $ b $ differ, the symbol in string $ a $ is earlier in the alphabet than the corresponding symbol in string $ b $ .

## 说明/提示

In the first set of input data, you can leave the array $ ind $ and the string $ c $ unchanged and simply perform all operations in that order.

In the second set of input data, you can set the array $ ind = [1, 1, 4, 2] $ and $ c = $ "zczw". Then the string $ s $ will change as follows: $ meow \rightarrow zeow \rightarrow ceow \rightarrow ceoz \rightarrow cwoz $ .

In the third set of input data, you can leave the array $ ind $ unchanged and set $ c =  $ "admn". Then the string $ s $ will change as follows: $ abacaba \rightarrow abacaba \rightarrow abdcaba \rightarrow abdcmba \rightarrow abdcmbn $ .

## 样例 #1

### 输入

```
4
1 2
a
1 1
cb
4 4
meow
1 2 1 4
zcwz
7 4
abacaba
1 3 5 7
damn
7 10
traktor
7 6 5 4 3 2 1 6 4 2
codeforces```

### 输出

```
b
cwoz
abdcmbn
ccdeefo```

# 题解

## 作者：zhouchuer (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1986D)
### 题意
题目告诉我们要输入长度为 $n$ 的字符串 $s$ 和长度为 $m$ 的数组 $ind$ 和字符串 $c$，你可以将 $ind$ 和 $c$ 打乱顺序，让你用 $c_i$ 替换 $s_{ind_i}$，让你求最小的字典序。 

### 思路
明显的贪心，只要先将 $ind$ 和 $c$ 分别按整数大小和字典序大小排序，再将 $ind$ 数组中重复出现的元素去重，最后将数组 $ind$ 遍历一遍，挑选对应的 $c_i$，然后令 $s_{ind_i} \gets c_i$ 就可以了。

### 代码
```c
#include<bits/stdc++.h>
using namespace std;

int t,n,m,ind[100005],cnt;
char c[100005];
string s;
int main(){
	cin>>t;
  	while(t--){
		cin>>n>>m;
    	cin>>s;
    	for(int i=1;i<=m;i++){
      		cin>>ind[i];
    	}
		for(int i=1;i<=m;i++){
          	cin>>c[i];
        }
		sort(ind+1,ind+m+1);
      	sort(c+1,c+m+1);
		cnt=0;
		for(int i=1;i<=m;i++){
			if(ind[i]!=ind[i-1]){
				s[ind[i]-1]=c[++cnt];
			}
		}
		cout<<s<<endl;
  	}
	return 0;
}
```

---

## 作者：Pink_Cut_Tree (赞：1)

# CF1986C Update Queries 题解

### 说明

数据如何输入翻译里给的不清楚，应该是：

每组数据中：

第一行两个正整数 $n,m$。

第二行一个字符串 $s$，长度为 $n$。

第三行 $m$ 个正整数 $ind_i$。

第四行一个字符串 $c$，长度为 $m$。

### 解析

贪心。

显然，我们要将尽可能小的字母放在前面，考虑把 $ind$ 数组和 $c$ 数组排序，并将 $ind$ 数组**去重**，最后将 $ind$ 数组扫一遍，直接替换即可。注意对 $ind$ 数组判重。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m;
char ch[N];
int ind[N];
string s;
int T;
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>n>>m;
		cin>>s;
		for(int i=1;i<=m;i++){
			cin>>ind[i];
		}
		for(int i=1;i<=m;i++){
			cin>>ch[i];
		}
		sort(ch+1,ch+m+1);
		sort(ind+1,ind+m+1);
		int cnt=0;
		for(int i=1;i<=m;i++){
			if(ind[i]!=ind[i-1]){
				s[ind[i]-1]=ch[++cnt];
			}
		}
		cout<<s<<"\n";
	}
return 0;
}
```

---

## 作者：e_mei_mountain_704 (赞：1)

[题目传送器](https://www.luogu.com.cn/problem/CF1986C)

### 思路

这道题是贪心算法。

要让你求最小的字典序，就要将 $c$ 中最小的字母换到 $s$ 尽可能前的位置。所以我们只需要将 $ind$ 和 $c$ 从小到大排序。用小的对应 $s$ 前面的。

### 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N=1e5+20;
char s[N];
int ind[N];
char c[N];

int main ()
{
	int t;
	cin>>t;
	while (t--)
	{
		int n,m;
		cin>>n>>m;
		for(int i=1; i<=n; i++)
			cin>>s[i];
		for(int i=1; i<=m; i++)
			cin>>ind[i];
		for(int i=1; i<=m; i++)
			cin>>c[i];
		sort(ind+1,ind+1+m);
		sort(c+1,c+1+m);
		for(int i=1,j=1; i<=m; i++)
		{
			if(ind[i]==ind[i-1]) continue;
			s[ind[i]]=c[j];
			j++;
		}
		for(int i=1; i<=n; i++)
			cout<<s[i];
		cout<<endl;
	}
    return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/164093180)

---

## 作者：CaiZi (赞：1)

## Update Queries 题解
**[题目链接](https://www.luogu.com.cn/problem/CF1986C)**
### 题目分析
简要题意：给定数组 $ind$ 和字符串 $c$，可以随意调换里面的元素，最后让 $s_{{ind}_i}=c_i$，求字典序最小的 $s$。

由于我们要让字典序最小，自然应该让 $s$ 前面的字符尽量小，于是我们把数组 $ind$ 和字符串 $c$ 排序。然而这样还不够，因为 $ind$ 中的元素是有重复的，如果遇到重复元素，我们只能计算一次，多余的相同元素无需考虑（你可以认为这些元素安排到了 $c$ 的末尾）。
### 代码展示
代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m,p,ind[200001];
string s,c;
signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cin>>t;
	while(t--){
		p=0;
		cin>>n>>m>>s;
		for(int i=1;i<=m;i++){
			cin>>ind[i];
		}
		cin>>c;
		sort(ind+1,ind+m+1);
		sort(c.begin(),c.end());
		for(int i=1;i<=m;i++){
			if(ind[i]!=ind[i-1]){
				s[ind[i]-1]=c[p];
				p++;
			}
		}
		cout<<s<<'\n';
	}
	return 0;
}
```
**[提交记录](https://www.luogu.com.cn/record/163714892)**

---

## 作者：2huk (赞：1)

> - 给定长度为 $n$ 的字符串 $s$ 和长度为 $m$ 的数组 $ind_i$ 和一个长度为 $m$ 的字符串 $c$。你可以将 $ind$ 和 $c$ 打乱顺序，然后依次按照 $i = (1, 2, \dots, m)$ 执行 $s_{ind_{i}} \gets c_i$。求最后得到的字典序小的 $s$。
> - $n, m \le 10^5$。

显然贪心。发现 $ind$ 中值 $i$ 的出现次数是不重要的，我们只需要关注这个值是否出现。若 $i$ 没出现那么一定仍保持 $s_i$ 不变，否则一定是将 $c$ 排序后，按 $i, j$ 递增的顺序执行 $s_i \gets c_j$。

```cpp
void solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++ i ) cin >> a[i];
	
	set<int> S;
	for (int i = 1; i <= m; ++ i ) {
		cin >> b[i];
		S.insert(b[i]);
	}
	
	for (int i = 1; i <= m; ++ i ) cin >> c[i];
	
	sort(c + 1, c + m + 1);
	
	int idx = 0;
	for (int t : S) {
		++ idx;
		a[t] = c[idx];
	}
	
	for (int i = 1; i <= n; ++ i ) cout << a[i];
	cout << '\n';
}
```

---

## 作者：ThisIsLu (赞：1)

简单贪心，先将 $c$ 数组排序。

对于第 $i$ 个位置，考虑有多少个 $ind_j=i$ 将 $j$ 最大的取最小，其它取最大即可。

所以维护一个左端点 $l$，遇到存在 $ind_j=i$ 的位置 $i$ 就把 $l$ 加 $1$ 并赋值 $c_l$。 

具体判断存不存在用桶就行了。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5;
int a[N+5];
int n,m;
char s[N+5],c[N+5];
bool mp[N+5];
void solve(){
    cin>>n>>m>>(s+1);
    for(int i=1;i<=n;i++) mp[i]=0;
    for(int i=1;i<=m;i++){
        int indi;
        cin>>indi;
        mp[indi]=true;
    }
    cin>>(c+1);
    sort(c+1,c+m+1);
    int l=1;
    for(int i=1;i<=n;i++){
        if(mp[i]){
            s[i]=c[l++];
        }
        putchar(s[i]);
    }
    putchar('\n');
}
signed main()
{
    int t;
    cin>>t;
    while(t--) solve();
    return 0;
}
```

---

## 作者：_Tatsu_ (赞：0)

#### [LINK](https://www.luogu.com.cn/problem/CF1986C)
## 题意 & 思路
先按题目输入，然后在第 $i$ 次操作时，将 $s_{ind_i}$
替换为 $c_i$ ，以使操作后的 $s$ 字符串字典序最小。

这题就是贪心，将 $ind$ 数组和 $c$ 字符串从小到大排序，即可让字典序最小。因为 $ind$ 数组的靠前项已经够小了，此时 $c_i$ 的值也较小。

但这样就能 AC 了吗？很显然不是。

当 $ind$ 数组有值相等的情况，$c_i$ 
会重复覆盖在同一位上，导致字典序偏大。
所以我们写一个去重就可以解决了。
其他不再赘述，详见代码。

## AC Code
```cpp
#include <bits/stdc++.h>
#define int long long
#define fro for
using namespace std;
int ind[100001];
signed main()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	int t;
	cin>>t;
	while (t--)
	{
		int n,m;
		char s[100001],c[100001];
		//输入
		sort(c+1,c+1+m);
		sort(ind+1,ind+m+1);
    	fro (int i=1,j=1;i<=m;i++)
      	{
      		if (ind[i]==ind[i-1])//如果重复，就跳过
      		continue;
      		s[ind[i]]=c[j++];
//ind[i]若不重复，则赋值。因为跳过了一些，导致c无法对应，所以用j来存c的下标。
     	fro (int i=1;i<1=n;i++)
		cout<<s[i];
		cout<<endl;
	}
	return 0;
}
```

最后感谢审核大大与大家的耐心阅读，谢谢！

---

## 作者：__galaxy_1202__ (赞：0)

**很显而易见的贪心题~~**
## 解题思路：
我们可以**将串 $c$ 与 $ind$ 数组进行从小到大的排序**（字符串会按照字典序）。这样一来字典序越靠前的字符就会尽可能的与 $ind$ 数组贴合，使其在 $s$ 串靠前的位置。  
**但是**，**$ind$ 数组必须去重**，因为**如果不去重，后面的字符就会覆盖前面的字符，前功尽弃！！！**
## CODE:
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, m, ind[100001];
string s, c;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t--)
	{
		cin >> n >> m >> s;
		for (int i = 1; i <= m; i++)
			cin >> ind[i];
		cin >> c;
		sort(ind + 1, ind + m + 1);
		sort(c.begin(), c.end());
		int cur = unique(ind + 1, ind + m + 1) - (ind + 1);
		for (int i = 1; i <= cur; i++)
			s[ind[i] - 1] = c[i - 1];
		cout << s << '\n';
	}
	return 0;
}
```

---

## 作者：gaomingyang101011 (赞：0)

# CF1986C Update Queries 题解

## 思路

首先，我们知道这是一个很简单的贪心题，我们要求的是一个字符串经过多次操作之后的使它的字典序最小。

因为题目说可以任意安排 $ind$ 数组和字符串 $c$ 的顺序，所以我们先将 $ind$ 数组和字符串 $c$ 进行排序，因为要让字典序最小所以我们要将越小的字母越往前放，但一个位置可能会被更新多次，所以我们要将 $ind$ 数组去重。

下面是代码，有不懂的可以根据代码来理解，还是比较简单的。

## 代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N=2*1e5+1;
int t;
int n,m;
char s[N];
int ind[N];
char c[N];
// 变量名称都与题目中含义相同 
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		cin>>s+1;
		for(int i=1;i<=m;i++) cin>>ind[i];
		cin>>c+1;
		//为了后面操作更加简单，输入从一开始 
		sort(ind+1,ind+1+m);
		sort(c+1,c+1+m);
		// 先将ind数组和字符串c进行排序 
		int sc=0;
		for(int i=1;i<=m;i++){
			if(ind[i]!=ind[i-1]){
				s[ind[i]]=c[++sc];
			}// 去重 
		}// 从左到右依次更新 
		cout<<s+1<<endl;
		// 输入是从一开始的，输出也要从一开始 
	}
}
```

---

## 作者：GeXiaoWei (赞：0)

# CF1986C Update Queries
## 解析
本题是一道基本贪心，想要让答案小，就要让变换后的字符串尽可能小。因为是最小字典序，所以要让答案靠前的字符都小一点。变成的字符从第二个字符串选，就只需要对修改操作与第二个字符串从小到大排序即可，注意去重。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,a[200005],b;
char s[200005],d[200005];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%s",&n,&m,s+1);b=0;
		for(int i=1;i<=m;i++) scanf("%d",&a[i]);
		scanf("%s",d+1);
		sort(d+1,d+m+1);sort(a+1,a+m+1);
		for(int i=1;i<=m;i++) if(a[i]!=a[i-1]) s[a[i]]=d[++b];
		printf("%s\n",s+1);
	}
	return 0;
} 
```

---

## 作者：HsNu1ly7_ (赞：0)

## 思路

需要字典序越小，前面的字母的大小很关键，一个明显的贪心策略就是，将数组 $ind$ 和字符串 $c$ 升序排序，再根据题意模拟即可。

**注意：**$ind$ 数组需要去重。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
void solve (){
	int n , m ;
	int ind[200010] = {} ;
	string s , c ;
  
	cin >> n >> m ;
	cin >> s ;
	for ( int i = 1 ; i <= m ; i++ ) cin >> ind[i] ;
	cin >> c ;

	sort ( ind + 1 , ind + 1 +  m ) ;

	sort ( c.begin() , c.end() ) ;
  
	int temp = 0 ;
	for ( int i = 1 ; i <= m ;  i++ ){
		if ( ind[i] != ind[i - 1] || i == 1 ){
			s[ind[i] - 1]  = c[temp++] ;
		}
	}

	cout << s << '\n' ;

	return ;
}
signed main (){
	ios::sync_with_stdio(0) ;
	cin.tie(0) ;
	cout.tie(0) ;
	int _ ;
	cin >> _ ;
	while ( _-- ){
		solve () ;
	}
	return 0 ;
}
```

---

## 作者：xcms (赞：0)

为了让字典序最小，必须把 $c$ 字符串排序，然后按照题意模拟即可。需要注意的是，$ind_i$ 与 $ind_{i+1}$ 可能会相同，如果相同就会影响最后的字符串 $s$。所以，我们需要进行一步去重的操作。

这里不放完整代码。
```cpp
sort(ind+1,ind+1+m);
sort(c.begin(),c.end());
m=unique(ind+1,ind+1+m)-(ind+1);//去重函数，在用的时候确保数组已经排序
for(int i=1;i<=m;i++)s[ind[i]-1]=c[i-1];//注意字符串的下标是从0开始
```

---

## 作者：qfy123 (赞：0)

# CF1986C
[传送门](https://www.luogu.com.cn/problem/CF1986C)
## 思路
简单贪心。

考虑到要使字符串 $s$ 字典序最小，那么就要让越靠前的字符尽量小。于是我们可以将 $ind$ 和 $c$ 升序排列。进行排序之后，考虑到 $ind$ 数组内会有连续的重复元素，而按照操作顺序，对于重复元素而言，后面的操作会顶替前面的操作，因此我们将最优操作安排到一段元素的最后面执行即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int T,n,m,ind[N];
char c[N],s[N];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		scanf("%s",s+1);
		for(int i=1;i<=m;i++) scanf("%d",ind+i);
		scanf("%s",c+1);
		sort(ind+1,ind+m+1);
		sort(c+1,c+m+1);
		int p = 0;
		for(int i=1;i<=m;i++) if(ind[i]!=ind[i-1]) s[ind[i]] = c[++p];//每次遇到不同的ind，直接进行最优操作，显然等价于将最优操作安排到一段重复元素的最后执行。
		for(int i=1;i<=n;i++) printf("%c",s[i]);
		puts("");
	}
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/163868357)

---

## 作者：sea_bird (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1986C)。

# 题目大意

输入 $t$ 个样例，每个样例四行，第一行包含两个数 $n$ 和 $m$，第二行包含一个长度为 $n$ 的字符串 $s$，第三行包含 $m$ 长度的数组 $ind$ 这是字符串 $c$ 的**索引**，每一个索引指向，第四行包含 $m$ 长度的字符串 $c$，输出按字典顺序排列的**最小**字符串 $s$，该字符串可以通过重新排列数组 $ind$ 中的索引和字符串 $c$ 中的字母来获得。

# 题目分析

很明显~~根据标签看出~~这是一道**贪心**类题目，这里插一段对于**贪心的解释**，贪心的每一步行动总是按某种指标选取最优的操作，并且不考虑以后可能造成的影响。按题目要求求最小字符串，所以要让字符串 $s$ 前面尽可能的小，所以我直接对 $ind$ 还有 $c$ 进行**排序**，但是注意 $ind$ 索引会有重复，而重复的索引会指向同一个字符，所以会**覆盖**前面相同的指引，所以只用考虑最后一轮，前面的先用大的字符。对于如何对字符串排序，我选择先将其转换为整数类型的在进行排序，当然如果用 `char` 类型的就不用转换了。

对于**覆盖**可以这么看，因为索引与字符串都是升序了，所以前面的一定不会比后面大，所以相同的指引下，只用处理前面的字符，后面的忽略掉就行了，这就相当于用前面小的字符覆盖了大的字符。

# Code

```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>
#include<queue>
#include<stack>
#include<math.h>
#include<string>
#include<cstring>
#include<vector>
using namespace std;
int n,m,j;
string s,c;//可以试试char类型的 
int ind[100005];
int str[100005];

void ans(){
	cin>>n>>m;
	cin>>s;
	j=0;//每次使用都清零 
	for(int i=1;i<=m;i++){
		cin>>ind[i];
	}
	cin>>c;
	for(int i=1;i<=m;i++){
		str[i]=int(c[i-1]);//字符串转整数类型 
	}
	sort(ind,ind+m+1);
	sort(str,str+m+1);
	for(int i=1;i<=m;i++){
		if(ind[i]!=ind[i-1]){//判断指引不相同 
			j++;
			s[ind[i]-1]=char(str[j]);//-1是给字符的 
		} 
	}
	cout<<s<<endl;
}
int main(){
	int t;
	cin>>t;
	for(int i=1;i<=t;i++){
		ans();
	} 
	return 0;
}
```

---

## 作者：_ayaka_ (赞：0)

### 思路
既然 $ind$ 和 $c$ 都可以任意排列，我们又要求组成的字符串尽可能小，那么我们的思路就出来了：

1. 先将 $ind$ 和 $c$ 排序；

1. 一个一个将 $s$ 中的字母替换。

这样就解决了……吗？

注意到 $ind$ 可能会重复，而题目说重复时后加的会覆盖先加的，那我们只要把重复的位置放入字典序最大的字母就可以了！

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t, n, m, ind[100005], cnt;
char c[100005], s[100005];
signed main() {
	cin >> t;
	while (t--) {
		cin >> n >> m;
		scanf("%s", s + 1);
		for (int i = 1; i <= m; i++) cin >> ind[i];
		scanf("%s", c + 1);
		sort(ind + 1, ind + m + 1);
		sort(c + 1, c + m + 1);
		cnt = 0;
		for (int i = 1; i <= m; i++) {
			if (ind[i] == ind[i - 1]) continue;//如果重复就自动拿最后的替换（cnt没变就相当于拿最后替换了）
			s[ind[i]] = c[++cnt];
		}
		printf("%s\n", s + 1);
	}
	return 抄代码不是好习惯！;
}
```

---

## 作者：NEKO_Daze (赞：0)

洛谷题目传送门：[CF1986C](https://www.luogu.com.cn/problem/CF1986C)   | |  CF原题传送门：[1986C](https://codeforces.com/contest/1986/problem/C)

#### 简要题意

给出一个长度为 $n$ 的字符串 $s$，一个长度为 $m$ 的数组 $ind$ 和一个长度为 $m$ 的字符串 $c$。你可以对 $ind$ 和 $c$ 进行随意的排序，排完序后从 $c$ 的开头开始执行 $s_{ind}=c_i$，使得操作后的 $s$ 字典序最小。
#### 思路

显而易见，这道题暴力枚举不是正解。

考虑贪心。$ind$ 的顺序其实无关紧要，贪心思路为将 $c$ 按字典序排序后操作以做到操作后 $s$ 的字典序最小。注意 $ind$ 可能会有重复，将 $c$ 按字典序排序后，对 $ind$ 去重并开始操作更新 $s$ 即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=107;
int main()
{
 int t,x,n,m,p;
 string s,c;
 cin>>t;
 while(t--)
 {
  set<int>ind; //因为set有去重的功能，所以考虑用set
  p=0;
  cin>>n>>m>>s;
  for(int i=0;i<m;i++) {cin>>x; ind.insert(x);}
  cin>>c;
  sort(c.begin(),c.end());
  for(auto u:ind) s[u-1]=c[p++];
  cout<<s<<endl;
 }
}
```

---

## 作者：linjinkun (赞：0)

十分简单的贪心。

为了使字典序最小，一定要把小的字符放前面。

这道题就做完了。

### 细节

- $ind$ 数组要排序，因为 $ind$ 不是有序的。

- $ind$ 数组要去重，因为 $ind$ 数组可能有重复，重复的就把最差的字符分给它（实际代码可以不用分，直接去重，反正要着也没用），不能让它影响了答案。

代码（贼短）：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
char a[N];
int e[N];
char xuan[N];//对应题目ind
signed main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n,m;
		scanf("%d %d",&n,&m);
		scanf("%s",a+1);
		for(int i = 1;i<=m;i++) 
		{
			scanf("%d",&e[i]);
		}
		scanf("%s",xuan+1);
		sort(xuan+1,xuan+m+1);//字符也得排序
		sort(e+1,e+m+1);//排序
		int cnt = 0;
		for(int i = 1;i<=m;i++)
		{
			if(e[i]!=e[i-1])//已经排序，可以利用这点进行简单去重
			{
				a[e[i]] = xuan[++cnt];
			}
		}
		printf("%s\n",a+1);
	}
	return 0;
}
```

---

## 作者：Harrylzh (赞：0)

## 思路

统计出有哪些位置要被改变，因为字典序要最小，要改变的位置越靠前越要选小的字母放。同一个位置可能会操作多次，我们只关注最后一次。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,m;
char a[1000000+5];
long long p[1000000+5];
string s,s2;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		cin>>s;
		for(long long i=1;i<=m;i++)
		{
			cin>>p[i];
		}
		cin>>s2;
		for(long long i=0;i<s2.size();i++) a[i+1]=s2[i];
		sort(a+1,a+m+1);//可改字母排序
		sort(p+1,p+m+1);//方便统计有哪些可改位置
		long long cur=0;
		for(long long i=1;i<=m;i++)
		{
			if(i>1&&p[i]==p[i-1]) continue;//此位置已经放好
			s[p[i]-1]=a[++cur];
		}
		cout<<s<<"\n";
	}
	return 0;
}
```

---

## 作者：Weekoder (赞：0)

### 思路

注意到 $idn$ 和 $c$ 都可以重新排列，考虑排序。注意到如果 $idn$ 的元素全部都两两不相同，则直接在排序后按顺序填入即可，因为这样保证了字典序小的排在了前面。而如果有相同的元素呢？那么，先插入的元素会被后面的覆盖掉，我们只需要考虑最后一次操作，而前面的操作则用字典序最大的来顶替。这里，$idn$ 在排序后，相同的元素会挤在一起。

代码：

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e5 + 5;

int T, n, m, idn[N];

string s, t;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
	cin >> T;
	while (T --) {
		t = "";
		cin >> n >> m >> s;
		for (int i = 1; i <= m; i++) cin >> idn[i];
		for (int i = 1; i <= m; i++) {
			char ch;
			cin >> ch;
			t += ch;
		}
		sort(idn + 1, idn + 1 + m);
		sort(t.begin(), t.end());
		deque<char> q;
		for (int i = 0; i < t.size(); i++) q.push_back(t[i]);
		for (int i = 1; i <= m; i++) {
			if (idn[i] != idn[i - 1]) {
				s[idn[i] - 1] = q.front();
				q.pop_front();
			}
			else {
				q.pop_back();
			}
		}
		cout << s << "\n";
	}
    return 0;
}
```

---

