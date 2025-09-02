# Count Good Substrings

## 题目描述

一个字符串是“好的”，当且仅当合并其中的连续区间后，它是一个回文串。比如“`aabba`”是好的，因为在合并后它变成了`aba`

给你一个字符串，现在要你分别求出长度为奇数和偶数的“好的”子串数量。（提示：不是本质不同的子串，不允许空串）

## 说明/提示

$1 \leq |s| \leq 10^5$，其中$|s|$是字符串的长度。

字符串只包含小写$a$和$b$两种字符。

## 样例 #1

### 输入

```
bb
```

### 输出

```
1 2
```

## 样例 #2

### 输入

```
baab
```

### 输出

```
2 4
```

## 样例 #3

### 输入

```
babb
```

### 输出

```
2 5
```

## 样例 #4

### 输入

```
babaa
```

### 输出

```
2 7
```

# 题解

## 作者：2023gdgz01 (赞：4)

考虑“好的”字符串形式，只能为 `ab...aba` 或 `ba...bab`。于是我们可以很快想出暴力做法，直接枚举 $s$ 的所有子串，判断其左右端点是否相等，时间复杂度为 $O(n^2)$。

可以 AC 前 $6$ 个测试点。[TLE 链接](https://www.luogu.com.cn/record/134317678)

代码如下：

```cpp
#include <iostream>
#include <string>

using namespace std;

int len, ans[2];
string s;

int main() {
	cin >> s;
	len = s.size();
	for (register int i = 0; i < len; ++i) {
		for (register int j = i; j < len; ++j) {
			ans[j - i + 1 & 1] += (s[i] == s[j]); //检查子串左右端点是否相等（j - i + 1 & 1 等同于 (j - i + 1) % 2 == 1）
		}
	}
	cout << ans[0] << " " << ans[1] << "\n";
	return 0;
}
```

------------

思考如何优化。对于当前下标 $i$，它会对所有下标 $x\text{ }(x\le i\text{ 且 }x\equiv i\pmod{2}\text{ 且 }s_x=s_i)$ 产生贡献，所以我们只需遍历一遍 $s$，并同时分别统计出当前下标 $i$ 前的 $a$ 和 $b$ 的数量即可，时间复杂度为 $O(n)$，可通过全部测试点。[AC 链接](https://www.luogu.com.cn/record/134320376)

最后， **十年 OI 一场空，不开 long long 见祖宗！**

代码如下：

```cpp
#include <iostream>
#include <string>

using namespace std;

int len, t;
long long ans[2];
long long sum[2][2]; //sum[0][j] 表示 s 中偶数位上的字符为 char('a' + j) 的个数，sum[1][j] 表示 s 中奇数位上的字符为 char('a' + j) 的个数
string s;

int main() {
	cin >> s;
	len = s.size();
	for (register int i = 0; i < len; ++i) {
		++ans[1]; //统计本身
		t = s[i] - 'a';
		if (i & 1) { //分别计算贡献
			ans[0] += sum[0][t];
			ans[1] += sum[1][t];
		}
		else {
			ans[0] += sum[1][t];
			ans[1] += sum[0][t];
		}
		++sum[i & 1][t];
	}
	cout << ans[0] << " " << ans[1] << "\n";
	return 0;
}
```

---

## 作者：叶ID (赞：2)

题目链接：[CF451D Count Good Substrings](https://www.luogu.org/problem/CF451D)

## 题意翻译

### 题目描述

一个字符串是“好的”，当且仅当合并其中的连续区间后，它是一个回文串。比如“`aabba`”是好的，因为在合并后它变成了`aba`

给你一个字符串，现在要你分别求出长度为奇数和偶数的“好的”子串数量。（提示：不是本质不同的子串，不允许空串）

### 输入格式

一行，字符串$s$

### 输出格式

一行，两个空格隔开的整数，分别为长度是偶数和奇数的“好的”字串数量。

### 样例解释

样例1中，有$s[1..1]= b$，$s[2..2] = b$和$s[1..2]= bb$是好的。

样例2中，好的子串有："$b$", "$a$", "$a$", "$b$", "$aa$", "$baab$"

样例3中，好的子串有："$b$", "$a$", "$b$", "$b$", "$bb$", "$bab$", "$babb$"

### 数据范围

$1 \leq |s| \leq 10^5$，其中$|s|$是字符串的长度。

字符串只包含小写$a$和$b$两种字符。

## 解题思路

**点拨提示：在这题中，由于只存在$a$和$b$两种字符，显然，子串是好的，当且仅当子串两端字符相同。如果只是来找解题提示的就无需往下看了。**

因此我们对于$a$和$b$字符做两次，每次只考虑一种字符。假设当前考虑的是$a$，

那么，我们分别统计当前位置以及之前的位置上，$a$出现在奇数位置和偶数位置的次数，然后就可以轻松求出以当前位置结尾的“好的子串”数量了（而且可以奇偶分别求）。

最终将$a$和$b$的答案分别相加即可。

## 代码与提交记录

```cpp
// status: [Accepted]
// oj:     [luogu]

#include<bits/stdc++.h>
using namespace std;

string s;
typedef long long ll;
#define int ll

pair<int,int> solve(char c) {
    int st[2];
    pair<int,int> ret = make_pair(0,0);
    st[0] = st[1] = 0;
    for(int i=0;i<(int)s.length();i++) {
        if(s[i] == c) {
            st[i%2]++;
            ret.first += st[(i%2)^1];
            ret.second += st[(i%2)^0];
        }
    }
    return ret;
}

signed main() {
    ios::sync_with_stdio(false);

    cin>>s;

    pair<int,int> x1 = solve('a');
    pair<int,int> x2 = solve('b');

    cout<<x1.first+x2.first<<' '<<x1.second+x2.second<<endl;
}

```

提交记录：[R24334233](https://www.luogu.org/record/24334233)


---

## 作者：PeterBei (赞：1)

考虑到字符串中只含有字母 $a$ 和 $b$，那么任意一个子串在经过化简后一定可以变成 $a$ 与 $b$ 轮流出现且每个字母仅出现一次的形式，即形如 ``a(b),b(a)...b(a),a(b)`` 的字符串。那么容易发现任意一个开头与结尾是相同字母的子串一定是一个回文串。

对此使用前缀和对 $a$ 和 $b$ 出现的次数进行维护即可。

但题目还要求记录回文串长度的奇偶，这时只需再开一维，将奇数位上和偶数位分开维护前缀和即可。

本题思维难度不大，若是使用普通写法的话代码难度也不高，因此建议使用位运算方法来编写该题代码，个人认为比较能锻炼逻辑思维。

```
int main(){
	scanf("%s", str + 1);
	long long len = strlen(str + 1);
	for(long long i = 1; i <= len; i++){
		ans[1]++;
		ans[i & 1] += sum[str[i] - 'a'][((i & 1) ^ 1) ^ (i & 1)];
		ans[(i & 1) ^ 1] += sum[str[i] - 'a'][(i & 1) ^ (i & 1)];
		sum[str[i] - 'a'][i & 1]++;
	} cout << ans[0] << ' ' << ans[1] << '\n';
	return 0;
}
```

---

## 作者：pandaSTT (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF451D)

## 前言

$ qwq $ 第一篇题解耶

## 题意：
给你一个字符串，然后找出奇数和偶数长度的子串的个数，这些字串符合，通过一些连续相同的字符合并后是回文串。

## 思路：
因为这些字符串中的字符只有 $  a,  b$，所以首位相同的字串都可以满足，这样就分别统计奇数和偶数位置的字符的个数，然后相互组合就可以。

## 代码

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  char s[100005];
  long long o[100005],e[100005],odd,even;
  int main(){
      cin>>s;
      int len=strlen(s);
      for(int i=0;i<len;i++){
          odd++;
          int x=s[i]-'a';
          if(i%2==0){
              odd+=o[x];
              even+=e[x];
              o[x]++;
          }
          else{
              odd+=e[x];
              even+=o[x];
              e[x]++;
          }
      }
      cout<<even<<" "<<odd;
      return 0;
   }
```


---

## 作者：Wf_yjqd (赞：1)

水题。

------------

显然去重后的串一定是 `a`，`b` 相间的。

所以只要开头结尾两个字符相同（均为 `a` 或均为 `b`），就是回文串。

考虑统计前面相同字符位置奇偶分别的个数，讨论贡献即可。

复杂度 $\operatorname{O}(n)$。

------------

注意统计奇偶相同时要加上本身，因为有长度为 $1$ 的串。

怕你不懂，写了点注释。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=1e5+84;
ll n,ans[2],cnt[2][2];//ans_i 表示长度为奇( i=1 )偶( i=0 )的个数，cnt_i_j 表示前缀中字符为a( i=0 )、b( i=1 )，位置为奇( j=1 )偶( j=0 )的个数
char s[maxn];
int main(){
    scanf("%s",s+1);
    n=strlen(s+1);
    for(ll i=1;i<=n;i++){
        ans[0]+=cnt[s[i]-'a'][i&1^1];//奇偶不同
        cnt[s[i]-'a'][i&1]++;
        ans[1]+=cnt[s[i]-'a'][i&1];//奇偶相同
    }
    printf("%lld %lld\n",ans[0],ans[1]);
    return 0;
}
```


---

## 作者：NahX_ (赞：0)

duel CF 上刷到的，晚了 5s 被薄纱了 /kk。

题目给定一个字符串只含 $a,b$，求分别有多少长度为偶 / 奇的子串为“好回文串”。

**字符串 $s$，为 “好回文串” 当且仅当合并连续相同字符后为回文串**。

比较重要的就是要想到一个字符串为好回文串当且仅当其中 $s_i \not= s_{i-1}$ 的个数为偶数，证明不难。

然后就有 $O(n^2)$ 的做法了。

容易发现可以直接做 $s_i \not= s_{i-1}$ 个数的前缀和，记 $sum_i$ 到第 $i$ 个字符的前缀和，从 1 遍历到 $n$，假如当前遍历到第 $i$ 位，记 $cnt_{0/1,0/1}$ 为所有 $sum_j \bmod 2=0/1,j\bmod 2=0/1，(j<i)$ 的个数，然后第 $i$ 位会更新答案为 $ans0\gets ans0+cnt_{sum_i \bmod 2,!(i\bmod 2)},ans1\gets ans1+cnt_{sum_i\bmod 2,i\bmod 2}$ ( $ans0$ 为长度为偶数的答案，$ans1$ 为长度为奇数的答案)，然后 $cnt_{sum_i\bmod 2 ,i\bmod 2}\gets cnt_{sum_i\bmod 2 ,i\bmod 2}+1$，对于长度为 1 的子串特殊处理即最后 $ans1 \gets ans1+n$。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
#define int long long
#define db double
#define endl '\n'
#define lowbit(x) x&-x
#define intz(x,a) memset(x,a,sizeof(x));
const int N=1e5+5;
char s[N];int cnt[N],ct[N][2];
signed main(){cin>>(s+1);int n=strlen(s+1),ans0=0,ans1=0;
	for(int i=2;i<=n;i++)if(s[i]^s[i-1])++cnt[i];
	for(int i=2;i<=n;i++)cnt[i]+=cnt[i-1];
	for(int i=1;i<=n;i++){
		ans0+=ct[cnt[i]%2][!(i%2)],ans1+=ct[cnt[i]%2][i%2];
		++ct[cnt[i]%2][i%2];
	}cout<<ans0<<' '<<n+ans1;
	return 0;
}

```

---

## 作者：GoodLuckCat (赞：0)

## CF451D题解

题目的意思就是：把字符串中的子串的所有字母“压缩”，同样的、连续的几个字母变成一个，让我们判断这一个字符串的字串是一个回文的字符串的有几个。

我的思路是，压缩后的回文的字符串有两种情况：$\texttt{abab...baba}$ 和 $\texttt{baba...abab}$，否则一定还可以压缩。从这里可以看出只需要判断首尾两个字符是否相等就行了。代码如下，记得开 `long long`。我用了分情况讨论，奇数和偶数两种。

```cpp
#include<iostream>
using namespace std;
long long a[100001],b[100001],a1,a2;//a1偶数，a2奇数
int main()
{
    char c;
    int t=0;
    while(cin>>c)
    {
        t++;
        c-=97;
        a2++;
        if(t%2)
        {
            a1+=b[c];
            a2+=a[c];
            a[c]++;
        }
        else
        {
            a1+=a[c];
            a2+=b[c];
            b[c]++;
        }
    }
    cout<<a1<<' '<<a2;
}
```

---

## 作者：_775spacing747_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF451D)

# 1 思路
通过分析样例可以发现，每一个子串在合并之后相邻两个字母一定不相同，所以，解题步骤如下：
1. 判断字符串首尾是否相同（即判断是否为回文）。 
2. 判断字符串长度的奇偶性。

# 2 代码
```cpp
#include<bits/stdc++.h>
#define int long long//这题要开long long 
using namespace std;
int a[100005],b[100005];
signed main()
{
	string s;
	int ans=0,sum=0;//需要两个计数变量 
    cin>>s;
    for(int i=0;i<s.size();i++)
	{
        ans++;//计数器++ 
        //判断奇偶性来了（重头戏） 
        if(i%2==0)//偶数 
		{
            ans+=a[s[i]-'a'];
            sum+=b[s[i]-'a'];
            a[s[i]-'a']++;
        }
        else//奇数 
		{
            ans+=b[s[i]-'a'];
            sum+=a[s[i]-'a'];
            b[s[i]-'a']++;
        }
    }
    cout<<sum<<" "<<ans;
    return 0;//华丽结束 
}
```

### [AC 记录](https://www.luogu.com.cn/record/131762306)

---

## 作者：Obviathy (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF451D)

## 题意简述

其实已经很清晰了，没有简述的必要

## 解题思路

考虑一个字符串合并完全之后是什么？一定是若干 `ab` 交替的吧！那么显然就只有两种情况：

- $\texttt{abab}\cdots\texttt{abab}$

- $\texttt{aba}\cdots\texttt{aba}$

那么其实很明显，第一种不是回文串，而第二种是。那么问题就得到了简化，即

> $S$ 有多少子串 $T$，长度位奇数（偶数），满足 $T_l = T_r$。

那么就直接可以搞出 $O(n^2)$ 的代码了：

```cpp
#include <bits/stdc++.h>
# define ll long long
# define ull unsigned long long
# define file(x) freopen(x ".in","r",stdin),freopen(x ".out","w",stdout)
# define IOS ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
using namespace std;
const int N = 1e5+10;
char s[N];
int ans2,ans1;
int main(){
   	IOS;
   	scanf("%s",s+1);
   	int n = strlen(s+1);
   	for(int len = 1;len <= n;len ++){
   		for(int l = 1;l + len - 1 <= n;l ++){;
   			int r = l + len - 1;
   			if((len & 1) && s[l] == s[r])ans2 ++;
   			if(!(len & 1) && s[l] == s[r])ans1 ++;
   		}
   	}
   	cout << ans1 << ' ' << ans2 << endl;
   	return 0;
}
```

然后喜提 $6$ 个点。

考虑怎样把它优化到线性。

我们发现其实没有必要枚举每一个区间。考虑枚举以 $i$ 位置位结尾有多少个满足条件的回文串，那么显然就可以分为一下几种情况会对答案造成贡献。

### 一、求长度为奇数的回文子串

现在我们已经枚举到了第 $i$ 个位置，那必定知道 $i$ 的奇偶性，分类讨论：

- 若 $i$ 为奇数位置，那么在它前面（包括它本身）奇数位置上的且与它字符相同的位置会对答案造成贡献。

举个例子，比如 $i=5$， 那么 $j=3$ 的时候，$i\sim j$ 这段表示的字符串长度为奇数，那如果这两个位置字符相同，那么就是一种答案。

- 若 $i$ 为偶数位置，那么在它前面（包括它本身）偶数位置上的且与它字符相同的位置会对答案造成贡献。

举个例子，比如 $i=4$， 那么 $j=2$ 的时候，$i\sim j$ 这段表示的字符串长度为奇数，那如果这两个位置字符相同，那么就是一种答案。

### 二、求长度为偶数的回文子串

现在我们已经枚举到了第 $i$ 个位置，那必定知道 $i$ 的奇偶性，分类讨论：

- 若 $i$ 为奇数位置，那么在它前面偶数位置上的且与它字符相同的位置会对答案造成贡献。

举个例子，比如 $i=5$， 那么 $j=2$ 的时候，$i\sim j$ 这段表示的字符串长度为奇数，那如果这两个位置字符相同，那么就是一种答案。

- 若 $i$ 为偶数位置，那么在它前面奇数位置上的且与它字符相同的位置会对答案造成贡献。

举个例子，比如 $i=4$， 那么 $j=3$ 的时候，$i\sim j$ 这段表示的字符串长度为奇数，那如果这两个位置字符相同，那么就是一种答案。

那么有了这个思路，我们只需要统计一下到目前 $i$ 位置**之前**，再奇数（偶数）位置上有几个 $\texttt{a}$，几个 $\texttt{b}$。

值得注意的是，我们统计的是 $i$ 位置之前，所以再计算长度位奇数的答案时，记得每次加上它本身一个字符的字符串。具体实现体现在 `ans1++` 上。

## code:

```cpp
#include <bits/stdc++.h>
# define ll long long
# define ull unsigned long long
# define file(x) freopen(x ".in","r",stdin),freopen(x ".out","w",stdout)
# define IOS ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
using namespace std;
const int N = 1e5+10;
char s[N];
ll ans0,ans1,cnt0[2],cnt1[2];
int main(){
	IOS;
	scanf("%s",s+1);
	int n = strlen(s+1);
	for(int i = 1;i <= n;i ++){
		ans1 ++;//注意不要漏下本身
		if(i & 1){
			ans1 += cnt1[s[i]-'a'];
			ans0 += cnt0[s[i]-'a'];
			cnt1[s[i]-'a']++;//奇数位置又多了一个的 s[i] 字符
		}else{
			ans1 += cnt0[s[i]-'a'];
			ans0 += cnt1[s[i]-'a'];
			cnt0[s[i]-'a']++;//偶数位置又多了一个的 s[i] 字符
		}
	}
	cout << ans0 << ' ' << ans1 << endl;
	return 0;
}
```

---

## 作者：Clarinet (赞：0)

[博客食用观感更佳](https://www.luogu.com.cn/blog/Czel-X/ti-xie-10-post)
# 简要题意
给出一个由 `ab` 组成的字符串，求在相邻的相同字符并为一个的情况下长度分别为偶数和奇数的回文串数量。
# 分析
首先，~~由于我的语文学的非常差~~，题目理解了好久才看懂。详细来讲，**确定回文串两端端点时，子串不应是合并状态**。

举个例子，如样例一的 `bb`，当我们分别选择位置 1 和 2 的两个字符时，我们可以发现最后合并完该子串中只会剩下一个字符 `b`，因此满足一种偶数长度的情况。至于奇数，就是每个 `b` 独立是一个回文串。

看其他题解也能轻易推出如果首尾字符种类相似的话就一定是回文串。接下来我们考虑如何计算。

先说结论：当遍历到一个奇数位时，则奇数子串数量的增加以前所有奇数位相同字符的数量，而偶数也增加所有之前偶数位相同字符的数量。当遍历到一个偶数位时，则反之。还有每个奇数位的字符都自成一个回文串。

这一部分稍稍有些难理解，~~这就是为什么这是道蓝题吗~~。如果实在难理解，可以对照几个样例看看。

或者可以这样想：若当前是奇数位，如 $i=5$，我们发现在 $i=1$ 的位置上有相同字符，则这个子串长度为 5，奇数子串数量加一。其他的结论也可以这样推出来。

再就是我看相同思路下其他题解好像都开了数组，个别几个开的还挺大，其实没有必要。我们用四个变量分别记录两个字符在两种位置上的数量就行了。**记得要开 `long long`，不然过不了！**
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
long long ans1,ans2,ja,jb,ra,rb;
int main(){
	cin>>a;
	for(int i=0;i<a.size();i++){
		ans1++;
		if(i%2==0){
			if(a[i]=='a'){
				ans1+=ja;
				ans2+=ra;
				ja++;
			}
			else{
				ans1+=jb;
				ans2+=rb;
				jb++;
			}
		}
		else{
			if(a[i]=='a'){
				ans1+=ra;
				ans2+=ja;
				ra++;
			}
			else{
				ans1+=rb;
				ans2+=jb;
				rb++;
			}
		}
	}
	cout<<ans2<<" "<<ans1;
	return 0;
}
```
感谢阅读！

---

## 作者：Φρανκ (赞：0)

题意：求一个由 a 与 b 构成的字符串中“好”子串（将所有连续相同字符压为一个后得到回文串）的数量。

核心思想：找规律

解：

发现在压完后所有字符串中均是 ab 交替出现，可知当且仅当该字符串开始和结尾相同时它“好”。

定义以下变量：

|  |a 的个数|b 的个数|
| :----------: | :----------: | :----------: |
|第偶数位|$ae$|$be$|
|第奇数位|$ao$|$bo$|

可以知道，偶数长度的“好”字符串始终点奇偶性不同，奇数的则相同。所以，偶数长度子串有 $aeao+bebo$ 个，奇数长度的则有 $\frac{ae^2+ae}{2}+\frac{ao^2+ao}{2}+\frac{be^2+be}{2}+\frac{bo^2+bo}{2}$ 个（对于每一类，设其中字符个数为 $i$，则可选字串数量为 $C^2_i+i$，因为要包含仅有一个字符的子串的情况），分别计算并输出即可。

代码：
```
#include <bits/stdc++.h>
using namespace std;
long long ao, ae, bo, be, res;
char ch[100001];
int main()
{
	cin>>ch+1;
	for(int i=1; i<=strlen(ch+1); i++)
		if(i%2==0)
			if(ch[i]=='a')
				ae++;
			else
				be++;
		else
			if(ch[i]=='a')
				ao++;
			else
				bo++;//统计
	cout<<ao*ae+bo*be<<" ";
	cout<<(ao*ao+ao+ae*ae+ae+bo*bo+bo+be*be+be)/2;//输出
	return 0;
}

```

---

