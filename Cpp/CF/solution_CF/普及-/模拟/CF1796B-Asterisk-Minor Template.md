# Asterisk-Minor Template

## 题目描述

You are given two strings $ a $ and $ b $ , consisting of lowercase Latin letters.

A template $ t $ is string, consisting of lowercase Latin letters and asterisks (character '\*'). A template is called asterisk-minor if the number of asterisks in it is less than or equal to the number of letters in it.

A string $ s $ is said to be matching a template $ t $ if you can replace each asterisk in $ t $ with a string of lowercase Latin letters (possibly, an empty string) so that it becomes equal to $ s $ .

Find an asterisk-minor template such that both $ a $ and $ b $ match it, or report that such a template doesn't exist. If there are multiple answers, print any of them.

## 说明/提示

In the first testcase, for a template "\*b", you can replace the only asterisk with "aaa" to get "aaab" (which is equal to $ a $ ) or with "zzz" to get "zzzb" (which is equal to $ b $ ).

In the third testcase, a template "\*o\*" is not asterisk-minor, as it contains more asterisks than letters. There are no asterisk-minor templates that both $ a $ and $ b $ match.

In the fourth testcase, for a template "a\*a\*a\*a", you can replace all asterisks with empty strings to get "aaaa" (which is equal to $ a $ ) or two of them with "a" and two of them with an empty string to get "aaaaaa" (which is equal to $ b $ ).

In the fifth testcase, there are no asterisks in a template "abcd", so only "abcd" can match it (which is coincidentally both $ a $ and $ b $ ).

## 样例 #1

### 输入

```
6
aaab
zzzb
codeforces
atcoder
codeforces
tokitlx
aaaa
aaaaaa
abcd
abcd
c
f```

### 输出

```
YES
*b
YES
*co*
NO
YES
a*a*a*a
YES
abcd
NO```

# 题解

## 作者：silent_ST (赞：2)

## 题意

给出两个字符串 $a,b$，输出一个由 `*` 和小写字母组成的字符串，满足：
1. 将所有的 `*` 用任意字符串替换，可以得到 $a$ 和 $b$

2. 小写字母的个数必须大于等于 `*` 的个数

## 思路

不难发现需要找出 $a, b$ 的公共子串（满足条件1），且公共子串长度大于等于 $2$（满足条件2）。

所以只需要找到 $a, b$ 的长度为 $2$ 的公共子串，如果找不到输出 `NO`。

此时输出字符串形式为 $* X *$ 。

注意特判：

首项相同，后面的所有项就可以直接用 * 代替（即 $X *$）；

末项相同，前面的所有项就可以直接用 * 代替（即 $* X$）。

## AC Code

```cpp

#include <iostream>
#include <string>
using namespace std;
int t;
int main(){
	cin >> t;
	while(t--){
		string a, b;
		cin >> a >> b;
        
		//首项相等特判
		if(a[0] == b[0]){
			cout << "YES" << '\n' << a[0] << "*" << '\n';
			continue;
		}
        
        //末项相等特判
		if(a[a.size() - 1] == b[b.size() - 1]){
			cout << "YES" << '\n' << "*" << a[a.size() - 1] << '\n';
			continue;
		}
        
		//找公共子串
		bool flag = false;
		for(int i = 0; i < a.size() - 1; i++){
			string check = a.substr(i, 2);
			if(b.find(check) != string::npos){
				flag = true;
				cout << "YES"  << '\n' << "*" << check << "*" << '\n';
				break;
			}
		}
		if(!flag) cout << "NO" << '\n';
	}
	return 0;
}
```

---

## 作者：SlyCharlotte (赞：2)

