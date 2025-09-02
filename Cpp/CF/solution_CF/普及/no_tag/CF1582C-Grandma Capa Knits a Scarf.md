# Grandma Capa Knits a Scarf

## 题目描述

给一个由小写字母组成的字符串 $s$ ，选择一个字母，删去这个字符串中任意个这个字母，使这个字符串变成回文的。如果存在多个答案，输出删除的字母个数最少的答案。

## 说明/提示

$1\le t\le100,1\le n\le10^5,1\le\sum n\le2\times10^5$ 。
### 样例解释
第一组数据，删除 $2$ 个 $a$ ，字符串变为 $bcaacb$ 。

第二组数据，方案不存在。

第三组数据，字符串本身就是回文的。

第四组数据，删除 $3$ 个 $r$ ，字符串变为 $palap$ 。

第五组数据，删除 $2$ 个 $y$ ，字符串变为 $khyhhyhk$ 。

## 样例 #1

### 输入

```
5
8
abcaacab
6
xyzxyz
4
abba
8
rprarlap
10
khyyhhyhky```

### 输出

```
2
-1
0
3
2```

# 题解

## 作者：Cht_master (赞：3)

- 题意简述：给定字符串 $\texttt{S}$，可以删除其中的任意一种字符若干个，求使 $\texttt{S}$ 回文最少需要删除多少个字符。无解输出 `-1`。多组测试，$1\le t\le 100$，$|\texttt{S}|\le 10^5$，$\sum|\texttt{S}|<=2\cdot 10^5$。
- 题目解析：
  - 字符集很小，考虑枚举删除哪种字符，记为 $del$。
  - 由于要求回文，那么考虑维护双指针 $l,r$ 从两端往中间扫。
    - 如果 $\texttt{S(l)}=\texttt{S(r)}$，那么不用删除；
    - 否则需要删掉一边。
      - 如果 $\texttt{S(l)}$ 和 $\texttt{S(r)}$ 都不是 $del$，那么当前方案不可行；
      - 如果 $\texttt{S(l)}$ 和 $\texttt{S(r)}$ 中任何一个是 $del$，那么相应的给计数器加 1，指针进行对应移动即可。

- ```cpp
  //枚举删那种字符:双指针,从两头往中间扫,如果不匹配就删除;
  //如果删除之后是两种不可删除字符,就说明当前删法是不行的.
  #include<bits/stdc++.h>
  using namespace std;
  const int mxN(2e5),mxS(26);
  int n,ans;char s[mxN+5];
  int main(){
  	int T;scanf("%d",&T);
  	while(T--){
  		scanf("%d%s",&n,s+1),ans=n+1;
  		for(int i(0);i<mxS;++i){//枚举删哪种字符.
  			char del(i+'a');int sm(0),l(1),r(n);
  			while(l<=r){
  				if(s[l]==s[r])++l,--r;
  				else{
  					if(s[l]==del){++sm,++l;continue;}
  					if(s[r]==del){++sm,--r;continue;}
  					sm=n+1;break;//是两种不可删除字符.
  				}
  			}
  			ans=min(ans,sm);
  		}
  		printf("%d\n",((ans==n+1)?(-1):(ans)));
  	}
  	return 0;
  }
  ```

  

---

## 作者：KSToki (赞：1)

# 题目大意
给定一个长度为 $n$ 的仅含小写字母的字符串 $s$，需要删除尽可能少的相同字符使得删除后的字符串是回文串。
# 题目分析
字符集大小只有 $26$，可以枚举删除哪个字母，两个指针暴力从两边往中间扫，不一样如果没有枚举的那个字母则无法选择这个字母，有那就删除它，对应边的指针移动一位，一样就同时移动一位，最后比较一下统计答案就可以了。
# 代码
```cpp
#include<bits/stdc++.h>
#define YPC rubbish 
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first
#define se second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define chkmin(x,y) (x=min(x,y))
#define chkmax(x,y) (x=max(x,y))
#define inv(x) ksm(x,mod-2)
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
#define For(i,x,y) for(R int i=x;i<=y;++i)
#define For2(i,x,y,k) for(R int i=x;i<=y;i+=k)
#define Rof(i,x,y) for(R int i=x;i>=y;--i)
#define Rof2(i,x,y,k) for(R int i=x;i>=y;i-=k)
#define ForG(i,edge,x) for(auto i:edge[x])
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n;
char s[100001];
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		scanf("%s",s+1);
		int ans=inf;
		For(i,0,25)
		{
			int l=1,r=n,res=0;
			while(l<=r)
			{
				if(s[l]==s[r])
					++l,--r;
				else if(s[l]=='a'+i)
					++res,++l;
				else if(s[r]=='a'+i)
					++res,--r;
				else
				{
					res=inf;
					break;
				}
			}
			chkmin(ans,res);
		}
		if(ans>n)
			puts("-1");
		else
			putint(ans);
	}
	return 0;
}

```

---

## 作者：Wide_Master (赞：0)

## 题意

