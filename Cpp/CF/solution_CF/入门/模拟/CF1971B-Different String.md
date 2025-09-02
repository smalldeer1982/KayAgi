# Different String

## 题目描述

给定一个以小写字母构成的字符串 $s$。

现在你的任务是，重新排列 $s$ 的字符以形成一个不等于 $s$ 的新字符串 $r$。

## 样例 #1

### 输入

```
8
codeforces
aaaaa
xxxxy
co
d
nutdealer
mwistht
hhhhhhhhhh```

### 输出

```
YES
forcodesec
NO
YES
xxyxx
YES
oc
NO
YES
undertale
YES
thtsiwm
NO```

# 题解

## 作者：cute_overmind (赞：14)

[题目传送门](https://www.luogu.com.cn/problem/CF1971B)

### 题目大意
给你 $t$ 组**小写**字符串，在经历各种变换后变成和原来**不同**的字符串。如果可以，输出 `YES`；反之输出 `NO`。

### 题目分析
考虑**暴力**求解。只要这一位的字符和前一位字符**不相同**，那就表示可以得到答案。反之，在最后输出 `NO` 即可。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
void solve()
{
	string s;
	cin >> s;
	int n = s.length();
	for(int i = 1;i < n;i++)
	{
		if(s[i] != s[i - 1]) 
		{
			cout << "YES" << "\n";
			swap(s[i] , s[i - 1]);
			cout << s << '\n';
			return ;
		}
	}
	cout << "NO" << "\n";
}
int main()
{
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
 } 
```

---

## 作者：yitian_ (赞：6)

## 题目分析

将给出 $t$ 个字符串，我们需要判断每个字符串能否重新排序成一个不相同的字符串。

## 思路

可以发现，只有一种情况无法重新排列成不同的字符串，即字符串中的所有字符都相同。也就是说，只要有任何两个字符不同，就可以重新排列成不同的字符串。

具体步骤如下：

1. 遍历字符串，判断相邻两个字符是否不相等。如果不相等，交换这两个字符，输出 `YES`，输出交换后的字符串。然后跳出循环。
2. 如果字符串中的所有字符都相同，输出 `NO`。

## C++ 代码实现

```c
#include<bits/stdc++.h> 
using namespace std;

int main()
{
	int t; 
	cin >> t; 
	while(t--)
	{
		int f=0; // 标记是否找到符合条件的重新排列
		string s;
		cin >> s;  
		for(int i=0;i<s.size()-1;i++) // 遍历 s 中的字符
		{
			if(s[i]!=s[i+1]) // 如果相邻字符不相同
			{
				f=1; // 标记找到了符合条件的重新排列
				swap(s[i],s[i+1]);// 交换相邻字符
				cout << "YES" << endl << s << endl; // 输出 YES 和重新排列后的字符串 s
				break; // 跳出循环
			}
		}
		if(f==0) // 如果没有找到符合条件的重新排列
		{
			cout << "NO" << endl; // 输出 NO
		}
	}
	return 0;
}
```

---

## 作者：Zskioaert1106 (赞：3)

### 题意分析
本题主要有两点：判断能否重排列以及重排列。
#### 能否重排列？
要将字符串 $s$ 重新排列以形成一个不等于 $s$ 的新字符串 $r$ ，仔细思考可以发现，只要字符串 $s$ 的所有字符不全是同一个，那么，就可以重排列。

那对于完全重复同一个字符的，我们自然可以说 `NO` 啦！

```cpp
for(int i=0;i<s.size();i++){
            if(s[i]!=s[i-1]&&i>0){
                panduan=1;
                continue;//节省时间
            }
        }
//打完才发现，i>0的判断是可以让循环中i从1开始的……
//大家也要检查优化自己的代码（虽然好像没人会犯这么低级的错误）
```
为了节省时间，我们可以在判断后加上 `continue` 。

#### 如何重排列？

如何重新排列成保证不同的字符串 $r$ 呢？我们看看判断部分的代码。

 ```if(s[i]!=s[i-1])``` 这是？我们根据相邻两个字符的异同就知道两个字符串不一样，那我们交换一下这两个字符就可以保证重新排列成保证不同的字符串啦！
 
 我们只用 `swap(s[i],s[i-1])` ，就得到了两个**保证不同**的字符串，这样是否有理论依据呢？
 
 （当然有！~~限于篇幅~~，请有疑问的读者思考并证明。）

闲话休讲，来上完整版的ＡＣ代码吧！

### ＡＣ代码

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int main(){
    int n;
    cin>>n;
    while(n--){//本题有多组测试数据
        bool b=0;
        string s;
        cin>>s;
        for(int i=1;i<s.size();i++){
            if(s[i]!=s[i-1]){//判断字符不同
                b=1;//添加标记
                swap(s[i],s[i-1]);//交换字符
                continue;//节省一分一秒
            }
        }
        if(b)cout<<"YES\n"<<s<<endl;//'\n'和endl是一个意思
        else cout<<"NO\n";
    }
    return 0;
}
```
感谢大家！（鞠躬）

---

## 作者：chenzhixuan2010 (赞：3)

### 题目大意：

一共有 $t$ 个字符串，对于每一个字符串，找到一个与这个字符串不同的字符串 $s$，使得重新排列字符串 $s$ 中的字符后可以变回原来的字符串。

### 思路：

可以枚举字符串中的每一个字符，如果这个字符与上一个字符不相同，那就可以把这两个字符调换组成新的字符串。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
void slove(){
	string s;
	cin>>s;
	int l = s.size();
	for (int i = 1;i < l;i++){
		if (s[i] != s[i - 1]){
			cout<<"YES\n";
			swap(s[i],s[i - 1]);
			cout<<s<<'\n';
			return ;
		}
	}
	cout<<"NO\n";
}

signed main(){
	int t;
	cin>>t;
	while (t--){
		slove();
	}
	return 0;
}
```

---

## 作者：volatile (赞：2)

# 题意

给出字符串 $s$，询问更改 $s$ 的排列顺序后与原来的 $s$ 是否不同，不同输出 `YES`，否则输出 `NO`。

# 思路

只要判断字符串中含有不同的字符即可。

# 代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int t;
	scanf("%d",&t);
	while(t--){
		char s[15];
		scanf("%s",s);
		int flag=1;
		for(int i=1;s[i]!='\0';i++){
			if(s[i]!=s[0]){
				swap(s[i],s[0]);
				printf("YES\n%s\n",s);
				flag=0;
				break;
			} 
		}
		if(flag) printf("NO\n");
	}
	return 0;
}
```

---

## 作者：AA12_G (赞：1)

好水的题，建议评红。
## 题目大意
一个字符串能不能重新排列他的字母让他不等于原来的字符串，多组数据。
## 思路
很简单啊，很容易发现：

- 如果 $s$ 里所有字符都相同，那么无论如何都不行。

- 如果至少一个字符不同，则可以将这个字符的位置调换到第一个，剩下字符向后延，这样就不一样了。

设 $s$ 的长度为 $k$，则时间复杂度为 $O(tk)$，能通过 $k \le 100000$ 的加强数据。

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s[1001];
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
	    cin>>s[i];//输入，没什么好说的
    }
    for(int i=1;i<=t;i++)
    {
    	bool f=1;int id=0;//f是有没有找到不相同的，id是不同的（第一个）的编号。
    	for(int j=1;j<s[i].size();j++)
    	{
    		if(s[i][j]!=s[i][j-1])//与前一个字符不同
    		{
    			f=0,id=j;//更新
                        break;//跳出循环
			}
		}
		if(f)cout<<"NO";//所有字符都一样，输出"NO"
		else
		{
			cout<<"YES\n";//先输出"YES"
				cout<<s[i][id];//第id个字符调换到第一个输出。
		for(int j=0;j<s[i].size();j++)
		{
			if(j!=id)cout<<s[i][j];//不是的话输出这个字符
		}
		
		}
	cout<<endl;//别忘了换行
	}
	return 0;
}
```

---

## 作者：OPEC (赞：1)

# [CF1971B Different String](https://www.luogu.com.cn/problem/CF1971B)

这道题只要有两种不同的字母，就可以组成一个新的字符串。如何组成一个新的字符串呢？这就需要把每一位都换个位置就可以了，这个和后面的换一下。

举几个例子:

`xxxxy` 变成 `xxxyx`

`abbbb` 变成 `bbbba`

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long
const int N=1e6+10,M=2e6+10;
const int INF=0x3f3f3f3f3f3f3f3f;
const int P=998244353;//3221225477
int t;
string s;
void solve()
{
	cin>>s;
	int tt=0;
	for(int i=0;i<s.size()-1;i++)
	{
		if(s[i]!=s[i+1])
		{
			swap(s[i],s[i+1]);
			tt=1;
		}
	}
	if(tt)
	{
		cout<<"YES\n";
		cout<<s<<'\n';
	}
	else
		cout<<"NO\n";
}
signed main()
{
	fst
	cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：Base_ring_tree (赞：1)

# solution
我们去想，他什么时候可以交换出可行的字串？那当然是他有**至少一个不同于相邻字符的字符**。不管是所有字母处一个以外都相同，还是每个字母都各不相同，都符合这个规则。那这样的话这道题不是易如反掌吗？！直接暴力遍历，找到这个与他相邻字母不同的那个字母，然后交换不就可以了么，毕竟只有一个字母与原字符串不同也属于可行情况滴！要是找不到呢，那就是不可行。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
string s;
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>s;
		bool flag=1;
		for(int i=1;i<s.size();i++)
		{
			if(s[i]!=s[i-1])//他与他相邻字母不同，交换
			{
				swap(s[i],s[i-1]);
				flag=0;
				break;
			}
		}
		if(!flag)
		{
			cout<<"YES"<<endl;
			cout<<s<<endl;
			flag=1;
		}
		else{
			cout<<"NO"<<endl;
		}
	}
	return 0;
 } 
```

