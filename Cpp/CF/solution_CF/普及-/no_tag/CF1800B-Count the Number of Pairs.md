# Count the Number of Pairs

## 题目描述

Kristina has a string $ s $ of length $ n $ , consisting only of lowercase and uppercase Latin letters. For each pair of lowercase letter and its matching uppercase letter, Kristina can get $ 1 $ burl. However, pairs of characters cannot overlap, so each character can only be in one pair.

For example, if she has the string $ s $ = "aAaaBACacbE", she can get a burl for the following character pairs:

- $ s_1 $ = "a" and $ s_2 $ = "A"
- $ s_4 $ = "a" and $ s_6 $ = "A"
- $ s_5 $ = "B" and $ s_{10} $ = "b"
- $ s_7 $ = "C" and $ s_9 $ = "c"

Kristina wants to get more burles for her string, so she is going to perform no more than $ k $ operations on it. In one operation, she can:

- either select the lowercase character $ s_i $ ( $ 1 \le i \le n $ ) and make it uppercase.
- or select uppercase character $ s_i $ ( $ 1 \le i \le n $ ) and make it lowercase.

For example, when $ k $ = 2 and $ s $ = "aAaaBACacbE" it can perform one operation: choose $ s_3 $ = "a" and make it uppercase. Then she will get another pair of $ s_3 $ = "A" and $ s_8 $ = "a"

Find maximum number of burles Kristina can get for her string.

## 说明/提示

The first test case is explained in the problem statement.

In the second test case, it is not possible to get any pair by performing any number of operations.

## 样例 #1

### 输入

```
5
11 2
aAaaBACacbE
2 2
ab
4 1
aaBB
6 0
abBAcC
5 3
cbccb```

### 输出

```
5
0
1
3
2```

# 题解

## 作者：zajasi (赞：4)

## 题意
给你一个字符串。一个大写字母和一个小写字母配一对（例如 `a` 和 `A` 算一对，但 `a` 和 `B` 不算）。你每一次可以将任意一个字母小写改成大写或大写改成小写，最多改 $k$ 次。问最多能配多少对。
## 解题思路
首先，先把能配的都配了再说。

然后，贪心的想，看看把大小写更改能在配几对。$k$ 能用完就用完，不能用完也要用到不能配为止。

上代码。
## AC 代码
```cpp
/*
written by : zjs123
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long  
int n,k;
string a;
int t;
int c[27],d[27];
main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n>>k>>a;
        for(int i=1;i<=26;i++){
            c[i]=d[i]=0;
        }
        for(int i=0;i<n;i++){
            if(a[i]>='A'&&a[i]<='Z'){
                c[a[i]-'A'+1]++;
            }
            else{
                d[a[i]-'a'+1]++;
            }//统计大小写个数
        }
        int z=0;
        for(int i=1;i<=26;i++){
            int x=min(c[i],d[i]);
//            cout<<c[i]<<" "<<d[i]<<"\n";
            z+=x;
            c[i]-=x;
            d[i]-=x;
            //先把能配的配了
            if(k>=(c[i]+d[i])/2){
                z+=(c[i]+d[i])/2;
                k-=(c[i]+d[i])/2;
            }
            else{
                z+=k;
                k=0;
            }//贪心，能配多少配多少
        }
        cout<<z<<"\n";
    }
    return 0;
}

```


---

## 作者：Rainsleep (赞：1)

## 题意

给定一个仅有大小写字母组成的长度为 $n$ 的字符串 $s$，可以进行 $k$ 次操作，可以将大写字母变为小写字母，或将小写字母变为大写字母，请求出使用不超过 $k$ 次操作所能获得的最多大小写字母对的数量。

## $\text{Solution}$

考虑维护一个桶，记录每个大写/小写字母出现的次数，首先统计无需操作就能配对的大小写字母对的数量，那么每个字母最后的数量一定是
+ **大写用完，小写富余**。
+ **大写富余，小写用完**。

