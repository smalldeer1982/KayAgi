# Email from Polycarp

## 题目描述

Methodius received an email from his friend Polycarp. However, Polycarp's keyboard is broken, so pressing a key on it once may cause the corresponding symbol to appear more than once (if you press a key on a regular keyboard, it prints exactly one symbol).

For example, as a result of typing the word "hello", the following words could be printed: "hello", "hhhhello", "hheeeellllooo", but the following could not be printed: "hell", "helo", "hhllllooo".

Note, that when you press a key, the corresponding symbol must appear (possibly, more than once). The keyboard is broken in a random manner, it means that pressing the same key you can get the different number of letters in the result.

For each word in the letter, Methodius has guessed what word Polycarp actually wanted to write, but he is not sure about it, so he asks you to help him.

You are given a list of pairs of words. For each pair, determine if the second word could be printed by typing the first one on Polycarp's keyboard.

## 样例 #1

### 输入

```
4
hello
hello
hello
helloo
hello
hlllloo
hello
helo
```

### 输出

```
YES
YES
NO
NO
```

## 样例 #2

### 输入

```
5
aa
bb
codeforces
codeforce
polycarp
poolycarpp
aaaa
aaaab
abcdefghijklmnopqrstuvwxyz
zabcdefghijklmnopqrstuvwxyz
```

### 输出

```
NO
NO
YES
NO
NO
```

# 题解

## 作者：Lovely_Elaina (赞：7)

双指针切了，为啥要用结构体啊。

我们把同学打的记为 $a$，wqy 打的记为 $b$。用 $i$ 遍历 $a$，用 $j$ 遍历 $b$。

- $a_i\neq b_j$，不匹配；
- 循环判断 $a_{i+1} = a_i$ 并且 $a_{i+1}\neq b_j$，则 $i$ 自增，$j$ 不变；
- 然后 $i$ 和 $j$ 同时自增。

```cpp
#include <bits/stdc++.h>
// #define int long long
#define endl '\n'
using namespace std;

string s1,s2;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(NULL); 
    
    int T;
    cin >> T;
    while(T--){
        cin >> s2 >> s1;

        bool b = 1;

        int i,j;
        i = j = 0;

        int l1,l2;
        l1 = s1.size();
        l2 = s2.size();
        while(i <= l1 && j <= l2){
            if(s1[i] != s2[j]){
                b = 0;
                break;
            }

            while(s1[i+1] == s1[i] && s2[j+1] != s1[i])
                i++;

            i++,j++;
        }

        if(b) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
```

---

## 作者：追梦之鲸 (赞：5)

