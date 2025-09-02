# [GCJ 2016 #1B] Getting the Digits

## 题目描述

你刚刚在一次国际谜题大会上结识了一位新朋友，并向他要了联系方式。第二天，你发现有人将一张纸条塞到了你的酒店房门下：

“致新朋友！我已经将我的电话号码中的每一个数字都替换成了其英文大写拼写（对于数字 $0$ 到 $9$，依次为 "ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"），然后把所有这些字母重新打乱，得到一个字符串 $\mathbf{S}$。你需要根据 $\mathbf{S}$ 推断出我的电话号码的位数以及具体的数字，不过我会告诉你，我的电话号码中的数字是非递减排列的。祝你好运……如果你能打通的话！”

你很想打电话告诉你的朋友，这种给联系方式的方式实在太让人抓狂了，但你得先把电话号码还原出来！那么，这个电话号码是多少？


## 说明/提示

**限制条件**

- $1 \leqslant \mathbf{T} \leqslant 100$。
- 保证每组数据都有唯一解。

**小数据集（11 分，测试集 1 - 可见）**

- $3 \leqslant \mathbf{S}$ 的长度 $\leqslant 20$。

**大数据集（12 分，测试集 2 - 隐藏）**

- $3 \leqslant \mathbf{S}$ 的长度 $\leqslant 2000$。

翻译由 GPT4.1 完成。

## 样例 #1

### 输入

```
4
OZONETOWER
WEIGHFOXTOURIST
OURNEONFOE
ETHER```

### 输出

```
Case #1: 012
Case #2: 2468
Case #3: 114
Case #4: 3```

# 题解

## 作者：chenzefan (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P13192)
## 前言
翻橙题，大水题，水题解，凑个数。
## 思路
由于字母被打乱，所以容易想到使用 map 计数。

观察 $0 \sim 9$ 的英文单词，可以发现有以下字母是唯一出现在一些单词里的。如：

- 字母 `Z`，只出现在 $0$ 的英文 `ZERO` 中。
- 字母 `W`，只出现在 $2$ 的英文 `TWO` 中。
- 字母 `U`，只出现在 $4$ 的英文 `FOUR` 中。
- 字母 `X`，只出现在 $6$ 的英文 `SIX` 中。
- 字母 `G`，只出现在 $8$ 的英文 `EIGHT` 中。

~~（怎么都是偶数啊！）~~

除去这些数字的英文，可以得到剩下几个英文的特性：

- 字母 `O`，剩下只出现在 $1$ 的英文 `ONE` 中。
- 字母 `T`，剩下只出现在 $3$ 的英文 `THREE` 中。
- 字母 `F`，剩下只出现在 $5$ 的英文 `FIVE` 中。
- 字母 `S`，剩下只出现在 $7$ 的英文 `SEVEN` 中。
- 字母 `I`，剩下只出现在 $9$ 的英文 `NINE` 中。

~~（怎么都是奇数啊！）~~

