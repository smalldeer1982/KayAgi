# [GCJ 2022 #1A] Double or One Thing

## 题目描述

给定一个由大写英文字母组成的字符串。你可以选择高亮其中任意数量的字母（可以是全部、部分或不选）。被高亮的字母不需要是连续的。然后，通过从左到右处理字母生成一个新字符串：未高亮的字母在新字符串中只出现一次，而被高亮的字母会重复出现两次。

![](https://cdn.luogu.com.cn/upload/image_hosting/q5ybwo42.png)

例如，初始字符串为 HELLOWORLD 时，你可以高亮 H、第一个和最后一个 L 以及最后一个 O，得到：HELLOWORLD $\Rightarrow$ HHELLLOWOORLLD。类似地，如果什么都不高亮，得到的是原字符串 HELLOWORLD；如果全部高亮，则得到 HHEELLLLOOWWOORRLLDD。注意：相同的字母可以独立选择是否高亮。

对于一个给定的字符串，根据高亮选择的不同，可以生成多种不同的结果字符串。在所有可能的生成字符串中，输出按字典序排列最靠前的一个。

注：若字符串 $s$ 是字符串 $t$ 的前缀，或者 $s$ 和 $t$ 在第一个不同字符处 $s$ 的字母在字母表中更靠前，则认为 $s$ 在字典序中排在 $t$ 之前。例如以下字符串按字典序排列为：CODE, HELLO, HI, HIM, HOME, JAM。

## 说明/提示

**样例解释**

在样例 #1 中，所有可能的生成字符串按字典序排列为：PEEEEL, PEEEELL, PEEEL, PEEELL, PEEL, PEELL, PPEEEEL, PPEEEELL, PPEEEL, PPEEELL, PPEEL 和 PPEELL。

在样例 #2 中，所有可能的生成字符串都只包含字母 A，其中最短的字符串字典序最靠前，因为它是其他所有字符串的前缀。

在样例 #3 中，从 CODEJAMDAY 可以生成 1024 种不同的字符串，其中 CCODDEEJAAMDAAY 是字典序最小的一个。

**限制条件**

- $1 \leq \mathbf{T} \leq 100$。
- 字符串 $\mathbf{S}$ 中的每个字符都是大写英文字母。

**测试集 1（10 分，可见评测结果）**

- $1 \leq$ 字符串 $\mathbf{S}$ 的长度 $\leq 10$。

**测试集 2（15 分，隐藏评测结果）**

- $1 \leq$ 字符串 $\mathbf{S}$ 的长度 $\leq 100$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
PEEL
AAAAAAAAAA
CODEJAMDAY```

### 输出

```
Case #1: PEEEEL
Case #2: AAAAAAAAAA
Case #3: CCODDEEJAAMDAAY```

# 题解

## 作者：wzbwzbwzb6 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P12984)
## 核心思路
题目要求在所有可能的生成字符串中，输出按字典序排列最靠前的一个。所以我们可以分以下两种情况进行讨论：
- 如果当前字符的字典序小于后面的字符，那么若高亮当前字符，一定会让字符串的字典序变小，所以重复当前字符。
- 如果当前字符等于后面的字符，那么建立一个用于记录位置的变量 $p$ 初始化为当前字符的位置加 2。用一个循环从 $p$ 向后遍历寻找与当前字符不同的字符。如果找到的字符大于当前字符，就重复当前字符。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int len;
//solve() 函数用于处理字符串。 
void solve(string x)
{
	int p;   //用于查找相同两个字符后的第一个不同字符。 
    for(int i = 0;i < len-1;i++)
	{
		if(x[i]<x[i+1])cout<<x[i];
		if(x[i]==x[i+1])     //连续多个相同字符的情况。 
		{
		    p=i+2;
			//跳过相同字符。 
			while(x[i]==x[p]) p++;	
			if(x[p]>x[i]) cout<<x[i];
		}
		cout<<x[i];
	}	
    cout<<x[len-1]<<endl;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t;
	cin>>t;
	for(int i = 1;i <= t;i++)
	{
		string s;
		cin>>s;
		cout<<"Case #"<<i<<": ";
		len = s.length();
		solve (s);       //调用处理函数。 
	}
	return 0;
}
```

---

## 作者：_____1__2___ (赞：2)

# 题解：P12984 [GCJ 2022 #1A] Double or One Thing

这道题要求字典序要最小，其实就是要高亮越小的字母越好，如果一个字母比他后一个字母还小，那高亮这个字母后的字典序一定比原来的小，因为高亮的字母顶替了后一个字母，获得了更小的字典序。同理如果前一个字母比后一个字母大，那么就不能高亮，直接输出。

那如果一个字母等于他后面的字母，我们需要往后看，判断第一个不等于这个字母的字母，如果比前面的字母大，说明前面那一些相等字母全部都要复制，否则就不复制。

所以，代码实现如下。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
	int T;
	cin >> T;
	for (int i=1;i<=T;i++) {
		string s;
		cin >> s;
		int len=s.size()-1;
		cout << "Case #" << i << ": ";
		for (int j=0;j<len;j++) {
			if (s[j]<s[j+1]) cout << s[j];
			if (s[j]==s[j+1]) {
				int k=j;
				while (s[k]==s[j]) k++;
				if (s[k]>s[j]) {
					cout << s[j];
				}
			}
			cout << s[j];
		}
		cout << s[len];
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：TFX_Y (赞：2)

## 思路

题目要求我们输出按字典序排列最靠前的一个字符串。

我们可以遍历每个字符串 $s$ 中的每个字符，当第一个和当前字符不同的字符的字典序大于当前字符时，可以使字符串字典序靠前，例如这个字符串：


```
EEL
```
当遍历到 $E$ 时，发现存在一个和当前字符不同的字符 $L$，因此选择高亮 $E$，因为添加一个 $E$ 之后，$L$ 之前的字符（同样是 $E$）会代替 $L$ 的位置，使字典序更小。

当不存在和当前字符不同的字符的字典序大于当前字符时，因为字符串越短，字典序越小，所以并不高亮。

我们可以用一个 $lst$ 来记录第一个和当前字符不同的字符的位置，并和当前字符比较，可行就再添加当前字符。最后别忘了加上最后一个字符，然后输出。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
string s;
string solve(){
	int len=s.length(),lst=0;
	string ans;
	for(int i=0;i<len-1;i++){
		while(s[lst]==s[i]) lst++;
		if(s[i]-'0'<s[lst]-'0') ans+=s[i];
		ans+=s[i];
	}
	return ans+s[len-1];
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	for(int k=1;k<=t;k++){
		cin>>s;
		cout<<"Case #"<<k<<": "<<solve()<<"\n";
	}
	return 0;
} 
```

---

## 作者：tujiaqi12 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P12984)

# 思路
### 先假设相邻字符不同
若出现 AB 的情况，将 A 高亮，将 B 后移，即可使字典序变小，也就是 AAB。
所以，判断一个字母是否需要高亮，只需要比较它与后一个字符的字典序大小，若前一个字母小，则将其高亮。
#### 拿样例的第三个字符串举个例子：


|正在遍历的元素|下一元素|是否高亮|结果|
|:-:|:-:|:-:|:-:|
|C|O|1|CC|
|O|D|0|CCO|
|D|E|1|CCODD|
|E|J|1|CCODDEE|
|J|A|0|CCODDEEJ|
|A|M|1|CCODDEEJAA|
|M|D|0|CCODDEEJAAM|
|D|A|0|CCODDEEJAAMD|
|A|Y|1|CCODDEEJAAMDAA|
|Y|NULL|0|CCODDEEJAAMDAAY|

### 现假设相邻字符可相同
可以将相邻的相同字母打包成一组，打包后相邻每一组字符种类一定不同，接下来的操作方法与之前类似：

将一组的字典序与下一组作比较，若其字典序更小，则整组全部高亮，否则全部不高亮。

#### 举个例子，例如：AABBBCDDB。


|正在遍历的元素|下一组|是否高亮|结果|
|:-:|:-:|:-:|:-:|
|AA|BBB|1|AAAA|
|BBB|C|1|AAAABBBBBB|
|C|DD|1|AAAABBBBBBCC|
|DD|B|0|AAAABBBBBBCCDD|
|B|NULL|0|AAAABBBBBBCCDDB|

# 代码
#### 详尽注释版

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct info{
	char c;//元素种类 
	ll v;//元素个数 
}a[105];//打包 
ll t;
char s[105];
ll n;//目前组数 
int main(){
	scanf("%lld",&t);
	for(ll i = 1;i <= t;i++){
		n = 0;
		scanf("%s",s+1);
		ll l = strlen(s+1);
		for(ll j = 1;j <= l;j++){
			if(s[j] == a[n].c){//与之前字符种类相同 
				a[n].v++;//最后一组的元素个数增加 
			}
			else{
				a[++n].c = s[j];//最后一组的元素种类设定 
				a[n].v = 1;//最后一组的元素个数设为1
			}
		}
		a[n+1].c = 0;
		printf("Case #%lld: ",i);//注意格式 
		for(ll i = 1;i <= n;i++){
			if(a[i].c > a[i+1].c){//字典序更大 
				for(ll j = 1;j <= a[i].v;j++){
					printf("%c",a[i].c);
				}
			}
			else{//字典序更大
				for(ll j = 1;j <= a[i].v*2;j++){
					printf("%c",a[i].c);//双倍输出 
				}
			}
		}
		printf("\n");//别忘记换行 
	}
	return 0;
}
```

#### 无注释版
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct info{
	char c;
	ll v;
}a[105];
ll t;
char s[105];
ll n;
int main(){
	scanf("%lld",&t);
	for(ll i = 1;i <= t;i++){
		n = 0;
		scanf("%s",s+1);
		ll l = strlen(s+1);
		for(ll j = 1;j <= l;j++){
			if(s[j] == a[n].c){
				a[n].v++;
			}
			else{
				a[++n].c = s[j];
				a[n].v = 1;
			}
		}
		a[n+1].c = 0;
		printf("Case #%lld: ",i);
		for(ll i = 1;i <= n;i++){
			if(a[i].c > a[i+1].c){
				for(ll j = 1;j <= a[i].v;j++){
					printf("%c",a[i].c);
				}
			}
			else{
				for(ll j = 1;j <= a[i].v*2;j++){
					printf("%c",a[i].c);
				}
			}
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：ELSIA (赞：1)

# 思路
题目要求字典序要最小，就是被高亮的字越小越好。如果前一个字母比后一个字母小，那么就高亮这个字母；如果如果前一个字母比后一个字母大，就不高亮这个字母，直接输出就行。还有一种情况，就是前一个字母等于后一个字母，那就看后面的字母是否大于前一个字母，如果大于就复制前一个字母，如果小于就不复制。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	long long n;
	cin >> n;
	long long ans = 0;
	while(n--){
		ans++;
		string s;
		cin >> s;
		long long len_s = s.size();
		cout << "Case #" << ans << ": " ;
		for(int i = 0 ; i < len_s ; i++){
			if(int(s[i]) < int(s[i+1])){
				cout << s[i]; //小于的情况
			}else{
				if(s[i] == s[i+1]){ //等于的情况
					long long a = i;
					for(; s[i] == s[a] ; a++)
					if(s[a+1] > s[i])
						cout << s[i];
				}
			}
			cout << s[i];
		}
		cout << endl; //记得换行
	}
	return 0; //华丽结束
}
```
如果感到这篇题解对你有用，不妨点个赞谢谢 。

---

## 作者：lizihan15550390562 (赞：1)

# 题目简述
输入一个字符串 $s$，我们可以使得其中的某一个字符双写，也可以不双写，求出经过一系列操作后，字典序最小的字符串。
# 解题思路
### 贪心！

倒序判断：把 $b$ 当做目标字符串，如果添加后字典序减小，那么双写（即当 $S_i<S_{i+1}$ 时，双写 $S_i$）。

### 代码一
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin>>T;
	for(int u=1;u<=T;u++){
		string S;
		cin>>S;
		printf("Case #%d: ",u);
		string b;
		for(int i=S.size()-1;i>=0;i--){
			b+=S[i];
			if(S[i]<=S[i+1]) b+=S[i];
		}
		for(int i=b.size()-1;i>=0;i--) cout<<b[i];
		cout<<endl;
	}
	return 0;
} 
```
**Stop！**  
先别着急抄，如果你仔细观察，就会发现：
```
样例输入：ABC
我们输出：AABBCC
正确输出：AABBC
```
是的，我们没有考虑最后的情况，这样会使字符串过长，从而达不到我们的目的。
### 修改代码 2

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin>>T;
	for(int u=1;u<=T;u++){
		string S;
		bool k=false;
		cin>>S;
		printf("Case #%d: ",u);
		string b;
		for(int i=S.size()-1;i>=0;i--){
			b+=S[i];
			if(S[i]<=S[i+1] && i!=S.size()) b+=S[i];
		}
		for(int i=b.size()-1;i>=0;i--) cout<<b[i];
		cout<<endl;
	}
	return 0;
} 
```
等等，还没完，仔细看样例 2，就会发现：
```
样例输入：AAAAAAAAAA
我们输出：AAAAAAAAAAAAAAAAAAA
正确输出：AAAAAAAAAA
```
我们没有考虑尾部重复的情况……
### 修改代码 3

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin>>T;
	for(int u=1;u<=T;u++){
		string S;
		bool k=false;
		cin>>S;
		printf("Case #%d: ",u);
		string b;
		for(int i=S.size()-1;i>=0;i--){
			b+=S[i];
			if(S[i]<=S[i+1] && i!=S.size() && k==true) b+=S[i];
			else if(S[i]!=S[i-1]) k=true;
		}
		for(int i=b.size()-1;i>=0;i--) cout<<b[i];
		cout<<endl;
	}
	return 0;
} 
```
不要着急！还没有完。
还有最后一种情况没有考虑。
```
样例输入：ABBA
我们输出：AABBBA
正确输出：AABBA
```
是的，这是最后一遍了，还有中间这个地方延长可能会导致原本大的字符的原位置会被小一点的重复字符替代。
# 第一百行——AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin>>T;
	for(int u=1;u<=T;u++){
		string S;
		bool k=false;
		cin>>S;
		printf("Case #%d: ",u);
		string b;
		for(int i=S.size()-1;i>=0;i--){
			b+=S[i];
			if(S[i]<=S[i+1] && i!=S.size() && k==true) b+=S[i];
			else if(S[i]!=S[i-1]) k=true;
			if(S[i]==S[i-1] && S[i]>S[i+1]) k=false;
		}
		for(int i=b.size()-1;i>=0;i--) cout<<b[i];
		cout<<endl;
	}
	return 0;
} 
```

