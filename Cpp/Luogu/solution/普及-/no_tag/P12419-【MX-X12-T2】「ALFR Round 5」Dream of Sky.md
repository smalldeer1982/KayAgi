# 【MX-X12-T2】「ALFR Round 5」Dream of Sky

## 题目背景

原题链接：<https://oier.team/problems/X12B>。

---

> “一旦你尝试过天空的味道，你就会永远向上仰望”——列奥纳多 达芬奇

## 题目描述

定义一个 01 串 $s$ 的权值为最小的 $k$ 使得 $s$ 能被分割成 $k$ 个子串，且每个子串的各个字符都相等。例如，`1011110000010000` 的权值为 $6$。

现有一个二进制数 $n\in[l,r]$，求 $n$ 转化为 01 字符串（不含前导零）后的权值最小是多少，即，求 $[l,r]$ 中权值最小的 $n$ 的权值。

## 说明/提示

**【样例解释】**

在第一组测试数据中 $l=3200,r=3500$。可以选择 $n=3327$，其二进制表示为 `110011111111`，权值为 $3$。可以证明在 $[l,r]$ 的数没有更小的权值了。

在第二组测试数据中 $l=1,r=2$。可以选择 $n=1$，其二进制表示为 `1`，权值为 $1$。显然这是最小可能的权值。

**【数据范围】**

对于 $20\%$ 的数据，$l,r\le2^{20}-1$。

对于 $50\%$ 的数据，$l,r\le2^{5\times10^3}-1$。

对于另外 $30\%$ 的数据，保证二进制数 $l$ 和 $r$ 的位数相同。

对于 $100\%$ 的数据，$1\le T\le10$，$1\le l\le r\le2^{5\times10^5}-1$，且 $l,r$ 没有前导零。

## 样例 #1

### 输入

```
2
110010000000 110110101100
1 10```

### 输出

```
3
1```

# 题解

## 作者：Swordmaker (赞：7)

# P12419 【MX-X12-T2】「ALFR Round 5」Dream of Sky

# 思路

如果两者长度不同，则可以构造出长度等于 $l$ 的长度且全为 $1$ 的序列，答案为 $1$。

否则，贪心寻找 $l$ 和 $r$ 第一个不一样的位置。

由于要求找最小的权值，所以我们尽量构造出一长串数字相等的结构。

将较小的数字在不一样的位置后面的数字全换成 $1$，而较大的则换成 $0$。

将两个新的数字和原来两个旧的数字进行比较，找最优解。

不要忘记特判 $l$ 和 $r$ 相等的情况。

# code
```cpp
#include<bits/stdc++.h>
#define int long long 
#define l1 l_1
#define l2 l_2
namespace AyanamiRei
{
	inline int read()
	{
		int x=0,f=1;
		char c=getchar();
		while(c>'9'||c<'0')
		{
			if(c=='-') f=-1;
			c=getchar();
		}
		while(c>='0'&&c<='9')
		{
			x=(x<<3)+(x<<1)+(c-'0');
			c=getchar();
		}
		return x*f;
	}
}
namespace SoryuAsukaLangley
{
	inline void write(int x)
	{
		if(x<0) putchar('-'),x=-x;
		if(x>9) write(x/10);
		putchar(x%10+'0');
		return;
	}
}
using namespace std;
using namespace AyanamiRei;
using namespace SoryuAsukaLangley;
int t,l1,l2;
string a,b;
inline void solve()
{
	if(l1!=l2)
	{
		write(1);
		putchar('\n');
		return;
	}
	int pos=0,ans1=1,ans2=1,ans3=1,ans4=1;
	for(int i=1;i<l1;i++)
	{
		if(a[i]!=a[i+1]) ans3++;
	}
	for(int i=1;i<l2;i++)
	{
		if(b[i]!=b[i+1]) ans4++;
	}
	for(int i=1;i<=l2;i++)
	{
		if(a[i]!=b[i])
		{
			pos=i;
			break; 
		}
	}
	if(!pos)
	{
		write(min(ans3,ans4));
		putchar('\n');
		return;
	}
	for(int i=pos+1;i<=l2;i++)
	{
		a[i]='1',b[i]='0';
	}
	for(int i=1;i<=pos;i++)
	{
		if(a[i]!=a[i+1]) ans1++;
	}
	for(int i=1;i<=pos;i++)
	{
		if(b[i]!=b[i+1]) ans2++;
	}
	int ans=min({ans1,ans2,ans3,ans4});
	write(ans);
	putchar('\n');
	return;
}
signed main()
{
	t=read();
	while(t--)
	{
		cin>>a>>b;
		l1=a.length(),l2=b.length();
		a=" "+a,b=" "+b;
		solve();
	}
	return 0;
}
```

