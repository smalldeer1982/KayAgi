# Not Quite a Palindromic String

## 题目描述

Vlad 发现了一个长度为偶数 $ n $ 的二进制字符串 $ ^{\text{∗}} $ $ s $。他认为一对索引 ( $ i, n - i + 1 $ )（其中 $ 1 \le i < n - i + 1 $）是好的，如果满足 $ s_i = s_{n - i + 1} $。

例如，在字符串 '010001' 中只有 $ 1 $ 对好的索引，因为 $ s_1 \ne s_6 $，$ s_2 \ne s_5 $，而 $ s_3 = s_4 $。在字符串 '0101' 中没有好的索引对。

Vlad 喜欢回文串，但又不那么喜欢，所以他希望通过重新排列字符串中的某些字符，使得恰好有 $ k $ 对好的索引。

判断是否可以通过重新排列给定字符串中的字符，使得恰好有 $ k $ 对好的索引 ( $ i, n - i + 1 $ )。

$ ^{\text{∗}} $ 二进制字符串是指仅由字符 '0' 和 '1' 组成的字符串。

## 样例 #1

### 输入

```
6
6 2
000000
2 1
01
4 1
1011
10 2
1101011001
10 1
1101011001
2 1
11```

### 输出

```
NO
NO
YES
NO
YES
YES```

# 题解

## 作者：TheTrash (赞：2)

### 题意

给你一个长度为 $n$ 的字符串 $s$，问你能不能通过重新排列字符串中的某些字符使得正好有 $k$ 个 $s_i=s_{n-i+1}$。

### 思路

先统计字符串内 ```0``` 和 ```1``` 的个数，分别保存在 $x$ 和 $y$ 里，然后让 $x$ 和 $y$ 都减去 $\frac{n}{2}-k$。如果 $x<0$ 或 $y<0$ 说明所有排列中符合 $s_i=s_{n-i+1}$ 的 $i$ 的数量最少也会大于 $k$，直接输出 ```NO``` 即可。接着还要判断能匹配到的索引对的数量是不是正好等于 $k$。如果是，输出 ```YES```，否则输出 ```NO```。

### 代码

```cpp
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<map>
#include<queue>
using namespace std;
int T,n,k,x,y;
string s;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>k>>s;
		for(int i=0;i<n;i++) s[i]=='0'?x++:y++;
		x-=(n/2-k),y-=(n/2-k);//先减再判断
		if(x<0||y<0) cout<<"NO\n";
		else if(x/2+y/2!=k) cout<<"NO\n";
		else cout<<"YES\n";
		x=0,y=0;//多测不清空，爆零两行泪
	}
}
```

---

## 作者：abort (赞：1)

## 题目大意
给出一个字符串 $s$，随意排列，使其恰好有 $k$ 对 $s_i = s_{n - i + 1}$。

## 解析
我们已知要满足 $n / 2 - k$ 对字符不等，则再不等的范围内需要满足 $0$ 和 $1$ 的个数相等，相等范围内，需要满足 $0$ 和 $1$ 的个数都能被 $2$ 整除。

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

