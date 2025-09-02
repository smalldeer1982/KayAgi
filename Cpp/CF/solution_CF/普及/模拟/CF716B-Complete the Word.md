# Complete the Word

## 题目描述

ZS the Coder loves to read the dictionary. He thinks that a word is nice if there exists a substring (contiguous segment of letters) of it of length $ 26 $ where each letter of English alphabet appears exactly once. In particular, if the string has length strictly less than $ 26 $ , no such substring exists and thus it is not nice.

Now, ZS the Coder tells you a word, where some of its letters are missing as he forgot them. He wants to determine if it is possible to fill in the missing letters so that the resulting word is nice. If it is possible, he needs you to find an example of such a word as well. Can you help him?

## 说明/提示

In the first sample case, ABCDEFGHIJKLMNOPQRZTUVWXYS is a valid answer beacuse it contains a substring of length $ 26 $ (the whole string in this case) which contains all the letters of the English alphabet exactly once. Note that there are many possible solutions, such as ABCDEFGHIJKLMNOPQRSTUVWXYZ or ABCEDFGHIJKLMNOPQRZTUVWXYS.

In the second sample case, there are no missing letters. In addition, the given string does not have a substring of length $ 26 $ that contains all the letters of the alphabet, so the answer is $ -1 $ .

In the third sample case, any string of length $ 26 $ that contains all letters of the English alphabet fits as an answer.

## 样例 #1

### 输入

```
ABC??FGHIJK???OPQR?TUVWXY?
```

### 输出

```
ABCDEFGHIJKLMNOPQRZTUVWXYS```

## 样例 #2

### 输入

```
WELCOMETOCODEFORCESROUNDTHREEHUNDREDANDSEVENTYTWO
```

### 输出

```
-1```

## 样例 #3

### 输入

```
??????????????????????????
```

### 输出

```
MNBVCXZLKJHGFDSAQPWOEIRUYT```

## 样例 #4

### 输入

```
AABCDEFGHIJKLMNOPQRSTUVW??M
```

### 输出

```
-1```

# 题解

## 作者：wkjwkj (赞：3)

