# [ABC301C] AtCoder Cards

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc301/tasks/abc301_c

AtCoder社ではカードを使った $ 1 $ 人ゲームが流行っています。  
 ゲームで使う各カードには、英小文字 $ 1 $ 文字または `@` の文字が書かれており、いずれのカードも十分多く存在します。  
 ゲームは以下の手順で行います。

1. カードを同じ枚数ずつ $ 2 $ 列に並べる。
2. `@` のカードを、それぞれ `a`, `t`, `c`, `o`, `d`, `e`, `r` のいずれかのカードと置き換える。
3. $ 2 $ つの列が一致していれば勝ち。そうでなければ負け。
 
このゲームに勝ちたいあなたは、次のようなイカサマをすることにしました。

- 手順 $ 1 $ 以降の好きなタイミングで、列内のカードを自由に並び替えてよい。
 
手順 $ 1 $ で並べられた $ 2 $ つの列を表す $ 2 $ つの文字列 $ S,T $ が与えられるので、イカサマをしてもよいときゲームに勝てるか判定してください。

## 说明/提示

### 制約

- $ S,T $ は英小文字と `@` からなる
- $ S,T $ の長さは等しく $ 1 $ 以上 $ 2\times\ 10^5 $ 以下
 
### Sample Explanation 1

`@` をうまく置き換えることによって、両方とも `chokudai` と一致させることが可能です。

### Sample Explanation 2

イカサマをし、`@` をうまく置き換えることによって、両方とも `chokudai` と一致させることが可能です。

### Sample Explanation 3

イカサマをしても勝つことはできません。

## 样例 #1

### 输入

```
ch@ku@ai
choku@@i```

### 输出

```
Yes```

## 样例 #2

### 输入

```
ch@kud@i
akidu@ho```

### 输出

```
Yes```

## 样例 #3

### 输入

```
aoki
@ok@```

### 输出

```
No```

## 样例 #4

### 输入

```
aa
bb```

### 输出

```
No```

# 题解

## 作者：CheZiHe929 (赞：10)

# AT_abc301_c题解

