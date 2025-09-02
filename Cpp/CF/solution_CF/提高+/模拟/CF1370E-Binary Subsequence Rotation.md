# Binary Subsequence Rotation

## 题目描述

给定两个长度为$n$的$01$串$a$和$b$，要求串$a$的任意子序列经过若干次“旋转”操作变为串$b$

对于一次“旋转操作”我们这样定义：
如果我们要旋转的序列为

$c_1,c_2,c_3,c_4,c_5...c_n$

那么旋转之后的序列为$c_n,c_1,c_2,c_3,c_4...c_{n-1}$

例如对于$s=1110100$

如果我们旋转的子序列的下标为${2,6,7}$（从1开始）

那么旋转之后的串为$1010110 $

求至少进行多少次“旋转”操作，能够把串$a$变成串$b$

## 样例 #1

### 输入

```
6
010000
000001```

### 输出

```
1```

## 样例 #2

### 输入

```
10
1111100000
0000011111```

### 输出

```
5```

## 样例 #3

### 输入

```
8
10101010
01010101```

### 输出

```
1```

## 样例 #4

### 输入

```
10
1111100000
1111100001```

### 输出

```
-1```

# 题解

## 作者：Guess00 (赞：5)

### 思路:最大子段和
~~(个人认为E比D简单)~~

先考虑什么时候无解(即输出`-1`)，明显当两个串1(或0)的数量不同时无法转换。读入时统计两串1(或0)的数量，若不同则输出`-1`.

接下来就是算最小的操作次数了。首先，两个串同一位置的两数如果相等，那么就不用对这个位置的两个数进行更改，于是可以在后面直接忽略同一位置两个数已经相同的地方。

**(下面所考虑的每个位置都默认这一位置的两数不同)**

因为只考虑两数不同的位置，那么知道a串这一位置的数就可以知道b串这一位置的数，所以可以只考虑a串。

易得一次操作可以将a串中01...01都转换成10...10这样就能和b串一致了。也就是说如果在a串中发现一个0(或1)，只需要在它后面找一个1(或0)即可，因为这两个可以放在同一个操作中，但在找到1(或0)之前，0(或1)需要占一个操作。也就是说最小操作数就是在a串的任何一段中找到$($0的数量$-$1的数量$)$或$($1的数量$-$0的数量$)$的最大值。所以可以将0设为`+1`,将1设为`-1`,求最大子段和，再反过来求一遍，所求最大和即为最小操作数。

时间复杂度:$\Theta(n)$

$\mathbb{CODE:}$
```cpp
#include <bits/stdc++.h>
const int MAXN=1000005;
int n,i,cnt,ans;
bool a[MAXN],b[MAXN];
inline void read(int &x)  //快读 
{
	short negative=1;
    x=0;
    char c=getchar();
    while(c<'0' || c>'9')
    {
    	if(c=='-')
			negative=-1;
		c=getchar();
	}
    while(c>='0' && c<='9')
        x=(x<<3)+(x<<1)+(c^48),c=getchar();
    x*=negative;
}
inline void print(int x)    //快输 
{
    if (x<0)
        putchar('-'),x=-x;
    if (x>9)
        print(x/10);
    putchar(x%10+'0');
}
signed main(void)
{
	read(n);
	for (i=1;i<=n;i++)
	{
		char c=getchar();
		while (c!='0' && c!='1')
			c=getchar();
		a[i]=(c=='1');
		cnt+=(c=='1');   //统计1的数量 
	}
	for (i=1;i<=n;i++)
	{
		char c=getchar();
		while (c!='0' && c!='1')
			c=getchar();
		b[i]=(c=='1');
		cnt-=(c=='1');
	}
	if (cnt)   //如果两串1的数量不同,输出-1 
		return printf("-1"),0;
	//两遍最大子段和 
	for (i=1,cnt=0;i<=n;i++)
	{
		if (a[i]!=b[i] && a[i])
			cnt++;   //如果是1加1 
		if (a[i]!=b[i] && (!a[i]))
			cnt--;   //如果是0减1 
		if (cnt<0)
			cnt=0;
		ans=std::max(ans,cnt);
	}
	for (i=1,cnt=0;i<=n;i++)
	{
		if (a[i]!=b[i] && a[i])
			cnt--;   //如果是1减1 
		if (a[i]!=b[i] && (!a[i]))
			cnt++;   //如果是0加1 
		if (cnt<0)
			cnt=0;
		ans=std::max(ans,cnt);
	}
	print(ans);
	return 0;
} 
```