[可能更好的阅读体验](https://mywkj.github.io/2020/04/16/cf716b-ti-jie/)

[原题链接](http://codeforces.com/problemset/problem/716/B)

- 本题还是比较容易的，以26个字母为一段，只要从前到后枚举每一段的末尾，同时去判断该段是否成立。若成立(即将问号填上后能使每个大写字母都出现一次)，就退出循环。并将剩余所有的问号都填上‘A’，~~这个其实可以随便填，反正有SPJ~~。如果整一个字符串都搜完了也没有一种合法的方案，则输出"-1".

  来看一下AC代码吧

```cpp
  #include<bits/stdc++.h>
  using  namespace std;
  char s[50005];
  int b[30];
  int main()
  {
  	scanf("%s",s+1);
  	int len=strlen(s+1);
  	if(len<26){//长度小于26直接输出-1
  		puts("-1");
  		return 0;
  	}
  	for(int i=1;i<=25;i++)
  	  if(s[i]>='A'&&s[i]<='Z')b[s[i]-'A'+1]++;//统计每个字母出现的次数
  	bool ok=false;
  	for(int i=26;i<=len;i++)//枚举每一段的末尾
  	{
  		if(s[i]>='A'&&s[i]<='Z')b[s[i]-'A'+1]++;//统计每个字母出现的次数
  		bool yes=0;
  		for(int j=1;j<=26;j++)if(b[j]>1){yes=1;break;}//有字母的出现次数>1则说明该段不可能成为合法段
  		if(yes){
  			if(s[i-25]>='A'&&s[i-25]<='Z')b[s[i-25]-'A'+1]--;
  			continue;
  		}
  		for(int p=i-25;p<=i;p++)//将问号填上
  		{
  			if(s[p]=='?'){
  				int w;
  				for(int j=1;j<=26;j++)
  				  if(b[j]==0){
  				  	w=j;
  				  	b[j]=1;
  				  	break;
  				  }
  				s[p]=w+'A'-1;
  			}
  		}
  		ok=true;
  		break;
  	}
  	if(ok){
  		for(int i=1;i<=len;i++)
  		  if(s[i]=='?')s[i]='A';
  		for(int i=1;i<=len;i++)
  		  printf("%c",s[i]);
  		return 0;
  	}
  	puts("-1");//未找到合法段
  	return 0;
  }
```

  

---

## 作者：cff_0102 (赞：1)

字符串长度最多才 $50000$，直接枚举不会超时。

读入后，先判断字符串长度是否小于 $26$，如果是直接输出 `-1`。

然后，枚举每一段长为 $26$ 的连续子串，看这个子串能否让 $26$ 个字母都出现一次。如果每个都不能，输出 `-1`。碰到有一个可以的，就把这个子串用 $26$ 个字母填满，剩下的问号随便选一个字母代替。然后输出，结束程序。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	string s;cin>>s;
	if(s.length()<26){
		cout<<-1;
		return 0;
	}
	int l=s.length();
	bool x=0;//是否有解 
	for(int i=26;i<=l;i++){
		int t[256];
		for(int j=0;j<255;j++)t[j]=0;
		for(int j=i-26;j<i;j++){
			t[s[j]]++;//记录 s[j] 这个字符出现几次
		}
		bool f=0;//是否无法满足要求 
		for(int j='A';j<='Z';j++){
			if(t[j]>1){//这一段子串无法满足要求 
				f=1;
				break;
			}
		}
		if(f)continue;
		//现在这个子串已经被确认能够满足要求了
		x=1;//有解 
		//要把这段子串里面问号的拿没出现过的字母填上
		int n='A';//目前碰到问号填 'A'
		for(int j=i-26;j<i;j++){
			while(t[n]&&n<='Z')n++;//这样能让 n 变为下一个没有被填进这段子串的字符，或者在这段子串已经填完时变为 'Z'+1
			if(s[j]=='?'){//这个空需要填
				s[j]=n;//这个空填上 n
				t[n]++;
			}
		}
		//现在这个子串已经被填完了，要填上剩下的空
		srand(time(NULL));//猜猜是干嘛的 
		for(int j=0;j<l;j++){
			if(s[j]=='?'){
				char c=rand()%26+'A';//随机生成一个字母
				s[j]=c;//填进去 
			}
		}
		//把 s 填完了，解已经知道了，要退出循环
		break; 
	}
	if(x==0){//无解 
		cout<<-1;
	}else{
		cout<<s;//别忘记输出了！ 
	}
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/116845483)，将近 $5$ 分钟才测完所有数据。

---

## 作者：ATION001 (赞：0)

~~这题也没那么难吧。~~
## 题目大意
给定一个字符串 $s$，现要求你修改 $s$ 中元素为`?`的点，将这一节点修改成任意大写字母，最后要求 $s$ 包含所有大写字母。
## 思路
首先长度小于 $26$ 一定无解。

对于长度大于等于 $26$ 的情况该咋办呢？对于 $s_i$，如果其值为`?`，枚举 $s$ 里字典序最小没有出现过的字母，将 $s_i$ 的值替换掉，否则不做改变。

如果字母都填完了，$s$ 里还有`?`的话，把`?`随便替换成任意字母就行了。

都填完了还是不满足条件直接输出 $-1$。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int cnt[100],ch;
bool flag=false;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>s;
	for(int l=0,r=0;l<s.size()&&r<s.size();r++){
		cnt[s[r]]++;
		ch+=(cnt[s[r]]==1&&s[r]!='?');
		while(s[r]!='?'&&cnt[s[r]]>1){
			cnt[s[l]]--;
			ch-=(!cnt[s[l]]&&s[l]!='?'),l++;
		}
		if(ch+cnt[int('?')]==26){
			flag=true;
			for(int i=l,j='A';i<=r;i++){
				if(s[i]=='?'){
					while(cnt[j]){
						j++;
					}
					s[i]=char(j),j++;
				}
			}
			break;
		}
	}
	if(flag){
		for(auto x:s){
			cout<<(x=='?'?'A':x);
		}
	}else{
		cout<<-1;
	}
} 
```

---

## 作者：The_outcast_person (赞：0)

简易构造题。以下称长度为 $26$，并且其中每个大写字母都出现一次的字串为目标串。

我们从头开始枚举字符串，并截出其后 $26$ 位。用一个桶记录每个字符是否出现过，顺带记下当前问号的个数与字母的种类数。这里提一下，我们认为出现了一个新的种类的字母，**当且仅当**当前枚举到的非问号字母在桶里没出现过。如果字母的种类数与问号的个数加起来不到 $26$，我们认为这 $26$ 个字符不能构成目标串。否则我们再次遍历这 $26$ 个字符，找到一个问号，就将其替换为一个未出现过的字母。而未出现过的字母可以提前遍历桶来预存在一个字符串里，实现 $O(1)$ 替换。完成后将标记设为 $1$ 就可以退出循环了。最后输出时，若标记还是 $0$，代表无法构成目标串，输出 $-1$；否则可能还会有未替换的问号，全部替换为任意字母即可。

附上代码：
```cpp
#include<bits/stdc++.h>
//#define int long long
#define il inline
#define pii pair<int,int>
#define mk make_pair
#define mod 998244353
using namespace std;
il int rd(){
    int jya=0,tl=1;char jyt=getchar();
    while(!isdigit(jyt)){if(jyt=='-')tl=-1;jyt=getchar();}
    while(isdigit(jyt)){jya=(jya<<1)+(jya<<3)+(jyt-'0');jyt=getchar();}
    return jya*tl;
}
il void wr(int jjy){
    if(jjy<0)putchar('-'),jjy=-jjy;
    if(jjy>9)wr(jjy/10);
    putchar(jjy%10+48);
}
il int max(int x,int y){return x>=y?x:y;}
il int min(int x,int y){return x<=y?x:y;}
const int JYAAKIOI=1145141919810;
string s,k;
int ls,t[186],ss,sum;
bool p;
int main(){
	//freopen("jytwcsnm.in","r",stdin);
	//freopen("jytwcsnm.out","w",stdout);
	cin>>s;
	ls=s.size();
	for(int i=0;i<ls;++i){
		if(i+25>=ls||p)break;
		memset(t,0,sizeof t);
		sum=ss=0;
		for(int j=i;j<=i+25;++j){
			if(s[j]=='?'){
				++sum;
				continue;
			}
			if(!t[int(s[j])])++ss;
			++t[int(s[j])];
		}
		if(ss+sum<26)continue;
		p=1;
		k="";int now=0;
		for(char j='A';j<='Z';++j){
			if(!t[int(j)])k=k+j; 
		}
		for(int j=i;j<=i+25;++j){
			if(s[j]=='?')s[j]=k[now],++now;
		}
	}
	if(!p)wr(-1);
	else {
		for(int i=0;i<ls;++i){
			if(s[i]=='?')putchar('A');
			else putchar(s[i]);
		}
	}
	return 0;
}
```

---

## 作者：Ryan_Adam (赞：0)

# CF716B Complete the Word 题解
## 分析
首先观察数据范围是 $50000$，可以考虑 $O(n)$ 暴力。

在字符串中枚举子串开始的位置 $i$，然后再枚举 $i$ 到 $i+25$，开个桶统计每个大写字母出现的次数，如果大于 $1$ 就直接 `break`。统计完之后剩下的就都是问号了，可以随便填，所以这个子串是一定合法的。用 $ans$ 来截取这一段合法子串，$st$ 记录 $ans$ 的起始位置，方便输出。如果所有子串都枚举完没有合法的，输出 $-1$ 即可。

输出时没到子串 $ans$ 时输出原串，问号随便输出。枚举到 $st$ 时就输出 $ans$，问号处缺啥填啥。
## 代码
代码过长，参考为主，不喜勿喷
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Raiden
{
    int t[30];
    signed work()
    {
        string s, ans;
        int st;
        cin >> s;
        if (s.size() < 26)
            cout << -1 << endl, return 0;
        bool flag = 1;
        for (int i = 0; i <= s.size() - 26; i++)
        {
            flag = 1;
            memset(t, 0, sizeof(t));
            for (int j = i; j < i + 26; j++)
            {
                if (s[j] != '?')
                {
                    if (t[s[j] - 'A'] > 0)
                        flag = 0, break;
                    t[s[j] - 'A']++;
                }
            }
            if (flag)
            {
                ans = s.substr(i, 26);
                st = i;
                break;
            }
        }
        if (!flag)
            cout << -1 << endl, return 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (i == st)
            {
                for (auto it : ans)
                {
                    if (it == '?')
                    {
                        for (int i = 0; i < 26; i++)
                            if (t[i] == 0)
                            {
                                cout << char(i + 'A');
                                t[i]++;
                                break;
                            }
                    }
                    else
                        cout << it;
                }
                i = st + 25;
            }
            else
            {
                if (s[i] == '?')
                    cout << 'A';
                else
                    cout << s[i];
            }
        }
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Raiden::work();
}
```