---

## 作者：Guoshihao123 (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/P12419)
## 题意
定义一个 $01$ 串 $s$ 的权值为最小的 $k$ 使得 $s$ 能被分割成 $k$ 个子串，且每个子串的各个字符都**相等**。  

现有一个二进制数 $n \in [l , r]$，求 $n$ 转化为 $01$ 字符串（不含前导零）后的权值最小是多少。

## 思路
这里为了方便讲解，我们将 $l$ 的长度记为 $lenl$， $r$ 的长度记为 $lenr$。  

显而易见，如果 $lenl<lenr$，那么 $k=1$，此时字符串 $n$ 为 $lenl$ 个 $1$。所以一定有 $r>n$；因为 $l$ 和 $n$ 的长度都是 $lenl$，所以一定有 $n \geq l$；符合题意，且此时权值 $k$ 最小。

若 $lenl=lenr$，那么我们直接按位匹配，直到出现第一个不同的字符为止。因为 $l \leq n \leq r$，所以 $n$ 的前缀一定是 $l$ 和 $r$ 的**最长公共前缀**。同时记录前缀的权值 $k$。  

此时如果匹配了整个字符串都没有不同的字符，那么我们有 $l=n=r$，此时权值为 $k$。  

等我们找到第一个不同的字符时，记此时位数为 $i$，因为 $l < r$，所以 $l[i]=0，r[i]=1$。  

此时若 $l[i-1]=0$，那么我们匹配 $l$，直到出现第一个 $1$ 为止。因为此时 $l[i]=0$，可以与上一位的 $0$ 连接，所以我们继续匹配能连接的 $0$，直到匹配到 $1$ 为止，记此时位数为 $j$，此时字符串 $n$ 为 $l[0]$ 到 $l[j]$ 接 $lenl-j$ 个 $1$，此时权值 $+1$。若匹配了整个字符串都没有 $1$，此时 $l=n$，权值为 $k$；否则权值为 $k+1$。  

若 $l[i-1]=1$，与上面同理，但匹配 $r$，直到出现第一个 $0$ 为止。若匹配了整个字符串都没有 $0$，此时 $l=n$，权值为 $k$；否则权值为 $k+1$。 

时间复杂度为 $O(n)$。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN=5e5+10;
int t;

