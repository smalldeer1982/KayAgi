# [ARC140A] Right String

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc140/tasks/arc140_a

英小文字からなる文字列 $ T $ に対して次の問題を考え、その答えを $ f(T) $ とします。

> $ T $ の先頭の文字を削除し末尾に追加する操作を任意の回数行うことによって作ることのできる文字列の種類数を求めてください。

英小文字からなる長さ $ N $ の文字列 $ S $ が与えられます。あなたは以下の操作を $ K $ 回以下行うことが出来ます。($ 1 $ 回も行わなくてもよいです。)

- $ S $ の文字を $ 1 $ 個選び、任意の英小文字に変更する。

操作終了後の $ f(S) $ の値としてあり得る最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 2000 $
- $ 0\ \le\ K\ \le\ N $
- $ S $ は英小文字からなる長さ $ N $ の文字列である。
- $ N,K $ は整数である。

### Sample Explanation 1

$ 1 $ 回目の操作で $ 4 $ 文字目を `c` から `b` に変更すると $ S= $ `abab` となり、$ f(S)=2 $ となります。 $ f(S) $ を $ 1 $ 回以下の操作で $ 1 $ 以下にすることはできないため、答えは $ 2 $ です。

## 样例 #1

### 输入

```
4 1
abac```

### 输出

```
2```

## 样例 #2

### 输入

```
10 0
aaaaaaaaaa```

### 输出

```
1```

## 样例 #3

### 输入

```
6 1
abcaba```

### 输出

```
3```

# 题解

## 作者：chinazhanghaoxun (赞：5)

## 题意

题目定义 $f(s)$ 表示循环执行将 $s$ 这个字符串的第一位放到最后一位的操作，能产生多少个不同的字符串。该题还可以让我们对 $s$ 中的 $k$ 个字符进行修改，求可以得到的最小的 $f(s)$ 是多少。
## 分析与解

我们先来假设有个字符串是这样的：```abcabcabc```，那么可以得到它的 $f(s)$ 等于3，分别为```abcabcabc```，```bcabcabca```和```cabcabcab```。举了这个例子后，我们可以知道，要求 $f(s)$ 其实就是求字符串 $s$ 的最小循环节长度。

既然知道了这个核心问题，我们就可以知道，要进行的操作也一定是想把 $s$ 的最小循环节长度缩小。那么我把上边的例子改一改，变成```abcarcabd```，那么我们假设循环节长度为 3 ，便可以每 3 位分割一下，变成```abc```，```arc```和```abd```。首先看第一位，都是```a``` ,就不用管了。第二位，有两个```b```和一个```r```，为了构成相同的循环节，肯定将```r```改为```b```是最优的。同理，第三位应将```d```变成```c```。
## 代码实现方式