---

## 作者：Elhaithan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF716B)
### 思路
因为字符串长度 $1 \leqslant |s| \leqslant 50000$，所以可以直接枚举原字符串中长度为 $26$ 的子串，不会超时。

遍历子串中的每一个字符，并记录其中每个大写字母出现的次数。判断这个子串是否满足条件，如果满足条件就将子串中的 `?` 转换为符合要求的大写字母，否则就遍历下一个子串。最后再将剩下的 `?` 改成任意大写字母就行了。
### AC code
详情见代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
string s;
map <char,int> freq;//用于记录每个大写字母的数量 
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin>>s;
	int len=s.size();
	if(len<26){
		cout<<-1;//字符串长度小于26的明显不符合条件
		return 0;
	} 
	for(int i=0; i<=len-26; i++){//减26防止超出原字符串大小
		for(char j='A'; j<='Z'; j++) freq[j]=0;//每次循环将计数器清零 
		bool flag=false;
		for(int j=i; j<=i+25; j++){//遍历字符
			if(s[j]>='A' && s[j]<='Z'){
				freq[s[j]]++;
				if(freq[s[j]]>1){
					flag=true;//如果子串中有重复字母，那必定至少有一个字母是没法填上的 
					break;
				}
			}
		}
		if(flag) continue;//判断 
		char c='A';//从'A'开始填
		for(int j=i; j<=i+25; j++){
			if(s[j]=='?'){
				while(freq[c]>0) c++;//如果字母已经出现过，就遍历下一个字母 
				s[j]=c;
				freq[c]++;
			}
		}
		srand(time(0));//产生随机数 
		for(int j=0; j<len; j++){
			if(s[j]=='?') s[j]=rand()%26+'A';//随机大写字母 
		}
		cout<<s;//输出答案
		return 0;
	}
	cout<<-1;//如果没找到符合条件的的就输出-1 
	
	return 0;
}

