# [GCJ 2020 Qualification] Nesting Depth

## 题目描述

**简要题意**：给定一个数字字符串 $\mathbf{S}$，在其中插入最少数量的左右括号，使得生成的字符串是平衡的，并且每个数字 $d$ 恰好位于 $d$ 对匹配的括号内。

我们定义字符串中两个括号的**嵌套**为它们之间严格包含的子串。一个左括号和其右侧的一个右括号称为**匹配**，如果它们的嵌套为空，或者它们的嵌套中的每个括号都与另一个括号匹配。位置 $p$ 的**嵌套深度**是包含 $p$ 的匹配括号对的数量 $m$。

例如，在以下字符串中，所有数字都与其嵌套深度匹配：`0((2)1)`、`(((3))1(2))`、`((((4))))`、`((2))((2))(1)`。前三个字符串在保持数字顺序相同的情况下长度最短，但最后一个不是，因为 `((22)1)` 也包含数字 `221` 且更短。

给定一个数字字符串 $\mathbf{S}$，找到另一个由括号和数字组成的字符串 $\mathbf{S}'$，满足以下条件：

* $\mathbf{S}'$ 中的所有括号都与其他括号匹配；
* 从 $\mathbf{S}'$ 中移除所有括号后得到 $\mathbf{S}$；
* $\mathbf{S}'$ 中的每个数字等于其嵌套深度；
* $\mathbf{S}'$ 的长度最短。

## 说明/提示

**样例解释**

字符串 `()0000()`、`(1)0(((()))1)` 和 `(1)(11)000` 分别不是样例 #1、#2 和 #3 的有效解，因为它们不是最短的。此外，`1)(` 和 `)(1` 不是样例 #4 的有效解，因为它们包含未匹配的括号，且在数字 `1` 的位置嵌套深度为 0。

你可以通过移除题目描述中提到的示例字符串的括号来创建仅适用于测试集 2 的样例输入。

**数据范围**

- $1 \leq \mathbf{T} \leq 100$；
- $1 \leq \mathbf{S}$ 的长度 $\leq 100$。

**测试集 1（5 分，可见判定）**

- $\mathbf{S}$ 中的每个字符为 `0` 或 `1`。

**测试集 2（11 分，可见判定）**

- $\mathbf{S}$ 中的每个字符为 `0` 到 `9` 的数字（含）。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
0000
101
111000
1```

### 输出

```
Case #1: 0000
Case #2: (1)0(1)
Case #3: (111)000
Case #4: (1)```

# 题解

## 作者：abc1234shi (赞：5)

# 题意
题意其实就是插入括号，使得所有括号内的字符串和括号外的字符串都是**平衡字符串**。

平衡字符串的定义：字符串中每个**有出现**的字母（题目中是数字）**出现的次数都相同**。当然，如果出现只**一种字母（数字）**，则它本身就是平衡字符串。

比一般水题加强一点的是位置 $p$ 的嵌套深度是包含 $p$ 的匹配括号对的数量 $m$。也就是说，这个数字是几，它就要**被几个括号嵌套**。 

题目最重要的一点是，要使得答案字符串**长度最短**。

# 思路

好家伙，这不贪心配上字符串，~~淄博烧烤串吗~~？

题目让我们维护一个**答案字符串**：我们先定义一个变量 $sd$（深度的拼音缩写），再求出第 $i$ 个数字 $d$。

如果 $d>sd$ 也就是此数字**大于**当前深度，那就是要加深度了，将答案字符串加**左括号**，并将 $sd$ 加一。

如果 $d<sd$ 也就是此数字**小于**当前深度，那就是深度超了，将答案字符串加加**右括号**，并将 $sd$ 减一。

然后直接将这个数字**加入**答案字符串，最后可能还有的左括号没有匹配右括号，所以要输出剩下的 $sd$ 个右括号。

最后注意，输出时还要输出**测试用例编号**。我喜欢将数据总行数递减，所以先将数据总行数**存档**，后用存档的数据总行数**减去**现在的数据剩余行数（虽然比较麻烦）。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	int h=t;
	while(t--){
		string r="";
		string s;
		cin>>s;
		int l=s.length();
		int sd=0;
		for(int i=0;i<l;i++){
			int d=s[i]-'0'; 
		    while(d>sd){
            r+='(';
            sd++;
            }
            while(d<sd){
            r+=')';
            sd--;
            }
            r+=s[i];
		}
		while(sd>0){
        r+=')';
        sd--;
        }
        cout<<"Case #"<<h-t<<": "<<r<<endl; 
	}
	return 0;
} 

