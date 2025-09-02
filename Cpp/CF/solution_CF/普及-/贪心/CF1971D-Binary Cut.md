# Binary Cut

## 题目描述

给定一个二进制字符串 $ ^{\dagger} $ 。请找到您需要将其切割成的最小片段数，将生成的片段重新排列成有序的二进制字符串。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1971D/198c30d478b8cd51c898ff4b7c617ab4c8bcae49.png)

请注意：

- 每个字符必须恰好位于其中一个片段中；
- 这些片段必须是原始字符串的连续子字符串；
- 你必须在重排中使用所有的片段。

$^{\dagger}$二进制字符串是由字符 $ \texttt{0}$ 和 $\texttt{1}$ 组成的字符串。排序后的二进制字符串是一个二进制字符串，使得所有字符 $\texttt{0}$ 位于所有字符 $\texttt{1}$ 之前。

## 样例 #1

### 输入

```
6
11010
00000000
1
10
0001111
0110```

### 输出

```
3
1
1
2
1
2```

# 题解

## 作者：Malkin_Moonlight (赞：3)

## 题解：CF1971D Binary Cut

### 思路

本题为**多测**一定要记得清空。

题目要求你把 `01` 串分成尽量少的小段，并重新排列这些小段，使所有的 `0` 都在 `1` 前面，输出最小的段数。

- 当我们遇到一段全是 `0` 或全是 `1` 的字符串，就不需要分开；

- 当我们遇到 `01` 这个子串时，我们只能保留一个 `01` 子串；

- 当我们遇到 `10` 就一定得分段。

最后要记住加 1，因为本来就有一段。

### 代码
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
#define pb emplace_back
const int MAXN=1e5+5;
const int Mod=1e9+7;
ll T,i,j;
string s;
int main()
{
	//freopen("xxx.in","r",stdin);
	//freopen("xxx.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>s;
		ll ans=0,flag=0;
		ll len=s.size();
		for(i=0;i<len-1;i++)
		{
			if(s[i]=='1' && s[i+1]=='0')
			{
				ans++;
			}
			else if(s[i]=='0' && s[i+1]=='1')
			{
				if(flag==0) flag=1;
				else ans++;
			}
		}
		cout<<ans+1<<endl;
	}
	return 0;
}

```

---

## 作者：zhangqiuyanAFOon2024 (赞：2)

### 简化题面
给定 $01$ 串，把它切成若干份，使得拼起来的字符串所有 $0$ 在所有 $1$ 的前面，求切之后的最小份数。

### 思路
显然，贪心， $0$ 和 $1$ 交界的时候要切。

~~做完了。~~

例如：$110111100$，要切三处：$11|0|1111|00$ 然后重新组合变成 $0|00|11|1111$。(这还没完)。

还有一点：如果 $0$ 在 $1$ 的前面，可以少切一次。

例如：$001001111$，先按原来切 $00|1|00|1111$，发现我们可以这样（少切第一次）：$001|00|1111$，然后还是可以得到 $000011111$。

(所以第一个样例只用切两次)。

### 代码？

~~过于简单，不放了。~~

---

## 作者：tanzicheng (赞：2)

## [CF1971D] Binary Cut 题解
### 题目翻译
现在有一个仅包含 $0$ 和 $1$ 的字符串 $S$，你可以将这个字符串切成多个子串，然后对其进行任意排序，使得 $S$ 变为一个单调不下降的字符串。

求最小**分片**数。

### 解题思路
因为要求切片，所以如果有多个 $0$ 或 $1$ 在一起，那么只需要将其看作一个 $0$ 或 $1$ 即可。然后我们看 $|S|$，如果 $|S|$ 等于 $1$，那么就是字符串仅由相同字符组成，只需分 $1$ 片即可；否则我们判断一下是否存在 $0$ 后出现 $1$，如果有，就需要分 $|S|-1$ 片（因为 $0$ 后出现 $1$ 的话可以把两个段看成一个），如果没有，就需要分 $|S|$ 片。
### 具体实现
依据结论计算即可。

[AC](https://www.luogu.com.cn/record/159015779) code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6 + 10;
int t;
void solve() {
    string s,r="";
    cin >> s;
    int ans = 0;
    char t = s[0];
    r += s[0];
    for (int i = 1; i < s.size(); i++) {
        if (s[i] != t)t = s[i], r += s[i];
    } //如果有多个0或1在一起，那么只需要将其看作一个0或 1
    //cout << r << endl;
    bool flag = false;
    int a=0, b=0;
    if (r[0] == '0')a++;
    else b++;
    for (int i = 1; i < r.size(); i++) {
        if (r[i] == '0')a++;
        else b++;
        if (r[i] == '1' && r[i - 1] == '0') flag = true;
    } //a+b等于更改后s的长度，可以用r.length()
    if (flag) cout << a + (b - 1); //0后出现1
    else cout << a + b;
    cout << endl;

}
signed main()
{
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
```