[更好的阅读体验？](https://zhuanlan.zhihu.com/p/610522558)


## 题意描述

给你两个字符串 $S,T$，你需要给出一个由 * 与小写字母组成的字符串，需要满足以下条件：

1. 其中个数小于等于小写字母的个数。
2. 使用若干小写字母代替 * 使得与 $S$ 相同，每个 * 可以用不同的若干小写字母代替。
3. 使用若干小写字母代替 * 使得与 $T$ 相同，每个 * 可以用不同的若干小写字母代替。

没有满足条件的输出 NO，否需要先输出 YES。

## 简要分析

不按发现，需要给出的字符串要么是 $X*$，$*X$ 或 $*X*$，其中 $X$ 代表若干小写字母，对于第三者 $X$ 的长度必须大于等于 $2$。

随后，分类讨论即可。

## 代码实现

```C++
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

typedef long long ll;
const ll maxn = 1e5 + 7;
const ll INF = 1e9 + 7, MOD = 998244353;

inline ll read() {
    char cCc;
    ll xXx = 0, wWw = 1;
    while (cCc < '0' || cCc > '9')
        (cCc == '-') && (wWw = -wWw), cCc = getchar();
    while (cCc >= '0' && cCc <= '9')
        xXx = (xXx << 1) + (xXx << 3) + (cCc ^ '0'), cCc = getchar();
    xXx *= wWw;
    return xXx;
}

inline void write(ll xXx) {
    if (xXx < 0)
        putchar('-'), xXx = -xXx;
    if (xXx > 9)
        write(xXx / 10);
    putchar(xXx % 10 + '0');
}

void solve() {
    string s, t;
    cin >> s >> t;
    if (s[0] == t[0]) {
        cout << "YES\n";
        cout << s[0] << "*\n";
    } else if (s[s.size() - 1] == t[t.size() - 1]) {
        cout << "YES\n" << "*" << t[t.size() - 1] << '\n';
    } else {
        bool flag = false;
        set<string> v1;
        for (ll i = 0; i + 1 < s.size(); i++) {
            v1.insert(s.substr(i, 2));
        }
        for (ll i = 0; i + 1 < t.size(); i++) {
            if (v1.contains(t.substr(i, 2))) {
                cout << "YES\n" << '*' << t.substr(i, 2) << "*\n";
                flag = true;
                break;
            }
        }
        if(!flag)cout << "NO\n";
    }
}

signed main() {
//    freopen("code.in","r",stdin);
//    freopen("code.out","w",stdout);
    ll T = read();
    while (T--)solve();
    return 0;
}
```


---

## 作者：Pyrf_uqcat (赞：1)

题板写得也是相当的抽象，第一眼还看不懂，先分析一下题板。

两个字符串，可以用 `*` 代替两个字符串中不同的子串，相同子串用这个子串代替。然后 `*` 不能比字符多。

思路：如果头尾的字符一样，那直接用 `*` 代替另一个方向的子串。不难想到，如果能使用两个 `*` 那一定成立，因为两个 `*` 可以向两边延伸，而如果要使用两个 `*` 那就一定要两个字符，所以只要依次遍历是否有两个连续的共同字符，就可以了。

---

## 作者：Mason123456 (赞：1)

## [CF1796B](https://www.luogu.com.cn/problem/CF1796B)

### 题目大意（~~主要是翻译的不太清晰~~）

给定两个字符串 $A, B$，其中，可以用 `*` 省略一段任意字符串，使得 `*` 替换成字符串后可以得到 $A$ 或 $B$ 字符串。但 `*` 的个数不能超过字母的个数。

### 提示

本题是 `special judge`。

### 思路

不难发现，尽管样例是 `a*a*a*a`，但是可以替换成 `*aa*`。也就是说，只要发现有一个长度为 $2$ 且同时为 $A, B$ 的子串即可。但是有一个特例（首字母或尾字母相同），即字符串只用一个 `*`，就无需长度为 $2$ 的子串了。

### Code

注意，代码中 `\n` 表示换行。

```cpp
#include <bits/stdc++.h>
using namespace std;
int q;
int main(){
	ios::sync_with_stdio(0);// 氮气加速 
	cin.tie(0);
	cout.tie(0);
	cin>>q;
	while(q--){
		string a,b;
		bool f = 0;// 标记是否找到公共长度为2的子串 
		cin>>a>>b;
		if(a.size() < b.size())	swap(a,b);// 应该不太需要，但是如果是用substr的话就有必要了 
		
		// 特判，首字母或尾字母相同 
		if(!f && a[0] == b[0]){
			cout<<"YES\n"<<a[0]<<"*\n";
			f = 1;
		}
		if(!f && a[a.size()-1] == b[b.size()-1]){
			cout<<"YES\n*"<<a[a.size()-1]<<"\n";
			f = 1;
		}
		
		
		// 寻找是否有长度为2的子串 
		for(int i = 0;i < a.size() - 1;i++){
			for(int j = 0;j < b.size() - 1;j++){
				if(a[i] == b[j] && a[i+1] == b[j+1] && !f){
					cout<<"YES\n*"<<a[i]<<a[i+1]<<"*\n";
					f = 1;
				}
			}
			
		}
		
		if(!f){
			cout<<"NO\n";
		}
	}
	
	return 0;
}

```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1796B)

