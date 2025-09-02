# The Fair Nut and String

## 题目描述

The Fair Nut found a string $ s $ . The string consists of lowercase Latin letters. The Nut is a curious guy, so he wants to find the number of strictly increasing sequences $ p_1, p_2, \ldots, p_k $ , such that:

1. For each $ i $ ( $ 1 \leq i \leq k $ ), $ s_{p_i} = $ 'a'.
2. For each $ i $ ( $ 1 \leq i < k $ ), there is such $ j $ that $ p_i < j < p_{i + 1} $ and $ s_j = $ 'b'.

The Nut is upset because he doesn't know how to find the number. Help him.

This number should be calculated modulo $ 10^9 + 7 $ .

## 说明/提示

In the first example, there are $ 5 $ possible sequences. $ [1] $ , $ [4] $ , $ [5] $ , $ [1, 4] $ , $ [1, 5] $ .

In the second example, there are $ 4 $ possible sequences. $ [2] $ , $ [3] $ , $ [4] $ , $ [5] $ .

In the third example, there are $ 3 $ possible sequences. $ [1] $ , $ [3] $ , $ [4] $ .

## 样例 #1

### 输入

```
abbaa
```

### 输出

```
5```

## 样例 #2

### 输入

```
baaaa
```

### 输出

```
4```

## 样例 #3

### 输入

```
agaa
```

### 输出

```
3```

# 题解

## 作者：Super_Cube (赞：5)

# 题目大意：

一句话：给你一个字符串，求出有几个形如 $"a"$ 或 $"aba \ldots aba"$ 的子序列。

# 思路：

定义 $ans$ 为从字符串开始到当前位置能构造出的子序列总数。

可以想到，只有当前你枚举到字符串里的字符为 $"a"$ 时，才能构造出需要的子序列。

分情况讨论当前 $"a"$ 能构造出的子序列：

1. 形如 $"a"$ 的子序列。

这个简单，直接将 $ans$ + $1$ 。

2. 形如 $"aba \ldots aba"$ 的子序列。

为了形成这样的子序列，我们需要找到离当前 $"a"$ 最近的一个 $"b"$ 。在这个 $"b"$ 之前能得到的所有答案都可以与当前的 $"a"$ 构成需要的子序列。

这样的话，$ans$ += 最近的 $"b"$ 之前能得到的所有答案。

### 所以：

当我们遇到一个 $"a"$ 时，$ans$ += $1$ + 最近的 $"b"$ 之前能得到的所有答案。

---

可能有人会问，最近的 $"b"$ 之前能得到的所有答案怎么求呢？

你可以拿一个变量 $x$ 把它记录下来嘛，每次遇到一个 $"b"$ 时，让 $x$ = 当时的 $ans$ 就好啦。

遇到 $"a"$ 时就让 $ans$ += $x$ + $1$ ，多么明了啊。

---

**注意取模哦！别忘了这一点。**

---

# Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
int ans,x;
int main(){
	cin>>a;
	for(int i=0;i<a.size();i++){
		if(a[i]=='a')ans=(ans+x+1)%1000000007;
		if(a[i]=='b')x=ans;
	}cout<<ans;
	return 0;
}
```

---

## 作者：cqbztz2 (赞：3)

# [题目传送门](https://www.luogu.com.cn/problem/CF1084C)

# 题意：

问给定的字符串有多少形如 $ "a","aba","ababa"... $ 的子串。

# 题解：

乘法原理 $ + $ 加法原理

- 这题需要考虑将字符 $ "b" $ 做分隔符，把每个含 $ "a" $ 不含 $ "b" $ 的区间分隔开,那么就很好解决了。

对于第一个区间的 $ "a" $，它只能选自己，所以它的选法就是这个区间 $ "a" $ 的数量。对于第二个区间，它有两种选择，一种是与上一个区间的子串结合，还有一种是不与前面的结合，只选自己，那么选法就是这个区间的 $ "a" $ 的数量乘以上一个区间所有符合条件的子串数量再加上这个区间的 $ "a" $ 的数量。对于第三个区间，也是两种选法，所以说从左到右每个区间可以形成的子串数量可以根据前面的结果递推出来，最终的结果就是所有区间可以形成的子串数量之和。

# 代码：

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  long long ans,sum,mod=1e9+7;
  string s;
  int main(){
      cin>>s;
      s[s.length()]='b';
      for(int i=0;i<=s.length();i++){
          if(s[i]=='a'){
              sum++;
          }
          else if(s[i]=='b'&&sum!=0){
              ans=((ans+ans*sum+sum)%mod+mod)%mod;
              sum=0;
          }
      }
      cout<<ans;
      return 0;
  }
```


---

## 作者：lhjy666 (赞：3)

