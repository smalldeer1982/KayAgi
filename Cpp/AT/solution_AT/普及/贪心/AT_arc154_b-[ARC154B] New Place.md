# [ARC154B] New Place

## 题目描述

给你两个长度为 $N$ 的字符串 $S$ 和 $T$，仅包含英文小写字母。

你可以重复进行下面的操作（可以不执行）：

- 将 $S$ 的第一个字符删去，并将这个字符插入到 $S$ 的任意位置。

问你至少执行多少次操作使得 $S$ 与 $T$ 相等。

## 样例 #1

### 输入

```
4
abab
abba```

### 输出

```
2```

## 样例 #2

### 输入

```
3
arc
cra```

### 输出

```
2```

# 题解

## 作者：CarroT1212 (赞：4)

### 题目大意

给定两个长度为 $N$ 的仅含小写字母的字符串 $S,T$。你可以进行若干次操作：删除 $S$ 的首位字符并将这个字符插入 $S$ 的任意位置。判断 $S$ 在操作后是否可以与 $T$ 相等，若可以，求出最小操作数。

数据范围：$1 \le N \le 2\times 10^5$。

------------

### 解法分析

首先有个结论：若 $S$ 中每个字母的个数都与 $T$ 中这个字母的个数相等，则一定有解，否则无解。

如果有数量不相等的字母，则显然怎么操作都不可能有解。

否则，我们就可以考虑把 $S$ 开头所有对不上 $T$ 的字符都通过操作插到后面。设 $S$ 中为 $T$ 的子序列的最长后缀子串的长度为 $l$，则答案为 $(N-l)$，也就是保持后面 $l$ 位不动，把前面 $(N-l)$ 位插到这 $l$ 位中间去，共需要 $(N-l)$ 次操作。容易发现这种做法在字母数相等的情况下一定有解，而且不会有比这更优的方法了。

匹配最长子序列是越早配上越好，所以可以 $O(N)$ 求出 $l$。

------------

### 代码

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
using namespace std;
const int N=2e5+7;
int n,cnts[129],cntt[129],ans;
char s[N],t[N];
int main() {
	scanf("%d%s%s",&n,s+1,t+1),ans=n;
	for (int i=1;i<=n;i++) cnts[s[i]]++,cntt[t[i]]++;
	for (int i='a';i<='z';i++) if (cnts[i]!=cntt[i]) return printf("-1"),0; // 字母数不相等
	for (int i=n;i;i--) if (s[ans]==t[i]) ans--; // 匹配
	printf("%d",ans);
	return 0;
}
```

---

## 作者：chinazhanghaoxun (赞：1)

## 思路
由于在操作过程中每个字母是不会额外出现或消失的，那么我们首先可以有一个特判，就是如果 $S$ 和 $T$ 每种字母个数都不一样，那么一定不行。

接下来考虑一般情况。选样例模拟一下便可以知道，$S$ 的后缀在没有被操作时永远保持的顺序不变，所以我们需要找到 $S$ 中的一个最长后缀子串且为 $T$ 的一个子串。那么我们就直接从后往前扫一遍，看有多长是 $S$ 和 $T$ 都有的。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnts[27],cntt[27],ans;
string s,t;
int main(){
	cin>>n>>s>>t;
	s='0'+s,t='0'+t;//使开头下标为1 
	for(int i=1;i<=n;i++){//记录每个字母出现次数 
		cnts[s[i]-'a'+1]++;
		cntt[t[i]-'a'+1]++;
	}
	for(int i=1;i<=26;i++){
		if(cnts[i]!=cntt[i]){//无法满足 
			cout<<-1;
			return 0;
		}
	}
	ans=n;
	for(int i=n;i>=1;i--){//从后往前扫一遍 
		if(s[ans]==t[i])
			ans--;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：_hxh (赞：1)

### 题意

给你两个长度为 $N$ 的字符串 $S$ 和 $T$，仅包含英文小写字母。你可以进行一次操作，将 $S$ 的第一个字符插入到另两个字符中去，问至少执行多少次操作才能使 $S$ 与 $T$ 相等。若怎么操作都不能使 $S$ 和 $T$ 相等，输出 `-1`。

### 分析

当然无解的情况就是 $S$ 中的某种字母的数量和 $T$ 中的不相等。反之则一定有解。分析一下，我们可以把 $S$ 拆成两个字串 $s1$ 和 $s2$，其中 $s1$ 是原字符串 $S$ 的前半部分，用来分配，插入到 $s2$ 中去的。这样显然 $s1$ 的长度就是操作次数，$s2$ 则是 $T$ 的子序列。要想让操作次数少，就要让 $s2$ 尽可能的长。

举个例子：

当 $S = \texttt{abbcaa}$，$T = \texttt{bacaba}$ 时，最优的分配方式就是 $s1 = \texttt{ab}$，$s2 = \texttt{bcaa}$，此时有最少操作次数，为 2。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
const int M = 30;
int n,a[M],b[M],cnt;
char s[N],t[N];
int main()
{
	cin >> n;
	cnt = n;
	for (int i = 1;i <= n;i++)
	{
		cin >> s[i];
		a[s[i] - 'a' + 1]++;
	}
	for (int i = 1;i <= n;i++)
	{
		cin >> t[i];
		b[t[i] - 'a' + 1]++;
	}
	for (int i = 1;i <= 26;i++)
		if (a[i] != b[i])
		{
			cout << -1 << endl;
			return 0;
		}
	for (int i = n;i >= 1;i--)
		if (s[cnt] == t[i])
			cnt--;
	cout << cnt << endl;
	return 0;
}
```

