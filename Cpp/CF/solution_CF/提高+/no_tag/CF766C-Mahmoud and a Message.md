# Mahmoud and a Message

## 题目描述

Mahmoud wrote a message $ s $ of length $ n $ . He wants to send it as a birthday present to his friend Moaz who likes strings. He wrote it on a magical paper but he was surprised because some characters disappeared while writing the string. That's because this magical paper doesn't allow character number $ i $ in the English alphabet to be written on it in a string of length more than $ a_{i} $ . For example, if $ a_{1}=2 $ he can't write character 'a' on this paper in a string of length $ 3 $ or more. String "aa" is allowed while string "aaa" is not.

Mahmoud decided to split the message into some non-empty substrings so that he can write every substring on an independent magical paper and fulfill the condition. The sum of their lengths should be $ n $ and they shouldn't overlap. For example, if $ a_{1}=2 $ and he wants to send string "aaa", he can split it into "a" and "aa" and use $ 2 $ magical papers, or into "a", "a" and "a" and use $ 3 $ magical papers. He can't split it into "aa" and "aa" because the sum of their lengths is greater than $ n $ . He can split the message into single string if it fulfills the conditions.

A substring of string $ s $ is a string that consists of some consecutive characters from string $ s $ , strings "ab", "abc" and "b" are substrings of string "abc", while strings "acb" and "ac" are not. Any string is a substring of itself.

While Mahmoud was thinking of how to split the message, Ehab told him that there are many ways to split it. After that Mahmoud asked you three questions:

- How many ways are there to split the string into substrings such that every substring fulfills the condition of the magical paper, the sum of their lengths is $ n $ and they don't overlap? Compute the answer modulo $ 10^{9}+7 $ .
- What is the maximum length of a substring that can appear in some valid splitting?
- What is the minimum number of substrings the message can be spit in?

Two ways are considered different, if the sets of split positions differ. For example, splitting "aa|a" and "a|aa" are considered different splittings of message "aaa".

## 说明/提示

In the first example the three ways to split the message are:

- a|a|b
- aa|b
- a|ab

The longest substrings are "aa" and "ab" of length $ 2 $ .

The minimum number of substrings is $ 2 $ in "a|ab" or "aa|b".

Notice that "aab" is not a possible splitting because the letter 'a' appears in a substring of length $ 3 $ , while $ a_{1}=2 $ .

## 样例 #1

### 输入

```
3
aab
2 3 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
```

### 输出

```
3
2
2
```

## 样例 #2

### 输入

```
10
abcdeabcde
5 5 5 5 4 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
```

### 输出

```
401
4
3
```

# 题解

## 作者：harada (赞：2)

给你一个小写字符串str和26个整数a[i]，是用来限制$每个字母所在分割字符串的最大长度$（字母i所在的字符串不能超过a[i]）

输出分割字符串的方案数。
输出所有方案中，最少的分割次数。
输出所有方案中，最大的子串长度。

dp[i][0] 表示前i个字母正确分割的数量
dp[i][1] 表示前i个字母正确分割且数量最少
dp[i][1] 表示前i个字母正确分割且最大子串的长度最大


dp[i][0] = dp[i][1] + dp[j - 1][0] 
dp[i][1] = min(dp[i][1], dp[j - 1] + 1)
dp[i][2] = max(dp[i][2], max(i - j + 1, dp[j - 1][2]))

其中j为(1<= j <= i 且是正确的分割长度)

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1005;
const int mod = 1e9 + 7;
const int inf = 1e9;
 //0：正确分割数量
 //1：正确分割次数最少数量
 //2：正确分割字符串最长
int dp[maxn][3];
int a[maxn];
char str[maxn];
int main() {
	int n;
	cin >> n;
	cin >> str + 1;
	for (int i = 0; i < 26; i++) {
		cin >> a[i];
	}
	for (int i = 0; i <= n; i++) {
		dp[i][0] = 0;
		dp[i][1] = inf;
		dp[i][2] = 0;
	}
	dp[0][0] = 1; dp[0][1] = 0; dp[0][2] = 0;
	for (int i = 1; i <= n; i++) {
		 int len=a[str[i]-'a'];
		for (int j = i; j >= 1; j--) {
			len=min(len,a[str[j]-'a']);
			if(i - j + 1 > len) { //字母长度限制
				break;
			}
			dp[i][0] = (dp[i][0] + dp[j - 1][0]) % mod;
			dp[i][1] = min(dp[i][1], dp[j - 1][1] + 1);
			dp[i][2] = max(dp[i][2], max(i - j + 1, dp[j - 1][2]));
		}
	}
	cout << dp[n][0] << endl;
	cout << dp[n][2] << endl;
	cout << dp[n][1] << endl;
	return 0;
}
````

---

## 作者：ZLCT (赞：0)

