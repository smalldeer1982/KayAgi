# [ABC295D] Three Days Ago

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc295/tasks/abc295_d

`20230322` は並べ替えると `02320232` となり、これは `0232` を $ 2 $ 度繰り返しています。  
 このように、数字のみからなる文字列であって、適切に文字を並び替える (そのままでもよい) ことによって同じ列を $ 2 $ 度繰り返すようにできるものを **嬉しい列** と呼びます。  
 数字のみからなる文字列 $ S $ が与えられるので、以下の条件を全て満たす整数の組 $ (l,r) $ はいくつあるか求めてください。

- $ 1\ \le\ l\ \le\ r\ \le\ |S| $ ( $ |S| $ は $ S $ の長さ)
- $ S $ の $ l $ 文字目から $ r $ 文字目までの (連続する) 部分文字列は嬉しい列である。

## 说明/提示

### 制約

- $ S $ は数字のみからなる長さ $ 1 $ 以上 $ 5\ \times\ 10^5 $ 以下の文字列
 
### Sample Explanation 1

$ S= $ `20230322` です。 条件を満たす整数組 $ (l,r) $ は $ (1,6),(1,8),(2,7),(7,8) $ の $ 4 $ つです。

### Sample Explanation 2

$ S $ の先頭が `0` である場合もあります。

## 样例 #1

### 输入

```
20230322```

### 输出

```
4```

## 样例 #2

### 输入

```
0112223333444445555556666666777777778888888889999999999```

### 输出

```
185```

## 样例 #3

### 输入

```
3141592653589793238462643383279502884197169399375105820974944```

### 输出

```
9```

# 题解

## 作者：Nemophery (赞：9)