```cpp
#include<bits/stdc++.h>
#define ll long long
#define MOD 1000000007
using namespace std;
char a[1000005];
int main()
{
	int ans=0;
	scanf("%s",a);
	int l=strlen(a),t1=0,t2=0;
	for (int i=l-1;i>=0;i--)
	{
		if(a[i]=='a')
		{
			t1++;
			t1+=t2;
			t1=t1%MOD;
			ans+=t2+1;
			ans=ans%MOD;
		}
		if(a[i]=='b')
		{
			t2+=t1;
			t2=t2%MOD;
			t1=0;
		}
	}
	printf("%d",ans%MOD);
	return 0;
}
```

---

## 作者：fengqiao17 (赞：2)

## Solution

定义 $cnt$ 为能构造出的子序列总数，分情况讨论 $a$ 能构造出的子序列：

1. $|s|=1$，直接将 $cnt$ 加一；
2. $|s|>1$，我们可以发现，在最近的一个 $b$ 之前能得到的所有答案都可以与当前的 $a$ 构成子序列，即 $cnt$ 加上最近的 $b$ 之前能得到的所有答案就可以了。

### 坑点！！

1. 取模：每次要模 $10^9+7$，可以定义常量 $p$；
2. 答案：类似于前缀和，每次遇到 $b$，让变量 $x$ 记录当时的 $cnt$ 即可。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int p = 1e9 + 7; //模数
int cnt, x; //答案以及记录器
string s;
int main() {
  cin >> s;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == 'a') {
      cnt = (cnt + x + 1) % p; //1和x对应上述两种情况
    } else if (s[i] == 'b') {
      x = cnt; //记录
    } else {
      continue;
    }
  }
  cout << cnt;
  return 0;
}
```

---

## 作者：oneman233 (赞：2)

找子序列的总数可以用这样的一种思路：

对于目前所有的答案ans当中的每一种情况，可以在它们的基础上增加当前的元素，那么对答案的贡献就是ans种，但是不要忘了考虑自己本身作为一种元素的情况，所以对答案的贡献应该是ans+1

代码中now储存目前有多少个可用的元素，一旦出现了b那么之前所有的a都可以对答案有贡献，更新答案就按照上面的说法即可

主函数如下：
```cpp
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>s;
    int ans=0,now=0;
    fo(i,0,s.length()){
		if(s[i]=='b') now=ans;
		else if(s[i]=='a') ans=(ans+now+1)%MOD;
	}
	cout<<ans;
    return 0;
}
```


---

## 作者：老官童鞋gogo (赞：1)


**在[我的博客](http://laoguantx.nov.vin/?p=102)更好的阅读！**

------------

## 题目理解与强调：

- 这道题目含有一条只包含小写字母的字符串。

- 要求能够找到多少个**子序列**满足形式 $ a,b,\ldots,a,b $


------------


## 思路分析：
这道题是一道计数题。

很简单地，我们可以得出结论：题目的答案与字符串 $ s $ 中的 '$ a,b,\ldots,a,b $' 的数量与位置有关，当我们读取到 '$ a $' 时，首先要在答案的基础上 $ +1 $ ，因为**我们可以让它单独成为一个形如 '$ a $' 的子序列**。同时可以构成 $ sum $ 个形如 '$ a,b,\ldots,a,b $ '的序列， $ sum $ 就是距离这个 '$ a $' 最近的 '$ b $' 之前所有满足形式的子序列个数，**因为我们可以通过这个 '$ b $' 与之前的所有子序列合起来构成一个新的子序列**。所以，在读取字符是读到 '$ b $' 时，将一个变量 $ p $ 赋值为 $ sum $ ，当读取到 '$ a $' 时，将 $ sum $ 加上 $ p+1 $ ，最后输出结果。


------------

## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#include<set>
using namespace std;
#define ll long long
#define pb(x) push_back(x)
#define mp(a,b) make_pair(a,b)
#define fi first
#define se second
#define pr(x) cerr<<#x<<"="<<(x)<<endl
#define pri(x,lo) {cerr<<#x<<"={";for (int ol=0;ol<=lo;ol++)cerr<<x[ol]<<",";cerr<<"}"<<endl;}
#define inf 100000000
#define N 1000
template<class T>inline void read(T &x)
{
    x=0;register char c=getchar();register bool f=0;
    while(!isdigit(c))f^=c=='-',c=getchar();
    while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
    if(f)x=-x;
}
template<class T>inline void print(T x)
{
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10);
    putchar('0'+x%10);
}
int main()
{
	register char c;
	register int sum=0,p=0;
	while(c=getchar())
	{
		if(c<'a'||c>'z')	break;
		if(c=='a')	sum=(sum+p+1)%1000000007;
		if(c=='b')	p=sum;
	}
	print(sum);
	return 0;
}
```


390ms&nbsp; 3.57MB



---

## 作者：liaoz123 (赞：0)

认真观察即可。

发现答案可以分为两类：