中的其中一种，那么发现如果在其基础上，通过操作构造新的大小写字母对，一定是其中较大值数量 $ -1$，较小值数量 $+1$，每次差值减小 $2$，当二者差值 $<2$ 时则无法再操作了，设 $maxx$ 为二者较大值，那么总共操作次数最多为 $\left \lfloor \dfrac{maxx}{2} \right \rfloor \div 1$，统计这样的待操作数量，最后由于操作数量可能不够用，记得跟 $k$ 取 $\min$。

代码：
```cpp
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>

using namespace std;

int T, n, k;
char s[200010];
int bin[60];

int main()
{
	scanf("%d", &T);
	while(T -- )
	{
		memset(bin, 0, sizeof bin);
		scanf("%d %d", &n, &k);
		scanf("%s", s + 1);
		for(int i(1);i <= n; ++ i)
			if(islower(s[i]))
				bin[s[i] - 'a'] ++ ;
			else if(isupper(s[i]))
				bin[s[i] - 'A' + 26] ++ ;
		int res = 0, wait = 0;
		for(int i(0);i < 26; ++ i)
		{
			int t = min(bin[i], bin[i + 26]);
			res += t, bin[i] -= t, bin[i + 26] -= t;
			if(bin[i] or bin[i + 26])
				wait += (max(bin[i], bin[i + 26]) >> 1);
		}
		res += min(wait, k);
		printf("%d\n", res);
	}
	return 0;
} 
```

---

## 作者：LegendaryGrandmaster (赞：1)

统计每个字母出现的次数，大小写配对的字母中最小出现数的数量都可以变成一组。

剩余的折半取整配对，如果没有 $k$ 小则取 $k$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
map<char,int>mp;
void slove()
{
	mp.clear();
	int n,k;
	string st;
	cin>>n>>k>>st;
	for(int i=0;i<st.size();i++)mp[st[i]]++;
	int ans=0;
	for(char i='A';i<='Z';i++){
		int a1=mp[i],a2=mp[char(i+32)];
		ans+=min(a1,a2);
		mp[i]-=min(a1,a2);
		mp[char(i+32)]-=min(a1,a2);
	}
	for(char i='A';i<='Z';i++){
		int a1=mp[i],a2=mp[char(i+32)];
		int c=abs(a1-a2)/2;
		if(k)ans+=min(k,c),k=max(0,k-c);
	}
	cout<<ans<<'\n';
}
int main()
{
	int t;
	cin>>t;
	while(t--)slove();
} 
```

---

## 作者：Larryyu (赞：1)

## _Description_
给定 $n$，$k$，长度为 $n$ 的字符串 $s$。

一个大写的字母和一个小写格式的该字母可以合并，合并后消失，且分值加一。

一次操作定义为将一个字母改变其大小写格式（大写转小写，小写转大写）。

求在不超过 $k$ 次操作后，该字符串的分值的最大值。

共 $t$ 组数据。

## _Solution_
设 $a_1,a_2$ 表示字母 ```a``` 的大小写数量。

为了让分值最大，所以要让大小写数量之差越小，这样才能使能合并的对数越多。

一种字母最多能有 $\lfloor(a_1+a_2)\div 2\rfloor$ 对大小写能合并，而达到这个数量需要 $add=\lfloor(a_1+a_2)\div 2\rfloor-\min(a_1,a_2)$（操作后的对数减去原来就有的对数就是操作中改动的对数）次操作。将二十六种字母的 $add$ 加起来，与 $k$ 取较小值（这就是在不超过操作 $k$ 次能增加的对数）加上原来就有的对数（$\min(a_1,a_2)+\min(b_1,b_2)+\dots+\min(z_1,z_2)$），这就是最终答案。

## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int t;
int a[30],b[30];
ll read(){
    ll x=0,f=1;
    char ch;
    ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void solve(){
	int n=read(),k=read(),ans=0;
	string s;
	cin>>s;
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	for(int i=0;i<n;i++){
		if(s[i]<='z'&&s[i]>='a') a[s[i]-'a'+1]++;
		else if(s[i]>='A'&&s[i]<='Z') b[s[i]-'A'+1]++;
	}
	for(int i=1;i<=26;i++){
		ans+=min(a[i],b[i]);//操作前就有的分值
		ans+=min(abs(a[i]-b[i])/2,k);//操作后增加的分值
		k-=min(abs(a[i]-b[i])/2,k);//减去该字母耗费的操作数
	}
	cout<<ans<<endl;
}
int main(){
	t=read();
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：ダ月 (赞：0)

### 题意概要：

给定 $n$ 个由大小写字符构成的字符串，最多进行 $k$ 次以下操作：将其中一个字符由大写转小写或小写转大写。记一个小写字母与其对应的大写字母为一组配对，问最多操作 $k$ 次，可以存在多少组配对。

### 题目分析：

我们先记录每种字符出现的次数。对于一个小写字母出现 $x$ 次，其对应大写字母 $y$ 次，显然无限次操作，会有 $\left\lfloor\frac{x+y}{2}\right\rfloor$ 个，此时最少操作了 $\left\lfloor\frac{|x-y|}{2}\right\rfloor$ 次。

我们记录在未操作之前能有多少组配对 $a$，然后记录假使任意次操作，让整个序列能达到最多配对数的最少操作 $b$，答案就是 $a+\min\{b,k\}$。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int T;
int n,m;
const int N=2e5+10;
char c[N];
int tot[128];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%s",&n,&m,c+1);
		memset(tot,0,sizeof(tot));
		for(int i=1;i<=n;i++)
			tot[int(c[i])]++;
		int sum=0,k=0;
		for(int i='a';i<='z';i++)
			sum+=abs(tot[i]-tot[i-'a'+'A'])/2,
			k+=min(tot[i],tot[i-'a'+'A']);
		printf("%d\n",k+min(sum,m));
	}return 0;
}
```

