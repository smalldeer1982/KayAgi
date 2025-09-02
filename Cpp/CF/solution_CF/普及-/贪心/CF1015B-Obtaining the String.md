# Obtaining the String

## 题目描述

You are given two strings $ s $ and $ t $ . Both strings have length $ n $ and consist of lowercase Latin letters. The characters in the strings are numbered from $ 1 $ to $ n $ .

You can successively perform the following move any number of times (possibly, zero):

- swap any two adjacent (neighboring) characters of $ s $ (i.e. for any $ i = \{1, 2, \dots, n - 1\} $ you can swap $ s_i $ and $ s_{i + 1}) $ .

You can't apply a move to the string $ t $ . The moves are applied to the string $ s $ one after another.

Your task is to obtain the string $ t $ from the string $ s $ . Find any way to do it with at most $ 10^4 $ such moves.

You do not have to minimize the number of moves, just find any sequence of moves of length $ 10^4 $ or less to transform $ s $ into $ t $ .

## 说明/提示

In the first example the string $ s $ changes as follows: "abcdef" $ \rightarrow $ "abdcef" $ \rightarrow $ "abdcfe" $ \rightarrow $ "abdfce" $ \rightarrow $ "abdfec".

In the second example there is no way to transform the string $ s $ into the string $ t $ through any allowed moves.

## 样例 #1

### 输入

```
6
abcdef
abdfec
```

### 输出

```
4
3 5 4 5 
```

## 样例 #2

### 输入

```
4
abcd
accd
```

### 输出

```
-1
```

# 题解

## 作者：SUNCHAOYI (赞：6)

这道题应该是$SPJ$，只要输出一个合法的解即可。这道题有**两种情况**，一个是有解的情况，另一个是输出$-1$。由于无解情况比较容易实现，所以我先讲这个。

$\text{1.无解情况：}$  
当出现无解情况时，肯定是字符串$s$与字符串$t$中的某一个字母数量不匹配。因此我们只要**设置一个数组**，当输入字符串$s$时，我们用$+$来记录，即`num[s[i] -'0']++;`，当输入$t$时用来$-$记录。如果匹配,那么每一个`num[i]`的值一定是会被**抵消**的，因此**一定会等于$0$**。我们只要循环一边即可：
```
for(int i = 0;i < n;i++)
{
	ok[a[i] - 96]++;//s输入 
	ok[b[i] - 96]--;//t输入 
}
for(int i = 1;i <= 26;i++)
{
	if(ok[i] != 0)//若不等于0，则肯定出现了不匹配的情况 
	{
		cout<<-1;
		return 0;
	}
} 
```

$\text{2.输出答案：}$    
我们**根据字符串$t$的顺序来给$s$排一个序**，例如$t = bcda$,$s = abcd$，$t$的顺序为$1234$，那么最开始$s$的顺序就是$2341$,也就是说我们需要通过移动变成最后的**升序序列**。
```
for(int i = 0;i < n;i++)
{
	for(int j = 0;j < n;j++)
	{
		//i代表最终的顺序，j是循环需要赋上初始值的 
		if(a[j] == b[i] && in[j] == 0)//重复的字母赋同一个数值 
		{
			in[j] = i;//赋值 
			break;//以免再次更新，直接退出就行 
		} 
	}
}
```
赋上值后，因为**每一次只能交换两个相邻的字母**$swap\ characters\ s_{c_j} and\ s_{c_{j + 1}}$ ，因此就相当于进行**冒泡排序**
```
for(循环)//冒泡排序 
{
	for(循环)
	{
		if(需要交换)//需要交换 
		{
			记录答案；
			进行交换；
		}
	}
}
```

------------

### 那么最后我们看一下完整的代码：
```
#include <iostream>
#include <algorithm>
using namespace std;
int ans[400005],ok[30],in[200];
int main()
{
	int n,k = 0;
	string a,b;	
	cin>>n;
	cin>>a>>b;
	for(int i = 0;i < n;i++)
	{
		ok[a[i] - 96]++;//s输入 
		ok[b[i] - 96]--;//t输入 
	}
	for(int i = 1;i <= 26;i++)
	{
	 
		if(ok[i] != 0)//若不等于0，则肯定出现了不匹配的情况 
		{
			cout<<-1;
			return 0;
		}
	} 
	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < n;j++)
		{
			//i代表最终的顺序，j是循环需要赋上初始值的 
			if(a[j] == b[i] && in[j] == 0)//重复的字母赋同一个数值 
			{
				in[j] = i;//赋值 
				break;//以免再次更新，直接退出就行 
			} 
		}
	}
	for(int i = 1;i <= n;i++)//冒泡排序 
	{
		for(int j = 0;j < n - 1;j++)
		{
			if(in[j] > in[j + 1])//需要交换 
			{
				ans[++k] = j + 1;//字符串从0开始 
				swap(in[j],in[j + 1]);//交换 
			}
		}
	}
	cout<<k<<endl;
	for(int i = 1;i <= k;i++) cout<<ans[i]<<" ";
	cout<<endl; 
	return 0;
}
```