int main(){
	cin >>t;
	while (t--){
		char l[MAXN],r[MAXN];
		cin >>l >>r;
		int n=strlen(l),m=strlen(r);
		if (n<m){
			cout <<1 <<endl;
			continue;
		}
		bool op=1;
		int ans=1,i=0;
		for (;l[i]==r[i]&&i<n;i++)
			if (l[i]-'0'!=op) op=!op,ans++;
		if (i==n) cout <<ans <<endl;
		else if (op){
			while (r[i]=='1'&&i<n)
				i++;
			if (i==n) cout <<ans <<endl;
			else cout <<ans+1 <<endl;
		} else{
			while (l[i]=='0'&&i<n)
				i++;
			if (i==n) cout <<ans <<endl;
			else cout <<ans+1 <<endl;
		}
	}
	return 0;
}
```

---

## 作者：l15130880055 (赞：5)

## P12419 【MX-X12-T2】「ALFR Round 5」Dream of Sky 题解

### Problem
定义 $s$ 的权值为最小的 $k$ 使得字符串 $s$ 分割成 $k$ 个各个字符都相同的子串，给定二进制数 $l,r$，找到 $[l,r]$ 中权值最小的数，答案为这个最小的权值。

### Solution
不难看出对于一个字符串 $s$，它的权值就是 `01` 子串的数量加上 `10` 子串的数量再加一，问题转化成了根据这个性质找到一个最优的 $n \in [l,r]$。

要想权值最小，等价于使 `10` 和 `01` 这样的子串最少，所以考虑找到一个后面全是相同数字的 $n$，因为要 $n \in [l,r]$，所以在 $l,r$ 第一个不同的字符放 `0` 后面就可以随便构造，那么就有四种情况。

如果 $l$ 本来后面就全是 `0`，那就不用改。否则将 $l$ 后面全改成 `1`。

如果 $r$ 本来后面就全是 `1`，那就不用改。否则将 $r$ 后面全改成 `0`。

四种情况分别算答案取最小值即可。

### Code

```cpp
std::string l, r; 
int out;
inline void solve() {
	out = 0;
	std::cin >> l >> r;
	if(l.size() != r.size()){
		Fastio::cout << 1 << '\n';
		return;
	}
	for(int i = 0; i < l.size(); i++){
		if(l[i] != r[i]){
			int f = 0;
			for(int j = i + 1; j < l.size(); j++){
				f |= (l[j] == '1');
			}
			if(f){
				for(int j = i + 1; j < l.size(); j++){
					l[j] = '1';
				}	
			}
			f = 0;
			for(int j = i + 1; j < l.size(); j++){
				f |= (r[j] == '0');
			}
			if(f){
				for(int j = i + 1; j < l.size(); j++){
					r[j] = '0';
				}	
			}
			break;
		}
	}
	for(int i = 0; i < l.size() - 1; i++){
		if(l[i] != l[i + 1]){
			out++;
		}
	}
	int u = 0;
	for(int i = 0; i < r.size() - 1; i++){
		if(r[i] != r[i + 1]){
			u++;
		}
	}
	Fastio::cout << std::min(u, out) + 1 << '\n';
}
```

---

## 作者：wmrqwq (赞：4)

验题人题解。

# 题目链接

[「ALFR Round 5」B Dream of Sky](https://www.luogu.com.cn/problem/P12419)

# 题意简述

定义一个 01 串 $s$ 的权值为最小的 $k$ 使得 $s$ 能被分割成 $k$ 个子串，且每个子串的各个字符都相等。例如，`1011110000010000` 的权值为 $6$。

现有一个二进制数 $n\in[l,r]$，求 $n$ 转化为 01 字符串（不含前导零）后的权值最小是多少，即，求 $[l,r]$ 中权值最小的 $n$ 的权值。

# 解题思路

注意到直接进行贪心很难满足数字在 $l \sim r$ 之间的限制，考虑从高位往低位贪心。
				
考虑从高位往低位贪心时，设 $l$ 这一个二进制位为 $a$，$r$ 这一个二进制位为 $b$，则会有以下几种情况：

- $a = b = 0$，此时 $x$ 这一位只能取 $0$，$x$ 这一位取 $0$ 后继续做下一位。
					
- $a = b = 1$，此时 $x$ 这一位只能取 $1$，$x$ 这一位取 $1$ 后继续做下一位。
   
- $a = 0$，$b = 1$，此时 $x$ 这一位可以取 $0$ 或 $1$，此时我们分讨 $x$ 这一位的取值：

  - 若 $x$ 这一位取 $0$，则后面持续取 $0$ 不会增加新的段数，如果可以，则答案可以为此时的连续段数，否则若后面持续取 $0$ 不合法，则后面持续取 $1$ 显然只会将连续段数 $+1$ 且一定合法，原因显然。
  					
  - 若 $x$ 这一位取 $1$，则后面持续取 $1$ 不会增加新的段数，如果可以，则答案可以为此时的连续段数，否则若后面持续取 $1$ 不合法，则后面持续取 $0$ 显然只会将连续段数 $+1$ 且一定合法，原因显然。
 
时间复杂度 $O(n)$。

# 参考代码

```cpp
ll n;
string l,r;
ll ans;
void solve()
{
    cin>>l>>r;
    n=l.size();
    l=' '+l,r=' '+r;
    if(l.size()!=r.size())
    {
        cout<<1<<endl;
        return ;
    }
    forl(i,1,n)
    {
        if(l[i]!=r[i])
        {
            ll s=0;
            if(l[i-1]=='0')
            {
                forl(j,i,n)
                    s+=l[j]=='0';
                if(s==n-i+1)
                {
                    cout<<ans<<endl;
                    return ;
                }
                cout<<ans+1<<endl;
                return ;
            }
            if(l[i-1]=='1')
            {
                forl(j,i,n)
                    s+=r[j]=='1';
                if(s==n-i+1)
                {
                    cout<<ans<<endl;
                    return ;
                }
                cout<<ans+1<<endl;
                return ;
            }
            return ;
        }
        else
            ans+=l[i]!=l[i-1];
    }
    cout<<ans<<endl;
}
```

---

## 作者：Heyg_future (赞：4)

# 【MX-X12-T2】「ALFR Round 5」Dream of Sky
## [题目传送门](https://www.luogu.com.cn/problem/P12419)
## Solution
看到本题，因为数据极大，所以第一时间要排除暴力，~~虽然时限比较宽~~。所以考虑贪心。

### 贪心思路
分为两种情况讨论。

当 $l$ 的长度比 $r$ 的长度短时，区间内必有一个二进制数所有位数均为 $1$。此时答案为 $1$，直接特判，不多解释了。

当 $l$ 的长度与 $r$ 的长度相等时，就需要好好判断了。

可以把题目转换为将 $l$ 或 $r$ 改变若干位，**使改变后的新数在原区间内，且权值最小**。可以从高位往低位进行贪心。当两数第 $i$ 位的数值相等时，就继续往下一位看直到出现不一样的为止，因为 $l<r$，所以此时 $l_i$ 必为 $0$，并且 $r_i$ 必为 $1$。那么此时前 $i$ 位已不可改变了，且权值已经定好，我们只要讨论从 $i+1$ 位开始后面的如何改变即可。

因为改变之后的数大于 $l$，所以 $l$ 的后面只能改 $0$ 为 $1$，同理 $r$ 的后面只能改 $1$ 为 $0$。因为已经确定第 $i$ 位以前的了，所以后面怎么改都可以，所以全部改为一样的 $1$ 或 $0$ 就可以使后端权值最小了。

此部分代码如下。
```cpp
ll s=0,i;
for(i=0;i<l.size();i++){
  if(l[i]!=r[i]){
    break;
  }
}
for(ll k=i+1;k<l.size();k++) l[k]='1',r[k]='0';
```
这样就可以将贪心过后的两个最优字符串计算出来了。此时只要统计哪个权值最小即可。统计的代码如下。
```cpp
ll f(string l){
	ll s=1;
	for(ll i=1;i<l.size();i++){
		if(l[i]!=l[i-1]) s++;
	}
	return s;
  //只要有与前一位不一样的，就视作一个部分，s++
}
```
最终代码如下。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
string l,r;
ll T;
ll f(string l){
	ll s=0;
	for(ll i=1;i<l.size();i++){
		if(l[i]!=l[i-1]) s++;
	}
	return s+1;
}
int main(){
	cin>>T;
	while(T--){
		cin>>l>>r;
		if(l.size()<r.size()) cout<<1;
		else{
			ll s=0,i;
			for(i=0;i<l.size();i++){
				if(l[i]!=r[i]){
					break;
				}
			}
			s=min(f(l),f(r));//要注意，边界也要计算
			for(ll k=i+1;k<l.size();k++) l[k]='1',r[k]='0';
			s=min({f(l),f(r),s});
			cout<<s;
		}
		cout<<"\n"; 
	}
    return 0;
}
```
这样就可以通过此题啦。