# 思路：
对于一个模板 $T$，其一定可以表示为 ```*c```、```c*```、```*cd*``` 的形式，所以可以对于每一个都判断一下就好了。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e3+10;
const int INF=0x3f3f3f3f;
char s[N],t[N]; 
bool flag1[N][N];
int T;
signed main(){
	cin>>T;
	while(T--){
		scanf("%s%s",s+1,t+1);
		int n=strlen(s+1),m=strlen(t+1);
		bool flag=false;
		for(int i=1;i<n;i++){
            flag1[s[i]-'a'][s[i+1]-'a']=true;
        }
		for(int i=1;i<m;i++){
			if(flag1[t[i]-'a'][t[i+1]-'a']){
				flag=true;
				cout<<"Yes"<<endl<<"*"<<t[i]<<t[i+1]<<"*"<<endl;
				break;
			}
		}
		if(s[1]==t[1]&&!flag){
            cout<<"Yes"<<endl<<s[1]<<"*"<<endl;
            flag=true;
        }
		if(s[n]==t[m]&&!flag){
            cout<<"Yes"<<endl<<"*"<<t[m]<<endl;
            flag=true;
        }
		if(!flag){
            cout<<"No"<<endl;
        }
		for(int i=1;i<n;i++){
            flag1[s[i]-'a'][s[i+1]-'a']=false;
        }
	}
	return 0;
}
```
完结撒花~

---

## 作者：Dream_Stars (赞：0)

## 题目大意：
题目定义了一种“字符串模板”的概念，就是可以使用 `*` 来代替一个任意的字符子串，使两个字符串都满足这个模板，如果有存在的模板，那么就输出 `YES` 和模板，否则，就输出 `NO`。

## 算法分析：
我们可以将模板归结成以下三种格式中的一种（$X$ 为一个相同的任意串）。

- `*X` 最开始的字符一样；
- `X*` 最末尾的字符一样；
- `*X*` 中间一部分的字符一样。

虽然题目样例中有一组数据是\
输入：
```cpp
aaaa
aaaaaa
```
输出：
```cpp
a*a*a*a`
```
这组样例不属于以上所述的任意一种情况，那怎么办，我们可以将这个数据的输出给改为 `a*` 这样也符合题目的意思，并且最后的所有数据都可以通过。所以，我们前两种情况只需要判断第一个字符与最后一个字符是否一样即可，并不需要找到最长的。