由此容易写出代码。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
signed main(){
	int t;map <char,int> mp,ans;
	scanf("%d",&t);
	for(int p=1;p<=t;p++){
		string s;cin>>s;mp.clear();ans.clear();
		for(int i=0;i<s.size();i++) mp[s[i]]++;
		//特殊的
		if(mp['Z']!=0) mp['E']-=mp['Z'],mp['R']-=mp['Z'],mp['O']-=mp['Z'],ans['0']=mp['Z'],mp['Z']=0;
		if(mp['W']!=0) mp['T']-=mp['W'],mp['O']-=mp['W'],ans['2']=mp['W'],mp['W']=0;
		if(mp['U']!=0) mp['F']-=mp['U'],mp['O']-=mp['U'],mp['R']-=mp['U'],ans['4']=mp['U'],mp['U']=0;
		if(mp['X']!=0) mp['S']-=mp['X'],mp['I']-=mp['X'],ans['6']=mp['X'],mp['X']=0;
		if(mp['G']!=0) mp['E']-=mp['G'],mp['I']-=mp['G'],mp['H']-=mp['G'],mp['T']-=mp['G'],ans['8']=mp['G'],mp['G']=0;
		//剩下的
		if(mp['O']!=0) mp['N']-=mp['O'],mp['E']-=mp['O'],ans['1']=mp['O'],mp['O']=0;
		if(mp['T']!=0) mp['H']-=mp['T'],mp['R']-=mp['T'],mp['E']-=mp['T']*2,ans['3']=mp['T'],mp['T']=0;
	    if(mp['F']!=0) mp['I']-=mp['F'],mp['V']-=mp['F'],mp['E']-=mp['F'],ans['5']=mp['F'],mp['F']=0;
	    if(mp['S']!=0) mp['E']-=mp['S']*2,mp['V']-=mp['S'],mp['N']-=mp['S'],ans['7']=mp['S'],mp['S']=0;
	    if(mp['I']!=0) mp['N']-=mp['I']*2,mp['E']-=mp['I'],ans['9']=mp['I'],mp['I']=0;
	    printf("Case #%d: ",p);
		for(char i='0';i<='9';i++) 
	    	for(int j=1;j<=ans[i];j++) cout<<i;
	    printf("\n");
	}
	return 0;
}
```
~~顺便夸赞一下这题的满分分数。（$23$ 分？）~~

撒花！

---

## 作者：xyx404 (赞：3)

## 思路：

通过观察可以发现有一些字母在所有数字中只出现过一次，我们可以先处理这些字母对应的单词。  
比如字母 `Z` 只出现在 `ZERO` 中。

在处理完这些后，我们可以发现有一些字母在这些单词中只出现过两次，而其中一个单词已经处理过了，这时我们就可以直接处理另外一个单词。  
例如 `SIX` 和 `SEVEN`，`SIX` 中的 `X` 只在它自己里面出现，已经被处理了，而 `S` 只在这两个单词中出现，所以剩下的 S 都是 $7$ 的了。

以此类推，我们便可以完成此题。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define itn int
#define ull unsigned long long
int T;
string s;
int main(){
	cin>>T;
	for(int i=1;i<=T;i++){
		cin>>s;
		unordered_map<char,int>cnt;
		int bj[12];memset(bj,0,sizeof bj);
		for(int i=0;i<s.size();i++)cnt[s[i]]++;
		while(cnt['Z']){// ZERO   0   Z 只在 0 中出现
			cnt['Z']--;cnt['E']--;cnt['R']--;
			cnt['O']--;
			bj[0]++;
		}
		while(cnt['W']){// TWO   2
			cnt['T']--;cnt['W']--;cnt['O']--;
			bj[2]++;
		}
		while(cnt['G']){// EIGHT 8
			cnt['E']--;cnt['I']--;cnt['G']--;
			cnt['H']--;cnt['T']--;
			bj[8]++;
		}
		while(cnt['X']){// SIX   6
			cnt['S']--;cnt['I']--;cnt['X']--;
			bj[6]++;
		}
		while(cnt['U']){// FOUR  4
			cnt['F']--;cnt['O']--;cnt['U']--;
			cnt['R']--;
			bj[4]++;
		}
		while(cnt['S']){// SEVEN 7 因为有 S 出现的只有 6 和 7，6 已经处理完了，剩下的 S 都是 7 的了
			cnt['S']--;cnt['E']--;cnt['V']--;
			cnt['E']--;cnt['N']--;
			bj[7]++;
		}
		while(cnt['F']){// FIVE  5
			cnt['F']--;cnt['I']--;cnt['V']--;
			cnt['E']--;
			bj[5]++;
		}
		while(cnt['H']){// THREE 3
			cnt['T']--;cnt['H']--;cnt['R']--;
			cnt['E']--;cnt['E']--;
			bj[3]++;
		}
		while(cnt['I']){// NINE 9
			cnt['N']--;cnt['I']--;cnt['N']--;
			cnt['E']--;
			bj[9]++;
		}
		while(cnt['O']){// ONE 1
			cnt['O']--;cnt['N']--;cnt['E']--;
			bj[1]++;
		}
		cout<<"Case #"<<i<<": ";
		for(int i=0;i<=9;i++){
			while(bj[i])cout<<i,bj[i]--;
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：__szh_DNCB__ (赞：1)

蒟蒻的第六篇题解。

思路别的题解都讲得差不多了，大致就是先把带特别字母的数字（02468）判掉，然后再判 13579。我的思路和别的题解也一样。

但是我选择了用 `map` 记录字符数量，同时为了避免排序，我直接选择桶来记录答案。

注意一下输出即可。

```code
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin >> T;
	for (int tt=1;tt<=T;tt++){
		map <char,int> s;
		int times[10] = {};
		string st;
		cin >> st;
		for (int i=0;i<st.length();i++){
			s[st[i]]++;
		}
		if (s['Z']){
			times[0] += s['Z'];
			s['Z']-=times[0];
			s['E']-=times[0];
			s['R']-=times[0];
			s['O']-=times[0];
		}if (s['W']){
			times[2] += s['W'];
			s['W']-=times[2];
			s['T']-=times[2];
			s['O']-=times[2];
		}if (s['U']){
			times[4] += s['U'];
			s['F']-=times[4];
			s['O']-=times[4];
			s['U']-=times[4];
			s['R']-=times[4];
		}if (s['X']){
			times[6] += s['X'];
			s['S']-=times[6];
			s['I']-=times[6];
			s['X']-=times[6];
		}if (s['G']){
			times[8] += s['G'];
			s['E']-=times[8];
			s['I']-=times[8];
			s['G']-=times[8];
			s['H']-=times[8];
			s['T']-=times[8];
		}if (s['O']){
			times[1] += s['O'];
			s['O']-=times[1];
			s['N']-=times[1];
			s['E']-=times[1];
		}if (s['T']){
			times[3] += s['T'];
			s['T']-=times[3];
			s['H']-=times[3];
			s['R']-=times[3];
			s['E']-=times[3];
			s['E']-=times[3];
		}if (s['F']){
			times[5] += s['F'];
			s['F']-=times[5];
			s['I']-=times[5];
			s['V']-=times[5];
			s['E']-=times[5];
		}if (s['S']){
			times[7] += s['S'];
			s['S']-=times[7];
			s['E']-=times[7];
			s['V']-=times[7];
			s['E']-=times[7];
			s['N']-=times[7];
		}if (s['I']){
			times[9] += s['I'];
			s['N']-=times[9];
			s['I']-=times[9];
			s['N']-=times[9];
			s['E']-=times[9];
		}
		cout << "Case #" << tt << ": ";
		for (int i=0;i<=9;i++){
			for (int j=1;j<=times[i];j++){
				cout << i;
			}
		}
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：Alice2012 (赞：1)

观察发现有些数字的英文包含的字母是它有而别的数字没有的，比如说 `EIGHT` 的 `G`，`FOUR` 的 `U` 等。如果字符串中出现了这些字母，那么我们可以锁定一定出现了某种数字。

但是并不是所有数字都包含这样的独特字母，那么如何去判断其它数字呢？假定某字母 $x$ 在这些单词中出现过 $n$ 次，且通过上述的“包含独特字母”的单词已经锁定了其中的 $n-1$ 个，那么余下的一个可以直接通过 $x$ 锁定。比如说，当通过 `Z` 锁定 `ZERO`，`W` 锁定 `TWO`，`U` 锁定 `FOUR` 后，可以直接通过 `O` 锁定 `ONE`。通过这种方法，我们可以锁定其它的数字。

代码实现中可能存在以第二种方法锁定包含独特字母的单词。但大体思路无异。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,tot,c[30];
string s;
signed main(){
	cin>>T;
	while(T--){
		cin>>s;
		vector<int>ans; 
		for(int i=0;i<26;i++)c[i]=0;
		for(int i=0;i<s.size();i++)c[s[i]-'A']++;
		//由于一个数字可能存在多次，所以要用while查找 
		while(c['G'-'A'])c['E'-'A']--,c['I'-'A']--,c['G'-'A']--,c['H'-'A']--,c['T'-'A']--,ans.push_back(8);//G->EIGHT
		while(c['H'-'A'])c['T'-'A']--,c['H'-'A']--,c['R'-'A']--,c['E'-'A']-=2,ans.push_back(3);//余下的H->THREE 
		while(c['T'-'A'])c['T'-'A']--,c['W'-'A']--,c['O'-'A']--,ans.push_back(2);//余下的T->TWO 
		while(c['U'-'A'])c['F'-'A']--,c['O'-'A']--,c['U'-'A']--,c['R'-'A']--,ans.push_back(4);//U->FOUR 
		while(c['X'-'A'])c['S'-'A']--,c['I'-'A']--,c['X'-'A']--,ans.push_back(6);//x->SIX
		while(c['Z'-'A'])c['Z'-'A']--,c['E'-'A']--,c['R'-'A']--,c['O'-'A']--,ans.push_back(0);//Z->ZERO
		while(c['O'-'A'])c['O'-'A']--,c['N'-'A']--,c['E'-'A']--,ans.push_back(1);//余下的O->ONE 
		while(c['F'-'A'])c['F'-'A']--,c['I'-'A']--,c['V'-'A']--,c['E'-'A']--,ans.push_back(5);//余下的F->FIVE 
		while(c['V'-'A'])c['S'-'A']--,c['E'-'A']-=2,c['V'-'A']--,c['N'-'A']--,ans.push_back(7);//余下的V->SEVEN 
		while(c['N'-'A'])c['N'-'A']-=2,c['I'-'A']--,c['E'-'A']--,ans.push_back(9);//余下的N->NINE 
		sort(ans.begin(),ans.end()),printf("Case #%lld: ",++tot);//注意输出时要排序 
		for(int i=0;i<ans.size();i++)cout<<ans[i];
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：yangdezuo (赞：1)

## 解析
### 题目大意
从一个字符串中解析出其中所含的数字。

### 方法
在 0 到 9 这几个数字的英文中，有几个字母是比较特殊的，比如说 Z，它只会出现在数字 0 当中，因此我们可以通过此性质判断每一个数字。

同时，我们需要存储每一个字母出现的次数，为了方便处理，可以使用 STL 大法中的 map，并将下标定义为 string 或 char 类型。

**注意：** 一些单词中有相同的字母，所以在判断时要注意先后顺序，比如 U 只在 4 中出现，排除 4 之后，F 就只在 5 中出现，剩下可参考下面的代码。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,a[11],x;
string s;
map<char,int>mp;
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>t;
	for(int o=1;o<=t;o++){
		cin>>s;
		for(int i='A';i<='Z';i++) mp[i]=0;
		for(int i:s) mp[i]++;
		memset(a,0,sizeof(a));
		x=mp['Z'];//0
		mp['Z']-=x,mp['E']-=x,mp['R']-=x,mp['O']-=x;
		a[0]+=x;
		x=mp['W'];//2
		mp['W']-=x,mp['T']-=x,mp['O']-=x;
		a[2]+=x;
		x=mp['G'];//8
		mp['E']-=x,mp['I']-=x,mp['G']-=x,mp['H']-=x,mp['T']-=x;
		a[8]+=x;
		x=mp['U'];//4
		mp['F']-=x,mp['O']-=x,mp['U']-=x,mp['R']-=x;
		a[4]+=x;
		x=mp['X'];//6
		mp['S']-=x,mp['I']-=x,mp['X']-=x;
		a[6]+=x;
		x=mp['F'];//5
		mp['F']-=x,mp['I']-=x,mp['V']-=x,mp['E']-=x;
		a[5]+=x;
		x=mp['I'];//9
		mp['N']-=x,mp['I']-=x,mp['N']-=x,mp['E']-=x;
		a[9]+=x;
		cout<<x<<endl;
		x=mp['H'];//3
		mp['T']-=x,mp['H']-=x,mp['R']-=x,mp['E']-=x,mp['E']-=x;
		a[3]+=x;
		x=mp['S'];//7
		mp['S']-=x,mp['E']-=x,mp['V']-=x,mp['E']-=x,mp['N']-=x;
		a[7]+=x;
		x=mp['N'];//1
		mp['O']-=x,mp['N']-=x,mp['E']-=x;
		a[1]+=x;
		cout<<"Case #"<<o<<": ";
		for(int i=0;i<=9;i++){
//			cout<<a[i]<<endl;
			for(int j=1;j<=a[i];j++) cout<<i;
		}
		cout<<'\n';
	}
}
/*
zero one two three four five six seven eight nine ten
z     n   w   h      u  f      x s       g    i   t     
zeroonetwothreefourfivesixseveneightnineten
ZEROONETWOTHREEFOURFIVESIXSEVENEIGHTNINE
*/
```

---

## 作者：huhengrui2013 (赞：1)

### 题解：P13192 [GCJ 2016 #1B] Getting the Digits

[传送门](https://www.luogu.com.cn/problem/P13192)

### 思路：

考虑用 map 记录每个字母出现的次数，有些数字的英文单词包含独特的字母，我们可以优先识别这些数字，如：

* Z 只在 ZERO 时出现。
* W 只在 TWO 时出现。
* U 只在 FOUR 时出现。
* X 只在 SIX 时出现。
* G 只在 EIGHT 时出现。

其他数字可以通过剩余字母识别，如：

* O 只在 ONE 时出现（在减去 ZERO，TWO，FOUR 的 O 之后）。
* T 只在 THREE 中出现（在减去 TWO，EIGHT 的 T 之后）。
* F 只在 FIVE 中出现（在减去 FOUR 的 F 之后）。
* S 只在 SEVEN 中出现（在减去 SIX 的 S 之后）。
* I 只在 NINE 中出现（在减去 SIX，EIGHT，FIVE 的 I 之后）。

识别之后将数字存在数组里，排序即可。

### AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;

void solve(int k,string s){
    cout<<"Case #"<<k<<": ";
    map<char,int> mp;
    int a[1000000],cnt;
    for(char c:s) mp[c]++;
    while(mp['Z']>0){
        a[++cnt]=0;
        mp['Z']--;
        mp['E']--;
        mp['R']--;
        mp['O']--;
    }
    while(mp['W']>0){
        a[++cnt]=2;
        mp['T']--;
        mp['W']--;
        mp['O']--;
    }
    while(mp['U']>0){
        a[++cnt]=4;
        mp['F']--;
        mp['O']--;
        mp['U']--;
        mp['R']--;
    }
    while(mp['X']>0){
        a[++cnt]=6;
        mp['S']--;
        mp['I']--;
        mp['X']--;
    }
    while(mp['G']>0){
        a[++cnt]=8;
        mp['E']--;
        mp['I']--;
        mp['G']--;
        mp['H']--;
        mp['T']--;
    }
    while(mp['O']>0){
        a[++cnt]=1;
        mp['O']--;
        mp['N']--;
        mp['E']--;
    }
    while(mp['T']>0){
        a[++cnt]=3;
        mp['T']--;
        mp['H']--;
        mp['R']--;
        mp['E']--;
        mp['E']--;
    }
    while(mp['F']>0){
        a[++cnt]=5;
        mp['F']--;
        mp['I']--;
        mp['V']--;
        mp['E']--;
    }
    while(mp['S']>0){
        a[++cnt]=7;
        mp['S']--;
        mp['E']--;
        mp['V']--;
        mp['E']--;
        mp['N']--;
    }
    while(mp['I']>0){
        a[++cnt]=9;
        mp['N']--;
        mp['I']--;
        mp['N']--;
        mp['E']--;
    }
    sort(a+1,a+1+cnt);
    for(int i=1;i<=cnt;i++) cout<<a[i];
    cout<<endl;
}
int main(){
    int t;
    cin>>t;
    for(int i=1;i<=t;i++){
        string s;
        cin>>s;
        solve(i,s);
    }
    
}
```

---

## 作者：Luogu_916767 (赞：0)

[InLuogu](https://www.luogu.com.cn/problem/P13192)

### 思路分析

不难发现，有些字母只出现在唯一的数字中，如 `B`、`G`、`L`、`U`、`W`、`X` 和 `Z`。我们可以先把这些数字的数量算出来，记录到数组中。然后，一些在不止一个数字中出现的字母会应这些数字的排除而对应唯一的数字，以此类推，可以分辨出所有数字。


### Code

```cpp
#include<bits/stdc++.h>

using namespace std;

int n;
string s;
int a[26];
int b[10];

int main(){
    cin>>n;
    for(int _ = 1; _ <= n; _ ++ ){
        cin>>s;
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        for(int i = 0; i < s.size(); i ++ ){
            a[s[i]-'A'] ++ ;
        }
        for(int i = 1; i <= a[25]; i ++ ){//Z
            b[0] ++ ;
            a[4] -- ;a[17] -- ;a[14] --;
        }
        a[25] = 0;
        for(int i = 1; i <= a[23]; i ++ ){//X
            b[6] ++ ;
            a[8] --;a[18] -- ;
        }
        a[23] = 0;
        for(int i = 1; i <= a[22]; i ++ ){//W
            b[2] ++ ;
            a[14] -- ;a[19] -- ;
        }
        a[22] = 0;
        for(int i = 1; i <= a[20]; i ++ ){//U
            b[4] ++ ;
            a[5] -- ;a[14] -- ;a[17] -- ;
        }
        a[20] = 0;
        for(int i = 1; i <= a[18]; i ++ ){//S
            b[7] ++ ;
            a[4] -= 2;a[13] -- ;a[21] -- ;
        }
        a[18] = 0;
        for(int i = 1; i <= a[21]; i ++ ){//V
            b[5] ++ ;
            a[4] -- ;a[5] -- ;a[8] -- ;
        }
        a[21] = 0;
        for(int i = 1; i <= a[17]; i ++ ){//R
            b[3] ++ ;
            a[4] -= 2;a[7] -- ;a[19] -- ;
        }
        a[17] = 0;
        for(int i = 1; i <= a[19]; i ++ ){//T
            b[8] ++ ;
            a[4] -- ;a[6] -- ;a[7] -- ;a[8] -- ;
        }
        a[19] = 0;
        for(int i = 1; i <= a[14]; i ++ ){//O
            b[1] ++ ;
            a[4] -- ;a[13] -- ;
        }
        a[14] = 0;
        for(int i = 1; i <= a[4]; i ++ ){//E
            b[9] ++ ;
            a[8] -- ;a[13] -= 2;
        }
        a[4] = 0;
        cout<<"Case #"<<_<<": ";
        for(int i = 0; i <= 9; i ++ ){
            for(int j = 1; j <= b[i]; j ++ ){
                cout<<i;
            }
        }
        cout<<"\n";
    }
}

/*
送你们个表^v^
      A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
ZERO  0 0 0 0 1 0 0 0 0 0 0 0 0 0 1 0 0 1 0 0 0 0 0 0 0 1
ONE   0 0 0 0 1 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0
TWO   0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 1 0 0 1 0 0 0
THREE 0 0 0 0 2 0 0 1 0 0 0 0 0 0 0 0 0 1 0 1 0 0 0 0 0 0
FOUR  0 0 0 0 0 1 0 0 0 0 0 0 0 0 1 0 0 1 0 0 1 0 0 0 0 0
FIVE  0 0 0 0 1 1 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0
SIX   0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 1 0 0 0 0 1 0 0
SEVEN 0 0 0 0 2 0 0 0 0 0 0 0 0 1 0 0 0 0 1 0 0 1 0 0 0 0
EIGHT 0 0 0 0 1 0 1 1 1 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0
NINE  0 0 0 0 1 0 0 0 1 0 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0
*/
```

---

## 作者：Chenxuhang_play (赞：0)

有些数字的英文单词包含独特的字母，我们可以优先识别这些数字：`Z` 只在 `ZERO` 中出现，`W` 只在 `TWO` 中出现，`U` 只在 `FOUR` 中出现，`X` 只在 `SIX` 中出现，`G` 只在 `EIGHT` 中出现。

而在除开这几种之后，又一些具有同样特征的数字：`O`（这个是字母 `O` 而不是数字 $0$） 只在 `ONE` 中出现，`T` 只在 `THREE` 中出现，`F` 只在 `FIVE` 中出现，`S` 只在 `SEVEN` 中出现，`I` 只在 `NINE` 中出现。

由此我们直接模拟即可得出代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string s,ans;
	int t;
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		cin>>s;
		cout<<"Case #"<<i<<": ";
	    map<char,int> map_;
	    int a[2005],ans=0;
	    for(char c:s) map_[c]++;
	    while(map_['Z']>0)
		{
	        a[++ans]=0;
	        map_['Z']--;map_['E']--;map_['R']--;map_['O']--;
	    }
	    while(map_['W']>0)
		{
	        a[++ans]=2;map_['T']--;map_['W']--;map_['O']--;
	    }
	    while(map_['U']>0)
		{
	        a[++ans]=4;map_['F']--;map_['O']--;map_['U']--;map_['R']--;
	    }
	    while(map_['X']>0)
		{
	        a[++ans]=6;map_['S']--;map_['I']--;map_['X']--;
	    }
	    while(map_['G']>0)
		{
	        a[++ans]=8;map_['E']--;map_['I']--;map_['G']--;map_['H']--;map_['T']--;
	    }
	    while(map_['O']>0)
		{
	        a[++ans]=1;map_['O']--;map_['N']--;map_['E']--;
	    }
	    while(map_['T']>0)
		{
	        a[++ans]=3;map_['T']--;map_['H']--;map_['R']--;map_['E']--;map_['E']--;
	    }
	    while(map_['F']>0)
		{
	        a[++ans]=5;map_['F']--;map_['I']--;map_['V']--;map_['E']--;
	    }
	    while(map_['S']>0)
		{
	        a[++ans]=7;map_['S']--;map_['E']--;map_['V']--;map_['E']--;map_['N']--;
	    }
	    while(map_['I']>0)
		{
	        a[++ans]=9;map_['N']--;map_['I']--;map_['N']--;map_['E']--;
	    }
	    sort(a+1,a+1+ans);
	    for(int i=1;i<=ans;i++) cout<<a[i];
	    cout<<endl;
	}
	return 0;
}
```

---

## 作者：Zqx_Vector_2014 (赞：0)

这题看似很难，实则非常简单。

他把题目说的让你以为他很难，实则不然，聪明的你可以发现：某些数字有它独特的特征（ZERO 在所有英文单词中，只有他有 Z，其他同理），但有的所有的字母都有重复怎么办呢？聪明的你又发现了：如果数字 3 判完了，数字 8 就可以判 H 了。

## 思路：

用 map 数组储存每个字符出现的次数，然后~~打表~~，在用一个字符串来储存得出的数据。

所以接下来就是漫长的~~打表~~环节：

>- 0、2、4、6 分别有 Z、W、U、X。
>
>- 0、4 的 R 被消掉了，3 就用 R 来判。
>
>- 接下来就不演示了，自己推吧。

打出来的代码就是：

```cpp
	string ss;
	while(m['Z']) ss+='0',
		m['Z']--,
		m['E']--,
		m['R']--,
		m['O']--;//ZERO
	while(m['W']) ss+='2',
		m['T']--,
		m['W']--,
		m['O']--;//TWO
	while(m['U']) ss+='4',
		m['F']--,
		m['O']--,
		m['U']--,
		m['R']--;//FOUR
	while(m['X']) ss+='6', 
		m['S']--,
		m['I']--,
		m['X']--;//SIX
	while(m['R']) ss+='3',
		m['T']--,
		m['H']--,
		m['R']--,
		m['E']--,
		m['E']--;//THREE
	while(m['H']) ss+='8',
		m['E']--,
		m['I']--,
		m['G']--,
		m['H']--,
		m['T']--;//EIGHT
	while(m['O']) ss+='1',
		m['O']--,
		m['N']--,
		m['E']--;//ONE
	while(m['F']) ss+='5',
		m['F']--,
		m['I']--,
		m['V']--,
		m['E']--;//FIVE
	while(m['V']) ss+='7',
		m['S']--,
		m['E']--,
		m['V']--,
		m['E']--,
		m['N']--;//SEVEN
	while(m['I']) ss+='9',m['I']--;//NINE
```

因为是不下降序列，那么用给字符串就排个序。

```cpp
	sort(ss.begin(),ss.end());
```

都到这了，干脆做一个 $\operatorname{num}$ 函数，把这俩合起来。

```cpp
map<char,int> m;
string num(){
	string ss;
	while(m['Z']) ss+='0',
		m['Z']--,
		m['E']--,
		m['R']--,
		m['O']--;//ZERO
	while(m['W']) ss+='2',
		m['T']--,
		m['W']--,
		m['O']--;//TWO
	while(m['U']) ss+='4',
		m['F']--,
		m['O']--,
		m['U']--,
		m['R']--;//FOUR
	while(m['X']) ss+='6', 
		m['S']--,
		m['I']--,
		m['X']--;//SIX
	while(m['R']) ss+='3',
		m['T']--,
		m['H']--,
		m['R']--,
		m['E']--,
		m['E']--;//THREE
	while(m['H']) ss+='8',
		m['E']--,
		m['I']--,
		m['G']--,
		m['H']--,
		m['T']--;//EIGHT
	while(m['O']) ss+='1',
		m['O']--,
		m['N']--,
		m['E']--;//ONE
	while(m['F']) ss+='5',
		m['F']--,
		m['I']--,
		m['V']--,
		m['E']--;//FIVE
	while(m['V']) ss+='7',
		m['S']--,
		m['E']--,
		m['V']--,
		m['E']--,
		m['N']--;//SEVEN
	while(m['I']) ss+='9',m['I']--; 
	sort(ss.begin(),ss.end());
	return ss;
}
```

加上 $\operatorname{mian}$ 函数和输入输出以及关于 m 的一些小操作，就做成总代码。

# Code：

```cpp
#include<bits/stdc++.h>
#define int long long
#define _n "\n"
#define _t "\t"
#define pr(x,y) printf("Case #%lld: %s\n",x,y)
const int mod=1e9+7;
const int inf=1e13;
const int bze=16;
using namespace std;
int max(int A,int B){return (A>B)?A:B;}
int min(int A,int B){return (A<B)?A:B;}
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int lcm(int a,int b){return a*b/gcd(a,b);}
map<char,int> m;
string num(){
	string ss;
	while(m['Z']) ss+='0',
		m['Z']--,
		m['E']--,
		m['R']--,
		m['O']--;//ZERO
	while(m['W']) ss+='2',
		m['T']--,
		m['W']--,
		m['O']--;//TWO
	while(m['U']) ss+='4',
		m['F']--,
		m['O']--,
		m['U']--,
		m['R']--;//FOUR
	while(m['X']) ss+='6', 
		m['S']--,
		m['I']--,
		m['X']--;//SIX
	while(m['R']) ss+='3',
		m['T']--,
		m['H']--,
		m['R']--,
		m['E']--,
		m['E']--;//THREE
	while(m['H']) ss+='8',
		m['E']--,
		m['I']--,
		m['G']--,
		m['H']--,
		m['T']--;//EIGHT
	while(m['O']) ss+='1',
		m['O']--,
		m['N']--,
		m['E']--;//ONE
	while(m['F']) ss+='5',
		m['F']--,
		m['I']--,
		m['V']--,
		m['E']--;//FIVE
	while(m['V']) ss+='7',
		m['S']--,
		m['E']--,
		m['V']--,
		m['E']--,
		m['N']--;//SEVEN
	while(m['I']) ss+='9',m['I']--; 
	sort(ss.begin(),ss.end());
	return ss;
}signed main(){
	ios::sync_with_stdio(0),
	cin.tie(0),cout.tie(0);
	int n;cin>>n;
	for(int i=0;i<n;i++){
		string ss;cin>>ss;
		for(int i=0;i<ss.size();i++)
			m[ss[i]]++;
		ss=num();
		pr(i+1,ss.c_str());
		m.clear();
	}
}
```

---

