# Special Task

## 题目描述

Special Agent Smart Beaver works in a secret research department of ABBYY. He's been working there for a long time and is satisfied with his job, as it allows him to eat out in the best restaurants and order the most expensive and exotic wood types there.

The content special agent has got an important task: to get the latest research by British scientists on the English Language. These developments are encoded and stored in a large safe. The Beaver's teeth are strong enough, so the authorities assured that upon arriving at the place the beaver won't have any problems with opening the safe.

And he finishes his aspen sprig and leaves for this important task. Of course, the Beaver arrived at the location without any problems, but alas. He can't open the safe with his strong and big teeth. At this point, the Smart Beaver get a call from the headquarters and learns that opening the safe with the teeth is not necessary, as a reliable source has sent the following information: the safe code consists of digits and has no leading zeroes. There also is a special hint, which can be used to open the safe. The hint is string $ s $ with the following structure:

- if $ s_{i} $ = "?", then the digit that goes $ i $ -th in the safe code can be anything (between $ 0 $ to $ 9 $ , inclusively);
- if $ s_{i} $ is a digit (between $ 0 $ to $ 9 $ , inclusively), then it means that there is digit $ s_{i} $ on position $ i $ in code;
- if the string contains letters from "A" to "J", then all positions with the same letters must contain the same digits and the positions with distinct letters must contain distinct digits.
- The length of the safe code coincides with the length of the hint.

For example, hint "?JGJ9" has such matching safe code variants: "51919", "55959", "12329", "93539" and so on, and has wrong variants such as: "56669", "00111", "03539" and "13666".

After receiving such information, the authorities change the plan and ask the special agents to work quietly and gently and not to try to open the safe by mechanical means, and try to find the password using the given hint.

At a special agent school the Smart Beaver was the fastest in his platoon finding codes for such safes, but now he is not in that shape: the years take their toll ... Help him to determine the number of possible variants of the code to the safe, matching the given hint. After receiving this information, and knowing his own speed of entering codes, the Smart Beaver will be able to determine whether he will have time for tonight's show "Beavers are on the trail" on his favorite TV channel, or he should work for a sleepless night...

## 样例 #1

### 输入

```
AJ
```

### 输出

```
81
```

## 样例 #2

### 输入

```
1?AA
```

### 输出

```
100
```

# 题解

## 作者：gdz0214_and_zxb0214 (赞：2)

