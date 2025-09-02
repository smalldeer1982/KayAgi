# [GCJ 2013 #1C] Consonants

## 题目描述

在英文中，$26$ 个字母被划分为**元音字母**和**辅音字母**。在本题中，a、e、i、o、u 被视为元音字母，其余 $21$ 个字母均为辅音字母。

居住在 Greatest Colorful Jungle 的一个部落有一个传统：部落成员的名字都由英文字母组成。但为新成员起一个好名字并不容易，因为名字反映了成员在部落中的社会地位。人们认为，名字越少见，地位就越高。

部落首领是一位专业的语言学家。他注意到，难以发音的名字通常较为罕见，而造成发音困难的原因在于名字中**连续辅音字母**过多。因此，他宣布，部落成员的社会地位由其 n-值决定。n-值定义为：名字中包含至少 $n$ 个连续辅音字母的子串的数量。例如，当 $n = 3$ 时，名字 "quartz" 的 n-值为 $4$，因为子串 quartz、uartz、artz 和 rtz 都包含至少 $3$ 个连续辅音字母。n-值越大，社会地位越高。两个子串只要起始或结束位置不同，就被视为不同（即使内容相同），例如 "tsetse" 包含 $11$ 个拥有两个连续辅音字母的子串，尽管其中有些子串（如 "tsetse" 和 "tsetse"）内容相同。

所有部落成员的名字及 $n$ 都由首领指定。虽然首领是语言学家，能够保证名字有意义，但他并不擅长计算 n-值。请你帮助首领确定每个名字的 n-值。注意，不同的名字可能对应不同的 $n$。


## 说明/提示

**限制条件**

- $1 \leqslant T \leqslant 100$
- $0 < n \leqslant L$

**小数据集（8 分，测试集 1 - 可见）**

- $1 \leqslant L \leqslant 100$

**大数据集（20 分，测试集 2 - 隐藏）**

- $1 \leqslant L \leqslant 10^6$
- 输入文件大小不超过 6MB

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
4
quartz 3
straight 3
gcj 2
tsetse 2```

### 输出

```
Case #1: 4
Case #2: 11
Case #3: 3
Case #4: 11```

# 题解

## 作者：linhanmo (赞：2)

# 题解：[P13291 [GCJ 2013 #1C] Consonants](https://www.luogu.com.cn/problem/P13291)

## 暴力

枚举区间 $[l,r]$，枚举 $r$ 时顺便计算是否超过 $n$ 个。

时间复杂度 $O(t\cdot L^2)$，不能通过。

## 正解

我们发现每次达到 $n$ 个时，扩大 $r$ 肯定也会满足。

所以只要维护两个下标即可，时间复杂度 $O(t\cdot L)$。

### [AC](https://www.luogu.com.cn/record/225639888) code

```cpp
#include <iostream>
using namespace std;
int t, n; string s; long long ans;
#define cons(c) ((c) != 'a' && (c) != 'e' && (c) != 'i' && (c) != 'o' && (c) != 'u')
int main(void) {
	cin.tie(nullptr) -> sync_with_stdio(false), cin >> t;
	for (int cs = 1; cs <= t; ++cs, ans = 0) {
        cin >> s >> n;
        for (int len = 0, l = -1, i = 0; i < s.length(); ++i) {
            if (cons(s[i])) { if (++len >= n) l = i - n + 1; }
		    else len = 0;
            if (l != -1) ans += l + 1;
        } cout << "Case #" << cs << ": " << ans << endl;
	}
    return 0;
}
```

---

## 作者：Circle_Table (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P13291)

简单说一下题意：求给定字符串中辅音字母数量不少于 $n$ 的子串个数。注意是多测。\
看完题目后我想都没想就写出了判定辅音的函数。接下来思考提议的实现方法。

现在的题解中似乎没人仔细说明实现的细节，但其实我是想了很久才想出来的。所以来仔细讲讲。

为了表述方便，我们定义最短辅音子串为原字符串中恰有 $n$ 个辅音字母的子串。\
当出现一个最短辅音子串后，那么在它前面的每一个元素到该子串最后一个元素所组成的子串也符合条件。见下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/mhct0uh2.png)