所以，我们可以将所有的情况归结为三种情况进行分情况各自讨论即可。
## 代码展示：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,lx,ly;
string x,y;
bool flag;
void paint(){
  printf("YES");
  printf("\n");
  printf("%c",x[0]);
  printf("*");
  printf("\n");
  return ;
}
void paint_(){
  printf("YES");
  printf("\n");
  printf("*");
  printf("%c",x[lx - 1]);
  printf("\n");
  return ;
}
void paint__(int l){
  flag = true;
  printf("YES");
  printf("\n");
  printf("*");
  printf("%c",x[l]);
  printf("%c",x[l + 1]);
  printf("*");
  printf("\n"); 
  return ;
}
void paint___(){
  printf("NO");
  printf("\n");
  return ;
}//到这里为止都是几种情况的输出和变量的定义。
//这样可以使主程序更为简洁。
int main(){
  cin>>n;
  for(int i = 1 ; i <= n ; i++){
    cin>>x>>y;
    lx = x.size() , ly = y.size() , flag = false;
    if(x[0] == y[0]) paint();
//开头一样的情况。
    else if(x[lx - 1] == y[ly - 1]) paint_();
//结尾一样的情况。
    else{
//中间有一部分一样的情况。
     for(int i = 0 ; i < lx - 1 ; i++){
      for(int j = 0 ; j < ly - 1 ; j++)
       if(x[i] == y[j] && x[i + 1] == y[j + 1]){
//发现有模板就直接输出。
        paint__(i);
        break;
       }
      if(flag==true) break;//找到一种答案了就可以直接跳出循环了。
	  }
    if(flag==false) paint___();//如果没有模板，输出NO。
	  }
  }
  return 0;//return 养成好习惯。
}
```

---

## 作者：__bjxx0201__ (赞：0)

## 题目大意

现在给出 $t$ 组数据，每一组数据有两个字符串 $a$ 和 $b$，试求出一个合法的模版 $T$ 是否能过替换这两个字符串。

## 思路

[题目传送门](https://www.luogu.com.cn/problem/CF1796B)

考虑到贪心的做法。

题目有点特殊，如果要保证答案有解，就需要满足以下 $3$ 条的任意一条：

1. 只有头上有 `*`。
2. 只有末尾有 `*`。
3. 字符串头尾有 `*`。

好的，接下来逐一分析。第一条，就可以在两个字符串的开头来判断是否能成立，如果能够成立，就直接输出 `YES`。

接下来第二条，末尾相同，一样的道理，判断两个字符串末尾是否相同，如果相同就直接输出 `YES`。

接下来就比较难办（贪心的思路在这里），如果收尾都不相同，就需要在两个字符串找出两个相同的字符（这样可以将这两个字符都变成 `*`，正确性显然），如果找出来了，依旧可以直接输出 `YES`。

其余的情况，就可以输出 `NO` 了。

以下展示循环内部的代码：

```
    	bool flag=false;//假设法。
    	string a,b;
    	cin>>a>>b;
    	if (a[0]==b[0]) {
    		cout<<"YES\n";
    		cout<<a[0]<<"*\n";
		}
		if (a[a.size ()-1]==b[b.size ()-1]) {
			cout<<"YES\n*";
			cout<<a[a.size ()-1]<<"\n";
		}
		else {
			for (int i=0;i<a.size ();i++) 
			    for (int j=0;j<b.size ();j++) {
			    	if (a[i]==b[j] && a[i+1]==b[j+1]) {
			    		cout<<"YES\n*";
			    	    cout<<a[i]<<a[i+1];
			    	    cout<<"*\n";
			    	    flag=true;
			    	    break;
					}
				}
			if (flag==true) break;
		}
```

---

## 作者：JHR100330 (赞：0)

# 题解：CF1796B Asterisk-Minor Template

#### upd 2024/7/23:修改了一处KaTeX错误。

本题考查贪心。

由于通配符 `*` 可以代替任意长度和形式的子串，且 `*`
的个数要小于等于剩余字符的个数，则考虑贪心。

设两个字符串为 $a,b$，长度分别为 $len_a,len_b$。

共分为四种情况：

1. 对于两字符串首字符相等的情况，很明显，将第二个字符及以后的全部字符全部替换为 `*` 即可，即输出 $a_0$（$b_0$）和一个 `*`。例：`abbb`，`accc` 都可转化为 `a*`。

1. 对于两字符串尾字符相等的情况，同理，将倒数第二个字符及以前的字符全部替换为 `*` 即可，即输出 $a_{len_a - 1}$（$b_{len_b - 1}$）和一个 `*`。例：`aaac`，`bbbc` 都可转化为 `*c`。

1. 对于两字符串中间有两个连续字符 $a_i,a_{i+1}$ 与 $b_i,b_{i+1}$ 相等的情况，即 $a_i = b_i,a_{i+1} = b_{i+1}$，同样的，将 $a_i$ 前、$a_{i+1}$ 后、$b_i$ 前、$b_{i+1}$ 后的字符全部替换为 `*` 即可，即输出 `*`，$a_i,a_{i+1}$（$b_i,b_{i+1}$），`*` 即可。例：`aaaaaaxybbbbb`，`cccxyd` 都可转化为 `*xy*`。

1. 对于其他的所有情况，不可能存在合法的模版（`*` 的个数 $\gt$ 剩余字母的个数），输出 `NO`。

## AC Code：

```cpp
#include<bits/stdc++.h>