---

## 作者：vectorwyx (赞：3)

$a,b$ 的 $0,1$ 数量不同肯定无解，先判掉。每次选长度为偶且 $01$ 交替式的子序列一定不劣。这是因为其余形式的子序列在循环右移一位后都会有不改变的位置，把这些位置剔除不会产生影响。

只考虑所有不同的位置，这些不同的位置上 $0,1$ 数量必然相同。问题转为把它们分成尽量少的 01 交替的子序列满足长度均为偶。直接贪心，记录当前以 $0$ 结尾和以 $1$ 结尾的子序列数量，能接就接，否则新开一个子序列。

这样显然是最优的，但长度的奇偶性如何保证呢？由于 $01$ 数量相同，所以最终得到的以 $0$ 结尾的奇长度子序列与以 $1$ 结尾的奇长度子序列数量也相同，两两配对，比较末尾 $0,1$ 出现位置的前后关系，把更晚出现的 $0/1$ 放到更早出现的子序列末尾即可。注意到这样做不会使某些长度为 $1$ 的子序列变空，同时也验证了只考虑不同位置的正确性（因为所选子序列包含相同位置的目的只可能是调整奇偶性，但是这个构造方案自己就能保证奇偶性）。
```cpp
//author:望远星
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define db double
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){if(ch=='-') fh=-1; ch=getchar();} while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0'; ch=getchar();} return x*fh;}
inline void out(int *a,int l,int r){fo(i,l,r) printf("%d ",*(a+i));puts("");}

const int N=1.1e6;
char a[N],b[N];
int cnt[2],n,rp1,rp2; 

signed main(){
	cin>>n;
	scanf("%s%s",a+1,b+1);
	fo(i,1,n){
		if(a[i]=='1') rp1++;
		if(b[i]=='1') rp2++;
	}
	if(rp1!=rp2){
		puts("-1");
		return 0;
	}
	fo(i,1,n) if(a[i]!=b[i]){
		bool x=a[i]=='1';
		if(cnt[x^1]) cnt[x^1]--,cnt[x]++;
		else cnt[x]++;
	}
	cout<<cnt[0]+cnt[1];
	return 0;
}
/*
-------------------------------------------------
*/
```


---

## 作者：zhylj (赞：3)

### Solution

首先先删去 $a,b$ 串相同的元素。

然后只保留 $a$ 的元素就可以求答案了，考虑一次可以使一串 $1010101\dots$ 或 $0101010\dots$（长度为偶数）符合条件。

先判断是否有解：若 $0,1$ 个数相等，则有解。

扫一遍数组，过程中存下当前位置有多少个 $0$ 结尾的串，有多少个 $1$ 结尾的串，每次把 $0$ 加入到 $1$ 结尾的串中，把 $1$ 加入到 $0$ 结尾的串中。如果没地方加，就新开个串。

这样构造出来的答案不一定合法，但是由于 $0,1$ 的个数相同，所以长度为奇数的末尾为 $0$ 的串和长度为奇数的末尾为 $1$ 的串的个数是相同的，把末尾的 $0$ 补过去就好了。

显然这样是最优的。

### Code

```cpp
int n, cnt[2], cnt_df; char a[kN], b[kN];
int main() { 
	scanf("%d%s%s", &n, a + 1, b + 1);
	for(int i = 1; i <= n; ++i) {
		if(a[i] != b[i]) {
			int cur = a[i] - '0';
			if(cur && cnt[0]) --cnt[0];
			if(!cur && cnt[1]) --cnt[1];
			if(cur) ++cnt[1], ++cnt_df;
			else ++cnt[0], --cnt_df;
		}
	}
	printf("%d\n", cnt_df ? -1 : cnt[0] + cnt[1]);
	return 0;
}
```

