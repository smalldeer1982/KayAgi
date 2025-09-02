# Replacement

## 题目描述

You have a binary string $ ^{\text{∗}} $ $ s $ of length $ n $ , and Iris gives you another binary string $ r $ of length $ n-1 $ .

Iris is going to play a game with you. During the game, you will perform $ n-1 $ operations on $ s $ . In the $ i $ -th operation ( $ 1 \le i \le n-1 $ ):

- First, you choose an index $ k $ such that $ 1\le k\le |s| - 1 $ and $ s_{k} \neq s_{k+1} $ . If it is impossible to choose such an index, you lose;
- Then, you replace $ s_ks_{k+1} $ with $ r_i $ . Note that this decreases the length of $ s $ by $ 1 $ .

If all the $ n-1 $ operations are performed successfully, you win.

Determine whether it is possible for you to win this game.

 $ ^{\text{∗}} $ A binary string is a string where each character is either $ \mathtt{0} $ or $ \mathtt{1} $ .

## 说明/提示

In the first test case, you cannot perform the first operation. Thus, you lose the game.

In the second test case, you can choose $ k=1 $ in the only operation, and after that, $ s $ becomes equal to $ \mathtt{1} $ . Thus, you win the game.

In the third test case, you can perform the following operations: $ \mathtt{1}\underline{\mathtt{10}}\mathtt{1}\xrightarrow{r_1=\mathtt{0}} \mathtt{1}\underline{\mathtt{01}} \xrightarrow{r_2=\mathtt{0}} \underline{\mathtt{10}} \xrightarrow{r_3=\mathtt{1}} \mathtt{1} $ .

## 样例 #1

### 输入

```
6
2
11
0
2
01
1
4
1101
001
6
111110
10000
6
010010
11010
8
10010010
0010010```

### 输出

```
NO
YES
YES
NO
YES
NO```

# 题解

## 作者：dmc0702 (赞：1)

# 分析
既然要进行 $n-1$ 轮，那么 $r$ 里面的数字肯定是会用完的。所以我们可以从 $r$ 的角度来想，在 $r$ 里，每用一个数字 $\mathtt{0}$ ，相对应 $s$ 里也会少一个 $\mathtt{0}$ 。 那么只需要统计 $s$ 里 $\mathtt{0}$ 与 $\mathtt{1}$ 的个数，在再 $r$ 里减即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false),cin.tie(0); 
	int t,n,sum1,sum2;
	string s,r;
	cin>>t;
	while(t--){
		cin>>n>>s>>r;
		sum1=sum2=0;
		for(int i=0;i<n;i++)s[i]=='0'?sum1++:sum2++;
		bool f=false;
		for(int i=0;i<n-1;i++){
			if(sum2<=0||sum1<=0){cout<<"No\n",f=true;break;}
			r[i]=='0'?sum2--:sum1--;
		}
		if(f)continue;
		cout<<"YES\n";
	}
	return 0;
}
```

---

## 作者：_Tatsu_ (赞：0)

## 问题分析
给定一个二进制字符串 $s$，在每一步中，我们需要找到一个相邻字符不同的位置 $j$，然后将其替换为另一个字符串 $r$ 中的字符，并继续进行直到字符串只剩下一个字符。我们需要判断是否可以完成所有的操作。

目标: 判断能否按照规则成功完成所有的操作。如果无法进行操作，即 $s_k=s_{k+1}$ 对于所有的 $k$，则游戏失败。

## 解题思路
对于每一步，我们需要尽可能选择一个相邻的不同字符对，并且确保替换后的结果能继续进行下去。

对于每一对相邻的不同字符，查看是否可以将其替换为 $r_i$。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
    int t;
    cin>>t;
    while (t--)
	{
	    int n;
		cin>>n;
		string s,r;
	    cin>>s;
        cin>>r;
        bool f=1;//表示是否可以完成操作
	    // 进行 n-1 次操作
	    for (int i=0;i<n-1;i++)
		{
	        bool ff=0;//是否找到可替换的字符对
	        for (int j=0;j<s.size()-1;j++)
			{
	            if (s[j]!=s[j+1])
				{
					//找到相邻不同的字符
	                s[j]=r[i];//将s[j]换为 r[i]
	                s.erase(j+1,1); //删除s[j+1]长度减1
	                ff=1;
	                break;//一旦找到替换对，退出当前循环
	            }
	        }
	        if (!ff)
			{
	            f=0;
	            break;
	        }
	    }
	    if (f)
	        cout<<"YES"<<endl;
	    else
	    	cout<<"NO"<<endl;
	}
    return 0;
}
```

