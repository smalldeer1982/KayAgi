# Minlexes

## 题目描述

Some time ago Lesha found an entertaining string $ s $ consisting of lowercase English letters. Lesha immediately developed an unique algorithm for this string and shared it with you. The algorithm is as follows.

Lesha chooses an arbitrary (possibly zero) number of pairs on positions $ (i, i + 1) $ in such a way that the following conditions are satisfied:

- for each pair $ (i, i + 1) $ the inequality $ 0 \le i < |s| - 1 $ holds;
- for each pair $ (i, i + 1) $ the equality $ s_i = s_{i + 1} $ holds;
- there is no index that is contained in more than one pair.

 After that Lesha removes all characters on indexes contained in these pairs and the algorithm is over. Lesha is interested in the lexicographically smallest strings he can obtain by applying the algorithm to the suffixes of the given string.

## 说明/提示

Consider the first example.

- The longest suffix is the whole string "abcdd". Choosing one pair $ (4, 5) $ , Lesha obtains "abc".
- The next longest suffix is "bcdd". Choosing one pair $ (3, 4) $ , we obtain "bc".
- The next longest suffix is "cdd". Choosing one pair $ (2, 3) $ , we obtain "c".
- The next longest suffix is "dd". Choosing one pair $ (1, 2) $ , we obtain "" (an empty string).
- The last suffix is the string "d". No pair can be chosen, so the answer is "d".

In the second example, for the longest suffix "abbcdddeaaffdfouurtytwoo" choose three pairs $ (11, 12) $ , $ (16, 17) $ , $ (23, 24) $ and we obtain "abbcdddeaadfortytw"

## 样例 #1

### 输入

```
abcdd```

### 输出

```
3 abc
2 bc
1 c
0 
1 d```

## 样例 #2

### 输入

```
abbcdddeaaffdfouurtytwoo```

### 输出

```
18 abbcd...tw
17 bbcdd...tw
16 bcddd...tw
15 cddde...tw
14 dddea...tw
13 ddeaa...tw
12 deaad...tw
11 eaadf...tw
10 aadfortytw
9 adfortytw
8 dfortytw
9 fdfortytw
8 dfortytw
7 fortytw
6 ortytw
5 rtytw
6 urtytw
5 rtytw
4 tytw
3 ytw
2 tw
1 w
0 
1 o```

# 题解

## 作者：Neutralized (赞：6)

