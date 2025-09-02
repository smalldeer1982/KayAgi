# Ability To Convert

## 题目描述

亚历山大正在学习如何把十进制数字转换成其他进制，但是他不懂英文字母，所以他只是把数值按照十进制数字的方式写出来。这意味着他会用 10 代替英文字母 A。这样，他就会把十进制的 475 转换成十六进制的 11311（475=1·16^2+13·16^1+11·16^0）。亚历山大平静的生活着，直到有一天他试着把这些数字转换回十进制数字。

亚历山大记着他总是用较小的数字工作，所以他需要找到在 n 进制的基础下，用他的转换系统得出数字 k 的最小十进制数。

## 样例 #1

### 输入

```
13
12
```

### 输出

```
12```

## 样例 #2

### 输入

```
16
11311
```

### 输出

```
475```

## 样例 #3

### 输入

```
20
999
```

### 输出

```
3789```

## 样例 #4

### 输入

```
17
2016
```

### 输出

```
594```

# 题解

## 作者：Miraik (赞：5)

简单贪心。

要使划分出来的各位数小于 $n$，并且最后拼在一起尽可能小，我们从低位向高位做，每次划分出的数尽可能大，这样保证总位数最小，且最高位尽可能小，显然最优。

然后就没了？

那你就错啦，还是有一点点小坑的：

- 从后向前枚举，当前划分出的数 $\ge n$ 时，我们不能划分到这里，必须往回一步。但注意此时我们不能允许前导 $0$ 的出现，因此预处理一个 $lst$ 数组，$lst_i$ 表示从第 $i$ 位向后第一个非 $0$ 数字（不包括 $i$）然后在向回走时直接 ```j=lst[j]``` 即可。

- 注意极端数据！！极端情况下由于 $k$ 达到 $60$ 位，计算时 $10^{60}$ 会爆 ```unsigned long long```。对此我的做法是：$n\le10^9$，因此出现这种情况必然就是有大段的连续 $0$，且到达下一位非 $0$ 数时必然不符合条件，我们判断如果此时数字的位数已经大于 $9$ 位，直接跳到 ```j=lst[j]``` 这步即可。

还算清晰的完整代码，其实也很好写就是了：

```cpp
#include<bits/stdc++.h>
#define int ll
using namespace std;
typedef unsigned long long ll;
inline int read(){
	int x=0;char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x;
}
int n,m,x[65],lst[65],ans;
char s[65];
signed main(){
	n=read();
	scanf("%s",s+1);
	m=strlen(s+1);
	for(int i=m,j=m+1;i;i--){ //求出向后第一个非 0 数字 
		lst[i]=j;
		if(s[i]!='0') j=i;
	}
	int pwn=1;
	for(int i=m;i;i--){
		int pw10=1; x[i+1]=0;
		for(int j=i;j;j--,pw10*=10){
			x[j]=x[j+1]+pw10*(s[j]-'0');
			if(pw10>n||x[j]>=n){ // pw10>n ：大段 0，必然不满足条件 
				j=min(lst[j],i);
				ans+=x[j]*pwn;
				pwn*=n;
				i=j;
				break;
			}
			else if(j==1){ // 已经最高位了，直接判断即可 
				ans+=x[j]*pwn;
				pwn*=n;
				i=j;
			}
		}
	}
	printf("%llu\n",ans);
	return 0;
}
```


---

## 作者：Tx_Lcy (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF758D)
## 思路
虽然这是一道简单的贪心，但是细节还是挺多的。

根据贪心的想法，要使最后的和尽可能小，我们显然要划分成尽可能少的部分，所以我们考虑从后往前做，若遇到一个位置 $i$，把 $i$ 划到后面那个部分时非法了（其实就是和大于等于 $n$）。那么 $i$ 只能划分到前面那个部分。