我们首先枚举循环节的长度，注意必须是 $s$ 长度的因数，否则直接跳过。接下来枚举每个循环节，统计每一位需要修改多少次。最后，判断这种修改方式是否符合只能修改 $k$ 次的要求。如果符合，就跟当前答案进行比较并更新为较小值。
## 代码及注释

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,k,ans=1000000;
	string s;
	cin>>n>>k>>s;
	for(int len=1;len<=n;len++){ //枚举得到循环节长度 
		if(n%len!=0){ //如果不是长度的因数直接跳过 
			continue;
		}
		int change=0; //记录当前改变次数
		for(int i=0;i<len;i++){ //只需要枚举第一个循环节 
			int t=-100; //用来记录当前这一次循环最大出现次数
			int have[27]={0};
			for(int j=i;j<n;j+=len){ //枚举循环节的每一位 
				t=max(t,++have[s[j]-'a']);
			}
			change+=n/len-t; //加上不是出现次数最多的 
		}
		if(change<=k){ //满足条件 
			ans=min(ans,len); //记录更小的答案 
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：HNOIRPplusplus (赞：2)

## 题意
+ 定义 $f(s)$：把字符串的第一位拿出来插到最后一位，求不停做此操作能够获得多少种字符串。
+ 你可以给你的长度为 $N$ 的字符串修改 $K$ 个字符。**可以不全部用完，甚至不用。**
+ 求修改完以后能获得的最小的 $f(s)$。

（这个题的翻译做的有一点孬）
## 做法
很明显的是，如果你的字符串是循环的，比如下面这个：`abab`，就是由 `ab` 循环而来的。易得它的 $f(s) = 2$。  
再比如，`iiyoiiyoiiyoiiyoiiyoiiyo`，是由 `iiyo` 循环而成，易得它的 $f(s) = 4$。

还不够明显吗？$f(s)$ 的大小就是循环节的长度！所以这题的核心在于：**构造循环**。而且循环节越短越好。
### 具体怎么做
首先很明显的是循环节的长度肯定是原字符串长度的因数，不然不能构成完整的循环。  
枚举了循环节长度之后，我们把每个循环节的每一位都比较一下，把出现次数最多的字母作为更改对象。

比如，`abcbscbbc` 这个字符串中，你打算以 $3$ 作为循环节长度。  
每节第一位： `a` 和 `b` 和 `b`，显然改成 `b`。  
每节第二位： `b` 和 `s` 和 `b`，显然改成 `b`。  
每节第三位： 都是 `c`，显然改成……不用改。

最后，如果修改次数不超过 `k`，我们就可以更新答案了。
## 代码
```cpp
#include <iostream>

using namespace std;

int main() {
  int n, k;
  string s;
  cin >> n >> k >> s;
  int ans = n;
  for(int l = 1; l <= n; l++) {
    if(n % l == 0) { //确定循环节长度
      int now = 0;
      for(int i = 0; i < l; i++) {
        int cnt[26] = {};
        int mx = 0;
        for(int j = i; j < n; j += l) {
          mx = max(mx, ++cnt[S[j] - 'a']); //确定出现最多的字母
        }
        now += n / l - mx; //修改的次数
      }
      if(now <= k) {
        ans = min(ans, l); //更新答案
      }
    }
  }
  cout << ans;
  return 0;
}
```
在[这里](/record/98326089)欣赏通过的记录。

---

## 作者：fish_love_cat (赞：1)

写在前面：**[双倍经验](https://www.luogu.com.cn/problem/P10810)**！

---

注意到可以直接枚举答案。直接 $O(n)$ 枚举即可。

对于每个答案的检查是容易的，时间复杂度易于做到 $O(n)$。

时间复杂度 $O(n^2)$，似乎已足以通过本题。~~虽然但是并没有去测（~~

只想过本题的可以直接去看代码了。

---

但是当梦熊的数据范围写着 $n\le 10^6$ 时，我们不得不再进行一个优化。

注意到，枚举答案的 $O(n)$ 似乎有些浪费。

使答案 $i$ 合法所必须具备的的前提条件是 $n\bmod i=0$。所以我们可以只枚举 $n$ 的因子。

这样就可以剪枝了。

因为 $n$ 的因子数量顶破天也不到 $2\sqrt n$，所以时间复杂度降到 $O(n\sqrt n)$。

好像还是很难通过 $n\le10^6$ 的数据？注意到，因子数量的根号显著跑不满，~~而且评测姬速度快的起飞~~，[最慢的点](https://www.luogu.com.cn/record/196072104)也只跑了 $300\text{ms}$。

那么就做完了。

---

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int k;
    string s;
    cin>>k>>k>>s;//过双倍经验时千万不要多读一个 k 啊！
    //cout<<s.size()<<' '; 
    for(int i=1;i<=s.size();i++){
        if(s.size()%i!=0)continue;
        int sum=0;
        for(int j=0;j<i;j++){int mapp[150]={};
            for(int g=0;g<s.size()/i;g++)
                mapp[s[g*i+j]]++;
            int maxx=-1;
            for(char c='a';c<='z';c++)
            maxx=max(maxx,mapp[c]);
            maxx=s.size()/i-maxx;
            sum+=maxx;
        }
            if(sum<=k){
                cout<<i;
                return 0;
            }
    }
    return 0;
}
```

---

## 作者：Lan_yan (赞：1)

显然在每个循环的同一位找到最多出现次数的字母替换即可。

主要是解答一些问题的。

一：为什么一定要是通过最小循环节修改？

因为循环节可以导致字符串走完一个循环节后还是原来样子。最小不用解释了吧。

如果不完全循环可以吗？显然不行。

例如字符串：`abcab`，如果你使用：`ab`，则可以看出走完循环后字符串变为：`cabab`，和原字符串不同。

二：为什么计字母数数组不能放到外面或者直接预处理？

因为大多数解法是所有循环的同一位比较看的，如果你预处理你就不知道在循环的第几位有哪些字母了。

三：如果我计数数组不初始化行吗？

祝你好运。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
char s[2005];
int main()
{
	int i,j,k;
	scanf("%d%d",&n,&m);
	cin>>s+1;
	for(i=1;i<=n;i++)
	{
		if(n%i==0)
		{
			int sum=0;
			for(j=1;j<=i;j++)
			{
				int maxn=0,cnt[30]={0};
				for(k=j;k<=n;k+=i)
					maxn=max(maxn,++cnt[s[k]-96]);
				sum+=n/i-maxn;
			}
			if(sum<=m)
			{
				printf("%d",i);
				return 0;
			}
		}
	}
	return 0;
}
```

---

## 作者：HHC883 (赞：1)

# 题目分析
容易发现，题目要求的就是 $k$ 次修改后得到的字符串的最短循环节长度（每个循环节都应是完整的，即末尾没有多余字符）。这很容易，只要枚举循环节可能的长度，即 $n$ 的因数，然后判断所需的最少修改次数是否小于 $k$ 即可，最后取最小值。
# 参考代码

```cpp
#include<iostream>
using namespace std;
int n,k;
char s[(int)1e5+5];
int cnt[30],ans=1e9;
bool check(int x){
	int tot=0;
	for(int i=1;i<=x;i++){
		for(int j=i;j<=n;j+=x) cnt[s[j]-'a']++;
		int maxn=0;
		for(int j=0;j<26;j++){
			if(cnt[j]>maxn) maxn=cnt[j];
			cnt[j]=0;
		}
		tot+=n/x-maxn;
	}
	return tot<=k;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>k>>s+1;
	for(int i=1;i*i<=n;i++){
		if(n%i==0){
			if(check(i)) ans=min(ans,i);
			if(i*i!=n) if(check(n/i)) ans=min(ans,n/i);
		}
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：lbh666 (赞：0)

## 题目分析

不难发现，$f(s)$ 就是求 $s$ 的循环节长度。所以考虑枚举循环节的长度，即 $n$ 的因数。然后统计循环节每一位字母出现次数的最大值，求出其它字母统一的最小代价，判断是否小于等于 $k$，最后取最小值即可。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,l,r) for(int i=l;i<=r;++i)
using namespace std;

const int N=1e6+5;
int k,n;
char s[N];
int mx[N][26];
int ch[N];

bool check(int p){
	rep(i,1,p)memset(mx[i],0,sizeof(mx[i]));
	rep(i,1,p)ch[i]=0;
	for(int i=1;i<=n;i+=p){
		for(int j=i;j<=i+p-1;++j){
			mx[j-i+1][s[j]-'a']++;
			int m=mx[j-i+1][s[j]-'a'];
			if(m>ch[j-i+1])ch[j-i+1]=m;
		}
	}
	int sum=0;
	rep(i,1,p){
		sum+=(n/p-ch[i]);
	}
	return sum<=k;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n>>k;
	cin>>s+1;
	for(int i=1;i<=n;++i){
		if(n%i)continue;
		if(check(i)){
			cout<<i<<"\n";
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：xk2013 (赞：0)

题目传送门：[AT_arc140_a [ARC140A] Right String](/problem/AT_arc140_a)

## 前置知识
- 字符串处理。

## 题意简述
本题给定我们字符串 $s$，让我们求 $k$ 次修改后得到的最小 $f(s)$，其中 $f(s)$ 定义为不断将字符串 $s$ 首位字符移动到最后一位的后面，最后能获得的不同字符串种类个数。

## 解题思路
不难发现 $f(s)$ 其实就是求 $s$ 的循环节长度，那这样思路就很明了了，枚举循环节长度，看看要修改多少次，$\le k$ 的话就输出即可。

实现时需要注意下细节。

## 完整代码
看完上面再看这儿，不能只看这儿，更不能 Copy！
```cpp
#include <algorithm>
#include <iostream>
#include <map>
#include <string>

int n, k;
std::string s;

int main(void)
{
	std::cin >> n >> k;
	std::cin >> s;
	
	for (int len = 1; len <= n; len++) // 枚举循环节长度
	{
		if (n % len != 0) // 必须整除，不然构不成循环节不是吗
		{
			continue;
		}
		
		int cnt = 0; // 修改次数
		
		for (int i = 1; i <= len; i++) // 遍历循环节的每一位
		{
			int res = 0;
			std::map <char, int> vis;
			
			for (int j = i - 1; j < n; j += len) // 统计字符个数
			{
				vis[s[j]]++;
			}
			
			for (auto [x, y] : vis) // 打擂台求最小修改次数
			{
				res = std::max(res, y);
			}
			
			cnt += n / len - res; // 计算修改次数
		}
		
		if (cnt <= k) // 判断是否符合要求
		{
			printf("%d", len);
			break;
		}
	}
	
	return 0;
}

```
----------------------
这是本五年级蒟蒻小学生的第 21 篇题解，不喜可喷，但求你不要喷太猛了哦~

## 更新日志
- 2025/01/11：初版。

---

## 作者：Dream_Stars (赞：0)

## 题目大意：
这道题定义 $f(s)$ 为将字符串 $s$ 的首位字母放到字符串的末尾，能获得不同字符串的数量。\
我们要做的就是把长度为 $N$ 的字符串修改 $K$
 次，可以比 $K$ 次少或者等于，但不能超过，求修改完以后最小的 $f(s)$ 的值。
## 算法分析：

我们可以先简单举几个例子来分析一下：

- 当字符串为 `qwqqwq` 时，显而易见，$f(s)$ 的数值为 $3$，是 `qwqqwq` 和 `wqqwqq` 和 `qqwqqw`；
- 当字符串为 `awaw` 时，显而易见，$f(s)$ 的数值为 $2$，时 `awaw` 和 `wawa`。

有以上两个例子的铺垫，我们可以知道题目求的是所给字符串的最小循环节，故我们可以枚举每一个循环节的长度，记录修改次数，若不比 $K$ 大，则记录答案，直至找到最优解。
## 代码展示：
```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAXN = 2 * 1e3 + 10;
const int N = 30;

char str[MAXN];
ll x[N];
ll n,k,t;
ll change,Max,ans = LONG_LONG_MAX;

bool work(ll l){
  if(n % l != 0) return false;
  change = 0;
  for(int i = 1 ; i <= l ; i++){
    memset(x , 0 , sizeof(x) ),
    Max = 0;
    for(int j = i ; j <= n ; j = j + l)
      x[str[j] - 'a' + 1]++,
      t = x[str[j] - 'a' + 1],
      Max = max(Max , t);
    change = change + n / l - Max;//修改次数记录
  }
  if(change > k)  return false;//判断是否可以修改
  else return true;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
  cin >> n >> k;
  for(int i = 1 ; i <= n ; i++)
	  cin >> str[i];
  for(ll l = 1 ; l <= n ; l++)//枚举循环节长度
    if(work(l) == true) ans = min(ans, l);
  cout << ans;
  return 0;
}
```

---

## 作者：细数繁星 (赞：0)

[洛谷双倍经验。好像是加强版。](https://www.luogu.com.cn/problem/P10810)

考虑其关键词：**循环节**，注意到循环节 $\mathrm{seq}\mid N$。因此，此部可优化掉大部分非因数的无效循环节。从枚举循环节个数开始。

对于每个循环节每一位，将所有其他的字符修改为出现次数最多的字符，这样做能减少修改操作次数。此方法最优，原因不言而喻。

**因此我们得出基本思路：枚举循环节个数，枚举循环节的每一位，枚举循环节。统计最多字符出现次数，统计循环节的修改次数，判断修改次数是否小于等于 $k$，若是，便为最佳答案。**

```cpp
#include <bits/stdc++.h>
#define rty printf("Yes\n");
#define RTY printf("YES\n");
#define rtn printf("No\n");
#define RTN printf("NO\n");
#define rep(v,b,e) for(int v=b;v<=e;v++)
#define repq(v,b,e) for(int v=b;v<e;v++)
#define rrep(v,e,b) for(int v=b;v>=e;v--)
#define rrepq(v,e,b) for(int v=b;v>e;v--)
#define stg string
#define vct vector
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

void solve() {
	
}


int k;
stg s;
int str[1005];

main() {
    int tmp;
//	int t; cin >> t; while (t--) solve();
  cin >> tmp >> k >> s;
  s = ' ' + s;
  int len = s.size() - 1;
  rep(i, 1, len) {
    if (len % i == 0) {
      int seq = len / i;
      int ans = 0;
      rep(j, 1, i) {
        int maxn = INT_MIN;
        memset(str, 0, sizeof str);
        rep(k, 1, seq) {
          int ind = j + (k - 1) * i;
          maxn = max(maxn, ++str[s[ind]]);
        }
        ans += seq - maxn; 
      }
      if (ans <= k) {
        cout << len / seq << endl;
        return 0;
      }
    }
  }
	return 0;
}

```

[AC 记录。](https://www.luogu.com.cn/record/180043448)

---

## 作者：RioFutaba (赞：0)

# 思路

对于一个由长度为 $l$ 的循环节组成的字符串 $s$，$f(s)=l$。每往后面放 $i$ 次就会重复。把 $s$ 修改成这种形式即可。

可以枚举循环节长度 $i$，对于一个循环节的某一位，修改成所有循环节的这一位出现次数最多的字符即可。

时间复杂度 $O(n^2)$。


```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=4e3+5;
int n,k;
int cnt[maxn][256];
string s;
bool check(int x){
	int tot=0;
	for(int i=0;i<n;i++)
		for(int j='a';j<='z';j++)
			cnt[i][j]=0;
	for(int i=0;i<x;i++){
		int mx=0;
		for(int j=i;j<n;j+=x)
			mx=max(mx,++cnt[i][s[j]]);//循环节的第i位出现最多的字母
		tot+=n/x-mx;//第i位需要修改的次数
	}
	return tot<=k;
}
int main(){
	cin >> n >> k;
	cin >> s;
	for(int i=1;i<=n;i++)
		if(n%i==0 && check(i)){
			cout << i << endl;
			return 0;
		}
}
```

---

## 作者：liuhongyang123 (赞：0)

## 真正要求的是什么
其实别看题目长那么抽象，其实就是求**循环节**，并且循环节要**最短**。

### why

我们可以手玩一个数据。

例如：

```dfsdfsdfsdfsdfs```

很明显答案是 $3$，分别是：

1. ```dfsdfsdfsdfsdfs```
2. ```fsdfsdfsdfsdfsd```
3. ```sdfsdfsdfsdfsdf```

在后面就是重复的了，所以我们就只需求**最短循环节**就行了。

## 做法
虽然吧，可以用 Kmp，但是显然大材小用了，数据太小了，所以啊，暴力大法好。

1. 枚举长度并判断可行性。
2. 试图修改并算出当前方案的答案。
3. 更新答案。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,ans,vis[30],maxx,tmp;
string s;
signed main(){
	cin>>n>>k;
	cin>>s;
	ans=n;
	for(int len=1;len<=n;len++) {
		if(n%len==0){
			tmp=0;
			for(int i=0;i<len;i++) {
				for(int j=1;j<=26;j++) vis[j]=0;
				maxx=0;
				for(int j=i;j<n;j+=len){
					vis[s[j]-'a'+1]++;
					maxx=max(maxx,vis[s[j]-'a'+1]);
				}
				tmp+=n/len-maxx;
			}
			if(tmp<=k) ans=min(ans,len);
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：_czy (赞：0)

### 题意

就是有一个字符串，你可以修改 $k$ 次，求**最小循环节**。

### 分析

为什么说是**最小循环节**？

因为题中的 $f(S)$ 究其根本就是 $S$ 的**最小循环节**。

我们每次将第一个字符放到最后，当刚好放完**最小循环节**个后，字符串开始重复。

所以，题中的 $f(S)$ 究其根本就是 $S$ 的**最小循环节**。

综上，我们只要枚举一下**最小循环节**的长度，再确认是否只需要 $k$ 次以下的修改就可以了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 2003
int n,k,s[30],maxs,sum,l;
char a[N];
int main(){
	scanf("%d%d%s",&n,&k,a+1);
	for(int i=1;i<=n;i++){
		if(n%i)continue;
		l=n/i,sum=0;
		for(int j=1;j<=i;j++){
			memset(s,0,26<<2);
			for(int k=0;k<l;k++)s[a[k*i+j]-'a']++;
			maxs=0;
			for(int k=0;k<26;k++)if(s[k]>maxs)maxs=s[k];
			sum+=l-maxs;
		}
		if(sum<=k){
			printf("%d",i);
			return 0;
		}
	}
}
```

---