---

## 作者：NEKO_Daze (赞：0)

[洛谷CF2029B](https://www.luogu.com.cn/problem/CF2029B) || [CodeForces 2029 B](https://codeforces.com/contest/2029/problem/B)

### 题意翻译

给出一个长度为 $n$ 的二进制字符串 $s$ 和另一个长度为 $n-1$ 的二进制字符串 $r$。对 $s$ 执行 $n-1$ 操作（$1 \le i \le n-1$），每次选择一个索引 $k$ 满足 $1\le k\le |s| - 1$ 和 $s_ {k} \neq s_ {k+1}$，否则输出 `NO` 并结束，然后将 $s_ ks_ {k+1}$ 替换为 $r_ i$。

当所有 $n-1$ 次操作完成后输出 `YES`。

### 思路

如果当前 $s$ 只包含 $0$ 或只包含 $1$，显然无法进行合法的操作。输出 `NO`。

在第 $i$ 次操作中，如果 $r_i=0$，我们实际上减少了 $1$ 个 $1$，反之亦然。因此，我们只需要不断更新 $s$ 中 $0$ 和 $1$ 的数量，它们中的任何一个下降到 $0$，那么输出 `NO`，否则必然可以完成所有操作并输出 `YES`。

时间复杂度：$\mathcal{O}(T\times n)$。

```cpp
#include <bits/stdc++.h>
#define all(s) s.begin(), s.end()

using namespace std;
using ll = long long;

const int _N = 1e5 + 5;

void solve() {
	int n; cin >> n;
	string s, t; cin >> s >> t;
	int cnt0 = count(all(s), '0'), cnt1 = n - cnt0;
	for (int i = 0; i < n - 1; i++) {
		if (cnt0 == 0 || cnt1 == 0) {
			cout << "NO" << '\n';
			return;
		}
		if (t[i] == '1') cnt0--;
		else cnt1--;
	}
	cout << "YES" << '\n';
}

int main() {
	int T; cin >> T;
	while (T--) {
		solve();
	}
}
```

---

## 作者：LINYUHENG2 (赞：0)

# 题意
给定一个长度为 $n$ 的 $01$ 串 $s$ 和一个长度为 $n-1$ 的 $01$ 串 $r$。

要对 $s$ 执行 $n-1$ 次操作。其中，一次操作的定义为：
- 选择一个索引 $k$ 满足 $s_k \ne s_{k+1}$。若没有这样的索引，则操作失败。
- 将 $\overline{s_ks_{k+1}}$ 替换为 $r_i$。

判断能否成功进行 $n-1$ 次操作。
# 分析
可以操作的条件是要字符串中同时存在 $0$ 和 $1$。
# 方法
统计字符串中 $0$ 和 $1$ 的个数，每次操作都会删除一个 $0$ 和一个 $1$ ，加上一个 $r_i$。开两个变量动态维护。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=200007;
long long t,n;
char s[N],t[N];
int main(){
	cin>>t;
	while(t--){
		cin>>n>>(s+1)>>(t+1);
		long long sum0=0,sum1=0,flag=1;
		for (int i=1;i<=n;++i){
            if (s[i]=='1') sum1++;
            else sum0++;
        }
		for (int i=1;i<n;++i){
			if (sum0==0||sum1==0){
                flag=0;
                break;
            }
			if (t[i]=='1') --sum0;
            else --sum1;
		}
		if(flag) cout<<"Yes";
        else cout<<"No";
	}
	return 0;
}

---

## 作者：long_long__int (赞：0)

# 题意
[题目翻译。](https://www.luogu.com.cn/paste/b9ft8kug)

# 题目解法
我们可以发现 $n\le 10^5$，所以平方级的复杂度是显然会超时的，所以要找复杂度更低的算法。因为每次操作必须删除一个 `0` 和一个 `1`，然后加上一个 $r_i$，所以就用两个变量统计一下 $s$ 中 `0` 和 `1` 的数量，在用 $r$ 里的减就行了。

代码（部分）：
```cpp
void work(){
    int n,n0=0,n1=0;
    string s,r;
    cin>>n>>s>>r;
    s=' '+s,r=' '+r;
    for(int i=1;i<=n;i++){
    	if(s[i]=='0'){
			n0++;
		}
    	else{
			n1++;
		}
    }
    for(int i=1;i<n;i++){
		if(n0<=0 or n1<=0){
			printf("No\n");
			return;
		}
		if(r[i]=='0'){
			n1--;
		}else{
			n0--;
		}
	}
	printf("Yes\n");
}
```

---

## 作者：_lmh_ (赞：0)

引理：可以操作的充要条件是字符串中同时存在 $0$ 和 $1$。

证明：显然。

然后正解就呼之欲出了：统计 $0$ 和 $1$ 的个数，每次操作必定删除一个 $0$ 和一个 $1$，加上一个 $r_i$，可以开两个变量动态维护。

时间复杂度：$O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=200007;
ll T,n;
char s[N],t[N];
int main(){
	cin>>T;
	while(T--){
		cin>>n>>(s+1)>>(t+1);
		ll sum0=0,sum1=0,fl=1;
		for (int i=1;i<=n;++i) if (s[i]=='1') sum1++;else sum0++;
		for (int i=1;i<n;++i){
			if (sum0==0||sum1==0){fl=0;break;}
			if (t[i]=='1') --sum0;else --sum1;
		}
		cout<<(fl?"Yes\n":"No\n");
	}
	return 0;
}
```

---

## 作者：tai_chi (赞：0)

可以在 [cnblog](https://www.cnblogs.com/tai-chi/p/18538159) 中阅读。

#### 题意

给一个长度为 $n$ 的 $\texttt{01}$ 串 $s$，一个长度为 $n-1$ 的 $\texttt{01}$ 串 $r$。

希望对 $s$ 执行 $n-1$ 次操作。一次操作定义为：

- 选择一个索引 $k$ 满足 $s_k \neq s_{k+1}$。若无法选择这样的索引，则操作失败；
- 将 $\overline{s_k s_{k+1}}$ 替换为 $r_i$。

判断是否可能成功进行 $n-1$ 次操作。

#### 分析

注意到，一个状态存在可操作的位置 $k$ 当且仅当序列不全为 $\texttt{0}$ 或全为 $\texttt{1}$，而一次 $r_i=\texttt{0}$ 的操作等价于去除了序列中一个 $\texttt{1}$ 位置，反之亦然。

那可以维护当前 $s$ 中 $\texttt{0}$ 和 $\texttt{1}$ 的数量，模拟操作即可。若一次操作前 $\texttt{0}$ 的数量为 $0$ 或 $\texttt{1}$ 的数量为 $0$ 即可判定无解。

```cpp
void solve()
{
	int n; cin>>n;
	string s1,s2; cin>>s1>>s2;
	int cnt1=0,cnt0=0;
	for(int i=0;i<n;i++)
	{
		if(s1[i]=='0') cnt0++;
		else cnt1++;
	}
	bool flag=1;
	for(int i=0;i<n-1;i++)
	{
		if(cnt1<=0||cnt0<=0) {flag=0; break;}
		if(s2[i]=='0') cnt1--;
		else cnt0--;
	}
	if(flag) cout<<"YES"<<"\n";
	else cout<<"NO"<<"\n";
}
```

---