[在我的博客中查看](https://lixiang_juruo.gitee.io/mybolg/2023/03/27/%E3%80%90%E9%A2%98%E8%A7%A3%E3%80%91-ABC295D-Three-Days-Ago-%E9%A2%98%E8%A7%A3/)  

其实题目就是让你找到所有满足区间中每个数的都能和其他相同的数配对的区间有多少个。

我用的是一种类似前缀和的思路。  
我们定义 $sum_i$ 为从 $1$ 到 $i$ 所有数是否可以两两配对。比如 $j$ 在 $1$ 到 $i$ 中是否能全部配对，可以的话 $sum_i$ 的第 $j$ 个字符就是 $0$，如果有落单的则是 $1$。  
可能有点不好理解，可以举个例子：当 $S$ 是 `20230322` 的时候，那么 $sum_4$ 就是 `1001000000`。   
显然，在 $sum$ 字符串相同的两个 $i$ 为端点的区间是符合要求的。  
直接统计的时间复杂度是 $O(n^2)$，显然会爆，所以我们可以用 `map` 来统计有多少个相同的 $sum$。

AC code：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 1;
string s;
map <string, ll> mp;
int main() {
    cin >> s;
    int len = s.size();
    ll ans = 0;
    string sum = "0000000000"; //一开始没有数字，所以全部为零
    mp[sum]++;
    for (int i = 0; i < len; i++) {
        ll num = s[i] - '0';
        sum[num] = (sum[num] == '1' ? '0' : '1'); //如果以前数字 num 有落单的，那么现在这个数可以与以前落单的配对，就从 1 变成 0。如果以前没有落单的，那么现在这个数字 num 会落单，就从 0 变成 1。
        ans += mp[sum];
        mp[sum]++; //统计目前 sum 字符串出现的次数
    }
    cout << ans;
    return 0;
}
```


---

## 作者：Xy_top (赞：7)

线性做法！

观察这题的数据范围是 $5\cdot 10^5$，暴力枚举会 TLE，我们先来考虑可以被分成两个相同子串的字符串所具有的性质：所有字母的出现次数均为偶数。

再来考虑如何优化：显然一个字符串所有子串的数量为 $n^2$，需要减少这个数量。

此时我们发现任意两个前缀相减就能得到所有的子串那么如果想让两个前缀相减得到的字符串满足那个性质，前缀有什么要求呢？

不难发现，两个前缀中任意字母的出现次数相减得到的一定是偶数，简而言之，两个前缀中任意字母的出现次数的奇偶性相同，而字母只有 $10$ 种，$0$,$1\cdots 9$。

考虑状压 DP，出现次数为奇数表示为 $1$，偶数表示为 $0$，存每个前缀中给定 $0\cdots 9$ 出现的奇偶的方案数。

比如 $f[10000][1001011010]$ 意思就是前 $10000$ 个前缀中，满足 $1$，$2$，$4$，$7$，$9$ 出现的次数为偶数，$0$，$3$，$5$，$6$，$8$ 出现的次数为奇数的前缀数量。

第 $i$ 轮先把状态算出来，然后答案加上前面和它状态一样的，最后再把它的状态加上去。

另外需要注意，刚开始啥都不选的方案也有一种，以及开 LL。

```cpp
talk is cheap,show me the code:
```
简短的代码：

```cpp
#include <cstring>
#include <iostream>
using namespace std;
char s[500005];
int len, f[1024] = {1}, cnt[15];
long long ans;
signed main () {
	scanf ("%s", s + 1);
	len = strlen (s + 1);
	for (int i = 1; i <= len; ++ i) {
		++ cnt[s[i] - 48];
		int mask = 0;
		for (int j = 0; j <= 9; j ++) mask |= (1LL << j) * (cnt[j] & 1);
		ans += f[mask] ++;
	}
	printf ("%lld", ans);
	return 0;
}
```

---

## 作者：MYiFR (赞：3)


### 题意

[原题链接](https://atcoder.jp/contests/abc295/tasks/abc295_d)

规定如果一个字符串 $ E $ 可以经过排列得到一个字符串 $ E' $ ，使得 $ E' $ 等于连接任意两个完全相等的字符串 $ T $ 所得到的新字符串，那么称 $ E $ 是一个“快乐”的字符串。

给定一个由字符 `0` 到 `9` 构成的字符串 $ S $ ，求出 $ S $ 所有的连续子串中有多少个是“快乐”的。数据保证 $ 1 \leq | S | \leq 5 \times 10 ^ 5 $ ，其中 $ | S |$ 表示 $ S $ 的长度。

### 思路

首先可以得出一个非常显然的结论，一个字符串 $ E $ 中的每个字符都出现了偶数次是 $ E $ 是“快乐”的字符串的充要条件。

由此，问题就转化成了求 $ S $ 的所有连续字串中有多少个满足每个字符出现偶数次。设 $ S_i $ 表示由 $ S $ 的前 $ i $ 个字符组成的子串，那么对于两个字串 $ S_a $ 和 $ S_b $ （ $ a<b $ ）,如果每个字符在 $ S_a $ 中出现的次数与在 $ S_b $ 中出现的次数的奇偶性一致，就说明由 $ S $ 的第 $ a $ 个字符到第 $ b $ 个字符组成的字串一定是“快乐”的。又注意到 $ S $ 由字符 `0` 到 `9` 构成，所以可以用一个 `string` 记录在 $ S_i $ 中每一个字符出现的次数的奇偶性，再用 `map` 记录每个记录用 `string` 的出现次数，答案显然就是对于`map` 中所有 `string` 出现次数 $ x $ ，$ ans = \sum \frac{x\times(x-1)}{2} $ 。

### AC代码

[链接](https://atcoder.jp/contests/abc295/submissions/40069005)

``` cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pdd pair<db,db>
#define F first
#define S second
using namespace std;
string s,cnt;
map<string,ll> mp; 
ll ans;
int main(){
	cin>>s;
	cnt="0000000000";
	++mp[cnt];
	for(char C:s){
		if(cnt[C-'0']=='0') cnt[C-'0']='1';
		else cnt[C-'0']='0';
		++mp[cnt];
	} 
	for(auto to:mp){
		ans+=to.S*(to.S-1)/2;
	}
	printf("%lld",ans);
	return 0;
}
//Ltwcfm.
```

---

## 作者：ppip (赞：2)

值域无关。$O(n\log n)$。

每个数随机权值，将序列每个数替换为对应的随机权值，然后可以认为是查询有多少个区间里的数异或起来等于 $0$。扫一遍，用 map 维护某一个前缀异或和有多少相同的即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int mw[10];
map<int,int> mp;
int main() {
    string s;cin>>s;
    int n{s.size()};
    mt19937 e(0xb6e0);
    for (int i{0};i<10;++i) mw[i]=e();
    mp[0]=1;
    int pre{0};
    long long ans{0};
    for (auto c:s) {
        pre^=mw[c^48];
        if (ans+=mp[pre]);
        ++mp[pre];
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Cindy_Li (赞：2)

萌萌思维题，但是考场差一点AC。

------------

题目等价于寻找区间 $[l,r]$ 满足数字 $0$~$9$ 各出现偶数次。

根据
[找筷子](https://www.luogu.com.cn/problem/P1469)
这道题的经验，出现偶数次 = 异或和为 $0$ 。

但是发现如果和找筷子一样直接异或到一起会出现冲突
（例子：$3 \oplus 5 \oplus 6 = 0 $）。

所以变成二进制数就可以了。

---------

朴素想法是暴力枚举每个区间，然后异或判断。复杂度 $O(|S|^3)$，显然无法通过本题。

利用前缀和进行优化，可以把复杂度降到 $O(|S|^2)$，仍然不能通过本题。

------------

由于题目要求的只是数量，不需要求出每个区间。

考虑满足条件的 $[l,r]$ 区间性质，必满足 $xorsum_{l-1} = xorsum_{r}$。

那么求 $xorsum$ 时记录当前值的出现次数 $cnt_x$，以 $r$ 为右端点，满足条件的 $l$ 数量是 $cnt_x - 1$，也就是区间数量。

累加即可。

-------------

code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=1;i<=n;i++)
#define LL long long

const int N=5e5+5;
int a[N],m[N];
int cnt;
LL ans;//不开long long见祖宗

int main()
{
	while(char c=getchar()){
		if(isdigit(c)) a[++cnt]=c-'0';
		else break;
	}
	int x=0;
	m[0]=1;//处理以1为左端点的情况
	rep(i,cnt){
		x^=(1<<a[i]);//状压
		ans+=m[x];
		m[x]++;
	}
	cout<<ans<<endl;
	return 0;
}


```


---

## 作者：zajasi (赞：1)

## 题意
问有多少对 $(l,r)$，满足在区间 $(l,r)$ 间所有数的个数都是偶数。
## 解题思路
很水的想到了 $\Theta(n^2)$ 做法，就是前缀和做法。单这明显是不行的。

我们发现这道题有一个隐藏的数据范围：数字个数只有十个！所以说，对于每一个状态，统计前缀和，然后对于前缀和记录奇偶性。奇数记为 $1$，偶数为 $0$。这样就出来了一个 $01$ 串。我们此时要做的事情就是查找这个字符串跟以前有多少个是相等的。变为十进制记哈希就行了。
## AC 代码
```cpp
/*
written by : zjs123
*/
#include<bits/stdc++.h>
using namespace std;
string a;
int s[11];
long long z;
int ax[3003];
int two(string a){
    int z=0;
    for(int i=0;i<a.size();i++){
        z=z*2+a[i]-'0';
    }
    return z;
}//转十进制
main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>a;
    ax[0]=1;//刚开始就是 0，要记
    for(int i=0;i<a.size();i++){
        string ss="";
        s[a[i]-'0']++;//统计前缀和
        for(int j=0;j<10;j++){
            if(s[j]&1)ss+='1';
            else ss+='0';
        }//记录01串
//        cout<<two(ss)<<" "<<c[two(ss)]<<" "<<ax[two(ss)]<<"\n";
        z+=(long long)ax[two(ss)];//查答案
        ax[two(ss)]++;//次数加一
    }
    cout<<z;
    return 0;
}

```

---

## 作者：lilong (赞：0)

很显然，满足条件的子段的异或和均为 $0$（因为每个数都出现了偶数次，而两个相同的数的异或值为 $0$）。问题转化为求异或和为 $0$ 的子段的个数。

不难想到，可以从前往后扫一遍，并且计算异或和，可以得出起点为 $1$ 且满足条件的子段。那么如何计算中间的子段数量？有如下可行的方案：计算异或和并不是直接异或本身 $a_i$，而是异或 $2^{a_i}$（把每个数的状态用二进制表示，不同数字的位置是唯一的，效率高），然后令答案加上当前异或和在前面出现的次数即可（异或和不变，则说明中间一段的异或和为 $0$，为符合要求的子段）。

具体实现见代码：

```cpp
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;

int cnt[1000001],len,ans,k,d;

signed main()
{
	cnt[0] = 1;
	string s;
	cin >> s;
	len = s.size();
	for( int i = 0 ; i < len ; i ++ )
	{
		k = s[i] - '0';
		k = 1 << k;//等同于 2^k
		d ^= k;
		ans += cnt[d];
		cnt[d] ++;
	}
	cout << ans;
	return 0;
}
```


---

## 作者：incra (赞：0)

## [题目链接](https://www.luogu.com.cn/problem/AT_abc295_d)
## 题解
如果一个字串可以满足以某种方式将这个子段重排，将子段分成两个完全相同的部分，那么这个字串中每一个字符出现次数都是偶数次。

当一个字串在原字符串中的区间为 $[l,r]$，那么对于任意 $i\in[0,9]$ 都有 $cnt_{r,i}-cnt_{l-1,i}\bmod 2=0$，及 $cnt_{r,i}$ 与 $cnt_{l-1,i}$ 具有相同的奇偶性。

考虑到数字只有 $0\sim 9$，所以可以用位运算优化。若从 $1\sim i$ 的每一个字符的出现字数的奇偶性位运算表示为 $state$，那么在 $i$ 上的答案就是 $c_{state}$，其中 $c_{state}$ 表示在 $1\sim i-1$ 中状态为 $c_{state}$ 的个数。

## 代码
```cpp
#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;
const int N = 500010;
int n;
char s[N];
int cnt[N][10];
int c[1 << 11];
int main () {
	cin >> s + 1;
	n = strlen (s + 1);
	LL ans = 0;
	c[0] = 1;
	for (int i = 1;i <= n;i++) {
		int state = 0;
		for (int j = 0;j <= 9;j++) {
			cnt[i][j] = cnt[i - 1][j] + (s[i] == '0' + j);
			state |= (cnt[i][j] & 1) << j;
		}
		ans += c[state];
//		cout << state << ' ' << c[state] << endl;
		c[state]++;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

**翻译**

给你一个只包含数字的串 $S$，记它以下标 $l$ 的字符开头，以下标 $r$ 的字符结尾的子串为 $[l,r]$，求有多少个 $[l,r]$ 能通过改变字符位置变成一个完全由两个相同字符串组成的串。

**分析**

易发现，只要一个字符串所有字符都有偶数个，它就是符合题意的。那么我们就可以建立 $tot$ 数组，用 `tot[i][j]` 记录在第 $i$ 位之前及第 $i$ 位 字符 $j$（这里因为原串只含数字，所以可以这样记录）出现的次数，易得 $tot$ 数组递推公式，即除了 $tot_{i_{S_i}}$ 要加一之外，其它都与 $tot_{i-1}$ 相同即可。

注意到 $S$ 的最长长度为 $5\times 10^5$，朴素算法 $O(n^2)$ 过不了，所以继续找规律。

我们会发现，只有当两个 $tot$ 数组中的数 `tot[i][n]` 与 `tot[j][n]` 模 $2$ 相等时，其差才会是偶数，并且当一个 `tot[i]` 与一个 `tot[j]` 的所有字符模 $2$ 相等时，$[i,j]$ 才是符合题意的子串。那么我们可以进行一个基本的状态压缩：化为二进制。

记 $|S|$ 为 $S$ 的长度，我们对于所有 $1\le i\le |S|$ 的整数 $i$，与所有 $0\le j\le 9$ 的整数 $j$，将 `tot[i][j]` 乘上 $2^j$ 再加起来，可以得到一个状态，可以证明一个状态只对应一种 $tot$ 的值。数字只有 $10$ 个，所以对应的状态只有 $2^{10}=1024$ 种。开一个 $a$ 数组记录状态，$a_i$ 表示第 $i$ 个状态的出现次数。对于一个状态的出现次数 $x$，只需要选取其中 $2$ 个便可以成为符合题意的字符串，易得结果就是 $x\times (x-1) \div 2$ 种选择方法，所以答案就是 $\sum a_i\times({a_i-1})\div 2$。

**AC Code**
```
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
long long tot[int(5e5+10)][10],a[1025];
int main()
{
	long long t,ans=0;//比赛时没开long long吃了一次罚时，各位千万要记住开long long啊
	string s;
	cin>>s;
	long long n=s.size();
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=9;j++) tot[i][j]=tot[i-1][j];
		tot[i][s[i-1]-'0']++;//递推tot数组
		for(int j=0;j<=9;j++) tot[i][j]%=2;//只计算其模2的结果，所以可以直接对2取模
	}
	for(int i=1;i<=n;i++)
	{
		t=0;
		for(int j=0;j<10;j++)
		{
			t+=pow(2,j)*tot[i][j];//计算其对应状态
		}
		a[t]++;
	}
	a[0]++;//第0种状态对应的是S中第一个字符
	for(int i=0;i<=1024;i++)
	{
		if(a[i])
		{
			ans+=a[i]*(a[i]-1)/2;//计算答案
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Unnamed114514 (赞：0)

首先，重排为两个循环，那么这个子串的所有字符出现 $2$ 次，记 $sum_{i,j}$ 表示 $i$ 字符在前 $j$ 个中出现的次数，那么若 $[l,r]$ 是一个可行的答案，则有：

$$\forall i\in[0,9],(sum_{i,r}-sum_{i,l-1})\bmod 2=0$$

即 $sum_{i,r}\equiv sum_{i,l-1}\pmod2$。

那么我们只需要把 $sum_{0,1,\cdots,9,r}$ 压缩成一个字符串，然后在前面找有多少个相同的字符串即可，可以用 `map`。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5e5+5;
int n,sum[10][maxn],ans;
string s,str;
map<string,int> cnt;
signed main(){
	cin>>s;
	n=s.size();
	s=' '+s;
	for(int j=0;j<10;++j)
		str+='0';
	++cnt[str];
	for(int i=1;i<=n;++i){
		for(int j=0;j<10;++j)
			sum[j][i]=sum[j][i-1];
		++sum[s[i]-'0'][i];
		str="";
		for(int j=0;j<10;++j){
			sum[j][i]%=2;
			str+=sum[j][i]+'0';
		}
		ans+=cnt[str];
		++cnt[str];
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Hyh_111 (赞：0)

## **题意**

给定字符串 $s$，求有多少个 $s$ 的子串经过重排后可以变为一个字符串重复两次所得到的结果。

## **思路**

使用 $10$ 位 bitset 保存状态，初始时全部位为 $0$。再用一个 map 存储每个 bitset 的状态出现了多少次。

若 bitset 的第 $i$ 位为 $0$，则代表已有偶数个 $i$ 出现，否则代表已有奇数个 $i$ 出现。

遍历 $s$，将 bitset 的第 $s_i$ 位改为与原来相反的值，并在 map 中将对应 bitset 的值的那个位置加上 $1$。

最后，遍历 map，如果第一关键字（bitset 值）为 $0$，那么将答案加上第二关键字，然后再将答案加上 $C_{\text{第二关键字}}^2$ 即可。

## **代码**

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

inline int read()
{
	int res = 0,f = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') f = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		res = (res << 3) + (res << 1) + c - 48;
		c = getchar();
	}
	return res * f;
}

bitset<10> bt;//bitset
map<unsigned long,int> mp;//map

signed main()
{
	string s;
	cin >> s;
	int n = s.length();
	for (int i = 0; i < n; i++)
	{
		bt.flip(s[i] - 48);//更新bitset状态
		mp[bt.to_ulong()]++;//更新map
	}
	map<unsigned long,int>::iterator it;
	int ans = 0;
	for (it = mp.begin(); it != mp.end(); it++)//遍历map
	{
		int x = (*it).second,y = (*it).first;
		if (y == 0) ans += x;//若第一关键字0，则所有包含在内区间{1,r}都满足条件
		ans += x * (x - 1) / 2;//两两搭配
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