[题目链接](https://www.luogu.com.cn/problem/CF1422E)。  

另一篇题解里可能是觉得我以下写的内容太 naive 所以没写。  
但是我觉得还是有必要写一下。    

有关每个后缀所以考虑倒着 $dp$，设 $f_i$ 表示后缀 $i$ 的最优方案，同时存对应的字符串长度。  
对于 $s_i \ne s_{i+1}$ 直接 $f_i= s_i+f_{i+1}$，否则有转移：  

$$
f_{i} = \min(s_i+s_i+f_{i+2},f_{i+2})
$$

现在来想想为什么只从 $i+2$ 转移就够了呢。我们需要证明 $s_i+f_{i+1}$ 对 $f_i$ 没有贡献，没必要直接对着 $dp$ 分析，来感性理解一下。  

考虑一段 `ddddddd...[...dxcai...]` 的 `d` 连续段 $len \ge 3$，后面接的 `[...dxcai...]` 是直接把 $f_{i+2}$ 拼过来。而我们正在 $dp$ 这个串的开头：  

1. `dd[dxcai...]`：你发现，如果在 $i+1$ 删了 $(i+1,i+2)$，把 $f_{i+1}$ 拼过来等价于直接取用 $f_{i+2}$。否则把 $f_{i+1}$ 拼过来等价于 $s_i+s_i+f_{i+2}$。  
2. `dd[ddxcai...]`：“删中间”这种方案和删 $(i,i+1)$ 等价。所以你直接考虑删 $(i,i+1)$ 和 $(i+2,i+3)$，不需要考虑 $(i+1,i+2)$。  
3. `dd[dddxcai...]`：我们回到了论证的第一情况。  

此后同理。所以不需要从 $f_{i+1}$ 转移到 $f_i$。  
然后你注意一万个细节这道题就写出来了。时间复杂度 $O(n)$。 

一些我所知的细节：  
1. 注意 $dp$ 时方案全存下来空间不够，只存字符串的 开头 $10$ 位（长度 $\le 10$ 时）或 开头 $7$ 位和末尾 $2$ 位 即可。  
2. 更新上一条里的内容时应该一位一位更新，比如 $f_{i} = s_i+s_i+f_{i+2}$ 需要先 $f_i = s_i+f_{i+2}$ 再 $f_i = s_i+f_{i}$。也可能是我写丑了。  
3. 注意特判整个 $f_{i+2}$ 都是 $s_i$ 这个字符的情况，显然此时直接选 $f_{i+2}$ 更优。 

```cpp
#include <bits/stdc++.h>
using namespace std;

int n; char s[100003];
struct DP{ int p[27],len; char s[13]; }f[100003];
inline DP Generate(const char &c,const DP &x){
	DP t=x; ++t.len,t.s[0]=c; const int upd=t.len>10?7:9;
	for(int j=0;j<upd;++j) t.s[j+1]=x.s[j]; return t;
} //notice that you should generate DP step by step instead of straightly f[i+2]->f[i].

main(){ ios::sync_with_stdio(0),cin.tie(0);
	cin>>s+1,n=strlen(s+1);
	for(int i=0;i<26;++i) f[n].p[i]=s[n]-'a',f[n+1].p[i]=114514;
	f[n].s[0]=s[n],f[n].p[s[n]-'a']=114514,f[n].len=1; //第一个不等于 c 的字符的权值
	for(int i=n-1;i>=1;--i){
		if(s[i]!=s[i+1]){
			f[i]=Generate(s[i],f[i+1]);
			for(int j=0;j<26;++j) f[i].p[j]=(j==s[i]-'a'?f[i+1].p[j]:s[i]-'a');
		} else{
			if(f[i+2].p[s[i]-'a']==114514||f[i+2].p[s[i]-'a']<s[i]-'a') f[i]=f[i+2];
			else{
				f[i]=Generate(s[i],f[i+2]),f[i]=Generate(s[i],f[i]);
				for(int j=0;j<26;++j) f[i].p[j]=(j==s[i]-'a'?f[i+2].p[j]:s[i]-'a');
			}
		}
	} for(int i=1;i<=n;++i){
		cout<<f[i].len<<' ';
		if(f[i].len<=10){
			for(int j=0;j<f[i].len;++j)
				cout<<f[i].s[j]; cout<<endl;
		} else{
			for(int j=0;j<5;++j)
				cout<<f[i].s[j]; cout<<"...";
			cout<<f[i].s[8]<<f[i].s[9]<<endl;
		}
	}
}
```

---

## 作者：封禁用户 (赞：6)

# 简要题意

在一个字符串 $s$ 中，对于每个后缀，任意删掉一些相邻的相同的字符，使得字符串字典序最小。

注意：删掉之后拼起来再出现的相邻相同字符不能够删除。

# 思路

**倍增好题**。

发现存在局部最优解（最优子结构），并且可以转移到其它结点，可以考虑使用 ```dp```。

那就设 $f _ i$ 表示 $[i , n]$ 经过一些操作，达成的字典序最小的字符串（求后缀最优解，从后往前遍历）。

可以得到状态转移：

$$

f_i = 

\begin{cases}

f_{i+1} + s_i, & s_i \neq s_{i+1},\\

\min \{f_{i+1} + s_i , f_{i+2}\} & s_i = s_{i+1}. \\
\end{cases}
$$

$s_i$ 表示第 $i$ 个字符，$\min$ 表示字典序更小的那个。

边界条件：$f_n = s_n$。

但是这样做的复杂度是 $\mathcal{O}(n^2)$。

## 字典序比较优化

瓶颈在于比较字典序。

考虑对字典序比较进行优化。

回顾字典序比较的过程，

过程是对于两个字符串，从头到尾一个个字符进行比较，遇到第一个字符不同时，就返回答案。

那么就可以有一个想法通过一些操作，快速找到第一个不同的字符。

可以考虑使用倍增优化，把两个串比较时，通过倍增找到 ```hash``` 值第一个不同的地方，这样字符串比较就能优化到 $\mathcal{O}(\log n)$。

## 输出优化

接下来的问题就是输出，

因为输出长字符只要输出前 $5$ 个和最后 $2$ 个。

所以可以对于前面的字符直接输出，后面的字符也可以写个倍增往后跳到需要的。

最后总的复杂度就是 $\mathcal{O}(n \log n)$。

# Code

```c++
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using i64 = long long ;
using ui64 = unsigned long long ;

const int N = 1e5 + 5 ;
const int base = 131 ;

char s[N];
int f[N] , g[N] , h[N];
ui64 Pow[100];
ui64 Hash[20][N];//自然溢出
int nxt[20][N];
int n;

void updata(int u, int v){
    v = h[v];
    h[u] = u;
    g[u] = g[v] + 1;//记录当前的长度
    nxt[0][u] = v;
    Hash[0][u] = s[u] - 'a';

    for(int i = 1; i <= 19; i++)
        nxt[i][u] = nxt[i-1][nxt[i-1][u]] , Hash[i][u] = Hash[i-1][u] * Pow[i - 1] + Hash[i-1][nxt[i-1][u]]; //处理hash倍增
// nxt是方便向后跳2^k的
}

int min(int x, int y){
    int tx = x , ty = y;
    
    x = h[x] , y = h[y];

    for(int i = 19; i >= 0; i--)
        if(nxt[i][x] && nxt[i][y] && Hash[i][x] == Hash[i][y])
            x = nxt[i][x] , y = nxt[i][y];//找到第一个不同的字符
        
    return Hash[0][x] < Hash[0][y]? tx: ty;//小细节不能写 <= 写 <= 会导致部分少删除
}

int main(){

    scanf("%s",s+1);

    n = strlen(s+1);

    Pow[0] = base;
    for(int i = 1; i <= 90; i++)
        Pow[i] = Pow[i - 1] * Pow[i - 1];//预处理 base 的 2^i 次方，方便将hash值拼起来

    for(int i = n; i >= 1; i--) {
        updata(i,i+1);//默认是接上字符

        if(i < n && s[i] == s[i+1] && min(i,i + 2) == i + 2) {//删除更优
            h[i] = h[h[i + 2]];
            g[i] = g[h[i + 2]];
        }
    }

    for(int i = 1; i <= n; i++) {
        printf("%d ",g[i]);

        int id = h[i];
        if(g[i] <= 10) {
            for(int j = id; j && j <= n; j = nxt[0][j])
                putchar(s[j]);
        } else {
            for(int j = 1; j <= 5; j++ , id = nxt[0][id])//前5个字符直接暴力找
                putchar(s[id]);
            
            printf("...");

            id = h[i];
            int len = g[i] - 2 ;

            for(int i = 19; i >= 0; i--)
                if(nxt[i][id] && (1<<i) <= len) len -= 1<<i , id = nxt[i][id];//倍增找最后两个字符
            
            for(int j = 1; j <= 2; j++ , id = nxt[0][id])
                putchar(s[id]);
        }

        puts("");
    }
    return 0;
}
```

## 牢骚

本来思路是完全正确的，但是我用了一个 ```Trie``` 树和递归找字符串，导致常数太大，真的气死人了。

---

## 作者：ycyaw (赞：5)

先考虑最朴素的$dp$，$f_i$表示第$i$位为开头的后缀答案字符串

倒着做，分两种情况转移：

1. 若$s_i=s_{i+1}$，考虑删或不删，$f_i=min(f_{i+2},s_i+s_i+f_{i+2})$

2. 否则删不了，$f_i=s_i+f_{i+1}$

其中$min$表示两个字符串字典序比较，加号表示字符串拼接

比较麻烦的是第一种情况，我们先令$f_i=f_{i+2}$，定义相同的两个字符都为$ch$。

若$f_i$为空，显然删掉更优

否则，若$ch<f_i$的第一位，显然不删更优；若$ch=f_i$的第一位，我们维护每个字符串的**最前面的不相同的两个相邻字符**的大小关系（如$fffg$，最前面的不相同的两个字符是$fg$），若递增（如例子中$f<g$），则不删更优，否则删了更优。

建立一个结构体来处理题目需要的输出格式，代码实现还是很简洁的。

$Code\ Below:$
```cpp
#include<bits/stdc++.h>
#define ts cout<<"ok"<<endl
#define ll long long
#define hh puts("")
#define pc putchar
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
using namespace std;
const int N=100005;
struct node{
    string pre,suf;
    int len,inc;
    node(){
        pre="",suf="";
        len=inc=0;
    }
    void ins(char ch){
        if(pre.size()&&ch!=pre[0]) inc=(ch<pre[0]);
        len++;
        if(suf.size()<2) suf=ch+suf;
        pre=ch+pre;
        if(pre.size()>10) pre.pop_back();
    }
};
node ans[N];
string s;
inline int read(){
    int ret=0,ff=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') ff=-1;ch=getchar();}
    while(isdigit(ch)){ret=ret*10+(ch^48);ch=getchar();}
    return ret*ff;
}
void write(int x){if(x<0){x=-x,pc('-');}if(x>9) write(x/10);pc(x%10+48);}
void writeln(int x){write(x),hh;}
void writesp(int x){write(x),pc(' ');}
signed main(){
    cin>>s;
    for(int i=s.size()-1;i>=0;i--){
        if(i+1<s.size()&&s[i]==s[i+1]){
            ans[i]=ans[i+2];
            if(ans[i].len&&(s[i]<ans[i].pre[0]||(s[i]==ans[i].pre[0]&&ans[i].inc))){
                ans[i].ins(s[i]);
                ans[i].ins(s[i]);
            }
        }
        else{
            ans[i]=ans[i+1];
            ans[i].ins(s[i]);
        }
    }
    for(int i=0;i<s.size();i++){
        writesp(ans[i].len);
        if(ans[i].len<=10) cout<<ans[i].pre<<endl;
        else cout<<ans[i].pre.substr(0,5)+"..."+ans[i].suf<<endl;
    }
    return 0;
}
```


---

## 作者：睿智的憨憨 (赞：2)

# CF1422E Minlexes 解题报告

## 题目大意

给定一条由小写字母组成的字符串 $s$，对于 $s$ 的每一个后缀（包括 $s$），删除若干组相邻的相同字母，使得最后把剩余部分拼接在起来的字典序最小，输出字符串长度和结果串，若结果串长度大于 $10$，依次输出输出前五个字符，省略号，以及最后两个字符。

## 解法分析

令 $n=|s|$。

首先：$1 \le n \le 10^5$。如果不是什么奇怪的东西，那么正解复杂度应该是 $O(n)$ 或 $O(n \log n)$ 了。带 $\log$ 估计很难，$O(n)$ 的话基本就是 $dp$ 了。

我们将原串中连续相同字母分成几个块，方便接下来的理解。举个例子，可以将字符串 `aabcdddeea` 分为 `aa`,`b`,`c`,`ddd`,`ee`,`a` 六个块。

由于 $O(n)$ 和 $O(n^2)$ 大致思路一样，所以先考虑 $O(n^2)$ 的做法：

令 $dp_i$ 为长度为后缀 $[i,n]$ 的结果串（注意，$dp$ 是 string 类型！），设 $i$ 在所处块中从后往前数是第 $k$ 个，由于从 $s_{i+k}$ 是另一个块的开始位置，所以答案肯定为 $[i,i+k-1]$ 的某个子序列与 $dp_{i+k}$ 相连，而 $[i,j+k-1]$ 中全是一样的字母，所以子序列之间的区别只有长度。那么选哪个子序列呢？我们发现 $k$ 的奇偶性在这里也很关键，所以对 $k$ 的奇偶性分类讨论。

若 $k$ 为奇数：此时子序列合法长度的集合为 $\{1,3,\cdots,k-1\}$，我们发现这不就是把 $dp_{i+1}$ 接上了 $S_i$ 嘛！所以 $dp_i$ 等于 $S_i+dp_{i+1}$（同 string 类型加法）。

若 $k$ 为偶数：此时子序列合法长度的集合为 $\{0,2,\cdots,k\}$，同样可以看作是把 $dp_{i+1}$ 接上了 $S_i$。**但是**，这还多了个 $0$，难不成子序列长度可以为 $-1$ 吗？所以 $dp_i$ 应该等于 $S_i+\min(dp_{i+1},dp_{i+k})$（同 string 类型 $\min$ 函数）。

至此，$O(n^2)$ 的解法就结束了，然而我们发现这个做法却并不能优化。

但是出题人他帮我们优化了啊！当字符串长度大于 $10$ 的时候我们只需输出前五个字符与后两个字符，所以我们的 $dp$ 只表示结果串的前 $10$ 个字符不就行了吗！此时时间复杂度为 $O(10 \times n)$。

你可能会有困惑，都给人家省略了，还怎么比较字符串大小啊？

一点儿都不用怕，只需要~~四种分类讨乱~~正常判断 $dp_{i+1}$ 与 $dp_{i+k}$ 就行啦，相信你在纸上推一推就能顿悟了！

当然了，输出的时候还要输出最后结果串长度与最后两个字符，额外开数组在转移时顺便记录就行啦，合理运用 STL 会让代码更好写哦。

## 参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
int n, k, sz[N];
string s, dp1[N], dp2[N];
char p[N];
int main(){
	cin >> s, n = s.size();
	s = ' ' + s;
	//初值 
	dp1[n + 1] = dp2[n + 1] = "";
	dp1[n] = s[n], dp2[n] = "";
	sz[n] = k = 1;
	//dp
	for (int i = n - 1; i >= 1; i--){
		if (sz[i + 1] < 10)
			dp1[i] = s[i] + dp1[i + 1];
		else if (sz[i + 1] == 10){
			dp1[i] = s[i] + dp1[i + 1].substr(0, 9);
			dp2[i] = dp1[i + 1].substr(8, 2);
		}
		else{
			dp1[i] = s[i] + dp1[i + 1].substr(0, 9);
			dp2[i] = dp2[i + 1];
		}
		sz[i] = sz[i + 1] + 1;
		if (s[i] == s[i + 1]){
			k++;
			if (k % 2 == 0 && dp1[i + k] < dp1[i])
				sz[i] = sz[i + k], dp1[i] = dp1[i + k], dp2[i] = dp2[i + k];
		}
		else
			k = 1;
	}
	//答案 
	for (int i = 1; i <= n; i++){
		cout << sz[i] << ' ';
		if (sz[i] <= 10)
			cout << dp1[i] << endl;
		else
			cout << dp1[i].substr(0, 5) << "..." << dp2[i] << endl; 
	}
	return 0;
}
```

---

## 作者：Grammar_hbw (赞：2)

这是一个使用栈的贪心做法。

## 转化问题

发现从前往后去删字符不好做，考虑从后往前，离线输出。

注意到题目说“可以删除两个相邻字符”，这等价于若当你把字符放到栈里的时候，栈顶恰好是同一个字符**且是前一个位置时压的**，那么你可以弹栈。

要求从栈顶到栈底的字典序最小。

**结论**：你一定会在弹栈会导致字典序变小的时候弹栈。证明：如果你这个时候不弹，你以后永远不会弹到这个位置，这样一定不优。

根据**结论**，只需要维护这个栈就可以了。

## 如何判定是否弹栈

根据**结论**，你需要比较弹栈和不弹栈时的字典序。记栈中最后一个和当前字符（$s_i$）不一致的字符是 $c$（不存在视为空字符，规定空字符最小。其实比较字典序时用空字符把所有字符串补成同一个长度是显然正确的。），那么 $c<s_i$ 等价于弹栈之后字典序会变小（因为不弹的话这个位置是等于 $s_i$ 的），反之当 $c>s_i$ 的时候弹栈后字典序会变大。模拟该过程即可 AC 。

## 实现细节

你可以另外使用 $26$ 个栈维护每一个字母的出现位置，这也方便你弹栈。

提示：如果你使用手写的栈，栈顶指针（尾后指针）为 ```tp``` ，那么 ```tp[-x]``` 就可以表示从栈顶往下第 $x$ 个位置。

时间复杂度和空间复杂度均为 $O((|\Sigma|+d)n)$ ，其中 $|\Sigma|$ 是字符集大小，$d$ 是输出字符的上限，在本题中分别为 $26$ 和 $10$ 。

Now, it's Code Time!

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=100007;
string s;
char ch[N],*tp=ch; //答案栈。
int ans[N],pos[26][N],*ttp[26]; //储存 26 个字母在栈中位置的栈。
string qwq[N]; //储存每一个位置要输出的内容。
void save(int o){ //处理并保存答案。
	int sz=tp-ch;
	ans[o]=sz;
	if(sz<=10) for(int i=-1;i>=-sz;i--) qwq[o]+=tp[i];
	else{for(int i=-1;i>=-5;i--) qwq[o]+=tp[i];qwq[o]+="...";qwq[o]+=ch[1];qwq[o]+=ch[0];}
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>s;
	int n=s.length();
	for(int i=0;i<26;i++) ttp[i]=pos[i];
	bool flg=0; //表示上一步有没有进栈，只有flg==1的时候才可以弹栈。
	for(int i=n-1;~i;i--){
		if((tp==ch)||(tp[-1]!=s[i])||(!flg)) *(ttp[s[i]-'a']++)=tp-ch,*(tp++)=s[i],flg=1; //栈为空或栈顶字符和当前字符不一致或上一步弹了栈，此时只能压栈。
		else{
			int num=-1,chr=-1;
			for(int j=0;j<26;j++) if(j!=s[i]-'a'&&ttp[j]!=pos[j]&&ttp[j][-1]>num) num=ttp[j][-1],chr=j+'a'; //处理出哪个字符是最后出现的，为空则num会保持为-1。
			if((!(~num))||(chr<s[i])) tp--,ttp[s[i]-'a']--,flg=0; //!(~num) 表示 num==-1，因为 -1 取反后为 0 。
			else *(ttp[s[i]-'a']++)=tp-ch,*(tp++)=s[i],flg=1;
		} //注意压栈和弹栈都要对两个栈进行处理。
		save(i); 
	}
	for(int i=0;i<n;i++) cout<<ans[i]<<' '<<qwq[i]<<'\n'; //输出答案。
}
```

---

