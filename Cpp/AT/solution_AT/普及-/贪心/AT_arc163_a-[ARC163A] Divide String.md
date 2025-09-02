# [ARC163A] Divide String

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc163/tasks/arc163_a

長さ $ N $ の英小文字からなる文字列 $ S $ が与えられます。$ S $ を $ 2 $ 個以上の連続部分文字列に分割し、それらが辞書順で狭義単調増加になるようにすることが出来るか判定してください。

厳密に書くと、以下の条件を全て満たす文字列の列 $ t=(t_1,t_2,\dots,t_k) $ が存在するか判定してください。

- 列の長さ $ k $ は $ 2 $ 以上である。
- $ t_i $ は空でない。($ 1\ \le\ i\ \le\ k $)
- $ t_1,t_2,\dots,t_k $ をこの順で連結すると $ S $ と一致する。
- $ 1\ \le\ i\ <\ k $ を満たす整数 $ i $ に対して、$ t_i $ は $ t_{i+1} $ より辞書順で小さい。
 
$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

  辞書順とは？文字列 $ S\ =\ S_1S_2\ldots\ S_{|S|} $ が文字列 $ T\ =\ T_1T_2\ldots\ T_{|T|} $ より**辞書順で小さい**とは、下記の 1. と 2. のどちらかが成り立つことを言います。 ここで、$ |S|,\ |T| $ はそれぞれ $ S,\ T $ の長さを表します。

1. $ |S|\ \lt\ |T| $ かつ $ S_1S_2\ldots\ S_{|S|}\ =\ T_1T_2\ldots\ T_{|S|} $。
2. ある整数 $ 1\ \leq\ i\ \leq\ \min\lbrace\ |S|,\ |T|\ \rbrace $ が存在して、下記の $ 2 $ つがともに成り立つ。 
  - $ S_1S_2\ldots\ S_{i-1}\ =\ T_1T_2\ldots\ T_{i-1} $
  - $ S_i $ が $ T_i $ よりアルファベット順で小さい文字である。

## 说明/提示

### 制約

- $ 1\ \le\ T\ \le\ 2000 $
- $ 2\ \le\ N\ \le\ 2000 $
- $ S $ は長さ $ N $ の英小文字からなる文字列
- $ 1 $ 個の入力に含まれるテストケースについて、それらの $ N $ の総和は $ 2000 $ を超えない。
 
### Sample Explanation 1

$ 1 $ 個目のテストケースは、$ S $ を `a`,`ba`,`c` と分割すればよいです。 $ 2 $ 個目のテストケースは、$ S $ をどのように分割しても辞書順で狭義単調増加にすることは出来ません。

## 样例 #1

### 输入

```
5
4
abac
3
cac
2
ab
12
abababababab
5
edcba```

### 输出

```
Yes
No
Yes
Yes
No```

# 题解

## 作者：zhlzt (赞：4)

### 暴力做法
首先，题目中划分成多个子串，按字典序严格递增排列，要是有满足条件的情况，把第二个以后的子串接到第二个子串后，还是满足条件啊！因为原来第二个子串就比第一个子串大，即前几位就已经足够大了，所以之后不管怎么样，都满足条件，因此只需要划分成两个子串即可。

请问有人认为 $O\left(\sum n^2\right)$ 的暴力做法过不了是为什么？难道题目里没说 $\sum n\le 2000$ 吗？所以 $\sum n^2\le4\times10^6$ 啊！