---

## 作者：EightSixSun (赞：2)

把t中的字符和s中的一个个匹配，按t中的序号给s中的赋值，做成一个数列 

然后冒泡排序即可 

//代码写的比较丑
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <cstdlib>
#define For(i,l,r) for(int i=l;i<=r;++i)

using namespace std;
int n,scnt[27],tcnt[27],sd[60],td[60];
char s[60],t[60];
int main()
{
    queue<int> ans;
    scanf("%d",&n);
    For(i,1,n)
    {
        while((s[i]=getchar())==' '||s[i]=='\n'||s[i]=='\r');
        scnt[s[i]-'a'+1]++;
    }
    For(i,1,n)
    {
        while((t[i]=getchar())==' '||t[i]=='\n'||t[i]=='\r');
        tcnt[t[i]-'a'+1]++;
    }
    For(i,1,26)
    {
        if(scnt[i]!=tcnt[i])
        {
            cout<<"-1";
            return 0;
        }
    }
    For(i,1,n)
    {
        td[i]=i;
        For(j,1,n)
        {
            if(s[j]==t[i]&&!sd[j])
            {
                sd[j]=i;
                break;
            }
        }
    }
    For(i,1,n)
    {
        For(j,1,n-1)
        {
            if(sd[j]>sd[j+1])
            {
                ans.push(j);
                swap(sd[j],sd[j+1]);
            }
        }
    }
    cout<<ans.size()<<'\n';
    while(!ans.empty())
    {
        cout<<ans.front()<<" ";
        ans.pop();
    }
}
```

---

## 作者：CQ_Bab (赞：1)

# 思路
这道题，评绿有点恐怖了，我们看到这里可以从第一个一直调整到最后一个，然后我们对于一个数如果它与目标串的这一位相等，那么不用改，如果不相等则去往后找第一个与它相等的位置，然后直接把拿一个数交换到这里来即可。这里因为不会改变每一个字符，所以如果字符出现的数量不相同的话，就输出无解。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define end putchar('\n')
#define in(x) scanf("%lld",&x)
#define lcm(x,y) x*y/__gcd(x,y)
#define il inline
#define pb push_back
#define w(x) while(x--)
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int n;
string s,t;
map<char,int>mp,ip;
bool check() 
{
	rep(i,1,n) {
		if(s[i]!=t[i]) return false;
	} return 1;
}
fire main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	cin>>n;
	cin>>s>>t;
	for(auto x:s) mp[x]++;
	for(auto x:t) ip[x]++;
	for(char c='a';c<='z';c++) {
		if(mp[c]!=ip[c]) {
			puts("-1");
			return false;
		}
	}
	s=" "+s;
	t=" "+t;
	vector<int>ans;
	while(!check()) {
		rep(i,1,n) {
			if(s[i]!=t[i]) {
				int stop=false;
				rep(j,i+1,n) {
					if(t[i]==s[j]) {
						stop=j;
						break;
					}
				}
				rep1(j,stop,i+1) {
					ans.pb(j-1);
					swap(s[j-1],s[j]);
				}
				break;
			}
		}
	}
	cout<<ans.size()<<endl;
	for(auto x:ans) cout<<x<<" ";
	return false;
}
/*
abdfec
abdfce
abdcfe
abcdfe
abcdef
*/

```

---

## 作者：ckk11288 (赞：1)

~~不应该是绿题~~

想要解决这道题，就得用**排序**思想，简单来说就是找一个匹配的字符不断交换直到到达目标位置。题目中的数据规模很小，所以两层循环就可以搞定的代码就没有必要再优化了。

那么，排序思想具体如何实现呢？我们从左到右开始重新排列，在第二个字符串中找到与第一个字符串当前位置所对应的字符，从右往左依次交换到目标位置。当然，如果两个字符串当前位置的字符本就已经相同了，就不必交换了。

具体说明在代码注释。