---

## 作者：duyi (赞：2)

## 题解 CF1370E Binary Subsequence Rotation

首先，显然无解当且仅当$s,t$里$0$的数量不同。

有解时，显然$s_i=t_i$的位置是不需要动的。我们只考虑$s_i=0,t_i=1$和$s_i=1,t_i=0$的位置，分别称为$01$和$10$。

考虑一次操作能做什么。首先，它至少可以消除掉一组$(01,10)$，也就是实现“交换$s$里的两个位置”。但这么使用操作显然太浪费了。其实，一次操作可以直接消除掉一长串$01,10,01,10,\dots$。具体来说，只要相邻的两项不同，且总长度是偶数就行了。

要使得操作次数最少，可以贪心。比如说，如果当前是$01$，我们就将其加入一个$10$结尾的序列。如果没有$10$结尾的序列，就以这个$01$单独新开一个序列。一个序列就代表一次操作，最终答案就是总的序列数量。

我们前面还有一个要求，就是序列的长度必须是偶数。这显然总是可以满足的，因为我们已经判断过，$01$与$10$数量相等。

时间复杂度$O(n)$。

参考代码：

```cpp
//problem:
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

template<typename T>inline void ckmax(T& x,T y){x=(y>x?y:x);}
template<typename T>inline void ckmin(T& x,T y){x=(y<x?y:x);}

const int MAXN=1e6;
int n;
char s[MAXN+5],t[MAXN+5];
int main() {
	cin>>n;
	cin>>(s+1);
	cin>>(t+1);
	int cnt_s0=0,cnt_t0=0;
	for(int i=1;i<=n;++i)
		cnt_s0+=(s[i]=='0');
	for(int i=1;i<=n;++i)
		cnt_t0+=(t[i]=='0');
	if(cnt_s0 != cnt_t0){
		cout<<-1<<endl;
		return 0;
	}
	int cnt10=0,cnt01=0;
	for(int i=1;i<=n;++i){
		if(s[i] == '0' && t[i] == '1'){
			if(cnt10){
				cnt10--;cnt01++;
			}
			else{
				cnt01++;
			}
		}
		if(s[i] == '1' && t[i] == '0'){
			if(cnt01){
				cnt01--;cnt10++;
			}
			else{
				cnt10++;
			}
		}
	}
	cout<<cnt01+cnt10<<endl;
	return 0;
}
```



---

## 作者：123zbk (赞：1)

首先 $a$ 和 $b$ 种 $0$ 和 $1$ 数量不同肯定无解，先判掉。
 
然后考虑最少的操作次数，如果两个串位置相同的数相等，那么就不需要修改了，只考虑数不等的位置。

可以发现每次选择 $1010\cdots1010$ 或 $0101\cdots0101$ 这样的串是最优的，因为可以直接让其合法。

所以我们维护两个值：以 $1$ 结尾的串的数量和以 $0$ 结尾的串的数量。