---

## 作者：Dream_Mr_li (赞：1)

## 题目描述

给你一个 `01` 串 $s$，你可以把它分成几段进行排序，问至少分几段，排序后前面都是 `0`，后面都是 `1`？

## 思路

我们来分析一下，排序后前面都是 `0`，后面都是 `1` 就证明所有 `1` 必须在 `0` 后面，否则不合法。

可以想到：

- 要是遇到一段全是 `0` 或全是 `1` 的字符串，就不需要分段，

- 第一次要是遇到 `01` 就无需分段，但是遇到了一个以上，就证明前面已有一个 `1` 了，不能再把有 `0` 的一段掺进去，就要分开。

- 要是遇到 `10` 就一定得分段。

## 代码

```c++
#include<bits/stdc++.h>
using namespace std;
string s;
int t;
int main(){
	cin>>t;
	while(t--){
		cin>>s;
		int ans=1,dy=0;//多测不清空，爆 0 泪两行 
		for(int i=0;i<s.size()-1;i++){
			if(s[i]=='1'&&s[i+1]=='0'){
				ans++;
			}else if(s[i]=='0'&&s[i+1]=='1'){
				if(dy==0){
					dy=1; continue;
				}
				ans++;
			}
		}
		cout<<ans<<"\u";//没换行，气不气
	}
	return 0;
}
```

---

## 作者：BDFZ_hym_AK_hym_ing (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF1971D)
### 题目大意
给你 $t$ 组数据，每组数据输入一个字符串 $a$，可以把字符串切块后拼在一起，使变化后的字符串有序，求至少要切成几块。  
算法：贪心。
### 题目分析
步骤 $1$：去重并证明去重不影响答案：  
要令切块少，同为一个数字的肯定不会被分开。  
例子：`011` 可以被分成 `01|1`。  
但在 `01|1` 这两块能拼的情况下，剩下的每一块里面肯定为同一个数字，此时 `011` 也可以放进去。  
所以 `011` 不用分开，取开头结尾得 `01`，也就是去重。  

步骤 $2$：判断答案：  
最多有一个 `01` 作为分界线，剩下的必然每一块里面都是同一个数，  
又因为经过去重，所以有 `01` 的情况下可以少分 $1$ 块，即输出 $|s|-1$，  
如没有 `01` 的话输出 $|s|$。
### 代码
核心代码：
```cpp
string s,a="";
cin>>s;
long long i;
s=s+'!';
for(i=1;i<s.size();i++)
{
	if(s[i]!=s[i-1])
	{
		a=a+s[i-1];
	}
}
cout<<a.size()-(a.find("01")!=string::npos)<<"\n";
```

---

## 作者：天使宝贝 (赞：1)