## 题面
[CF316A2 Special Task](https://www.luogu.com.cn/problem/CF316A2)
## 思路&导入
观察题面 发现将输入一个字符串。

其中 输入的字符分三种情况。
1. 字符为 `A B C …J`
2. 字符为 `？`
3. 字符为 `1 2 3 … 10`
### 情况一
先看到第一种情况。

这种情况下可知，无论多少重复字符都等价。

（重复字符都只有同样的取值方法。）

接着，我们仅需将这 $10$ 个数分配给这不同的且满足第一种情况的的字符种数。

于是我们发现，竟然是排列组合？

那么，公式显而易见地出现了。

情况一种数（$n$ 为不同的且满足第一种情况的字符总数）：$A_{10}^{n}$。

处理代码。
```cpp
for （int i = 10; i >= 10 - n + 1; i--） {
    ans *= i;
}
```
### 情况二
明显，情况二每个字符都有 $10$ 种处理方式。

处理代码。
```cpp
while （m--） {
    ans *= 10;
}
```
### 情况三
无需处理
```cpp
continue;
```
## 代码实现
### 特殊情况
然而题目中还要求。

> 同时，规定字符串开头的数字不能为 $0$。

这种情况只需加个小小的特判（详见 code。）
### 优化
可是，题目中有一句。

![](https://cdn.luogu.com.cn/upload/image_hosting/v2lvwt6g.png)

翻译：空间会炸。

我们发现，代码中有许多乘 $10$。

此处，我们决定使用存 $0$ 的方法。
### AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long //开long long 
int len, cnt1, ans = 1, f = 1, vis[10], i;
string s, k;
signed main() {
    cin >> s;
    len = s.size();
    for (i = 0; i < len; i++) {
        if (s[i] >= 'A' && !vis[s[i] - 'A']) {
            cnt1++;
            vis[s[i] - 'A'] = 1;
            if (i == 0) { //特判
                f = 0;
            }
        } else if (s[i] == '?') {
            if (i == 0) { //又是特判 
                ans *= 9;
            } else { //优化存0 
                k += '0';
            }
        }
    }
    for (i = 10; i >= 10 - cnt1 + 1; i--) {
        ans *= i;
    }
    if (!f) { //还是特判
        ans = ans / 10 * 9;
    }
    printf("%lld%s", ans, k.c_str()); //c_str函数:将string转为char数组 
    return 0;//功德圆满(真)
}
```

---

## 作者：szh_AK_all (赞：2)

## 良心题解

~~简单易懂的题解，没看懂的可以私信我~~

### 分析

这道题可以转化为一道排列组合题。由于我们只能改变字符 $A-J$ 的值，所以，我们只需考虑字符 $A-J$。

我们可以将不同的字母看成不同的格子，每个格子里都可以填 $0-9$ 这九个数字（开头格子除外）。并且每个格子填的数字不能重复。

当字母出现在开头时，计时器应该乘 $9$（注意：计时器的初始值应设为 $1$）；当字母出现在中间时，我们首先要判断该字母之前是否出现过。

具体的，如果该字母出现过，说明这个字母所对应的格子中要填的数已经确定了，那么我们不再考虑该字母。如果该字母没出现过，我们要考虑之前出现过多少不同的字母，也就是有多少个数字不能选。确定好如上信息后，将计时器乘可以选的数字的个数，并标记该字母，说明该字母不用再考虑了。

当然，我们好要考虑问号的情况。当问号出现在开头时，我们同样要将计时器乘 $9$；否则，将计时器乘 $10$。

至此，大致思路已经明确了。由于最终答案可能很大，所以应该使用高精度。

### 做法一：使用高精度
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[30];
struct ch
{
    int a[100005],s;
};
ch operator*(ch r,int t)//重载函数 高精度乘低精度
{
    for(int i=1;i<=r.s;i++)
        r.a[i]*=t;
    for(int i=1;i<=r.s+10;i++)//处理进位
    {
        r.a[i+1]+=r.a[i]/10;
        r.a[i]%=10;
    }
    r.s+=10;
    while(r.a[r.s]==0&&r.s>1)//处理前导0
        r.s--;
    return r;
}
int main()
{
	ch ans;
	memset(ans.a,0,sizeof(a));
	ans.s=1;
	ans.a[1]=1;
	string s;
	cin>>s;
	int chu=0;
	for(int i=0;i<s.size();i++)
	{
		if(s[i]>='A'&&s[i]<='J'&&a[s[i]-'A'+1]==0)
		{
			if(i==0)
				ans=ans*9;
			else
				ans=ans*(10-chu);//注意这里是用高精度
			chu++;
			a[s[i]-'A'+1]++;
		}
		else if(s[i]=='?')
			ans=ans*(10-(i==0));//同样是高精度
	}
	for(int i=ans.s;i>=1;i--)
		cout<<ans.a[i];
} 
```
提交这份代码，发现第 $21$ 个测试点超时了，考虑优化。

由于在调用高精度运算时，计时器大部分要乘的数字为 $10$，浪费了很多时间，所以，我们可以记录计时器要乘上多少个 $10$，最后输出对应个数的 $0$ 即可。

### 做法二：做法一优化
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[30];
struct ch
{
    int a[100005],s;
};
ch operator*(ch r,int t)
{
    for(int i=1;i<=r.s;i++)
        r.a[i]*=t;
    for(int i=1;i<=r.s+10;i++)
    {
        r.a[i+1]+=r.a[i]/10;
        r.a[i]%=10;
    }
    r.s+=10;
    while(r.a[r.s]==0&&r.s>1)
        r.s--;
    return r;
}
int main()
{
	ch ans;
	memset(ans.a,0,sizeof(a));
	ans.s=1;
	ans.a[1]=1;
	string s;
	cin>>s;
	int chu=0;
	int wen=0;
	for(int i=0;i<s.size();i++)
	{
		if(s[i]>='A'&&s[i]<='J'&&a[s[i]-'A'+1]==0)
		{
			if(i==0)
				ans=ans*9;
			else
				ans=ans*(10-chu);
			chu++;
			a[s[i]-'A'+1]++;
		}
		else if(s[i]=='?')
		{
		    if(i==0)
		        ans=ans*9;
		    else//这里不用调用高精度来计算ans*10，而是直接记录要乘上的10的个数
		        wen++;
		}
	}
	for(int i=ans.s;i>=1;i--)
		cout<<ans.a[i];
	for(int i=1;i<=wen;i++)//输出0
		cout<<0;
} 
```
这份代码可以通过本题，但还有一种更简单的方法。

在做法二的基础上，我们发现：既然出现次数很多的 $10$ 这个因子不用在高精度中计算，那么，计时器的大小最高为 $10!$，完全可以用 `int` 存下。

### 做法三：做法二的优化
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[30];
int main()
{
	string s;
	cin>>s;
	int ans=1;
	int chu=0;
	int wen=0;
	for(int i=0;i<s.size();i++)
	{
		if(s[i]>='A'&&s[i]<='J'&&a[s[i]-'A'+1]==0)
		{
			if(i==0)
				ans=ans*9;
			else
				ans=ans*(10-chu);
			chu++;
			a[s[i]-'A'+1]++;
		}
		else if(s[i]=='?')
		{
		    if(i==0)
		        ans=ans*9;
		    else
		        wen++;
		}
	}
	cout<<ans;
	for(int i=1;i<=wen;i++)
		cout<<0;
} 
```
本题接至此已结束，如果你看到了这里，不妨点个赞吧！


---

## 作者：辛丑九月 (赞：2)

## Analysis

建议评黄。

先考虑问号的情况：如果是开头的问号，那么不能取 $0$，答案乘 $9$ 倍，然后中间的问号 $10$ 个数都能取，答案乘 $10$ 倍。

再就是字母，显然是先数出字母的种类数 $p$，那么用组合数就可以知道方案数为 $p!\binom {10}p$ 解释为选出 $p$ 个数字，然后再是 $p$ 的全排列。

但是有一个问题，就是可能有字母在开头，那么我们优先考虑这种字母，答案先乘个 $9$（除了 $0$），剩下的组合数也变成了 $(p-1)!\binom {10}{p-1}$。

这题答案会很大，但是没有关系，发现除了乘 $10$ 以外最大可能性也就 $9 \times \binom {10} 5$，不会爆，拿个计数器把 $10$ 的个数存下来然后直接末尾输出 $0$ 即可。

值得注意的是 $m!\binom nm = m!\frac {n!}{m!(n-m)!} = \frac {n!}{(n-m)!} = n^{\underline m}$ 做起来会好写一点。

## Code

```cpp
# include <bits/stdc++.h>
# define int long long
using namespace std;

string s;
int n;
int res, cnt, p, t;
bool vis[30];

signed main () {
	cin >> s; res = 1; n = s.size ();
	if (s[0] == '?') res *= 9;
	for (int i = 1; i < n; i++) {
		if (s[i] == '?') cnt++;
		if (isupper (s[i]) && vis[s[i] - 'A'] == 0)
			vis[s[i] - 'A'] = 1, p++;
	}
	if (isupper (s[0])) {
		res *= 9, t = 1; // t 的作用是后面初始值由 10 变成 9
		for (int i = 1; i < n; i++)
			if (s[i] == s[0]) { p--; break ; }
	}
	for (int i = 1; i <= p; i++) res *= 10 - t - i + 1; // 计算组合数
	printf ("%lld", res); while (cnt--) putchar ('0');
	return 0;
}
```

---

## 作者：RioFutaba (赞：1)

## 题面
[CF316A2](https://www.luogu.com.cn/problem/CF316A2)
## 思路

开始的时候设一个 $tot$ 变量，初始值为 $10$，表示当前字母表示的数的可能的数量。再设一个答案为 $ans$。

如果当前位置为没有遇见过的字母，则答案乘以 $tot$。下一种字母的表示的数的可能性为 $tot-1$。注意如果字母在开头，那答案乘以 $9$，因为开头不能为 $0$。

如果当前位置为问号，那么答案乘以 $10$。同样的，如果问号在开头，答案乘以 $9$。

如果当前位置为数字，答案没有变化，不做处理。

因为答案很大，最多可以达到 $9 \times 10^{10^5-1}$，所以我们需要做一些处理。可以发现，当乘上 $10$ 的时候，直接在答案后面加个 $0$ 即可，计算过程中其他所有乘数的积不超过 $9!$。所以我们记录乘以 $10$ 的次数为 $cnt$，$ans$ 记录其他乘数的积，最后输出 $ans$ 时在后面加上 $cnt$ 个 $0$ 即可。

Code:
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
string s;
bool vis[256];
int tot=10;
signed main(){
	cin >> s;
	int ans=1,cnt=0;
	for(int i=0;i<(int)s.length();i++){
		if(i==0){
			if(isalpha(s[i]) || s[i]=='?') ans*=9;
			if(isalpha(s[i])) vis[s[i]]=1,tot--;
			continue;
		}
		if(s[i]>='0' && s[i]<='9') continue;
		else if(isalpha(s[i])){
			if(!vis[s[i]]) ans*=(tot--),vis[s[i]]=1;
		}else{
			cnt++;
		}
	}
	cout << ans;
	for(int i=1;i<=cnt;i++) cout << "0";
	cout << endl;
	return 0;
}
```

---

## 作者：初雪_matt (赞：1)

## 思路

简单如[你](https://www.luogu.com.cn/problem/CF316A1)。

分两种情况讨论，显然数字我们是不需要讨论的。

情况分别为字母，问号与首字符。

- 当这是首字符时，如果其是字母与问号，对答案的贡献均为 $9$。

- 当该字符为字母时，对答案的贡献应为 $T\times(10-K)$，其中 $T$ 为该字符是否出现过，$K$ 为当前统计过了多少个不同的字符。

- 当该字符为问号时，必定对答案的贡献为 $10$。

注意在首字符情况下依然要统计 $T$ 与 $K$ 的值，这里我用映射处理 $T$ 的值。如果你用的是普通高精度必然超时，显然我们统计问号数量的时候乘的 $10$ 可以直接加入字符串末尾，可以避免超时。

## 代码

```cpp
#include<bits/stdc++.h>
#define endl "\n"
using namespace std;
int n,m;
string s;
map<char,int> mp;
string ans="1";
int k,l,KA=9,KB=10;
string mul(string A,int B){//高精度
    string C;
    for(int i=A.size()-1,t=0;i>=0||t>0;i--){
        if(i>=0) t+=(A[i]-'0')*B;
        C+=(t%10)+'0';
        t/=10;
    }
    reverse(C.begin(),C.end());
    return C;
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>s;
	for(int i=0;i<s.length();i++){
		if(s[i]=='?'){
			l++;//统计问号数量，方便一起乘
			continue;
		}
		if(s[i]>='A'&&s[i]<='J') mp[s[i]]++;//统计每个字符的数量
	}
	if(s[0]=='?') ans=mul(ans,KA),l--;
	if(s[0]>='A'&&s[0]<='J') ans=mul(ans,KA),mp[s[0]]=1e9,k++;
	if(l) for(int i=1;i<=l;i++) ans+="0";	
	for(int i=1;i<s.length();i++){
		if(mp[s[i]]&&mp[s[i]]!=1e9){
			ans=mul(ans,KB-k++);
			mp[s[i]]=1e9;//1e9 是极大值，方便证明这个字符我们已经算过了
		}
	}
	cout<<ans<<endl;
}
```

---

## 作者：Genshin_ht (赞：0)

# 题解：CF316A2 Special Task

## 思路

分类讨论（要么是字母，要么是首字母）：

- 如果当前是首字母，且为字母或问号，则对答案乘 $9$。
- 如果当前不是首字母，且为字母，则答案乘 $t\times (10-k)$。
- 如果当前不是首字母，且为问号，则对答案乘 $10$。

## 注意
本题需要高精度，但如果不想打高精度的需要考虑既然出现次数很多的 $10$ 这个因子不用在高精度中计算，那么，计时器的大小最高为 $10!$（$10!$ 的意思为 $10$ 的阶乘，既 $10\times 9\times 8 \times 7......\times 2 \times 1$，在 `int` 范围内。

## 代码

```
#include <bits/stdc++.h>
using namespace std;
int a[30];
int main()
{
    string s;
    cin >> s;
    int ans = 1;
    int chu = 0;
    int wen = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] >= 'A' && s[i] <= 'J' && a[s[i] - 'A' + 1] == 0)
        {
            if (i == 0)
                ans = ans * 9;
            else
                ans = ans * (10 - chu);
            chu++;
            a[s[i] - 'A' + 1]++;
        }
        else if (s[i] == '?')
        {
            if (i == 0)
                ans = ans * 9;
            else
                wen++;
        }
    }
    cout << ans;
    for (int i = 1; i <= wen; i++)
        cout << 0;
}
```

---

## 作者：headache (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF316A2)


---

## 思路

一看到题解区的高精是两眼一花，于是决定另辟蹊径。

$\bullet$ 对于 $s_i$ 是字母的情况，可以用一个变量存储下一个字母有几个可能性，所以初始值应设为 $10$，每一次就减一。

**重点**，若字母在字符串开头，则只能乘 $9$。


$\bullet$ 对于 $s_i$ 为问号的情况可分两类。首先是开头，与字母处理方式类似，方案数乘 $9$，其余可无脑乘  $10$。

**处理技巧**，由于字符串长度在 $10^6$ 内，对于乘 $10$ 的情况，可直接在原数后面补一个 $0$。


---

## 代码展示
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
int cnt1=10,cnt2=0,ans=1;
signed main(){
	cin>>s;
	int len=s.size();
	for(int i=0;i<len;i++){
		if(s[i]<='A'&&s[i]>='J'){
			if(i==0) ans*=9;
			else{
				ans*=cnt1;
				cnt1--;
			}
		}
		else if(s[i]=='?'){
			if(i==0) ans*=9;
			else cnt2++;
		} 
	}
	cout<<ans;
	for(int i=1;i<=cnt2;i++) cout<<"0";
	return 0;
}
```