---

## 作者：Red_river (赞：1)

### 题目大意：
这道题其实就是说给你两个长度为 $n$ 字符串，然后每次从队首拿一个字符放到任何地方，求出最少什么时候使两个字符串相等。

#### 结论：
其实这道题有点类似于贪心，我们不难发现，其实只需要将每个不相等的字符直接插到最后面就行了，而最后面连续的与字符串相等的一段序列则完全不用变。具体可以参考代码以及注释部分。

```cpp
#include<bits/stdc++.h>
#define wk(x) write(x),putchar(' ')
#define wh(x) write(x),putchar('\n')
#define ll long long
#define ull unsigned long long
#define ri register int
#define INF 2147483647
#define mod 998244353
#define N 300005
#define Nm printf("No\n")
#define Yu printf("Yes\n")
#define f(x,k,y) for(int x=k;x<=y;x++)
using namespace std;
int n,m,k,jk,ans,sum,num,cnt,tot;
int head[N],dis[N],vis[N],wis[N],f[N];
char a[N],b[N];

void read(int &x)
{
	x=0;int ff=1;char ty;
	ty=getchar();
	while(!(ty>='0'&&ty<='9'))
	{
		if(ty=='-') ff=-1;
		ty=getchar();
	}
	while(ty>='0'&&ty<='9')
	x=(x<<3)+(x<<1)+ty-'0',ty=getchar();
	x*=ff;return;
}

void write(int x)
{
	if(x==0){
		putchar('0');return;
	}
	if(x<0){
		x=-x;putchar('-');
	}
	char asd[201];int ip=0;
	while(x) asd[++ip]=x%10+'0',x/=10;
	for(int i=ip;i>=1;i--) putchar(asd[i]);
	return;
}

signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n);scanf("%s%s",a+1,b+1);//a+1 和 b+1 代表从第1位开始存
	ans=n;//ans=n 代表如果全部不相等要多少次
	for(int i=n;i>=1;i--) f[a[i]]++,wis[b[i]]++;//每种字符个数加一
	for(int i='a';i<='z';i++) if(f[i]!=wis[i]){
		wh(-1);return 0;
	}// 从每个小写字符判断一次是否相等，毕竟不相等的话，只靠换位置是不可能使它一样的。 
	for(int i=n;i>=1;i--) if(a[ans]==b[i]) ans--;//如果相等就换下一位并且方案数减一 
	wh(ans);
	return 0;
}
```