---

## 作者：roumeideclown (赞：1)

# 题解：CF1971B Different String

## 题意简述

给定一个只包含小写字母的字符串 $s$，判断能否通过改变其中字母的排列顺序来得到一个新的字符串。若能，则输出 `YES` 并输出任意一种方案，否则输出 `NO`。

## 解法分析

显然，若有不同的字符，则可以做到。

## 参考代码

```
#include<bits/stdc++.h>
//#pragma G++ optimize(2,3,"Ofast")
using namespace std;
typedef long long ll;
string s;
int main() {
//  ios::sync_with_stdio(false);
//  cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	for(int i=1;i<=t;i++) { //多组数据
		cin>>s;
		bool flag=true;
		for(int j=0;j<s.length()-1;j++) {
			if(s[j]!=s[j+1]) { //判断不同的字符
				flag=false;
				break;
			}
		}
		if(flag) {
			cout<<"NO"<<'\n';
		}
		else {
			cout<<"YES"<<'\n';
			for(int j=1;j<s.length();j++) {
				cout<<s[j];
			}
			cout<<s[0]<<'\n';
		}
	}
	return 0;
}

```

---

## 作者：sunhaozhe111022 (赞：1)

**题目大意：**

给定 $n$ 个字符串，能否通过重新排列这些字符串，使其变成一个新的字符串。如果可以，输出 `YES` 和变换之后的字符串，否则输出 `NO`。