+ 坑点 $1$：我们在划分的过程中要用字符串类型记录，如果用整型，那么遇到 $100$ 这种情况的答案会是 $1$。
+ 坑点 $2$：当遇到某个位置划分非法时，下次仍然要从这个位置开始考虑。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int len(int x){
	int res=0;
	if (!x) return 1;
	while (x) ++res,x/=10;
	return res;
}//求出一个数的位数
inline int toint(string s){
	int l=s.length(),qpow=1,res=0;
	for (int i=0;i<l;++i) res+=qpow*(s[i]-'0'),qpow*=10;
	return res;
}//把字符串转化成整型
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n;string s;cin>>n>>s;
	int l=s.length(),q=len(n-1),qpow=1,ans=0;
	s=" "+s;int la=l;
	while (la>=1){
		int tag=0;string res="";
		for (int j=la;j>=max(1LL,la-q+1);--j){
		    if (toint(res+s[j])>=n){
				ans+=qpow*toint(res);qpow*=n;
				tag=1;break;//非法了就 break
			}else res+=s[j];
		}
		la=la-len(toint(res));
		if (!tag) ans+=qpow*toint(res),qpow*=n;
	}
	cout<<ans<<'\n';
	return 0;
}
```



---

## 作者：SengRiy (赞：3)

[**更好的阅读**](https://www.luogu.com.cn/blog/HLXBK/cf758d-ti-xie)

[**题目传送门**](https://www.luogu.com.cn/problem/CF758D)

### 题意

给一个 $n$ 进制的数，把这个数分成若干数位，使最后转化成十进制的数最小。

### 思路

经过分析样例，一般就可以形成一个贪心的思路。

这里说下我的贪心思路：

+ 首先所需分的数位数最开始是不知道的，我们无法直接知道最高位，因此应从低位向高位枚举

+ 接下来，判断如何分数位：

	+ 将此时的数位与这一位的数记录下来
    
    + 每枚举一个数字，判断这个数字是否在此时数位中的贡献比在下一个数位中的小：（设此数字为 $t$ ，此时数位的数的位数为 $len$ ，此时的数位为 $c$ ，进制为 $n$ ，则可以得出此数字在此时数位中的贡献为 `t * pow(10, len) * c` ， 在下一个数位中的贡献为 `t * c * n`）
    	+ 是，则不新增位数
        
        + 否，则记录贡献（设此时数位的数为 $s$ ，此时的数位为 $c$ ，则此时数位贡献为 `s * c`）且新增位数。

### 注意事项

这题有许多坑点需要注意

+ 每个数位的数没有前导零。所以当你发现这个数位的数有前导零时，你需要回到前导零开始的地方

+ 数有可能会超 `unsigned long long` 。当你像我一样用一个变量记录$10$ 的数位中的数的位数次方，请立即改正成仅记录次方次数。

### 代码

```cpp
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int N = 65;

unsigned long long n, ans;
string x;