---

## 作者：Register_int (赞：1)

转化题意：保留 $s$ 的一段后缀，将其余字符插入 $s$ 中，保证存在方案使得 $s$ 与 $t$ 匹配并且剩余后缀长度最大。首先，如果字母个数不同则无解，否则相当于重排，一定有解。接着，$s$ 的一段后缀不需要操作，当且仅当他为 $t$ 的一段子序列。因此，可以直接贪心地将 $s$ 的后缀与 $t$ 匹配，最后原串长度减去可以匹配的最大长度即为答案。时间复杂度 $O(n)$。

# AC 代码
```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int MAXN = 2e5 + 10;
 
int n, cnt[26]; char s[MAXN], t[MAXN];
 
int main() {
	scanf("%d%s%s", &n, s + 1, t + 1);
	for (int i = 1; i <= n; i++) cnt[s[i] - 'a']++, cnt[t[i] - 'a']--;
	for (int i = 0; i < 26; i++) if (cnt[i]) return puts("-1"), 0;
	for (int i = n, j = n; i; i--) {
		for (; j && t[j] != s[i]; j--);
		if (!j) return printf("%d", i), 0; j--;
	}
	puts("0");
}
```

---

## 作者：Daidly (赞：1)

# 题意

给定两长度为 $n$ 的字符串 $S,T$，定义一次操作为**取出 $S$ 的首位，插到任意位置**。询问最少的操作次数使 $S$ 变成 $T$，无解输出 `-1`。

# 题解

发现是取出一段前缀，然后将前缀中的每个字符插入到任意位置。显然若每个字符数相同，则一定有解（操作 $n$ 次）。

那么假如答案是操作 $k$ 次，则 $S_1\sim S_k$ 和 $S_{k+1}\sim S_n$ 有什么特点呢？发现 $S_{k+1}\sim S_{n}$ 是 $T$ 的一个子序列，而最小操作次数即为最长子序列有可二分性，二分判断即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long 

inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}

void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int N=2e5+5;
int n,ta[30],tb[30],t[N];
char a[N],b[N];
bool f;

bool check(int x){
	for(int i=1;i<=n;++i){
		if(x<=n&&b[i]==a[x])++x;
	}
	return (x==n+1);
}

signed main(){
	n=read(),cin>>(a+1),cin>>(b+1);
	for(int i=1;i<=n;++i)ta[a[i]-'a']++,tb[b[i]-'a']++;
	for(int i=0;i<26;++i){
		if(ta[i]!=tb[i]){f=1;break;}
	}
	if(f){puts("-1");return 0;}
	int l=1,r=n+1,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(check(mid))r=mid;
		else l=mid+1;
	}
	print(r-1);
	return 0;
}

```

---

## 作者：All_Wrong_Answer (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc154_b)


## 题目大意：

有两个长度为 $N$ 的字符串 $S$ 和 $T$，每次可以将 $S$ 的第一个字符放回 $S$ 中的任意位置，问最少要几次才能让 $S=T$。

## 题意转化：
贪心思想，将题目转化为找到一个字符串 $C$ 使得 $C$ 是 $T$ 的子串又是 $S$ 的**最长后缀子串**。

操作过程：

如果当前 $S$ 没有长度为 $x$ 的前缀连续子串与 $T$ 的前 $x$ 个字符相等，就进行操作，将 $S$ 的第一个字符插到与 $T$ 对应的位置上，直到存在前缀连续子串与 $T$ 的前 $x$ 位相等为止，操作了几次答案就是多少。

## 判断无解：

开两个 ```map<char,int>``` 分别存 $T$ 和 $S$ 中每个小写字母的个数，如果有任何一个小写字母数量不同就无解。

## 完整代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
char x[200005],y[200005];

map<char,int>s1;
map<char,int>s2;
//用来判断无解 
int n;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i];
		s1[x[i]]++; 
	}
	for(int j=1;j<=n;j++){
		cin>>y[j];
		s2[y[j]]++;
	}
	for(int i=int('a');i<=int('z');i++/*遍历每个小写字母*/){
		if(s1[char(i)]!=s2[char(i)]){
			cout<<"-1\n";//有任何一个不同就是无解 
			exit(0);
		}
	}
	int sd=0;
	for(int i=n;i>=1;i--){
		if(x[n-sd]==y[i]) sd++;//找子串 
	}
	cout<<n-sd<<endl;
	return 0;
}
```