using namespace std;

int t, lena, lenb;
bool solve; // 判断是否已经解决
string a, b;

int main() {
	cin >> t;
	while(t --){
		solve = 0;
		cin >> a >> b;
		lena = a.size(); lenb = b.size();
		if(a[0] == b[0]){printf("YES\n%c*\n", a[0]); continue;} // 首字符相等
		if(a[lena - 1] == b[lenb - 1]){printf("YES\n*%c\n", a[lena - 1]); continue;} // 尾字符相等
		for(int i = 0; i < lena - 1; i ++){ // 中间两个连续字符相等
			for(int j = 0; j < lenb - 1; j ++){
				if(a[i] == b[j] && a[i + 1] == b[j + 1]){ // 成功匹配
					printf("YES\n*%c%c*\n", a[i], a[i + 1]);
					solve = 1;
					break;
				}
			}
			if(solve) break;
		}
		if(!solve) puts("NO"); // 无解
	}
	return 0;
}
```

---

## 作者：Rookie_t (赞：0)

首先，我们要知道一共有三种有解的情况：

1. 头尾都有 `*`。 

2. 仅是头上有 `*`。 

3. 最后有 `*`。

然后，就要看如何添加 `*`。

如果两字符串首位相同，即 $s_1 = t_1$，可以将首位后改为 `*`。

如果两字符串末位相同，即 $s_{len1-1} = t_{len1-1}$，可以将末位后改为 `*`。

如果首尾均不相同，枚举两字符串。

如果有两个连续相同的字符，将此两位前后都改为 `*`，输出 `YES`。

否则输出 `NO`。


```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t;
int T,len1,len2;
bool b;
int main(){
    cin>>T;
    while(T--){
		b = 0;
		cin>>s>>t;
		len1 = s.size();
		len2 = t.size(); 
		if(s[0] == t[0]){
	        cout<<"YES"<<endl;
	        cout<<s[0]<<"*"<<endl;
		    b = 1;
		}
		else if(s[len1-1] == t[len2-1]){
		    cout<<"YES"<<endl;
		    cout<<"*"<<s[len1-1]<<endl;
		    b = 1;
		}
		else{
		    for(int i = 0;i<len1-1;i++){
				for(int j = 0;j<len2-1;j++){
				    if(s[i] == t[j]&&s[i+1] == t[j+1]){
						cout<<"YES"<<endl;
						cout<<"*"<<s[i]<<s[i+1]<<"*"<<endl;
						b = 1;
						break;
				    }
				}
				if(b){
					break;
				}
		    }
		}
		if(!b){
			cout<<"NO"<<endl;
		}
    }
    return 0;
}
```

---

## 作者：Rubedo_N (赞：0)

# CF1796B Asterisk-Minor Template 题解
## 思路
输出有 $3$ 种情况：
* 首位有 `*`。
* 尾位有 `*`。
* 中间是相同字符，首尾都有 `*`。

判断添加 `*` 的位置：
* 若两字符串首位相同，可以将首位后改为 `*`。
* 若两字符串末位相同，可以将末位前改为 `*`。
* 首尾均不相同，枚举两字符串。若有两个连续相同的字符，将此两位前后都改为 `*`，跳出循环，输出 `YES`。若一直为找到两个连续相同的字符，输出 `NO`。

具体思路见代码注释。
## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s1,s2;
int t,l1,l2;
bool flag;
int main(){
    cin>>t;
    while(t--){
		flag=false;
		cin>>s1>>s2;
		l1=s1.size();
		l2=s2.size(); 
		if(s1[0]==s2[0]){//首相同 
	        cout<<"YES"<<endl;
	        cout<<s1[0]<<"*"<<endl;
		    flag=true;
		}
		else if(s1[l1-1]==s2[l2-1]){//尾相同 
		    cout<<"YES"<<endl;
		    cout<<"*"<<s1[l1-1]<<endl;
		    flag=true;
		}
		else{
		    for(int i=0;i<l1-1;i++){//不包括首尾 
				for(int j=0;j<l2-1;j++){//不包括首尾 
				    if(s1[i]==s2[j]&&s1[i+1]==s2[j+1]){//两个连续字母相同
						cout<<"YES"<<endl;
						cout<<"*"<<s1[i]<<s1[i+1]<<"*"<<endl;
						flag=true;
						break;
				    }
				}
				if(flag)break;
		    }
		}
		if(!flag)cout<<"NO"<<endl;//未找到 
    }
    return 0;
}
```