int t;
void solve()
{
    cin >> t;
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        int cnt0 = 0, cnt1 = 0;
        string s;
        cin >> s;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '0') cnt0++;
            else cnt1++;
        } 
        int num = n / 2 - k;
        cnt0 -= num;
        cnt1 -= num;
        if (cnt0 < 0 || cnt1 < 0)
        {
            cout << "NO" << endl;
            continue;
        }
        if (cnt0 % 2 == 1 || cnt1 % 2 == 1)
        {
            cout << "NO" << endl;
            continue;
        }
        cout << "YES" << endl;
    }
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}
```

---

## 作者：wzy090702 (赞：1)

# CF2114B 题解
[洛谷传送门](https://www.luogu.com.cn/problem/CF2114B)

[vjudge 翻译传送门](https://vjudge.net/problem/CodeForces-2114B#author=DeepSeek_zh)

---

### 分析
通过观察我们不难发现：对于一个确定的二进制字符串 $ s $，每次调换两个数的位置，其 $ k $ 值的变化量永远为 $ 2 $ 的倍数。

我们不妨先令 $ s $ 中含有 $ x $ 个 $ 1 $ 和 $ y $ 个 $ 0 $。同时，这里事先默认 $ y \le x $。

让我们思考一下：如果我们想要构造出 $ k $ 的最小值，我们就需要让更多的 $ 0 $ 去和 $ 1 $“匹配”。因此，$ k $ 的最小值就为

 $$ ( x - y ) \div 2$$ 
 
显而易见，$ k $ 的最大值应该是

 $$ n \div 2 $$ 

不过，这个最大值可能取不到。

而根据前面的结论，我们只需要判定题目中所给的 $ k $ 是否满足和 $ s $ 中一个已知的 $ k $ 类似（即两个数都为偶数或奇数）即可。

### AC 代码

```cpp
#include<bits/stdc++.h>
#define For(i,a,n,x) for(auto i=a;i<=n;i+=x)
#define Ror(i,n,a,x) for(auto i=n;i>=a;i-=x)
#define lowbit(x) x&-x
#define ll long long
#define ull unsigned long long
using namespace std;//神奇の缺省源 
int t,l,k;
string s; 
int main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		cin>>l>>k>>s;
		int u0=0,u1=0;
		For(i,0,l-1,1){
			if(s[i]=='0')u0++;//计算字符串中含有0的数量 
			else u1++;//算字符串中含有1的数量 
		}
		int maxn=max(u0,u1),minn=min(u0,u1);
		if((maxn-minn)/2<=k && l/2>=k){//如果k在其最小值和“最大值”之间 
			if(((maxn-minn)/2)%2==k%2)cout<<"yes"<<endl;//如果两个数“类似”就输出yes	
			else cout<<"no"<<endl;
		}
		else cout<<"no"<<endl;//反之输出no		
	}
	return 0;
}
//tip：题目中已说明对大小写不敏感 
```
![](https://cdn.luogu.com.cn/upload/image_hosting/i6e727l1.png)

---

## 作者：_weishiqi66_ (赞：1)

# 题意
给定一个 $01$ 字符串，考虑是否能通过重排，使其有且仅有 $k$ 对字符是对称的。

# 做法
先统计 $0$ 和 $1$ 出现的次数，先考虑是否能凑出 $k$ 对对称。再考虑剩下的字符能否相异配对。为了使得剩下的字符能尽可能相异配对，我们要尽可能使剩下的 $0$ 和 $1$ 字符出现的次数相近。

# 代码
```
#include <bits/stdc++.h>
using namespace std;

