# The Number Of Good Substrings

## 题目描述

You are given a binary string $ s $ (recall that a string is binary if each character is either $ 0 $ or $ 1 $ ).

Let $ f(t) $ be the decimal representation of integer $ t $ written in binary form (possibly with leading zeroes). For example $ f(011) = 3, f(00101) = 5, f(00001) = 1, f(10) = 2, f(000) = 0 $ and $ f(000100) = 4 $ .

The substring $ s_{l}, s_{l+1}, \dots , s_{r} $ is good if $ r - l + 1 = f(s_l \dots s_r) $ .

For example string $ s = 1011 $ has $ 5 $ good substrings: $ s_1 \dots s_1 = 1 $ , $ s_3 \dots s_3 = 1 $ , $ s_4 \dots s_4 = 1 $ , $ s_1 \dots s_2 = 10 $ and $ s_2 \dots s_4 = 011 $ .

Your task is to calculate the number of good substrings of string $ s $ .

You have to answer $ t $ independent queries.

## 样例 #1

### 输入

```
4
0110
0101
00001000
0001000
```

### 输出

```
4
3
4
3
```

# 题解

## 作者：Miracle_1024 (赞：5)

## 思路：

### 大概题意：
   给你 $t$ 个 $01$ 串，求 $01$ 串中有多少个子串转化成十进制以后等于这个子串的长度。

### 解题：
  看题以后发现可以暴力枚举，然后发现如果 $0$ 的话是不会影响的，因为这一位转化后也是 $0$。所以按照二进制从后往前逐个枚举就行，最长的长度为 $\log_2len$，时间复杂度为 $O(n \log n)$。