int main() {
  cin >> n >> x;
  
  unsigned long long s = 0, c = 1, len = 0;
  for (long long i = x.size() - 1; i >= 0; --i) {  // 从低位向高位枚举
    int t = x[i] - '0';
    if (t * pow(10, len) <= t * n && s + (t * pow(10, len)) < n) {  // 判断这个数字是否在此时数位中的贡献比在下一个数位中的小
      s = s + t * pow(10, len);
      len++;
    } else {
      ans += s * c;  // 记录贡献
      if (s == 0) {  // 判断有无前导零
        i += len - 1;
        t = x[i] - '0';
      } else if (floor(log10(s)) < len) {
        i += len - floor(log10(s)) - 1;
        t = x[i] - '0';
      }
      s = t;  // 新增数位
      len = 1;
      c *= n;
    }
  }
  ans += s * c;
  
  cout << ans;
  
  return 0;
}
```

~~2000 的题真的能紫吗~~

---

## 作者：SSHhh (赞：3)

这道题本来是可以贪心的，贪心思路楼下也讲过了，不过因为部分细节原因，这道题的贪心我打挂了(惨不忍睹连续 WA 10 次)，所以这道题我还是可怜地打 dp 去了(神犇勿喷)...

言归正传，这道题的区间 dp 思路是这样的：我们先用一个 f[i][j] 表示从第 i 位到第 j 位组成的十进制数是多少。比如对于一个数 1235 来说，f[2][4]=235; 在此基础上，dp[i][j] 表示从第 i 位到第 j 位，按照当前 n 进制转换，得出的最小结果是多少。

那么很显然，每一位 k 上，如果把当前 k+1~r 这段区间转成一个 n 进制数的一位，那么前面的 l~k 段(也是 n 进制数的一位)的指数一定比 k+1~r 多一。所以 dp[l][r]=min(dp[l][r],dp[l][k]·10+dp[k+1][l])

不过，对于每一个 dp[i][j] 所用到的区间需要判断当前状态所用到的 n 进制数是否合法，所以使用记忆化搜索就可以了。

具体细节还有一个，如果数字里面的某一段连续的 0 数量超过了 n 的位数-1，那么前(n的位数-1)个 0 可以并到前面的一个 n 进制数后面，剩下的每一个都是一位 0(因为每一个 n 进制数都不含前导 0)，也就是说后面有几个0，前面就多乘几个 n 。这个细节很重要，一定要处理好。

最后说一点，绝对不要使用 cmath 里面的 pow 函数，自己写快速幂都比那个好(我就因为这个问题 WA 了五次╮(╯﹏╰）╭)。。。

好了下面就是代码了：

```cpp
#include<iostream>
#define INF 9223372036854775807ll	//long long max
using namespace std;
unsigned long long n,m,ans,f[105][105],dp[105][105];
string a;
int dig(unsigned long long a)	//a 在十进制下有几位
{
    int ans=0;
    while(a)	a/=10,ans++;
    return ans;
}
unsigned long long quick_pow(unsigned long long a,int mi)
{
    unsigned long long b=1;
    while(mi) {if(mi&1)	b*=a; a*=a,mi>>=1;}
    return b;
}
unsigned long long dfs(int i,int j)	//记忆化搜索
{
    if(dp[i][j]!=INF)	return dp[i][j];
    int state=0,p;	//state 表示后面有几个0，p 表示从第 p+1 位开始有连续的一串 0
    for(p=j;a[p]=='0' && p>=i;p--)
        state++;
    state-=dig(n)-1;	//前(n的位数-1)个 0 可以并到前面的一个 n 进制数后面
    if(state>0)	return dp[i][j]=dp[i][j],quick_pow(n,state)*dfs(i,p+dig(n)-1);	//特判多乘 state 个 n
    if(f[i][j]<n)	return dp[i][j]=f[i][j];
    for(int k=i;k<=j-1;k++)
    {
        if(a[k+1]!='0' || (a[k+1]=='0' && k+1==j))
            dp[i][j]=min(dp[i][j],dfs(1,k)*n+dfs(k+1,j));	//转移
    }
    return dp[i][j];
}
int main()
{
    cin>>n>>a,m=a.size(),a=" "+a;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=m;j++)
            f[i][j]=dp[i][j]=INF;
    for(int i=1;i<=m;i++)	dp[i][i]=f[i][i]=a[i]-'0';
    for(int len=2;len<=dig(n);len++)	//枚举区间长度
        for(int i=1;i+len-1<=m;i++)
        {
            int j=i+len-1;
            f[i][j]=f[i][j-1]*10+a[j]-'0';	//初始化 f 数组
        }
    cout<<dfs(1,m)<<endl;
    return 0;
}
```

---

## 作者：Yuby (赞：1)

[题面](https://www.luogu.com.cn/problem/CF758D)

点数：2000

#### 题意：

给你两个数 $n$ 和 $m$ 求 10 进制下最小的等于 $m$ 的数，这里转 $n$ 进制是指把这个数按 $n$ 进制分解后首尾相连的数。

#### 分析：

我承认这题我完全没想到 dp 的方法，问题是我贪心过了呀。。。

这个题就是说把一个数按 $n$ 进制拆开计算得到的最小值。

按照 whk 上学的东西也应该能想到把低位尽量放大最优，这不直接就结束了。

定义 $k$ 为 $m$ 的十进制位数。

也就是说每次要不取 $k$ 位要不取 $k-1$ 位。

#### 细节：

1.一位可以空，但显然不能有前导 0。就是说把他拆为 $n$ 进制的时候要注意不能有前导 0，具体见代码。

2.这一判断这一部分有没有越界。

3.判断取出的部分是否可以为 $n$ 进制的时候注意 $n$ 进制下的每一位应该为 $[0,n-1]$ 中。

代码（165ms）：

```cpp
string n,k,tmp;
ll l,len;
int main()
{
    cin>>n>>k;
    l=n.length(),len=k.length();
    ll base=1,num=0;
    for(ll i=0;i<l;i++)
    {
    	num=num*10+(n[i]^48);
	}
	ll ans=0;
	for(ll i=len-1;i>=0;)
	{
		tmp.clear();
		ll used=l;
		bool flag=0;
		for(ll j=l-1;j>=0;j--)
		{
			if(i-j<0)//越界。。。 
			{
				used--;
				continue;
			}
			else if(!flag&&k[i-j]=='0')//前导0 
			{
				used--;
				continue;
			}
			tmp.push_back(k[i-j]);
			flag|=(1&1&1^1^1);
		}
		ll num=0;
		if(tmp>=n&&tmp.length()==l)
		{
			tmp.clear();
			flag=0;
			used=l-1;
			for(ll j=l-2;i-j>=0&&j>=0;j--)
			{
				if(i-j<0)//越界
				{
					used--;
					continue;
				}
				else if(!flag&&k[i-j]=='0')//前导0 
				{
					used--;
					continue;
				}
				tmp.push_back(k[i-j]);
				flag|=(1&1&1^1^1);
			}
		}
		i-=max(used,1);
		for(ll j=0;j<tmp.length();j++)
			num=num*10+(tmp[j]-'0');
		ans+=num*base;
		base*=num;//注意进制问题
	}
	write(ans);
	return 0;
}
```





---

## 作者：legendgod (赞：1)

[CF758D Ability To Convert](https://www.luogu.com.cn/problem/CF758D)

我们考虑划分出一个数的过程实际上相当于对序列进行切割。

我们设 $f[i]$ 表示当前已经计算到第 i 个数了。

我们考虑向后转移 $f[j] = \min(f[j], f[i] \times n+  x)$。

注意我们一开始赋值极大值的时候会导致 $f[i] \times n$ 爆 $\tt unsigned\ long \ long$。

所以我们可以转移的条件是 $f[i] < \frac{\inf}{n}$。

之后考虑对于当前位置是 0 的情况，显然不能使其变成前导零，那么我们只能将其转移到 $f[i + 1]$ 的位置，也就是让它单独拿出来。

```cpp
#include <bits/stdc++.h>
using namespace std;