---

## 作者：haoyan1103 (赞：3)

## 题目大意
题目要求 $l$ 到 $r$ 区间内 $01$ 串的权值最小值。

一个 $01$ 串的权值指连续的 $0$ 或 $1$ 的数量。

例：$01$ 串 ```1101000``` 的权值为 $4$。

## 分析
简单的思考后我们可以得到：当 $l$ 的长度不等于 $r$ 的长度时，答案一定是 $1$。

因为当 $l$ 的长度不等于 $r$ 的长度时，长度为 $l$ 的长度的所有数位都是 $1$ 的 $01$ 串就是一个答案。

例：$l$ 是 ```1101000```，$r$ 是 ```11001001```，$01$ 串 ```1111111``` 就满足条件。

当 $l$ 的长度等于 $r$ 的长度时，设它们长度为 $n$，就先按 $l_i$ 等于 $r_i$ 来填 $01$ 串。当 $l_i$ 不等于 $r_i$ 时，$l_i$ 肯定等于 $0$，$r_i$ 肯定等于 $1$。

这样就相当于又分出了两个长度不同的 $01$ 串。$l_{i+1}$ 到 $l_n$ 一个，$r_i$ 到 $r_n$ 一个。

但有 $2$ 个特殊情况：
- 当 $l_{i+1}$ 到 $l_n$ 全为 $0$ 的情况。
- 当 $r_i$ 到 $r_n$  全为 $1$ 的情况。