---

## 作者：czh___ (赞：0)

题目大意：

给你一个字符串，如果是问号，则可以从 $0$ 到 $9$ 随便选一个数；如果是数字，这一位上就只能是这个数；如果是大写字母，那这一位上可以从 $0$ 到 $9$ 随便选一个数，但是相同的字母代表的数必须相同，不同的字母代表的数必须不同。第一位不能为 $0$。


 思路：

~~乍一看：这不是会乘法原理的就能做吗？~~

我们先读入一个字符串，从 $0$ 下标开始遍历，$0$ 下标做一个特判，是数字就不管，是问号直接 $ans$ $\times$ $9$，是字母就用一个 map 来标记，再乘 $9$。后面的下标依次做：是问号就乘十（等于在答案末尾多了一个零，这里有个小优化：用一个变量来记录零的个数，最后再输出），是数字就跳过不管，是字母先判断标记过没有，如果标记过，那直接跳过；如果没被标记，那我们用 $ans$ $\times$ $cnt$，$cnt$ 初值为十，每乘一次再减一。最后先输出 $ans$，再输出零的个数。

 $cnt$ 是啥？

是一个从十慢慢向下减的变量，因为字母选的数字每选一个就少一个，所以 $cnt$ 乘一次就减一。


 无注释代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char a[100001];
