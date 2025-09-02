# Tanya and Postcard

## 题目描述

Little Tanya decided to present her dad a postcard on his Birthday. She has already created a message — string $ s $ of length $ n $ , consisting of uppercase and lowercase English letters. Tanya can't write yet, so she found a newspaper and decided to cut out the letters and glue them into the postcard to achieve string $ s $ . The newspaper contains string $ t $ , consisting of uppercase and lowercase English letters. We know that the length of string $ t $ greater or equal to the length of the string $ s $ .

The newspaper may possibly have too few of some letters needed to make the text and too many of some other letters. That's why Tanya wants to cut some $ n $ letters out of the newspaper and make a message of length exactly $ n $ , so that it looked as much as possible like $ s $ . If the letter in some position has correct value and correct letter case (in the string $ s $ and in the string that Tanya will make), then she shouts joyfully "YAY!", and if the letter in the given position has only the correct value but it is in the wrong case, then the girl says "WHOOPS".

Tanya wants to make such message that lets her shout "YAY!" as much as possible. If there are multiple ways to do this, then her second priority is to maximize the number of times she says "WHOOPS". Your task is to help Tanya make the message.

## 样例 #1

### 输入

```
AbC
DCbA
```

### 输出

```
3 0
```

## 样例 #2

### 输入

```
ABC
abc
```

### 输出

```
0 3
```

## 样例 #3

### 输入

```
abacaba
AbaCaBA
```

### 输出

```
3 4
```

# 题解

## 作者：dear_deer_land (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF518B)

## 思路

贪心。

判断字母是否相同，如果相同，统计次数。


- 两个字母完全一样。

- 要小写字母，只有大写或要大写字母，只有小写。

注意她要求优先完全一样，所以先计算第一种再计算第二种即可。

---

## 作者：shenbairui (赞：1)

### 题目大意
给定两个字符串 $s_1$ 和 $s_2$。从 $s_2$ 中选择与 $s_1$ 大小写相等或大小写不等的字符，求出能选择多少。
### 题目分析
考虑对报纸里的字母用桶进行统计，并进行分类讨论。

判断字母是否相同，如果相同，统计次数。有三种情况：

两个字母完全一样。

要小写字母，只有大写。

