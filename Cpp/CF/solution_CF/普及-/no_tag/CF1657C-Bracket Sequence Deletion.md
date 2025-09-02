# Bracket Sequence Deletion

## 题目描述

### 题目翻译

LBW 有一个长度为 $n$ 的由括号组成的字符串，他每次要选择一个前缀并将其从字符串中删除。

这个前缀至少要满足以下两点要求：

+ 这个前缀是一个合法括号序列。
+ 此前缀是长度大于等于 $2$ 的回文串。

一直这样做，直到无法执行。

LBW 想知道最多能执行的次数与此时剩下的字符数。

## 说明/提示

$1 \le T \le 10^4$

$1 \le n \le 5 \times 10^5$

## 样例 #1

### 输入

```
5
2
()
3
())
4
((((
5
)((()
6
)((()(```

### 输出

```
1 0
1 1
2 0
1 0
1 1```

# 题解

## 作者：xh001 (赞：3)

# 题意

首先给定一个整数 $t$ 表示有 $t$ 组数据，每组数据包含一个数 $n$ 和一个长度为 $n$ 的由括号组成的字符串 $s$，每次要选择一个前缀并将其从字符串中删除。

这个前缀要满足以下两点要求：

+ 这个前缀是一个合法括号序列。
+ 此前缀是长度大于等于 $2$ 的回文串。

一直这样做，直到无法执行，求最多能执行的次数与此时剩下的字符数。
# 思路
首先进行分类讨论

当 $s_{0}$ 为 `(` 时：

若 $s_{1}$ 为 `(`，则构成了一个 `((` 的回文串。

若 $s_{1}$ 为 `)`，则构成了一个 `()` 的合法括号序列。

当 $s_{0}$ 为 `)` 时：

不可能构成合法括号序列。

到最近的那个是 `)` 的字符构成了一个形如 `)((((...((()` 的回文串，所以只要找到最近的 `)` 字符即可。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//好习惯。
ll t,n,sum;
string s; 
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--)
	{
		sum=0;
		cin>>n>>s;
		while(s.size())
		{
			if(s[0]=='(')
			{
				if(s.size()<=1) break;//删不了就退出循环。 
				s.erase(0,2);//字符串删除操作。 
				sum++;//累计答案。 
			}
			else
			{
				ll i=1;//从第二位开始找 ")"。 
				while(s[i]!=')')
				{
					i++;
					if(i>=s.size())
					{
						i=-1;
						break;
					}
				}
				if(i==-1) break;//删不了就退出循环。 
				else sum++;//累计答案。 
				s.erase(0,i+1);
			}
		}
		cout<<sum<<' '<<s.size()<<endl;
	}
	return 0;
}
```


---

## 作者：CodeMao (赞：1)

话不多说，直接上**思路**：

* 开头的第一个字符分为两种情况：

	* `(` , 这时因为后面一个字符不管是 `(` 还是 `)` 都可以构成好的字符串，如果是 `(` , 可以构成回文串；如果是 `)` , 可以构成合法括号序列；

	* `)` , 这时不可能再构成合法括号序列，所以只能构成回文串，所以只用找到后面的第一个 `)` 即可。

思路看完了，看看代码：

```cpp
#include <cstdio>
#define maxn 500005
int t,n,ans,len,p; //ans为操作数,len为被删去的字符个数
char s[maxn];
inline void in(int &a){ //快速读入
    a=0;char ch=getchar();
    while(ch<'0'||ch>'9')
        ch=getchar();
    while(ch>='0'&&ch<='9'){
        a=(a<<1)+(a<<3)+(ch^48);
        ch=getchar();
    }
}
inline void op(int a){ //快速输出
    if(a>9) op(a/10);
    putchar(a%10+'0');
}
int main(){
    in(t);
    while(t--){
        in(n);scanf("%s",s);ans=0,len=0;
        for(len=0;len<n-1;ans++) //根据思路模拟
            if(s[len]=='(') len+=2;
            else{
                p=len+1;
                while(p<n&&s[p]!=')') p++;
                if(p==n) break;
                else len=p+1;
            }
        op(ans),putchar(' '),op(n-len),puts("");
    }
    return 0;
}
```

---

## 作者：zhongcy (赞：1)

### Problem

------------

[CF Problem](https://codeforces.com/problemset/problem/1657/C)

给出一个长度为 $ n $ 的括号序列，每次从它的开头删掉一个『好的』括号序列。求出操作的最多次数以及剩下的字符数。

其中『好的』括号序列满足以下任意一点：

- 该字符串为合法括号序列
- 该字符串为回文串

### Solution

------------

每次考虑该字符串的第一个字符。

- 如果是 $ \texttt{ ( } $，则与后面字符构成的括号序列为 $ \texttt{ (( } $ 或 $ \texttt{ () } $ 均为『好的』括号序列。并且长度为 $ 2 $，满足长度最小。
- 如果是 $ \texttt{ ) } $，因为合法括号序列的第一个字符必为 $ \texttt{ ( } $，所以只能寻找回文串。根据回文串的定义，只需寻找该字符之后第一个 $ \texttt{ ) } $，这两个字符之间的字符（可能为空）均为 $ \texttt{ ( } $，因此这几个字符比构成回文串

### Code

------------

根据结论模拟即可。时间复杂度 $ \Theta (tn) $。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int t;cin>>t;
	while(t--)
	{
		int n;string s;
		cin>>n>>s;
		int i=0,ans=0,l=s.length();
		while(i<n-1)
		{
			if(s[i]=='(')
				i+=2;
			else
			{
				int pos=i+1;
				while(pos<n&&s[pos]!=')') pos++;
				if(pos==n)
					break;
				i=pos+1;
			}
			ans++;
		}
		cout<<ans<<" "<<n-i<<'\n';
	} 
	return 0;
}
```