map<char,bool>ma;
int ans=1,cnt=10,lingshu=0;
signed main(){
    cin>>a;
	int len=strlen(a);
	for(int i=0;i<len;i++){
		if(a[i]>='0'&&a[i]<='9')
			continue;
		if(i==0){
			ans*=9;
			if(a[i]!='?'){
				ma[a[i]]=1;
				cnt--;
			}	
		}
		else{
			if(a[i]=='?')
				lingshu++;
			else{
				if(!ma[a[i]]){
					ans*=cnt;
					ma[a[i]]=1;
					cnt--;
				}
			}
		}
	}
	cout<<ans;
	while(lingshu--)
		cout<<"0";
    return 0;
}
```

若还有不清楚的地方，欢迎大家私信骚扰！

---

## 作者：2011FYCCCTA (赞：0)

[题目](https://www.luogu.com.cn/problem/CF316A2)

很好的排列组合题。

---
### 思路

首先，统计出字母和 `?` 的数量，设共有 $a$ 种字母，$b$ 个 `?`。

再根据 $s$ 的第一位分讨（前导零问题）：

1. 第一位是数字：
	
	不用考虑前导零的问题，结果就是 $A_{10}^a \times 10^b$，注意字母所代表的数要区分顺序。

2. 第一位是字母：

	因为第一位不能是 $0$，所以第一位只有 $9$ 种选择，再从剩下的 $9$ 个数字选 $a - 1$ 个，结果就是 $9 \times A_9^{a - 1} \times 10^b$。
    
3. 第一位是 `?`：

	第一个 `?` 只有 $9$ 种选择，剩下的都有 $10$ 种，结果就是 $A_{10}^a \times 9 \times 10^{b - 1}$。
    
本题的 $|s|$ 可以达到 $10^5$，需要用~~python~~高精度。

---
### 代码
```cpp
#include "bits/stdc++.h"
using namespace std;
const int MAXS = 1e5;
string s;
char f;
int sc/*字母的数量*/ , sq/*?的数量*/ , ans[MAXS + 5];
map<char , bool> book;
int main()
{
    cin >> s;
    f = s[0];
    for (auto i : s)
    {
        if (i >= 'A' && i <= 'J' && !book[i])
        {
            ++sc;
            book[i] = true;
        }
        else if (i == '?') ++sq;
    }
    if (f >= '0' && f <= '9')
    {
        ans[1] = 1;
        for (int i = 10 ; i >= 10 - sc + 1 ; i--)
        {
            for (int j = 1 ; j <= MAXS ; j++) ans[j] *= i;
            for (int j = 1 ; j <= MAXS ; j++)
            {
                ans[j + 1] += ans[j] / 10;
                ans[j] %= 10;
            }
        }
    }
    else if (f >= 'A' && f <= 'J')
    {
        ans[1] = 9;
        for (int i = 9 ; i >= 9 - sc + 2 ; i--)
        {
            for (int j = 1 ; j <= MAXS ; j++) ans[j] *= i;
            for (int j = 1 ; j <= MAXS ; j++)
            {
                ans[j + 1] += ans[j] / 10;
                ans[j] %= 10;
            }
        }
    }
    else
    {
        ans[1] = 1;
        for (int i = 10 ; i >= 10 - sc + 1 ; i--)
        {
            for (int j = 1 ; j <= MAXS ; j++) ans[j] *= i;
            for (int j = 1 ; j <= MAXS ; j++)
            {
                ans[j + 1] += ans[j] / 10;
                ans[j] %= 10;
            }
        }
        for (int j = 1 ; j <= MAXS ; j++) ans[j] *= 9;
        for (int j = 1 ; j <= MAXS ; j++)
        {
            ans[j + 1] += ans[j] / 10;
            ans[j] %= 10;
        }
        --sq;
    }
    int top = MAXS;
    while (!ans[top--]);
    for (int i = top + 1 ; i >= 1 ; i--) cout << ans[i];
    while (sq--) cout << '0';
    return 0;
}
```

---

## 作者：tmpliyijiang (赞：0)

## 思路

### 第一步：忽略开头不能为 $0$ 的限制

#### 1. 首先考虑字母

因为每个字母在 $s$ 中位置固定，所以只需要求出出现的字母代表不同数字的方案总数即可。设出现 $m$ 个字母（$0<m\le 10$），则总数为 $\prod_{i=11-m}^{10}$，最大值为 $3628800$。

#### 2. 再考虑 `?`

由于它代表的数不固定，因此对于每一个都会使答案乘 $10$，直接运行显然爆，因此我们可以用一个计数器存储后缀 $0$ 的个数。

#### 3. 常数

不会对答案产生贡献，跳过。

### 第二步：考虑开头不能为 $0$ 的限制

#### 1. 开头为字母

这个字母不可能代表 $0$，因此将答案乘 $\frac{9}{10}$。

#### 2. 开头为 `?`

它不可能代表 $0$，因此将答案乘 $\frac{9}{10}$。

#### 3. 开头为常数

不会对答案产生贡献，跳过。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int cnt,m,ans=1,c[10];
int main(){
	cin>>s;
	int n=s.size();
	if(n==1){//特判
		if(isdigit(s[0]))putchar('1');
		else putchar('9');
		return 0;
	}
	for(register int i=0;i<n;i++){
		if(isupper(s[i]))c[s[i]-'A']++;//字母
		else if(s[i]=='?')cnt++;//'?'
	}
	for(register int i=0;i<10;i++)if(c[i])m++;//统计字母数量
	if(m){//不判导致m=0,死循环
		for(register int i=10;i>10-m;i--)ans*=i;//计算组合数
		if(isupper(s[0]))ans=ans/10*9;
	}
	if(s[0]=='?')cnt--,ans*=9;
	cout<<ans;
	if(cnt)//不判导致cnt=0,死循环
	for(int i=0;i<cnt;i++)putchar('0');
	return 0;
}
```