---

## 作者：wbxxxx (赞：0)

# 思路：
先用统计每个字母个数，如果发现字母个数都不一样，不用想就知道不可能对了直接输出 $-1$ 即可，最后再扫一边如果发现字符串前位相同，每次对于原有的答案减 $1$，扫完后输出即可。

相信大家都会了吧或有思路了吧，话不多说贴代码。



```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read()
{
    int X=0,w=1;char ch=getchar();
    while(ch>'9' || ch<'0'){if(ch=='-') w=-1;ch=getchar();}
    while(ch<='9' && ch>='0') X=(X<<3)+(X<<1)+ch-'0',ch=getchar();
    return X*w;
}//没什么用的快读
int a[1000009],b[1000009];
char s[10000009],f[1000009];
signed main()
{
	int n,i,j,cnt;
	n=read();
    cin>>s+1>>f+1,cnt=n;
	for (i=1;i<=n;i++) {
		a[s[i]]++;
		b[f[i]]++;
	}//统计字母出现次数
	for (i='a';i<='z';i++){
		if (a[i]!=b[i]){
			cout<<-1;
			return 0;
		}//特判
	}
	for (i=n;i>=1;i--){
		if (s[cnt]==f[i])
		cnt--;
	}
	cout<<cnt;
	return 0;
}
```

---

## 作者：yzx3195 (赞：0)

# 题目大意

给你两个字符串，每次可以把第一个字符取出，放到第一个字符串的任意位置，求把两个字符串变成一样的所需的最少步数。

# 思路

首先对于两个字符数量不同的串，哪怕他变了无数次，它也不可能一样，所以，我们先特判一下无解的情况，然后，从后往前找有哪些是不同的。因为后面相同的的就不用变了，这样就结束了。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e05 * 2 + 7;

char s[MAXN];

char t[MAXN];

int n;

int cnt[27][2];

signed main()
{
    cin >> n;

    scanf("%s", s + 1);

    for(int i = 1; i <= n; i++)
    {
        cnt[s[i] - 'a' + 1][0]++;
    }

    scanf("%s", t + 1);

    for(int i = 1; i <= n; i++)
    {
        cnt[t[i] - 'a' + 1][1]++;
    }

    for(int i = 1; i <= 26; i++)
    {
        if(cnt[i][0] != cnt[i][1])
            return printf("-1"), 0;
    }

	int pos = n;

    for(int i = n; i >= 1; i--)
    {
    	if(s[pos] == t[i])
    		--pos;
    }

    printf("%d", pos);

    return 0;
}
```

---

## 作者：XYQ_102 (赞：0)

可以看出，$S$ 的后面没有被操作的字母肯定是 $T$ 的子序列（因为根本就没动过）。只要从后往前遍历 $S$，用一个指针从后往前扫描 $T$，找到最近的一个与  $S_i$ 相同的 $T_j$。如果找不到，答案就是前面的字符个数。

至于无解的判定，当且仅当 $S$ 与 $T$ 的各个字母数量相同时有解。
## 核心代码
```cpp
int n;
string a,b;
int cnt[26][2],pos;
void Solve()
{
	cin>>n>>a>>b;
	for(int i=0;i<n;i++)
		cnt[a[i]-'a'][0]++,cnt[b[i]-'a'][1]++;
	for(int i=0;i<26;i++)
		if(cnt[i][0]!=cnt[i][1])return cout<<-1,void();
	pos=n-1;
	for(int i=n-1;~i;i--)
	{
		while(pos>=0&&b[pos]!=a[i])pos--;
		if(pos<0)return cout<<i+1,void();
		pos--;
	}
	cout<<0;
}
```

---

## 作者：shengyeqi (赞：0)

## 题面

[题目传送门](https://www.luogu.com.cn/problem/AT_arc154_b)

## 思路


1. 如果 $S$ 的 $T$ 字符数量不相等，则输出 $-1$。
    
2. 如果在不满足第一条的情况下，就从 $T$ 的末尾开始往前遍历来与 $S[sum]$ 比较（一开始时 $sum$ 为 $n$）。  

	- 如果一样，则 $sum - 1$。
    
   最后 $sum$ 的值就是最小操作数。
	
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+100;
int St[999],Tt[999];//桶数组
char s[N],t[N];//字符数组
int main()
{
	int n;
	cin>>n>>s+1>>t+1;//由于后面下表是从1开始的，所以这里也要+1
	for (int i=1;i<=n;i++)//桶排序
	{
		St[s[i]]++;
		Tt[t[i]]++;
	}
	for(int i='a';i<='z';i++)//第一个规则
	{
		if(St[i]!=Tt[i])
		{
			cout<<"-1";
			return 0;
		}
	}
	int sum=n;
	for(int i=n;i;i--)//第二个规则
	{
		if(s[sum]==t[i])sum--;
	}
	cout<<sum;
	return 0;
}
```