- 单个字母 $\texttt a$，这种情况贡献为 $1$。
- 形式为 $\texttt ababa$ 等的，假设当前扫描到一个字符 $\texttt a$，观察发现最近的 $\texttt b$ 前面的所有合法子序列均可以和当前的 $\texttt a$ 构成一个新的合法子序列。那么令最近一个 $\texttt b$ 之前的合法序列数量为 $pre$，那么这种情况贡献为 $pre$。遇到 $\texttt b$ 的时候记录一下即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
typedef long long ll;
ll ans,pre;
const ll mod=1e9+7;
int main(){
	cin>>a;
	int len=a.length();
	for(int i=0;i<len;i++){
		if(a[i]=='a')
		ans=(ans+pre+1)%mod;
		if(a[i]=='b')
		pre=ans;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：E1_de5truct0r (赞：0)

本题要用到的知识：~~输入输出、dp~~、前缀和、双指针，不会的同学可以去 OIwiki ~~颓废~~ 学习一下。

## 思路

假设输入的字符串为 $s$ 数组。

看到这道题目，~~显然不能贪心去做，因为我没想到很好的策略。~~ 我其实一开始没思路，后来意识到这可以用类似最大子段和的 dp 定义：$dp_i$ 表示最后一个选 $i$ 这个位置的字符的合法子串数。显然，只有在 $s_i$ 是 ```'a'``` 这个字符的时候才会转移。

- 先考虑暴力转移：每次从 $i$ 向前找到离 $i$ 最近的点 $j$ 使得 $s_j$ 是 ```b```，然后一直找到这个位置之前的第一个 ```a``` 的位置，记为 $j$。 那么都可以转移到 $1...j$ 的这些 ```a``` ，所以 $dp_i = \sum^j_{k=1} dp_k$。最后记得再加上自身本身作为一个合法字符串的情况。

	所以暴力转移方程为：

$$dp_i = \sum^j_{k=1} dp_k + 1$$

但是这样做复杂度是 $O(n^2)$，妥妥 T 出银河系。

- 所以来考虑优化：

	优化一：$O(1)$ 找到上文的“点 $j$”。我们可以用 $lst_i$ 表示 $i$ 前面最近的 $a$ 的位置。那么可以双指针来做。这个应该属于双指针比较基础的操作，我就不再多说了。这样每次到 $i$ 这个点，直接用 $lst_i$ 代替 $j$，就完成了 $O(1)$ 的操作。
    
	优化二：$O(1)$ 求出 $\sum^j_{k=1} dp_k$。~~这个是很 sb 的操作~~ ，显然前缀和维护即可。
    
最后转移方程就变成了：

$$dp_i=pre_{lst_i}$$

$$pre_i = pre_{i-1}+dp_i$$

其中 $lst$ 含义见上，$pre$ 是前缀和数组。最后输出显而易见，是 $\sum^n_{i=1} dp_i$。

然后就成功地 $O(n)$ 解决此问题了！

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod=1000000007;
char s[100005];
int dp[100005],pre[100005],lst[100005];
inline int Mod(int x){return x>=mod?x-mod:x;} // 因为只有加法，这样比取模快的多，算是小卡常
int main()
{
	scanf("%s",s+1);
	int n=strlen(s+1),lstt=0,lsta=0,l=1,r=0;
	while(r<=n)
	{
		r++;
		if(s[r]=='b')
		{
			lstt=lsta;
			while(s[r]=='b' && r<=n) r++;
		}
		if(s[r]=='a') lst[r]=lstt,lsta=r;
	}//双指针求 lst[i]
	
	int st=1;
	while(s[st]=='b') st++; // 去掉开头的 'b'（虽然没啥用）
	for(int i=st;i<=n;i++)
	{
		if(s[i]=='a')
			dp[i]=Mod(pre[lst[i]]+1); //转移
		pre[i]=Mod(pre[i-1]+dp[i]); //这句话千万不要放到 if 里，否则 pre 将会不连续影响结果。
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		ans=Mod(dp[i]+ans); // 由于我们 dp 的定义，答案要对 1~n 求和。
	printf("%d",ans);
	return 0;
}
```

整体来说这道题思维难度很低，只有那个双指针求 lst 比较细节，有点代码上的难度。

$$\large\text{----------- THE END -----------}$$

$$\text{thanks for reading.}$$

---

## 作者：mszyyds (赞：0)

这题居然是个蓝题！！！
## 思路
先说一下，比较麻烦，因为最开始读错题了，后来就将错就错了（裂幵。

用两个数 $num1num2$ 来记录以 $a$ 和以 $b$ 结尾的个数，每次遇见 $a$ 就更新 $numa$ 的值，推得            $numa=numa+numb+1$ (详见代码注释）那就直接上代码吧。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int numa,numb;
bool f=true;
char s[100005];
signed main()
{
	cin>>(s+1);
	int n=strlen(s+1);
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='a')
		{
			numa=(numa/*原来的*/+numb/*结尾为当前这个a的长度>1的子序列数*/+1/*单独这个a组成的子序列*/)%1000000007;//别忘了mod 
			f=false;
		}
		if((!f)&&s[i]=='b')
		{
			numb=numa;
			f=true;
		}
	} 
	cout<<numa%1000000007;
	return 0;
}

---