//#define Fread

#ifdef Fread
#define getchar() ((p1 == p2 && p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin)) ? EOF : *p1 ++)
char buf[1 << 21], *p1, *p2;
#endif // Fread

template <typename T>
void r1(T &x) {
	x = 0;
	char c(getchar());
	int f(1);
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c);c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
	x *= f;
}

const int maxn = 1e3 + 5;
const int maxm = maxn << 1;
typedef unsigned long long ull;
const ull inf = 2e18;
typedef int room[maxn];

ull n;
int m, lc;
char c[maxn];
ull f[maxn];
signed main() {
//    freopen(".in", "r", stdin);
//    freopen(".out", "w", stdout);
	int i, j;
    r1(n);
    scanf("%s", c + 1); lc = strlen(c + 1);
    for(i = 2; i <= lc + 1; ++ i) f[i] = inf;
    f[1] = 0;
    for(i = 1; i <= lc; ++ i) {
        if(c[i] == '0') {
            if(f[i] > inf / n) continue;
            f[i + 1] = min(f[i + 1], f[i] * n);
        }
        else {
            ull x(0);
            for(int j = i + 1; j <= lc + 1; ++ j) {
                x = (x * 10ull + c[j - 1] - '0');
                if(x >= n) break;
                if(f[i] > inf / n) continue;
                f[j] = min(f[j], f[i] * n + x);
            }
        }
    }
    printf("%llu\n", f[lc + 1]);
	return 0;
}

```



---

## 作者：AC自动机 (赞：0)

### 思路
首先会情不自禁向dp去想，但是仔细想想，贪心好像也有一定道理，因为想要转化得到的十进制数最小，因为转进制数的方式是这样的，如样例所示：5=1⋅13^1+2⋅13^0

因此转换成n进制的数，所以当最小是当然有每一位最大，这样这个n进制的数的位数可以尽可能短qwq,所以应该没有什么问题，然后就试着写了一份贪心，然后就AC了つ﹏⊂。

### 灰常重要的东西！！！(╯▔皿▔)╯

本题是一道细节题，需要处理大量的细节问题，有以下细节：

1.因为一般的做法是从后向前扫描字符串，并将其转换成十进制数，比较和n的大小，也就是能不能选到这一位，选不到就从这里分隔开，然后继续计算n进制数的下一位，但是是这样会出现一个问题，如一个50进制数：100000000000000000001，如果从字符串的最后一位开始，边选边算，当算到第一位的1的时候，发现已经大于n，这时候不能直接把1作为开头继续计算，因为如果这样的话，后面选的n进制数的一位就是00000000000000000001，显然这样的数是不存在的qwq，所以每次找到比n更大的十进制数时，一定要向回找，直到没有0或者当前十进制数的第一位，**注意**，千万不能一直顺着0向回找，而不管当前选的十进制数有多少位，不然像上面的例子，选了最后一位的1后再从倒数第二位的0开始向前选，然后选到第一位发现不行，向后一直退到倒数第二位，又等于没选，其实向后推到倒数第三位的十进制数位数已经变成了1，就不能再往后推了，否则会陷入死循环23333


2.有些极端数据会导致当前的十进制数溢出，要特殊判断！！

#### 极其优美の代码
```cpp
#include<iostream>
#include<cstring>
using namespace std;
int n;
string s;
int main(){
	cin>>n;    cin>>s;
	long long ans=0,fcheng=1;
	for(register int i=s.size()-1;i>=0;){
		long long now=0,cheng=1,wei=0,flag=1;
		for(register int j=i;j>=0;){
			if(now+(s[j]-'0')*cheng<n&&now+(s[j]-'0')*cheng>=0){
				now+=(s[j]-'0')*cheng,cheng*=10,j--,wei++;
				if(j<0){
					ans+=fcheng*now;
					cout<<ans<<endl;
					return 0;
				}
			}
			else if(now+(s[j]-'0')*cheng>=n||now+(s[j]-'0')*cheng<0){   
				while(s[j+1]=='0'&&wei!=1)j++,cheng/=10,wei--;     //当超出时，循环向回选，注意选的位数不能退回0位
				i=j,flag=0;
			}
			if(flag==0)break;
		}
		ans+=now*fcheng,fcheng*=n;
	}
	cout<<ans<<endl;
}
```

---