# CF766C Mahmoud and a Message
## 题目翻译
给定一个长度为 $n$ 只包含小写字母的字符串 $s$，再给定每个字符对应的权值 $a_i$，要把字符串分割成若干子串，要求对于所有 $i$ 都满足 $len_i\le a_{s_i}$（$len_i$ 表示 $i$ 所在子串的长度）。\
要求分别输出有多少种分割方式，分割后最长子串长度，最少分割次数。
## 加量不加题
因为题目所求大致是相互割裂的，所以下面我们分三部分解决。
### NO.1
如何输出方案数呢？注意到 $n\le 10^3$，于是这启示我们可以 $n^2$ 的做法。\
我们考虑 dp，设 $f_i$ 表示前 $i$ 个字符并且全部都被分成若干子串（保证无后效性）。我们枚举从何处转移，也就是 $i$ 所在子串的左端点，如果合法则可以有 $f_i+=f_{j-1}$ 的转移。\
接下来我们就要解决本题的重点：如何判断 $j-i$ 作为一个子串是否合法。\
首先暴力的想法十分明显，就是枚举区间的每个元素并判断 $a_{s_k}$ 是否大于等于 $i-j+1$（区间长度）。\
但是这样明显复杂度是 $O(n)$ 的，加上外层 $O(n^2)$ 循环，时间复杂度 $O(n^3)$ 肯定不行。\
我们发现 $i-j+1$ 的值是不变的，所以我们只要判断 $\min\{a_{s_k}\}$ 是否大于等于 $i-j+1$ 即可。\
于是我们考虑优化。\
首先第一种思路，考虑优化枚举次数：我们既然对于 $k$ 的枚举是 $j-i$ 的且所有值不会变，于是我们可以倒序枚举 $j$，并记录 $minn$ 表示已枚举的 $a_{s_k}$ 的最小值。由于从大到小枚举 $j$ 会使前面枚举的值在后面都能用到，所以这样每次只需要枚举当前元素并用 $minn$ 判断即可，复杂度 $O(n^2)$。\
第二种思路，考虑优化枚举速度：考虑到我们要求区间最小值，很自然想到可以用线段树和 st 表维护，这样复杂度分别为 $O(n^2\log{n})$ 和 $O(n^2)$。
### NO.2
对于是否合法的情况，我们还是和上面处理一样，唯一就是考虑如何记录答案。\
这一问应该是最好想的，我们只需要枚举每一个区间并判断是否合法并取最长即可。\
为什么这样取一定能保证分割合法呢？这个很好办，因为不需要保证分割总次数最少，所以只需要将其他字符都单独成区间，这样一定合法。
### NO.3
这一问有了第一问的经验，我们继续考虑 dp。\
设 $g_i$ 表示前 $i$ 个字符并且全部被分成若干子串。和第一问一样枚举左端点判断能否转移，至于转移方程也十分简单，就是取所有合法转移所需分割次数最小的即可。形式化来说就是 $g_i=\min(g_i,g_{j-1}+1)$。
## code
这里给出相对难写的线段树版本，虽然复杂度多一个 $\log$，但是思考过程较为直观。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,a[33],b[1123];
string s;
int f[1123];
int g[1123];
int maxx;
struct segment{
    int l,r,minn;
}tr[11234];
void pushup(int u){
    tr[u].minn=min(tr[u<<1].minn,tr[u<<1|1].minn);
}
void build(int u,int l,int r){
    tr[u].l=l;tr[u].r=r;
    if(l==r){
        tr[u].minn=b[l];
        return;
    }
    int mid=(l+r)>>1;
    build(u<<1,l,mid);
    build(u<<1|1,mid+1,r);
    pushup(u);
}
int query(int u,int x,int y){
    if(tr[u].l>=x&&tr[u].r<=y){
        return tr[u].minn;
    }
    int res=0x3f3f3f3f;
    if(tr[u<<1].r>=x){
        res=min(res,query(u<<1,x,y));
    }
    if(tr[u<<1|1].l<=y){
        res=min(res,query(u<<1|1,x,y));
    }
    return res;
}
signed main(){
    cin>>n>>s;
    memset(g,0x3f3f3f3f,sizeof(g));
    for(int i=0;i<26;++i){
        cin>>a[i];
    }
    for(int i=1;i<=n;++i){
        b[i]=a[s[i-1]-'a'];
    }
    build(1,1,n);
    for(int i=1;i<=n;++i){
        for(int j=i;j>=1;--j){
            if(j==1){
                if(query(1,1,i)>=i){
                    f[i]++;
                    g[i]=1;
                    maxx=max(maxx,i-j+1);
                }
            }
            else if(i-j+1<=query(1,j,i)){
                f[i]+=f[j-1];
                f[i]%=mod;
                g[i]=min(g[i],g[j-1]+1);
                maxx=max(maxx,i-j+1);
            }
        }
    }
    cout<<f[n]%mod<<'\n'<<maxx<<'\n'<<g[n]<<'\n';
    return 0;
}
```

---

