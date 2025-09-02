# Making Anti-Palindromes

## 题目描述

给您一个由小写字母组成的字符串 $s$，在每次操作中，您可以交换 $s$ 中的任意两个字母，请问把 $s$ 变为“反回文串”的最小操作次数是多少？


“反回文串”定义为：对于一个长度为 $n$ 的字符串 $s$，如果对于任意 $1\leqslant i\leqslant n$ 均有 $s_i\not=s_{n-i+1}$，那么字符串 $s$ 就叫做“反回文串”。

## 样例 #1

### 输入

```
10
10
codeforces
3
abc
10
taarrrataa
10
dcbdbdcccc
4
wwww
12
cabbaccabaac
10
aadaaaaddc
14
aacdaaaacadcdc
6
abccba
12
dcbcaebacccd```

### 输出

```
0
-1
1
1
-1
3
-1
2
2
2```

# 题解

## 作者：Lonehll (赞：9)

本题的题意很好理解，给一个字符串，一次操作可以交换其中任意两个字符，要达到的目标是把这个字符串变成 anti-palindrome，求最少的操作次数。  
所谓 anti-palindrome，就是对于字符串 $s$，任意的 $i$ 都满足 $\mathit{s}_i \neq \mathit{s}_{n-i+1}$（$\mathit{s}_i$ 为字符串 $s$ 的第 $i$ 个字符）。

很显然的，我们可以知道：
1. 如果某字母出现次数大于 $\frac{n}{2}$，那么它将无法成为 anti-palindrome。
1. 如果n是奇数，那么对正中间那个字符，它自己一定等于它自己，因此该字符串也无法成为 anti-palindrome。

以上就是任意次交换都无法成为 anti-palindrome 的充要条件，知道这个之后，我们就要开始计算合法情况的最小交换次数。

我们将字符串看成一对一对的字符，每一对的构成为 $\mathit{s}_i$ 和 $\mathit{s}_{n-i+1}$，很显然，一次交换操作带来的收益只能是减少一对或者两对相同的字符，我们希望减少两对的操作尽可能多，为了方便，我们将满足 $\mathit{s}_i = \mathit{s}_{n-i+1}$ 的字符对$(\mathit{s}_i, \mathit{s}_{n-i+1})$称为非法对，反之则为合法对。

举个例子，对于字符串 $s = \texttt{abccba}$，  
我们可以做到交换 $\mathit{s}_1$ 和 $\mathit{s}_2$，变成 $\texttt{baccba}$,此操作减少了两对，  
之后我们交换 $\mathit{s}_2$ 和 $\mathit{s}_3$，变成 $\texttt{bcacba}$ 于是此操作减少了一对。  
那么通过观察我们可以发现，如果我们将两个不同的非法对中的字符进行交换，则可以一次减少两个非法对，于是这样的操作数与值不同的非法对个数有关。  
我们记非法对中，值为 $\texttt{a}$ 的数目为 $\operatorname{num}\{ \texttt{a} \}$，记总共的非法对的数目为 $k$。对任意字母 $c$，如果都有$2 \times \operatorname{num}\{c\} \le k$，那么我们可以做到所有交换操作都为减少两对的（除了奇数对情况中的最后一对）。于是此时的答案为 $\frac{k}{2}$ 向上取整（考虑到奇数情况）。  
如果不满足该条件，那么我们可以知道，答案为 $\max(\operatorname{num}\{c\})$，这个结论的推导比较显而易见，因为对于所有值为c的非法对，都至少需要一次交换，而它的出现次数是最多的，因此在交换的过程中，就可以把其他非法对顺带变成合法的。  
代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;

int t, num[30];
char c[200010];