时间复杂度：$O(n)$。


---

## 作者：ztrztr (赞：0)

在 <https://ztrztr.top/archives/242> 食用更佳。

又是一道水题……
## 题意
给出一个字符串，你改变把 $k$ 个字符使得大写的变为小写，小写变为大写。求有多少对字符使得第一个字符是第二个的大写形式或小写形式。
## 思路
1. 进行统计，统计每个字符的大小写各有多少个。
2. 进行初步计算 $\text{ans} + \min\{\text{ch1, ch2}\}$。
3. 再次计算改变 $k$ 个字符的大小写形式后的数值，具体见代码。
4. 开心输出。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T --) {
        int ch1[205] = {0}, ch2[205] = {0}, ans = 0;
        int n, k, use = 0;
        cin >> n >> k;
        for (int i = 1; i <= n; i ++) {
            char ch; cin >> ch;
            if (ch >= 'A' and ch <= 'Z') ch1[ch - 65] ++;
            else ch2[ch - 97] ++;
            // cout << ch << " " << ch - 65 << " " << ch - 97 << "\n";
        }
        for (int i = 0; i <= 30; i ++) {
            // cout << ch1[i] << " " << ch2[i] << "\n";
            ans += (min(ch1[i], ch2[i]));
            int f = ch1[i], s = ch2[i];
            if (use < k) {
                int tem = max(f, s) - min(f, s);
                int can = tem / 2;
                if (use + can <= k) {
                    use += can;
                    ans += can;
                } else {
                    ans += k - use;
                    use = k;
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
```


---

## 作者：RandomLife (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1800B)

## 题意

有一个字符串，长度为 $n(1 \leq n \leq 2 \cdot 10^5)$，其中只包含大写字母和小写字母。如果可以匹配到类似的大写字母和小写字母（例如："a" 和 "A" 是类似的，但 "a" 和 "a" 或 "A" 和 "b" 就不类似。）称为一对。

现在你有 $k(0 \leq k \leq n)$ 次修改字符串的机会，但你的修改只能将小写字母变成大写字母，或将大写字母变为小写字母。（例如：从 "a" 修改成 "A"，从 "A" 修改成 "a"。）

问：修改后最多会有几对。

## Solution

可以先统计字符串每个字符出现的次数。

显然，对于已经成为一对的，我们无需进行修改，只需累加至答案即可。

对于剩下的，取出任意两个相同的字符，只需要将其中一个字符改为大写或小写就可以使这两个配对，因此统计两个同字符的对数累加至答案即可。当然，由于我们最多只能修改 $k$ 次，因此还需要修改次数与 $k$ 取最小值。

## AC code

```c++
#include <iostream>
#include <algorithm>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <string.h>
#include <vector>
#include <math.h>
#include <stdio.h>
using namespace std;
const int N = 200010;
int T, n, k, ans, d, cnt[256];
string str;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> T;
    while (T--) {
        memset(cnt, 0, sizeof cnt);
        ans = 0, d = 0;
        cin >> n >> k >> str;
        for (int i = 0; i < str.size(); ++i) {
            cnt[str[i]]++;
        }
        for (int i = 0; i < 26; ++i) {
            int a = i + 'a', b = i + 'A', p = min(cnt[a], cnt[b]);
            cnt[a] -= p, cnt[b] -= p, ans += p;
        }
        for (int i = 0; i < 26; ++i) {
            int a = i + 'a', b = i + 'A', p = cnt[a] / 2, q = cnt[b] / 2;
            d += p, d += q;
        }
        ans += min(d, k);
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：_5t0_0r2_ (赞：0)

# 分析：
这是一道标准模拟题。

首先，统计出所有字母的个数。

```cpp
cin >> n >> k >> s;
int A[26],a[26];//A存大写字母的个数，a存小写字母的个数。
for(int i = 0;i < n;i++){
   if(s[i] >= 'A' && s[i] <= 'Z')//大写字母
       A[s[i] - 'A']++;
   else //小写字母
       a[s[i] - 'a']++;
}
```

接下来，如果字母不改变的话，那么答案就是
$$ \sum_{i = 1}^{26} \min(A_i,a_i) $$

组合好后，这些字母就会被去掉。

```cpp
for(int i = 0;i < 26;i++){//枚举不同字母
    if(A[i] > a[i]){//大写字母多
        ans += a[i];
        A[i] -= a[i];
        a[i] = 0;
    }
    else{//小写字母多
        ans += A[i];
        a[i] -= A[i];
        A[i] = 0;
    }
}
```
然后，我们就会对剩下的字母进行大小写转换。明确一个前提：当一个字母至少有两个才能转换，否则只有一个字母转换了没意义。

每转换一个字母，就会去掉两个字母，并将 $k$ 减 $1$ 。

```cpp
for(int i = 0;i < 26;i++){//枚举不同字母
    if(a[i] == 0){
        if(A[i] / 2 <= k){
            ans += A[i] / 2;
            k -= A[i] / 2;
        }
        else{
            ans += k;
            break;
        }
    }
    else{
        if(a[i] / 2 <= k){
            ans += a[i] / 2;
            k -= a[i] / 2;
        }
        else{
            ans += k;
            break;
        }
    }
}
```

# 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, k, a[26], A[26], ans;
string s;
int main() {
	cin >> t;
	for (int x = 1; x <= t; x++) {
		memset(a, 0, sizeof a);
		memset(A, 0, sizeof A);
		ans = 0;
		cin >> n >> k >> s;
		for (int i = 0; i < n; i++) {
			if (s[i] >= 'A' && s[i] <= 'Z')
				A[s[i] - 'A']++;
			else
				a[s[i] - 'a']++;
		}
		for(int i = 0;i < 26;i++){
		    if(A[i] > a[i]){
		        ans += a[i];
		        A[i] -= a[i];
		        a[i] = 0;
		    }
		    else{//?????
		        ans += A[i];
		        a[i] -= A[i];
		        A[i] = 0;
		    }
		}
		for(int i = 0;i < 26;i++){
		    if(a[i] == 0){
		        if(A[i] / 2 <= k){
		            ans += A[i] / 2;
		            k -= A[i] / 2;
		        }
		        else{
		            ans += k;
		            break;
		        }
		    }
		    else{
		        if(a[i] / 2 <= k){
		            ans += a[i] / 2;
		            k -= a[i] / 2;
		        }
		        else{
		            ans += k;
		            break;
		        }
		    }
		}
		cout << ans << endl;
	}
}
```


---

## 作者：zfx_VeXl6 (赞：0)

首先，我们没必要把所有次数都用完。

如果是已经配好对的字母，就不用管了，累计答案。统计每个字母（区分大小写）的数量。如果有种字母大小写的数量都大于 $0$，那么对于这种字母，已配好的对就是大小写中较少的那个的数量。这个过程不使用操作。

接着如果这种字母除掉配好对的字母后大小写的数量有一个还大于 $0$，那么就可以通过操作使得一个大写字母变成小写字母或反之，从而形成新的配对。形成新配对的数量最多是这个字母的数量除以 $2$ 向下取整。但是每形成一个新配对就会消耗一次操作，所以需要判断。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,ans,c[129];
string s;
int main()
{
    cin>>t;
    while(t--)
    {
        ans=0;
        memset(c,0,sizeof(c));
        cin>>n>>k>>s;
        for(int i=0;i<n;i++)
            c[s[i]]++;
        for(int i=0;i<26;i++)
        {
            int tt=min(c[i+'A'],c[i+'a']);
            ans+=tt;
            c[i+'A']-=tt;
            c[i+'a']-=tt;
            tt=max(c[i+'A'],c[i+'a'])/2;
            if(tt<=k)
            {
                ans+=tt;
                k-=tt;
            }
            else
            {
                ans+=k;
                k=0;
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：minVan (赞：0)

**题目大意**

有一个由大小写字母组成的字符串 $s$，你有 $k$ 次机会，如果 $s_i$ 是小写字母，则 $s_i$ 可以变成大写字母；如果 $s_i$ 是大写字母，则 $s_i$ 可以变成小写字母，问最多有多少对 `(i + 'a', i + 'A')`。

**解题思路**

用一个 `map` 来标记每个字母，然后遍历 $1\dots26$，先把不用 $k$ 次机会的 `(i + 'a', i + 'A')` 去掉，然后再把多余的 `i + 'a'` 或 `i + 'A'` 两两配对，和剩下 $k$ 次机会比大小即可。

**标记部分代码**

```cpp
for(int i = 0; i < s.size(); i++) {
   mp[s[i]]++;
}
```

**$1\dots26$ 遍历部分代码**

```cpp
for(int i = 0; i < 26; i++) {
	if(mp[i + 'a'] || mp[i + 'A']) {
		ans += min(mp[i + 'a'], mp[i + 'A']);
		int tmp = abs(mp[i + 'a'] - mp[i + 'A']);
		if(k > 0) {
			int tmp2 = min(k, tmp / 2);
			k -= tmp2;
			k = max(k, 0);
			ans += tmp2;
		}
   }
}
```

**AC 代码，请勿抄袭**

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    cin >> t;
    while(t--) {
        map<char, int> mp;
        int n, k, ans = 0;
        string s;
        cin >> n >> k >> s;
        for(int i = 0; i < s.size(); i++) {
            mp[s[i]]++;
        }
        for(int i = 0; i < 26; i++) {
            if(mp[i + 'a'] || mp[i + 'A']) {
                ans += min(mp[i + 'a'], mp[i + 'A']);
                int tmp = abs(mp[i + 'a'] - mp[i + 'A']);
                if(k > 0) {
                    int tmp2 = min(k, tmp / 2);
                    k -= tmp2;
                    k = max(k, 0);
                    ans += tmp2;
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
```

---