需要特判一下。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
int t,ans;
string L,R;
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>L>>R;ans=0;L=" "+L,R=" "+R;
		if(L.size()!=R.size() && L.size()!=1){cout<<"1\n";continue;}//长度不相等的情况 
		for(int i=1;i<L.size();i++)
        {
            if(L[i]==R[i])
            {
                if(i==1)continue;
                ans+=(L[i]!=L[i-1]);//L[i] 等于 R[i] 直接填 
            }
            else
            {
                bool flag1=1,flag2=1;
                for(int j=i;j<L.size();j++)
                {
                    if(j!=i && L[j]!='0')flag1=0;
                    if(R[j]!='1')flag2=0;
                }
                if(flag1 && flag2)ans+=min((L[i]!=L[i-1]),(R[i]!=R[i-1]));
                else if(flag1)ans+=(L[i]!=L[i-1]);
                else if(flag2)ans+=(R[i]!=R[i-1]);//特判 
                else ans++;
                break;
            }
        }
		cout<<ans+1<<"\n";//ans 表示 01 断开的地方,答案要加 1 
	}
	return 0;
}
```

---

## 作者：JIN_LONG (赞：2)

## 思路：
本题的大致题意为让我们找到在二进制区间 $r$ 与 $l$ 中，权值最小的数。

这里解释一下权值是什么，将该数的二进制表示分割成最少段数，使得每段都是全 $0$ 或全 $1$，就是把这个二进制数当成一个字符串，如果字符串的第 $i$ 个与第 $i+1$ 个不同，就分开。权值则是分开后字符串一共分为了几段。

代码实现的步骤如下。

- 位数不同情况，直接输出 $1$ 即可。
- 位数相同时，我们需要比较 $l$ 和 $r$ 的二进制表示，找出最小的权值。
- 遍历字符串的每一位，如果 $r$ 当前位是 $0$ 且当前状态是 $1$ 且还没有遇到 $r$ 的限制（$qr$ 不为零时），就切换状态到 $0$，权值加上一，第二种情况同理。
- 检查是否遇到 $l$ 或 $r$ 的限制，遍历完后输出计算出的权值。
## 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
    int T;
    cin>>T;
    while(T--){
        string l,r;
        cin>>l>>r;
        // 如果l.size()<r.size()，直接输出1（可以构造全1的数）。 
        if(l.size()<r.size()){
            cout<<'1'<<endl;
        }
        else {
            int q=1,sum=1; // q表示当前状态（1或0），sum记录权值。 
            bool ql=0,qr=0; // 标记是否遇到l或r的限制
            for(int i=0;i<l.size();i++){
                // 如果r当前位是0且状态是1且没有r的限制，切换到0状态。 
                if(r[i]=='0'&&q==1&&!qr){
                    q=0;
                    sum++;
                }
                // 如果l当前位是1且状态是0且没有l的限制，切换到1状态。 
                else if(l[i]=='1'&&q==0&&!ql){
                    q=1;
                    sum++;
                }
                // 检查是否遇到l的限制（l当前位是0但状态是1）。 
                if(l[i]=='0'&&q==1){
                    ql=1;
                }
                // 检查是否遇到r的限制（r当前位是1但状态是0）。 
                if(r[i]=='1'&&q==0){
                     qr=1;
                }
            }
            cout<<sum<<endl;
        }
    }
    return 0;
}

```

---

## 作者：Sunset_afterglow (赞：2)