---

## 作者：lianchanghua (赞：1)

#### 题目大意

有 $T$ 组数据，每组给你一个 $n$，表示一个全部由 `(` 和 `)` 组成的长度为 $n$ 的字符串。当此时的前缀满足以下两种条件之一时即可操作：

- 这个前缀是一个合法括号序列。

- 此前缀是长度大于等于 $2$ 的回文串。

问最多能操作多少次以及最后剩下多少个字符。

#### 思路

- 当字符为 `(` 时，有两种选择 `()` 或 `((`。

- 当字符为 `)` 时，那么，就只有一种选择 `)((` $\cdots$ `()`。

那么不就很简单了？遍历一遍，`if` 语句判断。

#### AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		int cnt=0;
		int n;
		cin>>n;
		string s;
		cin>>s;
		int i=0;
		while(i<n-1){
			if(s[i]=='(')	i+=2,cnt++;
			else{
				int j=i+1;
				while(j<n&&s[j]!=')') j++;
				if(j==n)	break;
				i=j+1;
				cnt++;
			}
		}
		cout<<cnt<<" "<<n-i<<'\n';
	} 
	return 0;
}
```

---

## 作者：nynkqh_yzp (赞：0)

考虑剩下的序列的第一个符号。

如果是 `(`，那么接下来会有两种情况 `()` 或 `((`，都可以删除。

如果是 `)`，那么肯定不会有合法的括号序列，只能是回文串，那么就去找下一个 `)`，就会出现 `)(((`……`((()` 的情况，也可以删除。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,ans,an;
char a[500001];
stack<char>q;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%s",&n,a);
		ans=0;
		an=-1;
		for(int i=0;i<n;i++){
			if(a[i]=='('){
				if(i!=n-1)
					ans++,an=i+1;
				i++;
			}
			else{
				for(i+=1;a[i]!=')'&&i<n;i++){
				}
				if(i<n)
					ans++,an=i;
			}
		}
		printf("%d %d\n",ans,n-an-1);
	}
	return 0;
}
```


---

## 作者：caibet (赞：0)

- **题意与前排提示**：

  给一个长度为 $n$ 的括号序列，每次删除满足以下条件的长度不小于 $2$ 的最短前缀序列：

  - 此前缀序列是一个合法的括号序列，如 `(()())`。
  - 此前缀序列是一个回文序列，如 `)())()`。

  求当没有满足条件的前缀序列时，已经删除了多少次，以及还剩下多少个括号。
  
  提示：这篇题解所述解法比较无脑且麻烦但较容易理解（？）

- **解法**：

  如果需要满足的条件只有是括号序列合法，就可以开一个栈，逐个读入字符并动态判断括号序列合法。
  
  对于回文序列，我们可以使用双端队列，如果双端队列首尾相同就弹首弹尾，最后通过回文序列的性质判断答案。
  
  如果栈或双端队列满足条件，还要把两者都清空。
  
  具体的细节在代码中注释。
  
    ```cpp
  	namespace{
		int T;
		const int lim=5e5+2;
		int n;
		int sum;//操作总数
		int cnt;//剩余括号数
		int siz;//目前序列长度
		char a[lim];
		stack<char> st1;
		deque<char> st2;
		void solve(){
			n=read();
			F(i,1,<=n) a[i]=readc();
			sum=0;cnt=n;siz=0;
			while(!st1.empty()) st1.pop();
			while(!st2.empty()) st2.pop_back();
			F(i,1,<=n){
				++siz;
				if(st1.size()&&a[i]==')'&&a[i]!=st1.top()){//栈顶与当前字符匹配
					st1.pop();
				}else{
					st1.push(a[i]);
				}if(st2.size()&&st2.front()==a[i]){//队头与当前字符相同，即加入后首尾相同
					st2.pop_front();
				}else{
					st2.push_back(a[i]);
				}
				while(st2.size()>1&&st2.front()==st2.back()){//可能有之前的首尾相同没有匹配
					st2.pop_back();
					st2.pop_front();
				}
				if(st1.empty()||//合法
				(siz>1&&st2.size()==1)||//长度为奇数的回文序列
				st2.empty()){//长度为偶数的回文序列
					cnt-=siz;siz=0;
					++sum;
					while(!st1.empty()) st1.pop();
					while(!st2.empty()) st2.pop_back();
				}
			}
			put("%d %d\n",sum,cnt);
		}
		void work(){
			T=read();
			while(T--) solve();
		}
	}
    ```

---

## 作者：cyrxdzj (赞：0)

### 一、思路

本题的难点在于确定每次操作删除哪个子串。其实很好确定。

如果第一个字符串为左括号，则删除的子串的长度即为 $2$。因为，如果第二个字符串为右括号，则删除的子串符合条件一（合法的括号序列）。如果第二个字符串为左括号，则删除的子串符合条件二（回文）。

如果第一个字符串为右括号，则删除的子串显然不可能符合条件一。不过，我们可以找到下一个右括号，两个右括号之间（包括两个右括号）的子串一定符合条件二（两端右括号，中间都是左括号），且长度最短。

### 二、完整代码

```cpp
#include<cstdio>
using namespace std;
int t,n;
char a[500005];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%s",&n,a+1);
		int c=0,r=n;
		int now=1;
		while(true)
		{
			if(now>=n)
			{
				break;
			}
			if(a[now]=='(')
			{
				now+=2;
				c++;
				r-=2;
			}
			else
			{
				int j=-1;
				for(int i=now+1;i<=n;i++)
				{
					if(a[i]==')')
					{
						j=i;
						break;
					}
				}
				if(j==-1)
				{
					break;
				}
				c++;
				r-=(j-now+1);
				now=j+1;
			}
		}
		printf("%d %d\n",c,r);
	}
	return 0;
}

```

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

好的现在我们面前有一个字符串 $s$。

+ 如果 $s[1]$ 为 `(`，那么它和 $s[2]$ 必定是一个可删除的子串；

+ 否则，$s[1]$ 到最近的那个是 `)` 的字符（含）是个可删除的子串。

模拟一遍即可。注意结束判断。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 500000
int t;
int n;
char s[max_n+2];
int c;
int len;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1657C_1.in","r",stdin);
	freopen("CF1657C_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		scanf("%s",s+1);
		c=0;
		len=n;
		for(int l=1,r;l<=n;){
			len=n-l+1;
			if(s[l]=='('){
				if(l<n){
					l+=2;
					++c;
					len=n-l+1;
					continue;
				}
				else{
					len=1;
					break;
				}
			}
			for(r=l+1;r<=n;++r){
				if(s[r]==')'){
					l=r+1;
					++c;
					len=n-l+1;
					break;
				}
			}
			if(r>n){
				len=n-l+1;
				break;
			}
		}
		printf("%d %d\n",c,len);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/72287803)

By **dengziyue**

---

## 作者：MeowScore (赞：0)

看到题的第一反应：完蛋，又是括号序列！

再一看：简单模拟。

题意：给出一个括号序列，每次删除**最短的**“好的前缀”。“好的前缀”定义为一段合法的前缀括号序列或者是长度不小于 $2$ 的回文前缀。求出操作次数和剩余字符数。

考虑你删除的前缀可能会长什么样：

+ `((`

+ `))`

+ `()`

+ 两个 `)` 中间夹着一段连续的 `(`。

这包含了全部情况。可以自行举例，某些看似复杂的情况经过上述判断就根本不可能出现。

比如 `()(()())((())`，我们来模拟一下删除过程。

第一次删除：`(()())((())`。删掉了`()`。

第二次删除：`)())((())`。删掉了 `((`。

第三次删除：`)((())`。删掉了 `)()`。

第四次删除：`)`。删掉了 `)((()`。

答案为 `4 1`

那么我们逐个读入字符，依据刚才讨论的前缀形式，归结出以下操作：

+ 串为空，剩余字符数计数变量加一。

+ 读入字符和字符串剩余部分的开头相同，剩余字符数计数变量清空。

+ 读入字符为 `)` 且开头字符为 `(`，剩余字符数计数变量清空。

+ 都不满足，则剩余字符数计数变量加一。

代码：

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		char head;
		cin>>head;
		int ans=0;
		int rem=1;
		for(int i=2;i<=n;i++){
			char c;
			cin>>c;
			if(!rem){//串空了，更新首位字符 
				rem++;
				head=c;
				continue;
			}
			if(head==c){//开头字符和当前字符相等，那么这一段前缀可以清空 
				rem=0;
				ans++;
				continue;
			}
			if(head=='('&&c==')'){//匹配成了（） 
				rem=0;
				ans++;
				continue;
			}
			rem++;
		}
		cout<<ans<<' ';
		cout<<rem<<endl;
	}
	return 0;
}
```






---