```

---

## 作者：G__G (赞：0)

这道题还挺简单的。~~结果调代码时因为 $i$ 和 $j$ 不分调了两晚上。~~

对于对于给定的字符串的每一个长为 26 的子串，要想使其包含所有字母，则必须保证里面没有重复的字母。所以，我们可以先判断一下子串里有无重复字母。如果没有，则保证一定有解。若每一个长为 26 的子串里都有重复字母，则无解，输出 -1 即可。

接下来就是最关键的步骤：**构造**（由于本题有 SPJ，所以只要输出的解合理即可，方法可能很多，下面只给出一种）。

举个例子来说明一下：

$$??ABABABABC??FGHIJK???OPQR?TUVWXY???BABABA??$$

先找出一组可以构造的字串：

$$ABC??FGHIJK???OPQR?TUVWXY?$$

而此时我们不难找出一个满足的方案：

$$ABCDEFGHIJKLMNOPQRSTUVWXYZ$$

再将这个字串带到原串中，我可以发现，剩下的问号可以用任何字母来填充，把所有问号都消除后，一种方案就构造好了。

最后再看看代码，消化一下。

```
#include<bits/stdc++.h>
using namespace std;
int a[30]={1,0},x=0,y=0;
int main(){
	string s;
	cin>>s;
	if(s.size()<26){
		cout<<-1<<endl;
		return 0;
	}
	for(int i=0;i<=s.size()-26;i++){
		for(int j=1;j<=26;j++){
			a[j]=0;
		}
		bool f=0;
		for(int j=i;j<=i+25;j++){
			if(s[j]=='?'){
				continue;
			}
			a[(int)(s[j]-'A'+1)]++;
			if(a[(int)(s[j]-'A'+1)]==2){
				f=1;
				break;
			}
		}
		if(f){
			continue;
		}
		for(int j=i;j<=i+25;j++){
			if(s[j]=='?'){
				for(int k=1;k<=26;k++){
					if(a[k]==0){
						a[k]++;
						s[j]=(char)(k-1+'A');
						break; 
					}
				}
			}
		}
		for(int j=0;j<s.size();j++){
			if(s[j]=='?'){
				s[j]='A';
			}
			cout<<s[j];
		}
		return 0;
	}
	cout<<-1<<endl;
	return 0;
}
```


---

## 作者：Otue (赞：0)

## 思路
随便找到一个长度为 $26$ 的子串，若这个子串没有重复的字母，就可以对其进行替换。

有一个坑点，若还有剩下的 `?` 号，需要替换为任意一个大写字母。
## 代码
用 `map` 实现的代码：
```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 50500;