在此图中可以看出，当 $n=3$ 时，只要满足了连续三个字母是辅音字母，那么这一个子串的左端是几，答案就应该加上几。\
这个子串右端为第 $i$ 个，因此左端的左边一个为第 $i-n$ 个，左端就是 $l=i-n+1$ 了。

但是我们仅仅考虑向左。向右的话，还是上图，当我们遍历到 $i=6$ 时，再往左边看，实际上就是在原先的最短辅音子串的右边加上一个字母罢了。因此再加上一个 $i-n+1$ 即可。\
证明这种计算方法能够做到不重不漏。首先，由于每一个点都只向左寻找符合条件的子串，所以每到一个新点得到的子串就全部不同，因此做到了不重；而根据排列组合，我们确实考虑到了每一个可能的子串，不可能遗漏。

想清楚这些此题答案也就呼之欲出了。其他小细节见注释。

## 代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register int
#define ios ios::sync_with_stdio,cin.tie(0),cout.tie(0)
using namespace std;
const int N=1e6+5;
const char ch[5]={'a','e','i','o','u'};
char s[N];
int T,n,sum[N];
bool isfuyin(char c)//判断辅音的函数 
{
	for(ri i=0;i<5;i++)
		if(c==ch[i])return 0;
	return 1;
}
signed main()
{
	scanf("%d",&T);
	for(ri qwq=1;qwq<=T;qwq++)
	{
		scanf("%s %d",s+1,&n);
		memset(sum,0,sizeof(sum));//多测清空
		int len=strlen(s+1);
		ll ans=0,ans1=0;
		
		//预处理前缀和：求截止到a[i]连续有几个辅音字母
		for(ri i=1;i<=len;i++)
			if(isfuyin(s[i]))sum[i]=sum[i-1]+1;
			//否则sum[i]=0 (见前文memset)
		
		//求值 
		for(ri i=n;i<=len;i++)//从n开始：n以前绝不会有满n个的子串 
		{
			if(sum[i]>=n)ans1=i-n+1;
			ans+=ans1;
		}
		printf("Case #%d: %lld\n",qwq,ans);
	}
	return 0;
}
```

感谢阅读！

---

## 作者：liketaem (赞：0)

# 题目解释
这是一道~~看似黄题，实则是黄题~~的字符串相关的题目。
# 思路
### 1. 寻找满足要求的字符串
遍历字符串，找到所有长度至少为 $n$ 的连续辅音字母段。对于每个这样的段，记录其起始和结束位置。
### 2. 计算有效子串
对于每个长度为m的连续辅音段 $(m \ge n)$，计算包含至少 $n$ 个连续辅音字母的子串数量。具体来说，假设这个连续辅音段从位置 $i$ 到 $j$（共 $m$ 个字符），那么在这个段中，有效的子串必须包含至少 $n$ 个连续的辅音字母。这些子串的起始位置可以在 $i$ 之前或等于 $i$，结束位置可以在 $j$ 之后或等于 $j$，只要子串覆盖至少 $n$ 个连续的辅音字母。
- #### 解释（$n=3$）
选 ght。
|s|t|r|a|i|g|h|t|a|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|可选|可选|可选|可选|可选|必选|必选|必选|可选|

在 $n$ 左边有 $5$ 个可选，在 $t$ 左边有 $1$ 个可选，所以左端点有 $6$ 种选择，右端点有 $2$ 种选择，所以一共有 $6\times2=12$ 种选择。
### 3 .避免重复计算：
确保每个子串只被计算一次。可以通过滑动窗口的方式，维护最近的满足条件的辅音段，并计算新子串的数量。
- #### 解释（$n=3$）
选 str 和 ght。
|s|t|r|a|i|g|h|t|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|可选1|可选1|可选1|可选1|可选1|必选1|必选1|必选1|
|必选2|必选2|必选2|可选2|可选2|可选2|可选2|可选2|

在选 str 的时候会取到 straight，而且在选 ght 的时候也会取到 straight，所以要去重。
# 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define run_fast ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
using namespace std;
string s;
int n;
bool isVowel(char c) {
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}
signed main() {
	run_fast;
	int T;
	cin >> T;
	for (int j = 1; j <= T; j++) {
		cin >> s >> n;
		int ans = 0, con = 0, last = -1;
		for (int i = 0; i < s.size(); i++) {
			if (!isVowel(s[i])) {
				con++;
				if (con >= n) {
					int start = i - n + 1, left = start - last, right = s.size() - i;
					ans += left * right;
					last = start;
				}
			} else {
				con = 0;
			}
		}
		cout << "Case #" << j << ": " << ans << "\n";
	}
	return 0;
}
//var code = "c3d5192f-68a0-4517-859b-34fd1dd4f60c"
```