int main() {
	cin >> t;
	int n, cnt = 0;
	while(t--) {
		memset(num, 0, sizeof(num));
		cnt = 0;
		cin >> n;
		for(int i = 1; i <= n; i++) {
			cin >> c[i];
			num[c[i]-'a']++;  //此时num数组num[i]代表ascii码为(i+'a')的字符在该字符串中出现的次数
		}
		if(n % 2 != 0) {  //字符串中的字符个数为偶数则不可能成为anti
			cout << -1 << endl;
			continue;
		}
		int maxx = 0;
		for(int i = 0; i < 26; i++) {
			if(num[i] > maxx)
				maxx = num[i];
		}
		if(maxx > n/2) {  //某字符最多出现次数超过字符总数则也不可能成为anti
			cout << -1 << endl;
			continue;
		}
		memset(num, 0, sizeof(num));  //此时num为对应字符的非法对数
		for(int i = 1; i <= n/2; i++) {
			if(c[i] == c[n-i+1])
				cnt++, num[c[i]-'a']++;
		}
		maxx = 0;
		for(int i = 0; i < 26; i++) {
			if(num[i] > maxx)
				maxx = num[i];
		}
		if(maxx <= cnt-maxx)
			cnt = (cnt+1)/2;
		else
			cnt = maxx;
		cout << cnt << endl;
	}
    return 0;
}
```


---

## 作者：WaterSun (赞：1)

# 思路

发现对于无解的情况，当且仅当同一种字符出现次数大于 $\frac{n}{2}$ 或者 $n$ 为奇数。

然后统计每一种有字符的冲突对数，记 $vis_i$ 表示字符 $i$ 的冲突对数，并记 $num = \max \{vis_i\}$，$cnt = \sum vis_i$。

如果 $2num \leq cnt$，说明你每一次操作都会使两种不同字符交换到可行的位置，所以答案为 $\lceil \frac{cnt}{2} \rceil$。

否则，说明需要将 $vis_i = num$ 的这一种字符与其它字符交换，答案为 $num$。

# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

int n;
int vis[50];
string s;

inline int up(int a,int b){
    if (a % b == 0) return a / b;
    return a / b + 1;
}

inline void solve(){
    int Max = 0,ans = 0;
    cin >> n >> s;
    s = ' ' + s;
    if (n & 1){
        puts("-1");
        return;
    }
    memset(vis,0,sizeof(vis));
    for (re int i = 1;i <= n;i++){
        vis[s[i] - 'a']++;
        Max = max(Max,vis[s[i] - 'a']);
    }
    if (Max > n / 2){
        puts("-1");
        return;
    }
    memset(vis,0,sizeof(vis));
    for (re int i = 1,j = n;i <= j;i++,j--){
        if (s[i] == s[j]) vis[s[i] - 'a']++;
    }
    int cnt = 0,num = 0;
    for (re int i = 0;i < 26;i++){
        if (vis[i]){
            cnt += vis[i];
            num = max(num,vis[i]);
        }
    }
    if (num * 2 <= cnt) printf("%d\n",up(cnt,2));
    else printf("%d\n",num);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
```

---

## 作者：Amtlose (赞：0)

## 题目解析  
求变成“反回文串”的最小次数。

## 思路
首先应该明确什么时候要输出 $-1$。如果字符串的长度是奇数，或者一种字母的个数大于 $\frac{n}{2}$，那就输出 $-1$。

对于第一种情况，中间字母的下标固定为 $n\div2+1$，因此最中间的那个字母不会发生变化。

对于第二种情况，因为有一种字母的个数大于 $\frac{n}{2}$，即使在最优的情况下，字符串的前半段都会为同一种字母，这个字母一定还会出现剩余，所以字符串的后半段一定会出现与其对应位置的字母相同的情况。

接下来是有解的情况。比较 $s_i$ 和 $s_{n-i+1}$ 是否相等时，如果发现相等，就与其他字母交换，最终答案就不一定是最小的。

举一个例子，有一个字符串 $s=\texttt{abccba}$。如果交换 $s_1$ 和 $s_3$，就还需交换 $s_2$ 和 $s_4$ 才能让两组非法对变成合法对。若我们直接交换 $s_1$ 和 $s_2$，只交换一次就让两组非法对变成合法对了。因此我们可以发现这个的交换次数与 $s_i$ 和 $s_{n-i+1}$ 在变化过程中相等的次数有关。所以我们尽可能让两组 $s_i$ 和 $s_{n-i+1}$ 相等的非法对变成 $s_i$ 和 $s_{n-i+1}$ 不相等的合法对。