[Link](https://www.luogu.com.cn/problem/CF1185B)

#### 思路

题面说邮件中出现的单词中的字母会被重复，那么我们就把一段重复的字符串化成一个字母 $x$（表示重复的字母是什么）和一个数字 $y$（表示重复了多少次），就像这样 $aaaaa→x\!=\!a\ y\!=\!5$ 这样。那么我们就可以把邮件中出现的单词化成一个结构体数组 $A$。

然后我们还需按照上面的方法把 wqy 猜的单词化成一个结构体数组 $B$，这样有两个好处，一是便于比较，二是防止像 $aaaa\ aaa$ 这样的数据。

最后就开始比较了，首先比较两个结构体数组的长度，如果长度不一，那么肯定是错的。然后挨个比较 $A_{i.x}$ 和 $B_{i.x}$ 是否一样，还有 $A_{i.y}$ 是否小于 $B_{i.y}$。如果不是那么就是错的。

最后要注意把结构体数组长度清零。


#### Code：
```c
#include<bits/stdc++.h> 
using namespace std;
char hc;
template <class O>
inline void read(O &ie){hc=getchar();ie=0;for(;!isdigit(hc);hc=getchar());for(;isdigit(hc);hc=getchar())ie=ie*10+(hc^48);return;}
const int MAX=1e+9;
const int N=1e+6+10;
struct uer{
	int	y;char x;
}a[N],b[N];
signed main(){
	register bool tag;
	register int top,toq,t,n,m;
	register char c;
	read(t);
	while(t--){
		tag=false;
		top=1;toq=1;
		while(c<'a'||c>'z')c=getchar();
		a[1].x=c;
		a[1].y=1;
		for(;c<='z'&&c>='a';c=getchar()){
			if(a[top].x==c){
				a[top].y++;
			}else{
				a[++top].x=c;
				a[top].y=1;
			}
		}
		while(c<'a'||c>'z')c=getchar();
		b[1].x=c;
		b[1].y=1;
		for(;c<='z'&&c>='a';c=getchar()){
			if(b[toq].x==c){
				b[toq].y++;
			}else{
				b[++toq].x=c;
				b[toq].y=1;
			}
		}if(toq!=top){
			printf("NO\n");
			continue;
		}for(register int i=1;i<=top;i++){
			if(a[i].x!=b[i].x||a[i].y>b[i].y){
				printf("NO\n");
				tag=true;
				break;
			}
		}if(!tag)printf("YES\n");
	}
	return 0;
}
```

---

## 作者：C20210404杜铖昊 (赞：2)

根据题意：

我们就去键盘出错的几个字符跳过就可以了

有几个可以直接判定"NO"的条件

1.猜测的字符串长度大于屏幕上字符串的长度

2.猜测的字符串的第一个字符与屏幕上字符串的第一个字符不同

3.猜测的字符串的最后一个字符与屏幕上字符串的最后一个字符不同

code:
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
string s,s1;
int t;
int main(){
	scanf("%d",&t);
	for(int k = 1;k <= t;++k){
		int flag = 1;
		cin>>s>>s1;
		int i = 0,j = 0;
		if(s.length() > s1.length() or s[0] != s1[0] or s[s.length()-1] != s1[s1.length()-1]) flag = 0;
		for(i = 0;i < s.length();++i){
			if(s[i] == s[i+1]  and s[i] == s1[j]){
				j++;
				continue;
			}
			if(s[i] != s1[j]){//输出"NO"的条件 
				flag = 0;
				break;
			}
			else {
				while(s[i] == s1[j]) j++;//改变j的位置
			}
		}
		if(!flag or i != s.length() or j != s1.length()) printf("NO\n");//i或者j没到都是中途推出的,所以要输出"NO" 
		else printf("YES\n");
	}
	return 0;
}
```

---

## 作者：Big_Dinosaur (赞：1)

### 本题思路
首先，读入两个字符串 $s1,s2$，求出它们的长度，记为 $l1,l2$。

然后，定义结构体，包括两个参数 $len$ 和 $ch$，表示在字符串内，$ch$ 连续出现了 $len$ 次。

接下来，定义该结构体类型的数组 $a$ 和 $b$，然后将 $s1$ 和 $s2$ 用该方法放进这两个数组，即将连续相同字母归为一组放入数组元素，并将其长度记为 $su1$ 和 $su2$。

如果 $su1\ne su2$，则视为连通块数量不同，输出 $\texttt{NO}$，并进入下一轮循环。接下来，同时遍历两个数组，如果 $a_i$ 的 $ch$ 和 $b_i$ 的 $ch$ 不同，或者 $a_i$ 的 $len$ 比 $b_i$ 的 $len$ 大（即为样例中 $\texttt{hello}$ 和 $\texttt{helo}$ 的那一组），也要输出 $\texttt{NO}$，进入下一轮循环。

如果遍历完了，输出 $\texttt{YES}$ 并进入下一轮循环。

### AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s1,s2;
int n,a1,a2,l1,l2,t,su1,su2;
char c1,c2;
struct lx{int len;char ch;}a[1010000],b[1010000];
bool p(string s1,string s2){//判断
a1=a2=t=1;su1=su2=0;
l1=s1.size(),l2=s2.size();
c1=s1[0],c2=s2[0];
while(a1<l1){
if(s1[a1]==c1)++t;
else{a[++su1].ch=c1;a[su1].len=t;t=1;c1=s1[a1];}
++a1;
}
a[++su1].ch=c1;a[su1].len=t;t=1;//最后一组
while(a2<l2){
if(s2[a2]==c2)++t;
else{b[++su2].ch=c2;b[su2].len=t;t=1;c2=s2[a2];}
++a2;
}
b[++su2].ch=c2;b[su2].len=t;//最后一组
if(su1!=su2)return 0;//对数不等
for(int i=1;i<=su1;++i){
	if(a[i].ch!=b[i].ch||a[i].len>b[i].len)
    return 0;//字符不等或长度不对
}
return 1;
}
main(){
std::ios::sync_with_stdio(false);std::cin.tie(0);//优化
cin>>n;while(n--){
cin>>s1>>s2;
if(p(s1,s2))puts("YES");else puts("NO");
}
}
```

---

## 作者：cff_0102 (赞：0)

这道题第一眼就是用双指针。

用 $i$ 遍历猜测的字符串（$a$），用 $j$ 遍历打出来的字符串（$b$），记 $n,m$ 分别为 $a,b$ 的长度。

一直重复做下面的事情：先判断 $a_i$ 和 $b_j$ 是否相等（不相等直接输出 `NO`，或者如果此时 $i=n$ 但 $j\ne m$ 或 $i\ne n$ 但 $j=m$ 也输出 `NO`），然后相等就将 $i+1$，$j+1$，如果此时 $a_i$ 不等于 $b_j$，就一直将 $j+1$ 直到 $b_j\ne b_{j-1}$，进入下一个循环。如果此时 $i=n,j=m$，就退出循环输出 `YES`。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int t;cin>>t;while(t--){
		string a,b;cin>>a>>b;
		int n=a.length(),m=b.length();
		int i=0,j=0;
		bool f=1;
		while(1){
			if(a[i]!=b[j]){
				cout<<"NO\n";
				f=0;
				break;
			}
			if(i==n&&j!=m||i!=n&&j==m){
				cout<<"NO\n";
				f=0;
				break;
			}
			i++,j++;
			if((a[i]!=b[j]||i==n)&&j!=m){
				while(b[j]==b[j-1]){
					j++;
				}
			}
			if(i==n&&j==m)break;
		}
		if(f)cout<<"YES\n";
	} 
	return 0;
}
```

---

## 作者：smydahaoren (赞：0)

### 思路分析

这道题我认为就是字符串模拟，用两个游标来扫描字符串即可。

仔细观察题目，可以发现，第二个字符串必须是第一个字符串的基础上，在中间找出插入点，只能插入左边或者右边的字符，才是合法的。

设原始字符串游标为 $i$，第二个字符串游标为 $j$。当两个游标指向的字符相同时，游标同时向前一格。不相同时，第二个字符串的游标根据规则必须指向 $s_{i-1}$ 这个字符，否则不合法。

举个例子：

两个字符串为

```
Hello
```

```
Heeellooo
```

因为前两个字符都是一样的，所以 $i$ 和 $j$ 都会变成 $3$。然后 $j$ 指向的 $\texttt{e}$ 就必须等于 $i-1$ 指向的内容。否则不合法。

最后，在排查结束所有不合法的内容后，通过游标大小来判断发送的内容对于原始字符串是否完整。

### AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin>>T;
	while(T--){
	bool b=1;
	string s=" ",ss;
	string s1=" ",ss1;
	cin>>ss>>ss1;
	s+=ss;
	s1+=ss1;
	int j=1;
	for(int i=1;i<=s1.size();i++){
		if(s[j]==s1[i]){
			j++;
			continue;
		}
		if(s1[i]!=s[j-1]){
			b=0;
			break;
		}
	}
//	cout<<j<<" "<<b<<endl;
	if((j-1)==s.size()&&b)
	cout<<"YES"<<endl;
	else
	cout<<"NO"<<endl;
	}
	return 0;
}
```