如果两个串位置相同时的值不同，若 $a_i=1$，那么将它接到以 $0$ 结尾的串的后面，若 $a_i=0$，那么将它接到以 $1$ 结尾的串的后面，如果都不行只能重新开一个串。这样一定是最优的。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int n,cnt1,cnt2,res1,res2;
char a[maxn],b[maxn];
int main()
{
    cin>>n>>a+1>>b+1;
    for(int i=1;i<=n;i++)
    {
        if(a[i]=='1')
        {
            res1++;
        }
        if(b[i]=='1')
        {
            res2++;
        }
    }
    if(res1!=res2)
    {
        puts("-1");
        exit(0);
    }
    for(int i=1;i<=n;i++)
    {
        if(a[i]==b[i])
        {
           continue;
        }
        if(a[i]=='0')
        {
            if(cnt1)
            {
                cnt1--;
            }
            cnt2++;
        }
        else
        {
            if(cnt2)
            {
                cnt2--;
            }
            cnt1++;
        }
    }
    cout<<cnt1+cnt2;
    return 0;
}
```

---

## 作者：RyexAwl (赞：1)

# 题目大意
## 题目描述
给定两个长度为$n$的$01$串$a$和$b$，要求串$a$的任意子序列经过若干次“旋转”操作变为串$b$

对于一次“旋转操作”我们这样定义：
如果我们要旋转的序列为

$c_1,c_2,c_3,c_4,c_5...c_n$

那么旋转之后的序列为$c_n,c_1,c_2,c_3,c_4...c_{n-1}$

例如对于$s=1110100$

如果我们旋转的子序列的下标为${2,6,7}$（从$1$开始）

那么旋转之后的串为$1010110 $

求至少进行多少次“旋转”操作，能够把串$a$变成串$b$
## 输入格式
输入一共三行

第一行输入一个整数$n(1≤n≤10^6)$
第二行输入串$a$

第三行输入串$b$

## 输出格式
输出为$1$行，为最小的操作次数

# 思路

首先，如果要求我们改变的次数最小，那么我们就只改变$a$与$b$中不相同的元素。

设集合$c$为$a$中与$b$中的元素不同的元素，并且对于每个元素其值等于$a$的值。

而对于$c$中的元素而言，每一对不同的$1$和$0$都可以进行一次“旋转”操作，我们可以看作其两个元素进行交换。

而若干个元素的“旋转”操作可以看作若干次“交换”操作

因此如果$c$当中的$1$和$0$的个数不同是一定不能将$a$变为串$b$

而现在，我们的目标为用尽量少的操作使得$c$中的元素全部取反（即$1$变成$0$，$0$变成$1$）

那么我们每次进行旋转操作的序列一定是形如$010101$或$101010$这样的序列（必须为偶数位）

如果我们进行旋转操作的序列为形如$111000$这样的序列，那么就等价于我们进行三次$10$这样的旋转操作

那么我们要使得进行的操作次数尽量少，即每次使得我们选的子序列尽量的长

那么我们每进行一次操作就会使得和最大的子段的和减一，即每进行一次操作都能使得$max(\left | \sum_{i=l}^rc_i \right |)$减一

证明：

假设子段$[l,r]$的和为正数，那么子段两边的元素一定是$-1$，否则$\left | \sum_{i=l}^rc_i \right |$可以更大。

同理$c[l]$与$c[r]$必然是$1$，否则缩小区间范围，一定可以更大。

设该子段中一共有$k$个$1$，长度为$m$，那么该子段的$-1$的个数为$m-k$。

那么在该子段外至少有$2\times k -m$个$-1$

对于其中的$-1$，我们至多$m-k$次就可以将所有的$-1$变$1$（即所有的$-1$全都挨在一起的情况）

而对于每次操作，我们选择的$1$的个数比$-1$的个数多一定更优

因为我们当前子段的和是最大的，且为正，因此$1$的个数必然比$-1$的个数多

考虑反证

如果我们选的$-1$比$1$多的话，那么在当前子段至多选

$2\times m-2\times k-1$个元素


如果我们$1$的个数比$-1$的个数多，那么当前子段至多选

$2\times m-2\times k+1$个元素

而对于外面的元素，如果排序方式改变最多损失两个元素

因此至少不会变坏，且会更优

如果我们$-1$选$p$个，那么$1$必然会选$p+1$个

那么，其减少了$1$



如果到最后的序列不存在$-1$，那么每次我们至少可以从当前序列中选出一个$1$取反，因为在该子段外至少有$2\times k -m$个$-1$

因此，每次操作我们都可以使得$max(\left | \sum_{i=l}^rc_i \right |)$减一

并且，因为其和最大，所以能够确保每次操作，都能够作用于当前子段

那么，当$max(\left | \sum_{i=l}^rc_i \right |)$减为$0$时，即最小操作次数。

答案即为$max(\left | \sum_{i=l}^rc_i \right |)$

$QED$

而我们可以用下面代码$O(n)$的求出上述式子
```cpp
#include <iostream>
 
using namespace std;
 
const int maxn = 1e6 + 10;
 
char a[maxn],b[maxn];
 
int c[maxn],n;
 
 
int get(int x){
	int cur = 0,res = 0;
	for (int i = 0; i < n; i++){
		cur += x * c[i];
		res = max(res,cur);
		if (cur < 0) cur = 0;
	}
	return res;
}
 