设在非法对中出现 $k$ 的次数为 $sum_k$，一共有 $cnt$ 个非法对。若对于任意一个字母 $c$，都有 $2\times sum_c\le cnt$，就可以做到每一次交换都可以让两组非法对变成合法的，并且不会把本来就合法的对交换成非法对。如果不满足 $2\times sum_c\le cnt$，答案就是 $sum$ 数组中的最大值。因为对于每一个非法对都至少要交换一次，而当前这个字母在非法对中出现得最多，所以在交换的过程中就可以让其它的非法对变成一个合法对。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T;
int a[200010];
int sum[200010];
signed main()
{
    cin>>T;
    while(T--)
    {
        int n;
        string s;
        cin>>n>>s;
        s=" "+s;
        if(n%2==1)//长度是奇数的时候 
        {
            cout<<"-1"<<endl;
            continue;
        }
        memset(sum,0,sizeof(sum));//多测 
        for(int i=1;i<=n;i++)//求每一个字母出现的个数 
        {
            sum[s[i]-'a']++;
        }
        int maxn=-1;
        for(int i=0;i<26;i++)
        {
            maxn=max(maxn,sum[i]);//如果最大的不行了，所有的都不行 
        }
        if(maxn>n/2)
        {
            cout<<"-1"<<endl;
            continue;
        }
        memset(sum,0,sizeof(sum));
        int cnt=0;
        for(int i=1;i<=n/2;i++)
        {
            if(s[i]==s[n-i+1])
            {
                cnt++;//算非法对的个数 
                sum[s[i]-'a']++;//求出字母是s[i]在非法对中出现的次数 
            }
        }
        maxn=-1;
        for(int i=0;i<26;i++)
        {
            maxn=max(maxn,sum[i]);//求出最大值 
        }
        if(maxn<=cnt-maxn)//如果满足 2*sum[c]<=cnt
        {
            cout<<(cnt+1)/2<<endl;
        }
        else//否则
        {
            cout<<maxn<<endl;
        }
    }
    return 0;
}
```

---

## 作者：Three_leaf (赞：0)

### 题面
给你一个由小写字母组成的字符串 $s$，在每次操作中，你可以交换 $s$ 中的任意两个字母，请问把 $s$ 变为“反回文串”的最小操作次数是多少？


“反回文串”定义为：对于一个长度为 $n$ 的字符串 $s$，如果对于任意 $1\leqslant i\leqslant n$ 均有 $s_i\not=s_{n-i+1}$，那么字符串 $s$ 就叫做“反回文串”。

### 思路
一个合格的反回文串，显然满足两点：

- 长度为偶数。
- 不存在绝对众数。

读者自证不难。

然后我们发现最小一定得优先将 $i,j\ (s_i=s_{n-i-1},s_j=s_{n-j-1},s_i \not= s_j)$ 换位，因为这样用 $1$ 的贡献处理了 $2$ 个。特殊的，最多的种数如果大于其他的总和，贡献是他的数量，否则是总的要改的的数量。这里的总的要改的的数量是指一对一对的出现的，所以代码实现的时候要除以 $2$，而最多的种数同理要除 $4$。

### 代码
```cpp
#include<bits/stdc++.h>
#define Maxn 100005 
using namespace std;
map<char,int> mp;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t,n;
    cin>>t;
    string s;
    while(t--) {
        cin>>n>>s;
        int ans = 0; mp.clear();
        for(int i=0;i<n;i++) {
            mp[s[i]] ++;
            ans=max(ans,mp[s[i]]);
        } mp.clear();
        if(n & 1 || ans*2 > n)cout<<"-1\n";
        else {
            int res = 0;ans = 0;
            for(int i=0;i<n;i++)
                if(s[i] == s[n-i-1]) {
                    res++;
                    ans=max(ans,++mp[s[i]]);
                }
            // cout<<res<<" "<<ans<<" ";
            cout<<max(ceil(res*1.00/4.000),ceil(ans*1.0/2.00))<<"\n";
        }
    }
    return 0;
}
```

---

## 作者：CodingOIer (赞：0)

## CF1822E Making Anti-Palindromes 题解

### 思路分析

首先去掉 $n \bmod 2 =1$ 的情况，因为中间的字符正对自己。

然后我们记录下每一个字符的重复情况，即 $p_i$ 为 $j \le \dfrac{n}{2}, s_j = s_{n - j + 1} = i$ 的数量。

然后我们可以对于每一个字符的重复情况两两互消。

剩下的仅仅可能有一个仍然重复的。

考虑下面的情况，$s_a = 2, s_b = 1, s_c = 1$。

如果我们先吧 $b$ 和 $c$ 消去，剩下的 $a$ 不能消去肯定不是最优的。

我们记录一个 `std::vector<std::tuple<char, char, int>>` 分别为消去的字符一，字符二，消去的数量。

这给了我们程序一个反悔的机会。

如果剩下的那一个字符与某一组的字符均不相同，则可以反悔这两个字符，分别与剩下的字符组合，如：

```
begin:
aa aa bb cc
treatment:
aa aa bc bc
repent:
ab ab ac ac
or
aa ab ac bc
```

即我们额外付出 $1$ 的代价，组合**最多** $2$ 个剩下的字符。

如果还有剩的，就去原序列里面找不相同的 $s_i \not= s_{n - i + 1}$，付出 $1$ 的代价，组合 $1$ 个剩下的字符。

如果还有，则无解。

### 代码实现

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <tuple>
#include <vector>
constexpr int MaxN = 2e5 + 5;
int n;
int same[128];
char s[MaxN];
std::vector<char> ch;
std::vector<std::tuple<char, char, int>> rm;
void solve()
{
    ch.clear();
    rm.clear();
    memset(same, 0, sizeof(same));
    scanf("%d", &n);
    scanf("%s", s + 1);
    if (n % 2 == 1)
    {
        printf("%d\n", -1);
        return;
    }
    for (int i = 'a'; i <= 'z'; i++)
    {
        ch.push_back(i);
    }
    for (int i = 1, j = n; i < j; i++, j--)
    {
        if (s[i] == s[j])
        {
            same[s[i]]++;
        }
    }
    int answer = 0;
    for (auto i : ch)
    {
        for (auto j : ch)
        {
            if (i == j)
            {
                continue;
            }
            int l = std::min(same[i], same[j]);
            if (l == 0)
            {
                continue;
            }
            answer += l;
            same[i] -= l;
            same[j] -= l;
            rm.push_back({i, j, l});
        }
    }
    int k = 0;
    char c = '\0';
    for (int i = 'a'; i <= 'z'; i++)
    {
        if (same[i] != 0)
        {
            c = i;
            k = same[i];
        }
    }
    for (auto x : rm)
    {
        int i, j, l;
        std::tie(i, j, l) = x;
        if (i != c && j != c)
        {
            l = std::min(k, l * 2);
            answer += (l + 1) / 2;
            k -= l;
        }
    }
    for (int i = 1, j = n; i < j; i++, j--)
    {
        if (s[i] != s[j] && s[i] != c && s[j] != c && k >= 1)
        {
            answer++;
            k--;
        }
    }
    printf("%d\n", k == 0 ? answer : -1);
}
int main()
{
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}
```