---

## 作者：Wangjunhao2011 (赞：0)

这道题本蒟蒻也是想了很久，终于想到我们可以定义一个指针 $p$ 来遍历邮件内容。我的想法是从 $0$ 一直遍历到 ``a.size()``，其中拿一个指针 $p$，一开始是 $0$。如果 ``a[i]==a[i+1]``,那说明如果猜测正确，包括 ``b[p]`` 以内后面至少还有 $2$ 个。所以我们就假设他的猜测是对的，我们假设这个键盘对于这个字符只输出了一次。但如果 ``a[i]!=a[i+1]`` 我们就假设从 $p$ 开始，后面的都是这次输出的。

WA 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;cin>>T;
	for(int y=1;y<=T;y++){
		string a,b;cin>>a>>b;
		bool flag=0;
		if(b.size()<a.size()){
			cout<<"NO\n";
			continue;
		}
		int p=0;
		for(int i=0;i<a.size();i++){
			if(flag==1)continue;
			if(a[i]!=b[p]){
				flag=1;
				continue;
			} 
			if(a[i]==a[i+1]){
				p++;
				continue;
			} 
			else{
				while(b[p]==a[i])p++; 
			}
		}
		if(flag)cout<<"NO\n";
		else cout<<"YES\n";
	}
	return 0;
} 
```
你运行这个代码会发现连第二个样例都过不了。

### Hack 数据
输入
```cpp
1
aaaa
aaaab
```
输出
```cpp
NO
```
你会发现我们只完整的遍历了一遍 $a$，但是对于 $b$ 却并没有遍历完。于是我们可以加上以下代码：
```cpp
for(int i=p;i<b.size();i++){
	if(b[i]!=a[a.size()-1])flag=1;
}
```
AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;cin>>T;
	for(int y=1;y<=T;y++){
		string a,b;cin>>a>>b;
		bool flag=0;
		if(b.size()<a.size()){
			cout<<"NO\n";
			continue;
		}
		int p=0;
		int len=a.size();
		for(int i=0;i<len;i++){
			if(flag==1)continue;
			if(a[i]!=b[p]){
				flag=1;
				continue;
			} 
			if(a[i]==a[i+1]){
				p++;
				continue;
			} 
			else{
				while(b[p]==a[i])p++; 
			}
		}
		for(int i=p;i<b.size();i++){
			if(b[i]!=a[a.size()-1])flag=1;
		}
		if(flag)cout<<"NO\n";
		else cout<<"YES\n";
	}
	return 0;
} 
```