int main(){
	cin >> n >> a >> b;
	int s0 = 0,s1 = 0;
	for (int i = 0; i < n; i++){
		if (a[i] != b[i] && a[i] == '1'){ 
			c[i] = 1;
			s1++;
		}
		if (a[i] != b[i] && a[i] == '0'){ 
			c[i] = -1;
			s0++;
		}
	}
	if (s1 != s0){
		cout << -1;
		//system("PAUSE");
		return 0;
	}
	cout << max(get(1),get(-1));
	//system("PAUSE");
	return 0;
}
```


---

## 作者：ASC_8384 (赞：1)

# CF1370E Binary Subsequence Rotation

[题目](https://codeforces.com/contest/1370/problem/E)

转自[CF1370E Binary Subsequence Rotation](https://www.asc8384.top/2020/CF1370E-Binary-Subsequence-Rotation.htmlgg)

---

## 大意

给你两个 01 串，求最少的操作次数，使这个串相等。

一次操作：任选几个不同位置上的数，然后讲这些数顺时针旋转（就是将第一个挪到最后，其它的往前）。

## 思路

很显然，两串相同的是不影响答案的。而且不需要选择连续的位置，如果有一个 01 交替的子串，那么只需要 1 次操作，就可以将它们变为一样的。

所谓 01 交替串，举个例子，A 串为`0101010`，B串则为`1010101`。

这样就有了一个很裸的想法：每次找到最长的 01 交替串，将它们变成一样的，直到找不出为止。答案就是能找到几个这样的串。

然后我打了一发暴力，T14；记录下每次可以是 01 交替串的位置，WA9，然后凉了。

因为每次要找的是最长的 01 交替串，所以答案其实就是**每个位置及之前的0和1数量差的最大绝对值**，即**前缀最大差值**。

为什么呢？

因为我们找的字符串需要是 01 交替的，而每一个 01 交替就对当前位置及之前的0和1数量差贡献了`1`。

并且不能有连续个 0 或 1，每有几个连续的，那么就对数量差贡献了`1`。

## 代码

```cpp
int ans1 = 0, ans2 = 0;
int tmp = 0;
for(int i = 1; i <= n; i++) {
	tmp += a[i] - '0';
	tmp -= b[i] - '0';
	ans1 = max(tmp, ans1);
	ans2 = min(tmp, ans2);
}
cout << ans1 - ans2 << endl;
```


---

## 作者：luan341502 (赞：0)

首先特判掉两个串 $1$ 的数目不等。

只在 $a_i\ne b_i$ 的情况修改下标 $i$，否则修改次数会显著增多。

考虑将这些位置配成 $0101\dots 01$ 和 $1010\dots 10$ 的形式，这样显然能让一次修改的位置尽可能多。

用两个变量统计当前有多少个 $0$ 结尾的这样的串和 $1$ 结尾的这样的串（这里的串指的是操作序列构成的串）。由于题目说是子序列修改，那么位置可以随意放在不同的修改里，也就是说不需要真的模拟操作，只要统计数目即可。遇到 $1$ 时要放到 $0$ 的后面，遇到 $0$ 时要放到 $1$ 后面，但如果放不了只能重新开一个串。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char a[1000005],b[1000005];
int cnt1=0,cnt2=0;
void solve(){
	cin>>n>>(a+1)>>(b+1);
	for(int i=1;i<=n;i++){
		if(a[i]=='1') cnt1++;
		if(b[i]=='1') cnt2++;
	}
	if(cnt1^cnt2){
		cout<<"-1\n";
		return;
	}
	cnt1=cnt2=0;//cnt1:1结尾的数组 cnt2:0结尾的数组 
	for(int i=1;i<=n;i++){
		if(a[i]==b[i]) continue;
		if(a[i]=='0'){
			if(cnt1) cnt1--;
			cnt2++;
		}else{
			if(cnt2) cnt2--;
			cnt1++;
		}
	}
	cout<<cnt1+cnt2<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);solve();
	return 0;
} 
```


---