---

## 作者：xtzhangziche (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P12984)

## 思路
首先，我们看，要让字典序最小，也就是高亮的字母最小。

然后，题目说，被高亮的字母会重复出现两次，也就是如果高亮就重复输出两次被高亮的字母。

所以，只用两种情况来判断 $s_i$ 是否需要高亮（多输出一次）：

1. 如果 $s_i < s_{i+1}$，就输出一次 $s_i$。

2. 如果 $s_i = s_{i+1}$，就从 $i+2$ 开始，遍历字符串 $s$ 中不等于 $s_i$ 的字母，如果那个字母大于 $s_i$，就输出一次 $s_i$。

还有，不管 $s_i$ 有没有高亮，都需要先输出一次 $s_i$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,t;
string s;
int main(){
    cin>>T;
    while(T--)
    {
        cin>>s;
        cout<<"Case #"<<++t<<": ";
        int len=s.size()-1;
        for(int i=0;i<len;i++)
        {
            cout<<s[i];
            if(s[i]<s[i+1]) cout<<s[i];
            if(s[i]==s[i+1])
            {
                int x=i+2;
                while(s[i]==s[x]) x++;
                if(s[x]>s[i]) cout<<s[i];
            }
        }
        cout<<s[len]<<'\n';
    }
    return 0;
}
```

---

## 作者：jsisonx (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P12984)

# 题目分析

想让字典序最小，只需遵循下面这个规则：字典序小的字母尽量放在前面，字母一样时字符串长度尽量小。

遵循这两个规则，考虑每个字母是否需要重复（设字符串为 $S$）：

- 若 $S_i<S_{i+1}$，则 $S_i$ 需要重复，因为无论如何 $S_{i+1}$ 由原来的较大字母变成了 $S_i$ 这个较小字母，根据规则第一条可知 $S_i$ 需要重复。
- 若 $S_i=S_{i+1}$，则需要考虑从 $S_i$ 以后第一个与 $S_i$ 不同的字符（设为 $S_j$）与 $S_i$ 的大小关系。具体地，若 $S_i<S_j$，则 $S_i$ 要重复，否则不重复。这是因为如果 $S_i<S_j$，则 $S_i$ 重复后 $S_{i+1}$ 到 $S_{j-1}$ 间的所有字符向后移一个位置，从而 $S_j$ 变为更小的 $S_{j-1}$，即 $S_i$。
- 若 $S_i=S_{i+1}$，则一定不重复。

# 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
char c[205];
int main(){
	int t;
	cin>>t;
	for(int o=1;o<=t;o++){
		cout<<"Case #"<<o<<": ";
		cin>>c;
		int len=strlen(c);
		for(int i=0;i<len-1;i++){
			cout<<c[i];
			if(c[i]<c[i+1]){
				cout<<c[i];
			}
			else if(c[i]==c[i+1]){
				int k=-1;
				for(int j=i+1;j<len;j++){
					if(c[j]!=c[i]){
						k=j;
						break;
					}
				}
				if(k!=-1&&c[i]<c[k]){
					cout<<c[i];
				}
			}
		}
		cout<<c[len-1]<<endl;
	}
	return 0;
}
```

---