在这里，为了方便，可以用 `string` 来存储字符串，这样既可以用 `<` 和 `>`来方便地判断字典序大小，又可以用 `s.substr(l,d)` 这样的函数来方便地截取出 $s$ 的左端点为 $l$，长度为 $d$ 的子串。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n;scanf("%d",&n);
		string s; cin>>s; int flag=0;
		for(int i=1;i<n;i++){
			if(s.substr(0,i)<s.substr(i,n-i)){
				flag=1; break; // 已经找到一组解了
			}
		}
		if(flag==1) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```

---

## 作者：Butterfly_qwq (赞：2)

[题目传送门](https://atcoder.jp/contests/arc163/tasks/arc163_a)

[符号表](https://www.luogu.com.cn/paste/1hcda151)

题目大意：

给你一个字符串，请问这个字符串能不能被分割成若干个连续子串，使得所有子串以开头在原字符串的位置从小到大排序后所有子串以字典序顺序排列。有多组数据。

我们可以下结论：一个字符串只要能分割，那么他一定能分割成 2 个字符串。

证明：

设字符串 $s$ 可以按上述规则分为 $s_1s_2s_3s_4\dots s_{n-1}s_n$。

则 $s_1<s_2$ 而又有 $s_2<s_2s_3s_4s_5\dots s_{n-1}s_n$。

所以 $s_1<s_2s_3s_4s_5\dots s_{n-1}s_n$。

所以可以将 $s$ 从 $s_1$ 和 $s_2$ 之间分开，肯定不会出现问题。

证明完这个就好做了。

Code:

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,t;
	string s;
	cin>>t;
	qwq:while(t--)
	{
		cin>>n;
		cin>>s;
		for(int i=1;i<n;i++)
		{
			string ss1=s.substr(0,i),ss2=s.substr(i,n-i);
			if(ss1<ss2)
			{
				cout<<"Yes\n";
				goto qwq;
			}
		}
		cout<<"No\n";
	}
}
```

---

## 作者：DengDuck (赞：1)

提供一个 $\mathcal O(Tn\log n)$ 的做法。

枚举分界点，然后求一个最长公共前缀，相同的部分略过，比较下一位即可。

找最长公共前缀的方法很多。

- 二分+哈希，时间复杂度为 $\mathcal O(Tn\log n)$。
- 倍增后缀数组，时间复杂度为 $\mathcal O(Tn\log n)$。
- $\mathcal O(n)$ 后缀数组，时间复杂度为 $\mathcal O(Tn)$。

我写的是第一种。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=2005;
const LL M=4;
const LL P=1331;
const LL mod[M]={998244353,1000000009,20090327,1000000007};
char s[N];
LL T,n,pw[M][N],hsh[M][N];
LL gthsh(LL x,LL l,LL r)
{
	return (hsh[x][r]-hsh[x][l-1]*pw[x][r-l+1]%mod[x]+mod[x])%mod[x];
}
LL sam(LL l,LL r,LL L,LL R)
{
	for(int i=0;i<M;i++)
	{
		if(gthsh(i,l,r)!=gthsh(i,L,R))return 0;
	}
	return 1;
}
LL LCP(LL x)
{
	LL l=1,r=min(x,n-x),ans=0;
	while(l<=r)
	{
		LL mid=l+r>>1;
		if(sam(1,mid,x+1,x+mid))
		{
			l=mid+1,ans=mid;
			//cout<<"Win"<<ans<<endl;
		}
		else r=mid-1;
	}
	return ans;
}
LL pd(LL x)
{
	if(x*2==n)
	{
		if(sam(1,x,x+1,n))return false;
	}
	LL t=LCP(x);
	if(t==x)return 1;
	if(t==n-x)return 0;
	
	if(s[t+1]>s[x+t+1])return 0;
	return 1;
}
void work()
{
	for(int i=1;i<n;i++)
	{
		if(pd(i))
		{
			puts("Yes");
			return;
		}
	}
	puts("No");	
}
int main()
{
	for(int i=0;i<M;i++)
	{
		pw[i][0]=1;
		for(int j=1;j<N;j++)pw[i][j]=pw[i][j-1]*P%mod[i];
	}
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%s",&n,s+1);
		for(int i=1;i<=n;i++)
		{
			for(int j=0;j<M;j++)hsh[j][i]=(hsh[j][i-1]*P+s[i]-'a')%mod[j];
		}
		work();
	}
}
```

---

## 作者：code_hyx (赞：0)

感觉这题很像 CFdiv2A 的风格，难度也就和 CFdiv2A 差不多。  
显然，对于任意一个字符串，将其分为多个字串后，第一个子串的字典序一定小于原串，因为首字母是一样的，但长度变短了。  
结合这道题，对于一个子串，将其继续划分后，第一个子串的字典序只会更小，所以一定不会出现这一次划分后使得子串字典序非递增变成递增。也就是说，划分得越少越好，那么只分成两部分就行了。  
然后就是暴力枚举划分位置了。   
代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
string s;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		bool flag=false;
		int len;
		cin>>len;
		cin>>s;
		for(int i=1;i<len;i++)
		{
			string s1=s.substr(0,i),s2=s.substr(i,len-i);
			//cout<<s1<<" "<<s2<<"\n";
			if(s1<s2)
			{
				flag=true;
				break;
			}
		}
		if(flag==true)cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
} 
```


