# Minimax

## 题目描述

Prefix function of string $ t = t_1 t_2 \ldots t_n $ and position $ i $ in it is defined as the length $ k $ of the longest proper (not equal to the whole substring) prefix of substring $ t_1 t_2 \ldots t_i $ which is also a suffix of the same substring.

For example, for string $ t =  $ abacaba the values of the prefix function in positions $ 1, 2, \ldots, 7 $ are equal to $ [0, 0, 1, 0, 1, 2, 3] $ .

Let $ f(t) $ be equal to the maximum value of the prefix function of string $ t $ over all its positions. For example, $ f( $ abacaba $ ) = 3 $ .

You are given a string $ s $ . Reorder its characters arbitrarily to get a string $ t $ (the number of occurrences of any character in strings $ s $ and $ t $ must be equal). The value of $ f(t) $ must be minimized. Out of all options to minimize $ f(t) $ , choose the one where string $ t $ is the lexicographically smallest.

## 说明/提示

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

In the first test case, $ f(t) = 0 $ and the values of prefix function are $ [0, 0, 0, 0, 0] $ for any permutation of letters. String ckpuv is the lexicographically smallest permutation of letters of string vkcup.

In the second test case, $ f(t) = 1 $ and the values of prefix function are $ [0, 1, 0, 1, 0, 1, 0] $ .

In the third test case, $ f(t) = 5 $ and the values of prefix function are $ [0, 1, 2, 3, 4, 5] $ .

## 样例 #1

### 输入

```
3
vkcup
abababa
zzzzzz```

### 输出

```
ckpuv
aababab
zzzzzz```

# 题解

## 作者：Zesty_Fox (赞：9)

一道很好的构造题，锻炼思维。

以下设原串长为 $len$。

### Case 1: 只有一种字符

直接输出原串即可。

### Case 2: 有多种字符

#### Case 2.1: 存在一种字符出现次数为1

显然把这个字符放在最前面，其他字符排序后接在后面即可。

如：$\texttt{bbcaaa}$ 最优解为 $\texttt{caaabb}$。

#### Case 2.2: 所有字符出现次数大于等于2

不妨设最小的字符为 $\texttt{a}$，其出现次数为 $cnt$。

那么，最后的答案为 $1$。

由于要保证字典序最小，我们尽可能多地把 $\texttt{a}$ 放在最前。不难发现最前面最多有有连续两个 $\texttt{a}$。

##### Case 2.2.1 最前面可以放连续两个 a

考虑除这两个 $\texttt{a}$ 以外的 $\texttt{a}$，由于这些 $\texttt{a}$ 不能连续出现，所以这些 $\texttt{a}$ 每个后要么接一个非 $\texttt{a}$ 的字符，要么放在字符串尾。所以，字符串最前面可以放连续两个 $\texttt{a}$，当且仅当 $cnt-1 \le len-cnt+1$ （注意：从前往后第二个 $\texttt{a}$ 后也要接非 $\texttt{a}$ 的字符）。

可行性知道了，那还要构造最优解。显然，我们把所有非 $\texttt{a}$ 的字符排序，在相邻两个字符间依次插入 $\texttt{a}$ 直至 $\texttt{a}$ 用完。如果 $\texttt{a}$ 没有用完则一定还剩 $1$ 个 $\texttt{a}$，放在串最后即可。

例：$\texttt{baaaaaabcc}$ 最优解为 $\texttt{aababacaca}$。

##### Case 2.2.2 最前面不能放连续两个 a

那么，最前面只能放一个 $\texttt{a}$。

在其之后一定会接第二小的字符，不妨设为 $\texttt{b}$。

那么，后面不能再出现形如 $\texttt{ab}$ 这样的串了。

若字符种类 $\le 2$，所有的 $\texttt{a}$ 应放在所有的 $\texttt{b}$ 之后（否则一定会出现形如 $\texttt{ab}$ 这样的串）。如 $\texttt{bbabaaaaa}$ 的最优解为 $\texttt{abbbaaaaa}$。

否则，我们可以在最前面的 $\texttt{b}$ 后接所有的 $\texttt{a}$，再接一个第三小的字符（不妨设为 $\texttt{c}$ ），然后剩下的字符放置的位置没有限制，直接从小到大排序即可。如 $\texttt{bbaaaaaaaaaccdd}$ 的最优解为 $\texttt{abaaaaaaaacbcdd}$。