int n;
char a[N];

int main() {
    cin >> (a + 1);
    int lens = strlen(a + 1);
    for (int i = 1; i <= lens - 26 + 1; i++) {
        map<char, int> vis;
        map<char, int> vis2;
        for (int j = i; j <= i + 26 - 1; j++) {
            if (a[j] != '?') {
                vis[a[j]]++; // 统计字母出现次数
            }
        }
        int flg = 0;
        for (auto id = vis.begin(); id != vis.end(); id++) {
            if (id -> second > 1) flg = 1;  // 若没有重复字母
        } 
        if (!flg) {
            for (char a = 'A'; a <= 'Z'; a++) {
                if (vis[a] == 0) vis2[a] = 1;  // 记录没有出现过的字母
            }
            auto id = vis2.begin();  // 搞一个迭代器，扫一遍！
            for (int j = 1; j <= i - 1; j++) {
                if (a[j] == '?') cout << 'A';
                else cout << a[j];
            }
            for (int j = i; j <= i + 25; j++) {
                if (a[j] != '?') cout << a[j];
                else cout << id -> first, id++;  
            }
            for (int j = i + 26; j <= lens; j++) {
                if (a[j] == '?') cout << 'A';
                else cout << a[j];
            }
            exit(0);
        }
    }
    puts("-1");
}
```
完全可以不用 `map`：
```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 50500;

int n;
char a[N];