## 原题链接
[**Atcoder**](https://atcoder.jp/contests/abc301/tasks/abc301_c)

[**洛谷AT_abc301_c**](https://www.luogu.com.cn/problem/AT_abc301_c)

## 题目大意
给你两个长度相同的字符串 $S$ 和 $T$，你可以进行如下两个操作：

1. 将其中的 `@` 转化为 `a`，`t`，`c`，`o`，`d`，`e`，`r` 中的任意一个

2. 任意交换字符的顺序

问是否能通过数次以上两种操作使得字符串 $S$ 等于字符串 $T$。

## 思路分析
所谓看两个字符串是否相等，其实就是看每种字符类型的数量是否相等。既然要查看每一位上的字符是什么，所以不妨设 $S$ 和 $T$ 为字符数组。读入两个字符数组后，储存下每种字符类型的数量（包括 `@` 的数量）。然后每个字符类型进行比较，如果为七个字母之一且数量不一样的话，就让少的那一组的 `@` 减去相应的数量。如果非七个字母，那两个字符数组是一定无法通过题目中的两个操作变为一样的。最后比较每个组 `@` 的大小是否相等以及其正负性即可。

## 代码时间
```cpp
#include<bits/stdc++.h>
using namespace std;
char S[200005],T[200005]; 
int nums[30],numt[30];//S,T中每个字符类型的数量 
int Sat,Tat;//S,T中@的数量 
signed main(){
	cin>>S>>T;
	int len=strlen(S);//提前在循环外面计算字符数组长度，否则会TLE 
	for(int i=0;i<len;i++){
		if(S[i]=='@')Sat++;
		else nums[S[i]-'a'+1]++;//nums[1]为a的数量，nums[2]为b的数量，以此类推 
		if(T[i]=='@')Tat++;
		else numt[T[i]-'a'+1]++;//两处都不要忘记了+1 
	}
	for(int i=1;i<26;i++){
		if(nums[i]==numt[i])continue;//数量相等就跳过 
		if(i==1||i==3||i==4||i==5||i==15||i==18||i==20){
			//即S[i]或T[i]是否为atcoder其中一个字母 
			if(nums[i]>numt[i])Tat-=nums[i]-numt[i];
			else Sat-=numt[i]-nums[i];//因为前面数量相等的已经跳过，所以这里一定是不相等的 
		}
		else{//即数量不相等且不为七个字母之一 
			cout<<"No"<<endl;
			return 0;
		} 
	}
	if(Sat!=Tat||Tat<0||Sat<0){//如果剩余的@的数量不一致或其中一个的@的数量<0(也就是不够用了) 
		cout<<"No"<<endl;
		return 0;
	}
	//一直都没有被筛除掉（即为合格），也就是说可以调换至相等 
	cout<<"Yes"<<endl;
	return 0;
}
```

**无注释版的我放到了[这里](https://www.luogu.com.cn/paste/ygjtmvib)**

## AC记录
[**Atcoder**](https://atcoder.jp/contests/abc301/submissions/41415485)

[**洛谷**](https://www.luogu.com.cn/record/110480974)

**THE END.**

**THANK YOU.**

---

## 作者：FinderHT (赞：5)

### 题目传送门：
### [AtCoder](https://atcoder.jp/contests/abc301/tasks/abc301_c) | [洛谷](https://www.luogu.com.cn/problem/AT_abc301_c)

**思路分析**

我们可以用两个数组记录两个字符串中每个字母出现的个数，还要记录两个字符串中 `@` 的数量。特判 `a` `t` `c` `o` `d` `e` `r` 出现个数在数组中的位置，让少的那个的 `@` 的数量减去这个字母类型数量的个数的差。如果其他字母出现的数量不同，则输出 ```No``` 并结束程序。如果两个字符串 `@` 的数量有一个为非正数，输出 ```No```；否则输出```Yes```。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
int cntx=0,cnty=0;
int x[30],y[30];
signed main(){
	cin>>a>>b;
	int l=a.size();
	for(int i=0;i<l;i++){
		if(a[i]=='@')cntx++;//记录@的数量
		else x[a[i]-96]++;//记录每个字母的数量
		if(b[i]=='@')cnty++;
		else y[b[i]-96]++;
	}
	for(int i=1;i<=26;i++){
		if(i==1||i==20||i==3||i==15||i==4||i==5||i==18){//特判a t c o d e r的位置
			if(x[i]>y[i])cnty-=x[i]-y[i];
			else cntx-=y[i]-x[i];
		}
		else{
			if(x[i]!=y[i]){//其他字母不相同
				cout<<"No";
				return 0;
			} 
		}
	}
	if(cntx<0||cnty<0)cout<<"No";//有一个为非正数
	else cout<<"Yes";
	return 0;
}
```
## 完结撒花！！！

---

## 作者：hellolin (赞：2)

## AtCoder Beginner Contest 301 - C - AtCoder Cards

[洛谷题面](https://www.luogu.com.cn/problem/AT_abc301_c) | [AtCoder 题面](https://atcoder.jp/contests/abc301/tasks/abc301_c) | [AC 记录](https://www.luogu.com.cn/record/110510119) | $\texttt{\color{968d81}*380}$

首先，我们搞出来 $S$ 和 $T$ 中各种字符的数量（和 `@` 的数量）。注意也要同时搞出来字符集。

``` cpp
string s,t;
int sa,ta;
map<char,int>ss,tt;
set<char>al;

for(char i:s){
    if(i=='@')++sa;
    else{
        ++ss[i];
        al.insert(i);
    }
}
for(char i:t){
    if(i=='@')++ta;
    else{
        ++tt[i];
        al.insert(i);
    }
}
```

再枚举字符集中的字符，若数量不同则考虑花费一定量的 `@` 来补成一样的。

``` cpp
for(char i:al){
    int sc=ss[i], tc=tt[i];
    if(sc<tc){
        if(qwq.find(i)==-1){
            cout<<"No"<<endl;
            return;
        }
        else sa-=tc-sc;
    }
    if(sc>tc){
        if(qwq.find(i)==-1){
            cout<<"No"<<endl;
            return;
        }
        else ta-=sc-tc;
    }
}
```

完整代码如下：

``` cpp
// 珍爱账号，请勿贺题
#include <bits/stdc++.h>
using namespace std;
#define int long long

string s,t;
int sa,ta;
map<char,int>ss,tt;
set<char>al;
string atc="atcoder";
void solve(){
    cin>>s>>t;

    for(char i:s){
        if(i=='@')++sa;
        else{
            ++ss[i];
            al.insert(i);
        }
    }
    for(char i:t){
        if(i=='@')++ta;
        else{
            ++tt[i];
            al.insert(i);
        }
    }

    for(char i:al){
        int sc=ss[i], tc=tt[i];
        if(sc<tc){
            if(atc.find(i)==-1){
                cout<<"No"<<endl;
                return;
            }
            else sa-=tc-sc;
        }
        if(sc>tc){
            if(atc.find(i)==-1){
                cout<<"No"<<endl;
                return;
            }
            else ta-=sc-tc;
        }
    }

    cout<<((sa==ta&&sa>=0)?"Yes":"No")<<endl;
}

int32_t main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();

    return 0;
}
```

---

## 作者：kkxacj (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc301_c)

#### 思路

不难想到，要想让两个字符串变成一样的，那么两个字符串对应的每个字母数量肯定都，我们可以将每个字母存起来，然后每个字母比较个数，不一样，就来看是否是 `a`，`t`，`c`，`o`，`d`，`e`，`r` 中的任意一个，如果不是或者 `@` 不够了就直接输出 No，否则输出 Yes。



code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100],b[100],l,l1;
string s,s1;
int main()
{
	cin >> s >> s1;
	for(int i = 0;i < s.size();i++)
	{
		if(s[i] != '@') a[s[i] - 'a']++;
		else l++;
	}
	for(int i = 0;i < s.size();i++)
	{
		if(s1[i] != '@') b[s1[i] - 'a']++;
		else l1++;
	}
	for(int i = 0;i < 26;i++)
	{
		if(a[i] != b[i]) //如果不相等，那么需要用到 @ 
		{
			if(a[i] > b[i])
			{
				if((i + 'a' == 'a' || i + 'a' == 't' || i + 'a' == 'c' || i + 'a' == 'o' || i + 'a' == 'd' || i + 'a' == 'e' || i + 'a' == 'r') && l1 >= a[i] - b[i])
				{
					l1 -= (a[i] - b[i]);
				}
				else
				{
					cout << "No";
					return 0;
				}
			}
			else
			{
				if((i + 'a' == 'a' || i + 'a' == 't' || i + 'a' == 'c' || i + 'a' == 'o' || i + 'a' == 'd' || i + 'a' == 'e' || i + 'a' == 'r') && l >= b[i] - a[i])
				{
					l -= (b[i] - a[i]);
				}
				else
				{
					cout << "No";
					return 0;
				}
			}
		}
	}
	cout << "Yes";
    return 0;
}

```


---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc301_c)        
一道恶心的模拟。       
我们可以先把两个字符串每个字符出现的个数统计出来，之后进行比较，如果是那几个字母中的就替换。      
这里注意一下，替换是需要判断 `@` 的数量的。     
如果要替换，那么我们和替换的那个字符串中剩下的 `@` 的数量进行比较，如果可以就替换，不可以就无解。            
我们一开始判断字符有些麻烦，我们可以存到 unordered_map 里。         
[CODE](https://www.luogu.com.cn/paste/spwrg1qo)

---

## 作者：2huk (赞：0)

## 题目描述

给定两个字符串 $S$ 和 $T$，只含有小写字母和 $\mathrm{@}$。

现在要将两个字符串中的所有 $\mathrm{@}$ 替换成 $\mathrm{atcoder}$ 中的一个字符，问替换后的字符串经过**排列**后能否相等。

$1 \le |S| = |T| \le 2\times10^5$

## 分析

由于要排列字符串，不难想到用桶来存储每一个字符。

我们把两个字符串中的小写字母的出现次数分别存入两个桶 $A,B$ 中，并统计出两个字符串中 $\mathrm{@}$ 的出现次数为 $x$。

然后一一比较两个桶中的数据。如果 $A_i = B_i$，也就是两个字符出现的次数相同，那么我们不需要用 $\mathrm{@}$ 替换，也就不需要考虑这种情况。

反之，如果 $A_i \ne B_i$，那么也就是需要把原字符串中的若干个 $\mathrm{@}$ 替换成 $i$。根据题意，只能替换成 $\mathrm{atcoder}$ 中的一个字符，所以还需要判断当前的 $i$ 是否在 $\mathrm{atcoder}$ 中。如果不在就说明无论如何都无法成功替换，输出 $\mathrm{No}$ 结束即可。反之，如果在 $\mathrm{atcoder}$ 中，那么就需要统计出这样的字符的数量。我们让 $s$ 加上这 $A_i$ 和 $B_i$ 的差，表示**最少**需要把几个 $\mathrm{@}$ 替换成 $i$ 后使得两个字符串包含 $i$ 的数量是相同的。

如果执行到最后都没有结束程序，那么就需要比较原字符串中 $\mathrm{@}$ 的数量 $x$ 和 $s$ 的大小，是否是 $x \ge s$ 即可。

 ## 代码

放[这](https://www.luogu.com.cn/paste/ozs2vabw)了。



---

## 作者：DengDuck (赞：0)

首先上下都有的字母可以抵消，我们考虑用一个桶统计出每个字母上下数量的差。

同时，我们也统计出上下“妙妙符号” `@` 的数量，利用其消除上下 `atcoder` 几个字母的差距。

无解有两种情况：

- `@` 无法消去所有的 `atcoder` 的差距。
- 有不是 `atcoder` 的差距。
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
string a,b;
LL n,c[26],f1,f2;
int main()
{
	cin>>a>>b;
	n=a.size();
	for(int i=0;i<=n-1;i++)
	{	
		if(a[i]=='@')f1++;
		else c[a[i]-'a']++;
		if(b[i]=='@')f2++;
		else c[b[i]-'a']--;//统计
	}
	for(int i=0;i<=25;i++)
	{
		if(i+'a'=='a'||i+'a'=='t'||i+'a'=='c'||i+'a'=='o'||i+'a'=='d'||i+'a'=='e'||i+'a'=='r')
		{
			if(c[i]<0)f1+=c[i];
			else f2-=c[i];
			c[i]=0;
		}//消除 atcoder 差异
	} 
	if(f1!=f2||f1<0||f2<0)//无法消除 atcoder 差异
	{
		puts("No");
		return 0;
	}
	for(int i=0;i<=25;i++)//有其他差异
	{
		if(c[i]!=0)
		{
			puts("No");
			return 0;		
		}
	}
	puts("Yes");
}
```

---

## 作者：Loser_Syx (赞：0)

## 思路

题目说要经过重排和替换 `@`，使得两个字符串相等。

首先我们已知 `@` 可以被替换成 `a`，`t`，`c`，`o`，`d`，`e`，`r`，中任意一个，如果那两个字符串字符数量不等的字符中，有不是这些的，那么一定不能使其相等。

其他情况，我们可以统计，两个字符串一共有多少个不同的字符，如果 `@` 的总数 $\geq$ 他们的话，便可以替换，否则不能。

## 代码

```cpp
#include <iostream>
 
using namespace std;
typedef long long ll;
 
int a[114514];
 
int main(){
	string s, t;
	cin >> s >> t;
	ll s_ = 0, t_ = 0;
	int len = s.size();
	for(int i = 0; i < len; ++i){
		a[s[i]]++;
		if(s[i] == '@') s_ ++;
		a[t[i]]--;
		if(t[i] == '@') t_ ++;
	}
	
	int alldif = 0;
	for(char i = 'a'; i <= 'z'; ++i){
		if(a[i] != 0){
			if(i != 'a' && i != 't' && i != 'c' && i != 'o' && i != 'd' && i != 'e' && i != 'r') return cout << "No", 0;
		}
		alldif += abs(a[i]);
	}
	if(s_ + t_ < alldif) puts("No");
	else puts("Yes");
	return 0;
}
```

---

