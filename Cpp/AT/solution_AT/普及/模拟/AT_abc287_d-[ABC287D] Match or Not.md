# [ABC287D] Match or Not

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc287/tasks/abc287_d

英小文字と `?` からなる文字列 $ S,T $ が与えられます。ここで、$ |S|\ \gt\ |T| $ が成り立ちます(文字列 $ X $ に対し、 $ |X| $ で $ X $ の長さを表します)。

また、$ |X|=|Y| $ を満たす文字列 $ X,Y $ は、次の条件を満たすとき及びそのときに限り**マッチする**といいます。

- $ X,Y $ に含まれる `?` をそれぞれ独立に好きな英小文字に置き換えることで $ X $ と $ Y $ を一致させることができる
 
$ x=0,1,\ldots,|T| $ に対して次の問題を解いてください。

- $ S $ の先頭の $ x $ 文字と末尾の $ |T|-x $ 文字を順番を保ったまま連結することで得られる長さ $ |T| $ の文字列を $ S' $ とする。$ S' $ と $ T $ がマッチするならば `Yes` と、そうでなければ `No` と出力せよ。

## 说明/提示

### 制約

- $ S,T $ は英小文字と `?` からなる文字列
- $ 1\ \leq\ |T|\ \lt\ |S|\ \leq\ 3\ \times\ 10^5 $
 
### Sample Explanation 1

$ x=0 $ の場合、$ S' $ は `?c` となります。ここで、$ S' $ の $ 1 $ 文字目の `?` を `b` に、$ T $ の $ 2 $ 文字目の `?` を `c` に置き換えることで $ S' $ と $ T $ を一致させることができるため、$ S' $ と $ T $ はマッチします。このため、$ 1 $ 行目の出力は `Yes` です。 $ x=1,2 $ の場合は $ S' $ はそれぞれ `ac`、`a?` であり、$ T $ とマッチしません。このため、$ 2,3 $ 行目の出力は `No` です。

## 样例 #1

### 输入

```
a?c
b?```

### 输出

```
Yes
No
No```

## 样例 #2

### 输入

```
atcoder
?????```

### 输出

```
Yes
Yes
Yes
Yes
Yes
Yes```

## 样例 #3

### 输入

```
beginner
contest```

### 输出

```
No
No
No
No
No
No
No
No```

# 题解

## 作者：泥土笨笨 (赞：7)

看到很多大佬的做法用了前缀和，其实没必要，按照题目的描述模拟即可。在模拟的过程中，对比上一次要求的，和这一次要求的之间的差异。单独计算一下差异对答案的影响就行了。

首先先定义“匹配”：字符串 $s$ 中 $i$ 位置上的字符 $s_i$ 和字符串 $t$ 中 $j$ 位置上的字符 $t_j$ 匹配，当且仅当 $s_i$ 或者 $t_j$ 至少有一个是问号。或者这两个字符相等。

最开始第一次询问，要求 $t$ 和 $s$ 中长度相等的后缀匹配，为了描述方便，这里假设 $s$ 长度为 $6$，$t$ 长度为 $3$，把要求匹配的字符画出来：