要大写字母，只有小写。
### 代码如
```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
int akcsp[200],rp,ac;
int main(){
	cin>>a>>b;
	for(int i=0;i<b.size();i++) akcsp[b[i]]++;
	for(int i=0;i<a.size();i++){
		if(akcsp[a[i]]!=0){
			akcsp[a[i]]--;
			rp++;
			a[i]=32;
		}
	}
	for(int i=0;i<a.size();i++){
		if(akcsp[a[i]-32]!=0){
			akcsp[a[i]-32]--;
			ac++;
			a[i]=32;
		} 
	}
	for(int i=0;i<a.size();i++){
		if(akcsp[a[i]+32]!=0){
			akcsp[a[i]+32]--;
			ac++;
			a[i]=32;
		}
	}
	cout<<rp<<" "<<ac;
	return 0;
}
```
[AC记录](https://codeforces.com/contest/518/submission/282461472)

下期见！拜拜！

---

## 作者：Fearliciz (赞：1)

这道题可以用桶做。

首先将两个字符串读入。

其次用桶将报纸上的字母存储。

```cpp
for(int i=0;i<len2;i++) cn[b[i]]++;
```

接下来分别判断有没有完全一样的字符，和除了大小写不一样其他都一样的字符。

```cpp
for(int i=0;i<len1;i++) if(cn[a[i]]!=0){cn[a[i]]--;ans1++;a[i]=32;} //完全一样
    for(int i=0;i<len1;i++) if(cn[a[i]-32]!=0){cn[a[i]-32]--;ans2++;a[i]=32;} //大小写不一样
    for(int i=0;i<len1;i++) if(cn[a[i]+32]!=0){cn[a[i]+32]--;ans2++;a[i]=32;} //大小写不一样
```

注意，这里不能只有一个 $\texttt{for}$ 循环找大小写不一样的，因为有两种情况：

+ 想要小写的，却只有大写的。

+ 想要大写的，却只有小写的。

最后输出答案即可。

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[200001],b[200001];
int cn[200],ans1,ans2;
int main()
{
    cin>>a>>b;
    int len1=strlen(a),len2=strlen(b);
    for(int i=0;i<len2;i++) cn[b[i]]++; //用桶来存储
    for(int i=0;i<len1;i++) if(cn[a[i]]!=0){cn[a[i]]--;ans1++;a[i]=32;} //完全一样
    for(int i=0;i<len1;i++) if(cn[a[i]-32]!=0){cn[a[i]-32]--;ans2++;a[i]=32;} //大小写不一样
    for(int i=0;i<len1;i++) if(cn[a[i]+32]!=0){cn[a[i]+32]--;ans2++;a[i]=32;} //大小写不一样
    cout<<ans1<<' '<<ans2;
    return 0;
}
```


---

## 作者：Graphcity (赞：1)

## 思路

首先不妨把两个字符串中每个字符出现的次数放到两个桶 $s_1$ , $s_2$ 里面。由于这道题特殊的性质，大写和小写分开放。

不妨考虑贪心。要使得“耶”的次数尽量多，就得要先匹配字符完全一样的。匹配完“耶”之后，再来尽量匹配只有大小写不一样的字符，使得“哎哟”的次数最多。

假如匹配了两个字符 $a$ 和 $b$ , 让它们在桶中的数字减去 1 就可以表示它们被匹配了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int s1[30][2],s2[30][2]; //小写第二维是0,大写是1
int ans1,ans2;

int main()
{
	string a,b;
	cin>>a>>b;
	for(register int i=0;i<a.size();++i) //放入桶中
	{
		char ch=a[i];
		if(ch>='a' && ch<='z') s1[ch-'a'+1][0]++;
		else s1[ch-'A'+1][1]++;
	}
	for(register int i=0;i<b.size();++i)
	{
		char ch=b[i];
		if(ch>='a' && ch<='z') s2[ch-'a'+1][0]++;
		else s2[ch-'A'+1][1]++;
	}
	for(register int i=1;i<=26;++i) //匹配"耶"
	{
		while(s1[i][0] && s2[i][0])
			ans1++,s1[i][0]--,s2[i][0]--;
		while(s1[i][1] && s2[i][1])
			ans1++,s1[i][1]--,s2[i][1]--;
	}
	for(register int i=1;i<=26;++i) //匹配"哎呦"
	{
		while(s1[i][0] && s2[i][1])
			ans2++,s1[i][0]--,s2[i][1]--;
		while(s1[i][1] && s2[i][0])
			ans2++,s1[i][1]--,s2[i][0]--;
	}
	printf("%d %d",ans1,ans2);
	return 0;
}
```

---

## 作者：mcturtle (赞：0)

一道水题。
## 思路：

考察桶的应用。

先读入两个字符串，再把报纸上的字母存储进桶里。

处理三种情况：

- 两个字母完全一致
- 想要小写，但是大写
- 想要大写，但是小写

将这三种情况统计一下即可。

## 重要代码部分：
温馨提示，不要直接抄，理解了才行。
```cpp
//t[]代表桶，s[]代表字符串，x代表耶的次数，y代表哎呦的次数
for(int i=0;i<s.size();i++){
    if(t[s[i]]!=0)t[s[i]]--,x++;
    else if(t[s[i]-' ']!=0)t[s[i]-' ']--,y++;
    else if(t[s[i]+' ']!=0)t[s[i]+' ']++,y++;
}
```
时间复杂度 $O(N)$。

---

## 作者：TiAmo_qwq (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF518B)


---

## 思路：
这道题考察的是桶，定义一个数组 $a$，存储报纸上的每一个字母出现的次数，然后在小女孩需要的字符串里查找，这里分两种情况：

1.若有完全相同的字符，$ans1$ 加 $1$（$ans1$ 表示小女孩说“耶”的次数）。

2.若有相同字符但是大小写不同，$ans2$ 加 $1$（$ans2$ 表示小女孩说“哎呦”的次数）。

## 代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define pre(i, a, b) for(int i = (a); i >= (b); i--)

const int N = 1e6 + 10;

int a[100005];

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	string s, s1;
	cin >> s >> s1;
	rep(i, 0, s1.size() - 1){
		a[s1[i]]++;
	}
	int ans1 = 0, ans2 = 0;
	rep(i, 0, s.size() - 1){
		if(a[s[i]] != 0){
			a[s[i]]--;
			ans1++;
		}
		else if(a[s[i] - 32] != 0){
			a[s[i] - 32]--;
			ans2++;
		}
		else if(a[s[i] + 32] != 0){
			a[s[i] + 32]++;
			ans2++;
		}
	}
	cout << ans1<< ' ' << ans2;
	return 0;
}