```
# 细节
- 每一轮循环后要进行**清空**。
- 每一次输出答案要进行**换行**。
- 遍历字符串时记得**从 $0$ 开始**（因为字符串的存储是从 $0$ 开始的）。

---

## 作者：wf2025 (赞：4)

字符串题。

## 思路

这个问题要求为**数字字符串插入最少数量**的括号，使得每个数字  $d$  **恰好**位于  $d$  对匹配括号内。解题关键在于根据相邻数字的差值动态插入括号。\
~~可以暴力~~，就只是 $O(TS)$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
string solve(string s) {
    string res;
    int depth = 0;
    for (char c : s) {
        int num = c - '0';
        while (depth < num) {
            res += '(';
            depth++;
        }
        while (depth > num) {
            res += ')';
            depth--;
        }
        res += c;
    }
    while (depth > 0) {
        res += ')';
        depth--;
    }
    return res;
}
int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        string s;
        cin >> s;
        cout << "Case #" << t << ": " << solve(s) << endl;
    }
    return 0;
}

```

[记录详情](https://www.luogu.com.cn/record/222350049)

---

## 作者：goIdie (赞：2)

## 思路

对于每一个字符串，我们新建一个空的字符串 $ans$ 来存储答案，用 $now$ 表示当前嵌套深度，初始为 $0$。

遍历字符串，将字符转化为 int 类型整数 $q$。接下来分三种情况。

- $q>now$，则需要增加嵌套深度，添加 $q-now$ 个左括号。

- $q<now$，则需要减少嵌套深度，添加 $now-q$ 个右括号。

- $q=now$，不需要增加或减少嵌套深度。

将括号添加至 $ans$ 后，把当前字符也添加进去。

最后将 $now$ 更新为 $q$。

遍历完成后，如果 $now>0$，说明还有未闭合的左括号，再添加 $now$ 个右括号。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,now;
string s,ans;
int main(){
    cin>>T;
    for(int t=1;t<=T;t++){
        cin>>s;
        ans="";
        now=0;
        for(char c:s){
            int q=c-'0';
            if (q>now){
                ans+=string(q-now,'(');
                now=q;
            }
			else if(q<now){
                ans+=string(now-q, ')');
                now=q;
            }
            ans+=c;
        }
        if(now>0){
            ans+=string(now,')');
        }
        cout<<"Case #"<<t<<": "<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：Hkb150429 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P13049)

## 题意

给定一个数字字符串 $\mathbf{S}$，在其中插入最少数量的左右括号，使得生成的字符串是平衡的，并且每个数字 $d$ 恰好位于 $d$ 对匹配的括号内。

## 思路

我们可以把 $\mathbf{S}$ 的每个字符转化为对应的数字 $n$，如果当前深度小于 $n$，插入`(`，增加深度直到等于 $n$，否则插入`)`，减少深度直到等于 $n$，在所有数字处理完毕后，插入`)`闭合所有剩余的括号。

## AC CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
int main() {
    cin>>t;
    for (int i=1;i<=t;i++) {
        string s;
        cin>>s;
        string new_s;
        int shen=0;
        for (int j=0;j<s.size();j++) {
            int n=s[j]-'0';
            while(shen<n) {
                new_s+='(';
                shen++;
            }
            while(shen>n) {
               new_s+=')';
               shen--;
            }
            new_s+=s[j];
        }
        while(shen>0) {
            new_s+=')';
            shen--;
        }
        cout<<"Case #"<<i<<": "<<new_s<<endl;
    }
    return 0;
}
```

---

## 作者：huhengrui2013 (赞：1)

### 题解：P13049 [GCJ 2020 Qualification] Nesting Depth

[传送门](https://www.luogu.com.cn/problem/P13049)

### 思路：
考虑贪心，从左到右遍历字符串，根据当前数字和前一个数字的差来决定插入多少左括号或右括号。

注意：遍历结束后，应插入右括号以平衡所有左括号。

### AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;


string f(string s){
    string ans="";
    int pre=0;
    for(char c:s){//遍历
        int cnt=c-'0';
        while(pre<cnt) {
            //如果当前数字 cnt 大于前一个数字 pre，插入 cut-pre 个左括号。
            ans+='(';
            pre++;
        }
        while(pre>cnt) {
            //如果当前数字 cut 小于前一个数字 pre，插入 pre-cut 个右括号。
            ans+=')';
            pre--;
        }
        ans+=c;
    }
    while(pre>0){//补全右括号
        ans+=')';
        pre--;
    }
    return ans;
}
int main() {
    int t;
    cin>>t;
    for(int i=1;i<=t;i++){//t组数据
        string s;
        cin>>s;
        cout<<"Case #"<<i<<": "<<f(s)<<endl;//按格式输出
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P13049#ide)

### 前言
这道题目要求我们在数字字符串中插入最少数量的括号，使得每个数字的嵌套深度等于其数值，并且所有括号都正确匹配。我们需要找到满足条件的最短字符串。

### 思路
我们逐个处理数字字符串中的每个字符，通过比较当前数字与前一个数字的差值来决定插入括号的数量和位置。具体来说，当遇到比当前深度大的数字时，插入相应数量的左括号来增加深度；当遇到比当前深度小的数字时，插入相应数量的右括号来减少深度。处理完所有数字后，还需要插入剩余的右括号来确保所有括号都正确闭合。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
void sv() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        string S;
        cin >> S;
        string res;
        int d = 0;
        
        for (char c : S) {
            int num = c - '0';
            while (d < num) {
                res += '(';
                d++;
            }
            while (d > num) {
                res += ')';
                d--;
            }
            res += c;
        }
        
        while (d > 0) {
            res += ')';
            d--;
        }
        
        cout << "Case #" << t << ": " << res << endl;
    }
}
int main() {
    sv();
    return 0;
}
```

---

## 作者：ARIS1_0 (赞：1)

## 题意

给出一个字符串 $S$，其中含有的字符为 `0` 到 `9`，现在你需要在字符串中添加括号，满足：

1. 若 $S_i=k$，则 $S_i$ 被嵌套在恰好 $k$ 层括号中。
2. 去掉所有数字后，剩下的是合法括号序列。
3. 字符串最短。

多测。数据范围：$1\le T\le100,1\le|S|\le100$。

## 思路

题面可以转化为：每次选择一段子串 $S_i\sim S_j$，随后使该子串的所有数字减去 $\min_{i\le k\le j} S_k$。代价为减去的值的两倍。求最小代价。

若有一长度为 $2$ 的子串 $S_i,S_j$ 且 $S_i<S_j$，我们的贪心策略肯定是先减去 $S_i$，再减去 $S_j-S_i$，因为第一次减去时是两个数同时减去，节省了代价。容易发现这样一定是优的。

考虑证明：

有子串 $S_i\sim S_j$ 且满足 $S_i< S_{i+1}\le\dots\le S_j$。若我们认为第一次操作令整个子串减去 $S_i$ 不优，则我们令子串中 $>S_i$ 的数减去 $S_{i+1}$，随后再单独减去 $S_i$，代价为 $(S_{i+1}+S_i)\times2$。若先令整个子串减去 $S_i$，那么 $S_{i+1}\leftarrow S_{i+1}-S_i$，随后再减去 $S_{i+1}$，总代价为 $(S_i+(S_{i+1}-S_i))\times2=S_{i+1}\times2$。很明显后者更优。随后我们继续按此策略更新 $S_{i+2},S_{i+3},\dots$ 即可。递减的子串序列情况类似。

回到原题面，我们对应的贪心策略就是**从外往里**套括号。具体地，我们建出差分数组 $c$，若 $c_i<0$ 则此处放置 `)`，若 $c_i>0$ 则此处放置 `(`，若 $c_i=0$ 不放置。放置数量为 $|c_i|$。同时记得在末尾也要放上 `)`。

## 代码


```cpp
string s;
int n,a[105],c;
inline void work(int id){
	cin>>s;
	n=s.size();
	memset(a,0,sizeof(a));
	for(int i=1;i<=n;i++)a[i]=s[i-1]-'0';//字符串转成数组
	printf("Case #%d: ",id);
	for(int i=1;i<=n+1;i++){//循环到 n+1，因为最后也有可能要放括号
		c=a[i]-a[i-1];//差分数组可以滚掉，因为前后项无联系
		if(c<0){
			c=abs(c);
			for(int i=1;i<=c;i++)putchar(')');
		}else{
			for(int i=1;i<=c;i++)putchar('(');
		}
		if(i<=n)cout<<a[i];
	}
	puts("");
}
int t;
int main(){
	t=read();
	for(int i=1;i<=t;i++)work(i);
	return 0;
}
```

---

## 作者：Jasoncwx (赞：0)

[题目传送门！](/problem/P13049)
## 题目思路
分三个大板块。

第一个板块先把第一个数字前面的括号输出，即输出 $s_0$ 个前括号。

第二个板块分为三种情况，定义 $dis=s_i-s_{i-1}$，表示当前数字与前一个数字相差的距离。
- 情况 1：若 $dis=0$，表示这两个数字相同，不需要进行任何操作。
- 情况 2：若 $dis<0$，表示当前数字小于前面的数字，那么我们就需要在当前数字之前输出 $-dis$ 个后括号。
- 情况 3：若 $dis>0$，表示当前数字大于前面的数字，那么我们就需要在当前数字之前输出 $dis$ 个前括号。

第三个板块，按照板块二中的步骤，我们会发现我们遗漏了最后一个数字后面的后括号。我们只需要再输出 $s_{n-1}$ 个后括号即可。

## 代码
```cpp
//By Jasoncwx
#include<bits/stdc++.h>
#define R register
#define us unsigned
#define ll long long
inline ll read(){R ll s=0,w=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}return s*w;}
using namespace std;
const int N=1e6+5;
void make_f(int n){
	while(n--)cout<<"(";
}
void make_b(int n){
	while(n--)cout<<")";
}
int main(){
	int T=read();
	for(int t=1;t<=T;t++){
		cout<<"Case #"<<t<<": ";
		string s;
		cin>>s;
		//板块 1
		int now=s[0]-'0';
		make_f(now);
		cout<<now;
		//板块 2
		for(int i=1;i<s.size();i++){
			int dis=s[i]-s[i-1];
			if(!dis){
				cout<<s[i];
				continue;
			}
			else if(dis<0){
				make_b(-dis);
				cout<<s[i];
			}
			else{
				make_f(dis);
				cout<<s[i];
			}
		}
		//板块 3
		make_b(s[s.size()-1]-'0');
		cout<<endl;
	}
	return 0;
}
/*
4
021
312
4
221
*/
```

---

## 作者：_seven_7k_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13049)
## 思路
一道贪心题。我们不难想到，题目要求从 $\mathbf{S}'$ 中移除所有括号后得到 $\mathbf{S}$，其实是保证贪心的每一步最优是没问题的，同时也是必须这么去做的。然后我们考虑如何让 $\mathbf{S}'$ 的长度最小。我们一位一位来看。设当前数字为 $u$，上一位数字为 $k$，因为每个数字等于其嵌套深度，所以当 $u > k$ 时，输出 $u$ 减 $k$ 个左括号，然后输出 $u$；当 $k > u$ 时，输出 $k$ 减 $u$ 个右括号，输出 $u$；当相等时，直接输出 $u$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
int main(){
	int n,k=0;
	cin>>n;
	int i,j,u;
	for(i=1;i<=n;i++){
		cin>>a;
		cout<<"Case #"<<i<<": ";
		for(j=1;j<=a[0]-'0';j++){
			cout<<"(";
		}
		cout<<a[0];
		k=a[0]-'0';
		for(j=1;j<a.size();j++){
			if(a[j]-'0'>k){
				for(u=k+1;u<=a[j]-'0';u++){
					cout<<"(";
				}
				k=a[j]-'0';
				cout<<k;
			}
			else if(a[j]-'0'<k){
				for(u=a[j]-'0'+1;u<=k;u++){
					cout<<")";
				}
				k=a[j]-'0';
				cout<<k;
			}
			else{
				cout<<k;
			}
		}
		for(j=1;j<=k;j++){
			cout<<")";
		}
		cout<<endl;
		k=0;
	}
	return 0;
}
```

---

## 作者：fjtMESSI10 (赞：0)

## 思路
这题我们可以先将字符转换为数值，表示该位置所需的括号嵌套深度，然后就判断，如果当前深度大于前一位置的深度，就添加当前深度减前一深度个左括号，否则如果当前深度小于前一位置的深度，添加前一深度减当前深度个右括号。然后在调整括号后，添加当前数字字符，最后添加剩余的右括号，确保所有左括号被匹配，然后按要求输出就可以了。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++) {
		string s;
		cin >> s;
		string h;
		int sum = 0;
		for (int j = 0; j < s.size(); j++) {
			int ans = s[j] - '0';
			int cnt = ans - sum;
			if (cnt > 0) {
				h += string(cnt, '(');
			} else if (cnt < 0) {
				h += string(-cnt, ')');
			}
			h += s[j];
			sum = ans;
		}
		h += string(sum, ')');
		cout << "Case #" << i << ": " << h << endl;
	}
	return 0;
}
```

---