const int N=1e6;
int t,n,k;
char c[N];
bool check(int x,int y) {
	if(y<x) swap(x,y);
	if(x/2+y/2>=k) {
		y=y-2*k; 
		if(y>x) return y<=(x+1);
		int c=(x-y)/2/2*2;
		x=x-c; y=y+c;
		if(y<x) swap(x,y);
		if((x+y)%2==0){
			if(y-x<2) return 1;
		}
		else {
			if(y-x<=2) return 1;
		}
	}

	return 0;
}
int main() {
	//freopen("in.txt","r",stdin);
	cin>>t;
	while(t--) {
		cin>>n>>k;
		int x=0,y=0;
		for(int i=1;i<=n;i++) {
			cin>>c[i];
			if(c[i]=='1') x++;
			else y++;
		}
		if(check(x,y))cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```

---

## 作者：caizihan925 (赞：0)

# 题面大意

给定一个长度为 $n$ 的字符串 $s$，问能否通过重排使字符串中恰好有 $k$ 个位置 $i$ 满足 $s_i = s_{n - i + 1}$。 

# 思路

可以发现，题目说的是恰好 $k$ 个位置，那可以先判掉满足条件的位置 $i$ 的数量小于 $k$ 的情况。然后再判掉满足条件的位置 $i$ 的数量不为 $k$ 的情况。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1e5 + 10;

int n, k, ans;

string s;

void Solve(){
    cin >> n >> k >> s;
    int cnt0 = 0, cnt1 = 0;
    for(int i = 0; i < n; (s[i] == '0' ? cnt0++ : cnt1++), i++);
    cnt0 -= (n / 2 - k), cnt1 -= (n / 2 - k);
    if(cnt0 < 0 || cnt1 < 0){
        cout << "No\n";
        return ;
    }
    cout << (cnt0 / 2 + cnt1 / 2 == k ? "Yes\n" : "No\n");
}

signed main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int T;
    cin >> T;
    while(T--){
        Solve();
    }
    return 0;
}
```

---

## 作者：Gaochenxi103_QWQ (赞：0)

本题注意点为恰好，就是不多不少刚刚好。（废话）那么就考虑是否可以配出 $\frac{n}{2}-k$ 个 $0$ 和 $1$ 的对。

统计 $0$ 和 $1$ 的数量，在将每个减去 $\frac{n}{2}-k$ 个。判断剩余数量是否合法即可。

核心代码。
```cpp
cin>>n>>k;
int x=0,y=0;
for(int i=1;i<=n;i++)
{
    char cnt;
    cin>>cnt;
    if(cnt=='1')x++;
    else y++;
}
int c=n/2-k;
x-=c;
y-=c;
if(x<0 || y<0)
{
    cout<<"NO\n";
    continue;
}
int a=x/2,b=y/2;
if(a+b==k)cout<<"YES\n";
else cout<<"NO\n";
```

---

## 作者：_Star_Universe_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF2114B)
### 思路
对于每个 $01$ 串，我们不妨统计出 `0` 的数量记为 $x$，`1` 的数量记为 $y$，既然题目问我们能否恰好凑出 $k$ 对“好的索引”，我们就要先判断给定的 $k$ 是否在其取值范围内。

如果 $k$ 要取到最小值，我们会尽量多地将 $0$ 和 $1$ 配对，这样得到
$$k_{min} = |(x-y)\div 2|$$

显而易见，$k$ 的最大值就是左右两两配对，无一例外，即
$$k_{max} = n \div 2$$

若 $k$ 在其取值范围内，我们就需要使得匹配出 $k$ 对对称的字符后剩余字符相异配对，那么只需判断 $x \bmod 2 = 0$ 是否成立，因为 $n$ 是偶数，所以 $0$ 出现奇数次 $1$ 也会出现奇数次，差至少为 $2$，显然是不满足的，如果你想判断差是否小于 $2$ 也行。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,k;
string s;
signed main(){
    cin>>t;
    while(t--){
        cin>>n>>k;
        cin>>s;
        int count1=0,count2=0;
        for(int i=0;i<s.size();i++){
            if(s[i]=='0') count1++;
            else count2++;
        }
        int di=n/2-k;
        if((count1-=di)<0||(count2-=di)<0) cout<<"NO"<<endl;
        else if(count1%2!=0) cout<<"NO"<<endl;
        else cout<<"YES"<<endl;
    }
    return 0;
}
```

---

## 作者：wurang (赞：0)

这里提供一种有点抽象但简洁的思路。

由于有 $k$ 对索引，所以有 $\frac{n}{2} - k$ 对 $0$ 和 $1$。

接着如果剩下 $0$ 或 $1$ 小于 $0$，那么直接输出 no。

此时再做一个判断，如果 $0$ 的数量是奇数，那么输出 no。

此处有一个细节，由于此处剩下 $2 \times k$ 个数，如果 $0$ 的数量是偶数，那么 $1$ 的数量也为偶数，所以不用判。

如果以上两种都不成立，那么输出 yes。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int t;
int n, k;
string s;

signed main()
{
    cin >> t;
    while(t--)
    {
        cin >> n >> k;
        cin >> s;
        int c0 = 0, c1 = 0;
        for(int i = 0; i < s.size() ; i++)
            if(s[i] == '0') c0++;
            else c1++;
        c0 -= (n / 2 - k), c1 -= (n / 2 - k);
        if(c0 < 0 || c1 < 0) cout << "NO\n";
        else if(c0 % 2 != 0) cout << "NO\n";
        else cout << "YES\n";
    }
    return 0;
}
```

---