---

## 作者：QoQ_ (赞：0)

## 分析：

不难发现，其实输出一共只有三种，一种是前后都有 ```*```，一种是只有前面有 ```*```，还有一种就是后面有 ```*```，而输出 ```*``` 的条件就是除了字符串 $a,b$ 的公共子串，其他小写字母改写为 ```*```，那我们只要判断开头是否有相同子串，然后再判断结尾，最后再用一个循环来寻找 $a,b$ 中间的公共子串，若没有公共子串则输出 ```NO```。

## code 参考：
```
#include<bits/stdc++.h>
using namespace std;
string str,str2,s;
int n,la,lb;
bool cmp;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>str>>str2;
        cmp=false;
        la=str.size();
        lb=str2.size();
        if(str[0]==str2[0]){
            cout<<"YES"<<"\n";
            cout<<str[0]<<"*"<<"\n";
        }else if(str[la-1]==str2[lb-1]){
            cout<<"YES"<<"\n"<<"*";
            cout<<str[la-1]<<"\n";
        }else{
            for(int j=0;j<la-1;j++){
                s=str.substr(j,2);
                if(str2.find(s)!=string::npos){
                    cout<<"YES"<<"\n"<<"*"<<s<<"*"<<"\n";
                    cmp=true;
                    break;
                }
            }
            if(cmp==false){
                cout<<"NO"<<"\n";
            }
        }
    }
    return 0;
}
```
无注释，~~方便食用~~。

本蒟蒻的第三篇题解，望过 QAQ~

---

## 作者：ST_AS_IS_ZHY (赞：0)

## 题面翻译

定义一个字符串的模板 $T$，其中仅包含小写字母和可以代替任意字符串（包括空字符串）的通配符 ``*``。一个合法的模板需要满足 ``*`` 的数量小于等于小写字母的数量。

有一个仅包含小写字母的字符串 $s$，如果我们可以选择出一个合法的模板 $T$，可以通过替换所有的 ``*`` 使其等于 $s$，则称字符串 $s$ 与模板 $T$ 匹配。

现在有 $t$ $(1 \le t \le 10^4) $ 组询问，每次给出两个仅包含小写字母的字符串 $a,b$ $(1\le|a|,|b|\le 50)$，请给出一个合法的模板 $T$ 使其能同时匹配两个字符串，或输出无解 ``NO``。

## 题意

就是给你两个字符串，让你找到他们的一个相同的模板，模板就是将模板中的通配符 ``*`` 替换成任意的一个字符串后可以得到原来的字符串。

## 思路

先找到字符串首尾是否会出现相同的字母，如果有相同的字母，那他们的模板必然可以表示为他们相同的字母加上一个通配符 ``*``,若首尾没有，则去找字符串内有没有两个连续字母相同，毕竟要求指示符数量要小于等于小写字母数量，若找到了，他们的模板就可以表示为通配符 ``*`` 加上相同的两个字母加上通配符 ``*``。

## 代码

```c++
// Problem: Asterisk-Minor Template
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1796B
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
int t;
char ch;
bool flag;
int main()
{
    cin >> t;
    while(t --)
    {
	flag = false;
	string s1,s2;
	cin >> s1;
	cin >> s2;
	if(s1[0] == s2[0])
        {
            cout << "YES" <<'\n';
            cout << s1[0] << "*" << '\n';
	    flag = true;
	}
	else if(s1[s1.size() - 1] == s2[s2.size() - 1])
	{
	    cout << "YES" << '\n';
	    cout << "*" << s1[s1.size() - 1] << '\n';
	    flag = true;
	}
	else
	{
	    for(int i = 0 ; i < s1.size() - 1; i ++)
	    {
		for(int j = 0 ; j < s2.size() - 1; j ++)
		{
		    if(s1[i] == s2[j] && s1[i + 1] == s2[j + 1])
		    {
			cout << "YES" << '\n';
			cout << "*" << s1[i] << s1[i + 1] << "*" <<'\n';
			flag = true;
			break;
		    }
		}
		if(flag) break;
	    }
	}
	if(!flag) cout << "NO" << '\n';
    }
    return 0;
}
```