[Code](https://codeforces.com/contest/1530/submission/122937065)


---

## 作者：遮云壑 (赞：5)

## Description
- 给一些字符，你需要构造一个字符串，使得它的每一个前缀子串的公共前后缀最小
- 若有多种情况，输出字典序最小的。
## Solution
这题分类很烦，很多大佬都是清晰地直接分类，但是我更想还原一种思考的过程，这是我们在考场上更需要的。

这种毫无思路的题，拿到只好暴力打表玩数据。。

我们惊讶得发现，大部分串的答案（最长公共前后缀）都为1 。

顺着这个思路往下走，如何构造1 。我们设字典序最小的那个字母为 $a$ ，第二小为 $b$ ，第三小为 $c$

首先肯定 $aa$ 开头，如果再接 $a$ ， $aaa$ 的答案就为2了，那么我们接 $b$ ，$aab$ 再接 $a$ 依然答案为1，所以问题不大，继续上 $a$ ，然后类推，最后串的开头应该是这样 $aabababab...$ 对于 $c$ 及其以后的字母，接在 $ab$ 后面，所以我们构造出了一种串，形如 $aababab..ccddeeffggxxyyzz$ 
如果 $b$ 不够用， $c$ 接上，效果一样的

然而这种情况不能满足所有数据，以上的情况要使 $a$ 少于一半，否则可能出现 $aabababcdaaaaaa$ 的情况，答案就为2了，而我们依然要使答案为1，怎么办呢。只有第二位填 $b$ 了，那么后面填再多的 $a$ 也只会使答案为1，要使字典序最小，就在 $b$ 后面疯狂填 $a$ ，但是后面不能出现 $ab$ 了，所以在 $a$ 之后填一个 $c$ ，在案字典序填。最后形如 $abaaaaaaaaaaaaacbcddeeff$

当然，答案会不会是0呢，当然可能。细心的小伙伴应该已经发现了，我在上面的每一个串后面的乱七八糟的字母都打了两个，其实想一想，如果有一个字母仅出现了一次，那么答案一定为0，我们只要找到一个字典序最小的扔到前面然后剩下的字母按顺序输出就行了。

还有一个显然的情况，样例已经友好地给我们了，就是仅有一种字母，直接输出吧。

## code
细节超多，慢慢调吧

[出门右转](https://codeforces.com/contest/1530/submission/134021829)

---

## 作者：LRL65 (赞：3)

一道很好的构造题。

思路：

分类是一个难点。

### 情况1：只有一种字母

直接输出即可。
    
    
### 情况2：有一个字母只出现一次

先输出这个字母，然后按照**字典序**依次输出。

### 情况3:字典序最小的字母出现数量小于 $\dfrac{|s|+1}{2}$

那么就可以这样构造（ $x$ 表示字典序最小的字母，$y$ 表示其他字母）：

xxyxyxy……xyyy……y


此时 $f(s)=1$ 且字典序最小。

### 情况4:字典序最小的字母出现数量大于 $\dfrac{|s|+1}{2}$

这种情况又分为两类。

#### （1）只有两种字母

那么就可以这样构造（ $x$ 表示字典序最小的字母，$y$ 表示其他字母）：

xyy……yxx……x


此时 $f(s)=1$ 且字典序最小。


#### （2）不止两种字母

那么就可以这样构造（ $x$ 表示字典序最小的字母，$y$ 表示字典序第二小的字母， $z$ 表示第三小的字母，$q$ 表示剩下的所有字母）：

xyxx……xzqq……q


此时 $f(s)=1$ 且字典序最小。



------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a[30];
string s;
int main() {
	cin>>t;
	while(t--) {
		cin>>s;
		memset(a,0,sizeof(a));
		int cnt=0;
		for(int i=0;i<s.size();i++) {
			if(a[s[i]-'a'+1]==0)cnt++;
			a[s[i]-'a'+1]++;
		}
		if(cnt==1) {
			cout<<s<<endl;
			continue;
		}
		bool flag=0;
		for(int i=1;i<=26;i++)
			if(a[i]==1) {
				cout<<(char)(i+'a'-1);
				a[i]--;
				for(int i=1;i<=26;i++)
					for(int j=1;j<=a[i];j++)
						cout<<(char)(i+'a'-1);
				cout<<endl;
				flag=1;
				break;
			}
		if(flag)continue;
         int x=1;
		while(a[x]==0)x++;
		int y=x+1;
        while(a[y]==0)y++;
        if(2*a[x]<=s.size()+2) {
			cout<<(char)(x+'a'-1)<<(char)(x+'a'-1);
			a[x]-=2;
			for(int i=1;i<=a[x];i++) {
				while(a[y]==0)y++;
				cout<<(char)(y+'a'-1);
				cout<<(char)(x+'a'-1);
				a[y]--;
			}
                        a[x]=0;
			for(int i=1;i<=26;i++)
				for(int j=1;j<=a[i];j++)
					cout<<(char)(i+'a'-1);
			cout<<endl;
            continue;
		}
		if(cnt==2) {
			for(int i=1;i<=26;i++)
				if(a[i]>0) {
					cout<<(char)(i+'a'-1);
					a[i]--;
					for(int j=i+1;j<=26;j++)
						for(int k=1;k<=a[j];k++)
							cout<<(char)(j+'a'-1);
					for(int k=1;k<=a[i];k++)
						cout<<(char)(i+'a'-1);
					cout<<endl;
					break;
				}
			continue;
		}
        cout<<(char)(x+'a'-1)<<(char)(y+'a'-1);
        a[x]--;a[y]--;
        for(int i=1;i<=a[x];i++)
            cout<<(char)(x+'a'-1);
        a[x]=0;
        y++;
        while(a[y]==0)y++;
        cout<<(char)(y+'a'-1);
        a[y]--;
        for(int i=1;i<=26;i++)
            for(int j=1;j<=a[i];j++)
                cout<<(char)(i+'a'-1);
        cout<<endl;
	}
}
```


---

## 作者：1234567890sjx (赞：1)

沟石分讨，重度怀疑【】是否可以在考场上写出此题。

考虑大分类讨论：

+ 若 $S$ 串内只有一个不同的字符，则直接输出这个字符（必然没有其他情况）
+ 若 $S$ 中存在字母出现次数恰好为 $1$，则考虑选取这一类字符中 ASCII 最小的字符输出，其余字符按照 ASCII 从小到大输出。这样可以证明 $f(S)=0$。
+ 其余情况可以构造出 $f(S)=1$：
  + 若 ASCII 最小的字符 $x$ 出现次数小于等于字符串长度的一半，则可以先构造 $x$，然后其余字符组成的可重集合 $S'$：每一次先构造一个 $x$，然后从 $S'$ 中取出 ASCII 最小的字符。若此时 $x$ 已经用完则将 $S'$ 中剩下的字符按照 ASCII 顺序从小到大输出即可。
  + 否则，继续分类讨论：
    + 若此时字符串中只有两种不同的字符，则令 $x$ 为字典序较小者，$y$ 为字典序较大者，构造字符串 $S'=\overline{xyy\ldots yxx\ldots x}$，此时 $f(S')=1$。
    + 若此时字符串中有至少三种不同的字符，则令 $x$ 为字典序较小者，$y$ 为次小者，$z$ 为第三小者，则可以构造 $S'=xyxx\ldots xz$ 剩下的字母按照 ASCII 从小到大输出满足 $F(S')=1$。

因此总的构造时间复杂度为 $O(n)$。

```cpp
const int N=1000100;
const int mod=998244353;
VI z[N];
void solve(unsigned __testid=1){
    string s;
    cin>>s;
    int box[26]={0};
    for(auto &x:s)
        ++box[x-'a'];
    int diff=0;
    F(i,0,25)
        if(box[i])
            ++diff;
    if(diff==1)
        cout<<s<<'\n';
    else{
        int mi=1e18;
        F(i,0,25)
            if(box[i])
                mi=min(mi,box[i]);
        if(mi==1){
            F(i,0,25)
                if(box[i]==1){
                    --box[i];
                    putchar(i+'a');
                    break;
                }
            F(i,0,25)
                F(j,1,box[i])
                    putchar(i+'a');
            puts("");
        }else{
            int id;
            F(i,0,25)
                if(box[i]){
                    id=i;
                    break;
                }
            int n=s.size();
            if(box[id]*2-2<=n){
                int p=0;
                --box[id];--box[id];
                putchar(id+'a');
                putchar(id+'a');
                while(box[id]){
                    --box[id];
                    while(p==id||!box[p])
                        ++p;
                    --box[p];
                    putchar(p+'a');
                    putchar(id+'a');
                }
                F(i,p,25)
                    F(j,1,box[i])
                        putchar(i+'a');
                puts("");
            }else{
                if(diff==2){
                    int id2=id+1;
                    while(!box[id2])
                        ++id2;
                    putchar(id+'a');
                    while(box[id2]--)
                        putchar(id2+'a');
                    while(--box[id])
                        putchar(id+'a');
                    puts("");
                }else{
                    int id2=id+1;
                    while(!box[id2])
                        ++id2;
                    int id3=id2+1;
                    while(!box[id3])
                        ++id3;
                    putchar(id+'a');
                    putchar(id2+'a');
                    while(--box[id])
                        putchar(id+'a');
                    --box[id2];
                    putchar(id3+'a');
                    --box[id3];
                    F(i,0,25)
                        F(j,1,box[i])
                            putchar(i+'a');
                    puts("");
                }
            }
        }
    }
}
int32_t main(){
    // ios_base::sync_with_stdio(0) ;
    // cin.tie(nullptr);
    int T;
    cin>>T;
    // T=1;
    F(_,1,T)
        solve(_);
    return 256;//main can return 256
}
```

---

## 作者：123zbk (赞：1)

构造题。分几种情况讨论：

- 只由一种字符构成：直接输出即可。

 然后考虑字典序最小的字母（以后统称 $a$）出现的次数：

- 如果 $a$ 出现的次数 $\le\dfrac{|s|+2}{2}$ ：

我们首先可以先放一个 $a$，每次在 $a$ 之后按字典序接一个其他的字母（以后统称 $d$），最后把剩下的都填上就行了。

构造：$\texttt{aadad\dots adddd}$，此时 $f(s)=1$ 且字典序最小。

- 如果 $a$ 出现的次数 $\ge\dfrac{|s|+2}{2}$ ：

这里又分两种情况：

情况 1：如果只由两种字符组成：

此时不能像上一种情况那样构造了。

因为此时 $a$ 的个数多于字符串第二小字母（以后统称 $b$）的个数，所以剩下的是一连串 $a$，此时就会使 $f(s)=2$。

所以第二位必须放 $b$。但是如果第三位仍然放 $a$，因为 $a$ 的数量多，最后一定会形成 $ab$，此时 $f(s)=2$。所以必须将 $b$ 全部放完再放 $a$。

构造：$\texttt{abb\dots bbaaa\dots aaa}$，此时 $f(s)=1$ 且字典序最小。

情况 2：如果超过了两个字符：

首先前两位依然只能是 $ab$。因为至少有三种字符，所以现在还是不能像上一种情况构造。现在可以直接把所有的 $a$ 接到后面，然后用一个字典序第三小的字母（以后统称 $c$）来间隔一下，就可以使 $f(s)=1$ 了。

构造：$\texttt{abaaa\dots aaacddd\dots ddd}$，此时 $f(s)=1$ 且字典序最小。

- 如果存在只出现一次的字符：
那么把它放在第一位，剩下的按字典序排，可以保证 $f(s)=0$。

## code
```cpp
#include <bits/stdc++.h>
using namespace std;
int T,c[30],cnt;
string s;
int main()
{
    cin>>T;
    while(T--)
    {
        cin>>s;
        memset(c,0,sizeof(c));
        cnt=0;
        for(int i=0;i<s.size();i++)
        {
            int x=s[i]-'a'+1;
            if(not c[x])
            {
                cnt++;
            }
            c[x]++;
        }
        if(cnt==1)//只有一个字母 
        {
            cout<<s<<endl;
            continue;
        }
        bool flag=0;
        for(int i=1;i<=26;i++)//有只出现一次的字母  放到最前面 
        {
            if(c[i]==1)
            {
                flag=1;
                printf("%c",i+'a'-1);
                c[i]--;
                break;
            }
        }
        if(flag)
        {
            for(int i=1;i<=26;i++)
            {
                for(int j=1;j<=c[i];j++)
                {
                    printf("%c",i+'a'-1);
                }
            }
            puts("");
            continue;
        }
        int x=1;
        while(not c[x])//字典序第一小 
        {
            x++;
        }
        int y=x+1;
        while(not c[y])//第二小 
        {
            y++;
        }
        if(2*c[x]<=s.size()+2)//字典序最小的出现数量小于(s+1)/2  xxyxyxy……xyyy……y
        {
            printf("%c%c",x+'a'-1,x+'a'-1);
            c[x]-=2;
            for(int i=1;i<=c[x];i++)
            {
                while(not c[y])
                {
                    y++;
                }
                printf("%c%c",y+'a'-1,x+'a'-1);
                c[y]--;
            }
            c[x]=0;
            for(int i=1;i<=26;i++)
            {
                for(int j=1;j<=c[i];j++)
                {
                    printf("%c",i+'a'-1);
                }
            }
            puts("");
            continue;
        }
        if(cnt==2)//只有两个字母 xyy……yxx……x
        {
            for(int i=1;i<=26;i++)
            {
                if(c[i]>0)
                {
                    printf("%c",i+'a'-1);
                    c[i]--;
                    for(int j=i+1;j<=26;j++)
                    {
                        for(int k=1;k<=c[j];k++)
                        {
                            printf("%c",j+'a'-1);
                        }
                    }
                    for(int j=1;j<=c[i];j++)
                    {
                        printf("%c",i+'a'-1);
                    }
                    puts("");
                    break;
                }
            }
            continue;
        }//不只两个  xyxx……xzqq……q
        printf("%c%c",x+'a'-1,y+'a'-1);
        c[x]--;
        c[y]--;
        for(int i=1;i<=c[x];i++)
        {
            printf("%c",x+'a'-1);
        }
        c[x]=0;
        y++;
        while(not c[y])//字典序第三小 
        {
            y++;
        }
        printf("%c",y+'a'-1);
        c[y]--;
        for(int i=1;i<=26;i++)
        {
            for(int j=1;j<=c[i];j++)
            {
                printf("%c",i+'a'-1);
            }
        }
        puts("");
    }
    return 0;
}
```

---

## 作者：Vsinger_洛天依 (赞：1)

# [Minimax](https://www.luogu.com.cn/problem/CF1544E)

逆天冲刺 NOIP 题单可做题之十(字符串之二)。

逆天分讨题，看到就难受。

我们要考虑最小化前缀函数且字符串最小，也就是尽可能不要让前缀和后缀相同，同时最小化因此我们考虑分类讨论。

- 如果字符串内所有字符都是相同的。

    直接输出最小的情况即可，因为前后调转不会产生影响。

- 如果所有字符串都是不同的。

    直接输出最小的情况即可，因为前后调转同样不会产生影响。

- 当字符串内有字符出现且仅出现了一次。

    此时我们发现其可以让字典序最小的只出现了一次的字符放在最前面，此时我们可以发现其 $f$ 为最小。

- 如果当前字符串内最小的字符出现了小于一半的次数。

    我们先把最小值存到第一位和第二位，然后后面按照**当前**(指放目前的次小值,最小值)的情况用次小值,最小值的顺序放即可。

- 如果当前字符串内最小的字符出现了大于一半的次数且只由两种字符形成。

    我们先用一个最小值存到第一位，然后后面放所有次小值，最后放所有最小值即可。

- 最小的字符出现了大于一半的次数而且出现次数大于等于三次。

    我们先放一个最小值，然后放一个次小的隔开，接下来把所有最小值放完，放一个次次小值，接下来按照字典序排即可。

由于代码太长了我压了一下。


```cpp
inline void In(){
    t=read();
	while(t--){
		int cnt=0;
        memset(c,0,sizeof(c));
        cin>>s;len=s.size();
        for_(i,0,len-1){a[i+1]=(int)(s[i]-'a');c[(int)(s[i]-'a')]+=1;}
        sort(a+1,a+len+1);
        if(a[1]==a[len]){put(s,'\n');continue;}
        int f=1;for_(i,1,len-1){if(a[i]==a[i+1]){f=0;break;}}
        if(f){for_(i,1,len)putchar(char(a[i]+'a'));puts("");continue;}
        int temp=-1;
        for_(i,0,25){if(c[i]==1){temp=i;break;}}	
        if(temp!=-1){putchar(char(temp+'a'));c[temp]--;for_(i,0,25){for_(j,1,c[i])putchar((char)(i+'a'));}puts("");continue;}
        temp=-1;
        for_(i,0,25){if(c[i]!=0){temp=i;break;}}
        if(c[temp]*2<=len+2){putchar((char)(temp+'a'));putchar((char)(temp+'a'));c[temp]-=2;while(c[temp]>=1){int temp2=-1;for_(i,temp+1,26){if(c[i]!=0){temp2=i;break;}}putchar((char)(temp2+'a'));putchar((char)(temp+'a'));c[temp2]--;c[temp]--;}for_(i,0,25){for_(j,1,c[i]){putchar((char)(i+'a'));}}puts("");continue;}
        int temp2=-1;for_(i,temp+1,25){if(c[i]!=0){temp2=i;break;}}
        if(c[temp]+c[temp2]==len){putchar((char)(temp+'a'));c[temp]--;for_(i,1,c[temp2]){putchar((char)(temp2+'a'));}for_(i,1,c[temp]){putchar((char)(temp+'a'));}puts("");continue;}
        temp2=-1;for_(i,temp+1,26){if(c[i]!=0){temp2=i;break;}}
        int temp3=-1;for_(i,temp2+1,25)if(c[i]!=0){temp3=i;break;}putchar((char)(temp+'a'));c[temp]--;putchar((char)(temp2+'a'));c[temp2]--;
        for_(i,1,c[temp]){putchar((char)(temp+'a'));}
        c[temp]=0;putchar((char)(temp3+'a'));c[temp3]--;for_(i,0,25)for_(j,1,c[i])putchar((char)(i+'a'));puts("");
	}
}
```

---

## 作者：WeLikeStudying (赞：1)

**题意**
- 给你一串字符，让你将其重排，使得对该字符串的前缀数组（是的就是kmp用的）的最大值最小，输出字典序最小的满足要求的重排方案。
- 字符长度总和不超过 $10^5$ 。

**做法**
- 你知道前缀数组的很多性质，但显然这里用不上，我们需要考虑最简单的一些问题：什么情况下，答案很容易求？
- **全是一种字符**！重排显得毫无意义，前缀数组最大值为$|s|$，直接输出原字符串。
- **有一种字符只有一个**！将那个字符调到最前面，前缀数组全 0，找到字典序最小的只有一个的字符调到前面，其余按照字典序输出。
- 如果是一个任何种字符都有多于一个的那显然至少前缀数组的最大值为 1，然后我们就直接想一下什么情况的最大值为 1。
- 容易给出一组构造：$xy\dots yx\dots x$，$x$是一种字符，$y$是其它字符，所以不是前面两种情况我们只考虑最大值等于 1 的情况
- 考虑什么情况字典序最小？
- 显然最小的字符要最先出现，且不能出现多于两次
- 我们考虑什么情况能够出现两次，什么情况不能
- 如果最小字符在开头连续出现了两次$aay\dots $后面决不能（而且也是唯一要防止的）就是**连续出现两个**$a$，我们可以$aayayayayay\dots$的错开放（其实这样也同时使得字典序最小），如果这样还不能避免的话就只能出现一次，否则我们可以使$y$按字典序输出。
- 如果最小字符在开头出现了一次，那第二个字符后显然可以放很多连续的最小字符$ayaa\dots ay\dots$，发现问题了吗？$ay$与$ay$重叠了，处理方法是**如果存在字典序次于 $y$ 但存在的其它字母**就将它顶上第二个$y$，如果没有，非常遗憾，只能采取$ay\dots ya\dots a$的方式输出。
- [代码实现](https://www.luogu.com.cn/paste/wds1qfsg)。

---

## 作者：lty_ylzsx (赞：0)

## 题意

给一个字符串 $s$，要求将 $s$ 重新排列得到 $t$，使得：

* 对于 $t$ 的每个前缀 $i$，定义 $ f(i) $ 为前缀 $i$ 的 border，使得所有位置的 $ f(i) $ 最大值最小。

* 满足条件的 $t$ 的字典序最小。

## 思路分析

思路其实很简单清晰，即:

**大力分讨** 和 **大力特判**

~~然后瞎推就完了。~~

首先不难发现一个结论：

> 对于任意串 $s$，当 $s$ 中存在至少2种字符时，必然存在 $t$ 使得 $ f(t)=0 $ 或 $1$。

证明将在下文中体现。

然后约定几个变量:

1. $st$ 为 $s$ 中出现的字典序最小的字符。
2. $se$ 为 $s$ 中出现的字典序第二小的字符(如果存在至少两种字符)。
3. $th$ 为 $s$ 中出现的字典序第三小的字符(如果存在至少三种字符)。
4. $cnt_c$ 为 $s$ 中字符 $c$ 出现的次数。
5. $kinds$ 为 $s$ 中字符种数。

```cpp
for(int i='a';i<='z';i++)  cnt[i]=0;
st='z'+1;int kinds=0;
scanf(" %s",s+1);
n=strlen(s+1);
for(int i=1;i<=n;i++){
    if(!cnt[s[i]])  kinds++;
    cnt[s[i]]++;
    st=min(st,s[i]);
}
```

那么，开始酣畅淋漓的分讨特判吧~

---
### 壹.特判 $f(t)=0$.

不难发现，当且仅当 $\exists \ i,cnt_i=1$ 时，能够满足 $ f(i)=0 $.比如串 $s$ =$\tt{bababc}$，$t$ 显然为 $\tt{caabbb}$。

**code**

```cpp
bool b=0;
for(int i='a';i<='z';i++){
    if(cnt[i]==1){
        pc(i);--cnt[i];
        for(int j='a';j<='z';j++)
            while(cnt[j]-->0)  pc(j);
        b=1;pt;break;
    }
}
if(b)  continue;
```
---
### 贰.特判 $kinds=1$

直接输出即可。

```cpp
if(kinds==1){
    for(int i=1;i<=n;i++)  pc(st);
    pt;continue;
}
```
---
### 叁.对于 $f(t)=1$ 进行分讨

#### $1. kinds=2$

为了让字典序最小，显然要先尽可能多地输出 st (最多显然是2个),那么为了让 $f(t)=1$，接着分讨。

* $cnt_{st}=2$ 时，例如 $\tt{abbabbb}$，直接按字典序输出即可，即 $\tt{aabbbbb}$。

* $cnt_{st}=3$ 时，例如$abbaabb$，考虑先输出 2 个 $st$，再用 $se$ 分割一下，输出剩下的一个 $st$，再输出剩下的 $se$，即 $\tt{aababbb}$。

* $cnt_{st}>3$ 时，我们分讨要先输出几个 $st$。

    * $cnt_{st}-1>cnt_{se}+1$ 时，例如 $\tt{aabbaaaa}$ 不难发现此时 $st$ 一定会连着出现至少两次，(考虑用 $se$ 分割)，如果用两个 $st$ 开头，必然会令 $ f(t)=2 $，(比如 $\tt{aababaaa}$ )。所以必然要以一个 $st$ 开头。然后输出所有 $se$，(至于为什么输出所有的，显然 $ f(\tt{abaaaabb})=2 $)，最后输出剩下的 $st$，即 $\tt{abbaaaaa}$。

    * $cnt_{st}-1 \leq cnt_{se}+1$ 时，例如 $\tt{aabaabbbb}$ 不难发现此时 $st$ 可以被 $se$ 分隔开使得没有 $st$ 相邻，那么为了让字典序最小，我们用两个 $st$ 开头，接着循环输出$se st se st ……$即可。另外，由于 $cnt_{st}-2 < cnt_{se}$ 所以剩下的一定是 $se$。输出即可。即 $\tt{aabababbb}$。

**code**

```cpp
for(se=st+1;se<='z';se++)  if(cnt[se])  break;
if(kinds==2){
    if(cnt[st]==2){
        pc(st),pc(st),cnt[st]-=2;
        while(cnt[se]-->0)  pc(se);
    }
    else if(cnt[st]==3){
        pc(st),pc(st),cnt[st]-=2;
        pc(se),--cnt[se];
        pc(st),--cnt[st];
        while(cnt[se]-->0)  pc(se);
    }
    else{
        if(cnt[st]-1>cnt[se]+1){
            pc(st);cnt[st]--;
            while(cnt[se]-->0)  pc(se);
            while(cnt[st]-->0)  pc(st);
        }
        else{
            pc(st),pc(st),cnt[st]-=2;
            while(cnt[st] && cnt[se]){
                pc(se),pc(st);
                --cnt[st];--cnt[se];
            }
            while(cnt[se]-->0)  pc(se);
        }
    }
    pt;continue;
}
```
---
#### $2. kinds \geq 3$
* $cnt_{st}=2$ 以及 $cnt_{st}=3$ 时，方法同上。

* $cnt_{st}>3$ 时，与上文类似的，令 $els=n-cnt_{st}$ 。讨论：

    * $cnt_{st}-1>els+1$ 时，例如 $\tt{aabbaaacaac}$，上文已证，应使用一个 $st$ 开头，然后用一个 $se$ 分隔，接着输出所有 $st$ ，为了不重复出现 $st se$,我们再用 $th$ 分隔，然后以字典序输出剩下所有字符,即 $\tt{abaaaaaacbc}$。

    * $cnt_{st}-1\leq els+1$ 时，例如 $\tt{aababcabc}$,上文已证，应使用两个 $st$ 开头，然后用剩下的其他字符将剩下的 $st$ 分隔输出，输出完 $st$ 后按字典序输出剩下的其他字符即可。即 $\tt{aabababcc}$。

**code**

```cpp
if(kinds>=3){
    if(cnt[st]==2){
        pc(st),pc(st),cnt[st]=0;
        for(int i=st+1;i<='z';i++)
            if(cnt[i])
                while(cnt[i]-->0)  pc(i);
    }
    else if(cnt[st]==3){
        pc(st),pc(st);
        pc(se),--cnt[se];
        pc(st);cnt[st]=0;
        for(int i=st+1;i<='z';i++)
            if(cnt[i])
                while(cnt[i]-->0)  pc(i);
    }
    else{
        int els=n-cnt[st];
        if(cnt[st]-1>els+1){
            pc(st);--cnt[st];
            pc(se);--cnt[se];
            while(cnt[st]-->0)  pc(st);
            pc(th);--cnt[th];
            for(int i=st+1;i<='z';i++)
                if(cnt[i])
                    while(cnt[i]-->0)  pc(i);
        }
        else{
            pc(st),pc(st),cnt[st]-=2;
            for(int i=st+1;i<='z';i++){
                while(cnt[i] && cnt[st])
                    pc(i),pc(st),--cnt[i],--cnt[st];
                if(!cnt[st])
                    while(cnt[i]-->0)  pc(i);
            }
        }
    }
    pt;
}
```

真是一场酣畅淋漓的分讨啊。
---

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;

#define pc putchar
#define read read()
#define pt puts("")
inline int read
{
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9') {if(c=='-')  f=-1;c=getchar();}
    while(c>='0'&&c<='9')   x=(x<<3)+(x<<1)+c-'0',c=getchar();
    return f*x;
}
void write(int x)
{
    if(x<0)  pc('-'),x=-x;
    if(x>9)  write(x/10);
    pc(x%10+'0');
    return;
}
#define N 100010
int q,n;
char s[N];
int cnt[130];
char st='z'+1,se,th;
signed main()
{
    #ifndef ONLINE_JUDGE
        freopen("lty.in","r",stdin);
        freopen("lty.out","w",stdout);
    #endif
    q=read;
    while(q-->0){
        for(int i='a';i<='z';i++)  cnt[i]=0;
        st='z'+1;int kinds=0;
        scanf(" %s",s+1);
        n=strlen(s+1);
        for(int i=1;i<=n;i++){
            if(!cnt[s[i]])  kinds++;
            cnt[s[i]]++;
            st=min(st,s[i]);
        }
        bool b=0;
        for(int i='a';i<='z';i++){
            if(cnt[i]==1){
                pc(i);--cnt[i];
                for(int j='a';j<='z';j++)
                    while(cnt[j]-->0)  pc(j);
                b=1;pt;break;
            }
        }
        if(b)  continue;
        if(kinds==1){
            for(int i=1;i<=n;i++)  pc(st);
            pt;continue;
        }
        for(se=st+1;se<='z';se++)  if(cnt[se])  break;
        if(kinds==2){
            if(cnt[st]==2){
                pc(st),pc(st),cnt[st]-=2;
                while(cnt[se]-->0)  pc(se);
            }
            else if(cnt[st]==3){
                pc(st),pc(st),cnt[st]-=2;
                pc(se),--cnt[se];
                pc(st),--cnt[st];
                while(cnt[se]-->0)  pc(se);
            }
            else{
                if(cnt[st]-1>cnt[se]+1){
                    pc(st);cnt[st]--;
                    while(cnt[se]-->0)  pc(se);
                    while(cnt[st]-->0)  pc(st);
                }
                else{
                    pc(st),pc(st),cnt[st]-=2;
                    while(cnt[st] && cnt[se]){
                        pc(se),pc(st);
                        --cnt[st];--cnt[se];
                    }
                    while(cnt[se]-->0)  pc(se);
                }
            }
            pt;continue;
        }
        for(th=se+1;th<='z';th++)  if(cnt[th])  break;
        if(kinds>=3){
            if(cnt[st]==2){
                pc(st),pc(st),cnt[st]=0;
                for(int i=st+1;i<='z';i++)
                    if(cnt[i])
                        while(cnt[i]-->0)  pc(i);
            }
            else if(cnt[st]==3){
                pc(st),pc(st);
                pc(se),--cnt[se];
                pc(st);cnt[st]=0;
                for(int i=st+1;i<='z';i++)
                    if(cnt[i])
                        while(cnt[i]-->0)  pc(i);
            }
            else{
                int els=n-cnt[st];
                if(cnt[st]-1>els+1){
                    pc(st);--cnt[st];
                    pc(se);--cnt[se];
                    while(cnt[st]-->0)  pc(st);
                    pc(th);--cnt[th];
                    for(int i=st+1;i<='z';i++)
                        if(cnt[i])
                            while(cnt[i]-->0)  pc(i);
                }
                else{
                    pc(st),pc(st),cnt[st]-=2;
                    for(int i=st+1;i<='z';i++){
                        while(cnt[i] && cnt[st])
                            pc(i),pc(st),--cnt[i],--cnt[st];
                        if(!cnt[st])
                            while(cnt[i]-->0)  pc(i);
                    }
                }
            }
            pt;
        }
    }
    return 0;
}
```

~~萌新第一篇题解，求求求管理员给过~~

---

## 作者：TernaryTree (赞：0)

恶心大分讨题差不多得了。

一眼看出如果有一个最小的字符只出现一次，那显然就把它放在第一个，剩下按字典序输出就行了。这样 $f(S')=0$。

然后如果全部一样就输出原串。$f(S')=n-1$。

接下来证明剩下的情况 $f(S')=1$。首先证明 $\ge 1$，因为不存在只出现一次的字符，把任意一个字符放在开头，同样字符为结尾的串 $p(s,i)$ 就至少是 $1$。然后证明 $\le 1$。考虑构造 $\texttt{a\ bbb\dots b \ ccc\dots c ddd\dots d \dots aaa\dots a}$ 即可满足要求。

写完这个交上去愤怒地发现 WA1 原因是要求**字典序最小**，火大。

逐位考虑。对于第一位我们显然填最小的出现过的字符 $\tt i$。这是可行的。

对于第二位，开始启动分讨。

- 能放 $\tt i$
  
  这个时候字符串形如 $\tt ii\ xixixixixi\dots xi\ xxx\dots $。
  
  $\tt x$ 是去掉 $\tt i$ 字符后依次填的结果。这个时候要求满足 $2(cnt_{\tt i}-1)\le n$，否则最后 $\tt i$ 会多出来造成与前面的两个 $\tt i$ 匹配使得 $f(S')=2> 1$。
  
- 不能放 $\tt i$（$2(cnt_{\tt i}-1)> n$）

  这个时候我们设 $\tt i$ 后面最小的出现过的是 $\tt j$。我扔一个 $\tt j$ 在开头 $\tt i$ 的后面，然后把所有 $\tt i$ 全扔出来，再扔上一个 $\tt k$ 是 $\tt j$ 后面最小的出现过的字符，保证 $\tt ij$ 不会重复出现；后面依次构造。形如 $\tt i\ j\ iii\dots i\ k\ xxx\dots x$。
  
  这时候还有一种情况是总共只有两种字符，因为 $\tt k$ 不存在就导致我们的构造十分地尴尬，这个时候我们只能有 $\tt i \ jjj\dots j\ iii\dots i$ 的构造了。
  
勾史代码：

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 1e5 + 10;

int T, n;
char s[maxn];
int cnt[26], tot;

signed main() {
	cin >> T;
	while (T--) {
		cin >> (s + 1), n = strlen(s + 1);
		memset(cnt, 0, sizeof(cnt));
		tot = 0;
		for (int i = 1; i <= n; i++) cnt[s[i] - 'a']++;
		for (int i = 0; i < 26; i++) tot += !!cnt[i];
		bool fl = 0;
		if (tot == 1) {
			cout << (s + 1) << endl;
			continue;
		}
		for (int i = 0; i < 26; i++) {
			if (cnt[i] == 1) {
				fl = 1;
				cout << (char) (i + 'a');
				for (int j = 0; j < 26; j++) {
					if (i == j) continue;
					while (cnt[j]--) cout << (char) (j + 'a');
				}
				cout << endl;
				break;
			}
		}
		if (fl) continue;
		for (int i = 0; i < 26; i++) {
			if (cnt[i]) {
				int x = cnt[i];
				cout << (char) (i + 'a');
				cnt[i]--;
				if (cnt[i] * 2 <= n) {
					cout << (char) (i + 'a');
					cnt[i]--;
					for (int j = 0; j < 26; j++) {
						if (i == j) continue;
						while (cnt[j]--) {
							cout << (char) (j + 'a');
							if (cnt[i]) {
								cout << (char) (i + 'a');
								cnt[i]--;
							}
						}
					}
					while (cnt[i]--) cout << (char) (i + 'a');
					cout << endl;
				} else {
					char k;
					for (int j = 0; j < 26; j++) {
						if (i == j) continue;
						if (cnt[j]) {
							cout << (char) (j + 'a');
							cnt[j]--;
							k = j;
							break;
						}
					}
					if (tot == 2) {
						while (cnt[k]--) cout << (char) (k + 'a');
						while (cnt[i]--) cout << (char) (i + 'a');
						cout << endl;
						break;
					}
					while (cnt[i]--) cout << (char) (i + 'a');
					for (int j = 0; j < 26; j++) {
						if (i == j || j == k) continue;
						if (cnt[j]) {
							cout << (char) (j + 'a');
							cnt[j]--;
							break;
						}
					}
					for (int j = 0; j < 26; j++) {
						if (i == j) continue;
						while (cnt[j]--) cout << (char) (j + 'a');
					}
					cout << endl;
				}
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1530E 题解



## 思路分析

记 $S[l,r]$ 表示 $S$ 中第 $l$ 个字符到第 $r$ 个字符构成的子串。

假设我们对字符串里的字符从小到大重新标号为 $\texttt a,\texttt  b,\texttt  c,\texttt  d,\texttt  e,\cdots$。

对 $S$ 进行分类讨论，记 $\alpha(S)$ 为 $S$ 中不同字符的数量：

- $\alpha(S)=1$：

  显然，此时所有 $f(T)=|S|-1$，直接输出原字符串 $S$ 即可。

- $\alpha(S)>1$：

  - 假如 $S$ 中存在仅出现一次的字符 $\texttt{x}$：

    此时 $f(T)$ 最小值为 $0$，排列成 $\texttt {xaaabbccccc}\cdots$ 的形式即可。

  - 假如 $S$ 中不存在仅出现一次的字符 $\texttt{x}$：

    猜测对于任意 $S$，$f(T)$ 最小值总是 $1$，注意到无论哪个字符开头都不影响，因此强制把 $\texttt a$ 放到开头。

    记 $S$ 中标号为 $\texttt a$ 的字符的个数为 $A$。

    - 可以以 $\texttt{aa}$ 开头：

      此时 $T$ 第三个字符如果还是 $\texttt a$，那么此时 $T[1,2]=T[2,3]$，不满足 $f(T)=1$ 的限制。

      因此 $T$ 开头必须是 $\texttt{aab}$，而剩下串中只要不出现 $\texttt{aa}$ 即可，这要求 $A\le \left\lfloor\tfrac n2\right\rfloor+1$。

      因此此时的 $T$ 应该形如 $\texttt{aababacadaddefff}\cdots$，即后面每两个字符之间插入一个 $\texttt{a}$。

    - 只能以 $\texttt{ab}$ 开头：

      此时应该有 $A>\left\lfloor\tfrac n2\right\rfloor+1$。

      - 能以 $\texttt{aba}$ 开头：

        只需使 $T$ 中没有 $\texttt{ab}$，因此把所有 $\texttt a$ 都放在第 $\texttt b$ 后面，当 $\alpha(S)>2$ 时，我们用一个 $\texttt c$ 接在 $\texttt a$ 后面即可。

        此时 $T$ 形如 $\texttt{abaaaaacbbccccd}\cdots$。

      - 只能以 $\texttt{abb}$ 开头：

        此时应该有 $\alpha(S)=2$，而不能出现 $\texttt{ab}$，所以把所有 $\texttt b$ 堆在一起即可。

        此时 $T$ 形如 $\texttt{abbbbbbaaaa}\cdots$。

先对 $S$ 排序然后分类讨论逐种情况解决即可。

时间复杂度 $\Theta(n\log n)$，其中 $n=|S|$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
inline void solve() {
	string str;
	char ch=0;
	map <char,int> cnt;
	cin>>str;
	sort(str.begin(),str.end());
	int n=str.length();
	for(int i=0;i<n;++i) ++cnt[str[i]];
	for(auto x:cnt) {
		int tot=x.second;
		if(tot==n) {
			cout<<str<<endl;
			return ;
		}
		if(tot==1&&ch==0) ch=x.first;
	}
	string ret;
	if(ch!=0) {
		ret.push_back(ch);
		for(int i=0;i<n;++i) if(str[i]!=ch) ret.push_back(str[i]);
	} else if(cnt[str.front()]<=(n/2)+1) {
		ch=str.front();
		ret.push_back(ch),ret.push_back(ch);
		cnt[ch]-=2;
		for(int i=0;i<n;++i) {
			if(str[i]!=ch) {
				ret.push_back(str[i]);
				if(cnt[ch]>0) {
					ret.push_back(ch);
					--cnt[ch];
				}
			}
		}
	} else if(cnt.size()==2) {
		for(auto &x:cnt) {
			ret.push_back(x.first);
			--x.second;
			if(ret.length()==2) break;
		}
		for(int i=1;i<=cnt[ret[1]];++i) ret.push_back(ret[1]);
		for(int i=1;i<=cnt[ret[0]];++i) ret.push_back(ret[0]);
	} else {
		for(auto &x:cnt) {
			ret.push_back(x.first);
			--x.second;
			if(ret.length()==3) {
				ch=x.first;
				break;
			}
		}
		char ch=str.front();
		while(cnt[ch]--) ret.push_back(ch);
		swap(ret[2],ret[ret.length()-1]);
		for(auto x:cnt) {
			if(x.first==ch) continue;
			for(int i=1;i<=x.second;++i) {
				ret.push_back(x.first);
			}
		}
	}
	cout<<ret<<endl;
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：南阳刘子骥 (赞：0)

题目大意是，给定我们一个字符串，我们需要对其进行重排，使得对重排后的字符串跑一遍 KMP 得到的 next 数组的最大值最小。如果有多种答案可以使得这个最大值最小，我们需要给出字典序最小的那一个。

大分类讨论中构造题。

首先我们考虑，如何才能让我们得到的 next 数组最小？  
换句话说，我们如何才能让前缀和后缀尽量不匹配？

首先，如果全局只有一种字符，那么我们肯定是无能为力的。  
否则我们可以把这个最大值限定在 $1$ 以内。

首先，如果有至少一种字符只出现了一次，我们可以将其中最小的那一个放到开头，剩下的部分排序之后接到后面即可，因为没有任何其他的子串可以和开头的这一个前缀匹配，next 数组最大就是 $0$，同时我们做到了字典序最小。

剩下就是所有的字符都出现了两次及以上的情况了。

我们将这些字符按照从小到大的顺序分别重编号为 $a$、$b$、$c$ 等。  
后面再说的时候就是按照新的编号了。

为了使得字典序最小，我们肯定是要把 $a$ 拿到串的开头的，然后让其他的后缀与 $a$ 匹配。

观察给的样例的第二个字符串，这给了我们一个关于做法的提示。

如果不是 $a$ 的字符数量足够，我们可以在开头再放一个 $a$，然后在后面交替填充一个非 $a$ 的字符和一个 $a$，直到 $a$ 用完，最后把剩下的部分都填充上非 $a$ 字符就可以了。  
同时为了字典序最小，我们在填充非 $a$ 字符的时候需要先排序再填充。  
这个方案阻止了连续的 $a$ 匹配上开头的两个 $a$，同时也阻止了后面的 $a$ 与一个非 $a$ 字符组合起来匹配上开头的两个字符，可以把最大值压缩到 $1$ 以内。

如果非 $a$ 字符数量不够呢？  
我们这时候肯定不能再在前面放两个 $a$ 了。

我们可以想到把前面的 $aa$ 替换成 $ab$，以防止多余的 $a$ 与 $aa$ 匹配。  
然后为了字典序最小，我们把剩下的 $a$ 都追加在后面。

我们这样做的同时还需要防止 $ab$ 被匹配。  
一个简单的方法就是在一串 $a$ 后面放一个 $c$，阻止可能的 $ab$ 的出现。

如果找不到 $c$ 呢？

我们就换种思路，把字符串构造成 $abbb \dots bbaa \dots aa$ 的形式。

否则，我们就按照上面的思路，构造形如 $abaa \dots aacbb \dots$ 的字符串。

此时回顾我们的分类讨论，可以发现我们分的这几类已经可以覆盖所有的情况了。

代码如下：

``` cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 300010;
int n;
char s[N];
int cnt[26], tot;
void solve()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = 1; i <= n; i++)
		cnt[s[i] - 'a']++;
	for(int i = 0; i < 26; i++)
		if(cnt[i])tot++;
	int flag = -1;
	for(int i = 0; i < 26; i++)
	{
		if(cnt[i] == 1)
		{
			flag = i;
			break;
		}
	}
	if(flag != -1)
	{//有只出现过一次的字符
		string res;
		res.push_back('a' + flag);
		cnt[flag]--;
		for(int i = 0; i < 26; i++)
			while(cnt[i]--)
				res.push_back('a' + i);
		cout << res << endl;
	}
	else if(tot == 1)
	{//只有一种字符
		printf("%s\n", s + 1);
	}
	else
	{
		string res;
		vector<int>v;
		for(int i = 0; i < 26; i++)
			if(cnt[i])
				v.push_back(i);
		if(n - cnt[v[0]] >= cnt[v[0]] - 2)
		{//非a字符数量足够
			res.push_back('a' + v[0]);
			res.push_back('a' + v[0]);
			cnt[v[0]] -= 2;
			for(int i = v[1]; i < 26; i++)
			{
				while(cnt[i]--)
				{
					res.push_back('a' + i);
					if(cnt[v[0]])
					{
						res.push_back('a' + v[0]);
						cnt[v[0]]--;
					}
				}
			}
		}
		else if(tot == 2)
		{//只有两种字符
			res.push_back('a' + v[0]);
			cnt[v[0]]--;
			while(cnt[v[1]]--)
				res.push_back('a' + v[1]);
			while(cnt[v[0]]--)
				res.push_back('a' + v[0]);
		}
		else
		{//可以找到c的情况
			res.push_back('a' + v[0]);
			cnt[v[0]]--;
			res.push_back('a' + v[1]);
			cnt[v[1]]--;
			while(cnt[v[0]]--)
				res.push_back('a' + v[0]);
			res.push_back('a' + v[2]);
			cnt[v[2]]--;
			for(int i = v[1]; i < 26; i++)
				while(cnt[i]--)
					res.push_back('a' + i);
		}
		cout << res << endl;
	}
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		tot = 0;
		for(int i = 0; i < 26; i++)
			cnt[i] = 0;
		solve();
	}
	return 0;
}
```



---