$t$ 组数据。

给你一个包含 $n$ 个字符的字符串 $s$，你可以删除其中的一些字符，来使这个字符串回文。输出最少删除的字符个数。

## 分析

众所周知，字符串只有 $26$ 个字符，我们完全可以暴力，然后双指针优化。如果说两个一样就跳过，因为这两个字符是回文的，否则我们就删除左指针指向的字符或者右指针指向的字符。当然，如果这两个指针指向的字符都不能被删去，那么这种方法就不行。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int INF=1e17+7;
int t,n;
string s;
signed main()
{
    cin>>t;
    while(t--){
        cin>>n>>s;
        s=" "+s;
        int ans=INF;
        for(int i='a';i<='z';i++){
            int l=1,r=n,flag=0,count=0;
            while(l<r){
                if(s[l]!=s[r]){
                    if(s[l]==i){
                        l++;
                        count++;
                    }else if(s[r]==i){
                        r--;
                        count++;
                    }else{
                        flag=1;
                        break;
                    }
                }else{
                    l++;
                    r--;
                }
            }
            if(!flag) 
				ans=min(ans,count);
        }
        if(ans==INF)
            cout<<"-1"<<endl;
        else
            cout<<ans<<endl;
    }
    return 0;
}
``````

---

## 作者：_Lazy_whr_ (赞：0)

# 题意
给定一个字符串 $s$，可以选择一个字符并将 $s$ 中若干个这种字符删去，求最少要山区多少个字符使得 $s$ 成为回文串。
# 题解
由于字母只有 $26$ 种，非常小，所以我们可以枚举要删去的字符。然后我们用双指针优化，具体如果两位相同就跳过，否则就可以删去左指针或右指针。如果这两个指针指向的字符都不能被删去，那么这种方法就不行。
# AC Code
```cpp
#include <bits/stdc++.h>
#define int long long
#define endl "\n"
#define x1 x10
#define y1 y10
// #define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, (1 << 20), stdin), p1 == p2) ? EOF : *p1++)
// #pragma GCC target("avx")
// #pragma GCC optimize(3,"Ofast","inline")
namespace FastIO {
	char buf[(1 << 20)], *p1, *p2;
	char pbuf[(1 << 20)], *pp;
	inline int read() {
		int x = 0, f = 1;
		char ch = getchar();
		while (ch < '0' || ch > '9') {
			if (ch == '-')
				f = -1;
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9') {
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}

	template<typename T> inline void read (T &x) {
		x = read();
	}

	template<typename T,typename... Args> inline void read (T &x,Args &...x_) {
		read (x);
		read (x_...);
	}
}

namespace Constants {
	const int INF = 1e17;
	const int DIR[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	const double EPS = 1e-7;
	const double PI = acos (-1);
}

using namespace std;
using namespace FastIO;
using namespace Constants;

void CLOSE() {
	ios::sync_with_stdio (false);
	cin.tie (nullptr);
	cout.tie (nullptr);
}

int n;
string s;

main() {
	CLOSE();
	int t;
	cin >> t;
	while (t--) {
		cin >> n >> s;
		s = " " + s; // 转换下标
		int ans = INF;
		for (char i = 'a'; i <= 'z'; i++) { // 枚举要删去的字符
			int l = 1, r = n;
			int cnt = 0;
			int flag = 0;
			while (l < r) {
				if (s[l] != s[r]) { // 如果不一样
					if (s[l] == i) { // 如果能删左指针
						l++;
						cnt++;
					} else if (s[r] == i) { // 如果能删右指针
						r--;
						cnt++;
					} else { // 不然就不行
						flag = 1;
						break;
					}
				} else {
					l++;
					r--;
				}
			}
			if (flag == 0) {
				ans = min (ans, cnt);
			}
		}
		if (ans == INF) {
			cout << -1 << endl;
		} else {
			cout << ans << endl;
		}
	}
	return 0;
}
```

---

## 作者：Lizj (赞：0)

## 题意分析

题意：给出一个长度为 $n$ 的小写字母字符串，删去其中的一种字母使得它成为一个回文串，求最少的删去个数。

分析：我们可以枚举删去的字符，再用双指针扫一遍这个字符串，计算出删去的字符数，记录下最小值即可；当双指针指向的两个字符不同，也不为删去的字符时，当前方案不合法。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		char s[100010];
		for(int i=1;i<=n;i++){
			cin>>s[i];
		}
		int ans=n+1;
		for(int i=0;i<26;i++){
			char ch=i+'a';
			int l=1,r=n;
			int cnt=0;
			while(l<r){
				if(s[l]==s[r]){
					l++,r--;
				}
				else{
					if(s[l]==ch){
						l++,cnt++;
						continue;
					}
					if(s[r]==ch){
						r--,cnt++;
						continue;
					}
					cnt=n+1;
					break;
				}
			}
			ans=min(ans,cnt);
		}
		cout<<((ans==n+1)?(-1):ans)<<endl;
	}
	return 0;
}
```


---

