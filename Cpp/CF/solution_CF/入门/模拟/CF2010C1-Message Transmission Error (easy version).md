# Message Transmission Error (easy version)

## 题目描述

这是该问题的简化版本，仅在约束条件上与困难版本不同。

在 Berland 州立大学，服务器之间的本地网络并不总是无误地运行。当连续传输两条相同的信息时，可能会发生错误，导致这两条信息合并为一条。在这种合并中，第一条信息的结尾与第二条信息的开头重叠。当然，合并只能发生在相同的字符处。合并的长度必须是一个大于零且小于信息文本长度的正整数。

例如，当连续传输两条消息 "abrakadabra" 时，可能会发生上述类型的错误，导致收到的消息变为 "abrakadabrabrakadabra" 或 "abrakadabrakadabra"（在第一种情况下，合并发生在一个字符处，第二种情况下发生在四个字符处）。

给定收到的消息 $t$，判断它是否可能是本地网络运行中上述类型错误的结果。如果是，请给出一个可能的 $s$ 的值。

两条消息完全重叠的情况不应被视为错误。例如，如果收到的消息是 "abcd"，应认为其中没有错误。同样，仅仅将一条消息简单地接在另一条消息后面也不算错误。例如，如果收到的消息是 "abcabc"，也应认为其中没有错误。

## 说明/提示

在第二个示例中，一个合适的答案也可以是字符串 "acacaca"。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
abrakadabrabrakadabra```

### 输出

```
YES
abrakadabra```

## 样例 #2

### 输入

```
acacacaca```

### 输出

```
YES
acaca```

## 样例 #3

### 输入

```
abcabc```

### 输出

```
NO```

## 样例 #4

### 输入

```
abababab```

### 输出

```
YES
ababab```

## 样例 #5

### 输入

```
tatbt```

### 输出

```
NO```

# 题解

## 作者：lxyz (赞：4)

## 题目大意
输入一个字符串，如果它是由一个字符串和它本身重叠而成，则输出``YES``和那个字符串，否则输出 ``NO`` ，如有多解，输出任意解即可。  
## 思路
因为题目范围较小，可以直接暴力字符串的长度，然后再判断是否符合。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
string t;
int n,m;
int main(){
	cin>>t;
	m=t.size();
	n=m/2;
	while(n<m-1){
		n++;
		string a="",b=""; 
		for(int i=0;i<n;i++) a+=t[i];
		for(int i=m-n;i<m;i++) b+=t[i];
		if(a==b){ 
			cout<<"YES\n"<<a<<"\n";
			return 0;
		}
	}
	cout<<"NO\n";
	
	return 0; 
}
```

---

## 作者：abc1856896 (赞：2)

水题。建议降橙。

# Solution

显然可以直接暴力字符串的长度，再判断前后是否相等。但这样的时间复杂度是 $O(n^2)$。

瓶颈在判断相等，上哈希判断即可。

---

## 作者：qiutian120529 (赞：2)

## 0x01 题意
给定一个字符串，求出一个字符串同时为它的前缀和后缀。

## 0x02 思路
暴力枚举要求的字符串长度，然后求出字符串 $s$ 的符合长度的前后缀，判断是是否相等，是则输出 `YES` 和前（后）缀。最后还如果没有答案，则输出 `NO`。

## 0x03 Code
```cpp
#include<bits/stdc++.h> 
using namespace std;

string s;

int main(){
	cin >> s;
	for(int i = s.size() / 2 + 1; i < s.size(); i++){//枚举长度 
		string sa = "", sb = "";//初始化 
		for(int j = 0; j < i; j++){//统计前缀 
			sa += s[j];
		}
		for(int j = 0; j < i; j++){//统计后缀 
			sb += s[s.size() - 1 - j];
		}
		reverse(sb.begin(), sb.end());//后缀翻转 
		if(sa == sb){//判断是否相等 
			cout << "YES\n" << sa;
			return 0;
		}
	}
	cout << "NO";//无答案情况 
	return 0; 
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

枚举重合长度 $i\in[1,n)$，原串长应为 $m=\dfrac{n+i}{2}$，取出给定串的区间 $[1,m]$ 与区间 $[n-m+1,n]$ 进行比较，若相等则 $[1,m]$ 就是原串。找不到则无解。

---

## 作者：maoziming (赞：1)

## 题目大意
输入一个字符串，如果他是一个字符串重叠而成，则输出   `YES` ，并输出那个重叠的字符串，若无解输出 `NO` 。如果有多解输出其中一解即可。

## 思路
由于题目范围很小所以可以暴力枚举字符串的长度 $len$ ，并且通过字符串的长度可以获得字符串中的第一个长度为 $len$ 的子串，以及最后一个长度为 $len$ 的子串。由于是是子串重叠，所以只需要判断这两个字符串即可。

## Code

``` cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main()
{
	cin>>s;
	int len=s.size();//获取s的长度
	for(int t=1;t<len;t++)//枚举 
	{
		string x="",y="";//定义两个空串以备后面存储
		if((len+t)%2==0) //判断长度是否符合条件
		{
			for(int i=0;i<(len+i)/2;i++)//存储第一个字符串
			{
				x+=s[i];
			} 
			for(int i=len-(len+i)/2;i<len;i++)//存储第二个字符串
			{
				y+=s[i];
			}
			if(x==y)//如果相同就输出
			{
				cout<<"YES\n"<<x;//输出YES并输出其中一个字符串
				return 0;//有解后退出 
			} 
		}
	}
	cout<<"NO";//没有解就输出NO 
	return 0;
}
```

---

## 作者：wuyouawa (赞：1)

### 形式化题意

给定一个字符串 $s$，找出一个子串，使它前面的字符串与它重合后的字符串与它与它后面的字符串重合后的字符串相同，如无解，输出```NO```，如有多解，输出任意解。

### 思路

这题的 $s$ 的长度 $\le 100$，所以可以暴力枚举重合长度，而两个字符串的长度和就是重合长度+ $s$ 的总长度又因为两个字符串的长度是相等的，直接用长度和 $/2$ 就可得出字符串的长度，这样就可以得出两个字符串了，判断相等就直接输出。如果一直没输出就是无解。

### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
string s, f, l, ans;
int n;
int main() {
	cin >> s;
	n = s.size();
	for (int i = 1; i < n; i++) {
		if ((n + i) % 2 == 0)//只有n+i为2的倍数数时长度才为整数 {
			f = "";
			l = "";//要清空
			for (int j = 0; j < (n + i) / 2; j++) {
				f += s[j];//第一个字符串
			}
			for (int j = n - (n + i) / 2; j < n; j++) {
				l += s[j];//第二个字符串
			}
			if (f == l) {//如果相等直接输出
				cout << "YES\n" << f;
				return 0;
			}
		}

	}
	cout << "NO\n";//没找到就输出NO
	return 0;
}
```