---

## 作者：Merge_all (赞：0)

### 思路：
- 无解情况：给出的**字符串的长度是奇数**或者字符串中某个字符**出现的次数比字符串长度的一半还多**。这样就可以直接输出 -1。
- 我们在字符串中每次判断 $s_{i}$ 和 $s_{n-i+1}$ 是否相同，定义 $ans$ 是指有多少个**位置上的字符是相同的**，$res$ 是指在要**调整的位置上出现最大的字符出现的次数**。
- 由于我们是把整个字符串扫了一遍，所以 $ans$ 和 $res$ 都要先除以 2，又因为我们**每次要交换两个字符**，所以说 $ans$ 还要除以 2。那么最后的答案就是 $\max(ans,res)$。
### 代码：
```
#include<bits/stdc++.h>

using namespace std;

const int N=200100;
#define PII pair<int,int>
#define fi first
#define se second

int T,n;
char s[N];
int Max_num,ans,res;
map<char,int> mp,sum;
bool vis[N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>s;
		if(n&1){
			cout<<"-1\n";
			continue;
		}
		mp.clear();
		sum.clear();
		Max_num=-0x3f3f3f3f;
		ans=0;
		res=0;
		for(int i=0;i<n;i++){
			sum[s[i]]++;
			Max_num=max(Max_num,sum[s[i]]);
		}
		if(Max_num*2>n){
			cout<<"-1\n";
			continue;
		}
		for(int i=0;i<n;i++){
//			cout<<s[i]<<" "<<s[n-i-1]<<"\n";
			if(s[i]==s[n-i-1]){
				mp[s[i]]++;
				ans++;
				res=max(res,mp[s[i]]);
			}
		}
//		cout<<ans<<" "<<res<<"\n";
		cout<<max(ceil(ans/4.00000*1.0000),res/2.00000*1.0000)<<"\n";
	}
	return 0;
}
```

---

## 作者：Walrus (赞：0)

# CF1822E

一道评分才 $1600$ 的题，不过还是挺考思维的。

## 题意

给你一个只包含小写字母并且长度为 $n$ 的字符串，定义若 $s_i = s_{n-i+1}$，则这个字符串不是“好回文串”。
你可以通过交换**任意两个字符，使得将这个字符串改为“好回文串”，即任何位置 $i$ 都满足 $s_i \neq s_{n-i+1}$**。