---

## 作者：Crazyouth (赞：0)

**分析**

注意到 `*` 可以只有 $2$ 个，所以只要有长度为 $2$ 的公共子串，就是 `YES`。另外还有可能就是 `X*` 或 `*X`，特判这两种情况即首字母相同或尾字母相同即可。

**AC Code**

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t,maxx,ans,tp,tp2,tp3,flag;
	string a,b;
	cin>>t;
	while(t--)
	{
		flag=0;
		tp3=0;
		ans=0;
		maxx=-1;
		cin>>a>>b;
		for(int i=0;i<a.size()-1;i++)
		{
			for(int j=0;j<b.size()-1;j++)
			if(a[i]==b[j]&&a[i+1]==b[j+1])//判中间两字母的情况
			{
				cout<<"YES"<<endl;
				if(i>0||j>0) cout<<'*';//判要不要前*
				cout<<a[i]<<a[i+1];
				if(i<a.size()-2||j<b.size()-2) cout<<'*';//判要不要后*
				cout<<endl;
				flag=1;
				break;
			}
			if(flag) break;
		}
		if(!flag)
		{
			if(a[0]==b[0])//判断X*
			{
				cout<<"Yes\n"<<a[0]<<'*'<<endl;
				continue;
			}
			if(a[a.size()-1]==b[b.size()-1])//判断*X
			{
				cout<<"YES\n*"<<a[a.size()-1]<<endl;
				continue;
			}
			cout<<"NO"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：NotNaLocker (赞：0)

## CF1796B Asterisk-Minor Template 题解
### ~~几~~句闲话
有可能是 SPJ 哦。
### 题目思路
模板字符串 $T$ 有以下几种情况（假设 $T$ 中小写字母串用 `s` 表示）：

- `s*`，即 $a_0$ 与 $b_0$ 相同的情况。

- `*s`，即 $a$ 的最后一个字符与 $b$ 的最后一个字符相同的情况。

- `*s*`，即 $a$ 的某个字串与 $b$ 的某个子串相同的情况，需要保证 `s` 至少有两个字符。

### 题目实现
第一种情况，可以直接特判：

```cpp
if(a[0]==b[0]){
	cout<<"YES"<<endl<<a[0]<<"*"<<endl;
}
```

第二种情况也一样：

```cpp
else if(a[lena-1]==b[lenb-1]){
	cout<<"YES"<<endl<<"*"<<a[lena-1]<<endl;
}
```

第三种情况，由于前两种情况已经排除了 $a_0$ 和 $a_{lena-1}$，所以需要从 $a_1$ 到 $a_{lena-2}$ 进行遍历。

每次取 $a_i$ 至 $a_{i+1}$ 两个字符存储到一个串，原因已说明。随后在 $b$ 中查找，若找到，就输出并标记，然后退出。

```cpp
else{
	for(int i=0;i<lena-1;i++){
		string ext=a.substr(i,2);  //截取，存储
		if(b.find(ext)!=string::npos){  //如果找到
			cout<<"YES"<<endl<<"*"<<ext<<"*"<<endl;
			f=true;  //标记已找到
			break;
		}
	}
	if(!f) cout<<"NO"<<endl;  //如果没找到
	else f=false;  //否则还原
}
```
## AC Coding

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s,s2;
bool f;
int main(){
	cin>>n;
	while(n--){
		cin>>s>>s2;
		if(s[0]==s2[0]){
			cout<<"YES"<<endl<<s[0]<<"*"<<endl;
		}
		else if(s[s.size()-1]==s2[s2.size()-1]){
			cout<<"YES"<<endl<<"*"<<s[s.size()-1]<<endl;
		}
		else{
			for(int i=0;i<s.size()-1;i++){
				string ext=s.substr(i,2);
				if(s2.find(ext)!=string::npos){
					cout<<"YES"<<endl<<"*"<<ext<<"*"<<endl;
					f=true;
					break;
				}
			}
			if(!f) cout<<"NO"<<endl;
			else f=false;
		}
	}
	return 0;
}

```

## Thanks for watching.

---

## 作者：atomic_int (赞：0)

## 题意：
题意翻译中已有。

## 分析：
设 $n=a$ 的长度 $-1$，$m=b$ 的长度 $-1$，并且从 $0$ 开始。
- 对于 $a_0=b_0$ 输出 $a_0+$`*` 即可。
- 对于 $a_n=b_m$ 输出 `*`$+a_n$ 即可。
- 否则至少需要 $a$ 和 $b$ 至少有一个相同的且长度大于 $2$ 的子串，对于这个子串（设为 $s$）输出 `*`$s$`*`。

## 代码：
```cpp
inline void solve() {
	string a, b;
	cin >> a >> b;
	int N = a.size() - 1, M = b.size() - 1;
	if (a[0] == b[0]) {
		cout << "YES\n" << a[0] << "*\n";
		return ;
	}
	if (a[N] == b[M]) {
		cout << "YES\n" << '*' << a[N] << '\n';
		return ;
	}
	for (int i = 0; i < N; i ++) {
		string temp = a.substr(i, 2);
		if (b.find(temp) != b.npos) {
			cout << "YES\n" << "*" << temp << "*\n";
			return ;
		}
	}
	cout << "NO\n";
}
```

---

## 作者：Nygglatho (赞：0)

考虑构造的字符串的最简形式，显然只有四种，分别是：

1. $\text S \texttt *$
2. $\texttt * \text S$
3. $\texttt * \text S \texttt *$
4. $\texttt * $

（$\text S$ 表示任意小写字母组成的字符串）

其中，第 1 种无论 $\text S$ 长度是多少都已经满足了条件，第 2 种也是，第 4 种则是无论如何也不满足条件。

而第 3 种如果 $\text S$ 的长度为 $1$，那么将不满足条件（因为 $\texttt * $ 的个数大于小写字母的个数），而 $\text S$ 的长度大于 $1$，就满足条件了。

假如 $\text S$ 的长度等于 $1$，且 $a$ 与 $b$ 后面还有相同的字符，那么我们可以尝试将原来构造出来的字符串变成 $\texttt * \text S \texttt * \text T \texttt * $。

此时，又会分为两种情况：
- $\text T$ 长度为 $1$
- $\text T$ 长度大于 $1$

当 $\text T$ 的长度为 $1$ 的时候，这个字符串仍然不会满足条件，而 $\text T$ 的长度大于 $1$ 的时候，我们完全可以构造这样的字符串：$\texttt * \text T \texttt * $，而不去管 $\text S$。

之后仍然同理。

所以，我们只需要判断 $a$ 和 $b$ 是否有的在最两边的相同字符，以及在中间的长度为 $2$ 的相同字符串即可。

- - -

程序设计：
1. 先判断是否可以构造第 1 种和第 2 种。
2. 遍历字符串 $a$ 和 $b$，查找长度为 $2$ 以上的相同的子串。
3. 如果找到就输出，否则，输出 $\tt NO$ 即可。

```c
#include "bits/stdc++.h"
using namespace std;
string a, b;
#define l1 a.size() - 1
#define l2 b.size() - 1

void get() {
	for (int i = 0; i < l1; ++i) {
		for (int j = 0; j < l2; ++j) {
			if (a[i] == b[j] && a[i + 1] == b[j + 1]) {
				cout << "YES\n";
				cout << '*' << a[i] << a[i + 1] << "*\n";
				return;
			}
		}
	}
	cout << "NO\n";
	return;
}

int main() {
	int T;
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> T;
	while (T--) {
		cin >> a >> b;
		if (a[0] == b[0]) {
			cout << "YES\n";
			cout << a[0] << "*\n";
		} else if (a[l1] == b[l2]) {
			cout << "YES\n";
			cout << '*' << a[l1] << '\n';
		} else get();
	}
}
```

---