---

## 作者：songhongying (赞：1)

## 题目大意：
给定一个字符串 $s$。是否存在字符串 $t$ 既是 $s$ 的前缀，又是 $s$ 的后缀，且 $t$ 的长度大于 $s$ 的一半。

## 解题思路：
可以枚举此字符串的长度，但在此之前，需要先判断此字符串长度能否平均分成两份，如果可以，将此字符串分成两份，将每份均变成一个新的字符串，如果这两个字符串完全相同，则输出成立，并输出其中任意一个字符串，如果将所有的可能都枚举后，依旧没有成立的，则输出不成立。

## Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main() {

	cin >> s;
	int len = s.size();
	for (int i = 1; i < len; i++) {
		string q = "", w = "";
		if ((len + i) % 2 == 0) {//此长度符合条件
			for (int j = 0; j < (len + i) / 2; j++) {//前面的字符串
				q += s[j];
			}
			for (int j = len - (len + i) / 2; j < len; j++) {//后面的字符串
				w += s[j];
			}
			if (q == w) {//前后字符串相同
				cout << "YES" << endl << q;
				return 0;
			}
		}
	}
	cout << "NO";

	return 0;
}
```

---

## 作者：Life_Game (赞：0)

如果整个字符串的 Border 不能重叠的话，那么说明不是错误的。   
否则直接输出重叠的 Border 部分即可。
```cpp
#include<bits/stdc++.h>
#define MAXN 1000010
using namespace std;
int kmp[MAXN];
int la,lb,j; 
string b;
int main(){
    cin>>b;
    b=" "+b;
    lb=b.size()-1;
    for (int i=2;i<=lb;i++){     
	   while(j&&b[i]!=b[j+1])
            j=kmp[j];    
       if(b[j+1]==b[i])j++;    
        kmp[i]=j;
       }
    if(kmp[lb]<=lb/2){
     	cout<<"NO";
	 }
	else{
	 	cout<<"YES"<<'\n';
	 	for(int i=1;i<=kmp[lb];i++)	cout<<b[i];
	}
    return 0;
}
```

---

## 作者：MingRi_Doctor (赞：0)

## 思路:
本题数据范围很小，直接暴力枚举 $t$ 的前缀和后缀即可（详见代码解释）。
## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s; 
int q;//来记录t的最小长度
int main(){
	cin>>s;
	if(s.size()%2==0) q=s.size()/2;// 求出t的最小长度
	else q=s.size()/2+1;
	for(int i=q;i<=s.size();i++)
	{
		string t1,t2;//t的前缀和后缀
		for(int j=0;j<i;j++) t1+=s[j];//t的前缀
		for(int j=s.size()-1;j>=s.size()-i;j--) t2+=s[j];//t的后缀
		if(t1==t2)//判断前后缀是否相等
		{
			cout<<"YES\n"<<t1;//如果是输出 YES 和 t
			return 0; 
		}
	} 
	cout<<"NO\n";//如果枚举了所有长度都不行，就输出NO
	return 0;
}
```

---

## 作者：cly312 (赞：0)

先用 KMP 求出 $t$ 的最长公共前后缀长度，设 $t$ 的最长公共前后缀长度为 $k$，如果 $2\cdot k$ 大于 $t$ 的长度，那么 $t$ 中就有错误，原串就是从 $t$ 的最长公共前后缀。

证明：如果 $2\cdot k$ 大于 $t$ 的长度，那么就说明 $t$ 的最长公共前后缀有相交的部分，那么相交处就为原串发生合并的地方，原串也就是从 $t$ 的最长公共前后缀。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int nxt[400000];
int main(){
	int n,i,j;
	cin>>s;
	n=s.length();
	nxt[0]=0;
	j=0;
	for(i=1;i<n;i++){
		while(j>0&&s[i]!=s[j])j=nxt[j-1];
		if(s[i]==s[j])j++;
		nxt[i]=j;
	}
	if(nxt[n-1]*2>n)
		cout<<"YES\n"<<s.substr(0,nxt[n-1])<<'\n';
	else cout<<"NO\n";
	return 0;
}
```

---