## 分析

观察性质可以发现，若长度 $n$ 为奇数，则当一定有 $s_i=s_{n-i+1}$。

所以得出一个结论：

- 若长度 $n$ 为奇数，则不管怎么修改都无法满足要求，故输出 `-1`。



思考交换后带来的利益。

假设当前有 $s$ 对字符不符合要求，我们理所应当交换这些不符合要求的字符对，考虑两两交换。

所以答案应该是 $\lceil \frac{s}{2} \rceil$。



但是这样交上去并不能通过，为什么呢？我们注意到，如果有某个字符的出现次数超过了 $\lceil \frac{n}{2} \rceil$，显然不可以满足要求，同样输出 `-1`。这给了我们启示，我们假设有某一个字符做为**不符合要求的字符对**的数量超过了 $\lceil \frac{s}{2}\rceil$，则我们需要将这些字符统统交换一次，假设这个字符作为**不符合要求的字符对**的数量有 $mx$ 个，则答案将会变成 $mx$。



综上所述，答案为 $\max(mx,\lceil \frac{s}{2} \rceil)$。


代码比较长，不过还是挺清晰的。


## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int anti[30], num[30], ans, n, _, mx;
char s[N];
bool flag;

void init() {
	memset(num, 0, sizeof num);
	memset(anti, 0, sizeof anti);
	memset(s, 0, sizeof s);
	ans = mx = 0, flag = 1;
}

void solve() {
	for(int i = 1; i <= n; i++)
		num[s[i] - 'a']++;
	for(int i = 1; i <= n / 2; i++)
		if(s[i] == s[n - i + 1])
			anti[s[i] - 'a']++;

	for(int i = 0; i < 26; i++) {
		if(num[i] > n / 2) {
			cout << -1 << '\n';
			flag = 0;
			break;
		}
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr), cout.tie(nullptr);

	cin >> _;
	while(_--) {
		init();
		cin >> n;
		cin >> (s + 1);
		if(n & 1)
			cout << -1 << '\n';
		else {
			solve();
			if(!flag)
				continue;
			
			int sum = 0;
			for(int i = 0;i < 26;i++)
				sum += anti[i], mx = max(mx, anti[i]);
			if(mx <= sum - mx)
				cout << (sum + 1 >> 1) << '\n';
			else
				cout << mx << '\n';
		}
	}
	return 0;
}
```



---

## 作者：cqbzhr (赞：0)

根据题目意思，可以很显然的得到输出 $-1$ 时的两个结论：
- 如果某个字母出现的次数大于 $n\div2$，那么，这个字符串一定不能得到反回文串
- 如果 $n$ 是奇数，那么，对于正中间的那一个字符，$s[i]=s[n-i+1]$ 一定恒成立，则也一定不能得到反回文串。

对于其他的情况，为了求得最少需要交换的次数，那么，一次将两个不合规的字符对调则是最优的解法。因此，我们可以统计，对于不同的字母，总共有多少对非法的字母对（因为相同字母的非法对的两个字母的交换是没有任何意义的，字母的交换需要在不同字母的情况下进行）。

若对于任意的字母 $c$，满足 $c$ 字母的非法对数总数 $\times 2 \le$ 总的非法对数。则此时，我们可以实现所有的非法对都相互两两交换的情况(除去奇数情况下的最后一对),则此时，答案为：非法对的总数 $\div2$ 向上取整。

若不满足这种条件，则说明这个最大的非法对数，除了需要和其他字母非法字母进行交换以外，还需要一些不非法的字母和他进行交换，则答案为这个最大的非法对数的个数。

## AC code
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,a[26],b[26],k,ma,mb;
string s;
bool f;
int main(){
	scanf("%d",&t);
	while(t--){
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		scanf("%d",&n);
		cin>>s;
		k=0,f=0,ma=0,mb=0;
		if(n&1){
			printf("-1\n");
			continue;
		}
		for(int i=0;i<n;i++)a[s[i]-'a']++;
		for(int i=0;i<26;i++)ma=max(ma,a[i]);
		if(n/2<ma){
			printf("-1\n");
			continue;
		}
		for(int i=0;i<n/2;i++){
			if(s[i]==s[n-i-1]){
				b[s[i]-'a']++;
				k++;
			}
		}
		for(int i=0;i<26;i++){
			if(k<b[i]*2)f=1;
			mb=max(mb,b[i]);
		}
		if(f)printf("%d\n",mb);
		else printf("%d\n",(k+1)/2);
	}
	return 0;
}
```
附：多测不清空，爆零两行泪