---

## 作者：IkillDream (赞：0)

# P13291 题解

## 思路

一开始我直接想到遍历字符串的方法，然后统计所有有效子串，判断如果连续的辅音段 $\ge n$对于每个，那么满足条件，最后再累加结果就好了。

## [AC](https://www.luogu.com.cn/record/225272348) points

```c++
#include<bits/stdc++.h>
using namespace std;
char s[1000005];
int pre[1000005];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int t,n,l,r,cas=1;
    cin>>t;
    while(t--){
        cin>>s+1>>n;
        l=strlen(s+1);
        for(int i=1;i<=l;i++){
            pre[i]=pre[i-1];
            if(s[i]!='a'&&s[i]!='e'&&s[i]!='i'&&s[i]!='o'&&s[i]!='u') pre[i]++;
            else pre[i]=0;
        }
        long long ans=0;
        int last=-1;
        for(int i=1;i<=l;i++){
            if(pre[i]>=n) last=i-n+1;
            if(last!=-1) ans+=last;
        }
        cout<<"Case #"<<cas++<<": "<<ans<<"\n";
    }
    return 0;
}
```

## 后记

新知识：```ios::sync_with_stdio(0);cin.tie(0);```，这段代码的意思是关闭输入输出流，可以有效的帮我们减少时间，我们平时用的输入 ```cin```，是需要时间的，但 ```scanf("&变量名"，变量名)```，是不需要时间的，所以，在代码开头加上这句话是没有坏处的，当让，只要你不嫌 ```scanf``` 难打就好了。

对应练习：[1177](https://www.luogu.com.cn/problem/P1177)。

题解制作不容易如果决的我的题解写的好的话可以点个赞吗 qwq。

题解可以抄，但是你要学会哦！

---

## 作者：Clouds_dream (赞：0)

### 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P13291)  
即计算给定字符串中包含至少连续 $n$ 个辅音字母的子串数量。

### 题目分析
由于 $1 \le L \le 10^6$，直接枚举肯定是不行的。我们可以用滑动窗口来解决。  
我们遍历字符串，维护两个变量：当前连续辅音的长度（$cnt$）和最近一次出现连续 $n$ 个辅音的起始位置（$la$）。对于每个位置 $i$，我们能够快速计算以 $i$ 结尾的满足条件的子串数量，从而避免了对所有子串的枚举。

### 代码实现

```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

int ti;

void f(int t){
	string s;
	cin>>s;
	int n;
	cin>>n;
	int ans=0,cnt=0,la=-1;//cnt 记录当前连续辅音字母的长度,la 记录最近一次出现连续 n 个辅音的起始位置，初始为 -1 表示尚未出现
	for(int i=0;i<s.size();i++){
		if(s[i]=='a'||s[i]=='e'||s[i]=='i'||s[i]=='o'||s[i]=='u'){
            cnt=0;
        }
        else{
            cnt++;
        }
        if(cnt>=n){
            la=i-n+1;
        }
        if(la!=-1){
            ans+=(la+1);
        }
    }
    cout<<"Case #"<<t<<": "<<ans<<endl;
}

signed main()
{
	fst
	cin>>ti;
	for(int t=1;t<=ti;t++){
		f(t);
	}
	return 0;
}
```

---