**Code：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,ans,x[10001],y[10001];
int main()
{
		char a[101],b[101];
		ans=0;
		bool yf=0;
		memset(x,0,sizeof(x));memset(y,0,sizeof(y));
		scanf("%d",&n);
		scanf("%s",a+1);
		scanf("%s",b+1);//将字符串开头下标改为1，方便代码实现
		int cnt=0;//步数
		for(int i=1;i<=n;i++)//从左到右实现（当然你想从右到左也行）
		{//循环到i时，那么i之前的所有字符都是匹配好的
			if(a[i]==b[i])continue;//已经相同了就没必要改动了
			int j=i;//需要重新排列
			for(;j<=n;j++)
			{
				if(i!=j&&a[j]==b[i])//不远万里找到一个一模一样的字符
				{
					break;
				}
			}
			for(int k=j;k>i;k--)
			{
				swap(a[k],a[k-1]);//逐步把这个字符交换到指定地点
				cnt++;
				x[cnt]=k-1;//记得存下过程
			}
		}
		bool f=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]!=b[i])
			{
				f=1;break;	//不行
			}
		}
		if(!f)//行
		{
			printf("%d\n",cnt);
			for(int i=1;i<=cnt;i++)
			{
				printf("%d ",x[i]);//输出步数
			}
		}
		else 
		{
			puts("-1");
		}
	return 0;
}
```

---

## 作者：Hutao__ (赞：0)

~~一道大水题~~

## 题目大意

有 $n$ 个钥匙和 $n$ 个锁孔，你只能将钥匙移动到相邻位置上，问要移动几次和移动的过程。

## 思路

直接暴力，从第一位开始找，如果不同，往后找到相同的交换，否则输出无解。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;//钥匙与锁孔
int n,ans[10005],cnt;
int main(){
	cin>>n>>a>>b;
	for(int i=0;i<n;i++){
		if(a[i]!=b[i]){//如果不同
			int l;//记录下一个相同字母的变量
			bool f=false;//标记变量
			for(int j=i+1;j<n;j++){//从下一个开始找
				if(a[j]==b[i]){//如果找到了
					f=true;//标记
					l=j;//记录位置
					break;//退出
				}
			}
			if(!f){//如果没找到，输出无解
				cout<<-1;
				return 0;
			}
			for(int k=l;k>i;k--){//将字母移动争取位置
				swap(a[k],a[k-1]);
				ans[++cnt]=k;//记录答案
			}
		}
	}
	cout<<cnt<<'\n';
	for(int i=1;i<=cnt;i++)cout<<ans[i]<<' ';
	return 0;//完美收工~
}
```

---

## 作者：chatoudp (赞：0)

因为 $n$ 很小且只需输出任意一种方案即可，所以可以枚举 $s2$ 的每个字符，在 $s1$ 中找。若没找到，输出 $-1$，否则让 $s1$ 中的那个字符交换到 $s2$ 当前字符的位置（详见下方代码片段）。
```cpp
//pos 表示 s1 中该字符的位置。
//i 表示 s2 当前的位置
for(int j=pos;j>i;j--){
			a[++n]=j;
			swap(s1[j-1],s1[j]);//交换 
} 
```

注意：如果当前 $s2$ 的字符与 $s1$ 这个位置的字符相等，直接跳过（我就被这坑了）。

接下来是 AC 环节，~~请乱抄袭~~请勿抄袭。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
string s1,s2; 
int n,a[10005],x;
int main(){
	scanf("%d",&x);
	cin>>s1>>s2;
	for(int i=0;i<x;i++){
		bool f=0;
		int pos;
		if(s2[i]==s1[i]) continue;//正确，不换 
		for(int j=i+1;j<x;j++)
			if(s1[j]==s2[i]){
				f=1;
				pos=j;
				break;
			}
		if(f==0){
			printf("-1");
			return 0;
		}
		for(int j=pos;j>i;j--){
			a[++n]=j;
			swap(s1[j-1],s1[j]);//交换 
		} 
	}
	printf("%d\n",n);
	for(int i=1;i<=n;i++) printf("%d ",a[i]);
	return 0;
}