```

---

## 作者：smartdevil (赞：0)

## 题意：

给定两个字符串 $s_1$ 和 $s_2$。从 $s_2$ 中选和 $s_1$ 大小写相等或者不等，求能选多少。

## 思路：

桶排序，分类讨论。

判断字母是否相同，有三种情况。

- 字母完全一样。
- 要小写，只有大写。
- 要大写，有小写。

~~所以为啥不能提交了QWQ~~

---

## 作者：fmdd_szx (赞：0)

[原题](https://www.luogu.com.cn/problem/CF518B)
## 思路
考虑对报纸里的字母进行计数。

判断字母是否相同，如果相同，统计次数。有三种情况：

- 两个字母完全一样。
- 要小写字母，只有大写。
- 要大写字母，只有小写。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,s1,s2,f[1001];
char s[200001],t[200001];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>s+1>>t+1;
    n=strlen(s+1);
    m=strlen(t+1);
    for(i=1;i<=m;i++)
        f[t[i]]++;//计数
    for(i=1;i<=n;i++)//注意要用多个for
        if(f[s[i]]) f[s[i]]--,s1++,s[i]=32;//一样
    for(i=1;i<=n;i++)
        if(f[s[i]-32]) f[s[i]-32]--,s2++,s[i]=32;//只有大写
    for(i=1;i<=n;i++)
        if(f[s[i]+32]) f[s[i]+32]--,s2++,s[i]=32;//只有小写
    cout<<s1<<" "<<s2;//输出次数
    return 0;
}

```

---

## 作者：liyifan202201 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF518B)
## 思路
使用**贪心**。
- 若要使“耶”的次数尽量多。
> 匹配字符就要尽可能的完全一样。

- 若要使“哎呦”的次数尽量多。
> 匹配字符就要尽可能的大小写不一样。

**注意**：需先计算“耶”使“耶”尽可能的多，后计算“哎呦”在“耶”最多的条件下“哎呦”。
## 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
//a 的小写桶（al）和大写桶（ab）
map<int, int>al, ab;
//b 的小写桶（bl）和大写桶（bb）
map<int, int>bl, bb;
int ans1, ans2;