---

## 作者：_GJM_ (赞：0)

###### [更好的阅读体验？](https://www.luogu.com.cn/blog/GeJiamu/solution-at-arc154-b)

## 题意
给出两个字符串 $S$ 与 $T$，将他们进行如下操作：

* 将 $S$ 字符串的第一位移动至任意一位。

问：最少多少次以后可以让 $S$ 与 $T$ 相等。

## 思路
1. 判断 $S$ 能不能与 $T$ 相等。
   *  如果 $S$ 的 $T$ 的各个字符数量不相等，就输出 $-1$。
  
1. 如果 $S$ 能与 $T$ 相等，就从 $T$ 的末尾往前遍历，并与 $S$ 比较。
	* 如果一样，就不用加，只需要将 $i$ 减 $1$ 继续向前遍历。
    
	* 如果不一样，就将 $ans$ 加 $1$。
    
   * 最后 $ans$ 的值就是次数。

## [AC Code](https://www.luogu.com.cn/paste/14vexz29)


---

## 作者：To_Carpe_Diem (赞：0)

## 题目简述
输入两个字符串 $S$ 和 $T$，将他们进行如下操作：

- 将 $S$ 字符串的第一位删掉，放在任意一位。

问最少多少次以后可以让 $S$ 和 $T$ 相等。

## 思路简述
看到这个题目以后，第一个想到的就是搜索，暴力搜一遍。但是仔细想来倒也不用这么麻烦，只需要特判一下就可以。

如果两个字符串连字母个数都不一样直接输出 $-1$。

否则只需要从 $T$ 的末尾向首位遍历并与 $S$ 比较。

- 如果一样，就不用加，只需要将 `index--` 继续向前遍历。

- 如果不一样，就直接 `sum++` 将次数加 $1$ 就可以了，最后 `sum` 的值就是次数。

## 代码实现
```cpp
#include<iostream>
using namespace std;

string s1,s2;//两个字符串 S 和 T。 
int n,t1[105],t2[105];//t1 和 t2 分别存储 S 和 T 中的26个字母各自出现了几次 。 

int main(){
	cin>>n;
	cin>>s1>>s2;
	//记录 S 中26个字母各自出现了几次 。 
	for(int i=0;i<n;i++)
		t1[int(s1[i]-'a')]++;
	//记录 T 中26个字母各自出现了几次。 
	for(int i=0;i<n;i++)
		t2[int(s2[i]-'a')]++;
	//如果两个字符串连字母个数都不一样，就说明不行。 
	for(int i=0;i<26;i++){
		if(t1[i]!=t2[i]){
			cout<<"-1\n";
			return 0;
		}
	}
	int index=n-1,sum=0;//index是 T 的下标，sum 是操作次数 
	for(int i=n-1;i>=0;i--){//从后往前遍历 
		if(s1[index]!=s2[i])
			sum++;//如果不一样就将 sum++ 增加操作次数 
		else index--;//一样就说明两个字符一样，就不用移动。继续将 T 向前遍历即可 
	}
	cout<<sum<<"\n";
	return 0;
}

```