---

## 作者：InfSauf (赞：0)

输入一个字符串，其中包含数字，问号以及字母。

规定字符串开头数字不能为 $0$ 所以我们对字母及问号进行分类讨论。

1. 如果是字母在开头，则字母能代表的数字不能为 $0$，也就是说如果是字母在字符串的开头，则该字母能代替的数字就只有 $9$ 个。

2. 如果是问号开头，也只能代替 $9$ 个数字，因为 $0$ 不能作为开头。

3. 若既不是数字也不是问号开头则正常计算，每个字母可以代替一个数字，不同字母代替的数字不能相同。

对于字母是否出现过的判断，我们可以选择采用 map 进行记录，可以用两个 map 分别记录是否出现过与该字母可以代替的数字个数

```cpp
#include <bits/stdc++.h>
#include <map>
using namespace std;
void scan(__int128 &x)//__int128输入 
{
	x=0;int f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	x*=f;
}
inline void print(__int128 x)//__int128输出
{
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9) print(x/10);
	putchar(x%10+'0');
}
__int128 sum = 1;//开__int128懒得写高精度（ 
int b = 10;//只能代替0-9共10个数字，每出现一个新字母则减一 
map<char, int>mp;//记录该字母所能代替的数字数量 
map<char, bool>num;//记录该字母是否出现过 
int sum1;//记录？个数，因为是乘10，所以最后统一输出0，要不然#21会TLE 
int main(){
	string s;//字符串 
	cin >> s;
	for(int i = 0; i < s.size(); i++){
		if(s[i] >= '0' && s[i] <= '9')sum *= 1;//开头为数字 
		else if(i == 0 && (s[i] >= 'A' && s[i] <= 'J')){//第一个字符为字母 
			mp[s[i]] = 9;//可代替数字只有9种个 
			sum *= mp[s[i]];//答案乘上该字母所能代替的数字个数 
			num[s[i]] = 1;//该字母已经出现过 
			if(s[i + 1] != s[i])b--;//如果下一个字母与该字母不同，则减一 
		}
		else if(s[i] >= 'A' && s[i] <= 'J'){//如果字符为字母 
			if(!mp[s[i]]){//该字母没有出现过 
				mp[s[i]] = b;//记录该字母可代替数字的个数 
				sum *= mp[s[i]];//答案乘上该字母可代替数字的个数 
				num[s[i]] = 1;//该字母已经出现过 
				b--;//可代替数减一 
			}
			else if(i == 1)b--;//如果第二个字符是字母则减一，防止AA12?C这种情况 
			if(!num[s[i]])sum *= mp[s[i]];//字母每出现过，案乘上该字母所能代替的数字个数  
		}
		else if(i == 0 && s[i] == '?')sum *= 9;//如果开头是字母，则答案乘上9 
		else if(s[i] == '?')sum1++;//统计？个数 
	}
	print(sum);//输出答案 
	for(int i = 0; i < sum1; i++)cout << 0;//输出？个数的0 
}
```