int main() {
	string a, b;
	cin >> a >> b;
	//将 a 的小写和大写统计
	for (auto &i : a) {
		if (i >= 'a' and i <= 'z') {
			al[i - 'a' + 1]++;
		} else {
			ab[i - 'A' + 1]++;
		}
	}
	//将 b 的小写和大写统计

	for (auto &i : b) {
		if (i >= 'a' and i <= 'z') {
			bl[i - 'a' + 1]++;
		} else {
			bb[i - 'A' + 1]++;
		}
	}
	
	//计算“耶”的答案（先计算使“耶”尽可能的多）
	for (int i = 1; i <= 26; ++i) {
		while (al[i] and bl[i]){
			//统计答案和修改桶
			ans1++;
			al[i]--;
			bl[i]--;
		}
		while (ab[i] and bb[i]){
			//统计答案和修改桶
			ans1++;
			ab[i]--;
			bb[i]--;
		}
	}
	
	//匹配“哎呦”的答案
	//与上面的差不多
	for (int i = 1; i <= 26; ++i) {
		while (al[i] and bb[i]){
			//统计答案和修改桶
			ans2++;
			al[i]--;
			bb[i]--;
		}
		while (ab[i] and bl[i]){
			//统计答案和修改桶
			ans2++;
			ab[i]--;
			bl[i]--;
		}
	}
	cout<<ans1<<" "<<ans2;
	return 0;
}
```

---

## 作者：Scapegoat_Tree (赞：0)

## 思路

- 由于题目要求匹配大小写，我们要将大小写分开存放。

- 统计$s,t$的每个字母大小写个数。

- 由于要求“耶”尽可能多，所以尽可能匹配大小写。

- 将大小写尽可能匹配后，剩下的只有可能是“哎呦”，因此对于$s,t$中剩余的字母，取每个字符不区分大小写后的最小值，加和即可。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
namespace SGT
{
	char getc(){return getchar();}
	void putc(char ch){putchar(ch);}
	int read(){int mk=1,x=0;char ch=getc();while(ch!='-'&&(ch<'0'||ch>'9'))ch=getc();if(ch=='-')mk=-1,ch=getc();while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getc();return x*mk;}
	void write(int x,char ch){char cc[100000];int t=0;if(x==0)putc('0');if(x<0) putc('-'),x=-x;while(x){cc[++t]=char(x%10+48);x/=10;}for(int i=t;i>=1;i--)putc(cc[i]);putc(ch);}
	void write(char str[],char ch){for(int i=0;i<strlen(str);i++)putc(str[i]);putc(ch);}
	void write(char wr,char ch){putc(wr);putc(ch);}
	int max(int a,int b){return (a>b?a:b);}
	int min(int a,int b){return (a<b?a:b);}
}
using namespace SGT;
char s[200010];
int t1[200],t2[200],tt1,tt2,ans1,ans2;
signed main()
{
	char ch=getc();
	while(ch!='\n')
	{
		t1[ch-'A']++;
		ch=getc();
	}
	ch=getc();
	while(ch!='\n')
	{
		t2[ch-'A']++;
		ch=getc();
	}
	for(int i=0;i<=25;i++)
	{
		if(t1[i]>t2[i]) t1[i]-=t2[i],ans1+=t2[i],t2[i]=0;
		else t2[i]-=t1[i],ans1+=t1[i],t1[i]=0;
	}
	for(int i1=0;i1<=25;i1++)
	{
		int i=i1+'a'-'A';
		if(t1[i]>t2[i]) t1[i]-=t2[i],ans1+=t2[i],t2[i]=0;
		else t2[i]-=t1[i],ans1+=t1[i],t1[i]=0;
	}
	for(int i=0;i<=25;i++)
	{
		tt1=t1[i]+t1[i+'a'-'A'];
		tt2=t2[i]+t2[i+'a'-'A'];
		ans2+=min(tt1,tt2);
	} 
	write(ans1,' ');
	write(ans2,'\n');
	return 0;
}
```

---

## 作者：QQH08 (赞：0)

首先，分别用 $mp1_c$ 和 $mp2_c$ 表示字符串 s 和 t 中字符 c 出现的个数（可以用 map 实现）。然后分别考虑“耶！”和“哎呦”。

对于“耶！”：

对于每一个大小写字符 c，分 $2$ 类进行：

- 如果 $mp2_c \geq mp1_c$，则所有 $mp1_c$ 都可以加到答案里，再把 $mp2_c$ 和 $mp1_c$ 更新（具体见代码）。

- 如果 $mp2_c \leq mp1_c$，则只有 $mp2_c$ 的个数可以和 s 匹配，加到答案里，其他操作类似于第一种。

对于“哎呦”：

