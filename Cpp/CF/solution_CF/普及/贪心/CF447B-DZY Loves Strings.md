# DZY Loves Strings

## 题目描述

DZY loves collecting special strings which only contain lowercase letters. For each lowercase letter $ c $ DZY knows its value $ w_{c} $ . For each special string $ s=s_{1}s_{2}...\ s_{|s|} $ ( $ |s| $ is the length of the string) he represents its value with a function $ f(s) $ , where

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF447B/47a1fab5618b8aab7370048ef8382ed56e397765.png)Now DZY has a string $ s $ . He wants to insert $ k $ lowercase letters into this string in order to get the largest possible value of the resulting string. Can you help him calculate the largest possible value he could get?

## 说明/提示

In the test sample DZY can obtain "abcbbc", $ value=1·1+2·2+3·2+4·2+5·2+6·2=41 $ .

## 样例 #1

### 输入

```
abc
3
1 2 2 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
```

### 输出

```
41
```

# 题解

## 作者：Alex_Wei (赞：11)

题解 CF447B 【DZY Loves Strings】

#### 题意：给你一个小写字符串s，整数k和W'a'，W'b'，……W'z'，对于字符串s中的第i个字符（记作si），它的分值定义如下：Wsi*i。问你插入k个小写字符后，字符串s的总分值最大为多少？

### 思路：贪心，选择a~z中W值最大的一个字符添加k个到末尾，这时候s的分值最大

1. 输入，**定义m为W'a'~W'z'中最大的一个数**

2. **定义n为s的分值**，计算n

3. **定义q为添加k个 "a~z中W值最大的一个字符"的分值**，并输出n+q

4. q的计算**（l为s的长度）**：=m(l+1)+m(l+2)+……+m(l+k)  =  m[(l+1)+(l+2)+……+(l+k)]  =  m[(l+1)+(l+k)]*k/2

5. 有了（4），我们就可以不用定义q，直接输出n+m（l+1+l+k）*k/2

#### 代码（经过处理后只有12行）
```cpp
#include<bits/stdc++.h>
using namespace std;
int k,w[27],n,m;
string s;
int main()
{
	cin>>s>>k;
	for(int x=0;x<26;x++)cin>>w[x],m=max(m,w[x]);//计算m 
	for(int x=0;x<s.size();x++)n+=w[s[x]-'a']*(x+1);//计算n 
	cout<<n+m*(2*s.size()+k+1)*k/2;//输出 
	return 0;
}
```
~~怎么样，简单吧？~~

#### 珍爱生命，请勿抄袭

如果你觉得这篇题解不错，请点个赞吧，谢谢！

---

## 作者：きりと (赞：2)