---

## 作者：LOvO (赞：0)

# CF1822E Making Anti-Palindromes 题解

## 题目大意：

给你一些字符串，对于每个字符串，你可以多次交换任意两个字母，问将该字符串变为”反回文串“的最小操作次数，若无解，输出 $-1$。

“反回文串”定义为：对于一个长度为 $n$ 的字符串 $s$，如果对于任意 $1\leqslant i\leqslant n$ 均有 $s_i\not=s_{n-i+1}$，那么字符串 $s$ 就叫做“反回文串”。

## 解题思路：

先思考无解的情况：

如果该字符串长度为奇数，设该字符串长度为 $n$，则第 $\left \lceil n/2\right \rceil $ 个，即字符串中间的那个字符，一定等于它本身，无解。

设该字符串长度为 $n$，如果该字符串里有一个字符的数量超过了 $n/2$ ，那么这个字符串就一定不能变成“反回文串”，无解。

除了这两种情况，该字符串就一定可以成为“反回文串”。

我们令 $s_i$ 和 $s_{n-i+1}$ 为一对字符对。

因为要求交换次数最少，所以每次我们要消除尽量多的相同的字符对。

由于每次我们可以交换两个字符，所以每次操作我们最多可以消除两对。

但是由于有可能有许多相同的字符对，而两个相同的字符对一次只能消除一个，所以我们要统计一下每个字符有几对相同的字符对。

设这个数量为 $p$，相同的字符对的数量为 $q$，综上所述，答案为 $max(p,\left \lceil q/2\right \rceil )$。

## Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int num[26], tot[26];
int solve() {
	memset(tot, 0, sizeof tot);
	memset(num, 0, sizeof num);
	int n, cur = 0;
	cin >> n >> s;
	if (n % 2 == 1) return -1;
	for (int i = 0; i < s.size(); i++)		//统计每个字符出现次数。
		tot[s[i] - 'a']++;
	for (int i = 0; i < 26; i++)
		if (tot[i] > n / 2)
			return -1;
	for(int i = 0, j = s.size() - 1; i <= j; i++, j--) {	//统计每个字符相同的字符对的数量。
		if(s[i] == s[j])
			num[s[i] - 'a']++, cur++;	//cur为相同的字符对的数量。
	}
	int maxx = 0;
	for (int i = 0; i < 26; i++)
		maxx = max(maxx, num[i]);
	return max(maxx, (cur % 2?1:0) + cur / 2);
}
int main() {
	int t;
	cin >> t;
	while (t--)
		cout << solve() << endl;
	return 0;
}
```



---

## 作者：jiangruibo (赞：0)

### 思路：
- 首先来讨论**无解**的，明显可知，若字符串的**长度为奇数**或**某个字符出现的次数比字符串长度的一半还多**则为无解，输出 -1 即可。
- 然后我们去遍历每一个位置，判断 $S_{i}$ 与 $S_{n-i+1}$ 是否相同，统计一下得到 $cnt$。
- 最后再找到字符出现最多的字符的个数，输出 $\max(cnt,ans)$ 即可。

### 代码
```
#include <bits/stdc++.h>
#define int long long
using namespace std;

map<char,int> mp;
map<char,int> mp1;
map<char,int> mp2;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		mp.clear();
		int n;
		cin>>n;
		string s;
		cin>>s;
		if(n%2==1)
		{
			cout<<"-1"<<endl;
			continue;
		}
		for(int i=0;i<=n-1;i++)
		{
			mp[s[i]]++;
		}
		bool flag=false;
		for(int i=1;i<=26;i++)
		{
			if(mp[char(i+'a'-1)]*2>n)
			{
//				cout<<char(i+'a'-1)<<" ";
				cout<<"-1"<<endl;
				flag=true;
				break;
			}
		}
		if(flag==true)
		{
			continue;
		}
		mp1.clear();
		int cnt1=0;
		int maxn=-1e9;
		for(int i=1;i<=n;i++)
		{
			if(s[i-1]==s[n-i])
			{
				mp1[s[i-1]]++;
				maxn=max(maxn,mp1[s[i-1]]);
				cnt1++;
			}
		}
		cout<<max(ceil(1.0*cnt1/2/2),1.0*maxn/2)<<endl;
			
	}
	return 0;
}
/*
*/

```

---