![](https://cdn.luogu.com.cn/upload/image_hosting/v2ow1kta.png)

如图，第一次是最上面的情况，$t$ 跟 $s$ 的最后三个位置配对。此时我们可以计算出来，这三个对应的位置，有多少对位置是不匹配的，把不匹配的数量记到 $cnt$ 变量里面。如果 $cnt$ 是 $0$，此时可以输出 `Yes` ，否则输出 `No`。这次计算是 $O(n)$ 复杂度的，计算量等于 $t$ 的长度。

观察图中间的第二种情况，这时候其实就是把 $t$ 中第一个字符，要尝试匹配的元素变了，从原来的位置，变成 $s$ 中的第一个字符。用深蓝色表示。因为只有一个位置变了，我们很容易计算出 $cnt$ 的新值，这个维护工作量只是把旧的匹配的影响减掉，加上新的位置的影响，这样我们可以 $O(1)$ 计算出现在的 $cnt$。同理，如果 $cnt$ 是 $0$，此时可以输出 `Yes` ，否则输出 `No`。

同理，第三次，就是把第二条红线，变成图中的黄线。还是可以 $O(1)$ 维护 $cnt$。这样，我们可以在总的 $O(n)$ 复杂度计算答案。

代码：

```cpp
#include <iostream>
#include <cstring>

using namespace std;
typedef long long ll;
const ll MAXN = 3e5 + 5;
const ll MOD = 1e9 + 7;

int sl, tl;
char s[MAXN], t[MAXN];

int main() {
    cin >> s >> t;
    sl = strlen(s);
    tl = strlen(t);
    int cnt = 0;
    for (int i = 0; i < tl; ++i) {
        if (s[sl - tl + i] != '?' && t[i] != '?' && s[sl - tl + i] != t[i]) {
            cnt++;
        }
    }
    if (cnt == 0) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    for (int x = 1; x <= tl; ++x) {
        if (s[x - 1] != '?' && t[x - 1] != '?' && s[x - 1] != t[x - 1]) {
            cnt++;
        }
        if (s[sl - tl + x - 1] != '?' && t[x - 1] != '?' && s[sl - tl + x - 1] != t[x - 1]) {
            cnt--;
        }
        if (cnt == 0) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
```


---

## 作者：bloodstalk (赞：5)

## Description
翻译给的很明白了，就是让你判断 $S$ 串的前 $x(0 \leq x \leq |T|)$ 个字符和后 $|T|-x$ 个字符组成的字符串和 $T$ 串是否相等，其中问号能代替所有字母。 
## Solution
很有意思的一道题。

首先我们可以知道，如果前 $i-1$ 位不能匹配的话，那么第 $i$ 位不管它本身成功匹配与否，整个串是不匹配的。因此，我们可以很自然地想到递推求解(也可以说是前缀和)。

我们设 $pre_i$ 表示 $S$ 串的前 $i$ 位是否和 $T$ 串匹配，设 $suf_i$ 表示 $S$ 串的 $i-|S|$ 位是否和 $T$ 串匹配。等到最后统计答案的时候就判断 $pre_i$ 和 $suf_{|S|-|T|+i+1}$ 是否都能成功匹配即可。

初始值 $pre_0=1$ ，$suf_{|S|+1}=1$ 。

接下来考虑怎么求出 $pre$ 数组，其实也很简单：

- 如果 $pre_{i-1} = 0$ ，那么显然 $pre_i = 0$ ( $0$ 表示匹配不成功， $1$ 表示匹配成功)；

- 如果等于 $1$ ，我们需要判断这一位能不能匹配，有两种可能：
  
  (1)：这一位字母本身就是相等的；
  
  (2)：这两个字母中至少有一个问号。
  
  满足这两个条件，这一位就是匹配的了。

通过这个我们就可以求解这个问题了，$suf$ 数组也是同理，只不过是反过来了。


## Code
```cpp
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define next nxt
#define re register
#define il inline
const int N = 3e5 + 5;
using namespace std;
int max(int x,int y){return x > y ? x : y;}
int min(int x,int y){return x < y ? x : y;}

char s[N],t[N];
int n,m,pre[N],suf[N];

il int read()
{
	int f=0,s=0;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f |= (ch=='-');
	for(; isdigit(ch);ch=getchar()) s = (s<<1) + (s<<3) + (ch^48);
	return f ? -s : s;
}

signed main()
{
	cin >> s+1 >> t+1;
	pre[0] = 1;
	n = strlen(s+1) , m = strlen(t+1);
	for(re int i=1;i<=m;i++) if((s[i] == t[i] || (s[i] == '?' || t[i] == '?')) && pre[i-1]) pre[i] = 1; else pre[i] = 0;
	suf[n+1] = 1;
	for(re int i=n,j=m;i>=n-m+1;i--,j--) if((s[i] == t[j] || (s[i] == '?' || t[j] == '?')) && suf[i+1]) suf[i] = 1; else suf[i] = 0;
	for(re int i=0;i<=m;i++) if(pre[i] == 1 && suf[n-m+i+1] == 1) puts("Yes"); else puts("No");
	return 0;
}
```


---

## 作者：NightStriker (赞：5)

因为本题的数据范围是 $3 \times 10^5$，所以我们必须想出个线性解法。

首先“匹配”的含义是两个字符 $a$ 和 $b$ 相等或者其中有一个为 `?`。

我们可以先正着扫一遍 $T$，再倒着扫一遍，来枚举 $x$。最后看看哪些都同时符合。

这样就以 $\mathcal{O}(1)$ 的时间来计算 $x=0,1,2\cdot\cdot\cdot\cdot,|T|$ 时的答案了。总时间复杂度 $\mathcal{O}(|T|)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
string s,t;
bool a[300001],b[300001];
int main() {
	cin>>s>>t;
	s = " "+s,t = " "+t;//方便操作
	n = s.size();m = t.size();//n 为 |s|，m 为 |t|。
	a[1] = 1,b[m] = 1;//设初值
	for (int i = 1; i<=m; i++){//正着枚举 x 
		if (s[i]==t[i]||s[i]=='?'||t[i]=='?') a[i+1] = 1; 
		else break;//不符合条件则退出。
	} 
	for (int i = m; i>=1; i--){// 倒着枚举 x
		if (s[i+n-m]==t[i]||s[i+n-m]=='?'||t[i]=='?') b[i] = 1;//s 和 t 需要是反的。
		else break;
	}
	for (int i = 1; i<=m; i++) {
		if(a[i]&&b[i]) cout<<"Yes"<<endl;//看看每个是否都符合
		else cout<<"No"<<endl;
	}
	return 0;
}
```



---

## 作者：_JF_ (赞：4)

## [ABC287D] Match or Not 

有意思的简单题.

我们不妨把第一个字符串设为 $a$ 串，第二个设为 $b$ 串。

显然，如果一个 $a$ 串的一个字母有用去组成新的串和 $b$串进行比较，那么只要用到这个字母，他所对应的 $b$ 串的字母就是一样的，不会改变。

很自然想到前缀和。

如果当前 $a$ 串这个字母和 $b$ 串对应字母匹配，那就标记为 $0$，不匹配就标记为 $1$。

由于 $a$ 串需要有两个部分去组成新的字符串比对，所以考虑预处理两个前缀和数组，一个是从后往前，一个是从前往后。

如果当前询问长度为 $i$ 的串，那就是从前往后的长度是 $i$。从后往前的长度就是 $size(b)-i$。

查询这两部分的和是不是 $0$ 判断就好。
```cpp
    #include<bits/stdc++.h>
    using namespace std;
    const int N =1e6+10;
    char s[N],t[N];
    int s1[N],s2[N];
    int main()
    {
    	scanf("%s",s+1);
    	scanf("%s",t+1);
    	int n=strlen(s+1);
    	int n1=strlen(t+1);
    	for(int i=n-n1+1,j=1;i<=n;i++,j++)
    	{
    		if(s[i]==t[j]||s[i]=='?'||t[j]=='?')
    			s1[j]=0;
    		else
    			s1[j]=1;
    	}	
    	for(int i=1;i<=n1;i++)
    	{
    		if(s[i]==t[i]||s[i]=='?'||t[i]=='?')
    			s2[i]=0;
    		else
    			s2[i]=1;
    	}
    	for(int i=1;i<=n1;i++)
    		s1[i]+=s1[i-1],s2[i]+=s2[i-1];
    	for(int i=0;i<=n1;i++)
    	{
    		if(s1[n1]-s1[i]+s2[i]==0)//
    			 cout<<"Yes"<<endl;
    		else
    			cout<<"No"<<endl;
    	}
    }
    /*
    a?c
    b?
    */ 
```


---

## 作者：fengenrong (赞：3)

### 题意

给定两个字符串 $S,T$ ，它们仅由小写字母和字符 `?` 组成，其中 `?` 部分代表该位置可以被替换成任意的小写字母。

请你设计程序，对于所有的 $x=0,1,2,\dots,|T|$，判断是否存在满足以下要求的方案：

截取 $S$ 的前 $x$ 位与后 $|T|-x$ 位组成新的字符串 $P$ ，字符串 $P$ 与 $T$ 相等。
### 思路

这道题我们可以先使用一个字符串 $X$ 表示后 $|T|$ 位的字符串，接着遍历 $X$ 和 $T$ 看看是否符合，不符合的话我们就记录一下并且将 $cnt$ 加一，$cnt$ 表示当前字符串 $X$ 与字符串 $T$ 不相等的位的个数。如果 $cnt$ 为零，则输出 `Yes`，否则输出 `No`。

接着我们看一下下面这个样例：
```
atcoder
?????
```
我们的每一次组出来的应是：
```
coder
aoder
atder
atcer
atcor
atcod
```
不难发现，我们更改的第 $i$ 次只是 $X_i$。我们可以继续用回原本的 $cnt$，要是当前 $X_i$ 更改后与 $T_i$ 符合了并且原本是不符合的就讲 $cnt$ 减一；要是当前 $X_i$ 更改后与 $T_i$ 不符合了并且原本是符合的就讲 $cnt$ 加一。如果 $cnt$ 为零，则输出 `Yes`，否则输出 `No`。
### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
string s, t, x;
int bj[300005], cnt;
signed main() {
    cin >> s >> t;
    x = s.substr(s.size() - t.size(), t.size());//截取后面|t|位
    for (int i = 0; i < x.size(); i++)
        if (x[i] != '?' && t[i] != '?' && x[i] != t[i])//符合
            bj[i] = 1, cnt++;//记录
    printf((cnt == 0) ? "Yes\n" : "No\n");//判断
    for (int i = 0; i < t.size(); i++) {
        x[i] = s[i];
        if (bj[i] == 1 && (x[i] == t[i] || x[i] == '?' || t[i] == '?'))
            cnt--;
        if (x[i] != t[i] && x[i] != '?' && t[i] != '?' && bj[i] == 0)
            cnt++;
        printf((cnt == 0) ? "Yes\n" : "No\n");//判断
    }
    return 0;
}
```

---

## 作者：_qingshu_ (赞：0)

# 题意：

给定两个字符串 $S,T$，其中 $\texttt{?}$ 可以是任意字符。询问 $S$ 的前 $x$ 个字符与后 $| T |-x$ 字符组合起来的新字符串有没有可能与 $T$ 相同。

# 思路：

可以发现，无论 $x$ 的取值为多少，$S$ 中的每一个字符位置与 $T$ 中的字符位置都是对应的，只是取或者不取的问题，而且如果当前位置取了，要么前面的全部是被选取了的，要么后面的是全部的是全部被选取了的，从而想到前缀和做法。

我们可以记两个前缀和 $pre_i$ 与 $nxt_i$ 表示从开始和从结尾选取 $i$ 个字符与 $T$ 中不匹配的个数。

有了前缀和我们在扫一遍所有 $x$，如果两个前缀和都是 $0$ 就是有可能的。

# Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int pre[5200010],nxt[5200010];
string s,t;
signed main(){
	cin>>s>>t;
	for(int i=1;i<=t.size();i++){
		pre[i]=pre[i-1];
		if(s[i-1]!=t[i-1]&&s[i-1]!='?'&&t[i-1]!='?')pre[i]++;
		nxt[i]=nxt[i-1];
		if(s[s.size()-i]!=t[t.size()-i]&&s[s.size()-i]!='?'&&t[t.size()-i]!='?'){
			nxt[i]++;
		}
	}
	for(int i=0;i<=t.size();i++){
		if(pre[i]==0&&nxt[t.size()-i]==0){
			cout<<"Yes\n";
		}
		else{
			cout<<"No\n";
		}
	}
}
```

---

## 作者：billtun (赞：0)

## 题目大意：

给定两个字符串 $S$ 和 $T$（其中 $|S|$ 表示字符串 $S$ 的长度），对于 $x=0,1,\cdots,|T|$ 依次求解如下问题：

令 $U$ 为 $S$ 的前 $x$ 个字符与最后 $|T|-x$ 个字符组成的字符串，是否存在一种方式使得将 $T$ 和 $U$ 中的每一个 `?` 替换成任意的小写字母使得 $T=U$？如果存在，输出 `Yes`，否则输出 `No`。

数据范围：

对于 $100\%$ 的数据：$1\leq |T|<|S|\leq 3\times 10^5$，$S$ 和 $T$ 均只由小写字母和 `?` 组成。

## 思路：

### Num1：暴力。

充分利用string自带函数 `substr()`。

代码：
```cpp
#include<bits/stdc++.h>
#define ull unsigned  long long
#define p 1313131
#define Maxn 300005

using namespace std;

string s, t, c;
  
bool check(string s){
	for(int i=0;i<(int)t.size();i++){
		if(s[i]!='?' && t[i]!='?' && s[i]!=t[i]){
			return 0;
		}
	}
	return 1;
}

int main()
{
	cin>>s>>t;
	
	for(int i=0;i<=(int)t.size();i++){
		c=s.substr(0, i)+s.substr(s.size()-(t.size()-i), t.size()-i);
		printf(check(c) ? "Yes\n" : "No\n");
	}
	return 0;
}
```

~~哎？为什么会零分？~~

### Num2：由上一个转移到下一个。

我们可以发现，每一次都相当于是将 $S$ 串末端取的连续字符串的第一个转移到 $S$ 串首部取的连续字符串的最后一个的后面，其他不变。所以很自然的想到维护前一个的信息，在下一次直接利用（有一点像莫队的思想）。

代码：
```cpp
#include<bits/stdc++.h>
#define ull unsigned  long long
#define p 1313131
#define Maxn 300005

using namespace std;

int Num=0; // 不匹配个数
string s, t;
bool vis[Maxn]; // 是否匹配

int main()
{
	cin>>s>>t;
	
	for(int i=s.size()-t.size();i<(int)s.size();i++){
		if(s[i]!='?' && t[i-s.size()+t.size()]!='?' && s[i]!=t[i-s.size()+t.size()]){
			vis[i-s.size()+t.size()]=1;
			Num++;
		}
	}
	printf(Num!=0 ? "No\n" : "Yes\n");
	// 单独维护
	
	for(int i=0;i<(int)t.size();i++){ // 转移 
		if(vis[i] && (s[i]==t[i] || s[i]=='?' || t[i]=='?')){ // 本来未匹配上的
			Num--, vis[i]=0;
		}
		if(!vis[i] && (s[i]!=t[i] && s[i]!='?' && t[i]!='?')){ // 本来匹配上的
			Num++, vis[i]=1;
		}
		printf(Num!=0 ? "No\n" : "Yes\n");
	}
	return 0;
}
```

---

## 作者：unicorn1220 (赞：0)

直接上思路吧。

首先直接暴力的话 $O(n|T|)$ 炸掉，怎么办呢？

仔细观察一下每个截取出来的字符串，会发现第一个是从右开始的一段连续的完整字符串，长度为 $|T|$。后面的每一个就像是把上一个右边部分的最左边取到左边的尽头，**只改变一个值**。利用这个特点，我们可以先对第一个截取出来的字符串和 $T$ 做匹配，记下相匹配的位置的个数和每个位置的情况，就可以得出第一个答案。后面只要对改变的那个位置做判断，根据上一个的状态就可以做到 $O(1)$ 更新状态，一边更新一边输出就好。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
int xt;
bool bj[300005];
inline string read()
{
    char a;
    string si;
    a=getchar();
    while((a<'a'||a>'z')&&a!='?') a=getchar();
    while((a>='a'&&a<='z')||a=='?') si+=a,a=getchar();
    return si;
}
int main()
{
    a=read(),b=read();
    for(int i=0;i<b.size();i++) if(a[i+a.size()-b.size()]==b[i]||a[i+a.size()-b.size()]=='?'||b[i]=='?') xt++,bj[i]=1;
    xt==b.size()?printf("Yes\n"):printf("No\n");
    for(int i=1;i<=b.size();i++)
    {
        if(a[i-1]!=b[i-1]&&a[i-1]!='?'&&b[i-1]!='?')
        {
            if(bj[i-1]) xt--;
            bj[i-1]=0;
        } 
        else
        {
            if(!bj[i-1]) xt++;
            bj[i-1]=1;
        }
        xt==b.size()?printf("Yes\n"):printf("No\n");
    }
    return 0;
}
```

---

## 作者：FstAutoMaton (赞：0)

一道比较有趣的思维题。

首先，为了方便解释，我们可以用 $n$ 代表 $s$ 的长度，$m$ 代表 $t$ 的长度。
题目中说新字符串 $s'$ 是由字符串 $s$ 的前 $x$ 个字符和后 $m-x$ 个字符组成（ $x$ 意思与题目给的意思相同），哪么我们只需要确定前半部分和后半部分是否满足即可（只要有一个部分不满足就不行，两个部分都满足就行）。

那么问题来了，我们该如何判断这一个部分能否被满足呢？
我们可以计算 $s$ 与 $t$ 的最长公共前缀还有最长公共后缀。设 $pre$ 为 $s$ 与 $t$ 的最长公共前缀长度， $back$ 为 $s$ 与 $t$ 的最长公共后缀长度。
如果第一部分被 $\left[1, pre\right]$ 这个区间包含,且第二部分被 $\left[m-x+1,m\right]$ 包含，就是可行的（最长因为公共前缀在两个字符串中都为前缀，也两个字符串的这一段分相同，最长公共后缀同上）。

PS：其实看 $s'$ 前一部分和后一部分的长度也可以，那就变为 $x\le pre$ 且 $m-x+1\le back$ 就是可以。

代码如下：
```
#include <bits/stdc++.h>
using namespace std;
const int kMaxn = 3e5 + 5;
char s[kMaxn], t[kMaxn];
int l, r;
int main() {
    cin >> s + 1 >> t + 1;
    int n = strlen( s+ 1 );
    int m = strlen( t+ 1 );
    for( int i = 1; i <= m; i ++ ) {
        if( s[i] != t[i] && s[i] != '?' && t[i] != '?' ) {
            break;
        }
        l = i;
    }
    for( int i = n, j = m; i && j; i --, j -- ) {
        if( s[i] != t[j] && s[i] != '?' && t[j] != '?' ) {
            break;
        }
        r ++;
    }
    for( int i = 0; i <= m; i ++ ) {
        if( i <= l && m - i <= r ) {
            cout<< "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }
}
```


---

## 作者：Otue (赞：0)

## 思路
我们只需要看 $S$ 的前 $x$ 个字符和 $S$ 的后 $|T|-x$ 个字符是否与 $T$ 匹配。 因为每次只需要判断连续前缀和连续后缀，所以可以提前预处理出两个数组 $p$ 和 $q$。

* $p_x$ 表示 $S$ 的前 $x$ 个字符和 $T$ 前 $x$ 个字符是否匹配。
* $q_x$ 表示 $S$ 的后 $x$ 个字符和 $T$ 后 $x$ 个字符是否匹配。

对于 $x=0\sim n$，只需要看 $p_x$ 和 $q_{|T|-x}$ 是否匹配就行。
## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;
int n, m, k1[N], k2[N];  // 前缀后缀
char s[N], t[N];

int check(int a, int b) {  // 判断a,b是否可以相等
    if (a == '?' || b == '?') return 1;
    if (a == b) return 1;
    return 0;
}

int main() {
    cin >> (s + 1) >> (t + 1);
    int n = strlen(s + 1), m = strlen(t + 1);
    k1[0] = k2[0] = 1;
    for (int i = 1; i <= m; i++) {
        if (check(t[i], s[i]) && k1[i - 1]) k1[i] = 1;
    }
    for (int i = m; i >= 1; i--) {
        if (check(t[i], s[n - (m - i)]) && k2[m - i]) k2[m - i + 1] = 1;
    } 
    for (int i = 0; i <= m; i++) {
        if (k1[i] && k2[m - i]) puts("Yes");
        else puts("No");
    }
}
```

---