int main() {
    cin >> (a + 1);
    int lens = strlen(a + 1);
    for (int i = 1; i <= lens - 26 + 1; i++) {
        int vis[30] = {}, vis2[30] = {};
        for (int j = i; j <= i + 26 - 1; j++) {
            if (a[j] != '?') {
                vis[a[j] - 'A']++;
            }
        }
        int flg = 0;
        for (int j = 0; j < 26; j++) {
            if (vis[j] > 1) flg = 1;
        } 
        int ans[30] = {}, l = 0, id = 1;
        for (char a = 'A'; a <= 'Z'; a++) {
            if (vis[a - 'A'] == 0) ans[++l] = a - 'A';
        }
        if (!flg) {
            for (int j = 1; j <= i - 1; j++) {
                if (a[j] == '?') cout << 'A';
                else cout << a[j];
            }
            for (int j = i; j <= i + 25; j++) {
                if (a[j] != '?') cout << a[j];
                else cout << char(ans[id] + 'A'), id++;
            }
            for (int j = i + 26; j <= lens; j++) {
                if (a[j] == '?') cout << 'A';
                else cout << a[j];
            }
            exit(0);
        }
    }
    puts("-1");
}
```

---

## 作者：Siteyava_145 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF716B)

- 首先，如果输入的字符串的长度小于 $26$，那么字母是一定凑不齐的。

- 当字符串长度大于等于 $26$ 时，每 $26$ 个字符分一段进行判断，枚举每一段的开头。先用桶存每个字母的出现次数，如果有某字母出现 $2$ 次，那么不符合要求；反之则每种字母都出现不超过 $1$ 次，出现 $0$ 次的字母填充进“？”里，然后输出最终结果，跳出循环，防止多次输出。

- 输出时别忘把剩下的“？”改成字母，输出时加特判，第六个测试点卡。

- 解法在注释里详细说明。
AC CODE：

```
#include<bits/stdc++.h>
using namespace std;
int t[128];//桶，判定字符出现次数【13-20】行 
int main(){
    char c[50005];//字符串 
    cin>>c; 
	if(strlen(c)<26){cout<<-1;return 0;}//特判， c的长度<26时输出-1 
    for(int l=0;l<=strlen(c)-26;l++){//枚举每一段【长度26】的开头，共有c的长度-26+1段 
        int fl=0; //标记变量，让遍历到2个相同字母的时候 continue掉 
        memset(t,0,sizeof t);//清空桶 
        for(int i=l;i<26+l;i++){//判定字符出现次数 
        	if(c[i]=='?')continue;//遇到？时continue 
            t[c[i]]++;
            if(t[c[i]]==2){fl=1;break;}//如果有2个相同字母，就让标记变量=1，将开头+1 (16-18行)continue) 
        }
        if(fl){
	        continue;
        }
        //如果每个字母都不一样： 
        for(int i=l;i<(26+l);i++){//填充‘？’ 
            if(c[i]=='?'){ 
                for(int j=65;j<=90;j++){//A-Z 
                    if(t[j]==0){//如果字母没出现过 
                        t[j]=1;//让这个字母标记为出现过，避免重复 
                        c[i]=char(j);//填充 
                        break;
                    }
                }
            }
        }
        for(int i=0;i<strlen(c);i++){//输出 
        	if(c[i]=='?')cout<<'A';//填充剩下的‘？’,任意字母【SPJyyds】
        	else cout<<c[i];
		}
        return 0;
    }
    cout<<-1;//如果没有一段符合要求，输出-1 
    return 0;
}
```

---

## 作者：YueYang1235 (赞：0)

我的大致思路如下：

枚举每一个长度为 $ 26 $ 的连续字串，再开一个桶统计判断，计算下一个字串时，只需把开头扔掉，结尾加上即可。

可能实现有一点点麻烦，具体见代码注释。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;//原始字符串。
int n,a[55000];
int ha[50];
int main(){
	cin>>s;
	n=s.size();
	for(int i=1;i<=n;++i)a[i]=(s[i-1]=='?'?0:s[i-1]-'A'+1);//把字符串转化成数字。
	if(n<26){
		printf("-1\n");
		return 0;
	}//如果长度连26都没满，直接退出。
	for(int i=1;i<=26;++i)ha[a[i]]++;//开桶统计。
	for(int i=2;i<=n-24;++i){//由于每次是先判断后修改，所以i的取值范围要加1，n-26+1+1=n-24。
		int flag=1;
		for(int j=1;j<=26;++j)
			if(ha[j]>1){flag=0;break;}//判断是否有出现2次及两次以上的数，如果有就不满足条件了。
		if(flag){//如果满足
			for(int j=i-1;j<=i+24;++j)//先判断后修改，j的取值范围两端都要减1。
				if(a[j]==0)
					for(int k=1;k<=26;++k)
						if(ha[k]==0){a[j]=k;ha[k]=1;break;}//如果是问号的地方就填上，记得要把填的这个数标为1。
			for(int j=1;j<=n;++j){
				if(a[j]==0)printf("A");//其他问号的地方随便填，这里写的是‘A’，当然你也可以rand()。
				else cout<<char(a[j]+'A'-1);
			}
			exit(0);//直接结束程序。
		}
		ha[a[i-1]]--;
		ha[a[i+25]]++;//开头扔掉，结尾加上。
	}
	printf("-1\n");//如果中间没有直接结束，那么就是无解的，输出-1。
	return 0;
}
```


---