## 代码：


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+10;
const int INF=0x3f3f3f3f;
inline int read(){ll x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
ll t,a[N],ans,poww;
string s;
int main(){
	cin>>t;
	while(t--){
		ans=0;
		cin>>s;
		a[s.size()]=s.size();
		for(int i=s.size()-1;i>=0;i--){
			if(s[i]=='1')a[i]=i;
			else a[i]=a[i+1];
		}
		for(int i=0;i<s.size();i++){
			poww=0;
			for(int j=a[i];j<s.size();j++){
				poww*=2;
				if(s[j]=='1')poww++;
				if(poww>s.size())break;
				if(j-i+1==poww)ans++;
			}
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：Dream_poetry (赞：3)

题意：一个 $01$ 串，求有多少个二进制子串所对应的十进制值与它的长度相等。

思路：因为只有出现 $1$ 的时候才会改变对应的十进制值，所以每次从每一个 $1$ 往后来判断每个子串是否满足题意即可（即暴力枚举）,时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a[100005];
long long ans;
string b;

int main(){
    cin>>t;
    while(t--){
        cin>>b;
        int n=b.size(),now=n;
        ans=0;
        for(int i=n-1;i>=0;--i){
            if(b[i]=='1')
                now=i;
            a[i]=now;
        }
        for(int i=0;i<n;++i){
            int num=0;
            for(int j=a[i];j<n;j++){
                num*=2;
                if(b[j]=='1')
                    num++;
                if(num==j-i+1)  
                    ans++;
                if(num>n)
                    break;
            }
        }
        cout<<ans<<endl;
    }
	return 0;
```


---

## 作者：兮水XiShui丶 (赞：1)

通过读题,我们可以发现一个很重要的东西:$\sum_{i=1}^t len_i<=2*10^5$.

通过这个性质,我们可以发现,我们在枚举每一次的区间时,这个区间的最长长度为$log_2len$.  

然后就做完了??  

我们枚举一下每个区间的左/右端点,然后直接暴力统计答案就好了.  

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;
const int N = 200000 + 10;
int t,nex[N];
char s[N];
int main() {
    scanf("%d",&t);
    while(t--) {
        scanf("%s",s+1);
        int n=strlen(s+1);
        nex[n+1]=n+1;
        for(int i=n;i>=1;i--) {
            if(s[i]=='0') nex[i]=nex[i+1];
            else nex[i]=i;
        }
        int ans=0;
        for(int i=1;i<=n;i++){
            int now=0;
            for(int j=nex[i];j<=min(n,nex[i]+20);j++){
                now=now*2+s[j]-'0';
                if(now==j-i+1) ans++;
            }
        }
        printf("%d\n", ans);
    }
}
```

---

## 作者：liyp (赞：0)

## 思路
很简单的二进制题目。

看到题目，大多数人的第一反应就是暴力枚举子串的头尾，假设这个二进制串的长度为 $N$，这种做法要循环 $N^2$ 遍，在 $N$ 为 $2\times10^5$ 的情况下肯定是过不了的。

考虑优化。分析题目后我们不难发现，题目要求我们找到这个二进制数的一个子串，使得子串长度等于子串的十进制数，但数据范围中一个子串的长度是小于等于 $2 \times 10 ^ 5$ 的，而 $2 \times 10 ^5$ 这个数在二进制当中只有十八位，因此我们在枚举头尾时，从一个位置上为 `1` 的位置开始，只需要向后遍历 $18$ 位即可。

```cpp
for (int i = 0; i < s.size(); i++) {
    int flag = 1, c = 0;
    for (int j = i; j <= i + 18 + c && j < s.size(); j++) {
        if (flag) {
            if (s[j] == '0') c++;
            else flag = 0;
            }
            if ((j - i + 1) == ejz(i, j)) {
            ans++;
        }
    }
}
```

看到这里，聪明的你肯定写出了一份代码，高高兴兴地交上去，然后……

![404](https://img.picui.cn/free/2024/08/19/66c2f6192b328.png)

聪明的出题者专门出了数据来卡了这种做法。卡的方法也很简单：前面我们说过，我们只能从 `1` 的位置向后遍历 $18$ 位，但对于一个符合要求的子串，它可能存在许多个前导零，这会浪费掉许多循环的次数。出题者只需要出一个像 ``00000000000001`` 这种类型的数据，就可以轻松卡掉我们。

再次考虑优化，刚刚我们已经说了，超时的原因是因为大量的前导零。可如果我们在遍历到一个前导零时就可以自动跳到下一个为 `1` 的位置，问题不就解决了？

考虑定义一个数组 $a$，$a_i$ 代表在二进制串第 $i$ 为开始下一个为 `1` 的位置（可以就为 $i$）。这样，我们只需要稍微做一些改动，自动跳过前导零，就可以解决这个问题。

```cpp
for (int i = 0; i < s.size(); i++) {
    for (int j = a[i]; j < s.size() && j < a[i] + 18; j++) {
        if (ejz(i, j) == j - i + 1) {
            ans++;
        }
    }
}
```
## 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 10;
int a[MAXN];
string s;
int ejz(int l, int r) {
    int sum = 0;
    for (int i = a[l]; i <= r; i++) {
        sum *= 2;
        if (s[i] - '0') sum++;
    }
    return sum;
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> s;
        memset(a, 0, sizeof(a));
        a[s.size()] = s.size();
        for (int i = s.size() - 1; i> -1; i--) {
            if (s[i] == '1') {
                a[i] = i;
            }
            else a[i] = a[i + 1];
        }
        int ans = 0;
        for (int i = 0; i < s.size(); i++) {
            for (int j = a[i]; j < s.size() && j < a[i] + 18; j++) {
                if (ejz(i, j) == j - i + 1) {
                    ans++;
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：minVan (赞：0)

**解题思路**

给定一个 $01$ 串，求有多少个子串使得其所对应的二进制数的值等于子串长度。

**解题思路**

显然，每个子串的值与其有多少个 $1$ 有关，所以记录每个 $1$ 的位置，然后往前枚举看是否满足条件即可。时间复杂度 $\mathcal{O}(n\log n)$。

**AC 代码，请勿抄袭。**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int a[N];
long long ans;
signed main() {
    int t;
    cin >> t;
    while(t--) {
        string s;
        cin >> s;
        int n = s.size();
        for(int i = n - 1, t = n; i >= 0; i--) {
            if(s[i] == '1') { t = i; }
            a[i] = t;
        }
        ans = 0;
        for(int i = 0; i < n; i++) {
            int t = 0;
            for(int j = a[i]; j < n; j++) {
                t <<= 1;
                if(s[j] == '1') { ++t; }
                if(t == j - i + 1) { ++ans; }
                if(t > n) { break; }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：QWQ_123 (赞：0)

口胡题解。

设 $ne_i$ 表示在 $[i, n]$ 的数中第一个是 $1$ 的位置。

那么显然 $[i,ne_i]$，此时 $f=1$，然后由于每一次往后取 $f$ 都至少乘 $2$，所以至多取 $\log_2 n$ 次 $f$ 便 $>n$，那么直接退出即可。

时间复杂度 $O(n \log n)$。

---

## 作者：弦巻こころ (赞：0)

题意:给你一个有01字符串组成的二进制串. 现在我们要求满足条件的子串个数. 条件为:r-l+1=这个子串所对应的十进制值.

如$011_2$=$3_{10}$ 长度也为3. 它就满足条件.

思路:一看到数据范围 $n$<=$2*10^5$就知道算法时间复杂度是$O(n)$或者$O(nlogn)$,但怎么做呢?由于只有1才能改变式子的值.我们就循环去扫.看1及距离上个1中间隔了多少个0,然后再向后扫.如果这个值在长度范围内,ans就++,如果不在就break掉.这样最多向后扫logn次所以时间复杂度为$O(nlogn)$

代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,len,ans,num;
char s[200005];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		ans=0,len=0;
	 	scanf("%s",s);
	 	int n=strlen(s);
	 	for(int i=0;i<n;i++)
	 	{
	 		len++;
	 		if(s[i]=='1')//如果是一就向后扫
	 		{
	 			int len1=len;
	 			len=0;//将距离上个1有多少个0清零
	 			ans++;//它本身也可以作为答案
	 			num=1;
	 			for(int j=i+1;j<n;j++)
	 			{
	 				len1++;
	 				if(s[j]=='0')
	 				{
	 					num*=2;
	 				}
	 				if(s[j]=='1')
	 				{
	 					num*=2;
	 					num++;
	 				}
	 				if(num<=len1)//如果这个值在长度范围内
	 				{
	 					ans++;
	 				}else
	 				{
	 					break;
	 				}
	 			}
	 		}
	 	}
	 	cout<<ans<<endl;//输出答案
	}
}
```


---

## 作者：ylch (赞：0)

# CF1217C The Number Of Good Substrings 题解

[题目传送门-](https://www.luogu.com.cn/problem/CF1217C)

### 题目大意

给定一个 01 字符串，定义一个子串为好串，则该串满足串的长度等于串代表的十进制数，求出串的子串中好串的个数。

### 解题思路

数据范围为 $2 \times 10^5$，故与长度相等的二进制数最多有 $18$ 位（$0011 \text{ } 0000 \text{ } 1101 \text{ } 0100 \text{ } 0000_2$）。

数据范围很小，可以自由发挥（暴力/枚举）。

从头开始枚举，记录前导 $0$ 个数，若某个数对应的长度不够，则可以由前导 $0$ 来补充。

通过验证，符合要求的子串一定是由 $1$ 开头的，所以每次枚举到 $1$ 时就计算当前位置到末尾满足条件的子串个数，别忘了重置前导 $0$ 个数。

如何判断子串是否满足要求？原题面中有一句话：

> The substring $s_{l},s_{l+1},\dots,s_{r}$ is good if $r - l + 1 = f(s_l \dots s_r)$.

大体意思是如果 $r-l+1$ 和 $f(s_l \cdots s_r)$ 相等的话，这就是一个好串，主要解法这不就出来了吗？

还可以进行剪枝（优化）一下，如果 $r+1$ 比 $s$ 的长度长，那么一定怎么凑都凑不出来了，直接退出开始下一轮。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	string s;
	int T;
	for (cin >> T; T--; )
	{
		cin >> s;
		int ans = 0, pre = 0;
		for (int i=0; i<s.size(); i++)
		{
			if (s[i] == '0')	pre++;
			else
			{
				int r = i, cur = 1;
				for (int j=1; j<=18; j++)
				{
					if (cur <= pre+(r-i+1))	ans++;
					if (r+1 >= s.size())	break;
					cur = cur*2 + (s[++r] - '0');
				}
				pre = 0;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```

题解到此完毕，有错误和疑问欢迎指出，感激不尽！

参考文章 [Codeforces 1217 C. The Number Of Good Substrings 暴搜](https://blog.csdn.net/qq_42397248/article/details/100581449)

End
------------------

管理员大大辛苦啦~

谢谢大家！我们一起进步，一起 $rp++$！

---

## 作者：开始新的记忆 (赞：0)

题目大意：（额这里不太好描述，见谅）给你一个二进制串，设为s1,s2,s3……sn，问其中有多少个字串满足i，j（i<=j）使得si*2^(j-i)+si+1*2^(j-i-1)+……+sj*2^1=j-i+1。

大致思路：每次满足题意的字串都是以1开头的，我们只需每次都从每个1往后来判断每个子串是否满足题意即可，这里有一个剪枝就是当当前的大小如果大于了n那么就不肯能会有答案。最坏的时间复杂度在O(1000*(1000*log1000))左右，就是全为1的情况。


```
#include<bits/stdc++.h>
using namespace std;
int t,a[200005];
long long ans;
string b;
 
int main()
{	cin>>t;
	while(t--)
	{
		cin>>b;
		int n=b.size(),now=n;
        ans=0;
        for(int i=n-1;i>=0;--i)
		{
            if(b[i]=='1')
				now=i;
            a[i]=now;
        }
        for(int i=0;i<n;++i)
		{
            int num=0;
            for(int j=a[i];j<n;j++)
			{
                num*=2;
                if(b[j]=='1')
					num++;
                if(num==j-i+1)	
					ans++;
                if(num>n)
					break;
            }
        }
        cout<<ans<<endl;
    }
	return 0;
}
```


---