---

## 作者：yuheng_wang080904 (赞：0)

## 思路

作为签到题，大家不需要考虑太多，没啥要分讨的。

首先我们容易得到一个结论：如果一个字符串能分割成多个字符串满足题中要求，那么这个字符串必定能分成两个字符串满足要求。

那么就没什么好说的了，直接暴力枚举断点分成两个串比大小，总时间复杂度 $O(Tn)$，足以通过。

## 代码

代码主要部分：

```cpp
void solve(){
    ll n=read();
    string s;
    cin>>s;
    for(int i=1;i<=n;i++){
	string s1=s.substr(0,i),s2=s.substr(i,n-i);
	if(s1<s2){
	    cout<<"Yes\n";
	    return;
	}
    }
    cout<<"No\n";
    return;
}
```


---

## 作者：Loser_Syx (赞：0)

## 思路

贪心。

首先我们要划分为一些部分，其数量要求 $\geq 2$，此处我们考虑贪心，即只将其划分为两端。  
然后我们知道，$s_0$ 肯定是开头，所以只需要 $O(n)$ 枚举第二个开头在哪，比较大小便可。

```cpp
#include <iostream>
using namespace std;
string substr(string s, int l, int r){
	string rtn = "";
	for(int i = l; i <= r; ++i) rtn += s[i];
	return rtn;
}
int main(){
	int n;
	scanf("%d", &n);
	while(n--){
		int len;
		string s;
		cin >> len >> s;
		bool flag = 0;
		for(int i = 1; i < len; ++i){
			if(s[i] > s[0]){
				flag = 1;
				break;
			}else if(s[i] == s[0]){
				string qwq = substr(s, 0, i-1);
				string pwp = substr(s, i, len-1);if(pwp > qwq){flag = 1;break;}
			}
		}
		puts(flag ? "Yes" : "No");
	}
	return 0;
}
```

---

## 作者：引领天下 (赞：0)

题意：

给定一个长为 $N$ 的字符串 $S$，判断是否能将其划分为若干子串使得这些子串严格按照**字典序**递增。

做法：

首先，本题不用考虑拆成 $3$ 个及以上个子串的情况。因为对于一个固定开头的字符串来说，显然它的长度越长是越有利于它的字典序增大的。那么我们最后只需要找到一个断点 $i$ 将 $S$ 断成两个子串。

具体处理过程中，存在两种情况：

- 如果存在某个 $i$ 使得 $S_i>S_1$，那直接不用做了，将 $S$ 拆成从 $1$ 开始的和从 $i$ 开始的两个串就是满足题意的。

- 否则考虑截取 $S_0\dots S_{i-1}$ 和 $S_i\dots S_N$ 两个字符串，直接比较字典序即可。

做法上，为了图省事，我直接使用了 string 类~~这样就不用手写字典序比大小了~~。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t,n;
string s;
signed main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        cin>>n>> s;
        bool ok=0;
        for (int i=1;i<n;i++)ok|=s[i]>s[0]|((s[i]==s[0])&&(s.substr(0,i)<s.substr(i)));
        cout<<(ok?"Yes\n":"No\n");
    }
    return 0;
}
```

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_arc163_a)    
很水，但是情况挺多。        
## 题意
给你一个字符串，判断能否将其分成两个或以上的字符串且它们字典序上为严格升序。        
## 解法
我们易知，只要能分成两个以上的，都能被分成两个，只要分不成两个以上的，都不能被分成两个，反过来也一样。所以我们只需要考虑分成两个的情况。           
首先，我们容易发现可以暴力判断，但是这么样会超时。     
我们需要先判断一些特殊情况：     
- 如果整个字符串的字符都一样，那么判断条件是 $n≥3$。    
- 如果字符串里有一个比第一个字符大的字符，那么一定可以分割。      

那么如果还不行，说明字符串字符都小于等于第一个字符，我们对于所有的 $i(s_i=s_1\land i≠1)$ 进行暴力分割判断即可。         
时间复杂度 $O(tn)$，可以通过。     
[CODE](https://www.luogu.com.cn/paste/lyvg5b9p)

---