~~666，赛时交了 6 发才过。~~
# 题意
构造出一个二进制串，使得 01 分的段更少。
# 思路
记录一个`flag_1`，和`flag_2`，表示构造的二进制串，是否比 $l$ 大，是否比 $r$ 小，当其中一个值为`true`时，那么这个就直接不考虑了，当两个的值都为`true`时，直接跳出去，因为接下来取值不受 $l,r$ 影响，所以都可以取与上一个一样的值。  
接下来，重点考虑当两个都不满足时，分类讨论一下，有全等 $0 ,1$，或者 $0$ 和 $1$，$1$ 和 $0$ 不用考虑，因为当出现时，肯定不会跳到这种情况来。  
全等 $0$ 与全等 $1$ 的情况，都是考虑这个点与上一个点不同，导致对答案的贡献，因为这种情况下，二进制串这一位时确定的。
$0$ 和 $1$ 的情况，就是如果上一位是 $0$，那么`flag_2 = true`，不然`flag_1 = true`。
# 代码（有点乱）
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read() {
  int x = 0 ,f = 1;
  char ch = getchar();
  while('0' > ch || ch > '9'){
    if(ch == '-') f = -1;
    ch = getchar();
  }
  while('0' <= ch && ch <= '9') {
    x = (x << 1) + (x << 3) + (ch & 15);
    ch = getchar();
  }
  return x * f;
}
int T;
string str1 ,str2;
void sovle() {
  cin >> str1 >> str2;
  if(str1.size() < str2.size()) {cout << 1 << '\n';return ;}
  bool flag_1 = 0 ,flag_2 = 0; // flag_1 是否比起点大，flag_2 是否比终点小 
  bool vis = 1;
  int m = 1;
  for(int i = 1;i < str1.size();++ i) {
    if(flag_1 && flag_2) break;
    if(flag_1 && !flag_2) {
      if(str2[i] == '1') {
        if(!vis) flag_2 = true;
      }
      else {
        if(vis) {
          vis = 0;
          ++ m;
        }
      }
      continue;
    }
    if(!flag_1 && flag_2) {
      if(str1[i] == '1') {
        if(!vis) {
          vis = 1;
          ++ m;
        }
      }
      else {
        if(vis) {
          flag_1 = true;
        }
      }
      continue;
    }
    if(str1[i] == '0' && str2[i] == '0') {
      if(vis) {
        vis = 0;
        ++ m;
      }
    }
    else if(str1[i] == '1' && str2[i] == '1') {
      if(!vis) {
        ++ m;
        vis = 1;
      }
    }
    else if(str1[i] == '0' && str2[i] == '1') {
      if(vis) flag_1 = true;
      else flag_2 = true;
    }
  }
  cout << m << '\n';
  return ;
}
signed main() {
  T = read();
  while(T --)sovle();
  return 0;
}
```

---

## 作者：lcycl (赞：1)

## 思路
显然的贪心。贪心的思路十分简单，当前的一位尽可能与上一位一样，若和上一位一样时数字已经不在区间范围内，则当前数位取另一个数，计数变量加一。  

此外，还需注意的是，当 $l$ 和 $r$ 的长度不一样时，直接输出 $1$。  

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin>>T;
	string l,r;
	while(T--){
		cin>>l>>r;
		char tag='1';
		int sum=1;//计数变量（因为一开始就有一段，所以是1）
		bool flagl=0,flagr=0;//当flagl=1时，当前数字大于l，当flagr=1时，当前数字小于r
		if(l.size()!=r.size()){
			cout<<"1\n";
			continue;
		}//特判
		for(int i=0;i<l.size();i++){
			if(r[i]=='0'&&tag=='1'&&!flagr) tag='0',sum++;//若超出范围，则改变当前数位，计数变量加一
			else if(l[i]=='1'&&tag=='0'&&!flagl) tag='1',sum++;//同上
			if(l[i]=='0'&&tag=='1') flagl=1;//判断，若高位已经在范围内，则剩下怎么放都行
			if(r[i]=='1'&&tag=='0') flagr=1;//同上
		}
		cout<<sum<<"\n";
	}
	return 0;
}
```

---

## 作者：aljz (赞：0)

## 题目描述
定义一个 01 串 $s$ 的权值为最小的 $k$ 使得 $s$ 能被分割成 $k$ 个子串，且每个子串的各个字符都相等。

现有一个二进制数 $n\in[l,r]$，求 $n$ 转化为 01 字符串（不含前导零）后的权值最小是多少。