[题面传送门](https://www.luogu.com.cn/problem/CF1971D)

### 题目简述

给你 $t$ 个 $01$ 串，把它分成若干份，使得它重新排列后所有 $0$ 在 $1$ 的前面，求最小的分段数。

### 分析&思路

很明显的贪心，只有 $0$ 和 $1$ 交界是需要切。

接下来我们就来分讨一下：

1、如果碰到连续的 $1$ 或 $0$，则不切。

2、如果遇到 $01$ 这个子串时，只保留其中的 $1$ 个。

3、如果遇到 $10$ 这个子串是，肯定得切。

### CODE
```cpp
#include <bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
int t;
int main()
{
    IOS;  // 读入加速
    cin >> t;
    while (t--)
    {
        int ans = 0;
        bool flag = 0;
        string s;
        cin >> s;
        for (int i = 0; i < s.size() - 1; i++)
        {
            if (s[i] == '1' && s[i + 1] == '0')
                ans++;
            else if (s[i] == '0' && s[i + 1] == '1')
            {
                if (!flag)
                    flag = 1;
                else
                    ans++;
            }
        }
        cout << ans + 1 << endl;  // 注意，本身还有一段，所以要 +1
    }
    return 0;
}
```

---

## 作者：Just_A_Sentence (赞：1)

# 题意翻译

输入 $t(1\le t\le 500)$ 个长度不超过 $500$ 的 01 串，要求你把它们分成尽量少的小段，并重新排列这些小段，使所有的 `0` 都在 `1` 前面，输出最小的段数。

# 分析

一道不错的思维（贪心）题。

首先，全是 `0` 和全是 `1` 的子串肯定不能分开~~这不废话吗~~；其次，当我们遇到 `01` 这个子串时，我们只能保留一个 `01` 子串，因为目标 01 串最多只含有一个 `01` 子串，剩下的都要分开；最后，所有的 `10` 子串都要分开。

赛时代码如下：

~~~cpp
#include<bits/stdc++.h>
using namespace std;
char s[5005];
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%s",&s);
		int ans=0,flag=0;
		int len=strlen(s);
		for(int i=0;i<len-1;i++){
			if(s[i]=='1'&&s[i+1]=='0') ans++;
			if(s[i]=='0'&&s[i+1]=='1'){
				if(flag==0) flag=1;
				else ans++;
			}
		}
		printf("%d\n",ans+1);//最后要记住加1，因为本来就有一段。
	}
	return 0;
}
~~~

---

## 作者：G1yu (赞：1)

## 题解 [CF 1971D Binary Cut](https://www.luogu.com.cn/problem/CF1971D)

### 题意

给定一个由 `1` 与 `0` 组成的串，可以对此串进行任意次数的拆分与重组，要求给出使该串中的 `0` 全在 `1` 的前面的最少拆分次数。

例如：`11000` 可以通过一次拆分后得到 `11` 与 `000` 就能重组为 `00011` 这个满足要求的串，所以答案是 $1$。

### 思路

因为所有连续的 `0` 串与连续的 `1` 串都能直接用，所以真正重要的是它们之间相接的部分。所以我们不难发现，整个串中对答案有影响的只有 $2$ 种类型的子串。

1. 在连续的 `0` 串与连续的 `1` 串之间的 `01` 串。对于这种子串，它们能起到目标串中 `0` 串与 `1` 串之间的衔接作用，但只能用一次。所以这种串在第二次以及之后遇到就需要分。

2. 在连续的 `1` 串与连续的 `0` 串之间的 `10`$ 串。因为题目要求 `0` 全在 `1` 的前面的串，所以这种子串是不允许在目标串中存在的。因此有多少个分多少次。