```

---

## 作者：shredded_beef_qwq (赞：0)

## 具体思路
通过仔细读题我们可以发现 $n \le 50$，既然 $n$ 很小，那我们就可以直接暴力。我们可以直接按照题意枚举 $s1$ 和 $s2$ 的每一位，只要发现两个字符串的对应位不同，那么我们就枚举 $s1$ 的后面几位，如果 $s1$ 的后面几位中包含 $s2$ 这一位上的数，我们就交换 $s1$ 这两位的位置，并记录下交换过程和次数，否则就输出 $-1$。
## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
int ans[10010],cnt;
int main(){
	int n;
	cin>>n;
	cin>>a>>b;
	for(int i=0;i<n;i++){
		if(a[i]!=b[i]){
			bool f=false;
			int x;
			for(int j=i+1;j<n;j++){
				if(a[j]==b[i]){
					f=true;
					x=j;
					break;
				}
			}
			if(f==false){
				cout<<"-1"<<endl;
				return 0;
			}
			for(int j=x;j>i;j--){
				ans[++cnt]=j;
				swap(a[j],a[j-1]);
			}
		}
	}
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++) cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：TheSky233 (赞：0)

## Description

有两个字符串 $s,t$，问能否通过不超过 $10000$ 次交换 $s$ 中的相邻字符，使 $s$ 变为 $t$。

## Solution

首先，对于无解情况，只需 sort 一遍后比较是否相同即可。

如果有解，则对于每一个 $s_i \neq t_i$，从当前 $i$ 向后查找一个 $j$，使得 $s_i = t_j$，从 $j$ 向 $i$ 依次交换即可。


------------

### 时间复杂度分析

- 枚举外层 $i$ 的时间复杂度为 $\mathcal O(n)$

- 查找一个 $s_i=t_j$ 的时间复杂度为 $\mathcal O(n)$，从 $j$ 交换至 $i$ 的时间复杂度也为 $\mathcal O(n)$ ，注意这两个是同一层，时间复杂度为相加而非相乘。

于是总的时间复杂度即为 $\mathcal O(n^2)$。同理，交换次数上界也为 $\mathcal O(n^2)$，由于此题 $n$ 极小，因此可过。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

void Solve();

int n,m,q,k,p;
string a,b,c,d;
vector<int> v;

int main(){
	Solve();
}

int totMove;

void Solve(){
	cin>>n>>a>>b;
	c=a,d=b;
	sort(c.begin(),c.end());
	sort(d.begin(),d.end());
	if(a==b) return printf("0\n"),void();
	if(c!=d) return printf("-1\n"),void();
	for(int i=0;i<n;i++)
		if(a[i]!=b[i])
		for(int j=i+1;j<n;j++)
			if(b[i]==a[j]){
				for(int k=j-1;k>=i;k--)
					v.emplace_back(k+1),swap(a[k],a[k+1]),totMove++;
				break;
			}
	printf("%d\n",totMove);
	for(auto i:v) printf("%d ",i);
	return;
}
```

$\texttt{double exp:}$ [P8197](https://www.luogu.com.cn/problem/P8197)。

---

## 作者：X2H_tato (赞：0)

**题意：**

给出长度为n的两个字符串，问最少经过几次两个相邻字符的交换使得a串变成b串。

类比冒泡排序的算法，在找到一个ab不相同的字符时从当前位置开始交换，直到此处字符相同。

**代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
#define ll long long

int main()
{
	vector<int >v;
	int n,i,j,k,s[150]={0};
	string a,b;
	cin>>n;
	cin>>a>>b;
	for(i=0;i<n;i++)//存储字符及数量，判断ab字符串是否可能相等
	{
		s[a[i]]++;
		s[b[i]]--;
	}
	for(i=0;i<150;i++)
	{
		if(s[i]!=0)
		{
			cout<<"-1"<<endl;
			return 0;
		}
	}
	for(i=0;i<n;i++)
	{
		for(j=i;i<n;j++)
		{
			if(b[i]==a[j])
			{
				for(k=j;k>i;k--)
				{
					swap(a[k],a[k-1]);
					v.push_back(k);
				}
				break;
			}
		}
	}
	cout<<v.size()<<endl;
	for(i=0;i<v.size();i++)
	cout<<v[i]<<" ";
	return 0;
}

```


---

## 作者：zsc2003 (赞：0)

- codefoces 1015 div3 B
- 题目大意：
- 给你两个字符串s、t，长度均为n，你每次只能将si-1与si交换位置，如果最终能将s交换成为t，则输出最小的交换次数，否则输出-1

- 	思路：使用贪心的思想即可。
- 从1到n枚举t的每一位，若ti!=si,则寻找sj(j>i)于ti相同，若无法找到j则输出-1。否则让sj不断与sj-1交换位置，直到i=j 
- 代码实现：
```
#include<bits/stdc++.h>//万能头文件
using namespace std;
char s[60],t[60];
int n;
int step[5100],ans;
int main()
{
	scanf("%d",&n);//读入两个字符串
	for(int i=1;i<=n;i++)
		cin>>s[i];
	for(int i=1;i<=n;i++)
		cin>>t[i];
	for(int i=1;i<=n;i++)
	{
		if(t[i]!=s[i])
		{
			int j=i+1;
			while(s[j]!=t[i]&&j<=n+10)
				j++;
			j--;
			if(j>n)
			{
			    puts("-1");
			    return 0;
			}
			for(;j>=i;j--)
			{
				step[++ans]=j;
				swap(s[j],s[j+1]);
			}
		}
	}
	printf("%d\n",ans);
	for(int i=1;i<=ans;i++)
		printf("%d ",step[i]);
	return 0;
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

有点吓人。

注意到 $|s| \le 50$，考虑暴力。

假设当前处理到第 $i$ 位，且前 $i-1$ 位已经和 $b$ 相同。若当前这一位与 $b$ 的这一位相同，则继续处理 $i+1$ 就行。如果不同，我们显然只能向后找一个与 $b$ 的这一位相同的字符，通过交换把它换到第 $i$ 位上。这个在有解的时候交换次数是不超过 $n^2$ 次的，能过。

## 代码

[Link](https://codeforces.com/contest/1015/submission/231922358).

---