## 题目分析
首先来解释一下字符串的权值怎么求，其实就是找这个字符串两个相邻但不同的数出现的个数再加上一即为这个字符串的权值。

了解了权值怎么求之后，就想着怎么才能让权值最小。

当 $l$ 和 $r$ 的两个字符串长度不想等时，可以直接把 $l$ 字符串的所有字符全变成 1，所以最后答案直接输出 1 即可。

当 $l$ 和 $r$ 的两个字符串长度相等时，首先先记录一下两个字符串未更改时的权值，然后找两个字符串第一个数字大小不相同的并记录这个数，然后将 $l$ 字符串这个数后面的所有数全改成 1，将 $r$ 字符串这个数后面的所有数全改成 0，结果即为两个字符串未更改时的权值和两个字符串更改完后的权值的最小值。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
string l,r;
void solve()
{
	cin >> l >> r; 
	int nl=l.length(),nr=r.length();
	if(nl == nr)
	{
		int i;
		for(i=0;i<nl;++i)
		{
			if(l[i]!=r[i]) break;//找到两个字符串第一个数字大小不相同并记录位置
		}
		int  p=0,q=0;//两个字符串未更改时的权值
		for(int j=0;j<nl;++j)
		{
			if(l[j]!=l[j-1]) ++p;
		}
		for(int j=0;j<nr;++j)
		{
			if(r[j]!=r[j-1]) ++q;
		}
		for(int j=i+1;j<nl;++j) l[j]='1';
		for(int j=i+1;j<nr;++j) r[j]='0';
		int cnt=0,res=0;//两个字符串更改完后的权值
		for(i=0;i<nl;++i)
		{
			if(l[i]!=l[i-1]) ++cnt;
		}
		for(i=0;i<nr;++i)
		{
			if(r[i]!=r[i-1]) ++res;
		}
    //结果即为两个字符串未更改时的权值和两个字符串更改完后的权值的最小值
		cout << min(min(p,q),min(res,cnt)) << '\n'; 
	}
	else if(nl != nr)
	{
		cout << 1 << '\n';//不相等答案即为1
	}
}
signed main()
{
	cin >> T;//多组数据
	while(T--)
	solve();
	return 0;
}

```

---

## 作者：N0_1 (赞：0)

## 简单贪心

### 长度相同时
1. $l = r$ 时直接输出答案即可。
2. $l \neq r$，找到最小的 $i$ 满足 $l_{i} \neq r_{i}$，此时 $l_{i} = 0, r_{i} = 1$，则显然可以将 $l$ 变成如下形式： 

- $s_{1}=l_{0}l_{1}l_{2}\dots l_{pos-1}1000\dots$

- $s_{2}=l_{0}l_{1}l_{2}\dots l_{pos-1}0111\dots$。

考虑两种种特殊的情况:

$l=10100000, r = 11111111$，此时最优解为 $r$。

$l=10000000, r = 10111111$，此时最优解为 $l$。

四种情况取一下 $\min$ 即可。


### 长度不同时
显然可以构造出长度为 $|l| + 1$ 的全 $1$ 串，答案为 $1$。



#### code
```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

int calc(string s) {
    int cnt = 1;
    for (int i = 1; i < s.size(); i++) {
        if (s[i] ^ s[i - 1]) cnt ++;
    }
    return cnt;
}
void solve() {
    string s, t;
    cin >> s >> t;
    if (s.size() < t.size()) {
        cout << 1 << '\n';
        return ;
    }
    // s.size() == t.size()

    if (s.size() == 1) return cout << 1 << '\n', void();
    if (s == t) return cout << calc(s) << '\n', void();

    int len = s.size(), pos = 0;
    for (int i = 1; i < len; i++) {
        if (s[i] != t[i]) {
            pos = i;
            break;
        }
    }

    string tmp = s.substr(0, pos) + '1' + string(len - pos - 1, '0');
    string tmp2 = s.substr(0, pos) + '0' + string(len - pos - 1, '1');
    cout << min({calc(tmp), calc(s), calc(tmp2), calc(t)}) << '\n';
}

int main() {
    int T;
    cin >> T;
    while (T --) {
        solve();
    }
    return 0;
}
```

---