对于每一大小写字符 c，如果 $mp1_c \ne 0$，那么说明 s 里还有剩下的，直接用剩下大/小写的匹配即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int ans1,ans2;
char s[N],t[N];
map<char,int> mp,mp2;
void work(char c){
	if(mp2[c]>=mp[c]){
		ans1+=mp[c];
		mp2[c]-=mp[c];
		mp[c]=0;
	}
	else{
		ans1+=mp2[c];
		mp[c]-=mp2[c];
		mp2[c]=0;
	}
}
int main(){
	scanf("%s%s",s+1,t+1);
	int n=strlen(s+1),m=strlen(t+1);
	for(int i=1;i<=n;i++)mp[s[i]]++;
	for(int i=1;i<=m;i++)mp2[t[i]]++;
	for(int i=0;i<26;i++){
		char c='a'+i;
		work(c);
		c='A'+i;
		work(c);
	}
	for(int i=0;i<26;i++){
		char c='a'+i,c2='A'+i;
		if(mp[c]!=0){
			int x=min(mp[c],mp2[c2]);
			ans2+=x;
			mp[c]-=x;
			mp2[c2]-=x;
		}
		if(mp[c2]!=0){
			int x=min(mp[c2],mp2[c]);
			ans2+=x;
			mp[c2]-=x;
			mp2[c]-=x;
		}
	}
	printf("%d %d",ans1,ans2);
	return 0;
} 
```


---

## 作者：hanzizhou (赞：0)


### 思路
看这数据于是决定用桶来做。把相同的字母放在一个桶里。

因为"耶"越多越好，所以要先匹配一样的大小写字母，统计并标记成 $ 0 $，数量减 $ 1 $。

"耶"一样多的情况下，"哎呦"要尽量多，即大小写不同的字母尽量匹配，具体见代码。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[200001],t[200001];//字符串，不多做解释。
int l1,l2,sum[151],ans1,ans2;//长度及桶，还有"耶""哎呦"的个数
int main(){
	scanf("%s%s",s,t);
	l1=strlen(s);l2=strlen(t);
	for(int i=0;i<l2;++i)sum[t[i]]++;//统计
	for(int i=0;i<l1;++i)if(sum[s[i]]>0){sum[s[i]]--;ans1++;s[i]=0;}//相同的字母，答案加，字母减，标0。
	for(int i=0;i<l1;++i)
	if(s[i]>0){
		if('a'<=s[i]&&s[i]<='z'&&sum[s[i]-'a'+'A']){sum[s[i]-'a'+'A']--;ans2++;}//是小写字母，匹配大写字母。
		if('A'<=s[i]&&s[i]<='Z'&&sum[s[i]-'A'+'a']){sum[s[i]-'A'+'a']--;ans2++;}//是大写字母，匹配小写字母。
	}
	printf("%d %d",ans1,ans2);
	return 0;
}
```


---

## 作者：5G信号塔报装 (赞：0)

## 题意

给定两个字符串 $s_1$，$s_2$。从 $s_2$ 中选择与 $s_1$ 大小写相等或大小写不等的字符，求出能选择多少。

## 思路

没有细节，暴力裸题。

注意 $\text{length}$ 不超过 $2 \times 10^5$，显然开桶求解。计算 $s_1$ 和 $s_2$ 中最多能选中的字符对。除去预处理过程，时间复杂度为常数。

## 代码

```cpp
# include <bits/stdc++.h>
using namespace std;

int bucket1[128], bucket2[128];
string a, lib;

signed main() {
	cin >> a >> lib;
	for (int i = 0; i < a.length(); i++) {
		bucket1[a[i]]++;
	}
	for (int i = 0; i < lib.length(); i++) {
		bucket2[lib[i]]++;
	}
	int ab, ac;
	ab = ac = 0;
	for (int i = 'a'; i <= 'z'; i++) {
		int plus = min(bucket1[i], bucket2[i]);
		bucket1[i] -= plus;
		bucket2[i] -= plus;
		ab += plus; 
	}	 
	for (int i = 'A'; i <= 'Z'; i++) {
		int plus = min(bucket1[i], bucket2[i]);
		bucket1[i] -= plus;
		bucket2[i] -= plus;
		ab += plus; 
	}	 
	for (int i = 'a'; i <= 'z'; i++) {
		int plus = min(bucket1[i], bucket2[i - 'a' + 'A']);
		bucket1[i] -= plus;
		bucket2[i - 'a' + 'A'] -= plus;
		ac += plus;
	}
	for (int i = 'A'; i <= 'Z'; i++) {
		int plus = min(bucket1[i], bucket2[i - 'A' + 'a']);
		bucket1[i] -= plus;
		bucket2[i - 'A' + 'a'] -= plus;
		ac += plus;
	}
	printf("%d %d\n", ab, ac);
	return 0;
} 
```

---