---

## 作者：xibaohe (赞：0)

# CF316A2 Special Task 题解
首先声明，由于本题目思路较简单，这篇题解中的思路可能与其他题解相似。但其他的题解对本题重点的高精度都没有进行更多阐释，这篇题解将对高精度部分进行重点阐释。

# 题目思路
本题可以分为三种情况：

- 问号。问号可以代表文中提到的 $10$ 个数字，除非是开头，否则应将情况乘 $10$。

- 字母。我们可以统计字母的个数，然后计算方法与问号相同。

- 数字。由于数字已经给定，因此不需要考虑。

# 本题重点——封装高精度
这道题就是一道模拟，思路极为简单，如果不是因为高精度我认为甚至可以评红。

首先来为大家出示封装高精度的思路图解。

封装高精度，顾名思义，就是将高精度封装在结构体中，然后重载运算符进行操作。

![](https://cdn.luogu.com.cn/upload/image_hosting/oq2d94xu.png)

接下来进行关于高精度加法的讲解，我们可以重载加号进行运算。这里的难点是需要从低位向高位进位。

![](https://cdn.luogu.com.cn/upload/image_hosting/vwvh8nfr.png)

这是关于高精度减法的讲解，我们可以重载减号进行运算。这里的难点是需要从低位向高位退位。

![](https://cdn.luogu.com.cn/upload/image_hosting/lcuyka09.png)

这个高精度乘法只支持高精乘单精，除法与之类似。

![](https://cdn.luogu.com.cn/upload/image_hosting/fuwrq3rh.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/xoib1f40.png)

大家可以仔细观看上面的思路，下面为大家出示封装高精度的基本模板：

```cpp
#include<iostream>
#include<string>
#include<cstring>
using namespace std;

struct BIG
{
	int len, num[1005];
	BIG()
	{ //定义高精度变量且初始化为0
		memset(num, 0, sizeof(num));
		len = 1;
	}
	void set(int n)
	{ //低精度转高精度
		memset(num, 0, sizeof(num));
		len = 0;
		while(n > 0)
		{
			num[++len] = n % 10;
			n /= 10;
		}
		if(len == 0) len = 1;
	}
	void set(string s)
	{ //字符串转高精度
		memset(num, 0, sizeof(num));
		len = s.size();
		for(int i = 1; i <= len; i++)
			num[i] = s[len-i] - '0';
	}
	void print()
	{
		for(int i = len; i >= 1; i--)
			cout << num[i];
		cout << endl;
	}
};

BIG operator+ (BIG a, BIG b)
{ // 高精+高精
	BIG c;
	c.len = max(a.len, b.len);
	int u = 0;
	for(int i = 1; i <= c.len; i++)
	{
		int t = a.num[i] + b.num[i] + u;
		c.num[i] = t % 10;
		u = t / 10;
	}
	if(u > 0) c.num[++c.len] = u;
	return c;
}

bool operator< (BIG a, BIG b)
{
	if(a.len != b.len) return a.len < b.len;
	for(int i = a.len; i >= 1; i--)
		if(a.num[i] != b.num[i])
			return a.num[i] < b.num[i];
	return false;
}

bool operator> (BIG a, BIG b)
{
	return b < a;
}

bool operator== (BIG a, BIG b)
{
	return !(b < a) && !(a < b);
}

bool operator<= (BIG a, BIG b)
{
	return !(b < a);
}

bool operator>= (BIG a, BIG b)
{
	return !(a < b);
}

bool operator!= (BIG a, BIG b)
{
	return (b < a) || (a < b);
}

BIG operator- (BIG a, BIG b)
{ // 高精-高精（大减小）
	BIG c;
	c.len = max(a.len, b.len);
	int u = 0;
	for(int i = 1; i <= c.len; i++)
	{
		int t = a.num[i] - b.num[i] - u;
		if(t < 0)
		{
			c.num[i] = t + 10;
			u = 1;
		}
		else
		{
			c.num[i] = t;
			u = 0;
		}
	}
	while(c.num[c.len] == 0 && c.len > 1) c.len--;
	return c;
}

BIG operator* (BIG a, int b)
{ // 高精*单精
	BIG c;
	c.len = a.len;
	int u = 0; //记录进位多少
	for(int i = 1; i <= c.len; i++)
	{
		int t = a.num[i] * b + u;
		c.num[i] = t % 10;
		u = t / 10;
	}
	while(u > 0)
	{ //若a的最高位乘完了之后还需要进位，c会比a位数多
		c.len++;
		c.num[c.len] = u % 10;
		u /= 10;
	}
	return c;
}

BIG operator/ (BIG a, int b)
{// 高精÷单精（舍余数）
	BIG c;
	c.len = a.len;
	int r = 0; //记录余数
	for(int i = c.len; i >= 1; i--)
	{ //从最高位开始除
		int t = r * 10 + a.num[i];
		c.num[i] = t / b;
		r = t % b;
	}
	while(c.num[c.len] == 0 && c.len > 1) c.len--; //找到最高的非零位
	return c;
}

int main()
{

	return 0;
}

```

# 满分代码
其他几篇题解的代码已经写的很好了，为了防止抄题解者抄袭，这里就不放满分代码了。封装高精度模板已经给出，思路也已经揭晓，剩下的难度应该就很低了，大家自己完成吧！如果完成不了可以参考其他题解的代码。

---

## 作者：GeorgeAAAADHD (赞：0)

一道略带思维性的高精题。

首先定义一个高精度数组 $ans$，初始化设置为 $1$。

对于每个数字，每个数字只可能代表一种值，所以可以不进行任何操作。

对于每个 `A ~ J` 字符，存储它们可能代表的值的个数，第一个字母应该有十种情况，之后每个不同的字母的情况应该逐渐递减 $1$。特判字母在开头的情况，如果字母在开头，那么这个字母只有九种情况（舍去 $0$ 的情况）。最后高精相乘即可。

对于每个 `?` 字符，如在开头则高精乘上 $9$，否则将输出 $0$ 的个数加上一，最后统一输出即可。

最后奉上代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string a;
int is[11] = {0}, ans[100001] = {1, 1}, k = 10, g = 0;
int wei (int a) { //求单精度数位数函数
	int n = 0;
	do {
		n++;
		a /= 10;
	} while (a);
	return n;
}
void out () { //自定义高精度数输出函数
	for (int i = ans[0]; i; i--) {
		cout << ans[i];
	}
}
void mul_d (int b) { //高精度数乘单精度数函数
	int s, mx = wei(b) + ans[0];
	for (int i = 1; i <= ans[0]; i++){
		ans[i] *= b;
	}
	for(int i = 1; i <= mx; i++) {
		if (ans[i] >= 10) {
			ans[i + 1] += ans[i] / 10;
			ans[i] %= 10;
		}
	}
	ans[0] = mx + 1;
	while (ans[ans[0]] == 0) ans[0]--;
}
signed main () {
	cin >> a;
	for (int i = 0; i < a.length(); i++) {
		if (isalpha(a[i])) { //判断字母
			if (!is[a[i] - 'A' + 1]) { //判断是否出现过
				if (i == 0) is[a[i] - 'A' + 1] = 9; //特判出现在开头的情况
				else is[a[i] - 'A' + 1] = k;
				mul_d(is[a[i] - 'A' + 1]);
				k--;
			}
		}
		else if (a[i] == '?') { //判断问号
			if (i == 0) mul_d(9); //特判出现在开头的情况
			else g++;
		}
	}
	out(); //输出高精度数
	for(int i = 1;  i <= g; i++) putchar('0'); //统一输出0
	return 0;
}
```

---