---

## 作者：blsya23a2 (赞：0)

## 分析
首先，把输入的单词按顺序转换为某个字母和这个字母的连续出现次数的形式，例如把 `aaabb` 转换为 `(a,3),(b,2)`。转换后分别存储在列表 $e$ 和 $f$ 中。由题知，合法猜测有 3 个限制条件。
1. $e$ 的长度等于 $f$ 的长度。

2. 对于每个不超出范围的 $i$，$e_{i,1}=f_{i,1}$。
3. 对于每个不超出范围的 $i$，$e_{i,2}\le f_{i,2}$。

如果满足这 3 个条件，那么输出 `YES`，否则输出 `NO`。
## 代码
```python
a = int(input())
for b in range(a):
    c,d,e,f,g,h,i,j = input(),input(),[],[],0,0,0,0
    for k in c:
        if k != g:
            if g != 0:
                e.append((g,i))
            g,i = k,1
        else:
            i += 1
    e.append((g,i))
    for l in d:
        if l != h:
            if h != 0:
                f.append((h,j))
            h,j = l,1
        else:
            j += 1
    f.append((h,j))
    m = len(e)
    if len(f) != m:
        print('NO')
        continue
    o = 0
    for n in range(m):
        if e[n][0] != f[n][0] or e[n][1] > f[n][1]:
            o = 1
            break
    if o == 1:
        print('NO')
    else:
        print('YES')
```

---

## 作者：Coffee_zzz (赞：0)

细节题。

### 分析

设第一个字符串为 $a$，长度为 $n$；第二个字符串为 $b$，长度为 $m$。

当 $m<n$ 时显然无解，输出 `NO` 即可。

接着，用一个变量 $i$ 扫 $a$，一个变量 $j$ 扫 $b$。

若 $a_i$ 与 $b_j$ 相同，则将 $i+1$，$j+1$，继续扫，直到 $i=n$。  
反之，若 $a_i$ 与 $b_j$ 不相同，则将 $j+1$，继续检查，直到 $a_i$ 与 $b_j$ 相同。若此时 $j=0$ 或 $b_{j-1}$ 与 $b_j$ 不相同，因为多打出的字符一定与上一个字符相同，所以不合法，输出 `NO`。

若 $i$ 还没有扫完，$j$ 已经扫完了，显然不合法，输出 `NO`。

若 $i$ 扫完了，$j$ 却没有扫完，检查 $b$ 中剩余字符，若其中有字符与 $a_{i-1}$ 不相同，则输出 `NO`。

至此，所有不合法的情况全部被排除，输出 `YES` 即可。

### 代码

```c++
#include <bits/stdc++.h>
using namespace std;
int main(){
	int t,i,j,n,m;
	string a,b;
	cin>>t;
	while(t--){
		cin>>a>>b,n=a.size(),m=b.size(),j=0;
		if(m<n){
			puts("NO");
			continue;
		}
		for(i=0;i<n;i++){
			while(a[i]!=b[j]&&j!=m){
				if(j==0||b[j]!=b[j-1]){j=m;break;}
				j++;
			}
			if(j==m) {puts("NO");break;}
			j++;
		}
		if(i==n){
			for(;j<m;j++) if(b[j]!=b[j-1]) break;
			if(j==m) puts("YES");
			else puts("NO");
		}
	}
	return 0;
}
```

---