**思路：**

只需要判断有没有不同的字符即可，如果有，就交换两个不同字符的位置。

**C++ 代码实现：**
```cpp
#include<bits/stdc++.h>//万能头 YYDS！
using namespace std;
int n;//定义
string s;
int main()
{
    cin>>n;//输入，有 n 个字符串
    for(int i=1;i<=n;i++)//循环输入
    {
		cin>>s;//输入字符串 s
		string p=s;//记录原先的 s
		for(int j=1;j<s.size();j++)
		{
			if(s[j]!=s[j-1])//如果出现不相同的字符，代表可以变成新的字符串
			{
				swap(s[j],s[j-1]);//交换
				cout<<"YES\n"<<s<<endl;//输出，一定要换行！
				break;//跳出此循环
			}
		}
		if(p==s)//如果和原先的字符串没有变化，代表不行
		cout<<"NO\n";//输出
	}
    return 0;//华丽结束
}
```

---

## 作者：shapeshifter_lorde (赞：0)

蒟蒻第二篇题解。

遍历整个字符串，只要前一位字符与这一位不同，则能变换出新的字符串。

上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string str;
bool f;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		f=0;
		cin>>str;
		if(str.size()==1) cout<<"NO"<<endl;//特判只有一个字符的字符串 
		else{
			for(int j=1;j<str.size();j++){//从第二位开始判定，因此循环从1开始 
				if(str[j]!=str[j-1]){
					f=1;
					cout<<"YES"<<endl;
					swap(str[j],str[j-1]);
					cout<<str<<endl;//str[i]与str[i-1]交换后，已经不是原来的字符串了，此时可以直接输出。 
					break;
				}
			}	
			if(f==0) cout<<"NO"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Lian_zy (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1971B)

# 题目大意
给定 $t$ 个字符串，对于每个字符串 $s$，寻找与 $s$ 不同且能通过重新排列变回原来的字符串。

如果找不到这样的字符串，输出 `NO`，否则输出 `YES` 和这个字符串。

# 题目分析

只需要遍历每个字符串，然后遇到两位不一样的字符，交换后输出即可。

时间复杂度 $O(T|s|)$，还是很快的。

---

## 作者：tder (赞：0)

[CF1971 场记](https://tder6.github.io/articles/CF1971A%20to%20CF1971G%20%E5%9C%BA%E8%AE%B0.html) 食用效果更佳。

---

**【题意】**

给定字符串 $s$，求其的一个重排 $t$ 使得 $s\neq t$，或报告无解。多测。

**【思路】**

当且仅当 $s$ 中仅有一种字符，即 $s$ 中的每个字符均相同时，无解。

因此考虑将 $s$ 升序排序，若 $s_0=s_{|s|-1}$ 则无解，否则输出 $s$ 即可。

但是这样做可以被 $\tt aaab$ 轻松 Hack 掉，不信你可以去像我一样次罚时。于是不妨再降序排序一次，容易证明必定可行。

单组数据时间复杂度 $O(|s|\log|s|)$。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 1e5 + 5;
int t; string s, x;
signed main() {
	cin>>t;
	while(t--) {
		cin>>s; x = s;
		sort(x.begin(), x.end());
		if(s != x) {
			cout<<"YES"<<endl<<x<<endl;
			continue;
		}
		sort(x.begin(), x.end(), greater<char>());
		if(s != x) {
			cout<<"YES"<<endl<<x<<endl;
			continue;
		}
		cout<<"NO"<<endl;
	}
}
```

---

## 作者：huanglihuan (赞：0)

## [原题链接](https://codeforces.com/contest/1971/problem/B)
### 题目大意和目的
给出一个字符串 $s$，询问是否可以使用里面的字符拼成跟原本字符串不一样的字符串。
### 题目分析和思路
首先，我们需要判断 $s$ 中的字符是否 **全部相等**，是输出 `NO` 并结束本组程序，否则输出 `YES`。

接着，查找不一样的字符串在这里提供一种最简单的方法：即找跟第一个字符不同的字符调换两者位置。

### Code：
```cpp
#include <bits/stdc++.h>
#include <cstdio>
#define int long long
#define ull unsigned long long
#define mod 998244353
#define MOD 1000000007
using namespace std;
const int N = 1e5 + 5;

int a [N];

void solve ()
{
	string s;
	cin >> s;
	set <char> se;
	int len = s.size ();
	for (int i = 0;i < len;i ++) se.insert (s [i]);
	if (se.size () == 1)
	{
		cout << "NO\n";
		return ;
	}
	for (int i = 1;i < len;i ++)
	{
		if (s [i] != s [0])
		{
			swap (s [0],s [i]);
			break;
		}
	}
	cout << "YES\n" << s << endl;
}
signed main () {
	ios :: sync_with_stdio (false);
	cin.tie (0),cout.tie (0);
	int T;
	cin >> T;
	while (T --) solve ();
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

# 题解：CF1971B Different String

## 题意

给予你一个字符串 $s$，保证 $s$ 的长度小于等于 $10$。

任意排列 $s$，使其与原 $s$ 不同。

判断是否可以完成。

## 思路

由于字符串的长度最多为 $10$，我们可以尝试字符串的两个字符的所有交换。复杂度 $O(|s|^{2})$，这足够快了。如果它们都没有创建不同的字符串，那么原始字符串中的所有字符都是相同的，所以答案是否定的。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
string s;
int t,k=0;
int main() {
	cin>>t;
	while(t--) {
		k=0;
		cin>>s;
		for(int i=1;i<s.size();i++){
			if(s[i]!=s[0]){
				swap(s[i],s[0]);
				k=1;
				break;
			}
		}
		if(!k){
			cout<<"NO\n";
		}else{
			cout<<"YES"<<"\n";
			cout<<s<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：chenlongli (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1971B)
### 思路
本题其实就是找到有没有两个字符不一样，如果有就有解，否则就没解，如果有解，可以直接将这两个字符调换位置，就可以了。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int g,xg;
int main()
{
    int t,n;
    string k;
    cin>>t;
    for (int i=0;i<t;i++)
    {
    	cin>>k;
    	n=k.length();
    	char z1=k[0];
    	g=0,xg=0;
    	for (int j=1;j<n;j++)
    	{
    	    if (k[j]!=z1)
    	    {
    	        xg=j;
    	        break;
    	    }
    	}
    	if (xg==0)
    	{
    	    cout<<"NO"<<endl;
    	}
    	else
    	{
    	    cout<<"YES"<<endl;
    	    char x=k[g];
    	    k[g]=k[xg];
    	    k[xg]=x;
    	    cout<<k<<endl;
    	}
	}
}
```

---

## 作者：qinmingze (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1971B)

### 思路

题目让我们找字符串 $s$ 的任意一种排列，使它不等于原来的字符串 $s$，我们便可以想到只要有至少一位的字母是不一样的，那么就是可以的，因此当字符串中，**只有一种**字母时，那么肯定是**无解**的，因为无论怎么排，也不可能成功。而当**字母大于一种**时，肯定是**有解**的，然后我们**找到任意两个不同的字母进行交换**就可以了。

### 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 30;

int t[N];

int main(){
    int T;
    cin >> T;
    while(T--){
        string s;
        cin >> s;
        for(int i = 1; i <= 26; i++) t[i] = 0;
        for(int i = 0; i < s.size(); i++){
            t[s[i] - 'a' + 1]++;
        }
        int cnt = 0;
        for(int i = 1; i <= 26; i++){
            if(t[i]) cnt++;//统计字母种数。
        }
        if(cnt == 1)puts("NO");//只有一种时，无解。
        else{
            puts("YES");//有解。
            for(int i = 1; i < s.size(); i++){
                if(s[i] != s[0]){//找到不同的两个字母。
                    swap(s[i], s[0]);//进行交换。
                    break;
                }
            }
            cout << s << endl;//输出方案。
        }
    }
}
```

---

## 作者：zyn0309 (赞：0)

# CF1971B Different String
[题目传送门](https://www.luogu.com.cn/problem/CF1971B)
## 思路
枚举字符串 $s$ 中的每一位，如果 $s_i \ne s_{i-1}$，把 $s_i$ 和 $s_{i-1}$ 交换，即可得到新的字符串。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n;
bool flag;
int main(){
    cin>>n;
    for(int i=1;i<=n;++i){
      cin>>s;
      flag=0;
      for(int j=1;j<s.size();++j){
        if(s[j]!=s[j-1]){
          swap(s[j],s[j-1]);
          flag=1;
          cout<<"YES"<<endl<<s<<endl;
          break;
		}
	  }
	  if(!flag)
	    cout<<"NO"<<endl;
    }
    return 0;
}

---

## 作者：Infinite_Loop (赞：0)

# CF1971B
## 题意
给定一个由小写英文字母组成的字符串 $s$，将 $s$ 中的字符重新排列，组成一个新字符串 $r$，如果存在 $r$ 不等于 $s$，那么输出 ```YES```，再输出任意一个符合条件的 $r$；否则输出 ```NO```。
## 思路
我们发现，如果 $s$ 中的字符如果完全相同，那么不管怎样操作，新字符串 $r$ 一定和 $s$ 相同。

知道了这个性质，我们只需把 $s$ 从头到尾枚举一遍，如果有相邻的两个字符不一样的，则将两个字符交换即为符合的 $r$，跳出循环；如果循环结束还没找到，就输出 ```NO```。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string s;
int main(){
	cin>>t;
	while(t--){
		cin>>s;
		int n=s.size(),flag=0;
		for(int i=1;i<s.size();i++){
			if(s[i]!=s[i-1]){
				swap(s[i],s[i-1]);
				flag=1;
				break;
			}
		}
		if(flag)cout<<"YES"<<'\n'<<s<<'\n';
		else cout<<"NO"<<'\n';
	}
	return 0;
}
```

---

## 作者：mc_xiexie (赞：0)

# CF1971B Different String
## 思路
我们可以发现如果这个字符串只有一种字符就无法改变，所以用字符串的第一个字符判断后面的所有字符，如果不相等就交换这两个字符，输出“YES”。否则判断到最后一个字符，输出“NO”。
## 完整代码
```
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        string s;
        cin>>s;
        char c;
        c=s[0];
        bool b=0;
        for(int i=1;i<s.size();i++){
            if(s[i]!=c){
                swap(s[i], s[0]);
                b = 1; 
                break;
            }
        }
        if(b){
            cout << "YES\n";
            cout << s << '\n';
            continue;
        }
        cout<<"NO\n";
    }
    return 0;
}
```

---

## 作者：Dream_Mr_li (赞：0)

## Problem

给定一个由小写英文字母组成的字符串 $ s $。

重新排列字符串 $ s $ 的字符，形成一个新的字符串 $ r $，使得 $ r $ 不等于 $ s $，或者报告这是不可能的。

## Solution

因为如果每一位都相同的话必然输出 `NO`，所以这道题只需要将 $s$ 的每一位交换形成 $r$，再看 $s$ 与 $r$ 是否不同，如果是输出 `YES`，否则输出 `NO`。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
int n;string a,b; 
int main(){
	cin>>n;
	while(n--){
		cin>>a; b=a;//造一个新数组，以便与交换前的数组进行对比
		for(int i=0;i<b.size()-1;i++){
			swap(b[i],b[i+1]);//交换元素
		}
		if(a!=b){//判断 a 是否等于 b 
			cout<<"YES\n";
			cout<<b<<endl;
		}else{
			cout<<"NO\n";
		}
	}
	return 0;
}
```

---

## 作者：FXLIR (赞：0)

### 题意简述

给你一个字符串 $s$，问你能不能通过重新排列 $s$ 中的字符形成一个和 $s$ 不相同的字符串 $r$。
### 题目做法

不难想到，如果 $s$ 中只有一种字符，那么如何排列都不能形成与原串不同的字符串。但是只要有两种以上不同的字符，肯定能形成与原串不同的字符串。

因此，我们可以用 `map` 对每一个字符串中的字符种数进行统计，`map` 中的元素数量就是字符的种数。如果字符只有 $1$ 种，肯定不能排列成不同的字符串，输出 `NO` 即可。否则，我们可以直接将字符串倒序输出。

然而，这样的思路并不是完全正确的。如果遇到一个回文串，比如 `aabaa`，倒序输出和原串是一致的。

因此对于回文串，可以将最中间的一个字符放到新串的最前面，剩下的字符按原顺序输出。这样就解决了回文串的问题。

### AC code

```cpp
#include<map>
#include<string>
#include<iostream>
using namespace std;
int t;
string s;
bool is(string a){
	for(int i=0;i<a.size();i++){
		if(a[i]!=a[a.size()-i-1]){
			return 0;
		}
	}
	return 1;
}
int main(){
	cin>>t;
	while(t--){
		map<char,bool> mp;
		cin>>s;
		for(int i=0;i<s.size();i++){
			mp[s[i]]++;
		}
		if(mp.size()>1){
			cout<<"YES\n";
			if(!is(s)){
				for(int i=s.size()-1;i>=0;i--){
					cout<<s[i];
				}
			}else{
				cout<<s[(s.size()-1)/2];
				for(int i=s.size()-1;i>=0;i--){
					if(i!=(s.size()-1)/2){
						cout<<s[i];
					}
				}
			}
			cout<<"\n";
		}else{
			cout<<"NO\n";
		}
	}
	return 0;
} 
```

---

## 作者：keep_shining (赞：0)

## 题意：
有 $t$ 组样例，每组样例输入一个字符串 $s$，对于输入的字符串，你要通过变换将其变成新的字符串，如无法变换成新的输出 “NO”，若可以变换成新的先输出“YES”，再输出变换后的字符串。

## 思路：
很明显，只有当字符串中所有字符都相同时才输出“NO”，否则一定能变换成新的，那我们扫一遍字符串，看字符串中的字符是否全部相同，过程中顺便帮它变换一下。

## AC code：
```cpp
#include<bits/stdc++.h>

using namespace std;

#define fst ios::sync_with_stdio(false);cin.tie();cout.tie();
#define Endl endl
#define itn int
#define For(i,a,b) for(register int i=a;i<b;i++)
#define endl '\n'
#define rep(i,a,b) for(int i=b;i>=a;i--)

const int N=1e6+5;
const int M=2e3+5;

int t;

int read()
{
	register int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}

void write(int x)
{
	if(x>9)write(x/10);
	putchar(x%10+'0');
}

int main()
{
	t=read();
	while(t--)
	{
		string s;
		cin>>s;
		bool f=true;
		For(i,0,s.size()-1)//扫一遍
		{
			if(s[i]!=s[i+1])//不同的话就能变换，那就帮它变一下
			{
				swap(s[i],s[i+1]);
				f=false;//标记为可变换
			}
		}
		if(f)cout<<"NO"<<endl;//不可变换，输出“NO”
		else cout<<"YES"<<endl<<s<<endl;//能变换，输出“YES”加变换后的字符串
	}
    return 0;
}
```

---