---

## 作者：_zhx (赞：0)

# AT_arc154_b [ARC154B] New Place

### 思路

先桶排序，然后在比较 $s$ 和 $t$ 的字符：

如果 $s$ 和 $t$ 的字符不相等，就输出 $-1$。

否则从 $t$ 的末尾开始与 $s$ 的末尾比较，如果一样 $s$ 就往前推一位，最后与 $t$ 比较的那一位的下标就是答案。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+7;
int n,a[27],b[27],x;
char y[N],z[N];
int main()
{
	cin>>n>>y+1>>z+1,x=n;
	for(int i=1;i<=n;i++) a[y[i]]++,b[z[i]]++;
	for(int i='a';i<='z';i++) if(a[i]!=b[i]) cout<<"-1\n",exit(0);
	for(int i=n;i>=1;i--) if(y[x]==z[i]) x--; 
	cout<<x<<'\n';
	return 0;
}
```

---

## 作者：So_noSlack (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/AT_arc154_b)&[Atcoder 链接](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/arc154_b)

本篇题解为此题较**简单做法**及**较少码量**，并且码风优良，请放心阅读。

## 题目简述

给定两个长度为 $n$ 的字符串 $S,T$，定义一次操作可取出 $S$ 的首位，插到 $S$ 的任意位置。

求最少的操作次数使 $S$ 变成 $T$，**无解**输出 `-1`。

## 思路

首先很容易想到如果 $S$ 和 $T$ 的**某个字母的个数不同**，那么 $S$ 不可能变为 $T$。~~因为不可能凭空变出一个字母~~。通过两个**桶数组**即可记录 $S,T$ 的每个**字母个数**：

```cpp
int cnt_s[30], cnt_t[30];
for(int i = 0; i < n; i ++) 
	cnt_s[s[i] - 'a'] ++, cnt_t[t[i] - 'a'] ++;	
```

接着验证 $S$ 和 $T$ 的各个字母数量**是否一致**，一旦不一致立刻输出 `-1` 即可：

```cpp
for(int i = 0; i < 26; i ++) 
		if(cnt_s[i] != cnt_t[i]) {
			cout << "-1\n";
			return 0;
		}
```

特判 `-1` 的情况后就很简单了，**仅需遍历 $T$ 即可**，在过程中如果 $S$ 的当前位与 $T$ **相同**，则表示**不必进行操作**，把之前记录的 $ans$ **自减即可**。

经过以上分析，很容易即可得出**完整代码**了：

```cpp
#include<iostream>
using namespace std;

int n, cnt_s[30], cnt_t[30], ans = 0; // 必要数组不解释
string s, t; // 模式串和匹配串

int main() {
	cin >> n >> s >> t;
	ans = n - 1; // 因为下标从 0 开始，所以 ans 需初始化为 n - 1
	for(int i = 0; i < n; i ++) cnt_s[s[i] - 'a'] ++, cnt_t[t[i] - 'a'] ++; // 统计字母个数
	for(int i = 0; i < 26; i ++) 
		if(cnt_s[i] != cnt_t[i]) {
			cout << "-1\n"; // 字母个数不相同直接输出
			return 0;
		}
	for(int i = n - 1; i >= 0; i --)
		if(s[ans] == t[i]) ans --; // 满足条件不必操作，ans --
	cout << ans + 1 << endl; // 还是下标问题答案需 +1，建议写下标从 1 开始的
	return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/117459062)

$$\text{The End!}$$

---