**[题目传送门](https://www.luogu.com.cn/problem/CF447B)**

### 题目大意

见中文翻译

### 解题思路

贪心，现在我们可以在原字符串中插入$k$个字符，你们我们肯定要让插入的字符的价值最大，也就是说，我们插入的字符一定是$W_s[i]$最大的那个字符



然后考虑插在哪里，由于我们插入的字符的价值一定$≥$原字符串中每个字符的价值，那么我们就要让插入的字符串贡献最大，每个字符对总价值的贡献为：$W_s[i]*i$，那么我们就要让插入字符的$i$尽可能大，也就是从后面插入字符



### 代码实现

开个桶记一下每个字符的价值，然后先算一下元字符串的价值，再算一下后加入部分的价值

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
int num[27];
signed main()
{
	int k;
	cin>>s;
	cin>>k;
	int maxn=-1,ans=0;
	for(int i=1;i<=26;i++)
	{
		cin>>num[i];
		maxn=max(maxn,num[i]);
	}
	for(int i=0;i<s.size();i++)
	{
		ans+=num[s[i]-'a'+1]*(i+1);
	}
	int x=s.size();
	while(k--)
	{
		x++;
		ans+=maxn*x;
	}
	cout<<ans<<endl;
	return 0;
}
```



---

## 作者：Wy_x (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF447B)

## $\texttt{Solution}$:

1. 先算出来题目给定的字符串的价值。

2. 对于插入字符，手玩样例可知每个字符可以插入**无数次**，使用**贪心**策略，每次挑选**价值最大**的字母插入。

**注**：

- 价值最大的字母可以**边输入边记录**，初始化最大值时应定义**非正数**，以便更新最大值。

- 在枚举时，要**注意价值的计算方法**，不要算错。

## $\texttt{Code}$:
```cpp
#include<bits/stdc++.h>   //万能头文件  
using namespace std;

string s;

int k,a[30];
int ans,maxn=-9999999;
//ans 记录最终价值，maxn 记录 价值最大的字符的价值 

signed main()
{
	cin>>s>>k;
	
	for(int i=0;i<26;i++) cin>>a[i],maxn=max(maxn,a[i]);
	//记录 价值最大的字符的价值 
	for(int i=0;i<s.size();i++) ans+=a[s[i]-'a']*(i+1);
	//按照题意，把给定的字符串的总价值算出 
	for(int i=1;i<=k;i++) ans+=maxn*(s.size()+i);
	//贪心，每次把价值最大的字母加入队尾 
	cout<<ans;
	return 0;
}
```

---

## 作者：codeLJH114514 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF447B)

# 题目大意

给你一个由小写字母构成的字符串，可以在其中添加 $k$ 个字符，每一个字符都有一个价值，定义一个字符串的价值为：
$$\sum ^ {|S|} _ {i\ =\ 1} i \times W _ {S_i}$$
让你计算最大的价值。

# 数据范围

$1 \leqslant |S| \leqslant 10 ^ 3$

$1 \leqslant k \leqslant 10^3$

# 解题思路

算法 $\to$ 贪心

在字符串后面添加 $k$ 个价值最大的字符，可以证明，这样的方式一定可以得到最大的价值的字符串。

这样我们就得到了价值最大的字符串 :

```cpp
#include <iostream>
#define maxn 32
using namespace std;
string s;
int k, w[maxn];
int main() {
    cin >> s >> k;
    for (int i = 1; i <= 26; i++)
        cin >> w[i]; // 输入
    int mx = 0;
    for (int i = 1; i <= 26; i++)
        if (w[mx] < w[i])
            mx = i; // 找到价值最大的字符
    for (int i = 1; i <= k; i++)
        s += char(mx - 1 + 'a');
    // s 即为最大价值的字符串
    return 0;
}
```

再计算总价值即可。

完整代码 :

```cpp
#include <iostream>
#define maxn 32
using namespace std;
string s;
int k, w[maxn];
int main() {
    cin >> s >> k;
    for (int i = 1; i <= 26; i++)
        cin >> w[i]; // 输入
    int mx = 0;
    for (int i = 1; i <= 26; i++)
        if (w[mx] < w[i])
            mx = i; // 找到价值最大的字符
    for (int i = 1; i <= k; i++)
        s += char(mx - 1 + 'a');
    // s 即为最大价值的字符串
    int ans = 0;
    for (int i = 0; i < s.size(); i++)
        ans += (i + 1) * w[s[i] - 'a' + 1];
    cout << ans; // 计算总价值并输出
    return 0;
}
```

原始代码(无注释版)

```cpp
#include <iostream>
#define maxn 32
using namespace std;
string s;
int k, w[maxn];
int main() {
    cin >> s >> k;
    for (int i = 1; i <= 26; i++)
        cin >> w[i];
    int mx = 0;
    for (int i = 1; i <= 26; i++)
        if (w[mx] < w[i])
            mx = i;
    for (int i = 1; i <= k; i++)
        s += char(mx - 1 + 'a');
    int ans = 0;
    for (int i = 0; i < s.size(); i++)
        ans += (i + 1) * w[s[i] - 'a' + 1];
    cout << ans;
    return 0;
}
```

压行版

```cpp
#include <iostream>
using namespace std;
string s;
int k, w[32], ans, mx;
int main() {
    cin >> s >> k;
    for (int i = 1; i <= 26; i++) cin >> w[i];
    for (int i = 1; i <= 26; i++) if (w[mx] < w[i]) mx = i;
    for (int i = 1; i <= k; i++) s += char(mx - 1 + 'a');
    for (int i = 0; i < s.size(); i++) ans += (i + 1) * w[s[i] - 'a' + 1];
    cout << ans;
    return 0;
}
```

---

## 作者：xiaofeng_and_xiaoyu (赞：0)

闲话：~~RMJ 降得好啊~~

正题：

可以看出这是一道贪心，由于没有限制，直接放最大值就可以了。

剩下的是标准计算，没什么说的。

CF提交记录 $222878443$ ,已 AC。

```cpp
#include<iostream>
using namespace std;
int main(){
	string s;
	int k,t=-1;
	int val[30];
	cin>>s>>k;
	for(int i=1;i<27;i++){
		cin>>val[i];
		t=max(t,val[i]);//输入时计算最大值
	}
	int ans=0;
	for(int i=0;i<s.size();i++){
		ans+=val[s[i]-'a'+1]*(i+1);//计算
	}
	for(int i=0;i<k;i++){
		ans+=t*(i+s.size()+1);//加最大值计算
	}
	cout<<ans;
	return 0;
}
```


最后吐槽一句洛谷 RMJ。

---

## 作者：JacoAquamarine (赞：0)

随机跳题跳到的，写篇题解吧

### 题意

给定字符串 $s$，和每个字母的价值，问你在字符串后再增加 $k$ 个字符后能获得的最大价值。

- 题目中定义价值为 $\sum_{i=1}^{len} i \times W_{S_i}$。

### 思路

仔细观察发现题目不难，是个贪心，找出这些价值中的最大值，然后拿最大值进行计算，最后注意要乘上 $W_i$。

### Code

```cpp
#include<iostream>
#include<string>
using namespace std;
string str;
int k,a[30],ans,maxn=-2147483647;
int main(){
	cin>>str>>k;
	for(int i=1;i<=26;i++){
		cin>>a[i];
		maxn=max(a[i],maxn);
	}
	for(int i=1;i<=str.size();i++){
		ans+=(i+1)*a[s[i]-'a'];
	}
	for(int i=1;i<=k;i++){
		ans+=maxn*(i+str.size());
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Morax2022 (赞：0)

# CF447B 题解
**Solution**

基本就是贪心，先扫一遍原来的字符串，按照题目所说，乘上其 $w_i$ 就行了。

而后加的部分要求价值最大，先在 $26$ 个字母中找出价值最大的，剩下全选它。
# AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int val[27], mx = 0, ans = 0, k; //val存字母价值 
int main()
{
	cin >> s >> k;
	for (int i = 1; i <= 26; i++)
	{
		cin >> val[i];
		mx = max(mx, val[i]); //求价值最大的字母 
	}
	for (int i = 0; i < s.size(); i++) {ans += (i + 1) * val[s[i] - 96];} //原来字母的价值总和 
	cout << ans + mx * (s.size() + 1 + s.size() + k) * k / 2;
	//因为后面全取价值最大的字母，所以价值总和应为 mx * (s.size() + 1) + mx * (s.size() + 2)...
	//mx * (s.size() + k) = mx * (s.size() + 1 + s.size() + 2 + ... + s.size() + k) =
	//mx * (s.size() + 1 + s.size()) * k / 2。  
}
```
希望本题解能给大家带来帮助！

---

## 作者：Luo_gu_ykc (赞：0)

## 题目大意

给定字符串 $s$，和每个字母的价值，问你在字符串后再增加 $k$ 个字符后能获得的最大价值。

### 注：

价值的定义为： 

 - $Val = \sum_{i = 1}^{len} i \times W_{S_i}$

## 思路

先通过公式求出原序列的价值，再在字母价值里找价值最大的，再计算这个字母插入到原序列 $k$ 次后产生的总价值，最后统计价值即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long // 不开 long long 见祖宗
const int N = 35;
int k, a[N], maxi = LLONG_MIN, ans = 0;
map<char, int> cnt; // 这里用的是 map 映射
string s;
signed main(){
	cin >> s >> k;
	for(char i = 'a'; i <= 'z'; i++){
		cin >> cnt[i]; // 每个字母的价值
		maxi = max(maxi, cnt[i]);
	}
	for(int i = 0; i < s.size(); i++){
		ans = ans + cnt[s[i]] * (i + 1); // 计算价值
	}
	for(int i = s.size() + 1; i <= s.size() + k; i++){
		ans = ans + maxi * i; // 计算后插入的价值
   	}
	cout << ans;
	return 0;
}

```

---

## 作者：Eason_AC (赞：0)

## Content
有一个长度为 $n$ 的仅含小写字母的字符串 $s$ 以及 26 个英文小写字母的价值 $W_\texttt{a},W_\texttt{b},...,W_\texttt{z}$，请求出在后面插入 $k$ 个小写字母后所能够获得的最大价值。

对于一个长度为 $x$ 的字符串 $s'$，它的价值为 $\sum\limits_{i=1}^x i\times W_{s'_i}$。

**数据范围：$1\leqslant n\leqslant 1000,0\leqslant k\leqslant 1000,0\leqslant W_{\texttt{a}\sim\texttt{z}}\leqslant 1000$。**
## Solution
没插入前的 $s$ 的价值很好算，直接按照题目要求加就好了。

至于插入后的就要看字母价值中最大的那个了，因为根据样例来看，这道题是允许你重复加入同样的小写字母，所以我们找到最大的字母价值然后再插入 $k$ 次，注意，插入的字母位置是从 $n+1$ 标号到 $n+k$ 的，所以通过等差数列求和公式可得插入后的字符的总价值为 $\dfrac{(n+1+n+k)\times k\times\max\{W_{\texttt{a}\sim\texttt{z}}\}}{2}=\dfrac{(2n+k+1)\times k\times\max\{W_{\texttt{a}\sim\texttt{z}}\}}{2}$。

最后将插入的字符的价值加入到原来的价值里面就是我们想要的答案了。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstring>
using namespace std;

string s;
long long k, val[27], maxi, ans;

int main() {
	cin >> s;
	scanf("%d", &k);
	for(int i = 1; i <= 26; ++i) {scanf("%d", &val[i]); maxi = max(maxi, val[i]);}
	long long len = s.size();
	for(long long i = 0; i < len; ++i) ans += (i + 1) * val[s[i] - 'a' + 1];
	ans += (2 * len + k + 1) * k * maxi / 2;
	printf("%lld", ans);
	return 0;
}
//貌似不需要开 long long（
```

---

## 作者：LRL65 (赞：0)

思路：

首先，这个字符串可以分成两个部分：**原有的和后加的。** 答案只要把它们加在一起就行了。


------------


### 1. 原有的：

这个部分比较简单，只要将字符串扫一遍，然后乘上 $w_i$ ，最后加起来就行了。

这个部分的代码：

```cpp
	for(int i=0;i<s.size();i++) ans+=(i+1)*w[s[i]-'a'+1];
```

### 2. 后加的：

**要想它最后的价值最大，那加的字母的价值肯定得是最大的**。

这样我们先找出26个字母中价值最大的字母，然后加上 $k $ 个。

那么这个部分的价值应为(maxn为最大字母的价值）：

$maxn*(s.size()+1)+maxn*(s.size()+2)+……+maxn*(s.size()+k)$

然后提取公因数maxn，变为：

$maxn*[ (s.size()+1)+(s.size()+2)+……+(s.size()+k)]$

然后我们在运用等差数列的求和公式（（首项+末项）*项数/2），得：

$maxn*[(s.size()+1)+(s.size()+k)]*k/2 $



------------

最终的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int k,w[30],maxn=0,ans; 
int main() { 
	cin>>s>>k;
	for(int i=1;i<=26;i++) {//输入以及找最大
		cin>>w[i];
		maxn=max(maxn,w[i]);
	}
	for(int i=0;i<s.size();i++) ans+=(i+1)*w[s[i]-'a'+1];//原来的
	cout<<ans+maxn*((s.size()+1)+(s.size()+k))*k/2<<endl;	
	return 0;
}
```


---