综上所述，总的拆分次数为：`01` 串出现次数 $+$ `10` 串出现次数 $-1$。更多细节见代码。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin>>T;
	while(T--){
		string a;
		cin>>a;
		int ans = 1;//一开始就有一串，所以ans初始值为1。
		bool book = 0;
		for(int i = 0; i<= a.size();i++){
			if(a[i]=='1'&&a[i+1]=='0'){ //10串一定要分开。
				ans++;
			}
			if(a[i]=='0'&&a[i+1]=='1'){ 
				//对于01串，第一个能作为0串和1串的衔接点，之后的要分开。
				if(!book){
					book = 1; 
				}
				else ans++;
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：JXR_Kalcium (赞：0)

## 题目大意
有一个二进制字符串，可以把它切割成几个部分，使得部分重新排列后为排序二进制字符串，求部分的最小值。

## 解题思路
可以想到，如果这个字符串中有 $10$，那么肯定要切割（因为要保证 $0$ 在前，$1$ 在后）。其次，如果出现了一次 $01$，那么就可以放在一排 $0$ 和一排 $1$ 之间，所以不用切割，但如果有一次以上，那么多余的就要切割了。

## AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int t,ans,bz;
char s[501];

int main()
{
	scanf("%d",&t);
	
	while(t--)
	{
		scanf("%s",s); ans=1; bz=0;
		
		for(int i=1; i<strlen(s); ++i)
		{
			if(s[i]<s[i-1] || s[i]>s[i-1] && bz) ++ans;
			if(s[i]>s[i-1] && bz==0) bz=1;
		}
		
		printf("%d\n",ans);
	}

	return 0;
}
```

---

## 作者：mc_xiexie (赞：0)

# CF1971D Binary Cut
## 思路
- $1$ 越往右这个二进制数字越小，将所有 $1$ 都往右移这个二进制数字最小。
- 将同样的数字分在一个片段分得的片段最少。

进而写出代码。
## 完整代码

```
#include <bits/stdc++.h>
using namespace std;
int main() {
	int t; 
	cin >> t;
	while(t--){
	    string s;
    	cin >> s;
    	int sum = 1;
    	bool ex = 0;
    	for (int i = 0; i + 1 < s.size(); i++) {
    		if(s[i] != s[i + 1]){
    		   sum++; 
    		}
            if(s[i] == '0' && s[i + 1] == '1'){
                ex=1;
            }
    	}
    	cout << sum - ex << '\n';
	}
}
```

---

## 作者：All_Unluck_Beginning (赞：0)

# 题解：CF1971D Binary Cut

## 题意

给予你一个 $01$ 字符串，你可以将它分割，分割后必须排成先 $0$ 后 $1$ 的格式。

求最少分割为几部分。

## 思路

将 $0$ 和 $1$ 分离出来。

如：

```
010001 ->  0 1 000 1
```

求出一共有几部分，记为 $sum$。

接下来分类讨论：

1. $sum=1$，即只有 $1$ 或 $0$ 的序列，输出 $1$。
2. $sum=2$ 且开头为 $1$，即需分成两段的序列，所以输出 $2$。
3. 其它情况，输出 $sum-1$，因为必有一对相邻的 $1$ 和 $0$ 相融合。

这道题就愉快的卡过去了。

## 代码

```
#include <bits/stdc++.h> 
using namespace std;
int t,sum=0;
string s;
int main () {
	cin>>t;
	while(t--){
		int truly=0,falsely=0;
		sum=0;
		cin>>s;
		for(int i=0;i<s.size();i++){
			if(s[i]=='0'){
				if(falsely==0)sum++;
				falsely++;
				truly=0;
			}else{
				if(truly==0)sum++;
				truly++;
				falsely=0;
				
			}
		}
		if(sum==1){
			cout<<1<<"\n";
		}else if(sum==2&&s[0]=='1'){
			cout<<2<<"\n";
		}else{
			cout<<sum-1<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：tder (赞：0)

[CF1971 场记](https://tder6.github.io/articles/CF1971A%20to%20CF1971G%20%E5%9C%BA%E8%AE%B0.html) 食用效果更佳。

---

**【题意】**

给定 01 序列 $s$，试将 $s$ 分成尽可能少的连续子序列，使得将其重排后组成的序列单调不减。多测。

**【思路】**

考虑最终的 $t=\tt00\cdots0011\cdots11$，必定含有若干个 $\tt00\cdots00$ 和若干个 $\tt11\cdots11$，以及至多一个 $\tt00\cdots0011\cdots11$。例如，$\tt0001111$ 可以被分为 $\tt00~|~011~|~1~|~1$。

那么不妨用 $k$ 标记当前是否有形如 $\tt00\cdots0011\cdots11$ 的子序列。从前往后扫一遍 $s$，分割成若干个单调不减（当 $k=1$ 时需要保证均相同）的子序列，并统计个数即可。

单组数据时间复杂度 $O(|s|)$。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 1e5 + 5;
string s; int n, k, cnt;
void solve() {
	cin>>s; n = s.length(); s = " " + s;
	int i = 1; k = cnt = 0;
	while(i <= n) {
        // cout<<"i = "<<i<<endl;
		if(!k) {
            // cout<<"qwq"<<endl;
			while(i <= n && s[i + 1] >= s[i]) {
                if(s[i + 1] > s[i]) k = 1;
                i++;
            }
		} else while(i <= n && s[i + 1] == s[i]) i++;
		cnt++; i++;
	}
	cout<<cnt<<endl;
}
int t;
signed main() {
	cin>>t;
	while(t--) solve();
}
```

---

## 作者：Harrylzh (赞：0)

考虑最终切出的串符合什么性质。

- 全 $0$ 串和全 $1$ 串是永远可以的，分别放在开头与结尾即可。

- 根据题意，串内有下降的情况是绝对不允许的，可以进行第一次切割。

- 先 $0$ 后 $1$ 串最多出现一个，多的也要切割。

按上述方案模拟即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		string s;
		cin>>s;
		long long n=s.size();
		s=' '+s;
		long long res=0;//第一次切割的次数
		long long res2=0;//第二次切割的次数
		char lst=s[1]; 
		for(long long i=2;i<=n;i++)
		{
			if(s[i]<s[i-1])
			{
				res++;
				if(lst=='0'&&s[i-1]=='1') res2++;
				lst=s[i];
			}
		}
		if(lst=='0'&&s[n]=='1') res2++;
		cout<<res+max(0ll,res2-1)+1<<"\n";
	}
	return 0;
 } 
```

---

## 作者：Chenyichen0420 (赞：0)

## 题目大意（暂无翻译2024.5.12）

给你一个二进制串。问你至少要把这个串分成多少段，才可能按一定顺序拼接成 $0$ 在前，$1$ 在后的串？

## 思路分析

时限给得太大了。

一个很简单的思路：把原二进制串中所有连着的 $0$ 或 $1$ 分别拆分出来，一定可以重组为符合要求的串。

显然，这样可能不是最优。我们会注意到假定原串中既有 $0$，又有 $1$，那么最终的串一定会有一个 $01$ 交界的地方。而如果原串中恰好有 $01$ 相接（一定不能是 $10$，否则要换顺序）的地方，那么我们没有必要将原串从这里分开。注意，如果原串中有多个这样的地方，那么只能选择其中一处，即只记一次。

实现时可以略带优化：我们本就需要统计连着的 $0$ 或 $1$ 组成的子串有多少个（假定有 $k$ 个）。那么相接处（不论 $01$ 顺序）必然有 $k-1$ 个。如果相接处数量 $\ge2$，那么其中一定有 $01$ 相接，答案为 $k-1$。如果相接处数量为零，那么整个串都是纯 $0$ 或 $1$ 串，答案为 $1$。如果相接处只有一个，那么判断首位是否为 $0$。是则答案为 $1$，否则答案为 $2$。证明显然，毕竟这里把连着的 $0$ 或 $1$ 形式的子串放到了一起。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, ans; string s, st;
signed main() {
	ios::sync_with_stdio(0);
	cin >> t;
	while (t--) {
		cin >> s; ans = 1;
		for (int i = 1; i < s.size(); ++i)
			ans += s[i] ^ s[i - 1];
		if (ans > 2) cout << ans - 1 << endl;
		else if (ans == 1) cout << 1 << endl;
		else cout << ans - (s[0] == '0') << endl;
	}
	return 0;
}
// 46ms / 8.00KB / 378B C++14 (GCC 9)
// 截至 2024.5.12 11:45 的最优解
```

---

