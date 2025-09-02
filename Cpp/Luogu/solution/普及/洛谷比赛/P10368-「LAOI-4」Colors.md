# 「LAOI-4」Colors

## 题目背景

做这个题：

![](https://cdn.luogu.com.cn/upload/image_hosting/6053fe2y.png)

## 题目描述

给定长度为 $n$ 的字符串 $A$。  
- 若 $A_{i-1}=A_{i+1}$，则称 $A_i$ 为 「可消除的」。

定义一次操作为：消除 $A$ 中所有「可消除的」字符。

请你输出操作 $k$ 次后的 $A$。

## 说明/提示

样例解释：

- 对于第 $1$ 组数据，字符串为 $\text{aba}$，一次操作后为 $\text{aa}$。
- 对于第 $2$ 组数据，字符串为 $\text{acaca}$，一次操作后为 $\text{aa}$，两次操作后为 $\text{aa}$。
- 对于第 $3$ 组数据，字符串为 $\text{abc}$，零次操作后为 $\text{abc}$。

**「本题采用捆绑测试」**

| $\text{Subtask}$ | $\sum n \le$|  特殊性质 | 子任务依赖| 总分值 |
| :--------------: | :-----: |:-----:|:--: | :--------: |
|       $1$        |  $10^6$ |    $\text{A}$    |无| $5$ |
$2$        | $300$  | $k\le 300$ |无| $10$ |
$3$        | $10^3$  | 无| $2$| $15$ |
|       $4$        | $10^6$  | $\text{B}$ |无| $10$ |
|       $5$        | $10^6$ | $\text{C}$ |$4$| $20$ |
|       $6$        | $10^7$ |     无     |$1\sim5 $| $40$ |


对于 $100\%$ 的数据，$1  \le \sum n \le 10^7$，$1 \le  T \le 10^5$，$0\le k\le 10^{18}$，字符串均由小写字母组成。

特殊性质 $\text{A}$：$A$ 是一个 $\text{a}\sim\text{z}$ 的排列。

特殊性质 $\text{B}$：$\forall i\in[1,n-2], A_i= A_{i+2}$。

特殊性质 $\text{C}$：保证 $A_i$ 只可能有两种取值。


## 样例 #1

### 输入

```
3 0
3 1
aba
5 2
acaca
3 0
abc```

### 输出

```
aa
aa
abc```

# 题解

## 作者：Anemones (赞：13)

结论：操作二次后字符串不会继续被改变。

- 若 $A_{i-1}=A_{i+1}$，则称 $A_i$ 为 「可消除的」。

这句话我们可以把它理解成 $\texttt{121}$ 结构，那么一轮消除了所有 $\texttt{121}$ 结构后，剩下的便是形似 $\texttt{111}$ 这样的结构，$\texttt{111}$ 这样结构再经过消除就没有了。


```cpp
//luogu uid:YuZeAn 736184
#include<bits/stdc++.h>
#include<ext/rope>
using namespace __gnu_cxx;
#define dbg puts("-------------------DWT AK IOI--------------------")
#define int long long
#define mod 998244353
#define end putchar('\n')
#define sp putchar(' ')
using namespace std;
inline int read(){
    char c=getchar(),f=0;int t=0;
    for(;c<'0'||c>'9';c=getchar()) if(!(c^45)) f=1;
    for(;c>='0'&&c<='9';c=getchar()) t=(t<<1)+(t<<3)+(c^48);
    return f?-t:t;
}
inline void write(int x){
    static int t[25];int tp=0;
    if(x==0) return(void)(putchar('0'));else if(x<0) putchar('-'),x=-x;
    while(x) t[tp++]=x%10,x/=10;
    while(tp--) putchar(t[tp]+48);
}
signed main(){
	int T=read(),id=read();
	while(T--){
		int n=read(),k=read();
		string s,s1;
		cin>>s;
		k=min(2ll,k);
		if(k==0||n<=2){
			cout<<s<<endl;
			continue;
		}
		s1=s[0];
		for(int i=0;i<n-2;i++){
			if(s[i]!=s[i+2]) s1+=s[i+1];
		}
		//if(n-2!=0) s1+=s[n-2];
		if(n-1!=0)s1+=s[n-1];
		//cout<<s1<<endl;
		if(k==2){
			cout<<s1[0];
			for(int i=0;i<s1.size()-2;i++){
				if(s1[i]!=s1[i+2]) cout<<s1[i+1];
			}
			//if(s1.size()-2!=0) cout<<s1[n-2];
			if(s1.size()-1!=0) cout<<s1[s1.size()-1];
			cout<<endl;
		}
		else cout<<s1<<endl;
	}
    return 0;
}
```

---

## 作者：GoodLuckCat (赞：5)

## P10368 题解

[P10368题目传送门](https://www.luogu.com.cn/problem/P10368)

场上一开始看到这题，感觉挺好理解，就开打了。但是最后只有 $60$ 分（）

先来讲部分分做法：

### $10$ 分

题外话：大家可能会看到我的提交记录里面有一个 $5$ 分，但是那个是试出来的。

直接模拟。代码·非常简洁易懂，但是我可是调了好几次的......

```cpp
#include<iostream>
#include<string>
#include<vector>
using namespace std;
string xiaochu(string&i,int k)
{
    string r=i;
    bool e=1;
    while(k--&&e)
    {
        e=0;
        vector<int>m;
        for(int j=1;j<r.length()-1;j++)
        {
            if(r[j-1]==r[j+1])
            {
                m.push_back(j);
                e=1;
            }
        }
        for(int j=m.size()-1;j>=0;j--)r.erase(m[j],1);
    }
    return r;
}
int main()
{
    int T,id;
    cin>>T>>id;
    while(T--)
    {
        int n,k;
        cin>>n>>k;
        string i;
        cin>>i;
        cout<<xiaochu(i,k)<<endl;
    }
}
```

↑我猜有些人会直接复制上面的代码

但是我们可以发现就只对了五个点。

然后开始思考有没有更好的做法。

经过我长达十七秒的思考，得出了结论：**开 `long long`**。

>$0\le k\le 10^{18}$

这么大的数据，肯定要开 `long long`。

但是开 `long long` 之后——

### $60$ 分

发现还是会有一些点 TLE。准确来说是最后一个 Subtask。

代码和上面的就只差了一个数据类型：

```cpp
#include<iostream>
#include<string>
#include<vector>
using namespace std;
string xiaochu(string&i,int k)
{
    string r=i;
    bool e=1;
    while(k--&&e)
    {
        e=0;
        vector<int>m;
        for(int j=1;j<r.length()-1;j++)
        {
            if(r[j-1]==r[j+1])
            {
                m.push_back(j);
                e=1;
            }
        }
        for(int j=m.size()-1;j>=0;j--)r.erase(m[j],1);
    }
    return r;
}
int main()
{
    int T,id;
    cin>>T>>id;
    while(T--)
    {
        long long n,k;
        cin>>n>>k;
        string i;
        cin>>i;
        cout<<xiaochu(i,k)<<endl;
    }
}
```

### $100$ 分

注意到上面的两份代码都用到了一个叫做 `erase` 的函数。这个函数运行起来非常费时间。所以说，我们要优化一下。感谢 @[int_stl](/user/764666) 大佬的帮助。

代码如下：

```cpp
#include<iostream>
#include<string>
#include<vector>
using namespace std;
string xiaochu(string i,int k)
{
    bool e=1;
    while(k--&&e)
    {
        string s="";
        e=0;
        for(int j=0;j<=i.length()-1;j++)
        {
            if(j>0&&j<i.length()-1&&i[j-1]==i[j+1])e=1;
            else s+=i[j];
        }
        i=s;
    }
    return i;
}
int main()
{
    int T,id;
    cin>>T>>id;
    while(T--)
    {
        long long n,k;
        cin>>n>>k;
        string i;
        cin>>i;
        cout<<xiaochu(i,k)<<endl;
    }
}
```

至此，我们就完成了这道题。

~~第一次写题解写过 $\sout{150}$ 行祭~~

---

## 作者：Melo_qwq (赞：2)

本人用两页的提交记录发现了一个大坑。

~~谁像我一样写快读还要关同步流导致赛时写挂。~~

# 题目大意

如果一个字符两侧字符相同它就可以被删掉了。

注意多组数据，千万别漏输了 $id$。

# 题目实现

不难证明最多操作 $2$ 次就不会再变了。

证明：对于任意的形如 $aba$ 的串，第一次我们会将它消除成 $aa$ 的样子，下一次要么像 $aabb$ 一样无法消除要么像 $aaaa$ 一样一下消完。

没有什么必要的特判：要是长度小于等于 $2$ 或者操作次数为 $0$ 直接输出就行。

然后要是特判没用从第一位开始枚举按题意模拟输出即可。

## 巨大的坑点

先放上进行第二次消除（当然如果需要第二次消除的话）的代码：

```pascal
cout << ans[0] ;
for (int i = 0 ;i < ans.size () - 2 ;i ++) {
	if (ans[i] != ans[i + 2]) {
		cout << ans[i + 1] ;
	}
}
if (ans.size () - 1 != 0) cout << ans[ans.size () - 1] ;
cout << '\n' ;
```


下面是 RE 代码：

```cpp
cout << ans[0] ;
for (int i = 0 ;i <= ans.size () - 3 ;i ++) {
	if (ans[i] != ans[i + 2]) {
		cout << ans[i + 1] ;
	}
}
if (ans.size () - 1 != 0) cout << ans[ans.size () - 1] ;
cout << '\n' ;
```

你可能觉得一点区别没有，认为是评测机故障，或者像我一样觉得是测试点的问题，事实证明，官方这个坑挖的还是很好的。

$\color{red}警钟撅烂$：咱们在进行第一次消除后原串**可能只剩下 $2$ 个字符**，要是写 $\le len - 3$（$len$ 指串长）会导致数组越界！！！

那么为什么会导致数组越界呢？因为我们默认一个字符串的 size 函数是 unsigned int 类型，如果串长为 $2$，它减掉 $3$ 后变成了 $-1$，因为是无符号类，会变成一个巨大无比的数，从而爆掉，我们将它强转为 int 类型即可。

也就是下面这样：

```cpp
for (int i = 0 ;i <= (int) ans.size () - 3 ;i ++) {
	if (ans[i] != ans[i + 2]) {
		cout << ans[i + 1] ;
	}
}
```

那么就结束了，放上代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
using namespace std ;
inline int read () {
    char ch = getchar () ,f = 0 ;
	int t = 0 ;
    for( ;ch < '0' or ch > '9' ;ch = getchar ()) {
		if (! (ch ^ 45)) f = 1 ;
	}
    for( ;ch >= '0' and ch <= '9' ;ch = getchar ()){
		t = (t << 1) + (t << 3) + (ch ^ 48) ;
	}
    return f ? - t : t ;
}
signed main () {
	int t = read () ,id = read () ;
	do {
		int n = read () ,k = read () ;
		string s ,ans ;
		cin >> s ;
		k = min (2ll ,k) ;
		if (n <= 2 or k == 0) {
			cout << s << '\n' ;
			goto shin ;
		}
		ans += s[0] ;
		rep (i ,0 ,n - 3 ,1) {
			if (s[i] != s[i + 2]) {
				ans += s[i + 1] ;
			}
		}
		if (n - 1 != 0) ans += s[n - 1] ;
		if (k == 1) {
			cout << ans << '\n' ; 
			goto shin ;
		}
		cout << ans[0] ;
		for (int i = 0 ;i <= (int) ans.size () - 3 ;i ++) {
			if (ans[i] != ans[i + 2]) {
				cout << ans[i + 1] ;
			}
		}
		if (ans.size () - 1 != 0) cout << ans[ans.size () - 1] ;
		cout << '\n' ;
		shin : ;
	} while (t -- != 1) ;
	return 0 ;
}
```

---

## 作者：许多 (赞：1)

首先观察性质：当已经操作一次后，如果 $a_{i-1},a_i,a_{i+1}$ 都没有被消除，那么接下来一次操作 $a_{i}$ 也一定不会被消除。

~~看上去这是一句废话~~，但对于进一步的推导有重大帮助。如果第一次操作 $a_{i-1}$ 被消除，则原本 $a_{i-2}=a_i$，那么消除完之后 $a_{i-1}=a_i$。如果第二次操作是 $a_i$ 被消除，那一定有 $a_{i-1}=a_{i+1}=a_i$。结合上述性质，我们惊喜的发现**最多操作两次字符串不会变化**。

那就好做了，直接分类讨论暴力。

# CODE


```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define N 10001000
using namespace std;
inline LL read(){
    LL x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
LL T,id,n,k;
string s,ans;
int main(){
	T=read(),id=read();
	while(T--){
		n=read(),k=read();
        cin>>s;//不知道为啥换成getline就WA+RE
		if(k==0||n<=2){cout<<s<<endl;continue;}
		ans=s[0];
		for(LL i=1;i<n-1;i++)
			if(s[i-1]!=s[i+1])
                ans+=s[i];
		ans+=s[n-1];
		if(k>=2){
			cout<<ans[0];
			for(LL i=1;i<ans.size()-1;i++)
				if(ans[i-1]!=ans[i+1]) cout<<ans[i];
			cout<<ans[ans.size()-1]<<endl;
		}
		else cout<<ans<<endl;
	}
    return 0;
}
```

---

## 作者：_O_v_O_ (赞：1)

Conclusion Masters #2（确信

妙题。

先讲 VP 时做法。

观察到 $k$ 的范围极大，所以考虑剪枝。

很明显当一次无法消时之后都无法消，那么直接剪枝即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int T,id;
int n,k;
string s,ss;

bool xiao(){
	for(int i=0;i<n;i++){
		if(i==0||i==n-1||s[i-1]!=s[i+1]){
			ss.push_back(s[i]);
		}
	}
	s=ss;
	ss.clear();
	if(s.size()==n) return true;
	n=s.size();
	return false;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>T>>id;
	while(T--){
		cin>>n>>k>>s;
		for(int i=1;i<=k;i++){
			if(xiao()) break;
		}
		cout<<s<<endl;
	}
	return 0;
}
```

接下来讲严谨证明：

很明显能消除的字符只能为 $\tt aba$（以下称 $1$ 类）或 $\tt aaa$（以下称 $2$ 类）两种形式。

很明显，$1$ 类消完后会产生新的 $2$ 类，$2$ 类消完后不会产生新的可消除字符。

那么最多只需 $2$ 次即可消完。

---

## 作者：haokee (赞：1)

提供一种另类的模拟算法，适用于更多的情况（而不一定为 $\texttt{aba}$ 式，虽然赛后才发现最多只会删除两次）。

如果一次操作没有删除任何数的话，那么这次操作是毫无意义的，因此操作最多执行 $n$ 次。为了快速删除一个数，我们可以使用链表的结构。那么这样子的时间复杂度是 $\mathcal O(n^2)$ 的，仍然不优。

仔细观察，删除第 $i$ 个字符只会影响第 $i-1$ 个字符和第 $i+1$ 个字符，因此删除了之后直接对这两个进行判定就行了。但是我们需要考虑复杂一点的情况，假如有若干个需要删除的连续字符，那么我们只删除了一个就去对前一个字符作判定是不对的，因为后面的字符还没有删掉。

考虑新加一个 wait 数组，我们先把需要删的删掉了再来判断这些需要判断的数，而 wait 数组就是用来存储这些数的。这样，我们就可以愉快地使用 $\mathcal O(n)$ 的算法通过了。

```cpp
#include <iostream>
#include <vector>

using namespace std;

const int kMaxN = 1e7 + 5;

int prv[kMaxN], nxt[kMaxN], b[kMaxN], t, id, n;  // prv 是上一个元素，nxt 是下一个，b 是标记数组
long long k;                                     // 最多删除次数，注意使用 long long
vector<int> v, f, wait;                          // 分别为上一次删的，下一步要删的和 wait 数组
char s[kMaxN];                                   // 用来存储字符串

// 判断第 x 个字符是否满足条件
bool check(int x) { return s[nxt[x]] == s[prv[x]]; }

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);  // 读入优化
  for (cin >> t >> id; t; t--) {                     // 多组数据
    cin >> n >> k >> (s + 1);                        // 输入信息
    f.clear();                                       // 清空第一次要删的
    // 初始化链表
    for (int i = 1; i <= n; i++) {
      prv[i] = i - 1, nxt[i] = i + 1;
    }
    // 第一次删除（没有真正删掉）
    for (int i = 2; i <= n; i++) {
      check(i) && (f.push_back(i), 0);
    }
    // 最多 k 次并且有要删的
    for (int i = 1; i <= k && f.size(); i++) {
      wait.clear();      // 清空 wait 数组
      for (int j : f) {  // 遍历要删的
        b[j] = 1;        // 真正删除
      }
      // 执行下一步删除
      for (int j = 0, k; j < f.size(); ) {
        for (k = j + 1; k < f.size() && f[k] - f[k - 1] == 1; k++) { }  // 找到一段连续的 [j, k)
        nxt[prv[f[j]]] = nxt[f[k - 1]];                                 // 对链表进行删除操作
        prv[nxt[f[k - 1]]] = prv[f[j]];
        wait.push_back(prv[f[j]]);                                      // 加入 wait 数组
        wait.push_back(nxt[f[k - 1]]);
        j = k;                                                          // 跳过去
      }
      // 对 wait 进行逐一排查
      for (int j : wait) {
        if (!b[j] && 1 < j && j < n && check(j)) {  // 如果满足条件
          v.push_back(j);                           // 加入下一步要删的
        }
      }
      f = v, v.clear();                             // 交换并清空
    }
    // 输出并清空
    for (int i = 1; i <= n; b[i++] = 0) {
      if (!b[i]) {
        cout << s[i];
      }
    }
    cout << '\n';
  }
  return 0;
}
```

---

## 作者：LostKeyToReach (赞：1)

经过观察发现 $k \le 10^{18}$ 且 $\sum n \le 10^7$。

这说明直接按题意模拟是会超时的，所以我们可以编写一个函数检测是否存在可消除字符，当没有时，我们就没有操作下去的必要了，这样可以让程序的运行效率更高。

代码如下：
```cpp
#include <iostream>
#define int long long
using namespace std;
string ans;
bool chk(string x) {
	int cnt = 0;
	ans = "";
	for (int i = 0; i < x.size(); i++) {
		if (i - 1 >= 0 && i + 1 < x.size() && x[i - 1] == x[i + 1]) cnt++;
		else ans += x[i];
	}
	return cnt != 0;
}
signed main() {
	int t, id;
	cin >> t >> id;
	while (t--) {
		int n, k;
		cin >> n >> k;
		string s;
		cin >> s;
		while (k-- && chk(s)) {
			s = ans;
		}
		cout << s << endl;
	}
}
```

---

## 作者：Chu_awa_xing (赞：1)

## P10368题解
这题可以直接用字符串进行修改，因为字符串相加就是前者拼接上了后者。其次这里有一个优化，就是如果一次操作后，字符串没有变化，那么剩下的操作就没必要执行了，直接输出答案即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int id,T;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}
string f(string s){
	string tmp="";
	for(int i=0;i<s.length();i++){
		if((!i)||i==s.length()-1){
			tmp+=s[i];
		}
		else if(s[i-1]!=s[i+1]){
			tmp+=s[i];
		}
	}
	return tmp;
}
signed main(){
	T=read(),id=read();
	while(T--){
		long long n,k;
		n=read(),k=read();
		cin>>s;
		while(k--){
			string s0=f(s);
			if(s==s0){
				break;
			}
			else s=s0;
		}
		cout<<s<<"\n";
	}
}
```

---

## 作者：UniGravity (赞：1)

## Solution P10368 「LAOI-4」Colors
提供一种不需要脑子的做法。

~~有一个结论是经过 2 次操作后数组不再改变，但实际上如果不知道这个结论也可以实现。~~

---

$k\le10^{18}$ 是骗人的，因为每次操作至少删除 $1$ 个数，所以最多只有 $n$ 次操作。

运用类似链表的思想，我们记录 $a_i$ 前后是什么，分别记为 $pre_i$ 和 $nxt_i$。

每次删数只需要修改前后数字的 $nxt_{pre_i}$ 和 $pre_{nxt_i}$ 值即可，同时更新下一次操作需要删去的数。

---

由于最多只有 $n$ 次操作，每次操作最多 $n$ 个数被删去，直接用 vector 维护即可，时间复杂度是 $O(n)$。

为了防止重复和便于维护，先将所有可能成为下一回合删去的数拎出来到 tmp 里，再判断一次即可。

献上丑陋的代码：
```cpp
scanf("%lld %lld %s", &n, &k, a + 1);
forto(i, 1, n) {
    pre[i] = i - 1; nxt[i] = i + 1; f[i] = f1[i] = true;
} 
tot = nxt[n] = 0;
forto(i, 2, n - 1) {
    if (a[pre[i]] == a[nxt[i]]) {
        need[++tot] = i;
        //printf("add %lld\n", i);
        f[i] = false;
    }
}
while (tot) {
    if (!k) {
        forto(i, 1, n) {
            if (f1[i]) putchar(a[i]);
        }
        putchar('\n');
        return;
    }
    vector< int > tmp, qwq;
    forto(i, 1, tot) {
        rnt x = pre[need[i]], y = nxt[need[i]];
        nxt[x] = y; pre[y] = x;
        tmp.push_back(x); tmp.push_back(y);
        //printf("%lld <- %lld -> %lld\n", x, need[i], y);
        f1[need[i]] = false;
    }
    forto(i, 0, tmp.size() - 1) {
        rnt x = tmp[i];
        //printf("%lld <- %lld -> %lld\n", pre[x], x, nxt[x]);
        if (a[pre[x]] == a[nxt[x]] && f[x]) {
            f[x] = false;
            qwq.push_back(x);
        }
    }
    tot = 0;
    for (rnt i = 0; i < qwq.size(); i++) {
        need[++tot] = qwq[i];
    }
    k--;
}
forto(i, 1, n) {            
    if (f1[i]) putchar(a[i]);
}
putchar('\n');
```

---

## 作者：xzz_0611 (赞：0)

[题目传送门](/problem/P10368)
# 分析
简单的模拟题。

对于每一次操作，我们需要依次判断 $A_i$（$1<i<n$）是否可以被删除，不可被删除就将 $A_i$ 加入到另一个字符串的末尾，可以被删除就不用加，最后再用这个字符串覆盖掉 $A$。只要执行以上操作 $k$ 次即可。
# code
```cpp
#include<iostream>
#define ll long long//十年OI一场空，不开long long见祖宗
using namespace std;
string str,A;
bool chk() {
	bool flag=false;//判断是否减少了字符
	str="";//清空
	for(ll i=0;i<A.size();++i) {
		if(i-1>-1&&i+1<A.size()&&A[i-1]==A[i+1]) flag=true;
		else str+=A[i];//添加到末尾 
	}
	return flag;
}
int main() {
	ll T,id,n,k;
	cin>>T>>id;
	while(T--) {
		cin>>n>>k>>A;
		while(k--/*操作数一定要减1*/&&chk()/*若没有减少字符则不覆盖*/) A=str;//覆盖 
		cout<<A<<endl;
	}
	return 0;
}
```

---

## 作者：xuan_gong_dong (赞：0)

## 题面
[P10368 「LAOI-4」Colors](https://www.luogu.com.cn/problem/P10368)

## 分析
手玩了自己手写的数据，发现好像都删除次数不会大于 $2$。证了半天没证出来，但是也推翻不了，于是，用这个结论一交，就过了。。。

用这个数据很容易就写出来了，暴力删除两次就出来了，注意写几个简单的特判判 $k\le 1$ 的情况就好了。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k;
char c[10000010],hys[10000010]; 
signed main()
{
	int T,ID;
	scanf("%lld%lld",&T,&ID);
	while(T--)
	{
		scanf("%lld%lld",&n,&k);
		k=min(k,(long long){2});
		scanf("%s",c+1);
	
		if(k==0)
		{
			printf("%s",c+1);
			putchar(10);
			continue;
		}			
		int tot=0;
		hys[++tot]=c[1];
		for(int i=2;i<n;i++)
		{
			if(c[i-1]!=c[i+1])
			{
				hys[++tot]=c[i];
			}
		}
		if(n>1)hys[++tot]=c[n];
		if(k==1)
		{
			printf("%s",hys+1);
			for(int i=0;i<=tot;i++)hys[i]=0;
//			printf("tot=%d",tot);
			putchar(10);
			continue;
		}
		printf("%c",hys[1]);
		for(int i=2;i<tot;i++)
		{
			if(hys[i-1]!=hys[i+1])
			{
				printf("%c",hys[i]);
			}
		}
		if(tot>1)printf("%c",hys[tot]);
		for(int i=0;i<=tot+1;i++)hys[i]=0;
		putchar(10);
	}
	return 0;
}
```

---

## 作者：GXZJQ (赞：0)

# P10368 「LAOI-4」Colors 题解

更新于 $2024$ 年 $4$ 月 $29$ 日：修改了题目的证明，感谢 WhisperingWillow 的指正。

[题目链接](https://www.luogu.com.cn/problem/P10368)

## 题目大意
给定一个字符串 $s$，求出其按照题目变换方式变换后的字符串。

## 题目分析

不加证明的给出一个结论：

>对于每个字符串 $s$，最多只能进行两次变换。

这是为什么呢？从变换方式的角度入手，对于每次变换，我们都会把形如 `aba` 的子串进行操作。这会导致其变为 `aa` 的样子。此时就有两种情况：

1. 左边的若干个字符与这两个字符不相同，拼到一起后记为 `aabbcc`，它显然不满足题目的性质，不可继续消除；

2. 左边的若干个字符与这两个字符相同，拼到一起后就为 `aaaaaaa`，它虽然满足消除条件，但只需要一次就可以将其消除到最短的 `aa`，所以只能再多消除一次。

## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t, id, n, k;
string s1, s2;
//s1储存给定的字符串, s2储存删除后的字符串
int main() {
	cin >> t >> id;
	while (t--) {
		cin >> n >> k;
		cin >> s1;
		if (k == 0 || n < 3) {
			cout << s1 << endl;
			continue;
		}
		//不用操作或者长度不够不能操作
		if (k > 2) k = 2;
		//最多只能操作两次
		s2 = s1[0];
		//由于给定的字符串开头的左边没有字符,所以开头一定不会被删除
		for (int i = 0; i <= n - 2; i++) {
			if (s1[i] != s1[i + 2]) s2 += s1[i + 1];
			//左右不相同,不会删除
		}
		s1 = s2, s2 = "";
		if (k == 1) {
			cout << s1 << endl;
			continue;
		}
		s2 = s1[0];
		n = s1.length();
		if (n < 3) {
			cout << s1 << endl;
			continue;
		}
		for (int i = 0; i <= n - 2; i++) {
			if (s1[i] != s1[i + 2]) s2 += s1[i + 1];
			//左右不相同,不会删除
		}
		//再操作一遍
		s1 = s2, s2 = "";
		cout << s1 << endl;
		s1 = "";
	}
	return 0;
}
```

---

## 作者：Fantasy_Segment_Tree (赞：0)

实际上，最多经过两次，就不会再改变了。

因为第一次操作后剩下的最多只会有连续的 $2$ 个相同字符了。

所以，直接暴力就好了。

代码如下。

```cpp
#include <iostream>
using namespace std;

long long T, id;

string s;

int main() {
	cin >> T >> id;
	while(T--) {
		long long n, k;
		cin >> n >> k;
		string s;
		cin >> s;
		long long flag = 1, cnt = 0;
		while(flag && cnt < k) {
			string t = "";
			cnt++;
			flag = 0;
			t += s[0];
			for(long long i = 1; i < s.size() - 1; i++) {
				if(s[i - 1] != s[i + 1]) t += s[i];
				if(s[i - 1] == s[i + 1]) flag = 1;
			}
			if(s.size() != 1) t += s[s.size() - 1];
			s = t;
		}
		cout << s << endl;
	}
}
```

---

## 作者：xhr123bc (赞：0)

# 「LAOI-4」Colors

## 题目大意

给定一个长度为 $n$ 的字符串 $A$，如果 $A_{i-1} = A_{i+1}$，则称 $A_i$ 为「可消除的」。定义一次操作为：消除 $A$ 中所有「可消除的」字符。输出操作 $k$ 次后的 $A$。

## 题目思路

首先，我们可以观察到，对于给定的字符串，经过一定次数的操作后，字符串会进入一个循环，不断重复出现相同的状态。我们可以利用这个特点，先找到循环的起点和长度，然后直接计算出第 $k$ 次操作后的字符串。

具体步骤如下：

1. 使用 `op` 函数对字符串进行一次操作，删除所有可消除的字符。

2. 使用哈希表 `mp` 来记录每个状态第一次出现的位置，使用数组 `st` 来存储所有出现过的状态。

3. 不断对字符串进行操作，直到遇到一个之前出现过的状态。此时，我们就找到了循环的起点和长度。

4. 如果 $k$ 小于循环的起点，那么第 $k$ 次操作后的字符串就是 `st[k]`。

5. 否则，我们将 $k$ 减去循环的起点，然后对循环的长度取模，得到在循环中的位置。最终的字符串就是 `st[ls + k]`。

## 代码

```cpp
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

string op(string s) {
    int n = s.size();
    string ns;
    ns.reserve(n);

    for (int i = 0; i < n; ++i) {
        if (i == 0 || i == n - 1 || s[i - 1] != s[i + 1]) {
            ns += s[i];
        }
    }

    return ns;
}

string solve(string s, long long k) {
    unordered_map<string, int> mp;
    vector<string> st;

    while (mp.count(s) == 0) {
        mp[s] = st.size();
        st.push_back(s);
        s = op(s);
    }

    int ls = mp[s];
    int ll = st.size() - ls;

    if (k < ls) {
        return st[k];
    } else {
        k -= ls;
        k %= ll;
        return st[ls + k];
    }
}

int main() {
    int T, id;
    cin >> T >> id;

    while (T--) {
        int n;
        long long k;
        string s;
        cin >> n >> k >> s;

        cout << solve(s, k) << endl;
    }

    return 0;
}
```

这个算法的时间复杂度是 $O(n^2)$，空间复杂度是 $O(n^2)$。

---

